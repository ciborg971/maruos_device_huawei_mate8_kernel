/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_isp_statdis_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:22:06
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_ISP_STATDIS.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_ISP_STATDIS_INTERFACE_H__
#define __SOC_ISP_STATDIS_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) STATDIS
 ****************************************************************************/
/* �Ĵ���˵����Configuration register for DIS module
   λ����UNION�ṹ:  SOC_ISP_STATDIS_DIS_CONFIG_UNION */
#define SOC_ISP_STATDIS_DIS_CONFIG_ADDR(base)         ((base) + (0x0000))

/* �Ĵ���˵����FW flags the memory restore Done
   λ����UNION�ṹ:  SOC_ISP_STATDIS_RESTOREDONE_UNION */
#define SOC_ISP_STATDIS_RESTOREDONE_ADDR(base)        ((base) + (0x0004))

/* �Ĵ���˵����Window horizontal offset
   λ����UNION�ṹ:  SOC_ISP_STATDIS_DIS_H_OFFS_UNION */
#define SOC_ISP_STATDIS_DIS_H_OFFS_ADDR(base)         ((base) + (0x0008))

/* �Ĵ���˵����Window vertical offset
   λ����UNION�ṹ:  SOC_ISP_STATDIS_DIS_V_OFFS_UNION */
#define SOC_ISP_STATDIS_DIS_V_OFFS_ADDR(base)         ((base) + (0x000C))

/* �Ĵ���˵����Window horizontal size
   λ����UNION�ṹ:  SOC_ISP_STATDIS_DIS_H_SIZE_UNION */
#define SOC_ISP_STATDIS_DIS_H_SIZE_ADDR(base)         ((base) + (0x0010))

/* �Ĵ���˵����Windoz vertical size
   λ����UNION�ṹ:  SOC_ISP_STATDIS_DIS_V_SIZE_UNION */
#define SOC_ISP_STATDIS_DIS_V_SIZE_ADDR(base)         ((base) + (0x0014))

/* �Ĵ���˵����iteration 1 horizontal segmnt
   λ����UNION�ṹ:  SOC_ISP_STATDIS_DIS_H_SEGMENTS_UNION */
#define SOC_ISP_STATDIS_DIS_H_SEGMENTS_ADDR(base)     ((base) + (0x0018))

/* �Ĵ���˵����iteration 1 vertical segment
   λ����UNION�ṹ:  SOC_ISP_STATDIS_DIS_V_SEGMENTS_UNION */
#define SOC_ISP_STATDIS_DIS_V_SEGMENTS_ADDR(base)     ((base) + (0x001C))

/* �Ĵ���˵����estimated horizontal displacement
   λ����UNION�ṹ:  SOC_ISP_STATDIS_DIS_H_DELTA_0_UNION */
#define SOC_ISP_STATDIS_DIS_H_DELTA_0_ADDR(base)      ((base) + (0x0020))

/* �Ĵ���˵����estimated vertical displacement
   λ����UNION�ṹ:  SOC_ISP_STATDIS_DIS_V_DELTA_0_UNION */
#define SOC_ISP_STATDIS_DIS_V_DELTA_0_ADDR(base)      ((base) + (0x0024))

/* �Ĵ���˵����estimated horizontal displacement
   λ����UNION�ṹ:  SOC_ISP_STATDIS_DIS_H_DELTA_1_UNION */
#define SOC_ISP_STATDIS_DIS_H_DELTA_1_ADDR(base)      ((base) + (0x0028))

/* �Ĵ���˵����estimated vertical displacement
   λ����UNION�ṹ:  SOC_ISP_STATDIS_DIS_V_DELTA_1_UNION */
#define SOC_ISP_STATDIS_DIS_V_DELTA_1_ADDR(base)      ((base) + (0x002C))

/* �Ĵ���˵����estimated horizontal displacement
   λ����UNION�ṹ:  SOC_ISP_STATDIS_DIS_H_DELTA_2_UNION */
#define SOC_ISP_STATDIS_DIS_H_DELTA_2_ADDR(base)      ((base) + (0x0030))

/* �Ĵ���˵����estimated vertical displacement
   λ����UNION�ṹ:  SOC_ISP_STATDIS_DIS_V_DELTA_2_UNION */
#define SOC_ISP_STATDIS_DIS_V_DELTA_2_ADDR(base)      ((base) + (0x0034))

/* �Ĵ���˵����estimated horizontal displacement
   λ����UNION�ṹ:  SOC_ISP_STATDIS_DIS_H_DELTA_3_UNION */
#define SOC_ISP_STATDIS_DIS_H_DELTA_3_ADDR(base)      ((base) + (0x0038))

/* �Ĵ���˵����estimated vertical displacement
   λ����UNION�ṹ:  SOC_ISP_STATDIS_DIS_V_DELTA_3_UNION */
#define SOC_ISP_STATDIS_DIS_V_DELTA_3_ADDR(base)      ((base) + (0x003C))

/* �Ĵ���˵����X projection of current frame
   λ����UNION�ṹ:  SOC_ISP_STATDIS_SRAM2_UNION */
#define SOC_ISP_STATDIS_SRAM2_ADDR(base, Range2112)   ((base) + (0x1000+0x4*(Range2112)))

/* �Ĵ���˵����Y projection of current frame
   λ����UNION�ṹ:  SOC_ISP_STATDIS_SRAM4_UNION */
#define SOC_ISP_STATDIS_SRAM4_ADDR(base, Range2496)   ((base) + (0x4000+0x4*(Range2496)))





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
                     (1/1) STATDIS
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_ISP_STATDIS_DIS_CONFIG_UNION
 �ṹ˵��  : DIS_CONFIG �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: Configuration register for DIS module
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enable   : 1;  /* bit[0-0] : 0-disable measure,1-enable measure */
        unsigned int  irq_en   : 1;  /* bit[1-1] : 0-disable irq, 1- enable irq */
        unsigned int  nb_zone  : 1;  /* bit[2-2] : 0-work on 2 zones, 1-work on 4 zones */
        unsigned int  scm      : 1;  /* bit[3-3] : 0 - normal mode, 1 - save memory content after 3AStat done. */
        unsigned int  reserved : 28; /* bit[4-31]:  */
    } reg;
} SOC_ISP_STATDIS_DIS_CONFIG_UNION;
#endif
#define SOC_ISP_STATDIS_DIS_CONFIG_enable_START    (0)
#define SOC_ISP_STATDIS_DIS_CONFIG_enable_END      (0)
#define SOC_ISP_STATDIS_DIS_CONFIG_irq_en_START    (1)
#define SOC_ISP_STATDIS_DIS_CONFIG_irq_en_END      (1)
#define SOC_ISP_STATDIS_DIS_CONFIG_nb_zone_START   (2)
#define SOC_ISP_STATDIS_DIS_CONFIG_nb_zone_END     (2)
#define SOC_ISP_STATDIS_DIS_CONFIG_scm_START       (3)
#define SOC_ISP_STATDIS_DIS_CONFIG_scm_END         (3)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STATDIS_RESTOREDONE_UNION
 �ṹ˵��  : RESTOREDONE �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: FW flags the memory restore Done
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  restoredone : 1;  /* bit[0-0] : 1- after memory is fully restored */
        unsigned int  reserved    : 31; /* bit[1-31]:  */
    } reg;
} SOC_ISP_STATDIS_RESTOREDONE_UNION;
#endif
#define SOC_ISP_STATDIS_RESTOREDONE_restoredone_START  (0)
#define SOC_ISP_STATDIS_RESTOREDONE_restoredone_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STATDIS_DIS_H_OFFS_UNION
 �ṹ˵��  : DIS_H_OFFS �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: Window horizontal offset
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  h_offs   : 12; /* bit[0-11] : Window horizontal offset in Y domain - range 0..2048 */
        unsigned int  reserved : 20; /* bit[12-31]:  */
    } reg;
} SOC_ISP_STATDIS_DIS_H_OFFS_UNION;
#endif
#define SOC_ISP_STATDIS_DIS_H_OFFS_h_offs_START    (0)
#define SOC_ISP_STATDIS_DIS_H_OFFS_h_offs_END      (11)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STATDIS_DIS_V_OFFS_UNION
 �ṹ˵��  : DIS_V_OFFS �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Window vertical offset
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  v_offs   : 12; /* bit[0-11] : Window vertical offset in Y domain - ramge 0..2368 */
        unsigned int  reserved : 20; /* bit[12-31]:  */
    } reg;
} SOC_ISP_STATDIS_DIS_V_OFFS_UNION;
#endif
#define SOC_ISP_STATDIS_DIS_V_OFFS_v_offs_START    (0)
#define SOC_ISP_STATDIS_DIS_V_OFFS_v_offs_END      (11)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STATDIS_DIS_H_SIZE_UNION
 �ṹ˵��  : DIS_H_SIZE �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: Window horizontal size
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  h_size   : 12; /* bit[0-11] : Window horizontal size in Y domain - range: 64..2112 and must be even */
        unsigned int  reserved : 20; /* bit[12-31]:  */
    } reg;
} SOC_ISP_STATDIS_DIS_H_SIZE_UNION;
#endif
#define SOC_ISP_STATDIS_DIS_H_SIZE_h_size_START    (0)
#define SOC_ISP_STATDIS_DIS_H_SIZE_h_size_END      (11)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STATDIS_DIS_V_SIZE_UNION
 �ṹ˵��  : DIS_V_SIZE �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: Windoz vertical size
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  v_size   : 11; /* bit[0-10] : Window vertical size in Y domain - range: 64..1248 and must be even */
        unsigned int  reserved : 21; /* bit[11-31]:  */
    } reg;
} SOC_ISP_STATDIS_DIS_V_SIZE_UNION;
#endif
#define SOC_ISP_STATDIS_DIS_V_SIZE_v_size_START    (0)
#define SOC_ISP_STATDIS_DIS_V_SIZE_v_size_END      (10)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STATDIS_DIS_H_SEGMENTS_UNION
 �ṹ˵��  : DIS_H_SEGMENTS �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: iteration 1 horizontal segmnt
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  h_segments : 7;  /* bit[0-6] : iteration 1 horizontal segment - range 1..127 */
        unsigned int  reserved   : 25; /* bit[7-31]:  */
    } reg;
} SOC_ISP_STATDIS_DIS_H_SEGMENTS_UNION;
#endif
#define SOC_ISP_STATDIS_DIS_H_SEGMENTS_h_segments_START  (0)
#define SOC_ISP_STATDIS_DIS_H_SEGMENTS_h_segments_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STATDIS_DIS_V_SEGMENTS_UNION
 �ṹ˵��  : DIS_V_SEGMENTS �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000000�����:32
 �Ĵ���˵��: iteration 1 vertical segment
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  v_segments : 7;  /* bit[0-6] : iteration 1 vertical segment - range 1..75 */
        unsigned int  reserved   : 25; /* bit[7-31]:  */
    } reg;
} SOC_ISP_STATDIS_DIS_V_SEGMENTS_UNION;
#endif
#define SOC_ISP_STATDIS_DIS_V_SEGMENTS_v_segments_START  (0)
#define SOC_ISP_STATDIS_DIS_V_SEGMENTS_v_segments_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STATDIS_DIS_H_DELTA_0_UNION
 �ṹ˵��  : DIS_H_DELTA_0 �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: estimated horizontal displacement
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  delta_h_0 : 12; /* bit[0-11] : Zone 0 estimated horizontal displacement in Y domain */
        unsigned int  reserved  : 20; /* bit[12-31]:  */
    } reg;
} SOC_ISP_STATDIS_DIS_H_DELTA_0_UNION;
#endif
#define SOC_ISP_STATDIS_DIS_H_DELTA_0_delta_h_0_START  (0)
#define SOC_ISP_STATDIS_DIS_H_DELTA_0_delta_h_0_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STATDIS_DIS_V_DELTA_0_UNION
 �ṹ˵��  : DIS_V_DELTA_0 �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x00000000�����:32
 �Ĵ���˵��: estimated vertical displacement
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  delta_v_0 : 12; /* bit[0-11] : Zone 0 estimated vertical displacement in Y domain */
        unsigned int  reserved  : 20; /* bit[12-31]:  */
    } reg;
} SOC_ISP_STATDIS_DIS_V_DELTA_0_UNION;
#endif
#define SOC_ISP_STATDIS_DIS_V_DELTA_0_delta_v_0_START  (0)
#define SOC_ISP_STATDIS_DIS_V_DELTA_0_delta_v_0_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STATDIS_DIS_H_DELTA_1_UNION
 �ṹ˵��  : DIS_H_DELTA_1 �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x00000000�����:32
 �Ĵ���˵��: estimated horizontal displacement
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  delta_h_1 : 12; /* bit[0-11] : Zone 1 estimated horizontal displacement in Y domain */
        unsigned int  reserved  : 20; /* bit[12-31]:  */
    } reg;
} SOC_ISP_STATDIS_DIS_H_DELTA_1_UNION;
#endif
#define SOC_ISP_STATDIS_DIS_H_DELTA_1_delta_h_1_START  (0)
#define SOC_ISP_STATDIS_DIS_H_DELTA_1_delta_h_1_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STATDIS_DIS_V_DELTA_1_UNION
 �ṹ˵��  : DIS_V_DELTA_1 �Ĵ����ṹ���塣��ַƫ����:0x002C����ֵ:0x00000000�����:32
 �Ĵ���˵��: estimated vertical displacement
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  delta_v_1 : 12; /* bit[0-11] : Zone 1 estimated vertical displacement in Y domain */
        unsigned int  reserved  : 20; /* bit[12-31]:  */
    } reg;
} SOC_ISP_STATDIS_DIS_V_DELTA_1_UNION;
#endif
#define SOC_ISP_STATDIS_DIS_V_DELTA_1_delta_v_1_START  (0)
#define SOC_ISP_STATDIS_DIS_V_DELTA_1_delta_v_1_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STATDIS_DIS_H_DELTA_2_UNION
 �ṹ˵��  : DIS_H_DELTA_2 �Ĵ����ṹ���塣��ַƫ����:0x0030����ֵ:0x00000000�����:32
 �Ĵ���˵��: estimated horizontal displacement
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  delta_h_2 : 12; /* bit[0-11] : Zone 2 estimated horizontal displacement in Y domain */
        unsigned int  reserved  : 20; /* bit[12-31]:  */
    } reg;
} SOC_ISP_STATDIS_DIS_H_DELTA_2_UNION;
#endif
#define SOC_ISP_STATDIS_DIS_H_DELTA_2_delta_h_2_START  (0)
#define SOC_ISP_STATDIS_DIS_H_DELTA_2_delta_h_2_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STATDIS_DIS_V_DELTA_2_UNION
 �ṹ˵��  : DIS_V_DELTA_2 �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x00000000�����:32
 �Ĵ���˵��: estimated vertical displacement
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  delta_v_2 : 12; /* bit[0-11] : Zone 2 estimated vertical displacement in Y domain */
        unsigned int  reserved  : 20; /* bit[12-31]:  */
    } reg;
} SOC_ISP_STATDIS_DIS_V_DELTA_2_UNION;
#endif
#define SOC_ISP_STATDIS_DIS_V_DELTA_2_delta_v_2_START  (0)
#define SOC_ISP_STATDIS_DIS_V_DELTA_2_delta_v_2_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STATDIS_DIS_H_DELTA_3_UNION
 �ṹ˵��  : DIS_H_DELTA_3 �Ĵ����ṹ���塣��ַƫ����:0x0038����ֵ:0x00000000�����:32
 �Ĵ���˵��: estimated horizontal displacement
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  delta_h_3 : 12; /* bit[0-11] : Zone 3 estimated horizontal displacement in Y domain */
        unsigned int  reserved  : 20; /* bit[12-31]:  */
    } reg;
} SOC_ISP_STATDIS_DIS_H_DELTA_3_UNION;
#endif
#define SOC_ISP_STATDIS_DIS_H_DELTA_3_delta_h_3_START  (0)
#define SOC_ISP_STATDIS_DIS_H_DELTA_3_delta_h_3_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STATDIS_DIS_V_DELTA_3_UNION
 �ṹ˵��  : DIS_V_DELTA_3 �Ĵ����ṹ���塣��ַƫ����:0x003C����ֵ:0x00000000�����:32
 �Ĵ���˵��: estimated vertical displacement
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  delta_v_3 : 12; /* bit[0-11] : Zone 3 estimated vertical displacement in Y domain */
        unsigned int  reserved  : 20; /* bit[12-31]:  */
    } reg;
} SOC_ISP_STATDIS_DIS_V_DELTA_3_UNION;
#endif
#define SOC_ISP_STATDIS_DIS_V_DELTA_3_delta_v_3_START  (0)
#define SOC_ISP_STATDIS_DIS_V_DELTA_3_delta_v_3_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STATDIS_SRAM2_UNION
 �ṹ˵��  : SRAM2 �Ĵ����ṹ���塣��ַƫ����:0x1000+0x4*(Range2112)����ֵ:0x00000000�����:32
 �Ĵ���˵��: X projection of current frame
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  x_proj : 32; /* bit[0-31]: X projection */
    } reg;
} SOC_ISP_STATDIS_SRAM2_UNION;
#endif
#define SOC_ISP_STATDIS_SRAM2_x_proj_START  (0)
#define SOC_ISP_STATDIS_SRAM2_x_proj_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_STATDIS_SRAM4_UNION
 �ṹ˵��  : SRAM4 �Ĵ����ṹ���塣��ַƫ����:0x4000+0x4*(Range2496)����ֵ:0x00000000�����:32
 �Ĵ���˵��: Y projection of current frame
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  y_proj : 32; /* bit[0-31]: Y projection */
    } reg;
} SOC_ISP_STATDIS_SRAM4_UNION;
#endif
#define SOC_ISP_STATDIS_SRAM4_y_proj_START  (0)
#define SOC_ISP_STATDIS_SRAM4_y_proj_END    (31)






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

#endif /* end of soc_isp_statdis_interface.h */
