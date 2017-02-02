
/*lint --e{537}*/
//#include "mdrv_bbp.h"
//#include "mdrv_pm.h"
#include "osl_bio.h"
#include "product_config.h"
#include <bsp_version.h>
#include "hi_bbp.h"

#include "bsp_bbp.h"
#include "bbp_balong.h"

#ifdef CONFIG_BBP
/*�ϲ�ģ�����*/
/*****************************************************************************
* ����  : mdrv_bbp_register_lte_intr_cb
* ����  : ��PS���ã����������ע��lte 1ms��ʱ��֡�жϵĻص�
* ����  : pfunc
* ���  : void
* ����  : void
*****************************************************************************/
void mdrv_bbp_register_lte_intr_cb (BSPBBPIntTimerFunc pFunc)
{
    bbp_int_ltetf_regcb(pFunc);
}

/*****************************************************************************
* �� ��: mdrv_bbp_enable_lte_intr
* �� ��: ��PS���ã�������lte 1ms��ʱ��֡�ж�
* ���� : void
* ��� : void
* ���� : int
*****************************************************************************/
int mdrv_bbp_enable_lte_intr(void)
{
    return bbp_int_ltetf_enable();
}

/*****************************************************************************
* �� ��: mdrv_bbp_disable_lte_intr
* �� ��: ��PS���ã������ر�lte 1ms��ʱ��֡�ж�
* ���� : void
* ��� : void
* �� ��: void
*****************************************************************************/
void mdrv_bbp_disable_lte_intr(void)
{
    bbp_int_ltetf_disable();
}

/*****************************************************************************
* �� ��: mdrv_bbp_clear_lte_intr
* �� ��: ��PS���ã��������lte 1ms��ʱ��֡�ж�
* ���� : void
* ��� : void
* �� ��: void
*****************************************************************************/
void mdrv_bbp_clear_lte_intr(void)
{
    bbp_int_ltetf_clear();
}
/*****************************************************************************
* ����  : mdrv_bbp_get_lte_sysfrm
* ����  : get system frame num
* ����  : void
* ���  : void
* ����  : u16
*****************************************************************************/
unsigned short mdrv_bbp_get_lte_sysfrm(void)
{
    return bbp_get_lte_sysframe();
}

/*****************************************************************************
* ����  : mdrv_bbp_get_lte_subfrm
* ����  : get system sub frame num
* ����  : void
* ���  : void
* ����  : u16
*****************************************************************************/
unsigned short mdrv_bbp_get_lte_subfrm(void)
{
    return bbp_get_lte_subframe();
}

/*****************************************************************************
* ����  : mdrv_bbp_get_tds_subfrm
* ����  : get tds system sub frame num
* ����  : void
* ���  : void
* ����  : u32
*****************************************************************************/
unsigned short mdrv_bbp_get_tds_subfrm(void)
{
    return bbp_get_tds_subframe();
}
/*****************************************************************************
* ����  : mdrv_bbp_set_tds_subfrm_offset
* ����  : set tds system sub frame offset
* ����  : void
* ���  : void
* ����  : u32
*****************************************************************************/
unsigned short mdrv_bbp_set_tds_subfrm_offset(unsigned short usOffset)
{
    return bbp_set_tds_subframe_offset(usOffset);
}
/*****************************************************************************
* ����  : mdrv_bbp_get_sleep_period
* ����  : get sleep period(
* ����  : void
* ���  : void
* ����  : u32
*****************************************************************************/
unsigned int mdrv_bbp_get_sleep_period(void)
{
    return bbp_get_tds_sleeptime();
}

/*****************************************************************************
* ����  : mdrv_bbp_register_tdstf_intr_cb
* ����  : regist callback
* ����  : void
* ���  : void
* ����  : void
*****************************************************************************/
void mdrv_bbp_register_tdstf_intr_cb(BSPBBPIntTdsFunc pFunc)
{
    bbp_int_tdstf_regcb(pFunc);
}

/*****************************************************************************
* ����  : mdrv_bbp_enable_tdstf_intr
* ����  : enable tdstf
* ����  : void
* ���  : viod
* ����  : u32
*****************************************************************************/
int mdrv_bbp_enable_tdstf_intr(void)
{
    return bbp_int_tdstf_enable();
}

/*****************************************************************************
* ����  : mdrv_bbp_disable_tdstf_intr
* ����  : disable tdstf
* ����  : void
* ���  : void
* ����  : void
*****************************************************************************/
void mdrv_bbp_disable_tdstf_intr(void)
{
    bbp_int_tdstf_disable();
}

/*****************************************************************************
* ����  : BSP_GetTdsClkSwitchStatus
* ����  : get tdsclk switch
* ����  : void
* ���  : 0��ʾ�л���ϵͳʱ�ӣ�1��ʾ�л���32kʱ��
* ����  : void
*****************************************************************************/
unsigned int mdrv_bbp_get_tds_clkswitchflag(void)
{
    return bbp_get_tds_clkswitch();
}

/*****************************************************************************
* ����  : mdrv_bbp_enable_wakeup_intr
* ����  : enable bbp wakeup int
* ����  : void
* ���  : void
* ����  : void
*****************************************************************************/
void mdrv_bbp_enable_wakeup_intr(PWC_COMM_MODE_E mode)
{
    bbp_int_wakeup_enable(mode);
}

/*****************************************************************************
* ����  : mdrv_bbp_disable_wakeup_intr
* ����  : disable bbp wakeup int
* ����  : void
* ���  : void
* ����  : void
*****************************************************************************/
void mdrv_bbp_disable_wakeup_intr(PWC_COMM_MODE_E mode)
{
    bbp_int_wakeup_disable(mode);
}

/*****************************************************************************
* ����  : mdrv_bbp_clear_wakeup_intr
* ����  : clear bbp wakeup int
* ����  : void
* ���  : void
* ����  : void
*****************************************************************************/
void mdrv_bbp_clear_wakeup_intr(PWC_COMM_MODE_E mode)
{
    bbp_int_wakeup_clear(mode);
}

/*****************************************************************************
Function:   mdrv_bbp_get_measure_flag
Description:GET CTU MEASURE FLAG
Input:
Output:     the means flag value;
Return:
Others:
*****************************************************************************/
int mdrv_bbp_get_measure_flag(PWC_COMM_MODE_E enCommMode)
 {
    return bbp_get_meansflag(enCommMode);
 }
/*****************************************************************************
* ����  : mdrv_bbp_register_dltb_intr_cb
* ����  : ��PS���ã����������ע������������������жϵĻص�
* ����  : pfunc
* ���  : void
* ����  : void
* ˵��  :v7r5�и��жϲ���arm�д�����ֱ�Ӵ�׮
*****************************************************************************/
void mdrv_bbp_register_dltb_intr_cb(BSPBBPIntDlTbFunc pFunc)
{
    return;
}
/*****************************************************************************
* �� �� : bsp_bbp_lps_get_ta
* �� �� : ��lps����,�鿴������֡ͷ���ϵͳ��֡ͷ����ǰ��
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
int mdrv_bbp_get_lte_ta(void)
{
    return bbp_lps_get_ta();
}
/*****************************************************************************
* �� �� : int mdrv_bbp_init_intr
* �� �� : �ҽ�BBP��֡�ж�(T ��L)
* �� �� : void
* �� �� : void
* �� �� : 0Ϊ�ɹ���-1ʧ��
* ˵ �� :
*****************************************************************************/
int mdrv_bbp_init_intr(PWC_COMM_MODE_E mode)
{
    return bbp_int_timer_init(mode);
}
/*****************************************************************************
* �� �� ��  : mdrv_bbp_get_wakeup_time
*
* ��������  : ��ȡdsp����ʱ��
*
* �������  : mode:ģʽ lte or tds
* �������  : void
*
* �� �� ֵ  : ��λΪ32.768KHzʱ�Ӽ���
*
* ����˵��  :
*
*****************************************************************************/
unsigned int mdrv_bbp_get_wakeup_time(PWC_COMM_MODE_E mode)
{
    return bbp_get_wakeup_time(mode);
}
/*****************************************************************************
* �� �� ��  : mdrv_bbp_get_timing_val
*
* ��������  : Lģ��ϵͳʱ���32K��ʱ��ѯ
*
* �������  : pstTiming�ṹ��ָ��
* �������  : pstTiming�ṹ�嶨ʱֵ
*
* �� �� ֵ  : 0�ɹ�������ʧ��
*
* ����˵��  :�ڲ����жϣ���֤�������̲������
*
*****************************************************************************/
int mdrv_bbp_get_timing_val (BBP_TIMING_STRU *pstTiming)
{
    return bbp_get_timing_val(pstTiming);
}

/***************************************************************************
 �� �� ��  : DRV_PWRCTRL_BBPCLKENABLE()
 ��������  : ��bbp���ʱ��
 �������  : enModeId      Э��ģʽ
             enModuleId    ����ģ��
             enModemId     ����
             enChannel     channel���
 �������  : ��
 �� �� ֵ  : BBP_OK         �ɹ�
             ����           ʧ��
**************************************************************************/
int mdrv_pm_enable_bbpclk (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    /* p532 fpgaƽ̨��׮ */
    if(BSP_BOARD_TYPE_BBIT == bsp_get_version_info()->board_type)
    {
        return 0;
    }

    return bbp_clk_enable(enModeId, enModuleId, enModemId);
}
/***************************************************************************
 �� �� ��  : mdrv_pm_disable_bbpclk()
 ��������  : ͨ��ģ�����BBPģ�����
 �������  : enModeId      Э��ģʽ
             enModuleId    ����ģ��
             enModemId     ����
             enChannel     channel���
 �������  : ��
 �� �� ֵ  : BBP_OK         �ɹ�
             ����           ʧ��
**************************************************************************/
int mdrv_pm_disable_bbpclk (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    /* p532 fpgaƽ̨��׮ */
    if(BSP_BOARD_TYPE_BBIT == bsp_get_version_info()->board_type)
    {
        return 0;
    }

    
    return bbp_clk_disable(enModeId, enModuleId, enModemId);
}
/***************************************************************************
 �� �� ��  : mdrv_pm_gbbp_select_clksrc()
 ��������  : gbbpͨ��ѡ��
 �������  : enModemId     ����(0/2--g0;1--g1;��������ʧ��)
             enChannel     channel���(0--chan0,1--chan1,��Ч����������ʧ��)
 �������  : ��
 �� �� ֵ  : BBP_OK         �ɹ�
             ����           ʧ��
**************************************************************************/
int mdrv_pm_gbbp_select_clksrc (PWC_COMM_MODEM_E enModemId,PWC_COMM_CHANNEL_E enChannel)
{
    return bbp_gbbp_select_clksrc(enModemId,enChannel);
}
/*�������ģ���׮*/
#else
/*�ϲ�ģ�����׮�ӿ�*/
/*****************************************************************************
* ����  : mdrv_bbp_register_lte_intr_cb
* ����  : ��PS���ã����������ע��lte 1ms��ʱ��֡�жϵĻص�
* ����  : pfunc
* ���  : void
* ����  : void
*****************************************************************************/
void mdrv_bbp_register_lte_intr_cb (BSPBBPIntTimerFunc pFunc)
{
    return ;
}

/*****************************************************************************
* �� ��: mdrv_bbp_clear_lte_intr
* �� ��: ��PS���ã��������lte 1ms��ʱ��֡�ж�
* ���� : void
* ��� : void
* �� ��: void
*****************************************************************************/
void mdrv_bbp_clear_lte_intr(void)
{
    return ;
}

/*****************************************************************************
* �� ��: mdrv_bbp_enable_lte_intr
* �� ��: ��PS���ã�������lte 1ms��ʱ��֡�ж�
* ���� : void
* ��� : void
* ���� : int
*****************************************************************************/
int mdrv_bbp_enable_lte_intr(void)
{
    return (BSP_S32)-1;
}

/*****************************************************************************
* �� ��: mdrv_bbp_disable_lte_intr
* �� ��: ��PS���ã������ر�lte 1ms��ʱ��֡�ж�
* ���� : void
* ��� : void
* �� ��: void
*****************************************************************************/
void mdrv_bbp_disable_lte_intr(void)
{
    return ;
}

/*****************************************************************************
* ����  : mdrv_bbp_register_tdstf_intr_cb
* ����  : regist callback
* ����  : void
* ���  : void
* ����  : void
*****************************************************************************/
void mdrv_bbp_register_tdstf_intr_cb(BSPBBPIntTdsFunc pFunc)
{
    return ;
}

/*****************************************************************************
* ����  : mdrv_bbp_enable_tdstf_intr
* ����  : enable tdstf
* ����  : void
* ���  : viod
* ����  : u32
*****************************************************************************/
int mdrv_bbp_enable_tdstf_intr(void)
{
    return (BSP_S32)0;
}

/*****************************************************************************
* ����  : mdrv_bbp_disable_tdstf_intr
* ����  : disable tdstf
* ����  : void
* ���  : void
* ����  : void
*****************************************************************************/
void mdrv_bbp_disable_tdstf_intr(void)
{
    return ;
}
/*****************************************************************************
* ����  : mdrv_bbp_get_lte_sysfrm
* ����  : get system frame num
* ����  : void
* ���  : void
* ����  : u32
*****************************************************************************/
unsigned short mdrv_bbp_get_lte_sysfrm(void)
{
    return (BSP_U16)0;
}

/*****************************************************************************
* ����  : mdrv_bbp_get_lte_subfrm
* ����  : get system sub frame num
* ����  : void
* ���  : void
* ����  : u32
*****************************************************************************/
unsigned short mdrv_bbp_get_lte_subfrm(void)
{
    return (BSP_U16)0;
}

/*****************************************************************************
* ����  : BSP_GetTdsSubFrame
* ����  : get tds system sub frame num
* ����  : void
* ���  : void
* ����  : u32
*****************************************************************************/
unsigned short mdrv_bbp_get_tds_subfrm(void)
{
    return (BSP_U16)0;
}
/*****************************************************************************
* ����  : bsp_bbp_set_tds_subframe_offset
* ����  : set tds system sub frame offset
* ����  : void
* ���  : void
* ����  : u32
*****************************************************************************/
unsigned short mdrv_bbp_set_tds_subfrm_offset(unsigned short usOffset)
{
    return (BSP_U16)0;
}
/*****************************************************************************
* ����  : mdrv_bbp_get_sleep_period
* ����  : set tds system sub frame offset
* ����  : void
* ���  : void
* ����  : u32
*****************************************************************************/
unsigned int mdrv_bbp_get_sleep_period(void)
{
    return 0;
}

/*****************************************************************************
* ����  : mdrv_bbp_get_tds_clkswitchflag
* ����  : get tdsclk switch
* ����  : void
* ���  : 0��ʾ�л���ϵͳʱ�ӣ�1��ʾ�л���32kʱ��
* ����  : void
*****************************************************************************/
unsigned int mdrv_bbp_get_tds_clkswitchflag(void)
{
    return -1;
}

/***************************************************************************
 �� �� ��  : void mdrv_bbp_enable_wakeup_intr(PWC_COMM_MODE_E mode)
 ��������  : ��bbp���ʱ��
 �������  : enModeId      ͨ��ģʽ
                             enModuleId    ͨ��ģ��
                             enModemId    ����
 �������  : ��
 �� �� ֵ  : RET_OK         �ɹ�
                         RET_ERR        ʧ��
**************************************************************************/
void mdrv_bbp_enable_wakeup_intr(PWC_COMM_MODE_E mode)
{
    return ;
}

/*****************************************************************************
* ����  : mdrv_bbp_disable_wakeup_intr
* ����  : disable bbp wakeup int
* ����  : void
* ���  : void
* ����  : void
*****************************************************************************/
void mdrv_bbp_disable_wakeup_intr(PWC_COMM_MODE_E mode)
{
    return ;
}

/*****************************************************************************
* ����  : mdrv_bbp_clear_wakeup_intr
* ����  : clear bbp wakeup int
* ����  : void
* ���  : void
* ����  : void
*****************************************************************************/
void mdrv_bbp_clear_wakeup_intr(PWC_COMM_MODE_E mode)
{
    return ;
}

/*****************************************************************************
Function:   mdrv_bbp_get_measure_flag(PWC_COMM_MODE_E enCommMode)
Description:
Input:
Output:     the means flag value;
Return:
Others:
*****************************************************************************/
int mdrv_bbp_get_measure_flag(PWC_COMM_MODE_E enCommMode)
{
    return (BSP_S32)0;
}
/*****************************************************************************
* ����  : BSP_BBPIntDlTbRegCb
* ����  : ��PS���ã����������ע������������������жϵĻص�
* ����  : pfunc
* ���  : void
* ����  : void
* ˵��  :v7r5�и��жϲ���arm�д�����ֱ�Ӵ�׮
*****************************************************************************/
void mdrv_bbp_register_dltb_intr_cb(BSPBBPIntDlTbFunc pFunc)
{
    return ;
}
/*****************************************************************************
* �� �� : BSP_BBPIntDmaInit
* �� �� : �ҽ�bbp dma �ж�
* �� �� : void
* �� �� : void
* �� �� : 0Ϊ�ɹ���-1ʧ��
* ˵ �� :���жϲ�����arm�д�����׮
*****************************************************************************/
int bsp_bbp_dma_int_init(void)
{
    return 0;
}
/*****************************************************************************
* �� �� : bsp_bbp_dma_int_enable
* �� �� : ʹ��bbp dma �ж�
* �� �� : void
* �� �� : void
* �� �� : 0Ϊ�ɹ���-1ʧ��
* ˵ �� :
*****************************************************************************/
int bsp_bbp_dma_int_enable(void)
{
    return 0;
}

/*****************************************************************************
* �� �� : mdrv_bbp_get_lte_ta
* �� �� : ��lps����,�鿴������֡ͷ���ϵͳ��֡ͷ����ǰ��
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
int mdrv_bbp_get_lte_ta(void)
{
    return 0;
}
/*****************************************************************************
* �� �� : mdrv_bbp_init_intr
* �� �� : �ҽ�BBP��֡�ж�(T ��L)
* �� �� : void
* �� �� : void
* �� �� : 0Ϊ�ɹ���-1ʧ��
* ˵ �� :
*****************************************************************************/
int mdrv_bbp_init_intr(PWC_COMM_MODE_E mode)
{
    return 0;
}
/*****************************************************************************
* �� �� ��  : mdrv_bbp_get_wakeup_time
*
* ��������  : ��ȡdsp����ʱ��
*
* �������  : mode:ģʽ lte or tds
* �������  : void
*
* �� �� ֵ  : ��λΪ32.768KHzʱ�Ӽ���
*
* ����˵��  :
*
*****************************************************************************/
unsigned int mdrv_bbp_get_wakeup_time(PWC_COMM_MODE_E mode)
{
    return 0;
}
/***************************************************************************
 �� �� ��  : DRV_PWRCTRL_BBPCLKENABLE()
 ��������  : ��bbp���ʱ��
 �������  : enModeId      Э��ģʽ
             enModuleId    ����ģ��
             enModemId     ����
             enChannel     channel���
 �������  : ��
 �� �� ֵ  : BBP_OK         �ɹ�
             ����           ʧ��
**************************************************************************/
int mdrv_pm_enable_bbpclk (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    return 0;
}
/***************************************************************************
 �� �� ��  : mdrv_pm_disable_bbpclk()
 ��������  : ͨ��ģ�����BBPģ�����
 �������  : enModeId      Э��ģʽ
             enModuleId    ����ģ��
             enModemId     ����
             enChannel     channel���
 �������  : ��
 �� �� ֵ  : BBP_OK         �ɹ�
             ����           ʧ��
**************************************************************************/
int mdrv_pm_disable_bbpclk (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    return 0;
}

/*****************************************************************************
* �� �� ��  : mdrv_bbp_get_timing_val
*
* ��������  : Lģ��ϵͳʱ���32K��ʱ��ѯ
*
* �������  : pstTiming�ṹ��ָ��
* �������  : pstTiming�ṹ�嶨ʱֵ
*
* �� �� ֵ  : 0�ɹ�������ʧ��
*
* ����˵��  :�ڲ����жϣ���֤�������̲������
*
*****************************************************************************/
int mdrv_bbp_get_timing_val (BBP_TIMING_STRU *pstTiming)
{
    return 0;
}

/***************************************************************************
 �� �� ��  : mdrv_pm_gbbp_select_clksrc()
 ��������  : gbbpͨ��ѡ��
 �������  : enModemId     ����(0/2--g0;1--g1;��������ʧ��)
             enChannel     channel���(0--chan0,1--chan1,��Ч����������ʧ��)
 �������  : ��
 �� �� ֵ  : BBP_OK         �ɹ�
             ����           ʧ��
**************************************************************************/
int mdrv_pm_gbbp_select_clksrc (PWC_COMM_MODEM_E enModemId,PWC_COMM_CHANNEL_E enChannel)
{
    return 0;
}
#endif

