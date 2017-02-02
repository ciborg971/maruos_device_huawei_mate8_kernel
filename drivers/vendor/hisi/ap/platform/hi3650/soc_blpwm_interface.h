/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_blpwm_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:18:50
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_BLPWM.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_BLPWM_INTERFACE_H__
#define __SOC_BLPWM_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) register_blpwm
 ****************************************************************************/
/* �Ĵ���˵����������ƼĴ�����
   λ����UNION�ṹ:  SOC_BLPWM_IN_CTRL_UNION */
#define SOC_BLPWM_IN_CTRL_ADDR(base)                  ((base) + (0x000))

/* �Ĵ���˵�����������ʱ�ӷ�Ƶ�Ĵ�����
   λ����UNION�ṹ:  SOC_BLPWM_IN_DIV_UNION */
#define SOC_BLPWM_IN_DIV_ADDR(base)                   ((base) + (0x004))

/* �Ĵ���˵������������Ĵ�����
   λ����UNION�ṹ:  SOC_BLPWM_IN_NUM_UNION */
#define SOC_BLPWM_IN_NUM_ADDR(base)                   ((base) + (0x008))

/* �Ĵ���˵��������debug�Ĵ�����
   λ����UNION�ṹ:  SOC_BLPWM_IN_NUM_BAK_UNION */
#define SOC_BLPWM_IN_NUM_BAK_ADDR(base)               ((base) + (0x00C))

/* �Ĵ���˵��������������ֵ�Ĵ�����
   λ����UNION�ṹ:  SOC_BLPWM_CNT_MAX_UNION */
#define SOC_BLPWM_CNT_MAX_ADDR(base)                  ((base) + (0x010))

/* �Ĵ���˵���������ֵ������ֵ�Ĵ�����
   λ����UNION�ṹ:  SOC_BLPWM_INTR_DIFF_UNION */
#define SOC_BLPWM_INTR_DIFF_ADDR(base)                ((base) + (0x014))

/* �Ĵ���˵�����ж����μĴ�����
   λ����UNION�ṹ:  SOC_BLPWM_INTR_CTRL_UNION */
#define SOC_BLPWM_INTR_CTRL_ADDR(base)                ((base) + (0x018))

/* �Ĵ���˵�����ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_BLPWM_IN_INTR_UNION */
#define SOC_BLPWM_IN_INTR_ADDR(base)                  ((base) + (0x01C))

/* �Ĵ���˵�����ж�����Ĵ���
   λ����UNION�ṹ:  SOC_BLPWM_INTR_CLEAR_UNION */
#define SOC_BLPWM_INTR_CLEAR_ADDR(base)               ((base) + (0x020))

/* �Ĵ���˵�������ģʽ�Ĵ�����
   λ����UNION�ṹ:  SOC_BLPWM_OUT_CTRL_UNION */
#define SOC_BLPWM_OUT_CTRL_ADDR(base)                 ((base) + (0x100))

/* �Ĵ���˵�����������ʱ�ӷ�Ƶ�ȼĴ�����
   λ����UNION�ṹ:  SOC_BLPWM_OUT_DIV_UNION */
#define SOC_BLPWM_OUT_DIV_ADDR(base)                  ((base) + (0x104))

/* �Ĵ���˵�������PWM�ź����üĴ�����
   λ����UNION�ṹ:  SOC_BLPWM_OUT_CFG_UNION */
#define SOC_BLPWM_OUT_CFG_ADDR(base)                  ((base) + (0x108))

/* �Ĵ���˵�������PWM�źŷ���0���üĴ�����
   λ����UNION�ṹ:  SOC_BLPWM_GROUP0_CFG_UNION */
#define SOC_BLPWM_GROUP0_CFG_ADDR(base)               ((base) + (0x10C))

/* �Ĵ���˵�������PWM�źŷ���1���üĴ�����
   λ����UNION�ṹ:  SOC_BLPWM_GROUP1_CFG_UNION */
#define SOC_BLPWM_GROUP1_CFG_ADDR(base)               ((base) + (0x110))

/* �Ĵ���˵�������PWM�źŷ���2���üĴ�����
   λ����UNION�ṹ:  SOC_BLPWM_GROUP2_CFG_UNION */
#define SOC_BLPWM_GROUP2_CFG_ADDR(base)               ((base) + (0x114))

/* �Ĵ���˵�������PWM�źŷ���3���üĴ�����
   λ����UNION�ṹ:  SOC_BLPWM_GROUP3_CFG_UNION */
#define SOC_BLPWM_GROUP3_CFG_ADDR(base)               ((base) + (0x118))

/* �Ĵ���˵�������PWM�źŷ���4���üĴ�����
   λ����UNION�ṹ:  SOC_BLPWM_GROUP4_CFG_UNION */
#define SOC_BLPWM_GROUP4_CFG_ADDR(base)               ((base) + (0x11C))

/* �Ĵ���˵�������PWM�źŷ���5���üĴ�����
   λ����UNION�ṹ:  SOC_BLPWM_GROUP5_CFG_UNION */
#define SOC_BLPWM_GROUP5_CFG_ADDR(base)               ((base) + (0x120))

/* �Ĵ���˵�������PWM�źŷ���6���üĴ�����
   λ����UNION�ṹ:  SOC_BLPWM_GROUP6_CFG_UNION */
#define SOC_BLPWM_GROUP6_CFG_ADDR(base)               ((base) + (0x124))

/* �Ĵ���˵�������PWM�źŷ���7���üĴ�����
   λ����UNION�ṹ:  SOC_BLPWM_GROUP7_CFG_UNION */
#define SOC_BLPWM_GROUP7_CFG_ADDR(base)               ((base) + (0x128))

/* �Ĵ���˵�����������״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_BLPWM_OUT_STATUS_UNION */
#define SOC_BLPWM_OUT_STATUS_ADDR(base)               ((base) + (0x130))

/* �Ĵ���˵��������״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_BLPWM_GROUP_STATUS_UNION */
#define SOC_BLPWM_GROUP_STATUS_ADDR(base)             ((base) + (0x134))





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
                     (1/1) register_blpwm
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_BLPWM_IN_CTRL_UNION
 �ṹ˵��  : IN_CTRL �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cnt_enable    : 1;  /* bit[0]    : ����ʹ�ܣ�1ʹ�ܼ�����0ֹͣ������ */
        unsigned int  reserved_0    : 15; /* bit[1-15] : ������ */
        unsigned int  input_reverse : 1;  /* bit[16]   : ���뷴��ʹ�ܣ��������cabc_pwm�ź�Ϊ����Ч�� */
        unsigned int  reserved_1    : 15; /* bit[17-31]: ������ */
    } reg;
} SOC_BLPWM_IN_CTRL_UNION;
#endif
#define SOC_BLPWM_IN_CTRL_cnt_enable_START     (0)
#define SOC_BLPWM_IN_CTRL_cnt_enable_END       (0)
#define SOC_BLPWM_IN_CTRL_input_reverse_START  (16)
#define SOC_BLPWM_IN_CTRL_input_reverse_END    (16)


/*****************************************************************************
 �ṹ��    : SOC_BLPWM_IN_DIV_UNION
 �ṹ˵��  : IN_DIV �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������ʱ�ӷ�Ƶ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cnt_div  : 8;  /* bit[0-7] : ����ʱ�ӷ�Ƶ�ȣ�0Ϊ1��Ƶ��1Ϊ2��Ƶ���Դ����ơ� */
        unsigned int  reserved : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_BLPWM_IN_DIV_UNION;
#endif
#define SOC_BLPWM_IN_DIV_cnt_div_START   (0)
#define SOC_BLPWM_IN_DIV_cnt_div_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_BLPWM_IN_NUM_UNION
 �ṹ˵��  : IN_NUM �Ĵ����ṹ���塣��ַƫ����:0x008����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��������Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cnt_low  : 16; /* bit[0-15] : ��������Ĵ���, �ս��������ڵĵ͵�ƽ�������� */
        unsigned int  cnt_high : 16; /* bit[16-31]: ��������Ĵ���, �ս��������ڵĸߵ�ƽ�������� */
    } reg;
} SOC_BLPWM_IN_NUM_UNION;
#endif
#define SOC_BLPWM_IN_NUM_cnt_low_START   (0)
#define SOC_BLPWM_IN_NUM_cnt_low_END     (15)
#define SOC_BLPWM_IN_NUM_cnt_high_START  (16)
#define SOC_BLPWM_IN_NUM_cnt_high_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_BLPWM_IN_NUM_BAK_UNION
 �ṹ˵��  : IN_NUM_BAK �Ĵ����ṹ���塣��ַƫ����:0x00C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����debug�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cnt_low_debug  : 16; /* bit[0-15] : ����debug�Ĵ���,��һ��pwm���ڵĵ͵�ƽ�������� */
        unsigned int  cnt_high_debug : 16; /* bit[16-31]: ����debug�Ĵ���,��һ��pwm���ڵĸߵ�ƽ�������� */
    } reg;
} SOC_BLPWM_IN_NUM_BAK_UNION;
#endif
#define SOC_BLPWM_IN_NUM_BAK_cnt_low_debug_START   (0)
#define SOC_BLPWM_IN_NUM_BAK_cnt_low_debug_END     (15)
#define SOC_BLPWM_IN_NUM_BAK_cnt_high_debug_START  (16)
#define SOC_BLPWM_IN_NUM_BAK_cnt_high_debug_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_BLPWM_CNT_MAX_UNION
 �ṹ˵��  : CNT_MAX �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: ����������ֵ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cnt_max  : 16; /* bit[0-15] : ���ļ���ֵ��������ֵ������ǰ�������л�����һ�顣 */
        unsigned int  reserved : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_BLPWM_CNT_MAX_UNION;
#endif
#define SOC_BLPWM_CNT_MAX_cnt_max_START   (0)
#define SOC_BLPWM_CNT_MAX_cnt_max_END     (15)


/*****************************************************************************
 �ṹ��    : SOC_BLPWM_INTR_DIFF_UNION
 �ṹ˵��  : INTR_DIFF �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����ֵ������ֵ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cnt_intr_diff : 16; /* bit[0-15] : ��ǰ�����μ���ֵ�ĸߵ�ƽ��ֵ�ﵽ����ֵʱ�������жϡ� */
        unsigned int  reserved      : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_BLPWM_INTR_DIFF_UNION;
#endif
#define SOC_BLPWM_INTR_DIFF_cnt_intr_diff_START  (0)
#define SOC_BLPWM_INTR_DIFF_cnt_intr_diff_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_BLPWM_INTR_CTRL_UNION
 �ṹ˵��  : INTR_CTRL �Ĵ����ṹ���塣��ַƫ����:0x018����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж����μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cnt_intr_mask : 1;  /* bit[0]   : �ж����Σ�Ϊ1ʱ���θ��жϡ� */
        unsigned int  reserved      : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_BLPWM_INTR_CTRL_UNION;
#endif
#define SOC_BLPWM_INTR_CTRL_cnt_intr_mask_START  (0)
#define SOC_BLPWM_INTR_CTRL_cnt_intr_mask_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_BLPWM_IN_INTR_UNION
 �ṹ˵��  : IN_INTR �Ĵ����ṹ���塣��ַƫ����:0x01C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cnt_raw_intr : 1;  /* bit[0]    : ԭʼ�жϣ�����Ч�� */
        unsigned int  reserved_0   : 15; /* bit[1-15] : ������ */
        unsigned int  cnt_intr     : 1;  /* bit[16]   : ���κ��жϣ�����Ч�� */
        unsigned int  reserved_1   : 15; /* bit[17-31]: ������ */
    } reg;
} SOC_BLPWM_IN_INTR_UNION;
#endif
#define SOC_BLPWM_IN_INTR_cnt_raw_intr_START  (0)
#define SOC_BLPWM_IN_INTR_cnt_raw_intr_END    (0)
#define SOC_BLPWM_IN_INTR_cnt_intr_START      (16)
#define SOC_BLPWM_IN_INTR_cnt_intr_END        (16)


/*****************************************************************************
 �ṹ��    : SOC_BLPWM_INTR_CLEAR_UNION
 �ṹ˵��  : INTR_CLEAR �Ĵ����ṹ���塣��ַƫ����:0x020����ֵ:0x0000�����:32
 �Ĵ���˵��: �ж�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cnt_intr_clear : 1;  /* bit[0]   : �ж�����Ĵ���������ж�ʱ�Ը�λд1���ж�������λ�Զ��ָ�Ϊ�㡣 */
        unsigned int  reserved       : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_BLPWM_INTR_CLEAR_UNION;
#endif
#define SOC_BLPWM_INTR_CLEAR_cnt_intr_clear_START  (0)
#define SOC_BLPWM_INTR_CLEAR_cnt_intr_clear_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_BLPWM_OUT_CTRL_UNION
 �ṹ˵��  : OUT_CTRL �Ĵ����ṹ���塣��ַƫ����:0x100����ֵ:0x00000004�����:32
 �Ĵ���˵��: ���ģʽ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gen_en      : 1;  /* bit[0]   : 0��ֹͣ��������źţ����bl_pwmΪ0.
                                                      1�����ʹ�ܣ�  */
        unsigned int  gen_mode    : 1;  /* bit[1]   : ���ģʽѡ��Ĵ�����
                                                      0����������ģʽ��
                                                      1��ֱͨģʽ�� */
        unsigned int  bypass_mode : 1;  /* bit[2]   : bypassģʽ�������Խ����벻ͨ������ģ��ֱ����Ϊbl_pwm�������λֵΪ1����gen_en=0��bypass_mode=1ʱ�����ģʽ�� */
        unsigned int  reserved    : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_BLPWM_OUT_CTRL_UNION;
#endif
#define SOC_BLPWM_OUT_CTRL_gen_en_START       (0)
#define SOC_BLPWM_OUT_CTRL_gen_en_END         (0)
#define SOC_BLPWM_OUT_CTRL_gen_mode_START     (1)
#define SOC_BLPWM_OUT_CTRL_gen_mode_END       (1)
#define SOC_BLPWM_OUT_CTRL_bypass_mode_START  (2)
#define SOC_BLPWM_OUT_CTRL_bypass_mode_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_BLPWM_OUT_DIV_UNION
 �ṹ˵��  : OUT_DIV �Ĵ����ṹ���塣��ַƫ����:0x104����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������ʱ�ӷ�Ƶ�ȼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gen_cnt_div : 8;  /* bit[0-7] : �������ʱ�ӷ�Ƶ�ȡ�0Ϊ1��Ƶ��1Ϊ2��Ƶ���Դ����ơ� */
        unsigned int  reserved    : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_BLPWM_OUT_DIV_UNION;
#endif
#define SOC_BLPWM_OUT_DIV_gen_cnt_div_START  (0)
#define SOC_BLPWM_OUT_DIV_gen_cnt_div_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_BLPWM_OUT_CFG_UNION
 �ṹ˵��  : OUT_CFG �Ĵ����ṹ���塣��ַƫ����:0x108����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���PWM�ź����üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  start_low  : 16; /* bit[0-15] : ���÷���ģʽ����ʼ�͵�ƽ��������Ϊ0ʱ��ʾһ��pwm�����ڲ������͵�ƽ�� */
        unsigned int  start_high : 16; /* bit[16-31]: ���÷���ģʽ����ʼ�ߵ�ƽ��������Ϊ0ʱ��ʾһ��pwm�����ڲ������ߵ�ƽ�� */
    } reg;
} SOC_BLPWM_OUT_CFG_UNION;
#endif
#define SOC_BLPWM_OUT_CFG_start_low_START   (0)
#define SOC_BLPWM_OUT_CFG_start_low_END     (15)
#define SOC_BLPWM_OUT_CFG_start_high_START  (16)
#define SOC_BLPWM_OUT_CFG_start_high_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_BLPWM_GROUP0_CFG_UNION
 �ṹ˵��  : GROUP0_CFG �Ĵ����ṹ���塣��ַƫ����:0x10C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���PWM�źŷ���0���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  group0_refresh_freq : 8;  /* bit[0-7]  : ˢ��Ƶ�ʣ���ÿ���ٸ�����ʹ����һ������ֵ��Ϊ0ʱ��ʾÿ��ֵ��ִ��һ�Σ�Ϊ1ʱ���Σ��Դ����ơ� */
        unsigned int  group0_step_times   : 8;  /* bit[8-15] : �����ļ�/��������0ʱΪ��һ�Σ�1ʱ�����Σ��Դ����ơ� */
        unsigned int  group0_step         : 15; /* bit[16-30]: ������15λ�з������� */
        unsigned int  group0_active       : 1;  /* bit[31]   : ��ʾ�Ƿ���б������ã�Ϊ0ʱ�����д�������ͺ����ķ���������ڳ�ʼʱ��ֻ�з���0�˼Ĵ�����Чʱ���Ż���з���Ӽ������á� */
    } reg;
} SOC_BLPWM_GROUP0_CFG_UNION;
#endif
#define SOC_BLPWM_GROUP0_CFG_group0_refresh_freq_START  (0)
#define SOC_BLPWM_GROUP0_CFG_group0_refresh_freq_END    (7)
#define SOC_BLPWM_GROUP0_CFG_group0_step_times_START    (8)
#define SOC_BLPWM_GROUP0_CFG_group0_step_times_END      (15)
#define SOC_BLPWM_GROUP0_CFG_group0_step_START          (16)
#define SOC_BLPWM_GROUP0_CFG_group0_step_END            (30)
#define SOC_BLPWM_GROUP0_CFG_group0_active_START        (31)
#define SOC_BLPWM_GROUP0_CFG_group0_active_END          (31)


/*****************************************************************************
 �ṹ��    : SOC_BLPWM_GROUP1_CFG_UNION
 �ṹ˵��  : GROUP1_CFG �Ĵ����ṹ���塣��ַƫ����:0x110����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���PWM�źŷ���1���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  group1_refresh_freq : 8;  /* bit[0-7]  : ˢ��Ƶ�ʣ���ÿ���ٸ�����ʹ����һ������ֵ�� */
        unsigned int  group1_step_times   : 8;  /* bit[8-15] : �����ļ�/��������0ʱΪ��һ�Σ�1ʱ�����Σ��Դ����ơ� */
        unsigned int  group1_step         : 15; /* bit[16-30]: ������15λ�з������� */
        unsigned int  group1_active       : 1;  /* bit[31]   : ��ʾ�Ƿ���б������ã�Ϊ0ʱ�����д�������ͺ����ķ��������ѭ��ʹ�����һ���ߵ͵�ƽ���������bl_pwm�� */
    } reg;
} SOC_BLPWM_GROUP1_CFG_UNION;
#endif
#define SOC_BLPWM_GROUP1_CFG_group1_refresh_freq_START  (0)
#define SOC_BLPWM_GROUP1_CFG_group1_refresh_freq_END    (7)
#define SOC_BLPWM_GROUP1_CFG_group1_step_times_START    (8)
#define SOC_BLPWM_GROUP1_CFG_group1_step_times_END      (15)
#define SOC_BLPWM_GROUP1_CFG_group1_step_START          (16)
#define SOC_BLPWM_GROUP1_CFG_group1_step_END            (30)
#define SOC_BLPWM_GROUP1_CFG_group1_active_START        (31)
#define SOC_BLPWM_GROUP1_CFG_group1_active_END          (31)


/*****************************************************************************
 �ṹ��    : SOC_BLPWM_GROUP2_CFG_UNION
 �ṹ˵��  : GROUP2_CFG �Ĵ����ṹ���塣��ַƫ����:0x114����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���PWM�źŷ���2���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  group2_refresh_freq : 8;  /* bit[0-7]  : ˢ��Ƶ�ʣ���ÿ���ٸ�����ʹ����һ������ֵ�� */
        unsigned int  group2_step_times   : 8;  /* bit[8-15] : �����ļ�/��������0ʱΪ��һ�Σ�1ʱ�����Σ��Դ����ơ� */
        unsigned int  group2_step         : 15; /* bit[16-30]: ������15λ�з������� */
        unsigned int  group2_active       : 1;  /* bit[31]   : ��ʾ�Ƿ���б������ã�Ϊ0ʱ�����д�������ͺ����ķ��������ѭ��ʹ�����һ���ߵ͵�ƽ���������bl_pwm�� */
    } reg;
} SOC_BLPWM_GROUP2_CFG_UNION;
#endif
#define SOC_BLPWM_GROUP2_CFG_group2_refresh_freq_START  (0)
#define SOC_BLPWM_GROUP2_CFG_group2_refresh_freq_END    (7)
#define SOC_BLPWM_GROUP2_CFG_group2_step_times_START    (8)
#define SOC_BLPWM_GROUP2_CFG_group2_step_times_END      (15)
#define SOC_BLPWM_GROUP2_CFG_group2_step_START          (16)
#define SOC_BLPWM_GROUP2_CFG_group2_step_END            (30)
#define SOC_BLPWM_GROUP2_CFG_group2_active_START        (31)
#define SOC_BLPWM_GROUP2_CFG_group2_active_END          (31)


/*****************************************************************************
 �ṹ��    : SOC_BLPWM_GROUP3_CFG_UNION
 �ṹ˵��  : GROUP3_CFG �Ĵ����ṹ���塣��ַƫ����:0x118����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���PWM�źŷ���3���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  group3_refresh_freq : 8;  /* bit[0-7]  : ˢ��Ƶ�ʣ���ÿ���ٸ�����ʹ����һ������ֵ�� */
        unsigned int  group3_step_times   : 8;  /* bit[8-15] : �����ļ�/�������� */
        unsigned int  group3_step         : 15; /* bit[16-30]: ������15λ�з������� */
        unsigned int  group3_active       : 1;  /* bit[31]   : ��ʾ�Ƿ���б������ã�Ϊ0ʱ�����д�������ͺ����ķ��������ѭ��ʹ�����һ���ߵ͵�ƽ���������bl_pwm�� */
    } reg;
} SOC_BLPWM_GROUP3_CFG_UNION;
#endif
#define SOC_BLPWM_GROUP3_CFG_group3_refresh_freq_START  (0)
#define SOC_BLPWM_GROUP3_CFG_group3_refresh_freq_END    (7)
#define SOC_BLPWM_GROUP3_CFG_group3_step_times_START    (8)
#define SOC_BLPWM_GROUP3_CFG_group3_step_times_END      (15)
#define SOC_BLPWM_GROUP3_CFG_group3_step_START          (16)
#define SOC_BLPWM_GROUP3_CFG_group3_step_END            (30)
#define SOC_BLPWM_GROUP3_CFG_group3_active_START        (31)
#define SOC_BLPWM_GROUP3_CFG_group3_active_END          (31)


/*****************************************************************************
 �ṹ��    : SOC_BLPWM_GROUP4_CFG_UNION
 �ṹ˵��  : GROUP4_CFG �Ĵ����ṹ���塣��ַƫ����:0x11C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���PWM�źŷ���4���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  group4_refresh_freq : 8;  /* bit[0-7]  : ˢ��Ƶ�ʣ���ÿ���ٸ�����ʹ����һ������ֵ�� */
        unsigned int  group4_step_times   : 8;  /* bit[8-15] : �����ļ�/��������0ʱΪ��һ�Σ�1ʱ�����Σ��Դ����ơ� */
        unsigned int  group4_step         : 15; /* bit[16-30]: ������15λ�з������� */
        unsigned int  group4_active       : 1;  /* bit[31]   : ��ʾ�Ƿ���б������ã�Ϊ0ʱ�����д�������ͺ����ķ��������ѭ��ʹ�����һ���ߵ͵�ƽ���������bl_pwm�� */
    } reg;
} SOC_BLPWM_GROUP4_CFG_UNION;
#endif
#define SOC_BLPWM_GROUP4_CFG_group4_refresh_freq_START  (0)
#define SOC_BLPWM_GROUP4_CFG_group4_refresh_freq_END    (7)
#define SOC_BLPWM_GROUP4_CFG_group4_step_times_START    (8)
#define SOC_BLPWM_GROUP4_CFG_group4_step_times_END      (15)
#define SOC_BLPWM_GROUP4_CFG_group4_step_START          (16)
#define SOC_BLPWM_GROUP4_CFG_group4_step_END            (30)
#define SOC_BLPWM_GROUP4_CFG_group4_active_START        (31)
#define SOC_BLPWM_GROUP4_CFG_group4_active_END          (31)


/*****************************************************************************
 �ṹ��    : SOC_BLPWM_GROUP5_CFG_UNION
 �ṹ˵��  : GROUP5_CFG �Ĵ����ṹ���塣��ַƫ����:0x120����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���PWM�źŷ���5���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  group5_refresh_freq : 8;  /* bit[0-7]  : ˢ��Ƶ�ʣ���ÿ���ٸ�����ʹ����һ������ֵ�� */
        unsigned int  group5_step_times   : 8;  /* bit[8-15] : �����ļ�/��������0ʱΪ��һ�Σ�1ʱ�����Σ��Դ����ơ� */
        unsigned int  group5_step         : 15; /* bit[16-30]: ������15λ�з������� */
        unsigned int  group5_active       : 1;  /* bit[31]   : ��ʾ�Ƿ���б������ã�Ϊ0ʱ�����д��������ѭ��ʹ�����һ���������� */
    } reg;
} SOC_BLPWM_GROUP5_CFG_UNION;
#endif
#define SOC_BLPWM_GROUP5_CFG_group5_refresh_freq_START  (0)
#define SOC_BLPWM_GROUP5_CFG_group5_refresh_freq_END    (7)
#define SOC_BLPWM_GROUP5_CFG_group5_step_times_START    (8)
#define SOC_BLPWM_GROUP5_CFG_group5_step_times_END      (15)
#define SOC_BLPWM_GROUP5_CFG_group5_step_START          (16)
#define SOC_BLPWM_GROUP5_CFG_group5_step_END            (30)
#define SOC_BLPWM_GROUP5_CFG_group5_active_START        (31)
#define SOC_BLPWM_GROUP5_CFG_group5_active_END          (31)


/*****************************************************************************
 �ṹ��    : SOC_BLPWM_GROUP6_CFG_UNION
 �ṹ˵��  : GROUP6_CFG �Ĵ����ṹ���塣��ַƫ����:0x124����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���PWM�źŷ���6���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  group6_refresh_freq : 8;  /* bit[0-7]  : ˢ��Ƶ�ʣ���ÿ���ٸ�����ʹ����һ������ֵ�� */
        unsigned int  group6_step_times   : 8;  /* bit[8-15] : �����ļ�/��������0ʱΪ��һ�Σ�1ʱ�����Σ��Դ����ơ� */
        unsigned int  group6_step         : 15; /* bit[16-30]: ������15λ�з������� */
        unsigned int  group6_active       : 1;  /* bit[31]   : ��ʾ�Ƿ���б������ã�Ϊ0ʱ�����д�������ͺ����ķ��������ѭ��ʹ�����һ���ߵ͵�ƽ���������bl_pwm�� */
    } reg;
} SOC_BLPWM_GROUP6_CFG_UNION;
#endif
#define SOC_BLPWM_GROUP6_CFG_group6_refresh_freq_START  (0)
#define SOC_BLPWM_GROUP6_CFG_group6_refresh_freq_END    (7)
#define SOC_BLPWM_GROUP6_CFG_group6_step_times_START    (8)
#define SOC_BLPWM_GROUP6_CFG_group6_step_times_END      (15)
#define SOC_BLPWM_GROUP6_CFG_group6_step_START          (16)
#define SOC_BLPWM_GROUP6_CFG_group6_step_END            (30)
#define SOC_BLPWM_GROUP6_CFG_group6_active_START        (31)
#define SOC_BLPWM_GROUP6_CFG_group6_active_END          (31)


/*****************************************************************************
 �ṹ��    : SOC_BLPWM_GROUP7_CFG_UNION
 �ṹ˵��  : GROUP7_CFG �Ĵ����ṹ���塣��ַƫ����:0x128����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���PWM�źŷ���7���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  group7_refresh_freq : 8;  /* bit[0-7]  : ˢ��Ƶ�ʣ���ÿ���ٸ�����ʹ����һ������ֵ�� */
        unsigned int  group7_step_times   : 8;  /* bit[8-15] : �����ļ�/��������0ʱΪ��һ�Σ�1ʱ�����Σ��Դ����ơ� */
        unsigned int  group7_step         : 15; /* bit[16-30]: ������15λ�з������� */
        unsigned int  group7_active       : 1;  /* bit[31]   : ��ʾ�Ƿ���б������ã�Ϊ0ʱ�����д�������ͺ����ķ��������ѭ��ʹ�����һ���ߵ͵�ƽ���������bl_pwm�� */
    } reg;
} SOC_BLPWM_GROUP7_CFG_UNION;
#endif
#define SOC_BLPWM_GROUP7_CFG_group7_refresh_freq_START  (0)
#define SOC_BLPWM_GROUP7_CFG_group7_refresh_freq_END    (7)
#define SOC_BLPWM_GROUP7_CFG_group7_step_times_START    (8)
#define SOC_BLPWM_GROUP7_CFG_group7_step_times_END      (15)
#define SOC_BLPWM_GROUP7_CFG_group7_step_START          (16)
#define SOC_BLPWM_GROUP7_CFG_group7_step_END            (30)
#define SOC_BLPWM_GROUP7_CFG_group7_active_START        (31)
#define SOC_BLPWM_GROUP7_CFG_group7_active_END          (31)


/*****************************************************************************
 �ṹ��    : SOC_BLPWM_OUT_STATUS_UNION
 �ṹ˵��  : OUT_STATUS �Ĵ����ṹ���塣��ַƫ����:0x130����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gen_low  : 16; /* bit[0-15] : ����ģʽ���ʱ����ǰpwm�źŵĵ͵�ƽ�������� */
        unsigned int  gen_high : 16; /* bit[16-31]: ����ģʽ���ʱ����ǰpwm�źŵĸߵ�ƽ�������� */
    } reg;
} SOC_BLPWM_OUT_STATUS_UNION;
#endif
#define SOC_BLPWM_OUT_STATUS_gen_low_START   (0)
#define SOC_BLPWM_OUT_STATUS_gen_low_END     (15)
#define SOC_BLPWM_OUT_STATUS_gen_high_START  (16)
#define SOC_BLPWM_OUT_STATUS_gen_high_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_BLPWM_GROUP_STATUS_UNION
 �ṹ˵��  : GROUP_STATUS �Ĵ����ṹ���塣��ַƫ����:0x134����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gen_num          : 3;  /* bit[0-2]  : �������ʱ����ǰ�������õ������� */
        unsigned int  reserved_0       : 13; /* bit[3-15] : ���� */
        unsigned int  group_over       : 1;  /* bit[16]   : ����������ɡ� */
        unsigned int  group_inprogress : 1;  /* bit[17]   : ���ڽ��з���ļӼ������� */
        unsigned int  reserved_1       : 14; /* bit[18-31]: ������ */
    } reg;
} SOC_BLPWM_GROUP_STATUS_UNION;
#endif
#define SOC_BLPWM_GROUP_STATUS_gen_num_START           (0)
#define SOC_BLPWM_GROUP_STATUS_gen_num_END             (2)
#define SOC_BLPWM_GROUP_STATUS_group_over_START        (16)
#define SOC_BLPWM_GROUP_STATUS_group_over_END          (16)
#define SOC_BLPWM_GROUP_STATUS_group_inprogress_START  (17)
#define SOC_BLPWM_GROUP_STATUS_group_inprogress_END    (17)






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

#endif /* end of soc_blpwm_interface.h */
