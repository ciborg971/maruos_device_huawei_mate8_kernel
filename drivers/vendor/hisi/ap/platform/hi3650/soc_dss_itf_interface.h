/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_dss_itf_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:20:09
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_DSS_ITF.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_DSS_ITF_INTERFACE_H__
#define __SOC_DSS_ITF_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_ITF
 ****************************************************************************/
/* �Ĵ���˵����LDI-DPI0ˮƽɨ����ƼĴ���0
   λ����UNION�ṹ:  SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL0_UNION */
#define SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL0_ADDR(base)     ((base) + (0x0000))

/* �Ĵ���˵����LDI-DPI0ˮƽɨ��Ĵ���1
   λ����UNION�ṹ:  SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL1_UNION */
#define SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL1_ADDR(base)     ((base) + (0x0004))

/* �Ĵ���˵����LDI-DPI0ˮƽɨ��Ĵ���2
   λ����UNION�ṹ:  SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL2_UNION */
#define SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL2_ADDR(base)     ((base) + (0x0008))

/* �Ĵ���˵����LDI��ֱɨ����ƼĴ���0
   λ����UNION�ṹ:  SOC_DSS_ITF_LDI_VRT_CTRL0_UNION */
#define SOC_DSS_ITF_LDI_VRT_CTRL0_ADDR(base)          ((base) + (0x000C))

/* �Ĵ���˵����LDI��ֱɨ����ƼĴ���1
   λ����UNION�ṹ:  SOC_DSS_ITF_LDI_VRT_CTRL1_UNION */
#define SOC_DSS_ITF_LDI_VRT_CTRL1_ADDR(base)          ((base) + (0x0010))

/* �Ĵ���˵����LDI��ֱɨ����ƼĴ���2
   λ����UNION�ṹ:  SOC_DSS_ITF_LDI_VRT_CTRL2_UNION */
#define SOC_DSS_ITF_LDI_VRT_CTRL2_ADDR(base)          ((base) + (0x0014))

/* �Ĵ���˵����LDI�źż��Կ��ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_ITF_LDI_PLR_CTRL_UNION */
#define SOC_DSS_ITF_LDI_PLR_CTRL_ADDR(base)           ((base) + (0x0018))

/* �Ĵ���˵����LDI�źż��Կ��ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_ITF_DSS_SH_MASK_INT_UNION */
#define SOC_DSS_ITF_DSS_SH_MASK_INT_ADDR(base)        ((base) + (0x001C))

/* �Ĵ���˵����LDI 3D��ʾ���ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_ITF_LDI_3D_CTRL_UNION */
#define SOC_DSS_ITF_LDI_3D_CTRL_ADDR(base)            ((base) + (0x0020))

/* �Ĵ���˵����LDI���ƼĴ���
            (����PDPר��)
   λ����UNION�ṹ:  SOC_DSS_ITF_LDI_CTRL_UNION */
#define SOC_DSS_ITF_LDI_CTRL_ADDR(base)               ((base) + (0x0024))

/* �Ĵ���˵����LDI����ģʽ���ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_ITF_LDI_WORK_MODE_UNION */
#define SOC_DSS_ITF_LDI_WORK_MODE_ADDR(base)          ((base) + (0x0028))

/* �Ĵ���˵����3D frame by frame��ʽ��active space�׶�DE�ź���Ч���ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_ITF_LDI_DE_SPACE_LOW_UNION */
#define SOC_DSS_ITF_LDI_DE_SPACE_LOW_ADDR(base)       ((base) + (0x002C))

/* �Ĵ���˵����DSI Command(CMD)ģʽ���ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_ITF_DSI_CMD_MOD_CTRL_UNION */
#define SOC_DSS_ITF_DSI_CMD_MOD_CTRL_ADDR(base)       ((base) + (0x0030))

/* �Ĵ���˵����DSI Command(CMD)ģʽTE���ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_ITF_DSI_TE_CTRL_UNION */
#define SOC_DSS_ITF_DSI_TE_CTRL_ADDR(base)            ((base) + (0x0034))

/* �Ĵ���˵����DSI��Ӧ�����üĴ������ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_ITF_DSI_TE_HS_NUM_UNION */
#define SOC_DSS_ITF_DSI_TE_HS_NUM_ADDR(base)          ((base) + (0x0038))

/* �Ĵ���˵����DSI TE PINģʽ���Hsync��ȿ��ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_ITF_DSI_TE_HS_WD_UNION */
#define SOC_DSS_ITF_DSI_TE_HS_WD_ADDR(base)           ((base) + (0x003C))

/* �Ĵ���˵����DSI TE PINģʽ���Vsync��ȿ��ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_ITF_DSI_TE_VS_WD_UNION */
#define SOC_DSS_ITF_DSI_TE_VS_WD_ADDR(base)           ((base) + (0x0040))

/* �Ĵ���˵����LDI֡���ο��ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_ITF_LDI_FRM_MSK_UNION */
#define SOC_DSS_ITF_LDI_FRM_MSK_ADDR(base)            ((base) + (0x0044))

/* �Ĵ���˵����LDI֡ˢ�¿��ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_ITF_LDI_FRM_MSK_UP_UNION */
#define SOC_DSS_ITF_LDI_FRM_MSK_UP_ADDR(base)         ((base) + (0x0048))

/* �Ĵ���˵����v_inactive���μĴ���
   λ����UNION�ṹ:  SOC_DSS_ITF_LDI_VINACT_MSK_LEN_UNION */
#define SOC_DSS_ITF_LDI_VINACT_MSK_LEN_ADDR(base)     ((base) + (0x0050))

/* �Ĵ���˵����LDIѡ���CMD������жϼĴ���
   λ����UNION�ṹ:  SOC_DSS_ITF_LDI_CMD_EVENT_SEL_UNION */
#define SOC_DSS_ITF_LDI_CMD_EVENT_SEL_ADDR(base)      ((base) + (0x0060))

/* �Ĵ���˵����SRAM�͹��Ŀ��ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_ITF_SRAM_LP_CTRL_UNION */
#define SOC_DSS_ITF_SRAM_LP_CTRL_ADDR(base)           ((base) + (0x0064))

/* �Ĵ���˵������Ӱ�ӼĴ���ѡ���ź�
   λ����UNION�ṹ:  SOC_DSS_ITF_ITF_RD_SHADOW_UNION */
#define SOC_DSS_ITF_ITF_RD_SHADOW_ADDR(base)          ((base) + (0x006C))

/* �Ĵ���˵����LDI-DPI1ˮƽɨ����ƼĴ���0
   λ����UNION�ṹ:  SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL0_UNION */
#define SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL0_ADDR(base)     ((base) + (0x00F0))

/* �Ĵ���˵����LDI-DPI1ˮƽɨ��Ĵ���1
            (˫mipiר��)
   λ����UNION�ṹ:  SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL1_UNION */
#define SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL1_ADDR(base)     ((base) + (0x00F4))

/* �Ĵ���˵����LDI-DPI1ˮƽɨ��Ĵ���1
            (˫mipiר��)
   λ����UNION�ṹ:  SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL2_UNION */
#define SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL2_ADDR(base)     ((base) + (0x00F8))

/* �Ĵ���˵����LDI˫dpiģʽoverlap�ߴ�Ĵ���
            (˫mipiר��)
   λ����UNION�ṹ:  SOC_DSS_ITF_LDI_OVERLAP_SIZE_UNION */
#define SOC_DSS_ITF_LDI_OVERLAP_SIZE_ADDR(base)       ((base) + (0x00FC))

/* �Ĵ���˵����MEM�͹��Ŀ��ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_ITF_LDI_MEM_CTRL_UNION */
#define SOC_DSS_ITF_LDI_MEM_CTRL_ADDR(base)           ((base) + (0x0100))

/* �Ĵ���˵����һ��ģ��ʱ��ѡ���ź�
   λ����UNION�ṹ:  SOC_DSS_ITF_LDI_CLK_SEL_UNION */
#define SOC_DSS_ITF_LDI_CLK_SEL_ADDR(base)            ((base) + (0x0108))

/* �Ĵ���˵����һ��ģ��ʱ��ʹ���ź�
   λ����UNION�ṹ:  SOC_DSS_ITF_LDI_CLK_EN_UNION */
#define SOC_DSS_ITF_LDI_CLK_EN_ADDR(base)             ((base) + (0x010C))

/* �Ĵ���˵����sram bypassѡ���ź�
   λ����UNION�ṹ:  SOC_DSS_ITF_LDI_IF_BYPASS_UNION */
#define SOC_DSS_ITF_LDI_IF_BYPASS_ADDR(base)          ((base) + (0x0110))

/* �Ĵ���˵����ģ��Ӱ�ӼĴ����ָ���Ĭ��ֵ
   λ����UNION�ṹ:  SOC_DSS_ITF_REG_DEFAULT_UNION */
#define SOC_DSS_ITF_REG_DEFAULT_ADDR(base)            ((base) + (0x0114))

/* �Ĵ���˵����ģ��Ӱ�ӼĴ����ָ���Ĭ��ֵ
   λ����UNION�ṹ:  SOC_DSS_ITF_FRM_VALID_DBG_UNION */
#define SOC_DSS_ITF_FRM_VALID_DBG_ADDR(base)          ((base) + (0x0118))

/* �Ĵ���˵����LDI��crcУ����
   λ����UNION�ṹ:  SOC_DSS_ITF_CRC_DBG_ITF_UNION */
#define SOC_DSS_ITF_CRC_DBG_ITF_ADDR(base)            ((base) + (0x0200))

/* �Ĵ���˵����LDI��CRC����ʹ���ź�
   λ����UNION�ṹ:  SOC_DSS_ITF_CRC_ITF_EN_UNION */
#define SOC_DSS_ITF_CRC_ITF_EN_ADDR(base)             ((base) + (0x0204))

/* �Ĵ���˵����LDI�ϱ���CRCУ���֡��
   λ����UNION�ṹ:  SOC_DSS_ITF_CRC_ITF_FRM_UNION */
#define SOC_DSS_ITF_CRC_ITF_FRM_ADDR(base)            ((base) + (0x0208))





/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/



/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/



/*****************************************************************************
  6 STRUCT����
*****************************************************************************/



/*****************************************************************************
  7 UNION����
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_ITF
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL0_UNION
 �ṹ˵��  : LDI_DPI0_HRZ_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: LDI-DPI0ˮƽɨ����ƼĴ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpi0_hfp : 13; /* bit[0-12] : ��ǰ����ʱ�����ã�д�����ʵ��ֵ���к�����ȡֵ��Χ0~4095;
                                                    �к�����Ϊһ����Ч���ݽ�����ˮƽͬ���ź�ldi_hsync��Ч���ʱ���ڵ�����ʱ�Ӹ��� */
        unsigned int  reserved_0: 3;  /* bit[13-15]:  */
        unsigned int  dpi0_hbp : 13; /* bit[16-28]: �к�����ʱ�����ã�д�����ʵ��ֵ���к�������ȡֵ��ΧΪ0~4095 */
        unsigned int  reserved_1: 3;  /* bit[29-31]:  */
    } reg;
} SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL0_UNION;
#endif
#define SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL0_dpi0_hfp_START  (0)
#define SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL0_dpi0_hfp_END    (12)
#define SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL0_dpi0_hbp_START  (16)
#define SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL0_dpi0_hbp_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL1_UNION
 �ṹ˵��  : LDI_DPI0_HRZ_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: LDI-DPI0ˮƽɨ��Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpi0_hsw : 13; /* bit[0-12] : ˮƽͬ���������ã�д���ֵΪʵ��ֵ��1��Ľ����ˮƽͬ������Ŀ��������ʱ��Ϊ��λ��ȡֵ��ΧΪ1~4096 */
        unsigned int  reserved : 19; /* bit[13-31]:  */
    } reg;
} SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL1_UNION;
#endif
#define SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL1_dpi0_hsw_START  (0)
#define SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL1_dpi0_hsw_END    (12)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL2_UNION
 �ṹ˵��  : LDI_DPI0_HRZ_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: LDI-DPI0ˮƽɨ��Ĵ���2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpi0_hsize : 13; /* bit[0-12] : ˮƽ�ߴ�Ĵ�����д���ֵΪʵ��ֵ��1��Ľ�� */
        unsigned int  reserved   : 19; /* bit[13-31]: ���� */
    } reg;
} SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL2_UNION;
#endif
#define SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL2_dpi0_hsize_START  (0)
#define SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL2_dpi0_hsize_END    (12)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_LDI_VRT_CTRL0_UNION
 �ṹ˵��  : LDI_VRT_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: LDI��ֱɨ����ƼĴ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vfp      : 13; /* bit[0-12] : ֡ǰ����ʱ�����ã�д�����ʵ��ֵ��ȡֵ��ΧΪ0~4095;
                                                    ֡ǰ����Ϊ��Ч���ݽ�����֡ͬ���ź�ldi_vsync��Ч���ʱ���ڵ�����ɨ������ */
        unsigned int  reserved_0: 3;  /* bit[13-15]:  */
        unsigned int  vbp      : 13; /* bit[16-28]: ֡������ʱ�����ã�д�����ʵ��ֵ��ȡֵ��ΧΪ0~4095.
                                                    ֡������Ϊ֡ͬ���ź�ldi_vsync��Ч��һ֡��Ч���ݿ�ʼ���ʱ���ڵ�����ɨ������. */
        unsigned int  reserved_1: 3;  /* bit[29-31]:  */
    } reg;
} SOC_DSS_ITF_LDI_VRT_CTRL0_UNION;
#endif
#define SOC_DSS_ITF_LDI_VRT_CTRL0_vfp_START       (0)
#define SOC_DSS_ITF_LDI_VRT_CTRL0_vfp_END         (12)
#define SOC_DSS_ITF_LDI_VRT_CTRL0_vbp_START       (16)
#define SOC_DSS_ITF_LDI_VRT_CTRL0_vbp_END         (28)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_LDI_VRT_CTRL1_UNION
 �ṹ˵��  : LDI_VRT_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: LDI��ֱɨ����ƼĴ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vsw      : 13; /* bit[0-12] : ֡ͬ�����������ã�д���ֵΪʵ��ֵ��1�Ľ����֡ͬ������������ɨ������Ϊ��λ,ȡֵ��ΧΪ1~4096 */
        unsigned int  reserved : 19; /* bit[13-31]:  */
    } reg;
} SOC_DSS_ITF_LDI_VRT_CTRL1_UNION;
#endif
#define SOC_DSS_ITF_LDI_VRT_CTRL1_vsw_START       (0)
#define SOC_DSS_ITF_LDI_VRT_CTRL1_vsw_END         (12)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_LDI_VRT_CTRL2_UNION
 �ṹ˵��  : LDI_VRT_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: LDI��ֱɨ����ƼĴ���2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vsize    : 13; /* bit[0-12] : ��ֱ�ߴ�Ĵ�����д���ֵΪʵ��ֵ��1��Ľ�� */
        unsigned int  reserved : 19; /* bit[13-31]: ���� */
    } reg;
} SOC_DSS_ITF_LDI_VRT_CTRL2_UNION;
#endif
#define SOC_DSS_ITF_LDI_VRT_CTRL2_vsize_START     (0)
#define SOC_DSS_ITF_LDI_VRT_CTRL2_vsize_END       (12)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_LDI_PLR_CTRL_UNION
 �ṹ˵��  : LDI_PLR_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: LDI�źż��Կ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vsync_plr     : 1;  /* bit[0]   : ֡ͬ���ź�ldi_vsync_o��Ч���ԣ�
                                                        0��ldi_vsync_o����Ч��
                                                        1��ldi_hsync_o����Ч */
        unsigned int  hsync_plr     : 1;  /* bit[1]   : ��ͬ���ź�ldi_hsync_o��Ч���ԣ�
                                                        0��ldi_hsync_o����Ч��
                                                        1��ldi_hsync_o����Ч */
        unsigned int  pixel_clk_plr : 1;  /* bit[2]   : ����ʱ��ldi_pixel_clk��Ч���ԣ�
                                                        0��ldi_pixel_clk��������Ч��
                                                        1��ldi_pixel_clk�½�����Ч */
        unsigned int  data_en_plr   : 1;  /* bit[3]   : ������Ч�ź�ldi_data_en_o��Ч����:
                                                        0��ldi_data_en_o����Ч��
                                                        1��ldi_data_en_o����Ч */
        unsigned int  reserved      : 28; /* bit[4-31]:  */
    } reg;
} SOC_DSS_ITF_LDI_PLR_CTRL_UNION;
#endif
#define SOC_DSS_ITF_LDI_PLR_CTRL_vsync_plr_START      (0)
#define SOC_DSS_ITF_LDI_PLR_CTRL_vsync_plr_END        (0)
#define SOC_DSS_ITF_LDI_PLR_CTRL_hsync_plr_START      (1)
#define SOC_DSS_ITF_LDI_PLR_CTRL_hsync_plr_END        (1)
#define SOC_DSS_ITF_LDI_PLR_CTRL_pixel_clk_plr_START  (2)
#define SOC_DSS_ITF_LDI_PLR_CTRL_pixel_clk_plr_END    (2)
#define SOC_DSS_ITF_LDI_PLR_CTRL_data_en_plr_START    (3)
#define SOC_DSS_ITF_LDI_PLR_CTRL_data_en_plr_END      (3)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_DSS_SH_MASK_INT_UNION
 �ṹ˵��  : DSS_SH_MASK_INT �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000000�����:32
 �Ĵ���˵��: LDI�źż��Կ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dss_sh_mask_int : 14; /* bit[0-13] : sensor hub���ж����μĴ�������Ӧitf�ϱ���14���ж��ź�
                                                           0����ʾ����
                                                           1����ʾ������ */
        unsigned int  reserved        : 18; /* bit[14-31]:  */
    } reg;
} SOC_DSS_ITF_DSS_SH_MASK_INT_UNION;
#endif
#define SOC_DSS_ITF_DSS_SH_MASK_INT_dss_sh_mask_int_START  (0)
#define SOC_DSS_ITF_DSS_SH_MASK_INT_dss_sh_mask_int_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_LDI_3D_CTRL_UNION
 �ṹ˵��  : LDI_3D_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: LDI 3D��ʾ���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  active_space : 13; /* bit[0-12] : ֡��֮֡���active spaceʱ�����ã�д��Ϊʵ��ֵ��ȡֵ��ΧΪ0~4095����ֻ����3D ��ʾframe by frame��ʽ��;Active space����ɨ������Ϊ��λ */
        unsigned int  reserved     : 19; /* bit[13-31]:  */
    } reg;
} SOC_DSS_ITF_LDI_3D_CTRL_UNION;
#endif
#define SOC_DSS_ITF_LDI_3D_CTRL_active_space_START  (0)
#define SOC_DSS_ITF_LDI_3D_CTRL_active_space_END    (12)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_LDI_CTRL_UNION
 �ṹ˵��  : LDI_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x00000ED0�����:32
 �Ĵ���˵��: LDI���ƼĴ���
            (����PDPר��)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ldi_en         : 1;  /* bit[0]    : LDIʹ�� */
        unsigned int  disp_mode_buf  : 1;  /* bit[1]    : ��ʾģʽ��
                                                          0��2D ��ʾģʽ����3D��ʾʱ��frame by frameģʽ��Ĭ�����ã�
                                                          1��3D frame by frameģʽ�� */
        unsigned int  data_gate_en   : 1;  /* bit[2]    : ������Ч�ź��ſع���ʹ�ܡ�
                                                          0����ʹ�ܣ�
                                                          1��ʹ�ܣ� */
        unsigned int  bpp            : 2;  /* bit[3-4]  : ��������������á�
                                                          00������RGB565���ظ�ʽ��
                                                          01������RGB666���ظ�ʽ��
                                                          10������RGB888���ظ�ʽ��
                                                          11������ */
        unsigned int  dual_mode_en   : 1;  /* bit[5]    : ��/˫dpiѡ���źţ�
                                                          0����dpi���
                                                          1��˫dpi���
                                                          (PDPר��) */
        unsigned int  colorbar_width : 7;  /* bit[6-12] : colorbar RGB������ȣ�д��ֵΪʵ��ֵ��1��ȡֵ��ΧΪ1~128 */
        unsigned int  bgr            : 1;  /* bit[13]   : RGB�������:
                                                          0����ͨ��RGB�����ʽ��
                                                          1��BGR�����ʽ��Blue��Red�����Ե��� */
        unsigned int  color_mode     : 1;  /* bit[14]   : ��DSI DPI�ӿڵ�Color Mode�źţ�
                                                          0�� Full color Mode;
                                                          1�� Reduced Color Mode */
        unsigned int  shutdown       : 1;  /* bit[15]   : ��DSI DPI�ӿڵ�shutdown�źţ�
                                                          0�� LCD������ʾ;
                                                          1�� LCD����Sleepģʽ */
        unsigned int  split_mode     : 1;  /* bit[16]   : ˫dpi���ģʽѡ���źţ�
                                                          0������ģʽ
                                                          1����żģʽ
                                                          (PDPר��) */
        unsigned int  dpi0_rs_clear  : 1;  /* bit[17]   : �����DPI0_RS��clear�źţ�����Ч
                                                          (PDPר��) */
        unsigned int  dpi1_rs_clear  : 1;  /* bit[18]   : �����DPI1_RS��clear�źţ�����Ч
                                                          (PDPר��) */
        unsigned int  reserved       : 13; /* bit[19-31]:  */
    } reg;
} SOC_DSS_ITF_LDI_CTRL_UNION;
#endif
#define SOC_DSS_ITF_LDI_CTRL_ldi_en_START          (0)
#define SOC_DSS_ITF_LDI_CTRL_ldi_en_END            (0)
#define SOC_DSS_ITF_LDI_CTRL_disp_mode_buf_START   (1)
#define SOC_DSS_ITF_LDI_CTRL_disp_mode_buf_END     (1)
#define SOC_DSS_ITF_LDI_CTRL_data_gate_en_START    (2)
#define SOC_DSS_ITF_LDI_CTRL_data_gate_en_END      (2)
#define SOC_DSS_ITF_LDI_CTRL_bpp_START             (3)
#define SOC_DSS_ITF_LDI_CTRL_bpp_END               (4)
#define SOC_DSS_ITF_LDI_CTRL_dual_mode_en_START    (5)
#define SOC_DSS_ITF_LDI_CTRL_dual_mode_en_END      (5)
#define SOC_DSS_ITF_LDI_CTRL_colorbar_width_START  (6)
#define SOC_DSS_ITF_LDI_CTRL_colorbar_width_END    (12)
#define SOC_DSS_ITF_LDI_CTRL_bgr_START             (13)
#define SOC_DSS_ITF_LDI_CTRL_bgr_END               (13)
#define SOC_DSS_ITF_LDI_CTRL_color_mode_START      (14)
#define SOC_DSS_ITF_LDI_CTRL_color_mode_END        (14)
#define SOC_DSS_ITF_LDI_CTRL_shutdown_START        (15)
#define SOC_DSS_ITF_LDI_CTRL_shutdown_END          (15)
#define SOC_DSS_ITF_LDI_CTRL_split_mode_START      (16)
#define SOC_DSS_ITF_LDI_CTRL_split_mode_END        (16)
#define SOC_DSS_ITF_LDI_CTRL_dpi0_rs_clear_START   (17)
#define SOC_DSS_ITF_LDI_CTRL_dpi0_rs_clear_END     (17)
#define SOC_DSS_ITF_LDI_CTRL_dpi1_rs_clear_START   (18)
#define SOC_DSS_ITF_LDI_CTRL_dpi1_rs_clear_END     (18)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_LDI_WORK_MODE_UNION
 �ṹ˵��  : LDI_WORK_MODE �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x00000001�����:32
 �Ĵ���˵��: LDI����ģʽ���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  work_mode    : 1;  /* bit[0]   : ����ģʽ��
                                                       0��COLORBARģʽ:LDI�ڲ��Զ������졢�̡����ʴ��� ����LCD�����ԣ�
                                                       1����������ģʽ */
        unsigned int  colorbar_ort : 1;  /* bit[1]   : colorbar����ѡ���źţ�
                                                       0�� ����
                                                       1�� ���� */
        unsigned int  reserved     : 30; /* bit[2-31]:  */
    } reg;
} SOC_DSS_ITF_LDI_WORK_MODE_UNION;
#endif
#define SOC_DSS_ITF_LDI_WORK_MODE_work_mode_START     (0)
#define SOC_DSS_ITF_LDI_WORK_MODE_work_mode_END       (0)
#define SOC_DSS_ITF_LDI_WORK_MODE_colorbar_ort_START  (1)
#define SOC_DSS_ITF_LDI_WORK_MODE_colorbar_ort_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_LDI_DE_SPACE_LOW_UNION
 �ṹ˵��  : LDI_DE_SPACE_LOW �Ĵ����ṹ���塣��ַƫ����:0x002C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 3D frame by frame��ʽ��active space�׶�DE�ź���Ч���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  de_space_low : 1;  /* bit[0]   : DE�ź���active space�׶��Ƿ���Ч��
                                                       0��DE�ź���active space�׶�Ϊ�ߣ�
                                                       1��DE�ź���active space�׶�Ϊ�ͣ�
                                                       �üĴ���ֻ��3D frame by frame��ʽ����Ч��2D��ʽ����Ч */
        unsigned int  reserved     : 31; /* bit[1-31]:  */
    } reg;
} SOC_DSS_ITF_LDI_DE_SPACE_LOW_UNION;
#endif
#define SOC_DSS_ITF_LDI_DE_SPACE_LOW_de_space_low_START  (0)
#define SOC_DSS_ITF_LDI_DE_SPACE_LOW_de_space_low_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_DSI_CMD_MOD_CTRL_UNION
 �ṹ˵��  : DSI_CMD_MOD_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0030����ֵ:0x00000000�����:32
 �Ĵ���˵��: DSI Command(CMD)ģʽ���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsi_halt_cmd_en   : 1;  /* bit[0]   : ��CMDģʽ��HALT�źŵ�ʹ��
                                                            0����ʹ��Halt�źţ����ڲ���������ź�
                                                            1��ʹ��Halt�ź� */
        unsigned int  dsi_halt_video_en : 1;  /* bit[1]   : ��Videoģʽ��HALT�źŵ�ʹ��,����last line����ʹ��
                                                            0����ʹ��Halt�źţ����ڲ���������ź�
                                                            1��ʹ��Halt�ź� */
        unsigned int  dsi_wms_3d_mode   : 1;  /* bit[2]   : ��3Dģʽ��WMS�źŵ�ģʽ��frame by frame��
                                                            0 ����WMSģʽ
                                                            1 ����WMSģʽ */
        unsigned int  reserved          : 29; /* bit[3-31]:  */
    } reg;
} SOC_DSS_ITF_DSI_CMD_MOD_CTRL_UNION;
#endif
#define SOC_DSS_ITF_DSI_CMD_MOD_CTRL_dsi_halt_cmd_en_START    (0)
#define SOC_DSS_ITF_DSI_CMD_MOD_CTRL_dsi_halt_cmd_en_END      (0)
#define SOC_DSS_ITF_DSI_CMD_MOD_CTRL_dsi_halt_video_en_START  (1)
#define SOC_DSS_ITF_DSI_CMD_MOD_CTRL_dsi_halt_video_en_END    (1)
#define SOC_DSS_ITF_DSI_CMD_MOD_CTRL_dsi_wms_3d_mode_START    (2)
#define SOC_DSS_ITF_DSI_CMD_MOD_CTRL_dsi_wms_3d_mode_END      (2)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_DSI_TE_CTRL_UNION
 �ṹ˵��  : DSI_TE_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x00000100�����:32
 �Ĵ���˵��: DSI Command(CMD)ģʽTE���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsi_te_hard_en    : 1;  /* bit[0]    : TEģʽʹ���ź�
                                                             0����ʹ��TEģʽ
                                                             1��ʹ��TEģʽ��LDI����ź�ʱ��������TE�ź�
                                                             ÿ����TE Maskģʽ�����ǰ�������FRC��֡���л�����ģʽ���͹�ʱ��Ҫ��Disable����Ĵ����� */
        unsigned int  dsi_te0_pin_p     : 1;  /* bit[1]    : TE0 ����ѡ��
                                                             0���������뼫��
                                                             1�����뼫��ȡ�� */
        unsigned int  dsi_te1_pin_p     : 1;  /* bit[2]    : TE1 ����ѡ��
                                                             0���������뼫��
                                                             1�����뼫��ȡ�� */
        unsigned int  dsi_te_hard_sel   : 1;  /* bit[3]    : TEӲ��ģʽԴѡ��
                                                             0���ӹܽ������TE PINԴ
                                                             1����MIPI�ӿ��϶���TE TriggerԴ */
        unsigned int  dsi_te_tri_sel    : 2;  /* bit[4-5]  : TEӲ��ģʽ�£�DSI TE triger�ź�ѡ��
                                                             2'b01��DSI0 TE TRIGER
                                                             2'b10��DSI1 TE TRIGER
                                                             2'b11��DSI0 TE TRIGER | DSI1 TE TRIGER */
        unsigned int  dsi_te_pin_hd_sel : 2;  /* bit[6-7]  : TEӲ��ģʽ�£�TE PINѡ��
                                                             2'b01��TE0 PIN
                                                             2'b10��TE1 PIN
                                                             2'b11��TE0 PIN | TE1 PIN */
        unsigned int  dsi_te_mask_en    : 1;  /* bit[8]    : TE����ʹ�ܣ�ֻ����Hardģʽ��softģʽֻ������жϼ��ɣ�����˹��ܣ�
                                                             0������TE�źŹر�
                                                             1������TE�źŹ��ܴ� */
        unsigned int  dsi_te_mask_dis   : 4;  /* bit[9-12] : TE����ʱ��ʾ��TE����
                                                             �������6ʱ����ʼ��6��TE�ź���ʾ���ݵ����� */
        unsigned int  dsi_te_mask_und   : 4;  /* bit[13-16]: TE����ʱ���ε�TE����
                                                             �������6ʱ��������ʾ��TE���������6��TE�źű����� */
        unsigned int  dsi_te_pin_en     : 1;  /* bit[17]   : ��CMDģʽ����TE PIN���ܽţ����ʹ��
                                                             0 �ر�TE PIN����߼�������Videoģʽ��CMDģʽ����TE PIN����
                                                             1 ����TE PIN����߼�������CMDģʽ������TE PIN���� */
        unsigned int  reserved          : 14; /* bit[18-31]:  */
    } reg;
} SOC_DSS_ITF_DSI_TE_CTRL_UNION;
#endif
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_hard_en_START     (0)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_hard_en_END       (0)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te0_pin_p_START      (1)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te0_pin_p_END        (1)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te1_pin_p_START      (2)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te1_pin_p_END        (2)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_hard_sel_START    (3)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_hard_sel_END      (3)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_tri_sel_START     (4)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_tri_sel_END       (5)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_pin_hd_sel_START  (6)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_pin_hd_sel_END    (7)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_mask_en_START     (8)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_mask_en_END       (8)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_mask_dis_START    (9)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_mask_dis_END      (12)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_mask_und_START    (13)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_mask_und_END      (16)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_pin_en_START      (17)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_pin_en_END        (17)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_DSI_TE_HS_NUM_UNION
 �ṹ˵��  : DSI_TE_HS_NUM �Ĵ����ṹ���塣��ַƫ����:0x0038����ֵ:0x00000000�����:32
 �Ĵ���˵��: DSI��Ӧ�����üĴ������ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsi_te0_hs_num : 13; /* bit[0-12] : ������TE0�ź���Mode2(VS+HS)ģʽ�£��������ĸ�HSʱ��ʼ�������ݡ�
                                                          ����Ϊ0�����⺬�壬����ģʽ��VS�������ݲ���HS��
                                                          ʵ�ʷ���ֵΪDSI_TE1_HS_NUM + 1�з��͡� */
        unsigned int  dsi_te1_hs_num : 13; /* bit[13-25]: ������TE1�ź���Mode2(VS+HS)ģʽ�£��������ĸ�HSʱ��ʼ�������ݡ�
                                                          ����Ϊ0�����⺬�壬����ģʽ��VS�������ݲ���HS��
                                                          ʵ�ʷ���ֵΪDSI_TE1_HS_NUM + 1�з��͡� */
        unsigned int  reserved       : 6;  /* bit[26-31]:  */
    } reg;
} SOC_DSS_ITF_DSI_TE_HS_NUM_UNION;
#endif
#define SOC_DSS_ITF_DSI_TE_HS_NUM_dsi_te0_hs_num_START  (0)
#define SOC_DSS_ITF_DSI_TE_HS_NUM_dsi_te0_hs_num_END    (12)
#define SOC_DSS_ITF_DSI_TE_HS_NUM_dsi_te1_hs_num_START  (13)
#define SOC_DSS_ITF_DSI_TE_HS_NUM_dsi_te1_hs_num_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_DSI_TE_HS_WD_UNION
 �ṹ˵��  : DSI_TE_HS_WD �Ĵ����ṹ���塣��ַƫ����:0x003C����ֵ:0x00003003�����:32
 �Ĵ���˵��: DSI TE PINģʽ���Hsync��ȿ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsi_te0_hs_wd : 12; /* bit[0-11] : ���ڼ��TE0�ź���Mode2(VS+HS)ģʽ�£�HS�źŵ��б𣬵�������TE�ź���Ч�����������Ĵ�����������Ϊ���HS�źš�
                                                         ����Ĵ���������ֵ����С��DSI_TE0_VS_WD��ֵ�� */
        unsigned int  dsi_te1_hs_wd : 12; /* bit[12-23]: ���ڼ��TE1�ź���Mode2(VS+HS)ģʽ�£�HS�źŵ��б𣬵�������TE�ź���Ч�����������Ĵ�����������Ϊ���HS�źš�
                                                         ����Ĵ���������ֵ����С��DSI_TE1_VS_WD��ֵ�� */
        unsigned int  reserved      : 8;  /* bit[24-31]:  */
    } reg;
} SOC_DSS_ITF_DSI_TE_HS_WD_UNION;
#endif
#define SOC_DSS_ITF_DSI_TE_HS_WD_dsi_te0_hs_wd_START  (0)
#define SOC_DSS_ITF_DSI_TE_HS_WD_dsi_te0_hs_wd_END    (11)
#define SOC_DSS_ITF_DSI_TE_HS_WD_dsi_te1_hs_wd_START  (12)
#define SOC_DSS_ITF_DSI_TE_HS_WD_dsi_te1_hs_wd_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_DSI_TE_VS_WD_UNION
 �ṹ˵��  : DSI_TE_VS_WD �Ĵ����ṹ���塣��ַƫ����:0x0040����ֵ:0x00080080�����:32
 �Ĵ���˵��: DSI TE PINģʽ���Vsync��ȿ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsi_te0_vs_wd : 12; /* bit[0-11] : ���ڼ��TE0�ź���Mode2(VS+HS)ģʽ�£�VS�źŵ��б𣬵�������TE�ź���Ч�����������Ĵ�����������Ϊ���VS�ź� */
        unsigned int  dsi_te1_vs_wd : 12; /* bit[12-23]: ���ڼ��TE1�ź���Mode2(VS+HS)ģʽ�£�VS�źŵ��б𣬵�������TE�ź���Ч�����������Ĵ�����������Ϊ���VS�źţ��˼Ĵ������ñ������DSI_TE1_HS_WD�� */
        unsigned int  reserved      : 8;  /* bit[24-31]:  */
    } reg;
} SOC_DSS_ITF_DSI_TE_VS_WD_UNION;
#endif
#define SOC_DSS_ITF_DSI_TE_VS_WD_dsi_te0_vs_wd_START  (0)
#define SOC_DSS_ITF_DSI_TE_VS_WD_dsi_te0_vs_wd_END    (11)
#define SOC_DSS_ITF_DSI_TE_VS_WD_dsi_te1_vs_wd_START  (12)
#define SOC_DSS_ITF_DSI_TE_VS_WD_dsi_te1_vs_wd_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_LDI_FRM_MSK_UNION
 �ṹ˵��  : LDI_FRM_MSK �Ĵ����ṹ���塣��ַƫ����:0x0044����ֵ:0x00000000�����:32
 �Ĵ���˵��: LDI֡���ο��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_msk_en : 1;  /* bit[0]    : 0��֡���ι��ܹر�
                                                      1��֡���ι���ʹ�� */
        unsigned int  reserved_0 : 7;  /* bit[1-7]  : ���� */
        unsigned int  frm_msk    : 8;  /* bit[8-15] : ֡���ι���ʹ��ʱ��LDI����frm_unmsk:frm_msk�ı������frm_unmsk֡������frm_msk֡������ѭ�������磬���frm_unmsk=1��frm_msk=59��LDI���һ֡�󣬺�59֡��ʱ�䴦�ڲ�������ݡ� */
        unsigned int  frm_unmsk  : 8;  /* bit[16-23]: ֡���ι���ʹ��ʱ��LDI����frm_unmsk:frm_msk�ı������frm_unmsk֡������frm_msk֡������ѭ�������磬���frm_unmsk=1��frm_msk=59��LDI���һ֡�󣬺�59֡��ʱ�䴦�ڲ�������ݡ� */
        unsigned int  reserved_1 : 8;  /* bit[24-31]:  */
    } reg;
} SOC_DSS_ITF_LDI_FRM_MSK_UNION;
#endif
#define SOC_DSS_ITF_LDI_FRM_MSK_frm_msk_en_START  (0)
#define SOC_DSS_ITF_LDI_FRM_MSK_frm_msk_en_END    (0)
#define SOC_DSS_ITF_LDI_FRM_MSK_frm_msk_START     (8)
#define SOC_DSS_ITF_LDI_FRM_MSK_frm_msk_END       (15)
#define SOC_DSS_ITF_LDI_FRM_MSK_frm_unmsk_START   (16)
#define SOC_DSS_ITF_LDI_FRM_MSK_frm_unmsk_END     (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_LDI_FRM_MSK_UP_UNION
 �ṹ˵��  : LDI_FRM_MSK_UP �Ĵ����ṹ���塣��ַƫ����:0x0048����ֵ:0x00000000�����:32
 �Ĵ���˵��: LDI֡ˢ�¿��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  single_frm_update : 1;  /* bit[0]   : frm_msk_enΪ1ʱ����˼Ĵ���д1ˢ����һ֡ */
        unsigned int  reserved          : 31; /* bit[1-31]:  */
    } reg;
} SOC_DSS_ITF_LDI_FRM_MSK_UP_UNION;
#endif
#define SOC_DSS_ITF_LDI_FRM_MSK_UP_single_frm_update_START  (0)
#define SOC_DSS_ITF_LDI_FRM_MSK_UP_single_frm_update_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_LDI_VINACT_MSK_LEN_UNION
 �ṹ˵��  : LDI_VINACT_MSK_LEN �Ĵ����ṹ���塣��ַƫ����:0x0050����ֵ:0x00000000�����:32
 �Ĵ���˵��: v_inactive���μĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ldi_vinact_msk_len : 13; /* bit[0-12] : ֡��Ӱ����Ҫ�����εĳ��ȣ���λΪldi_clk_s���ڣ��ڱ������ڼ�DFS������rqos */
        unsigned int  reserved           : 19; /* bit[13-31]: ���� */
    } reg;
} SOC_DSS_ITF_LDI_VINACT_MSK_LEN_UNION;
#endif
#define SOC_DSS_ITF_LDI_VINACT_MSK_LEN_ldi_vinact_msk_len_START  (0)
#define SOC_DSS_ITF_LDI_VINACT_MSK_LEN_ldi_vinact_msk_len_END    (12)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_LDI_CMD_EVENT_SEL_UNION
 �ṹ˵��  : LDI_CMD_EVENT_SEL �Ĵ����ṹ���塣��ַƫ����:0x0060����ֵ:0x00000000�����:32
 �Ĵ���˵��: LDIѡ���CMD������жϼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ldi_cmd_event_sel : 4;  /* bit[0-3] : 0��ldiѡ��frm_end_int��Ϊcmd_event�ź�
                                                            1��ldiѡ��frm_start_int��Ϊcmd_event�ź�
                                                            2��ldiѡ��vbackporch_int��Ϊcmd_event�ź�
                                                            3��ldiѡ��vfrontporch_int��Ϊcmd_event�ź�
                                                            4��ldiѡ��vfrontporch_end_int��Ϊcmd_event�ź�
                                                            5��ldiѡ��vactive0_end_int��Ϊcmd_event�ź�
                                                            6��ldiѡ��vactive0_start_int��Ϊcmd_event�ź�
                                                            7��ldiѡ��vactive1_end_int��Ϊcmd_event�ź�
                                                            8��ldiѡ��vactive1_start_int��Ϊcmd_event�ź� */
        unsigned int  reserved          : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_DSS_ITF_LDI_CMD_EVENT_SEL_UNION;
#endif
#define SOC_DSS_ITF_LDI_CMD_EVENT_SEL_ldi_cmd_event_sel_START  (0)
#define SOC_DSS_ITF_LDI_CMD_EVENT_SEL_ldi_cmd_event_sel_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_SRAM_LP_CTRL_UNION
 �ṹ˵��  : SRAM_LP_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0064����ֵ:0x00000001�����:32
 �Ĵ���˵��: SRAM�͹��Ŀ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pd_in_vfp : 1;  /* bit[0]   : 0��SRAM��VFP�ڼ䲻����power downģʽ
                                                    1��SRAM��VFP�ڼ����power downģʽ */
        unsigned int  reserved  : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_ITF_SRAM_LP_CTRL_UNION;
#endif
#define SOC_DSS_ITF_SRAM_LP_CTRL_pd_in_vfp_START  (0)
#define SOC_DSS_ITF_SRAM_LP_CTRL_pd_in_vfp_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_ITF_RD_SHADOW_UNION
 �ṹ˵��  : ITF_RD_SHADOW �Ĵ����ṹ���塣��ַƫ����:0x006C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��Ӱ�ӼĴ���ѡ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itf_rd_shadow : 1;  /* bit[0]   : 1'b0 :�������Ĵ���
                                                        1'b1 :��Ӱ�ӼĴ��� */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_ITF_ITF_RD_SHADOW_UNION;
#endif
#define SOC_DSS_ITF_ITF_RD_SHADOW_itf_rd_shadow_START  (0)
#define SOC_DSS_ITF_ITF_RD_SHADOW_itf_rd_shadow_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL0_UNION
 �ṹ˵��  : LDI_DPI1_HRZ_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x00F0����ֵ:0x00000000�����:32
 �Ĵ���˵��: LDI-DPI1ˮƽɨ����ƼĴ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 16; /* bit[0-15] : ���� */
        unsigned int  dpi1_hbp : 13; /* bit[16-28]: �к�����ʱ�����ã�д�����ʵ��ֵ���к�������ȡֵ��ΧΪ0~4095 */
        unsigned int  reserved_1: 3;  /* bit[29-31]:  */
    } reg;
} SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL0_UNION;
#endif
#define SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL0_dpi1_hbp_START  (16)
#define SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL0_dpi1_hbp_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL1_UNION
 �ṹ˵��  : LDI_DPI1_HRZ_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x00F4����ֵ:0x00000000�����:32
 �Ĵ���˵��: LDI-DPI1ˮƽɨ��Ĵ���1
            (˫mipiר��)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpi1_hsw : 13; /* bit[0-12] : ˮƽͬ���������ã�д���ֵΪʵ��ֵ��1��Ľ����ˮƽͬ������Ŀ��������ʱ��Ϊ��λ��ȡֵ��ΧΪ1~4096 */
        unsigned int  reserved : 19; /* bit[13-31]:  */
    } reg;
} SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL1_UNION;
#endif
#define SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL1_dpi1_hsw_START  (0)
#define SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL1_dpi1_hsw_END    (12)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL2_UNION
 �ṹ˵��  : LDI_DPI1_HRZ_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0x00F8����ֵ:0x00000000�����:32
 �Ĵ���˵��: LDI-DPI1ˮƽɨ��Ĵ���1
            (˫mipiר��)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpi1_hsize : 13; /* bit[0-12] : ˮƽ�ߴ�Ĵ�����д���ֵΪʵ��ֵ��1��Ľ�� */
        unsigned int  reserved   : 19; /* bit[13-31]:  */
    } reg;
} SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL2_UNION;
#endif
#define SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL2_dpi1_hsize_START  (0)
#define SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL2_dpi1_hsize_END    (12)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_LDI_OVERLAP_SIZE_UNION
 �ṹ˵��  : LDI_OVERLAP_SIZE �Ĵ����ṹ���塣��ַƫ����:0x00FC����ֵ:0x00000000�����:32
 �Ĵ���˵��: LDI˫dpiģʽoverlap�ߴ�Ĵ���
            (˫mipiר��)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpi0_overlap_size : 8;  /* bit[0-7]  : ���ͼ����DPI1_HSIZE�ص�����ĳߴ磬��λΪ�С��˼Ĵ�������˫DPI����ģʽʱ�����á� */
        unsigned int  reserved_0        : 8;  /* bit[8-15] : ���� */
        unsigned int  dpi1_overlap_size : 8;  /* bit[16-23]: �Ұ�ͼ����DPI0_HSIZE�ص�����ĳߴ磬��λΪ�С��˼Ĵ�������˫DPI����ģʽʱ�����á� */
        unsigned int  reserved_1        : 8;  /* bit[24-31]:  */
    } reg;
} SOC_DSS_ITF_LDI_OVERLAP_SIZE_UNION;
#endif
#define SOC_DSS_ITF_LDI_OVERLAP_SIZE_dpi0_overlap_size_START  (0)
#define SOC_DSS_ITF_LDI_OVERLAP_SIZE_dpi0_overlap_size_END    (7)
#define SOC_DSS_ITF_LDI_OVERLAP_SIZE_dpi1_overlap_size_START  (16)
#define SOC_DSS_ITF_LDI_OVERLAP_SIZE_dpi1_overlap_size_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_LDI_MEM_CTRL_UNION
 �ṹ˵��  : LDI_MEM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0100����ֵ:0x00000000�����:32
 �Ĵ���˵��: MEM�͹��Ŀ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ldi_mem_ctrl : 4;  /* bit[0-3] : �����üĴ�������Ӧspram1344x48
                                                       [3] mem_ctrl_auto_en , �Զ�ģʽ���������ģʽѡ��,0�Զ�ģʽ��1�������ģʽ 
                                                       [2]: �������ģʽ����Ч��Ϊ1��ʾ����Shut Downģʽ
                                                       [1]: �������ģʽ����Ч��Ϊ1��ʾ����Deep Sleepģʽ
                                                       [0]: �������ģʽ����Ч��Ϊ1��ʾ����Sleepģʽ */
        unsigned int  reserved     : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_DSS_ITF_LDI_MEM_CTRL_UNION;
#endif
#define SOC_DSS_ITF_LDI_MEM_CTRL_ldi_mem_ctrl_START  (0)
#define SOC_DSS_ITF_LDI_MEM_CTRL_ldi_mem_ctrl_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_LDI_CLK_SEL_UNION
 �ṹ˵��  : LDI_CLK_SEL �Ĵ����ṹ���塣��ַƫ����:0x0108����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: һ��ģ��ʱ��ѡ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ldi_clk_sel : 32; /* bit[0-31]: ��һ��ģ���ʱ��ѡ���źţ�
                                                      1����ʾǿ�ƴ�ʱ�ӡ�
                                                      0����ʾ��Ҫ���������Ӳ����ʱ��ʹ����������ر�ʱ��
                                                      bit0������apb��
                                                      bit1������reg��
                                                      bit2������dss_ldi�� */
    } reg;
} SOC_DSS_ITF_LDI_CLK_SEL_UNION;
#endif
#define SOC_DSS_ITF_LDI_CLK_SEL_ldi_clk_sel_START  (0)
#define SOC_DSS_ITF_LDI_CLK_SEL_ldi_clk_sel_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_LDI_CLK_EN_UNION
 �ṹ˵��  : LDI_CLK_EN �Ĵ����ṹ���塣��ַƫ����:0x010C����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: һ��ģ��ʱ��ʹ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ldi_clk_en : 32; /* bit[0-31]: ��һ��ģ������ʱ��ʹ���ź�
                                                     1����ʾ���ʱ��ʹ����Ч������Ӳ������
                                                     0����ʾ���ʱ��ʹ����Ч����ֹӲ������
                                                     bit0��reserved��
                                                     bit1������reg��
                                                     bit2������dss_ldi�� */
    } reg;
} SOC_DSS_ITF_LDI_CLK_EN_UNION;
#endif
#define SOC_DSS_ITF_LDI_CLK_EN_ldi_clk_en_START  (0)
#define SOC_DSS_ITF_LDI_CLK_EN_ldi_clk_en_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_LDI_IF_BYPASS_UNION
 �ṹ˵��  : LDI_IF_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x0110����ֵ:0x00000000�����:32
 �Ĵ���˵��: sram bypassѡ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ldi_if_bypass : 1;  /* bit[0]   : ���� */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_ITF_LDI_IF_BYPASS_UNION;
#endif
#define SOC_DSS_ITF_LDI_IF_BYPASS_ldi_if_bypass_START  (0)
#define SOC_DSS_ITF_LDI_IF_BYPASS_ldi_if_bypass_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_REG_DEFAULT_UNION
 �ṹ˵��  : REG_DEFAULT �Ĵ����ṹ���塣��ַƫ����:0x0114����ֵ:0x00000000�����:32
 �Ĵ���˵��: ģ��Ӱ�ӼĴ����ָ���Ĭ��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg_default : 1;  /* bit[0]   : ģ������Ӱ�ӼĴ����ָ���Ĭ��ֵ������Ч */
        unsigned int  reserved    : 31; /* bit[1-31]:  */
    } reg;
} SOC_DSS_ITF_REG_DEFAULT_UNION;
#endif
#define SOC_DSS_ITF_REG_DEFAULT_reg_default_START  (0)
#define SOC_DSS_ITF_REG_DEFAULT_reg_default_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_FRM_VALID_DBG_UNION
 �ṹ˵��  : FRM_VALID_DBG �Ĵ����ṹ���塣��ַƫ����:0x0118����ֵ:0x00000000�����:32
 �Ĵ���˵��: ģ��Ӱ�ӼĴ����ָ���Ĭ��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_valid_dbg : 32; /* bit[0-31]: [31:25]:reserved;
                                                        [24]: 0��ʾѡ���������cmdlist vactive1_start_int����Ч֡���� �� 1��ʾÿ֡���vactive1_start_int
                                                        [23]: 0��ʾѡ���������cmdlist vactive1_end_int����Ч֡���� �� 1��ʾÿ֡���vactive1_end_int
                                                        [22]: 0��ʾѡ���������cmdlist vactive0_start_int����Ч֡���� �� 1��ʾÿ֡���vactive0_start_int
                                                        [21]: 0��ʾѡ���������cmdlist vactive0_end_int����Ч֡���� �� 1��ʾÿ֡���vactive0_end_int
                                                        [20]: 0��ʾѡ���������cmdlist vfrontporch_end_int����Ч֡���� �� 1��ʾÿ֡���vfrontporch_end_int
                                                        [19]: 0��ʾѡ���������cmdlist vfrontporch_int����Ч֡���� �� 1��ʾÿ֡���vfrontporch_int
                                                        [18]: 0��ʾѡ���������cmdlist vbackporch_int����Ч֡���� �� 1��ʾÿ֡���vbackporch_int
                                                        [17]: 0��ʾѡ���������cmdlist frm_start_int����Ч֡���� �� 1��ʾÿ֡���frm_start_int
                                                        [16]: 0��ʾѡ���������cmdlist frm_end_int����Ч֡���� �� 1��ʾÿ֡���frm_end_int
                                                        [15]: 0��ʾѡ��ÿ֡��glb dsi_te_tri_int �� 1��ʾ�����dsi_te_tri_int ����Ч֡����
                                                        [14]: 0��ʾѡ��ÿ֡��glb lcd_te0_pin_int �� 1��ʾ�����frm_start_int����Ч֡����
                                                        [13]: 0��ʾѡ��ÿ֡��glb lcd_te1_pin_int �� 1��ʾ�����lcd_te1_pin_int ����Ч֡����
                                                        [12]: 0��ʾѡ��ÿ֡��glb vactive1_end_int �� 1��ʾ�����vactive1_end_int ,��Ч֡����
                                                        [11]: 0��ʾѡ��ÿ֡��glb vactive1_start_int �� 1��ʾ�����vactive1_start_int ,��Ч֡����
                                                        [10]: 0��ʾѡ��ÿ֡��glb vactive0_end_int �� 1��ʾ�����vactive0_end_int ,��Ч֡����
                                                        [9]: 1��ʾѡ��ÿ֡��glb vactive0_start_int ��0��ʾ�����vactive0_start_int ,��Ч֡����
                                                        [8]: 0��ʾѡ��ÿ֡��glb vfrontporch_int �� 1��ʾ�����vfrontporch_int ,��Ч֡����
                                                        [7]: 0��ʾѡ��ÿ֡��glb vbackporch_int �� 1��ʾ�����vbackporch_int ,��Ч֡����
                                                        [6]: 0��ʾѡ��ÿ֡��glb vsync_int �� 1��ʾ�����vsync_int ,��Ч֡����
                                                        [5]: 0��ʾѡ��ÿ֡��glb vfrontporch_end_int �� 1��ʾ�����vfrontporch_end_int ,��Ч֡����
                                                        [4]: 0��ʾѡ��ÿ֡��glb frm_end_int �� 1��ʾ�����frm_end_int ����Ч֡����
                                                        [3]: 0��ʾѡ��ÿ֡��glb frm_start_int �� 1��ʾ�����frm_start_int����Ч֡����
                                                        [2:0]:reserved; */
    } reg;
} SOC_DSS_ITF_FRM_VALID_DBG_UNION;
#endif
#define SOC_DSS_ITF_FRM_VALID_DBG_frm_valid_dbg_START  (0)
#define SOC_DSS_ITF_FRM_VALID_DBG_frm_valid_dbg_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_CRC_DBG_ITF_UNION
 �ṹ˵��  : CRC_DBG_ITF �Ĵ����ṹ���塣��ַƫ����:0x0200����ֵ:0x00000000�����:32
 �Ĵ���˵��: LDI��crcУ����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_dbg_itf : 32; /* bit[0-31]: LDI0��crcУ���� */
    } reg;
} SOC_DSS_ITF_CRC_DBG_ITF_UNION;
#endif
#define SOC_DSS_ITF_CRC_DBG_ITF_crc_dbg_itf_START  (0)
#define SOC_DSS_ITF_CRC_DBG_ITF_crc_dbg_itf_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_CRC_ITF_EN_UNION
 �ṹ˵��  : CRC_ITF_EN �Ĵ����ṹ���塣��ַƫ����:0x0204����ֵ:0x00000000�����:32
 �Ĵ���˵��: LDI��CRC����ʹ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_itf_en : 1;  /* bit[0-0] : LDI0��CRC����ʹ���ź� */
        unsigned int  reserved   : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_ITF_CRC_ITF_EN_UNION;
#endif
#define SOC_DSS_ITF_CRC_ITF_EN_crc_itf_en_START  (0)
#define SOC_DSS_ITF_CRC_ITF_EN_crc_itf_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_ITF_CRC_ITF_FRM_UNION
 �ṹ˵��  : CRC_ITF_FRM �Ĵ����ṹ���塣��ַƫ����:0x0208����ֵ:0x00000000�����:32
 �Ĵ���˵��: LDI�ϱ���CRCУ���֡��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_itf_frm : 32; /* bit[0-31]: LDI0�ϱ���CRCУ���֡�� */
    } reg;
} SOC_DSS_ITF_CRC_ITF_FRM_UNION;
#endif
#define SOC_DSS_ITF_CRC_ITF_FRM_crc_itf_frm_START  (0)
#define SOC_DSS_ITF_CRC_ITF_FRM_crc_itf_frm_END    (31)






/*****************************************************************************
  8 OTHERS����
*****************************************************************************/



/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of soc_dss_itf_interface.h */
