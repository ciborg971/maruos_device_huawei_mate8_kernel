/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_dss_scf_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:20:24
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_DSS_SCF.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_DSS_SCF_INTERFACE_H__
#define __SOC_DSS_SCF_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_SCF
 ****************************************************************************/
/* �Ĵ���˵����ˮƽ��������ʹ��
   λ����UNION�ṹ:  SOC_DSS_SCF_SCF_EN_HSCL_STR_UNION */
#define SOC_DSS_SCF_SCF_EN_HSCL_STR_ADDR(base)        ((base) + (0x0000))

/* �Ĵ���˵������ֱ��������ʹ��
   λ����UNION�ṹ:  SOC_DSS_SCF_SCF_EN_VSCL_STR_UNION */
#define SOC_DSS_SCF_SCF_EN_VSCL_STR_ADDR(base)        ((base) + (0x0004))

/* �Ĵ���˵����ˮƽ�ʹ�ֱ�˲��Լ�video����ģʽ����
   λ����UNION�ṹ:  SOC_DSS_SCF_SCF_H_V_ORDER_UNION */
#define SOC_DSS_SCF_SCF_H_V_ORDER_ADDR(base)          ((base) + (0x0008))

/* �Ĵ���˵����������
   λ����UNION�ṹ:  SOC_DSS_SCF_SCF_INPUT_WIDTH_HEIGHT_UNION */
#define SOC_DSS_SCF_SCF_INPUT_WIDTH_HEIGHT_ADDR(base) ((base) + (0x0010))

/* �Ĵ���˵����������
   λ����UNION�ṹ:  SOC_DSS_SCF_SCF_OUTPUT_WIDTH_HEIGHT_UNION */
#define SOC_DSS_SCF_SCF_OUTPUT_WIDTH_HEIGHT_ADDR(base) ((base) + (0x0014))

/* �Ĵ���˵��������ϵ��MEM�͹��Ŀ���
   λ����UNION�ṹ:  SOC_DSS_SCF_SCF_COEF_MEM_CTRL_UNION */
#define SOC_DSS_SCF_SCF_COEF_MEM_CTRL_ADDR(base)      ((base) + (0x0018))

/* �Ĵ���˵����ˮƽ����ʹ���ź�
   λ����UNION�ṹ:  SOC_DSS_SCF_SCF_EN_HSCL_UNION */
#define SOC_DSS_SCF_SCF_EN_HSCL_ADDR(base)            ((base) + (0x001C))

/* �Ĵ���˵������ֱ����ʹ���ź�
   λ����UNION�ṹ:  SOC_DSS_SCF_SCF_EN_VSCL_UNION */
#define SOC_DSS_SCF_SCF_EN_VSCL_ADDR(base)            ((base) + (0x0020))

/* �Ĵ���˵����ˮƽ��ʼ��λ
   λ����UNION�ṹ:  SOC_DSS_SCF_SCF_ACC_HSCL_UNION */
#define SOC_DSS_SCF_SCF_ACC_HSCL_ADDR(base)           ((base) + (0x0024))

/* �Ĵ���˵����ͨ��1ˮƽ��λ�����ƫ����
   λ����UNION�ṹ:  SOC_DSS_SCF_SCF_ACC_HSCL1_UNION */
#define SOC_DSS_SCF_SCF_ACC_HSCL1_ADDR(base)          ((base) + (0x0028))

/* �Ĵ���˵����ˮƽ���ű���
   λ����UNION�ṹ:  SOC_DSS_SCF_SCF_INC_HSCL_UNION */
#define SOC_DSS_SCF_SCF_INC_HSCL_ADDR(base)           ((base) + (0x0034))

/* �Ĵ���˵������ֱ��ʼ��λ
   λ����UNION�ṹ:  SOC_DSS_SCF_SCF_ACC_VSCL_UNION */
#define SOC_DSS_SCF_SCF_ACC_VSCL_ADDR(base)           ((base) + (0x0038))

/* �Ĵ���˵����ͨ��1��ֱ��λ�����ƫ����
   λ����UNION�ṹ:  SOC_DSS_SCF_SCF_ACC_VSCL1_UNION */
#define SOC_DSS_SCF_SCF_ACC_VSCL1_ADDR(base)          ((base) + (0x003C))

/* �Ĵ���˵������ֱ���ű���
   λ����UNION�ṹ:  SOC_DSS_SCF_SCF_INC_VSCL_UNION */
#define SOC_DSS_SCF_SCF_INC_VSCL_ADDR(base)           ((base) + (0x0048))

/* �Ĵ���˵������λ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_SCF_SCF_EN_NONLINEAR_UNION */
#define SOC_DSS_SCF_SCF_EN_NONLINEAR_ADDR(base)       ((base) + (0x004C))

/* �Ĵ���˵�������崦��ʹ���ź�
   λ����UNION�ṹ:  SOC_DSS_SCF_SCF_EN_MMP_UNION */
#define SOC_DSS_SCF_SCF_EN_MMP_ADDR(base)             ((base) + (0x007C))

/* �Ĵ���˵����ˮƽ�˲������ڲ�״̬�Ĵ���0
   λ����UNION�ṹ:  SOC_DSS_SCF_SCF_DB_H0_UNION */
#define SOC_DSS_SCF_SCF_DB_H0_ADDR(base)              ((base) + (0x0080))

/* �Ĵ���˵����ˮƽ�˲������ڲ�״̬�Ĵ���1
   λ����UNION�ṹ:  SOC_DSS_SCF_SCF_DB_H1_UNION */
#define SOC_DSS_SCF_SCF_DB_H1_ADDR(base)              ((base) + (0x0084))

/* �Ĵ���˵������ֱ�˲������ڲ�״̬�Ĵ���0
   λ����UNION�ṹ:  SOC_DSS_SCF_SCF_DB_V0_UNION */
#define SOC_DSS_SCF_SCF_DB_V0_ADDR(base)              ((base) + (0x0088))

/* �Ĵ���˵������ֱ�˲������ڲ�״̬�Ĵ���1
   λ����UNION�ṹ:  SOC_DSS_SCF_SCF_DB_V1_UNION */
#define SOC_DSS_SCF_SCF_DB_V1_ADDR(base)              ((base) + (0x008C))

/* �Ĵ���˵����Line Buf MEM�͹��Ŀ���
   λ����UNION�ṹ:  SOC_DSS_SCF_SCF_LB_MEM_CTRL_UNION */
#define SOC_DSS_SCF_SCF_LB_MEM_CTRL_ADDR(base)        ((base) + (0x0090))

/* �Ĵ���˵�������Ĵ���ѡ��
   λ����UNION�ṹ:  SOC_DSS_SCF_SCF_RD_SHADOW_UNION */
#define SOC_DSS_SCF_SCF_RD_SHADOW_ADDR(base)          ((base) + (0x00F0))

/* �Ĵ���˵����һ��ģ��ʱ��ѡ���ź�
   λ����UNION�ṹ:  SOC_DSS_SCF_SCF_CLK_SEL_UNION */
#define SOC_DSS_SCF_SCF_CLK_SEL_ADDR(base)            ((base) + (0x00F8))

/* �Ĵ���˵����һ��ģ��ʱ��ʹ���ź�
   λ����UNION�ṹ:  SOC_DSS_SCF_SCF_CLK_EN_UNION */
#define SOC_DSS_SCF_SCF_CLK_EN_ADDR(base)             ((base) + (0x00FC))

/* �Ĵ���˵����ģ��Ӱ�ӼĴ����ָ���Ĭ��ֵ
   λ����UNION�ṹ:  SOC_DSS_SCF_REG_DEFAULT_UNION */
#define SOC_DSS_SCF_REG_DEFAULT_ADDR(base)            ((base) + (0x00F4))

/* �Ĵ���˵����SCF 6tap�˲�ϵ��
   λ����UNION�ṹ:  SOC_DSS_SCF_V0_SCF_VIDEO_6TAP_COEF_UNION */
#define SOC_DSS_SCF_V0_SCF_VIDEO_6TAP_COEF_ADDR(base) ((base) + (0x1000))

/* �Ĵ���˵����SCF 5tap�˲�ϵ��
   λ����UNION�ṹ:  SOC_DSS_SCF_V0_SCF_VIDEO_5TAP_COEF_UNION */
#define SOC_DSS_SCF_V0_SCF_VIDEO_5TAP_COEF_ADDR(base) ((base) + (0x3000))

/* �Ĵ���˵����SCF 4tap�˲�ϵ��
   λ����UNION�ṹ:  SOC_DSS_SCF_V0_SCF_VIDEO_4TAP_COEF_UNION */
#define SOC_DSS_SCF_V0_SCF_VIDEO_4TAP_COEF_ADDR(base) ((base) + (0x3800))





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
                     (1/1) reg_SCF
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_DSS_SCF_SCF_EN_HSCL_STR_UNION
 �ṹ˵��  : SCF_EN_HSCL_STR �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: ˮƽ��������ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_en_hscl_str   : 1;  /* bit[0]   : ˮƽ��������ʹ�ܣ�����EN_HSCL��Чʱ��Ч
                                                            0��ˮƽ�˲�����
                                                            1��ˮƽ�������� */
        unsigned int  scf_en_hscl_str_a : 1;  /* bit[1]   : alphaˮƽ��������ʹ�ܣ�����EN_HSCL��Чʱ��Ч
                                                            0��ˮƽ�˲�����
                                                            1��ˮƽ�������� */
        unsigned int  reserved          : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_DSS_SCF_SCF_EN_HSCL_STR_UNION;
#endif
#define SOC_DSS_SCF_SCF_EN_HSCL_STR_scf_en_hscl_str_START    (0)
#define SOC_DSS_SCF_SCF_EN_HSCL_STR_scf_en_hscl_str_END      (0)
#define SOC_DSS_SCF_SCF_EN_HSCL_STR_scf_en_hscl_str_a_START  (1)
#define SOC_DSS_SCF_SCF_EN_HSCL_STR_scf_en_hscl_str_a_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SCF_SCF_EN_VSCL_STR_UNION
 �ṹ˵��  : SCF_EN_VSCL_STR �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ֱ��������ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_en_vscl_str   : 1;  /* bit[0]   : ��ֱ��������ʹ�ܣ�����EN_VSCL��Чʱ��Ч
                                                            0����ֱ�˲�����
                                                            1����ֱ��������
                                                            ������ǽ�ʡ��������RDMAģ������ֱ�����������������С */
        unsigned int  scf_en_vscl_str_a : 1;  /* bit[1]   : alpha��ֱ��������ʹ�ܣ�����EN_VSCL��Чʱ��Ч
                                                            0����ֱ�˲�����
                                                            1����ֱ��������
                                                            ������ǽ�ʡ��������RDMAģ������ֱ�����������������С */
        unsigned int  reserved          : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_DSS_SCF_SCF_EN_VSCL_STR_UNION;
#endif
#define SOC_DSS_SCF_SCF_EN_VSCL_STR_scf_en_vscl_str_START    (0)
#define SOC_DSS_SCF_SCF_EN_VSCL_STR_scf_en_vscl_str_END      (0)
#define SOC_DSS_SCF_SCF_EN_VSCL_STR_scf_en_vscl_str_a_START  (1)
#define SOC_DSS_SCF_SCF_EN_VSCL_STR_scf_en_vscl_str_a_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SCF_SCF_H_V_ORDER_UNION
 �ṹ˵��  : SCF_H_V_ORDER �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: ˮƽ�ʹ�ֱ�˲��Լ�video����ģʽ����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_h_v_order : 1;  /* bit[0]   : ˮƽ�ʹ�ֱ�˲���˳��
                                                        0��ˮƽ����
                                                        1��ˮƽ���� */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_SCF_SCF_H_V_ORDER_UNION;
#endif
#define SOC_DSS_SCF_SCF_H_V_ORDER_scf_h_v_order_START  (0)
#define SOC_DSS_SCF_SCF_H_V_ORDER_scf_h_v_order_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SCF_SCF_INPUT_WIDTH_HEIGHT_UNION
 �ṹ˵��  : SCF_INPUT_WIDTH_HEIGHT �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_input_height : 13; /* bit[0-12] : ʵ������߶� - 1
                                                            V5�汾����Ҫ���� */
        unsigned int  reserved_0       : 3;  /* bit[13-15]: ���� */
        unsigned int  scf_input_width  : 13; /* bit[16-28]: ʵ�������� - 1
                                                            V5�汾����Ҫ���� */
        unsigned int  reserved_1       : 3;  /* bit[29-31]: ���� */
    } reg;
} SOC_DSS_SCF_SCF_INPUT_WIDTH_HEIGHT_UNION;
#endif
#define SOC_DSS_SCF_SCF_INPUT_WIDTH_HEIGHT_scf_input_height_START  (0)
#define SOC_DSS_SCF_SCF_INPUT_WIDTH_HEIGHT_scf_input_height_END    (12)
#define SOC_DSS_SCF_SCF_INPUT_WIDTH_HEIGHT_scf_input_width_START   (16)
#define SOC_DSS_SCF_SCF_INPUT_WIDTH_HEIGHT_scf_input_width_END     (28)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SCF_SCF_OUTPUT_WIDTH_HEIGHT_UNION
 �ṹ˵��  : SCF_OUTPUT_WIDTH_HEIGHT �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_output_height : 13; /* bit[0-12] : ʵ������߶� - 1
                                                             V5�汾����Ҫ���� */
        unsigned int  reserved_0        : 3;  /* bit[13-15]: ���� */
        unsigned int  scf_output_width  : 13; /* bit[16-28]: ʵ�������� - 1;
                                                             V5�汾����Ҫ���� */
        unsigned int  reserved_1        : 3;  /* bit[29-31]: ���� */
    } reg;
} SOC_DSS_SCF_SCF_OUTPUT_WIDTH_HEIGHT_UNION;
#endif
#define SOC_DSS_SCF_SCF_OUTPUT_WIDTH_HEIGHT_scf_output_height_START  (0)
#define SOC_DSS_SCF_SCF_OUTPUT_WIDTH_HEIGHT_scf_output_height_END    (12)
#define SOC_DSS_SCF_SCF_OUTPUT_WIDTH_HEIGHT_scf_output_width_START   (16)
#define SOC_DSS_SCF_SCF_OUTPUT_WIDTH_HEIGHT_scf_output_width_END     (28)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SCF_SCF_COEF_MEM_CTRL_UNION
 �ṹ˵��  : SCF_COEF_MEM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ϵ��MEM�͹��Ŀ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_hcoef_mem_ctrl : 4;  /* bit[0-3] : �����üĴ�����ˮƽ�˲�ϵ��LUT������ã�
                                                             [3] mem_ctrl_auto_en , �Զ�ģʽ���������ģʽѡ��,0�Զ�ģʽ��1�������ģʽ 
                                                             [2]: �������ģʽ����Ч��Ϊ1��ʾ����Shut Downģʽ
                                                             [1]: �������ģʽ����Ч��Ϊ1��ʾ����Deep Sleepģʽ
                                                             [0]: �������ģʽ����Ч��Ϊ1��ʾ����Sleepģʽ */
        unsigned int  scf_vcoef_mem_ctrl : 4;  /* bit[4-7] : �����üĴ�������ֱ�˲�ϵ��LUT������ã�
                                                             [3] mem_ctrl_auto_en , �Զ�ģʽ���������ģʽѡ��,0�Զ�ģʽ��1�������ģʽ 
                                                             [2]: �������ģʽ����Ч��Ϊ1��ʾ����Shut Downģʽ
                                                             [1]: �������ģʽ����Ч��Ϊ1��ʾ����Deep Sleepģʽ
                                                             [0]: �������ģʽ����Ч��Ϊ1��ʾ����Sleepģʽ */
        unsigned int  reserved           : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_DSS_SCF_SCF_COEF_MEM_CTRL_UNION;
#endif
#define SOC_DSS_SCF_SCF_COEF_MEM_CTRL_scf_hcoef_mem_ctrl_START  (0)
#define SOC_DSS_SCF_SCF_COEF_MEM_CTRL_scf_hcoef_mem_ctrl_END    (3)
#define SOC_DSS_SCF_SCF_COEF_MEM_CTRL_scf_vcoef_mem_ctrl_START  (4)
#define SOC_DSS_SCF_SCF_COEF_MEM_CTRL_scf_vcoef_mem_ctrl_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SCF_SCF_EN_HSCL_UNION
 �ṹ˵��  : SCF_EN_HSCL �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ˮƽ����ʹ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_en_hscl_en : 1;  /* bit[0]   : ˮƽ����ʹ���ź� */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_SCF_SCF_EN_HSCL_UNION;
#endif
#define SOC_DSS_SCF_SCF_EN_HSCL_scf_en_hscl_en_START  (0)
#define SOC_DSS_SCF_SCF_EN_HSCL_scf_en_hscl_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SCF_SCF_EN_VSCL_UNION
 �ṹ˵��  : SCF_EN_VSCL �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ֱ����ʹ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_en_vscl_en    : 1;  /* bit[0]   : ��ֱ����ʹ���ź� */
        unsigned int  scf_out_buffer_en : 1;  /* bit[1]   : ����ֱ��������ͼ��߶�С�ڵ�������ͼ��߶�ʱ��ʹ��scf����buffer���������ʹ�����üĴ�����
                                                            1.ʹ����buffer��������棻
                                                            0.��ʹ����buffer��������� */
        unsigned int  reserved          : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_DSS_SCF_SCF_EN_VSCL_UNION;
#endif
#define SOC_DSS_SCF_SCF_EN_VSCL_scf_en_vscl_en_START     (0)
#define SOC_DSS_SCF_SCF_EN_VSCL_scf_en_vscl_en_END       (0)
#define SOC_DSS_SCF_SCF_EN_VSCL_scf_out_buffer_en_START  (1)
#define SOC_DSS_SCF_SCF_EN_VSCL_scf_out_buffer_en_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SCF_SCF_ACC_HSCL_UNION
 �ṹ˵��  : SCF_ACC_HSCL �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x00000000�����:32
 �Ĵ���˵��: ˮƽ��ʼ��λ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_acc_hscl : 30; /* bit[0-29] : ˮƽ��ʼ��λ������ˮƽSC��ʲôλ�ÿ�ʼ�����š�
                                                        ���е�18λΪС�����֣���12λΪ�������֡� */
        unsigned int  reserved     : 2;  /* bit[30-31]: ���� */
    } reg;
} SOC_DSS_SCF_SCF_ACC_HSCL_UNION;
#endif
#define SOC_DSS_SCF_SCF_ACC_HSCL_scf_acc_hscl_START  (0)
#define SOC_DSS_SCF_SCF_ACC_HSCL_scf_acc_hscl_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SCF_SCF_ACC_HSCL1_UNION
 �ṹ˵��  : SCF_ACC_HSCL1 �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͨ��1ˮƽ��λ�����ƫ����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_acc_hscl1 : 19; /* bit[0-18] : ͨ��1ˮƽ��λ�����ƫ�����������ACC_HSCL��
                                                         V5�汾�˴�����ΪUV���������Y��������λƫ�ƣ�����Чλ��Ϊ17bit�з����� */
        unsigned int  reserved      : 13; /* bit[19-31]: ���� */
    } reg;
} SOC_DSS_SCF_SCF_ACC_HSCL1_UNION;
#endif
#define SOC_DSS_SCF_SCF_ACC_HSCL1_scf_acc_hscl1_START  (0)
#define SOC_DSS_SCF_SCF_ACC_HSCL1_scf_acc_hscl1_END    (18)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SCF_SCF_INC_HSCL_UNION
 �ṹ˵��  : SCF_INC_HSCL �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x00005000�����:32
 �Ĵ���˵��: ˮƽ���ű���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_inc_hscl : 24;
        unsigned int  reserved     : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_SCF_SCF_INC_HSCL_UNION;
#endif
#define SOC_DSS_SCF_SCF_INC_HSCL_scf_inc_hscl_START  (0)
#define SOC_DSS_SCF_SCF_INC_HSCL_scf_inc_hscl_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SCF_SCF_ACC_VSCL_UNION
 �ṹ˵��  : SCF_ACC_VSCL �Ĵ����ṹ���塣��ַƫ����:0x0038����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ֱ��ʼ��λ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_acc_vscl : 30; /* bit[0-29] : ��ֱ��ʼ��λ��������ֱSC��ʲôλ�ÿ�ʼ�����ţ����е�18λΪС�����֣���12λΪ�������֡� */
        unsigned int  reserved     : 2;  /* bit[30-31]: ���� */
    } reg;
} SOC_DSS_SCF_SCF_ACC_VSCL_UNION;
#endif
#define SOC_DSS_SCF_SCF_ACC_VSCL_scf_acc_vscl_START  (0)
#define SOC_DSS_SCF_SCF_ACC_VSCL_scf_acc_vscl_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SCF_SCF_ACC_VSCL1_UNION
 �ṹ˵��  : SCF_ACC_VSCL1 �Ĵ����ṹ���塣��ַƫ����:0x003C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͨ��1��ֱ��λ�����ƫ����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_acc_vscl1 : 19; /* bit[0-18] : ͨ��1��ֱ��λ�����ƫ�����������ACC_VSCL��
                                                         V5�汾Ϊ����ɫ��UV���������Y������ƫ��ֵ������Чλ��Ϊ17bit�з����� */
        unsigned int  reserved      : 13; /* bit[19-31]: ���� */
    } reg;
} SOC_DSS_SCF_SCF_ACC_VSCL1_UNION;
#endif
#define SOC_DSS_SCF_SCF_ACC_VSCL1_scf_acc_vscl1_START  (0)
#define SOC_DSS_SCF_SCF_ACC_VSCL1_scf_acc_vscl1_END    (18)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SCF_SCF_INC_VSCL_UNION
 �ṹ˵��  : SCF_INC_VSCL �Ĵ����ṹ���塣��ַƫ����:0x0048����ֵ:0x00005000�����:32
 �Ĵ���˵��: ��ֱ���ű���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_inc_vscl : 24;
        unsigned int  reserved     : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_SCF_SCF_INC_VSCL_UNION;
#endif
#define SOC_DSS_SCF_SCF_INC_VSCL_scf_inc_vscl_START  (0)
#define SOC_DSS_SCF_SCF_INC_VSCL_scf_inc_vscl_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SCF_SCF_EN_NONLINEAR_UNION
 �ṹ˵��  : SCF_EN_NONLINEAR �Ĵ����ṹ���塣��ַƫ����:0x004C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��λ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_sw_rst : 1;  /* bit[0]   : scfģ����λ���üĴ�����1��Ч */
        unsigned int  reserved   : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_SCF_SCF_EN_NONLINEAR_UNION;
#endif
#define SOC_DSS_SCF_SCF_EN_NONLINEAR_scf_sw_rst_START  (0)
#define SOC_DSS_SCF_SCF_EN_NONLINEAR_scf_sw_rst_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SCF_SCF_EN_MMP_UNION
 �ṹ˵��  : SCF_EN_MMP �Ĵ����ṹ���塣��ַƫ����:0x007C����ֵ:0x00000001�����:32
 �Ĵ���˵��: ���崦��ʹ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_en_mmp : 1;  /* bit[0]   : ���崦��ʹ���źţ�1��ʾʹ�ܣ�0��ʾ��ʹ�� */
        unsigned int  reserved   : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_SCF_SCF_EN_MMP_UNION;
#endif
#define SOC_DSS_SCF_SCF_EN_MMP_scf_en_mmp_START  (0)
#define SOC_DSS_SCF_SCF_EN_MMP_scf_en_mmp_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SCF_SCF_DB_H0_UNION
 �ṹ˵��  : SCF_DB_H0 �Ĵ����ṹ���塣��ַƫ����:0x0080����ֵ:0x00000000�����:32
 �Ĵ���˵��: ˮƽ�˲������ڲ�״̬�Ĵ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_debug_h0 : 32; /* bit[0-31]:  */
    } reg;
} SOC_DSS_SCF_SCF_DB_H0_UNION;
#endif
#define SOC_DSS_SCF_SCF_DB_H0_scf_debug_h0_START  (0)
#define SOC_DSS_SCF_SCF_DB_H0_scf_debug_h0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SCF_SCF_DB_H1_UNION
 �ṹ˵��  : SCF_DB_H1 �Ĵ����ṹ���塣��ַƫ����:0x0084����ֵ:0x00000000�����:32
 �Ĵ���˵��: ˮƽ�˲������ڲ�״̬�Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_debug_h1 : 32; /* bit[0-31]:  */
    } reg;
} SOC_DSS_SCF_SCF_DB_H1_UNION;
#endif
#define SOC_DSS_SCF_SCF_DB_H1_scf_debug_h1_START  (0)
#define SOC_DSS_SCF_SCF_DB_H1_scf_debug_h1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SCF_SCF_DB_V0_UNION
 �ṹ˵��  : SCF_DB_V0 �Ĵ����ṹ���塣��ַƫ����:0x0088����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ֱ�˲������ڲ�״̬�Ĵ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_debug_v0 : 32; /* bit[0-31]:  */
    } reg;
} SOC_DSS_SCF_SCF_DB_V0_UNION;
#endif
#define SOC_DSS_SCF_SCF_DB_V0_scf_debug_v0_START  (0)
#define SOC_DSS_SCF_SCF_DB_V0_scf_debug_v0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SCF_SCF_DB_V1_UNION
 �ṹ˵��  : SCF_DB_V1 �Ĵ����ṹ���塣��ַƫ����:0x008C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ֱ�˲������ڲ�״̬�Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_debug_v1 : 32; /* bit[0-31]:  */
    } reg;
} SOC_DSS_SCF_SCF_DB_V1_UNION;
#endif
#define SOC_DSS_SCF_SCF_DB_V1_scf_debug_v1_START  (0)
#define SOC_DSS_SCF_SCF_DB_V1_scf_debug_v1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SCF_SCF_LB_MEM_CTRL_UNION
 �ṹ˵��  : SCF_LB_MEM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0090����ֵ:0x00000000�����:32
 �Ĵ���˵��: Line Buf MEM�͹��Ŀ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_lb_mem_ctrl : 4;  /* bit[0-3] : �����üĴ�������ӦLine Buf��MEM
                                                          [3] mem_ctrl_auto_en , �Զ�ģʽ���������ģʽѡ��,0�Զ�ģʽ��1�������ģʽ 
                                                          [2]: �������ģʽ����Ч��Ϊ1��ʾ����Shut Downģʽ
                                                          [1]: �������ģʽ����Ч��Ϊ1��ʾ����Deep Sleepģʽ
                                                          [0]: �������ģʽ����Ч��Ϊ1��ʾ����Sleepģʽ */
        unsigned int  reserved        : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_DSS_SCF_SCF_LB_MEM_CTRL_UNION;
#endif
#define SOC_DSS_SCF_SCF_LB_MEM_CTRL_scf_lb_mem_ctrl_START  (0)
#define SOC_DSS_SCF_SCF_LB_MEM_CTRL_scf_lb_mem_ctrl_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SCF_SCF_RD_SHADOW_UNION
 �ṹ˵��  : SCF_RD_SHADOW �Ĵ����ṹ���塣��ַƫ����:0x00F0����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���Ĵ���ѡ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_rd_shadow : 1;  /* bit[0]   : ���Ĵ���ѡ��
                                                        0�������Ĵ���
                                                        1��Ӱ�ӼĴ��� */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_SCF_SCF_RD_SHADOW_UNION;
#endif
#define SOC_DSS_SCF_SCF_RD_SHADOW_scf_rd_shadow_START  (0)
#define SOC_DSS_SCF_SCF_RD_SHADOW_scf_rd_shadow_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SCF_SCF_CLK_SEL_UNION
 �ṹ˵��  : SCF_CLK_SEL �Ĵ����ṹ���塣��ַƫ����:0x00F8����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: һ��ģ��ʱ��ѡ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_clk_sel : 32; /* bit[0-31]: ��һ��ģ���ʱ��ѡ���źţ�
                                                      1����ʾǿ�ƴ�ʱ�ӡ�
                                                      0����ʾ��Ҫ���������Ӳ����ʱ��ʹ����������ر�ʱ��
                                                      [0]:ˮƽ����
                                                      [1]:��ֱ���� */
    } reg;
} SOC_DSS_SCF_SCF_CLK_SEL_UNION;
#endif
#define SOC_DSS_SCF_SCF_CLK_SEL_scf_clk_sel_START  (0)
#define SOC_DSS_SCF_SCF_CLK_SEL_scf_clk_sel_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SCF_SCF_CLK_EN_UNION
 �ṹ˵��  : SCF_CLK_EN �Ĵ����ṹ���塣��ַƫ����:0x00FC����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: һ��ģ��ʱ��ʹ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_clk_en : 32; /* bit[0-31]: ��һ��ģ������ʱ��ʹ���ź�
                                                     1����ʾ���ʱ��ʹ����Ч������Ӳ������
                                                     0����ʾ���ʱ��ʹ����Ч����ֹӲ������
                                                     [0]:ˮƽ����
                                                     [1]:��ֱ���� */
    } reg;
} SOC_DSS_SCF_SCF_CLK_EN_UNION;
#endif
#define SOC_DSS_SCF_SCF_CLK_EN_scf_clk_en_START  (0)
#define SOC_DSS_SCF_SCF_CLK_EN_scf_clk_en_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SCF_REG_DEFAULT_UNION
 �ṹ˵��  : REG_DEFAULT �Ĵ����ṹ���塣��ַƫ����:0x00F4����ֵ:0x00000000�����:32
 �Ĵ���˵��: ģ��Ӱ�ӼĴ����ָ���Ĭ��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg_default : 1;  /* bit[0]   :  */
        unsigned int  reserved    : 31; /* bit[1-31]:  */
    } reg;
} SOC_DSS_SCF_REG_DEFAULT_UNION;
#endif
#define SOC_DSS_SCF_REG_DEFAULT_reg_default_START  (0)
#define SOC_DSS_SCF_REG_DEFAULT_reg_default_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SCF_V0_SCF_VIDEO_6TAP_COEF_UNION
 �ṹ˵��  : V0_SCF_VIDEO_6TAP_COEF �Ĵ����ṹ���塣��ַƫ����:0x1000����ֵ:0x00000000�����:32
 �Ĵ���˵��: SCF 6tap�˲�ϵ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_video_6tap_coef : 32; /* bit[0-31]: 6tap����ϵ��lut��Ļ���ַ������V3���ã���ַ��Χ0x1000��0x143F */
    } reg;
} SOC_DSS_SCF_V0_SCF_VIDEO_6TAP_COEF_UNION;
#endif
#define SOC_DSS_SCF_V0_SCF_VIDEO_6TAP_COEF_scf_video_6tap_coef_START  (0)
#define SOC_DSS_SCF_V0_SCF_VIDEO_6TAP_COEF_scf_video_6tap_coef_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SCF_V0_SCF_VIDEO_5TAP_COEF_UNION
 �ṹ˵��  : V0_SCF_VIDEO_5TAP_COEF �Ĵ����ṹ���塣��ַƫ����:0x3000����ֵ:0x00000000�����:32
 �Ĵ���˵��: SCF 5tap�˲�ϵ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_video_5tap_coef : 32; /* bit[0-31]: 5tap����ϵ��lut��Ļ���ַ������V3���ã���ַ��Χ0x3000��0x343F */
    } reg;
} SOC_DSS_SCF_V0_SCF_VIDEO_5TAP_COEF_UNION;
#endif
#define SOC_DSS_SCF_V0_SCF_VIDEO_5TAP_COEF_scf_video_5tap_coef_START  (0)
#define SOC_DSS_SCF_V0_SCF_VIDEO_5TAP_COEF_scf_video_5tap_coef_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_SCF_V0_SCF_VIDEO_4TAP_COEF_UNION
 �ṹ˵��  : V0_SCF_VIDEO_4TAP_COEF �Ĵ����ṹ���塣��ַƫ����:0x3800����ֵ:0x00000000�����:32
 �Ĵ���˵��: SCF 4tap�˲�ϵ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_video_4tap_coef : 32; /* bit[0-31]: 4tap����ϵ��lut��Ļ���ַ������V3���ã���ַ��Χ0x3800��0x3A1F */
    } reg;
} SOC_DSS_SCF_V0_SCF_VIDEO_4TAP_COEF_UNION;
#endif
#define SOC_DSS_SCF_V0_SCF_VIDEO_4TAP_COEF_scf_video_4tap_coef_START  (0)
#define SOC_DSS_SCF_V0_SCF_VIDEO_4TAP_COEF_scf_video_4tap_coef_END    (31)






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

#endif /* end of soc_dss_scf_interface.h */
