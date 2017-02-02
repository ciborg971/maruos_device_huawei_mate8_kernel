
#ifndef _AMON_BALONG_H_
#define _AMON_BALONG_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "bsp_memmap.h"
#include "osl_types.h"
#include "drv_amon.h"
#include "hi_amon.h"
#include "bsp_shared_ddr.h"

/**************************************************************************
                                 �Ĵ�������
**************************************************************************/
/* AXI monitor���������÷���: CPUFAST, SOC */
#define AXI_MON_CPUFAST_BASE_ADDR       (g_amon_base_addr[AXI_FAST_ADDR_ENUM]) /* AXI monitor CPUFAST����ַ */
#define AXI_MON_SOC_BASE_ADDR           (g_amon_base_addr[AXI_SOC_ADDR_ENUM])     /* AXI monitor SOC����ַ */

/* AXI monitor�Ĵ���ƫ�Ƶ�ַ���� begin */
#define AXI_MON_CNT_RESET               HI_AMON_CNT_RESET_OFFSET                /* AXI monitorͳ�Ƽ�������λ�Ĵ���  */
#define AXI_MON_CNT_CTRL                HI_AMON_CNT_CTRL_OFFSET                 /* AXI monitorϵͳ���üĴ��� */
#define AXI_MON_CNT_STATE_INT           HI_AMON_CNT_STATE_INT_OFFSET            /* AXI monitorϵͳ״̬�Ĵ��� */
#define AXI_MON_WIN_COUNTER             HI_AMON_WIN_COUNTER_OFFSET              /* AXI monitorϵͳʱ�䴰������ */
#define AXI_MON_IDLE_COUNTER            HI_AMON_IDLE_COUNTER_OFFSET             /* AXI monitorϵͳidleͳ�Ƽ����� */
#define AXI_MON_PORT_SEL                HI_AMON_PORT_SEL_OFFSET                 /* AXI monitor���ID��AXI port���� */
#define AXI_MON_INT_CLR                 HI_AMON_INT_CLR_OFFSET                  /* AXI monitor�ж�����Ĵ��� */
#define AXI_ID_INT_SRC                  HI_AMON_ID_INT_SRC_OFFSET               /* ID��д����ж�ԭʼ�Ĵ��� */
#define AXI_ID_INT_MASK                 HI_AMON_ID_INT_MASK_OFFSET              /* ID��д����ж����μĴ��� */
#define AXI_ID_INT_STAT                 HI_AMON_ID_INT_STAT_OFFSET              /* ID��д����ж�״̬�Ĵ��� */

/* nΪport��ȡֵ��Χ0-7 */
#define AXI_MON_RD_WAIT_CYCLE_PORTS(n)  (HI_AMON_RD_WAIT_CYCLE_PORTS_0_OFFSET + n*0x10)   /* ���PORTsΪ��ȷ��λ���ȴ����������ĵ�ʱ�����ڼĴ��� */
#define AXI_MON_WR_WAIT_CYCLE_PORTS(n)  (HI_AMON_WR_WAIT_CYCLE_PORTS_0_OFFSET + n*0x10)   /* ���PORTsΪ��ȷ��λд�ȴ����������ĵ�ʱ�����ڼĴ��� */
/* nΪID, ȡֵ��Χ0-7 */
#define AXI_MON_CNT_TYPE(n)             (HI_AMON_CNT_TYPE_0_OFFSET + n*0x4)         /* ���ID�ļ������ѡ�� */
#define AXI_MON_CNT_ID(n)               (HI_AMON_CNT_ID_0_OFFSET + n*0x100)         /* AXI monitorϵͳID��Ϣ�Ĵ��� */
#define AXI_MON_ID_ADDR_DES(n)          (HI_AMON_ID_ADDR_DES_0_OFFSET + n*0x100)    /* ��ص�ַ�±߽� */
#define AXI_MON_ID_ADDR_DES_M(n)        (HI_AMON_ID_ADDR_DES_M_0_OFFSET + n*0x100)  /* ��ص�ַ�ϱ߽� */

/* ͳ�Ƽ����� begin */
#define AXI_MON_INCR1_ID(n)             (HI_AMON_INCR1_ID_0_OFFSET + n*0x100)               /* ���ID n����INCR1���������� */
#define AXI_MON_INCR2_ID(n)             (HI_AMON_INCR2_ID_0_OFFSET + n*0x100)               /* ���ID n����INCR2���������� */
#define AXI_MON_INCR4_ID(n)             (HI_AMON_INCR4_ID_0_OFFSET + n*0x100)               /* ���ID n����INCR4���������� */
#define AXI_MON_INCR8_ID(n)             (HI_AMON_INCR8_ID_0_OFFSET + n*0x100)               /* ���ID n����INCR8���������� */
#define AXI_MON_INCR16_ID(n)            (HI_AMON_INCR16_ID_0_OFFSET + n*0x100)              /* ���ID n����INCR16���������� */
#define AXI_MON_WRAP_ID(n)              (HI_AMON_WRAP_ID_0_OFFSET + n*0x100)                /* ���ID n����WRAP���������� */
#define AXI_MON_BURST_ID(n)             (HI_AMON_BURST_ID_0_OFFSET + n*0x100)               /* ���ID n����BURST���������� */
#define AXI_MON_FINISH_ID(n)            (HI_AMON_FINISH_ID_0_OFFSET + n*0x100)              /* ���ID n���BURST���������� */
#define AXI_MON_RD_WAIT_ID_LOW(n)       (HI_AMON_READ_WAIT_ID_0_OFFSET + n*0x100)           /* ���ID n���ȴ����ڼ���������32λ(64λ�Ĵ�����0~43��Ч) */
#define AXI_MON_RD_WAIT_ID_HIGH(n)      (HI_AMON_READ_WAIT_ID_0_OFFSET + 0x4 + n*0x100)     /* ���ID n���ȴ����ڼ���������32λ(64λ�Ĵ�����0~43��Ч) */
#define AXI_MON_WR_WAIT_ID_LOW(n)       (HI_AMON_WRITE_WAIT_ID_0_OFFSET + n*0x100)          /* ���ID nд�ȴ����ڼ���������32λ(64λ�Ĵ�����0~43��Ч) */
#define AXI_MON_WR_WAIT_ID_HIGH(n)      (HI_AMON_WRITE_WAIT_ID_0_OFFSET + 0x4 + n*0x100)    /* ���ID nд�ȴ����ڼ���������32λ(64λ�Ĵ�����0~43��Ч) */
#define AXI_MON_WR_WAIT_RESP_ID_LOW(n)  (HI_AMON_WRITE_WAIT_RESP_ID_0_OFFSET + n*0x100)     /* ���ID nд��Ӧ�ȴ����ڼ���������32λ(64λ�Ĵ�����0~43��Ч) */
#define AXI_MON_WR_WAIT_RESP_ID_HIGH(n) (HI_AMON_WRITE_WAIT_RESP_ID_0_OFFSET + 0x4 + n*0x100)/* ���ID nд��Ӧ�ȴ����ڼ���������32λ(64λ�Ĵ�����0~43��Ч) */
#define AXI_MON_RD_MAX_WAIT_ID(n)       (HI_AMON_READ_MAX_WAIT_ID_0_OFFSET + n*0x100)       /* ���ID n�����ȴ����ڼ����� */
#define AXI_MON_WR_MAX_WAIT_ID(n)       (HI_AMON_WRITE_MAX_WAIT_ID_0_OFFSET + n*0x100)      /* ���ID nд���ȴ����ڼ����� */
#define AXI_MON_WR_MAX_WAIT_RESP_ID(n)  (HI_AMON_WRITE_MAX_WAIT_RESP_ID_0_OFFSET + n*0x100) /* ���ID nд��Ӧ���ȴ����ڼ����� */
#define AXI_MON_RD_BYTES_ID_LOW(n)      (HI_AMON_READ_BYTES_ID_0_OFFSET + n*0x100)          /* ���ID n������������byteΪ��λ����32λ(64λ�Ĵ�����0~39��Ч) */
#define AXI_MON_RD_BYTES_ID_HIGH(n)     (HI_AMON_READ_BYTES_ID_0_OFFSET + 0x4 + n*0x100)    /* ���ID n������������byteΪ��λ����32λ(64λ�Ĵ�����0~39��Ч) */
#define AXI_MON_WR_BYTES_ID_LOW(n)      (HI_AMON_WRITE_BYTES_ID_0_OFFSET + n*0x100)         /* ���ID nд����������byteΪ��λ����32λ(64λ�Ĵ�����0~39��Ч) */
#define AXI_MON_WR_BYTES_ID_HIGH(n)     (HI_AMON_WRITE_BYTES_ID_0_OFFSET + 0x4 + n*0x100)   /* ���ID nд����������byteΪ��λ����32λ(64λ�Ĵ�����0~39��Ч) */
/* ͳ�Ƽ����� end */
/* AXI monitor�Ĵ���ƫ�Ƶ�ַ���� end */
#define SHM_MEM_M3_MNTN_ADDR            (SHM_BASE_ADDR + SHM_OFFSET_M3_MNTN)

#define AXI_MON_BACK_ADDR               (SHM_MEM_M3_MNTN_ADDR + 32*1024)
#define AXI_MON_BACK_SIZE               (2*1024)
/**************************************************************************
                               ���ݽṹ����
**************************************************************************/

/* ����ַ���� */
enum axi_base_addr_enum
{
    AXI_FAST_ADDR_ENUM,             /* cpu fast����ַ*/
    AXI_SOC_ADDR_ENUM,             /* soc ����ַ */
    AXI_CTRL_ADDR_BUTT                   /* ��Чֵ */
};

typedef unsigned int axi_config_enum_uint32;

/* AXI monitor״̬ */
enum axi_state_enum
{
    AXI_IDLE            = 0x0,  /* IDLE״̬ */
    AXI_WIN_RUNNING     = 0x4,  /* ��ʱ�䴰�ļ��״̬ */
    AXI_UNWIN_RUNNING   = 0x8,  /* ����ʱ�䴰�ļ��״̬ */
    AXI_STOP            = 0xC,  /* STOP״̬ */
    AXI_RESET_FINISH    = 0x10, /* ��λ��� */
    AXI_STATE_BUTT      = 0xFFFFFFFF
};
typedef unsigned int axi_state_enum_uint32;

/* �͹���: �Ĵ������ݡ��ָ� */
typedef struct
{ 
    u32     ctrl_reg;                           /* ���ƼĴ��� begin */
    u32     port_reg;
    u32     int_mask;
    u32     id_reg[AXI_MAX_CONFIG_ID];
    u32     addr_start_reg[AXI_MAX_CONFIG_ID];
    u32     addr_end_reg[AXI_MAX_CONFIG_ID];   /* ���ƼĴ��� end */
    u32     incr1_reg[AXI_MAX_CONFIG_ID];      /* ͳ�ƼĴ��� begin */
    u32     incr2_reg[AXI_MAX_CONFIG_ID]; 
    u32     incr4_reg[AXI_MAX_CONFIG_ID];
    u32     incr8_reg[AXI_MAX_CONFIG_ID]; 
    u32     incr16_reg[AXI_MAX_CONFIG_ID]; 
    u32     wrap_reg[AXI_MAX_CONFIG_ID]; 
    u32     burst_send_reg[AXI_MAX_CONFIG_ID]; 
    u32     burst_fin_reg[AXI_MAX_CONFIG_ID]; 
    u32     rd_cnt_low_reg[AXI_MAX_CONFIG_ID];
    u32     rd_cnt_high_reg[AXI_MAX_CONFIG_ID];
    u32     wr_cnt_low_reg[AXI_MAX_CONFIG_ID];
    u32     wr_cnt_high_reg[AXI_MAX_CONFIG_ID];/* ͳ�ƼĴ��� end */   
} axi_reg_bak_t;

typedef enum{
    amon_cpufast_clk_en = 0,
    amon_cpufast_clk_dis,
    amon_cpufast_clk_status,
    amon_cpufast_monitor_start = 3,
    amon_cpufast_dts_butt
}AMON_CPUFAST_DTS_SYSCTRL;

typedef enum{
    amon_soc_clk_en = 0,
    amon_soc_clk_dis,
    amon_soc_clk_status,
    amon_soc_monitor_start = 3,
    amon_dw_axi_clk_en = 4,
    amon_dw_axi_clk_dis = 5,    
    amon_dw_axi_clk_status = 6,
    amon_soc_dts_butt
}AMON_SOC_DTS_SYSCTRL;
typedef enum{
    AMON_BASE_ADDR = 0,
    AMON_START_BIT,
    AMON_END_BIT,
    AMON_ADDR_BUTT
}AMON_DTS_SYSCTRL_ADDR;

struct amon_sysctrl{
    u32 base_addr;
    u32 start_bit;
    u32 end_bit;
};

struct amon_sysctrl_struct
{
    struct amon_sysctrl amon_sysctrl_soc[amon_soc_dts_butt];
    struct amon_sysctrl amon_sysctrl_fast[amon_cpufast_dts_butt];
};
#define AMON_IS_VALID_ADDR(addr) ((addr != 0x0) ? true:false)

extern struct amon_sysctrl_struct g_amon_sysctrl;

static inline void hi_amon_set_reg(unsigned int value,unsigned int offset,unsigned int lowbit,unsigned highbit)
{
    unsigned int temp   = 0;
    unsigned int mask   = 0;

    temp   = readl(offset);
    mask   = ((1 << (highbit - lowbit + 1)) -1) << lowbit;
    value  = (temp & (~mask)) | ((value <<lowbit) & mask);
    writel(value  ,offset);

}
static inline int hi_amon_get_reg( unsigned int offset,unsigned int lowbit,unsigned int highbit)
{
    unsigned int mask = 0;
    unsigned int temp = 0;
    u32 value = 0;

    temp   = readl(offset);
    mask   = ((1 << (highbit - lowbit + 1)) -1) << lowbit;
    value = temp & mask;
    value = (value) >> lowbit; 

    return value;
}

static __inline__ unsigned int amon_cpufast_get_clk_status(void)
{   

    u32 base_addr =  g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_clk_status].base_addr;
    u32 start_bit = g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_clk_status].start_bit;
    u32 end_bit = g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_clk_status].end_bit;

	if(AMON_IS_VALID_ADDR(base_addr))
	{
        return hi_amon_get_reg(base_addr, start_bit, end_bit);
    }
    else
    {
        return 0;
    }
}

static __inline__ unsigned int amon_soc_get_clk_status(void)
{  

    u32 base_addr =  g_amon_sysctrl.amon_sysctrl_soc[amon_soc_clk_status].base_addr;
    u32 start_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_soc_clk_status].start_bit;
    u32 end_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_soc_clk_status].end_bit;

	if(AMON_IS_VALID_ADDR(base_addr))
	{
        return hi_amon_get_reg(base_addr, start_bit, end_bit);
    }
    else
    {
        return 0;
    }
}
/********************************************************************************/
/*    syssc ������AXI Monitorģ�飬������ֹͣ)                                  */
/********************************************************************************/
/* ����CPUFAST, ���������λΪ1����Ҫ��д0����д1 */
static __inline__ void amon_cpufast_start(void)
{
    u32 base_addr =  g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_monitor_start].base_addr;
    u32 start_bit = g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_monitor_start].start_bit;
    u32 end_bit = g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_monitor_start].end_bit;

	if(AMON_IS_VALID_ADDR(base_addr))
	{
        if(hi_amon_get_reg(base_addr, start_bit, end_bit))
        {
            hi_amon_set_reg(0, base_addr, start_bit, end_bit);
        }
        hi_amon_set_reg(1, base_addr, start_bit, end_bit);
    }
}



/* ����SOC, ���������λΪ1����Ҫ��д0����д1 */
static __inline__ void amon_soc_start()
{

    u32 base_addr =  g_amon_sysctrl.amon_sysctrl_soc[amon_soc_monitor_start].base_addr;
    u32 start_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_soc_monitor_start].start_bit;
    u32 end_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_soc_monitor_start].end_bit;

	if(AMON_IS_VALID_ADDR(base_addr))
	{
        if(hi_amon_get_reg(base_addr, start_bit, end_bit))
        {
            hi_amon_set_reg(0, base_addr, start_bit, end_bit);
        }
        hi_amon_set_reg(1, base_addr, start_bit, end_bit);
    }
}


/* ֹͣCPUFAST */
static __inline__ void amon_cpufast_stop(void)
{
    u32 base_addr =  g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_monitor_start].base_addr;
    u32 start_bit = g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_monitor_start].start_bit;
    u32 end_bit = g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_monitor_start].end_bit;

	if(AMON_IS_VALID_ADDR(base_addr))
	{
        hi_amon_set_reg(0, base_addr, start_bit, end_bit);
    }
}


/* ֹͣSOC */
static __inline__ void amon_soc_stop()
{
    u32 base_addr =  g_amon_sysctrl.amon_sysctrl_soc[amon_soc_monitor_start].base_addr;
    u32 start_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_soc_monitor_start].start_bit;
    u32 end_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_soc_monitor_start].end_bit;

	if(AMON_IS_VALID_ADDR(base_addr))
	{
        hi_amon_set_reg(0, base_addr, start_bit, end_bit);
    }
}
/* AXI Monitor CPUFAST ʱ��ʹ�� */
static __inline__ void amon_cpufast_clk_enable(void)
{
    u32 base_addr =  g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_clk_en].base_addr;
    u32 start_bit = g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_clk_en].start_bit;
    u32 end_bit = g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_clk_en].end_bit;

	if(AMON_IS_VALID_ADDR(base_addr))
	{
        hi_amon_set_reg(1, base_addr, start_bit, end_bit);
    }
}

/* AXI Monitor SOC ʱ��ʹ�� */
static __inline__ void amon_soc_clk_enable(void)
{
    u32 base_addr =  g_amon_sysctrl.amon_sysctrl_soc[amon_soc_clk_en].base_addr;
    u32 start_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_soc_clk_en].start_bit;
    u32 end_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_soc_clk_en].end_bit;

	if(AMON_IS_VALID_ADDR(base_addr))
	{
        hi_amon_set_reg(1, base_addr,  start_bit, end_bit);
    }
    base_addr =  g_amon_sysctrl.amon_sysctrl_soc[amon_dw_axi_clk_en].base_addr;
    start_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_dw_axi_clk_en].start_bit;
    end_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_dw_axi_clk_en].end_bit;

	if(AMON_IS_VALID_ADDR(base_addr))
	{
        hi_amon_set_reg(1, base_addr,start_bit, end_bit);
    }

}
/* AXI Monitor CPUFAST ʱ��ȥʹ�� */
static __inline__ void amon_cpufast_clk_disable(void)
{
    u32 base_addr =  g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_clk_dis].base_addr;
    u32 start_bit = g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_clk_dis].start_bit;
    u32 end_bit = g_amon_sysctrl.amon_sysctrl_fast[amon_cpufast_clk_dis].end_bit;

	if(AMON_IS_VALID_ADDR(base_addr))
	{
        hi_amon_set_reg(1, base_addr, start_bit, end_bit);
    }
}

/* AXI Monitor SOC ʱ��ȥʹ�� */
static __inline__ void amon_soc_clk_disable(void)
{
    u32 base_addr =  g_amon_sysctrl.amon_sysctrl_soc[amon_soc_clk_dis].base_addr;
    u32 start_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_soc_clk_dis].start_bit;
    u32 end_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_soc_clk_dis].end_bit;

	if(AMON_IS_VALID_ADDR(base_addr))
	{
        hi_amon_set_reg(1, base_addr, start_bit, end_bit);
    }

    base_addr =  g_amon_sysctrl.amon_sysctrl_soc[amon_dw_axi_clk_en].base_addr;
    start_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_dw_axi_clk_en].start_bit;
    end_bit = g_amon_sysctrl.amon_sysctrl_soc[amon_dw_axi_clk_en].end_bit;

	if(AMON_IS_VALID_ADDR(base_addr))
	{
        hi_amon_set_reg(1, base_addr, start_bit, end_bit);
    }

}

#ifdef ENABLE_BUILD_AMON
void bsp_amon_suspend();
void bsp_amon_resume();
s32 axi_init(void);
#else
static void inline bsp_amon_suspend()
{
    return;
}
static void inline bsp_amon_resume()
{
    return;
}
static s32 inline axi_init(void)
{
    return 0;
}

#endif

#ifdef __cplusplus
}
#endif

#endif /* _AMON_BALONG_H_ */

