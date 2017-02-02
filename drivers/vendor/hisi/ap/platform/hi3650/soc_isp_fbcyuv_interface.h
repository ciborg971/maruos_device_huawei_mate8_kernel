/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_isp_fbcyuv_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:21:36
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_ISP_FBCYUV.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_ISP_FBCYUV_INTERFACE_H__
#define __SOC_ISP_FBCYUV_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) FBCYUV
 ****************************************************************************/
/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ISP_FBCYUV_FBC_CONFIG1_UNION */
#define SOC_ISP_FBCYUV_FBC_CONFIG1_ADDR(base)         ((base) + (0x0000))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ISP_FBCYUV_FBC_CONFIG2_UNION */
#define SOC_ISP_FBCYUV_FBC_CONFIG2_ADDR(base)         ((base) + (0x0004))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ISP_FBCYUV_FBC_STREAM_SIZE_UNION */
#define SOC_ISP_FBCYUV_FBC_STREAM_SIZE_ADDR(base)     ((base) + (0x0008))





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
                     (1/1) FBCYUV
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_ISP_FBCYUV_FBC_CONFIG1_UNION
 �ṹ˵��  : FBC_CONFIG1 �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass     : 1;  /* bit[0-0]  : Bypass:
                                                      0: the module is active
                                                      1: the module is bypassed
                                                      the configuration is taken into account on a SOF.(Same HW behavior as RW_SHADOW) */
        unsigned int  reserved_0 : 15; /* bit[1-15] :  */
        unsigned int  line_width : 13; /* bit[16-28]: line width-1 (max is LM_SIZE-1 = 4224-1) */
        unsigned int  reserved_1 : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_FBCYUV_FBC_CONFIG1_UNION;
#endif
#define SOC_ISP_FBCYUV_FBC_CONFIG1_bypass_START      (0)
#define SOC_ISP_FBCYUV_FBC_CONFIG1_bypass_END        (0)
#define SOC_ISP_FBCYUV_FBC_CONFIG1_line_width_START  (16)
#define SOC_ISP_FBCYUV_FBC_CONFIG1_line_width_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_FBCYUV_FBC_CONFIG2_UNION
 �ṹ˵��  : FBC_CONFIG2 �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00460F20�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  initqpy   : 6;  /* bit[0-5]  :  */
        unsigned int  reserved_0: 2;  /* bit[6-7]  :  */
        unsigned int  initqpuv  : 5;  /* bit[8-12] :  */
        unsigned int  reserved_1: 3;  /* bit[13-15]:  */
        unsigned int  bit_thres : 8;  /* bit[16-23]:  */
        unsigned int  reserved_2: 8;  /* bit[24-31]:  */
    } reg;
} SOC_ISP_FBCYUV_FBC_CONFIG2_UNION;
#endif
#define SOC_ISP_FBCYUV_FBC_CONFIG2_initqpy_START    (0)
#define SOC_ISP_FBCYUV_FBC_CONFIG2_initqpy_END      (5)
#define SOC_ISP_FBCYUV_FBC_CONFIG2_initqpuv_START   (8)
#define SOC_ISP_FBCYUV_FBC_CONFIG2_initqpuv_END     (12)
#define SOC_ISP_FBCYUV_FBC_CONFIG2_bit_thres_START  (16)
#define SOC_ISP_FBCYUV_FBC_CONFIG2_bit_thres_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_ISP_FBCYUV_FBC_STREAM_SIZE_UNION
 �ṹ˵��  : FBC_STREAM_SIZE �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  streamsize : 22; /* bit[0-21] : length of the current encoded stream for the full frame, in 64b words
                                                      max=2635776 */
        unsigned int  reserved   : 10; /* bit[22-31]:  */
    } reg;
} SOC_ISP_FBCYUV_FBC_STREAM_SIZE_UNION;
#endif
#define SOC_ISP_FBCYUV_FBC_STREAM_SIZE_streamsize_START  (0)
#define SOC_ISP_FBCYUV_FBC_STREAM_SIZE_streamsize_END    (21)






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

#endif /* end of soc_isp_fbcyuv_interface.h */
