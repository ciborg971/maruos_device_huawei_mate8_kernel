/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_lpm3_cfg_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:22:15
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_LPM3_CFG.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_LPM3_CFG_INTERFACE_H__
#define __SOC_LPM3_CFG_INTERFACE_H__

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
/* �Ĵ���˵����M3����DDR�Ļ����������üĴ���
   λ����UNION�ṹ:  SOC_LPM3_CFG_ACCESS_WIN_UNION */
#define SOC_LPM3_CFG_ACCESS_WIN_ADDR(base)            ((base) + (0x000))

/* �Ĵ���˵����M3 halt״̬bypass���ƼĴ���
   λ����UNION�ṹ:  SOC_LPM3_CFG_HALT_BYPASS_UNION */
#define SOC_LPM3_CFG_HALT_BYPASS_ADDR(base)           ((base) + (0x004))

/* �Ĵ���˵����Lp_ram multi-cycle���ƼĴ���
   λ����UNION�ṹ:  SOC_LPM3_CFG_LPRAM_MULTI_CTRL_UNION */
#define SOC_LPM3_CFG_LPRAM_MULTI_CTRL_ADDR(base)      ((base) + (0x008))

/* �Ĵ���˵�����������߼�bypass���ƼĴ���
   λ����UNION�ṹ:  SOC_LPM3_CFG_DLOCK_BYPASS_UNION */
#define SOC_LPM3_CFG_DLOCK_BYPASS_ADDR(base)          ((base) + (0x00C))

/* �Ĵ���˵����Timer��Wdog����ʱ��ʹ��bypass���ƼĴ���
   λ����UNION�ṹ:  SOC_LPM3_CFG_TIMCLKEN_BYPASS_UNION */
#define SOC_LPM3_CFG_TIMCLKEN_BYPASS_ADDR(base)       ((base) + (0x010))

/* �Ĵ���˵����test pin��ʹ������Ĵ���
   λ����UNION�ṹ:  SOC_LPM3_CFG_TESTPIN_EN_UNION */
#define SOC_LPM3_CFG_TESTPIN_EN_ADDR(base)            ((base) + (0x014))

/* �Ĵ���˵����Harq memory���ƼĴ���0
   λ����UNION�ṹ:  SOC_LPM3_CFG_HARQMEM_CTRL0_UNION */
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ADDR(base)         ((base) + (0x020))

/* �Ĵ���˵����Harq memory���ƼĴ���1
   λ����UNION�ṹ:  SOC_LPM3_CFG_HARQMEM_CTRL1_UNION */
#define SOC_LPM3_CFG_HARQMEM_CTRL1_ADDR(base)         ((base) + (0x024))

/* �Ĵ���˵����NMI���жϼĴ���
   λ����UNION�ṹ:  SOC_LPM3_CFG_NMI_SOFT_UNION */
#define SOC_LPM3_CFG_NMI_SOFT_ADDR(base)              ((base) + (0x028))





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
 �ṹ��    : SOC_LPM3_CFG_ACCESS_WIN_UNION
 �ṹ˵��  : ACCESS_WIN �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x00000000�����:32
 �Ĵ���˵��: M3����DDR�Ļ����������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved      : 28; /* bit[0-27] : Reserved */
        unsigned int  access_window : 4;  /* bit[28-31]: M3��256MB DDR�ռ����ʱ�����ӵĻ������ʴ��ڡ�ȡֵ��ΧΪ0x0~0xD */
    } reg;
} SOC_LPM3_CFG_ACCESS_WIN_UNION;
#endif
#define SOC_LPM3_CFG_ACCESS_WIN_access_window_START  (28)
#define SOC_LPM3_CFG_ACCESS_WIN_access_window_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LPM3_CFG_HALT_BYPASS_UNION
 �ṹ˵��  : HALT_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x00000001�����:32
 �Ĵ���˵��: M3 halt״̬bypass���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  halt_bypass : 1;  /* bit[0]   : �Ƿ�bypass��M3debug״̬���ڲ�timer��watchdog�ļ���Ӱ��
                                                      0��halt״̬��Ӱ���������debug״̬��ֹͣ����
                                                      1��bypass halt״̬����debug״̬�²�ֹͣ���� */
        unsigned int  reserved    : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_LPM3_CFG_HALT_BYPASS_UNION;
#endif
#define SOC_LPM3_CFG_HALT_BYPASS_halt_bypass_START  (0)
#define SOC_LPM3_CFG_HALT_BYPASS_halt_bypass_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_LPM3_CFG_LPRAM_MULTI_CTRL_UNION
 �ṹ˵��  : LPRAM_MULTI_CTRL �Ĵ����ṹ���塣��ַƫ����:0x008����ֵ:0x00000000�����:32
 �Ĵ���˵��: Lp_ram multi-cycle���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lpram_multi_ctrl : 1;  /* bit[0]   : AO��LP_RAM multi-cycle���ƼĴ���
                                                           0������ramʱ�򣬶�����2 cycle����
                                                           1��ram���ʽӿڵ�fready��ѹһ�ģ�������3 cycle���� */
        unsigned int  reserved         : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_LPM3_CFG_LPRAM_MULTI_CTRL_UNION;
#endif
#define SOC_LPM3_CFG_LPRAM_MULTI_CTRL_lpram_multi_ctrl_START  (0)
#define SOC_LPM3_CFG_LPRAM_MULTI_CTRL_lpram_multi_ctrl_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_LPM3_CFG_DLOCK_BYPASS_UNION
 �ṹ˵��  : DLOCK_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x00C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������߼�bypass���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass_for_ssi1  : 1;  /* bit[0]    : pmussi1���ýӿڷ������߼���·���ƣ�Ĭ��Ϊ0 */
        unsigned int  bypass_for_ddrc  : 1;  /* bit[1]    : ddrc���ýӿڷ������߼���·���ƣ���Чʱ����·�߼������ǿ������Ϊ1��bypass����Ĭ��Ϊ0��������·�� */
        unsigned int  bypass_for_tsen  : 1;  /* bit[2]    : tsensorc���ýӿڷ������߼���·���ƣ�Ĭ��Ϊ0 */
        unsigned int  bypass_for_pmc   : 1;  /* bit[3]    : pmc���ýӿڷ������߼���·���ƣ�Ĭ��Ϊ0 */
        unsigned int  bypass_for_uart  : 1;  /* bit[4]    : uart���ýӿڷ������߼���·���ƣ�Ĭ��Ϊ0 */
        unsigned int  bypass_for_i2c   : 1;  /* bit[5]    : pmui2c���ýӿڷ������߼���·���ƣ�Ĭ��Ϊ0 */
        unsigned int  bypass_for_ssi0  : 1;  /* bit[6]    : pmussi0���ýӿڷ������߼���·���ƣ�Ĭ��Ϊ0 */
        unsigned int  bypass_for_pcrg  : 1;  /* bit[7]    : peri CRG���ýӿڷ������߼���·���ƣ�Ĭ��Ϊ0 */
        unsigned int  bypass_for_wdog  : 1;  /* bit[8]    : Watchdog���ýӿڷ������߼���·���ƣ�Ĭ��Ϊ0 */
        unsigned int  bypass_for_timer : 1;  /* bit[9]    : Timer���ýӿڷ������߼���·���ƣ�Ĭ��Ϊ0 */
        unsigned int  reserved_0       : 1;  /* bit[10]   : Unused */
        unsigned int  bypass_for_cssys : 1;  /* bit[11]   : Cssys���ýӿڷ������߼���·���ƣ�Ĭ��Ϊ0 */
        unsigned int  bypass_for_pwm   : 1;  /* bit[12]   : PWM���ʽӿڷ������߼���·���ƣ�Ĭ��Ϊ0 */
        unsigned int  bypass_for_rom   : 1;  /* bit[13]   : ROM���ʽӿڷ������߼���·���ƣ�Ĭ��Ϊ0 */
        unsigned int  bypass_for_ram   : 1;  /* bit[14]   : RAM���ʽӿڷ������߼���·���ƣ�Ĭ��Ϊ0 */
        unsigned int  bypass_for_nandc : 1;  /* bit[15]   : Nandc���ʽӿڷ������߼���·���ƣ�Ĭ��Ϊ0 */
        unsigned int  reserved_1       : 16; /* bit[16-31]: Reserved */
    } reg;
} SOC_LPM3_CFG_DLOCK_BYPASS_UNION;
#endif
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_ssi1_START   (0)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_ssi1_END     (0)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_ddrc_START   (1)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_ddrc_END     (1)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_tsen_START   (2)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_tsen_END     (2)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_pmc_START    (3)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_pmc_END      (3)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_uart_START   (4)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_uart_END     (4)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_i2c_START    (5)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_i2c_END      (5)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_ssi0_START   (6)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_ssi0_END     (6)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_pcrg_START   (7)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_pcrg_END     (7)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_wdog_START   (8)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_wdog_END     (8)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_timer_START  (9)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_timer_END    (9)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_cssys_START  (11)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_cssys_END    (11)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_pwm_START    (12)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_pwm_END      (12)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_rom_START    (13)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_rom_END      (13)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_ram_START    (14)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_ram_END      (14)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_nandc_START  (15)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_nandc_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_LPM3_CFG_TIMCLKEN_BYPASS_UNION
 �ṹ˵��  : TIMCLKEN_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x00000000�����:32
 �Ĵ���˵��: Timer��Wdog����ʱ��ʹ��bypass���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timclken_bypass : 1;  /* bit[0]   : bypass M3��ϵͳ�ڲ�Timer��Wdog�ļ���ʱ��ʹ�ܣ�Ĭ��ֵΪ0����λ��Чʱ������ʱ��ʹ�ܽ���ǿ������Ϊ1���Ա�֤M3������32KHzʱ��ʱ��Timer��Wdog�Կ����������� */
        unsigned int  reserved        : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_LPM3_CFG_TIMCLKEN_BYPASS_UNION;
#endif
#define SOC_LPM3_CFG_TIMCLKEN_BYPASS_timclken_bypass_START  (0)
#define SOC_LPM3_CFG_TIMCLKEN_BYPASS_timclken_bypass_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_LPM3_CFG_TESTPIN_EN_UNION
 �ṹ˵��  : TESTPIN_EN �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x00000000�����:32
 �Ĵ���˵��: test pin��ʹ������Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  testpin_en : 1;  /* bit[0]   : tp_m3lp_hclk test pin�����ʹ�ܿ���λ��
                                                     0��test pin�����Ϊ0
                                                     1��test pin�����Ϊtp_m3lp_hclk */
        unsigned int  reserved   : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_LPM3_CFG_TESTPIN_EN_UNION;
#endif
#define SOC_LPM3_CFG_TESTPIN_EN_testpin_en_START  (0)
#define SOC_LPM3_CFG_TESTPIN_EN_testpin_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_LPM3_CFG_HARQMEM_CTRL0_UNION
 �ṹ˵��  : HARQMEM_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x020����ֵ:0x00000000�����:32
 �Ĵ���˵��: Harq memory���ƼĴ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  soc_ap_occupy_grp1 : 2;  /* bit[0-1]  : 2'b0x��group 1��BBPռ��
                                                              2'b11��group 1��SOCռ�� */
        unsigned int  soc_ap_occupy_grp2 : 2;  /* bit[2-3]  : 2'b0x��group 2��BBPռ��
                                                              2'b11��group 2��SOCռ�� */
        unsigned int  soc_ap_occupy_grp3 : 2;  /* bit[4-5]  : 2'b0x��group 3��BBPռ��
                                                              2'b11��group 3��SOCռ�� */
        unsigned int  soc_ap_occupy_grp4 : 2;  /* bit[6-7]  : 2'b0x��group 4��BBPռ��
                                                              2'b11��group 4��SOCռ�� */
        unsigned int  soc_ap_occupy_grp5 : 2;  /* bit[8-9]  : 2'b0x��group 5��BBPռ��
                                                              2'b11��group 5��SOCռ�� */
        unsigned int  soc_ap_occupy_grp6 : 2;  /* bit[10-11]: 2'b0x��group 6��BBPռ��
                                                              2'b11��group 6��SOCռ�� */
        unsigned int  soc_ap_occupy_grp7 : 2;  /* bit[12-13]: 2'b0x��group 7��BBPռ��
                                                              2'b11��group 7��SOCռ�� */
        unsigned int  reserved           : 2;  /* bit[14-15]: Reserved */
        unsigned int  ram_ctrl_sd_grp1   : 1;  /* bit[16]   : group1 RAM �͹��Ŀ��ƣ�SD�ӿڣ�
                                                              1:��ʾshut downģʽ��
                                                              0:��ʾ����ģʽ�� */
        unsigned int  ram_ctrl_sd_grp2   : 1;  /* bit[17]   : group2 RAM �͹��Ŀ��ƣ�SD�ӿڣ�
                                                              1:��ʾshut downģʽ��
                                                              0:��ʾ����ģʽ�� */
        unsigned int  ram_ctrl_sd_grp3   : 1;  /* bit[18]   : group3 RAM �͹��Ŀ��ƣ�SD�ӿڣ�
                                                              1:��ʾshut downģʽ��
                                                              0:��ʾ����ģʽ�� */
        unsigned int  ram_ctrl_sd_grp4   : 3;  /* bit[19-21]: group4 RAM �͹��Ŀ��ƣ�SD�ӿڣ�
                                                              bit[21:19] RAM2~RAM0 SD�ӿڣ�
                                                              1:��ʾshut downģʽ��
                                                              0:��ʾ����ģʽ�� */
        unsigned int  ram_ctrl_sd_grp5   : 2;  /* bit[22-23]: group5 RAM �͹��Ŀ��ƣ�SD�ӿڣ�
                                                              bit[23:22] RAM1~RAM0 SD�ӿڣ�
                                                              1:��ʾshut downģʽ��
                                                              0:��ʾ����ģʽ�� */
        unsigned int  ram_ctrl_dslp_grp1 : 1;  /* bit[24]   : group1 RAM �͹��Ŀ��ƣ�DSLP�ӿڣ�
                                                              1:��ʾdeep sleepģʽ��
                                                              0:��ʾ����ģʽ�� */
        unsigned int  ram_ctrl_dslp_grp2 : 1;  /* bit[25]   : group2 RAM �͹��Ŀ��ƣ�DSLP�ӿڣ�
                                                              1:��ʾdeep sleepģʽ��
                                                              0:��ʾ����ģʽ�� */
        unsigned int  ram_ctrl_dslp_grp3 : 1;  /* bit[26]   : group3 RAM �͹��Ŀ��ƣ�DSLP�ӿڣ�
                                                              1:��ʾdeep sleepģʽ��
                                                              0:��ʾ����ģʽ�� */
        unsigned int  ram_ctrl_dslp_grp4 : 3;  /* bit[27-29]: group4 RAM �͹��Ŀ��ƣ�DSLP�ӿڣ�
                                                              bit[29:27] RAM2~RAM0 DSLP�ӿڣ�
                                                              1:��ʾdeep sleepģʽ��
                                                              0:��ʾ����ģʽ�� */
        unsigned int  ram_ctrl_dslp_grp5 : 2;  /* bit[30-31]: group5 RAM �͹��Ŀ��ƣ�DSLP�ӿڣ�
                                                              bit[31:30] RAM1~RAM0 DSLP�ӿڣ�
                                                              1:��ʾdeep sleepģʽ��
                                                              0:��ʾ����ģʽ�� */
    } reg;
} SOC_LPM3_CFG_HARQMEM_CTRL0_UNION;
#endif
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp1_START  (0)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp1_END    (1)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp2_START  (2)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp2_END    (3)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp3_START  (4)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp3_END    (5)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp4_START  (6)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp4_END    (7)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp5_START  (8)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp5_END    (9)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp6_START  (10)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp6_END    (11)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp7_START  (12)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp7_END    (13)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_sd_grp1_START    (16)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_sd_grp1_END      (16)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_sd_grp2_START    (17)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_sd_grp2_END      (17)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_sd_grp3_START    (18)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_sd_grp3_END      (18)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_sd_grp4_START    (19)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_sd_grp4_END      (21)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_sd_grp5_START    (22)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_sd_grp5_END      (23)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_dslp_grp1_START  (24)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_dslp_grp1_END    (24)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_dslp_grp2_START  (25)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_dslp_grp2_END    (25)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_dslp_grp3_START  (26)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_dslp_grp3_END    (26)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_dslp_grp4_START  (27)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_dslp_grp4_END    (29)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_dslp_grp5_START  (30)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_dslp_grp5_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LPM3_CFG_HARQMEM_CTRL1_UNION
 �ṹ˵��  : HARQMEM_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x024����ֵ:0x00000000�����:32
 �Ĵ���˵��: Harq memory���ƼĴ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ram_ctrl_sd_grp6   : 3;  /* bit[0-2]  : group6 RAM �͹��Ŀ��ƣ�SD�ӿڣ�
                                                              bit[2:0] RAM2~RAM0 SD�ӿڣ�
                                                              1:��ʾshut downģʽ��
                                                              0:��ʾ����ģʽ�� */
        unsigned int  ram_ctrl_sd_grp7   : 11; /* bit[3-13] : group7 RAM �͹��Ŀ��ƣ�SD�ӿڣ�
                                                              bit[13:3] RAM10~RAM0 SD�ӿڣ�
                                                              1:��ʾshut downģʽ��
                                                              0:��ʾ����ģʽ�� */
        unsigned int  reserved_0         : 2;  /* bit[14-15]: Reserved */
        unsigned int  ram_ctrl_dslp_grp6 : 3;  /* bit[16-18]: group6 RAM �͹��Ŀ��ƣ�DSLP�ӿڣ�
                                                              bit[18:16] RAM2~RAM0 DSLP�ӿڣ�
                                                              1:��ʾdeep sleep low powerģʽ��
                                                              0:��ʾ����ģʽ�� */
        unsigned int  ram_ctrl_dslp_grp7 : 11; /* bit[19-29]: group7 RAM �͹��Ŀ��ƣ�DSLP�ӿڣ�
                                                              bit[29:19] RAM10~RAM0 DSLP�ӿڣ�
                                                              1:��ʾdeep sleep low powerģʽ��
                                                              0:��ʾ����ģʽ�� */
        unsigned int  reserved_1         : 2;  /* bit[30-31]: Reserved */
    } reg;
} SOC_LPM3_CFG_HARQMEM_CTRL1_UNION;
#endif
#define SOC_LPM3_CFG_HARQMEM_CTRL1_ram_ctrl_sd_grp6_START    (0)
#define SOC_LPM3_CFG_HARQMEM_CTRL1_ram_ctrl_sd_grp6_END      (2)
#define SOC_LPM3_CFG_HARQMEM_CTRL1_ram_ctrl_sd_grp7_START    (3)
#define SOC_LPM3_CFG_HARQMEM_CTRL1_ram_ctrl_sd_grp7_END      (13)
#define SOC_LPM3_CFG_HARQMEM_CTRL1_ram_ctrl_dslp_grp6_START  (16)
#define SOC_LPM3_CFG_HARQMEM_CTRL1_ram_ctrl_dslp_grp6_END    (18)
#define SOC_LPM3_CFG_HARQMEM_CTRL1_ram_ctrl_dslp_grp7_START  (19)
#define SOC_LPM3_CFG_HARQMEM_CTRL1_ram_ctrl_dslp_grp7_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_LPM3_CFG_NMI_SOFT_UNION
 �ṹ˵��  : NMI_SOFT �Ĵ����ṹ���塣��ַƫ����:0x028����ֵ:0x00000000�����:32
 �Ĵ���˵��: NMI���жϼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nmi_soft : 1;  /* bit[0]   : ����ȥ��IOMCU��nmi���ж� */
        unsigned int  reserved : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_LPM3_CFG_NMI_SOFT_UNION;
#endif
#define SOC_LPM3_CFG_NMI_SOFT_nmi_soft_START  (0)
#define SOC_LPM3_CFG_NMI_SOFT_nmi_soft_END    (0)






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

#endif /* end of soc_lpm3_cfg_interface.h */
