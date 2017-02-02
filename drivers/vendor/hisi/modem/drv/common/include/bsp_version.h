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
#define DLOAD_VERSION      "2.0"                   /* ����Э��汾 */
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
	u32 board_id;/*Ӳ���汾�ţ�ͨ��hkadc��ȡ��Ŀǰ��Ҫ��NV��ʹ��*/
	u32 board_id_udp_masked;/*��Ʒ��ʵ��ID,��ΪUDP�����ο۰���Ϣ,ios��mbb�µ�dts����*/
	u16 chip_type;/*оƬ���ͣ���CHIP_V711=0x6921*/
	u16 eco_id;/*Լ��eco�汾�ŵĶ������Ϊ�汾����һ��eco��1*/
	u8  plat_type;/*ƽ̨���ͣ���PLAT_ASIC=0x0*/
	u8  is_mbb_udp;/*�ж��Ƿ�ΪMBB�µ�UDP��̬*/
	u8  board_type;/*�����ƽ̨���ͣ���BBIT SOC ASIC SFT*/
	u8  multimode_type;/*�ж��ǵ�ģ���Ƕ�ģ����*/
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

/*VERSIONINFO_I���ݽṹ�а汾�ַ��������Ч�ַ�����*/
#ifndef VER_MAX_LENGTH
#define VER_MAX_LENGTH                  30
#endif

/*memVersionCtrl�ӿڲ�������*/
#define VERIONREADMODE                  0
#define VERIONWRITEMODE                 1

#define HW_VER_PRODUCT_TYPE_MASK	(BSP_U32)0x00FF0000
#define HW_VER_PRODUCT_TYPE_OS		16

/* Ӳ����Ʒ��Ϣ���� */
#define HW_VER_INVALID              (BSP_U32)0XFFFFFFFF

#define HW_VER_PRODUCT_PORTING      (BSP_U32)0X00FFFFFE /* v7r2 Porting��*/
#define HW_VER_PRODUCT_SFT	        (BSP_U32)0x00FFFFFC /* SFT */


#define HW_VER_UDP_MASK				(BSP_U32)0XFF000000 	/*UDP��������*/
#define HW_VER_UDP_UNMASK			(BSP_U32)(~HW_VER_UDP_MASK) /*UDP����ȡ��*/

#define HW_VER_DTS_MASK				(BSP_U32)0XFFFF0000  /* dts mask, the first two bytes */

#define HW_VER_V711_UDP				(BSP_U32)0X71000000 /*V711 UDP*/
#define HW_VER_V750_UDP				(BSP_U32)0X75000000 /*V7R5 UDP*/
#define HW_VER_V722_UDP				(BSP_U32)0X72000000 /*V722 UDP*/
#define HW_VER_K3V5_UDP             (BSP_U32)0X35000000 /*K3V5 UDP*/

#define HW_VER_PXXX            		(BSP_U32)0XFF000000 /*P532*/

/*v711 RF �۰� */
#define HW_VER_V711_UDP_RF_HI6361EVB6_VER_D_RF_T       (BSP_U32)0X71000104/*���Ϊ1j, wangjiaan �ṩ*/


/*оƬ�汾��*/
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
* �� �� ��  	: bsp_get_hardware_version
*
* ��������  	: ��ȡӲ���汾��
*
* �������  	: ��
* �������  	: Ӳ���汾���ַ���ָ��
*
* �� �� ֵ  	: 0��ȡ�ɹ�
			-1��ȡʧ��
*
* �޸ļ�¼  :
*
*****************************************************************************/
char * bsp_version_get_hardware(void);

/*****************************************************************************
* �� �� ��  : bsp_get_product_inner_name
*
* ��������  : ��ȡ�ڲ���Ʒ����
*
* �������  : ��
* �������  :
*
 �� �� ֵ  : �ڲ���Ʒ�����ַ���ָ��
* �޸ļ�¼  :
*
*****************************************************************************/
char * bsp_version_get_product_inner_name(void);

/*****************************************************************************
* �� �� ��  : bsp_get_product_out_name
*
* ��������  : ��ȡ�ڲ���Ʒ����
*
* �������  : ��
* �������  :
*
 �� �� ֵ  : �ⲿ��Ʒ�����ַ���ָ��
* �޸ļ�¼  :
*
*****************************************************************************/
char * bsp_version_get_product_out_name(void);

/*****************************************************************************
* �� �� ��  : bsp_get_pcb_version
*
* ��������  : ��ȡPCB
*
* �������  : ��
* �������  :
*
 �� �� ֵ  : PCB�ַ���ָ��
* �޸ļ�¼  :
*
*****************************************************************************/
char * bsp_version_get_pcb(void);

/*****************************************************************************
* �� �� ��  : bsp_get_dloadid_version
*
* ��������  : ��ȡdloadid
*
* �������  : ��
* �������  :
*
 �� �� ֵ  : dloadid�ַ���ָ��
* �޸ļ�¼  :
*
*****************************************************************************/
char * bsp_version_get_dloadid(void);

/*****************************************************************************
* �� �� ��  : bsp_get_build_date_time
*
* ��������  : ��ȡ�������ں�ʱ��
*
* �������  : ��
* �������  :
*
 �� �� ֵ  : ����汾���ַ���ָ��
* �޸ļ�¼  :
*
*****************************************************************************/
char * bsp_version_get_build_date_time(void);

/*****************************************************************************
* �� �� ��  : bsp_get_chip_version
*
* ��������  : ��ȡоƬ�汾��
*
* �������  : ��
* �������  :
*
 �� �� ֵ  :оƬ�汾���ַ�����ָ��
* �޸ļ�¼  :
*
*****************************************************************************/
char * bsp_version_get_chip(void);

/*****************************************************************************
* �� �� ��  : bsp_get_firmware_version
*
* ��������  : ��ȡ����汾��
*
* �������  : ��
* �������  :
*
 �� �� ֵ  : ����汾���ַ���ָ��
* �޸ļ�¼  :
*
*****************************************************************************/
char * bsp_version_get_firmware(void);

/*****************************************************************************
* �� �� ��  : bsp_get_version_hash
*
* ��������  : ��ȡ������Ŀ��hashֵ
*
* �������  : ��
* �������  :
*
 �� �� ֵ  : ������Ŀ�hashֵ�ַ�����ָ��
* �޸ļ�¼  :
*
*****************************************************************************/
char * bsp_version_get_hash(void);

/*****************************************************************************
* �� �� ��  : bsp_get_iso_version
*
* ��������  : ��ȡiso_version
*
* �������  : ��
* �������  :
*
 �� �� ֵ  : iso_version�ַ�����ָ��
* �޸ļ�¼  :
*
*****************************************************************************/
char * bsp_version_get_iso(void);

/*****************************************************************************
* �� �� ��  : bsp_get_webui_version
*
* ��������  : ��ȡwebui_version
*
* �������  : ��
* �������  :
*
 �� �� ֵ  : webui_version�ַ�����ָ��
* �޸ļ�¼  :
*
*****************************************************************************/
char * bsp_version_get_webui(void);

/*****************************************************************************
* �� �� ��  : bsp_get_release_version
*
* ��������  : ��ȡrelease_version
*
* �������  : ��
* �������  :
*
 �� �� ֵ  : release_version�ַ�����ָ��
* �޸ļ�¼  :
*
*****************************************************************************/
char * bsp_version_get_release(void);

int bsp_dload_get_dload_info(struct dload_info_type* dload_info);


int bsp_version_debug(void);


void bsp_version_init(void);


int bsp_productinfo_init(void);

/*****************************************************************************
* ����	: bsp_get_board_mode_type
* ����	: get board type(GUL or LTE)
* ����	: void
* ���	: void
* ����	: BOARD_TYPE_E
*****************************************************************************/
PROTOCOL_TYPE_E bsp_get_board_mode_type(void);
/*****************************************************************************
* ����	: bsp_get_board_actual_type
* ����	: get board actual type 
* ����	: void
* ���	: void
* ����	: BOARD_ACTUAL_TYPE_E       BBIT/SFT/ASIC
*
* ����       : ��
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

