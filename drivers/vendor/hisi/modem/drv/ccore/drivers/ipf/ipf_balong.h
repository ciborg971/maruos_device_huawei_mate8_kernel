
#ifndef _IPF_BALONG_H_
#define _IPF_BALONG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mdrv_ipf.h"

#define IPF_ULADQ_PLEN_TH                 404
#define IPF_CCORE_INIT_SUCCESS        0x10000 
#define IPF_ADQ_RESERVE_NUM                 3

/* IPF transfer time recorder start */
#define IPF_MAX_STAMP_ORDER             32
#define IPF_MAX_TIME_LIMIT              (19200000*10)
#define IPF_FLS_MASK                    (31)
#define IPF_PWC_DOWN                    (0)

#define IPF_REGS_SIZE					(HI_IPF_CH1_ADQ1_RPTR_OFFSET + 4)
#define IPF_CD_EN_BIT					(1<<14)
#define SECCTRL_BYPASS					(1<<4)
#define SECCTRL_VALID0					(0x01 | SECCTRL_BYPASS)
#define SECCTRL_VALID1				 	(0x02 | SECCTRL_BYPASS)
//tmp close func
#define SECCTRL_VALID2					(0x04 | SECCTRL_BYPASS)
#define SECCTRL_VALID2_3				(0x0c | SECCTRL_BYPASS)
#define MST_DEFAULT_ADDR 				 0x400

typedef struct ipf_ctx {
	void * regs;
    unsigned int irq;
	void*	bd_phy;
	void*	bd_virt;
	void*	cd_virt;
	void*	cd_phy;
	void*	rd_virt;
	void*	rd_phy;
	void*	ad_phy[IPF_AD_MAX];
	void*	ad_virt[IPF_AD_MAX];
	unsigned int ipf_version;
	struct ipf_debug* status;
	char* 	dump_reg;
	int 	dump_size;
	unsigned int addr_limit;
	IPF_LIMIT_ADDR_S *sh_limit_addr;
} ipf_ctx_t;

#define IPF_GET_MEMBLK_BUF(node) \
    (*((unsigned int*) (((unsigned int)(node) + memblk_offset.bufoffset))))

#define IPF_GET_MEMBLK_LEN(node) \
    (*((unsigned short*) (((unsigned int)(node) + memblk_offset.lenoffset))))

#define IPF_GET_NEXT_MEMBLK(node) \
    ((unsigned int*) (*((unsigned int*) (((unsigned int)(node) + memblk_offset.nextoffset)))))



#ifndef NULL
#define NULL            (void*)0
#endif

#ifndef OK
#define OK 0
#endif

#ifndef ERROR
#define ERROR  (-1)
#endif

struct dts_param_c {
    unsigned int addr;
    unsigned int size;
    unsigned int irqnum0;
    unsigned int irqnum1;
};

struct ipf_memblk_offset {
    unsigned int bufoffset;
    unsigned int lenoffset;
    unsigned int nextoffset;
};
typedef struct tagIPF_TIMESTAMP_INFO_S
{
    unsigned int diff_order_cnt[IPF_MAX_STAMP_ORDER];
    unsigned int cnt_sum;
    unsigned int diff_sum;
    unsigned int diff_max;
    unsigned int overflow;
}IPF_TIMESTAMP_INFO_S;


typedef struct tagIPF_PWRCTL_FILTER_INFO_S
{
	unsigned int u32Flag;
	IPF_CHANNEL_TYPE_E eChnType;
	unsigned int u32FilterNum;
	IPF_FILTER_CONFIG_S *pstFilterInfo;
}IPF_PWRCTL_FILTER_INFO_S;


typedef struct tagIPF_ID_S
{
    unsigned int u32PsID;
    unsigned int u32FilterID;
    struct tagIPF_ID_S* pstNext;
}IPF_ID_S;

typedef struct tagIPF_FILTER_INFO_S
{
    IPF_ID_S* pstUseList;
    unsigned int u32FilterNum;
}IPF_FILTER_INFO_S;

static __inline__ unsigned int ipf_readl(unsigned int addr)
{
    return readl(addr);
}
static __inline__ void ipf_writel(unsigned int val, unsigned int addr)
{
    writel(val, addr);
}

void bsp_ipf_help(void);
void BSP_IPF_BackupFilter(unsigned int u32FilterID);
irqreturn_t  IPF_IntHandler (int irq, void* dev);
int IPF_FilterList_Init(void);
void IPF_Int_Connect(void);
void IPF_DeleteAll(IPF_FILTER_CHAIN_TYPE_E eFilterChainhead);
void bsp_ipf_mem(void);
int bsp_ipf_info(IPF_CHANNEL_TYPE_E eChnType);
int bsp_ipf_dump_adinfo(IPF_CHANNEL_TYPE_E eChnType, unsigned int u32AdType);
int bsp_ipf_dump_rdinfo(IPF_CHANNEL_TYPE_E eChnType);
int ipf_register_adq_empty_ulcb(BSP_IPF_AdqEmptyUlCb pAdqEmptyUl);
int ipf_register_wakeup_ulcb(BSP_IPF_WakeupUlCb pFnWakeupUl);
int bsp_ipf_dump_bdinfo(IPF_CHANNEL_TYPE_E eChnType);
int ccpu_reset_ipf_and_wait_idle(void);

#ifdef __cplusplus
}
#endif

#endif /*s_IPC_BALONG_H_*/

