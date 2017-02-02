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

/*lint --e{537}*/
#ifdef __KERNEL__
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/slab.h>
#endif

#if defined(__OS_VXWORKS__)||defined(__OS_RTOSCK__)
#include <string.h>
#endif

#include <product_config.h>
#include <osl_types.h>
#include <ptable_com.h>
#include <bsp_sram.h>
#include <drv_nv_id.h>
#include <drv_nv_def.h>
#include <bsp_version.h>
#include <bsp_nvim.h>
#include <bsp_sysctrl.h>
#include <bsp_nandc.h>

/*
*--------------------------------------------------------------*
* 宏定义                                                       *
*--------------------------------------------------------------*
*/

/*全局变量，保存产品信息,version 初始化配置nv值*/
PRODUCT_INFO_NV_STRU huawei_product_info =
{
	0
};
/*lint -save -e958*/
static __inline__ int bsp_version_default_set(void)
{
    u32 iret = 0;
	u32 hw_ver;/*硬件版本号*/

	hw_ver = bsp_get_version_info()->board_id;/*get hardware version*/

    /*read nv,get the exc protect setting*/
    /*lint -save -e26 -e119*/
    iret = bsp_nvm_read(NV_ID_DRV_NV_VERSION_INIT,(u8*)&huawei_product_info,sizeof(PRODUCT_INFO_NV_STRU));
	/*lint -restore*/

    if(NV_OK != iret)
    {
        ver_print_error("version init read nv error,not set,use the default config!\n");
        return VER_ERROR;
    }

	/*未查找到hwVer*/
	if(hw_ver!=huawei_product_info.index){
		ver_print_error("product info is not defined, pls check product_info_tbl!HKADC read:0x%x,nv read:0x%x\n",hw_ver,huawei_product_info.index);
		huawei_product_info.index = hw_ver;
		return VER_ERROR;
	}

	return VER_OK;

}
int bsp_productinfo_init(void)
{
	int iret=0;

	/*TODO:后续如果有子版本号，需要适配*/

    /*清除局部结构变量的内存，即初始化为全0*/
    memset((void *)(&huawei_product_info), 0, sizeof(PRODUCT_INFO_NV_STRU));
	iret = bsp_version_default_set();
	if(VER_ERROR==iret){
		ver_print_error("bsp version version_default_set fail!\n");
	}
    show_virtual_boardid();
	ver_print_error("bsp version init OK!\n");

	mdrv_ver_init();

	return iret;
}


char * bsp_version_get_hardware(void)
{
	unsigned int len;
	static bool b_geted=false;
	static char hardware_version[VERSION_MAX_LEN];
	char hardware_sub_ver = 0;

	/*单板为硬核，软核，或者UDP*/
	if((HW_VER_INVALID == huawei_product_info.index))
	{
		ver_print_error("init error\n");
    	return NULL;
	}

	if(!b_geted){
        /*lint -save -e18 -e718 -e746*/
		len = (unsigned int)(strlen(huawei_product_info.hwVer) + strlen(" Ver.X"));
        /*lint -restore*/

	    hardware_sub_ver = (char)huawei_product_info.hwIdSub+'A';

		(void)memset((void *)hardware_version, 0, MemparamType(len));
		/* coverity[secure_coding] */
		strncat(strncat(hardware_version, huawei_product_info.hwVer, strlen(huawei_product_info.hwVer)), " Ver.", strlen(" Ver."));
		*((hardware_version + len) - 1) = hardware_sub_ver;
		*(hardware_version + len) = 0;

		b_geted=true;
	}
	/*子版本号待确认*/

	return (char *)hardware_version;

}
char * bsp_version_get_product_inner_name(void)
{
	unsigned int len;
	static bool b_geted=false;
	static char product_inner_name[VERSION_MAX_LEN];

	if( HW_VER_INVALID == huawei_product_info.index)
	{
		return NULL;
	}

	if(!b_geted){
		len = (unsigned int)(strlen(huawei_product_info.name)+ strlen(huawei_product_info.namePlus));

		(void)memset((void*)product_inner_name, 0, MemparamType(len));

		/* coverity[secure_coding] */
		strncat(strncat(product_inner_name,huawei_product_info.name, strlen(huawei_product_info.name)), huawei_product_info.namePlus, strlen(huawei_product_info.namePlus));

		*(product_inner_name+len) = 0;
		b_geted=true;
	}

	return  (char*)product_inner_name;

}
char * bsp_version_get_product_out_name(void)
{
	if(HW_VER_INVALID == huawei_product_info.index)
	{
		return NULL;
	}

	return (char *)huawei_product_info.productId;
}


char * bsp_version_get_pcb(void)
{
	if(HW_VER_INVALID == huawei_product_info.index)
	{
		return NULL;
	}

	return (char *)huawei_product_info.hwVer;
}


char * bsp_version_get_dloadid(void)
{
	if(HW_VER_INVALID == huawei_product_info.index)
	{
		return NULL;
	}

	return (char *)huawei_product_info.dloadId;
}



char * bsp_version_get_build_date_time(void)
{
	static char * build_date   = __DATE__ ", " __TIME__;
	return build_date;
}


char * bsp_version_get_chip(void)
{
	return (char *)PRODUCT_CFG_CHIP_SOLUTION_NAME;
}


char * bsp_version_get_firmware(void)
{
	u32 iret = VER_OK;
	static NV_SW_VER_STRU nv_sw_ver={0};

	/*读取NV项中的软件版本号*/
    /*lint -save -e26 -e119*/
	iret=bsp_nvm_read(NV_ID_DRV_NV_DRV_VERSION_REPLACE_I, \
				(u8 *)&nv_sw_ver,
				sizeof(NV_SW_VER_STRU));
    /*lint -restore*/

    if(NV_OK != iret){/*如果获取失败，则返回默认版本号*/
		ver_print_info("get NV_SW_VERSION_REPLACE failed!\n");
		return (char*)PRODUCT_DLOAD_SOFTWARE_VER;
	}
	else{
		if(0 == nv_sw_ver.nvStatus){
			ver_print_info("nv_sw_ver.nvStatus :%d\n",nv_sw_ver.nvStatus);
			return (char*)PRODUCT_DLOAD_SOFTWARE_VER;
		}
	}

	return (char *)nv_sw_ver.nv_version_info;
}



char * bsp_version_get_hash(void)
{
	return CFG_PRODUCT_TAG_ID;
}


char * bsp_version_get_iso(void)
{
	/**TODO:  暂时先返回这个数值,后续看isover如何存储*/

	#define ISO_VER "00.000.00.000.00"
	return (char *)ISO_VER;
}
char * bsp_version_get_webui(void)
{
	/**TODO:  同isover*/
	return NULL;
}
char * bsp_version_get_release(void)
{
	/**TODO:  */
	return PRODUCT_FULL_VERSION_STR;
}


/*****************************************************************************
* 函数	: bsp_get_board_mode_type
* 功能	: get board type(GUL or LTE)
* 输入	: void
* 输出	: void
* 返回	: BOARD_TYPE_E
*****************************************************************************/
PROTOCOL_TYPE_E bsp_get_board_mode_type(void)
{
#ifdef BSP_CONFIG_P532_FPGA
	return bsp_get_version_info()->multimode_type;
#endif

#if(defined(FEATURE_MULTIMODE_GUL))
		return PROTOCOL_TYPE_GUL;
#else
		return PROTOCOL_TYPE_LTE_ONLY;
#endif
}

#ifdef __KERNEL__


char* bsp_dload_get_dload_version(void)
{
	return (char *)DLOAD_VERSION;
}


int bsp_dload_get_dload_info(struct dload_info_type* dload_info)
{
	char *dload_iso = NULL;
	char *product_name = NULL;
	char *firmware = NULL;

	/*获取iso version*/
	dload_iso = bsp_version_get_iso();
	if(NULL == dload_iso){
		ver_print_error("get iso ver is null!\n");
		return VER_ERROR;
	}
	/* coverity[secure_coding] */
	strncat(dload_info->iso_ver,dload_iso,strlen(dload_iso));

	/*获取dload id(升级中使用的产品名)*/
	product_name = bsp_version_get_dloadid();
	if(NULL == product_name){
		ver_print_error("get product name is null\n");
		return VER_ERROR;
	}
	/* coverity[secure_coding] */
	strncat(dload_info->product_name,product_name,strlen(product_name));

	/*获取software_version*/
	firmware = bsp_version_get_firmware();
	if(NULL == firmware){
		ver_print_error("get firmware version is null\n");
		return VER_ERROR;
	}
	/* coverity[secure_coding] */
	strncat(dload_info->software_ver,firmware,strlen(firmware));

	return VER_OK;

}

/*需要保证在nv模块初始化之后*/
module_init(bsp_productinfo_init);

#endif

const BSP_VERSION_INFO_S* bsp_get_version_info(void)
{
	return (BSP_VERSION_INFO_S *)(SHM_BASE_ADDR + SHM_OFFSET_VERSION);
}
int bsp_version_debug(void)
{
	int ret=0;

#ifdef __KERNEL__
	struct dload_info_type info={"\0","\0","\0"};
#endif

	/*判断version初始化是否成功*/
	if(huawei_product_info.index == HW_VER_INVALID){
		ver_print_error("huawei_product_info init failed!HW_VERSION_ADDR:0x%x\n",bsp_get_version_info()->board_id);
		return VER_ERROR;
	}

	ver_print_error("\n***************************************************\n");
	ver_print_error("\n*************huawei_product_info*******************\n");
	ver_print_error("\n***************************************************\n");
	ver_print_error("Hardware index :0x%x\n",huawei_product_info.index);
	ver_print_error("hw_Sub_ver     :0x%x\n",huawei_product_info.hwIdSub);
	ver_print_error("Inner name     :%s\n",huawei_product_info.name);
	ver_print_error("name plus      :%s\n",huawei_product_info.namePlus);
	ver_print_error("HardWare ver   :%s\n",huawei_product_info.hwVer);
	ver_print_error("DLOAD_ID       :%s\n",huawei_product_info.dloadId);
	ver_print_error("Out name       :%s\n",huawei_product_info.productId);

	ver_print_error("\n***************************************************\n");
	ver_print_error("\n*************from func get*******************\n");
	ver_print_error("\n***************************************************\n");
	ver_print_error("Board ID       :0x%x\n",bsp_get_version_info()->board_id);
	ver_print_error("Chip Type      :0x%x\n",bsp_get_version_info()->chip_type);
	ver_print_error("Plat Type      :0x%x\n",bsp_get_version_info()->plat_type);
	ver_print_error("eco id         :0x%x\n",bsp_get_version_info()->eco_id);
	ver_print_error("HardWare ver   :%s\n",bsp_version_get_hardware());
	ver_print_error("Inner name     :%s\n",bsp_version_get_product_inner_name());
	ver_print_error("Out name       :%s\n",bsp_version_get_product_out_name());
	ver_print_error("PCB_ver        :%s\n",bsp_version_get_pcb());
	ver_print_error("DLOAD_ID       :%s\n",bsp_version_get_dloadid());
	ver_print_error("Build_time     :%s\n",bsp_version_get_build_date_time());
	ver_print_error("Chip_ver       :%s\n",bsp_version_get_chip());
	ver_print_error("Firmware       :%s\n",bsp_version_get_firmware());
	ver_print_error("CommitID       :%s\n",bsp_version_get_hash());
	ver_print_error("ISO_ver        :%s\n",bsp_version_get_iso());
	ver_print_error("WebUI          :%s\n",bsp_version_get_webui());
	ver_print_error("Release_ver    :%s\n",bsp_version_get_release());
    
	ver_print_error("\n***************************************************\n");
	ver_print_error("\n*************from bsp_get_version_info get*******************\n");
	ver_print_error("\n***************************************************\n");
	ver_print_error("Board ID            :0x%x\n",bsp_get_version_info()->board_id);
	ver_print_error("board_id_udp_masked :0x%x\n",bsp_get_version_info()->board_id_udp_masked);
	ver_print_error("Chip Type           :0x%x\n",bsp_get_version_info()->chip_type);
	ver_print_error("Plat Type           :0x%x\n",bsp_get_version_info()->plat_type);
	ver_print_error("eco id              :0x%x\n",bsp_get_version_info()->eco_id);
	ver_print_error("is_mbb_udp          :0x%x\n",bsp_get_version_info()->is_mbb_udp);
	ver_print_error("board_type(for drv) :0x%x\n",bsp_get_version_info()->board_type);
	ver_print_error("board_type(for mdrv):0x%x\n",(BOARD_ACTUAL_TYPE_E)bsp_get_version_info()->board_type);
	ver_print_error("eco id              :0x%x\n\n",bsp_get_version_info()->multimode_type);

#ifdef __KERNEL__

	ver_print_error("dload_version  :%s\n",bsp_dload_get_dload_version());
	ret=bsp_dload_get_dload_info(&info);
#endif
	return VER_OK|ret;
}
static unsigned get_version_message_from_misc_ptn(misc_ptn_version_info *misc_message)
{
	u32 offset = MISC_VERSION_OFFSET;
    u32 skip_len = 0;

	if (misc_message == NULL)
		return VIRTUAL_BOARDID_MISC_ERROR;

    if (NAND_OK != bsp_nand_read(PTABLE_MISC_NM, offset, (void*)misc_message, (size_t)sizeof(misc_ptn_version_info), &skip_len))
    {
		ver_print_error("[get_misc_message] flash read failed \n");
		return VIRTUAL_BOARDID_MISC_ERROR;
    }

	return VIRTUAL_BOARDID_MISC_OK;
}

void show_virtual_boardid(void)
{
    unsigned error = 0;
    misc_ptn_version_info version_message;
    memset((void *)(&version_message), 0, sizeof(misc_ptn_version_info));
    error = get_version_message_from_misc_ptn(&version_message);
    if(VIRTUAL_BOARDID_MISC_ERROR == error)
        ver_print_error("[get_virtual_boardid]:get_version_message_in_misc_ptn ERROR!\n");
    else
    {    
        ver_print_error("virtual_boardid message are follows:\n");
        if(VIRTUAL_BOARDID_SET_OK == version_message.err_code)
            ver_print_error("VIRTUAL_BOARDID_SET_OK,virtual_boardid : 0x%x\n",version_message.virtual_boardid);
        else
            ver_print_error("err_code : 0x%x\n",version_message.err_code);
        ver_print_error("timestamp : %d\n",version_message.timestamp);
    }
    
    return ;
}

EXPORT_SYMBOL_GPL(huawei_product_info);
EXPORT_SYMBOL_GPL(bsp_productinfo_init);
EXPORT_SYMBOL_GPL(bsp_version_get_hardware);
EXPORT_SYMBOL_GPL(bsp_version_get_product_out_name);
EXPORT_SYMBOL_GPL(bsp_version_get_product_inner_name);
EXPORT_SYMBOL_GPL(bsp_get_version_info);
EXPORT_SYMBOL_GPL(bsp_get_board_mode_type);
EXPORT_SYMBOL_GPL(bsp_version_debug);

/*lint -restore*/

