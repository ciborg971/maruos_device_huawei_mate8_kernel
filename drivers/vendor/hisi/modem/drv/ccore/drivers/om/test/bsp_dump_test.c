
#ifdef __OS_VXWORKS__
#include <vxWorks.h>
#include <stdlib.h>
#include <logLib.h>
#include <stdio.h>
#include <errno.h>
#include <errnoLib.h>
#include <memLib.h>
#include <string.h>
#include <taskLib.h>
#include <intLib.h>
#include <vxWind.h>
#include <vxCpuLib.h>
#include <dbgLib.h>
#include <trcLib.h>
#include <sysSymTbl.h>
#include <taskHookLib.h>
#include <private/cplusLibP.h>
#include <private/dbgLibP.h>
#include <private/vxdbgLibP.h>
#include <private/vxdbgBpMsgQLibP.h>
#include <private/excLibP.h>
#include <private/rtpLibP.h>
#include <private/taskLibP.h>
#include <private/trcLibP.h>
#include <private/shellInternalLibP.h>
#include <private/eventLibP.h>
#include <symLib.h>
#include <taskLibCommon.h>
#include <a_out.h>
#include <vmLib.h>
#endif
#ifdef __OS_RTOSCK__

#endif
#include "string.h"
#include "osl_malloc.h"
#include "product_config.h"
//#include "osl_io.h"
#include "osl_types.h"
#include "osl_thread.h"
#include "bsp_om_api.h"
#include "bsp_dump.h"
#include "bsp_dump_drv.h"
#include "bsp_memmap.h"
#include "osl_malloc.h"
#include "drv_nv_def.h"
#include "securec.h"


#define  om_print_error(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_OM, "[om]:<%s> "fmt, __FUNCTION__, ##__VA_ARGS__))


enum exchS
{
    RESET,
    UNDEF,
    SWI,
    PABT,
    DABT,
    DIV,
    LOOP
};

void exchRESET(void);
void exchUNDEF(void);
void exchPABT(void);
void exchDABT(void);
void exchLOOP(void);
int  exchDIV(int a);
void exchTest(int type);
int dump_st_003(void);
int dump_st_004(void);
int dump_st_005(void);
int dump_st_006(void);
int dump_st_007(void);
int dump_st_008(void);
int dump_st_009(void);
int dump_st_010(void);
int dump_st_011(void);
int dump_st_012_013(void);
int dump_st_015_025(void);
int dump_st_026(void);
void dump_st_hook(void);
int dump_st_028(void);
void dump_st_029(void);
void dump_exc_task_test(void);
void dump_st_030(void);
void dump_st_031(void);

static char* g_dump_st_buffer;
static int   g_dump_st_len;
/*lint -save -e413*/
void exchRESET(void)
{
    /* coverity[assign_zero] */
    FUNC_VOID a = 0;/*lint !e611 !e740*/

    /* coverity[var_deref_op] */
    a();
}
/*lint -restore +e413*/
/*lint -save -e569 -e438*/

void exchUNDEF(void)
{
    int b = 0;
    FUNC_VOID a = (FUNC_VOID)(&b);/*lint !e611 !e740*/

    b = 0xffffffff;
    a();
}
/*lint -restore +e438 +e569*/

void exchPABT(void)
{
    FUNC_VOID a = (FUNC_VOID)0xF0000000;

    a();
}

void exchDABT(void)
{
    *(int *)0xF0000000 = 0x12345678;
}

void exchLOOP(void)
{
    /* coverity[no_escape] */
    for (;;)
    {
        ;
    }
}

int exchDIV(int a)
{
    int b = 4;

    return b / a;
}

void exchTest(int type)
{
    u32  task_id;
    switch (type)
    {
    case RESET:
        //(BSP_VOID)taskSpawn("exchRESET", 99, 0, 0x1000, (FUNCPTR)exchRESET, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        (void)osl_task_init("exchRESET", 20, 0x1000, (TSK_ENTRY_FUNC)exchRESET, NULL, &task_id);
        break;
    case UNDEF:
        //(BSP_VOID)taskSpawn("exchUNDEF", 99, 0, 0x1000, (FUNCPTR)exchUNDEF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        (void)osl_task_init("exchUNDEF", 20, 0x1000, (TSK_ENTRY_FUNC)exchUNDEF, NULL, &task_id);
        break;
    case PABT:
        //(BSP_VOID)taskSpawn("exchPABT", 99, 0, 0x1000, (FUNCPTR)exchPABT, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        (void)osl_task_init("exchPABT", 20, 0x1000, (TSK_ENTRY_FUNC)exchPABT, NULL, &task_id);
        break;
    case DABT:
        //(BSP_VOID)taskSpawn("exchDABT", 99, 0, 0x1000, (FUNCPTR)exchDABT, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);       
        (void)osl_task_init("exchDABT", 20, 0x1000, (TSK_ENTRY_FUNC)exchDABT, NULL, &task_id);
        break;
    case DIV:
        //(BSP_VOID)taskSpawn("exchDIV", 99, 0, 0x1000, (FUNCPTR)exchDIV, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        (void)osl_task_init("exchDIV", 20, 0x1000, (TSK_ENTRY_FUNC)exchDIV, NULL, &task_id);
        break;
    case LOOP:
        //(BSP_VOID)taskSpawn("exchLOOP", 253, 0, 0x1000, (FUNCPTR)exchLOOP, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        (void)osl_task_init("exchLOOP", 20, 0x1000, (TSK_ENTRY_FUNC)exchLOOP, NULL, &task_id);/* [false alarm]:fortify */
        break;
    default:
        break;
    }
}


/* RESET错误 */
int dump_st_003(void)
{
    exchTest(RESET);
//    exchRESET();
    return 0;
}


/* UNDEF错误 */
int dump_st_004(void)
{
    exchTest(UNDEF);
//    exchUNDEF();
    return 0;
}


/* SWI错误, cancel */
int dump_st_005(void)
{
    return 0;
}


/* Prefetch abort错误 */
int dump_st_006(void)
{
    exchTest(PABT);
//    exchPABT();
    return 0;
}

/* Data abort错误 */
int dump_st_007(void)
{
    exchTest(DABT);
//    exchDABT();
    return 0;
}

/* 除0错误 */
int dump_st_008(void)
{
    exchTest(DIV);
    return 0;
}

/* 核心过流 */
int dump_st_009(void)
{
    return 0;
}

/* 非核心过流 */
int dump_st_010(void)
{
    return 0;
}

/* 看门狗超时错误 */
int dump_st_011(void)
{
    return 0;
}

/* A核软件异常 */
int dump_st_012_013(void)
{
    return 0;
}

/* A核软件异常之后基本信息 */
int dump_st_015_025(void)
{
    return 0;
}

/* A核用户数据 */
int dump_st_026(void)
{
    char *p = NULL;
    p = (char*)osl_malloc(4096);
    if(p == NULL)
    {
        return 0;
    }
    
    (void)memset_s(p,4096,1,4096);
    system_error(0x88,1,2,p,4096);
    return 0;
}

/*lint -save -e702*/
void dump_st_hook(void)
{
    u32 len = g_dump_st_len>>1;

    om_print_error("dump_st_hook enter \n");
    (void)memset_s(g_dump_st_buffer,len, 0xcc, len);
    (void)memset_s(g_dump_st_buffer+len,len, 0xdd, len);
}
/*lint -restore +e702*/

/* C核扩展数据 */
int dump_st_028(void)
{
    int ret;

    g_dump_st_buffer = (char*)bsp_dump_register_field(DUMP_CP_SIM0, "SIM0", 0, 0, 0x4000, 0);
    if(BSP_NULL == g_dump_st_buffer)
    {
        om_print_error("get buffer failed.  test case 28 failed! \n");
        return BSP_ERROR;
    }
    g_dump_st_len = 0x4000;
    
    om_print_error("buffer=0x%x, len=0x%x\n", (u32)g_dump_st_buffer, g_dump_st_len);

    ret = bsp_dump_register_hook("UTRACE", (dump_hook)dump_st_hook);
    if(BSP_ERROR == ret)
    {
        om_print_error("register_hook failed.  test case 28 failed! \n");
        return BSP_ERROR;
    }

    return BSP_OK;
}

extern NV_DUMP_STRU g_dump_cfg;
void dump_st_029(void)
{
    g_dump_cfg.dump_cfg.Bits.commRegSave1= 1;
    g_dump_cfg.dump_cfg.Bits.commRegSave2= 1;
    g_dump_cfg.dump_cfg.Bits.commRegSave3= 1;
    g_dump_cfg.commRegAddr1 = HI_EDMA_REGBASE_ADDR_VIRT;
    g_dump_cfg.commRegSize1 = HI_EDMA_REG_SIZE;
    g_dump_cfg.commRegAddr2 = HI_SCI0_REGBASE_ADDR_VIRT;
    g_dump_cfg.commRegSize2 = HI_SCI0_REG_SIZE;
#ifdef HI_SCI1_REGBASE_ADDR_VIRT
    g_dump_cfg.dump_cfg.Bits.commRegSave1= 1;
    g_dump_cfg.commRegAddr3 = HI_SCI1_REGBASE_ADDR_VIRT;
    g_dump_cfg.commRegSize3 = HI_SCI1_REG_SIZE;
#endif
}

void dump_exc_task_test(void)
{
    om_print_error("%s: enter\n", __FUNCTION__);
    system_error(0x100, 0, 0, 0, 0);
}

void dump_st_030(void)
{
    u32 task_id;
    //(BSP_VOID)taskSpawn("exc_task_test", 99, 0, 0x1000, (FUNCPTR)dump_exc_task_test, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    
    (void)osl_task_init("exc_task_test", 20, 0x1000, (TSK_ENTRY_FUNC)dump_exc_task_test, NULL, &task_id);
    
}

#define DUMP_REG_BUF_SIZE   (4096)
char *dump_reg_buff = NULL;
void dump_st_031(void)
{
    char * addr;

    dump_reg_buff = osl_malloc(DUMP_REG_BUF_SIZE);
    (void)memset_s(dump_reg_buff, DUMP_REG_BUF_SIZE,0x5, DUMP_REG_BUF_SIZE);
    addr = (char*)bsp_dump_register_field(OM_CP_FTM_MNTN, "FTM_MNTN", (void *)dump_reg_buff, (void *)dump_reg_buff, 0x1000, 0x102);
    if(BSP_NULL == addr)
    {
        om_print_error("get buffer failed.  test case 31 failed! \n");
        return;
    }
    
    om_print_error("%s: buffer=%p\n", __FUNCTION__, addr);

    return;
}

/********************mdrv对外接口测试 begin***************************/
/* field注册接口测试 */
int mdrv_om_test_001(void)
{
    char * addr;

    addr = (char *)mdrv_om_register_field(DUMP_CP_REGS, "REGS", 0, 0, DUMP_REGS_SIZE, 0);
    if(addr != NULL)
    {
        om_print_error("%s pass\n", __FUNCTION__);
        return BSP_OK;
    }

    om_print_error("%s fail\n", __FUNCTION__);
    return BSP_ERROR;
}

/* field虚拟地址获取接口测试 */
int mdrv_om_test_002(void)
{
    char * addr;

    addr = (char *)mdrv_om_get_field_addr(DUMP_CP_REGS);
    if(addr != NULL)
    {
        om_print_error("%s pass\n", __FUNCTION__);
        return BSP_OK;
    }

    om_print_error("%s fail\n", __FUNCTION__);
    return BSP_ERROR;
}

/* field物理地址获取接口测试 */
int mdrv_om_test_003(void)
{
    char * addr;

    addr = (char *)mdrv_om_get_field_phy_addr(DUMP_CP_REGS);
    if(addr != NULL)
    {
        om_print_error("%s pass\n", __FUNCTION__);
        return BSP_OK;
    }

    om_print_error("%s fail\n", __FUNCTION__);
    return BSP_ERROR;
}

dump_handle g_dump_handle_test;
void dump_hook_test(void)
{
    om_print_error("dump hook test enter\n");
}
/* dump回调函数注册接口测试 */
int mdrv_om_test_004(void)
{
    g_dump_handle_test = mdrv_om_register_callback("DUMP_HOOK_TEST", (dump_hook)dump_hook_test);
    if(g_dump_handle_test != BSP_ERROR)
    {
        om_print_error("%s pass\n", __FUNCTION__);
        return BSP_OK;
    }

    om_print_error("%s fail\n", __FUNCTION__);
    return BSP_ERROR;
}

/* dump回调函数去注册接口测试 */
int mdrv_om_test_005(void)
{
    s32 ret;/* [false alarm]:fortify */
    ret = mdrv_om_unregister_callback(g_dump_handle_test);
    if(ret == BSP_OK)/* [false alarm]:fortify */
    {
        om_print_error("%s pass\n", __FUNCTION__);/* [false alarm]:fortify */
        return BSP_OK;/* [false alarm]:fortify */
    }/* [false alarm]:fortify */

    om_print_error("%s fail\n", __FUNCTION__);/* [false alarm]:fortify */
    return BSP_ERROR;/* [false alarm]:fortify */
}

/* HDIS连接设置接口测试 */
int mdrv_om_test_006(void)
{
    mdrv_om_set_hsoflag(0);

    om_print_error("%s pass\n", __FUNCTION__);
    return BSP_OK;
}

/* sysview配置接口测试 */
int mdrv_om_test_007(void)
{
    u32 ret;/* [false alarm]:fortify */
    ret = mdrv_om_set_sysview_swt(1, 0, 3);/* [false alarm]:fortify */
    if(ret == BSP_OK)/* [false alarm]:fortify */
    {
        om_print_error("%s pass\n", __FUNCTION__);/* [false alarm]:fortify */
        return BSP_OK;/* [false alarm]:fortify */
    }/* [false alarm]:fortify */
    

    om_print_error("%s fail\n", __FUNCTION__);/* [false alarm]:fortify */
    return BSP_ERROR;
}

/* sysview获取任务信息接口测试 */
int mdrv_om_test_008(void)
{
    u32 ret;
    char * data;

    data= osl_malloc(20*128);
    if(data == NULL)
    {
        om_print_error("%s malloc fail\n", __FUNCTION__);
        return BSP_ERROR;
    }

    ret = mdrv_om_get_alltaskinfo(data, 20*128);/* [false alarm]:fortify */
    if(ret == BSP_OK)
    {
        om_print_error("%s pass\n", __FUNCTION__);
        osl_free(data);
        return BSP_OK;
    }

    om_print_error("%s fail\n", __FUNCTION__);
    osl_free(data);
    return BSP_ERROR;
}

/* get root fs接口测试 */
int mdrv_om_test_009(void)
{
    s32 ret;/* [false alarm]:fortify */
    char data[50];/* [false alarm]:fortify */

    ret = mdrv_om_get_rootfs(data, sizeof(data));
    if(ret == BSP_OK)
    {
        om_print_error("%s pass\n", __FUNCTION__);/* [false alarm]:fortify */
        return BSP_OK;
    }

    om_print_error("%s fail\n", __FUNCTION__);/* [false alarm]:fortify */
    return BSP_ERROR;
}

extern bool g_exc_flag;
/* system_error测试 */
int mdrv_om_test_010(void)
{
    bool flag = g_exc_flag;/* [false alarm]:fortify */

    g_exc_flag = true;
    mdrv_om_system_error(0xf0000, 0, 0, 0, 0);
    g_exc_flag = flag;

    om_print_error("%s pass\n", __FUNCTION__);
    return BSP_OK;
}

/* get root fs接口测试 */
int mdrv_om_test_011(void)
{
    s32 ret;/* [false alarm]:fortify */
    DRV_OM_SYSTEM_RESET_S info;/* [false alarm]:fortify */

    ret = mdrv_om_get_system_reset_info(&info);
    if(ret == BSP_OK)
    {
        om_print_error("%s pass\n", __FUNCTION__);/* [false alarm]:fortify */
        return BSP_OK;
    }

    om_print_error("%s fail\n", __FUNCTION__);/* [false alarm]:fortify */
    return BSP_ERROR;/* [false alarm]:fortify */
}
/********************mdrv对外接口测试 end*****************************/

