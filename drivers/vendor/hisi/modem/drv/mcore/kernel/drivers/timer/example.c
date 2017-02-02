
/*��ʾ������������ʱ������ʱ��id1Ϊִֻ��һ�Σ�
 *��ʱ��id2Ϊ������ѭ��ִ��*/

#include "cmsis_os.h"
#include "printk.h"
#include <osl_types.h>
int countNum = 0,countNum1=0;
osSemaphoreId      test_sem;    
osSemaphoreDef(test_sem);


/****************************************************
 *        1������ص���������                            *
 ****************************************************/
u32 args1;                                               /*Timer1 �ص�����              */
u32 args2;                                               /*Timer2 �ص�����              */


/****************************************************
 *        2������ص�����                                       *
 ****************************************************/
void Timer1_callback(void const *args)
{
	countNum1++;
}
void Timer2_callback(void const *args)
{
	countNum++;
	if(countNum==10)
		osSemaphoreRelease(test_sem);
}

/****************************************************
 *        3������Timer������                                    *
 ****************************************************/

osTimerDef (Timer1,Timer1_callback);
osTimerDef (Timer2,Timer2_callback);
osTimerId Timer1;                                        /*����������ʱ����һ��id1Ϊ��ʱһ�Σ�id2Ϊѭ��ִ��*/
osTimerId Timer2;

/***********************************************************
 *        4������Timer�ĺ�����ʹ��ʱ�ɸ�����Ҫ*
 *                �ھ��幦�ܺ����н��д���                  *
 ************************************************************/                              
int TimerCreate_example(void)
{	
	u32 Timer1Delay = 5000;                           /*Timer1��ʱʱ��Ϊ5��   */
	u32 Timer2Delay = 10000;                         /*Timer2��ʱʱ��Ϊ10��  */
	osStatus status;
	args1=1;
	Timer1 = osTimerCreate(osTimer(Timer1),osTimerOnce,&args1);
	if(Timer1 )
	{
		status= osTimerStart(Timer1,Timer1Delay);                        
		if(status!=osOK)
		{
			printk("Timer1 start fail,status = 0x%x\n",status);
		}
	}
	else
	{
		printk("Timer1 create fail,status = 0x%x\n",Timer1);
		return -1;
	}
	args2=2;
	Timer2 = osTimerCreate(osTimer(Timer2),osTimerPeriodic,&args2);
	if(Timer2)
	{
		
		status= osTimerStart(Timer2,Timer2Delay);                       
		if(status!=osOK)
		{
			printk("Timer2 start fail,status = 0x%x\n",status);
		}
	}
	else
	{
		printk("Timer2 create fail,status = 0x%x\n",Timer2);
		return -1;
	}
	test_sem=osSemaphoreCreate(osSemaphore(test_sem),1);/*�����ź��������ƶ�ʱ��2ִ�д���*/
	osSemaphoreWait(test_sem, osWaitForever);
	osSemaphoreWait(test_sem, osWaitForever);
	status = osTimerStop(Timer2);                                          /*ֹͣ��ʱ��,��û��ɾ���������Լ���start*/
	if(status!=osOK)
	{
		printk("Timer2 stop fail\n");
	}
	/*�����ֹͣ��ɾ��һ��timer�����Ե���
	   status = osTimerDelete(timerId)
	   if(status!=osOK) {..........}*/
	printk("countNum1=%d, countNum=%d\n",countNum1,countNum);
	status = osTimerDelete(Timer1);
	if(status!=osOK)
	{
		printk("Timer1 delete fail,status = 0x%x\n",status);
	}
	status = osTimerDelete(Timer2);
	if(status!=osOK)
	{
		printk("Timer2 delete fail,status = 0x%x\n",status);
	}
	return 0;
}
