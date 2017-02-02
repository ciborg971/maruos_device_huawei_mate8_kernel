/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_dss_dbuf_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:20:00
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_DSS_DBUF.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_DSS_DBUF_INTERFACE_H__
#define __SOC_DSS_DBUF_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_DBUF
 ****************************************************************************/
/* �Ĵ���˵����֡�ߴ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_DBUF_FRM_SIZE_UNION */
#define SOC_DSS_DBUF_FRM_SIZE_ADDR(base)              ((base) + (0x0000))

/* �Ĵ���˵�����гߴ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_DBUF_FRM_HSIZE_UNION */
#define SOC_DSS_DBUF_FRM_HSIZE_ADDR(base)             ((base) + (0x0004))

/* �Ĵ���˵������ЧSRAM��Ŀ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_DBUF_SRAM_VALID_NUM_UNION */
#define SOC_DSS_DBUF_SRAM_VALID_NUM_ADDR(base)        ((base) + (0x0008))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DBUF_WBE_EN_UNION */
#define SOC_DSS_DBUF_WBE_EN_ADDR(base)                ((base) + (0x000C))

/* �Ĵ���˵����ͳ��ˮ��1
   λ����UNION�ṹ:  SOC_DSS_DBUF_THD_FILL_LEV0_UNION */
#define SOC_DSS_DBUF_THD_FILL_LEV0_ADDR(base)         ((base) + (0x0010))

/* �Ĵ���˵����ͳ��ˮ��2
   λ����UNION�ṹ:  SOC_DSS_DBUF_DFS_FILL_LEV1_UNION */
#define SOC_DSS_DBUF_DFS_FILL_LEV1_ADDR(base)         ((base) + (0x0014))

/* �Ĵ���˵����RQoS��ֵ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_DBUF_THD_RQOS_UNION */
#define SOC_DSS_DBUF_THD_RQOS_ADDR(base)              ((base) + (0x0018))

/* �Ĵ���˵����WQoS��ֵ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_DBUF_THD_WQOS_UNION */
#define SOC_DSS_DBUF_THD_WQOS_ADDR(base)              ((base) + (0x001C))

/* �Ĵ���˵����CG��ֵ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_DBUF_THD_CG_UNION */
#define SOC_DSS_DBUF_THD_CG_ADDR(base)                ((base) + (0x0020))

/* �Ĵ���˵�������������ֵ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_DBUF_THD_OTHER_UNION */
#define SOC_DSS_DBUF_THD_OTHER_ADDR(base)             ((base) + (0x0024))

/* �Ĵ���˵�������ˮ��0ͳ��ֵ
   λ����UNION�ṹ:  SOC_DSS_DBUF_FILL_LEV0_CNT_UNION */
#define SOC_DSS_DBUF_FILL_LEV0_CNT_ADDR(base)         ((base) + (0x0028))

/* �Ĵ���˵�������ˮ��1ͳ��ֵ
   λ����UNION�ṹ:  SOC_DSS_DBUF_FILL_LEV1_CNT_UNION */
#define SOC_DSS_DBUF_FILL_LEV1_CNT_ADDR(base)         ((base) + (0x002C))

/* �Ĵ���˵�������ˮ��2ͳ��ֵ
   λ����UNION�ṹ:  SOC_DSS_DBUF_FILL_LEV2_CNT_UNION */
#define SOC_DSS_DBUF_FILL_LEV2_CNT_ADDR(base)         ((base) + (0x0030))

/* �Ĵ���˵�������ˮ��3ͳ��ֵ
   λ����UNION�ṹ:  SOC_DSS_DBUF_FILL_LEV3_CNT_UNION */
#define SOC_DSS_DBUF_FILL_LEV3_CNT_ADDR(base)         ((base) + (0x0034))

/* �Ĵ���˵�������ˮ��4ͳ��ֵ
   λ����UNION�ṹ:  SOC_DSS_DBUF_FILL_LEV4_CNT_UNION */
#define SOC_DSS_DBUF_FILL_LEV4_CNT_ADDR(base)         ((base) + (0x0038))

/* �Ĵ���˵��������ͨ·���ˮ�޼Ĵ���
   λ����UNION�ṹ:  SOC_DSS_DBUF_ONLINE_FILL_LEVEL_UNION */
#define SOC_DSS_DBUF_ONLINE_FILL_LEVEL_ADDR(base)     ((base) + (0x003C))

/* �Ĵ���˵������дͨ·���ˮ�޼Ĵ���
   λ����UNION�ṹ:  SOC_DSS_DBUF_WB_FILL_LEVEL_UNION */
#define SOC_DSS_DBUF_WB_FILL_LEVEL_ADDR(base)         ((base) + (0x0040))

/* �Ĵ���˵����״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_DBUF_DFS_STATUS_UNION */
#define SOC_DSS_DBUF_DFS_STATUS_ADDR(base)            ((base) + (0x0044))

/* �Ĵ���˵����SRAM�͹��Ŀ��ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_DBUF_DFS_LP_CTRL_UNION */
#define SOC_DSS_DBUF_DFS_LP_CTRL_ADDR(base)           ((base) + (0x004C))

/* �Ĵ���˵�������Ĵ���ѡ���ź�
   λ����UNION�ṹ:  SOC_DSS_DBUF_DBUF_RD_SHADOW_SEL_UNION */
#define SOC_DSS_DBUF_DBUF_RD_SHADOW_SEL_ADDR(base)    ((base) + (0x0050))

/* �Ĵ���˵����MEM�͹��Ŀ��ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_DBUF_DBUF_MEM_CTRL_UNION */
#define SOC_DSS_DBUF_DBUF_MEM_CTRL_ADDR(base)         ((base) + (0x0054))

/* �Ĵ���˵����һ��ģ��ʱ��ѡ���ź�
   λ����UNION�ṹ:  SOC_DSS_DBUF_DBUF_CLK_SEL_UNION */
#define SOC_DSS_DBUF_DBUF_CLK_SEL_ADDR(base)          ((base) + (0x005C))

/* �Ĵ���˵����һ��ģ��ʱ��ʹ���ź�
   λ����UNION�ṹ:  SOC_DSS_DBUF_DBUF_CLK_EN_UNION */
#define SOC_DSS_DBUF_DBUF_CLK_EN_ADDR(base)           ((base) + (0x0060))

/* �Ĵ���˵����CPU��дmemoryʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_DSS_DBUF_DBG_CPU_EN_UNION */
#define SOC_DSS_DBUF_DBG_CPU_EN_ADDR(base)            ((base) + (0x0070))

/* �Ĵ���˵����SRAM�͹��Ŀ��ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_DBUF_DBG_CPU_START_UNION */
#define SOC_DSS_DBUF_DBG_CPU_START_ADDR(base)         ((base) + (0x0074))

/* �Ĵ���˵����CPU����memory��д�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_DBUF_DBG_CPU_CTL_UNION */
#define SOC_DSS_DBUF_DBG_CPU_CTL_ADDR(base)           ((base) + (0x0078))

/* �Ĵ���˵����MEM������0
   λ����UNION�ṹ:  SOC_DSS_DBUF_DBG_CPU_RDATA0_UNION */
#define SOC_DSS_DBUF_DBG_CPU_RDATA0_ADDR(base)        ((base) + (0x007C))

/* �Ĵ���˵����MEM������0
   λ����UNION�ṹ:  SOC_DSS_DBUF_DBG_CPU_RDATA1_UNION */
#define SOC_DSS_DBUF_DBG_CPU_RDATA1_ADDR(base)        ((base) + (0x0080))

/* �Ĵ���˵����MEM������0
   λ����UNION�ṹ:  SOC_DSS_DBUF_DBG_CPU_RDATA2_UNION */
#define SOC_DSS_DBUF_DBG_CPU_RDATA2_ADDR(base)        ((base) + (0x0084))

/* �Ĵ���˵����MEM������0
   λ����UNION�ṹ:  SOC_DSS_DBUF_DBG_CPU_RDATA3_UNION */
#define SOC_DSS_DBUF_DBG_CPU_RDATA3_ADDR(base)        ((base) + (0x0088))

/* �Ĵ���˵����MEM������0
   λ����UNION�ṹ:  SOC_DSS_DBUF_DBG_CPU_RDATA4_UNION */
#define SOC_DSS_DBUF_DBG_CPU_RDATA4_ADDR(base)        ((base) + (0x008C))

/* �Ĵ���˵����MEM������0
   λ����UNION�ṹ:  SOC_DSS_DBUF_DBG_CPU_WDATA0_UNION */
#define SOC_DSS_DBUF_DBG_CPU_WDATA0_ADDR(base)        ((base) + (0x0090))

/* �Ĵ���˵����MEM������0
   λ����UNION�ṹ:  SOC_DSS_DBUF_DBG_CPU_WDATA1_UNION */
#define SOC_DSS_DBUF_DBG_CPU_WDATA1_ADDR(base)        ((base) + (0x0094))

/* �Ĵ���˵����MEM������0
   λ����UNION�ṹ:  SOC_DSS_DBUF_DBG_CPU_WDATA2_UNION */
#define SOC_DSS_DBUF_DBG_CPU_WDATA2_ADDR(base)        ((base) + (0x0098))

/* �Ĵ���˵����MEM������0
   λ����UNION�ṹ:  SOC_DSS_DBUF_DBG_CPU_WDATA3_UNION */
#define SOC_DSS_DBUF_DBG_CPU_WDATA3_ADDR(base)        ((base) + (0x009C))

/* �Ĵ���˵����MEM������0
   λ����UNION�ṹ:  SOC_DSS_DBUF_DBG_CPU_WDATA4_UNION */
#define SOC_DSS_DBUF_DBG_CPU_WDATA4_ADDR(base)        ((base) + (0x00A0))

/* �Ĵ���˵����ģ��Ӱ�ӼĴ����ָ���Ĭ��ֵ
   λ����UNION�ṹ:  SOC_DSS_DBUF_REG_DEFAULT_UNION */
#define SOC_DSS_DBUF_REG_DEFAULT_ADDR(base)           ((base) + (0x00A4))





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
                     (1/1) reg_DBUF
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_FRM_SIZE_UNION
 �ṹ˵��  : FRM_SIZE �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: ֡�ߴ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_size : 27; /* bit[0-26] : һ֡ͼ������ظ��������磬���ͼ��ֱ���Ϊ16x16����frm_sizeΪ256 */
        unsigned int  reserved : 5;  /* bit[27-31]: ���� */
    } reg;
} SOC_DSS_DBUF_FRM_SIZE_UNION;
#endif
#define SOC_DSS_DBUF_FRM_SIZE_frm_size_START  (0)
#define SOC_DSS_DBUF_FRM_SIZE_frm_size_END    (26)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_FRM_HSIZE_UNION
 �ṹ˵��  : FRM_HSIZE �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: �гߴ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_hsize : 13; /* bit[0-12] : һ�е����ظ�����Ϊʵ��ֵ��1�����磬���ͼ��ֱ���Ϊ16x16����frm_sizeΪ15 */
        unsigned int  reserved  : 19; /* bit[13-31]: ���� */
    } reg;
} SOC_DSS_DBUF_FRM_HSIZE_UNION;
#endif
#define SOC_DSS_DBUF_FRM_HSIZE_frm_hsize_START  (0)
#define SOC_DSS_DBUF_FRM_HSIZE_frm_hsize_END    (12)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_SRAM_VALID_NUM_UNION
 �ṹ˵��  : SRAM_VALID_NUM �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ЧSRAM��Ŀ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sram_valid_num : 2;  /* bit[0-1] : ����DBUF0����Чmemory�ĸ���
                                                         0:DFS������Ϊ1408x144bits
                                                         1:DFS������Ϊ2816x144bits
                                                         2:DFS������Ϊ4224x144bits
                                                         3:����
                                                         
                                                         ����DBUF1����Чmemory�ĸ���
                                                         0:DFS������Ϊ512x144bits
                                                         1:DFS������Ϊ1024x144bits
                                                         2,3:���� */
        unsigned int  reserved       : 30; /* bit[2-31]: DBUF0���� */
    } reg;
} SOC_DSS_DBUF_SRAM_VALID_NUM_UNION;
#endif
#define SOC_DSS_DBUF_SRAM_VALID_NUM_sram_valid_num_START  (0)
#define SOC_DSS_DBUF_SRAM_VALID_NUM_sram_valid_num_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_WBE_EN_UNION
 �ṹ˵��  : WBE_EN �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wbe_en   : 1;  /* bit[0]   :  */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_DBUF_WBE_EN_UNION;
#endif
#define SOC_DSS_DBUF_WBE_EN_wbe_en_START    (0)
#define SOC_DSS_DBUF_WBE_EN_wbe_en_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_THD_FILL_LEV0_UNION
 �ṹ˵��  : THD_FILL_LEV0 �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x0258012C�����:32
 �Ĵ���˵��: ͳ��ˮ��1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thd_fill_lev1 : 14; /* bit[0-13] : ���ˮ��1���˴����ˮ�޵ĵ�λΪmemory��ȣ��������1��Ӧ��1x144bits = 6���� */
        unsigned int  reserved_0    : 2;  /* bit[14-15]: ���� */
        unsigned int  thd_fill_lev2 : 14; /* bit[16-29]: ���ˮ��2���˴����ˮ�޵ĵ�λΪmemory��ȣ��������1��Ӧ��1x144bits = 6���� */
        unsigned int  reserved_1    : 2;  /* bit[30-31]: ���� */
    } reg;
} SOC_DSS_DBUF_THD_FILL_LEV0_UNION;
#endif
#define SOC_DSS_DBUF_THD_FILL_LEV0_thd_fill_lev1_START  (0)
#define SOC_DSS_DBUF_THD_FILL_LEV0_thd_fill_lev1_END    (13)
#define SOC_DSS_DBUF_THD_FILL_LEV0_thd_fill_lev2_START  (16)
#define SOC_DSS_DBUF_THD_FILL_LEV0_thd_fill_lev2_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_DFS_FILL_LEV1_UNION
 �ṹ˵��  : DFS_FILL_LEV1 �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x04B00384�����:32
 �Ĵ���˵��: ͳ��ˮ��2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thd_fill_lev3 : 14; /* bit[0-13] : ���ˮ��3���˴����ˮ�޵ĵ�λΪmemory��ȣ��������1��Ӧ��1x144bits = 6���� */
        unsigned int  reserved_0    : 2;  /* bit[14-15]: ���� */
        unsigned int  thd_fill_lev4 : 14; /* bit[16-29]: ���ˮ��4���˴����ˮ�޵ĵ�λΪmemory��ȣ��������1��Ӧ��1x144bits = 6���� */
        unsigned int  reserved_1    : 2;  /* bit[30-31]: ���� */
    } reg;
} SOC_DSS_DBUF_DFS_FILL_LEV1_UNION;
#endif
#define SOC_DSS_DBUF_DFS_FILL_LEV1_thd_fill_lev3_START  (0)
#define SOC_DSS_DBUF_DFS_FILL_LEV1_thd_fill_lev3_END    (13)
#define SOC_DSS_DBUF_DFS_FILL_LEV1_thd_fill_lev4_START  (16)
#define SOC_DSS_DBUF_DFS_FILL_LEV1_thd_fill_lev4_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_THD_RQOS_UNION
 �ṹ˵��  : THD_RQOS �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: RQoS��ֵ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thd_rqos_in  : 14; /* bit[0-13] : ����ͨ·���ˮ��С�ڴ���ֵʱ��rqos�ź���1���˴����ˮ�޵ĵ�λΪmemory��ȣ��������1��Ӧ��1x144bits = 6���� */
        unsigned int  reserved_0   : 2;  /* bit[14-15]: ���� */
        unsigned int  thd_rqos_out : 14; /* bit[16-29]: ����ͨ·���ˮ�޴��ڴ���ֵʱ��rqos�ź���0���˴����ˮ�޵ĵ�λΪmemory��ȣ��������1��Ӧ��1x144bits = 6���� */
        unsigned int  reserved_1   : 2;  /* bit[30-31]: ���� */
    } reg;
} SOC_DSS_DBUF_THD_RQOS_UNION;
#endif
#define SOC_DSS_DBUF_THD_RQOS_thd_rqos_in_START   (0)
#define SOC_DSS_DBUF_THD_RQOS_thd_rqos_in_END     (13)
#define SOC_DSS_DBUF_THD_RQOS_thd_rqos_out_START  (16)
#define SOC_DSS_DBUF_THD_RQOS_thd_rqos_out_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_THD_WQOS_UNION
 �ṹ˵��  : THD_WQOS �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000000�����:32
 �Ĵ���˵��: WQoS��ֵ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thd_wqos_in  : 14; /* bit[0-13] : wbͨ·���ˮ�޴��ڴ���ֵʱ��wqos�ź���1���˴����ˮ�޵ĵ�λΪmemory��ȣ��������1��Ӧ��1x144bits = 6���� */
        unsigned int  reserved_0   : 2;  /* bit[14-15]: ���� */
        unsigned int  thd_wqos_out : 14; /* bit[16-29]: wbͨ·���ˮ��С�ڴ���ֵʱ��wqos�ź���0���˴����ˮ�޵ĵ�λΪmemory��ȣ��������1��Ӧ��1x144bits = 6���� */
        unsigned int  reserved_1   : 2;  /* bit[30-31]: ���� */
    } reg;
} SOC_DSS_DBUF_THD_WQOS_UNION;
#endif
#define SOC_DSS_DBUF_THD_WQOS_thd_wqos_in_START   (0)
#define SOC_DSS_DBUF_THD_WQOS_thd_wqos_in_END     (13)
#define SOC_DSS_DBUF_THD_WQOS_thd_wqos_out_START  (16)
#define SOC_DSS_DBUF_THD_WQOS_thd_wqos_out_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_THD_CG_UNION
 �ṹ˵��  : THD_CG �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: CG��ֵ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thd_cg_in  : 14; /* bit[0-13] : ����ͨ�����ˮ�޴��ڴ���ֵʱ��clock gate�ź���1���˴����ˮ�޵ĵ�λΪmemory��ȣ��������1��Ӧ��1x144bits = 6���� */
        unsigned int  reserved_0 : 2;  /* bit[14-15]: ���� */
        unsigned int  thd_cg_out : 14; /* bit[16-29]: ����ͨ�����ˮ��С�ڴ���ֵʱ��clock gate�ź���0���˴����ˮ�޵ĵ�λΪmemory��ȣ��������1��Ӧ��1x144bits = 6���� */
        unsigned int  reserved_1 : 2;  /* bit[30-31]: ���� */
    } reg;
} SOC_DSS_DBUF_THD_CG_UNION;
#endif
#define SOC_DSS_DBUF_THD_CG_thd_cg_in_START   (0)
#define SOC_DSS_DBUF_THD_CG_thd_cg_in_END     (13)
#define SOC_DSS_DBUF_THD_CG_thd_cg_out_START  (16)
#define SOC_DSS_DBUF_THD_CG_thd_cg_out_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_THD_OTHER_UNION
 �ṹ˵��  : THD_OTHER �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x001015E0�����:32
 �Ĵ���˵��: ���������ֵ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thd_wr_wait : 14; /* bit[0-13] : wbͨ�����ˮ�޴�������ͨ�����ˮ�ޣ��������߲�ֵС�ڴ���ֵʱ��DFS��������ͨ����full�ź���ΪFIFO��full�źţ������������ͨ����full�ź���ΪFIFO��full
                                                       Ĭ��ֵΪ5856-256=5600 */
        unsigned int  reserved_0  : 2;  /* bit[14-15]: ���� */
        unsigned int  dfs_cg_hold : 8;  /* bit[16-23]: dfs_ret_en���½�����dfs_cg�½���֮�����ʱ������
                                                       TBD */
        unsigned int  reserved_1  : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_DBUF_THD_OTHER_UNION;
#endif
#define SOC_DSS_DBUF_THD_OTHER_thd_wr_wait_START  (0)
#define SOC_DSS_DBUF_THD_OTHER_thd_wr_wait_END    (13)
#define SOC_DSS_DBUF_THD_OTHER_dfs_cg_hold_START  (16)
#define SOC_DSS_DBUF_THD_OTHER_dfs_cg_hold_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_FILL_LEV0_CNT_UNION
 �ṹ˵��  : FILL_LEV0_CNT �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���ˮ��0ͳ��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fill_lev0_cnt : 32; /* bit[0-31]: һ֡��DFS FIFO�����ˮ��С��fill_lev1�������� */
    } reg;
} SOC_DSS_DBUF_FILL_LEV0_CNT_UNION;
#endif
#define SOC_DSS_DBUF_FILL_LEV0_CNT_fill_lev0_cnt_START  (0)
#define SOC_DSS_DBUF_FILL_LEV0_CNT_fill_lev0_cnt_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_FILL_LEV1_CNT_UNION
 �ṹ˵��  : FILL_LEV1_CNT �Ĵ����ṹ���塣��ַƫ����:0x002C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���ˮ��1ͳ��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fill_lev1_cnt : 32; /* bit[0-31]: һ֡��DFS FIFO�����ˮ�޴��ڵ���fill_lev1��С��fill_lev2�������� */
    } reg;
} SOC_DSS_DBUF_FILL_LEV1_CNT_UNION;
#endif
#define SOC_DSS_DBUF_FILL_LEV1_CNT_fill_lev1_cnt_START  (0)
#define SOC_DSS_DBUF_FILL_LEV1_CNT_fill_lev1_cnt_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_FILL_LEV2_CNT_UNION
 �ṹ˵��  : FILL_LEV2_CNT �Ĵ����ṹ���塣��ַƫ����:0x0030����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���ˮ��2ͳ��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fill_lev2_cnt : 32; /* bit[0-31]: һ֡��DFS FIFO�����ˮ�޴��ڵ���fill_lev2��С��fill_lev3�������� */
    } reg;
} SOC_DSS_DBUF_FILL_LEV2_CNT_UNION;
#endif
#define SOC_DSS_DBUF_FILL_LEV2_CNT_fill_lev2_cnt_START  (0)
#define SOC_DSS_DBUF_FILL_LEV2_CNT_fill_lev2_cnt_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_FILL_LEV3_CNT_UNION
 �ṹ˵��  : FILL_LEV3_CNT �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���ˮ��3ͳ��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fill_lev3_cnt : 32; /* bit[0-31]: һ֡��DFS FIFO�����ˮ�޴��ڵ���fill_lev3��С��fill_lev4�������� */
    } reg;
} SOC_DSS_DBUF_FILL_LEV3_CNT_UNION;
#endif
#define SOC_DSS_DBUF_FILL_LEV3_CNT_fill_lev3_cnt_START  (0)
#define SOC_DSS_DBUF_FILL_LEV3_CNT_fill_lev3_cnt_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_FILL_LEV4_CNT_UNION
 �ṹ˵��  : FILL_LEV4_CNT �Ĵ����ṹ���塣��ַƫ����:0x0038����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���ˮ��4ͳ��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fill_lev4_cnt : 32; /* bit[0-31]: һ֡��DFS FIFO�����ˮ�޴��ڵ���fill_lev4�������� */
    } reg;
} SOC_DSS_DBUF_FILL_LEV4_CNT_UNION;
#endif
#define SOC_DSS_DBUF_FILL_LEV4_CNT_fill_lev4_cnt_START  (0)
#define SOC_DSS_DBUF_FILL_LEV4_CNT_fill_lev4_cnt_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_ONLINE_FILL_LEVEL_UNION
 �ṹ˵��  : ONLINE_FILL_LEVEL �Ĵ����ṹ���塣��ַƫ����:0x003C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ·���ˮ�޼Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  online_fill_lev : 14; /* bit[0-13] :  */
        unsigned int  reserved        : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_DSS_DBUF_ONLINE_FILL_LEVEL_UNION;
#endif
#define SOC_DSS_DBUF_ONLINE_FILL_LEVEL_online_fill_lev_START  (0)
#define SOC_DSS_DBUF_ONLINE_FILL_LEVEL_online_fill_lev_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_WB_FILL_LEVEL_UNION
 �ṹ˵��  : WB_FILL_LEVEL �Ĵ����ṹ���塣��ַƫ����:0x0040����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��дͨ·���ˮ�޼Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wb_fill_lev : 14; /* bit[0-13] :  */
        unsigned int  reserved    : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_DSS_DBUF_WB_FILL_LEVEL_UNION;
#endif
#define SOC_DSS_DBUF_WB_FILL_LEVEL_wb_fill_lev_START  (0)
#define SOC_DSS_DBUF_WB_FILL_LEVEL_wb_fill_lev_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_DFS_STATUS_UNION
 �ṹ˵��  : DFS_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0044����ֵ:0x00000015�����:32
 �Ĵ���˵��: ״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  online_empty  : 1;  /* bit[0]   :  */
        unsigned int  online_full   : 1;  /* bit[1]   :  */
        unsigned int  offline_empty : 1;  /* bit[2]   :  */
        unsigned int  offline_full  : 1;  /* bit[3]   :  */
        unsigned int  dfs_cg        : 1;  /* bit[4]   :  */
        unsigned int  dfs_wqos      : 1;  /* bit[5]   :  */
        unsigned int  dfs_rqos      : 1;  /* bit[6]   :  */
        unsigned int  dfs_wb_error  : 1;  /* bit[7]   :  */
        unsigned int  reserved      : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_DSS_DBUF_DFS_STATUS_UNION;
#endif
#define SOC_DSS_DBUF_DFS_STATUS_online_empty_START   (0)
#define SOC_DSS_DBUF_DFS_STATUS_online_empty_END     (0)
#define SOC_DSS_DBUF_DFS_STATUS_online_full_START    (1)
#define SOC_DSS_DBUF_DFS_STATUS_online_full_END      (1)
#define SOC_DSS_DBUF_DFS_STATUS_offline_empty_START  (2)
#define SOC_DSS_DBUF_DFS_STATUS_offline_empty_END    (2)
#define SOC_DSS_DBUF_DFS_STATUS_offline_full_START   (3)
#define SOC_DSS_DBUF_DFS_STATUS_offline_full_END     (3)
#define SOC_DSS_DBUF_DFS_STATUS_dfs_cg_START         (4)
#define SOC_DSS_DBUF_DFS_STATUS_dfs_cg_END           (4)
#define SOC_DSS_DBUF_DFS_STATUS_dfs_wqos_START       (5)
#define SOC_DSS_DBUF_DFS_STATUS_dfs_wqos_END         (5)
#define SOC_DSS_DBUF_DFS_STATUS_dfs_rqos_START       (6)
#define SOC_DSS_DBUF_DFS_STATUS_dfs_rqos_END         (6)
#define SOC_DSS_DBUF_DFS_STATUS_dfs_wb_error_START   (7)
#define SOC_DSS_DBUF_DFS_STATUS_dfs_wb_error_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_DFS_LP_CTRL_UNION
 �ṹ˵��  : DFS_LP_CTRL �Ĵ����ṹ���塣��ַƫ����:0x004C����ֵ:0x00000003�����:32
 �Ĵ���˵��: SRAM�͹��Ŀ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pd_upon_frm_end  : 1;  /* bit[0]   : 0����DFS������һ֡���ݺ�DFS SRAM������͹���ģʽ
                                                           1����DFS������һ֡���ݺ�DFS SRAM����͹���ģʽ */
        unsigned int  ret_aft_prefetch : 1;  /* bit[1]   : 0��һ֡��ʼ��Ԥȡ��ɺ�DFS SRAM������retentionģʽ
                                                           1��һ֡��ʼ��Ԥȡ��ɺ�DFS SRAM����retentionģʽ��������ģʽ�£�Ԥȡ��ɺ�ֹͣ��WBͨ·������� */
        unsigned int  reserved         : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_DSS_DBUF_DFS_LP_CTRL_UNION;
#endif
#define SOC_DSS_DBUF_DFS_LP_CTRL_pd_upon_frm_end_START   (0)
#define SOC_DSS_DBUF_DFS_LP_CTRL_pd_upon_frm_end_END     (0)
#define SOC_DSS_DBUF_DFS_LP_CTRL_ret_aft_prefetch_START  (1)
#define SOC_DSS_DBUF_DFS_LP_CTRL_ret_aft_prefetch_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_DBUF_RD_SHADOW_SEL_UNION
 �ṹ˵��  : DBUF_RD_SHADOW_SEL �Ĵ����ṹ���塣��ַƫ����:0x0050����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���Ĵ���ѡ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbuf_rd_shadow : 1;  /* bit[0]   : 1'b0 :�������Ĵ���
                                                         1'b1 :��Ӱ�ӼĴ��� */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_DBUF_DBUF_RD_SHADOW_SEL_UNION;
#endif
#define SOC_DSS_DBUF_DBUF_RD_SHADOW_SEL_dbuf_rd_shadow_START  (0)
#define SOC_DSS_DBUF_DBUF_RD_SHADOW_SEL_dbuf_rd_shadow_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_DBUF_MEM_CTRL_UNION
 �ṹ˵��  : DBUF_MEM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0054����ֵ:0x00000000�����:32
 �Ĵ���˵��: MEM�͹��Ŀ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbuf_mem_ctrl : 4;  /* bit[0-3] : �����üĴ���
                                                        [3] mem_ctrl_auto_en , �Զ�ģʽ���������ģʽѡ��,0�Զ�ģʽ��1�������ģʽ 
                                                        [2]: �������ģʽ����Ч��Ϊ1��ʾ����Shut Downģʽ
                                                        [1]: �������ģʽ����Ч��Ϊ1��ʾ����Deep Sleepģʽ
                                                        [0]: �������ģʽ����Ч��Ϊ1��ʾ����Sleepģʽ */
        unsigned int  reserved      : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_DSS_DBUF_DBUF_MEM_CTRL_UNION;
#endif
#define SOC_DSS_DBUF_DBUF_MEM_CTRL_dbuf_mem_ctrl_START  (0)
#define SOC_DSS_DBUF_DBUF_MEM_CTRL_dbuf_mem_ctrl_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_DBUF_CLK_SEL_UNION
 �ṹ˵��  : DBUF_CLK_SEL �Ĵ����ṹ���塣��ַƫ����:0x005C����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: һ��ģ��ʱ��ѡ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbuf_clk_sel : 32; /* bit[0-31]: ��һ��ģ���ʱ��ѡ���źţ�
                                                       1����ʾǿ�ƴ�ʱ�ӡ�
                                                       0����ʾ��Ҫ���������Ӳ����ʱ��ʹ����������ر�ʱ��
                                                       bit0������apb��
                                                       bit1������reg��
                                                       bit2������dbuf_core��
                                                       bit3������dbuf_wb��
                                                       bit4������dbuf_pm��
                                                       bit5������dbuf_afifo */
    } reg;
} SOC_DSS_DBUF_DBUF_CLK_SEL_UNION;
#endif
#define SOC_DSS_DBUF_DBUF_CLK_SEL_dbuf_clk_sel_START  (0)
#define SOC_DSS_DBUF_DBUF_CLK_SEL_dbuf_clk_sel_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_DBUF_CLK_EN_UNION
 �ṹ˵��  : DBUF_CLK_EN �Ĵ����ṹ���塣��ַƫ����:0x0060����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: һ��ģ��ʱ��ʹ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbuf_clk_en : 32; /* bit[0-31]: ��һ��ģ������ʱ��ʹ���ź�
                                                      1����ʾ���ʱ��ʹ����Ч������Ӳ������
                                                      0����ʾ���ʱ��ʹ����Ч����ֹӲ������
                                                      bit0��������
                                                      bit1������reg��
                                                      bit2������dbuf_core��
                                                      bit3������dbuf_wb��
                                                      bit4������dbuf_pm��
                                                      bit5������dbuf_afifo */
    } reg;
} SOC_DSS_DBUF_DBUF_CLK_EN_UNION;
#endif
#define SOC_DSS_DBUF_DBUF_CLK_EN_dbuf_clk_en_START  (0)
#define SOC_DSS_DBUF_DBUF_CLK_EN_dbuf_clk_en_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_DBG_CPU_EN_UNION
 �ṹ˵��  : DBG_CPU_EN �Ĵ����ṹ���塣��ַƫ����:0x0070����ֵ:0x00000000�����:32
 �Ĵ���˵��: CPU��дmemoryʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_ctl  : 1;  /* bit[0]   : �����üĴ���
                                                   1��cpu����memory��дʹ�ܣ�
                                                   0��cpu����memory��д��ʹ�ܣ� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_DBUF_DBG_CPU_EN_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_EN_cpu_ctl_START   (0)
#define SOC_DSS_DBUF_DBG_CPU_EN_cpu_ctl_END     (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_DBG_CPU_START_UNION
 �ṹ˵��  : DBG_CPU_START �Ĵ����ṹ���塣��ַƫ����:0x0074����ֵ:0x00000000�����:32
 �Ĵ���˵��: SRAM�͹��Ŀ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_start : 1;  /* bit[0]   : cpu��дmemory��ַ�������� */
        unsigned int  reserved  : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_DBUF_DBG_CPU_START_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_START_cpu_start_START  (0)
#define SOC_DSS_DBUF_DBG_CPU_START_cpu_start_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_DBG_CPU_CTL_UNION
 �ṹ˵��  : DBG_CPU_CTL �Ĵ����ṹ���塣��ַƫ����:0x0078����ֵ:0x00000000�����:32
 �Ĵ���˵��: CPU����memory��д�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_addr : 13; /* bit[0-12] : cpu��дmemory��ַ�������� */
        unsigned int  reserved_0: 3;  /* bit[13-15]: ���� */
        unsigned int  cpu_we   : 1;  /* bit[16]   : 1��CPU д��0��CPU �� */
        unsigned int  reserved_1: 15; /* bit[17-31]: ���� */
    } reg;
} SOC_DSS_DBUF_DBG_CPU_CTL_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_CTL_cpu_addr_START  (0)
#define SOC_DSS_DBUF_DBG_CPU_CTL_cpu_addr_END    (12)
#define SOC_DSS_DBUF_DBG_CPU_CTL_cpu_we_START    (16)
#define SOC_DSS_DBUF_DBG_CPU_CTL_cpu_we_END      (16)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_DBG_CPU_RDATA0_UNION
 �ṹ˵��  : DBG_CPU_RDATA0 �Ĵ����ṹ���塣��ַƫ����:0x007C����ֵ:0x00000000�����:32
 �Ĵ���˵��: MEM������0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_rdata0 : 32; /* bit[0-31]: mem���˿ڣ������� */
    } reg;
} SOC_DSS_DBUF_DBG_CPU_RDATA0_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_RDATA0_cpu_rdata0_START  (0)
#define SOC_DSS_DBUF_DBG_CPU_RDATA0_cpu_rdata0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_DBG_CPU_RDATA1_UNION
 �ṹ˵��  : DBG_CPU_RDATA1 �Ĵ����ṹ���塣��ַƫ����:0x0080����ֵ:0x00000000�����:32
 �Ĵ���˵��: MEM������0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_rdata1 : 32; /* bit[0-31]: mem���˿ڣ������� */
    } reg;
} SOC_DSS_DBUF_DBG_CPU_RDATA1_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_RDATA1_cpu_rdata1_START  (0)
#define SOC_DSS_DBUF_DBG_CPU_RDATA1_cpu_rdata1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_DBG_CPU_RDATA2_UNION
 �ṹ˵��  : DBG_CPU_RDATA2 �Ĵ����ṹ���塣��ַƫ����:0x0084����ֵ:0x00000000�����:32
 �Ĵ���˵��: MEM������0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_rdata2 : 32; /* bit[0-31]: mem���˿ڣ������� */
    } reg;
} SOC_DSS_DBUF_DBG_CPU_RDATA2_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_RDATA2_cpu_rdata2_START  (0)
#define SOC_DSS_DBUF_DBG_CPU_RDATA2_cpu_rdata2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_DBG_CPU_RDATA3_UNION
 �ṹ˵��  : DBG_CPU_RDATA3 �Ĵ����ṹ���塣��ַƫ����:0x0088����ֵ:0x00000000�����:32
 �Ĵ���˵��: MEM������0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_rdata3 : 32; /* bit[0-31]: mem���˿ڣ������� */
    } reg;
} SOC_DSS_DBUF_DBG_CPU_RDATA3_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_RDATA3_cpu_rdata3_START  (0)
#define SOC_DSS_DBUF_DBG_CPU_RDATA3_cpu_rdata3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_DBG_CPU_RDATA4_UNION
 �ṹ˵��  : DBG_CPU_RDATA4 �Ĵ����ṹ���塣��ַƫ����:0x008C����ֵ:0x00000000�����:32
 �Ĵ���˵��: MEM������0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_rdata4 : 16; /* bit[0-15] : mem���˿ڣ������� */
        unsigned int  reserved   : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_DSS_DBUF_DBG_CPU_RDATA4_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_RDATA4_cpu_rdata4_START  (0)
#define SOC_DSS_DBUF_DBG_CPU_RDATA4_cpu_rdata4_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_DBG_CPU_WDATA0_UNION
 �ṹ˵��  : DBG_CPU_WDATA0 �Ĵ����ṹ���塣��ַƫ����:0x0090����ֵ:0x00000000�����:32
 �Ĵ���˵��: MEM������0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_wdata0 : 32; /* bit[0-31]: memд�˿ڣ������� */
    } reg;
} SOC_DSS_DBUF_DBG_CPU_WDATA0_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_WDATA0_cpu_wdata0_START  (0)
#define SOC_DSS_DBUF_DBG_CPU_WDATA0_cpu_wdata0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_DBG_CPU_WDATA1_UNION
 �ṹ˵��  : DBG_CPU_WDATA1 �Ĵ����ṹ���塣��ַƫ����:0x0094����ֵ:0x00000000�����:32
 �Ĵ���˵��: MEM������0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_wdata1 : 32; /* bit[0-31]: memд�˿ڣ������� */
    } reg;
} SOC_DSS_DBUF_DBG_CPU_WDATA1_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_WDATA1_cpu_wdata1_START  (0)
#define SOC_DSS_DBUF_DBG_CPU_WDATA1_cpu_wdata1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_DBG_CPU_WDATA2_UNION
 �ṹ˵��  : DBG_CPU_WDATA2 �Ĵ����ṹ���塣��ַƫ����:0x0098����ֵ:0x00000000�����:32
 �Ĵ���˵��: MEM������0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_wdata2 : 32; /* bit[0-31]: memд�˿ڣ������� */
    } reg;
} SOC_DSS_DBUF_DBG_CPU_WDATA2_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_WDATA2_cpu_wdata2_START  (0)
#define SOC_DSS_DBUF_DBG_CPU_WDATA2_cpu_wdata2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_DBG_CPU_WDATA3_UNION
 �ṹ˵��  : DBG_CPU_WDATA3 �Ĵ����ṹ���塣��ַƫ����:0x009C����ֵ:0x00000000�����:32
 �Ĵ���˵��: MEM������0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_wdata3 : 32; /* bit[0-31]: memд�˿ڣ������� */
    } reg;
} SOC_DSS_DBUF_DBG_CPU_WDATA3_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_WDATA3_cpu_wdata3_START  (0)
#define SOC_DSS_DBUF_DBG_CPU_WDATA3_cpu_wdata3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_DBG_CPU_WDATA4_UNION
 �ṹ˵��  : DBG_CPU_WDATA4 �Ĵ����ṹ���塣��ַƫ����:0x00A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: MEM������0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_wdata4 : 16; /* bit[0-15] : memд�˿ڣ������� */
        unsigned int  reserved   : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_DSS_DBUF_DBG_CPU_WDATA4_UNION;
#endif
#define SOC_DSS_DBUF_DBG_CPU_WDATA4_cpu_wdata4_START  (0)
#define SOC_DSS_DBUF_DBG_CPU_WDATA4_cpu_wdata4_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUF_REG_DEFAULT_UNION
 �ṹ˵��  : REG_DEFAULT �Ĵ����ṹ���塣��ַƫ����:0x00A4����ֵ:0x00000000�����:32
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
} SOC_DSS_DBUF_REG_DEFAULT_UNION;
#endif
#define SOC_DSS_DBUF_REG_DEFAULT_reg_default_START  (0)
#define SOC_DSS_DBUF_REG_DEFAULT_reg_default_END    (0)






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

#endif /* end of soc_dss_dbuf_interface.h */
