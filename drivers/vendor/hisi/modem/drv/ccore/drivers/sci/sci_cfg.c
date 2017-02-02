/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : New0001.h
  �� �� ��   : ����
  ��    ��   : ��ӭ�� 61362
  ��������   : 2013��1��11��
  ����޸�   :
  ��������   : �ṩDSDA SCI��Ӳ������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��1��11��
    ��    ��   : ��ӭ�� 61362
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

/*lint --e{729,830,569,737,537,525,830,774,506}*/


#include <string.h>
#include "securec.h" 
#include "product_config.h"
#include "drv_nv_id.h"
#include "of.h"
#include "bsp_edma.h"
#include "bsp_nvim.h"
#include "bsp_sci.h"
#include "bsp_icc.h"
#include "bsp_clk.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/*��¼NV_SCI��ȫ�ֱ���*/
#if (FEATURE_OFF==FEATURE_MULTI_MODEM)
unsigned int g_SciNVValue = 0;   		/* default */
#else
#if(MULTI_MODEM_NUMBER == 3)
unsigned int g_SciNVValue = 0x8803;      /* default */
#elif(MULTI_MODEM_NUMBER == 2)
unsigned int g_SciNVValue = 0x802;      /* default */
#elif(MULTI_MODEM_NUMBER == 1)
unsigned int g_SciNVValue = 0;      /* default */
#endif
#endif

/*��¼�쳣�ļ�·����ȫ�ֱ���*/
const char * g_pcCardRecordFileName[2] = {SCI0_RECORD_LOG_PATH_LOST_CARD,
                                         SCI1_RECORD_LOG_PATH_LOST_CARD};

/*��¼��������ȫ�ֱ���*/
const char * g_pcCardTaskName[2] = {SCI_CARD0_SYNC_TASK_NAME,
                                   SCI_CARD1_SYNC_TASK_NAME};

const char * g_pcCardHOTPLUGTaskName[2] = {SCI_CARD0_HOTPLUG_TASK_NAME,
                                   SCI_CARD1_HOTPLUG_TASK_NAME};

void sci_print_cfg(SCI_CFG_STRU* p_sci_cfg);

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
    /*****************************************************************************
     �� �� ��  : sci_print_cfg
     ��������  : ��ӡ��ǰ��������
     �������  : 
     �������  : ��
     �� �� ֵ  : int
     ���ú���  :
     ��������  :
    
     �޸���ʷ      :
    
    *****************************************************************************/

void sci_print_cfg(SCI_CFG_STRU* p_sci_cfg)
{
    sci_print_error("card_id = %d\n",p_sci_cfg->card_id);
        
    sci_print_error("sci_id = %d\n",p_sci_cfg->sci_id);
        
    sci_print_error("base_addr = 0x%x\n",p_sci_cfg->base_addr);
        
    sci_print_error("int_number = 0x%x\n",p_sci_cfg->int_number);
    
    sci_print_error("icc_chnl = 0x%x\n",p_sci_cfg->icc_chnl);
    
    sci_print_error("pwr_type = %s\n",p_sci_cfg->pwr_type);
        
    sci_print_error("syncTaskName = %s\n",p_sci_cfg->syncTaskName);
        
    sci_print_error("hotPlugTaskName = %s\n",p_sci_cfg->hotPlugTaskName);
        
    sci_print_error("sci_int_handler = 0x%x\n",p_sci_cfg->sci_int_handler);

    sci_print_error("sync_task_id = %d\n",p_sci_cfg->sync_task_id);
        
    sci_print_error("hotplug_task_id = %d\n",p_sci_cfg->hotplug_task_id);


}

    /*****************************************************************************
     �� �� ��  : sci_set_default_nv
     ��������  : �趨Ĭ�ϵ�NVֵ
     �������  : 
     �������  : ��
     �� �� ֵ  : int
     ���ú���  :
     ��������  :
    
     �޸���ʷ      :
    
    *****************************************************************************/
void bsp_sci_set_default_nv()
{   
#if(FEATURE_ON == FEATURE_MULTI_MODEM)

    NV_SCI_CFG_UNION * nv_val = (NV_SCI_CFG_UNION *)&g_SciNVValue;

    if(MULTI_MODEM_NUMBER == 3)
    {    if(nv_val->cfg.card_num != 3 
            || nv_val->cfg.sci0 > 2 || nv_val->cfg.sci1 > 2 || nv_val->cfg.sci2 > 2 
            || nv_val->cfg.sci0 ==nv_val->cfg.sci1  || nv_val->cfg.sci0 ==nv_val->cfg.sci2 || nv_val->cfg.sci2 ==nv_val->cfg.sci1 )
         {
            g_SciNVValue = 0x8803;
            
            sci_print("3card nv value is error use default val %x\n",g_SciNVValue);
         }
    }
    else if(MULTI_MODEM_NUMBER == 2)
    {
         if(0x802 !=g_SciNVValue && 0x102 !=g_SciNVValue)
         {
             g_SciNVValue = 0x802;
             
             sci_print("2card nv value is error use default val %x\n",g_SciNVValue);
         }
    }
    else if(MULTI_MODEM_NUMBER == 1)
    {
         g_SciNVValue = 0x0;
         
         sci_print("1card nv value is error use default val %x\n",g_SciNVValue);
    }
#else
    g_SciNVValue = 0x0;
    sci_print("1card nv value is error use default val %x\n",g_SciNVValue);
#endif


}

/*****************************************************************************
 �� �� ��  : bsp_sci_get_nv
 ��������  : ��ȡSCI��NV��ֵ
 �������  : 
 �������  : ��
 �� �� ֵ  : int
 ���ú���  :
 ��������  :

 �޸���ʷ      :

*****************************************************************************/

int bsp_sci_get_nv(unsigned int *value)
{
    /*����NV���ӿ�*/
    if(BSP_OK == bsp_nvm_read(NV_ID_DRV_SCI_DSDA_SELECT, (u8*)&g_SciNVValue, NV_SCI_LEN)) 
    {
        bsp_sci_set_default_nv();

        /*��ȡ�ɹ�*/
        *value = g_SciNVValue;  
        sci_print_debug("nv value:0x%x\r\n",g_SciNVValue);
        return BSP_OK;
    }
    else 
	{    
	    *value = g_SciNVValue;
        sci_print("read nv error use default val %x\n",g_SciNVValue);
        return BSP_ERROR;
    }
    
}


/*****************************************************************************
 �� �� ��  : bsp_sci_cfg
 ��������  : ����Ӳ����ص�����
 �������  : unsigned int card_id
             unsigned int sci_id
 �������  : ��
 �� �� ֵ  : int
 ���ú���  :
 ��������  : BSP_SCI_ParseNV

 �޸���ʷ      :

*****************************************************************************/
int bsp_sci_cfg(unsigned int card_id, unsigned int sci_id)
{
    SCI_CFG_STRU * p_sci_cfg;
    struct device_node* dev = NULL;
    const char* name[] = {"hisilicon,sci0_balong","hisilicon,sci1_balong","null"};
    sci_freq_str sci_freq = {0,};
    s32 irq = 0;
    char* base_addr = NULL;
    
#if(FEATURE_ON == FEATURE_MULTI_MODEM)
    NV_SCI_CFG_UNION * nv_val = (NV_SCI_CFG_UNION *)(&g_SciNVValue);
#endif

    enum ICC_RECV_FUNC_ID ac_channel[2] = {IFC_RECV_FUNC_SIM0,IFC_RECV_FUNC_SIM1};

    p_sci_cfg = (SCI_CFG_STRU *)((int)&_sci_cfg_data_start + \
                                (int)(sizeof(SCI_CFG_STRU)*card_id));

    if (card_id >= (unsigned int)(&_sci_init_data_end - &_sci_init_data_start)) 
	{
		sci_print_error("card_id is too large!\r\n");
        return BSP_ERROR;
    }
    
    if(sci_id != CARD_CONNECT_SCI0  && sci_id != CARD_CONNECT_SCI1 && sci_id != CARD_CONNECT_SCI2)
    {
    	sci_print_error("card_id error!\r\n");
        return BSP_ERROR;
    }
    
    if(card_id > CARD2)
    {
        sci_print_error("card_id bigger than card2!\r\n");
        return BSP_ERROR;
    }
    
#if(FEATURE_ON == FEATURE_MULTI_MODEM)
    if(MULTI_MODEM_NUMBER == 3)
    {
        if(nv_val->cfg.sci0 ==nv_val->cfg.sci1  || nv_val->cfg.sci0 ==nv_val->cfg.sci2 || nv_val->cfg.sci2 ==nv_val->cfg.sci1  ) 
        {
            sci_print("in three modem the cfg can not same\n");
            return BSP_ERROR;
        }
    }
    else if(MULTI_MODEM_NUMBER == 2)
    {
        if(nv_val->cfg.sci0 ==nv_val->cfg.sci1)
        {
            sci_print("in double modem the cfg can not same\n");
            return BSP_ERROR;
        }
    }

#endif

    if(sci_id == CARD_CONNECT_SCI2)
    {
       p_sci_cfg->sci_id = sci_id;      
       p_sci_cfg->card_id = card_id;
       return BSP_OK;
    }

    dev = of_find_compatible_node(NULL,NULL,name[sci_id]);
    if(NULL == dev)
    {
        sci_print_error("sci not find\n");
        return BSP_ERROR;
    }
    irq = (int)irq_of_parse_and_map(dev,0);
    sci_print_error("irq is 0x%x\n",irq);
    base_addr = of_iomap(dev,0);
    if(NULL == base_addr)
    {
        sci_print_error("sci base addr not find\n");
        return BSP_ERROR;
    }
    
    (void)of_property_read_u32_index(dev, "sci_ref_freq", 0,&sci_freq.sci_ref_freq);
    if(sci_freq.sci_ref_freq == 0)
    {
        sci_print_error("sci get ref freq fail\n");
        return BSP_ERROR;
    }

    (void)of_property_read_u32_index(dev, "sci_work_freq", 0,&sci_freq.sci_work_freq);
    if(sci_freq.sci_work_freq == 0)
    {
        sci_print_error("sci get work freq fail\n");
        return BSP_ERROR;
    }



    p_sci_cfg->card_id = card_id;

    
    if (CARD_CONNECT_SCI0 == sci_id) 
    {  
        /* regs base\ int \ clk */
        p_sci_cfg->base_addr  = (unsigned int)base_addr;
        p_sci_cfg->int_number = (u32)irq;
        p_sci_cfg->sci_id     = sci_id;
        p_sci_cfg->dma_chan   = EDMA_SCI0_RX;     

        p_sci_cfg->clk_en_bit  = SCI0_CLK_SET_BIT_SHIFT;
  
        p_sci_cfg->clk_dis_bit = SCI0_CLK_SET_BIT_SHIFT; 

        /* PMU */
        p_sci_cfg->pwr_type = CARD_PM_TYPE_SIM0;

        /*�쳣��¼��ص����ã�������¼���Ļ���ַ�Լ���¼�ļ�·��*/
        p_sci_cfg->record_enum= CARD0_EXCP_RECORD_ADDR_NUM;

        
        p_sci_cfg->icc_chnl     = ((ICC_CHN_IFC<< 16) | ac_channel[sci_id]);

        p_sci_cfg->record_file= (char *)g_pcCardRecordFileName[sci_id];

        /* task */
        p_sci_cfg->syncTaskName   = (char *)g_pcCardTaskName[sci_id];
        
        p_sci_cfg->hotPlugTaskName= (char *)g_pcCardHOTPLUGTaskName[sci_id];

        /*��0ͶƱ*/
        p_sci_cfg->sleep_vote = PWRCTRL_SLEEP_SCI0;

        /*��0ʱ��*/
        p_sci_cfg->clk        = (struct clk*)clk_get(NULL,"sci0_clk");
        p_sci_cfg->sci_freq.sci_work_freq= sci_freq.sci_work_freq;
        p_sci_cfg->sci_freq.sci_ref_freq = sci_freq.sci_ref_freq;
		p_sci_cfg->slot_switch_flag = SCI_SLOT_SWITCH_NONE;
        p_sci_cfg->sci_pmu = NULL;
        p_sci_cfg->sync_task_id = 0;       
        p_sci_cfg->hotplug_task_id = 0;       
        p_sci_cfg->sci_int_handler = NULL;
        memset_s(&(p_sci_cfg->sci_sem),sizeof(SCI_SEM_S),0,sizeof(SCI_SEM_S));
        
    }
    else if (CARD_CONNECT_SCI1 == sci_id) 
    {  

        /* regs base\ int \ clk */
        p_sci_cfg->base_addr  = (unsigned int)base_addr;
        p_sci_cfg->int_number = (u32)irq;
        p_sci_cfg->sci_id     = sci_id;
        p_sci_cfg->dma_chan   = EDMA_SCI1_RX;     

        p_sci_cfg->clk_en_bit  = SCI1_CLK_SET_BIT_SHIFT;
  
        p_sci_cfg->clk_dis_bit = SCI1_CLK_SET_BIT_SHIFT; 

        /* PMU */
        p_sci_cfg->pwr_type = CARD_PM_TYPE_SIM1;

        /*�쳣��¼��ص����ã�������¼���Ļ���ַ�Լ���¼�ļ�·��*/
        p_sci_cfg->record_enum= CARD1_EXCP_RECORD_ADDR_NUM;

        
        p_sci_cfg->icc_chnl     = ((ICC_CHN_IFC<< 16) | ac_channel[sci_id]);
        
        p_sci_cfg->record_file= (char *)g_pcCardRecordFileName[sci_id];

        /* task */
        p_sci_cfg->syncTaskName   = (char *)g_pcCardTaskName[sci_id];
        
        p_sci_cfg->hotPlugTaskName= (char *)g_pcCardHOTPLUGTaskName[sci_id];

        /*��0ͶƱ*/
        p_sci_cfg->sleep_vote = PWRCTRL_SLEEP_SCI1;


        /*��0ʱ��*/
        p_sci_cfg->clk        = (struct clk*)clk_get(NULL,"sci1_clk");
        p_sci_cfg->sci_freq.sci_work_freq= sci_freq.sci_work_freq;
        p_sci_cfg->sci_freq.sci_ref_freq = sci_freq.sci_ref_freq;
		p_sci_cfg->slot_switch_flag = SCI_SLOT_SWITCH_NONE;        
        p_sci_cfg->sci_pmu = NULL;
        p_sci_cfg->sync_task_id = 0;
        p_sci_cfg->hotplug_task_id = 0;       
        p_sci_cfg->sci_int_handler = NULL;
        memset_s(&(p_sci_cfg->sci_sem),sizeof(SCI_SEM_S),0,sizeof(SCI_SEM_S));

        
    }
    return BSP_OK;
}

/*****************************************************************************
 �� �� ��  : BSP_SCI_ParseNV
 ��������  : ����NV
 �������  : NV_SCI_CFG_UNION * nv
 �������  : ��
 �� �� ֵ  : int
 ���ú���  :
 ��������  : BSP_SCI_CfgInit

 �޸���ʷ      :

*****************************************************************************/
/*lint --e{525,830}*/

int bsp_sci_parse_nv(NV_SCI_CFG_UNION * nv)
{
    NV_SCI_CFG_UNION *p_nv_sci = nv;

    if (SCI_SINGLE == p_nv_sci->cfg.card_num) 
	{
        /*����0����*/
        if (p_nv_sci->cfg.sci0 <= CARD_CONNECT_SCI1) 
        {
            sci_print_debug("sci0 connect sci%d\r\n",p_nv_sci->cfg.sci0);
            if(BSP_OK != bsp_sci_cfg(CARD0, p_nv_sci->cfg.sci0))
            {
            	sci_print_error("cfg sci%d failed! \r\n",p_nv_sci->cfg.sci0);
				return BSP_ERROR;
			}
        }
        else 
		{
            /*�ݲ�֧�ֶ࿨*/
			sci_print_error("do not support multi card! case 1\n");
            return ERROR;
        }
    }
    else if(SCI_SINGLE_MODLEM1 == p_nv_sci->cfg.card_num)
    { /*����1����*/
        if (p_nv_sci->cfg.sci1 <= CARD_CONNECT_SCI1) 
        {
            sci_print_debug("SCI_SINGLE_MODLEM1  connect sci%d\r\n",p_nv_sci->cfg.sci1);
			if(BSP_OK != bsp_sci_cfg(CARD1, p_nv_sci->cfg.sci1))
            {
            	sci_print_error("cfg sci%d failed! \r\n",p_nv_sci->cfg.sci1);
				return BSP_ERROR;
			}
        }
        else 
		{
            /*�ݲ�֧�ֶ࿨*/
			sci_print_error("do not support multi card! case 2\n");
            return ERROR;
        }
    }
    else if (SCI_DUAL == p_nv_sci->cfg.card_num) 
    {
        /*˫������*/
        if ((p_nv_sci->cfg.sci0 <= CARD_CONNECT_SCI1) &&
            (p_nv_sci->cfg.sci1 <= CARD_CONNECT_SCI1) &&
            (p_nv_sci->cfg.sci0 != p_nv_sci->cfg.sci1)) 
        {
            sci_print_debug("dual cards, sci0 connect sci%d,sci1 connect sci%d\r\n",p_nv_sci->cfg.sci0, p_nv_sci->cfg.sci1);
			if(BSP_OK != bsp_sci_cfg(CARD0, p_nv_sci->cfg.sci0))
            {
            	sci_print_error("bsp_sci_parse_nv, total cfg sci%d failed! \r\n",p_nv_sci->cfg.sci0);
				return BSP_ERROR;
			}
			if(BSP_OK != bsp_sci_cfg(CARD1, p_nv_sci->cfg.sci1))
            {
            	sci_print_error(" total cfg sci%d failed! \r\n",p_nv_sci->cfg.sci1);
				return BSP_ERROR;
			}

        }
        else 
		{
            /*�ݲ�֧�ֶ࿨*/
			sci_print_error("do not support multi card! case 3\n");
            return BSP_ERROR;
        }
    }
    else if (SCI_THREE== p_nv_sci->cfg.card_num)
	{
        /*˫������*/
        if ((p_nv_sci->cfg.sci0 <= CARD_CONNECT_SCI2) 
            &&(p_nv_sci->cfg.sci1 <= CARD_CONNECT_SCI2) 
            &&(p_nv_sci->cfg.sci0 != p_nv_sci->cfg.sci1)) 
        {
            sci_print_debug("dual cards, sci0 connect sci%d,sci1 connect sci%d\r\n",p_nv_sci->cfg.sci0, p_nv_sci->cfg.sci1);
			if(BSP_OK != bsp_sci_cfg(CARD0, p_nv_sci->cfg.sci0))
            {
            	sci_print_error("bsp_sci_parse_nv, total cfg sci%d failed! \r\n",p_nv_sci->cfg.sci0);
				return BSP_ERROR;
			}
			if(BSP_OK != bsp_sci_cfg(CARD1, p_nv_sci->cfg.sci1))
            {
            	sci_print_error(" total cfg sci%d failed! \r\n",p_nv_sci->cfg.sci1);
				return BSP_ERROR;
			}
            if(BSP_OK != bsp_sci_cfg(CARD2, p_nv_sci->cfg.sci2))
            {
            	sci_print_error(" total cfg sci%d failed! \r\n",p_nv_sci->cfg.sci1);
				return BSP_ERROR;
			}
        }
        else 
		{
            /*�ݲ�֧�ֶ࿨*/
			sci_print_error("do not support multi card! case 3\n");
            return BSP_ERROR;
        }

    }
    else
    {
         /*�ݲ�֧�ֳ���3�ſ�*/
		sci_print_error(" do not support more than 3 card! case 5\n");
        return BSP_ERROR;
    }

    return BSP_OK;
}
/*lint --e{525,830}*/


/*****************************************************************************
 �� �� ��  : BSP_SCI_CfgInit
 ��������  : SCI�ܵĳ�ʼ����������ʼ���׶ν���Ӳ�����ã���������Ҫ������ص�
             SCI������ʼ��
 �������  : void
 �������  : ��
 �� �� ֵ  : int
 ���ú���  :
 ��������  : BSP_DRV_Init

 �޸���ʷ      :
  1.��    ��   : 2013��1��11��
    ��    ��   : ��ӭ�� 61362
    �޸�����   : �����ɺ���

*****************************************************************************/
int bsp_sci_cfg_init(void)
{
    unsigned int i = 0;
    unsigned int init_func_num;
    /* coverity[assign] */
    int *p_init_start = (int *)&_sci_init_data_start;
    int call_addr;
    NV_SCI_CFG_UNION nv_sci;
    SCI_INIT_FUNCP p_func_sci_init;
    int card_type = 0;
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    /*��ȡNV_SCI��ֵ*/
    (void)bsp_sci_get_nv(&nv_sci.value);
#else
    nv_sci.value = g_SciNVValue;
#endif
    /*����NV_SCI*/
    if (BSP_ERROR == bsp_sci_parse_nv(&nv_sci)) 
	{
		sci_print_error("parse nv failed!\n");
        return BSP_ERROR;
    }
    init_func_num = &_sci_init_data_end - &_sci_init_data_start;

    card_type = ((NV_SCI_CFG_UNION *)&g_SciNVValue)->cfg.card_num; 
    if(SCI_SINGLE == card_type)
    {
        init_func_num= 1;
    }
    else if (SCI_SINGLE_MODLEM1 == card_type)
    {
         init_func_num= 1;
         /* coverity[ptr_arith] */
         p_init_start++;
    }
    
    sci_print_debug("init_func_num %d  start_add_opp 0x%0x\r\n", init_func_num,(p_init_start-(int*)&_sci_init_data_start));
        
    /*����SCI�ĳ�ʼ��*/
    for (i = 0; i < init_func_num; i++) 
	{
        call_addr = *(volatile int *)p_init_start;
        p_func_sci_init = (SCI_INIT_FUNCP)call_addr;
        sci_print_debug("call init function of card%d, address is 0x%x\r\n",i, call_addr);
        p_func_sci_init();
        /* coverity[ptr_arith] */
        p_init_start++;
    }

    return BSP_OK;
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


