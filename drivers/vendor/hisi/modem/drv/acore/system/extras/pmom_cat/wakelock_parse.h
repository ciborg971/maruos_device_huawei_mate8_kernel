

#ifndef  __WAKELOCK_PARSE_H__
#define  __WAKELOCK_PARSE_H__

#ifdef __cplusplus
    extern "C" {
#endif
#include <linux/types.h>

enum lock_enum{
	WAKE_UNLOCK,
	WAKE_LOCK,
};

struct wakelock_om_s{
	u32 stamp;
	u32 lock_id;
	u32 lock_type;
	u32 lock_state;
	u32 cur_task_id;
};
typedef enum tagPWC_CLIENT_ID_E
{
    PWRCTRL_SLEEP_BEGIN=0X100,
    PWRCTRL_SLEEP_TLPS = PWRCTRL_SLEEP_BEGIN,   /*MSP--fuxin*/
    PWRCTRL_SLEEP_PS_G0,        /*GU--ganlan*/
    PWRCTRL_SLEEP_PS_W0,       /*GU--ganlan*/
    PWRCTRL_SLEEP_PS_G1,        /*GU--ganlan*/
    PWRCTRL_SLEEP_PS_W1,       /*GU--ganlan*/
    PWRCTRL_SLEEP_FTM,           /*GU--zhangyizhan*/
    PWRCTRL_SLEEP_FTM_1,       /*GU--zhangyizhan*/
    PWRCTRL_SLEEP_NAS,           /*GU--zhangyizhan*/
    PWRCTRL_SLEEP_NAS_1,       /*GU--zhangyizhan*/
    PWRCTRL_SLEEP_OAM,          /* LTE --yangzhi */
    PWRCTRL_SLEEP_SCI0,            /* LTE --yangzhi */
    PWRCTRL_SLEEP_SCI1,            /* LTE --yangzhi */
    PWRCTRL_SLEEP_DMA,             /* GU --jinguojun*/
    PWRCTRL_SLEEP_MEM,              /*drv,flash or emmc*/
    PWRCTRL_SLEEP_DSFLOW,          /* NAS --zhangyizhan */
    PWRCTRL_SLEEP_TEST,            /* PM  ---shangmianyou */
    PWRCTRL_SLEEP_UART0,        /*UART0 -zhangliangdong */
    PWRCTRL_SLEEP_TDS,         /*TRRC&TL2----leixiantiao*/

    PWRCTRL_SLEEP_CDMAUART,         /*drv cdma uart ����*/
    PWRCTRL_SLEEP_USIM,             /*oam*/
    PWRCTRL_SLEEP_DSPPOWERON,       /*v8r1 ccore �ṩ��GUTL DSP��Ϊc���ϵ��ʼ��ͶƱ��*/
    PWRCTRL_SLEEP_RESET,            /* RESET  ---nieluhua */
    PWRCTRL_SLEEP_PS_G2,        /*GU--ganlan*/
    PWRCTRL_SLEEP_FTM_2,       /*GU--zhangyizhan*/
    PWRCTRL_SLEEP_NAS_2,       /*GU--zhangyizhan*/
    /*���²��ֵ�ID�Ѿ���ʹ���ˣ����ڻ�ɾ��*/
    PWRCTRL_SLEEP_RNIC,
    PWRCTRL_TEST_DEEPSLEEP  = 0x11f,
    LOCK_ID_BOTTOM =0x120
}PWC_CLIENT_ID_E;

int wakelock_msg_parse(char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr);

#ifdef __cplusplus
}
#endif

#endif
