/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_dss_dbug_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:20:01
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_DSS_DBUG.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_DSS_DBUG_INTERFACE_H__
#define __SOC_DSS_DBUG_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_DBUG
 ****************************************************************************/
/* �Ĵ���˵����OV0��crcУ����
   λ����UNION�ṹ:  SOC_DSS_DBUG_CRC_DBG_OV0_UNION */
#define SOC_DSS_DBUG_CRC_DBG_OV0_ADDR(base)           ((base) + (0x0000))

/* �Ĵ���˵����OV1��crcУ����
   λ����UNION�ṹ:  SOC_DSS_DBUG_CRC_DBG_OV1_UNION */
#define SOC_DSS_DBUG_CRC_DBG_OV1_ADDR(base)           ((base) + (0x0004))

/* �Ĵ���˵����SUM��crcУ����
   λ����UNION�ṹ:  SOC_DSS_DBUG_CRC_DBG_SUM_UNION */
#define SOC_DSS_DBUG_CRC_DBG_SUM_ADDR(base)           ((base) + (0x0008))

/* �Ĵ���˵����OV0��CRC����ʹ���ź�
   λ����UNION�ṹ:  SOC_DSS_DBUG_CRC_OV0_EN_UNION */
#define SOC_DSS_DBUG_CRC_OV0_EN_ADDR(base)            ((base) + (0x000C))

/* �Ĵ���˵���������ȡOV0��CRC����ź�
   λ����UNION�ṹ:  SOC_DSS_DBUG_DSS_GLB_DBG_O_UNION */
#define SOC_DSS_DBUG_DSS_GLB_DBG_O_ADDR(base)         ((base) + (0x0010))

/* �Ĵ���˵����OV0��crcУ�����Ƿ�ɶ�
   λ����UNION�ṹ:  SOC_DSS_DBUG_DSS_GLB_DBG_I_UNION */
#define SOC_DSS_DBUG_DSS_GLB_DBG_I_ADDR(base)         ((base) + (0x0014))

/* �Ĵ���˵����OV0�ϱ���CRCУ���֡��
   λ����UNION�ṹ:  SOC_DSS_DBUG_CRC_OV0_FRM_UNION */
#define SOC_DSS_DBUG_CRC_OV0_FRM_ADDR(base)           ((base) + (0x0018))

/* �Ĵ���˵����OV1��CRC����ʹ���ź�
   λ����UNION�ṹ:  SOC_DSS_DBUG_CRC_OV1_EN_UNION */
#define SOC_DSS_DBUG_CRC_OV1_EN_ADDR(base)            ((base) + (0x001C))

/* �Ĵ���˵����OV1�ϱ���CRCУ���֡��
   λ����UNION�ṹ:  SOC_DSS_DBUG_CRC_OV1_FRM_UNION */
#define SOC_DSS_DBUG_CRC_OV1_FRM_ADDR(base)           ((base) + (0x0020))

/* �Ĵ���˵����SUM��CRC����ʹ���ź�
   λ����UNION�ṹ:  SOC_DSS_DBUG_CRC_SUM_EN_UNION */
#define SOC_DSS_DBUG_CRC_SUM_EN_ADDR(base)            ((base) + (0x0024))

/* �Ĵ���˵����SUM�ϱ���CRCУ���֡��
   λ����UNION�ṹ:  SOC_DSS_DBUG_CRC_SUM_FRM_UNION */
#define SOC_DSS_DBUG_CRC_SUM_FRM_ADDR(base)           ((base) + (0x0028))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DBUG_REG2CTRL_LBS_EN_UNION */
#define SOC_DSS_DBUG_REG2CTRL_LBS_EN_ADDR(base)       ((base) + (0x0100))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DBUG_REG2LBS_LBS_FRM_LEN_UNION */
#define SOC_DSS_DBUG_REG2LBS_LBS_FRM_LEN_ADDR(base)   ((base) + (0x0104))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DBUG_DBG_BUS_MODE_UNION */
#define SOC_DSS_DBUG_DBG_BUS_MODE_ADDR(base)          ((base) + (0x0108))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DBUG_REG2LBS_LBS_FRM_UNION */
#define SOC_DSS_DBUG_REG2LBS_LBS_FRM_ADDR(base)       ((base) + (0x010C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DBUG_REG2LBS_LBS_ID_UNION */
#define SOC_DSS_DBUG_REG2LBS_LBS_ID_ADDR(base)        ((base) + (0x0110))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DBUG_REG2LBS_BUS_MSK_UNION */
#define SOC_DSS_DBUG_REG2LBS_BUS_MSK_ADDR(base)       ((base) + (0x0114))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DBUG_REG2HEAD_DIAG_ID_UNION */
#define SOC_DSS_DBUG_REG2HEAD_DIAG_ID_ADDR(base)      ((base) + (0x0118))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DBUG_REG2HEAD_HSRV_ID_UNION */
#define SOC_DSS_DBUG_REG2HEAD_HSRV_ID_ADDR(base)      ((base) + (0x011C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DBUG_REG2HEAD_LSRV_ID_UNION */
#define SOC_DSS_DBUG_REG2HEAD_LSRV_ID_ADDR(base)      ((base) + (0x0120))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DBUG_REG2HEAD_SESSION_ID_UNION */
#define SOC_DSS_DBUG_REG2HEAD_SESSION_ID_ADDR(base)   ((base) + (0x0124))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DBUG_REG2HEAD_MSG_TYPE_UNION */
#define SOC_DSS_DBUG_REG2HEAD_MSG_TYPE_ADDR(base)     ((base) + (0x0128))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DBUG_DBG_BUS_BASE_ADDR_UNION */
#define SOC_DSS_DBUG_DBG_BUS_BASE_ADDR_ADDR(base)     ((base) + (0x012C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DBUG_DBG_BUS_END_ADDR_UNION */
#define SOC_DSS_DBUG_DBG_BUS_END_ADDR_ADDR(base)      ((base) + (0x0130))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DBUG_DBG_PTR_ADDR_UNION */
#define SOC_DSS_DBUG_DBG_PTR_ADDR_ADDR(base)          ((base) + (0x0134))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DBUG_DBG_BUS_TIMING_UNION */
#define SOC_DSS_DBUG_DBG_BUS_TIMING_ADDR(base)        ((base) + (0x0138))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DBUG_DBG_BUS_LDI_SEL_UNION */
#define SOC_DSS_DBUG_DBG_BUS_LDI_SEL_ADDR(base)       ((base) + (0x013C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DBUG_DBG_BUS_END_UNION */
#define SOC_DSS_DBUG_DBG_BUS_END_ADDR(base)           ((base) + (0x0140))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DBUG_REG2MEM_GATE_SEL_UNION */
#define SOC_DSS_DBUG_REG2MEM_GATE_SEL_ADDR(base)      ((base) + (0x0144))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DBUG_SP_MEM_CTRL0_LOG_UNION */
#define SOC_DSS_DBUG_SP_MEM_CTRL0_LOG_ADDR(base)      ((base) + (0x0148))

/* �Ĵ���˵����MEM�͹��Ŀ��ƼĴ�����TP��
   λ����UNION�ṹ:  SOC_DSS_DBUG_TP_MEM_CTRL0_UNION */
#define SOC_DSS_DBUG_TP_MEM_CTRL0_ADDR(base)          ((base) + (0x014C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DBUG_DBG_BUS_TIMING_SEL_UNION */
#define SOC_DSS_DBUG_DBG_BUS_TIMING_SEL_ADDR(base)    ((base) + (0x0150))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_DBUG_DSS_DBG_WPTR_UNION */
#define SOC_DSS_DBUG_DSS_DBG_WPTR_ADDR(base)          ((base) + (0x0154))





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
                     (1/1) reg_DBUG
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUG_CRC_DBG_OV0_UNION
 �ṹ˵��  : CRC_DBG_OV0 �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: OV0��crcУ����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_dbg_ov0 : 32; /* bit[0-31]: OV0��crcУ���� */
    } reg;
} SOC_DSS_DBUG_CRC_DBG_OV0_UNION;
#endif
#define SOC_DSS_DBUG_CRC_DBG_OV0_crc_dbg_ov0_START  (0)
#define SOC_DSS_DBUG_CRC_DBG_OV0_crc_dbg_ov0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUG_CRC_DBG_OV1_UNION
 �ṹ˵��  : CRC_DBG_OV1 �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: OV1��crcУ����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_dbg_ov1 : 32; /* bit[0-31]: OV1��crcУ���� */
    } reg;
} SOC_DSS_DBUG_CRC_DBG_OV1_UNION;
#endif
#define SOC_DSS_DBUG_CRC_DBG_OV1_crc_dbg_ov1_START  (0)
#define SOC_DSS_DBUG_CRC_DBG_OV1_crc_dbg_ov1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUG_CRC_DBG_SUM_UNION
 �ṹ˵��  : CRC_DBG_SUM �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: SUM��crcУ����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_dbg_sum : 32; /* bit[0-31]: ���� */
    } reg;
} SOC_DSS_DBUG_CRC_DBG_SUM_UNION;
#endif
#define SOC_DSS_DBUG_CRC_DBG_SUM_crc_dbg_sum_START  (0)
#define SOC_DSS_DBUG_CRC_DBG_SUM_crc_dbg_sum_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUG_CRC_OV0_EN_UNION
 �ṹ˵��  : CRC_OV0_EN �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: OV0��CRC����ʹ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_ov0_en : 1;  /* bit[0-0] : OV0��crcУ��ʹ�� */
        unsigned int  reserved   : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_DBUG_CRC_OV0_EN_UNION;
#endif
#define SOC_DSS_DBUG_CRC_OV0_EN_crc_ov0_en_START  (0)
#define SOC_DSS_DBUG_CRC_OV0_EN_crc_ov0_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUG_DSS_GLB_DBG_O_UNION
 �ṹ˵��  : DSS_GLB_DBG_O �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����ȡOV0��CRC����ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dss_glb_dbg_o : 32; /* bit[0-31]: ���� */
    } reg;
} SOC_DSS_DBUG_DSS_GLB_DBG_O_UNION;
#endif
#define SOC_DSS_DBUG_DSS_GLB_DBG_O_dss_glb_dbg_o_START  (0)
#define SOC_DSS_DBUG_DSS_GLB_DBG_O_dss_glb_dbg_o_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUG_DSS_GLB_DBG_I_UNION
 �ṹ˵��  : DSS_GLB_DBG_I �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: OV0��crcУ�����Ƿ�ɶ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dss_glb_dbg_i : 32; /* bit[0-31]: ���� */
    } reg;
} SOC_DSS_DBUG_DSS_GLB_DBG_I_UNION;
#endif
#define SOC_DSS_DBUG_DSS_GLB_DBG_I_dss_glb_dbg_i_START  (0)
#define SOC_DSS_DBUG_DSS_GLB_DBG_I_dss_glb_dbg_i_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUG_CRC_OV0_FRM_UNION
 �ṹ˵��  : CRC_OV0_FRM �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: OV0�ϱ���CRCУ���֡��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_ov0_frm : 32; /* bit[0-31]: OV0�ϱ���CRCУ���֡�� */
    } reg;
} SOC_DSS_DBUG_CRC_OV0_FRM_UNION;
#endif
#define SOC_DSS_DBUG_CRC_OV0_FRM_crc_ov0_frm_START  (0)
#define SOC_DSS_DBUG_CRC_OV0_FRM_crc_ov0_frm_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUG_CRC_OV1_EN_UNION
 �ṹ˵��  : CRC_OV1_EN �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000000�����:32
 �Ĵ���˵��: OV1��CRC����ʹ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_ov1_en : 1;  /* bit[0-0] : OV1��CRC����ʹ���ź� */
        unsigned int  reserved   : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_DBUG_CRC_OV1_EN_UNION;
#endif
#define SOC_DSS_DBUG_CRC_OV1_EN_crc_ov1_en_START  (0)
#define SOC_DSS_DBUG_CRC_OV1_EN_crc_ov1_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUG_CRC_OV1_FRM_UNION
 �ṹ˵��  : CRC_OV1_FRM �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: OV1�ϱ���CRCУ���֡��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_ov1_frm : 32; /* bit[0-31]: OV1�ϱ���CRCУ���֡�� */
    } reg;
} SOC_DSS_DBUG_CRC_OV1_FRM_UNION;
#endif
#define SOC_DSS_DBUG_CRC_OV1_FRM_crc_ov1_frm_START  (0)
#define SOC_DSS_DBUG_CRC_OV1_FRM_crc_ov1_frm_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUG_CRC_SUM_EN_UNION
 �ṹ˵��  : CRC_SUM_EN �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x00000000�����:32
 �Ĵ���˵��: SUM��CRC����ʹ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_sum_en : 1;  /* bit[0-0] : SUM��CRC����ʹ���ź� */
        unsigned int  reserved   : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_DBUG_CRC_SUM_EN_UNION;
#endif
#define SOC_DSS_DBUG_CRC_SUM_EN_crc_sum_en_START  (0)
#define SOC_DSS_DBUG_CRC_SUM_EN_crc_sum_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUG_CRC_SUM_FRM_UNION
 �ṹ˵��  : CRC_SUM_FRM �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x00000000�����:32
 �Ĵ���˵��: SUM�ϱ���CRCУ���֡��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_sum_frm : 32; /* bit[0-31]: SUM�ϱ���CRCУ���֡�� */
    } reg;
} SOC_DSS_DBUG_CRC_SUM_FRM_UNION;
#endif
#define SOC_DSS_DBUG_CRC_SUM_FRM_crc_sum_frm_START  (0)
#define SOC_DSS_DBUG_CRC_SUM_FRM_crc_sum_frm_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUG_REG2CTRL_LBS_EN_UNION
 �ṹ˵��  : REG2CTRL_LBS_EN �Ĵ����ṹ���塣��ַƫ����:0x0100����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg2ctrl_lbs_en : 1;  /* bit[0-0] : ����ʹ���ź� */
        unsigned int  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_DBUG_REG2CTRL_LBS_EN_UNION;
#endif
#define SOC_DSS_DBUG_REG2CTRL_LBS_EN_reg2ctrl_lbs_en_START  (0)
#define SOC_DSS_DBUG_REG2CTRL_LBS_EN_reg2ctrl_lbs_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUG_REG2LBS_LBS_FRM_LEN_UNION
 �ṹ˵��  : REG2LBS_LBS_FRM_LEN �Ĵ����ṹ���塣��ַƫ����:0x0104����ֵ:0x00000800�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg2lbs_lbs_frm_len : 16; /* bit[0-15] : Bus�ɼ�����֡������ֵ������������burst8�ı�������λbyte������ֵ2048 */
        unsigned int  reserved            : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_DSS_DBUG_REG2LBS_LBS_FRM_LEN_UNION;
#endif
#define SOC_DSS_DBUG_REG2LBS_LBS_FRM_LEN_reg2lbs_lbs_frm_len_START  (0)
#define SOC_DSS_DBUG_REG2LBS_LBS_FRM_LEN_reg2lbs_lbs_frm_len_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUG_DBG_BUS_MODE_UNION
 �ṹ˵��  : DBG_BUS_MODE �Ĵ����ṹ���塣��ַƫ����:0x0108����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_bus_mode : 1;  /* bit[0-0] : Bus�ɼ�ģʽѡ���źš�
                                                       0������ģʽ�������ֵ���ʹ�ã�
                                                       1������ģʽ */
        unsigned int  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_DBUG_DBG_BUS_MODE_UNION;
#endif
#define SOC_DSS_DBUG_DBG_BUS_MODE_dbg_bus_mode_START  (0)
#define SOC_DSS_DBUG_DBG_BUS_MODE_dbg_bus_mode_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUG_REG2LBS_LBS_FRM_UNION
 �ṹ˵��  : REG2LBS_LBS_FRM �Ĵ����ṹ���塣��ַƫ����:0x010C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg2lbs_lbs_frm : 16; /* bit[0-15] : ����ģʽ��Bus�ɼ�֡���� */
        unsigned int  reserved        : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_DSS_DBUG_REG2LBS_LBS_FRM_UNION;
#endif
#define SOC_DSS_DBUG_REG2LBS_LBS_FRM_reg2lbs_lbs_frm_START  (0)
#define SOC_DSS_DBUG_REG2LBS_LBS_FRM_reg2lbs_lbs_frm_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUG_REG2LBS_LBS_ID_UNION
 �ṹ˵��  : REG2LBS_LBS_ID �Ĵ����ṹ���塣��ַƫ����:0x0110����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg2lbs_lbs_id : 32; /* bit[0-31]: Bus�ɼ�����֡ID��ʶ */
    } reg;
} SOC_DSS_DBUG_REG2LBS_LBS_ID_UNION;
#endif
#define SOC_DSS_DBUG_REG2LBS_LBS_ID_reg2lbs_lbs_id_START  (0)
#define SOC_DSS_DBUG_REG2LBS_LBS_ID_reg2lbs_lbs_id_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUG_REG2LBS_BUS_MSK_UNION
 �ṹ˵��  : REG2LBS_BUS_MSK �Ĵ����ṹ���塣��ַƫ����:0x0114����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg2lbs_bus_msk : 2;  /* bit[0-1] : ��д���ݲɼ������źš�
                                                          0��ʹ�ܲɼ���1�����βɼ�
                                                          bit0����������
                                                          bit1��д������ */
        unsigned int  reserved        : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_DSS_DBUG_REG2LBS_BUS_MSK_UNION;
#endif
#define SOC_DSS_DBUG_REG2LBS_BUS_MSK_reg2lbs_bus_msk_START  (0)
#define SOC_DSS_DBUG_REG2LBS_BUS_MSK_reg2lbs_bus_msk_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUG_REG2HEAD_DIAG_ID_UNION
 �ṹ˵��  : REG2HEAD_DIAG_ID �Ĵ����ṹ���塣��ַƫ����:0x0118����ֵ:0x48495349�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg2head_diag_id : 32; /* bit[0-31]: ֡ͷ��ϱ�ʶ��ȱʡֵ=0x48495349 */
    } reg;
} SOC_DSS_DBUG_REG2HEAD_DIAG_ID_UNION;
#endif
#define SOC_DSS_DBUG_REG2HEAD_DIAG_ID_reg2head_diag_id_START  (0)
#define SOC_DSS_DBUG_REG2HEAD_DIAG_ID_reg2head_diag_id_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUG_REG2HEAD_HSRV_ID_UNION
 �ṹ˵��  : REG2HEAD_HSRV_ID �Ĵ����ṹ���塣��ַƫ����:0x011C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg2head_hsrv_id : 8;  /* bit[0-7] : Service ID��SIDָʾ�� */
        unsigned int  reserved         : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_DSS_DBUG_REG2HEAD_HSRV_ID_UNION;
#endif
#define SOC_DSS_DBUG_REG2HEAD_HSRV_ID_reg2head_hsrv_id_START  (0)
#define SOC_DSS_DBUG_REG2HEAD_HSRV_ID_reg2head_hsrv_id_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUG_REG2HEAD_LSRV_ID_UNION
 �ṹ˵��  : REG2HEAD_LSRV_ID �Ĵ����ṹ���塣��ַƫ����:0x0120����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg2head_lsrv_id : 4;  /* bit[0-3] : Service ID��SSIDָʾ�� */
        unsigned int  reserved         : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_DSS_DBUG_REG2HEAD_LSRV_ID_UNION;
#endif
#define SOC_DSS_DBUG_REG2HEAD_LSRV_ID_reg2head_lsrv_id_START  (0)
#define SOC_DSS_DBUG_REG2HEAD_LSRV_ID_reg2head_lsrv_id_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUG_REG2HEAD_SESSION_ID_UNION
 �ṹ˵��  : REG2HEAD_SESSION_ID �Ĵ����ṹ���塣��ַƫ����:0x0124����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg2head_session_id : 8;  /* bit[0-7] : Session IDָʾ�� */
        unsigned int  reserved            : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_DSS_DBUG_REG2HEAD_SESSION_ID_UNION;
#endif
#define SOC_DSS_DBUG_REG2HEAD_SESSION_ID_reg2head_session_id_START  (0)
#define SOC_DSS_DBUG_REG2HEAD_SESSION_ID_reg2head_session_id_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUG_REG2HEAD_MSG_TYPE_UNION
 �ṹ˵��  : REG2HEAD_MSG_TYPE �Ĵ����ṹ���塣��ַƫ����:0x0128����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg2head_msg_type : 8;  /* bit[0-7] : Message type��Ϣ����ָʾ�� */
        unsigned int  reserved          : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_DSS_DBUG_REG2HEAD_MSG_TYPE_UNION;
#endif
#define SOC_DSS_DBUG_REG2HEAD_MSG_TYPE_reg2head_msg_type_START  (0)
#define SOC_DSS_DBUG_REG2HEAD_MSG_TYPE_reg2head_msg_type_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUG_DBG_BUS_BASE_ADDR_UNION
 �ṹ˵��  : DBG_BUS_BASE_ADDR �Ĵ����ṹ���塣��ַƫ����:0x012C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved          : 4;  /* bit[0-3] :  */
        unsigned int  dbg_bus_base_addr : 28; /* bit[4-31]: ��������bus������ddr�еĻ���ַ��128bit���롣 */
    } reg;
} SOC_DSS_DBUG_DBG_BUS_BASE_ADDR_UNION;
#endif
#define SOC_DSS_DBUG_DBG_BUS_BASE_ADDR_dbg_bus_base_addr_START  (4)
#define SOC_DSS_DBUG_DBG_BUS_BASE_ADDR_dbg_bus_base_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUG_DBG_BUS_END_ADDR_UNION
 �ṹ˵��  : DBG_BUS_END_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0130����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved         : 4;  /* bit[0-3] :  */
        unsigned int  dbg_bus_end_addr : 28; /* bit[4-31]: ��������bus������ddr�е�β��ַ��128bit���롣���Ҫ������Ϊ2048B�ı��� */
    } reg;
} SOC_DSS_DBUG_DBG_BUS_END_ADDR_UNION;
#endif
#define SOC_DSS_DBUG_DBG_BUS_END_ADDR_dbg_bus_end_addr_START  (4)
#define SOC_DSS_DBUG_DBG_BUS_END_ADDR_dbg_bus_end_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUG_DBG_PTR_ADDR_UNION
 �ṹ˵��  : DBG_PTR_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0134����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved     : 4;  /* bit[0-3] :  */
        unsigned int  dbg_ptr_addr : 28; /* bit[4-31]: ��ά�ɲ�ͨ��bufferдָ����ʼ��ַ�����bus����дָ�롣 */
    } reg;
} SOC_DSS_DBUG_DBG_PTR_ADDR_UNION;
#endif
#define SOC_DSS_DBUG_DBG_PTR_ADDR_dbg_ptr_addr_START  (4)
#define SOC_DSS_DBUG_DBG_PTR_ADDR_dbg_ptr_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUG_DBG_BUS_TIMING_UNION
 �ṹ˵��  : DBG_BUS_TIMING �Ĵ����ṹ���塣��ַƫ����:0x0138����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_bus_timing : 32; /* bit[0-31]: ֡��ʱ������ֵ���ڲ��������ﵽ��ֵʱ��ʾһ֡ */
    } reg;
} SOC_DSS_DBUG_DBG_BUS_TIMING_UNION;
#endif
#define SOC_DSS_DBUG_DBG_BUS_TIMING_dbg_bus_timing_START  (0)
#define SOC_DSS_DBUG_DBG_BUS_TIMING_dbg_bus_timing_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUG_DBG_BUS_LDI_SEL_UNION
 �ṹ˵��  : DBG_BUS_LDI_SEL �Ĵ����ṹ���塣��ַƫ����:0x013C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_bus_ldi_sel : 1;  /* bit[0-0] :  */
        unsigned int  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_DBUG_DBG_BUS_LDI_SEL_UNION;
#endif
#define SOC_DSS_DBUG_DBG_BUS_LDI_SEL_dbg_bus_ldi_sel_START  (0)
#define SOC_DSS_DBUG_DBG_BUS_LDI_SEL_dbg_bus_ldi_sel_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUG_DBG_BUS_END_UNION
 �ṹ˵��  : DBG_BUS_END �Ĵ����ṹ���塣��ַƫ����:0x0140����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_bus_end : 1;  /* bit[0]   : ���� */
        unsigned int  reserved    : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_DBUG_DBG_BUS_END_UNION;
#endif
#define SOC_DSS_DBUG_DBG_BUS_END_dbg_bus_end_START  (0)
#define SOC_DSS_DBUG_DBG_BUS_END_dbg_bus_end_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUG_REG2MEM_GATE_SEL_UNION
 �ṹ˵��  : REG2MEM_GATE_SEL �Ĵ����ṹ���塣��ַƫ����:0x0144����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg2mem_gate_sel : 1;  /* bit[0-0] : Ram��ʱ���ſ�ѡ���źš�
                                                           0��ʱ���ſ�ʹ�ܣ�1��ʱ���ſز�ʹ�� */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_DBUG_REG2MEM_GATE_SEL_UNION;
#endif
#define SOC_DSS_DBUG_REG2MEM_GATE_SEL_reg2mem_gate_sel_START  (0)
#define SOC_DSS_DBUG_REG2MEM_GATE_SEL_reg2mem_gate_sel_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUG_SP_MEM_CTRL0_LOG_UNION
 �ṹ˵��  : SP_MEM_CTRL0_LOG �Ĵ����ṹ���塣��ַƫ����:0x0148����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sp_mem_ctrl0_log : 4;  /* bit[0-3] : �����üĴ�����
                                                           [3]: reseverd; 
                                                           [2]: �������ģʽ����Ч��Ϊ1��ʾ����Shut Downģʽ
                                                           [1]: �������ģʽ����Ч��Ϊ1��ʾ����Deep Sleepģʽ
                                                           [0]: �������ģʽ����Ч��Ϊ1��ʾ����Sleepģʽ */
        unsigned int  reserved         : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_DSS_DBUG_SP_MEM_CTRL0_LOG_UNION;
#endif
#define SOC_DSS_DBUG_SP_MEM_CTRL0_LOG_sp_mem_ctrl0_log_START  (0)
#define SOC_DSS_DBUG_SP_MEM_CTRL0_LOG_sp_mem_ctrl0_log_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUG_TP_MEM_CTRL0_UNION
 �ṹ˵��  : TP_MEM_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x014C����ֵ:0x00000000�����:32
 �Ĵ���˵��: MEM�͹��Ŀ��ƼĴ�����TP��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tp_mem_ctrl0 : 4;  /* bit[0-3] : �����üĴ�����
                                                       [3]: reseverd; 
                                                       [2]: �������ģʽ����Ч��Ϊ1��ʾ����Shut Downģʽ
                                                       [1]: �������ģʽ����Ч��Ϊ1��ʾ����Deep Sleepģʽ
                                                       [0]: �������ģʽ����Ч��Ϊ1��ʾ����Sleepģʽ */
        unsigned int  reserved     : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_DSS_DBUG_TP_MEM_CTRL0_UNION;
#endif
#define SOC_DSS_DBUG_TP_MEM_CTRL0_tp_mem_ctrl0_START  (0)
#define SOC_DSS_DBUG_TP_MEM_CTRL0_tp_mem_ctrl0_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUG_DBG_BUS_TIMING_SEL_UNION
 �ṹ˵��  : DBG_BUS_TIMING_SEL �Ĵ����ṹ���塣��ַƫ����:0x0150����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_bus_timing_sel : 1;  /* bit[0-0] : �������֡����ģʽ��
                                                             0��ѡ�����õ�֡�ڼ�����1��ѡ��ldiΪ֡���� */
        unsigned int  reserved           : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_DBUG_DBG_BUS_TIMING_SEL_UNION;
#endif
#define SOC_DSS_DBUG_DBG_BUS_TIMING_SEL_dbg_bus_timing_sel_START  (0)
#define SOC_DSS_DBUG_DBG_BUS_TIMING_SEL_dbg_bus_timing_sel_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_DBUG_DSS_DBG_WPTR_UNION
 �ṹ˵��  : DSS_DBG_WPTR �Ĵ����ṹ���塣��ַƫ����:0x0154����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dss_dbg_wptr : 32; /* bit[0-31]: ÿ֡dbg�����ϱ���ǰд��ddr�ĵ�ַ���ֽ�Ϊ��λ�� */
    } reg;
} SOC_DSS_DBUG_DSS_DBG_WPTR_UNION;
#endif
#define SOC_DSS_DBUG_DSS_DBG_WPTR_dss_dbg_wptr_START  (0)
#define SOC_DSS_DBUG_DSS_DBG_WPTR_dss_dbg_wptr_END    (31)






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

#endif /* end of soc_dss_dbug_interface.h */
