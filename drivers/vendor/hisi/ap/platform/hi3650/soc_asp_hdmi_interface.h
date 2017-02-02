/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_asp_hdmi_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:18:10
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_ASP_HDMI.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_ASP_HDMI_INTERFACE_H__
#define __SOC_ASP_HDMI_INTERFACE_H__

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
/* �Ĵ���˵��������ͨ��TX3���ƼĴ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_ASP_TX3_UNION */
#define SOC_ASP_HDMI_ASP_TX3_ADDR(base)               ((base) + (0x000))

/* �Ĵ���˵����ASP DMAʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_ASP_DER_UNION */
#define SOC_ASP_HDMI_ASP_DER_ADDR(base)               ((base) + (0x004))

/* �Ĵ���˵����ASP DMAֹͣʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_ASP_DSTOP_UNION */
#define SOC_ASP_HDMI_ASP_DSTOP_ADDR(base)             ((base) + (0x008))

/* �Ĵ���˵����ASPȫ���ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_ASP_ASS_ISR_UNION */
#define SOC_ASP_HDMI_ASP_ASS_ISR_ADDR(base)           ((base) + (0x00C))

/* �Ĵ���˵����ASPԭʼ״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_ASP_IRSR_UNION */
#define SOC_ASP_HDMI_ASP_IRSR_ADDR(base)              ((base) + (0x010))

/* �Ĵ���˵����ASP�ж�ʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_ASP_IER_UNION */
#define SOC_ASP_HDMI_ASP_IER_ADDR(base)               ((base) + (0x014))

/* �Ĵ���˵����ASP���κ�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_ASP_IMSR_UNION */
#define SOC_ASP_HDMI_ASP_IMSR_ADDR(base)              ((base) + (0x018))

/* �Ĵ���˵����ASP�ж�����Ĵ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_ASP_ICR_UNION */
#define SOC_ASP_HDMI_ASP_ICR_ADDR(base)               ((base) + (0x01C))

/* �Ĵ���˵����ͨ���¸���ʼ�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_ASP_PCMNSSR_UNION */
#define SOC_ASP_HDMI_ASP_PCMNSSR_ADDR(base)           ((base) + (0x020))

/* �Ĵ���˵����PCM3ͨ��0��������Ĵ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_ASP_P30CGR_UNION */
#define SOC_ASP_HDMI_ASP_P30CGR_ADDR(base)            ((base) + (0x028))

/* �Ĵ���˵����PCM3ͨ��1��������Ĵ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_ASP_P31CGR_UNION */
#define SOC_ASP_HDMI_ASP_P31CGR_ADDR(base)            ((base) + (0x02C))

/* �Ĵ���˵����PCM3ͨ��2��������Ĵ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_ASP_P32CGR_UNION */
#define SOC_ASP_HDMI_ASP_P32CGR_ADDR(base)            ((base) + (0x030))

/* �Ĵ���˵����PCM3ͨ��3��������Ĵ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_ASP_P33CGR_UNION */
#define SOC_ASP_HDMI_ASP_P33CGR_ADDR(base)            ((base) + (0x034))

/* �Ĵ���˵����PCM3ͨ��4��������Ĵ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_ASP_P34CGR_UNION */
#define SOC_ASP_HDMI_ASP_P34CGR_ADDR(base)            ((base) + (0x038))

/* �Ĵ���˵����PCM3ͨ��5��������Ĵ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_ASP_P35CGR_UNION */
#define SOC_ASP_HDMI_ASP_P35CGR_ADDR(base)            ((base) + (0x03C))

/* �Ĵ���˵����PCM3ͨ��6��������Ĵ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_ASP_P36CGR_UNION */
#define SOC_ASP_HDMI_ASP_P36CGR_ADDR(base)            ((base) + (0x040))

/* �Ĵ���˵����PCM3ͨ��7��������Ĵ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_ASP_P37CGR_UNION */
#define SOC_ASP_HDMI_ASP_P37CGR_ADDR(base)            ((base) + (0x044))

/* �Ĵ���˵����PCM3Aͨ��������ʼ��ַ�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_ASP_P3ASAR_UNION */
#define SOC_ASP_HDMI_ASP_P3ASAR_ADDR(base)            ((base) + (0x048))

/* �Ĵ���˵����PCM3Aͨ�����˳��ȼĴ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_ASP_P3ADLR_UNION */
#define SOC_ASP_HDMI_ASP_P3ADLR_ADDR(base)            ((base) + (0x04C))

/* �Ĵ���˵����PCM3Bͨ��������ʼ��ַ�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_ASP_P3BSAR_UNION */
#define SOC_ASP_HDMI_ASP_P3BSAR_ADDR(base)            ((base) + (0x050))

/* �Ĵ���˵����PCM3Bͨ�����˳��ȼĴ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_ASP_P3BDLR_UNION */
#define SOC_ASP_HDMI_ASP_P3BDLR_ADDR(base)            ((base) + (0x054))

/* �Ĵ���˵�����������ݲ��Žӿ�ѡ��Ĵ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_ASP_SPDIFSEL_UNION */
#define SOC_ASP_HDMI_ASP_SPDIFSEL_ADDR(base)          ((base) + (0x058))

/* �Ĵ���˵����DMAֹͣʱPCM3Aͨ�����˳���״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_ASP_P3ADLS_UNION */
#define SOC_ASP_HDMI_ASP_P3ADLS_ADDR(base)            ((base) + (0x05C))

/* �Ĵ���˵����DMAֹͣʱPCM3Bͨ�����˳���״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_ASP_P3BDLS_UNION */
#define SOC_ASP_HDMI_ASP_P3BDLS_ADDR(base)            ((base) + (0x060))

/* �Ĵ���˵����DMA�������ݻ���FIFO״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_ASP_FDS_UNION */
#define SOC_ASP_HDMI_ASP_FDS_ADDR(base)               ((base) + (0x064))

/* �Ĵ���˵����PCM3Aͨ��DMA����ʣ�೤��״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_ASP_P3ADL_UNION */
#define SOC_ASP_HDMI_ASP_P3ADL_ADDR(base)             ((base) + (0x068))

/* �Ĵ���˵����PCM3Bͨ��DMA����ʣ�೤��״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_ASP_P3BDL_UNION */
#define SOC_ASP_HDMI_ASP_P3BDL_ADDR(base)             ((base) + (0x06C))

/* �Ĵ���˵����ASP_HDMIģ�鰲ȫ�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_ASP_SECURE_UNION */
#define SOC_ASP_HDMI_ASP_SECURE_ADDR(base)            ((base) + (0x070))

/* �Ĵ���˵����MIXCTL�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_RESERVED1_UNION */
#define SOC_ASP_HDMI_RESERVED1_ADDR(base)             ((base) + (0x074))

/* �Ĵ���˵����SIO1��Ƶ�ӿ�ѡ��Ĵ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_SIO1_ASPIF_SEL_UNION */
#define SOC_ASP_HDMI_SIO1_ASPIF_SEL_ADDR(base)        ((base) + (0x400))

/* �Ĵ���˵����SIO1�ж�ԭʼ״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_SIO1_RAW_INT_UNION */
#define SOC_ASP_HDMI_SIO1_RAW_INT_ADDR(base)          ((base) + (0x408))

/* �Ĵ���˵����SIO1�ж�����Ĵ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_SIO1_INT_CLR_UNION */
#define SOC_ASP_HDMI_SIO1_INT_CLR_ADDR(base)          ((base) + (0x40C))

/* �Ĵ���˵����SIO1�ж�ʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_SIO1_INT_ENABLE_UNION */
#define SOC_ASP_HDMI_SIO1_INT_ENABLE_ADDR(base)       ((base) + (0x410))

/* �Ĵ���˵����SIO1�ж����κ�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_SIO1_INT_MASKED_STATUS_UNION */
#define SOC_ASP_HDMI_SIO1_INT_MASKED_STATUS_ADDR(base) ((base) + (0x414))

/* �Ĵ���˵����SIO1 I2Sģʽ����
   λ����UNION�ṹ:  SOC_ASP_HDMI_SIO1_I2S_SET_UNION */
#define SOC_ASP_HDMI_SIO1_I2S_SET_ADDR(base)          ((base) + (0x41C))

/* �Ĵ���˵����SIO1 I2Sģʽ�������
   λ����UNION�ṹ:  SOC_ASP_HDMI_SIO1_I2S_CLR_UNION */
#define SOC_ASP_HDMI_SIO1_I2S_CLR_ADDR(base)          ((base) + (0x420))

/* �Ĵ���˵����SIO1 ����ͨ��״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_SIO1_TX_STA_UNION */
#define SOC_ASP_HDMI_SIO1_TX_STA_ADDR(base)           ((base) + (0x42C))

/* �Ĵ���˵����SIO1��fifo����Ĵ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_SIO1_CLR_UNION */
#define SOC_ASP_HDMI_SIO1_CLR_ADDR(base)              ((base) + (0x438))

/* �Ĵ���˵����SIO1����0������������
   λ����UNION�ṹ:  SOC_ASP_HDMI_SIO1_TST_TX0_DATA_UNION */
#define SOC_ASP_HDMI_SIO1_TST_TX0_DATA_ADDR(base)     ((base) + (0x440))

/* �Ĵ���˵����SIO1����1������������
   λ����UNION�ṹ:  SOC_ASP_HDMI_SIO1_TST_TX1_DATA_UNION */
#define SOC_ASP_HDMI_SIO1_TST_TX1_DATA_ADDR(base)     ((base) + (0x444))

/* �Ĵ���˵����SIO1����2������������
   λ����UNION�ṹ:  SOC_ASP_HDMI_SIO1_TST_TX2_DATA_UNION */
#define SOC_ASP_HDMI_SIO1_TST_TX2_DATA_ADDR(base)     ((base) + (0x448))

/* �Ĵ���˵����SIO1����3������������
   λ����UNION�ṹ:  SOC_ASP_HDMI_SIO1_TST_TX3_DATA_UNION */
#define SOC_ASP_HDMI_SIO1_TST_TX3_DATA_ADDR(base)     ((base) + (0x44C))

/* �Ĵ���˵����SIO1����4������������
   λ����UNION�ṹ:  SOC_ASP_HDMI_SIO1_TST_TX4_DATA_UNION */
#define SOC_ASP_HDMI_SIO1_TST_TX4_DATA_ADDR(base)     ((base) + (0x450))

/* �Ĵ���˵����SIO1����5������������
   λ����UNION�ṹ:  SOC_ASP_HDMI_SIO1_TST_TX5_DATA_UNION */
#define SOC_ASP_HDMI_SIO1_TST_TX5_DATA_ADDR(base)     ((base) + (0x454))

/* �Ĵ���˵����SIO1����6������������
   λ����UNION�ṹ:  SOC_ASP_HDMI_SIO1_TST_TX6_DATA_UNION */
#define SOC_ASP_HDMI_SIO1_TST_TX6_DATA_ADDR(base)     ((base) + (0x458))

/* �Ĵ���˵����SIO1����7������������
   λ����UNION�ṹ:  SOC_ASP_HDMI_SIO1_TST_TX7_DATA_UNION */
#define SOC_ASP_HDMI_SIO1_TST_TX7_DATA_ADDR(base)     ((base) + (0x45C))

/* �Ĵ���˵����SPDIF���ƼĴ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_SPDIF_CTRL_UNION */
#define SOC_ASP_HDMI_SPDIF_CTRL_ADDR(base)            ((base) + (0x800))

/* �Ĵ���˵����SPDIF���üĴ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_SPDIF_CONFIG_UNION */
#define SOC_ASP_HDMI_SPDIF_CONFIG_ADDR(base)          ((base) + (0x804))

/* �Ĵ���˵����SPDIF���κ��ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_SPDIF_INTRUPT_UNION */
#define SOC_ASP_HDMI_SPDIF_INTRUPT_ADDR(base)         ((base) + (0x808))

/* �Ĵ���˵����SPDIF�ж����μĴ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_SPDIF_INTR_MASK_UNION */
#define SOC_ASP_HDMI_SPDIF_INTR_MASK_ADDR(base)       ((base) + (0x80C))

/* �Ĵ���˵����SPDIF FIFO״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_SPDIF_FIFO_STATE_UNION */
#define SOC_ASP_HDMI_SPDIF_FIFO_STATE_ADDR(base)      ((base) + (0x810))

/* �Ĵ���˵�����ŵ�״̬��Ϣ�Ĵ���1
   λ����UNION�ṹ:  SOC_ASP_HDMI_SPDIF_CH_STATUS1_UNION */
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ADDR(base)      ((base) + (0x820))

/* �Ĵ���˵�����ŵ�״̬��Ϣ�Ĵ���2
   λ����UNION�ṹ:  SOC_ASP_HDMI_SPDIF_CH_STATUS2_UNION */
#define SOC_ASP_HDMI_SPDIF_CH_STATUS2_ADDR(base)      ((base) + (0x824))

/* �Ĵ���˵�����ŵ�״̬��Ϣ�Ĵ���3
   λ����UNION�ṹ:  SOC_ASP_HDMI_SPDIF_CH_STATUS3_UNION */
#define SOC_ASP_HDMI_SPDIF_CH_STATUS3_ADDR(base)      ((base) + (0x828))

/* �Ĵ���˵�����ŵ�״̬��Ϣ�Ĵ���4
   λ����UNION�ṹ:  SOC_ASP_HDMI_SPDIF_CH_STATUS4_UNION */
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ADDR(base)      ((base) + (0x82C))

/* �Ĵ���˵�����ŵ�״̬��Ϣ�Ĵ���5
   λ����UNION�ṹ:  SOC_ASP_HDMI_SPDIF_CH_STATUS5_UNION */
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ADDR(base)      ((base) + (0x830))

/* �Ĵ���˵�����û����ݼĴ���1
   λ����UNION�ṹ:  SOC_ASP_HDMI_SPDIF_USER_DATA1_UNION */
#define SOC_ASP_HDMI_SPDIF_USER_DATA1_ADDR(base)      ((base) + (0x840))

/* �Ĵ���˵�����û����ݼĴ���2
   λ����UNION�ṹ:  SOC_ASP_HDMI_SPDIF_USER_DATA2_UNION */
#define SOC_ASP_HDMI_SPDIF_USER_DATA2_ADDR(base)      ((base) + (0x844))

/* �Ĵ���˵�����û����ݼĴ���3
   λ����UNION�ṹ:  SOC_ASP_HDMI_SPDIF_USER_DATA3_UNION */
#define SOC_ASP_HDMI_SPDIF_USER_DATA3_ADDR(base)      ((base) + (0x848))

/* �Ĵ���˵�����û����ݼĴ���4
   λ����UNION�ṹ:  SOC_ASP_HDMI_SPDIF_USER_DATA4_UNION */
#define SOC_ASP_HDMI_SPDIF_USER_DATA4_ADDR(base)      ((base) + (0x84C))

/* �Ĵ���˵�����û����ݼĴ���5
   λ����UNION�ṹ:  SOC_ASP_HDMI_SPDIF_USER_DATA5_UNION */
#define SOC_ASP_HDMI_SPDIF_USER_DATA5_ADDR(base)      ((base) + (0x850))

/* �Ĵ���˵�����汾��Ϣ�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_HDMI_SPDIF_EDITION_UNION */
#define SOC_ASP_HDMI_SPDIF_EDITION_ADDR(base)         ((base) + (0x8F0))





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
 �ṹ��    : SOC_ASP_HDMI_ASP_TX3_UNION
 �ṹ˵��  : ASP_TX3 �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��TX3���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pcm3en                 : 1;  /* bit[0]    : TX3ͨ��ʹ�ܡ�
                                                                  0����ʹ�ܣ�
                                                                  1��ʹ�ܡ� */
        unsigned int  pcm3ge                 : 1;  /* bit[1]    : TX3ͨ������ʹ�ܡ�
                                                                  0����ʹ�ܣ�
                                                                  1��ʹ�ܡ� */
        unsigned int  pcm3tsen               : 1;  /* bit[2]    : TX3 ͸��ʹ�ܡ�
                                                                  0����ʹ�ܣ�
                                                                  1��ʹ�ܡ� */
        unsigned int  pcm3_data_in_width     : 3;  /* bit[3-5]  : TX3ͨ����Ƶ����λ��ѡ��
                                                                  000��16bit��
                                                                  001��18bit��
                                                                  010��20bit��
                                                                  011��24bit��
                                                                  100��8bit�� */
        unsigned int  pcm3_halfword_align_en : 1;  /* bit[6]    : TX3 16λ�ֶ���ʹ�ܡ�
                                                                  0����ʹ�ܣ�32λ�ֶ��룻
                                                                  1��ʹ�ܣ�16λ�ֶ��롣
                                                                  ע�⣺��Ƶ����λ��Ϊ8bitʱ��ֻ֧��16λ�ֶ��룻
                                                                  ��Ƶ����λ��Ϊ18bit��20bit��24bitʱ��ֻ֧��32λ�ֶ��롣 */
        unsigned int  pcm3_ch_num            : 3;  /* bit[7-9]  : TX3ͨ��������Ŀѡ��
                                                                  000��1������
                                                                  001��2������
                                                                  010��3������
                                                                  011��4������
                                                                  100��5������
                                                                  101��6������
                                                                  110��7������
                                                                  111��8������
                                                                  ע�⣺��Ƶ����λ��Ϊ8bitʱ��������Ŀֻ��ѡ��1������2������
                                                                  ��Ƶ����λ��Ϊ16bitʱ��������Ŀ��ѡ1������2������4������6������8������
                                                                  ��Ƶ����λ��Ϊ18bit��20bit��24bitʱ��������Ŀ��ѡ2������4������6������8������ */
        unsigned int  pcm3_8bit_usymb        : 1;  /* bit[10]   : TX3 8bit���ݵķ���֧�֡�
                                                                  0���з�������
                                                                  1���޷������� */
        unsigned int  pcm3_big_endian        : 1;  /* bit[11]   : TX3ͨ����Ƶ���ݴ�С��ѡ��
                                                                  0��С�ˣ�
                                                                  1����ˡ�
                                                                  ע�⣺ֻ���������֧�ִ�С�˿��䣺8bitλ�����Ƶ��16λ�ֶ���ĵ�����16bitλ�����Ƶ�� */
        unsigned int  pcm3_switch_order      : 1;  /* bit[12]   : TX3ͨ����Ƶ��������˳�򽻻�ʹ�ܡ�
                                                                  0����ʹ������˳�򽻻���
                                                                  1��0��1�������ݽ�����2��3�������ݽ�����4��5�������ݽ�����6��7�������ݽ����� */
        unsigned int  reserved               : 19; /* bit[13-31]: ������ */
    } reg;
} SOC_ASP_HDMI_ASP_TX3_UNION;
#endif
#define SOC_ASP_HDMI_ASP_TX3_pcm3en_START                  (0)
#define SOC_ASP_HDMI_ASP_TX3_pcm3en_END                    (0)
#define SOC_ASP_HDMI_ASP_TX3_pcm3ge_START                  (1)
#define SOC_ASP_HDMI_ASP_TX3_pcm3ge_END                    (1)
#define SOC_ASP_HDMI_ASP_TX3_pcm3tsen_START                (2)
#define SOC_ASP_HDMI_ASP_TX3_pcm3tsen_END                  (2)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_data_in_width_START      (3)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_data_in_width_END        (5)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_halfword_align_en_START  (6)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_halfword_align_en_END    (6)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_ch_num_START             (7)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_ch_num_END               (9)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_8bit_usymb_START         (10)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_8bit_usymb_END           (10)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_big_endian_START         (11)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_big_endian_END           (11)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_switch_order_START       (12)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_switch_order_END         (12)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_ASP_DER_UNION
 �ṹ˵��  : ASP_DER �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x00000000�����:32
 �Ĵ���˵��: ASP DMAʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pcm3ade  : 1;  /* bit[0]   : PCM3ͨ��A��DMAʹ�ܡ�
                                                   0��DMA��ʹ�ܣ�
                                                   1��DMAʹ�ܡ�
                                                   ע�⣺�üĴ������д��1����Ӳ�����㣬���д��0����Ч�� */
        unsigned int  pcm3bde  : 1;  /* bit[1]   : PCM3ͨ��B��DMAʹ�ܡ�
                                                   0��DMA��ʹ�ܣ�
                                                   1��DMAʹ�ܡ�
                                                   ע�⣺�üĴ������д��1����Ӳ�����㣬���д��0����Ч�� */
        unsigned int  reserved : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_ASP_HDMI_ASP_DER_UNION;
#endif
#define SOC_ASP_HDMI_ASP_DER_pcm3ade_START   (0)
#define SOC_ASP_HDMI_ASP_DER_pcm3ade_END     (0)
#define SOC_ASP_HDMI_ASP_DER_pcm3bde_START   (1)
#define SOC_ASP_HDMI_ASP_DER_pcm3bde_END     (1)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_ASP_DSTOP_UNION
 �ṹ˵��  : ASP_DSTOP �Ĵ����ṹ���塣��ַƫ����:0x008����ֵ:0x00000000�����:32
 �Ĵ���˵��: ASP DMAֹͣʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pcm3ads  : 1;  /* bit[0]   : PCM3ͨ��A��DMAֹͣʹ�ܡ�
                                                   0��DMAֹͣ��ʹ�ܣ�
                                                   1��DMAֹͣ��
                                                   ע�⣺�üĴ������д��1����Ӳ�����㣬���д��0����Ч�� */
        unsigned int  pcm3bds  : 1;  /* bit[1]   : PCM3ͨ��B��DMAֹͣʹ�ܡ�
                                                   0��DMAֹͣ��ʹ�ܣ�
                                                   1��DMAֹͣ��
                                                   ע�⣺�üĴ������д��1����Ӳ�����㣬���д��0����Ч�� */
        unsigned int  reserved : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_ASP_HDMI_ASP_DSTOP_UNION;
#endif
#define SOC_ASP_HDMI_ASP_DSTOP_pcm3ads_START   (0)
#define SOC_ASP_HDMI_ASP_DSTOP_pcm3ads_END     (0)
#define SOC_ASP_HDMI_ASP_DSTOP_pcm3bds_START   (1)
#define SOC_ASP_HDMI_ASP_DSTOP_pcm3bds_END     (1)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_ASP_ASS_ISR_UNION
 �ṹ˵��  : ASP_ASS_ISR �Ĵ����ṹ���塣��ַƫ����:0x00C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ASPȫ���ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sio1is   : 1;  /* bit[0]   : ��ƵSIO1�ӿڲ���ģ���ж�״̬��
                                                   0�����жϣ�
                                                   1�����жϡ� */
        unsigned int  spdifis  : 1;  /* bit[1]   : ��ƵSPDIF�ӿڲ���ģ���ж�״̬��
                                                   0�����жϣ�
                                                   1�����жϡ� */
        unsigned int  aspis    : 1;  /* bit[2]   : ASP����ģ���ж�״̬��
                                                   0�����жϣ�
                                                   1�����жϡ� */
        unsigned int  reserved : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_ASP_HDMI_ASP_ASS_ISR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_ASS_ISR_sio1is_START    (0)
#define SOC_ASP_HDMI_ASP_ASS_ISR_sio1is_END      (0)
#define SOC_ASP_HDMI_ASP_ASS_ISR_spdifis_START   (1)
#define SOC_ASP_HDMI_ASP_ASS_ISR_spdifis_END     (1)
#define SOC_ASP_HDMI_ASP_ASS_ISR_aspis_START     (2)
#define SOC_ASP_HDMI_ASP_ASS_ISR_aspis_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_ASP_IRSR_UNION
 �ṹ˵��  : ASP_IRSR �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x00000000�����:32
 �Ĵ���˵��: ASPԭʼ״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p3adfirs : 1;  /* bit[0]   : PCM3ͨ��A��DMA����ԭʼ�жϡ�
                                                   0�����жϣ�
                                                   1�����жϡ� */
        unsigned int  p3bdfirs : 1;  /* bit[1]   : PCM3ͨ��B��DMA����ԭʼ�жϡ�
                                                   0�����жϣ�
                                                   1�����жϡ� */
        unsigned int  aberirs  : 1;  /* bit[2]   : ASPģ������error��Ӧԭʼ�жϡ�
                                                   0�����жϣ�
                                                   1�����жϡ�
                                                   ע�⣺ASP��AHB master�������߷������������ϵ�Slave����HRESP��Ӧ����ΪERRORʱ���������жϡ����磬��RO���͵�ַ��д�����ȡ� */
        unsigned int  reserved : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_ASP_HDMI_ASP_IRSR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_IRSR_p3adfirs_START  (0)
#define SOC_ASP_HDMI_ASP_IRSR_p3adfirs_END    (0)
#define SOC_ASP_HDMI_ASP_IRSR_p3bdfirs_START  (1)
#define SOC_ASP_HDMI_ASP_IRSR_p3bdfirs_END    (1)
#define SOC_ASP_HDMI_ASP_IRSR_aberirs_START   (2)
#define SOC_ASP_HDMI_ASP_IRSR_aberirs_END     (2)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_ASP_IER_UNION
 �ṹ˵��  : ASP_IER �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x00000000�����:32
 �Ĵ���˵��: ASP�ж�ʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p3adfie  : 1;  /* bit[0]   : PCM3ͨ��A��DMA�����ж�ʹ�ܡ�
                                                   0����ʹ�ܣ�
                                                   1��ʹ�ܡ� */
        unsigned int  p3bdfie  : 1;  /* bit[1]   : PCM3ͨ��B��DMA�����ж�ʹ�ܡ�
                                                   0����ʹ�ܣ�
                                                   1��ʹ�ܡ� */
        unsigned int  aberie   : 1;  /* bit[2]   : ASPģ������error��Ӧ�ж�ʹ�ܡ�
                                                   0����ʹ�ܣ�
                                                   1��ʹ�ܡ� */
        unsigned int  reserved : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_ASP_HDMI_ASP_IER_UNION;
#endif
#define SOC_ASP_HDMI_ASP_IER_p3adfie_START   (0)
#define SOC_ASP_HDMI_ASP_IER_p3adfie_END     (0)
#define SOC_ASP_HDMI_ASP_IER_p3bdfie_START   (1)
#define SOC_ASP_HDMI_ASP_IER_p3bdfie_END     (1)
#define SOC_ASP_HDMI_ASP_IER_aberie_START    (2)
#define SOC_ASP_HDMI_ASP_IER_aberie_END      (2)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_ASP_IMSR_UNION
 �ṹ˵��  : ASP_IMSR �Ĵ����ṹ���塣��ַƫ����:0x018����ֵ:0x00000000�����:32
 �Ĵ���˵��: ASP���κ�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p3adfims : 1;  /* bit[0]   : PCM3ͨ��A��DMA�������κ��жϡ�
                                                   0�����жϣ�
                                                   1�����жϡ� */
        unsigned int  p3bdfims : 1;  /* bit[1]   : PCM3ͨ��B��DMA�������κ��жϡ�
                                                   0�����жϣ�
                                                   1�����жϡ� */
        unsigned int  aberims  : 1;  /* bit[2]   : ASPģ������error��Ӧ���κ��жϡ�
                                                   0�����жϣ�
                                                   1�����жϡ� */
        unsigned int  reserved : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_ASP_HDMI_ASP_IMSR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_IMSR_p3adfims_START  (0)
#define SOC_ASP_HDMI_ASP_IMSR_p3adfims_END    (0)
#define SOC_ASP_HDMI_ASP_IMSR_p3bdfims_START  (1)
#define SOC_ASP_HDMI_ASP_IMSR_p3bdfims_END    (1)
#define SOC_ASP_HDMI_ASP_IMSR_aberims_START   (2)
#define SOC_ASP_HDMI_ASP_IMSR_aberims_END     (2)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_ASP_ICR_UNION
 �ṹ˵��  : ASP_ICR �Ĵ����ṹ���塣��ַƫ����:0x01C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ASP�ж�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p3adficr : 1;  /* bit[0]   : PCM3ͨ��A��DMA�����ж����㡣
                                                   0�������㣻
                                                   1�����㡣
                                                   ע�⣺�üĴ������д��1���������жϣ����д��0����Ч�� */
        unsigned int  p3bdficr : 1;  /* bit[1]   : PCM3ͨ��B��DMA�����ж����㡣
                                                   0�������㣻
                                                   1�����㡣
                                                   ע�⣺�üĴ������д��1���������жϣ����д��0����Ч�� */
        unsigned int  abericr  : 1;  /* bit[2]   : ASPģ������error��Ӧ�ж����㡣
                                                   0�������㣻
                                                   1�����㡣
                                                   ע�⣺�üĴ������д��1���������жϣ����д��0����Ч�� */
        unsigned int  reserved : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_ASP_HDMI_ASP_ICR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_ICR_p3adficr_START  (0)
#define SOC_ASP_HDMI_ASP_ICR_p3adficr_END    (0)
#define SOC_ASP_HDMI_ASP_ICR_p3bdficr_START  (1)
#define SOC_ASP_HDMI_ASP_ICR_p3bdficr_END    (1)
#define SOC_ASP_HDMI_ASP_ICR_abericr_START   (2)
#define SOC_ASP_HDMI_ASP_ICR_abericr_END     (2)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_ASP_PCMNSSR_UNION
 �ṹ˵��  : ASP_PCMNSSR �Ĵ����ṹ���塣��ַƫ����:0x020����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͨ���¸���ʼ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p3dsr    : 1;  /* bit[0]   : PCM3ͨ���¸���ʼ��
                                                   0����Ч��
                                                   1���¸���ʼ�� */
        unsigned int  reserved : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_ASP_HDMI_ASP_PCMNSSR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_PCMNSSR_p3dsr_START     (0)
#define SOC_ASP_HDMI_ASP_PCMNSSR_p3dsr_END       (0)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_ASP_P30CGR_UNION
 �ṹ˵��  : ASP_P30CGR �Ĵ����ṹ���塣��ַƫ����:0x028����ֵ:0x00000000�����:32
 �Ĵ���˵��: PCM3ͨ��0��������Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p30cgr   : 16; /* bit[0-15] : PCM3ͨ��0���������С���á� */
        unsigned int  reserved : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_ASP_HDMI_ASP_P30CGR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P30CGR_p30cgr_START    (0)
#define SOC_ASP_HDMI_ASP_P30CGR_p30cgr_END      (15)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_ASP_P31CGR_UNION
 �ṹ˵��  : ASP_P31CGR �Ĵ����ṹ���塣��ַƫ����:0x02C����ֵ:0x00000000�����:32
 �Ĵ���˵��: PCM3ͨ��1��������Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p31cgr   : 16; /* bit[0-15] : PCM3ͨ��1���������С���á� */
        unsigned int  reserved : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_ASP_HDMI_ASP_P31CGR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P31CGR_p31cgr_START    (0)
#define SOC_ASP_HDMI_ASP_P31CGR_p31cgr_END      (15)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_ASP_P32CGR_UNION
 �ṹ˵��  : ASP_P32CGR �Ĵ����ṹ���塣��ַƫ����:0x030����ֵ:0x00000000�����:32
 �Ĵ���˵��: PCM3ͨ��2��������Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p32cgr   : 16; /* bit[0-15] : PCM3ͨ��2���������С���á� */
        unsigned int  reserved : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_ASP_HDMI_ASP_P32CGR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P32CGR_p32cgr_START    (0)
#define SOC_ASP_HDMI_ASP_P32CGR_p32cgr_END      (15)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_ASP_P33CGR_UNION
 �ṹ˵��  : ASP_P33CGR �Ĵ����ṹ���塣��ַƫ����:0x034����ֵ:0x00000000�����:32
 �Ĵ���˵��: PCM3ͨ��3��������Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p33cgr   : 16; /* bit[0-15] : PCM3ͨ��3���������С���á� */
        unsigned int  reserved : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_ASP_HDMI_ASP_P33CGR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P33CGR_p33cgr_START    (0)
#define SOC_ASP_HDMI_ASP_P33CGR_p33cgr_END      (15)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_ASP_P34CGR_UNION
 �ṹ˵��  : ASP_P34CGR �Ĵ����ṹ���塣��ַƫ����:0x038����ֵ:0x00000000�����:32
 �Ĵ���˵��: PCM3ͨ��4��������Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p34cgr   : 16; /* bit[0-15] : PCM3ͨ��4���������С���á� */
        unsigned int  reserved : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_ASP_HDMI_ASP_P34CGR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P34CGR_p34cgr_START    (0)
#define SOC_ASP_HDMI_ASP_P34CGR_p34cgr_END      (15)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_ASP_P35CGR_UNION
 �ṹ˵��  : ASP_P35CGR �Ĵ����ṹ���塣��ַƫ����:0x03C����ֵ:0x00000000�����:32
 �Ĵ���˵��: PCM3ͨ��5��������Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p35cgr   : 16; /* bit[0-15] : PCM3ͨ��5���������С���á� */
        unsigned int  reserved : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_ASP_HDMI_ASP_P35CGR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P35CGR_p35cgr_START    (0)
#define SOC_ASP_HDMI_ASP_P35CGR_p35cgr_END      (15)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_ASP_P36CGR_UNION
 �ṹ˵��  : ASP_P36CGR �Ĵ����ṹ���塣��ַƫ����:0x040����ֵ:0x00000000�����:32
 �Ĵ���˵��: PCM3ͨ��6��������Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p36cgr   : 16; /* bit[0-15] : PCM3ͨ��6���������С���á� */
        unsigned int  reserved : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_ASP_HDMI_ASP_P36CGR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P36CGR_p36cgr_START    (0)
#define SOC_ASP_HDMI_ASP_P36CGR_p36cgr_END      (15)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_ASP_P37CGR_UNION
 �ṹ˵��  : ASP_P37CGR �Ĵ����ṹ���塣��ַƫ����:0x044����ֵ:0x00000000�����:32
 �Ĵ���˵��: PCM3ͨ��7��������Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p37cgr   : 16; /* bit[0-15] : PCM3ͨ��7���������С���á� */
        unsigned int  reserved : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_ASP_HDMI_ASP_P37CGR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P37CGR_p37cgr_START    (0)
#define SOC_ASP_HDMI_ASP_P37CGR_p37cgr_END      (15)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_ASP_P3ASAR_UNION
 �ṹ˵��  : ASP_P3ASAR �Ĵ����ṹ���塣��ַƫ����:0x048����ֵ:0x00000000�����:32
 �Ĵ���˵��: PCM3Aͨ��������ʼ��ַ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p3asar : 32; /* bit[0-31]: PCM3ͨ��A��DMA��ʼ��ַ��
                                                 ע�⣺bit[1:0]��������Ϊ2'b0���Ƽ�bit[3:0]����Ϊ4'h0�� */
    } reg;
} SOC_ASP_HDMI_ASP_P3ASAR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P3ASAR_p3asar_START  (0)
#define SOC_ASP_HDMI_ASP_P3ASAR_p3asar_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_ASP_P3ADLR_UNION
 �ṹ˵��  : ASP_P3ADLR �Ĵ����ṹ���塣��ַƫ����:0x04C����ֵ:0x00000000�����:32
 �Ĵ���˵��: PCM3Aͨ�����˳��ȼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p3adlr   : 20; /* bit[0-19] : PCM3ͨ��A��DMA���ȣ����ֽ�Ϊ��λ��
                                                    ע�⣺bit[4:0]��������Ϊ5'b0�� */
        unsigned int  reserved : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_ASP_HDMI_ASP_P3ADLR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P3ADLR_p3adlr_START    (0)
#define SOC_ASP_HDMI_ASP_P3ADLR_p3adlr_END      (19)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_ASP_P3BSAR_UNION
 �ṹ˵��  : ASP_P3BSAR �Ĵ����ṹ���塣��ַƫ����:0x050����ֵ:0x00000000�����:32
 �Ĵ���˵��: PCM3Bͨ��������ʼ��ַ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p3bsar : 32; /* bit[0-31]: PCM3ͨ��B��DMA��ʼ��ַ��
                                                 ע�⣺bit[1:0]��������Ϊ2'b0���Ƽ�bit[3:0]����Ϊ4'h0�� */
    } reg;
} SOC_ASP_HDMI_ASP_P3BSAR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P3BSAR_p3bsar_START  (0)
#define SOC_ASP_HDMI_ASP_P3BSAR_p3bsar_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_ASP_P3BDLR_UNION
 �ṹ˵��  : ASP_P3BDLR �Ĵ����ṹ���塣��ַƫ����:0x054����ֵ:0x00000000�����:32
 �Ĵ���˵��: PCM3Bͨ�����˳��ȼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p3bdlr   : 20; /* bit[0-19] : PCM3ͨ��B��DMA���ȣ����ֽ�Ϊ��λ��
                                                    ע�⣺bit[4:0]��������Ϊ5'b0�� */
        unsigned int  reserved : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_ASP_HDMI_ASP_P3BDLR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P3BDLR_p3bdlr_START    (0)
#define SOC_ASP_HDMI_ASP_P3BDLR_p3bdlr_END      (19)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_ASP_SPDIFSEL_UNION
 �ṹ˵��  : ASP_SPDIFSEL �Ĵ����ṹ���塣��ַƫ����:0x058����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������ݲ��Žӿ�ѡ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  spdifsel : 1;  /* bit[0]   : �������Žӿ�ѡ��
                                                   0��HDMI�ӿڣ�
                                                   1��SPDIF�ӿڡ� */
        unsigned int  reserved : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_ASP_HDMI_ASP_SPDIFSEL_UNION;
#endif
#define SOC_ASP_HDMI_ASP_SPDIFSEL_spdifsel_START  (0)
#define SOC_ASP_HDMI_ASP_SPDIFSEL_spdifsel_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_ASP_P3ADLS_UNION
 �ṹ˵��  : ASP_P3ADLS �Ĵ����ṹ���塣��ַƫ����:0x05C����ֵ:0x00000000�����:32
 �Ĵ���˵��: DMAֹͣʱPCM3Aͨ�����˳���״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p3adls   : 20; /* bit[0-19] : PCM3ͨ��A��DMAֹͣʹ��ʱ��ʣ��δ��ɰ��˵�DMA������Ϣ����λΪ�ֽڡ� */
        unsigned int  reserved : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_ASP_HDMI_ASP_P3ADLS_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P3ADLS_p3adls_START    (0)
#define SOC_ASP_HDMI_ASP_P3ADLS_p3adls_END      (19)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_ASP_P3BDLS_UNION
 �ṹ˵��  : ASP_P3BDLS �Ĵ����ṹ���塣��ַƫ����:0x060����ֵ:0x00000000�����:32
 �Ĵ���˵��: DMAֹͣʱPCM3Bͨ�����˳���״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p3bdls   : 20; /* bit[0-19] : PCM3ͨ��B��DMAֹͣʹ��ʱ��ʣ��δ��ɰ��˵�DMA������Ϣ����λΪ�ֽڡ� */
        unsigned int  reserved : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_ASP_HDMI_ASP_P3BDLS_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P3BDLS_p3bdls_START    (0)
#define SOC_ASP_HDMI_ASP_P3BDLS_p3bdls_END      (19)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_ASP_FDS_UNION
 �ṹ˵��  : ASP_FDS �Ĵ����ṹ���塣��ַƫ����:0x064����ֵ:0x00000000�����:32
 �Ĵ���˵��: DMA�������ݻ���FIFO״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pcm3_fds : 6;  /* bit[0-5] : PCM3ͨ��DMA�������ݻ���FIFO���״̬��Ϣ�� */
        unsigned int  reserved : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_ASP_HDMI_ASP_FDS_UNION;
#endif
#define SOC_ASP_HDMI_ASP_FDS_pcm3_fds_START  (0)
#define SOC_ASP_HDMI_ASP_FDS_pcm3_fds_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_ASP_P3ADL_UNION
 �ṹ˵��  : ASP_P3ADL �Ĵ����ṹ���塣��ַƫ����:0x068����ֵ:0x00000000�����:32
 �Ĵ���˵��: PCM3Aͨ��DMA����ʣ�೤��״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p3adl    : 20; /* bit[0-19] : PCM3ͨ��A��DMAʣ��δ���˵�DMA������Ϣ����λΪ�ֽڡ� */
        unsigned int  reserved : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_ASP_HDMI_ASP_P3ADL_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P3ADL_p3adl_START     (0)
#define SOC_ASP_HDMI_ASP_P3ADL_p3adl_END       (19)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_ASP_P3BDL_UNION
 �ṹ˵��  : ASP_P3BDL �Ĵ����ṹ���塣��ַƫ����:0x06C����ֵ:0x00000000�����:32
 �Ĵ���˵��: PCM3Bͨ��DMA����ʣ�೤��״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p3bdl    : 20; /* bit[0-19] : PCM3ͨ��B��DMAʣ��δ���˵�DMA������Ϣ����λΪ�ֽڡ� */
        unsigned int  reserved : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_ASP_HDMI_ASP_P3BDL_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P3BDL_p3bdl_START     (0)
#define SOC_ASP_HDMI_ASP_P3BDL_p3bdl_END       (19)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_ASP_SECURE_UNION
 �ṹ˵��  : ASP_SECURE �Ĵ����ṹ���塣��ַƫ����:0x070����ֵ:0x00000003�����:32
 �Ĵ���˵��: ASP_HDMIģ�鰲ȫ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asp_secure_en_n      : 1;  /* bit[0]   : asp���ڰ�ȫ״̬��ʹ�ܼĴ���������Ч��ֻ���ɰ�ȫ���������� */
        unsigned int  asp_addr_secure_en_n : 1;  /* bit[1]   : asp dma��ַ���ڰ�ȫ״̬��ʹ�ܼĴ���������Ч��ֻ���ɰ�ȫ���������� */
        unsigned int  reserved             : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_ASP_HDMI_ASP_SECURE_UNION;
#endif
#define SOC_ASP_HDMI_ASP_SECURE_asp_secure_en_n_START       (0)
#define SOC_ASP_HDMI_ASP_SECURE_asp_secure_en_n_END         (0)
#define SOC_ASP_HDMI_ASP_SECURE_asp_addr_secure_en_n_START  (1)
#define SOC_ASP_HDMI_ASP_SECURE_asp_addr_secure_en_n_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_RESERVED1_UNION
 �ṹ˵��  : RESERVED1 �Ĵ����ṹ���塣��ַƫ����:0x074����ֵ:0x00000000�����:32
 �Ĵ���˵��: MIXCTL�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 2;  /* bit[0-1] :  */
        unsigned int  reserved_1: 30; /* bit[2-31]:  */
    } reg;
} SOC_ASP_HDMI_RESERVED1_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_SIO1_ASPIF_SEL_UNION
 �ṹ˵��  : SIO1_ASPIF_SEL �Ĵ����ṹ���塣��ַƫ����:0x400����ֵ:0x00000001�����:32
 �Ĵ���˵��: SIO1��Ƶ�ӿ�ѡ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  access_ctrl : 1;  /* bit[0]   : SIO1����ģʽѡ��
                                                      0������ģʽ������ģʽ��CPU�ɶ�ȡ���ͺͽ���FIFO�е����ݣ�
                                                      1����������ģʽ��
                                                      ע�⣺����Ӧ��ʱ���üĴ�������д��1��������д��0���� */
        unsigned int  reserved    : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_ASP_HDMI_SIO1_ASPIF_SEL_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_ASPIF_SEL_access_ctrl_START  (0)
#define SOC_ASP_HDMI_SIO1_ASPIF_SEL_access_ctrl_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_SIO1_RAW_INT_UNION
 �ṹ˵��  : SIO1_RAW_INT �Ĵ����ṹ���塣��ַƫ����:0x408����ֵ:0x00000000�����:32
 �Ĵ���˵��: SIO1�ж�ԭʼ״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 1;  /* bit[0]   :  */
        unsigned int  tx_int   : 1;  /* bit[1]   : SIO1�����жϡ�
                                                   0�����жϣ�
                                                   1�����жϡ�
                                                   ע�⣺����FIFO��ʣ�����ݵ���ˮ��ʱ�����жϣ�SIO1_INT_CLR�Ĵ�����Ӧλд1ʱ�ж����㡣 */
        unsigned int  reserved_1: 30; /* bit[2-31]: ������ */
    } reg;
} SOC_ASP_HDMI_SIO1_RAW_INT_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_RAW_INT_tx_int_START    (1)
#define SOC_ASP_HDMI_SIO1_RAW_INT_tx_int_END      (1)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_SIO1_INT_CLR_UNION
 �ṹ˵��  : SIO1_INT_CLR �Ĵ����ṹ���塣��ַƫ����:0x40C����ֵ:0x00000000�����:32
 �Ĵ���˵��: SIO1�ж�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0 : 1;  /* bit[0]   :  */
        unsigned int  tx_int_clr : 1;  /* bit[1]   : SIO1�����ж����㡣
                                                     0����Ч��
                                                     1������tx_int��
                                                     ע�⣺�üĴ������д��1���������жϣ����д��0����Ч�� */
        unsigned int  reserved_1 : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_ASP_HDMI_SIO1_INT_CLR_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_INT_CLR_tx_int_clr_START  (1)
#define SOC_ASP_HDMI_SIO1_INT_CLR_tx_int_clr_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_SIO1_INT_ENABLE_UNION
 �ṹ˵��  : SIO1_INT_ENABLE �Ĵ����ṹ���塣��ַƫ����:0x410����ֵ:0x00000000�����:32
 �Ĵ���˵��: SIO1�ж�ʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0    : 1;  /* bit[0]   :  */
        unsigned int  tx_int_enable : 1;  /* bit[1]   : �����ж�ʹ�ܡ�
                                                        0����ʹ�ܣ�
                                                        1��ʹ�ܡ� */
        unsigned int  reserved_1    : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_ASP_HDMI_SIO1_INT_ENABLE_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_INT_ENABLE_tx_int_enable_START  (1)
#define SOC_ASP_HDMI_SIO1_INT_ENABLE_tx_int_enable_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_SIO1_INT_MASKED_STATUS_UNION
 �ṹ˵��  : SIO1_INT_MASKED_STATUS �Ĵ����ṹ���塣��ַƫ����:0x414����ֵ:0x00000000�����:32
 �Ĵ���˵��: SIO1�ж����κ�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0  : 1;  /* bit[0]   :  */
        unsigned int  tx_int_mask : 1;  /* bit[1]   : �ж����κ�ķ���ͨ���жϡ�
                                                      0�����жϣ�
                                                      1�����жϡ�
                                                      ע�⣺SIO1_INT_CLR�Ĵ�����Ӧλд1ʱ�ж����㡣 */
        unsigned int  reserved_1  : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_ASP_HDMI_SIO1_INT_MASKED_STATUS_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_INT_MASKED_STATUS_tx_int_mask_START  (1)
#define SOC_ASP_HDMI_SIO1_INT_MASKED_STATUS_tx_int_mask_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_SIO1_I2S_SET_UNION
 �ṹ˵��  : SIO1_I2S_SET �Ĵ����ṹ���塣��ַƫ����:0x41C����ֵ:0x0008000C�����:32
 �Ĵ���˵��: SIO1 I2Sģʽ����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0        : 2;  /* bit[0-1]  :  */
        unsigned int  tx_ws_sel         : 1;  /* bit[2]    : ����ͬ���ź�ѡ��
                                                             1��ѡ���ⲿͬ����
                                                             0���ޱ仯��
                                                             ע�⣺1��ֻ֧���ⲿʱ�ӣ���λֻ��д��1������ֹд��0����2������ǰ������ʹ��SIO1_I2S_CLR�Ĵ����Ķ�Ӧ�������������������ᵼ������ʧ�ܡ� */
        unsigned int  tx_clk_sel        : 1;  /* bit[3]    : ����ʱ��ѡ��
                                                             1��ѡ���ⲿʱ�ӣ�
                                                             0���ޱ仯��
                                                             ע�⣺1��ֻ֧���ⲿʱ�ӣ���λֻ��д��1������ֹд��0����2������ǰ������ʹ��SIO1_I2S_CLR�Ĵ����Ķ�Ӧ�������������������ᵼ������ʧ�ܡ� */
        unsigned int  tx_fifo_threshold : 5;  /* bit[4-8]  : ����FIFO��ֵ��ʵ��ֵ��������ֵ��1��
                                                             ע�⣺����ǰ������ʹ��SIO1_I2S_CLR�Ĵ����Ķ�Ӧ�������������������ᵼ������ʧ�ܡ� */
        unsigned int  reserved_1        : 5;  /* bit[9-13] :  */
        unsigned int  tx_fifo_disable   : 1;  /* bit[14]   : ����FIFO Disable����ֹFIFOʱ����ʹ��FIFO���淢�����ݣ�FIFO����·��
                                                             0������ֹ��
                                                             1����ֹ��
                                                             ע�⣺1������Ӧ��ʱ����λ�Ƽ�����Ϊ��0����2������ǰ������ʹ��SIO1_I2S_CLR�Ĵ����Ķ�Ӧ�������������������ᵼ������ʧ�ܡ� */
        unsigned int  reserved_2        : 1;  /* bit[15]   :  */
        unsigned int  tx_enable         : 1;  /* bit[16]   : ����ͨ��ʹ�ܡ�
                                                             0����ʹ�ܣ�
                                                             1��ʹ�ܡ�
                                                             ע�⣺����ǰ������ʹ��SIO1_I2S_CLR�Ĵ����Ķ�Ӧ�������������������ᵼ������ʧ�ܡ� */
        unsigned int  reserved_3        : 1;  /* bit[17]   :  */
        unsigned int  dsp_mode          : 1;  /* bit[18]   : ��λֻ��д��0������ֹд��1����
                                                             ע�⣺����ǰ������ʹ��SIO1_I2S_CLR�Ĵ����Ķ�Ӧ�������������������ᵼ������ʧ�ܡ� */
        unsigned int  tx_rx_reset_n     : 1;  /* bit[19]   : ��λֻ��д��1������ֹд��0����
                                                             ע�⣺����ǰ������ʹ��SIO1_I2S_CLR�Ĵ����Ķ�Ӧ�������������������ᵼ������ʧ�ܡ� */
        unsigned int  reserved_4        : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_ASP_HDMI_SIO1_I2S_SET_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_ws_sel_START          (2)
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_ws_sel_END            (2)
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_clk_sel_START         (3)
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_clk_sel_END           (3)
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_fifo_threshold_START  (4)
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_fifo_threshold_END    (8)
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_fifo_disable_START    (14)
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_fifo_disable_END      (14)
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_enable_START          (16)
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_enable_END            (16)
#define SOC_ASP_HDMI_SIO1_I2S_SET_dsp_mode_START           (18)
#define SOC_ASP_HDMI_SIO1_I2S_SET_dsp_mode_END             (18)
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_rx_reset_n_START      (19)
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_rx_reset_n_END        (19)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_SIO1_I2S_CLR_UNION
 �ṹ˵��  : SIO1_I2S_CLR �Ĵ����ṹ���塣��ַƫ����:0x420����ֵ:0x0008000C�����:32
 �Ĵ���˵��: SIO1 I2Sģʽ�������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0            : 2;  /* bit[0-1]  :  */
        unsigned int  tx_ws_sel_clr         : 1;  /* bit[2]    : ��λֻ��д��0������ֹд��1����
                                                                 ע�⣺�üĴ������д��1������ʵ�����㣬���д��0����Ч�� */
        unsigned int  tx_clk_sel_clr        : 1;  /* bit[3]    : ��λֻ��д��0������ֹд��1����
                                                                 ע�⣺�üĴ������д��1������ʵ�����㣬���д��0����Ч�� */
        unsigned int  tx_fifo_threshold_clr : 5;  /* bit[4-8]  : ����FIFO��ֵ�����ÿһ���������FIFO��ֵ��ÿһ����һһ��Ӧ��
                                                                 0��������Ч��
                                                                 1������tx_fifo_disable��
                                                                 ע�⣺�üĴ������д��1������ʵ�����㣬���д��0����Ч�� */
        unsigned int  reserved_1            : 5;  /* bit[9-13] :  */
        unsigned int  tx_fifo_disable_clr   : 1;  /* bit[14]   : ����FIFO Disable�����
                                                                 0��������Ч��
                                                                 1������tx_fifo_disable��
                                                                 ע�⣺�üĴ������д��1������ʵ�����㣬���д��0����Ч�� */
        unsigned int  reserved_2            : 1;  /* bit[15]   :  */
        unsigned int  tx_enable_clr         : 1;  /* bit[16]   : ����ͨ��ʹ�����㡣
                                                                 0��������Ч��
                                                                 1������tx_enable��
                                                                 ע�⣺�üĴ������д��1������ʵ�����㣬���д��0����Ч�� */
        unsigned int  reserved_3            : 1;  /* bit[17]   :  */
        unsigned int  dsp_mode_clr          : 1;  /* bit[18]   : ��λֻ��д��0������ֹд��1����
                                                                 ע�⣺�üĴ������д��1������ʵ�����㣬���д��0����Ч�� */
        unsigned int  tx_rx_reset_n_clr     : 1;  /* bit[19]   : ��λֻ��д��0������ֹд��1����
                                                                 ע�⣺�üĴ������д��1������ʵ�����㣬���д��0����Ч�� */
        unsigned int  reserved_4            : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_ASP_HDMI_SIO1_I2S_CLR_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_ws_sel_clr_START          (2)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_ws_sel_clr_END            (2)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_clk_sel_clr_START         (3)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_clk_sel_clr_END           (3)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_fifo_threshold_clr_START  (4)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_fifo_threshold_clr_END    (8)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_fifo_disable_clr_START    (14)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_fifo_disable_clr_END      (14)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_enable_clr_START          (16)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_enable_clr_END            (16)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_dsp_mode_clr_START           (18)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_dsp_mode_clr_END             (18)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_rx_reset_n_clr_START      (19)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_rx_reset_n_clr_END        (19)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_SIO1_TX_STA_UNION
 �ṹ˵��  : SIO1_TX_STA �Ĵ����ṹ���塣��ַƫ����:0x42C����ֵ:0x00000000�����:32
 �Ĵ���˵��: SIO1 ����ͨ��״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tx_rfifo_over  : 1;  /* bit[0]    : ����������FIFO������澯��
                                                          0���޸澯��
                                                          1���и澯��
                                                          ע�⣺�ñ���Ϊ��ʷ�澯�����塣 */
        unsigned int  tx_lfifo_over  : 1;  /* bit[1]    : ����������FIFO������澯��
                                                          0���޸澯��
                                                          1���и澯��
                                                          ע�⣺�ñ���Ϊ��ʷ�澯�����塣 */
        unsigned int  tx_rfifo_depth : 6;  /* bit[2-7]  : ����������FIFOʣ�����ݸ����� */
        unsigned int  tx_lfifo_depth : 6;  /* bit[8-13] : ����������FIFOʣ�����ݸ����� */
        unsigned int  reserved       : 18; /* bit[14-31]: ������ */
    } reg;
} SOC_ASP_HDMI_SIO1_TX_STA_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_TX_STA_tx_rfifo_over_START   (0)
#define SOC_ASP_HDMI_SIO1_TX_STA_tx_rfifo_over_END     (0)
#define SOC_ASP_HDMI_SIO1_TX_STA_tx_lfifo_over_START   (1)
#define SOC_ASP_HDMI_SIO1_TX_STA_tx_lfifo_over_END     (1)
#define SOC_ASP_HDMI_SIO1_TX_STA_tx_rfifo_depth_START  (2)
#define SOC_ASP_HDMI_SIO1_TX_STA_tx_rfifo_depth_END    (7)
#define SOC_ASP_HDMI_SIO1_TX_STA_tx_lfifo_depth_START  (8)
#define SOC_ASP_HDMI_SIO1_TX_STA_tx_lfifo_depth_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_SIO1_CLR_UNION
 �ṹ˵��  : SIO1_CLR �Ĵ����ṹ���塣��ַƫ����:0x438����ֵ:0x00000000�����:32
 �Ĵ���˵��: SIO1��fifo����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tx_clr   : 1;  /* bit[0]   : TXͨ��fifo����Ĵ�����
                                                   0����Ч��
                                                   1������ͨ��fifo���㡣
                                                   ע�⣺�üĴ������д��1����Ӳ�����㣬���д��0����Ч�� */
        unsigned int  reserved_0: 1;  /* bit[1]   :  */
        unsigned int  reserved_1: 30; /* bit[2-31]: ������ */
    } reg;
} SOC_ASP_HDMI_SIO1_CLR_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_CLR_tx_clr_START    (0)
#define SOC_ASP_HDMI_SIO1_CLR_tx_clr_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_SIO1_TST_TX0_DATA_UNION
 �ṹ˵��  : SIO1_TST_TX0_DATA �Ĵ����ṹ���塣��ַƫ����:0x440����ֵ:0x00000000�����:32
 �Ĵ���˵��: SIO1����0������������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sio1_tst_tx0_data : 24; /* bit[0-23] : SIO1����0�����������ݣ�����SIO1�ӿڵ��ԡ� */
        unsigned int  reserved          : 8;  /* bit[24-31]: ������ */
    } reg;
} SOC_ASP_HDMI_SIO1_TST_TX0_DATA_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_TST_TX0_DATA_sio1_tst_tx0_data_START  (0)
#define SOC_ASP_HDMI_SIO1_TST_TX0_DATA_sio1_tst_tx0_data_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_SIO1_TST_TX1_DATA_UNION
 �ṹ˵��  : SIO1_TST_TX1_DATA �Ĵ����ṹ���塣��ַƫ����:0x444����ֵ:0x00000000�����:32
 �Ĵ���˵��: SIO1����1������������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sio1_tst_tx1_data : 24; /* bit[0-23] : SIO1����1�����������ݣ�����SIO1�ӿڵ��ԡ� */
        unsigned int  reserved          : 8;  /* bit[24-31]: ������ */
    } reg;
} SOC_ASP_HDMI_SIO1_TST_TX1_DATA_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_TST_TX1_DATA_sio1_tst_tx1_data_START  (0)
#define SOC_ASP_HDMI_SIO1_TST_TX1_DATA_sio1_tst_tx1_data_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_SIO1_TST_TX2_DATA_UNION
 �ṹ˵��  : SIO1_TST_TX2_DATA �Ĵ����ṹ���塣��ַƫ����:0x448����ֵ:0x00000000�����:32
 �Ĵ���˵��: SIO1����2������������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sio1_tst_tx2_data : 24; /* bit[0-23] : SIO1����2�����������ݣ�����SIO1�ӿڵ��ԡ� */
        unsigned int  reserved          : 8;  /* bit[24-31]: ������ */
    } reg;
} SOC_ASP_HDMI_SIO1_TST_TX2_DATA_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_TST_TX2_DATA_sio1_tst_tx2_data_START  (0)
#define SOC_ASP_HDMI_SIO1_TST_TX2_DATA_sio1_tst_tx2_data_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_SIO1_TST_TX3_DATA_UNION
 �ṹ˵��  : SIO1_TST_TX3_DATA �Ĵ����ṹ���塣��ַƫ����:0x44C����ֵ:0x00000000�����:32
 �Ĵ���˵��: SIO1����3������������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sio1_tst_tx3_data : 24; /* bit[0-23] : SIO1����3�����������ݣ�����SIO1�ӿڵ��ԡ� */
        unsigned int  reserved          : 8;  /* bit[24-31]: ������ */
    } reg;
} SOC_ASP_HDMI_SIO1_TST_TX3_DATA_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_TST_TX3_DATA_sio1_tst_tx3_data_START  (0)
#define SOC_ASP_HDMI_SIO1_TST_TX3_DATA_sio1_tst_tx3_data_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_SIO1_TST_TX4_DATA_UNION
 �ṹ˵��  : SIO1_TST_TX4_DATA �Ĵ����ṹ���塣��ַƫ����:0x450����ֵ:0x00000000�����:32
 �Ĵ���˵��: SIO1����4������������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sio1_tst_tx4_data : 24; /* bit[0-23] : SIO1����4�����������ݣ�����SIO1�ӿڵ��ԡ� */
        unsigned int  reserved          : 8;  /* bit[24-31]: ������ */
    } reg;
} SOC_ASP_HDMI_SIO1_TST_TX4_DATA_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_TST_TX4_DATA_sio1_tst_tx4_data_START  (0)
#define SOC_ASP_HDMI_SIO1_TST_TX4_DATA_sio1_tst_tx4_data_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_SIO1_TST_TX5_DATA_UNION
 �ṹ˵��  : SIO1_TST_TX5_DATA �Ĵ����ṹ���塣��ַƫ����:0x454����ֵ:0x00000000�����:32
 �Ĵ���˵��: SIO1����5������������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sio1_tst_tx5_data : 24; /* bit[0-23] : SIO1����5�����������ݣ�����SIO1�ӿڵ��ԡ� */
        unsigned int  reserved          : 8;  /* bit[24-31]: ������ */
    } reg;
} SOC_ASP_HDMI_SIO1_TST_TX5_DATA_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_TST_TX5_DATA_sio1_tst_tx5_data_START  (0)
#define SOC_ASP_HDMI_SIO1_TST_TX5_DATA_sio1_tst_tx5_data_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_SIO1_TST_TX6_DATA_UNION
 �ṹ˵��  : SIO1_TST_TX6_DATA �Ĵ����ṹ���塣��ַƫ����:0x458����ֵ:0x00000000�����:32
 �Ĵ���˵��: SIO1����6������������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sio1_tst_tx6_data : 24; /* bit[0-23] : SIO1����6�����������ݣ�����SIO1�ӿڵ��ԡ� */
        unsigned int  reserved          : 8;  /* bit[24-31]: ������ */
    } reg;
} SOC_ASP_HDMI_SIO1_TST_TX6_DATA_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_TST_TX6_DATA_sio1_tst_tx6_data_START  (0)
#define SOC_ASP_HDMI_SIO1_TST_TX6_DATA_sio1_tst_tx6_data_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_SIO1_TST_TX7_DATA_UNION
 �ṹ˵��  : SIO1_TST_TX7_DATA �Ĵ����ṹ���塣��ַƫ����:0x45C����ֵ:0x00000000�����:32
 �Ĵ���˵��: SIO1����7������������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sio1_tst_tx7_data : 24; /* bit[0-23] : SIO1����7�����������ݣ�����SIO1�ӿڵ��ԡ� */
        unsigned int  reserved          : 8;  /* bit[24-31]: ������ */
    } reg;
} SOC_ASP_HDMI_SIO1_TST_TX7_DATA_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_TST_TX7_DATA_sio1_tst_tx7_data_START  (0)
#define SOC_ASP_HDMI_SIO1_TST_TX7_DATA_sio1_tst_tx7_data_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_SPDIF_CTRL_UNION
 �ṹ˵��  : SPDIF_CTRL �Ĵ����ṹ���塣��ַƫ����:0x800����ֵ:0x00000000�����:32
 �Ĵ���˵��: SPDIF���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  spdif_en     : 1;  /* bit[0]   : SPDIFʹ�ܡ�
                                                       0����ʹ�ܣ�
                                                       1��ʹ�ܡ�
                                                       ע�⣺��ʹ��ʱ�����FIFO����λ������ */
        unsigned int  afifo_wlevel : 3;  /* bit[1-3] : FIFO�����ޡ�
                                                       000������ֵΪ4��
                                                       001������ֵΪ8��
                                                       010������ֵΪ16��
                                                       011������ֵΪ24��
                                                       100������ֵΪ28��
                                                       ������������
                                                       ע�⣺FIFO�п�λ�������ڿ�����ʱ��������FIFO��д�����ݣ�����ֹͣд�����ݡ� */
        unsigned int  intr_en      : 1;  /* bit[4]   : �ж����ʹ�ܡ�
                                                       0����ʹ�ܣ�
                                                       1��ʹ�ܡ�
                                                       ע�⣺����Ӧ��ʱ�����ж��Ƽ�����Ϊ��ʹ�ܡ� */
        unsigned int  dma_en       : 1;  /* bit[5]   : DMA�������ʹ���źš�
                                                       0����ʹ�ܣ�
                                                       1��ʹ�ܡ�
                                                       ע�⣺�üĴ���������ֻ������Ϊ��0���� */
        unsigned int  reserved     : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_ASP_HDMI_SPDIF_CTRL_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_CTRL_spdif_en_START      (0)
#define SOC_ASP_HDMI_SPDIF_CTRL_spdif_en_END        (0)
#define SOC_ASP_HDMI_SPDIF_CTRL_afifo_wlevel_START  (1)
#define SOC_ASP_HDMI_SPDIF_CTRL_afifo_wlevel_END    (3)
#define SOC_ASP_HDMI_SPDIF_CTRL_intr_en_START       (4)
#define SOC_ASP_HDMI_SPDIF_CTRL_intr_en_END         (4)
#define SOC_ASP_HDMI_SPDIF_CTRL_dma_en_START        (5)
#define SOC_ASP_HDMI_SPDIF_CTRL_dma_en_END          (5)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_SPDIF_CONFIG_UNION
 �ṹ˵��  : SPDIF_CONFIG �Ĵ����ṹ���塣��ַƫ����:0x804����ֵ:0x00000000�����:32
 �Ĵ���˵��: SPDIF���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  validity_info : 1;  /* bit[0]   : ��Ƶ���ݿɿ���λ��
                                                        0����Ƶ���ݿɿ����������Ƶ�����Ѿ��ȶ�����
                                                        1����Ƶ���ݲ��ɿ����������Ƶ������δ�ȶ�������Ƶ���ݲ�������PCM�롣 */
        unsigned int  reserved      : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_ASP_HDMI_SPDIF_CONFIG_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_CONFIG_validity_info_START  (0)
#define SOC_ASP_HDMI_SPDIF_CONFIG_validity_info_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_SPDIF_INTRUPT_UNION
 �ṹ˵��  : SPDIF_INTRUPT �Ĵ����ṹ���塣��ַƫ����:0x808����ֵ:0x00000001�����:32
 �Ĵ���˵��: SPDIF���κ��ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afifo_empty_intr  : 1;  /* bit[0]   : FIFO�ɲ��ձ�Ϊ��ʱ�������жϡ�
                                                            0�����жϣ�
                                                            1�����жϡ�
                                                            ע�⣺д1���жϣ�д0��Ч��֧�ֵ����ز����� */
        unsigned int  afifo_single_intr : 1;  /* bit[1]   : FIFO������Ϊ�п�λʱ�������жϡ�
                                                            0�����жϣ�
                                                            1�����жϡ�
                                                            ע�⣺д1���жϣ�д0��Ч��֧�ֵ����ز�����SPDIFʹ��ʱ���ܲ����жϡ� */
        unsigned int  dma_burstintr     : 1;  /* bit[2]   : FIFO��λ�����ɲ�����FIFO�����ޱ�Ϊ����FIFO������ʱ�������жϡ�
                                                            0�����жϣ�
                                                            1�����жϡ�
                                                            ע�⣺д1���жϣ�д0��Ч��֧�ֵ����ز�����SPDIFʹ��ʱ���ܲ����жϡ� */
        unsigned int  reserved          : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_ASP_HDMI_SPDIF_INTRUPT_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_INTRUPT_afifo_empty_intr_START   (0)
#define SOC_ASP_HDMI_SPDIF_INTRUPT_afifo_empty_intr_END     (0)
#define SOC_ASP_HDMI_SPDIF_INTRUPT_afifo_single_intr_START  (1)
#define SOC_ASP_HDMI_SPDIF_INTRUPT_afifo_single_intr_END    (1)
#define SOC_ASP_HDMI_SPDIF_INTRUPT_dma_burstintr_START      (2)
#define SOC_ASP_HDMI_SPDIF_INTRUPT_dma_burstintr_END        (2)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_SPDIF_INTR_MASK_UNION
 �ṹ˵��  : SPDIF_INTR_MASK �Ĵ����ṹ���塣��ַƫ����:0x80C����ֵ:0x00000000�����:32
 �Ĵ���˵��: SPDIF�ж����μĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afifo_empty_intr_mask  : 1;  /* bit[0]   : afifo_empty_intr�ж����Ρ�
                                                                 0�������Σ�
                                                                 1�����Ρ� */
        unsigned int  afifo_single_intr_mask : 1;  /* bit[1]   : afifo_single_intr�ж����Ρ�
                                                                 0�������Σ�
                                                                 1�����Ρ� */
        unsigned int  dma_burstintr_mask     : 1;  /* bit[2]   : dma_burstintr�ж����Ρ�
                                                                 0�������Σ�
                                                                 1�����Ρ� */
        unsigned int  reserved               : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_ASP_HDMI_SPDIF_INTR_MASK_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_INTR_MASK_afifo_empty_intr_mask_START   (0)
#define SOC_ASP_HDMI_SPDIF_INTR_MASK_afifo_empty_intr_mask_END     (0)
#define SOC_ASP_HDMI_SPDIF_INTR_MASK_afifo_single_intr_mask_START  (1)
#define SOC_ASP_HDMI_SPDIF_INTR_MASK_afifo_single_intr_mask_END    (1)
#define SOC_ASP_HDMI_SPDIF_INTR_MASK_dma_burstintr_mask_START      (2)
#define SOC_ASP_HDMI_SPDIF_INTR_MASK_dma_burstintr_mask_END        (2)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_SPDIF_FIFO_STATE_UNION
 �ṹ˵��  : SPDIF_FIFO_STATE �Ĵ����ṹ���塣��ַƫ����:0x810����ֵ:0x00000001�����:32
 �Ĵ���˵��: SPDIF FIFO״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afifo_empty_intr_state  : 1;  /* bit[0]   : FIFO��״̬��
                                                                  0��FIFO���գ�
                                                                  1��FIFO�ա� */
        unsigned int  afifo_single_intr_state : 1;  /* bit[1]   : FIFO�п�λ������дFIFO��
                                                                  0��FIFO����������дFIFO��
                                                                  1��FIFO�п�λ������дFIFO��
                                                                  ע�⣺SPDIFʹ��ʱ��������дFIFO�� */
        unsigned int  dma_burstintr_state     : 1;  /* bit[2]   : FIFO��λ����FIFO�����ޣ�����дFIFO��
                                                                  0��FIFO��λ������FIFO���ޣ�������дFIFO��
                                                                  1��FIFO��λ����FIFO���ޣ�����дFIFO��
                                                                  ע�⣺SPDIFʹ��ʱ��������дFIFO�� */
        unsigned int  afifo_depth             : 5;  /* bit[3-7] : FIFO���״̬��Ϣ�� */
        unsigned int  reserved                : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_ASP_HDMI_SPDIF_FIFO_STATE_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_FIFO_STATE_afifo_empty_intr_state_START   (0)
#define SOC_ASP_HDMI_SPDIF_FIFO_STATE_afifo_empty_intr_state_END     (0)
#define SOC_ASP_HDMI_SPDIF_FIFO_STATE_afifo_single_intr_state_START  (1)
#define SOC_ASP_HDMI_SPDIF_FIFO_STATE_afifo_single_intr_state_END    (1)
#define SOC_ASP_HDMI_SPDIF_FIFO_STATE_dma_burstintr_state_START      (2)
#define SOC_ASP_HDMI_SPDIF_FIFO_STATE_dma_burstintr_state_END        (2)
#define SOC_ASP_HDMI_SPDIF_FIFO_STATE_afifo_depth_START              (3)
#define SOC_ASP_HDMI_SPDIF_FIFO_STATE_afifo_depth_END                (7)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_SPDIF_CH_STATUS1_UNION
 �ṹ˵��  : SPDIF_CH_STATUS1 �Ĵ����ṹ���塣��ַƫ����:0x820����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ŵ�״̬��Ϣ�Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_status1_0  : 1;  /* bit[0]    : ������Ӧ�����
                                                         0��������Ӧ�ã�
                                                         1��רҵӦ�á� */
        unsigned int  ch_status1_1  : 1;  /* bit[1]    : ��������Ƶ���������
                                                         0������PCM������
                                                         1�������� */
        unsigned int  ch_status1_2  : 1;  /* bit[2]    : �����������Ƿ���ڰ�Ȩ������
                                                         0�����ڣ�
                                                         1�������ڡ� */
        unsigned int  ch_status1_5  : 3;  /* bit[3-5]  : ���������͵���Ƶ�����Ƿ񾭹�Ԥ���ء�
                                                         000����Ԥ���أ�
                                                         100��Ԥ����Ϊ50��s/15��s��
                                                         ������������ */
        unsigned int  ch_status1_7  : 2;  /* bit[6-7]  : �������ŵ�״̬��Ϣλ��
                                                         00���ŵ�״̬��������Ӧ�������ݸ�ʽ���á�
                                                         ������������ */
        unsigned int  ch_status1_8  : 1;  /* bit[8]    : ������Ӧ�����
                                                         0��������Ӧ�ã�
                                                         1��רҵӦ�á� */
        unsigned int  ch_status1_9  : 1;  /* bit[9]    : ��������Ƶ���������
                                                         0������PCM������
                                                         1�������� */
        unsigned int  ch_status1_10 : 1;  /* bit[10]   : �����������Ƿ���ڰ�Ȩ������
                                                         0�����ڣ�
                                                         1�������ڡ� */
        unsigned int  ch_status1_13 : 3;  /* bit[11-13]: ���������͵���Ƶ�����Ƿ񾭹�Ԥ���ء�
                                                         000����Ԥ���أ�
                                                         100��Ԥ����Ϊ50��s/15��s��
                                                         ������������ */
        unsigned int  ch_status1    : 2;  /* bit[14-15]: �������ŵ�״̬��Ϣλ��
                                                         00���ŵ�״̬��������Ӧ�������ݸ�ʽ���á�
                                                         ������������ */
        unsigned int  reserved      : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_ASP_HDMI_SPDIF_CH_STATUS1_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_0_START   (0)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_0_END     (0)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_1_START   (1)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_1_END     (1)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_2_START   (2)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_2_END     (2)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_5_START   (3)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_5_END     (5)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_7_START   (6)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_7_END     (7)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_8_START   (8)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_8_END     (8)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_9_START   (9)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_9_END     (9)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_10_START  (10)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_10_END    (10)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_13_START  (11)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_13_END    (13)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_START     (14)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_END       (15)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_SPDIF_CH_STATUS2_UNION
 �ṹ˵��  : SPDIF_CH_STATUS2 �Ĵ����ṹ���塣��ַƫ����:0x824����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ŵ�״̬��Ϣ�Ĵ���2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_status2_7  : 8;  /* bit[0-7]  : ������ѡ�������Ƶ�ӿ��źŵ��豸��
                                                         0x02������������Ƶ�ӿ��źŵ��豸ΪPCM encoder/decoder��
                                                         0x19������������Ƶ�ӿ��źŵ��豸ΪDVD�豸��
                                                         ���кܶ�����Ӧ�ã�������Ϣ��ο�IEC 60958Э�顣 */
        unsigned int  ch_status2_15 : 8;  /* bit[8-15] : ������ѡ�������Ƶ�ӿ��źŵ��豸��
                                                         0x02������������Ƶ�ӿ��źŵ��豸ΪPCM encoder/decoder��
                                                         0x19������������Ƶ�ӿ��źŵ��豸ΪDVD��Digital Versatile Disc���豸��
                                                         ���кܶ�����Ӧ�ã�������Ϣ��ο�IEC 60958Э�顣 */
        unsigned int  reserved      : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_ASP_HDMI_SPDIF_CH_STATUS2_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_CH_STATUS2_ch_status2_7_START   (0)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS2_ch_status2_7_END     (7)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS2_ch_status2_15_START  (8)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS2_ch_status2_15_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_SPDIF_CH_STATUS3_UNION
 �ṹ˵��  : SPDIF_CH_STATUS3 �Ĵ����ṹ���塣��ַƫ����:0x828����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ŵ�״̬��Ϣ�Ĵ���3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_status3_3  : 4;  /* bit[0-3]  : ���������á�
                                                         0x0��Դ����
                                                         ����Ƶ�ӿڹ̶������������ã�ʹ�����������ο�IEC 60958Э�顣 */
        unsigned int  ch_status3_7  : 4;  /* bit[4-7]  : ���������͡�
                                                         0x1����������ʽ����������
                                                         ����Ƶ�ӿڹ̶������������ã�ʹ�����������ο�IEC 60958Э�顣 */
        unsigned int  ch_status3_11 : 4;  /* bit[8-11] : ���������á�
                                                         0x0��Դ����
                                                         ����Ƶ�ӿڹ̶������������ã�ʹ�����������ο�IEC 60958Э�顣 */
        unsigned int  ch_status3_15 : 4;  /* bit[12-15]: ���������͡�
                                                         0x2����������ʽ����������
                                                         ����Ƶ�ӿڹ̶������������ã�ʹ�����������ο�IEC 60958Э�飬���޸���������� */
        unsigned int  reserved      : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_ASP_HDMI_SPDIF_CH_STATUS3_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_CH_STATUS3_ch_status3_3_START   (0)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS3_ch_status3_3_END     (3)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS3_ch_status3_7_START   (4)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS3_ch_status3_7_END     (7)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS3_ch_status3_11_START  (8)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS3_ch_status3_11_END    (11)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS3_ch_status3_15_START  (12)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS3_ch_status3_15_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_SPDIF_CH_STATUS4_UNION
 �ṹ˵��  : SPDIF_CH_STATUS4 �Ĵ����ṹ���塣��ַƫ����:0x82C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ŵ�״̬��Ϣ�Ĵ���4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_status4_3  : 4;  /* bit[0-3]  : ����������Ƶ�ʡ�
                                                         0x0��44.1kHz��
                                                         0x2��48kHz��
                                                         0x3��32kHz��
                                                         0xA��96kHz��
                                                         ������������ο�IEC 60958Э�顣 */
        unsigned int  ch_status4_5  : 2;  /* bit[4-5]  : ������ʱ�Ӿ��ȡ�
                                                         00��������
                                                         01��������
                                                         10��һ����
                                                         11���ӿ�֡���ʺͲ����ʲ�ƥ�䡣 */
        unsigned int  ch_status4_7  : 2;  /* bit[6-7]  : ������Э��ı���λ���̶���Ϊ00�� */
        unsigned int  ch_status4_11 : 4;  /* bit[8-11] : ����������Ƶ�ʡ�
                                                         0x0��44.1kHz��
                                                         0x2��48kHz��
                                                         0x3��32kHz��
                                                         0xA��96kHz��
                                                         ������������ο�IEC 60958Э�顣 */
        unsigned int  ch_status4_13 : 2;  /* bit[12-13]: ������ʱ�Ӿ��ȡ�
                                                         00��������
                                                         01��������
                                                         10��һ����
                                                         11���ӿ�֡���ʺͲ����ʲ�ƥ�䡣 */
        unsigned int  ch_status4_15 : 2;  /* bit[14-15]: ������Э��ı���λ���̶�Ϊ00�� */
        unsigned int  reserved      : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_ASP_HDMI_SPDIF_CH_STATUS4_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_3_START   (0)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_3_END     (3)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_5_START   (4)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_5_END     (5)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_7_START   (6)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_7_END     (7)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_11_START  (8)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_11_END    (11)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_13_START  (12)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_13_END    (13)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_15_START  (14)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_15_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_SPDIF_CH_STATUS5_UNION
 �ṹ˵��  : SPDIF_CH_STATUS5 �Ĵ����ṹ���塣��ַƫ����:0x830����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ŵ�״̬��Ϣ�Ĵ���5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_status5_0  : 1;  /* bit[0]    : �����������Ƶ�����ֳ���ѡ��
                                                         0�������Ƶ�����ֳ�����20��
                                                         1�������Ƶ�����ֳ�����24�� */
        unsigned int  ch_status5_3  : 3;  /* bit[1-3]  : ��������Ƶ�����ֵĳ��ȡ�
                                                         �������Ƶ������Ϊ24ʱ��Ƶ�����ֵĳ��ȣ�
                                                         001��20bit��
                                                         101��24bit��
                                                         �������Ȳ���IEC 60958Э�顣
                                                         �������Ƶ������Ϊ20ʱ��Ƶ�����ֵĳ��ȣ�
                                                         001��16bit��
                                                         101��20bit��
                                                         �������Ȳ���IEC 60958Э�顣 */
        unsigned int  ch_status5_7  : 4;  /* bit[4-7]  : ������Դ�����ʡ�
                                                         0x5��96kHz��
                                                         0xC��32kHz��
                                                         0xD��48kHz��
                                                         0xF��44.1kHz��
                                                         ������������ο�IEC 60958Э�顣 */
        unsigned int  ch_status5_8  : 1;  /* bit[8]    : �����������Ƶ�����ֳ���ѡ��
                                                         0�������Ƶ�����ֳ�����20��
                                                         1�������Ƶ�����ֳ�����24�� */
        unsigned int  ch_status5_11 : 3;  /* bit[9-11] : ��������Ƶ�����ֵĳ��ȡ�
                                                         �������Ƶ������Ϊ24ʱ��
                                                         001��20bit��
                                                         110��21bit��
                                                         010��22bit��
                                                         100��23bit��
                                                         101��24bit��
                                                         �����������������á�
                                                         �������Ƶ������Ϊ20ʱ��
                                                         001��16bit��
                                                         110��17bit��
                                                         010��18bit��
                                                         100��19bit��
                                                         101��20bit��
                                                         �����������������á� */
        unsigned int  ch_status5_15 : 4;  /* bit[12-15]: ������Դ�����ʡ�
                                                         0x5��96kHz��
                                                         0xC��32kHz��
                                                         0xD��48kHz��
                                                         0xF��44.1kHz��
                                                         ������������ο�IEC 60958Э�顣 */
        unsigned int  reserved      : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_ASP_HDMI_SPDIF_CH_STATUS5_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_0_START   (0)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_0_END     (0)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_3_START   (1)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_3_END     (3)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_7_START   (4)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_7_END     (7)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_8_START   (8)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_8_END     (8)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_11_START  (9)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_11_END    (11)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_15_START  (12)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_15_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_SPDIF_USER_DATA1_UNION
 �ṹ˵��  : SPDIF_USER_DATA1 �Ĵ����ṹ���塣��ַƫ����:0x840����ֵ:0x00000000�����:32
 �Ĵ���˵��: �û����ݼĴ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  user_data1_lc : 8;  /* bit[0-7]  : �������û�������Ϣ��
                                                         Ĭ��Ϊ0x00����û������������°�Ĭ���������ô˼Ĵ����� */
        unsigned int  user_data1_rc : 8;  /* bit[8-15] : �������û�������Ϣ��
                                                         Ĭ��Ϊ0x00����û������������°�Ĭ���������ô˼Ĵ����� */
        unsigned int  reserved      : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_ASP_HDMI_SPDIF_USER_DATA1_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_USER_DATA1_user_data1_lc_START  (0)
#define SOC_ASP_HDMI_SPDIF_USER_DATA1_user_data1_lc_END    (7)
#define SOC_ASP_HDMI_SPDIF_USER_DATA1_user_data1_rc_START  (8)
#define SOC_ASP_HDMI_SPDIF_USER_DATA1_user_data1_rc_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_SPDIF_USER_DATA2_UNION
 �ṹ˵��  : SPDIF_USER_DATA2 �Ĵ����ṹ���塣��ַƫ����:0x844����ֵ:0x00000000�����:32
 �Ĵ���˵��: �û����ݼĴ���2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  user_data2_lc : 8;  /* bit[0-7]  : �������û�������Ϣ��
                                                         Ĭ��Ϊ0x00����û������������°�Ĭ���������ô˼Ĵ����� */
        unsigned int  user_data2_rc : 8;  /* bit[8-15] : �������û�������Ϣ��
                                                         Ĭ��Ϊ0x00����û������������°�Ĭ���������ô˼Ĵ����� */
        unsigned int  reserved      : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_ASP_HDMI_SPDIF_USER_DATA2_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_USER_DATA2_user_data2_lc_START  (0)
#define SOC_ASP_HDMI_SPDIF_USER_DATA2_user_data2_lc_END    (7)
#define SOC_ASP_HDMI_SPDIF_USER_DATA2_user_data2_rc_START  (8)
#define SOC_ASP_HDMI_SPDIF_USER_DATA2_user_data2_rc_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_SPDIF_USER_DATA3_UNION
 �ṹ˵��  : SPDIF_USER_DATA3 �Ĵ����ṹ���塣��ַƫ����:0x848����ֵ:0x00000000�����:32
 �Ĵ���˵��: �û����ݼĴ���3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  user_data3_lc : 8;  /* bit[0-7]  : �������û�������Ϣ��
                                                         Ĭ��Ϊ0x00����û������������°�Ĭ���������ô˼Ĵ����� */
        unsigned int  user_data3_rc : 8;  /* bit[8-15] : �������û�������Ϣ��
                                                         Ĭ��Ϊ0x00����û������������°�Ĭ���������ô˼Ĵ����� */
        unsigned int  reserved      : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_ASP_HDMI_SPDIF_USER_DATA3_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_USER_DATA3_user_data3_lc_START  (0)
#define SOC_ASP_HDMI_SPDIF_USER_DATA3_user_data3_lc_END    (7)
#define SOC_ASP_HDMI_SPDIF_USER_DATA3_user_data3_rc_START  (8)
#define SOC_ASP_HDMI_SPDIF_USER_DATA3_user_data3_rc_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_SPDIF_USER_DATA4_UNION
 �ṹ˵��  : SPDIF_USER_DATA4 �Ĵ����ṹ���塣��ַƫ����:0x84C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �û����ݼĴ���4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  user_data4_lc : 8;  /* bit[0-7]  : �������û�������Ϣ��
                                                         Ĭ��Ϊ0x00����û������������°�Ĭ���������ô˼Ĵ����� */
        unsigned int  user_data4_rc : 8;  /* bit[8-15] : �������û�������Ϣ��
                                                         Ĭ��Ϊ0x00����û������������°�Ĭ���������ô˼Ĵ����� */
        unsigned int  reserved      : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_ASP_HDMI_SPDIF_USER_DATA4_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_USER_DATA4_user_data4_lc_START  (0)
#define SOC_ASP_HDMI_SPDIF_USER_DATA4_user_data4_lc_END    (7)
#define SOC_ASP_HDMI_SPDIF_USER_DATA4_user_data4_rc_START  (8)
#define SOC_ASP_HDMI_SPDIF_USER_DATA4_user_data4_rc_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_SPDIF_USER_DATA5_UNION
 �ṹ˵��  : SPDIF_USER_DATA5 �Ĵ����ṹ���塣��ַƫ����:0x850����ֵ:0x00000000�����:32
 �Ĵ���˵��: �û����ݼĴ���5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  user_data5_lc : 8;  /* bit[0-7]  : �������û�������Ϣ��
                                                         Ĭ��Ϊ0x00����û������������°�Ĭ���������ô˼Ĵ����� */
        unsigned int  user_data5_rc : 8;  /* bit[8-15] : �������û�������Ϣ��
                                                         Ĭ��Ϊ0x00����û������������°�Ĭ���������ô˼Ĵ����� */
        unsigned int  reserved      : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_ASP_HDMI_SPDIF_USER_DATA5_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_USER_DATA5_user_data5_lc_START  (0)
#define SOC_ASP_HDMI_SPDIF_USER_DATA5_user_data5_lc_END    (7)
#define SOC_ASP_HDMI_SPDIF_USER_DATA5_user_data5_rc_START  (8)
#define SOC_ASP_HDMI_SPDIF_USER_DATA5_user_data5_rc_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_ASP_HDMI_SPDIF_EDITION_UNION
 �ṹ˵��  : SPDIF_EDITION �Ĵ����ṹ���塣��ַƫ����:0x8F0����ֵ:0x00000021�����:32
 �Ĵ���˵��: �汾��Ϣ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  spdif_edition : 8;  /* bit[0-7] : SPDIF�汾�Ĵ����� */
        unsigned int  reserved      : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_ASP_HDMI_SPDIF_EDITION_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_EDITION_spdif_edition_START  (0)
#define SOC_ASP_HDMI_SPDIF_EDITION_spdif_edition_END    (7)






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

#endif /* end of soc_asp_hdmi_interface.h */
