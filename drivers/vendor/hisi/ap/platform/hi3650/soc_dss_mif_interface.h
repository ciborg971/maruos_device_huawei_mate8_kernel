/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_dss_mif_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:20:13
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_DSS_MIF.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_DSS_MIF_INTERFACE_H__
#define __SOC_DSS_MIF_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_MIF
 ****************************************************************************/
/* �Ĵ���˵����MIFȫ�ֿ��ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_MIF_MIF_ENABLE_UNION */
#define SOC_DSS_MIF_MIF_ENABLE_ADDR(base)             ((base) + (0x0000))

/* �Ĵ���˵����MEM�͹��Ŀ��ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_MIF_MIF_MEM_CTRL_UNION */
#define SOC_DSS_MIF_MIF_MEM_CTRL_ADDR(base)           ((base) + (0x0004))

/* �Ĵ���˵����MMU_CTRL���ƼĴ���0
   λ����UNION�ṹ:  SOC_DSS_MIF_MIF_CTRL0_UNION */
#define SOC_DSS_MIF_MIF_CTRL0_ADDR(base, j)           ((base) + (0x0000+32*(j)))

/* �Ĵ���˵����MMU_CTRL���ƼĴ���1
   λ����UNION�ṹ:  SOC_DSS_MIF_MIF_CTRL1_UNION */
#define SOC_DSS_MIF_MIF_CTRL1_ADDR(base, j)           ((base) + (0x0004+32*(j)))

/* �Ĵ���˵����MMU_CTRL���ƼĴ���2
   λ����UNION�ṹ:  SOC_DSS_MIF_MIF_CTRL2_UNION */
#define SOC_DSS_MIF_MIF_CTRL2_ADDR(base, j)           ((base) + (0x0008+32*(j)))

/* �Ĵ���˵����MMU_CTRL���ƼĴ���3
   λ����UNION�ṹ:  SOC_DSS_MIF_MIF_CTRL3_UNION */
#define SOC_DSS_MIF_MIF_CTRL3_ADDR(base, j)           ((base) + (0x000C+32*(j)))

/* �Ĵ���˵����MMU_CTRL���ƼĴ���4
   λ����UNION�ṹ:  SOC_DSS_MIF_MIF_CTRL4_UNION */
#define SOC_DSS_MIF_MIF_CTRL4_ADDR(base, j)           ((base) + (0x0010+32*(j)))

/* �Ĵ���˵����MMU_CTRL���ƼĴ���5
   λ����UNION�ṹ:  SOC_DSS_MIF_MIF_CTRL5_UNION */
#define SOC_DSS_MIF_MIF_CTRL5_ADDR(base, j)           ((base) + (0x0014+32*(j)))

/* �Ĵ���˵����MMU_CTRL״̬�Ĵ���0
   λ����UNION�ṹ:  SOC_DSS_MIF_MIF_STAT0_UNION */
#define SOC_DSS_MIF_MIF_STAT0_ADDR(base, k)           ((base) + (0x0160+16*(k)))

/* �Ĵ���˵����MMU_CTRL״̬�Ĵ���1
   λ����UNION�ṹ:  SOC_DSS_MIF_MIF_STAT1_UNION */
#define SOC_DSS_MIF_MIF_STAT1_ADDR(base, k)           ((base) + (0x0164+16*(k)))

/* �Ĵ���˵����MMU_CTRL״̬�Ĵ���2
   λ����UNION�ṹ:  SOC_DSS_MIF_MIF_STAT2_UNION */
#define SOC_DSS_MIF_MIF_STAT2_ADDR(base, k)           ((base) + (0x0168+16*(k)))

/* �Ĵ���˵����ģ��Ӱ�ӼĴ����ָ���Ĭ��ֵ
   λ����UNION�ṹ:  SOC_DSS_MIF_REG_DEFAULT_UNION */
#define SOC_DSS_MIF_REG_DEFAULT_ADDR(base)            ((base) + (0x0500))

/* �Ĵ���˵����Ӱ�ӼĴ�����ѡ��Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MIF_MIF_SHADOW_READ_UNION */
#define SOC_DSS_MIF_MIF_SHADOW_READ_ADDR(base)        ((base) + (0x0504))

/* �Ĵ���˵����Ӱ�ӼĴ�����ѡ��Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MIF_MIF_CLK_CTL_UNION */
#define SOC_DSS_MIF_MIF_CLK_CTL_ADDR(base)            ((base) + (0x0508))





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
                     (1/1) reg_MIF
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_DSS_MIF_MIF_ENABLE_UNION
 �ṹ˵��  : MIF_ENABLE �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: MIFȫ�ֿ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enable      : 1;  /* bit[0]   : MIFʹ���źţ�
                                                      1��ʹ��
                                                      0����ֹ */
        unsigned int  tagcache_en : 1;  /* bit[1]   : tag compare cacheʹ�ܣ�
                                                      1��ʹ��
                                                      0����ֹ */
        unsigned int  reserved    : 30; /* bit[2-31]:  */
    } reg;
} SOC_DSS_MIF_MIF_ENABLE_UNION;
#endif
#define SOC_DSS_MIF_MIF_ENABLE_enable_START       (0)
#define SOC_DSS_MIF_MIF_ENABLE_enable_END         (0)
#define SOC_DSS_MIF_MIF_ENABLE_tagcache_en_START  (1)
#define SOC_DSS_MIF_MIF_ENABLE_tagcache_en_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MIF_MIF_MEM_CTRL_UNION
 �ṹ˵��  : MIF_MEM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x01A80050�����:32
 �Ĵ���˵��: MEM�͹��Ŀ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mif_mem_ctrl_s : 16; /* bit[0-15] : Single Port����MEM�͹����������ģʽ����Ч��
                                                          [6:5]: WTSEL,Ĭ��Ϊ2'b10;
                                                          [4:3]: RTSEL,Ĭ��Ϊ2'b10;
                                                          [2]: Ϊ1��ʾ����Shut Downģʽ
                                                          [1]: Ϊ1��ʾ����Deep Sleepģʽ
                                                          [0]: Ϊ1��ʾ����Sleepģʽ */
        unsigned int  mif_mem_ctrl_t : 16; /* bit[16-31]: Two Port����MEM�͹����������ģʽ����Ч��
                                                          [9:7]: KP,Ĭ��Ϊ3'b011;
                                                          [6:5]: WCT,Ĭ��Ϊ2'b01;
                                                          [4:3]: RCT,Ĭ��Ϊ2'b01;
                                                          [2]: Ϊ1��ʾ����Shut Downģʽ
                                                          [1]: Ϊ1��ʾ����Deep Sleepģʽ
                                                          [0]: Ϊ1��ʾ����Sleepģʽ */
    } reg;
} SOC_DSS_MIF_MIF_MEM_CTRL_UNION;
#endif
#define SOC_DSS_MIF_MIF_MEM_CTRL_mif_mem_ctrl_s_START  (0)
#define SOC_DSS_MIF_MIF_MEM_CTRL_mif_mem_ctrl_s_END    (15)
#define SOC_DSS_MIF_MIF_MEM_CTRL_mif_mem_ctrl_t_START  (16)
#define SOC_DSS_MIF_MIF_MEM_CTRL_mif_mem_ctrl_t_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MIF_MIF_CTRL0_UNION
 �ṹ˵��  : MIF_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x0000+32*(j)����ֵ:0x00000000�����:32
 �Ĵ���˵��: MMU_CTRL���ƼĴ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctrl_en  : 1;  /* bit[0]   : 1��ͨ��ʹ��
                                                   0��ͨ����ֹ */
        unsigned int  reserved : 31; /* bit[1-31]:  */
    } reg;
} SOC_DSS_MIF_MIF_CTRL0_UNION;
#endif
#define SOC_DSS_MIF_MIF_CTRL0_ctrl_en_START   (0)
#define SOC_DSS_MIF_MIF_CTRL0_ctrl_en_END     (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MIF_MIF_CTRL1_UNION
 �ṹ˵��  : MIF_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x0004+32*(j)����ֵ:0x00000020�����:32
 �Ĵ���˵��: MMU_CTRL���ƼĴ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sid         : 4;  /* bit[0-3]  : sid��ţ�0~15 */
        unsigned int  qos_en      : 1;  /* bit[4]    : Ԥȡqosʹ���źţ�
                                                       1��ʹ��
                                                       0����ֹ */
        unsigned int  bypass      : 1;  /* bit[5]    : 1��bypass
                                                       0��normal */
        unsigned int  reserved_0  : 4;  /* bit[6-9]  :  */
        unsigned int  invalid_sel : 2;  /* bit[10-11]: TAG invalid���ԣ�
                                                       2'b00��VA��ת���µ�TAG,
                                                       2'b01��tag�Ƚ�ʱ���Ҷ˵�(��)
                                                       2'b10����һ��TAG�����tag�Ƚ�ʱ����˵�(С)
                                                       2'b11�� */
        unsigned int  reserved_1  : 5;  /* bit[12-16]:  */
        unsigned int  rw_type     : 1;  /* bit[17]   : 1��дͨ��
                                                       0����ͨ�� */
        unsigned int  initial_en  : 1;  /* bit[18]   : 1��Ԥȡinitialʹ��
                                                       0��Ԥȡinitial��ֹ */
        unsigned int  pref_va_ctl : 1;  /* bit[19]   : va��pref_va��˳�����.Сͼ��תʱ��Ԥȡ����ʵVA����֮����ܻ�������ҡ�1����֤Ԥȡ����ʵVA����֮���˳��. */
        unsigned int  reserved_2  : 12; /* bit[20-31]:  */
    } reg;
} SOC_DSS_MIF_MIF_CTRL1_UNION;
#endif
#define SOC_DSS_MIF_MIF_CTRL1_sid_START          (0)
#define SOC_DSS_MIF_MIF_CTRL1_sid_END            (3)
#define SOC_DSS_MIF_MIF_CTRL1_qos_en_START       (4)
#define SOC_DSS_MIF_MIF_CTRL1_qos_en_END         (4)
#define SOC_DSS_MIF_MIF_CTRL1_bypass_START       (5)
#define SOC_DSS_MIF_MIF_CTRL1_bypass_END         (5)
#define SOC_DSS_MIF_MIF_CTRL1_invalid_sel_START  (10)
#define SOC_DSS_MIF_MIF_CTRL1_invalid_sel_END    (11)
#define SOC_DSS_MIF_MIF_CTRL1_rw_type_START      (17)
#define SOC_DSS_MIF_MIF_CTRL1_rw_type_END        (17)
#define SOC_DSS_MIF_MIF_CTRL1_initial_en_START   (18)
#define SOC_DSS_MIF_MIF_CTRL1_initial_en_END     (18)
#define SOC_DSS_MIF_MIF_CTRL1_pref_va_ctl_START  (19)
#define SOC_DSS_MIF_MIF_CTRL1_pref_va_ctl_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MIF_MIF_CTRL2_UNION
 �ṹ˵��  : MIF_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0x0008+32*(j)����ֵ:0x00000000�����:32
 �Ĵ���˵��: MMU_CTRL���ƼĴ���2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stride0  : 20; /* bit[0-19] : ��λ4KB��ͼ��֡stride */
        unsigned int  reserved : 12; /* bit[20-31]:  */
    } reg;
} SOC_DSS_MIF_MIF_CTRL2_UNION;
#endif
#define SOC_DSS_MIF_MIF_CTRL2_stride0_START   (0)
#define SOC_DSS_MIF_MIF_CTRL2_stride0_END     (19)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MIF_MIF_CTRL3_UNION
 �ṹ˵��  : MIF_CTRL3 �Ĵ����ṹ���塣��ַƫ����:0x000C+32*(j)����ֵ:0x00000000�����:32
 �Ĵ���˵��: MMU_CTRL���ƼĴ���3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stride1  : 20; /* bit[0-19] : ��λ4KB��ͼ��֡stride */
        unsigned int  reserved : 12; /* bit[20-31]:  */
    } reg;
} SOC_DSS_MIF_MIF_CTRL3_UNION;
#endif
#define SOC_DSS_MIF_MIF_CTRL3_stride1_START   (0)
#define SOC_DSS_MIF_MIF_CTRL3_stride1_END     (19)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MIF_MIF_CTRL4_UNION
 �ṹ˵��  : MIF_CTRL4 �Ĵ����ṹ���塣��ַƫ����:0x0010+32*(j)����ֵ:0x00000000�����:32
 �Ĵ���˵��: MMU_CTRL���ƼĴ���4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stride2  : 20; /* bit[0-19] : ��λ4KB��ͼ��֡stride */
        unsigned int  reserved : 12; /* bit[20-31]:  */
    } reg;
} SOC_DSS_MIF_MIF_CTRL4_UNION;
#endif
#define SOC_DSS_MIF_MIF_CTRL4_stride2_START   (0)
#define SOC_DSS_MIF_MIF_CTRL4_stride2_END     (19)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MIF_MIF_CTRL5_UNION
 �ṹ˵��  : MIF_CTRL5 �Ĵ����ṹ���塣��ַƫ����:0x0014+32*(j)����ֵ:0x00000000�����:32
 �Ĵ���˵��: MMU_CTRL���ƼĴ���5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stride3  : 20; /* bit[0-19] : ��λ4KB��ͼ��֡stride */
        unsigned int  reserved : 12; /* bit[20-31]:  */
    } reg;
} SOC_DSS_MIF_MIF_CTRL5_UNION;
#endif
#define SOC_DSS_MIF_MIF_CTRL5_stride3_START   (0)
#define SOC_DSS_MIF_MIF_CTRL5_stride3_END     (19)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MIF_MIF_STAT0_UNION
 �ṹ˵��  : MIF_STAT0 �Ĵ����ṹ���塣��ַƫ����:0x0160+16*(k)����ֵ:0x00000000�����:32
 �Ĵ���˵��: MMU_CTRL״̬�Ĵ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tag_status : 32; /* bit[0-31]: ÿ��tag������״̬ */
    } reg;
} SOC_DSS_MIF_MIF_STAT0_UNION;
#endif
#define SOC_DSS_MIF_MIF_STAT0_tag_status_START  (0)
#define SOC_DSS_MIF_MIF_STAT0_tag_status_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MIF_MIF_STAT1_UNION
 �ṹ˵��  : MIF_STAT1 �Ĵ����ṹ���塣��ַƫ����:0x0164+16*(k)����ֵ:0x00008400�����:32
 �Ĵ���˵��: MMU_CTRL״̬�Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pref_ostd   : 5;  /* bit[0-4]  : ��ǰԤȡindex���� */
        unsigned int  index_ostd  : 5;  /* bit[5-9]  : ��ǰ��Чindex������ */
        unsigned int  pref_state  : 5;  /* bit[10-14]: ��ǰԤȡ״̬��״̬ */
        unsigned int  fetch_state : 4;  /* bit[15-18]: ��ǰʵȡ״̬��״̬ */
        unsigned int  reserved    : 13; /* bit[19-31]:  */
    } reg;
} SOC_DSS_MIF_MIF_STAT1_UNION;
#endif
#define SOC_DSS_MIF_MIF_STAT1_pref_ostd_START    (0)
#define SOC_DSS_MIF_MIF_STAT1_pref_ostd_END      (4)
#define SOC_DSS_MIF_MIF_STAT1_index_ostd_START   (5)
#define SOC_DSS_MIF_MIF_STAT1_index_ostd_END     (9)
#define SOC_DSS_MIF_MIF_STAT1_pref_state_START   (10)
#define SOC_DSS_MIF_MIF_STAT1_pref_state_END     (14)
#define SOC_DSS_MIF_MIF_STAT1_fetch_state_START  (15)
#define SOC_DSS_MIF_MIF_STAT1_fetch_state_END    (18)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MIF_MIF_STAT2_UNION
 �ṹ˵��  : MIF_STAT2 �Ĵ����ṹ���塣��ַƫ����:0x0168+16*(k)����ֵ:0x00000000�����:32
 �Ĵ���˵��: MMU_CTRL״̬�Ĵ���2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pref_tag_hit  : 16; /* bit[0-15] : ��ǰԤȡ����ֵ�� */
        unsigned int  fetch_tag_hit : 16; /* bit[16-31]: ��ǰʵȡ����ֵ�� */
    } reg;
} SOC_DSS_MIF_MIF_STAT2_UNION;
#endif
#define SOC_DSS_MIF_MIF_STAT2_pref_tag_hit_START   (0)
#define SOC_DSS_MIF_MIF_STAT2_pref_tag_hit_END     (15)
#define SOC_DSS_MIF_MIF_STAT2_fetch_tag_hit_START  (16)
#define SOC_DSS_MIF_MIF_STAT2_fetch_tag_hit_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MIF_REG_DEFAULT_UNION
 �ṹ˵��  : REG_DEFAULT �Ĵ����ṹ���塣��ַƫ����:0x0500����ֵ:0x00000000�����:32
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
} SOC_DSS_MIF_REG_DEFAULT_UNION;
#endif
#define SOC_DSS_MIF_REG_DEFAULT_reg_default_START  (0)
#define SOC_DSS_MIF_REG_DEFAULT_reg_default_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MIF_MIF_SHADOW_READ_UNION
 �ṹ˵��  : MIF_SHADOW_READ �Ĵ����ṹ���塣��ַƫ����:0x0504����ֵ:0x00000000�����:32
 �Ĵ���˵��: Ӱ�ӼĴ�����ѡ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mif_rd_shadow : 1;  /* bit[0]   : 1'b0 :�������Ĵ���
                                                        1'b1 :��Ӱ�ӼĴ��� */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_MIF_MIF_SHADOW_READ_UNION;
#endif
#define SOC_DSS_MIF_MIF_SHADOW_READ_mif_rd_shadow_START  (0)
#define SOC_DSS_MIF_MIF_SHADOW_READ_mif_rd_shadow_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MIF_MIF_CLK_CTL_UNION
 �ṹ˵��  : MIF_CLK_CTL �Ĵ����ṹ���塣��ַƫ����:0x0508����ֵ:0x00000003�����:32
 �Ĵ���˵��: Ӱ�ӼĴ�����ѡ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  clk_en   : 1;  /* bit[0]   : MIFģ������ʱ��ʹ���ź�
                                                   1����ʾ���ʱ��ʹ����Ч������Ӳ������
                                                   0����ʾ���ʱ��ʹ����Ч����ֹӲ������ */
        unsigned int  clk_sel  : 1;  /* bit[1]   : MIFģ���ʱ��ѡ���źţ�
                                                   1����ʾǿ�ƴ�ʱ�ӡ�
                                                   0����ʾ��Ҫ���������Ӳ����ʱ��ʹ����������ر�ʱ�� */
        unsigned int  reserved : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_DSS_MIF_MIF_CLK_CTL_UNION;
#endif
#define SOC_DSS_MIF_MIF_CLK_CTL_clk_en_START    (0)
#define SOC_DSS_MIF_MIF_CLK_CTL_clk_en_END      (0)
#define SOC_DSS_MIF_MIF_CLK_CTL_clk_sel_START   (1)
#define SOC_DSS_MIF_MIF_CLK_CTL_clk_sel_END     (1)






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

#endif /* end of soc_dss_mif_interface.h */
