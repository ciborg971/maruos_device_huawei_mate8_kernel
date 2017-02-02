
#include <stdio.h>
#include "pmom_cat.h"
#include "ipc_clk.h"


/* ����stat  ��д�ַ������� ��statΪ0��bit���ַ�����������Ϊ"" */
static int reset_str_array(char *str_array[], unsigned int stat)
{
    unsigned int i = 0;

	for (i = 0; i < 32; i++)
	{
	    if (0 == (stat & (1 << i)))
    	{
    	    str_array[i] = "";
    	}
	}

    return 0;
}

/* A�˽��յ��ж� */
char *g_aipc_int[32] = {
    "IPC_ACPU_INT_SRC_CCPU_MSG"          , /* 0  */
	"IPC_ACPU_INT_SRC_HIFI_MSG"	         , /* 1  */
	"IPC_ACPU_INT_SRC_MCU_MSG"	         , /* 2  */
	"IPC_ACPU_INT_SRC_CCPU_NVIM"         , /* 3  */
	"IPC_INT_DICC_USRDATA" 		         , /* 4  */
	"IPC_INT_DICC_RELDATA"		         , /* 5  */
	"IPC_ACPU_INT_SRC_CCPU_ICC"			 , /* 6  */
	"IPC_ACPU_INT_SRC_ICC_PRIVATE"       , /* 7  */
	"IPC_ACPU_SRC_CCPU_DUMP"		     , /* 8  */
	"IPC_ACPU_INT_SRC_MCPU"		         , /* 9  */
	"IPC_ACPU_INT_SRC_MCPU_WDT"	         , /* 10 */
	"IPC_ACPU_INT_MCU_SRC_DUMP"	         , /* 11 */
	"IPC_ACPU_INT_SRC_CCPU_RESET_IDLE"   , /* 12 */
	"IPC_ACPU_INT_SRC_CCPU_RESET_SUCC"   , /* 13 */
	"IPC_ACPU_INT_SRC_CCPU_LOG"	         , /* 14 */
	"IPC_ACPU_INT_SRC_MCU_FOR_TEST"      , /* 15 */
	"IPC_ACPU_INT_SRC_CCPU_TEST_ENABLE"  , /* 16 */
	"IPC_ACPU_INT_SRC_MCPU_USB_PME"      , /* 17 */
	""                                   , /* 18 */
	""                                   , /* 19 */
	""                                   , /* 20 */
	""                                   , /* 21 */
	""                                   , /* 22 */
	""                                   , /* 23 */
	""                                   , /* 24 */
	""                                   , /* 25 */
	""                                   , /* 26 */
	""                                   , /* 27 */
	""                                   , /* 28 */
	""                                   , /* 29 */
	""                                   , /* 30 */
	""                                     /* 31 */
};

/* C�˽��յ��ж� */
char *g_cipc_int[32] = {
    "IPC_CCPU_INT_SRC_HIFI_MSG"             ,  /* 0  */
    "IPC_CCPU_INT_SRC_MCU_MSG"              ,  /* 1  */
    "IPC_INT_DSP_HALT"                      ,  /* 2  */
    "IPC_INT_DSP_RESUME"                    ,  /* 3  */
    "IPC_INT_DICC_USRDATA"                  ,  /* 4  �����ϲ㹲���룬�˴���������A���жϺ�����һ��*/
    "IPC_INT_DICC_RELDATA"                  ,  /* 5  �����ϲ㹲���룬�˴���������A���жϺ�����һ��*/                                                         
    "IPC_INT_WAKE_GU"                       ,  /* 6  */
    "IPC_INT_SLEEP_GU"                      ,  /* 7  */
    "IPC_INT_WAKE_GSM"                      ,  /* 8  */
    "IPC_INT_WAKE_WCDMA"                    ,  /* 9  */
    "IPC_INT_DSP_PS_PUB_MBX"                ,  /* 10 */
    "IPC_INT_DSP_PS_MAC_MBX"                ,  /* 11 */
    "IPC_INT_DSP_MBX_RSD"                   ,  /* 12 */
    "IPC_CCPU_INT_SRC_DSP_MNTN"             ,  /* 13 */
    "IPC_CCPU_INT_SRC_DSP_RCM_PUB_MBX"      ,  /* 14 */
    "IPC_CCPU_INT_SRC_ACPU_ICC"             ,  /* 15 */
    "IPC_CCPU_INT_SDR_CCPU_BBP_MASTER_ERROR",  /* 16 */         
    "IPC_CCPU_INT_SRC_ACPU_RESET"           ,  /* 17 */
    "IPC_CCPU_SRC_ACPU_DUMP"                ,  /* 18 */
    "IPC_CCPU_INT_SRC_ICC_PRIVATE"          ,  /* 19 */
    "IPC_CCPU_INT_SRC_MCPU"                 ,  /* 20 */
    "IPC_CCPU_INT_SRC_MCPU_WDT"             ,  /* 21 */
	""                                      ,  /* 22 */
	""                                      ,  /* 23 */
	""                                      ,  /* 24 */
	""                                      ,  /* 25 */
	""                                      ,  /* 26 */
	""                                      ,  /* 27 */
	""                                      ,  /* 28 */
	""                                      ,  /* 29 */
	""                                      ,  /* 30 */
	""                                         /* 31 */	
};

int ipc_msg_parse(enum pm_log_core_no core_no, char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr)
{
	int data_len = 0;
	unsigned int ipc_int_stat = ((unsigned int*)in_buf)[0];
	char **ptr_str_tmp = NULL;
	int i = 0;
	char* ptr_str[32] = {NULL};

	/* step1: ��Ϣ���ͼ�� */
	if(len != sizeof(unsigned int))
	{
		return PMOM_ERR;
	}

	switch (core_no)
	{
	    case PM_LOG_ACORE:
			for (i = 0; i < 32; i++)
			{
			     ptr_str[i] = g_aipc_int[i];
			}
			(void)reset_str_array(ptr_str, ipc_int_stat);
			ptr_str_tmp = &ptr_str[0];
			break;
		case PM_LOG_CCORE:
			for (i = 0; i < 32; i++)
			{
			     ptr_str[i] = g_cipc_int[i];
			}
			(void)reset_str_array(ptr_str, ipc_int_stat);
			ptr_str_tmp = &ptr_str[0];
			break;
		default:
			return PMOM_ERR;
	}

	/* step2: ��ʽ����Ϣ��out_buf */                                         
	data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, "int stat:[Bit31:0][0x%08x]", ipc_int_stat);
	*out_ptr = *out_ptr + data_len;
	for (i = 31; i >=0 ; i--)
	{
	    if ('\0' != ptr_str_tmp[i][0])
    	{
			data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, "%s ", ptr_str_tmp[i]);
			*out_ptr = *out_ptr + data_len;
    	}
	}
	/* ��ӡ�س� */
	data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, "\n");
	*out_ptr = *out_ptr + data_len;

	return PMOM_OK;
}



int clk_msg_parse(enum pm_log_core_no core_no, char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr)
{
	int data_len = 0;
	struct clk_op_entry *clk_log = (struct clk_op_entry *)in_buf;
	char *clk_op_type_str = NULL;
	char *enable_cnt_before_or_after = NULL;
	

	/* step1: ��Ϣ���ͼ�� */
	if(len != sizeof(struct clk_op_entry))
	{
		return PMOM_ERR;
	}


	/* step2: ��ʽ����Ϣ��out_buf: �Իس����� */
	switch (clk_log->op_type)
	{
	    case CLK_OP_TYPE_ENAB:
			clk_op_type_str = "enable";
			break;
		case CLK_OP_TYPE_DISA:
			clk_op_type_str = "disable";
			break;
		case CLK_OP_TYPE_SETR:
			clk_op_type_str = "set_rate";
			break;
		case CLK_OP_TYPE_SETP:
			clk_op_type_str = "set_parent";
			break;
		case CLK_OP_TYPE_ENAU:
			clk_op_type_str = "en_auto_gate";
			break;
		case CLK_OP_TYPE_DIAU:
			clk_op_type_str = "dis_auto_gate";
			break;

		default:
			return PMOM_ERR;
	}

    clk_log->clk_name[LOG_CLK_NAME_LEN - 1] = 0x00;  /* ��ֹ�����������ֺ�������� */
	if (PM_LOG_CCORE == core_no) /* ccore */
	{
		data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, 
				"task:0x%x,%s,%s,enable_cnt before op %d\n", clk_log->task_id,  
				                                             clk_op_type_str, &clk_log->clk_name[0],
				                                             clk_log->enable_count_before_op); 
	}
	else  /* acore����������ops���¼��log�����Բ��ٽ������ü��� */
	{
		data_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ, 
				"task:0x%x,%s,%s\n", clk_log->task_id, clk_op_type_str, &clk_log->clk_name[0]); 
	}
	*out_ptr = *out_ptr + data_len;

	return PMOM_OK;
}

