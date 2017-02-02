/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_mmbuf_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:22:18
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_MMBUF.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_MMBUF_INTERFACE_H__
#define __SOC_MMBUF_INTERFACE_H__

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
/* �Ĵ���˵����SMC Lock�Ĵ�����
   λ����UNION�ṹ:  SOC_MMBUF_SMC_LOCK_UNION */
#define SOC_MMBUF_SMC_LOCK_ADDR(base)                 ((base) + (0x0000))

/* �Ĵ���˵����SRAM�͹���light sleepʱ����ƼĴ�����
   λ����UNION�ṹ:  SOC_MMBUF_SMC_MEM_LP_UNION */
#define SOC_MMBUF_SMC_MEM_LP_ADDR(base)               ((base) + (0x0004))

/* �Ĵ���˵����AXI slave ��clock gate���á�
   λ����UNION�ṹ:  SOC_MMBUF_GCLK_CS_UNION */
#define SOC_MMBUF_GCLK_CS_ADDR(base)                  ((base) + (0x000C))

/* �Ĵ���˵����Slave��QOS�����޸ļĴ�����
   λ����UNION�ṹ:  SOC_MMBUF_SMC_QOS_BACKDOOR_UNION */
#define SOC_MMBUF_SMC_QOS_BACKDOOR_ADDR(base)         ((base) + (0x0010))

/* �Ĵ���˵������ʣ���δ��ɵ�AXI����������λΪAXI���
   λ����UNION�ṹ:  SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_UNION */
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_ADDR(base)     ((base) + (0x0014))

/* �Ĵ���˵������ʣ���δ��ɵ�AXI����������λΪAXI���
   λ����UNION�ṹ:  SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_UNION */
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_ADDR(base)     ((base) + (0x0018))

/* �Ĵ���˵������ʣ���δ��ɵ�AXI����������λΪAXI���
   λ����UNION�ṹ:  SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_UNION */
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_ADDR(base)     ((base) + (0x001C))

/* �Ĵ���˵������ʣ���δ��ɵ�AXI����������λΪAXI���
   λ����UNION�ṹ:  SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_UNION */
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_ADDR(base)     ((base) + (0x0020))

/* �Ĵ���˵������ʣ���δ��ɵ�AXI����������λΪAXI���
   λ����UNION�ṹ:  SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_UNION */
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_ADDR(base)     ((base) + (0x0024))

/* �Ĵ���˵������ʣ���δ��ɵ�AXI����������λΪAXI���
   λ����UNION�ṹ:  SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_UNION */
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_ADDR(base)     ((base) + (0x0028))

/* �Ĵ���˵������ʣ���δ��ɵ�AXI����������λΪAXI���
   λ����UNION�ṹ:  SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_UNION */
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_ADDR(base)     ((base) + (0x002C))

/* �Ĵ���˵������ʣ���δ��ɵ�AXI����������λΪAXI���
   λ����UNION�ṹ:  SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_UNION */
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_ADDR(base)     ((base) + (0x0030))

/* �Ĵ���˵����AXI slave�ڵ�״̬��
   λ����UNION�ṹ:  SOC_MMBUF_SMC_CS_IDLE_UNION */
#define SOC_MMBUF_SMC_CS_IDLE_ADDR(base)              ((base) + (0x0034))

/* �Ĵ���˵����AXI slave����д��ӦFIFO�д洢��AXIд��Ӧ���������
   λ����UNION�ṹ:  SOC_MMBUF_SMC_DFX_BFIFO_CNT0_UNION */
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_ADDR(base)       ((base) + (0x0038))

/* �Ĵ���˵����AXI slave���ж�����FIFO�д洢��AXI�����ݸ�����
   λ����UNION�ṹ:  SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_UNION */
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_ADDR(base)      ((base) + (0x003C))

/* �Ĵ���˵������֯bank��sram memory��״̬��
   λ����UNION�ṹ:  SOC_MMBUF_SP_SRAM_STATE0_UNION */
#define SOC_MMBUF_SP_SRAM_STATE0_ADDR(base)           ((base) + (0x0040))

/* �Ĵ���˵������֯bank��sram memory��״̬��
   λ����UNION�ṹ:  SOC_MMBUF_SP_SRAM_STATE1_UNION */
#define SOC_MMBUF_SP_SRAM_STATE1_ADDR(base)           ((base) + (0x0044))





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
 �ṹ��    : SOC_MMBUF_SMC_LOCK_UNION
 �ṹ˵��  : SMC_LOCK �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: SMC Lock�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  smc_lock : 32; /* bit[0-31]: дlock�Ĵ�����
                                                   ��Lock�Ĵ���д32bits��Կ����ԿΪ0x5A5A_5A5A���������Ĵ�������ʾ���мĴ�����д����Lock�Ĵ���д��������ֵ�������Ĵ�����Lock������Χ�ڵļĴ�������д��Lock������Χ��ļĴ�������д��
                                                   ���κμĴ�������Lock�Ĵ�����Ӱ�죬�κ�ʱ�̶����Զ���
                                                   ��lock�Ĵ�����Lock�Ĵ�������ֵ��ʾ�Ĵ���������״̬����
                                                   0x0000_0000��ʾ�Ĵ������ڽ���״̬;
                                                   0x0000_0001��ʾ�Ĵ�����������״̬��
                                                   Lock�Ĵ���������Χ���ÿ���Ĵ��������� */
    } reg;
} SOC_MMBUF_SMC_LOCK_UNION;
#endif
#define SOC_MMBUF_SMC_LOCK_smc_lock_START  (0)
#define SOC_MMBUF_SMC_LOCK_smc_lock_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MMBUF_SMC_MEM_LP_UNION
 �ṹ˵��  : SMC_MEM_LP �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: SRAM�͹���light sleepʱ����ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  smc_ls_en      : 1;  /* bit[0]    : SMC SRAM Light Sleep���ܿ�ʹ��
                                                          1'b0: SMCӲ��LS���ܹرգ����κ�״̬�£�SRAM���������LSģʽ
                                                          1'b1: SMCӲ���Զ�����LSģʽ���ܿ���
                                                          ע��1���üĴ�����д��lock������
                                                          ע��2����smc_ls_en��smc_ds_enͬʱ��Ч����smc_ls_en��Ч��
                                                          ע��3���� light sleep �� deep sleep �л������У�����������Լ������ light sleep �л��� deep sleep Ϊ������
                                                          ��1�������üĴ����� light sleep �� deep sleep ����ʹ�ܵ�״̬�������� smc_ls_en = 0����
                                                          ��2����������е� memory ������ normal ̬����ȫ���˳��� light sleep����
                                                          ��3�����Ĵ������õ͹���ģʽ�� deep sleep���� light sleep�������� smc_ds_en = 1�� */
        unsigned int  smc_ds_en      : 1;  /* bit[1]    : SMC SRAM Light Sleep���ܿ�ʹ��
                                                          1'b0: SMCӲ��LS���ܹرգ����κ�״̬�£�SRAM���������LSģʽ
                                                          1'b1: SMCӲ���Զ�����LSģʽ���ܿ���
                                                          ע��1���üĴ�����д��lock������
                                                          ע��2����smc_ls_en��smc_ds_enͬʱ��Ч����smc_ls_en��Ч��
                                                          ע��3���� light sleep �� deep sleep �л������У�����������Լ������ light sleep �л��� deep sleep Ϊ������
                                                          ��1�������üĴ����� light sleep �� deep sleep ����ʹ�ܵ�״̬�������� smc_ls_en = 0����
                                                          ��2����������е� memory ������ normal ̬����ȫ���˳��� light sleep����
                                                          ��3�����Ĵ������õ͹���ģʽ�� deep sleep���� light sleep�������� smc_ds_en = 1�� */
        unsigned int  reserved_0     : 2;  /* bit[2-3]  : Reserved. */
        unsigned int  lp_exit_cycle  : 4;  /* bit[4-7]  : memory��retention״̬������Ҫ��ʱ�䣬��λΪAXI����cycle��
                                                          ��ֵ���趨��Ҫ�鿴��Ӧmemoryԭ�͵�light sleep������ģ��Ҫ���ֵ���ڵ���1��
                                                          ע1���üĴ�����д��lock������
                                                          ע2��ʵ����Ч��ֵ�Ǵ��趨ֵ��1���磺�趨Ϊ2��ʵ��ģ���ʾ3��ʱ�ӡ�
                                                          ע3����smc_ls_en��Чʱ����ֵΪlight sleep�˳�ʱ�䣻��smc_ds_en��Чʱ����ֵΪdeep sleep�˳�ʱ�䡣 */
        unsigned int  lp_enter_cycle : 16; /* bit[8-23] : ģ����к󣬵ȴ�����retention��ʱ�䣬�������պ��ڸ�ʱ���ڼ������У���memory����retention״̬����λΪAXI����cycle��
                                                          ��ֵ���趨��Ҫ�鿴��Ӧmemoryԭ�͵�light sleep������ģ��Ҫ���ֵ���ڵ������õ� lp_exit_cycle ��6��
                                                          ע1���üĴ�����д��lock������
                                                          ע2��ʵ����Ч��ֵ�Ǵ��趨ֵ��1���磺�趨Ϊ2��ʵ��ģ���ʾ3��ʱ�ӡ�
                                                          ע3����smc_ls_en��Чʱ����ֵΪlight sleep����ʱ�䣻��smc_ds_en��Чʱ����ֵΪdeep sleep����ʱ�䡣 */
        unsigned int  reserved_1     : 8;  /* bit[24-31]: Reserved. */
    } reg;
} SOC_MMBUF_SMC_MEM_LP_UNION;
#endif
#define SOC_MMBUF_SMC_MEM_LP_smc_ls_en_START       (0)
#define SOC_MMBUF_SMC_MEM_LP_smc_ls_en_END         (0)
#define SOC_MMBUF_SMC_MEM_LP_smc_ds_en_START       (1)
#define SOC_MMBUF_SMC_MEM_LP_smc_ds_en_END         (1)
#define SOC_MMBUF_SMC_MEM_LP_lp_exit_cycle_START   (4)
#define SOC_MMBUF_SMC_MEM_LP_lp_exit_cycle_END     (7)
#define SOC_MMBUF_SMC_MEM_LP_lp_enter_cycle_START  (8)
#define SOC_MMBUF_SMC_MEM_LP_lp_enter_cycle_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_MMBUF_GCLK_CS_UNION
 �ṹ˵��  : GCLK_CS �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x0000�����:32
 �Ĵ���˵��: AXI slave ��clock gate���á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi_s0_clock_disable  : 1;  /* bit[0]    : ������ƶ�ӦAXI slave�ڵ�ʱ��gate
                                                                 1'b0: ��AXI slave�ڵ�ʱ��Ϊfreerun
                                                                 1'b1: ��AXI slave�ڵ�ʱ�ӹرգ���ʱ��Ҫ�����֤�ö˿ڵ����ݷ�����������µ����ݷ��� */
        unsigned int  axi_s1_clock_disable  : 1;  /* bit[1]    : ������ƶ�ӦAXI slave�ڵ�ʱ��gate
                                                                 1'b0: ��AXI slave�ڵ�ʱ��Ϊfreerun
                                                                 1'b1: ��AXI slave�ڵ�ʱ�ӹرգ���ʱ��Ҫ�����֤�ö˿ڵ����ݷ�����������µ����ݷ��� */
        unsigned int  axi_s2_clock_disable  : 1;  /* bit[2]    : ������ƶ�ӦAXI slave�ڵ�ʱ��gate
                                                                 1'b0: ��AXI slave�ڵ�ʱ��Ϊfreerun
                                                                 1'b1: ��AXI slave�ڵ�ʱ�ӹرգ���ʱ��Ҫ�����֤�ö˿ڵ����ݷ�����������µ����ݷ��� */
        unsigned int  axi_s3_clock_disable  : 1;  /* bit[3]    : ������ƶ�ӦAXI slave�ڵ�ʱ��gate
                                                                 1'b0: ��AXI slave�ڵ�ʱ��Ϊfreerun
                                                                 1'b1: ��AXI slave�ڵ�ʱ�ӹرգ���ʱ��Ҫ�����֤�ö˿ڵ����ݷ�����������µ����ݷ��� */
        unsigned int  axi_s4_clock_disable  : 1;  /* bit[4]    : ������ƶ�ӦAXI slave�ڵ�ʱ��gate
                                                                 1'b0: ��AXI slave�ڵ�ʱ��Ϊfreerun
                                                                 1'b1: ��AXI slave�ڵ�ʱ�ӹرգ���ʱ��Ҫ�����֤�ö˿ڵ����ݷ�����������µ����ݷ��� */
        unsigned int  axi_s5_clock_disable  : 1;  /* bit[5]    : ������ƶ�ӦAXI slave�ڵ�ʱ��gate
                                                                 1'b0: ��AXI slave�ڵ�ʱ��Ϊfreerun
                                                                 1'b1: ��AXI slave�ڵ�ʱ�ӹرգ���ʱ��Ҫ�����֤�ö˿ڵ����ݷ�����������µ����ݷ��� */
        unsigned int  axi_s6_clock_disable  : 1;  /* bit[6]    : ������ƶ�ӦAXI slave�ڵ�ʱ��gate
                                                                 1'b0: ��AXI slave�ڵ�ʱ��Ϊfreerun
                                                                 1'b1: ��AXI slave�ڵ�ʱ�ӹرգ���ʱ��Ҫ�����֤�ö˿ڵ����ݷ�����������µ����ݷ��� */
        unsigned int  axi_s7_clock_disable  : 1;  /* bit[7]    : ������ƶ�ӦAXI slave�ڵ�ʱ��gate
                                                                 1'b0: ��AXI slave�ڵ�ʱ��Ϊfreerun
                                                                 1'b1: ��AXI slave�ڵ�ʱ�ӹرգ���ʱ��Ҫ�����֤�ö˿ڵ����ݷ�����������µ����ݷ��� */
        unsigned int  axi_s8_clock_disable  : 1;  /* bit[8]    : ������ƶ�ӦAXI slave�ڵ�ʱ��gate
                                                                 1'b0: ��AXI slave�ڵ�ʱ��Ϊfreerun
                                                                 1'b1: ��AXI slave�ڵ�ʱ�ӹرգ���ʱ��Ҫ�����֤�ö˿ڵ����ݷ�����������µ����ݷ��� */
        unsigned int  axi_s9_clock_disable  : 1;  /* bit[9]    : ������ƶ�ӦAXI slave�ڵ�ʱ��gate
                                                                 1'b0: ��AXI slave�ڵ�ʱ��Ϊfreerun
                                                                 1'b1: ��AXI slave�ڵ�ʱ�ӹرգ���ʱ��Ҫ�����֤�ö˿ڵ����ݷ�����������µ����ݷ��� */
        unsigned int  axi_s10_clock_disable : 1;  /* bit[10]   : ������ƶ�ӦAXI slave�ڵ�ʱ��gate
                                                                 1'b0: ��AXI slave�ڵ�ʱ��Ϊfreerun
                                                                 1'b1: ��AXI slave�ڵ�ʱ�ӹرգ���ʱ��Ҫ�����֤�ö˿ڵ����ݷ�����������µ����ݷ��� */
        unsigned int  axi_s11_clock_disable : 1;  /* bit[11]   : ������ƶ�ӦAXI slave�ڵ�ʱ��gate
                                                                 1'b0: ��AXI slave�ڵ�ʱ��Ϊfreerun
                                                                 1'b1: ��AXI slave�ڵ�ʱ�ӹرգ���ʱ��Ҫ�����֤�ö˿ڵ����ݷ�����������µ����ݷ��� */
        unsigned int  axi_s12_clock_disable : 1;  /* bit[12]   : ������ƶ�ӦAXI slave�ڵ�ʱ��gate
                                                                 1'b0: ��AXI slave�ڵ�ʱ��Ϊfreerun
                                                                 1'b1: ��AXI slave�ڵ�ʱ�ӹرգ���ʱ��Ҫ�����֤�ö˿ڵ����ݷ�����������µ����ݷ��� */
        unsigned int  axi_s13_clock_disable : 1;  /* bit[13]   : ������ƶ�ӦAXI slave�ڵ�ʱ��gate
                                                                 1'b0: ��AXI slave�ڵ�ʱ��Ϊfreerun
                                                                 1'b1: ��AXI slave�ڵ�ʱ�ӹرգ���ʱ��Ҫ�����֤�ö˿ڵ����ݷ�����������µ����ݷ��� */
        unsigned int  axi_s14_clock_disable : 1;  /* bit[14]   : ������ƶ�ӦAXI slave�ڵ�ʱ��gate
                                                                 1'b0: ��AXI slave�ڵ�ʱ��Ϊfreerun
                                                                 1'b1: ��AXI slave�ڵ�ʱ�ӹرգ���ʱ��Ҫ�����֤�ö˿ڵ����ݷ�����������µ����ݷ��� */
        unsigned int  axi_s15_clock_disable : 1;  /* bit[15]   : ������ƶ�ӦAXI slave�ڵ�ʱ��gate
                                                                 1'b0: ��AXI slave�ڵ�ʱ��Ϊfreerun
                                                                 1'b1: ��AXI slave�ڵ�ʱ�ӹرգ���ʱ��Ҫ�����֤�ö˿ڵ����ݷ�����������µ����ݷ��� */
        unsigned int  reserved              : 16; /* bit[16-31]:  */
    } reg;
} SOC_MMBUF_GCLK_CS_UNION;
#endif
#define SOC_MMBUF_GCLK_CS_axi_s0_clock_disable_START   (0)
#define SOC_MMBUF_GCLK_CS_axi_s0_clock_disable_END     (0)
#define SOC_MMBUF_GCLK_CS_axi_s1_clock_disable_START   (1)
#define SOC_MMBUF_GCLK_CS_axi_s1_clock_disable_END     (1)
#define SOC_MMBUF_GCLK_CS_axi_s2_clock_disable_START   (2)
#define SOC_MMBUF_GCLK_CS_axi_s2_clock_disable_END     (2)
#define SOC_MMBUF_GCLK_CS_axi_s3_clock_disable_START   (3)
#define SOC_MMBUF_GCLK_CS_axi_s3_clock_disable_END     (3)
#define SOC_MMBUF_GCLK_CS_axi_s4_clock_disable_START   (4)
#define SOC_MMBUF_GCLK_CS_axi_s4_clock_disable_END     (4)
#define SOC_MMBUF_GCLK_CS_axi_s5_clock_disable_START   (5)
#define SOC_MMBUF_GCLK_CS_axi_s5_clock_disable_END     (5)
#define SOC_MMBUF_GCLK_CS_axi_s6_clock_disable_START   (6)
#define SOC_MMBUF_GCLK_CS_axi_s6_clock_disable_END     (6)
#define SOC_MMBUF_GCLK_CS_axi_s7_clock_disable_START   (7)
#define SOC_MMBUF_GCLK_CS_axi_s7_clock_disable_END     (7)
#define SOC_MMBUF_GCLK_CS_axi_s8_clock_disable_START   (8)
#define SOC_MMBUF_GCLK_CS_axi_s8_clock_disable_END     (8)
#define SOC_MMBUF_GCLK_CS_axi_s9_clock_disable_START   (9)
#define SOC_MMBUF_GCLK_CS_axi_s9_clock_disable_END     (9)
#define SOC_MMBUF_GCLK_CS_axi_s10_clock_disable_START  (10)
#define SOC_MMBUF_GCLK_CS_axi_s10_clock_disable_END    (10)
#define SOC_MMBUF_GCLK_CS_axi_s11_clock_disable_START  (11)
#define SOC_MMBUF_GCLK_CS_axi_s11_clock_disable_END    (11)
#define SOC_MMBUF_GCLK_CS_axi_s12_clock_disable_START  (12)
#define SOC_MMBUF_GCLK_CS_axi_s12_clock_disable_END    (12)
#define SOC_MMBUF_GCLK_CS_axi_s13_clock_disable_START  (13)
#define SOC_MMBUF_GCLK_CS_axi_s13_clock_disable_END    (13)
#define SOC_MMBUF_GCLK_CS_axi_s14_clock_disable_START  (14)
#define SOC_MMBUF_GCLK_CS_axi_s14_clock_disable_END    (14)
#define SOC_MMBUF_GCLK_CS_axi_s15_clock_disable_START  (15)
#define SOC_MMBUF_GCLK_CS_axi_s15_clock_disable_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_MMBUF_SMC_QOS_BACKDOOR_UNION
 �ṹ˵��  : SMC_QOS_BACKDOOR �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: Slave��QOS�����޸ļĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  s0_qos_modify_en     : 1;  /* bit[0] : slave 0 �� QOS �޸�ʹ�ܣ�
                                                             1'b0: QOS�����κθ���
                                                             1'b1: ���Ĵ�slave�ڵ�QOS��QOSֵ��bit[1]���趨
                                                             ע�⣺�üĴ�����д��lock������ */
        unsigned int  s0_qos_modify_value  : 1;  /* bit[1] : Slave 0 ��QOS�趨�޸ĺ���
                                                             �Ĵ��������޸���ʹ�ܿ��ƣ�
                                                             1'b0: ��bit[0]=1ʱ����Slave�ڵ�QOS�޸�Ϊ2'b00(������ȼ�)
                                                             1'b1: ��bit[0]=1ʱ����Slave�ڵ�QOS�޸�Ϊ2'b11(������ȼ�)
                                                             ע�⣺�üĴ�����д��lock������ */
        unsigned int  s1_qos_modify_en     : 1;  /* bit[2] : slave 1 �� QOS �޸�ʹ�ܣ�
                                                             1'b0: QOS�����κθ���
                                                             1'b1: ���Ĵ�slave�ڵ�QOS��QOSֵ��bit[3]���趨
                                                             ע�⣺�üĴ�����д��lock������ */
        unsigned int  s1_qos_modify_value  : 1;  /* bit[3] : Slave 1 ��QOS�趨�޸ĺ���
                                                             �Ĵ��������޸���ʹ�ܿ��ƣ�
                                                             1'b0: ��bit[2]=1ʱ����Slave�ڵ�QOS�޸�Ϊ2'b00(������ȼ�)
                                                             1'b1: ��bit[2]=1ʱ����Slave�ڵ�QOS�޸�Ϊ2'b11(������ȼ�)
                                                             ע�⣺�üĴ�����д��lock������ */
        unsigned int  s2_qos_modify_en     : 1;  /* bit[4] : slave 2 �� QOS �޸�ʹ�ܣ�
                                                             1'b0: QOS�����κθ���
                                                             1'b1: ���Ĵ�slave�ڵ�QOS��QOSֵ��bit[5]���趨
                                                             ע�⣺�üĴ�����д��lock������ */
        unsigned int  s2_qos_modify_value  : 1;  /* bit[5] : Slave 2 ��QOS�趨�޸ĺ���
                                                             �Ĵ��������޸���ʹ�ܿ��ƣ�
                                                             1'b0: ��bit[4]=1ʱ����Slave�ڵ�QOS�޸�Ϊ2'b00(������ȼ�)
                                                             1'b1: ��bit[4]=1ʱ����Slave�ڵ�QOS�޸�Ϊ2'b11(������ȼ�)
                                                             ע�⣺�üĴ�����д��lock������ */
        unsigned int  s3_qos_modify_en     : 1;  /* bit[6] : slave 3 �� QOS �޸�ʹ�ܣ�
                                                             1'b0: QOS�����κθ���
                                                             1'b1: ���Ĵ�slave�ڵ�QOS��QOSֵ��bit[7]���趨
                                                             ע�⣺�üĴ�����д��lock������ */
        unsigned int  s3_qos_modify_value  : 1;  /* bit[7] : Slave 3 ��QOS�趨�޸ĺ���
                                                             �Ĵ��������޸���ʹ�ܿ��ƣ�
                                                             1'b0: ��bit[6]=1ʱ����Slave�ڵ�QOS�޸�Ϊ2'b00(������ȼ�)
                                                             1'b1: ��bit[6]=1ʱ����Slave�ڵ�QOS�޸�Ϊ2'b11(������ȼ�)
                                                             ע�⣺�üĴ�����д��lock������ */
        unsigned int  s4_qos_modify_en     : 1;  /* bit[8] : slave 4 �� QOS �޸�ʹ�ܣ�
                                                             1'b0: QOS�����κθ���
                                                             1'b1: ���Ĵ�slave�ڵ�QOS��QOSֵ��bit[9]���趨
                                                             ע�⣺�üĴ�����д��lock������ */
        unsigned int  s4_qos_modify_value  : 1;  /* bit[9] : Slave 4 ��QOS�趨�޸ĺ���
                                                             �Ĵ��������޸���ʹ�ܿ��ƣ�
                                                             1'b0: ��bit[8]=1ʱ����Slave�ڵ�QOS�޸�Ϊ2'b00(������ȼ�)
                                                             1'b1: ��bit[8]=1ʱ����Slave�ڵ�QOS�޸�Ϊ2'b11(������ȼ�)
                                                             ע�⣺�üĴ�����д��lock������ */
        unsigned int  s5_qos_modify_en     : 1;  /* bit[10]: slave 5 �� QOS �޸�ʹ�ܣ�
                                                             1'b0: QOS�����κθ���
                                                             1'b1: ���Ĵ�slave�ڵ�QOS��QOSֵ��bit[11]���趨
                                                             ע�⣺�üĴ�����д��lock������ */
        unsigned int  s5_qos_modify_value  : 1;  /* bit[11]: Slave 5 ��QOS�趨�޸ĺ���
                                                             �Ĵ��������޸���ʹ�ܿ��ƣ�
                                                             1'b0: ��bit[10]=1ʱ����Slave�ڵ�QOS�޸�Ϊ2'b00(������ȼ�)
                                                             1'b1: ��bit[10]=1ʱ����Slave�ڵ�QOS�޸�Ϊ2'b11(������ȼ�)
                                                             ע�⣺�üĴ�����д��lock������ */
        unsigned int  s6_qos_modify_en     : 1;  /* bit[12]: slave 6 �� QOS �޸�ʹ�ܣ�
                                                             1'b0: QOS�����κθ���
                                                             1'b1: ���Ĵ�slave�ڵ�QOS��QOSֵ��bit[13]���趨
                                                             ע�⣺�üĴ�����д��lock������ */
        unsigned int  s6_qos_modify_value  : 1;  /* bit[13]: Slave 6 ��QOS�趨�޸ĺ���
                                                             �Ĵ��������޸���ʹ�ܿ��ƣ�
                                                             1'b0: ��bit[12]=1ʱ����Slave�ڵ�QOS�޸�Ϊ2'b00(������ȼ�)
                                                             1'b1: ��bit[12]=1ʱ����Slave�ڵ�QOS�޸�Ϊ2'b11(������ȼ�)
                                                             ע�⣺�üĴ�����д��lock������ */
        unsigned int  s7_qos_modify_en     : 1;  /* bit[14]: slave 7 �� QOS �޸�ʹ�ܣ�
                                                             1'b0: QOS�����κθ���
                                                             1'b1: ���Ĵ�slave�ڵ�QOS��QOSֵ��bit[15]���趨
                                                             ע�⣺�üĴ�����д��lock������ */
        unsigned int  s7_qos_modify_value  : 1;  /* bit[15]: Slave 7 ��QOS�趨�޸ĺ���
                                                             �Ĵ��������޸���ʹ�ܿ��ƣ�
                                                             1'b0: ��bit[14]=1ʱ����Slave�ڵ�QOS�޸�Ϊ2'b00(������ȼ�)
                                                             1'b1: ��bit[14]=1ʱ����Slave�ڵ�QOS�޸�Ϊ2'b11(������ȼ�)
                                                             ע�⣺�üĴ�����д��lock������ */
        unsigned int  s8_qos_modify_en     : 1;  /* bit[16]: slave 8 �� QOS �޸�ʹ�ܣ�
                                                             1'b0: QOS�����κθ���
                                                             1'b1: ���Ĵ�slave�ڵ�QOS��QOSֵ��bit[17]���趨
                                                             ע�⣺�üĴ�����д��lock������ */
        unsigned int  s8_qos_modify_value  : 1;  /* bit[17]: Slave 8 ��QOS�趨�޸ĺ���
                                                             �Ĵ��������޸���ʹ�ܿ��ƣ�
                                                             1'b0: ��bit[16]=1ʱ����Slave�ڵ�QOS�޸�Ϊ2'b00(������ȼ�)
                                                             1'b1: ��bit[16]=1ʱ����Slave�ڵ�QOS�޸�Ϊ2'b11(������ȼ�)
                                                             ע�⣺�üĴ�����д��lock������ */
        unsigned int  s9_qos_modify_en     : 1;  /* bit[18]: slave 9 �� QOS �޸�ʹ�ܣ�
                                                             1'b0: QOS�����κθ���
                                                             1'b1: ���Ĵ�slave�ڵ�QOS��QOSֵ��bit[19]���趨
                                                             ע�⣺�üĴ�����д��lock������ */
        unsigned int  s9_qos_modify_value  : 1;  /* bit[19]: Slave 9 ��QOS�趨�޸ĺ���
                                                             �Ĵ��������޸���ʹ�ܿ��ƣ�
                                                             1'b0: ��bit[18]=1ʱ����Slave�ڵ�QOS�޸�Ϊ2'b00(������ȼ�)
                                                             1'b1: ��bit[18]=1ʱ����Slave�ڵ�QOS�޸�Ϊ2'b11(������ȼ�)
                                                             ע�⣺�üĴ�����д��lock������ */
        unsigned int  s10_qos_modify_en    : 1;  /* bit[20]: slave 10 �� QOS �޸�ʹ�ܣ�
                                                             1'b0: QOS�����κθ���
                                                             1'b1: ���Ĵ�slave�ڵ�QOS��QOSֵ��bit[21]���趨 */
        unsigned int  s10_qos_modify_value : 1;  /* bit[21]: Slave 10 ��QOS�趨�޸ĺ���
                                                             �Ĵ��������޸���ʹ�ܿ��ƣ�
                                                             1'b0: ��bit[20]=1ʱ����Slave�ڵ�QOS�޸�Ϊ2'b00(������ȼ�)
                                                             1'b1: ��bit20]=1ʱ����Slave�ڵ�QOS�޸�Ϊ2'b11(������ȼ�)
                                                             ע�⣺�üĴ�����д��lock������ */
        unsigned int  s11_qos_modify_en    : 1;  /* bit[22]: slave 11 �� QOS �޸�ʹ�ܣ�
                                                             1'b0: QOS�����κθ���
                                                             1'b1: ���Ĵ�slave�ڵ�QOS��QOSֵ��bit[23]���趨 */
        unsigned int  s11_qos_modify_value : 1;  /* bit[23]: Slave 11 ��QOS�趨�޸ĺ���
                                                             �Ĵ��������޸���ʹ�ܿ��ƣ�
                                                             1'b0: ��bit[22]=1ʱ����Slave�ڵ�QOS�޸�Ϊ2'b00(������ȼ�)
                                                             1'b1: ��bit[22]=1ʱ����Slave�ڵ�QOS�޸�Ϊ2'b11(������ȼ�)
                                                             ע�⣺�üĴ�����д��lock������ */
        unsigned int  s12_qos_modify_en    : 1;  /* bit[24]: slave 15 �� QOS �޸�ʹ�ܣ�
                                                             1'b0: QOS�����κθ���
                                                             1'b1: ���Ĵ�slave�ڵ�QOS��QOSֵ��bit[25]���趨
                                                             ע�⣺�üĴ�����д��lock������ */
        unsigned int  s12_qos_modify_value : 1;  /* bit[25]: Slave 12 ��QOS�趨�޸ĺ���
                                                             �Ĵ��������޸���ʹ�ܿ��ƣ�
                                                             1'b0: ��bit[24]=1ʱ����Slave�ڵ�QOS�޸�Ϊ2'b00(������ȼ�)
                                                             1'b1: ��bit[24]=1ʱ����Slave�ڵ�QOS�޸�Ϊ2'b11(������ȼ�)
                                                             ע�⣺�üĴ�����д��lock������ */
        unsigned int  s13_qos_modify_en    : 1;  /* bit[26]: slave 13 �� QOS �޸�ʹ�ܣ�
                                                             1'b0: QOS�����κθ���
                                                             1'b1: ���Ĵ�slave�ڵ�QOS��QOSֵ��bit[27]���趨
                                                             ע�⣺�üĴ�����д��lock������ */
        unsigned int  s13_qos_modify_value : 1;  /* bit[27]: Slave 13 ��QOS�趨�޸ĺ���
                                                             �Ĵ��������޸���ʹ�ܿ��ƣ�
                                                             1'b0: ��bit[26]=1ʱ����Slave�ڵ�QOS�޸�Ϊ2'b00(������ȼ�)
                                                             1'b1: ��bit[26]=1ʱ����Slave�ڵ�QOS�޸�Ϊ2'b11(������ȼ�)
                                                             ע�⣺�üĴ�����д��lock������ */
        unsigned int  s14_qos_modify_en    : 1;  /* bit[28]: slave 14 �� QOS �޸�ʹ�ܣ�
                                                             1'b0: QOS�����κθ���
                                                             1'b1: ���Ĵ�slave�ڵ�QOS��QOSֵ��bit[29]���趨
                                                             ע�⣺�üĴ�����д��lock������ */
        unsigned int  s14_qos_modify_value : 1;  /* bit[29]: Slave 14 ��QOS�趨�޸ĺ���
                                                             �Ĵ��������޸���ʹ�ܿ��ƣ�
                                                             1'b0: ��bit[28]=1ʱ����Slave�ڵ�QOS�޸�Ϊ2'b00(������ȼ�)
                                                             1'b1: ��bit[28]=1ʱ����Slave�ڵ�QOS�޸�Ϊ2'b11(������ȼ�)
                                                             ע�⣺�üĴ�����д��lock������ */
        unsigned int  s15_qos_modify_en    : 1;  /* bit[30]: slave 15 �� QOS �޸�ʹ�ܣ�
                                                             1'b0: QOS�����κθ���
                                                             1'b1: ���Ĵ�slave�ڵ�QOS��QOSֵ��bit[31]���趨
                                                             ע�⣺�üĴ�����д��lock������ */
        unsigned int  s15_qos_modify_value : 1;  /* bit[31]: Slave 15 ��QOS�趨�޸ĺ���
                                                             �Ĵ��������޸���ʹ�ܿ��ƣ�
                                                             1'b0: ��bit[30]=1ʱ����Slave�ڵ�QOS�޸�Ϊ2'b00(������ȼ�)
                                                             1'b1: ��bit[30]=1ʱ����Slave�ڵ�QOS�޸�Ϊ2'b11(������ȼ�)
                                                             ע�⣺�üĴ�����д��lock������ */
    } reg;
} SOC_MMBUF_SMC_QOS_BACKDOOR_UNION;
#endif
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s0_qos_modify_en_START      (0)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s0_qos_modify_en_END        (0)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s0_qos_modify_value_START   (1)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s0_qos_modify_value_END     (1)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s1_qos_modify_en_START      (2)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s1_qos_modify_en_END        (2)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s1_qos_modify_value_START   (3)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s1_qos_modify_value_END     (3)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s2_qos_modify_en_START      (4)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s2_qos_modify_en_END        (4)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s2_qos_modify_value_START   (5)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s2_qos_modify_value_END     (5)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s3_qos_modify_en_START      (6)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s3_qos_modify_en_END        (6)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s3_qos_modify_value_START   (7)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s3_qos_modify_value_END     (7)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s4_qos_modify_en_START      (8)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s4_qos_modify_en_END        (8)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s4_qos_modify_value_START   (9)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s4_qos_modify_value_END     (9)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s5_qos_modify_en_START      (10)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s5_qos_modify_en_END        (10)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s5_qos_modify_value_START   (11)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s5_qos_modify_value_END     (11)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s6_qos_modify_en_START      (12)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s6_qos_modify_en_END        (12)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s6_qos_modify_value_START   (13)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s6_qos_modify_value_END     (13)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s7_qos_modify_en_START      (14)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s7_qos_modify_en_END        (14)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s7_qos_modify_value_START   (15)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s7_qos_modify_value_END     (15)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s8_qos_modify_en_START      (16)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s8_qos_modify_en_END        (16)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s8_qos_modify_value_START   (17)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s8_qos_modify_value_END     (17)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s9_qos_modify_en_START      (18)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s9_qos_modify_en_END        (18)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s9_qos_modify_value_START   (19)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s9_qos_modify_value_END     (19)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s10_qos_modify_en_START     (20)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s10_qos_modify_en_END       (20)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s10_qos_modify_value_START  (21)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s10_qos_modify_value_END    (21)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s11_qos_modify_en_START     (22)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s11_qos_modify_en_END       (22)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s11_qos_modify_value_START  (23)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s11_qos_modify_value_END    (23)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s12_qos_modify_en_START     (24)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s12_qos_modify_en_END       (24)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s12_qos_modify_value_START  (25)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s12_qos_modify_value_END    (25)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s13_qos_modify_en_START     (26)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s13_qos_modify_en_END       (26)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s13_qos_modify_value_START  (27)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s13_qos_modify_value_END    (27)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s14_qos_modify_en_START     (28)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s14_qos_modify_en_END       (28)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s14_qos_modify_value_START  (29)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s14_qos_modify_value_END    (29)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s15_qos_modify_en_START     (30)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s15_qos_modify_en_END       (30)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s15_qos_modify_value_START  (31)
#define SOC_MMBUF_SMC_QOS_BACKDOOR_s15_qos_modify_value_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_UNION
 �ṹ˵��  : SMC_DFX_WCMD_CNT_1ST �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ʣ���δ��ɵ�AXI����������λΪAXI���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfx_cs0_wcmd_cnt_1st : 4;  /* bit[0-3]  : ��counterֵ��ʾ��ʣ���δ����ֵ�AXI����������λΪAXI���Cnt_2nd-cnt_1st��ֵ��ʾ��ǰ�Ѿ�����ֵ�����������λΪAXI��� */
        unsigned int  dfx_cs0_wcmd_cnt_2nd : 4;  /* bit[4-7]  : ��counterֵ��ʾ��ʣ���δ��ɵ�AXI����������λΪAXI��� */
        unsigned int  dfx_cs1_wcmd_cnt_1st : 4;  /* bit[8-11] : ��counterֵ��ʾ��ʣ���δ����ֵ�AXI����������λΪAXI���Cnt_2nd-cnt_1st��ֵ��ʾ��ǰ�Ѿ�����ֵ�����������λΪAXI��� */
        unsigned int  dfx_cs1_wcmd_cnt_2nd : 4;  /* bit[12-15]: ��counterֵ��ʾ��ʣ���δ��ɵ�AXI����������λΪAXI��� */
        unsigned int  dfx_cs2_wcmd_cnt_1st : 4;  /* bit[16-19]: ��counterֵ��ʾ��ʣ���δ����ֵ�AXI����������λΪAXI���Cnt_2nd-cnt_1st��ֵ��ʾ��ǰ�Ѿ�����ֵ�����������λΪAXI��� */
        unsigned int  dfx_cs2_wcmd_cnt_2nd : 4;  /* bit[20-23]: ��counterֵ��ʾ��ʣ���δ��ɵ�AXI����������λΪAXI��� */
        unsigned int  dfx_cs3_wcmd_cnt_1st : 4;  /* bit[24-27]: ��counterֵ��ʾ��ʣ���δ����ֵ�AXI����������λΪAXI���Cnt_2nd-cnt_1st��ֵ��ʾ��ǰ�Ѿ�����ֵ�����������λΪAXI��� */
        unsigned int  dfx_cs3_wcmd_cnt_2nd : 4;  /* bit[28-31]: ��counterֵ��ʾ��ʣ���δ��ɵ�AXI����������λΪAXI��� */
    } reg;
} SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_UNION;
#endif
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs0_wcmd_cnt_1st_START  (0)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs0_wcmd_cnt_1st_END    (3)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs0_wcmd_cnt_2nd_START  (4)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs0_wcmd_cnt_2nd_END    (7)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs1_wcmd_cnt_1st_START  (8)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs1_wcmd_cnt_1st_END    (11)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs1_wcmd_cnt_2nd_START  (12)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs1_wcmd_cnt_2nd_END    (15)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs2_wcmd_cnt_1st_START  (16)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs2_wcmd_cnt_1st_END    (19)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs2_wcmd_cnt_2nd_START  (20)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs2_wcmd_cnt_2nd_END    (23)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs3_wcmd_cnt_1st_START  (24)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs3_wcmd_cnt_1st_END    (27)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs3_wcmd_cnt_2nd_START  (28)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_1ST_dfx_cs3_wcmd_cnt_2nd_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_UNION
 �ṹ˵��  : SMC_DFX_WCMD_CNT_2ND �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ʣ���δ��ɵ�AXI����������λΪAXI���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfx_cs4_wcmd_cnt_1st : 4;  /* bit[0-3]  : ��counterֵ��ʾ��ʣ���δ����ֵ�AXI����������λΪAXI���Cnt_2nd-cnt_1st��ֵ��ʾ��ǰ�Ѿ�����ֵ�����������λΪAXI��� */
        unsigned int  dfx_cs4_wcmd_cnt_2nd : 4;  /* bit[4-7]  : ��counterֵ��ʾ��ʣ���δ��ɵ�AXI����������λΪAXI��� */
        unsigned int  dfx_cs5_wcmd_cnt_1st : 4;  /* bit[8-11] : ��counterֵ��ʾ��ʣ���δ����ֵ�AXI����������λΪAXI���Cnt_2nd-cnt_1st��ֵ��ʾ��ǰ�Ѿ�����ֵ�����������λΪAXI��� */
        unsigned int  dfx_cs5_wcmd_cnt_2nd : 4;  /* bit[12-15]: ��counterֵ��ʾ��ʣ���δ��ɵ�AXI����������λΪAXI��� */
        unsigned int  dfx_cs6_wcmd_cnt_1st : 4;  /* bit[16-19]: ��counterֵ��ʾ��ʣ���δ����ֵ�AXI����������λΪAXI���Cnt_2nd-cnt_1st��ֵ��ʾ��ǰ�Ѿ�����ֵ�����������λΪAXI��� */
        unsigned int  dfx_cs6_wcmd_cnt_2nd : 4;  /* bit[20-23]: ��counterֵ��ʾ��ʣ���δ��ɵ�AXI����������λΪAXI��� */
        unsigned int  dfx_cs7_wcmd_cnt_1st : 4;  /* bit[24-27]: ��counterֵ��ʾ��ʣ���δ����ֵ�AXI����������λΪAXI���Cnt_2nd-cnt_1st��ֵ��ʾ��ǰ�Ѿ�����ֵ�����������λΪAXI��� */
        unsigned int  dfx_cs7_wcmd_cnt_2nd : 4;  /* bit[28-31]: ��counterֵ��ʾ��ʣ���δ��ɵ�AXI����������λΪAXI��� */
    } reg;
} SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_UNION;
#endif
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs4_wcmd_cnt_1st_START  (0)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs4_wcmd_cnt_1st_END    (3)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs4_wcmd_cnt_2nd_START  (4)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs4_wcmd_cnt_2nd_END    (7)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs5_wcmd_cnt_1st_START  (8)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs5_wcmd_cnt_1st_END    (11)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs5_wcmd_cnt_2nd_START  (12)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs5_wcmd_cnt_2nd_END    (15)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs6_wcmd_cnt_1st_START  (16)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs6_wcmd_cnt_1st_END    (19)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs6_wcmd_cnt_2nd_START  (20)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs6_wcmd_cnt_2nd_END    (23)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs7_wcmd_cnt_1st_START  (24)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs7_wcmd_cnt_1st_END    (27)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs7_wcmd_cnt_2nd_START  (28)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_2ND_dfx_cs7_wcmd_cnt_2nd_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_UNION
 �ṹ˵��  : SMC_DFX_WCMD_CNT_3RD �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ʣ���δ��ɵ�AXI����������λΪAXI���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfx_cs8_wcmd_cnt_1st  : 4;  /* bit[0-3]  : ��counterֵ��ʾ��ʣ���δ����ֵ�AXI����������λΪAXI���Cnt_2nd-cnt_1st��ֵ��ʾ��ǰ�Ѿ�����ֵ�����������λΪAXI��� */
        unsigned int  dfx_cs8_wcmd_cnt_2nd  : 4;  /* bit[4-7]  : ��counterֵ��ʾ��ʣ���δ��ɵ�AXI����������λΪAXI��� */
        unsigned int  dfx_cs9_wcmd_cnt_1st  : 4;  /* bit[8-11] : ��counterֵ��ʾ��ʣ���δ����ֵ�AXI����������λΪAXI���Cnt_2nd-cnt_1st��ֵ��ʾ��ǰ�Ѿ�����ֵ�����������λΪAXI��� */
        unsigned int  dfx_cs9_wcmd_cnt_2nd  : 4;  /* bit[12-15]: ��counterֵ��ʾ��ʣ���δ��ɵ�AXI����������λΪAXI��� */
        unsigned int  dfx_cs10_wcmd_cnt_1st : 4;  /* bit[16-19]: ��counterֵ��ʾ��ʣ���δ����ֵ�AXI����������λΪAXI���Cnt_2nd-cnt_1st��ֵ��ʾ��ǰ�Ѿ�����ֵ�����������λΪAXI��� */
        unsigned int  dfx_cs10_wcmd_cnt_2nd : 4;  /* bit[20-23]: ��counterֵ��ʾ��ʣ���δ��ɵ�AXI����������λΪAXI��� */
        unsigned int  dfx_cs11_wcmd_cnt_1st : 4;  /* bit[24-27]: ��counterֵ��ʾ��ʣ���δ����ֵ�AXI����������λΪAXI���Cnt_2nd-cnt_1st��ֵ��ʾ��ǰ�Ѿ�����ֵ�����������λΪAXI��� */
        unsigned int  dfx_cs11_wcmd_cnt_2nd : 4;  /* bit[28-31]: ��counterֵ��ʾ��ʣ���δ��ɵ�AXI����������λΪAXI��� */
    } reg;
} SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_UNION;
#endif
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs8_wcmd_cnt_1st_START   (0)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs8_wcmd_cnt_1st_END     (3)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs8_wcmd_cnt_2nd_START   (4)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs8_wcmd_cnt_2nd_END     (7)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs9_wcmd_cnt_1st_START   (8)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs9_wcmd_cnt_1st_END     (11)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs9_wcmd_cnt_2nd_START   (12)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs9_wcmd_cnt_2nd_END     (15)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs10_wcmd_cnt_1st_START  (16)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs10_wcmd_cnt_1st_END    (19)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs10_wcmd_cnt_2nd_START  (20)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs10_wcmd_cnt_2nd_END    (23)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs11_wcmd_cnt_1st_START  (24)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs11_wcmd_cnt_1st_END    (27)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs11_wcmd_cnt_2nd_START  (28)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_3RD_dfx_cs11_wcmd_cnt_2nd_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_UNION
 �ṹ˵��  : SMC_DFX_WCMD_CNT_4TH �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ʣ���δ��ɵ�AXI����������λΪAXI���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfx_cs12_wcmd_cnt_1st : 4;  /* bit[0-3]  : ��counterֵ��ʾ��ʣ���δ����ֵ�AXI����������λΪAXI���Cnt_2nd-cnt_1st��ֵ��ʾ��ǰ�Ѿ�����ֵ�����������λΪAXI��� */
        unsigned int  dfx_cs12_wcmd_cnt_2nd : 4;  /* bit[4-7]  : ��counterֵ��ʾ��ʣ���δ��ɵ�AXI����������λΪAXI��� */
        unsigned int  dfx_cs13_wcmd_cnt_1st : 4;  /* bit[8-11] : ��counterֵ��ʾ��ʣ���δ����ֵ�AXI����������λΪAXI���Cnt_2nd-cnt_1st��ֵ��ʾ��ǰ�Ѿ�����ֵ�����������λΪAXI��� */
        unsigned int  dfx_cs13_wcmd_cnt_2nd : 4;  /* bit[12-15]: ��counterֵ��ʾ��ʣ���δ��ɵ�AXI����������λΪAXI��� */
        unsigned int  dfx_cs14_wcmd_cnt_1st : 4;  /* bit[16-19]: ��counterֵ��ʾ��ʣ���δ����ֵ�AXI����������λΪAXI���Cnt_2nd-cnt_1st��ֵ��ʾ��ǰ�Ѿ�����ֵ�����������λΪAXI��� */
        unsigned int  dfx_cs14_wcmd_cnt_2nd : 4;  /* bit[20-23]: ��counterֵ��ʾ��ʣ���δ��ɵ�AXI����������λΪAXI��� */
        unsigned int  dfx_cs15_wcmd_cnt_1st : 4;  /* bit[24-27]: ��counterֵ��ʾ��ʣ���δ����ֵ�AXI����������λΪAXI���Cnt_2nd-cnt_1st��ֵ��ʾ��ǰ�Ѿ�����ֵ�����������λΪAXI��� */
        unsigned int  dfx_cs15_wcmd_cnt_2nd : 4;  /* bit[28-31]: ��counterֵ��ʾ��ʣ���δ��ɵ�AXI����������λΪAXI��� */
    } reg;
} SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_UNION;
#endif
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs12_wcmd_cnt_1st_START  (0)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs12_wcmd_cnt_1st_END    (3)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs12_wcmd_cnt_2nd_START  (4)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs12_wcmd_cnt_2nd_END    (7)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs13_wcmd_cnt_1st_START  (8)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs13_wcmd_cnt_1st_END    (11)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs13_wcmd_cnt_2nd_START  (12)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs13_wcmd_cnt_2nd_END    (15)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs14_wcmd_cnt_1st_START  (16)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs14_wcmd_cnt_1st_END    (19)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs14_wcmd_cnt_2nd_START  (20)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs14_wcmd_cnt_2nd_END    (23)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs15_wcmd_cnt_1st_START  (24)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs15_wcmd_cnt_1st_END    (27)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs15_wcmd_cnt_2nd_START  (28)
#define SOC_MMBUF_SMC_DFX_WCMD_CNT_4TH_dfx_cs15_wcmd_cnt_2nd_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_UNION
 �ṹ˵��  : SMC_DFX_RCMD_CNT_1ST �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ʣ���δ��ɵ�AXI����������λΪAXI���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfx_cs0_rcmd_cnt_1st : 4;  /* bit[0-3]  : ��counterֵ��ʾ��ʣ���δ����ֵ�AXI����������λΪAXI���Cnt_2nd-cnt_1st��ֵ��ʾ��ǰ�Ѿ�����ֵ�����������λΪAXI��� */
        unsigned int  dfx_cs0_rcmd_cnt_2nd : 4;  /* bit[4-7]  : ��counterֵ��ʾ��ʣ���δ��ɵ�AXI����������λΪAXI��� */
        unsigned int  dfx_cs1_rcmd_cnt_1st : 4;  /* bit[8-11] : ��counterֵ��ʾ��ʣ���δ����ֵ�AXI����������λΪAXI���Cnt_2nd-cnt_1st��ֵ��ʾ��ǰ�Ѿ�����ֵ�����������λΪAXI��� */
        unsigned int  dfx_cs1_rcmd_cnt_2nd : 4;  /* bit[12-15]: ��counterֵ��ʾ��ʣ���δ��ɵ�AXI����������λΪAXI��� */
        unsigned int  dfx_cs2_rcmd_cnt_1st : 4;  /* bit[16-19]: ��counterֵ��ʾ��ʣ���δ����ֵ�AXI����������λΪAXI���Cnt_2nd-cnt_1st��ֵ��ʾ��ǰ�Ѿ�����ֵ�����������λΪAXI��� */
        unsigned int  dfx_cs2_rcmd_cnt_2nd : 4;  /* bit[20-23]: ��counterֵ��ʾ��ʣ���δ��ɵ�AXI����������λΪAXI��� */
        unsigned int  dfx_cs3_rcmd_cnt_1st : 4;  /* bit[24-27]: ��counterֵ��ʾ��ʣ���δ����ֵ�AXI����������λΪAXI���Cnt_2nd-cnt_1st��ֵ��ʾ��ǰ�Ѿ�����ֵ�����������λΪAXI��� */
        unsigned int  dfx_cs3_rcmd_cnt_2nd : 4;  /* bit[28-31]: ��counterֵ��ʾ��ʣ���δ��ɵ�AXI����������λΪAXI��� */
    } reg;
} SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_UNION;
#endif
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs0_rcmd_cnt_1st_START  (0)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs0_rcmd_cnt_1st_END    (3)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs0_rcmd_cnt_2nd_START  (4)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs0_rcmd_cnt_2nd_END    (7)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs1_rcmd_cnt_1st_START  (8)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs1_rcmd_cnt_1st_END    (11)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs1_rcmd_cnt_2nd_START  (12)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs1_rcmd_cnt_2nd_END    (15)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs2_rcmd_cnt_1st_START  (16)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs2_rcmd_cnt_1st_END    (19)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs2_rcmd_cnt_2nd_START  (20)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs2_rcmd_cnt_2nd_END    (23)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs3_rcmd_cnt_1st_START  (24)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs3_rcmd_cnt_1st_END    (27)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs3_rcmd_cnt_2nd_START  (28)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_1ST_dfx_cs3_rcmd_cnt_2nd_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_UNION
 �ṹ˵��  : SMC_DFX_RCMD_CNT_2ND �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ʣ���δ��ɵ�AXI����������λΪAXI���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfx_cs4_rcmd_cnt_1st : 4;  /* bit[0-3]  : ��counterֵ��ʾ��ʣ���δ����ֵ�AXI����������λΪAXI���Cnt_2nd-cnt_1st��ֵ��ʾ��ǰ�Ѿ�����ֵ�����������λΪAXI��� */
        unsigned int  dfx_cs4_rcmd_cnt_2nd : 4;  /* bit[4-7]  : ��counterֵ��ʾ��ʣ���δ��ɵ�AXI����������λΪAXI��� */
        unsigned int  dfx_cs5_rcmd_cnt_1st : 4;  /* bit[8-11] : ��counterֵ��ʾ��ʣ���δ����ֵ�AXI����������λΪAXI���Cnt_2nd-cnt_1st��ֵ��ʾ��ǰ�Ѿ�����ֵ�����������λΪAXI��� */
        unsigned int  dfx_cs5_rcmd_cnt_2nd : 4;  /* bit[12-15]: ��counterֵ��ʾ��ʣ���δ��ɵ�AXI����������λΪAXI��� */
        unsigned int  dfx_cs6_rcmd_cnt_1st : 4;  /* bit[16-19]: ��counterֵ��ʾ��ʣ���δ����ֵ�AXI����������λΪAXI���Cnt_2nd-cnt_1st��ֵ��ʾ��ǰ�Ѿ�����ֵ�����������λΪAXI��� */
        unsigned int  dfx_cs6_rcmd_cnt_2nd : 4;  /* bit[20-23]: ��counterֵ��ʾ��ʣ���δ��ɵ�AXI����������λΪAXI��� */
        unsigned int  dfx_cs7_rcmd_cnt_1st : 4;  /* bit[24-27]: ��counterֵ��ʾ��ʣ���δ����ֵ�AXI����������λΪAXI���Cnt_2nd-cnt_1st��ֵ��ʾ��ǰ�Ѿ�����ֵ�����������λΪAXI��� */
        unsigned int  dfx_cs7_rcmd_cnt_2nd : 4;  /* bit[28-31]: ��counterֵ��ʾ��ʣ���δ��ɵ�AXI����������λΪAXI��� */
    } reg;
} SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_UNION;
#endif
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs4_rcmd_cnt_1st_START  (0)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs4_rcmd_cnt_1st_END    (3)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs4_rcmd_cnt_2nd_START  (4)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs4_rcmd_cnt_2nd_END    (7)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs5_rcmd_cnt_1st_START  (8)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs5_rcmd_cnt_1st_END    (11)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs5_rcmd_cnt_2nd_START  (12)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs5_rcmd_cnt_2nd_END    (15)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs6_rcmd_cnt_1st_START  (16)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs6_rcmd_cnt_1st_END    (19)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs6_rcmd_cnt_2nd_START  (20)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs6_rcmd_cnt_2nd_END    (23)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs7_rcmd_cnt_1st_START  (24)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs7_rcmd_cnt_1st_END    (27)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs7_rcmd_cnt_2nd_START  (28)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_2ND_dfx_cs7_rcmd_cnt_2nd_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_UNION
 �ṹ˵��  : SMC_DFX_RCMD_CNT_3RD �Ĵ����ṹ���塣��ַƫ����:0x002C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ʣ���δ��ɵ�AXI����������λΪAXI���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfx_cs8_rcmd_cnt_1st  : 4;  /* bit[0-3]  : ��counterֵ��ʾ��ʣ���δ����ֵ�AXI����������λΪAXI���Cnt_2nd - cnt_1st��ֵ��ʾ��ǰ�Ѿ�����ֵ�����������λΪAXI��� */
        unsigned int  dfx_cs8_rcmd_cnt_2nd  : 4;  /* bit[4-7]  : ��counterֵ��ʾ��ʣ���δ��ɵ�AXI����������λΪAXI��� */
        unsigned int  dfx_cs9_rcmd_cnt_1st  : 4;  /* bit[8-11] : ��counterֵ��ʾ��ʣ���δ����ֵ�AXI����������λΪAXI���Cnt_2nd-cnt_1st��ֵ��ʾ��ǰ�Ѿ�����ֵ�����������λΪAXI��� */
        unsigned int  dfx_cs9_rcmd_cnt_2nd  : 4;  /* bit[12-15]: ��counterֵ��ʾ��ʣ���δ��ɵ�AXI����������λΪAXI��� */
        unsigned int  dfx_cs10_rcmd_cnt_1st : 4;  /* bit[16-19]: ��counterֵ��ʾ��ʣ���δ����ֵ�AXI����������λΪAXI���Cnt_2nd-cnt_1st��ֵ��ʾ��ǰ�Ѿ�����ֵ�����������λΪAXI��� */
        unsigned int  dfx_cs10_rcmd_cnt_2nd : 4;  /* bit[20-23]: ��counterֵ��ʾ��ʣ���δ��ɵ�AXI����������λΪAXI��� */
        unsigned int  dfx_cs11_rcmd_cnt_1st : 4;  /* bit[24-27]: ��counterֵ��ʾ��ʣ���δ����ֵ�AXI����������λΪAXI���Cnt_2nd-cnt_1st��ֵ��ʾ��ǰ�Ѿ�����ֵ�����������λΪAXI��� */
        unsigned int  dfx_cs11_rcmd_cnt_2nd : 4;  /* bit[28-31]: ��counterֵ��ʾ��ʣ���δ��ɵ�AXI����������λΪAXI��� */
    } reg;
} SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_UNION;
#endif
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs8_rcmd_cnt_1st_START   (0)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs8_rcmd_cnt_1st_END     (3)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs8_rcmd_cnt_2nd_START   (4)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs8_rcmd_cnt_2nd_END     (7)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs9_rcmd_cnt_1st_START   (8)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs9_rcmd_cnt_1st_END     (11)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs9_rcmd_cnt_2nd_START   (12)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs9_rcmd_cnt_2nd_END     (15)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs10_rcmd_cnt_1st_START  (16)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs10_rcmd_cnt_1st_END    (19)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs10_rcmd_cnt_2nd_START  (20)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs10_rcmd_cnt_2nd_END    (23)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs11_rcmd_cnt_1st_START  (24)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs11_rcmd_cnt_1st_END    (27)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs11_rcmd_cnt_2nd_START  (28)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_3RD_dfx_cs11_rcmd_cnt_2nd_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_UNION
 �ṹ˵��  : SMC_DFX_RCMD_CNT_4TH �Ĵ����ṹ���塣��ַƫ����:0x0030����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ʣ���δ��ɵ�AXI����������λΪAXI���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfx_cs12_rcmd_cnt_1st : 4;  /* bit[0-3]  : ��counterֵ��ʾ��ʣ���δ����ֵ�AXI����������λΪAXI���Cnt_2nd-cnt_1st��ֵ��ʾ��ǰ�Ѿ�����ֵ�����������λΪAXI��� */
        unsigned int  dfx_cs12_rcmd_cnt_2nd : 4;  /* bit[4-7]  : ��counterֵ��ʾ��ʣ���δ��ɵ�AXI����������λΪAXI��� */
        unsigned int  dfx_cs13_rcmd_cnt_1st : 4;  /* bit[8-11] : ��counterֵ��ʾ��ʣ���δ����ֵ�AXI����������λΪAXI���Cnt_2nd-cnt_1st��ֵ��ʾ��ǰ�Ѿ�����ֵ�����������λΪAXI��� */
        unsigned int  dfx_cs13_rcmd_cnt_2nd : 4;  /* bit[12-15]: ��counterֵ��ʾ��ʣ���δ��ɵ�AXI����������λΪAXI��� */
        unsigned int  dfx_cs14_rcmd_cnt_1st : 4;  /* bit[16-19]: ��counterֵ��ʾ��ʣ���δ����ֵ�AXI����������λΪAXI���Cnt_2nd-cnt_1st��ֵ��ʾ��ǰ�Ѿ�����ֵ�����������λΪAXI��� */
        unsigned int  dfx_cs14_rcmd_cnt_2nd : 4;  /* bit[20-23]: ��counterֵ��ʾ��ʣ���δ��ɵ�AXI����������λΪAXI��� */
        unsigned int  dfx_cs15_rcmd_cnt_1st : 4;  /* bit[24-27]: ��counterֵ��ʾ��ʣ���δ����ֵ�AXI����������λΪAXI���Cnt_2nd-cnt_1st��ֵ��ʾ��ǰ�Ѿ�����ֵ�����������λΪAXI��� */
        unsigned int  dfx_cs15_rcmd_cnt_2nd : 4;  /* bit[28-31]: ��counterֵ��ʾ��ʣ���δ��ɵ�AXI����������λΪAXI��� */
    } reg;
} SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_UNION;
#endif
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs12_rcmd_cnt_1st_START  (0)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs12_rcmd_cnt_1st_END    (3)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs12_rcmd_cnt_2nd_START  (4)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs12_rcmd_cnt_2nd_END    (7)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs13_rcmd_cnt_1st_START  (8)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs13_rcmd_cnt_1st_END    (11)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs13_rcmd_cnt_2nd_START  (12)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs13_rcmd_cnt_2nd_END    (15)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs14_rcmd_cnt_1st_START  (16)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs14_rcmd_cnt_1st_END    (19)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs14_rcmd_cnt_2nd_START  (20)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs14_rcmd_cnt_2nd_END    (23)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs15_rcmd_cnt_1st_START  (24)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs15_rcmd_cnt_1st_END    (27)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs15_rcmd_cnt_2nd_START  (28)
#define SOC_MMBUF_SMC_DFX_RCMD_CNT_4TH_dfx_cs15_rcmd_cnt_2nd_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MMBUF_SMC_CS_IDLE_UNION
 �ṹ˵��  : SMC_CS_IDLE �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: AXI slave�ڵ�״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfx_cs0_idle  : 1;  /* bit[0]    : ��ʾ��AXI slave�ڵ�״̬��
                                                         1'b0:��ʾAXI slave�����ڹ�����������AXI����δ��ɡ�
                                                         1'b1:��ʾAXI slave�ڿ��У�������FIFO�е�AXI����ȫ����ɡ� */
        unsigned int  dfx_cs1_idle  : 1;  /* bit[1]    : ��ʾ��AXI slave�ڵ�״̬��
                                                         1'b0:��ʾAXI slave�����ڹ�����������AXI����δ��ɡ�
                                                         1'b1:��ʾAXI slave�ڿ��У�������FIFO�е�AXI����ȫ����ɡ� */
        unsigned int  dfx_cs2_idle  : 1;  /* bit[2]    : ��ʾ��AXI slave�ڵ�״̬��
                                                         1'b0:��ʾAXI slave�����ڹ�����������AXI����δ��ɡ�
                                                         1'b1:��ʾAXI slave�ڿ��У�������FIFO�е�AXI����ȫ����ɡ� */
        unsigned int  dfx_cs3_idle  : 1;  /* bit[3]    : ��ʾ��AXI slave�ڵ�״̬��
                                                         1'b0:��ʾAXI slave�����ڹ�����������AXI����δ��ɡ�
                                                         1'b1:��ʾAXI slave�ڿ��У�������FIFO�е�AXI����ȫ����ɡ� */
        unsigned int  dfx_cs4_idle  : 1;  /* bit[4]    : ��ʾ��AXI slave�ڵ�״̬��
                                                         1'b0:��ʾAXI slave�����ڹ�����������AXI����δ��ɡ�
                                                         1'b1:��ʾAXI slave�ڿ��У�������FIFO�е�AXI����ȫ����ɡ� */
        unsigned int  dfx_cs5_idle  : 1;  /* bit[5]    : ��ʾ��AXI slave�ڵ�״̬��
                                                         1'b0:��ʾAXI slave�����ڹ�����������AXI����δ��ɡ�
                                                         1'b1:��ʾAXI slave�ڿ��У�������FIFO�е�AXI����ȫ����ɡ� */
        unsigned int  dfx_cs6_idle  : 1;  /* bit[6]    : ��ʾ��AXI slave�ڵ�״̬��
                                                         1'b0:��ʾAXI slave�����ڹ�����������AXI����δ��ɡ�
                                                         1'b1:��ʾAXI slave�ڿ��У�������FIFO�е�AXI����ȫ����ɡ� */
        unsigned int  dfx_cs7_idle  : 1;  /* bit[7]    : ��ʾ��AXI slave�ڵ�״̬��
                                                         1'b0:��ʾAXI slave�����ڹ�����������AXI����δ��ɡ�
                                                         1'b1:��ʾAXI slave�ڿ��У�������FIFO�е�AXI����ȫ����ɡ� */
        unsigned int  dfx_cs8_idle  : 1;  /* bit[8]    : ��ʾ��AXI slave�ڵ�״̬��
                                                         1'b0:��ʾAXI slave�����ڹ�����������AXI����δ��ɡ�
                                                         1'b1:��ʾAXI slave�ڿ��У�������FIFO�е�AXI����ȫ����ɡ� */
        unsigned int  dfx_cs9_idle  : 1;  /* bit[9]    : ��ʾ��AXI slave�ڵ�״̬��
                                                         1'b0:��ʾAXI slave�����ڹ�����������AXI����δ��ɡ�
                                                         1'b1:��ʾAXI slave�ڿ��У�������FIFO�е�AXI����ȫ����ɡ� */
        unsigned int  dfx_cs10_idle : 1;  /* bit[10]   : ��ʾ��AXI slave�ڵ�״̬��
                                                         1'b0:��ʾAXI slave�����ڹ�����������AXI����δ��ɡ�
                                                         1'b1:��ʾAXI slave�ڿ��У�������FIFO�е�AXI����ȫ����ɡ� */
        unsigned int  dfx_cs11_idle : 1;  /* bit[11]   : ��ʾ��AXI slave�ڵ�״̬��
                                                         1'b0:��ʾAXI slave�����ڹ�����������AXI����δ��ɡ�
                                                         1'b1:��ʾAXI slave�ڿ��У�������FIFO�е�AXI����ȫ����ɡ� */
        unsigned int  dfx_cs12_idle : 1;  /* bit[12]   : ��ʾ��AXI slave�ڵ�״̬��
                                                         1'b0:��ʾAXI slave�����ڹ�����������AXI����δ��ɡ�
                                                         1'b1:��ʾAXI slave�ڿ��У�������FIFO�е�AXI����ȫ����ɡ� */
        unsigned int  dfx_cs13_idle : 1;  /* bit[13]   : ��ʾ��AXI slave�ڵ�״̬��
                                                         1'b0:��ʾAXI slave�����ڹ�����������AXI����δ��ɡ�
                                                         1'b1:��ʾAXI slave�ڿ��У�������FIFO�е�AXI����ȫ����ɡ� */
        unsigned int  dfx_cs14_idle : 1;  /* bit[14]   : ��ʾ��AXI slave�ڵ�״̬��
                                                         1'b0:��ʾAXI slave�����ڹ�����������AXI����δ��ɡ�
                                                         1'b1:��ʾAXI slave�ڿ��У�������FIFO�е�AXI����ȫ����ɡ� */
        unsigned int  dfx_cs15_idle : 1;  /* bit[15]   : ��ʾ��AXI slave�ڵ�״̬��
                                                         1'b0:��ʾAXI slave�����ڹ�����������AXI����δ��ɡ�
                                                         1'b1:��ʾAXI slave�ڿ��У�������FIFO�е�AXI����ȫ����ɡ� */
        unsigned int  reserved      : 16; /* bit[16-31]: Reserved. */
    } reg;
} SOC_MMBUF_SMC_CS_IDLE_UNION;
#endif
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs0_idle_START   (0)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs0_idle_END     (0)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs1_idle_START   (1)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs1_idle_END     (1)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs2_idle_START   (2)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs2_idle_END     (2)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs3_idle_START   (3)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs3_idle_END     (3)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs4_idle_START   (4)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs4_idle_END     (4)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs5_idle_START   (5)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs5_idle_END     (5)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs6_idle_START   (6)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs6_idle_END     (6)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs7_idle_START   (7)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs7_idle_END     (7)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs8_idle_START   (8)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs8_idle_END     (8)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs9_idle_START   (9)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs9_idle_END     (9)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs10_idle_START  (10)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs10_idle_END    (10)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs11_idle_START  (11)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs11_idle_END    (11)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs12_idle_START  (12)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs12_idle_END    (12)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs13_idle_START  (13)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs13_idle_END    (13)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs14_idle_START  (14)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs14_idle_END    (14)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs15_idle_START  (15)
#define SOC_MMBUF_SMC_CS_IDLE_dfx_cs15_idle_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_MMBUF_SMC_DFX_BFIFO_CNT0_UNION
 �ṹ˵��  : SMC_DFX_BFIFO_CNT0 �Ĵ����ṹ���塣��ַƫ����:0x0038����ֵ:0x00000000�����:32
 �Ĵ���˵��: AXI slave����д��ӦFIFO�д洢��AXIд��Ӧ���������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfx_cs0_bfifo_cnt  : 2;  /* bit[0-1]  : ��1��AXI slave����д��ӦFIFO�д洢��AXIд��Ӧ��������� */
        unsigned int  dfx_cs1_bfifo_cnt  : 2;  /* bit[2-3]  : ��2��AXI slave����д��ӦFIFO�д洢��AXIд��Ӧ��������� */
        unsigned int  dfx_cs2_bfifo_cnt  : 2;  /* bit[4-5]  : ��3��AXI slave����д��ӦFIFO�д洢��AXIд��Ӧ��������� */
        unsigned int  dfx_cs3_bfifo_cnt  : 2;  /* bit[6-7]  : ��4��AXI slave����д��ӦFIFO�д洢��AXIд��Ӧ��������� */
        unsigned int  dfx_cs4_bfifo_cnt  : 2;  /* bit[8-9]  : ��5��AXI slave����д��ӦFIFO�д洢��AXIд��Ӧ��������� */
        unsigned int  dfx_cs5_bfifo_cnt  : 2;  /* bit[10-11]: ��6��AXI slave����д��ӦFIFO�д洢��AXIд��Ӧ��������� */
        unsigned int  dfx_cs6_bfifo_cnt  : 2;  /* bit[12-13]: ��7��AXI slave����д��ӦFIFO�д洢��AXIд��Ӧ��������� */
        unsigned int  dfx_cs7_bfifo_cnt  : 2;  /* bit[14-15]: ��8��AXI slave����д��ӦFIFO�д洢��AXIд��Ӧ��������� */
        unsigned int  dfx_cs8_bfifo_cnt  : 2;  /* bit[16-17]: ��9��AXI slave����д��ӦFIFO�д洢��AXIд��Ӧ��������� */
        unsigned int  dfx_cs9_bfifo_cnt  : 2;  /* bit[18-19]: ��10��AXI slave����д��ӦFIFO�д洢��AXIд��Ӧ��������� */
        unsigned int  dfx_cs10_bfifo_cnt : 2;  /* bit[20-21]: ��11��AXI slave����д��ӦFIFO�д洢��AXIд��Ӧ��������� */
        unsigned int  dfx_cs11_bfifo_cnt : 2;  /* bit[22-23]: ��12��AXI slave����д��ӦFIFO�д洢��AXIд��Ӧ��������� */
        unsigned int  dfx_cs12_bfifo_cnt : 2;  /* bit[24-25]: ��13��AXI slave����д��ӦFIFO�д洢��AXIд��Ӧ��������� */
        unsigned int  dfx_cs13_bfifo_cnt : 2;  /* bit[26-27]: ��14��AXI slave����д��ӦFIFO�д洢��AXIд��Ӧ��������� */
        unsigned int  dfx_cs14_bfifo_cnt : 2;  /* bit[28-29]: ��15��AXI slave����д��ӦFIFO�д洢��AXIд��Ӧ��������� */
        unsigned int  dfx_cs15_bfifo_cnt : 2;  /* bit[30-31]: ��16��AXI slave����д��ӦFIFO�д洢��AXIд��Ӧ��������� */
    } reg;
} SOC_MMBUF_SMC_DFX_BFIFO_CNT0_UNION;
#endif
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs0_bfifo_cnt_START   (0)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs0_bfifo_cnt_END     (1)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs1_bfifo_cnt_START   (2)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs1_bfifo_cnt_END     (3)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs2_bfifo_cnt_START   (4)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs2_bfifo_cnt_END     (5)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs3_bfifo_cnt_START   (6)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs3_bfifo_cnt_END     (7)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs4_bfifo_cnt_START   (8)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs4_bfifo_cnt_END     (9)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs5_bfifo_cnt_START   (10)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs5_bfifo_cnt_END     (11)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs6_bfifo_cnt_START   (12)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs6_bfifo_cnt_END     (13)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs7_bfifo_cnt_START   (14)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs7_bfifo_cnt_END     (15)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs8_bfifo_cnt_START   (16)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs8_bfifo_cnt_END     (17)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs9_bfifo_cnt_START   (18)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs9_bfifo_cnt_END     (19)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs10_bfifo_cnt_START  (20)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs10_bfifo_cnt_END    (21)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs11_bfifo_cnt_START  (22)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs11_bfifo_cnt_END    (23)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs12_bfifo_cnt_START  (24)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs12_bfifo_cnt_END    (25)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs13_bfifo_cnt_START  (26)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs13_bfifo_cnt_END    (27)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs14_bfifo_cnt_START  (28)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs14_bfifo_cnt_END    (29)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs15_bfifo_cnt_START  (30)
#define SOC_MMBUF_SMC_DFX_BFIFO_CNT0_dfx_cs15_bfifo_cnt_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_UNION
 �ṹ˵��  : SMC_DFX_RDFIFO_CNT1 �Ĵ����ṹ���塣��ַƫ����:0x003C����ֵ:0x00000000�����:32
 �Ĵ���˵��: AXI slave���ж�����FIFO�д洢��AXI�����ݸ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfx_cs0_rdfifo_cnt  : 2;  /* bit[0-1]  : ��1��AXI slave���ж�����FIFO�д洢��AXI�����ݸ����� */
        unsigned int  dfx_cs1_rdfifo_cnt  : 2;  /* bit[2-3]  : ��2��AXI slave���ж�����FIFO�д洢��AXI�����ݸ����� */
        unsigned int  dfx_cs2_rdfifo_cnt  : 2;  /* bit[4-5]  : ��3��AXI slave���ж�����FIFO�д洢��AXI�����ݸ����� */
        unsigned int  dfx_cs3_rdfifo_cnt  : 2;  /* bit[6-7]  : ��4��AXI slave���ж�����FIFO�д洢��AXI�����ݸ����� */
        unsigned int  dfx_cs4_rdfifo_cnt  : 2;  /* bit[8-9]  : ��5��AXI slave���ж�����FIFO�д洢��AXI�����ݸ����� */
        unsigned int  dfx_cs5_rdfifo_cnt  : 2;  /* bit[10-11]: ��6��AXI slave���ж�����FIFO�д洢��AXI�����ݸ����� */
        unsigned int  dfx_cs6_rdfifo_cnt  : 2;  /* bit[12-13]: ��7��AXI slave���ж�����FIFO�д洢��AXI�����ݸ����� */
        unsigned int  dfx_cs7_rdfifo_cnt  : 2;  /* bit[14-15]: ��8��AXI slave���ж�����FIFO�д洢��AXI�����ݸ����� */
        unsigned int  dfx_cs8_rdfifo_cnt  : 2;  /* bit[16-17]: ��9��AXI slave���ж�����FIFO�д洢��AXI�����ݸ����� */
        unsigned int  dfx_cs9_rdfifo_cnt  : 2;  /* bit[18-19]: ��10��AXI slave���ж�����FIFO�д洢��AXI�����ݸ����� */
        unsigned int  dfx_cs10_rdfifo_cnt : 2;  /* bit[20-21]: ��11��AXI slave���ж�����FIFO�д洢��AXI�����ݸ����� */
        unsigned int  dfx_cs11_rdfifo_cnt : 2;  /* bit[22-23]: ��12��AXI slave���ж�����FIFO�д洢��AXI�����ݸ����� */
        unsigned int  dfx_cs12_rdfifo_cnt : 2;  /* bit[24-25]: ��13��AXI slave���ж�����FIFO�д洢��AXI�����ݸ����� */
        unsigned int  dfx_cs13_rdfifo_cnt : 2;  /* bit[26-27]: ��14��AXI slave���ж�����FIFO�д洢��AXI�����ݸ����� */
        unsigned int  dfx_cs14_rdfifo_cnt : 2;  /* bit[28-29]: ��15��AXI slave���ж�����FIFO�д洢��AXI�����ݸ����� */
        unsigned int  dfx_cs15_rdfifo_cnt : 2;  /* bit[30-31]: ��16��AXI slave���ж�����FIFO�д洢��AXI�����ݸ����� */
    } reg;
} SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_UNION;
#endif
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs0_rdfifo_cnt_START   (0)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs0_rdfifo_cnt_END     (1)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs1_rdfifo_cnt_START   (2)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs1_rdfifo_cnt_END     (3)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs2_rdfifo_cnt_START   (4)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs2_rdfifo_cnt_END     (5)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs3_rdfifo_cnt_START   (6)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs3_rdfifo_cnt_END     (7)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs4_rdfifo_cnt_START   (8)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs4_rdfifo_cnt_END     (9)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs5_rdfifo_cnt_START   (10)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs5_rdfifo_cnt_END     (11)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs6_rdfifo_cnt_START   (12)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs6_rdfifo_cnt_END     (13)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs7_rdfifo_cnt_START   (14)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs7_rdfifo_cnt_END     (15)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs8_rdfifo_cnt_START   (16)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs8_rdfifo_cnt_END     (17)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs9_rdfifo_cnt_START   (18)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs9_rdfifo_cnt_END     (19)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs10_rdfifo_cnt_START  (20)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs10_rdfifo_cnt_END    (21)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs11_rdfifo_cnt_START  (22)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs11_rdfifo_cnt_END    (23)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs12_rdfifo_cnt_START  (24)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs12_rdfifo_cnt_END    (25)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs13_rdfifo_cnt_START  (26)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs13_rdfifo_cnt_END    (27)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs14_rdfifo_cnt_START  (28)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs14_rdfifo_cnt_END    (29)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs15_rdfifo_cnt_START  (30)
#define SOC_MMBUF_SMC_DFX_RDFIFO_CNT1_dfx_cs15_rdfifo_cnt_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MMBUF_SP_SRAM_STATE0_UNION
 �ṹ˵��  : SP_SRAM_STATE0 �Ĵ����ṹ���塣��ַƫ����:0x0040����ֵ:0x0000�����:32
 �Ĵ���˵��: ��֯bank��sram memory��״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  st_int0_sram0 : 2;  /* bit[0-1]  : ��֯bank0��sram0 memory��״̬��
                                                         2'b00: normal state
                                                         2'b01: in light sleep state
                                                         2'b10: in deep sleep state
                                                         2'b11: in shut down state */
        unsigned int  st_int0_sram1 : 2;  /* bit[2-3]  : ��֯bank0��sram1 memory��״̬��
                                                         2'b00: normal state
                                                         2'b01: in light sleep state
                                                         2'b10: in deep sleep state
                                                         2'b11: in shut down state */
        unsigned int  st_int1_sram0 : 2;  /* bit[4-5]  : ��֯bank1��sram0 memory��״̬��
                                                         2'b00: normal state
                                                         2'b01: in light sleep state
                                                         2'b10: in deep sleep state
                                                         2'b11: in shut down state */
        unsigned int  st_int1_sram1 : 2;  /* bit[6-7]  : ��֯bank1��sram1 memory��״̬��
                                                         2'b00: normal state
                                                         2'b01: in light sleep state
                                                         2'b10: in deep sleep state
                                                         2'b11: in shut down state */
        unsigned int  st_int2_sram0 : 2;  /* bit[8-9]  : ��֯bank2��sram0 memory��״̬��
                                                         2'b00: normal state
                                                         2'b01: in light sleep state
                                                         2'b10: in deep sleep state
                                                         2'b11: in shut down state */
        unsigned int  st_int2_sram1 : 2;  /* bit[10-11]: ��֯bank2��sram1 memory��״̬��
                                                         2'b00: normal state
                                                         2'b01: in light sleep state
                                                         2'b10: in deep sleep state
                                                         2'b11: in shut down state */
        unsigned int  st_int3_sram0 : 2;  /* bit[12-13]: ��֯bank3��sram0 memory��״̬��
                                                         2'b00: normal state
                                                         2'b01: in light sleep state
                                                         2'b10: in deep sleep state
                                                         2'b11: in shut down state */
        unsigned int  st_int3_sram1 : 2;  /* bit[14-15]: ��֯bank3��sram1 memory��״̬��
                                                         2'b00: normal state
                                                         2'b01: in light sleep state
                                                         2'b10: in deep sleep state
                                                         2'b11: in shut down state */
        unsigned int  st_int4_sram0 : 2;  /* bit[16-17]: ��֯bank4��sram0 memory��״̬��
                                                         2'b00: normal state
                                                         2'b01: in light sleep state
                                                         2'b10: in deep sleep state
                                                         2'b11: in shut down state */
        unsigned int  st_int4_sram1 : 2;  /* bit[18-19]: ��֯bank4��sram1 memory��״̬��
                                                         2'b00: normal state
                                                         2'b01: in light sleep state
                                                         2'b10: in deep sleep state
                                                         2'b11: in shut down state */
        unsigned int  st_int5_sram0 : 2;  /* bit[20-21]: ��֯bank5��sram0 memory��״̬��
                                                         2'b00: normal state
                                                         2'b01: in light sleep state
                                                         2'b10: in deep sleep state
                                                         2'b11: in shut down state */
        unsigned int  st_int5_sram1 : 2;  /* bit[22-23]: ��֯bank5��sram1 memory��״̬��
                                                         2'b00: normal state
                                                         2'b01: in light sleep state
                                                         2'b10: in deep sleep state
                                                         2'b11: in shut down state */
        unsigned int  st_int6_sram0 : 2;  /* bit[24-25]: ��֯bank6��sram0 memory��״̬��
                                                         2'b00: normal state
                                                         2'b01: in light sleep state
                                                         2'b10: in deep sleep state
                                                         2'b11: in shut down state */
        unsigned int  st_int6_sram1 : 2;  /* bit[26-27]: ��֯bank6��sram1 memory��״̬��
                                                         2'b00: normal state
                                                         2'b01: in light sleep state
                                                         2'b10: in deep sleep state
                                                         2'b11: in shut down state */
        unsigned int  st_int7_sram0 : 2;  /* bit[28-29]: ��֯bank7��sram0 memory��״̬��
                                                         2'b00: normal state
                                                         2'b01: in light sleep state
                                                         2'b10: in deep sleep state
                                                         2'b11: in shut down state */
        unsigned int  st_int7_sram1 : 2;  /* bit[30-31]: ��֯bank7��sram1 memory��״̬��
                                                         2'b00: normal state
                                                         2'b01: in light sleep state
                                                         2'b10: in deep sleep state
                                                         2'b11: in shut down state */
    } reg;
} SOC_MMBUF_SP_SRAM_STATE0_UNION;
#endif
#define SOC_MMBUF_SP_SRAM_STATE0_st_int0_sram0_START  (0)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int0_sram0_END    (1)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int0_sram1_START  (2)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int0_sram1_END    (3)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int1_sram0_START  (4)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int1_sram0_END    (5)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int1_sram1_START  (6)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int1_sram1_END    (7)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int2_sram0_START  (8)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int2_sram0_END    (9)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int2_sram1_START  (10)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int2_sram1_END    (11)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int3_sram0_START  (12)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int3_sram0_END    (13)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int3_sram1_START  (14)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int3_sram1_END    (15)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int4_sram0_START  (16)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int4_sram0_END    (17)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int4_sram1_START  (18)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int4_sram1_END    (19)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int5_sram0_START  (20)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int5_sram0_END    (21)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int5_sram1_START  (22)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int5_sram1_END    (23)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int6_sram0_START  (24)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int6_sram0_END    (25)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int6_sram1_START  (26)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int6_sram1_END    (27)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int7_sram0_START  (28)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int7_sram0_END    (29)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int7_sram1_START  (30)
#define SOC_MMBUF_SP_SRAM_STATE0_st_int7_sram1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_MMBUF_SP_SRAM_STATE1_UNION
 �ṹ˵��  : SP_SRAM_STATE1 �Ĵ����ṹ���塣��ַƫ����:0x0044����ֵ:0x0000�����:32
 �Ĵ���˵��: ��֯bank��sram memory��״̬��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  st_int8_sram0  : 2;  /* bit[0-1]  : ��֯bank8��sram0 memory��״̬��
                                                          2'b00: normal state
                                                          2'b01: in light sleep state
                                                          2'b10: in deep sleep state
                                                          2'b11: in shut down state */
        unsigned int  st_int8_sram1  : 2;  /* bit[2-3]  : ��֯bank8��sram1 memory��״̬��
                                                          2'b00: normal state
                                                          2'b01: in light sleep state
                                                          2'b10: in deep sleep state
                                                          2'b11: in shut down state */
        unsigned int  st_int9_sram0  : 2;  /* bit[4-5]  : ��֯bank9��sram0 memory��״̬��
                                                          2'b00: normal state
                                                          2'b01: in light sleep state
                                                          2'b10: in deep sleep state
                                                          2'b11: in shut down state */
        unsigned int  st_int9_sram1  : 2;  /* bit[6-7]  : ��֯bank9��sram1 memory��״̬��
                                                          2'b00: normal state
                                                          2'b01: in light sleep state
                                                          2'b10: in deep sleep state
                                                          2'b11: in shut down state */
        unsigned int  st_int10_sram0 : 2;  /* bit[8-9]  : ��֯bank10��sram0 memory��״̬��
                                                          2'b00: normal state
                                                          2'b01: in light sleep state
                                                          2'b10: in deep sleep state
                                                          2'b11: in shut down state */
        unsigned int  st_int10_sram1 : 2;  /* bit[10-11]: ��֯bank10��sram1 memory��״̬��
                                                          2'b00: normal state
                                                          2'b01: in light sleep state
                                                          2'b10: in deep sleep state
                                                          2'b11: in shut down state */
        unsigned int  st_int11_sram0 : 2;  /* bit[12-13]: ��֯bank11��sram0 memory��״̬��
                                                          2'b00: normal state
                                                          2'b01: in light sleep state
                                                          2'b10: in deep sleep state
                                                          2'b11: in shut down state */
        unsigned int  st_int11_sram1 : 2;  /* bit[14-15]: ��֯bank11��sram1 memory��״̬��
                                                          2'b00: normal state
                                                          2'b01: in light sleep state
                                                          2'b10: in deep sleep state
                                                          2'b11: in shut down state */
        unsigned int  st_int12_sram0 : 2;  /* bit[16-17]: ��֯bank12��sram0 memory��״̬��
                                                          2'b00: normal state
                                                          2'b01: in light sleep state
                                                          2'b10: in deep sleep state
                                                          2'b11: in shut down state */
        unsigned int  st_int12_sram1 : 2;  /* bit[18-19]: ��֯bank12��sram1 memory��״̬��
                                                          2'b00: normal state
                                                          2'b01: in light sleep state
                                                          2'b10: in deep sleep state
                                                          2'b11: in shut down state */
        unsigned int  st_int13_sram0 : 2;  /* bit[20-21]: ��֯bank13��sram0 memory��״̬��
                                                          2'b00: normal state
                                                          2'b01: in light sleep state
                                                          2'b10: in deep sleep state
                                                          2'b11: in shut down state */
        unsigned int  st_int13_sram1 : 2;  /* bit[22-23]: ��֯bank13��sram1 memory��״̬��
                                                          2'b00: normal state
                                                          2'b01: in light sleep state
                                                          2'b10: in deep sleep state
                                                          2'b11: in shut down state */
        unsigned int  st_int14_sram0 : 2;  /* bit[24-25]: ��֯bank14��sram0 memory��״̬��
                                                          2'b00: normal state
                                                          2'b01: in light sleep state
                                                          2'b10: in deep sleep state
                                                          2'b11: in shut down state */
        unsigned int  st_int14_sram1 : 2;  /* bit[26-27]: ��֯bank14��sram1 memory��״̬��
                                                          2'b00: normal state
                                                          2'b01: in light sleep state
                                                          2'b10: in deep sleep state
                                                          2'b11: in shut down state */
        unsigned int  st_int15_sram0 : 2;  /* bit[28-29]: ��֯bank15��sram0 memory��״̬��
                                                          2'b00: normal state
                                                          2'b01: in light sleep state
                                                          2'b10: in deep sleep state
                                                          2'b11: in shut down state */
        unsigned int  st_int15_sram1 : 2;  /* bit[30-31]: ��֯bank15��sram1 memory��״̬��
                                                          2'b00: normal state
                                                          2'b01: in light sleep state
                                                          2'b10: in deep sleep state
                                                          2'b11: in shut down state */
    } reg;
} SOC_MMBUF_SP_SRAM_STATE1_UNION;
#endif
#define SOC_MMBUF_SP_SRAM_STATE1_st_int8_sram0_START   (0)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int8_sram0_END     (1)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int8_sram1_START   (2)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int8_sram1_END     (3)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int9_sram0_START   (4)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int9_sram0_END     (5)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int9_sram1_START   (6)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int9_sram1_END     (7)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int10_sram0_START  (8)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int10_sram0_END    (9)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int10_sram1_START  (10)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int10_sram1_END    (11)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int11_sram0_START  (12)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int11_sram0_END    (13)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int11_sram1_START  (14)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int11_sram1_END    (15)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int12_sram0_START  (16)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int12_sram0_END    (17)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int12_sram1_START  (18)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int12_sram1_END    (19)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int13_sram0_START  (20)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int13_sram0_END    (21)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int13_sram1_START  (22)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int13_sram1_END    (23)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int14_sram0_START  (24)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int14_sram0_END    (25)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int14_sram1_START  (26)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int14_sram1_END    (27)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int15_sram0_START  (28)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int15_sram0_END    (29)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int15_sram1_START  (30)
#define SOC_MMBUF_SP_SRAM_STATE1_st_int15_sram1_END    (31)






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

#endif /* end of soc_mmbuf_interface.h */
