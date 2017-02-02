#ifndef _FASTBOOT_VERSION_BALONG_H_
#define _FASTBOOT_VERSION_BALONG_H_

#include <platform.h>
#include "product_config.h"
#include <bsp_version.h>

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof(a)/(sizeof((a)[0])))
#endif



u32 balong_version_get_hw_version(u8* is_udp);

/*****************************************************************************
* 函数	: bsp_get_board_actual_type
* 功能	: get board actual type
* 输入	: void
* 输出	: void
* 返回	: BOARD_ACTUAL_TYPE_E       BBIT/SFT/ASIC
*
* 其它说明  : 无
*
*****************************************************************************/
BSP_BOARD_ACTUAL_TYPE_E bsp_get_board_actual_type(void);

/*****************************************************************************
* 函数	: bsp_version_init
* 功能	: bsp_save_chip_version ;  bsp_save_hw_version
* 输入	: void
* 输出	: void
*
*****************************************************************************/
void bsp_version_init(void);

const BSP_VERSION_INFO_S* bsp_get_version_info(void);

void bsp_set_multimode_type(int gul);


#endif
