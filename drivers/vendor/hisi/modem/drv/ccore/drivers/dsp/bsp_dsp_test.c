
/*lint --e{537} */
#include <stdio.h>

#include <osl_types.h>
#include <osl_bio.h>
#include <osl_sem.h>
#include <osl_wait.h>
#include <osl_spinlock.h>

#include <hi_base.h>
#include <hi_syssc.h>
#include <hi_syscrg.h>
#include <hi_pwrctrl.h>
#include <hi_dsp.h>

#include <bsp_om.h>
#include <bsp_edma.h>
#include <bsp_sram.h>
#include <bsp_dpm.h>
#include <bsp_dsp.h>
#include <bsp_icc.h>
#include <bsp_version.h>
#include <bsp_hardtimer.h>

#include <bsp_busstress.h>

#include <TLPhyDspTestInterface.h>


#ifdef __cplusplus
extern "C" {
#endif

#define DEMEM1_START_FOR_BUS_PRESS_TEST TL_PHY_MAILBOX_SOC_TEST_ADDR

int bsp_bbe_run_test(void);

int bsp_bbe_run_test(void)
{
    int ret = 0; 
    ret = bsp_bbe_load_muti();
    
    if (ret)
        return ret;
    writel(0, DEMEM1_START_FOR_BUS_PRESS_TEST);
    
    return bsp_bbe_run();

}
static int bsp_bbe_stress_writeReadTest_start(UINT32 mailBody1, UINT32 mailBody2, UINT32 mailBody3);
static int bsp_bbe_stress_writeReadTest_start(UINT32 mailBody1, UINT32 mailBody2, UINT32 mailBody3)
{
    
    DSP_DRV_MAIL_HEAD mailHead;
    if(((mailBody1 >= DDR_LPHY_SDR_ADDR) && ((mailBody1 + mailBody2) <= (DDR_LPHY_SDR_ADDR + DDR_LPHY_SDR_SIZE))) || 
        ((mailBody1 >= BBE_TCM_ADDR) && ((mailBody1 + mailBody2) <= (BBE_TCM_ADDR + BBE_TCM_SIZE))))
    {
        
        mailHead.ulReg32 = readl(DEMEM1_START_FOR_BUS_PRESS_TEST);
        mailHead.bits.ulPPTR++;
        mailHead.bits.ulMsgID = WRITE_READ_TEST;
        writel(mailBody1, DEMEM1_START_FOR_BUS_PRESS_TEST + 0x4);
        writel(mailBody2, DEMEM1_START_FOR_BUS_PRESS_TEST + 0x8);
        writel(mailBody3, DEMEM1_START_FOR_BUS_PRESS_TEST + 0xC);
        writel(mailHead.ulReg32, DEMEM1_START_FOR_BUS_PRESS_TEST);

        return 0;
    }
    else
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "Invalid addr input !\n");
        return -1;
    }
    
}

static int bsp_bbe_stress_readWriteTest_start(UINT32 mailBody1, UINT32 mailBody2, UINT32 mailBody3);
static int bsp_bbe_stress_readWriteTest_start(UINT32 mailBody1, UINT32 mailBody2, UINT32 mailBody3)
{
    
    DSP_DRV_MAIL_HEAD mailHead;
    if((((mailBody1 >= DDR_LPHY_SDR_ADDR) && ((mailBody1 + mailBody3) <= (DDR_LPHY_SDR_ADDR + DDR_LPHY_SDR_SIZE))) || 
        ((mailBody1 >= BBE_TCM_ADDR) && ((mailBody1 + mailBody3) <= (BBE_TCM_ADDR + BBE_TCM_SIZE)))) &&
        (((mailBody2 >= DDR_LPHY_SDR_ADDR && ((mailBody2 + mailBody3) <= (DDR_LPHY_SDR_ADDR + DDR_LPHY_SDR_SIZE))) || 
        ((mailBody2 >= BBE_TCM_ADDR) && ((mailBody2 + mailBody3) <= (BBE_TCM_ADDR + BBE_TCM_SIZE))))) )
    {
        
        mailHead.ulReg32 = readl(DEMEM1_START_FOR_BUS_PRESS_TEST);
        mailHead.bits.ulPPTR++;
        mailHead.bits.ulMsgID = READ_WRITE_TEST;
        writel(mailBody1, DEMEM1_START_FOR_BUS_PRESS_TEST + 0x4);
        writel(mailBody2, DEMEM1_START_FOR_BUS_PRESS_TEST + 0x8);
        writel(mailBody3, DEMEM1_START_FOR_BUS_PRESS_TEST + 0xC);
        writel(mailHead.ulReg32, DEMEM1_START_FOR_BUS_PRESS_TEST);

        return 0;
    }
    else
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "Invalid addr input !\n");
        return -1;
    }
}

static int bsp_bbe_stress_funcCycleCalc_start(UINT32 mailBody1, UINT32 mailBody2, UINT32 mailBody3);
static int bsp_bbe_stress_funcCycleCalc_start(UINT32 mailBody1, UINT32 mailBody2, UINT32 mailBody3)
{
    
    DSP_DRV_MAIL_HEAD mailHead;
    
    mailHead.ulReg32 = readl(DEMEM1_START_FOR_BUS_PRESS_TEST);
    mailHead.bits.ulPPTR++;
    mailHead.bits.ulMsgID = FUNC_CYCLE_CALC;
    writel(mailBody1, DEMEM1_START_FOR_BUS_PRESS_TEST + 0x4);
    /* 
            writel(mailBody2, DEMEM1_START_FOR_BUS_PRESS_TEST + 0x8);
            writel(mailBody3, DEMEM1_START_FOR_BUS_PRESS_TEST + 0xC);
       */
    writel(mailHead.ulReg32, DEMEM1_START_FOR_BUS_PRESS_TEST);

    return 0;
    
}
int bsp_bbe_stress_test_start(UINT32 mailBody1, UINT32 mailBody2, UINT32 mailBody3, UINT16 msgID);
int bsp_bbe_stress_test_start(UINT32 mailBody1, UINT32 mailBody2, UINT32 mailBody3, UINT16 msgID)
{
    if(WRITE_READ_TEST == msgID)
    {
        return bsp_bbe_stress_writeReadTest_start(mailBody1, mailBody2, mailBody3);
    }
    else if(READ_WRITE_TEST == msgID)
    {
        return bsp_bbe_stress_readWriteTest_start(mailBody1, mailBody2, mailBody3);
    }
    else if(FUNC_CYCLE_CALC == msgID)
    {
        return bsp_bbe_stress_funcCycleCalc_start(mailBody1, mailBody2, mailBody3);
    }
    else
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "Invalid msgID !\n");
        return -1;
    }
    
}

static int bsp_bbe_stress_writeReadTest_result();
static int bsp_bbe_stress_writeReadTest_result()
{
    DSP_DRV_MAIL_HEAD mailHead;
    UINT32 addr, result;
    result = readl(DEMEM1_START_FOR_BUS_PRESS_TEST + 0xC);
    if (0xAAAAAAAA == result)
    {
        bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_DSP, "SUCCESS!\n");
        return 0;
    }    
    else
    {
        addr = readl(DEMEM1_START_FOR_BUS_PRESS_TEST + 0x4);
        mailHead.ulReg32 = readl(DEMEM1_START_FOR_BUS_PRESS_TEST);
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "MsgID:%d, Addr:%d, Result:%d\n", mailHead.bits.ulMsgID, addr, result);
        return -1;
    }
}

static int bsp_bbe_stress_readWriteTest_result();
static int bsp_bbe_stress_readWriteTest_result()
{
    UINT32 sAddr, dAddr, len;
    UINT32 i;
    DSP_DRV_MAIL_HEAD mailHead;
    UINT32 sData, dData;
    mailHead.ulReg32 = readl(DEMEM1_START_FOR_BUS_PRESS_TEST);
    sAddr = readl(DEMEM1_START_FOR_BUS_PRESS_TEST + 0x4);
    dAddr = readl(DEMEM1_START_FOR_BUS_PRESS_TEST + 0x8);
    len = readl(DEMEM1_START_FOR_BUS_PRESS_TEST + 0xC);
    for(i = 0; i < len; i = i + 4)
    {
        sData = readl(sAddr);
        dData = readl(dAddr);
        if(sData != dData)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "MsgID:%d, sAddr:%d, dAddr:%d\n", mailHead.bits.ulMsgID, sAddr, dAddr);
            return -1;
        }
        sAddr += 0x4;
        dAddr += 0x4;
    }
    bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_DSP, "SUCCEED!\n");
    return 0;
    
}

static int bsp_bbe_stress_funcCycleCalc_result();
static int bsp_bbe_stress_funcCycleCalc_result()
{
    DSP_DRV_MAIL_HEAD mailHead;
    UINT32 funID, cycle;
    mailHead.ulReg32 = readl(DEMEM1_START_FOR_BUS_PRESS_TEST);
    
    funID = readl(DEMEM1_START_FOR_BUS_PRESS_TEST + 0x4);
    cycle = readl(DEMEM1_START_FOR_BUS_PRESS_TEST + 0x8);
    bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_DSP, "MsgID:%d, Addr:%d, Result:%d\n", mailHead.bits.ulMsgID, funID, cycle);
    return 0;
    
}


int bsp_bbe_stress_test_result(void);
int bsp_bbe_stress_test_result(void)
{

    DSP_DRV_MAIL_HEAD mailHead;
    mailHead.ulReg32 = readl(DEMEM1_START_FOR_BUS_PRESS_TEST);
    if(mailHead.bits.ulPPTR == mailHead.bits.ulCPTR)
    {
        if(WRITE_READ_TEST == mailHead.bits.ulMsgID)
        {
            return bsp_bbe_stress_writeReadTest_result();
        }
        else if(READ_WRITE_TEST == mailHead.bits.ulMsgID)
        {
            return bsp_bbe_stress_readWriteTest_result();
        }
        else if(FUNC_CYCLE_CALC == mailHead.bits.ulMsgID)
        {
            return bsp_bbe_stress_funcCycleCalc_result();
        }
        else
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "Invalid msgID ! \n");
            return -1;
        }
    }
    else
    {
        bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_DSP, "BBE has not finished! \n");
        return -1;
    }
    
    
}

int bsp_bbe_stop_test(void);
int bsp_bbe_stop_test(void)
{
    int ret = 0;
    ret |= bsp_bbe_stop();
    ret |= bsp_bbe_reset();
    ret |= bsp_bbe_clock_disable();

    return ret;
}


#ifdef __cplusplus
}
#endif

