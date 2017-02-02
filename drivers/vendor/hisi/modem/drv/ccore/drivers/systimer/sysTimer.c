/*************************************************************************
*   ��Ȩ����(C) 1987-2009, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  BSP_CLK.c
*
*   ��    �� :  liumengcun
*
*   ��    �� :  ���ļ�����Ϊ"CLK_UsrTimer.c", ʵ���û�ʱ�ӳ�ʼ��,�ҽ�,����,�رյȹ���
*
*   �޸ļ�¼ :  2009��3��5��  v1.00  liumengcun  ����
*               2009��5��19�� v1.00  liumengcun  �޸�
*   BJ9D00787:��ST BSP CLOCK���û�����TIMER����������ȥʹ�ܡ�ʹ��TIMER����������TIMER
*              �Ĵ�������Ԥ�ڣ����Ҵ�������������з����˳�������
*   BJ9D00699: �û�ʱ��BSP_USRCLK_TimerMilliSecStart()���ö�ʱ����ʱ�ĺ���ֵС��ϵͳ
*              ��Сֵû�з��ش���
*   BJ9D00652: ���õ���TIMERΪ�������Сֵ������ż������ϵͳ����������
*				2009��5��19�� v1.00  liumengcun  �޸�
*	BJ9D00953:����һ������timer��Ȼ�����BSP_USRCLK_TimerStop���ýӿ�ֻΪone shot
*             timer�ṩ������������timer��ͣ����
*************************************************************************/
#include "copyright_wrs.h"
#include "vxWorks.h"
#include "logLib.h"
#include "tickLib.h"
#include "stdlib.h"
#include "string.h"
#include "iv.h"
#include "intLib.h"
#include "prjParams.h"

#include "mdrv.h"
#include "sysTimer.h"


//BSP_U32  g_u32TickCnt;

/* locals */
/*ϵͳʱ��*/
LOCAL SYSCLKFUNCPTR sysClkRoutine	= NULL; /* routine to call on clock interrupt */
LOCAL int sysClkArg		= 0;    /* its argument */
LOCAL int sysClkRunning		= FALSE;
LOCAL int sysClkConnected	= FALSE;
LOCAL int sysClkTicksPerSecond	= 100;
UINT32 g_u32sysClkTickCounter = 0;
UINT32 g_sysIntFirstTime = 0;
//int g_sysIntFirstTime = 0;


//int g_sysStampIntFirstTime = 0;
//int g_softTimeIntFirstTime = 0;


extern void sysHwInit2 (void);

//LOCAL BOOL	BspClkRunning = FALSE;   /* bsp clk running flag */
//LOCAL int BspClkTicksPerSecond = 100;
//int g_UsrIntFirstTime = 0;
extern void cpufreq_checkload_in_sysint(void);
/*****************************************************************************
* �� �� ��  : sysClkInt
*
* ��������  : This routine handles the system clock interrupt.  It is attached
*             to the clock interrupt vector by the routine sysClkConnect().
*
* �������  : ��
* �������  : ��
* �� �� ֵ  : ��
*
* �޸ļ�¼  : 2009��1��20��   liumengcun  creat

*****************************************************************************/
void sysClkInt (void)
{
    /* ��ȡ�Ĵ������ֵ*/
    UINT readValue;

    /*SYS CLK*/
    BSP_REG_READ(SYSTIMER_BASE_ADDR, CLK_REGOFF_INTSTATUS, readValue);

    if(readValue != 0)
    {
    	/* ϵͳʱ��tick����*/
    	g_u32sysClkTickCounter++;

        /*���ж�:�˴�V7R2�� p532�в��죬��platform�´���*/
	systimer_int_clear(SYSTIMER_BASE_ADDR);

        /* If any routine attached via sysClkConnect(), call it */
        if (sysClkRoutine != NULL)
        {
            (* sysClkRoutine) (sysClkArg);
        }
    }
    cpufreq_checkload_in_sysint();
}

/*****************************************************************************
* �� �� ��  : sysClkConnect
*
* ��������  : This routine specifies the interrupt service routine to be called
*             at each clock interrupt.  It does not enable system clock interrupts.
*             Normally it is called from usrRoot() in usrConfig.c to connect
*             usrClock() to the system clock interrupt.
*
* �������  : FUNCPTR routine   routine to be called at each clock interrupt
              int arg	        argument with which to call routine
* �������  : ��
* �� �� ֵ  : OK, or ERROR if the routine cannot be connected to the interrupt.
*
* �޸ļ�¼  : 2009��1��20��   liumengcun  creat

*****************************************************************************/
STATUS sysClkConnect
    (
    SYSCLKFUNCPTR routine,	  /* routine to be called at each clock interrupt */
    int arg		          /* argument with which to call routine */
    )
    {
    if (sysClkConnected == FALSE)
    {
    	sysHwInit2 ();	  /* XXX for now -- needs to be in usrConfig.c */
    	sysClkConnected = TRUE;
    }

    sysClkRoutine = NULL; /* ensure routine not called with wrong arg */

    sysClkArg	  = arg;
    sysClkRoutine = routine;

    return OK;
    }

/*****************************************************************************
* �� �� ��  : sysClkDisable
*
* ��������  : This routine disables system clock interrupts.
*
* �������  : ��
* �������  : ��
* �� �� ֵ  : ��
*
* �޸ļ�¼  : 2009��1��20��   liumengcun  creat

*****************************************************************************/
void sysClkDisable (void)
{
    if (sysClkRunning)
	{
	    /* �ر��ж�ʹ�ܼĴ���*/
        BSP_REG_WRITE(SYSTIMER_BASE_ADDR,CLK_REGOFF_CTRL, CLK_DEF_DISABLE);

    	/* ϵͳʱ��tick��������*/
    	g_u32sysClkTickCounter = 0;
    	sysClkRunning = FALSE;
	}
}
/*****************************************************************************
* �� �� ��  : sysClkEnable
*
* ��������  : This routine enables system clock interrupts.
*
* �������  : ��
* �������  : ��
* �� �� ֵ  : ��
*
* �޸ļ�¼  : 2009��1��20��   liumengcun  creat

*****************************************************************************/
void sysClkEnable (void)
{
    UINT32 tc;
    unsigned int u32Times = 100;
    unsigned int i = 0;

    if (!sysClkRunning)
	{
    	/* ϵͳtick��������*/
    	g_u32sysClkTickCounter = 0;

        BSP_REG_WRITE(SYSTIMER_BASE_ADDR,CLK_REGOFF_CTRL, CLK_DEF_DISABLE);

    	/* Calculate the timer value*/
    	tc = (UINT32)((SYS_TIMER_CLK / sysClkTicksPerSecond) - AMBA_RELOAD_TICKS);

    	/* Load Timer Reload value into Timer registers */
        BSP_REG_WRITE (SYSTIMER_BASE_ADDR,CLK_REGOFF_LOAD, tc);

        /* ��ѯ������ʹ���Ƿ���Ч */
	i = systimer_check_enable_success();
        if(i == u32Times)
        {
            logMsg("write LoadValue error\n",1,2,3,4,5,6);
            return;
        }

        BSP_REG_WRITE(SYSTIMER_BASE_ADDR,CLK_REGOFF_CTRL, CLK_DEF_ENABLE);

        /*��һ������ʱ��Ҫʹ���ж�*/
    	if(0 == g_sysIntFirstTime)
        {
        	/* enable clock interrupt in interrupt controller */
        	TIMER_INT_ENABLE (INT_LVL_SYSTIMER);
        	g_sysIntFirstTime = 1;
        }

    	sysClkRunning = TRUE;
	}
}
/*****************************************************************************
* �� �� ��  : sysClkRateGet
*
* ��������  : This routine returns the interrupt rate of the system clock.
*
* �������  : ��
* �������  : ��
* �� �� ֵ  : The number of ticks per second of the system clock.
*
* �޸ļ�¼  : 2009��1��20��   liumengcun  creat

*****************************************************************************/
int sysClkRateGet (void)
{
    return sysClkTicksPerSecond;
}

/*****************************************************************************
* �� �� ��  : sysClkRateSet
*
* ��������  : This routine sets the interrupt rate of the system clock.  It does
*             not enable system clock interrupts unilaterally, but if the system
*             clock is currently enabled, the clock is disabled and then
*             re-enabled with the new rate.  Normally it is called by usrRoot()
*             in usrConfig.c.
*
* �������  : int ticksPerSecond   number of clock interrupts per second
* �������  : ��
* �� �� ֵ  : OK, or ERROR if the tick rate is invalid or the timer cannot be set.
*
* �޸ļ�¼  : 2009��1��20��   liumengcun  creat

*****************************************************************************/
STATUS sysClkRateSet
    (
    int ticksPerSecond	    /* number of clock interrupts per second */
    )
    {
    if (ticksPerSecond < SYS_CLK_RATE_MIN || ticksPerSecond > SYS_CLK_RATE_MAX)
    {
        logMsg("sysClkRateSet err, ticksPerSecond: %d \n",ticksPerSecond,0,0,0,0,0);
	    return ERROR;
    }

    sysClkTicksPerSecond = ticksPerSecond;

    if (sysClkRunning)
	{
    	sysClkDisable ();
    	sysClkEnable ();
	}

    return OK;
    }

/*****************************************************************************
* �� �� ��  : sysClkTicksGet
*
* ��������  : ���ϵͳʱ������������tick��.
*
* �������  : ��
* �������  : ��
* �� �� ֵ  : ϵͳʱ������������tick��.
*
* �޸ļ�¼  : 2009��2��24��   liumengcun  creat

*****************************************************************************/
UINT32 sysClkTicksGet (void)
{
    return g_u32sysClkTickCounter;
}

