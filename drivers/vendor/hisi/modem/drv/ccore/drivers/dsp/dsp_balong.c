/*************************************************************************
*   ��Ȩ����(C) 2010-2015, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  dsp_balong.c
*
*   ��    �� :  c00326366
*
*   ��    �� :  ���ļ���Ҫ���DSP����ļ��ؼ��͹��Ĵ���
*
*   �޸ļ�¼ :  2015��5��7��  v1.00  c00326366  ����
*************************************************************************/
/*lint --e{537} */
#include <product_config.h>
#include "securec.h"
#include <osl_types.h>
#include <osl_bio.h>
#include <osl_sem.h>
#include <osl_wait.h>
#include <osl_spinlock.h>
#include <osl_malloc.h>


#include <hi_base.h>
#include <hi_pwrctrl.h>
#include <hi_dsp.h>

#include <bsp_shared_ddr.h>

#include <bsp_om.h>
#include <bsp_edma.h>
#include <bsp_dpm.h>
#include <bsp_dsp.h>
#include <bsp_version.h>
#include <bsp_sysctrl.h>
#include <bsp_hardtimer.h>
#include <bsp_memrepair.h>
#include <bsp_pm_om.h>
#include <bsp_hw_spinlock.h>
#include <hi_pwrctrl_interface.h>
#include <mdrv_pm.h>

#include <of.h>

#include "dsp_balong.h"
#include <bsp_dspload.h>
#include <bsp_nvim_mem.h>

#include "drv_nv_id.h"
#include "drv_nv_def.h"
#include "bsp_nvim.h"

#ifdef CONFIG_CBBE

enum dsp_store_state_en{
    DSP_STORE_IDLE = 0,
    DSP_STORE_NEED,
    DSP_STORE_DOING,
    DSP_STORE_HAD,
    DSP_RESTORE_DOING
};


struct dsp_ctrl_state
{
    spinlock_t spin_lock;
    u32 restore_edma_channel_id;
    u32 dsp_power_on_count;
    u32 dsp_unreset_count;
    u32 dsp_clock_enable_count;
    u32 dsp_suspend_count;
    u32 dsp_resume_count;
    u32 dsp_sem_up_count;
    u32 dsp_sem_down_count;
    u32 dsp_run_count;
    u32 dsp_stop_count;
    
    u32 is_dsp_power_on     :1;  /* 1 for power on */
    u32 is_dsp_clock_enable :1;  /* 1 for clock enable */
    u32 is_dsp_unreset      :1;  /* 1 for unreset */
    u32 is_bbe_power_on     :1;  /* 1 for power on */
    u32 is_bbe_clock_enable :1;  /* 1 for clock enable */
    u32 is_bbe_unreset      :1;  /* 1 for unreset */
    u32 is_dsp_running      :1;
    u32 is_dsp_deep_sleep   :1;
    u32 is_dsp_store_state  :3;  /* 0-idle; 1-need store; 2-storing; 3-has store; 4-restoring */
};

struct dsp_sectinfo{
    u32                         imageaddr;      /* ������DDR�е��׵�ַ */
    u32                         ba_tcmnum;      /* ��Ҫ���ݵ�DTCM�θ��� */
    u32                         re_tcmnum;      /* ��Ҫ�ָ���DTCM/ITCM�θ��� */
    struct list_head            oncehead;       /* ֻ��Ҫ����1�εĶε�����ͷ */
    struct list_head            secthead;       /* ÿ�ζ���Ҫ���صĶε�����ͷ */
    struct edma_cb             *pba_edmacb;     /* ����TCM��EDMA�����׵�ַ */
    struct edma_cb             *pre_edmacb;     /* �ָ�TCM��EDMA�����׵�ַ */
};

struct dsp_mainctrl{
    struct dsp_ctrl             tcm_info;
    struct dsp_sysctrl          reg_sysctrl[DSP_DTS_REG_BUTT];
    struct dsp_pwc_ctrl         pwc_ctrl;
    struct dsp_ctrl_state       ctrl_state;
    struct dsp_pm_om_qos_log    dsp_timedump;
    struct dsp_pm_om_qos_log   *dsp_timedump_addr;
    struct dsp_sectinfo         sect_info;
};


struct dsp_sect_node{
    struct dsp_sect_desc_stru   sectinfo;
    struct list_head            sectlist;
};


struct dsp_mainctrl g_dsp_ctrl[BSP_DSP_BUTT];

struct cdsp_drx_debug{
    u32 drx_cbbe16_pd;
    u32 drx_cbbe16_pll;
};

struct cdsp_drx_debug g_cdsp_drx = {0};



static inline void dsp_get_reg(unsigned int *value, struct dsp_sysctrl *pstreg)
{
    unsigned int mask = 0;
    unsigned int temp = 0;
    unsigned int reg    = pstreg->base_addr + pstreg->offset;
   
    temp   = readl(reg);
    mask   = ((1U << (pstreg->end_bit - pstreg->start_bit + 1)) -1) << pstreg->start_bit;
    *value = temp & mask;
    *value = (*value) >> pstreg->start_bit; 
}

static inline void dsp_set_reg(unsigned int value, struct dsp_sysctrl *pstreg)
{
    unsigned int reg    = pstreg->base_addr + pstreg->offset;
    unsigned int temp   = 0;
    unsigned int mask   = 0;

    temp   = readl(reg);
    mask   = ((1U << (pstreg->end_bit - pstreg->start_bit + 1)) -1) << pstreg->start_bit;
    value  = (temp & (~mask)) | ((value <<pstreg->start_bit) & mask);
    writel(value  ,reg);
}

#if 0   /* �����ô��� */

u32 dsp_load_get_reg(u32 base_addr, u32 offset, u32 start_bit, u32 end_bit)
{
    struct dsp_sysctrl streg;
    u32 value;
    
    streg.base_addr = base_addr;
    streg.offset    = offset;
    streg.start_bit = start_bit;
    streg.end_bit   = end_bit;
    
    dsp_get_reg(&value, &streg);

    return value;
}


u32 dsp_load_set_reg(u32 value, u32 base_addr, u32 offset, u32 start_bit, u32 end_bit)
{
    struct dsp_sysctrl streg;
    
    streg.base_addr = base_addr;
    streg.offset    = offset;
    streg.start_bit = start_bit;
    streg.end_bit   = end_bit;
    
    dsp_set_reg(value, &streg);

    return value;
}
#endif

#ifdef DSP_LOAD_WITH_EDMA

int dsp_edma_lli_start(enum bsp_dsp_type_e etype, struct edma_cb *pedmacb)
{
    s32                   edmaid      = 0;
    struct edma_cb       *pedmahead   = NULL;
    
    /* ����ͨ����ע��ͨ���жϻص����� */
    edmaid = bsp_edma_channel_init(EDMA_PWC_CDSP_TCM, NULL, 0, 0);
	if (edmaid < 0)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, 
            "bsp_edma_channel_init EDMA_PWC_CDSP_TCM failed %d. \n", edmaid);
        
        return 1;
    }

    g_dsp_ctrl[etype].ctrl_state.restore_edma_channel_id = edmaid;

    /* ��ȡedma �����׽ڵ��ַ */
    pedmahead = bsp_edma_channel_get_lli_addr((u32)edmaid);
    if (NULL == pedmahead)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, 
            "bsp_edma_channel_get_lli_addr EDMA_PWC_CDSP_TCM failed. \n");
        
        bsp_edma_channel_free((u32)edmaid);
        return 1;
    }
    
    /* �����׽ڵ�Ĵ������Ĵ���������ʹ��memcpy */
    pedmahead->lli      = pedmacb->lli;
    pedmahead->config   = pedmacb->config;
    pedmahead->src_addr = pedmacb->src_addr;
    pedmahead->des_addr = pedmacb->des_addr;
    pedmahead->cnt0     = pedmacb->cnt0;
    pedmahead->bindx    = pedmacb->bindx;
    pedmahead->cindx    = pedmacb->cindx;
    pedmahead->cnt1     = pedmacb->cnt1;

    /* ����EDMA����󼴷��� */
    if (bsp_edma_channel_lli_async_start((u32)edmaid))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, 
            "bsp_edma_channel_lli_async_start EDMA_PWC_CDSP_TCM failed!\n\n");
        
        bsp_edma_channel_free((u32)edmaid);
        
        return 1;
    }

    return 0;
}

/*****************************************************************************
* �� �� ��  : dsp_store_edma_lli_init
*
* ��������  : ����TCM����ʱ��EDMA����
*
* �� �� ֵ  : 0���ɹ���1��ʧ��
*
* ����˵��  : ֻ�ڿ�������ʱ����һ�Σ�����ռ䲻�ͷ�
*
*****************************************************************************/
int dsp_store_edma_lli_init(enum bsp_dsp_type_e etype)
{
    u32 i = 0;
    u32 bcount = 0, acount = 0;
    struct list_head *p, *n;
    struct dsp_sect_node *psect;
    struct edma_cb       *pedmacb     = NULL;
    struct dsp_bin_header_stru *pheader;
    
    if(0 == g_dsp_ctrl[etype].sect_info.ba_tcmnum)
    {
        return 1;
    }
    
    pheader = (struct dsp_bin_header_stru *)g_dsp_ctrl[etype].sect_info.imageaddr;

    /* ������32���ֽڣ���֤��ַ���� */
    pedmacb = (struct edma_cb *)osl_cachedma_malloc((g_dsp_ctrl[etype].sect_info.ba_tcmnum * sizeof(struct edma_cb)) + 32);

    if (NULL == pedmacb)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "osl_cachedma_malloc failed. \n");
        return 1;
    }

    pedmacb = (struct edma_cb *)(((u32)pedmacb+0x1f) & 0xFFFFFFE0);
    g_dsp_ctrl[etype].sect_info.pba_edmacb = pedmacb;

    /* TODO: �����Ƿ���Ҫ�ź������� */
    list_for_each_safe(p, n, &g_dsp_ctrl[etype].sect_info.secthead)
    {
        psect = list_entry(p, struct dsp_sect_node ,sectlist);

        /* ֻ��Ҫ����DTCM */
        if(1 != psect->sectinfo.ucTcmType)
        {
            continue;
        }
        
        i++;

        /* TODO : Ӧ������λ */
        if(i > g_dsp_ctrl[etype].sect_info.ba_tcmnum)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "backup tcm number error i %d, ba_tcmnum %d. \n"
                ,i, g_dsp_ctrl[etype].sect_info.ba_tcmnum);
            return 1;
        }

        /* ���⿽��Խ�磬Ӧ�������� TODO */
        if((pheader->ulFileSize - psect->sectinfo.ulFileOffset) < psect->sectinfo.ulSectSize)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, 
                "ulFileSize 0x%x, ulFileOffset 0x%x, ulSectSize 0x%x. \n",
                pheader->ulFileSize, psect->sectinfo.ulFileOffset, psect->sectinfo.ulSectSize);
            continue;
        }
        
        if(psect->sectinfo.ulSectSize >= BBE_SECT_LEN_64K)
        {
            acount = psect->sectinfo.ulSectSize & 0x3ff;
            bcount = psect->sectinfo.ulSectSize >> 10;
            
            pedmacb->lli        = EDMA_SET_LLI((g_dsp_ctrl[etype].sect_info.pba_edmacb + i), \
                                                ((i < g_dsp_ctrl[etype].sect_info.ba_tcmnum)?0:1));
            pedmacb->config     = EDMA_SET_CONFIG(EDMA_PWC_CDSP_TCM, EDMA_M2M, EDMA_TRANS_WIDTH_64, EDMA_BUR_LEN_16);
            pedmacb->src_addr   = psect->sectinfo.ulTargetAddr;
            pedmacb->des_addr   = (g_dsp_ctrl[etype].sect_info.imageaddr + psect->sectinfo.ulFileOffset);
            pedmacb->cnt0       = ((bcount - 1)<<16) | BBE_SECT_LEN_1K;
            pedmacb->bindx      = (BBE_SECT_LEN_1K<<16) |BBE_SECT_LEN_1K;
            pedmacb->cindx      = 0;
            pedmacb->cnt1       = 0;
            
            pedmacb++;

            i++;

            pedmacb->lli        = EDMA_SET_LLI((g_dsp_ctrl[etype].sect_info.pba_edmacb + i), \
                                                ((i < g_dsp_ctrl[etype].sect_info.ba_tcmnum)?0:1));
            pedmacb->config     = EDMA_SET_CONFIG(EDMA_PWC_CDSP_TCM, EDMA_M2M, EDMA_TRANS_WIDTH_64, EDMA_BUR_LEN_16);
            pedmacb->src_addr   = psect->sectinfo.ulTargetAddr + (bcount * BBE_SECT_LEN_1K);
            pedmacb->des_addr   = (g_dsp_ctrl[etype].sect_info.imageaddr \
                                  + psect->sectinfo.ulFileOffset \
                                  + (bcount * BBE_SECT_LEN_1K));
            pedmacb->cnt0       = acount;
            pedmacb->bindx      = 0;
            pedmacb->cindx      = 0;
            pedmacb->cnt1       = 0;
            
            pedmacb++;
        }
        else
        {
            pedmacb->lli        = EDMA_SET_LLI((g_dsp_ctrl[etype].sect_info.pba_edmacb + i), \
                                                ((i < g_dsp_ctrl[etype].sect_info.ba_tcmnum)?0:1));
            pedmacb->config     = EDMA_SET_CONFIG(EDMA_PWC_CDSP_TCM, EDMA_M2M, EDMA_TRANS_WIDTH_64, EDMA_BUR_LEN_16);
            pedmacb->src_addr   = psect->sectinfo.ulTargetAddr;
            pedmacb->des_addr   = (g_dsp_ctrl[etype].sect_info.imageaddr + psect->sectinfo.ulFileOffset);
            pedmacb->cnt0       = psect->sectinfo.ulSectSize;
            pedmacb->bindx      = 0;
            pedmacb->cindx      = 0;
            pedmacb->cnt1       = 0;
            
            pedmacb++;
        }
    }

    return 0;
}


/*****************************************************************************
* �� �� ��  : dsp_restore_edma_lli_init
*
* ��������  : ����TCM�ָ�ʱ��EDMA����
*
* �� �� ֵ  : 0���ɹ���1��ʧ��
*
* ����˵��  : ֻ�ڿ�������ʱ����һ�Σ�����ռ䲻�ͷ�
*
*****************************************************************************/
int dsp_restore_edma_lli_init(enum bsp_dsp_type_e etype)
{
    u32 i = 0;
    u32 bcount = 0, acount = 0;
    struct list_head *p, *n;
    struct dsp_sect_node *psect;
    struct edma_cb       *pedmacb = NULL;

    if(0 == g_dsp_ctrl[etype].sect_info.re_tcmnum)
    {
        return 1;
    }
    
    /* ������32���ֽڣ���֤��ַ���� */
    pedmacb = (struct edma_cb *)osl_cachedma_malloc((g_dsp_ctrl[etype].sect_info.re_tcmnum * sizeof(struct edma_cb)) + 32);

    if (NULL == pedmacb)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "osl_cachedma_malloc failed. \n");
        return 1;
    }

    pedmacb = (struct edma_cb *)(((u32)pedmacb+0x1f) & 0xFFFFFFE0);
    g_dsp_ctrl[etype].sect_info.pre_edmacb = pedmacb;

    /* TODO: �����Ƿ���Ҫ�ź������� */
    list_for_each_safe(p, n, &g_dsp_ctrl[etype].sect_info.secthead)
    {
        i++;

        /* TODO : Ӧ������λ */
        if(i > g_dsp_ctrl[etype].sect_info.re_tcmnum)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "backup tcm number error i %d, re_tcmnum %d. \n"
                ,i, g_dsp_ctrl[etype].sect_info.re_tcmnum);
            return 1;
        }

        psect = list_entry(p, struct dsp_sect_node ,sectlist);

        if(psect->sectinfo.ulSectSize >= BBE_SECT_LEN_64K)
        {
            acount = psect->sectinfo.ulSectSize & 0x3ff;
            bcount = psect->sectinfo.ulSectSize >> 10;
            
            pedmacb->lli        = EDMA_SET_LLI((g_dsp_ctrl[etype].sect_info.pre_edmacb + i), \
                                                ((i < g_dsp_ctrl[etype].sect_info.re_tcmnum)?0:1));
            pedmacb->config     = EDMA_SET_CONFIG(EDMA_PWC_CDSP_TCM, EDMA_M2M, EDMA_TRANS_WIDTH_64, EDMA_BUR_LEN_16);
            pedmacb->src_addr   = (g_dsp_ctrl[etype].sect_info.imageaddr + psect->sectinfo.ulFileOffset);
            pedmacb->des_addr   = psect->sectinfo.ulTargetAddr;
            pedmacb->cnt0       = ((bcount - 1)<<16) | BBE_SECT_LEN_1K;
            pedmacb->bindx      = (BBE_SECT_LEN_1K<<16) |BBE_SECT_LEN_1K;
            pedmacb->cindx      = 0;
            pedmacb->cnt1       = 0;
            
            pedmacb++;

            i++;

            pedmacb->lli        = EDMA_SET_LLI((g_dsp_ctrl[etype].sect_info.pre_edmacb + i), \
                                                ((i < g_dsp_ctrl[etype].sect_info.re_tcmnum)?0:1));
            pedmacb->config     = EDMA_SET_CONFIG(EDMA_PWC_CDSP_TCM, EDMA_M2M, EDMA_TRANS_WIDTH_64, EDMA_BUR_LEN_16);
            pedmacb->src_addr   = (g_dsp_ctrl[etype].sect_info.imageaddr \
                                  + psect->sectinfo.ulFileOffset \
                                  + (bcount * BBE_SECT_LEN_1K));
            pedmacb->des_addr   = psect->sectinfo.ulTargetAddr + (bcount * BBE_SECT_LEN_1K);
            pedmacb->cnt0       = acount;
            pedmacb->bindx      = 0;
            pedmacb->cindx      = 0;
            pedmacb->cnt1       = 0;
            
            pedmacb++;
        }
        else
        {
            pedmacb->lli        = EDMA_SET_LLI((g_dsp_ctrl[etype].sect_info.pre_edmacb + i), \
                                                ((i < g_dsp_ctrl[etype].sect_info.re_tcmnum)?0:1));
            pedmacb->config     = EDMA_SET_CONFIG(EDMA_PWC_CDSP_TCM, EDMA_M2M, EDMA_TRANS_WIDTH_64, EDMA_BUR_LEN_16);
            pedmacb->src_addr   = (g_dsp_ctrl[etype].sect_info.imageaddr + psect->sectinfo.ulFileOffset);
            pedmacb->des_addr   = psect->sectinfo.ulTargetAddr;
            pedmacb->cnt0       = psect->sectinfo.ulSectSize;
            pedmacb->bindx      = 0;
            pedmacb->cindx      = 0;
            pedmacb->cnt1       = 0;
            
            pedmacb++;
        }
    }
    
    return 0;
}

int dsp_edma_lli_store(enum bsp_dsp_type_e etype)
{
    /* ����ָ�������û����Ҫ���صĶ� */
    if(NULL == g_dsp_ctrl[etype].sect_info.pba_edmacb)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp_edma_lli_store no backup section. \n");
        return 1;
    }
    
    return dsp_edma_lli_start(etype, g_dsp_ctrl[etype].sect_info.pba_edmacb);
}


int dsp_edma_lli_restore(enum bsp_dsp_type_e etype)
{
    /* �������������û����Ҫ���صĶ� */
    if(NULL == g_dsp_ctrl[etype].sect_info.pre_edmacb)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp_edma_lli_restore no restore section. \n");
        return 1;
    }
    
    return dsp_edma_lli_start(etype, g_dsp_ctrl[etype].sect_info.pre_edmacb);
}

#endif

/*****************************************************************************
* �� �� ��  : bsp_bbe_load
*
* ��������  : DSP������ص�TCM(����Э��ջ����ʱ����)
*
* �� �� ֵ  : 0���ɹ���1��ʧ��
*
*****************************************************************************/
int bsp_bbe_load(enum bsp_dsp_type_e etype)
{
    int ret = 0;
    
    if(!g_dsp_ctrl[etype].pwc_ctrl.is_pmctrl_in_dpm)
    {
        ret  = bsp_bbe_power_on_ex(etype);
        ret |= bsp_dsp_clk_enable(etype);
        ret |= bsp_dsp_unreset_ex(etype);
    }

    ret |= bsp_bbe_clk_enable(etype);
    ret |= bsp_bbe_unreset_ex(etype);

    if (ret)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "fail to setup bbe16\r\n");
        return -1;
    }

    /* ����ʱ��tcm�п�����֮ǰ����� */

    /* ��������Ҫ���صĶ���Ϣ */
    ret = dsp_parse_image_header(etype);

    dsp_load_once_sect(etype);

#ifdef DSP_LOAD_WITH_EDMA
    /* ���ݶ���Ϣ����EDMA����ռ� */
    dsp_store_edma_lli_init(etype);
    dsp_restore_edma_lli_init(etype);
#endif

    ret |= bsp_bbe_restore_ex(etype);

    ret |= bsp_bbe_wait_restore_over(etype);

    /* ����ʱ��tcm�п�����֮������� */
    
    g_dsp_ctrl[etype].ctrl_state.is_dsp_deep_sleep = 0;

    return ret;
}

/*****************************************************************************
* �� �� ��  : dsp_parse_image_header
*
* ��������  : ��������ͷ(����Ҫ������صĶ���Ϣ��������)
*
* �� �� ֵ  : 0���ɹ���1��ʧ��
*
* ����˵��  : ֻ��Ҫ����һ�εĶκ�ÿ�ζ���Ҫ���صĶηֿ��洢
*               1.����ֻ��Ҫ����һ�εĶμ��غ�ɾ��
*               2.�������ÿ�ζ���Ҫ���صĶεĸ���������EDMA����ռ�
*
*****************************************************************************/
int dsp_parse_image_header(enum bsp_dsp_type_e etype)
{
    u32 i,num;
    u32 flag = 0;
    struct dsp_bin_header_stru *pheader;
    struct dsp_sect_desc_stru *psect;
    struct dsp_sect_node *pstsectnode;
    
    
    flag = readl((unsigned int)SHM_BASE_ADDR + SHM_OFFSET_CDSP_FLAG);
    if (flag != DSPLOAD_MAGIC)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "CDSP image not found\r\n");
        return 1;
    }
    
    INIT_LIST_HEAD(&g_dsp_ctrl[etype].sect_info.secthead);
    INIT_LIST_HEAD(&g_dsp_ctrl[etype].sect_info.oncehead);

    pheader = (struct dsp_bin_header_stru *)g_dsp_ctrl[etype].tcm_info.bbe_ddr_pub_dtcm_addr;

    if(NULL == pheader)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp_parse_image_header failed :pheader 0x%p.\n", pheader);
        
        return 1;
    }

    g_dsp_ctrl[etype].sect_info.imageaddr = (u32)pheader;
    g_dsp_ctrl[etype].sect_info.ba_tcmnum = 0;
    g_dsp_ctrl[etype].sect_info.re_tcmnum = 0;

    for(i = 0; i < pheader->ulSectNum; i++)
    {
        psect = &pheader->astSect[i];
        
        /* �����п�����sizeΪ0�Ķ� */
        if(0 == psect->ulSectSize)
        {
            continue;
        }

        if((psect->ulFileOffset > pheader->ulFileSize)
            || ((psect->ulFileOffset + psect->ulSectSize) > pheader->ulFileSize)
            || (psect->ulTargetAddr < CPHY_PUB_DTCM_BASE)
            || (psect->ulTargetAddr > (CPHY_PRV_ITCM_BASE+CPHY_PRV_ITCM_SIZE))
            )
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, 
                "dsp_parse_image_header fail : ulFileSize 0x%x, ulFileOffset 0x%x, ulSectSize 0x%x, ulTargetAddr 0x%x.\n", 
                pheader->ulFileSize, psect->ulFileOffset, psect->ulSectSize, psect->ulTargetAddr);

            return 1;
        }

        if(1 == psect->ucLoadType)  /* ÿ�ε͹����ϵ綼��Ҫ���أ���EDMA���� */
        {
            /* ����EDMA�ڵ�ĳ������ƣ����ȴ��ڵ���64Kʱ��Ҫ��ֳ����ΰ��� */
            num = (psect->ulSectSize >= BBE_SECT_LEN_64K) ? 2 : 1;
            
            g_dsp_ctrl[etype].sect_info.re_tcmnum += num;           
            
            if(1 == psect->ucTcmType)
            {
                g_dsp_ctrl[etype].sect_info.ba_tcmnum += num;
            }
            
            pstsectnode = osl_malloc(sizeof(struct dsp_sect_node));
            if(NULL == pstsectnode)
            {
                return 1;
            }

            memcpy_s((void*)&pstsectnode->sectinfo, sizeof(struct dsp_sect_desc_stru),
                   (void*)psect, sizeof(struct dsp_sect_desc_stru));
            /*����bbe16��ARM������DTCM��ַ��һ�£���Ҫ��ƫ��*/
            pstsectnode->sectinfo.ulTargetAddr = pstsectnode->sectinfo.ulTargetAddr - CPHY_PUB_DTCM_BASE + (u32)g_dsp_ctrl[BSP_DSP_CBBE].tcm_info.tcm_dtcm_base_addr;

            list_add(&pstsectnode->sectlist, &g_dsp_ctrl[etype].sect_info.secthead);
        }
        else if(0 == psect->ucLoadType)  /* ֻ�ڿ���ʱ���أ�����MEMCPY */
        {
            pstsectnode = osl_malloc(sizeof(struct dsp_sect_node));
            if(NULL == pstsectnode)
            {
                return 1;
            }

            memcpy_s((void*)&pstsectnode->sectinfo, sizeof(struct dsp_sect_desc_stru),
                   (void*)psect, sizeof(struct dsp_sect_desc_stru));
            /*����bbe16��ARM������DTCM��ַ��һ�£���Ҫ��ƫ��*/
            pstsectnode->sectinfo.ulTargetAddr = pstsectnode->sectinfo.ulTargetAddr - CPHY_PUB_DTCM_BASE + (u32)g_dsp_ctrl[BSP_DSP_CBBE].tcm_info.tcm_dtcm_base_addr;            

            list_add(&pstsectnode->sectlist, &g_dsp_ctrl[etype].sect_info.oncehead);
        }
        else
        {
            /* do nothing */
        }
    }

    return 0;
}


/*****************************************************************************
* �� �� ��  : dsp_load_once_sect
*
* ��������  : ����ֻ��Ҫ����һ�εĶ�
*
* �� �� ֵ  : 0���ɹ���1��ʧ��
*
* ����˵��  : 
*
*****************************************************************************/
void dsp_load_once_sect(enum bsp_dsp_type_e etype)
{
    struct list_head *p, *n;
    struct dsp_sect_node *psect;

    /* TODO: �����Ƿ���Ҫ�ź������� */
    list_for_each_safe(p, n, &g_dsp_ctrl[etype].sect_info.oncehead)
    {
        psect = list_entry(p, struct dsp_sect_node ,sectlist);
    
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, 
            "dsp_load_once_sect src 0x%x: , dst : 0x%x. \n",
            (void*)(g_dsp_ctrl[etype].sect_info.imageaddr + psect->sectinfo.ulFileOffset), (void*)psect->sectinfo.ulTargetAddr);

        memcpy_s((void*)psect->sectinfo.ulTargetAddr, CPHY_PRV_ITCM_SIZE,
               (void*)(g_dsp_ctrl[etype].sect_info.imageaddr + psect->sectinfo.ulFileOffset), psect->sectinfo.ulSectSize);

        /* ucLoadType = 0�Ķ�ֻ��Ҫ����һ�� */
        list_del(&psect->sectlist);
        osl_free(psect);
    }

    return ;
}

/*****************************************************************************
* �� �� ��  : bsp_bbe_store_ex
*
* ��������  : ���ָ��BBE16��DTCM�ı���
*
* �� �� ֵ  : 0���ɹ���1��ʧ��
*
* ����˵��  : ���ڵ͹��ĳ���������ӿڳ�����dump���泡��
*
*****************************************************************************/
int bsp_bbe_store_ex(enum bsp_dsp_type_e etype)
{
#ifdef DSP_LOAD_WITH_EDMA

    return dsp_edma_lli_store(etype);

#else
    int ret = 0;
    struct list_head *p, *n;
    struct dsp_sect_node *psect;
    struct dsp_bin_header_stru *pheader;

    pheader = (struct dsp_bin_header_stru *)g_dsp_ctrl[etype].sect_info.imageaddr;

    /* TODO: �����Ƿ���Ҫ�ź������� */
    list_for_each_safe(p, n, &g_dsp_ctrl[etype].sect_info.secthead)
    {
        psect = list_entry(p, struct dsp_sect_node ,sectlist);

        /* ����DTCM */
        if(1 == psect->sectinfo.ucTcmType)
        {
            memcpy_s((void*)(g_dsp_ctrl[etype].sect_info.imageaddr + psect->sectinfo.ulFileOffset), 
                    (pheader->ulFileSize - psect->sectinfo.ulFileOffset),
                   (void*)psect->sectinfo.ulTargetAddr, psect->sectinfo.ulSectSize);
        }
    }
    
    return ret;
#endif
}


/*****************************************************************************
* �� �� ��  : bsp_bbe_restore_ex
*
* ��������  : �ָ�TCM(���������еĶ���Ϣ��DDR�ָ���TCM�У������TCMͷ)
*
* �� �� ֵ  : 0���ɹ���1��ʧ��
*
* ����˵��  : 
*
*****************************************************************************/
int bsp_bbe_restore_ex(enum bsp_dsp_type_e etype)
{
    int ret = 0;
    
#ifdef DSP_LOAD_WITH_EDMA
    ret = dsp_edma_lli_restore(etype);
    if(ret)
    {
        return ret;
    }
#else
    struct list_head *p, *n;
    struct dsp_sect_node *psect;
    
    /* TODO: �����Ƿ���Ҫ�ź������� */
    list_for_each_safe(p, n, &g_dsp_ctrl[etype].sect_info.secthead)
    {
        psect = list_entry(p, struct dsp_sect_node ,sectlist);
        
        if(1 == psect->sectinfo.ucLoadType)
        {
            memcpy_s((void*)psect->sectinfo.ulTargetAddr, CPHY_PRV_ITCM_SIZE,
                   (void*)(g_dsp_ctrl[etype].sect_info.imageaddr + psect->sectinfo.ulFileOffset), psect->sectinfo.ulSectSize);
        }
    }
#endif

    return ret;
}

int dsp_wait_edma_over(enum bsp_dsp_type_e etype)
{
    int ret = 0;

#ifdef DSP_LOAD_WITH_EDMA
    if(0 == g_dsp_ctrl[etype].ctrl_state.restore_edma_channel_id)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp_wait_edma_over no edma channel start. \n");
        return 1;
    }

    while(!bsp_edma_channel_is_idle(g_dsp_ctrl[etype].ctrl_state.restore_edma_channel_id)) ;
    
    ret = bsp_edma_channel_free(g_dsp_ctrl[etype].ctrl_state.restore_edma_channel_id);
    g_dsp_ctrl[etype].ctrl_state.restore_edma_channel_id = 0;
    if (ret)
    {
        ret = 1;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "fail to free edma channel\r\n");
    }
#endif

    return ret;
}

int bsp_bbe_wait_store_over(enum bsp_dsp_type_e etype)
{
    return dsp_wait_edma_over(etype);
}

int bsp_bbe_wait_restore_over(enum bsp_dsp_type_e etype)
{
    return dsp_wait_edma_over(etype);
}

/*****************************************************************************
* �� �� ��  : bsp_bbe_power_on_ex
*
* ��������  : ��BBE�ϵ磬�ڲ����ýӿ�
*
* �� �� ֵ  : 0���ɹ���1��ʧ��
*
* ����˵��  : 
*
*****************************************************************************/
int bsp_bbe_power_on_ex(enum bsp_dsp_type_e etype)
{
    unsigned long irq_flags;
    int ret = 0;
    unsigned int  tmp;

    spin_lock_irqsave(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);
    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[BBE16_MTCMOS_CTRL_EN].base_addr))
    {
        dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[BBE16_MTCMOS_CTRL_EN]);
    }
    
    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[BBE16_MTCMOS_RDY_STAT].base_addr))
    {
        do
        {
            dsp_get_reg(&tmp, &g_dsp_ctrl[etype].reg_sysctrl[BBE16_MTCMOS_RDY_STAT]);
        }
        while(!tmp);
    }
    
    udelay(30);
    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[BBE16_ISO_CTRL_DIS].base_addr))
    {
        dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[BBE16_ISO_CTRL_DIS]);
    }

    /* TODO: memrepair*/

    g_dsp_ctrl[etype].ctrl_state.is_dsp_power_on = 1;
    g_dsp_ctrl[etype].ctrl_state.is_bbe_power_on = 1;

    spin_unlock_irqrestore(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    return ret;
}

/*****************************************************************************
* �� �� ��  : bsp_bbe_power_off_ex
*
* ��������  : ��BBE�µ磬�ڲ����ýӿ�
*
* �� �� ֵ  : 0���ɹ���1��ʧ��
*
* ����˵��  : 
*
*****************************************************************************/
int bsp_bbe_power_off_ex(enum bsp_dsp_type_e etype)
{
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);
    
    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[BBE16_ISO_CTRL_EN].base_addr))
    {
        dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[BBE16_ISO_CTRL_EN]);
    }
    
    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[BBE16_MTCMOS_CTRL_DIS].base_addr))
    {
        dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[BBE16_MTCMOS_CTRL_DIS]);
    }
    
    g_dsp_ctrl[etype].ctrl_state.is_dsp_power_on = 0;
    g_dsp_ctrl[etype].ctrl_state.is_bbe_power_on = 0;

    spin_unlock_irqrestore(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    return 0;
}


/*****************************************************************************
* �� �� ��  : bsp_bbe_power_up_ex
*
* ��������  : ��BBE�ϵ磬�ⲿ���ýӿ�
*
* �� �� ֵ  : 0���ɹ���1��ʧ��
*
* ����˵��  : 
*
*****************************************************************************/
int bsp_bbe_power_up_ex(enum bsp_dsp_type_e etype)
{
    int ret = 0;
    
    if(!g_dsp_ctrl[etype].pwc_ctrl.is_pmctrl_in_dpm)
    {
       ret =  bsp_bbe_power_on_ex(etype);
       ret |= bsp_dsp_clk_enable(etype);
       ret |= bsp_dsp_unreset_ex(etype);
    }
    
    return ret;
}


/*****************************************************************************
* �� �� ��  : bsp_bbe_power_up_ex
*
* ��������  : ��BBE�µ磬�ⲿ���ýӿ�
*
* �� �� ֵ  : 0���ɹ���1��ʧ��
*
* ����˵��  : 
*
*****************************************************************************/
int bsp_bbe_power_down_ex(enum bsp_dsp_type_e etype)
{
    int ret = 0;
    
    if(1 == g_cdsp_drx.drx_cbbe16_pd)
    {
        return ret;
    }
    else
    {
        if(!g_dsp_ctrl[etype].pwc_ctrl.is_pmctrl_in_dpm)
        {
           ret  = bsp_dsp_reset_ex(etype);
           ret |= bsp_dsp_clk_disable(etype);
           ret |= bsp_bbe_power_off_ex(etype);
        }
        
        return ret;
    }
}


int bsp_bbe_run_ex(enum bsp_dsp_type_e etype)
{
    /* ��bbe��ʼ���� */
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);
    
    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[BBE16_RUNSTALL].base_addr))
    {
        dsp_set_reg(0, &g_dsp_ctrl[etype].reg_sysctrl[BBE16_RUNSTALL]);
    }
    
    g_dsp_ctrl[etype].ctrl_state.is_dsp_running = 1;

    spin_unlock_irqrestore(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    return 0;
}

int bsp_bbe_stop_ex(enum bsp_dsp_type_e etype)
{
    /* ��bbeֹͣ���� */
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    
    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[BBE16_RUNSTALL].base_addr))
    {
        dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[BBE16_RUNSTALL]);
    }
    
    g_dsp_ctrl[etype].ctrl_state.is_dsp_running = 0;

    spin_unlock_irqrestore(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    return 0;
}

int bsp_bbe_clk_enable(enum bsp_dsp_type_e etype)
{
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    /* enable clock */
    
    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[BBE_CORE_CLK_EN].base_addr))
    {
        dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[BBE_CORE_CLK_EN]);
    }

    g_dsp_ctrl[etype].ctrl_state.is_bbe_clock_enable = 1;

    spin_unlock_irqrestore(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    return 0;
}

int bsp_bbe_clk_disable(enum bsp_dsp_type_e etype)
{
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    /* disable clock */
    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[DSP0_CORE_CLK_DIS].base_addr))
    {
        dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[DSP0_CORE_CLK_DIS]);
    }

    g_dsp_ctrl[etype].ctrl_state.is_bbe_clock_enable = 0;

    spin_unlock_irqrestore(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    return 0;
}

int bsp_bbe_unreset_ex(enum bsp_dsp_type_e etype)
{
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    /* unreset BBE16 */
    
    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[BBE16_CORE_SRST_DIS].base_addr))
    {
        dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[BBE16_CORE_SRST_DIS]);
    }

    g_dsp_ctrl[etype].ctrl_state.is_bbe_unreset = 1;

    spin_unlock_irqrestore(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    return 0;
}

int bsp_bbe_reset_ex(enum bsp_dsp_type_e etype)
{
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    /* reset BBE16 */ 
    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[BBE16_CORE_SRST_EN].base_addr))
    {
        dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[BBE16_CORE_SRST_EN]);
    }

    g_dsp_ctrl[etype].ctrl_state.is_bbe_unreset = 0;

    spin_unlock_irqrestore(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    return 0;
}

int bsp_dsp_clk_enable(enum bsp_dsp_type_e etype)
{
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    /* enable clock */
    
    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[BBE16_PD_CLK_EN].base_addr))
    {
        dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[BBE16_PD_CLK_EN]);
    }
    //sc_dsp_clock_enable(1);
    
    g_dsp_ctrl[etype].ctrl_state.is_dsp_clock_enable = 1;

    spin_unlock_irqrestore(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    return 0;
}

int bsp_dsp_clk_disable(enum bsp_dsp_type_e etype)
{
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    /* disable clock */
    
    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[BBE16_PD_CLK_DIS].base_addr))
    {
        dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[BBE16_PD_CLK_DIS]);
    }

    g_dsp_ctrl[etype].ctrl_state.is_dsp_clock_enable = 0;

    spin_unlock_irqrestore(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    return 0;
}

int bsp_dsp_pll_status_ex(enum bsp_dsp_type_e etype)
{
    unsigned int data = 0;
    
    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[PLL_EN].base_addr))
    {
        //K3��V7R5
        dsp_get_reg(&data, &g_dsp_ctrl[etype].reg_sysctrl[PLL_LOCK]);
    }
    
    return (int)data;
}

int bsp_dsp_pll_enable_ex(enum bsp_dsp_type_e etype)
{
    unsigned long irq_flags;
    unsigned int data;
    spin_lock_irqsave(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);
    
    /* open dsp pll */
    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[PLL_EN].base_addr))
    {
        //K3��V7R5
        dsp_get_reg(&data, &g_dsp_ctrl[etype].reg_sysctrl[PLL_LOCK]);

        if(!data)
        {
            dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[PLL_EN]);
            dsp_set_reg(0, &g_dsp_ctrl[etype].reg_sysctrl[PLL_BP]);
            do
            {
                dsp_get_reg(&data, &g_dsp_ctrl[etype].reg_sysctrl[PLL_LOCK]);
            }
            while(!data);
            
            dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[PLL_CLK_GT]);
        }
    }
    else if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[PD].base_addr))
    {
        //P532
        dsp_set_reg(0, &g_dsp_ctrl[etype].reg_sysctrl[PD]);
    }
    spin_unlock_irqrestore(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    return 0;
}

int bsp_dsp_pll_disable_ex(enum bsp_dsp_type_e etype)
{
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);
    /* close dsp dfs */
    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[PLL_EN].base_addr))
    {
        //k3��V7R5
        dsp_set_reg(0, &g_dsp_ctrl[etype].reg_sysctrl[PLL_CLK_GT]);
        dsp_set_reg(0, &g_dsp_ctrl[etype].reg_sysctrl[PLL_EN]);
        dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[PLL_BP]);
    }
    else if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[PD].base_addr))
    {
        //P532
        dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[PD]);
    }
    spin_unlock_irqrestore(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    return 0;
}

/* 0:dsp pll   1:ccpu/peri pll*/
void bsp_bbe_chose_pll_ex(enum bsp_dsp_type_e etype, u32 flag)
{
    u32 tmp = 0;
    if(0 == flag)
    {
        if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[SEL_MODEM_BBE16].base_addr))
        {
            //AUSTIN Xģ
            tmp = readl(g_dsp_ctrl[etype].reg_sysctrl[SEL_MODEM_BBE16].base_addr + g_dsp_ctrl[etype].reg_sysctrl[SEL_MODEM_BBE16].offset);
            /* first: bbe sel dsp pll */
            tmp &= ~0x30;
            tmp |= 0x300020;
            writel(tmp, g_dsp_ctrl[etype].reg_sysctrl[SEL_MODEM_BBE16].base_addr + g_dsp_ctrl[etype].reg_sysctrl[SEL_MODEM_BBE16].offset);
            /* first :div [3:0] div=1 */
            tmp &= ~0xF;
            tmp |= 0xF0000;
            writel(tmp, g_dsp_ctrl[etype].reg_sysctrl[SEL_MODEM_BBE16].base_addr + g_dsp_ctrl[etype].reg_sysctrl[SEL_MODEM_BBE16].offset);
        }
        if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[DSP0_REFCLK_SW].base_addr))
        {
            //V7R5
            dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[BBE_REFCLK_EN]);
            dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[DSP0_REFCLK_SW]);
            dsp_set_reg(0, &g_dsp_ctrl[etype].reg_sysctrl[BBE16_CORE_CLK_DIV]);
            dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[DSP0_FREQMODE]);
            dsp_set_reg(2, &g_dsp_ctrl[etype].reg_sysctrl[BBE_REFCLK_DIS]);
        }
    }
    else
    {
        if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[SEL_MODEM_BBE16].base_addr))
        {
            //AUSTIN Xģ
            tmp = readl(g_dsp_ctrl[etype].reg_sysctrl[SEL_MODEM_BBE16].base_addr + g_dsp_ctrl[etype].reg_sysctrl[SEL_MODEM_BBE16].offset);
            /* first :div [3:0] div=2 */
            tmp &= ~0xF;
            tmp |= 0xF0001;
            writel(tmp, g_dsp_ctrl[etype].reg_sysctrl[SEL_MODEM_BBE16].base_addr + g_dsp_ctrl[etype].reg_sysctrl[SEL_MODEM_BBE16].offset);
            udelay(1);
            /* bbe sel ccpu pll */
            tmp &= ~0x30;
            tmp |= 0x300010;
            writel(tmp, g_dsp_ctrl[etype].reg_sysctrl[SEL_MODEM_BBE16].base_addr + g_dsp_ctrl[etype].reg_sysctrl[SEL_MODEM_BBE16].offset);
        }
        if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[DSP0_REFCLK_SW].base_addr))
        {
            //V7R5
            dsp_set_reg(2, &g_dsp_ctrl[etype].reg_sysctrl[BBE_REFCLK_EN]);
            dsp_set_reg(2, &g_dsp_ctrl[etype].reg_sysctrl[BBE16_CORE_CLK_DIV]);
            dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[DSP0_FREQMODE]);
            udelay(1);
            dsp_set_reg(2, &g_dsp_ctrl[etype].reg_sysctrl[DSP0_REFCLK_SW]);
            dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[BBE_REFCLK_DIS]);            
        }
    }
}

int bsp_dsp_dfs_pll_status_ex(enum bsp_dsp_type_e etype)
{
    int ret = PWRCTRL_COMM_ON;

    if(1 == g_cdsp_drx.drx_cbbe16_pll)
    {
        return ret;
    }
    else
    {
        ret = bsp_dsp_pll_status_ex(etype);
        
        if(ret == 1)
        {
            ret = PWRCTRL_COMM_ON;
        }
        else
        {
            ret = PWRCTRL_COMM_OFF;
        }
        
        return ret;
    }
}

int bsp_dsp_dfs_pll_enable_ex(enum bsp_dsp_type_e etype)
{
    int ret = 0;
    if(g_dsp_ctrl[BSP_DSP_CBBE].pwc_ctrl.can_switch_pll)
    {
        ret = bsp_dsp_pll_enable_ex(etype);
        bsp_bbe_chose_pll_ex(etype, 0);
    }
    return ret;
}

int bsp_dsp_dfs_pll_disable_ex(enum bsp_dsp_type_e etype)
{
    int ret = 0;
    if(1 == g_cdsp_drx.drx_cbbe16_pll)
    {
        return ret;
    }
    else
    {
        if(g_dsp_ctrl[BSP_DSP_CBBE].pwc_ctrl.can_switch_pll)
        {
            bsp_bbe_chose_pll_ex(etype, 1);
            ret = bsp_dsp_pll_disable_ex(etype);
        }
        return ret;
    }
}

void bsp_bbe_refclk_enable_ex(enum bsp_dsp_type_e etype)
{
    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[BBE_REFCLK_EN].base_addr))
    {
        //k3
        dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[BBE_REFCLK_EN]);
    }
}

void bsp_bbe_refclk_disable_ex(enum bsp_dsp_type_e etype)
{
    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[BBE_REFCLK_DIS].base_addr))
    {
        //k3
        dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[BBE_REFCLK_DIS]);
    }
}

int bsp_dsp_unreset_ex(enum bsp_dsp_type_e etype)
{
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    /* unreset BBE16 */
    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[BBE16_PD_SRST_DIS].base_addr))
    {
        dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[BBE16_PD_SRST_DIS]);
    }
    
    g_dsp_ctrl[etype].ctrl_state.is_dsp_unreset = 1;

    spin_unlock_irqrestore(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    return 0;
}

int bsp_dsp_reset_ex(enum bsp_dsp_type_e etype)
{
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    /* reset BBE16 */
    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[BBE16_PD_SRST_EN].base_addr))
    {
        dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[BBE16_PD_SRST_EN]);
    } 
    
    g_dsp_ctrl[etype].ctrl_state.is_dsp_unreset = 0;

    spin_unlock_irqrestore(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    return 0;
}


/*****************************************************************************
* �� �� ��  : bsp_dsp_store_dtcm_force
*
* ��������  : ǿ�ƽ���BBE16��DTCM�ı��ݣ�����dumpģ�鱸��
*
* �� �� ֵ  : 0���ɹ���1��ʧ��
*
* ����˵��  : 
*
*****************************************************************************/
int bsp_dsp_store_dtcm_force(enum bsp_dsp_type_e etype)
{
    int ret = 0;
    ret = (int)(g_dsp_ctrl[etype].ctrl_state.is_dsp_power_on &&
                g_dsp_ctrl[etype].ctrl_state.is_dsp_clock_enable &&
                g_dsp_ctrl[etype].ctrl_state.is_dsp_unreset &&
                g_dsp_ctrl[etype].ctrl_state.is_bbe_power_on &&
                g_dsp_ctrl[etype].ctrl_state.is_bbe_clock_enable &&
                g_dsp_ctrl[etype].ctrl_state.is_bbe_unreset);
    
    if (!ret)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "store %d dtcm fail : dsp is in deep sleep!\r\n", etype);
        return ret;
    }
    
    ret  = bsp_bbe_stop_ex(etype);
    ret |= bsp_bbe_store_ex(etype);
    if (ret)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "fail to store %d dtcm\r\n", etype);
        return 1;
    }
    
    return ret;
}


/*****************************************************************************
* �� �� ��  : bsp_dsp_store_dtcm_normal
*
* ��������  : DSP����˯��ʱBBE16��DTCM�ı��ݣ�����MSP�͹���ģ�鱸��
*
* �� �� ֵ  : 0���ɹ���1��ʧ��
*
* ����˵��  : 
*
*****************************************************************************/
int bsp_dsp_store_dtcm_normal(enum bsp_dsp_type_e etype)
{
    int ret = 0;

    g_dsp_ctrl[etype].ctrl_state.is_dsp_store_state = DSP_STORE_NEED;
    
    if(!g_dsp_ctrl[etype].pwc_ctrl.is_pmctrl_in_dpm)
    {
        ret = bsp_bbe_store_ex(etype);
        
        g_dsp_ctrl[etype].ctrl_state.is_dsp_store_state = DSP_STORE_DOING;
    }
    
    g_dsp_ctrl[etype].ctrl_state.is_dsp_deep_sleep = 1;

    return ret;
}


/*****************************************************************************
* �� �� ��  : bsp_dsp_wait_store_over_normal
*
* ��������  : �ȴ��������
*
* �� �� ֵ  : 0���ɹ���1��ʧ��
*
* ����˵��  : 
*
*****************************************************************************/
int bsp_dsp_wait_store_over_normal(enum bsp_dsp_type_e etype)
{
    int ret = 0;
    
    if (DSP_STORE_DOING == g_dsp_ctrl[etype].ctrl_state.is_dsp_store_state)
    {
        ret = bsp_bbe_wait_store_over(etype);
        
        g_dsp_ctrl[etype].ctrl_state.is_dsp_store_state = DSP_STORE_HAD;
    }
    
    return ret;
}


/*****************************************************************************
* �� �� ��  : bsp_dsp_restore_tcm_normal
*
* ��������  : DSP����˯��ʱBBE16��TCM�Ļָ�������MSP�͹���ģ����DSP����
*
* �� �� ֵ  : 0���ɹ���1��ʧ��
*
* ����˵��  : 
*
*****************************************************************************/
int bsp_dsp_restore_tcm_normal(enum bsp_dsp_type_e etype)
{
    int ret = 0;

    if(DSP_STORE_HAD == g_dsp_ctrl[etype].ctrl_state.is_dsp_store_state)
    {
        ret = bsp_bbe_restore_ex(etype);
        
        g_dsp_ctrl[etype].ctrl_state.is_dsp_store_state = DSP_RESTORE_DOING;
    }

    g_dsp_ctrl[etype].ctrl_state.is_dsp_deep_sleep = 0;

    return ret;
}


/*****************************************************************************
* �� �� ��  : bsp_dsp_wait_restore_over_normal
*
* ��������  : �ȴ��ָ����
*
* �� �� ֵ  : 0���ɹ���1��ʧ��
*
* ����˵��  : 
*
*****************************************************************************/
int bsp_dsp_wait_restore_over_normal(enum bsp_dsp_type_e etype)
{
    int ret = 0;
    
    if (DSP_RESTORE_DOING == g_dsp_ctrl[etype].ctrl_state.is_dsp_store_state)
    {
        ret = bsp_bbe_wait_restore_over(etype);
        
        g_dsp_ctrl[etype].ctrl_state.is_dsp_store_state = DSP_STORE_IDLE;
    }
    
    return ret;
}


/*****************************************************************************
* �� �� ��  : bsp_dsp_get_addr_info
*
* ��������  : ��ȡDSP��ص�ַ��Ϣ
*
* �������  : pAddrInfo
* �������  : pAddrInfo
*
* �� �� ֵ  : 0-�ɹ�; 1-ʧ��
* ����˵��  : ������ô˽ӿ�ʱ�������������û�г�ʼ�����򷵻�ʧ��
*
*****************************************************************************/
int bsp_dsp_get_addr_info(enum bsp_dsp_type_e etype, BSP_DSP_ADDR_INFO_STRU *pAddrInfo)
{
    if(NULL == pAddrInfo)
    {
        return 1;
    }
    
    if(BSP_DSP_CBBE == etype)
    {
        if(0 != g_dsp_ctrl[etype].tcm_info.bbe_ddr_pub_dtcm_addr)
        {
            pAddrInfo->load_addr    = (u32)g_dsp_ctrl[etype].tcm_info.bbe_ddr_pub_dtcm_addr;
            pAddrInfo->backup_addr  = (u32)(g_dsp_ctrl[etype].tcm_info.bbe_ddr_pub_dtcm_addr + CBBE_1X_DATA_OFFSET);

            return 0;
        }
    }

    return 1;
}

#ifdef CONFIG_CCORE_PM

/*****************************************************************************
* �� �� ��  : bsp_dsp_dpm_prepare
*
* ��������  : dpm prepare������BBE16��DTCM�ı���
*
* �� �� ֵ  : 0���ɹ���1��ʧ��
*
* ����˵��  : 
*
*****************************************************************************/
int bsp_dsp_dpm_prepare(struct dpm_device *dev)
{
    int ret = 0;
    enum bsp_dsp_type_e etype = BSP_DSP_CBBE;

    if(g_dsp_ctrl[etype].pwc_ctrl.is_pmctrl_in_dpm)
    {
        if(DSP_STORE_NEED == g_dsp_ctrl[etype].ctrl_state.is_dsp_store_state)
        {
            ret = bsp_bbe_clk_enable(etype);
            ret |= bsp_bbe_unreset_ex(etype);

            /* save public image's data */
            ret |= bsp_bbe_store_ex(etype);
            g_dsp_ctrl[etype].ctrl_state.is_dsp_store_state = DSP_STORE_DOING;
        }
    }
    
    return ret;
}


/*****************************************************************************
* �� �� ��  : bsp_dsp_dpm_suspend_late
*
* ��������  : dpm late������BBE16��DTCM�ı���
*
* �� �� ֵ  : 0���ɹ���1��ʧ��
*
* ����˵��  : 
*
*****************************************************************************/
int bsp_dsp_dpm_suspend_late(struct dpm_device *dev)
{
    /* ���豸����˯��ģʽ֮ǰ�ж��Ƿ���Ĵ洢��ɣ������ɣ���bbe�µ� */
    int ret = 0;
    enum bsp_dsp_type_e etype = BSP_DSP_CBBE;
    
    if(g_dsp_ctrl[etype].pwc_ctrl.is_pmctrl_in_dpm)
    {
        if(DSP_STORE_DOING == g_dsp_ctrl[etype].ctrl_state.is_dsp_store_state)
        {
            ret = bsp_bbe_wait_store_over(etype);
            g_dsp_ctrl[etype].ctrl_state.is_dsp_store_state = DSP_STORE_HAD;
            
            ret |= bsp_bbe_reset_ex(etype);
            ret |= bsp_bbe_clk_disable(etype);
        }

        ret |= bsp_dsp_reset_ex(etype);
        ret |= bsp_dsp_clk_disable(etype);
        
#if defined(CONFIG_G_POWER_OPTIMIZE)
        bsp_bbe_refclk_disable_ex(etype);
#else
        ret |= bsp_dsp_pll_disable_ex(etype);
#endif
        if(g_dsp_ctrl[etype].ctrl_state.is_dsp_deep_sleep)
        {
            ret |= bsp_bbe_power_off_ex(etype);
        }
    }
    else
    {
#if defined(CONFIG_G_POWER_OPTIMIZE)
        bsp_bbe_refclk_disable_ex(etype);
#else
        /* V7R5·����bbe16�������µ磬DPMֻ����ر�DSP PLL��
           ����V7R5��DSP�µ�ʱ�Ѿ��е�peri_pll��dsp_pll��dsp�ϵ�ʱ�򿪣����л��������˴�����ɾ�� */
//        ret |= bsp_dsp_pll_disable_ex(etype);
#endif
    }
    
    return ret;
}


/*****************************************************************************
* �� �� ��  : bsp_dsp_dpm_resume_early
*
* ��������  : dpm resume early������BBE16��TCM�Ļָ�
*
* �� �� ֵ  : 0���ɹ���1��ʧ��
*
* ����˵��  : 
*
*****************************************************************************/
int bsp_dsp_dpm_resume_early(struct dpm_device *dev)
{
    /* dsp�ϵ� */
    int ret = 0;
    enum bsp_dsp_type_e etype = BSP_DSP_CBBE;

    if(g_dsp_ctrl[etype].pwc_ctrl.is_pmctrl_in_dpm)
    {
        if(g_dsp_ctrl[etype].ctrl_state.is_dsp_deep_sleep)
        {
            ret |= bsp_bbe_power_on_ex(etype);
        }
        
#if defined(CONFIG_G_POWER_OPTIMIZE)
        bsp_bbe_refclk_enable_ex(etype);
#else
        ret |= bsp_dsp_pll_enable_ex(etype);
#endif

        ret |= bsp_dsp_clk_enable(etype);
        ret |= bsp_dsp_unreset_ex(etype);
    }
    else
    {
#if defined(CONFIG_G_POWER_OPTIMIZE)
        /* K3V5·����bbe16�������µ磬DPMֻ�����bbp��ϵͳ�ο�ʱ�� */
        bsp_bbe_refclk_enable_ex(etype);
#else
        /* V7R5·����bbe16�������µ磬DPMֻ�����DSP PLL��
           ����V7R5��DSP�µ�ʱ�Ѿ��е�peri_pll��dsp_pll��dsp�ϵ�ʱ�򿪣����л��������˴�����ɾ�� */
//      ret |= bsp_dsp_pll_enable_ex(etype);
#endif
    }
    
    return ret;
}


/*****************************************************************************
* �� �� ��  : bsp_dsp_dpm_resume_early
*
* ��������  : dpm complete������BBE16
*
* �� �� ֵ  : 0���ɹ���1��ʧ��
*
* ����˵��  : 
*
*****************************************************************************/
int bsp_dsp_dpm_complete(struct dpm_device *dev)
{
    /* dsp�ϵ���bbe */
    int ret = 0;
    enum bsp_dsp_type_e etype = BSP_DSP_CBBE;

    if(g_dsp_ctrl[etype].pwc_ctrl.is_pmctrl_in_dpm)
    {
        /* ��������ģ��suspend��ʧ�ܵ���bsp_dsp_dpm_suspend_lateû�ߵ� */
        if(DSP_STORE_DOING == g_dsp_ctrl[etype].ctrl_state.is_dsp_store_state)
        {
            ret = bsp_bbe_wait_store_over(etype);
            ret |= bsp_bbe_reset_ex(etype);
            ret |= bsp_bbe_clk_disable(etype);
        }
    }
    
    return ret;
}


static struct dpm_device g_dsp_dpm_device = {
    .device_name = "dsp_dpm",
    .prepare        = bsp_dsp_dpm_prepare,
    .suspend_early  = NULL,
    .suspend        = NULL,
    .suspend_late   = bsp_dsp_dpm_suspend_late,
    .resume_early   = bsp_dsp_dpm_resume_early,
    .resume         = NULL,
    .resume_late    = NULL,
    .complete       = bsp_dsp_dpm_complete,
};
#endif

/*lint -save -e525*/
void dsp_load_init(void)
{
    int ret = 0;
    int i = 0;
    u32 reg_addr[4];
    struct device_node *dev_node = NULL;
    char* node_name[2] = {
        "hisilicon,cdsp_balong_dtcm",
        "hisilicon,cdsp_balong_itcm"
    };
    ST_PWC_SWITCH_STRU cfg;
    char *reg_name[DSP_DTS_REG_BUTT] = {
                            "bbe16_pd_clk_en", 
                            "bbe16_pd_clk_dis", 
                            "bbe16_pd_srst_dis", 
                            "bbe16_pd_srst_en",
                            "bbe16_core_srst_dis", 
                            "bbe16_dbg_srst_dis", 
                            "bbe16_core_srst_en", 
                            "bbe16_dbg_srst_en", 
                            "pd",
                            "bbe16_runstall",
                            "bbe_refclk_en",
                            "bbe_refclk_dis", 
                            "pll_lock",
                            "pll_en",
                            "pll_bp",
                            "pll_postdivpd",
                            "pll_clk_gt", 
                            "div_modem_bbe16",
                            "sel_modem_bbe16",
                            "clkdivmasken",
                            "dsp0_core_clk_dis", 
                            "dsp0_dbg_clk_dis",
                            "bbe_core_clk_en",
                            "dsp0_dbg_clk_en",
                            "bbe16_mtcmos_ctrl_en", 
                            "bbe16_mtcmos_rdy_stat",
                            "bbe16_iso_ctrl_dis",
                            "bbe16_mtcmos_ctrl_dis",
                            "bbe16_iso_ctrl_en",
                            "bbe16_waiti_en",
                            "bbe16_waiti_div",
                            "bbe16_core_clk_div",
                            "dsp0_freqmode",
                            "dsp0_refclk_sw"
                            };

    if(BSP_OK != bsp_nvm_read(NV_ID_DRV_NV_PWC_SWITCH, (u8 *)&cfg, sizeof(ST_PWC_SWITCH_STRU)))
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "Dsp_balong get NV_ID_DRV_NV_PWC_SWITCH failed!\n");
	}
    else
    {
        g_cdsp_drx.drx_cbbe16_pd = cfg.drx_cbbe16_pd;
        g_cdsp_drx.drx_cbbe16_pll =  cfg.drx_cbbe16_pll;
    }

    memset_s(&g_dsp_ctrl[BSP_DSP_TLBBE], sizeof(g_dsp_ctrl), 0, sizeof(g_dsp_ctrl));

    dev_node = of_find_compatible_node(NULL,NULL,node_name[0]);
    if(!dev_node)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp init failed : get cdsp_balong_dtcm node failed!\n");
        return;
    }
    
    /* �ڴ�ӳ�䣬��û�ַ */
    g_dsp_ctrl[BSP_DSP_CBBE].tcm_info.tcm_dtcm_base_addr = (char *)of_iomap(dev_node, 0);
    if (NULL == g_dsp_ctrl[BSP_DSP_CBBE].tcm_info.tcm_dtcm_base_addr)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp init failed : cdsp_balong_dtcm iomap failed!\n");
        return;
    }
    
    g_dsp_ctrl[BSP_DSP_CBBE].tcm_info.lphy_pub_dtcm_size = CPHY_PUB_DTCM_SIZE;
    
    ret  = of_property_read_u32(dev_node, "is_pmctrl_in_dpm", &g_dsp_ctrl[BSP_DSP_CBBE].pwc_ctrl.is_pmctrl_in_dpm);   
    ret |= of_property_read_u32(dev_node, "can_switch_pll", &g_dsp_ctrl[BSP_DSP_CBBE].pwc_ctrl.can_switch_pll);
    if(ret)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp init failed : dtcm dev_node read failed!\n");
        return;
    }
    
    dev_node = of_find_compatible_node(NULL,NULL,node_name[1]);
    if(!dev_node)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp init failed : get dsp_balong_itcm node faileded!\n");
        return;
    }
    
    /* �ڴ�ӳ�䣬��û�ַ */
    g_dsp_ctrl[BSP_DSP_CBBE].tcm_info.tcm_itcm_base_addr = (char *)of_iomap(dev_node, 0);
    if (NULL == g_dsp_ctrl[BSP_DSP_CBBE].tcm_info.tcm_itcm_base_addr)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp init failed : dsp_balong_itcm iomap failed!\n");
        return;
    }
    g_dsp_ctrl[BSP_DSP_CBBE].tcm_info.lphy_pub_itcm_size = CPHY_PUB_ITCM_SIZE;

    g_dsp_ctrl[BSP_DSP_CBBE].tcm_info.bbe_ddr_pub_dtcm_addr = (int)ioremap_wc((MMU_VA_T)DDR_CBBE_IMAGE_ADDR, DDR_CBBE_IMAGE_SIZE);
    g_dsp_ctrl[BSP_DSP_CBBE].tcm_info.bbe_ddr_pub_itcm_addr = g_dsp_ctrl[BSP_DSP_CBBE].tcm_info.bbe_ddr_pub_dtcm_addr + CPHY_PUB_DTCM_SIZE;

    for(i = 0; i < DSP_DTS_REG_BUTT; i++)
    {
        ret = of_property_read_u32_array(dev_node, reg_name[i], reg_addr, DSP_ADDR_BUTT);   
        if(ret)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp init failed : itcm dev_node reg read failed!\n");
            return;
        }
        
        g_dsp_ctrl[BSP_DSP_CBBE].reg_sysctrl[i].base_addr = (u32)bsp_sysctrl_addr_get((void *)reg_addr[DSP_BASE_ADDR]);
        g_dsp_ctrl[BSP_DSP_CBBE].reg_sysctrl[i].offset    = reg_addr[DSP_OFFSET];
        g_dsp_ctrl[BSP_DSP_CBBE].reg_sysctrl[i].start_bit = reg_addr[DSP_START_BIT];
        g_dsp_ctrl[BSP_DSP_CBBE].reg_sysctrl[i].end_bit   = reg_addr[DSP_END_BIT];
    }

    spin_lock_init(&(g_dsp_ctrl[BSP_DSP_CBBE].ctrl_state.spin_lock));

#ifdef CONFIG_CCORE_PM
    ret = bsp_device_pm_add(&g_dsp_dpm_device);
#endif
    if (ret)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp init failed : bsp_device_pm_add failed!\n");
        return;
    }

    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "[DSP] dsp_load_init success .\n");
}
/*lint -restore*/

/*****************************************************************************
* �� �� ��  : dsp_load_help
*
* ��������  : DSP����ģ��İ���
*
* ����˵��  : 
*
*****************************************************************************/
void dsp_load_help(enum bsp_dsp_type_e etype)
{
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, 
        "is_dsp_power_on %d.\n", g_dsp_ctrl[etype].ctrl_state.is_dsp_power_on);
    
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, 
        "is_dsp_clock_enable %d.\n", g_dsp_ctrl[etype].ctrl_state.is_dsp_clock_enable);
    
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, 
        "is_dsp_unreset %d.\n", g_dsp_ctrl[etype].ctrl_state.is_dsp_unreset);
    
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, 
        "is_bbe_power_on %d.\n", g_dsp_ctrl[etype].ctrl_state.is_bbe_power_on);
    
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, 
        "is_bbe_clock_enable %d.\n", g_dsp_ctrl[etype].ctrl_state.is_bbe_clock_enable);
    
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, 
        "is_bbe_unreset %d.\n", g_dsp_ctrl[etype].ctrl_state.is_bbe_unreset);
    
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, 
        "is_dsp_running %d.\n", g_dsp_ctrl[etype].ctrl_state.is_dsp_running);
    
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, 
        "is_dsp_deep_sleep %d.\n", g_dsp_ctrl[etype].ctrl_state.is_dsp_deep_sleep);
    
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, 
        "is_dsp_store_state %d.\n", g_dsp_ctrl[etype].ctrl_state.is_dsp_store_state);
}
#endif


