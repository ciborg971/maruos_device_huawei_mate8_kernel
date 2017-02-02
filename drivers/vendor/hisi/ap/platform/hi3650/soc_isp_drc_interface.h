/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_isp_drc_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:21:34
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_ISP_DRC.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_ISP_DRC_INTERFACE_H__
#define __SOC_ISP_DRC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) DRC
 ****************************************************************************/
/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ISP_DRC_DRC_CONFIG_UNION */
#define SOC_ISP_DRC_DRC_CONFIG_ADDR(base)             ((base) + (0x0000))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ISP_DRC_BLOCKNUM_UNION */
#define SOC_ISP_DRC_BLOCKNUM_ADDR(base)               ((base) + (0x0004))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ISP_DRC_FIRSTBLOCK_UNION */
#define SOC_ISP_DRC_FIRSTBLOCK_ADDR(base)             ((base) + (0x0008))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ISP_DRC_PLAINBLOCK_UNION */
#define SOC_ISP_DRC_PLAINBLOCK_ADDR(base)             ((base) + (0x000C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ISP_DRC_LASTBLOCK_UNION */
#define SOC_ISP_DRC_LASTBLOCK_ADDR(base)              ((base) + (0x0010))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ISP_DRC_XSTRIPESTART_END_UNION */
#define SOC_ISP_DRC_XSTRIPESTART_END_ADDR(base)       ((base) + (0x0014))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ISP_DRC_STRIPE_INFO_UNION */
#define SOC_ISP_DRC_STRIPE_INFO_ADDR(base)            ((base) + (0x0018))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ISP_DRC_FRAME_INFO_UNION */
#define SOC_ISP_DRC_FRAME_INFO_ADDR(base)             ((base) + (0x001C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ISP_DRC_BUFFWINH_UNION */
#define SOC_ISP_DRC_BUFFWINH_ADDR(base, Range3)       ((base) + (0x0020+0x4*(Range3)))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ISP_DRC_BUFFWINV_UNION */
#define SOC_ISP_DRC_BUFFWINV_ADDR(base, Range3)       ((base) + (0x002C+0x4*(Range3)))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ISP_DRC_BUFFWINSIZE_UNION */
#define SOC_ISP_DRC_BUFFWINSIZE_ADDR(base, Range6)    ((base) + (0x0038+0x4*(Range6)))

/* �Ĵ���˵����9 x 8 - shadowed
   λ����UNION�ṹ:  SOC_ISP_DRC_ALPHA_EVEN_0_UNION */
#define SOC_ISP_DRC_ALPHA_EVEN_0_ADDR(base, Range9)   ((base) + (0x0100+0x4*(Range9)))

/* �Ĵ���˵����9 x 8 - shadowed
   λ����UNION�ṹ:  SOC_ISP_DRC_ALPHA_EVEN_1_UNION */
#define SOC_ISP_DRC_ALPHA_EVEN_1_ADDR(base, Range9)   ((base) + (0x0140+0x4*(Range9)))

/* �Ĵ���˵����8 x 8 - shadowed
   λ����UNION�ṹ:  SOC_ISP_DRC_ALPHA_ODD_0_UNION */
#define SOC_ISP_DRC_ALPHA_ODD_0_ADDR(base, Range8)    ((base) + (0x0180+0x4*(Range8)))

/* �Ĵ���˵����8 x 8 - shadowed
   λ����UNION�ṹ:  SOC_ISP_DRC_ALPHA_ODD_1_UNION */
#define SOC_ISP_DRC_ALPHA_ODD_1_ADDR(base, Range8)    ((base) + (0x01C0+0x4*(Range8)))

/* �Ĵ���˵����9 x 8 - shadowed
   λ����UNION�ṹ:  SOC_ISP_DRC_RA_TAB_EVEN_0_UNION */
#define SOC_ISP_DRC_RA_TAB_EVEN_0_ADDR(base, Range9)  ((base) + (0x0200+0x4*(Range9)))

/* �Ĵ���˵����9 x 8 - shadowed
   λ����UNION�ṹ:  SOC_ISP_DRC_RA_TAB_EVEN_1_UNION */
#define SOC_ISP_DRC_RA_TAB_EVEN_1_ADDR(base, Range9)  ((base) + (0x0240+0x4*(Range9)))

/* �Ĵ���˵����8 x 16 - shadowed
   λ����UNION�ṹ:  SOC_ISP_DRC_RA_TAB_ODD_0_UNION */
#define SOC_ISP_DRC_RA_TAB_ODD_0_ADDR(base, Range8)   ((base) + (0x0280+0x4*(Range8)))

/* �Ĵ���˵����8 x 16 - shadowed
   λ����UNION�ṹ:  SOC_ISP_DRC_RA_TAB_ODD_1_UNION */
#define SOC_ISP_DRC_RA_TAB_ODD_1_ADDR(base, Range8)   ((base) + (0x02C0+0x4*(Range8)))

/* �Ĵ���˵����SRAM 33 x 20 - shadowed
   λ����UNION�ṹ:  SOC_ISP_DRC_RAT_TABHL_EVEN_0_UNION */
#define SOC_ISP_DRC_RAT_TABHL_EVEN_0_ADDR(base, Range33)  ((base) + (0x0300+0x4*(Range33)))

/* �Ĵ���˵����SRAM 33 x 20 - shadowed
   λ����UNION�ṹ:  SOC_ISP_DRC_RAT_TABHL_EVEN_1_UNION */
#define SOC_ISP_DRC_RAT_TABHL_EVEN_1_ADDR(base, Range33)  ((base) + (0x0400+0x4*(Range33)))

/* �Ĵ���˵����SRAM 32 x 20 - shadowed
   λ����UNION�ṹ:  SOC_ISP_DRC_RAT_TABHL_ODD_0_UNION */
#define SOC_ISP_DRC_RAT_TABHL_ODD_0_ADDR(base, Range32)  ((base) + (0x0500+0x4*(Range32)))

/* �Ĵ���˵����SRAM 32 x 20 - shadowed
   λ����UNION�ṹ:  SOC_ISP_DRC_RAT_TABHL_ODD_1_UNION */
#define SOC_ISP_DRC_RAT_TABHL_ODD_1_ADDR(base, Range32)  ((base) + (0x0600+0x4*(Range32)))

/* �Ĵ���˵����SRAM 256 x 10 - shadowed
   λ����UNION�ṹ:  SOC_ISP_DRC_AVERMATRIX_0_UNION */
#define SOC_ISP_DRC_AVERMATRIX_0_ADDR(base, Range128)  ((base) + (0x0700+0x4*(Range128)))

/* �Ĵ���˵����SRAM 256 x 10 - shadowed
   λ����UNION�ṹ:  SOC_ISP_DRC_AVERMATRIX_1_UNION */
#define SOC_ISP_DRC_AVERMATRIX_1_ADDR(base, Range128)  ((base) + (0x0900+0x4*(Range128)))





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
                     (1/1) DRC
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_ISP_DRC_DRC_CONFIG_UNION
 �ṹ˵��  : DRC_CONFIG �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass                  : 1;  /* bit[0]   : bypass:
                                                                  0: the module is active
                                                                  1: the module is bypassed */
        unsigned int  stat_enable             : 1;  /* bit[1]   : stat_enable:
                                                                  0: DRC Statistic feature is disable
                                                                  1: DRC Statistic feature is enable */
        unsigned int  alpha_table_active      : 1;  /* bit[2]   : alpha_table_active:
                                                                  0:the tablename_0 is used by the HW
                                                                  1:the tablename_1 is used by the HW */
        unsigned int  ra_tab_table_active     : 1;  /* bit[3]   : ra_tab_table_active:
                                                                  0:the tablename_0 is used by the HW
                                                                  1:the tablename_1 is used by the HW */
        unsigned int  rat_tabhl_table_active  : 1;  /* bit[4]   : rat_tabhl_table_active:
                                                                  0:the tablename_0 is used by the HW
                                                                  1:the tablename_1 is used by the HW */
        unsigned int  avermatrix_table_active : 1;  /* bit[5]   : avermatrix_table_active:
                                                                  0:the tablename_0 is used by the HW
                                                                  1:the tablename_1 is used by the HW */
        unsigned int  reserved                : 26; /* bit[6-31]:  */
    } reg;
} SOC_ISP_DRC_DRC_CONFIG_UNION;
#endif
#define SOC_ISP_DRC_DRC_CONFIG_bypass_START                   (0)
#define SOC_ISP_DRC_DRC_CONFIG_bypass_END                     (0)
#define SOC_ISP_DRC_DRC_CONFIG_stat_enable_START              (1)
#define SOC_ISP_DRC_DRC_CONFIG_stat_enable_END                (1)
#define SOC_ISP_DRC_DRC_CONFIG_alpha_table_active_START       (2)
#define SOC_ISP_DRC_DRC_CONFIG_alpha_table_active_END         (2)
#define SOC_ISP_DRC_DRC_CONFIG_ra_tab_table_active_START      (3)
#define SOC_ISP_DRC_DRC_CONFIG_ra_tab_table_active_END        (3)
#define SOC_ISP_DRC_DRC_CONFIG_rat_tabhl_table_active_START   (4)
#define SOC_ISP_DRC_DRC_CONFIG_rat_tabhl_table_active_END     (4)
#define SOC_ISP_DRC_DRC_CONFIG_avermatrix_table_active_START  (5)
#define SOC_ISP_DRC_DRC_CONFIG_avermatrix_table_active_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_ISP_DRC_BLOCKNUM_UNION
 �ṹ˵��  : BLOCKNUM �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  blocknumv        : 5;  /* bit[0-4]  : VerticalBlock number in frame */
        unsigned int  reserved_0       : 3;  /* bit[5-7]  :  */
        unsigned int  blocknumh        : 5;  /* bit[8-12] : Horizontal block number in frame */
        unsigned int  reserved_1       : 3;  /* bit[13-15]:  */
        unsigned int  blocknumh_stripe : 5;  /* bit[16-20]: Horizontal block number in stripe */
        unsigned int  reserved_2       : 11; /* bit[21-31]:  */
    } reg;
} SOC_ISP_DRC_BLOCKNUM_UNION;
#endif
#define SOC_ISP_DRC_BLOCKNUM_blocknumv_START         (0)
#define SOC_ISP_DRC_BLOCKNUM_blocknumv_END           (4)
#define SOC_ISP_DRC_BLOCKNUM_blocknumh_START         (8)
#define SOC_ISP_DRC_BLOCKNUM_blocknumh_END           (12)
#define SOC_ISP_DRC_BLOCKNUM_blocknumh_stripe_START  (16)
#define SOC_ISP_DRC_BLOCKNUM_blocknumh_stripe_END    (20)


/*****************************************************************************
 �ṹ��    : SOC_ISP_DRC_FIRSTBLOCK_UNION
 �ṹ˵��  : FIRSTBLOCK �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  firstblockoffh : 10; /* bit[0-9]  : The horizontal offset of the first pixel in current block in stripe */
        unsigned int  reserved_0     : 6;  /* bit[10-15]:  */
        unsigned int  firstblocknumh : 5;  /* bit[16-20]: Left block number of the first pixel in stripe */
        unsigned int  reserved_1     : 11; /* bit[21-31]:  */
    } reg;
} SOC_ISP_DRC_FIRSTBLOCK_UNION;
#endif
#define SOC_ISP_DRC_FIRSTBLOCK_firstblockoffh_START  (0)
#define SOC_ISP_DRC_FIRSTBLOCK_firstblockoffh_END    (9)
#define SOC_ISP_DRC_FIRSTBLOCK_firstblocknumh_START  (16)
#define SOC_ISP_DRC_FIRSTBLOCK_firstblocknumh_END    (20)


/*****************************************************************************
 �ṹ��    : SOC_ISP_DRC_PLAINBLOCK_UNION
 �ṹ˵��  : PLAINBLOCK �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  blockwinv : 10; /* bit[0-9]  : Plain block height in frame; width x height cannot exceed 0x20000 */
        unsigned int  reserved_0: 6;  /* bit[10-15]:  */
        unsigned int  blockwinh : 10; /* bit[16-25]: Plain block width in frame; width x height cannot exceed 0x20000 */
        unsigned int  reserved_1: 6;  /* bit[26-31]:  */
    } reg;
} SOC_ISP_DRC_PLAINBLOCK_UNION;
#endif
#define SOC_ISP_DRC_PLAINBLOCK_blockwinv_START  (0)
#define SOC_ISP_DRC_PLAINBLOCK_blockwinv_END    (9)
#define SOC_ISP_DRC_PLAINBLOCK_blockwinh_START  (16)
#define SOC_ISP_DRC_PLAINBLOCK_blockwinh_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_ISP_DRC_LASTBLOCK_UNION
 �ṹ˵��  : LASTBLOCK �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lastwinv        : 10; /* bit[0-9]  : Last block height in frame;width x height cannot exceed 0x20000 */
        unsigned int  lastwinh        : 10; /* bit[10-19]: Last block width in frame; width x height cannot exceed 0x20000 */
        unsigned int  lastwinh_stripe : 10; /* bit[20-29]: Last block width in stripe  */
        unsigned int  reserved        : 2;  /* bit[30-31]:  */
    } reg;
} SOC_ISP_DRC_LASTBLOCK_UNION;
#endif
#define SOC_ISP_DRC_LASTBLOCK_lastwinv_START         (0)
#define SOC_ISP_DRC_LASTBLOCK_lastwinv_END           (9)
#define SOC_ISP_DRC_LASTBLOCK_lastwinh_START         (10)
#define SOC_ISP_DRC_LASTBLOCK_lastwinh_END           (19)
#define SOC_ISP_DRC_LASTBLOCK_lastwinh_stripe_START  (20)
#define SOC_ISP_DRC_LASTBLOCK_lastwinh_stripe_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_ISP_DRC_XSTRIPESTART_END_UNION
 �ṹ˵��  : XSTRIPESTART_END �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  endpoint   : 13; /* bit[0-12] : endpoint of the stripe in the image coordinates */
        unsigned int  reserved_0 : 3;  /* bit[13-15]:  */
        unsigned int  startpoint : 13; /* bit[16-28]: Startpoint of the stripe in the image coordinates */
        unsigned int  reserved_1 : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_DRC_XSTRIPESTART_END_UNION;
#endif
#define SOC_ISP_DRC_XSTRIPESTART_END_endpoint_START    (0)
#define SOC_ISP_DRC_XSTRIPESTART_END_endpoint_END      (12)
#define SOC_ISP_DRC_XSTRIPESTART_END_startpoint_START  (16)
#define SOC_ISP_DRC_XSTRIPESTART_END_startpoint_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_DRC_STRIPE_INFO_UNION
 �ṹ˵��  : STRIPE_INFO �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  khright    : 7;  /* bit[0-6]  : width of the right overlap */
        unsigned int  reserved_0 : 1;  /* bit[7]    :  */
        unsigned int  khleft     : 7;  /* bit[8-14] : width of the left overlap */
        unsigned int  reserved_1 : 1;  /* bit[15]   :  */
        unsigned int  stripewinh : 13; /* bit[16-28]: width minus 1 of a stripe, the actual image width for ISP pipeline. */
        unsigned int  reserved_2 : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_DRC_STRIPE_INFO_UNION;
#endif
#define SOC_ISP_DRC_STRIPE_INFO_khright_START     (0)
#define SOC_ISP_DRC_STRIPE_INFO_khright_END       (6)
#define SOC_ISP_DRC_STRIPE_INFO_khleft_START      (8)
#define SOC_ISP_DRC_STRIPE_INFO_khleft_END        (14)
#define SOC_ISP_DRC_STRIPE_INFO_stripewinh_START  (16)
#define SOC_ISP_DRC_STRIPE_INFO_stripewinh_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_DRC_FRAME_INFO_UNION
 �ṹ˵��  : FRAME_INFO �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frame_height : 13; /* bit[0-12] : height of frame minus 1; cannot exceed 4992 pixels */
        unsigned int  reserved_0   : 3;  /* bit[13-15]:  */
        unsigned int  frame_width  : 13; /* bit[16-28]: width of frame minus 1; cannot exceed 6656 pixels */
        unsigned int  reserved_1   : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_DRC_FRAME_INFO_UNION;
#endif
#define SOC_ISP_DRC_FRAME_INFO_frame_height_START  (0)
#define SOC_ISP_DRC_FRAME_INFO_frame_height_END    (12)
#define SOC_ISP_DRC_FRAME_INFO_frame_width_START   (16)
#define SOC_ISP_DRC_FRAME_INFO_frame_width_END     (28)


/*****************************************************************************
 �ṹ��    : SOC_ISP_DRC_BUFFWINH_UNION
 �ṹ˵��  : BUFFWINH �Ĵ����ṹ���塣��ַƫ����:0x0020+0x4*(Range3)����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  buffwinh : 16; /* bit[0-15] : 3 different part width for biliresizer */
        unsigned int  reserved : 16; /* bit[16-31]:  */
    } reg;
} SOC_ISP_DRC_BUFFWINH_UNION;
#endif
#define SOC_ISP_DRC_BUFFWINH_buffwinh_START  (0)
#define SOC_ISP_DRC_BUFFWINH_buffwinh_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_ISP_DRC_BUFFWINV_UNION
 �ṹ˵��  : BUFFWINV �Ĵ����ṹ���塣��ַƫ����:0x002C+0x4*(Range3)����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  buffwinv : 16; /* bit[0-15] : 3 different part height for biliresizer */
        unsigned int  reserved : 16; /* bit[16-31]:  */
    } reg;
} SOC_ISP_DRC_BUFFWINV_UNION;
#endif
#define SOC_ISP_DRC_BUFFWINV_buffwinv_START  (0)
#define SOC_ISP_DRC_BUFFWINV_buffwinv_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_ISP_DRC_BUFFWINSIZE_UNION
 �ṹ˵��  : BUFFWINSIZE �Ĵ����ṹ���塣��ַƫ����:0x0038+0x4*(Range6)����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  buffwinsize : 26; /* bit[0-25] : 6 different block size in stripe */
        unsigned int  reserved    : 6;  /* bit[26-31]:  */
    } reg;
} SOC_ISP_DRC_BUFFWINSIZE_UNION;
#endif
#define SOC_ISP_DRC_BUFFWINSIZE_buffwinsize_START  (0)
#define SOC_ISP_DRC_BUFFWINSIZE_buffwinsize_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_ISP_DRC_ALPHA_EVEN_0_UNION
 �ṹ˵��  : ALPHA_EVEN_0 �Ĵ����ṹ���塣��ַƫ����:0x0100+0x4*(Range9)����ֵ:0x00000000�����:32
 �Ĵ���˵��: 9 x 8 - shadowed
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  alpha_even_0 : 8;  /* bit[0-7] :  */
        unsigned int  reserved     : 24; /* bit[8-31]:  */
    } reg;
} SOC_ISP_DRC_ALPHA_EVEN_0_UNION;
#endif
#define SOC_ISP_DRC_ALPHA_EVEN_0_alpha_even_0_START  (0)
#define SOC_ISP_DRC_ALPHA_EVEN_0_alpha_even_0_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_ISP_DRC_ALPHA_EVEN_1_UNION
 �ṹ˵��  : ALPHA_EVEN_1 �Ĵ����ṹ���塣��ַƫ����:0x0140+0x4*(Range9)����ֵ:0x00000000�����:32
 �Ĵ���˵��: 9 x 8 - shadowed
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  alpha_even_1 : 8;  /* bit[0-7] :  */
        unsigned int  reserved     : 24; /* bit[8-31]:  */
    } reg;
} SOC_ISP_DRC_ALPHA_EVEN_1_UNION;
#endif
#define SOC_ISP_DRC_ALPHA_EVEN_1_alpha_even_1_START  (0)
#define SOC_ISP_DRC_ALPHA_EVEN_1_alpha_even_1_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_ISP_DRC_ALPHA_ODD_0_UNION
 �ṹ˵��  : ALPHA_ODD_0 �Ĵ����ṹ���塣��ַƫ����:0x0180+0x4*(Range8)����ֵ:0x00000000�����:32
 �Ĵ���˵��: 8 x 8 - shadowed
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  alpha_odd_0 : 8;  /* bit[0-7] :  */
        unsigned int  reserved    : 24; /* bit[8-31]:  */
    } reg;
} SOC_ISP_DRC_ALPHA_ODD_0_UNION;
#endif
#define SOC_ISP_DRC_ALPHA_ODD_0_alpha_odd_0_START  (0)
#define SOC_ISP_DRC_ALPHA_ODD_0_alpha_odd_0_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_ISP_DRC_ALPHA_ODD_1_UNION
 �ṹ˵��  : ALPHA_ODD_1 �Ĵ����ṹ���塣��ַƫ����:0x01C0+0x4*(Range8)����ֵ:0x00000000�����:32
 �Ĵ���˵��: 8 x 8 - shadowed
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  alpha_odd_1 : 8;  /* bit[0-7] :  */
        unsigned int  reserved    : 24; /* bit[8-31]:  */
    } reg;
} SOC_ISP_DRC_ALPHA_ODD_1_UNION;
#endif
#define SOC_ISP_DRC_ALPHA_ODD_1_alpha_odd_1_START  (0)
#define SOC_ISP_DRC_ALPHA_ODD_1_alpha_odd_1_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_ISP_DRC_RA_TAB_EVEN_0_UNION
 �ṹ˵��  : RA_TAB_EVEN_0 �Ĵ����ṹ���塣��ַƫ����:0x0200+0x4*(Range9)����ֵ:0x00000000�����:32
 �Ĵ���˵��: 9 x 8 - shadowed
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ra_tab_even_0 : 8;  /* bit[0-7] :  */
        unsigned int  reserved      : 24; /* bit[8-31]:  */
    } reg;
} SOC_ISP_DRC_RA_TAB_EVEN_0_UNION;
#endif
#define SOC_ISP_DRC_RA_TAB_EVEN_0_ra_tab_even_0_START  (0)
#define SOC_ISP_DRC_RA_TAB_EVEN_0_ra_tab_even_0_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_ISP_DRC_RA_TAB_EVEN_1_UNION
 �ṹ˵��  : RA_TAB_EVEN_1 �Ĵ����ṹ���塣��ַƫ����:0x0240+0x4*(Range9)����ֵ:0x00000000�����:32
 �Ĵ���˵��: 9 x 8 - shadowed
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ra_tab_even_1 : 8;  /* bit[0-7] :  */
        unsigned int  reserved      : 24; /* bit[8-31]:  */
    } reg;
} SOC_ISP_DRC_RA_TAB_EVEN_1_UNION;
#endif
#define SOC_ISP_DRC_RA_TAB_EVEN_1_ra_tab_even_1_START  (0)
#define SOC_ISP_DRC_RA_TAB_EVEN_1_ra_tab_even_1_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_ISP_DRC_RA_TAB_ODD_0_UNION
 �ṹ˵��  : RA_TAB_ODD_0 �Ĵ����ṹ���塣��ַƫ����:0x0280+0x4*(Range8)����ֵ:0x00000000�����:32
 �Ĵ���˵��: 8 x 16 - shadowed
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ra_tab_odd_0 : 8;  /* bit[0-7] :  */
        unsigned int  reserved     : 24; /* bit[8-31]:  */
    } reg;
} SOC_ISP_DRC_RA_TAB_ODD_0_UNION;
#endif
#define SOC_ISP_DRC_RA_TAB_ODD_0_ra_tab_odd_0_START  (0)
#define SOC_ISP_DRC_RA_TAB_ODD_0_ra_tab_odd_0_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_ISP_DRC_RA_TAB_ODD_1_UNION
 �ṹ˵��  : RA_TAB_ODD_1 �Ĵ����ṹ���塣��ַƫ����:0x02C0+0x4*(Range8)����ֵ:0x00000000�����:32
 �Ĵ���˵��: 8 x 16 - shadowed
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ra_tab_odd_1 : 8;  /* bit[0-7] :  */
        unsigned int  reserved     : 24; /* bit[8-31]:  */
    } reg;
} SOC_ISP_DRC_RA_TAB_ODD_1_UNION;
#endif
#define SOC_ISP_DRC_RA_TAB_ODD_1_ra_tab_odd_1_START  (0)
#define SOC_ISP_DRC_RA_TAB_ODD_1_ra_tab_odd_1_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_ISP_DRC_RAT_TABHL_EVEN_0_UNION
 �ṹ˵��  : RAT_TABHL_EVEN_0 �Ĵ����ṹ���塣��ַƫ����:0x0300+0x4*(Range33)����ֵ:0x00000000�����:32
 �Ĵ���˵��: SRAM 33 x 20 - shadowed
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rat_tabhl_even_0 : 20; /* bit[0-19] :  */
        unsigned int  reserved         : 12; /* bit[20-31]:  */
    } reg;
} SOC_ISP_DRC_RAT_TABHL_EVEN_0_UNION;
#endif
#define SOC_ISP_DRC_RAT_TABHL_EVEN_0_rat_tabhl_even_0_START  (0)
#define SOC_ISP_DRC_RAT_TABHL_EVEN_0_rat_tabhl_even_0_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_ISP_DRC_RAT_TABHL_EVEN_1_UNION
 �ṹ˵��  : RAT_TABHL_EVEN_1 �Ĵ����ṹ���塣��ַƫ����:0x0400+0x4*(Range33)����ֵ:0x00000000�����:32
 �Ĵ���˵��: SRAM 33 x 20 - shadowed
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rat_tabhl_even_1 : 20; /* bit[0-19] :  */
        unsigned int  reserved         : 12; /* bit[20-31]:  */
    } reg;
} SOC_ISP_DRC_RAT_TABHL_EVEN_1_UNION;
#endif
#define SOC_ISP_DRC_RAT_TABHL_EVEN_1_rat_tabhl_even_1_START  (0)
#define SOC_ISP_DRC_RAT_TABHL_EVEN_1_rat_tabhl_even_1_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_ISP_DRC_RAT_TABHL_ODD_0_UNION
 �ṹ˵��  : RAT_TABHL_ODD_0 �Ĵ����ṹ���塣��ַƫ����:0x0500+0x4*(Range32)����ֵ:0x00000000�����:32
 �Ĵ���˵��: SRAM 32 x 20 - shadowed
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rat_tabhl_odd_0 : 20; /* bit[0-19] :  */
        unsigned int  reserved        : 12; /* bit[20-31]:  */
    } reg;
} SOC_ISP_DRC_RAT_TABHL_ODD_0_UNION;
#endif
#define SOC_ISP_DRC_RAT_TABHL_ODD_0_rat_tabhl_odd_0_START  (0)
#define SOC_ISP_DRC_RAT_TABHL_ODD_0_rat_tabhl_odd_0_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_ISP_DRC_RAT_TABHL_ODD_1_UNION
 �ṹ˵��  : RAT_TABHL_ODD_1 �Ĵ����ṹ���塣��ַƫ����:0x0600+0x4*(Range32)����ֵ:0x00000000�����:32
 �Ĵ���˵��: SRAM 32 x 20 - shadowed
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rat_tabhl_odd_1 : 20; /* bit[0-19] :  */
        unsigned int  reserved        : 12; /* bit[20-31]:  */
    } reg;
} SOC_ISP_DRC_RAT_TABHL_ODD_1_UNION;
#endif
#define SOC_ISP_DRC_RAT_TABHL_ODD_1_rat_tabhl_odd_1_START  (0)
#define SOC_ISP_DRC_RAT_TABHL_ODD_1_rat_tabhl_odd_1_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_ISP_DRC_AVERMATRIX_0_UNION
 �ṹ˵��  : AVERMATRIX_0 �Ĵ����ṹ���塣��ַƫ����:0x0700+0x4*(Range128)����ֵ:0x00000000�����:32
 �Ĵ���˵��: SRAM 256 x 10 - shadowed
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  avermatrix_odd_0  : 10; /* bit[0-9]  : odd part */
        unsigned int  reserved_0        : 6;  /* bit[10-15]:  */
        unsigned int  avermatrix_even_0 : 10; /* bit[16-25]: even part */
        unsigned int  reserved_1        : 6;  /* bit[26-31]:  */
    } reg;
} SOC_ISP_DRC_AVERMATRIX_0_UNION;
#endif
#define SOC_ISP_DRC_AVERMATRIX_0_avermatrix_odd_0_START   (0)
#define SOC_ISP_DRC_AVERMATRIX_0_avermatrix_odd_0_END     (9)
#define SOC_ISP_DRC_AVERMATRIX_0_avermatrix_even_0_START  (16)
#define SOC_ISP_DRC_AVERMATRIX_0_avermatrix_even_0_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_ISP_DRC_AVERMATRIX_1_UNION
 �ṹ˵��  : AVERMATRIX_1 �Ĵ����ṹ���塣��ַƫ����:0x0900+0x4*(Range128)����ֵ:0x00000000�����:32
 �Ĵ���˵��: SRAM 256 x 10 - shadowed
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  avermatrix_odd_1  : 10; /* bit[0-9]  : odd part */
        unsigned int  reserved_0        : 6;  /* bit[10-15]:  */
        unsigned int  avermatrix_even_1 : 10; /* bit[16-25]: even part */
        unsigned int  reserved_1        : 6;  /* bit[26-31]:  */
    } reg;
} SOC_ISP_DRC_AVERMATRIX_1_UNION;
#endif
#define SOC_ISP_DRC_AVERMATRIX_1_avermatrix_odd_1_START   (0)
#define SOC_ISP_DRC_AVERMATRIX_1_avermatrix_odd_1_END     (9)
#define SOC_ISP_DRC_AVERMATRIX_1_avermatrix_even_1_START  (16)
#define SOC_ISP_DRC_AVERMATRIX_1_avermatrix_even_1_END    (25)






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

#endif /* end of soc_isp_drc_interface.h */
