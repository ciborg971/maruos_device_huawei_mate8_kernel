/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_isp_dgamma_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:21:32
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_ISP_DGAMMA.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_ISP_DGAMMA_INTERFACE_H__
#define __SOC_ISP_DGAMMA_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) DGAMMA
 ****************************************************************************/
/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ISP_DGAMMA_DGAMMA_CONFIG_UNION */
#define SOC_ISP_DGAMMA_DGAMMA_CONFIG_ADDR(base)       ((base) + (0x0000))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ISP_DGAMMA_DGAMMA_OUT_ACTIVE_UNION */
#define SOC_ISP_DGAMMA_DGAMMA_OUT_ACTIVE_ADDR(base)   ((base) + (0x0008))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ISP_DGAMMA_LUTSCL_FACTOR_UNION */
#define SOC_ISP_DGAMMA_LUTSCL_FACTOR_ADDR(base)       ((base) + (0x000c))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ISP_DGAMMA_DGAMMA_OUT_R_0_UNION */
#define SOC_ISP_DGAMMA_DGAMMA_OUT_R_0_ADDR(base, Range96)  ((base) + (0x0100+0x4*(Range96)))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ISP_DGAMMA_DGAMMA_OUT_G_0_UNION */
#define SOC_ISP_DGAMMA_DGAMMA_OUT_G_0_ADDR(base, Range96, Num96)  ((base) + (0x0100+0x4*(Num96)+0x4*(Range96)))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ISP_DGAMMA_DGAMMA_OUT_B_0_UNION */
#define SOC_ISP_DGAMMA_DGAMMA_OUT_B_0_ADDR(base, Range96, Num96)  ((base) + (0x0100+0x4*2*(Num96)+0x4*(Range96)))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ISP_DGAMMA_DGAMMA_OUT_R_1_UNION */
#define SOC_ISP_DGAMMA_DGAMMA_OUT_R_1_ADDR(base, Range96)  ((base) + (0x0600+0x4*(Range96)))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ISP_DGAMMA_DGAMMA_OUT_G_1_UNION */
#define SOC_ISP_DGAMMA_DGAMMA_OUT_G_1_ADDR(base, Range96, Num96)  ((base) + (0x0600+0x4*(Num96)+0x4*(Range96)))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ISP_DGAMMA_DGAMMA_OUT_B_1_UNION */
#define SOC_ISP_DGAMMA_DGAMMA_OUT_B_1_ADDR(base, Range96, Num96)  ((base) + (0x0600+0x4*2*(Num96)+0x4*(Range96)))





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
                     (1/1) DGAMMA
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_ISP_DGAMMA_DGAMMA_CONFIG_UNION
 �ṹ˵��  : DGAMMA_CONFIG �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass   : 1;  /* bit[0-0] : Bypass:
                                                   0: the module is active
                                                   1: the module is bypassed */
        unsigned int  reserved : 31; /* bit[1-31]:  */
    } reg;
} SOC_ISP_DGAMMA_DGAMMA_CONFIG_UNION;
#endif
#define SOC_ISP_DGAMMA_DGAMMA_CONFIG_bypass_START    (0)
#define SOC_ISP_DGAMMA_DGAMMA_CONFIG_bypass_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_ISP_DGAMMA_DGAMMA_OUT_ACTIVE_UNION
 �ṹ˵��  : DGAMMA_OUT_ACTIVE �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dgamma_active : 1;  /* bit[0-0] : DGAMMA_active:
                                                        0:DGAMMA_OUT_0 is used by the HW
                                                        1:DGAMMA_OUT_1 is used by the HW */
        unsigned int  reserved      : 31; /* bit[1-31]:  */
    } reg;
} SOC_ISP_DGAMMA_DGAMMA_OUT_ACTIVE_UNION;
#endif
#define SOC_ISP_DGAMMA_DGAMMA_OUT_ACTIVE_dgamma_active_START  (0)
#define SOC_ISP_DGAMMA_DGAMMA_OUT_ACTIVE_dgamma_active_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_ISP_DGAMMA_LUTSCL_FACTOR_UNION
 �ṹ˵��  : LUTSCL_FACTOR �Ĵ����ṹ���塣��ַƫ����:0x000c����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lutscl_factor : 11; /* bit[0-10] : LSC factor U11Q10 */
        unsigned int  reserved      : 21; /* bit[11-31]:  */
    } reg;
} SOC_ISP_DGAMMA_LUTSCL_FACTOR_UNION;
#endif
#define SOC_ISP_DGAMMA_LUTSCL_FACTOR_lutscl_factor_START  (0)
#define SOC_ISP_DGAMMA_LUTSCL_FACTOR_lutscl_factor_END    (10)


/*****************************************************************************
 �ṹ��    : SOC_ISP_DGAMMA_DGAMMA_OUT_R_0_UNION
 �ṹ˵��  : DGAMMA_OUT_R_0 �Ĵ����ṹ���塣��ַƫ����:0x0100+0x4*(Range96)����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dgamma_out_r : 10; /* bit[0-9]  : 8 bits for DGamma_Out values for Red pixels */
        unsigned int  reserved     : 22; /* bit[10-31]:  */
    } reg;
} SOC_ISP_DGAMMA_DGAMMA_OUT_R_0_UNION;
#endif
#define SOC_ISP_DGAMMA_DGAMMA_OUT_R_0_dgamma_out_r_START  (0)
#define SOC_ISP_DGAMMA_DGAMMA_OUT_R_0_dgamma_out_r_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_ISP_DGAMMA_DGAMMA_OUT_G_0_UNION
 �ṹ˵��  : DGAMMA_OUT_G_0 �Ĵ����ṹ���塣��ַƫ����:0x0100+0x4*(Num96)+0x4*(Range96)����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dgamma_out_g : 10; /* bit[0-9]  : 8 bits for DGamma_Out values for Red pixels */
        unsigned int  reserved     : 22; /* bit[10-31]:  */
    } reg;
} SOC_ISP_DGAMMA_DGAMMA_OUT_G_0_UNION;
#endif
#define SOC_ISP_DGAMMA_DGAMMA_OUT_G_0_dgamma_out_g_START  (0)
#define SOC_ISP_DGAMMA_DGAMMA_OUT_G_0_dgamma_out_g_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_ISP_DGAMMA_DGAMMA_OUT_B_0_UNION
 �ṹ˵��  : DGAMMA_OUT_B_0 �Ĵ����ṹ���塣��ַƫ����:0x0100+0x4*2*(Num96)+0x4*(Range96)����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dgamma_out_b : 10; /* bit[0-9]  : 8 bits for DGamma_Out values for Red pixels */
        unsigned int  reserved     : 22; /* bit[10-31]:  */
    } reg;
} SOC_ISP_DGAMMA_DGAMMA_OUT_B_0_UNION;
#endif
#define SOC_ISP_DGAMMA_DGAMMA_OUT_B_0_dgamma_out_b_START  (0)
#define SOC_ISP_DGAMMA_DGAMMA_OUT_B_0_dgamma_out_b_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_ISP_DGAMMA_DGAMMA_OUT_R_1_UNION
 �ṹ˵��  : DGAMMA_OUT_R_1 �Ĵ����ṹ���塣��ַƫ����:0x0600+0x4*(Range96)����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dgamma_out_r : 10; /* bit[0-9]  : 8 bits for DGamma_Out values for Red pixels */
        unsigned int  reserved     : 22; /* bit[10-31]:  */
    } reg;
} SOC_ISP_DGAMMA_DGAMMA_OUT_R_1_UNION;
#endif
#define SOC_ISP_DGAMMA_DGAMMA_OUT_R_1_dgamma_out_r_START  (0)
#define SOC_ISP_DGAMMA_DGAMMA_OUT_R_1_dgamma_out_r_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_ISP_DGAMMA_DGAMMA_OUT_G_1_UNION
 �ṹ˵��  : DGAMMA_OUT_G_1 �Ĵ����ṹ���塣��ַƫ����:0x0600+0x4*(Num96)+0x4*(Range96)����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dgamma_out_g : 10; /* bit[0-9]  : 8 bits for DGamma_Out values for Red pixels */
        unsigned int  reserved     : 22; /* bit[10-31]:  */
    } reg;
} SOC_ISP_DGAMMA_DGAMMA_OUT_G_1_UNION;
#endif
#define SOC_ISP_DGAMMA_DGAMMA_OUT_G_1_dgamma_out_g_START  (0)
#define SOC_ISP_DGAMMA_DGAMMA_OUT_G_1_dgamma_out_g_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_ISP_DGAMMA_DGAMMA_OUT_B_1_UNION
 �ṹ˵��  : DGAMMA_OUT_B_1 �Ĵ����ṹ���塣��ַƫ����:0x0600+0x4*2*(Num96)+0x4*(Range96)����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dgamma_out_b : 10; /* bit[0-9]  : 8 bits for DGamma_Out values for Red pixels */
        unsigned int  reserved     : 22; /* bit[10-31]:  */
    } reg;
} SOC_ISP_DGAMMA_DGAMMA_OUT_B_1_UNION;
#endif
#define SOC_ISP_DGAMMA_DGAMMA_OUT_B_1_dgamma_out_b_START  (0)
#define SOC_ISP_DGAMMA_DGAMMA_OUT_B_1_dgamma_out_b_END    (9)






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

#endif /* end of soc_isp_dgamma_interface.h */
