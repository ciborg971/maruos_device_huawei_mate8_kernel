/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_gpio_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:20:42
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_GPIO.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_GPIO_INTERFACE_H__
#define __SOC_GPIO_INTERFACE_H__

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
/* �Ĵ���˵�������ݼĴ�����
   λ����UNION�ṹ:  SOC_GPIO_GPIODATA_UNION */
#define SOC_GPIO_GPIODATA_ADDR(base)                  ((base) + (0x000~0x3fc))

/* �Ĵ���˵����������ƼĴ�����
   λ����UNION�ṹ:  SOC_GPIO_GPIODIR_UNION */
#define SOC_GPIO_GPIODIR_ADDR(base)                   ((base) + (0x400))

/* �Ĵ���˵�������ػ��ƽ������ʽѡ��Ĵ�����
   λ����UNION�ṹ:  SOC_GPIO_GPIOIS_UNION */
#define SOC_GPIO_GPIOIS_ADDR(base)                    ((base) + (0x404))

/* �Ĵ���˵�������ػ�˫�ش�����ʽ�Ĵ�����
   λ����UNION�ṹ:  SOC_GPIO_GPIOIBE_UNION */
#define SOC_GPIO_GPIOIBE_ADDR(base)                   ((base) + (0x408))

/* �Ĵ���˵��������/���ػ�ߵ�ƽ/�͵�ƽѡ��Ĵ�����
   λ����UNION�ṹ:  SOC_GPIO_GPIOIEV_UNION */
#define SOC_GPIO_GPIOIEV_ADDR(base)                   ((base) + (0x40C))

/* �Ĵ���˵�����ж����μĴ�����
   λ����UNION�ṹ:  SOC_GPIO_GPIOIE_UNION */
#define SOC_GPIO_GPIOIE_ADDR(base)                    ((base) + (0x410))

/* �Ĵ���˵�����ж����μĴ�����
   λ����UNION�ṹ:  SOC_GPIO_GPIOIE2_UNION */
#define SOC_GPIO_GPIOIE2_ADDR(base)                   ((base) + (0x500))

/* �Ĵ���˵�����ж����μĴ�����
   λ����UNION�ṹ:  SOC_GPIO_GPIOIE3_UNION */
#define SOC_GPIO_GPIOIE3_ADDR(base)                   ((base) + (0x504))

/* �Ĵ���˵����ԭʼ�ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_GPIO_GPIORIS_UNION */
#define SOC_GPIO_GPIORIS_ADDR(base)                   ((base) + (0x414))

/* �Ĵ���˵�������κ��ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_GPIO_GPIOMIS_UNION */
#define SOC_GPIO_GPIOMIS_ADDR(base)                   ((base) + (0x418))

/* �Ĵ���˵�������κ��ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_GPIO_GPIOMIS2_UNION */
#define SOC_GPIO_GPIOMIS2_ADDR(base)                  ((base) + (0x530))

/* �Ĵ���˵�������κ��ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_GPIO_GPIOMIS3_UNION */
#define SOC_GPIO_GPIOMIS3_ADDR(base)                  ((base) + (0x534))

/* �Ĵ���˵�����ж�����Ĵ�����
   λ����UNION�ṹ:  SOC_GPIO_GPIOIC_UNION */
#define SOC_GPIO_GPIOIC_ADDR(base)                    ((base) + (0x41C))

/* �Ĵ���˵����Ӳ/���ģʽ���ƼĴ�����
   λ����UNION�ṹ:  SOC_GPIO_GPIOAFSEL_UNION */
#define SOC_GPIO_GPIOAFSEL_ADDR(base)                 ((base) + (0x420))





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
 �ṹ��    : SOC_GPIO_GPIODATA_UNION
 �ṹ˵��  : GPIODATA �Ĵ����ṹ���塣��ַƫ����:0x000~0x3fc����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���ݼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  data_register : 8;  /* bit[0-7] : ����/������ݡ�
                                                        ͨ���ԼĴ�����ַ�Ŀ��ƣ�����һ��ָ���ڶԸ�������λ���е��������� */
        unsigned int  reserved      : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_GPIO_GPIODATA_UNION;
#endif
#define SOC_GPIO_GPIODATA_data_register_START  (0)
#define SOC_GPIO_GPIODATA_data_register_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_GPIO_GPIODIR_UNION
 �ṹ˵��  : GPIODIR �Ĵ����ṹ���塣��ַƫ����:0x400����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  data_direct : 8;  /* bit[0-7] : ���ݷ���
                                                      0�����룻
                                                      1������� */
        unsigned int  reserved    : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_GPIO_GPIODIR_UNION;
#endif
#define SOC_GPIO_GPIODIR_data_direct_START  (0)
#define SOC_GPIO_GPIODIR_data_direct_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_GPIO_GPIOIS_UNION
 �ṹ˵��  : GPIOIS �Ĵ����ṹ���塣��ַƫ����:0x404����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���ػ��ƽ������ʽѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  interrupt_sense : 8;  /* bit[0-7] : ���ػ����������ʽѡ��
                                                          0�����ش����жϣ�
                                                          1����ƽ�����жϡ� */
        unsigned int  reserved        : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_GPIO_GPIOIS_UNION;
#endif
#define SOC_GPIO_GPIOIS_interrupt_sense_START  (0)
#define SOC_GPIO_GPIOIS_interrupt_sense_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_GPIO_GPIOIBE_UNION
 �ṹ˵��  : GPIOIBE �Ĵ����ṹ���塣��ַƫ����:0x408����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���ػ�˫�ش�����ʽ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  interrupt_sense : 8;  /* bit[0-7] : ���ػ�˫�ش�����ʽѡ��
                                                          0�����ش����������ش��������½��ش����ɼĴ���GPIOIEV������
                                                          1���������½��ض����Դ����жϡ� */
        unsigned int  reserved        : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_GPIO_GPIOIBE_UNION;
#endif
#define SOC_GPIO_GPIOIBE_interrupt_sense_START  (0)
#define SOC_GPIO_GPIOIBE_interrupt_sense_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_GPIO_GPIOIEV_UNION
 �ṹ˵��  : GPIOIEV �Ĵ����ṹ���塣��ַƫ����:0x40C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����/���ػ�ߵ�ƽ/�͵�ƽѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  interrupt_event : 8;  /* bit[0-7] : ����/���ػ�ߵ�ƽ/�͵�ƽѡ��
                                                          0���½��ػ�͵�ƽ�����жϣ�
                                                          1�������ػ�ߵ�ƽ�����жϡ� */
        unsigned int  reserved        : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_GPIO_GPIOIEV_UNION;
#endif
#define SOC_GPIO_GPIOIEV_interrupt_event_START  (0)
#define SOC_GPIO_GPIOIEV_interrupt_event_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_GPIO_GPIOIE_UNION
 �ṹ˵��  : GPIOIE �Ĵ����ṹ���塣��ַƫ����:0x410����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж����μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  interrupt_mask : 8;  /* bit[0-7] : �ж����Ρ�
                                                         0��������Ӧ�ܽŵ��жϣ�
                                                         1��ʹ����Ӧ�ܽŵ��жϡ� */
        unsigned int  reserved       : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_GPIO_GPIOIE_UNION;
#endif
#define SOC_GPIO_GPIOIE_interrupt_mask_START  (0)
#define SOC_GPIO_GPIOIE_interrupt_mask_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_GPIO_GPIOIE2_UNION
 �ṹ˵��  : GPIOIE2 �Ĵ����ṹ���塣��ַƫ����:0x500����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж����μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  interrupt2_mask : 8;  /* bit[0-7] : �ж����Ρ�
                                                          0��������Ӧ�ܽŵ��жϣ�
                                                          1��ʹ����Ӧ�ܽŵ��жϡ� */
        unsigned int  reserved        : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_GPIO_GPIOIE2_UNION;
#endif
#define SOC_GPIO_GPIOIE2_interrupt2_mask_START  (0)
#define SOC_GPIO_GPIOIE2_interrupt2_mask_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_GPIO_GPIOIE3_UNION
 �ṹ˵��  : GPIOIE3 �Ĵ����ṹ���塣��ַƫ����:0x504����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж����μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  interrupt3_mask : 8;  /* bit[0-7] : �ж����Ρ�
                                                          0��������Ӧ�ܽŵ��жϣ�
                                                          1��ʹ����Ӧ�ܽŵ��жϡ� */
        unsigned int  reserved        : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_GPIO_GPIOIE3_UNION;
#endif
#define SOC_GPIO_GPIOIE3_interrupt3_mask_START  (0)
#define SOC_GPIO_GPIOIE3_interrupt3_mask_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_GPIO_GPIORIS_UNION
 �ṹ˵��  : GPIORIS �Ĵ����ṹ���塣��ַƫ����:0x414����ֵ:0x00000000�����:32
 �Ĵ���˵��: ԭʼ�ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  raw_interrupt_status : 8;  /* bit[0-7] : ԭʼ�ж�״̬��
                                                               0����λ��Ӧ�Ĺܽ�û�д����жϣ�
                                                               1����λ��Ӧ�Ĺܽ��Ѿ������жϡ� */
        unsigned int  reserved             : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_GPIO_GPIORIS_UNION;
#endif
#define SOC_GPIO_GPIORIS_raw_interrupt_status_START  (0)
#define SOC_GPIO_GPIORIS_raw_interrupt_status_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_GPIO_GPIOMIS_UNION
 �ṹ˵��  : GPIOMIS �Ĵ����ṹ���塣��ַƫ����:0x418����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���κ��ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  masked_interrupt_status : 8;  /* bit[0-7] : ���κ��ж�״̬��
                                                                  0����λ��Ӧ�Ĺܽ�û�д����жϣ�
                                                                  1����λ��Ӧ�Ĺܽ��Ѿ������жϡ� */
        unsigned int  reserved                : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_GPIO_GPIOMIS_UNION;
#endif
#define SOC_GPIO_GPIOMIS_masked_interrupt_status_START  (0)
#define SOC_GPIO_GPIOMIS_masked_interrupt_status_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_GPIO_GPIOMIS2_UNION
 �ṹ˵��  : GPIOMIS2 �Ĵ����ṹ���塣��ַƫ����:0x530����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���κ��ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  masked_interrupt2_status : 8;  /* bit[0-7] : ���κ��ж�״̬��
                                                                   0����λ��Ӧ�Ĺܽ�û�д����жϣ�
                                                                   1����λ��Ӧ�Ĺܽ��Ѿ������жϡ� */
        unsigned int  reserved                 : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_GPIO_GPIOMIS2_UNION;
#endif
#define SOC_GPIO_GPIOMIS2_masked_interrupt2_status_START  (0)
#define SOC_GPIO_GPIOMIS2_masked_interrupt2_status_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_GPIO_GPIOMIS3_UNION
 �ṹ˵��  : GPIOMIS3 �Ĵ����ṹ���塣��ַƫ����:0x534����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���κ��ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  masked_interrupt3_status : 8;  /* bit[0-7] : ���κ��ж�״̬��
                                                                   0����λ��Ӧ�Ĺܽ�û�д����жϣ�
                                                                   1����λ��Ӧ�Ĺܽ��Ѿ������жϡ� */
        unsigned int  reserved                 : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_GPIO_GPIOMIS3_UNION;
#endif
#define SOC_GPIO_GPIOMIS3_masked_interrupt3_status_START  (0)
#define SOC_GPIO_GPIOMIS3_masked_interrupt3_status_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_GPIO_GPIOIC_UNION
 �ṹ˵��  : GPIOIC �Ĵ����ṹ���塣��ַƫ����:0x41C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  interrupt_status_clear : 8;  /* bit[0-7] : �ж������
                                                                 0�����ж���Ӱ�죻
                                                                 1�������Ӧ�жϡ� */
        unsigned int  reserved               : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_GPIO_GPIOIC_UNION;
#endif
#define SOC_GPIO_GPIOIC_interrupt_status_clear_START  (0)
#define SOC_GPIO_GPIOIC_interrupt_status_clear_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_GPIO_GPIOAFSEL_UNION
 �ṹ˵��  : GPIOAFSEL �Ĵ����ṹ���塣��ַƫ����:0x420����ֵ:0x00000000�����:32
 �Ĵ���˵��: Ӳ/���ģʽ���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode_control_select_register : 8;  /* bit[0-7] : ����ģʽѡ��
                                                                       0���������ģʽ��
                                                                       1��Ӳ������ģʽ�� */
        unsigned int  reserved                     : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_GPIO_GPIOAFSEL_UNION;
#endif
#define SOC_GPIO_GPIOAFSEL_mode_control_select_register_START  (0)
#define SOC_GPIO_GPIOAFSEL_mode_control_select_register_END    (7)






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

#endif /* end of soc_gpio_interface.h */
