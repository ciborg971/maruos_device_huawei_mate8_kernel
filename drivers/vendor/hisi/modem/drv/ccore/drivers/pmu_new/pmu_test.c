#include <product_config.h>
#include <securec.h>
#include <osl_malloc.h>
#include <osl_bio.h>
#include <osl_err.h>
#include <osl_spinlock.h>
#include <osl_thread.h>
#include <of.h>

#include <bsp_regulator.h>
#include <pmu_balong.h>
#include <pmu_pmic.h>
#include <hi_pmu.h>

extern struct pmic_volt_info g_pmic_voltinfo;
extern struct pmic_xo_info g_pmic_xoinfo;
extern struct dcdc_info g_pmu_exdcdc;

#define pmu_print_test(fmt, ...) (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PMU, fmt,##__VA_ARGS__))


struct volt_test_cfg
{
    u32 id;
    const char *name;
    u32 onoff_ctrl;
    u32 voltage_ctrl;
};
struct volt_test_info
{
    u32 volt_num;
    struct volt_test_cfg *volt_test;
};
struct volt_test_info g_pmic_test;

/*dcdc_volt*/
int dcdc_enable_test()
{
    int ret = BSP_OK;
    unsigned int dc_id = 0;

    for(dc_id = 0; dc_id < g_pmu_exdcdc.dc_num; dc_id++)
    {
        (void)dcdc_volt_enable((int)dc_id);
        if(!dcdc_volt_is_enabled((int)dc_id))
        {
            pmu_print_error("dcdc_id %d enable error!",dc_id);
            ret |= BSP_ERROR;
        }
    }

    return ret;
}
int dcdc_disable_test()
{
    int ret = BSP_OK;
    unsigned int dc_id = 0;

    for(dc_id = 0; dc_id < g_pmu_exdcdc.dc_num; dc_id++)
    {
        (void)dcdc_volt_disable((int)dc_id);
        if(dcdc_volt_is_enabled((int)dc_id))
        {
            pmu_print_error("dcdc_id %d disable error!\n",dc_id);
            ret |= BSP_ERROR;
        }
    }

    return ret;
}
/*pmic_xorf*/
int pmic_xorf_enable_test()
{
    int ret = BSP_OK;
    unsigned int rf_id = 0;

    for(rf_id = 0; rf_id < g_pmic_xoinfo.xorf_num; rf_id++)
    {
        pmic_rfclk_enable(rf_id);
        if(!pmic_rfclk_is_enabled(rf_id))
        {
            pmu_print_error("xorf_id %d enable error!",rf_id);
            ret |= BSP_ERROR;
        }
    }

    return ret;
}
int pmic_xorf_disable_test()
{
    int ret = BSP_OK;
    unsigned int rf_id = 0;

    for(rf_id = 0; rf_id < g_pmic_xoinfo.xorf_num; rf_id++)
    {
        pmic_rfclk_disable(rf_id);
        if(pmic_rfclk_is_enabled(rf_id))
        {
            pmu_print_error("xorf_id %d disable error!\n",rf_id);
            ret |= BSP_ERROR;
        }
    }

    return ret;
}
/*pmic_volt*/
int pmic_volt_enable_test()
{
    int ret = BSP_OK;
    unsigned int volt_id = 0;

    for(volt_id = 0; volt_id < g_pmic_test.volt_num; volt_id++)
    {
        if(g_pmic_test.volt_test[volt_id].onoff_ctrl)
        {
            (void)pmic_volt_enable((int)volt_id);
            if(!pmic_volt_is_enabled((int)volt_id))
            {
                pmu_print_error("volt_id %d enable error!",volt_id);
                ret |= BSP_ERROR;
            }
        }
    }

    return ret;
}
int pmic_volt_disable_test()
{
    int ret = BSP_OK;
    u32 volt_id = 0;

    for(volt_id = 0; volt_id < g_pmic_test.volt_num; volt_id++)
    {
        if(g_pmic_test.volt_test[volt_id].onoff_ctrl)
        {
            (void)pmic_volt_disable((int)volt_id);
            if(pmic_volt_is_enabled((int)volt_id))
            {
                pmu_print_error("volt_id %d disable error!\n",volt_id);
                ret = BSP_ERROR;
            }
        }
    }

    return ret;
}
int pmic_volt_voltage_test()
{
    int ret = BSP_OK;
    struct pmic_volt_ctrl *volt_ctrl = NULL;
    u32 volt_id = 0;
    u32 vsel = 0;
    u32 selector = 0;
    u32 voltage = 0;

    for(volt_id = 0; volt_id < g_pmic_test.volt_num; volt_id++)
    {
        if(g_pmic_test.volt_test[volt_id].voltage_ctrl)
        {
            volt_ctrl = &g_pmic_voltinfo.volt_ctrl[volt_id];
            for(vsel = 0; vsel < volt_ctrl->voltage_nums ; vsel++)
            {
                voltage = pmic_volt_list_voltage((int)volt_id,vsel);
                (void)pmic_volt_set_voltage((int)volt_id, (int)voltage, (int)voltage, &selector);
                if((int)voltage != pmic_volt_get_voltage((int)volt_id))
				{                    					pmu_print_error("volt_id %d set or get voltage error!voltage:%d, get_voltgae:%d \n",volt_id, voltage, pmic_volt_get_voltage((int)volt_id));
				}
                if(vsel != selector)
                {                  					pmu_print_error("volt_id %d list voltage error!vsel:%d, selector:%d \n",volt_id, vsel, selector);
                }
            }
        }
    }

    return ret;
}

/*stress*/

void pmu_test_init(void)
{
    int ret = BSP_OK;
    struct device_node *dev_node = NULL;
    struct device_node *child_node = NULL;
    u32 id = 0;
    u32 test_size = 0;

    dev_node = of_find_compatible_node(NULL, NULL, "hisilicon,pmu_pmic_test");
    if(NULL == dev_node)
    {
        pmu_print_error("pmic test device node not found!\n");
        return;
    }

    g_pmic_test.volt_num = of_get_child_count(dev_node);

    test_size = sizeof(struct volt_test_cfg)*(g_pmic_test.volt_num);
    g_pmic_test.volt_test = (struct volt_test_cfg *)osl_malloc(test_size);
    if(IS_ERR(g_pmic_test.volt_test))
    {
        pmu_print_error("malloc pmic_volt_test failed\n");
        return;
    }
    (void)memset_s((void *)g_pmic_test.volt_test,test_size,0,test_size);

    for_each_child_of_node(dev_node, child_node)
    {
        ret = of_property_read_u32_index(child_node,"volt_id",0,&id);
        if (ret) {
            pmu_print_error("get volt_id info from dts failed\n");
            return;
        };
        g_pmic_test.volt_test[id].id = id;
        ret = of_property_read_string_index(child_node,"volt_name",0,&(g_pmic_test.volt_test[id].name));
        ret |= of_property_read_u32_index(child_node,"test_flag",0,&g_pmic_test.volt_test[id].onoff_ctrl);
        ret |= of_property_read_u32_index(child_node,"test_flag",1,&g_pmic_test.volt_test[id].voltage_ctrl);
        if (ret) {
            pmu_print_error("get vtest_flag info from dts failed\n");
            return;
        }
    }
}
void pmu_test_help(void)
{
    pmu_print_test("dcdc_enable_test:test enable dcdc volt \n");
    pmu_print_test("dcdc_disable_test:test disable dcdc volt \n");
    pmu_print_test("pmic_xorf_enable_test:test xorf enable\n");
    pmu_print_test("pmic_xorf_disable_test:test xorf disable\n");
    pmu_print_test("pmic_volt_enable_test:test volt enable\n");
    pmu_print_test("pmic_volt_disable_test:test volt disable\n");
    pmu_print_test("pmic_volt_voltage_test:test volt voltage\n");
    pmu_print_test("pmu_test_init:init test\n");
}

/*pmic exc test*/
#if 0
void pmic_ocp0_handler(int volt_id)
{
    pmic_print_error("test0 volt ocp,%d!\n",volt_id);
}
void pmic_ocp1_handler(int volt_id)
{
    pmic_print_error("test1 volt ocp,%d!\n",volt_id);
}
void pmic_ocp_test_init(int volt_id)
{
    pmic_ocp_register(volt_id,pmic_ocp0_handler);
    pmic_ocp_register(volt_id,pmic_ocp1_handler);
}
#endif
