/*************************************************************************
*   ��Ȩ����(C) 2010-2015, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  dsp_balong.h
*
*   ��    �� :  c00326366
*
*   ��    �� :
*
*   �޸ļ�¼ :  2015��5��7��  v1.00  c00326366  ����
*************************************************************************/
#ifndef __DSP_BALONG_H__
#define __DSP_BALONG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <bsp_shared_ddr.h>
#if defined(__OS_VXWORKS__) || defined(__OS_RTOSCK__)
#include <bsp_dpm.h>
#include <mdrv_dsp.h>
#endif

/* #define BSP_BBE_STATE_CHECK */
//#define DSP_LOAD_WITH_EDMA


#define IS_VALID_ADDR(addr) ((addr != 0x0) ? true:false)

#define CBBE_1X_DATA_OFFSET             (624*1024)
#define CBBE_EVDO_DATA_OFFSET           (824*1024)

#define BBE_SECT_LEN_1K                 (1*1024)
#define BBE_SECT_LEN_64K                (64*1024)

typedef enum{
    BBE16_PD_CLK_EN = 0,
    BBE16_PD_CLK_DIS,
    BBE16_PD_SRST_DIS,
    BBE16_PD_SRST_EN,
    BBE16_CORE_SRST_DIS,
    BBE16_DBG_SRST_DIS = 5,
    BBE16_CORE_SRST_EN,
    BBE16_DBG_SRST_EN,
    PD,
    BBE16_RUNSTALL,
    BBE_REFCLK_EN = 10,
    BBE_REFCLK_DIS,
    PLL_LOCK,
    PLL_EN,
    PLL_BP,
    PLL_POSTDIVPD = 15,
    PLL_CLK_GT,
    DIV_MODEM_BBE16,
    SEL_MODEM_BBE16,
    CLKDIVMASKEN,
    DSP0_CORE_CLK_DIS = 20,
    DSP0_DBG_CLK_DIS,
    BBE_CORE_CLK_EN,
    DSP0_DBG_CLK_EN,
    BBE16_MTCMOS_CTRL_EN,
    BBE16_MTCMOS_RDY_STAT = 25,
    BBE16_ISO_CTRL_DIS,
    BBE16_MTCMOS_CTRL_DIS,
    BBE16_ISO_CTRL_EN,
    BBE16_WAITI_EN,
    BBE16_WAITI_DIV = 30,
    BBE16_CORE_CLK_DIV,
    DSP0_FREQMODE,
    DSP0_REFCLK_SW,
    DSP_DTS_REG_BUTT
}DSP_DTS_SYSCTRL;

struct dsp_sysctrl{
    u32 base_addr;
    u32 offset;
    u32 start_bit;
    u32 end_bit;
};

struct dsp_ctrl{
    void *tcm_dtcm_base_addr;//tcm
    u32 lphy_pub_dtcm_size;
    void *tcm_itcm_base_addr;//tcm
    u32 lphy_pub_itcm_size;
    int bbe_ddr_pub_dtcm_addr;//ddr
    int bbe_ddr_pub_itcm_addr;//ddr
};

typedef enum
{
    DSP_PWC_OFF = 0,
    DSP_PWC_ON = 1,
    DSP_PWC_BUTT
}DSP_PWC_STATUS_E;

typedef enum{
    DSP_BASE_ADDR = 0,
    DSP_OFFSET,
    DSP_START_BIT,
    DSP_END_BIT,
    DSP_ADDR_BUTT
}DSP_DTS_SYSCTRL_ADDR;

struct dsp_pwc_ctrl{
    u32 is_pmctrl_in_dpm;
    u32 can_switch_pll;
    u32 can_switch_waiti;
};

#ifdef __cplusplus
}
#endif

#endif

