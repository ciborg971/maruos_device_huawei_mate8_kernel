/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_isp_awbgain_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:21:24
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_ISP_AWBGAIN.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_ISP_AWBGAIN_INTERFACE_H__
#define __SOC_ISP_AWBGAIN_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) AWBGAIN
 ****************************************************************************/
/* �Ĵ���˵����Auto white balance gain green
   λ����UNION�ṹ:  SOC_ISP_AWBGAIN_AWBGAIN_GR_UNION */
#define SOC_ISP_AWBGAIN_AWBGAIN_GR_ADDR(base)         ((base) + (0x0000))

/* �Ĵ���˵����Auto white balance properties
   λ����UNION�ṹ:  SOC_ISP_AWBGAIN_AWBGAIN_RB_UNION */
#define SOC_ISP_AWBGAIN_AWBGAIN_RB_ADDR(base)         ((base) + (0x0004))





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
                     (1/1) AWBGAIN
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_ISP_AWBGAIN_AWBGAIN_GR_UNION
 �ṹ˵��  : AWBGAIN_GR �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: Auto white balance gain green
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  awb_gain_gb : 12; /* bit[0-11] : gain value for green component in blue line 400h = 1, unsigned integer value, range 0 to 4 with 10 bit fractional part */
        unsigned int  reserved_0  : 4;  /* bit[12-15]: reserved */
        unsigned int  awb_gain_gr : 12; /* bit[16-27]: gain value for green component in red line 400h = 1, unsigned integer value, range 0 to 4 with 10 bit fractional part */
        unsigned int  reserved_1  : 4;  /* bit[28-31]: Reserved */
    } reg;
} SOC_ISP_AWBGAIN_AWBGAIN_GR_UNION;
#endif
#define SOC_ISP_AWBGAIN_AWBGAIN_GR_awb_gain_gb_START  (0)
#define SOC_ISP_AWBGAIN_AWBGAIN_GR_awb_gain_gb_END    (11)
#define SOC_ISP_AWBGAIN_AWBGAIN_GR_awb_gain_gr_START  (16)
#define SOC_ISP_AWBGAIN_AWBGAIN_GR_awb_gain_gr_END    (27)


/*****************************************************************************
 �ṹ��    : SOC_ISP_AWBGAIN_AWBGAIN_RB_UNION
 �ṹ˵��  : AWBGAIN_RB �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: Auto white balance properties
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  awb_gain_b : 12; /* bit[0-11] : gain value for green component in blue line 400h = 1, unsigned integer value, range 0 to 4 with 10 bit fractional part */
        unsigned int  reserved_0 : 4;  /* bit[12-15]: reserved */
        unsigned int  awb_gain_r : 12; /* bit[16-27]: gain value for green component in red line 400h = 1, unsigned integer value, range 0 to 4 with 10 bit fractional part */
        unsigned int  reserved_1 : 4;  /* bit[28-31]: Reserved */
    } reg;
} SOC_ISP_AWBGAIN_AWBGAIN_RB_UNION;
#endif
#define SOC_ISP_AWBGAIN_AWBGAIN_RB_awb_gain_b_START  (0)
#define SOC_ISP_AWBGAIN_AWBGAIN_RB_awb_gain_b_END    (11)
#define SOC_ISP_AWBGAIN_AWBGAIN_RB_awb_gain_r_START  (16)
#define SOC_ISP_AWBGAIN_AWBGAIN_RB_awb_gain_r_END    (27)






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

#endif /* end of soc_isp_awbgain_interface.h */
