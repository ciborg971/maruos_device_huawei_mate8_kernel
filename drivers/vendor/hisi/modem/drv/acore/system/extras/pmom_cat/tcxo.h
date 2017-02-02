

#ifndef  __TCXO_H__
#define  __TCXO_H__

#ifdef __cplusplus
    extern "C" {
#endif

#include <linux/types.h>

struct tcxo_pm_log
{
	unsigned int sw;
	unsigned int mode_id;
};

enum TCXO_PM_OM
{
	TCXO_ON,
	TCXO_OFF,	
	TCXO_TIMER_START,
	TCXO_STATUS,
    TCXO_TIMER_HANDER,
	TCXO_FIRST_ON,
	TCXO_PM_STATUS,
};

typedef enum tagPWC_COMM_MODE_E
{
    PWC_COMM_MODE_GSM,
    PWC_COMM_MODE_WCDMA,
    PWC_COMM_MODE_LTE,
    PWC_COMM_MODE_TDS,
    PWC_COMM_MODE_LCIPHER,
    PWC_COMM_MODE_BUTT
}PWC_COMM_MODE_E;
int tcxo_msg_parse(char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr);

#ifdef __cplusplus
}
#endif

#endif   /* __TCXO_H__ */