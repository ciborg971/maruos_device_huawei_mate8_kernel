/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_dss_ifbc_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:20:08
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_DSS_IFBC.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_DSS_IFBC_INTERFACE_H__
#define __SOC_DSS_IFBC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_IFBC
 ****************************************************************************/
/* �Ĵ���˵����IFBCͼ��ߴ�
   λ����UNION�ṹ:  SOC_DSS_IFBC_IFBC_SIZE_UNION */
#define SOC_DSS_IFBC_IFBC_SIZE_ADDR(base)             ((base) + (0x0000))

/* �Ĵ���˵����IFBC����
   λ����UNION�ṹ:  SOC_DSS_IFBC_IFBC_CTRL_UNION */
#define SOC_DSS_IFBC_IFBC_CTRL_ADDR(base)             ((base) + (0x0004))

/* �Ĵ���˵����IFBC Himax����
   λ����UNION�ṹ:  SOC_DSS_IFBC_IFBC_HIMAX_CTRL0_UNION */
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL0_ADDR(base)      ((base) + (0x0008))

/* �Ĵ���˵����IFBC Himax����
   λ����UNION�ṹ:  SOC_DSS_IFBC_IFBC_HIMAX_CTRL1_UNION */
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL1_ADDR(base)      ((base) + (0x000C))

/* �Ĵ���˵����IFBC Himax����
   λ����UNION�ṹ:  SOC_DSS_IFBC_IFBC_HIMAX_CTRL2_UNION */
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL2_ADDR(base)      ((base) + (0x0010))

/* �Ĵ���˵����IFBC Himax����
   λ����UNION�ṹ:  SOC_DSS_IFBC_IFBC_HIMAX_CTRL3_UNION */
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL3_ADDR(base)      ((base) + (0x0014))

/* �Ĵ���˵�����͹��Ŀ���
   λ����UNION�ṹ:  SOC_DSS_IFBC_IFBC_EN_UNION */
#define SOC_DSS_IFBC_IFBC_EN_ADDR(base)               ((base) + (0x0018))

/* �Ĵ���˵����MEM�͹��Ŀ��ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_IFBC_IFBC_MEM_CTRL_UNION */
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ADDR(base)         ((base) + (0x001C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_IFBC_IFBC_INSERT_UNION */
#define SOC_DSS_IFBC_IFBC_INSERT_ADDR(base)           ((base) + (0x0020))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_IFBC_HIMAX_TEST_MODE_UNION */
#define SOC_DSS_IFBC_HIMAX_TEST_MODE_ADDR(base)       ((base) + (0x0024))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_IFBC_IFBC_CORE_GT_UNION */
#define SOC_DSS_IFBC_IFBC_CORE_GT_ADDR(base)          ((base) + (0x0028))

/* �Ĵ���˵����MEM�͹��Ŀ��ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_IFBC_IFBC_PM_CTRL_UNION */
#define SOC_DSS_IFBC_IFBC_PM_CTRL_ADDR(base)          ((base) + (0x002C))

/* �Ĵ���˵������Ӱ�ӼĴ���ѡ���ź�
   λ����UNION�ṹ:  SOC_DSS_IFBC_IFBC_RD_SHADOW_UNION */
#define SOC_DSS_IFBC_IFBC_RD_SHADOW_ADDR(base)        ((base) + (0x0030))

/* �Ĵ���˵����Orise���ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_IFBC_ORISE_CTL_UNION */
#define SOC_DSS_IFBC_ORISE_CTL_ADDR(base)             ((base) + (0x0034))

/* �Ĵ���˵����Orise debug�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_IFBC_ORSISE_DEBUG0_UNION */
#define SOC_DSS_IFBC_ORSISE_DEBUG0_ADDR(base)         ((base) + (0x0038))

/* �Ĵ���˵����Orise debug�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_IFBC_ORSISE_DEBUG1_UNION */
#define SOC_DSS_IFBC_ORSISE_DEBUG1_ADDR(base)         ((base) + (0x003C))

/* �Ĵ���˵����RSP�����ź�
   λ����UNION�ṹ:  SOC_DSS_IFBC_rsp_comp_test_UNION */
#define SOC_DSS_IFBC_rsp_comp_test_ADDR(base)         ((base) + (0x0040))

/* �Ĵ���˵����һ��ģ��ʱ��ѡ���ź�
   λ����UNION�ṹ:  SOC_DSS_IFBC_IFBC_CLK_SEL_UNION */
#define SOC_DSS_IFBC_IFBC_CLK_SEL_ADDR(base)          ((base) + (0x044))

/* �Ĵ���˵����һ��ģ��ʱ��ʹ���ź�
   λ����UNION�ṹ:  SOC_DSS_IFBC_IFBC_CLK_EN_UNION */
#define SOC_DSS_IFBC_IFBC_CLK_EN_ADDR(base)           ((base) + (0x048))

/* �Ĵ���˵����PAD�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_IFBC_IFBC_PAD_UNION */
#define SOC_DSS_IFBC_IFBC_PAD_ADDR(base)              ((base) + (0x004C))

/* �Ĵ���˵����ģ��Ӱ�ӼĴ����ָ���Ĭ��ֵ
   λ����UNION�ṹ:  SOC_DSS_IFBC_REG_DEFAULT_UNION */
#define SOC_DSS_IFBC_REG_DEFAULT_ADDR(base)           ((base) + (0x0050))





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
                     (1/1) reg_IFBC
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_DSS_IFBC_IFBC_SIZE_UNION
 �ṹ˵��  : IFBC_SIZE �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x04FF02CF�����:32
 �Ĵ���˵��: IFBCͼ��ߴ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ifbc_size_vrt : 16; /* bit[0-15] : IFBC����ͼ������ظ߶�(��ֱ����)-1(������Ϊ��λ)��ֻ����ż�� */
        unsigned int  ifbc_size_hrz : 16; /* bit[16-31]: IFBC����ͼ������ؿ��(ˮƽ����)-1(������Ϊ��λ)��ֻ����ż�� */
    } reg;
} SOC_DSS_IFBC_IFBC_SIZE_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_SIZE_ifbc_size_vrt_START  (0)
#define SOC_DSS_IFBC_IFBC_SIZE_ifbc_size_vrt_END    (15)
#define SOC_DSS_IFBC_IFBC_SIZE_ifbc_size_hrz_START  (16)
#define SOC_DSS_IFBC_IFBC_SIZE_ifbc_size_hrz_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_IFBC_IFBC_CTRL_UNION
 �ṹ˵��  : IFBC_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000006�����:32
 �Ĵ���˵��: IFBC����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  comp_mode     : 3;  /* bit[0-2]  : ѹ���㷨ģʽ
                                                         3'b000: orise2x
                                                         3'b001: orise3x
                                                         3'b010: himax2x
                                                         3'b011: rsp2x
                                                         3'b100: rsp3x
                                                         3'b101: vesa dsc/1 pipe
                                                         3'b110: vesa dsc/2 pipe */
        unsigned int  ifbc_out_mode : 1;  /* bit[3]    : ifbc������ݸ�ʽ��
                                                         1: 24bit��Ϊ��Ч����
                                                         0: ��8λ��0����16λ��Ч���� */
        unsigned int  cmp_dat_rev0  : 1;  /* bit[4]    : Ҫ��24bit�ߵ�λ��ת
                                                         0����
                                                         1����ת */
        unsigned int  cmp_dat_rev1  : 1;  /* bit[5]    : Ҫ��byte�ߵ�λ��ת
                                                         0����
                                                         1����ת */
        unsigned int  auto_sel      : 1;  /* bit[6]    : 1��Ӳ���Զ�����ģʽ��Ӳ������comp_mode,ifbc_size_hrz,out_mode�Զ�����dpk_mode_sel,dup_mode_sel,num_pad,insert_byte,insert_byte_num��
                                                         0���������ģʽ */
        unsigned int  dpk_mode_sel  : 3;  /* bit[7-9]  : ifbc_dpk����������Чλ��
                                                         3'b0: 16bit��orise3xʱʹ��
                                                         3'b1: 48bit��orise2x/himax2x/rsp2xʱʹ��
                                                         3'b10:64bit��rsp3xʱʹ�� */
        unsigned int  dup_mode_sel  : 3;  /* bit[10-12]: fbc_dup������õ�ģʽ
                                                         3'b0: 4x1 size�����rsp2xʱʹ��
                                                         3'b1: 4x2 size�����rsp3xʱʹ��
                                                         3'b10:2x2 size�����himax2x/orise2xʱʹ��
                                                         3'b11:2x1 size�����orise3xʱʹ�� */
        unsigned int  porch_num     : 8;  /* bit[13-20]: ÿ����Ҫ��β��Ҫ��ѹ���е���������ͬifbc �������ص�ʱ�� */
        unsigned int  reserved      : 11; /* bit[21-31]: ���� */
    } reg;
} SOC_DSS_IFBC_IFBC_CTRL_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_CTRL_comp_mode_START      (0)
#define SOC_DSS_IFBC_IFBC_CTRL_comp_mode_END        (2)
#define SOC_DSS_IFBC_IFBC_CTRL_ifbc_out_mode_START  (3)
#define SOC_DSS_IFBC_IFBC_CTRL_ifbc_out_mode_END    (3)
#define SOC_DSS_IFBC_IFBC_CTRL_cmp_dat_rev0_START   (4)
#define SOC_DSS_IFBC_IFBC_CTRL_cmp_dat_rev0_END     (4)
#define SOC_DSS_IFBC_IFBC_CTRL_cmp_dat_rev1_START   (5)
#define SOC_DSS_IFBC_IFBC_CTRL_cmp_dat_rev1_END     (5)
#define SOC_DSS_IFBC_IFBC_CTRL_auto_sel_START       (6)
#define SOC_DSS_IFBC_IFBC_CTRL_auto_sel_END         (6)
#define SOC_DSS_IFBC_IFBC_CTRL_dpk_mode_sel_START   (7)
#define SOC_DSS_IFBC_IFBC_CTRL_dpk_mode_sel_END     (9)
#define SOC_DSS_IFBC_IFBC_CTRL_dup_mode_sel_START   (10)
#define SOC_DSS_IFBC_IFBC_CTRL_dup_mode_sel_END     (12)
#define SOC_DSS_IFBC_IFBC_CTRL_porch_num_START      (13)
#define SOC_DSS_IFBC_IFBC_CTRL_porch_num_END        (20)


/*****************************************************************************
 �ṹ��    : SOC_DSS_IFBC_IFBC_HIMAX_CTRL0_UNION
 �ṹ˵��  : IFBC_HIMAX_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x04020100�����:32
 �Ĵ���˵��: IFBC Himax����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_hm_lut0 : 32; /* bit[0-31]: himax��� */
    } reg;
} SOC_DSS_IFBC_IFBC_HIMAX_CTRL0_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL0_cfg_hm_lut0_START  (0)
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL0_cfg_hm_lut0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_IFBC_IFBC_HIMAX_CTRL1_UNION
 �ṹ˵��  : IFBC_HIMAX_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x18100A08�����:32
 �Ĵ���˵��: IFBC Himax����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_hm_lut1 : 32; /* bit[0-31]: himax��� */
    } reg;
} SOC_DSS_IFBC_IFBC_HIMAX_CTRL1_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL1_cfg_hm_lut1_START  (0)
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL1_cfg_hm_lut1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_IFBC_IFBC_HIMAX_CTRL2_UNION
 �ṹ˵��  : IFBC_HIMAX_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x40383020�����:32
 �Ĵ���˵��: IFBC Himax����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_hm_lut2 : 32; /* bit[0-31]: himax��� */
    } reg;
} SOC_DSS_IFBC_IFBC_HIMAX_CTRL2_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL2_cfg_hm_lut2_START  (0)
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL2_cfg_hm_lut2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_IFBC_IFBC_HIMAX_CTRL3_UNION
 �ṹ˵��  : IFBC_HIMAX_CTRL3 �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0xFFC0A080�����:32
 �Ĵ���˵��: IFBC Himax����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_hm_lut3 : 32; /* bit[0-31]: himax��� */
    } reg;
} SOC_DSS_IFBC_IFBC_HIMAX_CTRL3_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL3_cfg_hm_lut3_START  (0)
#define SOC_DSS_IFBC_IFBC_HIMAX_CTRL3_cfg_hm_lut3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_IFBC_IFBC_EN_UNION
 �ṹ˵��  : IFBC_EN �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: �͹��Ŀ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ifbc_en      : 1;  /* bit[0]   : 0: IFBC disable;
                                                       1: IFBC enable; */
        unsigned int  ifbc_out_sel : 1;  /* bit[1]   : 0: bypass;
                                                       1: �������� */
        unsigned int  reserved     : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_DSS_IFBC_IFBC_EN_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_EN_ifbc_en_START       (0)
#define SOC_DSS_IFBC_IFBC_EN_ifbc_en_END         (0)
#define SOC_DSS_IFBC_IFBC_EN_ifbc_out_sel_START  (1)
#define SOC_DSS_IFBC_IFBC_EN_ifbc_out_sel_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_DSS_IFBC_IFBC_MEM_CTRL_UNION
 �ṹ˵��  : IFBC_MEM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000000�����:32
 �Ĵ���˵��: MEM�͹��Ŀ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ifbc_mem_ctrl_0 : 4;  /* bit[0-3]  : �����üĴ�������Ӧ��һ��spram512x48
                                                           [3] mem_ctrl_auto_en , �Զ�ģʽ���������ģʽѡ��,0�Զ�ģʽ��1�������ģʽ 
                                                           [2]: �������ģʽ����Ч��Ϊ1��ʾ����Shut Downģʽ
                                                           [1]: �������ģʽ����Ч��Ϊ1��ʾ����Deep Sleepģʽ
                                                           [0]: �������ģʽ����Ч��Ϊ1��ʾ����Sleepģʽ */
        unsigned int  ifbc_mem_ctrl_1 : 4;  /* bit[4-7]  : �����üĴ�������bit�������� */
        unsigned int  ifbc_mem_ctrl_2 : 4;  /* bit[8-11] : �����üĴ�������bit�������� */
        unsigned int  ifbc_mem_ctrl_3 : 4;  /* bit[12-15]: �����üĴ�������bit�������� */
        unsigned int  ifbc_mem_ctrl_4 : 4;  /* bit[16-19]: �����üĴ�������bit�������� */
        unsigned int  ifbc_mem_ctrl_5 : 4;  /* bit[20-23]: �����üĴ�������bit�������� */
        unsigned int  ifbc_mem_ctrl_6 : 4;  /* bit[24-27]: �����üĴ�������bit�������� */
        unsigned int  ifbc_mem_ctrl_7 : 4;  /* bit[28-31]: �����üĴ�������bit�������� */
    } reg;
} SOC_DSS_IFBC_IFBC_MEM_CTRL_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_0_START  (0)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_0_END    (3)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_1_START  (4)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_1_END    (7)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_2_START  (8)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_2_END    (11)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_3_START  (12)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_3_END    (15)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_4_START  (16)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_4_END    (19)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_5_START  (20)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_5_END    (23)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_6_START  (24)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_6_END    (27)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_7_START  (28)
#define SOC_DSS_IFBC_IFBC_MEM_CTRL_ifbc_mem_ctrl_7_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_IFBC_IFBC_INSERT_UNION
 �ṹ˵��  : IFBC_INSERT �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  insert_byte_num : 16; /* bit[0-15] : ѹ������ÿ�β����������ݵĸ��� */
        unsigned int  insert_byte     : 16; /* bit[16-31]: ѹ������ÿ�в����������ݵ�byteλ�� */
    } reg;
} SOC_DSS_IFBC_IFBC_INSERT_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_INSERT_insert_byte_num_START  (0)
#define SOC_DSS_IFBC_IFBC_INSERT_insert_byte_num_END    (15)
#define SOC_DSS_IFBC_IFBC_INSERT_insert_byte_START      (16)
#define SOC_DSS_IFBC_IFBC_INSERT_insert_byte_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_IFBC_HIMAX_TEST_MODE_UNION
 �ṹ˵��  : HIMAX_TEST_MODE �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x00000008�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  force_pat_ext_mode : 1;  /* bit[0]   : The compression is forced to only use "RGB truncation mode", default is disable. */
        unsigned int  force_pat_mode     : 1;  /* bit[1]   : The compression is forced to only use "pattern mode", default is disable. */
        unsigned int  force_yuv_mode     : 1;  /* bit[2]   : The compression is forced to only use "YUV truncation mode", default is disable. */
        unsigned int  mcmp_pat_ext_en    : 1;  /* bit[3]   : Use "RGB truncation mode" during compression, default is enable */
        unsigned int  reserved           : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_DSS_IFBC_HIMAX_TEST_MODE_UNION;
#endif
#define SOC_DSS_IFBC_HIMAX_TEST_MODE_force_pat_ext_mode_START  (0)
#define SOC_DSS_IFBC_HIMAX_TEST_MODE_force_pat_ext_mode_END    (0)
#define SOC_DSS_IFBC_HIMAX_TEST_MODE_force_pat_mode_START      (1)
#define SOC_DSS_IFBC_HIMAX_TEST_MODE_force_pat_mode_END        (1)
#define SOC_DSS_IFBC_HIMAX_TEST_MODE_force_yuv_mode_START      (2)
#define SOC_DSS_IFBC_HIMAX_TEST_MODE_force_yuv_mode_END        (2)
#define SOC_DSS_IFBC_HIMAX_TEST_MODE_mcmp_pat_ext_en_START     (3)
#define SOC_DSS_IFBC_HIMAX_TEST_MODE_mcmp_pat_ext_en_END       (3)


/*****************************************************************************
 �ṹ��    : SOC_DSS_IFBC_IFBC_CORE_GT_UNION
 �ṹ˵��  : IFBC_CORE_GT �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ifbc_core_1_gt   : 2;  /* bit[0-1]  : �üĴ������ڿ����Ƿ�����orise3x��ʼ�����У�
                                                            00��ʹ��orise ctr��ʼ�����У��Ƽ����ã���
                                                            10����ʹ��orise ctr��ʼ�����У�
                                                            01,11�������� */
        unsigned int  ifbc_core_2_gt   : 2;  /* bit[2-3]  : [1]��1'b1 ��ʾ��IFBC�Ĺ���ʱ��������ſأ�1'b0 ��ʾ��IFBC�Ĺ���ʱ����Ӳ���Զ����ƣ�
                                                            [0]��1'b0 ��ʾ��IFBC����ʱ�����У�1'b1 ��ʾ��IFBC����ʱ�ӹرգ� */
        unsigned int  ifbc_core_2_gt_h : 2;  /* bit[4-5]  : [1]��1'b1 ��ʾ��IFBC�Ĺ���ʱ��������ſأ�1'b0 ��ʾ��IFBC�Ĺ���ʱ����Ӳ���Զ����ƣ�
                                                            [0]��1'b0 ��ʾ��IFBC����ʱ�����У�1'b1 ��ʾ��IFBC����ʱ�ӹرգ� */
        unsigned int  ifbc_core_2_gt_o : 2;  /* bit[6-7]  : [1]��1'b1 ��ʾ��IFBC�Ĺ���ʱ��������ſأ�1'b0 ��ʾ��IFBC�Ĺ���ʱ����Ӳ���Զ����ƣ�
                                                            [0]��1'b0 ��ʾ��IFBC����ʱ�����У�1'b1 ��ʾ��IFBC����ʱ�ӹرգ� */
        unsigned int  ifbc_core_2_gt_n : 2;  /* bit[8-9]  : [1]��1'b1 ��ʾ��IFBC�Ĺ���ʱ��������ſأ�1'b0 ��ʾ��IFBC�Ĺ���ʱ����Ӳ���Զ����ƣ�
                                                            [0]��1'b0 ��ʾ��IFBC����ʱ�����У�1'b1 ��ʾ��IFBC����ʱ�ӹرգ� */
        unsigned int  ifbc_core_4_gt   : 2;  /* bit[10-11]: [1]�� 1'b1 ��ʾ��IFBC�Ĺ���ʱ��������ſأ�1'b0 ��ʾ��IFBC�Ĺ���ʱ����Ӳ���Զ����ƣ�
                                                            [0]��1'b0 ��ʾ��IFBC����ʱ�����У�1'b1 ��ʾ��IFBC����ʱ�ӹرգ� */
        unsigned int  reserved         : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_DSS_IFBC_IFBC_CORE_GT_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_1_gt_START    (0)
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_1_gt_END      (1)
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_2_gt_START    (2)
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_2_gt_END      (3)
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_2_gt_h_START  (4)
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_2_gt_h_END    (5)
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_2_gt_o_START  (6)
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_2_gt_o_END    (7)
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_2_gt_n_START  (8)
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_2_gt_n_END    (9)
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_4_gt_START    (10)
#define SOC_DSS_IFBC_IFBC_CORE_GT_ifbc_core_4_gt_END      (11)


/*****************************************************************************
 �ṹ��    : SOC_DSS_IFBC_IFBC_PM_CTRL_UNION
 �ṹ˵��  : IFBC_PM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x002C����ֵ:0x80FFFFFF�����:32
 �Ĵ���˵��: MEM�͹��Ŀ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ifbc_pm_ctrl : 32; /* bit[0-31]: [31] mem_ctrl_auto_en , �Զ�ģʽ���������ģʽѡ��,1�Զ�ģʽ��0�������ģʽ 
                                                       [30] slp_mode ģʽѡ��1 slpģʽ��0 dslpģʽ 
                                                       [29:24] reserved
                                                       [23:21] SLP/DSLPģʽt(d)slp��ʱ�Ĵ��� 
                                                       [20:18] SLP/DSLPģʽt(d)slpx��ʱ�Ĵ��� 
                                                       [17:15] SLP/DSLPģʽtx(d)slp��ʱ�Ĵ��� 
                                                       [14:12] SLP/DSLPģʽt(d)slpwk��ʱ�Ĵ��� 
                                                       [11:9] SDģʽtsd��ʱ�Ĵ��� 
                                                       [8:6] SDģʽtsdx��ʱ�Ĵ��� 
                                                       [5:3] SDģʽtxsd��ʱ�Ĵ��� 
                                                       [2:0] SDģʽtsdwk��ʱ�Ĵ��� */
    } reg;
} SOC_DSS_IFBC_IFBC_PM_CTRL_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_PM_CTRL_ifbc_pm_ctrl_START  (0)
#define SOC_DSS_IFBC_IFBC_PM_CTRL_ifbc_pm_ctrl_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_IFBC_IFBC_RD_SHADOW_UNION
 �ṹ˵��  : IFBC_RD_SHADOW �Ĵ����ṹ���塣��ַƫ����:0x0030����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��Ӱ�ӼĴ���ѡ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ifbc_rd_shadow : 1;  /* bit[0]   : 1'b0 :�������Ĵ���
                                                         1'b1 :��Ӱ�ӼĴ��� */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_IFBC_IFBC_RD_SHADOW_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_RD_SHADOW_ifbc_rd_shadow_START  (0)
#define SOC_DSS_IFBC_IFBC_RD_SHADOW_ifbc_rd_shadow_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_IFBC_ORISE_CTL_UNION
 �ṹ˵��  : ORISE_CTL �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x00000000�����:32
 �Ĵ���˵��: Orise���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  i_param_value : 8;  /* bit[0-7]  : setting for internal */
        unsigned int  i_param_addr  : 8;  /* bit[8-15] : setting for internal */
        unsigned int  reserved      : 16; /* bit[16-31]:  */
    } reg;
} SOC_DSS_IFBC_ORISE_CTL_UNION;
#endif
#define SOC_DSS_IFBC_ORISE_CTL_i_param_value_START  (0)
#define SOC_DSS_IFBC_ORISE_CTL_i_param_value_END    (7)
#define SOC_DSS_IFBC_ORISE_CTL_i_param_addr_START   (8)
#define SOC_DSS_IFBC_ORISE_CTL_i_param_addr_END     (15)


/*****************************************************************************
 �ṹ��    : SOC_DSS_IFBC_ORSISE_DEBUG0_UNION
 �ṹ˵��  : ORSISE_DEBUG0 �Ĵ����ṹ���塣��ַƫ����:0x0038����ֵ:0x00000000�����:32
 �Ĵ���˵��: Orise debug�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  orise_debug_l : 32; /* bit[0-31]: debug */
    } reg;
} SOC_DSS_IFBC_ORSISE_DEBUG0_UNION;
#endif
#define SOC_DSS_IFBC_ORSISE_DEBUG0_orise_debug_l_START  (0)
#define SOC_DSS_IFBC_ORSISE_DEBUG0_orise_debug_l_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_IFBC_ORSISE_DEBUG1_UNION
 �ṹ˵��  : ORSISE_DEBUG1 �Ĵ����ṹ���塣��ַƫ����:0x003C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Orise debug�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  orise_debug_h : 32; /* bit[0-31]: debug */
    } reg;
} SOC_DSS_IFBC_ORSISE_DEBUG1_UNION;
#endif
#define SOC_DSS_IFBC_ORSISE_DEBUG1_orise_debug_h_START  (0)
#define SOC_DSS_IFBC_ORSISE_DEBUG1_orise_debug_h_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_IFBC_rsp_comp_test_UNION
 �ṹ˵��  : rsp_comp_test �Ĵ����ṹ���塣��ַƫ����:0x0040����ֵ:0x00000000�����:32
 �Ĵ���˵��: RSP�����ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rsp_comp_test : 4;  /* bit[0-3] : RSP�����źţ�Ĭ��Ϊ0 */
        unsigned int  reserved      : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_DSS_IFBC_rsp_comp_test_UNION;
#endif
#define SOC_DSS_IFBC_rsp_comp_test_rsp_comp_test_START  (0)
#define SOC_DSS_IFBC_rsp_comp_test_rsp_comp_test_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_DSS_IFBC_IFBC_CLK_SEL_UNION
 �ṹ˵��  : IFBC_CLK_SEL �Ĵ����ṹ���塣��ַƫ����:0x044����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: һ��ģ��ʱ��ѡ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ifbc_clk_sel : 32; /* bit[0-31]: ��һ��ģ���ʱ��ѡ���źţ�
                                                       1����ʾǿ�ƴ�ʱ�ӡ�
                                                       0����ʾ��Ҫ���������Ӳ����ʱ��ʹ����������ر�ʱ��
                                                       bit0������apb��
                                                       bit1������reg�� */
    } reg;
} SOC_DSS_IFBC_IFBC_CLK_SEL_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_CLK_SEL_ifbc_clk_sel_START  (0)
#define SOC_DSS_IFBC_IFBC_CLK_SEL_ifbc_clk_sel_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_IFBC_IFBC_CLK_EN_UNION
 �ṹ˵��  : IFBC_CLK_EN �Ĵ����ṹ���塣��ַƫ����:0x048����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: һ��ģ��ʱ��ʹ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ifbc_clk_en : 32; /* bit[0-31]: ��һ��ģ������ʱ��ʹ���ź�
                                                      1����ʾ���ʱ��ʹ����Ч������Ӳ������
                                                      0����ʾ���ʱ��ʹ����Ч����ֹӲ������
                                                      ���� */
    } reg;
} SOC_DSS_IFBC_IFBC_CLK_EN_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_CLK_EN_ifbc_clk_en_START  (0)
#define SOC_DSS_IFBC_IFBC_CLK_EN_ifbc_clk_en_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_IFBC_IFBC_PAD_UNION
 �ṹ˵��  : IFBC_PAD �Ĵ����ṹ���塣��ַƫ����:0x004C����ֵ:0x00000000�����:32
 �Ĵ���˵��: PAD�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  num_pad  : 3;  /* bit[0-2] : ĩβpadding��������Ŀ */
        unsigned int  reserved : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_DSS_IFBC_IFBC_PAD_UNION;
#endif
#define SOC_DSS_IFBC_IFBC_PAD_num_pad_START   (0)
#define SOC_DSS_IFBC_IFBC_PAD_num_pad_END     (2)


/*****************************************************************************
 �ṹ��    : SOC_DSS_IFBC_REG_DEFAULT_UNION
 �ṹ˵��  : REG_DEFAULT �Ĵ����ṹ���塣��ַƫ����:0x0050����ֵ:0x00000000�����:32
 �Ĵ���˵��: ģ��Ӱ�ӼĴ����ָ���Ĭ��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg_default : 1;  /* bit[0]   : ģ������Ӱ�ӼĴ����ָ���Ĭ��ֵ������Ч */
        unsigned int  reserved    : 31; /* bit[1-31]:  */
    } reg;
} SOC_DSS_IFBC_REG_DEFAULT_UNION;
#endif
#define SOC_DSS_IFBC_REG_DEFAULT_reg_default_START  (0)
#define SOC_DSS_IFBC_REG_DEFAULT_reg_default_END    (0)






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

#endif /* end of soc_dss_ifbc_interface.h */
