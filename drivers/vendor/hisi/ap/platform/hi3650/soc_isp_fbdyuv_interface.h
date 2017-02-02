/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_isp_fbdyuv_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:21:38
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_ISP_FBDYUV.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_ISP_FBDYUV_INTERFACE_H__
#define __SOC_ISP_FBDYUV_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) FBDYUV
 ****************************************************************************/
/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ISP_FBDYUV_FBD_CONFIG_UNION */
#define SOC_ISP_FBDYUV_FBD_CONFIG_ADDR(base)          ((base) + (0x0000))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ISP_FBDYUV_FBD_STATUS_UNION */
#define SOC_ISP_FBDYUV_FBD_STATUS_ADDR(base)          ((base) + (0x0004))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ISP_FBDYUV_FBD_STREAM_SIZE_UNION */
#define SOC_ISP_FBDYUV_FBD_STREAM_SIZE_ADDR(base)     ((base) + (0x0008))





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
                     (1/1) FBDYUV
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_ISP_FBDYUV_FBD_CONFIG_UNION
 �ṹ˵��  : FBD_CONFIG �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000001�����:32
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
                                                      1: the module is bypassed */
        unsigned int  reserved_0 : 15; /* bit[1-15] :  */
        unsigned int  line_width : 13; /* bit[16-28]: Line width-1 (max =4224-1) */
        unsigned int  reserved_1 : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_FBDYUV_FBD_CONFIG_UNION;
#endif
#define SOC_ISP_FBDYUV_FBD_CONFIG_bypass_START      (0)
#define SOC_ISP_FBDYUV_FBD_CONFIG_bypass_END        (0)
#define SOC_ISP_FBDYUV_FBD_CONFIG_line_width_START  (16)
#define SOC_ISP_FBDYUV_FBD_CONFIG_line_width_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_FBDYUV_FBD_STATUS_UNION
 �ṹ˵��  : FBD_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stream_error : 1;  /* bit[0-0] : default is 0. In case the FBD hardware detects the stream is corrupted, it stream_error is asserted high. It is the FW responsibility to clear this bit */
        unsigned int  reserved     : 31; /* bit[1-31]:  */
    } reg;
} SOC_ISP_FBDYUV_FBD_STATUS_UNION;
#endif
#define SOC_ISP_FBDYUV_FBD_STATUS_stream_error_START  (0)
#define SOC_ISP_FBDYUV_FBD_STATUS_stream_error_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_ISP_FBDYUV_FBD_STREAM_SIZE_UNION
 �ṹ˵��  : FBD_STREAM_SIZE �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
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
} SOC_ISP_FBDYUV_FBD_STREAM_SIZE_UNION;
#endif
#define SOC_ISP_FBDYUV_FBD_STREAM_SIZE_streamsize_START  (0)
#define SOC_ISP_FBDYUV_FBD_STREAM_SIZE_streamsize_END    (21)






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

#endif /* end of soc_isp_fbdyuv_interface.h */
