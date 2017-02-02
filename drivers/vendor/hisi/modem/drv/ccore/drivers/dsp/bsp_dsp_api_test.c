

#include <bsp_om.h>
#include <bsp_dsp.h>
#include <mdrv_dsp.h>


#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 �ṹ��    : PS_PHY_DYN_ADDR_SHARE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������PS�Ĺ����ַ��OAM��Ҫ��ȡ������TTF���߳�ʼ������PHY��ȡ
*****************************************************************************/
typedef struct
{
    /*������ʼ��,PSֻ��*/
    unsigned int uwProtectWord1;                      /*0x5a5a5a5a
 */
    unsigned int uwPhyGttfShareAddr;                  /* GDSP��GTTF�����ڴ�ӿڵ�ַ,������ʼ��
 */

    /*PS�����ʼ��,PHYֻ��*/
    unsigned int uwProtectWord2;                      /*0x5a5a5a5a��PS��д
 */
    unsigned int uwHsupaUpaccMacePduBaseAddr;         /*HSUPA_UPACC_MACE_PDU_BASE_ADDR
 */
    unsigned int uwEcsArmDspBufferSize;               /*ECS_ARM_DSP_BUFFER_SIZE
 */
    unsigned int uwSocTimeSliceAddr;                  /*ʱ���ȡ��ַ
 */

    /*AXI addr*/
    unsigned int uwStatusFlagAddr;                    /*HIFI/DSP STATUS_FLAG_ADDR
 */
    unsigned int uwTempratureAddr;                    /*�±�
 */

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
    unsigned int uwProtectWord;           /*0x5a5a5a5a
 */
    unsigned int uwHifiPhyMboxHeadAddr;   /*HIFI��PHY�Ĺ��������壬PHY�����ʼ�����뾲̬��ʼ����
 */
    unsigned int uwHifiPhyMboxBodyAddr;
    unsigned int uwPhyHifiMboxHeadAddr;   /*PHY��HIFI�Ĺ��������壬PHY�����ʼ�����뾲̬��ʼ����
 */
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

int mdrv_dsp_load_bbe_test(void)
{
    int ret = 0;
    bsp_bbe_reset();
    mdrv_dsp_load_bbe();
    ret = bsp_bbe_is_muti_loaded();
    if( 1 == ret )
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp load bbe ok !\n");
        return 0;
    }
    return -1;
}

int mdrv_dsp_run_bbe_test(void)
{
    bsp_bbe_reset();
    bsp_bbe_load_muti();
    mdrv_dsp_run_bbe();
    if(1 == bsp_bbe_is_run())
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp run bbe ok !\n");
        return 0;
    }
    return -1;
}

int mdrv_dsp_backup_bbe_test(void)
{
    mdrv_dsp_backup_bbe();
    if(1 == bsp_msp_bbe_is_stored())
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp backup bbe ok !\n");
        return 0;
    }
    return -1;
}

int mdrv_dsp_restore_bbe_test(void)
{
    mdrv_dsp_restore_bbe();
    if(1 == bsp_msp_bbe_is_restored())
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp restore bbe ok !\n");
        return 0;
    }
    return -1;
}

int mdrv_dsp_get_br_status_test()
{
    mdrv_dsp_get_br_status();
    if(1 == bsp_msp_is_edma_ok())
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp get br status ok !\n");
        return 0;
    }
    return -1;
}

int mdrv_dsp_stop_bbe_test()
{
    bsp_bbe_reset();
    bsp_bbe_load_muti();
    bsp_bbe_run();
    mdrv_dsp_stop_bbe();
    if(0 == bsp_bbe_is_run())
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp stop bbe ok !\n");
        return 0;
    }
    return -1;
}

int mdrv_dsp_unreset_bbe_test()
{
    mdrv_dsp_unreset_bbe();
    if(1 == bsp_bbe_is_unreset())
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp unreset bbe ok !\n");
        return 0;
    }
    return -1;
}

int mdrv_dsp_reset_bbe_test()
{
    mdrv_dsp_reset_bbe();
    if(0 == bsp_bbe_is_unreset())
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp reset bbe ok !\n");
        return 0;
    }
    return -1;
}

int mdrv_dsp_enable_clk_test()
{
    mdrv_dsp_enable_clk();
    if(1 == bsp_bbe_is_clock_enable())
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp enable bbe clk ok !\n");
        return 0;
    }
    return -1;
}

int mdrv_dsp_disable_clk_test()
{
    mdrv_dsp_disable_clk();
    if(0 == bsp_bbe_is_clock_enable())
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp disable bbe clk ok !\n");
        return 0;
    }
    return -1;
}

int mdrv_dsp_update_shareinfo_test(void)
{
    int ret = 0;
    DSP_SHARE_ADDR_STRU str;
    str.stPsPhyDynAddr.uwProtectWord1 = 0x5a5a5a5a;
    ret = mdrv_dsp_update_shareinfo((unsigned long)&str);
    if(0 != ret)
        return -1;
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "dsp update shareinfo ok !\n");
    str.stPsPhyDynAddr.uwProtectWord1 = 0x0;
    ret = mdrv_dsp_update_shareinfo((unsigned long)&str);
    if(-1 != ret)
        return -1; 
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "\ndsp update shareinfo ok !\n");
    return 0;
}

#ifdef __cplusplus
}
#endif

