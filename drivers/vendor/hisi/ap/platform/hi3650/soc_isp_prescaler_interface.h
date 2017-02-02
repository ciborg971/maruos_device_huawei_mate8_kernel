/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_isp_prescaler_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:22:01
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_ISP_PRESCALER.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_ISP_PRESCALER_INTERFACE_H__
#define __SOC_ISP_PRESCALER_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) PRESCALER
 ****************************************************************************/
/* �Ĵ���˵����horizontal cropping configuration
   λ����UNION�ṹ:  SOC_ISP_PRESCALER_HCROP_UNION */
#define SOC_ISP_PRESCALER_HCROP_ADDR(base)            ((base) + (0x0000))

/* �Ĵ���˵����vertical cropping configuration
   λ����UNION�ṹ:  SOC_ISP_PRESCALER_VCROP_UNION */
#define SOC_ISP_PRESCALER_VCROP_ADDR(base)            ((base) + (0x0004))

/* �Ĵ���˵����Prescaler Mode
   λ����UNION�ṹ:  SOC_ISP_PRESCALER_MODE_UNION */
#define SOC_ISP_PRESCALER_MODE_ADDR(base)             ((base) + (0x0008))





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
                     (1/1) PRESCALER
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_ISP_PRESCALER_HCROP_UNION
 �ṹ˵��  : HCROP �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: horizontal cropping configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ihright1 : 13; /* bit[0-12] : Position of last pixel in active area of picture from H-GKM1 (left picture).It should be set according to left picture size (=ihsize1-1).When there is merge 2 extra pixels should be received at input right border. Qu13.0
                                                    0x1FFF means no crop
                                                    otherwise:
                                                    0:first pixel in input stream
                                                    1:second pixel in input stream
                                                    n:(n+1) th pixel in input stream */
        unsigned int  reserved_0: 3;  /* bit[13-15]:  */
        unsigned int  ihright2 : 13; /* bit[16-28]: Position of last pixel in active area of picture from H-GKM2 (right picture).It should be set according to right picture size (=hsize2-1) Qu13.0
                                                    0x1FFF means no crop
                                                    otherwise:
                                                    0:first pixel in input stream
                                                    1:second pixel in input stream
                                                    n:(n+1) th pixel in input stream */
        unsigned int  ihleft2  : 2;  /* bit[29-30]: Position of first pixel in active area of right picture ( from GKM-2) Qu2.0 . 0 means no crop. It should be set to 0 when no merge- It should be set to 1 in merge case ( two extra pixels received at input left border )
                                                    0:first pixel is pixel 0
                                                    1:first pixel is pixel 1
                                                    n:first pixel is pixel #n */
        unsigned int  reserved_1: 1;  /* bit[31-31]:  */
    } reg;
} SOC_ISP_PRESCALER_HCROP_UNION;
#endif
#define SOC_ISP_PRESCALER_HCROP_ihright1_START  (0)
#define SOC_ISP_PRESCALER_HCROP_ihright1_END    (12)
#define SOC_ISP_PRESCALER_HCROP_ihright2_START  (16)
#define SOC_ISP_PRESCALER_HCROP_ihright2_END    (28)
#define SOC_ISP_PRESCALER_HCROP_ihleft2_START   (29)
#define SOC_ISP_PRESCALER_HCROP_ihleft2_END     (30)


/*****************************************************************************
 �ṹ��    : SOC_ISP_PRESCALER_VCROP_UNION
 �ṹ˵��  : VCROP �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: vertical cropping configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ivbottom : 13; /* bit[0-12] : Position of last line in active area of picture. Qu13.0
                                                    0x1FFF means no crop
                                                    otherwise:
                                                    0:first line in input stream
                                                    1:second line in input stream
                                                    n:(n+1) th line in input stream */
        unsigned int  reserved : 19; /* bit[13-31]:  */
    } reg;
} SOC_ISP_PRESCALER_VCROP_UNION;
#endif
#define SOC_ISP_PRESCALER_VCROP_ivbottom_START  (0)
#define SOC_ISP_PRESCALER_VCROP_ivbottom_END    (12)


/*****************************************************************************
 �ṹ��    : SOC_ISP_PRESCALER_MODE_UNION
 �ṹ˵��  : MODE �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000004�����:32
 �Ĵ���˵��: Prescaler Mode
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  input_sel : 2;  /* bit[0-1] : Selection Frame Merger Input
                                                    00, 01: H-GKM1 is selected, H-GKM2 is not used- 
                                                    10:H-GKM2 is selected and H-GKM1 is not used
                                                    11: both H-GKM1 and H-GKM2 are selected for merge.  */
        unsigned int  bypass    : 1;  /* bit[2-2] : Bypass mode configuration:
                                                    0: No bypass
                                                    1: Bypass mode */
        unsigned int  reserved  : 29; /* bit[3-31]:  */
    } reg;
} SOC_ISP_PRESCALER_MODE_UNION;
#endif
#define SOC_ISP_PRESCALER_MODE_input_sel_START  (0)
#define SOC_ISP_PRESCALER_MODE_input_sel_END    (1)
#define SOC_ISP_PRESCALER_MODE_bypass_START     (2)
#define SOC_ISP_PRESCALER_MODE_bypass_END       (2)






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

#endif /* end of soc_isp_prescaler_interface.h */
