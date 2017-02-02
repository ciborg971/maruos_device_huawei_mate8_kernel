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
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/ctype.h>
#include "hi_base.h"

#include "product_config.h"
#include "osl_types.h"
#include "osl_bio.h"

#include "bsp_version.h"
#include "mdrv_version.h"
#include "bsp_memmap.h"

#include <drv_nv_id.h>
#include <drv_nv_def.h>
#include <bsp_nvim.h>
#include <mdrv_misc_comm.h>

MODEM_VER_INFO_S ver_info;

extern PRODUCT_INFO_NV_STRU huawei_product_info;

/*****************************************************************************
* �� �� ��  : BSP_GetBuildVersion
*
* ��������  :
*
* �������  :
* �������  : ��
*
* �� �� ֵ  : ��
*
* �޸ļ�¼  : 2011-3-29 wuzechun creat
*
*****************************************************************************/
MSW_VER_INFO_S * bsp_version_get_build_verinfo(void)
{
#define MAX_VER_SECTION 8
#define VER_PART_LEN 3
#define VERC_PART_LEN 2

    static MSW_VER_INFO_S st = {0,0,0,0,0,0,0,{0},{0}};
	static bool binited = false;
	int ret;

    char * pCur, * pFind;
    char au8Args[MAX_VER_SECTION] = {0};
	u32 verno = 0;

	if(!binited)
	{
		pCur = PRODUCT_VERSION_STR;
	    pFind = pCur;

        memset(&st, 0, sizeof(MSW_VER_INFO_S));

	    while (NULL != (pCur = strchr(pCur, 'V')) )
	    {
	        pCur++;

	        if (isdigit(*(pCur)))
	        {
	            memset(au8Args, 0, MAX_VER_SECTION);
	            strncpy(au8Args, pCur, VER_PART_LEN);
				/* coverity[incompatible_cast] */
				ret = strict_strtoul(au8Args, 10, (unsigned long *)&verno);
				if(ret)
				{
					ver_print_error("kstrtouint error:ret %#x, au8Args:%s\n", ret, au8Args);
					return (&st);
				}
	            st.ulVVerNO = (u16)verno;
	            break;
	        }
	    }
	    pCur = pFind;
	    while (NULL != (pCur = strchr(pFind, 'R')) )
	    {
	        pCur++;

	        if (isdigit(*(pCur-2)) && isdigit(*(pCur)))
	        {
	            memset(au8Args, 0, MAX_VER_SECTION);
	            strncpy(au8Args, pCur, VER_PART_LEN);
                /* coverity[incompatible_cast] */
				ret = strict_strtoul(au8Args, 10, (unsigned long *)&verno);
				if(ret)
				{
					ver_print_error("kstrtouint error:ret %#x, au8Args:%s\n", ret, au8Args);
					return (&st);
				}
	            st.ulRVerNO = (u16)verno;
	            break;
	        }
	    }
	    pCur = pFind;
	    while (NULL != (pCur = strchr(pFind, 'C')) )
	    {
	        pCur++;

	        if (isdigit(*(pCur-2)) && isdigit(*(pCur)))
	        {
	            memset(au8Args, 0, MAX_VER_SECTION);
	            strncpy(au8Args, pCur, VERC_PART_LEN);
	            pCur += VERC_PART_LEN;
                /* coverity[incompatible_cast] */
				ret = strict_strtoul(au8Args, 10, (unsigned long *)&verno);
				if(ret)
				{
					ver_print_error("kstrtouint error:ret %#x, au8Args:%s\n", ret, au8Args);
					return (&st);
				}
	            st.ulCVerNO = (u16)verno;
	            break;
	        }
	    }
	    pCur = pFind;
	    while (NULL != (pCur = strchr(pFind, 'B')) )
	    {
	        pCur++;

	        if (isdigit(*(pCur-2)) && isdigit(*(pCur)))
	        {
	            memset(au8Args, 0, MAX_VER_SECTION);
	            strncpy(au8Args, pCur, VER_PART_LEN);
                /* coverity[incompatible_cast] */
				ret = strict_strtoul(au8Args, 10, (unsigned long *)&verno);
				if(ret)
				{
					ver_print_error("kstrtouint error:ret %#x, au8Args:%s\n", ret, au8Args);
					return (&st);
				}
	            st.ulBVerNO = (u16)verno;
	            break;
	        }
	    }
	    pCur = pFind;
	    while (NULL != (pCur = strstr(pFind, "SPC")) )
	    {
	        pCur+=3;

	        if (isdigit(*(pCur-4)) && isdigit(*(pCur)))
	        {
	            memset(au8Args, 0, MAX_VER_SECTION);
	            strncpy(au8Args, pCur, VER_PART_LEN);
                /* coverity[incompatible_cast] */
				ret = strict_strtoul(au8Args, 10, (unsigned long *)&verno);
				if(ret)
				{
					ver_print_error("kstrtouint error:ret %#x, au8Args:%s\n", ret, au8Args);
					return (&st);
				}
	            st.ulSpcNO = (u16)verno;
	            break;
	        }
	    }

		st.ulProductNo = 0;/*���ߺ�����������Ʒ*/

        /* coverity[buffer_size_warning] */
		strncpy((void *)st.acBuildDate, __DATE__, BUILD_DATE_LEN);

        /* coverity[buffer_size_warning] */
		strncpy((void *)st.acBuildTime, __TIME__, BUILD_TIME_LEN);
	}

	return (&st);
}

/*****************************************************************************
 �� �� ��  : mdrv_ver_get_info
 ��������  : ����modem�汾��Ϣ
 �������  :
 �������  :
 �� �� ֵ  : Modem �汾��Ϣ
****************************************************************************/
const MODEM_VER_INFO_S * mdrv_ver_get_info(void)
{
	return &ver_info;	
}

void mdrv_ver_init(void)
{	
	memset(&ver_info, 0x0, sizeof(MODEM_VER_INFO_S));

	ver_info.stproductinfo.eboardatype   = (BOARD_ACTUAL_TYPE_E)bsp_get_version_info()->board_type;
	ver_info.stproductinfo.echiptype     = V7R2_CHIP;
	ver_info.stproductinfo.eprotype      = bsp_get_board_mode_type();
	ver_info.stproductinfo.productname   = (unsigned char*)bsp_version_get_product_out_name();
	ver_info.stproductinfo.productnamelen= VER_MAX_LENGTH;

	ver_info.sthwverinfo.hwfullver       = (unsigned char*)bsp_version_get_hardware();
	ver_info.sthwverinfo.hwfullverlen    = VER_MAX_LENGTH;
	ver_info.sthwverinfo.hwidsub         = huawei_product_info.hwIdSub;
	ver_info.sthwverinfo.hwindex         = bsp_get_version_info()->board_id;
	ver_info.sthwverinfo.hwinname        = (unsigned char*)bsp_version_get_product_inner_name();
	ver_info.sthwverinfo.hwinnamelen     = VER_MAX_LENGTH;
	ver_info.sthwverinfo.hwname          = (unsigned char*)bsp_version_get_product_out_name();
	ver_info.sthwverinfo.hwnamelen       = VER_MAX_LENGTH;

	memcpy(&(ver_info.stswverinfo), bsp_version_get_build_verinfo(), sizeof(MSW_VER_INFO_S));

	return ;
}


/*lint -save -e64 -e437 -e233 -e713*/
/*****************************************************************************
 �� �� ��  : mdrv_misc_support_check
 ��������  : ��ѯģ���Ƿ�֧��
 �������  : enModuleType: ��Ҫ��ѯ��ģ������
 �������  : ��
 ����ֵ    ��BSP_MODULE_SUPPORT��BSP_MODULE_UNSUPPORT
*****************************************************************************/
BSP_MODULE_SUPPORT_E mdrv_misc_support_check (BSP_MODULE_TYPE_E module_type)
{
    u32 ret;
    bool bSupport = BSP_MODULE_SUPPORT;
    DRV_MODULE_SUPPORT_STRU   stSupportNv = {0};

    if(module_type >= BSP_MODULE_TYPE_BOTTOM)
    {
        return BSP_MODULE_UNSUPPORT;
    }

    ret = bsp_nvm_read(NV_ID_DRV_MODULE_SUPPORT, (u8*)&stSupportNv, (unsigned int)sizeof(DRV_MODULE_SUPPORT_STRU));/*lint !e26 !e119 */
    if(NV_OK != ret)
	{
		(void)memset(&stSupportNv, 0xFF,sizeof(DRV_MODULE_SUPPORT_STRU));
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_HWADP,
			"bsp_nvm_read error, ret %#x, item %#x\n, set to default %#x",
			ret, NV_ID_DRV_MODULE_SUPPORT, stSupportNv);
	}

    switch(module_type)
    {
        case BSP_MODULE_TYPE_SD:
            bSupport = stSupportNv.sdcard;
            break;

        case BSP_MODULE_TYPE_CHARGE:
            bSupport = stSupportNv.charge;
            break;

        case BSP_MODULE_TYPE_WIFI:
            bSupport = stSupportNv.wifi;
            break;

        case BSP_MODULE_TYPE_OLED:
            bSupport = stSupportNv.oled;
            break;

        case BSP_MODULE_TYPE_HIFI:
			bSupport = stSupportNv.hifi;
            break;

        case BSP_MODULE_TYPE_POWER_ON_OFF:
			bSupport = stSupportNv.onoff;
            break;

        case BSP_MODULE_TYPE_HSIC:
			bSupport = stSupportNv.hsic;
            break;

        case BSP_MODULE_TYPE_LOCALFLASH:
			bSupport = stSupportNv.localflash;
            break;

		default:
			bSupport = 0;
    }

    if(bSupport)
        return BSP_MODULE_SUPPORT;
    else
        return BSP_MODULE_UNSUPPORT;
}/* [false alarm]:�� */
/*lint -restore +e64 +e437 +e233 +e713*/


EXPORT_SYMBOL_GPL(bsp_version_get_build_verinfo);

EXPORT_SYMBOL_GPL(mdrv_ver_get_info);

EXPORT_SYMBOL_GPL(mdrv_ver_init);

/***********************************************************************/

