/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_isp_lsc_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:22:00
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_ISP_LSC.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_ISP_LSC_INTERFACE_H__
#define __SOC_ISP_LSC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) LSC
 ****************************************************************************/
/* �Ĵ���˵����LSC control
   λ����UNION�ṹ:  SOC_ISP_LSC_LSC_CTRL_UNION */
#define SOC_ISP_LSC_LSC_CTRL_ADDR(base)               ((base) + (0x0000))

/* �Ĵ���˵����red ram address
   λ����UNION�ṹ:  SOC_ISP_LSC_LSC_R_TABLE_ADDR_UNION */
#define SOC_ISP_LSC_LSC_R_TABLE_ADDR_ADDR(base)       ((base) + (0x0004))

/* �Ĵ���˵����green-red ram address
   λ����UNION�ṹ:  SOC_ISP_LSC_LSC_GR_TABLE_ADDR_UNION */
#define SOC_ISP_LSC_LSC_GR_TABLE_ADDR_ADDR(base)      ((base) + (0x0008))

/* �Ĵ���˵����blue ram address
   λ����UNION�ṹ:  SOC_ISP_LSC_LSC_B_TABLE_ADDR_UNION */
#define SOC_ISP_LSC_LSC_B_TABLE_ADDR_ADDR(base)       ((base) + (0x000C))

/* �Ĵ���˵����green-blue ram address
   λ����UNION�ṹ:  SOC_ISP_LSC_LSC_GB_TABLE_ADDR_UNION */
#define SOC_ISP_LSC_LSC_GB_TABLE_ADDR_ADDR(base)      ((base) + (0x0010))

/* �Ĵ���˵����Sample table red
   λ����UNION�ṹ:  SOC_ISP_LSC_LSC_R_TABLE_DATA_UNION */
#define SOC_ISP_LSC_LSC_R_TABLE_DATA_ADDR(base)       ((base) + (0x0014))

/* �Ĵ���˵����Sample table gren - red
   λ����UNION�ṹ:  SOC_ISP_LSC_LSC_GR_TABLE_DATA_UNION */
#define SOC_ISP_LSC_LSC_GR_TABLE_DATA_ADDR(base)      ((base) + (0x0018))

/* �Ĵ���˵����Sample table blue
   λ����UNION�ṹ:  SOC_ISP_LSC_LSC_B_TABLE_DATA_UNION */
#define SOC_ISP_LSC_LSC_B_TABLE_DATA_ADDR(base)       ((base) + (0x001C))

/* �Ĵ���˵����Sample table green blue
   λ����UNION�ṹ:  SOC_ISP_LSC_LSC_GB_TABLE_DATA_UNION */
#define SOC_ISP_LSC_LSC_GB_TABLE_DATA_ADDR(base)      ((base) + (0x0020))

/* �Ĵ���˵����Gradient table x
   λ����UNION�ṹ:  SOC_ISP_LSC_LSC_XGRAD_0_1_UNION */
#define SOC_ISP_LSC_LSC_XGRAD_0_1_ADDR(base)          ((base) + (0x0024))

/* �Ĵ���˵����Gradient table x
   λ����UNION�ṹ:  SOC_ISP_LSC_LSC_XGRAD_2_3_UNION */
#define SOC_ISP_LSC_LSC_XGRAD_2_3_ADDR(base)          ((base) + (0x0028))

/* �Ĵ���˵����Gradient table x
   λ����UNION�ṹ:  SOC_ISP_LSC_LSC_XGRAD_4_5_UNION */
#define SOC_ISP_LSC_LSC_XGRAD_4_5_ADDR(base)          ((base) + (0x002C))

/* �Ĵ���˵����Gradient table x
   λ����UNION�ṹ:  SOC_ISP_LSC_LSC_XGRAD_6_7_UNION */
#define SOC_ISP_LSC_LSC_XGRAD_6_7_ADDR(base)          ((base) + (0x0030))

/* �Ĵ���˵����Gradient table x
   λ����UNION�ṹ:  SOC_ISP_LSC_LSC_XGRAD_8_9_UNION */
#define SOC_ISP_LSC_LSC_XGRAD_8_9_ADDR(base)          ((base) + (0x0034))

/* �Ĵ���˵����Gradient table x
   λ����UNION�ṹ:  SOC_ISP_LSC_LSC_XGRAD_10_UNION */
#define SOC_ISP_LSC_LSC_XGRAD_10_ADDR(base)           ((base) + (0x0038))

/* �Ĵ���˵����Gradient table y
   λ����UNION�ṹ:  SOC_ISP_LSC_LSC_YGRAD_0_1_UNION */
#define SOC_ISP_LSC_LSC_YGRAD_0_1_ADDR(base)          ((base) + (0x003C))

/* �Ĵ���˵����Gradient table y
   λ����UNION�ṹ:  SOC_ISP_LSC_LSC_YGRAD_2_3_UNION */
#define SOC_ISP_LSC_LSC_YGRAD_2_3_ADDR(base)          ((base) + (0x0040))

/* �Ĵ���˵����Gradient table y
   λ����UNION�ṹ:  SOC_ISP_LSC_LSC_YGRAD_4_5_UNION */
#define SOC_ISP_LSC_LSC_YGRAD_4_5_ADDR(base)          ((base) + (0x0044))

/* �Ĵ���˵����Gradient table y
   λ����UNION�ṹ:  SOC_ISP_LSC_LSC_YGRAD_6_7_UNION */
#define SOC_ISP_LSC_LSC_YGRAD_6_7_ADDR(base)          ((base) + (0x0048))

/* �Ĵ���˵����size table
   λ����UNION�ṹ:  SOC_ISP_LSC_LSC_XSIZE_0_1_UNION */
#define SOC_ISP_LSC_LSC_XSIZE_0_1_ADDR(base)          ((base) + (0x004C))

/* �Ĵ���˵����size table
   λ����UNION�ṹ:  SOC_ISP_LSC_LSC_XSIZE_2_3_UNION */
#define SOC_ISP_LSC_LSC_XSIZE_2_3_ADDR(base)          ((base) + (0x0050))

/* �Ĵ���˵����size table
   λ����UNION�ṹ:  SOC_ISP_LSC_LSC_XSIZE_4_5_UNION */
#define SOC_ISP_LSC_LSC_XSIZE_4_5_ADDR(base)          ((base) + (0x0054))

/* �Ĵ���˵����size table
   λ����UNION�ṹ:  SOC_ISP_LSC_LSC_XSIZE_6_7_UNION */
#define SOC_ISP_LSC_LSC_XSIZE_6_7_ADDR(base)          ((base) + (0x0058))

/* �Ĵ���˵����size table
   λ����UNION�ṹ:  SOC_ISP_LSC_LSC_XSIZE_8_9_UNION */
#define SOC_ISP_LSC_LSC_XSIZE_8_9_ADDR(base)          ((base) + (0x005C))

/* �Ĵ���˵����size table
   λ����UNION�ṹ:  SOC_ISP_LSC_LSC_XSIZE_10_UNION */
#define SOC_ISP_LSC_LSC_XSIZE_10_ADDR(base)           ((base) + (0x0060))

/* �Ĵ���˵����size table
   λ����UNION�ṹ:  SOC_ISP_LSC_LSC_YSIZE_0_1_UNION */
#define SOC_ISP_LSC_LSC_YSIZE_0_1_ADDR(base)          ((base) + (0x0064))

/* �Ĵ���˵����size table
   λ����UNION�ṹ:  SOC_ISP_LSC_LSC_YSIZE_2_3_UNION */
#define SOC_ISP_LSC_LSC_YSIZE_2_3_ADDR(base)          ((base) + (0x0068))

/* �Ĵ���˵����size table
   λ����UNION�ṹ:  SOC_ISP_LSC_LSC_YSIZE_4_5_UNION */
#define SOC_ISP_LSC_LSC_YSIZE_4_5_ADDR(base)          ((base) + (0x006C))

/* �Ĵ���˵����size table
   λ����UNION�ṹ:  SOC_ISP_LSC_LSC_YSIZE_6_7_UNION */
#define SOC_ISP_LSC_LSC_YSIZE_6_7_ADDR(base)          ((base) + (0x0070))

/* �Ĵ���˵����status
   λ����UNION�ṹ:  SOC_ISP_LSC_LSC_TABLE_SEL_UNION */
#define SOC_ISP_LSC_LSC_TABLE_SEL_ADDR(base)          ((base) + (0x0074))

/* �Ĵ���˵����status
   λ����UNION�ṹ:  SOC_ISP_LSC_LSC_STATUS_UNION */
#define SOC_ISP_LSC_LSC_STATUS_ADDR(base)             ((base) + (0x0078))





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
                     (1/1) LSC
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_ISP_LSC_LSC_CTRL_UNION
 �ṹ˵��  : LSC_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: LSC control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lsc_en   : 1;  /* bit[0]   : 0: deactivation request for lens shading correction
                                                   1: activation request for lens shading correction 
                                                   Activation/Deactivation is object of a shadowing mechanism.
                                                   Next value is reflected in this register.
                                                   The current status is visible at ISP_LSC_STATUS.lsc_enable_status */
        unsigned int  reserved : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_ISP_LSC_LSC_CTRL_UNION;
#endif
#define SOC_ISP_LSC_LSC_CTRL_lsc_en_START    (0)
#define SOC_ISP_LSC_LSC_CTRL_lsc_en_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_ISP_LSC_LSC_R_TABLE_ADDR_UNION
 �ṹ˵��  : LSC_R_TABLE_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: red ram address
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  r_ram_addr : 9;  /* bit[0-8] : table address in RAM for samples of the Red color component. Will be automatically incremented by each read or write access to the table. Valid addresses are in the range 0 to 203.
                                                     Table set 0 access by SW at table address [0...203]. Table set 1 access at table address [204...407].
                                                     
                                                     Note on programming sequence: To fill the RED table, first set this base address register and then write in sequence your data in Sample table RED.
                                                     => If another table need to be configured, corresponding base address must be set again */
        unsigned int  reserved   : 23; /* bit[9-31]: Reserved */
    } reg;
} SOC_ISP_LSC_LSC_R_TABLE_ADDR_UNION;
#endif
#define SOC_ISP_LSC_LSC_R_TABLE_ADDR_r_ram_addr_START  (0)
#define SOC_ISP_LSC_LSC_R_TABLE_ADDR_r_ram_addr_END    (8)


/*****************************************************************************
 �ṹ��    : SOC_ISP_LSC_LSC_GR_TABLE_ADDR_UNION
 �ṹ˵��  : LSC_GR_TABLE_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: green-red ram address
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gr_ram_addr : 9;  /* bit[0-8] : table address in RAM for samples of the Green (Red) color component. Will be automatically incremented by each read or write access to the table. Valid addresses are in the range 0 to 203.
                                                      Table set 0 access by SW at table address [0...203]. Table set 1 access at table address [204...407].
                                                      
                                                      Note on programming sequence: To fill the GREEN-RED table, first set this base address register and then write in sequence your data in Sample table GREEN-RED.
                                                      => If another table need to be configured, corresponding base address must be set again */
        unsigned int  reserved    : 23; /* bit[9-31]: Reserved */
    } reg;
} SOC_ISP_LSC_LSC_GR_TABLE_ADDR_UNION;
#endif
#define SOC_ISP_LSC_LSC_GR_TABLE_ADDR_gr_ram_addr_START  (0)
#define SOC_ISP_LSC_LSC_GR_TABLE_ADDR_gr_ram_addr_END    (8)


/*****************************************************************************
 �ṹ��    : SOC_ISP_LSC_LSC_B_TABLE_ADDR_UNION
 �ṹ˵��  : LSC_B_TABLE_ADDR �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: blue ram address
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  b_ram_addr : 9;  /* bit[0-8] : table address in RAM for samples of the Blue color component. Will be automatically incremented by each read or write access to the table. Valid addresses are in the range 0 to 203.
                                                     Table set 0 access by SW at table address [0...203]. Table set 1 access at table address [204...407].
                                                     
                                                     Note on programming sequence: To fill the BLUE table, first set this base address register and then write in sequence your data in Sample table BLUE.
                                                     => If another table need to be configured, corresponding base address must be set again */
        unsigned int  reserved   : 23; /* bit[9-31]: Reserved */
    } reg;
} SOC_ISP_LSC_LSC_B_TABLE_ADDR_UNION;
#endif
#define SOC_ISP_LSC_LSC_B_TABLE_ADDR_b_ram_addr_START  (0)
#define SOC_ISP_LSC_LSC_B_TABLE_ADDR_b_ram_addr_END    (8)


/*****************************************************************************
 �ṹ��    : SOC_ISP_LSC_LSC_GB_TABLE_ADDR_UNION
 �ṹ˵��  : LSC_GB_TABLE_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: green-blue ram address
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gb_ram_addr : 9;  /* bit[0-8] : table address in RAM for samples of the Green (Blue) color component. Will be automatically incremented by each read or write access to the table. Valid addresses are in the range 0 to 203.
                                                      Table set 0 access by SW at table address [0...203]. Table set 1 access at table address [204...407].
                                                      
                                                      Note on programming sequence: To fill the GREEN-BLUE table, first set this base address register and then write in sequence your data in Sample table GREEN-BLUE.
                                                      => If another table need to be configured, corresponding base address must be set again */
        unsigned int  reserved    : 23; /* bit[9-31]: Reserved */
    } reg;
} SOC_ISP_LSC_LSC_GB_TABLE_ADDR_UNION;
#endif
#define SOC_ISP_LSC_LSC_GB_TABLE_ADDR_gb_ram_addr_START  (0)
#define SOC_ISP_LSC_LSC_GB_TABLE_ADDR_gb_ram_addr_END    (8)


/*****************************************************************************
 �ṹ��    : SOC_ISP_LSC_LSC_R_TABLE_DATA_UNION
 �ṹ˵��  : LSC_R_TABLE_DATA �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: Sample table red
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  r_sample_0 : 13; /* bit[0-12] : correction factor at sample point (fixed point number: 3 bits integer with 10-bit fractional part, range 1..7.999)
                                                      Correction can only be programmed, if the RGB Bayer path is switched on via ISP_CTRL register (ISP_MODE bits).
                                                      Table set 0 access by SW at table address [0...203]. Table set 1 access at table address [204...407]. */
        unsigned int  reserved_0 : 3;  /* bit[13-15]: Reserved */
        unsigned int  r_sample_1 : 13; /* bit[16-28]: correction factor at sample point (fixed point number: 3 bits integer with 10-bit fractional part, range 1..7.999)
                                                      Correction can only be programmed, if the RGB Bayer path is switched on via ISP_CTRL register (ISP_MODE bits).
                                                      Table set 0 access by SW at table address [0...203]. Table set 1 access at table address [204...407]. */
        unsigned int  reserved_1 : 3;  /* bit[29-31]: Reserved */
    } reg;
} SOC_ISP_LSC_LSC_R_TABLE_DATA_UNION;
#endif
#define SOC_ISP_LSC_LSC_R_TABLE_DATA_r_sample_0_START  (0)
#define SOC_ISP_LSC_LSC_R_TABLE_DATA_r_sample_0_END    (12)
#define SOC_ISP_LSC_LSC_R_TABLE_DATA_r_sample_1_START  (16)
#define SOC_ISP_LSC_LSC_R_TABLE_DATA_r_sample_1_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_LSC_LSC_GR_TABLE_DATA_UNION
 �ṹ˵��  : LSC_GR_TABLE_DATA �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: Sample table gren - red
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gr_sample_0 : 13; /* bit[0-12] : correction factor at sample point (fixed point number: 3 bits integer with 10-bit fractional part, range 1..7.999)
                                                       Correction can only be programmed, if the RGB Bayer path is switched on via ISP_CTRL register (ISP_MODE bits).
                                                       Table set 0 access by SW at table address [0...203]. Table set 1 access at table address [204...407]. */
        unsigned int  reserved_0  : 3;  /* bit[13-15]: Reserved */
        unsigned int  gr_sample_1 : 13; /* bit[16-28]: correction factor at sample point (fixed point number: 3 bits integer with 10-bit fractional part, range 1..7.999)
                                                       Correction can only be programmed, if the RGB Bayer path is switched on via ISP_CTRL register (ISP_MODE bits).
                                                       Table set 0 access by SW at table address [0...203]. Table set 1 access at table address [204...407]. */
        unsigned int  reserved_1  : 3;  /* bit[29-31]: Reserved */
    } reg;
} SOC_ISP_LSC_LSC_GR_TABLE_DATA_UNION;
#endif
#define SOC_ISP_LSC_LSC_GR_TABLE_DATA_gr_sample_0_START  (0)
#define SOC_ISP_LSC_LSC_GR_TABLE_DATA_gr_sample_0_END    (12)
#define SOC_ISP_LSC_LSC_GR_TABLE_DATA_gr_sample_1_START  (16)
#define SOC_ISP_LSC_LSC_GR_TABLE_DATA_gr_sample_1_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_LSC_LSC_B_TABLE_DATA_UNION
 �ṹ˵��  : LSC_B_TABLE_DATA �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Sample table blue
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  b_sample_0 : 13; /* bit[0-12] : correction factor at sample point (fixed point number: 3 bits integer with 10-bit fractional part, range 1..7.999)
                                                      Correction can only be programmed, if the RGB Bayer path is switched on via ISP_CTRL register (ISP_MODE bits).
                                                      Table set 0 access by SW at table address [0...203]. Table set 1 access at table address [204...407]. */
        unsigned int  reserved_0 : 3;  /* bit[13-15]: Reserved */
        unsigned int  b_sample_1 : 13; /* bit[16-28]: correction factor at sample point (fixed point number: 3 bits integer with 10-bit fractional part, range 1..7.999)
                                                      Correction can only be programmed, if the RGB Bayer path is switched on via ISP_CTRL register (ISP_MODE bits).
                                                      Table set 0 access by SW at table address [0...203]. Table set 1 access at table address [204...407]. */
        unsigned int  reserved_1 : 3;  /* bit[29-31]: Reserved */
    } reg;
} SOC_ISP_LSC_LSC_B_TABLE_DATA_UNION;
#endif
#define SOC_ISP_LSC_LSC_B_TABLE_DATA_b_sample_0_START  (0)
#define SOC_ISP_LSC_LSC_B_TABLE_DATA_b_sample_0_END    (12)
#define SOC_ISP_LSC_LSC_B_TABLE_DATA_b_sample_1_START  (16)
#define SOC_ISP_LSC_LSC_B_TABLE_DATA_b_sample_1_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_LSC_LSC_GB_TABLE_DATA_UNION
 �ṹ˵��  : LSC_GB_TABLE_DATA �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: Sample table green blue
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gb_sample_0 : 13; /* bit[0-12] : correction factor at sample point (fixed point number: 3 bits integer with 10-bit fractional part, range 1..7.999)
                                                       Correction can only be programmed, if the RGB Bayer path is switched on via ISP_CTRL register (ISP_MODE bits).
                                                       Table set 0 access by SW at table address [0...203]. Table set 1 access at table address [204...407]. */
        unsigned int  reserved_0  : 3;  /* bit[13-15]: Reserved */
        unsigned int  gb_sample_1 : 13; /* bit[16-28]: correction factor at sample point (fixed point number: 3 bits integer with 10-bit fractional part, range 1..7.999)
                                                       Correction can only be programmed, if the RGB Bayer path is switched on via ISP_CTRL register (ISP_MODE bits).
                                                       Table set 0 access by SW at table address [0...203]. Table set 1 access at table address [204...407]. */
        unsigned int  reserved_1  : 3;  /* bit[29-31]: Reserved */
    } reg;
} SOC_ISP_LSC_LSC_GB_TABLE_DATA_UNION;
#endif
#define SOC_ISP_LSC_LSC_GB_TABLE_DATA_gb_sample_0_START  (0)
#define SOC_ISP_LSC_LSC_GB_TABLE_DATA_gb_sample_0_END    (12)
#define SOC_ISP_LSC_LSC_GB_TABLE_DATA_gb_sample_1_START  (16)
#define SOC_ISP_LSC_LSC_GB_TABLE_DATA_gb_sample_1_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_LSC_LSC_XGRAD_0_1_UNION
 �ṹ˵��  : LSC_XGRAD_0_1 �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x00000000�����:32
 �Ĵ���˵��: Gradient table x
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  xgrad_0  : 12; /* bit[0-11] : factor for x-gradient calculation of sector 0. Cannot be updated during frame processing.
                                                    Note: x_grad_0 must be equal to 2**15 / x_sect_size_0 */
        unsigned int  reserved_0: 4;  /* bit[12-15]: Reserved */
        unsigned int  xgrad_1  : 12; /* bit[16-27]: factor for x-gradient calculation of sector 1. Cannot be updated during frame processing.
                                                    Note: x_grad_1 must be equal to 2**15 / x_sect_size_1 */
        unsigned int  reserved_1: 4;  /* bit[28-31]: Reserved */
    } reg;
} SOC_ISP_LSC_LSC_XGRAD_0_1_UNION;
#endif
#define SOC_ISP_LSC_LSC_XGRAD_0_1_xgrad_0_START   (0)
#define SOC_ISP_LSC_LSC_XGRAD_0_1_xgrad_0_END     (11)
#define SOC_ISP_LSC_LSC_XGRAD_0_1_xgrad_1_START   (16)
#define SOC_ISP_LSC_LSC_XGRAD_0_1_xgrad_1_END     (27)


/*****************************************************************************
 �ṹ��    : SOC_ISP_LSC_LSC_XGRAD_2_3_UNION
 �ṹ˵��  : LSC_XGRAD_2_3 �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x00000000�����:32
 �Ĵ���˵��: Gradient table x
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  xgrad_2  : 12; /* bit[0-11] : factor for x-gradient calculation of sector 2. Cannot be updated during frame processing.
                                                    Note: x_grad_2 must be equal to 2**15 / x_sect_size_2 */
        unsigned int  reserved_0: 4;  /* bit[12-15]: Reserved */
        unsigned int  xgrad_3  : 12; /* bit[16-27]: factor for x-gradient calculation of sector 3. Cannot be updated during frame processing.
                                                    Note: x_grad_3 must be equal to 2**15 / x_sect_size_3 */
        unsigned int  reserved_1: 4;  /* bit[28-31]: Reserved */
    } reg;
} SOC_ISP_LSC_LSC_XGRAD_2_3_UNION;
#endif
#define SOC_ISP_LSC_LSC_XGRAD_2_3_xgrad_2_START   (0)
#define SOC_ISP_LSC_LSC_XGRAD_2_3_xgrad_2_END     (11)
#define SOC_ISP_LSC_LSC_XGRAD_2_3_xgrad_3_START   (16)
#define SOC_ISP_LSC_LSC_XGRAD_2_3_xgrad_3_END     (27)


/*****************************************************************************
 �ṹ��    : SOC_ISP_LSC_LSC_XGRAD_4_5_UNION
 �ṹ˵��  : LSC_XGRAD_4_5 �Ĵ����ṹ���塣��ַƫ����:0x002C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Gradient table x
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  xgrad_4  : 12; /* bit[0-11] : factor for x-gradient calculation of sector 4. Cannot be updated during frame processing.
                                                    Note: x_grad_4 must be equal to 2**15 / x_sect_size_4 */
        unsigned int  reserved_0: 4;  /* bit[12-15]: Reserved */
        unsigned int  xgrad_5  : 12; /* bit[16-27]: factor for x-gradient calculation of sector 5. Cannot be updated during frame processing.
                                                    Note: x_grad_5 must be equal to 2**15 / x_sect_size_5 */
        unsigned int  reserved_1: 4;  /* bit[28-31]: Reserved */
    } reg;
} SOC_ISP_LSC_LSC_XGRAD_4_5_UNION;
#endif
#define SOC_ISP_LSC_LSC_XGRAD_4_5_xgrad_4_START   (0)
#define SOC_ISP_LSC_LSC_XGRAD_4_5_xgrad_4_END     (11)
#define SOC_ISP_LSC_LSC_XGRAD_4_5_xgrad_5_START   (16)
#define SOC_ISP_LSC_LSC_XGRAD_4_5_xgrad_5_END     (27)


/*****************************************************************************
 �ṹ��    : SOC_ISP_LSC_LSC_XGRAD_6_7_UNION
 �ṹ˵��  : LSC_XGRAD_6_7 �Ĵ����ṹ���塣��ַƫ����:0x0030����ֵ:0x00000000�����:32
 �Ĵ���˵��: Gradient table x
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  xgrad_6  : 12; /* bit[0-11] : factor for x-gradient calculation of sector 6. Cannot be updated during frame processing.
                                                    Note: x_grad_6 must be equal to 2**15 / x_sect_size_6 */
        unsigned int  reserved_0: 4;  /* bit[12-15]: Reserved */
        unsigned int  xgrad_7  : 12; /* bit[16-27]: factor for x-gradient calculation of sector 7. Cannot be updated during frame processing.
                                                    Note: x_grad_7 must be equal to 2**15 / x_sect_size_7 */
        unsigned int  reserved_1: 4;  /* bit[28-31]: Reserved */
    } reg;
} SOC_ISP_LSC_LSC_XGRAD_6_7_UNION;
#endif
#define SOC_ISP_LSC_LSC_XGRAD_6_7_xgrad_6_START   (0)
#define SOC_ISP_LSC_LSC_XGRAD_6_7_xgrad_6_END     (11)
#define SOC_ISP_LSC_LSC_XGRAD_6_7_xgrad_7_START   (16)
#define SOC_ISP_LSC_LSC_XGRAD_6_7_xgrad_7_END     (27)


/*****************************************************************************
 �ṹ��    : SOC_ISP_LSC_LSC_XGRAD_8_9_UNION
 �ṹ˵��  : LSC_XGRAD_8_9 �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x00000000�����:32
 �Ĵ���˵��: Gradient table x
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  xgrad_8  : 12; /* bit[0-11] : factor for x-gradient calculation of sector 8. Cannot be updated during frame processing.
                                                    Note: x_grad_8 must be equal to 2**15 / x_sect_size_8 */
        unsigned int  reserved_0: 4;  /* bit[12-15]: Reserved */
        unsigned int  xgrad_9  : 12; /* bit[16-27]: factor for x-gradient calculation of sector 9. Cannot be updated during frame processing.
                                                    Note: x_grad_9 must be equal to 2**15 / x_sect_size_9 */
        unsigned int  reserved_1: 4;  /* bit[28-31]: Reserved */
    } reg;
} SOC_ISP_LSC_LSC_XGRAD_8_9_UNION;
#endif
#define SOC_ISP_LSC_LSC_XGRAD_8_9_xgrad_8_START   (0)
#define SOC_ISP_LSC_LSC_XGRAD_8_9_xgrad_8_END     (11)
#define SOC_ISP_LSC_LSC_XGRAD_8_9_xgrad_9_START   (16)
#define SOC_ISP_LSC_LSC_XGRAD_8_9_xgrad_9_END     (27)


/*****************************************************************************
 �ṹ��    : SOC_ISP_LSC_LSC_XGRAD_10_UNION
 �ṹ˵��  : LSC_XGRAD_10 �Ĵ����ṹ���塣��ַƫ����:0x0038����ֵ:0x00000000�����:32
 �Ĵ���˵��: Gradient table x
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  xgrad_10 : 12; /* bit[0-11] : factor for x-gradient calculation of sector 10. Cannot be updated during frame processing.
                                                    Note: x_grad_10 must be equal to 2**15 / x_sect_size_10 */
        unsigned int  reserved : 20; /* bit[12-31]: Reserved */
    } reg;
} SOC_ISP_LSC_LSC_XGRAD_10_UNION;
#endif
#define SOC_ISP_LSC_LSC_XGRAD_10_xgrad_10_START  (0)
#define SOC_ISP_LSC_LSC_XGRAD_10_xgrad_10_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_ISP_LSC_LSC_YGRAD_0_1_UNION
 �ṹ˵��  : LSC_YGRAD_0_1 �Ĵ����ṹ���塣��ַƫ����:0x003C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Gradient table y
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ygrad_0  : 12; /* bit[0-11] : factor for y-gradient calculation of sector 0. Cannot be updated during frame processing.
                                                    Note: y_grad_0 must be equal to 2**15 / y_sect_size_0 */
        unsigned int  reserved_0: 4;  /* bit[12-15]: Reserved */
        unsigned int  ygrad_1  : 12; /* bit[16-27]: factor for y-gradient calculation of sector 1. Cannot be updated during frame processing.
                                                    Note: y_grad_1 must be equal to 2**15 / y_sect_size_1 */
        unsigned int  reserved_1: 4;  /* bit[28-31]: Reserved */
    } reg;
} SOC_ISP_LSC_LSC_YGRAD_0_1_UNION;
#endif
#define SOC_ISP_LSC_LSC_YGRAD_0_1_ygrad_0_START   (0)
#define SOC_ISP_LSC_LSC_YGRAD_0_1_ygrad_0_END     (11)
#define SOC_ISP_LSC_LSC_YGRAD_0_1_ygrad_1_START   (16)
#define SOC_ISP_LSC_LSC_YGRAD_0_1_ygrad_1_END     (27)


/*****************************************************************************
 �ṹ��    : SOC_ISP_LSC_LSC_YGRAD_2_3_UNION
 �ṹ˵��  : LSC_YGRAD_2_3 �Ĵ����ṹ���塣��ַƫ����:0x0040����ֵ:0x00000000�����:32
 �Ĵ���˵��: Gradient table y
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ygrad_2  : 12; /* bit[0-11] : factor for y-gradient calculation of sector 2. Cannot be updated during frame processing.
                                                    Note: y_grad_2 must be equal to 2**15 / y_sect_size_2 */
        unsigned int  reserved_0: 4;  /* bit[12-15]: Reserved */
        unsigned int  ygrad_3  : 12; /* bit[16-27]: factor for y-gradient calculation of sector 3. Cannot be updated during frame processing.
                                                    Note: y_grad_3 must be equal to 2**15 / y_sect_size_3 */
        unsigned int  reserved_1: 4;  /* bit[28-31]: Reserved */
    } reg;
} SOC_ISP_LSC_LSC_YGRAD_2_3_UNION;
#endif
#define SOC_ISP_LSC_LSC_YGRAD_2_3_ygrad_2_START   (0)
#define SOC_ISP_LSC_LSC_YGRAD_2_3_ygrad_2_END     (11)
#define SOC_ISP_LSC_LSC_YGRAD_2_3_ygrad_3_START   (16)
#define SOC_ISP_LSC_LSC_YGRAD_2_3_ygrad_3_END     (27)


/*****************************************************************************
 �ṹ��    : SOC_ISP_LSC_LSC_YGRAD_4_5_UNION
 �ṹ˵��  : LSC_YGRAD_4_5 �Ĵ����ṹ���塣��ַƫ����:0x0044����ֵ:0x00000000�����:32
 �Ĵ���˵��: Gradient table y
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ygrad_4  : 12; /* bit[0-11] : factor for y-gradient calculation of sector 4. Cannot be updated during frame processing.
                                                    Note: y_grad_4 must be equal to 2**15 / y_sect_size_4 */
        unsigned int  reserved_0: 4;  /* bit[12-15]: Reserved */
        unsigned int  ygrad_5  : 12; /* bit[16-27]: factor for y-gradient calculation of sector 5. Cannot be updated during frame processing.
                                                    Note: y_grad_5 must be equal to 2**15 / y_sect_size_5 */
        unsigned int  reserved_1: 4;  /* bit[28-31]: Reserved */
    } reg;
} SOC_ISP_LSC_LSC_YGRAD_4_5_UNION;
#endif
#define SOC_ISP_LSC_LSC_YGRAD_4_5_ygrad_4_START   (0)
#define SOC_ISP_LSC_LSC_YGRAD_4_5_ygrad_4_END     (11)
#define SOC_ISP_LSC_LSC_YGRAD_4_5_ygrad_5_START   (16)
#define SOC_ISP_LSC_LSC_YGRAD_4_5_ygrad_5_END     (27)


/*****************************************************************************
 �ṹ��    : SOC_ISP_LSC_LSC_YGRAD_6_7_UNION
 �ṹ˵��  : LSC_YGRAD_6_7 �Ĵ����ṹ���塣��ַƫ����:0x0048����ֵ:0x00000000�����:32
 �Ĵ���˵��: Gradient table y
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ygrad_6  : 12; /* bit[0-11] : factor for y-gradient calculation of sector 6. Cannot be updated during frame processing.
                                                    Note: y_grad_6 must be equal to 2**15 / y_sect_size_6 */
        unsigned int  reserved_0: 4;  /* bit[12-15]: Reserved */
        unsigned int  ygrad_7  : 12; /* bit[16-27]: factor for y-gradient calculation of sector 7. Cannot be updated during frame processing.
                                                    Note: y_grad_7 must be equal to 2**15 / y_sect_size_7 */
        unsigned int  reserved_1: 4;  /* bit[28-31]: Reserved */
    } reg;
} SOC_ISP_LSC_LSC_YGRAD_6_7_UNION;
#endif
#define SOC_ISP_LSC_LSC_YGRAD_6_7_ygrad_6_START   (0)
#define SOC_ISP_LSC_LSC_YGRAD_6_7_ygrad_6_END     (11)
#define SOC_ISP_LSC_LSC_YGRAD_6_7_ygrad_7_START   (16)
#define SOC_ISP_LSC_LSC_YGRAD_6_7_ygrad_7_END     (27)


/*****************************************************************************
 �ṹ��    : SOC_ISP_LSC_LSC_XSIZE_0_1_UNION
 �ṹ˵��  : LSC_XSIZE_0_1 �Ĵ����ṹ���塣��ַƫ����:0x004C����ֵ:0x00000000�����:32
 �Ĵ���˵��: size table
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  x_sect_size_0 : 10; /* bit[0-9]  : sector 0 size in x-direction. Cannot be updated during frame processing.
                                                         The sector size in x-direction must be greater than 12 pixels.
                                                         Note: The sum of the sector sizes in x-direction must be "picture width/2" */
        unsigned int  reserved_0    : 6;  /* bit[10-15]: Reserved */
        unsigned int  x_sect_size_1 : 10; /* bit[16-25]: sector 1 size in x-direction. Cannot be updated during frame processing.
                                                         The sector size in x-direction must be greater than 12 pixels.
                                                         Note: The sum of the sector sizes in x-direction must be "picture width/2" */
        unsigned int  reserved_1    : 6;  /* bit[26-31]: Reserved */
    } reg;
} SOC_ISP_LSC_LSC_XSIZE_0_1_UNION;
#endif
#define SOC_ISP_LSC_LSC_XSIZE_0_1_x_sect_size_0_START  (0)
#define SOC_ISP_LSC_LSC_XSIZE_0_1_x_sect_size_0_END    (9)
#define SOC_ISP_LSC_LSC_XSIZE_0_1_x_sect_size_1_START  (16)
#define SOC_ISP_LSC_LSC_XSIZE_0_1_x_sect_size_1_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_ISP_LSC_LSC_XSIZE_2_3_UNION
 �ṹ˵��  : LSC_XSIZE_2_3 �Ĵ����ṹ���塣��ַƫ����:0x0050����ֵ:0x00000000�����:32
 �Ĵ���˵��: size table
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  x_sect_size_2 : 10; /* bit[0-9]  : sector 2 size in x-direction. Cannot be updated during frame processing.
                                                         The sector size in x-direction must be greater than 12 pixels.
                                                         Note: The sum of the sector sizes in x-direction must be "picture width/2" */
        unsigned int  reserved_0    : 6;  /* bit[10-15]: Reserved */
        unsigned int  x_sect_size_3 : 10; /* bit[16-25]: sector 3 size in x-direction. Cannot be updated during frame processing.
                                                         The sector size in x-direction must be greater than 12 pixels.
                                                         Note: The sum of the sector sizes in x-direction must be "picture width/2" */
        unsigned int  reserved_1    : 6;  /* bit[26-31]: Reserved */
    } reg;
} SOC_ISP_LSC_LSC_XSIZE_2_3_UNION;
#endif
#define SOC_ISP_LSC_LSC_XSIZE_2_3_x_sect_size_2_START  (0)
#define SOC_ISP_LSC_LSC_XSIZE_2_3_x_sect_size_2_END    (9)
#define SOC_ISP_LSC_LSC_XSIZE_2_3_x_sect_size_3_START  (16)
#define SOC_ISP_LSC_LSC_XSIZE_2_3_x_sect_size_3_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_ISP_LSC_LSC_XSIZE_4_5_UNION
 �ṹ˵��  : LSC_XSIZE_4_5 �Ĵ����ṹ���塣��ַƫ����:0x0054����ֵ:0x00000000�����:32
 �Ĵ���˵��: size table
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  x_sect_size_4 : 10; /* bit[0-9]  : sector 4 size in x-direction. Cannot be updated during frame processing.
                                                         The sector size in x-direction must be greater than 12 pixels.
                                                         Note: The sum of the sector sizes in x-direction must be "picture width/2" */
        unsigned int  reserved_0    : 6;  /* bit[10-15]: Reserved */
        unsigned int  x_sect_size_5 : 10; /* bit[16-25]: sector 5 size in x-direction. Cannot be updated during frame processing.
                                                         The sector size in x-direction must be greater than 12 pixels.
                                                         Note: The sum of the sector sizes in x-direction must be "picture width/2" */
        unsigned int  reserved_1    : 6;  /* bit[26-31]: Reserved */
    } reg;
} SOC_ISP_LSC_LSC_XSIZE_4_5_UNION;
#endif
#define SOC_ISP_LSC_LSC_XSIZE_4_5_x_sect_size_4_START  (0)
#define SOC_ISP_LSC_LSC_XSIZE_4_5_x_sect_size_4_END    (9)
#define SOC_ISP_LSC_LSC_XSIZE_4_5_x_sect_size_5_START  (16)
#define SOC_ISP_LSC_LSC_XSIZE_4_5_x_sect_size_5_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_ISP_LSC_LSC_XSIZE_6_7_UNION
 �ṹ˵��  : LSC_XSIZE_6_7 �Ĵ����ṹ���塣��ַƫ����:0x0058����ֵ:0x00000000�����:32
 �Ĵ���˵��: size table
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  x_sect_size_6 : 10; /* bit[0-9]  : sector 6 size in x-direction. Cannot be updated during frame processing.
                                                         The sector size in x-direction must be greater than 12 pixels.
                                                         Note: The sum of the sector sizes in x-direction must be "picture width/2" */
        unsigned int  reserved_0    : 6;  /* bit[10-15]: Reserved */
        unsigned int  x_sect_size_7 : 10; /* bit[16-25]: sector 7 size in x-direction. Cannot be updated during frame processing.
                                                         The sector size in x-direction must be greater than 12 pixels.
                                                         Note: The sum of the sector sizes in x-direction must be "picture width/2" */
        unsigned int  reserved_1    : 6;  /* bit[26-31]: Reserved */
    } reg;
} SOC_ISP_LSC_LSC_XSIZE_6_7_UNION;
#endif
#define SOC_ISP_LSC_LSC_XSIZE_6_7_x_sect_size_6_START  (0)
#define SOC_ISP_LSC_LSC_XSIZE_6_7_x_sect_size_6_END    (9)
#define SOC_ISP_LSC_LSC_XSIZE_6_7_x_sect_size_7_START  (16)
#define SOC_ISP_LSC_LSC_XSIZE_6_7_x_sect_size_7_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_ISP_LSC_LSC_XSIZE_8_9_UNION
 �ṹ˵��  : LSC_XSIZE_8_9 �Ĵ����ṹ���塣��ַƫ����:0x005C����ֵ:0x00000000�����:32
 �Ĵ���˵��: size table
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  x_sect_size_8 : 10; /* bit[0-9]  : sector 8 size in x-direction. Cannot be updated during frame processing.
                                                         The sector size in x-direction must be greater than 12 pixels.
                                                         Note: The sum of the sector sizes in x-direction must be "picture width/2" */
        unsigned int  reserved_0    : 6;  /* bit[10-15]: Reserved */
        unsigned int  x_sect_size_9 : 10; /* bit[16-25]: sector 9 size in x-direction. Cannot be updated during frame processing.
                                                         The sector size in x-direction must be greater than 12 pixels.
                                                         Note: The sum of the sector sizes in x-direction must be "picture width/2" */
        unsigned int  reserved_1    : 6;  /* bit[26-31]: Reserved */
    } reg;
} SOC_ISP_LSC_LSC_XSIZE_8_9_UNION;
#endif
#define SOC_ISP_LSC_LSC_XSIZE_8_9_x_sect_size_8_START  (0)
#define SOC_ISP_LSC_LSC_XSIZE_8_9_x_sect_size_8_END    (9)
#define SOC_ISP_LSC_LSC_XSIZE_8_9_x_sect_size_9_START  (16)
#define SOC_ISP_LSC_LSC_XSIZE_8_9_x_sect_size_9_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_ISP_LSC_LSC_XSIZE_10_UNION
 �ṹ˵��  : LSC_XSIZE_10 �Ĵ����ṹ���塣��ַƫ����:0x0060����ֵ:0x00000000�����:32
 �Ĵ���˵��: size table
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  x_sect_size_10 : 10; /* bit[0-9]  : sector 10 size in x-direction. Cannot be updated during frame processing.
                                                          The sector size in x-direction must be greater than 12 pixels.
                                                          Note: The sum of the sector sizes in x-direction must be "picture width/2" */
        unsigned int  reserved       : 22; /* bit[10-31]: Reserved */
    } reg;
} SOC_ISP_LSC_LSC_XSIZE_10_UNION;
#endif
#define SOC_ISP_LSC_LSC_XSIZE_10_x_sect_size_10_START  (0)
#define SOC_ISP_LSC_LSC_XSIZE_10_x_sect_size_10_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_ISP_LSC_LSC_YSIZE_0_1_UNION
 �ṹ˵��  : LSC_YSIZE_0_1 �Ĵ����ṹ���塣��ַƫ����:0x0064����ֵ:0x00000000�����:32
 �Ĵ���˵��: size table
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  y_sect_size_0 : 10; /* bit[0-9]  : sector 0 size in y-direction. Cannot be updated during frame processing.
                                                         minimum sector size is 8 in y direction
                                                         Note: The sum of the sector sizes in y-direction must be "picture height/2" */
        unsigned int  reserved_0    : 6;  /* bit[10-15]: Reserved */
        unsigned int  y_sect_size_1 : 10; /* bit[16-25]: sector 1 size in y-direction. Cannot be updated during frame processing.
                                                         minimum sector size is 8 in y direction.
                                                         Note: The sum of the sector sizes in y-direction must be "picture height/2" */
        unsigned int  reserved_1    : 6;  /* bit[26-31]: Reserved */
    } reg;
} SOC_ISP_LSC_LSC_YSIZE_0_1_UNION;
#endif
#define SOC_ISP_LSC_LSC_YSIZE_0_1_y_sect_size_0_START  (0)
#define SOC_ISP_LSC_LSC_YSIZE_0_1_y_sect_size_0_END    (9)
#define SOC_ISP_LSC_LSC_YSIZE_0_1_y_sect_size_1_START  (16)
#define SOC_ISP_LSC_LSC_YSIZE_0_1_y_sect_size_1_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_ISP_LSC_LSC_YSIZE_2_3_UNION
 �ṹ˵��  : LSC_YSIZE_2_3 �Ĵ����ṹ���塣��ַƫ����:0x0068����ֵ:0x00000000�����:32
 �Ĵ���˵��: size table
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  y_sect_size_2 : 10; /* bit[0-9]  : sector 2 size in y-direction. Cannot be updated during frame processing.
                                                         minimum sector size is 8 in y direction
                                                         Note: The sum of the sector sizes in y-direction must be "picture height/2" */
        unsigned int  reserved_0    : 6;  /* bit[10-15]: Reserved */
        unsigned int  y_sect_size_3 : 10; /* bit[16-25]: sector 3 size in y-direction. Cannot be updated during frame processing.
                                                         minimum sector size is 8 in y direction
                                                         Note: The sum of the sector sizes in y-direction must be "picture height/2" */
        unsigned int  reserved_1    : 6;  /* bit[26-31]: Reserved */
    } reg;
} SOC_ISP_LSC_LSC_YSIZE_2_3_UNION;
#endif
#define SOC_ISP_LSC_LSC_YSIZE_2_3_y_sect_size_2_START  (0)
#define SOC_ISP_LSC_LSC_YSIZE_2_3_y_sect_size_2_END    (9)
#define SOC_ISP_LSC_LSC_YSIZE_2_3_y_sect_size_3_START  (16)
#define SOC_ISP_LSC_LSC_YSIZE_2_3_y_sect_size_3_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_ISP_LSC_LSC_YSIZE_4_5_UNION
 �ṹ˵��  : LSC_YSIZE_4_5 �Ĵ����ṹ���塣��ַƫ����:0x006C����ֵ:0x00000000�����:32
 �Ĵ���˵��: size table
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  y_sect_size_4 : 10; /* bit[0-9]  : sector 4 size in y-direction. Cannot be updated during frame processing.
                                                         minimum sector size is 8 in y direction
                                                         Note: The sum of the sector sizes in y-direction must be "picture height/2" */
        unsigned int  reserved_0    : 6;  /* bit[10-15]: Reserved */
        unsigned int  y_sect_size_5 : 10; /* bit[16-25]: sector 5 size in y-direction. Cannot be updated during frame processing.
                                                         minimum sector size is 8 in y direction
                                                         Note: The sum of the sector sizes in y-direction must be "picture height/2" */
        unsigned int  reserved_1    : 6;  /* bit[26-31]: Reserved */
    } reg;
} SOC_ISP_LSC_LSC_YSIZE_4_5_UNION;
#endif
#define SOC_ISP_LSC_LSC_YSIZE_4_5_y_sect_size_4_START  (0)
#define SOC_ISP_LSC_LSC_YSIZE_4_5_y_sect_size_4_END    (9)
#define SOC_ISP_LSC_LSC_YSIZE_4_5_y_sect_size_5_START  (16)
#define SOC_ISP_LSC_LSC_YSIZE_4_5_y_sect_size_5_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_ISP_LSC_LSC_YSIZE_6_7_UNION
 �ṹ˵��  : LSC_YSIZE_6_7 �Ĵ����ṹ���塣��ַƫ����:0x0070����ֵ:0x00000000�����:32
 �Ĵ���˵��: size table
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  y_sect_size_6 : 10; /* bit[0-9]  : sector 6 size in y-direction. Cannot be updated during frame processing.
                                                         minimum sector size is 8 in y direction
                                                         Note: The sum of the sector sizes in y-direction must be "picture height/2" */
        unsigned int  reserved_0    : 6;  /* bit[10-15]: Reserved */
        unsigned int  y_sect_size_7 : 10; /* bit[16-25]: sector 7 size in y-direction. Cannot be updated during frame processing.
                                                         minimum sector size is 8 in y direction
                                                         Note: The sum of the sector sizes in y-direction must be "picture height/2" */
        unsigned int  reserved_1    : 6;  /* bit[26-31]: Reserved */
    } reg;
} SOC_ISP_LSC_LSC_YSIZE_6_7_UNION;
#endif
#define SOC_ISP_LSC_LSC_YSIZE_6_7_y_sect_size_6_START  (0)
#define SOC_ISP_LSC_LSC_YSIZE_6_7_y_sect_size_6_END    (9)
#define SOC_ISP_LSC_LSC_YSIZE_6_7_y_sect_size_7_START  (16)
#define SOC_ISP_LSC_LSC_YSIZE_6_7_y_sect_size_7_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_ISP_LSC_LSC_TABLE_SEL_UNION
 �ṹ˵��  : LSC_TABLE_SEL �Ĵ����ṹ���塣��ַƫ����:0x0074����ֵ:0x00000000�����:32
 �Ĵ���˵��: status
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  table_select : 1;  /* bit[0]   : 0: next active tables set is table set 0. 
                                                       1: next active tables set is table set 1. 
                                                       Table selection is object of a shadowing mechnism.
                                                       Next value is reflected in this register.
                                                       The current status is visible at ISP_LSC_STATUS::active_table. */
        unsigned int  reserved     : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_ISP_LSC_LSC_TABLE_SEL_UNION;
#endif
#define SOC_ISP_LSC_LSC_TABLE_SEL_table_select_START  (0)
#define SOC_ISP_LSC_LSC_TABLE_SEL_table_select_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_ISP_LSC_LSC_STATUS_UNION
 �ṹ˵��  : LSC_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0078����ֵ:0x00000000�����:32
 �Ĵ���˵��: status
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lsc_en_status : 1;  /* bit[0]   : 0: lens shading correction is currently off 
                                                        1: lens shading correction is currently on */
        unsigned int  active_table  : 1;  /* bit[1]   : 0: currently active tables set is table set 0 
                                                        1: currently active tables set is table set 1 */
        unsigned int  reserved      : 30; /* bit[2-31]: Reserved */
    } reg;
} SOC_ISP_LSC_LSC_STATUS_UNION;
#endif
#define SOC_ISP_LSC_LSC_STATUS_lsc_en_status_START  (0)
#define SOC_ISP_LSC_LSC_STATUS_lsc_en_status_END    (0)
#define SOC_ISP_LSC_LSC_STATUS_active_table_START   (1)
#define SOC_ISP_LSC_LSC_STATUS_active_table_END     (1)






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

#endif /* end of soc_isp_lsc_interface.h */
