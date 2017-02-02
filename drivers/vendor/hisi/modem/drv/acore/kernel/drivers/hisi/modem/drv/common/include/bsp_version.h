/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __BSP_VERSION_H__
#define __BSP_VERSION_H__

#ifdef __cplusplus
extern "C" {
#endif

#if (defined(__OS_VXWORKS__) || defined(__OS_RTOSCK__) || defined(__KERNEL__))
#include <mdrv_version.h>
#endif

#include <bsp_shared_ddr.h>
#include <bsp_om.h>

#define CFG_PRODUCT_TAG_ID "193c25990102eeb27f5ed9243d9a01e144e3efc4"
#define DLOAD_VERSION      "2.0"                   /* 下载协议版本 */
#define VERSION_MAX_LEN    32

#define CHIP_TYPE_MASK 0xffff0000
#define PLAT_TYPE_MASK 0x0000f000
#define ECO_INFO_MASK 0x00000fff

typedef enum
{
	CHIP_P531 = 0x0530,
	CHIP_P532 = 0x0532,
	CHIP_K3V3 = 0x3630,
	CHIP_K3V5 = 0x3650,
	CHIP_K3V6 = 0x3660,
	CHIP_V8R5 = 0x6250,
	CHIP_V711 = 0x6921,
	CHIP_V722 = 0x6932,
	CHIP_V750 = 0x6950
}VERSION_CHIP_TYPE_E;

typedef enum
{
	PLAT_ASIC= 0x0,
	PLAT_PORTING = 0xa,
	PLAT_EMU = 0xe
}VERSION_PLAT_TYPE_E;

typedef enum{
	 BSP_BOARD_TYPE_BBIT    = 0,
	 BSP_BOARD_TYPE_SFT,
	 BSP_BOARD_TYPE_ASIC,
	 BSP_BOARD_TYPE_SOC,
	 BSP_BOARD_TYPE_MAX
}BSP_BOARD_ACTUAL_TYPE_E;

typedef struct
{
	u32 board_id;/*硬件版本号，通过hkadc读取，目前主要是NV在使用*/
	u32 board_id_udp_masked;/*产品版实际ID,若为UDP则屏蔽扣板信息,ios和mbb下的dts在用*/
	u16 chip_type;/*芯片类型，如CHIP_V711=0x6921*/
	u16 eco_id;/*约定eco版本号的定义规则为版本增加一个eco加1*/
	u8  plat_type;/*平台类型，如PLAT_ASIC=0x0*/
	u8  is_mbb_udp;/*判断是否为MBB下的UDP形态*/
	u8  board_type;/*具体的平台类型，如BBIT SOC ASIC SFT*/
	u8  multimode_type;/*判断是单模还是多模类型*/
}BSP_VERSION_INFO_S;

#if defined( __CMSIS_RTOS ) || defined(__FASTBOOT__)
typedef enum{
     PROTOCOL_TYPE_LTE_ONLY    = 0,
     PROTOCOL_TYPE_GUL
}PROTOCOL_TYPE_E;
#endif

#ifndef VER_ERROR
#define VER_ERROR (-1)
#endif

#ifndef VER_OK
#define VER_OK 0
#endif

#ifndef isdigit
#define isdigit(c)      (((c) >= '0') && ((c) <= '9'))
#endif

#if defined(__OS_VXWORKS__) || defined(__OS_RTOSCK__)
#define StrParamType (unsigned int)
#define MemparamType (int)
#else
#define StrParamType (int)
#define MemparamType (unsigned int)
#endif

#define  ver_print_error(fmt, ...)   (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_VERSION, "[version]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define  ver_print_info(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_VERSION, "[version]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof(a)/(sizeof((a)[0])))
#endif

struct dload_info_type{
	char software_ver[VERSION_MAX_LEN];
	char product_name[VERSION_MAX_LEN];
	char iso_ver[VERSION_MAX_LEN];
};

/*VERSIONINFO_I数据结构中版本字符串最大有效字符长度*/
#ifndef VER_MAX_LENGTH
#define VER_MAX_LENGTH                  30
#endif

/*memVersionCtrl接口操作类型*/
#define VERIONREADMODE                  0
#define VERIONWRITEMODE                 1

#define HW_VER_PRODUCT_TYPE_MASK	(BSP_U32)0x00FF0000
#define HW_VER_PRODUCT_TYPE_OS		16

/* 硬件产品信息适配 */
#define HW_VER_INVALID              (BSP_U32)0XFFFFFFFF

#define HW_VER_PRODUCT_PORTING      (BSP_U32)0X00FFFFFE /* v7r2 Porting板*/
#define HW_VER_PRODUCT_SFT	        (BSP_U32)0x00FFFFFC /* SFT */


#define HW_VER_UDP_MASK				(BSP_U32)0XFF000000 	/*UDP单板掩码*/
#define HW_VER_UDP_UNMASK			(BSP_U32)(~HW_VER_UDP_MASK) /*UDP掩码取反*/

#define HW_VER_DTS_MASK				(BSP_U32)0XFFFF0000  /* dts mask, the first two bytes */

#define HW_VER_V711_UDP				(BSP_U32)0X71000000 /*V711 UDP*/
#define HW_VER_V750_UDP				(BSP_U32)0X75000000 /*V7R5 UDP*/
#define HW_VER_V722_UDP				(BSP_U32)0X72000000 /*V722 UDP*/
#define HW_VER_K3V5_UDP             (BSP_U32)0X35000000 /*K3V5 UDP*/

#define HW_VER_PXXX            		(BSP_U32)0XFF000000 /*P532*/

/*v711 RF 扣板 */
#define HW_VER_V711_UDP_RF_HI6361EVB6_VER_D_RF_T       (BSP_U32)0X71000104/*编号为1j, wangjiaan 提供*/


/*芯片版本号*/
#define CHIP_VER_HI6950_ASIC    (BSP_U32)0X69500100
#define CHIP_VER_HI6930_ASIC    (BSP_U32)0X69300100
#define CHIP_VER_HI6921_ASIC    (BSP_U32)0X69210100
#define CHIP_VER_HI3630_ASIC    (BSP_U32)0X36300100
#define CHIP_VER_HI3635_ASIC    (BSP_U32)0X36350100
#define CHIP_VER_P532_ASIC      (BSP_U32)0X05320100
#define CHIP_VER_P531_ASIC      (BSP_U32)0X05300100

#define CHIP_VER_HI6950_SFT     (BSP_U32)0X6950A100
#define CHIP_VER_HI3635_SFT     (BSP_U32)0X3635FFFF

#define CHIP_VER_HI3650_UDP     (BSP_U32)0X36500100
#define CHIP_VER_HI3650_SFT     (BSP_U32)0X3650A100

/*****************************************************************************
* 函 数 名  	: bsp_get_hardware_version
*
* 功能描述  	: 获取硬件版本号
*
* 输入参数  	: 无
* 输出参数  	: 硬件版本号字符串指针
*
* 返 回 值  	: 0获取成功
			-1获取失败
*
* 修改记录  :
*
*****************************************************************************/
char * bsp_version_get_hardware(void);

/*****************************************************************************
* 函 数 名  : bsp_get_product_inner_name
*
* 功能描述  : 获取内部产品名称
*
* 输入参数  : 无
* 输出参数  :
*
 返 回 值  : 内部产品名称字符串指针
* 修改记录  :
*
*****************************************************************************/
char * bsp_version_get_product_inner_name(void);

/*****************************************************************************
* 函 数 名  : bsp_get_product_out_name
*
* 功能描述  : 获取内部产品名称
*
* 输入参数  : 无
* 输出参数  :
*
 返 回 值  : 外部产品名称字符串指针
* 修改记录  :
*
*****************************************************************************/
char * bsp_version_get_product_out_name(void);

/*****************************************************************************
* 函 数 名  : bsp_get_pcb_version
*
* 功能描述  : 获取PCB
*
* 输入参数  : 无
* 输出参数  :
*
 返 回 值  : PCB字符串指针
* 修改记录  :
*
*****************************************************************************/
char * bsp_version_get_pcb(void);

/*****************************************************************************
* 函 数 名  : bsp_get_dloadid_version
*
* 功能描述  : 获取dloadid
*
* 输入参数  : 无
* 输出参数  :
*
 返 回 值  : dloadid字符串指针
* 修改记录  :
*
*****************************************************************************/
char * bsp_version_get_dloadid(void);

/*****************************************************************************
* 函 数 名  : bsp_get_build_date_time
*
* 功能描述  : 获取编译日期和时间
*
* 输入参数  : 无
* 输出参数  :
*
 返 回 值  : 软件版本号字符串指针
* 修改记录  :
*
*****************************************************************************/
char * bsp_version_get_build_date_time(void);

/*****************************************************************************
* 函 数 名  : bsp_get_chip_version
*
* 功能描述  : 获取芯片版本号
*
* 输入参数  : 无
* 输出参数  :
*
 返 回 值  :芯片版本号字符串的指针
* 修改记录  :
*
*****************************************************************************/
char * bsp_version_get_chip(void);

/*****************************************************************************
* 函 数 名  : bsp_get_firmware_version
*
* 功能描述  : 获取软件版本号
*
* 输入参数  : 无
* 输出参数  :
*
 返 回 值  : 软件版本号字符串指针
* 修改记录  :
*
*****************************************************************************/
char * bsp_version_get_firmware(void);

/*****************************************************************************
* 函 数 名  : bsp_get_version_hash
*
* 功能描述  : 获取软件中心库的hash值
*
* 输入参数  : 无
* 输出参数  :
*
 返 回 值  : 软件中心库hash值字符串的指针
* 修改记录  :
*
*****************************************************************************/
char * bsp_version_get_hash(void);

/*****************************************************************************
* 函 数 名  : bsp_get_iso_version
*
* 功能描述  : 获取iso_version
*
* 输入参数  : 无
* 输出参数  :
*
 返 回 值  : iso_version字符串的指针
* 修改记录  :
*
*****************************************************************************/
char * bsp_version_get_iso(void);

/*****************************************************************************
* 函 数 名  : bsp_get_webui_version
*
* 功能描述  : 获取webui_version
*
* 输入参数  : 无
* 输出参数  :
*
 返 回 值  : webui_version字符串的指针
* 修改记录  :
*
*****************************************************************************/
char * bsp_version_get_webui(void);

/*****************************************************************************
* 函 数 名  : bsp_get_release_version
*
* 功能描述  : 获取release_version
*
* 输入参数  : 无
* 输出参数  :
*
 返 回 值  : release_version字符串的指针
* 修改记录  :
*
*****************************************************************************/
char * bsp_version_get_release(void);

int bsp_dload_get_dload_info(struct dload_info_type* dload_info);


int bsp_version_debug(void);


void bsp_version_init(void);


int bsp_productinfo_init(void);

/*****************************************************************************
* 函数	: bsp_get_board_mode_type
* 功能	: get board type(GUL or LTE)
* 输入	: void
* 输出	: void
* 返回	: BOARD_TYPE_E
*****************************************************************************/
PROTOCOL_TYPE_E bsp_get_board_mode_type(void);
/*****************************************************************************
* 函数	: bsp_get_board_actual_type
* 功能	: get board actual type 
* 输入	: void
* 输出	: void
* 返回	: BOARD_ACTUAL_TYPE_E       BBIT/SFT/ASIC
*
* 其它       : 无
*
*****************************************************************************/
const BSP_VERSION_INFO_S* bsp_get_version_info(void);


void mdrv_ver_init(void);

void bsp_set_multimode_type(int gul);
VERSION_CHIP_TYPE_E bsp_version_get_chip_type(void);

#define VIRTUAL_BOARDID_SET_OK      0x12345000
#define VIRTUAL_BOARDID_NO_SET      0x12345001
#define VIRTUAL_BOARDID_CMD_NULL    0x12345002
#define VIRTUAL_BOARDID_ERR_FORMAT  0x12345003
#define VIRTUAL_BOARDID_NV_NOBURN   0x12345004
#define VIRTUAL_BOARDID_SET_FLAG    0x12345005

#define MISC_VERSION_OFFSET 100

typedef struct  {
    unsigned err_code;
    unsigned virtual_boardid;
    unsigned timestamp;
    unsigned set_ok_flag;
} misc_ptn_version_info;

typedef enum {
	VIRTUAL_BOARDID_MISC_OK = 0,
	VIRTUAL_BOARDID_MISC_ERROR,
}virtual_boardid_misc_return_type;

void set_virtual_boardid(char *virtual_boardid);
void show_virtual_boardid(void);
void clear_virtual_boardid(void);
void update_version_boardid(void);



#ifdef __cplusplus
}
#endif

#endif

