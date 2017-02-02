
#include <asm/compiler.h>
#include "atfdriver.h"
#define FUNCID_OEN_SHIFT		24
#define FUNCID_OEN_MASK			0x3f
#define FUNCID_OEN_WIDTH		6
#define OEN_TOS_START			50	/* Trusted OS */
#define OEN_TOS_END			63

noinline int atfd_hisi_service_efusec_smc(u64 function_id, u64 arg0, u64 arg1, u64 arg2)
{
    asm volatile(
            __asmeq("%0", "x0")
            __asmeq("%1", "x1")
            __asmeq("%2", "x2")
            __asmeq("%3", "x3")
            "smc    #0\n"
        : "+r" (function_id)
        : "r" (arg0), "r" (arg1), "r" (arg2));

    return (int)function_id;
}

noinline int atfd_hisi_service_tsp_smc_asm(u64 function_id, u64* arg0, u64* arg1, u64* arg2)
{
    asm volatile(
            __asmeq("%0", "x0")
            __asmeq("%1", "x1")
            __asmeq("%2", "x2")
            __asmeq("%3", "x3")
            "smc    #0\n"
        : "+r" (function_id)
        : "r" (*arg0), "r" (*arg1), "r" (*arg2));

    return (int)function_id;
}

noinline int atfd_hisi_service_tsp_smc(u64 function_id, u64 arg0, u64 arg1, u64 arg2)
{
    int tsp_flag=0;
    int oen;
    u64 *tsp_result;


    oen = (function_id >> FUNCID_OEN_SHIFT) & FUNCID_OEN_MASK;
    if(oen >= OEN_TOS_START && oen <= OEN_TOS_END){
        tsp_flag = 1;
        tsp_result = (u64*)arg2;
    }

    atfd_hisi_service_tsp_smc_asm(function_id, &arg0, &arg1, &arg2);

    if(tsp_flag)
    {
        tsp_result[0] = arg0;
        tsp_result[1] = arg1;
    }
    return (int)function_id;
}

/* the interface is used as access some secure registers from unsecure-Kernel layer.
 * main_fun_id--input parameter, fixed as ACCESS_REGISTER_FN_MAIN_ID,equal to 0xc500aa01
 * buff_addr_phy--input parameter for write, output para for read, the allocated buffer address in Kernel, must be physical address
 * data_len--the buffer size, unit is Bytes
 * sub_fun_id--the sub function id, started by 0x55bbcce0, the index increase one by one
*/
noinline int atfd_hisi_service_access_register_smc(u64 main_fun_id, u64 buff_addr_phy, u64 data_len, u64 sub_fun_id)
{
    asm volatile(
            __asmeq("%0", "x0")
            __asmeq("%1", "x1")
            __asmeq("%2", "x2")
            __asmeq("%3", "x3")
            "smc    #0\n"
        : "+r" (main_fun_id)
        : "r" (buff_addr_phy), "r" (data_len), "r" (sub_fun_id));

    return (int)main_fun_id;
}

noinline int atfd_hisi_rpmb_smc(u64 function_id, u64 arg0, u64 arg1,  u64 arg2)
{
    asm volatile(
            __asmeq("%0", "x0")
            __asmeq("%1", "x1")
            __asmeq("%2", "x2")
            __asmeq("%3", "x3")
            "smc    #0\n"
        : "+r" (function_id)
        : "r" (arg0), "r" (arg1), "r" (arg2));

    return function_id;
}
