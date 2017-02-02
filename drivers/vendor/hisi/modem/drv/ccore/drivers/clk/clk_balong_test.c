
#include <osl_list.h>
#include <clk_balong_core.h>

extern struct list_head balong_clocks ;
extern struct hlist_head  clk_balong_root_list;


static int clk_strcmp(const char *cs, const char *ct)
{
	char c1, c2;

	while (1) {			/*lint !e716*/
		c1 = *cs++;
		c2 = *ct++;
		if (c1 != c2)
			return c1 < c2 ? -1 : 1;
		if (!c1)
			break;
	}
	return 0;
}


/* ����ʱ������
   ����ӵ�dts�ļ����ʱ�ӣ�
   ����ȷ�ĳ�ʼ��������ӵ������У������ӡ��
   ʱ�������������ź�ʱ�ӵ����֣����������
   ����ӵ�ʱ�����֣���ʾ���Գɹ�
*/
void clk_system_test_001(void)
{
    struct clk_lookup     *ptr_clk_lookup = NULL;

	clk_printf("clk cfg test-------------------------------starting\n");

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node) 
	{
        clk_printf("in list no = %d name = %s\n", ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id);
		clk_printf("\n\n");
	}

	clk_printf("clk cfg test-------------------------------end\n");

    return ;
}


/*
   ���Ի�ȡʱ��
   ������������ÿһ��ʱ�����֣�����clk_get�������ط�NULL���������Գɹ�
   
*/
void clk_system_test_002(void)
{
    struct clk_lookup     *ptr_clk_lookup = NULL;
	struct clk            *ptr_clk = NULL;

	clk_printf("clk get test-------------------------------starting\n");


	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node) 
	{
        ptr_clk = clk_get(NULL, ptr_clk_lookup->con_id);
		if (NULL == ptr_clk)
		{
		    clk_printf("in list no = %d clk name = %s clk_get test ---------------- fail\n", 
				ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id);
			clk_printf("\n\n");
			continue ;
		}
		else
		{
		    clk_printf("in list no = %d clk name = %s clk_get test ok\n", 
				ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id);
			clk_printf("\n\n");
		}
	}

	
	clk_printf("clk get test-------------------------------end\n");

    return ;
}

/*
  ��ȡʱ�ӵĴ򿪹ر�״̬
*/
void clk_system_test_003()
{
    struct clk_lookup     *ptr_clk_lookup = NULL;
	struct clk            *ptr_clk = NULL;
	bool                  is_enabled = false;
	int                   ret = -1;


	clk_printf("clk is_enabled test-------------------------------starting\n");


	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node) 
	{
        ptr_clk = clk_get(NULL, ptr_clk_lookup->con_id);
		if (NULL == ptr_clk)
		{
		    clk_printf("in list no = %d clk name = %s clk_get  ---------------- fail\n", 
				ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id);
			clk_printf("\n\n");
			continue ;
		}

		is_enabled = clk_is_enabled(ptr_clk);
		if (false == is_enabled) /* �رյ� */
		{
		    ret = clk_enable(ptr_clk);
			if (ret)
			{
			    clk_printf("no = %d name = %s init disabled but enable err\n", ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id);
				clk_printf("\n\n");
				continue ; /* ������һʱ�� */
			}
			else
			{
				is_enabled = clk_is_enabled(ptr_clk);
				if (false == is_enabled)
				{
			        clk_printf("no = %d name = %s init disabled  call enable ok but it is still disabled\n", 
						ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id);
					clk_printf("\n\n");
					continue;
				}
				else
				{
			        clk_printf("no = %d name = %s init disabled  call enable ok and it is now enabled\n", 
						ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id);
					clk_printf("\n\n");
				}
			}
			
		}
		else  /* ʱ���Ǵ򿪵� */
		{
		    clk_disable(ptr_clk);
			is_enabled = clk_is_enabled(ptr_clk);
			if (false != is_enabled)
			{
		        clk_printf("no = %d name = %s init enabled  call disable ok but it is still enabled\n", 
					ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id);
				clk_printf("\n\n");
				continue;
			}
			else
			{
		        clk_printf("no = %d name = %s init enabled  call disable ok and it is now disabled\n", 
					ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id);
				clk_printf("\n\n");
			}
			
		}
	}


	clk_printf("clk is_enabled test-------------------------------end\n");

    return ;
}

/*
  ���Դ�ʱ��
  ��������Ҷ�ӽڵ�
*/
void clk_system_test_004()
{
    struct clk_lookup     *ptr_clk_lookup = NULL;
	struct clk            *ptr_clk = NULL;
	bool                  is_enabled = false;
	int                   ret = -1;

	clk_printf("clk enable test-------------------------------starting\n");

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node) 
	{
	    clk_printf("in list no = %d clk name = %s enable test----------- starting\n", 
			ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id);
		if (1 != ptr_clk_lookup->clk->leaf_flag)
		{
		    clk_printf("not leaf clk continue with the next clk\n");
			clk_printf("\n\n");
			continue;
		}
        ptr_clk = clk_get(NULL, ptr_clk_lookup->con_id);
		if (NULL == ptr_clk)
		{
		    clk_printf("in list no = %d clk name = %s clk_get  ---------------- fail\n", 
				ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id);
			clk_printf("\n\n");
			continue ;  /* ������һʱ�� */
		}

		ret = clk_enable(ptr_clk);
		if (ret)
		{
		    clk_printf("in list no = %d clk name = %s clk_enable  ---------------- fail\n", 
				ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id);
			clk_printf("\n\n");
			continue ;  /* ������һʱ�� */
		}

		is_enabled = clk_is_enabled(ptr_clk);
		if (false == is_enabled)
		{
		    clk_printf("in list no = %d clk name = %s clk should be enabled but now it is disabled---------------- fail\n", 
				ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id);
			clk_printf("\n\n");
			continue ;
		}

	    clk_printf("in list no = %d clk name = %s enable test----------- ok\n", 
			ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id);
		clk_printf("\n\n");

		
	}

	clk_printf("clk enable test-------------------------------end\n");

    return ;
}



/*
  ���Թر�ʱ��
  ע��:������uart��ص�ʱ�ӣ���Ϊ�ر���Щʱ�ӿ��ܵ��´��ڲ��ܴ�ӡ
*/
void clk_system_test_005()
{
    struct clk_lookup     *ptr_clk_lookup = NULL;
	struct clk            *ptr_clk = NULL;
	bool                  is_enabled = false;

	clk_printf("clk disable test-------------------------------starting\n");


	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node) 
	{
	    clk_printf("in list no = %d clk name = %s disable test----------- starting\n", 
			ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id);
        if ((0 == clk_strcmp((const char *)ptr_clk_lookup->con_id, "uart0_clk")) ||
			(0 == clk_strcmp((const char *)ptr_clk_lookup->con_id, "uart1_clk")) ||
			(0 == clk_strcmp((const char *)ptr_clk_lookup->con_id, "uart2_clk")) ||
			(0 == clk_strcmp((const char *)ptr_clk_lookup->con_id, "uart3_clk"))
		    )
    	{
    	    clk_printf("uart relative clk continue with the next\n");
			clk_printf("\n\n");
			continue ; /* ������һʱ�� */
    	}

		if (1 != ptr_clk_lookup->clk->leaf_flag)
		{
		    clk_printf("not leaf clk continue with the next clk\n");
			clk_printf("\n\n");
			continue;
		}
		
        ptr_clk = clk_get(NULL, ptr_clk_lookup->con_id);
		if (NULL == ptr_clk)
		{
		    clk_printf("in list no = %d clk name = %s clk_get  ---------------- fail\n", 
				ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id);
			clk_printf("\n\n");
			continue ;  /* ������һʱ�� */
		}

		clk_disable(ptr_clk);

		is_enabled = clk_is_enabled(ptr_clk);
		if (true == is_enabled)
		{
		    clk_printf("in list no = %d clk name = %s clk should be disabled but now it is enabled---------------- fail\n", 
				ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id);
			clk_printf("\n\n");
			continue ;
		}

	    clk_printf("in list no = %d clk name = %s disable test----------- ok\n", 
			ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id);
		clk_printf("\n\n");

		
	}

	clk_printf("clk disable test-------------------------------end\n");


    return ;
}


/*
  ���Դ�ʱ���Զ��ſ�
*/
void clk_system_test_006(void)
{
    struct clk_lookup     *ptr_clk_lookup = NULL;
    int                   ret = -1;

	clk_printf("clk enable auto gating test-------------------------------starting\n");
	
	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node) 
	{
	    if (1 == ptr_clk_lookup->clk->leaf_flag)
    	{
    	     ret = clk_enable_auto_gating(ptr_clk_lookup->clk);
			 if (ret)
		 	 {
		 	    clk_printf("no=%d name=%s enable_auto_gating err\n", ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id);
                clk_printf("\n\n");
				continue ;
		 	 }
			 else
		 	{
		 	    clk_printf("no=%d name=%s enable_auto_gating ok\n", ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id);
                clk_printf("\n\n");
		 	}
			 
			 	
    	}
	}

	clk_printf("clk enable auto gating test-------------------------------end\n");
	
    return ;
}


/*
  ���Թر�ʱ���Զ��ſ�
*/
void clk_system_test_007(void)
{
    struct clk_lookup     *ptr_clk_lookup = NULL;
    int                   ret = -1;


	clk_printf("clk disable auto gating test-------------------------------starting\n");
	
	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node) 
	{
	    if (1 == ptr_clk_lookup->clk->leaf_flag)
    	{
    	     ret = clk_disable_auto_gating(ptr_clk_lookup->clk);
			 if (ret)
		 	 {
		 	    clk_printf("no=%d name=%s disable_auto_gating err\n", ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id);
                clk_printf("\n\n");
				continue ;
		 	 }
			 else
		 	{
		 	    clk_printf("no=%d name=%s disable_auto_gating ok\n", ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id);
                clk_printf("\n\n");
		 	}
			 
			 	
    	}
	}

	clk_printf("clk disable auto gating test-------------------------------end\n");
    return ;
}

/* 
  ��������ʱ��Ƶ�� 
*/
#define TEST_CCLK_V711

#ifdef TEST_CCLK_V711
unsigned int g_sci0_div_reg_addr = 0x90000110;
unsigned int g_sci0_div_mask = 0x00000700;
unsigned int g_sci0_div_start_bit = 8;

unsigned int g_sci1_div_reg_addr = 0x90000110;
unsigned int g_sci1_div_mask = 0x00007000;
unsigned int g_sci1_div_start_bit = 12;

unsigned int g_cipher_div_reg_addr = 0x90000108;
unsigned int g_cipher_div_mask = 0xf0000000;
unsigned int g_cipher_div_start_bit = 28;


#elif defined(TEST_CCLK_P532)
unsigned int g_sci0_div_reg_addr = 0x90000100;
unsigned int g_sci0_div_mask = 0x00000700;
unsigned int g_sci0_div_start_bit = 8;

unsigned int g_sci1_div_reg_addr = 0x90000100;
unsigned int g_sci1_div_mask = 0x00007000;
unsigned int g_sci1_div_start_bit = 12;

unsigned int g_cipher_div_reg_addr = 0x9001B108;
unsigned int g_cipher_div_mask = 0xf0000000;
unsigned int g_cipher_div_start_bit = 28;

#elif defined(TEST_CCLK_V7R5)

#endif



void clk_system_test_008(void)
{
    struct clk  *ptr_clk = NULL;
    int          div_val = 0;  /* ��Ƶֵ */
	int          ret = -1;
	unsigned int reg_ini_val = 0; /* �����ļĴ�����ԭʼֵ */  
	unsigned int reg_bits_val = 0;  /* ���λ��ֵ */

	clk_printf("clk set rate test-------------------------------starting\n");

	/* ����sci0_clk��P532�ϣ�120M ������Ƶ��(0x90000100[10:8])�õ� */
	/* ����ÿһ����Ƶֵ */
	ptr_clk = clk_get(NULL, "sci0_clk");
	if (!ptr_clk)
	{
	    clk_printf("sci0_clk clk_get err\n");
		return ;
	}

	
	for (div_val = 2; div_val <= 7; div_val++)
	{
	    clk_printf("sci0_clk clk_set_rate to %d starting...\n", 120000000/div_val);
	    ret = clk_set_rate(ptr_clk, (unsigned long)(120000000/div_val));
		if (ret)
		{
		    clk_printf("clk_set_rate err div_val = %d\n", div_val);
			continue ;
		}

        reg_ini_val = readl(g_sci0_div_reg_addr);
		clk_printf("reg_ini_val = 0x%08x\n", reg_ini_val);
		reg_bits_val = ((reg_ini_val & g_sci0_div_mask) >> g_sci0_div_start_bit);
		if (div_val != reg_bits_val)
		{
		    clk_printf("clk_set_rate %d err div_val = %d reg_bits_val = %d\n", 
				       120000000/div_val, div_val, reg_bits_val);
			continue ;
		}
		
	    clk_printf("clk_set_rate %d ok div_val = %d reg_bits_val = %d\n", 
			       120000000/div_val, div_val, reg_bits_val);
	}
	
	/* ����sci1_clk��P532�ϣ�120M ������Ƶ��(0x90000100[15:12])�õ� */
	/* ����ÿһ����Ƶֵ */
	ptr_clk = clk_get(NULL, "sci1_clk");
	if (!ptr_clk)
	{
	    clk_printf("sci1_clk clk_get err\n");
		return ;
	}

	
	for (div_val = 2; div_val <= 7; div_val++)
	{
	    clk_printf("sci1_clk clk_set_rate to %d starting...\n", 120000000/div_val);
	    ret = clk_set_rate(ptr_clk, (unsigned long)(120000000/div_val));
		if (ret)
		{
		    clk_printf("clk_set_rate err div_val = %d\n", div_val);
			continue ;
		}

        reg_ini_val = readl(g_sci1_div_reg_addr);
		clk_printf("reg_ini_val = 0x%08x\n", reg_ini_val);
		reg_bits_val = ((reg_ini_val & g_sci1_div_mask) >> g_sci1_div_start_bit);
		if (div_val != reg_bits_val)
		{
		    clk_printf("clk_set_rate %d err div_val = %d reg_bits_val = %d\n", 
				       120000000/div_val, div_val, reg_bits_val);
			continue ;
		}
		
	    clk_printf("clk_set_rate %d ok div_val = %d reg_bits_val = %d\n", 
			       120000000/div_val, div_val, reg_bits_val);
	}

    /* ����cipher_clk��P532�ϣ�960M ������Ƶ��(0x9001B108[31:28])�õ� */
	/* ����ÿһ����Ƶֵ */
	ptr_clk = clk_get(NULL, "cipher_clk");
	if (!ptr_clk)
	{
	    clk_printf("cipher_clk clk_get err\n");
		return ;
	}

	
	for (div_val = 1; div_val <= 15; div_val++)
	{
	    clk_printf("cipher_clk clk_set_rate to %d starting...\n", 960000000/div_val);
	    ret = clk_set_rate(ptr_clk, (unsigned long)(960000000/div_val));
		if (ret)
		{
		    clk_printf("clk_set_rate err div_val = %d\n", div_val);
			continue ;
		}

        reg_ini_val = readl(g_cipher_div_reg_addr);
		clk_printf("reg_ini_val = 0x%08x\n", reg_ini_val);
		reg_bits_val = ((reg_ini_val & g_cipher_div_mask) >> g_cipher_div_start_bit);
		if (div_val != reg_bits_val)
		{
		    clk_printf("clk_set_rate %d err div_val = %d reg_bits_val = %d\n", 
				       960000000/div_val, div_val, reg_bits_val);
			continue ;
		}
		
	    clk_printf("clk_set_rate %d ok div_val = %d reg_bits_val = %d\n", 
			       960000000/div_val, div_val, reg_bits_val);
	}

	
	clk_printf("clk set rate test-------------------------------end\n");

    return ;
}

/* 
  �������ø�ʱ�� 
  �������������ʱ�ӣ�����丸ʱ�������������ϣ��������ø�ʱ��
*/
void clk_system_test_009(void)
{
    struct clk_lookup     *ptr_clk_lookup = NULL;
	int                   parents_sum = 0; /* ��ʱ������ */
	struct clk            *ptr_clk = NULL;
	struct clk            *ptr_parent_clk = NULL;
	int                   ret = -1;
	int                   i = 0;

	clk_printf("clk set parent test-------------------------------starting\n");

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node)
	{
		parents_sum = ptr_clk_lookup->clk->num_parents;

	    if (2 > parents_sum)
    	{
    	    continue ; /* ֻ��һ������û�и�ʱ�ӣ�������һʱ�� */
    	}

		/* ���������������ϸ�ʱ�� */
		for (i = 0; i < parents_sum; i++)
		{
		    ptr_clk = ptr_clk_lookup->clk;
			ptr_parent_clk = ptr_clk_lookup->clk->parents[i];
		    ret = clk_set_parent(ptr_clk, ptr_parent_clk);
			if (ret)
			{
			    clk_printf("no = %d name = %s set to parent %s err\n", 
					       ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id, ptr_parent_clk->name);
				continue ; /* ��ʱ�Ӽ���������һ����ʱ�� */
			}

			/* ���óɹ� */
		    clk_printf("no = %d name = %s set to parent %s ok\n", 
				       ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id, ptr_parent_clk->name);
		}
	}

	clk_printf("clk set parent test-------------------------------end\n");
    return ;
}

/* 
  ��ʾʱ����Ϣ
*/
void clk_system_test_010(void)
{
    struct clk_lookup     *ptr_clk_lookup = NULL;
    struct clk_lookup     *ptr_clk_lookup_search_parent = NULL;
    struct clk            *ptr_clk = NULL;
	char                  *clk_name = NULL;
	struct clk            *ptr_parent_clk = NULL;

	clk_printf("clk show info test-------------------------------starting\n");

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node) 
	{
	    if (1 != ptr_clk_lookup->clk->leaf_flag)
    	{
    	    continue ; /* ��Ҷ�ӽڵ㣬������һʱ�� */
    	}
		
		ptr_clk = clk_get(NULL, ptr_clk_lookup->con_id);
		if (NULL == ptr_clk)
		{
		    clk_printf("clk_get %s err\n", clk_name);
			continue ;
		}

		clk_printf("clk no=%d name=%s rate=%d is_virtual=%d aux_flag=%d enable_count=%d\n",
			       ptr_clk_lookup->clk_no, ptr_clk->name, ptr_clk->rate,
			       ptr_clk->is_virtual_clk, ptr_clk->aux_flag, ptr_clk->enable_count);			

	    while ((ptr_parent_clk = clk_get_parent(ptr_clk)))
		{
            /* ���������ҵ���ʱ�ӵı�� */
			list_for_each_entry(ptr_clk_lookup_search_parent, &balong_clocks, node)
        	{
        	    if (ptr_parent_clk == ptr_clk_lookup_search_parent->clk)
    	    	{
    	    	    break;
    	    	}
        	}
		
		    clk_printf("clk no=%d name=%s rate=%d is_virtual=%d aux_flag=%d enable_count=%d\n",
				       ptr_clk_lookup_search_parent->clk_no, ptr_parent_clk->name, ptr_parent_clk->rate,
				       ptr_parent_clk->is_virtual_clk, ptr_parent_clk->aux_flag, ptr_parent_clk->enable_count);			
			ptr_clk = ptr_parent_clk;
		}

	    clk_printf("\n\n\n");


	}

	
	clk_printf("clk show info test-------------------------------end\n");

    return ;
}

/* 
  ���Ե͹��Ĵ���
*/
void clk_system_test_011(void)
{



    return ;
}

/* 
  ���Կ�ά�ɲ�
*/
void clk_system_test_012(void)
{



    return ;
}



