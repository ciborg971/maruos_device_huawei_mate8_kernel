/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_isp_ce_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:21:29
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_ISP_CE.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_ISP_CE_INTERFACE_H__
#define __SOC_ISP_CE_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) CE
 ****************************************************************************/
/* �Ĵ���˵����General Configuration register
   λ����UNION�ṹ:  SOC_ISP_CE_CFG_UNION */
#define SOC_ISP_CE_CFG_ADDR(base)                     ((base) + (0x0))

/* �Ĵ���˵����Limits of the face position (u13.0)
   λ����UNION�ṹ:  SOC_ISP_CE_FACE_POSITION_LU_UNION */
#define SOC_ISP_CE_FACE_POSITION_LU_ADDR(base)        ((base) + (0x4))

/* �Ĵ���˵����Limits of the face position (u13.0)
   λ����UNION�ṹ:  SOC_ISP_CE_FACE_POSITION_RD_UNION */
#define SOC_ISP_CE_FACE_POSITION_RD_ADDR(base)        ((base) + (0x8))

/* �Ĵ���˵����UV Gray filter configuration (9 Config)
   λ����UNION�ṹ:  SOC_ISP_CE_UV_GRAY_FILTER_UNION */
#define SOC_ISP_CE_UV_GRAY_FILTER_ADDR(base, Range9)  ((base) + (0x40+0x4*(Range9)))

/* �Ĵ���˵����Selects the active GAIN_ALONG_HUE to use on next start of frame
   λ����UNION�ṹ:  SOC_ISP_CE_GAIN_ALONG_HUE_CFG_UNION */
#define SOC_ISP_CE_GAIN_ALONG_HUE_CFG_ADDR(base)      ((base) + (0xFC))

/* �Ĵ���˵����Along Gain (256 words of s8.0) - 256 locations (Memory)- Bank0
   λ����UNION�ṹ:  SOC_ISP_CE_GAIN_ALONG_HUE0_UNION */
#define SOC_ISP_CE_GAIN_ALONG_HUE0_ADDR(base, Range256)  ((base) + (0x100+0x4*(Range256)))

/* �Ĵ���˵����Along Gain (256 words of s8.0) - 256 locations (Memory)- Bank1
   λ����UNION�ṹ:  SOC_ISP_CE_GAIN_ALONG_HUE1_UNION */
#define SOC_ISP_CE_GAIN_ALONG_HUE1_ADDR(base, Range256)  ((base) + (0x500+0x4*(Range256)))

/* �Ĵ���˵����256 words of u8.0
   λ����UNION�ṹ:  SOC_ISP_CE_GRID_FLAG_UNION */
#define SOC_ISP_CE_GRID_FLAG_ADDR(base, Range256)     ((base) + (0x900+0x4*(Range256)))

/* �Ĵ���˵����128*5 of u8.0 (256 locations - 0/1/2/3/4 on 2 address locations)
   λ����UNION�ṹ:  SOC_ISP_CE_GRID_INFO_0_UNION */
#define SOC_ISP_CE_GRID_INFO_0_ADDR(base, Range128)   ((base) + (0xD00+0x8*(Range128)))

/* �Ĵ���˵����128*5 of u8.0 (256 locations - 0/1/2/3/4 on 2 address locations)
   λ����UNION�ṹ:  SOC_ISP_CE_GRID_INFO_1_UNION */
#define SOC_ISP_CE_GRID_INFO_1_ADDR(base, Range128)   ((base) + (0xD04+0x8*(Range128)))

/* �Ĵ���˵����Statistic Max Saturation (256 words of u8.0)
   λ����UNION�ṹ:  SOC_ISP_CE_STAT_SATURATION_UNION */
#define SOC_ISP_CE_STAT_SATURATION_ADDR(base, Range256)  ((base) + (0x1100+0x4*(Range256)))

/* �Ĵ���˵����Statistic HistH (64 words of u12.0)
   λ����UNION�ṹ:  SOC_ISP_CE_STAT_HISTH_UNION */
#define SOC_ISP_CE_STAT_HISTH_ADDR(base, Range64)     ((base) + (0x1500+0x4*(Range64)))





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
                     (1/1) CE
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_ISP_CE_CFG_UNION
 �ṹ˵��  : CFG �Ĵ����ṹ���塣��ַƫ����:0x0����ֵ:0x00000000�����:32
 �Ĵ���˵��: General Configuration register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0         : 16; /* bit[0-15] :  */
        unsigned int  hue_stat_ds_factor : 4;  /* bit[16-19]: u4.0 */
        unsigned int  mce_strength       : 6;  /* bit[20-25]: u6.0 */
        unsigned int  reserved_1         : 1;  /* bit[26]   :  */
        unsigned int  get_stat           : 1;  /* bit[27]   : u1.0 - enable /disable the statistic computation. When Disabled, the statistic of the previous frame remains valid. When Enabled, all previous frame statistics are resetted and a new compute starts. */
        unsigned int  enable_sce         : 1;  /* bit[28]   : u1.0 :  */
        unsigned int  enable_mce         : 1;  /* bit[29]   : u1.0 :  */
        unsigned int  is_face_valid      : 1;  /* bit[30]   : u1.0 : enable bit to compute statistic on the face region */
        unsigned int  modify_frame       : 1;  /* bit[31]   : u1.0 : enable bit to modify the frame */
    } reg;
} SOC_ISP_CE_CFG_UNION;
#endif
#define SOC_ISP_CE_CFG_hue_stat_ds_factor_START  (16)
#define SOC_ISP_CE_CFG_hue_stat_ds_factor_END    (19)
#define SOC_ISP_CE_CFG_mce_strength_START        (20)
#define SOC_ISP_CE_CFG_mce_strength_END          (25)
#define SOC_ISP_CE_CFG_get_stat_START            (27)
#define SOC_ISP_CE_CFG_get_stat_END              (27)
#define SOC_ISP_CE_CFG_enable_sce_START          (28)
#define SOC_ISP_CE_CFG_enable_sce_END            (28)
#define SOC_ISP_CE_CFG_enable_mce_START          (29)
#define SOC_ISP_CE_CFG_enable_mce_END            (29)
#define SOC_ISP_CE_CFG_is_face_valid_START       (30)
#define SOC_ISP_CE_CFG_is_face_valid_END         (30)
#define SOC_ISP_CE_CFG_modify_frame_START        (31)
#define SOC_ISP_CE_CFG_modify_frame_END          (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_CE_FACE_POSITION_LU_UNION
 �ṹ˵��  : FACE_POSITION_LU �Ĵ����ṹ���塣��ַƫ����:0x4����ֵ:0x00000000�����:32
 �Ĵ���˵��: Limits of the face position (u13.0)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lu_x     : 13; /* bit[0-12] : u13.0 : this represents half coordinate of face position */
        unsigned int  reserved_0: 3;  /* bit[13-15]:  */
        unsigned int  lu_y     : 13; /* bit[16-28]: u13.0 */
        unsigned int  reserved_1: 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CE_FACE_POSITION_LU_UNION;
#endif
#define SOC_ISP_CE_FACE_POSITION_LU_lu_x_START      (0)
#define SOC_ISP_CE_FACE_POSITION_LU_lu_x_END        (12)
#define SOC_ISP_CE_FACE_POSITION_LU_lu_y_START      (16)
#define SOC_ISP_CE_FACE_POSITION_LU_lu_y_END        (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_CE_FACE_POSITION_RD_UNION
 �ṹ˵��  : FACE_POSITION_RD �Ĵ����ṹ���塣��ַƫ����:0x8����ֵ:0x00000000�����:32
 �Ĵ���˵��: Limits of the face position (u13.0)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rd_x     : 13; /* bit[0-12] : u13.0 : this represents half coordinate of face position */
        unsigned int  reserved_0: 3;  /* bit[13-15]:  */
        unsigned int  rd_y     : 13; /* bit[16-28]: u13.0 */
        unsigned int  reserved_1: 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CE_FACE_POSITION_RD_UNION;
#endif
#define SOC_ISP_CE_FACE_POSITION_RD_rd_x_START      (0)
#define SOC_ISP_CE_FACE_POSITION_RD_rd_x_END        (12)
#define SOC_ISP_CE_FACE_POSITION_RD_rd_y_START      (16)
#define SOC_ISP_CE_FACE_POSITION_RD_rd_y_END        (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_CE_UV_GRAY_FILTER_UNION
 �ṹ˵��  : UV_GRAY_FILTER �Ĵ����ṹ���塣��ַƫ����:0x40+0x4*(Range9)����ֵ:0x00000000�����:32
 �Ĵ���˵��: UV Gray filter configuration (9 Config)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  strength        : 5;  /* bit[0-4]  : u5.0 */
        unsigned int  reserved_0      : 3;  /* bit[5-7]  :  */
        unsigned int  threshold       : 8;  /* bit[8-15] : u8.0 */
        unsigned int  threshold_recip : 15; /* bit[16-30]: u0.15 */
        unsigned int  reserved_1      : 1;  /* bit[31]   :  */
    } reg;
} SOC_ISP_CE_UV_GRAY_FILTER_UNION;
#endif
#define SOC_ISP_CE_UV_GRAY_FILTER_strength_START         (0)
#define SOC_ISP_CE_UV_GRAY_FILTER_strength_END           (4)
#define SOC_ISP_CE_UV_GRAY_FILTER_threshold_START        (8)
#define SOC_ISP_CE_UV_GRAY_FILTER_threshold_END          (15)
#define SOC_ISP_CE_UV_GRAY_FILTER_threshold_recip_START  (16)
#define SOC_ISP_CE_UV_GRAY_FILTER_threshold_recip_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_ISP_CE_GAIN_ALONG_HUE_CFG_UNION
 �ṹ˵��  : GAIN_ALONG_HUE_CFG �Ĵ����ṹ���塣��ַƫ����:0xFC����ֵ:0x00000000�����:32
 �Ĵ���˵��: Selects the active GAIN_ALONG_HUE to use on next start of frame
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  active   : 1;  /* bit[0]   : GAIN_ALONG_HUE active bit:
                                                   0:gain_along_hue0 is used by the HW
                                                   1:gain_along_hue1 is used by the HW */
        unsigned int  reserved : 31; /* bit[1-31]:  */
    } reg;
} SOC_ISP_CE_GAIN_ALONG_HUE_CFG_UNION;
#endif
#define SOC_ISP_CE_GAIN_ALONG_HUE_CFG_active_START    (0)
#define SOC_ISP_CE_GAIN_ALONG_HUE_CFG_active_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_ISP_CE_GAIN_ALONG_HUE0_UNION
 �ṹ˵��  : GAIN_ALONG_HUE0 �Ĵ����ṹ���塣��ַƫ����:0x100+0x4*(Range256)����ֵ:0x00000000�����:32
 �Ĵ���˵��: Along Gain (256 words of s8.0) - 256 locations (Memory)- Bank0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gain_along_hue0 : 8;  /* bit[0-7] : s8.0 */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_ISP_CE_GAIN_ALONG_HUE0_UNION;
#endif
#define SOC_ISP_CE_GAIN_ALONG_HUE0_gain_along_hue0_START  (0)
#define SOC_ISP_CE_GAIN_ALONG_HUE0_gain_along_hue0_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_ISP_CE_GAIN_ALONG_HUE1_UNION
 �ṹ˵��  : GAIN_ALONG_HUE1 �Ĵ����ṹ���塣��ַƫ����:0x500+0x4*(Range256)����ֵ:0x00000000�����:32
 �Ĵ���˵��: Along Gain (256 words of s8.0) - 256 locations (Memory)- Bank1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gain_along_hue1 : 8;  /* bit[0-7] : s8.0 */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_ISP_CE_GAIN_ALONG_HUE1_UNION;
#endif
#define SOC_ISP_CE_GAIN_ALONG_HUE1_gain_along_hue1_START  (0)
#define SOC_ISP_CE_GAIN_ALONG_HUE1_gain_along_hue1_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_ISP_CE_GRID_FLAG_UNION
 �ṹ˵��  : GRID_FLAG �Ĵ����ṹ���塣��ַƫ����:0x900+0x4*(Range256)����ֵ:0x00000000�����:32
 �Ĵ���˵��: 256 words of u8.0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  grid_flag : 8;  /* bit[0-7] : u8.0 */
        unsigned int  reserved  : 24; /* bit[8-31]:  */
    } reg;
} SOC_ISP_CE_GRID_FLAG_UNION;
#endif
#define SOC_ISP_CE_GRID_FLAG_grid_flag_START  (0)
#define SOC_ISP_CE_GRID_FLAG_grid_flag_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_ISP_CE_GRID_INFO_0_UNION
 �ṹ˵��  : GRID_INFO_0 �Ĵ����ṹ���塣��ַƫ����:0xD00+0x8*(Range128)����ֵ:0x00000000�����:32
 �Ĵ���˵��: 128*5 of u8.0 (256 locations - 0/1/2/3/4 on 2 address locations)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  grid_info_0 : 8;  /* bit[0-7]  :  */
        unsigned int  grid_info_1 : 8;  /* bit[8-15] :  */
        unsigned int  grid_info_2 : 8;  /* bit[16-23]:  */
        unsigned int  grid_info_3 : 8;  /* bit[24-31]:  */
    } reg;
} SOC_ISP_CE_GRID_INFO_0_UNION;
#endif
#define SOC_ISP_CE_GRID_INFO_0_grid_info_0_START  (0)
#define SOC_ISP_CE_GRID_INFO_0_grid_info_0_END    (7)
#define SOC_ISP_CE_GRID_INFO_0_grid_info_1_START  (8)
#define SOC_ISP_CE_GRID_INFO_0_grid_info_1_END    (15)
#define SOC_ISP_CE_GRID_INFO_0_grid_info_2_START  (16)
#define SOC_ISP_CE_GRID_INFO_0_grid_info_2_END    (23)
#define SOC_ISP_CE_GRID_INFO_0_grid_info_3_START  (24)
#define SOC_ISP_CE_GRID_INFO_0_grid_info_3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_CE_GRID_INFO_1_UNION
 �ṹ˵��  : GRID_INFO_1 �Ĵ����ṹ���塣��ַƫ����:0xD04+0x8*(Range128)����ֵ:0x00000000�����:32
 �Ĵ���˵��: 128*5 of u8.0 (256 locations - 0/1/2/3/4 on 2 address locations)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  grid_info_4 : 8;  /* bit[0-7] :  */
        unsigned int  reserved    : 24; /* bit[8-31]:  */
    } reg;
} SOC_ISP_CE_GRID_INFO_1_UNION;
#endif
#define SOC_ISP_CE_GRID_INFO_1_grid_info_4_START  (0)
#define SOC_ISP_CE_GRID_INFO_1_grid_info_4_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_ISP_CE_STAT_SATURATION_UNION
 �ṹ˵��  : STAT_SATURATION �Ĵ����ṹ���塣��ַƫ����:0x1100+0x4*(Range256)����ֵ:0x00000000�����:32
 �Ĵ���˵��: Statistic Max Saturation (256 words of u8.0)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  max_saturation : 8;  /* bit[0-7] : represents the pMaxSaturation information 256 words of u8.0 */
        unsigned int  reserved       : 24; /* bit[8-31]:  */
    } reg;
} SOC_ISP_CE_STAT_SATURATION_UNION;
#endif
#define SOC_ISP_CE_STAT_SATURATION_max_saturation_START  (0)
#define SOC_ISP_CE_STAT_SATURATION_max_saturation_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_ISP_CE_STAT_HISTH_UNION
 �ṹ˵��  : STAT_HISTH �Ĵ����ṹ���塣��ַƫ����:0x1500+0x4*(Range64)����ֵ:0x00000000�����:32
 �Ĵ���˵��: Statistic HistH (64 words of u12.0)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hist_h   : 12; /* bit[0-11] : represents the pHistH information 64 words of u12.0 */
        unsigned int  reserved : 20; /* bit[12-31]:  */
    } reg;
} SOC_ISP_CE_STAT_HISTH_UNION;
#endif
#define SOC_ISP_CE_STAT_HISTH_hist_h_START    (0)
#define SOC_ISP_CE_STAT_HISTH_hist_h_END      (11)






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

#endif /* end of soc_isp_ce_interface.h */
