

/*lint --e{762} */

#ifndef CLK_BALONG_CORE_H
#define CLK_BALONG_CORE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include "bsp_clk.h"
#include <of.h>

#include <osl_list.h>
#include <osl_spinlock.h>
#include <osl_sem.h>
#include <osl_malloc.h>
#include <osl_thread.h>
#include "securec.h"

#define  clk_printf(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_CLK, "[clk]: <%s> "fmt"", __FUNCTION__, ##__VA_ARGS__))

//#define  CLK_EN_INFO_PRINT
#ifdef   CLK_EN_INFO_PRINT
#define  clk_printf_info(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_CLK, "[clk]: <%s> "fmt"", __FUNCTION__, ##__VA_ARGS__))
#else
#define  clk_printf_info(fmt, ...)    
#endif
typedef void (*drv_of_clk_init_cb_t)(struct device_node *);

enum clk_op_type{
    CLK_OP_TYPE_ENAB = 0x454E4142,  /* clk_enable              */
    CLK_OP_TYPE_DISA = 0x44495341,  /* clk_disable             */
    CLK_OP_TYPE_SETR = 0x53455452,  /* clk_set_rate            */
    CLK_OP_TYPE_SETP = 0x53455450,  /* clk_set_parent          */
    CLK_OP_TYPE_ENAU = 0x454E4155,  /* clk_enable_auto_gating  */
    CLK_OP_TYPE_DIAU = 0x44494155   /* clk_disable_auto_gating */
};

#define LOG_CLK_NAME_LEN   8  /* ��¼ʱ�����ֵ�ǰ8���ַ� */

struct clk_op_entry{
    OSL_TASK_ID       task_id;                         /* ����������ID */
	char              clk_name[LOG_CLK_NAME_LEN];      /* ��������ʱ������ */
	unsigned int      op_type;                         /* �������� */
	unsigned int      enable_count_before_op;          /* ����ǰ��Ӧ�ü��� */
};

#define NOTIFY_STOP_MASK	0x8000		

static inline char *clk_alloc_copy(const char *src_str)
{
	unsigned int len;
	char         *dst_str = NULL;

	if (!src_str)
	{
		return NULL;
	}

	len = strlen(src_str) + 1;
	dst_str = osl_malloc(len);
	if (dst_str)
	{
		memcpy_s(dst_str, len, src_str, len);
	}
	
	return dst_str;
}





#ifndef BIT
#define BIT(nr)			(1UL << (nr))
#endif



/* ʱ��flag */
#define CLK_SET_RATE_GATE	     BIT(0) /* �ı�ʱ��Ƶ��ʱӦ�ñ��ض� */
#define CLK_SET_PARENT_GATE	     BIT(1) /* ���ø�ʱ��ʱӦ�ñ��ض� */
#define CLK_SET_RATE_PARENT	     BIT(2) /* Ƶ�ʸı�ʱ����ʱ������һ�� */
#define CLK_IGNORE_UNUSED	     BIT(3) /* ��ʹ��Ҳ���ض� */
#define CLK_IS_ROOT		         BIT(4) /* ��ʱ�ӣ�û�и�ʱ�� */
#define CLK_IS_BASIC		     BIT(5) /* ����ʱ�ӣ�û��to_clk_xxx()���� */
#define CLK_GET_RATE_NOCACHE	 BIT(6) /* ��ʹ�û����ʱ��Ƶ�� */



struct clk_div_table {
	unsigned int	val_to_reg; /* Ӧ��д���Ĵ����е�ֵ��N+1��ƵʱΪdiv_val-1 */  
	unsigned int	div_val;    /* ��Ƶֵ */
};



#define CLK_MUX_INDEX_ONE		BIT(0) /* ��1����������0,1,2,3... */
#define CLK_MUX_INDEX_BIT		BIT(1) /* ��2��������������2^0,2^1,2^2... */
#define CLK_MUX_HIWORD_MASK		BIT(2)


/***********************************************************************
*����:ע��ʱ��
*����:�����ַ�����Ӳ��ָ��ʱ��
*����:ʱ�ӽṹ��ָ��
************************************************************************/
struct clk *drv_clk_register(const char * dev, struct clk_hw *hw);


/***********************************************************************
*����:��ȡʱ������
*����:ʱ�ӽṹ��ָ��
*����:ʱ������
************************************************************************/
const char *__drv_clk_get_name(struct clk *clk);

/***********************************************************************
*����:��ȡ��ʱ�Ӹ���
*����:ʱ�ӽṹ��ָ��
*����:��ʱ�Ӹ���
************************************************************************/
u8 __drv_clk_get_num_parents(struct clk *clk);

/***********************************************************************
*����:��ȡ��ʱ��
*����:ʱ�ӽṹ��ָ��
*����:��ʱ�ӽṹ��ָ��
************************************************************************/
struct clk *__drv_clk_get_parent(struct clk *clk);

/***********************************************************************
*����:��ȡʱ�ӱ�־
*����:ʱ�ӽṹ��ָ��
*����:ʱ�ӱ�־
************************************************************************/
unsigned long __drv_clk_get_flags(struct clk *clk);


/***********************************************************************
*����:roundʱ��Ƶ��
*����:ʱ�ӽṹ��ָ�룬ʱ��Ƶ��
*����:round���ʱ��Ƶ��
************************************************************************/
unsigned long __drv_clk_round_rate(struct clk *clk, unsigned long rate);

/***********************************************************************
*����:ͨ��of�ӿڻ�ȡ��ʱ������
*����:�豸�ڵ�ָ�룬��ʱ������
*����:��ʱ���ַ���
************************************************************************/
const char *drv_of_clk_get_parent_name(struct device_node *np, int index);

/***********************************************************************
*����:ͨ��of�ӿڳ�ʼ��ʱ��
*����:of_device_id�ṹ��ָ��
*����:��
************************************************************************/
void drv_of_clk_init(const struct of_device_id *matches);

/***********************************************************************
*����:��ʱ����ӵ�������
*����:ʱ�Ӳ��ҽṹ��ָ��
*����:��
************************************************************************/
void drv_clkdev_add(struct clk_lookup *cl);

/***********************************************************************
*����:��ʱ��
*����:ʱ�ӽṹ��ָ��
*����:0���ɹ�������ֵ��ʧ��
************************************************************************/
int __drv_clk_enable(struct clk *ptr_clk);

/***********************************************************************
*����:�ر�ʱ��
*����:ʱ�ӽṹ��ָ��
*����:��
************************************************************************/
void __drv_clk_disable(struct clk *ptr_clk);



#ifdef __cplusplus
}
#endif


#endif
