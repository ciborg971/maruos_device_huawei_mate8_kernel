

/*lint --e{537} */
#include <stdio.h>
#include <string.h>
#include <product_config.h>
#include <drv_nv_id.h>
#include <drv_nv_def.h>
#include <bsp_nvim.h>
#include <bsp_dsp.h>

#include "mdrv_dsp.h"
#include <bsp_dspload.h>
/*****************************************************************************
 �ṹ��    : PS_PHY_DYN_ADDR_SHARE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������PS�Ĺ����ַ��OAM��Ҫ��ȡ������TTF���߳�ʼ������PHY��ȡ
*****************************************************************************/
typedef struct
{
    /*������ʼ��,PSֻ��*/
    unsigned int uwProtectWord1;                      /*0x5a5a5a5a*/
    unsigned int uwPhyGttfShareAddr;                  /* GDSP��GTTF�����ڴ�ӿڵ�ַ,������ʼ��*/

    /*PS�����ʼ��,PHYֻ��*/
    unsigned int uwProtectWord2;                      /*0x5a5a5a5a��PS��д*/
    unsigned int uwHsupaUpaccMacePduBaseAddr;         /*HSUPA_UPACC_MACE_PDU_BASE_ADDR*/
    unsigned int uwEcsArmDspBufferSize;               /*ECS_ARM_DSP_BUFFER_SIZE*/
    unsigned int uwSocTimeSliceAddr;                  /*ʱ���ȡ��ַ*/

    /*AXI addr*/
    unsigned int uwStatusFlagAddr;                    /*HIFI/DSP STATUS_FLAG_ADDR*/
    unsigned int uwTempratureAddr;                    /*�±�*/

    unsigned long uwHsdpaWttfBufAddr;                  /* HSDPA WTTF����buf��ַ */
    /*��������չ�á��Ժ���԰�ƽ̨��صĵ�ַ�ŵ����ﴫ�ݽ���*/
    unsigned long uwReserved[15];
}PS_PHY_DYN_ADDR_SHARE_STRU;

/*****************************************************************************
 �ṹ��    : PHY_HIFI_DYN_ADDR_SHARE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������HIFI�Ĺ����ַ��OAM��Ҫ������HIFI��BOOT�����������е���Ӧ�ṹ��
*****************************************************************************/
typedef struct
{
    unsigned int uwProtectWord;           /*0x5a5a5a5a*/
    unsigned int uwHifiPhyMboxHeadAddr;   /*HIFI��PHY�Ĺ��������壬PHY�����ʼ�����뾲̬��ʼ����*/
    unsigned int uwHifiPhyMboxBodyAddr;
    unsigned int uwPhyHifiMboxHeadAddr;   /*PHY��HIFI�Ĺ��������壬PHY�����ʼ�����뾲̬��ʼ����*/
    unsigned int uwPhyHifiMboxBodyAddr;
    unsigned int uwReserved[3];
}PHY_HIFI_DYN_ADDR_SHARE_STRU;

/*****************************************************************************
 �ṹ��    : PS_PHY_DYN_ADDR_SHARE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DSP�ϵ�ʱOAM��Ҫ��DSP��".dsp_share_addr"��д���½ṹ�����ݣ���ʼ��ַ��DRV����ZSP bin���󴫸�OAM
*****************************************************************************/
typedef struct
{
    PS_PHY_DYN_ADDR_SHARE_STRU      stPsPhyDynAddr;     /*PS��PHY�Ĺ��������� */
    PHY_HIFI_DYN_ADDR_SHARE_STRU    stPhyHifiDynAddr;   /*PHY��HIFI�Ĺ��������� */
}DSP_SHARE_ADDR_STRU;

/************************************************************************
 * FUNCTION
 *       BSP_GUDSP_UpateShareInfo
 * DESCRIPTION
 *       ���DSP����Ķ�̬��Ϣ��ȡ�͸��¹���
 * INPUTS
 *       NONE
 * OUTPUTS
 *       BSP_OK/BSP_ERR
 *************************************************************************/
/*lint -save -e586*/
int mdrv_dsp_update_shareinfo(unsigned long shareAddr)
{
    DSP_SHARE_ADDR_STRU      *pstDspShareInfo = (DSP_SHARE_ADDR_STRU*)shareAddr;

    if(0x5A5A5A5A != pstDspShareInfo->stPsPhyDynAddr.uwProtectWord1)
    {
        (void)printf("\r\n BSP_GUDSP_UpateShareInfo: ZSP Share Info uwProtectWord1 Error.");
        return -1;     /*�쳣�˳��������*/
    }

    /*��дL2ʹ�õĵ�ַ�ռ��С*/
    pstDspShareInfo->stPsPhyDynAddr.uwHsupaUpaccMacePduBaseAddr   = DDR_UPA_ADDR;
    pstDspShareInfo->stPsPhyDynAddr.uwEcsArmDspBufferSize         = DDR_UPA_SIZE;

    //pstDspShareInfo->stPsPhyDynAddr.uwHsdpaWttfBufAddr            = ECS_ARM_DSP_BUFFER_BASE_ADDR;

    /*��ǰ��Ϣд����ɱ�־*/
    pstDspShareInfo->stPsPhyDynAddr.uwProtectWord2    = 0x5A5A5A5A;

    return 0;
}

/*****************************************************************************
 �� �� ��  : bsp_dsp_is_hifi_exist
 ��������  : ��ȡCODEC����״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : 1:  CODEC����
             0��CODEC ������
*****************************************************************************/
int bsp_dsp_is_hifi_exist(void)
{
    int ret = 0;
    DRV_MODULE_SUPPORT_STRU   stSupportNv = {0};

    ret = (int)bsp_nvm_read(NV_ID_DRV_MODULE_SUPPORT, (u8*)&stSupportNv, sizeof(DRV_MODULE_SUPPORT_STRU));
    if (ret)
        ret = 0;
    else
        ret = (int)stSupportNv.hifi;

    return ret;
}


int mdrv_dsp_load_bbe(void)
{
    return bsp_bbe_load_muti();
}

int mdrv_dsp_run_bbe(void)
{
    return bsp_bbe_run();
}

int mdrv_dsp_stop_bbe(void)
{
    return bsp_bbe_stop();
}

int mdrv_dsp_unreset_bbe(void)
{
    return bsp_bbe_unreset();
}

int mdrv_dsp_reset_bbe(void)
{
    return bsp_bbe_reset();
}

int mdrv_dsp_enable_clk(void)
{
    return bsp_bbe_clock_enable();
}

int mdrv_dsp_disable_clk(void)
{
    return bsp_bbe_clock_disable();
}

int mdrv_dsp_backup_bbe(void)
{
    return bsp_msp_bbe_store();
}
int mdrv_dsp_restore_bbe(void)
{
    return bsp_msp_bbe_restore();
}

int mdrv_dsp_get_br_status(void)
{
    return bsp_msp_wait_edma_ok();
}

#ifdef CONFIG_CBBE

int mdrv_dsp_load(BSP_DSP_TYPE_E edsptype)
{
    return bsp_bbe_load(edsptype);
}

int mdrv_dsp_run(BSP_DSP_TYPE_E edsptype)
{
    return bsp_bbe_run_ex(edsptype);
}

int mdrv_dsp_stop(BSP_DSP_TYPE_E edsptype)
{
    return bsp_bbe_stop_ex(edsptype);
}

int mdrv_dsp_unreset(BSP_DSP_TYPE_E edsptype)
{
    return bsp_bbe_unreset_ex(edsptype);
}

int mdrv_dsp_reset(BSP_DSP_TYPE_E edsptype)
{
    return bsp_bbe_reset_ex(edsptype);
}

int mdrv_dsp_enable_clock(BSP_DSP_TYPE_E edsptype)
{
    return bsp_bbe_clk_enable(edsptype);
}

int mdrv_dsp_disable_clock(BSP_DSP_TYPE_E edsptype)
{
    return bsp_bbe_clk_disable(edsptype);
}

int mdrv_dsp_backup(BSP_DSP_TYPE_E edsptype)
{
    return bsp_dsp_store_dtcm_normal(edsptype);
}

int mdrv_dsp_restore(BSP_DSP_TYPE_E edsptype)
{
    return bsp_dsp_restore_tcm_normal(edsptype);
}

int mdrv_dsp_wait_backup_over(BSP_DSP_TYPE_E edsptype)
{
    return bsp_dsp_wait_store_over_normal(edsptype);
}

int mdrv_dsp_wait_restore_over(BSP_DSP_TYPE_E edsptype)
{
    return bsp_dsp_wait_restore_over_normal(edsptype);
}

int mdrv_dsp_get_addr_info(BSP_DSP_TYPE_E edsptype, BSP_DSP_ADDR_INFO_STRU *pAddrInfo)
{
    return bsp_dsp_get_addr_info(edsptype, pAddrInfo);
}

#else
int mdrv_dsp_load(BSP_DSP_TYPE_E edsptype)
{
    (void)printf("\r\n error : not support X DSP.\r\n ");
    return 0;
}

int mdrv_dsp_run(BSP_DSP_TYPE_E edsptype)
{
    return 0;
}

int mdrv_dsp_stop(BSP_DSP_TYPE_E edsptype)
{
    return 0;
}

int mdrv_dsp_unreset(BSP_DSP_TYPE_E edsptype)
{
    return 0;
}

int mdrv_dsp_reset(BSP_DSP_TYPE_E edsptype)
{
    return 0;
}

int mdrv_dsp_enable_clock(BSP_DSP_TYPE_E edsptype)
{
    return 0;
}

int mdrv_dsp_disable_clock(BSP_DSP_TYPE_E edsptype)
{
    return 0;
}

int mdrv_dsp_backup(BSP_DSP_TYPE_E edsptype)
{
    return 0;
}

int mdrv_dsp_restore(BSP_DSP_TYPE_E edsptype)
{
    return 0;
}

int mdrv_dsp_wait_backup_over(BSP_DSP_TYPE_E edsptype)
{
    return 0;
}

int mdrv_dsp_wait_restore_over(BSP_DSP_TYPE_E edsptype)
{
    return 0;
}

int mdrv_dsp_get_addr_info(BSP_DSP_TYPE_E edsptype, BSP_DSP_ADDR_INFO_STRU *pAddrInfo)
{
    return 1;
}

#endif



