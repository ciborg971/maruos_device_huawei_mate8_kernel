
/*lint -save -e514*/
#include "bbp_osl.h"
#include "bsp_hardtimer.h"
#include "bsp_version.h"
#include "bsp_memrepair.h"
#include "hi_bbp_reg.h"
#include "bbp_balong.h"

#ifdef __cplusplus
extern "C" {
#endif

extern struct bbp_info g_bbpinfo;

unsigned int bbp_pwrctrl_is_enabled(u32 pwr_id)
{
    unsigned int state;

    /*������Դ�У�check cmos;�Ƕ�����Դ��check clk/rst;*/
    if(BBP_PWR_DEPENDENT != (g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.en_reg & BBP_PWR_DEPENDENT))
    {
        state = bbp_bit_chk(g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.state_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.state_bit))\
               &bbp_bit_chk(g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.rdy_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.rdy_bit));
    }
    else
    {
        state = (!bbp_bit_chk(g_bbpinfo.pwr.pwr_act[pwr_id].rst_ctrl.state_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].rst_ctrl.state_bit)))\
               &bbp_bit_chk(g_bbpinfo.pwr.pwr_act[pwr_id].clk_ctrl.state_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].clk_ctrl.state_bit));
    }

    return state;
}
void bbp_pwrctrl_enable(u32 pwr_id)
{
    u32 value = 0;
    int ret = 0;

    /*�Ƕ�����Դ�����ϵ硢��ǯλ*/
    if(BBP_PWR_DEPENDENT != (g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.en_reg & BBP_PWR_DEPENDENT))
    {
        /*�����ϵ�*/
        bbp_bit_set(g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.en_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.en_bit));

        /*�ȴ��ϵ����*/
        do
        {
            value = bbp_bit_get(g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.rdy_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.rdy_bit));
        }while(value==0);

        udelay(30);
    }

    /*���ý⸴λ*/;
    bbp_bit_set(g_bbpinfo.pwr.pwr_act[pwr_id].rst_ctrl.dis_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].rst_ctrl.dis_bit));

    if(BBP_PWR_DEPENDENT != (g_bbpinfo.pwr.pwr_act[pwr_id].iso_ctrl.en_reg & BBP_PWR_DEPENDENT))
    {
        /*����Ƕλ��ʹ��*/
        bbp_bit_set(g_bbpinfo.pwr.pwr_act[pwr_id].iso_ctrl.dis_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].iso_ctrl.dis_bit));
    }
    /*mem repair*/
    if(g_bbpinfo.pwr.pwr_act[pwr_id].repair_id & 0x80000000)
    {
        ret = bsp_modem_memrepair(g_bbpinfo.pwr.pwr_act[pwr_id].repair_id & 0x7fffffff);
        if(BSP_OK != ret)
        {
            bbp_print_error("pwr_id %d memrepair fail !\n",pwr_id);
        }
    }

    /*����ʱ��ʹ��*/
    bbp_bit_set(g_bbpinfo.pwr.pwr_act[pwr_id].clk_ctrl.en_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].clk_ctrl.en_bit));
}
void bbp_pwrctrl_disable(u32 pwr_id)
{
    /*����ʱ�Ӳ�ʹ��*/
    bbp_bit_set(g_bbpinfo.pwr.pwr_act[pwr_id].clk_ctrl.dis_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].clk_ctrl.dis_bit));

    if(BBP_PWR_DEPENDENT != (g_bbpinfo.pwr.pwr_act[pwr_id].iso_ctrl.en_reg & BBP_PWR_DEPENDENT))
    {
        /*����Ƕλʹ��*/
        bbp_bit_set(g_bbpinfo.pwr.pwr_act[pwr_id].iso_ctrl.en_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].iso_ctrl.en_bit));
    }

    /*���ø�λ*/
    bbp_bit_set(g_bbpinfo.pwr.pwr_act[pwr_id].rst_ctrl.en_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].rst_ctrl.en_bit));

    if(BBP_PWR_DEPENDENT != (g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.en_reg & BBP_PWR_DEPENDENT))
    {
        /*���õ���*/
        bbp_bit_set(g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.dis_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.dis_bit));
    }
}
unsigned int bbp_clkctrl_is_enabled(u32 clk_id)
{
    return bbp_bit_chk(g_bbpinfo.clk.clk_act[clk_id].clk_ctrl.state_reg,(u32)0x1 << g_bbpinfo.clk.clk_act[clk_id].clk_ctrl.state_bit);
}
void bbp_clkctrl_enable(u32 clk_id)
{
    bbp_bit_set(g_bbpinfo.clk.clk_act[clk_id].clk_ctrl.en_reg,(u32)0x1 << g_bbpinfo.clk.clk_act[clk_id].clk_ctrl.en_bit);
}
void bbp_clkctrl_disable(u32 clk_id)
{
    bbp_bit_set(g_bbpinfo.clk.clk_act[clk_id].clk_ctrl.dis_reg,(u32)0x1 << g_bbpinfo.clk.clk_act[clk_id].clk_ctrl.dis_bit);
}
unsigned int bbp_rstctrl_is_enabled(u32 clk_id)
{
    return bbp_bit_chk(g_bbpinfo.clk.clk_act[clk_id].rst_ctrl.state_reg,(u32)0x1 << g_bbpinfo.clk.clk_act[clk_id].rst_ctrl.state_bit);
}
void bbp_rstctrl_enable(u32 clk_id)
{
    bbp_bit_set(g_bbpinfo.clk.clk_act[clk_id].rst_ctrl.en_reg,(u32)0x1 << g_bbpinfo.clk.clk_act[clk_id].rst_ctrl.en_bit);
}
void bbp_rstctrl_disable(u32 clk_id)
{
    bbp_bit_set(g_bbpinfo.clk.clk_act[clk_id].rst_ctrl.dis_reg,(u32)0x1 << g_bbpinfo.clk.clk_act[clk_id].rst_ctrl.dis_bit);
}

/*debugʹ��*/
#if 1
/*��Դ�и�λ״̬*/
unsigned int bbp_pwr_rst_status(u32 pwr_id)
{
    return bbp_bit_chk(g_bbpinfo.pwr.pwr_act[pwr_id].rst_ctrl.state_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].rst_ctrl.state_bit));
}
/*��Դ��ǯλ״̬*/
unsigned int bbp_pwr_iso_status(u32 pwr_id)
{
    return bbp_bit_chk(g_bbpinfo.pwr.pwr_act[pwr_id].iso_ctrl.state_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].iso_ctrl.state_bit));
}
/*��Դ��ǯλ״̬*/
unsigned int bbp_pwr_clk_status(u32 pwr_id)
{
    return bbp_bit_chk(g_bbpinfo.pwr.pwr_act[pwr_id].clk_ctrl.state_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].clk_ctrl.state_bit));
}
/*��Դ�е�Դ״̬*/
unsigned int bbp_pwr_cmos_status(u32 pwr_id)
{
    unsigned int state;

    state = bbp_bit_chk(g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.state_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.state_bit))\
           &bbp_bit_chk(g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.rdy_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.rdy_bit));

    return state;
}
/*for clear pclint*/
void bbp_disable(u32 clk_id)
{
    bbp_bit_clr(g_bbpinfo.clk.clk_act[clk_id].rst_ctrl.dis_reg,(u32)0x1 << g_bbpinfo.clk.clk_act[clk_id].rst_ctrl.dis_bit);
}
#endif

#ifdef __cplusplus
}
#endif
/*lint -restore*/
