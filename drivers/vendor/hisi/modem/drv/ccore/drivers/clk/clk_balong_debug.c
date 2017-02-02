

/*lint --e{530,525,628,666,801,830,144,413} */

#include <osl_list.h>
#include <bsp_om.h>
#include <clk_balong_core.h>

extern struct list_head balong_clocks ;
extern struct hlist_head  clk_balong_root_list;

void clk_debug_get(const char* clk_name)
{
    struct clk *ptr_clk = NULL;

    ptr_clk = clk_get(NULL, clk_name);
	if (IS_ERR(ptr_clk))
	{
		clk_printf("clk_get %s err\n", clk_name);
		return ;
	}

	clk_printf("clk_get %s ok\n", clk_name);

    return ;
}
void clk_debug_show_reg(unsigned int reg_addr)
{
    unsigned int reg_val = 0;

	reg_val = readl(reg_addr);
	clk_printf("addr 0x%08x = 0x%08x\n", reg_addr, reg_val);

    return ;
}


void clk_debug_show_clks_in_root_hlist(void)
{
	struct clk *ptr_clk = NULL;
	static unsigned int   u32_cnt_in_root_hlist = 0;

	/*lint -save -e160 -e40 */
	/* search the 'proper' clk tree first */
	hlist_for_each_entry(ptr_clk, &clk_balong_root_list, child_node) 
	{
        clk_printf("in root hlist no = %d name = %s\n", u32_cnt_in_root_hlist, ptr_clk->name);
		u32_cnt_in_root_hlist++;	
	}
    /*lint -restore +e160 +e40 */

    return ;
}

void clk_debug_show_clks_in_list(void)
{
    struct clk_lookup     *ptr_clk_lookup;

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node) 
	{
        clk_printf("in list no = %d name = %s\n", ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id);
	}

    return ;
}

void clk_debug_show_all_clks_rate(void)
{
    struct clk_lookup     *ptr_clk_lookup;

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node) 
	{
        clk_printf("in list no=%d name=%s rate=%d\n", ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id, 
			                                          ptr_clk_lookup->clk->rate);
	}

    return ;
}




void clk_debug_enable_clk(unsigned int clk_no_in_list)
{
    struct clk_lookup     *ptr_clk_lookup = NULL;
    struct clk  *ptr_clk = NULL;
	char *clk_name = NULL;


	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node) 
	{
	    if (clk_no_in_list == ptr_clk_lookup->clk_no)
    	{
    	    clk_name = clk_alloc_copy(ptr_clk_lookup->con_id);
			ptr_clk = clk_get(NULL, clk_name);
			if (NULL == ptr_clk)
			{
			    clk_printf("clk_get %s err\n", clk_name);
				return ;
			}

		    clk_printf("clk_get %s ok\n", clk_name);

			(void)clk_enable(ptr_clk);

		    clk_printf("clk_enable ok\n");

    	}
	}

	


    return ;
}




/*lint -save -e144 -e413 */
void clk_debug_disable_clk(unsigned int clk_no_in_list)
{
    struct clk_lookup     *ptr_clk_lookup = NULL;
    struct clk            *ptr_clk = NULL;
	char                  *clk_name = NULL;


	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node) 
	{
	    if (clk_no_in_list == ptr_clk_lookup->clk_no)
    	{
    	    clk_name = clk_alloc_copy(ptr_clk_lookup->con_id);
			ptr_clk = clk_get(NULL, clk_name);
			if (NULL == ptr_clk)
			{
			    clk_printf("clk_get %s err\n", clk_name);
				return ;
			}

		    clk_printf("clk_get %s ok\n", clk_name);

			clk_disable(ptr_clk);

		    clk_printf("clk_disable end\n");

    	}
	}

    return ;
}
/*lint -restore +e144 +e413 */


void clk_debug_is_enabled(unsigned int clk_no_in_list)
{
    struct clk_lookup     *ptr_clk_lookup = NULL;
    struct clk  *ptr_clk = NULL;
	char *clk_name = NULL;
	int ret = -1;


	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node) 
	{
	    if (clk_no_in_list == ptr_clk_lookup->clk_no)
    	{
    	    clk_name = clk_alloc_copy(ptr_clk_lookup->con_id);
			ptr_clk = clk_get(NULL, clk_name);
			if (NULL == ptr_clk)
			{
			    clk_printf("clk_get %s err\n", clk_name);
				return ;
			}

		    clk_printf("clk_get %s ok\n", clk_name);

			ret = clk_is_enabled(ptr_clk);
			if (false == ret)
			{
			    clk_printf("%s is disabled\n", clk_name);
			}
			else
			{
			    clk_printf("%s is enabled\n", clk_name);
			}
				
    	}
	}

    return ;
}










void clk_debug_set_rate(unsigned int clk_no_in_list, unsigned long req_rate)
{
    struct clk_lookup     *ptr_clk_lookup = NULL;
    struct clk  *ptr_clk = NULL;
	char *clk_name = NULL;
	int ret = -1;


	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node) 
	{
	    if (clk_no_in_list == ptr_clk_lookup->clk_no)
    	{
    	    clk_name = clk_alloc_copy(ptr_clk_lookup->con_id);
			ptr_clk = clk_get(NULL, clk_name);
			if (NULL == ptr_clk)
			{
			    clk_printf("clk_get %s err\n", clk_name);
				return ;
			}

		    clk_printf("clk_get %s ok\n", clk_name);

			ret = clk_set_rate(ptr_clk, req_rate);
			if (ret)
			{
			    clk_printf("%s set rate to %d err ret = %d\n", clk_name, req_rate, ret);
			}
			else
			{
			    clk_printf("%s set rate to %d ok\n", clk_name, req_rate);
			}
			
				
    	}
	}

    return ;
}




void clk_debug_get_rate(unsigned int clk_no_in_list)
{
    struct clk_lookup     *ptr_clk_lookup = NULL;
    struct clk  *ptr_clk = NULL;
	char *clk_name = NULL;
	unsigned long rate_get = 0;


	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node) 
	{
	    if (clk_no_in_list == ptr_clk_lookup->clk_no)
    	{
    	    clk_name = clk_alloc_copy(ptr_clk_lookup->con_id);
			ptr_clk = clk_get(NULL, clk_name);
			if (NULL == ptr_clk)
			{
			    clk_printf("clk_get %s err\n", clk_name);
				return ;
			}

		    clk_printf("clk_get %s ok\n", clk_name);

			rate_get = clk_get_rate(ptr_clk);
            clk_printf("get rate = %d\n", rate_get);
			
				
    	}
	}

    return ;
}





void clk_debug_set_parent(unsigned int clk_no_in_list, unsigned int parent_clk_no_in_list)
{
    struct clk_lookup     *ptr_clk_lookup = NULL;
    struct clk            *ptr_clk = NULL;
	struct clk            *ptr_parent_clk = NULL;
	char                  *clk_name = NULL;
	char                  *parent_clk_name = NULL;
	int                   ret = -1;


	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node) 
	{
	    if (clk_no_in_list == ptr_clk_lookup->clk_no)
    	{
    	    clk_name = clk_alloc_copy(ptr_clk_lookup->con_id);
			ptr_clk = clk_get(NULL, clk_name);
			if (NULL == ptr_clk)
			{
			    clk_printf("clk_get %s err\n", clk_name);
				return ;
			}

		    clk_printf("clk_get %s ok\n", clk_name);
    	}

	    if (parent_clk_no_in_list == ptr_clk_lookup->clk_no)
        {
    	    parent_clk_name = clk_alloc_copy(ptr_clk_lookup->con_id);
			ptr_parent_clk = clk_get(NULL, parent_clk_name);
			if (NULL == ptr_parent_clk)
			{
			    clk_printf("clk_get parent %s err\n", parent_clk_name);
				return ;
			}

		    clk_printf("clk_get parent %s ok\n", parent_clk_name);
    	}	
	}

	ret = clk_set_parent(ptr_clk, ptr_parent_clk);
	if (ret)
	{
	    clk_printf("%s set parent to %s err ret=%d\n", clk_name, parent_clk_name, ret);
		return ;
	}
	else
	{
	    clk_printf("%s set parent to %s ok\n", clk_name, parent_clk_name);
	}

    return ;
}

void clk_debug_get_parent(unsigned int clk_no_in_list)
{
    struct clk_lookup     *ptr_clk_lookup = NULL;
    struct clk            *ptr_clk = NULL;
	char                  *clk_name = NULL;
	struct clk            *ptr_parent_clk = NULL;

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node) 
	{
	    if (clk_no_in_list == ptr_clk_lookup->clk_no)
    	{
    	    clk_name = clk_alloc_copy(ptr_clk_lookup->con_id);
			ptr_clk = clk_get(NULL, clk_name);
			if (NULL == ptr_clk)
			{
			    clk_printf("clk_get %s err\n", clk_name);
				return ;
			}

		    clk_printf("clk_get %s ok\n", clk_name);
    	}
	}

	if (NULL == ptr_clk)
	{
		clk_printf("search clk err\n");
		return ;
	}

	ptr_parent_clk = clk_get_parent(ptr_clk);
	if (IS_ERR(ptr_parent_clk))
	{
	    /*lint -save -e613*/  
        clk_printf("get %s parent err\n", ptr_clk->name);
	    /*lint -restore +e613*/  
		return ;
	}
	else
	{
	    /*lint -save -e613*/  
        clk_printf("get %s parent %s ok\n", ptr_clk->name, ptr_parent_clk->name); 
        /*lint -restore +e613*/
	}


    return ;
}

void clk_debug_show_clk_parents(unsigned int clk_no_in_list)
{
    struct clk_lookup     *ptr_clk_lookup = NULL;
    struct clk            *ptr_clk = NULL;
	char                  *clk_name = NULL;
	struct clk            *ptr_parent_clk = NULL;

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node) 
	{
	    if (clk_no_in_list == ptr_clk_lookup->clk_no)
    	{
    	    clk_name = clk_alloc_copy(ptr_clk_lookup->con_id);
			ptr_clk = clk_get(NULL, clk_name);
			if (NULL == ptr_clk)
			{
			    clk_printf("clk_get %s err\n", clk_name);
				return ;
			}

		    //clk_printf("clk_get %s ok\n", clk_name);
    	}
	}

	if (NULL == ptr_clk)
	{
		clk_printf("search clk err\n");
		return ;
	}

    /*lint -save -e613*/
    clk_printf(" %s  \n", ptr_clk->name);  
    /*lint -restore +e613*/

    while ((ptr_parent_clk = clk_get_parent(ptr_clk)))
	{
	    clk_printf(" %s  \n", ptr_parent_clk->name);
		ptr_clk = ptr_parent_clk;
	}

	
    return ;
}

void clk_debug_show_clks_enable_count(void)
{
    struct clk_lookup     *ptr_clk_lookup;

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node) 
	{
        clk_printf("in list no=%d name=%s enable_count=%d\n", 
			ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id, ptr_clk_lookup->clk->enable_count);
	}

    return ;
}

void clk_debug_show_clk_info(unsigned int clk_no_in_list)
{
    struct clk_lookup     *ptr_clk_lookup = NULL;
    struct clk  *ptr_clk = NULL;
	char *clk_name = NULL;


	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node) 
	{
	    if (clk_no_in_list == ptr_clk_lookup->clk_no)
    	{
    	    clk_name = clk_alloc_copy(ptr_clk_lookup->con_id);
			ptr_clk = clk_get(NULL, clk_name);
			if (NULL == ptr_clk)
			{
			    clk_printf("clk_get %s err\n", clk_name);
				return ;
			}

		    clk_printf("clk_get %s ok\n", clk_name);

            clk_printf("clk no=%d name=%s rate=%d is_virtual=%d aux_flag=%d enable_count=%d",
				       clk_no_in_list, ptr_clk->name, ptr_clk->rate,
				       ptr_clk->is_virtual_clk, ptr_clk->aux_flag, ptr_clk->enable_count);			
				
    	}
	}

    return ;
}

void clk_debug_show_clk_from_leaf_info(unsigned int leaf_clk_no_in_list)
{
    struct clk_lookup     *ptr_clk_lookup = NULL;
    struct clk            *ptr_clk = NULL;
	char                  *clk_name = NULL;
	struct clk            *ptr_parent_clk = NULL;

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node) 
	{
	    if (leaf_clk_no_in_list == ptr_clk_lookup->clk_no)
    	{
    	    clk_name = clk_alloc_copy(ptr_clk_lookup->con_id);
			ptr_clk = clk_get(NULL, clk_name);
			if (NULL == ptr_clk)
			{
			    clk_printf("clk_get %s err\n", clk_name);
				return ;
			}

    	}
	}

	if (NULL == ptr_clk)
	{
		clk_printf("search clk err\n");
		return ;
	}

    /*lint -save -e613*/
    clk_printf("clk name=%s rate=%d is_virtual=%d aux_flag=%d enable_count=%d\n",  
		       ptr_clk->name, ptr_clk->rate,                                       
		       ptr_clk->is_virtual_clk, ptr_clk->aux_flag, ptr_clk->enable_count); 	
    /*lint -restore +e613*/
    while ((ptr_parent_clk = clk_get_parent(ptr_clk)))
	{
	    clk_printf("clk name=%s rate=%d is_virtual=%d aux_flag=%d enable_count=%d\n",
			       ptr_parent_clk->name, ptr_parent_clk->rate,
			       ptr_parent_clk->is_virtual_clk, ptr_parent_clk->aux_flag, ptr_parent_clk->enable_count);			
		ptr_clk = ptr_parent_clk;
	}

	
    return ;
}

void clk_debug_show_children(unsigned int clk_no_in_list)
{
    struct clk_lookup     *ptr_clk_lookup = NULL;
    struct clk_lookup     *ptr_clk_lookup_2nd_time = NULL;
	struct clk            *ptr_parent_clk = NULL;
	struct clk            *ptr_child_clk = NULL;
	
	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node) 
	{
	    if (clk_no_in_list == ptr_clk_lookup->clk_no)
    	{
    	    ptr_parent_clk = ptr_clk_lookup->clk;
    	
			/* 遍历链表 */
			list_for_each_entry(ptr_clk_lookup_2nd_time, &balong_clocks, node)  /*lint !e613*/
			{
			    ptr_child_clk = ptr_clk_lookup_2nd_time->clk;
				if (ptr_parent_clk == ptr_child_clk->parent)
				{
				    clk_printf("no %d clk %s is parent of no %d %s\n", 
						ptr_clk_lookup->clk_no, ptr_parent_clk->name, 
						ptr_clk_lookup_2nd_time->clk_no, ptr_child_clk->name);
				}
			}
    	}
	}


    return ;
}

void clk_debug_show_all_children(void)
{
    struct clk_lookup     *ptr_clk_lookup = NULL;
    struct clk_lookup     *ptr_clk_lookup_2nd_time = NULL;
	struct clk            *ptr_parent_clk = NULL;
	struct clk            *ptr_child_clk = NULL;
	
	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node) 
	{
	    ptr_parent_clk = ptr_clk_lookup->clk;
	
		/* 遍历链表 */
		list_for_each_entry(ptr_clk_lookup_2nd_time, &balong_clocks, node)  /*lint !e613*/
		{
		    ptr_child_clk = ptr_clk_lookup_2nd_time->clk;
			if (ptr_parent_clk == ptr_child_clk->parent)
			{
			    clk_printf("no %d clk %s is parent of no %d %s\n", 
					ptr_clk_lookup->clk_no, ptr_parent_clk->name, 
					ptr_clk_lookup_2nd_time->clk_no, ptr_child_clk->name);
				
			}
		}
		clk_printf("\n\n");
	}


    return ;
}

void clk_debug_enable_auto_gating(unsigned int clk_no_in_list)
{
    struct clk_lookup     *ptr_clk_lookup = NULL;
	int                   ret = -1;

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node) 
	{
	    if (clk_no_in_list == ptr_clk_lookup->clk_no)
    	{
    	    ret = clk_enable_auto_gating(ptr_clk_lookup->clk);
			if (ret)
			{
			    clk_printf("no %d name %s enable_auto_gating err\n", 
					       ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id);
				return ;
			}
		    clk_printf("no %d name %s enable_auto_gating ok\n", 
				       ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id);
		
    	}
	}


    return ;
}



void clk_debug_disable_auto_gating(unsigned int clk_no_in_list)
{
    struct clk_lookup     *ptr_clk_lookup = NULL;
	int                   ret = -1;

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node) 
	{
	    if (clk_no_in_list == ptr_clk_lookup->clk_no)
    	{
    	    ret = clk_disable_auto_gating(ptr_clk_lookup->clk);
			if (ret)
			{
			    clk_printf("no %d name %s disable_auto_gating err\n",  
					       ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id);
				return ;
			}
		    clk_printf("no %d name %s disable_auto_gating ok\n",   /* [false alarm]:屏蔽Fortify错误 */
				       ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id);
		
    	}
	}


    return ;
}

void clk_debug_show_all_maybe_parents(void)
{
    struct clk_lookup     *ptr_clk_lookup = NULL;
    struct clk_lookup     *ptr_clk_lookup_parent = NULL;
	int                   i = 0;
		
	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node) 
	{
	    clk_printf("clk no = %d name = %s num_parents = %d\n", 
			       ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id, ptr_clk_lookup->clk->num_parents);
		
	    for (i = 0; i < ptr_clk_lookup->clk->num_parents; i++) /*lint !e830*/
    	{
		    //clk_printf("parent %d  name = %s\n", 
			//	        i,  ptr_clk_lookup->clk->parents[i]->name);

			/* 遍历链表 */
			list_for_each_entry(ptr_clk_lookup_parent, &balong_clocks, node) /*lint !e613*/
	    	{
	    	    /* 是父时钟 */
	    	    if (ptr_clk_lookup_parent->clk == ptr_clk_lookup->clk->parents[i])
    	    	{
                    /* 还是当前父时钟 */
				    if (ptr_clk_lookup_parent->clk == ptr_clk_lookup->clk->parent)
			    	{
					    clk_printf("parent %d  no = %d name = %s----current parent\n", 
							        i,  ptr_clk_lookup_parent->clk_no, ptr_clk_lookup_parent->con_id);
			    	}
					else  /* 只是父时钟，非当前父时钟 */
					{
					    clk_printf("parent %d  no = %d name = %s\n", 
							        i,  ptr_clk_lookup_parent->clk_no, ptr_clk_lookup_parent->con_id);
					}
    	    	}
	    	    
	    	}
		
			//ptr_clk_lookup_parent = container_of(&(ptr_clk_lookup->clk->parents[i]), struct clk_lookup, clk);
		    //clk_printf("parent %d no = %d name = %s\n", 
			//	        i, ptr_clk_lookup_parent->clk_no, ptr_clk_lookup_parent->con_id);
    	}

		clk_printf("\n\n"); /*lint !e539*/
	}
	

    return ;
}


void uart0_clk_test(void)
{
    /* 首先测试开关 */
	struct clk *ptr_clk = NULL;
	int        i = 0;
	int        enable_cnt = 0;
	int        disable_cnt = 0;
	bool       is_enabled = false;

    clk_printf("uart0_clk test starting...\n");
	
	ptr_clk = clk_get(NULL, "uart0_clk");
	if (IS_ERR(ptr_clk))
	{
	    clk_printf("clk_get uart0_clk err\n");
		return ;
	}

    /* 开很多次，一次能关闭 */
	enable_cnt = 100;
	disable_cnt = 1;
	for (i = 0; i < enable_cnt; i++)
	{
	    (void)clk_enable(ptr_clk);
	}
	for (i = 0; i < disable_cnt; i++)
	{
	    clk_disable(ptr_clk);
	}
    is_enabled = clk_is_enabled(ptr_clk);
	if (false != is_enabled)
	{
	    clk_printf("after %d times enable and %d times disable the clk should be disabled but now it is enabled\n", 
	    enable_cnt, disable_cnt);
	    return ;
	}
    clk_printf("after %d times enable and %d times disable the clk is disabled test ok\n", enable_cnt, disable_cnt);

    /* 关很多次，一次能打开 */
	enable_cnt = 1;
	disable_cnt = 100;

	for (i = 0; i < disable_cnt; i++)
	{
	    clk_disable(ptr_clk);
	}
	for (i = 0; i < enable_cnt; i++)
	{
	    (void)clk_enable(ptr_clk);  
	}
	
	is_enabled = clk_is_enabled(ptr_clk);
	if (true != is_enabled)
	{
	    clk_printf("after %d times disable and %d times enable the clk should be enabled but now it is disabled\n", disable_cnt, enable_cnt);
	    return ;
	}
    clk_printf("after %d times disable and %d times enable the clk is enabled test ok\n", disable_cnt, enable_cnt);
	
	
    clk_printf("uart0_clk test end...\n");

    return ;
}

