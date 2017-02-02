
#include "osl_bio.h"
#include "osl_malloc.h"
#include "watchpoint.h"

extern s32 wp_register(u32 type, u32 start_addr, u32 end_addr);

/* 单个4字节对齐地址 */
s32 wp_st_001(void)
{
    wp_cfg_t cfg;
    s32 wp_id;
    u8 * data;

    data = (u8 *)osl_malloc(4);
    if(data == NULL)
    {
        wp_print("malloc fail\n");
        return BSP_ERROR;
    }

    cfg.enable = WATCHPOINT_ENABLE;
    cfg.type   = WATCHPOINT_RW;
    cfg.start_addr  = (u32)data;
    cfg.end_addr    = 0;

    wp_id = bsp_wp_register(&cfg);
    if(BSP_ERROR == wp_id)
    {
        wp_print("fail\n");
        osl_free(data);
        return BSP_ERROR;
    }

    (void)bsp_wp_unregister(wp_id);
    wp_print("pass\n");
    osl_free(data);
    return BSP_OK;
}

/* 单个非4字节对齐地址 */
s32 wp_st_002(void)
{
    wp_cfg_t cfg;
    s32 wp_id;
    u8 * data;

    data = (u8 *)osl_malloc(4);
    if(data == NULL)
    {
        wp_print("malloc fail\n");
        return BSP_ERROR;
    }

    cfg.enable = WATCHPOINT_ENABLE;
    cfg.type   = WATCHPOINT_RW;
    cfg.start_addr  = (u32)data + 1;
    cfg.end_addr    = 0;

    wp_id = bsp_wp_register(&cfg);
    if(BSP_ERROR == wp_id)
    {
        wp_print("pass\n");
        osl_free(data);
        return BSP_OK;
    }

    wp_print("fail\n");
    (void)bsp_wp_unregister(wp_id);
    osl_free(data);
    return BSP_ERROR;
}

/* 合法地址范围 */
s32 wp_st_003(void)
{
    wp_cfg_t cfg;
    s32 wp_id;
    u8 * data;

    data = (u8 *)osl_malloc(0x10);
    if(data == NULL)
    {
        wp_print("malloc fail\n");
        return BSP_ERROR;
    }

    cfg.enable = WATCHPOINT_ENABLE;
    cfg.type   = WATCHPOINT_RW;
    cfg.start_addr  = (u32)data;
    cfg.end_addr    = (u32)data + 0xF;

    wp_id = bsp_wp_register(&cfg);
    if(BSP_ERROR == wp_id)
    {
        wp_print("fail\n");
        osl_free(data);
        return BSP_ERROR;
    }

    (void)bsp_wp_unregister(wp_id);
    wp_print("pass\n");
    osl_free(data);
    return BSP_OK;
}

/* 非法地址范围 */
s32 wp_st_004(void)
{
    wp_cfg_t cfg;
    s32 wp_id;
    u8 * data;

    data = (u8 *)osl_malloc(0x10);
    if(data == NULL)
    {
        wp_print("malloc fail\n");
        return BSP_ERROR;
    }

    cfg.enable = WATCHPOINT_ENABLE;
    cfg.type   = WATCHPOINT_RW;
    cfg.start_addr  = (u32)data + 0x8;
    cfg.end_addr    = (u32)data + 0x4;

    wp_id = bsp_wp_register(&cfg);
    if(BSP_ERROR == wp_id)
    {
        wp_print("pass\n");
        osl_free(data);
        return BSP_OK;
    }

    (void)bsp_wp_unregister(wp_id);
    wp_print("fail\n");
    osl_free(data);
    return BSP_OK;
}

/* 读取监控地址 */
s32 wp_st_005(void)
{
    s32 wp_id;
    u8 * data;

    data = (u8 *)osl_malloc(4);
    if(data == NULL)
    {
        wp_print("malloc fail\n");
        return BSP_ERROR;
    }

    wp_id = wp_register(WATCHPOINT_R, (u32)data, 0);
    if(BSP_ERROR == wp_id)
    {
        wp_print("fail\n");
        osl_free(data);
        return BSP_ERROR;
    }

    /* 只监控读，写不会触发异常 */
    writel(0x1234, (u32)data);

    /* rtosck会触发复位 */
    (void)readl((u32)data);
    (void)bsp_wp_unregister(wp_id);
    wp_print("pass\n");
    osl_free(data);
    return BSP_OK;
}

/* 写入监控地址 */
s32 wp_st_006(void)
{
    s32 wp_id;
    u8 * data;

    data = (u8 *)osl_malloc(4);
    if(data == NULL)
    {
        wp_print("malloc fail\n");
        return BSP_ERROR;
    }

    wp_id = wp_register(WATCHPOINT_W, (u32)data, 0);
    if(BSP_ERROR == wp_id)
    {
        wp_print("fail\n");
        osl_free(data);
        return BSP_ERROR;
    }

    /* 只监控写，读不会触发异常 */
    (void)readl((u32)data);

    /* rtosck会触发复位 */
    writel(0x1234, (u32)data);
    (void)bsp_wp_unregister(wp_id);
    wp_print("pass\n");
    osl_free(data);
    return BSP_OK;
}

/* 读写监控地址 */
s32 wp_st_007(void)
{
    s32 wp_id;
    u8 * data;

    data = (u8 *)osl_malloc(4);
    if(data == NULL)
    {
        wp_print("malloc fail\n");
        return BSP_ERROR;
    }

    wp_id = wp_register(WATCHPOINT_W, (u32)data, 0);
    if(BSP_ERROR == wp_id)
    {
        wp_print("fail\n");
        osl_free(data);
        return BSP_ERROR;
    }

    /* 读、写均触发异常，rtosck会触发复位 */
    (void)readl((u32)data);
    writel(0x1234, (u32)data);

    (void)bsp_wp_unregister(wp_id);
    wp_print("pass\n");
    osl_free(data);
    return BSP_OK;
}

/* 监控地址范围外读写 */
s32 wp_st_008(void)
{
    s32 wp_id;
    u8 * data;

    data = (u8 *)osl_malloc(8);
    if(data == NULL)
    {
        wp_print("malloc fail\n");
        return BSP_ERROR;
    }

    wp_id = wp_register(WATCHPOINT_W, (u32)data, 0);
    if(BSP_ERROR == wp_id)
    {
        wp_print("fail\n");
        osl_free(data);
        return BSP_ERROR;
    }

    (void)readl((u32)data+4);
    writel(0x1234, (u32)data+4);

    (void)bsp_wp_unregister(wp_id);
    wp_print("pass\n");
    osl_free(data);
    return BSP_OK;
}

/* 动态配置 */
s32 wp_st_009(void)
{
    wp_cfg_t cfg;
    s32 wp_id;
    u8 * data;

    data = (u8 *)osl_malloc(8);
    if(data == NULL)
    {
        wp_print("malloc fail\n");
        return BSP_ERROR;
    }

    cfg.enable = WATCHPOINT_ENABLE;
    cfg.type   = WATCHPOINT_RW;
    cfg.start_addr  = (u32)data;
    cfg.end_addr    = 0;

    wp_id = bsp_wp_register(&cfg);
    if(BSP_ERROR == wp_id)
    {
        wp_print("fail\n");
        osl_free(data);
        return BSP_ERROR;
    }

    (void)bsp_wp_disable(wp_id);
    (void)readl((u32)data);

    (void)bsp_wp_enable(wp_id);
    (void)readl((u32)data);

    (void)bsp_wp_unregister(wp_id);
    wp_print("pass\n");
    osl_free(data);
    return BSP_OK;    
}

/* 多次申请 */
s32 wp_st_010(void)
{
    wp_cfg_t cfg;
    s32 wp_id[4];
    u32 i;

    cfg.enable = WATCHPOINT_ENABLE;
    cfg.type   = WATCHPOINT_RW;
    cfg.start_addr  = 0x55600000;
    cfg.end_addr    = 0;

    for(i=0; i<4; i++)
    {
        wp_id[i] = bsp_wp_register(&cfg);
        if(BSP_ERROR == wp_id[i])
        {
            wp_print("fail\n");
            return BSP_ERROR;
        }
    }

    if(BSP_ERROR != bsp_wp_register(&cfg))
    {
        wp_print("fail\n");
    }

    
    for(i=0; i<4; i++)
    {
        (void)bsp_wp_unregister(wp_id[i]);
    }

    wp_print("pass\n");
    return BSP_OK;    
}

/* 非法ID测试 */
s32 wp_st_011(void)
{
    if(BSP_ERROR != bsp_wp_register(NULL))
    {
        goto fail;
    }

    if(BSP_ERROR != bsp_wp_enable(0x100))
    {
        goto fail;
    }

    if(BSP_ERROR != bsp_wp_disable(0x100))
    {
        goto fail;
    }

    if(BSP_ERROR != bsp_wp_unregister(0x100))
    {
        goto fail;
    }

    wp_print("pass\n");
    return BSP_OK;

fail:
    wp_print("fail\n");
    return BSP_ERROR;
}



