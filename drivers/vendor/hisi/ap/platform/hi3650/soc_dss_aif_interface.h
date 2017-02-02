/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_dss_aif_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:19:57
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_DSS_AIF.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_DSS_AIF_INTERFACE_H__
#define __SOC_DSS_AIF_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_AIF
 ****************************************************************************/
/* �Ĵ���˵����AIFͨ��0��ͨ�����ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_AIF_AIF_CH_CTL_0_UNION */
#define SOC_DSS_AIF_AIF_CH_CTL_0_ADDR(base)           ((base) + (0x0000))

/* �Ĵ���˵����AIFͨ��1��ͨ�����ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_AIF_AIF_CH_CTL_1_UNION */
#define SOC_DSS_AIF_AIF_CH_CTL_1_ADDR(base)           ((base) + (0x0020))

/* �Ĵ���˵����AIFͨ��2��ͨ�����ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_AIF_AIF_CH_CTL_2_UNION */
#define SOC_DSS_AIF_AIF_CH_CTL_2_ADDR(base)           ((base) + (0x0040))

/* �Ĵ���˵����AIFͨ��3��ͨ�����ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_AIF_AIF_CH_CTL_3_UNION */
#define SOC_DSS_AIF_AIF_CH_CTL_3_ADDR(base)           ((base) + (0x0060))

/* �Ĵ���˵����AIFͨ��4��ͨ�����ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_AIF_AIF_CH_CTL_4_UNION */
#define SOC_DSS_AIF_AIF_CH_CTL_4_ADDR(base)           ((base) + (0x0080))

/* �Ĵ���˵����AIFͨ��5��ͨ�����ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_AIF_AIF_CH_CTL_5_UNION */
#define SOC_DSS_AIF_AIF_CH_CTL_5_ADDR(base)           ((base) + (0x00a0))

/* �Ĵ���˵����AIFͨ��6��ͨ�����ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_AIF_AIF_CH_CTL_6_UNION */
#define SOC_DSS_AIF_AIF_CH_CTL_6_ADDR(base)           ((base) + (0x00c0))

/* �Ĵ���˵����AIFͨ��7��ͨ�����ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_AIF_AIF_CH_CTL_7_UNION */
#define SOC_DSS_AIF_AIF_CH_CTL_7_ADDR(base)           ((base) + (0x00e0))

/* �Ĵ���˵����AIFͨ��8��ͨ�����ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_AIF_AIF_CH_CTL_8_UNION */
#define SOC_DSS_AIF_AIF_CH_CTL_8_ADDR(base)           ((base) + (0x0100))

/* �Ĵ���˵����AIFͨ��9��ͨ�����ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_AIF_AIF_CH_CTL_9_UNION */
#define SOC_DSS_AIF_AIF_CH_CTL_9_ADDR(base)           ((base) + (0x0120))

/* �Ĵ���˵����AIFͨ��10��ͨ�����ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_AIF_AIF_CH_CTL_10_UNION */
#define SOC_DSS_AIF_AIF_CH_CTL_10_ADDR(base)          ((base) + (0x0140))

/* �Ĵ���˵����AXI0 Read ID Mask
   λ����UNION�ṹ:  SOC_DSS_AIF_AXI0_RID_MSK0_UNION */
#define SOC_DSS_AIF_AXI0_RID_MSK0_ADDR(base)          ((base) + (0x0800))

/* �Ĵ���˵����AXI0 Read ID Mask
   λ����UNION�ṹ:  SOC_DSS_AIF_AXI0_RID_MSK1_UNION */
#define SOC_DSS_AIF_AXI0_RID_MSK1_ADDR(base)          ((base) + (0x0804))

/* �Ĵ���˵����AXI0 Read ID Mask
   λ����UNION�ṹ:  SOC_DSS_AIF_AXI0_WID_MSK_UNION */
#define SOC_DSS_AIF_AXI0_WID_MSK_ADDR(base)           ((base) + (0x0808))

/* �Ĵ���˵����AXI0 Read QOS remap
   λ����UNION�ṹ:  SOC_DSS_AIF_AXI0_R_QOS_MAP_UNION */
#define SOC_DSS_AIF_AXI0_R_QOS_MAP_ADDR(base)         ((base) + (0x080c))

/* �Ĵ���˵����AXI1 Read ID Mask
   λ����UNION�ṹ:  SOC_DSS_AIF_AXI1_RID_MSK0_UNION */
#define SOC_DSS_AIF_AXI1_RID_MSK0_ADDR(base)          ((base) + (0x0810))

/* �Ĵ���˵����AXI1 Read ID Mask
   λ����UNION�ṹ:  SOC_DSS_AIF_AXI1_RID_MSK1_UNION */
#define SOC_DSS_AIF_AXI1_RID_MSK1_ADDR(base)          ((base) + (0x0814))

/* �Ĵ���˵����AXI1 Read ID Mask
   λ����UNION�ṹ:  SOC_DSS_AIF_AXI1_WID_MSK_UNION */
#define SOC_DSS_AIF_AXI1_WID_MSK_ADDR(base)           ((base) + (0x0818))

/* �Ĵ���˵����AXI1 Read QOS remap
   λ����UNION�ṹ:  SOC_DSS_AIF_AXI1_R_QOS_MAP_UNION */
#define SOC_DSS_AIF_AXI1_R_QOS_MAP_ADDR(base)         ((base) + (0x081c))

/* �Ĵ���˵����AIFģ��ʱ��ѡ��
   λ����UNION�ṹ:  SOC_DSS_AIF_AIF_CLK_SEL0_UNION */
#define SOC_DSS_AIF_AIF_CLK_SEL0_ADDR(base)           ((base) + (0x0820))

/* �Ĵ���˵����AIFģ��ʱ��ѡ��
   λ����UNION�ṹ:  SOC_DSS_AIF_AIF_CLK_SEL1_UNION */
#define SOC_DSS_AIF_AIF_CLK_SEL1_ADDR(base)           ((base) + (0x0824))

/* �Ĵ���˵����AIFģ��ʱ��ʹ��
   λ����UNION�ṹ:  SOC_DSS_AIF_AIF_CLK_EN0_UNION */
#define SOC_DSS_AIF_AIF_CLK_EN0_ADDR(base)            ((base) + (0x0828))

/* �Ĵ���˵����AIFģ��ʱ��ʹ��
   λ����UNION�ṹ:  SOC_DSS_AIF_AIF_CLK_EN1_UNION */
#define SOC_DSS_AIF_AIF_CLK_EN1_ADDR(base)            ((base) + (0x082c))

/* �Ĵ���˵����monitor���ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_AIF_MONITOR_CTRL_UNION */
#define SOC_DSS_AIF_MONITOR_CTRL_ADDR(base)           ((base) + (0x0830))

/* �Ĵ���˵����monitor��ʱ����ʼֵ
   λ����UNION�ṹ:  SOC_DSS_AIF_MONITOR_TIMER_INI_UNION */
#define SOC_DSS_AIF_MONITOR_TIMER_INI_ADDR(base)      ((base) + (0x0834))

/* �Ĵ���˵����debug buffer����ַ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_AIF_DEBUG_BUF_BASE_UNION */
#define SOC_DSS_AIF_DEBUG_BUF_BASE_ADDR(base)         ((base) + (0x0838))

/* �Ĵ���˵����debug���ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_AIF_DEBUG_CTRL_UNION */
#define SOC_DSS_AIF_DEBUG_CTRL_ADDR(base)             ((base) + (0x083C))

/* �Ĵ���˵����Ӱ�ӼĴ�����ѡ��Ĵ���
   λ����UNION�ṹ:  SOC_DSS_AIF_AIF_SHADOW_READ_UNION */
#define SOC_DSS_AIF_AIF_SHADOW_READ_ADDR(base)        ((base) + (0x0840))

/* �Ĵ���˵����AIFͨ��SRAM���ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_AIF_AIF_MEM_CTRL_UNION */
#define SOC_DSS_AIF_AIF_MEM_CTRL_ADDR(base)           ((base) + (0x0844))

/* �Ĵ���˵����AXI recorder part a
   λ����UNION�ṹ:  SOC_DSS_AIF_AXI_REC_A_m_UNION */
#define SOC_DSS_AIF_AXI_REC_A_m_ADDR(base, m)         ((base) + (0x0880+0x10*(m)))

/* �Ĵ���˵����AXI recorder part b
   λ����UNION�ṹ:  SOC_DSS_AIF_AXI_REC_B_m_UNION */
#define SOC_DSS_AIF_AXI_REC_B_m_ADDR(base, m)         ((base) + (0x0884+0x10*(m)))

/* �Ĵ���˵����AXI recorder part c
   λ����UNION�ṹ:  SOC_DSS_AIF_AXI_REC_C_m_UNION */
#define SOC_DSS_AIF_AXI_REC_C_m_ADDR(base, m)         ((base) + (0x0888+0x10*(m)))

/* �Ĵ���˵����AXI recorder part d
   λ����UNION�ṹ:  SOC_DSS_AIF_AXI_REC_D_m_UNION */
#define SOC_DSS_AIF_AXI_REC_D_m_ADDR(base, m)         ((base) + (0x088C+0x10*(m)))





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
                     (1/1) reg_AIF
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_DSS_AIF_AIF_CH_CTL_0_UNION
 �ṹ˵��  : AIF_CH_CTL_0 �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x0000�����:32
 �Ĵ���˵��: AIFͨ��0��ͨ�����ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi_sel     : 1;  /* bit[0]    : AXI�˿�ѡ��
                                                       0��ѡ��AXI0��
                                                       1��ѡ��AXI1  */
        unsigned int  max_cmd     : 3;  /* bit[1-3]  : credit_mode����1����2ʱ���������������� */
        unsigned int  mid         : 4;  /* bit[4-7]  : ͨ����MID��
                                                       0x0~0x9����Ч����ֵ��
                                                       0xA~0xF����ֹ���ã��������ϵͳ��ɲ���Ԥ֪�ĺ���� */
        unsigned int  credit_mode : 2;  /* bit[8-9]  : ����ģʽ��
                                                       0x0����ͨģʽ
                                                       0x1��afbcģʽ����ͨ����Ч��
                                                       0x2������ģʽ
                                                       0x3����Чֵ�� */
        unsigned int  reserved    : 1;  /* bit[10]   : ���� */
        unsigned int  credit_en   : 1;  /* bit[11]   : ��������ʹ�ܡ�
                                                       0��ͨ���������ƽ�ֹ��max_cont��credit_step����ֵ��Ч��
                                                       1��ͨ����������ʹ�ܣ�max_cont��credit_step����ֵ��Ч�� */
        unsigned int  max_cont    : 4;  /* bit[12-15]: credit_mod����0ʱ������������󳤶ȡ�
                                                       0x0������������󳤶ȵ���1��
                                                       0x1������������󳤶ȵ���2��
                                                       ����
                                                       0xF������������󳤶ȵ���16��
                                                       credit_mode����1����2ʱ����ʾ��������ֵ��
                                                       ��λ��512Bytes����ʱ֧��0x0-0xE�� */
        unsigned int  credit_step : 7;  /* bit[16-22]: ͨ���������ƣ�
                                                       0x0��ͨ��ֻ������������󳤶ȿ��ƣ�
                                                       0x1��1/128*ͨ��������
                                                       0x2��2/128*ͨ�������� 
                                                       0x3��3/128*ͨ�������� 
                                                       0x4��4/128*ͨ��������
                                                       0x5��5/128*ͨ��������
                                                       0x6��6/128*ͨ��������
                                                       0x7��7/128*ͨ��������
                                                       0x8��8/128*ͨ��������
                                                       ���� 
                                                       0xFF��127/128*ͨ�������� */
        unsigned int  credit_lth  : 9;  /* bit[23-31]: credit_mode����1����2ʱ����������ֵ����λ��16Bytes�� */
    } reg;
} SOC_DSS_AIF_AIF_CH_CTL_0_UNION;
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_0_axi_sel_START      (0)
#define SOC_DSS_AIF_AIF_CH_CTL_0_axi_sel_END        (0)
#define SOC_DSS_AIF_AIF_CH_CTL_0_max_cmd_START      (1)
#define SOC_DSS_AIF_AIF_CH_CTL_0_max_cmd_END        (3)
#define SOC_DSS_AIF_AIF_CH_CTL_0_mid_START          (4)
#define SOC_DSS_AIF_AIF_CH_CTL_0_mid_END            (7)
#define SOC_DSS_AIF_AIF_CH_CTL_0_credit_mode_START  (8)
#define SOC_DSS_AIF_AIF_CH_CTL_0_credit_mode_END    (9)
#define SOC_DSS_AIF_AIF_CH_CTL_0_credit_en_START    (11)
#define SOC_DSS_AIF_AIF_CH_CTL_0_credit_en_END      (11)
#define SOC_DSS_AIF_AIF_CH_CTL_0_max_cont_START     (12)
#define SOC_DSS_AIF_AIF_CH_CTL_0_max_cont_END       (15)
#define SOC_DSS_AIF_AIF_CH_CTL_0_credit_step_START  (16)
#define SOC_DSS_AIF_AIF_CH_CTL_0_credit_step_END    (22)
#define SOC_DSS_AIF_AIF_CH_CTL_0_credit_lth_START   (23)
#define SOC_DSS_AIF_AIF_CH_CTL_0_credit_lth_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_AIF_AIF_CH_CTL_1_UNION
 �ṹ˵��  : AIF_CH_CTL_1 �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x0000�����:32
 �Ĵ���˵��: AIFͨ��1��ͨ�����ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi_sel     : 1;  /* bit[0]    : AXI�˿�ѡ��
                                                       0��ѡ��AXI0��
                                                       1��ѡ��AXI1  */
        unsigned int  reserved_0  : 3;  /* bit[1-3]  : ���� */
        unsigned int  mid         : 4;  /* bit[4-7]  : ͨ����MID��
                                                       0x0~0x9����Ч����ֵ��
                                                       0xA~0xF����ֹ���ã��������ϵͳ��ɲ���Ԥ֪�ĺ���� */
        unsigned int  credit_mode : 2;  /* bit[8-9]  : ����ģʽ��
                                                       0x0����ͨģʽ
                                                       0x1��afbcģʽ����ͨ����Ч��
                                                       0x2������ģʽ
                                                       0x3����Чֵ�� */
        unsigned int  reserved_1  : 1;  /* bit[10]   : ���� */
        unsigned int  credit_en   : 1;  /* bit[11]   : ��������ʹ�ܡ�
                                                       0��ͨ���������ƽ�ֹ��max_cont��credit_step����ֵ��Ч��
                                                       1��ͨ����������ʹ�ܣ�max_cont��credit_step����ֵ��Ч�� */
        unsigned int  max_cont    : 4;  /* bit[12-15]: credit_mod����0ʱ������������󳤶ȡ�
                                                       0x0������������󳤶ȵ���1��
                                                       0x1������������󳤶ȵ���2��
                                                       ����
                                                       0xF������������󳤶ȵ���16��
                                                       credit_mode����1����2ʱ����ʾ��������ֵ��
                                                       ��λ��512Bytes����ʱ֧��0x0-0xE�� */
        unsigned int  credit_step : 7;  /* bit[16-22]: ͨ���������ƣ�
                                                       0x0��ͨ��ֻ������������󳤶ȿ��ƣ�
                                                       0x1��1/128*ͨ��������
                                                       0x2��2/128*ͨ�������� 
                                                       0x3��3/128*ͨ�������� 
                                                       0x4��4/128*ͨ��������
                                                       0x5��5/128*ͨ��������
                                                       0x6��6/128*ͨ��������
                                                       0x7��7/128*ͨ��������
                                                       0x8��8/128*ͨ��������
                                                       ���� 
                                                       0xFF��127/128*ͨ�������� */
        unsigned int  reserved_2  : 9;  /* bit[23-31]: ���� */
    } reg;
} SOC_DSS_AIF_AIF_CH_CTL_1_UNION;
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_1_axi_sel_START      (0)
#define SOC_DSS_AIF_AIF_CH_CTL_1_axi_sel_END        (0)
#define SOC_DSS_AIF_AIF_CH_CTL_1_mid_START          (4)
#define SOC_DSS_AIF_AIF_CH_CTL_1_mid_END            (7)
#define SOC_DSS_AIF_AIF_CH_CTL_1_credit_mode_START  (8)
#define SOC_DSS_AIF_AIF_CH_CTL_1_credit_mode_END    (9)
#define SOC_DSS_AIF_AIF_CH_CTL_1_credit_en_START    (11)
#define SOC_DSS_AIF_AIF_CH_CTL_1_credit_en_END      (11)
#define SOC_DSS_AIF_AIF_CH_CTL_1_max_cont_START     (12)
#define SOC_DSS_AIF_AIF_CH_CTL_1_max_cont_END       (15)
#define SOC_DSS_AIF_AIF_CH_CTL_1_credit_step_START  (16)
#define SOC_DSS_AIF_AIF_CH_CTL_1_credit_step_END    (22)


/*****************************************************************************
 �ṹ��    : SOC_DSS_AIF_AIF_CH_CTL_2_UNION
 �ṹ˵��  : AIF_CH_CTL_2 �Ĵ����ṹ���塣��ַƫ����:0x0040����ֵ:0x0000�����:32
 �Ĵ���˵��: AIFͨ��2��ͨ�����ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi_sel     : 1;  /* bit[0]    : AXI�˿�ѡ��
                                                       0��ѡ��AXI0��
                                                       1��ѡ��AXI1  */
        unsigned int  max_cmd     : 3;  /* bit[1-3]  : credit_mode����1����2ʱ���������������� */
        unsigned int  mid         : 4;  /* bit[4-7]  : ͨ����MID��
                                                       0x0~0x9����Ч����ֵ��
                                                       0xA~0xF����ֹ���ã��������ϵͳ��ɲ���Ԥ֪�ĺ���� */
        unsigned int  credit_mode : 2;  /* bit[8-9]  : ����ģʽ��
                                                       0x0����ͨģʽ
                                                       0x1��afbcģʽ����ͨ����Ч��
                                                       0x2������ģʽ
                                                       0x3����Чֵ�� */
        unsigned int  reserved    : 1;  /* bit[10]   : ���� */
        unsigned int  credit_en   : 1;  /* bit[11]   : ��������ʹ�ܡ�
                                                       0��ͨ���������ƽ�ֹ��max_cont��credit_step����ֵ��Ч��
                                                       1��ͨ����������ʹ�ܣ�max_cont��credit_step����ֵ��Ч�� */
        unsigned int  max_cont    : 4;  /* bit[12-15]: credit_mod����0ʱ������������󳤶ȡ�
                                                       0x0������������󳤶ȵ���1��
                                                       0x1������������󳤶ȵ���2��
                                                       ����
                                                       0xF������������󳤶ȵ���16��
                                                       credit_mode����1����2ʱ����ʾ��������ֵ��
                                                       ��λ��512Bytes����ʱ֧��0x0-0xE�� */
        unsigned int  credit_step : 7;  /* bit[16-22]: ͨ���������ƣ�
                                                       0x0��ͨ��ֻ������������󳤶ȿ��ƣ�
                                                       0x1��1/128*ͨ��������
                                                       0x2��2/128*ͨ�������� 
                                                       0x3��3/128*ͨ�������� 
                                                       0x4��4/128*ͨ��������
                                                       0x5��5/128*ͨ��������
                                                       0x6��6/128*ͨ��������
                                                       0x7��7/128*ͨ��������
                                                       0x8��8/128*ͨ��������
                                                       ���� 
                                                       0xFF��127/128*ͨ�������� */
        unsigned int  credit_lth  : 9;  /* bit[23-31]: credit_mode����1����2ʱ����������ֵ����λ��16Bytes�� */
    } reg;
} SOC_DSS_AIF_AIF_CH_CTL_2_UNION;
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_2_axi_sel_START      (0)
#define SOC_DSS_AIF_AIF_CH_CTL_2_axi_sel_END        (0)
#define SOC_DSS_AIF_AIF_CH_CTL_2_max_cmd_START      (1)
#define SOC_DSS_AIF_AIF_CH_CTL_2_max_cmd_END        (3)
#define SOC_DSS_AIF_AIF_CH_CTL_2_mid_START          (4)
#define SOC_DSS_AIF_AIF_CH_CTL_2_mid_END            (7)
#define SOC_DSS_AIF_AIF_CH_CTL_2_credit_mode_START  (8)
#define SOC_DSS_AIF_AIF_CH_CTL_2_credit_mode_END    (9)
#define SOC_DSS_AIF_AIF_CH_CTL_2_credit_en_START    (11)
#define SOC_DSS_AIF_AIF_CH_CTL_2_credit_en_END      (11)
#define SOC_DSS_AIF_AIF_CH_CTL_2_max_cont_START     (12)
#define SOC_DSS_AIF_AIF_CH_CTL_2_max_cont_END       (15)
#define SOC_DSS_AIF_AIF_CH_CTL_2_credit_step_START  (16)
#define SOC_DSS_AIF_AIF_CH_CTL_2_credit_step_END    (22)
#define SOC_DSS_AIF_AIF_CH_CTL_2_credit_lth_START   (23)
#define SOC_DSS_AIF_AIF_CH_CTL_2_credit_lth_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_AIF_AIF_CH_CTL_3_UNION
 �ṹ˵��  : AIF_CH_CTL_3 �Ĵ����ṹ���塣��ַƫ����:0x0060����ֵ:0x0000�����:32
 �Ĵ���˵��: AIFͨ��3��ͨ�����ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi_sel     : 1;  /* bit[0]    : AXI�˿�ѡ��
                                                       0��ѡ��AXI0��
                                                       1��ѡ��AXI1  */
        unsigned int  max_cmd     : 3;  /* bit[1-3]  : credit_mode����1����2ʱ���������������� */
        unsigned int  mid         : 4;  /* bit[4-7]  : ͨ����MID��
                                                       0x0~0x9����Ч����ֵ��
                                                       0xA~0xF����ֹ���ã��������ϵͳ��ɲ���Ԥ֪�ĺ���� */
        unsigned int  credit_mode : 2;  /* bit[8-9]  : ����ģʽ��
                                                       0x0����ͨģʽ
                                                       0x1��afbcģʽ����ͨ����Ч��
                                                       0x2������ģʽ
                                                       0x3����Чֵ�� */
        unsigned int  reserved    : 1;  /* bit[10]   : ���� */
        unsigned int  credit_en   : 1;  /* bit[11]   : ��������ʹ�ܡ�
                                                       0��ͨ���������ƽ�ֹ��max_cont��credit_step����ֵ��Ч��
                                                       1��ͨ����������ʹ�ܣ�max_cont��credit_step����ֵ��Ч�� */
        unsigned int  max_cont    : 4;  /* bit[12-15]: credit_mod����0ʱ������������󳤶ȡ�
                                                       0x0������������󳤶ȵ���1��
                                                       0x1������������󳤶ȵ���2��
                                                       ����
                                                       0xF������������󳤶ȵ���16��
                                                       credit_mode����1����2ʱ����ʾ��������ֵ��
                                                       ��λ��512Bytes����ʱ֧��0x0-0xE�� */
        unsigned int  credit_step : 7;  /* bit[16-22]: ͨ���������ƣ�
                                                       0x0��ͨ��ֻ������������󳤶ȿ��ƣ�
                                                       0x1��1/128*ͨ��������
                                                       0x2��2/128*ͨ�������� 
                                                       0x3��3/128*ͨ�������� 
                                                       0x4��4/128*ͨ��������
                                                       0x5��5/128*ͨ��������
                                                       0x6��6/128*ͨ��������
                                                       0x7��7/128*ͨ��������
                                                       0x8��8/128*ͨ��������
                                                       ���� 
                                                       0xFF��127/128*ͨ�������� */
        unsigned int  credit_lth  : 9;  /* bit[23-31]: credit_mode����1����2ʱ����������ֵ����λ��16Bytes�� */
    } reg;
} SOC_DSS_AIF_AIF_CH_CTL_3_UNION;
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_3_axi_sel_START      (0)
#define SOC_DSS_AIF_AIF_CH_CTL_3_axi_sel_END        (0)
#define SOC_DSS_AIF_AIF_CH_CTL_3_max_cmd_START      (1)
#define SOC_DSS_AIF_AIF_CH_CTL_3_max_cmd_END        (3)
#define SOC_DSS_AIF_AIF_CH_CTL_3_mid_START          (4)
#define SOC_DSS_AIF_AIF_CH_CTL_3_mid_END            (7)
#define SOC_DSS_AIF_AIF_CH_CTL_3_credit_mode_START  (8)
#define SOC_DSS_AIF_AIF_CH_CTL_3_credit_mode_END    (9)
#define SOC_DSS_AIF_AIF_CH_CTL_3_credit_en_START    (11)
#define SOC_DSS_AIF_AIF_CH_CTL_3_credit_en_END      (11)
#define SOC_DSS_AIF_AIF_CH_CTL_3_max_cont_START     (12)
#define SOC_DSS_AIF_AIF_CH_CTL_3_max_cont_END       (15)
#define SOC_DSS_AIF_AIF_CH_CTL_3_credit_step_START  (16)
#define SOC_DSS_AIF_AIF_CH_CTL_3_credit_step_END    (22)
#define SOC_DSS_AIF_AIF_CH_CTL_3_credit_lth_START   (23)
#define SOC_DSS_AIF_AIF_CH_CTL_3_credit_lth_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_AIF_AIF_CH_CTL_4_UNION
 �ṹ˵��  : AIF_CH_CTL_4 �Ĵ����ṹ���塣��ַƫ����:0x0080����ֵ:0x0000�����:32
 �Ĵ���˵��: AIFͨ��4��ͨ�����ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi_sel     : 1;  /* bit[0]    : AXI�˿�ѡ��
                                                       0��ѡ��AXI0��
                                                       1��ѡ��AXI1  */
        unsigned int  max_cmd     : 3;  /* bit[1-3]  : credit_mode����1����2ʱ���������������� */
        unsigned int  mid         : 4;  /* bit[4-7]  : ͨ����MID��
                                                       0x0~0x9����Ч����ֵ��
                                                       0xA~0xF����ֹ���ã��������ϵͳ��ɲ���Ԥ֪�ĺ���� */
        unsigned int  credit_mode : 2;  /* bit[8-9]  : ����ģʽ��
                                                       0x0����ͨģʽ
                                                       0x1��afbcģʽ����ͨ����Ч��
                                                       0x2������ģʽ
                                                       0x3����Чֵ�� */
        unsigned int  reserved    : 1;  /* bit[10]   : ���� */
        unsigned int  credit_en   : 1;  /* bit[11]   : ��������ʹ�ܡ�
                                                       0��ͨ���������ƽ�ֹ��max_cont��credit_step����ֵ��Ч��
                                                       1��ͨ����������ʹ�ܣ�max_cont��credit_step����ֵ��Ч�� */
        unsigned int  max_cont    : 4;  /* bit[12-15]: credit_mod����0ʱ������������󳤶ȡ�
                                                       0x0������������󳤶ȵ���1��
                                                       0x1������������󳤶ȵ���2��
                                                       ����
                                                       0xF������������󳤶ȵ���16��
                                                       credit_mode����1����2ʱ����ʾ��������ֵ��
                                                       ��λ��512Bytes����ʱ֧��0x0-0xE�� */
        unsigned int  credit_step : 7;  /* bit[16-22]: ͨ���������ƣ�
                                                       0x0��ͨ��ֻ������������󳤶ȿ��ƣ�
                                                       0x1��1/128*ͨ��������
                                                       0x2��2/128*ͨ�������� 
                                                       0x3��3/128*ͨ�������� 
                                                       0x4��4/128*ͨ��������
                                                       0x5��5/128*ͨ��������
                                                       0x6��6/128*ͨ��������
                                                       0x7��7/128*ͨ��������
                                                       0x8��8/128*ͨ��������
                                                       ���� 
                                                       0xFF��127/128*ͨ�������� */
        unsigned int  credit_lth  : 9;  /* bit[23-31]: credit_mode����1����2ʱ����������ֵ����λ��16Bytes�� */
    } reg;
} SOC_DSS_AIF_AIF_CH_CTL_4_UNION;
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_4_axi_sel_START      (0)
#define SOC_DSS_AIF_AIF_CH_CTL_4_axi_sel_END        (0)
#define SOC_DSS_AIF_AIF_CH_CTL_4_max_cmd_START      (1)
#define SOC_DSS_AIF_AIF_CH_CTL_4_max_cmd_END        (3)
#define SOC_DSS_AIF_AIF_CH_CTL_4_mid_START          (4)
#define SOC_DSS_AIF_AIF_CH_CTL_4_mid_END            (7)
#define SOC_DSS_AIF_AIF_CH_CTL_4_credit_mode_START  (8)
#define SOC_DSS_AIF_AIF_CH_CTL_4_credit_mode_END    (9)
#define SOC_DSS_AIF_AIF_CH_CTL_4_credit_en_START    (11)
#define SOC_DSS_AIF_AIF_CH_CTL_4_credit_en_END      (11)
#define SOC_DSS_AIF_AIF_CH_CTL_4_max_cont_START     (12)
#define SOC_DSS_AIF_AIF_CH_CTL_4_max_cont_END       (15)
#define SOC_DSS_AIF_AIF_CH_CTL_4_credit_step_START  (16)
#define SOC_DSS_AIF_AIF_CH_CTL_4_credit_step_END    (22)
#define SOC_DSS_AIF_AIF_CH_CTL_4_credit_lth_START   (23)
#define SOC_DSS_AIF_AIF_CH_CTL_4_credit_lth_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_AIF_AIF_CH_CTL_5_UNION
 �ṹ˵��  : AIF_CH_CTL_5 �Ĵ����ṹ���塣��ַƫ����:0x00a0����ֵ:0x0000�����:32
 �Ĵ���˵��: AIFͨ��5��ͨ�����ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi_sel     : 1;  /* bit[0]    : AXI�˿�ѡ��
                                                       0��ѡ��AXI0��
                                                       1��ѡ��AXI1  */
        unsigned int  max_cmd     : 3;  /* bit[1-3]  : credit_mode����1����2ʱ���������������� */
        unsigned int  mid         : 4;  /* bit[4-7]  : ͨ����MID��
                                                       0x0~0x9����Ч����ֵ��
                                                       0xA~0xF����ֹ���ã��������ϵͳ��ɲ���Ԥ֪�ĺ���� */
        unsigned int  credit_mode : 2;  /* bit[8-9]  : ����ģʽ��
                                                       0x0����ͨģʽ
                                                       0x1��afbcģʽ����ͨ����Ч��
                                                       0x2������ģʽ
                                                       0x3����Чֵ�� */
        unsigned int  reserved    : 1;  /* bit[10]   : ���� */
        unsigned int  credit_en   : 1;  /* bit[11]   : ��������ʹ�ܡ�
                                                       0��ͨ���������ƽ�ֹ��max_cont��credit_step����ֵ��Ч��
                                                       1��ͨ����������ʹ�ܣ�max_cont��credit_step����ֵ��Ч�� */
        unsigned int  max_cont    : 4;  /* bit[12-15]: credit_mod����0ʱ������������󳤶ȡ�
                                                       0x0������������󳤶ȵ���1��
                                                       0x1������������󳤶ȵ���2��
                                                       ����
                                                       0xF������������󳤶ȵ���16��
                                                       credit_mode����1����2ʱ����ʾ��������ֵ��
                                                       ��λ��512Bytes����ʱ֧��0x0-0xE�� */
        unsigned int  credit_step : 7;  /* bit[16-22]: ͨ���������ƣ�
                                                       0x0��ͨ��ֻ������������󳤶ȿ��ƣ�
                                                       0x1��1/128*ͨ��������
                                                       0x2��2/128*ͨ�������� 
                                                       0x3��3/128*ͨ�������� 
                                                       0x4��4/128*ͨ��������
                                                       0x5��5/128*ͨ��������
                                                       0x6��6/128*ͨ��������
                                                       0x7��7/128*ͨ��������
                                                       0x8��8/128*ͨ��������
                                                       ���� 
                                                       0xFF��127/128*ͨ�������� */
        unsigned int  credit_lth  : 9;  /* bit[23-31]: credit_mode����1����2ʱ����������ֵ����λ��16Bytes�� */
    } reg;
} SOC_DSS_AIF_AIF_CH_CTL_5_UNION;
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_5_axi_sel_START      (0)
#define SOC_DSS_AIF_AIF_CH_CTL_5_axi_sel_END        (0)
#define SOC_DSS_AIF_AIF_CH_CTL_5_max_cmd_START      (1)
#define SOC_DSS_AIF_AIF_CH_CTL_5_max_cmd_END        (3)
#define SOC_DSS_AIF_AIF_CH_CTL_5_mid_START          (4)
#define SOC_DSS_AIF_AIF_CH_CTL_5_mid_END            (7)
#define SOC_DSS_AIF_AIF_CH_CTL_5_credit_mode_START  (8)
#define SOC_DSS_AIF_AIF_CH_CTL_5_credit_mode_END    (9)
#define SOC_DSS_AIF_AIF_CH_CTL_5_credit_en_START    (11)
#define SOC_DSS_AIF_AIF_CH_CTL_5_credit_en_END      (11)
#define SOC_DSS_AIF_AIF_CH_CTL_5_max_cont_START     (12)
#define SOC_DSS_AIF_AIF_CH_CTL_5_max_cont_END       (15)
#define SOC_DSS_AIF_AIF_CH_CTL_5_credit_step_START  (16)
#define SOC_DSS_AIF_AIF_CH_CTL_5_credit_step_END    (22)
#define SOC_DSS_AIF_AIF_CH_CTL_5_credit_lth_START   (23)
#define SOC_DSS_AIF_AIF_CH_CTL_5_credit_lth_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_AIF_AIF_CH_CTL_6_UNION
 �ṹ˵��  : AIF_CH_CTL_6 �Ĵ����ṹ���塣��ַƫ����:0x00c0����ֵ:0x0000�����:32
 �Ĵ���˵��: AIFͨ��6��ͨ�����ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi_sel     : 1;  /* bit[0]    : AXI�˿�ѡ��
                                                       0��ѡ��AXI0��
                                                       1��ѡ��AXI1  */
        unsigned int  reserved_0  : 3;  /* bit[1-3]  : ���� */
        unsigned int  mid         : 4;  /* bit[4-7]  : ͨ����MID��
                                                       0x0~0x9����Ч����ֵ��
                                                       0xA~0xF����ֹ���ã��������ϵͳ��ɲ���Ԥ֪�ĺ���� */
        unsigned int  credit_mode : 2;  /* bit[8-9]  : ����ģʽ��
                                                       0x0����ͨģʽ
                                                       0x1��afbcģʽ����ͨ����Ч��
                                                       0x2������ģʽ
                                                       0x3����Чֵ�� */
        unsigned int  reserved_1  : 1;  /* bit[10]   : ���� */
        unsigned int  credit_en   : 1;  /* bit[11]   : ��������ʹ�ܡ�
                                                       0��ͨ���������ƽ�ֹ��max_cont��credit_step����ֵ��Ч��
                                                       1��ͨ����������ʹ�ܣ�max_cont��credit_step����ֵ��Ч�� */
        unsigned int  max_cont    : 4;  /* bit[12-15]: credit_mod����0ʱ������������󳤶ȡ�
                                                       0x0������������󳤶ȵ���1��
                                                       0x1������������󳤶ȵ���2��
                                                       ����
                                                       0xF������������󳤶ȵ���16��
                                                       credit_mode����1����2ʱ����ʾ��������ֵ��
                                                       ��λ��512Bytes����ʱ֧��0x0-0xE�� */
        unsigned int  credit_step : 7;  /* bit[16-22]: ͨ���������ƣ�
                                                       0x0��ͨ��ֻ������������󳤶ȿ��ƣ�
                                                       0x1��1/128*ͨ��������
                                                       0x2��2/128*ͨ�������� 
                                                       0x3��3/128*ͨ�������� 
                                                       0x4��4/128*ͨ��������
                                                       0x5��5/128*ͨ��������
                                                       0x6��6/128*ͨ��������
                                                       0x7��7/128*ͨ��������
                                                       0x8��8/128*ͨ��������
                                                       ���� 
                                                       0xFF��127/128*ͨ�������� */
        unsigned int  reserved_2  : 9;  /* bit[23-31]: ���� */
    } reg;
} SOC_DSS_AIF_AIF_CH_CTL_6_UNION;
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_6_axi_sel_START      (0)
#define SOC_DSS_AIF_AIF_CH_CTL_6_axi_sel_END        (0)
#define SOC_DSS_AIF_AIF_CH_CTL_6_mid_START          (4)
#define SOC_DSS_AIF_AIF_CH_CTL_6_mid_END            (7)
#define SOC_DSS_AIF_AIF_CH_CTL_6_credit_mode_START  (8)
#define SOC_DSS_AIF_AIF_CH_CTL_6_credit_mode_END    (9)
#define SOC_DSS_AIF_AIF_CH_CTL_6_credit_en_START    (11)
#define SOC_DSS_AIF_AIF_CH_CTL_6_credit_en_END      (11)
#define SOC_DSS_AIF_AIF_CH_CTL_6_max_cont_START     (12)
#define SOC_DSS_AIF_AIF_CH_CTL_6_max_cont_END       (15)
#define SOC_DSS_AIF_AIF_CH_CTL_6_credit_step_START  (16)
#define SOC_DSS_AIF_AIF_CH_CTL_6_credit_step_END    (22)


/*****************************************************************************
 �ṹ��    : SOC_DSS_AIF_AIF_CH_CTL_7_UNION
 �ṹ˵��  : AIF_CH_CTL_7 �Ĵ����ṹ���塣��ַƫ����:0x00e0����ֵ:0x0000�����:32
 �Ĵ���˵��: AIFͨ��7��ͨ�����ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi_sel     : 1;  /* bit[0]    : AXI�˿�ѡ��
                                                       0��ѡ��AXI0��
                                                       1��ѡ��AXI1  */
        unsigned int  reserved_0  : 3;  /* bit[1-3]  : ���� */
        unsigned int  mid         : 4;  /* bit[4-7]  : ͨ����MID��
                                                       0x0~0x9����Ч����ֵ��
                                                       0xA~0xF����ֹ���ã��������ϵͳ��ɲ���Ԥ֪�ĺ���� */
        unsigned int  credit_mode : 2;  /* bit[8-9]  : ����ģʽ��
                                                       0x0����ͨģʽ
                                                       0x1��afbcģʽ����ͨ����Ч��
                                                       0x2������ģʽ
                                                       0x3����Чֵ�� */
        unsigned int  reserved_1  : 1;  /* bit[10]   : ���� */
        unsigned int  credit_en   : 1;  /* bit[11]   : ��������ʹ�ܡ�
                                                       0��ͨ���������ƽ�ֹ��max_cont��credit_step����ֵ��Ч��
                                                       1��ͨ����������ʹ�ܣ�max_cont��credit_step����ֵ��Ч�� */
        unsigned int  max_cont    : 4;  /* bit[12-15]: credit_mod����0ʱ������������󳤶ȡ�
                                                       0x0������������󳤶ȵ���1��
                                                       0x1������������󳤶ȵ���2��
                                                       ����
                                                       0xF������������󳤶ȵ���16��
                                                       credit_mode����1����2ʱ����ʾ��������ֵ��
                                                       ��λ��512Bytes����ʱ֧��0x0-0xE�� */
        unsigned int  credit_step : 7;  /* bit[16-22]: ͨ���������ƣ�
                                                       0x0��ͨ��ֻ������������󳤶ȿ��ƣ�
                                                       0x1��1/128*ͨ��������
                                                       0x2��2/128*ͨ�������� 
                                                       0x3��3/128*ͨ�������� 
                                                       0x4��4/128*ͨ��������
                                                       0x5��5/128*ͨ��������
                                                       0x6��6/128*ͨ��������
                                                       0x7��7/128*ͨ��������
                                                       0x8��8/128*ͨ��������
                                                       ���� 
                                                       0xFF��127/128*ͨ�������� */
        unsigned int  reserved_2  : 9;  /* bit[23-31]: ���� */
    } reg;
} SOC_DSS_AIF_AIF_CH_CTL_7_UNION;
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_7_axi_sel_START      (0)
#define SOC_DSS_AIF_AIF_CH_CTL_7_axi_sel_END        (0)
#define SOC_DSS_AIF_AIF_CH_CTL_7_mid_START          (4)
#define SOC_DSS_AIF_AIF_CH_CTL_7_mid_END            (7)
#define SOC_DSS_AIF_AIF_CH_CTL_7_credit_mode_START  (8)
#define SOC_DSS_AIF_AIF_CH_CTL_7_credit_mode_END    (9)
#define SOC_DSS_AIF_AIF_CH_CTL_7_credit_en_START    (11)
#define SOC_DSS_AIF_AIF_CH_CTL_7_credit_en_END      (11)
#define SOC_DSS_AIF_AIF_CH_CTL_7_max_cont_START     (12)
#define SOC_DSS_AIF_AIF_CH_CTL_7_max_cont_END       (15)
#define SOC_DSS_AIF_AIF_CH_CTL_7_credit_step_START  (16)
#define SOC_DSS_AIF_AIF_CH_CTL_7_credit_step_END    (22)


/*****************************************************************************
 �ṹ��    : SOC_DSS_AIF_AIF_CH_CTL_8_UNION
 �ṹ˵��  : AIF_CH_CTL_8 �Ĵ����ṹ���塣��ַƫ����:0x0100����ֵ:0x0000�����:32
 �Ĵ���˵��: AIFͨ��8��ͨ�����ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi_sel     : 1;  /* bit[0]    : AXI�˿�ѡ��
                                                       0��ѡ��AXI0��
                                                       1��ѡ��AXI1  */
        unsigned int  max_cmd     : 3;  /* bit[1-3]  : credit_mode����1����2ʱ���������������� */
        unsigned int  mid         : 4;  /* bit[4-7]  : ͨ����MID��
                                                       0x0~0x9����Ч����ֵ��
                                                       0xA~0xF����ֹ���ã��������ϵͳ��ɲ���Ԥ֪�ĺ���� */
        unsigned int  credit_mode : 2;  /* bit[8-9]  : ����ģʽ��
                                                       0x0����ͨģʽ
                                                       0x1��afbcģʽ����ͨ����Ч��
                                                       0x2������ģʽ
                                                       0x3����Чֵ�� */
        unsigned int  reserved    : 1;  /* bit[10]   : ���� */
        unsigned int  credit_en   : 1;  /* bit[11]   : ��������ʹ�ܡ�
                                                       0��ͨ���������ƽ�ֹ��max_cont��credit_step����ֵ��Ч��
                                                       1��ͨ����������ʹ�ܣ�max_cont��credit_step����ֵ��Ч�� */
        unsigned int  max_cont    : 4;  /* bit[12-15]: credit_mod����0ʱ������������󳤶ȡ�
                                                       0x0������������󳤶ȵ���1��
                                                       0x1������������󳤶ȵ���2��
                                                       ����
                                                       0xF������������󳤶ȵ���16��
                                                       credit_mode����1����2ʱ����ʾ��������ֵ��
                                                       ��λ��512Bytes����ʱ֧��0x0-0xE�� */
        unsigned int  credit_step : 7;  /* bit[16-22]: ͨ���������ƣ�
                                                       0x0��ͨ��ֻ������������󳤶ȿ��ƣ�
                                                       0x1��1/128*ͨ��������
                                                       0x2��2/128*ͨ�������� 
                                                       0x3��3/128*ͨ�������� 
                                                       0x4��4/128*ͨ��������
                                                       0x5��5/128*ͨ��������
                                                       0x6��6/128*ͨ��������
                                                       0x7��7/128*ͨ��������
                                                       0x8��8/128*ͨ��������
                                                       ���� 
                                                       0xFF��127/128*ͨ�������� */
        unsigned int  credit_lth  : 9;  /* bit[23-31]: credit_mode����1����2ʱ����������ֵ����λ��16Bytes�� */
    } reg;
} SOC_DSS_AIF_AIF_CH_CTL_8_UNION;
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_8_axi_sel_START      (0)
#define SOC_DSS_AIF_AIF_CH_CTL_8_axi_sel_END        (0)
#define SOC_DSS_AIF_AIF_CH_CTL_8_max_cmd_START      (1)
#define SOC_DSS_AIF_AIF_CH_CTL_8_max_cmd_END        (3)
#define SOC_DSS_AIF_AIF_CH_CTL_8_mid_START          (4)
#define SOC_DSS_AIF_AIF_CH_CTL_8_mid_END            (7)
#define SOC_DSS_AIF_AIF_CH_CTL_8_credit_mode_START  (8)
#define SOC_DSS_AIF_AIF_CH_CTL_8_credit_mode_END    (9)
#define SOC_DSS_AIF_AIF_CH_CTL_8_credit_en_START    (11)
#define SOC_DSS_AIF_AIF_CH_CTL_8_credit_en_END      (11)
#define SOC_DSS_AIF_AIF_CH_CTL_8_max_cont_START     (12)
#define SOC_DSS_AIF_AIF_CH_CTL_8_max_cont_END       (15)
#define SOC_DSS_AIF_AIF_CH_CTL_8_credit_step_START  (16)
#define SOC_DSS_AIF_AIF_CH_CTL_8_credit_step_END    (22)
#define SOC_DSS_AIF_AIF_CH_CTL_8_credit_lth_START   (23)
#define SOC_DSS_AIF_AIF_CH_CTL_8_credit_lth_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_AIF_AIF_CH_CTL_9_UNION
 �ṹ˵��  : AIF_CH_CTL_9 �Ĵ����ṹ���塣��ַƫ����:0x0120����ֵ:0x0000�����:32
 �Ĵ���˵��: AIFͨ��9��ͨ�����ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi_sel     : 1;  /* bit[0]    : AXI�˿�ѡ��
                                                       0��ѡ��AXI0��
                                                       1��ѡ��AXI1  */
        unsigned int  max_cmd     : 3;  /* bit[1-3]  : credit_mode����1����2ʱ���������������� */
        unsigned int  mid         : 4;  /* bit[4-7]  : ͨ����MID��
                                                       0x0~0x9����Ч����ֵ��
                                                       0xA~0xF����ֹ���ã��������ϵͳ��ɲ���Ԥ֪�ĺ���� */
        unsigned int  credit_mode : 2;  /* bit[8-9]  : ����ģʽ��
                                                       0x0����ͨģʽ
                                                       0x1��afbcģʽ����ͨ����Ч��
                                                       0x2������ģʽ
                                                       0x3����Чֵ�� */
        unsigned int  reserved    : 1;  /* bit[10]   : ���� */
        unsigned int  credit_en   : 1;  /* bit[11]   : ��������ʹ�ܡ�
                                                       0��ͨ���������ƽ�ֹ��max_cont��credit_step����ֵ��Ч��
                                                       1��ͨ����������ʹ�ܣ�max_cont��credit_step����ֵ��Ч�� */
        unsigned int  max_cont    : 4;  /* bit[12-15]: credit_mod����0ʱ������������󳤶ȡ�
                                                       0x0������������󳤶ȵ���1��
                                                       0x1������������󳤶ȵ���2��
                                                       ����
                                                       0xF������������󳤶ȵ���16��
                                                       credit_mode����1����2ʱ����ʾ��������ֵ��
                                                       ��λ��512Bytes����ʱ֧��0x0-0xE�� */
        unsigned int  credit_step : 7;  /* bit[16-22]: ͨ���������ƣ�
                                                       0x0��ͨ��ֻ������������󳤶ȿ��ƣ�
                                                       0x1��1/128*ͨ��������
                                                       0x2��2/128*ͨ�������� 
                                                       0x3��3/128*ͨ�������� 
                                                       0x4��4/128*ͨ��������
                                                       0x5��5/128*ͨ��������
                                                       0x6��6/128*ͨ��������
                                                       0x7��7/128*ͨ��������
                                                       0x8��8/128*ͨ��������
                                                       ���� 
                                                       0xFF��127/128*ͨ�������� */
        unsigned int  credit_lth  : 9;  /* bit[23-31]: credit_mode����1����2ʱ����������ֵ����λ��16Bytes�� */
    } reg;
} SOC_DSS_AIF_AIF_CH_CTL_9_UNION;
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_9_axi_sel_START      (0)
#define SOC_DSS_AIF_AIF_CH_CTL_9_axi_sel_END        (0)
#define SOC_DSS_AIF_AIF_CH_CTL_9_max_cmd_START      (1)
#define SOC_DSS_AIF_AIF_CH_CTL_9_max_cmd_END        (3)
#define SOC_DSS_AIF_AIF_CH_CTL_9_mid_START          (4)
#define SOC_DSS_AIF_AIF_CH_CTL_9_mid_END            (7)
#define SOC_DSS_AIF_AIF_CH_CTL_9_credit_mode_START  (8)
#define SOC_DSS_AIF_AIF_CH_CTL_9_credit_mode_END    (9)
#define SOC_DSS_AIF_AIF_CH_CTL_9_credit_en_START    (11)
#define SOC_DSS_AIF_AIF_CH_CTL_9_credit_en_END      (11)
#define SOC_DSS_AIF_AIF_CH_CTL_9_max_cont_START     (12)
#define SOC_DSS_AIF_AIF_CH_CTL_9_max_cont_END       (15)
#define SOC_DSS_AIF_AIF_CH_CTL_9_credit_step_START  (16)
#define SOC_DSS_AIF_AIF_CH_CTL_9_credit_step_END    (22)
#define SOC_DSS_AIF_AIF_CH_CTL_9_credit_lth_START   (23)
#define SOC_DSS_AIF_AIF_CH_CTL_9_credit_lth_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_AIF_AIF_CH_CTL_10_UNION
 �ṹ˵��  : AIF_CH_CTL_10 �Ĵ����ṹ���塣��ַƫ����:0x0140����ֵ:0x0000�����:32
 �Ĵ���˵��: AIFͨ��10��ͨ�����ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi_sel     : 1;  /* bit[0]    : AXI�˿�ѡ��
                                                       0��ѡ��AXI0��
                                                       1��ѡ��AXI1  */
        unsigned int  reserved_0  : 3;  /* bit[1-3]  : ���� */
        unsigned int  mid         : 4;  /* bit[4-7]  : ͨ����MID��
                                                       0x0~0x9����Ч����ֵ��
                                                       0xA~0xF����ֹ���ã��������ϵͳ��ɲ���Ԥ֪�ĺ���� */
        unsigned int  credit_mode : 2;  /* bit[8-9]  : ����ģʽ��
                                                       0x0����ͨģʽ
                                                       0x1��afbcģʽ����ͨ����Ч��
                                                       0x2������ģʽ
                                                       0x3����Чֵ�� */
        unsigned int  reserved_1  : 1;  /* bit[10]   : ���� */
        unsigned int  credit_en   : 1;  /* bit[11]   : ��������ʹ�ܡ�
                                                       0��ͨ���������ƽ�ֹ��max_cont��credit_step����ֵ��Ч��
                                                       1��ͨ����������ʹ�ܣ�max_cont��credit_step����ֵ��Ч�� */
        unsigned int  max_cont    : 4;  /* bit[12-15]: credit_mod����0ʱ������������󳤶ȡ�
                                                       0x0������������󳤶ȵ���1��
                                                       0x1������������󳤶ȵ���2��
                                                       ����
                                                       0xF������������󳤶ȵ���16��
                                                       credit_mode����1����2ʱ����ʾ��������ֵ��
                                                       ��λ��512Bytes����ʱ֧��0x0-0xE�� */
        unsigned int  credit_step : 7;  /* bit[16-22]: ͨ���������ƣ�
                                                       0x0��ͨ��ֻ������������󳤶ȿ��ƣ�
                                                       0x1��1/128*ͨ��������
                                                       0x2��2/128*ͨ�������� 
                                                       0x3��3/128*ͨ�������� 
                                                       0x4��4/128*ͨ��������
                                                       0x5��5/128*ͨ��������
                                                       0x6��6/128*ͨ��������
                                                       0x7��7/128*ͨ��������
                                                       0x8��8/128*ͨ��������
                                                       ���� 
                                                       0xFF��127/128*ͨ�������� */
        unsigned int  reserved_2  : 9;  /* bit[23-31]: ���� */
    } reg;
} SOC_DSS_AIF_AIF_CH_CTL_10_UNION;
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_10_axi_sel_START      (0)
#define SOC_DSS_AIF_AIF_CH_CTL_10_axi_sel_END        (0)
#define SOC_DSS_AIF_AIF_CH_CTL_10_mid_START          (4)
#define SOC_DSS_AIF_AIF_CH_CTL_10_mid_END            (7)
#define SOC_DSS_AIF_AIF_CH_CTL_10_credit_mode_START  (8)
#define SOC_DSS_AIF_AIF_CH_CTL_10_credit_mode_END    (9)
#define SOC_DSS_AIF_AIF_CH_CTL_10_credit_en_START    (11)
#define SOC_DSS_AIF_AIF_CH_CTL_10_credit_en_END      (11)
#define SOC_DSS_AIF_AIF_CH_CTL_10_max_cont_START     (12)
#define SOC_DSS_AIF_AIF_CH_CTL_10_max_cont_END       (15)
#define SOC_DSS_AIF_AIF_CH_CTL_10_credit_step_START  (16)
#define SOC_DSS_AIF_AIF_CH_CTL_10_credit_step_END    (22)


/*****************************************************************************
 �ṹ��    : SOC_DSS_AIF_AXI0_RID_MSK0_UNION
 �ṹ˵��  : AXI0_RID_MSK0 �Ĵ����ṹ���塣��ַƫ����:0x0800����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: AXI0 Read ID Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi0_rid_msk0 : 32; /* bit[0-31]: AXI0���˿�ID_MAP��0~31bit Maskλ��Ϊ0��ʾ��Ӧ��ID�������䣬Ϊ1��ʾ��Ӧ��ID�ɷ��䡣 */
    } reg;
} SOC_DSS_AIF_AXI0_RID_MSK0_UNION;
#endif
#define SOC_DSS_AIF_AXI0_RID_MSK0_axi0_rid_msk0_START  (0)
#define SOC_DSS_AIF_AXI0_RID_MSK0_axi0_rid_msk0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_AIF_AXI0_RID_MSK1_UNION
 �ṹ˵��  : AXI0_RID_MSK1 �Ĵ����ṹ���塣��ַƫ����:0x0804����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: AXI0 Read ID Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi0_rid_msk1 : 32; /* bit[0-31]: AXI0���˿�ID_MAP��31~63bit Maskλ��Ϊ0��ʾ��Ӧ��ID�������䣬Ϊ1��ʾ��Ӧ��ID�ɷ��䡣 */
    } reg;
} SOC_DSS_AIF_AXI0_RID_MSK1_UNION;
#endif
#define SOC_DSS_AIF_AXI0_RID_MSK1_axi0_rid_msk1_START  (0)
#define SOC_DSS_AIF_AXI0_RID_MSK1_axi0_rid_msk1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_AIF_AXI0_WID_MSK_UNION
 �ṹ˵��  : AXI0_WID_MSK �Ĵ����ṹ���塣��ַƫ����:0x0808����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: AXI0 Read ID Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi0_wid_msk : 32; /* bit[0-31]: AXI0���˿�ID_MAP��0~31bit Maskλ��Ϊ0��ʾ��Ӧ��ID�������䣬Ϊ1��ʾ��Ӧ��ID�ɷ��䡣 */
    } reg;
} SOC_DSS_AIF_AXI0_WID_MSK_UNION;
#endif
#define SOC_DSS_AIF_AXI0_WID_MSK_axi0_wid_msk_START  (0)
#define SOC_DSS_AIF_AXI0_WID_MSK_axi0_wid_msk_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_AIF_AXI0_R_QOS_MAP_UNION
 �ṹ˵��  : AXI0_R_QOS_MAP �Ĵ����ṹ���塣��ַƫ����:0x080c����ֵ:0xE4E4E4E4�����:32
 �Ĵ���˵��: AXI0 Read QOS remap
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi0_rd_qos_map : 8;  /* bit[0-7]  : AXI0���˿�QOS��ӳ���
                                                           [1:0]������Ϊ2'b00ʱ��ӳ��ֵ��
                                                           [3:2]������Ϊ2'b01ʱ��ӳ��ֵ��
                                                           [5:4]������Ϊ2'b10ʱ��ӳ��ֵ��
                                                           [7:6]: ����Ϊ2'b11ʱ��ӳ��ֵ�� */
        unsigned int  axi0_wr_qos_map : 8;  /* bit[8-15] : AXI0д�˿�QOS��ӳ���
                                                           [1:0]������Ϊ2'b00ʱ��ӳ��ֵ��
                                                           [3:2]������Ϊ2'b01ʱ��ӳ��ֵ��
                                                           [5:4]������Ϊ2'b10ʱ��ӳ��ֵ��
                                                           [7:6]: ����Ϊ2'b11ʱ��ӳ��ֵ�� */
        unsigned int  axi0_rd_prs_map : 8;  /* bit[16-23]: AXI0���˿�Mainpress��ӳ���
                                                           [1:0]������Ϊ2'b00ʱ��ӳ��ֵ��
                                                           [3:2]������Ϊ2'b01ʱ��ӳ��ֵ��
                                                           [5:4]������Ϊ2'b10ʱ��ӳ��ֵ��
                                                           [7:6]: ����Ϊ2'b11ʱ��ӳ��ֵ�� */
        unsigned int  axi0_wr_prs_map : 8;  /* bit[24-31]: AXI0д�˿�Mainpress��ӳ���
                                                           [1:0]������Ϊ2'b00ʱ��ӳ��ֵ��
                                                           [3:2]������Ϊ2'b01ʱ��ӳ��ֵ��
                                                           [5:4]������Ϊ2'b10ʱ��ӳ��ֵ��
                                                           [7:6]: ����Ϊ2'b11ʱ��ӳ��ֵ�� */
    } reg;
} SOC_DSS_AIF_AXI0_R_QOS_MAP_UNION;
#endif
#define SOC_DSS_AIF_AXI0_R_QOS_MAP_axi0_rd_qos_map_START  (0)
#define SOC_DSS_AIF_AXI0_R_QOS_MAP_axi0_rd_qos_map_END    (7)
#define SOC_DSS_AIF_AXI0_R_QOS_MAP_axi0_wr_qos_map_START  (8)
#define SOC_DSS_AIF_AXI0_R_QOS_MAP_axi0_wr_qos_map_END    (15)
#define SOC_DSS_AIF_AXI0_R_QOS_MAP_axi0_rd_prs_map_START  (16)
#define SOC_DSS_AIF_AXI0_R_QOS_MAP_axi0_rd_prs_map_END    (23)
#define SOC_DSS_AIF_AXI0_R_QOS_MAP_axi0_wr_prs_map_START  (24)
#define SOC_DSS_AIF_AXI0_R_QOS_MAP_axi0_wr_prs_map_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_AIF_AXI1_RID_MSK0_UNION
 �ṹ˵��  : AXI1_RID_MSK0 �Ĵ����ṹ���塣��ַƫ����:0x0810����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: AXI1 Read ID Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi1_rid_msk0 : 32; /* bit[0-31]: AXI1���˿�ID_MAP��0~31bit Maskλ��Ϊ0��ʾ��Ӧ��ID�������䣬Ϊ1��ʾ��Ӧ��ID�ɷ��䡣 */
    } reg;
} SOC_DSS_AIF_AXI1_RID_MSK0_UNION;
#endif
#define SOC_DSS_AIF_AXI1_RID_MSK0_axi1_rid_msk0_START  (0)
#define SOC_DSS_AIF_AXI1_RID_MSK0_axi1_rid_msk0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_AIF_AXI1_RID_MSK1_UNION
 �ṹ˵��  : AXI1_RID_MSK1 �Ĵ����ṹ���塣��ַƫ����:0x0814����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: AXI1 Read ID Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi1_rid_msk1 : 32; /* bit[0-31]: AXI1���˿�ID_MAP��31~63bit Maskλ��Ϊ0��ʾ��Ӧ��ID�������䣬Ϊ1��ʾ��Ӧ��ID�ɷ��䡣 */
    } reg;
} SOC_DSS_AIF_AXI1_RID_MSK1_UNION;
#endif
#define SOC_DSS_AIF_AXI1_RID_MSK1_axi1_rid_msk1_START  (0)
#define SOC_DSS_AIF_AXI1_RID_MSK1_axi1_rid_msk1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_AIF_AXI1_WID_MSK_UNION
 �ṹ˵��  : AXI1_WID_MSK �Ĵ����ṹ���塣��ַƫ����:0x0818����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: AXI1 Read ID Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi1_wid_msk : 32; /* bit[0-31]: AXI1д�˿�ID_MAP��0~31bit Maskλ��Ϊ0��ʾ��Ӧ��ID�������䣬Ϊ1��ʾ��Ӧ��ID�ɷ��䡣 */
    } reg;
} SOC_DSS_AIF_AXI1_WID_MSK_UNION;
#endif
#define SOC_DSS_AIF_AXI1_WID_MSK_axi1_wid_msk_START  (0)
#define SOC_DSS_AIF_AXI1_WID_MSK_axi1_wid_msk_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_AIF_AXI1_R_QOS_MAP_UNION
 �ṹ˵��  : AXI1_R_QOS_MAP �Ĵ����ṹ���塣��ַƫ����:0x081c����ֵ:0xE4E4E4E4�����:32
 �Ĵ���˵��: AXI1 Read QOS remap
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi1_rd_qos_map : 8;  /* bit[0-7]  : AXI1���˿�QOS��ӳ���
                                                           [1:0]������Ϊ2'b00ʱ��ӳ��ֵ��
                                                           [3:2]������Ϊ2'b01ʱ��ӳ��ֵ��
                                                           [5:4]������Ϊ2'b10ʱ��ӳ��ֵ��
                                                           [7:6]: ����Ϊ2'b11ʱ��ӳ��ֵ�� */
        unsigned int  axi1_wr_qos_map : 8;  /* bit[8-15] : AXI0д�˿�QOS��ӳ���
                                                           [1:0]������Ϊ2'b00ʱ��ӳ��ֵ��
                                                           [3:2]������Ϊ2'b01ʱ��ӳ��ֵ��
                                                           [5:4]������Ϊ2'b10ʱ��ӳ��ֵ��
                                                           [7:6]: ����Ϊ2'b11ʱ��ӳ��ֵ�� */
        unsigned int  axi1_rd_prs_map : 8;  /* bit[16-23]: AXI0���˿�Mainpress��ӳ���
                                                           [1:0]������Ϊ2'b00ʱ��ӳ��ֵ��
                                                           [3:2]������Ϊ2'b01ʱ��ӳ��ֵ��
                                                           [5:4]������Ϊ2'b10ʱ��ӳ��ֵ��
                                                           [7:6]: ����Ϊ2'b11ʱ��ӳ��ֵ�� */
        unsigned int  axi1_wr_prs_map : 8;  /* bit[24-31]: AXI0д�˿�Mainpress��ӳ���
                                                           [1:0]������Ϊ2'b00ʱ��ӳ��ֵ��
                                                           [3:2]������Ϊ2'b01ʱ��ӳ��ֵ��
                                                           [5:4]������Ϊ2'b10ʱ��ӳ��ֵ��
                                                           [7:6]: ����Ϊ2'b11ʱ��ӳ��ֵ�� */
    } reg;
} SOC_DSS_AIF_AXI1_R_QOS_MAP_UNION;
#endif
#define SOC_DSS_AIF_AXI1_R_QOS_MAP_axi1_rd_qos_map_START  (0)
#define SOC_DSS_AIF_AXI1_R_QOS_MAP_axi1_rd_qos_map_END    (7)
#define SOC_DSS_AIF_AXI1_R_QOS_MAP_axi1_wr_qos_map_START  (8)
#define SOC_DSS_AIF_AXI1_R_QOS_MAP_axi1_wr_qos_map_END    (15)
#define SOC_DSS_AIF_AXI1_R_QOS_MAP_axi1_rd_prs_map_START  (16)
#define SOC_DSS_AIF_AXI1_R_QOS_MAP_axi1_rd_prs_map_END    (23)
#define SOC_DSS_AIF_AXI1_R_QOS_MAP_axi1_wr_prs_map_START  (24)
#define SOC_DSS_AIF_AXI1_R_QOS_MAP_axi1_wr_prs_map_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_AIF_AIF_CLK_SEL0_UNION
 �ṹ˵��  : AIF_CLK_SEL0 �Ĵ����ṹ���塣��ַƫ����:0x0820����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: AIFģ��ʱ��ѡ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  aif_clk_sel0 : 32; /* bit[0-31]: ��һ��ģ���ʱ��ѡ���źţ�
                                                       1����ʾǿ�ƴ�ʱ�ӡ�
                                                       0����ʾ��Ҫ���������Ӳ����ʱ��ʹ����������ر�ʱ�� */
    } reg;
} SOC_DSS_AIF_AIF_CLK_SEL0_UNION;
#endif
#define SOC_DSS_AIF_AIF_CLK_SEL0_aif_clk_sel0_START  (0)
#define SOC_DSS_AIF_AIF_CLK_SEL0_aif_clk_sel0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_AIF_AIF_CLK_SEL1_UNION
 �ṹ˵��  : AIF_CLK_SEL1 �Ĵ����ṹ���塣��ַƫ����:0x0824����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: AIFģ��ʱ��ѡ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  aif_clk_sel1 : 32; /* bit[0-31]: ��һ��ģ���ʱ��ѡ���źţ�
                                                       1����ʾǿ�ƴ�ʱ�ӡ�
                                                       0����ʾ��Ҫ���������Ӳ����ʱ��ʹ����������ر�ʱ�� */
    } reg;
} SOC_DSS_AIF_AIF_CLK_SEL1_UNION;
#endif
#define SOC_DSS_AIF_AIF_CLK_SEL1_aif_clk_sel1_START  (0)
#define SOC_DSS_AIF_AIF_CLK_SEL1_aif_clk_sel1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_AIF_AIF_CLK_EN0_UNION
 �ṹ˵��  : AIF_CLK_EN0 �Ĵ����ṹ���塣��ַƫ����:0x0828����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: AIFģ��ʱ��ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  aif_clk_en0 : 32; /* bit[0-31]: ��һ��ģ������ʱ��ʹ���ź�
                                                      1����ʾ���ʱ��ʹ����Ч������Ӳ������
                                                      0����ʾ���ʱ��ʹ����Ч����ֹӲ������ */
    } reg;
} SOC_DSS_AIF_AIF_CLK_EN0_UNION;
#endif
#define SOC_DSS_AIF_AIF_CLK_EN0_aif_clk_en0_START  (0)
#define SOC_DSS_AIF_AIF_CLK_EN0_aif_clk_en0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_AIF_AIF_CLK_EN1_UNION
 �ṹ˵��  : AIF_CLK_EN1 �Ĵ����ṹ���塣��ַƫ����:0x082c����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: AIFģ��ʱ��ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  aif_clk_en1 : 32; /* bit[0-31]: ��һ��ģ������ʱ��ʹ���ź�
                                                      1����ʾ���ʱ��ʹ����Ч������Ӳ������
                                                      0����ʾ���ʱ��ʹ����Ч����ֹӲ������ */
    } reg;
} SOC_DSS_AIF_AIF_CLK_EN1_UNION;
#endif
#define SOC_DSS_AIF_AIF_CLK_EN1_aif_clk_en1_START  (0)
#define SOC_DSS_AIF_AIF_CLK_EN1_aif_clk_en1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_AIF_MONITOR_CTRL_UNION
 �ṹ˵��  : MONITOR_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0830����ֵ:0x00000000�����:32
 �Ĵ���˵��: monitor���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_run      : 1;  /* bit[0]   : monitorʹ�ܡ�
                                                           0��monitor��ʹ�ܣ�
                                                           1��monitorʹ�ܣ� */
        unsigned int  reserved_0       : 3;  /* bit[1-3] : ������ */
        unsigned int  monitor_streamid : 4;  /* bit[4-7] : monitor��Ӧ��streamid */
        unsigned int  reserved_1       : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_DSS_AIF_MONITOR_CTRL_UNION;
#endif
#define SOC_DSS_AIF_MONITOR_CTRL_monitor_run_START       (0)
#define SOC_DSS_AIF_MONITOR_CTRL_monitor_run_END         (0)
#define SOC_DSS_AIF_MONITOR_CTRL_monitor_streamid_START  (4)
#define SOC_DSS_AIF_MONITOR_CTRL_monitor_streamid_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_AIF_MONITOR_TIMER_INI_UNION
 �ṹ˵��  : MONITOR_TIMER_INI �Ĵ����ṹ���塣��ַƫ����:0x0834����ֵ:0x00000000�����:32
 �Ĵ���˵��: monitor��ʱ����ʼֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_ini : 32; /* bit[0-31]: monitor��ʱ����ʼֵ */
    } reg;
} SOC_DSS_AIF_MONITOR_TIMER_INI_UNION;
#endif
#define SOC_DSS_AIF_MONITOR_TIMER_INI_monitor_ini_START  (0)
#define SOC_DSS_AIF_MONITOR_TIMER_INI_monitor_ini_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_AIF_DEBUG_BUF_BASE_UNION
 �ṹ˵��  : DEBUG_BUF_BASE �Ĵ����ṹ���塣��ַƫ����:0x0838����ֵ:0x00000000�����:32
 �Ĵ���˵��: debug buffer����ַ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved   : 4;  /* bit[0-3] : ���� */
        unsigned int  debug_base : 28; /* bit[4-31]: debug buffer����ַ��16Bytes���롣 */
    } reg;
} SOC_DSS_AIF_DEBUG_BUF_BASE_UNION;
#endif
#define SOC_DSS_AIF_DEBUG_BUF_BASE_debug_base_START  (4)
#define SOC_DSS_AIF_DEBUG_BUF_BASE_debug_base_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_AIF_DEBUG_CTRL_UNION
 �ṹ˵��  : DEBUG_CTRL �Ĵ����ṹ���塣��ַƫ����:0x083C����ֵ:0x00000000�����:32
 �Ĵ���˵��: debug���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  debug_en    : 1;  /* bit[0]    : debug DMAʹ�� */
        unsigned int  reserved    : 15; /* bit[1-15] : ���� */
        unsigned int  debug_depth : 16; /* bit[16-31]: debug���-1����ȱ���16Bytes���롣 */
    } reg;
} SOC_DSS_AIF_DEBUG_CTRL_UNION;
#endif
#define SOC_DSS_AIF_DEBUG_CTRL_debug_en_START     (0)
#define SOC_DSS_AIF_DEBUG_CTRL_debug_en_END       (0)
#define SOC_DSS_AIF_DEBUG_CTRL_debug_depth_START  (16)
#define SOC_DSS_AIF_DEBUG_CTRL_debug_depth_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_AIF_AIF_SHADOW_READ_UNION
 �ṹ˵��  : AIF_SHADOW_READ �Ĵ����ṹ���塣��ַƫ����:0x0840����ֵ:0x00000000�����:32
 �Ĵ���˵��: Ӱ�ӼĴ�����ѡ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  aif_rd_shadow : 1;  /* bit[0]   : 1'b0 :�������Ĵ���
                                                        1'b1 :��Ӱ�ӼĴ��� */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_AIF_AIF_SHADOW_READ_UNION;
#endif
#define SOC_DSS_AIF_AIF_SHADOW_READ_aif_rd_shadow_START  (0)
#define SOC_DSS_AIF_AIF_SHADOW_READ_aif_rd_shadow_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_AIF_AIF_MEM_CTRL_UNION
 �ṹ˵��  : AIF_MEM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0844����ֵ:0x00000A18�����:32
 �Ĵ���˵��: AIFͨ��SRAM���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mem_ctrl : 16; /* bit[0-15] : Two Port����MEM�͹����������ģʽ����Ч��
                                                    [9:7]: KP,Ĭ��Ϊ3'b011;
                                                    [6:5]: WCT,Ĭ��Ϊ2'b01;
                                                    [4:3]: RCT,Ĭ��Ϊ2'b01;;
                                                    [2]: Ϊ1��ʾ����Shut Downģʽ
                                                    [1]: Ϊ1��ʾ����Deep Sleepģʽ
                                                    [0]: Ϊ1��ʾ����Sleepģʽ */
        unsigned int  reserved : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_DSS_AIF_AIF_MEM_CTRL_UNION;
#endif
#define SOC_DSS_AIF_AIF_MEM_CTRL_mem_ctrl_START  (0)
#define SOC_DSS_AIF_AIF_MEM_CTRL_mem_ctrl_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_DSS_AIF_AXI_REC_A_m_UNION
 �ṹ˵��  : AXI_REC_A_m �Ĵ����ṹ���塣��ַƫ����:0x0880+0x10*(m)����ֵ:0x00000000�����:32
 �Ĵ���˵��: AXI recorder part a
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  length : 3;  /* bit[0-2] : burst length */
        unsigned int  rw     : 1;  /* bit[3]   : ��д��־��
                                                 0������
                                                 1��д */
        unsigned int  addr   : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_DSS_AIF_AXI_REC_A_m_UNION;
#endif
#define SOC_DSS_AIF_AXI_REC_A_m_length_START  (0)
#define SOC_DSS_AIF_AXI_REC_A_m_length_END    (2)
#define SOC_DSS_AIF_AXI_REC_A_m_rw_START      (3)
#define SOC_DSS_AIF_AXI_REC_A_m_rw_END        (3)
#define SOC_DSS_AIF_AXI_REC_A_m_addr_START    (4)
#define SOC_DSS_AIF_AXI_REC_A_m_addr_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_AIF_AXI_REC_B_m_UNION
 �ṹ˵��  : AXI_REC_B_m �Ĵ����ṹ���塣��ַƫ����:0x0884+0x10*(m)����ֵ:0x00000000�����:32
 �Ĵ���˵��: AXI recorder part b
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id          : 16; /* bit[0-15] : ����id */
        unsigned int  prs         : 2;  /* bit[16-17]: ͨ��mainpress�ź� */
        unsigned int  qos         : 2;  /* bit[18-19]: ����qos�ź� */
        unsigned int  user        : 4;  /* bit[20-23]: ͨ�����user�ź� */
        unsigned int  prot        : 3;  /* bit[24-26]: ͨ�����prot�ź� */
        unsigned int  reserved    : 1;  /* bit[27]   : ���� */
        unsigned int  response    : 2;  /* bit[28-29]: �����response */
        unsigned int  rec_axi_sel : 1;  /* bit[30]   : axiѡ��
                                                       0��axi0��
                                                       1��axi1 */
        unsigned int  recd_vld    : 1;  /* bit[31]   : ��¼��Ч��־ */
    } reg;
} SOC_DSS_AIF_AXI_REC_B_m_UNION;
#endif
#define SOC_DSS_AIF_AXI_REC_B_m_id_START           (0)
#define SOC_DSS_AIF_AXI_REC_B_m_id_END             (15)
#define SOC_DSS_AIF_AXI_REC_B_m_prs_START          (16)
#define SOC_DSS_AIF_AXI_REC_B_m_prs_END            (17)
#define SOC_DSS_AIF_AXI_REC_B_m_qos_START          (18)
#define SOC_DSS_AIF_AXI_REC_B_m_qos_END            (19)
#define SOC_DSS_AIF_AXI_REC_B_m_user_START         (20)
#define SOC_DSS_AIF_AXI_REC_B_m_user_END           (23)
#define SOC_DSS_AIF_AXI_REC_B_m_prot_START         (24)
#define SOC_DSS_AIF_AXI_REC_B_m_prot_END           (26)
#define SOC_DSS_AIF_AXI_REC_B_m_response_START     (28)
#define SOC_DSS_AIF_AXI_REC_B_m_response_END       (29)
#define SOC_DSS_AIF_AXI_REC_B_m_rec_axi_sel_START  (30)
#define SOC_DSS_AIF_AXI_REC_B_m_rec_axi_sel_END    (30)
#define SOC_DSS_AIF_AXI_REC_B_m_recd_vld_START     (31)
#define SOC_DSS_AIF_AXI_REC_B_m_recd_vld_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_AIF_AXI_REC_C_m_UNION
 �ṹ˵��  : AXI_REC_C_m �Ĵ����ṹ���塣��ַƫ����:0x0888+0x10*(m)����ֵ:0x00000000�����:32
 �Ĵ���˵��: AXI recorder part c
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi_rec_begin : 32; /* bit[0-31]: ������ʼʱ��� */
    } reg;
} SOC_DSS_AIF_AXI_REC_C_m_UNION;
#endif
#define SOC_DSS_AIF_AXI_REC_C_m_axi_rec_begin_START  (0)
#define SOC_DSS_AIF_AXI_REC_C_m_axi_rec_begin_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_AIF_AXI_REC_D_m_UNION
 �ṹ˵��  : AXI_REC_D_m �Ĵ����ṹ���塣��ַƫ����:0x088C+0x10*(m)����ֵ:0x00000000�����:32
 �Ĵ���˵��: AXI recorder part d
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi_rec_end : 32; /* bit[0-31]: �������ʱ��� */
    } reg;
} SOC_DSS_AIF_AXI_REC_D_m_UNION;
#endif
#define SOC_DSS_AIF_AXI_REC_D_m_axi_rec_end_START  (0)
#define SOC_DSS_AIF_AXI_REC_D_m_axi_rec_end_END    (31)






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

#endif /* end of soc_dss_aif_interface.h */
