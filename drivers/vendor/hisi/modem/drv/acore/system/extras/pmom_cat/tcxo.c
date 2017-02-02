


#include <stdio.h>
#include "pmom_cat.h"
#include "tcxo.h"

char *g_tcxo_act[] = {
	"start open tcxo",
	"close tcxo",
	"start timer to wait tcxo stable",
};

char *g_mode_id[] = {
	"GSM",
	"WCDMA",
	"LTE",
	"TDS",
};

int tcxo_msg_parse(char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr)
{
    int data_len = 0;
	struct tcxo_pm_log *log_msg = (struct tcxo_pm_log *)in_buf;

    /* step1: ��Ϣ���ͼ�� */
	if(len != sizeof(*log_msg))
	{
		return PMOM_ERR;
	}

	if (log_msg->sw > TCXO_ON && log_msg->sw <= TCXO_TIMER_START)
	{
		/* step2: ��ʽ����Ϣ��out_buf: �Իس����� */
		data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ,
				"%s, %s\n", g_mode_id[log_msg->mode_id], g_tcxo_act[log_msg->sw]);
		*out_ptr = *out_ptr + data_len;
	}
	else if (log_msg->sw == TCXO_STATUS)
	{
		data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ,
				"check tcxo%d'is stable\n", log_msg->mode_id);
		*out_ptr = *out_ptr + data_len;
	}
	else if (log_msg->sw == TCXO_TIMER_HANDER)
	{
		data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ,
				"timer handler finish: tcxo%d is opend and stable\n", log_msg->mode_id);
		*out_ptr = *out_ptr + data_len;
	}
	else if (log_msg->sw == TCXO_FIRST_ON)
	{
		data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ,
				"M3 opened tcxo, CP wait %dslice(>0 is error!)for stable\n", log_msg->mode_id);
		*out_ptr = *out_ptr + data_len;
	}
	else if (log_msg->sw == TCXO_PM_STATUS)
	{
		if(log_msg->mode_id&((unsigned int)0x1 << PWC_COMM_MODE_GSM))
		{
			data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ,"GSM, ");
			*out_ptr = *out_ptr + data_len;
		}
		if(log_msg->mode_id&((unsigned int)0x1 << PWC_COMM_MODE_WCDMA))
		{
			data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ,"WCDMA, ");
			*out_ptr = *out_ptr + data_len;
		}
		if(log_msg->mode_id&((unsigned int)0x1 << PWC_COMM_MODE_LTE))
		{
			data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, "LTE, ");
			*out_ptr = *out_ptr + data_len;
		}
		if(log_msg->mode_id&((unsigned int)0x1 << PWC_COMM_MODE_TDS))
		{
			data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, "TDS, ");
			*out_ptr = *out_ptr + data_len;
		}
		data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, "not close TCXO1,stop PM flow\n");
		*out_ptr = *out_ptr + data_len;
	}

	return PMOM_OK;
}
