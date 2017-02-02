

#ifndef  __IPC_CLK_H__
#define  __IPC_CLK_H__

#ifdef __cplusplus
    extern "C" {
#endif


enum clk_op_type{
    CLK_OP_TYPE_ENAB = 0x454E4142,  /* clk_enable              */
    CLK_OP_TYPE_DISA = 0x44495341,  /* clk_disable             */
    CLK_OP_TYPE_SETR = 0x53455452,  /* clk_set_rate            */
    CLK_OP_TYPE_SETP = 0x53455450,  /* clk_set_parent          */
    CLK_OP_TYPE_ENAU = 0x454E4155,  /* clk_enable_auto_gating  */
    CLK_OP_TYPE_DIAU = 0x44494155   /* clk_disable_auto_gating */
};

enum pm_log_core_no{
    PM_LOG_ACORE,  
	PM_LOG_CCORE
};


#define LOG_CLK_NAME_LEN   8  /* ��¼ʱ�����ֵ�ǰ8���ַ� */

struct clk_op_entry{
    unsigned int      task_id;                         /* ����������ID */
	char              clk_name[LOG_CLK_NAME_LEN]; /* ��������ʱ������ */
    unsigned int      op_type;                         /* �������� */
	unsigned int      enable_count_before_op;          /* ����ǰ��Ӧ�ü��� */
};




int ipc_msg_parse(enum pm_log_core_no core_no, char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr);
int clk_msg_parse(enum pm_log_core_no core_no, char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr);

#ifdef __cplusplus
}
#endif

#endif   /* __IPC_CLK_H__ */

