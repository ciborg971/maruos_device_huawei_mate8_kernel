
/*lint -save -e537 -e656 -e801 */
#include <bsp_bbp.h>
#include <bbp_balong.h>
#include <hi_bbp.h>
#include "hi_bbp_reg.h"

extern struct bbp_info g_bbpinfo;
#define bbp_print_dbg(fmt, ...) (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_BBP, fmt,##__VA_ARGS__))

/*****************************************************************************
* �� �� : bbp_log_set
* �� �� : bbp ��ش�ӡ�ȼ�����
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
void bbp_log_set(u32 level)
{
    /*todo xuwenfang*/
    (void)bsp_mod_level_set(BSP_MODU_BBP, level);
    bbp_print_info("bbp log id=%d, set to level=%d)\n",BSP_MODU_BBP,level);
}
/*****************************************************************************
* �� �� : bbp_log_get
* �� �� : ��ȡbbp ��ش�ӡ�ȼ�
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
void bbp_log_get(void)
{
    u32 log_level = 0;

    log_level = bsp_log_module_cfg_get(BSP_MODU_BBP);
    bbp_print_dbg("bbp log id=%d, level=%d\n",BSP_MODU_BBP,log_level);
}
/*****************************************************************************
* �� �� : bbp_time_enable
* �� �� : �򿪼�ʱ���ܣ�ͳ�����ݱ��ݻָ�ʱ��
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
void bbp_time_enable(void)
{
    g_bbpinfo.dbg.time_debug = 1;
}
/*****************************************************************************
* �� �� : bbp_time_disable
* �� �� : �رռ�ʱ����
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
void bbp_time_disable(void)
{
    g_bbpinfo.dbg.time_debug = 0;
}
/*****************************************************************************
* �� �� : bbp_dma_enable
* �� �� : ��bbp dma��ʽ�����ݱ��ݻָ�ʱ����dma����
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
void bbp_dma_enable(void)
{
    g_bbpinfo.dpm.enable_dma = 1;
}
/*****************************************************************************
* �� �� : bbp_dma_disable
* �� �� : ��bbp dma��ʽ�����ݱ��ݻָ�ʱ����memcpy ����
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
void bbp_dma_disable(void)
{
    g_bbpinfo.dpm.enable_dma  = 0;
}
/*****************************************************************************
* �� �� : bbp_part_show
* �� �� : ��ȡbbp����ַ�ж�Ӧid�ź����ּ���ַ��Ϣ
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
void bbp_part_show(void)
{
    int i = 0;

    bbp_print_dbg("%-10s%-20s%10s%10s%10s\n", "part_id","part_name", "phy addr", "virt addr", "size");
    for(i = BBP_PART_TOP;i < BBP_PART_BUTT ;i++)
    {
        bbp_print_dbg("%-10d%-20s%10x%10x%10x\n",g_bbpinfo.part[i].id,g_bbpinfo.part[i].name,g_bbpinfo.part[i].reg_phyaddr,g_bbpinfo.part[i].reg_base,g_bbpinfo.part[i].size);
    }
}
/*****************************************************************************
* �� �� : bbp_pwrid_show
* �� �� : ��ȡbbp����Դ�ж�Ӧid�ź�����
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
void bbp_pwrid_show(void)
{
    u32 i = 0;

    for(i = BBP_PWR_MIN;i <= BBP_PWR_MAX; i++)
    {
        bbp_print_dbg("pwr_id %d: -- %s;\n",g_bbpinfo.pwr.pwr_act[i].pwr_id,g_bbpinfo.pwr.pwr_act[i].name);
    }
}
/*****************************************************************************
* �� �� : bbp_clkid_show
* �� �� : ��ȡbbp��ʱ���ж�Ӧid�ź�����
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
void bbp_clkid_show(void)
{
    u32 i = 0;

    for(i = BBP_CLK_MIN;i <= BBP_CLK_MAX; i++)
    {
        bbp_print_dbg("clk_id: %d -- %s;\n",g_bbpinfo.clk.clk_act[i].clk_id,g_bbpinfo.clk.clk_act[i].name);
    }
}
/*****************************************************************************
* �� �� : bbp_int_debug
* �� �� : bbp �жϺ��޸ģ�����ʹ��
* �� �� : int_eumn:Ҫ�޸ĵ��ж�ģ�飬irq_no:�µ��жϺ�
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
void bbp_int_irq_set(BBP_INT_ID_E int_eumn,unsigned irq_no)
{
    switch(int_eumn){
        case BBP_INT_LTETF:
            g_bbpinfo.bbpint[BBP_INT_LTETF].irq = irq_no;
            break;
        case BBP_INT_TDSTF:
            g_bbpinfo.bbpint[BBP_INT_TDSTF].irq = irq_no;
            break;
        default:
            bbp_print_dbg("not support this int !\n");
            break;
    }
}
/*****************************************************************************
* �� �� : bbp_int_debug
* �� �� : bbp �ж������Ϣ: �жϺţ��ж�״̬�������жϼ���
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
void bbp_int_debug(void)
{
    //bbp_print_dbg("bbp lte timer int arm status:%d\n",);/*�鿴armʹ��״̬*/

    bbp_print_dbg("%-10s%-20s%10s%10s%10s\n", "irq_id","irq_name", "irq_num", "irq_mask", "irq_cnt");
    /*ltetf*/
    bbp_print_dbg("%-10s%-20s%10d%10d%10d\n", "0","lte_tf",g_bbpinfo.bbpint[BBP_INT_LTETF].irq,\
                    hi_bbp_int_ltetf_status(),g_bbpinfo.bbpint[BBP_INT_LTETF].cnt);
    /*tdstf*/
    bbp_print_dbg("%-10s%-20s%10d%10d%10d\n", "1","tds_tf",g_bbpinfo.bbpint[BBP_INT_TDSTF].irq,\
                    hi_bbp_int_tdstf_status(),g_bbpinfo.bbpint[BBP_INT_TDSTF].cnt);

}
void bbp_int_show(void)
{
    //bbp_print_dbg("bbp lte timer int arm status:%d\n",);/*�鿴armʹ��״̬*/

    bbp_print_dbg("%-10s%-20s%10s%10s\n", "irq_id","irq_name", "irq_num", "irq_cnt");
    /*ltetf*/
    bbp_print_dbg("%-10s%-20s%10d%10d\n", "0","lte_tf",g_bbpinfo.bbpint[BBP_INT_LTETF].irq,\
                    g_bbpinfo.bbpint[BBP_INT_LTETF].cnt);
    /*tdstf*/
    bbp_print_dbg("%-10s%-20s%10d%10d\n", "1","tds_tf",g_bbpinfo.bbpint[BBP_INT_TDSTF].irq,\
                    g_bbpinfo.bbpint[BBP_INT_TDSTF].cnt);

}
void bbp_pwr_reg_show(void)
{
    int i = 0;

    bbp_print_dbg("********************************* pwr clk reg info *********************************\n");

    bbp_print_dbg("%-10s%-20s%-20s%-20s%-20s\n", "pwr_id", "pwr_name", "en_reg","dis_reg","state_reg");

    for(i = BBP_PWR_MIN;i <= BBP_PWR_MAX ;i++)
    {
        bbp_print_dbg("%-10d%-20s%-20x%-20x%-20x\n",g_bbpinfo.pwr.pwr_act[i].pwr_id,g_bbpinfo.pwr.pwr_act[i].name,\
            g_bbpinfo.pwr.pwr_act[i].clk_ctrl.en_reg,g_bbpinfo.pwr.pwr_act[i].clk_ctrl.dis_reg,g_bbpinfo.pwr.pwr_act[i].clk_ctrl.state_reg);
    }

    bbp_print_dbg("%-10s%-20s%-20s%-20s%-20s\n", "pwr_id", "pwr_name", "en_bit","dis_bit","state_bit");

    for(i = BBP_PWR_MIN;i <= BBP_PWR_MAX ;i++)
    {
        bbp_print_dbg("%-10d%-20s%-20d%-20d%-20d\n",g_bbpinfo.pwr.pwr_act[i].pwr_id,g_bbpinfo.pwr.pwr_act[i].name,\
            g_bbpinfo.pwr.pwr_act[i].clk_ctrl.en_bit,g_bbpinfo.pwr.pwr_act[i].clk_ctrl.dis_bit,g_bbpinfo.pwr.pwr_act[i].clk_ctrl.state_bit);
    }

    bbp_print_dbg("********************************* pwr rst reg info *********************************\n");

    bbp_print_dbg("%-10s%-20s%-20s%-20s%-20s\n", "pwr_id", "pwr_name", "en_reg","dis_reg","state_reg");

    for(i = BBP_PWR_MIN;i <= BBP_PWR_MAX ;i++)
    {
        bbp_print_dbg("%-10d%-20s%-20x%-20x%-20x\n",g_bbpinfo.pwr.pwr_act[i].pwr_id,g_bbpinfo.pwr.pwr_act[i].name,\
            g_bbpinfo.pwr.pwr_act[i].rst_ctrl.en_reg,g_bbpinfo.pwr.pwr_act[i].rst_ctrl.dis_reg,g_bbpinfo.pwr.pwr_act[i].rst_ctrl.state_reg);
    }
    bbp_print_dbg("%-10s%-20s%-20s%-20s%-20s\n", "pwr_id", "pwr_name", "en_bit","dis_bit","state_bit");

    for(i = BBP_PWR_MIN;i <= BBP_PWR_MAX ;i++)
    {
        bbp_print_dbg("%-10d%-20s%-20d%-20d%-20d\n",g_bbpinfo.pwr.pwr_act[i].pwr_id,g_bbpinfo.pwr.pwr_act[i].name,\
             g_bbpinfo.pwr.pwr_act[i].rst_ctrl.en_bit,g_bbpinfo.pwr.pwr_act[i].rst_ctrl.dis_bit,g_bbpinfo.pwr.pwr_act[i].rst_ctrl.state_bit);
    }
    bbp_print_dbg("********************************* pwr iso reg info *********************************\n");

    bbp_print_dbg("%-10s%-20s%-20s%-20s%-20s\n", "pwr_id", "pwr_name", "en_reg","dis_reg","state_reg");

    for(i = BBP_PWR_MIN;i <= BBP_PWR_MAX ;i++)
    {
        bbp_print_dbg("%-10d%-20s%-20x%-20x%-20x\n",g_bbpinfo.pwr.pwr_act[i].pwr_id,g_bbpinfo.pwr.pwr_act[i].name,\
            g_bbpinfo.pwr.pwr_act[i].iso_ctrl.en_reg,g_bbpinfo.pwr.pwr_act[i].iso_ctrl.dis_reg,g_bbpinfo.pwr.pwr_act[i].iso_ctrl.state_reg);
    }
    bbp_print_dbg("%-10s%-20s%-20s%-20s%-20s\n", "pwr_id", "pwr_name","en_bit","dis_bit","state_bit");

    for(i = BBP_PWR_MIN;i <= BBP_PWR_MAX ;i++)
    {
        bbp_print_dbg("%-10d%-20s%-20d%-20d%-20d\n",g_bbpinfo.pwr.pwr_act[i].pwr_id,g_bbpinfo.pwr.pwr_act[i].name,\
            g_bbpinfo.pwr.pwr_act[i].iso_ctrl.en_bit,g_bbpinfo.pwr.pwr_act[i].iso_ctrl.dis_bit,g_bbpinfo.pwr.pwr_act[i].iso_ctrl.state_bit);
    }

    bbp_print_dbg("********************************* pwr mos reg info *********************************\n");

    bbp_print_dbg("%-10s%-20s%-20s%-20s%-20s%-20s\n", "pwr_id", "pwr_name", "en_reg","dis_reg","rdy_reg","state_reg");

    for(i = BBP_PWR_MIN;i <= BBP_PWR_MAX ;i++)
    {
        bbp_print_dbg("%-10d%-20s%-20x%-20x%-20x%-20x\n",g_bbpinfo.pwr.pwr_act[i].pwr_id,g_bbpinfo.pwr.pwr_act[i].name,\
            g_bbpinfo.pwr.pwr_act[i].mos_ctrl.en_reg,g_bbpinfo.pwr.pwr_act[i].mos_ctrl.dis_reg,g_bbpinfo.pwr.pwr_act[i].mos_ctrl.rdy_reg,\
            g_bbpinfo.pwr.pwr_act[i].mos_ctrl.state_reg);
    }
    bbp_print_dbg("%-10s%-20s%-20s%-20s%-20s%-20s\n", "pwr_id", "pwr_name","en_bit","dis_bit","rdy_bit","state_bit");

    for(i = BBP_PWR_MIN;i <= BBP_PWR_MAX ;i++)
    {
        bbp_print_dbg("%-10d%-20s%-20d%-20d%-20d%-20d\n",g_bbpinfo.pwr.pwr_act[i].pwr_id,g_bbpinfo.pwr.pwr_act[i].name,\
             g_bbpinfo.pwr.pwr_act[i].mos_ctrl.en_bit,g_bbpinfo.pwr.pwr_act[i].iso_ctrl.dis_bit,g_bbpinfo.pwr.pwr_act[i].mos_ctrl.rdy_bit,\
             g_bbpinfo.pwr.pwr_act[i].mos_ctrl.state_bit);
    }
}
void bbp_clk_reg_show(void)
{
    int i = 0;

    bbp_print_dbg("********************************* clk reg info *********************************\n");

    bbp_print_dbg("%-10s%-20s%-20s%-20s%-20s\n", "clk_id", "clk_name", "en_reg","dis_reg","state_reg");

    for(i = BBP_CLK_MIN;i <= BBP_CLK_MAX ;i++)
    {
        bbp_print_dbg("%-10d%-20s%-20x%-20x%-20x\n",g_bbpinfo.clk.clk_act[i].clk_id,g_bbpinfo.clk.clk_act[i].name,\
            g_bbpinfo.clk.clk_act[i].clk_ctrl.en_reg,g_bbpinfo.clk.clk_act[i].clk_ctrl.dis_reg,g_bbpinfo.clk.clk_act[i].clk_ctrl.state_reg);
    }

    bbp_print_dbg("%-10s%-20s%-20s%-20s%-20s\n", "clk_id", "clk_name","en_bit","dis_bit","state_bit");

    for(i = BBP_CLK_MIN;i <= BBP_CLK_MAX ;i++)
    {
        bbp_print_dbg("%-10d%-20s%-20d%-20d%-20d\n",g_bbpinfo.clk.clk_act[i].clk_id,g_bbpinfo.clk.clk_act[i].name,\
             g_bbpinfo.clk.clk_act[i].clk_ctrl.en_bit,g_bbpinfo.clk.clk_act[i].clk_ctrl.dis_bit,g_bbpinfo.clk.clk_act[i].clk_ctrl.state_bit);
    }

    if(g_bbpinfo.clk.rst_flag)
    {
        bbp_print_dbg("********************************* clk rst reg info *********************************\n");
        bbp_print_dbg("%-10s%-20s%-20s%-20s%-20s\n", "clk_id", "clk_name", "rst_reg","unrst_reg","state_reg");

        for(i = BBP_CLK_MIN;i <= BBP_CLK_MAX ;i++)
        {
            bbp_print_dbg("%-10d%-20s%-20x%-20x%-20x\n",g_bbpinfo.clk.clk_act[i].clk_id,g_bbpinfo.clk.clk_act[i].name,\
                g_bbpinfo.clk.clk_act[i].rst_ctrl.en_reg,g_bbpinfo.clk.clk_act[i].rst_ctrl.dis_reg,g_bbpinfo.clk.clk_act[i].rst_ctrl.state_reg);
        }

        bbp_print_dbg("%-10s%-20s%-20s%-20s%-20s\n", "clk_id", "clk_name","rst_bit","unrst_bit","state_bit");

        for(i = BBP_CLK_MIN;i <= BBP_CLK_MAX ;i++)
        {
            bbp_print_dbg("%-10d%-20s%-20d%-20d%-20d\n",g_bbpinfo.clk.clk_act[i].clk_id,g_bbpinfo.clk.clk_act[i].name,\
                 g_bbpinfo.clk.clk_act[i].rst_ctrl.en_bit,g_bbpinfo.clk.clk_act[i].rst_ctrl.dis_bit,g_bbpinfo.clk.clk_act[i].rst_ctrl.state_bit);
        }
    }
}
/*****************************************************************************
* �� �� : bbp_state_get
* �� �� : ��ȡbbp���ӡ��硢��λ��Ƕλ��ǰ״̬
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
void bbp_pwr_state_show(void)
{
    u32 i = 0;
    unsigned int status = 0;
    //unsigned int status_rst = 0;
    //unsigned int status_iso = 0;
    //unsigned int status_clk = 0;
    //unsigned int status_mos = 0;

    bbp_print_dbg("%-10s%-20s%-20s\n", "pwr_id", "pwr_name", "pwr_state");

    for(i = 0;i <= BBP_PWR_MAX ;i++)
    {
        status = bbp_pwrctrl_is_enabled(i);
        bbp_print_dbg("%-10d%-20s%-20d%\n",i,g_bbpinfo.pwr.pwr_act[i].name,status);
    }
    #if 0
    bbp_print_dbg("%-10s%-20s%-20s%-20s%-20s%-20s\n", "pwr_id", "pwr_name", "rst_state","iso_state","clk_state","mos_state");
    for(i = 0;i <= BBP_PWR_MAX ;i++)
    {
        status_rst = bbp_pwr_rst_status(i);
        status_iso = bbp_pwr_iso_status(i);
        status_clk = bbp_pwr_clk_status(i);
        status_mos = bbp_pwr_cmos_status(i);
        bbp_print_dbg("%-10d%-20s%-20d%-20d%-20d%-20d\n",i,g_bbpinfo.pwr.pwr_act[i].name,status_rst,status_iso,status_clk,status_mos);
    }
    #endif
}
void bbp_clk_state_show(void)
{
    u32 i = 0;
    unsigned int status = 0;
    unsigned int status_clk = 0;
    unsigned int status_rst = 0;

    bbp_print_dbg("%-10s%-20s%-10s\n", "clk_id", "clk_name", "clk_state");

    for(i = 0;i <= BBP_CLK_MAX ;i++)
    {
        status = (unsigned int)bbp_clkctrl_status(i);
        if(g_bbpinfo.clk.rst_flag)
            status &= (unsigned int)bbp_rstctrl_status(i);
        bbp_print_dbg("%-10d%-20s%-10d\n",i,g_bbpinfo.clk.clk_act[i].name,status);
    }

    if(g_bbpinfo.clk.rst_flag)
    {
        bbp_print_dbg("%-10s%-20s%-20s%-20s\n", "clk_id", "clk_name","clk_state", "rst_state");
        for(i = 0;i <= BBP_CLK_MAX ;i++)
        {
            status_clk = bbp_clkctrl_is_enabled(i);
            status_rst = bbp_rstctrl_is_enabled(i);
            bbp_print_dbg("%-10d%-20s%-20d%-20d%\n",i,g_bbpinfo.clk.clk_act[i].name,status_clk,status_rst);
        }
    }
}

void bbp_pwrmap_show(void)
{
    u32 mode_id,module_id,modem_id = 0;
    u32 enModeId,enModuleId,enModemId = 0;
    u32 pwr_id = 0;
    u32 i = 0;


    bbp_print_dbg("*************************bbp pwr map********************************\n");
    bbp_print_dbg("%-10s%-10s%-10s%-30s\n", "module_id", "modem_id", "mode_id", "pwr_id(name)");
    for(enModuleId = BBP_PWC_MODULE_MIN;enModuleId <= BBP_PWC_MODULE_MAX; enModuleId++)
    {
        for(enModemId = BBP_PWC_MODEM_MIN;enModemId <= BBP_PWC_MODEM_MAX; enModemId++)/*lint !e775*/
        {
            for(enModeId = BBP_PWC_MODE_MIN;enModeId <= BBP_PWC_MODE_MAX;enModeId++)
            {
                bbp_print_dbg("%-10d%-10d%-10d",enModuleId,enModemId,enModeId);
                mode_id = enModeId - BBP_PWC_MODE_MIN;
                modem_id = enModemId - BBP_PWC_MODEM_MIN;
                module_id = enModuleId - BBP_PWC_MODULE_MIN;

                for (i = 0 ;i < BBP_VOTE_PWR_NUM ;i++ )
                {
                    pwr_id = g_bbpinfo.pwr.pwr_list[module_id][modem_id][mode_id].pwc_pwr[i];

                    if (BBP_PWC_NULL == pwr_id)
                    {
                        if(i == 0)
                            bbp_print_dbg("%-10s\n","pwr_null");/*û����Ҫ�����ĵ�Դ��*/
                        else
                            bbp_print_dbg("\n");/*��Դ������ʾ���*/
                        break;
                    }
                    else
                    {
                        bbp_print_dbg("%-10d%-20s",pwr_id,g_bbpinfo.pwr.pwr_act[pwr_id].name);
                    }
                }
            }
        }
    }
}
void bbp_clkmap_show(void)
{
    u32 mode_id,module_id,modem_id = 0;
    u32 enModeId,enModuleId,enModemId = 0;
    u32 clk_id = 0;
    u32 i = 0;


    bbp_print_dbg("*************************bbp clk map********************************\n");
    bbp_print_dbg("%-10s%-10s%-10s%-30s\n", "module_id", "modem_id", "mode_id", "clk_id(name)");
    for(enModuleId = BBP_PWC_MODULE_MIN;enModuleId <= BBP_PWC_MODULE_MAX; enModuleId++)
    {
        for(enModemId = BBP_PWC_MODEM_MIN;enModemId <= BBP_PWC_MODEM_MAX; enModemId++)/*lint !e775*/
        {
            for(enModeId = BBP_PWC_MODE_MIN;enModeId <= BBP_PWC_MODE_MAX;enModeId++)
            {
                bbp_print_dbg("%-10d%-10d%-10d",enModuleId,enModemId,enModeId);
                mode_id = enModeId - BBP_PWC_MODE_MIN;
                modem_id = enModemId - BBP_PWC_MODEM_MIN;
                module_id = enModuleId - BBP_PWC_MODULE_MIN;

                for (i = 0 ;i < BBP_VOTE_CLK_NUM ;i++ )
                {
                    clk_id = g_bbpinfo.clk.clk_list[module_id][modem_id][mode_id].pwc_clk[i];

                    if (BBP_PWC_NULL == clk_id)
                    {
                        if(i == 0)
                            bbp_print_dbg("%-10s\n","clk_null");/*û����Ҫ������ʱ����*/
                        else
                            bbp_print_dbg("\n");/*ʱ��������ʾ���*/
                        break;
                    }
                    else
                    {
                        bbp_print_dbg("%-10d%-20s",clk_id,g_bbpinfo.clk.clk_act[clk_id].name);
                    }
                }
            }
        }
    }
}

void bbp_map_show(void)
{
    bbp_pwrmap_show();
    bbp_clkmap_show();
}
/*****************************************************************************
* �� �� : bbp_clk_vote_debug
* �� �� : bbp ʱ��ͶƱ��Ϣ
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
u32 bbp_vote_bit_get(BBP_VOTE_ID_E vote_id, u32 module_id, u32 modem_id, u32 mode_id)
{
    u32 vote_bit = 0;

    switch(vote_id){
    case BBP_VOTE_PWR:
        vote_bit = BBP_MODE_NUM*modem_id + mode_id;
        break;
    case BBP_VOTE_CLK:
        vote_bit = BBP_MODE_NUM*BBP_MODEM_NUM*module_id + BBP_MODE_NUM*modem_id + mode_id;
        break;
    case BBP_VOTE_PLL:
        vote_bit = BBP_MODE_NUM*modem_id + mode_id;
        break;
    default:
        bbp_print_dbg("note support this vote!");
        break;
    }

    return vote_bit;
}
BBP_VOTE_LOCK_E bbp_vote_lock_get(BBP_VOTE_ID_E vote_id, u32 dev_id, u32 module_id, u32 modem_id, u32 mode_id)
{
    u32 vote_bit = 0;
    u64 vote_lock = 0;

    switch(vote_id){
    case BBP_VOTE_PWR:
        vote_lock = g_bbpinfo.om->pwr[dev_id].lock;
        vote_bit = (BBP_MODE_NUM*modem_id + mode_id);
        break;
    case BBP_VOTE_CLK:
        vote_lock = g_bbpinfo.om->clk[dev_id].lock;
        vote_bit = BBP_MODE_NUM*BBP_MODEM_NUM*module_id + BBP_MODE_NUM*modem_id + mode_id;
        break;
    case BBP_VOTE_PLL:
        vote_lock = g_bbpinfo.om->pll.lock;
        vote_bit = (BBP_MODE_NUM*modem_id + mode_id);
        break;
    default:
        bbp_print_dbg("note support this vote!");
        break;
    }

    if(vote_lock & ((u64)0x1 << vote_bit))
        return BBP_VOTE_LOCK;
    else
        return BBP_VOTE_UNLOCK;
}

void bbp_clk_vote_show(void)
{
    u32 enModeId,enModuleId,enModemId = 0;
    u32 mode_id,module_id,modem_id,clk_id,vote_clk_id = 0;
    BBP_VOTE_LOCK_E lock_state = BBP_VOTE_UNLOCK;
    u32 enable_votes,disable_votes = 0;

    for(clk_id = BBP_VOTE_CLK_MIN;clk_id <= BBP_VOTE_CLK_MAX ;clk_id++)
    {
        bbp_print_dbg("*****************clk %d:%10s vote info***********************\n",clk_id,g_bbpinfo.clk.clk_act[clk_id].name);
        bbp_print_dbg("%-10s%-10s%-10s%-10s%-10s%-10s\n","module", "modem", "mode", "lock","en_votes","dis_votes");

        for(enModuleId = BBP_PWC_MODULE_MIN;enModuleId <= BBP_PWC_MODULE_MAX;enModuleId++)
        {
            for(enModemId = BBP_PWC_MODEM_MIN;enModemId <= BBP_PWC_MODEM_MAX;enModemId++)/*lint !e775*/
            {
                for(enModeId = BBP_PWC_MODE_MIN;enModeId <= BBP_PWC_MODE_MAX;enModeId++)
                {
                    mode_id = enModeId - BBP_PWC_MODE_MIN;
                    modem_id = enModemId - BBP_PWC_MODEM_MIN;
                    module_id = enModuleId - BBP_PWC_MODULE_MIN;
                    vote_clk_id = clk_id - BBP_VOTE_CLK_MIN;

                    lock_state = bbp_vote_lock_get(BBP_VOTE_CLK,vote_clk_id,module_id,modem_id,mode_id);
                    enable_votes = g_bbpinfo.om->clk[vote_clk_id].enable_vote[module_id][modem_id][mode_id];
                    disable_votes = g_bbpinfo.om->clk[vote_clk_id].disable_vote[module_id][modem_id][mode_id];
                    bbp_print_dbg("%-10d%-10d%-10d%-10d%-10d%-10d\n",module_id,modem_id,mode_id,lock_state,enable_votes,disable_votes);
                }
            }
        }
    }
}
void bbp_pwr_vote_show(void)
{
    u32 enModeId,enModuleId,enModemId = 0;
    u32 mode_id,module_id,modem_id,pwr_id,vote_pwr_id = 0;
    BBP_VOTE_LOCK_E lock_state = BBP_VOTE_UNLOCK;
    u32 enable_votes,disable_votes = 0;

    for(pwr_id = BBP_VOTE_PWR_MIN;pwr_id <= BBP_VOTE_PWR_MAX ;pwr_id++)
    {
        bbp_print_dbg("*****************pwr %d:%10s vote info***********************\n",pwr_id,g_bbpinfo.pwr.pwr_act[pwr_id].name);
        bbp_print_dbg("%-10s%-10s%-10s%-10s%-10s\n", "modem","mode", "lock","en_votes","dis_votes");

        for(enModuleId = BBP_PWC_MODULE_MIN;enModuleId <= BBP_PWC_MODULE_MAX;enModuleId++)
        {
            for(enModemId = BBP_PWC_MODEM_MIN;enModemId <= BBP_PWC_MODEM_MAX;enModemId++)/*lint !e775*/
            {
                for(enModeId = BBP_PWC_MODE_MIN;enModeId <= BBP_PWC_MODE_MAX;enModeId++)
                {
                    mode_id = enModeId - BBP_PWC_MODE_MIN;
                    modem_id = enModemId - BBP_PWC_MODEM_MIN;
                    module_id = enModuleId - BBP_PWC_MODULE_MIN;
                    vote_pwr_id = pwr_id-BBP_VOTE_PWR_MIN;

                    lock_state = bbp_vote_lock_get(BBP_VOTE_PWR,vote_pwr_id,module_id,modem_id,mode_id);
                    enable_votes = g_bbpinfo.om->pwr[vote_pwr_id].enable_vote[module_id][modem_id][mode_id];
                    disable_votes = g_bbpinfo.om->pwr[vote_pwr_id].disable_vote[module_id][modem_id][mode_id];
                    bbp_print_dbg("%-10d%-10d%-10d%-10d%-10d\n",modem_id,mode_id,lock_state,enable_votes,disable_votes);
                }
            }
        }
    }
}

void bbp_vote_show(void)
{
    bbp_pwr_vote_show();
    bbp_clk_vote_show();
}

void bbp_ltetf_stamp_show(void)
{
    /*lte tf*/
    bbp_print_dbg("%-30s,0x%-20x \n","BBP_LTEINT_EN_IN"           ,g_bbpinfo.om->stamp_ltetf[BBP_LTEINT_EN_IN]);
    bbp_print_dbg("%-30s,0x%-20x \n","BBP_LTEINT_EN_CLS"          ,g_bbpinfo.om->stamp_ltetf[BBP_LTEINT_EN_CLS]);
    bbp_print_dbg("%-30s,0x%-20x \n","BBP_LTEINT_EN_UNMASK"       ,g_bbpinfo.om->stamp_ltetf[BBP_LTEINT_EN_UNMASK]);
    bbp_print_dbg("%-30s,0x%-20x \n","BBP_LTEINT_DIS_IN"          ,g_bbpinfo.om->stamp_ltetf[BBP_LTEINT_DIS_IN]);
    bbp_print_dbg("%-30s,0x%-20x \n","BBP_LTEINT_DIS_MASK"        ,g_bbpinfo.om->stamp_ltetf[BBP_LTEINT_DIS_MASK]);
    bbp_print_dbg("%-30s,0x%-20x \n","BBP_LTEINT_HANDLE_FUNC"     ,g_bbpinfo.om->stamp_ltetf[BBP_LTEINT_HANDLE_FUNC]);
    bbp_print_dbg("%-30s,0x%-20x \n","BBP_LTEINT_CLEAR_IN"        ,g_bbpinfo.om->stamp_ltetf[BBP_LTEINT_CLEAR_IN]);
    bbp_print_dbg("%-30s,0x%-20x \n","BBP_LTEINT_CLEAR_CLS"       ,g_bbpinfo.om->stamp_ltetf[BBP_LTEINT_CLEAR_CLS]);
}
void bbp_tdstf_stamp_show(void)
{
    /*tds tf*/
    bbp_print_dbg("%-30s,0x%-20x \n","BBP_TDSINT_EN_IN"           ,g_bbpinfo.om->stamp_tdstf[BBP_TDSINT_EN_IN]);
    bbp_print_dbg("%-30s,0x%-20x \n","BBP_TDSINT_EN_CLS"          ,g_bbpinfo.om->stamp_tdstf[BBP_TDSINT_EN_CLS]);
    bbp_print_dbg("%-30s,0x%-20x \n","BBP_TDSINT_EN_UNMASK"       ,g_bbpinfo.om->stamp_tdstf[BBP_TDSINT_EN_UNMASK]);
    bbp_print_dbg("%-30s,0x%-20x \n","BBP_TDSINT_DIS_IN"          ,g_bbpinfo.om->stamp_tdstf[BBP_TDSINT_DIS_IN]);
    bbp_print_dbg("%-30s,0x%-20x \n","BBP_TDSINT_DIS_MASK"        ,g_bbpinfo.om->stamp_tdstf[BBP_TDSINT_DIS_MASK]);
    bbp_print_dbg("%-30s,0x%-20x \n","BBP_TDSINT_HANDLE_FUNC"     ,g_bbpinfo.om->stamp_tdstf[BBP_TDSINT_HANDLE_FUNC]);
    bbp_print_dbg("%-30s,0x%-20x \n","BBP_TDSINT_CLEAR_IN"        ,g_bbpinfo.om->stamp_tdstf[BBP_TDSINT_CLEAR_IN]);
    bbp_print_dbg("%-30s,0x%-20x \n","BBP_TDSINT_CLEAR_CLS"       ,g_bbpinfo.om->stamp_tdstf[BBP_TDSINT_CLEAR_CLS]);
}
void bbp_pwr_stamp_show(void)
{
    int i = 0;

    bbp_print_dbg("%-20s,%-30s,%-20s,%-20s \n","pwr_id","pwr_name","pwron","pwroff");

    for(i = 0; i < BBP_VOTE_PWR_NUM; i++)
    {
        bbp_print_dbg("%-20d,%-30s,0x%-20x,0x%-20x \n",(i + BBP_VOTE_PWR_MIN),g_bbpinfo.pwr.pwr_act[i + BBP_VOTE_PWR_MIN].name,g_bbpinfo.om->stamp_pwron[i],g_bbpinfo.om->stamp_pwroff[i]);
    }
}
void bbp_clk_stamp_show(void)
{
    int i = 0;

    bbp_print_dbg("%-20s,%-30s,%-22s,%-20s \n","clk_id","clk_name","clkon","clkoff");

    for(i = 0; i < BBP_VOTE_CLK_NUM; i++)
    {
        bbp_print_dbg("%-20d,%-30s,0x%-20x,0x%-20x \n",(i + BBP_VOTE_CLK_MIN),g_bbpinfo.clk.clk_act[i + BBP_VOTE_CLK_MIN].name,g_bbpinfo.om->stamp_clkon[i],g_bbpinfo.om->stamp_clkoff[i]);
    }
}
void bbp_dpm_stamp_show(void)
{
    bbp_print_dbg("%-30s,0x%-20x \n","BBP_PREPAIR_IN"            ,g_bbpinfo.om->stamp_tdstf[BBP_PREPAIR_IN]);
    bbp_print_dbg("%-30s,0x%-20x \n","BBP_PREPAIR_END"           ,g_bbpinfo.om->stamp_tdstf[BBP_PREPAIR_END]);
    bbp_print_dbg("%-30s,0x%-20x \n","BBP_SUSPEND_IN"            ,g_bbpinfo.om->stamp_tdstf[BBP_SUSPEND_IN]);
    bbp_print_dbg("%-30s,0x%-20x \n","BBP_SUSPEND_BBCRST"        ,g_bbpinfo.om->stamp_tdstf[BBP_SUSPEND_BBCRST]);
    bbp_print_dbg("%-30s,0x%-20x \n","BBP_SUSPEND_END"           ,g_bbpinfo.om->stamp_tdstf[BBP_SUSPEND_END]);

    bbp_print_dbg("%-30s,0x%-20x \n","BBP_RESUME_IN"             ,g_bbpinfo.om->stamp_tdstf[BBP_RESUME_IN]);
    bbp_print_dbg("%-30s,0x%-20x \n","BBP_RESUME_BBCUNRST"       ,g_bbpinfo.om->stamp_tdstf[BBP_RESUME_BBCUNRST]);
    bbp_print_dbg("%-30s,0x%-20x \n","BBP_RESUME_END"            ,g_bbpinfo.om->stamp_tdstf[BBP_RESUME_END]);
    bbp_print_dbg("%-30s,0x%-20x \n","BBP_COMPLETE_IN"           ,g_bbpinfo.om->stamp_tdstf[BBP_COMPLETE_IN]);
    bbp_print_dbg("%-30s,0x%-20x \n","BBP_COMPLETE_END"          ,g_bbpinfo.om->stamp_tdstf[BBP_COMPLETE_END]);
}
void bbp_dma_stamp_show(void)
{
    bbp_print_dbg("%-30s,0x%-20x \n","BBP_DMATRAN_IN"            ,g_bbpinfo.om->stamp_tdstf[BBP_DMATRAN_IN]);
    bbp_print_dbg("%-30s,0x%-20x \n","BBP_DMATRAN_CLKEN"         ,g_bbpinfo.om->stamp_tdstf[BBP_DMATRAN_CLKEN]);
    bbp_print_dbg("%-30s,0x%-20x \n","BBP_DMATRAN_ADDR"          ,g_bbpinfo.om->stamp_tdstf[BBP_DMATRAN_ADDR]);
    bbp_print_dbg("%-30s,0x%-20x \n","BBP_DMATRAN_END"           ,g_bbpinfo.om->stamp_tdstf[BBP_DMATRAN_END]);
    bbp_print_dbg("%-30s,0x%-20x \n","BBP_DMAFINISH_IN"          ,g_bbpinfo.om->stamp_tdstf[BBP_DMAFINISH_IN]);
    bbp_print_dbg("%-30s,0x%-20x \n","BBP_DMAFINISH_BUSY"        ,g_bbpinfo.om->stamp_tdstf[BBP_DMAFINISH_BUSY]);
    bbp_print_dbg("%-30s,0x%-20x \n","BBP_DMAFINISH_END"         ,g_bbpinfo.om->stamp_tdstf[BBP_DMAFINISH_END]);
    bbp_print_dbg("%-30s,0x%-20x \n","BBP_DMACONFIG"             ,g_bbpinfo.om->stamp_tdstf[BBP_DMACONFIG]);
}
void bbp_stamp_show(void)
{
    bbp_ltetf_stamp_show();
    bbp_tdstf_stamp_show();
    bbp_dpm_stamp_show();
    bbp_dma_stamp_show();
    bbp_pwr_stamp_show();
    bbp_clk_stamp_show();
}
/*****************************************************************************
* �� �� : bbp_debug_help
* �� �� : bbp debug�ӿ����˵��
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
void bbp_debug_help(void)
{
    bbp_print_dbg("bbp_log_set(u32 level) : bbp ��ش�ӡ�ȼ�����\n");
    bbp_print_dbg("bbp_log_get : ��ȡbbp ��ش�ӡ�ȼ�\n");
    bbp_print_dbg("bbp_time_enable :  �򿪼�ʱ����\n");
    bbp_print_dbg("bbp_time_disable : �رռ�ʱ����\n");
    bbp_print_dbg("bbp_dma_enable :  ���ݱ��ݻָ�ʱ����dma����\n");
    bbp_print_dbg("bbp_dma_disable : ���ݱ��ݻָ�ʱ����memcpy ����\n");

    bbp_print_dbg("bbp_part_show : ��ȡbbp����ַ����Ϣ\n");
    bbp_print_dbg("bbp_pwrid_show : ��ȡbbp����Դ�ж�Ӧid��\n");
    bbp_print_dbg("bbp_clkid_show : ��ȡbbp��ʱ���ж�Ӧid��\n");
    bbp_print_dbg("bbp_int_debug : bbp �ж������Ϣ\n");
    bbp_print_dbg("bbp_int_show : bbp �жϺż��жϼ�����Ϣ\n");
    bbp_print_dbg("bbp_pwr_reg_show : ��ȡbbp�ĵ�Դ�мĴ�����Ϣ\n");
    bbp_print_dbg("bbp_clk_reg_show : ��ȡbbp��ʱ���мĴ�����Ϣ\n");
    bbp_print_dbg("bbp_clk_state_show : ��ȡbbp���ӵ�ǰ״̬\n");
    bbp_print_dbg("bbp_pwr_state_show : ��ȡbbp�ĵ統ǰ״̬\n");
    bbp_print_dbg("bbp_clk_vote_show :  bbp ʱ��ͶƱ��Ϣ\n");
    bbp_print_dbg("bbp_pwr_vote_show : bbp ��ԴͶƱ��Ϣ\n");
    bbp_print_dbg("bbp_vote_show :  bbp ͶƱ��Ϣ\n");
    bbp_print_dbg("bbp_map_show :  bbp ��Դ��ʱ����pll�п��Ʊ���Ϣ\n");
    bbp_print_dbg("bbp_stamp_show :  bbp ʱ�����Ϣ\n");
}
/*lint -restore*/