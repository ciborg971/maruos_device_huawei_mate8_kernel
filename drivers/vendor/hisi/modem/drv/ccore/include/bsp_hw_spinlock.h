
#ifndef __BSP_HW_SPINLOCK_H__
#define __BSP_HW_SPINLOCK_H__


#ifdef __cplusplus
extern "C" {
#endif

#include <osl_irq.h>


#define HW_SPINLOCK_WAIT_FOREVER    (-1)
#define HW_MEMREPAIR_LOCKID         (0x4)
#define HW_PMUCLK_LOCKID         (0x9)
#define HW_GPIO_LOCKID         (0x1)

/*****************************************************************************
* ����  : hwspin_trylock
* ����  : ���Ի�ȡһ��Ӳ����
* ����  : Ӳ����ID
* ���  : ��
* ����  : �ɹ�����0
* ע������: ��Ӳ����ֻ�ܱ�֤�˼以�⣬���ڵĻ�����Ҫ�����߱�֤
*****************************************************************************/
int hwspin_trylock(u32 id);

/*****************************************************************************
* ����  : hwspin_unlock
* ����  : ���Ի�ȡһ��Ӳ����
* ����  : Ӳ����ID
* ���  : ��
* ����  : �ɹ�����0
* ע������: ��
*****************************************************************************/
int hwspin_unlock(u32 id);

/*****************************************************************************
* ����  : hwspin_lock_timeout
* ����  : ���Ի�ȡһ��Ӳ����
* ����  : id        Ӳ����ID
          time_us   ��΢��Ϊ��λ����ʱʱ�䣬���õȴ���ʹ��HW_SPINLOCK_WAIT_FOREVER
* ���  : ��
* ����  : �ɹ�����0
* ע������: ��
*****************************************************************************/
int hwspin_lock_timeout(u32 id, int time_us);


void hwspinlock_init(void);

#ifdef __cplusplus
}
#endif

#endif

