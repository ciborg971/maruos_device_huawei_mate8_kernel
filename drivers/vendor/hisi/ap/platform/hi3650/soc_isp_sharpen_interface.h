/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_isp_sharpen_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:22:04
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_ISP_SHARPEN.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_ISP_SHARPEN_INTERFACE_H__
#define __SOC_ISP_SHARPEN_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) SHARPEN
 ****************************************************************************/
/* �Ĵ���˵����Mid band filter coefficients 0
   λ����UNION�ṹ:  SOC_ISP_SHARPEN_G33_0_UNION */
#define SOC_ISP_SHARPEN_G33_0_ADDR(base)              ((base) + (0x000))

/* �Ĵ���˵����Mid band filter coefficients 1
   λ����UNION�ṹ:  SOC_ISP_SHARPEN_G33_1_UNION */
#define SOC_ISP_SHARPEN_G33_1_ADDR(base)              ((base) + (0x004))

/* �Ĵ���˵����Mid band filter coefficients 2
   λ����UNION�ṹ:  SOC_ISP_SHARPEN_G33_2_UNION */
#define SOC_ISP_SHARPEN_G33_2_ADDR(base)              ((base) + (0x008))

/* �Ĵ���˵����Line Detection configuration
   λ����UNION�ṹ:  SOC_ISP_SHARPEN_LINEDET_UNION */
#define SOC_ISP_SHARPEN_LINEDET_ADDR(base)            ((base) + (0x00C))

/* �Ĵ���˵����sharp configuration (mid-band)
   λ����UNION�ṹ:  SOC_ISP_SHARPEN_SHARPCFG_UNION */
#define SOC_ISP_SHARPEN_SHARPCFG_ADDR(base)           ((base) + (0x010))

/* �Ĵ���˵����edge configuration (high-band)
   λ����UNION�ṹ:  SOC_ISP_SHARPEN_EDGECFG_UNION */
#define SOC_ISP_SHARPEN_EDGECFG_ADDR(base)            ((base) + (0x014))

/* �Ĵ���˵����undershoot/overshoot configuration
   λ����UNION�ṹ:  SOC_ISP_SHARPEN_SHOOTCFG_UNION */
#define SOC_ISP_SHARPEN_SHOOTCFG_ADDR(base)           ((base) + (0x018))

/* �Ĵ���˵����Filter select configuration
   λ����UNION�ṹ:  SOC_ISP_SHARPEN_SELCFG_UNION */
#define SOC_ISP_SHARPEN_SELCFG_ADDR(base)             ((base) + (0x01C))

/* �Ĵ���˵����horizontal cropping configuration
   λ����UNION�ṹ:  SOC_ISP_SHARPEN_HCROP_UNION */
#define SOC_ISP_SHARPEN_HCROP_ADDR(base)              ((base) + (0x020))

/* �Ĵ���˵����vertical croppring configuration
   λ����UNION�ṹ:  SOC_ISP_SHARPEN_VCROP_UNION */
#define SOC_ISP_SHARPEN_VCROP_ADDR(base)              ((base) + (0x024))





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
                     (1/1) SHARPEN
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_ISP_SHARPEN_G33_0_UNION
 �ṹ˵��  : G33_0 �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x00000000�����:32
 �Ĵ���˵��: Mid band filter coefficients 0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g0_0     : 8;  /* bit[0-7]  : Mid Band filter coefficient Qs8.0
                                                    G0_0 = G3[0][0] */
        unsigned int  g0_1     : 8;  /* bit[8-15] : Mid Band filter coefficient Qs8.0
                                                    G0_1 = G3[0][1] */
        unsigned int  g0_2     : 8;  /* bit[16-23]: Mid Band filter coefficient Qs8.0
                                                    G0_2 = G3[0][2] */
        unsigned int  reserved : 8;  /* bit[24-31]:  */
    } reg;
} SOC_ISP_SHARPEN_G33_0_UNION;
#endif
#define SOC_ISP_SHARPEN_G33_0_g0_0_START      (0)
#define SOC_ISP_SHARPEN_G33_0_g0_0_END        (7)
#define SOC_ISP_SHARPEN_G33_0_g0_1_START      (8)
#define SOC_ISP_SHARPEN_G33_0_g0_1_END        (15)
#define SOC_ISP_SHARPEN_G33_0_g0_2_START      (16)
#define SOC_ISP_SHARPEN_G33_0_g0_2_END        (23)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SHARPEN_G33_1_UNION
 �ṹ˵��  : G33_1 �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x00000000�����:32
 �Ĵ���˵��: Mid band filter coefficients 1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g1_0     : 8;  /* bit[0-7]  : Mid Band filter coefficient Qs8.0
                                                    G1_0 = G3[1][0] */
        unsigned int  g1_1     : 8;  /* bit[8-15] : Mid Band filter coefficient Qs8.0
                                                    G1_1 = G3[1][1] */
        unsigned int  g1_2     : 8;  /* bit[16-23]: Mid Band filter coefficient Qs8.0
                                                    G1_2 = G3[1][2] */
        unsigned int  reserved : 8;  /* bit[24-31]:  */
    } reg;
} SOC_ISP_SHARPEN_G33_1_UNION;
#endif
#define SOC_ISP_SHARPEN_G33_1_g1_0_START      (0)
#define SOC_ISP_SHARPEN_G33_1_g1_0_END        (7)
#define SOC_ISP_SHARPEN_G33_1_g1_1_START      (8)
#define SOC_ISP_SHARPEN_G33_1_g1_1_END        (15)
#define SOC_ISP_SHARPEN_G33_1_g1_2_START      (16)
#define SOC_ISP_SHARPEN_G33_1_g1_2_END        (23)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SHARPEN_G33_2_UNION
 �ṹ˵��  : G33_2 �Ĵ����ṹ���塣��ַƫ����:0x008����ֵ:0x00000000�����:32
 �Ĵ���˵��: Mid band filter coefficients 2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g2_0     : 8;  /* bit[0-7]  : Mid Band filter coefficient Qs8.0
                                                    G2_0 = G3[2][0] */
        unsigned int  g2_1     : 8;  /* bit[8-15] : Mid Band filter coefficient Qs8.0
                                                    G2_1 = G3[2][1] */
        unsigned int  g2_2     : 8;  /* bit[16-23]: Mid Band filter coefficient Qs8.0
                                                    G2_2 = G3[2][2] */
        unsigned int  reserved : 8;  /* bit[24-31]:  */
    } reg;
} SOC_ISP_SHARPEN_G33_2_UNION;
#endif
#define SOC_ISP_SHARPEN_G33_2_g2_0_START      (0)
#define SOC_ISP_SHARPEN_G33_2_g2_0_END        (7)
#define SOC_ISP_SHARPEN_G33_2_g2_1_START      (8)
#define SOC_ISP_SHARPEN_G33_2_g2_1_END        (15)
#define SOC_ISP_SHARPEN_G33_2_g2_2_START      (16)
#define SOC_ISP_SHARPEN_G33_2_g2_2_END        (23)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SHARPEN_LINEDET_UNION
 �ṹ˵��  : LINEDET �Ĵ����ṹ���塣��ַƫ����:0x00C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Line Detection configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  linethd1  : 5;  /* bit[0-4]  : Line Detection threshold Qu5.0 */
        unsigned int  reserved_0: 3;  /* bit[5-7]  :  */
        unsigned int  linethd2  : 5;  /* bit[8-12] : Line Detection threshold Qu5.0 */
        unsigned int  reserved_1: 3;  /* bit[13-15]:  */
        unsigned int  lineamt1  : 12; /* bit[16-27]: high-band sharpen strength when line is detected Qu12.0 */
        unsigned int  reserved_2: 3;  /* bit[28-30]:  */
        unsigned int  linedeten : 1;  /* bit[31-31]: Line Detection enable Qu1
                                                     0: line detection disabled
                                                     1: line detection enabled */
    } reg;
} SOC_ISP_SHARPEN_LINEDET_UNION;
#endif
#define SOC_ISP_SHARPEN_LINEDET_linethd1_START   (0)
#define SOC_ISP_SHARPEN_LINEDET_linethd1_END     (4)
#define SOC_ISP_SHARPEN_LINEDET_linethd2_START   (8)
#define SOC_ISP_SHARPEN_LINEDET_linethd2_END     (12)
#define SOC_ISP_SHARPEN_LINEDET_lineamt1_START   (16)
#define SOC_ISP_SHARPEN_LINEDET_lineamt1_END     (27)
#define SOC_ISP_SHARPEN_LINEDET_linedeten_START  (31)
#define SOC_ISP_SHARPEN_LINEDET_linedeten_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SHARPEN_SHARPCFG_UNION
 �ṹ˵��  : SHARPCFG �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x00000000�����:32
 �Ĵ���˵��: sharp configuration (mid-band)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sharpamt1    : 12; /* bit[0-11] : mid-band sharpen strength Qu12.0 */
        unsigned int  sharpthd1mul : 12; /* bit[12-23]: Convert 1/SharpThd1 to multiplication Qu12.0 */
        unsigned int  sharpthd1    : 8;  /* bit[24-31]: mid-band sharpen strength threshold Qu8.0 */
    } reg;
} SOC_ISP_SHARPEN_SHARPCFG_UNION;
#endif
#define SOC_ISP_SHARPEN_SHARPCFG_sharpamt1_START     (0)
#define SOC_ISP_SHARPEN_SHARPCFG_sharpamt1_END       (11)
#define SOC_ISP_SHARPEN_SHARPCFG_sharpthd1mul_START  (12)
#define SOC_ISP_SHARPEN_SHARPCFG_sharpthd1mul_END    (23)
#define SOC_ISP_SHARPEN_SHARPCFG_sharpthd1_START     (24)
#define SOC_ISP_SHARPEN_SHARPCFG_sharpthd1_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SHARPEN_EDGECFG_UNION
 �ṹ˵��  : EDGECFG �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x00000000�����:32
 �Ĵ���˵��: edge configuration (high-band)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  edgeamt1    : 12; /* bit[0-11] : high-band sharpen strength Qu12.0 */
        unsigned int  edgethd1mul : 12; /* bit[12-23]: Convert 1/EdgeThd1 to multiplication Qu12.0 */
        unsigned int  edgethd1    : 8;  /* bit[24-31]: high-band sharpen strength threhold Qu8.0 */
    } reg;
} SOC_ISP_SHARPEN_EDGECFG_UNION;
#endif
#define SOC_ISP_SHARPEN_EDGECFG_edgeamt1_START     (0)
#define SOC_ISP_SHARPEN_EDGECFG_edgeamt1_END       (11)
#define SOC_ISP_SHARPEN_EDGECFG_edgethd1mul_START  (12)
#define SOC_ISP_SHARPEN_EDGECFG_edgethd1mul_END    (23)
#define SOC_ISP_SHARPEN_EDGECFG_edgethd1_START     (24)
#define SOC_ISP_SHARPEN_EDGECFG_edgethd1_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SHARPEN_SHOOTCFG_UNION
 �ṹ˵��  : SHOOTCFG �Ĵ����ṹ���塣��ַƫ����:0x018����ֵ:0x00000000�����:32
 �Ĵ���˵��: undershoot/overshoot configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  undershootamt : 8;  /* bit[0-7]  : Undershoot amplitude Qu8.0 */
        unsigned int  overshootamt  : 8;  /* bit[8-15] : Overshoot amplitude Qu8.0 */
        unsigned int  reserved      : 16; /* bit[16-31]:  */
    } reg;
} SOC_ISP_SHARPEN_SHOOTCFG_UNION;
#endif
#define SOC_ISP_SHARPEN_SHOOTCFG_undershootamt_START  (0)
#define SOC_ISP_SHARPEN_SHOOTCFG_undershootamt_END    (7)
#define SOC_ISP_SHARPEN_SHOOTCFG_overshootamt_START   (8)
#define SOC_ISP_SHARPEN_SHOOTCFG_overshootamt_END     (15)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SHARPEN_SELCFG_UNION
 �ṹ˵��  : SELCFG �Ĵ����ṹ���塣��ַƫ����:0x01C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Filter select configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hbfsel   : 1;  /* bit[0-0] : High-band filter coefficients selection */
        unsigned int  edgecmp  : 1;  /* bit[1-1] : Used to select Sharp1 or YEdge1 to control the High-band sharpen strength. 
                                                   0: select YEdge1
                                                   1: select Sharp1 */
        unsigned int  reserved : 30; /* bit[2-31]:  */
    } reg;
} SOC_ISP_SHARPEN_SELCFG_UNION;
#endif
#define SOC_ISP_SHARPEN_SELCFG_hbfsel_START    (0)
#define SOC_ISP_SHARPEN_SELCFG_hbfsel_END      (0)
#define SOC_ISP_SHARPEN_SELCFG_edgecmp_START   (1)
#define SOC_ISP_SHARPEN_SELCFG_edgecmp_END     (1)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SHARPEN_HCROP_UNION
 �ṹ˵��  : HCROP �Ĵ����ṹ���塣��ַƫ����:0x020����ֵ:0x00001FFF�����:32
 �Ĵ���˵��: horizontal cropping configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ihright  : 13; /* bit[0-12] : Input picture horizontal size.There must be an even number of pixels in input so ihright must be an odd number.Qu13.0
                                                    ihsize= ihright+1.Ihsize is supported in the range 4 to 4224( 4 <= ihsize <= 4224 )
                                                    1:2 pixels in input stream
                                                    n:(n+1) pixels in input stream */
        unsigned int  reserved : 19; /* bit[13-31]:  */
    } reg;
} SOC_ISP_SHARPEN_HCROP_UNION;
#endif
#define SOC_ISP_SHARPEN_HCROP_ihright_START   (0)
#define SOC_ISP_SHARPEN_HCROP_ihright_END     (12)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SHARPEN_VCROP_UNION
 �ṹ˵��  : VCROP �Ĵ����ṹ���塣��ַƫ����:0x024����ֵ:0x00001FFF�����:32
 �Ĵ���˵��: vertical croppring configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ivbottom : 13; /* bit[0-12] : Input picture vertical size. Qu13.0
                                                    Ivsize= ivbottom+1. Ivsize is supported in the range 4 to 8192 (4 <= ivsize <= 8192)
                                                    0:1 line in input stream
                                                    1:2 lines in input stream
                                                    n:(n+1) lines in input stream */
        unsigned int  reserved : 19; /* bit[13-31]:  */
    } reg;
} SOC_ISP_SHARPEN_VCROP_UNION;
#endif
#define SOC_ISP_SHARPEN_VCROP_ivbottom_START  (0)
#define SOC_ISP_SHARPEN_VCROP_ivbottom_END    (12)






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

#endif /* end of soc_isp_sharpen_interface.h */
