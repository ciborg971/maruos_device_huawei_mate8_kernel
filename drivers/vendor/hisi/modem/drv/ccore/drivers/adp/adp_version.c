/*lint --e{537}*/
#include <string.h>
#include <stdio.h>
#include "hi_base.h"

#include "product_config.h"
#include "securec.h"
#include "osl_types.h"
#include "osl_bio.h"

#include "bsp_version.h"
#include "mdrv_version.h"
#include "bsp_memmap.h"

#include <drv_nv_id.h>
#include <drv_nv_def.h>
#include <bsp_nvim.h>
#include <mdrv_misc_comm.h>

typedef struct
{
    unsigned char CompId;                            /* 组件号：参见COMP_TYPE */
    unsigned char CompVer[VER_MAX_LENGTH+1];         /* 最大版本长度 30 字符+ \0 */
}VERSIONINFO;

/*全局变量*/
VERSIONINFO                 verCheckInfo[ VER_INFO_NUM ];
MODEM_VER_INFO_S     ver_info;
extern PRODUCT_INFO_NV_STRU huawei_product_info;

/*****************************************************************************
 函 数 名  : bsp_version_memversion_ctrl
 功能描述  : 组件版本读写接口。
 输入参数  : pcData：当Mode为读的时候，为调用者待保存返回的组件版本信息的内存地址；
                     当Mode为写的时候，为调用者准备写入的组件版本信息的地址。
             ucLength：当Mode为读的时候，为调用者待保存返回的组件版本信息的内存大小；
                       当Mode为写的时候，为调用者准备写入的组件版本信息的字符数（不包括'\0'）。
             ucType：版本信息ID
             ucMode：0：读取指定ID的组件版本信息；1：写入指定ID的组件版本信息。
 输出参数  : 无。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
*****************************************************************************/
/*lint -save -e958*/
int bsp_version_memversion_ctrl(signed char *pcData, unsigned char ucLength, COMP_TYPE_E ucType, unsigned char ucMode)
/*lint -save restore*/
{
	/*lint -save -e958*/
	u8 *lpv_VerTmp;
    u8 liv_Index;
    u8 ucLen;
	/*lint -save restore*/
    if(ucType >= VER_INFO_NUM)
    {
        ver_print_error("Version Info Type Error\n");
        return VER_ERROR;
    }

    if (ucMode > VERIONWRITEMODE)
    {
        ver_print_error("Control Mode Error\n");
        return VER_ERROR;
    }

    ucLen = ucLength;
    if((VERIONWRITEMODE == ucMode)&&(ucLen > VER_MAX_LENGTH))
    {
        ver_print_error("Version Info Length Error\n");
        ucLen = VER_MAX_LENGTH;
    }

    if((VERIONWRITEMODE == ucMode)&&(0 == ucLen))
    {
        /*lint -save -e18 -e718 -e746*/
        ucLen = (u8)(strlen((const char *)pcData)+1);
        /*lint -restore*/
        if(ucLen >= VER_MAX_LENGTH)
        {
            ucLen = VER_MAX_LENGTH;
        }
    }

    if(NULL == pcData)
    {
        ver_print_error("Data Buffer Pointer Null\n");
        return VER_ERROR;
    }

    lpv_VerTmp = (u8 *)verCheckInfo[ucType].CompVer;
    for(liv_Index = 0; liv_Index < ucLen; liv_Index++)
    {
        if(ucMode)
        {
            *(lpv_VerTmp + liv_Index) = *((u8 *)pcData + liv_Index);
        }
        else
        {
            *((u8 *)pcData + liv_Index) = *(lpv_VerTmp + liv_Index);
        }
    }

    return  VER_OK;
}


/********************************************************************************************************************
 函 数 名  : bsp_version_init
 功能描述  :
 输出参数  :
 返 回 值  :
 注意事项  ：
********************************************************************************************************************/
void bsp_version_init(void)
{
	u32 i;
    int ret = 0;

    /*init*/
    (void)memset_s((void *)verCheckInfo, sizeof (verCheckInfo), 0, sizeof (verCheckInfo));
    for( i = 0; i < VER_INFO_NUM; i++)
    {
        verCheckInfo[i].CompId = (u8)i;
    }

    ret |= bsp_version_memversion_ctrl((signed char *)PRODUCT_VERSION_STR, 0 , VER_VXWORKS,(unsigned char)VERIONWRITEMODE);

    /*Read Product ID version infomation*/
    ret |= bsp_version_memversion_ctrl((signed char *)PRODUCT_VERSION_STR ,0 , VER_PRODUCT_ID,(unsigned char)VERIONWRITEMODE);

    /*Read product version infomation*/
    ret |= bsp_version_memversion_ctrl((signed char *)PRODUCT_DLOAD_SOFTWARE_VER, 0, VER_SOFTWARE,(unsigned char)VERIONWRITEMODE);

    /*Read hardware version infomation*/
	if(NULL != bsp_version_get_hardware())
	{
		ret |= bsp_version_memversion_ctrl((signed char *)bsp_version_get_hardware(), 0, VER_HARDWARE,(unsigned char)VERIONWRITEMODE);
	}
    if (VER_ERROR == ret)
    {
        ver_print_error("bsp_version_memversion_ctrl return Error\n");
    }

}

/*****************************************************************************
 函 数 名  : bsp_version_get_verall
 功能描述  : 查询所有组件的版本号。
 输入参数  : ppVersionInfo：待保存的版本信息地址。
 输出参数  : ucLength：待返回的数据的字节数。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
*****************************************************************************/
int mdrv_ver_get_memberinfo (void ** ppVersionInfo, unsigned int * ulLength)
{
    if ((NULL == ppVersionInfo) || (NULL == ulLength))
    {
        return VER_ERROR;
    }

    *ppVersionInfo = verCheckInfo;
    *ulLength = sizeof(verCheckInfo);
    return VER_OK;
}


/*****************************************************************************
 函 数 名  : mdrv_ver_init_platform
 功能描述  : 初始化芯片的版本号
 输入参数  : 无
 输出参数  : none
 返 回 值  : void
*****************************************************************************/
void mdrv_ver_init_platform(void)
{
   return;
}

int mdrv_ver_memberctrl(signed char *pcData, unsigned char ucLength, COMP_TYPE_E ucType, unsigned char ucMode)
{
	return bsp_version_memversion_ctrl(pcData,ucLength,ucType,ucMode);
}

/*****************************************************************************
 函 数 名  : mdrv_ver_get_info
 功能描述  : 返回modem版本信息
 输入参数  :
 输出参数  :
 返 回 值  : Modem 版本信息
****************************************************************************/
const MODEM_VER_INFO_S * mdrv_ver_get_info(void)
{
	return &ver_info;
}

/*lint -save -e64 -e437 -e233 -e713*/
/*****************************************************************************
 函 数 名  : mdrv_misc_support_check
 功能描述  : 查询模块是否支持
 输入参数  : enModuleType: 需要查询的模块类型
 输出参数  : 无
 返回值    ：BSP_MODULE_SUPPORT或BSP_MODULE_UNSUPPORT
*****************************************************************************/
BSP_MODULE_SUPPORT_E mdrv_misc_support_check (BSP_MODULE_TYPE_E module_type)
{
    s32 ret;
    bool bSupport = BSP_MODULE_SUPPORT;
    DRV_MODULE_SUPPORT_STRU   stSupportNv;

    if(module_type >= BSP_MODULE_TYPE_BOTTOM)
    {
        return BSP_MODULE_UNSUPPORT;
    }

    ret = bsp_nvm_read(NV_ID_DRV_MODULE_SUPPORT, (u8*)&stSupportNv, sizeof(DRV_MODULE_SUPPORT_STRU));
    if(NV_OK != ret)
	{
		/*lint --e{18,718,746}*/
		(void)memset_s((void *)&stSupportNv, (u32)sizeof(DRV_MODULE_SUPPORT_STRU), 0xFF,(u32)sizeof(DRV_MODULE_SUPPORT_STRU));

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
}/* [false alarm]:误报 */
/*lint -restore +e64 +e437 +e233 +e713*/

void mdrv_ver_init(void)
{
	(void)memset_s(&ver_info, sizeof(MODEM_VER_INFO_S), 0x0, sizeof(MODEM_VER_INFO_S));

	ver_info.stproductinfo.eboardatype   = (BOARD_ACTUAL_TYPE_E)bsp_get_version_info()->board_type;
	ver_info.stproductinfo.echiptype     = V7R2_CHIP;
	ver_info.stproductinfo.eprotype      = bsp_get_board_mode_type();
	ver_info.stproductinfo.productname   = (unsigned char*)bsp_version_get_product_out_name();
	ver_info.stproductinfo.productnamelen= VER_MAX_LENGTH;

	ver_info.sthwverinfo.hwfullver       = (unsigned char*)bsp_version_get_hardware();
	ver_info.sthwverinfo.hwfullverlen    = VER_MAX_LENGTH;
	ver_info.sthwverinfo.hwidsub         = huawei_product_info.hwIdSub;
	ver_info.sthwverinfo.hwindex         = (int)(bsp_get_version_info()->board_id);
	ver_info.sthwverinfo.hwinname        = (unsigned char*)bsp_version_get_product_inner_name();
	ver_info.sthwverinfo.hwinnamelen     = VER_MAX_LENGTH;
	ver_info.sthwverinfo.hwname          = (unsigned char*)bsp_version_get_product_out_name();
	ver_info.sthwverinfo.hwnamelen       = VER_MAX_LENGTH;

	(void)memcpy_s(ver_info.stswverinfo.acBuildDate, BUILD_DATE_LEN, __DATE__, sizeof(ver_info.stswverinfo.acBuildDate));
	(void)memcpy_s(ver_info.stswverinfo.acBuildTime, BUILD_TIME_LEN, __TIME__, sizeof(ver_info.stswverinfo.acBuildTime));/*[false alarm]*/

	return ;
}


