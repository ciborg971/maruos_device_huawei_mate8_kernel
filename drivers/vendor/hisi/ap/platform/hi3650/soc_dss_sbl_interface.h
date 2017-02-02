/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_dss_sbl_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:20:23
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_DSS_SBL.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_DSS_SBL_INTERFACE_H__
#define __SOC_DSS_SBL_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_SBL
 ****************************************************************************/
/* �Ĵ���˵�������ݸ�ʽ
   λ����UNION�ṹ:  SOC_DSS_SBL_DATA_FORMAT_UNION */
#define SOC_DSS_SBL_DATA_FORMAT_ADDR(base)            ((base) + (0x0000))

/* �Ĵ���˵�������ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_SBL_CONTROL_REG1_UNION */
#define SOC_DSS_SBL_CONTROL_REG1_ADDR(base)           ((base) + (0x0004))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_HS_POS_L_UNION */
#define SOC_DSS_SBL_HS_POS_L_ADDR(base)               ((base) + (0x0008))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_HS_POS_H_UNION */
#define SOC_DSS_SBL_HS_POS_H_ADDR(base)               ((base) + (0x000C))

/* �Ĵ���˵����֡���
   λ����UNION�ṹ:  SOC_DSS_SBL_FRAME_WIDTH_L_UNION */
#define SOC_DSS_SBL_FRAME_WIDTH_L_ADDR(base)          ((base) + (0x0010))

/* �Ĵ���˵����֡���
   λ����UNION�ṹ:  SOC_DSS_SBL_FRAME_WIDTH_H_UNION */
#define SOC_DSS_SBL_FRAME_WIDTH_H_ADDR(base)          ((base) + (0x00000014))

/* �Ĵ���˵����֡�߶�
   λ����UNION�ṹ:  SOC_DSS_SBL_FRAME_HEIGHT_L_UNION */
#define SOC_DSS_SBL_FRAME_HEIGHT_L_ADDR(base)         ((base) + (0x0018))

/* �Ĵ���˵����֡�߶�
   λ����UNION�ṹ:  SOC_DSS_SBL_FRAME_HEIGHT_H_UNION */
#define SOC_DSS_SBL_FRAME_HEIGHT_H_ADDR(base)         ((base) + (0x001C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_VS_POS_L_UNION */
#define SOC_DSS_SBL_VS_POS_L_ADDR(base)               ((base) + (0x0020))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_VS_POS_H_UNION */
#define SOC_DSS_SBL_VS_POS_H_ADDR(base)               ((base) + (0x0024))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_ENABLE_UNION */
#define SOC_DSS_SBL_ENABLE_ADDR(base)                 ((base) + (0x0400))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_STRENGTH_UNION */
#define SOC_DSS_SBL_STRENGTH_ADDR(base)               ((base) + (0x0408))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_VARIANCE_INTENSITY_SPACE_UNION */
#define SOC_DSS_SBL_VARIANCE_INTENSITY_SPACE_ADDR(base) ((base) + (0x040C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_SLOPE_MAX_UNION */
#define SOC_DSS_SBL_SLOPE_MAX_ADDR(base)              ((base) + (0x0410))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_SLOPE_MIN_UNION */
#define SOC_DSS_SBL_SLOPE_MIN_ADDR(base)              ((base) + (0x0414))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_BLACK_LEVEL_L_UNION */
#define SOC_DSS_SBL_BLACK_LEVEL_L_ADDR(base)          ((base) + (0x0418))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_BLACK_LEVEL_H_UNION */
#define SOC_DSS_SBL_BLACK_LEVEL_H_ADDR(base)          ((base) + (0x041C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_WHITE_LEVEL_L_UNION */
#define SOC_DSS_SBL_WHITE_LEVEL_L_ADDR(base)          ((base) + (0x0420))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_WHITE_LEVEL_H_UNION */
#define SOC_DSS_SBL_WHITE_LEVEL_H_ADDR(base)          ((base) + (0x0424))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_BRIGHT_DARK_AMP_LIMIT_UNION */
#define SOC_DSS_SBL_BRIGHT_DARK_AMP_LIMIT_ADDR(base)  ((base) + (0x0428))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_DITHER_MODE_UNION */
#define SOC_DSS_SBL_DITHER_MODE_ADDR(base)            ((base) + (0x042C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_CONFIG_BUFFER_MODE_UNION */
#define SOC_DSS_SBL_CONFIG_BUFFER_MODE_ADDR(base)     ((base) + (0x0430))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_CONFIG_BUFFER_GLOBAL_UNION */
#define SOC_DSS_SBL_CONFIG_BUFFER_GLOBAL_ADDR(base)   ((base) + (0x0434))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_ASYMMETRY_LUT_ADDR_UNION */
#define SOC_DSS_SBL_ASYMMETRY_LUT_ADDR_ADDR(base)     ((base) + (0x0480))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_ASYMMETRY_LUT_WRITE_DATA_L_UNION */
#define SOC_DSS_SBL_ASYMMETRY_LUT_WRITE_DATA_L_ADDR(base) ((base) + (0x0484))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_ASYMMETRY_LUT_WRITE_DATA_H_UNION */
#define SOC_DSS_SBL_ASYMMETRY_LUT_WRITE_DATA_H_ADDR(base) ((base) + (0x0488))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_COLOR_CORRECTION_LUT_ADDR_UNION */
#define SOC_DSS_SBL_COLOR_CORRECTION_LUT_ADDR_ADDR(base) ((base) + (0x04C0))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_COLOR_CORRECTION_LUT_WRITE_DATA_L_UNION */
#define SOC_DSS_SBL_COLOR_CORRECTION_LUT_WRITE_DATA_L_ADDR(base) ((base) + (0x04C4))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_COLOR_CORRECTION_LUT_WRITE_DATA_H_UNION */
#define SOC_DSS_SBL_COLOR_CORRECTION_LUT_WRITE_DATA_H_ADDR(base) ((base) + (0x04C8))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_LOGO_LEFT_UNION */
#define SOC_DSS_SBL_LOGO_LEFT_ADDR(base)              ((base) + (0x0800))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_LOGO_TOP_UNION */
#define SOC_DSS_SBL_LOGO_TOP_ADDR(base)               ((base) + (0x0804))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_APICAL_DITHER_UNION */
#define SOC_DSS_SBL_APICAL_DITHER_ADDR(base)          ((base) + (0x0840))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_UNION */
#define SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_ADDR(base) ((base) + (0x0C00))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_STRENGTH_MANUAL_UNION */
#define SOC_DSS_SBL_STRENGTH_MANUAL_ADDR(base)        ((base) + (0x0C04))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_DRC_IN_L_UNION */
#define SOC_DSS_SBL_DRC_IN_L_ADDR(base)               ((base) + (0x0C08))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_DRC_IN_H_UNION */
#define SOC_DSS_SBL_DRC_IN_H_ADDR(base)               ((base) + (0x0C0C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_BACKLIGHT_L_UNION */
#define SOC_DSS_SBL_BACKLIGHT_L_ADDR(base)            ((base) + (0x0C10))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_BACKLIGHT_H_UNION */
#define SOC_DSS_SBL_BACKLIGHT_H_ADDR(base)            ((base) + (0x0C14))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_AMBIENT_LIGHT_L_UNION */
#define SOC_DSS_SBL_AMBIENT_LIGHT_L_ADDR(base)        ((base) + (0x0C18))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_AMBIENT_LIGHT_H_UNION */
#define SOC_DSS_SBL_AMBIENT_LIGHT_H_ADDR(base)        ((base) + (0x0C1C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_START_CALC_UNION */
#define SOC_DSS_SBL_START_CALC_ADDR(base)             ((base) + (0x0C20))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_STRENGTH_LIMIT_UNION */
#define SOC_DSS_SBL_STRENGTH_LIMIT_ADDR(base)         ((base) + (0x0C24))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_CALIBRATION_A_L_UNION */
#define SOC_DSS_SBL_CALIBRATION_A_L_ADDR(base)        ((base) + (0x0C28))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_CALIBRATION_A_H_UNION */
#define SOC_DSS_SBL_CALIBRATION_A_H_ADDR(base)        ((base) + (0x0C2C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_CALIBRATION_B_L_UNION */
#define SOC_DSS_SBL_CALIBRATION_B_L_ADDR(base)        ((base) + (0x0C30))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_CALIBRATION_B_H_UNION */
#define SOC_DSS_SBL_CALIBRATION_B_H_ADDR(base)        ((base) + (0x0C34))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_CALIBRATION_C_L_UNION */
#define SOC_DSS_SBL_CALIBRATION_C_L_ADDR(base)        ((base) + (0x0C38))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_CALIBRATION_C_H_UNION */
#define SOC_DSS_SBL_CALIBRATION_C_H_ADDR(base)        ((base) + (0x0C3C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_CALIBRATION_D_L_UNION */
#define SOC_DSS_SBL_CALIBRATION_D_L_ADDR(base)        ((base) + (0x0C40))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_CALIBRATION_D_H_UNION */
#define SOC_DSS_SBL_CALIBRATION_D_H_ADDR(base)        ((base) + (0x0C44))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_T_FILTER_CONTROL_UNION */
#define SOC_DSS_SBL_T_FILTER_CONTROL_ADDR(base)       ((base) + (0x0C48))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_BACKLIGHT_MIN_L_UNION */
#define SOC_DSS_SBL_BACKLIGHT_MIN_L_ADDR(base)        ((base) + (0x0C4C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_BACKLIGHT_MIN_H_UNION */
#define SOC_DSS_SBL_BACKLIGHT_MIN_H_ADDR(base)        ((base) + (0x0C50))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_BACKLIGHT_MAX_L_UNION */
#define SOC_DSS_SBL_BACKLIGHT_MAX_L_ADDR(base)        ((base) + (0x0C54))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_BACKLIGHT_MAX_H_UNION */
#define SOC_DSS_SBL_BACKLIGHT_MAX_H_ADDR(base)        ((base) + (0x0C58))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_BACKLIGHT_SCALE_L_UNION */
#define SOC_DSS_SBL_BACKLIGHT_SCALE_L_ADDR(base)      ((base) + (0x0C5C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_BACKLIGHT_SCALE_H_UNION */
#define SOC_DSS_SBL_BACKLIGHT_SCALE_H_ADDR(base)      ((base) + (0x0C60))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_AMBIENT_LIGHT_MIN_L_UNION */
#define SOC_DSS_SBL_AMBIENT_LIGHT_MIN_L_ADDR(base)    ((base) + (0x0C64))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_AMBIENT_LIGHT_MIN_H_UNION */
#define SOC_DSS_SBL_AMBIENT_LIGHT_MIN_H_ADDR(base)    ((base) + (0x0C68))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_FILTER_A_L_UNION */
#define SOC_DSS_SBL_FILTER_A_L_ADDR(base)             ((base) + (0x0C6C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_FILTER_A_H_UNION */
#define SOC_DSS_SBL_FILTER_A_H_ADDR(base)             ((base) + (0x0C70))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_FILTER_B_UNION */
#define SOC_DSS_SBL_FILTER_B_ADDR(base)               ((base) + (0x0C74))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_STRENGTH_OUT_UNION */
#define SOC_DSS_SBL_STRENGTH_OUT_ADDR(base)           ((base) + (0x0C80))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_DRC_OUT_L_UNION */
#define SOC_DSS_SBL_DRC_OUT_L_ADDR(base)              ((base) + (0x0C84))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_DRC_OUT_H_UNION */
#define SOC_DSS_SBL_DRC_OUT_H_ADDR(base)              ((base) + (0x0C88))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_BACKLIGHT_OUT_L_UNION */
#define SOC_DSS_SBL_BACKLIGHT_OUT_L_ADDR(base)        ((base) + (0x0C8C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_BACKLIGHT_OUT_H_UNION */
#define SOC_DSS_SBL_BACKLIGHT_OUT_H_ADDR(base)        ((base) + (0x0C90))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_CALC_DONE_UNION */
#define SOC_DSS_SBL_CALC_DONE_ADDR(base)              ((base) + (0x0C94))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_AL_CALIB_LUT_LUT_ADDR_UNION */
#define SOC_DSS_SBL_AL_CALIB_LUT_LUT_ADDR_ADDR(base)  ((base) + (0x0F00))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_AL_CALIB_LUT_LUT_WRITE_DATA_L_UNION */
#define SOC_DSS_SBL_AL_CALIB_LUT_LUT_WRITE_DATA_L_ADDR(base) ((base) + (0x0F10))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_SBL_AL_CALIB_LUT_LUT_WRITE_DATA_H_UNION */
#define SOC_DSS_SBL_AL_CALIB_LUT_LUT_WRITE_DATA_H_ADDR(base) ((base) + (0x0F14))





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
                     (1/1) reg_SBL
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_DATA_FORMAT_UNION
 �ṹ˵��  : DATA_FORMAT �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000003�����:32
 �Ĵ���˵��: ���ݸ�ʽ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  data_format : 2;  /* bit[0-1] :  */
        unsigned int  reserved    : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_DSS_SBL_DATA_FORMAT_UNION;
#endif
#define SOC_DSS_SBL_DATA_FORMAT_data_format_START  (0)
#define SOC_DSS_SBL_DATA_FORMAT_data_format_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_CONTROL_REG1_UNION
 �ṹ˵��  : CONTROL_REG1 �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  contrlo_reg1 : 8;  /* bit[0-7] :  */
        unsigned int  reserved     : 24; /* bit[8-31]: Control Reg1��sync_format��.Should be Zero */
    } reg;
} SOC_DSS_SBL_CONTROL_REG1_UNION;
#endif
#define SOC_DSS_SBL_CONTROL_REG1_contrlo_reg1_START  (0)
#define SOC_DSS_SBL_CONTROL_REG1_contrlo_reg1_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_HS_POS_L_UNION
 �ṹ˵��  : HS_POS_L �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hs_pos_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_HS_POS_L_UNION;
#endif
#define SOC_DSS_SBL_HS_POS_L_hs_pos_l_START  (0)
#define SOC_DSS_SBL_HS_POS_L_hs_pos_l_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_HS_POS_H_UNION
 �ṹ˵��  : HS_POS_H �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hs_pos_h : 8;  /* bit[0-7] :  */
        unsigned int  reserved : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_HS_POS_H_UNION;
#endif
#define SOC_DSS_SBL_HS_POS_H_hs_pos_h_START  (0)
#define SOC_DSS_SBL_HS_POS_H_hs_pos_h_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_FRAME_WIDTH_L_UNION
 �ṹ˵��  : FRAME_WIDTH_L �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: ֡���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frame_width_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved      : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_FRAME_WIDTH_L_UNION;
#endif
#define SOC_DSS_SBL_FRAME_WIDTH_L_frame_width_l_START  (0)
#define SOC_DSS_SBL_FRAME_WIDTH_L_frame_width_l_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_FRAME_WIDTH_H_UNION
 �ṹ˵��  : FRAME_WIDTH_H �Ĵ����ṹ���塣��ַƫ����:0x00000014����ֵ:0x00000001�����:32
 �Ĵ���˵��: ֡���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frame_width_h : 8;  /* bit[0-7] :  */
        unsigned int  reserved      : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_FRAME_WIDTH_H_UNION;
#endif
#define SOC_DSS_SBL_FRAME_WIDTH_H_frame_width_h_START  (0)
#define SOC_DSS_SBL_FRAME_WIDTH_H_frame_width_h_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_FRAME_HEIGHT_L_UNION
 �ṹ˵��  : FRAME_HEIGHT_L �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: ֡�߶�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frame_height_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved       : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_FRAME_HEIGHT_L_UNION;
#endif
#define SOC_DSS_SBL_FRAME_HEIGHT_L_frame_height_l_START  (0)
#define SOC_DSS_SBL_FRAME_HEIGHT_L_frame_height_l_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_FRAME_HEIGHT_H_UNION
 �ṹ˵��  : FRAME_HEIGHT_H �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000001�����:32
 �Ĵ���˵��: ֡�߶�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frame_height_h : 8;  /* bit[0-7] :  */
        unsigned int  reserved       : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_FRAME_HEIGHT_H_UNION;
#endif
#define SOC_DSS_SBL_FRAME_HEIGHT_H_frame_height_h_START  (0)
#define SOC_DSS_SBL_FRAME_HEIGHT_H_frame_height_h_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_VS_POS_L_UNION
 �ṹ˵��  : VS_POS_L �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vs_pos_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_VS_POS_L_UNION;
#endif
#define SOC_DSS_SBL_VS_POS_L_vs_pos_l_START  (0)
#define SOC_DSS_SBL_VS_POS_L_vs_pos_l_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_VS_POS_H_UNION
 �ṹ˵��  : VS_POS_H �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vs_pos_h : 8;  /* bit[0-7] :  */
        unsigned int  reserved : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_VS_POS_H_UNION;
#endif
#define SOC_DSS_SBL_VS_POS_H_vs_pos_h_START  (0)
#define SOC_DSS_SBL_VS_POS_H_vs_pos_h_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_ENABLE_UNION
 �ṹ˵��  : ENABLE �Ĵ����ṹ���塣��ַƫ����:0x0400����ֵ:0x00000007�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enable           : 1;  /* bit[0]   : 0:off 1:on */
        unsigned int  local_contrast   : 2;  /* bit[1-2] :  */
        unsigned int  reserved_0       : 1;  /* bit[3]   :  */
        unsigned int  color_correction : 1;  /* bit[4]   :  */
        unsigned int  reserved_1       : 27; /* bit[5-31]:  */
    } reg;
} SOC_DSS_SBL_ENABLE_UNION;
#endif
#define SOC_DSS_SBL_ENABLE_enable_START            (0)
#define SOC_DSS_SBL_ENABLE_enable_END              (0)
#define SOC_DSS_SBL_ENABLE_local_contrast_START    (1)
#define SOC_DSS_SBL_ENABLE_local_contrast_END      (2)
#define SOC_DSS_SBL_ENABLE_color_correction_START  (4)
#define SOC_DSS_SBL_ENABLE_color_correction_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_STRENGTH_UNION
 �ṹ˵��  : STRENGTH �Ĵ����ṹ���塣��ַƫ����:0x0408����ֵ:0x00000080�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  strength : 8;  /* bit[0-7] : Note:DO NOT USE (LEGACY BEHAV)-THIS REGISTER IS NOT USED TO CONTROL IRIDIX STRENGTH.USE strength_manual INSTEAD.Strength od dynamic range compression.With other parameters at defaults,increases visibility of shadows. */
        unsigned int  reserved : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_STRENGTH_UNION;
#endif
#define SOC_DSS_SBL_STRENGTH_strength_START  (0)
#define SOC_DSS_SBL_STRENGTH_strength_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_VARIANCE_INTENSITY_SPACE_UNION
 �ṹ˵��  : VARIANCE_INTENSITY_SPACE �Ĵ����ṹ���塣��ַƫ����:0x040C����ֵ:0x00000041�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  variance_space     : 4;  /* bit[0-3] : Sets the degree of spatial sensitivity of the algorithm */
        unsigned int  variance_intensity : 4;  /* bit[4-7] : Sets the degree of luminance sensitivity of the algorithm */
        unsigned int  reserved           : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_VARIANCE_INTENSITY_SPACE_UNION;
#endif
#define SOC_DSS_SBL_VARIANCE_INTENSITY_SPACE_variance_space_START      (0)
#define SOC_DSS_SBL_VARIANCE_INTENSITY_SPACE_variance_space_END        (3)
#define SOC_DSS_SBL_VARIANCE_INTENSITY_SPACE_variance_intensity_START  (4)
#define SOC_DSS_SBL_VARIANCE_INTENSITY_SPACE_variance_intensity_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_SLOPE_MAX_UNION
 �ṹ˵��  : SLOPE_MAX �Ĵ����ṹ���塣��ַƫ����:0x0410����ֵ:0x0000003C�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  slope_max : 8;  /* bit[0-7] : Restricts the maximum slope(gain) which can be generated by the adaptive algorithm */
        unsigned int  reserved  : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_SLOPE_MAX_UNION;
#endif
#define SOC_DSS_SBL_SLOPE_MAX_slope_max_START  (0)
#define SOC_DSS_SBL_SLOPE_MAX_slope_max_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_SLOPE_MIN_UNION
 �ṹ˵��  : SLOPE_MIN �Ĵ����ṹ���塣��ַƫ����:0x0414����ֵ:0x00000080�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  slope_min : 8;  /* bit[0-7] : Restricts the minimum slope(gain) which can be generated by the adaptive algorithm */
        unsigned int  reserved  : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_SLOPE_MIN_UNION;
#endif
#define SOC_DSS_SBL_SLOPE_MIN_slope_min_START  (0)
#define SOC_DSS_SBL_SLOPE_MIN_slope_min_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_BLACK_LEVEL_L_UNION
 �ṹ˵��  : BLACK_LEVEL_L �Ĵ����ṹ���塣��ַƫ����:0x0418����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  black_level_l : 8;  /* bit[0-7] : Sets black level for iridix processing */
        unsigned int  reserved      : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_BLACK_LEVEL_L_UNION;
#endif
#define SOC_DSS_SBL_BLACK_LEVEL_L_black_level_l_START  (0)
#define SOC_DSS_SBL_BLACK_LEVEL_L_black_level_l_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_BLACK_LEVEL_H_UNION
 �ṹ˵��  : BLACK_LEVEL_H �Ĵ����ṹ���塣��ַƫ����:0x041C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  black_level_h : 2;  /* bit[0-1] : Sets black level for iridix processing */
        unsigned int  reserved      : 30; /* bit[2-31]:  */
    } reg;
} SOC_DSS_SBL_BLACK_LEVEL_H_UNION;
#endif
#define SOC_DSS_SBL_BLACK_LEVEL_H_black_level_h_START  (0)
#define SOC_DSS_SBL_BLACK_LEVEL_H_black_level_h_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_WHITE_LEVEL_L_UNION
 �ṹ˵��  : WHITE_LEVEL_L �Ĵ����ṹ���塣��ַƫ����:0x0420����ֵ:0x000000FF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  white_level_l : 8;  /* bit[0-7] : Sets white level for iridix processing */
        unsigned int  reserved      : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_WHITE_LEVEL_L_UNION;
#endif
#define SOC_DSS_SBL_WHITE_LEVEL_L_white_level_l_START  (0)
#define SOC_DSS_SBL_WHITE_LEVEL_L_white_level_l_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_WHITE_LEVEL_H_UNION
 �ṹ˵��  : WHITE_LEVEL_H �Ĵ����ṹ���塣��ַƫ����:0x0424����ֵ:0x00000003�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  white_level_h : 2;  /* bit[0-1] : Sets white level for iridix processing */
        unsigned int  reserved      : 30; /* bit[2-31]:  */
    } reg;
} SOC_DSS_SBL_WHITE_LEVEL_H_UNION;
#endif
#define SOC_DSS_SBL_WHITE_LEVEL_H_white_level_h_START  (0)
#define SOC_DSS_SBL_WHITE_LEVEL_H_white_level_h_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_BRIGHT_DARK_AMP_LIMIT_UNION
 �ṹ˵��  : BRIGHT_DARK_AMP_LIMIT �Ĵ����ṹ���塣��ַƫ����:0x0428����ֵ:0x000000F0�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dark_amp_limit   : 4;  /* bit[0-3] :  */
        unsigned int  bright_amp_limit : 4;  /* bit[4-7] :  */
        unsigned int  reserved         : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_BRIGHT_DARK_AMP_LIMIT_UNION;
#endif
#define SOC_DSS_SBL_BRIGHT_DARK_AMP_LIMIT_dark_amp_limit_START    (0)
#define SOC_DSS_SBL_BRIGHT_DARK_AMP_LIMIT_dark_amp_limit_END      (3)
#define SOC_DSS_SBL_BRIGHT_DARK_AMP_LIMIT_bright_amp_limit_START  (4)
#define SOC_DSS_SBL_BRIGHT_DARK_AMP_LIMIT_bright_amp_limit_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_DITHER_MODE_UNION
 �ṹ˵��  : DITHER_MODE �Ĵ����ṹ���塣��ַƫ����:0x042C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dither_mode : 3;  /* bit[0-2] :  */
        unsigned int  reserved    : 29; /* bit[3-31]:  */
    } reg;
} SOC_DSS_SBL_DITHER_MODE_UNION;
#endif
#define SOC_DSS_SBL_DITHER_MODE_dither_mode_START  (0)
#define SOC_DSS_SBL_DITHER_MODE_dither_mode_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_CONFIG_BUFFER_MODE_UNION
 �ṹ˵��  : CONFIG_BUFFER_MODE �Ĵ����ṹ���塣��ַƫ����:0x0430����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  config_buffer_mode : 2;  /* bit[0-1] : double buffering control for video pipeline configuration parameters */
        unsigned int  reserved           : 30; /* bit[2-31]:  */
    } reg;
} SOC_DSS_SBL_CONFIG_BUFFER_MODE_UNION;
#endif
#define SOC_DSS_SBL_CONFIG_BUFFER_MODE_config_buffer_mode_START  (0)
#define SOC_DSS_SBL_CONFIG_BUFFER_MODE_config_buffer_mode_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_CONFIG_BUFFER_GLOBAL_UNION
 �ṹ˵��  : CONFIG_BUFFER_GLOBAL �Ĵ����ṹ���塣��ַƫ����:0x0434����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  config_buffer_global : 1;  /* bit[0]   : double buffering control for video pipeline configuration parameters */
        unsigned int  reserved             : 31; /* bit[1-31]:  */
    } reg;
} SOC_DSS_SBL_CONFIG_BUFFER_GLOBAL_UNION;
#endif
#define SOC_DSS_SBL_CONFIG_BUFFER_GLOBAL_config_buffer_global_START  (0)
#define SOC_DSS_SBL_CONFIG_BUFFER_GLOBAL_config_buffer_global_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_ASYMMETRY_LUT_ADDR_UNION
 �ṹ˵��  : ASYMMETRY_LUT_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0480����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asymmetry_lut_addr : 6;  /* bit[0-5] : LUT address register (valid range 0 to 32) */
        unsigned int  reserved           : 26; /* bit[6-31]:  */
    } reg;
} SOC_DSS_SBL_ASYMMETRY_LUT_ADDR_UNION;
#endif
#define SOC_DSS_SBL_ASYMMETRY_LUT_ADDR_asymmetry_lut_addr_START  (0)
#define SOC_DSS_SBL_ASYMMETRY_LUT_ADDR_asymmetry_lut_addr_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_ASYMMETRY_LUT_WRITE_DATA_L_UNION
 �ṹ˵��  : ASYMMETRY_LUT_WRITE_DATA_L �Ĵ����ṹ���塣��ַƫ����:0x0484����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asymmetry_lut_write_data_l : 8;  /* bit[0-7] : LUT write data register */
        unsigned int  reserved                   : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_ASYMMETRY_LUT_WRITE_DATA_L_UNION;
#endif
#define SOC_DSS_SBL_ASYMMETRY_LUT_WRITE_DATA_L_asymmetry_lut_write_data_l_START  (0)
#define SOC_DSS_SBL_ASYMMETRY_LUT_WRITE_DATA_L_asymmetry_lut_write_data_l_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_ASYMMETRY_LUT_WRITE_DATA_H_UNION
 �ṹ˵��  : ASYMMETRY_LUT_WRITE_DATA_H �Ĵ����ṹ���塣��ַƫ����:0x0488����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asymmetry_lut_write_data_h : 4;  /* bit[0-3] : LUT write data register 
                                                                       */
        unsigned int  reserved                   : 28; /* bit[4-31]:  */
    } reg;
} SOC_DSS_SBL_ASYMMETRY_LUT_WRITE_DATA_H_UNION;
#endif
#define SOC_DSS_SBL_ASYMMETRY_LUT_WRITE_DATA_H_asymmetry_lut_write_data_h_START  (0)
#define SOC_DSS_SBL_ASYMMETRY_LUT_WRITE_DATA_H_asymmetry_lut_write_data_h_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_COLOR_CORRECTION_LUT_ADDR_UNION
 �ṹ˵��  : COLOR_CORRECTION_LUT_ADDR �Ĵ����ṹ���塣��ַƫ����:0x04C0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  color_correction_lut_addr : 6;  /* bit[0-5] : LUT address register(valid range 0 to 32) */
        unsigned int  reserved                  : 26; /* bit[6-31]:  */
    } reg;
} SOC_DSS_SBL_COLOR_CORRECTION_LUT_ADDR_UNION;
#endif
#define SOC_DSS_SBL_COLOR_CORRECTION_LUT_ADDR_color_correction_lut_addr_START  (0)
#define SOC_DSS_SBL_COLOR_CORRECTION_LUT_ADDR_color_correction_lut_addr_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_COLOR_CORRECTION_LUT_WRITE_DATA_L_UNION
 �ṹ˵��  : COLOR_CORRECTION_LUT_WRITE_DATA_L �Ĵ����ṹ���塣��ַƫ����:0x04C4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  color_correction_lut_write_data_l : 8;  /* bit[0-7] : LUT write data register */
        unsigned int  reserved                          : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_COLOR_CORRECTION_LUT_WRITE_DATA_L_UNION;
#endif
#define SOC_DSS_SBL_COLOR_CORRECTION_LUT_WRITE_DATA_L_color_correction_lut_write_data_l_START  (0)
#define SOC_DSS_SBL_COLOR_CORRECTION_LUT_WRITE_DATA_L_color_correction_lut_write_data_l_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_COLOR_CORRECTION_LUT_WRITE_DATA_H_UNION
 �ṹ˵��  : COLOR_CORRECTION_LUT_WRITE_DATA_H �Ĵ����ṹ���塣��ַƫ����:0x04C8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  color_correction_lut_write_data_h : 4;  /* bit[0-3] : LUT write data register 
                                                                             
                                                                              */
        unsigned int  reserved                          : 28; /* bit[4-31]:  */
    } reg;
} SOC_DSS_SBL_COLOR_CORRECTION_LUT_WRITE_DATA_H_UNION;
#endif
#define SOC_DSS_SBL_COLOR_CORRECTION_LUT_WRITE_DATA_H_color_correction_lut_write_data_h_START  (0)
#define SOC_DSS_SBL_COLOR_CORRECTION_LUT_WRITE_DATA_H_color_correction_lut_write_data_h_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_LOGO_LEFT_UNION
 �ṹ˵��  : LOGO_LEFT �Ĵ����ṹ���塣��ַƫ����:0x0800����ֵ:0x00000002�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  logo_left : 8;  /* bit[0-7] : Sets x ordinate of logo(in 16-pixel steps) */
        unsigned int  reserved  : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_LOGO_LEFT_UNION;
#endif
#define SOC_DSS_SBL_LOGO_LEFT_logo_left_START  (0)
#define SOC_DSS_SBL_LOGO_LEFT_logo_left_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_LOGO_TOP_UNION
 �ṹ˵��  : LOGO_TOP �Ĵ����ṹ���塣��ַƫ����:0x0804����ֵ:0x00000002�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  logo_top : 8;  /* bit[0-7] : Sets y ordinate of logo(in 16-pixel steps) */
        unsigned int  reserved : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_LOGO_TOP_UNION;
#endif
#define SOC_DSS_SBL_LOGO_TOP_logo_top_START  (0)
#define SOC_DSS_SBL_LOGO_TOP_logo_top_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_APICAL_DITHER_UNION
 �ṹ˵��  : APICAL_DITHER �Ĵ����ṹ���塣��ַƫ����:0x0840����ֵ:0x00000003�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enable_dither : 1;  /* bit[0]   : Enable/Disable external dither module */
        unsigned int  shift_mode    : 1;  /* bit[1]   : 0=out is MSB aligned 1=out is LSB aligned */
        unsigned int  dither_amount : 2;  /* bit[2-3] : 0=dither 1 bit 1=dither 2 bits */
        unsigned int  reserved_0    : 3;  /* bit[4-6] :  */
        unsigned int  dither_bypass : 1;  /* bit[7]   : bypass dither module */
        unsigned int  reserved_1    : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_APICAL_DITHER_UNION;
#endif
#define SOC_DSS_SBL_APICAL_DITHER_enable_dither_START  (0)
#define SOC_DSS_SBL_APICAL_DITHER_enable_dither_END    (0)
#define SOC_DSS_SBL_APICAL_DITHER_shift_mode_START     (1)
#define SOC_DSS_SBL_APICAL_DITHER_shift_mode_END       (1)
#define SOC_DSS_SBL_APICAL_DITHER_dither_amount_START  (2)
#define SOC_DSS_SBL_APICAL_DITHER_dither_amount_END    (3)
#define SOC_DSS_SBL_APICAL_DITHER_dither_bypass_START  (7)
#define SOC_DSS_SBL_APICAL_DITHER_dither_bypass_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_UNION
 �ṹ˵��  : AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL �Ĵ����ṹ���塣��ַƫ����:0x0C00����ֵ:0x00000080�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  backlight_sel        : 1;  /* bit[0]   : Enable/Disable Manual Backlight */
        unsigned int  drc_sel              : 1;  /* bit[1]   : Enable/Disable Manual drc */
        unsigned int  strength_sel         : 1;  /* bit[2]   : Enable/Disable Manual strength */
        unsigned int  reserved_0           : 4;  /* bit[3-6] :  */
        unsigned int  automatic_start_calc : 1;  /* bit[7]   : Enable/Disable auto trigger of start calc */
        unsigned int  reserved_1           : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_UNION;
#endif
#define SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_backlight_sel_START         (0)
#define SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_backlight_sel_END           (0)
#define SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_drc_sel_START               (1)
#define SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_drc_sel_END                 (1)
#define SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_strength_sel_START          (2)
#define SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_strength_sel_END            (2)
#define SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_automatic_start_calc_START  (7)
#define SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_automatic_start_calc_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_STRENGTH_MANUAL_UNION
 �ṹ˵��  : STRENGTH_MANUAL �Ĵ����ṹ���塣��ַƫ����:0x0C04����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  strength_manual : 8;  /* bit[0-7] : Manual override value of iridix module strength when option_select=9(dec) */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_STRENGTH_MANUAL_UNION;
#endif
#define SOC_DSS_SBL_STRENGTH_MANUAL_strength_manual_START  (0)
#define SOC_DSS_SBL_STRENGTH_MANUAL_strength_manual_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_DRC_IN_L_UNION
 �ṹ˵��  : DRC_IN_L �Ĵ����ṹ���塣��ַƫ����:0x0C08����ֵ:0x000000FF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  drc_in_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_DRC_IN_L_UNION;
#endif
#define SOC_DSS_SBL_DRC_IN_L_drc_in_l_START  (0)
#define SOC_DSS_SBL_DRC_IN_L_drc_in_l_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_DRC_IN_H_UNION
 �ṹ˵��  : DRC_IN_H �Ĵ����ṹ���塣��ַƫ����:0x0C0C����ֵ:0x000000FF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  drc_in_h : 8;  /* bit[0-7] : target strength of dynamic range compression */
        unsigned int  reserved : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_DRC_IN_H_UNION;
#endif
#define SOC_DSS_SBL_DRC_IN_H_drc_in_h_START  (0)
#define SOC_DSS_SBL_DRC_IN_H_drc_in_h_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_BACKLIGHT_L_UNION
 �ṹ˵��  : BACKLIGHT_L �Ĵ����ṹ���塣��ַƫ����:0x0C10����ֵ:0x000000FF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  backlight_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved    : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_BACKLIGHT_L_UNION;
#endif
#define SOC_DSS_SBL_BACKLIGHT_L_backlight_l_START  (0)
#define SOC_DSS_SBL_BACKLIGHT_L_backlight_l_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_BACKLIGHT_H_UNION
 �ṹ˵��  : BACKLIGHT_H �Ĵ����ṹ���塣��ַƫ����:0x0C14����ֵ:0x000000FF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  backlight_h : 8;  /* bit[0-7] : screen brightness on a scale of 0 to backlight_scale */
        unsigned int  reserved    : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_BACKLIGHT_H_UNION;
#endif
#define SOC_DSS_SBL_BACKLIGHT_H_backlight_h_START  (0)
#define SOC_DSS_SBL_BACKLIGHT_H_backlight_h_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_AMBIENT_LIGHT_L_UNION
 �ṹ˵��  : AMBIENT_LIGHT_L �Ĵ����ṹ���塣��ַƫ����:0x0C18����ֵ:0x000000FF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ambient_light_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_AMBIENT_LIGHT_L_UNION;
#endif
#define SOC_DSS_SBL_AMBIENT_LIGHT_L_ambient_light_l_START  (0)
#define SOC_DSS_SBL_AMBIENT_LIGHT_L_ambient_light_l_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_AMBIENT_LIGHT_H_UNION
 �ṹ˵��  : AMBIENT_LIGHT_H �Ĵ����ṹ���塣��ַƫ����:0x0C1C����ֵ:0x000000FF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ambient_light_h : 8;  /* bit[0-7] : ambient light level from photosensor */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_AMBIENT_LIGHT_H_UNION;
#endif
#define SOC_DSS_SBL_AMBIENT_LIGHT_H_ambient_light_h_START  (0)
#define SOC_DSS_SBL_AMBIENT_LIGHT_H_ambient_light_h_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_START_CALC_UNION
 �ṹ˵��  : START_CALC �Ĵ����ṹ���塣��ַƫ����:0x0C20����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  start_calc : 1;  /* bit[0]   : start calculator pulse */
        unsigned int  reserved   : 31; /* bit[1-31]:  */
    } reg;
} SOC_DSS_SBL_START_CALC_UNION;
#endif
#define SOC_DSS_SBL_START_CALC_start_calc_START  (0)
#define SOC_DSS_SBL_START_CALC_start_calc_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_STRENGTH_LIMIT_UNION
 �ṹ˵��  : STRENGTH_LIMIT �Ĵ����ṹ���塣��ַƫ����:0x0C24����ֵ:0x00000080�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  strength_limit : 8;  /* bit[0-7] : imposes a cap on maximum dynamic range compression strength */
        unsigned int  reserved       : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_STRENGTH_LIMIT_UNION;
#endif
#define SOC_DSS_SBL_STRENGTH_LIMIT_strength_limit_START  (0)
#define SOC_DSS_SBL_STRENGTH_LIMIT_strength_limit_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_CALIBRATION_A_L_UNION
 �ṹ˵��  : CALIBRATION_A_L �Ĵ����ṹ���塣��ַƫ����:0x0C28����ֵ:0x0000006E�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  calibration_a_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_CALIBRATION_A_L_UNION;
#endif
#define SOC_DSS_SBL_CALIBRATION_A_L_calibration_a_l_START  (0)
#define SOC_DSS_SBL_CALIBRATION_A_L_calibration_a_l_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_CALIBRATION_A_H_UNION
 �ṹ˵��  : CALIBRATION_A_H �Ĵ����ṹ���塣��ַƫ����:0x0C2C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  calibration_a_h : 8;  /* bit[0-7] : screen calibration parameter */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_CALIBRATION_A_H_UNION;
#endif
#define SOC_DSS_SBL_CALIBRATION_A_H_calibration_a_h_START  (0)
#define SOC_DSS_SBL_CALIBRATION_A_H_calibration_a_h_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_CALIBRATION_B_L_UNION
 �ṹ˵��  : CALIBRATION_B_L �Ĵ����ṹ���塣��ַƫ����:0x0C30����ֵ:0x0000005F�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  calibration_b_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_CALIBRATION_B_L_UNION;
#endif
#define SOC_DSS_SBL_CALIBRATION_B_L_calibration_b_l_START  (0)
#define SOC_DSS_SBL_CALIBRATION_B_L_calibration_b_l_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_CALIBRATION_B_H_UNION
 �ṹ˵��  : CALIBRATION_B_H �Ĵ����ṹ���塣��ַƫ����:0x0C34����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  calibration_b_h : 8;  /* bit[0-7] : screen calibration parameter */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_CALIBRATION_B_H_UNION;
#endif
#define SOC_DSS_SBL_CALIBRATION_B_H_calibration_b_h_START  (0)
#define SOC_DSS_SBL_CALIBRATION_B_H_calibration_b_h_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_CALIBRATION_C_L_UNION
 �ṹ˵��  : CALIBRATION_C_L �Ĵ����ṹ���塣��ַƫ����:0x0C38����ֵ:0x00000013�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  calibration_c_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_CALIBRATION_C_L_UNION;
#endif
#define SOC_DSS_SBL_CALIBRATION_C_L_calibration_c_l_START  (0)
#define SOC_DSS_SBL_CALIBRATION_C_L_calibration_c_l_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_CALIBRATION_C_H_UNION
 �ṹ˵��  : CALIBRATION_C_H �Ĵ����ṹ���塣��ַƫ����:0x0C3C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  calibration_c_h : 8;  /* bit[0-7] : screen calibration parameter */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_CALIBRATION_C_H_UNION;
#endif
#define SOC_DSS_SBL_CALIBRATION_C_H_calibration_c_h_START  (0)
#define SOC_DSS_SBL_CALIBRATION_C_H_calibration_c_h_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_CALIBRATION_D_L_UNION
 �ṹ˵��  : CALIBRATION_D_L �Ĵ����ṹ���塣��ַƫ����:0x0C40����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  calibration_d_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_CALIBRATION_D_L_UNION;
#endif
#define SOC_DSS_SBL_CALIBRATION_D_L_calibration_d_l_START  (0)
#define SOC_DSS_SBL_CALIBRATION_D_L_calibration_d_l_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_CALIBRATION_D_H_UNION
 �ṹ˵��  : CALIBRATION_D_H �Ĵ����ṹ���塣��ַƫ����:0x0C44����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  calibration_d_h : 8;  /* bit[0-7] : screen calibration parameter */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_CALIBRATION_D_H_UNION;
#endif
#define SOC_DSS_SBL_CALIBRATION_D_H_calibration_d_h_START  (0)
#define SOC_DSS_SBL_CALIBRATION_D_H_calibration_d_h_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_T_FILTER_CONTROL_UNION
 �ṹ˵��  : T_FILTER_CONTROL �Ĵ����ṹ���塣��ַƫ����:0x0C48����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  t_filter_control : 8;  /* bit[0-7] : Recursion depth of temporal filter */
        unsigned int  reserved         : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_T_FILTER_CONTROL_UNION;
#endif
#define SOC_DSS_SBL_T_FILTER_CONTROL_t_filter_control_START  (0)
#define SOC_DSS_SBL_T_FILTER_CONTROL_t_filter_control_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_BACKLIGHT_MIN_L_UNION
 �ṹ˵��  : BACKLIGHT_MIN_L �Ĵ����ṹ���塣��ַƫ����:0x0C4C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  backlight_min_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_BACKLIGHT_MIN_L_UNION;
#endif
#define SOC_DSS_SBL_BACKLIGHT_MIN_L_backlight_min_l_START  (0)
#define SOC_DSS_SBL_BACKLIGHT_MIN_L_backlight_min_l_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_BACKLIGHT_MIN_H_UNION
 �ṹ˵��  : BACKLIGHT_MIN_H �Ĵ����ṹ���塣��ַƫ����:0x0C50����ֵ:0x00000028�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  backlight_min_h : 8;  /* bit[0-7] : minimum output backlight value permitted */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_BACKLIGHT_MIN_H_UNION;
#endif
#define SOC_DSS_SBL_BACKLIGHT_MIN_H_backlight_min_h_START  (0)
#define SOC_DSS_SBL_BACKLIGHT_MIN_H_backlight_min_h_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_BACKLIGHT_MAX_L_UNION
 �ṹ˵��  : BACKLIGHT_MAX_L �Ĵ����ṹ���塣��ַƫ����:0x0C54����ֵ:0x000000FF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  backlight_max_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_BACKLIGHT_MAX_L_UNION;
#endif
#define SOC_DSS_SBL_BACKLIGHT_MAX_L_backlight_max_l_START  (0)
#define SOC_DSS_SBL_BACKLIGHT_MAX_L_backlight_max_l_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_BACKLIGHT_MAX_H_UNION
 �ṹ˵��  : BACKLIGHT_MAX_H �Ĵ����ṹ���塣��ַƫ����:0x0C58����ֵ:0x000000FF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  backlight_max_h : 8;  /* bit[0-7] : maximum output backlight value permitted */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_BACKLIGHT_MAX_H_UNION;
#endif
#define SOC_DSS_SBL_BACKLIGHT_MAX_H_backlight_max_h_START  (0)
#define SOC_DSS_SBL_BACKLIGHT_MAX_H_backlight_max_h_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_BACKLIGHT_SCALE_L_UNION
 �ṹ˵��  : BACKLIGHT_SCALE_L �Ĵ����ṹ���塣��ַƫ����:0x0C5C����ֵ:0x000000FF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  backlight_scale_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved          : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_BACKLIGHT_SCALE_L_UNION;
#endif
#define SOC_DSS_SBL_BACKLIGHT_SCALE_L_backlight_scale_l_START  (0)
#define SOC_DSS_SBL_BACKLIGHT_SCALE_L_backlight_scale_l_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_BACKLIGHT_SCALE_H_UNION
 �ṹ˵��  : BACKLIGHT_SCALE_H �Ĵ����ṹ���塣��ַƫ����:0x0C60����ֵ:0x000000FF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  backlight_scale_h : 8;  /* bit[0-7] : digital value corresponding to the maximum possible backlight input level */
        unsigned int  reserved          : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_BACKLIGHT_SCALE_H_UNION;
#endif
#define SOC_DSS_SBL_BACKLIGHT_SCALE_H_backlight_scale_h_START  (0)
#define SOC_DSS_SBL_BACKLIGHT_SCALE_H_backlight_scale_h_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_AMBIENT_LIGHT_MIN_L_UNION
 �ṹ˵��  : AMBIENT_LIGHT_MIN_L �Ĵ����ṹ���塣��ַƫ����:0x0C64����ֵ:0x0000000E�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ambient_light_min_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved            : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_AMBIENT_LIGHT_MIN_L_UNION;
#endif
#define SOC_DSS_SBL_AMBIENT_LIGHT_MIN_L_ambient_light_min_l_START  (0)
#define SOC_DSS_SBL_AMBIENT_LIGHT_MIN_L_ambient_light_min_l_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_AMBIENT_LIGHT_MIN_H_UNION
 �ṹ˵��  : AMBIENT_LIGHT_MIN_H �Ĵ����ṹ���塣��ַƫ����:0x0C68����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ambient_light_min_h : 8;  /* bit[0-7] : ambient light level below which backlight_out is set to backlight_min */
        unsigned int  reserved            : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_AMBIENT_LIGHT_MIN_H_UNION;
#endif
#define SOC_DSS_SBL_AMBIENT_LIGHT_MIN_H_ambient_light_min_h_START  (0)
#define SOC_DSS_SBL_AMBIENT_LIGHT_MIN_H_ambient_light_min_h_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_FILTER_A_L_UNION
 �ṹ˵��  : FILTER_A_L �Ĵ����ṹ���塣��ַƫ����:0x0C6C����ֵ:0x000000CA�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filter_a_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved   : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_FILTER_A_L_UNION;
#endif
#define SOC_DSS_SBL_FILTER_A_L_filter_a_l_START  (0)
#define SOC_DSS_SBL_FILTER_A_L_filter_a_l_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_FILTER_A_H_UNION
 �ṹ˵��  : FILTER_A_H �Ĵ����ṹ���塣��ַƫ����:0x0C70����ֵ:0x00000006�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filter_a_h : 8;  /* bit[0-7] : filter values for the input ambient_light */
        unsigned int  reserved   : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_FILTER_A_H_UNION;
#endif
#define SOC_DSS_SBL_FILTER_A_H_filter_a_h_START  (0)
#define SOC_DSS_SBL_FILTER_A_H_filter_a_h_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_FILTER_B_UNION
 �ṹ˵��  : FILTER_B �Ĵ����ṹ���塣��ַƫ����:0x0C74����ֵ:0x00000006�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filter_b : 8;  /* bit[0-7] : filter values for the input ambient_light */
        unsigned int  reserved : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_FILTER_B_UNION;
#endif
#define SOC_DSS_SBL_FILTER_B_filter_b_START  (0)
#define SOC_DSS_SBL_FILTER_B_filter_b_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_STRENGTH_OUT_UNION
 �ṹ˵��  : STRENGTH_OUT �Ĵ����ṹ���塣��ַƫ����:0x0C80����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  strength_out : 8;  /* bit[0-7] : The primary output of the calculator, passed to the internal iridix module strength register. This is included as an output from the core for debug purposes only */
        unsigned int  reserved     : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_STRENGTH_OUT_UNION;
#endif
#define SOC_DSS_SBL_STRENGTH_OUT_strength_out_START  (0)
#define SOC_DSS_SBL_STRENGTH_OUT_strength_out_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_DRC_OUT_L_UNION
 �ṹ˵��  : DRC_OUT_L �Ĵ����ṹ���塣��ַƫ����:0x0C84����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  drc_out_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved  : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_DRC_OUT_L_UNION;
#endif
#define SOC_DSS_SBL_DRC_OUT_L_drc_out_l_START  (0)
#define SOC_DSS_SBL_DRC_OUT_L_drc_out_l_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_DRC_OUT_H_UNION
 �ṹ˵��  : DRC_OUT_H �Ĵ����ṹ���塣��ַƫ����:0x0C88����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  drc_out_h : 8;  /* bit[0-7] : calculated dynamic range compression */
        unsigned int  reserved  : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_DRC_OUT_H_UNION;
#endif
#define SOC_DSS_SBL_DRC_OUT_H_drc_out_h_START  (0)
#define SOC_DSS_SBL_DRC_OUT_H_drc_out_h_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_BACKLIGHT_OUT_L_UNION
 �ṹ˵��  : BACKLIGHT_OUT_L �Ĵ����ṹ���塣��ַƫ����:0x0C8C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  backlight_out_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_BACKLIGHT_OUT_L_UNION;
#endif
#define SOC_DSS_SBL_BACKLIGHT_OUT_L_backlight_out_l_START  (0)
#define SOC_DSS_SBL_BACKLIGHT_OUT_L_backlight_out_l_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_BACKLIGHT_OUT_H_UNION
 �ṹ˵��  : BACKLIGHT_OUT_H �Ĵ����ṹ���塣��ַƫ����:0x0C90����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  backlight_out_h : 8;  /* bit[0-7] : calculated backlight setting */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_BACKLIGHT_OUT_H_UNION;
#endif
#define SOC_DSS_SBL_BACKLIGHT_OUT_H_backlight_out_h_START  (0)
#define SOC_DSS_SBL_BACKLIGHT_OUT_H_backlight_out_h_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_CALC_DONE_UNION
 �ṹ˵��  : CALC_DONE �Ĵ����ṹ���塣��ַƫ����:0x0C94����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  calc_done : 1;  /* bit[0]   : calculation done flag */
        unsigned int  reserved  : 31; /* bit[1-31]:  */
    } reg;
} SOC_DSS_SBL_CALC_DONE_UNION;
#endif
#define SOC_DSS_SBL_CALC_DONE_calc_done_START  (0)
#define SOC_DSS_SBL_CALC_DONE_calc_done_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_AL_CALIB_LUT_LUT_ADDR_UNION
 �ṹ˵��  : AL_CALIB_LUT_LUT_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0F00����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  al_calib_lut_lut_addr : 6;  /* bit[0-5] : LUT address register(valid range 0 to 32) */
        unsigned int  reserved              : 26; /* bit[6-31]:  */
    } reg;
} SOC_DSS_SBL_AL_CALIB_LUT_LUT_ADDR_UNION;
#endif
#define SOC_DSS_SBL_AL_CALIB_LUT_LUT_ADDR_al_calib_lut_lut_addr_START  (0)
#define SOC_DSS_SBL_AL_CALIB_LUT_LUT_ADDR_al_calib_lut_lut_addr_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_AL_CALIB_LUT_LUT_WRITE_DATA_L_UNION
 �ṹ˵��  : AL_CALIB_LUT_LUT_WRITE_DATA_L �Ĵ����ṹ���塣��ַƫ����:0x0F10����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  al_calib_lut_lut_write_data_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved                      : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_AL_CALIB_LUT_LUT_WRITE_DATA_L_UNION;
#endif
#define SOC_DSS_SBL_AL_CALIB_LUT_LUT_WRITE_DATA_L_al_calib_lut_lut_write_data_l_START  (0)
#define SOC_DSS_SBL_AL_CALIB_LUT_LUT_WRITE_DATA_L_al_calib_lut_lut_write_data_l_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SBL_AL_CALIB_LUT_LUT_WRITE_DATA_H_UNION
 �ṹ˵��  : AL_CALIB_LUT_LUT_WRITE_DATA_H �Ĵ����ṹ���塣��ַƫ����:0x0F14����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  al_calib_lut_lut_write_data_h : 8;  /* bit[0-7] : LUT write data register */
        unsigned int  reserved                      : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_AL_CALIB_LUT_LUT_WRITE_DATA_H_UNION;
#endif
#define SOC_DSS_SBL_AL_CALIB_LUT_LUT_WRITE_DATA_H_al_calib_lut_lut_write_data_h_START  (0)
#define SOC_DSS_SBL_AL_CALIB_LUT_LUT_WRITE_DATA_H_al_calib_lut_lut_write_data_h_END    (7)






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

#endif /* end of soc_dss_sbl_interface.h */
