/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : pwrctrl_perimgr.h
  �� �� ��   : ����
  ��    ��   : ������ 56193
  ��������   : 2012��7��25��
  ����޸�   :
  ��������   : pwrctrl_perimgr.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��7��25��
    ��    ��   : ������ 56193
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/


#ifndef __PWRCTRL_PERIMGR_H__
#define __PWRCTRL_PERIMGR_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define PWRCTRL_SLICE_TIMER_ADDR                (SOC_TIMER_TIMERN_VALUE_ADDR(SOC_MTimer5_BASE_ADDR,0))             /*tobedone*/
#define PWRCTRL_SLICE_TIMER_VADDR               IO_ADDRESS((SOC_TIMER_TIMERN_VALUE_ADDR(SOC_MTimer5_BASE_ADDR,0))) /*tobedone*/

/* in 19.2M clock count per ms is: xxx */
#define PWRCTRL_TIMECLK_19M2                (19200000)
/* in 32K clock count per ms is: xxx */
#define PWRCTRL_TIMECLK_32K                 (32768)

#define PWRCTRL_ACPU_TIMER_TOTAL_NUM        (18)
#define PWRCTRL_INTENABLE                   (1<<5)      /* enable interrupt 1 disabel 0 enable */
#define PWRCTRL_FREE                        (1<<6)      /* free mode */
#define PWRCTRL_ENABLE                      (1<<7)      /* enabling timer */

/*1:ps 32k, 10: slice, 11: drv-AOTimer*/
#define PWRCTRL_ALWAYSON_TIMER     (BIT(TIMER_CCPU_MSP_ID)|BIT(TIMER_ACPU_SOFTTIMER_ID)|BIT(TIMER_ALL_SLICE_ID)) /*tobedone*/

/* timer enougth to enter sleep,UNIT 1MS*/
#define PWRCTRL_MAX_TIME                    (0xFFFFFFFF)
#define PWRCTRL_THOUSAND_TIME               (1000)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/
typedef struct
{
    u32_t ulTimerLoad;             /* Load Register */
    u32_t ulTimerValue;            /* Current Value Register */
    u32_t ulTimerControl;          /* Control Register */
    u32_t ulTimerIntClr;           /* Interrupt Clear Register */
    u32_t ulTimerRIS;              /* Raw Interrupt Status Register */
    u32_t ulTimerMIS;              /* Masked Interrupt Status Register */
    u32_t ulTimerBGLoad;           /* Background Load Register */
} PWRCTRL_TIMER_REG_STRU;


/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/
#define PWRCTRL_TIMER_LOAD_ADDR(TimerAddr) \
    ((u32_t)&(((PWRCTRL_TIMER_REG_STRU *)(TimerAddr))->ulTimerLoad))

#define PWRCTRL_TIMER_VALUE_ADDR(TimerAddr) \
    ((u32_t)&(((PWRCTRL_TIMER_REG_STRU *)(TimerAddr))->ulTimerValue))

#define PWRCTRL_TIMER_CONTROL_ADDR(TimerAddr) \
    ((u32_t)&(((PWRCTRL_TIMER_REG_STRU *)(TimerAddr))->ulTimerControl))




/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/
extern struct notifier_block pm_reboot_nb;

/*****************************************************************************
  10 ��������
*****************************************************************************/
extern u32_t pwrctrl_get_timer_count( void_t );
extern u32_t pwrctrl_get_timer_base_addr( u32_t timerId);
extern u32_t  pwrctrl_get_timer_clk( u32_t timerId);
extern u32_t pwrctrl_get_timer_active( u32_t timerId);
extern u32_t pwrctrl_get_timer_cnt( u32_t timerId);
extern s32_t pwrctrl_sleep_mgr_get_next_schedule_time( u32_t ulAllTimer,u32_t *pTimerID, u32_t *pNextScheduleTime);




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of bsp_pwc_perimgr.h */
