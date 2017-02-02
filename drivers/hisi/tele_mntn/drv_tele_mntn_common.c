

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "drv_tele_mntn_common.h"
#include  "drv_tele_mntn_platform.h"

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
TELE_MNTN_DATA_SECTION u8 *tele_mntn_sctrl_base = TELE_MNTN_NULL;
#if !defined(CONFIG_TELE_MNTN_CORE_CM3)
TELE_MNTN_DATA_SECTION u8 *tele_mntn_rtc0_base = TELE_MNTN_NULL;
#endif


#if defined (CONFIG_TELE_MNTN_CORE_APP)
TELE_MNTN_DATA_SECTION ACORE_TELE_MNTN_STRU *p_acore_tele_mntn = TELE_MNTN_NULL;
TELE_MNTN_DATA_SECTION LPMCU_TELE_MNTN_STRU *p_lpmcu_tele_mntn = TELE_MNTN_NULL;
#elif defined(CONFIG_TELE_MNTN_CORE_CM3)
TELE_MNTN_DATA_SECTION LPMCU_TELE_MNTN_STRU *p_lpmcu_tele_mntn = (LPMCU_TELE_MNTN_STRU *)LPMCU_STAT_BASE;
#endif

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


s32_t tele_mntn_is_func_on (TELE_MNTN_TYPE_ID type_id)
{
/*lint -e571*/
    u32_t tmp = 0;
    u32_t id = type_id;
    if(!tele_mntn_sctrl_base)
    {
        return TELE_MNTN_ERRO;
    }
    if(id >= 32)
    {
        tmp = TELE_MNTN_READ_REG(SOC_SCTRL_SCBAKDATA15_ADDR(tele_mntn_sctrl_base));
        id -= 32;
    }
    else
    {
        tmp = TELE_MNTN_READ_REG(SOC_SCTRL_SCBAKDATA5_ADDR(tele_mntn_sctrl_base));
    }
    if(tmp & BIT(id))
    {
        return TELE_MNTN_OK;
    }

    return TELE_MNTN_ERRO;
/*lint +e571*/
}

s32_t tele_mntn_common_init (void_t)
{
#if defined(CONFIG_TELE_MNTN_CORE_MODEM)
    tele_mntn_sctrl_base = (u8_t *)TELE_MNTN_AXI_PHY_TO_VIRT(SOC_ACPU_SCTRL_BASE_ADDR, 0x400);
    tele_mntn_rtc0_base = (u8_t *)TELE_MNTN_AXI_PHY_TO_VIRT(SOC_ACPU_RTC0_BASE_ADDR, 0x400);
#elif defined (CONFIG_TELE_MNTN_CORE_APP)
    tele_mntn_sctrl_base = (u8_t *)TELE_MNTN_AXI_PHY_TO_VIRT(SOC_ACPU_SCTRL_BASE_ADDR, 0x400);
    tele_mntn_rtc0_base = (u8_t *)TELE_MNTN_AXI_PHY_TO_VIRT(SOC_ACPU_RTC0_BASE_ADDR, 0x400);
    if(M3_RDR_SYS_CONTEXT_BASE_ADDR)
    {
        p_acore_tele_mntn = (ACORE_TELE_MNTN_STRU*)M3_RDR_SYS_CONTEXT_KERNEL_STAT_ADDR;
        p_lpmcu_tele_mntn = (LPMCU_TELE_MNTN_STRU*)M3_RDR_SYS_CONTEXT_LPMCU_STAT_ADDR;
    }
#elif defined(CONFIG_TELE_MNTN_CORE_CM3)
    tele_mntn_sctrl_base = (u8_t *)TELE_MNTN_AXI_PHY_TO_VIRT(SOC_LPMCU_SCTRL_BASE_ADDR, 0x400);
#endif

    return TELE_MNTN_OK;
}

u64_t tele_mntn_func_sw_get (void_t)
{
    u64_t tmp = 0;
    if(!tele_mntn_sctrl_base)
    {
        return 0;
    }
    tmp = (u64_t)TELE_MNTN_READ_REG(SOC_SCTRL_SCBAKDATA15_ADDR(tele_mntn_sctrl_base));
    tmp = (tmp << 32) | TELE_MNTN_READ_REG(SOC_SCTRL_SCBAKDATA5_ADDR(tele_mntn_sctrl_base));
    return tmp;
}

u64_t tele_mntn_func_sw_set (u64_t sw)
{
    if(!tele_mntn_sctrl_base)
    {
        return 0;
    }
    TELE_MNTN_WRITE_REG((sw >> 32) , SOC_SCTRL_SCBAKDATA15_ADDR(tele_mntn_sctrl_base));
    TELE_MNTN_WRITE_REG((u32_t)(sw), SOC_SCTRL_SCBAKDATA5_ADDR(tele_mntn_sctrl_base));
    return sw;

}

u64_t tele_mntn_func_sw_bit_set (u32_t bit)
{
    u32_t tmp = 0;
    if(!tele_mntn_sctrl_base)
    {
        return 0;
    }
    if(bit >= 32)
    {
        tmp = TELE_MNTN_READ_REG(SOC_SCTRL_SCBAKDATA15_ADDR(tele_mntn_sctrl_base));
        tmp |= BIT(bit-32);
        TELE_MNTN_WRITE_REG(tmp , SOC_SCTRL_SCBAKDATA15_ADDR(tele_mntn_sctrl_base));
    }
    else
    {
        tmp = TELE_MNTN_READ_REG(SOC_SCTRL_SCBAKDATA5_ADDR(tele_mntn_sctrl_base));
        tmp |= BIT(bit);
        TELE_MNTN_WRITE_REG(tmp , SOC_SCTRL_SCBAKDATA5_ADDR(tele_mntn_sctrl_base));
    }

    return tele_mntn_func_sw_get();
}

u64_t tele_mntn_func_sw_bit_clr (u32_t bit)
{
    u32_t tmp = 0;

    if(!tele_mntn_sctrl_base)
    {
        return 0;
    }

    if(bit >= 32)
    {
        tmp = TELE_MNTN_READ_REG(SOC_SCTRL_SCBAKDATA15_ADDR(tele_mntn_sctrl_base));
        tmp &= (~((u32_t)BIT(bit-32)));
        TELE_MNTN_WRITE_REG(tmp , SOC_SCTRL_SCBAKDATA15_ADDR(tele_mntn_sctrl_base));
    }
    else
    {
        tmp = TELE_MNTN_READ_REG(SOC_SCTRL_SCBAKDATA5_ADDR(tele_mntn_sctrl_base));
        tmp &= (~((u32_t)BIT(bit)));
        TELE_MNTN_WRITE_REG(tmp , SOC_SCTRL_SCBAKDATA5_ADDR(tele_mntn_sctrl_base));
    }

    return tele_mntn_func_sw_get();
}



#if !defined(CONFIG_TELE_MNTN_CORE_CM3)
u32_t get_slice_time(void_t)
{
    if(!tele_mntn_sctrl_base)
    {
        return 0;
    }
    return TELE_MNTN_READ_REG(SOC_SCTRL_SCBBPDRXSTAT1_ADDR(tele_mntn_sctrl_base));
}
u32_t get_rtc_time(void_t)
{
    if(!tele_mntn_rtc0_base)
    {
        return 0;
    }

    return TELE_MNTN_READ_REG(SOC_RTCTIMERWDTV100_RTC_DR_ADDR(tele_mntn_rtc0_base));
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

