
#ifndef __M3_PM_TEST_H__
#define __M3_PM_TEST_H__


#ifdef CONFIG_M3PM_TEST
extern u32 debug_can_sleep(void);
#else
static inline u32 debug_can_sleep(void){return 1;}
#endif


#endif


        
