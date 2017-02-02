
#include <stdio.h>
#include "pmom_cat.h"
#include "dpm_m3pm.h"

int dpm_msg_parse(unsigned int typeid, char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr)
{
	int data_len = 0;
	struct dpm_fail_pm_om_log *log_msg = (struct dpm_fail_pm_om_log *)in_buf;

	/* step1: ��Ϣ���ͼ�� */
	if(len != sizeof(*log_msg))
	{
		return PMOM_ERR;
	}

	/* step2: ��ʽ����Ϣ��out_buf: �Իس����� */
	if (0 == typeid)
	{
		data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, 
				"<mdm dpm failed> ops_addr:0x%x, ops_in_stamp:0x%x, ops_out_stamp:0x%x,fail cnt:0x%x \n", log_msg->ops_addr, log_msg->before_stamp, 
				log_msg->after_stamp, log_msg->fail_cnt); 
        
		*out_ptr = *out_ptr + data_len;
	}
	else
	{
		return PMOM_ERR;
	}

	return PMOM_OK;
}


int m3pm_msg_parse(unsigned int typeid, char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr)
{
	int data_len = 0;
	u32 *log_msg = (u32 *)in_buf;


	/* step2: ��ʽ����Ϣ��out_buf: �Իس����� */
	switch (typeid)
	{
		case m3_mdm_pm_log_a9:
            if( M3PM_LOG_MDM_A9_SIZE != len)
                return PMOM_ERR;
            data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, 
                "a9_power_down(0x%08x - 0x%08x), a9_power_up(0x%08x - 0x%08x, irq_no:%d) \n",\
                *(u32*)(log_msg), *(u32*)(log_msg+1),*(u32*)(log_msg+2), *(u32*)(log_msg+3), *(u32*)(log_msg+4));
    		break;
		case m3_mdm_pm_log_a9_sr:
            if( M3PM_LOG_MDM_A9_SR_SIZE != len)
                return PMOM_ERR;
            data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, 
                "a9_power_down(0x%08x - 0x%08x), a9_power_up(0x%08x - 0x%08x, irq_no:%d) \t modem_suspend,begin:0x%08x, dpm_sus_end:0x%08x, sram_sus_end:0x%08x, cpufreq_sus_end:0x%08x,\t modem_resume,begin:0x%08x, end:0x%08x, modem_resume_ok begin:0x%08x, cpufreq_resume_end:0x%08x , dpm_resume_end:0x%08x  \n", \
                 *(u32*)(log_msg),*(u32*)(log_msg+1),*(u32*)(log_msg+2),*(u32*)(log_msg+0x3),*(u32*)(log_msg+4),     *(u32*)(log_msg+5),*(u32*)(log_msg+6),*(u32*)(log_msg+7),*(u32*)(log_msg+8),   *(u32*)(log_msg+9),*(u32*)(log_msg+10),*(u32*)(log_msg+11),*(u32*)(log_msg+12),*(u32*)(log_msg+12));
			break;

		case M3PM_LOG_MODEM_DPM_OFFSET:
            if(M3PM_LOG_MODEM_DPM_SIZE!= len)
                return PMOM_ERR;
            data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, 
                "m3_modem_dpm_fail, slice:0x%x, suspend_fail_cnt: TEMP-0x%08x, IPF-0x%08x \n", \
                                *(u32*)(log_msg), *(u32*)(log_msg+1), *(u32*)(log_msg+2) );
			break;
		default:
			return PMOM_ERR;
	}
        
		*out_ptr = *out_ptr + data_len;

	return PMOM_OK;
}


