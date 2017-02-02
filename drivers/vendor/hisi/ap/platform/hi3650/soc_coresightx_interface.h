/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_coresightx_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:19:10
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_coresightx.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_CORESIGHTX_INTERFACE_H__
#define __SOC_CORESIGHTX_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) CORESIGHT
 ****************************************************************************/
/* �Ĵ���˵����Funnel���ƼĴ���
   λ����UNION�ṹ:  SOC_coresightx_CTRL_REG_UNION */
#define SOC_coresightx_CTRL_REG_ADDR(base)            ((base) + (0x1000))

/* �Ĵ���˵����Funnel���ȼ����ƼĴ���
   λ����UNION�ṹ:  SOC_coresightx_PRIORITY_CTRL_REG_UNION */
#define SOC_coresightx_PRIORITY_CTRL_REG_ADDR(base)   ((base) + (0x1004))

/* �Ĵ���˵����Funnel�������ʼĴ���
   λ����UNION�ṹ:  SOC_coresightx_LOCKACCESS_UNION */
#define SOC_coresightx_LOCKACCESS_ADDR(base)          ((base) + (0x1FB0))

/* �Ĵ���˵����Funnel����״̬�Ĵ���
   λ����UNION�ṹ:  SOC_coresightx_LOCKSTATUS_UNION */
#define SOC_coresightx_LOCKSTATUS_ADDR(base)          ((base) + (0x1FB4))

/* �Ĵ���˵����TPIU trigger������ֵ�Ĵ���
   λ����UNION�ṹ:  SOC_coresightx_TRIGGER_COUNTER_VALUE_UNION */
#define SOC_coresightx_TRIGGER_COUNTER_VALUE_ADDR(base) ((base) + (0x2104))

/* �Ĵ���˵����TPIU Formatterͬ���������Ĵ���
   λ����UNION�ṹ:  SOC_coresightx_FSCR_UNION */
#define SOC_coresightx_FSCR_ADDR(base)                ((base) + (0x2308))

/* �Ĵ���˵����TPIU���ɲ���ģʽ���ƼĴ���
   λ����UNION�ṹ:  SOC_coresightx_ITCTRL_UNION */
#define SOC_coresightx_ITCTRL_ADDR(base)              ((base) + (0x2F00))

/* �Ĵ���˵����ETR RAM size�Ĵ���
   λ����UNION�ṹ:  SOC_coresightx_RSZ_UNION */
#define SOC_coresightx_RSZ_ADDR(base)                 ((base) + (0x3004))

/* �Ĵ���˵����ETR���ƼĴ���
   λ����UNION�ṹ:  SOC_coresightx_CTL_UNION */
#define SOC_coresightx_CTL_ADDR(base)                 ((base) + (0x3020))

/* �Ĵ���˵����ETR����buffer��ַ�Ĵ���
   λ����UNION�ṹ:  SOC_coresightx_DBALO_UNION */
#define SOC_coresightx_DBALO_ADDR(base)               ((base) + (0x3118))

/* �Ĵ���˵����CTI���ƼĴ���
   λ����UNION�ṹ:  SOC_coresightx_CTICONTROL_UNION */
#define SOC_coresightx_CTICONTROL_ADDR(base)          ((base) + (0x4000))

/* �Ĵ���˵����CTItrigger0��channelʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_coresightx_CTIINEN0_UNION */
#define SOC_coresightx_CTIINEN0_ADDR(base)            ((base) + (0x4020))

/* �Ĵ���˵����CTI channelʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_coresightx_CTIGATE_UNION */
#define SOC_coresightx_CTIGATE_ADDR(base)             ((base) + (0x4140))

/* �Ĵ���˵����STMӲ���¼�ʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_coresightx_STMHEER_UNION */
#define SOC_coresightx_STMHEER_ADDR(base)             ((base) + (0x5D00))

/* �Ĵ���˵����STM�����˿�ʹ���ź�
   λ����UNION�ṹ:  SOC_coresightx_STMSPER_UNION */
#define SOC_coresightx_STMSPER_ADDR(base)             ((base) + (0x5E00))

/* �Ĵ���˵����STM trace������״̬�Ĵ���
   λ����UNION�ṹ:  SOC_coresightx_STMTCSR_UNION */
#define SOC_coresightx_STMTCSR_ADDR(base)             ((base) + (0x5E80))

/* �Ĵ���˵����ETF���ƼĴ���
   λ����UNION�ṹ:  SOC_coresightx_ETFCTL_UNION */
#define SOC_coresightx_ETFCTL_ADDR(base)              ((base) + (0x6020))

/* �Ĵ���˵����ETF����ģʽ�Ĵ���
   λ����UNION�ṹ:  SOC_coresightx_ETFMODE_UNION */
#define SOC_coresightx_ETFMODE_ADDR(base)             ((base) + (0x6028))

/* �Ĵ���˵����ETF����ģʽ���ƼĴ���
   λ����UNION�ṹ:  SOC_coresightx_ETFITCTRL_UNION */
#define SOC_coresightx_ETFITCTRL_ADDR(base)           ((base) + (0x6F00))

/* �Ĵ���˵����timestamp�������ƼĴ���
   λ����UNION�ṹ:  SOC_coresightx_TSCNTCR_UNION */
#define SOC_coresightx_TSCNTCR_ADDR(base)             ((base) + (0x7000))

/* �Ĵ���˵����timestamp��ǰ����ֵ��λ�Ĵ���
   λ����UNION�ṹ:  SOC_coresightx_TSCNTCVLW_UNION */
#define SOC_coresightx_TSCNTCVLW_ADDR(base)           ((base) + (0x7008))

/* �Ĵ���˵����timestamp��ǰ����ֵ��λ�Ĵ���
   λ����UNION�ṹ:  SOC_coresightx_TSCNTCVUP_UNION */
#define SOC_coresightx_TSCNTCVUP_ADDR(base)           ((base) + (0x700C))

/* �Ĵ���˵����timestamp��ǰ����ֵ��λ�Ĵ���
   λ����UNION�ṹ:  SOC_coresightx_TSCNTCVLW_RO_UNION */
#define SOC_coresightx_TSCNTCVLW_RO_ADDR(base)        ((base) + (0x8000))

/* �Ĵ���˵����timestamp��ǰ����ֵ��λ�Ĵ���
   λ����UNION�ṹ:  SOC_coresightx_TSCNTCVUP_RO_UNION */
#define SOC_coresightx_TSCNTCVUP_RO_ADDR(base)        ((base) + (0x8004))





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
                     (1/1) CORESIGHT
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_coresightx_CTRL_REG_UNION
 �ṹ˵��  : CTRL_REG �Ĵ����ṹ���塣��ַƫ����:0x1000����ֵ:0x00000300�����:32
 �Ĵ���˵��: Funnel���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enable   : 5;  /* bit[0-4]  : bit[0]~bit[3]�ֱ��Ӧport0~port4��
                                                    0��slave port disabled
                                                    1��slave port enabled */
        unsigned int  reserved_0: 3;  /* bit[5-7]  : Reserved */
        unsigned int  holdtime : 4;  /* bit[8-11] : Funnel ATB slave�˿�һ�����ٽ��յ�transaction��������hold time��Ϊ�˽��Ͷ˿�Ƶ���л���trace���ܴ�����Ӱ�졣���ٽ��յ�transaction��Ϊhold timeֵ��1��ȡֵ��Χb0000~b1110��b1111������ */
        unsigned int  reserved_1: 20; /* bit[12-31]: Reserved */
    } reg;
} SOC_coresightx_CTRL_REG_UNION;
#endif
#define SOC_coresightx_CTRL_REG_enable_START    (0)
#define SOC_coresightx_CTRL_REG_enable_END      (4)
#define SOC_coresightx_CTRL_REG_holdtime_START  (8)
#define SOC_coresightx_CTRL_REG_holdtime_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_coresightx_PRIORITY_CTRL_REG_UNION
 �ṹ˵��  : PRIORITY_CTRL_REG �Ĵ����ṹ���塣��ַƫ����:0x1004����ֵ:0x00000000�����:32
 �Ĵ���˵��: Funnel���ȼ����ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  priport0 : 3;  /* bit[0-2]  : �˿�0���ȼ����� */
        unsigned int  priport1 : 3;  /* bit[3-5]  : �˿�1���ȼ����� */
        unsigned int  priport2 : 3;  /* bit[6-8]  : �˿�2���ȼ����� */
        unsigned int  priport3 : 3;  /* bit[9-11] : �˿�3���ȼ����� */
        unsigned int  priport4 : 3;  /* bit[12-14]: �˿�4���ȼ����ã���ֵԽ�ͣ����ȼ�Խ�ߣ�������ֵ��ͬʱ�����С�Ķ˿����ȼ��ϸߡ����ܵ�ȡֵ���£�
                                                    b000�����ȼ�0
                                                    b001�����ȼ�1
                                                    b010�����ȼ�2
                                                    b011�����ȼ�3
                                                    b100�����ȼ�4
                                                    b101�����ȼ�5
                                                    b110�����ȼ�6
                                                    b111�����ȼ�0 */
        unsigned int  reserved : 17; /* bit[15-31]: Reserved */
    } reg;
} SOC_coresightx_PRIORITY_CTRL_REG_UNION;
#endif
#define SOC_coresightx_PRIORITY_CTRL_REG_priport0_START  (0)
#define SOC_coresightx_PRIORITY_CTRL_REG_priport0_END    (2)
#define SOC_coresightx_PRIORITY_CTRL_REG_priport1_START  (3)
#define SOC_coresightx_PRIORITY_CTRL_REG_priport1_END    (5)
#define SOC_coresightx_PRIORITY_CTRL_REG_priport2_START  (6)
#define SOC_coresightx_PRIORITY_CTRL_REG_priport2_END    (8)
#define SOC_coresightx_PRIORITY_CTRL_REG_priport3_START  (9)
#define SOC_coresightx_PRIORITY_CTRL_REG_priport3_END    (11)
#define SOC_coresightx_PRIORITY_CTRL_REG_priport4_START  (12)
#define SOC_coresightx_PRIORITY_CTRL_REG_priport4_END    (14)


/*****************************************************************************
 �ṹ��    : SOC_coresightx_LOCKACCESS_UNION
 �ṹ˵��  : LOCKACCESS �Ĵ����ṹ���塣��ַƫ����:0x1FB0����ֵ:0x00000000�����:32
 �Ĵ���˵��: Funnel�������ʼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  key : 32; /* bit[0-31]: д��0xC5ACCE55���н�����Ȼ��ſ�����������funnel�Ĵ�����д�������κ�ֵ���ٴ������� */
    } reg;
} SOC_coresightx_LOCKACCESS_UNION;
#endif
#define SOC_coresightx_LOCKACCESS_key_START  (0)
#define SOC_coresightx_LOCKACCESS_key_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_coresightx_LOCKSTATUS_UNION
 �ṹ˵��  : LOCKSTATUS �Ĵ����ṹ���塣��ַƫ����:0x1FB4����ֵ:0x00000003�����:32
 �Ĵ���˵��: Funnel����״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sli      : 1;  /* bit[0]   : ָʾ�ڼ��Ƿ�֧���������ƣ�
                                                   0�������֧����������
                                                   1�����֧���������� */
        unsigned int  slk      : 1;  /* bit[1]   : ����ĵ�ǰ����״̬��
                                                   0���ѽ���������д����
                                                   1����������������д�������ɶ� */
        unsigned int  ntt      : 1;  /* bit[2]   : ָʾ�������ʼĴ���Ϊ32-bit */
        unsigned int  reserved : 29; /* bit[3-31]: Reserved */
    } reg;
} SOC_coresightx_LOCKSTATUS_UNION;
#endif
#define SOC_coresightx_LOCKSTATUS_sli_START       (0)
#define SOC_coresightx_LOCKSTATUS_sli_END         (0)
#define SOC_coresightx_LOCKSTATUS_slk_START       (1)
#define SOC_coresightx_LOCKSTATUS_slk_END         (1)
#define SOC_coresightx_LOCKSTATUS_ntt_START       (2)
#define SOC_coresightx_LOCKSTATUS_ntt_END         (2)


/*****************************************************************************
 �ṹ��    : SOC_coresightx_TRIGGER_COUNTER_VALUE_UNION
 �ṹ˵��  : TRIGGER_COUNTER_VALUE �Ĵ����ṹ���塣��ַƫ����:0x2104����ֵ:0x00000000�����:32
 �Ĵ���˵��: TPIU trigger������ֵ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  trigcount : 8;  /* bit[0-7] : 8-bit����ֵ�������ӳ�ָ������words�������trigger��д�����ᵼ��trigger������reload������������Ԥ��ֵ�������ǵ�ǰ����ֵ�� */
        unsigned int  reserved  : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_coresightx_TRIGGER_COUNTER_VALUE_UNION;
#endif
#define SOC_coresightx_TRIGGER_COUNTER_VALUE_trigcount_START  (0)
#define SOC_coresightx_TRIGGER_COUNTER_VALUE_trigcount_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_coresightx_FSCR_UNION
 �ṹ˵��  : FSCR �Ĵ����ṹ���塣��ַƫ����:0x2308����ֵ:0x00000040�����:32
 �Ĵ���˵��: TPIU Formatterͬ���������Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cyccount : 12; /* bit[0-11] : 12-bit����ֵ�����������ԵĲ���ͬ��������ʼֵΪ0x40����ÿ64֡���ݺ����ͬ������ */
        unsigned int  reserved : 20; /* bit[12-31]: Reserved */
    } reg;
} SOC_coresightx_FSCR_UNION;
#endif
#define SOC_coresightx_FSCR_cyccount_START  (0)
#define SOC_coresightx_FSCR_cyccount_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_coresightx_ITCTRL_UNION
 �ṹ˵��  : ITCTRL �Ĵ����ṹ���塣��ַƫ����:0x2F00����ֵ:0x00000000�����:32
 �Ĵ���˵��: TPIU���ɲ���ģʽ���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ime      : 1;  /* bit[0]   : ���ɲ���ģʽ����λ��
                                                   0����������ģʽ
                                                   1�����ɲ���ģʽ */
        unsigned int  reserved : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_coresightx_ITCTRL_UNION;
#endif
#define SOC_coresightx_ITCTRL_ime_START       (0)
#define SOC_coresightx_ITCTRL_ime_END         (0)


/*****************************************************************************
 �ṹ��    : SOC_coresightx_RSZ_UNION
 �ṹ˵��  : RSZ �Ĵ����ṹ���塣��ַƫ����:0x3004����ֵ:0x00000400�����:32
 �Ĵ���˵��: ETR RAM size�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rsz      : 31; /* bit[0-30]: trace buffer�Ĵ�С����32-bit wordΪ��λ����1KBʱ���Ĵ���ֵΪ0x00000100 */
        unsigned int  reserved : 1;  /* bit[31]  : Reserved */
    } reg;
} SOC_coresightx_RSZ_UNION;
#endif
#define SOC_coresightx_RSZ_rsz_START       (0)
#define SOC_coresightx_RSZ_rsz_END         (30)


/*****************************************************************************
 �ṹ��    : SOC_coresightx_CTL_UNION
 �ṹ˵��  : CTL �Ĵ����ṹ���塣��ַƫ����:0x3020����ֵ:0x00000000�����:32
 �Ĵ���˵��: ETR���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tracecapten : 1;  /* bit[0]   : ����trace���ݵĲ�׽ */
        unsigned int  reserved    : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_coresightx_CTL_UNION;
#endif
#define SOC_coresightx_CTL_tracecapten_START  (0)
#define SOC_coresightx_CTL_tracecapten_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_coresightx_DBALO_UNION
 �ṹ˵��  : DBALO �Ĵ����ṹ���塣��ַƫ����:0x3118����ֵ:0x00000000�����:32
 �Ĵ���˵��: ETR����buffer��ַ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bufaddrlo : 32; /* bit[0-31]: ��Ϊtrace buffer��ϵͳ�ڴ�ĵ�32-bit��ַ */
    } reg;
} SOC_coresightx_DBALO_UNION;
#endif
#define SOC_coresightx_DBALO_bufaddrlo_START  (0)
#define SOC_coresightx_DBALO_bufaddrlo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_coresightx_CTICONTROL_UNION
 �ṹ˵��  : CTICONTROL �Ĵ����ṹ���塣��ַƫ����:0x4000����ֵ:0x00000000�����:32
 �Ĵ���˵��: CTI���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  glben    : 1;  /* bit[0]   : CTI����ʹ�ܿ���λ
                                                   0��disabled
                                                   1��enabled */
        unsigned int  reserved : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_coresightx_CTICONTROL_UNION;
#endif
#define SOC_coresightx_CTICONTROL_glben_START     (0)
#define SOC_coresightx_CTICONTROL_glben_END       (0)


/*****************************************************************************
 �ṹ��    : SOC_coresightx_CTIINEN0_UNION
 �ṹ˵��  : CTIINEN0 �Ĵ����ṹ���塣��ַƫ����:0x4020����ֵ:0x00000000�����:32
 �Ĵ���˵��: CTItrigger0��channelʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  triginen : 4;  /* bit[0-3] : ʹ��trigger�¼�����Ӧchannel��ӳ��
                                                   0��disable CTITRIGIN����Ӧchannel��ӳ��
                                                   1��enable CTITRIGIN����Ӧchannel��ӳ�� */
        unsigned int  reserved : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_coresightx_CTIINEN0_UNION;
#endif
#define SOC_coresightx_CTIINEN0_triginen_START  (0)
#define SOC_coresightx_CTIINEN0_triginen_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_coresightx_CTIGATE_UNION
 �ṹ˵��  : CTIGATE �Ĵ����ṹ���塣��ַƫ����:0x4140����ֵ:0x0000000F�����:32
 �Ĵ���˵��: CTI channelʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctigateen0 : 1;  /* bit[0]   : ʹ��ͨ��0
                                                     0��disable CTICHOUT0
                                                     1��enable CTICHOUT0 */
        unsigned int  ctigateen1 : 1;  /* bit[1]   : ʹ��ͨ��1
                                                     0��disable CTICHOUT1
                                                     1��enable CTICHOUT1 */
        unsigned int  ctigateen2 : 1;  /* bit[2]   : ʹ��ͨ��2
                                                     0��disable CTICHOUT2
                                                     1��enable CTICHOUT2 */
        unsigned int  ctigateen3 : 1;  /* bit[3]   : ʹ��ͨ��3
                                                     0��disable CTICHOUT3
                                                     1��enable CTICHOUT3 */
        unsigned int  reserved   : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_coresightx_CTIGATE_UNION;
#endif
#define SOC_coresightx_CTIGATE_ctigateen0_START  (0)
#define SOC_coresightx_CTIGATE_ctigateen0_END    (0)
#define SOC_coresightx_CTIGATE_ctigateen1_START  (1)
#define SOC_coresightx_CTIGATE_ctigateen1_END    (1)
#define SOC_coresightx_CTIGATE_ctigateen2_START  (2)
#define SOC_coresightx_CTIGATE_ctigateen2_END    (2)
#define SOC_coresightx_CTIGATE_ctigateen3_START  (3)
#define SOC_coresightx_CTIGATE_ctigateen3_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_coresightx_STMHEER_UNION
 �ṹ˵��  : STMHEER �Ĵ����ṹ���塣��ַƫ����:0x5D00����ֵ:0x00000000�����:32
 �Ĵ���˵��: STMӲ���¼�ʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  heen : 32; /* bit[0-31]: Ӳ������¼�ʹ�ܣ�ÿbit��Ӧ1���¼���
                                               0��Ӳ�¼�disabled
                                               1��Ӳ�¼�enabled */
    } reg;
} SOC_coresightx_STMHEER_UNION;
#endif
#define SOC_coresightx_STMHEER_heen_START  (0)
#define SOC_coresightx_STMHEER_heen_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_coresightx_STMSPER_UNION
 �ṹ˵��  : STMSPER �Ĵ����ṹ���塣��ַƫ����:0x5E00����ֵ:0x00000000�����:32
 �Ĵ���˵��: STM�����˿�ʹ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  spe : 32; /* bit[0-31]: �����˿�ʹ�ܿ���ÿbit��Ӧһ���˿�
                                              0���ö˿�disable
                                              1���ö˿�enable */
    } reg;
} SOC_coresightx_STMSPER_UNION;
#endif
#define SOC_coresightx_STMSPER_spe_START  (0)
#define SOC_coresightx_STMSPER_spe_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_coresightx_STMTCSR_UNION
 �ṹ˵��  : STMTCSR �Ĵ����ṹ���塣��ַƫ����:0x5E80����ֵ:0x00000004�����:32
 �Ĵ���˵��: STM trace������״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en       : 1;  /* bit[0]    : STMȫ��ʹ��
                                                    0��STM disabled
                                                    1��STM enabled */
        unsigned int  tsen     : 1;  /* bit[1]    : ����ʱ��������Ƿ񱻺���
                                                    0��timestamp disabled������ʱ��������󱻺���
                                                    1��timestamp enabled�����ɼ����˿�ѡ��timestamping������ʱ��� */
        unsigned int  syncen   : 1;  /* bit[2]    : STMͬ�����ƼĴ������á� */
        unsigned int  reserved_0: 2;  /* bit[3-4]  : Reserved */
        unsigned int  compen   : 1;  /* bit[5]    : �����˿�����ѹ��ʹ��
                                                    0��ѹ��disabled��������ԭʼsize���д���
                                                    1��ѹ��enabled�����ݱ�ѹ���Խ�ʡ���� */
        unsigned int  reserved_1: 10; /* bit[6-15] : Reserved */
        unsigned int  traceid  : 7;  /* bit[16-22]: ATB trace ID */
        unsigned int  busy     : 1;  /* bit[23]   : 0��STM is not busy
                                                    1��STM is busy */
        unsigned int  reserved_2: 8;  /* bit[24-31]: Reserved */
    } reg;
} SOC_coresightx_STMTCSR_UNION;
#endif
#define SOC_coresightx_STMTCSR_en_START        (0)
#define SOC_coresightx_STMTCSR_en_END          (0)
#define SOC_coresightx_STMTCSR_tsen_START      (1)
#define SOC_coresightx_STMTCSR_tsen_END        (1)
#define SOC_coresightx_STMTCSR_syncen_START    (2)
#define SOC_coresightx_STMTCSR_syncen_END      (2)
#define SOC_coresightx_STMTCSR_compen_START    (5)
#define SOC_coresightx_STMTCSR_compen_END      (5)
#define SOC_coresightx_STMTCSR_traceid_START   (16)
#define SOC_coresightx_STMTCSR_traceid_END     (22)
#define SOC_coresightx_STMTCSR_busy_START      (23)
#define SOC_coresightx_STMTCSR_busy_END        (23)


/*****************************************************************************
 �ṹ��    : SOC_coresightx_ETFCTL_UNION
 �ṹ˵��  : ETFCTL �Ĵ����ṹ���塣��ַƫ����:0x6020����ֵ:0x00000000�����:32
 �Ĵ���˵��: ETF���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tracecapten : 1;  /* bit[0]   : ����trace���ݵĲ�׽ */
        unsigned int  reserved    : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_coresightx_ETFCTL_UNION;
#endif
#define SOC_coresightx_ETFCTL_tracecapten_START  (0)
#define SOC_coresightx_ETFCTL_tracecapten_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_coresightx_ETFMODE_UNION
 �ṹ˵��  : ETFMODE �Ĵ����ṹ���塣��ַƫ����:0x6028����ֵ:0x00000000�����:32
 �Ĵ���˵��: ETF����ģʽ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 2;  /* bit[0-1] : ѡ��ETF�Ĺ���ģʽ��
                                                   11��Reserved
                                                   10��Hardware FIFO mode
                                                   01��Software FIFO mode
                                                   00��Circular Buffer mode */
        unsigned int  reserved : 30; /* bit[2-31]: Reserved */
    } reg;
} SOC_coresightx_ETFMODE_UNION;
#endif
#define SOC_coresightx_ETFMODE_mode_START      (0)
#define SOC_coresightx_ETFMODE_mode_END        (1)


/*****************************************************************************
 �ṹ��    : SOC_coresightx_ETFITCTRL_UNION
 �ṹ˵��  : ETFITCTRL �Ĵ����ṹ���塣��ַƫ����:0x6F00����ֵ:0x00000000�����:32
 �Ĵ���˵��: ETF����ģʽ���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  integrationmode : 1;  /* bit[0]   : ����ETF�ڹ���ģʽ�ͼ���ģʽ֮���л���
                                                          0��disable integration mode
                                                          1��enable integration mode */
        unsigned int  reserved        : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_coresightx_ETFITCTRL_UNION;
#endif
#define SOC_coresightx_ETFITCTRL_integrationmode_START  (0)
#define SOC_coresightx_ETFITCTRL_integrationmode_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_coresightx_TSCNTCR_UNION
 �ṹ˵��  : TSCNTCR �Ĵ����ṹ���塣��ַƫ����:0x7000����ֵ:0x00000000�����:32
 �Ĵ���˵��: timestamp�������ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en       : 1;  /* bit[0]   : ʹ�ܿ���
                                                   0��������disabled
                                                   1��������enabled */
        unsigned int  hdbg     : 1;  /* bit[1]   : Halt on debug����
                                                   0��HLTDBG�źŶԼ�������Ӱ��
                                                   1��HLTDBG�ź���Чʱ����ͣ���� */
        unsigned int  reserved : 30; /* bit[2-31]: Reserved */
    } reg;
} SOC_coresightx_TSCNTCR_UNION;
#endif
#define SOC_coresightx_TSCNTCR_en_START        (0)
#define SOC_coresightx_TSCNTCR_en_END          (0)
#define SOC_coresightx_TSCNTCR_hdbg_START      (1)
#define SOC_coresightx_TSCNTCR_hdbg_END        (1)


/*****************************************************************************
 �ṹ��    : SOC_coresightx_TSCNTCVLW_UNION
 �ṹ˵��  : TSCNTCVLW �Ĵ����ṹ���塣��ַƫ����:0x7008����ֵ:0x00000000�����:32
 �Ĵ���˵��: timestamp��ǰ����ֵ��λ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cntcvlw : 32; /* bit[0-31]: ��ǰ����ֵ��bit[31:0] */
    } reg;
} SOC_coresightx_TSCNTCVLW_UNION;
#endif
#define SOC_coresightx_TSCNTCVLW_cntcvlw_START  (0)
#define SOC_coresightx_TSCNTCVLW_cntcvlw_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_coresightx_TSCNTCVUP_UNION
 �ṹ˵��  : TSCNTCVUP �Ĵ����ṹ���塣��ַƫ����:0x700C����ֵ:0x00000000�����:32
 �Ĵ���˵��: timestamp��ǰ����ֵ��λ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cntcvup : 32; /* bit[0-31]: ��ǰ����ֵ��bit[63:32] */
    } reg;
} SOC_coresightx_TSCNTCVUP_UNION;
#endif
#define SOC_coresightx_TSCNTCVUP_cntcvup_START  (0)
#define SOC_coresightx_TSCNTCVUP_cntcvup_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_coresightx_TSCNTCVLW_RO_UNION
 �ṹ˵��  : TSCNTCVLW_RO �Ĵ����ṹ���塣��ַƫ����:0x8000����ֵ:0x00000000�����:32
 �Ĵ���˵��: timestamp��ǰ����ֵ��λ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cntcvlw_ro : 32; /* bit[0-31]: ��ǰ����ֵ��bit[31:0]��ֻ������ */
    } reg;
} SOC_coresightx_TSCNTCVLW_RO_UNION;
#endif
#define SOC_coresightx_TSCNTCVLW_RO_cntcvlw_ro_START  (0)
#define SOC_coresightx_TSCNTCVLW_RO_cntcvlw_ro_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_coresightx_TSCNTCVUP_RO_UNION
 �ṹ˵��  : TSCNTCVUP_RO �Ĵ����ṹ���塣��ַƫ����:0x8004����ֵ:0x00000000�����:32
 �Ĵ���˵��: timestamp��ǰ����ֵ��λ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cntcvup_ro : 32; /* bit[0-31]: ��ǰ����ֵ��bit[63:32]��ֻ������ */
    } reg;
} SOC_coresightx_TSCNTCVUP_RO_UNION;
#endif
#define SOC_coresightx_TSCNTCVUP_RO_cntcvup_ro_START  (0)
#define SOC_coresightx_TSCNTCVUP_RO_cntcvup_ro_END    (31)






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

#endif /* end of soc_coresightx_interface.h */
