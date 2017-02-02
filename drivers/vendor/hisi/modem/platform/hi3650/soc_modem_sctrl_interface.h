

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_MODEM_SCTRL_INTERFACE_H__
#define __SOC_MODEM_SCTRL_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) cpu_if_mdm_sc_auto
 ****************************************************************************/
/* �Ĵ���˵�����ϵ���ʱ��ʹ�ܼĴ���������ʹ������ʱ�ӡ��Ա���д1��ʹ�ܶ�Ӧ��ʱ�ӣ�д0��Ӱ��ʱ��ʹ�ܵ�״̬��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_UNION */
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ADDR(base)     ((base) + (0x0000))

/* �Ĵ���˵�����ϵ���ʱ�ӽ�ֹ�Ĵ��������ڽ�ֹ����ʱ�ӡ��Ա���д1����ֹ��Ӧ��ʱ�ӣ�д0��Ӱ��ʱ��ʹ�ܵ�״̬��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_UNION */
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ADDR(base)    ((base) + (0x0004))

/* �Ĵ���˵�����ϵ���ʱ��״̬�Ĵ��������ڻض�������ʱ�ӵ�״̬������ʱ�ӿ����ź��辭����CRG�н���ͬ��������ˣ�����ļĴ���ֵ���ӳ���Ӧʱ����ļ������ں��������Ӧʱ��״̬��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ADDR(base) ((base) + (0x0008))

/* �Ĵ���˵�����ϵ�����λʹ�ܼĴ���������ʹ�����踴λ���Ա���д1����ӦIP���븴λ״̬��д0��Ӱ�츴λ״̬��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_UNION */
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_ADDR(base)     ((base) + (0x0018))

/* �Ĵ���˵�����ϵ�����λ��ֹ�Ĵ��������ڽ�ֹ���踴λ���Ա���д1����Ӧ��������λ��д0��Ӱ�츴λʹ�ܵ�״̬��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_UNION */
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_ADDR(base)    ((base) + (0x001C))

/* �Ĵ���˵�����ϵ�����λ״̬�Ĵ��������ڻض������踴λ��״̬�����踴λ�����ź��辭��ͬ��������ˣ�����ļĴ���ֵ���ӳ���Ӧʱ����ļ������ں��������Ӧ�⸴λ״̬��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_ADDR(base) ((base) + (0x0020))

/* �Ĵ���˵����������ʱ��ʹ�ܼĴ��������ڿ��Ƹ��������ܵ�ʱ��ʹ�ܡ�����Ӧλд1ʹ����Ӧ��ѹ��ʱ�ӣ�д0��Ӱ�졣�üĴ���ֻ���ϵ縴λʱ����λ��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_ADDR(base)     ((base) + (0x0040))

/* �Ĵ���˵����������ʱ�ӽ�ֹ�Ĵ��������ڿ��Ƹ��������ܵ�ʱ�ӽ�ֹ������Ӧλд1��ֹ��Ӧ������ʱ�ӣ�д0��Ӱ�졣�üĴ���ֻ���ϵ縴λʱ����λ��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_PW_CLKDIS_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKDIS_ADDR(base)    ((base) + (0x0044))

/* �Ĵ���˵�����µ���ʱ��״̬��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_STAT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_STAT_ADDR(base) ((base) + (0x0048))

/* �Ĵ���˵������������λʹ�ܼĴ��������ڿ��Ƹ��������ܵĸ�λʹ�ܡ�����Ӧλд1ʹ����Ӧ��������λ�źţ������븴λ̬����д0��Ӱ�졣�üĴ���ֻ���ϵ縴λʱ����λ��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_ADDR(base)     ((base) + (0x004C))

/* �Ĵ���˵������������λ��ֹ�Ĵ��������ڿ��Ƹ��������ܵĸ�λ��ֹ������Ӧλд1��ֹ��Ӧ��������λ�źţ����˳���λ̬����д0��Ӱ�졣�üĴ���ֻ���ϵ縴λʱ����λ��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_PW_RSTDIS_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTDIS_ADDR(base)    ((base) + (0x0050))

/* �Ĵ���˵�����µ�����λ״̬
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_STAT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_STAT_ADDR(base) ((base) + (0x0054))

/* �Ĵ���˵����������ISOʹ�ܼĴ��������ڿ��Ƹ���������ص�Isolation Cellʹ�ܡ�����Ӧλд1ʹ����Ӧ������IsoLation Cell�����źŸ��ϣ���д0��Ӱ�졣�üĴ���ֻ���ϵ縴λʱ����λ��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_ADDR(base)     ((base) + (0x0058))

/* �Ĵ���˵����������ISO��ֹ�Ĵ��������ڿ��Ƹ���������ص�Isolation Cell��ֹ������Ӧλд1��ֹ��Ӧ������IsoLation Cell�����źŲ����ϣ���д0��Ӱ�졣�üĴ���ֻ���ϵ縴λʱ����λ��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_PW_ISODIS_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PW_ISODIS_ADDR(base)    ((base) + (0x005C))

/* �Ĵ���˵�����µ���ISO״̬��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_STAT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_STAT_ADDR(base) ((base) + (0x0060))

/* �Ĵ���˵������������Դʹ�ܼĴ��������ڿ��Ƹ��������ĵ�Դʹ�ܣ�����Ӧλд1����Ӧ��ѹ���Դ��д0��Ӱ�졣�üĴ�����ֻ���ϵ縴λʱ����λ��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSEN_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSEN_ADDR(base)  ((base) + (0x0064))

/* �Ĵ���˵������������Դ��ֹ�Ĵ��������ڿ��Ƹ��������ĵ�Դ��ֹ������Ӧλд1�ر���Ӧ��ѹ���Դ��д0��Ӱ�졣�üĴ�����ֻ���ϵ縴λʱ����λ��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSDIS_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSDIS_ADDR(base) ((base) + (0x0068))

/* �Ĵ���˵������������Դ����״̬
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_STAT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_STAT_ADDR(base) ((base) + (0x006C))

/* �Ĵ���˵�����µ���MTCMOS��ʱ����Դ�����ź�
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_ACK_SUB_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_ACK_SUB_ADDR(base) ((base) + (0x0074))

/* �Ĵ���˵����ϵͳPOWER״̬�Ĵ��������ڼ��ϵͳ������POWER״̬��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_TIMEOUT_STAT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_TIMEOUT_STAT_ADDR(base) ((base) + (0x0078))

/* �Ĵ���˵��������ʱ��ʹ�ܼĴ���������ʹ������ʱ�ӡ��Ա���д1��ʹ�ܶ�Ӧ��ʱ�ӣ�д0��Ӱ��ʱ��ʹ�ܵ�״̬��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_ADDR(base) ((base) + (0x0100))

/* �Ĵ���˵��������ʱ�ӽ�ֹ�Ĵ��������ڽ�ֹ����ʱ�ӡ��Ա���д1����ֹ��Ӧ��ʱ�ӣ�д0��Ӱ��ʱ��ʹ�ܵ�״̬��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_ADDR(base) ((base) + (0x0104))

/* �Ĵ���˵��������ʱ��״̬�Ĵ���9�����ڻض�������ʱ�ӵ�״̬������ʱ�ӿ����ź��辭����CRG�н���ͬ��������ˣ�����ļĴ���ֵ���ӳ���Ӧʱ����ļ������ں��������Ӧʱ��״̬��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_ADDR(base) ((base) + (0x0108))

/* �Ĵ���˵����BBPʱ��ʹ�ܼĴ���0������ʹ������ʱ�ӡ��Ա���д1��ʹ�ܶ�Ӧ��ʱ�ӣ�д0��Ӱ��ʱ��ʹ�ܵ�״̬��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_ADDR(base)   ((base) + (0x0120))

/* �Ĵ���˵��������ʱ�ӽ�ֹ�Ĵ���0�����ڽ�ֹ����ʱ�ӡ��Ա���д1����ֹ��Ӧ��ʱ�ӣ�д0��Ӱ��ʱ��ʹ�ܵ�״̬��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_ADDR(base)  ((base) + (0x0124))

/* �Ĵ���˵��������ʱ��״̬�Ĵ���0�����ڻض�������ʱ�ӵ�״̬������ʱ�ӿ����ź��辭����CRG�н���ͬ��������ˣ�����ļĴ���ֵ���ӳ���Ӧʱ����ļ������ں��������Ӧʱ��״̬��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_ADDR(base) ((base) + (0x0128))

/* �Ĵ���˵����BBPʱ��ʹ�ܼĴ���1������ʹ������ʱ�ӡ��Ա���д1��ʹ�ܶ�Ӧ��ʱ�ӣ�д0��Ӱ��ʱ��ʹ�ܵ�״̬��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_ADDR(base)   ((base) + (0x012C))

/* �Ĵ���˵��������ʱ�ӽ�ֹ�Ĵ���1�����ڽ�ֹ����ʱ�ӡ��Ա���д1����ֹ��Ӧ��ʱ�ӣ�д0��Ӱ��ʱ��ʹ�ܵ�״̬��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_ADDR(base)  ((base) + (0x0130))

/* �Ĵ���˵��������ʱ��״̬�Ĵ���1�����ڻض�������ʱ�ӵ�״̬������ʱ�ӿ����ź��辭����CRG�н���ͬ��������ˣ�����ļĴ���ֵ���ӳ���Ӧʱ����ļ������ں��������Ӧʱ��״̬��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_ADDR(base) ((base) + (0x0134))

/* �Ĵ���˵�������踴λʹ�ܼĴ���������ʹ�����踴λ���Ա���д1����ӦIP���븴λ״̬��д0��Ӱ�츴λ״̬��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_ADDR(base) ((base) + (0x0150))

/* �Ĵ���˵�������踴λ��ֹ�Ĵ��������ڽ�ֹ���踴λ���Ա���д1����Ӧ��������λ��д0��Ӱ�츴λʹ�ܵ�״̬��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_ADDR(base) ((base) + (0x0154))

/* �Ĵ���˵�������踴λ״̬�Ĵ���6�����ڻض������踴λ��״̬�����踴λ�����ź��辭��ͬ��������ˣ�����ļĴ���ֵ���ӳ���Ӧʱ����ļ������ں��������Ӧ�⸴λ״̬��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_ADDR(base) ((base) + (0x0158))

/* �Ĵ���˵����BBP��λʹ�ܼĴ���������ʹ�����踴λ���Ա���д1����ӦIP���븴λ״̬��д0��Ӱ�츴λ״̬��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_ADDR(base)   ((base) + (0x0170))

/* �Ĵ���˵����BBP��λ��ֹ�Ĵ��������ڽ�ֹ���踴λ���Ա���д1����Ӧ��������λ��д0��Ӱ�츴λʹ�ܵ�״̬��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_ADDR(base)  ((base) + (0x0174))

/* �Ĵ���˵����BBP��λ״̬�Ĵ��������ڻض������踴λ��״̬�����踴λ�����ź��辭��ͬ��������ˣ�����ļĴ���ֵ���ӳ���Ӧʱ����ļ������ں��������Ӧ�⸴λ״̬��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_ADDR(base) ((base) + (0x0178))

/* �Ĵ���˵����BBP��λʹ�ܼĴ���1������ʹ�����踴λ���Ա���д1����ӦIP���븴λ״̬��д0��Ӱ�츴λ״̬��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_ADDR(base)   ((base) + (0x017C))

/* �Ĵ���˵����BBP��λ��ֹ�Ĵ���1�����ڽ�ֹ���踴λ���Ա���д1����Ӧ��������λ��д0��Ӱ�츴λʹ�ܵ�״̬��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_ADDR(base)  ((base) + (0x0180))

/* �Ĵ���˵����BBP��λ״̬�Ĵ���1�����ڻض������踴λ��״̬�����踴λ�����ź��辭��ͬ��������ˣ�����ļĴ���ֵ���ӳ���Ӧʱ����ļ������ں��������Ӧ�⸴λ״̬��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_ADDR(base) ((base) + (0x0184))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_EN_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_EN_ADDR(base) ((base) + (0x01E0))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATRAW_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATRAW_ADDR(base) ((base) + (0x01E4))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATMSK_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATMSK_ADDR(base) ((base) + (0x01E8))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_ADDR(base) ((base) + (0x01F0))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_ADDR(base) ((base) + (0x01F4))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_ADDR(base) ((base) + (0x01F8))

/* �Ĵ���˵����ϵͳ�����ж�ʹ�ܼĴ��������ڶ�ϵͳ�����жϽ����������á���ӦbitΪ1��ʾʹ����Ӧ�жϣ�Ϊ0��ʾ�����жϡ�
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_ADDR(base) ((base) + (0x0200))

/* �Ĵ���˵����ϵͳ�����ж��жϼĴ���������ָʾϵͳ����ԭʼ�ж�״̬������ǰ������ӦbitΪ1��ʾ���жϣ�Ϊ0��ʾ���жϡ�
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_ADDR(base) ((base) + (0x0204))

/* �Ĵ���˵����ϵͳ�����ж����κ�Ĵ���������ָʾϵͳ�����ж�״̬�����κ󣩡���ӦbitΪ1��ʾ���жϣ�Ϊ0��ʾ���жϡ�
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_ADDR(base) ((base) + (0x0208))

/* �Ĵ���˵����ccpu�����ж��͸�mcu���ж�ʹ�ܼĴ���0�����ڶ�mcu�Ļ����жϽ����������á���ӦbitΪ1��ʾʹ����Ӧ�жϣ�Ϊ0��ʾ�����жϡ�
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ADDR(base) ((base) + (0x020C))

/* �Ĵ���˵����mcpu�����ж��͸�mcu��ԭʼ�����жϼĴ���������ָʾmcu��ԭʼ�����ж�״̬������ǰ������ӦbitΪ1��ʾ���жϣ�Ϊ0��ʾ���жϡ�
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ADDR(base) ((base) + (0x0210))

/* �Ĵ���˵����mcpu�����ж��͸�mcu�����κ����жϼĴ���������ָʾmcu�ĵ�ǰ�����ж�״̬�����κ󣩡���ӦbitΪ1��ʾ���жϣ�Ϊ0��ʾ���жϡ�
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ADDR(base) ((base) + (0x0214))

/* �Ĵ���˵����mcpu�����ж��͸�mcu�Ļ����ж�ʹ�ܼĴ��������ڶ�mcu�Ļ����жϽ����������á���ӦbitΪ1��ʾʹ����Ӧ�жϣ�Ϊ0��ʾ�����жϡ�
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ADDR(base) ((base) + (0x0218))

/* �Ĵ���˵����mcpu�����ж��͸�mcu��ԭʼ�����жϼĴ���������ָʾmcu��ԭʼ�����ж�״̬������ǰ����
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ADDR(base) ((base) + (0x021C))

/* �Ĵ���˵����mcpu�����ж��͸�mcu�����κ����жϼĴ���������ָʾmcu�ĵ�ǰ�����ж�״̬�����κ󣩡�
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ADDR(base) ((base) + (0x0220))

/* �Ĵ���˵����ԭʼ�ڲ��жϼĴ���������ָʾSC�ڲ���ԭʼ�ж�״̬(����ǰ)����ӦbitΪ1��ʾ���жϣ�Ϊ0��ʾ���ж�
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_INT_RAW_STAT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_INT_RAW_STAT_ADDR(base) ((base) + (0x0224))

/* �Ĵ���˵�������κ��ڲ��жϼĴ���������ָʾSC��ǰ�ڲ��ж�״̬(���κ�)����ӦbitΪ1��ʾ���жϣ�Ϊ0��ʾ���ж�
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_INT_MASK_STAT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_INT_MASK_STAT_ADDR(base) ((base) + (0x0228))

/* �Ĵ���˵�����ڲ��ж�����Ĵ���������Ӧ�жϱ���λд1����ʾ�����Ӧ���ж�״̬������ԭʼ�ڲ��жϼĴ��������κ��ڲ��жϼĴ���
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_INT_CLEAR_UNION */
#define SOC_MODEM_SCTRL_MDMSC_INT_CLEAR_ADDR(base)    ((base) + (0x022C))

/* �Ĵ���˵�����ڲ��ж����μĴ������Ա���д1�������Σ�д0��Ӱ�����ε�״̬
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_INT_EN_UNION */
#define SOC_MODEM_SCTRL_MDMSC_INT_EN_ADDR(base)       ((base) + (0x0230))

/* �Ĵ���˵�����ڲ��ж����μĴ������Ա���д1����ֹ���Σ�д0��Ӱ��ʱ�����ε�״̬
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_INT_DIS_UNION */
#define SOC_MODEM_SCTRL_MDMSC_INT_DIS_ADDR(base)      ((base) + (0x0234))

/* �Ĵ���˵�����ڲ��ж�ʹ�ܼĴ���������SC�ڲ��жϵ��������á���ӦbitΪ1��ʾʹ����Ӧ�жϣ�Ϊ0��ʾ�����ж�
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_INT_EN_STAT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_INT_EN_STAT_ADDR(base)  ((base) + (0x0238))

/* �Ĵ���˵�����жϼ���ʹ�ܼĴ������������ʹ��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_ADDR(base) ((base) + (0x0250))

/* �Ĵ���˵�����жϼ���ʹ�ܼĴ������������ʹ��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_ADDR(base) ((base) + (0x0254))

/* �Ĵ���˵�����жϼ���״̬�Ĵ���0������������ԡ�
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_ADDR(base) ((base) + (0x0258))

/* �Ĵ���˵�����жϼ���״̬�Ĵ���1������������ԡ�
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_ADDR(base) ((base) + (0x025C))

/* �Ĵ���˵�����жϼ���״̬�Ĵ���2������������ԡ�
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_UNION */
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_ADDR(base) ((base) + (0x0260))

/* �Ĵ���˵�����жϼ���״̬�Ĵ���3������������ԡ�
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_UNION */
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_ADDR(base) ((base) + (0x0264))

/* �Ĵ���˵�����жϼ���״̬�Ĵ���4������������ԡ�
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_UNION */
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_ADDR(base) ((base) + (0x0268))

/* �Ĵ���˵�����жϼ���״̬�Ĵ���5������������ԡ�
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_UNION */
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_ADDR(base) ((base) + (0x026C))

/* �Ĵ���˵����BBP ��˫TCXOʱ��ѡ�����
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_BBPCLK_SEL_CTRL_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBPCLK_SEL_CTRL_ADDR(base) ((base) + (0x0270))

/* �Ĵ���˵����BBE16 debug reset����
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_BBE16_DEBUG_RSTCTRL_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEBUG_RSTCTRL_ADDR(base) ((base) + (0x0274))

/* �Ĵ���˵����timerʹ�ܼĴ���0��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_ADDR(base)    ((base) + (0x02A0))

/* �Ĵ���˵����timerʹ�ܼĴ���1��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_ADDR(base)    ((base) + (0x02A4))

/* �Ĵ���˵����timerʹ�ܼĴ���2��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_UNION */
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_ADDR(base)    ((base) + (0x02A8))

/* �Ĵ���˵����Modem��ϵͳ�Զ���CCPU remap�ߴ��ϱ�����
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL4_UNION */
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL4_ADDR(base) ((base) + (0x02AC))

/* �Ĵ���˵����Modem��ϵͳ�Զ���CCPU remap״̬�ϱ�
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL_RPT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL_RPT_ADDR(base) ((base) + (0x02B0))

/* �Ĵ���˵����Modem��ϵͳ�Զ���CCPU�� remap SRAM��ַ���üĴ���
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL3_UNION */
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL3_ADDR(base) ((base) + (0x02B4))

/* �Ĵ���˵����Modem��ϵͳ�Զ���CCPU����remapʹ�����üĴ���
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL2_UNION */
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL2_ADDR(base) ((base) + (0x02B8))

/* �Ĵ���˵����Modem��ϵͳ�Զ���CCPU���ܿ���remap ����ַ
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL0_ADDR(base) ((base) + (0x02BC))

/* �Ĵ���˵����Modem��ϵͳ�Զ���CCPU���ܿ��ƣ�debug���
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL1_ADDR(base) ((base) + (0x02C0))

/* �Ĵ���˵����ALWAYSON������ϵͳ���ƼĴ��������ܰ���SCI���ơ�NOC Timeout���ơ�TCXO AFC������ơ�modem��sysnoc�ſص�ͶƱ
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_UNION */
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_ADDR(base) ((base) + (0x02C4))

/* �Ĵ���˵����������ƼĴ��������ܰ���UPACC��CICOM��CICOMģʽѡ��DMAC
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_ADDR(base)  ((base) + (0x02C8))

/* �Ĵ���˵��������״̬�Ĵ��������ܰ���CICOM״̬
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_PERIPH_STAT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_STAT_ADDR(base)  ((base) + (0x02CC))

/* �Ĵ���˵����MDM_NOC������Master�豸�����ȼ�����
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_ADDR(base) ((base) + (0x02D0))

/* �Ĵ���˵����MDM_NOC������Master�豸�����ȼ�����
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_ADDR(base) ((base) + (0x02D4))

/* �Ĵ���˵����MDM_NOC������Master�豸�����ȼ�����
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_UNION */
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_ADDR(base) ((base) + (0x02D8))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL3_UNION */
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL3_ADDR(base) ((base) + (0x02DC))

/* �Ĵ���˵����������ƼĴ��������ܰ���mdmsys_ramctrl_s��mdmsys_ramctrl_d1w2r����
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_MEMCTRL_UNION */
#define SOC_MODEM_SCTRL_MDMSC_MEMCTRL_ADDR(base)      ((base) + (0x02E0))

/* �Ĵ���˵����BBE16���üĴ��������ܰ���BBE16��trace��notrace memory����
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_BBE16_MEMCTRL_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBE16_MEMCTRL_ADDR(base) ((base) + (0x02E4))

/* �Ĵ���˵����Modem��ϵͳ�Զ���BBE16�Ŀ��ơ����ܰ���BBE16��ַ��������ָʾ,BBE16���������µ�����BBE16ʱ�����͹���ʹ��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_ADDR(base) ((base) + (0x02E8))

/* �Ĵ���˵����BBE16 TCM ��BBE16���ⲿ����ѡ���ź�
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_ADDR(base) ((base) + (0x02EC))

/* �Ĵ���˵����BBE16���ƼĴ��������ܰ���LTE�������ȼ���LTEDSP����
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL0_ADDR(base)  ((base) + (0x02F0))

/* �Ĵ���˵����BBP��ϵͳ���ƼĴ��������ܰ���LTEDSP NMI�ж�����
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL1_ADDR(base)  ((base) + (0x02F4))

/* �Ĵ���˵����BBE16״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_BBE16_STAT0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBE16_STAT0_ADDR(base)  ((base) + (0x02F8))

/* �Ĵ���˵����BBP��ϵͳ״̬�Ĵ��������ܰ���LTEDSP״̬
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_BBE16_STAT1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBE16_STAT1_ADDR(base)  ((base) + (0x02FC))

/* �Ĵ���˵����BBE16 ����DDR������ַ�����ã���ַ���þ���Ϊ1M
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_BBE16_DDRADDR_PROT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DDRADDR_PROT_ADDR(base) ((base) + (0x0300))

/* �Ĵ���˵����MDMNOC power domain ���ƼĴ���
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_CTRL_UNION */
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_CTRL_ADDR(base) ((base) + (0x0304))

/* �Ĵ���˵����MDMNOC power domain�ϱ��Ĵ���
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_RPT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_RPT_ADDR(base) ((base) + (0x0308))

/* �Ĵ���˵����MDM_NOC������Master�豸�����ȼ�����
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_UNION */
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_ADDR(base) ((base) + (0x030C))

/* �Ĵ���˵����BBP���ƼĴ��������ܰ���BBP Local���߿���
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_BBP_LBUS_CTRL_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBP_LBUS_CTRL_ADDR(base) ((base) + (0x0310))

/* �Ĵ���˵����CCPU�����ֲ�AXI����״̬�ϱ�
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_CCPU_LAXI_STAT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_CCPU_LAXI_STAT_ADDR(base) ((base) + (0x0314))

/* �Ĵ���˵����BBE16�����ֲ�AXI����״̬�ϱ�
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_BBE16_LAXI_STAT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBE16_LAXI_STAT_ADDR(base) ((base) + (0x0318))

/* �Ĵ���˵����MDM_NOC���ߵ͹�������ģʽ����
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_NOC_LPOWER_CFG_UNION */
#define SOC_MODEM_SCTRL_MDMSC_NOC_LPOWER_CFG_ADDR(base) ((base) + (0x031C))

/* �Ĵ���˵����ʱ�Ӳ������üĴ���0
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG0_ADDR(base)  ((base) + (0x0320))

/* �Ĵ���˵����ʱ�Ӳ������üĴ���1
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG1_ADDR(base)  ((base) + (0x0324))

/* �Ĵ���˵����ʱ�Ӳ������üĴ���2
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG2_UNION */
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG2_ADDR(base)  ((base) + (0x0328))

/* �Ĵ���˵������������Դ�ȶ�������1������ָʾ����������Դ�������ѹ�ȶ������ʱ�䡣�üĴ���ֻ���ϵ縴λʱ����λ��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_PWUP_TIME0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PWUP_TIME0_ADDR(base)   ((base) + (0x0330))

/* �Ĵ���˵������������Դ�ȶ�������1������ָʾ����������Դ�������ѹ�ȶ������ʱ�䡣�üĴ���ֻ���ϵ縴λʱ����λ��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_PWUP_TIME1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PWUP_TIME1_ADDR(base)   ((base) + (0x0334))

/* �Ĵ���˵����BBE16�����µ��SRAM��ַ���ƼĴ�����
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_BBEPWDN_SRAM_CTRL_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBEPWDN_SRAM_CTRL_ADDR(base) ((base) + (0x0340))

/* �Ĵ���˵����BBE16����DDRԽ�籣����ӳ���ֵַ���üĴ���
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_BBE16_OVERADDR_PROT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBE16_OVERADDR_PROT_ADDR(base) ((base) + (0x0344))

/* �Ĵ���˵����slicer count0
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT0_ADDR(base) ((base) + (0x0350))

/* �Ĵ���˵����slicer count1
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT1_ADDR(base) ((base) + (0x0354))

/* �Ĵ���˵����slicer count2
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT2_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT2_ADDR(base) ((base) + (0x0358))

/* �Ĵ���˵����slicer count3
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT3_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT3_ADDR(base) ((base) + (0x035C))

/* �Ĵ���˵����slicer count4
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT4_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT4_ADDR(base) ((base) + (0x0360))

/* �Ĵ���˵����slicer count5
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT5_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT5_ADDR(base) ((base) + (0x0364))

/* �Ĵ���˵����slicer count6
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT6_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT6_ADDR(base) ((base) + (0x0368))

/* �Ĵ���˵����slicer count7
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT7_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT7_ADDR(base) ((base) + (0x036C))

/* �Ĵ���˵����WBBPID�Ĵ�����
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_WBBPID_UNION */
#define SOC_MODEM_SCTRL_MDMSC_WBBPID_ADDR(base)       ((base) + (0x0380))

/* �Ĵ���˵����GBBPID�Ĵ�����
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_GBBPID_UNION */
#define SOC_MODEM_SCTRL_MDMSC_GBBPID_ADDR(base)       ((base) + (0x0384))

/* �Ĵ���˵����BBP��ά�ɲ������������
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_LTEBBP_DRX_TIMER0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_LTEBBP_DRX_TIMER0_ADDR(base) ((base) + (0x0388))

/* �Ĵ���˵����BBP��ά�ɲ������������
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_LTEBBP_DRX_TIMER1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_LTEBBP_DRX_TIMER1_ADDR(base) ((base) + (0x038C))

/* �Ĵ���˵����Modem �汾�Ĵ���
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_SOC_VERSION_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SOC_VERSION_ADDR(base)  ((base) + (0x0394))

/* �Ĵ���˵���������Ĵ������ṩ������Ի����ʹ�á��Ĵ�����ֵ��ϵͳ��λ
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_RESERVED01_UNION */
#define SOC_MODEM_SCTRL_MDMSC_RESERVED01_ADDR(base)   ((base) + (0x0398))

/* �Ĵ���˵���������Ĵ������ṩ������Ի����ʹ�á��Ĵ�����ֵ��ϵͳ��λ
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_RESERVED02_UNION */
#define SOC_MODEM_SCTRL_MDMSC_RESERVED02_ADDR(base)   ((base) + (0x039C))

/* �Ĵ���˵���������ϱ��Ĵ������ṩоƬECOʹ�á�
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_RESERVED03_UNION */
#define SOC_MODEM_SCTRL_MDMSC_RESERVED03_ADDR(base)   ((base) + (0x03A0))

/* �Ĵ���˵���������Ĵ������ṩ������Ի����ʹ�á��Ĵ�����ֵ����ϵͳ��λ
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_RESERVED04_UNION */
#define SOC_MODEM_SCTRL_MDMSC_RESERVED04_ADDR(base)   ((base) + (0x03A4))

/* �Ĵ���˵���������Ĵ������ṩ������Ի����ʹ�á��Ĵ�����ֵ����ϵͳ��λ
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_RESERVED05_UNION */
#define SOC_MODEM_SCTRL_MDMSC_RESERVED05_ADDR(base)   ((base) + (0x03A8))

/* �Ĵ���˵���������Ĵ������ṩ������Ի����ʹ�á��Ĵ�����ֵ����ϵͳ��λ
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_RESERVED06_UNION */
#define SOC_MODEM_SCTRL_MDMSC_RESERVED06_ADDR(base)   ((base) + (0x03AC))

/* �Ĵ���˵����BBP��G/W/C�͸�ARM�Ļ���ָʾ(�˼Ĵ���ֻ����FPGA����)
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_FPGA_BBP_DRX_FLAG_UNION */
#define SOC_MODEM_SCTRL_MDMSC_FPGA_BBP_DRX_FLAG_ADDR(base) ((base) + (0x03B0))

/* �Ĵ���˵����PMU SSI cnt�����ϱ�(������FPGA����)
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_FPGA_PMUSSI_CNT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_FPGA_PMUSSI_CNT_ADDR(base) ((base) + (0x03B4))

/* �Ĵ���˵����Modem��ϵͳModem_SC TESTPIN�ź�ѡ���ź�
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_TESTPIN_SEL_UNION */
#define SOC_MODEM_SCTRL_MDMSC_TESTPIN_SEL_ADDR(base)  ((base) + (0x03B8))

/* �Ĵ���˵����Modem��ϵͳTESTPIN�ź�ѡ���ź�
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MODEM_TESTPIN_SEL_UNION */
#define SOC_MODEM_SCTRL_MODEM_TESTPIN_SEL_ADDR(base)  ((base) + (0x03BC))

/* �Ĵ���˵����BBIT MODEM��ϵͳȫ�ָ�λʹ�ܼĴ���������ʹ�����踴λ���Ա���д1����ӦIP���븴λ״̬��д0��Ӱ�츴λ״̬��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTEN_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTEN_ADDR(base) ((base) + (0x03D0))

/* �Ĵ���˵����BBIT MODEM��ϵͳȫ�ָ�λ��ֹ�Ĵ��������ڽ�ֹ���踴λ���Ա���д1����Ӧ��������λ��д0��Ӱ�츴λʹ�ܵ�״̬��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTDIS_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTDIS_ADDR(base) ((base) + (0x03D4))

/* �Ĵ���˵����BBIT MODEM��ϵͳȫ�ָ�λ״̬�Ĵ��������ڻض������踴λ��״̬�����踴λ�����ź��辭��ͬ��������ˣ�����ļĴ���ֵ���ӳ���Ӧʱ����ļ������ں��������Ӧ�⸴λ״̬��
   λ����UNION�ṹ:  SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTEN_STAT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTEN_STAT_ADDR(base) ((base) + (0x03D8))





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
                     (1/1) cpu_if_mdm_sc_auto
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_UNION
 �ṹ˵��  : MDMSC_AO_CLKEN �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ϵ���ʱ��ʹ�ܼĴ���������ʹ������ʱ�ӡ��Ա���д1��ʹ�ܶ�Ӧ��ʱ�ӣ�д0��Ӱ��ʱ��ʹ�ܵ�״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ao_peri_clken_sci0_pclk         : 1;  /* bit[0]    : [0] : SCI0 ����ʱ�� */
        unsigned int  ao_peri_clken_sci1_pclk         : 1;  /* bit[1]    : [1] : SCI1 ����ʱ�� */
        unsigned int  ao_peri_clken_modem_timer0_pclk : 1;  /* bit[2]    : [2] : Modem�� Timer0 ����ʱ�� */
        unsigned int  ao_peri_clken_modem_timer1_pclk : 1;  /* bit[3]    : [3] : Modem�� Timer1 ����ʱ�� */
        unsigned int  ao_peri_clken_modem_timer2_pclk : 1;  /* bit[4]    : [4] : Modem�� Timer2 ����ʱ�� */
        unsigned int  ao_peri_clken_modem_timer3_pclk : 1;  /* bit[5]    : [5] : Modem�� Timer3 ����ʱ�� */
        unsigned int  ao_peri_clken_modem_timer4_pclk : 1;  /* bit[6]    : [6] : Modem�� Timer4 ����ʱ�� */
        unsigned int  ao_peri_clken_modem_timer5_pclk : 1;  /* bit[7]    : [7] : Modem�� Timer5 ����ʱ�� */
        unsigned int  ao_peri_clken_modem_timer6_pclk : 1;  /* bit[8]    : [8] : Modem�� Timer6 ����ʱ�� */
        unsigned int  ao_peri_clken_modem_timer7_pclk : 1;  /* bit[9]    : [9] : Modem�� Timer7 ����ʱ�� */
        unsigned int  ao_peri_clken_modem_timer8_pclk : 1;  /* bit[10]   : [10] : Modem�� Timer8 ����ʱ�� */
        unsigned int  ao_peri_clken_modem_timer9_pclk : 1;  /* bit[11]   : [11] : Modem�� Timer9 ����ʱ�� */
        unsigned int  ao_peri_clken_watchdog0_pclk    : 1;  /* bit[12]   : [12] : ccpu Watchdog ����ʱ�� */
        unsigned int  ao_peri_clken_watchdog1_pclk    : 1;  /* bit[13]   : [13]: bbe16 Watchdog ����ʱ�� */
        unsigned int  ao_peri_clken_apb_bbp_on        : 1;  /* bit[14]   : [14] : BBP�ϵ���APB�ӿ�ʱ�� */
        unsigned int  ao_peri_clken_19m_bbp_on        : 1;  /* bit[15]   : [15] : BBP�ϵ���tcxoʱ�� */
        unsigned int  reserved_0                      : 1;  /* bit[16]   : reserved */
        unsigned int  ao_peri_clken_104m_gbbp1_on     : 1;  /* bit[17]   : [17]:bbp�ϵ���GUʱ��clk_104m_gbbp1_on */
        unsigned int  reserved_1                      : 1;  /* bit[18]   : reserved */
        unsigned int  reserved_2                      : 1;  /* bit[19]   : reserved */
        unsigned int  ao_peri_clken_104m_gbbp2_on     : 1;  /* bit[20]   : [20]:bbp�ϵ���GUʱ��clk_104m_gbbp2_on */
        unsigned int  reserved_3                      : 11; /* bit[21-31]: ʱ��ʹ�ܶ������£�д1ʱ�Ӵ򿪣��� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_sci0_pclk_START          (0)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_sci0_pclk_END            (0)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_sci1_pclk_START          (1)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_sci1_pclk_END            (1)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer0_pclk_START  (2)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer0_pclk_END    (2)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer1_pclk_START  (3)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer1_pclk_END    (3)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer2_pclk_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer2_pclk_END    (4)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer3_pclk_START  (5)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer3_pclk_END    (5)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer4_pclk_START  (6)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer4_pclk_END    (6)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer5_pclk_START  (7)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer5_pclk_END    (7)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer6_pclk_START  (8)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer6_pclk_END    (8)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer7_pclk_START  (9)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer7_pclk_END    (9)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer8_pclk_START  (10)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer8_pclk_END    (10)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer9_pclk_START  (11)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer9_pclk_END    (11)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_watchdog0_pclk_START     (12)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_watchdog0_pclk_END       (12)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_watchdog1_pclk_START     (13)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_watchdog1_pclk_END       (13)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_apb_bbp_on_START         (14)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_apb_bbp_on_END           (14)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_19m_bbp_on_START         (15)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_19m_bbp_on_END           (15)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_104m_gbbp1_on_START      (17)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_104m_gbbp1_on_END        (17)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_104m_gbbp2_on_START      (20)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_104m_gbbp2_on_END        (20)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_UNION
 �ṹ˵��  : MDMSC_AO_CLKDIS �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ϵ���ʱ�ӽ�ֹ�Ĵ��������ڽ�ֹ����ʱ�ӡ��Ա���д1����ֹ��Ӧ��ʱ�ӣ�д0��Ӱ��ʱ��ʹ�ܵ�״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ao_peri_clkdis_sci0_pclk         : 1;  /* bit[0]    : [0] : SCI0 ����ʱ�� */
        unsigned int  ao_peri_clkdis_sci1_pclk         : 1;  /* bit[1]    : [1] : SCI1 ����ʱ�� */
        unsigned int  ao_peri_clkdis_modem_timer0_pclk : 1;  /* bit[2]    : [2] : Modem�� Timer0 ����ʱ�� */
        unsigned int  ao_peri_clkdis_modem_timer1_pclk : 1;  /* bit[3]    : [3] : Modem�� Timer1 ����ʱ�� */
        unsigned int  ao_peri_clkdis_modem_timer2_pclk : 1;  /* bit[4]    : [4] : Modem�� Timer2 ����ʱ�� */
        unsigned int  ao_peri_clkdis_modem_timer3_pclk : 1;  /* bit[5]    : [5] : Modem�� Timer3 ����ʱ�� */
        unsigned int  ao_peri_clkdis_modem_timer4_pclk : 1;  /* bit[6]    : [6] : Modem�� Timer4 ����ʱ�� */
        unsigned int  ao_peri_clkdis_modem_timer5_pclk : 1;  /* bit[7]    : [7] : Modem�� Timer5 ����ʱ�� */
        unsigned int  ao_peri_clkdis_modem_timer6_pclk : 1;  /* bit[8]    : [8] : Modem�� Timer6 ����ʱ�� */
        unsigned int  ao_peri_clkdis_modem_timer7_pclk : 1;  /* bit[9]    : [9] : Modem�� Timer7 ����ʱ�� */
        unsigned int  ao_peri_clkdis_modem_timer8_pclk : 1;  /* bit[10]   : [10] : Modem�� Timer8 ����ʱ�� */
        unsigned int  ao_peri_clkdis_modem_timer9_pclk : 1;  /* bit[11]   : [11] : Modem�� Timer9 ����ʱ�� */
        unsigned int  ao_peri_clkdis_watchdog0_pclk    : 1;  /* bit[12]   : [12] : ccpu Watchdog ����ʱ�� */
        unsigned int  ao_peri_clkdis_watchdog1_pclk    : 1;  /* bit[13]   : [13]: bbe16 Watchdog ����ʱ�� */
        unsigned int  ao_peri_clkdis_apb_bbp_on        : 1;  /* bit[14]   : [14] : BBP�ϵ���APB�ӿ�ʱ�� */
        unsigned int  ao_peri_clkdis_19m_bbp_on        : 1;  /* bit[15]   : [15] : BBP�ϵ���tcxoʱ�� */
        unsigned int  reserved_0                       : 1;  /* bit[16]   : reserved */
        unsigned int  ao_peri_clkdis_104m_gbbp1_on     : 1;  /* bit[17]   : [17]:bbp�ϵ���GUʱ��clk_104m_gbbp1_on */
        unsigned int  reserved_1                       : 1;  /* bit[18]   : reserved */
        unsigned int  reserved_2                       : 1;  /* bit[19]   : reserved */
        unsigned int  ao_peri_clkdis_104m_gbbp2_on     : 1;  /* bit[20]   : [20]:bbp�ϵ���GUʱ��clk_104m_gbbp2_on */
        unsigned int  reserved_3                       : 11; /* bit[21-31]: ʱ�ӽ�ֹ�������£�д1ʱ�ӹرգ���  */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_sci0_pclk_START          (0)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_sci0_pclk_END            (0)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_sci1_pclk_START          (1)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_sci1_pclk_END            (1)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer0_pclk_START  (2)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer0_pclk_END    (2)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer1_pclk_START  (3)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer1_pclk_END    (3)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer2_pclk_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer2_pclk_END    (4)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer3_pclk_START  (5)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer3_pclk_END    (5)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer4_pclk_START  (6)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer4_pclk_END    (6)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer5_pclk_START  (7)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer5_pclk_END    (7)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer6_pclk_START  (8)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer6_pclk_END    (8)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer7_pclk_START  (9)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer7_pclk_END    (9)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer8_pclk_START  (10)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer8_pclk_END    (10)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer9_pclk_START  (11)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer9_pclk_END    (11)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_watchdog0_pclk_START     (12)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_watchdog0_pclk_END       (12)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_watchdog1_pclk_START     (13)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_watchdog1_pclk_END       (13)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_apb_bbp_on_START         (14)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_apb_bbp_on_END           (14)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_19m_bbp_on_START         (15)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_19m_bbp_on_END           (15)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_104m_gbbp1_on_START      (17)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_104m_gbbp1_on_END        (17)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_104m_gbbp2_on_START      (20)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_104m_gbbp2_on_END        (20)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_UNION
 �ṹ˵��  : MDMSC_AO_CLKEN_STAT �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ϵ���ʱ��״̬�Ĵ��������ڻض�������ʱ�ӵ�״̬������ʱ�ӿ����ź��辭����CRG�н���ͬ��������ˣ�����ļĴ���ֵ���ӳ���Ӧʱ����ļ������ں��������Ӧʱ��״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ao_peri_clken_stat_sci0_pclk         : 1;  /* bit[0]    : [0] : SCI0 ����ʱ�� */
        unsigned int  ao_peri_clken_stat_sci1_pclk         : 1;  /* bit[1]    : [1] : SCI1 ����ʱ�� */
        unsigned int  ao_peri_clken_stat_modem_timer0_pclk : 1;  /* bit[2]    : [2] : Modem�� Timer0 ����ʱ�� */
        unsigned int  ao_peri_clken_stat_modem_timer1_pclk : 1;  /* bit[3]    : [3] : Modem�� Timer1 ����ʱ�� */
        unsigned int  ao_peri_clken_stat_modem_timer2_pclk : 1;  /* bit[4]    : [4] : Modem�� Timer2 ����ʱ�� */
        unsigned int  ao_peri_clken_stat_modem_timer3_pclk : 1;  /* bit[5]    : [5] : Modem�� Timer3 ����ʱ�� */
        unsigned int  ao_peri_clken_stat_modem_timer4_pclk : 1;  /* bit[6]    : [6] : Modem�� Timer4 ����ʱ�� */
        unsigned int  ao_peri_clken_stat_modem_timer5_pclk : 1;  /* bit[7]    : [7] : Modem�� Timer5 ����ʱ�� */
        unsigned int  ao_peri_clken_stat_modem_timer6_pclk : 1;  /* bit[8]    : [8] : Modem�� Timer6 ����ʱ�� */
        unsigned int  ao_peri_clken_stat_modem_timer7_pclk : 1;  /* bit[9]    : [9] : Modem�� Timer7 ����ʱ�� */
        unsigned int  ao_peri_clken_stat_modem_timer8_pclk : 1;  /* bit[10]   : [10] : Modem�� Timer8 ����ʱ�� */
        unsigned int  ao_peri_clken_stat_modem_timer9_pclk : 1;  /* bit[11]   : [11] : Modem�� Timer9 ����ʱ�� */
        unsigned int  ao_peri_clken_stat_watchdog0_pclk    : 1;  /* bit[12]   : [12] : ccpu Watchdog ����ʱ�� */
        unsigned int  ao_peri_clken_stat_watchdog1_pclk    : 1;  /* bit[13]   : [13]: bbe16 Watchdog ����ʱ�� */
        unsigned int  ao_peri_clken_stat_apb_bbp_on        : 1;  /* bit[14]   : [14] : BBP�ϵ���APB�ӿ�ʱ�� */
        unsigned int  ao_peri_clken_stat_19m_bbp_on        : 1;  /* bit[15]   : [15] : BBP�ϵ���tcxoʱ�� */
        unsigned int  reserved_0                           : 1;  /* bit[16]   : reserved */
        unsigned int  ao_peri_clken_stat_104m_gbbp1_on     : 1;  /* bit[17]   : [17]:bbp�ϵ���GUʱ��clk_104m_gbbp1_on */
        unsigned int  reserved_1                           : 1;  /* bit[18]   : reserved */
        unsigned int  reserved_2                           : 1;  /* bit[19]   : reserved */
        unsigned int  ao_peri_clken_stat_104m_gbbp2_on     : 1;  /* bit[20]   : [20]:bbp�ϵ���GUʱ��clk_104m_gbbp2_on */
        unsigned int  reserved_3                           : 11; /* bit[21-31]: ʱ��״̬�������£��ߵ�ƽ��ʾʱ�Ӵ򿪣���  */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_sci0_pclk_START          (0)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_sci0_pclk_END            (0)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_sci1_pclk_START          (1)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_sci1_pclk_END            (1)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer0_pclk_START  (2)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer0_pclk_END    (2)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer1_pclk_START  (3)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer1_pclk_END    (3)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer2_pclk_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer2_pclk_END    (4)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer3_pclk_START  (5)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer3_pclk_END    (5)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer4_pclk_START  (6)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer4_pclk_END    (6)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer5_pclk_START  (7)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer5_pclk_END    (7)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer6_pclk_START  (8)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer6_pclk_END    (8)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer7_pclk_START  (9)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer7_pclk_END    (9)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer8_pclk_START  (10)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer8_pclk_END    (10)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer9_pclk_START  (11)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer9_pclk_END    (11)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_watchdog0_pclk_START     (12)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_watchdog0_pclk_END       (12)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_watchdog1_pclk_START     (13)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_watchdog1_pclk_END       (13)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_apb_bbp_on_START         (14)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_apb_bbp_on_END           (14)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_19m_bbp_on_START         (15)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_19m_bbp_on_END           (15)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_104m_gbbp1_on_START      (17)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_104m_gbbp1_on_END        (17)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_104m_gbbp2_on_START      (20)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_104m_gbbp2_on_END        (20)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_UNION
 �ṹ˵��  : MDMSC_AO_RSTEN �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ϵ�����λʹ�ܼĴ���������ʹ�����踴λ���Ա���д1����ӦIP���븴λ״̬��д0��Ӱ�츴λ״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ao_peri_rsten_sci0                  : 1;  /* bit[0]    : [0] : SCI0����ʱ������λ */
        unsigned int  ao_peri_rsten_sci1                  : 1;  /* bit[1]    : [1] : SCI1����ʱ������λ */
        unsigned int  reserved_0                          : 12; /* bit[2-13] : reserved */
        unsigned int  ao_peri_rsten_reset_apb_bbp_on_n    : 1;  /* bit[14]   : [14] :BBP�ϵ�����λ reset_apb_bbp_on_n */
        unsigned int  ao_peri_rsten_reset_19m_bbp_on_n    : 1;  /* bit[15]   : [15] : BBP�ϵ�����λreset_19m_bbp_on_n */
        unsigned int  ao_peri_rsten_reset_32k_bbp_on_n    : 1;  /* bit[16]   : [16] :BBP�ϵ�����λ reset_32k_bbp_on_n */
        unsigned int  ao_peri_rsten_reset_104m_gbbp1_on_n : 1;  /* bit[17]   : [17] : BBP�ϵ�����λreset_104m_gbbp1_on_n */
        unsigned int  reserved_1                          : 1;  /* bit[18]   : reserved */
        unsigned int  reserved_2                          : 1;  /* bit[19]   : reserved */
        unsigned int  ao_peri_rsten_reset_104m_gbbp2_on_n : 1;  /* bit[20]   : [20] : BBP�ϵ�����λreset_104m_gbbp2_on_n */
        unsigned int  reserved_3                          : 11; /* bit[21-31]: ��λʹ�ܶ������£�д1��λʹ�ܣ���
                                                                               [31:21] : Reserved */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_ao_peri_rsten_sci0_START                   (0)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_ao_peri_rsten_sci0_END                     (0)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_ao_peri_rsten_sci1_START                   (1)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_ao_peri_rsten_sci1_END                     (1)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_ao_peri_rsten_reset_apb_bbp_on_n_START     (14)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_ao_peri_rsten_reset_apb_bbp_on_n_END       (14)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_ao_peri_rsten_reset_19m_bbp_on_n_START     (15)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_ao_peri_rsten_reset_19m_bbp_on_n_END       (15)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_ao_peri_rsten_reset_32k_bbp_on_n_START     (16)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_ao_peri_rsten_reset_32k_bbp_on_n_END       (16)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_ao_peri_rsten_reset_104m_gbbp1_on_n_START  (17)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_ao_peri_rsten_reset_104m_gbbp1_on_n_END    (17)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_ao_peri_rsten_reset_104m_gbbp2_on_n_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_ao_peri_rsten_reset_104m_gbbp2_on_n_END    (20)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_UNION
 �ṹ˵��  : MDMSC_AO_RSTDIS �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ϵ�����λ��ֹ�Ĵ��������ڽ�ֹ���踴λ���Ա���д1����Ӧ��������λ��д0��Ӱ�츴λʹ�ܵ�״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ao_peri_rstdis_sci0                  : 1;  /* bit[0]    : [0] : SCI0����ʱ������λ */
        unsigned int  ao_peri_rstdis_sci1                  : 1;  /* bit[1]    : [1] : SCI1����ʱ������λ */
        unsigned int  reserved_0                           : 12; /* bit[2-13] : reserved */
        unsigned int  ao_peri_rstdis_reset_apb_bbp_on_n    : 1;  /* bit[14]   : [14] :BBP�ϵ�����λ reset_apb_bbp_on_n */
        unsigned int  ao_peri_rstdis_reset_19m_bbp_on_n    : 1;  /* bit[15]   : [15] : BBP�ϵ�����λreset_19m_bbp_on_n */
        unsigned int  ao_peri_rstdis_reset_32k_bbp_on_n    : 1;  /* bit[16]   : [16] :BBP�ϵ�����λ reset_32k_bbp_on_n */
        unsigned int  ao_peri_rstdis_reset_104m_gbbp1_on_n : 1;  /* bit[17]   : [17] : BBP�ϵ�����λreset_104m_gbbp1_on_n */
        unsigned int  reserved_1                           : 1;  /* bit[18]   : reserved */
        unsigned int  reserved_2                           : 1;  /* bit[19]   : reserved */
        unsigned int  ao_peri_rstdis_reset_104m_gbbp2_on_n : 1;  /* bit[20]   : [20] : BBP�ϵ�����λreset_104m_gbbp2_on_n */
        unsigned int  reserved_3                           : 11; /* bit[21-31]: ��λ��ֹ�������£�д1��λ�������
                                                                                [31:21] : Reserved */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_ao_peri_rstdis_sci0_START                   (0)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_ao_peri_rstdis_sci0_END                     (0)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_ao_peri_rstdis_sci1_START                   (1)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_ao_peri_rstdis_sci1_END                     (1)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_ao_peri_rstdis_reset_apb_bbp_on_n_START     (14)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_ao_peri_rstdis_reset_apb_bbp_on_n_END       (14)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_ao_peri_rstdis_reset_19m_bbp_on_n_START     (15)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_ao_peri_rstdis_reset_19m_bbp_on_n_END       (15)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_ao_peri_rstdis_reset_32k_bbp_on_n_START     (16)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_ao_peri_rstdis_reset_32k_bbp_on_n_END       (16)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_ao_peri_rstdis_reset_104m_gbbp1_on_n_START  (17)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_ao_peri_rstdis_reset_104m_gbbp1_on_n_END    (17)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_ao_peri_rstdis_reset_104m_gbbp2_on_n_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_ao_peri_rstdis_reset_104m_gbbp2_on_n_END    (20)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_UNION
 �ṹ˵��  : MDMSC_AO_RSTEN_STAT �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: �ϵ�����λ״̬�Ĵ��������ڻض������踴λ��״̬�����踴λ�����ź��辭��ͬ��������ˣ�����ļĴ���ֵ���ӳ���Ӧʱ����ļ������ں��������Ӧ�⸴λ״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ao_peri_rsten_stat_sci0            : 1;  /* bit[0]    : [0] : SCI0����ʱ������λ */
        unsigned int  ao_peri_rsten_stat_sci1            : 1;  /* bit[1]    : [1] : SCI1����ʱ������λ */
        unsigned int  reserved_0                         : 12; /* bit[2-13] : reserved */
        unsigned int  ao_peri_rsten_stat_apb_bbp_on_n    : 1;  /* bit[14]   : [14] :BBP�ϵ�����λ reset_apb_bbp_on_n */
        unsigned int  ao_peri_rsten_stat_19m_bbp_on_n    : 1;  /* bit[15]   : [15] : BBP�ϵ�����λreset_19m_bbp_on_n */
        unsigned int  ao_peri_rsten_stat_32k_bbp_on_n    : 1;  /* bit[16]   : [16] :BBP�ϵ�����λ reset_32k_bbp_on_n */
        unsigned int  ao_peri_rsten_stat_104m_gbbp1_on_n : 1;  /* bit[17]   : [17] : BBP�ϵ�����λreset_104m_gbbp1_on_n */
        unsigned int  reserved_1                         : 1;  /* bit[18]   : reserved */
        unsigned int  reserved_2                         : 1;  /* bit[19]   : reserved */
        unsigned int  ao_peri_rsten_stat_104m_gbbp2_on_n : 1;  /* bit[20]   : [20] : BBP�ϵ�����λreset_104m_gbbp2_on_n */
        unsigned int  reserved_3                         : 11; /* bit[21-31]: ��λ״̬�������£��ߵ�ƽ��ʾ���ڸ�λ��
                                                                              [31:21] : Reserved */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_ao_peri_rsten_stat_sci0_START             (0)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_ao_peri_rsten_stat_sci0_END               (0)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_ao_peri_rsten_stat_sci1_START             (1)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_ao_peri_rsten_stat_sci1_END               (1)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_ao_peri_rsten_stat_apb_bbp_on_n_START     (14)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_ao_peri_rsten_stat_apb_bbp_on_n_END       (14)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_ao_peri_rsten_stat_19m_bbp_on_n_START     (15)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_ao_peri_rsten_stat_19m_bbp_on_n_END       (15)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_ao_peri_rsten_stat_32k_bbp_on_n_START     (16)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_ao_peri_rsten_stat_32k_bbp_on_n_END       (16)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_ao_peri_rsten_stat_104m_gbbp1_on_n_START  (17)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_ao_peri_rsten_stat_104m_gbbp1_on_n_END    (17)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_ao_peri_rsten_stat_104m_gbbp2_on_n_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_ao_peri_rsten_stat_104m_gbbp2_on_n_END    (20)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_UNION
 �ṹ˵��  : MDMSC_PW_CLKEN �Ĵ����ṹ���塣��ַƫ����:0x0040����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������ʱ��ʹ�ܼĴ��������ڿ��Ƹ��������ܵ�ʱ��ʹ�ܡ�����Ӧλд1ʹ����Ӧ��ѹ��ʱ�ӣ�д0��Ӱ�졣�üĴ���ֻ���ϵ縴λʱ����λ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pw_clken_dspbbe : 1;  /* bit[0]   : [0]��DSPBBE�µ��� */
        unsigned int  pw_clken_bbp_cs : 1;  /* bit[1]   : [1]��BBP CS�µ���  */
        unsigned int  pw_clken_lte    : 1;  /* bit[2]   : [2]��LTEBBPTOP�µ���  */
        unsigned int  reserved_0      : 1;  /* bit[3]   : [3]��BBP PS�µ���(��������Harq Mem�����Ƶ�AO_Sctrl��)  */
        unsigned int  reserved_1      : 28; /* bit[4-31]: [31:4]������
                                                            */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_pw_clken_dspbbe_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_pw_clken_dspbbe_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_pw_clken_bbp_cs_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_pw_clken_bbp_cs_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_pw_clken_lte_START     (2)
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_pw_clken_lte_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_PW_CLKDIS_UNION
 �ṹ˵��  : MDMSC_PW_CLKDIS �Ĵ����ṹ���塣��ַƫ����:0x0044����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������ʱ�ӽ�ֹ�Ĵ��������ڿ��Ƹ��������ܵ�ʱ�ӽ�ֹ������Ӧλд1��ֹ��Ӧ������ʱ�ӣ�д0��Ӱ�졣�üĴ���ֻ���ϵ縴λʱ����λ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pw_clkdis_dspbbe : 1;  /* bit[0]   : [0]��DSPBBE�µ��� */
        unsigned int  pw_clkdis_bbp_cs : 1;  /* bit[1]   : [1]��BBP CS�µ���  */
        unsigned int  pw_clkdis_lte    : 1;  /* bit[2]   : [2]��LTEBBPTOP�µ���  */
        unsigned int  reserved_0       : 1;  /* bit[3]   : [3]��BBP PS�µ���  */
        unsigned int  reserved_1       : 28; /* bit[4-31]: [31:4]������ */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PW_CLKDIS_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKDIS_pw_clkdis_dspbbe_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKDIS_pw_clkdis_dspbbe_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKDIS_pw_clkdis_bbp_cs_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKDIS_pw_clkdis_bbp_cs_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKDIS_pw_clkdis_lte_START     (2)
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKDIS_pw_clkdis_lte_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_STAT_UNION
 �ṹ˵��  : MDMSC_PW_CLKEN_STAT �Ĵ����ṹ���塣��ַƫ����:0x0048����ֵ:0x00000000�����:32
 �Ĵ���˵��: �µ���ʱ��״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pw_clken_stat_dspbbe : 1;  /* bit[0]   : [0]��DSPBBE�µ��� */
        unsigned int  pw_clken_stat_bbp_cs : 1;  /* bit[1]   : [1]��BBP CS�µ���  */
        unsigned int  pw_clken_stat_lte    : 1;  /* bit[2]   : [2]��LTEBBPTOP�µ���  */
        unsigned int  reserved_0           : 1;  /* bit[3]   : [3]��BBP PS�µ���(��������Harq Mem�����Ƶ�AO_Sctrl��)  */
        unsigned int  reserved_1           : 28; /* bit[4-31]: 0���رգ�
                                                               1���򿪡�
                                                               [31:4]������  */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_STAT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_STAT_pw_clken_stat_dspbbe_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_STAT_pw_clken_stat_dspbbe_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_STAT_pw_clken_stat_bbp_cs_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_STAT_pw_clken_stat_bbp_cs_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_STAT_pw_clken_stat_lte_START     (2)
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_STAT_pw_clken_stat_lte_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_UNION
 �ṹ˵��  : MDMSC_PW_RSTEN �Ĵ����ṹ���塣��ַƫ����:0x004C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��������λʹ�ܼĴ��������ڿ��Ƹ��������ܵĸ�λʹ�ܡ�����Ӧλд1ʹ����Ӧ��������λ�źţ������븴λ̬����д0��Ӱ�졣�üĴ���ֻ���ϵ縴λʱ����λ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pw_rsten_dspbbe : 1;  /* bit[0]   : [0]��DSPBBE�µ��� */
        unsigned int  pw_rsten_bbp_cs : 1;  /* bit[1]   : [1]��BBP CS�µ���  */
        unsigned int  pw_rsten_lte    : 1;  /* bit[2]   : [2]��LTEBBPTOP�µ���  */
        unsigned int  reserved_0      : 1;  /* bit[3]   : [3]��BBP PS�µ���(��������Harq Mem�����Ƶ�AO_Sctrl��)  */
        unsigned int  reserved_1      : 28; /* bit[4-31]: [31:4]������
                                                            */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_pw_rsten_dspbbe_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_pw_rsten_dspbbe_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_pw_rsten_bbp_cs_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_pw_rsten_bbp_cs_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_pw_rsten_lte_START     (2)
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_pw_rsten_lte_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_PW_RSTDIS_UNION
 �ṹ˵��  : MDMSC_PW_RSTDIS �Ĵ����ṹ���塣��ַƫ����:0x0050����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��������λ��ֹ�Ĵ��������ڿ��Ƹ��������ܵĸ�λ��ֹ������Ӧλд1��ֹ��Ӧ��������λ�źţ����˳���λ̬����д0��Ӱ�졣�üĴ���ֻ���ϵ縴λʱ����λ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pw_rstdis_dspbbe : 1;  /* bit[0]   : [0]��DSPBBE�µ��� */
        unsigned int  pw_rstdis_bbp_cs : 1;  /* bit[1]   : [1]��BBP CS�µ���  */
        unsigned int  pw_rstdis_lte    : 1;  /* bit[2]   : [2]��LTEBBPTOP�µ���  */
        unsigned int  reserved_0       : 1;  /* bit[3]   : [3]��BBP PS�µ���(��������Harq Mem�����Ƶ�AO_Sctrl��)  */
        unsigned int  reserved_1       : 28; /* bit[4-31]: [31:4]������
                                                             */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PW_RSTDIS_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTDIS_pw_rstdis_dspbbe_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTDIS_pw_rstdis_dspbbe_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTDIS_pw_rstdis_bbp_cs_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTDIS_pw_rstdis_bbp_cs_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTDIS_pw_rstdis_lte_START     (2)
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTDIS_pw_rstdis_lte_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_STAT_UNION
 �ṹ˵��  : MDMSC_PW_RSTEN_STAT �Ĵ����ṹ���塣��ַƫ����:0x0054����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: �µ�����λ״̬
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pw_rsten_stat_dspbbe : 1;  /* bit[0]   : [0]��DSPBBE�µ��� */
        unsigned int  pw_rsten_stat_bbp_cs : 1;  /* bit[1]   : [1]��BBP CS�µ���  */
        unsigned int  pw_rsten_stat_lte    : 1;  /* bit[2]   : [2]��LTEBBPTOP�µ���  */
        unsigned int  reserved_0           : 1;  /* bit[3]   : [3]��BBP PS�µ���(��������Harq Mem�����Ƶ�AO_Sctrl��)  */
        unsigned int  reserved_1           : 28; /* bit[4-31]: �µ�����λ״̬��
                                                               [31:4]������
                                                               0����λ��ʹ�ܣ�
                                                               1����λʹ�ܡ� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_STAT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_STAT_pw_rsten_stat_dspbbe_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_STAT_pw_rsten_stat_dspbbe_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_STAT_pw_rsten_stat_bbp_cs_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_STAT_pw_rsten_stat_bbp_cs_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_STAT_pw_rsten_stat_lte_START     (2)
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_STAT_pw_rsten_stat_lte_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_UNION
 �ṹ˵��  : MDMSC_PW_ISOEN �Ĵ����ṹ���塣��ַƫ����:0x0058����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������ISOʹ�ܼĴ��������ڿ��Ƹ���������ص�Isolation Cellʹ�ܡ�����Ӧλд1ʹ����Ӧ������IsoLation Cell�����źŸ��ϣ���д0��Ӱ�졣�üĴ���ֻ���ϵ縴λʱ����λ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pw_isoen_dspbbe : 1;  /* bit[0]   : [0]��DSPBBE�µ��� */
        unsigned int  pw_isoen_bbp_cs : 1;  /* bit[1]   : [1]��BBP CS�µ���(��MTCMOS���룬���ź�����)  */
        unsigned int  pw_isoen_lte    : 1;  /* bit[2]   : [2]��LTEBBPTOP�µ���  */
        unsigned int  reserved_0      : 1;  /* bit[3]   : [3]��BBP PS�µ���(��������Harq Mem�����Ƶ�AO_Sctrl��)  */
        unsigned int  reserved_1      : 28; /* bit[4-31]: [31:4]������
                                                            */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_pw_isoen_dspbbe_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_pw_isoen_dspbbe_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_pw_isoen_bbp_cs_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_pw_isoen_bbp_cs_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_pw_isoen_lte_START     (2)
#define SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_pw_isoen_lte_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_PW_ISODIS_UNION
 �ṹ˵��  : MDMSC_PW_ISODIS �Ĵ����ṹ���塣��ַƫ����:0x005C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������ISO��ֹ�Ĵ��������ڿ��Ƹ���������ص�Isolation Cell��ֹ������Ӧλд1��ֹ��Ӧ������IsoLation Cell�����źŲ����ϣ���д0��Ӱ�졣�üĴ���ֻ���ϵ縴λʱ����λ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pw_isodis_dspbbe : 1;  /* bit[0]   : [0]��DSPBBE�µ��� */
        unsigned int  pw_isodis_bbp_cs : 1;  /* bit[1]   : [1]��BBP CS�µ���(��MTCMOS���룬���ź�����)  */
        unsigned int  pw_isodis_lte    : 1;  /* bit[2]   : [2]��LTEBBPTOP�µ���  */
        unsigned int  reserved_0       : 1;  /* bit[3]   : [3]��BBP PS�µ���(��������Harq Mem�����Ƶ�AO_Sctrl��)  */
        unsigned int  reserved_1       : 28; /* bit[4-31]: [31:4]������
                                                             */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PW_ISODIS_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PW_ISODIS_pw_isodis_dspbbe_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_ISODIS_pw_isodis_dspbbe_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_ISODIS_pw_isodis_bbp_cs_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_ISODIS_pw_isodis_bbp_cs_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_ISODIS_pw_isodis_lte_START     (2)
#define SOC_MODEM_SCTRL_MDMSC_PW_ISODIS_pw_isodis_lte_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_STAT_UNION
 �ṹ˵��  : MDMSC_PW_ISOEN_STAT �Ĵ����ṹ���塣��ַƫ����:0x0060����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: �µ���ISO״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pw_iso_stat_dspbbe : 1;  /* bit[0]   : [0]��DSPBBE�µ��� */
        unsigned int  pw_iso_stat_bbp_cs : 1;  /* bit[1]   : [1]��BBP CS�µ���(��MTCMOS���룬���ź�����)  */
        unsigned int  pw_iso_stat_lte    : 1;  /* bit[2]   : [2]��LTEBBPTOP�µ���  */
        unsigned int  reserved_0         : 1;  /* bit[3]   : [3]��BBP PS�µ���(��������Harq Mem�����Ƶ�AO_Sctrl��)  */
        unsigned int  reserved_1         : 28; /* bit[4-31]: �µ���ISO״̬��[31:4]������
                                                             0��isolation��ʹ�ܣ�
                                                             1��isolationʹ�ܡ� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_STAT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_STAT_pw_iso_stat_dspbbe_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_STAT_pw_iso_stat_dspbbe_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_STAT_pw_iso_stat_bbp_cs_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_STAT_pw_iso_stat_bbp_cs_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_STAT_pw_iso_stat_lte_START     (2)
#define SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_STAT_pw_iso_stat_lte_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSEN_UNION
 �ṹ˵��  : MDMSC_PW_MTCMOSEN �Ĵ����ṹ���塣��ַƫ����:0x0064����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��������Դʹ�ܼĴ��������ڿ��Ƹ��������ĵ�Դʹ�ܣ�����Ӧλд1����Ӧ��ѹ���Դ��д0��Ӱ�졣�üĴ�����ֻ���ϵ縴λʱ����λ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pw_mtcmosen_dspbbe : 1;  /* bit[0]   : [0]��DSPBBE�µ��� */
        unsigned int  pw_mtcmosen_bbp_cs : 1;  /* bit[1]   : [1]��BBP CS�µ���(��MTCMOS���룬���ź�����)  */
        unsigned int  pw_mtcmosen_lte    : 1;  /* bit[2]   : [2]��LTEBBPTOP�µ���  */
        unsigned int  reserved_0         : 1;  /* bit[3]   : [3]��BBP PS�µ���(��������Harq Mem�����Ƶ�AO_Sctrl��)  */
        unsigned int  reserved_1         : 28; /* bit[4-31]: [31:4]������  */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSEN_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSEN_pw_mtcmosen_dspbbe_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSEN_pw_mtcmosen_dspbbe_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSEN_pw_mtcmosen_bbp_cs_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSEN_pw_mtcmosen_bbp_cs_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSEN_pw_mtcmosen_lte_START     (2)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSEN_pw_mtcmosen_lte_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSDIS_UNION
 �ṹ˵��  : MDMSC_PW_MTCMOSDIS �Ĵ����ṹ���塣��ַƫ����:0x0068����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��������Դ��ֹ�Ĵ��������ڿ��Ƹ��������ĵ�Դ��ֹ������Ӧλд1�ر���Ӧ��ѹ���Դ��д0��Ӱ�졣�üĴ�����ֻ���ϵ縴λʱ����λ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pw_mtcmosdis_dspbbe : 1;  /* bit[0]   : [0]��DSPBBE�µ��� */
        unsigned int  pw_mtcmosdis_bbp_cs : 1;  /* bit[1]   : [1]��BBP CS�µ���(��MTCMOS���룬���ź�����)  */
        unsigned int  pw_mtcmosdis_lte    : 1;  /* bit[2]   : [2]��LTEBBPTOP�µ���  */
        unsigned int  reserved_0          : 1;  /* bit[3]   : [3]��BBP PS�µ���(��������Harq Mem�����Ƶ�AO_Sctrl��)  */
        unsigned int  reserved_1          : 28; /* bit[4-31]: reserved */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSDIS_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSDIS_pw_mtcmosdis_dspbbe_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSDIS_pw_mtcmosdis_dspbbe_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSDIS_pw_mtcmosdis_bbp_cs_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSDIS_pw_mtcmosdis_bbp_cs_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSDIS_pw_mtcmosdis_lte_START     (2)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSDIS_pw_mtcmosdis_lte_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_STAT_UNION
 �ṹ˵��  : MDMSC_PW_MTCMOS_STAT �Ĵ����ṹ���塣��ַƫ����:0x006C����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: ��������Դ����״̬
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pw_mtcmos_stat_dspbbe : 1;  /* bit[0]   : [0]��DSPBBE�µ��� */
        unsigned int  pw_mtcmos_stat_bbp_cs : 1;  /* bit[1]   : [1]��BBP CS�µ���(��MTCMOS���룬���ź�����)  */
        unsigned int  pw_mtcmos_stat_lte    : 1;  /* bit[2]   : [2]��LTEBBPTOP�µ���  */
        unsigned int  reserved_0            : 1;  /* bit[3]   : [3]��BBP PS�µ���(��������Harq Mem�����Ƶ�AO_Sctrl��)  */
        unsigned int  reserved_1            : 28; /* bit[4-31]: �µ���MTCMOS״̬��[31:4]������
                                                                1:mtcmos��
                                                                0:mtcmos�ر� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_STAT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_STAT_pw_mtcmos_stat_dspbbe_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_STAT_pw_mtcmos_stat_dspbbe_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_STAT_pw_mtcmos_stat_bbp_cs_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_STAT_pw_mtcmos_stat_bbp_cs_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_STAT_pw_mtcmos_stat_lte_START     (2)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_STAT_pw_mtcmos_stat_lte_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_ACK_SUB_UNION
 �ṹ˵��  : MDMSC_PW_MTCMOS_ACK_SUB �Ĵ����ṹ���塣��ַƫ����:0x0074����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: �µ���MTCMOS��ʱ����Դ�����ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pw_mtcmos_ack_dspbbe : 1;  /* bit[0]   : [0]��DSPBBE�µ��� */
        unsigned int  pw_mtcmos_ack_bbp_cs : 1;  /* bit[1]   : [1]��BBP CS�µ���(��MTCMOS���룬���ź�����)  */
        unsigned int  pw_mtcmos_ack_lte    : 1;  /* bit[2]   : [2]��LTEBBPTOP�µ���  */
        unsigned int  reserved_0           : 1;  /* bit[3]   : [3]��BBP PS�µ���(��������Harq Mem�����Ƶ�AO_Sctrl��)  */
        unsigned int  reserved_1           : 28; /* bit[4-31]: �µ���MTCMOS��ʱ����Դ�����źš�
                                                               0����Դ�رգ�
                                                               1����Դ�򿪡�
                                                               [31:4]������  */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_ACK_SUB_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_ACK_SUB_pw_mtcmos_ack_dspbbe_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_ACK_SUB_pw_mtcmos_ack_dspbbe_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_ACK_SUB_pw_mtcmos_ack_bbp_cs_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_ACK_SUB_pw_mtcmos_ack_bbp_cs_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_ACK_SUB_pw_mtcmos_ack_lte_START     (2)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_ACK_SUB_pw_mtcmos_ack_lte_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_TIMEOUT_STAT_UNION
 �ṹ˵��  : MDMSC_PW_MTCMOS_TIMEOUT_STAT �Ĵ����ṹ���塣��ַƫ����:0x0078����ֵ:0x00000000�����:32
 �Ĵ���˵��: ϵͳPOWER״̬�Ĵ��������ڼ��ϵͳ������POWER״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pw_mtcmos_timeout_stat_dspbbe : 1;  /* bit[0]   : [0]��DSPBBE�µ��� */
        unsigned int  pw_mtcmos_timeout_stat_bbp_cs : 1;  /* bit[1]   : [1]��BBP CS�µ���  */
        unsigned int  pw_mtcmos_timeout_stat_lte    : 1;  /* bit[2]   : [2]��LTEBBPTOP�µ���  */
        unsigned int  reserved_0                    : 1;  /* bit[3]   : [3]��BBP PS�µ���(��������Harq Mem�����Ƶ�AO_Sctrl��)  */
        unsigned int  reserved_1                    : 28; /* bit[4-31]: �µ���MTCMOS�ȶ����������ָʾ�źš�
                                                                        [31:4]������ 
                                                                        0��δ�����
                                                                        1��MTCMOS�ȶ�״̬�� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_TIMEOUT_STAT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_TIMEOUT_STAT_pw_mtcmos_timeout_stat_dspbbe_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_TIMEOUT_STAT_pw_mtcmos_timeout_stat_dspbbe_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_TIMEOUT_STAT_pw_mtcmos_timeout_stat_bbp_cs_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_TIMEOUT_STAT_pw_mtcmos_timeout_stat_bbp_cs_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_TIMEOUT_STAT_pw_mtcmos_timeout_stat_lte_START     (2)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_TIMEOUT_STAT_pw_mtcmos_timeout_stat_lte_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_UNION
 �ṹ˵��  : MDMSC_PERIPH_CLKEN �Ĵ����ṹ���塣��ַƫ����:0x0100����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʱ��ʹ�ܼĴ���������ʹ������ʱ�ӡ��Ա���д1��ʹ�ܶ�Ӧ��ʱ�ӣ�д0��Ӱ��ʱ��ʹ�ܵ�״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                  : 1;  /* bit[0]    : reserved */
        unsigned int  reserved_1                  : 1;  /* bit[1]    : reserved */
        unsigned int  reserved_2                  : 1;  /* bit[2]    : reserved */
        unsigned int  reserved_3                  : 1;  /* bit[3]    : reserved */
        unsigned int  periph_clken_bbe16_kernel   : 1;  /* bit[4]    : BBE16�ں�ʱ�� */
        unsigned int  periph_clken_clk_bbe16_lbus : 1;  /* bit[5]    : BBE16 �ֲ�AXI����ʱ�� */
        unsigned int  reserved_4                  : 1;  /* bit[6]    : reserved */
        unsigned int  reserved_5                  : 1;  /* bit[7]    : reserved */
        unsigned int  periph_clken_modem_dmac     : 1;  /* bit[8]    : ModemDMAC����ʱ�� */
        unsigned int  periph_clken_cicom_upacc    : 1;  /* bit[9]    : UPACCʱ�� */
        unsigned int  reserved_6                  : 1;  /* bit[10]   : reserved */
        unsigned int  reserved_7                  : 1;  /* bit[11]   : reserved */
        unsigned int  periph_clken_cicom_l_cipher : 1;  /* bit[12]   : LCIPHERʱ�� */
        unsigned int  periph_clken_cicom_gu0      : 1;  /* bit[13]   : GUCIPHER0ʱ�� */
        unsigned int  reserved_8                  : 1;  /* bit[14]   : reserved */
        unsigned int  reserved_9                  : 1;  /* bit[15]   : reserved */
        unsigned int  periph_clken_modem_uart0    : 1;  /* bit[16]   : Modem��UART0����ʱ�� */
        unsigned int  reserved_10                 : 1;  /* bit[17]   : reserved */
        unsigned int  reserved_11                 : 1;  /* bit[18]   : reserved */
        unsigned int  reserved_12                 : 13; /* bit[19-31]: ʱ��ʹ�ܶ������£�д1ʱ�Ӵ򿪣���Modem��ϵͳ����IPʱ�ӿ��� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_periph_clken_bbe16_kernel_START    (4)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_periph_clken_bbe16_kernel_END      (4)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_periph_clken_clk_bbe16_lbus_START  (5)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_periph_clken_clk_bbe16_lbus_END    (5)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_periph_clken_modem_dmac_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_periph_clken_modem_dmac_END        (8)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_periph_clken_cicom_upacc_START     (9)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_periph_clken_cicom_upacc_END       (9)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_periph_clken_cicom_l_cipher_START  (12)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_periph_clken_cicom_l_cipher_END    (12)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_periph_clken_cicom_gu0_START       (13)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_periph_clken_cicom_gu0_END         (13)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_periph_clken_modem_uart0_START     (16)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_periph_clken_modem_uart0_END       (16)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_UNION
 �ṹ˵��  : MDMSC_PERIPH_CLKDIS �Ĵ����ṹ���塣��ַƫ����:0x0104����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʱ�ӽ�ֹ�Ĵ��������ڽ�ֹ����ʱ�ӡ��Ա���д1����ֹ��Ӧ��ʱ�ӣ�д0��Ӱ��ʱ��ʹ�ܵ�״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                   : 1;  /* bit[0]    : reserved */
        unsigned int  reserved_1                   : 1;  /* bit[1]    : reserved */
        unsigned int  reserved_2                   : 1;  /* bit[2]    : reserved */
        unsigned int  reserved_3                   : 1;  /* bit[3]    : reserved */
        unsigned int  periph_clkdis_bbe16_kernel   : 1;  /* bit[4]    : BBE16�ں�ʱ�� */
        unsigned int  periph_clkdis_clk_bbe16_lbus : 1;  /* bit[5]    : BBE16 �ֲ�AXI����ʱ�� */
        unsigned int  reserved_4                   : 1;  /* bit[6]    : reserved */
        unsigned int  reserved_5                   : 1;  /* bit[7]    : reserved */
        unsigned int  periph_clkdis_modem_dmac     : 1;  /* bit[8]    : ModemDMAC����ʱ�� */
        unsigned int  periph_clkdis_cicom_upacc    : 1;  /* bit[9]    : UPACCʱ�� */
        unsigned int  reserved_6                   : 1;  /* bit[10]   : reserved */
        unsigned int  reserved_7                   : 1;  /* bit[11]   : reserved */
        unsigned int  periph_clkdis_cicom_l_cipher : 1;  /* bit[12]   : LCIPHERʱ�� */
        unsigned int  periph_clkdis_cicom_gu0      : 1;  /* bit[13]   : GUCIPHER0ʱ�� */
        unsigned int  reserved_8                   : 1;  /* bit[14]   : reserved */
        unsigned int  reserved_9                   : 1;  /* bit[15]   : reserved */
        unsigned int  periph_clkdis_modem_uart0    : 1;  /* bit[16]   : Modem��UART0����ʱ�� */
        unsigned int  reserved_10                  : 1;  /* bit[17]   : reserved */
        unsigned int  reserved_11                  : 1;  /* bit[18]   : reserved */
        unsigned int  reserved_12                  : 13; /* bit[19-31]: ʱ�ӽ�ֹ�������£�д1ʱ�ӹرգ���Modem��ϵͳ����IPʱ�ӿ��� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_periph_clkdis_bbe16_kernel_START    (4)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_periph_clkdis_bbe16_kernel_END      (4)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_periph_clkdis_clk_bbe16_lbus_START  (5)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_periph_clkdis_clk_bbe16_lbus_END    (5)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_periph_clkdis_modem_dmac_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_periph_clkdis_modem_dmac_END        (8)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_periph_clkdis_cicom_upacc_START     (9)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_periph_clkdis_cicom_upacc_END       (9)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_periph_clkdis_cicom_l_cipher_START  (12)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_periph_clkdis_cicom_l_cipher_END    (12)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_periph_clkdis_cicom_gu0_START       (13)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_periph_clkdis_cicom_gu0_END         (13)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_periph_clkdis_modem_uart0_START     (16)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_periph_clkdis_modem_uart0_END       (16)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_UNION
 �ṹ˵��  : MDMSC_PERIPH_CLKEN_STAT �Ĵ����ṹ���塣��ַƫ����:0x0108����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʱ��״̬�Ĵ���9�����ڻض�������ʱ�ӵ�״̬������ʱ�ӿ����ź��辭����CRG�н���ͬ��������ˣ�����ļĴ���ֵ���ӳ���Ӧʱ����ļ������ں��������Ӧʱ��״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                       : 1;  /* bit[0]    : reserved */
        unsigned int  reserved_1                       : 1;  /* bit[1]    : reserved */
        unsigned int  reserved_2                       : 1;  /* bit[2]    : reserved */
        unsigned int  reserved_3                       : 1;  /* bit[3]    : reserved */
        unsigned int  periph_clken_stat_bbe16_kernel   : 1;  /* bit[4]    : BBE16�ں�ʱ�� */
        unsigned int  periph_clken_stat_clk_bbe16_lbus : 1;  /* bit[5]    : BBE16 �ֲ�AXI����ʱ�� */
        unsigned int  reserved_4                       : 1;  /* bit[6]    : reserved */
        unsigned int  reserved_5                       : 1;  /* bit[7]    : reserved */
        unsigned int  periph_clken_stat_modem_dmac     : 1;  /* bit[8]    : ModemDMAC����ʱ�� */
        unsigned int  periph_clken_stat_cicom_upacc    : 1;  /* bit[9]    : UPACCʱ�� */
        unsigned int  reserved_6                       : 1;  /* bit[10]   : reserved */
        unsigned int  reserved_7                       : 1;  /* bit[11]   : reserved */
        unsigned int  periph_clken_stat_cicom_l_cipher : 1;  /* bit[12]   : LCIPHERʱ�� */
        unsigned int  periph_clken_stat_cicom_gu0      : 1;  /* bit[13]   : GUCIPHER0ʱ�� */
        unsigned int  reserved_8                       : 1;  /* bit[14]   : reserved */
        unsigned int  reserved_9                       : 1;  /* bit[15]   : reserved */
        unsigned int  periph_clken_stat_modem_uart0    : 1;  /* bit[16]   : Modem��UART0����ʱ�� */
        unsigned int  reserved_10                      : 1;  /* bit[17]   : reserved */
        unsigned int  reserved_11                      : 1;  /* bit[18]   : reserved */
        unsigned int  reserved_12                      : 13; /* bit[19-31]: ʱ��״̬�������£��ߵ�ƽ��ʾʱ�Ӵ򿪣���Modem��ϵͳ����IPʱ�ӿ��� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_periph_clken_stat_bbe16_kernel_START    (4)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_periph_clken_stat_bbe16_kernel_END      (4)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_periph_clken_stat_clk_bbe16_lbus_START  (5)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_periph_clken_stat_clk_bbe16_lbus_END    (5)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_periph_clken_stat_modem_dmac_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_periph_clken_stat_modem_dmac_END        (8)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_periph_clken_stat_cicom_upacc_START     (9)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_periph_clken_stat_cicom_upacc_END       (9)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_periph_clken_stat_cicom_l_cipher_START  (12)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_periph_clken_stat_cicom_l_cipher_END    (12)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_periph_clken_stat_cicom_gu0_START       (13)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_periph_clken_stat_cicom_gu0_END         (13)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_periph_clken_stat_modem_uart0_START     (16)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_periph_clken_stat_modem_uart0_END       (16)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_UNION
 �ṹ˵��  : MDMSC_BBP_CLKEN0 �Ĵ����ṹ���塣��ַƫ����:0x0120����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBPʱ��ʹ�ܼĴ���0������ʹ������ʱ�ӡ��Ա���д1��ʹ�ܶ�Ӧ��ʱ�ӣ�д0��Ӱ��ʱ��ʹ�ܵ�״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbp_clken0_122m_tds         : 1;  /* bit[0]    : clk_122m_tds */
        unsigned int  bbp_clken0_245m_tds         : 1;  /* bit[1]    : clk_245m_tds */
        unsigned int  bbp_clken0_19m_cs           : 1;  /* bit[2]    : clk_19m_cs */
        unsigned int  reserved_0                  : 1;  /* bit[3]    : reserved */
        unsigned int  bbp_clken0_122m_twc         : 1;  /* bit[4]    : clk_122_twc */
        unsigned int  reserved_1                  : 1;  /* bit[5]    : reserved */
        unsigned int  bbp_clken0_122m_wc_abb      : 1;  /* bit[6]    : clk_122m_wc_abb */
        unsigned int  bbp_clken0_61m_wbbp_cs      : 1;  /* bit[7]    : clk_61m_wbbp_cs */
        unsigned int  bbp_clken0_122m_wbbp_cs     : 1;  /* bit[8]    : clk_122m_wbbp_cs */
        unsigned int  bbp_clken0_122m_tw          : 1;  /* bit[9]    : clk_122m_tw */
        unsigned int  bbp_clken0_104m_gbbp1       : 1;  /* bit[10]   : clk_104m_gbbp1 */
        unsigned int  bbp_clken0_axis_cs          : 1;  /* bit[11]   : clk_axis_cs */
        unsigned int  bbp_clken0_122m_cbbp        : 1;  /* bit[12]   : clk_122m_cbbp */
        unsigned int  reserved_2                  : 1;  /* bit[13]   : reserved */
        unsigned int  bbp_clken0_axim_bbc         : 1;  /* bit[14]   : clk_axim_bbc */
        unsigned int  bbp_clken0_122m_lte_pdf_bbc : 1;  /* bit[15]   : clk_122m_lte_pdf_bbc */
        unsigned int  bbp_clken0_122m_lte_pdt_bbc : 1;  /* bit[16]   : clk_122m_lte_pdt_bbc */
        unsigned int  bbp_clken0_245m_lte_bbc     : 1;  /* bit[17]   : clk_245m_lte_bbc */
        unsigned int  bbp_clken0_245m_wbbp_cs     : 1;  /* bit[18]   : clk_245m_wbbp_cs */
        unsigned int  bbp_clken0_104m_gbbp_sdr    : 1;  /* bit[19]   : clk_104m_gbbp_sdr */
        unsigned int  bbp_clken0_245m_wbbp_sdr    : 1;  /* bit[20]   : clk_245m_wbbp_sdr */
        unsigned int  bbp_clken0_104m_gbbp2       : 1;  /* bit[21]   : clk_104m_gbbp2 */
        unsigned int  bbp_clken0_150m_noc_cs      : 1;  /* bit[22]   : clk_150m_noc_cs */
        unsigned int  bbp_clken0_axim_bbpmst      : 1;  /* bit[23]   : clk_axim_bbpmst */
        unsigned int  bbp_clken0_19m_ch0_bbc      : 1;  /* bit[24]   : clk_19m_ch0_bbc */
        unsigned int  bbp_clken0_19m_ch1_bbc      : 1;  /* bit[25]   : clk_19m_ch1_bbc */
        unsigned int  reserved_3                  : 6;  /* bit[26-31]: ʱ��ʹ�ܶ������£�д1ʱ�Ӵ򿪣���BBP CS�������ʱ�ӿ��� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_122m_tds_START          (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_122m_tds_END            (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_245m_tds_START          (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_245m_tds_END            (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_19m_cs_START            (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_19m_cs_END              (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_122m_twc_START          (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_122m_twc_END            (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_122m_wc_abb_START       (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_122m_wc_abb_END         (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_61m_wbbp_cs_START       (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_61m_wbbp_cs_END         (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_122m_wbbp_cs_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_122m_wbbp_cs_END        (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_122m_tw_START           (9)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_122m_tw_END             (9)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_104m_gbbp1_START        (10)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_104m_gbbp1_END          (10)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_axis_cs_START           (11)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_axis_cs_END             (11)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_122m_cbbp_START         (12)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_122m_cbbp_END           (12)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_axim_bbc_START          (14)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_axim_bbc_END            (14)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_122m_lte_pdf_bbc_START  (15)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_122m_lte_pdf_bbc_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_122m_lte_pdt_bbc_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_122m_lte_pdt_bbc_END    (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_245m_lte_bbc_START      (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_245m_lte_bbc_END        (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_245m_wbbp_cs_START      (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_245m_wbbp_cs_END        (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_104m_gbbp_sdr_START     (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_104m_gbbp_sdr_END       (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_245m_wbbp_sdr_START     (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_245m_wbbp_sdr_END       (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_104m_gbbp2_START        (21)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_104m_gbbp2_END          (21)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_150m_noc_cs_START       (22)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_150m_noc_cs_END         (22)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_axim_bbpmst_START       (23)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_axim_bbpmst_END         (23)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_19m_ch0_bbc_START       (24)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_19m_ch0_bbc_END         (24)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_19m_ch1_bbc_START       (25)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_19m_ch1_bbc_END         (25)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_UNION
 �ṹ˵��  : MDMSC_BBP_CLKDIS0 �Ĵ����ṹ���塣��ַƫ����:0x0124����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʱ�ӽ�ֹ�Ĵ���0�����ڽ�ֹ����ʱ�ӡ��Ա���д1����ֹ��Ӧ��ʱ�ӣ�д0��Ӱ��ʱ��ʹ�ܵ�״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbp_clkdis0_122m_tds         : 1;  /* bit[0]    : clk_122m_tds */
        unsigned int  bbp_clkdis0_245m_tds         : 1;  /* bit[1]    : clk_245m_tds */
        unsigned int  bbp_clkdis0_19m_cs           : 1;  /* bit[2]    : clk_19m_cs */
        unsigned int  reserved_0                   : 1;  /* bit[3]    : reserved */
        unsigned int  bbp_clkdis0_122m_twc         : 1;  /* bit[4]    : clk_122_twc */
        unsigned int  reserved_1                   : 1;  /* bit[5]    : reserved */
        unsigned int  bbp_clkdis0_122m_wc_abb      : 1;  /* bit[6]    : clk_122m_wc_abb */
        unsigned int  bbp_clkdis0_61m_wbbp_cs      : 1;  /* bit[7]    : clk_61m_wbbp_cs */
        unsigned int  bbp_clkdis0_122m_wbbp_cs     : 1;  /* bit[8]    : clk_122m_wbbp_cs */
        unsigned int  bbp_clkdis0_122m_tw          : 1;  /* bit[9]    : clk_122m_tw */
        unsigned int  bbp_clkdis0_104m_gbbp1       : 1;  /* bit[10]   : clk_104m_gbbp1 */
        unsigned int  bbp_clkdis0_axis_cs          : 1;  /* bit[11]   : clk_axis_cs */
        unsigned int  bbp_clkdis0_122m_cbbp        : 1;  /* bit[12]   : clk_122m_cbbp */
        unsigned int  reserved_2                   : 1;  /* bit[13]   : reserved */
        unsigned int  bbp_clkdis0_axim_bbc         : 1;  /* bit[14]   : clk_axim_bbc */
        unsigned int  bbp_clkdis0_122m_lte_pdf_bbc : 1;  /* bit[15]   : clk_122m_lte_pdf_bbc */
        unsigned int  bbp_clkdis0_122m_lte_pdt_bbc : 1;  /* bit[16]   : clk_122m_lte_pdt_bbc */
        unsigned int  bbp_clkdis0_245m_lte_bbc     : 1;  /* bit[17]   : clk_245m_lte_bbc */
        unsigned int  bbp_clkdis0_245m_wbbp_cs     : 1;  /* bit[18]   : clk_245m_wbbp_cs */
        unsigned int  bbp_clkdis0_104m_gbbp_sdr    : 1;  /* bit[19]   : clk_104m_gbbp_sdr */
        unsigned int  bbp_clkdis0_245m_wbbp_sdr    : 1;  /* bit[20]   : clk_245m_wbbp_sdr */
        unsigned int  bbp_clkdis0_104m_gbbp2       : 1;  /* bit[21]   : clk_104m_gbbp2 */
        unsigned int  bbp_clkdis0_150m_noc_cs      : 1;  /* bit[22]   : clk_150m_noc_cs */
        unsigned int  bbp_clkdis0_axim_bbpmst      : 1;  /* bit[23]   : clk_axim_bbpmst */
        unsigned int  bbp_clkdis0_19m_ch0_bbc      : 1;  /* bit[24]   : clk_19m_ch0_bbc */
        unsigned int  bbp_clkdis0_19m_ch1_bbc      : 1;  /* bit[25]   : clk_19m_ch1_bbc */
        unsigned int  reserved_3                   : 6;  /* bit[26-31]: ʱ�ӽ�ֹ�������£�д1ʱ�ӹرգ���BBP CS�������ʱ�ӿ��� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_122m_tds_START          (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_122m_tds_END            (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_245m_tds_START          (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_245m_tds_END            (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_19m_cs_START            (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_19m_cs_END              (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_122m_twc_START          (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_122m_twc_END            (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_122m_wc_abb_START       (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_122m_wc_abb_END         (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_61m_wbbp_cs_START       (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_61m_wbbp_cs_END         (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_122m_wbbp_cs_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_122m_wbbp_cs_END        (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_122m_tw_START           (9)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_122m_tw_END             (9)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_104m_gbbp1_START        (10)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_104m_gbbp1_END          (10)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_axis_cs_START           (11)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_axis_cs_END             (11)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_122m_cbbp_START         (12)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_122m_cbbp_END           (12)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_axim_bbc_START          (14)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_axim_bbc_END            (14)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_122m_lte_pdf_bbc_START  (15)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_122m_lte_pdf_bbc_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_122m_lte_pdt_bbc_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_122m_lte_pdt_bbc_END    (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_245m_lte_bbc_START      (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_245m_lte_bbc_END        (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_245m_wbbp_cs_START      (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_245m_wbbp_cs_END        (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_104m_gbbp_sdr_START     (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_104m_gbbp_sdr_END       (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_245m_wbbp_sdr_START     (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_245m_wbbp_sdr_END       (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_104m_gbbp2_START        (21)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_104m_gbbp2_END          (21)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_150m_noc_cs_START       (22)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_150m_noc_cs_END         (22)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_axim_bbpmst_START       (23)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_axim_bbpmst_END         (23)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_19m_ch0_bbc_START       (24)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_19m_ch0_bbc_END         (24)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_19m_ch1_bbc_START       (25)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_19m_ch1_bbc_END         (25)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_UNION
 �ṹ˵��  : MDMSC_BBP_CLKEN_STAT0 �Ĵ����ṹ���塣��ַƫ����:0x0128����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʱ��״̬�Ĵ���0�����ڻض�������ʱ�ӵ�״̬������ʱ�ӿ����ź��辭����CRG�н���ͬ��������ˣ�����ļĴ���ֵ���ӳ���Ӧʱ����ļ������ں��������Ӧʱ��״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbp_clken_stat0_122m_tds         : 1;  /* bit[0]    : clk_122m_tds */
        unsigned int  bbp_clken_stat0_245m_tds         : 1;  /* bit[1]    : clk_245m_tds */
        unsigned int  bbp_clken_stat0_19m_cs           : 1;  /* bit[2]    : clk_19m_cs */
        unsigned int  reserved_0                       : 1;  /* bit[3]    : reserved */
        unsigned int  bbp_clken_stat0_122m_twc         : 1;  /* bit[4]    : clk_122_twc */
        unsigned int  reserved_1                       : 1;  /* bit[5]    : reserved */
        unsigned int  bbp_clken_stat0_122m_wc_abb      : 1;  /* bit[6]    : clk_122m_wc_abb */
        unsigned int  bbp_clken_stat0_61m_wbbp_cs      : 1;  /* bit[7]    : clk_61m_wbbp_cs */
        unsigned int  bbp_clken_stat0_122m_wbbp_cs     : 1;  /* bit[8]    : clk_122m_wbbp_cs */
        unsigned int  bbp_clken_stat0_122m_tw          : 1;  /* bit[9]    : clk_122m_tw */
        unsigned int  bbp_clken_stat0_104m_gbbp1       : 1;  /* bit[10]   : clk_104m_gbbp1 */
        unsigned int  bbp_clken_stat0_axis_cs          : 1;  /* bit[11]   : clk_axis_cs */
        unsigned int  bbp_clken_stat0_122m_cbbp        : 1;  /* bit[12]   : clk_122m_cbbp */
        unsigned int  reserved_2                       : 1;  /* bit[13]   : reserved */
        unsigned int  bbp_clken_stat0_axim_bbc         : 1;  /* bit[14]   : clk_axim_bbc */
        unsigned int  bbp_clken_stat0_122m_lte_pdf_bbc : 1;  /* bit[15]   : clk_122m_lte_pdf_bbc */
        unsigned int  bbp_clken_stat0_122m_lte_pdt_bbc : 1;  /* bit[16]   : clk_122m_lte_pdt_bbc */
        unsigned int  bbp_clken_stat0_245m_lte_bbc     : 1;  /* bit[17]   : clk_245m_lte_bbc */
        unsigned int  bbp_clken_stat0_245m_wbbp_cs     : 1;  /* bit[18]   : clk_245m_wbbp_cs */
        unsigned int  bbp_clken_stat0_104m_gbbp_sdr    : 1;  /* bit[19]   : clk_104m_gbbp_sdr */
        unsigned int  bbp_clken_stat0_245m_wbbp_sdr    : 1;  /* bit[20]   : clk_245m_wbbp_sdr */
        unsigned int  bbp_clken_stat0_104m_gbbp2       : 1;  /* bit[21]   : clk_104m_gbbp2 */
        unsigned int  bbp_clken_stat0_150m_noc_cs      : 1;  /* bit[22]   : clk_150m_noc_cs */
        unsigned int  bbp_clken_stat0_axim_bbpmst      : 1;  /* bit[23]   : clk_axim_bbpmst */
        unsigned int  bbp_clken_stat0_19m_ch0_bbc      : 1;  /* bit[24]   : clk_19m_ch0_bbc */
        unsigned int  bbp_clken_stat0_19m_ch1_bbc      : 1;  /* bit[25]   : clk_19m_ch1_bbc */
        unsigned int  reserved_3                       : 6;  /* bit[26-31]: ʱ��״̬�������£��ߵ�ƽ��ʾʱ�Ӵ򿪣���BBP CS�������ʱ�ӿ��� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_122m_tds_START          (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_122m_tds_END            (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_245m_tds_START          (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_245m_tds_END            (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_19m_cs_START            (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_19m_cs_END              (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_122m_twc_START          (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_122m_twc_END            (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_122m_wc_abb_START       (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_122m_wc_abb_END         (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_61m_wbbp_cs_START       (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_61m_wbbp_cs_END         (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_122m_wbbp_cs_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_122m_wbbp_cs_END        (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_122m_tw_START           (9)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_122m_tw_END             (9)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_104m_gbbp1_START        (10)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_104m_gbbp1_END          (10)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_axis_cs_START           (11)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_axis_cs_END             (11)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_122m_cbbp_START         (12)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_122m_cbbp_END           (12)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_axim_bbc_START          (14)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_axim_bbc_END            (14)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_122m_lte_pdf_bbc_START  (15)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_122m_lte_pdf_bbc_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_122m_lte_pdt_bbc_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_122m_lte_pdt_bbc_END    (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_245m_lte_bbc_START      (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_245m_lte_bbc_END        (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_245m_wbbp_cs_START      (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_245m_wbbp_cs_END        (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_104m_gbbp_sdr_START     (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_104m_gbbp_sdr_END       (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_245m_wbbp_sdr_START     (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_245m_wbbp_sdr_END       (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_104m_gbbp2_START        (21)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_104m_gbbp2_END          (21)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_150m_noc_cs_START       (22)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_150m_noc_cs_END         (22)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_axim_bbpmst_START       (23)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_axim_bbpmst_END         (23)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_19m_ch0_bbc_START       (24)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_19m_ch0_bbc_END         (24)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_19m_ch1_bbc_START       (25)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_19m_ch1_bbc_END         (25)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_UNION
 �ṹ˵��  : MDMSC_BBP_CLKEN1 �Ĵ����ṹ���塣��ַƫ����:0x012C����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBPʱ��ʹ�ܼĴ���1������ʹ������ʱ�ӡ��Ա���д1��ʹ�ܶ�Ӧ��ʱ�ӣ�д0��Ӱ��ʱ��ʹ�ܵ�״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbp_clken1_axim_wbbp     : 1;  /* bit[0]    : clk_axim_wbbp */
        unsigned int  bbp_clken1_61m_wbbp_ps   : 1;  /* bit[1]    : clk_61m_wbbp_ps */
        unsigned int  bbp_clken1_122m_wbbp_ps  : 1;  /* bit[2]    : clk_122m_wbbp_ps */
        unsigned int  bbp_clken1_245m_wbbp_ps  : 1;  /* bit[3]    : clk_245m_wbbp_ps */
        unsigned int  bbp_clken1_245m_irm      : 1;  /* bit[4]    : clk_245m_irm */
        unsigned int  reserved_0               : 1;  /* bit[5]    : reserved */
        unsigned int  bbp_clken1_122m_cbbp_irm : 1;  /* bit[6]    : clk_122m_cbbp_irm */
        unsigned int  bbp_clken1_axis_irm      : 1;  /* bit[7]    : clk_axis_irm */
        unsigned int  bbp_clken1_122m_wc_irm   : 1;  /* bit[8]    : clk_122m_wc_irm */
        unsigned int  reserved_1               : 1;  /* bit[9]    : reserved */
        unsigned int  reserved_2               : 6;  /* bit[10-15]: reserved */
        unsigned int  bbp_clken1_axi_lte       : 1;  /* bit[16]   : clk_axi_lte */
        unsigned int  bbp_clken1_122m_lte_pdf  : 1;  /* bit[17]   : clk_122m_lte_pdf */
        unsigned int  bbp_clken1_122m_lte_pdt  : 1;  /* bit[18]   : clk_122m_lte_pdt */
        unsigned int  bbp_clken1_122m_tds_pdt  : 1;  /* bit[19]   : clk_122m_tds_pdt */
        unsigned int  bbp_clken1_245m_lte      : 1;  /* bit[20]   : clk_245m_lte */
        unsigned int  bbp_clken1_19m_lte       : 1;  /* bit[21]   : clk_19m_lte */
        unsigned int  reserved_3               : 10; /* bit[22-31]: ʱ��ʹ�ܶ������£�д1ʱ�Ӵ򿪣���BBP PS������LTE�������ʱ�ӿ��� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_axim_wbbp_START      (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_axim_wbbp_END        (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_61m_wbbp_ps_START    (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_61m_wbbp_ps_END      (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_122m_wbbp_ps_START   (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_122m_wbbp_ps_END     (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_245m_wbbp_ps_START   (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_245m_wbbp_ps_END     (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_245m_irm_START       (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_245m_irm_END         (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_122m_cbbp_irm_START  (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_122m_cbbp_irm_END    (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_axis_irm_START       (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_axis_irm_END         (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_122m_wc_irm_START    (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_122m_wc_irm_END      (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_axi_lte_START        (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_axi_lte_END          (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_122m_lte_pdf_START   (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_122m_lte_pdf_END     (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_122m_lte_pdt_START   (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_122m_lte_pdt_END     (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_122m_tds_pdt_START   (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_122m_tds_pdt_END     (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_245m_lte_START       (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_245m_lte_END         (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_19m_lte_START        (21)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_19m_lte_END          (21)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_UNION
 �ṹ˵��  : MDMSC_BBP_CLKDIS1 �Ĵ����ṹ���塣��ַƫ����:0x0130����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʱ�ӽ�ֹ�Ĵ���1�����ڽ�ֹ����ʱ�ӡ��Ա���д1����ֹ��Ӧ��ʱ�ӣ�д0��Ӱ��ʱ��ʹ�ܵ�״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbp_clkdis1_axim_wbbp     : 1;  /* bit[0]    : clk_axim_wbbp */
        unsigned int  bbp_clkdis1_61m_wbbp_ps   : 1;  /* bit[1]    : clk_61m_wbbp_ps */
        unsigned int  bbp_clkdis1_122m_wbbp_ps  : 1;  /* bit[2]    : clk_122m_wbbp_ps */
        unsigned int  bbp_clkdis1_245m_wbbp_ps  : 1;  /* bit[3]    : clk_245m_wbbp_ps */
        unsigned int  bbp_clkdis1_245m_irm      : 1;  /* bit[4]    : clk_245m_irm */
        unsigned int  reserved_0                : 1;  /* bit[5]    : reserved */
        unsigned int  bbp_clkdis1_122m_cbbp_irm : 1;  /* bit[6]    : clk_122m_cbbp_irm */
        unsigned int  bbp_clkdis1_axis_irm      : 1;  /* bit[7]    : clk_axis_irm */
        unsigned int  bbp_clkdis1_122m_wc_irm   : 1;  /* bit[8]    : clk_122m_wc_irm */
        unsigned int  reserved_1                : 1;  /* bit[9]    : reserved */
        unsigned int  reserved_2                : 6;  /* bit[10-15]: reserved */
        unsigned int  bbp_clkdis1_axi_lte       : 1;  /* bit[16]   : clk_axi_lte */
        unsigned int  bbp_clkdis1_122m_lte_pdf  : 1;  /* bit[17]   : clk_122m_lte_pdf */
        unsigned int  bbp_clkdis1_122m_lte_pdt  : 1;  /* bit[18]   : clk_122m_lte_pdt */
        unsigned int  bbp_clkdis1_122m_tds_pdt  : 1;  /* bit[19]   : clk_122m_tds_pdt */
        unsigned int  bbp_clkdis1_245m_lte      : 1;  /* bit[20]   : clk_245m_lte */
        unsigned int  bbp_clkdis1_19m_lte       : 1;  /* bit[21]   : clk_19m_lte */
        unsigned int  reserved_3                : 10; /* bit[22-31]: ʱ�ӽ�ֹ�������£�д1ʱ�ӹرգ���BBP PS������LTE�������ʱ�ӿ��� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_axim_wbbp_START      (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_axim_wbbp_END        (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_61m_wbbp_ps_START    (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_61m_wbbp_ps_END      (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_122m_wbbp_ps_START   (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_122m_wbbp_ps_END     (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_245m_wbbp_ps_START   (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_245m_wbbp_ps_END     (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_245m_irm_START       (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_245m_irm_END         (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_122m_cbbp_irm_START  (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_122m_cbbp_irm_END    (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_axis_irm_START       (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_axis_irm_END         (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_122m_wc_irm_START    (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_122m_wc_irm_END      (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_axi_lte_START        (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_axi_lte_END          (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_122m_lte_pdf_START   (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_122m_lte_pdf_END     (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_122m_lte_pdt_START   (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_122m_lte_pdt_END     (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_122m_tds_pdt_START   (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_122m_tds_pdt_END     (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_245m_lte_START       (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_245m_lte_END         (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_19m_lte_START        (21)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_19m_lte_END          (21)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_UNION
 �ṹ˵��  : MDMSC_BBP_CLKEN_STAT1 �Ĵ����ṹ���塣��ַƫ����:0x0134����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʱ��״̬�Ĵ���1�����ڻض�������ʱ�ӵ�״̬������ʱ�ӿ����ź��辭����CRG�н���ͬ��������ˣ�����ļĴ���ֵ���ӳ���Ӧʱ����ļ������ں��������Ӧʱ��״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbp_clken_stat1_axim_wbbp     : 1;  /* bit[0]    : clk_axim_wbbp */
        unsigned int  bbp_clken_stat1_61m_wbbp_ps   : 1;  /* bit[1]    : clk_61m_wbbp_ps */
        unsigned int  bbp_clken_stat1_122m_wbbp_ps  : 1;  /* bit[2]    : clk_122m_wbbp_ps */
        unsigned int  bbp_clken_stat1_245m_wbbp_ps  : 1;  /* bit[3]    : clk_245m_wbbp_ps */
        unsigned int  bbp_clken_stat1_245m_irm      : 1;  /* bit[4]    : clk_245m_irm */
        unsigned int  reserved_0                    : 1;  /* bit[5]    : reserved */
        unsigned int  bbp_clken_stat1_122m_cbbp_irm : 1;  /* bit[6]    : clk_122m_cbbp_irm */
        unsigned int  bbp_clken_stat1_axis_irm      : 1;  /* bit[7]    : clk_axis_irm */
        unsigned int  bbp_clken_stat1_122m_wc_irm   : 1;  /* bit[8]    : clk_122m_wc_irm */
        unsigned int  reserved_1                    : 1;  /* bit[9]    : reserved */
        unsigned int  reserved_2                    : 6;  /* bit[10-15]: reserved */
        unsigned int  bbp_clken_stat1_axi_lte       : 1;  /* bit[16]   : clk_axi_lte */
        unsigned int  bbp_clken_stat1_122m_lte_pdf  : 1;  /* bit[17]   : clk_122m_lte_pdf */
        unsigned int  bbp_clken_stat1_122m_lte_pdt  : 1;  /* bit[18]   : clk_122m_lte_pdt */
        unsigned int  bbp_clken_stat1_122m_tds_pdt  : 1;  /* bit[19]   : clk_122m_tds_pdt */
        unsigned int  bbp_clken_stat1_245m_lte      : 1;  /* bit[20]   : clk_245m_lte */
        unsigned int  bbp_clken_stat1_19m_lte       : 1;  /* bit[21]   : clk_19m_lte */
        unsigned int  reserved_3                    : 10; /* bit[22-31]: ʱ��״̬�������£��ߵ�ƽ��ʾʱ�Ӵ򿪣���BBP PS������LTE�������ʱ�ӿ��� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_axim_wbbp_START      (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_axim_wbbp_END        (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_61m_wbbp_ps_START    (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_61m_wbbp_ps_END      (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_122m_wbbp_ps_START   (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_122m_wbbp_ps_END     (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_245m_wbbp_ps_START   (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_245m_wbbp_ps_END     (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_245m_irm_START       (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_245m_irm_END         (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_122m_cbbp_irm_START  (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_122m_cbbp_irm_END    (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_axis_irm_START       (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_axis_irm_END         (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_122m_wc_irm_START    (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_122m_wc_irm_END      (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_axi_lte_START        (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_axi_lte_END          (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_122m_lte_pdf_START   (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_122m_lte_pdf_END     (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_122m_lte_pdt_START   (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_122m_lte_pdt_END     (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_122m_tds_pdt_START   (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_122m_tds_pdt_END     (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_245m_lte_START       (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_245m_lte_END         (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_19m_lte_START        (21)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_19m_lte_END          (21)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_UNION
 �ṹ˵��  : MDMSC_PERIPH_RSTEN �Ĵ����ṹ���塣��ַƫ����:0x0150����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���踴λʹ�ܼĴ���������ʹ�����踴λ���Ա���д1����ӦIP���븴λ״̬��д0��Ӱ�츴λ״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                : 1;  /* bit[0]    : reserved */
        unsigned int  reserved_1                : 1;  /* bit[1]    : reserved */
        unsigned int  reserved_2                : 1;  /* bit[2]    : reserved */
        unsigned int  reserved_3                : 1;  /* bit[3]    : reserved */
        unsigned int  periph_rsten_bbe16_kernel : 1;  /* bit[4]    : BBE16�ں�ʱ������λ */
        unsigned int  periph_rsten_bbe16_lbus   : 1;  /* bit[5]    : BBE16 �ֲ�AXI������λ */
        unsigned int  reserved_4                : 1;  /* bit[6]    : reserved */
        unsigned int  reserved_5                : 1;  /* bit[7]    : reserved */
        unsigned int  periph_rsten_mdmac        : 1;  /* bit[8]    : mdmac����ʱ������λ */
        unsigned int  periph_rsten_upacc        : 1;  /* bit[9]    : upacc����ʱ������λ */
        unsigned int  reserved_6                : 1;  /* bit[10]   : reserved */
        unsigned int  reserved_7                : 1;  /* bit[11]   : reserved */
        unsigned int  periph_rsten_lcipher      : 1;  /* bit[12]   : lcipher����ʱ������λ */
        unsigned int  periph_rsten_gucipher0    : 1;  /* bit[13]   : gucipher0����ʱ������λ */
        unsigned int  reserved_8                : 1;  /* bit[14]   : reserved */
        unsigned int  reserved_9                : 1;  /* bit[15]   : reserved */
        unsigned int  periph_rsten_muart0       : 1;  /* bit[16]   : Modem��UART0����ʱ������λ */
        unsigned int  reserved_10               : 1;  /* bit[17]   : reserved */
        unsigned int  reserved_11               : 14; /* bit[18-31]: ��λʹ�ܶ������£�д1��λʹ�ܣ���Modem��ϵͳ����IP��λ����
                                                                     [31:18] ���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_periph_rsten_bbe16_kernel_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_periph_rsten_bbe16_kernel_END    (4)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_periph_rsten_bbe16_lbus_START    (5)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_periph_rsten_bbe16_lbus_END      (5)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_periph_rsten_mdmac_START         (8)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_periph_rsten_mdmac_END           (8)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_periph_rsten_upacc_START         (9)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_periph_rsten_upacc_END           (9)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_periph_rsten_lcipher_START       (12)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_periph_rsten_lcipher_END         (12)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_periph_rsten_gucipher0_START     (13)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_periph_rsten_gucipher0_END       (13)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_periph_rsten_muart0_START        (16)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_periph_rsten_muart0_END          (16)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_UNION
 �ṹ˵��  : MDMSC_PERIPH_RSTDIS �Ĵ����ṹ���塣��ַƫ����:0x0154����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���踴λ��ֹ�Ĵ��������ڽ�ֹ���踴λ���Ա���д1����Ӧ��������λ��д0��Ӱ�츴λʹ�ܵ�״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                 : 1;  /* bit[0]    : reserved */
        unsigned int  reserved_1                 : 1;  /* bit[1]    : reserved */
        unsigned int  reserved_2                 : 1;  /* bit[2]    : reserved */
        unsigned int  reserved_3                 : 1;  /* bit[3]    : reserved */
        unsigned int  periph_rstdis_bbe16_kernel : 1;  /* bit[4]    : BBE16�ں�ʱ������λ */
        unsigned int  periph_rstdis_bbe16_lbus   : 1;  /* bit[5]    : BBE16 �ֲ�AXI������λ */
        unsigned int  reserved_4                 : 1;  /* bit[6]    : reserved */
        unsigned int  reserved_5                 : 1;  /* bit[7]    : reserved */
        unsigned int  periph_rstdis_mdmac        : 1;  /* bit[8]    : mdmac����ʱ������λ */
        unsigned int  periph_rstdis_upacc        : 1;  /* bit[9]    : upacc����ʱ������λ */
        unsigned int  reserved_6                 : 1;  /* bit[10]   : reserved */
        unsigned int  reserved_7                 : 1;  /* bit[11]   : reserved */
        unsigned int  periph_rstdis_lcipher      : 1;  /* bit[12]   : lcipher����ʱ������λ */
        unsigned int  periph_rstdis_gucipher0    : 1;  /* bit[13]   : gucipher0����ʱ������λ */
        unsigned int  reserved_8                 : 1;  /* bit[14]   : reserved */
        unsigned int  reserved_9                 : 1;  /* bit[15]   : reserved */
        unsigned int  periph_rstdis_muart0       : 1;  /* bit[16]   : Modem��UART0����ʱ������λ */
        unsigned int  reserved_10                : 1;  /* bit[17]   : reserved */
        unsigned int  reserved_11                : 14; /* bit[18-31]: ��λ��ֹ�������£�д1��λ�������Modem��ϵͳ����IP��λ����
                                                                      [31:18] : Reserved */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_periph_rstdis_bbe16_kernel_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_periph_rstdis_bbe16_kernel_END    (4)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_periph_rstdis_bbe16_lbus_START    (5)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_periph_rstdis_bbe16_lbus_END      (5)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_periph_rstdis_mdmac_START         (8)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_periph_rstdis_mdmac_END           (8)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_periph_rstdis_upacc_START         (9)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_periph_rstdis_upacc_END           (9)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_periph_rstdis_lcipher_START       (12)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_periph_rstdis_lcipher_END         (12)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_periph_rstdis_gucipher0_START     (13)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_periph_rstdis_gucipher0_END       (13)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_periph_rstdis_muart0_START        (16)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_periph_rstdis_muart0_END          (16)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_UNION
 �ṹ˵��  : MDMSC_PERIPH_RSTEN_STAT �Ĵ����ṹ���塣��ַƫ����:0x0158����ֵ:0xFFFFFFFE�����:32
 �Ĵ���˵��: ���踴λ״̬�Ĵ���6�����ڻض������踴λ��״̬�����踴λ�����ź��辭��ͬ��������ˣ�����ļĴ���ֵ���ӳ���Ӧʱ����ļ������ں��������Ӧ�⸴λ״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                     : 1;  /* bit[0]    : reserved */
        unsigned int  reserved_1                     : 1;  /* bit[1]    : reserved */
        unsigned int  reserved_2                     : 1;  /* bit[2]    : reserved */
        unsigned int  reserved_3                     : 1;  /* bit[3]    : reserved */
        unsigned int  periph_rsten_stat_bbe16_kernel : 1;  /* bit[4]    : BBE16�ں�ʱ������λ */
        unsigned int  periph_rsten_stat_bbe16_lbus   : 1;  /* bit[5]    : BBE16 �ֲ�AXI������λ */
        unsigned int  reserved_4                     : 1;  /* bit[6]    : reserved */
        unsigned int  reserved_5                     : 1;  /* bit[7]    : reserved */
        unsigned int  periph_rsten_stat_mdmac        : 1;  /* bit[8]    : mdmac����ʱ������λ */
        unsigned int  periph_rsten_stat_upacc        : 1;  /* bit[9]    : upacc����ʱ������λ */
        unsigned int  reserved_6                     : 1;  /* bit[10]   : reserved */
        unsigned int  reserved_7                     : 1;  /* bit[11]   : reserved */
        unsigned int  periph_rsten_stat_lcipher      : 1;  /* bit[12]   : lcipher����ʱ������λ */
        unsigned int  periph_rsten_stat_gucipher0    : 1;  /* bit[13]   : gucipher0����ʱ������λ */
        unsigned int  reserved_8                     : 1;  /* bit[14]   : reserved */
        unsigned int  reserved_9                     : 1;  /* bit[15]   : reserved */
        unsigned int  periph_rsten_stat_stat_muart0  : 1;  /* bit[16]   : Modem��UART0����ʱ������λ */
        unsigned int  reserved_10                    : 1;  /* bit[17]   : reserved */
        unsigned int  reserved_11                    : 14; /* bit[18-31]: ��λ״̬�������£��ߵ�ƽ��ʾ���ڸ�λ��Modem��ϵͳ����IP��λ����
                                                                          [31:18] : Reserved */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_periph_rsten_stat_bbe16_kernel_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_periph_rsten_stat_bbe16_kernel_END    (4)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_periph_rsten_stat_bbe16_lbus_START    (5)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_periph_rsten_stat_bbe16_lbus_END      (5)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_periph_rsten_stat_mdmac_START         (8)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_periph_rsten_stat_mdmac_END           (8)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_periph_rsten_stat_upacc_START         (9)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_periph_rsten_stat_upacc_END           (9)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_periph_rsten_stat_lcipher_START       (12)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_periph_rsten_stat_lcipher_END         (12)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_periph_rsten_stat_gucipher0_START     (13)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_periph_rsten_stat_gucipher0_END       (13)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_periph_rsten_stat_stat_muart0_START   (16)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_periph_rsten_stat_stat_muart0_END     (16)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_UNION
 �ṹ˵��  : MDMSC_BBP_RSTEN0 �Ĵ����ṹ���塣��ַƫ����:0x0170����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��λʹ�ܼĴ���������ʹ�����踴λ���Ա���д1����ӦIP���븴λ״̬��д0��Ӱ�츴λ״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbp_rsten0_122m_tds         : 1;  /* bit[0]    : rst_122m_tds_n */
        unsigned int  bbp_rsten0_245m_tds         : 1;  /* bit[1]    : rst_245m_tds_n */
        unsigned int  bbp_rsten0_19m_cs           : 1;  /* bit[2]    : rst_19m_cs_n */
        unsigned int  bbp_rsten0_32k_cs           : 1;  /* bit[3]    : rst_32k_cs_n */
        unsigned int  bbp_rsten0_122m_twc         : 1;  /* bit[4]    : rst_122m_twc_n */
        unsigned int  reserved_0                  : 1;  /* bit[5]    : reserved */
        unsigned int  bbp_rsten0_122m_wc_abb      : 1;  /* bit[6]    : rst_122m_wc_abb_n */
        unsigned int  bbp_rsten0_61m_wbbp_cs      : 1;  /* bit[7]    : rst_61m_wbbp_cs_n */
        unsigned int  bbp_rsten0_122m_wbbp_cs     : 1;  /* bit[8]    : rst_122m_wbbp_cs_n */
        unsigned int  bbp_rsten0_122m_tw          : 1;  /* bit[9]    : rst_122m_tw_n */
        unsigned int  bbp_rsten0_104m_gbbp1       : 1;  /* bit[10]   : rst_104m_gbbp1_n */
        unsigned int  bbp_rsten0_axis_cs          : 1;  /* bit[11]   : rst_axis_cs_n */
        unsigned int  bbp_rsten0_122m_cbbp        : 1;  /* bit[12]   : rst_122m_cbbp_n */
        unsigned int  reserved_1                  : 1;  /* bit[13]   : reserved */
        unsigned int  bbp_rsten0_axim_bbc         : 1;  /* bit[14]   : rst_axim_bbc_n */
        unsigned int  bbp_rsten0_122m_lte_pdf_bbc : 1;  /* bit[15]   : rst_122m_lte_pdf_bbc_n */
        unsigned int  bbp_rsten0_122m_lte_pdt_bbc : 1;  /* bit[16]   : rst_122m_lte_pdt_bbc_n */
        unsigned int  bbp_rsten0_245m_lte_bbc     : 1;  /* bit[17]   : rst_245m_lte_bbc_n */
        unsigned int  bbp_rsten0_245m_wbbp_cs     : 1;  /* bit[18]   : rst_245m_wbbp_cs_n */
        unsigned int  bbp_rsten0_104m_gbbp_sdr    : 1;  /* bit[19]   : rst_104m_gbbp_sdr_n */
        unsigned int  bbp_rsten0_245m_wbbp_sdr    : 1;  /* bit[20]   : rst_245m_wbbp_sdr_n */
        unsigned int  bbp_rsten0_104m_gbbp2       : 1;  /* bit[21]   : rst_104m_gbbp2_n */
        unsigned int  bbp_rsten0_150m_noc_cs      : 1;  /* bit[22]   : rst_150m_noc_cs_n */
        unsigned int  bbp_rsten0_axim_bbpmst      : 1;  /* bit[23]   : rst_axim_bbpmst_n */
        unsigned int  bbp_rsten0_19m_ch0_bbc      : 1;  /* bit[24]   : rst_19m_ch0_bbc_n */
        unsigned int  bbp_rsten0_19m_ch1_bbc      : 1;  /* bit[25]   : rst_19m_ch1_bbc_n */
        unsigned int  reserved_2                  : 6;  /* bit[26-31]: ��λʹ�ܶ������£�д1��λʹ�ܣ���BBP CS������λ����
                                                                       ���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_122m_tds_START          (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_122m_tds_END            (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_245m_tds_START          (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_245m_tds_END            (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_19m_cs_START            (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_19m_cs_END              (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_32k_cs_START            (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_32k_cs_END              (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_122m_twc_START          (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_122m_twc_END            (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_122m_wc_abb_START       (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_122m_wc_abb_END         (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_61m_wbbp_cs_START       (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_61m_wbbp_cs_END         (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_122m_wbbp_cs_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_122m_wbbp_cs_END        (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_122m_tw_START           (9)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_122m_tw_END             (9)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_104m_gbbp1_START        (10)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_104m_gbbp1_END          (10)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_axis_cs_START           (11)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_axis_cs_END             (11)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_122m_cbbp_START         (12)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_122m_cbbp_END           (12)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_axim_bbc_START          (14)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_axim_bbc_END            (14)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_122m_lte_pdf_bbc_START  (15)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_122m_lte_pdf_bbc_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_122m_lte_pdt_bbc_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_122m_lte_pdt_bbc_END    (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_245m_lte_bbc_START      (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_245m_lte_bbc_END        (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_245m_wbbp_cs_START      (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_245m_wbbp_cs_END        (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_104m_gbbp_sdr_START     (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_104m_gbbp_sdr_END       (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_245m_wbbp_sdr_START     (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_245m_wbbp_sdr_END       (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_104m_gbbp2_START        (21)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_104m_gbbp2_END          (21)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_150m_noc_cs_START       (22)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_150m_noc_cs_END         (22)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_axim_bbpmst_START       (23)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_axim_bbpmst_END         (23)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_19m_ch0_bbc_START       (24)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_19m_ch0_bbc_END         (24)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_19m_ch1_bbc_START       (25)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_19m_ch1_bbc_END         (25)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_UNION
 �ṹ˵��  : MDMSC_BBP_RSTDIS0 �Ĵ����ṹ���塣��ַƫ����:0x0174����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��λ��ֹ�Ĵ��������ڽ�ֹ���踴λ���Ա���д1����Ӧ��������λ��д0��Ӱ�츴λʹ�ܵ�״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbp_rstdis0_122m_tds         : 1;  /* bit[0]    : rst_122m_tds_n */
        unsigned int  bbp_rstdis0_245m_tds         : 1;  /* bit[1]    : rst_245m_tds_n */
        unsigned int  bbp_rstdis0_19m_cs           : 1;  /* bit[2]    : rst_19m_cs_n */
        unsigned int  bbp_rstdis0_32k_cs           : 1;  /* bit[3]    : rst_32k_cs_n */
        unsigned int  bbp_rstdis0_122m_twc         : 1;  /* bit[4]    : rst_122m_twc_n */
        unsigned int  reserved_0                   : 1;  /* bit[5]    : reserved */
        unsigned int  bbp_rstdis0_122m_wc_abb      : 1;  /* bit[6]    : rst_122m_wc_abb_n */
        unsigned int  bbp_rstdis0_61m_wbbp_cs      : 1;  /* bit[7]    : rst_61m_wbbp_cs_n */
        unsigned int  bbp_rstdis0_122m_wbbp_cs     : 1;  /* bit[8]    : rst_122m_wbbp_cs_n */
        unsigned int  bbp_rstdis0_122m_tw          : 1;  /* bit[9]    : rst_122m_tw_n */
        unsigned int  bbp_rstdis0_104m_gbbp1       : 1;  /* bit[10]   : rst_104m_gbbp1_n */
        unsigned int  bbp_rstdis0_axis_cs          : 1;  /* bit[11]   : rst_axis_cs_n */
        unsigned int  bbp_rstdis0_122m_cbbp        : 1;  /* bit[12]   : rst_122m_cbbp_n */
        unsigned int  reserved_1                   : 1;  /* bit[13]   : reserved */
        unsigned int  bbp_rstdis0_axim_bbc         : 1;  /* bit[14]   : rst_axim_bbc_n */
        unsigned int  bbp_rstdis0_122m_lte_pdf_bbc : 1;  /* bit[15]   : rst_122m_lte_pdf_bbc_n */
        unsigned int  bbp_rstdis0_122m_lte_pdt_bbc : 1;  /* bit[16]   : rst_122m_lte_pdt_bbc_n */
        unsigned int  bbp_rstdis0_245m_lte_bbc     : 1;  /* bit[17]   : rst_245m_lte_bbc_n */
        unsigned int  bbp_rstdis0_245m_wbbp_cs     : 1;  /* bit[18]   : rst_245m_wbbp_cs_n */
        unsigned int  bbp_rstdis0_104m_gbbp_sdr    : 1;  /* bit[19]   : rst_104m_gbbp_sdr_n */
        unsigned int  bbp_rstdis0_245m_wbbp_sdr    : 1;  /* bit[20]   : rst_245m_wbbp_sdr_n */
        unsigned int  bbp_rstdis0_104m_gbbp2       : 1;  /* bit[21]   : rst_104m_gbbp2_n */
        unsigned int  bbp_rstdis0_150m_noc_cs      : 1;  /* bit[22]   : rst_150m_noc_cs_n */
        unsigned int  bbp_rstdis0_axim_bbpmst      : 1;  /* bit[23]   : rst_axim_bbpmst_n */
        unsigned int  bbp_rstdis0_19m_ch0_bbc      : 1;  /* bit[24]   : rst_19m_ch0_bbc_n */
        unsigned int  bbp_rstdis0_19m_ch1_bbc      : 1;  /* bit[25]   : rst_19m_ch1_bbc_n */
        unsigned int  reserved_2                   : 6;  /* bit[26-31]: ��λ��ֹ�������£�д1��λ�������BBP CS������λ����
                                                                        ���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_122m_tds_START          (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_122m_tds_END            (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_245m_tds_START          (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_245m_tds_END            (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_19m_cs_START            (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_19m_cs_END              (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_32k_cs_START            (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_32k_cs_END              (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_122m_twc_START          (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_122m_twc_END            (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_122m_wc_abb_START       (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_122m_wc_abb_END         (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_61m_wbbp_cs_START       (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_61m_wbbp_cs_END         (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_122m_wbbp_cs_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_122m_wbbp_cs_END        (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_122m_tw_START           (9)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_122m_tw_END             (9)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_104m_gbbp1_START        (10)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_104m_gbbp1_END          (10)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_axis_cs_START           (11)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_axis_cs_END             (11)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_122m_cbbp_START         (12)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_122m_cbbp_END           (12)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_axim_bbc_START          (14)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_axim_bbc_END            (14)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_122m_lte_pdf_bbc_START  (15)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_122m_lte_pdf_bbc_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_122m_lte_pdt_bbc_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_122m_lte_pdt_bbc_END    (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_245m_lte_bbc_START      (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_245m_lte_bbc_END        (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_245m_wbbp_cs_START      (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_245m_wbbp_cs_END        (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_104m_gbbp_sdr_START     (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_104m_gbbp_sdr_END       (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_245m_wbbp_sdr_START     (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_245m_wbbp_sdr_END       (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_104m_gbbp2_START        (21)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_104m_gbbp2_END          (21)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_150m_noc_cs_START       (22)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_150m_noc_cs_END         (22)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_axim_bbpmst_START       (23)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_axim_bbpmst_END         (23)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_19m_ch0_bbc_START       (24)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_19m_ch0_bbc_END         (24)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_19m_ch1_bbc_START       (25)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_19m_ch1_bbc_END         (25)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_UNION
 �ṹ˵��  : MDMSC_BBP_RSTEN_STAT0 �Ĵ����ṹ���塣��ַƫ����:0x0178����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: BBP��λ״̬�Ĵ��������ڻض������踴λ��״̬�����踴λ�����ź��辭��ͬ��������ˣ�����ļĴ���ֵ���ӳ���Ӧʱ����ļ������ں��������Ӧ�⸴λ״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbp_rsten_stat0_122m_tds         : 1;  /* bit[0]    : rst_122m_tds_n */
        unsigned int  bbp_rsten_stat0_245m_tds         : 1;  /* bit[1]    : rst_245m_tds_n */
        unsigned int  bbp_rsten_stat0_19m_cs           : 1;  /* bit[2]    : rst_19m_cs_n */
        unsigned int  bbp_rsten_stat0_32k_cs           : 1;  /* bit[3]    : rst_32k_cs_n */
        unsigned int  bbp_rsten_stat0_122m_twc         : 1;  /* bit[4]    : rst_122m_twc_n */
        unsigned int  reserved_0                       : 1;  /* bit[5]    : reserved */
        unsigned int  bbp_rsten_stat0_122m_wc_abb      : 1;  /* bit[6]    : rst_122m_wc_abb_n */
        unsigned int  bbp_rsten_stat0_61m_wbbp_cs      : 1;  /* bit[7]    : rst_61m_wbbp_cs_n */
        unsigned int  bbp_rsten_stat0_122m_wbbp_cs     : 1;  /* bit[8]    : rst_122m_wbbp_cs_n */
        unsigned int  bbp_rsten_stat0_122m_tw          : 1;  /* bit[9]    : rst_122m_tw_n */
        unsigned int  bbp_rsten_stat0_104m_gbbp1       : 1;  /* bit[10]   : rst_104m_gbbp1_n */
        unsigned int  bbp_rsten_stat0_axis_cs          : 1;  /* bit[11]   : rst_axis_cs_n */
        unsigned int  bbp_rsten_stat0_122m_cbbp        : 1;  /* bit[12]   : rst_122m_cbbp_n */
        unsigned int  reserved_1                       : 1;  /* bit[13]   : reserved */
        unsigned int  bbp_rsten_stat0_axim_bbc         : 1;  /* bit[14]   : rst_axim_bbc_n */
        unsigned int  bbp_rsten_stat0_122m_lte_pdf_bbc : 1;  /* bit[15]   : rst_122m_lte_pdf_bbc_n */
        unsigned int  bbp_rsten_stat0_122m_lte_pdt_bbc : 1;  /* bit[16]   : rst_122m_lte_pdt_bbc_n */
        unsigned int  bbp_rsten_stat0_245m_lte_bbc     : 1;  /* bit[17]   : rst_245m_lte_bbc_n */
        unsigned int  bbp_rsten_stat0_245m_wbbp_cs     : 1;  /* bit[18]   : rst_245m_wbbp_cs_n */
        unsigned int  bbp_rsten_stat0_104m_gbbp_sdr    : 1;  /* bit[19]   : rst_104m_gbbp_sdr_n */
        unsigned int  bbp_rsten_stat0_245m_wbbp_sdr    : 1;  /* bit[20]   : rst_245m_wbbp_sdr_n */
        unsigned int  bbp_rsten_stat0_104m_gbbp2       : 1;  /* bit[21]   : rst_104m_gbbp2_n */
        unsigned int  bbp_rsten_stat0_150m_noc_cs      : 1;  /* bit[22]   : rst_150m_noc_cs_n */
        unsigned int  bbp_rsten_stat0_axim_bbpmst      : 1;  /* bit[23]   : rst_axim_bbpmst_n */
        unsigned int  bbp_rsten_stat0_19m_ch0_bbc      : 1;  /* bit[24]   : rst_19m_ch0_bbc_n */
        unsigned int  bbp_rsten_stat0_19m_ch1_bbc      : 1;  /* bit[25]   : rst_19m_ch1_bbc_n */
        unsigned int  reserved_2                       : 6;  /* bit[26-31]: ��λ״̬�������£��ߵ�ƽ��ʾ���ڸ�λ��BBP CS������λ���ơ�
                                                                            ���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_122m_tds_START          (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_122m_tds_END            (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_245m_tds_START          (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_245m_tds_END            (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_19m_cs_START            (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_19m_cs_END              (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_32k_cs_START            (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_32k_cs_END              (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_122m_twc_START          (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_122m_twc_END            (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_122m_wc_abb_START       (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_122m_wc_abb_END         (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_61m_wbbp_cs_START       (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_61m_wbbp_cs_END         (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_122m_wbbp_cs_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_122m_wbbp_cs_END        (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_122m_tw_START           (9)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_122m_tw_END             (9)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_104m_gbbp1_START        (10)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_104m_gbbp1_END          (10)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_axis_cs_START           (11)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_axis_cs_END             (11)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_122m_cbbp_START         (12)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_122m_cbbp_END           (12)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_axim_bbc_START          (14)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_axim_bbc_END            (14)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_122m_lte_pdf_bbc_START  (15)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_122m_lte_pdf_bbc_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_122m_lte_pdt_bbc_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_122m_lte_pdt_bbc_END    (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_245m_lte_bbc_START      (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_245m_lte_bbc_END        (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_245m_wbbp_cs_START      (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_245m_wbbp_cs_END        (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_104m_gbbp_sdr_START     (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_104m_gbbp_sdr_END       (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_245m_wbbp_sdr_START     (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_245m_wbbp_sdr_END       (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_104m_gbbp2_START        (21)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_104m_gbbp2_END          (21)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_150m_noc_cs_START       (22)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_150m_noc_cs_END         (22)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_axim_bbpmst_START       (23)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_axim_bbpmst_END         (23)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_19m_ch0_bbc_START       (24)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_19m_ch0_bbc_END         (24)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_19m_ch1_bbc_START       (25)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_19m_ch1_bbc_END         (25)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_UNION
 �ṹ˵��  : MDMSC_BBP_RSTEN1 �Ĵ����ṹ���塣��ַƫ����:0x017C����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��λʹ�ܼĴ���1������ʹ�����踴λ���Ա���д1����ӦIP���븴λ״̬��д0��Ӱ�츴λ״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbp_rsten1_axim_wbbp     : 1;  /* bit[0]   : rst_axim_wbbp_n */
        unsigned int  bbp_rsten1_61m_wbbp_ps   : 1;  /* bit[1]   : rst_61m_wbbp_ps_n */
        unsigned int  bbp_rsten1_122m_wbbp_ps  : 1;  /* bit[2]   : rst_122m_wbbp_ps_n */
        unsigned int  bbp_rsten1_245m_wbbp_ps  : 1;  /* bit[3]   : rst_245m_wbbp_ps_n */
        unsigned int  bbp_rsten1_245m_irm      : 1;  /* bit[4]   : rst_245m_157m_irm_n */
        unsigned int  reserved_0               : 1;  /* bit[5]   : reserved */
        unsigned int  bbp_rsten1_122m_cbbp_irm : 1;  /* bit[6]   : rst_122m_cbbp_irm_n */
        unsigned int  bbp_rsten1_axis_irm      : 1;  /* bit[7]   : rst_axis_irm_n */
        unsigned int  bbp_rsten1_122m_wc_irm   : 1;  /* bit[8]   : rst_122m_wc_irm_n */
        unsigned int  reserved_1               : 23; /* bit[9-31]: ��λʹ�ܶ������£�д1��λʹ�ܣ���BBP PS������LTE������λ����
                                                                   Reserved */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_bbp_rsten1_axim_wbbp_START      (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_bbp_rsten1_axim_wbbp_END        (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_bbp_rsten1_61m_wbbp_ps_START    (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_bbp_rsten1_61m_wbbp_ps_END      (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_bbp_rsten1_122m_wbbp_ps_START   (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_bbp_rsten1_122m_wbbp_ps_END     (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_bbp_rsten1_245m_wbbp_ps_START   (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_bbp_rsten1_245m_wbbp_ps_END     (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_bbp_rsten1_245m_irm_START       (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_bbp_rsten1_245m_irm_END         (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_bbp_rsten1_122m_cbbp_irm_START  (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_bbp_rsten1_122m_cbbp_irm_END    (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_bbp_rsten1_axis_irm_START       (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_bbp_rsten1_axis_irm_END         (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_bbp_rsten1_122m_wc_irm_START    (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_bbp_rsten1_122m_wc_irm_END      (8)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_UNION
 �ṹ˵��  : MDMSC_BBP_RSTDIS1 �Ĵ����ṹ���塣��ַƫ����:0x0180����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��λ��ֹ�Ĵ���1�����ڽ�ֹ���踴λ���Ա���д1����Ӧ��������λ��д0��Ӱ�츴λʹ�ܵ�״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbp_rstdis1_axim_wbbp     : 1;  /* bit[0]   : rst_axim_wbbp_n */
        unsigned int  bbp_rstdis1_61m_wbbp_ps   : 1;  /* bit[1]   : rst_61m_wbbp_ps_n */
        unsigned int  bbp_rstdis1_122m_wbbp_ps  : 1;  /* bit[2]   : rst_122m_wbbp_ps_n */
        unsigned int  bbp_rstdis1_245m_wbbp_ps  : 1;  /* bit[3]   : rst_245m_wbbp_ps_n */
        unsigned int  bbp_rstdis1_245m_irm      : 1;  /* bit[4]   : rst_245m_irm_n */
        unsigned int  reserved_0                : 1;  /* bit[5]   : reserved */
        unsigned int  bbp_rstdis1_122m_cbbp_irm : 1;  /* bit[6]   : rst_122m_cbbp_irm_n */
        unsigned int  bbp_rstdis1_axis_irm      : 1;  /* bit[7]   : rst_axis_irm_n */
        unsigned int  bbp_rstdis1_122m_wc_irm   : 1;  /* bit[8]   : rst_122m_wc_irm_n */
        unsigned int  reserved_1                : 23; /* bit[9-31]: ��λ��ֹ�������£�д1��λ�������BBP PS������LTE������λ����
                                                                    Reseved */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_bbp_rstdis1_axim_wbbp_START      (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_bbp_rstdis1_axim_wbbp_END        (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_bbp_rstdis1_61m_wbbp_ps_START    (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_bbp_rstdis1_61m_wbbp_ps_END      (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_bbp_rstdis1_122m_wbbp_ps_START   (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_bbp_rstdis1_122m_wbbp_ps_END     (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_bbp_rstdis1_245m_wbbp_ps_START   (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_bbp_rstdis1_245m_wbbp_ps_END     (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_bbp_rstdis1_245m_irm_START       (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_bbp_rstdis1_245m_irm_END         (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_bbp_rstdis1_122m_cbbp_irm_START  (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_bbp_rstdis1_122m_cbbp_irm_END    (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_bbp_rstdis1_axis_irm_START       (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_bbp_rstdis1_axis_irm_END         (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_bbp_rstdis1_122m_wc_irm_START    (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_bbp_rstdis1_122m_wc_irm_END      (8)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_UNION
 �ṹ˵��  : MDMSC_BBP_RSTEN_STAT1 �Ĵ����ṹ���塣��ַƫ����:0x0184����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: BBP��λ״̬�Ĵ���1�����ڻض������踴λ��״̬�����踴λ�����ź��辭��ͬ��������ˣ�����ļĴ���ֵ���ӳ���Ӧʱ����ļ������ں��������Ӧ�⸴λ״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbp_rsten_stat1_axim_wbbp     : 1;  /* bit[0]   : rst_axim_wbbp_n */
        unsigned int  bbp_rsten_stat1_61m_wbbp_ps   : 1;  /* bit[1]   : rst_61m_wbbp_ps_n */
        unsigned int  bbp_rsten_stat1_122m_wbbp_ps  : 1;  /* bit[2]   : rst_122m_wbbp_ps_n */
        unsigned int  bbp_rsten_stat1_245m_wbbp_ps  : 1;  /* bit[3]   : rst_245m_wbbp_ps_n */
        unsigned int  bbp_rsten_stat1_245m_irm      : 1;  /* bit[4]   : rst_245m_157m_irm_n */
        unsigned int  reserved_0                    : 1;  /* bit[5]   : reserved */
        unsigned int  bbp_rsten_stat1_122m_cbbp_irm : 1;  /* bit[6]   : rst_122m_cbbp_irm_n */
        unsigned int  bbp_rsten_stat1_axis_irm      : 1;  /* bit[7]   : rst_axis_irm_n */
        unsigned int  bbp_rsten_stat1_122m_wc_irm   : 1;  /* bit[8]   : rst_122m_wc_irm_n */
        unsigned int  reserved_1                    : 23; /* bit[9-31]: ��λ״̬�������£��ߵ�ƽ��ʾ���ڸ�λ��BBP PS������LTE������λ����
                                                                        Reseved */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_bbp_rsten_stat1_axim_wbbp_START      (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_bbp_rsten_stat1_axim_wbbp_END        (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_bbp_rsten_stat1_61m_wbbp_ps_START    (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_bbp_rsten_stat1_61m_wbbp_ps_END      (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_bbp_rsten_stat1_122m_wbbp_ps_START   (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_bbp_rsten_stat1_122m_wbbp_ps_END     (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_bbp_rsten_stat1_245m_wbbp_ps_START   (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_bbp_rsten_stat1_245m_wbbp_ps_END     (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_bbp_rsten_stat1_245m_irm_START       (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_bbp_rsten_stat1_245m_irm_END         (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_bbp_rsten_stat1_122m_cbbp_irm_START  (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_bbp_rsten_stat1_122m_cbbp_irm_END    (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_bbp_rsten_stat1_axis_irm_START       (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_bbp_rsten_stat1_axis_irm_END         (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_bbp_rsten_stat1_122m_wc_irm_START    (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_bbp_rsten_stat1_122m_wc_irm_END      (8)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_EN_UNION
 �ṹ˵��  : MDMSC_SECONDARY_NEWINT0_EN �Ĵ����ṹ���塣��ַƫ����:0x01E0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_secondary_int_en_ipc_s_inner_core_intr4  : 1;  /* bit[0]    : ��ȫIPC�����Tensilica BBE16�ĺ˼��ж�(ipc_s_inner_core_intr[4]) */
        unsigned int  sc_secondary_int_en_ipc_ns_inner_core_intr4 : 1;  /* bit[1]    : �ǰ�ȫIPC�����Tensilica BBE16�ĺ˼��ж�(ipc_ns_inner_core_intr[4]) */
        unsigned int  sc_secondary_int_en_ipc_s_lock_intr4        : 1;  /* bit[2]    : ��ȫIPC�����Tensilica BBE16����Դ���ж�(ipc_s_lock_intr[4]) */
        unsigned int  sc_secondary_int_en_ipc_ns_lock_intr4       : 1;  /* bit[3]    : �ǰ�ȫIPC�����Tensilica BBE16����Դ���ж�(ipc_ns_lock_intr[4]) */
        unsigned int  reserved_0                                  : 12; /* bit[4-15] : ���� */
        unsigned int  reserved_1                                  : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_EN_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_EN_sc_secondary_int_en_ipc_s_inner_core_intr4_START   (0)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_EN_sc_secondary_int_en_ipc_s_inner_core_intr4_END     (0)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_EN_sc_secondary_int_en_ipc_ns_inner_core_intr4_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_EN_sc_secondary_int_en_ipc_ns_inner_core_intr4_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_EN_sc_secondary_int_en_ipc_s_lock_intr4_START         (2)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_EN_sc_secondary_int_en_ipc_s_lock_intr4_END           (2)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_EN_sc_secondary_int_en_ipc_ns_lock_intr4_START        (3)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_EN_sc_secondary_int_en_ipc_ns_lock_intr4_END          (3)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATRAW_UNION
 �ṹ˵��  : MDMSC_SECONDARY_NEWINT0_STATRAW �Ĵ����ṹ���塣��ַƫ����:0x01E4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_secondary_int_raw_ipc_s_inner_core_intr4  : 1;  /* bit[0]    : ��ȫIPC�����Tensilica BBE16�ĺ˼��ж�(ipc_s_inner_core_intr[4]) */
        unsigned int  sc_secondary_int_raw_ipc_ns_inner_core_intr4 : 1;  /* bit[1]    : �ǰ�ȫIPC�����Tensilica BBE16�ĺ˼��ж�(ipc_ns_inner_core_intr[4]) */
        unsigned int  sc_secondary_int_raw_ipc_s_lock_intr4        : 1;  /* bit[2]    : ��ȫIPC�����Tensilica BBE16����Դ���ж�(ipc_s_lock_intr[4]) */
        unsigned int  sc_secondary_int_raw_ipc_ns_lock_intr4       : 1;  /* bit[3]    : �ǰ�ȫIPC�����Tensilica BBE16����Դ���ж�(ipc_ns_lock_intr[4]) */
        unsigned int  reserved_0                                   : 12; /* bit[4-15] : ���� */
        unsigned int  reserved_1                                   : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATRAW_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATRAW_sc_secondary_int_raw_ipc_s_inner_core_intr4_START   (0)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATRAW_sc_secondary_int_raw_ipc_s_inner_core_intr4_END     (0)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATRAW_sc_secondary_int_raw_ipc_ns_inner_core_intr4_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATRAW_sc_secondary_int_raw_ipc_ns_inner_core_intr4_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATRAW_sc_secondary_int_raw_ipc_s_lock_intr4_START         (2)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATRAW_sc_secondary_int_raw_ipc_s_lock_intr4_END           (2)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATRAW_sc_secondary_int_raw_ipc_ns_lock_intr4_START        (3)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATRAW_sc_secondary_int_raw_ipc_ns_lock_intr4_END          (3)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATMSK_UNION
 �ṹ˵��  : MDMSC_SECONDARY_NEWINT0_STATMSK �Ĵ����ṹ���塣��ַƫ����:0x01E8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_secondary_int_mask_ipc_s_inner_core_intr4  : 1;  /* bit[0]    : ��ȫIPC�����Tensilica BBE16�ĺ˼��ж�(ipc_s_inner_core_intr[4]) */
        unsigned int  sc_secondary_int_mask_ipc_ns_inner_core_intr4 : 1;  /* bit[1]    : �ǰ�ȫIPC�����Tensilica BBE16�ĺ˼��ж�(ipc_ns_inner_core_intr[4]) */
        unsigned int  sc_secondary_int_mask_ipc_s_lock_intr4        : 1;  /* bit[2]    : ��ȫIPC�����Tensilica BBE16����Դ���ж�(ipc_s_lock_intr[4]) */
        unsigned int  sc_secondary_int_mask_ipc_ns_lock_intr4       : 1;  /* bit[3]    : �ǰ�ȫIPC�����Tensilica BBE16����Դ���ж�(ipc_ns_lock_intr[4]) */
        unsigned int  reserved_0                                    : 12; /* bit[4-15] : ���� */
        unsigned int  reserved_1                                    : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATMSK_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATMSK_sc_secondary_int_mask_ipc_s_inner_core_intr4_START   (0)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATMSK_sc_secondary_int_mask_ipc_s_inner_core_intr4_END     (0)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATMSK_sc_secondary_int_mask_ipc_ns_inner_core_intr4_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATMSK_sc_secondary_int_mask_ipc_ns_inner_core_intr4_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATMSK_sc_secondary_int_mask_ipc_s_lock_intr4_START         (2)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATMSK_sc_secondary_int_mask_ipc_s_lock_intr4_END           (2)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATMSK_sc_secondary_int_mask_ipc_ns_lock_intr4_START        (3)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATMSK_sc_secondary_int_mask_ipc_ns_lock_intr4_END          (3)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_UNION
 �ṹ˵��  : MDMSC_SECONDARY_NEWINT1_EN �Ĵ����ṹ���塣��ַƫ����:0x01F0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                              : 16; /* bit[0-15] : ���� */
        unsigned int  sc_secondary_int_en_axierrirq_n         : 1;  /* bit[16]   : �ֲ�����д����ʱBͨ�����ص�error�ж� */
        unsigned int  sc_secondary_int_en_mwdt_bbe_ot_intr    : 1;  /* bit[17]   : BBE16 watchdog�ĳ�ʱ�ж� */
        unsigned int  sc_secondary_int_en_mnoc_fault0         : 1;  /* bit[18]   : MODEMNOC Fault�ź�observer_Error_mainFault_0 */
        unsigned int  sc_secondary_int_en_mnoc_fault1         : 1;  /* bit[19]   : MODEMNOC Fault�ź�observer_Error_mainFault_1 */
        unsigned int  sc_secondary_int_en_comm_32k_int        : 1;  /* bit[20]   : comm_32k_int�ж� */
        unsigned int  sc_secondary_int_en_ccpu_sftfiq_intr    : 1;  /* bit[21]   : ccpu_sftfiq_intr�ж� */
        unsigned int  sc_secondary_newint_en_bbpmst_error_int : 1;  /* bit[22]   : bbpmst_error_int�ж� */
        unsigned int  sc_secondary_int_en_arremap_error_flag  : 1;  /* bit[23]   : ������REMAP����ָʾ�͸�CCPU�Ķ����ж� */
        unsigned int  sc_secondary_int_en_awremap_error_flag  : 1;  /* bit[24]   : д����REMAP����ָʾ�͸�CCPU�Ķ����ж� */
        unsigned int  sc_secondary_int_en_usim0_detect_int    : 1;  /* bit[25]   : usim0�Ȳ�μ���ж��͸�CCPU�Ķ����ж� */
        unsigned int  sc_secondary_int_en_usim1_detect_int    : 1;  /* bit[26]   : usim1�Ȳ�μ���ж��͸�CCPU�Ķ����ж� */
        unsigned int  reserved_1                              : 5;  /* bit[27-31]: ���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_axierrirq_n_START          (16)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_axierrirq_n_END            (16)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_mwdt_bbe_ot_intr_START     (17)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_mwdt_bbe_ot_intr_END       (17)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_mnoc_fault0_START          (18)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_mnoc_fault0_END            (18)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_mnoc_fault1_START          (19)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_mnoc_fault1_END            (19)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_comm_32k_int_START         (20)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_comm_32k_int_END           (20)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_ccpu_sftfiq_intr_START     (21)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_ccpu_sftfiq_intr_END       (21)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_newint_en_bbpmst_error_int_START  (22)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_newint_en_bbpmst_error_int_END    (22)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_arremap_error_flag_START   (23)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_arremap_error_flag_END     (23)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_awremap_error_flag_START   (24)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_awremap_error_flag_END     (24)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_usim0_detect_int_START     (25)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_usim0_detect_int_END       (25)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_usim1_detect_int_START     (26)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_usim1_detect_int_END       (26)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_UNION
 �ṹ˵��  : MDMSC_SECONDARY_NEWINT1_STATRAW �Ĵ����ṹ���塣��ַƫ����:0x01F4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                               : 16; /* bit[0-15] : ���� */
        unsigned int  sc_secondary_int_raw_axierrirq_n         : 1;  /* bit[16]   : �ֲ�����д����ʱBͨ�����ص�error�ж� */
        unsigned int  sc_secondary_int_raw_mwdt_bbe_ot_intr    : 1;  /* bit[17]   : BBE16 watchdog�ĳ�ʱ�ж� */
        unsigned int  sc_secondary_int_raw_mnoc_fault0         : 1;  /* bit[18]   : MODEMNOC Fault�ź�observer_Error_mainFault_0 */
        unsigned int  sc_secondary_int_raw_mnoc_fault1         : 1;  /* bit[19]   : MODEMNOC Fault�ź�observer_Error_mainFault_1 */
        unsigned int  sc_secondary_int_raw_comm_32k_int        : 1;  /* bit[20]   : comm_32k_int�ж� */
        unsigned int  sc_secondary_int_raw_ccpu_sftfiq_intr    : 1;  /* bit[21]   : ccpu_sftfiq_intr�ж� */
        unsigned int  sc_secondary_newint_raw_bbpmst_error_int : 1;  /* bit[22]   : bbpmst_error_int�ж� */
        unsigned int  sc_secondary_int_raw_arremap_error_flag  : 1;  /* bit[23]   : ������REMAP����ָʾ�͸�CCPU�Ķ����ж� */
        unsigned int  sc_secondary_int_raw_awremap_error_flag  : 1;  /* bit[24]   : д����REMAP����ָʾ�͸�CCPU�Ķ����ж� */
        unsigned int  sc_secondary_int_raw_usim0_detect_int    : 1;  /* bit[25]   : usim0�Ȳ�μ���ж��͸�CCPU�Ķ����ж� */
        unsigned int  sc_secondary_int_raw_usim1_detect_int    : 1;  /* bit[26]   : usim1�Ȳ�μ���ж��͸�CCPU�Ķ����ж� */
        unsigned int  reserved_1                               : 5;  /* bit[27-31]: ���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_axierrirq_n_START          (16)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_axierrirq_n_END            (16)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_mwdt_bbe_ot_intr_START     (17)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_mwdt_bbe_ot_intr_END       (17)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_mnoc_fault0_START          (18)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_mnoc_fault0_END            (18)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_mnoc_fault1_START          (19)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_mnoc_fault1_END            (19)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_comm_32k_int_START         (20)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_comm_32k_int_END           (20)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_ccpu_sftfiq_intr_START     (21)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_ccpu_sftfiq_intr_END       (21)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_newint_raw_bbpmst_error_int_START  (22)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_newint_raw_bbpmst_error_int_END    (22)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_arremap_error_flag_START   (23)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_arremap_error_flag_END     (23)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_awremap_error_flag_START   (24)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_awremap_error_flag_END     (24)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_usim0_detect_int_START     (25)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_usim0_detect_int_END       (25)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_usim1_detect_int_START     (26)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_usim1_detect_int_END       (26)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_UNION
 �ṹ˵��  : MDMSC_SECONDARY_NEWINT1_STATMSK �Ĵ����ṹ���塣��ַƫ����:0x01F8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                                : 16; /* bit[0-15] : ���� */
        unsigned int  sc_secondary_int_mask_axierrirq_n         : 1;  /* bit[16]   : �ֲ�����д����ʱBͨ�����ص�error�ж� */
        unsigned int  sc_secondary_int_mask_mwdt_bbe_ot_intr    : 1;  /* bit[17]   : BBE16 watchdog�ĳ�ʱ�ж� */
        unsigned int  sc_secondary_int_mask_mnoc_fault0         : 1;  /* bit[18]   : MODEMNOC Fault�ź�observer_Error_mainFault_0 */
        unsigned int  sc_secondary_int_mask_mnoc_fault1         : 1;  /* bit[19]   : MODEMNOC Fault�ź�observer_Error_mainFault_1 */
        unsigned int  sc_secondary_int_mask_comm_32k_int        : 1;  /* bit[20]   : comm_32k_int�ж� */
        unsigned int  sc_secondary_int_mask_ccpu_sftfiq_intr    : 1;  /* bit[21]   : ccpu_sftfiq_intr�ж� */
        unsigned int  sc_secondary_newint_mask_bbpmst_error_int : 1;  /* bit[22]   : bbpmst_error_int�ж� */
        unsigned int  sc_secondary_int_mask_arremap_error_flag  : 1;  /* bit[23]   : ������REMAP����ָʾ�͸�CCPU�Ķ����ж� */
        unsigned int  sc_secondary_int_mask_awremap_error_flag  : 1;  /* bit[24]   : д����REMAP����ָʾ�͸�CCPU�Ķ����ж� */
        unsigned int  sc_secondary_int_mask_usim0_detect_int    : 1;  /* bit[25]   : usim0�Ȳ�μ���ж��͸�CCPU�Ķ����ж� */
        unsigned int  sc_secondary_int_mask_usim1_detect_int    : 1;  /* bit[26]   : usim1�Ȳ�μ���ж��͸�CCPU�Ķ����ж� */
        unsigned int  reserved_1                                : 5;  /* bit[27-31]: ���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_axierrirq_n_START          (16)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_axierrirq_n_END            (16)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_mwdt_bbe_ot_intr_START     (17)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_mwdt_bbe_ot_intr_END       (17)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_mnoc_fault0_START          (18)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_mnoc_fault0_END            (18)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_mnoc_fault1_START          (19)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_mnoc_fault1_END            (19)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_comm_32k_int_START         (20)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_comm_32k_int_END           (20)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_ccpu_sftfiq_intr_START     (21)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_ccpu_sftfiq_intr_END       (21)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_newint_mask_bbpmst_error_int_START  (22)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_newint_mask_bbpmst_error_int_END    (22)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_arremap_error_flag_START   (23)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_arremap_error_flag_END     (23)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_awremap_error_flag_START   (24)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_awremap_error_flag_END     (24)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_usim0_detect_int_START     (25)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_usim0_detect_int_END       (25)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_usim1_detect_int_START     (26)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_usim1_detect_int_END       (26)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_UNION
 �ṹ˵��  : MDMSC_SECONDARY_INT_EN �Ĵ����ṹ���塣��ַƫ����:0x0200����ֵ:0x00000000�����:32
 �Ĵ���˵��: ϵͳ�����ж�ʹ�ܼĴ��������ڶ�ϵͳ�����жϽ����������á���ӦbitΪ1��ʾʹ����Ӧ�жϣ�Ϊ0��ʾ�����жϡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_secondary_int_en_wbbp_otdoa_int2bbe        : 1;  /* bit[0] : wbbp_otdoa_int2bbe�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_en_bbpslot_bbe16_in14        : 1;  /* bit[1] : bbpslot_bbe16_in14�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_en_bbpslot_bbe16_in13        : 1;  /* bit[2] : bbpslot_bbe16_in13�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_en_upacc_dsp_int             : 1;  /* bit[3] : UPACC�жϣ�upacc_dsp_int�� */
        unsigned int  sc_secondary_int_en_upacc_arm_int             : 1;  /* bit[4] : UPACC�жϣ�upacc_arm_int�� */
        unsigned int  sc_secondary_int_en_g1_int_bbp_to_dsp_32k     : 1;  /* bit[5] : g1_int_bbp_to_dsp_32k�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_en_g1_int_bbp_to_dsp         : 1;  /* bit[6] : g1_int_bbp_to_dsp�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_en_g2_int_bbp_to_dsp_32k     : 1;  /* bit[7] : g2_int_bbp_to_dsp_32k�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_en_g2_int_bbp_to_dsp         : 1;  /* bit[8] : g2_int_bbp_to_dsp�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_en_bbpcom_ctu_g1_arm_intr    : 1;  /* bit[9] : bbpcom_ctu_g1_arm_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_en_bbpcom_ctu_g2_arm_intr    : 1;  /* bit[10]: bbpcom_ctu_g2_arm_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_en_bbpcom_ctu_w_arm_intr     : 1;  /* bit[11]: bbpcom_ctu_w_arm_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_en_wbbp_card1_0ms_intr       : 1;  /* bit[12]: wbbp_card1_0ms_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_en_wbbp_wdrx_slp_awk_sw_intr : 1;  /* bit[13]: wbbp_wdrx_slp_awk_sw_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_en_wbbp_clk_sw_intr          : 1;  /* bit[14]: wbbp_clk_sw_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_en_wbbp_card2_0ms_intr       : 1;  /* bit[15]: wbbp_card2_0ms_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_en_wbbp_search_intr          : 1;  /* bit[16]: wbbp_search_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_en_wbbp_rake_intr            : 1;  /* bit[17]: wbbp_rake_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_en_wbbp_decode_intr          : 1;  /* bit[18]: wbbp_decode_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_en_wbbp_card1_time_intr      : 1;  /* bit[19]: wbbp_card1_time_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_en_wbbp_card2_time_intr      : 1;  /* bit[20]: wbbp_card2_time_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_en_wbbp_multi_search_intr    : 1;  /* bit[21]: wbbp_multi_search_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_en_wbbp_bbpmst_intr          : 1;  /* bit[22]: wbbp_bbpmst_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_en_lte_dsp_warn_intr         : 1;  /* bit[23]: lte_dsp_warn_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_en_mwdt_bbe_intr             : 1;  /* bit[24]: mwdt_bbe_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_en_bbpmst_error_int          : 1;  /* bit[25]: bbpmst_error_int�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_en_mtimer8_intc              : 1;  /* bit[26]: mtimer8_intc�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_en_mtimer9_intc              : 1;  /* bit[27]: mtimer9_intc�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_en_muart0_intr               : 1;  /* bit[28]: Modem��uart0(CCPU/BBE16����)�ж� */
        unsigned int  sc_secondary_int_en_uart3_intr                : 1;  /* bit[29]: AP��uart3��LTE/Connectivity���渴�ã��ж� */
        unsigned int  sc_secondary_int_en_uart0_intr                : 1;  /* bit[30]: AP��uart0(���ڲ���У׼���������) �ж� */
        unsigned int  reserved                                      : 1;  /* bit[31]: reserved */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_otdoa_int2bbe_START         (0)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_otdoa_int2bbe_END           (0)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_bbpslot_bbe16_in14_START         (1)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_bbpslot_bbe16_in14_END           (1)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_bbpslot_bbe16_in13_START         (2)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_bbpslot_bbe16_in13_END           (2)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_upacc_dsp_int_START              (3)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_upacc_dsp_int_END                (3)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_upacc_arm_int_START              (4)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_upacc_arm_int_END                (4)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_g1_int_bbp_to_dsp_32k_START      (5)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_g1_int_bbp_to_dsp_32k_END        (5)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_g1_int_bbp_to_dsp_START          (6)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_g1_int_bbp_to_dsp_END            (6)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_g2_int_bbp_to_dsp_32k_START      (7)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_g2_int_bbp_to_dsp_32k_END        (7)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_g2_int_bbp_to_dsp_START          (8)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_g2_int_bbp_to_dsp_END            (8)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_bbpcom_ctu_g1_arm_intr_START     (9)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_bbpcom_ctu_g1_arm_intr_END       (9)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_bbpcom_ctu_g2_arm_intr_START     (10)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_bbpcom_ctu_g2_arm_intr_END       (10)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_bbpcom_ctu_w_arm_intr_START      (11)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_bbpcom_ctu_w_arm_intr_END        (11)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_card1_0ms_intr_START        (12)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_card1_0ms_intr_END          (12)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_wdrx_slp_awk_sw_intr_START  (13)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_wdrx_slp_awk_sw_intr_END    (13)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_clk_sw_intr_START           (14)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_clk_sw_intr_END             (14)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_card2_0ms_intr_START        (15)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_card2_0ms_intr_END          (15)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_search_intr_START           (16)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_search_intr_END             (16)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_rake_intr_START             (17)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_rake_intr_END               (17)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_decode_intr_START           (18)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_decode_intr_END             (18)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_card1_time_intr_START       (19)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_card1_time_intr_END         (19)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_card2_time_intr_START       (20)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_card2_time_intr_END         (20)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_multi_search_intr_START     (21)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_multi_search_intr_END       (21)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_bbpmst_intr_START           (22)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_bbpmst_intr_END             (22)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_lte_dsp_warn_intr_START          (23)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_lte_dsp_warn_intr_END            (23)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_mwdt_bbe_intr_START              (24)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_mwdt_bbe_intr_END                (24)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_bbpmst_error_int_START           (25)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_bbpmst_error_int_END             (25)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_mtimer8_intc_START               (26)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_mtimer8_intc_END                 (26)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_mtimer9_intc_START               (27)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_mtimer9_intc_END                 (27)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_muart0_intr_START                (28)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_muart0_intr_END                  (28)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_uart3_intr_START                 (29)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_uart3_intr_END                   (29)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_uart0_intr_START                 (30)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_uart0_intr_END                   (30)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_UNION
 �ṹ˵��  : MDMSC_SECONDARY_INT_STATRAW �Ĵ����ṹ���塣��ַƫ����:0x0204����ֵ:0x00000000�����:32
 �Ĵ���˵��: ϵͳ�����ж��жϼĴ���������ָʾϵͳ����ԭʼ�ж�״̬������ǰ������ӦbitΪ1��ʾ���жϣ�Ϊ0��ʾ���жϡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_secondary_int_raw_wbbp_otdoa_int2bbe        : 1;  /* bit[0] : wbbp_otdoa_int2bbe�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_raw_bbpslot_bbe16_in14        : 1;  /* bit[1] : bbpslot_bbe16_int14�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_raw_bbpslot_bbe16_in13        : 1;  /* bit[2] : bbpslot_bbe16_int13�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_raw_upacc_dsp_int             : 1;  /* bit[3] : UPACC�жϣ�upacc_dsp_int�� */
        unsigned int  sc_secondary_int_raw_upacc_arm_int             : 1;  /* bit[4] : UPACC�жϣ�upacc_arm_int�� */
        unsigned int  sc_secondary_int_raw_g1_int_bbp_to_dsp_32k     : 1;  /* bit[5] : g1_int_bbp_to_dsp_32k�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_raw_g1_int_bbp_to_dsp         : 1;  /* bit[6] : g1_int_bbp_to_dsp�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_raw_g2_int_bbp_to_dsp_32k     : 1;  /* bit[7] : g2_int_bbp_to_dsp_32k�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_raw_g2_int_bbp_to_dsp         : 1;  /* bit[8] : g2_int_bbp_to_dsp�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_raw_bbpcom_ctu_g1_arm_intr    : 1;  /* bit[9] : bbpcom_ctu_g1_arm_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_raw_bbpcom_ctu_g2_arm_intr    : 1;  /* bit[10]: bbpcom_ctu_g2_arm_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_raw_bbpcom_ctu_w_arm_intr     : 1;  /* bit[11]: bbpcom_ctu_w_arm_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_raw_wbbp_card1_0ms_intr       : 1;  /* bit[12]: wbbp_card1_0ms_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_raw_wbbp_wdrx_slp_awk_sw_intr : 1;  /* bit[13]: wbbp_wdrx_slp_awk_sw_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_raw_wbbp_clk_sw_intr          : 1;  /* bit[14]: wbbp_clk_sw_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_raw_wbbp_card2_0ms_intr       : 1;  /* bit[15]: wbbp_card2_0ms_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_raw_wbbp_search_intr          : 1;  /* bit[16]: wbbp_search_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_raw_wbbp_rake_intr            : 1;  /* bit[17]: wbbp_rake_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_raw_wbbp_decode_intr          : 1;  /* bit[18]: wbbp_decode_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_raw_wbbp_card1_time_intr      : 1;  /* bit[19]: wbbp_card1_time_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_raw_wbbp_card2_time_intr      : 1;  /* bit[20]: wbbp_card2_time_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_raw_wbbp_multi_search_intr    : 1;  /* bit[21]: wbbp_multi_search_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_raw_wbbp_bbpmst_intr          : 1;  /* bit[22]: wbbp_bbpmst_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_raw_lte_dsp_warn_intr         : 1;  /* bit[23]: lte_dsp_warn_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_raw_mwdt_bbe_intr             : 1;  /* bit[24]: mwdt_bbe_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_raw_bbpmst_error_int          : 1;  /* bit[25]: bbpmst_error_int�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_raw_mtimer8_intc              : 1;  /* bit[26]: mtimer8_intc�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_raw_mtimer9_intc              : 1;  /* bit[27]: mtimer9_intc�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_raw_muart0_intr               : 1;  /* bit[28]: Modem��uart0(CCPU/BBE16����)�ж� */
        unsigned int  sc_secondary_int_raw_uart3_intr                : 1;  /* bit[29]: AP��uart3��LTE/Connectivity���渴�ã��ж� */
        unsigned int  sc_secondary_int_raw_uart0_intr                : 1;  /* bit[30]: AP��uart0(���ڲ���У׼���������) �ж� */
        unsigned int  reserved                                       : 1;  /* bit[31]: ����
                                                                                       
                                                                                         */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_otdoa_int2bbe_START         (0)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_otdoa_int2bbe_END           (0)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_bbpslot_bbe16_in14_START         (1)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_bbpslot_bbe16_in14_END           (1)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_bbpslot_bbe16_in13_START         (2)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_bbpslot_bbe16_in13_END           (2)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_upacc_dsp_int_START              (3)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_upacc_dsp_int_END                (3)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_upacc_arm_int_START              (4)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_upacc_arm_int_END                (4)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_g1_int_bbp_to_dsp_32k_START      (5)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_g1_int_bbp_to_dsp_32k_END        (5)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_g1_int_bbp_to_dsp_START          (6)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_g1_int_bbp_to_dsp_END            (6)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_g2_int_bbp_to_dsp_32k_START      (7)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_g2_int_bbp_to_dsp_32k_END        (7)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_g2_int_bbp_to_dsp_START          (8)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_g2_int_bbp_to_dsp_END            (8)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_bbpcom_ctu_g1_arm_intr_START     (9)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_bbpcom_ctu_g1_arm_intr_END       (9)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_bbpcom_ctu_g2_arm_intr_START     (10)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_bbpcom_ctu_g2_arm_intr_END       (10)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_bbpcom_ctu_w_arm_intr_START      (11)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_bbpcom_ctu_w_arm_intr_END        (11)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_card1_0ms_intr_START        (12)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_card1_0ms_intr_END          (12)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_wdrx_slp_awk_sw_intr_START  (13)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_wdrx_slp_awk_sw_intr_END    (13)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_clk_sw_intr_START           (14)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_clk_sw_intr_END             (14)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_card2_0ms_intr_START        (15)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_card2_0ms_intr_END          (15)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_search_intr_START           (16)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_search_intr_END             (16)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_rake_intr_START             (17)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_rake_intr_END               (17)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_decode_intr_START           (18)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_decode_intr_END             (18)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_card1_time_intr_START       (19)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_card1_time_intr_END         (19)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_card2_time_intr_START       (20)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_card2_time_intr_END         (20)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_multi_search_intr_START     (21)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_multi_search_intr_END       (21)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_bbpmst_intr_START           (22)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_bbpmst_intr_END             (22)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_lte_dsp_warn_intr_START          (23)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_lte_dsp_warn_intr_END            (23)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_mwdt_bbe_intr_START              (24)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_mwdt_bbe_intr_END                (24)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_bbpmst_error_int_START           (25)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_bbpmst_error_int_END             (25)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_mtimer8_intc_START               (26)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_mtimer8_intc_END                 (26)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_mtimer9_intc_START               (27)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_mtimer9_intc_END                 (27)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_muart0_intr_START                (28)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_muart0_intr_END                  (28)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_uart3_intr_START                 (29)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_uart3_intr_END                   (29)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_uart0_intr_START                 (30)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_uart0_intr_END                   (30)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_UNION
 �ṹ˵��  : MDMSC_SECONDARY_INT_STATMSK �Ĵ����ṹ���塣��ַƫ����:0x0208����ֵ:0x00000000�����:32
 �Ĵ���˵��: ϵͳ�����ж����κ�Ĵ���������ָʾϵͳ�����ж�״̬�����κ󣩡���ӦbitΪ1��ʾ���жϣ�Ϊ0��ʾ���жϡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_secondary_int_mask_wbbp_otdoa_int2bbe        : 1;  /* bit[0] : wbbp_otdoa_int2bbe�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_mask_bbpslot_bbe16_in14        : 1;  /* bit[1] : bbpslot_bbe16_in14�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_mask_bbpslot_bbe16_in13        : 1;  /* bit[2] : bbpslot_bbe16_in13�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_mask_upacc_dsp_int             : 1;  /* bit[3] : UPACC�жϣ�upacc_dsp_int�� */
        unsigned int  sc_secondary_int_mask_upacc_arm_int             : 1;  /* bit[4] : UPACC�жϣ�upacc_arm_int�� */
        unsigned int  sc_secondary_int_mask_g1_int_bbp_to_dsp_32k     : 1;  /* bit[5] : g1_int_bbp_to_dsp_32k�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_mask_g1_int_bbp_to_dsp         : 1;  /* bit[6] : g1_int_bbp_to_dsp�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_mask_g2_int_bbp_to_dsp_32k     : 1;  /* bit[7] : g2_int_bbp_to_dsp_32k�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_mask_g2_int_bbp_to_dsp         : 1;  /* bit[8] : g2_int_bbp_to_dsp�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_mask_bbpcom_ctu_g1_arm_intr    : 1;  /* bit[9] : bbpcom_ctu_g1_arm_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_mask_bbpcom_ctu_g2_arm_intr    : 1;  /* bit[10]: bbpcom_ctu_g2_arm_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_mask_bbpcom_ctu_w_arm_intr     : 1;  /* bit[11]: bbpcom_ctu_w_arm_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_mask_wbbp_card1_0ms_intr       : 1;  /* bit[12]: wbbp_card1_0ms_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_mask_wbbp_wdrx_slp_awk_sw_intr : 1;  /* bit[13]: wbbp_wdrx_slp_awk_sw_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_mask_wbbp_clk_sw_intr          : 1;  /* bit[14]: wbbp_clk_sw_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_mask_wbbp_card2_0ms_intr       : 1;  /* bit[15]: wbbp_card2_0ms_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_mask_wbbp_search_intr          : 1;  /* bit[16]: wbbp_search_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_mask_wbbp_rake_intr            : 1;  /* bit[17]: wbbp_rake_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_mask_wbbp_decode_intr          : 1;  /* bit[18]: wbbp_decode_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_mask_wbbp_card1_time_intr      : 1;  /* bit[19]: wbbp_card1_time_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_mask_wbbp_card2_time_intr      : 1;  /* bit[20]: wbbp_card2_time_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_mask_wbbp_multi_search_intr    : 1;  /* bit[21]: wbbp_multi_search_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_mask_wbbp_bbpmst_intr          : 1;  /* bit[22]: wbbp_bbpmst_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_mask_lte_dsp_warn_intr         : 1;  /* bit[23]: lte_dsp_warn_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_mask_mwdt_bbe_intr             : 1;  /* bit[24]: mwdt_bbe_intr�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_mask_bbpmst_error_int          : 1;  /* bit[25]: bbpmst_error_int�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_mask_mtimer8_intc              : 1;  /* bit[26]: mtimer8_intc�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_mask_mtimer9_intc              : 1;  /* bit[27]: mtimer9_intc�͸�BBE16���ж� */
        unsigned int  sc_secondary_int_mask_muart0_intr               : 1;  /* bit[28]: Modem��uart0(CCPU/BBE16����)�ж� */
        unsigned int  sc_secondary_int_mask_uart3_intr                : 1;  /* bit[29]: AP��uart3��LTE/Connectivity���渴�ã��ж� */
        unsigned int  sc_secondary_int_mask_uart0_intr                : 1;  /* bit[30]: AP��uart0(���ڲ���У׼���������) �ж� */
        unsigned int  reserved                                        : 1;  /* bit[31]: ������ */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_otdoa_int2bbe_START         (0)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_otdoa_int2bbe_END           (0)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_bbpslot_bbe16_in14_START         (1)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_bbpslot_bbe16_in14_END           (1)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_bbpslot_bbe16_in13_START         (2)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_bbpslot_bbe16_in13_END           (2)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_upacc_dsp_int_START              (3)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_upacc_dsp_int_END                (3)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_upacc_arm_int_START              (4)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_upacc_arm_int_END                (4)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_g1_int_bbp_to_dsp_32k_START      (5)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_g1_int_bbp_to_dsp_32k_END        (5)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_g1_int_bbp_to_dsp_START          (6)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_g1_int_bbp_to_dsp_END            (6)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_g2_int_bbp_to_dsp_32k_START      (7)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_g2_int_bbp_to_dsp_32k_END        (7)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_g2_int_bbp_to_dsp_START          (8)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_g2_int_bbp_to_dsp_END            (8)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_bbpcom_ctu_g1_arm_intr_START     (9)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_bbpcom_ctu_g1_arm_intr_END       (9)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_bbpcom_ctu_g2_arm_intr_START     (10)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_bbpcom_ctu_g2_arm_intr_END       (10)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_bbpcom_ctu_w_arm_intr_START      (11)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_bbpcom_ctu_w_arm_intr_END        (11)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_card1_0ms_intr_START        (12)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_card1_0ms_intr_END          (12)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_wdrx_slp_awk_sw_intr_START  (13)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_wdrx_slp_awk_sw_intr_END    (13)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_clk_sw_intr_START           (14)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_clk_sw_intr_END             (14)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_card2_0ms_intr_START        (15)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_card2_0ms_intr_END          (15)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_search_intr_START           (16)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_search_intr_END             (16)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_rake_intr_START             (17)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_rake_intr_END               (17)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_decode_intr_START           (18)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_decode_intr_END             (18)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_card1_time_intr_START       (19)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_card1_time_intr_END         (19)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_card2_time_intr_START       (20)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_card2_time_intr_END         (20)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_multi_search_intr_START     (21)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_multi_search_intr_END       (21)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_bbpmst_intr_START           (22)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_bbpmst_intr_END             (22)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_lte_dsp_warn_intr_START          (23)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_lte_dsp_warn_intr_END            (23)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_mwdt_bbe_intr_START              (24)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_mwdt_bbe_intr_END                (24)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_bbpmst_error_int_START           (25)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_bbpmst_error_int_END             (25)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_mtimer8_intc_START               (26)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_mtimer8_intc_END                 (26)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_mtimer9_intc_START               (27)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_mtimer9_intc_END                 (27)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_muart0_intr_START                (28)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_muart0_intr_END                  (28)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_uart3_intr_START                 (29)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_uart3_intr_END                   (29)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_uart0_intr_START                 (30)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_uart0_intr_END                   (30)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_UNION
 �ṹ˵��  : MDMSC_CCPU_WKUP_INT_EN0 �Ĵ����ṹ���塣��ַƫ����:0x020C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ccpu�����ж��͸�mcu���ж�ʹ�ܼĴ���0�����ڶ�mcu�Ļ����жϽ����������á���ӦbitΪ1��ʾʹ����Ӧ�жϣ�Ϊ0��ʾ�����жϡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ccpu_wakeup_int_en0_usim0_detect_int   : 1;  /* bit[0] : [0] ��usim0�Ȳ�μ���ж� */
        unsigned int  ccpu_wakeup_int_en0_usim1_detect_int   : 1;  /* bit[1] : [1] ��usim1�Ȳ�μ���ж� */
        unsigned int  ccpu_wakeup_int_en0_GPIO2              : 1;  /* bit[2] : [2] ��GPIO2  */
        unsigned int  ccpu_wakeup_int_en0_mdmnoc_fault0_intr : 1;  /* bit[3] : [3] ��mdmnoc_fault0_intr */
        unsigned int  ccpu_wakeup_int_en0_mdmnoc_fault1_intr : 1;  /* bit[4] : [4] ��mdmnoc_fault1_intr */
        unsigned int  ccpu_wakeup_int_en0_ccpu_sftfiq_intr   : 1;  /* bit[5] : [5] ��ccpu_sftfiq_intr */
        unsigned int  reserved_0                             : 1;  /* bit[6] : [6] ������ */
        unsigned int  ccpu_wakeup_int_en0_GPIO7              : 1;  /* bit[7] : [7] ��GPIO7  */
        unsigned int  reserved_1                             : 1;  /* bit[8] : [8] ������ */
        unsigned int  ccpu_wakeup_int_en0_GPIO9              : 1;  /* bit[9] : [9] ��GPIO9 */
        unsigned int  reserved_2                             : 1;  /* bit[10]: [10]������ */
        unsigned int  reserved_3                             : 1;  /* bit[11]: [11]������ */
        unsigned int  reserved_4                             : 1;  /* bit[12]: [12]������ */
        unsigned int  reserved_5                             : 1;  /* bit[13]: [13]������ */
        unsigned int  ccpu_wakeup_int_en0_CSYSPWRUPREQ       : 1;  /* bit[14]: [14]��CSYSPWRUPREQ CoreSight system power up����״̬�źţ��߱�ʾ������Ч�� */
        unsigned int  ccpu_wakeup_int_en0_CDBGPWRUPREQ       : 1;  /* bit[15]: [15]��CDBGPWRUPREQ CoreSight debug power up����״̬�źţ��߱�ʾ������Ч�� */
        unsigned int  ccpu_wakeup_int_en0_OTG_WKP_STS        : 1;  /* bit[16]: [16]��OTG_WKP_STS  */
        unsigned int  ccpu_wakeup_int_en0_cbbp_intr01        : 1;  /* bit[17]: [17]��CDMA1x��CDMA EVDO˯��/�����ж�(32K) */
        unsigned int  ccpu_wakeup_int_en0_RTC_INT            : 1;  /* bit[18]: [18]��RTC_INT  */
        unsigned int  ccpu_wakeup_int_en0_MTimer0            : 1;  /* bit[19]: [19]��MTimer0 */
        unsigned int  ccpu_wakeup_int_en0_MTimer1            : 1;  /* bit[20]: [20]��MTimer1 */
        unsigned int  ccpu_wakeup_int_en0_MTimer2            : 1;  /* bit[21]: [21]��MTimer2 */
        unsigned int  ccpu_wakeup_int_en0_MTimer3            : 1;  /* bit[22]: [22]��MTimer3 */
        unsigned int  ccpu_wakeup_int_en0_MTimer4            : 1;  /* bit[23]: [23]��MTimer4 */
        unsigned int  ccpu_wakeup_int_en0_MTimer5            : 1;  /* bit[24]: [24]��MTimer5 */
        unsigned int  ccpu_wakeup_int_en0_MTimer6            : 1;  /* bit[25]: [25]��MTimer6 */
        unsigned int  ccpu_wakeup_int_en0_MTimer7            : 1;  /* bit[26]: [26]��MTimer7 */
        unsigned int  ccpu_wakeup_int_en0_MTimer8            : 1;  /* bit[27]: [27]��MTimer8 */
        unsigned int  ccpu_wakeup_int_en0_MTimer9            : 1;  /* bit[28]: [28]��MTimer9 */
        unsigned int  ccpu_wakeup_int_en0_MTimer10           : 1;  /* bit[29]: [29]��MTimer10 */
        unsigned int  ccpu_wakeup_int_en0_MTimer11           : 1;  /* bit[30]: [30]��MTimer11  */
        unsigned int  ccpu_wakeup_int_en0_MTimer12           : 1;  /* bit[31]: ��ӦCCPU�Ļ����ж�bit0��31�� 
                                                                               [31]��MTimer12  */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_usim0_detect_int_START    (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_usim0_detect_int_END      (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_usim1_detect_int_START    (1)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_usim1_detect_int_END      (1)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_GPIO2_START               (2)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_GPIO2_END                 (2)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_mdmnoc_fault0_intr_START  (3)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_mdmnoc_fault0_intr_END    (3)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_mdmnoc_fault1_intr_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_mdmnoc_fault1_intr_END    (4)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_ccpu_sftfiq_intr_START    (5)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_ccpu_sftfiq_intr_END      (5)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_GPIO7_START               (7)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_GPIO7_END                 (7)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_GPIO9_START               (9)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_GPIO9_END                 (9)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_CSYSPWRUPREQ_START        (14)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_CSYSPWRUPREQ_END          (14)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_CDBGPWRUPREQ_START        (15)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_CDBGPWRUPREQ_END          (15)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_OTG_WKP_STS_START         (16)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_OTG_WKP_STS_END           (16)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_cbbp_intr01_START         (17)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_cbbp_intr01_END           (17)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_RTC_INT_START             (18)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_RTC_INT_END               (18)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer0_START             (19)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer0_END               (19)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer1_START             (20)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer1_END               (20)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer2_START             (21)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer2_END               (21)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer3_START             (22)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer3_END               (22)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer4_START             (23)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer4_END               (23)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer5_START             (24)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer5_END               (24)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer6_START             (25)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer6_END               (25)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer7_START             (26)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer7_END               (26)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer8_START             (27)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer8_END               (27)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer9_START             (28)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer9_END               (28)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer10_START            (29)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer10_END              (29)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer11_START            (30)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer11_END              (30)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer12_START            (31)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer12_END              (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_UNION
 �ṹ˵��  : MDMSC_CCPU_WKUP_INT_STATRAW0 �Ĵ����ṹ���塣��ַƫ����:0x0210����ֵ:0x00000000�����:32
 �Ĵ���˵��: mcpu�����ж��͸�mcu��ԭʼ�����жϼĴ���������ָʾmcu��ԭʼ�����ж�״̬������ǰ������ӦbitΪ1��ʾ���жϣ�Ϊ0��ʾ���жϡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ccpu_wakeup_int_raw0_usim0_detect_int   : 1;  /* bit[0] : [0] ��usim0�Ȳ�μ���ж� */
        unsigned int  ccpu_wakeup_int_raw0_usim1_detect_int   : 1;  /* bit[1] : [1] ��usim1�Ȳ�μ���ж� */
        unsigned int  ccpu_wakeup_int_raw0_GPIO2              : 1;  /* bit[2] : [2] ��GPIO2  */
        unsigned int  ccpu_wakeup_int_raw0_mdmnoc_fault0_intr : 1;  /* bit[3] : [3] ��mdmnoc_fault0_intr */
        unsigned int  ccpu_wakeup_int_raw0_mdmnoc_fault1_intr : 1;  /* bit[4] : [4] ��mdmnoc_fault1_intr */
        unsigned int  ccpu_wakeup_int_raw0_ccpu_sftfiq_intr   : 1;  /* bit[5] : [5] ��ccpu_sftfiq_intr */
        unsigned int  reserved_0                              : 1;  /* bit[6] : [6] ������ */
        unsigned int  ccpu_wakeup_int_raw0_GPIO7              : 1;  /* bit[7] : [7] ��GPIO7  */
        unsigned int  reserved_1                              : 1;  /* bit[8] : [8] ������ */
        unsigned int  ccpu_wakeup_int_raw0_GPIO9              : 1;  /* bit[9] : [9] ��GPIO9 */
        unsigned int  reserved_2                              : 1;  /* bit[10]: [10]������ */
        unsigned int  reserved_3                              : 1;  /* bit[11]: [11]������ */
        unsigned int  reserved_4                              : 1;  /* bit[12]: [12]������ */
        unsigned int  reserved_5                              : 1;  /* bit[13]: [13]������ */
        unsigned int  ccpu_wakeup_int_raw0_CSYSPWRUPREQ       : 1;  /* bit[14]: [14]��CSYSPWRUPREQ CoreSight system power up����״̬�źţ��߱�ʾ������Ч�� */
        unsigned int  ccpu_wakeup_int_raw0_CDBGPWRUPREQ       : 1;  /* bit[15]: [15]��CDBGPWRUPREQ CoreSight debug power up����״̬�źţ��߱�ʾ������Ч�� */
        unsigned int  ccpu_wakeup_int_raw0_OTG_WKP_STS        : 1;  /* bit[16]: [16]��OTG_WKP_STS  */
        unsigned int  ccpu_wakeup_int_raw0_cbbp_intr01        : 1;  /* bit[17]: [17]��CDMA1x��CDMA EVDO˯��/�����ж�(32K) */
        unsigned int  ccpu_wakeup_int_raw0_RTC_INT            : 1;  /* bit[18]: [18]��RTC_INT  */
        unsigned int  ccpu_wakeup_int_raw0_MTimer0            : 1;  /* bit[19]: [19]��MTimer0 */
        unsigned int  ccpu_wakeup_int_raw0_MTimer1            : 1;  /* bit[20]: [20]��MTimer1 */
        unsigned int  ccpu_wakeup_int_raw0_MTimer2            : 1;  /* bit[21]: [21]��MTimer2 */
        unsigned int  ccpu_wakeup_int_raw0_MTimer3            : 1;  /* bit[22]: [22]��MTimer3 */
        unsigned int  ccpu_wakeup_int_raw0_MTimer4            : 1;  /* bit[23]: [23]��MTimer4 */
        unsigned int  ccpu_wakeup_int_raw0_MTimer5            : 1;  /* bit[24]: [24]��MTimer5 */
        unsigned int  ccpu_wakeup_int_raw0_MTimer6            : 1;  /* bit[25]: [25]��MTimer6 */
        unsigned int  ccpu_wakeup_int_raw0_MTimer7            : 1;  /* bit[26]: [26]��MTimer7 */
        unsigned int  ccpu_wakeup_int_raw0_MTimer8            : 1;  /* bit[27]: [27]��MTimer8 */
        unsigned int  ccpu_wakeup_int_raw0_MTimer9            : 1;  /* bit[28]: [28]��MTimer9 */
        unsigned int  ccpu_wakeup_int_raw0_MTimer10           : 1;  /* bit[29]: [29]��MTimer10 */
        unsigned int  ccpu_wakeup_int_raw0_MTimer11           : 1;  /* bit[30]: [30]��MTimer11  */
        unsigned int  ccpu_wakeup_int_raw0_MTimer12           : 1;  /* bit[31]: ��ӦCCPU�Ļ����ж�bit0��31�� 
                                                                                [31]��MTimer12  */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_usim0_detect_int_START    (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_usim0_detect_int_END      (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_usim1_detect_int_START    (1)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_usim1_detect_int_END      (1)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_GPIO2_START               (2)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_GPIO2_END                 (2)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_mdmnoc_fault0_intr_START  (3)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_mdmnoc_fault0_intr_END    (3)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_mdmnoc_fault1_intr_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_mdmnoc_fault1_intr_END    (4)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_ccpu_sftfiq_intr_START    (5)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_ccpu_sftfiq_intr_END      (5)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_GPIO7_START               (7)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_GPIO7_END                 (7)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_GPIO9_START               (9)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_GPIO9_END                 (9)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_CSYSPWRUPREQ_START        (14)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_CSYSPWRUPREQ_END          (14)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_CDBGPWRUPREQ_START        (15)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_CDBGPWRUPREQ_END          (15)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_OTG_WKP_STS_START         (16)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_OTG_WKP_STS_END           (16)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_cbbp_intr01_START         (17)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_cbbp_intr01_END           (17)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_RTC_INT_START             (18)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_RTC_INT_END               (18)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer0_START             (19)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer0_END               (19)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer1_START             (20)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer1_END               (20)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer2_START             (21)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer2_END               (21)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer3_START             (22)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer3_END               (22)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer4_START             (23)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer4_END               (23)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer5_START             (24)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer5_END               (24)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer6_START             (25)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer6_END               (25)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer7_START             (26)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer7_END               (26)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer8_START             (27)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer8_END               (27)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer9_START             (28)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer9_END               (28)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer10_START            (29)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer10_END              (29)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer11_START            (30)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer11_END              (30)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer12_START            (31)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer12_END              (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_UNION
 �ṹ˵��  : MDMSC_CCPU_WKUP_INT_STATMSK0 �Ĵ����ṹ���塣��ַƫ����:0x0214����ֵ:0x00000000�����:32
 �Ĵ���˵��: mcpu�����ж��͸�mcu�����κ����жϼĴ���������ָʾmcu�ĵ�ǰ�����ж�״̬�����κ󣩡���ӦbitΪ1��ʾ���жϣ�Ϊ0��ʾ���жϡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ccpu_wakeup_int_mask0_usim0_detect_int   : 1;  /* bit[0] : [0] ��usim0�Ȳ�μ���ж� */
        unsigned int  ccpu_wakeup_int_mask0_usim1_detect_int   : 1;  /* bit[1] : [1] ��usim1�Ȳ�μ���ж� */
        unsigned int  ccpu_wakeup_int_mask0_GPIO2              : 1;  /* bit[2] : [2] ��GPIO2  */
        unsigned int  ccpu_wakeup_int_mask0_mdmnoc_fault0_intr : 1;  /* bit[3] : [3] ��mdmnoc_fault0_intr */
        unsigned int  ccpu_wakeup_int_mask0_mdmnoc_fault1_intr : 1;  /* bit[4] : [4] ��mdmnoc_fault1_intr */
        unsigned int  ccpu_wakeup_int_mask0_ccpu_sftfiq_intr   : 1;  /* bit[5] : [5] ��ccpu_sftfiq_intr */
        unsigned int  reserved_0                               : 1;  /* bit[6] : [6] ������ */
        unsigned int  ccpu_wakeup_int_mask0_GPIO7              : 1;  /* bit[7] : [7] ��GPIO7  */
        unsigned int  reserved_1                               : 1;  /* bit[8] : [8] ������ */
        unsigned int  ccpu_wakeup_int_mask0_GPIO9              : 1;  /* bit[9] : [9] ��GPIO9 */
        unsigned int  reserved_2                               : 1;  /* bit[10]: [10]������ */
        unsigned int  reserved_3                               : 1;  /* bit[11]: [11]������ */
        unsigned int  reserved_4                               : 1;  /* bit[12]: [12]������ */
        unsigned int  reserved_5                               : 1;  /* bit[13]: [13]������ */
        unsigned int  ccpu_wakeup_int_mask0_CSYSPWRUPREQ       : 1;  /* bit[14]: [14]��CSYSPWRUPREQ CoreSight system power up����״̬�źţ��߱�ʾ������Ч�� */
        unsigned int  ccpu_wakeup_int_mask0_CDBGPWRUPREQ       : 1;  /* bit[15]: [15]��CDBGPWRUPREQ CoreSight debug power up����״̬�źţ��߱�ʾ������Ч�� */
        unsigned int  ccpu_wakeup_int_mask0_OTG_WKP_STS        : 1;  /* bit[16]: [16]��OTG_WKP_STS  */
        unsigned int  ccpu_wakeup_int_mask0_cbbp_intr01        : 1;  /* bit[17]: [17]��CDMA1x��CDMA EVDO˯��/�����ж�(32K) */
        unsigned int  ccpu_wakeup_int_mask0_RTC_INT            : 1;  /* bit[18]: [18]��RTC_INT  */
        unsigned int  ccpu_wakeup_int_mask0_MTimer0            : 1;  /* bit[19]: [19]��MTimer0 */
        unsigned int  ccpu_wakeup_int_mask0_MTimer1            : 1;  /* bit[20]: [20]��MTimer1 */
        unsigned int  ccpu_wakeup_int_mask0_MTimer2            : 1;  /* bit[21]: [21]��MTimer2 */
        unsigned int  ccpu_wakeup_int_mask0_MTimer3            : 1;  /* bit[22]: [22]��MTimer3 */
        unsigned int  ccpu_wakeup_int_mask0_MTimer4            : 1;  /* bit[23]: [23]��MTimer4 */
        unsigned int  ccpu_wakeup_int_mask0_MTimer5            : 1;  /* bit[24]: [24]��MTimer5 */
        unsigned int  ccpu_wakeup_int_mask0_MTimer6            : 1;  /* bit[25]: [25]��MTimer6 */
        unsigned int  ccpu_wakeup_int_mask0_MTimer7            : 1;  /* bit[26]: [26]��MTimer7 */
        unsigned int  ccpu_wakeup_int_mask0_MTimer8            : 1;  /* bit[27]: [27]��MTimer8 */
        unsigned int  ccpu_wakeup_int_mask0_MTimer9            : 1;  /* bit[28]: [28]��MTimer9 */
        unsigned int  ccpu_wakeup_int_mask0_MTimer10           : 1;  /* bit[29]: [29]��MTimer10 */
        unsigned int  ccpu_wakeup_int_mask0_MTimer11           : 1;  /* bit[30]: [30]��MTimer11  */
        unsigned int  ccpu_wakeup_int_mask0_MTimer12           : 1;  /* bit[31]: ��ӦCCPU�Ļ����ж�bit0��31�� 
                                                                                 [31]��MTimer12  */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_usim0_detect_int_START    (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_usim0_detect_int_END      (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_usim1_detect_int_START    (1)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_usim1_detect_int_END      (1)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_GPIO2_START               (2)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_GPIO2_END                 (2)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_mdmnoc_fault0_intr_START  (3)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_mdmnoc_fault0_intr_END    (3)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_mdmnoc_fault1_intr_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_mdmnoc_fault1_intr_END    (4)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_ccpu_sftfiq_intr_START    (5)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_ccpu_sftfiq_intr_END      (5)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_GPIO7_START               (7)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_GPIO7_END                 (7)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_GPIO9_START               (9)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_GPIO9_END                 (9)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_CSYSPWRUPREQ_START        (14)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_CSYSPWRUPREQ_END          (14)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_CDBGPWRUPREQ_START        (15)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_CDBGPWRUPREQ_END          (15)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_OTG_WKP_STS_START         (16)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_OTG_WKP_STS_END           (16)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_cbbp_intr01_START         (17)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_cbbp_intr01_END           (17)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_RTC_INT_START             (18)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_RTC_INT_END               (18)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer0_START             (19)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer0_END               (19)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer1_START             (20)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer1_END               (20)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer2_START             (21)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer2_END               (21)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer3_START             (22)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer3_END               (22)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer4_START             (23)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer4_END               (23)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer5_START             (24)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer5_END               (24)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer6_START             (25)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer6_END               (25)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer7_START             (26)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer7_END               (26)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer8_START             (27)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer8_END               (27)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer9_START             (28)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer9_END               (28)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer10_START            (29)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer10_END              (29)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer11_START            (30)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer11_END              (30)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer12_START            (31)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer12_END              (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_UNION
 �ṹ˵��  : MDMSC_CCPU_WKUP_INT_EN1 �Ĵ����ṹ���塣��ַƫ����:0x0218����ֵ:0x00000000�����:32
 �Ĵ���˵��: mcpu�����ж��͸�mcu�Ļ����ж�ʹ�ܼĴ��������ڶ�mcu�Ļ����жϽ����������á���ӦbitΪ1��ʾʹ����Ӧ�жϣ�Ϊ0��ʾ�����жϡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ccpu_wakeup_int_en1_MTimer13           : 1;  /* bit[0]    : [0] ��MTimer13 */
        unsigned int  ccpu_wakeup_int_en1_MTimer14           : 1;  /* bit[1]    : [1] ��MTimer14  */
        unsigned int  ccpu_wakeup_int_en1_MTimer15           : 1;  /* bit[2]    : [2] ��MTimer15  */
        unsigned int  ccpu_wakeup_int_en1_MTimer16           : 1;  /* bit[3]    : [3] ��MTimer16  */
        unsigned int  ccpu_wakeup_int_en1_MTimer17           : 1;  /* bit[4]    : [4] ��MTimer17  */
        unsigned int  ccpu_wakeup_int_en1_MTimer18           : 1;  /* bit[5]    : [5] ��MTimer18  */
        unsigned int  ccpu_wakeup_int_en1_MTimer19           : 1;  /* bit[6]    : [6] ��MTimer19 */
        unsigned int  ccpu_wakeup_int_en1_MWatchDog          : 1;  /* bit[7]    : [7] ��MWatchDog */
        unsigned int  ccpu_wakeup_int_en1_CCPU_WKUP_VOTE     : 1;  /* bit[8]    : [8] ��MCPU_WKUP_VOTE */
        unsigned int  ccpu_wakeup_int_en1_GBBP1WKUP          : 1;  /* bit[9]    : [9] ��GSM1 DRX�����ж� */
        unsigned int  ccpu_wakeup_int_en1_GBBP2WKUP          : 1;  /* bit[10]   : [10]��GSM2 DRX�����ж� */
        unsigned int  ccpu_wakeup_int_en1_WBBP1WKUP          : 1;  /* bit[11]   : [11]��WBBP�����ж�1  */
        unsigned int  ccpu_wakeup_int_en1_lte_arm_wakeup_int : 1;  /* bit[12]   : [12]��lte_arm_wakeup_int  */
        unsigned int  ccpu_wakeup_int_en1_tds_drx_arm_int1   : 1;  /* bit[13]   : [13]��tds_drx_arm_int1  */
        unsigned int  ccpu_wakeup_int_en1_IPC2CCPU_01        : 1;  /* bit[14]   : �ǰ�ȫIPC�����CCPU�ĺ˼��ж�0��ns_ipc_cpu_intr0[1]�� */
        unsigned int  ccpu_wakeup_int_en1_IPF_0              : 1;  /* bit[15]   : [15]��IPF_0 */
        unsigned int  ccpu_wakeup_int_en1_IPF_1              : 1;  /* bit[16]   : [16]��IPF_1 */
        unsigned int  ccpu_wakeup_int_en1_SOCP_0             : 1;  /* bit[17]   : [17]��SOCP_0 */
        unsigned int  ccpu_wakeup_int_en1_SOCP_1             : 1;  /* bit[18]   : [18]��SOCP_1 */
        unsigned int  ccpu_wakeup_int_en1_IPC2CCPU_06        : 1;  /* bit[19]   : �ǰ�ȫIPC�����CCPU�ĺ˼��ж�1��ns_ipc_cpu_intr0[6]�� */
        unsigned int  ccpu_wakeup_int_en1_SEC_IPC2CCPU_01    : 1;  /* bit[20]   : ��ȫIPC�����CCPU�ĺ˼��жϣ�s_ipc_cpu_intr0[1]�� */
        unsigned int  reserved                               : 11; /* bit[21-31]: ��ӦCCPU�Ļ����ж�bit32��52��
                                                                                  ���������� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_MTimer13_START            (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_MTimer13_END              (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_MTimer14_START            (1)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_MTimer14_END              (1)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_MTimer15_START            (2)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_MTimer15_END              (2)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_MTimer16_START            (3)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_MTimer16_END              (3)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_MTimer17_START            (4)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_MTimer17_END              (4)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_MTimer18_START            (5)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_MTimer18_END              (5)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_MTimer19_START            (6)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_MTimer19_END              (6)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_MWatchDog_START           (7)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_MWatchDog_END             (7)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_CCPU_WKUP_VOTE_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_CCPU_WKUP_VOTE_END        (8)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_GBBP1WKUP_START           (9)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_GBBP1WKUP_END             (9)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_GBBP2WKUP_START           (10)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_GBBP2WKUP_END             (10)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_WBBP1WKUP_START           (11)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_WBBP1WKUP_END             (11)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_lte_arm_wakeup_int_START  (12)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_lte_arm_wakeup_int_END    (12)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_tds_drx_arm_int1_START    (13)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_tds_drx_arm_int1_END      (13)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_IPC2CCPU_01_START         (14)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_IPC2CCPU_01_END           (14)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_IPF_0_START               (15)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_IPF_0_END                 (15)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_IPF_1_START               (16)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_IPF_1_END                 (16)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_SOCP_0_START              (17)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_SOCP_0_END                (17)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_SOCP_1_START              (18)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_SOCP_1_END                (18)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_IPC2CCPU_06_START         (19)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_IPC2CCPU_06_END           (19)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_SEC_IPC2CCPU_01_START     (20)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_SEC_IPC2CCPU_01_END       (20)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_UNION
 �ṹ˵��  : MDMSC_CCPU_WKUP_INT_STATRAW1 �Ĵ����ṹ���塣��ַƫ����:0x021C����ֵ:0x00000000�����:32
 �Ĵ���˵��: mcpu�����ж��͸�mcu��ԭʼ�����жϼĴ���������ָʾmcu��ԭʼ�����ж�״̬������ǰ����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ccpu_wakeup_int_raw1_MTimer13           : 1;  /* bit[0]    : [0] ��MTimer13 */
        unsigned int  ccpu_wakeup_int_raw1_MTimer14           : 1;  /* bit[1]    : [1] ��MTimer14  */
        unsigned int  ccpu_wakeup_int_raw1_MTimer15           : 1;  /* bit[2]    : [2] ��MTimer15  */
        unsigned int  ccpu_wakeup_int_raw1_MTimer16           : 1;  /* bit[3]    : [3] ��MTimer16  */
        unsigned int  ccpu_wakeup_int_raw1_MTimer17           : 1;  /* bit[4]    : [4] ��MTimer17  */
        unsigned int  ccpu_wakeup_int_raw1_MTimer18           : 1;  /* bit[5]    : [5] ��MTimer18  */
        unsigned int  ccpu_wakeup_int_raw1_MTimer19           : 1;  /* bit[6]    : [6] ��MTimer19 */
        unsigned int  ccpu_wakeup_int_raw1_MWatchDog          : 1;  /* bit[7]    : [7] ��MWatchDog */
        unsigned int  ccpu_wakeup_int_raw1_CCPU_WKUP_VOTE     : 1;  /* bit[8]    : [8] ��MCPU_WKUP_VOTE */
        unsigned int  ccpu_wakeup_int_raw1_GBBP1WKUP          : 1;  /* bit[9]    : [9] ��GSM1 DRX�����ж� */
        unsigned int  ccpu_wakeup_int_raw1_GBBP2WKUP          : 1;  /* bit[10]   : [10]��GSM2 DRX�����ж� */
        unsigned int  ccpu_wakeup_int_raw1_WBBP1WKUP          : 1;  /* bit[11]   : [11]��WBBP�����ж�1  */
        unsigned int  ccpu_wakeup_int_raw1_lte_arm_wakeup_int : 1;  /* bit[12]   : [12]��lte_arm_wakeup_int  */
        unsigned int  ccpu_wakeup_int_raw1_tds_drx_arm_int1   : 1;  /* bit[13]   : [13]��tds_drx_arm_int1  */
        unsigned int  ccpu_wakeup_int_raw1_IPC2CCPU_01        : 1;  /* bit[14]   : �ǰ�ȫIPC�����CCPU�ĺ˼��ж�0��ns_ipc_cpu_intr0[1]�� */
        unsigned int  ccpu_wakeup_int_raw1_IPF_0              : 1;  /* bit[15]   : [15]��IPF_0 */
        unsigned int  ccpu_wakeup_int_raw1_IPF_1              : 1;  /* bit[16]   : [16]��IPF_1 */
        unsigned int  ccpu_wakeup_int_raw1_SOCP_0             : 1;  /* bit[17]   : [17]��SOCP_0 */
        unsigned int  ccpu_wakeup_int_raw1_SOCP_1             : 1;  /* bit[18]   : [18]��SOCP_1 */
        unsigned int  ccpu_wakeup_int_raw1_IPC2CCPU_06        : 1;  /* bit[19]   : �ǰ�ȫIPC�����CCPU�ĺ˼��ж�1��ns_ipc_cpu_intr0[6]�� */
        unsigned int  ccpu_wakeup_int_raw1_SEC_IPC2CCPU_01    : 1;  /* bit[20]   : ��ȫIPC�����CCPU�ĺ˼��жϣ�s_ipc_cpu_intr0[1]�� */
        unsigned int  reserved                                : 11; /* bit[21-31]: ��ӦCCPU�Ļ����ж�bit32��52��
                                                                                   ���������� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_MTimer13_START            (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_MTimer13_END              (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_MTimer14_START            (1)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_MTimer14_END              (1)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_MTimer15_START            (2)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_MTimer15_END              (2)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_MTimer16_START            (3)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_MTimer16_END              (3)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_MTimer17_START            (4)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_MTimer17_END              (4)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_MTimer18_START            (5)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_MTimer18_END              (5)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_MTimer19_START            (6)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_MTimer19_END              (6)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_MWatchDog_START           (7)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_MWatchDog_END             (7)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_CCPU_WKUP_VOTE_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_CCPU_WKUP_VOTE_END        (8)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_GBBP1WKUP_START           (9)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_GBBP1WKUP_END             (9)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_GBBP2WKUP_START           (10)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_GBBP2WKUP_END             (10)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_WBBP1WKUP_START           (11)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_WBBP1WKUP_END             (11)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_lte_arm_wakeup_int_START  (12)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_lte_arm_wakeup_int_END    (12)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_tds_drx_arm_int1_START    (13)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_tds_drx_arm_int1_END      (13)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_IPC2CCPU_01_START         (14)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_IPC2CCPU_01_END           (14)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_IPF_0_START               (15)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_IPF_0_END                 (15)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_IPF_1_START               (16)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_IPF_1_END                 (16)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_SOCP_0_START              (17)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_SOCP_0_END                (17)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_SOCP_1_START              (18)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_SOCP_1_END                (18)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_IPC2CCPU_06_START         (19)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_IPC2CCPU_06_END           (19)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_SEC_IPC2CCPU_01_START     (20)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_SEC_IPC2CCPU_01_END       (20)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_UNION
 �ṹ˵��  : MDMSC_CCPU_WKUP_INT_STATMSK1 �Ĵ����ṹ���塣��ַƫ����:0x0220����ֵ:0x00000000�����:32
 �Ĵ���˵��: mcpu�����ж��͸�mcu�����κ����жϼĴ���������ָʾmcu�ĵ�ǰ�����ж�״̬�����κ󣩡�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ccpu_wakeup_int_mask1_MTimer13           : 1;  /* bit[0]    : [0] ��MTimer13 */
        unsigned int  ccpu_wakeup_int_mask1_MTimer14           : 1;  /* bit[1]    : [1] ��MTimer14  */
        unsigned int  ccpu_wakeup_int_mask1_MTimer15           : 1;  /* bit[2]    : [2] ��MTimer15  */
        unsigned int  ccpu_wakeup_int_mask1_MTimer16           : 1;  /* bit[3]    : [3] ��MTimer16  */
        unsigned int  ccpu_wakeup_int_mask1_MTimer17           : 1;  /* bit[4]    : [4] ��MTimer17  */
        unsigned int  ccpu_wakeup_int_mask1_MTimer18           : 1;  /* bit[5]    : [5] ��MTimer18  */
        unsigned int  ccpu_wakeup_int_mask1_MTimer19           : 1;  /* bit[6]    : [6] ��MTimer19 */
        unsigned int  ccpu_wakeup_int_mask1_MWatchDog          : 1;  /* bit[7]    : [7] ��MWatchDog */
        unsigned int  ccpu_wakeup_int_mask1_CCPU_WKUP_VOTE     : 1;  /* bit[8]    : [8] ��CCPU_WKUP_VOTE */
        unsigned int  ccpu_wakeup_int_mask1_GBBP1WKUP          : 1;  /* bit[9]    : [9] ��GSM1 DRX�����ж� */
        unsigned int  ccpu_wakeup_int_mask1_GBBP2WKUP          : 1;  /* bit[10]   : [10]��GSM2 DRX�����ж� */
        unsigned int  ccpu_wakeup_int_mask1_WBBP1WKUP          : 1;  /* bit[11]   : [11]��WBBP�����ж�1  */
        unsigned int  ccpu_wakeup_int_mask1_lte_arm_wakeup_int : 1;  /* bit[12]   : [12]��lte_arm_wakeup_int  */
        unsigned int  ccpu_wakeup_int_mask1_tds_drx_arm_int1   : 1;  /* bit[13]   : [13]��tds_drx_arm_int1  */
        unsigned int  ccpu_wakeup_int_mask1_IPC2CCPU_01        : 1;  /* bit[14]   : �ǰ�ȫIPC�����CCPU�ĺ˼��ж�0��ns_ipc_cpu_intr0[1]�� */
        unsigned int  ccpu_wakeup_int_mask1_IPF_0              : 1;  /* bit[15]   : [15]��IPF_0 */
        unsigned int  ccpu_wakeup_int_mask1_IPF_1              : 1;  /* bit[16]   : [16]��IPF_1 */
        unsigned int  ccpu_wakeup_int_mask1_SOCP_0             : 1;  /* bit[17]   : [17]��SOCP_0 */
        unsigned int  ccpu_wakeup_int_mask1_SOCP_1             : 1;  /* bit[18]   : [18]��SOCP_1 */
        unsigned int  ccpu_wakeup_int_mask1_IPC2CCPU_06        : 1;  /* bit[19]   : �ǰ�ȫIPC�����CCPU�ĺ˼��ж�1��ns_ipc_cpu_intr0[6]�� */
        unsigned int  ccpu_wakeup_int_mask1_SEC_IPC2CCPU_01    : 1;  /* bit[20]   : ��ȫIPC�����CCPU�ĺ˼��жϣ�s_ipc_cpu_intr0[1]�� */
        unsigned int  ccpu_wakeup_int_mask1                    : 11; /* bit[21-31]: ��ӦCCPU�Ļ����ж�bit32��52��
                                                                                    ���������� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_MTimer13_START            (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_MTimer13_END              (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_MTimer14_START            (1)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_MTimer14_END              (1)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_MTimer15_START            (2)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_MTimer15_END              (2)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_MTimer16_START            (3)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_MTimer16_END              (3)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_MTimer17_START            (4)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_MTimer17_END              (4)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_MTimer18_START            (5)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_MTimer18_END              (5)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_MTimer19_START            (6)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_MTimer19_END              (6)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_MWatchDog_START           (7)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_MWatchDog_END             (7)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_CCPU_WKUP_VOTE_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_CCPU_WKUP_VOTE_END        (8)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_GBBP1WKUP_START           (9)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_GBBP1WKUP_END             (9)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_GBBP2WKUP_START           (10)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_GBBP2WKUP_END             (10)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_WBBP1WKUP_START           (11)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_WBBP1WKUP_END             (11)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_lte_arm_wakeup_int_START  (12)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_lte_arm_wakeup_int_END    (12)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_tds_drx_arm_int1_START    (13)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_tds_drx_arm_int1_END      (13)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_IPC2CCPU_01_START         (14)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_IPC2CCPU_01_END           (14)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_IPF_0_START               (15)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_IPF_0_END                 (15)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_IPF_1_START               (16)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_IPF_1_END                 (16)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_SOCP_0_START              (17)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_SOCP_0_END                (17)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_SOCP_1_START              (18)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_SOCP_1_END                (18)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_IPC2CCPU_06_START         (19)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_IPC2CCPU_06_END           (19)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_SEC_IPC2CCPU_01_START     (20)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_SEC_IPC2CCPU_01_END       (20)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_START                     (21)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_END                       (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_INT_RAW_STAT_UNION
 �ṹ˵��  : MDMSC_INT_RAW_STAT �Ĵ����ṹ���塣��ַƫ����:0x0224����ֵ:0x00000000�����:32
 �Ĵ���˵��: ԭʼ�ڲ��жϼĴ���������ָʾSC�ڲ���ԭʼ�ж�״̬(����ǰ)����ӦbitΪ1��ʾ���жϣ�Ϊ0��ʾ���ж�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mdmsc_int_statr_bbe16_mwtd_intr_req : 1;  /* bit[0]   : BBE16 watchdog ��λ�����жϣ��͸�CCPU */
        unsigned int  mdmsc_int_statr_ccpu_mwtd_intr_req  : 1;  /* bit[1]   : ccpu watchdog ��λ�����жϣ��͸�MCU/ACPU */
        unsigned int  reserved                            : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_INT_RAW_STAT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_INT_RAW_STAT_mdmsc_int_statr_bbe16_mwtd_intr_req_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_RAW_STAT_mdmsc_int_statr_bbe16_mwtd_intr_req_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_RAW_STAT_mdmsc_int_statr_ccpu_mwtd_intr_req_START   (1)
#define SOC_MODEM_SCTRL_MDMSC_INT_RAW_STAT_mdmsc_int_statr_ccpu_mwtd_intr_req_END     (1)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_INT_MASK_STAT_UNION
 �ṹ˵��  : MDMSC_INT_MASK_STAT �Ĵ����ṹ���塣��ַƫ����:0x0228����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���κ��ڲ��жϼĴ���������ָʾSC��ǰ�ڲ��ж�״̬(���κ�)����ӦbitΪ1��ʾ���жϣ�Ϊ0��ʾ���ж�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mdmsc_int_statm_bbe16_mwtd_intr_req : 1;  /* bit[0]   : BBE16 watchdog ��λ�����жϣ��͸�CCPU */
        unsigned int  mdmsc_int_statm_ccpu_mwtd_intr_req  : 1;  /* bit[1]   : ccpu watchdog ��λ�����жϣ��͸�MCU/ACPU */
        unsigned int  reserved                            : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_INT_MASK_STAT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_INT_MASK_STAT_mdmsc_int_statm_bbe16_mwtd_intr_req_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_MASK_STAT_mdmsc_int_statm_bbe16_mwtd_intr_req_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_MASK_STAT_mdmsc_int_statm_ccpu_mwtd_intr_req_START   (1)
#define SOC_MODEM_SCTRL_MDMSC_INT_MASK_STAT_mdmsc_int_statm_ccpu_mwtd_intr_req_END     (1)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_INT_CLEAR_UNION
 �ṹ˵��  : MDMSC_INT_CLEAR �Ĵ����ṹ���塣��ַƫ����:0x022C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ڲ��ж�����Ĵ���������Ӧ�жϱ���λд1����ʾ�����Ӧ���ж�״̬������ԭʼ�ڲ��жϼĴ��������κ��ڲ��жϼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mdmsc_int_clear_bbe16_mwtd_intr_req : 1;  /* bit[0]   : BBE16 watchdog ��λ�����жϣ��͸�CCPU */
        unsigned int  mdmsc_int_clear_ccpu_mwtd_intr_req  : 1;  /* bit[1]   : ccpu watchdog ��λ�����жϣ��͸�MCU/ACPU */
        unsigned int  reserved                            : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_INT_CLEAR_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_INT_CLEAR_mdmsc_int_clear_bbe16_mwtd_intr_req_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_CLEAR_mdmsc_int_clear_bbe16_mwtd_intr_req_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_CLEAR_mdmsc_int_clear_ccpu_mwtd_intr_req_START   (1)
#define SOC_MODEM_SCTRL_MDMSC_INT_CLEAR_mdmsc_int_clear_ccpu_mwtd_intr_req_END     (1)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_INT_EN_UNION
 �ṹ˵��  : MDMSC_INT_EN �Ĵ����ṹ���塣��ַƫ����:0x0230����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ڲ��ж����μĴ������Ա���д1�������Σ�д0��Ӱ�����ε�״̬
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mdmsc_int_en_bbe16_mwtd_intr_req : 1;  /* bit[0]   : BBE16 watchdog ��λ�����жϣ��͸�CCPU */
        unsigned int  mdmsc_int_en_ccpu_mwtd_intr_req  : 1;  /* bit[1]   : ccpu watchdog ��λ�����жϣ��͸�MCU/ACPU */
        unsigned int  reserved                         : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_INT_EN_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_INT_EN_mdmsc_int_en_bbe16_mwtd_intr_req_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_EN_mdmsc_int_en_bbe16_mwtd_intr_req_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_EN_mdmsc_int_en_ccpu_mwtd_intr_req_START   (1)
#define SOC_MODEM_SCTRL_MDMSC_INT_EN_mdmsc_int_en_ccpu_mwtd_intr_req_END     (1)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_INT_DIS_UNION
 �ṹ˵��  : MDMSC_INT_DIS �Ĵ����ṹ���塣��ַƫ����:0x0234����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ڲ��ж����μĴ������Ա���д1����ֹ���Σ�д0��Ӱ��ʱ�����ε�״̬
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mdmsc_int_dis_bbe16_mwtd_intr_req : 1;  /* bit[0]   : BBE16 watchdog ��λ�����жϣ��͸�CCPU */
        unsigned int  mdmsc_int_dis_ccpu_mwtd_intr_req  : 1;  /* bit[1]   : ccpu watchdog ��λ�����жϣ��͸�MCU/ACPU */
        unsigned int  reserved                          : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_INT_DIS_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_INT_DIS_mdmsc_int_dis_bbe16_mwtd_intr_req_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_DIS_mdmsc_int_dis_bbe16_mwtd_intr_req_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_DIS_mdmsc_int_dis_ccpu_mwtd_intr_req_START   (1)
#define SOC_MODEM_SCTRL_MDMSC_INT_DIS_mdmsc_int_dis_ccpu_mwtd_intr_req_END     (1)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_INT_EN_STAT_UNION
 �ṹ˵��  : MDMSC_INT_EN_STAT �Ĵ����ṹ���塣��ַƫ����:0x0238����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ڲ��ж�ʹ�ܼĴ���������SC�ڲ��жϵ��������á���ӦbitΪ1��ʾʹ����Ӧ�жϣ�Ϊ0��ʾ�����ж�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mdmsc_int_en_sta_bbe16_mwtd_intr_req : 1;  /* bit[0]   : BBE16 watchdog ��λ�����жϣ��͸�CCPU */
        unsigned int  mdmsc_int_en_sta_ccpu_mwtd_intr_req  : 1;  /* bit[1]   : ccpu watchdog ��λ�����жϣ��͸�MCU/ACPU */
        unsigned int  reserved                             : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_INT_EN_STAT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_INT_EN_STAT_mdmsc_int_en_sta_bbe16_mwtd_intr_req_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_EN_STAT_mdmsc_int_en_sta_bbe16_mwtd_intr_req_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_EN_STAT_mdmsc_int_en_sta_ccpu_mwtd_intr_req_START   (1)
#define SOC_MODEM_SCTRL_MDMSC_INT_EN_STAT_mdmsc_int_en_sta_ccpu_mwtd_intr_req_END     (1)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_UNION
 �ṹ˵��  : MDMSC_INT_COUNT_EN0 �Ĵ����ṹ���塣��ַƫ����:0x0250����ֵ:0x00000000�����:32
 �Ĵ���˵��: �жϼ���ʹ�ܼĴ������������ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_int_count_en0  : 1;  /* bit[0] : GUBBP VOMOS�ж� count enable 1:enable 0:disable */
        unsigned int  sc_int_count_en1  : 1;  /* bit[1] : WBBP�ж�10 count enable
                                                          ��wbbp_bbpmst_intr��
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en2  : 1;  /* bit[2] : WBBP�ж�9 count enable
                                                          ��wbbp_multi_search_intr��
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en3  : 1;  /* bit[3] : WBBP�ж�8 count enable
                                                          ��wbbp_card2_time_intr��
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en4  : 1;  /* bit[4] : WBBP�ж�7 count enable
                                                          ��wbbp_card1_time_intr��
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en5  : 1;  /* bit[5] : WBBP�ж�6 count enable
                                                          ��wbbp_decode_intr��
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en6  : 1;  /* bit[6] : WBBP�ж�5 count enable
                                                          ��wbbp_rake_intr��
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en7  : 1;  /* bit[7] : WBBP�ж�4 count enable
                                                          ��wbbp_search_intr��
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en8  : 1;  /* bit[8] : WBBP�ж�3 count enable
                                                          ��wbbp_card2_0ms_intr��
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en9  : 1;  /* bit[9] : WBBP�ж�2 count enable
                                                          ��wbbp_clk_sw_intr��
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en10 : 1;  /* bit[10]: WBBP�ж�1 count enable
                                                          ��wbbp_wdrx_slp_awk_sw_intr��
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en11 : 1;  /* bit[11]: WBBP�ж�0 count enable
                                                          ��wbbp_card1_0ms_intr��
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en12 : 1;  /* bit[12]: GBBP�ж�3 count enable
                                                          ��g1_int_bbp_to_dsp_32k��
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en13 : 1;  /* bit[13]: GBBP�ж�2 count enable
                                                          ��g1_int_bbp_to_dsp��
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en14 : 1;  /* bit[14]: GBBP�ж�1 count enable
                                                          ��g1_int_bbp_to_cpu_32k��
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en15 : 1;  /* bit[15]: GBBP�ж�0 count enable
                                                          ��g1_int_bbp_to_cpu��
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en16 : 1;  /* bit[16]: CTU_W2ARM�ж� count enable 
                                                          (bbpcom_ctu_w_arm_intr)
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en17 : 1;  /* bit[17]: CTU_G2ARM�ж� count enable 
                                                          (bbpcom_ctu_g1_arm_intr)
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en18 : 1;  /* bit[18]: GU_Cipher_intr[1] count enable 
                                                          (gucipher0_arm_dl_intr)
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en19 : 1;  /* bit[19]: GU_Cipher_intr[0] count enable 
                                                          (gucipher0_arm_ul_intr)
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en20 : 1;  /* bit[20]: UPACC_intr[1] count enable
                                                          (upacc_dsp_intr)
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en21 : 1;  /* bit[21]: UPACC_intr[0] count enable
                                                          (upacc_arm_intr)
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en22 : 1;  /* bit[22]: IPC2CCPU_1 count enable 
                                                          (ipc_ns_lock_intr[1])
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en23 : 1;  /* bit[23]: IPC2CCPU_0 count enable 
                                                          (ipc_ns_inner_core_intr[1])
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en24 : 1;  /* bit[24]: MEDMAC1 count enable 
                                                          (mdmdmac_s_intr[1])
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en25 : 1;  /* bit[25]: SOCP_intr[1] count enable 
                                                          (socp_intr[1])
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en26 : 1;  /* bit[26]: SOCP_intr[0] count enable 
                                                          (socp_intr[0])
                                                          1:enable 0:disable  */
        unsigned int  reserved_0        : 1;  /* bit[27]: ���� */
        unsigned int  reserved_1        : 1;  /* bit[28]: ���� */
        unsigned int  sc_int_count_en29 : 1;  /* bit[29]: GBBP2�ж�3 GSM2 DRX�ж�(g2_int_bbp_to_dsp_32k) */
        unsigned int  sc_int_count_en30 : 1;  /* bit[30]: GBBP2�ж�2 GSM2��DRX�ж�1(g2_int_bbp_to_dsp) */
        unsigned int  sc_int_count_en31 : 1;  /* bit[31]: GBBP2�ж�1 GSM2Ԥ��
                                                          (g2_int_bbp_to_cpu_32k) */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en0_START   (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en0_END     (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en1_START   (1)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en1_END     (1)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en2_START   (2)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en2_END     (2)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en3_START   (3)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en3_END     (3)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en4_START   (4)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en4_END     (4)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en5_START   (5)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en5_END     (5)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en6_START   (6)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en6_END     (6)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en7_START   (7)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en7_END     (7)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en8_START   (8)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en8_END     (8)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en9_START   (9)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en9_END     (9)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en10_START  (10)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en10_END    (10)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en11_START  (11)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en11_END    (11)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en12_START  (12)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en12_END    (12)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en13_START  (13)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en13_END    (13)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en14_START  (14)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en14_END    (14)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en15_START  (15)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en15_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en16_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en16_END    (16)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en17_START  (17)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en17_END    (17)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en18_START  (18)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en18_END    (18)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en19_START  (19)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en19_END    (19)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en20_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en20_END    (20)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en21_START  (21)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en21_END    (21)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en22_START  (22)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en22_END    (22)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en23_START  (23)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en23_END    (23)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en24_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en24_END    (24)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en25_START  (25)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en25_END    (25)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en26_START  (26)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en26_END    (26)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en29_START  (29)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en29_END    (29)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en30_START  (30)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en30_END    (30)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en31_START  (31)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en31_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_UNION
 �ṹ˵��  : MDMSC_INT_COUNT_EN1 �Ĵ����ṹ���塣��ַƫ����:0x0254����ֵ:0x00000000�����:32
 �Ĵ���˵��: �жϼ���ʹ�ܼĴ������������ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_int_count_en32 : 1;  /* bit[0] : GBBP2�ж�0 GSM2��DRX�ж�0(g2_int_bbp_to_cpu) */
        unsigned int  sc_int_count_en33 : 1;  /* bit[1] : CTU_G2toARM�ж� BBP COMMON CTU_GBBP2 to ARM�ж�
                                                          (bbpcom_ctu_g2_arm_intr) */
        unsigned int  sc_int_count_en34 : 1;  /* bit[2] : IPC2CCPU_2 IPC�����CCPU�ĺ˼��ж�1��ipc_ns_inner_core_intr[6]�� */
        unsigned int  sc_int_count_en35 : 1;  /* bit[3] : ��ȫIPC�����CCPU����Դ���жϣ�ipc_s_lock_intr[1]�� */
        unsigned int  sc_int_count_en36 : 1;  /* bit[4] : ��ȫIPC�����CCPU�ĺ˼��ж�(ipc_s_inner_core_intr[1]�� */
        unsigned int  sc_int_count_en37 : 1;  /* bit[5] : TDSģʱ����ʾtds hsupaģ������ж�tds_hsupa_intr��Cģʱ����ʾCDMA1x��CDMA EVDO˯��/�����ж�(32K)cbbp_intr01.
                                                          (tcbbp_intr01) */
        unsigned int  sc_int_count_en38 : 1;  /* bit[6] : TDSģʱ����ʾtds harqģ������ж�tds_harq_intr��Cģʱ����ʾCDMA1x��CDMA EVDOʱ���л��ж�(imiʱ��)cbbp_intr02.
                                                          (tcbbp_intr02) */
        unsigned int  sc_int_count_en39 : 1;  /* bit[7] : TDSģʱ����ʾtds turboģ������ж�tds_turbo_intr��Cģʱ����ʾCDMA1x��CDMA EVDO�ྶ����/С�������ж�cbbp_intr03.
                                                          (tcbbp_intr03) */
        unsigned int  sc_int_count_en40 : 1;  /* bit[8] : TDSģʱ����ʾtds viterbiģ������ж�tds_viterbi_intr��Cģʱ����ʾCDMA1x��CDMA EVDO��ʱ�ж�cbbp_intr04.
                                                          (tcbbp_intr04) */
        unsigned int  sc_int_count_en41 : 1;  /* bit[9] : TDSģʱ����ʾtdsǰ��ģ���ж�tds_fpu_intr��Cģʱ����ʾCDMA1x��CDMA EVDO����/�����ж�cbbp_intr05.
                                                          (tcbbp_intr05) */
        unsigned int  sc_int_count_en42 : 1;  /* bit[10]: TDSģʱ����ʾtds��Ƶǰ���ж�tds_rfc_intr��Cģʱ����ʾCDMA1x��CDMA EVDO��Ƶ�ϱ�/���ݰ����ж�cbbp_intr06.
                                                          (tcbbp_intr06) */
        unsigned int  sc_int_count_en43 : 1;  /* bit[11]: ������ */
        unsigned int  sc_int_count_en44 : 1;  /* bit[12]: ������ */
        unsigned int  sc_int_count_en45 : 1;  /* bit[13]: ������ */
        unsigned int  sc_int_count_en46 : 1;  /* bit[14]: ������ */
        unsigned int  sc_int_count_en47 : 1;  /* bit[15]: ������ */
        unsigned int  sc_int_count_en48 : 1;  /* bit[16]: ������ */
        unsigned int  sc_int_count_en49 : 1;  /* bit[17]: ������ */
        unsigned int  sc_int_count_en50 : 1;  /* bit[18]: ������ */
        unsigned int  sc_int_count_en51 : 1;  /* bit[19]: ������ */
        unsigned int  sc_int_count_en52 : 1;  /* bit[20]: ������ */
        unsigned int  sc_int_count_en53 : 1;  /* bit[21]: ������ */
        unsigned int  sc_int_count_en54 : 1;  /* bit[22]: ������ */
        unsigned int  sc_int_count_en55 : 1;  /* bit[23]: ������ */
        unsigned int  sc_int_count_en56 : 1;  /* bit[24]: ������ */
        unsigned int  sc_int_count_en57 : 1;  /* bit[25]: ������ */
        unsigned int  sc_int_count_en58 : 1;  /* bit[26]: ������ */
        unsigned int  sc_int_count_en59 : 1;  /* bit[27]: ������ */
        unsigned int  sc_int_count_en60 : 1;  /* bit[28]: ������ */
        unsigned int  sc_int_count_en61 : 1;  /* bit[29]: ������ */
        unsigned int  sc_int_count_en62 : 1;  /* bit[30]: ������ */
        unsigned int  sc_int_count_en63 : 1;  /* bit[31]: ������ */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en32_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en32_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en33_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en33_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en34_START  (2)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en34_END    (2)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en35_START  (3)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en35_END    (3)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en36_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en36_END    (4)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en37_START  (5)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en37_END    (5)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en38_START  (6)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en38_END    (6)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en39_START  (7)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en39_END    (7)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en40_START  (8)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en40_END    (8)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en41_START  (9)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en41_END    (9)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en42_START  (10)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en42_END    (10)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en43_START  (11)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en43_END    (11)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en44_START  (12)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en44_END    (12)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en45_START  (13)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en45_END    (13)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en46_START  (14)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en46_END    (14)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en47_START  (15)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en47_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en48_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en48_END    (16)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en49_START  (17)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en49_END    (17)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en50_START  (18)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en50_END    (18)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en51_START  (19)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en51_END    (19)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en52_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en52_END    (20)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en53_START  (21)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en53_END    (21)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en54_START  (22)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en54_END    (22)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en55_START  (23)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en55_END    (23)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en56_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en56_END    (24)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en57_START  (25)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en57_END    (25)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en58_START  (26)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en58_END    (26)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en59_START  (27)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en59_END    (27)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en60_START  (28)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en60_END    (28)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en61_START  (29)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en61_END    (29)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en62_START  (30)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en62_END    (30)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en63_START  (31)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en63_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_UNION
 �ṹ˵��  : MDMSC_INT_COUNT_STAT0 �Ĵ����ṹ���塣��ַƫ����:0x0258����ֵ:0x00000000�����:32
 �Ĵ���˵��: �жϼ���״̬�Ĵ���0������������ԡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_int_count_sta0 : 4;  /* bit[0-3]  : GUBBP VOMOS�ж� count number */
        unsigned int  sc_int_count_sta1 : 4;  /* bit[4-7]  : WBBP�ж�10 count number */
        unsigned int  sc_int_count_sta2 : 4;  /* bit[8-11] : WBBP�ж�9 count number */
        unsigned int  sc_int_count_sta3 : 4;  /* bit[12-15]: WBBP�ж�8 count number */
        unsigned int  sc_int_count_sta4 : 4;  /* bit[16-19]: WBBP�ж�7 count number */
        unsigned int  sc_int_count_sta5 : 4;  /* bit[20-23]: WBBP�ж�6 count number */
        unsigned int  sc_int_count_sta6 : 4;  /* bit[24-27]: WBBP�ж�5 count number */
        unsigned int  sc_int_count_sta7 : 4;  /* bit[28-31]: WBBP�ж�4 count number */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_sc_int_count_sta0_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_sc_int_count_sta0_END    (3)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_sc_int_count_sta1_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_sc_int_count_sta1_END    (7)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_sc_int_count_sta2_START  (8)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_sc_int_count_sta2_END    (11)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_sc_int_count_sta3_START  (12)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_sc_int_count_sta3_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_sc_int_count_sta4_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_sc_int_count_sta4_END    (19)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_sc_int_count_sta5_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_sc_int_count_sta5_END    (23)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_sc_int_count_sta6_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_sc_int_count_sta6_END    (27)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_sc_int_count_sta7_START  (28)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_sc_int_count_sta7_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_UNION
 �ṹ˵��  : MDMSC_INT_COUNT_STAT1 �Ĵ����ṹ���塣��ַƫ����:0x025C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �жϼ���״̬�Ĵ���1������������ԡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_int_count_sta8  : 4;  /* bit[0-3]  : WBBP�ж�3 count number */
        unsigned int  sc_int_count_sta9  : 4;  /* bit[4-7]  : WBBP�ж�2 count number */
        unsigned int  sc_int_count_sta10 : 4;  /* bit[8-11] : WBBP�ж�1 count number */
        unsigned int  sc_int_count_sta11 : 4;  /* bit[12-15]: WBBP�ж�0 count number */
        unsigned int  sc_int_count_sta12 : 4;  /* bit[16-19]: GBBP�ж�3 count number */
        unsigned int  sc_int_count_sta13 : 4;  /* bit[20-23]: GBBP�ж�2 count number */
        unsigned int  sc_int_count_sta14 : 4;  /* bit[24-27]: GBBP�ж�1 count number */
        unsigned int  sc_int_count_sta15 : 4;  /* bit[28-31]: GBBP�ж�0 count number */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_sc_int_count_sta8_START   (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_sc_int_count_sta8_END     (3)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_sc_int_count_sta9_START   (4)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_sc_int_count_sta9_END     (7)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_sc_int_count_sta10_START  (8)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_sc_int_count_sta10_END    (11)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_sc_int_count_sta11_START  (12)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_sc_int_count_sta11_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_sc_int_count_sta12_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_sc_int_count_sta12_END    (19)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_sc_int_count_sta13_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_sc_int_count_sta13_END    (23)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_sc_int_count_sta14_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_sc_int_count_sta14_END    (27)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_sc_int_count_sta15_START  (28)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_sc_int_count_sta15_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_UNION
 �ṹ˵��  : MDMSC_INT_COUNT_STAT2 �Ĵ����ṹ���塣��ַƫ����:0x0260����ֵ:0x00000000�����:32
 �Ĵ���˵��: �жϼ���״̬�Ĵ���2������������ԡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_int_count_sta16 : 4;  /* bit[0-3]  : CTU_W2ARM�ж� count number */
        unsigned int  sc_int_count_sta17 : 4;  /* bit[4-7]  : CTU_G2ARM�ж� count number */
        unsigned int  sc_int_count_sta18 : 4;  /* bit[8-11] : GU_Cipher_intr[1] count number */
        unsigned int  sc_int_count_sta19 : 4;  /* bit[12-15]: GU_Cipher_intr[0] count number */
        unsigned int  sc_int_count_sta20 : 4;  /* bit[16-19]: UPACC_intr[1] count number */
        unsigned int  sc_int_count_sta21 : 4;  /* bit[20-23]: UPACC_intr[0] count number */
        unsigned int  sc_int_count_sta22 : 4;  /* bit[24-27]: IPC2CCPU_1 count number */
        unsigned int  sc_int_count_sta23 : 4;  /* bit[28-31]: IPC2CCPU_0 count number */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_sc_int_count_sta16_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_sc_int_count_sta16_END    (3)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_sc_int_count_sta17_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_sc_int_count_sta17_END    (7)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_sc_int_count_sta18_START  (8)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_sc_int_count_sta18_END    (11)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_sc_int_count_sta19_START  (12)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_sc_int_count_sta19_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_sc_int_count_sta20_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_sc_int_count_sta20_END    (19)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_sc_int_count_sta21_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_sc_int_count_sta21_END    (23)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_sc_int_count_sta22_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_sc_int_count_sta22_END    (27)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_sc_int_count_sta23_START  (28)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_sc_int_count_sta23_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_UNION
 �ṹ˵��  : MDMSC_INT_COUNT_STAT3 �Ĵ����ṹ���塣��ַƫ����:0x0264����ֵ:0x00000000�����:32
 �Ĵ���˵��: �жϼ���״̬�Ĵ���3������������ԡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_int_count_sta24 : 4;  /* bit[0-3]  : MEDMAC1 count number */
        unsigned int  sc_int_count_sta25 : 4;  /* bit[4-7]  : SOCP_intr[1] count number */
        unsigned int  sc_int_count_sta26 : 4;  /* bit[8-11] : SOCP_intr[0] count number  */
        unsigned int  sc_int_count_sta27 : 4;  /* bit[12-15]: GU Cipher1�����ж�(arm_int_dl) count number  */
        unsigned int  sc_int_count_sta28 : 4;  /* bit[16-19]: GU Cipher1�����ж�(arm_int_ul) count number  */
        unsigned int  sc_int_count_sta29 : 4;  /* bit[20-23]: GBBP2�ж�3 GSM2 DRX�ж�(g2_int_bbp_to_dsp_32k) count number  */
        unsigned int  sc_int_count_sta30 : 4;  /* bit[24-27]: GBBP2�ж�2 GSM2��DRX�ж�1(g2_int_bbp_to_dsp) count number  */
        unsigned int  sc_int_count_sta31 : 4;  /* bit[28-31]: GBBP2�ж�1 GSM2Ԥ����g2_int_bbp_to_cpu_32k�� count number  */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_sc_int_count_sta24_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_sc_int_count_sta24_END    (3)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_sc_int_count_sta25_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_sc_int_count_sta25_END    (7)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_sc_int_count_sta26_START  (8)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_sc_int_count_sta26_END    (11)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_sc_int_count_sta27_START  (12)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_sc_int_count_sta27_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_sc_int_count_sta28_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_sc_int_count_sta28_END    (19)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_sc_int_count_sta29_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_sc_int_count_sta29_END    (23)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_sc_int_count_sta30_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_sc_int_count_sta30_END    (27)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_sc_int_count_sta31_START  (28)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_sc_int_count_sta31_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_UNION
 �ṹ˵��  : MDMSC_INT_COUNT_STAT4 �Ĵ����ṹ���塣��ַƫ����:0x0268����ֵ:0x00000000�����:32
 �Ĵ���˵��: �жϼ���״̬�Ĵ���4������������ԡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_int_count_sta32 : 4;  /* bit[0-3]  : GBBP2�ж�0 GSM2��DRX�ж�0(g2_int_bbp_to_cpu) */
        unsigned int  sc_int_count_sta33 : 4;  /* bit[4-7]  : CTU_G2toARM�ж� BBP COMMON CTU_GBBP2 to ARM�ж� */
        unsigned int  sc_int_count_sta34 : 4;  /* bit[8-11] : IPC2CCPU_2 IPC�����CCPU�ĺ˼��ж�1��ipc_cpu_intr0[6]�� */
        unsigned int  sc_int_count_sta35 : 4;  /* bit[12-15]: ��ȫIPC�����CCPU����Դ���жϣ�s_ipc_cpu_intr1[1]�� */
        unsigned int  sc_int_count_sta36 : 4;  /* bit[16-19]: ��ȫIPC�����CCPU�ĺ˼��жϣ�s_ipc_cpu_intr0[1]�� */
        unsigned int  sc_int_count_sta37 : 4;  /* bit[20-23]: TDSģʱ����ʾtds hsupaģ������ж�tds_hsupa_intr��Cģʱ����ʾCDMA1x��CDMA EVDO˯��/�����ж�(32K)cbbp_intr01.
                                                              (tcbbp_intr01) */
        unsigned int  sc_int_count_sta38 : 4;  /* bit[24-27]: TDSģʱ����ʾtds harqģ������ж�tds_harq_intr��Cģʱ����ʾCDMA1x��CDMA EVDOʱ���л��ж�(imiʱ��)cbbp_intr02.
                                                              (tcbbp_intr02) */
        unsigned int  sc_int_count_sta39 : 4;  /* bit[28-31]: TDSģʱ����ʾtds turboģ������ж�tds_turbo_intr��Cģʱ����ʾCDMA1x��CDMA EVDO�ྶ����/С�������ж�cbbp_intr03.
                                                              (tcbbp_intr03) */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_sc_int_count_sta32_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_sc_int_count_sta32_END    (3)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_sc_int_count_sta33_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_sc_int_count_sta33_END    (7)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_sc_int_count_sta34_START  (8)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_sc_int_count_sta34_END    (11)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_sc_int_count_sta35_START  (12)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_sc_int_count_sta35_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_sc_int_count_sta36_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_sc_int_count_sta36_END    (19)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_sc_int_count_sta37_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_sc_int_count_sta37_END    (23)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_sc_int_count_sta38_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_sc_int_count_sta38_END    (27)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_sc_int_count_sta39_START  (28)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_sc_int_count_sta39_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_UNION
 �ṹ˵��  : MDMSC_INT_COUNT_STAT5 �Ĵ����ṹ���塣��ַƫ����:0x026C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �жϼ���״̬�Ĵ���5������������ԡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_int_count_sta40 : 4;  /* bit[0-3]  : TDSģʱ����ʾtds viterbiģ������ж�tds_viterbi_intr��Cģʱ����ʾCDMA1x��CDMA EVDO��ʱ�ж�cbbp_intr04
                                                              ��tcbbp_intr04�� */
        unsigned int  sc_int_count_sta41 : 4;  /* bit[4-7]  : TDSģʱ����ʾtdsǰ��ģ���ж�tds_fpu_intr��Cģʱ����ʾCDMA1x��CDMA EVDO����/�����ж�cbbp_intr05.
                                                              ��tcbbp_intr05�� */
        unsigned int  sc_int_count_sta42 : 4;  /* bit[8-11] : TDSģʱ����ʾtds��Ƶǰ���ж�tds_rfc_intr��Cģʱ����ʾCDMA1x��CDMA EVDO��Ƶ�ϱ�/���ݰ����ж�cbbp_intr06.
                                                              (tcbbp_intr06) */
        unsigned int  sc_int_count_sta43 : 4;  /* bit[12-15]: ������ */
        unsigned int  sc_int_count_sta44 : 4;  /* bit[16-19]: ������ */
        unsigned int  sc_int_count_sta45 : 4;  /* bit[20-23]: ������ */
        unsigned int  sc_int_count_sta46 : 4;  /* bit[24-27]: ������ */
        unsigned int  sc_int_count_sta47 : 4;  /* bit[28-31]: ������ */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_sc_int_count_sta40_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_sc_int_count_sta40_END    (3)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_sc_int_count_sta41_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_sc_int_count_sta41_END    (7)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_sc_int_count_sta42_START  (8)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_sc_int_count_sta42_END    (11)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_sc_int_count_sta43_START  (12)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_sc_int_count_sta43_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_sc_int_count_sta44_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_sc_int_count_sta44_END    (19)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_sc_int_count_sta45_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_sc_int_count_sta45_END    (23)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_sc_int_count_sta46_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_sc_int_count_sta46_END    (27)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_sc_int_count_sta47_START  (28)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_sc_int_count_sta47_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_BBPCLK_SEL_CTRL_UNION
 �ṹ˵��  : MDMSC_BBPCLK_SEL_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0270����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP ��˫TCXOʱ��ѡ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbp_clk_sel : 6;  /* bit[0-5] : BBP ʱ��Դѡ���ź�
                                                      bbp_clk_sel[0]����BBP��ʱ�ӵ�ѡ��
                                                      bbp_clk_sel[1]����BBP ABBʱ�ӵ�ѡ��
                                                      bbp_clk_sel[2]����G1ʱ�ӵ�ѡ��
                                                      bbp_clk_sel[3]����G2ʱ�ӵ�ѡ��
                                                      bbp_clk_sel[4]����tcxo ch0ʱ�ӵ�ѡ��
                                                      bbp_clk_sel[5]����tcxo ch1ʱ�ӵ�ѡ�� */
        unsigned int  reserved    : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBPCLK_SEL_CTRL_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBPCLK_SEL_CTRL_bbp_clk_sel_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_BBPCLK_SEL_CTRL_bbp_clk_sel_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_BBE16_DEBUG_RSTCTRL_UNION
 �ṹ˵��  : MDMSC_BBE16_DEBUG_RSTCTRL �Ĵ����ṹ���塣��ַƫ����:0x0274����ֵ:0x00000001�����:32
 �Ĵ���˵��: BBE16 debug reset����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbe16_debug_reset : 1;  /* bit[0]   : bbe16 APB debug��λֵ��Ĭ��Ϊ1'b1 */
        unsigned int  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBE16_DEBUG_RSTCTRL_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEBUG_RSTCTRL_bbe16_debug_reset_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEBUG_RSTCTRL_bbe16_debug_reset_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_UNION
 �ṹ˵��  : MDMSC_TIMER_EN0 �Ĵ����ṹ���塣��ַƫ����:0x02A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: timerʹ�ܼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timer_en0_ccpu_dualtimer0_en0     : 2;  /* bit[0-1]  : [1:0] ccpu dualtimer0 ��en0����Ӧccpu timer0
                                                                             ʱ��ʹ�ܿ��ƺ��壺
                                                                             x0��ϵͳģʽ����Normalʱ����Ƶ��Ϊ19.2MHz��ϵͳģʽ����SLOW��Sleep�󣬼���Ƶ��Ϊϵͳʱ�ӣ�
                                                                             x1���ο�ʱ��ѡ��32KHz�� */
        unsigned int  timer_en0_ccpu_dualtimer0_en1     : 2;  /* bit[2-3]  : [3:2] ccpu dualtimer0 ��en1 ����Ӧccpu timer1 */
        unsigned int  timer_en0_ccpu_dualtimer1_en0     : 2;  /* bit[4-5]  : [5:4] ccpu dualtimer1 ��en0����Ӧccpu timer2 */
        unsigned int  timer_en0_ccpu_dualtimer1_en1     : 2;  /* bit[6-7]  : [7:6] ccpu dualtimer1 ��en1 ����Ӧccpu timer3 */
        unsigned int  timer_en0_ccpu_dualtimer2_en0     : 2;  /* bit[8-9]  : [9:8] ccpu dualtimer2 ��en0����Ӧccpu timer4 */
        unsigned int  timer_en0_ccpu_dualtimer2_en1     : 2;  /* bit[10-11]: [11:10] ccpu dualtimer2 ��en1����Ӧccpu timer5 */
        unsigned int  timer_en0_ccpu_dualtimer3_en0     : 2;  /* bit[12-13]: [13:12] ccpu dualtimer3 ��en0����Ӧccpu timer6 */
        unsigned int  timer_en0_ccpu_dualtimer3_en1     : 2;  /* bit[14-15]: [15:14] ccpu dualtimer3 ��en1����Ӧccpu timer7  */
        unsigned int  timer_en0_msk_ccpu_dualtimer0_en0 : 2;  /* bit[16-17]: [17:16] ccpu timer0 */
        unsigned int  timer_en0_msk_ccpu_dualtimer0_en1 : 2;  /* bit[18-19]: [19:18] ccpu timer1 */
        unsigned int  timer_en0_msk_ccpu_dualtimer1_en0 : 2;  /* bit[20-21]: [21:20] ccpu timer2 */
        unsigned int  timer_en0_msk_ccpu_dualtimer1_en1 : 2;  /* bit[22-23]: [23:22] ccpu timer3 */
        unsigned int  timer_en0_msk_ccpu_dualtimer2_en0 : 2;  /* bit[24-25]: [25:24] ccpu timer4 */
        unsigned int  timer_en0_msk_ccpu_dualtimer2_en1 : 2;  /* bit[26-27]: [27:26] ccpu timer5 */
        unsigned int  timer_en0_msk_ccpu_dualtimer3_en0 : 2;  /* bit[28-29]: [29:28] ccpu timer6 */
        unsigned int  timer_en0_msk_ccpu_dualtimer3_en1 : 2;  /* bit[30-31]: [31:16]��ÿһbit˳���Ӧbit15��bit0������bit31��16��bitд1��ͬʱ������bit15��0������Ч����bit31��16��bitд0ʱ������bit15��0���ֲ��䣻
                                                                             [30:30] ccpu timer7 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_ccpu_dualtimer0_en0_START      (0)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_ccpu_dualtimer0_en0_END        (1)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_ccpu_dualtimer0_en1_START      (2)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_ccpu_dualtimer0_en1_END        (3)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_ccpu_dualtimer1_en0_START      (4)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_ccpu_dualtimer1_en0_END        (5)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_ccpu_dualtimer1_en1_START      (6)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_ccpu_dualtimer1_en1_END        (7)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_ccpu_dualtimer2_en0_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_ccpu_dualtimer2_en0_END        (9)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_ccpu_dualtimer2_en1_START      (10)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_ccpu_dualtimer2_en1_END        (11)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_ccpu_dualtimer3_en0_START      (12)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_ccpu_dualtimer3_en0_END        (13)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_ccpu_dualtimer3_en1_START      (14)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_ccpu_dualtimer3_en1_END        (15)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_msk_ccpu_dualtimer0_en0_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_msk_ccpu_dualtimer0_en0_END    (17)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_msk_ccpu_dualtimer0_en1_START  (18)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_msk_ccpu_dualtimer0_en1_END    (19)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_msk_ccpu_dualtimer1_en0_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_msk_ccpu_dualtimer1_en0_END    (21)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_msk_ccpu_dualtimer1_en1_START  (22)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_msk_ccpu_dualtimer1_en1_END    (23)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_msk_ccpu_dualtimer2_en0_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_msk_ccpu_dualtimer2_en0_END    (25)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_msk_ccpu_dualtimer2_en1_START  (26)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_msk_ccpu_dualtimer2_en1_END    (27)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_msk_ccpu_dualtimer3_en0_START  (28)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_msk_ccpu_dualtimer3_en0_END    (29)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_msk_ccpu_dualtimer3_en1_START  (30)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_msk_ccpu_dualtimer3_en1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_UNION
 �ṹ˵��  : MDMSC_TIMER_EN1 �Ĵ����ṹ���塣��ַƫ����:0x02A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: timerʹ�ܼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timer_en1_ccpu_dualtimer4_en0     : 2;  /* bit[0-1]  : [1:0] ccpu dualtimer0 ��en0����Ӧccpu timer0
                                                                             ʱ��ʹ�ܿ��ƺ��壺
                                                                             x0��ϵͳģʽ����Normalʱ����Ƶ��Ϊ19.2MHz��ϵͳģʽ����SLOW��Sleep�󣬼���Ƶ��Ϊϵͳʱ�ӣ�
                                                                             x1���ο�ʱ��ѡ��32KHz�� */
        unsigned int  timer_en1_ccpu_dualtimer4_en1     : 2;  /* bit[2-3]  : [3:2] ccpu dualtimer4 ��en1 ����Ӧccpu timer9 */
        unsigned int  timer_en1_ccpu_dualtimer5_en0     : 2;  /* bit[4-5]  : [5:4] ccpu dualtimer5 ��en0����Ӧccpu timer10 */
        unsigned int  timer_en1_ccpu_dualtimer5_en1     : 2;  /* bit[6-7]  : [7:6] ccpu dualtimer5 ��en1 ����Ӧccpu timer11 */
        unsigned int  timer_en1_ccpu_dualtimer6_en0     : 2;  /* bit[8-9]  : [9:8] ccpu dualtimer6 ��en0����Ӧccpu timer12 */
        unsigned int  timer_en1_ccpu_dualtimer6_en1     : 2;  /* bit[10-11]: [11:10] ccpu dualtimer6 ��en1����Ӧccpu timer13 */
        unsigned int  timer_en1_ccpu_dualtimer7_en0     : 2;  /* bit[12-13]: [13:12] ccpu dualtimer7 ��en0����Ӧccpu timer14 */
        unsigned int  timer_en1_ccpu_dualtimer7_en1     : 2;  /* bit[14-15]: [15:14] ccpu dualtimer7 ��en1����Ӧccpu timer15 */
        unsigned int  timer_en1_msk_ccpu_dualtimer4_en0 : 2;  /* bit[16-17]: [17:16] ccpu timer8 */
        unsigned int  timer_en1_msk_ccpu_dualtimer4_en1 : 2;  /* bit[18-19]: [19:18] ccpu timer9 */
        unsigned int  timer_en1_msk_ccpu_dualtimer5_en0 : 2;  /* bit[20-21]: [21:20] ccpu timer10 */
        unsigned int  timer_en1_msk_ccpu_dualtimer5_en1 : 2;  /* bit[22-23]: [23:22] ccpu timer11 */
        unsigned int  timer_en1_msk_ccpu_dualtimer6_en0 : 2;  /* bit[24-25]: [25:24] ccpu timer12 */
        unsigned int  timer_en1_msk_ccpu_dualtimer6_en1 : 2;  /* bit[26-27]: [27:26] ccpu timer13 */
        unsigned int  timer_en1_msk_ccpu_dualtimer7_en0 : 2;  /* bit[28-29]: [29:28] ccpu timer14 */
        unsigned int  timer_en1_msk_ccpu_dualtimer7_en1 : 2;  /* bit[30-31]: [31:16]��ÿһbit˳���Ӧbit15��bit0������bit31��16��bitд1��ͬʱ������bit15��0������Ч����bit31��16��bitд0ʱ������bit15��0���ֲ��䣻
                                                                             [30:30] ccpu timer15 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_ccpu_dualtimer4_en0_START      (0)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_ccpu_dualtimer4_en0_END        (1)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_ccpu_dualtimer4_en1_START      (2)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_ccpu_dualtimer4_en1_END        (3)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_ccpu_dualtimer5_en0_START      (4)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_ccpu_dualtimer5_en0_END        (5)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_ccpu_dualtimer5_en1_START      (6)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_ccpu_dualtimer5_en1_END        (7)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_ccpu_dualtimer6_en0_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_ccpu_dualtimer6_en0_END        (9)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_ccpu_dualtimer6_en1_START      (10)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_ccpu_dualtimer6_en1_END        (11)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_ccpu_dualtimer7_en0_START      (12)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_ccpu_dualtimer7_en0_END        (13)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_ccpu_dualtimer7_en1_START      (14)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_ccpu_dualtimer7_en1_END        (15)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_msk_ccpu_dualtimer4_en0_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_msk_ccpu_dualtimer4_en0_END    (17)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_msk_ccpu_dualtimer4_en1_START  (18)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_msk_ccpu_dualtimer4_en1_END    (19)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_msk_ccpu_dualtimer5_en0_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_msk_ccpu_dualtimer5_en0_END    (21)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_msk_ccpu_dualtimer5_en1_START  (22)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_msk_ccpu_dualtimer5_en1_END    (23)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_msk_ccpu_dualtimer6_en0_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_msk_ccpu_dualtimer6_en0_END    (25)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_msk_ccpu_dualtimer6_en1_START  (26)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_msk_ccpu_dualtimer6_en1_END    (27)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_msk_ccpu_dualtimer7_en0_START  (28)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_msk_ccpu_dualtimer7_en0_END    (29)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_msk_ccpu_dualtimer7_en1_START  (30)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_msk_ccpu_dualtimer7_en1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_UNION
 �ṹ˵��  : MDMSC_TIMER_EN2 �Ĵ����ṹ���塣��ַƫ����:0x02A8����ֵ:0x00000000�����:32
 �Ĵ���˵��: timerʹ�ܼĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                        : 8;  /* bit[0-7]  : reserved */
        unsigned int  timer_en2_ccpu_dualtimer8_en0     : 2;  /* bit[8-9]  : [9:8] ccpu dualtimer8 ��en0����Ӧccpu timer16 */
        unsigned int  timer_en2_ccpu_dualtimer8_en1     : 2;  /* bit[10-11]: [11:10] ccpu dualtimer8 ��en1����Ӧccpu timer17 */
        unsigned int  timer_en2_ccpu_dualtimer9_en0     : 2;  /* bit[12-13]: [13:12] ccpu dualtimer9 ��en0����Ӧccpu timer18 */
        unsigned int  timer_en2_ccpu_dualtimer9_en1     : 2;  /* bit[14-15]: [1:0] ccpu dualtimer0 ��en0����Ӧccpu timer0
                                                                             ʱ��ʹ�ܿ��ƺ��壺
                                                                             x0��ϵͳģʽ����Normalʱ����Ƶ��Ϊ19.2MHz��ϵͳģʽ����SLOW��Sleep�󣬼���Ƶ��Ϊϵͳʱ�ӣ�
                                                                             x1���ο�ʱ��ѡ��32KHz�� */
        unsigned int  reserved_1                        : 8;  /* bit[16-23]: reserved */
        unsigned int  timer_en2_msk_ccpu_dualtimer8_en0 : 2;  /* bit[24-25]: [25:24] ccpu timer16 */
        unsigned int  timer_en2_msk_ccpu_dualtimer8_en1 : 2;  /* bit[26-27]: [27:26] ccpu timer17 */
        unsigned int  timer_en2_msk_ccpu_dualtimer9_en0 : 2;  /* bit[28-29]: [29:28] ccpu timer18 */
        unsigned int  timer_en2_msk_ccpu_dualtimer9_en1 : 2;  /* bit[30-31]: [31:16]��ÿһbit˳���Ӧbit15��bit0������bit31��16��bitд1��ͬʱ������bit15��0������Ч����bit31��16��bitд0ʱ������bit15��0���ֲ��䣻
                                                                             [30:30] ccpu timer19 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_timer_en2_ccpu_dualtimer8_en0_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_timer_en2_ccpu_dualtimer8_en0_END        (9)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_timer_en2_ccpu_dualtimer8_en1_START      (10)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_timer_en2_ccpu_dualtimer8_en1_END        (11)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_timer_en2_ccpu_dualtimer9_en0_START      (12)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_timer_en2_ccpu_dualtimer9_en0_END        (13)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_timer_en2_ccpu_dualtimer9_en1_START      (14)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_timer_en2_ccpu_dualtimer9_en1_END        (15)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_timer_en2_msk_ccpu_dualtimer8_en0_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_timer_en2_msk_ccpu_dualtimer8_en0_END    (25)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_timer_en2_msk_ccpu_dualtimer8_en1_START  (26)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_timer_en2_msk_ccpu_dualtimer8_en1_END    (27)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_timer_en2_msk_ccpu_dualtimer9_en0_START  (28)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_timer_en2_msk_ccpu_dualtimer9_en0_END    (29)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_timer_en2_msk_ccpu_dualtimer9_en1_START  (30)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_timer_en2_msk_ccpu_dualtimer9_en1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL4_UNION
 �ṹ˵��  : MDMSC_CCPU_DEFCTRL4 �Ĵ����ṹ���塣��ַƫ����:0x02AC����ֵ:0x00000000�����:32
 �Ĵ���˵��: Modem��ϵͳ�Զ���CCPU remap�ߴ��ϱ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  remap_error_clr : 1;  /* bit[0]   : REMAP �����źŵ����㣬����1���aw/arremap_error_flag�źŵģ������ź� */
        unsigned int  reserved        : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL4_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL4_remap_error_clr_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL4_remap_error_clr_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL_RPT_UNION
 �ṹ˵��  : MDMSC_CCPU_DEFCTRL_RPT �Ĵ����ṹ���塣��ַƫ����:0x02B0����ֵ:0x00000000�����:32
 �Ĵ���˵��: Modem��ϵͳ�Զ���CCPU remap״̬�ϱ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  arremap_error_flag : 1;  /* bit[0]   : ������REMAP�ĵ�20bit�Ƿ�ӳ�䵽reserved�ռ�,0��ʾû�У�1��ʾ�У���Ϊ����ӳ�䣩 */
        unsigned int  awremap_error_flag : 1;  /* bit[1]   : д����REMAP�ĵ�20bit�Ƿ�ӳ�䵽reserved�ռ�,0��ʾû�У�1��ʾ�У���Ϊ����ӳ�䣩 */
        unsigned int  reserved           : 30; /* bit[2-31]: reserved */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL_RPT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL_RPT_arremap_error_flag_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL_RPT_arremap_error_flag_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL_RPT_awremap_error_flag_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL_RPT_awremap_error_flag_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL3_UNION
 �ṹ˵��  : MDMSC_CCPU_DEFCTRL3 �Ĵ����ṹ���塣��ַƫ����:0x02B4����ֵ:0xE0000FFB�����:32
 �Ĵ���˵��: Modem��ϵͳ�Զ���CCPU�� remap SRAM��ַ���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sram_addr_cfg_value : 12; /* bit[0-11] : BBE16 SRAM�ķ��ʵ�ַ�ռ�ĸ�12bit */
        unsigned int  sram_addr_boundary  : 20; /* bit[12-31]: BBE16 SRAM�ĵ�ַ�߽磬Ĭ��ֵΪ0xE0000��896K�� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL3_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL3_sram_addr_cfg_value_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL3_sram_addr_cfg_value_END    (11)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL3_sram_addr_boundary_START   (12)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL3_sram_addr_boundary_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL2_UNION
 �ṹ˵��  : MDMSC_CCPU_DEFCTRL2 �Ĵ����ṹ���塣��ַƫ����:0x02B8����ֵ:0x00000000�����:32
 �Ĵ���˵��: Modem��ϵͳ�Զ���CCPU����remapʹ�����üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ccpu_remap_en : 1;  /* bit[0]   : ccpu remapʹ���źţ�����Ч */
        unsigned int  reserved      : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL2_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL2_ccpu_remap_en_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL2_ccpu_remap_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL0_UNION
 �ṹ˵��  : MDMSC_CCPU_DEFCTRL0 �Ĵ����ṹ���塣��ַƫ����:0x02BC����ֵ:0x00000000�����:32
 �Ĵ���˵��: Modem��ϵͳ�Զ���CCPU���ܿ���remap ����ַ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ccpu_remap_cfg_value : 12; /* bit[0-11] : ccpu remap��12bit��ַ,�����û�ַ������ccpu_remap_enʹ���ź���Ч */
        unsigned int  reserved             : 20; /* bit[12-31]: reserved */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL0_ccpu_remap_cfg_value_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL0_ccpu_remap_cfg_value_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL1_UNION
 �ṹ˵��  : MDMSC_CCPU_DEFCTRL1 �Ĵ����ṹ���塣��ַƫ����:0x02C0����ֵ:0x00000000�����:32
 �Ĵ���˵��: Modem��ϵͳ�Զ���CCPU���ܿ��ƣ�debug���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cs_ccpu_dbg_rst_ctrl : 1;  /* bit[0]   : CCPU Coresight Debug��λ�����źŵĿ��ơ�
                                                               0����ʾ������Coresight��λ����
                                                               1����ʾ����Coresight��λ���� */
        unsigned int  reserved             : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL1_cs_ccpu_dbg_rst_ctrl_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL1_cs_ccpu_dbg_rst_ctrl_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_UNION
 �ṹ˵��  : MDMSC_ALWAYSON_SYS_CTRL �Ĵ����ṹ���塣��ַƫ����:0x02C4����ֵ:0x000000E4�����:32
 �Ĵ���˵��: ALWAYSON������ϵͳ���ƼĴ��������ܰ���SCI���ơ�NOC Timeout���ơ�TCXO AFC������ơ�modem��sysnoc�ſص�ͶƱ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gbbp_gps_restrain_sel                  : 1;  /* bit[0]    : GģGPS���ƣ�GBBP���Ĭ�ϸ���Ч�������ⲿ������������
                                                                                  0���������Ƹ���Ч����GBBP��������źŽ���ֱͨ
                                                                                  1���������Ƶ���Ч����GBBP��������źŽ���ȡ�� */
        unsigned int  gbbp_led_restrain_sel                  : 1;  /* bit[1]    : Gģ��������ƣ�GBBP���Ĭ�ϸ���Ч�������ⲿ������������
                                                                                  0���������Ƹ���Ч����GBBP��������źŽ���ֱͨ
                                                                                  1���������Ƶ���Ч����GBBP��������źŽ���ȡ�� */
        unsigned int  clk_en_sysnoc_mdm                      : 1;  /* bit[2]    : modem�����sysnoc����ʱ���ſ�
                                                                                  0��modem��ϵͳͶƱsysnocʱ���ſ�
                                                                                  1��modem��ϵͳͶƱsysnocʱ����Ч */
        unsigned int  reserved_0                             : 2;  /* bit[3-4]  : reserved */
        unsigned int  modemnoc_timeout_en                    : 1;  /* bit[5]    : modemnoc_timeout_en
                                                                                  0:disable timeout
                                                                                  1:enable timeout */
        unsigned int  tcxo0_afc_high_z                       : 1;  /* bit[6]    : [6]��TCXO_0 AFC�����������ơ�
                                                                                  0�����ʹ�ܣ�
                                                                                  1��������衣 */
        unsigned int  tcxo1_afc_high_z                       : 1;  /* bit[7]    : [7]��TCXO_1 AFC�����������ơ�
                                                                                  0�����ʹ�ܣ�
                                                                                  1��������衣 */
        unsigned int  alwayson_and_periph_sys_ctrl0_sci0     : 1;  /* bit[8]    : SCI0���buffer���ơ�Ĭ��0
                                                                                  0��open-drain��
                                                                                  1��offchip buffer�� */
        unsigned int  alwayson_and_periph_sys_ctrl0_sci1     : 1;  /* bit[9]    : SCI1���buffer���ơ�Ĭ��0
                                                                                  0��open-drain��
                                                                                  1��offchip buffer�� */
        unsigned int  reserved_1                             : 6;  /* bit[10-15]: reserved */
        unsigned int  gbbp_gps_restrain_sel_msk              : 1;  /* bit[16]   : GģGPS���ƣ�GBBP���Ĭ�ϸ���Ч�������ⲿ������������ */
        unsigned int  gbbp_led_restrain_sel_msk              : 1;  /* bit[17]   : Gģ��������ƣ�GBBP���Ĭ�ϸ���Ч�������ⲿ������������ */
        unsigned int  clk_en_sysnoc_mdm_msk                  : 1;  /* bit[18]   : modem�����sysnoc����ʱ���ſ�MSK����λ */
        unsigned int  reserved_2                             : 2;  /* bit[19-20]: reserved */
        unsigned int  modemnoc_timeout_en_msk                : 1;  /* bit[21]   : modemnoc_timeout_en
                                                                                  0:disable timeout
                                                                                  1:enable timeout */
        unsigned int  tcxo0_afc_high_z_msk                   : 1;  /* bit[22]   : TCXO_0 AFC�����������ơ� */
        unsigned int  tcxo1_afc_high_z_msk                   : 1;  /* bit[23]   : TCXO_1 AFC�����������ơ� */
        unsigned int  alwayson_and_periph_sys_ctrl0_msk_sci0 : 1;  /* bit[24]   : SCI0���buffer���ơ�Ĭ��0 */
        unsigned int  alwayson_and_periph_sys_ctrl0_msk_sci1 : 1;  /* bit[25]   : SCI1���buffer���ơ�Ĭ��0 */
        unsigned int  reserved_3                             : 6;  /* bit[26-31]: [31:16]��ÿһbit˳���Ӧbit15��bit0������bit31��16��bitд1��ͬʱ������bit15��0������Ч����bit31��16��bitд0ʱ������bit15��0���ֲ��䣻
                                                                                  [31]����  */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_gbbp_gps_restrain_sel_START                   (0)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_gbbp_gps_restrain_sel_END                     (0)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_gbbp_led_restrain_sel_START                   (1)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_gbbp_led_restrain_sel_END                     (1)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_clk_en_sysnoc_mdm_START                       (2)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_clk_en_sysnoc_mdm_END                         (2)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_modemnoc_timeout_en_START                     (5)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_modemnoc_timeout_en_END                       (5)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_tcxo0_afc_high_z_START                        (6)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_tcxo0_afc_high_z_END                          (6)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_tcxo1_afc_high_z_START                        (7)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_tcxo1_afc_high_z_END                          (7)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_alwayson_and_periph_sys_ctrl0_sci0_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_alwayson_and_periph_sys_ctrl0_sci0_END        (8)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_alwayson_and_periph_sys_ctrl0_sci1_START      (9)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_alwayson_and_periph_sys_ctrl0_sci1_END        (9)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_gbbp_gps_restrain_sel_msk_START               (16)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_gbbp_gps_restrain_sel_msk_END                 (16)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_gbbp_led_restrain_sel_msk_START               (17)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_gbbp_led_restrain_sel_msk_END                 (17)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_clk_en_sysnoc_mdm_msk_START                   (18)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_clk_en_sysnoc_mdm_msk_END                     (18)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_modemnoc_timeout_en_msk_START                 (21)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_modemnoc_timeout_en_msk_END                   (21)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_tcxo0_afc_high_z_msk_START                    (22)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_tcxo0_afc_high_z_msk_END                      (22)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_tcxo1_afc_high_z_msk_START                    (23)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_tcxo1_afc_high_z_msk_END                      (23)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_alwayson_and_periph_sys_ctrl0_msk_sci0_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_alwayson_and_periph_sys_ctrl0_msk_sci0_END    (24)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_alwayson_and_periph_sys_ctrl0_msk_sci1_START  (25)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_alwayson_and_periph_sys_ctrl0_msk_sci1_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_UNION
 �ṹ˵��  : MDMSC_PERIPH_CTRL �Ĵ����ṹ���塣��ַƫ����:0x02C8����ֵ:0x000004D2�����:32
 �Ĵ���˵��: ������ƼĴ��������ܰ���UPACC��CICOM��CICOMģʽѡ��DMAC
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gucicom0sel_mode                  : 1;  /* bit[0] : gucicom0sel_mode
                                                                          0��WCDMA�ӽ���ģʽ
                                                                          1��GSM�ӽ���ģʽ */
        unsigned int  gucicom0soft_auto_clk_gate_en     : 1;  /* bit[1] : gucicom0auto_clk_gate_en
                                                                          1'b0:Ӳ���Զ��ſز�ʹ��
                                                                          1'b1:Ӳ���Զ��ſ�ʹ�� */
        unsigned int  gucicom0soft_gate_clk_en          : 1;  /* bit[2] : gucicom0soft_gate_clk_en
                                                                          1'b0:����ſز�ʹ��
                                                                          1'b1:����ſ�ʹ�� */
        unsigned int  reserved_0                        : 1;  /* bit[3] : gucicom1sel_mode(����)
                                                                          0��WCDMA�ӽ���ģʽ
                                                                          1��GSM�ӽ���ģʽ */
        unsigned int  reserved_1                        : 1;  /* bit[4] : gucicom1auto_clk_gate_en(����)
                                                                          1'b0:Ӳ���Զ��ſز�ʹ��
                                                                          1'b1:Ӳ���Զ��ſ�ʹ�� */
        unsigned int  reserved_2                        : 1;  /* bit[5] : gucicom11soft_gate_clk_en(����)
                                                                          1'b0:����ſز�ʹ��
                                                                          1'b1:����ſ�ʹ�� */
        unsigned int  mdmdmac_auto_clken0_sel           : 1;  /* bit[6] : mdmdmac_auto_clken0_selPERIPH_MISC
                                                                          0:autoclkgatedisable
                                                                          1:autoclkgageenable */
        unsigned int  mdmdmac_auto_clken1_sel           : 1;  /* bit[7] : mdmdmac_auto_clken1_selPERIPH_MISC
                                                                          0:autoclkgatedisable
                                                                          1:autoclkgageenable */
        unsigned int  dw_x2x_auto_clk_gate_en           : 1;  /* bit[8] : ccpu������x2x�ŵ��Զ��ſ�ʹ��
                                                                          1'b0:Ӳ���Զ��ſز�ʹ��
                                                                          1'b1:Ӳ���Զ��ſ�ʹ�� */
        unsigned int  dw_axi_auto_clk_gate_en           : 1;  /* bit[9] : ccpu������axi���ߵ��Զ��ſ�ʹ��
                                                                          1'b0:Ӳ���Զ��ſز�ʹ��
                                                                          1'b1:Ӳ���Զ��ſ�ʹ�� */
        unsigned int  UPACC_auto_clk_gate_en            : 1;  /* bit[10]: (UPACC)auto_clk_gate_en
                                                                          1'b0:Ӳ���Զ��ſز�ʹ��
                                                                          1'b1:Ӳ���Զ��ſ�ʹ�� */
        unsigned int  upacc_soft_gate_clk_en            : 1;  /* bit[11]: (UPACC)soft_gate_clk_en
                                                                          1'b0:����ſز�ʹ��
                                                                          1'b1:����ſ�ʹ�� */
        unsigned int  bbe16_axi_auto_clk_gate_en        : 1;  /* bit[12]: BBE16������axi���ߵ��Զ��ſ�ʹ��
                                                                          1'b0:Ӳ���Զ��ſز�ʹ��
                                                                          1'b1:Ӳ���Զ��ſ�ʹ�� */
        unsigned int  ddr_x2x_auto_clk_gate_en          : 1;  /* bit[13]: CCPU��DDR��X2X�ŵ��Զ��ſ�ʹ��
                                                                          1'b0:Ӳ���Զ��ſز�ʹ��
                                                                          1'b1:Ӳ���Զ��ſ�ʹ�� */
        unsigned int  reserved_3                        : 1;  /* bit[14]: reserved */
        unsigned int  reserved_4                        : 1;  /* bit[15]: reserved */
        unsigned int  gucicom0sel_mode_msk              : 1;  /* bit[16]: gucicom0sel_mode */
        unsigned int  gucicom0soft_auto_clk_gate_en_msk : 1;  /* bit[17]: gucicom0auto_clk_gate_en */
        unsigned int  gucicom0soft_gate_clk_en_msk      : 1;  /* bit[18]: gucicom0soft_gate_clk_en */
        unsigned int  reserved_5                        : 1;  /* bit[19]: gucicom1sel_mode(����) */
        unsigned int  reserved_6                        : 1;  /* bit[20]: gucicom1auto_clk_gate_en(����) */
        unsigned int  reserved_7                        : 1;  /* bit[21]: gucicom1soft_gate_clk_en(����) */
        unsigned int  mdmdmac_auto_clken0_sel_msk       : 1;  /* bit[22]: mdmdmac_auto_clken0_selPERIPH_MISC */
        unsigned int  mdmdmac_auto_clken1_sel_msk       : 1;  /* bit[23]: mdmdmac_auto_clken1_selPERIPH_MISC */
        unsigned int  dw_x2x_auto_clk_gate_en_msk       : 1;  /* bit[24]: ccpu������x2x�ŵ��Զ��ſ�ʹ��
                                                                          1'b0:Ӳ���Զ��ſز�ʹ��
                                                                          1'b1:Ӳ���Զ��ſ�ʹ�� */
        unsigned int  dw_axi_auto_clk_gate_en_msk       : 1;  /* bit[25]: ccpu������axi���ߵ��Զ��ſ�ʹ��
                                                                          1'b0:Ӳ���Զ��ſز�ʹ��
                                                                          1'b1:Ӳ���Զ��ſ�ʹ�� */
        unsigned int  UPACC_auto_clk_gate_en_msk        : 1;  /* bit[26]: (UPACC)auto_clk_gate_en */
        unsigned int  upacc_soft_gate_clk_en_msk        : 1;  /* bit[27]: (UPACC)soft_gate_clk_en */
        unsigned int  bbe16_axi_auto_clk_gate_en_msk    : 1;  /* bit[28]: BBE16������axi���ߵ��Զ��ſ�ʹ��
                                                                          1'b0:Ӳ���Զ��ſز�ʹ��
                                                                          1'b1:Ӳ���Զ��ſ�ʹ�� */
        unsigned int  ddr_x2x_auto_clk_gate_en_msk      : 1;  /* bit[29]: ccpu������axi���ߵ��Զ��ſ�ʹ��
                                                                          1'b0:Ӳ���Զ��ſز�ʹ��
                                                                          1'b1:Ӳ���Զ��ſ�ʹ�� */
        unsigned int  reserved_8                        : 1;  /* bit[30]: reserved */
        unsigned int  reserved_9                        : 1;  /* bit[31]: [31:16]��ÿһbit˳���Ӧbit15��bit0������bit31��16��bitд1��ͬʱ������bit15��0������Ч����bit31��16��bitд0ʱ������bit15��0���ֲ��䣻
                                                                          [31:28]�������� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_gucicom0sel_mode_START                   (0)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_gucicom0sel_mode_END                     (0)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_gucicom0soft_auto_clk_gate_en_START      (1)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_gucicom0soft_auto_clk_gate_en_END        (1)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_gucicom0soft_gate_clk_en_START           (2)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_gucicom0soft_gate_clk_en_END             (2)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_mdmdmac_auto_clken0_sel_START            (6)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_mdmdmac_auto_clken0_sel_END              (6)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_mdmdmac_auto_clken1_sel_START            (7)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_mdmdmac_auto_clken1_sel_END              (7)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_dw_x2x_auto_clk_gate_en_START            (8)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_dw_x2x_auto_clk_gate_en_END              (8)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_dw_axi_auto_clk_gate_en_START            (9)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_dw_axi_auto_clk_gate_en_END              (9)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_UPACC_auto_clk_gate_en_START             (10)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_UPACC_auto_clk_gate_en_END               (10)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_upacc_soft_gate_clk_en_START             (11)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_upacc_soft_gate_clk_en_END               (11)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_bbe16_axi_auto_clk_gate_en_START         (12)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_bbe16_axi_auto_clk_gate_en_END           (12)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_ddr_x2x_auto_clk_gate_en_START           (13)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_ddr_x2x_auto_clk_gate_en_END             (13)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_gucicom0sel_mode_msk_START               (16)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_gucicom0sel_mode_msk_END                 (16)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_gucicom0soft_auto_clk_gate_en_msk_START  (17)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_gucicom0soft_auto_clk_gate_en_msk_END    (17)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_gucicom0soft_gate_clk_en_msk_START       (18)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_gucicom0soft_gate_clk_en_msk_END         (18)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_mdmdmac_auto_clken0_sel_msk_START        (22)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_mdmdmac_auto_clken0_sel_msk_END          (22)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_mdmdmac_auto_clken1_sel_msk_START        (23)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_mdmdmac_auto_clken1_sel_msk_END          (23)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_dw_x2x_auto_clk_gate_en_msk_START        (24)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_dw_x2x_auto_clk_gate_en_msk_END          (24)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_dw_axi_auto_clk_gate_en_msk_START        (25)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_dw_axi_auto_clk_gate_en_msk_END          (25)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_UPACC_auto_clk_gate_en_msk_START         (26)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_UPACC_auto_clk_gate_en_msk_END           (26)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_upacc_soft_gate_clk_en_msk_START         (27)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_upacc_soft_gate_clk_en_msk_END           (27)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_bbe16_axi_auto_clk_gate_en_msk_START     (28)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_bbe16_axi_auto_clk_gate_en_msk_END       (28)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_ddr_x2x_auto_clk_gate_en_msk_START       (29)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_ddr_x2x_auto_clk_gate_en_msk_END         (29)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_PERIPH_STAT_UNION
 �ṹ˵��  : MDMSC_PERIPH_STAT �Ĵ����ṹ���塣��ַƫ����:0x02CC����ֵ:0x00000001�����:32
 �Ĵ���˵��: ����״̬�Ĵ��������ܰ���CICOM״̬
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gucipher0_clk_state : 1;  /* bit[0]   : gucipher0_clk_stateʱ���ſ�ָʾ
                                                              0��ʱ�ӹرգ�
                                                              1��ʱ�Ӵ򿪡� */
        unsigned int  reserved_0          : 1;  /* bit[1]   : gucipher1_clk_stateʱ���ſ�ָʾ(����)
                                                              0��ʱ�ӹرգ�
                                                              1��ʱ�Ӵ򿪡� */
        unsigned int  reserved_1          : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PERIPH_STAT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_STAT_gucipher0_clk_state_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_STAT_gucipher0_clk_state_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_UNION
 �ṹ˵��  : MDMSC_MNOC_QOSCTRL0 �Ĵ����ṹ���塣��ַƫ����:0x02D0����ֵ:0x00000000�����:32
 �Ĵ���˵��: MDM_NOC������Master�豸�����ȼ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  modem_noc_master_press_edmac   : 3;  /* bit[0-2]  : MDM NOC Master�豸EDMAC������PRESS���ȼ����ã�������ֵ0��7 */
        unsigned int  reserved_0                     : 1;  /* bit[3]    : ���� */
        unsigned int  modem_noc_master_hurry_edmac   : 3;  /* bit[4-6]  : MDM NOC Master�豸EDMAC������HURRY���ȼ����ã�������ֵ0��7 */
        unsigned int  reserved_1                     : 1;  /* bit[7]    : ���� */
        unsigned int  modem_noc_master_awqos_edmac   : 3;  /* bit[8-10] : MDM NOC Master�豸EDMAC������AWQOS���ȼ����ã�������ֵΪ0��7 */
        unsigned int  reserved_2                     : 1;  /* bit[11]   : ���� */
        unsigned int  modem_noc_master_arqos_edmac   : 3;  /* bit[12-14]: MDM NOC Master�豸EDMAC������ARQOS���ȼ����ã�������ֵΪ0��7 */
        unsigned int  reserved_3                     : 1;  /* bit[15]   : ���� */
        unsigned int  modem_noc_master_press_lcipher : 3;  /* bit[16-18]: MDM NOC Master�豸LCIPHER������PRESS���ȼ����ã�������ֵ0��7 */
        unsigned int  reserved_4                     : 1;  /* bit[19]   : ���� */
        unsigned int  modem_noc_master_hurry_lcipher : 3;  /* bit[20-22]: MDM NOC Master�豸LCIPHER������HURRY���ȼ����ã�������ֵ0��7 */
        unsigned int  reserved_5                     : 1;  /* bit[23]   : ���� */
        unsigned int  modem_noc_master_awqos_lcipher : 3;  /* bit[24-26]: MDM NOC Master�豸LCIPHER������AWQOS���ȼ����ã�������ֵΪ0��7 */
        unsigned int  reserved_6                     : 1;  /* bit[27]   : ���� */
        unsigned int  modem_noc_master_arqos_lcipher : 3;  /* bit[28-30]: MDM NOC Master�豸LCIPHER������ARQOS���ȼ����ã�������ֵΪ0��7 */
        unsigned int  reserved_7                     : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_modem_noc_master_press_edmac_START    (0)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_modem_noc_master_press_edmac_END      (2)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_modem_noc_master_hurry_edmac_START    (4)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_modem_noc_master_hurry_edmac_END      (6)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_modem_noc_master_awqos_edmac_START    (8)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_modem_noc_master_awqos_edmac_END      (10)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_modem_noc_master_arqos_edmac_START    (12)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_modem_noc_master_arqos_edmac_END      (14)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_modem_noc_master_press_lcipher_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_modem_noc_master_press_lcipher_END    (18)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_modem_noc_master_hurry_lcipher_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_modem_noc_master_hurry_lcipher_END    (22)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_modem_noc_master_awqos_lcipher_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_modem_noc_master_awqos_lcipher_END    (26)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_modem_noc_master_arqos_lcipher_START  (28)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_modem_noc_master_arqos_lcipher_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_UNION
 �ṹ˵��  : MDMSC_MNOC_QOSCTRL1 �Ĵ����ṹ���塣��ַƫ����:0x02D4����ֵ:0x00000000�����:32
 �Ĵ���˵��: MDM_NOC������Master�豸�����ȼ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  modem_noc_master_press_upacc    : 3;  /* bit[0-2]  : MDM NOC Master�豸UPACC������PRESS���ȼ����ã�������ֵ0��7 */
        unsigned int  reserved_0                      : 1;  /* bit[3]    : ���� */
        unsigned int  modem_noc_master_hurry_upacc    : 3;  /* bit[4-6]  : MDM NOC Master�豸UPACC������HURRY���ȼ����ã�������ֵ0��7 */
        unsigned int  reserved_1                      : 1;  /* bit[7]    : ���� */
        unsigned int  modem_noc_master_awqos_upacc    : 3;  /* bit[8-10] : MDM NOC Master�豸UPACC������AWQOS���ȼ����ã�������ֵΪ0��7 */
        unsigned int  reserved_2                      : 1;  /* bit[11]   : ���� */
        unsigned int  modem_noc_master_arqos_upacc    : 3;  /* bit[12-14]: MDM NOC Master�豸UPACC������ARQOS���ȼ����ã�������ֵΪ0��7 */
        unsigned int  reserved_3                      : 1;  /* bit[15]   : ���� */
        unsigned int  modem_noc_master_press_gucipher : 3;  /* bit[16-18]: MDM NOC Master�豸GUCIPHER������PRESS���ȼ����ã�������ֵ0��7 */
        unsigned int  reserved_4                      : 1;  /* bit[19]   : ���� */
        unsigned int  modem_noc_master_hurry_gucipher : 3;  /* bit[20-22]: MDM NOC Master�豸GUCIPHER������HURRY���ȼ����ã�������ֵ0��7 */
        unsigned int  reserved_5                      : 1;  /* bit[23]   : ���� */
        unsigned int  modem_noc_master_awqos_gucipher : 3;  /* bit[24-26]: MDM NOC Master�豸GUCIPHER������AWQOS���ȼ����ã�������ֵΪ0��7 */
        unsigned int  reserved_6                      : 1;  /* bit[27]   : ���� */
        unsigned int  modem_noc_master_arqos_gucipher : 3;  /* bit[28-30]: MDM NOC Master�豸GUCIPHER������ARQOS���ȼ����ã�������ֵΪ0��7 */
        unsigned int  reserved_7                      : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_modem_noc_master_press_upacc_START     (0)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_modem_noc_master_press_upacc_END       (2)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_modem_noc_master_hurry_upacc_START     (4)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_modem_noc_master_hurry_upacc_END       (6)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_modem_noc_master_awqos_upacc_START     (8)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_modem_noc_master_awqos_upacc_END       (10)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_modem_noc_master_arqos_upacc_START     (12)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_modem_noc_master_arqos_upacc_END       (14)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_modem_noc_master_press_gucipher_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_modem_noc_master_press_gucipher_END    (18)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_modem_noc_master_hurry_gucipher_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_modem_noc_master_hurry_gucipher_END    (22)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_modem_noc_master_awqos_gucipher_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_modem_noc_master_awqos_gucipher_END    (26)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_modem_noc_master_arqos_gucipher_START  (28)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_modem_noc_master_arqos_gucipher_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_UNION
 �ṹ˵��  : MDMSC_MNOC_QOSCTRL2 �Ĵ����ṹ���塣��ַƫ����:0x02D8����ֵ:0x00000000�����:32
 �Ĵ���˵��: MDM_NOC������Master�豸�����ȼ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  modem_noc_master_press_lbbp0  : 3;  /* bit[0-2]  : MDM NOC Master�豸LBBP������PRESS���ȼ����ã�������ֵ0��7 */
        unsigned int  reserved_0                    : 1;  /* bit[3]    : ���� */
        unsigned int  modem_noc_master_hurry_lbbp0  : 3;  /* bit[4-6]  : MDM NOC Master�豸LBBP������HURRY���ȼ����ã�������ֵ0��7 */
        unsigned int  reserved_1                    : 1;  /* bit[7]    : ���� */
        unsigned int  modem_noc_master_awqos_lbbp0  : 3;  /* bit[8-10] : MDM NOC Master�豸LBBP������AWQOS���ȼ����ã�������ֵΪ0��7 */
        unsigned int  reserved_2                    : 1;  /* bit[11]   : ���� */
        unsigned int  modem_noc_master_arqos_lbbp0  : 3;  /* bit[12-14]: MDM NOC Master�豸LBBP������ARQOS���ȼ����ã�������ֵΪ0��7 */
        unsigned int  reserved_3                    : 1;  /* bit[15]   : ���� */
        unsigned int  modem_noc_master_press_gubbp0 : 3;  /* bit[16-18]: MDM NOC Master�豸GUBBP������PRESS���ȼ����ã�������ֵ0��7 */
        unsigned int  reserved_4                    : 1;  /* bit[19]   : ���� */
        unsigned int  modem_noc_master_hurry_gubbp0 : 3;  /* bit[20-22]: MDM NOC Master�豸GUBBP������HURRY���ȼ����ã�������ֵ0��7 */
        unsigned int  reserved_5                    : 1;  /* bit[23]   : ���� */
        unsigned int  modem_noc_master_awqos_gubbp0 : 3;  /* bit[24-26]: MDM NOC Master�豸GUBBP������AWQOS���ȼ����ã�������ֵΪ0��7 */
        unsigned int  reserved_6                    : 1;  /* bit[27]   : ���� */
        unsigned int  modem_noc_master_arqos_gubbp0 : 3;  /* bit[28-30]: MDM NOC Master�豸GUBBP������ARQOS���ȼ����ã�������ֵΪ0��7 */
        unsigned int  reserved_7                    : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_modem_noc_master_press_lbbp0_START   (0)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_modem_noc_master_press_lbbp0_END     (2)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_modem_noc_master_hurry_lbbp0_START   (4)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_modem_noc_master_hurry_lbbp0_END     (6)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_modem_noc_master_awqos_lbbp0_START   (8)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_modem_noc_master_awqos_lbbp0_END     (10)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_modem_noc_master_arqos_lbbp0_START   (12)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_modem_noc_master_arqos_lbbp0_END     (14)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_modem_noc_master_press_gubbp0_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_modem_noc_master_press_gubbp0_END    (18)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_modem_noc_master_hurry_gubbp0_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_modem_noc_master_hurry_gubbp0_END    (22)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_modem_noc_master_awqos_gubbp0_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_modem_noc_master_awqos_gubbp0_END    (26)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_modem_noc_master_arqos_gubbp0_START  (28)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_modem_noc_master_arqos_gubbp0_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL3_UNION
 �ṹ˵��  : MDMSC_MNOC_QOSCTRL3 �Ĵ����ṹ���塣��ַƫ����:0x02DC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  modem_noc_master_press_ccpu : 3;  /* bit[0-2]  : MDM NOC Master�豸CCPU������PRESS���ȼ����ã�������ֵ0��7 */
        unsigned int  reserved_0                  : 1;  /* bit[3]    : ���� */
        unsigned int  modem_noc_master_hurry_ccpu : 3;  /* bit[4-6]  : MDM NOC Master�豸CCPU������HURRY���ȼ����ã�������ֵ0��7 */
        unsigned int  reserved_1                  : 1;  /* bit[7]    : ���� */
        unsigned int  modem_noc_master_awqos_ccpu : 3;  /* bit[8-10] : MDM NOC Master�豸CCPU������AWQOS���ȼ����ã�������ֵΪ0��7 */
        unsigned int  reserved_2                  : 1;  /* bit[11]   : ���� */
        unsigned int  modem_noc_master_arqos_ccpu : 3;  /* bit[12-14]: MDM NOC Master�豸CCPU������ARQOS���ȼ����ã�������ֵΪ0��7 */
        unsigned int  reserved_3                  : 1;  /* bit[15]   : ���� */
        unsigned int  reserved_4                  : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL3_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL3_modem_noc_master_press_ccpu_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL3_modem_noc_master_press_ccpu_END    (2)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL3_modem_noc_master_hurry_ccpu_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL3_modem_noc_master_hurry_ccpu_END    (6)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL3_modem_noc_master_awqos_ccpu_START  (8)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL3_modem_noc_master_awqos_ccpu_END    (10)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL3_modem_noc_master_arqos_ccpu_START  (12)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL3_modem_noc_master_arqos_ccpu_END    (14)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_MEMCTRL_UNION
 �ṹ˵��  : MDMSC_MEMCTRL �Ĵ����ṹ���塣��ַƫ����:0x02E0����ֵ:0x0C9B0C9B�����:32
 �Ĵ���˵��: ������ƼĴ��������ܰ���mdmsys_ramctrl_s��mdmsys_ramctrl_d1w2r����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mdmsys_ramctrl_d1w2r : 16; /* bit[0-15] : Modem��ϵͳEDMAC��Memory���� */
        unsigned int  mdmsys_ramctrl_s     : 16; /* bit[16-31]: Modem��ϵͳ��Memory���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_MEMCTRL_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_MEMCTRL_mdmsys_ramctrl_d1w2r_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_MEMCTRL_mdmsys_ramctrl_d1w2r_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_MEMCTRL_mdmsys_ramctrl_s_START      (16)
#define SOC_MODEM_SCTRL_MDMSC_MEMCTRL_mdmsys_ramctrl_s_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_BBE16_MEMCTRL_UNION
 �ṹ˵��  : MDMSC_BBE16_MEMCTRL �Ĵ����ṹ���塣��ַƫ����:0x02E4����ֵ:0x0C9B0C9B�����:32
 �Ĵ���˵��: BBE16���üĴ��������ܰ���BBE16��trace��notrace memory����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbe16_notrace_mem_ctrl : 16; /* bit[0-15] : DSPBBE��notrace memory�Ŀ��� */
        unsigned int  bbe16_trace_mem_ctrl   : 16; /* bit[16-31]: DSPBBE��trace memory�Ŀ��� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBE16_MEMCTRL_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBE16_MEMCTRL_bbe16_notrace_mem_ctrl_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_MEMCTRL_bbe16_notrace_mem_ctrl_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_MEMCTRL_bbe16_trace_mem_ctrl_START    (16)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_MEMCTRL_bbe16_trace_mem_ctrl_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_UNION
 �ṹ˵��  : MDMSC_BBE16_DEFCTRL �Ĵ����ṹ���塣��ַƫ����:0x02E8����ֵ:0x00000008�����:32
 �Ĵ���˵��: Modem��ϵͳ�Զ���BBE16�Ŀ��ơ����ܰ���BBE16��ַ��������ָʾ,BBE16���������µ�����BBE16ʱ�����͹���ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbe16_lowpower_en             : 1;  /* bit[0]    : bbe16 ����sleepmode״̬����ʱ��ѡ���Ƶʱ�ӣ��л���ʱ�����ĵ͹���ģʽ�Ŀ���ʹ�ܣ�
                                                                         0����ʹ�ܣ�Ĭ�ϣ���
                                                                         1��ʹ�� */
        unsigned int  bbe16_pwrdwn_req              : 1;  /* bit[1]    : bbe16���������µ������źţ���BBE16�����µ�ǰ���ô��ź�Ϊ1���ڷ����ϵ�������ô��ź�Ϊ0 */
        unsigned int  bbe16_overaddr_prot_rev       : 1;  /* bit[2]    : BBE16����DDR��ַ��Խ�籣����ַ��תָʾ��
                                                                         0��ָ����ַ��Χ�ڵĵ�ַΪ��Ч���ʵ�ַ�Σ���Ĭ�ϣ�
                                                                         1��ָ����ַ��Χ��ĵ�ַΪ��Чָ����ַ�Σ� */
        unsigned int  bbe16_overaddr_prot_bypass    : 1;  /* bit[3]    : BBE16����DDR��ַ��Խ�籣��������·ָʾ��
                                                                         0������·,������Ч
                                                                         1����·��������Ч(Ĭ��) */
        unsigned int  reserved_0                    : 12; /* bit[4-15] : ���� */
        unsigned int  bbe16_lowpower_en_msk         : 1;  /* bit[16]   : bbe16_lowpower_en MSK����λ */
        unsigned int  bbe16_pwrdwn_req_msk          : 1;  /* bit[17]   : bbe16_pwrdwn_req MSK����λ */
        unsigned int  bbe16_ddraddr_prot_rev_msk    : 1;  /* bit[18]   : bbe16_ddraddr_prot_rev MSK����λ */
        unsigned int  bbe16_ddraddr_prot_bypass_msk : 1;  /* bit[19]   : bbe16_ddraddr_prot_bypass MSK����λ */
        unsigned int  reserved_1                    : 12; /* bit[20-31]: [31:16]��ÿһbit˳���Ӧbit15��bit0������bit31��16��bitд1��ͬʱ������bit15��0������Ч����bit31��16��bitд0ʱ������bit15��0���ֲ��䣻 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_bbe16_lowpower_en_START              (0)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_bbe16_lowpower_en_END                (0)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_bbe16_pwrdwn_req_START               (1)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_bbe16_pwrdwn_req_END                 (1)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_bbe16_overaddr_prot_rev_START        (2)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_bbe16_overaddr_prot_rev_END          (2)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_bbe16_overaddr_prot_bypass_START     (3)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_bbe16_overaddr_prot_bypass_END       (3)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_bbe16_lowpower_en_msk_START          (16)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_bbe16_lowpower_en_msk_END            (16)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_bbe16_pwrdwn_req_msk_START           (17)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_bbe16_pwrdwn_req_msk_END             (17)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_bbe16_ddraddr_prot_rev_msk_START     (18)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_bbe16_ddraddr_prot_rev_msk_END       (18)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_bbe16_ddraddr_prot_bypass_msk_START  (19)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_bbe16_ddraddr_prot_bypass_msk_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_UNION
 �ṹ˵��  : MDMSC_BBE16_TCM_SEL �Ĵ����ṹ���塣��ַƫ����:0x02EC����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBE16 TCM ��BBE16���ⲿ����ѡ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbe16_tcm_sel0  : 1;  /* bit[0]    : bbe16_tcm_sel[0]��ӦSRAM 0xFFB0_XXXX��BBE16 ָ��IRAM0 0xFF20_XXXX�� */
        unsigned int  bbe16_tcm_sel1  : 1;  /* bit[1]    : bbe16_tcm_sel[1]��ӦSRAM 0xFFB1_XXXX��BBE16 ָ��IRAM0 0xFF21_XXXX�� */
        unsigned int  bbe16_tcm_sel2  : 1;  /* bit[2]    : bbe16_tcm_sel[2]��ӦSRAM 0xFFB2_XXXX��BBE16 ָ��IRAM0 0xFF22_XXXX�� */
        unsigned int  bbe16_tcm_sel3  : 1;  /* bit[3]    : bbe16_tcm_sel[3]��ӦSRAM 0xFFB3_XXXX��BBE16 ָ��IRAM0 0xFF23_XXXX�� */
        unsigned int  bbe16_tcm_sel4  : 1;  /* bit[4]    : bbe16_tcm_sel[4]��ӦSRAM 0xFFB4_XXXX��BBE16 ָ��IRAM1 0xFF24_XXXX�� */
        unsigned int  bbe16_tcm_sel5  : 1;  /* bit[5]    : bbe16_tcm_sel[5]��ӦSRAM 0xFFB5_XXXX��BBE16 ָ��IRAM1 0xFF25_XXXX�� */
        unsigned int  bbe16_tcm_sel6  : 1;  /* bit[6]    : bbe16_tcm_sel[6]��ӦSRAM 0xFFB6_XXXX��BBE16 ָ��IRAM1 0xFF26_XXXX�� */
        unsigned int  bbe16_tcm_sel7  : 1;  /* bit[7]    : bbe16_tcm_sel[7]��ӦSRAM 0xFFB7_XXXX��BBE16 ����DRAM0 0xFF28_XXXX�� */
        unsigned int  bbe16_tcm_sel8  : 1;  /* bit[8]    : bbe16_tcm_sel[8]��ӦSRAM 0xFFB8_XXXX��BBE16 ����DRAM0 0xFF29_XXXX�� */
        unsigned int  bbe16_tcm_sel9  : 1;  /* bit[9]    : bbe16_tcm_sel[9]��ӦSRAM 0xFFB9_XXXX��BBE16 ����DRAM0 0xFF2A_XXXX�� */
        unsigned int  bbe16_tcm_sel10 : 1;  /* bit[10]   : bbe16_tcm_sel[10]��ӦSRAM 0xFFBA_XXXX��BBE16 ����DRAM0 0xFF2B_XXXX�� */
        unsigned int  bbe16_tcm_sel11 : 1;  /* bit[11]   : bbe16_tcm_sel[11]��ӦSRAM 0xFFBB_XXXX��BBE16 ����DRAM1 0xFF2C_XXXX�� */
        unsigned int  bbe16_tcm_sel12 : 1;  /* bit[12]   : bbe16_tcm_sel[12]��ӦSRAM 0xFFBC_XXXX��BBE16 ����DRAM1 0xFF2D_XXXX�� */
        unsigned int  bbe16_tcm_sel13 : 1;  /* bit[13]   : bbe16_tcm_sel[13]��ӦSRAM 0xFFBD_XXXX��BBE16 ����DRAM1 0xFF2E_XXXX�� */
        unsigned int  reserved        : 18; /* bit[14-31]: bbe16_tcm_sel��BBE16���ⲿ����memory��ѡ��ָʾ�źţ�Ϊ0��ʾmemory�����BBE16ʹ�ã�Ϊ1��ʶ��λΪSRAM����64KBΪ�����ȸ��ã�һ����12�����õ�Ԫ�� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel0_START   (0)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel0_END     (0)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel1_START   (1)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel1_END     (1)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel2_START   (2)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel2_END     (2)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel3_START   (3)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel3_END     (3)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel4_START   (4)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel4_END     (4)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel5_START   (5)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel5_END     (5)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel6_START   (6)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel6_END     (6)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel7_START   (7)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel7_END     (7)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel8_START   (8)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel8_END     (8)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel9_START   (9)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel9_END     (9)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel10_START  (10)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel10_END    (10)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel11_START  (11)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel11_END    (11)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel12_START  (12)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel12_END    (12)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel13_START  (13)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel13_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL0_UNION
 �ṹ˵��  : MDMSC_BBE16_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x02F0����ֵ:0x00000031�����:32
 �Ĵ���˵��: BBE16���ƼĴ��������ܰ���LTE�������ȼ���LTEDSP����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbe16_runstall       : 1;  /* bit[0]   : bbe16����/ֹͣ��
                                                               0�����У�
                                                               1��ֹͣ����Ĭ��ֵ�� */
        unsigned int  bbe16_statvectorsel  : 1;  /* bit[1]   : bbe16_statvectorsel��������Ϊ0�� */
        unsigned int  bbe16_ocdhaltonreset : 1;  /* bit[2]   : bbe16�ڽ⸴λʱǿ�н���OCDHaltģʽ��
                                                               0������ģʽ��Ĭ��ֵ����
                                                               1��OCDHaltģʽ��
                                                               ��bit�ڽ⸴λǰ6�����ڼ���10�����ڲ����޸ġ�
                                                               �ڽ⸴λ��ɺ󣬸ı��bitû��Ӱ�졣 */
        unsigned int  reserved_0           : 1;  /* bit[3]   : reserved */
        unsigned int  bbe16_pireqpriority  : 2;  /* bit[4-5] : �ⲿ��core����TCM���ȼ�ѡ���źţ�Ĭ��ֵΪ3����ʾ�ⲿ�������ȼ���� */
        unsigned int  reserved_1           : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL0_bbe16_runstall_START        (0)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL0_bbe16_runstall_END          (0)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL0_bbe16_statvectorsel_START   (1)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL0_bbe16_statvectorsel_END     (1)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL0_bbe16_ocdhaltonreset_START  (2)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL0_bbe16_ocdhaltonreset_END    (2)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL0_bbe16_pireqpriority_START   (4)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL0_bbe16_pireqpriority_END     (5)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL1_UNION
 �ṹ˵��  : MDMSC_BBE16_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x02F4����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��ϵͳ���ƼĴ��������ܰ���LTEDSP NMI�ж�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbe16_nmi_irq     : 16; /* bit[0-15] : BBENMI�ж������źš�������һ���ؾ��ɶ�DSP�����жϡ�
                                                             ��BBE�����жϡ� */
        unsigned int  bbe16_nmi_irq_msk : 16; /* bit[16-31]: [31:16]��ÿһbit˳���Ӧbit15��bit0������bit31��16��bitд1��ͬʱ������bit15��0������Ч����bit31��16��bitд0ʱ������bit15��0���ֲ��䣻 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL1_bbe16_nmi_irq_START      (0)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL1_bbe16_nmi_irq_END        (15)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL1_bbe16_nmi_irq_msk_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL1_bbe16_nmi_irq_msk_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_BBE16_STAT0_UNION
 �ṹ˵��  : MDMSC_BBE16_STAT0 �Ĵ����ṹ���塣��ַƫ����:0x02F8����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBE16״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbe16_tie_expstate : 32; /* bit[0-31]: bbe16_tie_expstate[31:0] */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBE16_STAT0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBE16_STAT0_bbe16_tie_expstate_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_STAT0_bbe16_tie_expstate_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_BBE16_STAT1_UNION
 �ṹ˵��  : MDMSC_BBE16_STAT1 �Ĵ����ṹ���塣��ַƫ����:0x02FC����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��ϵͳ״̬�Ĵ��������ܰ���LTEDSP״̬
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0      : 3;  /* bit[0-2] : ���� */
        unsigned int  bbe16_xocdmode  : 1;  /* bit[3]   : ������OCDhaltmode״ָ̬ʾ�źţ�����Ч�� */
        unsigned int  bbe16_pwaitmode : 1;  /* bit[4]   : ������sleepmode״ָ̬ʾ�źţ�����Ч��ָʾ��ǰ������ͨ��ִ��WAITIָ�����sleepmode��clockgating�����ȴ�δ�����жϻ��ѡ� */
        unsigned int  reserved_1      : 27; /* bit[5-31]: ���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBE16_STAT1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBE16_STAT1_bbe16_xocdmode_START   (3)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_STAT1_bbe16_xocdmode_END     (3)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_STAT1_bbe16_pwaitmode_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_STAT1_bbe16_pwaitmode_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_BBE16_DDRADDR_PROT_UNION
 �ṹ˵��  : MDMSC_BBE16_DDRADDR_PROT �Ĵ����ṹ���塣��ַƫ����:0x0300����ֵ:0x0FFF0000�����:32
 �Ĵ���˵��: BBE16 ����DDR������ַ�����ã���ַ���þ���Ϊ1M
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbe16_2ddr_valid_laddr : 12; /* bit[0-11] : BBE16 ����DDR��Ч��ַ����ʼ��ַ��12bit */
        unsigned int  reserved_0             : 4;  /* bit[12-15]: ���� */
        unsigned int  bbe16_2ddr_valid_haddr : 12; /* bit[16-27]: BBE16 ����DDR��Ч��ַ�ν�����ַ��12bit */
        unsigned int  reserved_1             : 4;  /* bit[28-31]: ���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBE16_DDRADDR_PROT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DDRADDR_PROT_bbe16_2ddr_valid_laddr_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DDRADDR_PROT_bbe16_2ddr_valid_laddr_END    (11)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DDRADDR_PROT_bbe16_2ddr_valid_haddr_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DDRADDR_PROT_bbe16_2ddr_valid_haddr_END    (27)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_CTRL_UNION
 �ṹ˵��  : MDMSC_MDMNOC_POWER_DOMAIN_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0304����ֵ:0x00000000�����:32
 �Ĵ���˵��: MDMNOC power domain ���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbe_domain_idlereq     : 1;  /* bit[0]    : bbe16 powerdomain idlereq
                                                                  0��normal mode
                                                                  1��idle req when this domain idle,power down or rst */
        unsigned int  bbp_domain_idlereq     : 1;  /* bit[1]    : bbp powerdomain idlereq
                                                                  0��normal mode
                                                                  1��idle req when this domain idle,power down or rst */
        unsigned int  reserved_0             : 14; /* bit[2-15] : ���� */
        unsigned int  bbe_domain_idlereq_msk : 1;  /* bit[16]   : bbe_domain_idlereq MSK����λ */
        unsigned int  bbp_domain_idlereq_msk : 1;  /* bit[17]   : bbp_domain_idlereq MSK����λ */
        unsigned int  reserved_1             : 14; /* bit[18-31]: [31:16]��ÿһbit˳���Ӧbit15��bit0������bit31��16��bitд1��ͬʱ������bit15��0������Ч����bit31��16��bitд0ʱ������bit15��0���ֲ��䣻 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_CTRL_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_CTRL_bbe_domain_idlereq_START      (0)
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_CTRL_bbe_domain_idlereq_END        (0)
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_CTRL_bbp_domain_idlereq_START      (1)
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_CTRL_bbp_domain_idlereq_END        (1)
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_CTRL_bbe_domain_idlereq_msk_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_CTRL_bbe_domain_idlereq_msk_END    (16)
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_CTRL_bbp_domain_idlereq_msk_START  (17)
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_CTRL_bbp_domain_idlereq_msk_END    (17)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_RPT_UNION
 �ṹ˵��  : MDMSC_MDMNOC_POWER_DOMAIN_RPT �Ĵ����ṹ���塣��ַƫ����:0x0308����ֵ:0x00000000�����:32
 �Ĵ���˵��: MDMNOC power domain�ϱ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbe_domain_idleack : 1;  /* bit[0]   : bbe16 powerdomain״̬�ϱ��ź�(bbe_domain_idle_ack)
                                                             0��idle req not ack
                                                             1��idle req ack
                                                             when this domain pwdn or rst,it still can be accessed if idleack and idle both valid */
        unsigned int  bbe_domain_idle    : 1;  /* bit[1]   : bbe16 powerdomain״̬�ϱ��źţ�bbe_domain_idle��
                                                             0��domain not idle
                                                             1��domain in idle
                                                             when this domain pwdn or rst,it still can be accessed if idleack and idle both valid */
        unsigned int  bbp_domain_idleack : 1;  /* bit[2]   : BBP powerdomain״̬�ϱ��ź�(bbp_domain_idle_ack)
                                                             0��idle req not ack
                                                             1��idle req ack
                                                             when this domain pwdn or rst,it still can be accessed if idleack and idle both valid */
        unsigned int  bbp_domain_idle    : 1;  /* bit[3]   : BBP powerdomain״̬�ϱ��źţ�bbp_domain_idle��
                                                             0��domain not idle
                                                             1��domain in idle
                                                             when this domain pwdn or rst,it still can be accessed if idleack and idle both valid */
        unsigned int  reserved           : 28; /* bit[4-31]:  */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_RPT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_RPT_bbe_domain_idleack_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_RPT_bbe_domain_idleack_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_RPT_bbe_domain_idle_START     (1)
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_RPT_bbe_domain_idle_END       (1)
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_RPT_bbp_domain_idleack_START  (2)
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_RPT_bbp_domain_idleack_END    (2)
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_RPT_bbp_domain_idle_START     (3)
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_RPT_bbp_domain_idle_END       (3)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_UNION
 �ṹ˵��  : MDMSC_MNOC_QOSCTRL4 �Ĵ����ṹ���塣��ַƫ����:0x030C����ֵ:0x00000000�����:32
 �Ĵ���˵��: MDM_NOC������Master�豸�����ȼ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  modem_noc_master_press_lbbp1  : 3;  /* bit[0-2]  : MDM NOC Master�豸LBBP������PRESS���ȼ����ã�������ֵ0��7 */
        unsigned int  reserved_0                    : 1;  /* bit[3]    : ���� */
        unsigned int  modem_noc_master_hurry_lbbp1  : 3;  /* bit[4-6]  : MDM NOC Master�豸LBBP������HURRY���ȼ����ã�������ֵ0��7 */
        unsigned int  reserved_1                    : 1;  /* bit[7]    : ���� */
        unsigned int  modem_noc_master_awqos_lbbp1  : 3;  /* bit[8-10] : MDM NOC Master�豸LBBP������AWQOS���ȼ����ã�������ֵΪ0��7 */
        unsigned int  reserved_2                    : 1;  /* bit[11]   : ���� */
        unsigned int  modem_noc_master_arqos_lbbp1  : 3;  /* bit[12-14]: MDM NOC Master�豸LBBP������ARQOS���ȼ����ã�������ֵΪ0��7 */
        unsigned int  reserved_3                    : 1;  /* bit[15]   : ���� */
        unsigned int  modem_noc_master_press_gubbp1 : 3;  /* bit[16-18]: MDM NOC Master�豸GUBBP������PRESS���ȼ����ã�������ֵ0��7 */
        unsigned int  reserved_4                    : 1;  /* bit[19]   : ���� */
        unsigned int  modem_noc_master_hurry_gubbp1 : 3;  /* bit[20-22]: MDM NOC Master�豸GUBBP������HURRY���ȼ����ã�������ֵ0��7 */
        unsigned int  reserved_5                    : 1;  /* bit[23]   : ���� */
        unsigned int  modem_noc_master_awqos_gubbp1 : 3;  /* bit[24-26]: MDM NOC Master�豸GUBBP������AWQOS���ȼ����ã�������ֵΪ0��7 */
        unsigned int  reserved_6                    : 1;  /* bit[27]   : ���� */
        unsigned int  modem_noc_master_arqos_gubbp1 : 3;  /* bit[28-30]: MDM NOC Master�豸GUBBP������ARQOS���ȼ����ã�������ֵΪ0��7 */
        unsigned int  reserved_7                    : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_modem_noc_master_press_lbbp1_START   (0)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_modem_noc_master_press_lbbp1_END     (2)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_modem_noc_master_hurry_lbbp1_START   (4)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_modem_noc_master_hurry_lbbp1_END     (6)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_modem_noc_master_awqos_lbbp1_START   (8)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_modem_noc_master_awqos_lbbp1_END     (10)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_modem_noc_master_arqos_lbbp1_START   (12)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_modem_noc_master_arqos_lbbp1_END     (14)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_modem_noc_master_press_gubbp1_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_modem_noc_master_press_gubbp1_END    (18)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_modem_noc_master_hurry_gubbp1_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_modem_noc_master_hurry_gubbp1_END    (22)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_modem_noc_master_awqos_gubbp1_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_modem_noc_master_awqos_gubbp1_END    (26)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_modem_noc_master_arqos_gubbp1_START  (28)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_modem_noc_master_arqos_gubbp1_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_BBP_LBUS_CTRL_UNION
 �ṹ˵��  : MDMSC_BBP_LBUS_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0310����ֵ:0x0C9B0000�����:32
 �Ĵ���˵��: BBP���ƼĴ��������ܰ���BBP Local���߿���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbpaxi_priority_set  : 2;  /* bit[0-1]  : bbp������Ч������
                                                                00:���ȼ�dma>axi
                                                                01:���ȼ�dma<axi
                                                                others:reserved */
        unsigned int  bbp_axi_bsi_cg_en    : 1;  /* bit[2]    : bbp_axi_lbuscg_en�Զ��ſ�ʹ��
                                                                0:clknotgate
                                                                1:clkgateenable */
        unsigned int  bbp_axi_rs_cg_en     : 1;  /* bit[3]    : bbp_axi_rs_cg_en�Զ��ſ�ʹ�ܡ�
                                                                0:clknotgate
                                                                1:clkgateenable */
        unsigned int  bbp_axi_gs_cg_en     : 1;  /* bit[4]    : bbp_axi_gs_cg_en�Զ��ſ�ʹ��
                                                                0:clknotgate
                                                                1:clkgateenable */
        unsigned int  bus_lockdown_protect : 2;  /* bit[5-6]  : ���߷�ֹ��������
                                                                00:�رշ���������
                                                                01:ʹ�ܷ�������������ʱʱ��512cycles
                                                                10:ʹ�ܷ�������������ʱʱ��1024cycles
                                                                11:ʹ�ܷ�������������ʱʱ��2048cycles */
        unsigned int  reserved             : 9;  /* bit[7-15] : reserved */
        unsigned int  atpram_ctrl          : 16; /* bit[16-31]: bbp�ӿ��ź�atpramctrl */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBP_LBUS_CTRL_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBP_LBUS_CTRL_bbpaxi_priority_set_START   (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_LBUS_CTRL_bbpaxi_priority_set_END     (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_LBUS_CTRL_bbp_axi_bsi_cg_en_START     (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_LBUS_CTRL_bbp_axi_bsi_cg_en_END       (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_LBUS_CTRL_bbp_axi_rs_cg_en_START      (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_LBUS_CTRL_bbp_axi_rs_cg_en_END        (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_LBUS_CTRL_bbp_axi_gs_cg_en_START      (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_LBUS_CTRL_bbp_axi_gs_cg_en_END        (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_LBUS_CTRL_bus_lockdown_protect_START  (5)
#define SOC_MODEM_SCTRL_MDMSC_BBP_LBUS_CTRL_bus_lockdown_protect_END    (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_LBUS_CTRL_atpram_ctrl_START           (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_LBUS_CTRL_atpram_ctrl_END             (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_CCPU_LAXI_STAT_UNION
 �ṹ˵��  : MDMSC_CCPU_LAXI_STAT �Ĵ����ṹ���塣��ַƫ����:0x0314����ֵ:0x00000000�����:32
 �Ĵ���˵��: CCPU�����ֲ�AXI����״̬�ϱ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ccpu_localaxi_dlock_irq : 1;  /* bit[0]    : CCPU local axi��������ָʾ,״̬����ϵͳ��λ�ı�,dlock_irq����������
                                                                   0:����������״̬
                                                                   1:��������״̬ */
        unsigned int  ccpu_localaxi_dlock_wr  : 1;  /* bit[1]    : CCPU local axi���߶�дָʾ,״̬����ϵͳ��λ�ı�,dlock_irq����������
                                                                   0:���߶�ָʾ
                                                                   1:����дָʾ */
        unsigned int  reserved_0              : 2;  /* bit[2-3]  : ���� */
        unsigned int  ccpu_localaxi_dlock_id  : 6;  /* bit[4-9]  : CCPU local axi���߲���idָʾ,״̬����ϵͳ��λ�ı�,dlock_irq���������� */
        unsigned int  reserved_1              : 6;  /* bit[10-15]: ���� */
        unsigned int  ccpu_localaxi_dlock_slv : 2;  /* bit[16-17]: CCPU local axi����slave�˿�ָʾ,��Ӧ�˿�0��1,״̬����ϵͳ��λ�ı�,dlock_irq���������� */
        unsigned int  reserved_2              : 6;  /* bit[18-23]: ���� */
        unsigned int  ccpu_localaxi_dlock_mst : 1;  /* bit[24]   : CCPU local axi����master�˿�ָʾ,��Ӧ�˿�0��1,״̬����ϵͳ��λ�ı�,dlock_irq���������� */
        unsigned int  reserved_3              : 7;  /* bit[25-31]: ���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_CCPU_LAXI_STAT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_CCPU_LAXI_STAT_ccpu_localaxi_dlock_irq_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_LAXI_STAT_ccpu_localaxi_dlock_irq_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_LAXI_STAT_ccpu_localaxi_dlock_wr_START   (1)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_LAXI_STAT_ccpu_localaxi_dlock_wr_END     (1)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_LAXI_STAT_ccpu_localaxi_dlock_id_START   (4)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_LAXI_STAT_ccpu_localaxi_dlock_id_END     (9)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_LAXI_STAT_ccpu_localaxi_dlock_slv_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_LAXI_STAT_ccpu_localaxi_dlock_slv_END    (17)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_LAXI_STAT_ccpu_localaxi_dlock_mst_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_LAXI_STAT_ccpu_localaxi_dlock_mst_END    (24)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_BBE16_LAXI_STAT_UNION
 �ṹ˵��  : MDMSC_BBE16_LAXI_STAT �Ĵ����ṹ���塣��ַƫ����:0x0318����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBE16�����ֲ�AXI����״̬�ϱ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbe16_localaxi_dlock_irq : 1;  /* bit[0]    : BBE16 local axi��������ָʾ,״̬����ϵͳ��λ�ı�,dlock_irq����������
                                                                    0:����������״̬
                                                                    1:��������״̬ */
        unsigned int  bbe16_localaxi_dlock_wr  : 1;  /* bit[1]    : BBE16 local axi���߶�дָʾ,״̬����ϵͳ��λ�ı�,dlock_irq����������
                                                                    0:���߶�ָʾ
                                                                    1:����дָʾ */
        unsigned int  reserved_0               : 2;  /* bit[2-3]  : ���� */
        unsigned int  bbe16_localaxi_dlock_id  : 6;  /* bit[4-9]  : BBE16 local axi���߲���idָʾ,״̬����ϵͳ��λ�ı�,dlock_irq���������� */
        unsigned int  reserved_1               : 6;  /* bit[10-15]: ���� */
        unsigned int  bbe16_localaxi_dlock_slv : 1;  /* bit[16]   : BBE16 local axi����slave�˿�ָʾ,״̬����ϵͳ��λ�ı�,dlock_irq���������� */
        unsigned int  reserved_2               : 7;  /* bit[17-23]: ���� */
        unsigned int  bbe16_localaxi_dlock_mst : 1;  /* bit[24]   : BBE16 local axi����master�˿�ָʾ,��Ӧ�˿�0��1,״̬����ϵͳ��λ�ı�,dlock_irq���������� */
        unsigned int  reserved_3               : 7;  /* bit[25-31]: ���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBE16_LAXI_STAT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBE16_LAXI_STAT_bbe16_localaxi_dlock_irq_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_LAXI_STAT_bbe16_localaxi_dlock_irq_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_LAXI_STAT_bbe16_localaxi_dlock_wr_START   (1)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_LAXI_STAT_bbe16_localaxi_dlock_wr_END     (1)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_LAXI_STAT_bbe16_localaxi_dlock_id_START   (4)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_LAXI_STAT_bbe16_localaxi_dlock_id_END     (9)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_LAXI_STAT_bbe16_localaxi_dlock_slv_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_LAXI_STAT_bbe16_localaxi_dlock_slv_END    (16)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_LAXI_STAT_bbe16_localaxi_dlock_mst_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_LAXI_STAT_bbe16_localaxi_dlock_mst_END    (24)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_NOC_LPOWER_CFG_UNION
 �ṹ˵��  : MDMSC_NOC_LPOWER_CFG �Ĵ����ṹ���塣��ַƫ����:0x031C����ֵ:0x00200020�����:32
 �Ĵ���˵��: MDM_NOC���ߵ͹�������ģʽ����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mdmnoc_in_lpower_pulse_width  : 10; /* bit[0-9]  : MDMNOC���߽���͹�������ģʽ������ߵ�ƽ�������ֵ */
        unsigned int  reserved_0                    : 6;  /* bit[10-15]: ���� */
        unsigned int  mdmnoc_out_lpower_pulse_width : 10; /* bit[16-25]: MDMNOC�����˳��͹�������ģʽ�ĵ͵�ƽ�������ֵ */
        unsigned int  reserved_1                    : 5;  /* bit[26-30]: ���� */
        unsigned int  mdmnoc_lpower_en              : 1;  /* bit[31]   : MDMNOC���ߵ͹�������ģʽʹ���źţ�1ΪMDMNOC֧�ֵ͹�������ģʽ��0ΪMDMNOC��֧�ֵ͹�������ģʽ */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_NOC_LPOWER_CFG_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_NOC_LPOWER_CFG_mdmnoc_in_lpower_pulse_width_START   (0)
#define SOC_MODEM_SCTRL_MDMSC_NOC_LPOWER_CFG_mdmnoc_in_lpower_pulse_width_END     (9)
#define SOC_MODEM_SCTRL_MDMSC_NOC_LPOWER_CFG_mdmnoc_out_lpower_pulse_width_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_NOC_LPOWER_CFG_mdmnoc_out_lpower_pulse_width_END    (25)
#define SOC_MODEM_SCTRL_MDMSC_NOC_LPOWER_CFG_mdmnoc_lpower_en_START               (31)
#define SOC_MODEM_SCTRL_MDMSC_NOC_LPOWER_CFG_mdmnoc_lpower_en_END                 (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG0_UNION
 �ṹ˵��  : MDMSC_DFS_DIVCFG0 �Ĵ����ṹ���塣��ַƫ����:0x0320����ֵ:0x00000700�����:32
 �Ĵ���˵��: ʱ�Ӳ������üĴ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  clk_div0_ccpu_cfg_value           : 7;  /* bit[0-6]  : ʱ�Ӳ�����
                                                                             [6:4]:����
                                                                             [3:0]:CCPUʱ�ӵķ�Ƶ��������; */
        unsigned int  clk_div0_ccpu_cfg_vld             : 1;  /* bit[7]    : ʱ�Ӳ�����Чָʾ�� */
        unsigned int  clk_div0_bbe16_lowpower_cfg_value : 7;  /* bit[8-14] : ʱ�Ӳ�����
                                                                             [14:12]:����
                                                                             [11:8]: BBE16 �͹���ʱ�ӵķ�Ƶ�������� */
        unsigned int  clk_div0_bbe16_lowpower_cfg_vld   : 1;  /* bit[15]   : ʱ�Ӳ�����Чָʾ�� */
        unsigned int  reserved_0                        : 7;  /* bit[16-22]: ʱ�Ӳ����� */
        unsigned int  reserved_1                        : 1;  /* bit[23]   : ʱ�Ӳ�����Чָʾ�� */
        unsigned int  reserved_2                        : 7;  /* bit[24-30]: ʱ�Ӳ����� */
        unsigned int  reserved_3                        : 1;  /* bit[31]   : ʱ�Ӳ�����Чָʾ�� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG0_clk_div0_ccpu_cfg_value_START            (0)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG0_clk_div0_ccpu_cfg_value_END              (6)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG0_clk_div0_ccpu_cfg_vld_START              (7)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG0_clk_div0_ccpu_cfg_vld_END                (7)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG0_clk_div0_bbe16_lowpower_cfg_value_START  (8)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG0_clk_div0_bbe16_lowpower_cfg_value_END    (14)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG0_clk_div0_bbe16_lowpower_cfg_vld_START    (15)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG0_clk_div0_bbe16_lowpower_cfg_vld_END      (15)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG1_UNION
 �ṹ˵��  : MDMSC_DFS_DIVCFG1 �Ĵ����ṹ���塣��ַƫ����:0x0324����ֵ:0x000B0300�����:32
 �Ĵ���˵��: ʱ�Ӳ������üĴ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  clk_div1_bbe16_cfg_value       : 7;  /* bit[0-6]  : ʱ�Ӳ�����
                                                                          [6:4]:����
                                                                          [3:0]:BBE16ʱ�ӵķ�Ƶ��������; */
        unsigned int  clk_div1_bbe16_cfg_value_vld   : 1;  /* bit[7]    : ʱ�Ӳ�����Чָʾ�� */
        unsigned int  clk_div1_ccpuatb_cfg_value     : 7;  /* bit[8-14] : ʱ�Ӳ�����
                                                                          [14:12]:����
                                                                          [11:8]:MCPU ATBʱ�ӵķ�Ƶ��������; */
        unsigned int  clk_div1_ccpuatb_cfg_value_vld : 1;  /* bit[15]   : ʱ�Ӳ�����Чָʾ�� */
        unsigned int  clk_div1_ccpuapb_cfg_value     : 7;  /* bit[16-22]: ʱ�Ӳ�����
                                                                          [22:20]:����
                                                                          [19:16]:MCPU APBʱ�ӵķ�Ƶ��������; */
        unsigned int  clk_div1_ccpuapb_cfg_value_vld : 1;  /* bit[23]   : ʱ�Ӳ�����Чָʾ�� */
        unsigned int  reserved_0                     : 7;  /* bit[24-30]: ʱ�Ӳ����� */
        unsigned int  reserved_1                     : 1;  /* bit[31]   : ʱ�Ӳ�����Чָʾ�� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG1_clk_div1_bbe16_cfg_value_START        (0)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG1_clk_div1_bbe16_cfg_value_END          (6)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG1_clk_div1_bbe16_cfg_value_vld_START    (7)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG1_clk_div1_bbe16_cfg_value_vld_END      (7)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG1_clk_div1_ccpuatb_cfg_value_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG1_clk_div1_ccpuatb_cfg_value_END        (14)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG1_clk_div1_ccpuatb_cfg_value_vld_START  (15)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG1_clk_div1_ccpuatb_cfg_value_vld_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG1_clk_div1_ccpuapb_cfg_value_START      (16)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG1_clk_div1_ccpuapb_cfg_value_END        (22)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG1_clk_div1_ccpuapb_cfg_value_vld_START  (23)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG1_clk_div1_ccpuapb_cfg_value_vld_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG2_UNION
 �ṹ˵��  : MDMSC_DFS_DIVCFG2 �Ĵ����ṹ���塣��ַƫ����:0x0328����ֵ:0x00050101�����:32
 �Ĵ���˵��: ʱ�Ӳ������üĴ���2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  clk_div2_noc_cfg_value           : 7;  /* bit[0-6]  : ʱ�Ӳ�����
                                                                            [6:4]:����
                                                                            [3:0]:Modem NOC ʱ�ӵķ�Ƶ��������; */
        unsigned int  clk_div2_noc_cfg_vld             : 1;  /* bit[7]    : ʱ�Ӳ�����Чָʾ�� */
        unsigned int  clk_div2_ccpu_lbus_cfg_value     : 7;  /* bit[8-14] : ʱ�Ӳ�����
                                                                            [14:12]:����
                                                                            [11:8]:CCPU LBUSʱ�ӵķ�Ƶ��������; */
        unsigned int  clk_div2_ccpu_lbus_cfg_vld       : 1;  /* bit[15]   : ʱ�Ӳ�����Чָʾ�� */
        unsigned int  clk_div2_mdmnoc_lpower_cfg_value : 7;  /* bit[16-22]: ʱ�Ӳ�����
                                                                            [22:20]:����
                                                                            [19:16]:Modem NOC�͹�������ģʽ�µ�ʱ�ӷ�Ƶ�������� */
        unsigned int  clk_div2_mdmnoc_lpower_cfg_vld   : 1;  /* bit[23]   : ʱ�Ӳ�����Чָʾ�� */
        unsigned int  reserved_0                       : 7;  /* bit[24-30]: ʱ�Ӳ����� */
        unsigned int  reserved_1                       : 1;  /* bit[31]   : ʱ�Ӳ�����Чָʾ�� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG2_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG2_clk_div2_noc_cfg_value_START            (0)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG2_clk_div2_noc_cfg_value_END              (6)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG2_clk_div2_noc_cfg_vld_START              (7)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG2_clk_div2_noc_cfg_vld_END                (7)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG2_clk_div2_ccpu_lbus_cfg_value_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG2_clk_div2_ccpu_lbus_cfg_value_END        (14)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG2_clk_div2_ccpu_lbus_cfg_vld_START        (15)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG2_clk_div2_ccpu_lbus_cfg_vld_END          (15)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG2_clk_div2_mdmnoc_lpower_cfg_value_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG2_clk_div2_mdmnoc_lpower_cfg_value_END    (22)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG2_clk_div2_mdmnoc_lpower_cfg_vld_START    (23)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG2_clk_div2_mdmnoc_lpower_cfg_vld_END      (23)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_PWUP_TIME0_UNION
 �ṹ˵��  : MDMSC_PWUP_TIME0 �Ĵ����ṹ���塣��ַƫ����:0x0330����ֵ:0x00C800C8�����:32
 �Ĵ���˵��: ��������Դ�ȶ�������1������ָʾ����������Դ�������ѹ�ȶ������ʱ�䡣�üĴ���ֻ���ϵ縴λʱ����λ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwup_time_dspbbe : 16; /* bit[0-15] : [15:0]: ָʾDSPBBE�µ�����ѹ�������ѹ�ȶ�ʱ�䣬����TCXOʱ�ӵݼ������� */
        unsigned int  pwup_time_lte    : 16; /* bit[16-31]: [31:16]: ָʾLTE�µ�����ѹ�������ѹ�ȶ�ʱ�䣬����TCXOʱ�ӵݼ������� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PWUP_TIME0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PWUP_TIME0_pwup_time_dspbbe_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PWUP_TIME0_pwup_time_dspbbe_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_PWUP_TIME0_pwup_time_lte_START     (16)
#define SOC_MODEM_SCTRL_MDMSC_PWUP_TIME0_pwup_time_lte_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_PWUP_TIME1_UNION
 �ṹ˵��  : MDMSC_PWUP_TIME1 �Ĵ����ṹ���塣��ַƫ����:0x0334����ֵ:0x00C800C8�����:32
 �Ĵ���˵��: ��������Դ�ȶ�������1������ָʾ����������Դ�������ѹ�ȶ������ʱ�䡣�üĴ���ֻ���ϵ縴λʱ����λ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwup_time_bbp_cs : 16; /* bit[0-15] : [15:0]: ָʾBBP_CS�µ��� ��ѹ�������ѹ�ȶ�ʱ�䣬����TCXOʱ�ӵݼ������� */
        unsigned int  reserved         : 16; /* bit[16-31]: [31:16]: ָʾBBP_PS�µ�����ѹ�������ѹ�ȶ�ʱ�䣬����TCXOʱ�ӵݼ�������(harq mem�����ps�����������ƣ�����) */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PWUP_TIME1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PWUP_TIME1_pwup_time_bbp_cs_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PWUP_TIME1_pwup_time_bbp_cs_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_BBEPWDN_SRAM_CTRL_UNION
 �ṹ˵��  : MDMSC_BBEPWDN_SRAM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0340����ֵ:0xFF280000�����:32
 �Ĵ���˵��: BBE16�����µ��SRAM��ַ���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbe16pwrdn_sram_remap_addr : 32; /* bit[0-31]: BBE16�����µ��CCPU����SRAM�ĵ�ַӳ�䵽TCM��ַ�Σ�Ĭ��ֵΪTCM��ʼ��ַ��0xFF280000�� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBEPWDN_SRAM_CTRL_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBEPWDN_SRAM_CTRL_bbe16pwrdn_sram_remap_addr_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_BBEPWDN_SRAM_CTRL_bbe16pwrdn_sram_remap_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_BBE16_OVERADDR_PROT_UNION
 �ṹ˵��  : MDMSC_BBE16_OVERADDR_PROT �Ĵ����ṹ���塣��ַƫ����:0x0344����ֵ:0xFE000000�����:32
 �Ĵ���˵��: BBE16����DDRԽ�籣����ӳ���ֵַ���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbe16_overaddr_prot_value : 32; /* bit[0-31]: BBE16��Խ�籣���ĵ�ֵַ��ӳ�䵽MEMORYMAP��reserved�ռ䣬Ĭ��ֵΪ0xFE00_0000 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBE16_OVERADDR_PROT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBE16_OVERADDR_PROT_bbe16_overaddr_prot_value_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_OVERADDR_PROT_bbe16_overaddr_prot_value_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT0_UNION
 �ṹ˵��  : MDMSC_SLICER_COUNT0 �Ĵ����ṹ���塣��ַƫ����:0x0350����ֵ:0x00000000�����:32
 �Ĵ���˵��: slicer count0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_slicer_count : 32; /* bit[0-31]: slicer count 32kʱ�Ӵ� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT0_sc_slicer_count_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT0_sc_slicer_count_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT1_UNION
 �ṹ˵��  : MDMSC_SLICER_COUNT1 �Ĵ����ṹ���塣��ַƫ����:0x0354����ֵ:0x00000000�����:32
 �Ĵ���˵��: slicer count1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_slicer_count_gbbp1_int : 32; /* bit[0-31]: sc_slicer_count��gbbp1_int�ж�����ֵ */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT1_sc_slicer_count_gbbp1_int_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT1_sc_slicer_count_gbbp1_int_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT2_UNION
 �ṹ˵��  : MDMSC_SLICER_COUNT2 �Ĵ����ṹ���塣��ַƫ����:0x0358����ֵ:0x00000000�����:32
 �Ĵ���˵��: slicer count2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_slicer_count_gbbp1_int_32k : 32; /* bit[0-31]: sc_slicer_count��gbbp1_int_32k�ж�����ֵ */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT2_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT2_sc_slicer_count_gbbp1_int_32k_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT2_sc_slicer_count_gbbp1_int_32k_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT3_UNION
 �ṹ˵��  : MDMSC_SLICER_COUNT3 �Ĵ����ṹ���塣��ַƫ����:0x035C����ֵ:0x00000000�����:32
 �Ĵ���˵��: slicer count3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_slicer_count_gbbp2_int : 32; /* bit[0-31]: sc_slicer_count��gbbp2_int�ж�����ֵ */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT3_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT3_sc_slicer_count_gbbp2_int_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT3_sc_slicer_count_gbbp2_int_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT4_UNION
 �ṹ˵��  : MDMSC_SLICER_COUNT4 �Ĵ����ṹ���塣��ַƫ����:0x0360����ֵ:0x00000000�����:32
 �Ĵ���˵��: slicer count4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_slicer_count_gbbp2_int_32k : 32; /* bit[0-31]: sc_slicer_count��gbbp2_int_32k�ж�����ֵ */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT4_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT4_sc_slicer_count_gbbp2_int_32k_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT4_sc_slicer_count_gbbp2_int_32k_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT5_UNION
 �ṹ˵��  : MDMSC_SLICER_COUNT5 �Ĵ����ṹ���塣��ַƫ����:0x0364����ֵ:0x00000000�����:32
 �Ĵ���˵��: slicer count5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_slicer_count_wbbp_clksw : 32; /* bit[0-31]: sc_slicer_count��wbbp2_int�ж�����ֵ */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT5_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT5_sc_slicer_count_wbbp_clksw_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT5_sc_slicer_count_wbbp_clksw_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT6_UNION
 �ṹ˵��  : MDMSC_SLICER_COUNT6 �Ĵ����ṹ���塣��ַƫ����:0x0368����ֵ:0x00000000�����:32
 �Ĵ���˵��: slicer count6
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_slicer_count_wbbp_int_32k : 32; /* bit[0-31]: sc_slicer_count��wbbp1_int_32k�ж�����ֵ */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT6_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT6_sc_slicer_count_wbbp_int_32k_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT6_sc_slicer_count_wbbp_int_32k_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT7_UNION
 �ṹ˵��  : MDMSC_SLICER_COUNT7 �Ĵ����ṹ���塣��ַƫ����:0x036C����ֵ:0x00000000�����:32
 �Ĵ���˵��: slicer count7
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_slicer_count_1x_evdo_int_32k : 32; /* bit[0-31]: sc_slicer_count��1x��evdo��wakeup�ж�����ֵ */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT7_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT7_sc_slicer_count_1x_evdo_int_32k_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT7_sc_slicer_count_1x_evdo_int_32k_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_WBBPID_UNION
 �ṹ˵��  : MDMSC_WBBPID �Ĵ����ṹ���塣��ַƫ����:0x0380����ֵ:0x48690001�����:32
 �Ĵ���˵��: WBBPID�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wbbp_id       : 16; /* bit[0-15] : 16'h0001�� */
        unsigned int  wbbp_designer : 16; /* bit[16-31]: 16'h4869,��H����ASCII����0x48����i����ASCII����0x69�� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_WBBPID_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_WBBPID_wbbp_id_START        (0)
#define SOC_MODEM_SCTRL_MDMSC_WBBPID_wbbp_id_END          (15)
#define SOC_MODEM_SCTRL_MDMSC_WBBPID_wbbp_designer_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_WBBPID_wbbp_designer_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_GBBPID_UNION
 �ṹ˵��  : MDMSC_GBBPID �Ĵ����ṹ���塣��ַƫ����:0x0384����ֵ:0x48690002�����:32
 �Ĵ���˵��: GBBPID�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gbbp_id       : 16; /* bit[0-15] : 16'h0002�� */
        unsigned int  gbbp_designer : 16; /* bit[16-31]: 16'h4869,��H����ASCII����0x48����i����ASCII����0x69�� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_GBBPID_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_GBBPID_gbbp_id_START        (0)
#define SOC_MODEM_SCTRL_MDMSC_GBBPID_gbbp_id_END          (15)
#define SOC_MODEM_SCTRL_MDMSC_GBBPID_gbbp_designer_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_GBBPID_gbbp_designer_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_LTEBBP_DRX_TIMER0_UNION
 �ṹ˵��  : MDMSC_LTEBBP_DRX_TIMER0 �Ĵ����ṹ���塣��ַƫ����:0x0388����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��ά�ɲ������������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ldrx_abs_timer_low : 32; /* bit[0-31]: lteabstimerpub[31;0]
                                                             BBP��ά�ɲ��������������32bit���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_LTEBBP_DRX_TIMER0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_LTEBBP_DRX_TIMER0_ldrx_abs_timer_low_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_LTEBBP_DRX_TIMER0_ldrx_abs_timer_low_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_LTEBBP_DRX_TIMER1_UNION
 �ṹ˵��  : MDMSC_LTEBBP_DRX_TIMER1 �Ĵ����ṹ���塣��ַƫ����:0x038C����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��ά�ɲ������������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ldrx_abs_timer_high : 32; /* bit[0-31]: lteabstimerpub[63;32]
                                                              BBP��ά�ɲ��������������32bit���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_LTEBBP_DRX_TIMER1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_LTEBBP_DRX_TIMER1_ldrx_abs_timer_high_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_LTEBBP_DRX_TIMER1_ldrx_abs_timer_high_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_SOC_VERSION_UNION
 �ṹ˵��  : MDMSC_SOC_VERSION �Ĵ����ṹ���塣��ַƫ����:0x0394����ֵ:0x20130808�����:32
 �Ĵ���˵��: Modem �汾�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  modem_soc_version : 32; /* bit[0-31]: Modem �汾�Ĵ��� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SOC_VERSION_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SOC_VERSION_modem_soc_version_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_SOC_VERSION_modem_soc_version_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_RESERVED01_UNION
 �ṹ˵��  : MDMSC_RESERVED01 �Ĵ����ṹ���塣��ַƫ����:0x0398����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����Ĵ������ṩ������Ի����ʹ�á��Ĵ�����ֵ��ϵͳ��λ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mdmsc_reserved01 : 32; /* bit[0-31]: �����Ĵ������Ĵ�����ֵ��ϵͳ��λ */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_RESERVED01_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_RESERVED01_mdmsc_reserved01_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_RESERVED01_mdmsc_reserved01_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_RESERVED02_UNION
 �ṹ˵��  : MDMSC_RESERVED02 �Ĵ����ṹ���塣��ַƫ����:0x039C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����Ĵ������ṩ������Ի����ʹ�á��Ĵ�����ֵ��ϵͳ��λ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mdmsc_reserved02 : 32; /* bit[0-31]: �����Ĵ������Ĵ�����ֵ��ϵͳ��λ */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_RESERVED02_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_RESERVED02_mdmsc_reserved02_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_RESERVED02_mdmsc_reserved02_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_RESERVED03_UNION
 �ṹ˵��  : MDMSC_RESERVED03 �Ĵ����ṹ���塣��ַƫ����:0x03A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����ϱ��Ĵ������ṩоƬECOʹ�á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mdmsc_reserved03 : 32; /* bit[0-31]: �����ϱ��Ĵ��� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_RESERVED03_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_RESERVED03_mdmsc_reserved03_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_RESERVED03_mdmsc_reserved03_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_RESERVED04_UNION
 �ṹ˵��  : MDMSC_RESERVED04 �Ĵ����ṹ���塣��ַƫ����:0x03A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����Ĵ������ṩ������Ի����ʹ�á��Ĵ�����ֵ����ϵͳ��λ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mdmsc_reserved04 : 32; /* bit[0-31]: �����Ĵ������Ĵ�����ֵ����ϵͳ��λ */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_RESERVED04_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_RESERVED04_mdmsc_reserved04_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_RESERVED04_mdmsc_reserved04_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_RESERVED05_UNION
 �ṹ˵��  : MDMSC_RESERVED05 �Ĵ����ṹ���塣��ַƫ����:0x03A8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����Ĵ������ṩ������Ի����ʹ�á��Ĵ�����ֵ����ϵͳ��λ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mdmsc_reserved05 : 32; /* bit[0-31]: �����Ĵ������Ĵ�����ֵ����ϵͳ��λ */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_RESERVED05_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_RESERVED05_mdmsc_reserved05_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_RESERVED05_mdmsc_reserved05_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_RESERVED06_UNION
 �ṹ˵��  : MDMSC_RESERVED06 �Ĵ����ṹ���塣��ַƫ����:0x03AC����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����Ĵ������ṩ������Ի����ʹ�á��Ĵ�����ֵ����ϵͳ��λ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mdmsc_reserved06 : 32; /* bit[0-31]: �����Ĵ������Ĵ�����ֵ����ϵͳ��λ */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_RESERVED06_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_RESERVED06_mdmsc_reserved06_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_RESERVED06_mdmsc_reserved06_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_FPGA_BBP_DRX_FLAG_UNION
 �ṹ˵��  : MDMSC_FPGA_BBP_DRX_FLAG �Ĵ����ṹ���塣��ַƫ����:0x03B0����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��G/W/C�͸�ARM�Ļ���ָʾ(�˼Ĵ���ֻ����FPGA����)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fpga_gcudrx_deepsleep_flag : 8;  /* bit[0-7] : [7:5]����
                                                                     [4]:cdrx_deepsleep_flag_1x
                                                                     [3]:cdrx_deepsleep_flag_evdo
                                                                     [2]:g2drx_deepsleep_flag
                                                                     [1]:g1drx_deepsleep_flag
                                                                     [0]:wdrx_deepsleep_flag */
        unsigned int  reserved                   : 24; /* bit[8-31]: BBP��G/W/C�͸�ARM�Ļ���ָʾ,�ڻ���ǰ��ǰһ��ʱ���ARMָʾ��ʱ����ǰ�������ã�ARMʹ�ø��ź��ж��Ƿ������˯�ߣ�����Ч(ֻ����FPGA����) */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_FPGA_BBP_DRX_FLAG_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_FPGA_BBP_DRX_FLAG_fpga_gcudrx_deepsleep_flag_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_FPGA_BBP_DRX_FLAG_fpga_gcudrx_deepsleep_flag_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_FPGA_PMUSSI_CNT_UNION
 �ṹ˵��  : MDMSC_FPGA_PMUSSI_CNT �Ĵ����ṹ���塣��ַƫ����:0x03B4����ֵ:0x00000000�����:32
 �Ĵ���˵��: PMU SSI cnt�����ϱ�(������FPGA����)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fpga_pmussi0_mst_cnt : 3;  /* bit[0-2]  : fpga_pmussi0_mst_cnt */
        unsigned int  reserved_0           : 1;  /* bit[3]    : ���� */
        unsigned int  fpga_pmussi1_mst_cnt : 3;  /* bit[4-6]  : fpga_pmussi1_mst_cnt */
        unsigned int  reserved_1           : 1;  /* bit[7]    : ���� */
        unsigned int  fpga_pmussi2_mst_cnt : 3;  /* bit[8-10] : fpga_pmussi2_mst_cnt */
        unsigned int  reserved_2           : 21; /* bit[11-31]: PMU SSI cnt�����ϱ�(������FPGA����)
                                                                ���� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_FPGA_PMUSSI_CNT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_FPGA_PMUSSI_CNT_fpga_pmussi0_mst_cnt_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_FPGA_PMUSSI_CNT_fpga_pmussi0_mst_cnt_END    (2)
#define SOC_MODEM_SCTRL_MDMSC_FPGA_PMUSSI_CNT_fpga_pmussi1_mst_cnt_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_FPGA_PMUSSI_CNT_fpga_pmussi1_mst_cnt_END    (6)
#define SOC_MODEM_SCTRL_MDMSC_FPGA_PMUSSI_CNT_fpga_pmussi2_mst_cnt_START  (8)
#define SOC_MODEM_SCTRL_MDMSC_FPGA_PMUSSI_CNT_fpga_pmussi2_mst_cnt_END    (10)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_TESTPIN_SEL_UNION
 �ṹ˵��  : MDMSC_TESTPIN_SEL �Ĵ����ṹ���塣��ַƫ����:0x03B8����ֵ:0x00000000�����:32
 �Ĵ���˵��: Modem��ϵͳModem_SC TESTPIN�ź�ѡ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mdmsc_testpin_sel : 5;  /* bit[0-4] : Modem SC testpinѡ������ź� */
        unsigned int  reserved          : 27; /* bit[5-31]:  */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_TESTPIN_SEL_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_TESTPIN_SEL_mdmsc_testpin_sel_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_TESTPIN_SEL_mdmsc_testpin_sel_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MODEM_TESTPIN_SEL_UNION
 �ṹ˵��  : MODEM_TESTPIN_SEL �Ĵ����ṹ���塣��ַƫ����:0x03BC����ֵ:0x00000000�����:32
 �Ĵ���˵��: Modem��ϵͳTESTPIN�ź�ѡ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  modem_testpin_sel : 5;  /* bit[0-4] : Modem��ϵͳtestpinѡ������ź� */
        unsigned int  reserved          : 27; /* bit[5-31]:  */
    } reg;
} SOC_MODEM_SCTRL_MODEM_TESTPIN_SEL_UNION;
#endif
#define SOC_MODEM_SCTRL_MODEM_TESTPIN_SEL_modem_testpin_sel_START  (0)
#define SOC_MODEM_SCTRL_MODEM_TESTPIN_SEL_modem_testpin_sel_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTEN_UNION
 �ṹ˵��  : MDMSC_BBIT_GLB_RSTEN �Ĵ����ṹ���塣��ַƫ����:0x03D0����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBIT MODEM��ϵͳȫ�ָ�λʹ�ܼĴ���������ʹ�����踴λ���Ա���д1����ӦIP���븴λ״̬��д0��Ӱ�츴λ״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fpga_bbit_modem_glb_rsten : 1;  /* bit[0]   : ������FPGA BBITƽ̨Modemȫ����λ */
        unsigned int  reserved                  : 31; /* bit[1-31]: ��λʹ�ܶ������£�д1��λʹ�ܣ��� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTEN_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTEN_fpga_bbit_modem_glb_rsten_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTEN_fpga_bbit_modem_glb_rsten_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTDIS_UNION
 �ṹ˵��  : MDMSC_BBIT_GLB_RSTDIS �Ĵ����ṹ���塣��ַƫ����:0x03D4����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBIT MODEM��ϵͳȫ�ָ�λ��ֹ�Ĵ��������ڽ�ֹ���踴λ���Ա���д1����Ӧ��������λ��д0��Ӱ�츴λʹ�ܵ�״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fpga_bbit_modem_glb_rstdis : 1;  /* bit[0]   : ������FPGA BBITƽ̨Modemȫ����λ */
        unsigned int  reserved                   : 31; /* bit[1-31]: ��λ��ֹ�������£�д1��λ������� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTDIS_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTDIS_fpga_bbit_modem_glb_rstdis_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTDIS_fpga_bbit_modem_glb_rstdis_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTEN_STAT_UNION
 �ṹ˵��  : MDMSC_BBIT_GLB_RSTEN_STAT �Ĵ����ṹ���塣��ַƫ����:0x03D8����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBIT MODEM��ϵͳȫ�ָ�λ״̬�Ĵ��������ڻض������踴λ��״̬�����踴λ�����ź��辭��ͬ��������ˣ�����ļĴ���ֵ���ӳ���Ӧʱ����ļ������ں��������Ӧ�⸴λ״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fpga_bbit_modem_glb_rsten_stat : 1;  /* bit[0]   : ������FPGA BBITƽ̨Modemȫ����λ */
        unsigned int  reserved                       : 31; /* bit[1-31]: ��λ״̬�������£��ߵ�ƽ��ʾ���ڸ�λ�� */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTEN_STAT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTEN_STAT_fpga_bbit_modem_glb_rsten_stat_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTEN_STAT_fpga_bbit_modem_glb_rsten_stat_END    (0)






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

#endif /* end of soc_modem_sctrl_interface.h */
