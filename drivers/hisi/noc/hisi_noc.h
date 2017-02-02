#ifndef __HISI_NOC_H
#define __HISI_NOC_H

#include <soc_acpu_baseaddr_interface.h>

#define MODULE_NAME	"HISI_NOC"
#define MAX_NOC_NODE_NAME_LEN	20
#define GET_NODE_FROM_ARRAY(node, idx)                 \
	node = hi3xxx_nodes_array[idx];           \


/*used by k3*/
#define PCTRL_PH_BASE   SOC_ACPU_PCTRL_BASE_ADDR
#define SCTRL_PH_BASE   SOC_ACPU_SCTRL_BASE_ADDR
#define PMCTRL_PH_BASE  0xFFF31000/*SOC_ACPU_PMC_BASE_ADDR*/

#define HI3XXX_NOC_MAX_IRQ_NR     64
#define HI3XXX_NOC_PCTRL_IRQ_MASK 0xF04000000807ABFBULL
#define PCTRL_NOC_IRQ_STAT1   SOC_PCTRL_PERI_STAT0_ADDR(0)
#define PCTRL_NOC_IRQ_STAT3   SOC_PCTRL_PERI_STAT3_ADDR(0)
#define PCTRL_PERI_STAT2   SOC_PCTRL_PERI_STAT2_ADDR(0)
#define PCTRL_PERI_CTRL19   SOC_PCTRL_PERI_CTRL19_ADDR(0)
#define SCTRL_SCPERSTATUS6  SOC_SCTRL_SCPERSTATUS6_ADDR(0)

#define HI3XXX_MAX_NODES_NR   33
#define HISI_NOC_CLOCK_MAX		2

#define PMCTRL_PERI_INT_STAT0_OFFSET   SOC_PMCTRL_PERI_INT0_STAT_ADDR(0)
#define PMCTRL_PERI_INT_MASK_OFFSET   SOC_PMCTRL_PERI_INT0_MASK_ADDR(0)
#define PMCTRL_NOC_POWER_IDLEREQ    SOC_PMCTRL_NOC_POWER_IDLEREQ_ADDR(0)
#define PMCTRL_NOC_POWER_IDLEACK    SOC_PMCTRL_NOC_POWER_IDLEACK_ADDR(0)
#define PMCTRL_NOC_POWER_IDLE    SOC_PMCTRL_NOC_POWER_IDLE_ADDR(0)

#define HISI_NOC_HI3650 (1<<0)
#define HISI_NOC_HI6250 (1<<1)

#define HISI_NOC_HI3XXX (HISI_NOC_HI3650)
#define HISI_NOC_HI6XXX (HISI_NOC_HI6250)

#define NOC_PTYPE_UART 1
#define NOC_PTYPE_PSTORE 0

#define NOC_PLATFORM_ID		(g_config_hisi_noc_data->platform_id)
struct hisi_noc_data {
	unsigned int platform_id;
};


enum NOC_IRQ_TPYE {
	NOC_ERR_PROBE_IRQ,
	NOC_PACKET_PROBE_IRQ,
	NOC_TRANS_PROBE_IRQ,
};

struct noc_arr_info {
	const void *ptr;
	unsigned int	len;
};

struct hisi_noc_irqd {
	enum NOC_IRQ_TPYE type;
	struct noc_node *node;
};
struct hisi_noc_device {
	struct device		*dev;
	void __iomem		*sys_base;
	void __iomem        *media_base;
	unsigned int		hi6220_irq[4];
	void __iomem		*pctrl_base;
	void __iomem		*pmctrl_base;
	void __iomem		*sctrl_base;
	void __iomem		*pwrctrl_reg;
	void __iomem		*pcrgctrl_base;
	unsigned int		hi3xxx_irq;
	unsigned int		timeout_irq;
};

struct	packet_configration {
	unsigned int		statperiod;
	unsigned int		statalarmmax;

	unsigned int		packet_counters_0_src;
	unsigned int		packet_counters_1_src;
	unsigned int        packet_counters_2_src;
	unsigned int        packet_counters_3_src;

	unsigned int		packet_counters_0_alarmmode;
	unsigned int		packet_counters_1_alarmmode;
    unsigned int		packet_counters_2_alarmmode;
    unsigned int		packet_counters_3_alarmmode;

	unsigned int		packet_filterlut;
	unsigned int		packet_f0_routeidbase;
	unsigned int		packet_f0_routeidmask;
	unsigned int		packet_f0_addrbase;
	unsigned int		packet_f0_windowsize;
	unsigned int		packet_f0_securitymask;
	unsigned int		packet_f0_opcode;
	unsigned int		packet_f0_status;
	unsigned int		packet_f0_length;
	unsigned int		packet_f0_urgency;
	unsigned int		packet_f0_usermask;

	unsigned int		packet_f1_routeidbase;
	unsigned int		packet_f1_routeidmask;
	unsigned int		packet_f1_addrbase;
	unsigned int		packet_f1_windowsize;
	unsigned int		packet_f1_securitymask;
	unsigned int		packet_f1_opcode;
	unsigned int		packet_f1_status;
	unsigned int		packet_f1_length;
	unsigned int		packet_f1_urgency;
	unsigned int		packet_f1_usermask;

};
struct transcation_configration {
	unsigned int		statperiod;
	unsigned int		statalarmmax;

	unsigned int		trans_f_mode;
	unsigned int		trans_f_addrbase_low;
	unsigned int		trans_f_addrwindowsize;
	unsigned int		trans_f_opcode;
	unsigned int		trans_f_usermask;
	unsigned int		trans_f_securitymask;

	unsigned int		trans_p_mode;
	unsigned int		trans_p_thresholds_0_0;
	unsigned int		trans_p_thresholds_0_1;
	unsigned int		trans_p_thresholds_0_2;
	unsigned int		trans_p_thresholds_0_3;

	unsigned int		trans_m_counters_0_src;
	unsigned int		trans_m_counters_1_src;
	unsigned int		trans_m_counters_2_src;
	unsigned int		trans_m_counters_3_src;

	unsigned int		trans_m_counters_0_alarmmode;
	unsigned int		trans_m_counters_1_alarmmode;
	unsigned int		trans_m_counters_2_alarmmode;
	unsigned int		trans_m_counters_3_alarmmode;
};

// Clock information for Noc
struct noc_clk {
	unsigned int		offset; // offset of clock status register in PERI_CRG
	unsigned int 		mask_bit; // bit to indicate clock status
};

struct noc_node {
	char			*name;
	void __iomem		*base;
	unsigned int		bus_id;
	unsigned int		interrupt_num;
	unsigned int		pwrack_bit;
	unsigned int		eprobe_offset;
	bool			eprobe_autoenable;
	int			eprobe_hwirq;
   	int                 hwirq_type;
	struct	transcation_configration	tran_cfg;
	struct	packet_configration		packet_cfg;
	struct noc_clk	crg_clk[HISI_NOC_CLOCK_MAX]; // Currently 2 clock sources for each noc node
};

void __iomem * get_errprobe_base(const char *name);
struct noc_node * get_probe_node(const char *name);

extern const struct hisi_noc_data *g_config_hisi_noc_data;

//add for Hi_3xxx
unsigned int noc_find_addr_from_routeid(unsigned int idx, int initflow, int targetflow, int targetsubrange);
int noc_set_routeid_info(unsigned int platform_id);
int  get_bus_id_by_base(const void __iomem	*base);
int is_noc_node_available(struct noc_node *node);
struct dentry *noc_get_debugfs_dentry(void);
struct platform_device *noc_get_pt_pdev(void);
unsigned int is_noc_init(void);
uint *noc_pkt_enable(void);
uint *noc_trans_enable(void);
/*
Function: noc_get_irq_status
Description: noc part, get irq status
input: void __iomem * pctrl_base: pctrl virtual base address
output: none
return: irq status
*/
unsigned long noc_get_irq_status(void __iomem * pctrl_base);
void enable_noc_transcation_probe(struct device *dev);
void disable_noc_transcation_probe(struct device *dev);
void enable_noc_packet_probe(struct device *dev);
void disable_noc_packet_probe(struct device *dev);
void noc_record_log_pstorememory(void __iomem *base, int ptype);
typedef struct datapath_routid_addr {
    int init_flow;
    int targ_flow;
    int targ_subrange;
    unsigned int init_localaddr;
} ROUTE_ID_ADDR_STRU;

#endif
