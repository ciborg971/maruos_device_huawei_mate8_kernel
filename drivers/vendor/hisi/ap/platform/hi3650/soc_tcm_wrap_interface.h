/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_tcm_wrap_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:23:14
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_TCM_WRAP.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_TCM_WRAP_INTERFACE_H__
#define __SOC_TCM_WRAP_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_define
 ****************************************************************************/
/* �Ĵ���˵����Remapģ����ƼĴ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_REMAP_CFG_UNION */
#define SOC_TCM_WRAP_REMAP_CFG_ADDR(base)             ((base) + (0x000))

/* �Ĵ���˵����Map_tableд�����Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_MAP_TABLE_WP_UNION */
#define SOC_TCM_WRAP_MAP_TABLE_WP_ADDR(base)          ((base) + (0x004))

/* �Ĵ���˵�����͹��Ŀ��ƼĴ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_LP_CTRL_UNION */
#define SOC_TCM_WRAP_LP_CTRL_ADDR(base)               ((base) + (0x008))

/* �Ĵ���˵�����͹��Ŀ��ƼĴ���1
   λ����UNION�ṹ:  SOC_TCM_WRAP_LP_CTRL_1_UNION */
#define SOC_TCM_WRAP_LP_CTRL_1_ADDR(base)             ((base) + (0x00C))

/* �Ĵ���˵����ITCM��TLB_ENTY_0�Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_ITCM_TLB_ENTRY0_UNION */
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY0_ADDR(base)       ((base) + (0x010))

/* �Ĵ���˵����ITCM��TLB_ENTY_1�Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_ITCM_TLB_ENTRY1_UNION */
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY1_ADDR(base)       ((base) + (0x014))

/* �Ĵ���˵����ITCM��TLB_ENTY_2�Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_ITCM_TLB_ENTRY2_UNION */
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY2_ADDR(base)       ((base) + (0x018))

/* �Ĵ���˵����ITCM��TLB_ENTY_3�Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_ITCM_TLB_ENTRY3_UNION */
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY3_ADDR(base)       ((base) + (0x01C))

/* �Ĵ���˵����ITCM��TLB_ENTY_4�Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_ITCM_TLB_ENTRY4_UNION */
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY4_ADDR(base)       ((base) + (0x020))

/* �Ĵ���˵����ITCM��TLB_ENTY_5�Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_ITCM_TLB_ENTRY5_UNION */
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY5_ADDR(base)       ((base) + (0x024))

/* �Ĵ���˵����ITCM��TLB_ENTY_6�Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_ITCM_TLB_ENTRY6_UNION */
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY6_ADDR(base)       ((base) + (0x028))

/* �Ĵ���˵����ITCM��TLB_ENTY_7�Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_ITCM_TLB_ENTRY7_UNION */
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY7_ADDR(base)       ((base) + (0x02C))

/* �Ĵ���˵����D0TCM��TLB_ENTY_0�Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_D0TCM_TLB_ENTRY0_UNION */
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY0_ADDR(base)      ((base) + (0x030))

/* �Ĵ���˵����D0TCM��TLB_ENTY_1�Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_D0TCM_TLB_ENTRY1_UNION */
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY1_ADDR(base)      ((base) + (0x034))

/* �Ĵ���˵����D0TCM��TLB_ENTY_2�Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_D0TCM_TLB_ENTRY2_UNION */
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY2_ADDR(base)      ((base) + (0x038))

/* �Ĵ���˵����D0TCM��TLB_ENTY_3�Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_D0TCM_TLB_ENTRY3_UNION */
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY3_ADDR(base)      ((base) + (0x03C))

/* �Ĵ���˵����D0TCM��TLB_ENTY_4�Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_D0TCM_TLB_ENTRY4_UNION */
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY4_ADDR(base)      ((base) + (0x040))

/* �Ĵ���˵����D0TCM��TLB_ENTY_5�Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_D0TCM_TLB_ENTRY5_UNION */
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY5_ADDR(base)      ((base) + (0x044))

/* �Ĵ���˵����D0TCM��TLB_ENTY_6�Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_D0TCM_TLB_ENTRY6_UNION */
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY6_ADDR(base)      ((base) + (0x048))

/* �Ĵ���˵����D0TCM��TLB_ENTY_7�Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_D0TCM_TLB_ENTRY7_UNION */
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY7_ADDR(base)      ((base) + (0x04C))

/* �Ĵ���˵����D1TCM��TLB_ENTY_0�Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_D1TCM_TLB_ENTRY0_UNION */
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY0_ADDR(base)      ((base) + (0x050))

/* �Ĵ���˵����D1TCM��TLB_ENTY_1�Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_D1TCM_TLB_ENTRY1_UNION */
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY1_ADDR(base)      ((base) + (0x054))

/* �Ĵ���˵����D1TCM��TLB_ENTY_2�Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_D1TCM_TLB_ENTRY2_UNION */
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY2_ADDR(base)      ((base) + (0x058))

/* �Ĵ���˵����D1TCM��TLB_ENTY_3�Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_D1TCM_TLB_ENTRY3_UNION */
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY3_ADDR(base)      ((base) + (0x05C))

/* �Ĵ���˵����D1TCM��TLB_ENTY_4�Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_D1TCM_TLB_ENTRY4_UNION */
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY4_ADDR(base)      ((base) + (0x060))

/* �Ĵ���˵����D1TCM��TLB_ENTY_5�Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_D1TCM_TLB_ENTRY5_UNION */
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY5_ADDR(base)      ((base) + (0x064))

/* �Ĵ���˵����D1TCM��TLB_ENTY_6�Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_D1TCM_TLB_ENTRY6_UNION */
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY6_ADDR(base)      ((base) + (0x068))

/* �Ĵ���˵����D1TCM��TLB_ENTY_7�Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_D1TCM_TLB_ENTRY7_UNION */
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY7_ADDR(base)      ((base) + (0x06C))

/* �Ĵ���˵����ITCM�����д����Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_ITCM_HIT_CNT_UNION */
#define SOC_TCM_WRAP_ITCM_HIT_CNT_ADDR(base)          ((base) + (0x070))

/* �Ĵ���˵����ITCM��miss�����Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_ITCM_MISS_CNT_UNION */
#define SOC_TCM_WRAP_ITCM_MISS_CNT_ADDR(base)         ((base) + (0x074))

/* �Ĵ���˵����D0TCM�����д����Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_D0TCM_HIT_CNT_UNION */
#define SOC_TCM_WRAP_D0TCM_HIT_CNT_ADDR(base)         ((base) + (0x078))

/* �Ĵ���˵����D0TCM��miss�����Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_D0TCM_MISS_CNT_UNION */
#define SOC_TCM_WRAP_D0TCM_MISS_CNT_ADDR(base)        ((base) + (0x07C))

/* �Ĵ���˵����D1TCM�����д����Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_D1TCM_HIT_CNT_UNION */
#define SOC_TCM_WRAP_D1TCM_HIT_CNT_ADDR(base)         ((base) + (0x080))

/* �Ĵ���˵����D1TCM��miss�����Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_D1TCM_MISS_CNT_UNION */
#define SOC_TCM_WRAP_D1TCM_MISS_CNT_ADDR(base)        ((base) + (0x084))

/* �Ĵ���˵����TCM ADDRESS�߽��鹦��ʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_TCMADDR_BOUNDARY_CHECK_BYPASS_UNION */
#define SOC_TCM_WRAP_TCMADDR_BOUNDARY_CHECK_BYPASS_ADDR(base) ((base) + (0x098))

/* �Ĵ���˵����ITCM�������ͼĴ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_TCM_ERR_TYPE_UNION */
#define SOC_TCM_WRAP_TCM_ERR_TYPE_ADDR(base)          ((base) + (0x09C))

/* �Ĵ���˵����BANKѡ��Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_BANK_SEL_UNION */
#define SOC_TCM_WRAP_BANK_SEL_ADDR(base)              ((base) + (0x0A0))

/* �Ĵ���˵����ITCM�����ַ�Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_ITCM_ERR_ADDR_UNION */
#define SOC_TCM_WRAP_ITCM_ERR_ADDR_ADDR(base)         ((base) + (0x0A8))

/* �Ĵ���˵����D0TCM�����ַ�Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_D0TCM_ERR_ADDR_UNION */
#define SOC_TCM_WRAP_D0TCM_ERR_ADDR_ADDR(base)        ((base) + (0x0AC))

/* �Ĵ���˵����D1TCM�����ַ�Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_D1TCM_ERR_ADDR_UNION */
#define SOC_TCM_WRAP_D1TCM_ERR_ADDR_ADDR(base)        ((base) + (0x0B0))

/* �Ĵ���˵����ITCM����������Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_ITCM_ERR_CNT_UNION */
#define SOC_TCM_WRAP_ITCM_ERR_CNT_ADDR(base)          ((base) + (0x0B4))

/* �Ĵ���˵����D0TCM����������Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_D0TCM_ERR_CNT_UNION */
#define SOC_TCM_WRAP_D0TCM_ERR_CNT_ADDR(base)         ((base) + (0x0B8))

/* �Ĵ���˵����D1TCM����������Ĵ���
   λ����UNION�ṹ:  SOC_TCM_WRAP_D1TCM_ERR_CNT_UNION */
#define SOC_TCM_WRAP_D1TCM_ERR_CNT_ADDR(base)         ((base) + (0x0BC))





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
                     (1/1) reg_define
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_REMAP_CFG_UNION
 �ṹ˵��  : REMAP_CFG �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x00000001�����:32
 �Ĵ���˵��: Remapģ����ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass            : 1;  /* bit[0-0]  : Remap�����Ƿ�Bypass
                                                             0��ʹ��Remap���� 
                                                             1����ʹ��Remap���� */
        unsigned int  invalid           : 1;  /* bit[1-1]  : ��Micro TLB�е�entry����invalid���� */
        unsigned int  itcm_cnt_clr      : 1;  /* bit[2-2]  : д1���ͳ��ITCM��д���������к�miss��������д0��Ч�� */
        unsigned int  d0tcm_cnt_clr     : 1;  /* bit[3-3]  : д1���ͳ��D0TCM��д���������к�miss��������д0��Ч�� */
        unsigned int  d1tcm_cnt_clr     : 1;  /* bit[4-4]  : д1���ͳ��D1TCM��д���������к�miss��������д0��Ч�� */
        unsigned int  itcm_err_cnt_clr  : 1;  /* bit[5-5]  : д1���ͳ��ITCM����������ʹ����ַ��д0��Ч�� */
        unsigned int  d0tcm_err_cnt_clr : 1;  /* bit[6-6]  : д1���ͳ��D0TCM����������ʹ����ַ��д0��Ч�� */
        unsigned int  d1tcm_err_cnt_clr : 1;  /* bit[7-7]  : д1���ͳ��D1TCM����������ʹ����ַ��д0��Ч�� */
        unsigned int  itcm_err_clr      : 1;  /* bit[8-8]  : д1���ITCM ERR״̬��д0��Ч�� */
        unsigned int  d0tcm_err_clr     : 1;  /* bit[9-9]  : д1���D0TCM ERR״̬��д0��Ч�� */
        unsigned int  d1tcm_err_clr     : 1;  /* bit[10-10]: д1���D1TCM ERR״̬��д0��Ч�� */
        unsigned int  reserved          : 21; /* bit[11-31]: reserved */
    } reg;
} SOC_TCM_WRAP_REMAP_CFG_UNION;
#endif
#define SOC_TCM_WRAP_REMAP_CFG_bypass_START             (0)
#define SOC_TCM_WRAP_REMAP_CFG_bypass_END               (0)
#define SOC_TCM_WRAP_REMAP_CFG_invalid_START            (1)
#define SOC_TCM_WRAP_REMAP_CFG_invalid_END              (1)
#define SOC_TCM_WRAP_REMAP_CFG_itcm_cnt_clr_START       (2)
#define SOC_TCM_WRAP_REMAP_CFG_itcm_cnt_clr_END         (2)
#define SOC_TCM_WRAP_REMAP_CFG_d0tcm_cnt_clr_START      (3)
#define SOC_TCM_WRAP_REMAP_CFG_d0tcm_cnt_clr_END        (3)
#define SOC_TCM_WRAP_REMAP_CFG_d1tcm_cnt_clr_START      (4)
#define SOC_TCM_WRAP_REMAP_CFG_d1tcm_cnt_clr_END        (4)
#define SOC_TCM_WRAP_REMAP_CFG_itcm_err_cnt_clr_START   (5)
#define SOC_TCM_WRAP_REMAP_CFG_itcm_err_cnt_clr_END     (5)
#define SOC_TCM_WRAP_REMAP_CFG_d0tcm_err_cnt_clr_START  (6)
#define SOC_TCM_WRAP_REMAP_CFG_d0tcm_err_cnt_clr_END    (6)
#define SOC_TCM_WRAP_REMAP_CFG_d1tcm_err_cnt_clr_START  (7)
#define SOC_TCM_WRAP_REMAP_CFG_d1tcm_err_cnt_clr_END    (7)
#define SOC_TCM_WRAP_REMAP_CFG_itcm_err_clr_START       (8)
#define SOC_TCM_WRAP_REMAP_CFG_itcm_err_clr_END         (8)
#define SOC_TCM_WRAP_REMAP_CFG_d0tcm_err_clr_START      (9)
#define SOC_TCM_WRAP_REMAP_CFG_d0tcm_err_clr_END        (9)
#define SOC_TCM_WRAP_REMAP_CFG_d1tcm_err_clr_START      (10)
#define SOC_TCM_WRAP_REMAP_CFG_d1tcm_err_clr_END        (10)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_MAP_TABLE_WP_UNION
 �ṹ˵��  : MAP_TABLE_WP �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x00000000�����:32
 �Ĵ���˵��: Map_tableд�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mt_wp : 32; /* bit[0-31]: ֻ�мĴ�������Ϊ0x6864_3650ʱ�����ܶ�Map Table�������ã�����ֻ�ܶ�Map Table���ж������� */
    } reg;
} SOC_TCM_WRAP_MAP_TABLE_WP_UNION;
#endif
#define SOC_TCM_WRAP_MAP_TABLE_WP_mt_wp_START  (0)
#define SOC_TCM_WRAP_MAP_TABLE_WP_mt_wp_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_LP_CTRL_UNION
 �ṹ˵��  : LP_CTRL �Ĵ����ṹ���塣��ַƫ����:0x008����ֵ:0x00F000F0�����:32
 �Ĵ���˵��: �͹��Ŀ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  auto_gate_en    : 1;  /* bit[0-0]  : ʱ���Զ��ſع���
                                                           0����ʹ��
                                                           1��ʹ�� */
        unsigned int  reserved_0      : 3;  /* bit[1-3]  : reserved */
        unsigned int  auto_gate_cnt   : 8;  /* bit[4-11] : TCMʱ���Զ��ſع��ܵķ�����������������ֵ��������û�в�����TCM�Զ��ſ���Ч������ֵ����С��3�����������ó�0x3 */
        unsigned int  reserved_1      : 4;  /* bit[12-15]: reserved */
        unsigned int  auto_mem_lp_en  : 1;  /* bit[16-16]: Memory�Զ�����Deepsleep����
                                                           0����ʹ��
                                                           1��ʹ�� */
        unsigned int  reserved_2      : 3;  /* bit[17-19]: reserved */
        unsigned int  auto_mem_lp_cnt : 8;  /* bit[20-27]: Memory�Զ�����Deepsleep��û�в��������������������ó�0x7 */
        unsigned int  reserved_3      : 4;  /* bit[28-31]: reserved */
    } reg;
} SOC_TCM_WRAP_LP_CTRL_UNION;
#endif
#define SOC_TCM_WRAP_LP_CTRL_auto_gate_en_START     (0)
#define SOC_TCM_WRAP_LP_CTRL_auto_gate_en_END       (0)
#define SOC_TCM_WRAP_LP_CTRL_auto_gate_cnt_START    (4)
#define SOC_TCM_WRAP_LP_CTRL_auto_gate_cnt_END      (11)
#define SOC_TCM_WRAP_LP_CTRL_auto_mem_lp_en_START   (16)
#define SOC_TCM_WRAP_LP_CTRL_auto_mem_lp_en_END     (16)
#define SOC_TCM_WRAP_LP_CTRL_auto_mem_lp_cnt_START  (20)
#define SOC_TCM_WRAP_LP_CTRL_auto_mem_lp_cnt_END    (27)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_LP_CTRL_1_UNION
 �ṹ˵��  : LP_CTRL_1 �Ĵ����ṹ���塣��ַƫ����:0x00C����ֵ:0x00000001�����:32
 �Ĵ���˵��: �͹��Ŀ��ƼĴ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tcm128_gate_en_soft : 1;  /* bit[0-0] : 128Mhzʱ�����ſ�
                                                              0����ʹ��
                                                              1��ʹ�� */
        unsigned int  reserved            : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_TCM_WRAP_LP_CTRL_1_UNION;
#endif
#define SOC_TCM_WRAP_LP_CTRL_1_tcm128_gate_en_soft_START  (0)
#define SOC_TCM_WRAP_LP_CTRL_1_tcm128_gate_en_soft_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_ITCM_TLB_ENTRY0_UNION
 �ṹ˵��  : ITCM_TLB_ENTRY0 �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x00000000�����:32
 �Ĵ���˵��: ITCM��TLB_ENTY_0�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itcm_tlb_entry0 : 20; /* bit[0-19] : ITCM tlb_entry0��ֵ */
        unsigned int  reserved        : 12; /* bit[20-31]: reserved */
    } reg;
} SOC_TCM_WRAP_ITCM_TLB_ENTRY0_UNION;
#endif
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY0_itcm_tlb_entry0_START  (0)
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY0_itcm_tlb_entry0_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_ITCM_TLB_ENTRY1_UNION
 �ṹ˵��  : ITCM_TLB_ENTRY1 �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x00000000�����:32
 �Ĵ���˵��: ITCM��TLB_ENTY_1�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itcm_tlb_entry1 : 20; /* bit[0-19] : ` */
        unsigned int  reserved        : 12; /* bit[20-31]: reserved */
    } reg;
} SOC_TCM_WRAP_ITCM_TLB_ENTRY1_UNION;
#endif
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY1_itcm_tlb_entry1_START  (0)
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY1_itcm_tlb_entry1_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_ITCM_TLB_ENTRY2_UNION
 �ṹ˵��  : ITCM_TLB_ENTRY2 �Ĵ����ṹ���塣��ַƫ����:0x018����ֵ:0x00000000�����:32
 �Ĵ���˵��: ITCM��TLB_ENTY_2�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itcm_tlb_entry2 : 20; /* bit[0-19] : ITCM tlb_entry2��ֵ */
        unsigned int  reserved        : 12; /* bit[20-31]: reserved */
    } reg;
} SOC_TCM_WRAP_ITCM_TLB_ENTRY2_UNION;
#endif
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY2_itcm_tlb_entry2_START  (0)
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY2_itcm_tlb_entry2_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_ITCM_TLB_ENTRY3_UNION
 �ṹ˵��  : ITCM_TLB_ENTRY3 �Ĵ����ṹ���塣��ַƫ����:0x01C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ITCM��TLB_ENTY_3�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itcm_tlb_entry3 : 20; /* bit[0-19] : ITCM tlb_entry3��ֵ */
        unsigned int  reserved        : 12; /* bit[20-31]: reserved */
    } reg;
} SOC_TCM_WRAP_ITCM_TLB_ENTRY3_UNION;
#endif
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY3_itcm_tlb_entry3_START  (0)
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY3_itcm_tlb_entry3_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_ITCM_TLB_ENTRY4_UNION
 �ṹ˵��  : ITCM_TLB_ENTRY4 �Ĵ����ṹ���塣��ַƫ����:0x020����ֵ:0x00000000�����:32
 �Ĵ���˵��: ITCM��TLB_ENTY_4�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itcm_tlb_entry4 : 20; /* bit[0-19] : ITCM tlb_entry4��ֵ */
        unsigned int  reserved        : 12; /* bit[20-31]: reserved */
    } reg;
} SOC_TCM_WRAP_ITCM_TLB_ENTRY4_UNION;
#endif
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY4_itcm_tlb_entry4_START  (0)
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY4_itcm_tlb_entry4_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_ITCM_TLB_ENTRY5_UNION
 �ṹ˵��  : ITCM_TLB_ENTRY5 �Ĵ����ṹ���塣��ַƫ����:0x024����ֵ:0x00000000�����:32
 �Ĵ���˵��: ITCM��TLB_ENTY_5�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itcm_tlb_entry5 : 20; /* bit[0-19] : ITCM tlb_entry5��ֵ */
        unsigned int  reserved        : 12; /* bit[20-31]: reserved */
    } reg;
} SOC_TCM_WRAP_ITCM_TLB_ENTRY5_UNION;
#endif
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY5_itcm_tlb_entry5_START  (0)
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY5_itcm_tlb_entry5_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_ITCM_TLB_ENTRY6_UNION
 �ṹ˵��  : ITCM_TLB_ENTRY6 �Ĵ����ṹ���塣��ַƫ����:0x028����ֵ:0x00000000�����:32
 �Ĵ���˵��: ITCM��TLB_ENTY_6�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itcm_tlb_entry6 : 20; /* bit[0-19] : ITCM tlb_entry6��ֵ */
        unsigned int  reserved        : 12; /* bit[20-31]: reserved */
    } reg;
} SOC_TCM_WRAP_ITCM_TLB_ENTRY6_UNION;
#endif
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY6_itcm_tlb_entry6_START  (0)
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY6_itcm_tlb_entry6_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_ITCM_TLB_ENTRY7_UNION
 �ṹ˵��  : ITCM_TLB_ENTRY7 �Ĵ����ṹ���塣��ַƫ����:0x02C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ITCM��TLB_ENTY_7�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itcm_tlb_entry7 : 20; /* bit[0-19] : ITCM tlb_entry7��ֵ */
        unsigned int  reserved        : 12; /* bit[20-31]: reserved */
    } reg;
} SOC_TCM_WRAP_ITCM_TLB_ENTRY7_UNION;
#endif
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY7_itcm_tlb_entry7_START  (0)
#define SOC_TCM_WRAP_ITCM_TLB_ENTRY7_itcm_tlb_entry7_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_D0TCM_TLB_ENTRY0_UNION
 �ṹ˵��  : D0TCM_TLB_ENTRY0 �Ĵ����ṹ���塣��ַƫ����:0x030����ֵ:0x00000000�����:32
 �Ĵ���˵��: D0TCM��TLB_ENTY_0�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d0tcm_tlb_entry0 : 19; /* bit[0-18] : d0tcm tlb_entry0��ֵ */
        unsigned int  reserved         : 13; /* bit[19-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D0TCM_TLB_ENTRY0_UNION;
#endif
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY0_d0tcm_tlb_entry0_START  (0)
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY0_d0tcm_tlb_entry0_END    (18)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_D0TCM_TLB_ENTRY1_UNION
 �ṹ˵��  : D0TCM_TLB_ENTRY1 �Ĵ����ṹ���塣��ַƫ����:0x034����ֵ:0x00000000�����:32
 �Ĵ���˵��: D0TCM��TLB_ENTY_1�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d0tcm_tlb_entry1 : 19; /* bit[0-18] : d0tcm tlb_entry1��ֵ */
        unsigned int  reserved         : 13; /* bit[19-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D0TCM_TLB_ENTRY1_UNION;
#endif
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY1_d0tcm_tlb_entry1_START  (0)
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY1_d0tcm_tlb_entry1_END    (18)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_D0TCM_TLB_ENTRY2_UNION
 �ṹ˵��  : D0TCM_TLB_ENTRY2 �Ĵ����ṹ���塣��ַƫ����:0x038����ֵ:0x00000000�����:32
 �Ĵ���˵��: D0TCM��TLB_ENTY_2�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d0tcm_tlb_entry2 : 19; /* bit[0-18] : d0tcm tlb_entry2��ֵ */
        unsigned int  reserved         : 13; /* bit[19-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D0TCM_TLB_ENTRY2_UNION;
#endif
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY2_d0tcm_tlb_entry2_START  (0)
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY2_d0tcm_tlb_entry2_END    (18)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_D0TCM_TLB_ENTRY3_UNION
 �ṹ˵��  : D0TCM_TLB_ENTRY3 �Ĵ����ṹ���塣��ַƫ����:0x03C����ֵ:0x00000000�����:32
 �Ĵ���˵��: D0TCM��TLB_ENTY_3�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d0tcm_tlb_entry3 : 19; /* bit[0-18] : d0tcm tlb_entry3��ֵ */
        unsigned int  reserved         : 13; /* bit[19-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D0TCM_TLB_ENTRY3_UNION;
#endif
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY3_d0tcm_tlb_entry3_START  (0)
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY3_d0tcm_tlb_entry3_END    (18)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_D0TCM_TLB_ENTRY4_UNION
 �ṹ˵��  : D0TCM_TLB_ENTRY4 �Ĵ����ṹ���塣��ַƫ����:0x040����ֵ:0x00000000�����:32
 �Ĵ���˵��: D0TCM��TLB_ENTY_4�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d0tcm_tlb_entry4 : 19; /* bit[0-18] : d0tcm tlb_entry4��ֵ */
        unsigned int  reserved         : 13; /* bit[19-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D0TCM_TLB_ENTRY4_UNION;
#endif
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY4_d0tcm_tlb_entry4_START  (0)
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY4_d0tcm_tlb_entry4_END    (18)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_D0TCM_TLB_ENTRY5_UNION
 �ṹ˵��  : D0TCM_TLB_ENTRY5 �Ĵ����ṹ���塣��ַƫ����:0x044����ֵ:0x00000000�����:32
 �Ĵ���˵��: D0TCM��TLB_ENTY_5�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d0tcm_tlb_entry5 : 19; /* bit[0-18] : d0tcm tlb_entry5��ֵ */
        unsigned int  reserved         : 13; /* bit[19-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D0TCM_TLB_ENTRY5_UNION;
#endif
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY5_d0tcm_tlb_entry5_START  (0)
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY5_d0tcm_tlb_entry5_END    (18)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_D0TCM_TLB_ENTRY6_UNION
 �ṹ˵��  : D0TCM_TLB_ENTRY6 �Ĵ����ṹ���塣��ַƫ����:0x048����ֵ:0x00000000�����:32
 �Ĵ���˵��: D0TCM��TLB_ENTY_6�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d0tcm_tlb_entry6 : 19; /* bit[0-18] : d0tcm tlb_entry6��ֵ */
        unsigned int  reserved         : 13; /* bit[19-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D0TCM_TLB_ENTRY6_UNION;
#endif
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY6_d0tcm_tlb_entry6_START  (0)
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY6_d0tcm_tlb_entry6_END    (18)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_D0TCM_TLB_ENTRY7_UNION
 �ṹ˵��  : D0TCM_TLB_ENTRY7 �Ĵ����ṹ���塣��ַƫ����:0x04C����ֵ:0x00000000�����:32
 �Ĵ���˵��: D0TCM��TLB_ENTY_7�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d0tcm_tlb_entry7 : 19; /* bit[0-18] : d0tcm tlb_entry7��ֵ */
        unsigned int  reserved         : 13; /* bit[19-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D0TCM_TLB_ENTRY7_UNION;
#endif
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY7_d0tcm_tlb_entry7_START  (0)
#define SOC_TCM_WRAP_D0TCM_TLB_ENTRY7_d0tcm_tlb_entry7_END    (18)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_D1TCM_TLB_ENTRY0_UNION
 �ṹ˵��  : D1TCM_TLB_ENTRY0 �Ĵ����ṹ���塣��ַƫ����:0x050����ֵ:0x00000000�����:32
 �Ĵ���˵��: D1TCM��TLB_ENTY_0�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d1tcm_tlb_entry0 : 19; /* bit[0-18] : d1tcm tlb_entry0��ֵ */
        unsigned int  reserved         : 13; /* bit[19-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D1TCM_TLB_ENTRY0_UNION;
#endif
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY0_d1tcm_tlb_entry0_START  (0)
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY0_d1tcm_tlb_entry0_END    (18)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_D1TCM_TLB_ENTRY1_UNION
 �ṹ˵��  : D1TCM_TLB_ENTRY1 �Ĵ����ṹ���塣��ַƫ����:0x054����ֵ:0x00000000�����:32
 �Ĵ���˵��: D1TCM��TLB_ENTY_1�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d1tcm_tlb_entry1 : 19; /* bit[0-18] : d1tcm tlb_entry1��ֵ */
        unsigned int  reserved         : 13; /* bit[19-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D1TCM_TLB_ENTRY1_UNION;
#endif
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY1_d1tcm_tlb_entry1_START  (0)
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY1_d1tcm_tlb_entry1_END    (18)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_D1TCM_TLB_ENTRY2_UNION
 �ṹ˵��  : D1TCM_TLB_ENTRY2 �Ĵ����ṹ���塣��ַƫ����:0x058����ֵ:0x00000000�����:32
 �Ĵ���˵��: D1TCM��TLB_ENTY_2�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d1tcm_tlb_entry2 : 19; /* bit[0-18] : d1tcm tlb_entry2��ֵ */
        unsigned int  reserved         : 13; /* bit[19-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D1TCM_TLB_ENTRY2_UNION;
#endif
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY2_d1tcm_tlb_entry2_START  (0)
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY2_d1tcm_tlb_entry2_END    (18)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_D1TCM_TLB_ENTRY3_UNION
 �ṹ˵��  : D1TCM_TLB_ENTRY3 �Ĵ����ṹ���塣��ַƫ����:0x05C����ֵ:0x00000000�����:32
 �Ĵ���˵��: D1TCM��TLB_ENTY_3�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d1tcm_tlb_entry3 : 19; /* bit[0-18] : d1tcm tlb_entry3��ֵ */
        unsigned int  reserved         : 13; /* bit[19-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D1TCM_TLB_ENTRY3_UNION;
#endif
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY3_d1tcm_tlb_entry3_START  (0)
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY3_d1tcm_tlb_entry3_END    (18)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_D1TCM_TLB_ENTRY4_UNION
 �ṹ˵��  : D1TCM_TLB_ENTRY4 �Ĵ����ṹ���塣��ַƫ����:0x060����ֵ:0x00000000�����:32
 �Ĵ���˵��: D1TCM��TLB_ENTY_4�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d1tcm_tlb_entry4 : 19; /* bit[0-18] : d1tcm tlb_entry4��ֵ */
        unsigned int  reserved         : 13; /* bit[19-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D1TCM_TLB_ENTRY4_UNION;
#endif
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY4_d1tcm_tlb_entry4_START  (0)
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY4_d1tcm_tlb_entry4_END    (18)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_D1TCM_TLB_ENTRY5_UNION
 �ṹ˵��  : D1TCM_TLB_ENTRY5 �Ĵ����ṹ���塣��ַƫ����:0x064����ֵ:0x00000000�����:32
 �Ĵ���˵��: D1TCM��TLB_ENTY_5�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d1tcm_tlb_entry5 : 19; /* bit[0-18] : d1tcm tlb_entry5��ֵ */
        unsigned int  reserved         : 13; /* bit[19-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D1TCM_TLB_ENTRY5_UNION;
#endif
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY5_d1tcm_tlb_entry5_START  (0)
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY5_d1tcm_tlb_entry5_END    (18)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_D1TCM_TLB_ENTRY6_UNION
 �ṹ˵��  : D1TCM_TLB_ENTRY6 �Ĵ����ṹ���塣��ַƫ����:0x068����ֵ:0x00000000�����:32
 �Ĵ���˵��: D1TCM��TLB_ENTY_6�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d1tcm_tlb_entry6 : 19; /* bit[0-18] : d1tcm tlb_entry6��ֵ */
        unsigned int  reserved         : 13; /* bit[19-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D1TCM_TLB_ENTRY6_UNION;
#endif
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY6_d1tcm_tlb_entry6_START  (0)
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY6_d1tcm_tlb_entry6_END    (18)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_D1TCM_TLB_ENTRY7_UNION
 �ṹ˵��  : D1TCM_TLB_ENTRY7 �Ĵ����ṹ���塣��ַƫ����:0x06C����ֵ:0x00000000�����:32
 �Ĵ���˵��: D1TCM��TLB_ENTY_7�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d1tcm_tlb_entry7 : 19; /* bit[0-18] : d1tcm tlb_entry7��ֵ */
        unsigned int  reserved         : 13; /* bit[19-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D1TCM_TLB_ENTRY7_UNION;
#endif
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY7_d1tcm_tlb_entry7_START  (0)
#define SOC_TCM_WRAP_D1TCM_TLB_ENTRY7_d1tcm_tlb_entry7_END    (18)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_ITCM_HIT_CNT_UNION
 �ṹ˵��  : ITCM_HIT_CNT �Ĵ����ṹ���塣��ַƫ����:0x070����ֵ:0x00000000�����:32
 �Ĵ���˵��: ITCM�����д����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itcm_hit_cnt : 32; /* bit[0-31]: ITCM�����д��� */
    } reg;
} SOC_TCM_WRAP_ITCM_HIT_CNT_UNION;
#endif
#define SOC_TCM_WRAP_ITCM_HIT_CNT_itcm_hit_cnt_START  (0)
#define SOC_TCM_WRAP_ITCM_HIT_CNT_itcm_hit_cnt_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_ITCM_MISS_CNT_UNION
 �ṹ˵��  : ITCM_MISS_CNT �Ĵ����ṹ���塣��ַƫ����:0x074����ֵ:0x00000000�����:32
 �Ĵ���˵��: ITCM��miss�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itcm_miss_cnt : 32; /* bit[0-31]: ITCM��miss���� */
    } reg;
} SOC_TCM_WRAP_ITCM_MISS_CNT_UNION;
#endif
#define SOC_TCM_WRAP_ITCM_MISS_CNT_itcm_miss_cnt_START  (0)
#define SOC_TCM_WRAP_ITCM_MISS_CNT_itcm_miss_cnt_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_D0TCM_HIT_CNT_UNION
 �ṹ˵��  : D0TCM_HIT_CNT �Ĵ����ṹ���塣��ַƫ����:0x078����ֵ:0x00000000�����:32
 �Ĵ���˵��: D0TCM�����д����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d0tcm_hit_cnt : 32; /* bit[0-31]: D0TCM�����д��� */
    } reg;
} SOC_TCM_WRAP_D0TCM_HIT_CNT_UNION;
#endif
#define SOC_TCM_WRAP_D0TCM_HIT_CNT_d0tcm_hit_cnt_START  (0)
#define SOC_TCM_WRAP_D0TCM_HIT_CNT_d0tcm_hit_cnt_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_D0TCM_MISS_CNT_UNION
 �ṹ˵��  : D0TCM_MISS_CNT �Ĵ����ṹ���塣��ַƫ����:0x07C����ֵ:0x00000000�����:32
 �Ĵ���˵��: D0TCM��miss�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d0tcm_miss_cnt : 32; /* bit[0-31]: D0TCM��miss���� */
    } reg;
} SOC_TCM_WRAP_D0TCM_MISS_CNT_UNION;
#endif
#define SOC_TCM_WRAP_D0TCM_MISS_CNT_d0tcm_miss_cnt_START  (0)
#define SOC_TCM_WRAP_D0TCM_MISS_CNT_d0tcm_miss_cnt_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_D1TCM_HIT_CNT_UNION
 �ṹ˵��  : D1TCM_HIT_CNT �Ĵ����ṹ���塣��ַƫ����:0x080����ֵ:0x00000000�����:32
 �Ĵ���˵��: D1TCM�����д����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d1tcm_hit_cnt : 32; /* bit[0-31]: D1TCM�����д��� */
    } reg;
} SOC_TCM_WRAP_D1TCM_HIT_CNT_UNION;
#endif
#define SOC_TCM_WRAP_D1TCM_HIT_CNT_d1tcm_hit_cnt_START  (0)
#define SOC_TCM_WRAP_D1TCM_HIT_CNT_d1tcm_hit_cnt_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_D1TCM_MISS_CNT_UNION
 �ṹ˵��  : D1TCM_MISS_CNT �Ĵ����ṹ���塣��ַƫ����:0x084����ֵ:0x00000000�����:32
 �Ĵ���˵��: D1TCM��miss�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d1tcm_miss_cnt : 32; /* bit[0-31]: D1TCM��miss���� */
    } reg;
} SOC_TCM_WRAP_D1TCM_MISS_CNT_UNION;
#endif
#define SOC_TCM_WRAP_D1TCM_MISS_CNT_d1tcm_miss_cnt_START  (0)
#define SOC_TCM_WRAP_D1TCM_MISS_CNT_d1tcm_miss_cnt_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_TCMADDR_BOUNDARY_CHECK_BYPASS_UNION
 �ṹ˵��  : TCMADDR_BOUNDARY_CHECK_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x098����ֵ:0x00000003�����:32
 �Ĵ���˵��: TCM ADDRESS�߽��鹦��ʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tcmaddr_boundary_check_bypass : 1;  /* bit[0-0] : tcmaddr�߽��鹦��
                                                                        1'b0:��bypass��ʹ���������
                                                                        1'b1:bypass��鹦�� */
        unsigned int  bank_collision_check_bypass   : 1;  /* bit[1-1] : bank��ͻ��鹦��
                                                                        1'b0:ʹ��bank��ͻ���
                                                                        1'b1:bypass��鹦�� */
        unsigned int  reserved                      : 30; /* bit[2-31]: reserved */
    } reg;
} SOC_TCM_WRAP_TCMADDR_BOUNDARY_CHECK_BYPASS_UNION;
#endif
#define SOC_TCM_WRAP_TCMADDR_BOUNDARY_CHECK_BYPASS_tcmaddr_boundary_check_bypass_START  (0)
#define SOC_TCM_WRAP_TCMADDR_BOUNDARY_CHECK_BYPASS_tcmaddr_boundary_check_bypass_END    (0)
#define SOC_TCM_WRAP_TCMADDR_BOUNDARY_CHECK_BYPASS_bank_collision_check_bypass_START    (1)
#define SOC_TCM_WRAP_TCMADDR_BOUNDARY_CHECK_BYPASS_bank_collision_check_bypass_END      (1)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_TCM_ERR_TYPE_UNION
 �ṹ˵��  : TCM_ERR_TYPE �Ĵ����ṹ���塣��ַƫ����:0x09C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ITCM�������ͼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itcm_page_err          : 1;  /* bit[0-0]  : ITCMȱҳ����
                                                                  1'b0:�޴�
                                                                  1'b1:�д� */
        unsigned int  itcmaddr_out_320k_err  : 1;  /* bit[1-1]  : ITCM���ʳ���320K�ռ����
                                                                  1'b0:�޴�
                                                                  1'b1:�д� */
        unsigned int  reserved_0             : 2;  /* bit[2-3]  : reserved */
        unsigned int  d0tcm_page_err         : 1;  /* bit[4-4]  : D0TCMȱҳ����
                                                                  1'b0:�޴�
                                                                  1'b1:�д� */
        unsigned int  d0tcmaddr_out_320k_err : 1;  /* bit[5-5]  : D0TCM���ʳ���320K�ռ����
                                                                  1'b0:�޴�
                                                                  1'b1:�д� */
        unsigned int  reserved_1             : 2;  /* bit[6-7]  : reserved */
        unsigned int  d1tcm_page_err         : 1;  /* bit[8-8]  : D1TCMȱҳ����
                                                                  1'b0:�޴�
                                                                  1'b1:�д� */
        unsigned int  d1tcmaddr_out_320k_err : 1;  /* bit[9-9]  : D1TCM���ʳ���320K�ռ����
                                                                  1'b0:�޴�
                                                                  1'b1:�д� */
        unsigned int  reserved_2             : 2;  /* bit[10-11]: reserved */
        unsigned int  itcm_err_bank0         : 1;  /* bit[12-12]: ITCM�Ƿ�����˷����DTCM��bank0
                                                                  1'b1:�����˷����DTCM��bank0
                                                                  1'b0:δ���� */
        unsigned int  itcm_err_bank1         : 1;  /* bit[13-13]: ITCM�Ƿ�����˷����DTCM��bank1
                                                                  1'b1:�����˷����DTCM��bank1
                                                                  1'b0:δ���� */
        unsigned int  itcm_err_bank2         : 1;  /* bit[14-14]: ITCM�Ƿ�����˷����DTCM��bank2
                                                                  1'b1:�����˷����DTCM��bank2
                                                                  1'b0:δ���� */
        unsigned int  itcm_err_bank3         : 1;  /* bit[15-15]: ITCM�Ƿ�����˷����DTCM��bank3
                                                                  1'b1:�����˷����DTCM��bank3
                                                                  1'b0:δ���� */
        unsigned int  itcm_err_bank4         : 1;  /* bit[16-16]: ITCM�Ƿ�����˷����DTCM��bank4
                                                                  1'b1:�����˷����DTCM��bank4
                                                                  1'b0:δ���� */
        unsigned int  d0tcm_err_bank0        : 1;  /* bit[17-17]: D0TCM�Ƿ�����˷����ITCM��bank0
                                                                  1'b1:�����˷����ITCM��bank0
                                                                  1'b0:δ���� */
        unsigned int  d0tcm_err_bank1        : 1;  /* bit[18-18]: D0TCM�Ƿ�����˷����ITCM��bank1
                                                                  1'b1:�����˷����ITCM��bank1
                                                                  1'b0:δ���� */
        unsigned int  d0tcm_err_bank2        : 1;  /* bit[19-19]: D0TCM�Ƿ�����˷����ITCM��bank2
                                                                  1'b1:�����˷����ITCM��bank2
                                                                  1'b0:δ���� */
        unsigned int  d0tcm_err_bank3        : 1;  /* bit[20-20]: D0TCM�Ƿ�����˷����ITCM��bank3
                                                                  1'b1:�����˷����ITCM��bank3
                                                                  1'b0:δ���� */
        unsigned int  d0tcm_err_bank4        : 1;  /* bit[21-21]: D0TCM�Ƿ�����˷����ITCM��bank4
                                                                  1'b1:�����˷����ITCM��bank4
                                                                  1'b0:δ���� */
        unsigned int  d1tcm_err_bank0        : 1;  /* bit[22-22]: D1TCM�Ƿ�����˷����ITCM��bank0
                                                                  1'b1:�����˷����ITCM��bank0
                                                                  1'b0:δ���� */
        unsigned int  d1tcm_err_bank1        : 1;  /* bit[23-23]: D1TCM�Ƿ�����˷����ITCM��bank1
                                                                  1'b1:�����˷����ITCM��bank1
                                                                  1'b0:δ���� */
        unsigned int  d1tcm_err_bank2        : 1;  /* bit[24-24]: D1TCM�Ƿ�����˷����ITCM��bank2
                                                                  1'b1:�����˷����ITCM��bank2
                                                                  1'b0:δ���� */
        unsigned int  d1tcm_err_bank3        : 1;  /* bit[25-25]: D1TCM�Ƿ�����˷����ITCM��bank3
                                                                  1'b1:�����˷����ITCM��bank3
                                                                  1'b0:δ���� */
        unsigned int  d1tcm_err_bank4        : 1;  /* bit[26-26]: D1TCM�Ƿ�����˷����ITCM��bank4
                                                                  1'b1:�����˷����ITCM��bank4
                                                                  1'b0:δ���� */
        unsigned int  reserved_3             : 5;  /* bit[27-31]: reserved */
    } reg;
} SOC_TCM_WRAP_TCM_ERR_TYPE_UNION;
#endif
#define SOC_TCM_WRAP_TCM_ERR_TYPE_itcm_page_err_START           (0)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_itcm_page_err_END             (0)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_itcmaddr_out_320k_err_START   (1)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_itcmaddr_out_320k_err_END     (1)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d0tcm_page_err_START          (4)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d0tcm_page_err_END            (4)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d0tcmaddr_out_320k_err_START  (5)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d0tcmaddr_out_320k_err_END    (5)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d1tcm_page_err_START          (8)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d1tcm_page_err_END            (8)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d1tcmaddr_out_320k_err_START  (9)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d1tcmaddr_out_320k_err_END    (9)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_itcm_err_bank0_START          (12)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_itcm_err_bank0_END            (12)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_itcm_err_bank1_START          (13)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_itcm_err_bank1_END            (13)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_itcm_err_bank2_START          (14)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_itcm_err_bank2_END            (14)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_itcm_err_bank3_START          (15)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_itcm_err_bank3_END            (15)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_itcm_err_bank4_START          (16)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_itcm_err_bank4_END            (16)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d0tcm_err_bank0_START         (17)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d0tcm_err_bank0_END           (17)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d0tcm_err_bank1_START         (18)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d0tcm_err_bank1_END           (18)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d0tcm_err_bank2_START         (19)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d0tcm_err_bank2_END           (19)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d0tcm_err_bank3_START         (20)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d0tcm_err_bank3_END           (20)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d0tcm_err_bank4_START         (21)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d0tcm_err_bank4_END           (21)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d1tcm_err_bank0_START         (22)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d1tcm_err_bank0_END           (22)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d1tcm_err_bank1_START         (23)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d1tcm_err_bank1_END           (23)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d1tcm_err_bank2_START         (24)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d1tcm_err_bank2_END           (24)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d1tcm_err_bank3_START         (25)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d1tcm_err_bank3_END           (25)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d1tcm_err_bank4_START         (26)
#define SOC_TCM_WRAP_TCM_ERR_TYPE_d1tcm_err_bank4_END           (26)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_BANK_SEL_UNION
 �ṹ˵��  : BANK_SEL �Ĵ����ṹ���塣��ַƫ����:0x0A0����ֵ:0x0000001C�����:32
 �Ĵ���˵��: BANKѡ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bank0_sel : 1;  /* bit[0-0] : bank0�����ITCM����DTCM
                                                    1'b0:�����ITCM
                                                    1'b1:�����DTCM */
        unsigned int  bank1_sel : 1;  /* bit[1-1] : bank1�����ITCM����DTCM
                                                    1'b0:�����ITCM
                                                    1'b1:�����DTCM */
        unsigned int  bank2_sel : 1;  /* bit[2-2] : bank2�����ITCM����DTCM
                                                    1'b0:�����ITCM
                                                    1'b1:�����DTCM */
        unsigned int  bank3_sel : 1;  /* bit[3-3] : bank3�����ITCM����DTCM
                                                    1'b0:�����ITCM
                                                    1'b1:�����DTCM */
        unsigned int  bank4_sel : 1;  /* bit[4-4] : bank4�����ITCM����DTCM
                                                    1'b0:�����ITCM
                                                    1'b1:�����DTCM */
        unsigned int  reserved  : 27; /* bit[5-31]: reserved */
    } reg;
} SOC_TCM_WRAP_BANK_SEL_UNION;
#endif
#define SOC_TCM_WRAP_BANK_SEL_bank0_sel_START  (0)
#define SOC_TCM_WRAP_BANK_SEL_bank0_sel_END    (0)
#define SOC_TCM_WRAP_BANK_SEL_bank1_sel_START  (1)
#define SOC_TCM_WRAP_BANK_SEL_bank1_sel_END    (1)
#define SOC_TCM_WRAP_BANK_SEL_bank2_sel_START  (2)
#define SOC_TCM_WRAP_BANK_SEL_bank2_sel_END    (2)
#define SOC_TCM_WRAP_BANK_SEL_bank3_sel_START  (3)
#define SOC_TCM_WRAP_BANK_SEL_bank3_sel_END    (3)
#define SOC_TCM_WRAP_BANK_SEL_bank4_sel_START  (4)
#define SOC_TCM_WRAP_BANK_SEL_bank4_sel_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_ITCM_ERR_ADDR_UNION
 �ṹ˵��  : ITCM_ERR_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0A8����ֵ:0x00000000�����:32
 �Ĵ���˵��: ITCM�����ַ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itcm_err_addr : 23; /* bit[0-22] : ITCM��������ĵ�ַ */
        unsigned int  reserved      : 9;  /* bit[23-31]: reserved */
    } reg;
} SOC_TCM_WRAP_ITCM_ERR_ADDR_UNION;
#endif
#define SOC_TCM_WRAP_ITCM_ERR_ADDR_itcm_err_addr_START  (0)
#define SOC_TCM_WRAP_ITCM_ERR_ADDR_itcm_err_addr_END    (22)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_D0TCM_ERR_ADDR_UNION
 �ṹ˵��  : D0TCM_ERR_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0AC����ֵ:0x00000000�����:32
 �Ĵ���˵��: D0TCM�����ַ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d0tcm_err_addr : 22; /* bit[0-21] : D0TCM��������ĵ�ַ */
        unsigned int  reserved       : 10; /* bit[22-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D0TCM_ERR_ADDR_UNION;
#endif
#define SOC_TCM_WRAP_D0TCM_ERR_ADDR_d0tcm_err_addr_START  (0)
#define SOC_TCM_WRAP_D0TCM_ERR_ADDR_d0tcm_err_addr_END    (21)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_D1TCM_ERR_ADDR_UNION
 �ṹ˵��  : D1TCM_ERR_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0B0����ֵ:0x00000000�����:32
 �Ĵ���˵��: D1TCM�����ַ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d1tcm_err_addr : 22; /* bit[0-21] : D1TCM��������ĵ�ַ */
        unsigned int  reserved       : 10; /* bit[22-31]: reserved */
    } reg;
} SOC_TCM_WRAP_D1TCM_ERR_ADDR_UNION;
#endif
#define SOC_TCM_WRAP_D1TCM_ERR_ADDR_d1tcm_err_addr_START  (0)
#define SOC_TCM_WRAP_D1TCM_ERR_ADDR_d1tcm_err_addr_END    (21)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_ITCM_ERR_CNT_UNION
 �ṹ˵��  : ITCM_ERR_CNT �Ĵ����ṹ���塣��ַƫ����:0x0B4����ֵ:0x00000000�����:32
 �Ĵ���˵��: ITCM����������Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itcm_err_cnt : 32; /* bit[0-31]: ITCM ERR������ */
    } reg;
} SOC_TCM_WRAP_ITCM_ERR_CNT_UNION;
#endif
#define SOC_TCM_WRAP_ITCM_ERR_CNT_itcm_err_cnt_START  (0)
#define SOC_TCM_WRAP_ITCM_ERR_CNT_itcm_err_cnt_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_D0TCM_ERR_CNT_UNION
 �ṹ˵��  : D0TCM_ERR_CNT �Ĵ����ṹ���塣��ַƫ����:0x0B8����ֵ:0x00000000�����:32
 �Ĵ���˵��: D0TCM����������Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d0tcm_err_cnt : 32; /* bit[0-31]: D0TCM ERR������ */
    } reg;
} SOC_TCM_WRAP_D0TCM_ERR_CNT_UNION;
#endif
#define SOC_TCM_WRAP_D0TCM_ERR_CNT_d0tcm_err_cnt_START  (0)
#define SOC_TCM_WRAP_D0TCM_ERR_CNT_d0tcm_err_cnt_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_TCM_WRAP_D1TCM_ERR_CNT_UNION
 �ṹ˵��  : D1TCM_ERR_CNT �Ĵ����ṹ���塣��ַƫ����:0x0BC����ֵ:0x00000000�����:32
 �Ĵ���˵��: D1TCM����������Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  d1tcm_err_cnt : 32; /* bit[0-31]: D1TCM ERR������ */
    } reg;
} SOC_TCM_WRAP_D1TCM_ERR_CNT_UNION;
#endif
#define SOC_TCM_WRAP_D1TCM_ERR_CNT_d1tcm_err_cnt_START  (0)
#define SOC_TCM_WRAP_D1TCM_ERR_CNT_d1tcm_err_cnt_END    (31)






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

#endif /* end of soc_tcm_wrap_interface.h */
