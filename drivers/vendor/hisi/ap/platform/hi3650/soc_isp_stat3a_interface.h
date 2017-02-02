/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_isp_stat3a_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:22:04
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_ISP_STAT3A.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_ISP_STAT3A_INTERFACE_H__
#define __SOC_ISP_STAT3A_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) STAT3A
 ****************************************************************************/
/* �Ĵ���˵����Configuration register for 3A module
   λ����UNION�ṹ:  SOC_ISP_STAT3A_STAT3A_CONFIG_UNION */
#define SOC_ISP_STAT3A_STAT3A_CONFIG_ADDR(base)       ((base) + (0x0000))

/* �Ĵ���˵����Status register for 3A module
   λ����UNION�ṹ:  SOC_ISP_STAT3A_STAT3A_STATUS_UNION */
#define SOC_ISP_STAT3A_STAT3A_STATUS_ADDR(base)       ((base) + (0x0004))

/* �Ĵ���˵����Crop Left-Right
   λ����UNION�ṹ:  SOC_ISP_STAT3A_GKM_CROPLR_UNION */
#define SOC_ISP_STAT3A_GKM_CROPLR_ADDR(base)          ((base) + (0x0008))

/* �Ĵ���˵����Crop Top-Bottom
   λ����UNION�ṹ:  SOC_ISP_STAT3A_GKM_CROPTB_UNION */
#define SOC_ISP_STAT3A_GKM_CROPTB_ADDR(base)          ((base) + (0x000C))

/* �Ĵ���˵����Focus window horizontal parameters
   λ����UNION�ṹ:  SOC_ISP_STAT3A_FW_X_0_UNION */
#define SOC_ISP_STAT3A_FW_X_0_ADDR(base)              ((base) + (0x0010))

/* �Ĵ���˵����Focus window vertical parameters
   λ����UNION�ṹ:  SOC_ISP_STAT3A_FW_Y_0_UNION */
#define SOC_ISP_STAT3A_FW_Y_0_ADDR(base)              ((base) + (0x0014))

/* �Ĵ���˵����Focus window horizontal parameters
   λ����UNION�ṹ:  SOC_ISP_STAT3A_FW_X_1_UNION */
#define SOC_ISP_STAT3A_FW_X_1_ADDR(base)              ((base) + (0x0018))

/* �Ĵ���˵����Focus window vertical parameters
   λ����UNION�ṹ:  SOC_ISP_STAT3A_FW_Y_1_UNION */
#define SOC_ISP_STAT3A_FW_Y_1_ADDR(base)              ((base) + (0x001C))

/* �Ĵ���˵����Focus window horizontal parameters
   λ����UNION�ṹ:  SOC_ISP_STAT3A_FW_X_2_UNION */
#define SOC_ISP_STAT3A_FW_X_2_ADDR(base)              ((base) + (0x0020))

/* �Ĵ���˵����Focus window vertical parameters
   λ����UNION�ṹ:  SOC_ISP_STAT3A_FW_Y_2_UNION */
#define SOC_ISP_STAT3A_FW_Y_2_ADDR(base)              ((base) + (0x0024))

/* �Ĵ���˵����Focus window horizontal parameters
   λ����UNION�ṹ:  SOC_ISP_STAT3A_FW_X_3_UNION */
#define SOC_ISP_STAT3A_FW_X_3_ADDR(base)              ((base) + (0x0028))

/* �Ĵ���˵����Focus window vertical parameters
   λ����UNION�ṹ:  SOC_ISP_STAT3A_FW_Y_3_UNION */
#define SOC_ISP_STAT3A_FW_Y_3_ADDR(base)              ((base) + (0x002C))

/* �Ĵ���˵����Focus window horizontal parameters
   λ����UNION�ṹ:  SOC_ISP_STAT3A_FW_X_4_UNION */
#define SOC_ISP_STAT3A_FW_X_4_ADDR(base)              ((base) + (0x0030))

/* �Ĵ���˵����Focus window vertical parameters
   λ����UNION�ṹ:  SOC_ISP_STAT3A_FW_Y_4_UNION */
#define SOC_ISP_STAT3A_FW_Y_4_ADDR(base)              ((base) + (0x0034))

/* �Ĵ���˵����Focus window horizontal parameters
   λ����UNION�ṹ:  SOC_ISP_STAT3A_FW_X_5_UNION */
#define SOC_ISP_STAT3A_FW_X_5_ADDR(base)              ((base) + (0x0038))

/* �Ĵ���˵����Focus window vertical parameters
   λ����UNION�ṹ:  SOC_ISP_STAT3A_FW_Y_5_UNION */
#define SOC_ISP_STAT3A_FW_Y_5_ADDR(base)              ((base) + (0x003C))

/* �Ĵ���˵����Focus window horizontal parameters
   λ����UNION�ṹ:  SOC_ISP_STAT3A_FW_X_6_UNION */
#define SOC_ISP_STAT3A_FW_X_6_ADDR(base)              ((base) + (0x0040))

/* �Ĵ���˵����Focus window vertical parameters
   λ����UNION�ṹ:  SOC_ISP_STAT3A_FW_Y_6_UNION */
#define SOC_ISP_STAT3A_FW_Y_6_ADDR(base)              ((base) + (0x0044))

/* �Ĵ���˵����Focus window horizontal parameters
   λ����UNION�ṹ:  SOC_ISP_STAT3A_FW_X_7_UNION */
#define SOC_ISP_STAT3A_FW_X_7_ADDR(base)              ((base) + (0x0048))

/* �Ĵ���˵����Focus window vertical parameters
   λ����UNION�ṹ:  SOC_ISP_STAT3A_FW_Y_7_UNION */
#define SOC_ISP_STAT3A_FW_Y_7_ADDR(base)              ((base) + (0x004C))

/* �Ĵ���˵����Focus window horizontal parameters
   λ����UNION�ṹ:  SOC_ISP_STAT3A_FW_X_8_UNION */
#define SOC_ISP_STAT3A_FW_X_8_ADDR(base)              ((base) + (0x0050))

/* �Ĵ���˵����Focus window vertical parameters
   λ����UNION�ṹ:  SOC_ISP_STAT3A_FW_Y_8_UNION */
#define SOC_ISP_STAT3A_FW_Y_8_ADDR(base)              ((base) + (0x0054))

/* �Ĵ���˵����Histogram window horizontal parameters
   λ����UNION�ṹ:  SOC_ISP_STAT3A_HIST_X_UNION */
#define SOC_ISP_STAT3A_HIST_X_ADDR(base)              ((base) + (0x0058))

/* �Ĵ���˵����Histogram window vertical parameters
   λ����UNION�ṹ:  SOC_ISP_STAT3A_HIST_Y_UNION */
#define SOC_ISP_STAT3A_HIST_Y_ADDR(base)              ((base) + (0x005C))

/* �Ĵ���˵����AF Parameters
   λ����UNION�ṹ:  SOC_ISP_STAT3A_AF_PARAM_1_UNION */
#define SOC_ISP_STAT3A_AF_PARAM_1_ADDR(base)          ((base) + (0x0060))

/* �Ĵ���˵����filter coefficient for Focus Value FIR
   λ����UNION�ṹ:  SOC_ISP_STAT3A_Y_C0_UNION */
#define SOC_ISP_STAT3A_Y_C0_ADDR(base)                ((base) + (0x0064))

/* �Ĵ���˵����filter coefficient for Focus Value FIR
   λ����UNION�ṹ:  SOC_ISP_STAT3A_Y_C1_UNION */
#define SOC_ISP_STAT3A_Y_C1_ADDR(base)                ((base) + (0x0068))

/* �Ĵ���˵����filter coefficient for Focus Value FIR
   λ����UNION�ṹ:  SOC_ISP_STAT3A_Y_C2_UNION */
#define SOC_ISP_STAT3A_Y_C2_ADDR(base)                ((base) + (0x006C))

/* �Ĵ���˵����filter coefficient for Focus Value FIR
   λ����UNION�ṹ:  SOC_ISP_STAT3A_Y_C3_UNION */
#define SOC_ISP_STAT3A_Y_C3_ADDR(base)                ((base) + (0x0070))

/* �Ĵ���˵����filter coefficient for Focus Value FIR
   λ����UNION�ṹ:  SOC_ISP_STAT3A_Y_C4_UNION */
#define SOC_ISP_STAT3A_Y_C4_ADDR(base)                ((base) + (0x0074))

/* �Ĵ���˵����filter coefficient for Focus Value FIR
   λ����UNION�ṹ:  SOC_ISP_STAT3A_Y_C5_UNION */
#define SOC_ISP_STAT3A_Y_C5_ADDR(base)                ((base) + (0x0078))

/* �Ĵ���˵����filter coefficient for Focus Value FIR
   λ����UNION�ṹ:  SOC_ISP_STAT3A_Y_C6_UNION */
#define SOC_ISP_STAT3A_Y_C6_ADDR(base)                ((base) + (0x007C))

/* �Ĵ���˵����filter coefficient for Focus Value FIR
   λ����UNION�ṹ:  SOC_ISP_STAT3A_Y_C7_UNION */
#define SOC_ISP_STAT3A_Y_C7_ADDR(base)                ((base) + (0x0080))

/* �Ĵ���˵����filter coefficient for Focus Value FIR
   λ����UNION�ṹ:  SOC_ISP_STAT3A_Y_C8_UNION */
#define SOC_ISP_STAT3A_Y_C8_ADDR(base)                ((base) + (0x0084))

/* �Ĵ���˵����filter coefficient for Focus Value FIR
   λ����UNION�ṹ:  SOC_ISP_STAT3A_Y_C9_UNION */
#define SOC_ISP_STAT3A_Y_C9_ADDR(base)                ((base) + (0x0088))

/* �Ĵ���˵����number of paxels in frame
   λ����UNION�ṹ:  SOC_ISP_STAT3A_BLOCKNUM_UNION */
#define SOC_ISP_STAT3A_BLOCKNUM_ADDR(base)            ((base) + (0x008C))

/* �Ĵ���˵����size of paxels in frame
   λ����UNION�ṹ:  SOC_ISP_STAT3A_BLOCKWIN_UNION */
#define SOC_ISP_STAT3A_BLOCKWIN_ADDR(base)            ((base) + (0x000090))

/* �Ĵ���˵����Column Offset for AE
   λ����UNION�ṹ:  SOC_ISP_STAT3A_COLUMNOFFSET_UNION */
#define SOC_ISP_STAT3A_COLUMNOFFSET_ADDR(base)        ((base) + (0x0094))

/* �Ĵ���˵����Threshold for cumulative histogram
   λ����UNION�ṹ:  SOC_ISP_STAT3A_BINTHD_UNION */
#define SOC_ISP_STAT3A_BINTHD_ADDR(base)              ((base) + (0x0098))

/* �Ĵ���˵����ROI w,h
   λ����UNION�ṹ:  SOC_ISP_STAT3A_LOCATIONROI01_UNION */
#define SOC_ISP_STAT3A_LOCATIONROI01_ADDR(base)       ((base) + (0x009C))

/* �Ĵ���˵����ROI w,h
   λ����UNION�ṹ:  SOC_ISP_STAT3A_LOCATIONROI23_UNION */
#define SOC_ISP_STAT3A_LOCATIONROI23_ADDR(base)       ((base) + (0x00A0))

/* �Ĵ���˵����ROI w,h
   λ����UNION�ṹ:  SOC_ISP_STAT3A_LOCATIONROI45_UNION */
#define SOC_ISP_STAT3A_LOCATIONROI45_ADDR(base)       ((base) + (0x00A4))

/* �Ĵ���˵����ROI w,h
   λ����UNION�ṹ:  SOC_ISP_STAT3A_LOCATIONROI67_UNION */
#define SOC_ISP_STAT3A_LOCATIONROI67_ADDR(base)       ((base) + (0x00A8))

/* �Ĵ���˵����ROI w,h
   λ����UNION�ṹ:  SOC_ISP_STAT3A_LOCATIONROI89_UNION */
#define SOC_ISP_STAT3A_LOCATIONROI89_ADDR(base)       ((base) + (0x00AC))

/* �Ĵ���˵����ROI 0,1 width
   λ����UNION�ṹ:  SOC_ISP_STAT3A_SIZEROI01_UNION */
#define SOC_ISP_STAT3A_SIZEROI01_ADDR(base)           ((base) + (0x00B0))

/* �Ĵ���˵����ROI 2,3 width
   λ����UNION�ṹ:  SOC_ISP_STAT3A_SIZEROI23_UNION */
#define SOC_ISP_STAT3A_SIZEROI23_ADDR(base)           ((base) + (0x00B4))

/* �Ĵ���˵����ROI 4,5 width
   λ����UNION�ṹ:  SOC_ISP_STAT3A_SIZEROI45_UNION */
#define SOC_ISP_STAT3A_SIZEROI45_ADDR(base)           ((base) + (0x00B8))

/* �Ĵ���˵����ROI 6,7 width
   λ����UNION�ṹ:  SOC_ISP_STAT3A_SIZEROI67_UNION */
#define SOC_ISP_STAT3A_SIZEROI67_ADDR(base)           ((base) + (0x00BC))

/* �Ĵ���˵����ROI 9 width, and ROI heigth
   λ����UNION�ṹ:  SOC_ISP_STAT3A_SIZEROI8_UNION */
#define SOC_ISP_STAT3A_SIZEROI8_ADDR(base)            ((base) + (0x00C0))

/* �Ĵ���˵����AWB cfg
   λ����UNION�ṹ:  SOC_ISP_STAT3A_COLORVALUE_UNION */
#define SOC_ISP_STAT3A_COLORVALUE_ADDR(base)          ((base) + (0x00C4))

/* �Ĵ���˵����AWB cfg
   λ����UNION�ṹ:  SOC_ISP_STAT3A_GRAYZONETOP_UNION */
#define SOC_ISP_STAT3A_GRAYZONETOP_ADDR(base)         ((base) + (0x00C8))

/* �Ĵ���˵����AWB cfg
   λ����UNION�ṹ:  SOC_ISP_STAT3A_GRAYZONEBOTTOM_UNION */
#define SOC_ISP_STAT3A_GRAYZONEBOTTOM_ADDR(base)      ((base) + (0x00CC))

/* �Ĵ���˵����AWB cfg
   λ����UNION�ṹ:  SOC_ISP_STAT3A_GRAYZONELEFT_UNION */
#define SOC_ISP_STAT3A_GRAYZONELEFT_ADDR(base)        ((base) + (0x00D0))

/* �Ĵ���˵����AWB cfg
   λ����UNION�ṹ:  SOC_ISP_STAT3A_GRAYZONERIGHT_UNION */
#define SOC_ISP_STAT3A_GRAYZONERIGHT_ADDR(base)       ((base) + (0x00D4))

/* �Ĵ���˵����AWB cfg
   λ����UNION�ṹ:  SOC_ISP_STAT3A_GREENLUMAVALUE_UNION */
#define SOC_ISP_STAT3A_GREENLUMAVALUE_ADDR(base)      ((base) + (0x00D8))

/* �Ĵ���˵����AWB cfg
   λ����UNION�ṹ:  SOC_ISP_STAT3A_GREENCEN_UNION */
#define SOC_ISP_STAT3A_GREENCEN_ADDR(base)            ((base) + (0x00DC))

/* �Ĵ���˵����AWB cfg
   λ����UNION�ṹ:  SOC_ISP_STAT3A_GREENDISTCOEF_UNION */
#define SOC_ISP_STAT3A_GREENDISTCOEF_ADDR(base)       ((base) + (0x00E0))

/* �Ĵ���˵����AWB cfg
   λ����UNION�ṹ:  SOC_ISP_STAT3A_GREENDIST_UNION */
#define SOC_ISP_STAT3A_GREENDIST_ADDR(base)           ((base) + (0x00E4))

/* �Ĵ���˵����rgb Hist param
   λ����UNION�ṹ:  SOC_ISP_STAT3A_RGBHIST_UNION */
#define SOC_ISP_STAT3A_RGBHIST_ADDR(base)             ((base) + (0x00E8))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ISP_STAT3A_PREGAIN_UNION */
#define SOC_ISP_STAT3A_PREGAIN_ADDR(base)             ((base) + (0x00EC))

/* �Ĵ���˵����Coefficient for Luma computation
   λ����UNION�ṹ:  SOC_ISP_STAT3A_LUMACOEF_UNION */
#define SOC_ISP_STAT3A_LUMACOEF_ADDR(base)            ((base) + (0x00F0))

/* �Ĵ���˵����AF Parameters
   λ����UNION�ṹ:  SOC_ISP_STAT3A_AF_PARAM_2_UNION */
#define SOC_ISP_STAT3A_AF_PARAM_2_ADDR(base)          ((base) + (0x00F4))





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
                     (1/1) STAT3A
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_STAT3A_CONFIG_UNION
 �ṹ˵��  : STAT3A_CONFIG �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: Configuration register for 3A module
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enable   : 1;  /* bit[0-0] : 0-disable,1-enable  */
        unsigned int  irq_en   : 1;  /* bit[1-1] : 0-disable irq, 1- enable irq */
        unsigned int  scm      : 1;  /* bit[2-2] : 0 - normal mode, 1 - save DIS memory content after 3AStat done->does not generate V_END at end of Stat3A */
        unsigned int  reserved : 29; /* bit[3-31]:  */
    } reg;
} SOC_ISP_STAT3A_STAT3A_CONFIG_UNION;
#endif
#define SOC_ISP_STAT3A_STAT3A_CONFIG_enable_START    (0)
#define SOC_ISP_STAT3A_STAT3A_CONFIG_enable_END      (0)
#define SOC_ISP_STAT3A_STAT3A_CONFIG_irq_en_START    (1)
#define SOC_ISP_STAT3A_STAT3A_CONFIG_irq_en_END      (1)
#define SOC_ISP_STAT3A_STAT3A_CONFIG_scm_START       (2)
#define SOC_ISP_STAT3A_STAT3A_CONFIG_scm_END         (2)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_STAT3A_STATUS_UNION
 �ṹ˵��  : STAT3A_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: Status register for 3A module
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  state    : 2;  /* bit[0-1] : 00-RDY, 01-EXEC, 10-END */
        unsigned int  reserved : 30; /* bit[2-31]:  */
    } reg;
} SOC_ISP_STAT3A_STAT3A_STATUS_UNION;
#endif
#define SOC_ISP_STAT3A_STAT3A_STATUS_state_START     (0)
#define SOC_ISP_STAT3A_STAT3A_STATUS_state_END       (1)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_GKM_CROPLR_UNION
 �ṹ˵��  : GKM_CROPLR �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: Crop Left-Right
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cleft    : 13; /* bit[0-12] : Crop left */
        unsigned int  reserved_0: 3;  /* bit[13-15]:  */
        unsigned int  cright   : 13; /* bit[16-28]: Crop right */
        unsigned int  reserved_1: 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_STAT3A_GKM_CROPLR_UNION;
#endif
#define SOC_ISP_STAT3A_GKM_CROPLR_cleft_START     (0)
#define SOC_ISP_STAT3A_GKM_CROPLR_cleft_END       (12)
#define SOC_ISP_STAT3A_GKM_CROPLR_cright_START    (16)
#define SOC_ISP_STAT3A_GKM_CROPLR_cright_END      (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_GKM_CROPTB_UNION
 �ṹ˵��  : GKM_CROPTB �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Crop Top-Bottom
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctop     : 13; /* bit[0-12] : crop top */
        unsigned int  reserved_0: 3;  /* bit[13-15]:  */
        unsigned int  cbottom  : 13; /* bit[16-28]: crop bottom */
        unsigned int  reserved_1: 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_STAT3A_GKM_CROPTB_UNION;
#endif
#define SOC_ISP_STAT3A_GKM_CROPTB_ctop_START      (0)
#define SOC_ISP_STAT3A_GKM_CROPTB_ctop_END        (12)
#define SOC_ISP_STAT3A_GKM_CROPTB_cbottom_START   (16)
#define SOC_ISP_STAT3A_GKM_CROPTB_cbottom_END     (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_FW_X_0_UNION
 �ṹ˵��  : FW_X_0 �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: Focus window horizontal parameters
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fw_x_strt_0  : 13; /* bit[0-12] : Focus window horizontal start */
        unsigned int  reserved_0   : 3;  /* bit[13-15]:  */
        unsigned int  fw_x_width_0 : 13; /* bit[16-28]: Focus window horizontal width */
        unsigned int  reserved_1   : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_STAT3A_FW_X_0_UNION;
#endif
#define SOC_ISP_STAT3A_FW_X_0_fw_x_strt_0_START   (0)
#define SOC_ISP_STAT3A_FW_X_0_fw_x_strt_0_END     (12)
#define SOC_ISP_STAT3A_FW_X_0_fw_x_width_0_START  (16)
#define SOC_ISP_STAT3A_FW_X_0_fw_x_width_0_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_FW_Y_0_UNION
 �ṹ˵��  : FW_Y_0 �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: Focus window vertical parameters
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fw_y_strt_0  : 13; /* bit[0-12] : Focus window vertical start */
        unsigned int  reserved_0   : 3;  /* bit[13-15]:  */
        unsigned int  fw_y_width_0 : 13; /* bit[16-28]: Focus window vertical height */
        unsigned int  reserved_1   : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_STAT3A_FW_Y_0_UNION;
#endif
#define SOC_ISP_STAT3A_FW_Y_0_fw_y_strt_0_START   (0)
#define SOC_ISP_STAT3A_FW_Y_0_fw_y_strt_0_END     (12)
#define SOC_ISP_STAT3A_FW_Y_0_fw_y_width_0_START  (16)
#define SOC_ISP_STAT3A_FW_Y_0_fw_y_width_0_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_FW_X_1_UNION
 �ṹ˵��  : FW_X_1 �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: Focus window horizontal parameters
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fw_x_strt_1  : 13; /* bit[0-12] : Focus window horizontal start */
        unsigned int  reserved_0   : 3;  /* bit[13-15]:  */
        unsigned int  fw_x_width_1 : 13; /* bit[16-28]: Focus window horizontal width */
        unsigned int  reserved_1   : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_STAT3A_FW_X_1_UNION;
#endif
#define SOC_ISP_STAT3A_FW_X_1_fw_x_strt_1_START   (0)
#define SOC_ISP_STAT3A_FW_X_1_fw_x_strt_1_END     (12)
#define SOC_ISP_STAT3A_FW_X_1_fw_x_width_1_START  (16)
#define SOC_ISP_STAT3A_FW_X_1_fw_x_width_1_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_FW_Y_1_UNION
 �ṹ˵��  : FW_Y_1 �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Focus window vertical parameters
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fw_y_strt_1  : 13; /* bit[0-12] : Focus window vertical start */
        unsigned int  reserved_0   : 3;  /* bit[13-15]:  */
        unsigned int  fw_y_width_1 : 13; /* bit[16-28]: Focus window vertical height */
        unsigned int  reserved_1   : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_STAT3A_FW_Y_1_UNION;
#endif
#define SOC_ISP_STAT3A_FW_Y_1_fw_y_strt_1_START   (0)
#define SOC_ISP_STAT3A_FW_Y_1_fw_y_strt_1_END     (12)
#define SOC_ISP_STAT3A_FW_Y_1_fw_y_width_1_START  (16)
#define SOC_ISP_STAT3A_FW_Y_1_fw_y_width_1_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_FW_X_2_UNION
 �ṹ˵��  : FW_X_2 �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: Focus window horizontal parameters
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fw_x_strt_2  : 13; /* bit[0-12] : Focus window horizontal start */
        unsigned int  reserved_0   : 3;  /* bit[13-15]:  */
        unsigned int  fw_x_width_2 : 13; /* bit[16-28]: Focus window horizontal width */
        unsigned int  reserved_1   : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_STAT3A_FW_X_2_UNION;
#endif
#define SOC_ISP_STAT3A_FW_X_2_fw_x_strt_2_START   (0)
#define SOC_ISP_STAT3A_FW_X_2_fw_x_strt_2_END     (12)
#define SOC_ISP_STAT3A_FW_X_2_fw_x_width_2_START  (16)
#define SOC_ISP_STAT3A_FW_X_2_fw_x_width_2_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_FW_Y_2_UNION
 �ṹ˵��  : FW_Y_2 �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x00000000�����:32
 �Ĵ���˵��: Focus window vertical parameters
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fw_y_strt_2  : 13; /* bit[0-12] : Focus window vertical start */
        unsigned int  reserved_0   : 3;  /* bit[13-15]:  */
        unsigned int  fw_y_width_2 : 13; /* bit[16-28]: Focus window vertical height */
        unsigned int  reserved_1   : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_STAT3A_FW_Y_2_UNION;
#endif
#define SOC_ISP_STAT3A_FW_Y_2_fw_y_strt_2_START   (0)
#define SOC_ISP_STAT3A_FW_Y_2_fw_y_strt_2_END     (12)
#define SOC_ISP_STAT3A_FW_Y_2_fw_y_width_2_START  (16)
#define SOC_ISP_STAT3A_FW_Y_2_fw_y_width_2_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_FW_X_3_UNION
 �ṹ˵��  : FW_X_3 �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x00000000�����:32
 �Ĵ���˵��: Focus window horizontal parameters
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fw_x_strt_3  : 13; /* bit[0-12] : Focus window horizontal start */
        unsigned int  reserved_0   : 3;  /* bit[13-15]:  */
        unsigned int  fw_x_width_3 : 13; /* bit[16-28]: Focus window horizontal width */
        unsigned int  reserved_1   : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_STAT3A_FW_X_3_UNION;
#endif
#define SOC_ISP_STAT3A_FW_X_3_fw_x_strt_3_START   (0)
#define SOC_ISP_STAT3A_FW_X_3_fw_x_strt_3_END     (12)
#define SOC_ISP_STAT3A_FW_X_3_fw_x_width_3_START  (16)
#define SOC_ISP_STAT3A_FW_X_3_fw_x_width_3_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_FW_Y_3_UNION
 �ṹ˵��  : FW_Y_3 �Ĵ����ṹ���塣��ַƫ����:0x002C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Focus window vertical parameters
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fw_y_strt_3  : 13; /* bit[0-12] : Focus window vertical start */
        unsigned int  reserved_0   : 3;  /* bit[13-15]:  */
        unsigned int  fw_y_width_3 : 13; /* bit[16-28]: Focus window vertical height */
        unsigned int  reserved_1   : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_STAT3A_FW_Y_3_UNION;
#endif
#define SOC_ISP_STAT3A_FW_Y_3_fw_y_strt_3_START   (0)
#define SOC_ISP_STAT3A_FW_Y_3_fw_y_strt_3_END     (12)
#define SOC_ISP_STAT3A_FW_Y_3_fw_y_width_3_START  (16)
#define SOC_ISP_STAT3A_FW_Y_3_fw_y_width_3_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_FW_X_4_UNION
 �ṹ˵��  : FW_X_4 �Ĵ����ṹ���塣��ַƫ����:0x0030����ֵ:0x00000000�����:32
 �Ĵ���˵��: Focus window horizontal parameters
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fw_x_strt_4  : 13; /* bit[0-12] : Focus window horizontal start */
        unsigned int  reserved_0   : 3;  /* bit[13-15]:  */
        unsigned int  fw_x_width_4 : 13; /* bit[16-28]: Focus window horizontal width */
        unsigned int  reserved_1   : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_STAT3A_FW_X_4_UNION;
#endif
#define SOC_ISP_STAT3A_FW_X_4_fw_x_strt_4_START   (0)
#define SOC_ISP_STAT3A_FW_X_4_fw_x_strt_4_END     (12)
#define SOC_ISP_STAT3A_FW_X_4_fw_x_width_4_START  (16)
#define SOC_ISP_STAT3A_FW_X_4_fw_x_width_4_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_FW_Y_4_UNION
 �ṹ˵��  : FW_Y_4 �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x00000000�����:32
 �Ĵ���˵��: Focus window vertical parameters
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fw_y_strt_4  : 13; /* bit[0-12] : Focus window vertical start */
        unsigned int  reserved_0   : 3;  /* bit[13-15]:  */
        unsigned int  fw_y_width_4 : 13; /* bit[16-28]: Focus window vertical height */
        unsigned int  reserved_1   : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_STAT3A_FW_Y_4_UNION;
#endif
#define SOC_ISP_STAT3A_FW_Y_4_fw_y_strt_4_START   (0)
#define SOC_ISP_STAT3A_FW_Y_4_fw_y_strt_4_END     (12)
#define SOC_ISP_STAT3A_FW_Y_4_fw_y_width_4_START  (16)
#define SOC_ISP_STAT3A_FW_Y_4_fw_y_width_4_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_FW_X_5_UNION
 �ṹ˵��  : FW_X_5 �Ĵ����ṹ���塣��ַƫ����:0x0038����ֵ:0x00000000�����:32
 �Ĵ���˵��: Focus window horizontal parameters
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fw_x_strt_5  : 13; /* bit[0-12] : Focus window horizontal start */
        unsigned int  reserved_0   : 3;  /* bit[13-15]:  */
        unsigned int  fw_x_width_5 : 13; /* bit[16-28]: Focus window horizontal width */
        unsigned int  reserved_1   : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_STAT3A_FW_X_5_UNION;
#endif
#define SOC_ISP_STAT3A_FW_X_5_fw_x_strt_5_START   (0)
#define SOC_ISP_STAT3A_FW_X_5_fw_x_strt_5_END     (12)
#define SOC_ISP_STAT3A_FW_X_5_fw_x_width_5_START  (16)
#define SOC_ISP_STAT3A_FW_X_5_fw_x_width_5_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_FW_Y_5_UNION
 �ṹ˵��  : FW_Y_5 �Ĵ����ṹ���塣��ַƫ����:0x003C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Focus window vertical parameters
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fw_y_strt_5  : 13; /* bit[0-12] : Focus window vertical start */
        unsigned int  reserved_0   : 3;  /* bit[13-15]:  */
        unsigned int  fw_y_width_5 : 13; /* bit[16-28]: Focus window vertical height */
        unsigned int  reserved_1   : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_STAT3A_FW_Y_5_UNION;
#endif
#define SOC_ISP_STAT3A_FW_Y_5_fw_y_strt_5_START   (0)
#define SOC_ISP_STAT3A_FW_Y_5_fw_y_strt_5_END     (12)
#define SOC_ISP_STAT3A_FW_Y_5_fw_y_width_5_START  (16)
#define SOC_ISP_STAT3A_FW_Y_5_fw_y_width_5_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_FW_X_6_UNION
 �ṹ˵��  : FW_X_6 �Ĵ����ṹ���塣��ַƫ����:0x0040����ֵ:0x00000000�����:32
 �Ĵ���˵��: Focus window horizontal parameters
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fw_x_strt_6  : 13; /* bit[0-12] : Focus window horizontal start */
        unsigned int  reserved_0   : 3;  /* bit[13-15]:  */
        unsigned int  fw_x_width_6 : 13; /* bit[16-28]: Focus window horizontal width */
        unsigned int  reserved_1   : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_STAT3A_FW_X_6_UNION;
#endif
#define SOC_ISP_STAT3A_FW_X_6_fw_x_strt_6_START   (0)
#define SOC_ISP_STAT3A_FW_X_6_fw_x_strt_6_END     (12)
#define SOC_ISP_STAT3A_FW_X_6_fw_x_width_6_START  (16)
#define SOC_ISP_STAT3A_FW_X_6_fw_x_width_6_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_FW_Y_6_UNION
 �ṹ˵��  : FW_Y_6 �Ĵ����ṹ���塣��ַƫ����:0x0044����ֵ:0x00000000�����:32
 �Ĵ���˵��: Focus window vertical parameters
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fw_y_strt_6  : 13; /* bit[0-12] : Focus window vertical start */
        unsigned int  reserved_0   : 3;  /* bit[13-15]:  */
        unsigned int  fw_y_width_6 : 13; /* bit[16-28]: Focus window vertical height */
        unsigned int  reserved_1   : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_STAT3A_FW_Y_6_UNION;
#endif
#define SOC_ISP_STAT3A_FW_Y_6_fw_y_strt_6_START   (0)
#define SOC_ISP_STAT3A_FW_Y_6_fw_y_strt_6_END     (12)
#define SOC_ISP_STAT3A_FW_Y_6_fw_y_width_6_START  (16)
#define SOC_ISP_STAT3A_FW_Y_6_fw_y_width_6_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_FW_X_7_UNION
 �ṹ˵��  : FW_X_7 �Ĵ����ṹ���塣��ַƫ����:0x0048����ֵ:0x00000000�����:32
 �Ĵ���˵��: Focus window horizontal parameters
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fw_x_strt_7  : 13; /* bit[0-12] : Focus window horizontal start */
        unsigned int  reserved_0   : 3;  /* bit[13-15]:  */
        unsigned int  fw_x_width_7 : 13; /* bit[16-28]: Focus window horizontal width */
        unsigned int  reserved_1   : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_STAT3A_FW_X_7_UNION;
#endif
#define SOC_ISP_STAT3A_FW_X_7_fw_x_strt_7_START   (0)
#define SOC_ISP_STAT3A_FW_X_7_fw_x_strt_7_END     (12)
#define SOC_ISP_STAT3A_FW_X_7_fw_x_width_7_START  (16)
#define SOC_ISP_STAT3A_FW_X_7_fw_x_width_7_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_FW_Y_7_UNION
 �ṹ˵��  : FW_Y_7 �Ĵ����ṹ���塣��ַƫ����:0x004C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Focus window vertical parameters
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fw_y_strt_7  : 13; /* bit[0-12] : Focus window vertical start */
        unsigned int  reserved_0   : 3;  /* bit[13-15]:  */
        unsigned int  fw_y_width_7 : 13; /* bit[16-28]: Focus window vertical height */
        unsigned int  reserved_1   : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_STAT3A_FW_Y_7_UNION;
#endif
#define SOC_ISP_STAT3A_FW_Y_7_fw_y_strt_7_START   (0)
#define SOC_ISP_STAT3A_FW_Y_7_fw_y_strt_7_END     (12)
#define SOC_ISP_STAT3A_FW_Y_7_fw_y_width_7_START  (16)
#define SOC_ISP_STAT3A_FW_Y_7_fw_y_width_7_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_FW_X_8_UNION
 �ṹ˵��  : FW_X_8 �Ĵ����ṹ���塣��ַƫ����:0x0050����ֵ:0x00000000�����:32
 �Ĵ���˵��: Focus window horizontal parameters
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fw_x_strt_8  : 13; /* bit[0-12] : Focus window horizontal start */
        unsigned int  reserved_0   : 3;  /* bit[13-15]:  */
        unsigned int  fw_x_width_8 : 13; /* bit[16-28]: Focus window horizontal width */
        unsigned int  reserved_1   : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_STAT3A_FW_X_8_UNION;
#endif
#define SOC_ISP_STAT3A_FW_X_8_fw_x_strt_8_START   (0)
#define SOC_ISP_STAT3A_FW_X_8_fw_x_strt_8_END     (12)
#define SOC_ISP_STAT3A_FW_X_8_fw_x_width_8_START  (16)
#define SOC_ISP_STAT3A_FW_X_8_fw_x_width_8_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_FW_Y_8_UNION
 �ṹ˵��  : FW_Y_8 �Ĵ����ṹ���塣��ַƫ����:0x0054����ֵ:0x00000000�����:32
 �Ĵ���˵��: Focus window vertical parameters
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fw_y_strt_8  : 13; /* bit[0-12] : Focus window vertical start */
        unsigned int  reserved_0   : 3;  /* bit[13-15]:  */
        unsigned int  fw_y_width_8 : 13; /* bit[16-28]: Focus window vertical height */
        unsigned int  reserved_1   : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_STAT3A_FW_Y_8_UNION;
#endif
#define SOC_ISP_STAT3A_FW_Y_8_fw_y_strt_8_START   (0)
#define SOC_ISP_STAT3A_FW_Y_8_fw_y_strt_8_END     (12)
#define SOC_ISP_STAT3A_FW_Y_8_fw_y_width_8_START  (16)
#define SOC_ISP_STAT3A_FW_Y_8_fw_y_width_8_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_HIST_X_UNION
 �ṹ˵��  : HIST_X �Ĵ����ṹ���塣��ַƫ����:0x0058����ֵ:0x00000000�����:32
 �Ĵ���˵��: Histogram window horizontal parameters
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hist_x_strt  : 13; /* bit[0-12] : Histogram window horizontal start */
        unsigned int  reserved_0   : 3;  /* bit[13-15]:  */
        unsigned int  hist_x_width : 13; /* bit[16-28]: Histogram window horizontal width */
        unsigned int  reserved_1   : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_STAT3A_HIST_X_UNION;
#endif
#define SOC_ISP_STAT3A_HIST_X_hist_x_strt_START   (0)
#define SOC_ISP_STAT3A_HIST_X_hist_x_strt_END     (12)
#define SOC_ISP_STAT3A_HIST_X_hist_x_width_START  (16)
#define SOC_ISP_STAT3A_HIST_X_hist_x_width_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_HIST_Y_UNION
 �ṹ˵��  : HIST_Y �Ĵ����ṹ���塣��ַƫ����:0x005C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Histogram window vertical parameters
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hist_y_strt  : 13; /* bit[0-12] : Histogram window vertical start */
        unsigned int  reserved_0   : 3;  /* bit[13-15]:  */
        unsigned int  hist_y_width : 13; /* bit[16-28]: Histogram window vertical height */
        unsigned int  reserved_1   : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_STAT3A_HIST_Y_UNION;
#endif
#define SOC_ISP_STAT3A_HIST_Y_hist_y_strt_START   (0)
#define SOC_ISP_STAT3A_HIST_Y_hist_y_strt_END     (12)
#define SOC_ISP_STAT3A_HIST_Y_hist_y_width_START  (16)
#define SOC_ISP_STAT3A_HIST_Y_hist_y_width_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_AF_PARAM_1_UNION
 �ṹ˵��  : AF_PARAM_1 �Ĵ����ṹ���塣��ַƫ����:0x0060����ֵ:0x00000000�����:32
 �Ĵ���˵��: AF Parameters
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thld      : 24; /* bit[0-23] : Threshold */
        unsigned int  thld_en   : 1;  /* bit[24-24]: Threshold enable */
        unsigned int  fdog_dog  : 1;  /* bit[25-25]: fdog dog operator selection */
        unsigned int  square_en : 1;  /* bit[26-26]: square enable */
        unsigned int  reserved  : 3;  /* bit[27-29]:  */
        unsigned int  grad_sel  : 2;  /* bit[30-31]: Gradient histogram location selection */
    } reg;
} SOC_ISP_STAT3A_AF_PARAM_1_UNION;
#endif
#define SOC_ISP_STAT3A_AF_PARAM_1_thld_START       (0)
#define SOC_ISP_STAT3A_AF_PARAM_1_thld_END         (23)
#define SOC_ISP_STAT3A_AF_PARAM_1_thld_en_START    (24)
#define SOC_ISP_STAT3A_AF_PARAM_1_thld_en_END      (24)
#define SOC_ISP_STAT3A_AF_PARAM_1_fdog_dog_START   (25)
#define SOC_ISP_STAT3A_AF_PARAM_1_fdog_dog_END     (25)
#define SOC_ISP_STAT3A_AF_PARAM_1_square_en_START  (26)
#define SOC_ISP_STAT3A_AF_PARAM_1_square_en_END    (26)
#define SOC_ISP_STAT3A_AF_PARAM_1_grad_sel_START   (30)
#define SOC_ISP_STAT3A_AF_PARAM_1_grad_sel_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_Y_C0_UNION
 �ṹ˵��  : Y_C0 �Ĵ����ṹ���塣��ַƫ����:0x0064����ֵ:0x00000000�����:32
 �Ĵ���˵��: filter coefficient for Focus Value FIR
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_c00  : 9;  /* bit[0-8]  : x_v_flt_c0 */
        unsigned int  reserved_0: 7;  /* bit[9-15] :  */
        unsigned int  flt_c01  : 9;  /* bit[16-24]: x_v_flt_c1 */
        unsigned int  reserved_1: 7;  /* bit[25-31]:  */
    } reg;
} SOC_ISP_STAT3A_Y_C0_UNION;
#endif
#define SOC_ISP_STAT3A_Y_C0_flt_c00_START   (0)
#define SOC_ISP_STAT3A_Y_C0_flt_c00_END     (8)
#define SOC_ISP_STAT3A_Y_C0_flt_c01_START   (16)
#define SOC_ISP_STAT3A_Y_C0_flt_c01_END     (24)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_Y_C1_UNION
 �ṹ˵��  : Y_C1 �Ĵ����ṹ���塣��ַƫ����:0x0068����ֵ:0x00000000�����:32
 �Ĵ���˵��: filter coefficient for Focus Value FIR
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_c02  : 9;  /* bit[0-8]  : x_v_flt_c2 */
        unsigned int  reserved_0: 7;  /* bit[9-15] :  */
        unsigned int  flt_c03  : 9;  /* bit[16-24]: x_v_flt_c3 */
        unsigned int  reserved_1: 7;  /* bit[25-31]:  */
    } reg;
} SOC_ISP_STAT3A_Y_C1_UNION;
#endif
#define SOC_ISP_STAT3A_Y_C1_flt_c02_START   (0)
#define SOC_ISP_STAT3A_Y_C1_flt_c02_END     (8)
#define SOC_ISP_STAT3A_Y_C1_flt_c03_START   (16)
#define SOC_ISP_STAT3A_Y_C1_flt_c03_END     (24)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_Y_C2_UNION
 �ṹ˵��  : Y_C2 �Ĵ����ṹ���塣��ַƫ����:0x006C����ֵ:0x00000000�����:32
 �Ĵ���˵��: filter coefficient for Focus Value FIR
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_c04  : 9;  /* bit[0-8]  : x_v_flt_c4 */
        unsigned int  reserved_0: 7;  /* bit[9-15] :  */
        unsigned int  flt_c10  : 9;  /* bit[16-24]: x_h_flt_c0 */
        unsigned int  reserved_1: 7;  /* bit[25-31]:  */
    } reg;
} SOC_ISP_STAT3A_Y_C2_UNION;
#endif
#define SOC_ISP_STAT3A_Y_C2_flt_c04_START   (0)
#define SOC_ISP_STAT3A_Y_C2_flt_c04_END     (8)
#define SOC_ISP_STAT3A_Y_C2_flt_c10_START   (16)
#define SOC_ISP_STAT3A_Y_C2_flt_c10_END     (24)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_Y_C3_UNION
 �ṹ˵��  : Y_C3 �Ĵ����ṹ���塣��ַƫ����:0x0070����ֵ:0x00000000�����:32
 �Ĵ���˵��: filter coefficient for Focus Value FIR
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_c11  : 9;  /* bit[0-8]  : x_h_flt_c1 */
        unsigned int  reserved_0: 7;  /* bit[9-15] :  */
        unsigned int  flt_c12  : 9;  /* bit[16-24]: x_h_flt_c2 */
        unsigned int  reserved_1: 7;  /* bit[25-31]:  */
    } reg;
} SOC_ISP_STAT3A_Y_C3_UNION;
#endif
#define SOC_ISP_STAT3A_Y_C3_flt_c11_START   (0)
#define SOC_ISP_STAT3A_Y_C3_flt_c11_END     (8)
#define SOC_ISP_STAT3A_Y_C3_flt_c12_START   (16)
#define SOC_ISP_STAT3A_Y_C3_flt_c12_END     (24)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_Y_C4_UNION
 �ṹ˵��  : Y_C4 �Ĵ����ṹ���塣��ַƫ����:0x0074����ֵ:0x00000000�����:32
 �Ĵ���˵��: filter coefficient for Focus Value FIR
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_c13  : 9;  /* bit[0-8]  : x_h_flt_c3 */
        unsigned int  reserved_0: 7;  /* bit[9-15] :  */
        unsigned int  flt_c14  : 9;  /* bit[16-24]: x_h_flt_c4 */
        unsigned int  reserved_1: 7;  /* bit[25-31]:  */
    } reg;
} SOC_ISP_STAT3A_Y_C4_UNION;
#endif
#define SOC_ISP_STAT3A_Y_C4_flt_c13_START   (0)
#define SOC_ISP_STAT3A_Y_C4_flt_c13_END     (8)
#define SOC_ISP_STAT3A_Y_C4_flt_c14_START   (16)
#define SOC_ISP_STAT3A_Y_C4_flt_c14_END     (24)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_Y_C5_UNION
 �ṹ˵��  : Y_C5 �Ĵ����ṹ���塣��ַƫ����:0x0078����ֵ:0x00000000�����:32
 �Ĵ���˵��: filter coefficient for Focus Value FIR
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_c20  : 9;  /* bit[0-8]  : y_v_flt_c0 */
        unsigned int  reserved_0: 7;  /* bit[9-15] :  */
        unsigned int  flt_c21  : 9;  /* bit[16-24]: y_v_flt_c1 */
        unsigned int  reserved_1: 7;  /* bit[25-31]:  */
    } reg;
} SOC_ISP_STAT3A_Y_C5_UNION;
#endif
#define SOC_ISP_STAT3A_Y_C5_flt_c20_START   (0)
#define SOC_ISP_STAT3A_Y_C5_flt_c20_END     (8)
#define SOC_ISP_STAT3A_Y_C5_flt_c21_START   (16)
#define SOC_ISP_STAT3A_Y_C5_flt_c21_END     (24)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_Y_C6_UNION
 �ṹ˵��  : Y_C6 �Ĵ����ṹ���塣��ַƫ����:0x007C����ֵ:0x00000000�����:32
 �Ĵ���˵��: filter coefficient for Focus Value FIR
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_c22  : 9;  /* bit[0-8]  : y_v_flt_c2 */
        unsigned int  reserved_0: 7;  /* bit[9-15] :  */
        unsigned int  flt_c23  : 9;  /* bit[16-24]: y_v_flt_c3 */
        unsigned int  reserved_1: 7;  /* bit[25-31]:  */
    } reg;
} SOC_ISP_STAT3A_Y_C6_UNION;
#endif
#define SOC_ISP_STAT3A_Y_C6_flt_c22_START   (0)
#define SOC_ISP_STAT3A_Y_C6_flt_c22_END     (8)
#define SOC_ISP_STAT3A_Y_C6_flt_c23_START   (16)
#define SOC_ISP_STAT3A_Y_C6_flt_c23_END     (24)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_Y_C7_UNION
 �ṹ˵��  : Y_C7 �Ĵ����ṹ���塣��ַƫ����:0x0080����ֵ:0x00000000�����:32
 �Ĵ���˵��: filter coefficient for Focus Value FIR
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_c24  : 9;  /* bit[0-8]  : y_v_flt_c4 */
        unsigned int  reserved_0: 7;  /* bit[9-15] :  */
        unsigned int  flt_c30  : 9;  /* bit[16-24]: y_h_flt_c0 */
        unsigned int  reserved_1: 7;  /* bit[25-31]:  */
    } reg;
} SOC_ISP_STAT3A_Y_C7_UNION;
#endif
#define SOC_ISP_STAT3A_Y_C7_flt_c24_START   (0)
#define SOC_ISP_STAT3A_Y_C7_flt_c24_END     (8)
#define SOC_ISP_STAT3A_Y_C7_flt_c30_START   (16)
#define SOC_ISP_STAT3A_Y_C7_flt_c30_END     (24)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_Y_C8_UNION
 �ṹ˵��  : Y_C8 �Ĵ����ṹ���塣��ַƫ����:0x0084����ֵ:0x00000000�����:32
 �Ĵ���˵��: filter coefficient for Focus Value FIR
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_c31  : 9;  /* bit[0-8]  : y_h_flt_c1 */
        unsigned int  reserved_0: 7;  /* bit[9-15] :  */
        unsigned int  flt_c32  : 9;  /* bit[16-24]: y_h_flt_c2 */
        unsigned int  reserved_1: 7;  /* bit[25-31]:  */
    } reg;
} SOC_ISP_STAT3A_Y_C8_UNION;
#endif
#define SOC_ISP_STAT3A_Y_C8_flt_c31_START   (0)
#define SOC_ISP_STAT3A_Y_C8_flt_c31_END     (8)
#define SOC_ISP_STAT3A_Y_C8_flt_c32_START   (16)
#define SOC_ISP_STAT3A_Y_C8_flt_c32_END     (24)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_Y_C9_UNION
 �ṹ˵��  : Y_C9 �Ĵ����ṹ���塣��ַƫ����:0x0088����ֵ:0x00000000�����:32
 �Ĵ���˵��: filter coefficient for Focus Value FIR
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flt_c33  : 9;  /* bit[0-8]  : y_h_flt_c3 */
        unsigned int  reserved_0: 7;  /* bit[9-15] :  */
        unsigned int  flt_c34  : 9;  /* bit[16-24]: y_h_flt_c4 */
        unsigned int  reserved_1: 7;  /* bit[25-31]:  */
    } reg;
} SOC_ISP_STAT3A_Y_C9_UNION;
#endif
#define SOC_ISP_STAT3A_Y_C9_flt_c33_START   (0)
#define SOC_ISP_STAT3A_Y_C9_flt_c33_END     (8)
#define SOC_ISP_STAT3A_Y_C9_flt_c34_START   (16)
#define SOC_ISP_STAT3A_Y_C9_flt_c34_END     (24)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_BLOCKNUM_UNION
 �ṹ˵��  : BLOCKNUM �Ĵ����ṹ���塣��ַƫ����:0x008C����ֵ:0x00000000�����:32
 �Ĵ���˵��: number of paxels in frame
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  numv     : 5;  /* bit[0-4]  : number of rows of blocks, range [8,32] */
        unsigned int  reserved_0: 11; /* bit[5-15] :  */
        unsigned int  numh     : 5;  /* bit[16-20]: number of columns of blocks, range [8,32] */
        unsigned int  reserved_1: 11; /* bit[21-31]:  */
    } reg;
} SOC_ISP_STAT3A_BLOCKNUM_UNION;
#endif
#define SOC_ISP_STAT3A_BLOCKNUM_numv_START      (0)
#define SOC_ISP_STAT3A_BLOCKNUM_numv_END        (4)
#define SOC_ISP_STAT3A_BLOCKNUM_numh_START      (16)
#define SOC_ISP_STAT3A_BLOCKNUM_numh_END        (20)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_BLOCKWIN_UNION
 �ṹ˵��  : BLOCKWIN �Ĵ����ṹ���塣��ַƫ����:0x000090����ֵ:0x00000000�����:32
 �Ĵ���˵��: size of paxels in frame
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  winv     : 10; /* bit[0-9]  : width of every blocks, range [12,832] */
        unsigned int  reserved_0: 6;  /* bit[10-15]:  */
        unsigned int  winh     : 10; /* bit[16-25]: height of every block, range [12,624] */
        unsigned int  reserved_1: 6;  /* bit[26-31]:  */
    } reg;
} SOC_ISP_STAT3A_BLOCKWIN_UNION;
#endif
#define SOC_ISP_STAT3A_BLOCKWIN_winv_START      (0)
#define SOC_ISP_STAT3A_BLOCKWIN_winv_END        (9)
#define SOC_ISP_STAT3A_BLOCKWIN_winh_START      (16)
#define SOC_ISP_STAT3A_BLOCKWIN_winh_END        (25)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_COLUMNOFFSET_UNION
 �ṹ˵��  : COLUMNOFFSET �Ĵ����ṹ���塣��ַƫ����:0x0094����ֵ:0x00000000�����:32
 �Ĵ���˵��: Column Offset for AE
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  startcol : 12; /* bit[0-11] :  */
        unsigned int  reserved_0: 4;  /* bit[12-15]:  */
        unsigned int  endcol   : 13; /* bit[16-28]:  */
        unsigned int  reserved_1: 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_STAT3A_COLUMNOFFSET_UNION;
#endif
#define SOC_ISP_STAT3A_COLUMNOFFSET_startcol_START  (0)
#define SOC_ISP_STAT3A_COLUMNOFFSET_startcol_END    (11)
#define SOC_ISP_STAT3A_COLUMNOFFSET_endcol_START    (16)
#define SOC_ISP_STAT3A_COLUMNOFFSET_endcol_END      (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_BINTHD_UNION
 �ṹ˵��  : BINTHD �Ĵ����ṹ���塣��ַƫ����:0x0098����ֵ:0x00000000�����:32
 �Ĵ���˵��: Threshold for cumulative histogram
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bin01thd : 12; /* bit[0-11] :  */
        unsigned int  reserved_0: 4;  /* bit[12-15]:  */
        unsigned int  bin23thd : 12; /* bit[16-27]:  */
        unsigned int  reserved_1: 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_STAT3A_BINTHD_UNION;
#endif
#define SOC_ISP_STAT3A_BINTHD_bin01thd_START  (0)
#define SOC_ISP_STAT3A_BINTHD_bin01thd_END    (11)
#define SOC_ISP_STAT3A_BINTHD_bin23thd_START  (16)
#define SOC_ISP_STAT3A_BINTHD_bin23thd_END    (27)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_LOCATIONROI01_UNION
 �ṹ˵��  : LOCATIONROI01 �Ĵ����ṹ���塣��ַƫ����:0x009C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ROI w,h
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  locationroi_0 : 13; /* bit[0-12] :  */
        unsigned int  reserved_0    : 3;  /* bit[13-15]:  */
        unsigned int  locationroi_1 : 13; /* bit[16-28]:  */
        unsigned int  reserved_1    : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_STAT3A_LOCATIONROI01_UNION;
#endif
#define SOC_ISP_STAT3A_LOCATIONROI01_locationroi_0_START  (0)
#define SOC_ISP_STAT3A_LOCATIONROI01_locationroi_0_END    (12)
#define SOC_ISP_STAT3A_LOCATIONROI01_locationroi_1_START  (16)
#define SOC_ISP_STAT3A_LOCATIONROI01_locationroi_1_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_LOCATIONROI23_UNION
 �ṹ˵��  : LOCATIONROI23 �Ĵ����ṹ���塣��ַƫ����:0x00A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: ROI w,h
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  locationroi_2 : 13; /* bit[0-12] :  */
        unsigned int  reserved_0    : 3;  /* bit[13-15]:  */
        unsigned int  locationroi_3 : 13; /* bit[16-28]:  */
        unsigned int  reserved_1    : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_STAT3A_LOCATIONROI23_UNION;
#endif
#define SOC_ISP_STAT3A_LOCATIONROI23_locationroi_2_START  (0)
#define SOC_ISP_STAT3A_LOCATIONROI23_locationroi_2_END    (12)
#define SOC_ISP_STAT3A_LOCATIONROI23_locationroi_3_START  (16)
#define SOC_ISP_STAT3A_LOCATIONROI23_locationroi_3_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_LOCATIONROI45_UNION
 �ṹ˵��  : LOCATIONROI45 �Ĵ����ṹ���塣��ַƫ����:0x00A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: ROI w,h
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  locationroi_4 : 13; /* bit[0-12] :  */
        unsigned int  reserved_0    : 3;  /* bit[13-15]:  */
        unsigned int  locationroi_5 : 13; /* bit[16-28]:  */
        unsigned int  reserved_1    : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_STAT3A_LOCATIONROI45_UNION;
#endif
#define SOC_ISP_STAT3A_LOCATIONROI45_locationroi_4_START  (0)
#define SOC_ISP_STAT3A_LOCATIONROI45_locationroi_4_END    (12)
#define SOC_ISP_STAT3A_LOCATIONROI45_locationroi_5_START  (16)
#define SOC_ISP_STAT3A_LOCATIONROI45_locationroi_5_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_LOCATIONROI67_UNION
 �ṹ˵��  : LOCATIONROI67 �Ĵ����ṹ���塣��ַƫ����:0x00A8����ֵ:0x00000000�����:32
 �Ĵ���˵��: ROI w,h
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  locationroi_6 : 13; /* bit[0-12] :  */
        unsigned int  reserved_0    : 3;  /* bit[13-15]:  */
        unsigned int  locationroi_7 : 13; /* bit[16-28]:  */
        unsigned int  reserved_1    : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_STAT3A_LOCATIONROI67_UNION;
#endif
#define SOC_ISP_STAT3A_LOCATIONROI67_locationroi_6_START  (0)
#define SOC_ISP_STAT3A_LOCATIONROI67_locationroi_6_END    (12)
#define SOC_ISP_STAT3A_LOCATIONROI67_locationroi_7_START  (16)
#define SOC_ISP_STAT3A_LOCATIONROI67_locationroi_7_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_LOCATIONROI89_UNION
 �ṹ˵��  : LOCATIONROI89 �Ĵ����ṹ���塣��ַƫ����:0x00AC����ֵ:0x00000000�����:32
 �Ĵ���˵��: ROI w,h
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  locationroi_8 : 13; /* bit[0-12] :  */
        unsigned int  reserved_0    : 3;  /* bit[13-15]:  */
        unsigned int  locationroi_9 : 13; /* bit[16-28]:  */
        unsigned int  reserved_1    : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_STAT3A_LOCATIONROI89_UNION;
#endif
#define SOC_ISP_STAT3A_LOCATIONROI89_locationroi_8_START  (0)
#define SOC_ISP_STAT3A_LOCATIONROI89_locationroi_8_END    (12)
#define SOC_ISP_STAT3A_LOCATIONROI89_locationroi_9_START  (16)
#define SOC_ISP_STAT3A_LOCATIONROI89_locationroi_9_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_SIZEROI01_UNION
 �ṹ˵��  : SIZEROI01 �Ĵ����ṹ���塣��ַƫ����:0x00B0����ֵ:0x00000000�����:32
 �Ĵ���˵��: ROI 0,1 width
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sizeroi_0 : 10; /* bit[0-9]  :  */
        unsigned int  reserved_0: 6;  /* bit[10-15]:  */
        unsigned int  sizeroi_1 : 10; /* bit[16-25]:  */
        unsigned int  reserved_1: 6;  /* bit[26-31]:  */
    } reg;
} SOC_ISP_STAT3A_SIZEROI01_UNION;
#endif
#define SOC_ISP_STAT3A_SIZEROI01_sizeroi_0_START  (0)
#define SOC_ISP_STAT3A_SIZEROI01_sizeroi_0_END    (9)
#define SOC_ISP_STAT3A_SIZEROI01_sizeroi_1_START  (16)
#define SOC_ISP_STAT3A_SIZEROI01_sizeroi_1_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_SIZEROI23_UNION
 �ṹ˵��  : SIZEROI23 �Ĵ����ṹ���塣��ַƫ����:0x00B4����ֵ:0x00000000�����:32
 �Ĵ���˵��: ROI 2,3 width
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sizeroi_2 : 10; /* bit[0-9]  :  */
        unsigned int  reserved_0: 6;  /* bit[10-15]:  */
        unsigned int  sizeroi_3 : 10; /* bit[16-25]:  */
        unsigned int  reserved_1: 6;  /* bit[26-31]:  */
    } reg;
} SOC_ISP_STAT3A_SIZEROI23_UNION;
#endif
#define SOC_ISP_STAT3A_SIZEROI23_sizeroi_2_START  (0)
#define SOC_ISP_STAT3A_SIZEROI23_sizeroi_2_END    (9)
#define SOC_ISP_STAT3A_SIZEROI23_sizeroi_3_START  (16)
#define SOC_ISP_STAT3A_SIZEROI23_sizeroi_3_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_SIZEROI45_UNION
 �ṹ˵��  : SIZEROI45 �Ĵ����ṹ���塣��ַƫ����:0x00B8����ֵ:0x00000000�����:32
 �Ĵ���˵��: ROI 4,5 width
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sizeroi_4 : 10; /* bit[0-9]  :  */
        unsigned int  reserved_0: 6;  /* bit[10-15]:  */
        unsigned int  sizeroi_5 : 10; /* bit[16-25]:  */
        unsigned int  reserved_1: 6;  /* bit[26-31]:  */
    } reg;
} SOC_ISP_STAT3A_SIZEROI45_UNION;
#endif
#define SOC_ISP_STAT3A_SIZEROI45_sizeroi_4_START  (0)
#define SOC_ISP_STAT3A_SIZEROI45_sizeroi_4_END    (9)
#define SOC_ISP_STAT3A_SIZEROI45_sizeroi_5_START  (16)
#define SOC_ISP_STAT3A_SIZEROI45_sizeroi_5_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_SIZEROI67_UNION
 �ṹ˵��  : SIZEROI67 �Ĵ����ṹ���塣��ַƫ����:0x00BC����ֵ:0x00000000�����:32
 �Ĵ���˵��: ROI 6,7 width
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sizeroi_6 : 10; /* bit[0-9]  :  */
        unsigned int  reserved_0: 6;  /* bit[10-15]:  */
        unsigned int  sizeroi_7 : 10; /* bit[16-25]:  */
        unsigned int  reserved_1: 6;  /* bit[26-31]:  */
    } reg;
} SOC_ISP_STAT3A_SIZEROI67_UNION;
#endif
#define SOC_ISP_STAT3A_SIZEROI67_sizeroi_6_START  (0)
#define SOC_ISP_STAT3A_SIZEROI67_sizeroi_6_END    (9)
#define SOC_ISP_STAT3A_SIZEROI67_sizeroi_7_START  (16)
#define SOC_ISP_STAT3A_SIZEROI67_sizeroi_7_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_SIZEROI8_UNION
 �ṹ˵��  : SIZEROI8 �Ĵ����ṹ���塣��ַƫ����:0x00C0����ֵ:0x00000000�����:32
 �Ĵ���˵��: ROI 9 width, and ROI heigth
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sizeroi_8 : 10; /* bit[0-9]  :  */
        unsigned int  reserved_0: 6;  /* bit[10-15]:  */
        unsigned int  sizeroi_h : 10; /* bit[16-25]: height for all ROI */
        unsigned int  reserved_1: 6;  /* bit[26-31]:  */
    } reg;
} SOC_ISP_STAT3A_SIZEROI8_UNION;
#endif
#define SOC_ISP_STAT3A_SIZEROI8_sizeroi_8_START  (0)
#define SOC_ISP_STAT3A_SIZEROI8_sizeroi_8_END    (9)
#define SOC_ISP_STAT3A_SIZEROI8_sizeroi_h_START  (16)
#define SOC_ISP_STAT3A_SIZEROI8_sizeroi_h_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_COLORVALUE_UNION
 �ṹ˵��  : COLORVALUE �Ĵ����ṹ���塣��ַƫ����:0x00C4����ֵ:0x00000000�����:32
 �Ĵ���˵��: AWB cfg
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  maxcolorvalue : 12; /* bit[0-11] :  */
        unsigned int  reserved_0    : 4;  /* bit[12-15]:  */
        unsigned int  mincolorvalue : 12; /* bit[16-27]:  */
        unsigned int  reserved_1    : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_STAT3A_COLORVALUE_UNION;
#endif
#define SOC_ISP_STAT3A_COLORVALUE_maxcolorvalue_START  (0)
#define SOC_ISP_STAT3A_COLORVALUE_maxcolorvalue_END    (11)
#define SOC_ISP_STAT3A_COLORVALUE_mincolorvalue_START  (16)
#define SOC_ISP_STAT3A_COLORVALUE_mincolorvalue_END    (27)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_GRAYZONETOP_UNION
 �ṹ˵��  : GRAYZONETOP �Ĵ����ṹ���塣��ַƫ����:0x00C8����ֵ:0x00000000�����:32
 �Ĵ���˵��: AWB cfg
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  topk     : 14; /* bit[0-13] :  */
        unsigned int  reserved_0: 2;  /* bit[14-15]:  */
        unsigned int  topb     : 14; /* bit[16-29]:  */
        unsigned int  reserved_1: 2;  /* bit[30-31]:  */
    } reg;
} SOC_ISP_STAT3A_GRAYZONETOP_UNION;
#endif
#define SOC_ISP_STAT3A_GRAYZONETOP_topk_START      (0)
#define SOC_ISP_STAT3A_GRAYZONETOP_topk_END        (13)
#define SOC_ISP_STAT3A_GRAYZONETOP_topb_START      (16)
#define SOC_ISP_STAT3A_GRAYZONETOP_topb_END        (29)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_GRAYZONEBOTTOM_UNION
 �ṹ˵��  : GRAYZONEBOTTOM �Ĵ����ṹ���塣��ַƫ����:0x00CC����ֵ:0x00000000�����:32
 �Ĵ���˵��: AWB cfg
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bottomk  : 14; /* bit[0-13] :  */
        unsigned int  reserved_0: 2;  /* bit[14-15]:  */
        unsigned int  bottomb  : 14; /* bit[16-29]:  */
        unsigned int  reserved_1: 2;  /* bit[30-31]:  */
    } reg;
} SOC_ISP_STAT3A_GRAYZONEBOTTOM_UNION;
#endif
#define SOC_ISP_STAT3A_GRAYZONEBOTTOM_bottomk_START   (0)
#define SOC_ISP_STAT3A_GRAYZONEBOTTOM_bottomk_END     (13)
#define SOC_ISP_STAT3A_GRAYZONEBOTTOM_bottomb_START   (16)
#define SOC_ISP_STAT3A_GRAYZONEBOTTOM_bottomb_END     (29)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_GRAYZONELEFT_UNION
 �ṹ˵��  : GRAYZONELEFT �Ĵ����ṹ���塣��ַƫ����:0x00D0����ֵ:0x00000000�����:32
 �Ĵ���˵��: AWB cfg
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  leftk    : 14; /* bit[0-13] :  */
        unsigned int  reserved_0: 2;  /* bit[14-15]:  */
        unsigned int  leftb    : 14; /* bit[16-29]:  */
        unsigned int  reserved_1: 2;  /* bit[30-31]:  */
    } reg;
} SOC_ISP_STAT3A_GRAYZONELEFT_UNION;
#endif
#define SOC_ISP_STAT3A_GRAYZONELEFT_leftk_START     (0)
#define SOC_ISP_STAT3A_GRAYZONELEFT_leftk_END       (13)
#define SOC_ISP_STAT3A_GRAYZONELEFT_leftb_START     (16)
#define SOC_ISP_STAT3A_GRAYZONELEFT_leftb_END       (29)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_GRAYZONERIGHT_UNION
 �ṹ˵��  : GRAYZONERIGHT �Ĵ����ṹ���塣��ַƫ����:0x00D4����ֵ:0x00000000�����:32
 �Ĵ���˵��: AWB cfg
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rightk   : 14; /* bit[0-13] :  */
        unsigned int  reserved_0: 2;  /* bit[14-15]:  */
        unsigned int  rightb   : 14; /* bit[16-29]:  */
        unsigned int  reserved_1: 2;  /* bit[30-31]:  */
    } reg;
} SOC_ISP_STAT3A_GRAYZONERIGHT_UNION;
#endif
#define SOC_ISP_STAT3A_GRAYZONERIGHT_rightk_START    (0)
#define SOC_ISP_STAT3A_GRAYZONERIGHT_rightk_END      (13)
#define SOC_ISP_STAT3A_GRAYZONERIGHT_rightb_START    (16)
#define SOC_ISP_STAT3A_GRAYZONERIGHT_rightb_END      (29)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_GREENLUMAVALUE_UNION
 �ṹ˵��  : GREENLUMAVALUE �Ĵ����ṹ���塣��ַƫ����:0x00D8����ֵ:0x00000000�����:32
 �Ĵ���˵��: AWB cfg
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  maxvalue : 12; /* bit[0-11] :  */
        unsigned int  reserved_0: 4;  /* bit[12-15]:  */
        unsigned int  minvalue : 12; /* bit[16-27]:  */
        unsigned int  reserved_1: 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_STAT3A_GREENLUMAVALUE_UNION;
#endif
#define SOC_ISP_STAT3A_GREENLUMAVALUE_maxvalue_START  (0)
#define SOC_ISP_STAT3A_GREENLUMAVALUE_maxvalue_END    (11)
#define SOC_ISP_STAT3A_GREENLUMAVALUE_minvalue_START  (16)
#define SOC_ISP_STAT3A_GREENLUMAVALUE_minvalue_END    (27)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_GREENCEN_UNION
 �ṹ˵��  : GREENCEN �Ĵ����ṹ���塣��ַƫ����:0x00DC����ֵ:0x00000000�����:32
 �Ĵ���˵��: AWB cfg
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  greencenrg : 12; /* bit[0-11] :  */
        unsigned int  reserved_0 : 4;  /* bit[12-15]:  */
        unsigned int  greencnbg  : 12; /* bit[16-27]:  */
        unsigned int  reserved_1 : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_STAT3A_GREENCEN_UNION;
#endif
#define SOC_ISP_STAT3A_GREENCEN_greencenrg_START  (0)
#define SOC_ISP_STAT3A_GREENCEN_greencenrg_END    (11)
#define SOC_ISP_STAT3A_GREENCEN_greencnbg_START   (16)
#define SOC_ISP_STAT3A_GREENCEN_greencnbg_END     (27)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_GREENDISTCOEF_UNION
 �ṹ˵��  : GREENDISTCOEF �Ĵ����ṹ���塣��ַƫ����:0x00E0����ֵ:0x00000000�����:32
 �Ĵ���˵��: AWB cfg
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  greendistrg : 16; /* bit[0-15] :  */
        unsigned int  greendistbg : 16; /* bit[16-31]:  */
    } reg;
} SOC_ISP_STAT3A_GREENDISTCOEF_UNION;
#endif
#define SOC_ISP_STAT3A_GREENDISTCOEF_greendistrg_START  (0)
#define SOC_ISP_STAT3A_GREENDISTCOEF_greendistrg_END    (15)
#define SOC_ISP_STAT3A_GREENDISTCOEF_greendistbg_START  (16)
#define SOC_ISP_STAT3A_GREENDISTCOEF_greendistbg_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_GREENDIST_UNION
 �ṹ˵��  : GREENDIST �Ĵ����ṹ���塣��ַƫ����:0x00E4����ֵ:0x00000000�����:32
 �Ĵ���˵��: AWB cfg
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crosscoef : 16; /* bit[0-15] :  */
        unsigned int  thresh    : 12; /* bit[16-27]:  */
        unsigned int  reserved  : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_STAT3A_GREENDIST_UNION;
#endif
#define SOC_ISP_STAT3A_GREENDIST_crosscoef_START  (0)
#define SOC_ISP_STAT3A_GREENDIST_crosscoef_END    (15)
#define SOC_ISP_STAT3A_GREENDIST_thresh_START     (16)
#define SOC_ISP_STAT3A_GREENDIST_thresh_END       (27)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_RGBHIST_UNION
 �ṹ˵��  : RGBHIST �Ĵ����ṹ���塣��ַƫ����:0x00E8����ֵ:0x00000000�����:32
 �Ĵ���˵��: rgb Hist param
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rgbhistmin   : 12; /* bit[0-11] :  */
        unsigned int  reserved_0   : 4;  /* bit[12-15]:  */
        unsigned int  rgbhistshift : 4;  /* bit[16-19]:  */
        unsigned int  reserved_1   : 12; /* bit[20-31]:  */
    } reg;
} SOC_ISP_STAT3A_RGBHIST_UNION;
#endif
#define SOC_ISP_STAT3A_RGBHIST_rgbhistmin_START    (0)
#define SOC_ISP_STAT3A_RGBHIST_rgbhistmin_END      (11)
#define SOC_ISP_STAT3A_RGBHIST_rgbhistshift_START  (16)
#define SOC_ISP_STAT3A_RGBHIST_rgbhistshift_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_PREGAIN_UNION
 �ṹ˵��  : PREGAIN �Ĵ����ṹ���塣��ַƫ����:0x00EC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rgpregain : 12; /* bit[0-11] :  */
        unsigned int  reserved_0: 4;  /* bit[12-15]:  */
        unsigned int  bgpregain : 12; /* bit[16-27]:  */
        unsigned int  reserved_1: 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_STAT3A_PREGAIN_UNION;
#endif
#define SOC_ISP_STAT3A_PREGAIN_rgpregain_START  (0)
#define SOC_ISP_STAT3A_PREGAIN_rgpregain_END    (11)
#define SOC_ISP_STAT3A_PREGAIN_bgpregain_START  (16)
#define SOC_ISP_STAT3A_PREGAIN_bgpregain_END    (27)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_LUMACOEF_UNION
 �ṹ˵��  : LUMACOEF �Ĵ����ṹ���塣��ַƫ����:0x00F0����ֵ:0x00000000�����:32
 �Ĵ���˵��: Coefficient for Luma computation
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rcoef    : 8;  /* bit[0-7]  :  */
        unsigned int  gcoef    : 8;  /* bit[8-15] :  */
        unsigned int  bcoef    : 8;  /* bit[16-23]:  */
        unsigned int  reserved : 8;  /* bit[24-31]:  */
    } reg;
} SOC_ISP_STAT3A_LUMACOEF_UNION;
#endif
#define SOC_ISP_STAT3A_LUMACOEF_rcoef_START     (0)
#define SOC_ISP_STAT3A_LUMACOEF_rcoef_END       (7)
#define SOC_ISP_STAT3A_LUMACOEF_gcoef_START     (8)
#define SOC_ISP_STAT3A_LUMACOEF_gcoef_END       (15)
#define SOC_ISP_STAT3A_LUMACOEF_bcoef_START     (16)
#define SOC_ISP_STAT3A_LUMACOEF_bcoef_END       (23)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STAT3A_AF_PARAM_2_UNION
 �ṹ˵��  : AF_PARAM_2 �Ĵ����ṹ���塣��ַƫ����:0x00F4����ֵ:0x00000000�����:32
 �Ĵ���˵��: AF Parameters
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hist_shft : 4;  /* bit[0-3] : Luminance histogram shift */
        unsigned int  reserved  : 28; /* bit[4-31]:  */
    } reg;
} SOC_ISP_STAT3A_AF_PARAM_2_UNION;
#endif
#define SOC_ISP_STAT3A_AF_PARAM_2_hist_shft_START  (0)
#define SOC_ISP_STAT3A_AF_PARAM_2_hist_shft_END    (3)






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

#endif /* end of soc_isp_stat3a_interface.h */
