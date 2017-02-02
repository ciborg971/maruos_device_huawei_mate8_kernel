/***********************************************************************************************************************
˵�������ļ�������Clockģ��ʹ�ú��װ���壬ת����soc_baseaddr_interface.h��
      soc_sctrl_interface.h��soc_pmctrl_interface.h
************************************************************************************************************************/
#include "soc_baseaddr_interface.h" /* �Ĵ�����ַת�����ɵ�ͷ�ļ� */
#if defined (CHIP_BB_HI6210)
#include "soc_peri_sctrl_interface.h"
#elif defined (CHIP_BB_HI6620)
#include "soc_sctrl_interface.h"    /* ϵͳ���ƼĴ���ת�����ɵ�ͷ�ļ� */
#endif
#include "soc_ao_sctrl_interface.h" /* AOϵͳ���ƼĴ���ת�����ɵ�ͷ�ļ� */
#include "soc_pmctrl_interface.h"   /* PM���ƼĴ���ת�����ɵ�ͷ�ļ� */
#include "soc_smart_interface.h"   /* SMART STAR���ƼĴ���ת�����ɵ�ͷ�ļ� */
#include "mach/hardware.h"

#define DISABLE_REG_OFFSET 0x04
#define ENASTAT_REG_OFFSET 0x08

#define CLKDIV_SET_INVALID -1
#define CLKSEL_SET_INVALID -1

#define CALC_REG_MASK(bit_start, bit_end) \
    (((0x1 << (bit_end - bit_start + 1)) - 1) << bit_start)


#define SCTRL_OFF_BASE_ADDR  IO_ADDRESS(SOC_SC_OFF_BASE_ADDR)
#define SCTRL_ON_BASE_ADDR   IO_ADDRESS(SOC_SC_ON_BASE_ADDR)
#define PMCTRL_BASE_ADDR     IO_ADDRESS(SOC_PMCTRL_BASE_ADDR)

/* clkin_sys���������ת���� */
/* ת����ʱ��clkin_sys��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLKIN_SYS_ENABLE_REG_ADDR   NULL    /* ʹ�ܼĴ�����ַת����� */
#define CLKIN_SYS_ENABLE_BIT_OFFSET 0   /* ʱ��ʹ��λƫ�� */

/* ת����ʱ��clkin_sys��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLKIN_SYS_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLKIN_SYS_CLKSEL_MASK       0   //��ʱ��ѡ������
#define CLKIN_SYS_CLKSEL_SET_VALID  0       //��ʱ��ѡ����Ч��־λ
#define CLKIN_SYS_CLKDIV_REG_ADDR   NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLKIN_SYS_CLKDIV_MASK       0                   //ʱ�ӷ�Ƶ����
#define CLKIN_SYS_CLKDIV_SET_VALID  0       //ʱ�ӷ�Ƶ������Ч��־λ

/* clkin_sys���������ת���� */

/* clk_ref���������ת���� */
/* ת����ʱ��clk_ref��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_REF_ENABLE_REG_ADDR     NULL    /* ʹ�ܼĴ�����ַת����� */
#define CLK_REF_ENABLE_BIT_OFFSET   0  /* ʱ��ʹ��λƫ�� */

/* ת����ʱ��clk_ref��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_REF_CLKSEL_REG_ADDR    NULL                 //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_REF_CLKSEL_MASK        0   //��ʱ��ѡ������
#define CLK_REF_CLKSEL_SET_VALID   0   //��ʱ��ѡ����Ч��־λ
#define CLK_REF_CLKDIV_REG_ADDR    NULL                 //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_REF_CLKDIV_MASK        0    //ʱ�ӷ�Ƶ����
#define CLK_REF_CLKDIV_SET_VALID   0   //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_ref32k���������ת���� */
/* ת����ʱ��clk_ref32k��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_REF32K_ENABLE_REG_ADDR  NULL    /* ʹ�ܼĴ�����ַת����� */
#define CLK_REF32K_ENABLE_BIT_OFFSET    0   /* ʱ��ʹ��λƫ�� */

/* ת����ʱ��clk_ref32k��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_REF32K_CLKSEL_REG_ADDR  NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_REF32K_CLKSEL_MASK      0   //��ʱ��ѡ������
#define CLK_REF32K_CLKSEL_SET_VALID 0       //��ʱ��ѡ����Ч��־λ
#define CLK_REF32K_CLKDIV_REG_ADDR  NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_REF32K_CLKDIV_MASK      0                   //ʱ�ӷ�Ƶ����
#define CLK_REF32K_CLKDIV_SET_VALID 0       //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_ref32k���������ת���� */


/* clk_pmu32kb���������ת���� */
/* ת����ʱ��clk_ref��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_PMU32KB_ENABLE_REG_ADDR     SOC_SMART_ONOFF8_ADDR(0)    /* ʹ�ܼĴ�����ַת����� */
#define CLK_PMU32KB_ENABLE_BIT_OFFSET   SOC_SMART_ONOFF8_en_32kb_START  /* ʱ��ʹ��λƫ�� */
/* clk_pmu32kb���������ת���� */

/* clk_pmu32kc���������ת���� */
/* ת����ʱ��clk_ref��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_PMU32KC_ENABLE_REG_ADDR     SOC_SMART_ONOFF8_ADDR(0)    /* ʹ�ܼĴ�����ַת����� */
#define CLK_PMU32KC_ENABLE_BIT_OFFSET   SOC_SMART_ONOFF8_en_32kc_START  /* ʱ��ʹ��λƫ�� */
/* clk_pmu32kc���������ת���� */


/* clk_apll0���������ת���� */
/* ת����ʱ��clk_apll0��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_APLL0_ENABLE_REG_ADDR   NULL    /* ʹ�ܼĴ�����ַת����� */
#define CLK_APLL0_ENABLE_BIT_OFFSET 0   /* ʱ��ʹ��λƫ�� */

/* ת����ʱ��clk_apll0��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_APLL0_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_APLL0_CLKSEL_MASK       0   //��ʱ��ѡ������
#define CLK_APLL0_CLKSEL_SET_VALID  0       //��ʱ��ѡ����Ч��־λ
#define CLK_APLL0_CLKDIV_REG_ADDR   NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_APLL0_CLKDIV_MASK       0                   //ʱ�ӷ�Ƶ����
#define CLK_APLL0_CLKDIV_SET_VALID  0       //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_apll1���������ת���� */
/* ת����ʱ��clk_apll1��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_APLL1_ENABLE_REG_ADDR   NULL    /* ʹ�ܼĴ�����ַת����� */
#define CLK_APLL1_ENABLE_BIT_OFFSET 0   /* ʱ��ʹ��λƫ�� */

/* ת����ʱ��clk_apll1��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_APLL1_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_APLL1_CLKSEL_MASK       0   //��ʱ��ѡ������
#define CLK_APLL1_CLKSEL_SET_VALID  0       //��ʱ��ѡ����Ч��־λ
#define CLK_APLL1_CLKDIV_REG_ADDR   NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_APLL1_CLKDIV_MASK       0                   //ʱ�ӷ�Ƶ����
#define CLK_APLL1_CLKDIV_SET_VALID  0       //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_dsplpl���������ת���� */
/* ת����ʱ��clk_dsppll��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_DSPPLL_ENABLE_REG_ADDR  NULL    /* ʹ�ܼĴ�����ַת����� */
#define CLK_DSPPLL_ENABLE_BIT_OFFSET    0   /* ʱ��ʹ��λƫ�� */

/* ת����ʱ��clk_dsppll��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_DSPPLL_CLKSEL_REG_ADDR  NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_DSPPLL_CLKSEL_MASK      0   //��ʱ��ѡ������
#define CLK_DSPPLL_CLKSEL_SET_VALID 0       //��ʱ��ѡ����Ч��־λ
#define CLK_DSPPLL_CLKDIV_REG_ADDR  NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_DSPPLL_CLKDIV_MASK      0                   //ʱ�ӷ�Ƶ����
#define CLK_DSPPLL_CLKDIV_SET_VALID 0       //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_gpll0���������ת���� */
/* ת����ʱ��clk_gpll0��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_GPLL0_ENABLE_REG_ADDR   SOC_PMCTRL_G3DPLL0CTRL_ADDR(PMCTRL_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define CLK_GPLL0_ENABLE_BIT_OFFSET SOC_PMCTRL_G3DPLL0CTRL_g3dpll0_en_cfg_START /* ʱ��ʹ��λƫ�� */

/* ת����ʱ��clk_gpll0��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_GPLL0_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_GPLL0_CLKSEL_MASK       0   //��ʱ��ѡ������
#define CLK_GPLL0_CLKSEL_SET_VALID  0       //��ʱ��ѡ����Ч��־λ
#define CLK_GPLL0_CLKDIV_REG_ADDR   NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_GPLL0_CLKDIV_MASK       0                   //ʱ�ӷ�Ƶ����
#define CLK_GPLL0_CLKDIV_SET_VALID  0       //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_gpll1���������ת���� */
/* ת����ʱ��clk_gpll1��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_GPLL1_ENABLE_REG_ADDR   NULL    /* ʹ�ܼĴ�����ַת����� */
#define CLK_GPLL1_ENABLE_BIT_OFFSET 0   /* ʱ��ʹ��λƫ�� */

/* ת����ʱ��clk_gpll1��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_GPLL1_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_GPLL1_CLKSEL_MASK       0   //��ʱ��ѡ������
#define CLK_GPLL1_CLKSEL_SET_VALID  0       //��ʱ��ѡ����Ч��־λ
#define CLK_GPLL1_CLKDIV_REG_ADDR   NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_GPLL1_CLKDIV_MASK       0                   //ʱ�ӷ�Ƶ����
#define CLK_GPLL1_CLKDIV_SET_VALID  0       //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_peripll���������ת���� */
/* ת����ʱ��clk_peripll��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_PERIPLL_ENABLE_REG_ADDR SOC_PMCTRL_PERIPLLCTRL_ADDR(PMCTRL_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define CLK_PERIPLL_ENABLE_BIT_OFFSET   SOC_PMCTRL_PERIPLLCTRL_peripll_en_START

#define CLK_DDRBUS_DIV_CLKDIV_REG_ADDR  SOC_PMCTRL_DDRCLKPROFILE_ADDR(PMCTRL_BASE_ADDR) //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_DDRBUS_DIV_CLKDIV_MASK      CALC_REG_MASK(SOC_PMCTRL_DDRCLKPROFILE_ddrbus_clk_div_prof_START, \
                                                SOC_PMCTRL_DDRCLKPROFILE_ddrbus_clk_div_prof_END)                   //ʱ�ӷ�Ƶ����
#define CLK_DDRBUS_DIV_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* ת����ʱ��clk_peripll��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_PERIPLL_CLKSEL_REG_ADDR NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_PERIPLL_CLKSEL_MASK     0   //��ʱ��ѡ������
#define CLK_PERIPLL_CLKSEL_SET_VALID    0       //��ʱ��ѡ����Ч��־λ
#define CLK_PERIPLL_CLKDIV_REG_ADDR NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_PERIPLL_CLKDIV_MASK     0                   //ʱ�ӷ�Ƶ����
#define CLK_PERIPLL_CLKDIV_SET_VALID    0       //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_hdmipll���������ת���� */
/* ת����ʱ��clk_hdmipll��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_HDMIPLL_ENABLE_REG_ADDR SOC_PMCTRL_HDMIPLLCTRL_ADDR(PMCTRL_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define CLK_HDMIPLL_ENABLE_BIT_OFFSET   SOC_PMCTRL_HDMIPLLCTRL_hdmipll_en_START   /* ʱ��ʹ��λƫ�� */

/* ת����ʱ��clk_hdmipll��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_HDMIPLL_CLKSEL_REG_ADDR NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_HDMIPLL_CLKSEL_MASK     0   //��ʱ��ѡ������
#define CLK_HDMIPLL_CLKSEL_SET_VALID    0       //��ʱ��ѡ����Ч��־λ
#define CLK_HDMIPLL_CLKDIV_REG_ADDR NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_HDMIPLL_CLKDIV_MASK     0                   //ʱ�ӷ�Ƶ����
#define CLK_HDMIPLL_CLKDIV_SET_VALID    0       //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_ddrpll���������ת���� */
/* ת����ʱ��clk_ddrpll��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_DDRPLL_ENABLE_REG_ADDR  NULL    /* ʹ�ܼĴ�����ַת����� */
#define CLK_DDRPLL_ENABLE_BIT_OFFSET    0   /* ʱ��ʹ��λƫ�� */

/* ת����ʱ��clk_ddrpll��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_DDRPLL_CLKSEL_REG_ADDR  NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_DDRPLL_CLKSEL_MASK      0   //��ʱ��ѡ������
#define CLK_DDRPLL_CLKSEL_SET_VALID 0       //��ʱ��ѡ����Ч��־λ
#define CLK_DDRPLL_CLKDIV_REG_ADDR  NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_DDRPLL_CLKDIV_MASK      0                   //ʱ�ӷ�Ƶ����
#define CLK_DDRPLL_CLKDIV_SET_VALID 0       //ʱ�ӷ�Ƶ������Ч��־λ

/* ת����ʱ��clk_300m_src��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_300M_SRC_ENABLE_REG_ADDR    NULL    /* ʹ�ܼĴ�����ַת����� */
#define CLK_300M_SRC_ENABLE_BIT_OFFSET  0   /* ʱ��ʹ��λƫ�� */

/* ת����ʱ��clk_300m_src��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_300M_SRC_CLKSEL_REG_ADDR    NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_300M_SRC_CLKSEL_MASK        0   //��ʱ��ѡ������
#define CLK_300M_SRC_CLKSEL_SET_VALID   0       //��ʱ��ѡ����Ч��־λ

#define CLK_300M_SRC_CLKDIV_REG_ADDR    NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_300M_SRC_CLKDIV_MASK        0                   //ʱ�ӷ�Ƶ����
#define CLK_300M_SRC_CLKDIV_SET_VALID   0       //ʱ�ӷ�Ƶ������Ч��־λ

/* ת����ʱ��clk_100m_src��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_100M_SRC_ENABLE_REG_ADDR    NULL    /* ʹ�ܼĴ�����ַת����� */
#define CLK_100M_SRC_ENABLE_BIT_OFFSET  0   /* ʱ��ʹ��λƫ�� */

/* ת����ʱ��clk_100m_src��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_100M_SRC_CLKSEL_REG_ADDR    NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_100M_SRC_CLKSEL_MASK        0   //��ʱ��ѡ������
#define CLK_100M_SRC_CLKSEL_SET_VALID   0       //��ʱ��ѡ����Ч��־λ

#define CLK_100M_SRC_CLKDIV_REG_ADDR    NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_100M_SRC_CLKDIV_MASK        0                   //ʱ�ӷ�Ƶ����
#define CLK_100M_SRC_CLKDIV_SET_VALID   0       //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_bus_src ���������ת���� */
/* ת����ʱ��clk_bus_src��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_BUS_SRC_ENABLE_REG_ADDR NULL    /* ʹ�ܼĴ�����ַת����� */
#define CLK_BUS_SRC_ENABLE_BIT_OFFSET   0   /* ʱ��ʹ��λƫ�� */

/* ת����ʱ��clk_bus_src��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_BUS_SRC_CLKSEL_REG_ADDR NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_BUS_SRC_CLKSEL_MASK     0   //��ʱ��ѡ������
#define CLK_BUS_SRC_CLKSEL_SET_VALID    CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_BUS_SRC_CLKDIV_REG_ADDR SOC_SCTRL_SC_CLKCFG8BIT1_ADDR(SCTRL_OFF_BASE_ADDR)  //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_BUS_SRC_CLKDIV_MASK     CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT1_clk_8bit_cfg1_value1_START, \
                                        SOC_SCTRL_SC_CLKCFG8BIT1_clk_8bit_cfg1_value1_END)                  //ʱ�ӷ�Ƶ����
#define CLK_BUS_SRC_CLKDIV_SET_VALID    SOC_SCTRL_SC_CLKCFG8BIT1_clk_8bit_cfg1_vld1_START       //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_bus_src���������ת���� */

#define CLK_27M_GATED_ENABLE_REG_ADDR SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define CLK_27M_GATED_ENABLE_BIT_OFFSET   SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_27m_START   /* ʱ��ʹ��λƫ�� */

#define CLK_27M_GATED_CLKSEL_REG_ADDR  SOC_PMCTRL_CLKCFG4BIT1_ADDR(PMCTRL_BASE_ADDR)   //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_27M_GATED_CLKSEL_MASK      CALC_REG_MASK(SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_value0_START, \
                                                        SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_value0_END)    //��ʱ��ѡ������
#define CLK_27M_GATED_CLKSEL_SET_VALID CALC_REG_MASK(SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_vld0_START, \
                                                        SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_vld0_END)    //��ʱ��ѡ������
                                                        
#define CLK_27M_ENABLE_REG_ADDR SOC_SCTRL_SC_PERIPH_CLKEN8_ADDR(SCTRL_OFF_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define CLK_27M_ENABLE_BIT_OFFSET   SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_27m_START   /* ʱ��ʹ��λƫ�� */

#define CLK_27M_CLKDIV_REG_ADDR    SOC_SCTRL_SC_CLKCFG8BIT4_ADDR(SCTRL_OFF_BASE_ADDR)  //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_27M_CLKDIV_MASK        CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT4_clk_8bit_cfg4_value1_START, \
                                                            SOC_SCTRL_SC_CLKCFG8BIT4_clk_8bit_cfg4_value1_END)                  //ʱ�ӷ�Ƶ����
#define CLK_27M_CLKDIV_SET_VALID   SOC_SCTRL_SC_CLKCFG8BIT4_clk_8bit_cfg4_vld1_START       //ʱ�ӷ�Ƶ������Ч��־λ

#define CLK_90K_ENABLE_REG_ADDR SOC_SCTRL_SC_PERIPH_CLKEN8_ADDR(SCTRL_OFF_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define CLK_90K_ENABLE_BIT_OFFSET   SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_90k_START   /* ʱ��ʹ��λƫ�� */

/* clk_mali ���������ת���� */
/* ת����ʱ��clk_mali��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_MALI_ENABLE_REG_ADDR    SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)   /* ʹ�ܼĴ�����ַת����� */
#define CLK_MALI_ENABLE_BIT_OFFSET  SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_6clk_mali_START  /* ʱ��ʹ��λƫ�� */

/* ת����ʱ��clk_mali��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_MALI_CLKSEL_REG_ADDR    SOC_PMCTRL_G3DCLKSEL_ADDR(PMCTRL_BASE_ADDR) //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_MALI_CLKSEL_MASK        CALC_REG_MASK(SOC_PMCTRL_G3DCLKSEL_g3d_pllsw_cfg_START, SOC_PMCTRL_G3DCLKSEL_g3d_pllsw_cfg_END) //��ʱ��ѡ������
#define CLK_MALI_CLKSEL_SET_VALID   CALC_REG_MASK(SOC_PMCTRL_G3DCLKSEL_g3d_pllsw_stat_START, SOC_PMCTRL_G3DCLKSEL_g3d_pllsw_stat_END)        //��ʱ��ѡ����Ч��־λ

/* ת����ʱ�� clk_mali ��ʱ�ӷ�Ƶ�Ĵ�����ѡ�������������Ч��־λ */
#define CLK_MALI_CLKDIV_REG_ADDR    SOC_PMCTRL_G3DCLKDIV_ADDR(PMCTRL_BASE_ADDR) //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_MALI_CLKDIV_MASK        CALC_REG_MASK(SOC_PMCTRL_G3DCLKDIV_g3d_clkdiv_cfg_START, \
                                            SOC_PMCTRL_G3DCLKDIV_g3d_clkdiv_cfg_END)                    //ʱ�ӷ�Ƶ����
#define CLK_MALI_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_mali���������ת���� */

/* clk_dsppll_edc0_core_gated���������ת���� */
/* ת����ʱ��clk_dsppll_edc0_core_gated��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_DSPPLL_EDC0_CORE_GATED_ENABLE_REG_ADDR      SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_DSPPLL_EDC0_CORE_GATED_ENABLE_BIT_OFFSET    SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_dsppll_edc0_core_gated_START           //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_dsppll_edc0_core_gated��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_DSPPLL_EDC0_CORE_GATED_CLKSEL_REG_ADDR  SOC_PMCTRL_CLKCFG4BIT1_ADDR(PMCTRL_BASE_ADDR)   //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_DSPPLL_EDC0_CORE_GATED_CLKSEL_MASK      CALC_REG_MASK(SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_value4_START, \
                                                            SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_value4_END)    //��ʱ��ѡ������
#define CLK_DSPPLL_EDC0_CORE_GATED_CLKSEL_SET_VALID CALC_REG_MASK(SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_vld4_START , \
                                                            SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_vld4_END)    //��ʱ��ѡ������
#define CLK_DSPPLL_EDC0_CORE_GATED_CLKDIV_REG_ADDR  NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_DSPPLL_EDC0_CORE_GATED_CLKDIV_MASK      0                   //ʱ�ӷ�Ƶ����
#define CLK_DSPPLL_EDC0_CORE_GATED_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_dsppll_edc0_core_gated���������ת���� */

/* clk_edc0_core���������ת���� */
/* ת����ʱ��clk_edc0_core��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_EDC0_CORE_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_EDC0_CORE_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_edc0_core_START          //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_edc0_core��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_EDC0_CORE_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_EDC0_CORE_CLKSEL_MASK       0   //��ʱ��ѡ������
#define CLK_EDC0_CORE_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_EDC0_CORE_CLKDIV_REG_ADDR   SOC_SCTRL_SC_CLKCFG8BIT7_ADDR(SCTRL_OFF_BASE_ADDR)  //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_EDC0_CORE_CLKDIV_MASK       CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_value1_START, \
                                                SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_value1_END)                  //ʱ�ӷ�Ƶ����
#define CLK_EDC0_CORE_CLKDIV_SET_VALID  SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_vld1_START       //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_edc0_core���������ת���� */

/* clk_mux_edc0_pix_gated���������ת���� */
/* ת����ʱ��clk_mux_edc0_pix_gated��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_MUX_EDC0_PIX_GATED_ENABLE_REG_ADDR      SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_MUX_EDC0_PIX_GATED_ENABLE_BIT_OFFSET    SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_mux_edc0_pix_gated_START           //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_mux_edc0_pix_gated��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_MUX_EDC0_PIX_GATED_CLKSEL_REG_ADDR  SOC_PMCTRL_CLKCFG4BIT1_ADDR(PMCTRL_BASE_ADDR)   //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_MUX_EDC0_PIX_GATED_CLKSEL_MASK      CALC_REG_MASK(SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_value4_START, \
                                                        SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_value4_END)    //��ʱ��ѡ������
#define CLK_MUX_EDC0_PIX_GATED_CLKSEL_SET_VALID CALC_REG_MASK(SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_vld4_START, \
                                                        SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_vld4_END)    //��ʱ��ѡ������
                                                        
#define CLK_MUX_EDC0_PIX_GATED_CLKDIV_REG_ADDR  NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_MUX_EDC0_PIX_GATED_CLKDIV_MASK      0                   //ʱ�ӷ�Ƶ����
#define CLK_MUX_EDC0_PIX_GATED_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_mux_edc0_pix_gated���������ת���� */

/* clk_edc0_pix_ldi���������ת���� */
/* ת����ʱ��clk_edc0_pix_ldi��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_EDC0_PIX_LDI_ENABLE_REG_ADDR    SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_EDC0_PIX_LDI_ENABLE_BIT_OFFSET  SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_edc0_pix_ldi_START           //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_edc0_pix_ldi��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_EDC0_PIX_LDI_CLKSEL_REG_ADDR    NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_EDC0_PIX_LDI_CLKSEL_MASK        0   //��ʱ��ѡ������
#define CLK_EDC0_PIX_LDI_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_EDC0_PIX_LDI_CLKDIV_REG_ADDR    SOC_SCTRL_SC_CLKCFG8BIT7_ADDR(SCTRL_OFF_BASE_ADDR)  //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_EDC0_PIX_LDI_CLKDIV_MASK        CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_value0_START, \
                                                            SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_value0_END)                  //ʱ�ӷ�Ƶ����
#define CLK_EDC0_PIX_LDI_CLKDIV_SET_VALID   SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_vld0_START       //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_edc0_pix_ldi���������ת���� */

/* clk_edc1_core���������ת���� */
/* ת����ʱ��clk_edc1_core��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_EDC1_CORE_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_EDC1_CORE_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_edc1_core_START          //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_edc1_core��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_EDC1_CORE_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_EDC1_CORE_CLKSEL_MASK       0   //��ʱ��ѡ������
#define CLK_EDC1_CORE_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_EDC1_CORE_CLKDIV_REG_ADDR   SOC_SCTRL_SC_CLKCFG8BIT7_ADDR(SCTRL_OFF_BASE_ADDR)  //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_EDC1_CORE_CLKDIV_MASK       CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_value3_START, \
                                                SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_value3_END)                  //ʱ�ӷ�Ƶ����
#define CLK_EDC1_CORE_CLKDIV_SET_VALID  SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_vld3_START       //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_edc1_core���������ת���� */

/* clk_axi_video_bus���������ת���� */
/* ת����ʱ��clk_axi_video_bus��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_AXI_VIDEO_BUS_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN10_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_AXI_VIDEO_BUS_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_axi_video_bus_START          //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_axi_video_bus��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_AXI_VIDEO_BUS_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_AXI_VIDEO_BUS_CLKSEL_MASK       0   //��ʱ��ѡ������
#define CLK_AXI_VIDEO_BUS_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_AXI_VIDEO_BUS_CLKDIV_REG_ADDR   NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_AXI_VIDEO_BUS_CLKDIV_MASK       0                   //ʱ�ӷ�Ƶ����
#define CLK_AXI_VIDEO_BUS_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_axi_video_bus���������ת���� */

/* clk_axi_img_bus���������ת���� */
/* ת����ʱ��clk_axi_img_bus��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_AXI_IMG_BUS_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN10_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_AXI_IMG_BUS_ENABLE_BIT_OFFSET       SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_axi_img_bus_START            //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_axi_img_bus��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_AXI_IMG_BUS_CLKSEL_REG_ADDR     NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_AXI_IMG_BUS_CLKSEL_MASK         0   //��ʱ��ѡ������
#define CLK_AXI_IMG_BUS_CLKSEL_SET_VALID    CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_AXI_IMG_BUS_CLKDIV_REG_ADDR     NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_AXI_IMG_BUS_CLKDIV_MASK         0                   //ʱ�ӷ�Ƶ����
#define CLK_AXI_IMG_BUS_CLKDIV_SET_VALID    CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_axi_img_bus���������ת���� */

/* clk_peripll_vpp_gated���������ת���� */
/* ת����ʱ��clk_peripll_vpp_gated��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_PERIPLL_VPP_GATED_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_PERIPLL_VPP_GATED_ENABLE_BIT_OFFSET SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_peripll_vpp_gated_START            //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_peripll_vpp_gated��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_PERIPLL_VPP_GATED_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_PERIPLL_VPP_GATED_CLKSEL_MASK       0   //��ʱ��ѡ������
#define CLK_PERIPLL_VPP_GATED_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_PERIPLL_VPP_GATED_CLKDIV_REG_ADDR   NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_PERIPLL_VPP_GATED_CLKDIV_MASK       0                   //ʱ�ӷ�Ƶ����
#define CLK_PERIPLL_VPP_GATED_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_peripll_vpp_gated���������ת���� */

/* clk_x2x_vpp_brg_s���������ת���� */
/* ת����ʱ��clk_x2x_vpp_brg_s��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_X2X_VPP_BRG_S_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN10_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_X2X_VPP_BRG_S_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_vpp_brg_s_START          //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_x2x_vpp_brg_s��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_X2X_VPP_BRG_S_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_X2X_VPP_BRG_S_CLKSEL_MASK       0   //��ʱ��ѡ������
#define CLK_X2X_VPP_BRG_S_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_X2X_VPP_BRG_S_CLKDIV_REG_ADDR   NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_X2X_VPP_BRG_S_CLKDIV_MASK       0                   //ʱ�ӷ�Ƶ����
#define CLK_X2X_VPP_BRG_S_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_x2x_vpp_brg_s���������ת���� */

/* clk_p2p_vpp_brg_s���������ת���� */
/* ת����ʱ��clk_p2p_vpp_brg_s��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_P2P_VPP_BRG_S_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN8_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_P2P_VPP_BRG_S_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_p2p_vpp_brg_s_START            //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_p2p_vpp_brg_s��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_P2P_VPP_BRG_S_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_P2P_VPP_BRG_S_CLKSEL_MASK       0   //��ʱ��ѡ������
#define CLK_P2P_VPP_BRG_S_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_P2P_VPP_BRG_S_CLKDIV_REG_ADDR   NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_P2P_VPP_BRG_S_CLKDIV_MASK       0                   //ʱ�ӷ�Ƶ����
#define CLK_P2P_VPP_BRG_S_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_p2p_vpp_brg_s���������ת���� */

/* clk_2vpp_slave_clk���������ת���� */
/* ת����ʱ��clk_2vpp_slave_clk��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_2VPP_SLAVE_CLK_ENABLE_REG_ADDR      SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_2VPP_SLAVE_CLK_ENABLE_BIT_OFFSET    SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_2vpp_slave_clk_START         //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_2vpp_slave_clk��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_2VPP_SLAVE_CLK_CLKSEL_REG_ADDR  NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_2VPP_SLAVE_CLK_CLKSEL_MASK      0   //��ʱ��ѡ������
#define CLK_2VPP_SLAVE_CLK_CLKSEL_SET_VALID CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_2VPP_SLAVE_CLK_CLKDIV_REG_ADDR  SOC_SCTRL_SC_CLKCFG8BIT8_ADDR(SCTRL_OFF_BASE_ADDR)  //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_2VPP_SLAVE_CLK_CLKDIV_MASK      CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_value2_START, \
                                                SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_value2_END)                  //ʱ�ӷ�Ƶ����
#define CLK_2VPP_SLAVE_CLK_CLKDIV_SET_VALID SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_vld2_START       //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_2vpp_slave_clk���������ת���� */

/* clk_peripll_venc_gated���������ת���� */
/* ת����ʱ��clk_peripll_venc_gated��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_PERIPLL_VENC_GATED_ENABLE_REG_ADDR      SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_PERIPLL_VENC_GATED_ENABLE_BIT_OFFSET        SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_peripll_venc_gated_START           //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_peripll_venc_gated��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_PERIPLL_VENC_GATED_CLKSEL_REG_ADDR  NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_PERIPLL_VENC_GATED_CLKSEL_MASK      0   //��ʱ��ѡ������
#define CLK_PERIPLL_VENC_GATED_CLKSEL_SET_VALID CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_PERIPLL_VENC_GATED_CLKDIV_REG_ADDR  NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_PERIPLL_VENC_GATED_CLKDIV_MASK      0                   //ʱ�ӷ�Ƶ����
#define CLK_PERIPLL_VENC_GATED_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_peripll_venc_gated���������ת���� */

/* clk_x2x_venc_brg_s���������ת���� */
/* ת����ʱ��clk_x2x_venc_brg_s��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_X2X_VENC_BRG_S_ENABLE_REG_ADDR      SOC_SCTRL_SC_PERIPH_CLKEN10_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_X2X_VENC_BRG_S_ENABLE_BIT_OFFSET    SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_venc_brg_s_START         //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_x2x_venc_brg_s��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_X2X_VENC_BRG_S_CLKSEL_REG_ADDR  NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_X2X_VENC_BRG_S_CLKSEL_MASK      0   //��ʱ��ѡ������
#define CLK_X2X_VENC_BRG_S_CLKSEL_SET_VALID CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_X2X_VENC_BRG_S_CLKDIV_REG_ADDR  NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_X2X_VENC_BRG_S_CLKDIV_MASK      0                   //ʱ�ӷ�Ƶ����
#define CLK_X2X_VENC_BRG_S_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_x2x_venc_brg_s���������ת���� */

/* clk_p2p_venc_brg_s���������ת���� */
/* ת����ʱ��clk_p2p_venc_brg_s��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_P2P_VENC_BRG_S_ENABLE_REG_ADDR      SOC_SCTRL_SC_PERIPH_CLKEN8_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_P2P_VENC_BRG_S_ENABLE_BIT_OFFSET    SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_p2p_venc_brg_s_START           //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_p2p_venc_brg_s��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_P2P_VENC_BRG_S_CLKSEL_REG_ADDR  NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_P2P_VENC_BRG_S_CLKSEL_MASK      0   //��ʱ��ѡ������
#define CLK_P2P_VENC_BRG_S_CLKSEL_SET_VALID CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_P2P_VENC_BRG_S_CLKDIV_REG_ADDR  NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_P2P_VENC_BRG_S_CLKDIV_MASK      0                   //ʱ�ӷ�Ƶ����
#define CLK_P2P_VENC_BRG_S_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_p2p_venc_brg_s���������ת���� */

/* clk_0venc_slave_clk���������ת���� */
/* ת����ʱ��clk_0venc_slave_clk��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_0VENC_SLAVE_CLK_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_0VENC_SLAVE_CLK_ENABLE_BIT_OFFSET       SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_0venc_clk_START          //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_0venc_slave_clk��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_0VENC_SLAVE_CLK_CLKSEL_REG_ADDR NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_0VENC_SLAVE_CLK_CLKSEL_MASK     0   //��ʱ��ѡ������
#define CLK_0VENC_SLAVE_CLK_CLKSEL_SET_VALID    CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_0VENC_SLAVE_CLK_CLKDIV_REG_ADDR SOC_SCTRL_SC_CLKCFG8BIT8_ADDR(SCTRL_OFF_BASE_ADDR)  //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_0VENC_SLAVE_CLK_CLKDIV_MASK     CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_value3_START, \
                                                SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_value3_END)                  //ʱ�ӷ�Ƶ����
#define CLK_0VENC_SLAVE_CLK_CLKDIV_SET_VALID    SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_vld3_START       //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_0venc_slave_clk���������ת���� */

/* clk_peripll_vdec_gated���������ת���� */
/* ת����ʱ��clk_peripll_vdec_gated��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_PERIPLL_VDEC_GATED_ENABLE_REG_ADDR      SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_PERIPLL_VDEC_GATED_ENABLE_BIT_OFFSET        SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_dsppll_vdec_gated_START            //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_peripll_vdec_gated��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_PERIPLL_VDEC_GATED_CLKSEL_REG_ADDR  NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_PERIPLL_VDEC_GATED_CLKSEL_MASK      0   //��ʱ��ѡ������
#define CLK_PERIPLL_VDEC_GATED_CLKSEL_SET_VALID CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_PERIPLL_VDEC_GATED_CLKDIV_REG_ADDR  NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_PERIPLL_VDEC_GATED_CLKDIV_MASK      0                   //ʱ�ӷ�Ƶ����
#define CLK_PERIPLL_VDEC_GATED_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_peripll_vdec_gated���������ת���� */

/* clk_x2x_vdec_brg_s���������ת���� */
/* ת����ʱ��clk_x2x_vdec_brg_s��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_X2X_VDEC_BRG_S_ENABLE_REG_ADDR      SOC_SCTRL_SC_PERIPH_CLKEN10_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_X2X_VDEC_BRG_S_ENABLE_BIT_OFFSET    SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_vdec_brg_s_START         //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_vdec_vpp_brg_s��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_X2X_VDEC_BRG_S_CLKSEL_REG_ADDR  NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_X2X_VDEC_BRG_S_CLKSEL_MASK      0   //��ʱ��ѡ������
#define CLK_X2X_VDEC_BRG_S_CLKSEL_SET_VALID CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_X2X_VDEC_BRG_S_CLKDIV_REG_ADDR  NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_X2X_VDEC_BRG_S_CLKDIV_MASK      0                   //ʱ�ӷ�Ƶ����
#define CLK_X2X_VDEC_BRG_S_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_x2x_vdec_brg_s���������ת���� */

/* clk_p2p_vdec_brg_s���������ת���� */
/* ת����ʱ��clk_p2p_vdec_brg_s��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_P2P_VDEC_BRG_S_ENABLE_REG_ADDR      SOC_SCTRL_SC_PERIPH_CLKEN8_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_P2P_VDEC_BRG_S_ENABLE_BIT_OFFSET    SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_p2p_vdec_brg_s_START           //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_p2p_vdec_brg_s��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_P2P_VDEC_BRG_S_CLKSEL_REG_ADDR  NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_P2P_VDEC_BRG_S_CLKSEL_MASK      0   //��ʱ��ѡ������
#define CLK_P2P_VDEC_BRG_S_CLKSEL_SET_VALID CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_P2P_VDEC_BRG_S_CLKDIV_REG_ADDR  NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_P2P_VDEC_BRG_S_CLKDIV_MASK      0                   //ʱ�ӷ�Ƶ����
#define CLK_P2P_VDEC_BRG_S_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_p2p_vdec_brg_s���������ת���� */

/* clk_1vdec_slave_clk���������ת���� */
/* ת����ʱ��clk_1vdec_slave_clk��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_1VDEC_SLAVE_CLK_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_1VDEC_SLAVE_CLK_ENABLE_BIT_OFFSET       SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_1vdec_clk_START         //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_1vdec_slave_clk��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_1VDEC_SLAVE_CLK_CLKSEL_REG_ADDR NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_1VDEC_SLAVE_CLK_CLKSEL_MASK     0   //��ʱ��ѡ������
#define CLK_1VDEC_SLAVE_CLK_CLKSEL_SET_VALID    CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_1VDEC_SLAVE_CLK_CLKDIV_REG_ADDR SOC_SCTRL_SC_CLKCFG8BIT8_ADDR(SCTRL_OFF_BASE_ADDR)  //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_1VDEC_SLAVE_CLK_CLKDIV_MASK     CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_value1_START, \
                                                SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_value1_END)                  //ʱ�ӷ�Ƶ����
#define CLK_1VDEC_SLAVE_CLK_CLKDIV_SET_VALID    SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_vld1_START       //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_1vdec_slave_clk���������ת���� */

/* clk_dsppll_g2dcore_gated���������ת���� */
/* ת����ʱ��clk_dsppll_g2dcore_gated��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_DSPPLL_G2DCORE_GATED_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR) //ʹ�ܼĴ�����ַת�����
#define CLK_DSPPLL_G2DCORE_GATED_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_dsppll_g2dcore_gated_START         //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_dsppll_g2dcore_gated��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_DSPPLL_G2DCORE_GATED_CLKSEL_REG_ADDR    NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_DSPPLL_G2DCORE_GATED_CLKSEL_MASK        0   //��ʱ��ѡ������
#define CLK_DSPPLL_G2DCORE_GATED_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_DSPPLL_G2DCORE_GATED_CLKDIV_REG_ADDR    NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_DSPPLL_G2DCORE_GATED_CLKDIV_MASK        0                   //ʱ�ӷ�Ƶ����
#define CLK_DSPPLL_G2DCORE_GATED_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_dsppll_g2dcore_gated���������ת���� */

/* clk_5g2d_core_clk���������ת���� */
/* ת����ʱ��clk_5g2d_core_clk��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_5G2D_CORE_CLK_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_5G2D_CORE_CLK_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_5g2d_core_clk_START          //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_5g2d_core_clk��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_5G2D_CORE_CLK_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_5G2D_CORE_CLK_CLKSEL_MASK       0   //��ʱ��ѡ������
#define CLK_5G2D_CORE_CLK_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_5G2D_CORE_CLK_CLKDIV_REG_ADDR   SOC_SCTRL_SC_CLKCFG8BIT6_ADDR(SCTRL_OFF_BASE_ADDR)  //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_5G2D_CORE_CLK_CLKDIV_MASK       CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_value0_START, \
                                                SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_value0_END)                  //ʱ�ӷ�Ƶ����
#define CLK_5G2D_CORE_CLK_CLKDIV_SET_VALID  SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_vld0_START       //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_5g2d_core_clk���������ת���� */

/* clk_4g2d_axi_clkhb���������ת���� */
/* ת����ʱ��clk_4g2d_axi_clkhb��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_4G2D_AXI_CLKHB_ENABLE_REG_ADDR      SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_4G2D_AXI_CLKHB_ENABLE_BIT_OFFSET        SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_4g2d_axi_clkhb_START         //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_4g2d_axi_clkhb��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_4G2D_AXI_CLKHB_CLKSEL_REG_ADDR  NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_4G2D_AXI_CLKHB_CLKSEL_MASK      0   //��ʱ��ѡ������
#define CLK_4G2D_AXI_CLKHB_CLKSEL_SET_VALID CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_4G2D_AXI_CLKHB_CLKDIV_REG_ADDR  NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_4G2D_AXI_CLKHB_CLKDIV_MASK      0                   //ʱ�ӷ�Ƶ����
#define CLK_4G2D_AXI_CLKHB_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_4g2d_axi_clkhb���������ת���� */

/* clk_3g2d_cfg_clk���������ת���� */
/* ת����ʱ��clk_3g2d_cfg_clk��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_3G2D_CFG_CLK_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_3G2D_CFG_CLK_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_3g2d_cfg_clk_START           //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_3g2d_cfg_clk��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_3G2D_CFG_CLK_CLKSEL_REG_ADDR    NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_3G2D_CFG_CLK_CLKSEL_MASK        0   //��ʱ��ѡ������
#define CLK_3G2D_CFG_CLK_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_3G2D_CFG_CLK_CLKDIV_REG_ADDR    NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_3G2D_CFG_CLK_CLKDIV_MASK        0                   //ʱ�ӷ�Ƶ����
#define CLK_3G2D_CFG_CLK_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_3g2d_cfg_clk���������ת���� */

/* clk_p2p_mali_brg_s ���������ת���� */
/* ת����ʱ�� clk_p2p_mali_brg_s ��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_P2P_MALI_BRG_S_ENABLE_REG_ADDR      SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_P2P_MALI_BRG_S_ENABLE_BIT_OFFSET        SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_7pclk_p2p_mali_START           //ʱ��ʹ��λƫ��

/* ת����ʱ�� clk_p2p_mali_brg_s ��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_P2P_MALI_BRG_S_CLKSEL_REG_ADDR  NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_P2P_MALI_BRG_S_CLKSEL_MASK      0   //��ʱ��ѡ������
#define CLK_P2P_MALI_BRG_S_CLKSEL_SET_VALID CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_P2P_MALI_BRG_S_CLKDIV_REG_ADDR  NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_P2P_MALI_BRG_S_CLKDIV_MASK      0                   //ʱ�ӷ�Ƶ����
#define CLK_P2P_MALI_BRG_S_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_p2p_mali_brg_s ���������ת���� */

/* clk_x2x_mali_brg_s���������ת���� */
/* ת����ʱ��clk_x2x_mali_brg_s��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_X2X_MALI_BRG_S_ENABLE_REG_ADDR      SOC_SCTRL_SC_PERIPH_CLKEN10_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_X2X_MALI_BRG_S_ENABLE_BIT_OFFSET        SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_mali_brg_s_START         //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_x2x_mali_brg_s��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_X2X_MALI_BRG_S_CLKSEL_REG_ADDR  NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_X2X_MALI_BRG_S_CLKSEL_MASK      0   //��ʱ��ѡ������
#define CLK_X2X_MALI_BRG_S_CLKSEL_SET_VALID CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_X2X_MALI_BRG_S_CLKDIV_REG_ADDR  NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_X2X_MALI_BRG_S_CLKDIV_MASK      0                   //ʱ�ӷ�Ƶ����
#define CLK_X2X_MALI_BRG_S_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_x2x_mali_brg_s���������ת���� */

/* clk_x2x_mali_brg_m���������ת���� */
/* ת����ʱ��clk_x2x_mali_brg_m��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_X2X_MALI_BRG_M_ENABLE_REG_ADDR      SOC_SCTRL_SC_PERIPH_CLKEN10_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_X2X_MALI_BRG_M_ENABLE_BIT_OFFSET        SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_mali_brg_m_START         //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_x2x_mali_brg_m��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_X2X_MALI_BRG_M_CLKSEL_REG_ADDR  NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_X2X_MALI_BRG_M_CLKSEL_MASK      0   //��ʱ��ѡ������
#define CLK_X2X_MALI_BRG_M_CLKSEL_SET_VALID CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_X2X_MALI_BRG_M_CLKDIV_REG_ADDR  NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_X2X_MALI_BRG_M_CLKDIV_MASK      0                   //ʱ�ӷ�Ƶ����
#define CLK_X2X_MALI_BRG_M_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_x2x_mali_brg_m���������ת���� */

/* clk_axi_mali_bus���������ת���� */
/* ת����ʱ��clk_axi_mali_bus��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_AXI_MALI_BUS_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN10_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_AXI_MALI_BUS_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_axi_mali_bus_START           //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_axi_mali_bus��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_AXI_MALI_BUS_CLKSEL_REG_ADDR    NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_AXI_MALI_BUS_CLKSEL_MASK        0   //��ʱ��ѡ������
#define CLK_AXI_MALI_BUS_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_AXI_MALI_BUS_CLKDIV_REG_ADDR    NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_AXI_MALI_BUS_CLKDIV_MASK        0                   //ʱ�ӷ�Ƶ����
#define CLK_AXI_MALI_BUS_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_axi_mali_bus���������ת���� */

/* clk_aclk_edc0���������ת���� */
/* ת����ʱ��clk_aclk_edc0��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_ACLK_EDC0_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_ACLK_EDC0_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_aclk_edc0_START          //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_aclk_edc0��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_ACLK_EDC0_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_ACLK_EDC0_CLKSEL_MASK       0   //��ʱ��ѡ������
#define CLK_ACLK_EDC0_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_ACLK_EDC0_CLKDIV_REG_ADDR   NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_ACLK_EDC0_CLKDIV_MASK       0                   //ʱ�ӷ�Ƶ����
#define CLK_ACLK_EDC0_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_aclk_edc0���������ת���� */

/* clk_edc0_cfg_clk���������ת���� */
/* ת����ʱ��clk_edc0_cfg_clk��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_EDC0_CFG_CLK_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_EDC0_CFG_CLK_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_edc0_cfg_clk_START           //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_edc0_cfg_clk��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_EDC0_CFG_CLK_CLKSEL_REG_ADDR    NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_EDC0_CFG_CLK_CLKSEL_MASK        0   //��ʱ��ѡ������
#define CLK_EDC0_CFG_CLK_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_EDC0_CFG_CLK_CLKDIV_REG_ADDR    NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_EDC0_CFG_CLK_CLKDIV_MASK        0                   //ʱ�ӷ�Ƶ����
#define CLK_EDC0_CFG_CLK_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_edc0_cfg_clk���������ת���� */

/* clk_dsio_cfg_clk���������ת���� */
/* ת����ʱ��clk_dsio_cfg_clk��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_DSIO_CFG_CLK_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_DSIO_CFG_CLK_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_dsio_cfg_clk_START           //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_dsio_cfg_clk��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_DSIO_CFG_CLK_CLKSEL_REG_ADDR    NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_DSIO_CFG_CLK_CLKSEL_MASK        0   //��ʱ��ѡ������
#define CLK_DSIO_CFG_CLK_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_DSIO_CFG_CLK_CLKDIV_REG_ADDR    NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_DSIO_CFG_CLK_CLKDIV_MASK        0               //ʱ�ӷ�Ƶ����
#define CLK_DSIO_CFG_CLK_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_dsio_cfg_clk���������ת���� */

/* clk_edc1_pix_ldi���������ת���� */
/* ת����ʱ��clk_edc1_pix_ldi��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_EDC1_PIX_LDI_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_EDC1_PIX_LDI_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_edc1_pix_ldi_START           //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_edc1_pix_ldi��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_EDC1_PIX_LDI_CLKSEL_REG_ADDR    NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_EDC1_PIX_LDI_CLKSEL_MASK        0   //��ʱ��ѡ������
#define CLK_EDC1_PIX_LDI_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_EDC1_PIX_LDI_CLKDIV_REG_ADDR    SOC_SCTRL_SC_CLKCFG8BIT7_ADDR(SCTRL_OFF_BASE_ADDR)  //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_EDC1_PIX_LDI_CLKDIV_MASK        CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_value2_START, \
                                                SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_value2_END)                  //ʱ�ӷ�Ƶ����
#define CLK_EDC1_PIX_LDI_CLKDIV_SET_VALID   SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_vld2_START       //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_edc1_pix_ldi���������ת���� */

/* clk_edc1_axi���������ת���� */
/* ת����ʱ��clk_edc1_axi��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_EDC1_AXI_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_EDC1_AXI_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_edc1_axi_START           //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_edc1_axi��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_EDC1_AXI_CLKSEL_REG_ADDR    NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_EDC1_AXI_CLKSEL_MASK        0   //��ʱ��ѡ������
#define CLK_EDC1_AXI_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_EDC1_AXI_CLKDIV_REG_ADDR    NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_EDC1_AXI_CLKDIV_MASK        0                   //ʱ�ӷ�Ƶ����
#define CLK_EDC1_AXI_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_edc1_axi���������ת���� */

/* clk_edc1_cfg_clk���������ת���� */
/* ת����ʱ��clk_edc1_cfg_clk��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_EDC1_CFG_CLK_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_EDC1_CFG_CLK_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_edc1_cfg_clk_START         //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_edc1_cfg_clk��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_EDC1_CFG_CLK_CLKSEL_REG_ADDR    NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_EDC1_CFG_CLK_CLKSEL_MASK        0   //��ʱ��ѡ������
#define CLK_EDC1_CFG_CLK_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_EDC1_CFG_CLK_CLKDIV_REG_ADDR    NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_EDC1_CFG_CLK_CLKDIV_MASK        0                   //ʱ�ӷ�Ƶ����
#define CLK_EDC1_CFG_CLK_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_edc1_cfg_clk���������ת���� */

/* clk_isp_cfg_clk���������ת���� */
/* ת����ʱ��clk_isp_cfg_clk��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_ISP_CFG_CLK_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_ISP_CFG_CLK_ENABLE_BIT_OFFSET       SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_isp_cfg_clk_START            //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_isp_cfg_clk��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_ISP_CFG_CLK_CLKSEL_REG_ADDR NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_ISP_CFG_CLK_CLKSEL_MASK     0   //��ʱ��ѡ������
#define CLK_ISP_CFG_CLK_CLKSEL_SET_VALID    CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_ISP_CFG_CLK_CLKDIV_REG_ADDR NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_ISP_CFG_CLK_CLKDIV_MASK     0                   //ʱ�ӷ�Ƶ����
#define CLK_ISP_CFG_CLK_CLKDIV_SET_VALID    CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_isp_cfg_clk���������ת���� */

/* clk_isp_axi���������ת���� */
/* ת����ʱ��clk_isp_axi��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_ISP_AXI_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_ISP_AXI_ENABLE_BIT_OFFSET       SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_isp_axi_START         //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_isp_axi��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_ISP_AXI_CLKSEL_REG_ADDR NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_ISP_AXI_CLKSEL_MASK     0   //��ʱ��ѡ������
#define CLK_ISP_AXI_CLKSEL_SET_VALID    CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_ISP_AXI_CLKDIV_REG_ADDR NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_ISP_AXI_CLKDIV_MASK     0                   //ʱ�ӷ�Ƶ����
#define CLK_ISP_AXI_CLKDIV_SET_VALID    CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_isp_axi���������ת���� */

/* clk_peripll_isp_gated���������ת���� */
/* ת����ʱ��clk_peripll_isp_gated��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_PERIPLL_ISP_GATED_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_PERIPLL_ISP_GATED_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_mux_isp_gated_START         //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_peripll_isp_gated��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_PERIPLL_ISP_GATED_CLKSEL_REG_ADDR   SOC_PMCTRL_CLKCFG4BIT1_ADDR(PMCTRL_BASE_ADDR)     //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_PERIPLL_ISP_GATED_CLKSEL_MASK       CALC_REG_MASK(SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_value2_START, \
                                                SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_value2_END)              //ʱ�ӷ�Ƶ����
#define CLK_PERIPLL_ISP_GATED_CLKSEL_SET_VALID  CALC_REG_MASK(SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_vld2_START , \
                                                SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_vld2_END)              //ʱ�ӷ�Ƶ����
#define CLK_PERIPLL_ISP_GATED_CLKDIV_REG_ADDR   NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_PERIPLL_ISP_GATED_CLKDIV_MASK       0                   //ʱ�ӷ�Ƶ����
#define CLK_PERIPLL_ISP_GATED_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_peripll_isp_gated���������ת���� */

/* clk_isp���������ת���� */
/* ת����ʱ��clk_isp��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_ISP_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_ISP_ENABLE_BIT_OFFSET       SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_clk_isp_START            //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_isp��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_ISP_CLKSEL_REG_ADDR NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_ISP_CLKSEL_MASK     0   //��ʱ��ѡ������
#define CLK_ISP_CLKSEL_SET_VALID    CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_ISP_CLKDIV_REG_ADDR     SOC_SCTRL_SC_CLKCFG8BIT6_ADDR(SCTRL_OFF_BASE_ADDR)  //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_ISP_CLKDIV_MASK         CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_value1_START, \
                                                SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_value1_END)              //ʱ�ӷ�Ƶ����
#define CLK_ISP_CLKDIV_SET_VALID    SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_vld1_START       //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_isp���������ת���� */


/* clk_peripll_isp_ref_gated���������ת���� */
/* ת����ʱ��clk_peripll_isp_ref_gated��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_PERIPLL_ISP_REF_GATED_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_PERIPLL_ISP_REF_GATED_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_peripll_isp_ref_gated_START            //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_peripll_isp_ref_gated��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_PERIPLL_ISP_REF_GATED_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_PERIPLL_ISP_REF_GATED_CLKSEL_MASK       0   //��ʱ��ѡ������
#define CLK_PERIPLL_ISP_REF_GATED_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_PERIPLL_ISP_REF_GATED_CLKDIV_REG_ADDR       NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_PERIPLL_ISP_REF_GATED_CLKDIV_MASK           0               //ʱ�ӷ�Ƶ����
#define CLK_PERIPLL_ISP_REF_GATED_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_peripll_isp_ref_gated���������ת���� */

/* clk_isp_ref���������ת���� */
/* ת����ʱ��clk_isp_ref��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_ISP_REF_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_ISP_REF_ENABLE_BIT_OFFSET       SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_clk_isp_ref_START            //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_isp_ref��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_ISP_REF_CLKSEL_REG_ADDR NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_ISP_REF_CLKSEL_MASK     0   //��ʱ��ѡ������
#define CLK_ISP_REF_CLKSEL_SET_VALID    CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_ISP_REF_CLKDIV_REG_ADDR     SOC_SCTRL_SC_CLKCFG8BIT6_ADDR(SCTRL_OFF_BASE_ADDR)  //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_ISP_REF_CLKDIV_MASK         CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_value3_START, \
                                                SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_value3_END)              //ʱ�ӷ�Ƶ����
#define CLK_ISP_REF_CLKDIV_SET_VALID    SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_vld3_START       //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_isp_ref���������ת���� */

/* clk_hdmi_slave���������ת���� */
/* ת����ʱ��clk_hdmi_slave��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_HDMI_SLAVE_ENABLE_REG_ADDR      SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_HDMI_SLAVE_ENABLE_BIT_OFFSET        SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_hdmi_slave_START         //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_hdmi_slave��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_HDMI_SLAVE_CLKSEL_REG_ADDR  NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_HDMI_SLAVE_CLKSEL_MASK      0   //��ʱ��ѡ������
#define CLK_HDMI_SLAVE_CLKSEL_SET_VALID CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_HDMI_SLAVE_CLKDIV_REG_ADDR      NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_HDMI_SLAVE_CLKDIV_MASK          0               //ʱ�ӷ�Ƶ����
#define CLK_HDMI_SLAVE_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_hdmi_slave���������ת���� */

/* clk_hdmi_sck���������ת���� */
/* ת����ʱ��clk_hdmi_sck��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_HDMI_SCK_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_HDMI_SCK_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_clk_hdmi_sck_START           //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_hdmi_sck��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_HDMI_SCK_CLKSEL_REG_ADDR    NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_HDMI_SCK_CLKSEL_MASK        0   //��ʱ��ѡ������
#define CLK_HDMI_SCK_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_HDMI_SCK_CLKDIV_REG_ADDR        NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_HDMI_SCK_CLKDIV_MASK            0               //ʱ�ӷ�Ƶ����
#define CLK_HDMI_SCK_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_hdmi_sck���������ת���� */

/* clk_hdmipll_divfrac���������ת���� */
/* ת����ʱ��clk_hdmipll_divfrac��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_HDMIPLL_DIVFRAC_ENABLE_REG_ADDR     NULL    //ʹ�ܼĴ�����ַת�����
#define CLK_HDMIPLL_DIVFRAC_ENABLE_BIT_OFFSET       0           //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_hdmipll_divfrac��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_HDMIPLL_DIVFRAC_CLKSEL_REG_ADDR NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_HDMIPLL_DIVFRAC_CLKSEL_MASK     0   //��ʱ��ѡ������
#define CLK_HDMIPLL_DIVFRAC_CLKSEL_SET_VALID    CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_HDMIPLL_DIVFRAC_CLKDIV_REG_ADDR SOC_SCTRL_SC_CLKCFGALL4_ADDR(SCTRL_OFF_BASE_ADDR)   //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_HDMIPLL_DIVFRAC_CLKDIV_MASK     CALC_REG_MASK(SOC_SCTRL_SC_CLKCFGALL4_divfrac_49m_START, \
                                                SOC_SCTRL_SC_CLKCFGALL4_divfrac_49m_END)                //ʱ�ӷ�Ƶ����
#define CLK_HDMIPLL_DIVFRAC_CLKDIV_SET_VALID    CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_hdmipll_divfrac���������ת���� */

/* clk_mclk_hdmi���������ת���� */
/* ת����ʱ��clk_mclk_hdmi��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_MCLK_HDMI_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_MCLK_HDMI_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_mclk_hdmi_START          //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_mclk_hdmi��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_MCLK_HDMI_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_MCLK_HDMI_CLKSEL_MASK       0   //��ʱ��ѡ������
#define CLK_MCLK_HDMI_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_MCLK_HDMI_CLKDIV_REG_ADDR       NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_MCLK_HDMI_CLKDIV_MASK           0               //ʱ�ӷ�Ƶ����
#define CLK_MCLK_HDMI_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_mclk_hdmi���������ת���� */

/* clk_asp_hdmi_adws���������ת���� */
/* ת����ʱ��clk_asp_hdmi_adws��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_ASP_HDMI_ADWS_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN3_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_ASP_HDMI_ADWS_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_clk_asp_hdmi_adws_START            //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_asp_hdmi_adws��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_ASP_HDMI_ADWS_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_ASP_HDMI_ADWS_CLKSEL_MASK       0   //��ʱ��ѡ������
#define CLK_ASP_HDMI_ADWS_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_ASP_HDMI_ADWS_CLKDIV_REG_ADDR       NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_ASP_HDMI_ADWS_CLKDIV_MASK           0               //ʱ�ӷ�Ƶ����
#define CLK_ASP_HDMI_ADWS_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_asp_hdmi_adws���������ת���� */

/* clk_asp_hdmi_bclk���������ת���� */
/* ת����ʱ��clk_asp_hdmi_bclk��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_ASP_HDMI_BCLK_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN3_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_ASP_HDMI_BCLK_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_clk_asp_hdmi_bclk_START            //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_asp_hdmi_bclk��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_ASP_HDMI_BCLK_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_ASP_HDMI_BCLK_CLKSEL_MASK       0   //��ʱ��ѡ������
#define CLK_ASP_HDMI_BCLK_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_ASP_HDMI_BCLK_CLKDIV_REG_ADDR       NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_ASP_HDMI_BCLK_CLKDIV_MASK           0               //ʱ�ӷ�Ƶ����
#define CLK_ASP_HDMI_BCLK_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_asp_hdmi_bclk���������ת���� */

/* clk_asp_hdmi_ref���������ת���� */
/* ת����ʱ��clk_asp_hdmi_ref��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_ASP_HDMI_REF_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN3_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_ASP_HDMI_REF_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_clk_asp_hdmi_ref_START         //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_asp_hdmi_ref��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_ASP_HDMI_REF_CLKSEL_REG_ADDR    NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_ASP_HDMI_REF_CLKSEL_MASK        0   //��ʱ��ѡ������
#define CLK_ASP_HDMI_REF_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_ASP_HDMI_REF_CLKDIV_REG_ADDR        NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_ASP_HDMI_REF_CLKDIV_MASK            0               //ʱ�ӷ�Ƶ����
#define CLK_ASP_HDMI_REF_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_asp_hdmi_ref���������ת���� */

/* clk_asp_spdif_ref���������ת���� */
/* ת����ʱ��clk_asp_spdif_ref��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_ASP_SPDIF_REF_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN3_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_ASP_SPDIF_REF_ENABLE_BIT_OFFSET SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_clk_asp_spdif_ref_START            //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_asp_spdif_ref��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_ASP_SPDIF_REF_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_ASP_SPDIF_REF_CLKSEL_MASK       0   //��ʱ��ѡ������
#define CLK_ASP_SPDIF_REF_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_ASP_SPDIF_REF_CLKDIV_REG_ADDR       NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_ASP_SPDIF_REF_CLKDIV_MASK           0               //ʱ�ӷ�Ƶ����
#define CLK_ASP_SPDIF_REF_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

#define CLK_ASP_CFG_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN3_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_ASP_CFG_ENABLE_BIT_OFFSET SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_asp_cfg_clk_START            //ʱ��ʹ��λƫ��

/* clk_asp_spdif_ref���������ת���� */

/* clk_dphy0_ref���������ת���� */
/* ת����ʱ��clk_dphy0_ref��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_DPHY0_REF_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_DPHY0_REF_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_dphy0_START          //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_dphy0_ref��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_DPHY0_REF_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_DPHY0_REF_CLKSEL_MASK       0   //��ʱ��ѡ������
#define CLK_DPHY0_REF_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_DPHY0_REF_CLKDIV_REG_ADDR       NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_DPHY0_REF_CLKDIV_MASK           0               //ʱ�ӷ�Ƶ����
#define CLK_DPHY0_REF_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_dphy0_ref���������ת���� */

/* clk_dphy0_cfg���������ת���� */
/* ת����ʱ��clk_dphy0_cfg��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_DPHY0_CFG_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_DPHY0_CFG_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_dphy0_clk_START          //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_dphy0_cfg��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_DPHY0_CFG_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_DPHY0_CFG_CLKSEL_MASK       0   //��ʱ��ѡ������
#define CLK_DPHY0_CFG_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_DPHY0_CFG_CLKDIV_REG_ADDR       NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_DPHY0_CFG_CLKDIV_MASK           0               //ʱ�ӷ�Ƶ����
#define CLK_DPHY0_CFG_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_dphy0_cfg���������ת���� */

/* clk_dphy1_cfg���������ת���� */
/* ת����ʱ��clk_dphy1_cfg��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_DPHY1_CFG_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_DPHY1_CFG_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_dphy1_cfg_START          //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_dphy1_cfg��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_DPHY1_CFG_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_DPHY1_CFG_CLKSEL_MASK       0   //��ʱ��ѡ������
#define CLK_DPHY1_CFG_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_DPHY1_CFG_CLKDIV_REG_ADDR       NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_DPHY1_CFG_CLKDIV_MASK           0               //ʱ�ӷ�Ƶ����
#define CLK_DPHY1_CFG_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_dphy1_cfg���������ת���� */

/* clk_dphy2_cfg���������ת���� */
/* ת����ʱ��clk_dphy2_cfg��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_DPHY2_CFG_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_DPHY2_CFG_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_dphy2_cfg_clk_START          //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_dphy2_cfg��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_DPHY2_CFG_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_DPHY2_CFG_CLKSEL_MASK       0   //��ʱ��ѡ������
#define CLK_DPHY2_CFG_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_DPHY2_CFG_CLKDIV_REG_ADDR       NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_DPHY2_CFG_CLKDIV_MASK           0               //ʱ�ӷ�Ƶ����
#define CLK_DPHY2_CFG_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_dphy2_cfg���������ת���� */

/* clk_uart0���������ת���� */
/* ת����ʱ��clk_uart0��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_UART0_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_UART0_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart0_START            //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_uart0��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_UART0_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_UART0_CLKSEL_MASK       0   //��ʱ��ѡ������
#define CLK_UART0_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_UART0_CLKDIV_REG_ADDR   NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_UART0_CLKDIV_MASK       0                   //ʱ�ӷ�Ƶ����
#define CLK_UART0_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

#define PCLK_UART0_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define PCLK_UART0_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart0_pclk_START            //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_uart0��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define PCLK_UART0_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define PCLK_UART0_CLKSEL_MASK       0   //��ʱ��ѡ������
#define PCLK_UART0_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define PCLK_UART0_CLKDIV_REG_ADDR   NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define PCLK_UART0_CLKDIV_MASK       0                   //ʱ�ӷ�Ƶ����
#define PCLK_UART0_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_uart0���������ת���� */

/* clk_uart1���������ת���� */
/* ת����ʱ��clk_uart1��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_UART1_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_UART1_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart1_START            //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_uart1��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_UART1_CLKSEL_REG_ADDR   SOC_SCTRL_SC_CLK_SEL0_ADDR(SCTRL_OFF_BASE_ADDR) //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_UART1_CLKSEL_MASK       CALC_REG_MASK(SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart1_START, \
                                        SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart1_END)    //��ʱ��ѡ������
#define CLK_UART1_CLKSEL_SET_VALID  CALC_REG_MASK(SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart1_msk_START , \
                                        SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart1_msk_END)    //��ʱ��ѡ������
                                        
#define CLK_UART1_CLKDIV_REG_ADDR   NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_UART1_CLKDIV_MASK       0                   //ʱ�ӷ�Ƶ����
#define CLK_UART1_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

#define PCLK_UART1_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define PCLK_UART1_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart1_pclk_START            //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_uart0��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define PCLK_UART1_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define PCLK_UART1_CLKSEL_MASK       0   //��ʱ��ѡ������
#define PCLK_UART1_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define PCLK_UART1_CLKDIV_REG_ADDR   NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define PCLK_UART1_CLKDIV_MASK       0                   //ʱ�ӷ�Ƶ����
#define PCLK_UART1_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_uart1���������ת���� */

/* clk_uart2���������ת���� */
/* ת����ʱ��clk_uart2��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_UART2_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_UART2_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart2_START            //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_uart2��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_UART2_CLKSEL_REG_ADDR   SOC_SCTRL_SC_CLK_SEL0_ADDR(SCTRL_OFF_BASE_ADDR) //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_UART2_CLKSEL_MASK       CALC_REG_MASK(SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart2_START, \
                                        SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart2_END)    //��ʱ��ѡ������
#define CLK_UART2_CLKSEL_SET_VALID  CALC_REG_MASK(SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart2_msk_START, \
                                        SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart2_msk_END)    //��ʱ��ѡ������
#define CLK_UART2_CLKDIV_REG_ADDR   NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_UART2_CLKDIV_MASK       0                   //ʱ�ӷ�Ƶ����
#define CLK_UART2_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

#define PCLK_UART2_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define PCLK_UART2_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart2_pclk_START            //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_uart0��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define PCLK_UART2_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define PCLK_UART2_CLKSEL_MASK       0   //��ʱ��ѡ������
#define PCLK_UART2_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define PCLK_UART2_CLKDIV_REG_ADDR   NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define PCLK_UART2_CLKDIV_MASK       0                   //ʱ�ӷ�Ƶ����
#define PCLK_UART2_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_uart2���������ת���� */

/* clk_uart3���������ת���� */
/* ת����ʱ��clk_uart3��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_UART3_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_UART3_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart3_START            //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_uart3��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_UART3_CLKSEL_REG_ADDR   SOC_SCTRL_SC_CLK_SEL0_ADDR(SCTRL_OFF_BASE_ADDR) //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_UART3_CLKSEL_MASK       CALC_REG_MASK(SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart3_START, \
                                        SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart3_END)    //��ʱ��ѡ������
#define CLK_UART3_CLKSEL_SET_VALID  CALC_REG_MASK(SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart3_msk_START , \
                                        SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart3_msk_END)    //��ʱ��ѡ������
#define CLK_UART3_CLKDIV_REG_ADDR   NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_UART3_CLKDIV_MASK       0                   //ʱ�ӷ�Ƶ����
#define CLK_UART3_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

#define PCLK_UART3_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define PCLK_UART3_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart3_pclk_START            //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_uart0��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define PCLK_UART3_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define PCLK_UART3_CLKSEL_MASK       0   //��ʱ��ѡ������
#define PCLK_UART3_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define PCLK_UART3_CLKDIV_REG_ADDR   NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define PCLK_UART3_CLKDIV_MASK       0                   //ʱ�ӷ�Ƶ����
#define PCLK_UART3_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_uart3���������ת���� */

/* clk_uart4���������ת���� */
/* ת����ʱ��clk_uart4��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_UART4_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_UART4_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart4_START            //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_uart4��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_UART4_CLKSEL_REG_ADDR   SOC_SCTRL_SC_CLK_SEL0_ADDR(SCTRL_OFF_BASE_ADDR) //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_UART4_CLKSEL_MASK       CALC_REG_MASK(SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart4_START, \
                                        SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart4_END)    //��ʱ��ѡ������
#define CLK_UART4_CLKSEL_SET_VALID  CALC_REG_MASK(SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart4_msk_START, \
                                        SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart4_msk_END)    //��ʱ��ѡ������
#define CLK_UART4_CLKDIV_REG_ADDR   NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_UART4_CLKDIV_MASK       0                   //ʱ�ӷ�Ƶ����
#define CLK_UART4_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

#define PCLK_UART4_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define PCLK_UART4_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart4_pclk_START            //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_uart0��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define PCLK_UART4_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define PCLK_UART4_CLKSEL_MASK       0   //��ʱ��ѡ������
#define PCLK_UART4_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define PCLK_UART4_CLKDIV_REG_ADDR   NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define PCLK_UART4_CLKDIV_MASK       0                   //ʱ�ӷ�Ƶ����
#define PCLK_UART4_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_uart4���������ת���� */

/* clk_uart5���������ת���� */
/* ת����ʱ��clk_uart5��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_UART5_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_UART5_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart5_START            //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_uart5��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_UART5_CLKSEL_REG_ADDR   SOC_SCTRL_SC_CLK_SEL0_ADDR(SCTRL_OFF_BASE_ADDR) //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_UART5_CLKSEL_MASK       CALC_REG_MASK(SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart5_START, \
                                        SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart5_END)    //��ʱ��ѡ������
#define CLK_UART5_CLKSEL_SET_VALID  CALC_REG_MASK(SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart5_msk_START, \
                                        SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart5_msk_END)    //��ʱ��ѡ������
#define CLK_UART5_CLKDIV_REG_ADDR   NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_UART5_CLKDIV_MASK       0                   //ʱ�ӷ�Ƶ����
#define CLK_UART5_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

#define PCLK_UART5_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define PCLK_UART5_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart5_pclk_START            //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_uart0��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define PCLK_UART5_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define PCLK_UART5_CLKSEL_MASK       0   //��ʱ��ѡ������
#define PCLK_UART5_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define PCLK_UART5_CLKDIV_REG_ADDR   NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define PCLK_UART5_CLKDIV_MASK       0                   //ʱ�ӷ�Ƶ����
#define PCLK_UART5_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_uart5���������ת���� */

/* clk_uart6���������ת���� */
/* ת����ʱ��clk_uart6��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_UART6_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_UART6_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart6_START            //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_uart6��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_UART6_CLKSEL_REG_ADDR   SOC_SCTRL_SC_CLK_SEL0_ADDR(SCTRL_OFF_BASE_ADDR) //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_UART6_CLKSEL_MASK       CALC_REG_MASK(SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart6_START, \
                                        SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart6_END)    //��ʱ��ѡ������
#define CLK_UART6_CLKSEL_SET_VALID  CALC_REG_MASK(SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart6_msk_START, \
                                        SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart6_msk_END)    //��ʱ��ѡ������
#define CLK_UART6_CLKDIV_REG_ADDR   NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_UART6_CLKDIV_MASK       0                   //ʱ�ӷ�Ƶ����
#define CLK_UART6_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

#define PCLK_UART6_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define PCLK_UART6_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart6_pclk_START            //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_uart0��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define PCLK_UART6_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define PCLK_UART6_CLKSEL_MASK       0   //��ʱ��ѡ������
#define PCLK_UART6_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define PCLK_UART6_CLKDIV_REG_ADDR   NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define PCLK_UART6_CLKDIV_MASK       0                   //ʱ�ӷ�Ƶ����
#define PCLK_UART6_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_uart6���������ת���� */

/* hclk_nandc���������ת���� */
/* ת����ʱ��hclk_nandc��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define HCLK_NANDC_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN3_ADDR(SCTRL_OFF_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define HCLK_NANDC_ENABLE_BIT_OFFSET   SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_hclk_nandc_START  /* ʱ��ʹ��λƫ�� */

/* hclk_mmc0���������ת���� */
/* ת����ʱ��hclk_mmc0��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define HCLK_MMC0_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN3_ADDR(SCTRL_OFF_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define HCLK_MMC0_ENABLE_BIT_OFFSET   SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc0_bus_START /* ʱ��ʹ��λƫ�� */

/* hclk_mmc1���������ת���� */
/* ת����ʱ��hclk_mmc1��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define HCLK_MMC1_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN3_ADDR(SCTRL_OFF_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define HCLK_MMC1_ENABLE_BIT_OFFSET   SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc1_bus_START  /* ʱ��ʹ��λƫ�� */

/* hclk_mmc2���������ת���� */
/* ת����ʱ��hclk_mmc2��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define HCLK_MMC2_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN3_ADDR(SCTRL_OFF_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define HCLK_MMC2_ENABLE_BIT_OFFSET   SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc2_bus_START  /* ʱ��ʹ��λƫ�� */

/* clk_dsppll_mmc0_gated���������ת���� */
/* ת����ʱ��clk_dsppll_mmc0_gated��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_DSPPLL_MMC0_GATED_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_DSPPLL_MMC0_GATED_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_dsppll_mmc0_gated_START           //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_dsppll_mmc0_gated��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_DSPPLL_MMC0_GATED_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_DSPPLL_MMC0_GATED_CLKSEL_MASK       0   //��ʱ��ѡ������
#define CLK_DSPPLL_MMC0_GATED_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_DSPPLL_MMC0_GATED_CLKDIV_REG_ADDR    SOC_SCTRL_SC_CLKCFG8BIT0_ADDR(SCTRL_OFF_BASE_ADDR)     //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_DSPPLL_MMC0_GATED_CLKDIV_MASK        CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_value0_START, \
                                                        SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_value0_END)                  //ʱ�ӷ�Ƶ����
#define CLK_DSPPLL_MMC0_GATED_CLKDIV_SET_VALID   SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_vld0_START      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_dsppll_mmc0_gated���������ת���� */

/* clk_dsppll_mmc1_gated���������ת���� */
/* ת����ʱ��clk_dsppll_mmc1_gated��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_DSPPLL_MMC1_GATED_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_DSPPLL_MMC1_GATED_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_dsppll_mmc1_gated_START          //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_dsppll_mmc1_gated��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_DSPPLL_MMC1_GATED_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_DSPPLL_MMC1_GATED_CLKSEL_MASK       0   //��ʱ��ѡ������
#define CLK_DSPPLL_MMC1_GATED_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_DSPPLL_MMC1_GATED_CLKDIV_REG_ADDR    SOC_SCTRL_SC_CLKCFG8BIT0_ADDR(SCTRL_OFF_BASE_ADDR)    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_DSPPLL_MMC1_GATED_CLKDIV_MASK        CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_value1_START, \
                                                        SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_value1_END)                  //ʱ�ӷ�Ƶ����
#define CLK_DSPPLL_MMC1_GATED_CLKDIV_SET_VALID   SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_vld1_START       //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_dsppll_mmc1_gated���������ת���� */

/* clk_dsppll_mmc2_gated���������ת���� */
/* ת����ʱ��clk_dsppll_mmc2_gated��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_DSPPLL_MMC2_GATED_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)     //ʹ�ܼĴ�����ַת�����
#define CLK_DSPPLL_MMC2_GATED_ENABLE_BIT_OFFSET    SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_dsppll_mmc2_gated_START           //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_dsppll_mmc2_gated��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_DSPPLL_MMC2_GATED_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_DSPPLL_MMC2_GATED_CLKSEL_MASK       0   //��ʱ��ѡ������
#define CLK_DSPPLL_MMC2_GATED_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_DSPPLL_MMC2_GATED_CLKDIV_REG_ADDR    SOC_SCTRL_SC_CLKCFG8BIT0_ADDR(SCTRL_OFF_BASE_ADDR)    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_DSPPLL_MMC2_GATED_CLKDIV_MASK        CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_value2_START, \
                                                        SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_value2_END)                  //ʱ�ӷ�Ƶ����
#define CLK_DSPPLL_MMC2_GATED_CLKDIV_SET_VALID   SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_vld2_START      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_dsppll_mmc2_gated���������ת���� */

/* clk_mmc0high���������ת���� */
/* ת����ʱ��clk_mmc0high��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_MMC0HIGH_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN3_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_MMC0HIGH_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc0high_START         //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_mmc0low��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_MMC0HIGH_CLKSEL_REG_ADDR    NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_MMC0HIGH_CLKSEL_MASK        0   //��ʱ��ѡ������
#define CLK_MMC0HIGH_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_MMC0HIGH_CLKDIV_REG_ADDR       SOC_SCTRL_SC_CLKCFG8BIT0_ADDR(SCTRL_OFF_BASE_ADDR)  //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_MMC0HIGH_CLKDIV_MASK          CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_value0_START, \
                                                        SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_value0_END)                  //ʱ�ӷ�Ƶ����
#define CLK_MMC0HIGH_CLKDIV_SET_VALID  SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_vld0_START       //ʱ�ӷ�Ƶ������Ч��־λ


/* clk_mmc0high���������ת���� */

/* clk_mmc1high���������ת���� */
/* ת����ʱ��clk_mmc1high��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_MMC1HIGH_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN3_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_MMC1HIGH_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc1high_START         //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_mmc1low��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_MMC1HIGH_CLKSEL_REG_ADDR    NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_MMC1HIGH_CLKSEL_MASK        0   //��ʱ��ѡ������
#define CLK_MMC1HIGH_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_MMC1HIGH_CLKDIV_REG_ADDR       SOC_SCTRL_SC_CLKCFG8BIT0_ADDR(SCTRL_OFF_BASE_ADDR)  //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_MMC1HIGH_CLKDIV_MASK           CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_value1_START, \
                                                        SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_value1_END)                  //ʱ�ӷ�Ƶ����
#define CLK_MMC1HIGH_CLKDIV_SET_VALID  SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_vld1_START       //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_mmc1high���������ת���� */

/* clk_mmc2high���������ת���� */
/* ת����ʱ��clk_mmc2high��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_MMC2HIGH_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN3_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_MMC2HIGH_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc2high_START         //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_mmc2low��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_MMC2HIGH_CLKSEL_REG_ADDR    NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_MMC2HIGH_CLKSEL_MASK        0   //��ʱ��ѡ������
#define CLK_MMC2HIGH_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_MMC2HIGH_CLKDIV_REG_ADDR       SOC_SCTRL_SC_CLKCFG8BIT0_ADDR(SCTRL_OFF_BASE_ADDR)   //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_MMC2HIGH_CLKDIV_MASK           CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_value2_START, \
                                                        SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_value2_END)                  //ʱ�ӷ�Ƶ����
#define CLK_MMC2HIGH_CLKDIV_SET_VALID  SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_vld2_START       //ʱ�ӷ�Ƶ������Ч��־λ


/* clk_mmc0low���������ת���� */
/* ת����ʱ��clk_mmc0low��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_MMC0LOW_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN3_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_MMC0LOW_ENABLE_BIT_OFFSET       SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc0low_START          //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_mmc0low��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_MMC0LOW_CLKSEL_REG_ADDR NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_MMC0LOW_CLKSEL_MASK     0   //��ʱ��ѡ������
#define CLK_MMC0LOW_CLKSEL_SET_VALID    CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_MMC0LOW_CLKDIV_REG_ADDR  SOC_SCTRL_SC_CLKCFG8BIT2_ADDR(SCTRL_OFF_BASE_ADDR)     //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_MMC0LOW_CLKDIV_MASK     CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_value0_START, \
                                                        SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_value0_END)                  //ʱ�ӷ�Ƶ����
#define CLK_MMC0LOW_CLKDIV_SET_VALID    SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_vld0_START      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_mmc0low���������ת���� */

/* clk_mmc1low���������ת���� */
/* ת����ʱ��clk_mmc1low��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_MMC1LOW_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN3_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_MMC1LOW_ENABLE_BIT_OFFSET       SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc1low_START          //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_mmc1low��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_MMC1LOW_CLKSEL_REG_ADDR NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_MMC1LOW_CLKSEL_MASK     0   //��ʱ��ѡ������
#define CLK_MMC1LOW_CLKSEL_SET_VALID    CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_MMC1LOW_CLKDIV_REG_ADDR SOC_SCTRL_SC_CLKCFG8BIT2_ADDR(SCTRL_OFF_BASE_ADDR)    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_MMC1LOW_CLKDIV_MASK    CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_value1_START, \
                                                        SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_value1_END)                  //ʱ�ӷ�Ƶ����
#define CLK_MMC1LOW_CLKDIV_SET_VALID    SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_vld1_START      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_mmc1low���������ת���� */

/* clk_mmc2low���������ת���� */
/* ת����ʱ��clk_mmc2low��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_MMC2LOW_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN3_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_MMC2LOW_ENABLE_BIT_OFFSET       SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc2low_START          //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_mmc2low��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_MMC2LOW_CLKSEL_REG_ADDR NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_MMC2LOW_CLKSEL_MASK     0   //��ʱ��ѡ������
#define CLK_MMC2LOW_CLKSEL_SET_VALID    CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_MMC2LOW_CLKDIV_REG_ADDR SOC_SCTRL_SC_CLKCFG8BIT2_ADDR(SCTRL_OFF_BASE_ADDR)    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_MMC2LOW_CLKDIV_MASK     CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_value2_START, \
                                                        SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_value2_END)                  //ʱ�ӷ�Ƶ����
#define CLK_MMC2LOW_CLKDIV_SET_VALID    SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_vld2_START      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_mmc2low���������ת���� */

/* clk_ddrio_div���������ת���� */
/* ת����ʱ��clk_ddrio_div��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_DDRIO_DIV_ENABLE_REG_ADDR       NULL    //ʹ�ܼĴ�����ַת�����
#define CLK_DDRIO_DIV_ENABLE_BIT_OFFSET     0           //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_ddrio_div��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_DDRIO_DIV_CLKSEL_REG_ADDR   SOC_PMCTRL_DDRCLKPROFILE_ADDR(PMCTRL_BASE_ADDR) //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_DDRIO_DIV_CLKSEL_MASK       CALC_REG_MASK(SOC_PMCTRL_DDRCLKPROFILE_ddr_pllsw_prof_START, \
                                                SOC_PMCTRL_DDRCLKPROFILE_ddr_pllsw_prof_END)    //��ʱ��ѡ������
#define CLK_DDRIO_DIV_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_DDRIO_DIV_CLKDIV_REG_ADDR   SOC_PMCTRL_DDRCLKPROFILE_ADDR(PMCTRL_BASE_ADDR) //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_DDRIO_DIV_CLKDIV_MASK       CALC_REG_MASK(SOC_PMCTRL_DDRCLKPROFILE_ddrio_clk_div_prof_START, \
                                                SOC_PMCTRL_DDRCLKPROFILE_ddrio_clk_div_prof_END)                    //ʱ�ӷ�Ƶ����
#define CLK_DDRIO_DIV_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_ddrio_div���������ת���� */

/* clk_ddrio���������ת���� */
/* ת����ʱ��clk_ddrio��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_DDRIO_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN0_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_DDRIO_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN0_periph_clken0_clk_ddrio_START            //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_ddrio��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_DDRIO_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_DDRIO_CLKSEL_MASK       0   //��ʱ��ѡ������
#define CLK_DDRIO_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_DDRIO_CLKDIV_REG_ADDR   NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_DDRIO_CLKDIV_MASK       0                   //ʱ�ӷ�Ƶ����
#define CLK_DDRIO_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_ddrio���������ת���� */

/* clk_ddrc_div���������ת���� */
/* ת����ʱ��clk_ddrc_div��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_DDRC_DIV_ENABLE_REG_ADDR        NULL    //ʹ�ܼĴ�����ַת�����
#define CLK_DDRC_DIV_ENABLE_BIT_OFFSET      0           //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_ddrc_div��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_DDRC_DIV_CLKSEL_REG_ADDR    NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_DDRC_DIV_CLKSEL_MASK        0   //��ʱ��ѡ������
#define CLK_DDRC_DIV_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_DDRC_DIV_CLKDIV_REG_ADDR    SOC_PMCTRL_DDRCLKPROFILE_ADDR(PMCTRL_BASE_ADDR) //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_DDRC_DIV_CLKDIV_MASK        CALC_REG_MASK(SOC_PMCTRL_DDRCLKPROFILE_ddrc_clk_div_prof_START, \
                                                SOC_PMCTRL_DDRCLKPROFILE_ddrc_clk_div_prof_END)                 //ʱ�ӷ�Ƶ����
#define CLK_DDRC_DIV_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_ddrc_div���������ת���� */

/* clk_ddrc���������ת���� */
/* ת����ʱ��clk_ddrc��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_DDRC_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN0_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_DDRC_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN0_periph_clken0_clk_ddrc_START         //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_ddrc��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_DDRC_CLKSEL_REG_ADDR    NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_DDRC_CLKSEL_MASK        0   //��ʱ��ѡ������
#define CLK_DDRC_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_DDRC_CLKDIV_REG_ADDR    NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_DDRC_CLKDIV_MASK        0                   //ʱ�ӷ�Ƶ����
#define CLK_DDRC_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_ddrc���������ת���� */

/* clk_ddrbus_div���������ת���� */
/* ת����ʱ��clk_ddrbus_div��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_DDRBUS_DIV_ENABLE_REG_ADDR      NULL    //ʹ�ܼĴ�����ַת�����
#define CLK_DDRBUS_DIV_ENABLE_BIT_OFFSET    0           //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_ddrbus_div��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_DDRBUS_DIV_CLKSEL_REG_ADDR  NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_DDRBUS_DIV_CLKSEL_MASK      0   //��ʱ��ѡ������
#define CLK_DDRBUS_DIV_CLKSEL_SET_VALID CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_DDRBUS_DIV_CLKDIV_REG_ADDR  SOC_PMCTRL_DDRCLKPROFILE_ADDR(PMCTRL_BASE_ADDR) //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_DDRBUS_DIV_CLKDIV_MASK      CALC_REG_MASK(SOC_PMCTRL_DDRCLKPROFILE_ddrbus_clk_div_prof_START, \
                                                SOC_PMCTRL_DDRCLKPROFILE_ddrbus_clk_div_prof_END)                   //ʱ�ӷ�Ƶ����
#define CLK_DDRBUS_DIV_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_ddrcbus_div���������ת���� */

/* clk_ddrphy���������ת���� */
/* ת����ʱ��clk_ddrphy��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_DDRPHY_ENABLE_REG_ADDR      SOC_SCTRL_SC_PERIPH_CLKEN0_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_DDRPHY_ENABLE_BIT_OFFSET    SOC_SCTRL_SC_PERIPH_CLKEN0_periph_clken0_clk_ddrphy_START           //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_ddrphy��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_DDRPHY_CLKSEL_REG_ADDR  NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_DDRPHY_CLKSEL_MASK      0   //��ʱ��ѡ������
#define CLK_DDRPHY_CLKSEL_SET_VALID CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_DDRPHY_CLKDIV_REG_ADDR  NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_DDRPHY_CLKDIV_MASK      0                   //ʱ�ӷ�Ƶ����
#define CLK_DDRPHY_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_ddrphy���������ת���� */

/* clk_i2c0���������ת���� */
/* ת����ʱ��clk_i2c0��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_I2C0_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_I2C0_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c0_START         //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_i2c0��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_I2C0_CLKSEL_REG_ADDR    NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_I2C0_CLKSEL_MASK        0   //��ʱ��ѡ������
#define CLK_I2C0_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_I2C0_CLKDIV_REG_ADDR    NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_I2C0_CLKDIV_MASK        0                   //ʱ�ӷ�Ƶ����
#define CLK_I2C0_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

#define PCLK_I2C0_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define PCLK_I2C0_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c0_pclk_START         //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_i2c0��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define PCLK_I2C0_CLKSEL_REG_ADDR    NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define PCLK_I2C0_CLKSEL_MASK        0   //��ʱ��ѡ������
#define PCLK_I2C0_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define PCLK_I2C0_CLKDIV_REG_ADDR    NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define PCLK_I2C0_CLKDIV_MASK        0                   //ʱ�ӷ�Ƶ����
#define PCLK_I2C0_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_i2c0���������ת���� */

/* clk_i2c1���������ת���� */
/* ת����ʱ��clk_i2c1��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_I2C1_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_I2C1_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c1_START         //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_i2c1��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_I2C1_CLKSEL_REG_ADDR    NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_I2C1_CLKSEL_MASK        0   //��ʱ��ѡ������
#define CLK_I2C1_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_I2C1_CLKDIV_REG_ADDR    NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_I2C1_CLKDIV_MASK        0                   //ʱ�ӷ�Ƶ����
#define CLK_I2C1_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* ת����ʱ��clk_i2c1��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define PCLK_I2C1_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define PCLK_I2C1_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c1_pclk_START         //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_i2c1��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define PCLK_I2C1_CLKSEL_REG_ADDR    NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define PCLK_I2C1_CLKSEL_MASK        0   //��ʱ��ѡ������
#define PCLK_I2C1_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define PCLK_I2C1_CLKDIV_REG_ADDR    NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define PCLK_I2C1_CLKDIV_MASK        0                   //ʱ�ӷ�Ƶ����
#define PCLK_I2C1_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_i2c1���������ת���� */

/* clk_i2c2���������ת���� */
/* ת����ʱ��clk_i2c2��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_I2C2_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_I2C2_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c2_START         //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_i2c2��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_I2C2_CLKSEL_REG_ADDR    NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_I2C2_CLKSEL_MASK        0   //��ʱ��ѡ������
#define CLK_I2C2_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_I2C2_CLKDIV_REG_ADDR    NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_I2C2_CLKDIV_MASK        0                   //ʱ�ӷ�Ƶ����
#define CLK_I2C2_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* ת����ʱ��clk_i2c2��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define PCLK_I2C2_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define PCLK_I2C2_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c2_pclk_START         //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_i2c2��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define PCLK_I2C2_CLKSEL_REG_ADDR    NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define PCLK_I2C2_CLKSEL_MASK        0   //��ʱ��ѡ������
#define PCLK_I2C2_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define PCLK_I2C2_CLKDIV_REG_ADDR    NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define PCLK_I2C2_CLKDIV_MASK        0                   //ʱ�ӷ�Ƶ����
#define PCLK_I2C2_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_i2c2���������ת���� */

/* clk_i2c3���������ת���� */
/* ת����ʱ��clk_i2c3��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_I2C3_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_I2C3_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c3_START         //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_i2c3��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_I2C3_CLKSEL_REG_ADDR    NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_I2C3_CLKSEL_MASK        0   //��ʱ��ѡ������
#define CLK_I2C3_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_I2C3_CLKDIV_REG_ADDR    NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_I2C3_CLKDIV_MASK        0                   //ʱ�ӷ�Ƶ����
#define CLK_I2C3_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* ת����ʱ��clk_i2c3��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define PCLK_I2C3_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define PCLK_I2C3_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c3_pclk_START         //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_i2c3��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define PCLK_I2C3_CLKSEL_REG_ADDR    NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define PCLK_I2C3_CLKSEL_MASK        0   //��ʱ��ѡ������
#define PCLK_I2C3_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define PCLK_I2C3_CLKDIV_REG_ADDR    NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define PCLK_I2C3_CLKDIV_MASK        0                   //ʱ�ӷ�Ƶ����
#define PCLK_I2C3_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_i2c3���������ת���� */

/* clk_i2c4���������ת���� */
/* ת����ʱ��clk_i2c4��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_I2C4_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_I2C4_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c4_START         //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_i2c4��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_I2C4_CLKSEL_REG_ADDR    NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_I2C4_CLKSEL_MASK        0   //��ʱ��ѡ������
#define CLK_I2C4_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_I2C4_CLKDIV_REG_ADDR    NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_I2C4_CLKDIV_MASK        0                   //ʱ�ӷ�Ƶ����
#define CLK_I2C4_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* ת����ʱ��clk_i2c4��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define PCLK_I2C4_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define PCLK_I2C4_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c4_pclk_START         //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_i2c4��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define PCLK_I2C4_CLKSEL_REG_ADDR    NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define PCLK_I2C4_CLKSEL_MASK        0   //��ʱ��ѡ������
#define PCLK_I2C4_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define PCLK_I2C4_CLKDIV_REG_ADDR    NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define PCLK_I2C4_CLKDIV_MASK        0                   //ʱ�ӷ�Ƶ����
#define PCLK_I2C4_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_i2c4���������ת���� */

/* clk_i2c5���������ת���� */
/* ת����ʱ��clk_i2c5��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_I2C5_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_I2C5_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c5_START         //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_i2c5��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_I2C5_CLKSEL_REG_ADDR    NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_I2C5_CLKSEL_MASK        0   //��ʱ��ѡ������
#define CLK_I2C5_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_I2C5_CLKDIV_REG_ADDR    NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_I2C5_CLKDIV_MASK        0                   //ʱ�ӷ�Ƶ����
#define CLK_I2C5_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* ת����ʱ��clk_i2c5��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define PCLK_I2C5_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define PCLK_I2C5_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c5_pclk_START         //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_i2c5��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define PCLK_I2C5_CLKSEL_REG_ADDR    NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define PCLK_I2C5_CLKSEL_MASK        0   //��ʱ��ѡ������
#define PCLK_I2C5_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define PCLK_I2C5_CLKDIV_REG_ADDR    NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define PCLK_I2C5_CLKDIV_MASK        0                   //ʱ�ӷ�Ƶ����
#define PCLK_I2C5_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_i2c5���������ת���� */

/* clk_pwm0���������ת���� */
/* ת����ʱ��clk_pwm0��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_PWM0_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN2_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_PWM0_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_pwm0_START         //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_pwm0��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_PWM0_CLKSEL_REG_ADDR    SOC_SCTRL_SC_CLK_SEL1_ADDR(SCTRL_OFF_BASE_ADDR) //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_PWM0_CLKSEL_MASK        CALC_REG_MASK(SOC_SCTRL_SC_CLK_SEL1_sel_clk_pwm0_START, \
                                                SOC_SCTRL_SC_CLK_SEL1_sel_clk_pwm0_END) //��ʱ��ѡ������
#define CLK_PWM0_CLKSEL_SET_VALID   CALC_REG_MASK(SOC_SCTRL_SC_CLK_SEL1_sel_clk_pwm0_msk_START, \
                                                SOC_SCTRL_SC_CLK_SEL1_sel_clk_pwm0_msk_END) //��ʱ��ѡ������
#define CLK_PWM0_CLKDIV_REG_ADDR    SOC_SCTRL_SC_CLKCFG8BIT10_ADDR(SCTRL_OFF_BASE_ADDR) //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_PWM0_CLKDIV_MASK        CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT10_clk_8bit_cfg10_value0_START, \
                                                SOC_SCTRL_SC_CLKCFG8BIT10_clk_8bit_cfg10_value0_END)                    //ʱ�ӷ�Ƶ����
#define CLK_PWM0_CLKDIV_SET_VALID   SOC_SCTRL_SC_CLKCFG8BIT10_clk_8bit_cfg10_vld0_START     //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_pwm0���������ת���� */

/* pclk_pwm0���������ת���� */
/* ת����ʱ��pclk_pwm0��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define PCLK_PWM0_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN2_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define PCLK_PWM0_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_pwm0_pclk_START            //ʱ��ʹ��λƫ��

/* ת����ʱ��pclk_pwm0��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define PCLK_PWM0_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define PCLK_PWM0_CLKSEL_MASK       0   //��ʱ��ѡ������
#define PCLK_PWM0_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define PCLK_PWM0_CLKDIV_REG_ADDR   NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define PCLK_PWM0_CLKDIV_MASK       0       //ʱ�ӷ�Ƶ����
#define PCLK_PWM0_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* pclk_pwm0���������ת���� */

/* clk_pwm1���������ת���� */
/* ת����ʱ��clk_pwm1��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_PWM1_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN2_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_PWM1_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_pwm1_START         //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_pwm1��ʱ��ѡ��Ĵ�����ѡ����s���������Ч��־λ */
#define CLK_PWM1_CLKSEL_REG_ADDR    SOC_SCTRL_SC_CLK_SEL1_ADDR(SCTRL_OFF_BASE_ADDR) //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_PWM1_CLKSEL_MASK        CALC_REG_MASK(SOC_SCTRL_SC_CLK_SEL1_sel_clk_pwm1_START, \
                                                SOC_SCTRL_SC_CLK_SEL1_sel_clk_pwm1_END) //��ʱ��ѡ������
#define CLK_PWM1_CLKSEL_SET_VALID   CALC_REG_MASK(SOC_SCTRL_SC_CLK_SEL1_sel_clk_pwm1_msk_START, \
                                                SOC_SCTRL_SC_CLK_SEL1_sel_clk_pwm1_msk_END) //��ʱ��ѡ������
#define CLK_PWM1_CLKDIV_REG_ADDR    SOC_SCTRL_SC_CLKCFG8BIT10_ADDR(SCTRL_OFF_BASE_ADDR) //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_PWM1_CLKDIV_MASK        CALC_REG_MASK(SOC_SCTRL_SC_CLKCFG8BIT10_clk_8bit_cfg10_value1_START, \
                                                SOC_SCTRL_SC_CLKCFG8BIT10_clk_8bit_cfg10_value1_END)                    //ʱ�ӷ�Ƶ����
#define CLK_PWM1_CLKDIV_SET_VALID   SOC_SCTRL_SC_CLKCFG8BIT10_clk_8bit_cfg10_vld1_START     //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_pwm1���������ת���� */

/* pclk_pwm1���������ת���� */
/* ת����ʱ��pclk_pwm1��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define PCLK_PWM1_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN2_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define PCLK_PWM1_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_pwm1_pclk_START            //ʱ��ʹ��λƫ��

/* ת����ʱ��pclk_pwm1��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define PCLK_PWM1_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define PCLK_PWM1_CLKSEL_MASK       0   //��ʱ��ѡ������
#define PCLK_PWM1_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define PCLK_PWM1_CLKDIV_REG_ADDR   NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define PCLK_PWM1_CLKDIV_MASK       0       //ʱ�ӷ�Ƶ����
#define PCLK_PWM1_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* pclk_pwm1���������ת���� */

/* clk_spi0���������ת���� */
/* ת����ʱ��clk_spi0��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_SPI0_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)  //ʹ�ܼĴ�����ַת�����
#define CLK_SPI0_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_spi0_START //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_spi0��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_SPI0_CLKSEL_REG_ADDR    NULL   //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_SPI0_CLKSEL_MASK        0 //��ʱ��ѡ������
#define CLK_SPI0_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_SPI0_CLKDIV_REG_ADDR    NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_SPI0_CLKDIV_MASK        0                   //ʱ�ӷ�Ƶ����
#define CLK_SPI0_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

#define PCLK_SPI0_ENABLE_REG_ADDR       SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)  //ʹ�ܼĴ�����ַת�����
#define PCLK_SPI0_ENABLE_BIT_OFFSET     SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_spi0_pclk_START //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_spi0��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define PCLK_SPI0_CLKSEL_REG_ADDR    NULL   //��ʱ��ѡ��Ĵ�����ַת�����
#define PCLK_SPI0_CLKSEL_MASK        0 //��ʱ��ѡ������
#define PCLK_SPI0_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define PCLK_SPI0_CLKDIV_REG_ADDR    NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define PCLK_SPI0_CLKDIV_MASK        0                   //ʱ�ӷ�Ƶ����
#define PCLK_SPI0_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_spi0���������ת���� */

/* clk_spi1���������ת���� */
/* ת����ʱ��clk_spi1��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_SPI1_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define CLK_SPI1_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_spi1_START         //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_spi1��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_SPI1_CLKSEL_REG_ADDR    NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_SPI1_CLKSEL_MASK        0   //��ʱ��ѡ������
#define CLK_SPI1_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_SPI1_CLKDIV_REG_ADDR    NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_SPI1_CLKDIV_MASK        0                   //ʱ�ӷ�Ƶ����
#define CLK_SPI1_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* ת����ʱ��clk_spi1��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define PCLK_SPI1_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    //ʹ�ܼĴ�����ַת�����
#define PCLK_SPI1_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_spi1_pclk_START         //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_spi1��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define PCLK_SPI1_CLKSEL_REG_ADDR    NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define PCLK_SPI1_CLKSEL_MASK        0   //��ʱ��ѡ������
#define PCLK_SPI1_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define PCLK_SPI1_CLKDIV_REG_ADDR    NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define PCLK_SPI1_CLKDIV_MASK        0                   //ʱ�ӷ�Ƶ����
#define PCLK_SPI1_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_spi1���������ת���� */

/* clk_dsppll_hifi_core_gated���������ת���� */
/* ת����ʱ��clk_dsppll_hifi_core_gated��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_DSPPLL_HIFI_CORE_GATED_ENABLE_REG_ADDR      SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_DSPPLL_HIFI_CORE_GATED_ENABLE_BIT_OFFSET    SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_dsppll_hifi_core_gated_START           //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_dsppll_hifi_core_gated��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_DSPPLL_HIFI_CORE_GATED_CLKSEL_REG_ADDR  NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_DSPPLL_HIFI_CORE_GATED_CLKSEL_MASK      0   //��ʱ��ѡ������
#define CLK_DSPPLL_HIFI_CORE_GATED_CLKSEL_SET_VALID CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_DSPPLL_HIFI_CORE_GATED_CLKDIV_REG_ADDR  NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_DSPPLL_HIFI_CORE_GATED_CLKDIV_MASK      0                   //ʱ�ӷ�Ƶ����
#define CLK_DSPPLL_HIFI_CORE_GATED_CLKDIV_SET_VALID CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_dsppll_hifi_core_gated���������ת���� */

/* clk_hifi_core���������ת���� */
/* ת����ʱ��clk_hifi_core��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_HIFI_CORE_ENABLE_REG_ADDR       NULL    //ʹ�ܼĴ�����ַת�����
#define CLK_HIFI_CORE_ENABLE_BIT_OFFSET     0           //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_hifi_core��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_HIFI_CORE_CLKSEL_REG_ADDR   NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_HIFI_CORE_CLKSEL_MASK       0   //��ʱ��ѡ������
#define CLK_HIFI_CORE_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_HIFI_CORE_CLKDIV_REG_ADDR   NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_HIFI_CORE_CLKDIV_MASK       0                   //ʱ�ӷ�Ƶ����
#define CLK_HIFI_CORE_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_hifi_core���������ת���� */
#define CLK_CSI_APB_MUX_ENABLE_REG_ADDR         SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_CSI_APB_MUX_ENABLE_BIT_OFFSET       SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_csi_apb_mux_START            //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_csi_apb_mux��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_CSI_APB_MUX_CLKSEL_REG_ADDR     NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_CSI_APB_MUX_CLKSEL_MASK         0   //��ʱ��ѡ������
#define CLK_CSI_APB_MUX_CLKSEL_SET_VALID    CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_CSI_APB_MUX_CLKDIV_REG_ADDR     NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_CSI_APB_MUX_CLKDIV_MASK         0                   //ʱ�ӷ�Ƶ����
#define CLK_CSI_APB_MUX_CLKDIV_SET_VALID    CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_csi_apb_mux���������ת���� */

/* clk_csio_cfg���������ת���� */
/* ת����ʱ��clk_csio_cfg��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_CSIO_CFG_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_CSIO_CFG_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_clk_csio_cfg_START           //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_csio_cfg��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_CSIO_CFG_CLKSEL_REG_ADDR        NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_CSIO_CFG_CLKSEL_MASK            0   //��ʱ��ѡ������
#define CLK_CSIO_CFG_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_CSIO_CFG_CLKDIV_REG_ADDR        NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_CSIO_CFG_CLKDIV_MASK            0                   //ʱ�ӷ�Ƶ����
#define CLK_CSIO_CFG_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_csio_cfg���������ת���� */

/* csi1_cfg_clk���������ת���� */
/* ת����ʱ��csi1_cfg_clk��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CSI1_CFG_CLK_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CSI1_CFG_CLK_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_csi1_cfg_clk_START           //ʱ��ʹ��λƫ��

/* ת����ʱ��csi1_cfg_clk��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CSI1_CFG_CLK_CLKSEL_REG_ADDR        NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CSI1_CFG_CLK_CLKSEL_MASK            0   //��ʱ��ѡ������
#define CSI1_CFG_CLK_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CSI1_CFG_CLK_CLKDIV_REG_ADDR        NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CSI1_CFG_CLK_CLKDIV_MASK            0                   //ʱ�ӷ�Ƶ����
#define CSI1_CFG_CLK_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* csi1_cfg_clk���������ת���� */

/* csi2_cfg_clk���������ת���� */
/* ת����ʱ��csi2_cfg_clk��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CSI2_CFG_CLK_ENABLE_REG_ADDR        SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(SCTRL_OFF_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CSI2_CFG_CLK_ENABLE_BIT_OFFSET      SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_csi2_cfg_clk_START           //ʱ��ʹ��λƫ��

/* ת����ʱ��csi2_cfg_clk��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CSI2_CFG_CLK_CLKSEL_REG_ADDR        NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CSI2_CFG_CLK_CLKSEL_MASK            0   //��ʱ��ѡ������
#define CSI2_CFG_CLK_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CSI2_CFG_CLK_CLKDIV_REG_ADDR        NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CSI2_CFG_CLK_CLKDIV_MASK            0                   //ʱ�ӷ�Ƶ����
#define CSI2_CFG_CLK_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* csi2_cfg_clk���������ת���� */

/* clk_pmussi���������ת���� */
/* ת����ʱ��clk_pmussi��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_PMUSSI_ENABLE_REG_ADDR        SOC_AO_SCTRL_SC_PERIPH_CLKEN5_ADDR(SCTRL_ON_BASE_ADDR)   //ʹ�ܼĴ�����ַת�����
#define CLK_PMUSSI_ENABLE_BIT_OFFSET      SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_pmussi_START           //ʱ��ʹ��λƫ��

/* ת����ʱ��clk_pmussi��ʱ��ѡ��Ĵ�����ѡ�������������Ч��־λ */
#define CLK_PMUSSI_CLKSEL_REG_ADDR        NULL    //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_PMUSSI_CLKSEL_MASK            0   //��ʱ��ѡ������
#define CLK_PMUSSI_CLKSEL_SET_VALID   CLKSEL_SET_INVALID      //��ʱ��ѡ����Ч��־λ

#define CLK_PMUSSI_CLKDIV_REG_ADDR        NULL    //ʱ�ӷ�Ƶ�Ĵ�����ַת�����
#define CLK_PMUSSI_CLKDIV_MASK            0                   //ʱ�ӷ�Ƶ����
#define CLK_PMUSSI_CLKDIV_SET_VALID   CLKDIV_SET_INVALID      //ʱ�ӷ�Ƶ������Ч��־λ

/* clk_pmussi���������ת���� */
/* clk_rtc���������ת���� */
/* ת����ʱ��clk_rtc��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_RTC_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define CLK_RTC_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_rtc_START  /* ʱ��ʹ��λƫ�� */

/* clk_watchdog0���������ת���� */
/* ת����ʱ��clk_watchdog0��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_WATCHDOG0_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define CLK_WATCHDOG0_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_watchdog0_START  /* ʱ��ʹ��λƫ�� */

/* pclk_watchdog0���������ת���� */
/* ת����ʱ��clk_watchdog0_pclk��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define PCLK_WATCHDOG0_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define PCLK_WATCHDOG0_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_watchdog0_pclk_START  /* ʱ��ʹ��λƫ�� */

#define HCLK_USBOTG_ON_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN6_ADDR(SCTRL_ON_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define HCLK_USBOTG_ON_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_hclk_usbotg_START  /* ʱ��ʹ��λƫ�� */

#define HCLK_USBOTG_OFF_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN2_ADDR(SCTRL_OFF_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define HCLK_USBOTG_OFF_ENABLE_BIT_OFFSET   SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_usbotg_bus_clk_START  /* ʱ��ʹ��λƫ�� */

#define CLK_USBOTG_OFF_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN2_ADDR(SCTRL_OFF_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define CLK_USBOTG_OFF_ENABLE_BIT_OFFSET   SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_usbotg_work_clk_START  /* ʱ��ʹ��λƫ�� */

#define CLK_PICOPHY_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN6_ADDR(SCTRL_ON_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define CLK_PICOPHY_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_clk_picophy_START  /* ʱ��ʹ��λƫ�� */

#define CLK_PICOPHY_TEST_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN6_ADDR(SCTRL_ON_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define CLK_PICOPHY_TEST_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_clk_picophy_test_START  /* ʱ��ʹ��λƫ�� */

#define CLK_TS_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN2_ADDR(SCTRL_OFF_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define CLK_TS_ENABLE_BIT_OFFSET   SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_ts_clk_START  /* ʱ��ʹ��λƫ�� */

#define HCLK_TS_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN2_ADDR(SCTRL_OFF_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define HCLK_TS_ENABLE_BIT_OFFSET   SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_ts_hclk_START  /* ʱ��ʹ��λƫ�� */

#define CLK_GPS_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(SCTRL_OFF_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define CLK_GPS_ENABLE_BIT_OFFSET   SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_clk_tcxo_gps_START  /* ʱ��ʹ��λƫ�� */

#define CLK_TSENSOR0_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN2_ADDR(SCTRL_OFF_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define CLK_TSENSOR0_ENABLE_BIT_OFFSET   SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_tsensor0_clk_START  /* ʱ��ʹ��λƫ�� */

#define CLK_TSENSOR1_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN2_ADDR(SCTRL_OFF_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define CLK_TSENSOR1_ENABLE_BIT_OFFSET   SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_tsensor1_clk_START  /* ʱ��ʹ��λƫ�� */

/* clk_ap_dmac_axi0���������ת���� */
/* ת����ʱ��clk_ap_dmac_axi0��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_AP_DMAC_AXI0_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN2_ADDR(SCTRL_OFF_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define CLK_AP_DMAC_AXI0_ENABLE_BIT_OFFSET   SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_ap_dmac_axi0_START  /* ʱ��ʹ��λƫ�� */

/* clk_ap_dmac_axi1���������ת���� */
/* ת����ʱ��clk_ap_dmac_axi1��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_AP_DMAC_AXI1_ENABLE_REG_ADDR     SOC_SCTRL_SC_PERIPH_CLKEN2_ADDR(SCTRL_OFF_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define CLK_AP_DMAC_AXI1_ENABLE_BIT_OFFSET   SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_ap_dmac_axi1_START  /* ʱ��ʹ��λƫ�� */

/* pclk_timer0���������ת���� */
/* ת����ʱ��pclk_timer0��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define PCLK_TIMER0_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define PCLK_TIMER0_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer0_pclk_START  /* ʱ��ʹ��λƫ�� */

/* clk_timer0���������ת���� */
/* ת����ʱ��clk_timer0��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_TIMER0_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define CLK_TIMER0_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer0_START  /* ʱ��ʹ��λƫ�� */
#define CLK_TIMER0_CLKSEL_REG_ADDR    SOC_AO_SCTRL_SC_TIMER_EN0_ADDR(SCTRL_ON_BASE_ADDR) //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_TIMER0_CLKSEL_MASK        CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_1acpu_dualtimer0_en0_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_1acpu_dualtimer0_en0_END) //��ʱ��ѡ������
#define CLK_TIMER0_CLKSEL_SET_VALID   CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_1acpu_dualtimer0_en0_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_1acpu_dualtimer0_en0_END) //��ʱ��ѡ������        //��ʱ��ѡ����Ч��־λ

/* pclk_timer1���������ת���� */
/* ת����ʱ��pclk_timer1��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define PCLK_TIMER1_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define PCLK_TIMER1_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer0_pclk_START  /* ʱ��ʹ��λƫ�� */

/* clk_timer1���������ת���� */
/* ת����ʱ��clk_timer1��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_TIMER1_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define CLK_TIMER1_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer0_START  /* ʱ��ʹ��λƫ�� */
#define CLK_TIMER1_CLKSEL_REG_ADDR    SOC_AO_SCTRL_SC_TIMER_EN0_ADDR(SCTRL_ON_BASE_ADDR) //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_TIMER1_CLKSEL_MASK        CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_3acpu_dualtimer0_en1_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_3acpu_dualtimer0_en1_END) //��ʱ��ѡ������
#define CLK_TIMER1_CLKSEL_SET_VALID   CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_3acpu_dualtimer0_en1_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_3acpu_dualtimer0_en1_END) //��ʱ��ѡ������    

/* pclk_timer2���������ת���� */
/* ת����ʱ��pclk_timer2��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define PCLK_TIMER2_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define PCLK_TIMER2_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer1_pclk_START  /* ʱ��ʹ��λƫ�� */

/* clk_timer2���������ת���� */
/* ת����ʱ��clk_timer2��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_TIMER2_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define CLK_TIMER2_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer1_START  /* ʱ��ʹ��λƫ�� */
#define CLK_TIMER2_CLKSEL_REG_ADDR    SOC_AO_SCTRL_SC_TIMER_EN0_ADDR(SCTRL_ON_BASE_ADDR) //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_TIMER2_CLKSEL_MASK        CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_5acpu_dualtimer1_en0_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_5acpu_dualtimer1_en0_END) //��ʱ��ѡ������
#define CLK_TIMER2_CLKSEL_SET_VALID   CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_5acpu_dualtimer1_en0_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_5acpu_dualtimer1_en0_END) //��ʱ��ѡ������ 


/* pclk_timer3���������ת���� */
/* ת����ʱ��pclk_timer3��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define PCLK_TIMER3_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define PCLK_TIMER3_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer1_pclk_START  /* ʱ��ʹ��λƫ�� */

/* clk_timer3���������ת���� */
/* ת����ʱ��clk_timer3��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_TIMER3_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define CLK_TIMER3_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer1_START  /* ʱ��ʹ��λƫ�� */
#define CLK_TIMER3_CLKSEL_REG_ADDR    SOC_AO_SCTRL_SC_TIMER_EN0_ADDR(SCTRL_ON_BASE_ADDR) //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_TIMER3_CLKSEL_MASK        CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_7acpu_dualtimer1_en1_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_7acpu_dualtimer1_en1_END) //��ʱ��ѡ������
#define CLK_TIMER3_CLKSEL_SET_VALID   CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_7acpu_dualtimer1_en1_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_7acpu_dualtimer1_en1_END) //��ʱ��ѡ������ 

/* pclk_timer4���������ת���� */
/* ת����ʱ��pclk_timer4��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define PCLK_TIMER4_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define PCLK_TIMER4_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer2_pclk_START  /* ʱ��ʹ��λƫ�� */

/* clk_timer4���������ת���� */
/* ת����ʱ��clk_timer4��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_TIMER4_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define CLK_TIMER4_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer2_START  /* ʱ��ʹ��λƫ�� */
#define CLK_TIMER4_CLKSEL_REG_ADDR    SOC_AO_SCTRL_SC_TIMER_EN0_ADDR(SCTRL_ON_BASE_ADDR) //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_TIMER4_CLKSEL_MASK        CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_9acpu_dualtimer2_en0_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_9acpu_dualtimer2_en0_END) //��ʱ��ѡ������
#define CLK_TIMER4_CLKSEL_SET_VALID   CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_9acpu_dualtimer2_en0_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_9acpu_dualtimer2_en0_END) //��ʱ��ѡ������

/* pclk_timer5���������ת���� */
/* ת����ʱ��pclk_timer5��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define PCLK_TIMER5_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define PCLK_TIMER5_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer2_pclk_START  /* ʱ��ʹ��λƫ�� */

/* clk_timer5���������ת���� */
/* ת����ʱ��clk_timer5��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_TIMER5_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define CLK_TIMER5_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer2_START  /* ʱ��ʹ��λƫ�� */
#define CLK_TIMER5_CLKSEL_REG_ADDR    SOC_AO_SCTRL_SC_TIMER_EN0_ADDR(SCTRL_ON_BASE_ADDR) //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_TIMER5_CLKSEL_MASK        CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_11acpu_dualtimer2_en1_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_11acpu_dualtimer2_en1_END) //��ʱ��ѡ������
#define CLK_TIMER5_CLKSEL_SET_VALID   CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_11acpu_dualtimer2_en1_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_11acpu_dualtimer2_en1_END) //��ʱ��ѡ������ 

/* pclk_timer6���������ת���� */
/* ת����ʱ��pclk_timer6��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define PCLK_TIMER6_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define PCLK_TIMER6_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer3_pclk_START  /* ʱ��ʹ��λƫ�� */

/* clk_timer6���������ת���� */
/* ת����ʱ��clk_timer6��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_TIMER6_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define CLK_TIMER6_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer3_START  /* ʱ��ʹ��λƫ�� */
#define CLK_TIMER6_CLKSEL_REG_ADDR    SOC_AO_SCTRL_SC_TIMER_EN0_ADDR(SCTRL_ON_BASE_ADDR) //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_TIMER6_CLKSEL_MASK        CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_13acpu_dualtimer3_en0_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_13acpu_dualtimer3_en0_END) //��ʱ��ѡ������
#define CLK_TIMER6_CLKSEL_SET_VALID   CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_13acpu_dualtimer3_en0_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_13acpu_dualtimer3_en0_END) //��ʱ��ѡ������ 


/* pclk_timer7���������ת���� */
/* ת����ʱ��pclk_timer7��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define PCLK_TIMER7_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define PCLK_TIMER7_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer3_pclk_START  /* ʱ��ʹ��λƫ�� */

/* clk_timer7���������ת���� */
/* ת����ʱ��clk_timer7��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_TIMER7_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define CLK_TIMER7_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer3_START  /* ʱ��ʹ��λƫ�� */
#define CLK_TIMER7_CLKSEL_REG_ADDR    SOC_AO_SCTRL_SC_TIMER_EN0_ADDR(SCTRL_ON_BASE_ADDR) //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_TIMER7_CLKSEL_MASK        CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_15acpu_dualtimer3_en1_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_15acpu_dualtimer3_en1_END) //��ʱ��ѡ������
#define CLK_TIMER7_CLKSEL_SET_VALID   CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_15acpu_dualtimer3_en1_START , \
                                                SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_15acpu_dualtimer3_en1_END) //��ʱ��ѡ������

/* pclk_timer8���������ת���� */
/* ת����ʱ��pclk_timer8��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define PCLK_TIMER8_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define PCLK_TIMER8_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer4pclk_START  /* ʱ��ʹ��λƫ�� */

/* clk_timer8���������ת���� */
/* ת����ʱ��clk_timer8��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_TIMER8_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define CLK_TIMER8_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer4_START  /* ʱ��ʹ��λƫ�� */
#define CLK_TIMER8_CLKSEL_REG_ADDR    SOC_AO_SCTRL_SC_TIMER_EN1_ADDR(SCTRL_ON_BASE_ADDR) //��ʱ��ѡ��Ĵ�����ַת�����
#define CLK_TIMER8_CLKSEL_MASK        CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_1acpu_dualtimer4_en0_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_1acpu_dualtimer4_en0_END) //��ʱ��ѡ������
#define CLK_TIMER8_CLKSEL_SET_VALID   CALC_REG_MASK(SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_msk_1acpu_dualtimer4_en0_START, \
                                                SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_msk_1acpu_dualtimer4_en0_END) //��ʱ��ѡ������ 

/* pclk_timer8���������ת���� */
/* ת����ʱ��pclk_timer8��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define PCLK_TIMER9_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define PCLK_TIMER9_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer4pclk_START  /* ʱ��ʹ��λƫ�� */

/* clk_timer8���������ת���� */
/* ת����ʱ��clk_timer8��ʹ�ܼĴ�����״̬�Ĵ����ĵ�ַ��λƫ�� */
#define CLK_TIMER9_ENABLE_REG_ADDR     SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(SCTRL_ON_BASE_ADDR)    /* ʹ�ܼĴ�����ַת����� */
#define CLK_TIMER9_ENABLE_BIT_OFFSET   SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer4_START  /* ʱ��ʹ��λƫ�� */

#define CLK_GPIO0_ENABLE_REG_ADDR       NULL    //��1<C4>��??��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO0_ENABLE_BIT_OFFSET     0           //����<D6><D3>��1<C4><DC>????<D2><C6>

/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio0<B5><C4>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D��<B1><EA>???? */
#define CLK_GPIO0_CLKSEL_REG_ADDR   NULL    //<B8><B8>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO0_CLKSEL_MASK       0   //<B8><B8>����<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO0_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>����<D6><D3>??<D4><F1><D3><D0>D��<B1><EA>????

#define CLK_GPIO0_CLKDIV_REG_ADDR   NULL    //����<D6>����<D6>?��<BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO0_CLKDIV_MASK       0                   //����<D6>����<D6>?��<D1><DA><C2><EB>
#define CLK_GPIO0_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //����<D6>����<D6>?��<C9><E8><D6><C3><D3><D0>D��<B1><EA>????

/* clk_gpio0<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */

/* clk_gpio1<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */
/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio1<B5><C4>��1<C4>��??��<E6><C6><F7><A3><AC>���䨬?<BC>?��<E6><C6><F7><B5>?��<D8>?��<BA><CD>????<D2><C6> */
#define CLK_GPIO1_ENABLE_REG_ADDR       NULL    //��1<C4>��??��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO1_ENABLE_BIT_OFFSET     0           //����<D6><D3>��1<C4><DC>????<D2><C6>

/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio1<B5><C4>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D��<B1><EA>???? */
#define CLK_GPIO1_CLKSEL_REG_ADDR   NULL    //<B8><B8>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO1_CLKSEL_MASK       0   //<B8><B8>����<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO1_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>����<D6><D3>??<D4><F1><D3><D0>D��<B1><EA>????

#define CLK_GPIO1_CLKDIV_REG_ADDR   NULL    //����<D6>����<D6>?��<BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO1_CLKDIV_MASK       0                   //����<D6>����<D6>?��<D1><DA><C2><EB>
#define CLK_GPIO1_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //����<D6>����<D6>?��<C9><E8><D6><C3><D3><D0>D��<B1><EA>????

/* clk_gpio1<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */

/* clk_gpio2<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */
/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio2<B5><C4>��1<C4>��??��<E6><C6><F7><A3><AC>���䨬?<BC>?��<E6><C6><F7><B5>?��<D8>?��<BA><CD>????<D2><C6> */
#define CLK_GPIO2_ENABLE_REG_ADDR       NULL    //��1<C4>��??��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO2_ENABLE_BIT_OFFSET     0           //����<D6><D3>��1<C4><DC>????<D2><C6>

/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio2<B5><C4>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D��<B1><EA>???? */
#define CLK_GPIO2_CLKSEL_REG_ADDR   NULL    //<B8><B8>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO2_CLKSEL_MASK       0   //<B8><B8>����<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO2_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>����<D6><D3>??<D4><F1><D3><D0>D��<B1><EA>????

#define CLK_GPIO2_CLKDIV_REG_ADDR   NULL    //����<D6>����<D6>?��<BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO2_CLKDIV_MASK       0                   //����<D6>����<D6>?��<D1><DA><C2><EB>
#define CLK_GPIO2_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //����<D6>����<D6>?��<C9><E8><D6><C3><D3><D0>D��<B1><EA>????

/* clk_gpio2<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */

/* clk_gpio3<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */

/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio3<B5><C4>��1<C4>��??��<E6><C6><F7><A3><AC>���䨬?<BC>?��<E6><C6><F7><B5>?��<D8>?��<BA><CD>????<D2><C6> */
#define CLK_GPIO3_ENABLE_REG_ADDR       NULL    //��1<C4>��??��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO3_ENABLE_BIT_OFFSET     0           //����<D6><D3>��1<C4><DC>????<D2><C6>
#define CLK_GPIO3_CLKSEL_REG_ADDR   NULL    //<B8><B8>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO3_CLKSEL_MASK       0   //<B8><B8>����<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO3_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>����<D6><D3>??<D4><F1><D3><D0>D��<B1><EA>????

#define CLK_GPIO3_CLKDIV_REG_ADDR   NULL    //����<D6>����<D6>?��<BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO3_CLKDIV_MASK       0                   //����<D6>����<D6>?��<D1><DA><C2><EB>
#define CLK_GPIO3_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //����<D6>����<D6>?��<C9><E8><D6><C3><D3><D0>D��<B1><EA>????

/* clk_gpio3<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */

/* clk_gpio4<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */
/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio4<B5><C4>��1<C4>��??��<E6><C6><F7><A3><AC>���䨬?<BC>?��<E6><C6><F7><B5>?��<D8>?��<BA><CD>????<D2><C6> */
#define CLK_GPIO4_ENABLE_REG_ADDR       NULL    //��1<C4>��??��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO4_ENABLE_BIT_OFFSET     0           //����<D6><D3>��1<C4><DC>????<D2><C6>

/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio4<B5><C4>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D��<B1><EA>???? */
#define CLK_GPIO4_CLKSEL_REG_ADDR   NULL    //<B8><B8>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO4_CLKSEL_MASK       0   //<B8><B8>����<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO4_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>����<D6><D3>??<D4><F1><D3><D0>D��<B1><EA>????

#define CLK_GPIO4_CLKDIV_REG_ADDR   NULL    //����<D6>����<D6>?��<BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO4_CLKDIV_MASK       0                   //����<D6>����<D6>?��<D1><DA><C2><EB>
#define CLK_GPIO4_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //����<D6>����<D6>?��<C9><E8><D6><C3><D3><D0>D��<B1><EA>????

/* clk_gpio4<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */

/* clk_gpio5<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */
/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio5<B5><C4>��1<C4>��??��<E6><C6><F7><A3><AC>���䨬?<BC>?��<E6><C6><F7><B5>?��<D8>?��<BA><CD>????<D2><C6> */
#define CLK_GPIO5_ENABLE_REG_ADDR       NULL    //��1<C4>��??��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO5_ENABLE_BIT_OFFSET     0           //����<D6><D3>��1<C4><DC>????<D2><C6>

/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio5<B5><C4>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D��<B1><EA>???? */
#define CLK_GPIO5_CLKSEL_REG_ADDR   NULL    //<B8><B8>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO5_CLKSEL_MASK       0   //<B8><B8>����<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO5_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>����<D6><D3>??<D4><F1><D3><D0>D��<B1><EA>????

#define CLK_GPIO5_CLKDIV_REG_ADDR   NULL    //����<D6>����<D6>?��<BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO5_CLKDIV_MASK       0                   //����<D6>����<D6>?��<D1><DA><C2><EB>
#define CLK_GPIO5_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //����<D6>����<D6>?��<C9><E8><D6><C3><D3><D0>D��<B1><EA>????

/* clk_gpio5<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */
#define CLK_GPIO6_ENABLE_REG_ADDR       NULL    //��1<C4>��??��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO6_ENABLE_BIT_OFFSET     0           //����<D6><D3>��1<C4><DC>????<D2><C6>

/* clk_gpio6<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */
/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio6<B5><C4>��1<C4>��??��<E6><C6><F7><A3><AC>���䨬?<BC>?��<E6><C6><F7><B5>?��<D8>?��<BA><CD>????<D2><C6> */
#define CLK_GPIO6_ENABLE_REG_ADDR       NULL    //��1<C4>��??��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO6_ENABLE_BIT_OFFSET     0           //����<D6><D3>��1<C4><DC>????<D2><C6>

/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio6<B5><C4>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D��<B1><EA>???? */
#define CLK_GPIO6_CLKSEL_REG_ADDR   NULL    //<B8><B8>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO6_CLKSEL_MASK       0   //<B8><B8>����<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO6_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>����<D6><D3>??<D4><F1><D3><D0>D��<B1><EA>????
/* clk_gpio6<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */
#define CLK_GPIO6_CLKDIV_REG_ADDR   NULL    //����<D6>����<D6>?��<BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO6_CLKDIV_MASK       0                   //����<D6>����<D6>?��<D1><DA><C2><EB>
#define CLK_GPIO6_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //����<D6>����<D6>?��<C9><E8><D6><C3><D3><D0>D��<B1><EA>????

/* clk_gpio7<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */
/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio7<B5><C4>��1<C4>��??��<E6><C6><F7><A3><AC>���䨬?<BC>?��<E6><C6><F7><B5>?��<D8>?��<BA><CD>????<D2><C6> */
#define CLK_GPIO7_ENABLE_REG_ADDR       NULL    //��1<C4>��??��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO7_ENABLE_BIT_OFFSET     0           //����<D6><D3>��1<C4><DC>????<D2><C6>

/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio7<B5><C4>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D��<B1><EA>???? */
#define CLK_GPIO7_CLKSEL_REG_ADDR   NULL    //<B8><B8>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO7_CLKSEL_MASK       0   //<B8><B8>����<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO7_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>����<D6><D3>??<D4><F1><D3><D0>D��<B1><EA>????

#define CLK_GPIO7_CLKDIV_REG_ADDR   NULL    //����<D6>����<D6>?��<BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO7_CLKDIV_MASK       0                   //����<D6>����<D6>?��<D1><DA><C2><EB>
#define CLK_GPIO7_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //����<D6>����<D6>?��<C9><E8><D6><C3><D3><D0>D��<B1><EA>????

/* clk_gpio7<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */

/* clk_gpio8<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */
/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio8<B5><C4>��1<C4>��??��<E6><C6><F7><A3><AC>���䨬?<BC>?��<E6><C6><F7><B5>?��<D8>?��<BA><CD>????<D2><C6> */
#define CLK_GPIO8_ENABLE_REG_ADDR       NULL    //��1<C4>��??��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO8_ENABLE_BIT_OFFSET     0           //����<D6><D3>��1<C4><DC>????<D2><C6>

/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio8<B5><C4>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D��<B1><EA>???? */
#define CLK_GPIO8_CLKSEL_REG_ADDR   NULL    //<B8><B8>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO8_CLKSEL_MASK       0   //<B8><B8>����<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO8_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>����<D6><D3>??<D4><F1><D3><D0>D��<B1><EA>????

#define CLK_GPIO8_CLKDIV_REG_ADDR   NULL    //����<D6>����<D6>?��<BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO8_CLKDIV_MASK       0                   //����<D6>����<D6>?��<D1><DA><C2><EB>
#define CLK_GPIO8_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //����<D6>����<D6>?��<C9><E8><D6><C3><D3><D0>D��<B1><EA>????

/* clk_gpio8<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */

/* clk_gpio9<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */
/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio9<B5><C4>��1<C4>��??��<E6><C6><F7><A3><AC>���䨬?<BC>?��<E6><C6><F7><B5>?��<D8>?��<BA><CD>????<D2><C6> */
#define CLK_GPIO9_ENABLE_REG_ADDR       NULL    //��1<C4>��??��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO9_ENABLE_BIT_OFFSET     0           //����<D6><D3>��1<C4><DC>????<D2><C6>

/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio9<B5><C4>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D��<B1><EA>???? */
#define CLK_GPIO9_CLKSEL_REG_ADDR   NULL    //<B8><B8>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO9_CLKSEL_MASK       0   //<B8><B8>����<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO9_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>����<D6><D3>??<D4><F1><D3><D0>D��<B1><EA>????

#define CLK_GPIO9_CLKDIV_REG_ADDR   NULL    //����<D6>����<D6>?��<BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO9_CLKDIV_MASK       0                   //����<D6>����<D6>?��<D1><DA><C2><EB>
#define CLK_GPIO9_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //����<D6>����<D6>?��<C9><E8><D6><C3><D3><D0>D��<B1><EA>????

/* clk_gpio9<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */
#define CLK_GPIO10_ENABLE_REG_ADDR       NULL    //��1<C4>��??��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO10_ENABLE_BIT_OFFSET     0           //����<D6><D3>��1<C4><DC>????<D2><C6>

/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio10<B5><C4>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D��<B1><EA>???? */
#define CLK_GPIO10_CLKSEL_REG_ADDR   NULL    //<B8><B8>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO10_CLKSEL_MASK       0   //<B8><B8>����<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO10_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>����<D6><D3>??<D4><F1><D3><D0>D��<B1><EA>????
#define CLK_GPIO10_CLKDIV_REG_ADDR   NULL    //����<D6>����<D6>?��<BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO10_CLKDIV_MASK       0                   //����<D6>����<D6>?��<D1><DA><C2><EB>
#define CLK_GPIO10_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //����<D6>����<D6>?��<C9><E8><D6><C3><D3><D0>D��<B1><EA>????

/* clk_gpio10<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */

/* clk_gpio11<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */
/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio11<B5><C4>��1<C4>��??��<E6><C6><F7><A3><AC>���䨬?<BC>?��<E6><C6><F7><B5>?��<D8>?��<BA><CD>????<D2><C6> */
#define CLK_GPIO11_ENABLE_REG_ADDR       NULL    //��1<C4>��??��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO11_ENABLE_BIT_OFFSET     0           //����<D6><D3>��1<C4><DC>????<D2><C6>

/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio11<B5><C4>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D��<B1><EA>???? */
#define CLK_GPIO11_CLKSEL_REG_ADDR   NULL    //<B8><B8>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO11_CLKSEL_MASK       0   //<B8><B8>����<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO11_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>����<D6><D3>??<D4><F1><D3><D0>D��<B1><EA>????

#define CLK_GPIO11_CLKDIV_REG_ADDR   NULL    //����<D6>����<D6>?��<BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO11_CLKDIV_MASK       0                   //����<D6>����<D6>?��<D1><DA><C2><EB>
#define CLK_GPIO11_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //����<D6>����<D6>?��<C9><E8><D6><C3><D3><D0>D��<B1><EA>????

/* clk_gpio11<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */

/* clk_gpio12<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */
/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio12<B5><C4>��1<C4>��??��<E6><C6><F7><A3><AC>���䨬?<BC>?��<E6><C6><F7><B5>?��<D8>?��<BA><CD>????<D2><C6> */
#define CLK_GPIO12_ENABLE_REG_ADDR       NULL    //��1<C4>��??��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO12_ENABLE_BIT_OFFSET     0           //����<D6><D3>��1<C4><DC>????<D2><C6>

/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio12<B5><C4>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D��<B1><EA>???? */
#define CLK_GPIO12_CLKSEL_REG_ADDR   NULL    //<B8><B8>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO12_CLKSEL_MASK       0   //<B8><B8>����<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO12_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>����<D6><D3>??<D4><F1><D3><D0>D��<B1><EA>????

#define CLK_GPIO12_CLKDIV_REG_ADDR   NULL    //����<D6>����<D6>?��<BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO12_CLKDIV_MASK       0                   //����<D6>����<D6>?��<D1><DA><C2><EB>
#define CLK_GPIO12_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //����<D6>����<D6>?��<C9><E8><D6><C3><D3><D0>D��<B1><EA>????

/* clk_gpio12<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */
#define CLK_GPIO13_ENABLE_REG_ADDR       NULL    //��1<C4>��??��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO13_ENABLE_BIT_OFFSET     0           //����<D6><D3>��1<C4><DC>????<D2><C6>

/* clk_gpio13<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */
/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio13<B5><C4>��1<C4>��??��<E6><C6><F7><A3><AC>���䨬?<BC>?��<E6><C6><F7><B5>?��<D8>?��<BA><CD>????<D2><C6> */
#define CLK_GPIO13_CLKSEL_REG_ADDR   NULL    //<B8><B8>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO13_CLKSEL_MASK       0   //<B8><B8>����<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO13_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>����<D6><D3>??<D4><F1><D3><D0>D��<B1><EA>????

#define CLK_GPIO13_CLKDIV_REG_ADDR   NULL    //����<D6>����<D6>?��<BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO13_CLKDIV_MASK       0                   //����<D6>����<D6>?��<D1><DA><C2><EB>
#define CLK_GPIO13_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //����<D6>����<D6>?��<C9><E8><D6><C3><D3><D0>D��<B1><EA>????

/* clk_gpio13<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */

/* clk_gpio14<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */
/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio14<B5><C4>��1<C4>��??��<E6><C6><F7><A3><AC>���䨬?<BC>?��<E6><C6><F7><B5>?��<D8>?��<BA><CD>????<D2><C6> */
#define CLK_GPIO14_ENABLE_REG_ADDR       NULL    //��1<C4>��??��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO14_ENABLE_BIT_OFFSET     0           //����<D6><D3>��1<C4><DC>????<D2><C6>

/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio14<B5><C4>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D��<B1><EA>???? */
#define CLK_GPIO14_CLKSEL_REG_ADDR   NULL    //<B8><B8>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO14_CLKSEL_MASK       0   //<B8><B8>����<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO14_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>����<D6><D3>??<D4><F1><D3><D0>D��<B1><EA>????

#define CLK_GPIO14_CLKDIV_REG_ADDR   NULL    //����<D6>����<D6>?��<BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO14_CLKDIV_MASK       0                   //����<D6>����<D6>?��<D1><DA><C2><EB>
#define CLK_GPIO14_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //����<D6>����<D6>?��<C9><E8><D6><C3><D3><D0>D��<B1><EA>????

/* clk_gpio14<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */

/* clk_gpio15<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */
/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio15<B5><C4>��1<C4>��??��<E6><C6><F7><A3><AC>���䨬?<BC>?��<E6><C6><F7><B5>?��<D8>?��<BA><CD>????<D2><C6> */
#define CLK_GPIO15_ENABLE_REG_ADDR       NULL    //��1<C4>��??��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO15_ENABLE_BIT_OFFSET     0           //����<D6><D3>��1<C4><DC>????<D2><C6>

/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio15<B5><C4>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D��<B1><EA>???? */
#define CLK_GPIO15_CLKSEL_REG_ADDR   NULL    //<B8><B8>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO15_CLKSEL_MASK       0   //<B8><B8>����<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO15_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>����<D6><D3>??<D4><F1><D3><D0>D��<B1><EA>????

#define CLK_GPIO15_CLKDIV_REG_ADDR   NULL    //����<D6>����<D6>?��<BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO15_CLKDIV_MASK       0                   //����<D6>����<D6>?��<D1><DA><C2><EB>
#define CLK_GPIO15_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //����<D6>����<D6>?��<C9><E8><D6><C3><D3><D0>D��<B1><EA>????

/* clk_gpio15<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */

/* clk_gpio16<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */
/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio16<B5><C4>��1<C4>��??��<E6><C6><F7><A3><AC>���䨬?<BC>?��<E6><C6><F7><B5>?��<D8>?��<BA><CD>????<D2><C6> */
#define CLK_GPIO16_ENABLE_REG_ADDR       NULL    //��1<C4>��??��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO16_ENABLE_BIT_OFFSET     0           //����<D6><D3>��1<C4><DC>????<D2><C6>

/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio16<B5><C4>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D��<B1><EA>???? */
#define CLK_GPIO16_CLKSEL_REG_ADDR   NULL    //<B8><B8>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO16_CLKSEL_MASK       0   //<B8><B8>����<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO16_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>����<D6><D3>??<D4><F1><D3><D0>D��<B1><EA>????

#define CLK_GPIO16_CLKDIV_REG_ADDR   NULL    //����<D6>����<D6>?��<BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO16_CLKDIV_MASK       0                   //����<D6>����<D6>?��<D1><DA><C2><EB>
#define CLK_GPIO16_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //����<D6>����<D6>?��<C9><E8><D6><C3><D3><D0>D��<B1><EA>????

/* clk_gpio16<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */

/* clk_gpio17<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */
/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio17<B5><C4>��1<C4>��??��<E6><C6><F7><A3><AC>���䨬?<BC>?��<E6><C6><F7><B5>?��<D8>?��<BA><CD>????<D2><C6> */
#define CLK_GPIO17_ENABLE_REG_ADDR       NULL    //��1<C4>��??��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO17_ENABLE_BIT_OFFSET     0           //����<D6><D3>��1<C4><DC>????<D2><C6>

/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio17<B5><C4>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D��<B1><EA>???? */
#define CLK_GPIO17_CLKSEL_REG_ADDR   NULL    //<B8><B8>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO17_CLKSEL_MASK       0   //<B8><B8>����<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO17_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>����<D6><D3>??<D4><F1><D3><D0>D��<B1><EA>????

#define CLK_GPIO17_CLKDIV_REG_ADDR   NULL    //����<D6>����<D6>?��<BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO17_CLKDIV_MASK       0                   //����<D6>����<D6>?��<D1><DA><C2><EB>
#define CLK_GPIO17_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //����<D6>����<D6>?��<C9><E8><D6><C3><D3><D0>D��<B1><EA>????

/* clk_gpio17<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */

/* clk_gpio18<B2><D9><D7><F7><BA><EA><CF><E0><B9><D8>��a<B6><A8><D2><E5> */
/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio18<B5><C4>��1<C4>��??��<E6><C6><F7><A3><AC>���䨬?<BC>?��<E6><C6><F7><B5>?��<D8>?��<BA><CD>????<D2><C6> */
#define CLK_GPIO18_ENABLE_REG_ADDR       NULL    //��1<C4>��??��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO18_ENABLE_BIT_OFFSET     0           //����<D6><D3>��1<C4><DC>????<D2><C6>

/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio18<B5><C4>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D��<B1><EA>???? */
#define CLK_GPIO18_CLKSEL_REG_ADDR   NULL    //<B8><B8>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO18_CLKSEL_MASK       0   //<B8><B8>����<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO18_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>����<D6><D3>??<D4><F1><D3><D0>D��<B1><EA> */
#define CLK_GPIO18_CLKDIV_REG_ADDR   NULL    //����<D6>����<D6>?��<BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO18_CLKDIV_MASK       0                   //����<D6>����<D6>?��<D1><DA><C2><EB>
#define CLK_GPIO18_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //����<D6>����<D6>?��<C9><E8><D6><C3><D3><D0>D��<B1><EA>????
#define CLK_GPIO19_ENABLE_REG_ADDR       NULL    //��1<C4>��??��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO19_ENABLE_BIT_OFFSET     0           //����<D6><D3>��1<C4><DC>????<D2><C6>

/* ��a<B6><A8><D2><E5>����<D6><D3>clk_gpio18<B5><C4>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><A1><A2>??<D4><F1><D1><DA><C2><EB><BA><CD><C9><E8><D6><C3><D3><D0>D��<B1><EA>???? */
#define CLK_GPIO19_CLKSEL_REG_ADDR   NULL    //<B8><B8>����<D6><D3>??<D4><F1><BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO19_CLKSEL_MASK       0   //<B8><B8>����<D6><D3>??<D4><F1><D1><DA><C2><EB>
#define CLK_GPIO19_CLKSEL_SET_VALID  CLKSEL_SET_INVALID      //<B8><B8>����<D6><D3>??<D4><F1><D3><D0>D��<B1><EA> */
#define CLK_GPIO19_CLKDIV_REG_ADDR   NULL    //����<D6>����<D6>?��<BC>?��<E6><C6><F7><B5><D8>?����a<B6><A8><D2><E5><BA><EA>
#define CLK_GPIO19_CLKDIV_MASK       0                   //����<D6>����<D6>?��<D1><DA><C2><EB>
#define CLK_GPIO19_CLKDIV_SET_VALID  CLKDIV_SET_INVALID      //����<D6>����<D6>?��<C9><E8><D6><C3><D3><D0>D��<B1><EA>????

