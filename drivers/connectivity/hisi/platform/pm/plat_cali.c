

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "plat_firmware.h"
#include "plat_cali.h"
#include "plat_debug.h"
#include "plat_type.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define RF_CALI_DATA_BUF_LEN  (sizeof(oal_cali_param_stru))

/*****************************************************************************
  3 全局变量定义
*****************************************************************************/

/*保存校准数据的buf*/
oal_uint8 *g_pucCaliDataBuf = NULL;

/*****************************************************************************
  4 函数实现
*****************************************************************************/


oal_int32 get_cali_count(oal_uint32 *count)
{
    oal_cali_param_stru *pst_cali_data = NULL;
    oal_uint16 cali_count;
    oal_uint32 cali_parm;

    if (NULL == count)
    {
        PS_PRINT_ERR("count is NULL\n");
        return -EFAIL;
    }

    if (NULL == g_pucCaliDataBuf)
    {
        PS_PRINT_ERR("g_pucCaliDataBuf is NULL\n");
        return -EFAIL;
    }

    pst_cali_data = (oal_cali_param_stru *)g_pucCaliDataBuf;
    cali_count    = pst_cali_data->st_cali_update_info.ul_cali_time;
    cali_parm     = *(oal_uint32 *)&(pst_cali_data->st_cali_update_info);

    PS_PRINT_WARNING("cali count is [%d], cali update info is [%d]\n", cali_count, cali_parm);

    *count = cali_parm;

    return SUCC;
}


int32 get_bfgx_cali_data(oal_uint8 *buf, oal_uint32 *len, oal_uint32 buf_len)
{
    oal_cali_param_stru *pst_cali_data = NULL;
    oal_uint32 bfgx_cali_data_len;

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -EFAIL;
    }

    if (NULL == len)
    {
        PS_PRINT_ERR("len is NULL\n");
        return -EFAIL;
    }

    bfgx_cali_data_len = sizeof(oal_bfgn_cali_param_stru);
    if (buf_len < bfgx_cali_data_len)
    {
        PS_PRINT_ERR("buf_len[%d] is smaller than struct size[%d]\n", buf_len, bfgx_cali_data_len);
        return -EFAIL;
    }

    if (NULL == g_pucCaliDataBuf)
    {
        PS_PRINT_ERR("g_pucCaliDataBuf is NULL\n");
        return -EFAIL;
    }

    pst_cali_data = (oal_cali_param_stru *)g_pucCaliDataBuf;
    OS_MEM_CPY(buf, (oal_uint8 *)&(pst_cali_data->st_bfgn_cali_data), bfgx_cali_data_len);
    *len = bfgx_cali_data_len;

    return SUCC;
}


void *get_cali_data_buf_addr(void)
{
    return g_pucCaliDataBuf;
}

EXPORT_SYMBOL(get_cali_data_buf_addr);


void plat_bfgx_cali_data_test(void)
{
    oal_cali_param_stru *pst_cali_data = NULL;
    oal_uint32 *p_test = NULL;
    oal_uint32 count;
    oal_uint32 i;

    pst_cali_data = (oal_cali_param_stru *)get_cali_data_buf_addr();
    if (NULL == pst_cali_data)
    {
        PS_PRINT_ERR("get_cali_data_buf_addr failed\n");
        return;
    }

    p_test = (oal_uint32 *)&(pst_cali_data->st_bfgn_cali_data);
    count  = sizeof(oal_bfgn_cali_param_stru) / sizeof(oal_uint32);

    for (i = 0; i < count; i++)
    {
        p_test[i] = i;
    }

    return;
}


oal_int32 cali_data_buf_malloc(void)
{
    oal_uint8 *buffer = NULL;

    buffer = OS_KZALLOC_GFP(RF_CALI_DATA_BUF_LEN);
    if (NULL == buffer)
    {
        return -EFAIL;
    }
    g_pucCaliDataBuf = buffer;

    //plat_bfgx_cali_data_test();

    return SUCC;
}


void cali_data_buf_free(void)
{
    if (NULL != g_pucCaliDataBuf)
    {
        OS_MEM_KFREE(g_pucCaliDataBuf);
    }
    g_pucCaliDataBuf = NULL;
}


