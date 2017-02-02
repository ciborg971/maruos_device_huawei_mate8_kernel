
#include <string.h>

#include "product_config.h"
#include "drv_comm.h"
#include "osl_bio.h"
#include "osl_types.h"
//#include "mdrv_efuse.h"
#include "efuse_balong.h"
#include "hi_efuse.h"
#include "bsp_icc.h"
#include "bsp_om.h"


#ifdef CONFIG_EFUSE

int mdrv_efuse_read_huk(unsigned char *pbuf, unsigned int len)
{
    if ((NULL == pbuf) || (len < (EFUSE_HUK_SIZE * EFUSE_GROUP_SIZE))) {
        efuse_print_error("para error, pbuf is 0x%x, len is %d.\n", pbuf, len);
        return BSP_ERROR;
    }

    if (BSP_OK != bsp_efuse_read((u32*)pbuf, EFUSE_GRP_HUK, EFUSE_HUK_SIZE)) {
        efuse_print_error("efuse_read is failed!\n" );
        return BSP_ERROR;
    }

    return BSP_OK;
}

int mdrv_efuse_check_huk_valid(void)
{
    u32 i = 0;
    u32 buffer[EFUSE_HUK_SIZE] = {0};

    if (BSP_OK != mdrv_efuse_read_huk((unsigned char*)buffer, sizeof(buffer))) {
        efuse_print_error("read huk failed!\n");
        return BSP_FALSE;
    }

    for (i = 0; i < EFUSE_HUK_SIZE; i++) {
        if (0 != buffer[i]) {
            efuse_print_info("CheckHukIsValid success!\n");
            return BSP_TRUE;
        }
    }

    return BSP_FALSE;
}

int mdrv_efuse_write_huk(char *pbuf, unsigned int len)
{
    u32 i = 0;
    u32 buffer[EFUSE_HUK_SIZE] = {0};

    if ((NULL == pbuf) || (0 == len)) {
        efuse_print_error("para error.\n");
        return BSP_ERROR;
    }

    for (i = 0; i < len; i++) {
        if(0 != *(pbuf+i))
            break;
    }

    if (i >= len) {
        efuse_print_error("pBuf is null, please contact CW equipment colleague to confirm why send the command 'at^huk=000'.\n");
        return BSP_ERROR;
    }

    if ((EFUSE_GROUP_SIZE * EFUSE_HUK_SIZE) != len) {
        efuse_print_error("len is not %d.\n", EFUSE_GROUP_SIZE * EFUSE_HUK_SIZE);
        return BSP_ERROR;
    }

    if (BSP_OK != mdrv_efuse_read_huk((unsigned char*)buffer, len)) {
        efuse_print_error("read huk failed!\n");
        return BSP_ERROR;
    }

    for (i = 0; i < EFUSE_HUK_SIZE; i++) {
        if (0 != buffer[i]) {
            efuse_print_error("HUK has been written!\n");
            return BSP_ERROR;
        }
    }

    if (BSP_OK != bsp_efuse_write((u32 *)pbuf, EFUSE_GRP_HUK, EFUSE_HUK_SIZE)) {
        efuse_print_error("efuseWrite error!\n");
        return BSP_ERROR;
    }

    efuse_print_info("efuseWriteHUK SUCC!\n");
    return BSP_OK;
}

#else

int mdrv_efuse_read_huk(unsigned char *pbuf, unsigned int len)
{
    return BSP_OK;
}
int mdrv_efuse_write_huk(char *pbuf, unsigned int len)
{
    return OK;
}
int mdrv_efuse_check_huk_valid(void)
{
    return OK;
}

#endif



