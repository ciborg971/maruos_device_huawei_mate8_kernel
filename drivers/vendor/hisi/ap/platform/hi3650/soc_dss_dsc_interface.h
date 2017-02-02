/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_dss_dsc_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:20:03
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_DSS_DSC.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_DSS_DSC_INTERFACE_H__
#define __SOC_DSS_DSC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_DSC
 ****************************************************************************/
/* �Ĵ���˵�����汾�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_DSC_VERSION_UNION */
#define SOC_DSS_DSC_VERSION_ADDR(base)                ((base) + (0x0000))

/* �Ĵ���˵����PPS��־�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_DSC_PPS_IDENTIFIER_UNION */
#define SOC_DSS_DSC_PPS_IDENTIFIER_ADDR(base)         ((base) + (0x0004))

/* �Ĵ���˵����ʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_DSS_DSC_DSC_EN_UNION */
#define SOC_DSS_DSC_DSC_EN_ADDR(base)                 ((base) + (0x0008))

/* �Ĵ���˵�������ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_DSC_DSC_CTRL_UNION */
#define SOC_DSS_DSC_DSC_CTRL_ADDR(base)               ((base) + (0x000C))

/* �Ĵ���˵��������ͼ��ߴ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_DSC_PIC_SIZE_UNION */
#define SOC_DSS_DSC_PIC_SIZE_ADDR(base)               ((base) + (0x0010))

/* �Ĵ���˵����SLICE�ߴ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_DSC_SLICE_SIZE_UNION */
#define SOC_DSS_DSC_SLICE_SIZE_ADDR(base)             ((base) + (0x0014))

/* �Ĵ���˵����chunk�ߴ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_DSC_CHUNK_SIZE_UNION */
#define SOC_DSS_DSC_CHUNK_SIZE_ADDR(base)             ((base) + (0x0018))

/* �Ĵ���˵����RC model��ʱ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_DSC_INITIAL_DELAY_UNION */
#define SOC_DSS_DSC_INITIAL_DELAY_ADDR(base)          ((base) + (0x001C))

/* �Ĵ���˵����RC�����Ĵ���0
   λ����UNION�ṹ:  SOC_DSS_DSC_RC_PARAM0_UNION */
#define SOC_DSS_DSC_RC_PARAM0_ADDR(base)              ((base) + (0x0020))

/* �Ĵ���˵����RC�����Ĵ���1
   λ����UNION�ṹ:  SOC_DSS_DSC_RC_PARAM1_UNION */
#define SOC_DSS_DSC_RC_PARAM1_ADDR(base)              ((base) + (0x0024))

/* �Ĵ���˵����RC�����Ĵ���2
   λ����UNION�ṹ:  SOC_DSS_DSC_RC_PARAM2_UNION */
#define SOC_DSS_DSC_RC_PARAM2_ADDR(base)              ((base) + (0x0028))

/* �Ĵ���˵����RC�����Ĵ���3
   λ����UNION�ṹ:  SOC_DSS_DSC_RC_PARAM3_UNION */
#define SOC_DSS_DSC_RC_PARAM3_ADDR(base)              ((base) + (0x002C))

/* �Ĵ���˵����flatness QP��ֵ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_DSC_FLATNESS_QP_TH_UNION */
#define SOC_DSS_DSC_FLATNESS_QP_TH_ADDR(base)         ((base) + (0x0030))

/* �Ĵ���˵����RC�����Ĵ���4
   λ����UNION�ṹ:  SOC_DSS_DSC_RC_PARAM4_UNION */
#define SOC_DSS_DSC_RC_PARAM4_ADDR(base)              ((base) + (0x0034))

/* �Ĵ���˵����RC�����Ĵ���5
   λ����UNION�ṹ:  SOC_DSS_DSC_RC_PARAM5_UNION */
#define SOC_DSS_DSC_RC_PARAM5_ADDR(base)              ((base) + (0x0038))

/* �Ĵ���˵����fullness��ֵ�Ĵ���0
   λ����UNION�ṹ:  SOC_DSS_DSC_RC_BUF_THRESH0_UNION */
#define SOC_DSS_DSC_RC_BUF_THRESH0_ADDR(base)         ((base) + (0x003C))

/* �Ĵ���˵����fullness��ֵ�Ĵ���1
   λ����UNION�ṹ:  SOC_DSS_DSC_RC_BUF_THRESH1_UNION */
#define SOC_DSS_DSC_RC_BUF_THRESH1_ADDR(base)         ((base) + (0x0040))

/* �Ĵ���˵����fullness��ֵ�Ĵ���2
   λ����UNION�ṹ:  SOC_DSS_DSC_RC_BUF_THRESH2_UNION */
#define SOC_DSS_DSC_RC_BUF_THRESH2_ADDR(base)         ((base) + (0x0044))

/* �Ĵ���˵����fullness��ֵ�Ĵ���3
   λ����UNION�ṹ:  SOC_DSS_DSC_RC_BUF_THRESH3_UNION */
#define SOC_DSS_DSC_RC_BUF_THRESH3_ADDR(base)         ((base) + (0x0048))

/* �Ĵ���˵����RC_RANGE�����Ĵ���0
   λ����UNION�ṹ:  SOC_DSS_DSC_RC_RANGE_PARAM0_UNION */
#define SOC_DSS_DSC_RC_RANGE_PARAM0_ADDR(base)        ((base) + (0x004C))

/* �Ĵ���˵����RC_RANGE�����Ĵ���1
   λ����UNION�ṹ:  SOC_DSS_DSC_RC_RANGE_PARAM1_UNION */
#define SOC_DSS_DSC_RC_RANGE_PARAM1_ADDR(base)        ((base) + (0x0050))

/* �Ĵ���˵����RC_RANGE�����Ĵ���2
   λ����UNION�ṹ:  SOC_DSS_DSC_RC_RANGE_PARAM2_UNION */
#define SOC_DSS_DSC_RC_RANGE_PARAM2_ADDR(base)        ((base) + (0x0054))

/* �Ĵ���˵����RC_RANGE�����Ĵ���3
   λ����UNION�ṹ:  SOC_DSS_DSC_RC_RANGE_PARAM3_UNION */
#define SOC_DSS_DSC_RC_RANGE_PARAM3_ADDR(base)        ((base) + (0x0058))

/* �Ĵ���˵����RC_RANGE�����Ĵ���4
   λ����UNION�ṹ:  SOC_DSS_DSC_RC_RANGE_PARAM4_UNION */
#define SOC_DSS_DSC_RC_RANGE_PARAM4_ADDR(base)        ((base) + (0x005C))

/* �Ĵ���˵����RC_RANGE�����Ĵ���5
   λ����UNION�ṹ:  SOC_DSS_DSC_RC_RANGE_PARAM5_UNION */
#define SOC_DSS_DSC_RC_RANGE_PARAM5_ADDR(base)        ((base) + (0x0060))

/* �Ĵ���˵����RC_RANGE�����Ĵ���6
   λ����UNION�ṹ:  SOC_DSS_DSC_RC_RANGE_PARAM6_UNION */
#define SOC_DSS_DSC_RC_RANGE_PARAM6_ADDR(base)        ((base) + (0x0064))

/* �Ĵ���˵����RC_RANGE�����Ĵ���7
   λ����UNION�ṹ:  SOC_DSS_DSC_RC_RANGE_PARAM7_UNION */
#define SOC_DSS_DSC_RC_RANGE_PARAM7_ADDR(base)        ((base) + (0x0068))

/* �Ĵ���˵����ADJUSTMENT_BITS�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_DSC_ADJUSTMENT_BITS_UNION */
#define SOC_DSS_DSC_ADJUSTMENT_BITS_ADDR(base)        ((base) + (0x006C))

/* �Ĵ���˵����group����ߴ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_DSC_BITS_PER_GRP_UNION */
#define SOC_DSS_DSC_BITS_PER_GRP_ADDR(base)           ((base) + (0x0070))

/* �Ĵ���˵����multi_slice���ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_DSC_MULTI_SLICE_CTL_UNION */
#define SOC_DSS_DSC_MULTI_SLICE_CTL_ADDR(base)        ((base) + (0x0074))

/* �Ĵ���˵����DSC������ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_DSC_DSC_OUT_CTRL_UNION */
#define SOC_DSS_DSC_DSC_OUT_CTRL_ADDR(base)           ((base) + (0x0078))

/* �Ĵ���˵����һ��ģ��ʱ��ѡ���ź�
   λ����UNION�ṹ:  SOC_DSS_DSC_DSC_CLK_SEL_UNION */
#define SOC_DSS_DSC_DSC_CLK_SEL_ADDR(base)            ((base) + (0x007C))

/* �Ĵ���˵����һ��ģ��ʱ��ʹ���ź�
   λ����UNION�ṹ:  SOC_DSS_DSC_DSC_CLK_EN_UNION */
#define SOC_DSS_DSC_DSC_CLK_EN_ADDR(base)             ((base) + (0x0080))

/* �Ĵ���˵����DSC memory�͹��Ŀ��ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_DSC_DSC_MEM_CTRL_UNION */
#define SOC_DSS_DSC_DSC_MEM_CTRL_ADDR(base)           ((base) + (0x0084))

/* �Ĵ���˵��������״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_DSC_DSC_ST_DATAIN_UNION */
#define SOC_DSS_DSC_DSC_ST_DATAIN_ADDR(base)          ((base) + (0x0088))

/* �Ĵ���˵�������״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_DSC_DSC_ST_DATAOUT_UNION */
#define SOC_DSS_DSC_DSC_ST_DATAOUT_ADDR(base)         ((base) + (0x008C))

/* �Ĵ���˵����SLICEλ��״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_DSC_DSC0_ST_SLC_POS_UNION */
#define SOC_DSS_DSC_DSC0_ST_SLC_POS_ADDR(base)        ((base) + (0x0090))

/* �Ĵ���˵����SLICEλ��״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_DSC_DSC1_ST_SLC_POS_UNION */
#define SOC_DSS_DSC_DSC1_ST_SLC_POS_ADDR(base)        ((base) + (0x0094))

/* �Ĵ���˵����PICTUREλ��״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_DSC_DSC0_ST_PIC_POS_UNION */
#define SOC_DSS_DSC_DSC0_ST_PIC_POS_ADDR(base)        ((base) + (0x0098))

/* �Ĵ���˵����PICTUREλ��״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_DSC_DSC1_ST_PIC_POS_UNION */
#define SOC_DSS_DSC_DSC1_ST_PIC_POS_ADDR(base)        ((base) + (0x009C))

/* �Ĵ���˵����FIFO����״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_DSC_DSC0_ST_FIFO_UNION */
#define SOC_DSS_DSC_DSC0_ST_FIFO_ADDR(base)           ((base) + (0x00A0))

/* �Ĵ���˵����FIFO����״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_DSC_DSC1_ST_FIFO_UNION */
#define SOC_DSS_DSC_DSC1_ST_FIFO_ADDR(base)           ((base) + (0x00A4))

/* �Ĵ���˵����LINEBUF״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_DSC_DSC0_ST_LINEBUF_UNION */
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_ADDR(base)        ((base) + (0x00A8))

/* �Ĵ���˵����LINEBUF״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_DSC_DSC1_ST_LINEBUF_UNION */
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_ADDR(base)        ((base) + (0x00AC))

/* �Ĵ���˵�����ӿ�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_DSC_DSC_ST_ITFC_UNION */
#define SOC_DSS_DSC_DSC_ST_ITFC_ADDR(base)            ((base) + (0x00B0))

/* �Ĵ���˵�������Ĵ���ѡ���ź�
   λ����UNION�ṹ:  SOC_DSS_DSC_DSC_RD_SHADOW_SEL_UNION */
#define SOC_DSS_DSC_DSC_RD_SHADOW_SEL_ADDR(base)      ((base) + (0x00B4))

/* �Ĵ���˵����ģ��Ӱ�ӼĴ����ָ���Ĭ��ֵ
   λ����UNION�ṹ:  SOC_DSS_DSC_DSC_REG_DEFAULT_UNION */
#define SOC_DSS_DSC_DSC_REG_DEFAULT_ADDR(base)        ((base) + (0x00B8))





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
                     (1/1) reg_DSC
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_VERSION_UNION
 �ṹ˵��  : VERSION �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000011�����:32
 �Ĵ���˵��: �汾�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc_version_minor : 4;  /* bit[0-3] : С�汾�� */
        unsigned int  dsc_version_major : 4;  /* bit[4-7] : ��汾�� */
        unsigned int  reserved          : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_DSS_DSC_VERSION_UNION;
#endif
#define SOC_DSS_DSC_VERSION_dsc_version_minor_START  (0)
#define SOC_DSS_DSC_VERSION_dsc_version_minor_END    (3)
#define SOC_DSS_DSC_VERSION_dsc_version_major_START  (4)
#define SOC_DSS_DSC_VERSION_dsc_version_major_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_PPS_IDENTIFIER_UNION
 �ṹ˵��  : PPS_IDENTIFIER �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: PPS��־�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pps_identifier : 8;  /* bit[0-7] : PPSʶ��� */
        unsigned int  reserved       : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_DSC_PPS_IDENTIFIER_UNION;
#endif
#define SOC_DSS_DSC_PPS_IDENTIFIER_pps_identifier_START  (0)
#define SOC_DSS_DSC_PPS_IDENTIFIER_pps_identifier_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_DSC_EN_UNION
 �ṹ˵��  : DSC_EN �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000004�����:32
 �Ĵ���˵��: ʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc_en             : 1;  /* bit[0]   : DSCʹ�ܼĴ���
                                                             0: DSC��ʹ��
                                                             1: DSCʹ�� */
        unsigned int  dual_dsc_en        : 1;  /* bit[1]   : ˫ͨ��DSCʹ�ܼĴ���
                                                             0: ʹ�õ�ͨ��DSC
                                                             1: ʹ��˫ͨ��DSC
                                                             ˫ͨ��DSC�ڴ�ֱ��ʣ�1080P���ϣ�ʱʹ�ã�������ҪLCD֧����2��DSC decoder��ѹ */
        unsigned int  dsc_if_bypass      : 1;  /* bit[2]   : dsc_if bypass���ƼĴ���
                                                             0: dsc_ifʹ��
                                                             1: dsc_if��ʹ��
                                                             ���Լ����
                                                             ��dual_dsc_en=1ʱ��dsc_if_bypass����Ϊ0��
                                                             ��dual_dsc_en=0ʱ��dsc_if_bypassΪ0��1���ɣ�����Ϊ1 */
        unsigned int  reset_ich_per_line : 1;  /* bit[3]   : ichÿ�и�λʹ�ܼĴ���
                                                             0: ��ʹ��ÿ�и�λich����
                                                             1: ÿ����ʼʱ��λich
                                                             
                                                             ����Э��������ǣ���dual_dsc_en = 1ʱ��reset_ich_per_line����Ϊ1��
                                                             �����DriverIC��֧��ÿ�и�λich����bit��Ҫ����Ϊ0�� */
        unsigned int  reserved           : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_DSS_DSC_DSC_EN_UNION;
#endif
#define SOC_DSS_DSC_DSC_EN_dsc_en_START              (0)
#define SOC_DSS_DSC_DSC_EN_dsc_en_END                (0)
#define SOC_DSS_DSC_DSC_EN_dual_dsc_en_START         (1)
#define SOC_DSS_DSC_DSC_EN_dual_dsc_en_END           (1)
#define SOC_DSS_DSC_DSC_EN_dsc_if_bypass_START       (2)
#define SOC_DSS_DSC_DSC_EN_dsc_if_bypass_END         (2)
#define SOC_DSS_DSC_DSC_EN_reset_ich_per_line_START  (3)
#define SOC_DSS_DSC_DSC_EN_reset_ich_per_line_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_DSC_CTRL_UNION
 �ṹ˵��  : DSC_CTRL �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00080C98�����:32
 �Ĵ���˵��: ���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bits_per_component : 4;  /* bit[0-3]  : ��������ÿ�������ı��������޷�������
                                                              4'b1000: 8 bpc
                                                              ����: ���� */
        unsigned int  linebuf_depth      : 4;  /* bit[4-7]  : line buffer����λ��Ĵ������޷�������
                                                              4'b1000: 8 bits
                                                              4'b1001: 9 bits
                                                              ���������� */
        unsigned int  reserved_0         : 2;  /* bit[8-9]  : ���� */
        unsigned int  block_pred_enable  : 1;  /* bit[10]   : block predictionʹ�ܼĴ���
                                                              1'b0: ��ʹ��block prediction
                                                              1'b1: ʹ��block prediction */
        unsigned int  convert_rgb        : 1;  /* bit[11]   : RGB->YCoCgת��ʹ�ܼĴ���
                                                              1'b0: ԭʼ��������YCbCr
                                                              1'b1: �������������RGBת����YCoCg */
        unsigned int  enable_422         : 1;  /* bit[12]   : YCbCr����ģʽ�Ĵ���
                                                              1'b0: ʹ��4:4:4����
                                                              1'b1: ʹ��4:2:2���� */
        unsigned int  vbr_enable         : 1;  /* bit[13]   : VBRʹ�ܼĴ���
                                                              1'b0: ��ʹ��VBR
                                                              1'b1: ʹ��VBR */
        unsigned int  reserved_1         : 2;  /* bit[14-15]: ���� */
        unsigned int  bits_per_pixel     : 10; /* bit[16-25]: Ŀ��ѹ�����ݱ��ؼĴ������޷�������
                                                              ���Լ����
                                                              1. ��֧�ִ��ڵ���6bpp����ֵ
                                                              2. ��vbr_enable=0ʱ���˼Ĵ�����С��ʼ��ʹ��MPPԤ��ʱѹ�����صı����� */
        unsigned int  reserved_2         : 6;  /* bit[26-31]: ������ */
    } reg;
} SOC_DSS_DSC_DSC_CTRL_UNION;
#endif
#define SOC_DSS_DSC_DSC_CTRL_bits_per_component_START  (0)
#define SOC_DSS_DSC_DSC_CTRL_bits_per_component_END    (3)
#define SOC_DSS_DSC_DSC_CTRL_linebuf_depth_START       (4)
#define SOC_DSS_DSC_DSC_CTRL_linebuf_depth_END         (7)
#define SOC_DSS_DSC_DSC_CTRL_block_pred_enable_START   (10)
#define SOC_DSS_DSC_DSC_CTRL_block_pred_enable_END     (10)
#define SOC_DSS_DSC_DSC_CTRL_convert_rgb_START         (11)
#define SOC_DSS_DSC_DSC_CTRL_convert_rgb_END           (11)
#define SOC_DSS_DSC_DSC_CTRL_enable_422_START          (12)
#define SOC_DSS_DSC_DSC_CTRL_enable_422_END            (12)
#define SOC_DSS_DSC_DSC_CTRL_vbr_enable_START          (13)
#define SOC_DSS_DSC_DSC_CTRL_vbr_enable_END            (13)
#define SOC_DSS_DSC_DSC_CTRL_bits_per_pixel_START      (16)
#define SOC_DSS_DSC_DSC_CTRL_bits_per_pixel_END        (25)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_PIC_SIZE_UNION
 �ṹ˵��  : PIC_SIZE �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͼ��ߴ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pic_height : 16; /* bit[0-15] : ԭʼ����ͼ��߶ȼĴ�������λ���С�����ֵΪʵ��ֵ��1 */
        unsigned int  pic_width  : 16; /* bit[16-31]: ԭʼ����ͼ���ȼĴ�������λ�����ء�����ֵΪʵ��ֵ��1 */
    } reg;
} SOC_DSS_DSC_PIC_SIZE_UNION;
#endif
#define SOC_DSS_DSC_PIC_SIZE_pic_height_START  (0)
#define SOC_DSS_DSC_PIC_SIZE_pic_height_END    (15)
#define SOC_DSS_DSC_PIC_SIZE_pic_width_START   (16)
#define SOC_DSS_DSC_PIC_SIZE_pic_width_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_SLICE_SIZE_UNION
 �ṹ˵��  : SLICE_SIZE �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: SLICE�ߴ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  slice_height : 16; /* bit[0-15] : slice�߶ȼĴ�������λ���С�����ֵΪʵ��ֵ��1 */
        unsigned int  slice_width  : 16; /* bit[16-31]: slice��ȼĴ�������λ�����ء�����ֵΪʵ��ֵ��1 */
    } reg;
} SOC_DSS_DSC_SLICE_SIZE_UNION;
#endif
#define SOC_DSS_DSC_SLICE_SIZE_slice_height_START  (0)
#define SOC_DSS_DSC_SLICE_SIZE_slice_height_END    (15)
#define SOC_DSS_DSC_SLICE_SIZE_slice_width_START   (16)
#define SOC_DSS_DSC_SLICE_SIZE_slice_width_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_CHUNK_SIZE_UNION
 �ṹ˵��  : CHUNK_SIZE �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: chunk�ߴ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  chunk_size : 16; /* bit[0-15] : chunk�ߴ�Ĵ��������޷�������
                                                      ����ֵΪceil(bits_per_pixel*slice_width/8) bytes */
        unsigned int  reserved   : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_DSS_DSC_CHUNK_SIZE_UNION;
#endif
#define SOC_DSS_DSC_CHUNK_SIZE_chunk_size_START  (0)
#define SOC_DSS_DSC_CHUNK_SIZE_chunk_size_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_INITIAL_DELAY_UNION
 �ṹ˵��  : INITIAL_DELAY �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000200�����:32
 �Ĵ���˵��: RC model��ʱ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  initial_xmit_delay : 10; /* bit[0-9]  : Initial decoding delay. Specifies the number
                                                              of pixel times that the decoder accumulates
                                                              data in its rate buffer before starting
                                                              to decode and output pixels. */
        unsigned int  reserved           : 6;  /* bit[10-15]: ���� */
        unsigned int  initial_dec_delay  : 16; /* bit[16-31]: Initial transmission delay. Specifies the
                                                              number of pixel times that the encoder waits
                                                              before transmitting data from its rate buffer. */
    } reg;
} SOC_DSS_DSC_INITIAL_DELAY_UNION;
#endif
#define SOC_DSS_DSC_INITIAL_DELAY_initial_xmit_delay_START  (0)
#define SOC_DSS_DSC_INITIAL_DELAY_initial_xmit_delay_END    (9)
#define SOC_DSS_DSC_INITIAL_DELAY_initial_dec_delay_START   (16)
#define SOC_DSS_DSC_INITIAL_DELAY_initial_dec_delay_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_RC_PARAM0_UNION
 �ṹ˵��  : RC_PARAM0 �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000020�����:32
 �Ĵ���˵��: RC�����Ĵ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  initial_scale_value      : 6;  /* bit[0-5]  : �޷���С������������λС��λ
                                                                    Specifies the initial rcXformScale factor value used at the beginning of a slice */
        unsigned int  reserved                 : 10; /* bit[6-15] : ���� */
        unsigned int  scale_increment_interval : 16; /* bit[16-31]: Specifies the number of group times between
                                                                    incrementing the rcXformScale factor at the end of a slice */
    } reg;
} SOC_DSS_DSC_RC_PARAM0_UNION;
#endif
#define SOC_DSS_DSC_RC_PARAM0_initial_scale_value_START       (0)
#define SOC_DSS_DSC_RC_PARAM0_initial_scale_value_END         (5)
#define SOC_DSS_DSC_RC_PARAM0_scale_increment_interval_START  (16)
#define SOC_DSS_DSC_RC_PARAM0_scale_increment_interval_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_RC_PARAM1_UNION
 �ṹ˵��  : RC_PARAM1 �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x000C0000�����:32
 �Ĵ���˵��: RC�����Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scale_decrement_interval : 12; /* bit[0-11] : Specifies the number of group times between decrementing the rcXformScale factor at the beginning of a slice */
        unsigned int  reserved_0               : 4;  /* bit[12-15]: ���� */
        unsigned int  first_line_bpg_offset    : 5;  /* bit[16-20]: �޷�������
                                                                    Specifies the number of additional bits that are allocated for each group on the first line of a slice. */
        unsigned int  reserved_1               : 11; /* bit[21-31]: ���� */
    } reg;
} SOC_DSS_DSC_RC_PARAM1_UNION;
#endif
#define SOC_DSS_DSC_RC_PARAM1_scale_decrement_interval_START  (0)
#define SOC_DSS_DSC_RC_PARAM1_scale_decrement_interval_END    (11)
#define SOC_DSS_DSC_RC_PARAM1_first_line_bpg_offset_START     (16)
#define SOC_DSS_DSC_RC_PARAM1_first_line_bpg_offset_END       (20)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_RC_PARAM2_UNION
 �ṹ˵��  : RC_PARAM2 �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x00000000�����:32
 �Ĵ���˵��: RC�����Ĵ���2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nfl_bpg_offset   : 16; /* bit[0-15] : �޷���С������11 bitsΪС��λ
                                                            Specifies the number of bits (including fractional bits) that are de-allocated for each group, for groups after the first line of a slice. */
        unsigned int  slice_bpg_offset : 16; /* bit[16-31]: �޷���С������11 bitsΪС��λ */
    } reg;
} SOC_DSS_DSC_RC_PARAM2_UNION;
#endif
#define SOC_DSS_DSC_RC_PARAM2_nfl_bpg_offset_START    (0)
#define SOC_DSS_DSC_RC_PARAM2_nfl_bpg_offset_END      (15)
#define SOC_DSS_DSC_RC_PARAM2_slice_bpg_offset_START  (16)
#define SOC_DSS_DSC_RC_PARAM2_slice_bpg_offset_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_RC_PARAM3_UNION
 �ṹ˵��  : RC_PARAM3 �Ĵ����ṹ���塣��ַƫ����:0x002C����ֵ:0x00001800�����:32
 �Ĵ���˵��: RC�����Ĵ���3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  initial_offset : 16; /* bit[0-15] : �޷�������
                                                          Specifies the initial value for rcXformOffset, which is initial_offset - rc_model_size at the start of a slice */
        unsigned int  final_offset   : 16; /* bit[16-31]: �޷�������
                                                          Specifies the maximum end-of-slice value for rcXformOffset, which is final_offset - rc_model_size */
    } reg;
} SOC_DSS_DSC_RC_PARAM3_UNION;
#endif
#define SOC_DSS_DSC_RC_PARAM3_initial_offset_START  (0)
#define SOC_DSS_DSC_RC_PARAM3_initial_offset_END    (15)
#define SOC_DSS_DSC_RC_PARAM3_final_offset_START    (16)
#define SOC_DSS_DSC_RC_PARAM3_final_offset_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_FLATNESS_QP_TH_UNION
 �ṹ˵��  : FLATNESS_QP_TH �Ĵ����ṹ���塣��ַƫ����:0x0030����ֵ:0x000C0003�����:32
 �Ĵ���˵��: flatness QP��ֵ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flatness_min_qp : 8;  /* bit[0-7]  : �޷�������
                                                           Specifies the minimum QP at which flatness is signaled and the flatness QP adjustment is made. */
        unsigned int  reserved_0      : 8;  /* bit[8-15] :  */
        unsigned int  flatness_max_qp : 8;  /* bit[16-23]: �޷�������
                                                           Specifies the maximum QP at which flatness is signaled and the flatness QP adjustment is made. */
        unsigned int  reserved_1      : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_DSC_FLATNESS_QP_TH_UNION;
#endif
#define SOC_DSS_DSC_FLATNESS_QP_TH_flatness_min_qp_START  (0)
#define SOC_DSS_DSC_FLATNESS_QP_TH_flatness_min_qp_END    (7)
#define SOC_DSS_DSC_FLATNESS_QP_TH_flatness_max_qp_START  (16)
#define SOC_DSS_DSC_FLATNESS_QP_TH_flatness_max_qp_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_RC_PARAM4_UNION
 �ṹ˵��  : RC_PARAM4 �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x00602000�����:32
 �Ĵ���˵��: RC�����Ĵ���4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rc_model_size  : 16; /* bit[0-15] : �޷�������
                                                          Specifies the number of bits within the
                                                          ��RC model�� */
        unsigned int  reserved_0     : 4;  /* bit[16-19]: ���� */
        unsigned int  rc_edge_factor : 4;  /* bit[20-23]: �޷���С������1����λС��λ
                                                          Compared to the ratio of current activity vs. previous activity to determine the presence of an ��edge,�� which in turn determines whether the QP is incremented in the short-term RC */
        unsigned int  reserved_1     : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_DSC_RC_PARAM4_UNION;
#endif
#define SOC_DSS_DSC_RC_PARAM4_rc_model_size_START   (0)
#define SOC_DSS_DSC_RC_PARAM4_rc_model_size_END     (15)
#define SOC_DSS_DSC_RC_PARAM4_rc_edge_factor_START  (20)
#define SOC_DSS_DSC_RC_PARAM4_rc_edge_factor_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_RC_PARAM5_UNION
 �ṹ˵��  : RC_PARAM5 �Ĵ����ṹ���塣��ַƫ����:0x0038����ֵ:0x00330B0B�����:32
 �Ĵ���˵��: RC�����Ĵ���5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rc_quant_incr_limit0 : 5;  /* bit[0-4]  : �޷�������
                                                                QP threshold that is used in the short-term RC */
        unsigned int  reserved_0           : 3;  /* bit[5-7]  : ���� */
        unsigned int  rc_quant_incr_limit1 : 5;  /* bit[8-12] : �޷�������
                                                                QP threshold that is used in the short-term RC */
        unsigned int  reserved_1           : 3;  /* bit[13-15]: ���� */
        unsigned int  rc_tgt_offset_hi     : 4;  /* bit[16-19]: �޷�������
                                                                Specifies the upper end of the variability range around the target bits per group that is allowed by the short-term RC */
        unsigned int  rc_tgt_offset_lo     : 4;  /* bit[20-23]: �޷�������
                                                                Specifies the lower end of the variability range around the target bits per group that is allowed by the short-term RC */
        unsigned int  reserved_2           : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_DSC_RC_PARAM5_UNION;
#endif
#define SOC_DSS_DSC_RC_PARAM5_rc_quant_incr_limit0_START  (0)
#define SOC_DSS_DSC_RC_PARAM5_rc_quant_incr_limit0_END    (4)
#define SOC_DSS_DSC_RC_PARAM5_rc_quant_incr_limit1_START  (8)
#define SOC_DSS_DSC_RC_PARAM5_rc_quant_incr_limit1_END    (12)
#define SOC_DSS_DSC_RC_PARAM5_rc_tgt_offset_hi_START      (16)
#define SOC_DSS_DSC_RC_PARAM5_rc_tgt_offset_hi_END        (19)
#define SOC_DSS_DSC_RC_PARAM5_rc_tgt_offset_lo_START      (20)
#define SOC_DSS_DSC_RC_PARAM5_rc_tgt_offset_lo_END        (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_RC_BUF_THRESH0_UNION
 �ṹ˵��  : RC_BUF_THRESH0 �Ĵ����ṹ���塣��ַƫ����:0x003C����ֵ:0x0E1C2A38�����:32
 �Ĵ���˵��: fullness��ֵ�Ĵ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rc_buf_thresh3 : 8;  /* bit[0-7]  : �޷�������
                                                          �˼Ĵ�������6bit�õ�ʵ�ʵ���ֵ������long-term RC���� */
        unsigned int  rc_buf_thresh2 : 8;  /* bit[8-15] : �޷�������
                                                          �˼Ĵ�������6bit�õ�ʵ�ʵ���ֵ������long-term RC���� */
        unsigned int  rc_buf_thresh1 : 8;  /* bit[16-23]: �޷�������
                                                          �˼Ĵ�������6bit�õ�ʵ�ʵ���ֵ������long-term RC���� */
        unsigned int  rc_buf_thresh0 : 8;  /* bit[24-31]: �޷�������
                                                          �˼Ĵ�������6bit�õ�ʵ�ʵ���ֵ������long-term RC���� */
    } reg;
} SOC_DSS_DSC_RC_BUF_THRESH0_UNION;
#endif
#define SOC_DSS_DSC_RC_BUF_THRESH0_rc_buf_thresh3_START  (0)
#define SOC_DSS_DSC_RC_BUF_THRESH0_rc_buf_thresh3_END    (7)
#define SOC_DSS_DSC_RC_BUF_THRESH0_rc_buf_thresh2_START  (8)
#define SOC_DSS_DSC_RC_BUF_THRESH0_rc_buf_thresh2_END    (15)
#define SOC_DSS_DSC_RC_BUF_THRESH0_rc_buf_thresh1_START  (16)
#define SOC_DSS_DSC_RC_BUF_THRESH0_rc_buf_thresh1_END    (23)
#define SOC_DSS_DSC_RC_BUF_THRESH0_rc_buf_thresh0_START  (24)
#define SOC_DSS_DSC_RC_BUF_THRESH0_rc_buf_thresh0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_RC_BUF_THRESH1_UNION
 �ṹ˵��  : RC_BUF_THRESH1 �Ĵ����ṹ���塣��ַƫ����:0x0040����ֵ:0x46546269�����:32
 �Ĵ���˵��: fullness��ֵ�Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rc_buf_thresh7 : 8;  /* bit[0-7]  : �޷�������
                                                          �˼Ĵ�������6bit�õ�ʵ�ʵ���ֵ������long-term RC���� */
        unsigned int  rc_buf_thresh6 : 8;  /* bit[8-15] : �޷�������
                                                          �˼Ĵ�������6bit�õ�ʵ�ʵ���ֵ������long-term RC���� */
        unsigned int  rc_buf_thresh5 : 8;  /* bit[16-23]: �޷�������
                                                          �˼Ĵ�������6bit�õ�ʵ�ʵ���ֵ������long-term RC���� */
        unsigned int  rc_buf_thresh4 : 8;  /* bit[24-31]: �޷�������
                                                          �˼Ĵ�������6bit�õ�ʵ�ʵ���ֵ������long-term RC���� */
    } reg;
} SOC_DSS_DSC_RC_BUF_THRESH1_UNION;
#endif
#define SOC_DSS_DSC_RC_BUF_THRESH1_rc_buf_thresh7_START  (0)
#define SOC_DSS_DSC_RC_BUF_THRESH1_rc_buf_thresh7_END    (7)
#define SOC_DSS_DSC_RC_BUF_THRESH1_rc_buf_thresh6_START  (8)
#define SOC_DSS_DSC_RC_BUF_THRESH1_rc_buf_thresh6_END    (15)
#define SOC_DSS_DSC_RC_BUF_THRESH1_rc_buf_thresh5_START  (16)
#define SOC_DSS_DSC_RC_BUF_THRESH1_rc_buf_thresh5_END    (23)
#define SOC_DSS_DSC_RC_BUF_THRESH1_rc_buf_thresh4_START  (24)
#define SOC_DSS_DSC_RC_BUF_THRESH1_rc_buf_thresh4_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_RC_BUF_THRESH2_UNION
 �ṹ˵��  : RC_BUF_THRESH2 �Ĵ����ṹ���塣��ַƫ����:0x0044����ֵ:0x7077797B�����:32
 �Ĵ���˵��: fullness��ֵ�Ĵ���2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rc_buf_thresh11 : 8;  /* bit[0-7]  : �޷�������
                                                           �˼Ĵ�������6bit�õ�ʵ�ʵ���ֵ������long-term RC���� */
        unsigned int  rc_buf_thresh10 : 8;  /* bit[8-15] : �޷�������
                                                           �˼Ĵ�������6bit�õ�ʵ�ʵ���ֵ������long-term RC���� */
        unsigned int  rc_buf_thresh9  : 8;  /* bit[16-23]: �޷�������
                                                           �˼Ĵ�������6bit�õ�ʵ�ʵ���ֵ������long-term RC���� */
        unsigned int  rc_buf_thresh8  : 8;  /* bit[24-31]: �޷�������
                                                           �˼Ĵ�������6bit�õ�ʵ�ʵ���ֵ������long-term RC���� */
    } reg;
} SOC_DSS_DSC_RC_BUF_THRESH2_UNION;
#endif
#define SOC_DSS_DSC_RC_BUF_THRESH2_rc_buf_thresh11_START  (0)
#define SOC_DSS_DSC_RC_BUF_THRESH2_rc_buf_thresh11_END    (7)
#define SOC_DSS_DSC_RC_BUF_THRESH2_rc_buf_thresh10_START  (8)
#define SOC_DSS_DSC_RC_BUF_THRESH2_rc_buf_thresh10_END    (15)
#define SOC_DSS_DSC_RC_BUF_THRESH2_rc_buf_thresh9_START   (16)
#define SOC_DSS_DSC_RC_BUF_THRESH2_rc_buf_thresh9_END     (23)
#define SOC_DSS_DSC_RC_BUF_THRESH2_rc_buf_thresh8_START   (24)
#define SOC_DSS_DSC_RC_BUF_THRESH2_rc_buf_thresh8_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_RC_BUF_THRESH3_UNION
 �ṹ˵��  : RC_BUF_THRESH3 �Ĵ����ṹ���塣��ַƫ����:0x0048����ֵ:0x7D7E0000�����:32
 �Ĵ���˵��: fullness��ֵ�Ĵ���3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved        : 16; /* bit[0-15] : ���� */
        unsigned int  rc_buf_thresh13 : 8;  /* bit[16-23]: �޷�������
                                                           �˼Ĵ�������6bit�õ�ʵ�ʵ���ֵ������long-term RC���� */
        unsigned int  rc_buf_thresh12 : 8;  /* bit[24-31]: �޷�������
                                                           �˼Ĵ�������6bit�õ�ʵ�ʵ���ֵ������long-term RC���� */
    } reg;
} SOC_DSS_DSC_RC_BUF_THRESH3_UNION;
#endif
#define SOC_DSS_DSC_RC_BUF_THRESH3_rc_buf_thresh13_START  (16)
#define SOC_DSS_DSC_RC_BUF_THRESH3_rc_buf_thresh13_END    (23)
#define SOC_DSS_DSC_RC_BUF_THRESH3_rc_buf_thresh12_START  (24)
#define SOC_DSS_DSC_RC_BUF_THRESH3_rc_buf_thresh12_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_RC_RANGE_PARAM0_UNION
 �ṹ˵��  : RC_RANGE_PARAM0 �Ĵ����ṹ���塣��ַƫ����:0x004C����ֵ:0x01020100�����:32
 �Ĵ���˵��: RC_RANGE�����Ĵ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  range_bpg_offset1 : 6;  /* bit[0-5]  : long-rc rangeΪ1ʱ��range����
                                                             �з����� */
        unsigned int  range_max_qp1     : 5;  /* bit[6-10] : long-rc rangeΪ1ʱ��range����
                                                             �޷����� */
        unsigned int  range_min_qp1     : 5;  /* bit[11-15]: long-rc rangeΪ1ʱ��range����
                                                             �޷����� */
        unsigned int  range_bpg_offset0 : 6;  /* bit[16-21]: long-rc rangeΪ0ʱ��range����
                                                             �з����� */
        unsigned int  range_max_qp0     : 5;  /* bit[22-26]: long-rc rangeΪ0ʱ��range����
                                                             �޷����� */
        unsigned int  range_min_qp0     : 5;  /* bit[27-31]: long-rc rangeΪ0ʱ��range����
                                                             �޷����� */
    } reg;
} SOC_DSS_DSC_RC_RANGE_PARAM0_UNION;
#endif
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_bpg_offset1_START  (0)
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_bpg_offset1_END    (5)
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_max_qp1_START      (6)
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_max_qp1_END        (10)
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_min_qp1_START      (11)
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_min_qp1_END        (15)
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_bpg_offset0_START  (16)
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_bpg_offset0_END    (21)
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_max_qp0_START      (22)
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_max_qp0_END        (26)
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_min_qp0_START      (27)
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_min_qp0_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_RC_RANGE_PARAM1_UNION
 �ṹ˵��  : RC_RANGE_PARAM1 �Ĵ����ṹ���塣��ַƫ����:0x0050����ֵ:0x094009BE�����:32
 �Ĵ���˵��: RC_RANGE�����Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  range_bpg_offset3 : 6;  /* bit[0-5]  : long-rc rangeΪ3ʱ��range����
                                                             �з����� */
        unsigned int  range_max_qp3     : 5;  /* bit[6-10] : long-rc rangeΪ3ʱ��range����
                                                             �޷����� */
        unsigned int  range_min_qp3     : 5;  /* bit[11-15]: long-rc rangeΪ3ʱ��range����
                                                             �޷����� */
        unsigned int  range_bpg_offset2 : 6;  /* bit[16-21]: long-rc rangeΪ2ʱ��range����
                                                             �з����� */
        unsigned int  range_max_qp2     : 5;  /* bit[22-26]: long-rc rangeΪ2ʱ��range����
                                                             �޷����� */
        unsigned int  range_min_qp2     : 5;  /* bit[27-31]: long-rc rangeΪ2ʱ��range����
                                                             �޷����� */
    } reg;
} SOC_DSS_DSC_RC_RANGE_PARAM1_UNION;
#endif
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_bpg_offset3_START  (0)
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_bpg_offset3_END    (5)
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_max_qp3_START      (6)
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_max_qp3_END        (10)
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_min_qp3_START      (11)
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_min_qp3_END        (15)
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_bpg_offset2_START  (16)
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_bpg_offset2_END    (21)
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_max_qp2_START      (22)
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_max_qp2_END        (26)
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_min_qp2_START      (27)
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_min_qp2_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_RC_RANGE_PARAM2_UNION
 �ṹ˵��  : RC_RANGE_PARAM2 �Ĵ����ṹ���塣��ַƫ����:0x0054����ֵ:0x19FC19FA�����:32
 �Ĵ���˵��: RC_RANGE�����Ĵ���2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  range_bpg_offset5 : 6;  /* bit[0-5]  : long-rc rangeΪ5ʱ��range����
                                                             �з����� */
        unsigned int  range_max_qp5     : 5;  /* bit[6-10] : long-rc rangeΪ5ʱ��range����
                                                             �޷����� */
        unsigned int  range_min_qp5     : 5;  /* bit[11-15]: long-rc rangeΪ5ʱ��range����
                                                             �޷����� */
        unsigned int  range_bpg_offset4 : 6;  /* bit[16-21]: long-rc rangeΪ4ʱ��range����
                                                             �з����� */
        unsigned int  range_max_qp4     : 5;  /* bit[22-26]: long-rc rangeΪ4ʱ��range����
                                                             �޷����� */
        unsigned int  range_min_qp4     : 5;  /* bit[27-31]: long-rc rangeΪ4ʱ��range����
                                                             �޷����� */
    } reg;
} SOC_DSS_DSC_RC_RANGE_PARAM2_UNION;
#endif
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_bpg_offset5_START  (0)
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_bpg_offset5_END    (5)
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_max_qp5_START      (6)
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_max_qp5_END        (10)
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_min_qp5_START      (11)
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_min_qp5_END        (15)
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_bpg_offset4_START  (16)
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_bpg_offset4_END    (21)
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_max_qp4_START      (22)
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_max_qp4_END        (26)
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_min_qp4_START      (27)
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_min_qp4_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_RC_RANGE_PARAM3_UNION
 �ṹ˵��  : RC_RANGE_PARAM3 �Ĵ����ṹ���塣��ַƫ����:0x0058����ֵ:0x19F81A38�����:32
 �Ĵ���˵��: RC_RANGE�����Ĵ���3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  range_bpg_offset7 : 6;  /* bit[0-5]  : long-rc rangeΪ7ʱ��range����
                                                             �з����� */
        unsigned int  range_max_qp7     : 5;  /* bit[6-10] : long-rc rangeΪ7ʱ��range����
                                                             �޷����� */
        unsigned int  range_min_qp7     : 5;  /* bit[11-15]: long-rc rangeΪ7ʱ��range����
                                                             �޷����� */
        unsigned int  range_bpg_offset6 : 6;  /* bit[16-21]: long-rc rangeΪ6ʱ��range����
                                                             �з����� */
        unsigned int  range_max_qp6     : 5;  /* bit[22-26]: long-rc rangeΪ6ʱ��range����
                                                             �޷����� */
        unsigned int  range_min_qp6     : 5;  /* bit[27-31]: long-rc rangeΪ6ʱ��range����
                                                             �޷����� */
    } reg;
} SOC_DSS_DSC_RC_RANGE_PARAM3_UNION;
#endif
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_bpg_offset7_START  (0)
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_bpg_offset7_END    (5)
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_max_qp7_START      (6)
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_max_qp7_END        (10)
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_min_qp7_START      (11)
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_min_qp7_END        (15)
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_bpg_offset6_START  (16)
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_bpg_offset6_END    (21)
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_max_qp6_START      (22)
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_max_qp6_END        (26)
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_min_qp6_START      (27)
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_min_qp6_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_RC_RANGE_PARAM4_UNION
 �ṹ˵��  : RC_RANGE_PARAM4 �Ĵ����ṹ���塣��ַƫ����:0x005C����ֵ:0x1A781AB6�����:32
 �Ĵ���˵��: RC_RANGE�����Ĵ���4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  range_bpg_offset9 : 6;  /* bit[0-5]  : long-rc rangeΪ9ʱ��range����
                                                             �з����� */
        unsigned int  range_max_qp9     : 5;  /* bit[6-10] : long-rc rangeΪ9ʱ��range����
                                                             �޷����� */
        unsigned int  range_min_qp9     : 5;  /* bit[11-15]: long-rc rangeΪ9ʱ��range����
                                                             �޷����� */
        unsigned int  range_bpg_offset8 : 6;  /* bit[16-21]: long-rc rangeΪ8ʱ��range����
                                                             �з����� */
        unsigned int  range_max_qp8     : 5;  /* bit[22-26]: long-rc rangeΪ8ʱ��range����
                                                             �޷����� */
        unsigned int  range_min_qp8     : 5;  /* bit[27-31]: long-rc rangeΪ8ʱ��range����
                                                             �޷����� */
    } reg;
} SOC_DSS_DSC_RC_RANGE_PARAM4_UNION;
#endif
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_bpg_offset9_START  (0)
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_bpg_offset9_END    (5)
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_max_qp9_START      (6)
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_max_qp9_END        (10)
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_min_qp9_START      (11)
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_min_qp9_END        (15)
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_bpg_offset8_START  (16)
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_bpg_offset8_END    (21)
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_max_qp8_START      (22)
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_max_qp8_END        (26)
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_min_qp8_START      (27)
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_min_qp8_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_RC_RANGE_PARAM5_UNION
 �ṹ˵��  : RC_RANGE_PARAM5 �Ĵ����ṹ���塣��ַƫ����:0x0060����ֵ:0x2AF62B34�����:32
 �Ĵ���˵��: RC_RANGE�����Ĵ���5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  range_bpg_offset11 : 6;  /* bit[0-5]  : long-rc rangeΪ11ʱ��range����
                                                              �з����� */
        unsigned int  range_max_qp11     : 5;  /* bit[6-10] : long-rc rangeΪ11ʱ��range����
                                                              �޷����� */
        unsigned int  range_min_qp11     : 5;  /* bit[11-15]: long-rc rangeΪ11ʱ��range����
                                                              �޷����� */
        unsigned int  range_bpg_offset10 : 6;  /* bit[16-21]: long-rc rangeΪ10ʱ��range����
                                                              �з����� */
        unsigned int  range_max_qp10     : 5;  /* bit[22-26]: long-rc rangeΪ10ʱ��range����
                                                              �޷����� */
        unsigned int  range_min_qp10     : 5;  /* bit[27-31]: long-rc rangeΪ10ʱ��range����
                                                              �޷����� */
    } reg;
} SOC_DSS_DSC_RC_RANGE_PARAM5_UNION;
#endif
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_bpg_offset11_START  (0)
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_bpg_offset11_END    (5)
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_max_qp11_START      (6)
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_max_qp11_END        (10)
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_min_qp11_START      (11)
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_min_qp11_END        (15)
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_bpg_offset10_START  (16)
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_bpg_offset10_END    (21)
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_max_qp10_START      (22)
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_max_qp10_END        (26)
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_min_qp10_START      (27)
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_min_qp10_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_RC_RANGE_PARAM6_UNION
 �ṹ˵��  : RC_RANGE_PARAM6 �Ĵ����ṹ���塣��ַƫ����:0x0064����ֵ:0x2B743B74�����:32
 �Ĵ���˵��: RC_RANGE�����Ĵ���6
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  range_bpg_offset13 : 6;  /* bit[0-5]  : long-rc rangeΪ13ʱ��range����
                                                              �з����� */
        unsigned int  range_max_qp13     : 5;  /* bit[6-10] : long-rc rangeΪ13ʱ��range����
                                                              �޷����� */
        unsigned int  range_min_qp13     : 5;  /* bit[11-15]: long-rc rangeΪ13ʱ��range����
                                                              �޷����� */
        unsigned int  range_bpg_offset12 : 6;  /* bit[16-21]: long-rc rangeΪ12ʱ��range����
                                                              �з����� */
        unsigned int  range_max_qp12     : 5;  /* bit[22-26]: long-rc rangeΪ12ʱ��range����
                                                              �޷����� */
        unsigned int  range_min_qp12     : 5;  /* bit[27-31]: long-rc rangeΪ12ʱ��range����
                                                              �޷����� */
    } reg;
} SOC_DSS_DSC_RC_RANGE_PARAM6_UNION;
#endif
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_bpg_offset13_START  (0)
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_bpg_offset13_END    (5)
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_max_qp13_START      (6)
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_max_qp13_END        (10)
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_min_qp13_START      (11)
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_min_qp13_END        (15)
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_bpg_offset12_START  (16)
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_bpg_offset12_END    (21)
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_max_qp12_START      (22)
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_max_qp12_END        (26)
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_min_qp12_START      (27)
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_min_qp12_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_RC_RANGE_PARAM7_UNION
 �ṹ˵��  : RC_RANGE_PARAM7 �Ĵ����ṹ���塣��ַƫ����:0x0068����ֵ:0x6BF40000�����:32
 �Ĵ���˵��: RC_RANGE�����Ĵ���7
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved           : 16; /* bit[0-15] : ���� */
        unsigned int  range_bpg_offset14 : 6;  /* bit[16-21]: long-rc rangeΪ14ʱ��range����
                                                              �з����� */
        unsigned int  range_max_qp14     : 5;  /* bit[22-26]: long-rc rangeΪ14ʱ��range����
                                                              �޷����� */
        unsigned int  range_min_qp14     : 5;  /* bit[27-31]: long-rc rangeΪ14ʱ��range����
                                                              �޷����� */
    } reg;
} SOC_DSS_DSC_RC_RANGE_PARAM7_UNION;
#endif
#define SOC_DSS_DSC_RC_RANGE_PARAM7_range_bpg_offset14_START  (16)
#define SOC_DSS_DSC_RC_RANGE_PARAM7_range_bpg_offset14_END    (21)
#define SOC_DSS_DSC_RC_RANGE_PARAM7_range_max_qp14_START      (22)
#define SOC_DSS_DSC_RC_RANGE_PARAM7_range_max_qp14_END        (26)
#define SOC_DSS_DSC_RC_RANGE_PARAM7_range_min_qp14_START      (27)
#define SOC_DSS_DSC_RC_RANGE_PARAM7_range_min_qp14_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_ADJUSTMENT_BITS_UNION
 �ṹ˵��  : ADJUSTMENT_BITS �Ĵ����ṹ���塣��ַƫ����:0x006C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ADJUSTMENT_BITS�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  adjustment_bits : 4;  /* bit[0-3] : ADJUSTMENT_BITS�Ĵ���
                                                          adjustment_bitsʹ�ñ�����һ�е�bit��Ϊbyte��������
                                                          ����ֵ = 
                                                          ��8-(bits_per_pixel * slice_hsize) % 8��% 8
                                                          ȡֵ��ΧΪ0-7 */
        unsigned int  reserved        : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_DSS_DSC_ADJUSTMENT_BITS_UNION;
#endif
#define SOC_DSS_DSC_ADJUSTMENT_BITS_adjustment_bits_START  (0)
#define SOC_DSS_DSC_ADJUSTMENT_BITS_adjustment_bits_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_BITS_PER_GRP_UNION
 �ṹ˵��  : BITS_PER_GRP �Ĵ����ṹ���塣��ַƫ����:0x0070����ֵ:0x00001518�����:32
 �Ĵ���˵��: group����ߴ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bits_per_grp     : 6;  /* bit[0-5]  : ÿ��group������bit��
                                                            ����ֵ=ceil��bits_per_pixel * 3�� */
        unsigned int  reserved_0       : 2;  /* bit[6-7]  : ���� */
        unsigned int  adj_bits_per_grp : 6;  /* bit[8-13] : ����ֵ=bits_per_pixel * 3 - 3 */
        unsigned int  reserved_1       : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_DSS_DSC_BITS_PER_GRP_UNION;
#endif
#define SOC_DSS_DSC_BITS_PER_GRP_bits_per_grp_START      (0)
#define SOC_DSS_DSC_BITS_PER_GRP_bits_per_grp_END        (5)
#define SOC_DSS_DSC_BITS_PER_GRP_adj_bits_per_grp_START  (8)
#define SOC_DSS_DSC_BITS_PER_GRP_adj_bits_per_grp_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_MULTI_SLICE_CTL_UNION
 �ṹ˵��  : MULTI_SLICE_CTL �Ĵ����ṹ���塣��ַƫ����:0x0074����ֵ:0x00000000�����:32
 �Ĵ���˵��: multi_slice���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  slices_per_line  : 2;  /* bit[0-1]  : ÿ�е�slice��Ŀ
                                                            2'b00: 1 slice per line
                                                            2'b01: 2 slices per line
                                                            2'b1x: reserved
                                                            ��pic_width > slice_widthʱ��slices_per_line=1������slices_per_line=0 */
        unsigned int  reserved         : 14; /* bit[2-15] : ���� */
        unsigned int  pic_line_grp_num : 16; /* bit[16-31]: pic_line_grp_num = (slice_width+3)/3*slices_per_line-1
                                                            ע���˴�slice_widthΪʵ��ֵ��1 */
    } reg;
} SOC_DSS_DSC_MULTI_SLICE_CTL_UNION;
#endif
#define SOC_DSS_DSC_MULTI_SLICE_CTL_slices_per_line_START   (0)
#define SOC_DSS_DSC_MULTI_SLICE_CTL_slices_per_line_END     (1)
#define SOC_DSS_DSC_MULTI_SLICE_CTL_pic_line_grp_num_START  (16)
#define SOC_DSS_DSC_MULTI_SLICE_CTL_pic_line_grp_num_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_DSC_OUT_CTRL_UNION
 �ṹ˵��  : DSC_OUT_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0078����ֵ:0x00000000�����:32
 �Ĵ���˵��: DSC������ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc_out_mode : 1;  /* bit[0]   : 0: 24bit���ģʽ��
                                                       1: 16bit���ģʽ��
                                                       24bit���ģʽʱ��DSC�����24bitȫ����Ч��
                                                       16bit���ģʽʱ��DSC�����24bit�е�16bit��Ч��
                                                       ��chunk_size%3==0ʱ��dsc_out_mode=0������dsc_out_mode=1. */
        unsigned int  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_DSC_DSC_OUT_CTRL_UNION;
#endif
#define SOC_DSS_DSC_DSC_OUT_CTRL_dsc_out_mode_START  (0)
#define SOC_DSS_DSC_DSC_OUT_CTRL_dsc_out_mode_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_DSC_CLK_SEL_UNION
 �ṹ˵��  : DSC_CLK_SEL �Ĵ����ṹ���塣��ַƫ����:0x007C����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: һ��ģ��ʱ��ѡ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc_clk_sel : 32; /* bit[0-31]: ��һ��ģ���ʱ��ѡ���źţ�
                                                      1����ʾǿ�ƴ�ʱ�ӡ�
                                                      0����ʾ��Ҫ���������Ӳ����ʱ��ʹ����������ر�ʱ��
                                                      [31:3]: ����
                                                      [2]: DSC_IFʱ�ӿ��ƼĴ���
                                                      [1]: DSC1ʱ�ӿ��ƼĴ�����
                                                      [0]: DSC0ʱ�ӿ��ƼĴ����� */
    } reg;
} SOC_DSS_DSC_DSC_CLK_SEL_UNION;
#endif
#define SOC_DSS_DSC_DSC_CLK_SEL_dsc_clk_sel_START  (0)
#define SOC_DSS_DSC_DSC_CLK_SEL_dsc_clk_sel_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_DSC_CLK_EN_UNION
 �ṹ˵��  : DSC_CLK_EN �Ĵ����ṹ���塣��ַƫ����:0x0080����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: һ��ģ��ʱ��ʹ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc_clk_en : 32; /* bit[0-31]: ��һ��ģ������ʱ��ʹ���ź�
                                                     1����ʾ���ʱ��ʹ����Ч������Ӳ������
                                                     0����ʾ���ʱ��ʹ����Ч����ֹӲ������
                                                     [31:3]: ����
                                                     [2]: DSC_IFʱ�ӿ��ƼĴ���
                                                     [1]: DSC1ʱ�ӿ��ƼĴ�����
                                                     [0]: DSC0ʱ�ӿ��ƼĴ����� */
    } reg;
} SOC_DSS_DSC_DSC_CLK_EN_UNION;
#endif
#define SOC_DSS_DSC_DSC_CLK_EN_dsc_clk_en_START  (0)
#define SOC_DSS_DSC_DSC_CLK_EN_dsc_clk_en_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_DSC_MEM_CTRL_UNION
 �ṹ˵��  : DSC_MEM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0084����ֵ:0x00000000�����:32
 �Ĵ���˵��: DSC memory�͹��Ŀ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc_mem_ctrl_0 : 4;  /* bit[0-3]  : DSC0 memory�͹��Ŀ��ƼĴ���
                                                          [3] mem_ctrl_auto_en , �Զ�ģʽ���������ģʽѡ��,0�Զ�ģʽ��1�������ģʽ 
                                                          [2]: �������ģʽ����Ч��Ϊ1��ʾ����Shut Downģʽ
                                                          [1]: �������ģʽ����Ч��Ϊ1��ʾ����Deep Sleepģʽ
                                                          [0]: �������ģʽ����Ч��Ϊ1��ʾ����Sleepģʽ */
        unsigned int  dsc_mem_ctrl_1 : 4;  /* bit[4-7]  : DSC1 memory�͹��Ŀ��ƼĴ����������غ���ͬ[3:0] */
        unsigned int  dsc_mem_ctrl_2 : 4;  /* bit[8-11] : DSC_IF line buffer�͹��Ŀ��ƼĴ����������غ���ͬ[3:0] */
        unsigned int  dsc_mem_ctrl_3 : 4;  /* bit[12-15]: ���� */
        unsigned int  dsc_mem_ctrl_4 : 4;  /* bit[16-19]: ���� */
        unsigned int  dsc_mem_ctrl_5 : 4;  /* bit[20-23]: ���� */
        unsigned int  dsc_mem_ctrl_6 : 4;  /* bit[24-27]: ���� */
        unsigned int  dsc_mem_ctrl_7 : 4;  /* bit[28-31]: ���� */
    } reg;
} SOC_DSS_DSC_DSC_MEM_CTRL_UNION;
#endif
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_0_START  (0)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_0_END    (3)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_1_START  (4)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_1_END    (7)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_2_START  (8)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_2_END    (11)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_3_START  (12)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_3_END    (15)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_4_START  (16)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_4_END    (19)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_5_START  (20)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_5_END    (23)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_6_START  (24)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_6_END    (27)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_7_START  (28)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_7_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_DSC_ST_DATAIN_UNION
 �ṹ˵��  : DSC_ST_DATAIN �Ĵ����ṹ���塣��ַƫ����:0x0088����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  datain_line_cnt : 12; /* bit[0-11] : ������������λ��״̬�Ĵ��� */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: ���� */
        unsigned int  datain_pix_cnt  : 12; /* bit[16-27]: �������غ���λ��״̬�Ĵ��� */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: ���� */
    } reg;
} SOC_DSS_DSC_DSC_ST_DATAIN_UNION;
#endif
#define SOC_DSS_DSC_DSC_ST_DATAIN_datain_line_cnt_START  (0)
#define SOC_DSS_DSC_DSC_ST_DATAIN_datain_line_cnt_END    (11)
#define SOC_DSS_DSC_DSC_ST_DATAIN_datain_pix_cnt_START   (16)
#define SOC_DSS_DSC_DSC_ST_DATAIN_datain_pix_cnt_END     (27)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_DSC_ST_DATAOUT_UNION
 �ṹ˵��  : DSC_ST_DATAOUT �Ĵ����ṹ���塣��ַƫ����:0x008C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dataout_line_cnt : 12; /* bit[0-11] : �����������λ��״̬�Ĵ��� */
        unsigned int  reserved         : 4;  /* bit[12-15]: ���� */
        unsigned int  dataout_byte_cnt : 16; /* bit[16-31]: ���byte��״̬�Ĵ��� */
    } reg;
} SOC_DSS_DSC_DSC_ST_DATAOUT_UNION;
#endif
#define SOC_DSS_DSC_DSC_ST_DATAOUT_dataout_line_cnt_START  (0)
#define SOC_DSS_DSC_DSC_ST_DATAOUT_dataout_line_cnt_END    (11)
#define SOC_DSS_DSC_DSC_ST_DATAOUT_dataout_byte_cnt_START  (16)
#define SOC_DSS_DSC_DSC_ST_DATAOUT_dataout_byte_cnt_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_DSC0_ST_SLC_POS_UNION
 �ṹ˵��  : DSC0_ST_SLC_POS �Ĵ����ṹ���塣��ַƫ����:0x0090����ֵ:0x00000000�����:32
 �Ĵ���˵��: SLICEλ��״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc0_slice_line_cnt : 12; /* bit[0-11] : dsc0 slice����λ��״̬�Ĵ���
                                                               ��dsc0��ǰ���������λ������slice������λ�� */
        unsigned int  reserved_0          : 4;  /* bit[12-15]: ���� */
        unsigned int  dsc0_slice_pix_cnt  : 12; /* bit[16-27]: dsc0 slice����λ��״̬�Ĵ���
                                                               ��dsc0��ǰ���������λ������slice�ĺ���λ�� */
        unsigned int  reserved_1          : 4;  /* bit[28-31]: ���� */
    } reg;
} SOC_DSS_DSC_DSC0_ST_SLC_POS_UNION;
#endif
#define SOC_DSS_DSC_DSC0_ST_SLC_POS_dsc0_slice_line_cnt_START  (0)
#define SOC_DSS_DSC_DSC0_ST_SLC_POS_dsc0_slice_line_cnt_END    (11)
#define SOC_DSS_DSC_DSC0_ST_SLC_POS_dsc0_slice_pix_cnt_START   (16)
#define SOC_DSS_DSC_DSC0_ST_SLC_POS_dsc0_slice_pix_cnt_END     (27)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_DSC1_ST_SLC_POS_UNION
 �ṹ˵��  : DSC1_ST_SLC_POS �Ĵ����ṹ���塣��ַƫ����:0x0094����ֵ:0x00000000�����:32
 �Ĵ���˵��: SLICEλ��״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc1_slice_line_cnt : 12; /* bit[0-11] : dsc1 slice����λ��״̬�Ĵ���
                                                               ��dsc1��ǰ���������λ������slice������λ�� */
        unsigned int  reserved_0          : 4;  /* bit[12-15]: ���� */
        unsigned int  dsc1_slice_pix_cnt  : 12; /* bit[16-27]: dsc1 slice����λ��״̬�Ĵ���
                                                               ��dsc1��ǰ���������λ������slice�ĺ���λ�� */
        unsigned int  reserved_1          : 4;  /* bit[28-31]: ���� */
    } reg;
} SOC_DSS_DSC_DSC1_ST_SLC_POS_UNION;
#endif
#define SOC_DSS_DSC_DSC1_ST_SLC_POS_dsc1_slice_line_cnt_START  (0)
#define SOC_DSS_DSC_DSC1_ST_SLC_POS_dsc1_slice_line_cnt_END    (11)
#define SOC_DSS_DSC_DSC1_ST_SLC_POS_dsc1_slice_pix_cnt_START   (16)
#define SOC_DSS_DSC_DSC1_ST_SLC_POS_dsc1_slice_pix_cnt_END     (27)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_DSC0_ST_PIC_POS_UNION
 �ṹ˵��  : DSC0_ST_PIC_POS �Ĵ����ṹ���塣��ַƫ����:0x0098����ֵ:0x00000000�����:32
 �Ĵ���˵��: PICTUREλ��״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc0_pic_line_cnt : 12; /* bit[0-11] : dsc0 picturee����λ��״̬�Ĵ���
                                                             ��dsc0��ǰ���������λ����֡�ĺ���λ�� */
        unsigned int  reserved_0        : 4;  /* bit[12-15]: ���� */
        unsigned int  dsc0_pic_pix_cnt  : 12; /* bit[16-27]: dsc0 picture����λ��״̬�Ĵ���
                                                             ��dsc0��ǰ���������λ����֡�ĺ���λ�� */
        unsigned int  reserved_1        : 4;  /* bit[28-31]: ���� */
    } reg;
} SOC_DSS_DSC_DSC0_ST_PIC_POS_UNION;
#endif
#define SOC_DSS_DSC_DSC0_ST_PIC_POS_dsc0_pic_line_cnt_START  (0)
#define SOC_DSS_DSC_DSC0_ST_PIC_POS_dsc0_pic_line_cnt_END    (11)
#define SOC_DSS_DSC_DSC0_ST_PIC_POS_dsc0_pic_pix_cnt_START   (16)
#define SOC_DSS_DSC_DSC0_ST_PIC_POS_dsc0_pic_pix_cnt_END     (27)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_DSC1_ST_PIC_POS_UNION
 �ṹ˵��  : DSC1_ST_PIC_POS �Ĵ����ṹ���塣��ַƫ����:0x009C����ֵ:0x00000000�����:32
 �Ĵ���˵��: PICTUREλ��״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc1_pic_line_cnt : 12; /* bit[0-11] : dsc1 picturee����λ��״̬�Ĵ���
                                                             ��dsc0��ǰ���������λ����֡�ĺ���λ�� */
        unsigned int  reserved_0        : 4;  /* bit[12-15]: ���� */
        unsigned int  dsc1_pic_pix_cnt  : 12; /* bit[16-27]: dsc1 picture����λ��״̬�Ĵ���
                                                             ��dsc0��ǰ���������λ����֡�ĺ���λ�� */
        unsigned int  reserved_1        : 4;  /* bit[28-31]: ���� */
    } reg;
} SOC_DSS_DSC_DSC1_ST_PIC_POS_UNION;
#endif
#define SOC_DSS_DSC_DSC1_ST_PIC_POS_dsc1_pic_line_cnt_START  (0)
#define SOC_DSS_DSC_DSC1_ST_PIC_POS_dsc1_pic_line_cnt_END    (11)
#define SOC_DSS_DSC_DSC1_ST_PIC_POS_dsc1_pic_pix_cnt_START   (16)
#define SOC_DSS_DSC_DSC1_ST_PIC_POS_dsc1_pic_pix_cnt_END     (27)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_DSC0_ST_FIFO_UNION
 �ṹ˵��  : DSC0_ST_FIFO �Ĵ����ṹ���塣��ַƫ����:0x00A0����ֵ:0x00002AAA�����:32
 �Ĵ���˵��: FIFO����״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc0_flatff_full     : 1;  /* bit[0]    : dsc0 flat���fifo��ָʾ״̬�Ĵ��� */
        unsigned int  dsc0_flatff_empty    : 1;  /* bit[1]    : dsc0 flat���fifo��ָʾ״̬�Ĵ��� */
        unsigned int  dsc0_blncff0_full    : 1;  /* bit[2]    : dsc0 Y����balance fifo0��ָʾ�Ĵ��� */
        unsigned int  dsc0_blncff0_empty   : 1;  /* bit[3]    : dsc0 Y����balance fifo0��ָʾ�Ĵ��� */
        unsigned int  dsc0_blncff1_full    : 1;  /* bit[4]    : dsc0 Y����balance fifo1��ָʾ�Ĵ��� */
        unsigned int  dsc0_blncff1_empty   : 1;  /* bit[5]    : dsc0 Y����balance fifo1��ָʾ�Ĵ��� */
        unsigned int  dsc0_sesizeff0_full  : 1;  /* bit[6]    : dsc0 Y����syntax element size fifo0��ָʾ�Ĵ��� */
        unsigned int  dsc0_sesizeff0_empty : 1;  /* bit[7]    : dsc0 Y����syntax element size fifo0��ָʾ�Ĵ��� */
        unsigned int  dsc0_sesizeff1_full  : 1;  /* bit[8]    : dsc0 Y����syntax element size fifo1��ָʾ�Ĵ��� */
        unsigned int  dsc0_sesizeff1_empty : 1;  /* bit[9]    : dsc0 Y����syntax element size fifo1��ָʾ�Ĵ��� */
        unsigned int  dsc0_rcbuf0_full     : 1;  /* bit[10]   : dsc0 rc buffer0������ָʾ�Ĵ��� */
        unsigned int  dsc0_rcbuf0_empty    : 1;  /* bit[11]   : dsc0 rc buffer0��ָʾ�Ĵ��� */
        unsigned int  dsc0_rcbuf1_full     : 1;  /* bit[12]   : dsc0 rc buffer1������ָʾ�Ĵ��� */
        unsigned int  dsc0_rcbuf1_empty    : 1;  /* bit[13]   : dsc0 rc buffer1��ָʾ�Ĵ��� */
        unsigned int  reserved             : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_DSS_DSC_DSC0_ST_FIFO_UNION;
#endif
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_flatff_full_START      (0)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_flatff_full_END        (0)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_flatff_empty_START     (1)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_flatff_empty_END       (1)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_blncff0_full_START     (2)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_blncff0_full_END       (2)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_blncff0_empty_START    (3)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_blncff0_empty_END      (3)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_blncff1_full_START     (4)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_blncff1_full_END       (4)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_blncff1_empty_START    (5)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_blncff1_empty_END      (5)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_sesizeff0_full_START   (6)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_sesizeff0_full_END     (6)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_sesizeff0_empty_START  (7)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_sesizeff0_empty_END    (7)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_sesizeff1_full_START   (8)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_sesizeff1_full_END     (8)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_sesizeff1_empty_START  (9)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_sesizeff1_empty_END    (9)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_rcbuf0_full_START      (10)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_rcbuf0_full_END        (10)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_rcbuf0_empty_START     (11)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_rcbuf0_empty_END       (11)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_rcbuf1_full_START      (12)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_rcbuf1_full_END        (12)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_rcbuf1_empty_START     (13)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_rcbuf1_empty_END       (13)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_DSC1_ST_FIFO_UNION
 �ṹ˵��  : DSC1_ST_FIFO �Ĵ����ṹ���塣��ַƫ����:0x00A4����ֵ:0x00002AAA�����:32
 �Ĵ���˵��: FIFO����״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc1_flatff_full     : 1;  /* bit[0]    : dsc1 flat���fifo��ָʾ״̬�Ĵ��� */
        unsigned int  dsc1_flatff_empty    : 1;  /* bit[1]    : dsc1 flat���fifo��ָʾ״̬�Ĵ��� */
        unsigned int  dsc1_blncff0_full    : 1;  /* bit[2]    : dsc1 Y����balance fifo0��ָʾ�Ĵ��� */
        unsigned int  dsc1_blncff0_empty   : 1;  /* bit[3]    : dsc1 Y����balance fifo0��ָʾ�Ĵ��� */
        unsigned int  dsc1_blncff1_full    : 1;  /* bit[4]    : dsc1 Y����balance fifo1��ָʾ�Ĵ��� */
        unsigned int  dsc1_blncff1_empty   : 1;  /* bit[5]    : dsc1 Y����balance fifo1��ָʾ�Ĵ��� */
        unsigned int  dsc1_sesizeff0_full  : 1;  /* bit[6]    : dsc1 Y����syntax element size fifo0��ָʾ�Ĵ��� */
        unsigned int  dsc1_sesizeff0_empty : 1;  /* bit[7]    : dsc1 Y����syntax element size fifo0��ָʾ�Ĵ��� */
        unsigned int  dsc1_sesizeff1_full  : 1;  /* bit[8]    : dsc1 Y����syntax element size fifo1��ָʾ�Ĵ��� */
        unsigned int  dsc1_sesizeff1_empty : 1;  /* bit[9]    : dsc1 Y����syntax element size fifo1��ָʾ�Ĵ��� */
        unsigned int  dsc1_rcbuf0_full     : 1;  /* bit[10]   : dsc1 rc buffer0������ָʾ�Ĵ��� */
        unsigned int  dsc1_rcbuf0_empty    : 1;  /* bit[11]   : dsc1 rc buffer0��ָʾ�Ĵ��� */
        unsigned int  dsc1_rcbuf1_full     : 1;  /* bit[12]   : dsc1 rc buffer1������ָʾ�Ĵ��� */
        unsigned int  dsc1_rcbuf1_empty    : 1;  /* bit[13]   : dsc1 rc buffer1��ָʾ�Ĵ��� */
        unsigned int  reserved             : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_DSS_DSC_DSC1_ST_FIFO_UNION;
#endif
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_flatff_full_START      (0)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_flatff_full_END        (0)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_flatff_empty_START     (1)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_flatff_empty_END       (1)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_blncff0_full_START     (2)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_blncff0_full_END       (2)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_blncff0_empty_START    (3)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_blncff0_empty_END      (3)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_blncff1_full_START     (4)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_blncff1_full_END       (4)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_blncff1_empty_START    (5)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_blncff1_empty_END      (5)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_sesizeff0_full_START   (6)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_sesizeff0_full_END     (6)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_sesizeff0_empty_START  (7)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_sesizeff0_empty_END    (7)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_sesizeff1_full_START   (8)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_sesizeff1_full_END     (8)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_sesizeff1_empty_START  (9)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_sesizeff1_empty_END    (9)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_rcbuf0_full_START      (10)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_rcbuf0_full_END        (10)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_rcbuf0_empty_START     (11)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_rcbuf0_empty_END       (11)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_rcbuf1_full_START      (12)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_rcbuf1_full_END        (12)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_rcbuf1_empty_START     (13)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_rcbuf1_empty_END       (13)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_DSC0_ST_LINEBUF_UNION
 �ṹ˵��  : DSC0_ST_LINEBUF �Ĵ����ṹ���塣��ַƫ����:0x00A8����ֵ:0x00220000�����:32
 �Ĵ���˵��: LINEBUF״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc0_addr_linebuf  : 10; /* bit[0-9]  : dsc0 line buffer ��ַ״̬�Ĵ��� */
        unsigned int  reserved_0         : 6;  /* bit[10-15]: ���� */
        unsigned int  dsc0_infifo_full   : 1;  /* bit[16]   : dsc0 �ؽ����ض��뻺��fifo ��״̬������ */
        unsigned int  dsc0_infifo_empty  : 1;  /* bit[17]   : dsc0 �ؽ����ض��뻺��fifo ��״̬������ */
        unsigned int  dsc0_infifo_uflow  : 1;  /* bit[18]   : dsc0 �ؽ����ض��뻺��fifo underflow״̬������ */
        unsigned int  dsc0_infifo_oflow  : 1;  /* bit[19]   : dsc0 �ؽ����ض��뻺��fifo overflow״̬������ */
        unsigned int  dsc0_outfifo_full  : 1;  /* bit[20]   : dsc0 �ؽ�����д������fifo ��״̬������ */
        unsigned int  dsc0_outfifo_empty : 1;  /* bit[21]   : dsc0 �ؽ�����д������fifo ��״̬������ */
        unsigned int  dsc0_outfifo_uflow : 1;  /* bit[22]   : dsc0 �ؽ�����д������fifo underflow״̬������ */
        unsigned int  dsc0_outfifo_oflow : 1;  /* bit[23]   : dsc0 �ؽ�����д������fifo overflow״̬������ */
        unsigned int  reserved_1         : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_DSC_DSC0_ST_LINEBUF_UNION;
#endif
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_addr_linebuf_START   (0)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_addr_linebuf_END     (9)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_infifo_full_START    (16)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_infifo_full_END      (16)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_infifo_empty_START   (17)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_infifo_empty_END     (17)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_infifo_uflow_START   (18)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_infifo_uflow_END     (18)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_infifo_oflow_START   (19)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_infifo_oflow_END     (19)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_outfifo_full_START   (20)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_outfifo_full_END     (20)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_outfifo_empty_START  (21)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_outfifo_empty_END    (21)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_outfifo_uflow_START  (22)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_outfifo_uflow_END    (22)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_outfifo_oflow_START  (23)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_outfifo_oflow_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_DSC1_ST_LINEBUF_UNION
 �ṹ˵��  : DSC1_ST_LINEBUF �Ĵ����ṹ���塣��ַƫ����:0x00AC����ֵ:0x00220000�����:32
 �Ĵ���˵��: LINEBUF״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc1_addr_linebuf  : 10; /* bit[0-9]  : dsc1 line buffer ��ַ״̬�Ĵ��� */
        unsigned int  reserved_0         : 6;  /* bit[10-15]: ���� */
        unsigned int  dsc1_infifo_full   : 1;  /* bit[16]   : dsc1 �ؽ����ض��뻺��fifo ��״̬������ */
        unsigned int  dsc1_infifo_empty  : 1;  /* bit[17]   : dsc1 �ؽ����ض��뻺��fifo ��״̬������ */
        unsigned int  dsc1_infifo_uflow  : 1;  /* bit[18]   : dsc1 �ؽ����ض��뻺��fifo underflow״̬������ */
        unsigned int  dsc1_infifo_oflow  : 1;  /* bit[19]   : dsc1 �ؽ����ض��뻺��fifo overflow״̬������ */
        unsigned int  dsc1_outfifo_full  : 1;  /* bit[20]   : dsc1 �ؽ�����д������fifo ��״̬������ */
        unsigned int  dsc1_outfifo_empty : 1;  /* bit[21]   : dsc1 �ؽ�����д������fifo ��״̬������ */
        unsigned int  dsc1_outfifo_uflow : 1;  /* bit[22]   : dsc1 �ؽ�����д������fifo underflow״̬������ */
        unsigned int  dsc1_outfifo_oflow : 1;  /* bit[23]   : dsc1 �ؽ�����д������fifo overflow״̬������ */
        unsigned int  reserved_1         : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_DSC_DSC1_ST_LINEBUF_UNION;
#endif
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_addr_linebuf_START   (0)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_addr_linebuf_END     (9)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_infifo_full_START    (16)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_infifo_full_END      (16)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_infifo_empty_START   (17)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_infifo_empty_END     (17)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_infifo_uflow_START   (18)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_infifo_uflow_END     (18)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_infifo_oflow_START   (19)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_infifo_oflow_END     (19)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_outfifo_full_START   (20)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_outfifo_full_END     (20)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_outfifo_empty_START  (21)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_outfifo_empty_END    (21)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_outfifo_uflow_START  (22)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_outfifo_uflow_END    (22)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_outfifo_oflow_START  (23)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_outfifo_oflow_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_DSC_ST_ITFC_UNION
 �ṹ˵��  : DSC_ST_ITFC �Ĵ����ṹ���塣��ַƫ����:0x00B0����ֵ:0x0000000A�����:32
 �Ĵ���˵��: �ӿ�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc1_pre_drdy  : 1;  /* bit[0]    : dsc1 ǰ��ready-need�ӿ�״̬�Ĵ��� */
        unsigned int  dsc1_pre_dneed : 1;  /* bit[1]    : dsc1 ǰ��ready-need�ӿ�״̬�Ĵ��� */
        unsigned int  dsc1_dv2pred   : 1;  /* bit[2]    : dsc1 ǰ��ready-need�ӿ�״̬�Ĵ��� */
        unsigned int  dsc1_nxt_dneed : 1;  /* bit[3]    : dsc1 ��ready-need�ӿ�״̬�Ĵ��� */
        unsigned int  dsc1_nxt_drdy  : 1;  /* bit[4]    : dsc1 ��ready-need�ӿ�״̬�Ĵ��� */
        unsigned int  dsc0_pre_drdy  : 1;  /* bit[5]    : dsc0 ǰ��ready-need�ӿ�״̬�Ĵ��� */
        unsigned int  dsc0_pre_dneed : 1;  /* bit[6]    : dsc0 ǰ��ready-need�ӿ�״̬�Ĵ��� */
        unsigned int  dsc0_dv2pred   : 1;  /* bit[7]    : dsc0 ǰ��ready-need�ӿ�״̬�Ĵ��� */
        unsigned int  dsc0_nxt_dneed : 1;  /* bit[8]    : dsc0 ��ready-need�ӿ�״̬�Ĵ��� */
        unsigned int  dsc0_nxt_drdy  : 1;  /* bit[9]    : dsc0 ��ready-need�ӿ�״̬�Ĵ��� */
        unsigned int  reserved       : 22; /* bit[10-31]: ���� */
    } reg;
} SOC_DSS_DSC_DSC_ST_ITFC_UNION;
#endif
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc1_pre_drdy_START   (0)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc1_pre_drdy_END     (0)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc1_pre_dneed_START  (1)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc1_pre_dneed_END    (1)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc1_dv2pred_START    (2)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc1_dv2pred_END      (2)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc1_nxt_dneed_START  (3)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc1_nxt_dneed_END    (3)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc1_nxt_drdy_START   (4)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc1_nxt_drdy_END     (4)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc0_pre_drdy_START   (5)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc0_pre_drdy_END     (5)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc0_pre_dneed_START  (6)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc0_pre_dneed_END    (6)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc0_dv2pred_START    (7)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc0_dv2pred_END      (7)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc0_nxt_dneed_START  (8)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc0_nxt_dneed_END    (8)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc0_nxt_drdy_START   (9)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc0_nxt_drdy_END     (9)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_DSC_RD_SHADOW_SEL_UNION
 �ṹ˵��  : DSC_RD_SHADOW_SEL �Ĵ����ṹ���塣��ַƫ����:0x00B4����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���Ĵ���ѡ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc_rd_shadow : 1;  /* bit[0]   : 1'b0 :�������Ĵ���
                                                        1'b1 :��Ӱ�ӼĴ��� */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_DSC_DSC_RD_SHADOW_SEL_UNION;
#endif
#define SOC_DSS_DSC_DSC_RD_SHADOW_SEL_dsc_rd_shadow_START  (0)
#define SOC_DSS_DSC_DSC_RD_SHADOW_SEL_dsc_rd_shadow_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DSC_DSC_REG_DEFAULT_UNION
 �ṹ˵��  : DSC_REG_DEFAULT �Ĵ����ṹ���塣��ַƫ����:0x00B8����ֵ:0x00000000�����:32
 �Ĵ���˵��: ģ��Ӱ�ӼĴ����ָ���Ĭ��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc_reg_default : 1;  /* bit[0]   : ��˼Ĵ���д1������Ӱ�ӼĴ����ָ�����λֵ�� */
        unsigned int  reserved        : 31; /* bit[1-31]:  */
    } reg;
} SOC_DSS_DSC_DSC_REG_DEFAULT_UNION;
#endif
#define SOC_DSS_DSC_DSC_REG_DEFAULT_dsc_reg_default_START  (0)
#define SOC_DSS_DSC_DSC_REG_DEFAULT_dsc_reg_default_END    (0)






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

#endif /* end of soc_dss_dsc_interface.h */
