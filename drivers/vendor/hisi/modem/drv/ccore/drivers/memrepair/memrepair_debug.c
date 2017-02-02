
#include <product_config.h>
#include <securec.h>
#include <osl_types.h>
#include <bsp_sysctrl.h>
#include <bsp_om.h>
#include <bsp_shared_ddr.h>
#include <bsp_hardtimer.h>
#include <bsp_version.h>
#include <bsp_hw_spinlock.h>
#include <bsp_memrepair.h>

#include <memrepair_balong.h>

#ifdef __OS_RTOSCK__
#define mr_print_dbg SRE_Printf
#else
#define mr_print_dbg(fmt, ...) (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEMREPAIR, fmt,##__VA_ARGS__))
#endif

extern struct memrepair_info g_memrepair;

/*****************************************************************************
* �� �� : memrepair_log_set
* �� �� : memrepair ��ش�ӡ�ȼ�����
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
void memrepair_log_set(u32 level)
{
    /*todo xuwenfang*/
    (void)bsp_mod_level_set(BSP_MODU_MEMREPAIR, level);
    mr_print_dbg("bbp log id=%d, set to level=%d)\n",BSP_MODU_MEMREPAIR,level);
}
/*****************************************************************************
* �� �� : memrepair_log_get
* �� �� : ��ȡmemrepair ��ش�ӡ�ȼ�
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
void memrepair_log_get(void)
{
    u32 log_level = 0;

    log_level = bsp_log_module_cfg_get(BSP_MODU_MEMREPAIR);
    mr_print_dbg("bbp log id=%d, level=%d\n",BSP_MODU_MEMREPAIR,log_level);
}

/*****************************************************************************
* �� �� : memrepair_info_show
* �� �� : ��ȡmemrepair ���޸��������޸�ʱ����Ϣ
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
void memrepair_info_show(void)
{
    int moudle = 0;

    mr_print_dbg("%-10s %-20s %-20s\n","moudle_id","repair_cnts","time_cost");
    for(moudle = MODEM_MEMREPAIR_DSP;moudle < MODEM_MEMREPAIR_BUTT;moudle++)
    {
        mr_print_dbg("%-10d 0x%-20x 0x%-20x\n",moudle,g_memrepair.info[moudle].cnts,g_memrepair.info[moudle].time);
    }
}
/*****************************************************************************
* �� �� : bad_mem_check
* �� �� : ������
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
int bad_mem_check(u32 addr, u32 value, u32 len)
{
    u32 reg_value = 0;
    int iret = 0;
    u32 i = 0;

    (void)memset_s((void *)addr,len,(int)value,len);
    for(i = 0;i < len;)
    {
        reg_value = (u32)readl(addr + i);
        if(reg_value != value)
        {
            mr_print_dbg("bad mem addr 0x%x,value is 0x%x,should be 0x%x. \n",addr+i,reg_value,value);
            iret = -1;
        }
        i+=4;
    }
    /*��valueȡ�����ټ��һ��*/
    value = ~value;

    (void)memset_s((void *)addr,len,(int)value,len);
    for(i = 0;i < len; )
    {
        reg_value = (u32)readl(addr + i);
        if(reg_value != value)
        {
            mr_print_dbg("bad mem addr 0x%x,value is 0x%x,should be 0x%x. \n",addr+i,reg_value,value);
            iret = -1;
        }
        i+=4;
    }

    mr_print_dbg("mem check finsh.\n");

    return iret;
}
/*****************************************************************************
* �� �� : module_memrepair_test
* �� �� : ������
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
void module_memrepair_test(modem_memrepair_ip module,u32 addr, u32 value, u32 len)
{
    int iret = 0;

    /*�ȼ���Ƿ��л���*/
    iret = bad_mem_check(addr,value,len);
    if(!iret)
    {
        mr_print_dbg("bbp irm memory have no bad mem.\n");
    }
    else
    {
        /*ִ��memrepair*/
        iret = bsp_modem_memrepair(module);
        if(iret)
        {
            mr_print_dbg("repair error!\n");
        }
        /*���¼�⻵��*/
        iret = bad_mem_check(addr,value,len);
        if(iret)
        {
            mr_print_dbg("repair failed,mem still bad!\n");
        }
        else
        {
            mr_print_dbg("repair ok!\n");
        }
    }
}

int bsp_modem_memrepair_test(void)
{
    int iret = 0;

#if 0
    /**/
    iret = module_memrepair_test(MODEM_MEMREPAIR_DSP,);
    iret |= module_memrepair_test(MODEM_MEMREPAIR_BBPIRM,);
    iret |= module_memrepair_test(MODEM_MEMREPAIR_BBPCOM,);
    iret |= module_memrepair_test(MODEM_MEMREPAIR_BBPCS,);
    mr_print_error("test finsh.\n");
#endif
    return iret;
}
/*****************************************************************************
* �� �� : memrepair_flag_onoff
* �� �� : ��memrepair���߲���
* �� �� : onoff:0--memrepair;1--not repair
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
void memrepair_flag_onoff(int onoff)
{
    g_memrepair.flag = onoff;
}
/*****************************************************************************
* �� �� : memrepair_help
* �� �� : ����˵��
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
void memrepair_help(void)
{
    mr_print_dbg("show debug info       : memrepair_info_show (void)!\n");
    mr_print_dbg("check mem bad or not  : bad_mem_check (addr,value,len)!\n");
    mr_print_dbg("test module repair    : module_memrepair_test(module,addr,value,len)!\n");
    mr_print_dbg("get_memrepair_bit     : get_memrepair_bit(module)!\n");
    mr_print_dbg("is_need_memrepair     : modem_is_need_memrepair (module)!\n");
    mr_print_dbg("memrepair  func       : bsp_modem_memrepair (module)!\n");
    mr_print_dbg("memrepair  time       : bsp_get_memrepair_time (void)!\n");
    mr_print_dbg("log level  set        : memrepair_log_set (level)!\n");
    mr_print_dbg("log level  get        : memrepair_log_get (void)!\n");
    mr_print_dbg("onoff repair function : memrepair_flag_onoff (onoff)!\n");
}

