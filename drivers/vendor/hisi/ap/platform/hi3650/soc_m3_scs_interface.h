/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_m3_scs_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-23 11:27:30
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��23��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_M3_SCS.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_M3_SCS_INTERFACE_H__
#define __SOC_M3_SCS_INTERFACE_H__

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
/* �Ĵ���˵����Intrrupt Controller Type Register
   λ����UNION�ṹ:  SOC_M3_SCS_ICTR_UNION */
#define SOC_M3_SCS_ICTR_ADDR(base)                    ((base) + (0x004))

/* �Ĵ���˵����Auxiliary Control Register
   λ����UNION�ṹ:  SOC_M3_SCS_ACTLR_UNION */
#define SOC_M3_SCS_ACTLR_ADDR(base)                   ((base) + (0x008))

/* �Ĵ���˵����SysTick Control and Status Register
   λ����UNION�ṹ:  SOC_M3_SCS_STCSR_UNION */
#define SOC_M3_SCS_STCSR_ADDR(base)                   ((base) + (0x010))

/* �Ĵ���˵����SysTick Reload Value Register
   λ����UNION�ṹ:  SOC_M3_SCS_STRVR_UNION */
#define SOC_M3_SCS_STRVR_ADDR(base)                   ((base) + (0x014))

/* �Ĵ���˵����SysTick Current Value Register
   λ����UNION�ṹ:  SOC_M3_SCS_STCVR_UNION */
#define SOC_M3_SCS_STCVR_ADDR(base)                   ((base) + (0x018))

/* �Ĵ���˵����SysTick Calibration Value Register
   λ����UNION�ṹ:  SOC_M3_SCS_STCR_UNION */
#define SOC_M3_SCS_STCR_ADDR(base)                    ((base) + (0x01C))

/* �Ĵ���˵����Interrupt Set-Enable Register n
   λ����UNION�ṹ:  SOC_M3_SCS_NVIC_ISERn_UNION */
#define SOC_M3_SCS_NVIC_ISERn_ADDR(base, n)           ((base) + (0x100+(n)*4))

/* �Ĵ���˵����Interrupt Clear-Enable Register n
   λ����UNION�ṹ:  SOC_M3_SCS_NVIC_ICERn_UNION */
#define SOC_M3_SCS_NVIC_ICERn_ADDR(base, n)           ((base) + (0x180+(n)*4))

/* �Ĵ���˵����Interrupt Set-Pending Register n
   λ����UNION�ṹ:  SOC_M3_SCS_NVIC_ISPRn_UNION */
#define SOC_M3_SCS_NVIC_ISPRn_ADDR(base, n)           ((base) + (0x200+(n)*4))

/* �Ĵ���˵����Interrupt Clear-Pending Register n
   λ����UNION�ṹ:  SOC_M3_SCS_NVIC_ICPRn_UNION */
#define SOC_M3_SCS_NVIC_ICPRn_ADDR(base, n)           ((base) + (0x280+(n)*4))

/* �Ĵ���˵����Interrupt Active Bit Register n
   λ����UNION�ṹ:  SOC_M3_SCS_NVIC_IABRn_UNION */
#define SOC_M3_SCS_NVIC_IABRn_ADDR(base, n)           ((base) + (0x300+(n)*4))

/* �Ĵ���˵����Interrupt Priority Register m
   λ����UNION�ṹ:  SOC_M3_SCS_NVIC_IPRm_UNION */
#define SOC_M3_SCS_NVIC_IPRm_ADDR(base, m)            ((base) + (0x400+(m)*4))

/* �Ĵ���˵����CPUID Base Register
   λ����UNION�ṹ:  SOC_M3_SCS_CPUID_UNION */
#define SOC_M3_SCS_CPUID_ADDR(base)                   ((base) + (0xD00))

/* �Ĵ���˵����Interrupt Control and State Register
   λ����UNION�ṹ:  SOC_M3_SCS_ICSR_UNION */
#define SOC_M3_SCS_ICSR_ADDR(base)                    ((base) + (0xD04))

/* �Ĵ���˵����Vector Table Offset Register
   λ����UNION�ṹ:  SOC_M3_SCS_VTOR_UNION */
#define SOC_M3_SCS_VTOR_ADDR(base)                    ((base) + (0xD08))

/* �Ĵ���˵����Application Interrupt and Reset Control Register
   λ����UNION�ṹ:  SOC_M3_SCS_AIRCR_UNION */
#define SOC_M3_SCS_AIRCR_ADDR(base)                   ((base) + (0xD0C))

/* �Ĵ���˵����System Control Register
   λ����UNION�ṹ:  SOC_M3_SCS_SCR_UNION */
#define SOC_M3_SCS_SCR_ADDR(base)                     ((base) + (0xD10))

/* �Ĵ���˵����Configuration and Control Register
   λ����UNION�ṹ:  SOC_M3_SCS_CCR_UNION */
#define SOC_M3_SCS_CCR_ADDR(base)                     ((base) + (0xD14))

/* �Ĵ���˵����System Handler Priorty Register 1
   λ����UNION�ṹ:  SOC_M3_SCS_SHPR1_UNION */
#define SOC_M3_SCS_SHPR1_ADDR(base)                   ((base) + (0xD18))

/* �Ĵ���˵����System Handler Priorty Register 2
   λ����UNION�ṹ:  SOC_M3_SCS_SHPR2_UNION */
#define SOC_M3_SCS_SHPR2_ADDR(base)                   ((base) + (0xD1C))

/* �Ĵ���˵����System Handler Priorty Register 3
   λ����UNION�ṹ:  SOC_M3_SCS_SHPR3_UNION */
#define SOC_M3_SCS_SHPR3_ADDR(base)                   ((base) + (0xD20))

/* �Ĵ���˵����System Handler Control and State Register
   λ����UNION�ṹ:  SOC_M3_SCS_SHCSR_UNION */
#define SOC_M3_SCS_SHCSR_ADDR(base)                   ((base) + (0xD24))

/* �Ĵ���˵����Configurable Fault Status Registers
   λ����UNION�ṹ:  SOC_M3_SCS_CFSR_UNION */
#define SOC_M3_SCS_CFSR_ADDR(base)                    ((base) + (0xD28))

/* �Ĵ���˵����HardFault Status Register
   λ����UNION�ṹ:  SOC_M3_SCS_HFSR_UNION */
#define SOC_M3_SCS_HFSR_ADDR(base)                    ((base) + (0xD2C))

/* �Ĵ���˵����Debug Fault Status Register
   λ����UNION�ṹ:  SOC_M3_SCS_DFSR_UNION */
#define SOC_M3_SCS_DFSR_ADDR(base)                    ((base) + (0xD30))

/* �Ĵ���˵����MemManage Fault Address Register
   λ����UNION�ṹ:  SOC_M3_SCS_MMFAR_UNION */
#define SOC_M3_SCS_MMFAR_ADDR(base)                   ((base) + (0xD34))

/* �Ĵ���˵����BusFault Address Register
   λ����UNION�ṹ:  SOC_M3_SCS_BFAR_UNION */
#define SOC_M3_SCS_BFAR_ADDR(base)                    ((base) + (0xD38))

/* �Ĵ���˵����Auxiliary Fault Status Register
   λ����UNION�ṹ:  SOC_M3_SCS_AFSR_UNION */
#define SOC_M3_SCS_AFSR_ADDR(base)                    ((base) + (0xD3C))

/* �Ĵ���˵����Processor Feature Register 0
   λ����UNION�ṹ:  SOC_M3_SCS_ID_PFR0_UNION */
#define SOC_M3_SCS_ID_PFR0_ADDR(base)                 ((base) + (0xD40))

/* �Ĵ���˵����Processor Feature Register 1
   λ����UNION�ṹ:  SOC_M3_SCS_ID_PFR1_UNION */
#define SOC_M3_SCS_ID_PFR1_ADDR(base)                 ((base) + (0xD44))

/* �Ĵ���˵����Debug Features Register 0
   λ����UNION�ṹ:  SOC_M3_SCS_ID_DFR0_UNION */
#define SOC_M3_SCS_ID_DFR0_ADDR(base)                 ((base) + (0xD48))

/* �Ĵ���˵����Auxiliary Features Register 0
   λ����UNION�ṹ:  SOC_M3_SCS_ID_AFR0_UNION */
#define SOC_M3_SCS_ID_AFR0_ADDR(base)                 ((base) + (0xD4C))

/* �Ĵ���˵����Memory Model Feature Register 0
   λ����UNION�ṹ:  SOC_M3_SCS_ID_MMFR0_UNION */
#define SOC_M3_SCS_ID_MMFR0_ADDR(base)                ((base) + (0xD50))

/* �Ĵ���˵����Memory Model Feature Register 1
   λ����UNION�ṹ:  SOC_M3_SCS_ID_MMFR1_UNION */
#define SOC_M3_SCS_ID_MMFR1_ADDR(base)                ((base) + (0xD54))

/* �Ĵ���˵����Memory Model Feature Register 2
   λ����UNION�ṹ:  SOC_M3_SCS_ID_MMFR2_UNION */
#define SOC_M3_SCS_ID_MMFR2_ADDR(base)                ((base) + (0xD58))

/* �Ĵ���˵����Memory Model Feature Register 3
   λ����UNION�ṹ:  SOC_M3_SCS_ID_MMFR3_UNION */
#define SOC_M3_SCS_ID_MMFR3_ADDR(base)                ((base) + (0xD5C))

/* �Ĵ���˵����Instruction Set Attributes Register 0
   λ����UNION�ṹ:  SOC_M3_SCS_ID_ISAR0_UNION */
#define SOC_M3_SCS_ID_ISAR0_ADDR(base)                ((base) + (0xD60))

/* �Ĵ���˵����Instruction Set Attributes Register 1
   λ����UNION�ṹ:  SOC_M3_SCS_ID_ISAR1_UNION */
#define SOC_M3_SCS_ID_ISAR1_ADDR(base)                ((base) + (0xD64))

/* �Ĵ���˵����Instruction Set Attributes Register 2
   λ����UNION�ṹ:  SOC_M3_SCS_ID_ISAR2_UNION */
#define SOC_M3_SCS_ID_ISAR2_ADDR(base)                ((base) + (0xD68))

/* �Ĵ���˵����Instruction Set Attributes Register 3
   λ����UNION�ṹ:  SOC_M3_SCS_ID_ISAR3_UNION */
#define SOC_M3_SCS_ID_ISAR3_ADDR(base)                ((base) + (0xD6C))

/* �Ĵ���˵����Instruction Set Attributes Register 4
   λ����UNION�ṹ:  SOC_M3_SCS_ID_ISAR4_UNION */
#define SOC_M3_SCS_ID_ISAR4_ADDR(base)                ((base) + (0xD70))

/* �Ĵ���˵����Coprocessor Access Control Register
   λ����UNION�ṹ:  SOC_M3_SCS_CPACR_UNION */
#define SOC_M3_SCS_CPACR_ADDR(base)                   ((base) + (0xD88))

/* �Ĵ���˵����Software Triggered Interrupt Register
   λ����UNION�ṹ:  SOC_M3_SCS_STIR_UNION */
#define SOC_M3_SCS_STIR_ADDR(base)                    ((base) + (0xF00))





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
 �ṹ��    : SOC_M3_SCS_ICTR_UNION
 �ṹ˵��  : ICTR �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x00000003�����:32
 �Ĵ���˵��: Intrrupt Controller Type Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intlinesnum : 4;  /* bit[0-3] : NVIC���֧��240���ж� */
        unsigned int  reserved    : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_M3_SCS_ICTR_UNION;
#endif
#define SOC_M3_SCS_ICTR_intlinesnum_START  (0)
#define SOC_M3_SCS_ICTR_intlinesnum_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_ACTLR_UNION
 �ṹ˵��  : ACTLR �Ĵ����ṹ���塣��ַƫ����:0x008����ֵ:0x00000000�����:32
 �Ĵ���˵��: Auxiliary Control Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dismcycint : 1;  /* bit[0]   : ��ֹ������ָ����жϡ���������ж���Ӧ�ӳ١� */
        unsigned int  disdefwbuf : 1;  /* bit[1]   : ��ֹ��Ĭ�ϵĵ�ַ�ռ����ʱʹ��write buffer��
                                                     ���е�bus fault����Ϊprecise bus fault
                                                     ���ǻή�ʹ��������� */
        unsigned int  disfold    : 1;  /* bit[2]   : ��ֹIT floding���ܡ� */
        unsigned int  reserved   : 29; /* bit[3-31]: Reserved */
    } reg;
} SOC_M3_SCS_ACTLR_UNION;
#endif
#define SOC_M3_SCS_ACTLR_dismcycint_START  (0)
#define SOC_M3_SCS_ACTLR_dismcycint_END    (0)
#define SOC_M3_SCS_ACTLR_disdefwbuf_START  (1)
#define SOC_M3_SCS_ACTLR_disdefwbuf_END    (1)
#define SOC_M3_SCS_ACTLR_disfold_START     (2)
#define SOC_M3_SCS_ACTLR_disfold_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_STCSR_UNION
 �ṹ˵��  : STCSR �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x00000000�����:32
 �Ĵ���˵��: SysTick Control and Status Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enable    : 1;  /* bit[0]    : 0����ֹ������
                                                     1��ʹ�ܼ���������������ST_RVR�Ĵ�����ȡreloadֵ��ʼ���������������COUNTFLAG��Ϊ1����ѡ���Ƿ�����TICKINT��Ȼ���ٻ�ȡreloadֵ���¿�ʼ������ */
        unsigned int  tickint   : 1;  /* bit[1]    : 0����������󲻹���SysTick handler���������ͨ��COUNTFLAG���ж��Ƿ�Ƶ���
                                                     1��������������SysTick handler */
        unsigned int  clksource : 1;  /* bit[2]    : 0���ⲿ�ο�ʱ��(STCLK)
                                                     1��coreʱ��(FCLK)
                                                     ���û���ⲿ�ο�ʱ�ӣ�������Ϊ1��Coreʱ��Ƶ�ʱ������ⲿ�ο�ʱ�ӵ�2.5�����ϣ��������ֵ����Ԥ�� */
        unsigned int  reserved_0: 13; /* bit[3-15] : Reserved */
        unsigned int  countflag : 1;  /* bit[16]   : ����һ�α�����ʼ��������Ϊ0ʱ����1
                                                     ������Ĵ������κβ��֣�������ֵ���㣻
                                                     ���������ͨ��DAP���ʣ�ֻ�е�MasterType����Ϊ0������£���ֵ���ܱ����㣬���򲻻�ı� */
        unsigned int  reserved_1: 15; /* bit[17-31]: Reserved */
    } reg;
} SOC_M3_SCS_STCSR_UNION;
#endif
#define SOC_M3_SCS_STCSR_enable_START     (0)
#define SOC_M3_SCS_STCSR_enable_END       (0)
#define SOC_M3_SCS_STCSR_tickint_START    (1)
#define SOC_M3_SCS_STCSR_tickint_END      (1)
#define SOC_M3_SCS_STCSR_clksource_START  (2)
#define SOC_M3_SCS_STCSR_clksource_END    (2)
#define SOC_M3_SCS_STCSR_countflag_START  (16)
#define SOC_M3_SCS_STCSR_countflag_END    (16)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_STRVR_UNION
 �ṹ˵��  : STRVR �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x00000000�����:32
 �Ĵ���˵��: SysTick Reload Value Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reload   : 24; /* bit[0-23] : ����������װ�ص�ֵ����ΧΪ1��0x00FFFFFF������Ϊ0��Ч
                                                    ����ΪN���򵹼���N+1��ʱ�����ں�������󣬲��Ҳ���ѭ���������ÿ��tick�ж��������µ�reloadֵM���򵹼���M��ʱ�����ڲ������� */
        unsigned int  reserved : 8;  /* bit[24-31]: Reserved */
    } reg;
} SOC_M3_SCS_STRVR_UNION;
#endif
#define SOC_M3_SCS_STRVR_reload_START    (0)
#define SOC_M3_SCS_STRVR_reload_END      (23)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_STCVR_UNION
 �ṹ˵��  : STCVR �Ĵ����ṹ���塣��ַƫ����:0x018����ֵ:0x00000000�����:32
 �Ĵ���˵��: SysTick Current Value Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  current  : 24; /* bit[0-23] : ������ȡ��ǰ��������ֵ
                                                    д��д�壬��д�üĴ������򽫼Ĵ������㣬�������ST_CSR�Ĵ�����COUNTFLAGλ */
        unsigned int  reserved : 8;  /* bit[24-31]: Reserved */
    } reg;
} SOC_M3_SCS_STCVR_UNION;
#endif
#define SOC_M3_SCS_STCVR_current_START   (0)
#define SOC_M3_SCS_STCVR_current_END     (23)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_STCR_UNION
 �ṹ˵��  : STCR �Ĵ����ṹ���塣��ַƫ����:0x01C����ֵ:0x00000000�����:32
 �Ĵ���˵��: SysTick Calibration Value Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tenms    : 24; /* bit[0-23] : ���ڼ���׼ȷ��10ms��У׼ֵ��SKEWλ����Ϊ1 */
        unsigned int  reserved : 6;  /* bit[24-29]: Reserved */
        unsigned int  skew     : 1;  /* bit[30]   : 0��У׼ֵ��׼ȷ��10ms
                                                    1��У׼ֵ����׼ȷ��10ms */
        unsigned int  noref    : 1;  /* bit[31]   : 0���вο�ʱ��
                                                    1���޲ο�ʱ�� */
    } reg;
} SOC_M3_SCS_STCR_UNION;
#endif
#define SOC_M3_SCS_STCR_tenms_START     (0)
#define SOC_M3_SCS_STCR_tenms_END       (23)
#define SOC_M3_SCS_STCR_skew_START      (30)
#define SOC_M3_SCS_STCR_skew_END        (30)
#define SOC_M3_SCS_STCR_noref_START     (31)
#define SOC_M3_SCS_STCR_noref_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_NVIC_ISERn_UNION
 �ṹ˵��  : NVIC_ISERn �Ĵ����ṹ���塣��ַƫ����:0x100+(n)*4����ֵ:0x00000000�����:32
 �Ĵ���˵��: Interrupt Set-Enable Register n
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  setena : 32; /* bit[0-31]: �ж�ʹ�ܿ��ƣ�ÿbit��Ӧһ���ж�
                                                 On reads 0 = Interrupt disabled.
                                                  1 = Interrupt enabled.
                                                 On writes 0 = No effect.
                                                  1 = Enable interrupt. */
    } reg;
} SOC_M3_SCS_NVIC_ISERn_UNION;
#endif
#define SOC_M3_SCS_NVIC_ISERn_setena_START  (0)
#define SOC_M3_SCS_NVIC_ISERn_setena_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_NVIC_ICERn_UNION
 �ṹ˵��  : NVIC_ICERn �Ĵ����ṹ���塣��ַƫ����:0x180+(n)*4����ֵ:0x00000000�����:32
 �Ĵ���˵��: Interrupt Clear-Enable Register n
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  clrena : 32; /* bit[0-31]: �ж�ȥʹ�ܿ��ƣ�ÿbit��Ӧһ���ж�
                                                 On reads 0 = Interrupt disabled.
                                                  1 = Interrupt enabled.
                                                 On writes 0 = No effect.
                                                  1 = Disable interrupt. */
    } reg;
} SOC_M3_SCS_NVIC_ICERn_UNION;
#endif
#define SOC_M3_SCS_NVIC_ICERn_clrena_START  (0)
#define SOC_M3_SCS_NVIC_ICERn_clrena_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_NVIC_ISPRn_UNION
 �ṹ˵��  : NVIC_ISPRn �Ĵ����ṹ���塣��ַƫ����:0x200+(n)*4����ֵ:0x00000000�����:32
 �Ĵ���˵��: Interrupt Set-Pending Register n
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  setpend : 32; /* bit[0-31]: �ж�pending״̬���ƣ�ÿbit��Ӧһ���ж�
                                                  On reads 0 = Interrupt is not pending.
                                                   1 = Interrupt is pending.
                                                  On writes 0 = No effect.
                                                   1 = Changes state of interrupt to pending. */
    } reg;
} SOC_M3_SCS_NVIC_ISPRn_UNION;
#endif
#define SOC_M3_SCS_NVIC_ISPRn_setpend_START  (0)
#define SOC_M3_SCS_NVIC_ISPRn_setpend_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_NVIC_ICPRn_UNION
 �ṹ˵��  : NVIC_ICPRn �Ĵ����ṹ���塣��ַƫ����:0x280+(n)*4����ֵ:0x00000000�����:32
 �Ĵ���˵��: Interrupt Clear-Pending Register n
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  clrpend : 32; /* bit[0-31]: �ж�pending״̬�����ÿbit��Ӧһ���ж�
                                                  On reads 0 = Interrupt is not pending.
                                                   1 = Interrupt is pending.
                                                  On writes 0 = No effect.
                                                   1 = Clears the pending state of the interrupt. */
    } reg;
} SOC_M3_SCS_NVIC_ICPRn_UNION;
#endif
#define SOC_M3_SCS_NVIC_ICPRn_clrpend_START  (0)
#define SOC_M3_SCS_NVIC_ICPRn_clrpend_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_NVIC_IABRn_UNION
 �ṹ˵��  : NVIC_IABRn �Ĵ����ṹ���塣��ַƫ����:0x300+(n)*4����ֵ:0x00000000�����:32
 �Ĵ���˵��: Interrupt Active Bit Register n
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  active : 32; /* bit[0-31]: �ж�active״̬��ÿbit��Ӧһ���ж�
                                                 0 = Interrupt not active.
                                                 1 = Interrupt active. */
    } reg;
} SOC_M3_SCS_NVIC_IABRn_UNION;
#endif
#define SOC_M3_SCS_NVIC_IABRn_active_START  (0)
#define SOC_M3_SCS_NVIC_IABRn_active_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_NVIC_IPRm_UNION
 �ṹ˵��  : NVIC_IPRm �Ĵ����ṹ���塣��ַƫ����:0x400+(m)*4����ֵ:0x00000000�����:32
 �Ĵ���˵��: Interrupt Priority Register m
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pri_n0 : 8;  /* bit[0-7]  : For register NVIC_IPRm, priority of interrupt number 4m */
        unsigned int  pri_n1 : 8;  /* bit[8-15] : For register NVIC_IPRm, priority of interrupt number 4m+1. */
        unsigned int  pri_n2 : 8;  /* bit[16-23]: For register NVIC_IPRm, priority of interrupt number 4m+2. */
        unsigned int  pri_n3 : 8;  /* bit[24-31]: For register NVIC_IPRm, priority of interrupt number 4m+3. */
    } reg;
} SOC_M3_SCS_NVIC_IPRm_UNION;
#endif
#define SOC_M3_SCS_NVIC_IPRm_pri_n0_START  (0)
#define SOC_M3_SCS_NVIC_IPRm_pri_n0_END    (7)
#define SOC_M3_SCS_NVIC_IPRm_pri_n1_START  (8)
#define SOC_M3_SCS_NVIC_IPRm_pri_n1_END    (15)
#define SOC_M3_SCS_NVIC_IPRm_pri_n2_START  (16)
#define SOC_M3_SCS_NVIC_IPRm_pri_n2_END    (23)
#define SOC_M3_SCS_NVIC_IPRm_pri_n3_START  (24)
#define SOC_M3_SCS_NVIC_IPRm_pri_n3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_CPUID_UNION
 �ṹ˵��  : CPUID �Ĵ����ṹ���塣��ַƫ����:0xD00����ֵ:0x412FC231�����:32
 �Ĵ���˵��: CPUID Base Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  revision    : 4;  /* bit[0-3]  : Revision */
        unsigned int  partno      : 12; /* bit[4-15] : [11:10] b11 = Cortex family
                                                       [9:8] b00 = version
                                                       [7:6] b00 = reserved
                                                       [5:4] b10 = M (v7-M)
                                                       [3:0] X = family member. Cortex-M3 family is b0011. */
        unsigned int  constant    : 4;  /* bit[16-19]: �̶�Ϊ0xF */
        unsigned int  variant     : 4;  /* bit[20-23]: �ɼ��ɾ���variantֵ */
        unsigned int  implementer : 8;  /* bit[24-31]: ARMΪ0x41 */
    } reg;
} SOC_M3_SCS_CPUID_UNION;
#endif
#define SOC_M3_SCS_CPUID_revision_START     (0)
#define SOC_M3_SCS_CPUID_revision_END       (3)
#define SOC_M3_SCS_CPUID_partno_START       (4)
#define SOC_M3_SCS_CPUID_partno_END         (15)
#define SOC_M3_SCS_CPUID_constant_START     (16)
#define SOC_M3_SCS_CPUID_constant_END       (19)
#define SOC_M3_SCS_CPUID_variant_START      (20)
#define SOC_M3_SCS_CPUID_variant_END        (23)
#define SOC_M3_SCS_CPUID_implementer_START  (24)
#define SOC_M3_SCS_CPUID_implementer_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_ICSR_UNION
 �ṹ˵��  : ICSR �Ĵ����ṹ���塣��ַƫ����:0xD04����ֵ:0x00000000�����:32
 �Ĵ���˵��: Interrupt Control and State Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vectactive  : 9;  /* bit[0-8]  : ��ǰ���ڴ����ISR��Ӧ���жϺţ�����NMI��Hard Fault
                                                       �ⲿ�жϴ�16�ſ�ʼ����INTISR[0]=16 */
        unsigned int  reserved_0  : 2;  /* bit[9-10] : Reserved */
        unsigned int  rettobase   : 1;  /* bit[11]   : This bit is 1 when the set of all active exceptions minus the IPSR_current_exception yields the empty set. */
        unsigned int  vectpending : 10; /* bit[12-21]: ��ʾ������ȼ������ISR��Ӧ���жϺ� */
        unsigned int  isrpending  : 1;  /* bit[22]   : �жϹ����־��������NMI��Fault�쳣
                                                       0���ж�û�й���
                                                       1���жϹ��� */
        unsigned int  isrpreempt  : 1;  /* bit[23]   : ����debugģʽ��ʹ�ã���ʾһ��������ж����¸����ڽ������� */
        unsigned int  reserved_1  : 1;  /* bit[24]   : Reserved */
        unsigned int  pendstclr   : 1;  /* bit[25]   : ���SysTick����
                                                       0�������SysTick����
                                                       1�����SysTick���� */
        unsigned int  pendstset   : 1;  /* bit[26]   : ����SysTick����
                                                       0��������SysTick
                                                       1������SysTick */
        unsigned int  pendsvclr   : 1;  /* bit[27]   : ���pendSV����
                                                       0�������pendSV����
                                                       1�����pendSV���� */
        unsigned int  pendsvset   : 1;  /* bit[28]   : ����pendSV����
                                                       0��������pendSV
                                                       1������pendSV */
        unsigned int  reserved_2  : 2;  /* bit[29-30]: Reserved */
        unsigned int  nmipendset  : 1;  /* bit[31]   : ����NMI�жϹ���
                                                       0��������NMI
                                                       1������NMI
                                                       һ������NMI����NMI�������ΪNMIû������λ */
    } reg;
} SOC_M3_SCS_ICSR_UNION;
#endif
#define SOC_M3_SCS_ICSR_vectactive_START   (0)
#define SOC_M3_SCS_ICSR_vectactive_END     (8)
#define SOC_M3_SCS_ICSR_rettobase_START    (11)
#define SOC_M3_SCS_ICSR_rettobase_END      (11)
#define SOC_M3_SCS_ICSR_vectpending_START  (12)
#define SOC_M3_SCS_ICSR_vectpending_END    (21)
#define SOC_M3_SCS_ICSR_isrpending_START   (22)
#define SOC_M3_SCS_ICSR_isrpending_END     (22)
#define SOC_M3_SCS_ICSR_isrpreempt_START   (23)
#define SOC_M3_SCS_ICSR_isrpreempt_END     (23)
#define SOC_M3_SCS_ICSR_pendstclr_START    (25)
#define SOC_M3_SCS_ICSR_pendstclr_END      (25)
#define SOC_M3_SCS_ICSR_pendstset_START    (26)
#define SOC_M3_SCS_ICSR_pendstset_END      (26)
#define SOC_M3_SCS_ICSR_pendsvclr_START    (27)
#define SOC_M3_SCS_ICSR_pendsvclr_END      (27)
#define SOC_M3_SCS_ICSR_pendsvset_START    (28)
#define SOC_M3_SCS_ICSR_pendsvset_END      (28)
#define SOC_M3_SCS_ICSR_nmipendset_START   (31)
#define SOC_M3_SCS_ICSR_nmipendset_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_VTOR_UNION
 �ṹ˵��  : VTOR �Ĵ����ṹ���塣��ַƫ����:0xD08����ֵ:0x00000000�����:32
 �Ĵ���˵��: Vector Table Offset Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 7;  /* bit[0-6]  : Reserved */
        unsigned int  tbloff   : 22; /* bit[7-28] : �������ƫ�Ƶ�ַ����ʾ��Code�����RAM�������͵�ַ��ʼ��ƫ�Ƶ�ַ������32-bit���� */
        unsigned int  tblabse  : 1;  /* bit[29]   : �������ַ�����ڴ������
                                                    0��Code����
                                                    1��RAM���� */
        unsigned int  reserved_1: 2;  /* bit[30-31]: Reserved */
    } reg;
} SOC_M3_SCS_VTOR_UNION;
#endif
#define SOC_M3_SCS_VTOR_tbloff_START    (7)
#define SOC_M3_SCS_VTOR_tbloff_END      (28)
#define SOC_M3_SCS_VTOR_tblabse_START   (29)
#define SOC_M3_SCS_VTOR_tblabse_END     (29)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_AIRCR_UNION
 �ṹ˵��  : AIRCR �Ĵ����ṹ���塣��ַƫ����:0xD0C����ֵ:0xFA050000�����:32
 �Ĵ���˵��: Application Interrupt and Reset Control Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vectreset           : 1;  /* bit[0]    : ϵͳ��λbit�����ڸ�λ��debugģ�����߼�����λ���塣
                                                               0������λϵͳ
                                                               1����λϵͳ
                                                               ��debugģʽ�£�ֻ�е�����������halt״̬��������
                                                               ע�⣺SYSRESETREQҲ�ᱻVECTRESET�������˽�������λ�����������Ҫͬʱ����1 */
        unsigned int  vectclractive       : 1;  /* bit[1]    : �����������λ������
                                                               0�������
                                                               1��������м�����жϡ�NMI��Fault��״̬��Ϣ
                                                               ��λ������debugʱ����һ��ȷ����״̬��
                                                               IPSR�Ĵ������ܸ�λӰ�졣 */
        unsigned int  sysresetreq         : 1;  /* bit[2]    : ���ø�λ���������SYSRESETREQ�źţ�����ϵͳ��λ�����ڸ�λ�ڲ���debugģ����������߼� */
        unsigned int  reserved_0          : 5;  /* bit[3-7]  : Reserved */
        unsigned int  prigroup            : 3;  /* bit[8-10] : ������ռ���ȼ��������ȼ��ķָ�λ
                                                               0�� [7.1] ��ռ���ȼ�7bit�������ȼ�1bit
                                                               1�� [6.2] ��ռ���ȼ�6bit�������ȼ�2bit
                                                               2�� [5.3] ��ռ���ȼ�5bit�������ȼ�3bit
                                                               3�� [4.4] ��ռ���ȼ�4bit�������ȼ�4bit
                                                               4�� [3.5] ��ռ���ȼ�3bit�������ȼ�5bit
                                                               5�� [2.6] ��ռ���ȼ�2bit�������ȼ�6bit
                                                               6�� [1.7] ��ռ���ȼ�1bit�������ȼ�7bit
                                                               7�� [0.8] ����ռ���ȼ��������ȼ�8bit
                                                               ��ռ���ȼ���PRI���ȼ�λ��8bit����벿�֣���λ����ʾ�������ȼ����Ұ벿�֣���λ����ʾ */
        unsigned int  reserved_1          : 4;  /* bit[11-14]: Reserved */
        unsigned int  endianess           : 1;  /* bit[15]   : 0��С��
                                                               1�����
                                                               �ڸ�λʱ���������ź�BIGEND������ʱ���޷����� */
        unsigned int  vectkey_vectkeystat : 16; /* bit[16-31]: �ԸüĴ���д������������VECTKEYλд0x5FA�������޷����ļĴ���ֵ����λд����ֵ��Ч��������ʼ��Ϊ0xFA05 */
    } reg;
} SOC_M3_SCS_AIRCR_UNION;
#endif
#define SOC_M3_SCS_AIRCR_vectreset_START            (0)
#define SOC_M3_SCS_AIRCR_vectreset_END              (0)
#define SOC_M3_SCS_AIRCR_vectclractive_START        (1)
#define SOC_M3_SCS_AIRCR_vectclractive_END          (1)
#define SOC_M3_SCS_AIRCR_sysresetreq_START          (2)
#define SOC_M3_SCS_AIRCR_sysresetreq_END            (2)
#define SOC_M3_SCS_AIRCR_prigroup_START             (8)
#define SOC_M3_SCS_AIRCR_prigroup_END               (10)
#define SOC_M3_SCS_AIRCR_endianess_START            (15)
#define SOC_M3_SCS_AIRCR_endianess_END              (15)
#define SOC_M3_SCS_AIRCR_vectkey_vectkeystat_START  (16)
#define SOC_M3_SCS_AIRCR_vectkey_vectkeystat_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_SCR_UNION
 �ṹ˵��  : SCR �Ĵ����ṹ���塣��ַƫ����:0xD10����ֵ:0x00000000�����:32
 �Ĵ���˵��: System Control Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0  : 1;  /* bit[0]   : Reserved */
        unsigned int  sleeponexit : 1;  /* bit[1]   : ����handlerģʽ��threadģʽ�Ƴ�ʱ����˯��
                                                      0��������threadģʽʱ��˯��
                                                      1���Ƴ�ISRʱ����˯�� */
        unsigned int  sleepdeep   : 1;  /* bit[2]   : 0�����ܹر�coreʱ��
                                                      1��ʹ����ź�SLEEPDEEP��Ч��ָʾ���Թر�coreʱ�� */
        unsigned int  reserved_1  : 1;  /* bit[3]   : Reserved */
        unsigned int  sevonpend   : 1;  /* bit[4]   : ���ø�λ���ǵĵ��жϴ�δ�������״̬��WFE���� */
        unsigned int  reserved_2  : 27; /* bit[5-31]: Reserved */
    } reg;
} SOC_M3_SCS_SCR_UNION;
#endif
#define SOC_M3_SCS_SCR_sleeponexit_START  (1)
#define SOC_M3_SCS_SCR_sleeponexit_END    (1)
#define SOC_M3_SCS_SCR_sleepdeep_START    (2)
#define SOC_M3_SCS_SCR_sleepdeep_END      (2)
#define SOC_M3_SCS_SCR_sevonpend_START    (4)
#define SOC_M3_SCS_SCR_sevonpend_END      (4)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_CCR_UNION
 �ṹ˵��  : CCR �Ĵ����ṹ���塣��ַƫ����:0xD14����ֵ:0x00000000�����:32
 �Ĵ���˵��: Configuration and Control Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nonebasethrdena : 1;  /* bit[0]    : 0���������һ���쳣����ʱֻ�ܽ���threadģʽ
                                                           1��handlerģʽ�κ�����¶��ܹ�ͨ�����Ʒ���ֵ����threadģʽ */
        unsigned int  usersetmpend    : 1;  /* bit[1]    : ����1����ʹ���û������ܹ�ͨ������STIR�Ĵ���������Main�쳣 */
        unsigned int  reserved_0      : 1;  /* bit[2]    : Reserved */
        unsigned int  unalign_trp     : 1;  /* bit[3]    : Trap for unaligned access. This enables faulting/halting on any unaligned half or full word access. Unaligned load-store multiples always fault. The relevant Usage Fault Status Register bit is UNALIGNED, see Usage Fault Status Register */
        unsigned int  div_0_trp       : 1;  /* bit[4]    : Trap on Divide by 0. This enables faulting/halting when an attempt is made to divide by 0. The relevant Usage Fault Status Register bit is DIVBYZERO, see Usage Fault Status Register */
        unsigned int  reserved_1      : 3;  /* bit[5-7]  : Reserved */
        unsigned int  bfhfnmign       : 1;  /* bit[8]    : ʹ�ܸ�λ����������������-1��-2���ȼ�����������load��store������������������fault */
        unsigned int  stkalign        : 1;  /* bit[9]    : 0����֤SP�ڽ����쳣֮ǰֻ��4-byte����
                                                           1�����쳣��ڣ�SP�ڽ����쳣֮ǰ����Ϊ8-byte���� */
        unsigned int  reserved_2      : 22; /* bit[10-31]: Reserved */
    } reg;
} SOC_M3_SCS_CCR_UNION;
#endif
#define SOC_M3_SCS_CCR_nonebasethrdena_START  (0)
#define SOC_M3_SCS_CCR_nonebasethrdena_END    (0)
#define SOC_M3_SCS_CCR_usersetmpend_START     (1)
#define SOC_M3_SCS_CCR_usersetmpend_END       (1)
#define SOC_M3_SCS_CCR_unalign_trp_START      (3)
#define SOC_M3_SCS_CCR_unalign_trp_END        (3)
#define SOC_M3_SCS_CCR_div_0_trp_START        (4)
#define SOC_M3_SCS_CCR_div_0_trp_END          (4)
#define SOC_M3_SCS_CCR_bfhfnmign_START        (8)
#define SOC_M3_SCS_CCR_bfhfnmign_END          (8)
#define SOC_M3_SCS_CCR_stkalign_START         (9)
#define SOC_M3_SCS_CCR_stkalign_END           (9)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_SHPR1_UNION
 �ṹ˵��  : SHPR1 �Ĵ����ṹ���塣��ַƫ����:0xD18����ֵ:0x00000000�����:32
 �Ĵ���˵��: System Handler Priorty Register 1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pri_4    : 8;  /* bit[0-7]  : Priority of system handler 4, MemManage */
        unsigned int  pri_5    : 8;  /* bit[8-15] : Priority of system handler 5, BusFault */
        unsigned int  pri_6    : 8;  /* bit[16-23]: Priority of system handler 6, UsageFault */
        unsigned int  reserved : 8;  /* bit[24-31]: Reserved for priority of system handler 7 */
    } reg;
} SOC_M3_SCS_SHPR1_UNION;
#endif
#define SOC_M3_SCS_SHPR1_pri_4_START     (0)
#define SOC_M3_SCS_SHPR1_pri_4_END       (7)
#define SOC_M3_SCS_SHPR1_pri_5_START     (8)
#define SOC_M3_SCS_SHPR1_pri_5_END       (15)
#define SOC_M3_SCS_SHPR1_pri_6_START     (16)
#define SOC_M3_SCS_SHPR1_pri_6_END       (23)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_SHPR2_UNION
 �ṹ˵��  : SHPR2 �Ĵ����ṹ���塣��ַƫ����:0xD1C����ֵ:0x00000000�����:32
 �Ĵ���˵��: System Handler Priorty Register 2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 8;  /* bit[0-7]  : Reserved for priority of system handler 8 */
        unsigned int  reserved_1: 8;  /* bit[8-15] : Reserved for priority of system handler 9 */
        unsigned int  reserved_2: 8;  /* bit[16-23]: Reserved for priority of system handler 10 */
        unsigned int  pri_11   : 8;  /* bit[24-31]: Priority of system handler 11, SVCall */
    } reg;
} SOC_M3_SCS_SHPR2_UNION;
#endif
#define SOC_M3_SCS_SHPR2_pri_11_START    (24)
#define SOC_M3_SCS_SHPR2_pri_11_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_SHPR3_UNION
 �ṹ˵��  : SHPR3 �Ĵ����ṹ���塣��ַƫ����:0xD20����ֵ:0x00000000�����:32
 �Ĵ���˵��: System Handler Priorty Register 3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pri_12   : 8;  /* bit[0-7]  : Priority of system handler 12, DebugMonitor */
        unsigned int  reserved : 8;  /* bit[8-15] : Reserved for priority of system handler 13 */
        unsigned int  pri_14   : 8;  /* bit[16-23]: Priority of system handler 14, PendSV */
        unsigned int  pri_15   : 8;  /* bit[24-31]: Priority of system handler 15, SysTick */
    } reg;
} SOC_M3_SCS_SHPR3_UNION;
#endif
#define SOC_M3_SCS_SHPR3_pri_12_START    (0)
#define SOC_M3_SCS_SHPR3_pri_12_END      (7)
#define SOC_M3_SCS_SHPR3_pri_14_START    (16)
#define SOC_M3_SCS_SHPR3_pri_14_END      (23)
#define SOC_M3_SCS_SHPR3_pri_15_START    (24)
#define SOC_M3_SCS_SHPR3_pri_15_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_SHCSR_UNION
 �ṹ˵��  : SHCSR �Ĵ����ṹ���塣��ַƫ����:0xD24����ֵ:0x00000000�����:32
 �Ĵ���˵��: System Handler Control and State Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  memfaultact    : 1;  /* bit[0]    : 0 = MemManage is not active.
                                                          1 = MemManage is active. */
        unsigned int  busfaultact    : 1;  /* bit[1]    : 0 = BusFault is not active.
                                                          1 = BusFault is active. */
        unsigned int  reserved_0     : 1;  /* bit[2]    : Reserved */
        unsigned int  usgfaultact    : 1;  /* bit[3]    : 0 = UsageFault is not active.
                                                          1 = UsageFault is active. */
        unsigned int  reserved_1     : 3;  /* bit[4-6]  : Reserved */
        unsigned int  svcallact      : 1;  /* bit[7]    : 0 = SVCall is not active.
                                                          1 = SVCall is active.  */
        unsigned int  monitoract     : 1;  /* bit[8]    : 0 = Monitor is not active.
                                                          1 = Monitor is active.  */
        unsigned int  reserved_2     : 1;  /* bit[9]    : Reserved */
        unsigned int  pendsvact      : 1;  /* bit[10]   : 0 = PendSV is not active.
                                                          1 = PendSV is active.  */
        unsigned int  systickact     : 1;  /* bit[11]   : 0 = SysTick is not active.
                                                          1 = SysTick is active. */
        unsigned int  usgfaultpended : 1;  /* bit[12]   : 0 = UsageFault is not pending.
                                                          1 = UsageFault is pending. */
        unsigned int  memfaultpended : 1;  /* bit[13]   : 0 = MemManage is not pending.
                                                          1 = MemManage is pending. */
        unsigned int  busfaultpended : 1;  /* bit[14]   : 0 = BusFault is not pending.
                                                          1 = BusFault is pending. */
        unsigned int  svcallpended   : 1;  /* bit[15]   : 0 = SVCall is not pending.
                                                          1 = SVCall is pending. */
        unsigned int  memfaultena    : 1;  /* bit[16]   : 0 = Disable MemManage fault.
                                                          1 = Enable MemManage fault.  */
        unsigned int  busfaultena    : 1;  /* bit[17]   : 0 = Disable BusFault.
                                                          1 = Enable BusFault.  */
        unsigned int  usgfaultena    : 1;  /* bit[18]   : 0 = Disable UsageFault.
                                                          1 = Enable UsageFault.  */
        unsigned int  reserved_3     : 13; /* bit[19-31]: Reserved */
    } reg;
} SOC_M3_SCS_SHCSR_UNION;
#endif
#define SOC_M3_SCS_SHCSR_memfaultact_START     (0)
#define SOC_M3_SCS_SHCSR_memfaultact_END       (0)
#define SOC_M3_SCS_SHCSR_busfaultact_START     (1)
#define SOC_M3_SCS_SHCSR_busfaultact_END       (1)
#define SOC_M3_SCS_SHCSR_usgfaultact_START     (3)
#define SOC_M3_SCS_SHCSR_usgfaultact_END       (3)
#define SOC_M3_SCS_SHCSR_svcallact_START       (7)
#define SOC_M3_SCS_SHCSR_svcallact_END         (7)
#define SOC_M3_SCS_SHCSR_monitoract_START      (8)
#define SOC_M3_SCS_SHCSR_monitoract_END        (8)
#define SOC_M3_SCS_SHCSR_pendsvact_START       (10)
#define SOC_M3_SCS_SHCSR_pendsvact_END         (10)
#define SOC_M3_SCS_SHCSR_systickact_START      (11)
#define SOC_M3_SCS_SHCSR_systickact_END        (11)
#define SOC_M3_SCS_SHCSR_usgfaultpended_START  (12)
#define SOC_M3_SCS_SHCSR_usgfaultpended_END    (12)
#define SOC_M3_SCS_SHCSR_memfaultpended_START  (13)
#define SOC_M3_SCS_SHCSR_memfaultpended_END    (13)
#define SOC_M3_SCS_SHCSR_busfaultpended_START  (14)
#define SOC_M3_SCS_SHCSR_busfaultpended_END    (14)
#define SOC_M3_SCS_SHCSR_svcallpended_START    (15)
#define SOC_M3_SCS_SHCSR_svcallpended_END      (15)
#define SOC_M3_SCS_SHCSR_memfaultena_START     (16)
#define SOC_M3_SCS_SHCSR_memfaultena_END       (16)
#define SOC_M3_SCS_SHCSR_busfaultena_START     (17)
#define SOC_M3_SCS_SHCSR_busfaultena_END       (17)
#define SOC_M3_SCS_SHCSR_usgfaultena_START     (18)
#define SOC_M3_SCS_SHCSR_usgfaultena_END       (18)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_CFSR_UNION
 �ṹ˵��  : CFSR �Ĵ����ṹ���塣��ַƫ����:0xD28����ֵ:0x00000000�����:32
 �Ĵ���˵��: Configurable Fault Status Registers
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iaccviol    : 1;  /* bit[0]    : 0 = No MPU or Execute Never (XN) default memory map access violation has occurred.
                                                       1 = MPU or Execute Never (XN) default memory map access violation on an instruction fetch has occurred. The fault is signalled only if the instruction is issued. */
        unsigned int  daccviol    : 1;  /* bit[1]    : 0 = No data access violation has occurred. 
                                                       1 = Data access violation. The MMAR shows the data address that the load or store tried 
                                                       to access. */
        unsigned int  reserved_0  : 1;  /* bit[2]    : Reserved */
        unsigned int  munstkerr   : 1;  /* bit[3]    : 0 = No derived MemManage fault has occurred. 
                                                       1 = A derived MemManage fault occurred on exception return.  */
        unsigned int  mstkerr     : 1;  /* bit[4]    : 0 = No derived MemManage fault has occurred.
                                                       1 = A derived MemManage fault occurred on exception entry. */
        unsigned int  mlsperr     : 1;  /* bit[5]    : 0 = No derived MemManage fault has occurred.
                                                       1 = A derived MemManage fault occurred on exception entry. */
        unsigned int  reserved_1  : 1;  /* bit[6]    : Reserved */
        unsigned int  mmarvalid   : 1;  /* bit[7]    : 0 = MMAR does not have valid contents.
                                                       1 = MMAR has valid contents. */
        unsigned int  ibuserr     : 1;  /* bit[8]    : 0 = No bus fault on an instruction prefetch has occurred.
                                                       1 = A bus fault on an instruction prefetch has occurred. The fault is signalled only if the instruction is issued */
        unsigned int  preciserr   : 1;  /* bit[9]    : 0 = No precise data access error has occurred.
                                                       1 = A precise data access error has occurred, and the processor has written the faulting address to the BFAR */
        unsigned int  impreciserr : 1;  /* bit[10]   : 0 = No imprecise data access error has occurred.
                                                       1 = Imprecise data access error has occurred */
        unsigned int  unstkerr    : 1;  /* bit[11]   : 0 = No derived bus fault has occurred.
                                                       1 = A derived bus fault has occurred on exception return. */
        unsigned int  stkerr      : 1;  /* bit[12]   : 0 = No derived bus fault has occurred.
                                                       1 = A derived bus fault has occurred on exception entry. */
        unsigned int  lsperr      : 1;  /* bit[13]   : 0 = No bus fault occurred during FP lazy state preservation.
                                                       1 = A bus fault occurred during FP lazy state preservation. */
        unsigned int  reserved_2  : 1;  /* bit[14]   : Reserved */
        unsigned int  bfarvalid   : 1;  /* bit[15]   : 0 = BFAR does not have valid contents.
                                                       1 = BFAR has valid contents. */
        unsigned int  undefinstr  : 1;  /* bit[16]   : 0 = No Undefined Instruction Usage fault has occurred.
                                                       1 = The processor has attempted to execute an undefined instruction. This might be an undefined instruction associated with an enabled coprocessor */
        unsigned int  invstate    : 1;  /* bit[17]   : 0 = EPSR.T bit and EPSR.IT bits are valid for instruction execution.
                                                       1 = Instruction executed with invalid EPSR.T or EPSR.IT field. */
        unsigned int  invpc       : 1;  /* bit[18]   : 0 = No integrity check error has occurred.
                                                       1 = An integrity check error has occurred on EXC_RETURN.  */
        unsigned int  nocp        : 1;  /* bit[19]   : 0 = No coprocessor access error has occurred.
                                                       1 = A coprocessor access error has occurred. This shows that the coprocessor is disabled or not present */
        unsigned int  reserved_3  : 4;  /* bit[20-23]: Reserved */
        unsigned int  unaligned   : 1;  /* bit[24]   : 0 = No unaligned access error has occurred.
                                                       1 = Unaligned access error has occurred.
                                                       Multi-word accesses always fault if not word aligned. Software can configure 
                                                       unaligned word and halfword accesses to fault, by enabling UNALIGN_TRP in the 
                                                       CCR */
        unsigned int  divbyzero   : 1;  /* bit[25]   : 0 = No divide by zero error has occurred.
                                                       1 = Divide by zero error has occurred.
                                                       When SDIV or UDIV instruction is used with a divisor of 0, this fault occurs if DIV_0_TRP is enabled in the CCR */
        unsigned int  reserved_4  : 6;  /* bit[26-31]: Reserved */
    } reg;
} SOC_M3_SCS_CFSR_UNION;
#endif
#define SOC_M3_SCS_CFSR_iaccviol_START     (0)
#define SOC_M3_SCS_CFSR_iaccviol_END       (0)
#define SOC_M3_SCS_CFSR_daccviol_START     (1)
#define SOC_M3_SCS_CFSR_daccviol_END       (1)
#define SOC_M3_SCS_CFSR_munstkerr_START    (3)
#define SOC_M3_SCS_CFSR_munstkerr_END      (3)
#define SOC_M3_SCS_CFSR_mstkerr_START      (4)
#define SOC_M3_SCS_CFSR_mstkerr_END        (4)
#define SOC_M3_SCS_CFSR_mlsperr_START      (5)
#define SOC_M3_SCS_CFSR_mlsperr_END        (5)
#define SOC_M3_SCS_CFSR_mmarvalid_START    (7)
#define SOC_M3_SCS_CFSR_mmarvalid_END      (7)
#define SOC_M3_SCS_CFSR_ibuserr_START      (8)
#define SOC_M3_SCS_CFSR_ibuserr_END        (8)
#define SOC_M3_SCS_CFSR_preciserr_START    (9)
#define SOC_M3_SCS_CFSR_preciserr_END      (9)
#define SOC_M3_SCS_CFSR_impreciserr_START  (10)
#define SOC_M3_SCS_CFSR_impreciserr_END    (10)
#define SOC_M3_SCS_CFSR_unstkerr_START     (11)
#define SOC_M3_SCS_CFSR_unstkerr_END       (11)
#define SOC_M3_SCS_CFSR_stkerr_START       (12)
#define SOC_M3_SCS_CFSR_stkerr_END         (12)
#define SOC_M3_SCS_CFSR_lsperr_START       (13)
#define SOC_M3_SCS_CFSR_lsperr_END         (13)
#define SOC_M3_SCS_CFSR_bfarvalid_START    (15)
#define SOC_M3_SCS_CFSR_bfarvalid_END      (15)
#define SOC_M3_SCS_CFSR_undefinstr_START   (16)
#define SOC_M3_SCS_CFSR_undefinstr_END     (16)
#define SOC_M3_SCS_CFSR_invstate_START     (17)
#define SOC_M3_SCS_CFSR_invstate_END       (17)
#define SOC_M3_SCS_CFSR_invpc_START        (18)
#define SOC_M3_SCS_CFSR_invpc_END          (18)
#define SOC_M3_SCS_CFSR_nocp_START         (19)
#define SOC_M3_SCS_CFSR_nocp_END           (19)
#define SOC_M3_SCS_CFSR_unaligned_START    (24)
#define SOC_M3_SCS_CFSR_unaligned_END      (24)
#define SOC_M3_SCS_CFSR_divbyzero_START    (25)
#define SOC_M3_SCS_CFSR_divbyzero_END      (25)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_HFSR_UNION
 �ṹ˵��  : HFSR �Ĵ����ṹ���塣��ַƫ����:0xD2C����ֵ:0x00000000�����:32
 �Ĵ���˵��: HardFault Status Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 1;  /* bit[0]   : Reserved */
        unsigned int  vecttbl  : 1;  /* bit[1]   : Indicates when a fault has occurred because of a vector table read error on exception processing:
                                                   0 = No vector table read fault has occurred.
                                                   1 = Vector table read fault has occurred */
        unsigned int  reserved_1: 28; /* bit[2-29]: Reserved */
        unsigned int  forced   : 1;  /* bit[30]  : Indicates that a fault with configurable priority has been escalated to a HardFault exception, because it could not be made active, because of priority or because it was disabled:
                                                   0 = No priority escalation has occurred.
                                                   1 = Processor has escalated a configurable-priority exception to HardFault */
        unsigned int  debugevt : 1;  /* bit[31]  : Indicates when a Debug event has occurred:
                                                   0 = No Debug event has occurred.
                                                   1 = Debug event has occurred. The Debug Fault Status Register has been updated
                                                   The processor sets this bit to 1 only when halting debug is disabled and a Debug event occurs */
    } reg;
} SOC_M3_SCS_HFSR_UNION;
#endif
#define SOC_M3_SCS_HFSR_vecttbl_START   (1)
#define SOC_M3_SCS_HFSR_vecttbl_END     (1)
#define SOC_M3_SCS_HFSR_forced_START    (30)
#define SOC_M3_SCS_HFSR_forced_END      (30)
#define SOC_M3_SCS_HFSR_debugevt_START  (31)
#define SOC_M3_SCS_HFSR_debugevt_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_DFSR_UNION
 �ṹ˵��  : DFSR �Ĵ����ṹ���塣��ַƫ����:0xD30����ֵ:0x00000000�����:32
 �Ĵ���˵��: Debug Fault Status Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  halted   : 1;  /* bit[0]   : 0 = No active halt request debug event.
                                                   1 = Halt request debug event active. */
        unsigned int  bkpt     : 1;  /* bit[1]   : Indicates a debug event generated by BKPT instruction execution or a breakpoint match in FPB:
                                                   0 = No current breakpoint debug event.
                                                   1 = At least one current breakpoint debug event. */
        unsigned int  dwttrap  : 1;  /* bit[2]   : Indicates a debug event generated by the DWT:
                                                   0 = No current debug events generated by the DWT.
                                                   1 = At least one current debug event generated by the DWT. */
        unsigned int  vcatch   : 1;  /* bit[3]   : Indicates triggering of a Vector catch:
                                                   0 = No Vector catch triggered.
                                                   1 = Vector catch triggered.
                                                   The corresponding FSR shows the primary cause of the exception. */
        unsigned int  external : 1;  /* bit[4]   : Indicates a debug event generated because of the assertion of EDBGRQ:
                                                   0 = No EDBGRQ debug event.
                                                   1 = EDBGRQ debug event. */
        unsigned int  reserved : 27; /* bit[5-31]: Reserved */
    } reg;
} SOC_M3_SCS_DFSR_UNION;
#endif
#define SOC_M3_SCS_DFSR_halted_START    (0)
#define SOC_M3_SCS_DFSR_halted_END      (0)
#define SOC_M3_SCS_DFSR_bkpt_START      (1)
#define SOC_M3_SCS_DFSR_bkpt_END        (1)
#define SOC_M3_SCS_DFSR_dwttrap_START   (2)
#define SOC_M3_SCS_DFSR_dwttrap_END     (2)
#define SOC_M3_SCS_DFSR_vcatch_START    (3)
#define SOC_M3_SCS_DFSR_vcatch_END      (3)
#define SOC_M3_SCS_DFSR_external_START  (4)
#define SOC_M3_SCS_DFSR_external_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_MMFAR_UNION
 �ṹ˵��  : MMFAR �Ĵ����ṹ���塣��ַƫ����:0xD34����ֵ:0x00000000�����:32
 �Ĵ���˵��: MemManage Fault Address Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  address_mem : 32; /* bit[0-31]: Data address for an MPU fault.  */
    } reg;
} SOC_M3_SCS_MMFAR_UNION;
#endif
#define SOC_M3_SCS_MMFAR_address_mem_START  (0)
#define SOC_M3_SCS_MMFAR_address_mem_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_BFAR_UNION
 �ṹ˵��  : BFAR �Ĵ����ṹ���塣��ַƫ����:0xD38����ֵ:0x00000000�����:32
 �Ĵ���˵��: BusFault Address Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  address_bus : 32; /* bit[0-31]: Data address for a precise bus fault. */
    } reg;
} SOC_M3_SCS_BFAR_UNION;
#endif
#define SOC_M3_SCS_BFAR_address_bus_START  (0)
#define SOC_M3_SCS_BFAR_address_bus_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_AFSR_UNION
 �ṹ˵��  : AFSR �Ĵ����ṹ���塣��ַƫ����:0xD3C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Auxiliary Fault Status Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  auxfault : 32; /* bit[0-31]: Latched version of the AUXFAULT inputs */
    } reg;
} SOC_M3_SCS_AFSR_UNION;
#endif
#define SOC_M3_SCS_AFSR_auxfault_START  (0)
#define SOC_M3_SCS_AFSR_auxfault_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_ID_PFR0_UNION
 �ṹ˵��  : ID_PFR0 �Ĵ����ṹ���塣��ַƫ����:0xD40����ֵ:0x00000030�����:32
 �Ĵ���˵��: Processor Feature Register 0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ID_PFR0 : 32; /* bit[0-31]:  */
    } reg;
} SOC_M3_SCS_ID_PFR0_UNION;
#endif
#define SOC_M3_SCS_ID_PFR0_ID_PFR0_START  (0)
#define SOC_M3_SCS_ID_PFR0_ID_PFR0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_ID_PFR1_UNION
 �ṹ˵��  : ID_PFR1 �Ĵ����ṹ���塣��ַƫ����:0xD44����ֵ:0x00000200�����:32
 �Ĵ���˵��: Processor Feature Register 1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ID_PFR1 : 32; /* bit[0-31]:  */
    } reg;
} SOC_M3_SCS_ID_PFR1_UNION;
#endif
#define SOC_M3_SCS_ID_PFR1_ID_PFR1_START  (0)
#define SOC_M3_SCS_ID_PFR1_ID_PFR1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_ID_DFR0_UNION
 �ṹ˵��  : ID_DFR0 �Ĵ����ṹ���塣��ַƫ����:0xD48����ֵ:0x00100000�����:32
 �Ĵ���˵��: Debug Features Register 0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ID_DFR0 : 32; /* bit[0-31]:  */
    } reg;
} SOC_M3_SCS_ID_DFR0_UNION;
#endif
#define SOC_M3_SCS_ID_DFR0_ID_DFR0_START  (0)
#define SOC_M3_SCS_ID_DFR0_ID_DFR0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_ID_AFR0_UNION
 �ṹ˵��  : ID_AFR0 �Ĵ����ṹ���塣��ַƫ����:0xD4C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Auxiliary Features Register 0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ID_AFR0 : 32; /* bit[0-31]:  */
    } reg;
} SOC_M3_SCS_ID_AFR0_UNION;
#endif
#define SOC_M3_SCS_ID_AFR0_ID_AFR0_START  (0)
#define SOC_M3_SCS_ID_AFR0_ID_AFR0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_ID_MMFR0_UNION
 �ṹ˵��  : ID_MMFR0 �Ĵ����ṹ���塣��ַƫ����:0xD50����ֵ:0x00100030�����:32
 �Ĵ���˵��: Memory Model Feature Register 0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ID_MMFR0 : 32; /* bit[0-31]:  */
    } reg;
} SOC_M3_SCS_ID_MMFR0_UNION;
#endif
#define SOC_M3_SCS_ID_MMFR0_ID_MMFR0_START  (0)
#define SOC_M3_SCS_ID_MMFR0_ID_MMFR0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_ID_MMFR1_UNION
 �ṹ˵��  : ID_MMFR1 �Ĵ����ṹ���塣��ַƫ����:0xD54����ֵ:0x00000000�����:32
 �Ĵ���˵��: Memory Model Feature Register 1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ID_MMFR1 : 32; /* bit[0-31]:  */
    } reg;
} SOC_M3_SCS_ID_MMFR1_UNION;
#endif
#define SOC_M3_SCS_ID_MMFR1_ID_MMFR1_START  (0)
#define SOC_M3_SCS_ID_MMFR1_ID_MMFR1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_ID_MMFR2_UNION
 �ṹ˵��  : ID_MMFR2 �Ĵ����ṹ���塣��ַƫ����:0xD58����ֵ:0x01000000�����:32
 �Ĵ���˵��: Memory Model Feature Register 2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ID_MMFR2 : 32; /* bit[0-31]:  */
    } reg;
} SOC_M3_SCS_ID_MMFR2_UNION;
#endif
#define SOC_M3_SCS_ID_MMFR2_ID_MMFR2_START  (0)
#define SOC_M3_SCS_ID_MMFR2_ID_MMFR2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_ID_MMFR3_UNION
 �ṹ˵��  : ID_MMFR3 �Ĵ����ṹ���塣��ַƫ����:0xD5C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Memory Model Feature Register 3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ID_MMFR3 : 32; /* bit[0-31]:  */
    } reg;
} SOC_M3_SCS_ID_MMFR3_UNION;
#endif
#define SOC_M3_SCS_ID_MMFR3_ID_MMFR3_START  (0)
#define SOC_M3_SCS_ID_MMFR3_ID_MMFR3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_ID_ISAR0_UNION
 �ṹ˵��  : ID_ISAR0 �Ĵ����ṹ���塣��ַƫ����:0xD60����ֵ:0x01100110�����:32
 �Ĵ���˵��: Instruction Set Attributes Register 0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ID_ISAR0 : 32; /* bit[0-31]:  */
    } reg;
} SOC_M3_SCS_ID_ISAR0_UNION;
#endif
#define SOC_M3_SCS_ID_ISAR0_ID_ISAR0_START  (0)
#define SOC_M3_SCS_ID_ISAR0_ID_ISAR0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_ID_ISAR1_UNION
 �ṹ˵��  : ID_ISAR1 �Ĵ����ṹ���塣��ַƫ����:0xD64����ֵ:0x02111000�����:32
 �Ĵ���˵��: Instruction Set Attributes Register 1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ID_ISAR1 : 32; /* bit[0-31]:  */
    } reg;
} SOC_M3_SCS_ID_ISAR1_UNION;
#endif
#define SOC_M3_SCS_ID_ISAR1_ID_ISAR1_START  (0)
#define SOC_M3_SCS_ID_ISAR1_ID_ISAR1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_ID_ISAR2_UNION
 �ṹ˵��  : ID_ISAR2 �Ĵ����ṹ���塣��ַƫ����:0xD68����ֵ:0x21112231�����:32
 �Ĵ���˵��: Instruction Set Attributes Register 2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ID_ISAR2 : 32; /* bit[0-31]:  */
    } reg;
} SOC_M3_SCS_ID_ISAR2_UNION;
#endif
#define SOC_M3_SCS_ID_ISAR2_ID_ISAR2_START  (0)
#define SOC_M3_SCS_ID_ISAR2_ID_ISAR2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_ID_ISAR3_UNION
 �ṹ˵��  : ID_ISAR3 �Ĵ����ṹ���塣��ַƫ����:0xD6C����ֵ:0x01111110�����:32
 �Ĵ���˵��: Instruction Set Attributes Register 3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ID_ISAR3 : 32; /* bit[0-31]:  */
    } reg;
} SOC_M3_SCS_ID_ISAR3_UNION;
#endif
#define SOC_M3_SCS_ID_ISAR3_ID_ISAR3_START  (0)
#define SOC_M3_SCS_ID_ISAR3_ID_ISAR3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_ID_ISAR4_UNION
 �ṹ˵��  : ID_ISAR4 �Ĵ����ṹ���塣��ַƫ����:0xD70����ֵ:0x01310132�����:32
 �Ĵ���˵��: Instruction Set Attributes Register 4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ID_ISAR4 : 32; /* bit[0-31]:  */
    } reg;
} SOC_M3_SCS_ID_ISAR4_UNION;
#endif
#define SOC_M3_SCS_ID_ISAR4_ID_ISAR4_START  (0)
#define SOC_M3_SCS_ID_ISAR4_ID_ISAR4_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_CPACR_UNION
 �ṹ˵��  : CPACR �Ĵ����ṹ���塣��ַƫ����:0xD88����ֵ:0x00000000�����:32
 �Ĵ���˵��: Coprocessor Access Control Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  CPACR : 32; /* bit[0-31]:  */
    } reg;
} SOC_M3_SCS_CPACR_UNION;
#endif
#define SOC_M3_SCS_CPACR_CPACR_START  (0)
#define SOC_M3_SCS_CPACR_CPACR_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_M3_SCS_STIR_UNION
 �ṹ˵��  : STIR �Ĵ����ṹ���塣��ַƫ����:0xF00����ֵ:0x00000000�����:32
 �Ĵ���˵��: Software Triggered Interrupt Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intid    : 9;  /* bit[0-8] : Indicates the interrupt to be triggered.The value written is (ExceptionNumber - 16) */
        unsigned int  reserved : 23; /* bit[9-31]: Reserved */
    } reg;
} SOC_M3_SCS_STIR_UNION;
#endif
#define SOC_M3_SCS_STIR_intid_START     (0)
#define SOC_M3_SCS_STIR_intid_END       (8)






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

#endif /* end of soc_m3_scs_interface.h */
