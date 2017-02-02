/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_isp_blc_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:21:27
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_ISP_BLC.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_ISP_BLC_INTERFACE_H__
#define __SOC_ISP_BLC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) BLC
 ****************************************************************************/
/* �Ĵ���˵����global control register
   λ����UNION�ṹ:  SOC_ISP_BLC_BLS_CTRL_UNION */
#define SOC_ISP_BLC_BLS_CTRL_ADDR(base)               ((base) + (0x0000))

/* �Ĵ���˵����samples register
   λ����UNION�ṹ:  SOC_ISP_BLC_BLS_SAMPLES_UNION */
#define SOC_ISP_BLC_BLS_SAMPLES_ADDR(base)            ((base) + (0x0004))

/* �Ĵ���˵����samples register
   λ����UNION�ṹ:  SOC_ISP_BLC_BLS_H1_START_UNION */
#define SOC_ISP_BLC_BLS_H1_START_ADDR(base)           ((base) + (0x0008))

/* �Ĵ���˵����samples register
   λ����UNION�ṹ:  SOC_ISP_BLC_BLS_H1_STOP_UNION */
#define SOC_ISP_BLC_BLS_H1_STOP_ADDR(base)            ((base) + (0x000C))

/* �Ĵ���˵����samples register
   λ����UNION�ṹ:  SOC_ISP_BLC_BLS_V1_START_UNION */
#define SOC_ISP_BLC_BLS_V1_START_ADDR(base)           ((base) + (0x0010))

/* �Ĵ���˵����samples register
   λ����UNION�ṹ:  SOC_ISP_BLC_BLS_V1_STOP_UNION */
#define SOC_ISP_BLC_BLS_V1_STOP_ADDR(base)            ((base) + (0x0014))

/* �Ĵ���˵����samples register
   λ����UNION�ṹ:  SOC_ISP_BLC_BLS_H2_START_UNION */
#define SOC_ISP_BLC_BLS_H2_START_ADDR(base)           ((base) + (0x0018))

/* �Ĵ���˵����samples register
   λ����UNION�ṹ:  SOC_ISP_BLC_BLS_H2_STOP_UNION */
#define SOC_ISP_BLC_BLS_H2_STOP_ADDR(base)            ((base) + (0x001C))

/* �Ĵ���˵����samples register
   λ����UNION�ṹ:  SOC_ISP_BLC_BLS_V2_START_UNION */
#define SOC_ISP_BLC_BLS_V2_START_ADDR(base)           ((base) + (0x0020))

/* �Ĵ���˵����samples register
   λ����UNION�ṹ:  SOC_ISP_BLC_BLS_V2_STOP_UNION */
#define SOC_ISP_BLC_BLS_V2_STOP_ADDR(base)            ((base) + (0x0024))

/* �Ĵ���˵����fixed black level A
   λ����UNION�ṹ:  SOC_ISP_BLC_BLS_A_FIXED_UNION */
#define SOC_ISP_BLC_BLS_A_FIXED_ADDR(base)            ((base) + (0x0028))

/* �Ĵ���˵����fixed black level B
   λ����UNION�ṹ:  SOC_ISP_BLC_BLS_B_FIXED_UNION */
#define SOC_ISP_BLC_BLS_B_FIXED_ADDR(base)            ((base) + (0x002C))

/* �Ĵ���˵����fixed black level C
   λ����UNION�ṹ:  SOC_ISP_BLC_BLS_C_FIXED_UNION */
#define SOC_ISP_BLC_BLS_C_FIXED_ADDR(base)            ((base) + (0x0030))

/* �Ĵ���˵����fixed black level D
   λ����UNION�ṹ:  SOC_ISP_BLC_BLS_D_FIXED_UNION */
#define SOC_ISP_BLC_BLS_D_FIXED_ADDR(base)            ((base) + (0x0034))

/* �Ĵ���˵����measured black level A
   λ����UNION�ṹ:  SOC_ISP_BLC_BLS_A_MEASURED_UNION */
#define SOC_ISP_BLC_BLS_A_MEASURED_ADDR(base)         ((base) + (0x0038))

/* �Ĵ���˵����measured black level B
   λ����UNION�ṹ:  SOC_ISP_BLC_BLS_B_MEASURED_UNION */
#define SOC_ISP_BLC_BLS_B_MEASURED_ADDR(base)         ((base) + (0x003C))

/* �Ĵ���˵����measured black level C
   λ����UNION�ṹ:  SOC_ISP_BLC_BLS_C_MEASURED_UNION */
#define SOC_ISP_BLC_BLS_C_MEASURED_ADDR(base)         ((base) + (0x0040))

/* �Ĵ���˵����measured black level D
   λ����UNION�ṹ:  SOC_ISP_BLC_BLS_D_MEASURED_UNION */
#define SOC_ISP_BLC_BLS_D_MEASURED_ADDR(base)         ((base) + (0x0044))





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
                     (1/1) BLC
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_ISP_BLC_BLS_CTRL_UNION
 �ṹ˵��  : BLS_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: global control register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_enable : 1;  /* bit[0]   : 1: black level subtraction is enabled 
                                                     0: bypass the black level processing */
        unsigned int  bls_mode   : 1;  /* bit[1]   : 1: subtract measured values 
                                                     0: subtract fixed values */
        unsigned int  bls_win_en : 2;  /* bit[2-3] : 0: no measuring is performed 
                                                     1: only window 1 is measured 
                                                     2: only window 2 is measured 
                                                     3: both windows are measured */
        unsigned int  reserved   : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_CTRL_UNION;
#endif
#define SOC_ISP_BLC_BLS_CTRL_bls_enable_START  (0)
#define SOC_ISP_BLC_BLS_CTRL_bls_enable_END    (0)
#define SOC_ISP_BLC_BLS_CTRL_bls_mode_START    (1)
#define SOC_ISP_BLC_BLS_CTRL_bls_mode_END      (1)
#define SOC_ISP_BLC_BLS_CTRL_bls_win_en_START  (2)
#define SOC_ISP_BLC_BLS_CTRL_bls_win_en_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_ISP_BLC_BLS_SAMPLES_UNION
 �ṹ˵��  : BLS_SAMPLES �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: samples register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_samples : 5;
        unsigned int  reserved    : 27; /* bit[5-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_SAMPLES_UNION;
#endif
#define SOC_ISP_BLC_BLS_SAMPLES_bls_samples_START  (0)
#define SOC_ISP_BLC_BLS_SAMPLES_bls_samples_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_ISP_BLC_BLS_H1_START_UNION
 �ṹ˵��  : BLS_H1_START �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: samples register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_h1_start : 14; /* bit[0-13] : Black pixel window 1 horizontal start position */
        unsigned int  reserved     : 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_H1_START_UNION;
#endif
#define SOC_ISP_BLC_BLS_H1_START_bls_h1_start_START  (0)
#define SOC_ISP_BLC_BLS_H1_START_bls_h1_start_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_ISP_BLC_BLS_H1_STOP_UNION
 �ṹ˵��  : BLS_H1_STOP �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: samples register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_h1_stop : 14; /* bit[0-13] : Black pixel window 1 horizontal stop position */
        unsigned int  reserved    : 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_H1_STOP_UNION;
#endif
#define SOC_ISP_BLC_BLS_H1_STOP_bls_h1_stop_START  (0)
#define SOC_ISP_BLC_BLS_H1_STOP_bls_h1_stop_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_ISP_BLC_BLS_V1_START_UNION
 �ṹ˵��  : BLS_V1_START �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: samples register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_v1_start : 14; /* bit[0-13] : Black pixel window 1 vertical start position */
        unsigned int  reserved     : 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_V1_START_UNION;
#endif
#define SOC_ISP_BLC_BLS_V1_START_bls_v1_start_START  (0)
#define SOC_ISP_BLC_BLS_V1_START_bls_v1_start_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_ISP_BLC_BLS_V1_STOP_UNION
 �ṹ˵��  : BLS_V1_STOP �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: samples register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_v1_stop : 14; /* bit[0-13] : Black pixel window 1 verticall stop position */
        unsigned int  reserved    : 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_V1_STOP_UNION;
#endif
#define SOC_ISP_BLC_BLS_V1_STOP_bls_v1_stop_START  (0)
#define SOC_ISP_BLC_BLS_V1_STOP_bls_v1_stop_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_ISP_BLC_BLS_H2_START_UNION
 �ṹ˵��  : BLS_H2_START �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: samples register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_h2_start : 14; /* bit[0-13] : Black pixel window 2 horizontal start position */
        unsigned int  reserved     : 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_H2_START_UNION;
#endif
#define SOC_ISP_BLC_BLS_H2_START_bls_h2_start_START  (0)
#define SOC_ISP_BLC_BLS_H2_START_bls_h2_start_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_ISP_BLC_BLS_H2_STOP_UNION
 �ṹ˵��  : BLS_H2_STOP �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000000�����:32
 �Ĵ���˵��: samples register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_h2_stop : 14; /* bit[0-13] : Black pixel window 2 horizontal stop position */
        unsigned int  reserved    : 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_H2_STOP_UNION;
#endif
#define SOC_ISP_BLC_BLS_H2_STOP_bls_h2_stop_START  (0)
#define SOC_ISP_BLC_BLS_H2_STOP_bls_h2_stop_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_ISP_BLC_BLS_V2_START_UNION
 �ṹ˵��  : BLS_V2_START �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: samples register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_v2_start : 14; /* bit[0-13] : Black pixel window 2 vertical start position */
        unsigned int  reserved     : 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_V2_START_UNION;
#endif
#define SOC_ISP_BLC_BLS_V2_START_bls_v2_start_START  (0)
#define SOC_ISP_BLC_BLS_V2_START_bls_v2_start_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_ISP_BLC_BLS_V2_STOP_UNION
 �ṹ˵��  : BLS_V2_STOP �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x00000000�����:32
 �Ĵ���˵��: samples register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_v2_stop : 14; /* bit[0-13] : Black pixel window 2 verticall stop position */
        unsigned int  reserved    : 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_V2_STOP_UNION;
#endif
#define SOC_ISP_BLC_BLS_V2_STOP_bls_v2_stop_START  (0)
#define SOC_ISP_BLC_BLS_V2_STOP_bls_v2_stop_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_ISP_BLC_BLS_A_FIXED_UNION
 �ṹ˵��  : BLS_A_FIXED �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x00000000�����:32
 �Ĵ���˵��: fixed black level A
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_a_fixed : 15; /* bit[0-14] : Fixed black level for A pixels �C signed two's complement, value range from -4096 to +4095, a positive value will be subtracted from the pixel values */
        unsigned int  reserved    : 17; /* bit[15-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_A_FIXED_UNION;
#endif
#define SOC_ISP_BLC_BLS_A_FIXED_bls_a_fixed_START  (0)
#define SOC_ISP_BLC_BLS_A_FIXED_bls_a_fixed_END    (14)


/*****************************************************************************
 �ṹ��    : SOC_ISP_BLC_BLS_B_FIXED_UNION
 �ṹ˵��  : BLS_B_FIXED �Ĵ����ṹ���塣��ַƫ����:0x002C����ֵ:0x00000000�����:32
 �Ĵ���˵��: fixed black level B
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_b_fixed : 15; /* bit[0-14] : Fixed black level for B pixels �C signed two's complement, value range from -4096 to +4095, a positive value will be subtracted from the pixel values */
        unsigned int  reserved    : 17; /* bit[15-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_B_FIXED_UNION;
#endif
#define SOC_ISP_BLC_BLS_B_FIXED_bls_b_fixed_START  (0)
#define SOC_ISP_BLC_BLS_B_FIXED_bls_b_fixed_END    (14)


/*****************************************************************************
 �ṹ��    : SOC_ISP_BLC_BLS_C_FIXED_UNION
 �ṹ˵��  : BLS_C_FIXED �Ĵ����ṹ���塣��ַƫ����:0x0030����ֵ:0x00000000�����:32
 �Ĵ���˵��: fixed black level C
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_c_fixed : 15; /* bit[0-14] : Fixed black level for C pixels �C signed two's complement, value range from -4096 to +4095, a positive value will be subtracted from the pixel values */
        unsigned int  reserved    : 17; /* bit[15-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_C_FIXED_UNION;
#endif
#define SOC_ISP_BLC_BLS_C_FIXED_bls_c_fixed_START  (0)
#define SOC_ISP_BLC_BLS_C_FIXED_bls_c_fixed_END    (14)


/*****************************************************************************
 �ṹ��    : SOC_ISP_BLC_BLS_D_FIXED_UNION
 �ṹ˵��  : BLS_D_FIXED �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x00000000�����:32
 �Ĵ���˵��: fixed black level D
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_d_fixed : 15; /* bit[0-14] : Fixed black level for D pixels �C signed two's complement, value range from -4096 to +4095, a positive value will be subtracted from the pixel values */
        unsigned int  reserved    : 17; /* bit[15-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_D_FIXED_UNION;
#endif
#define SOC_ISP_BLC_BLS_D_FIXED_bls_d_fixed_START  (0)
#define SOC_ISP_BLC_BLS_D_FIXED_bls_d_fixed_END    (14)


/*****************************************************************************
 �ṹ��    : SOC_ISP_BLC_BLS_A_MEASURED_UNION
 �ṹ˵��  : BLS_A_MEASURED �Ĵ����ṹ���塣��ַƫ����:0x0038����ֵ:0x00000000�����:32
 �Ĵ���˵��: measured black level A
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_a_measured : 14; /* bit[0-13] : Measured black level for A pixels */
        unsigned int  reserved       : 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_A_MEASURED_UNION;
#endif
#define SOC_ISP_BLC_BLS_A_MEASURED_bls_a_measured_START  (0)
#define SOC_ISP_BLC_BLS_A_MEASURED_bls_a_measured_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_ISP_BLC_BLS_B_MEASURED_UNION
 �ṹ˵��  : BLS_B_MEASURED �Ĵ����ṹ���塣��ַƫ����:0x003C����ֵ:0x00000000�����:32
 �Ĵ���˵��: measured black level B
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_b_measured : 14; /* bit[0-13] : Measured black level for B pixels  */
        unsigned int  reserved       : 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_B_MEASURED_UNION;
#endif
#define SOC_ISP_BLC_BLS_B_MEASURED_bls_b_measured_START  (0)
#define SOC_ISP_BLC_BLS_B_MEASURED_bls_b_measured_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_ISP_BLC_BLS_C_MEASURED_UNION
 �ṹ˵��  : BLS_C_MEASURED �Ĵ����ṹ���塣��ַƫ����:0x0040����ֵ:0x00000000�����:32
 �Ĵ���˵��: measured black level C
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_c_measured : 14; /* bit[0-13] : Measured black level for C pixels  */
        unsigned int  reserved       : 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_C_MEASURED_UNION;
#endif
#define SOC_ISP_BLC_BLS_C_MEASURED_bls_c_measured_START  (0)
#define SOC_ISP_BLC_BLS_C_MEASURED_bls_c_measured_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_ISP_BLC_BLS_D_MEASURED_UNION
 �ṹ˵��  : BLS_D_MEASURED �Ĵ����ṹ���塣��ַƫ����:0x0044����ֵ:0x00000000�����:32
 �Ĵ���˵��: measured black level D
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_d_measured : 14; /* bit[0-13] : Measured black level for D pixels  */
        unsigned int  reserved       : 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_D_MEASURED_UNION;
#endif
#define SOC_ISP_BLC_BLS_D_MEASURED_bls_d_measured_START  (0)
#define SOC_ISP_BLC_BLS_D_MEASURED_bls_d_measured_END    (13)






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

#endif /* end of soc_isp_blc_interface.h */
