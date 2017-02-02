/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : tcxo_balong.c
  �� �� ��   : ����
  ��    ��   : �쾭��x00221564
  ��������   : 2013��8��26��
  ����޸�   :
  ��������   : tcxo_balong.cͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   :  �쾭��x00221564
    ��    ��   : 2013��8��26��
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __TCXO_BALONG_H__
#define __TCXO_BALONG_H__

#include <mdrv_pm.h>
#include <bsp_om.h>
#include <bsp_nvim.h>
#include <osl_irq.h>
#include <bsp_hardtimer.h>
#include <bsp_softtimer.h>
#include <hi_pwrctrl_interface.h>
#include <product_config.h>
#include <drv_nv_def.h>
#include <drv_nv_id.h>
#include <bsp_memmap.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define PWC_TCXO_INITED 1
#define PWC_TCXO_UNINITED 0

#define TCXO_STABLE_TIME 0x5            /*150us*/
#define TCXO_STABLE_TIME_SCLICE_NUM 5   /*150us*/

/*�����Ӧ��mskֵ*/
#define CALC_REG_MSK(bit_start, bit_end) \
    (((0x1 << (bit_end - bit_start + 1)) - 1) << bit_start)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
typedef enum tagPWC_TCXO_CFG_E
{
    PWC_TCXO_CFG_DCARD_SFUNC_SEL_0,  /*V7R2 bit 00����*/ /*˫������,channel 0ʹ��tcxo0��channel 1ʹ��tcxo0*/
    PWC_TCXO_CFG_DCARD_DFUNC_SEL_1,                               /*˫��˫��,channel 0ʹ��tcxo1��channel 1ʹ��tcxo0*/
    PWC_TCXO_CFG_DCARD_DFUNC_SEL_0,  /*V7R2 bit 10����*/ /*˫��˫��,channel 0ʹ��tcxo0��channel 1ʹ��tcxo1*/
    PWC_TCXO_CFG_DCARD_SFUNC_SEL_1,                               /*˫������,channel 0ʹ��tcxo1��channel 1ʹ��tcxo1*/
    PWC_TCXO_CFG_SCARD_SFUNC_SEL_0,                               /*��������,channel 0ʹ��tcxo0��channel 1ʹ��tcxo0*/
    PWC_TCXO_CFG_SCARD_SFUNC_SEL_1,                               /*��������,channel 0ʹ��tcxo1��channel 1ʹ��tcxo1*/
    PWC_TCXO_CFG_BUTT
}PWC_TCXO_CFG_E;

typedef enum tagPWC_TCXO_TIMER_STATUS_E
{
    PWC_TCXO_TIMER_RUNNING,
    PWC_TCXO_TIMER_STOP,
    PWC_TCXO_TIMER_BUTT
}PWC_TCXO_TIMER_STATUS_E;

typedef enum tagPWC_TCXO_ID_E
{
    PWC_TCXO_ID_0,
    PWC_TCXO_ID_1,
    PWC_TCXO_ID_BUTT
}PWC_TCXO_ID_E;

typedef enum tagPWC_PMU_TCXO_EN
{
    RFIC1_ID_0,
    TCXO1_ID_1,
    TCXO_ID_BUTT
}PMU_TCXO_EN;

/*****************************************************************************
  STRUCT����
*****************************************************************************/
struct tcxo_timer_callback{
    PWC_TCXO_FUNCPTR  routine;             /* timer��ʱ�ص����� */
    BSP_S32                   arg;                   /* timer��ʱ�ص����� */
    BSP_U32                   timerValue;        /* ����ֵ ms*/
};

/*
*TCXO��Ϣ�ṹ��
*g_stTcxoTimerStru:��TCXO��timer�ص���Ϣ
*timer:��timer��Ϣ
*timer_status:��timer������״̬
*tcxo_status:��TCXO��״̬
*/
struct tcxo_info{
    struct tcxo_timer_callback        g_stTcxoTimerStru[ PWC_COMM_MODE_BUTT];
    PWC_TCXO_TIMER_STATUS_E    timer_status;
    int                                         tcxo_status;
};

/*TCXO��ʼ������*/
int tcxo_init_configure(void);

/*tcxo debug*/
void debug_tcxo_function(PWC_COMM_MODEM_E  tcxoId, PWC_COMM_MODE_E enModeType);
void debug_tcxo(void);
void debug_pastar_dpm(void);

/***************************************************************************
 �� �� ��  : bsp_pmu_tcxo1_en_enable
 ��������  :ʹ��PMU TCXO1 EN
 ���ú���  :
 ��������  :

 �޸���ʷ      :
**************************************************************************/
void bsp_pmu_tcxo1_en_enable(PMU_TCXO_EN bit_value);

/***************************************************************************
 �� �� ��  : bsp_pmu_tcxo1_en_disable
 ��������  :ȥʹ��PMU TCXO1 EN
 ���ú���  :
 ��������  :

 �޸���ʷ      :
**************************************************************************/
void bsp_pmu_tcxo1_en_disable(PMU_TCXO_EN bit_value);

#if defined(CONFIG_K3V3_CLK_CRG)
void bsp_tcxo1_set_flag(unsigned int flag);
void bsp_tcxo1_enable_first(void);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of tcxo_balong.h */

