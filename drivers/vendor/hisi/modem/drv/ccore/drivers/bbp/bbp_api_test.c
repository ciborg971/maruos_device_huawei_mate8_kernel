

/*lint --e{537}*/
#include <string.h>
#include <stdlib.h>
#include "securec.h"
#include <osl_thread.h>
#include <osl_malloc.h>
#include "bsp_bbp.h"
#include "bsp_memmap.h"
#include "hi_base.h"
#include "hi_bbp_dma.h"
#include <bsp_shared_ddr.h>
#include <bsp_hardtimer.h>
#include <bsp_busstress.h>
#include "bsp_dpm.h"
#include "soc_memmap.h"
#include <soc_memmap.h>
#include "hi_bbp_reg.h"
#include "hi_bbp_ltedrx.h"
#include "hi_bbp_tdsdrx.h"
#include "bbp_balong.h"

extern struct bbp_info g_bbpinfo;

extern int sysClkRateGet(void);
extern unsigned long random(void);
static void bbp_msleep(int x)
{
    osl_task_delay(sysClkRateGet()*x/1000+1);
}

/*��ʱ��֡�жϲ���*/
/*****************************************************************************
* �� �� : bbp_int_ltetf_func
* �� �� : bbp lte 1ms��ʱ��֡�жϴ�����Ժ���
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
void bbp_int_ltetf_func(void)
{
    bbp_print_debug("ltetf int in!\n");
}
/*****************************************************************************
* �� �� : bbp_int_tdstf_func
* �� �� : bbp tds 5ms��ʱ��֡�жϴ�����Ժ���
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
void bbp_int_tdstf_func(void)
{
    bbp_print_debug("tdstf int in!\n");
}
/*****************************************************************************
* �� �� : mdrv_bbp_int_ltetf_test
* �� �� : bbp���ϲ��ṩ��tds�ж���ؽӿڲ���
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
s32 mdrv_bbp_int_ltetf_test()
{
    u32 int_cnt1 = 0;
    u32 int_cnt2 = 0;
    s32 iret = BBP_OK;

    /*ע���жϴ�����(����汾����Ҫע�ᣬʹ���ϲ�ע���)*/
    mdrv_bbp_register_lte_intr_cb(bbp_int_ltetf_func);
    /*�ҽ��ж�*/
    mdrv_bbp_init_intr(PWC_COMM_MODE_LTE);
    /*���ж�*/
    mdrv_bbp_enable_lte_intr();
    /*��ѯ�жϼ���*/
    int_cnt1 = g_bbpinfo.bbpint[BBP_INT_LTETF].cnt;
    bbp_msleep(5);
    int_cnt2 = g_bbpinfo.bbpint[BBP_INT_LTETF].cnt;

    /*�з�ת�������ֻ�Ƚ��Ƿ����*/
    if(int_cnt1 == int_cnt2)
    {
        bbp_print_error("enable test fail ,lte int cnt1 is %d,cnt 2 is %d!\n",int_cnt1,int_cnt2);
        iret = BBP_ERR;
        goto out;
    }

    /*���ж�*/
    mdrv_bbp_disable_lte_intr();
    int_cnt1 = g_bbpinfo.bbpint[BBP_INT_LTETF].cnt;
    bbp_msleep(5);
    int_cnt2 = g_bbpinfo.bbpint[BBP_INT_LTETF].cnt;
    if(int_cnt1 != int_cnt2)
    {
        bbp_print_error("disable test fail ,lte int cnt1 is %d,cnt 2 is %d!\n",int_cnt1,int_cnt2);
        iret = BBP_ERR;
        goto out;
    }

    bbp_print_error("test ok!\n");

out:
    return iret;
}

/*****************************************************************************
* �� �� : mdrv_bbp_int_tdstf_test
* �� �� : bbp���ϲ��ṩ��tds�ж���ؽӿڲ���
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
s32 mdrv_bbp_int_tdstf_test(void)
{
    u32 int_cnt1 = 0;
    u32 int_cnt2 = 0;
    s32 iret = BBP_OK;

    /*ע���жϴ�����(����汾����Ҫע�ᣬʹ���ϲ�ע���)*/
    mdrv_bbp_register_tdstf_intr_cb(bbp_int_tdstf_func);
    mdrv_bbp_init_intr(PWC_COMM_MODE_TDS);
    /*���ж�*/
    mdrv_bbp_enable_tdstf_intr();
    /*��ѯ�жϼ���*/
    int_cnt1 = g_bbpinfo.bbpint[BBP_INT_TDSTF].cnt;
    bbp_msleep(20);
    int_cnt2 = g_bbpinfo.bbpint[BBP_INT_TDSTF].cnt;

    /*�з�ת�������ֻ�Ƚ��Ƿ����*/
    if(int_cnt1 == int_cnt2)
    {
        bbp_print_error("test fail ,tds int cnt1 is %d,cnt 2 is %d!\n",int_cnt1,int_cnt2);
        iret = BBP_ERR;
        goto out;
    }
    /*���ж�*/
    mdrv_bbp_disable_tdstf_intr();
    int_cnt1 = g_bbpinfo.bbpint[BBP_INT_TDSTF].cnt;
    bbp_msleep(5);
    int_cnt2 = g_bbpinfo.bbpint[BBP_INT_TDSTF].cnt;
    if(int_cnt1 != int_cnt2)
    {
        bbp_print_error("disable test fail ,lte int cnt1 is %d,cnt 2 is %d!\n",int_cnt1,int_cnt2);
        iret = BBP_ERR;
        goto out;
    }

    bbp_print_error("test ok!\n");

out:
    return iret;
}
/*****************************************************************************
* �� �� : mdrv_bbp_int_ltewp_test
* �� �� : lte wake up�жϲ���
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� : ���й�����ʱ������,����ȫϵͳ��,����Ӱ��dsp
*****************************************************************************/
s32 bbp_int_ltewp_test(void)
{
    s32 iret = BBP_OK;
    u32 reg_temp = 0;/*���滽�Ѷ�ʱ��Ĭ��ֵ*/

    /*���û��Ѷ�ʱ��,�����ж�,�ȱ��������*/
    reg_temp = readl((unsigned)g_bbpinfo.part[BBP_LDRX].reg_base + HI_BBP_LTEDRX_WAKEUP_32K_CNT_OFFSET);
    writel(5,(unsigned)g_bbpinfo.part[BBP_LDRX].reg_base + HI_BBP_LTEDRX_WAKEUP_32K_CNT_OFFSET);
    /*���ж�*/
    mdrv_bbp_enable_wakeup_intr(PWC_COMM_MODE_LTE);
    /*˯��ʹ��,�����źţ�д1����Ч*/
    writel(1,(unsigned)g_bbpinfo.part[BBP_LDRX].reg_base + HI_BBP_LTEDRX_SLEEP_START_OFFSET);
    bbp_msleep(10);
    /*ȷ���Ƿ���Ӧ*/
    if(!hi_bbp_int_ltewp_status())
    {
        bbp_print_error("ltewp int enable error!\n");
        iret = BBP_ERR;
        goto out;
    }
    /*���ж�*/
    mdrv_bbp_disable_wakeup_intr(PWC_COMM_MODE_LTE);
    bbp_msleep(10);
    mdrv_bbp_clear_wakeup_intr(PWC_COMM_MODE_LTE);
    bbp_msleep(10);
    if(hi_bbp_int_ltewp_status())
    {
        bbp_print_error("ltewp int disable error!\n");
        iret = BBP_ERR;
        goto out;
    }
    bbp_print_error("test ok!\n");
out:
    /*�ָ���ʱ������*/
    writel(reg_temp,(unsigned)g_bbpinfo.part[BBP_LDRX].reg_base + HI_BBP_LTEDRX_WAKEUP_32K_CNT_OFFSET);
    return iret;
}
/*****************************************************************************
* �� �� : bbp_int_tdswp_test
* �� �� : tds wake up�жϲ���
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� : ���й�����ʱ������,����ȫϵͳ��,����Ӱ��dsp
*****************************************************************************/
s32 bbp_int_tdswp_test(void)
{
    s32 iret = BBP_OK;
    u32 reg_temp = 0;/*���滽�Ѷ�ʱ��Ĭ��ֵ*/

    /*���û��Ѷ�ʱ��,�����ж�,�ȱ��������*/
    reg_temp = readl((unsigned)g_bbpinfo.part[BBP_TDRX].reg_base + HI_BBP_TDSDRX_WAKEUP_32K_CNT_OFFSET);
    writel(5,(unsigned)g_bbpinfo.part[BBP_TDRX].reg_base + HI_BBP_TDSDRX_WAKEUP_32K_CNT_OFFSET);

    /*���ж�*/
    mdrv_bbp_enable_wakeup_intr(PWC_COMM_MODE_TDS);
    /*˯��ʹ��,�����źţ�д1����Ч*/
    writel(1,(unsigned)g_bbpinfo.part[BBP_TDRX].reg_base + HI_BBP_TDSDRX_SLEEP_START_OFFSET);
    bbp_msleep(10);
    /*ȷ���Ƿ���Ӧ*/
    if(!hi_bbp_int_tdswp_status())
    {
        bbp_print_error("tdswp int enable error!\n");
        iret = BBP_ERR;
        goto out;
    }
    /*����Ѳ������ж�*/
    mdrv_bbp_clear_wakeup_intr(PWC_COMM_MODE_TDS);
    bbp_msleep(5);
    /*���ж�*/
    mdrv_bbp_disable_wakeup_intr(PWC_COMM_MODE_TDS);
    bbp_msleep(10);

    if(hi_bbp_int_tdswp_status())
    {
        bbp_print_error("tdswp int disable error!\n");
        iret = BBP_ERR;
        goto out;
    }
    bbp_print_error("test ok!\n");
out:
    /*�ָ���ʱ������*/
    writel(reg_temp,(unsigned)g_bbpinfo.part[BBP_TDRX].reg_base + HI_BBP_TDSDRX_WAKEUP_32K_CNT_OFFSET);
    return iret;
}
/*****************************************************************************
* �� �� : mdrv_bbp_int_wp_test
* �� �� : bbp���ϲ��ṩ��tds wake up�жϽӿڲ���
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� : ���й�����ʱ������,����ȫϵͳ��,����Ӱ��dsp
*****************************************************************************/
s32 mdrv_bbp_int_wp_test(void)
{
    s32 iret = BBP_OK;

    iret |= bbp_int_ltewp_test();
    iret |= bbp_int_tdswp_test();

    return iret;
}
/*��׮����*/
void bbp_int_dltb_func(void)
{
    bbp_print_debug("dltb int in!\n");
}
s32 mdrv_bbp_int_dltb_test(void)
{
    s32 iret = BBP_OK;

    mdrv_bbp_register_dltb_intr_cb(bbp_int_dltb_func);

    bbp_print_error("test ok!\n");
    return iret;
}
/*****************************************************************************
* �� �� : bbp_int_test
* �� �� : bbp �жϲ��ԣ��ֶ�����ʹ��
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
s32 bbp_int_test(void)
{
    s32 iret = BBP_OK;

    iret = mdrv_bbp_int_ltetf_test();
    iret |= mdrv_bbp_int_tdstf_test();
    iret |= mdrv_bbp_int_wp_test();

    return iret;
}
s32 mdrv_bbp_lte_sysfrm_test(void)
{
    s32 iret = BBP_OK;
    unsigned short sysfrm1 = 0;
    unsigned short sysfrm2 = 0;
    u32 lbbp_switch = 0;

    lbbp_switch = bbp_get_ltemtcmos_status();

    if(lbbp_switch)
    {
        sysfrm1 = mdrv_bbp_get_lte_sysfrm();
        bbp_msleep(10);
        sysfrm2 = mdrv_bbp_get_lte_sysfrm();

        if(sysfrm1 == sysfrm2)
        {
            bbp_print_error("sysfrm not change!\n");
            iret = BBP_ERR;
            goto out;
        }
    }
    else
    {
        sysfrm1 = mdrv_bbp_get_lte_sysfrm();
        if(sysfrm1 != BBP_POWER_DOWN_BACK)
        {
            bbp_print_error("should be DOWN_BACK!\n");
            iret = BBP_ERR;
            goto out;
        }
    }

    bbp_print_error("test ok!\n");
out:
    return iret;
}
s32 mdrv_bbp_lte_subfrm_test(void)
{
    s32 iret = BBP_OK;
    unsigned short subfrm1 = 0;
    unsigned short subfrm2 = 0;
    u32 lbbp_switch = 0;

    lbbp_switch = bbp_get_ltemtcmos_status();

    if(lbbp_switch)
    {
        subfrm1 = mdrv_bbp_get_lte_subfrm();
        bbp_msleep(1);
        subfrm2 = mdrv_bbp_get_lte_subfrm();

        if(subfrm1 == subfrm2)
        {
            bbp_print_error("sysfrm not change!\n");
            iret = BBP_ERR;
            goto out;
        }
    }
    else
    {
        subfrm1 = mdrv_bbp_get_lte_subfrm();
        if(subfrm1 != BBP_POWER_DOWN_BACK)
        {
            bbp_print_error("should be DOWN_BACK!\n");
            iret = BBP_ERR;
            goto out;
        }
    }

    bbp_print_error("test ok!\n");
out:
    return iret;
}
s32 mdrv_bbp_tds_subfrm_test(void)
{
    s32 iret = BBP_OK;
    unsigned short subfrm1 = 0;
    unsigned short subfrm2 = 0;
    u32 tbbp_switch = 0;

    tbbp_switch = bbp_get_twmtcmos_status();
    if(tbbp_switch)
    {
        subfrm1 = mdrv_bbp_get_tds_subfrm();
        bbp_msleep(5);
        subfrm2 = mdrv_bbp_get_tds_subfrm();
        if(subfrm1 == subfrm2)
        {
            bbp_print_error("sysfrm not change,both %d!\n",subfrm2);
            iret = BBP_ERR;
            goto out;
        }
    }
    else
    {
        subfrm1 = mdrv_bbp_get_tds_subfrm();
        if(subfrm1 != BBP_POWER_DOWN_BACK)
        {
            bbp_print_error("should be DOWN_BACK!\n");
            iret = BBP_ERR;
            goto out;
        }
    }
    bbp_print_error("test ok!\n");
out:
    return iret;
}
s32 mdrv_bbp_tds_subfrm_offset_test(void)
{
    s32 iret = BBP_OK;
    unsigned short usret = BBP_OK;
    unsigned short offset1 = 0x5;
    unsigned short offset2 = 0;
    u32 tbbp_switch = 0;

    tbbp_switch = bbp_get_twmtcmos_status();

    if(tbbp_switch)
    {
        usret = mdrv_bbp_set_tds_subfrm_offset(offset1);

        if(usret == BBP_POWER_DOWN_BACK)
        {
            iret = BBP_ERR;
            goto out;
        }
        hi_bbp_get_tds_sfn_oft(&offset2);
        if(offset2 != offset1)
        {
            bbp_print_error("error,set %d,get %d!\n",offset1,offset2);
            iret = BBP_ERR;
            goto out;
        }
    }
    else
    {
        usret = mdrv_bbp_set_tds_subfrm_offset(offset1);

        if(usret != BBP_POWER_DOWN_BACK)
        {
            bbp_print_error("should be DOWN_BACK!\n");
            iret = BBP_ERR;
            goto out;
        }
    }

    bbp_print_error("test ok!\n");

out:
    return iret;
}
s32 mdrv_bbp_measure_flag_test(void)
{
    s32 iret = BBP_OK;
    int means_value = 0;
    PWC_COMM_MODE_E mode = PWC_COMM_MODE_GSM;

    for(mode = PWC_COMM_MODE_GSM;mode <= PWC_COMM_MODE_TDS;mode++)
    {
        means_value = mdrv_bbp_get_measure_flag(mode);
        if(means_value == 0xffffffff)
        {
            iret = BBP_ERR;
            bbp_print_error("mode %d test error!\n",mode);
            goto out;
        }
    }
    /*����Ӧ�÷���-1*/
    for(mode = PWC_COMM_MODE_TDS + 1;mode <= PWC_COMM_MODE_BUTT;mode++)
    {
        means_value = mdrv_bbp_get_measure_flag(mode);
        if(means_value != -1)
        {
            iret = BBP_ERR;
            bbp_print_error("mode %d test error,should be -1!\n",mode);
            goto out;
        }
    }

    bbp_print_error("test ok!\n");

out:
    return iret;
}
s32 mdrv_bbp_lte_ta_test(void)
{
    s32 iret = BBP_OK;
    int ta_value = 0;

    ta_value = bbp_lps_get_ta();
    if(ta_value == 0)
    {
        iret = BBP_ERR;
        bbp_print_error("test error!\n");
        goto out;
    }

    bbp_print_error("test ok!\n");

out:
    return iret;
}
s32 mdrv_bbp_sleep_period_test(void)
{
    s32 iret = BBP_OK;
    int sleep_time = 0;
    u32 reg_temp = 0;/*���滽�Ѷ�ʱ��Ĭ��ֵ*/

    /*���û��Ѷ�ʱ��*/
    reg_temp = readl((unsigned)g_bbpinfo.part[BBP_TDRX].reg_base + HI_BBP_TDSDRX_WAKEUP_32K_CNT_OFFSET);
    writel(10,(unsigned)g_bbpinfo.part[BBP_TDRX].reg_base + HI_BBP_TDSDRX_WAKEUP_32K_CNT_OFFSET);

    /*˯��ʹ��,�����źţ�д1����Ч*/
    writel(1,(unsigned)g_bbpinfo.part[BBP_TDRX].reg_base + HI_BBP_TDSDRX_SLEEP_START_OFFSET);
    bbp_msleep(5);
    sleep_time = mdrv_bbp_get_sleep_period();
    if((sleep_time == 0) ||(sleep_time >10))
    {
        iret = BBP_ERR;
        bbp_print_error("sleep time is %d,test error!\n",sleep_time);
        goto out;
    }

    bbp_print_error("test ok!\n");

out:
    /*�ָ���ʱ������*/
    writel(reg_temp,(unsigned)g_bbpinfo.part[BBP_TDRX].reg_base + HI_BBP_TDSDRX_WAKEUP_32K_CNT_OFFSET);
    return iret;
}
/*����ӿڲ���*/
/*���Զ������µ�ӿ�*/
/*bbp_clk*/
u32 mdrv_bbp_clk_test(void)
{
    u32 test_result = BBP_OK;
    u32 iret = BBP_OK;
    u32 clk_id = 0;
    u32 clk_cnt[BBP_CLK_MAX - BBP_CLK_MIN + 1] = {0};
    bool clkon_flag = true;
    u8 mode_id,module_id,modem_id,channel_id,i = 0;

    for(module_id = BBP_PWC_MODULE_MIN;module_id <= BBP_PWC_MODULE_MAX; module_id++)
    {
        for(modem_id = BBP_PWC_MODEM_MIN;modem_id <= BBP_PWC_MODEM_MAX; modem_id++)
        {
            for(mode_id = BBP_PWC_MODE_MIN;mode_id <= BBP_PWC_MODE_MAX;mode_id++)
            {
                for(channel_id = PWC_COMM_CHANNEL_0;channel_id <= PWC_COMM_CHANNEL_BUTT;channel_id++)
                {
                    iret = mdrv_pm_enable_bbpclk(mode_id,module_id,modem_id,channel_id);
                    /*�ҵ�������clkid*/
                    for (i = BBP_CLK_MIN ;i <= BBP_CLK_MAX ;i++ )
                    {
                        clk_id = g_bbpinfo.clk.clk_list[module_id-BBP_PWC_MODULE_MIN][modem_id-BBP_PWC_MODEM_MIN][mode_id-BBP_PWC_MODE_MIN].pwc_clk[i-BBP_CLK_MIN];
                        if (BBP_PWC_NULL == clk_id)
                        {
                            break;
                        }
                        else
                        {
                            clk_cnt[clk_id - BBP_CLK_MIN]++;
                        }
                    }
                }
            }
        }
    }
    for(module_id = BBP_PWC_MODULE_MIN;module_id <= BBP_PWC_MODULE_MAX; module_id++)
    {
        for(modem_id = BBP_PWC_MODEM_MIN;modem_id <= BBP_PWC_MODEM_MAX; modem_id++)
        {
            for(mode_id = BBP_PWC_MODE_MIN;mode_id <= BBP_PWC_MODE_MAX;mode_id++)
            {
                for(channel_id = PWC_COMM_CHANNEL_0;channel_id <= PWC_COMM_CHANNEL_BUTT;channel_id++)
                {
                    iret |= mdrv_pm_disable_bbpclk(mode_id,module_id,modem_id,channel_id);
                     /*�ҵ�������clkid*/
                    for (i = BBP_CLK_MIN ;i <= BBP_CLK_MAX ;i++ )
                    {
                        clk_id = g_bbpinfo.clk.clk_list[module_id-BBP_PWC_MODULE_MIN][modem_id-BBP_PWC_MODEM_MIN][mode_id-BBP_PWC_MODE_MIN].pwc_clk[i-BBP_CLK_MIN];
                        if (BBP_PWC_NULL == clk_id)
                        {
                            if(BBP_CLK_MIN == i)/*û�пɲ�����pwridĬ�Ϸ���off״̬*/
                                clkon_flag = false;
                            break;
                        }
                        else
                        {
                            if(--clk_cnt[clk_id - BBP_CLK_MIN])
                                clkon_flag &= true;/*��pwrid����ͶƱ�����ܹرգ��鿴��һ��clkid�Ƿ�ر�*/
                            else
                                clkon_flag &= false;/*����һ��clkid�Ѿ���ͶƱ���رգ�������Ӧ�÷���off��*/
                        }
                    }
                }

                if(false == clkon_flag)
                {
                    if(PWRCTRL_COMM_OFF != bbp_clk_status(mode_id,module_id,modem_id))
                    {
                        bbp_print_error("mode %d module %d modem %d vote error,should be off!",mode_id,module_id,modem_id);
                        test_result = BBP_ERR;
                        goto out;
                    }
                    clkon_flag = true;
                }
                else
                {
                    if(PWRCTRL_COMM_ON != bbp_clk_status(mode_id,module_id,modem_id))
                    {
                        bbp_print_error("mode %d module %d modem %d vote error,should be on!",mode_id,module_id,modem_id);
                        test_result = BBP_ERR;
                        goto out;
                    }
                }
            }
        }
    }

out:
    if(test_result || iret)
        bbp_print_error("test error!");
    else
        bbp_print_error("test ok!");

    return (test_result|iret);
}

int mdrv_bbp_get_timing_val_test()
{
    BBP_TIMING_STRU *pstTiming = NULL;
    int len = sizeof(BBP_TIMING_STRU);
    int ret = 0;

    pstTiming = malloc(len);
    memset_s(pstTiming,len,0,len);

    ret = mdrv_bbp_get_timing_val(pstTiming);
    if(!ret)
    {
        bbp_print_error("lte time reg value:0x%x,32k systime reg value:0x%x.\n",pstTiming->uwLTETimeRegVal,pstTiming->uw32KSysTime);
    }
    else
        bbp_print_error("test error!\n");

    return ret;
}

