
/*************************************************************************
*   ��Ȩ����(C) 1987-2020, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  product_version_info.c
*
*   ��    �� :  zuofenghua
*
*   ��    �� :  ����ά��Ӳ���汾�������Ϣ
*
*   �޸ļ�¼ :  2013��2��23��  v1.00  zuofenghua  ����
*
*************************************************************************/
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
#include "securec.h"
#include <osl_types.h>
#include <bsp_sram.h>
#include <drv_nv_id.h>
#include <drv_nv_def.h>
#include <bsp_version.h>
#include <bsp_nvim.h>
#include <bsp_sysctrl.h>

/*
*--------------------------------------------------------------*
* �궨��                                                       *
*--------------------------------------------------------------*
*/

/*ȫ�ֱ����������Ʒ��Ϣ,version ��ʼ������nvֵ*/
PRODUCT_INFO_NV_STRU huawei_product_info =
{
    0
};
/*lint -save -e958*/
static __inline__ int bsp_version_default_set(void)
{
    u32 iret = 0;
    u32 hw_ver;/*Ӳ���汾��*/

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

    /*δ���ҵ�hwVer*/
    if(hw_ver!=huawei_product_info.index){
        ver_print_error("board_id: HKADC read(0x%x),nv read(0x%x)\n",hw_ver,huawei_product_info.index);
        huawei_product_info.index = hw_ver;
        return VER_ERROR;
    }

    return VER_OK;

}
int bsp_productinfo_init(void)
{
    int iret=0;

    /*TODO:����������Ӱ汾�ţ���Ҫ����*/

    /*����ֲ��ṹ�������ڴ棬����ʼ��Ϊȫ0*/
    (void)memset_s((void *)(&huawei_product_info), sizeof(PRODUCT_INFO_NV_STRU), 0, sizeof(PRODUCT_INFO_NV_STRU));
    iret = bsp_version_default_set();
    if(VER_ERROR==iret){
        ver_print_error("bsp version version_default_set fail!\n");
    }
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

    /*����ΪӲ�ˣ���ˣ�����UDP*/
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
        /*lint -save -e732*/
        (void)memset_s((void *)hardware_version, VERSION_MAX_LEN, 0, MemparamType(len));
        /*lint -restore*/
        /* coverity[secure_coding] */
        (void)strncat_s((char *)strncat_s(hardware_version, VERSION_MAX_LEN, huawei_product_info.hwVer, 
        strlen(huawei_product_info.hwVer)), VERSION_MAX_LEN, " Ver.", strlen(" Ver."));
        *((hardware_version + len) - 1) = hardware_sub_ver;
        *(hardware_version + len) = 0;

        b_geted=true;
    }
    /*�Ӱ汾�Ŵ�ȷ��*/

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
        /*lint -save -e732*/
        (void)memset_s((void*)product_inner_name, VERSION_MAX_LEN, 0, MemparamType(len));
        /*lint -restore*/
        /* coverity[secure_coding] */
        (void)strncat_s((char *)strncat_s(product_inner_name, VERSION_MAX_LEN, huawei_product_info.name, strlen(huawei_product_info.name)), VERSION_MAX_LEN, huawei_product_info.namePlus, strlen(huawei_product_info.namePlus));

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

    /*��ȡNV���е�����汾��*/
    /*lint -save -e26 -e119*/
    iret=bsp_nvm_read(NV_ID_DRV_NV_DRV_VERSION_REPLACE_I, \
                (u8 *)&nv_sw_ver,
                sizeof(NV_SW_VER_STRU));
    /*lint -restore*/

    if(NV_OK != iret){/*�����ȡʧ�ܣ��򷵻�Ĭ�ϰ汾��*/
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
    /**TODO:  ��ʱ�ȷ��������ֵ,������isover��δ洢*/

    #define ISO_VER "00.000.00.000.00"
    return (char *)ISO_VER;
}
char * bsp_version_get_webui(void)
{
    /**TODO:  ͬisover*/
    return NULL;
}
char * bsp_version_get_release(void)
{
    /**TODO:  */
    return PRODUCT_FULL_VERSION_STR;
}

/*****************************************************************************
* ����	: bsp_get_board_mode_type
* ����	: get board type(GUL or LTE)
* ����	: void
* ���	: void
* ����	: BOARD_TYPE_E
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

    /*��ȡiso version*/
    dload_iso = bsp_version_get_iso();
    if(NULL == dload_iso){
        ver_print_error("get iso ver is null!\n");
        return VER_ERROR;
    }
    /* coverity[secure_coding] */
    strncat_s(dload_info->iso_ver,VERSION_MAX_LEN,dload_iso,strlen(dload_iso));

    /*��ȡdload id(������ʹ�õĲ�Ʒ��)*/
    product_name = bsp_version_get_dloadid();
    if(NULL == product_name){
        ver_print_error("get product name is null\n");
        return VER_ERROR;
    }
    /* coverity[secure_coding] */
    strncat_s(dload_info->product_name,VERSION_MAX_LEN,product_name,strlen(product_name));

    /*��ȡsoftware_version*/
    firmware = bsp_version_get_firmware();
    if(NULL == firmware){
        ver_print_error("get firmware version is null\n");
        return VER_ERROR;
    }
    /* coverity[secure_coding] */
    strncat_s(dload_info->software_ver,VERSION_MAX_LEN,firmware,strlen(firmware));

    return VER_OK;

}
/*��Ҫ��֤��nvģ���ʼ��֮��*/
module_init(bsp_productinfo_init);

#endif


const BSP_VERSION_INFO_S* bsp_get_version_info(void)
{
	return (BSP_VERSION_INFO_S *)((u32)SHM_BASE_ADDR + SHM_OFFSET_VERSION);
}
int bsp_version_debug(void)
{
    int ret=0;

#ifdef __KERNEL__
    struct dload_info_type info={"\0","\0","\0"};
#endif

    /*�ж�version��ʼ���Ƿ�ɹ�*/
    if(huawei_product_info.index == HW_VER_INVALID){
        ver_print_error("huawei_product_info init failed!HW_VERSION_ADDR:0x%x\n",bsp_get_version_info()->board_id);
        return VER_ERROR;
    }

    ver_print_error("\n***************************************************\n");
    ver_print_error("\n*************huawei_product_info*******************\n");
    ver_print_error("\n***************************************************\n");
    ver_print_error("Hardware index    :0x%x\n",huawei_product_info.index);
    ver_print_error("hw_Sub_ver        :0x%x\n",huawei_product_info.hwIdSub);
    ver_print_error("Inner name        :%s\n",huawei_product_info.name);
    ver_print_error("name plus         :%s\n",huawei_product_info.namePlus);
    ver_print_error("HardWare ver      :%s\n",huawei_product_info.hwVer);
    ver_print_error("DLOAD_ID          :%s\n",huawei_product_info.dloadId);
    ver_print_error("Out name          :%s\n",huawei_product_info.productId);

    ver_print_error("\n***************************************************\n");
    ver_print_error("\n*************from func get*******************\n");
    ver_print_error("\n***************************************************\n");
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
    ver_print_error("eco id              :0x%x\n",bsp_get_version_info()->multimode_type);
#ifdef __KERNEL__

    ver_print_error("dload_version    :%s\n",bsp_dload_get_dload_version());
    ret=bsp_dload_get_dload_info(&info);
#endif
    return VER_OK|ret;
}
/*lint -restore*/

