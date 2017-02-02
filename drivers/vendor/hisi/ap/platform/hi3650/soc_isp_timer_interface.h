/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_isp_timer_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:22:09
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_ISP_TIMER.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_ISP_TIMER_INTERFACE_H__
#define __SOC_ISP_TIMER_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) TIMER
 ****************************************************************************/
/* �Ĵ���˵����������ֵ�Ĵ���
   λ����UNION�ṹ:  SOC_ISP_TIMER_TIMER0_LOAD_UNION */
#define SOC_ISP_TIMER_TIMER0_LOAD_ADDR(base)          ((base) + (0x0000))

/* �Ĵ���˵����������ֵ�Ĵ���
   λ����UNION�ṹ:  SOC_ISP_TIMER_TIMER1_LOAD_UNION */
#define SOC_ISP_TIMER_TIMER1_LOAD_ADDR(base)          ((base) + (0x0020))

/* �Ĵ���˵������ǰ����ֵ�Ĵ���
   λ����UNION�ṹ:  SOC_ISP_TIMER_TIMER0_VALUE_UNION */
#define SOC_ISP_TIMER_TIMER0_VALUE_ADDR(base)         ((base) + (0x0004))

/* �Ĵ���˵������ǰ����ֵ�Ĵ���
   λ����UNION�ṹ:  SOC_ISP_TIMER_TIMER1_VALUE_UNION */
#define SOC_ISP_TIMER_TIMER1_VALUE_ADDR(base)         ((base) + (0x0024))

/* �Ĵ���˵�������ƼĴ���
   λ����UNION�ṹ:  SOC_ISP_TIMER_TIMER0_CONTROL_UNION */
#define SOC_ISP_TIMER_TIMER0_CONTROL_ADDR(base)       ((base) + (0x0008))

/* �Ĵ���˵�������ƼĴ���
   λ����UNION�ṹ:  SOC_ISP_TIMER_TIMER1_CONTROL_UNION */
#define SOC_ISP_TIMER_TIMER1_CONTROL_ADDR(base)       ((base) + (0x0028))

/* �Ĵ���˵�����ж�����Ĵ���
   λ����UNION�ṹ:  SOC_ISP_TIMER_TIMER0_INTCLR_UNION */
#define SOC_ISP_TIMER_TIMER0_INTCLR_ADDR(base)        ((base) + (0x000C))

/* �Ĵ���˵�����ж�����Ĵ���
   λ����UNION�ṹ:  SOC_ISP_TIMER_TIMER1_INTCLR_UNION */
#define SOC_ISP_TIMER_TIMER1_INTCLR_ADDR(base)        ((base) + (0x002C))

/* �Ĵ���˵����ԭʼ�ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ISP_TIMER_TIMER0_RIS_UNION */
#define SOC_ISP_TIMER_TIMER0_RIS_ADDR(base)           ((base) + (0x0010))

/* �Ĵ���˵����ԭʼ�ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ISP_TIMER_TIMER1_RIS_UNION */
#define SOC_ISP_TIMER_TIMER1_RIS_ADDR(base)           ((base) + (0x0030))

/* �Ĵ���˵�������κ��ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ISP_TIMER_TIMER0_MIS_UNION */
#define SOC_ISP_TIMER_TIMER0_MIS_ADDR(base)           ((base) + (0x0014))

/* �Ĵ���˵�������κ��ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ISP_TIMER_TIMER1_MIS_UNION */
#define SOC_ISP_TIMER_TIMER1_MIS_ADDR(base)           ((base) + (0x0034))

/* �Ĵ���˵����Periodicģʽ������ֵ�Ĵ���
   λ����UNION�ṹ:  SOC_ISP_TIMER_TIMER0_BGLOAD_UNION */
#define SOC_ISP_TIMER_TIMER0_BGLOAD_ADDR(base)        ((base) + (0x0018))

/* �Ĵ���˵����Periodicģʽ������ֵ�Ĵ���
   λ����UNION�ṹ:  SOC_ISP_TIMER_TIMER1_BGLOAD_UNION */
#define SOC_ISP_TIMER_TIMER1_BGLOAD_ADDR(base)        ((base) + (0x0038))





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
                     (1/1) TIMER
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_ISP_TIMER_TIMER0_LOAD_UNION
 �ṹ˵��  : TIMER0_LOAD �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������ֵ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timerxload : 32; /* bit[0-31]: �����Ŷ�ʱ���ļ�����ֵ */
    } reg;
} SOC_ISP_TIMER_TIMER0_LOAD_UNION;
#endif
#define SOC_ISP_TIMER_TIMER0_LOAD_timerxload_START  (0)
#define SOC_ISP_TIMER_TIMER0_LOAD_timerxload_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_TIMER_TIMER1_LOAD_UNION
 �ṹ˵��  : TIMER1_LOAD �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������ֵ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timerxload : 32; /* bit[0-31]: �����Ŷ�ʱ���ļ�����ֵ */
    } reg;
} SOC_ISP_TIMER_TIMER1_LOAD_UNION;
#endif
#define SOC_ISP_TIMER_TIMER1_LOAD_timerxload_START  (0)
#define SOC_ISP_TIMER_TIMER1_LOAD_timerxload_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_TIMER_TIMER0_VALUE_UNION
 �ṹ˵��  : TIMER0_VALUE �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0xffffffff�����:32
 �Ĵ���˵��: ��ǰ����ֵ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timerxvalue : 32; /* bit[0-31]: ��ʾ���ڵݼ��Ķ�ʱ�������ĵ�ǰֵ */
    } reg;
} SOC_ISP_TIMER_TIMER0_VALUE_UNION;
#endif
#define SOC_ISP_TIMER_TIMER0_VALUE_timerxvalue_START  (0)
#define SOC_ISP_TIMER_TIMER0_VALUE_timerxvalue_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_TIMER_TIMER1_VALUE_UNION
 �ṹ˵��  : TIMER1_VALUE �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0xffffffff�����:32
 �Ĵ���˵��: ��ǰ����ֵ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timerxvalue : 32; /* bit[0-31]: ��ʾ���ڵݼ��Ķ�ʱ�������ĵ�ǰֵ */
    } reg;
} SOC_ISP_TIMER_TIMER1_VALUE_UNION;
#endif
#define SOC_ISP_TIMER_TIMER1_VALUE_timerxvalue_START  (0)
#define SOC_ISP_TIMER_TIMER1_VALUE_timerxvalue_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_TIMER_TIMER0_CONTROL_UNION
 �ṹ˵��  : TIMER0_CONTROL �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000020�����:32
 �Ĵ���˵��: ���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  oneshot    : 1;  /* bit[0]   : ����ģʽ��
                                                     0���ؾ������ȱʡֵ����
                                                     1��һ���Լ����� */
        unsigned int  timersize  : 1;  /* bit[1]   : ������λ����
                                                     0��16bit��ȱʡֵ����
                                                     1��32bit�� */
        unsigned int  timerpre   : 2;  /* bit[2-3] : Ԥ��Ƶ���ӣ�
                                                     00��������Ԥ��Ƶ��ʱ��Ƶ�ʳ���1��ȱʡֵ����
                                                     01��4��Ԥ��Ƶ������ʱ��ʱ��Ƶ�ʳ���16��
                                                     10��8��Ԥ��Ƶ������ʱ��ʱ��Ƶ�ʳ���256��
                                                     11��δ���壬����Ϊ��ֵ���൱��Ԥ��Ƶ����Ϊ8��Ԥ��Ƶ */
        unsigned int  reserved_0 : 1;  /* bit[4]   : ������д��Ч����ʱ����0�� */
        unsigned int  internable : 1;  /* bit[5]   : �ж�ʹ��λ��д��ʱ����
                                                     0����ֹ�жϣ�
                                                     1��ʹ���ж�(ȱʡֵ)�� */
        unsigned int  timermode  : 1;  /* bit[6]   : ����ģʽ��
                                                     0����ʱ������Free-runningģʽ��ȱʡֵ����
                                                     1����ʱ������Periodicģʽ�� */
        unsigned int  timeren    : 1;  /* bit[7]   : ��ʱ��ʹ��λ��
                                                     0����ֹ��ȱʡֵ����
                                                     1��ʹ�ܡ���ʱ��ʹ��λ�� */
        unsigned int  reserved_1 : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_ISP_TIMER_TIMER0_CONTROL_UNION;
#endif
#define SOC_ISP_TIMER_TIMER0_CONTROL_oneshot_START     (0)
#define SOC_ISP_TIMER_TIMER0_CONTROL_oneshot_END       (0)
#define SOC_ISP_TIMER_TIMER0_CONTROL_timersize_START   (1)
#define SOC_ISP_TIMER_TIMER0_CONTROL_timersize_END     (1)
#define SOC_ISP_TIMER_TIMER0_CONTROL_timerpre_START    (2)
#define SOC_ISP_TIMER_TIMER0_CONTROL_timerpre_END      (3)
#define SOC_ISP_TIMER_TIMER0_CONTROL_internable_START  (5)
#define SOC_ISP_TIMER_TIMER0_CONTROL_internable_END    (5)
#define SOC_ISP_TIMER_TIMER0_CONTROL_timermode_START   (6)
#define SOC_ISP_TIMER_TIMER0_CONTROL_timermode_END     (6)
#define SOC_ISP_TIMER_TIMER0_CONTROL_timeren_START     (7)
#define SOC_ISP_TIMER_TIMER0_CONTROL_timeren_END       (7)


/*****************************************************************************
 �ṹ��    : SOC_ISP_TIMER_TIMER1_CONTROL_UNION
 �ṹ˵��  : TIMER1_CONTROL �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x00000020�����:32
 �Ĵ���˵��: ���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  oneshot    : 1;  /* bit[0]   : ����ģʽ��
                                                     0���ؾ������ȱʡֵ����
                                                     1��һ���Լ����� */
        unsigned int  timersize  : 1;  /* bit[1]   : ������λ����
                                                     0��16bit��ȱʡֵ����
                                                     1��32bit�� */
        unsigned int  timerpre   : 2;  /* bit[2-3] : Ԥ��Ƶ���ӣ�
                                                     00��������Ԥ��Ƶ��ʱ��Ƶ�ʳ���1��ȱʡֵ����
                                                     01��4��Ԥ��Ƶ������ʱ��ʱ��Ƶ�ʳ���16��
                                                     10��8��Ԥ��Ƶ������ʱ��ʱ��Ƶ�ʳ���256��
                                                     11��δ���壬����Ϊ��ֵ���൱��Ԥ��Ƶ����Ϊ8��Ԥ��Ƶ */
        unsigned int  reserved_0 : 1;  /* bit[4]   : ������д��Ч����ʱ����0�� */
        unsigned int  internable : 1;  /* bit[5]   : �ж�ʹ��λ��д��ʱ����
                                                     0����ֹ�жϣ�
                                                     1��ʹ���ж�(ȱʡֵ)�� */
        unsigned int  timermode  : 1;  /* bit[6]   : ����ģʽ��
                                                     0����ʱ������Free-runningģʽ��ȱʡֵ����
                                                     1����ʱ������Periodicģʽ�� */
        unsigned int  timeren    : 1;  /* bit[7]   : ��ʱ��ʹ��λ��
                                                     0����ֹ��ȱʡֵ����
                                                     1��ʹ�ܡ���ʱ��ʹ��λ�� */
        unsigned int  reserved_1 : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_ISP_TIMER_TIMER1_CONTROL_UNION;
#endif
#define SOC_ISP_TIMER_TIMER1_CONTROL_oneshot_START     (0)
#define SOC_ISP_TIMER_TIMER1_CONTROL_oneshot_END       (0)
#define SOC_ISP_TIMER_TIMER1_CONTROL_timersize_START   (1)
#define SOC_ISP_TIMER_TIMER1_CONTROL_timersize_END     (1)
#define SOC_ISP_TIMER_TIMER1_CONTROL_timerpre_START    (2)
#define SOC_ISP_TIMER_TIMER1_CONTROL_timerpre_END      (3)
#define SOC_ISP_TIMER_TIMER1_CONTROL_internable_START  (5)
#define SOC_ISP_TIMER_TIMER1_CONTROL_internable_END    (5)
#define SOC_ISP_TIMER_TIMER1_CONTROL_timermode_START   (6)
#define SOC_ISP_TIMER_TIMER1_CONTROL_timermode_END     (6)
#define SOC_ISP_TIMER_TIMER1_CONTROL_timeren_START     (7)
#define SOC_ISP_TIMER_TIMER1_CONTROL_timeren_END       (7)


/*****************************************************************************
 �ṹ��    : SOC_ISP_TIMER_TIMER0_INTCLR_UNION
 �ṹ˵��  : TIMER0_INTCLR �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timerxintclr : 32; /* bit[0-31]: �κ�д�����������Timer��ʱ�����ж� */
    } reg;
} SOC_ISP_TIMER_TIMER0_INTCLR_UNION;
#endif
#define SOC_ISP_TIMER_TIMER0_INTCLR_timerxintclr_START  (0)
#define SOC_ISP_TIMER_TIMER0_INTCLR_timerxintclr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_TIMER_TIMER1_INTCLR_UNION
 �ṹ˵��  : TIMER1_INTCLR �Ĵ����ṹ���塣��ַƫ����:0x002C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timerxintclr : 32; /* bit[0-31]: �κ�д�����������Timer��ʱ�����ж� */
    } reg;
} SOC_ISP_TIMER_TIMER1_INTCLR_UNION;
#endif
#define SOC_ISP_TIMER_TIMER1_INTCLR_timerxintclr_START  (0)
#define SOC_ISP_TIMER_TIMER1_INTCLR_timerxintclr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_TIMER_TIMER0_RIS_UNION
 �ṹ˵��  : TIMER0_RIS �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: ԭʼ�ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timerxris : 1;  /* bit[0]   : ��ʱ���ؼ�������ԭʼ�ж�״̬��
                                                    0����ԭʼ�жϣ�
                                                    1����ԭʼ�жϡ� */
        unsigned int  reserved  : 31; /* bit[1-31]: ������д��Ч����ʱ����0�� */
    } reg;
} SOC_ISP_TIMER_TIMER0_RIS_UNION;
#endif
#define SOC_ISP_TIMER_TIMER0_RIS_timerxris_START  (0)
#define SOC_ISP_TIMER_TIMER0_RIS_timerxris_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_ISP_TIMER_TIMER1_RIS_UNION
 �ṹ˵��  : TIMER1_RIS �Ĵ����ṹ���塣��ַƫ����:0x0030����ֵ:0x00000000�����:32
 �Ĵ���˵��: ԭʼ�ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timerxris : 1;  /* bit[0]   : ��ʱ���ؼ�������ԭʼ�ж�״̬��
                                                    0����ԭʼ�жϣ�
                                                    1����ԭʼ�жϡ� */
        unsigned int  reserved  : 31; /* bit[1-31]: ������д��Ч����ʱ����0�� */
    } reg;
} SOC_ISP_TIMER_TIMER1_RIS_UNION;
#endif
#define SOC_ISP_TIMER_TIMER1_RIS_timerxris_START  (0)
#define SOC_ISP_TIMER_TIMER1_RIS_timerxris_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_ISP_TIMER_TIMER0_MIS_UNION
 �ṹ˵��  : TIMER0_MIS �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���κ��ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timerxmis : 1;  /* bit[0]   : ��ʱ�������κ�ļ������ж�״̬��
                                                    0�����жϣ�
                                                    1�����жϡ� */
        unsigned int  reserved  : 31; /* bit[1-31]: ������д��Ч����ʱ����0�� */
    } reg;
} SOC_ISP_TIMER_TIMER0_MIS_UNION;
#endif
#define SOC_ISP_TIMER_TIMER0_MIS_timerxmis_START  (0)
#define SOC_ISP_TIMER_TIMER0_MIS_timerxmis_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_ISP_TIMER_TIMER1_MIS_UNION
 �ṹ˵��  : TIMER1_MIS �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���κ��ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timerxmis : 1;  /* bit[0]   : ��ʱ�������κ�ļ������ж�״̬��
                                                    0�����жϣ�
                                                    1�����жϡ� */
        unsigned int  reserved  : 31; /* bit[1-31]: ������д��Ч����ʱ����0�� */
    } reg;
} SOC_ISP_TIMER_TIMER1_MIS_UNION;
#endif
#define SOC_ISP_TIMER_TIMER1_MIS_timerxmis_START  (0)
#define SOC_ISP_TIMER_TIMER1_MIS_timerxmis_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_ISP_TIMER_TIMER0_BGLOAD_UNION
 �ṹ˵��  : TIMER0_BGLOAD �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: Periodicģʽ������ֵ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timerxbgload : 32; /* bit[0-31]: �洢��ʱ���ļ�����ֵ */
    } reg;
} SOC_ISP_TIMER_TIMER0_BGLOAD_UNION;
#endif
#define SOC_ISP_TIMER_TIMER0_BGLOAD_timerxbgload_START  (0)
#define SOC_ISP_TIMER_TIMER0_BGLOAD_timerxbgload_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_TIMER_TIMER1_BGLOAD_UNION
 �ṹ˵��  : TIMER1_BGLOAD �Ĵ����ṹ���塣��ַƫ����:0x0038����ֵ:0x00000000�����:32
 �Ĵ���˵��: Periodicģʽ������ֵ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timerxbgload : 32; /* bit[0-31]: �洢��ʱ���ļ�����ֵ */
    } reg;
} SOC_ISP_TIMER_TIMER1_BGLOAD_UNION;
#endif
#define SOC_ISP_TIMER_TIMER1_BGLOAD_timerxbgload_START  (0)
#define SOC_ISP_TIMER_TIMER1_BGLOAD_timerxbgload_END    (31)






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

#endif /* end of soc_isp_timer_interface.h */
