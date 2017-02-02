
#ifdef __cplusplus
extern "C"
{
#endif
#include <product_config.h>

#ifdef CONFIG_PA_RF
#include <of.h>
#include <mdrv_pm.h>
#include <drv_nv_def.h>
#include <drv_nv_id.h>
#include <bsp_shared_ddr.h>
#include <bsp_pa_rf.h>
#include <bsp_regulator.h>
#include <bsp_pmu.h>
#include <bsp_pmu_hi6561.h>
#include <bsp_nvim.h>
#include "pa_rf_balong.h"
#include <tcxo_balong.h>

#define PA_RF_VOLT_NUM  MODEM_PA1

u32 g_channel_max_num = 0;  /* ���channel���� */
int s_is_gpa_usepmu = 1;    /* GPA�Ƿ�ʹ��PMU���磬���ǵ�ع��磻Ĭ��ʹ��pmu���ɸ���NV���� */

struct pmu_parf_ops pmu_parf_ops;

#ifndef CONFIG_PASTAR

#define NV_PARF_SWITCH_DEFAULT_VAL  ((1<<MODEM_PA0)|(1<<MODEM_RFIC0_ANALOG0)\
                                    |(1<<MODEM_RFIC0_ANALOG1)|(1<<MODEM_FEM0)|(1<<MODEM_PA_VBIAS0))


struct parf_power_ctrl_s parf_power_ctrl[PA_RF_VOLT_NUM]={
    [MODEM_PA0] = {
        .status_stub = 0,
        .is_exist = 1,
        .name = VOLT_NAME_PA_VCC,
        },
    [MODEM_RFIC0_ANALOG0] = {
        .status_stub = 0,
        .is_exist = 1,
        .name = VOLT_NAME_RFIC_FRONT_VCC,
        },
    [MODEM_RFIC0_ANALOG1] = {
        .status_stub = 0,
        .is_exist = 1,
        .name = VOLT_NAME_RFIC_VCC,
        },
    [MODEM_FEM0] = {
        .status_stub = 0,
        .is_exist = 1,
        .name = VOLT_NAME_RF_FEM_VCC,
        },
    [MODEM_PA_VBIAS0] = {
        .status_stub = 0,
        .is_exist = 1,
        .name = VOLT_NAME_PA_VBIA2_VCC,
        },
};

/*
 * ���������PMUоƬ������
 */

s32 pmu_power_on(EM_MODEM_CONSUMER_ID_E power_id)
{
    s32 ret = 0;

    if(parf_power_ctrl[power_id].is_exist)
    {
        ret = regulator_enable(parf_power_ctrl[power_id].regulator);
    }
    else
    {
        parf_power_ctrl[power_id].status_stub = 1;
    }

    return ret;
}
s32 pmu_power_off(EM_MODEM_CONSUMER_ID_E power_id)
{
    s32 ret = 0;

    if(parf_power_ctrl[power_id].is_exist)
    {
        ret = regulator_disable(parf_power_ctrl[power_id].regulator);
    }
    else
    {
        parf_power_ctrl[power_id].status_stub = 0;
    }

    return ret;
}

s32 pmu_is_poweron(EM_MODEM_CONSUMER_ID_E power_id)
{
    return parf_power_ctrl[power_id].is_exist \
              ? regulator_is_enabled(parf_power_ctrl[power_id].regulator) \
              : parf_power_ctrl[power_id].status_stub;
}

/*****************************************************************************
 �� �� ��  : bsp_pmu_get_pa_powerstatus
 ��������  : ��ȡpa���µ�״̬
 �������  : @modem_id - ����or����(6559ֻ֧�ֵ������˲�������)
 �������  : ��
 �� �� ֵ  : 0 - �ɹ�����0 - ʧ��
*****************************************************************************/
PWC_COMM_STATUS_E bsp_pmu_get_pa_powerstatus(PWC_COMM_MODEM_E modem_id)
{
    s32 status1, status2;
    PWC_COMM_STATUS_E result = PWC_COMM_STATUS_BUTT;

    if(modem_id >= g_channel_max_num)
    {
        parf_print_error("NOTE: invalid modem id %d\n", modem_id);
        return PWC_COMM_STATUS_BUTT;
    }

    status1 = pmu_is_poweron(MODEM_PA0);
    status2 = pmu_is_poweron(MODEM_PA_VBIAS0);

    if(status1 && status2)
    {
        result = PWRCTRL_COMM_ON;
    }
    else if(0 == (status1 | status2))
    {
        result = PWRCTRL_COMM_OFF;
    }
    else
    {
        result = PWC_COMM_STATUS_BUTT;
    }

    return result;
}

/*****************************************************************************
 �� �� ��  : bsp_pmu_pa_poweron
 ��������  : ��pa�ϵ�
 �������  : @modem_id - ����or����(6559ֻ֧�ֵ������˲�������)
 �������  : ��
 �� �� ֵ  : 0 - �ɹ�����0 - ʧ��
*****************************************************************************/
s32 bsp_pmu_pa_poweron(PWC_COMM_MODEM_E modem_id)
{
    s32 ret = PARF_OK;

    if(modem_id >= g_channel_max_num)
    {
        parf_print_error("NOTE: invalid modem id %d\n", modem_id);
        return PARF_ERROR;
    }

    ret = pmu_power_on(MODEM_PA0) | pmu_power_on(MODEM_PA_VBIAS0);
    if(ret)
    {
        parf_print_error("ERROR: enable pa failed, ret %d \n", ret);
        return ret;
    }

    return ret;
}

/*****************************************************************************
 �� �� ��  : bsp_pmu_pa_poweroff
 ��������  : ��pa�µ�
 �������  : @modem_id - ����or����(6559ֻ֧�ֵ������˲�������)
 �������  : ��
 �� �� ֵ  : 0 - �ɹ�����0 - ʧ��
*****************************************************************************/
s32 bsp_pmu_pa_poweroff(PWC_COMM_MODEM_E modem_id)
{
    s32 ret = PARF_OK;

    if(modem_id >= g_channel_max_num)
    {
        parf_print_error("NOTE: invalid modem id %d\n", modem_id);
        return PARF_ERROR;
    }

    /* 711 LDO12��USB���ã��˴����ܹص�����Ҫ���Ǽ��ݷ���? */
    ret = pmu_power_off(MODEM_PA0);/* | pmu_power_off(MODEM_PA_VBIAS0);*/
    if(ret)
    {
        parf_print_error("ERROR: disable pa failed, ret %d \n", ret);
        return ret;
    }

    return ret;
}

/*****************************************************************************
 �� �� ��  : bsp_pmu_get_rf_powerstatus
 ��������  : ��ȡrf���µ�״̬
 �������  : @modem_id - ����or����(6559ֻ֧�ֵ������˲�������)
 �������  : ��
 �� �� ֵ  : 0 - �ɹ�����0 - ʧ��
*****************************************************************************/
PWC_COMM_STATUS_E bsp_pmu_get_rf_powerstatus(PWC_COMM_MODEM_E modem_id)
{
    s32 status1, status2, status3;
    s32 result = 0;

    /* bbstarֻ֧��modem0 */
    if(modem_id != PWC_COMM_MODEM_0)
    {
        parf_print_error("NOTE: invalid modem id %d\n", modem_id);
        return PWC_COMM_STATUS_BUTT;
    }

    status1 = pmu_is_poweron(MODEM_RFIC0_ANALOG0);

    status2 = pmu_is_poweron(MODEM_RFIC0_ANALOG1);

    status3 = pmu_is_poweron(MODEM_FEM0);

    if(status1 && status2 && status3)
    {
        result = PWRCTRL_COMM_ON;
    }
    else if(0 == (status1 | status2 | status3))
    {
        result = PWRCTRL_COMM_OFF;
    }
    else
    {
        result = PWC_COMM_STATUS_BUTT;
    }

    return (PWC_COMM_STATUS_E)result;
}

/*****************************************************************************
 �� �� ��  : bsp_pmu_rf_poweron
 ��������  : ��rf�ϵ�
 �������  : @modem_id - ����or����(6559ֻ֧�ֵ������˲�������)
 �������  : ��
 �� �� ֵ  : 0 - �ɹ�����0 - ʧ��
*****************************************************************************/
s32 bsp_pmu_rf_poweron(PWC_COMM_MODEM_E modem_id)
{
    s32 ret = OK;

    /* bbstarֻ֧��modem0 */
    if(modem_id != PWC_COMM_MODEM_0)
    {
        parf_print_error("NOTE: invalid modem id %d\n", modem_id);
        return BSP_PMU_ERROR;
    }

    ret = pmu_power_on(MODEM_RFIC0_ANALOG0)\
        | pmu_power_on(MODEM_RFIC0_ANALOG1)\
        | pmu_power_on(MODEM_FEM0);

    if(ret)
    {
        parf_print_error("ERROR: rf power on failed, ret %d \n", ret);
    }

    return ret;
}

/*****************************************************************************
 �� �� ��  : bsp_pmu_rf_poweroff
 ��������  : ��rf�µ�
 �������  : @modem_id - ����or����(6559ֻ֧�ֵ������˲�������)
 �������  : ��
 �� �� ֵ  : 0 - �ɹ�����0 - ʧ��
*****************************************************************************/
s32 bsp_pmu_rf_poweroff(PWC_COMM_MODEM_E modem_id)
{
    s32 ret = OK;

    /* bbstarֻ֧��modem0 */
    if(modem_id != PWC_COMM_MODEM_0)
    {
        parf_print_error("NOTE: invalid modem id %d\n", modem_id);
        return BSP_PMU_ERROR;
    }

    ret = pmu_power_off(MODEM_RFIC0_ANALOG0)\
        | pmu_power_off(MODEM_RFIC0_ANALOG1)\
        | pmu_power_off(MODEM_FEM0);

    if(ret)
    {
        parf_print_error("ERROR: rf power off failed, ret %d \n", ret);
    }

    return ret;
}

/*****************************************************************************
 �� �� ��  : drv_pmu_parf_exc_check
 ��������  : ͨ��ģ����pa/rf�����Ƿ����쳣
 �������  : modem_id       ����
 �������  : ��
 �� �� ֵ  : 0          û���쳣
             1          �����쳣
             -1         ��������
*****************************************************************************/
s32 drv_pmu_parf_exc_check(PWC_COMM_MODEM_E modem_id)
{
    /* ������� */
    if(modem_id >= g_channel_max_num)
    {
        parf_print_error("NOTE: invalid modem_id %d\n", modem_id);
        return PARF_ERROR;
    }

    return bsp_pmu_parf_exc_check();
}

/*****************************************************************************
 �� �� ��  : drv_pmu_modem_voltage_set
 ��������  : ͨ��ģ�����õ�ѹ�ӿ�
 �������  : consumer_id     �û�id
             voltage_mv      ���õĵ�ѹֵ����
 �������  : ��
 �� �� ֵ  : 0          ���óɹ�
             else       ����ʧ��
*****************************************************************************/
s32 drv_pmu_modem_voltage_set(EM_MODEM_CONSUMER_ID_E consumer_id, u32 voltage_mv )
{
    s32 ret = 0;

    /* ������� */
    if(consumer_id >= PA_RF_VOLT_NUM)
    {
        parf_print_error("ERROR: invalid consumer_id %d\n", consumer_id);
        return ERROR;
    }

    if(parf_power_ctrl[consumer_id].is_exist)
    {
        ret = regulator_set_voltage(parf_power_ctrl[consumer_id].regulator, (s32)voltage_mv * 1000, (s32)voltage_mv * 1000);
    }
    else
    {
        parf_print_error("ERROR: regulator %s is not exist\n", parf_power_ctrl[consumer_id].name);
        ret = -1;
    }

    if(ret)
    {
        parf_print_error("ERROR: regulator_set_voltage failed, ret = %d\n", ret);
    }

    return ret;
}

/*****************************************************************************
 �� �� ��  : drv_pmu_modem_voltage_get
 ��������  : ͨ��ģ���ȡ��ѹ�ӿ�
 �������  : consumer_id     �û�id
             voltage_mv      ��õĵ�ѹֵ����
 �������  : ��
 �� �� ֵ  : 0          ��ȡ�ɹ�
             else       ��ȡʧ��
*****************************************************************************/
s32 drv_pmu_modem_voltage_get( EM_MODEM_CONSUMER_ID_E consumer_id, u32 *voltage_mv )
{
    s32 ret = OK;

    /* ������� */
    if(consumer_id >= PA_RF_VOLT_NUM)
    {
        parf_print_error("ERROR: invalid consumer_id %d\n", consumer_id);
        return ERROR;
    }

    if(!voltage_mv)
    {
        parf_print_error("ERROR: null pointer of vlotage_mv\n");
        return ERROR;
    }

    /* ��ȡ��ѹֵ����ת��Ϊmv */
    if(parf_power_ctrl[consumer_id].is_exist)
    {
        *voltage_mv = (u32)regulator_get_voltage(parf_power_ctrl[consumer_id].regulator) / 1000;
    }
    else
    {
        parf_print_error("ERROR: regulator %s is not exist\n", parf_power_ctrl[consumer_id].name);
        *voltage_mv = 0;
        ret = -1;
    }

    return ret;
}

/*****************************************************************************
 �� �� ��  : drv_pmu_modem_voltage_list
 ��������  : ͨ��ģ���ȡ��ѹ���÷�Χ�ӿ�
 �������  : consumer_id     �û�id
             list            ��ѹ��Χ����
             size            �����С
 �������  : ��
 �� �� ֵ  : 0          ��ȡ�ɹ�
             else       ��ȡʧ��
*****************************************************************************/
s32 drv_pmu_modem_voltage_list(EM_MODEM_CONSUMER_ID_E consumer_id,u16 **list, u32 *size)
{
    /* �ϲ�û�е��ã��˴�ֱ�ӷ���ERROR */
    return PARF_OK;
}

/*****************************************************************************
 ����    : drv_pmu_modem_apt_enable
 ����    : ͨ��ģ��ʹ��APT״̬�ӿ�
 ����    : modem_id       ����
          mode_id        ģʽ
 ���    : ��
 ����    : 1  APTʹ��/   0    APTδʹ��/  -1    ��ȡʧ��
*****************************************************************************/
s32 drv_pmu_modem_apt_enable(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
    /* ������� */
    if(modem_id >= g_channel_max_num)
    {
        parf_print_error("NOTE: invalid modem_id %d\n", modem_id);
        return PARF_ERROR;
    }

    if(mode_id >= PWC_COMM_MODE_BUTT)
    {
        parf_print_error("ERROR: invalid mode_id %d\n", mode_id);
        return PARF_ERROR;
    }

    return bsp_pmu_apt_enable();
}

/*****************************************************************************
 ����    : drv_pmu_modem_apt_disable
 ����    : ͨ��ģ��ȥʹ��APT״̬�ӿ�
 ����    : modem_id       ����
          mode_id        ģʽ
 ���    : ��
 ����    : 1  APTʹ��/   0    APTδʹ��/  -1    ��ȡʧ��
*****************************************************************************/
s32 drv_pmu_modem_apt_disable(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
    /* ������� */
    if(modem_id >= g_channel_max_num)
    {
        parf_print_error("NOTE: invalid modem_id %d\n", modem_id);
        return PARF_ERROR;
    }

    if(mode_id >= PWC_COMM_MODE_BUTT)
    {
        parf_print_error("ERROR: invalid mode_id %d\n", mode_id);
        return PARF_ERROR;
    }

    return bsp_pmu_apt_disable();
}

/*****************************************************************************
 ����    : drv_pmu_modem_apt_status_get
 ����    : ͨ��ģ���ȡ��ǰAPT״̬�ӿ�
 ����    : modem_id       ����
          mode_id        ģʽ
 ���    : ��
 ����    : 1  APTʹ��/   0    APTδʹ��/  -1    ��ȡʧ��
*****************************************************************************/
s32 drv_pmu_modem_apt_status_get(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
    /* ������� */
    if(modem_id >= g_channel_max_num)
    {
        parf_print_error("NOTE: invalid modem_id %d\n", modem_id);
        return PARF_ERROR;
    }

    if(mode_id >= PWC_COMM_MODE_BUTT)
    {
        parf_print_error("ERROR: invalid mode_id %d\n", mode_id);
        return PARF_ERROR;
    }

    return bsp_pmu_apt_status_get();
}

/*****************************************************************************
 ����     : drv_pmu_modem_mode_config
 ����    : ͨ��ģ������Gģ��Wģ�ӿ�
 ����    : modem_id       ����
          mode_id        ģʽ
 ���    : ��
 ����  : 0         ���óɹ�/  else      ����ʧ��
*****************************************************************************/
s32 drv_pmu_modem_mode_config(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
    s32 ret = OK;

    /* ������� */
    if(modem_id > PWC_COMM_MODEM_0)
    {
        parf_print_error("NOTE: invalid modem_id %d\n", modem_id);
        return ERROR;
    }

    if(mode_id >= PWC_COMM_MODE_BUTT)
    {
        parf_print_error("ERROR: invalid mode_id %d\n", mode_id);
        return ERROR;
    }

    switch(mode_id){
        case PWC_COMM_MODE_LTE :
        case PWC_COMM_MODE_TDS :
        case PWC_COMM_MODE_WCDMA :
            if(parf_power_ctrl[MODEM_PA0].is_exist)
            {
                /* ����buck pa�ĵ�ѹΪ3.3v */
                ret|= regulator_set_voltage(parf_power_ctrl[MODEM_PA0].regulator,3300000,3300000);
            }
            /* �ر�APT */
            ret |= bsp_pmu_apt_disable();

			/* set RFIC0_ANALOG0 1.8V */
            if(parf_power_ctrl[MODEM_RFIC0_ANALOG0].is_exist)
            {
                ret |= regulator_set_voltage(parf_power_ctrl[MODEM_RFIC0_ANALOG0].regulator,1800000,1800000);
            }
            break;

        case PWC_COMM_MODE_GSM:
            if(parf_power_ctrl[MODEM_PA0].is_exist)
            {
                /* ����buck pa�ĵ�ѹΪ3.7v */
                ret|= regulator_set_voltage(parf_power_ctrl[MODEM_PA0].regulator,3700000,3700000);
            }
            /* �ر�APT */
            ret |= bsp_pmu_apt_disable();

			/* set RFIC0_ANALOG0 2.2V */
            if(parf_power_ctrl[MODEM_RFIC0_ANALOG0].is_exist)
            {
                ret |= regulator_set_voltage(parf_power_ctrl[MODEM_RFIC0_ANALOG0].regulator,2200000,2200000);
            }
            break;

        default:
            ;
    }

    return ret;
}

s32 parf_regulator_register(NV_DRV_PARF_SWITCH_STRU switchs)
{
	u32 ret = PARF_OK;
	u32 i = 0;

	/* ����NV���ã���ȡregulator */
	for(i=0; i<PA_RF_VOLT_NUM; i++)
	{
		parf_power_ctrl[i].is_exist = 1 & (switchs.cont.u32>>i);
		if(parf_power_ctrl[i].is_exist)
		{
			parf_power_ctrl[i].regulator = regulator_get(NULL, parf_power_ctrl[i].name);
			if(NULL == parf_power_ctrl[i].regulator)
			{
				parf_print_error("ERROR: regulator_pmu%d get regulator failed %d\n", i);
				ret |= (1U << i);
			}
		}
	}

	if(ret != PARF_OK)
	{
		return (s32)ret;
	}

	return PARF_OK;
}

#endif

/*
 * �����Ƕ����ṩ�Ľӿڣ�����DRV�ӿں�dpm���̽ӿ�
 */

/*****************************************************************************
 �� �� ��  : DRV_PASTAR_EXC_CHECK
 ��������  : ͨ��ģ����PASTAR�Ƿ����쳣�ӿ�
 �������  : modem_id       ����
 �������  : ��
 �� �� ֵ  : 0          û���쳣
             else       �����쳣
*****************************************************************************/
int mdrv_pmu_check_pastar(PWC_COMM_MODEM_E modem_id)
{
    return pmu_parf_ops.drv_pastar_exc_check(modem_id);
}

/*****************************************************************************
 �� �� ��  : DRV_MODEM_VOLTAGE_SET
 ��������  : ͨ��ģ�����õ�ѹ�ӿ�
 �������  : consumer_id     �û�id
             voltage_mv      ���õĵ�ѹֵ����
 �������  : ��
 �� �� ֵ  : 0          ���óɹ�
             else       ����ʧ��
*****************************************************************************/
int mdrv_pmu_set_voltage(EM_MODEM_CONSUMER_ID_E consumer_id, unsigned int voltage_mv)
{
    return pmu_parf_ops.drv_modem_voltage_set(consumer_id,voltage_mv);
}

/*****************************************************************************
 �� �� ��  : DRV_MODEM_VOLTAGE_GET
 ��������  : ͨ��ģ���ȡ��ѹ�ӿ�
 �������  : consumer_id     �û�id
             voltage_mv      ��õĵ�ѹֵ����
 �������  : ��
 �� �� ֵ  : 0          ��ȡ�ɹ�
             else       ��ȡʧ��
*****************************************************************************/
int mdrv_pmu_get_voltage(EM_MODEM_CONSUMER_ID_E consumer_id, unsigned int *voltage_mv)
{
    return pmu_parf_ops.drv_modem_voltage_get(consumer_id, voltage_mv);
}

/*****************************************************************************
 �� �� ��  : mdrv_pmu_list_voltage
 ��������  : ͨ��ģ���ȡ��ѹ���÷�Χ�ӿ�
 �������  : consumer_id     �û�id
             list            ��ѹ��Χ����
             size            �����С
 �������  : ��
 �� �� ֵ  : 0          ��ȡ�ɹ�
             else       ��ȡʧ��
*****************************************************************************/
int mdrv_pmu_list_voltage(EM_MODEM_CONSUMER_ID_E consumer_id, unsigned short **list, unsigned int *size)
{
    return pmu_parf_ops.drv_modem_voltage_list(consumer_id, list, size);
}

/*****************************************************************************
 ����    : mdrv_pmu_enable_apt
 ����    : ͨ��ģ��ʹ��APT״̬�ӿ�
 ����    : modem_id       ����
 ���    : ��
 ����    : 1  APTʹ��/   0    APTδʹ��/  -1    ��ȡʧ��
*****************************************************************************/
int mdrv_pmu_enable_apt(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
    return pmu_parf_ops.drv_modem_apt_enable(modem_id, mode_id);
}

/*****************************************************************************
 ����    : mdrv_pmu_disable_apt
 ����    : ͨ��ģ��ȥʹ��APT״̬�ӿ�
 ����    : modem_id       ����
 ���    : ��
 ����    : 1  APTʹ��/   0    APTδʹ��/  -1    ��ȡʧ��
*****************************************************************************/
int mdrv_pmu_disable_apt(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
    return pmu_parf_ops.drv_modem_apt_disable(modem_id, mode_id);
}

/*****************************************************************************
 ����    : mdrv_pmu_get_aptstatus
 ����    : ͨ��ģ���ȡ��ǰAPT״̬�ӿ�
 ����    : modem_id       ����
 ���    : ��
 ����    : 1  APTʹ��/   0    APTδʹ��/  -1    ��ȡʧ��
*****************************************************************************/
int mdrv_pmu_get_aptstatus(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
    return pmu_parf_ops.drv_modem_apt_status_get(modem_id, mode_id);
}

/*****************************************************************************
 ����     : mdrv_pmu_set_modem_mode
 ����    : ͨ��ģ������Gģ��Wģ�ӿ�
 ����    : modem_id       ����
 ���    : ��
 ����  : 0         ���óɹ�/  else      ����ʧ��
*****************************************************************************/
int mdrv_pmu_set_modem_mode(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
    return pmu_parf_ops.drv_modem_mode_config(modem_id, mode_id);
}

/*****************************************************************************
 �� �� ��  : bsp_pa_poweron
 ��������  : ��pa�ϵ�
 �������  : @modem_id - 0:���� 1:����
 �������  : ��
 �� �� ֵ  : 0 - �ɹ�����0 - ʧ��
*****************************************************************************/
s32 bsp_pa_poweron(PWC_COMM_MODEM_E modem_id)
{
    return  pmu_parf_ops.pmu_pa_power_on(modem_id);
}

/*****************************************************************************
 �� �� ��  : bsp_pa_poweroff
 ��������  : ��pa�µ�
 �������  : @modem_id - 0:���� 1:����
 �������  : ��
 �� �� ֵ  : 0 - �ɹ�����0 - ʧ��
*****************************************************************************/
s32 bsp_pa_poweroff(PWC_COMM_MODEM_E modem_id)
{
    return  pmu_parf_ops.pmu_pa_power_off(modem_id);
}

/*****************************************************************************
 �� �� ��  : bsp_get_pa_powerstatus
 ��������  : ��ȡpa���µ�״̬
 �������  : @modem_id - 0:���� 1:����
 �������  : ��
 �� �� ֵ  : 0 - �ɹ�����0 - ʧ��
*****************************************************************************/
PWC_COMM_STATUS_E bsp_get_pa_powerstatus(PWC_COMM_MODEM_E modem_id)
{
    return  pmu_parf_ops.pmu_pa_power_status(modem_id);
}

/*****************************************************************************
 �� �� ��  : bsp_rf_poweron
 ��������  : ��rf�ϵ�
 �������  : @modem_id - 0:���� 1:����
 �������  : ��
 �� �� ֵ  : 0 - �ɹ�����0 - ʧ��
*****************************************************************************/
s32 bsp_rf_poweron(PWC_COMM_MODEM_E modem_id)
{
    return  pmu_parf_ops.pmu_rf_power_on(modem_id);
}

/*****************************************************************************
 �� �� ��  : bsp_rf_poweroff
 ��������  : ��rf�µ�
 �������  : @modem_id - 0:���� 1:����
 �������  : ��
 �� �� ֵ  : 0 - �ɹ�����0 - ʧ��
*****************************************************************************/
s32 bsp_rf_poweroff(PWC_COMM_MODEM_E modem_id)
{
    return  pmu_parf_ops.pmu_rf_power_off(modem_id);
}

/*****************************************************************************
 �� �� ��  : bsp_get_rf_powerstatus
 ��������  : ��ȡrf���µ�״̬
 �������  : @modem_id - 0:���� 1:����
 �������  : ��
 �� �� ֵ  : 0 - �ɹ�����0 - ʧ��
*****************************************************************************/
PWC_COMM_STATUS_E bsp_get_rf_powerstatus(PWC_COMM_MODEM_E modem_id)
{
    return  pmu_parf_ops.pmu_rf_power_status(modem_id);
}

/*
 * ��dpm�ṩ�Ľӿ�
 */
struct pa_rf_vote_map_stru pa_rf_vote_map[PA_RF_ID_MAX] = {
    {"PA0_pd", 0, 0,{0},{0},0,0,{0}},
    {"PA1_pd", 0, 0,{0},{0},0,0,{0}},
    {"RFIC0_pd", 0, 0,{0},{0},0,0,{0}},
    {"RFIC1_pd", 0, 0,{0},{0},0,0,{0}}
};

ST_PWC_SWITCH_STRU g_nv_pwc_switch_data = {0};

s32 parf_get_dts_info(u32 *channel_max_num)
{
    struct device_node *node = NULL;
    s32 ret = PARF_OK;

    if(!channel_max_num)
    {
        parf_print_error("ERROR: null pointer!\n");
        return PARF_ERROR;
    }

    /* ��ȡDTS�ڵ� */
    node = of_find_compatible_node(NULL, NULL, "hisilicon,pa_rf");/*[false alarm]:���д��벻��dead code*/
    if (!node)
    {
        parf_print_error("ERROR: pa_rf dts node not found!\n");
        return PARF_ERROR;
    }

    /* ��ȡchannel���� */
    ret = of_property_read_u32(node, "channel_max_num", channel_max_num);
    if(ret)
    {
        parf_print_error("ERROR: read channel_max_num from dts failed, ret = %d!\n", ret);
        return ret;
    }

    return PARF_OK;
}

void parf_ops_register(void)
{
#ifdef CONFIG_PASTAR
    pmu_parf_ops.pmu_pa_power_on = bsp_pmu_hi6561_pa_poweron;
    pmu_parf_ops.pmu_pa_power_off = bsp_pmu_hi6561_pa_poweroff;
    pmu_parf_ops.pmu_pa_power_status = bsp_pmu_hi6561_get_pa_powerstatus;
    pmu_parf_ops.pmu_rf_power_on = bsp_pmu_hi6561_rf_poweron;
    pmu_parf_ops.pmu_rf_power_off = bsp_pmu_hi6561_rf_poweroff;
    pmu_parf_ops.pmu_rf_power_status = bsp_pmu_hi6561_get_rf_powerstatus;
    pmu_parf_ops.drv_pastar_exc_check = drv_pmu_hi6561_exc_check;
    pmu_parf_ops.drv_modem_voltage_set = drv_pmu_hi6561_voltage_set;
    pmu_parf_ops.drv_modem_voltage_get = drv_pmu_hi6561_voltage_get;
    pmu_parf_ops.drv_modem_voltage_list = drv_pmu_hi6561_voltage_list;
    pmu_parf_ops.drv_modem_apt_enable = drv_pmu_hi6561_apt_enable;
    pmu_parf_ops.drv_modem_apt_disable = drv_pmu_hi6561_apt_disable;
    pmu_parf_ops.drv_modem_apt_status_get = drv_pmu_hi6561_apt_status_get;
    pmu_parf_ops.drv_modem_mode_config = drv_pmu_hi6561_mode_config;
#else
    pmu_parf_ops.pmu_pa_power_on = bsp_pmu_pa_poweron;
    pmu_parf_ops.pmu_pa_power_off = bsp_pmu_pa_poweroff;
    pmu_parf_ops.pmu_pa_power_status = bsp_pmu_get_pa_powerstatus;
    pmu_parf_ops.pmu_rf_power_on = bsp_pmu_rf_poweron;
    pmu_parf_ops.pmu_rf_power_off = bsp_pmu_rf_poweroff;
    pmu_parf_ops.pmu_rf_power_status = bsp_pmu_get_rf_powerstatus;
    pmu_parf_ops.drv_pastar_exc_check = drv_pmu_parf_exc_check;
    pmu_parf_ops.drv_modem_voltage_set = drv_pmu_modem_voltage_set;
    pmu_parf_ops.drv_modem_voltage_get = drv_pmu_modem_voltage_get;
    pmu_parf_ops.drv_modem_voltage_list = drv_pmu_modem_voltage_list;
    pmu_parf_ops.drv_modem_apt_enable = drv_pmu_modem_apt_enable;
    pmu_parf_ops.drv_modem_apt_disable = drv_pmu_modem_apt_disable;
    pmu_parf_ops.drv_modem_apt_status_get = drv_pmu_modem_apt_status_get;
    pmu_parf_ops.drv_modem_mode_config = drv_pmu_modem_mode_config;
#endif
    return;
}

int bsp_pa_rf_dpm_init(void)
{
    s32 i = 0;
    u32 ret = PARF_OK;

    /*��ʼ��spinlock*/
    for(i = 0; i < PA_RF_ID_MAX; i++)
    {
        spin_lock_init(&pa_rf_vote_map[i].spinlock);
    }

    ret = bsp_nvm_read(NV_ID_DRV_NV_PWC_SWITCH, (u8 *)(&g_nv_pwc_switch_data), sizeof(ST_PWC_SWITCH_STRU));
    if(ret != NV_OK)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PARF, "ERROR: bsp_nvm_read failed, ret = %d\n", ret);
        return (int)ret;
    }

    return PARF_OK;
}

/*****************************************************************************
 �� �� ��  : bsp_pa_rf_init
 ��������  : ��ȡregulator
 �������  : ��
 �������  : ��
 �� �� ֵ  : 0:�ɹ���else - ʧ�ܡ�ʧ��ʱ����ֵ��bit0~bit4��Ӧ��ȡʧ�ܵ�regulator_pmu id
*****************************************************************************/
s32 bsp_pa_rf_init(void)
{
    s32 ret = PARF_OK;

#ifdef CONFIG_PASTAR
#else
    NV_DRV_PARF_SWITCH_STRU switchs;
    ret = (s32)bsp_nvm_read(NV_ID_DRV_PA_RF_SWITCH, (u8*)&switchs, sizeof(NV_DRV_PARF_SWITCH_STRU));
    if(ret)
    {
        switchs.cont.u32= NV_PARF_SWITCH_DEFAULT_VAL;
        parf_print_error("ERROR: bsp_nvm_read failed %d,set to default %#x\n", ret, switchs.cont.u32);
    }
    s_is_gpa_usepmu = switchs.cont.bits.gpa;
    /* regulatorע�� */
    ret = parf_regulator_register(switchs);
    if(ret != PARF_OK)
    {
        parf_print_error("parf_regulator_register failed, ret = %d\n", ret);
		parf_print_error("pa_rf init failed\n");
		return ret;
    }
#endif

    /* ��ȡ֧�ֵ����ͨ���� */
    ret = parf_get_dts_info(&g_channel_max_num);
    if(ret != PARF_OK)
    {
        parf_print_error("parf_get_dts_info failed, ret = %d\n", ret);
		parf_print_error("pa_rf init failed\n");
		return ret;
    }

    /* dpm���ܳ�ʼ�� */
    ret = bsp_pa_rf_dpm_init();
    if(ret != PARF_OK)
    {
        parf_print_error("bsp_pa_rf_dpm_init failed, ret = %d\n", ret);
		parf_print_error("pa_rf init failed\n");
		return ret;
    }

    /* opsע�� */
    parf_ops_register();

    /* ��ʼ��ok */
    parf_print_always("pa_rf init ok\n");

    return PARF_OK;
}

/*�ײ����ʵ��PA���ϵ�PA0--[0]PA1--[1]*/
int bsp_pa_power_up(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    unsigned long flags = 0;
    unsigned long sub_scripts = 0;
    int ret = PARF_OK;

    /* GPAʹ�õ�ع��磬������PMU */
    if((PWC_COMM_MODE_GSM == enCommMode) && (!s_is_gpa_usepmu))
    {
        return 0;
    }
    sub_scripts = (enModemId == PWC_COMM_MODEM_0) ? PA0 : PA1;

    spin_lock_irqsave(&pa_rf_vote_map[sub_scripts].spinlock, flags);
    pa_rf_vote_map[sub_scripts].enable_count[enCommMode] ++;
    pa_rf_vote_map[sub_scripts].enable_real ++;

    ret = bsp_pa_poweron(enModemId);
    if(!(pa_rf_vote_map[sub_scripts].vote & ((unsigned int)1 << enCommMode)))   /* Ͷ�ϵ�Ʊ */
    {
        pa_rf_vote_map[sub_scripts].vote |= ((unsigned int)1 << enCommMode);
    }
    spin_unlock_irqrestore(&pa_rf_vote_map[sub_scripts].spinlock, flags);

    return ret;
}

int bsp_pa_power_down(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    unsigned long flags = 0;
    unsigned long sub_scripts = 0;
    unsigned int drx_pa_pd;
    int ret = PARF_OK;

    /* GPAʹ�õ�ع��磬������PMU */
    if((PWC_COMM_MODE_GSM == enCommMode) && (!s_is_gpa_usepmu))
    {
        return 0;
    }

    /* ������������ */
    sub_scripts = (enModemId == PWC_COMM_MODEM_0) ? PA0 : PA1;
    drx_pa_pd = (enModemId == PWC_COMM_MODEM_0) ? g_nv_pwc_switch_data.drx_pa0_pd : g_nv_pwc_switch_data.drx_pa1_pd;

    spin_lock_irqsave(&pa_rf_vote_map[sub_scripts].spinlock, flags);
    pa_rf_vote_map[sub_scripts].disable_count[enCommMode] ++;   /* ���ýӿڵĴ����ۼ� */

    if(pa_rf_vote_map[sub_scripts].vote & ((unsigned int)1 << enCommMode))  /* ȥ���ϵ�Ʊ��ͬ���µ� */
    {
        pa_rf_vote_map[sub_scripts].vote &= ~((unsigned int)1 << enCommMode);
    }

    if(!pa_rf_vote_map[sub_scripts].vote)   /* ����ģ��ͬ���µ磬�ſ����µ� */
    {
        /*����NV�����������Ƿ�ر�*/
        if (drx_pa_pd == 0)
        {
            pa_rf_vote_map[sub_scripts].disable_real ++;    /* ʵ���µ�Ĵ����ۼ� */
            ret = bsp_pa_poweroff(enModemId);
        }
    }
    spin_unlock_irqrestore(&pa_rf_vote_map[sub_scripts].spinlock, flags);

    return ret;
}

PWC_COMM_STATUS_E bsp_pa_power_status(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    /* GPAʹ�õ�ع��磬ֱ�ӷ����ϵ�״̬ */
    if((PWC_COMM_MODE_GSM == enCommMode) && (!s_is_gpa_usepmu))
    {
        return PWRCTRL_COMM_ON;
    }
    return bsp_get_pa_powerstatus(enModemId);
}

/*�ײ����ʵ��RFIC���ϵ�RFIC0--[2] RFIC1--[3]*/
int bsp_rfic_power_up(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    unsigned long flags = 0;
    unsigned long sub_scripts = 0;
    int ret = PARF_OK;

    sub_scripts = (enModemId == PWC_COMM_MODEM_0) ? RFIC0 : RFIC1;

    spin_lock_irqsave(&pa_rf_vote_map[sub_scripts].spinlock, flags);
    pa_rf_vote_map[sub_scripts].enable_count[enCommMode] ++;
    pa_rf_vote_map[sub_scripts].enable_real ++;

    if(RFIC1 == sub_scripts)    /* ���ڸ���rf�����⴦�� */
    {
        bsp_pmu_tcxo1_en_enable(RFIC1_ID_0);
    }

    ret = bsp_rf_poweron(enModemId);
    if(!(pa_rf_vote_map[sub_scripts].vote & ((unsigned int)1 << enCommMode)))
    {
        pa_rf_vote_map[sub_scripts].vote |= ((unsigned int)1 << enCommMode);
    }
    spin_unlock_irqrestore(&pa_rf_vote_map[sub_scripts].spinlock, flags);

    return ret;
}
int bsp_rfic_power_down(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    unsigned long flags = 0;
    unsigned long sub_scripts = 0;
    unsigned int drx_pa_pd;
    int ret = PARF_OK;

    /* ���������� */
    sub_scripts = (enModemId == PWC_COMM_MODEM_0) ? RFIC0 : RFIC1;
    drx_pa_pd = (enModemId == PWC_COMM_MODEM_0) ? g_nv_pwc_switch_data.drx_rfic0_pd : g_nv_pwc_switch_data.drx_rfic1_pd;

    spin_lock_irqsave(&pa_rf_vote_map[sub_scripts].spinlock, flags);
    pa_rf_vote_map[sub_scripts].disable_count[enCommMode] ++;   /* ���ýӿڵĴ����ۼ� */

    if(pa_rf_vote_map[sub_scripts].vote & ((unsigned int)1 << enCommMode))  /* ȥ���ϵ�Ʊ��ͬ���µ� */
    {
        pa_rf_vote_map[sub_scripts].vote &= ~((unsigned int)1 << enCommMode);
    }

    if(!pa_rf_vote_map[sub_scripts].vote)   /* ����ģ��ͬ���µ磬�ſ����µ� */
    {
        /* ����NV�����������Ƿ�ر� */
        if (drx_pa_pd == 0)
        {
            pa_rf_vote_map[sub_scripts].disable_real ++;        /* ʵ���µ�Ĵ����ۼ� */
            ret = bsp_rf_poweroff(enModemId);
            if(RFIC1 == sub_scripts)
            {
                bsp_pmu_tcxo1_en_disable(RFIC1_ID_0);
            }
        }
    }
    spin_unlock_irqrestore(&pa_rf_vote_map[sub_scripts].spinlock, flags);

    return ret;
}

PWC_COMM_STATUS_E bsp_rfic_power_status(PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel)
{
    return bsp_get_rf_powerstatus(enModemId);
}

/*****************************************************************************
* �� ��    : bsp_fem_power_down
* �� ��    : fem �µ��׮
* �� ��    : ��
* �� ��    :
* �� ��    : rf��Դ����״̬
* ˵ ��    :
*****************************************************************************/
int bsp_fem_power_down(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return 0;
}
/*****************************************************************************
 ����    : bsp_fem_power_up
 ����    : RF �ϵ��׮
 ����    : ��
 ���    : ��
 ����    : rf��Դ����״̬
*****************************************************************************/
int bsp_fem_power_up(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return 0;
}
/*****************************************************************************
 �� �� ��  :bsp_pa_power_status
 ��������  :RF��Դ״̬��ѯ��׮
 �������  :
 �������  :
 �� �� ֵ  : pa��Դ����״̬
*****************************************************************************/
PWC_COMM_STATUS_E bsp_fem_power_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return PWRCTRL_COMM_ON;
}

int bsp_rfclk_enable(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return 0;
}

int bsp_rfclk_disable(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return 0;
}
#else
#include <osl_types.h>
#include <mdrv_pmu.h>
#include <mdrv_pm.h>
#include "pa_rf_balong.h"
u32 g_channel_max_num = 0;  /* ���channel���� */

/*
 * �����Ǵ�׮�ӿڣ�ֻ�е�PASTAR��PMU��������ʱ���Ż��õ���Щ�ӿ�
 */

s32 bsp_pa_rf_init(void)
{
    parf_print_error("NOTICE: pa_rf_init stub!\n");
    return (s32)PARF_OK;
}

#endif

#ifdef __cplusplus
}
#endif
