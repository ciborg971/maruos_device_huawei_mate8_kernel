/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_iomcu_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:21:19
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_IOMCU.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_IOMCU_INTERFACE_H__
#define __SOC_IOMCU_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_define
 ****************************************************************************/
/* �Ĵ���˵����IOMCUʱ��ѡ��Ĵ���������ѡ��ʱ�ӡ�
   λ����UNION�ṹ:  SOC_IOMCU_CLK_SEL_UNION */
#define SOC_IOMCU_CLK_SEL_ADDR(base)                  ((base) + (0x000))

/* �Ĵ���˵����IOMCU��Ƶ�Ĵ���0
   λ����UNION�ṹ:  SOC_IOMCU_CFG_DIV0_UNION */
#define SOC_IOMCU_CFG_DIV0_ADDR(base)                 ((base) + (0x004))

/* �Ĵ���˵����IOMCU��Ƶ�Ĵ���1
   λ����UNION�ṹ:  SOC_IOMCU_CFG_DIV1_UNION */
#define SOC_IOMCU_CFG_DIV1_ADDR(base)                 ((base) + (0x008))

/* �Ĵ���˵����RTCʱ�����üĴ���
   λ����UNION�ṹ:  SOC_IOMCU_RTC_CFG_UNION */
#define SOC_IOMCU_RTC_CFG_ADDR(base)                  ((base) + (0x00C))

/* �Ĵ���˵����IOMCU����ʱ��ʹ�ܼĴ���0���Ա���д1��ʹ��IOMCU_CLKSTAT0��Ӧ��ʱ�ӣ�д0��Ӱ��ʱ��ʹ�ܵ�״̬��
   λ����UNION�ṹ:  SOC_IOMCU_CLKEN0_UNION */
#define SOC_IOMCU_CLKEN0_ADDR(base)                   ((base) + (0x010))

/* �Ĵ���˵����IOMCU����ʱ��ʹ�ܼĴ���0���Ա���д1��ʹ��IOMCU_CLKSTAT0��Ӧ��ʱ�ӣ�д0��Ӱ��ʱ��ʹ�ܵ�״̬��
   λ����UNION�ṹ:  SOC_IOMCU_CLKDIS0_UNION */
#define SOC_IOMCU_CLKDIS0_ADDR(base)                  ((base) + (0x014))

/* �Ĵ���˵����IOMCU����ʱ��״̬�Ĵ���0����IOMCU_CLKEN0��IOMCU_CLKDIS0���ý���״̬�޸ġ�
            ����ʱ�ӿ����ź��辭����CRG�н���ͬ��������ˣ�����ļĴ���ֵ���ӳ���Ӧʱ����ļ������ں��������Ӧʱ��״̬��
            �˼Ĵ�����Ӱ�쵽�������߼�����ʱ�ӹر�ʱ�ҷ�������bypass����£��������߼���Ч���ڲ����߷���pslverr�źš�
            ÿ��Bit���壺
            0��ʱ�ӹرգ�
            1��ʱ�Ӵ򿪡�
   λ����UNION�ṹ:  SOC_IOMCU_CLKSTAT0_UNION */
#define SOC_IOMCU_CLKSTAT0_ADDR(base)                 ((base) + (0x018))

/* �Ĵ���˵����IOMCU������λʹ�ܼĴ���0������ʹ��IOMCU_RSTSTAT0��λ���Ա���д1����ӦIP���븴λ״̬��д0��Ӱ�츴λ״̬��
   λ����UNION�ṹ:  SOC_IOMCU_RSTEN0_UNION */
#define SOC_IOMCU_RSTEN0_ADDR(base)                   ((base) + (0x020))

/* �Ĵ���˵����IOMCU������λʹ�ܼĴ���0������ʹ��IOMCU_RSTSTAT0��λ���Ա���д1����ӦIP����⸴λ״̬��д0��Ӱ�츴λ״̬��
   λ����UNION�ṹ:  SOC_IOMCU_RSTDIS0_UNION */
#define SOC_IOMCU_RSTDIS0_ADDR(base)                  ((base) + (0x024))

/* �Ĵ���˵����ALWAYSON�����踴λ״̬�Ĵ���4����SC_PERIPH_RSTEN4��SC_PERIPH_RSTDIS4���ý���״̬�޸ġ��⸴λ�����ź��辭��ͬ��������ˣ�����ļĴ���ֵ���ӳ���Ӧʱ����ļ������ں��������Ӧ�⸴λ״̬��
            �˼Ĵ�����Ӱ�쵽�������߼���������߼����ڸ�λ״̬ʱ�ҷ�������bypass����£��������߼���Ч���ڲ����߷���pslverr�źš�
            ÿ��Bit���壺
            0����λ��ʹ�ܣ�
            1����λʹ�ܡ�
   λ����UNION�ṹ:  SOC_IOMCU_RSTSTAT0_UNION */
#define SOC_IOMCU_RSTSTAT0_ADDR(base)                 ((base) + (0x028))

/* �Ĵ���˵����IOMCU M7���üĴ���
   λ����UNION�ṹ:  SOC_IOMCU_M7_CFG0_UNION */
#define SOC_IOMCU_M7_CFG0_ADDR(base)                  ((base) + (0x030))

/* �Ĵ���˵����IOMCU M7���üĴ���
   λ����UNION�ṹ:  SOC_IOMCU_M7_CFG1_UNION */
#define SOC_IOMCU_M7_CFG1_ADDR(base)                  ((base) + (0x034))

/* �Ĵ���˵����IOMCU M7״̬�Ĵ���
   λ����UNION�ṹ:  SOC_IOMCU_M7_STAT0_UNION */
#define SOC_IOMCU_M7_STAT0_ADDR(base)                 ((base) + (0x038))

/* �Ĵ���˵����IOMCU M7״̬�Ĵ���
   λ����UNION�ṹ:  SOC_IOMCU_M7_STAT1_UNION */
#define SOC_IOMCU_M7_STAT1_ADDR(base)                 ((base) + (0x03C))

/* �Ĵ���˵����M3����DDR�Ļ����������üĴ���
   λ����UNION�ṹ:  SOC_IOMCU_DDR_ACCESS_WINDOW_UNION */
#define SOC_IOMCU_DDR_ACCESS_WINDOW_ADDR(base)        ((base) + (0x040))

/* �Ĵ���˵����M3����MMBUF�Ļ����������üĴ���
   λ����UNION�ṹ:  SOC_IOMCU_MMBUF_ACCESS_WINDOW_UNION */
#define SOC_IOMCU_MMBUF_ACCESS_WINDOW_ADDR(base)      ((base) + (0x044))

/* �Ĵ���˵����M3����HACK�Ļ����������üĴ���
   λ����UNION�ṹ:  SOC_IOMCU_HACK_ACCESS_WINDOW_UNION */
#define SOC_IOMCU_HACK_ACCESS_WINDOW_ADDR(base)       ((base) + (0x048))

/* �Ĵ���˵�����������߼�bypass���ƼĴ���
   λ����UNION�ṹ:  SOC_IOMCU_DLOCK_BYPASS_UNION */
#define SOC_IOMCU_DLOCK_BYPASS_ADDR(base)             ((base) + (0x04C))

/* �Ĵ���˵����mem���Ŀ��ƼĴ���
   λ����UNION�ṹ:  SOC_IOMCU_MEM_CTRL_PGT_UNION */
#define SOC_IOMCU_MEM_CTRL_PGT_ADDR(base)             ((base) + (0x050))

/* �Ĵ���˵����mem�������ƼĴ���
   λ����UNION�ṹ:  SOC_IOMCU_MEM_CTRL_UNION */
#define SOC_IOMCU_MEM_CTRL_ADDR(base)                 ((base) + (0x054))

/* �Ĵ���˵����IOMCU״̬��ѯ�Ĵ���
   λ����UNION�ṹ:  SOC_IOMCU_SYS_STAT_UNION */
#define SOC_IOMCU_SYS_STAT_ADDR(base)                 ((base) + (0x058))

/* �Ĵ���˵����IOMCU���ÿ��ƼĴ���
   λ����UNION�ṹ:  SOC_IOMCU_SYS_CONFIG_UNION */
#define SOC_IOMCU_SYS_CONFIG_ADDR(base)               ((base) + (0x05C))

/* �Ĵ���˵����IOMCU��ϵͳ�����жϼĴ���
   λ����UNION�ṹ:  SOC_IOMCU_WAKEUP_EN_UNION */
#define SOC_IOMCU_WAKEUP_EN_ADDR(base)                ((base) + (0x060))

/* �Ĵ���˵����IOMCU��ϵͳ�����ж�����Ĵ���
   λ����UNION�ṹ:  SOC_IOMCU_WAKEUP_CLR_UNION */
#define SOC_IOMCU_WAKEUP_CLR_ADDR(base)               ((base) + (0x064))

/* �Ĵ���˵����IOMCU��ϵͳ�����ж�����Ĵ���
   λ����UNION�ṹ:  SOC_IOMCU_WAKEUP_STAT_UNION */
#define SOC_IOMCU_WAKEUP_STAT_ADDR(base)              ((base) + (0x068))

/* �Ĵ���˵����IOMCU�����ԭʼ����ж�״̬
   λ����UNION�ṹ:  SOC_IOMCU_COMB_INT_RAW_UNION */
#define SOC_IOMCU_COMB_INT_RAW_ADDR(base)             ((base) + (0x070))

/* �Ĵ���˵����IOMCU���������ж�״̬
   λ����UNION�ṹ:  SOC_IOMCU_COMB_INT_MSK_UNION */
#define SOC_IOMCU_COMB_INT_MSK_ADDR(base)             ((base) + (0x074))

/* �Ĵ���˵����IOMCU��������κ�����ж�״̬
   λ����UNION�ṹ:  SOC_IOMCU_COMB_INT_STAT_UNION */
#define SOC_IOMCU_COMB_INT_STAT_ADDR(base)            ((base) + (0x078))

/* �Ĵ���˵����IOMCU�����Զ���Ƶ/��ʱ�ӼĴ���
   λ����UNION�ṹ:  SOC_IOMCU_BUS_AUTO_FREQ_UNION */
#define SOC_IOMCU_BUS_AUTO_FREQ_ADDR(base)            ((base) + (0x080))

/* �Ĵ���˵����MISC�߼�����Ŀ��ƼĴ���
   λ����UNION�ṹ:  SOC_IOMCU_MISC_CTRL_UNION */
#define SOC_IOMCU_MISC_CTRL_ADDR(base)                ((base) + (0x084))

/* �Ĵ���˵����NOC ����źŵĿ���
   λ����UNION�ṹ:  SOC_IOMCU_NOC_CTRL_UNION */
#define SOC_IOMCU_NOC_CTRL_ADDR(base)                 ((base) + (0x088))

/* �Ĵ���˵����IOMCU M7���üĴ���2
   λ����UNION�ṹ:  SOC_IOMCU_M7_CFG2_UNION */
#define SOC_IOMCU_M7_CFG2_ADDR(base)                  ((base) + (0x08C))

/* �Ĵ���˵����IOMCU����ʱ��ʹ�ܼĴ���1���Ա���д1��ʹ��IOMCU_CLKSTAT0��Ӧ��ʱ�ӣ�д0��Ӱ��ʱ��ʹ�ܵ�״̬��
   λ����UNION�ṹ:  SOC_IOMCU_CLKEN1_UNION */
#define SOC_IOMCU_CLKEN1_ADDR(base)                   ((base) + (0x090))

/* �Ĵ���˵����IOMCU����ʱ��ʹ�ܼĴ���1���Ա���д1��ʹ��IOMCU_CLKSTAT0��Ӧ��ʱ�ӣ�д0��Ӱ��ʱ��ʹ�ܵ�״̬��
   λ����UNION�ṹ:  SOC_IOMCU_CLKDIS1_UNION */
#define SOC_IOMCU_CLKDIS1_ADDR(base)                  ((base) + (0x094))

/* �Ĵ���˵����IOMCU����ʱ��״̬�Ĵ���1����IOMCU_CLKEN0��IOMCU_CLKDIS0���ý���״̬�޸ġ�
            ����ʱ�ӿ����ź��辭����CRG�н���ͬ��������ˣ�����ļĴ���ֵ���ӳ���Ӧʱ����ļ������ں��������Ӧʱ��״̬��
            ÿ��Bit���壺
            0��ʱ�ӹرգ�
            1��ʱ�Ӵ򿪡�
   λ����UNION�ṹ:  SOC_IOMCU_CLKSTAT1_UNION */
#define SOC_IOMCU_CLKSTAT1_ADDR(base)                 ((base) + (0x098))

/* �Ĵ���˵������ȫTZPCλ�����԰�ȫ����0��ʾ��ȫ��1��ʾ�ǰ�ȫ��
   λ����UNION�ṹ:  SOC_IOMCU_SEC_TZPC_UNION */
#define SOC_IOMCU_SEC_TZPC_ADDR(base)                 ((base) + (0x0100))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_IOMCU_SEC_RES_UNION */
#define SOC_IOMCU_SEC_RES_ADDR(base)                  ((base) + (0x104))





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
                     (1/1) reg_define
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_IOMCU_CLK_SEL_UNION
 �ṹ˵��  : CLK_SEL �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x055558C5�����:32
 �Ĵ���˵��: IOMCUʱ��ѡ��Ĵ���������ѡ��ʱ�ӡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  clk_mcu_sel         : 2;  /* bit[0-1]  : Cortex M7ʱ��Դѡ��
                                                               2'b00:32K��
                                                               2'b01:TCX0��
                                                               2'b10:PPLL0��
                                                               2'b11:FLL */
        unsigned int  clk_mcu_sel_stat    : 2;  /* bit[2-3]  : Cortex M7ʱ��Դ״̬��
                                                               2'b00:32K��
                                                               2'b01:TCX0��
                                                               2'b10:PPLL0��
                                                               2'b11:FLL */
        unsigned int  clk_mmbuf_sel       : 2;  /* bit[4-5]  : MMBUF��ʱ���л� 
                                                               00��TCXO
                                                               01��FPLL
                                                               1x: PPLL0 */
        unsigned int  clk_mmbuf_sel_stat  : 2;  /* bit[6-7]  : MMBUF��ʱ���л�״̬
                                                               00��TCXO
                                                               01��FPLL
                                                               1x: PPLL0 */
        unsigned int  clk_nocbus_sel      : 2;  /* bit[8-9]  : AO_BUS��ʱ���л�
                                                               00��TCXO
                                                               01��FPLL
                                                               10��DDRPLL
                                                               11: PPLL0 */
        unsigned int  clk_nocbus_sel_stat : 2;  /* bit[10-11]: AO_BUS��ʱ���л�״̬
                                                               00��TCXO
                                                               01��FPLL
                                                               10��DDRPLL
                                                               11: PPLL0 */
        unsigned int  clk_peri0_sel       : 2;  /* bit[12-13]: IOMCU Peir0(UART)ʱ��Դѡ��
                                                               2'b00:FLL��
                                                               2'b01:TCXO��
                                                               2'b10:PPLL0��
                                                               2'b11:Reserved */
        unsigned int  clk_peri1_sel       : 2;  /* bit[14-15]: IOMCU Peir1(SPI)ʱ��Դѡ��
                                                               2'b00:FLL��
                                                               2'b01:TCXO��
                                                               2'b10:PPLL0��
                                                               2'b11:Reserved */
        unsigned int  clk_peri2_sel       : 2;  /* bit[16-17]: IOMCU Peir2(I2C)ʱ��Դѡ��
                                                               2'b00:FLL��
                                                               2'b01:TCXO��
                                                               2'b10:PPLL0��
                                                               2'b11:Reserved */
        unsigned int  clk_peri3_sel       : 2;  /* bit[18-19]: IOMCU Peir3(BLPWM)ʱ��Դѡ��
                                                               2'b00:FLL��
                                                               2'b01:TCXO��
                                                               2'b10:PPLL0��
                                                               2'b11:Reserved */
        unsigned int  clk_peri0_sel_stat  : 2;  /* bit[20-21]: IOMCU Peir0(UART)ʱ��Դ״̬��
                                                               2'b00:FLL��
                                                               2'b01:TCXO��
                                                               2'b10:PPLL0��
                                                               2'b11:Reserved */
        unsigned int  clk_peri1_sel_stat  : 2;  /* bit[22-23]: IOMCU Peir1(SPI)ʱ��Դ״̬��
                                                               2'b00:FLL��
                                                               2'b01:TCXO��
                                                               2'b10:PPLL0��
                                                               2'b11:Reserved */
        unsigned int  clk_peri2_sel_stat  : 2;  /* bit[24-25]: IOMCU Peir2(I2C)ʱ��Դ״̬��
                                                               2'b00:FLL��
                                                               2'b01:TCXO��
                                                               2'b10:PPLL0��
                                                               2'b11:Reserved */
        unsigned int  clk_peri3_sel_stat  : 2;  /* bit[26-27]: IOMCU Peir3(BLPWM)ʱ��Դ״̬��
                                                               2'b00:FLL��
                                                               2'b01:TCXO��
                                                               2'b10:PPLL0��
                                                               2'b11:Reserved */
        unsigned int  clk_pll_stable      : 1;  /* bit[28]   : IOMCU�ⲿPLL�ȶ��ź� */
        unsigned int  clk_fll_stable      : 1;  /* bit[29]   : IOMCU�ⲿFLL�ȶ��ź� */
        unsigned int  reserved            : 2;  /* bit[30-31]: reserved */
    } reg;
} SOC_IOMCU_CLK_SEL_UNION;
#endif
#define SOC_IOMCU_CLK_SEL_clk_mcu_sel_START          (0)
#define SOC_IOMCU_CLK_SEL_clk_mcu_sel_END            (1)
#define SOC_IOMCU_CLK_SEL_clk_mcu_sel_stat_START     (2)
#define SOC_IOMCU_CLK_SEL_clk_mcu_sel_stat_END       (3)
#define SOC_IOMCU_CLK_SEL_clk_mmbuf_sel_START        (4)
#define SOC_IOMCU_CLK_SEL_clk_mmbuf_sel_END          (5)
#define SOC_IOMCU_CLK_SEL_clk_mmbuf_sel_stat_START   (6)
#define SOC_IOMCU_CLK_SEL_clk_mmbuf_sel_stat_END     (7)
#define SOC_IOMCU_CLK_SEL_clk_nocbus_sel_START       (8)
#define SOC_IOMCU_CLK_SEL_clk_nocbus_sel_END         (9)
#define SOC_IOMCU_CLK_SEL_clk_nocbus_sel_stat_START  (10)
#define SOC_IOMCU_CLK_SEL_clk_nocbus_sel_stat_END    (11)
#define SOC_IOMCU_CLK_SEL_clk_peri0_sel_START        (12)
#define SOC_IOMCU_CLK_SEL_clk_peri0_sel_END          (13)
#define SOC_IOMCU_CLK_SEL_clk_peri1_sel_START        (14)
#define SOC_IOMCU_CLK_SEL_clk_peri1_sel_END          (15)
#define SOC_IOMCU_CLK_SEL_clk_peri2_sel_START        (16)
#define SOC_IOMCU_CLK_SEL_clk_peri2_sel_END          (17)
#define SOC_IOMCU_CLK_SEL_clk_peri3_sel_START        (18)
#define SOC_IOMCU_CLK_SEL_clk_peri3_sel_END          (19)
#define SOC_IOMCU_CLK_SEL_clk_peri0_sel_stat_START   (20)
#define SOC_IOMCU_CLK_SEL_clk_peri0_sel_stat_END     (21)
#define SOC_IOMCU_CLK_SEL_clk_peri1_sel_stat_START   (22)
#define SOC_IOMCU_CLK_SEL_clk_peri1_sel_stat_END     (23)
#define SOC_IOMCU_CLK_SEL_clk_peri2_sel_stat_START   (24)
#define SOC_IOMCU_CLK_SEL_clk_peri2_sel_stat_END     (25)
#define SOC_IOMCU_CLK_SEL_clk_peri3_sel_stat_START   (26)
#define SOC_IOMCU_CLK_SEL_clk_peri3_sel_stat_END     (27)
#define SOC_IOMCU_CLK_SEL_clk_pll_stable_START       (28)
#define SOC_IOMCU_CLK_SEL_clk_pll_stable_END         (28)
#define SOC_IOMCU_CLK_SEL_clk_fll_stable_START       (29)
#define SOC_IOMCU_CLK_SEL_clk_fll_stable_END         (29)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_CFG_DIV0_UNION
 �ṹ˵��  : CFG_DIV0 �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x07151515�����:32
 �Ĵ���˵��: IOMCU��Ƶ�Ĵ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomcu_mcu0_div        : 2;  /* bit[0-1]  : Cortex M7��ʱ�ӷ�Ƶ��˫���Ƶ��һ��ķ�Ƶϵ�� */
        unsigned int  iomcu_apb_l_div_pre   : 2;  /* bit[2-3]  : IOMCU��ϵͳ�ڵ���APB��ʱ��˫���Ƶ����һ��ķ�Ƶϵ�� */
        unsigned int  iomcu_apb_l_div       : 2;  /* bit[4-5]  : IOMCU��ϵͳ�ڵ���APB��ʱ��˫���Ƶ���ڶ���ķ�Ƶϵ�� */
        unsigned int  reserved_0            : 1;  /* bit[6]    : reserved */
        unsigned int  iomcu_apb_l_div_en    : 1;  /* bit[7]    : ǰ0~6λ��ʹ�� */
        unsigned int  iomcu_apb_h_div       : 2;  /* bit[8-9]  : IOMCU��ϵͳ�ڸ���APB��ʱ�ӷ�Ƶ����Ƶϵ�� */
        unsigned int  iomcu_mcu1_div        : 2;  /* bit[10-11]: Cortex M7��ʱ�ӷ�Ƶ��˫���Ƶ�еڶ���ķ�Ƶϵ�� */
        unsigned int  iomcu_peri0_div       : 2;  /* bit[12-13]: IOMCU��ϵͳ��PERI0��UART������ʱ�ӷ�Ƶ����Ƶϵ�� */
        unsigned int  reserved_1            : 1;  /* bit[14]   : reserved */
        unsigned int  iomcu_peri_ahb_div_en : 1;  /* bit[15]   : ǰ7~14bitλ��ʹ�� */
        unsigned int  iomcu_peri1_div       : 2;  /* bit[16-17]: IOMCU��ϵͳ��PERI1(SPI)����ʱ�ӷ�Ƶ����Ƶϵ�� */
        unsigned int  iomcu_peri2_div       : 2;  /* bit[18-19]: IOMCU��ϵͳ��PERI2(I2C)����ʱ�ӷ�Ƶ����Ƶϵ�� */
        unsigned int  iomcu_peri3_div       : 2;  /* bit[20-21]: IOMCU��ϵͳ��PERI3(BLPWM)����ʱ�ӷ�Ƶ����Ƶϵ�� */
        unsigned int  reserved_2            : 1;  /* bit[22]   : reserved */
        unsigned int  iomcu_peri_div_en     : 1;  /* bit[23]   : ǰ15~22bitλ��ʹ�� */
        unsigned int  iomcu_div             : 6;  /* bit[24-29]: IOMCU��ϵͳ������PPLL0ʱ�ӷ�Ƶ����Ƶϵ�� */
        unsigned int  reserved_3            : 1;  /* bit[30]   : reserved */
        unsigned int  iomcu_div_en          : 1;  /* bit[31]   : IOMCU��ϵͳ������PPLL0ʱ�ӷ�Ƶ����Ƶϵ��ʹ�� */
    } reg;
} SOC_IOMCU_CFG_DIV0_UNION;
#endif
#define SOC_IOMCU_CFG_DIV0_iomcu_mcu0_div_START         (0)
#define SOC_IOMCU_CFG_DIV0_iomcu_mcu0_div_END           (1)
#define SOC_IOMCU_CFG_DIV0_iomcu_apb_l_div_pre_START    (2)
#define SOC_IOMCU_CFG_DIV0_iomcu_apb_l_div_pre_END      (3)
#define SOC_IOMCU_CFG_DIV0_iomcu_apb_l_div_START        (4)
#define SOC_IOMCU_CFG_DIV0_iomcu_apb_l_div_END          (5)
#define SOC_IOMCU_CFG_DIV0_iomcu_apb_l_div_en_START     (7)
#define SOC_IOMCU_CFG_DIV0_iomcu_apb_l_div_en_END       (7)
#define SOC_IOMCU_CFG_DIV0_iomcu_apb_h_div_START        (8)
#define SOC_IOMCU_CFG_DIV0_iomcu_apb_h_div_END          (9)
#define SOC_IOMCU_CFG_DIV0_iomcu_mcu1_div_START         (10)
#define SOC_IOMCU_CFG_DIV0_iomcu_mcu1_div_END           (11)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri0_div_START        (12)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri0_div_END          (13)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri_ahb_div_en_START  (15)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri_ahb_div_en_END    (15)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri1_div_START        (16)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri1_div_END          (17)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri2_div_START        (18)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri2_div_END          (19)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri3_div_START        (20)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri3_div_END          (21)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri_div_en_START      (23)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri_div_en_END        (23)
#define SOC_IOMCU_CFG_DIV0_iomcu_div_START              (24)
#define SOC_IOMCU_CFG_DIV0_iomcu_div_END                (29)
#define SOC_IOMCU_CFG_DIV0_iomcu_div_en_START           (31)
#define SOC_IOMCU_CFG_DIV0_iomcu_div_en_END             (31)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_CFG_DIV1_UNION
 �ṹ˵��  : CFG_DIV1 �Ĵ����ṹ���塣��ַƫ����:0x008����ֵ:0x0000000F�����:32
 �Ĵ���˵��: IOMCU��Ƶ�Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomcu_mcu0_div_nopending : 2;  /* bit[0-1]  : Cortex M7��ʱ��������idle̬˫���Ƶ����һ�η�Ƶϵ�� */
        unsigned int  iomcu_mcu1_div_nopending : 2;  /* bit[2-3]  : Cortex M7��ʱ��������idle̬˫���Ƶ���ڶ����Ƶϵ�� */
        unsigned int  reserved_0               : 3;  /* bit[4-6]  : reserved */
        unsigned int  reserved_1               : 1;  /* bit[7]    : Cortex M7��ʱ��������idle̬��Ƶ����Ƶϵ������ʹ�� */
        unsigned int  reserved_2               : 7;  /* bit[8-14] : reserved */
        unsigned int  reserved_3               : 1;  /* bit[15]   : reserved */
        unsigned int  reserved_4               : 7;  /* bit[16-22]: reserved */
        unsigned int  reserved_5               : 1;  /* bit[23]   : reserved */
        unsigned int  reserved_6               : 7;  /* bit[24-30]: reserved */
        unsigned int  reserved_7               : 1;  /* bit[31]   : reserved */
    } reg;
} SOC_IOMCU_CFG_DIV1_UNION;
#endif
#define SOC_IOMCU_CFG_DIV1_iomcu_mcu0_div_nopending_START  (0)
#define SOC_IOMCU_CFG_DIV1_iomcu_mcu0_div_nopending_END    (1)
#define SOC_IOMCU_CFG_DIV1_iomcu_mcu1_div_nopending_START  (2)
#define SOC_IOMCU_CFG_DIV1_iomcu_mcu1_div_nopending_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_RTC_CFG_UNION
 �ṹ˵��  : RTC_CFG �Ĵ����ṹ���塣��ַƫ����:0x00C����ֵ:0x000024A2�����:32
 �Ĵ���˵��: RTCʱ�����üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rtc_clk_sel       : 1;  /* bit[0]    : RTCʱ��Դѡ��
                                                             0��19.2MHz/586
                                                             1��32768Hz */
        unsigned int  rtc_crc_clken     : 1;  /* bit[1]    : CRCģ���ʱ��ʹ�� */
        unsigned int  reserved_0        : 2;  /* bit[2-3]  : reserved */
        unsigned int  rtc_div_quotient  : 11; /* bit[4-14] : RTC��Ƶ�������� */
        unsigned int  reserved_1        : 1;  /* bit[15]   : reserved */
        unsigned int  rtc_div_remainder : 10; /* bit[16-25]: RTC��Ƶ�������� */
        unsigned int  reserved_2        : 6;  /* bit[26-31]: reserved */
    } reg;
} SOC_IOMCU_RTC_CFG_UNION;
#endif
#define SOC_IOMCU_RTC_CFG_rtc_clk_sel_START        (0)
#define SOC_IOMCU_RTC_CFG_rtc_clk_sel_END          (0)
#define SOC_IOMCU_RTC_CFG_rtc_crc_clken_START      (1)
#define SOC_IOMCU_RTC_CFG_rtc_crc_clken_END        (1)
#define SOC_IOMCU_RTC_CFG_rtc_div_quotient_START   (4)
#define SOC_IOMCU_RTC_CFG_rtc_div_quotient_END     (14)
#define SOC_IOMCU_RTC_CFG_rtc_div_remainder_START  (16)
#define SOC_IOMCU_RTC_CFG_rtc_div_remainder_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_CLKEN0_UNION
 �ṹ˵��  : CLKEN0 �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x0367C000�����:32
 �Ĵ���˵��: IOMCU����ʱ��ʹ�ܼĴ���0���Ա���д1��ʹ��IOMCU_CLKSTAT0��Ӧ��ʱ�ӣ�д0��Ӱ��ʱ��ʹ�ܵ�״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomcu_clken0_0dmac         : 1;  /* bit[0] : 0dmac */
        unsigned int  iomcu_clken0_lwdt          : 1;  /* bit[1] : lwdt */
        unsigned int  iomcu_clken0_2timer        : 1;  /* bit[2] : 2timer */
        unsigned int  iomcu_clken0_3i2c0         : 1;  /* bit[3] : 3i2c0 */
        unsigned int  iomcu_clken0_4i2c1         : 1;  /* bit[4] : 4i2c1 */
        unsigned int  iomcu_clken0_5i2c2         : 1;  /* bit[5] : 5i2c2 */
        unsigned int  iomcu_clken0_6gpio0        : 1;  /* bit[6] : 6gpio0 */
        unsigned int  iomcu_clken0_7gpio1        : 1;  /* bit[7] : 7gpio1 */
        unsigned int  iomcu_clken0_8gpio2        : 1;  /* bit[8] : 8gpio2 */
        unsigned int  iomcu_clken0_9gpio3        : 1;  /* bit[9] : 9gpio3 */
        unsigned int  iomcu_clken0_10spi0        : 1;  /* bit[10]: 10spi0 */
        unsigned int  iomcu_clken0_11uart3       : 1;  /* bit[11]: 11uart3 */
        unsigned int  iomcu_clken0_12uart7       : 1;  /* bit[12]: 12uart7 */
        unsigned int  iomcu_clken0_13blpwm       : 1;  /* bit[13]: 13blpwm */
        unsigned int  iomcu_clken0_14fclk_mcu    : 1;  /* bit[14]: 14fclk_mcu */
        unsigned int  iomcu_clken0_15clk_mcu     : 1;  /* bit[15]: 15clk_mcu */
        unsigned int  iomcu_clken0_16clk_etm     : 1;  /* bit[16]: 16clk_etm */
        unsigned int  iomcu_clken0_17aclk_mcu    : 1;  /* bit[17]: 17aclk_mcu */
        unsigned int  iomcu_clken0_18hclk_mcu    : 1;  /* bit[18]: 18hclk_mcu */
        unsigned int  iomcu_clken0_19clk_fll     : 1;  /* bit[19]: 19clk_fll */
        unsigned int  iomcu_clken0_20clk_ppll0   : 1;  /* bit[20]: 20clk_ppll0 */
        unsigned int  iomcu_clken0_21clk_dapb    : 1;  /* bit[21]: 21clk_dapb */
        unsigned int  iomcu_clken0_22clk_atb     : 1;  /* bit[22]: 22clk_atb */
        unsigned int  iomcu_clken0_23pclk_rtc    : 1;  /* bit[23]: 23pclk_rtc */
        unsigned int  iomcu_clken0_24clk_ctm     : 1;  /* bit[24]: 24clk_ctm */
        unsigned int  iomcu_clken0_25clk_tcxo_in : 1;  /* bit[25]: 25clk_tcxo_in */
        unsigned int  iomcu_clken0_26tcm         : 1;  /* bit[26]: 26tcm */
        unsigned int  iomcu_clken0_27i2c6        : 1;  /* bit[27]: 27i2c6 */
        unsigned int  iomcu_clken0_28mmbuf       : 1;  /* bit[28]: ��λ��ʱ�������� */
        unsigned int  iomcu_clken0_29ao_bus      : 1;  /* bit[29]: ��λ��ʱ�������� */
        unsigned int  iomcu_clken0_30spi2        : 1;  /* bit[30]: 30spi2 */
        unsigned int  iomcu_clken0_31uart8       : 1;  /* bit[31]: 31uart8 */
    } reg;
} SOC_IOMCU_CLKEN0_UNION;
#endif
#define SOC_IOMCU_CLKEN0_iomcu_clken0_0dmac_START          (0)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_0dmac_END            (0)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_lwdt_START           (1)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_lwdt_END             (1)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_2timer_START         (2)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_2timer_END           (2)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_3i2c0_START          (3)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_3i2c0_END            (3)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_4i2c1_START          (4)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_4i2c1_END            (4)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_5i2c2_START          (5)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_5i2c2_END            (5)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_6gpio0_START         (6)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_6gpio0_END           (6)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_7gpio1_START         (7)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_7gpio1_END           (7)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_8gpio2_START         (8)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_8gpio2_END           (8)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_9gpio3_START         (9)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_9gpio3_END           (9)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_10spi0_START         (10)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_10spi0_END           (10)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_11uart3_START        (11)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_11uart3_END          (11)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_12uart7_START        (12)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_12uart7_END          (12)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_13blpwm_START        (13)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_13blpwm_END          (13)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_14fclk_mcu_START     (14)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_14fclk_mcu_END       (14)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_15clk_mcu_START      (15)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_15clk_mcu_END        (15)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_16clk_etm_START      (16)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_16clk_etm_END        (16)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_17aclk_mcu_START     (17)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_17aclk_mcu_END       (17)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_18hclk_mcu_START     (18)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_18hclk_mcu_END       (18)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_19clk_fll_START      (19)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_19clk_fll_END        (19)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_20clk_ppll0_START    (20)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_20clk_ppll0_END      (20)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_21clk_dapb_START     (21)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_21clk_dapb_END       (21)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_22clk_atb_START      (22)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_22clk_atb_END        (22)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_23pclk_rtc_START     (23)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_23pclk_rtc_END       (23)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_24clk_ctm_START      (24)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_24clk_ctm_END        (24)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_25clk_tcxo_in_START  (25)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_25clk_tcxo_in_END    (25)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_26tcm_START          (26)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_26tcm_END            (26)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_27i2c6_START         (27)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_27i2c6_END           (27)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_28mmbuf_START        (28)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_28mmbuf_END          (28)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_29ao_bus_START       (29)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_29ao_bus_END         (29)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_30spi2_START         (30)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_30spi2_END           (30)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_31uart8_START        (31)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_31uart8_END          (31)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_CLKDIS0_UNION
 �ṹ˵��  : CLKDIS0 �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x00000000�����:32
 �Ĵ���˵��: IOMCU����ʱ��ʹ�ܼĴ���0���Ա���д1��ʹ��IOMCU_CLKSTAT0��Ӧ��ʱ�ӣ�д0��Ӱ��ʱ��ʹ�ܵ�״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomcu_clkdis0_0dmac         : 1;  /* bit[0] : 0dmac */
        unsigned int  iomcu_clkdis0_lwdt          : 1;  /* bit[1] : lwdt */
        unsigned int  iomcu_clkdis0_2timer        : 1;  /* bit[2] : 2timer */
        unsigned int  iomcu_clkdis0_3i2c0         : 1;  /* bit[3] : 3i2c0 */
        unsigned int  iomcu_clkdis0_4i2c1         : 1;  /* bit[4] : 4i2c1 */
        unsigned int  iomcu_clkdis0_5i2c2         : 1;  /* bit[5] : 5i2c2 */
        unsigned int  iomcu_clkdis0_6gpio0        : 1;  /* bit[6] : 6gpio0 */
        unsigned int  iomcu_clkdis0_7gpio1        : 1;  /* bit[7] : 7gpio1 */
        unsigned int  iomcu_clkdis0_8gpio2        : 1;  /* bit[8] : 8gpio2 */
        unsigned int  iomcu_clkdis0_9gpio3        : 1;  /* bit[9] : 9gpio3 */
        unsigned int  iomcu_clkdis0_10spi0        : 1;  /* bit[10]: 10spi0 */
        unsigned int  iomcu_clkdis0_11uart3       : 1;  /* bit[11]: 11uart3 */
        unsigned int  iomcu_clkdis0_12uart7       : 1;  /* bit[12]: 12uart7 */
        unsigned int  iomcu_clkdis0_13blpwm       : 1;  /* bit[13]: 13blpwm */
        unsigned int  iomcu_clkdis0_14fclk_mcu    : 1;  /* bit[14]: 14fclk_mcu */
        unsigned int  iomcu_clkdis0_15clk_mcu     : 1;  /* bit[15]: 15clk_mcu */
        unsigned int  iomcu_clkdis0_16clk_etm     : 1;  /* bit[16]: 16clk_etm */
        unsigned int  iomcu_clkdis0_17aclk_mcu    : 1;  /* bit[17]: 17aclk_mcu */
        unsigned int  iomcu_clkdis0_18hclk_mcu    : 1;  /* bit[18]: 18hclk_mcu */
        unsigned int  iomcu_clkdis0_19clk_fll     : 1;  /* bit[19]: 19clk_fll */
        unsigned int  iomcu_clkdis0_20clk_ppll0   : 1;  /* bit[20]: 20clk_ppll0 */
        unsigned int  iomcu_clkdis0_21clk_dapb    : 1;  /* bit[21]: 21clk_dapb */
        unsigned int  iomcu_clkdis0_22clk_atb     : 1;  /* bit[22]: 22clk_atb */
        unsigned int  iomcu_clkdis0_23pclk_rtc    : 1;  /* bit[23]: 23pclk_rtc */
        unsigned int  iomcu_clkdis0_24clk_ctm     : 1;  /* bit[24]: 24clk_ctm */
        unsigned int  iomcu_clkdis0_25clk_tcxo_in : 1;  /* bit[25]: 25clk_tcxo_in */
        unsigned int  iomcu_clkdis0_26tcm         : 1;  /* bit[26]: 26tcm */
        unsigned int  iomcu_clkdis0_27i2c6        : 1;  /* bit[27]: 27i2c6 */
        unsigned int  iomcu_clkdis0_28mmbuf       : 1;  /* bit[28]: ��λ��ʱ�������� */
        unsigned int  iomcu_clkdis0_29ao_bus      : 1;  /* bit[29]: ��λ��ʱ�������� */
        unsigned int  iomcu_clkdis0_30spi2        : 1;  /* bit[30]: 30spi2 */
        unsigned int  iomcu_clkdis0_31uart8       : 1;  /* bit[31]: 31uart8 */
    } reg;
} SOC_IOMCU_CLKDIS0_UNION;
#endif
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_0dmac_START          (0)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_0dmac_END            (0)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_lwdt_START           (1)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_lwdt_END             (1)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_2timer_START         (2)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_2timer_END           (2)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_3i2c0_START          (3)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_3i2c0_END            (3)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_4i2c1_START          (4)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_4i2c1_END            (4)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_5i2c2_START          (5)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_5i2c2_END            (5)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_6gpio0_START         (6)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_6gpio0_END           (6)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_7gpio1_START         (7)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_7gpio1_END           (7)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_8gpio2_START         (8)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_8gpio2_END           (8)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_9gpio3_START         (9)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_9gpio3_END           (9)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_10spi0_START         (10)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_10spi0_END           (10)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_11uart3_START        (11)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_11uart3_END          (11)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_12uart7_START        (12)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_12uart7_END          (12)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_13blpwm_START        (13)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_13blpwm_END          (13)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_14fclk_mcu_START     (14)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_14fclk_mcu_END       (14)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_15clk_mcu_START      (15)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_15clk_mcu_END        (15)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_16clk_etm_START      (16)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_16clk_etm_END        (16)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_17aclk_mcu_START     (17)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_17aclk_mcu_END       (17)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_18hclk_mcu_START     (18)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_18hclk_mcu_END       (18)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_19clk_fll_START      (19)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_19clk_fll_END        (19)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_20clk_ppll0_START    (20)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_20clk_ppll0_END      (20)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_21clk_dapb_START     (21)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_21clk_dapb_END       (21)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_22clk_atb_START      (22)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_22clk_atb_END        (22)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_23pclk_rtc_START     (23)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_23pclk_rtc_END       (23)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_24clk_ctm_START      (24)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_24clk_ctm_END        (24)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_25clk_tcxo_in_START  (25)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_25clk_tcxo_in_END    (25)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_26tcm_START          (26)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_26tcm_END            (26)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_27i2c6_START         (27)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_27i2c6_END           (27)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_28mmbuf_START        (28)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_28mmbuf_END          (28)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_29ao_bus_START       (29)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_29ao_bus_END         (29)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_30spi2_START         (30)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_30spi2_END           (30)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_31uart8_START        (31)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_31uart8_END          (31)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_CLKSTAT0_UNION
 �ṹ˵��  : CLKSTAT0 �Ĵ����ṹ���塣��ַƫ����:0x018����ֵ:0x0367C000�����:32
 �Ĵ���˵��: IOMCU����ʱ��״̬�Ĵ���0����IOMCU_CLKEN0��IOMCU_CLKDIS0���ý���״̬�޸ġ�
            ����ʱ�ӿ����ź��辭����CRG�н���ͬ��������ˣ�����ļĴ���ֵ���ӳ���Ӧʱ����ļ������ں��������Ӧʱ��״̬��
            �˼Ĵ�����Ӱ�쵽�������߼�����ʱ�ӹر�ʱ�ҷ�������bypass����£��������߼���Ч���ڲ����߷���pslverr�źš�
            ÿ��Bit���壺
            0��ʱ�ӹرգ�
            1��ʱ�Ӵ򿪡�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomcu_clkstat0_0dmac         : 1;  /* bit[0] : 0dmac */
        unsigned int  iomcu_clkstat0_lwdt          : 1;  /* bit[1] : lwdt */
        unsigned int  iomcu_clkstat0_2timer        : 1;  /* bit[2] : 2timer */
        unsigned int  iomcu_clkstat0_3i2c0         : 1;  /* bit[3] : 3i2c0 */
        unsigned int  iomcu_clkstat0_4i2c1         : 1;  /* bit[4] : 4i2c1 */
        unsigned int  iomcu_clkstat0_5i2c2         : 1;  /* bit[5] : 5i2c2 */
        unsigned int  iomcu_clkstat0_6gpio0        : 1;  /* bit[6] : 6gpio0 */
        unsigned int  iomcu_clkstat0_7gpio1        : 1;  /* bit[7] : 7gpio1 */
        unsigned int  iomcu_clkstat0_8gpio2        : 1;  /* bit[8] : 8gpio2 */
        unsigned int  iomcu_clkstat0_9gpio3        : 1;  /* bit[9] : 9gpio3 */
        unsigned int  iomcu_clkstat0_10spi0        : 1;  /* bit[10]: 10spi0 */
        unsigned int  iomcu_clkstat0_11uart3       : 1;  /* bit[11]: 11uart3 */
        unsigned int  iomcu_clkstat0_12uart7       : 1;  /* bit[12]: 12uart7 */
        unsigned int  iomcu_clkstat0_13blpwm       : 1;  /* bit[13]: 13blpwm */
        unsigned int  iomcu_clkstat0_14fclk_mcu    : 1;  /* bit[14]: 14fclk_mcu */
        unsigned int  iomcu_clkstat0_15clk_mcu     : 1;  /* bit[15]: 15clk_mcu */
        unsigned int  iomcu_clkstat0_16clk_etm     : 1;  /* bit[16]: 16clk_etm */
        unsigned int  iomcu_clkstat0_17aclk_mcu    : 1;  /* bit[17]: 17aclk_mcu */
        unsigned int  iomcu_clkstat0_18hclk_mcu    : 1;  /* bit[18]: 18hclk_mcu */
        unsigned int  iomcu_clkstat0_19clk_fll     : 1;  /* bit[19]: 19clk_fll */
        unsigned int  iomcu_clkstat0_20clk_ppll0   : 1;  /* bit[20]: 20clk_ppll0 */
        unsigned int  iomcu_clkstat0_21clk_dapb    : 1;  /* bit[21]: 21clk_dapb */
        unsigned int  iomcu_clkstat0_22clk_atb     : 1;  /* bit[22]: 22clk_atb */
        unsigned int  iomcu_clkstat0_23pclk_rtc    : 1;  /* bit[23]: 23pclk_rtc */
        unsigned int  iomcu_clkstat0_24clk_ctm     : 1;  /* bit[24]: 24clk_ctm */
        unsigned int  iomcu_clkstat0_25clk_tcxo_in : 1;  /* bit[25]: 25clk_tcxo_in */
        unsigned int  iomcu_clkstat0_26tcm         : 1;  /* bit[26]: 26tcm */
        unsigned int  iomcu_clkstat0_27i2c6        : 1;  /* bit[27]: 27i2c6 */
        unsigned int  iomcu_clkstat0_28mmbuf       : 1;  /* bit[28]: ��λ��ʱ�������� */
        unsigned int  iomcu_clkstat0_29ao_bus      : 1;  /* bit[29]: ��λ��ʱ�������� */
        unsigned int  iomcu_clkstat0_30spi2        : 1;  /* bit[30]: 30spi2 */
        unsigned int  iomcu_clkstat0_31uart8       : 1;  /* bit[31]: 31uart8 */
    } reg;
} SOC_IOMCU_CLKSTAT0_UNION;
#endif
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_0dmac_START          (0)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_0dmac_END            (0)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_lwdt_START           (1)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_lwdt_END             (1)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_2timer_START         (2)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_2timer_END           (2)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_3i2c0_START          (3)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_3i2c0_END            (3)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_4i2c1_START          (4)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_4i2c1_END            (4)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_5i2c2_START          (5)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_5i2c2_END            (5)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_6gpio0_START         (6)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_6gpio0_END           (6)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_7gpio1_START         (7)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_7gpio1_END           (7)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_8gpio2_START         (8)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_8gpio2_END           (8)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_9gpio3_START         (9)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_9gpio3_END           (9)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_10spi0_START         (10)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_10spi0_END           (10)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_11uart3_START        (11)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_11uart3_END          (11)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_12uart7_START        (12)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_12uart7_END          (12)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_13blpwm_START        (13)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_13blpwm_END          (13)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_14fclk_mcu_START     (14)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_14fclk_mcu_END       (14)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_15clk_mcu_START      (15)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_15clk_mcu_END        (15)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_16clk_etm_START      (16)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_16clk_etm_END        (16)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_17aclk_mcu_START     (17)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_17aclk_mcu_END       (17)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_18hclk_mcu_START     (18)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_18hclk_mcu_END       (18)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_19clk_fll_START      (19)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_19clk_fll_END        (19)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_20clk_ppll0_START    (20)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_20clk_ppll0_END      (20)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_21clk_dapb_START     (21)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_21clk_dapb_END       (21)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_22clk_atb_START      (22)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_22clk_atb_END        (22)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_23pclk_rtc_START     (23)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_23pclk_rtc_END       (23)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_24clk_ctm_START      (24)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_24clk_ctm_END        (24)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_25clk_tcxo_in_START  (25)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_25clk_tcxo_in_END    (25)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_26tcm_START          (26)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_26tcm_END            (26)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_27i2c6_START         (27)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_27i2c6_END           (27)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_28mmbuf_START        (28)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_28mmbuf_END          (28)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_29ao_bus_START       (29)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_29ao_bus_END         (29)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_30spi2_START         (30)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_30spi2_END           (30)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_31uart8_START        (31)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_31uart8_END          (31)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_RSTEN0_UNION
 �ṹ˵��  : RSTEN0 �Ĵ����ṹ���塣��ַƫ����:0x020����ֵ:0x00000000�����:32
 �Ĵ���˵��: IOMCU������λʹ�ܼĴ���0������ʹ��IOMCU_RSTSTAT0��λ���Ա���д1����ӦIP���븴λ״̬��д0��Ӱ�츴λ״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomcu_rsten0_0dma       : 1;  /* bit[0] : 0dma */
        unsigned int  iomcu_rsten0_1wdt       : 1;  /* bit[1] : 1wdt */
        unsigned int  iomcu_rsten0_2timer     : 1;  /* bit[2] : 2timer */
        unsigned int  iomcu_rsten0_3i2c0      : 1;  /* bit[3] : 3i2c0 */
        unsigned int  iomcu_rsten0_4i2c1      : 1;  /* bit[4] : 4i2c1 */
        unsigned int  iomcu_rsten0_5i2c2      : 1;  /* bit[5] : 5i2c2 */
        unsigned int  iomcu_rsten0_6gpio0     : 1;  /* bit[6] : 6gpio0 */
        unsigned int  iomcu_rsten0_7gpio1     : 1;  /* bit[7] : 7gpio1 */
        unsigned int  iomcu_rsten0_8gpio2     : 1;  /* bit[8] : 8gpio2 */
        unsigned int  iomcu_rsten0_9gpio3     : 1;  /* bit[9] : 9gpio3 */
        unsigned int  iomcu_rsten0_10spi0     : 1;  /* bit[10]: 10spi0 */
        unsigned int  iomcu_rsten0_11uart3    : 1;  /* bit[11]: 11uart3 */
        unsigned int  iomcu_rsten0_12uart7    : 1;  /* bit[12]: 12uart7 */
        unsigned int  iomcu_rsten0_13blpwm    : 1;  /* bit[13]: 13blpwm */
        unsigned int  iomcu_rsten0_14mcu_sys  : 1;  /* bit[14]: 14mcu_sys */
        unsigned int  iomcu_rsten0_15mcu_etm  : 1;  /* bit[15]: 15mcu_etm */
        unsigned int  iomcu_rsten0_16reserved : 1;  /* bit[16]: 16reserved */
        unsigned int  iomcu_rsten0_17reserved : 1;  /* bit[17]: 17reserved */
        unsigned int  iomcu_rsten0_18tcm      : 1;  /* bit[18]: 18tcm */
        unsigned int  iomcu_rsten0_19reserved : 1;  /* bit[19]: 19reserved */
        unsigned int  iomcu_rsten0_20reserved : 1;  /* bit[20]: 20reserved */
        unsigned int  iomcu_rsten0_21dapb     : 1;  /* bit[21]: 21dapb */
        unsigned int  iomcu_rsten0_22atb      : 1;  /* bit[22]: 22atb */
        unsigned int  iomcu_rsten0_23rtc      : 1;  /* bit[23]: 23rtc */
        unsigned int  iomcu_rsten0_24ctm      : 1;  /* bit[24]: 24ctm */
        unsigned int  iomcu_rsten0_25reserved : 1;  /* bit[25]: 25reserved */
        unsigned int  iomcu_rsten0_26reserved : 1;  /* bit[26]: 26reserved */
        unsigned int  iomcu_rsten0_27i2c6     : 1;  /* bit[27]: 27i2c6 */
        unsigned int  iomcu_rsten0_28reserved : 1;  /* bit[28]: 28reserved */
        unsigned int  iomcu_rsten0_29reserved : 1;  /* bit[29]: 29reserved */
        unsigned int  iomcu_rsten0_30spi2     : 1;  /* bit[30]: 30spi2 */
        unsigned int  iomcu_rsten0_31uart8    : 1;  /* bit[31]: 31uart8 */
    } reg;
} SOC_IOMCU_RSTEN0_UNION;
#endif
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_0dma_START        (0)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_0dma_END          (0)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_1wdt_START        (1)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_1wdt_END          (1)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_2timer_START      (2)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_2timer_END        (2)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_3i2c0_START       (3)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_3i2c0_END         (3)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_4i2c1_START       (4)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_4i2c1_END         (4)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_5i2c2_START       (5)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_5i2c2_END         (5)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_6gpio0_START      (6)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_6gpio0_END        (6)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_7gpio1_START      (7)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_7gpio1_END        (7)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_8gpio2_START      (8)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_8gpio2_END        (8)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_9gpio3_START      (9)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_9gpio3_END        (9)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_10spi0_START      (10)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_10spi0_END        (10)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_11uart3_START     (11)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_11uart3_END       (11)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_12uart7_START     (12)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_12uart7_END       (12)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_13blpwm_START     (13)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_13blpwm_END       (13)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_14mcu_sys_START   (14)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_14mcu_sys_END     (14)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_15mcu_etm_START   (15)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_15mcu_etm_END     (15)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_16reserved_START  (16)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_16reserved_END    (16)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_17reserved_START  (17)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_17reserved_END    (17)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_18tcm_START       (18)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_18tcm_END         (18)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_19reserved_START  (19)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_19reserved_END    (19)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_20reserved_START  (20)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_20reserved_END    (20)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_21dapb_START      (21)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_21dapb_END        (21)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_22atb_START       (22)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_22atb_END         (22)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_23rtc_START       (23)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_23rtc_END         (23)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_24ctm_START       (24)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_24ctm_END         (24)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_25reserved_START  (25)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_25reserved_END    (25)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_26reserved_START  (26)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_26reserved_END    (26)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_27i2c6_START      (27)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_27i2c6_END        (27)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_28reserved_START  (28)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_28reserved_END    (28)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_29reserved_START  (29)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_29reserved_END    (29)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_30spi2_START      (30)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_30spi2_END        (30)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_31uart8_START     (31)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_31uart8_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_RSTDIS0_UNION
 �ṹ˵��  : RSTDIS0 �Ĵ����ṹ���塣��ַƫ����:0x024����ֵ:0x00000000�����:32
 �Ĵ���˵��: IOMCU������λʹ�ܼĴ���0������ʹ��IOMCU_RSTSTAT0��λ���Ա���д1����ӦIP����⸴λ״̬��д0��Ӱ�츴λ״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomcu_rstdis0_0dma       : 1;  /* bit[0] : 0dma */
        unsigned int  iomcu_rstdis0_1wdt       : 1;  /* bit[1] : 1wdt */
        unsigned int  iomcu_rstdis0_2timer     : 1;  /* bit[2] : 2timer */
        unsigned int  iomcu_rstdis0_3i2c0      : 1;  /* bit[3] : 3i2c0 */
        unsigned int  iomcu_rstdis0_4i2c1      : 1;  /* bit[4] : 4i2c1 */
        unsigned int  iomcu_rstdis0_5i2c2      : 1;  /* bit[5] : 5i2c2 */
        unsigned int  iomcu_rstdis0_6gpio0     : 1;  /* bit[6] : 6gpio0 */
        unsigned int  iomcu_rstdis0_7gpio1     : 1;  /* bit[7] : 7gpio1 */
        unsigned int  iomcu_rstdis0_8gpio2     : 1;  /* bit[8] : 8gpio2 */
        unsigned int  iomcu_rstdis0_9gpio3     : 1;  /* bit[9] : 9gpio3 */
        unsigned int  iomcu_rstdis0_10spi0     : 1;  /* bit[10]: 10spi0 */
        unsigned int  iomcu_rstdis0_11uart3    : 1;  /* bit[11]: 11uart3 */
        unsigned int  iomcu_rstdis0_12uart7    : 1;  /* bit[12]: 12uart7 */
        unsigned int  iomcu_rstdis0_13blpwm    : 1;  /* bit[13]: 13blpwm */
        unsigned int  iomcu_rstdis0_14mcu_sys  : 1;  /* bit[14]: 14mcu_sys */
        unsigned int  iomcu_rstdis0_15mcu_etm  : 1;  /* bit[15]: 15mcu_etm */
        unsigned int  iomcu_rstdis0_16reserved : 1;  /* bit[16]: 16reserved */
        unsigned int  iomcu_rstdis0_17reserved : 1;  /* bit[17]: 17reserved */
        unsigned int  iomcu_rstdis0_18tcm      : 1;  /* bit[18]: 18tcm */
        unsigned int  iomcu_rstdis0_19reserved : 1;  /* bit[19]: 19reserved */
        unsigned int  iomcu_rstdis0_20reserved : 1;  /* bit[20]: 20reserved */
        unsigned int  iomcu_rstdis0_21dapb     : 1;  /* bit[21]: 21dapb */
        unsigned int  iomcu_rstdis0_22atb      : 1;  /* bit[22]: 22atb */
        unsigned int  iomcu_rstdis0_23rtc      : 1;  /* bit[23]: 23rtc */
        unsigned int  iomcu_rstdis0_24ctm      : 1;  /* bit[24]: 24ctm */
        unsigned int  iomcu_rstdis0_25reserved : 1;  /* bit[25]: 25reserved */
        unsigned int  iomcu_rstdis0_26reserved : 1;  /* bit[26]: 26reserved */
        unsigned int  iomcu_rstdis0_27i2c6     : 1;  /* bit[27]: 27i2c6 */
        unsigned int  iomcu_rstdis0_28reserved : 1;  /* bit[28]: 28reserved */
        unsigned int  iomcu_rstdis0_29reserved : 1;  /* bit[29]: 29reserved */
        unsigned int  iomcu_rstdis0_30spi2     : 1;  /* bit[30]: 30spi2 */
        unsigned int  iomcu_rstdis0_31uart8    : 1;  /* bit[31]: 31uart8 */
    } reg;
} SOC_IOMCU_RSTDIS0_UNION;
#endif
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_0dma_START        (0)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_0dma_END          (0)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_1wdt_START        (1)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_1wdt_END          (1)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_2timer_START      (2)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_2timer_END        (2)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_3i2c0_START       (3)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_3i2c0_END         (3)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_4i2c1_START       (4)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_4i2c1_END         (4)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_5i2c2_START       (5)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_5i2c2_END         (5)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_6gpio0_START      (6)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_6gpio0_END        (6)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_7gpio1_START      (7)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_7gpio1_END        (7)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_8gpio2_START      (8)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_8gpio2_END        (8)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_9gpio3_START      (9)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_9gpio3_END        (9)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_10spi0_START      (10)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_10spi0_END        (10)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_11uart3_START     (11)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_11uart3_END       (11)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_12uart7_START     (12)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_12uart7_END       (12)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_13blpwm_START     (13)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_13blpwm_END       (13)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_14mcu_sys_START   (14)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_14mcu_sys_END     (14)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_15mcu_etm_START   (15)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_15mcu_etm_END     (15)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_16reserved_START  (16)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_16reserved_END    (16)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_17reserved_START  (17)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_17reserved_END    (17)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_18tcm_START       (18)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_18tcm_END         (18)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_19reserved_START  (19)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_19reserved_END    (19)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_20reserved_START  (20)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_20reserved_END    (20)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_21dapb_START      (21)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_21dapb_END        (21)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_22atb_START       (22)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_22atb_END         (22)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_23rtc_START       (23)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_23rtc_END         (23)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_24ctm_START       (24)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_24ctm_END         (24)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_25reserved_START  (25)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_25reserved_END    (25)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_26reserved_START  (26)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_26reserved_END    (26)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_27i2c6_START      (27)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_27i2c6_END        (27)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_28reserved_START  (28)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_28reserved_END    (28)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_29reserved_START  (29)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_29reserved_END    (29)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_30spi2_START      (30)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_30spi2_END        (30)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_31uart8_START     (31)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_31uart8_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_RSTSTAT0_UNION
 �ṹ˵��  : RSTSTAT0 �Ĵ����ṹ���塣��ַƫ����:0x028����ֵ:0xC9E4FFFF�����:32
 �Ĵ���˵��: ALWAYSON�����踴λ״̬�Ĵ���4����SC_PERIPH_RSTEN4��SC_PERIPH_RSTDIS4���ý���״̬�޸ġ��⸴λ�����ź��辭��ͬ��������ˣ�����ļĴ���ֵ���ӳ���Ӧʱ����ļ������ں��������Ӧ�⸴λ״̬��
            �˼Ĵ�����Ӱ�쵽�������߼���������߼����ڸ�λ״̬ʱ�ҷ�������bypass����£��������߼���Ч���ڲ����߷���pslverr�źš�
            ÿ��Bit���壺
            0����λ��ʹ�ܣ�
            1����λʹ�ܡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomcu_rststats0_0dma       : 1;  /* bit[0] : 0dma */
        unsigned int  iomcu_rststats0_1wdt       : 1;  /* bit[1] : 1wdt */
        unsigned int  iomcu_rststats0_2timer     : 1;  /* bit[2] : 2timer */
        unsigned int  iomcu_rststats0_3i2c0      : 1;  /* bit[3] : 3i2c0 */
        unsigned int  iomcu_rststats0_4i2c1      : 1;  /* bit[4] : 4i2c1 */
        unsigned int  iomcu_rststats0_5i2c2      : 1;  /* bit[5] : 5i2c2 */
        unsigned int  iomcu_rststats0_6gpio0     : 1;  /* bit[6] : 6gpio0 */
        unsigned int  iomcu_rststats0_7gpio1     : 1;  /* bit[7] : 7gpio1 */
        unsigned int  iomcu_rststats0_8gpio2     : 1;  /* bit[8] : 8gpio2 */
        unsigned int  iomcu_rststats0_9gpio3     : 1;  /* bit[9] : 9gpio3 */
        unsigned int  iomcu_rststats0_10spi0     : 1;  /* bit[10]: 10spi0 */
        unsigned int  iomcu_rststats0_11uart3    : 1;  /* bit[11]: 11uart3 */
        unsigned int  iomcu_rststats0_12uart7    : 1;  /* bit[12]: 12uart7 */
        unsigned int  iomcu_rststats0_13blpwm    : 1;  /* bit[13]: 13blpwm */
        unsigned int  iomcu_rststats0_14mcu_sys  : 1;  /* bit[14]: 14mcu_sys */
        unsigned int  iomcu_rststats0_15mcu_etm  : 1;  /* bit[15]: 15mcu_etm */
        unsigned int  iomcu_rststats0_16reserved : 1;  /* bit[16]: 16reserved */
        unsigned int  iomcu_rststats0_17reserved : 1;  /* bit[17]: 17reserved */
        unsigned int  iomcu_rststats0_18tcm      : 1;  /* bit[18]: 18tcm */
        unsigned int  iomcu_rststats0_19reserved : 1;  /* bit[19]: 19reserved */
        unsigned int  iomcu_rststats0_20reserved : 1;  /* bit[20]: 20reserved */
        unsigned int  iomcu_rststats0_21dapb     : 1;  /* bit[21]: 21dapb */
        unsigned int  iomcu_rststats0_22atb      : 1;  /* bit[22]: 22atb */
        unsigned int  iomcu_rststats0_23rtc      : 1;  /* bit[23]: 23rtc */
        unsigned int  iomcu_rststats0_24ctm      : 1;  /* bit[24]: 24ctm */
        unsigned int  iomcu_rststats0_25reserved : 1;  /* bit[25]: 25reserved */
        unsigned int  iomcu_rststats0_26reserved : 1;  /* bit[26]: 26reserved */
        unsigned int  iomcu_rststats0_27i2c6     : 1;  /* bit[27]: 27i2c6 */
        unsigned int  iomcu_rststats0_28reserved : 1;  /* bit[28]: 28reserved */
        unsigned int  iomcu_rststats0_29reserved : 1;  /* bit[29]: 29reserved */
        unsigned int  iomcu_rststats0_30spi2     : 1;  /* bit[30]: 30spi2 */
        unsigned int  iomcu_rststat0_31uart8     : 1;  /* bit[31]: 31uart8 */
    } reg;
} SOC_IOMCU_RSTSTAT0_UNION;
#endif
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_0dma_START        (0)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_0dma_END          (0)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_1wdt_START        (1)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_1wdt_END          (1)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_2timer_START      (2)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_2timer_END        (2)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_3i2c0_START       (3)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_3i2c0_END         (3)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_4i2c1_START       (4)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_4i2c1_END         (4)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_5i2c2_START       (5)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_5i2c2_END         (5)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_6gpio0_START      (6)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_6gpio0_END        (6)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_7gpio1_START      (7)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_7gpio1_END        (7)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_8gpio2_START      (8)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_8gpio2_END        (8)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_9gpio3_START      (9)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_9gpio3_END        (9)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_10spi0_START      (10)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_10spi0_END        (10)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_11uart3_START     (11)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_11uart3_END       (11)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_12uart7_START     (12)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_12uart7_END       (12)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_13blpwm_START     (13)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_13blpwm_END       (13)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_14mcu_sys_START   (14)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_14mcu_sys_END     (14)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_15mcu_etm_START   (15)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_15mcu_etm_END     (15)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_16reserved_START  (16)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_16reserved_END    (16)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_17reserved_START  (17)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_17reserved_END    (17)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_18tcm_START       (18)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_18tcm_END         (18)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_19reserved_START  (19)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_19reserved_END    (19)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_20reserved_START  (20)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_20reserved_END    (20)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_21dapb_START      (21)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_21dapb_END        (21)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_22atb_START       (22)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_22atb_END         (22)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_23rtc_START       (23)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_23rtc_END         (23)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_24ctm_START       (24)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_24ctm_END         (24)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_25reserved_START  (25)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_25reserved_END    (25)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_26reserved_START  (26)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_26reserved_END    (26)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_27i2c6_START      (27)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_27i2c6_END        (27)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_28reserved_START  (28)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_28reserved_END    (28)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_29reserved_START  (29)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_29reserved_END    (29)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_30spi2_START      (30)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_30spi2_END        (30)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststat0_31uart8_START      (31)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststat0_31uart8_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_M7_CFG0_UNION
 �ṹ˵��  : M7_CFG0 �Ĵ����ṹ���塣��ַƫ����:0x030����ֵ:0x00000003�����:32
 �Ĵ���˵��: IOMCU M7���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_wait               : 1;  /* bit[0]   : CPU IDLE���ƣ��ڽӸ�λ֮����Ҫ��CPU����IDLE̬���д�����أ����֮���ٳ������ź�
                                                                 0������IDLE
                                                                 1������IDLE */
        unsigned int  hclken_sleeping_bypass : 1;  /* bit[1]   : �����hclk_en:��M7����sleeping̬ʱ���Ƿ��Զ��ر�M7��hclkʱ��
                                                                 0���Զ��ر�M7��hclkʱ��
                                                                 1�����Զ��ر�M7��hclkʱ�� */
        unsigned int  reserved_0             : 1;  /* bit[2]   : reserved */
        unsigned int  cpu_iadbgprot          : 1;  /* bit[3]   : ??? */
        unsigned int  cpu_initvtor           : 25; /* bit[4-28]: M7���������ַ */
        unsigned int  ahbs_ready_error_clr   : 1;  /* bit[29]  : AHBS����READY�ź�Ϊ��ʱ������������״̬����źţ�״̬��IOMCU_M7_STA0[29]�鿴 */
        unsigned int  cfg_bigend             : 1;  /* bit[30]  : M7��С�˵����� */
        unsigned int  reserved_1             : 1;  /* bit[31]  : reserved */
    } reg;
} SOC_IOMCU_M7_CFG0_UNION;
#endif
#define SOC_IOMCU_M7_CFG0_cpu_wait_START                (0)
#define SOC_IOMCU_M7_CFG0_cpu_wait_END                  (0)
#define SOC_IOMCU_M7_CFG0_hclken_sleeping_bypass_START  (1)
#define SOC_IOMCU_M7_CFG0_hclken_sleeping_bypass_END    (1)
#define SOC_IOMCU_M7_CFG0_cpu_iadbgprot_START           (3)
#define SOC_IOMCU_M7_CFG0_cpu_iadbgprot_END             (3)
#define SOC_IOMCU_M7_CFG0_cpu_initvtor_START            (4)
#define SOC_IOMCU_M7_CFG0_cpu_initvtor_END              (28)
#define SOC_IOMCU_M7_CFG0_ahbs_ready_error_clr_START    (29)
#define SOC_IOMCU_M7_CFG0_ahbs_ready_error_clr_END      (29)
#define SOC_IOMCU_M7_CFG0_cfg_bigend_START              (30)
#define SOC_IOMCU_M7_CFG0_cfg_bigend_END                (30)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_M7_CFG1_UNION
 �ṹ˵��  : M7_CFG1 �Ĵ����ṹ���塣��ַƫ����:0x034����ֵ:0xF8000148�����:32
 �Ĵ���˵��: IOMCU M7���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfgstcalib_cycclecnt   : 24; /* bit[0-23]: M7 tickʱ�Ӽ������ڣ�32Kʱ�Ӽ�������Ĭ��10msһ������ */
        unsigned int  cfgstcalib_precision   : 1;  /* bit[24]  : M7�ڲ��������� */
        unsigned int  cfgstcalib_ticken      : 1;  /* bit[25]  : M7�Ƿ�ʹ���ⲿ���� */
        unsigned int  halt_bypass            : 1;  /* bit[26]  : ��M7����halt̬ʱ��Timer�Ƿ����
                                                                 0��������
                                                                 1������ */
        unsigned int  hack_remap_bypass      : 1;  /* bit[27]  : ��hack_mem���ʵ�remap�����Ƿ�bypass
                                                                 0����bypass,��hack_mem�ķ���remap��MMBuf/Harq��
                                                                 1��bypass,��hack_mem�ķ���remap��DDR�� */
        unsigned int  mmbuf_remap_bypass     : 1;  /* bit[28]  : ��mmbuf���ʵ�remap�����Ƿ�bypass
                                                                 0����bypass,��mmbuf�ķ���remap��MMBuf/Harq��
                                                                 1��bypass,��mmbuf�ķ���remap��DDR�� */
        unsigned int  aclken_sleeping_bypass : 1;  /* bit[29]  : �����aclk_en:��M7����sleeping̬ʱ���Ƿ��Զ��ر�M7��AXIʱ��
                                                                 0���Զ��ر�M7��AXIʱ��
                                                                 1�����Զ��ر�M7��AXIʱ�� */
        unsigned int  deepsleeping_bypass    : 1;  /* bit[30]  : ��M7����deepsleeping̬ʱ���Ƿ��Զ��ر�FLL
                                                                 0���Զ��ر�FLL
                                                                 1�����Զ��ر�FLL */
        unsigned int  clken_sleeping_bypass  : 1;  /* bit[31]  : �����clk_en:��M7����sleeping̬ʱ���Ƿ��Զ��ر�M7����ʱ��
                                                                 0���Զ��ر�M7����ʱ��
                                                                 1�����Զ��ر�M7����ʱ�� */
    } reg;
} SOC_IOMCU_M7_CFG1_UNION;
#endif
#define SOC_IOMCU_M7_CFG1_cfgstcalib_cycclecnt_START    (0)
#define SOC_IOMCU_M7_CFG1_cfgstcalib_cycclecnt_END      (23)
#define SOC_IOMCU_M7_CFG1_cfgstcalib_precision_START    (24)
#define SOC_IOMCU_M7_CFG1_cfgstcalib_precision_END      (24)
#define SOC_IOMCU_M7_CFG1_cfgstcalib_ticken_START       (25)
#define SOC_IOMCU_M7_CFG1_cfgstcalib_ticken_END         (25)
#define SOC_IOMCU_M7_CFG1_halt_bypass_START             (26)
#define SOC_IOMCU_M7_CFG1_halt_bypass_END               (26)
#define SOC_IOMCU_M7_CFG1_hack_remap_bypass_START       (27)
#define SOC_IOMCU_M7_CFG1_hack_remap_bypass_END         (27)
#define SOC_IOMCU_M7_CFG1_mmbuf_remap_bypass_START      (28)
#define SOC_IOMCU_M7_CFG1_mmbuf_remap_bypass_END        (28)
#define SOC_IOMCU_M7_CFG1_aclken_sleeping_bypass_START  (29)
#define SOC_IOMCU_M7_CFG1_aclken_sleeping_bypass_END    (29)
#define SOC_IOMCU_M7_CFG1_deepsleeping_bypass_START     (30)
#define SOC_IOMCU_M7_CFG1_deepsleeping_bypass_END       (30)
#define SOC_IOMCU_M7_CFG1_clken_sleeping_bypass_START   (31)
#define SOC_IOMCU_M7_CFG1_clken_sleeping_bypass_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_M7_STAT0_UNION
 �ṹ˵��  : M7_STAT0 �Ĵ����ṹ���塣��ַƫ����:0x038����ֵ:0x00000000�����:32
 �Ĵ���˵��: IOMCU M7״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  m7_iaddr_stat         : 29; /* bit[0-28]: M7ָ��DW��ַ */
        unsigned int  ahbs_ready_error_stat : 1;  /* bit[29]  : AHBS����READY�ź�Ϊ��ʱ���������Ĵ���״ָ̬ʾ��ͬʱ����IOMCU_M7_CFG0[29]����״̬��� */
        unsigned int  cpu_halt_stat         : 1;  /* bit[30]  : CPU HALT״ָ̬ʾ */
        unsigned int  cpu_lockup            : 1;  /* bit[31]  : CPU����ָʾ */
    } reg;
} SOC_IOMCU_M7_STAT0_UNION;
#endif
#define SOC_IOMCU_M7_STAT0_m7_iaddr_stat_START          (0)
#define SOC_IOMCU_M7_STAT0_m7_iaddr_stat_END            (28)
#define SOC_IOMCU_M7_STAT0_ahbs_ready_error_stat_START  (29)
#define SOC_IOMCU_M7_STAT0_ahbs_ready_error_stat_END    (29)
#define SOC_IOMCU_M7_STAT0_cpu_halt_stat_START          (30)
#define SOC_IOMCU_M7_STAT0_cpu_halt_stat_END            (30)
#define SOC_IOMCU_M7_STAT0_cpu_lockup_START             (31)
#define SOC_IOMCU_M7_STAT0_cpu_lockup_END               (31)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_M7_STAT1_UNION
 �ṹ˵��  : M7_STAT1 �Ĵ����ṹ���塣��ַƫ����:0x03C����ֵ:0x00000000�����:32
 �Ĵ���˵��: IOMCU M7״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  m7_sleeping_stat     : 1;  /* bit[0]    : M7������Sleeping״ָ̬ʾ */
        unsigned int  m7_deepsleeping_stat : 1;  /* bit[1]    : M7������DeepSleeping״ָ̬ʾ */
        unsigned int  m7_ahbs_ready_stat   : 1;  /* bit[2]    : M7������Slave�ӿ�readyָʾ�źţ������ź�Ϊ0ʱ�������M7�ڲ����з��� */
        unsigned int  m7_axi_bypass        : 1;  /* bit[3]    : m7 axi��ͶƱ��Sctrl�����Ƿ�ر�AO_BUS/MMBuf��Ӧ��bypass�źţ�0����Bypass,����ʹ��Nopending�źţ�ֱ��AO��ƵMMBUF��ʱ�ӡ����˹���Austin�в�ʵ�֣� */
        unsigned int  m7_ahb_bypass        : 1;  /* bit[4]    : m7 ahb��ͶƱ��Sctrl�����Ƿ�ر�AO_BUS/MMBuf��Ӧ��bypass�źţ�0����Bypass,����ʹ��Nopending�źţ�ֱ��AO��ƵMMBUF��ʱ�ӡ����˹���Austin�в�ʵ�֣� */
        unsigned int  m7_dma_bypass        : 1;  /* bit[5]    : m7 dma��ͶƱ��Sctrl�����Ƿ�ر�AO_BUS/MMBuf��Ӧ��bypass�źţ�0����Bypass,����ʹ��Nopending�źţ�ֱ��AO��ƵMMBUF��ʱ�ӡ����˹���Austin�в�ʵ�֣� */
        unsigned int  m7_sc_stat           : 9;  /* bit[6-14] : M7��ϵͳ�������Խӽӿ�
                                                                ��[6]bit�����Sctrl������ĿǰM7��״̬�Ƿ�Ϊdeepsleep */
        unsigned int  m7_etmpwrupreq       : 1;  /* bit[15]   : M7�ڲ�etmpwrupreqָʾ�ź� */
        unsigned int  reserved             : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_IOMCU_M7_STAT1_UNION;
#endif
#define SOC_IOMCU_M7_STAT1_m7_sleeping_stat_START      (0)
#define SOC_IOMCU_M7_STAT1_m7_sleeping_stat_END        (0)
#define SOC_IOMCU_M7_STAT1_m7_deepsleeping_stat_START  (1)
#define SOC_IOMCU_M7_STAT1_m7_deepsleeping_stat_END    (1)
#define SOC_IOMCU_M7_STAT1_m7_ahbs_ready_stat_START    (2)
#define SOC_IOMCU_M7_STAT1_m7_ahbs_ready_stat_END      (2)
#define SOC_IOMCU_M7_STAT1_m7_axi_bypass_START         (3)
#define SOC_IOMCU_M7_STAT1_m7_axi_bypass_END           (3)
#define SOC_IOMCU_M7_STAT1_m7_ahb_bypass_START         (4)
#define SOC_IOMCU_M7_STAT1_m7_ahb_bypass_END           (4)
#define SOC_IOMCU_M7_STAT1_m7_dma_bypass_START         (5)
#define SOC_IOMCU_M7_STAT1_m7_dma_bypass_END           (5)
#define SOC_IOMCU_M7_STAT1_m7_sc_stat_START            (6)
#define SOC_IOMCU_M7_STAT1_m7_sc_stat_END              (14)
#define SOC_IOMCU_M7_STAT1_m7_etmpwrupreq_START        (15)
#define SOC_IOMCU_M7_STAT1_m7_etmpwrupreq_END          (15)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_DDR_ACCESS_WINDOW_UNION
 �ṹ˵��  : DDR_ACCESS_WINDOW �Ĵ����ṹ���塣��ַƫ����:0x040����ֵ:0x00000000�����:32
 �Ĵ���˵��: M3����DDR�Ļ����������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ddr_access_window : 32; /* bit[0-31]: M7��512MB DDR�ռ����ʱ�����ӵĻ������ʴ��� */
    } reg;
} SOC_IOMCU_DDR_ACCESS_WINDOW_UNION;
#endif
#define SOC_IOMCU_DDR_ACCESS_WINDOW_ddr_access_window_START  (0)
#define SOC_IOMCU_DDR_ACCESS_WINDOW_ddr_access_window_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_MMBUF_ACCESS_WINDOW_UNION
 �ṹ˵��  : MMBUF_ACCESS_WINDOW �Ĵ����ṹ���塣��ַƫ����:0x044����ֵ:0x00000000�����:32
 �Ĵ���˵��: M3����MMBUF�Ļ����������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mmbuf_access_window : 32; /* bit[0-31]: M7��256KB MMBUF�ռ����ʱ�����ӵĻ������ʴ��ڣ����÷�Χ��0x6000_0000~0x7FFF_FFFF�� */
    } reg;
} SOC_IOMCU_MMBUF_ACCESS_WINDOW_UNION;
#endif
#define SOC_IOMCU_MMBUF_ACCESS_WINDOW_mmbuf_access_window_START  (0)
#define SOC_IOMCU_MMBUF_ACCESS_WINDOW_mmbuf_access_window_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_HACK_ACCESS_WINDOW_UNION
 �ṹ˵��  : HACK_ACCESS_WINDOW �Ĵ����ṹ���塣��ַƫ����:0x048����ֵ:0x00000000�����:32
 �Ĵ���˵��: M3����HACK�Ļ����������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hack_access_window : 32; /* bit[0-31]: M7��2MB Hack Mem�ռ����ʱ�����ӵĻ������ʴ��ڣ����÷�Χ��0x6000_0000~0x7FFF_FFFF */
    } reg;
} SOC_IOMCU_HACK_ACCESS_WINDOW_UNION;
#endif
#define SOC_IOMCU_HACK_ACCESS_WINDOW_hack_access_window_START  (0)
#define SOC_IOMCU_HACK_ACCESS_WINDOW_hack_access_window_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_DLOCK_BYPASS_UNION
 �ṹ˵��  : DLOCK_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x04C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������߼�bypass���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass_for_watchdog : 1;  /* bit[0]    : Watchdog���ýӿڷ������߼���·���ƣ���Чʱ����·�߼������ǿ������Ϊ1��bypass����Ĭ��Ϊ0��������·�� */
        unsigned int  bypass_for_timer    : 1;  /* bit[1]    : Timer���ýӿڷ������߼���·���ƣ���Чʱ����·�߼������ǿ������Ϊ1��bypass����Ĭ��Ϊ0��������·�� */
        unsigned int  bypass_for_spi      : 1;  /* bit[2]    : spi���ýӿڷ������߼���·���ƣ���Чʱ����·�߼������ǿ������Ϊ1��bypass����Ĭ��Ϊ0��������·�� */
        unsigned int  bypass_for_gpio0    : 1;  /* bit[3]    : gpio0���ýӿڷ������߼���·���ƣ���Чʱ����·�߼������ǿ������Ϊ1��bypass����Ĭ��Ϊ0��������·�� */
        unsigned int  bypass_for_gpio1    : 1;  /* bit[4]    : gpio1���ýӿڷ������߼���·���ƣ���Чʱ����·�߼������ǿ������Ϊ1��bypass����Ĭ��Ϊ0��������·�� */
        unsigned int  bypass_for_gpio2    : 1;  /* bit[5]    : gpio2���ýӿڷ������߼���·���ƣ���Чʱ����·�߼������ǿ������Ϊ1��bypass����Ĭ��Ϊ0��������·�� */
        unsigned int  bypass_for_gpio3    : 1;  /* bit[6]    : gpio3���ýӿڷ������߼���·���ƣ���Чʱ����·�߼������ǿ������Ϊ1��bypass����Ĭ��Ϊ0��������·�� */
        unsigned int  bypass_for_i2c0     : 1;  /* bit[7]    : i2c0���ýӿڷ������߼���·���ƣ���Чʱ����·�߼������ǿ������Ϊ1��bypass����Ĭ��Ϊ0��������·�� */
        unsigned int  bypass_for_i2c1     : 1;  /* bit[8]    : i2c1���ýӿڷ������߼���·���ƣ���Чʱ����·�߼������ǿ������Ϊ1��bypass����Ĭ��Ϊ0��������·�� */
        unsigned int  bypass_for_i2c2     : 1;  /* bit[9]    : i2c2���ýӿڷ������߼���·���ƣ���Чʱ����·�߼������ǿ������Ϊ1��bypass����Ĭ��Ϊ0��������·�� */
        unsigned int  bypass_for_uart3    : 1;  /* bit[10]   : uart3���ýӿڷ������߼���·���ƣ���Чʱ����·�߼������ǿ������Ϊ1��bypass����Ĭ��Ϊ0��������·�� */
        unsigned int  bypass_for_blpwm    : 1;  /* bit[11]   : blpwm���ýӿڷ������߼���·���ƣ���Чʱ����·�߼������ǿ������Ϊ1��bypass����Ĭ��Ϊ0��������·�� */
        unsigned int  bypass_for_uart7    : 1;  /* bit[12]   : uart7���ýӿڷ������߼���·���ƣ���Чʱ����·�߼������ǿ������Ϊ1��bypass����Ĭ��Ϊ0��������·�� */
        unsigned int  bypass_for_dma      : 1;  /* bit[13]   : dma���ýӿڷ������߼���·���ƣ���Чʱ����·�߼������ǿ������Ϊ1��bypass����Ĭ��Ϊ0��������·�� */
        unsigned int  bypass_for_rtc      : 1;  /* bit[14]   : rtc���ýӿڷ������߼���·���ƣ���Чʱ����·�߼������ǿ������Ϊ1��bypass����Ĭ��Ϊ0��������·�� */
        unsigned int  bypass_for_i2c6     : 1;  /* bit[15]   : i2c6���ýӿڷ������߼���·���ƣ���Чʱ����·�߼������ǿ������Ϊ1��bypass����Ĭ��Ϊ0��������·�� */
        unsigned int  bypass_for_uart8    : 1;  /* bit[16]   : uart8���ýӿڷ������߼���·���ƣ���Чʱ����·�߼������ǿ������Ϊ1��bypass����Ĭ��Ϊ0��������·�� */
        unsigned int  bypass_for_spi2     : 1;  /* bit[17]   : spi2���ýӿڷ������߼���·���ƣ���Чʱ����·�߼������ǿ������Ϊ1��bypass����Ĭ��Ϊ0��������·�� */
        unsigned int  bypass_for_tcm      : 1;  /* bit[18]   : tcm���ýӿڷ������߼���·���ƣ���Чʱ����·�߼������ǿ������Ϊ1��bypass����Ĭ��Ϊ0��������·�� */
        unsigned int  reserved            : 13; /* bit[19-31]: Reserved */
    } reg;
} SOC_IOMCU_DLOCK_BYPASS_UNION;
#endif
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_watchdog_START  (0)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_watchdog_END    (0)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_timer_START     (1)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_timer_END       (1)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_spi_START       (2)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_spi_END         (2)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_gpio0_START     (3)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_gpio0_END       (3)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_gpio1_START     (4)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_gpio1_END       (4)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_gpio2_START     (5)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_gpio2_END       (5)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_gpio3_START     (6)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_gpio3_END       (6)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_i2c0_START      (7)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_i2c0_END        (7)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_i2c1_START      (8)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_i2c1_END        (8)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_i2c2_START      (9)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_i2c2_END        (9)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_uart3_START     (10)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_uart3_END       (10)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_blpwm_START     (11)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_blpwm_END       (11)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_uart7_START     (12)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_uart7_END       (12)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_dma_START       (13)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_dma_END         (13)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_rtc_START       (14)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_rtc_END         (14)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_i2c6_START      (15)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_i2c6_END        (15)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_uart8_START     (16)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_uart8_END       (16)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_spi2_START      (17)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_spi2_END        (17)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_tcm_START       (18)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_tcm_END         (18)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_MEM_CTRL_PGT_UNION
 �ṹ˵��  : MEM_CTRL_PGT �Ĵ����ṹ���塣��ַƫ����:0x050����ֵ:0x00000000�����:32
 �Ĵ���˵��: mem���Ŀ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mem_ctrl_bank0     : 3;  /* bit[0-2]  : bank0 mem���Ŀ���
                                                              [2]:SD
                                                              [1]:DSLP
                                                              [0]:SLP */
        unsigned int  reserved_0         : 1;  /* bit[3]    : reserved */
        unsigned int  mem_ctrl_bank1     : 3;  /* bit[4-6]  : bank1 mem���Ŀ���
                                                              [2]:SD
                                                              [1]:DSLP
                                                              [0]:SLP */
        unsigned int  reserved_1         : 1;  /* bit[7]    : reserved */
        unsigned int  mem_ctrl_bank2     : 3;  /* bit[8-10] : bank2 mem���Ŀ���
                                                              [2]:SD
                                                              [1]:DSLP
                                                              [0]:SLP */
        unsigned int  reserved_2         : 1;  /* bit[11]   : reserved */
        unsigned int  mem_ctrl_bank3     : 3;  /* bit[12-14]: bank3 mem���Ŀ���
                                                              [2]:SD
                                                              [1]:DSLP
                                                              [0]:SLP */
        unsigned int  reserved_3         : 1;  /* bit[15]   : reserved */
        unsigned int  mem_ctrl_bank4     : 3;  /* bit[16-18]: bank4 mem���Ŀ���
                                                              [2]:SD
                                                              [1]:DSLP
                                                              [0]:SLP */
        unsigned int  reserved_4         : 1;  /* bit[19]   : reserved */
        unsigned int  mem_ctrl_icache    : 3;  /* bit[20-22]: icache mem���Ŀ���
                                                              [2]:SD
                                                              [1]:DSLP
                                                              [0]:SLP */
        unsigned int  reserved_5         : 1;  /* bit[23]   : reserved */
        unsigned int  mem_ctrl_dcache    : 3;  /* bit[24-26]: dcache mem���Ŀ���
                                                              [2]:SD
                                                              [1]:DSLP
                                                              [0]:SLP */
        unsigned int  reserved_6         : 1;  /* bit[27]   : reserved */
        unsigned int  mem_ctrl_map_table : 3;  /* bit[28-30]: map_table mem���Ŀ���
                                                              [2]:SD
                                                              [1]:DSLP
                                                              [0]:SLP */
        unsigned int  reserved_7         : 1;  /* bit[31]   : reserved */
    } reg;
} SOC_IOMCU_MEM_CTRL_PGT_UNION;
#endif
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_bank0_START      (0)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_bank0_END        (2)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_bank1_START      (4)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_bank1_END        (6)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_bank2_START      (8)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_bank2_END        (10)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_bank3_START      (12)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_bank3_END        (14)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_bank4_START      (16)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_bank4_END        (18)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_icache_START     (20)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_icache_END       (22)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_dcache_START     (24)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_dcache_END       (26)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_map_table_START  (28)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_map_table_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_MEM_CTRL_UNION
 �ṹ˵��  : MEM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x054����ֵ:0x00003554�����:32
 �Ĵ���˵��: mem�������ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tcm_wtsel   : 2;  /* bit[0-1]  : TCM memoryд�������� */
        unsigned int  tcm_rtsel   : 2;  /* bit[2-3]  : TCM memory���������� */
        unsigned int  cache_wtsel : 2;  /* bit[4-5]  : Cache memoryд�������� */
        unsigned int  cache_rtsel : 2;  /* bit[6-7]  : Cache memory���������� */
        unsigned int  tp_rct      : 2;  /* bit[8-9]  : Two Port memory�������� */
        unsigned int  tp_wct      : 2;  /* bit[10-11]: Two Port memory�������� */
        unsigned int  tp_kp       : 3;  /* bit[12-14]: Two Port memory�������� */
        unsigned int  reserved    : 17; /* bit[15-31]: Memory�������� */
    } reg;
} SOC_IOMCU_MEM_CTRL_UNION;
#endif
#define SOC_IOMCU_MEM_CTRL_tcm_wtsel_START    (0)
#define SOC_IOMCU_MEM_CTRL_tcm_wtsel_END      (1)
#define SOC_IOMCU_MEM_CTRL_tcm_rtsel_START    (2)
#define SOC_IOMCU_MEM_CTRL_tcm_rtsel_END      (3)
#define SOC_IOMCU_MEM_CTRL_cache_wtsel_START  (4)
#define SOC_IOMCU_MEM_CTRL_cache_wtsel_END    (5)
#define SOC_IOMCU_MEM_CTRL_cache_rtsel_START  (6)
#define SOC_IOMCU_MEM_CTRL_cache_rtsel_END    (7)
#define SOC_IOMCU_MEM_CTRL_tp_rct_START       (8)
#define SOC_IOMCU_MEM_CTRL_tp_rct_END         (9)
#define SOC_IOMCU_MEM_CTRL_tp_wct_START       (10)
#define SOC_IOMCU_MEM_CTRL_tp_wct_END         (11)
#define SOC_IOMCU_MEM_CTRL_tp_kp_START        (12)
#define SOC_IOMCU_MEM_CTRL_tp_kp_END          (14)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_SYS_STAT_UNION
 �ṹ˵��  : SYS_STAT �Ĵ����ṹ���塣��ַƫ����:0x058����ֵ:0x00000002�����:32
 �Ĵ���˵��: IOMCU״̬��ѯ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sys_stat   : 4;  /* bit[0-3] : ����ָʾϵͳ״̬ */
        unsigned int  xtal_ready : 2;  /* bit[4-5] : ���ڷֱ�ָʾ��������״̬�Ƿ��Ѿ��ȶ� */
        unsigned int  reserved   : 26; /* bit[6-31]: reserved */
    } reg;
} SOC_IOMCU_SYS_STAT_UNION;
#endif
#define SOC_IOMCU_SYS_STAT_sys_stat_START    (0)
#define SOC_IOMCU_SYS_STAT_sys_stat_END      (3)
#define SOC_IOMCU_SYS_STAT_xtal_ready_START  (4)
#define SOC_IOMCU_SYS_STAT_xtal_ready_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_SYS_CONFIG_UNION
 �ṹ˵��  : SYS_CONFIG �Ĵ����ṹ���塣��ַƫ����:0x05C����ֵ:0x00000000�����:32
 �Ĵ���˵��: IOMCU���ÿ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sleep_mode : 1;  /* bit[0]   : IOMCU��ϵͳ����Sleepģʽ�½������á�
                                                     1'b1:�ر�TCXO
                                                     1'b0:���ر�TCXO */
        unsigned int  ppll0_en   : 1;  /* bit[1]   : ����PPLL0��ʹ���ź� */
        unsigned int  fll_en     : 1;  /* bit[2]   : ����FLL��ʹ���ź� */
        unsigned int  reserved   : 29; /* bit[3-31]: reserved */
    } reg;
} SOC_IOMCU_SYS_CONFIG_UNION;
#endif
#define SOC_IOMCU_SYS_CONFIG_sleep_mode_START  (0)
#define SOC_IOMCU_SYS_CONFIG_sleep_mode_END    (0)
#define SOC_IOMCU_SYS_CONFIG_ppll0_en_START    (1)
#define SOC_IOMCU_SYS_CONFIG_ppll0_en_END      (1)
#define SOC_IOMCU_SYS_CONFIG_fll_en_START      (2)
#define SOC_IOMCU_SYS_CONFIG_fll_en_END        (2)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_WAKEUP_EN_UNION
 �ṹ˵��  : WAKEUP_EN �Ĵ����ṹ���塣��ַƫ����:0x060����ֵ:0x00000000�����:32
 �Ĵ���˵��: IOMCU��ϵͳ�����жϼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wakeup_en   : 1;  /* bit[0]   : IOMCU��ϵͳ�����ж�ʹ�� */
        unsigned int  soft_int_en : 1;  /* bit[1]   : TCXO��ϻ����ж�������ж�ʹ�� */
        unsigned int  reserved    : 30; /* bit[2-31]: Reserved */
    } reg;
} SOC_IOMCU_WAKEUP_EN_UNION;
#endif
#define SOC_IOMCU_WAKEUP_EN_wakeup_en_START    (0)
#define SOC_IOMCU_WAKEUP_EN_wakeup_en_END      (0)
#define SOC_IOMCU_WAKEUP_EN_soft_int_en_START  (1)
#define SOC_IOMCU_WAKEUP_EN_soft_int_en_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_WAKEUP_CLR_UNION
 �ṹ˵��  : WAKEUP_CLR �Ĵ����ṹ���塣��ַƫ����:0x064����ֵ:0x00000000�����:32
 �Ĵ���˵��: IOMCU��ϵͳ�����ж�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wakeup_clr   : 1;  /* bit[0]   : IOMCU��ϵͳ�����ж���� */
        unsigned int  soft_int_clr : 1;  /* bit[1]   : TCXO��ϻ����ж�������ж���� */
        unsigned int  reserved     : 30; /* bit[2-31]: reserved */
    } reg;
} SOC_IOMCU_WAKEUP_CLR_UNION;
#endif
#define SOC_IOMCU_WAKEUP_CLR_wakeup_clr_START    (0)
#define SOC_IOMCU_WAKEUP_CLR_wakeup_clr_END      (0)
#define SOC_IOMCU_WAKEUP_CLR_soft_int_clr_START  (1)
#define SOC_IOMCU_WAKEUP_CLR_soft_int_clr_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_WAKEUP_STAT_UNION
 �ṹ˵��  : WAKEUP_STAT �Ĵ����ṹ���塣��ַƫ����:0x068����ֵ:0x00000000�����:32
 �Ĵ���˵��: IOMCU��ϵͳ�����ж�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wakeup_stat   : 1;  /* bit[0]   : IOMCU��ϵͳ�����ж�״̬ */
        unsigned int  soft_int_stat : 1;  /* bit[1]   : TCXO��ϻ����ж�������ж�״̬ */
        unsigned int  reserved      : 30; /* bit[2-31]: reserved */
    } reg;
} SOC_IOMCU_WAKEUP_STAT_UNION;
#endif
#define SOC_IOMCU_WAKEUP_STAT_wakeup_stat_START    (0)
#define SOC_IOMCU_WAKEUP_STAT_wakeup_stat_END      (0)
#define SOC_IOMCU_WAKEUP_STAT_soft_int_stat_START  (1)
#define SOC_IOMCU_WAKEUP_STAT_soft_int_stat_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_COMB_INT_RAW_UNION
 �ṹ˵��  : COMB_INT_RAW �Ĵ����ṹ���塣��ַƫ����:0x070����ֵ:0x00000000�����:32
 �Ĵ���˵��: IOMCU�����ԭʼ����ж�״̬
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gpio0_int_raw      : 1;  /* bit[0]    : ����ж��е�GPIO0��ԭʼ�ж�״̬ */
        unsigned int  gpio1_int_raw      : 1;  /* bit[1]    : ����ж��е�GPIO1��ԭʼ�ж�״̬ */
        unsigned int  gpio2_int_raw      : 1;  /* bit[2]    : ����ж��е�GPIO2��ԭʼ�ж�״̬ */
        unsigned int  gpio3_int_raw      : 1;  /* bit[3]    : ����ж��е�GPIO3��ԭʼ�ж�״̬ */
        unsigned int  timer1_int_raw     : 1;  /* bit[4]    : ����ж��е�timer��ԭʼ�ж�״̬ */
        unsigned int  timer2_int_raw     : 1;  /* bit[5]    : ����ж��е�timer��ԭʼ�ж�״̬ */
        unsigned int  soft_int_raw       : 1;  /* bit[6]    : ����ж��е�����жϵ�ԭʼ�ж�״̬ */
        unsigned int  dss_rise_int_raw   : 1;  /* bit[7]    : DSS�жϵ�������ԭʼ�ж�״̬ */
        unsigned int  dss_down_int_raw   : 1;  /* bit[8]    : DSS�жϵ��½���ԭʼ�ж�״̬ */
        unsigned int  sys_wakeup_int_raw : 1;  /* bit[9]    : �ⲿϵͳ������״̬���뵽Sleep״̬���ж�״̬ */
        unsigned int  reserved           : 22; /* bit[10-31]: reserved */
    } reg;
} SOC_IOMCU_COMB_INT_RAW_UNION;
#endif
#define SOC_IOMCU_COMB_INT_RAW_gpio0_int_raw_START       (0)
#define SOC_IOMCU_COMB_INT_RAW_gpio0_int_raw_END         (0)
#define SOC_IOMCU_COMB_INT_RAW_gpio1_int_raw_START       (1)
#define SOC_IOMCU_COMB_INT_RAW_gpio1_int_raw_END         (1)
#define SOC_IOMCU_COMB_INT_RAW_gpio2_int_raw_START       (2)
#define SOC_IOMCU_COMB_INT_RAW_gpio2_int_raw_END         (2)
#define SOC_IOMCU_COMB_INT_RAW_gpio3_int_raw_START       (3)
#define SOC_IOMCU_COMB_INT_RAW_gpio3_int_raw_END         (3)
#define SOC_IOMCU_COMB_INT_RAW_timer1_int_raw_START      (4)
#define SOC_IOMCU_COMB_INT_RAW_timer1_int_raw_END        (4)
#define SOC_IOMCU_COMB_INT_RAW_timer2_int_raw_START      (5)
#define SOC_IOMCU_COMB_INT_RAW_timer2_int_raw_END        (5)
#define SOC_IOMCU_COMB_INT_RAW_soft_int_raw_START        (6)
#define SOC_IOMCU_COMB_INT_RAW_soft_int_raw_END          (6)
#define SOC_IOMCU_COMB_INT_RAW_dss_rise_int_raw_START    (7)
#define SOC_IOMCU_COMB_INT_RAW_dss_rise_int_raw_END      (7)
#define SOC_IOMCU_COMB_INT_RAW_dss_down_int_raw_START    (8)
#define SOC_IOMCU_COMB_INT_RAW_dss_down_int_raw_END      (8)
#define SOC_IOMCU_COMB_INT_RAW_sys_wakeup_int_raw_START  (9)
#define SOC_IOMCU_COMB_INT_RAW_sys_wakeup_int_raw_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_COMB_INT_MSK_UNION
 �ṹ˵��  : COMB_INT_MSK �Ĵ����ṹ���塣��ַƫ����:0x074����ֵ:0x00000000�����:32
 �Ĵ���˵��: IOMCU���������ж�״̬
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gpio0_int_msk      : 1;  /* bit[0]    : ����ж��е�GPIO0���ж����� */
        unsigned int  gpio1_int_msk      : 1;  /* bit[1]    : ����ж��е�GPIO1���ж����� */
        unsigned int  gpio2_int_msk      : 1;  /* bit[2]    : ����ж��е�GPIO2���ж����� */
        unsigned int  gpio3_int_msk      : 1;  /* bit[3]    : ����ж��е�GPIO3���ж����� */
        unsigned int  timer1_int_msk     : 1;  /* bit[4]    : ����ж��е�timer���ж����� */
        unsigned int  timer2_int_msk     : 1;  /* bit[5]    : ����ж��е�timer���ж����� */
        unsigned int  soft_int_msk       : 1;  /* bit[6]    : ����ж��е�����жϵ�ԭʼ�ж����� */
        unsigned int  dss_rise_int_msk   : 1;  /* bit[7]    : DSS�жϵ�������ԭʼ�ж����� */
        unsigned int  dss_down_int_msk   : 1;  /* bit[8]    : DSS�жϵ��½���ԭʼ�ж����� */
        unsigned int  dss_rise_int_clr   : 1;  /* bit[9]    : DSS�жϵ�������ԭʼ�ж���� */
        unsigned int  dss_down_int_clr   : 1;  /* bit[10]   : DSS�жϵ��½���ԭʼ�ж���� */
        unsigned int  sys_wakeup_int_msk : 1;  /* bit[11]   : �ⲿϵͳ������״̬���뵽Sleep״̬���ж����� */
        unsigned int  sys_wakeup_int_clr : 1;  /* bit[12]   : �ⲿϵͳ������״̬���뵽Sleep״̬���ж���� */
        unsigned int  reserved           : 19; /* bit[13-31]: reserved */
    } reg;
} SOC_IOMCU_COMB_INT_MSK_UNION;
#endif
#define SOC_IOMCU_COMB_INT_MSK_gpio0_int_msk_START       (0)
#define SOC_IOMCU_COMB_INT_MSK_gpio0_int_msk_END         (0)
#define SOC_IOMCU_COMB_INT_MSK_gpio1_int_msk_START       (1)
#define SOC_IOMCU_COMB_INT_MSK_gpio1_int_msk_END         (1)
#define SOC_IOMCU_COMB_INT_MSK_gpio2_int_msk_START       (2)
#define SOC_IOMCU_COMB_INT_MSK_gpio2_int_msk_END         (2)
#define SOC_IOMCU_COMB_INT_MSK_gpio3_int_msk_START       (3)
#define SOC_IOMCU_COMB_INT_MSK_gpio3_int_msk_END         (3)
#define SOC_IOMCU_COMB_INT_MSK_timer1_int_msk_START      (4)
#define SOC_IOMCU_COMB_INT_MSK_timer1_int_msk_END        (4)
#define SOC_IOMCU_COMB_INT_MSK_timer2_int_msk_START      (5)
#define SOC_IOMCU_COMB_INT_MSK_timer2_int_msk_END        (5)
#define SOC_IOMCU_COMB_INT_MSK_soft_int_msk_START        (6)
#define SOC_IOMCU_COMB_INT_MSK_soft_int_msk_END          (6)
#define SOC_IOMCU_COMB_INT_MSK_dss_rise_int_msk_START    (7)
#define SOC_IOMCU_COMB_INT_MSK_dss_rise_int_msk_END      (7)
#define SOC_IOMCU_COMB_INT_MSK_dss_down_int_msk_START    (8)
#define SOC_IOMCU_COMB_INT_MSK_dss_down_int_msk_END      (8)
#define SOC_IOMCU_COMB_INT_MSK_dss_rise_int_clr_START    (9)
#define SOC_IOMCU_COMB_INT_MSK_dss_rise_int_clr_END      (9)
#define SOC_IOMCU_COMB_INT_MSK_dss_down_int_clr_START    (10)
#define SOC_IOMCU_COMB_INT_MSK_dss_down_int_clr_END      (10)
#define SOC_IOMCU_COMB_INT_MSK_sys_wakeup_int_msk_START  (11)
#define SOC_IOMCU_COMB_INT_MSK_sys_wakeup_int_msk_END    (11)
#define SOC_IOMCU_COMB_INT_MSK_sys_wakeup_int_clr_START  (12)
#define SOC_IOMCU_COMB_INT_MSK_sys_wakeup_int_clr_END    (12)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_COMB_INT_STAT_UNION
 �ṹ˵��  : COMB_INT_STAT �Ĵ����ṹ���塣��ַƫ����:0x078����ֵ:0x00000000�����:32
 �Ĵ���˵��: IOMCU��������κ�����ж�״̬
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gpio0_int_mskd      : 1;  /* bit[0]    : ����ж��е�GPIO0�����κ��ж�״̬ */
        unsigned int  gpio1_int_mskd      : 1;  /* bit[1]    : ����ж��е�GPIO1�����κ��ж�״̬ */
        unsigned int  gpio2_int_mskd      : 1;  /* bit[2]    : ����ж��е�GPIO2�����κ��ж�״̬ */
        unsigned int  gpio3_int_mskd      : 1;  /* bit[3]    : ����ж��е�GPIO3�����κ��ж�״̬ */
        unsigned int  timer1_int_mskd     : 1;  /* bit[4]    : ����ж��е�timer�����κ��ж�״̬ */
        unsigned int  timer2_int_mskd     : 1;  /* bit[5]    : ����ж��е�timer�����κ��ж�״̬ */
        unsigned int  soft_int_mskd       : 1;  /* bit[6]    : ����ж��е�����жϵ����κ��ж�״̬ */
        unsigned int  dss_rise_int_mskd   : 1;  /* bit[7]    : DSS�жϵ�������ԭʼ�ж����κ���ж�״̬ */
        unsigned int  dss_down_int_mskd   : 1;  /* bit[8]    : DSS�жϵ��½���ԭʼ�ж����κ���ж�״̬ */
        unsigned int  sys_wakeup_int_mskd : 1;  /* bit[9]    : �ⲿϵͳ�ӵ�����״̬����Sleep���κ���ж�״̬ */
        unsigned int  reserved            : 22; /* bit[10-31]: reserved */
    } reg;
} SOC_IOMCU_COMB_INT_STAT_UNION;
#endif
#define SOC_IOMCU_COMB_INT_STAT_gpio0_int_mskd_START       (0)
#define SOC_IOMCU_COMB_INT_STAT_gpio0_int_mskd_END         (0)
#define SOC_IOMCU_COMB_INT_STAT_gpio1_int_mskd_START       (1)
#define SOC_IOMCU_COMB_INT_STAT_gpio1_int_mskd_END         (1)
#define SOC_IOMCU_COMB_INT_STAT_gpio2_int_mskd_START       (2)
#define SOC_IOMCU_COMB_INT_STAT_gpio2_int_mskd_END         (2)
#define SOC_IOMCU_COMB_INT_STAT_gpio3_int_mskd_START       (3)
#define SOC_IOMCU_COMB_INT_STAT_gpio3_int_mskd_END         (3)
#define SOC_IOMCU_COMB_INT_STAT_timer1_int_mskd_START      (4)
#define SOC_IOMCU_COMB_INT_STAT_timer1_int_mskd_END        (4)
#define SOC_IOMCU_COMB_INT_STAT_timer2_int_mskd_START      (5)
#define SOC_IOMCU_COMB_INT_STAT_timer2_int_mskd_END        (5)
#define SOC_IOMCU_COMB_INT_STAT_soft_int_mskd_START        (6)
#define SOC_IOMCU_COMB_INT_STAT_soft_int_mskd_END          (6)
#define SOC_IOMCU_COMB_INT_STAT_dss_rise_int_mskd_START    (7)
#define SOC_IOMCU_COMB_INT_STAT_dss_rise_int_mskd_END      (7)
#define SOC_IOMCU_COMB_INT_STAT_dss_down_int_mskd_START    (8)
#define SOC_IOMCU_COMB_INT_STAT_dss_down_int_mskd_END      (8)
#define SOC_IOMCU_COMB_INT_STAT_sys_wakeup_int_mskd_START  (9)
#define SOC_IOMCU_COMB_INT_STAT_sys_wakeup_int_mskd_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_BUS_AUTO_FREQ_UNION
 �ṹ˵��  : BUS_AUTO_FREQ �Ĵ����ṹ���塣��ַƫ����:0x080����ֵ:0x08000003�����:32
 �Ĵ���˵��: IOMCU�����Զ���Ƶ/��ʱ�ӼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  auto_m7_freq_bypass  : 1;  /* bit[0]    : M7�ж��Զ���Ƶ�����Ƿ�bypass
                                                                0����bypass����Ƶ
                                                                1��bypass������Ƶ */
        unsigned int  auto_cpu_freq_bypass : 1;  /* bit[1]    : �ⲿCPU�ж��Զ���Ƶ�����Ƿ�bypass
                                                                0����bypass����Ƶ
                                                                1��bypass������Ƶ */
        unsigned int  reserved_0           : 2;  /* bit[2-3]  : reserved */
        unsigned int  auto_num_in          : 10; /* bit[4-13] : �����Զ���Ƶʱ����Ҫ����idle״̬�������� */
        unsigned int  reserved_1           : 2;  /* bit[14-15]: reserved */
        unsigned int  auto_num_out         : 10; /* bit[16-25]: �˳��Զ���Ƶʱ����Ҫ���ַ�idle״̬�������� */
        unsigned int  reserved_2           : 1;  /* bit[26]   : reserved */
        unsigned int  noc_clkgate_bypass   : 1;  /* bit[27]   : �Ƿ��NOC����ʱ�ӹرյ�Bypass��Ĭ��Ϊ1��������Bypass,���Զ���NOCʱ�ӡ� */
        unsigned int  reserved_3           : 4;  /* bit[28-31]: reserved */
    } reg;
} SOC_IOMCU_BUS_AUTO_FREQ_UNION;
#endif
#define SOC_IOMCU_BUS_AUTO_FREQ_auto_m7_freq_bypass_START   (0)
#define SOC_IOMCU_BUS_AUTO_FREQ_auto_m7_freq_bypass_END     (0)
#define SOC_IOMCU_BUS_AUTO_FREQ_auto_cpu_freq_bypass_START  (1)
#define SOC_IOMCU_BUS_AUTO_FREQ_auto_cpu_freq_bypass_END    (1)
#define SOC_IOMCU_BUS_AUTO_FREQ_auto_num_in_START           (4)
#define SOC_IOMCU_BUS_AUTO_FREQ_auto_num_in_END             (13)
#define SOC_IOMCU_BUS_AUTO_FREQ_auto_num_out_START          (16)
#define SOC_IOMCU_BUS_AUTO_FREQ_auto_num_out_END            (25)
#define SOC_IOMCU_BUS_AUTO_FREQ_noc_clkgate_bypass_START    (27)
#define SOC_IOMCU_BUS_AUTO_FREQ_noc_clkgate_bypass_END      (27)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_MISC_CTRL_UNION
 �ṹ˵��  : MISC_CTRL �Ĵ����ṹ���塣��ַƫ����:0x084����ֵ:0x00003780�����:32
 �Ĵ���˵��: MISC�߼�����Ŀ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  spi_cs        : 4;  /* bit[0-3]  : �ĸ�SPI��ѡ��Ĵ�������Ӧ��ÿһbit��ѡһ���Ĵ����� */
        unsigned int  clk_tp_ctrl   : 1;  /* bit[4]    : ʱ��TP�źŵĿ���bit��
                                                         0��������TP�۲⡣
                                                         1������TP�۲⡣ */
        unsigned int  dmac_ckgt_dis : 1;  /* bit[5]    : dmac��Ӳ���ſ�ʹ��λ������Ϊ1����ʾȥʹ�ܣ�0��ʾʹ���Զ��ſع��ܣ�Ĭ��ֵΪ0 */
        unsigned int  cfg_itcm_size : 4;  /* bit[6-9]  : ITCM SIZE����
                                                         0KB noTCM 4'b0000
                                                         4KB 4'b0011
                                                         8KB 4'b0100
                                                         16KB 4'b0101
                                                         32KB 4'b0110
                                                         64KB 4'b0111
                                                         128KB 4'b1000
                                                         256KB 4'b1001
                                                         512KB 4'b1010
                                                         1MB 4'b1011
                                                         2MB 4'b1100
                                                         4MB 4'b1101
                                                         8MB 4'b1110
                                                         16MB 4'b1111  */
        unsigned int  cfg_dtcm_size : 4;  /* bit[10-13]: DCTCM SIZE����
                                                         0KB noTCM 4'b0000
                                                         4KB 4'b0011
                                                         8KB 4'b0100
                                                         16KB 4'b0101
                                                         32KB 4'b0110
                                                         64KB 4'b0111
                                                         128KB 4'b1000
                                                         256KB 4'b1001
                                                         512KB 4'b1010
                                                         1MB 4'b1011
                                                         2MB 4'b1100
                                                         4MB 4'b1101
                                                         8MB 4'b1110
                                                         16MB 4'b1111  */
        unsigned int  reserved      : 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_IOMCU_MISC_CTRL_UNION;
#endif
#define SOC_IOMCU_MISC_CTRL_spi_cs_START         (0)
#define SOC_IOMCU_MISC_CTRL_spi_cs_END           (3)
#define SOC_IOMCU_MISC_CTRL_clk_tp_ctrl_START    (4)
#define SOC_IOMCU_MISC_CTRL_clk_tp_ctrl_END      (4)
#define SOC_IOMCU_MISC_CTRL_dmac_ckgt_dis_START  (5)
#define SOC_IOMCU_MISC_CTRL_dmac_ckgt_dis_END    (5)
#define SOC_IOMCU_MISC_CTRL_cfg_itcm_size_START  (6)
#define SOC_IOMCU_MISC_CTRL_cfg_itcm_size_END    (9)
#define SOC_IOMCU_MISC_CTRL_cfg_dtcm_size_START  (10)
#define SOC_IOMCU_MISC_CTRL_cfg_dtcm_size_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_NOC_CTRL_UNION
 �ṹ˵��  : NOC_CTRL �Ĵ����ṹ���塣��ַƫ����:0x088����ֵ:0x00000000�����:32
 �Ĵ���˵��: NOC ����źŵĿ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  noc_iomcu_dma_mst_awqos   : 2;  /* bit[0-1]  : NOC DMA AWͨ��QOS */
        unsigned int  noc_iomcu_dma_mst_arqos   : 2;  /* bit[2-3]  : NOC DMA ARͨ��QOS */
        unsigned int  noc_iomcu_axi_mst_awqos   : 2;  /* bit[4-5]  : NOC AXI AWͨ��QOS */
        unsigned int  noc_iomcu_axi_mst_arqos   : 2;  /* bit[6-7]  : NOC AXI ARͨ��QOS */
        unsigned int  noc_iomcu_ahb_mst_requser : 2;  /* bit[8-9]  : NOC AHBͨ��QOS */
        unsigned int  noc_ahb_mst_mid           : 5;  /* bit[10-14]: NOC AHB Masterͨ��Mid */
        unsigned int  reserved                  : 17; /* bit[15-31]:  */
    } reg;
} SOC_IOMCU_NOC_CTRL_UNION;
#endif
#define SOC_IOMCU_NOC_CTRL_noc_iomcu_dma_mst_awqos_START    (0)
#define SOC_IOMCU_NOC_CTRL_noc_iomcu_dma_mst_awqos_END      (1)
#define SOC_IOMCU_NOC_CTRL_noc_iomcu_dma_mst_arqos_START    (2)
#define SOC_IOMCU_NOC_CTRL_noc_iomcu_dma_mst_arqos_END      (3)
#define SOC_IOMCU_NOC_CTRL_noc_iomcu_axi_mst_awqos_START    (4)
#define SOC_IOMCU_NOC_CTRL_noc_iomcu_axi_mst_awqos_END      (5)
#define SOC_IOMCU_NOC_CTRL_noc_iomcu_axi_mst_arqos_START    (6)
#define SOC_IOMCU_NOC_CTRL_noc_iomcu_axi_mst_arqos_END      (7)
#define SOC_IOMCU_NOC_CTRL_noc_iomcu_ahb_mst_requser_START  (8)
#define SOC_IOMCU_NOC_CTRL_noc_iomcu_ahb_mst_requser_END    (9)
#define SOC_IOMCU_NOC_CTRL_noc_ahb_mst_mid_START            (10)
#define SOC_IOMCU_NOC_CTRL_noc_ahb_mst_mid_END              (14)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_M7_CFG2_UNION
 �ṹ˵��  : M7_CFG2 �Ĵ����ṹ���塣��ַƫ����:0x08C����ֵ:0x00000000�����:32
 �Ĵ���˵��: IOMCU M7���üĴ���2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomcu_reserved : 32; /* bit[0-31]: Ԥ�� */
    } reg;
} SOC_IOMCU_M7_CFG2_UNION;
#endif
#define SOC_IOMCU_M7_CFG2_iomcu_reserved_START  (0)
#define SOC_IOMCU_M7_CFG2_iomcu_reserved_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_CLKEN1_UNION
 �ṹ˵��  : CLKEN1 �Ĵ����ṹ���塣��ַƫ����:0x090����ֵ:0x0000000F�����:32
 �Ĵ���˵��: IOMCU����ʱ��ʹ�ܼĴ���1���Ա���д1��ʹ��IOMCU_CLKSTAT0��Ӧ��ʱ�ӣ�д0��Ӱ��ʱ��ʹ�ܵ�״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomcu_clken1_0peri0 : 1;  /* bit[0]   : 0peri0 */
        unsigned int  iomcu_clken1_1peri1 : 1;  /* bit[1]   : 1peri1 */
        unsigned int  iomcu_clken1_2peri2 : 1;  /* bit[2]   : 2peri2 */
        unsigned int  iomcu_clken1_3peri3 : 1;  /* bit[3]   : 3peri3 */
        unsigned int  reserved            : 28; /* bit[4-31]: reserved */
    } reg;
} SOC_IOMCU_CLKEN1_UNION;
#endif
#define SOC_IOMCU_CLKEN1_iomcu_clken1_0peri0_START  (0)
#define SOC_IOMCU_CLKEN1_iomcu_clken1_0peri0_END    (0)
#define SOC_IOMCU_CLKEN1_iomcu_clken1_1peri1_START  (1)
#define SOC_IOMCU_CLKEN1_iomcu_clken1_1peri1_END    (1)
#define SOC_IOMCU_CLKEN1_iomcu_clken1_2peri2_START  (2)
#define SOC_IOMCU_CLKEN1_iomcu_clken1_2peri2_END    (2)
#define SOC_IOMCU_CLKEN1_iomcu_clken1_3peri3_START  (3)
#define SOC_IOMCU_CLKEN1_iomcu_clken1_3peri3_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_CLKDIS1_UNION
 �ṹ˵��  : CLKDIS1 �Ĵ����ṹ���塣��ַƫ����:0x094����ֵ:0x00000000�����:32
 �Ĵ���˵��: IOMCU����ʱ��ʹ�ܼĴ���1���Ա���д1��ʹ��IOMCU_CLKSTAT0��Ӧ��ʱ�ӣ�д0��Ӱ��ʱ��ʹ�ܵ�״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomcu_clkdis1_0peri0 : 1;  /* bit[0]   : dis1_0peri0 */
        unsigned int  iomcu_clkdis1_1peri1 : 1;  /* bit[1]   : dis1_1peri1 */
        unsigned int  iomcu_clkdis1_2peri2 : 1;  /* bit[2]   : dis1_2peri2 */
        unsigned int  iomcu_clkdis1_3peri3 : 1;  /* bit[3]   : dis1_3peri3 */
        unsigned int  reserved             : 28; /* bit[4-31]: reserved */
    } reg;
} SOC_IOMCU_CLKDIS1_UNION;
#endif
#define SOC_IOMCU_CLKDIS1_iomcu_clkdis1_0peri0_START  (0)
#define SOC_IOMCU_CLKDIS1_iomcu_clkdis1_0peri0_END    (0)
#define SOC_IOMCU_CLKDIS1_iomcu_clkdis1_1peri1_START  (1)
#define SOC_IOMCU_CLKDIS1_iomcu_clkdis1_1peri1_END    (1)
#define SOC_IOMCU_CLKDIS1_iomcu_clkdis1_2peri2_START  (2)
#define SOC_IOMCU_CLKDIS1_iomcu_clkdis1_2peri2_END    (2)
#define SOC_IOMCU_CLKDIS1_iomcu_clkdis1_3peri3_START  (3)
#define SOC_IOMCU_CLKDIS1_iomcu_clkdis1_3peri3_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_CLKSTAT1_UNION
 �ṹ˵��  : CLKSTAT1 �Ĵ����ṹ���塣��ַƫ����:0x098����ֵ:0x0000000F�����:32
 �Ĵ���˵��: IOMCU����ʱ��״̬�Ĵ���1����IOMCU_CLKEN0��IOMCU_CLKDIS0���ý���״̬�޸ġ�
            ����ʱ�ӿ����ź��辭����CRG�н���ͬ��������ˣ�����ļĴ���ֵ���ӳ���Ӧʱ����ļ������ں��������Ӧʱ��״̬��
            ÿ��Bit���壺
            0��ʱ�ӹرգ�
            1��ʱ�Ӵ򿪡�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomcu_clkstat1_0peri0 : 1;  /* bit[0]   : stat1_0peri0 */
        unsigned int  iomcu_clkstat1_1peri1 : 1;  /* bit[1]   : stat1_1peri1 */
        unsigned int  iomcu_clkstat1_2peri2 : 1;  /* bit[2]   : stat1_2peri2 */
        unsigned int  iomcu_clkstat1_3peri3 : 1;  /* bit[3]   : stat1_3peri3 */
        unsigned int  reserved              : 28; /* bit[4-31]: reserved */
    } reg;
} SOC_IOMCU_CLKSTAT1_UNION;
#endif
#define SOC_IOMCU_CLKSTAT1_iomcu_clkstat1_0peri0_START  (0)
#define SOC_IOMCU_CLKSTAT1_iomcu_clkstat1_0peri0_END    (0)
#define SOC_IOMCU_CLKSTAT1_iomcu_clkstat1_1peri1_START  (1)
#define SOC_IOMCU_CLKSTAT1_iomcu_clkstat1_1peri1_END    (1)
#define SOC_IOMCU_CLKSTAT1_iomcu_clkstat1_2peri2_START  (2)
#define SOC_IOMCU_CLKSTAT1_iomcu_clkstat1_2peri2_END    (2)
#define SOC_IOMCU_CLKSTAT1_iomcu_clkstat1_3peri3_START  (3)
#define SOC_IOMCU_CLKSTAT1_iomcu_clkstat1_3peri3_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_SEC_TZPC_UNION
 �ṹ˵��  : SEC_TZPC �Ĵ����ṹ���塣��ַƫ����:0x0100����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ȫTZPCλ�����԰�ȫ����0��ʾ��ȫ��1��ʾ�ǰ�ȫ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomcu_AHB_tzpc   : 1;  /* bit[0]    : AHB���߰�ȫ����bit */
        unsigned int  iomcu_AXI_tzpc   : 1;  /* bit[1]    : AXI���߰�ȫ����bit */
        unsigned int  reserved_0       : 1;  /* bit[2]    : ��ȫ����bit */
        unsigned int  iomcu_i2c2_tzpc  : 1;  /* bit[3]    : I2C2��ȫ����bit */
        unsigned int  iomcu_i2c1_tzpc  : 1;  /* bit[4]    : I2C1��ȫ����bit */
        unsigned int  iomcu_spi2_tzpc  : 1;  /* bit[5]    : SPI2��ȫ����bit */
        unsigned int  iomcu_uart8_tzpc : 1;  /* bit[6]    : UART8��ȫ����bit */
        unsigned int  iomcu_i2c6_tzpc  : 1;  /* bit[7]    : i2c6��ȫ����bit */
        unsigned int  iomcu_tcm_tzpc   : 1;  /* bit[8]    : TCM��ȫ����bit��ֻ����TCM REMAP APB���֣� */
        unsigned int  iomcu_spi_tzpc   : 1;  /* bit[9]    : SPI��ȫ����bit */
        unsigned int  iomcu_i2c0_tzpc  : 1;  /* bit[10]   : I2C0��ȫ����bit */
        unsigned int  iomcu_uart3_tzpc : 1;  /* bit[11]   : UART3��ȫ����bit */
        unsigned int  iomcu_blpwm_tzpc : 1;  /* bit[12]   : BLPWM��ȫ����bit */
        unsigned int  iomcu_uart7_tzpc : 1;  /* bit[13]   : UART7��ȫ����bit */
        unsigned int  reserved_1       : 1;  /* bit[14]   : reserved */
        unsigned int  iomcu_gpio0_tzpc : 1;  /* bit[15]   : GPIO0��ȫ����bit */
        unsigned int  iomcu_gpio1_tzpc : 1;  /* bit[16]   : GPIO1��ȫ����bit */
        unsigned int  iomcu_gpio2_tzpc : 1;  /* bit[17]   : GPIO2��ȫ����bit */
        unsigned int  iomcu_gpio3_tzpc : 1;  /* bit[18]   : GPIO3��ȫ����bit */
        unsigned int  iomcu_wdg_tzpc   : 1;  /* bit[19]   : WDG��ȫ����bit */
        unsigned int  iomcu_timer_tzpc : 1;  /* bit[20]   : TIMER��ȫ����bit */
        unsigned int  iomcu_sctrl_tzpc : 1;  /* bit[21]   : IO_CONFIG��ȫ����bit */
        unsigned int  iomcu_rtc_tzpc   : 1;  /* bit[22]   : RTC��ȫ����bit */
        unsigned int  iomcu_m7_tzpc    : 1;  /* bit[23]   : IOMCU_M7_AHB_SLV��ȫ����bit */
        unsigned int  reserved_2       : 8;  /* bit[24-31]:  */
    } reg;
} SOC_IOMCU_SEC_TZPC_UNION;
#endif
#define SOC_IOMCU_SEC_TZPC_iomcu_AHB_tzpc_START    (0)
#define SOC_IOMCU_SEC_TZPC_iomcu_AHB_tzpc_END      (0)
#define SOC_IOMCU_SEC_TZPC_iomcu_AXI_tzpc_START    (1)
#define SOC_IOMCU_SEC_TZPC_iomcu_AXI_tzpc_END      (1)
#define SOC_IOMCU_SEC_TZPC_iomcu_i2c2_tzpc_START   (3)
#define SOC_IOMCU_SEC_TZPC_iomcu_i2c2_tzpc_END     (3)
#define SOC_IOMCU_SEC_TZPC_iomcu_i2c1_tzpc_START   (4)
#define SOC_IOMCU_SEC_TZPC_iomcu_i2c1_tzpc_END     (4)
#define SOC_IOMCU_SEC_TZPC_iomcu_spi2_tzpc_START   (5)
#define SOC_IOMCU_SEC_TZPC_iomcu_spi2_tzpc_END     (5)
#define SOC_IOMCU_SEC_TZPC_iomcu_uart8_tzpc_START  (6)
#define SOC_IOMCU_SEC_TZPC_iomcu_uart8_tzpc_END    (6)
#define SOC_IOMCU_SEC_TZPC_iomcu_i2c6_tzpc_START   (7)
#define SOC_IOMCU_SEC_TZPC_iomcu_i2c6_tzpc_END     (7)
#define SOC_IOMCU_SEC_TZPC_iomcu_tcm_tzpc_START    (8)
#define SOC_IOMCU_SEC_TZPC_iomcu_tcm_tzpc_END      (8)
#define SOC_IOMCU_SEC_TZPC_iomcu_spi_tzpc_START    (9)
#define SOC_IOMCU_SEC_TZPC_iomcu_spi_tzpc_END      (9)
#define SOC_IOMCU_SEC_TZPC_iomcu_i2c0_tzpc_START   (10)
#define SOC_IOMCU_SEC_TZPC_iomcu_i2c0_tzpc_END     (10)
#define SOC_IOMCU_SEC_TZPC_iomcu_uart3_tzpc_START  (11)
#define SOC_IOMCU_SEC_TZPC_iomcu_uart3_tzpc_END    (11)
#define SOC_IOMCU_SEC_TZPC_iomcu_blpwm_tzpc_START  (12)
#define SOC_IOMCU_SEC_TZPC_iomcu_blpwm_tzpc_END    (12)
#define SOC_IOMCU_SEC_TZPC_iomcu_uart7_tzpc_START  (13)
#define SOC_IOMCU_SEC_TZPC_iomcu_uart7_tzpc_END    (13)
#define SOC_IOMCU_SEC_TZPC_iomcu_gpio0_tzpc_START  (15)
#define SOC_IOMCU_SEC_TZPC_iomcu_gpio0_tzpc_END    (15)
#define SOC_IOMCU_SEC_TZPC_iomcu_gpio1_tzpc_START  (16)
#define SOC_IOMCU_SEC_TZPC_iomcu_gpio1_tzpc_END    (16)
#define SOC_IOMCU_SEC_TZPC_iomcu_gpio2_tzpc_START  (17)
#define SOC_IOMCU_SEC_TZPC_iomcu_gpio2_tzpc_END    (17)
#define SOC_IOMCU_SEC_TZPC_iomcu_gpio3_tzpc_START  (18)
#define SOC_IOMCU_SEC_TZPC_iomcu_gpio3_tzpc_END    (18)
#define SOC_IOMCU_SEC_TZPC_iomcu_wdg_tzpc_START    (19)
#define SOC_IOMCU_SEC_TZPC_iomcu_wdg_tzpc_END      (19)
#define SOC_IOMCU_SEC_TZPC_iomcu_timer_tzpc_START  (20)
#define SOC_IOMCU_SEC_TZPC_iomcu_timer_tzpc_END    (20)
#define SOC_IOMCU_SEC_TZPC_iomcu_sctrl_tzpc_START  (21)
#define SOC_IOMCU_SEC_TZPC_iomcu_sctrl_tzpc_END    (21)
#define SOC_IOMCU_SEC_TZPC_iomcu_rtc_tzpc_START    (22)
#define SOC_IOMCU_SEC_TZPC_iomcu_rtc_tzpc_END      (22)
#define SOC_IOMCU_SEC_TZPC_iomcu_m7_tzpc_START     (23)
#define SOC_IOMCU_SEC_TZPC_iomcu_m7_tzpc_END       (23)


/*****************************************************************************
 �ṹ��    : SOC_IOMCU_SEC_RES_UNION
 �ṹ˵��  : SEC_RES �Ĵ����ṹ���塣��ַƫ����:0x104����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomcu_se_reserved : 32; /* bit[0-31]: Ԥ�� */
    } reg;
} SOC_IOMCU_SEC_RES_UNION;
#endif
#define SOC_IOMCU_SEC_RES_iomcu_se_reserved_START  (0)
#define SOC_IOMCU_SEC_RES_iomcu_se_reserved_END    (31)






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

#endif /* end of soc_iomcu_interface.h */
