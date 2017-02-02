#include <mdrv_pm.h>
#include <bsp_bbp.h>
#include <bsp_abb.h>
#include <bsp_rf_balong.h>
#include <bsp_version.h>
#include <bsp_dsp.h>
#include <bsp_dspload.h>

/*****************************************************************************
* �� �� ��  : mdrv_pm_pwrup
*
* ��������  : ͨ��ģ����Ƶ�Դ�ϵ�ӿ�
*
* �������  : PWC_COMM_MODE_E enModeId      Э��ģʽ
*             PWC_COMM_MODULE_E enModuleId  ����ģ��
*             PWC_COMM_MODEM_E enModemId    ����
*             PWC_COMM_CHANNEL_E enChannel  channel���
* �������  :
*
* �� �� ֵ  : 0��ִ�гɹ���1��ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_pm_pwrup (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId,
                   PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    int ret = 0;

	/* p532 fpgaƽ̨��׮ */
	if(BSP_BOARD_TYPE_BBIT == bsp_get_version_info()->board_type)
	{
		return 0;
	}

    switch (enModuleId)
    {
        case PWC_COMM_MODULE_PA:
            ret = bsp_pa_power_up(enModeId, enModemId, enChannel);
            break;
        case PWC_COMM_MODULE_RF:
            ret = bsp_rfic_power_up(enModeId, enModemId, enChannel);
            break;
        case PWC_COMM_MODULE_ABB:
            ret = bsp_abb_power_up(enModeId, enModemId, enChannel);
            break;
        case PWC_COMM_MODULE_BBE16:
            ret = bsp_bbe_power_up();
            break;
#ifdef CONFIG_CBBE
        case PWC_COMM_MODULE_CBBE16:
            ret = bsp_bbe_power_up_ex(BSP_DSP_CBBE);
            break;
#endif
        case PWC_COMM_MODULE_BBP_DRX:
        case PWC_COMM_MODULE_BBP_DPA:
        case PWC_COMM_MODULE_BBP_MEM:
            ret = bsp_bbp_power_up(enModeId, enModuleId, enModemId);
            break;
		case PWC_COMM_MODULE_FEM:
			ret = bsp_fem_power_up(enModeId, enModemId, enChannel);
			break;
        default:
            //bsp_trace();
            break;
    }

    return ret;
}

/*****************************************************************************
* �� �� ��  : mdrv_pm_pwrdown
*
* ��������  : ͨ��ģ����Ƶ�Դ�µ�ӿ�
*
* �������  : PWC_COMM_MODE_E enModeId      Э��ģʽ
*             PWC_COMM_MODULE_E enModuleId  ����ģ��
*             PWC_COMM_MODEM_E enModemId    ����
*             PWC_COMM_CHANNEL_E enChannel  channel���
* �������  :
*
* �� �� ֵ  : 0��ִ�гɹ���1��ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_pm_pwrdown (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId,
                     PWC_COMM_MODEM_E enModemId,PWC_COMM_CHANNEL_E enChannel)
{
    int ret = 0;

	/* p532 fpgaƽ̨��׮ */
	if(BSP_BOARD_TYPE_BBIT == bsp_get_version_info()->board_type)
	{
		return 0;
	}

    switch (enModuleId)
    {
        case PWC_COMM_MODULE_PA:
            ret = bsp_pa_power_down(enModeId, enModemId, enChannel);
            break;
        case PWC_COMM_MODULE_RF:
            ret = bsp_rfic_power_down(enModeId, enModemId, enChannel);
            break;
        case PWC_COMM_MODULE_ABB:
            ret = bsp_abb_power_down(enModeId, enModemId, enChannel);
            break;
        case PWC_COMM_MODULE_BBE16:
            ret = bsp_bbe_power_down();
            break;
#ifdef CONFIG_CBBE
        case PWC_COMM_MODULE_CBBE16:
            ret = bsp_bbe_power_down_ex(BSP_DSP_CBBE);
            break;
#endif
        case PWC_COMM_MODULE_BBP_DRX:
        case PWC_COMM_MODULE_BBP_DPA:
        case PWC_COMM_MODULE_BBP_MEM:
            ret = bsp_bbp_power_down(enModeId, enModuleId, enModemId);
            break;
		case PWC_COMM_MODULE_FEM:
			ret = bsp_fem_power_down(enModeId, enModemId, enChannel);
			break;
        default:
            //bsp_trace();
            break;
    }

    return ret;
}

/*****************************************************************************
* �� �� ��  : mdrv_pm_get_pwrstatus
*
* ��������  : ͨ��ģ����Ƶ�Դ��ѯ�ӿ�
*
* �������  : PWC_COMM_MODE_E enModeId      Э��ģʽ
*             PWC_COMM_MODULE_E enModuleId  ����ģ��
*             PWC_COMM_MODEM_E enModemId    ����
*             PWC_COMM_CHANNEL_E enChannel  channel���
* �������  :
*
* �� �� ֵ  : PWRCTRL_COMM_ON ����ģ���Ѿ��ϵ�
*             PWRCTRL_COMM_OFF ����ģ���Ѿ��µ�
*             ����������
* ����˵��  :
*
*****************************************************************************/
int mdrv_pm_get_pwrstatus (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId,
                           PWC_COMM_MODEM_E enModemId,PWC_COMM_CHANNEL_E enChannel)
{
    int ret = PWRCTRL_COMM_ON;

	/* p532 fpgaƽ̨��׮ */
	if(BSP_BOARD_TYPE_BBIT == bsp_get_version_info()->board_type)
	{
		return PWRCTRL_COMM_ON;
	}

    switch (enModuleId)
    {
        case PWC_COMM_MODULE_PA:
            ret = bsp_pa_power_status(enModeId, enModemId, enChannel);
            break;
        case PWC_COMM_MODULE_RF:
            ret = bsp_rfic_power_status(enModemId, enChannel);
            break;
        case PWC_COMM_MODULE_ABB:
            ret = bsp_abb_power_status(enModeId, enModemId, enChannel);
            break;
        case PWC_COMM_MODULE_BBE16:
            ret = bsp_bbe_power_status();
            break;
        case PWC_COMM_MODULE_BBP_DRX:
        case PWC_COMM_MODULE_BBP_DPA:
        case PWC_COMM_MODULE_BBP_MEM:
            ret = bsp_bbp_power_status(enModeId, enModuleId, enModemId);
            break;
		case PWC_COMM_MODULE_FEM:
			ret = bsp_fem_power_status(enModeId, enModemId, enChannel);
			break;
        default:
            //bsp_trace();
            break;
    }

    return ret;
}

/*****************************************************************************
* �� �� ��  : mdrv_pm_enable_pllclk
*
* ��������  : DRX PLLʹ��ʱ��
*
* �������  : PWC_COMM_MODE_E enModeId      Э��ģʽ
*             PWC_COMM_MODULE_E enModuleId  ����ģ��
*             PWC_COMM_MODEM_E enModemId    ����
*             PWC_COMM_CHANNEL_E enChannel  channel���
* �������  :
*
* �� �� ֵ  :  0��ִ�гɹ���-1��ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_pm_enable_pllclk (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId,
                           PWC_COMM_MODEM_E enModemId,PWC_COMM_CHANNEL_E enChannel)
{
    int ret = 0;

	/* p532 fpgaƽ̨��׮ */
	if(BSP_BOARD_TYPE_BBIT == bsp_get_version_info()->board_type)
	{
		return 0;
	}

    switch (enModuleId)
    {
        case PWC_COMM_MODULE_PA:
            //ret =
            break;
        case PWC_COMM_MODULE_RF:
            ret = bsp_rfclk_enable(enModeId, enModemId, enChannel);
            break;
        case PWC_COMM_MODULE_ABB:
            ret = bsp_abb_pll_enable(enModeId, enModemId, enChannel);
            break;
        case PWC_COMM_MODULE_BBE16:
            ret = bsp_dsp_dfs_pll_enable();
            break;
#ifdef CONFIG_CBBE
        case PWC_COMM_MODULE_CBBE16:
            ret = bsp_dsp_dfs_pll_enable_ex(BSP_DSP_CBBE);
            break;
#endif
        case PWC_COMM_MODULE_BBP_DRX:
        case PWC_COMM_MODULE_BBP_DPA:
        case PWC_COMM_MODULE_BBP_MEM:
            //ret = bsp_bbp_dfs_enable(enModeId, enModuleId, enModemId);
            break;
        default:
            //bsp_trace();
            break;
    }

    return ret;
}

/*****************************************************************************
* �� �� ��  : mdrv_pm_disable_pllclk
*
* ��������  : DRX PLL�ر�ʱ��
*
* �������  : PWC_COMM_MODE_E enModeId      Э��ģʽ
*             PWC_COMM_MODULE_E enModuleId  ����ģ��
*             PWC_COMM_MODEM_E enModemId    ����
*             PWC_COMM_CHANNEL_E enChannel  channel���
* �������  :
*
* �� �� ֵ  : 0��ִ�гɹ���-1��ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_pm_disable_pllclk (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId,
                            PWC_COMM_MODEM_E enModemId,PWC_COMM_CHANNEL_E enChannel)
{
    int ret = 0;

	/* p532 fpgaƽ̨��׮ */
	if(BSP_BOARD_TYPE_BBIT == bsp_get_version_info()->board_type)
	{
		return 0;
	}

    switch (enModuleId)
    {
        case PWC_COMM_MODULE_PA:
            //ret =
            break;
        case PWC_COMM_MODULE_RF:
            ret = bsp_rfclk_disable(enModeId, enModemId, enChannel);
            break;
        case PWC_COMM_MODULE_ABB:
            ret = bsp_abb_pll_disable(enModeId, enModemId, enChannel);
            break;
        case PWC_COMM_MODULE_BBE16:
            ret = bsp_dsp_dfs_pll_disable();
            break;
#ifdef CONFIG_CBBE
        case PWC_COMM_MODULE_CBBE16:
            ret = bsp_dsp_dfs_pll_disable_ex(BSP_DSP_CBBE);
            break;
#endif
        case PWC_COMM_MODULE_BBP_DRX:
        case PWC_COMM_MODULE_BBP_DPA:
        case PWC_COMM_MODULE_BBP_MEM:
            //ret = bsp_bbp_dfs_disable(enModeId, enModuleId, enModemId);
            break;
        default:
            //bsp_trace();
            break;
    }

    return ret;
}

/*****************************************************************************
* �� �� ��  : mdrv_pm_get_pllclk_status
*
* ��������  : DRX PLL��ѯʱ��
*
* �������  : PWC_COMM_MODE_E enModeId      Э��ģʽ
*             PWC_COMM_MODULE_E enModuleId  ����ģ��
*             PWC_COMM_MODEM_E enModemId    ����
*             PWC_COMM_CHANNEL_E enChannel  channel���
* �������  :
*
* �� �� ֵ  : PWRCTRL_COMM_ON         ʱ�Ӵ�
*             PWRCTRL_COMM_OFF        ʱ�ӹر�
*             -1                      ��ѯʧ��
*
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_pm_get_pllclk_status (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId,
                               PWC_COMM_MODEM_E enModemId,PWC_COMM_CHANNEL_E enChannel)
{
    int ret = PWRCTRL_COMM_ON;

	/* p532 fpgaƽ̨��׮ */
	if(BSP_BOARD_TYPE_BBIT == bsp_get_version_info()->board_type)
	{
		return PWRCTRL_COMM_ON;
	}

    switch (enModuleId)
    {
        case PWC_COMM_MODULE_PA:
            //ret =
            break;
        case PWC_COMM_MODULE_RF:
            //ret =
            break;
        case PWC_COMM_MODULE_ABB:
            ret = bsp_abb_pll_status(enModeId, enModemId, enChannel);
            break;
        case PWC_COMM_MODULE_BBE16:
            ret = bsp_dsp_dfs_pll_status();
            break;
#ifdef CONFIG_CBBE
        case PWC_COMM_MODULE_CBBE16:
            ret = bsp_dsp_dfs_pll_status_ex(BSP_DSP_CBBE);
            break;
#endif
        case PWC_COMM_MODULE_BBP_DRX:
        case PWC_COMM_MODULE_BBP_DPA:
        case PWC_COMM_MODULE_BBP_MEM:
            //ret = bsp_bbp_dfs_status(enModeId, enModuleId, enModemId);
            break;
        default:
            //bsp_trace();
            break;
    }

    return ret;
}


