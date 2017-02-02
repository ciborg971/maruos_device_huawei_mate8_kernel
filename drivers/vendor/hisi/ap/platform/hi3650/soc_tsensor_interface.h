/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_tsensor_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:23:15
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_Tsensor.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_TSENSOR_INTERFACE_H__
#define __SOC_TSENSOR_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) register_tsensorc
 ****************************************************************************/
/* �Ĵ���˵����Tsensor1�¶�У׼�Ĵ���1
   λ����UNION�ṹ:  SOC_Tsensor_CALIBRATION11_UNION */
#define SOC_Tsensor_CALIBRATION11_ADDR(base)          ((base) + (0x000))

/* �Ĵ���˵����Tsensor1�¶�У׼�Ĵ���2
   λ����UNION�ṹ:  SOC_Tsensor_CALIBRATION21_UNION */
#define SOC_Tsensor_CALIBRATION21_ADDR(base)          ((base) + (0x004))

/* �Ĵ���˵����Tsensor1ģʽ���üĴ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_CONFIG1_UNION */
#define SOC_Tsensor_TEMP_CONFIG1_ADDR(base)           ((base) + (0x008))

/* �Ĵ���˵����Tsensor1�¶ȼ��ʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_DET_EN1_UNION */
#define SOC_Tsensor_TEMP_DET_EN1_ADDR(base)           ((base) + (0x00C))

/* �Ĵ���˵����Tsensor1�¶ȼ��ȥʹ�ܵȴ��Ĵ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_WAIT_BYPASS1_UNION */
#define SOC_Tsensor_TEMP_WAIT_BYPASS1_ADDR(base)      ((base) + (0x010))

/* �Ĵ���˵����Tsensor1�¶ȼ��ȥʹ�ܵȴ�ʱ��Ĵ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_WAIT_TIME1_UNION */
#define SOC_Tsensor_TEMP_WAIT_TIME1_ADDR(base)        ((base) + (0x014))

/* �Ĵ���˵����Tsensor1�¶ȼ�⵱ǰ״̬�Ĵ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_FSMSTAT1_UNION */
#define SOC_Tsensor_TEMP_FSMSTAT1_ADDR(base)          ((base) + (0x018))

/* �Ĵ���˵����Tsensor1�¶ȼ�����Ĵ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP1_UNION */
#define SOC_Tsensor_TEMP1_ADDR(base)                  ((base) + (0x01C))

/* �Ĵ���˵����Tsensor1�¶ȱ������޼Ĵ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_TH1_UNION */
#define SOC_Tsensor_TEMP_TH1_ADDR(base)               ((base) + (0x020))

/* �Ĵ���˵����Tsensor1�¶ȸ�λ���޼Ĵ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_RST_TH1_UNION */
#define SOC_Tsensor_TEMP_RST_TH1_ADDR(base)           ((base) + (0x024))

/* �Ĵ���˵����Tsensor1�¶Ȼ��ͼĴ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_LAG1_UNION */
#define SOC_Tsensor_TEMP_LAG1_ADDR(base)              ((base) + (0x028))

/* �Ĵ���˵����Tsensor1�ж����μĴ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_INT_MSK1_UNION */
#define SOC_Tsensor_TEMP_INT_MSK1_ADDR(base)          ((base) + (0x02C))

/* �Ĵ���˵����Tsensor1�ж�����Ĵ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_INT_CLR1_UNION */
#define SOC_Tsensor_TEMP_INT_CLR1_ADDR(base)          ((base) + (0x030))

/* �Ĵ���˵����Tsensor1��λ���μĴ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_RST_MSK1_UNION */
#define SOC_Tsensor_TEMP_RST_MSK1_ADDR(base)          ((base) + (0x034))

/* �Ĵ���˵����Tsensor1ԭʼ�жϼĴ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_RAWINT1_UNION */
#define SOC_Tsensor_TEMP_RAWINT1_ADDR(base)           ((base) + (0x038))

/* �Ĵ���˵����Tsensor1�����жϼĴ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_MSKINT1_UNION */
#define SOC_Tsensor_TEMP_MSKINT1_ADDR(base)           ((base) + (0x03C))

/* �Ĵ���˵����Tsensor2�¶�У׼�Ĵ���1
   λ����UNION�ṹ:  SOC_Tsensor_CALIBRATION12_UNION */
#define SOC_Tsensor_CALIBRATION12_ADDR(base)          ((base) + (0x040))

/* �Ĵ���˵����Tsensor2�¶�У׼�Ĵ���2
   λ����UNION�ṹ:  SOC_Tsensor_CALIBRATION22_UNION */
#define SOC_Tsensor_CALIBRATION22_ADDR(base)          ((base) + (0x044))

/* �Ĵ���˵����Tsensor2ģʽ���üĴ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_CONFIG2_UNION */
#define SOC_Tsensor_TEMP_CONFIG2_ADDR(base)           ((base) + (0x048))

/* �Ĵ���˵����Tsensor2�¶ȼ��ʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_DET_EN2_UNION */
#define SOC_Tsensor_TEMP_DET_EN2_ADDR(base)           ((base) + (0x04C))

/* �Ĵ���˵����Tsensor2�¶ȼ��ȥʹ�ܵȴ��Ĵ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_WAIT_BYPASS2_UNION */
#define SOC_Tsensor_TEMP_WAIT_BYPASS2_ADDR(base)      ((base) + (0x050))

/* �Ĵ���˵����Tsensor2�¶ȼ��ȥʹ�ܵȴ�ʱ��Ĵ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_WAIT_TIME2_UNION */
#define SOC_Tsensor_TEMP_WAIT_TIME2_ADDR(base)        ((base) + (0x054))

/* �Ĵ���˵����Tsensor2�¶ȼ�⵱ǰ״̬�Ĵ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_FSMSTAT2_UNION */
#define SOC_Tsensor_TEMP_FSMSTAT2_ADDR(base)          ((base) + (0x058))

/* �Ĵ���˵����Tsensor2�¶ȼ�����Ĵ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP2_UNION */
#define SOC_Tsensor_TEMP2_ADDR(base)                  ((base) + (0x05C))

/* �Ĵ���˵����Tsensor2�¶ȱ������޼Ĵ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_TH2_UNION */
#define SOC_Tsensor_TEMP_TH2_ADDR(base)               ((base) + (0x060))

/* �Ĵ���˵����Tsensor2�¶ȸ�λ���޼Ĵ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_RST_TH2_UNION */
#define SOC_Tsensor_TEMP_RST_TH2_ADDR(base)           ((base) + (0x064))

/* �Ĵ���˵����Tsensor2�¶Ȼ��ͼĴ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_LAG2_UNION */
#define SOC_Tsensor_TEMP_LAG2_ADDR(base)              ((base) + (0x068))

/* �Ĵ���˵����Tsensor2�ж����μĴ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_INT_MSK2_UNION */
#define SOC_Tsensor_TEMP_INT_MSK2_ADDR(base)          ((base) + (0x06C))

/* �Ĵ���˵����Tsensor2�ж�����Ĵ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_INT_CLR2_UNION */
#define SOC_Tsensor_TEMP_INT_CLR2_ADDR(base)          ((base) + (0x070))

/* �Ĵ���˵����Tsensor2��λ���μĴ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_RST_MSK2_UNION */
#define SOC_Tsensor_TEMP_RST_MSK2_ADDR(base)          ((base) + (0x074))

/* �Ĵ���˵����Tsensor2ԭʼ�жϼĴ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_RAWINT2_UNION */
#define SOC_Tsensor_TEMP_RAWINT2_ADDR(base)           ((base) + (0x078))

/* �Ĵ���˵����Tsensor2�����жϼĴ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_MSKINT2_UNION */
#define SOC_Tsensor_TEMP_MSKINT2_ADDR(base)           ((base) + (0x07C))

/* �Ĵ���˵����Tsensor3�¶�У׼�Ĵ���1
   λ����UNION�ṹ:  SOC_Tsensor_CALIBRATION13_UNION */
#define SOC_Tsensor_CALIBRATION13_ADDR(base)          ((base) + (0x080))

/* �Ĵ���˵����Tsensor3�¶�У׼�Ĵ���2
   λ����UNION�ṹ:  SOC_Tsensor_CALIBRATION23_UNION */
#define SOC_Tsensor_CALIBRATION23_ADDR(base)          ((base) + (0x084))

/* �Ĵ���˵����Tsensor3ģʽ���üĴ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_CONFIG3_UNION */
#define SOC_Tsensor_TEMP_CONFIG3_ADDR(base)           ((base) + (0x088))

/* �Ĵ���˵����Tsensor3�¶ȼ��ʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_DET_EN3_UNION */
#define SOC_Tsensor_TEMP_DET_EN3_ADDR(base)           ((base) + (0x08C))

/* �Ĵ���˵����Tsensor3�¶ȼ��ȥʹ�ܵȴ��Ĵ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_WAIT_BYPASS3_UNION */
#define SOC_Tsensor_TEMP_WAIT_BYPASS3_ADDR(base)      ((base) + (0x090))

/* �Ĵ���˵����Tsensor3�¶ȼ��ȥʹ�ܵȴ�ʱ��Ĵ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_WAIT_TIME3_UNION */
#define SOC_Tsensor_TEMP_WAIT_TIME3_ADDR(base)        ((base) + (0x094))

/* �Ĵ���˵����Tsensor3�¶ȼ�⵱ǰ״̬�Ĵ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_FSMSTAT3_UNION */
#define SOC_Tsensor_TEMP_FSMSTAT3_ADDR(base)          ((base) + (0x098))

/* �Ĵ���˵����Tsensor3�¶ȼ�����Ĵ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP3_UNION */
#define SOC_Tsensor_TEMP3_ADDR(base)                  ((base) + (0x09C))

/* �Ĵ���˵����Tsensor3�¶ȱ������޼Ĵ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_TH3_UNION */
#define SOC_Tsensor_TEMP_TH3_ADDR(base)               ((base) + (0x0A0))

/* �Ĵ���˵����Tsensor3�¶ȸ�λ���޼Ĵ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_RST_TH3_UNION */
#define SOC_Tsensor_TEMP_RST_TH3_ADDR(base)           ((base) + (0x0A4))

/* �Ĵ���˵����Tsensor3�¶Ȼ��ͼĴ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_LAG3_UNION */
#define SOC_Tsensor_TEMP_LAG3_ADDR(base)              ((base) + (0x0A8))

/* �Ĵ���˵����Tsensor3�ж����μĴ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_INT_MSK3_UNION */
#define SOC_Tsensor_TEMP_INT_MSK3_ADDR(base)          ((base) + (0x0AC))

/* �Ĵ���˵����Tsensor3�ж�����Ĵ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_INT_CLR3_UNION */
#define SOC_Tsensor_TEMP_INT_CLR3_ADDR(base)          ((base) + (0x0B0))

/* �Ĵ���˵����Tsensor3��λ���μĴ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_RST_MSK3_UNION */
#define SOC_Tsensor_TEMP_RST_MSK3_ADDR(base)          ((base) + (0x0B4))

/* �Ĵ���˵����Tsensor3ԭʼ�жϼĴ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_RAWINT3_UNION */
#define SOC_Tsensor_TEMP_RAWINT3_ADDR(base)           ((base) + (0x0B8))

/* �Ĵ���˵����Tsensor3�����жϼĴ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_MSKINT3_UNION */
#define SOC_Tsensor_TEMP_MSKINT3_ADDR(base)           ((base) + (0x0BC))

/* �Ĵ���˵����Tsensor4�¶�У׼�Ĵ���1
   λ����UNION�ṹ:  SOC_Tsensor_CALIBRATION14_UNION */
#define SOC_Tsensor_CALIBRATION14_ADDR(base)          ((base) + (0x0C0))

/* �Ĵ���˵����Tsensor4�¶�У׼�Ĵ���2
   λ����UNION�ṹ:  SOC_Tsensor_CALIBRATION24_UNION */
#define SOC_Tsensor_CALIBRATION24_ADDR(base)          ((base) + (0x0C4))

/* �Ĵ���˵����Tsensor4ģʽ���üĴ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_CONFIG4_UNION */
#define SOC_Tsensor_TEMP_CONFIG4_ADDR(base)           ((base) + (0x0C8))

/* �Ĵ���˵����Tsensor4�¶ȼ��ʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_DET_EN4_UNION */
#define SOC_Tsensor_TEMP_DET_EN4_ADDR(base)           ((base) + (0x0CC))

/* �Ĵ���˵����Tsensor4�¶ȼ��ȥʹ�ܵȴ��Ĵ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_WAIT_BYPASS4_UNION */
#define SOC_Tsensor_TEMP_WAIT_BYPASS4_ADDR(base)      ((base) + (0x0D0))

/* �Ĵ���˵����Tsensor4�¶ȼ��ȥʹ�ܵȴ�ʱ��Ĵ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_WAIT_TIME4_UNION */
#define SOC_Tsensor_TEMP_WAIT_TIME4_ADDR(base)        ((base) + (0x0D4))

/* �Ĵ���˵����Tsensor4�¶ȼ�⵱ǰ״̬�Ĵ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_FSMSTAT4_UNION */
#define SOC_Tsensor_TEMP_FSMSTAT4_ADDR(base)          ((base) + (0x0D8))

/* �Ĵ���˵����Tsensor4�¶ȼ�����Ĵ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP4_UNION */
#define SOC_Tsensor_TEMP4_ADDR(base)                  ((base) + (0x0DC))

/* �Ĵ���˵����Tsensor4�¶ȱ������޼Ĵ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_TH4_UNION */
#define SOC_Tsensor_TEMP_TH4_ADDR(base)               ((base) + (0x0E0))

/* �Ĵ���˵����Tsensor4�¶ȸ�λ���޼Ĵ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_RST_TH4_UNION */
#define SOC_Tsensor_TEMP_RST_TH4_ADDR(base)           ((base) + (0x0E4))

/* �Ĵ���˵����Tsensor4�¶Ȼ��ͼĴ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_LAG4_UNION */
#define SOC_Tsensor_TEMP_LAG4_ADDR(base)              ((base) + (0x0E8))

/* �Ĵ���˵����Tsensor4�ж����μĴ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_INT_MSK4_UNION */
#define SOC_Tsensor_TEMP_INT_MSK4_ADDR(base)          ((base) + (0x0EC))

/* �Ĵ���˵����Tsensor4�ж�����Ĵ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_INT_CLR4_UNION */
#define SOC_Tsensor_TEMP_INT_CLR4_ADDR(base)          ((base) + (0x0F0))

/* �Ĵ���˵����Tsensor4��λ���μĴ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_RST_MSK4_UNION */
#define SOC_Tsensor_TEMP_RST_MSK4_ADDR(base)          ((base) + (0x0F4))

/* �Ĵ���˵����Tsensor4ԭʼ�жϼĴ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_RAWINT4_UNION */
#define SOC_Tsensor_TEMP_RAWINT4_ADDR(base)           ((base) + (0x0F8))

/* �Ĵ���˵����Tsensor4�����жϼĴ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_MSKINT4_UNION */
#define SOC_Tsensor_TEMP_MSKINT4_ADDR(base)           ((base) + (0x0FC))

/* �Ĵ���˵����Tsensor1������ƼĴ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_SOFTCTRL1_UNION */
#define SOC_Tsensor_TEMP_SOFTCTRL1_ADDR(base)         ((base) + (0x100))

/* �Ĵ���˵����Tsensor1������Ƽ�����Ĵ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP1_SOFT_UNION */
#define SOC_Tsensor_TEMP1_SOFT_ADDR(base)             ((base) + (0x104))

/* �Ĵ���˵����Tsensor2������ƼĴ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_SOFTCTRL2_UNION */
#define SOC_Tsensor_TEMP_SOFTCTRL2_ADDR(base)         ((base) + (0x108))

/* �Ĵ���˵����Tsensor2������Ƽ�����Ĵ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP2_SOFT_UNION */
#define SOC_Tsensor_TEMP2_SOFT_ADDR(base)             ((base) + (0x10C))

/* �Ĵ���˵����Tsensor3������ƼĴ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_SOFTCTRL3_UNION */
#define SOC_Tsensor_TEMP_SOFTCTRL3_ADDR(base)         ((base) + (0x110))

/* �Ĵ���˵����Tsensor3������Ƽ�����Ĵ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP3_SOFT_UNION */
#define SOC_Tsensor_TEMP3_SOFT_ADDR(base)             ((base) + (0x114))

/* �Ĵ���˵����Tsensor4������ƼĴ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP_SOFTCTRL4_UNION */
#define SOC_Tsensor_TEMP_SOFTCTRL4_ADDR(base)         ((base) + (0x118))

/* �Ĵ���˵����Tsensor4������Ƽ�����Ĵ���
   λ����UNION�ṹ:  SOC_Tsensor_TEMP4_SOFT_UNION */
#define SOC_Tsensor_TEMP4_SOFT_ADDR(base)             ((base) + (0x11C))





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
                     (1/1) register_tsensorc
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_Tsensor_CALIBRATION11_UNION
 �ṹ˵��  : CALIBRATION11 �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor1�¶�У׼�Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  local_sensorerror   : 10; /* bit[0-9]  : ATE �¶�У׼�����Ϣ�����λ��ʾ���ţ�
                                                               1�������¶ȼ�ȥУ׼���
                                                               0�������¶ȼ���У׼��� */
        unsigned int  remote_sensor1error : 6;  /* bit[10-15]: reserved */
        unsigned int  remote_sensor2error : 8;  /* bit[16-23]: reserved */
        unsigned int  remote_sensor3error : 8;  /* bit[24-31]: reserved */
    } reg;
} SOC_Tsensor_CALIBRATION11_UNION;
#endif
#define SOC_Tsensor_CALIBRATION11_local_sensorerror_START    (0)
#define SOC_Tsensor_CALIBRATION11_local_sensorerror_END      (9)
#define SOC_Tsensor_CALIBRATION11_remote_sensor1error_START  (10)
#define SOC_Tsensor_CALIBRATION11_remote_sensor1error_END    (15)
#define SOC_Tsensor_CALIBRATION11_remote_sensor2error_START  (16)
#define SOC_Tsensor_CALIBRATION11_remote_sensor2error_END    (23)
#define SOC_Tsensor_CALIBRATION11_remote_sensor3error_START  (24)
#define SOC_Tsensor_CALIBRATION11_remote_sensor3error_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_CALIBRATION21_UNION
 �ṹ˵��  : CALIBRATION21 �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor1�¶�У׼�Ĵ���2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  remote_sensor4error : 10; /* bit[0-9]  : reserved */
        unsigned int  remote_sensor5error : 6;  /* bit[10-15]: reserved */
        unsigned int  remote_sensor6error : 8;  /* bit[16-23]: reserved */
        unsigned int  remote_sensor7error : 8;  /* bit[24-31]: reserved */
    } reg;
} SOC_Tsensor_CALIBRATION21_UNION;
#endif
#define SOC_Tsensor_CALIBRATION21_remote_sensor4error_START  (0)
#define SOC_Tsensor_CALIBRATION21_remote_sensor4error_END    (9)
#define SOC_Tsensor_CALIBRATION21_remote_sensor5error_START  (10)
#define SOC_Tsensor_CALIBRATION21_remote_sensor5error_END    (15)
#define SOC_Tsensor_CALIBRATION21_remote_sensor6error_START  (16)
#define SOC_Tsensor_CALIBRATION21_remote_sensor6error_END    (23)
#define SOC_Tsensor_CALIBRATION21_remote_sensor7error_START  (24)
#define SOC_Tsensor_CALIBRATION21_remote_sensor7error_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_CONFIG1_UNION
 �ṹ˵��  : TEMP_CONFIG1 �Ĵ����ṹ���塣��ַƫ����:0x008����ֵ:0x00002000�����:32
 �Ĵ���˵��: Tsensor1ģʽ���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  channel_num1 : 3;  /* bit[0-2]  : Tsensor1ͨ������ѡ��
                                                        0��ֻ��LOCAL SENSOR */
        unsigned int  channel_sel1 : 4;  /* bit[3-6]  : Tsensor1ͨ��ģʽѡ��
                                                        0000����ѡ��LOCAL SENSOR���¶�ֵ
                                                        0001~1111�������� */
        unsigned int  temp_mode1   : 2;  /* bit[7-8]  : Tsensor1ͬһͨ���¶Ȳ���ģʽѡ��
                                                        00������β���ȡ��ֵ
                                                        01��������
                                                        10��������
                                                        11�������� */
        unsigned int  sample_num1  : 8;  /* bit[9-16] : Tsensor1ͬһͨ����������ѡ��ֻ֧��16����������16��32��64��128��256
                                                        ����ֵΪN����Ӧ����2*N
                                                        ����ֵΪ16��32��64��128��256��Ӧ����ֵΪ8��16��32��64��128 */
        unsigned int  ct_sel_apb1  : 2;  /* bit[17-18]: Tsensor1 HKADCת��ʱ��ѡ��
                                                        00����0.512ms
                                                        01����0.256ms
                                                        10����1.024ms
                                                        11����2.048ms */
        unsigned int  reserved     : 13; /* bit[19-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_CONFIG1_UNION;
#endif
#define SOC_Tsensor_TEMP_CONFIG1_channel_num1_START  (0)
#define SOC_Tsensor_TEMP_CONFIG1_channel_num1_END    (2)
#define SOC_Tsensor_TEMP_CONFIG1_channel_sel1_START  (3)
#define SOC_Tsensor_TEMP_CONFIG1_channel_sel1_END    (6)
#define SOC_Tsensor_TEMP_CONFIG1_temp_mode1_START    (7)
#define SOC_Tsensor_TEMP_CONFIG1_temp_mode1_END      (8)
#define SOC_Tsensor_TEMP_CONFIG1_sample_num1_START   (9)
#define SOC_Tsensor_TEMP_CONFIG1_sample_num1_END     (16)
#define SOC_Tsensor_TEMP_CONFIG1_ct_sel_apb1_START   (17)
#define SOC_Tsensor_TEMP_CONFIG1_ct_sel_apb1_END     (18)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_DET_EN1_UNION
 �ṹ˵��  : TEMP_DET_EN1 �Ĵ����ṹ���塣��ַƫ����:0x00C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor1�¶ȼ��ʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_det_en1 : 1;  /* bit[0]   : Tsensor1�¶Ȳ���ʹ�ܼĴ�����
                                                       0����ʹ��
                                                       1��ʹ�� */
        unsigned int  calib1       : 1;  /* bit[1]   : Tsensor1У׼ʹ��λ
                                                       1'b1��������У׼�㷨
                                                       1'b0������У׼�㷨��Ĭ�ϣ� */
        unsigned int  calib1_en    : 1;  /* bit[2]   : ʹ�ܺ��ܹ�ͨ��VCALIB1���е�ѹ��ʽУ׼��
                                                       1'b0:disable
                                                       1'b1:��ʾenable
                                                       ȱʡΪ��0�������ߵ�ƽ0.8V�� */
        unsigned int  reserved     : 29; /* bit[3-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_DET_EN1_UNION;
#endif
#define SOC_Tsensor_TEMP_DET_EN1_temp_det_en1_START  (0)
#define SOC_Tsensor_TEMP_DET_EN1_temp_det_en1_END    (0)
#define SOC_Tsensor_TEMP_DET_EN1_calib1_START        (1)
#define SOC_Tsensor_TEMP_DET_EN1_calib1_END          (1)
#define SOC_Tsensor_TEMP_DET_EN1_calib1_en_START     (2)
#define SOC_Tsensor_TEMP_DET_EN1_calib1_en_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_WAIT_BYPASS1_UNION
 �ṹ˵��  : TEMP_WAIT_BYPASS1 �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x00000001�����:32
 �Ĵ���˵��: Tsensor1�¶ȼ��ȥʹ�ܵȴ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_wait_bypass1 : 1;  /* bit[0]   : Tsensor1ȥʹ�ܺ�ȴ��Ĵ�����
                                                            0��ȥʹ�ܺ�ȴ����ȴ�ʱ�������
                                                            1��ȥʹ�ܺ󲻵ȴ� */
        unsigned int  reserved          : 31; /* bit[1-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_WAIT_BYPASS1_UNION;
#endif
#define SOC_Tsensor_TEMP_WAIT_BYPASS1_temp_wait_bypass1_START  (0)
#define SOC_Tsensor_TEMP_WAIT_BYPASS1_temp_wait_bypass1_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_WAIT_TIME1_UNION
 �ṹ˵��  : TEMP_WAIT_TIME1 �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x000001F4�����:32
 �Ĵ���˵��: Tsensor1�¶ȼ��ȥʹ�ܵȴ�ʱ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_wait_time1 : 32; /* bit[0-31]: reserved */
    } reg;
} SOC_Tsensor_TEMP_WAIT_TIME1_UNION;
#endif
#define SOC_Tsensor_TEMP_WAIT_TIME1_temp_wait_time1_START  (0)
#define SOC_Tsensor_TEMP_WAIT_TIME1_temp_wait_time1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_FSMSTAT1_UNION
 �ṹ˵��  : TEMP_FSMSTAT1 �Ĵ����ṹ���塣��ַƫ����:0x018����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor1�¶ȼ�⵱ǰ״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  m_fsm_stat : 4;  /* bit[0-3] : Tsensor1 SAMPLE״̬����ǰ״̬
                                                     IDLE:0
                                                     INIT:1
                                                     CHANNEL_JUDGE:2
                                                     TEMP_DISEN:3
                                                     CHANNEL_CHG:4
                                                     WAIT2MS:5
                                                     TEMP_EN:6
                                                     SAMPLE_ON:7
                                                     WAIT_SAMPLE:8
                                                     SAMPLE:9
                                                     CHANNEL_MODE:10
                                                     CHANNLE_ADD:11
                                                     DET_TEMP_UPDATE:12 */
        unsigned int  s_fsm_stat : 4;  /* bit[4-7] : Tsensor1 TEMPCTL״̬����ǰ״̬
                                                     IDLE:0
                                                     INIT:1
                                                     WAIT:2
                                                     SAMPLE:3
                                                     CALIB:4
                                                     COUNT:5
                                                     OFF:6 */
        unsigned int  reserved   : 24; /* bit[8-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_FSMSTAT1_UNION;
#endif
#define SOC_Tsensor_TEMP_FSMSTAT1_m_fsm_stat_START  (0)
#define SOC_Tsensor_TEMP_FSMSTAT1_m_fsm_stat_END    (3)
#define SOC_Tsensor_TEMP_FSMSTAT1_s_fsm_stat_START  (4)
#define SOC_Tsensor_TEMP_FSMSTAT1_s_fsm_stat_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP1_UNION
 �ṹ˵��  : TEMP1 �Ĵ����ṹ���塣��ַƫ����:0x01C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor1�¶ȼ�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp1    : 10; /* bit[0-9]  : Tsensor1�¶ȼ�����Ĵ��� */
        unsigned int  reserved : 22; /* bit[10-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP1_UNION;
#endif
#define SOC_Tsensor_TEMP1_temp1_START     (0)
#define SOC_Tsensor_TEMP1_temp1_END       (9)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_TH1_UNION
 �ṹ˵��  : TEMP_TH1 �Ĵ����ṹ���塣��ַƫ����:0x020����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor1�¶ȱ������޼Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_0th1 : 10; /* bit[0-9]  : Tsensor1�¶ȱ�������0 */
        unsigned int  temp_1th1 : 10; /* bit[10-19]: Tsensor1�¶ȱ�������1 */
        unsigned int  temp_2th1 : 10; /* bit[20-29]: Tsensor1�¶ȱ�������2 */
        unsigned int  reserved  : 2;  /* bit[30-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_TH1_UNION;
#endif
#define SOC_Tsensor_TEMP_TH1_temp_0th1_START  (0)
#define SOC_Tsensor_TEMP_TH1_temp_0th1_END    (9)
#define SOC_Tsensor_TEMP_TH1_temp_1th1_START  (10)
#define SOC_Tsensor_TEMP_TH1_temp_1th1_END    (19)
#define SOC_Tsensor_TEMP_TH1_temp_2th1_START  (20)
#define SOC_Tsensor_TEMP_TH1_temp_2th1_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_RST_TH1_UNION
 �ṹ˵��  : TEMP_RST_TH1 �Ĵ����ṹ���塣��ַƫ����:0x024����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor1�¶ȸ�λ���޼Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_rst_th1 : 10; /* bit[0-9]  : Tsensor1�¶ȸ�λ���� */
        unsigned int  reserved     : 22; /* bit[10-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_RST_TH1_UNION;
#endif
#define SOC_Tsensor_TEMP_RST_TH1_temp_rst_th1_START  (0)
#define SOC_Tsensor_TEMP_RST_TH1_temp_rst_th1_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_LAG1_UNION
 �ṹ˵��  : TEMP_LAG1 �Ĵ����ṹ���塣��ַƫ����:0x028����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor1�¶Ȼ��ͼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_lag1 : 7;  /* bit[0-6] : Tsensor1�¶Ȼ������� */
        unsigned int  reserved  : 25; /* bit[7-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_LAG1_UNION;
#endif
#define SOC_Tsensor_TEMP_LAG1_temp_lag1_START  (0)
#define SOC_Tsensor_TEMP_LAG1_temp_lag1_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_INT_MSK1_UNION
 �ṹ˵��  : TEMP_INT_MSK1 �Ĵ����ṹ���塣��ַƫ����:0x02C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor1�ж����μĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_int_msk1 : 1;  /* bit[0]   : Tsensor1�ж����ο���BIT��
                                                        1��������
                                                        0������ */
        unsigned int  reserved      : 31; /* bit[1-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_INT_MSK1_UNION;
#endif
#define SOC_Tsensor_TEMP_INT_MSK1_temp_int_msk1_START  (0)
#define SOC_Tsensor_TEMP_INT_MSK1_temp_int_msk1_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_INT_CLR1_UNION
 �ṹ˵��  : TEMP_INT_CLR1 �Ĵ����ṹ���塣��ַƫ����:0x030����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor1�ж�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_int_clr1 : 1;  /* bit[0]   : Tsensor1�ж��������BIT��
                                                        1�����RAW��MSK�ж�
                                                        0������ */
        unsigned int  reserved      : 31; /* bit[1-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_INT_CLR1_UNION;
#endif
#define SOC_Tsensor_TEMP_INT_CLR1_temp_int_clr1_START  (0)
#define SOC_Tsensor_TEMP_INT_CLR1_temp_int_clr1_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_RST_MSK1_UNION
 �ṹ˵��  : TEMP_RST_MSK1 �Ĵ����ṹ���塣��ַƫ����:0x034����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor1��λ���μĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_rst_msk1 : 1;  /* bit[0]   : Tsensor1��λ���ο���BIT��
                                                        1��������
                                                        0������ */
        unsigned int  reserved      : 31; /* bit[1-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_RST_MSK1_UNION;
#endif
#define SOC_Tsensor_TEMP_RST_MSK1_temp_rst_msk1_START  (0)
#define SOC_Tsensor_TEMP_RST_MSK1_temp_rst_msk1_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_RAWINT1_UNION
 �ṹ˵��  : TEMP_RAWINT1 �Ĵ����ṹ���塣��ַƫ����:0x038����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor1ԭʼ�жϼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_rawint1 : 1;  /* bit[0]   : Tsensor1ԭʼ�жϣ�
                                                       1�����ж�
                                                       0�����ж� */
        unsigned int  reserved     : 31; /* bit[1-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_RAWINT1_UNION;
#endif
#define SOC_Tsensor_TEMP_RAWINT1_temp_rawint1_START  (0)
#define SOC_Tsensor_TEMP_RAWINT1_temp_rawint1_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_MSKINT1_UNION
 �ṹ˵��  : TEMP_MSKINT1 �Ĵ����ṹ���塣��ַƫ����:0x03C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor1�����жϼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_mskint1 : 1;  /* bit[0]   : Tsensor1�����жϣ�
                                                       1�����ж�
                                                       0�����ж� */
        unsigned int  reserved     : 31; /* bit[1-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_MSKINT1_UNION;
#endif
#define SOC_Tsensor_TEMP_MSKINT1_temp_mskint1_START  (0)
#define SOC_Tsensor_TEMP_MSKINT1_temp_mskint1_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_CALIBRATION12_UNION
 �ṹ˵��  : CALIBRATION12 �Ĵ����ṹ���塣��ַƫ����:0x040����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor2�¶�У׼�Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  local_sensorerror   : 10; /* bit[0-9]  : ATE �¶�У׼�����Ϣ�����λ��ʾ���ţ�
                                                               1�������¶ȼ�ȥУ׼���
                                                               0�������¶ȼ���У׼��� */
        unsigned int  remote_sensor1error : 6;  /* bit[10-15]: ATE �¶�У׼�����Ϣ�����λ��ʾ���ţ�
                                                               1�������¶ȼ�ȥУ׼���
                                                               0�������¶ȼ���У׼��� */
        unsigned int  remote_sensor2error : 8;  /* bit[16-23]: ATE �¶�У׼�����Ϣ�����λ��ʾ���ţ�
                                                               1�������¶ȼ�ȥУ׼���
                                                               0�������¶ȼ���У׼��� */
        unsigned int  remote_sensor3error : 8;  /* bit[24-31]: ATE �¶�У׼�����Ϣ�����λ��ʾ���ţ�
                                                               1�������¶ȼ�ȥУ׼���
                                                               0�������¶ȼ���У׼��� */
    } reg;
} SOC_Tsensor_CALIBRATION12_UNION;
#endif
#define SOC_Tsensor_CALIBRATION12_local_sensorerror_START    (0)
#define SOC_Tsensor_CALIBRATION12_local_sensorerror_END      (9)
#define SOC_Tsensor_CALIBRATION12_remote_sensor1error_START  (10)
#define SOC_Tsensor_CALIBRATION12_remote_sensor1error_END    (15)
#define SOC_Tsensor_CALIBRATION12_remote_sensor2error_START  (16)
#define SOC_Tsensor_CALIBRATION12_remote_sensor2error_END    (23)
#define SOC_Tsensor_CALIBRATION12_remote_sensor3error_START  (24)
#define SOC_Tsensor_CALIBRATION12_remote_sensor3error_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_CALIBRATION22_UNION
 �ṹ˵��  : CALIBRATION22 �Ĵ����ṹ���塣��ַƫ����:0x044����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor2�¶�У׼�Ĵ���2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  remote_sensor4error : 10; /* bit[0-9]  : ATE �¶�У׼�����Ϣ�����λ��ʾ���ţ�
                                                               1�������¶ȼ�ȥУ׼���
                                                               0�������¶ȼ���У׼��� */
        unsigned int  remote_sensor5error : 6;  /* bit[10-15]: ATE �¶�У׼�����Ϣ�����λ��ʾ���ţ�
                                                               1�������¶ȼ�ȥУ׼���
                                                               0�������¶ȼ���У׼��� */
        unsigned int  remote_sensor6error : 8;  /* bit[16-23]: ATE �¶�У׼�����Ϣ�����λ��ʾ���ţ�
                                                               1�������¶ȼ�ȥУ׼���
                                                               0�������¶ȼ���У׼��� */
        unsigned int  remote_sensor7error : 8;  /* bit[24-31]: ATE �¶�У׼�����Ϣ�����λ��ʾ���ţ�
                                                               1�������¶ȼ�ȥУ׼���
                                                               0�������¶ȼ���У׼��� */
    } reg;
} SOC_Tsensor_CALIBRATION22_UNION;
#endif
#define SOC_Tsensor_CALIBRATION22_remote_sensor4error_START  (0)
#define SOC_Tsensor_CALIBRATION22_remote_sensor4error_END    (9)
#define SOC_Tsensor_CALIBRATION22_remote_sensor5error_START  (10)
#define SOC_Tsensor_CALIBRATION22_remote_sensor5error_END    (15)
#define SOC_Tsensor_CALIBRATION22_remote_sensor6error_START  (16)
#define SOC_Tsensor_CALIBRATION22_remote_sensor6error_END    (23)
#define SOC_Tsensor_CALIBRATION22_remote_sensor7error_START  (24)
#define SOC_Tsensor_CALIBRATION22_remote_sensor7error_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_CONFIG2_UNION
 �ṹ˵��  : TEMP_CONFIG2 �Ĵ����ṹ���塣��ַƫ����:0x048����ֵ:0x00002000�����:32
 �Ĵ���˵��: Tsensor2ģʽ���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  channel_num2 : 3;  /* bit[0-2]  : Tsensor2ͨ������ѡ��
                                                        0��ֻ��LOCAL SENSOR */
        unsigned int  channel_sel2 : 4;  /* bit[3-6]  : Tsensor2ͨ��ģʽѡ��
                                                        0000����ѡ��LOCAL SENSOR���¶�ֵ
                                                        ������������ */
        unsigned int  temp_mode2   : 2;  /* bit[7-8]  : Tsensor2ͬһͨ���¶Ȳ���ģʽѡ��
                                                        00������β���ȡ��ֵ
                                                        ������������ */
        unsigned int  sample_num2  : 8;  /* bit[9-16] : Tsensor2ͬһͨ����������ѡ��ֻ֧��16����������16��32��64��128��256
                                                        ����ֵΪN����Ӧ����2*N
                                                        ����ֵΪ16��32��64��128��256��Ӧ����ֵΪ8��16��32��64��128 */
        unsigned int  ct_sel_apb2  : 2;  /* bit[17-18]: Tsensor2 HKADCת��ʱ��ѡ��
                                                        00����0.512ms
                                                        01����0.256ms
                                                        10����1.024ms
                                                        11����2.048ms */
        unsigned int  reserved     : 13; /* bit[19-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_CONFIG2_UNION;
#endif
#define SOC_Tsensor_TEMP_CONFIG2_channel_num2_START  (0)
#define SOC_Tsensor_TEMP_CONFIG2_channel_num2_END    (2)
#define SOC_Tsensor_TEMP_CONFIG2_channel_sel2_START  (3)
#define SOC_Tsensor_TEMP_CONFIG2_channel_sel2_END    (6)
#define SOC_Tsensor_TEMP_CONFIG2_temp_mode2_START    (7)
#define SOC_Tsensor_TEMP_CONFIG2_temp_mode2_END      (8)
#define SOC_Tsensor_TEMP_CONFIG2_sample_num2_START   (9)
#define SOC_Tsensor_TEMP_CONFIG2_sample_num2_END     (16)
#define SOC_Tsensor_TEMP_CONFIG2_ct_sel_apb2_START   (17)
#define SOC_Tsensor_TEMP_CONFIG2_ct_sel_apb2_END     (18)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_DET_EN2_UNION
 �ṹ˵��  : TEMP_DET_EN2 �Ĵ����ṹ���塣��ַƫ����:0x04C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor2�¶ȼ��ʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_det_en2 : 1;  /* bit[0]   : Tsensor2�¶Ȳ���ʹ�ܼĴ�����
                                                       0����ʹ��
                                                       1��ʹ�� */
        unsigned int  calib2       : 1;  /* bit[1]   : Tsensor2У׼ʹ��λ
                                                       1'b1��������У׼�㷨
                                                       1'b0������У׼�㷨��Ĭ�ϣ� */
        unsigned int  calib2_en    : 1;  /* bit[2]   : ʹ�ܺ��ܹ�ͨ��VCALIB1���е�ѹ��ʽУ׼��
                                                       1'b0:disable
                                                       1'b1:��ʾenable
                                                       ȱʡΪ��0�������ߵ�ƽ0.8V�� */
        unsigned int  reserved     : 29; /* bit[3-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_DET_EN2_UNION;
#endif
#define SOC_Tsensor_TEMP_DET_EN2_temp_det_en2_START  (0)
#define SOC_Tsensor_TEMP_DET_EN2_temp_det_en2_END    (0)
#define SOC_Tsensor_TEMP_DET_EN2_calib2_START        (1)
#define SOC_Tsensor_TEMP_DET_EN2_calib2_END          (1)
#define SOC_Tsensor_TEMP_DET_EN2_calib2_en_START     (2)
#define SOC_Tsensor_TEMP_DET_EN2_calib2_en_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_WAIT_BYPASS2_UNION
 �ṹ˵��  : TEMP_WAIT_BYPASS2 �Ĵ����ṹ���塣��ַƫ����:0x050����ֵ:0x00000001�����:32
 �Ĵ���˵��: Tsensor2�¶ȼ��ȥʹ�ܵȴ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_wait_bypass2 : 1;  /* bit[0]   : Tsensor2ȥʹ�ܺ�ȴ��Ĵ�����
                                                            0��ȥʹ�ܺ�ȴ����ȴ�ʱ�������
                                                            1��ȥʹ�ܺ󲻵ȴ� */
        unsigned int  reserved          : 31; /* bit[1-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_WAIT_BYPASS2_UNION;
#endif
#define SOC_Tsensor_TEMP_WAIT_BYPASS2_temp_wait_bypass2_START  (0)
#define SOC_Tsensor_TEMP_WAIT_BYPASS2_temp_wait_bypass2_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_WAIT_TIME2_UNION
 �ṹ˵��  : TEMP_WAIT_TIME2 �Ĵ����ṹ���塣��ַƫ����:0x054����ֵ:0x000001F4�����:32
 �Ĵ���˵��: Tsensor2�¶ȼ��ȥʹ�ܵȴ�ʱ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_wait_time2 : 32; /* bit[0-31]: �ȴ�ʱ��ΪN��PCLK���ڡ�N��ʾ������ֵ
                                                          Ĭ��Ϊ500��PCLKΪ100MHZʱ��5us�� */
    } reg;
} SOC_Tsensor_TEMP_WAIT_TIME2_UNION;
#endif
#define SOC_Tsensor_TEMP_WAIT_TIME2_temp_wait_time2_START  (0)
#define SOC_Tsensor_TEMP_WAIT_TIME2_temp_wait_time2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_FSMSTAT2_UNION
 �ṹ˵��  : TEMP_FSMSTAT2 �Ĵ����ṹ���塣��ַƫ����:0x058����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor2�¶ȼ�⵱ǰ״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  m_fsm_stat : 4;  /* bit[0-3] : Tsensor2 SAMPLE״̬����ǰ״̬
                                                     IDLE:0
                                                     INIT:1
                                                     CHANNEL_JUDGE:2
                                                     TEMP_DISEN:3
                                                     CHANNEL_CHG:4
                                                     WAIT2MS:5
                                                     TEMP_EN:6
                                                     SAMPLE_ON:7
                                                     WAIT_SAMPLE:8
                                                     SAMPLE:9
                                                     CHANNEL_MODE:10
                                                     CHANNLE_ADD:11
                                                     DET_TEMP_UPDATE:12 */
        unsigned int  s_fsm_stat : 4;  /* bit[4-7] : Tsensor2 TEMPCTL״̬����ǰ״̬
                                                     IDLE:0
                                                     INIT:1
                                                     WAIT:2
                                                     SAMPLE:3
                                                     CALIB:4
                                                     COUNT:5
                                                     OFF:6 */
        unsigned int  reserved   : 24; /* bit[8-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_FSMSTAT2_UNION;
#endif
#define SOC_Tsensor_TEMP_FSMSTAT2_m_fsm_stat_START  (0)
#define SOC_Tsensor_TEMP_FSMSTAT2_m_fsm_stat_END    (3)
#define SOC_Tsensor_TEMP_FSMSTAT2_s_fsm_stat_START  (4)
#define SOC_Tsensor_TEMP_FSMSTAT2_s_fsm_stat_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP2_UNION
 �ṹ˵��  : TEMP2 �Ĵ����ṹ���塣��ַƫ����:0x05C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor2�¶ȼ�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp2    : 10; /* bit[0-9]  : Tsensor2�¶ȼ�����Ĵ��� */
        unsigned int  reserved : 22; /* bit[10-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP2_UNION;
#endif
#define SOC_Tsensor_TEMP2_temp2_START     (0)
#define SOC_Tsensor_TEMP2_temp2_END       (9)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_TH2_UNION
 �ṹ˵��  : TEMP_TH2 �Ĵ����ṹ���塣��ַƫ����:0x060����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor2�¶ȱ������޼Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_0th2 : 10; /* bit[0-9]  : Tsensor2�¶ȱ�������0 */
        unsigned int  temp_1th2 : 10; /* bit[10-19]: Tsensor2�¶ȱ�������1 */
        unsigned int  temp_2th2 : 10; /* bit[20-29]: Tsensor2�¶ȱ�������2 */
        unsigned int  temp_3th2 : 2;  /* bit[30-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_TH2_UNION;
#endif
#define SOC_Tsensor_TEMP_TH2_temp_0th2_START  (0)
#define SOC_Tsensor_TEMP_TH2_temp_0th2_END    (9)
#define SOC_Tsensor_TEMP_TH2_temp_1th2_START  (10)
#define SOC_Tsensor_TEMP_TH2_temp_1th2_END    (19)
#define SOC_Tsensor_TEMP_TH2_temp_2th2_START  (20)
#define SOC_Tsensor_TEMP_TH2_temp_2th2_END    (29)
#define SOC_Tsensor_TEMP_TH2_temp_3th2_START  (30)
#define SOC_Tsensor_TEMP_TH2_temp_3th2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_RST_TH2_UNION
 �ṹ˵��  : TEMP_RST_TH2 �Ĵ����ṹ���塣��ַƫ����:0x064����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor2�¶ȸ�λ���޼Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_rst_th2 : 10; /* bit[0-9]  : Tsensor2�¶ȸ�λ���� */
        unsigned int  reserved     : 22; /* bit[10-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_RST_TH2_UNION;
#endif
#define SOC_Tsensor_TEMP_RST_TH2_temp_rst_th2_START  (0)
#define SOC_Tsensor_TEMP_RST_TH2_temp_rst_th2_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_LAG2_UNION
 �ṹ˵��  : TEMP_LAG2 �Ĵ����ṹ���塣��ַƫ����:0x068����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor2�¶Ȼ��ͼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_lag2 : 7;  /* bit[0-6] : Tsensor2�¶Ȼ������� */
        unsigned int  reserved  : 25; /* bit[7-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_LAG2_UNION;
#endif
#define SOC_Tsensor_TEMP_LAG2_temp_lag2_START  (0)
#define SOC_Tsensor_TEMP_LAG2_temp_lag2_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_INT_MSK2_UNION
 �ṹ˵��  : TEMP_INT_MSK2 �Ĵ����ṹ���塣��ַƫ����:0x06C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor2�ж����μĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_int_msk2 : 1;  /* bit[0]   : Tsensor2�ж����ο���BIT��
                                                        1��������
                                                        0������ */
        unsigned int  reserved      : 31; /* bit[1-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_INT_MSK2_UNION;
#endif
#define SOC_Tsensor_TEMP_INT_MSK2_temp_int_msk2_START  (0)
#define SOC_Tsensor_TEMP_INT_MSK2_temp_int_msk2_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_INT_CLR2_UNION
 �ṹ˵��  : TEMP_INT_CLR2 �Ĵ����ṹ���塣��ַƫ����:0x070����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor2�ж�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_int_clr2 : 1;  /* bit[0]   : Tsensor2�ж��������BIT��
                                                        1�����RAW��MSK�ж�
                                                        0������ */
        unsigned int  reserved      : 31; /* bit[1-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_INT_CLR2_UNION;
#endif
#define SOC_Tsensor_TEMP_INT_CLR2_temp_int_clr2_START  (0)
#define SOC_Tsensor_TEMP_INT_CLR2_temp_int_clr2_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_RST_MSK2_UNION
 �ṹ˵��  : TEMP_RST_MSK2 �Ĵ����ṹ���塣��ַƫ����:0x074����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor2��λ���μĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_rst_msk2 : 1;  /* bit[0]   : Tsensor2��λ���ο���BIT��
                                                        1��������
                                                        0������ */
        unsigned int  reserved      : 31; /* bit[1-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_RST_MSK2_UNION;
#endif
#define SOC_Tsensor_TEMP_RST_MSK2_temp_rst_msk2_START  (0)
#define SOC_Tsensor_TEMP_RST_MSK2_temp_rst_msk2_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_RAWINT2_UNION
 �ṹ˵��  : TEMP_RAWINT2 �Ĵ����ṹ���塣��ַƫ����:0x078����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor2ԭʼ�жϼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_rawint2 : 1;  /* bit[0]   : Tsensor2ԭʼ�жϣ�
                                                       1�����ж�
                                                       0�����ж� */
        unsigned int  reserved     : 31; /* bit[1-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_RAWINT2_UNION;
#endif
#define SOC_Tsensor_TEMP_RAWINT2_temp_rawint2_START  (0)
#define SOC_Tsensor_TEMP_RAWINT2_temp_rawint2_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_MSKINT2_UNION
 �ṹ˵��  : TEMP_MSKINT2 �Ĵ����ṹ���塣��ַƫ����:0x07C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor2�����жϼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_mskint2 : 1;  /* bit[0]   : Tsensor2�����жϣ�
                                                       1�����ж�
                                                       0�����ж� */
        unsigned int  reserved     : 31; /* bit[1-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_MSKINT2_UNION;
#endif
#define SOC_Tsensor_TEMP_MSKINT2_temp_mskint2_START  (0)
#define SOC_Tsensor_TEMP_MSKINT2_temp_mskint2_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_CALIBRATION13_UNION
 �ṹ˵��  : CALIBRATION13 �Ĵ����ṹ���塣��ַƫ����:0x080����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor3�¶�У׼�Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  local_sensorerror   : 10; /* bit[0-9]  : ATE �¶�У׼�����Ϣ�����λ��ʾ���ţ�
                                                               1�������¶ȼ�ȥУ׼���
                                                               0�������¶ȼ���У׼��� */
        unsigned int  remote_sensor1error : 6;  /* bit[10-15]: ATE �¶�У׼�����Ϣ�����λ��ʾ���ţ�
                                                               1�������¶ȼ�ȥУ׼���
                                                               0�������¶ȼ���У׼��� */
        unsigned int  remote_sensor2error : 8;  /* bit[16-23]: ATE �¶�У׼�����Ϣ�����λ��ʾ���ţ�
                                                               1�������¶ȼ�ȥУ׼���
                                                               0�������¶ȼ���У׼��� */
        unsigned int  remote_sensor3error : 8;  /* bit[24-31]: ATE �¶�У׼�����Ϣ�����λ��ʾ���ţ�
                                                               1�������¶ȼ�ȥУ׼���
                                                               0�������¶ȼ���У׼��� */
    } reg;
} SOC_Tsensor_CALIBRATION13_UNION;
#endif
#define SOC_Tsensor_CALIBRATION13_local_sensorerror_START    (0)
#define SOC_Tsensor_CALIBRATION13_local_sensorerror_END      (9)
#define SOC_Tsensor_CALIBRATION13_remote_sensor1error_START  (10)
#define SOC_Tsensor_CALIBRATION13_remote_sensor1error_END    (15)
#define SOC_Tsensor_CALIBRATION13_remote_sensor2error_START  (16)
#define SOC_Tsensor_CALIBRATION13_remote_sensor2error_END    (23)
#define SOC_Tsensor_CALIBRATION13_remote_sensor3error_START  (24)
#define SOC_Tsensor_CALIBRATION13_remote_sensor3error_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_CALIBRATION23_UNION
 �ṹ˵��  : CALIBRATION23 �Ĵ����ṹ���塣��ַƫ����:0x084����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor3�¶�У׼�Ĵ���2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  remote_sensor4error : 10; /* bit[0-9]  : ATE �¶�У׼�����Ϣ�����λ��ʾ���ţ�
                                                               1�������¶ȼ�ȥУ׼���
                                                               0�������¶ȼ���У׼��� */
        unsigned int  remote_sensor5error : 6;  /* bit[10-15]: ATE �¶�У׼�����Ϣ�����λ��ʾ���ţ�
                                                               1�������¶ȼ�ȥУ׼���
                                                               0�������¶ȼ���У׼��� */
        unsigned int  remote_sensor6error : 8;  /* bit[16-23]: ATE �¶�У׼�����Ϣ�����λ��ʾ���ţ�
                                                               1�������¶ȼ�ȥУ׼���
                                                               0�������¶ȼ���У׼��� */
        unsigned int  remote_sensor7error : 8;  /* bit[24-31]: ATE �¶�У׼�����Ϣ�����λ��ʾ���ţ�
                                                               1�������¶ȼ�ȥУ׼���
                                                               0�������¶ȼ���У׼��� */
    } reg;
} SOC_Tsensor_CALIBRATION23_UNION;
#endif
#define SOC_Tsensor_CALIBRATION23_remote_sensor4error_START  (0)
#define SOC_Tsensor_CALIBRATION23_remote_sensor4error_END    (9)
#define SOC_Tsensor_CALIBRATION23_remote_sensor5error_START  (10)
#define SOC_Tsensor_CALIBRATION23_remote_sensor5error_END    (15)
#define SOC_Tsensor_CALIBRATION23_remote_sensor6error_START  (16)
#define SOC_Tsensor_CALIBRATION23_remote_sensor6error_END    (23)
#define SOC_Tsensor_CALIBRATION23_remote_sensor7error_START  (24)
#define SOC_Tsensor_CALIBRATION23_remote_sensor7error_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_CONFIG3_UNION
 �ṹ˵��  : TEMP_CONFIG3 �Ĵ����ṹ���塣��ַƫ����:0x088����ֵ:0x00002000�����:32
 �Ĵ���˵��: Tsensor3ģʽ���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  channel_num3 : 3;  /* bit[0-2]  : Tsensor3ͨ������ѡ��
                                                        0��ֻ��LOCAL SENSOR */
        unsigned int  channel_sel3 : 4;  /* bit[3-6]  : Tsensor3ͨ��ģʽѡ��
                                                        0000����ѡ��LOCAL SENSOR���¶�ֵ
                                                        ������������ */
        unsigned int  temp_mode3   : 2;  /* bit[7-8]  : Tsensor3ͬһͨ���¶Ȳ���ģʽѡ��
                                                        00������β���ȡ��ֵ
                                                        ������������ */
        unsigned int  sample_num3  : 8;  /* bit[9-16] : Tsensor3ͬһͨ����������ѡ��ֻ֧��16����������16��32��64��128��256
                                                        ����ֵΪN����Ӧ����2*N
                                                        ����ֵΪ16��32��64��128��256��Ӧ����ֵΪ8��16��32��64��128 */
        unsigned int  ct_sel_apb3  : 2;  /* bit[17-18]: Tsensor3 HKADCת��ʱ��ѡ��
                                                        00����0.512ms
                                                        01����0.256ms
                                                        10����1.024ms
                                                        11����2.048ms */
        unsigned int  reserved     : 13; /* bit[19-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_CONFIG3_UNION;
#endif
#define SOC_Tsensor_TEMP_CONFIG3_channel_num3_START  (0)
#define SOC_Tsensor_TEMP_CONFIG3_channel_num3_END    (2)
#define SOC_Tsensor_TEMP_CONFIG3_channel_sel3_START  (3)
#define SOC_Tsensor_TEMP_CONFIG3_channel_sel3_END    (6)
#define SOC_Tsensor_TEMP_CONFIG3_temp_mode3_START    (7)
#define SOC_Tsensor_TEMP_CONFIG3_temp_mode3_END      (8)
#define SOC_Tsensor_TEMP_CONFIG3_sample_num3_START   (9)
#define SOC_Tsensor_TEMP_CONFIG3_sample_num3_END     (16)
#define SOC_Tsensor_TEMP_CONFIG3_ct_sel_apb3_START   (17)
#define SOC_Tsensor_TEMP_CONFIG3_ct_sel_apb3_END     (18)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_DET_EN3_UNION
 �ṹ˵��  : TEMP_DET_EN3 �Ĵ����ṹ���塣��ַƫ����:0x08C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor3�¶ȼ��ʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_det_en3 : 1;  /* bit[0]   : Tsensor3�¶Ȳ���ʹ�ܼĴ�����
                                                       0����ʹ��
                                                       1��ʹ�� */
        unsigned int  calib3       : 1;  /* bit[1]   : Tsensor3У׼ʹ��λ
                                                       1'b1��������У׼�㷨
                                                       1'b0������У׼�㷨��Ĭ�ϣ� */
        unsigned int  calib3_en    : 1;  /* bit[2]   : ʹ�ܺ��ܹ�ͨ��VCALIB1���е�ѹ��ʽУ׼��
                                                       1'b0:disable
                                                       1'b1:��ʾenable
                                                       ȱʡΪ��0�������ߵ�ƽ0.8V�� */
        unsigned int  reserved     : 29; /* bit[3-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_DET_EN3_UNION;
#endif
#define SOC_Tsensor_TEMP_DET_EN3_temp_det_en3_START  (0)
#define SOC_Tsensor_TEMP_DET_EN3_temp_det_en3_END    (0)
#define SOC_Tsensor_TEMP_DET_EN3_calib3_START        (1)
#define SOC_Tsensor_TEMP_DET_EN3_calib3_END          (1)
#define SOC_Tsensor_TEMP_DET_EN3_calib3_en_START     (2)
#define SOC_Tsensor_TEMP_DET_EN3_calib3_en_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_WAIT_BYPASS3_UNION
 �ṹ˵��  : TEMP_WAIT_BYPASS3 �Ĵ����ṹ���塣��ַƫ����:0x090����ֵ:0x00000001�����:32
 �Ĵ���˵��: Tsensor3�¶ȼ��ȥʹ�ܵȴ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_wait_bypass3 : 1;  /* bit[0]   : Tsensor3ȥʹ�ܺ�ȴ��Ĵ�����
                                                            0��ȥʹ�ܺ�ȴ����ȴ�ʱ�������
                                                            1��ȥʹ�ܺ󲻵ȴ� */
        unsigned int  reserved          : 31; /* bit[1-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_WAIT_BYPASS3_UNION;
#endif
#define SOC_Tsensor_TEMP_WAIT_BYPASS3_temp_wait_bypass3_START  (0)
#define SOC_Tsensor_TEMP_WAIT_BYPASS3_temp_wait_bypass3_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_WAIT_TIME3_UNION
 �ṹ˵��  : TEMP_WAIT_TIME3 �Ĵ����ṹ���塣��ַƫ����:0x094����ֵ:0x000001F4�����:32
 �Ĵ���˵��: Tsensor3�¶ȼ��ȥʹ�ܵȴ�ʱ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_wait_time3 : 32; /* bit[0-31]: �ȴ�ʱ��ΪN��PCLK���ڡ�N��ʾ������ֵ
                                                          Ĭ��Ϊ500��PCLKΪ100MHZʱ��5us�� */
    } reg;
} SOC_Tsensor_TEMP_WAIT_TIME3_UNION;
#endif
#define SOC_Tsensor_TEMP_WAIT_TIME3_temp_wait_time3_START  (0)
#define SOC_Tsensor_TEMP_WAIT_TIME3_temp_wait_time3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_FSMSTAT3_UNION
 �ṹ˵��  : TEMP_FSMSTAT3 �Ĵ����ṹ���塣��ַƫ����:0x098����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor3�¶ȼ�⵱ǰ״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  m_fsm_stat : 4;  /* bit[0-3] : Tsensor3 SAMPLE״̬����ǰ״̬
                                                     IDLE:0
                                                     INIT:1
                                                     CHANNEL_JUDGE:2
                                                     TEMP_DISEN:3
                                                     CHANNEL_CHG:4
                                                     WAIT2MS:5
                                                     TEMP_EN:6
                                                     SAMPLE_ON:7
                                                     WAIT_SAMPLE:8
                                                     SAMPLE:9
                                                     CHANNEL_MODE:10
                                                     CHANNLE_ADD:11
                                                     DET_TEMP_UPDATE:12 */
        unsigned int  s_fsm_stat : 4;  /* bit[4-7] : Tsensor3 TEMPCTL״̬����ǰ״̬
                                                     IDLE:0
                                                     INIT:1
                                                     WAIT:2
                                                     SAMPLE:3
                                                     CALIB:4
                                                     COUNT:5
                                                     OFF:6 */
        unsigned int  reserved   : 24; /* bit[8-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_FSMSTAT3_UNION;
#endif
#define SOC_Tsensor_TEMP_FSMSTAT3_m_fsm_stat_START  (0)
#define SOC_Tsensor_TEMP_FSMSTAT3_m_fsm_stat_END    (3)
#define SOC_Tsensor_TEMP_FSMSTAT3_s_fsm_stat_START  (4)
#define SOC_Tsensor_TEMP_FSMSTAT3_s_fsm_stat_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP3_UNION
 �ṹ˵��  : TEMP3 �Ĵ����ṹ���塣��ַƫ����:0x09C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor3�¶ȼ�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp3    : 10; /* bit[0-9]  : Tsensor3�¶ȼ�����Ĵ��� */
        unsigned int  reserved : 22; /* bit[10-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP3_UNION;
#endif
#define SOC_Tsensor_TEMP3_temp3_START     (0)
#define SOC_Tsensor_TEMP3_temp3_END       (9)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_TH3_UNION
 �ṹ˵��  : TEMP_TH3 �Ĵ����ṹ���塣��ַƫ����:0x0A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor3�¶ȱ������޼Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_0th3 : 10; /* bit[0-9]  : Tsensor3�¶ȱ�������0 */
        unsigned int  temp_1th3 : 10; /* bit[10-19]: Tsensor3�¶ȱ�������1 */
        unsigned int  temp_2th3 : 10; /* bit[20-29]: Tsensor3�¶ȱ�������2 */
        unsigned int  temp_3th3 : 2;  /* bit[30-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_TH3_UNION;
#endif
#define SOC_Tsensor_TEMP_TH3_temp_0th3_START  (0)
#define SOC_Tsensor_TEMP_TH3_temp_0th3_END    (9)
#define SOC_Tsensor_TEMP_TH3_temp_1th3_START  (10)
#define SOC_Tsensor_TEMP_TH3_temp_1th3_END    (19)
#define SOC_Tsensor_TEMP_TH3_temp_2th3_START  (20)
#define SOC_Tsensor_TEMP_TH3_temp_2th3_END    (29)
#define SOC_Tsensor_TEMP_TH3_temp_3th3_START  (30)
#define SOC_Tsensor_TEMP_TH3_temp_3th3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_RST_TH3_UNION
 �ṹ˵��  : TEMP_RST_TH3 �Ĵ����ṹ���塣��ַƫ����:0x0A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor3�¶ȸ�λ���޼Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_rst_th3 : 10; /* bit[0-9]  : Tsensor3�¶ȸ�λ���� */
        unsigned int  reserved     : 22; /* bit[10-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_RST_TH3_UNION;
#endif
#define SOC_Tsensor_TEMP_RST_TH3_temp_rst_th3_START  (0)
#define SOC_Tsensor_TEMP_RST_TH3_temp_rst_th3_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_LAG3_UNION
 �ṹ˵��  : TEMP_LAG3 �Ĵ����ṹ���塣��ַƫ����:0x0A8����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor3�¶Ȼ��ͼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_lag3 : 7;  /* bit[0-6] : Tsensor3�¶Ȼ������� */
        unsigned int  reserved  : 25; /* bit[7-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_LAG3_UNION;
#endif
#define SOC_Tsensor_TEMP_LAG3_temp_lag3_START  (0)
#define SOC_Tsensor_TEMP_LAG3_temp_lag3_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_INT_MSK3_UNION
 �ṹ˵��  : TEMP_INT_MSK3 �Ĵ����ṹ���塣��ַƫ����:0x0AC����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor3�ж����μĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_int_msk3 : 1;  /* bit[0]   : Tsensor3�ж����ο���BIT��
                                                        1��������
                                                        0������ */
        unsigned int  reserved      : 31; /* bit[1-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_INT_MSK3_UNION;
#endif
#define SOC_Tsensor_TEMP_INT_MSK3_temp_int_msk3_START  (0)
#define SOC_Tsensor_TEMP_INT_MSK3_temp_int_msk3_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_INT_CLR3_UNION
 �ṹ˵��  : TEMP_INT_CLR3 �Ĵ����ṹ���塣��ַƫ����:0x0B0����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor3�ж�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_int_clr3 : 1;  /* bit[0]   : Tsensor3�ж��������BIT��
                                                        1�����RAW��MSK�ж�
                                                        0������ */
        unsigned int  reserved      : 31; /* bit[1-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_INT_CLR3_UNION;
#endif
#define SOC_Tsensor_TEMP_INT_CLR3_temp_int_clr3_START  (0)
#define SOC_Tsensor_TEMP_INT_CLR3_temp_int_clr3_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_RST_MSK3_UNION
 �ṹ˵��  : TEMP_RST_MSK3 �Ĵ����ṹ���塣��ַƫ����:0x0B4����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor3��λ���μĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_rst_msk3 : 1;  /* bit[0]   : Tsensor3��λ���ο���BIT��
                                                        1��������
                                                        0������ */
        unsigned int  reserved      : 31; /* bit[1-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_RST_MSK3_UNION;
#endif
#define SOC_Tsensor_TEMP_RST_MSK3_temp_rst_msk3_START  (0)
#define SOC_Tsensor_TEMP_RST_MSK3_temp_rst_msk3_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_RAWINT3_UNION
 �ṹ˵��  : TEMP_RAWINT3 �Ĵ����ṹ���塣��ַƫ����:0x0B8����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor3ԭʼ�жϼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_rawint3 : 1;  /* bit[0]   : Tsensor3ԭʼ�жϣ�
                                                       1�����ж�
                                                       0�����ж� */
        unsigned int  reserved     : 31; /* bit[1-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_RAWINT3_UNION;
#endif
#define SOC_Tsensor_TEMP_RAWINT3_temp_rawint3_START  (0)
#define SOC_Tsensor_TEMP_RAWINT3_temp_rawint3_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_MSKINT3_UNION
 �ṹ˵��  : TEMP_MSKINT3 �Ĵ����ṹ���塣��ַƫ����:0x0BC����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor3�����жϼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_mskint3 : 1;  /* bit[0]   : Tsensor3�����жϣ�
                                                       1�����ж�
                                                       0�����ж� */
        unsigned int  reserved     : 31; /* bit[1-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_MSKINT3_UNION;
#endif
#define SOC_Tsensor_TEMP_MSKINT3_temp_mskint3_START  (0)
#define SOC_Tsensor_TEMP_MSKINT3_temp_mskint3_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_CALIBRATION14_UNION
 �ṹ˵��  : CALIBRATION14 �Ĵ����ṹ���塣��ַƫ����:0x0C0����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor4�¶�У׼�Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  local_sensorerror   : 10; /* bit[0-9]  : ATE �¶�У׼�����Ϣ�����λ��ʾ���ţ�
                                                               1�������¶ȼ�ȥУ׼���
                                                               0�������¶ȼ���У׼��� */
        unsigned int  remote_sensor1error : 6;  /* bit[10-15]: ATE �¶�У׼�����Ϣ�����λ��ʾ���ţ�
                                                               1�������¶ȼ�ȥУ׼���
                                                               0�������¶ȼ���У׼��� */
        unsigned int  remote_sensor2error : 8;  /* bit[16-23]: ATE �¶�У׼�����Ϣ�����λ��ʾ���ţ�
                                                               1�������¶ȼ�ȥУ׼���
                                                               0�������¶ȼ���У׼��� */
        unsigned int  remote_sensor3error : 8;  /* bit[24-31]: ATE �¶�У׼�����Ϣ�����λ��ʾ���ţ�
                                                               1�������¶ȼ�ȥУ׼���
                                                               0�������¶ȼ���У׼��� */
    } reg;
} SOC_Tsensor_CALIBRATION14_UNION;
#endif
#define SOC_Tsensor_CALIBRATION14_local_sensorerror_START    (0)
#define SOC_Tsensor_CALIBRATION14_local_sensorerror_END      (9)
#define SOC_Tsensor_CALIBRATION14_remote_sensor1error_START  (10)
#define SOC_Tsensor_CALIBRATION14_remote_sensor1error_END    (15)
#define SOC_Tsensor_CALIBRATION14_remote_sensor2error_START  (16)
#define SOC_Tsensor_CALIBRATION14_remote_sensor2error_END    (23)
#define SOC_Tsensor_CALIBRATION14_remote_sensor3error_START  (24)
#define SOC_Tsensor_CALIBRATION14_remote_sensor3error_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_CALIBRATION24_UNION
 �ṹ˵��  : CALIBRATION24 �Ĵ����ṹ���塣��ַƫ����:0x0C4����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor4�¶�У׼�Ĵ���2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  remote_sensor4error : 10; /* bit[0-9]  : ATE �¶�У׼�����Ϣ�����λ��ʾ���ţ�
                                                               1�������¶ȼ�ȥУ׼���
                                                               0�������¶ȼ���У׼��� */
        unsigned int  remote_sensor5error : 6;  /* bit[10-15]: ATE �¶�У׼�����Ϣ�����λ��ʾ���ţ�
                                                               1�������¶ȼ�ȥУ׼���
                                                               0�������¶ȼ���У׼��� */
        unsigned int  remote_sensor6error : 8;  /* bit[16-23]: ATE �¶�У׼�����Ϣ�����λ��ʾ���ţ�
                                                               1�������¶ȼ�ȥУ׼���
                                                               0�������¶ȼ���У׼��� */
        unsigned int  remote_sensor7error : 8;  /* bit[24-31]: ATE �¶�У׼�����Ϣ�����λ��ʾ���ţ�
                                                               1�������¶ȼ�ȥУ׼���
                                                               0�������¶ȼ���У׼��� */
    } reg;
} SOC_Tsensor_CALIBRATION24_UNION;
#endif
#define SOC_Tsensor_CALIBRATION24_remote_sensor4error_START  (0)
#define SOC_Tsensor_CALIBRATION24_remote_sensor4error_END    (9)
#define SOC_Tsensor_CALIBRATION24_remote_sensor5error_START  (10)
#define SOC_Tsensor_CALIBRATION24_remote_sensor5error_END    (15)
#define SOC_Tsensor_CALIBRATION24_remote_sensor6error_START  (16)
#define SOC_Tsensor_CALIBRATION24_remote_sensor6error_END    (23)
#define SOC_Tsensor_CALIBRATION24_remote_sensor7error_START  (24)
#define SOC_Tsensor_CALIBRATION24_remote_sensor7error_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_CONFIG4_UNION
 �ṹ˵��  : TEMP_CONFIG4 �Ĵ����ṹ���塣��ַƫ����:0x0C8����ֵ:0x00002000�����:32
 �Ĵ���˵��: Tsensor4ģʽ���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  channel_num4 : 3;  /* bit[0-2]  : Tsensor4ͨ������ѡ��
                                                        0��ֻ��LOCAL SENSOR */
        unsigned int  channel_sel4 : 4;  /* bit[3-6]  : Tsensor4ͨ��ģʽѡ��
                                                        ������������ */
        unsigned int  temp_mode4   : 2;  /* bit[7-8]  : Tsensor4ͬһͨ���¶Ȳ���ģʽѡ��
                                                        00������β���ȡ��ֵ
                                                        ������������ */
        unsigned int  sample_num4  : 8;  /* bit[9-16] : Tsensor4ͬһͨ����������ѡ��ֻ֧��16����������16��32��64��128��256
                                                        ����ֵΪN����Ӧ����2*N
                                                        ����ֵΪ16��32��64��128��256��Ӧ����ֵΪ8��16��32��64��128 */
        unsigned int  ct_sel_apb4  : 2;  /* bit[17-18]: Tsensor4 HKADCת��ʱ��ѡ��
                                                        00����0.512ms
                                                        01����0.256ms
                                                        10����1.024ms
                                                        11����2.048ms */
        unsigned int  reserved     : 13; /* bit[19-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_CONFIG4_UNION;
#endif
#define SOC_Tsensor_TEMP_CONFIG4_channel_num4_START  (0)
#define SOC_Tsensor_TEMP_CONFIG4_channel_num4_END    (2)
#define SOC_Tsensor_TEMP_CONFIG4_channel_sel4_START  (3)
#define SOC_Tsensor_TEMP_CONFIG4_channel_sel4_END    (6)
#define SOC_Tsensor_TEMP_CONFIG4_temp_mode4_START    (7)
#define SOC_Tsensor_TEMP_CONFIG4_temp_mode4_END      (8)
#define SOC_Tsensor_TEMP_CONFIG4_sample_num4_START   (9)
#define SOC_Tsensor_TEMP_CONFIG4_sample_num4_END     (16)
#define SOC_Tsensor_TEMP_CONFIG4_ct_sel_apb4_START   (17)
#define SOC_Tsensor_TEMP_CONFIG4_ct_sel_apb4_END     (18)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_DET_EN4_UNION
 �ṹ˵��  : TEMP_DET_EN4 �Ĵ����ṹ���塣��ַƫ����:0x0CC����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor4�¶ȼ��ʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_det_en4 : 1;  /* bit[0]   : Tsensor4�¶Ȳ���ʹ�ܼĴ�����
                                                       0����ʹ��
                                                       1��ʹ�� */
        unsigned int  calib4       : 1;  /* bit[1]   : Tsensor4У׼ʹ��λ
                                                       1'b1��������У׼�㷨
                                                       1'b0������У׼�㷨��Ĭ�ϣ� */
        unsigned int  calib4_en    : 1;  /* bit[2]   : ʹ�ܺ��ܹ�ͨ��VCALIB1���е�ѹ��ʽУ׼��
                                                       1'b0:disable
                                                       1'b1:��ʾenable
                                                       ȱʡΪ��0�������ߵ�ƽ0.8V�� */
        unsigned int  reserved     : 29; /* bit[3-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_DET_EN4_UNION;
#endif
#define SOC_Tsensor_TEMP_DET_EN4_temp_det_en4_START  (0)
#define SOC_Tsensor_TEMP_DET_EN4_temp_det_en4_END    (0)
#define SOC_Tsensor_TEMP_DET_EN4_calib4_START        (1)
#define SOC_Tsensor_TEMP_DET_EN4_calib4_END          (1)
#define SOC_Tsensor_TEMP_DET_EN4_calib4_en_START     (2)
#define SOC_Tsensor_TEMP_DET_EN4_calib4_en_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_WAIT_BYPASS4_UNION
 �ṹ˵��  : TEMP_WAIT_BYPASS4 �Ĵ����ṹ���塣��ַƫ����:0x0D0����ֵ:0x00000001�����:32
 �Ĵ���˵��: Tsensor4�¶ȼ��ȥʹ�ܵȴ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_wait_bypass4 : 1;  /* bit[0]   : Tsensor4ȥʹ�ܺ�ȴ��Ĵ�����
                                                            0��ȥʹ�ܺ�ȴ����ȴ�ʱ�������
                                                            1��ȥʹ�ܺ󲻵ȴ� */
        unsigned int  reserved          : 31; /* bit[1-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_WAIT_BYPASS4_UNION;
#endif
#define SOC_Tsensor_TEMP_WAIT_BYPASS4_temp_wait_bypass4_START  (0)
#define SOC_Tsensor_TEMP_WAIT_BYPASS4_temp_wait_bypass4_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_WAIT_TIME4_UNION
 �ṹ˵��  : TEMP_WAIT_TIME4 �Ĵ����ṹ���塣��ַƫ����:0x0D4����ֵ:0x000001F4�����:32
 �Ĵ���˵��: Tsensor4�¶ȼ��ȥʹ�ܵȴ�ʱ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_wait_time4 : 32; /* bit[0-31]: �ȴ�ʱ��ΪN��PCLK���ڡ�N��ʾ������ֵ
                                                          Ĭ��Ϊ500��PCLKΪ100MHZʱ��5us�� */
    } reg;
} SOC_Tsensor_TEMP_WAIT_TIME4_UNION;
#endif
#define SOC_Tsensor_TEMP_WAIT_TIME4_temp_wait_time4_START  (0)
#define SOC_Tsensor_TEMP_WAIT_TIME4_temp_wait_time4_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_FSMSTAT4_UNION
 �ṹ˵��  : TEMP_FSMSTAT4 �Ĵ����ṹ���塣��ַƫ����:0x0D8����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor4�¶ȼ�⵱ǰ״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  m_fsm_stat : 4;  /* bit[0-3] : Tsensor4 SAMPLE״̬����ǰ״̬
                                                     IDLE:0
                                                     INIT:1
                                                     CHANNEL_JUDGE:2
                                                     TEMP_DISEN:3
                                                     CHANNEL_CHG:4
                                                     WAIT2MS:5
                                                     TEMP_EN:6
                                                     SAMPLE_ON:7
                                                     WAIT_SAMPLE:8
                                                     SAMPLE:9
                                                     CHANNEL_MODE:10
                                                     CHANNLE_ADD:11
                                                     DET_TEMP_UPDATE:12 */
        unsigned int  s_fsm_stat : 4;  /* bit[4-7] : Tsensor4 TEMPCTL״̬����ǰ״̬
                                                     IDLE:0
                                                     INIT:1
                                                     WAIT:2
                                                     SAMPLE:3
                                                     CALIB:4
                                                     COUNT:5
                                                     OFF:6 */
        unsigned int  reserved   : 24; /* bit[8-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_FSMSTAT4_UNION;
#endif
#define SOC_Tsensor_TEMP_FSMSTAT4_m_fsm_stat_START  (0)
#define SOC_Tsensor_TEMP_FSMSTAT4_m_fsm_stat_END    (3)
#define SOC_Tsensor_TEMP_FSMSTAT4_s_fsm_stat_START  (4)
#define SOC_Tsensor_TEMP_FSMSTAT4_s_fsm_stat_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP4_UNION
 �ṹ˵��  : TEMP4 �Ĵ����ṹ���塣��ַƫ����:0x0DC����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor4�¶ȼ�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp4    : 10; /* bit[0-9]  : Tsensor4�¶ȼ�����Ĵ��� */
        unsigned int  reserved : 22; /* bit[10-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP4_UNION;
#endif
#define SOC_Tsensor_TEMP4_temp4_START     (0)
#define SOC_Tsensor_TEMP4_temp4_END       (9)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_TH4_UNION
 �ṹ˵��  : TEMP_TH4 �Ĵ����ṹ���塣��ַƫ����:0x0E0����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor4�¶ȱ������޼Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_0th4 : 10; /* bit[0-9]  : Tsensor4�¶ȱ�������0 */
        unsigned int  temp_1th4 : 10; /* bit[10-19]: Tsensor4�¶ȱ�������1 */
        unsigned int  temp_2th4 : 10; /* bit[20-29]: Tsensor4�¶ȱ�������2 */
        unsigned int  temp_3th4 : 2;  /* bit[30-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_TH4_UNION;
#endif
#define SOC_Tsensor_TEMP_TH4_temp_0th4_START  (0)
#define SOC_Tsensor_TEMP_TH4_temp_0th4_END    (9)
#define SOC_Tsensor_TEMP_TH4_temp_1th4_START  (10)
#define SOC_Tsensor_TEMP_TH4_temp_1th4_END    (19)
#define SOC_Tsensor_TEMP_TH4_temp_2th4_START  (20)
#define SOC_Tsensor_TEMP_TH4_temp_2th4_END    (29)
#define SOC_Tsensor_TEMP_TH4_temp_3th4_START  (30)
#define SOC_Tsensor_TEMP_TH4_temp_3th4_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_RST_TH4_UNION
 �ṹ˵��  : TEMP_RST_TH4 �Ĵ����ṹ���塣��ַƫ����:0x0E4����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor4�¶ȸ�λ���޼Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_rst_th4 : 10; /* bit[0-9]  : Tsensor4�¶ȸ�λ���� */
        unsigned int  reserved     : 22; /* bit[10-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_RST_TH4_UNION;
#endif
#define SOC_Tsensor_TEMP_RST_TH4_temp_rst_th4_START  (0)
#define SOC_Tsensor_TEMP_RST_TH4_temp_rst_th4_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_LAG4_UNION
 �ṹ˵��  : TEMP_LAG4 �Ĵ����ṹ���塣��ַƫ����:0x0E8����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor4�¶Ȼ��ͼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_lag4 : 7;  /* bit[0-6] : Tsensor4�¶Ȼ������� */
        unsigned int  reserved  : 25; /* bit[7-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_LAG4_UNION;
#endif
#define SOC_Tsensor_TEMP_LAG4_temp_lag4_START  (0)
#define SOC_Tsensor_TEMP_LAG4_temp_lag4_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_INT_MSK4_UNION
 �ṹ˵��  : TEMP_INT_MSK4 �Ĵ����ṹ���塣��ַƫ����:0x0EC����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor4�ж����μĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_int_msk4 : 1;  /* bit[0]   : Tsensor4�ж����ο���BIT��
                                                        1��������
                                                        0������ */
        unsigned int  reserved      : 31; /* bit[1-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_INT_MSK4_UNION;
#endif
#define SOC_Tsensor_TEMP_INT_MSK4_temp_int_msk4_START  (0)
#define SOC_Tsensor_TEMP_INT_MSK4_temp_int_msk4_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_INT_CLR4_UNION
 �ṹ˵��  : TEMP_INT_CLR4 �Ĵ����ṹ���塣��ַƫ����:0x0F0����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor4�ж�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_int_clr4 : 1;  /* bit[0]   : Tsensor4�ж��������BIT��
                                                        1�����RAW��MSK�ж�
                                                        0������ */
        unsigned int  reserved      : 31; /* bit[1-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_INT_CLR4_UNION;
#endif
#define SOC_Tsensor_TEMP_INT_CLR4_temp_int_clr4_START  (0)
#define SOC_Tsensor_TEMP_INT_CLR4_temp_int_clr4_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_RST_MSK4_UNION
 �ṹ˵��  : TEMP_RST_MSK4 �Ĵ����ṹ���塣��ַƫ����:0x0F4����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor4��λ���μĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_rst_msk4 : 1;  /* bit[0]   : Tsensor4��λ���ο���BIT��
                                                        1��������
                                                        0������ */
        unsigned int  reserved      : 31; /* bit[1-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_RST_MSK4_UNION;
#endif
#define SOC_Tsensor_TEMP_RST_MSK4_temp_rst_msk4_START  (0)
#define SOC_Tsensor_TEMP_RST_MSK4_temp_rst_msk4_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_RAWINT4_UNION
 �ṹ˵��  : TEMP_RAWINT4 �Ĵ����ṹ���塣��ַƫ����:0x0F8����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor4ԭʼ�жϼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_rawint4 : 1;  /* bit[0]   : Tsensor4ԭʼ�жϣ�
                                                       1�����ж�
                                                       0�����ж� */
        unsigned int  reserved     : 31; /* bit[1-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_RAWINT4_UNION;
#endif
#define SOC_Tsensor_TEMP_RAWINT4_temp_rawint4_START  (0)
#define SOC_Tsensor_TEMP_RAWINT4_temp_rawint4_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_MSKINT4_UNION
 �ṹ˵��  : TEMP_MSKINT4 �Ĵ����ṹ���塣��ַƫ����:0x0FC����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor4�����жϼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp_mskint4 : 1;  /* bit[0]   : Tsensor4�����жϣ�
                                                       1�����ж�
                                                       0�����ж� */
        unsigned int  reserved     : 31; /* bit[1-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_MSKINT4_UNION;
#endif
#define SOC_Tsensor_TEMP_MSKINT4_temp_mskint4_START  (0)
#define SOC_Tsensor_TEMP_MSKINT4_temp_mskint4_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_SOFTCTRL1_UNION
 �ṹ˵��  : TEMP_SOFTCTRL1 �Ĵ����ṹ���塣��ַƫ����:0x100����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor1������ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sel_soft1      : 1;  /* bit[0]    : Tsensor1�������ѡ��
                                                          1���������
                                                          0��״̬������ */
        unsigned int  temp_en1_soft  : 1;  /* bit[1]    : Tsensor1�������ʹ�ܣ�
                                                          1��ʹ��
                                                          0����ʹ�� */
        unsigned int  ct_sel1_soft   : 2;  /* bit[2-3]  : Tsensor1�������ת�����ʣ�
                                                          00����0.512ms
                                                          01����0.256ms
                                                          10����1.024ms
                                                          11����2.048ms */
        unsigned int  test1_soft     : 8;  /* bit[4-11] : Tsensor1�������ͨ��ѡ��ֻ�����3bit����
                                                          000��local sensor ��default�� */
        unsigned int  calib1_soft    : 1;  /* bit[12]   : Tsensor1���У׼ʹ��λ
                                                          1'b1��������У׼�㷨
                                                          1'b0������У׼�㷨��Ĭ�ϣ� */
        unsigned int  calib1_en_soft : 1;  /* bit[13]   : ���ʹ��λ��ʹ�ܺ��ܹ�ͨ��VCALIB1���е�ѹ��ʽУ׼��
                                                          1'b0:disable
                                                          1'b1:��ʾenable
                                                          ȱʡΪ��0�������ߵ�ƽ0.8V�� */
        unsigned int  reserved       : 18; /* bit[14-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_SOFTCTRL1_UNION;
#endif
#define SOC_Tsensor_TEMP_SOFTCTRL1_sel_soft1_START       (0)
#define SOC_Tsensor_TEMP_SOFTCTRL1_sel_soft1_END         (0)
#define SOC_Tsensor_TEMP_SOFTCTRL1_temp_en1_soft_START   (1)
#define SOC_Tsensor_TEMP_SOFTCTRL1_temp_en1_soft_END     (1)
#define SOC_Tsensor_TEMP_SOFTCTRL1_ct_sel1_soft_START    (2)
#define SOC_Tsensor_TEMP_SOFTCTRL1_ct_sel1_soft_END      (3)
#define SOC_Tsensor_TEMP_SOFTCTRL1_test1_soft_START      (4)
#define SOC_Tsensor_TEMP_SOFTCTRL1_test1_soft_END        (11)
#define SOC_Tsensor_TEMP_SOFTCTRL1_calib1_soft_START     (12)
#define SOC_Tsensor_TEMP_SOFTCTRL1_calib1_soft_END       (12)
#define SOC_Tsensor_TEMP_SOFTCTRL1_calib1_en_soft_START  (13)
#define SOC_Tsensor_TEMP_SOFTCTRL1_calib1_en_soft_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP1_SOFT_UNION
 �ṹ˵��  : TEMP1_SOFT �Ĵ����ṹ���塣��ַƫ����:0x104����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor1������Ƽ�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp1_soft : 10; /* bit[0-9]  : Tsensor1��������¶ȼ�����Ĵ��� */
        unsigned int  reserved   : 22; /* bit[10-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP1_SOFT_UNION;
#endif
#define SOC_Tsensor_TEMP1_SOFT_temp1_soft_START  (0)
#define SOC_Tsensor_TEMP1_SOFT_temp1_soft_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_SOFTCTRL2_UNION
 �ṹ˵��  : TEMP_SOFTCTRL2 �Ĵ����ṹ���塣��ַƫ����:0x108����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor2������ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sel_soft2      : 1;  /* bit[0]    : Tsensor2�������ѡ��
                                                          1���������
                                                          0��״̬������ */
        unsigned int  temp_en2_soft  : 1;  /* bit[1]    : Tsensor2�������ʹ�ܣ�
                                                          1��ʹ��
                                                          0����ʹ�� */
        unsigned int  ct_sel2_soft   : 2;  /* bit[2-3]  : Tsensor2�������ת�����ʣ�
                                                          00����0.512ms
                                                          01����0.256ms
                                                          10����1.024ms
                                                          11����2.048ms */
        unsigned int  test2_soft     : 8;  /* bit[4-11] : Tsensor2�������ͨ��ѡ��ֻ�����3bit����
                                                          000��local sensor ��default�� */
        unsigned int  calib2_soft    : 1;  /* bit[12]   : Tsensor2У׼ʹ��λ
                                                          1'b1��������У׼�㷨
                                                          1'b0������У׼�㷨��Ĭ�ϣ� */
        unsigned int  calib2_en_soft : 1;  /* bit[13]   : ���ʹ��λ��ʹ�ܺ��ܹ�ͨ��VCALIB1���е�ѹ��ʽУ׼��
                                                          1'b0:disable
                                                          1'b1:��ʾenable
                                                          ȱʡΪ��0�������ߵ�ƽ0.8V�� */
        unsigned int  reserved       : 18; /* bit[14-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_SOFTCTRL2_UNION;
#endif
#define SOC_Tsensor_TEMP_SOFTCTRL2_sel_soft2_START       (0)
#define SOC_Tsensor_TEMP_SOFTCTRL2_sel_soft2_END         (0)
#define SOC_Tsensor_TEMP_SOFTCTRL2_temp_en2_soft_START   (1)
#define SOC_Tsensor_TEMP_SOFTCTRL2_temp_en2_soft_END     (1)
#define SOC_Tsensor_TEMP_SOFTCTRL2_ct_sel2_soft_START    (2)
#define SOC_Tsensor_TEMP_SOFTCTRL2_ct_sel2_soft_END      (3)
#define SOC_Tsensor_TEMP_SOFTCTRL2_test2_soft_START      (4)
#define SOC_Tsensor_TEMP_SOFTCTRL2_test2_soft_END        (11)
#define SOC_Tsensor_TEMP_SOFTCTRL2_calib2_soft_START     (12)
#define SOC_Tsensor_TEMP_SOFTCTRL2_calib2_soft_END       (12)
#define SOC_Tsensor_TEMP_SOFTCTRL2_calib2_en_soft_START  (13)
#define SOC_Tsensor_TEMP_SOFTCTRL2_calib2_en_soft_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP2_SOFT_UNION
 �ṹ˵��  : TEMP2_SOFT �Ĵ����ṹ���塣��ַƫ����:0x10C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor2������Ƽ�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp2_soft : 10; /* bit[0-9]  : Tsensor2��������¶ȼ�����Ĵ��� */
        unsigned int  reserved   : 22; /* bit[10-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP2_SOFT_UNION;
#endif
#define SOC_Tsensor_TEMP2_SOFT_temp2_soft_START  (0)
#define SOC_Tsensor_TEMP2_SOFT_temp2_soft_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_SOFTCTRL3_UNION
 �ṹ˵��  : TEMP_SOFTCTRL3 �Ĵ����ṹ���塣��ַƫ����:0x110����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor3������ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sel_soft3      : 1;  /* bit[0]    : Tsensor3�������ѡ��
                                                          1���������
                                                          0��״̬������ */
        unsigned int  temp_en3_soft  : 1;  /* bit[1]    : Tsensor3�������ʹ�ܣ�
                                                          1��ʹ��
                                                          0����ʹ�� */
        unsigned int  ct_sel3_soft   : 2;  /* bit[2-3]  : Tsensor3�������ת�����ʣ�
                                                          00����0.512ms
                                                          01����0.256ms
                                                          10����1.024ms
                                                          11����2.048ms */
        unsigned int  test3_soft     : 8;  /* bit[4-11] : Tsensor3�������ͨ��ѡ��ֻ�����3bit����
                                                          000��local sensor ��default�� */
        unsigned int  calib3_soft    : 1;  /* bit[12]   : Tsensor3У׼ʹ��λ
                                                          1'b1��������У׼�㷨
                                                          1'b0������У׼�㷨��Ĭ�ϣ� */
        unsigned int  calib3_en_soft : 1;  /* bit[13]   : ���ʹ��λ��ʹ�ܺ��ܹ�ͨ��VCALIB1���е�ѹ��ʽУ׼��
                                                          1'b0:disable
                                                          1'b1:��ʾenable
                                                          ȱʡΪ��0�������ߵ�ƽ0.8V�� */
        unsigned int  reserved       : 18; /* bit[14-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_SOFTCTRL3_UNION;
#endif
#define SOC_Tsensor_TEMP_SOFTCTRL3_sel_soft3_START       (0)
#define SOC_Tsensor_TEMP_SOFTCTRL3_sel_soft3_END         (0)
#define SOC_Tsensor_TEMP_SOFTCTRL3_temp_en3_soft_START   (1)
#define SOC_Tsensor_TEMP_SOFTCTRL3_temp_en3_soft_END     (1)
#define SOC_Tsensor_TEMP_SOFTCTRL3_ct_sel3_soft_START    (2)
#define SOC_Tsensor_TEMP_SOFTCTRL3_ct_sel3_soft_END      (3)
#define SOC_Tsensor_TEMP_SOFTCTRL3_test3_soft_START      (4)
#define SOC_Tsensor_TEMP_SOFTCTRL3_test3_soft_END        (11)
#define SOC_Tsensor_TEMP_SOFTCTRL3_calib3_soft_START     (12)
#define SOC_Tsensor_TEMP_SOFTCTRL3_calib3_soft_END       (12)
#define SOC_Tsensor_TEMP_SOFTCTRL3_calib3_en_soft_START  (13)
#define SOC_Tsensor_TEMP_SOFTCTRL3_calib3_en_soft_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP3_SOFT_UNION
 �ṹ˵��  : TEMP3_SOFT �Ĵ����ṹ���塣��ַƫ����:0x114����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor3������Ƽ�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp3_soft : 10; /* bit[0-9]  : Tsensor3��������¶ȼ�����Ĵ��� */
        unsigned int  reserved   : 22; /* bit[10-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP3_SOFT_UNION;
#endif
#define SOC_Tsensor_TEMP3_SOFT_temp3_soft_START  (0)
#define SOC_Tsensor_TEMP3_SOFT_temp3_soft_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP_SOFTCTRL4_UNION
 �ṹ˵��  : TEMP_SOFTCTRL4 �Ĵ����ṹ���塣��ַƫ����:0x118����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor4������ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sel_soft4      : 1;  /* bit[0]    : Tsensor4�������ѡ��
                                                          1���������
                                                          0��״̬������ */
        unsigned int  temp_en4_soft  : 1;  /* bit[1]    : Tsensor4�������ʹ�ܣ�
                                                          1��ʹ��
                                                          0����ʹ�� */
        unsigned int  ct_sel4_soft   : 2;  /* bit[2-3]  : Tsensor4�������ת�����ʣ�
                                                          00����0.512ms
                                                          01����0.256ms
                                                          10����1.024ms
                                                          11����2.048ms */
        unsigned int  test4_soft     : 8;  /* bit[4-11] : Tsensor4�������ͨ��ѡ��ֻ�����3bit����
                                                          000��local sensor ��default�� */
        unsigned int  calib4_soft    : 1;  /* bit[12]   : Tsensor4У׼ʹ��λ
                                                          1'b1��������У׼�㷨
                                                          1'b0������У׼�㷨��Ĭ�ϣ� */
        unsigned int  calib4_en_soft : 1;  /* bit[13]   : ���ʹ��λ��ʹ�ܺ��ܹ�ͨ��VCALIB1���е�ѹ��ʽУ׼��
                                                          1'b0:disable
                                                          1'b1:��ʾenable
                                                          ȱʡΪ��0�������ߵ�ƽ0.8V�� */
        unsigned int  reserved       : 18; /* bit[14-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP_SOFTCTRL4_UNION;
#endif
#define SOC_Tsensor_TEMP_SOFTCTRL4_sel_soft4_START       (0)
#define SOC_Tsensor_TEMP_SOFTCTRL4_sel_soft4_END         (0)
#define SOC_Tsensor_TEMP_SOFTCTRL4_temp_en4_soft_START   (1)
#define SOC_Tsensor_TEMP_SOFTCTRL4_temp_en4_soft_END     (1)
#define SOC_Tsensor_TEMP_SOFTCTRL4_ct_sel4_soft_START    (2)
#define SOC_Tsensor_TEMP_SOFTCTRL4_ct_sel4_soft_END      (3)
#define SOC_Tsensor_TEMP_SOFTCTRL4_test4_soft_START      (4)
#define SOC_Tsensor_TEMP_SOFTCTRL4_test4_soft_END        (11)
#define SOC_Tsensor_TEMP_SOFTCTRL4_calib4_soft_START     (12)
#define SOC_Tsensor_TEMP_SOFTCTRL4_calib4_soft_END       (12)
#define SOC_Tsensor_TEMP_SOFTCTRL4_calib4_en_soft_START  (13)
#define SOC_Tsensor_TEMP_SOFTCTRL4_calib4_en_soft_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_Tsensor_TEMP4_SOFT_UNION
 �ṹ˵��  : TEMP4_SOFT �Ĵ����ṹ���塣��ַƫ����:0x11C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Tsensor4������Ƽ�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  temp4_soft : 10; /* bit[0-9]  : Tsensor4��������¶ȼ�����Ĵ��� */
        unsigned int  reserved   : 22; /* bit[10-31]: ����λ */
    } reg;
} SOC_Tsensor_TEMP4_SOFT_UNION;
#endif
#define SOC_Tsensor_TEMP4_SOFT_temp4_soft_START  (0)
#define SOC_Tsensor_TEMP4_SOFT_temp4_soft_END    (9)






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

#endif /* end of soc_tsensor_interface.h */
