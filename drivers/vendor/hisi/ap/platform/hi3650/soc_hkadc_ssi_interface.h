/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_hkadc_ssi_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-04-08 11:46:09
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��4��8��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_HKADC_SSI.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_HKADC_SSI_INTERFACE_H__
#define __SOC_HKADC_SSI_INTERFACE_H__

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
/* �Ĵ���˵����HKADC�������á�
   λ����UNION�ṹ:  SOC_HKADC_SSI_HKADC_DSP_START_UNION */
#define SOC_HKADC_SSI_HKADC_DSP_START_ADDR(base)      ((base) + (0x0000))

/* �Ĵ���˵����HKADC�������á�
   λ����UNION�ṹ:  SOC_HKADC_SSI_HKADC_DSP_CFG_UNION */
#define SOC_HKADC_SSI_HKADC_DSP_CFG_ADDR(base)        ((base) + (0x0004))

/* �Ĵ���˵����HKADC�������á�
   λ����UNION�ṹ:  SOC_HKADC_SSI_HKADC_WR_NUM_UNION */
#define SOC_HKADC_SSI_HKADC_WR_NUM_ADDR(base)         ((base) + (0x0008))

/* �Ĵ���˵����HKADC�������á�
   λ����UNION�ṹ:  SOC_HKADC_SSI_HKADC_DSP_WAIT_TIME_UNION */
#define SOC_HKADC_SSI_HKADC_DSP_WAIT_TIME_ADDR(base)  ((base) + (0x000C))

/* �Ĵ���˵����HKADC�������á�
   λ����UNION�ṹ:  SOC_HKADC_SSI_HKADC_TIMEOUT_ERR_CLR_UNION */
#define SOC_HKADC_SSI_HKADC_TIMEOUT_ERR_CLR_ADDR(base) ((base) + (0x0010))

/* �Ĵ���˵����HKADC��ʱ�ϱ���
   λ����UNION�ṹ:  SOC_HKADC_SSI_HKADC_TIMEOUT_ERR_UNION */
#define SOC_HKADC_SSI_HKADC_TIMEOUT_ERR_ADDR(base)    ((base) + (0x0018))

/* �Ĵ���˵����HKADC��������ϱ���
   λ����UNION�ṹ:  SOC_HKADC_SSI_HKADC_DSP_START_CLR_UNION */
#define SOC_HKADC_SSI_HKADC_DSP_START_CLR_ADDR(base)  ((base) + (0x001C))

/* �Ĵ���˵����HKADC�������á�
   λ����UNION�ṹ:  SOC_HKADC_SSI_HKADC_WR01_DATA_UNION */
#define SOC_HKADC_SSI_HKADC_WR01_DATA_ADDR(base)      ((base) + (0x0020))

/* �Ĵ���˵����HKADC�������á�
   λ����UNION�ṹ:  SOC_HKADC_SSI_HKADC_WR23_DATA_UNION */
#define SOC_HKADC_SSI_HKADC_WR23_DATA_ADDR(base)      ((base) + (0x0024))

/* �Ĵ���˵����HKADC�������á�
   λ����UNION�ṹ:  SOC_HKADC_SSI_HKADC_WR45_DATA_UNION */
#define SOC_HKADC_SSI_HKADC_WR45_DATA_ADDR(base)      ((base) + (0x0028))

/* �Ĵ���˵����HKADC�������á�
   λ����UNION�ṹ:  SOC_HKADC_SSI_HKADC_WR67_DATA_UNION */
#define SOC_HKADC_SSI_HKADC_WR67_DATA_ADDR(base)      ((base) + (0x002C))

/* �Ĵ���˵����HKADC�ӳ����á�
   λ����UNION�ṹ:  SOC_HKADC_SSI_HKADC_DELAY01_UNION */
#define SOC_HKADC_SSI_HKADC_DELAY01_ADDR(base)        ((base) + (0x0030))

/* �Ĵ���˵����HKADC�ӳ����á�
   λ����UNION�ṹ:  SOC_HKADC_SSI_HKADC_DELAY23_UNION */
#define SOC_HKADC_SSI_HKADC_DELAY23_ADDR(base)        ((base) + (0x0034))

/* �Ĵ���˵����HKADC�ӳ����á�
   λ����UNION�ṹ:  SOC_HKADC_SSI_HKADC_DELAY45_UNION */
#define SOC_HKADC_SSI_HKADC_DELAY45_ADDR(base)        ((base) + (0x0038))

/* �Ĵ���˵����HKADC�ӳ����á�
   λ����UNION�ṹ:  SOC_HKADC_SSI_HKADC_DELAY6_UNION */
#define SOC_HKADC_SSI_HKADC_DELAY6_ADDR(base)         ((base) + (0x003C))

/* �Ĵ���˵����HKADC���ݻض���
   λ����UNION�ṹ:  SOC_HKADC_SSI_HKADC_DSP_RD0_DATA_UNION */
#define SOC_HKADC_SSI_HKADC_DSP_RD0_DATA_ADDR(base)   ((base) + (0x0040))

/* �Ĵ���˵����HKADC���ݻض���
   λ����UNION�ṹ:  SOC_HKADC_SSI_HKADC_DSP_RD1_DATA_UNION */
#define SOC_HKADC_SSI_HKADC_DSP_RD1_DATA_ADDR(base)   ((base) + (0x0044))

/* �Ĵ���˵����HKADC���ݻض���
   λ����UNION�ṹ:  SOC_HKADC_SSI_HKADC_DSP_RD2_DATA_UNION */
#define SOC_HKADC_SSI_HKADC_DSP_RD2_DATA_ADDR(base)   ((base) + (0x0048))

/* �Ĵ���˵����HKADC���ݻض���
   λ����UNION�ṹ:  SOC_HKADC_SSI_HKADC_DSP_RD3_DATA_UNION */
#define SOC_HKADC_SSI_HKADC_DSP_RD3_DATA_ADDR(base)   ((base) + (0x004C))

/* �Ĵ���˵����HKADC���ݻض���
   λ����UNION�ṹ:  SOC_HKADC_SSI_HKADC_DSP_RD4_DATA_UNION */
#define SOC_HKADC_SSI_HKADC_DSP_RD4_DATA_ADDR(base)   ((base) + (0x0050))

/* �Ĵ���˵����HKADC���ݻض���
   λ����UNION�ṹ:  SOC_HKADC_SSI_HKADC_DSP_RD5_DATA_UNION */
#define SOC_HKADC_SSI_HKADC_DSP_RD5_DATA_ADDR(base)   ((base) + (0x0054))

/* �Ĵ���˵����HKADC���ݻض���
   λ����UNION�ṹ:  SOC_HKADC_SSI_HKADC_DSP_RD6_DATA_UNION */
#define SOC_HKADC_SSI_HKADC_DSP_RD6_DATA_ADDR(base)   ((base) + (0x0058))

/* �Ĵ���˵����HKADC���ݻض���
   λ����UNION�ṹ:  SOC_HKADC_SSI_HKADC_DSP_RD7_DATA_UNION */
#define SOC_HKADC_SSI_HKADC_DSP_RD7_DATA_ADDR(base)   ((base) + (0x005C))

/* �Ĵ���˵����HKADC�������ʱ�����á�
   λ����UNION�ṹ:  SOC_HKADC_SSI_HKADC_OP_INTERVAL_UNION */
#define SOC_HKADC_SSI_HKADC_OP_INTERVAL_ADDR(base)    ((base) + (0x0060))

/* �Ĵ���˵����HKADC�������ʱ�书��ʹ�ܡ�
   λ����UNION�ṹ:  SOC_HKADC_SSI_HKADC_OP_INTERVAL_BYPASS_UNION */
#define SOC_HKADC_SSI_HKADC_OP_INTERVAL_BYPASS_ADDR(base) ((base) + (0x0064))

/* �Ĵ���˵����HKADCͨ��ʹ�ܡ�
   λ����UNION�ṹ:  SOC_HKADC_SSI_HKADC_CHANNEL_EN_UNION */
#define SOC_HKADC_SSI_HKADC_CHANNEL_EN_ADDR(base)     ((base) + (0x0068))

/* �Ĵ���˵����HKADC �������ݡ�
   λ����UNION�ṹ:  SOC_HKADC_SSI_HKADC_DBG_INFO_UNION */
#define SOC_HKADC_SSI_HKADC_DBG_INFO_ADDR(base)       ((base) + (0x00D0))

/* �Ĵ���˵����HKADC �������ԭʼ�жϡ�
   λ����UNION�ṹ:  SOC_HKADC_SSI_HKADC_FINSH_RAW_INT_UNION */
#define SOC_HKADC_SSI_HKADC_FINSH_RAW_INT_ADDR(base)  ((base) + (0x0100))

/* �Ĵ���˵����HKADC����������κ��жϡ�
   λ����UNION�ṹ:  SOC_HKADC_SSI_HKADC_FINSH_MSK_INT_UNION */
#define SOC_HKADC_SSI_HKADC_FINSH_MSK_INT_ADDR(base)  ((base) + (0x0104))

/* �Ĵ���˵����HKADC��������ж������
   λ����UNION�ṹ:  SOC_HKADC_SSI_HKADC_FINSH_INT_CLR_UNION */
#define SOC_HKADC_SSI_HKADC_FINSH_INT_CLR_ADDR(base)  ((base) + (0x0108))

/* �Ĵ���˵����HKADC��������ж����Ρ�
   λ����UNION�ṹ:  SOC_HKADC_SSI_HKADC_FINSH_INT_MSK_UNION */
#define SOC_HKADC_SSI_HKADC_FINSH_INT_MSK_ADDR(base)  ((base) + (0x010C))





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
 �ṹ��    : SOC_HKADC_SSI_HKADC_DSP_START_UNION
 �ṹ˵��  : HKADC_DSP_START �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: HKADC�������á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_start : 1;  /* bit[0]   : �������HKADC�����źš�
                                                    �߼������㡣 */
        unsigned int  reserved  : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_START_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_START_dsp_start_START  (0)
#define SOC_HKADC_SSI_HKADC_DSP_START_dsp_start_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_HKADC_SSI_HKADC_DSP_CFG_UNION
 �ṹ˵��  : HKADC_DSP_CFG �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: HKADC�������á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_cfg  : 20; /* bit[0-19] : master check ��ͬ��λʱ���SSI IP��ʱ�ȴ����� */
        unsigned int  reserved : 12; /* bit[20-31]: reserved */
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_CFG_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_CFG_dsp_cfg_START   (0)
#define SOC_HKADC_SSI_HKADC_DSP_CFG_dsp_cfg_END     (19)


/*****************************************************************************
 �ṹ��    : SOC_HKADC_SSI_HKADC_WR_NUM_UNION
 �ṹ˵��  : HKADC_WR_NUM �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: HKADC�������á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hkadc_wr_num : 3;  /* bit[0-2] : ���HKADC�Ĵ������� */
        unsigned int  reserved     : 29; /* bit[3-31]: reserved */
    } reg;
} SOC_HKADC_SSI_HKADC_WR_NUM_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_WR_NUM_hkadc_wr_num_START  (0)
#define SOC_HKADC_SSI_HKADC_WR_NUM_hkadc_wr_num_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_HKADC_SSI_HKADC_DSP_WAIT_TIME_UNION
 �ṹ˵��  : HKADC_DSP_WAIT_TIME �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: HKADC�������á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_wait_time : 32; /* bit[0-31]: ���HKADC����ʱʱ�䳤�� */
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_WAIT_TIME_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_WAIT_TIME_dsp_wait_time_START  (0)
#define SOC_HKADC_SSI_HKADC_DSP_WAIT_TIME_dsp_wait_time_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HKADC_SSI_HKADC_TIMEOUT_ERR_CLR_UNION
 �ṹ˵��  : HKADC_TIMEOUT_ERR_CLR �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: HKADC�������á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  time_out_err_clr : 1;  /* bit[0]   : ��ʱ��� */
        unsigned int  reserved         : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_HKADC_SSI_HKADC_TIMEOUT_ERR_CLR_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_TIMEOUT_ERR_CLR_time_out_err_clr_START  (0)
#define SOC_HKADC_SSI_HKADC_TIMEOUT_ERR_CLR_time_out_err_clr_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_HKADC_SSI_HKADC_TIMEOUT_ERR_UNION
 �ṹ˵��  : HKADC_TIMEOUT_ERR �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: HKADC��ʱ�ϱ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timeout_err : 1;  /* bit[0]   : ���HKADC����ʱ״ָ̬ʾ */
        unsigned int  reserved    : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_HKADC_SSI_HKADC_TIMEOUT_ERR_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_TIMEOUT_ERR_timeout_err_START  (0)
#define SOC_HKADC_SSI_HKADC_TIMEOUT_ERR_timeout_err_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_HKADC_SSI_HKADC_DSP_START_CLR_UNION
 �ṹ˵��  : HKADC_DSP_START_CLR �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000000�����:32
 �Ĵ���˵��: HKADC��������ϱ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_start_clr : 1;  /* bit[0]   : HKADC��д���״̬�ź� */
        unsigned int  reserved      : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_START_CLR_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_START_CLR_dsp_start_clr_START  (0)
#define SOC_HKADC_SSI_HKADC_DSP_START_CLR_dsp_start_clr_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_HKADC_SSI_HKADC_WR01_DATA_UNION
 �ṹ˵��  : HKADC_WR01_DATA �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: HKADC�������á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_wr0_cfg : 16; /* bit[0-15] : HKADC�Ĵ�����д���ã�
                                                       15����дָʾ��0��д��1����
                                                       14-8����д��ַ
                                                       7-0����д���� */
        unsigned int  dsp_wr1_cfg : 16; /* bit[16-31]: HKADC�Ĵ�����д���ã�
                                                       31����дָʾ��0��д��1����
                                                       30-24����д��ַ
                                                       23-16����д���� */
    } reg;
} SOC_HKADC_SSI_HKADC_WR01_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_WR01_DATA_dsp_wr0_cfg_START  (0)
#define SOC_HKADC_SSI_HKADC_WR01_DATA_dsp_wr0_cfg_END    (15)
#define SOC_HKADC_SSI_HKADC_WR01_DATA_dsp_wr1_cfg_START  (16)
#define SOC_HKADC_SSI_HKADC_WR01_DATA_dsp_wr1_cfg_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HKADC_SSI_HKADC_WR23_DATA_UNION
 �ṹ˵��  : HKADC_WR23_DATA �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x00000000�����:32
 �Ĵ���˵��: HKADC�������á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_wr2_cfg : 16; /* bit[0-15] : HKADC�Ĵ�����д���ã�
                                                       15����дָʾ��0��д��1����
                                                       14-8����д��ַ
                                                       7-0����д���� */
        unsigned int  dsp_wr3_cfg : 16; /* bit[16-31]: HKADC�Ĵ�����д���ã�
                                                       31����дָʾ��0��д��1����
                                                       30-24����д��ַ
                                                       23-16����д���� */
    } reg;
} SOC_HKADC_SSI_HKADC_WR23_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_WR23_DATA_dsp_wr2_cfg_START  (0)
#define SOC_HKADC_SSI_HKADC_WR23_DATA_dsp_wr2_cfg_END    (15)
#define SOC_HKADC_SSI_HKADC_WR23_DATA_dsp_wr3_cfg_START  (16)
#define SOC_HKADC_SSI_HKADC_WR23_DATA_dsp_wr3_cfg_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HKADC_SSI_HKADC_WR45_DATA_UNION
 �ṹ˵��  : HKADC_WR45_DATA �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x00000000�����:32
 �Ĵ���˵��: HKADC�������á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_wr4_cfg : 16; /* bit[0-15] : HKADC�Ĵ�����д���ã�
                                                       15����дָʾ��0��д��1����
                                                       14-8����д��ַ
                                                       7-0����д���� */
        unsigned int  dsp_wr5_cfg : 16; /* bit[16-31]: HKADC�Ĵ�����д���ã�
                                                       31����дָʾ��0��д��1����
                                                       30-24����д��ַ
                                                       23-16����д���� */
    } reg;
} SOC_HKADC_SSI_HKADC_WR45_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_WR45_DATA_dsp_wr4_cfg_START  (0)
#define SOC_HKADC_SSI_HKADC_WR45_DATA_dsp_wr4_cfg_END    (15)
#define SOC_HKADC_SSI_HKADC_WR45_DATA_dsp_wr5_cfg_START  (16)
#define SOC_HKADC_SSI_HKADC_WR45_DATA_dsp_wr5_cfg_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HKADC_SSI_HKADC_WR67_DATA_UNION
 �ṹ˵��  : HKADC_WR67_DATA �Ĵ����ṹ���塣��ַƫ����:0x002C����ֵ:0x00000000�����:32
 �Ĵ���˵��: HKADC�������á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_wr6_cfg : 16; /* bit[0-15] : HKADC�Ĵ�����д���ã�
                                                       15����дָʾ��0��д��1����
                                                       14-8����д��ַ
                                                       7-0����д���� */
        unsigned int  dsp_wr7_cfg : 16; /* bit[16-31]: HKADC�Ĵ�����д���ã�
                                                       31����дָʾ��0��д��1����
                                                       30-24����д��ַ
                                                       23-16����д���� */
    } reg;
} SOC_HKADC_SSI_HKADC_WR67_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_WR67_DATA_dsp_wr6_cfg_START  (0)
#define SOC_HKADC_SSI_HKADC_WR67_DATA_dsp_wr6_cfg_END    (15)
#define SOC_HKADC_SSI_HKADC_WR67_DATA_dsp_wr7_cfg_START  (16)
#define SOC_HKADC_SSI_HKADC_WR67_DATA_dsp_wr7_cfg_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HKADC_SSI_HKADC_DELAY01_UNION
 �ṹ˵��  : HKADC_DELAY01 �Ĵ����ṹ���塣��ַƫ����:0x0030����ֵ:0x00000000�����:32
 �Ĵ���˵��: HKADC�ӳ����á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_delay0 : 16; /* bit[0-15] : HKADC��д�Ĵ���0�ͼĴ���1֮����������ʱ����λ1 cycle */
        unsigned int  dsp_delay1 : 16; /* bit[16-31]: HKADC��д�Ĵ���1�ͼĴ���2֮����������ʱ����λ1 cycle */
    } reg;
} SOC_HKADC_SSI_HKADC_DELAY01_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DELAY01_dsp_delay0_START  (0)
#define SOC_HKADC_SSI_HKADC_DELAY01_dsp_delay0_END    (15)
#define SOC_HKADC_SSI_HKADC_DELAY01_dsp_delay1_START  (16)
#define SOC_HKADC_SSI_HKADC_DELAY01_dsp_delay1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HKADC_SSI_HKADC_DELAY23_UNION
 �ṹ˵��  : HKADC_DELAY23 �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x00000000�����:32
 �Ĵ���˵��: HKADC�ӳ����á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_delay2 : 16; /* bit[0-15] : HKADC��д�Ĵ���2�ͼĴ���3֮����������ʱ����λ1 cycle */
        unsigned int  dsp_delay3 : 16; /* bit[16-31]: HKADC��д�Ĵ���3�ͼĴ���4֮����������ʱ����λ1 cycle */
    } reg;
} SOC_HKADC_SSI_HKADC_DELAY23_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DELAY23_dsp_delay2_START  (0)
#define SOC_HKADC_SSI_HKADC_DELAY23_dsp_delay2_END    (15)
#define SOC_HKADC_SSI_HKADC_DELAY23_dsp_delay3_START  (16)
#define SOC_HKADC_SSI_HKADC_DELAY23_dsp_delay3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HKADC_SSI_HKADC_DELAY45_UNION
 �ṹ˵��  : HKADC_DELAY45 �Ĵ����ṹ���塣��ַƫ����:0x0038����ֵ:0x00000000�����:32
 �Ĵ���˵��: HKADC�ӳ����á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_delay4 : 16; /* bit[0-15] : HKADC��д�Ĵ���4�ͼĴ���5֮����������ʱ����λ1 cycle */
        unsigned int  dsp_delay5 : 16; /* bit[16-31]: HKADC��д�Ĵ���5�ͼĴ���6֮����������ʱ����λ1 cycle */
    } reg;
} SOC_HKADC_SSI_HKADC_DELAY45_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DELAY45_dsp_delay4_START  (0)
#define SOC_HKADC_SSI_HKADC_DELAY45_dsp_delay4_END    (15)
#define SOC_HKADC_SSI_HKADC_DELAY45_dsp_delay5_START  (16)
#define SOC_HKADC_SSI_HKADC_DELAY45_dsp_delay5_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HKADC_SSI_HKADC_DELAY6_UNION
 �ṹ˵��  : HKADC_DELAY6 �Ĵ����ṹ���塣��ַƫ����:0x003C����ֵ:0x00000000�����:32
 �Ĵ���˵��: HKADC�ӳ����á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_delay6 : 16; /* bit[0-15] : HKADC��д�Ĵ���6�ͼĴ���7֮����������ʱ����λ1 cycle */
        unsigned int  reserved   : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_HKADC_SSI_HKADC_DELAY6_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DELAY6_dsp_delay6_START  (0)
#define SOC_HKADC_SSI_HKADC_DELAY6_dsp_delay6_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_HKADC_SSI_HKADC_DSP_RD0_DATA_UNION
 �ṹ˵��  : HKADC_DSP_RD0_DATA �Ĵ����ṹ���塣��ַƫ����:0x0040����ֵ:0x00000000�����:32
 �Ĵ���˵��: HKADC���ݻض���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_rd0_data : 32; /* bit[0-31]: HKADC�Ĵ���0�ض�ֵ */
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_RD0_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_RD0_DATA_dsp_rd0_data_START  (0)
#define SOC_HKADC_SSI_HKADC_DSP_RD0_DATA_dsp_rd0_data_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HKADC_SSI_HKADC_DSP_RD1_DATA_UNION
 �ṹ˵��  : HKADC_DSP_RD1_DATA �Ĵ����ṹ���塣��ַƫ����:0x0044����ֵ:0x00000000�����:32
 �Ĵ���˵��: HKADC���ݻض���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_rd1_data : 32; /* bit[0-31]: HKADC�Ĵ���1�ض�ֵ */
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_RD1_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_RD1_DATA_dsp_rd1_data_START  (0)
#define SOC_HKADC_SSI_HKADC_DSP_RD1_DATA_dsp_rd1_data_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HKADC_SSI_HKADC_DSP_RD2_DATA_UNION
 �ṹ˵��  : HKADC_DSP_RD2_DATA �Ĵ����ṹ���塣��ַƫ����:0x0048����ֵ:0x00000000�����:32
 �Ĵ���˵��: HKADC���ݻض���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_rd2_data : 32; /* bit[0-31]: HKADC�Ĵ���2�ض�ֵ */
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_RD2_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_RD2_DATA_dsp_rd2_data_START  (0)
#define SOC_HKADC_SSI_HKADC_DSP_RD2_DATA_dsp_rd2_data_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HKADC_SSI_HKADC_DSP_RD3_DATA_UNION
 �ṹ˵��  : HKADC_DSP_RD3_DATA �Ĵ����ṹ���塣��ַƫ����:0x004C����ֵ:0x00000000�����:32
 �Ĵ���˵��: HKADC���ݻض���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_rd3_data : 32; /* bit[0-31]: HKADC�Ĵ���3�ض�ֵ */
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_RD3_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_RD3_DATA_dsp_rd3_data_START  (0)
#define SOC_HKADC_SSI_HKADC_DSP_RD3_DATA_dsp_rd3_data_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HKADC_SSI_HKADC_DSP_RD4_DATA_UNION
 �ṹ˵��  : HKADC_DSP_RD4_DATA �Ĵ����ṹ���塣��ַƫ����:0x0050����ֵ:0x00000000�����:32
 �Ĵ���˵��: HKADC���ݻض���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_rd4_data : 32; /* bit[0-31]: HKADC�Ĵ���4�ض�ֵ */
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_RD4_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_RD4_DATA_dsp_rd4_data_START  (0)
#define SOC_HKADC_SSI_HKADC_DSP_RD4_DATA_dsp_rd4_data_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HKADC_SSI_HKADC_DSP_RD5_DATA_UNION
 �ṹ˵��  : HKADC_DSP_RD5_DATA �Ĵ����ṹ���塣��ַƫ����:0x0054����ֵ:0x00000000�����:32
 �Ĵ���˵��: HKADC���ݻض���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_rd5_data : 32; /* bit[0-31]: HKADC�Ĵ���5�ض�ֵ */
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_RD5_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_RD5_DATA_dsp_rd5_data_START  (0)
#define SOC_HKADC_SSI_HKADC_DSP_RD5_DATA_dsp_rd5_data_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HKADC_SSI_HKADC_DSP_RD6_DATA_UNION
 �ṹ˵��  : HKADC_DSP_RD6_DATA �Ĵ����ṹ���塣��ַƫ����:0x0058����ֵ:0x00000000�����:32
 �Ĵ���˵��: HKADC���ݻض���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_rd6_data : 32; /* bit[0-31]: HKADC�Ĵ���6�ض�ֵ */
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_RD6_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_RD6_DATA_dsp_rd6_data_START  (0)
#define SOC_HKADC_SSI_HKADC_DSP_RD6_DATA_dsp_rd6_data_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HKADC_SSI_HKADC_DSP_RD7_DATA_UNION
 �ṹ˵��  : HKADC_DSP_RD7_DATA �Ĵ����ṹ���塣��ַƫ����:0x005C����ֵ:0x00000000�����:32
 �Ĵ���˵��: HKADC���ݻض���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_rd7_data : 32; /* bit[0-31]: HKADC�Ĵ���7�ض�ֵ */
    } reg;
} SOC_HKADC_SSI_HKADC_DSP_RD7_DATA_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DSP_RD7_DATA_dsp_rd7_data_START  (0)
#define SOC_HKADC_SSI_HKADC_DSP_RD7_DATA_dsp_rd7_data_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HKADC_SSI_HKADC_OP_INTERVAL_UNION
 �ṹ˵��  : HKADC_OP_INTERVAL �Ĵ����ṹ���塣��ַƫ����:0x0060����ֵ:0x00000000�����:32
 �Ĵ���˵��: HKADC�������ʱ�����á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hkadc_op_interval : 32; /* bit[0-31]: HKADC����������ʱ������ */
    } reg;
} SOC_HKADC_SSI_HKADC_OP_INTERVAL_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_OP_INTERVAL_hkadc_op_interval_START  (0)
#define SOC_HKADC_SSI_HKADC_OP_INTERVAL_hkadc_op_interval_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HKADC_SSI_HKADC_OP_INTERVAL_BYPASS_UNION
 �ṹ˵��  : HKADC_OP_INTERVAL_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x0064����ֵ:0x00000001�����:32
 �Ĵ���˵��: HKADC�������ʱ�书��ʹ�ܡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  op_interval_bypass_en : 1;  /* bit[0]   : op_interval����bypassʹ�ܣ�
                                                                0��ʹ��op_interval����
                                                                1��bypass op_interval���� */
        unsigned int  reserved              : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_HKADC_SSI_HKADC_OP_INTERVAL_BYPASS_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_OP_INTERVAL_BYPASS_op_interval_bypass_en_START  (0)
#define SOC_HKADC_SSI_HKADC_OP_INTERVAL_BYPASS_op_interval_bypass_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_HKADC_SSI_HKADC_CHANNEL_EN_UNION
 �ṹ˵��  : HKADC_CHANNEL_EN �Ĵ����ṹ���塣��ַƫ����:0x0068����ֵ:0x00000007�����:32
 �Ĵ���˵��: HKADCͨ��ʹ�ܡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hkadc_channel_en_sft : 1;  /* bit[0]   : ���ͨ��ʹ�ܣ���Ҫ����ʹ�ã���
                                                               0���ر�ͨ��
                                                               1����ͨ�� */
        unsigned int  hkadc_channel_en_hd0 : 1;  /* bit[1]   : Ӳ��channel0ͨ��ʹ�ܣ���Ҫ����ʹ�ã���
                                                               0���ر�ͨ��
                                                               1����ͨ�� */
        unsigned int  hkadc_channel_en_hd1 : 1;  /* bit[2]   : Ӳ��channel1ͨ��ʹ�ܣ���Ҫ����ʹ�ã���
                                                               0���ر�ͨ��
                                                               1����ͨ�� */
        unsigned int  reserved             : 29; /* bit[3-31]: reserved */
    } reg;
} SOC_HKADC_SSI_HKADC_CHANNEL_EN_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_CHANNEL_EN_hkadc_channel_en_sft_START  (0)
#define SOC_HKADC_SSI_HKADC_CHANNEL_EN_hkadc_channel_en_sft_END    (0)
#define SOC_HKADC_SSI_HKADC_CHANNEL_EN_hkadc_channel_en_hd0_START  (1)
#define SOC_HKADC_SSI_HKADC_CHANNEL_EN_hkadc_channel_en_hd0_END    (1)
#define SOC_HKADC_SSI_HKADC_CHANNEL_EN_hkadc_channel_en_hd1_START  (2)
#define SOC_HKADC_SSI_HKADC_CHANNEL_EN_hkadc_channel_en_hd1_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_HKADC_SSI_HKADC_DBG_INFO_UNION
 �ṹ˵��  : HKADC_DBG_INFO �Ĵ����ṹ���塣��ַƫ����:0x00D0����ֵ:0x00000000�����:32
 �Ĵ���˵��: HKADC �������ݡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  arb_info : 32; /* bit[0-31]: ״̬�ź���ϵ��ϱ��Ĵ��� */
    } reg;
} SOC_HKADC_SSI_HKADC_DBG_INFO_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_DBG_INFO_arb_info_START  (0)
#define SOC_HKADC_SSI_HKADC_DBG_INFO_arb_info_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_HKADC_SSI_HKADC_FINSH_RAW_INT_UNION
 �ṹ˵��  : HKADC_FINSH_RAW_INT �Ĵ����ṹ���塣��ַƫ����:0x0100����ֵ:0x00000000�����:32
 �Ĵ���˵��: HKADC �������ԭʼ�жϡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hkadc_finish_raw_int : 1;  /* bit[0]   : hkadc�������ԭʼ�ж� */
        unsigned int  reserved             : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_HKADC_SSI_HKADC_FINSH_RAW_INT_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_FINSH_RAW_INT_hkadc_finish_raw_int_START  (0)
#define SOC_HKADC_SSI_HKADC_FINSH_RAW_INT_hkadc_finish_raw_int_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_HKADC_SSI_HKADC_FINSH_MSK_INT_UNION
 �ṹ˵��  : HKADC_FINSH_MSK_INT �Ĵ����ṹ���塣��ַƫ����:0x0104����ֵ:0x00000000�����:32
 �Ĵ���˵��: HKADC����������κ��жϡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hkadc_finish_msk_int : 1;  /* bit[0]   : hkadc����������κ��ж� */
        unsigned int  reserved             : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_HKADC_SSI_HKADC_FINSH_MSK_INT_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_FINSH_MSK_INT_hkadc_finish_msk_int_START  (0)
#define SOC_HKADC_SSI_HKADC_FINSH_MSK_INT_hkadc_finish_msk_int_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_HKADC_SSI_HKADC_FINSH_INT_CLR_UNION
 �ṹ˵��  : HKADC_FINSH_INT_CLR �Ĵ����ṹ���塣��ַƫ����:0x0108����ֵ:0x00000000�����:32
 �Ĵ���˵��: HKADC��������ж������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hkadc_finish_int_clr : 1;  /* bit[0]   : hkadc��������ж���� */
        unsigned int  reserved             : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_HKADC_SSI_HKADC_FINSH_INT_CLR_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_FINSH_INT_CLR_hkadc_finish_int_clr_START  (0)
#define SOC_HKADC_SSI_HKADC_FINSH_INT_CLR_hkadc_finish_int_clr_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_HKADC_SSI_HKADC_FINSH_INT_MSK_UNION
 �ṹ˵��  : HKADC_FINSH_INT_MSK �Ĵ����ṹ���塣��ַƫ����:0x010C����ֵ:0x00000000�����:32
 �Ĵ���˵��: HKADC��������ж����Ρ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hkadc_finish_int_msk : 1;  /* bit[0]   : hkadc��������ж����� */
        unsigned int  reserved             : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_HKADC_SSI_HKADC_FINSH_INT_MSK_UNION;
#endif
#define SOC_HKADC_SSI_HKADC_FINSH_INT_MSK_hkadc_finish_int_msk_START  (0)
#define SOC_HKADC_SSI_HKADC_FINSH_INT_MSK_hkadc_finish_int_msk_END    (0)






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

#endif /* end of soc_hkadc_ssi_interface.h */
