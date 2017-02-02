/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_dss_mctl_mutex_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:20:10
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_DSS_MCTL_MUTEX.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_DSS_MCTL_MUTEX_INTERFACE_H__
#define __SOC_DSS_MCTL_MUTEX_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_MCTL_MUTEX
 ****************************************************************************/
/* �Ĵ���˵��������ʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_MUTEX_CTL_EN_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_EN_ADDR(base)          ((base) + (0x0000))

/* �Ĵ���˵����MUTEX���ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_ADDR(base)       ((base) + (0x0004))

/* �Ĵ���˵����MUTEX״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_STATUS_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_STATUS_ADDR(base) ((base) + (0x0008))

/* �Ĵ���˵����ITFѡ��Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_ITF_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_ITF_ADDR(base)   ((base) + (0x000C))

/* �Ĵ���˵����DBUFѡ��Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_DBUF_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_DBUF_ADDR(base)  ((base) + (0x0010))

/* �Ĵ���˵����OV0���scfѡ��Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_SCF_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_SCF_ADDR(base)   ((base) + (0x0014))

/* �Ĵ���˵����OV��ѡ��Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_OV_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_OV_ADDR(base)    ((base) + (0x0018))

/* �Ĵ���˵����WCH0ѡ��Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_WCH0_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_WCH0_ADDR(base)  ((base) + (0x0020))

/* �Ĵ���˵����WCH1��ѡ��Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_WCH1_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_WCH1_ADDR(base)  ((base) + (0x0024))

/* �Ĵ���˵����RCH0��ѡ��Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH0_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH0_ADDR(base)  ((base) + (0x0030))

/* �Ĵ���˵����RCH1��ѡ��Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH1_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH1_ADDR(base)  ((base) + (0x0034))

/* �Ĵ���˵����RCH2��ѡ��Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH2_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH2_ADDR(base)  ((base) + (0x0038))

/* �Ĵ���˵����RCH3��ѡ��Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH3_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH3_ADDR(base)  ((base) + (0x003C))

/* �Ĵ���˵����RCH4��ѡ��Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH4_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH4_ADDR(base)  ((base) + (0x0040))

/* �Ĵ���˵����RCH5��ѡ��Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH5_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH5_ADDR(base)  ((base) + (0x0044))

/* �Ĵ���˵����RCH6��ѡ��Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH6_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH6_ADDR(base)  ((base) + (0x0048))

/* �Ĵ���˵����RCH7��ѡ��Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH7_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH7_ADDR(base)  ((base) + (0x004C))

/* �Ĵ���˵����CTL TOP�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_MUTEX_CTL_TOP_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_TOP_ADDR(base)         ((base) + (0x0050))

/* �Ĵ���˵����MOD����ˢ��״̬
   λ����UNION�ṹ:  SOC_DSS_MCTL_MUTEX_CTL_FLUSH_STATUS_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_FLUSH_STATUS_ADDR(base) ((base) + (0x0054))

/* �Ĵ���˵��������峡����
   λ����UNION�ṹ:  SOC_DSS_MCTL_MUTEX_CTL_CLEAR_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_CLEAR_ADDR(base)       ((base) + (0x0058))

/* �Ĵ���˵����Clear ACK��ʱ���üĴ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_MUTEX_CTL_CACK_TOUT_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_CACK_TOUT_ADDR(base)   ((base) + (0x0060))

/* �Ĵ���˵����MUTEX��ʱ���üĴ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_MUTEX_CTL_MUTEX_TOUT_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_TOUT_ADDR(base)  ((base) + (0x0064))

/* �Ĵ���˵��������״̬
   λ����UNION�ṹ:  SOC_DSS_MCTL_MUTEX_CTL_STATUS_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_STATUS_ADDR(base)      ((base) + (0x0068))

/* �Ĵ���˵���������ж�ʹ��
   λ����UNION�ṹ:  SOC_DSS_MCTL_MUTEX_CTL_INTEN_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_INTEN_ADDR(base)       ((base) + (0x006C))

/* �Ĵ���˵����һ��ģ��ʱ��ѡ���ź�
   λ����UNION�ṹ:  SOC_DSS_MCTL_MUTEX_CTL_CLK_SEL_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_CLK_SEL_ADDR(base)     ((base) + (0x0080))

/* �Ĵ���˵����һ��ģ��ʱ��ʹ���ź�
   λ����UNION�ṹ:  SOC_DSS_MCTL_MUTEX_CTL_CLK_EN_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_CLK_EN_ADDR(base)      ((base) + (0x0084))

/* �Ĵ���˵������ά�ɲ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_MUTEX_CTL_DBG_UNION */
#define SOC_DSS_MCTL_MUTEX_CTL_DBG_ADDR(base)         ((base) + (0x00E0))





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
                     (1/1) reg_MCTL_MUTEX
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_MUTEX_CTL_EN_UNION
 �ṹ˵��  : CTL_EN �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_en   : 1;  /* bit[0]   : 1'b1 : CTLʹ��
                                                   1'b0 : CTL��ֹ */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_EN_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_EN_ctl_en_START    (0)
#define SOC_DSS_MCTL_MUTEX_CTL_EN_ctl_en_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_UNION
 �ṹ˵��  : CTL_MUTEX �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: MUTEX���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_sw : 1;  /* bit[0]   : 1'b1 : ����������������ڵ�ǰMUTEX��module
                                                       1'b0 : reserved */
        unsigned int  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_ctl_mutex_sw_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_ctl_mutex_sw_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_STATUS_UNION
 �ṹ˵��  : CTL_MUTEX_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: MUTEX״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_status : 1;  /* bit[0]   : mutex��ǰ״̬
                                                           1'b1 : ��������������ڵ�ǰMUTEX��module
                                                           1'b0 : reserved
                                                           ��λֵ��0x0 */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_STATUS_ctl_mutex_status_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_STATUS_ctl_mutex_status_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_ITF_UNION
 �ṹ˵��  : CTL_MUTEX_ITF �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ITFѡ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_itf : 2;  /* bit[0-1] : ��ǰmodule״̬
                                                        1'b1��module��ѡ���ڵ�ǰCTL
                                                        1'b0��reserved
                                                        [1:0]
                                                         2'h1:itf0 dpp ifbc
                                                         2'h2,itf1
                                                         2'h3,2'h0: ��Ч  */
        unsigned int  reserved      : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_ITF_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_ITF_ctl_mutex_itf_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_ITF_ctl_mutex_itf_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_DBUF_UNION
 �ṹ˵��  : CTL_MUTEX_DBUF �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: DBUFѡ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_dbuf : 2;  /* bit[0-1] : ��ǰmodule״̬
                                                          2'h1:dbuf0��ѡ���ڵ�ǰCTL
                                                          2'h2,dbuf1��ѡ���ڵ�ǰCTL
                                                          2'h3,2'h0: ��Ч  */
        unsigned int  reserved       : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_DBUF_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_DBUF_ctl_mutex_dbuf_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_DBUF_ctl_mutex_dbuf_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_SCF_UNION
 �ṹ˵��  : CTL_MUTEX_SCF �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: OV0���scfѡ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_scf : 1;  /* bit[0]   : ��ǰmodule״̬
                                                        1'b1��scf ��ѡ���ڵ�ǰCTL
                                                        1'b0��reserved  */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_SCF_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_SCF_ctl_mutex_scf_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_SCF_ctl_mutex_scf_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_OV_UNION
 �ṹ˵��  : CTL_MUTEX_OV �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: OV��ѡ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_ov : 4;  /* bit[0-3] : ��ǰmodule״̬
                                                        4'h1:ov0��ѡ���ڵ�ǰCTL,
                                                        4'h2:ov1��ѡ���ڵ�ǰCTL,
                                                        4'h4:ov2��ѡ���ڵ�ǰCTL,
                                                        4'h8:ov3��ѡ���ڵ�ǰCTL,
                                                        other ��Ч */
        unsigned int  reserved     : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_OV_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_OV_ctl_mutex_ov_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_OV_ctl_mutex_ov_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_WCH0_UNION
 �ṹ˵��  : CTL_MUTEX_WCH0 �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: WCH0ѡ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_wch0 : 1;  /* bit[0]   : ��ǰmodule״̬
                                                         1'b1��wch0��ѡ���ڵ�ǰCTL
                                                         1'b0��reserved */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_WCH0_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_WCH0_ctl_mutex_wch0_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_WCH0_ctl_mutex_wch0_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_WCH1_UNION
 �ṹ˵��  : CTL_MUTEX_WCH1 �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x00000000�����:32
 �Ĵ���˵��: WCH1��ѡ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_wch1 : 1;  /* bit[0]   : ��ǰmodule״̬
                                                         1'b1��wch1��ѡ���ڵ�ǰCTL
                                                         1'b0��reserved */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_WCH1_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_WCH1_ctl_mutex_wch1_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_WCH1_ctl_mutex_wch1_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH0_UNION
 �ṹ˵��  : CTL_MUTEX_RCH0 �Ĵ����ṹ���塣��ַƫ����:0x0030����ֵ:0x00000000�����:32
 �Ĵ���˵��: RCH0��ѡ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_rch0 : 1;  /* bit[0]   : ��ǰmodule״̬
                                                         1'b1��rch0��ѡ���ڵ�ǰCTL
                                                         1'b0��reserved */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH0_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH0_ctl_mutex_rch0_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH0_ctl_mutex_rch0_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH1_UNION
 �ṹ˵��  : CTL_MUTEX_RCH1 �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x00000000�����:32
 �Ĵ���˵��: RCH1��ѡ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_rch1 : 1;  /* bit[0]   : ��ǰmodule״̬
                                                         1'b1��rch1��ѡ���ڵ�ǰCTL
                                                         1'b0��reserved */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH1_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH1_ctl_mutex_rch1_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH1_ctl_mutex_rch1_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH2_UNION
 �ṹ˵��  : CTL_MUTEX_RCH2 �Ĵ����ṹ���塣��ַƫ����:0x0038����ֵ:0x00000000�����:32
 �Ĵ���˵��: RCH2��ѡ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_rch2 : 1;  /* bit[0]   : ��ǰmodule״̬
                                                         1'b1��rch2��ѡ���ڵ�ǰCTL
                                                         1'b0��reserved */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH2_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH2_ctl_mutex_rch2_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH2_ctl_mutex_rch2_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH3_UNION
 �ṹ˵��  : CTL_MUTEX_RCH3 �Ĵ����ṹ���塣��ַƫ����:0x003C����ֵ:0x00000000�����:32
 �Ĵ���˵��: RCH3��ѡ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_rch3 : 1;  /* bit[0]   : ��ǰmodule״̬
                                                         1'b1��rch3��ѡ���ڵ�ǰCTL
                                                         1'b0��reserved */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH3_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH3_ctl_mutex_rch3_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH3_ctl_mutex_rch3_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH4_UNION
 �ṹ˵��  : CTL_MUTEX_RCH4 �Ĵ����ṹ���塣��ַƫ����:0x0040����ֵ:0x00000000�����:32
 �Ĵ���˵��: RCH4��ѡ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_rch4 : 1;  /* bit[0]   : ��ǰmodule״̬
                                                         1'b1��rch4��ѡ���ڵ�ǰCTL
                                                         1'b0��reserved */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH4_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH4_ctl_mutex_rch4_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH4_ctl_mutex_rch4_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH5_UNION
 �ṹ˵��  : CTL_MUTEX_RCH5 �Ĵ����ṹ���塣��ַƫ����:0x0044����ֵ:0x00000000�����:32
 �Ĵ���˵��: RCH5��ѡ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_rch5 : 1;  /* bit[0]   : ��ǰmodule״̬
                                                         1'b1��rch5��ѡ���ڵ�ǰCTL
                                                         1'b0��reserved */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH5_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH5_ctl_mutex_rch5_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH5_ctl_mutex_rch5_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH6_UNION
 �ṹ˵��  : CTL_MUTEX_RCH6 �Ĵ����ṹ���塣��ַƫ����:0x0048����ֵ:0x00000000�����:32
 �Ĵ���˵��: RCH6��ѡ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_rch6 : 1;  /* bit[0]   : ��ǰmodule״̬
                                                         1'b1��rch6��ѡ���ڵ�ǰCTL
                                                         1'b0��reserved */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH6_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH6_ctl_mutex_rch6_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH6_ctl_mutex_rch6_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH7_UNION
 �ṹ˵��  : CTL_MUTEX_RCH7 �Ĵ����ṹ���塣��ַƫ����:0x004C����ֵ:0x00000000�����:32
 �Ĵ���˵��: RCH7��ѡ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_rch7 : 1;  /* bit[0]   : ��ǰmodule״̬
                                                         1'b1��rch7��ѡ���ڵ�ǰCTL
                                                         1'b0��reserved */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH7_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH7_ctl_mutex_rch7_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_RCH7_ctl_mutex_rch7_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_MUTEX_CTL_TOP_UNION
 �ṹ˵��  : CTL_TOP �Ĵ����ṹ���塣��ַƫ����:0x0050����ֵ:0x00000008�����:32
 �Ĵ���˵��: CTL TOP�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_sof_sel    : 2;  /* bit[0-1] : ѡ��MUTEX��ģʽ
                                                         0x1��singleģʽ
                                                         0x2��ITF0 ��ˢ��ģʽ
                                                         0x3��ITF1 ��ˢ��ģʽ
                                                         ����������� */
        unsigned int  ctl_frm_st_sel : 1;  /* bit[2]   : ֡�����ź�ѡ��
                                                         0:frame_start ��֡�����ź�;
                                                         1:frame_end ��֡�����ź�.
                                                         ��λֵ0x0 */
        unsigned int  ctl_block_mode : 1;  /* bit[3]   : ���� */
        unsigned int  reserved       : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_TOP_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_TOP_ctl_sof_sel_START     (0)
#define SOC_DSS_MCTL_MUTEX_CTL_TOP_ctl_sof_sel_END       (1)
#define SOC_DSS_MCTL_MUTEX_CTL_TOP_ctl_frm_st_sel_START  (2)
#define SOC_DSS_MCTL_MUTEX_CTL_TOP_ctl_frm_st_sel_END    (2)
#define SOC_DSS_MCTL_MUTEX_CTL_TOP_ctl_block_mode_START  (3)
#define SOC_DSS_MCTL_MUTEX_CTL_TOP_ctl_block_mode_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_MUTEX_CTL_FLUSH_STATUS_UNION
 �ṹ˵��  : CTL_FLUSH_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0054����ֵ:0x00000000�����:32
 �Ĵ���˵��: MOD����ˢ��״̬
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mod_flush_status : 32; /* bit[0-31]: ���� */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_FLUSH_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_FLUSH_STATUS_ctl_mod_flush_status_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_FLUSH_STATUS_ctl_mod_flush_status_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_MUTEX_CTL_CLEAR_UNION
 �ṹ˵��  : CTL_CLEAR �Ĵ����ṹ���塣��ַƫ����:0x0058����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����峡����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_sw_clr : 1;  /* bit[0]   : �������һ�Σ��Ե�ǰMUTEX���Լ���ǰmutex���Ƶ��ڵ�module���һ��������� */
        unsigned int  reserved   : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_CLEAR_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_CLEAR_ctl_sw_clr_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_CLEAR_ctl_sw_clr_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_MUTEX_CTL_CACK_TOUT_UNION
 �ṹ˵��  : CTL_CACK_TOUT �Ĵ����ṹ���塣��ַƫ����:0x0060����ֵ:0x000003FF�����:32
 �Ĵ���˵��: Clear ACK��ʱ���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_cack_tout : 16; /* bit[0-15] : CTLͨ·����clear ack��ʱ�����Ĵ��� */
        unsigned int  reserved      : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_CACK_TOUT_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_CACK_TOUT_ctl_cack_tout_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_CACK_TOUT_ctl_cack_tout_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_MUTEX_CTL_MUTEX_TOUT_UNION
 �ṹ˵��  : CTL_MUTEX_TOUT �Ĵ����ṹ���塣��ַƫ����:0x0064����ֵ:0x000003FF�����:32
 �Ĵ���˵��: MUTEX��ʱ���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_mutex_tout : 16; /* bit[0-15] : mutex��ʱ��������SOF�����������мĴ���reload������ʱ�䡣 */
        unsigned int  reserved       : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_MUTEX_TOUT_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_TOUT_ctl_mutex_tout_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_MUTEX_TOUT_ctl_mutex_tout_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_MUTEX_CTL_STATUS_UNION
 �ṹ˵��  : CTL_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0068����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����״̬
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_status : 3;  /* bit[0-2] : [0] : �峡��ʱ
                                                     [1] : mutex��ʱ
                                                     [2] : all reload update��� */
        unsigned int  reserved   : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_STATUS_ctl_status_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_STATUS_ctl_status_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_MUTEX_CTL_INTEN_UNION
 �ṹ˵��  : CTL_INTEN �Ĵ����ṹ���塣��ַƫ����:0x006C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����ж�ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_inten : 3;  /* bit[0-2] : [0] : �峡��ʱ�ж�ʹ��
                                                    [1] : mutex��ʱ�ж�ʹ��
                                                    [2] : all reload update����ж� */
        unsigned int  reserved  : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_INTEN_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_INTEN_ctl_inten_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_INTEN_ctl_inten_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_MUTEX_CTL_CLK_SEL_UNION
 �ṹ˵��  : CTL_CLK_SEL �Ĵ����ṹ���塣��ַƫ����:0x0080����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: һ��ģ��ʱ��ѡ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_clk_sel : 32; /* bit[0-31]: ��һ��ģ���ʱ��ѡ���źţ�
                                                      1����ʾǿ�ƴ�ʱ�ӡ�
                                                      0����ʾ��Ҫ���������Ӳ����ʱ��ʹ����������ر�ʱ��
                                                      [0] reg
                                                      [1] ctl/mutex
                                                      [31:2]��reserved */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_CLK_SEL_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_CLK_SEL_ctl_clk_sel_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_CLK_SEL_ctl_clk_sel_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_MUTEX_CTL_CLK_EN_UNION
 �ṹ˵��  : CTL_CLK_EN �Ĵ����ṹ���塣��ַƫ����:0x0084����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: һ��ģ��ʱ��ʹ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_clk_en : 32; /* bit[0-31]: ��һ��ģ������ʱ��ʹ���ź�
                                                     1����ʾ���ʱ��ʹ����Ч������Ӳ������
                                                     0����ʾ���ʱ��ʹ����Ч����ֹӲ������
                                                     [0] reg
                                                     [1] ctl/mutex
                                                     [31:2]��reserved */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_CLK_EN_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_CLK_EN_ctl_clk_en_START  (0)
#define SOC_DSS_MCTL_MUTEX_CTL_CLK_EN_ctl_clk_en_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_MUTEX_CTL_DBG_UNION
 �ṹ˵��  : CTL_DBG �Ĵ����ṹ���塣��ַƫ����:0x00E0����ֵ:0x00002600�����:32
 �Ĵ���˵��: ��ά�ɲ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_dbg  : 24; /* bit[0-23] : [23] 1'b1����֧��soft clear
                                                    [22] 1'b1��Ĭ��single mode����clear������bit��1��single mode����֡βѡ�񷢳�clear��
                                                    [18:16] reserved��
                                                    [21] 1'b1��holdclear ack�źţ����ֵ���һ֡֡ͷ������
                                                    [20] 1'b1��cmdlist��֡event listѡ����mctl�ġ�
                                                     1'b0��cmdlist��֡event listѡ����ldi�ġ�
                                                    [19] 1'b1��֧��unflow��֡βclearͬʱ��Ч��
                                                    [15] 1'b1���յ�unflow���̷���clear��
                                                     1'b0���յ�unflow����¼��֡β����clear��
                                                    [14:13] ֡�����ź���ʱ
                                                    [12:10] clear ack��ʱ
                                                    [9:7] ֡��ʼ�ź���ʱ
                                                    [6] ����single mode��������״̬��ģʽ
                                                    [5] 1'b1�� ֡��ʼ�źŸ���itf���ڵ�ctlѡ��
                                                     1'b0�� ֡��ʼ�źŸ���ģʽѡ��ctl_sof_sel)
                                                    [4:3] 2'b*1�� ctl_abt_if״̬
                                                     2'b10�� abt_ctl_if״̬
                                                     2'b00�� flush״̬
                                                    [2] 1'b1��auto modeʱ��������֡ͷ��ctl_mutex_mod
                                                     1'b0��auto modeʱ������֡ͷ��ctl_mutex_mod
                                                    [1] reserved��
                                                    [0] 1'b1��ÿ֡������clear
                                                    
                                                    ���ͳ����Ƽ�����
                                                    1��cpu���õ����ߣ�����Ĭ��ֵ
                                                    2��cmdlist������ͳһ����Ϊ��58A620
                                                    3�����ߣ�����Ĭ��ֵ */
        unsigned int  reserved : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_MCTL_MUTEX_CTL_DBG_UNION;
#endif
#define SOC_DSS_MCTL_MUTEX_CTL_DBG_ctl_dbg_START   (0)
#define SOC_DSS_MCTL_MUTEX_CTL_DBG_ctl_dbg_END     (23)






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

#endif /* end of soc_dss_mctl_mutex_interface.h */
