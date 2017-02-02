
#include <stdio.h>
#include "pmom_cat.h"
#include "wakelock_parse.h"
char *g_wakerlock_obj[] = {
	"unlock",
	"lock",
};
char *wakelock_name[]={
    "PWRCTRL_SLEEP_TLPS" ,   /*MSP--fuxin*/
    "PWRCTRL_SLEEP_PS_G0",        /*GU--ganlan*/
    "PWRCTRL_SLEEP_PS_W0",       /*GU--ganlan*/
    "PWRCTRL_SLEEP_PS_G1",        /*GU--ganlan*/
    "PWRCTRL_SLEEP_PS_W1",       /*GU--ganlan*/
    "PWRCTRL_SLEEP_FTM",           /*GU--zhangyizhan*/
    "PWRCTRL_SLEEP_FTM_1",       /*GU--zhangyizhan*/
    "PWRCTRL_SLEEP_NAS",           /*GU--zhangyizhan*/
    "PWRCTRL_SLEEP_NAS_1",       /*GU--zhangyizhan*/
    "PWRCTRL_SLEEP_OAM",          /* LTE --yangzhi */
    "PWRCTRL_SLEEP_SCI0",            /* LTE --yangzhi */
    "PWRCTRL_SLEEP_SCI1",            /* LTE --yangzhi */
    "PWRCTRL_SLEEP_DMA",             /* GU --jinguojun*/
    "PWRCTRL_SLEEP_MEM",              /*drv,flash or emmc*/
    "PWRCTRL_SLEEP_DSFLOW",          /* NAS --zhangyizhan */
    "PWRCTRL_SLEEP_TEST",            /* PM  ---shangmianyou */
    "PWRCTRL_SLEEP_UART0",        /*UART0 -zhangliangdong */
    "PWRCTRL_SLEEP_TDS",         /*TRRC&TL2----leixiantiao*/
    "PWRCTRL_SLEEP_CDMAUART",         /*drv cdma uart ����*/
    "PWRCTRL_SLEEP_USIM",             /*oam*/
    "PWRCTRL_SLEEP_DSPPOWERON",       /*v8r1 ccore �ṩ��GUTL DSP��Ϊc���ϵ��ʼ��ͶƱ��*/
    "PWRCTRL_SLEEP_RESET",            /*RESET -nieluhua */
    "PWRCTRL_SLEEP_PS_G2",        /*GU--ganlan*/
    "PWRCTRL_SLEEP_FTM_2",       /*GU--zhangyizhan*/
    "PWRCTRL_SLEEP_NAS_2",       /*GU--zhangyizhan*/
    "PWRCTRL_SLEEP_RNIC",

};
int wakelock_msg_parse(char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr)
{
	int data_len = 0;
	struct wakelock_om_s *log_msg = (struct wakelock_om_s *)in_buf;

	/* step1: ��Ϣ���ͼ�� */
	if(len != sizeof(*log_msg))
	{
		return PMOM_ERR;
	}

	/* step2: ��ʽ����Ϣ��out_buf: �Իس����� */
	
	data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, 
			"task_id:0x%x, %s(lock_id:0x%x), %s, lock_state:0x%x,\n", 
			log_msg->cur_task_id,wakelock_name[log_msg->lock_id],log_msg->lock_id,
			g_wakerlock_obj[(unsigned int)log_msg->lock_type], log_msg->lock_state); 
	*out_ptr = *out_ptr + data_len;
	return PMOM_OK;
}

