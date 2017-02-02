/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : pwrctrl_common.h
  �� �� ��   : ����
  ��    ��   : ������ 56193
  ��������   : 2012��7��25��
  ����޸�   :
  ��������   : pwrctrl_common.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��7��25��
    ��    ��   : ������ 56193
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include <soc_baseaddr_interface.h>
#if defined(CHIP_BB_HI6210)

#else
#include <soc_sctrl_interface.h>
#endif
#include <soc_timer_interface.h>
#include <pwrctrl_multi_memcfg.h>

#include <pwrctrl_multi_def.h>
#include <mntn/excDrv.h>

#ifndef __PWRCTRL_COMMON_H__
#define __PWRCTRL_COMMON_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
#define PWC_REG_UART_PHY            (SOC_UART0_BASE_ADDR)
#define PWRCTRL_SLICETIMER_XLOAD    (0xFFFFFFFF)
#define PWRCTRL_SLICE_UNIT_CONV     (1000)           /*s -> us*/
#define PWC_MCU_SLICE_TIMER_ID      (PWC_SLICE_TIMER_ID)


#define PWRCTRL_ACPU_PD_SIZE        0x200
#define PWRCTRL_ACPU_HOTPLUG_SIZE   0x200
#define PWRCTRL_INIT_FLAG           0x12345678

/*A ���쳣��Ϣ������*/
#define EXCH_ACPU_CORE_PWC_ADDR     (PWRCTRL_EXC_ACPU_ADDR - EXCH_BASE_ADDR + EXCH_DDR_BASE_ADDR)  /*phy addr*/
#define EXCH_ACPU_CORE_PWC_ADDR_V   (PWRCTRL_EXC_ACPU_ADDR)  /*virtue addr*/
#define EXCH_ACPU_CORE_PWC_SIZE     (PWRCTRL_EXC_ACPU_SIZE)
#define EXCH_ACPU_CORE_HOTPLUG_ADDR (EXCH_ACPU_CORE_PWC_ADDR_V + PWRCTRL_ACPU_PD_SIZE)



#define EXCH_ACPU_CORE_INFO_OFFSET      (sizeof(PWRCTRL_ACPU_EXC_PD_STRU))





#ifdef WIN32    /*for pc ut/st*/
#define IO_ADDRESS(x)               (0xffff0000)
#endif

/*log output*/
#ifdef WIN32
#define PWC_TRACE(enLogLevel, fmt, arg0, arg1, arg2, arg3, arg4, arg5)     \
    printf("["#enLogLevel"]"fmt"\n", arg0, arg1, arg2, arg3, arg4, arg5)

#else
#define PWC_TRACE(enLogLevel, fmt, arg0, arg1, arg2, arg3, arg4, arg5)     \
    printk(fmt, arg0, arg1, arg2, arg3, arg4, arg5)
#endif

#define PWC_LOG_MEM(info, addr, size) \
    pwrctrl_log_mem(info, addr, size)

#ifdef _PWRCTRL_DEB_VERSION_
#define PWRCTRL_DEBUG_TRACE(data) \
{\
    if( 0 == g_ulPwrctrlDebugTrace)\
    {\
        *(volatile u8_t *)(UART_CCPU_BASE) = data;\
    }\
    if( 1 == g_ulPwrctrlDebugTrace)\
    {\
         PWC_TRACE(PWC_LOG_MAX, "%c",data);\
    }\
}
#else
#define PWRCTRL_DEBUG_TRACE(data)
#endif

extern unsigned int g_ulpwrctrl_print_switch;

/*����EM_PWC_SWITCHģ�黮��*/

#define PRINT_PWC_DBG(mod, fmt, args...)  \
do { \
    if (0 != (g_ulpwrctrl_print_switch&(1<<mod))) \
    { \
        printk(fmt, ## args) ; \
    } \
} while (0)

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

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

typedef struct PWRCTRL_ACPU_EXC_PD_STRU_S
{
    u32_t  SlpCnt;         //+0X0
    u32_t  WkCnt;          //+0X4
    u32_t  rev[2];         //+0X8

    u32_t  SlpMgrSTm;
    u32_t  SlpSTm;
    u32_t  WkSTm;
    u32_t  WkMgrSTm;

    u32_t  SlpIpcCnt;
    u32_t  SlpIpcSTm;
    u32_t  WfiRetCnt;
    u32_t  WfiRetSTm;

    u32_t  mcPdCnt;     //��core(master core)��¼:�Դ�core�����µ�״̬
    u32_t  mcPuCnt;
    u32_t  mcPdSTm;
    u32_t  mcPuSTm;

    u32_t  mcWfiFailCnt;
    u32_t  mcWfiFailSTm;
    u32_t  rev2[2];
}PWRCTRL_ACPU_EXC_PD_STRU;

typedef struct PWRCTRL_ACPU_EXC_LOG_STRU_S
{
    PWRCTRL_ACPU_EXC_PD_STRU  core0;
    PWRCTRL_ACPU_EXC_PD_STRU  core1;
    PWRCTRL_ACPU_EXC_PD_STRU  core2;
    PWRCTRL_ACPU_EXC_PD_STRU  core3;

}PWRCTRL_ACPU_EXC_LOG_STRU;

/*****************************************************************************
  7 UNION����
*****************************************************************************/

/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/
extern ST_PWC_SWITCH_STRU * g_stAcpuPwcSwitch;
extern PWRCTRL_ACPU_EXC_LOG_STRU * g_stAcpuPwcExcLog;
extern u32_t   g_ulPwcDebugTrace;
extern u32_t g_pwc_init_flag;


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern s32_t pwrctrl_clr_bits (u32_t ulRegAddr, u32_t ulMask);
extern s32_t pwrctrl_common_initial ( void_t );
extern s32_t pwrctrl_debug_info_show( void_t );
extern u32_t  pwrctrl_get_slice_time( void_t );
extern u32_t pwrctrl_is_bit_set ( u32_t addr,  u32_t offset);
extern s32_t pwrctrl_mem_cpy ( void_t * dest, void_t * src, u32_t size );
extern u32_t pwrctrl_read_reg32 ( u32_t ulRegAddr );
extern s32_t pwrctrl_timer_delay (u32_t time);
extern s32_t pwrctrl_write_reg32( u32_t ulRegAddr, u32_t ulRegVal);
extern s32_t pwrctrl_set_bits (u32_t ulRegAddr, u32_t ulMask);
extern s32_t pwrctrl_is_func_on ( EM_PWC_SWITCH funId );
extern void_t pwrctrl_log_mem(u8_t* info, void_t* addr, u32_t size);
extern void_t pwrctrl_write_reg32_mask (u32_t ulRegAddr, u32_t ulRegVal, u32_t ulMask);
extern u32_t pwrctrl_read_reg32_mask(u32_t ulRegAddr, u32_t ulMask);
extern bool_t pwrctrl_is_bits_set(u32_t ulRegAddr, u32_t ulMask);
extern bool_t pwrctrl_is_bits_clr(u32_t ulRegAddr, u32_t ulMask);









#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of bsp_pwc_common.h */
