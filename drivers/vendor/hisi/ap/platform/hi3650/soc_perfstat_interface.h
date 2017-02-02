/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_perfstat_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:22:26
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_PERFSTAT.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_PERFSTAT_INTERFACE_H__
#define __SOC_PERFSTAT_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) register_PERF_STAT
 ****************************************************************************/
/* �Ĵ���˵����ʱ��gate�Ĵ���
   λ����UNION�ṹ:  SOC_PERFSTAT_CLK_GATE_UNION */
#define SOC_PERFSTAT_CLK_GATE_ADDR(base)              ((base) + (0x00))

/* �Ĵ���˵���������Ĵ�����
   λ����UNION�ṹ:  SOC_PERFSTAT_CMD_START_UNION */
#define SOC_PERFSTAT_CMD_START_ADDR(base)             ((base) + (0x04))

/* �Ĵ���˵��������ͳ�����ڼĴ�����
   λ����UNION�ṹ:  SOC_PERFSTAT_SAMPLE_CNT_REG_UNION */
#define SOC_PERFSTAT_SAMPLE_CNT_REG_ADDR(base)        ((base) + (0x08))

/* �Ĵ���˵�������������Ĵ�����
   λ����UNION�ṹ:  SOC_PERFSTAT_SAMPLE_NUM_REG_UNION */
#define SOC_PERFSTAT_SAMPLE_NUM_REG_ADDR(base)        ((base) + (0x0C))

/* �Ĵ���˵��������ֹͣ�Ĵ���
   λ����UNION�ṹ:  SOC_PERFSTAT_SAMPLE_STOP_UNION */
#define SOC_PERFSTAT_SAMPLE_STOP_ADDR(base)           ((base) + (0x10))

/* �Ĵ���˵������ض˿ڸ����Ĵ�����
   λ����UNION�ṹ:  SOC_PERFSTAT_REAL_PORT_NUM_UNION */
#define SOC_PERFSTAT_REAL_PORT_NUM_ADDR(base)         ((base) + (0x14))

/* �Ĵ���˵������ַģʽ�Ĵ���
   λ����UNION�ṹ:  SOC_PERFSTAT_AXI_ADDR_MODE_UNION */
#define SOC_PERFSTAT_AXI_ADDR_MODE_ADDR(base)         ((base) + (0x18))

/* �Ĵ���˵��������ģʽд��ַ�Ĵ�����
   λ����UNION�ṹ:  SOC_PERFSTAT_SEQ_ADDR_UNION */
#define SOC_PERFSTAT_SEQ_ADDR_ADDR(base)              ((base) + (0x1C))

/* �Ĵ���˵��������ģʽд��ַ����Ĵ�����
   λ����UNION�ṹ:  SOC_PERFSTAT_SEQ_ADDR_LEN_UNION */
#define SOC_PERFSTAT_SEQ_ADDR_LEN_ADDR(base)          ((base) + (0x20))

/* �Ĵ���˵���������ַ
   λ����UNION�ṹ:  SOC_PERFSTAT_DESCRIPTOR_ADDR_UNION */
#define SOC_PERFSTAT_DESCRIPTOR_ADDR_ADDR(base)       ((base) + (0x24))

/* �Ĵ���˵������ǰ�����ַ�Ĵ���
   λ����UNION�ṹ:  SOC_PERFSTAT_LAST_DESC_ADDR_UNION */
#define SOC_PERFSTAT_LAST_DESC_ADDR_ADDR(base)        ((base) + (0x28))

/* �Ĵ���˵������λ������Ĵ���
   λ����UNION�ṹ:  SOC_PERFSTAT_STAT_RST_CNT_UNION */
#define SOC_PERFSTAT_STAT_RST_CNT_ADDR(base)          ((base) + (0x2C))

/* �Ĵ���˵����ST�ж����ο��ƼĴ���
   λ����UNION�ṹ:  SOC_PERFSTAT_INT_EN_UNION */
#define SOC_PERFSTAT_INT_EN_ADDR(base)                ((base) + (0x30))

/* �Ĵ���˵����ST�ж�����Ĵ���
   λ����UNION�ṹ:  SOC_PERFSTAT_INT_CLR_UNION */
#define SOC_PERFSTAT_INT_CLR_ADDR(base)               ((base) + (0x34))

/* �Ĵ���˵����STԭʼ�ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_PERFSTAT_RAW_INT_STAT_UNION */
#define SOC_PERFSTAT_RAW_INT_STAT_ADDR(base)          ((base) + (0x38))

/* �Ĵ���˵����ST���κ��ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_PERFSTAT_MASK_INT_STAT_UNION */
#define SOC_PERFSTAT_MASK_INT_STAT_ADDR(base)         ((base) + (0x3C))

/* �Ĵ���˵�����ܲ��������Ĵ���
   λ����UNION�ṹ:  SOC_PERFSTAT_ALL_SAMPLE_NUM_UNION */
#define SOC_PERFSTAT_ALL_SAMPLE_NUM_ADDR(base)        ((base) + (0x40))

/* �Ĵ���˵����������ַ�Ĵ���
   λ����UNION�ṹ:  SOC_PERFSTAT_LAST_SAMPLE_AXI_ADDR_UNION */
#define SOC_PERFSTAT_LAST_SAMPLE_AXI_ADDR_ADDR(base)  ((base) + (0x44))

/* �Ĵ���˵������ʱ������
   λ����UNION�ṹ:  SOC_PERFSTAT_OVERTIME_CFG_CNT_UNION */
#define SOC_PERFSTAT_OVERTIME_CFG_CNT_ADDR(base)      ((base) + (0x48))

/* �Ĵ���˵������ѯfifo��״̬�Ĵ���
   λ����UNION�ṹ:  SOC_PERFSTAT_DEBUG_FIFO_FULL_UNION */
#define SOC_PERFSTAT_DEBUG_FIFO_FULL_ADDR(base)       ((base) + (0x4C))

/* �Ĵ���˵������ѯmonitor�����Ĵ���
   λ����UNION�ṹ:  SOC_PERFSTAT_DEBUG_MONITOR_UNION */
#define SOC_PERFSTAT_DEBUG_MONITOR_ADDR(base)         ((base) + (0x50))

/* �Ĵ���˵����monitor��λ�Ĵ���
   λ����UNION�ṹ:  SOC_PERFSTAT_MONITOR_RESET_UNION */
#define SOC_PERFSTAT_MONITOR_RESET_ADDR(base)         ((base) + (0x54))





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
                     (1/1) register_PERF_STAT
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_PERFSTAT_CLK_GATE_UNION
 �ṹ˵��  : CLK_GATE �Ĵ����ṹ���塣��ַƫ����:0x00����ֵ:0x0000�����:32
 �Ĵ���˵��: ʱ��gate�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apb_clk_gate : 1;  /* bit[0]   : ʱ��gate��������real_port_numΪ0xffff���ڲ���δ����ʱʹ�ã�gating��Ч�󣬲��ɻָ���
                                                       gating����Զ��monitor����axiʱ�ӡ�
                                                       0��ʱ��gate��Ч��
                                                       1��ʱ��gate��Ч�� */
        unsigned int  reserved     : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PERFSTAT_CLK_GATE_UNION;
#endif
#define SOC_PERFSTAT_CLK_GATE_apb_clk_gate_START  (0)
#define SOC_PERFSTAT_CLK_GATE_apb_clk_gate_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PERFSTAT_CMD_START_UNION
 �ṹ˵��  : CMD_START �Ĵ����ṹ���塣��ַƫ����:0x04����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cmd_start : 1;  /* bit[0]   : ����������־��
                                                    0����������δ��Ч��
                                                    1������������Ч�� */
        unsigned int  reserved  : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PERFSTAT_CMD_START_UNION;
#endif
#define SOC_PERFSTAT_CMD_START_cmd_start_START  (0)
#define SOC_PERFSTAT_CMD_START_cmd_start_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PERFSTAT_SAMPLE_CNT_REG_UNION
 �ṹ˵��  : SAMPLE_CNT_REG �Ĵ����ṹ���塣��ַƫ����:0x08����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͳ�����ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ����ͳ����������ʱ��Ƶ��Ϊ60MHz�� */
    } reg;
} SOC_PERFSTAT_SAMPLE_CNT_REG_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_PERFSTAT_SAMPLE_NUM_REG_UNION
 �ṹ˵��  : SAMPLE_NUM_REG �Ĵ����ṹ���塣��ַƫ����:0x0C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���������Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ��������������0��ʾѭ������������ֵΪʵ�ʲ��������� */
    } reg;
} SOC_PERFSTAT_SAMPLE_NUM_REG_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_PERFSTAT_SAMPLE_STOP_UNION
 �ṹ˵��  : SAMPLE_STOP �Ĵ����ṹ���塣��ַƫ����:0x10����ֵ:0x0000�����:32
 �Ĵ���˵��: ����ֹͣ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sample_stop : 1;  /* bit[0]   : ����ֹͣ��
                                                      0����Ч��
                                                      1�����ò���ֹͣ�� */
        unsigned int  reserved    : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PERFSTAT_SAMPLE_STOP_UNION;
#endif
#define SOC_PERFSTAT_SAMPLE_STOP_sample_stop_START  (0)
#define SOC_PERFSTAT_SAMPLE_STOP_sample_stop_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PERFSTAT_REAL_PORT_NUM_UNION
 �ṹ˵��  : REAL_PORT_NUM �Ĵ����ṹ���塣��ַƫ����:0x14����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ض˿ڸ����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  real_port_num : 16; /* bit[0-15] : ���ô���ض˿ڸ�����ÿbit����1���˿ڣ������ü��ÿ���˿ڣ�����Ϊ0xffff����
                                                         ���ж˿�ӳ�����£���0����dss_m0����1����dss_m1����2����cci_m1����3����cci_m2����4����gpu����5����modem_m0����6����modem_m1����7����isp_dram����8����isp_a7����9����vdec����10����venc����11����ivp����12����sysnoc����13����audio����14����emmc����15����usb�� */
        unsigned int  reserved      : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_PERFSTAT_REAL_PORT_NUM_UNION;
#endif
#define SOC_PERFSTAT_REAL_PORT_NUM_real_port_num_START  (0)
#define SOC_PERFSTAT_REAL_PORT_NUM_real_port_num_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_PERFSTAT_AXI_ADDR_MODE_UNION
 �ṹ˵��  : AXI_ADDR_MODE �Ĵ����ṹ���塣��ַƫ����:0x18����ֵ:0x0000�����:32
 �Ĵ���˵��: ��ַģʽ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi_addr_mode : 1;  /* bit[0]   : ��ַģʽ��
                                                        0��������ַģʽ��
                                                        1�������ַģʽ�� */
        unsigned int  reserved      : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PERFSTAT_AXI_ADDR_MODE_UNION;
#endif
#define SOC_PERFSTAT_AXI_ADDR_MODE_axi_addr_mode_START  (0)
#define SOC_PERFSTAT_AXI_ADDR_MODE_axi_addr_mode_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PERFSTAT_SEQ_ADDR_UNION
 �ṹ˵��  : SEQ_ADDR �Ĵ����ṹ���塣��ַƫ����:0x1C����ֵ:0x0000�����:32
 �Ĵ���˵��: ����ģʽд��ַ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ����ģʽ������AXIд�����׵�ַ��32Byte���룩�� */
    } reg;
} SOC_PERFSTAT_SEQ_ADDR_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_PERFSTAT_SEQ_ADDR_LEN_UNION
 �ṹ˵��  : SEQ_ADDR_LEN �Ĵ����ṹ���塣��ַƫ����:0x20����ֵ:0x0000�����:32
 �Ĵ���˵��: ����ģʽд��ַ����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ����ģʽ������AXIд������ַ���䣨32Byte�������� */
    } reg;
} SOC_PERFSTAT_SEQ_ADDR_LEN_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_PERFSTAT_DESCRIPTOR_ADDR_UNION
 �ṹ˵��  : DESCRIPTOR_ADDR �Ĵ����ṹ���塣��ַƫ����:0x24����ֵ:0x0000�����:32
 �Ĵ���˵��: �����ַ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: �����ַ������AXI���������׵�ַ�� */
    } reg;
} SOC_PERFSTAT_DESCRIPTOR_ADDR_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_PERFSTAT_LAST_DESC_ADDR_UNION
 �ṹ˵��  : LAST_DESC_ADDR �Ĵ����ṹ���塣��ַƫ����:0x28����ֵ:0x0000�����:32
 �Ĵ���˵��: ��ǰ�����ַ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: �����쳣������ѯ��ǰ�����ַ�������������ʱ��debug */
    } reg;
} SOC_PERFSTAT_LAST_DESC_ADDR_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_PERFSTAT_STAT_RST_CNT_UNION
 �ṹ˵��  : STAT_RST_CNT �Ĵ����ṹ���塣��ַƫ����:0x2C����ֵ:0x0000�����:32
 �Ĵ���˵��: ��λ������Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stat_rst_cnt : 9;  /* bit[0-8] : �����쳣������ѯ��λ�������״̬����������ֵΪ0ʱ����ʾԶ��monitorģ�鴦�ڷ�shift״̬�� */
        unsigned int  reserved     : 23; /* bit[9-31]: ������ */
    } reg;
} SOC_PERFSTAT_STAT_RST_CNT_UNION;
#endif
#define SOC_PERFSTAT_STAT_RST_CNT_stat_rst_cnt_START  (0)
#define SOC_PERFSTAT_STAT_RST_CNT_stat_rst_cnt_END    (8)


/*****************************************************************************
 �ṹ��    : SOC_PERFSTAT_INT_EN_UNION
 �ṹ˵��  : INT_EN �Ĵ����ṹ���塣��ַƫ����:0x30����ֵ:0x0000�����:32
 �Ĵ���˵��: ST�ж����ο��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sample_int_en   : 1;  /* bit[0]   : �Ƿ�������������жϣ�
                                                          0����ֹ�жϣ�
                                                          1�������жϡ� */
        unsigned int  overtime_int_en : 1;  /* bit[1]   : �Ƿ�����ʱ�жϣ�
                                                          0����ֹ�жϣ�
                                                          1�������жϡ� */
        unsigned int  desc_int_en     : 1;  /* bit[2]   : �Ƿ����������жϣ�
                                                          0����ֹ�жϣ�
                                                          1�������жϡ� */
        unsigned int  desc_error_en   : 1;  /* bit[3]   : �Ƿ�������������жϣ�
                                                          0����ֹ�жϣ�
                                                          1�������жϡ� */
        unsigned int  reserved        : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_PERFSTAT_INT_EN_UNION;
#endif
#define SOC_PERFSTAT_INT_EN_sample_int_en_START    (0)
#define SOC_PERFSTAT_INT_EN_sample_int_en_END      (0)
#define SOC_PERFSTAT_INT_EN_overtime_int_en_START  (1)
#define SOC_PERFSTAT_INT_EN_overtime_int_en_END    (1)
#define SOC_PERFSTAT_INT_EN_desc_int_en_START      (2)
#define SOC_PERFSTAT_INT_EN_desc_int_en_END        (2)
#define SOC_PERFSTAT_INT_EN_desc_error_en_START    (3)
#define SOC_PERFSTAT_INT_EN_desc_error_en_END      (3)


/*****************************************************************************
 �ṹ��    : SOC_PERFSTAT_INT_CLR_UNION
 �ṹ˵��  : INT_CLR �Ĵ����ṹ���塣��ַƫ����:0x34����ֵ:0x0000�����:32
 �Ĵ���˵��: ST�ж�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sample_int_clr   : 1;  /* bit[0]   : ��ɲ��������ж������
                                                           0����Ч��
                                                           1������жϡ� */
        unsigned int  overtime_int_clr : 1;  /* bit[1]   : ��ɳ�ʱ�ж������
                                                           0����Ч��
                                                           1������жϡ� */
        unsigned int  desc_int_clr     : 1;  /* bit[2]   : ��������ж������
                                                           0����Ч��
                                                           1������жϡ� */
        unsigned int  desc_error_clr   : 1;  /* bit[3]   : �����������ж������
                                                           0����Ч��
                                                           1������жϡ� */
        unsigned int  reserved         : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_PERFSTAT_INT_CLR_UNION;
#endif
#define SOC_PERFSTAT_INT_CLR_sample_int_clr_START    (0)
#define SOC_PERFSTAT_INT_CLR_sample_int_clr_END      (0)
#define SOC_PERFSTAT_INT_CLR_overtime_int_clr_START  (1)
#define SOC_PERFSTAT_INT_CLR_overtime_int_clr_END    (1)
#define SOC_PERFSTAT_INT_CLR_desc_int_clr_START      (2)
#define SOC_PERFSTAT_INT_CLR_desc_int_clr_END        (2)
#define SOC_PERFSTAT_INT_CLR_desc_error_clr_START    (3)
#define SOC_PERFSTAT_INT_CLR_desc_error_clr_END      (3)


/*****************************************************************************
 �ṹ��    : SOC_PERFSTAT_RAW_INT_STAT_UNION
 �ṹ˵��  : RAW_INT_STAT �Ĵ����ṹ���塣��ַƫ����:0x38����ֵ:0x0000�����:32
 �Ĵ���˵��: STԭʼ�ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sample_raw_int_stat : 1;  /* bit[0]   : ԭʼ���������ж�״̬��
                                                              0����Ч��
                                                              1����Ч�� */
        unsigned int  overtime_int_stat   : 1;  /* bit[1]   : ԭʼ��ʱ�ж�״̬��
                                                              0����Ч��
                                                              1����Ч�� */
        unsigned int  desc_raw_int_stat   : 1;  /* bit[2]   : ԭʼ�����ж�״̬��
                                                              0����Ч��
                                                              1����Ч�� */
        unsigned int  desc_raw_error_stat : 1;  /* bit[3]   : ԭʼ��������ж�״̬��
                                                              0����Ч��
                                                              1����Ч�� */
        unsigned int  reserved            : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_PERFSTAT_RAW_INT_STAT_UNION;
#endif
#define SOC_PERFSTAT_RAW_INT_STAT_sample_raw_int_stat_START  (0)
#define SOC_PERFSTAT_RAW_INT_STAT_sample_raw_int_stat_END    (0)
#define SOC_PERFSTAT_RAW_INT_STAT_overtime_int_stat_START    (1)
#define SOC_PERFSTAT_RAW_INT_STAT_overtime_int_stat_END      (1)
#define SOC_PERFSTAT_RAW_INT_STAT_desc_raw_int_stat_START    (2)
#define SOC_PERFSTAT_RAW_INT_STAT_desc_raw_int_stat_END      (2)
#define SOC_PERFSTAT_RAW_INT_STAT_desc_raw_error_stat_START  (3)
#define SOC_PERFSTAT_RAW_INT_STAT_desc_raw_error_stat_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_PERFSTAT_MASK_INT_STAT_UNION
 �ṹ˵��  : MASK_INT_STAT �Ĵ����ṹ���塣��ַƫ����:0x3C����ֵ:0x0000�����:32
 �Ĵ���˵��: ST���κ��ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sample_mask_int_stat : 1;  /* bit[0]   : ���κ���������ж�״̬��
                                                               0����Ч��
                                                               1����Ч�� */
        unsigned int  overtime_int_stat    : 1;  /* bit[1]   : ���κ�ʱ�ж�״̬��
                                                               0����Ч��
                                                               1����Ч�� */
        unsigned int  desc_mask_int_stat   : 1;  /* bit[2]   : ���κ������ж�״̬��
                                                               0����Ч��
                                                               1����Ч�� */
        unsigned int  desc_mask_error_stat : 1;  /* bit[3]   : ���κ���������ж�״̬��
                                                               0����Ч��
                                                               1����Ч�� */
        unsigned int  reserved             : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_PERFSTAT_MASK_INT_STAT_UNION;
#endif
#define SOC_PERFSTAT_MASK_INT_STAT_sample_mask_int_stat_START  (0)
#define SOC_PERFSTAT_MASK_INT_STAT_sample_mask_int_stat_END    (0)
#define SOC_PERFSTAT_MASK_INT_STAT_overtime_int_stat_START     (1)
#define SOC_PERFSTAT_MASK_INT_STAT_overtime_int_stat_END       (1)
#define SOC_PERFSTAT_MASK_INT_STAT_desc_mask_int_stat_START    (2)
#define SOC_PERFSTAT_MASK_INT_STAT_desc_mask_int_stat_END      (2)
#define SOC_PERFSTAT_MASK_INT_STAT_desc_mask_error_stat_START  (3)
#define SOC_PERFSTAT_MASK_INT_STAT_desc_mask_error_stat_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_PERFSTAT_ALL_SAMPLE_NUM_UNION
 �ṹ˵��  : ALL_SAMPLE_NUM �Ĵ����ṹ���塣��ַƫ����:0x40����ֵ:0x0000�����:32
 �Ĵ���˵��: �ܲ��������Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: �ܲ�����������ʾ��ǰ�Ѳ����Ĵ���ֵ */
    } reg;
} SOC_PERFSTAT_ALL_SAMPLE_NUM_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_PERFSTAT_LAST_SAMPLE_AXI_ADDR_UNION
 �ṹ˵��  : LAST_SAMPLE_AXI_ADDR �Ĵ����ṹ���塣��ַƫ����:0x44����ֵ:0x0000�����:32
 �Ĵ���˵��: ������ַ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: �õ�ַ��ʾ���һ������д��ɺ��дָ���ַ */
    } reg;
} SOC_PERFSTAT_LAST_SAMPLE_AXI_ADDR_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_PERFSTAT_OVERTIME_CFG_CNT_UNION
 �ṹ˵��  : OVERTIME_CFG_CNT �Ĵ����ṹ���塣��ַƫ����:0x48����ֵ:0x0000�����:32
 �Ĵ���˵��: ��ʱ������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ��ά�ɲ�Ĵ��������ü�����ֵ����ظü��������ڣ�monitorģ���axi����˷�ѹ��Ϣ�� */
    } reg;
} SOC_PERFSTAT_OVERTIME_CFG_CNT_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_PERFSTAT_DEBUG_FIFO_FULL_UNION
 �ṹ˵��  : DEBUG_FIFO_FULL �Ĵ����ṹ���塣��ַƫ����:0x4C����ֵ:0x0000�����:32
 �Ĵ���˵��: ��ѯfifo��״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  debug_fifo_full : 1;  /* bit[0]   : ��ά�ɲ�Ĵ��������ó�ʱ��������ʹ�á�
                                                          ����ʱ�ж���Чʱ����ѯfifo״̬��
                                                          0��fifo��ǰΪ����״̬��
                                                          1��fifo��ǰΪ��״̬�� */
        unsigned int  reserved        : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PERFSTAT_DEBUG_FIFO_FULL_UNION;
#endif
#define SOC_PERFSTAT_DEBUG_FIFO_FULL_debug_fifo_full_START  (0)
#define SOC_PERFSTAT_DEBUG_FIFO_FULL_debug_fifo_full_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PERFSTAT_DEBUG_MONITOR_UNION
 �ṹ˵��  : DEBUG_MONITOR �Ĵ����ṹ���塣��ַƫ����:0x50����ֵ:0x0000�����:32
 �Ĵ���˵��: ��ѯmonitor�����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  debug_monitor : 16; /* bit[0-15] : ��ά�ɲ�Ĵ��������ó�ʱ��������ʹ�á�
                                                         ����ʱ�ж���Чʱ����ѯ��monitor�Ƿ����������У�16bit��ʾ16��monitor�˿ڵ�����״̬��
                                                         0��δ������
                                                         1�������� */
        unsigned int  reserved      : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_PERFSTAT_DEBUG_MONITOR_UNION;
#endif
#define SOC_PERFSTAT_DEBUG_MONITOR_debug_monitor_START  (0)
#define SOC_PERFSTAT_DEBUG_MONITOR_debug_monitor_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_PERFSTAT_MONITOR_RESET_UNION
 �ṹ˵��  : MONITOR_RESET �Ĵ����ṹ���塣��ַƫ����:0x54����ֵ:0x0000�����:32
 �Ĵ���˵��: monitor��λ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_reset : 1;  /* bit[0]   : �����쳣������stat_rst_cnt�Ĵ���Ϊ0������minotor״̬���ص�IDLE״̬�������������� */
        unsigned int  reserved      : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PERFSTAT_MONITOR_RESET_UNION;
#endif
#define SOC_PERFSTAT_MONITOR_RESET_monitor_reset_START  (0)
#define SOC_PERFSTAT_MONITOR_RESET_monitor_reset_END    (0)






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

#endif /* end of soc_perfstat_interface.h */
