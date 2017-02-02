

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "soc_interface.h"

#ifndef __BBP_GSM_ON_INTERFACE_H__
#define __BBP_GSM_ON_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/***======================================================================***
                     (1/1) register_define_gdrx
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27]     �л���104M�ж������104Mʱ����������źţ�����ָʾDRX˯�߽���֮����ARM��
             ����������CPU�������ѡ���ʱ���ѡ�
 bit[26]     ����
 bit[25]     GBBP���ﶨʱ���߿�ʼʱ�̲������ж��źţ�һ��104MHz�����źš�����ָʾARM�л���32KHzʱ�ӡ�
 bit[24]     �����ж������32KHzʱ����������źţ�����DRX˯�߽���֮����ARM��
             ������������ʱ���ѡ�
             ע��CPU��������ʱ��Ҫ������λ����ж�λ�������п����յ����õĻ����жϡ�
 bit[23:0]   ����
   UNION�ṹ:  GBBP_DRX_CPU_INT_STA_UNION */
#define GBBP_DRX_CPU_INT_STA_ADDR                     (SOC_BBP_GSM_ON_BASE_ADDR + 0x0)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27]     ʱ���л���104M�ж�������μĴ���
 bit[26]     ����
 bit[25]     ARMָ���Ķ�ʱ���߿�ʼ֮�󷢳��Ķ�ʱ�ж����μĴ���
 bit[24]     �����ж����μĴ�����1��ʾ���Σ�0��ʾ�����Ρ�
             ע��CPU��������ʱ��Ҫ������λ����ж�λ�������п����յ����õĻ����жϡ�
 bit[23:0]   ����
   UNION�ṹ:  GBBP_DRX_CPU_INT_MASK_UNION */
#define GBBP_DRX_CPU_INT_MASK_ADDR                    (SOC_BBP_GSM_ON_BASE_ADDR + 0x4)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27]     ʱ���л���104M�ж��������Ĵ���
 bit[26]     ����
 bit[25]     ARMָ���Ķ�ʱ���߿�ʼ֮�󷢳��Ķ�ʱ�ж�����Ĵ���
 bit[24]     �����ж�����Ĵ���
 bit[23:0]   ����
   UNION�ṹ:  GBBP_DRX_CPU_INT_CLR_UNION */
#define GBBP_DRX_CPU_INT_CLR_ADDR                     (SOC_BBP_GSM_ON_BASE_ADDR + 0x8)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27]     �л���104M�ж������104Mʱ����������źţ�����ָʾDRX˯�߽���֮����ARM��
             ����������CPU�������ѡ���ʱ���ѡ�
 bit[26]     ����
 bit[25]     GBBP���ﶨʱ���߿�ʼʱ�̲������ж��źţ�һ��104MHz�����źš�����ָʾARM�л���32KHzʱ�ӡ�
 bit[24]     �����ж������32KHzʱ����������źţ�����DRX˯�߽���֮����ARM��
             ������������ʱ���ѡ�
             ע��CPU��������ʱ��Ҫ������λ����ж�λ�������п����յ����õĻ����жϡ�
 bit[23:0]   ����
   UNION�ṹ:  GBBP_DRX_DSP_INT_STA_UNION */
#define GBBP_DRX_DSP_INT_STA_ADDR                     (SOC_BBP_GSM_ON_BASE_ADDR + 0x10)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27]     ʱ���л���104M�ж�������μĴ���
 bit[26]     ����
 bit[25]     ARMָ���Ķ�ʱ���߿�ʼ֮�󷢳��Ķ�ʱ�ж����μĴ���
 bit[24]     �����ж����μĴ�����1��ʾ���Σ�0��ʾ�����Ρ�
             ע��CPU��������ʱ��Ҫ������λ����ж�λ�������п����յ����õĻ����жϡ�
 bit[23:0]   ����
   UNION�ṹ:  GBBP_DRX_DSP_INT_MASK_UNION */
#define GBBP_DRX_DSP_INT_MASK_ADDR                    (SOC_BBP_GSM_ON_BASE_ADDR + 0x14)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27]     ʱ���л���104M�ж��������Ĵ���
 bit[26]     ����
 bit[25]     ARMָ���Ķ�ʱ���߿�ʼ֮�󷢳��Ķ�ʱ�ж�����Ĵ���
 bit[24]     �����ж�����Ĵ���
 bit[23:0]   ����
   UNION�ṹ:  GBBP_DRX_DSP_INT_CLR_UNION */
#define GBBP_DRX_DSP_INT_CLR_ADDR                     (SOC_BBP_GSM_ON_BASE_ADDR + 0x18)

/* �Ĵ���˵����
 bit[31:16]  ����
 bit[15:0]   ARM 104M�ж��ӳ��ϱ����ʱ���������λΪimi_clk
   UNION�ṹ:  GBBP_ARM_INT_DELAY_REG_PD_UNION */
#define GBBP_ARM_INT_DELAY_REG_PD_ADDR                (SOC_BBP_GSM_ON_BASE_ADDR + 0x1C)

/* �Ĵ���˵����
 bit[31:16]  ����
 bit[15:0]   PHY 104M�ж��ӳ��ϱ����ʱ���������λΪimi_clk
   UNION�ṹ:  GBBP_DSP_INT_DELAY_REG_PD_UNION */
#define GBBP_DSP_INT_DELAY_REG_PD_ADDR                (SOC_BBP_GSM_ON_BASE_ADDR + 0x28)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2]      bit[2] CPU��������GDRXʹ�ܣ��߼������㡣���ź�����ǰӦ��ȷ��GBBP 104Mϵͳʱ���Ѿ��򿪲����ȶ���
 bit[1]      bit[1] 0������˯�ߣ�Ĭ�ϣ���1���ȵ�sleep_pointʱ��ʼ
 bit[0]      bit[0] DRX˯��������д1������1��104MHz��д0�����塣
   UNION�ṹ:  GBBP_SLEEP_EN_UNION */
#define GBBP_SLEEP_EN_ADDR                            (SOC_BBP_GSM_ON_BASE_ADDR + 0x30)

/* �Ĵ���˵����
 bit[31:11]  ����
 bit[10:0]   bit[10:0] �ϱ������жϵ�ʱ���л�ʱ����32.768k����������
   UNION�ṹ:  GBBP_WAKE_CNF_UNION */
#define GBBP_WAKE_CNF_ADDR                            (SOC_BBP_GSM_ON_BASE_ADDR + 0x34)

/* �Ĵ���˵����
 bit[31:26]  ����
 bit[25:0]   ˯�ߵ��ϱ������ж����ʱ����32.768k����������������ֵ�������1��
   UNION�ṹ:  GBBP_WAKEUP_LEN_UNION */
#define GBBP_WAKEUP_LEN_ADDR                          (SOC_BBP_GSM_ON_BASE_ADDR + 0x38)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:24]  bit[29:24]˯�߼���96�����֣�ָʾ1��32K�ж��ٸ�96��104M�ӵı�������
             ע������gdrx_msr_timebase��gdrx_msr_integer��gdrx_msr_frac��ʾ��һ��32Kʱ�Ӱ�����104Mʱ�ӵĸ������ֱ���x��y��z��ʾ������������ȡֵ��
             ����ʱ��У׼��������Եõ�һ��32Kʱ���൱��m.n��104Mʱ�ӣ�m��n�ֱ�Ϊ������С�����֡�����֮�������¹�ϵ��m=x*96+y��n=z/2048��
             
 bit[23]     ����
 bit[22:16]  ˯�߼����������֣�����96��104MHzʱ�Ӹ�����
             ��gdrx_msr_timebaseһ���ʾ��˯�߼�����ȫ���������֡�
             
 bit[15:11]  ����
 bit[10:0]   ˯�߼���С�����֣��ü������Ľ�λ��ʾ1��104Mʱ�ӡ�
   UNION�ṹ:  GBBP_MSR_CNF_UNION */
#define GBBP_MSR_CNF_ADDR                             (SOC_BBP_GSM_ON_BASE_ADDR + 0x3C)

/* �Ĵ���˵����
 bit[31:27]  ����
 bit[26:0]   AMR�ж�GBBP˯��ʱ����ȵ�����ֵ����GDRX�ڲ�32K����ֵ���ڸ�����ʱ���ڲ������ź�Ϊ1��֪ͨARM��
   UNION�ṹ:  GBBP_CPU_DRX_DEPTH_CFG_UNION */
#define GBBP_CPU_DRX_DEPTH_CFG_ADDR                   (SOC_BBP_GSM_ON_BASE_ADDR + 0x40)

/* �Ĵ���˵����
 bit[31:29]  ����
 bit[28:16]  DRX�����л�ʱ���ص�GTC��gtc_timebase����ֵ��������
 bit[15:7]   ����
 bit[6:0]    DRX�����л�ʱ���ص�GTC��FRAC����ֵ��������
   UNION�ṹ:  GBBP_WAKE_GTC_QB_FRAC_RPT_UNION */
#define GBBP_WAKE_GTC_QB_FRAC_RPT_ADDR                (SOC_BBP_GSM_ON_BASE_ADDR + 0x50)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:24]  DRX�����л�ʱ���ص�GTC��T3����ֵ��������
 bit[23:21]  ����
 bit[20:16]  DRX�����л�ʱ���ص�GTC��T2����ֵ��������
 bit[15:11]  ����
 bit[10:0]   DRX�����л�ʱ���ص�GTC��T1����ֵ��������
   UNION�ṹ:  GBBP_WAKE_GTC_T1_T2_T3_RPT_UNION */
#define GBBP_WAKE_GTC_T1_T2_T3_RPT_ADDR               (SOC_BBP_GSM_ON_BASE_ADDR + 0x54)

/* �Ĵ���˵����
 bit[31:27]  ����
 bit[26:16]  DRX�����л�ʱ���ص�GTC��FN_HIGH����ֵ��������
 bit[15:11]  ����
 bit[10:0]   DRX�����л�ʱ���ص�GTC��FN_LOW����ֵ��������
   UNION�ṹ:  GBBP_DRX_WAKE_GTC_FN_RPT_UNION */
#define GBBP_DRX_WAKE_GTC_FN_RPT_ADDR                 (SOC_BBP_GSM_ON_BASE_ADDR + 0x58)

/* �Ĵ���˵����
 bit[31:21]  ����
 bit[20]     DRXģ���ж�����PHY����ֵ�ϱ���DRXģ����ж����μ���0xD1214�Ĵ���bit24����ֵ��������
 bit[19:17]  ����
 bit[16]     DRXģ���ж�����ARM����ֵ�ϱ���DRXģ����ж����μ���0xd1204�Ĵ���bit24����ֵ��������
 bit[15:5]   ����
 bit[4]      DRXģ���ж�״̬�ϱ�PHY
             �ж�״̬�ϱ�����0x01200�Ĵ���bit24�ϱ�ֵ����������
             
 bit[3:1]    ����
 bit[0]      DRXģ���ж�״̬�ϱ�ARM
             �ж�״̬�ϱ�����0x01200�Ĵ���bit24�ϱ�ֵ�� ������
             
   UNION�ṹ:  GBBP_GDRX_INT_MASK_STATE_RPT_UNION */
#define GBBP_GDRX_INT_MASK_STATE_RPT_ADDR             (SOC_BBP_GSM_ON_BASE_ADDR + 0x5C)

/* �Ĵ���˵����
 bit[31]     GBBPģ�������testpinѡ���źţ����ź�Ϊ1ʱ��ѡ��ǵ�������GDRX��testpin������ѡ������������test_pin
 bit[30:4]   ����
 bit[3:0]    GDRXģ���������ѡ���ź�
   UNION�ṹ:  GBBP_DRX_TEST_PIN_SEL_UNION */
#define GBBP_DRX_TEST_PIN_SEL_ADDR                    (SOC_BBP_GSM_ON_BASE_ADDR + 0x60)





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

/***======================================================================***
                     (1/1) register_define_gdrx
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : GBBP_DRX_CPU_INT_STA_UNION
 �ṹ˵��  : DRX_CPU_INT_STA �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      drx_cpu_int_sta_reg;
    struct
    {
        unsigned long  reserved_0          : 24; /* bit[0-23] : ���� */
        unsigned long  drx_int_state_cpu24 : 1;  /* bit[24]   : �����ж������32KHzʱ����������źţ�����DRX˯�߽���֮����ARM��
                                                                ������������ʱ���ѡ�
                                                                ע��CPU��������ʱ��Ҫ������λ����ж�λ�������п����յ����õĻ����жϡ� */
        unsigned long  drx_int_state_cpu25 : 1;  /* bit[25]   : GBBP���ﶨʱ���߿�ʼʱ�̲������ж��źţ�һ��104MHz�����źš�����ָʾARM�л���32KHzʱ�ӡ� */
        unsigned long  reserved_1          : 1;  /* bit[26]   : ���� */
        unsigned long  drx_int_state_cpu27 : 1;  /* bit[27]   : �л���104M�ж������104Mʱ����������źţ�����ָʾDRX˯�߽���֮����ARM��
                                                                ����������CPU�������ѡ���ʱ���ѡ� */
        unsigned long  reserved_2          : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_DRX_CPU_INT_STA_UNION;
#define GBBP_DRX_CPU_INT_STA_drx_int_state_cpu24_START  (24)
#define GBBP_DRX_CPU_INT_STA_drx_int_state_cpu24_END    (24)
#define GBBP_DRX_CPU_INT_STA_drx_int_state_cpu25_START  (25)
#define GBBP_DRX_CPU_INT_STA_drx_int_state_cpu25_END    (25)
#define GBBP_DRX_CPU_INT_STA_drx_int_state_cpu27_START  (27)
#define GBBP_DRX_CPU_INT_STA_drx_int_state_cpu27_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_DRX_CPU_INT_MASK_UNION
 �ṹ˵��  : DRX_CPU_INT_MASK �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x0B000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      drx_cpu_int_mask_reg;
    struct
    {
        unsigned long  reserved_0         : 24; /* bit[0-23] : ���� */
        unsigned long  cpu_drx_int_mask24 : 1;  /* bit[24]   : �����ж����μĴ�����1��ʾ���Σ�0��ʾ�����Ρ�
                                                               ע��CPU��������ʱ��Ҫ������λ����ж�λ�������п����յ����õĻ����жϡ� */
        unsigned long  cpu_drx_int_mask25 : 1;  /* bit[25]   : ARMָ���Ķ�ʱ���߿�ʼ֮�󷢳��Ķ�ʱ�ж����μĴ��� */
        unsigned long  reserved_1         : 1;  /* bit[26]   : ���� */
        unsigned long  cpu_drx_int_mask27 : 1;  /* bit[27]   : ʱ���л���104M�ж�������μĴ��� */
        unsigned long  reserved_2         : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_DRX_CPU_INT_MASK_UNION;
#define GBBP_DRX_CPU_INT_MASK_cpu_drx_int_mask24_START  (24)
#define GBBP_DRX_CPU_INT_MASK_cpu_drx_int_mask24_END    (24)
#define GBBP_DRX_CPU_INT_MASK_cpu_drx_int_mask25_START  (25)
#define GBBP_DRX_CPU_INT_MASK_cpu_drx_int_mask25_END    (25)
#define GBBP_DRX_CPU_INT_MASK_cpu_drx_int_mask27_START  (27)
#define GBBP_DRX_CPU_INT_MASK_cpu_drx_int_mask27_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_DRX_CPU_INT_CLR_UNION
 �ṹ˵��  : DRX_CPU_INT_CLR �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      drx_cpu_int_clr_reg;
    struct
    {
        unsigned long  reserved_0        : 24; /* bit[0-23] : ���� */
        unsigned long  cpu_drx_int_clr24 : 1;  /* bit[24]   : �����ж�����Ĵ��� */
        unsigned long  cpu_drx_int_clr25 : 1;  /* bit[25]   : ARMָ���Ķ�ʱ���߿�ʼ֮�󷢳��Ķ�ʱ�ж�����Ĵ��� */
        unsigned long  reserved_1        : 1;  /* bit[26]   : ���� */
        unsigned long  cpu_drx_int_clr27 : 1;  /* bit[27]   : ʱ���л���104M�ж��������Ĵ��� */
        unsigned long  reserved_2        : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_DRX_CPU_INT_CLR_UNION;
#define GBBP_DRX_CPU_INT_CLR_cpu_drx_int_clr24_START  (24)
#define GBBP_DRX_CPU_INT_CLR_cpu_drx_int_clr24_END    (24)
#define GBBP_DRX_CPU_INT_CLR_cpu_drx_int_clr25_START  (25)
#define GBBP_DRX_CPU_INT_CLR_cpu_drx_int_clr25_END    (25)
#define GBBP_DRX_CPU_INT_CLR_cpu_drx_int_clr27_START  (27)
#define GBBP_DRX_CPU_INT_CLR_cpu_drx_int_clr27_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_DRX_DSP_INT_STA_UNION
 �ṹ˵��  : DRX_DSP_INT_STA �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      drx_dsp_int_sta_reg;
    struct
    {
        unsigned long  reserved_0          : 24; /* bit[0-23] : ���� */
        unsigned long  drx_int_state_dsp24 : 1;  /* bit[24]   : �����ж������32KHzʱ����������źţ�����DRX˯�߽���֮����ARM��
                                                                ������������ʱ���ѡ�
                                                                ע��CPU��������ʱ��Ҫ������λ����ж�λ�������п����յ����õĻ����жϡ� */
        unsigned long  drx_int_state_dsp25 : 1;  /* bit[25]   : GBBP���ﶨʱ���߿�ʼʱ�̲������ж��źţ�һ��104MHz�����źš�����ָʾARM�л���32KHzʱ�ӡ� */
        unsigned long  reserved_1          : 1;  /* bit[26]   : ���� */
        unsigned long  drx_int_state_dsp27 : 1;  /* bit[27]   : �л���104M�ж������104Mʱ����������źţ�����ָʾDRX˯�߽���֮����ARM��
                                                                ����������CPU�������ѡ���ʱ���ѡ� */
        unsigned long  reserved_2          : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_DRX_DSP_INT_STA_UNION;
#define GBBP_DRX_DSP_INT_STA_drx_int_state_dsp24_START  (24)
#define GBBP_DRX_DSP_INT_STA_drx_int_state_dsp24_END    (24)
#define GBBP_DRX_DSP_INT_STA_drx_int_state_dsp25_START  (25)
#define GBBP_DRX_DSP_INT_STA_drx_int_state_dsp25_END    (25)
#define GBBP_DRX_DSP_INT_STA_drx_int_state_dsp27_START  (27)
#define GBBP_DRX_DSP_INT_STA_drx_int_state_dsp27_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_DRX_DSP_INT_MASK_UNION
 �ṹ˵��  : DRX_DSP_INT_MASK �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x0B000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      drx_dsp_int_mask_reg;
    struct
    {
        unsigned long  reserved_0         : 24; /* bit[0-23] : ���� */
        unsigned long  dsp_drx_int_mask24 : 1;  /* bit[24]   : �����ж����μĴ�����1��ʾ���Σ�0��ʾ�����Ρ�
                                                               ע��CPU��������ʱ��Ҫ������λ����ж�λ�������п����յ����õĻ����жϡ� */
        unsigned long  dsp_drx_int_mask25 : 1;  /* bit[25]   : ARMָ���Ķ�ʱ���߿�ʼ֮�󷢳��Ķ�ʱ�ж����μĴ��� */
        unsigned long  reserved_1         : 1;  /* bit[26]   : ���� */
        unsigned long  dsp_drx_int_mask27 : 1;  /* bit[27]   : ʱ���л���104M�ж�������μĴ��� */
        unsigned long  reserved_2         : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_DRX_DSP_INT_MASK_UNION;
#define GBBP_DRX_DSP_INT_MASK_dsp_drx_int_mask24_START  (24)
#define GBBP_DRX_DSP_INT_MASK_dsp_drx_int_mask24_END    (24)
#define GBBP_DRX_DSP_INT_MASK_dsp_drx_int_mask25_START  (25)
#define GBBP_DRX_DSP_INT_MASK_dsp_drx_int_mask25_END    (25)
#define GBBP_DRX_DSP_INT_MASK_dsp_drx_int_mask27_START  (27)
#define GBBP_DRX_DSP_INT_MASK_dsp_drx_int_mask27_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_DRX_DSP_INT_CLR_UNION
 �ṹ˵��  : DRX_DSP_INT_CLR �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      drx_dsp_int_clr_reg;
    struct
    {
        unsigned long  reserved_0        : 24; /* bit[0-23] : ���� */
        unsigned long  dsp_drx_int_clr24 : 1;  /* bit[24]   : �����ж�����Ĵ��� */
        unsigned long  dsp_drx_int_clr25 : 1;  /* bit[25]   : ARMָ���Ķ�ʱ���߿�ʼ֮�󷢳��Ķ�ʱ�ж�����Ĵ��� */
        unsigned long  reserved_1        : 1;  /* bit[26]   : ���� */
        unsigned long  dsp_drx_int_clr27 : 1;  /* bit[27]   : ʱ���л���104M�ж��������Ĵ��� */
        unsigned long  reserved_2        : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_DRX_DSP_INT_CLR_UNION;
#define GBBP_DRX_DSP_INT_CLR_dsp_drx_int_clr24_START  (24)
#define GBBP_DRX_DSP_INT_CLR_dsp_drx_int_clr24_END    (24)
#define GBBP_DRX_DSP_INT_CLR_dsp_drx_int_clr25_START  (25)
#define GBBP_DRX_DSP_INT_CLR_dsp_drx_int_clr25_END    (25)
#define GBBP_DRX_DSP_INT_CLR_dsp_drx_int_clr27_START  (27)
#define GBBP_DRX_DSP_INT_CLR_dsp_drx_int_clr27_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_ARM_INT_DELAY_REG_PD_UNION
 �ṹ˵��  : ARM_INT_DELAY_REG_PD �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_int_delay_reg_pd_reg;
    struct
    {
        unsigned long  cpu_int_dly_clk : 16; /* bit[0-15] : ARM 104M�ж��ӳ��ϱ����ʱ���������λΪimi_clk */
        unsigned long  reserved        : 16; /* bit[16-31]: ���� */
    } reg;
} GBBP_ARM_INT_DELAY_REG_PD_UNION;
#define GBBP_ARM_INT_DELAY_REG_PD_cpu_int_dly_clk_START  (0)
#define GBBP_ARM_INT_DELAY_REG_PD_cpu_int_dly_clk_END    (15)


/*****************************************************************************
 �ṹ��    : GBBP_DSP_INT_DELAY_REG_PD_UNION
 �ṹ˵��  : DSP_INT_DELAY_REG_PD �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_int_delay_reg_pd_reg;
    struct
    {
        unsigned long  dsp_int_dly_clk : 16; /* bit[0-15] : PHY 104M�ж��ӳ��ϱ����ʱ���������λΪimi_clk */
        unsigned long  reserved        : 16; /* bit[16-31]: ���� */
    } reg;
} GBBP_DSP_INT_DELAY_REG_PD_UNION;
#define GBBP_DSP_INT_DELAY_REG_PD_dsp_int_dly_clk_START  (0)
#define GBBP_DSP_INT_DELAY_REG_PD_dsp_int_dly_clk_END    (15)


/*****************************************************************************
 �ṹ��    : GBBP_SLEEP_EN_UNION
 �ṹ˵��  : SLEEP_EN �Ĵ����ṹ���塣��ַƫ����:0x0030����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sleep_en_reg;
    struct
    {
        unsigned long  gdrx_sleep_en    : 1;  /* bit[0]   : bit[0] DRX˯��������д1������1��104MHz��д0�����塣 */
        unsigned long  gdrx_sleep_mode  : 1;  /* bit[1]   : bit[1] 0������˯�ߣ�Ĭ�ϣ���1���ȵ�sleep_pointʱ��ʼ */
        unsigned long  gdrx_wake_up_imi : 1;  /* bit[2]   : bit[2] CPU��������GDRXʹ�ܣ��߼������㡣���ź�����ǰӦ��ȷ��GBBP 104Mϵͳʱ���Ѿ��򿪲����ȶ��� */
        unsigned long  reserved         : 29; /* bit[3-31]: ���� */
    } reg;
} GBBP_SLEEP_EN_UNION;
#define GBBP_SLEEP_EN_gdrx_sleep_en_START     (0)
#define GBBP_SLEEP_EN_gdrx_sleep_en_END       (0)
#define GBBP_SLEEP_EN_gdrx_sleep_mode_START   (1)
#define GBBP_SLEEP_EN_gdrx_sleep_mode_END     (1)
#define GBBP_SLEEP_EN_gdrx_wake_up_imi_START  (2)
#define GBBP_SLEEP_EN_gdrx_wake_up_imi_END    (2)


/*****************************************************************************
 �ṹ��    : GBBP_WAKE_CNF_UNION
 �ṹ˵��  : WAKE_CNF �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      wake_cnf_reg;
    struct
    {
        unsigned long  gdrx_switch_len : 11; /* bit[0-10] : bit[10:0] �ϱ������жϵ�ʱ���л�ʱ����32.768k���������� */
        unsigned long  reserved        : 21; /* bit[11-31]: ���� */
    } reg;
} GBBP_WAKE_CNF_UNION;
#define GBBP_WAKE_CNF_gdrx_switch_len_START  (0)
#define GBBP_WAKE_CNF_gdrx_switch_len_END    (10)


/*****************************************************************************
 �ṹ��    : GBBP_WAKEUP_LEN_UNION
 �ṹ˵��  : WAKEUP_LEN �Ĵ����ṹ���塣��ַƫ����:0x0038����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      wakeup_len_reg;
    struct
    {
        unsigned long  gdrx_wakeup_len : 26; /* bit[0-25] : ˯�ߵ��ϱ������ж����ʱ����32.768k����������������ֵ�������1�� */
        unsigned long  reserved        : 6;  /* bit[26-31]: ���� */
    } reg;
} GBBP_WAKEUP_LEN_UNION;
#define GBBP_WAKEUP_LEN_gdrx_wakeup_len_START  (0)
#define GBBP_WAKEUP_LEN_gdrx_wakeup_len_END    (25)


/*****************************************************************************
 �ṹ��    : GBBP_MSR_CNF_UNION
 �ṹ˵��  : MSR_CNF �Ĵ����ṹ���塣��ַƫ����:0x003C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      msr_cnf_reg;
    struct
    {
        unsigned long  gdrx_msr_frac     : 11; /* bit[0-10] : ˯�߼���С�����֣��ü������Ľ�λ��ʾ1��104Mʱ�ӡ� */
        unsigned long  reserved_0        : 5;  /* bit[11-15]: ���� */
        unsigned long  gdrx_msr_integer  : 7;  /* bit[16-22]: ˯�߼����������֣�����96��104MHzʱ�Ӹ�����
                                                              ��gdrx_msr_timebaseһ���ʾ��˯�߼�����ȫ���������֡� */
        unsigned long  reserved_1        : 1;  /* bit[23]   : ���� */
        unsigned long  gdrx_msr_timebase : 6;  /* bit[24-29]: bit[29:24]˯�߼���96�����֣�ָʾ1��32K�ж��ٸ�96��104M�ӵı�������
                                                              ע������gdrx_msr_timebase��gdrx_msr_integer��gdrx_msr_frac��ʾ��һ��32Kʱ�Ӱ�����104Mʱ�ӵĸ������ֱ���x��y��z��ʾ������������ȡֵ��
                                                              ����ʱ��У׼��������Եõ�һ��32Kʱ���൱��m.n��104Mʱ�ӣ�m��n�ֱ�Ϊ������С�����֡�����֮�������¹�ϵ��m=x*96+y��n=z/2048�� */
        unsigned long  reserved_2        : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_MSR_CNF_UNION;
#define GBBP_MSR_CNF_gdrx_msr_frac_START      (0)
#define GBBP_MSR_CNF_gdrx_msr_frac_END        (10)
#define GBBP_MSR_CNF_gdrx_msr_integer_START   (16)
#define GBBP_MSR_CNF_gdrx_msr_integer_END     (22)
#define GBBP_MSR_CNF_gdrx_msr_timebase_START  (24)
#define GBBP_MSR_CNF_gdrx_msr_timebase_END    (29)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_DRX_DEPTH_CFG_UNION
 �ṹ˵��  : CPU_DRX_DEPTH_CFG �Ĵ����ṹ���塣��ַƫ����:0x0040����ֵ:0x00000200�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      cpu_drx_depth_cfg_reg;
    struct
    {
        unsigned long  cpu_drx_depth : 27; /* bit[0-26] : AMR�ж�GBBP˯��ʱ����ȵ�����ֵ����GDRX�ڲ�32K����ֵ���ڸ�����ʱ���ڲ������ź�Ϊ1��֪ͨARM�� */
        unsigned long  reserved      : 5;  /* bit[27-31]: ���� */
    } reg;
} GBBP_CPU_DRX_DEPTH_CFG_UNION;
#define GBBP_CPU_DRX_DEPTH_CFG_cpu_drx_depth_START  (0)
#define GBBP_CPU_DRX_DEPTH_CFG_cpu_drx_depth_END    (26)


/*****************************************************************************
 �ṹ��    : GBBP_WAKE_GTC_QB_FRAC_RPT_UNION
 �ṹ˵��  : WAKE_GTC_QB_FRAC_RPT �Ĵ����ṹ���塣��ַƫ����:0x0050����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      wake_gtc_qb_frac_rpt_reg;
    struct
    {
        unsigned long  gdrx_gtc_wake_frac : 7;  /* bit[0-6]  : DRX�����л�ʱ���ص�GTC��FRAC����ֵ�������� */
        unsigned long  reserved_0         : 9;  /* bit[7-15] : ���� */
        unsigned long  gdrx_gtc_wake_chip : 13; /* bit[16-28]: DRX�����л�ʱ���ص�GTC��gtc_timebase����ֵ�������� */
        unsigned long  reserved_1         : 3;  /* bit[29-31]: ���� */
    } reg;
} GBBP_WAKE_GTC_QB_FRAC_RPT_UNION;
#define GBBP_WAKE_GTC_QB_FRAC_RPT_gdrx_gtc_wake_frac_START  (0)
#define GBBP_WAKE_GTC_QB_FRAC_RPT_gdrx_gtc_wake_frac_END    (6)
#define GBBP_WAKE_GTC_QB_FRAC_RPT_gdrx_gtc_wake_chip_START  (16)
#define GBBP_WAKE_GTC_QB_FRAC_RPT_gdrx_gtc_wake_chip_END    (28)


/*****************************************************************************
 �ṹ��    : GBBP_WAKE_GTC_T1_T2_T3_RPT_UNION
 �ṹ˵��  : WAKE_GTC_T1_T2_T3_RPT �Ĵ����ṹ���塣��ַƫ����:0x0054����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      wake_gtc_t1_t2_t3_rpt_reg;
    struct
    {
        unsigned long  gdrx_gtc_t1_cnt : 11; /* bit[0-10] : DRX�����л�ʱ���ص�GTC��T1����ֵ�������� */
        unsigned long  reserved_0      : 5;  /* bit[11-15]: ���� */
        unsigned long  gdrx_gtc_t2_cnt : 5;  /* bit[16-20]: DRX�����л�ʱ���ص�GTC��T2����ֵ�������� */
        unsigned long  reserved_1      : 3;  /* bit[21-23]: ���� */
        unsigned long  gdrx_gtc_t3_cnt : 6;  /* bit[24-29]: DRX�����л�ʱ���ص�GTC��T3����ֵ�������� */
        unsigned long  reserved_2      : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_WAKE_GTC_T1_T2_T3_RPT_UNION;
#define GBBP_WAKE_GTC_T1_T2_T3_RPT_gdrx_gtc_t1_cnt_START  (0)
#define GBBP_WAKE_GTC_T1_T2_T3_RPT_gdrx_gtc_t1_cnt_END    (10)
#define GBBP_WAKE_GTC_T1_T2_T3_RPT_gdrx_gtc_t2_cnt_START  (16)
#define GBBP_WAKE_GTC_T1_T2_T3_RPT_gdrx_gtc_t2_cnt_END    (20)
#define GBBP_WAKE_GTC_T1_T2_T3_RPT_gdrx_gtc_t3_cnt_START  (24)
#define GBBP_WAKE_GTC_T1_T2_T3_RPT_gdrx_gtc_t3_cnt_END    (29)


/*****************************************************************************
 �ṹ��    : GBBP_DRX_WAKE_GTC_FN_RPT_UNION
 �ṹ˵��  : DRX_WAKE_GTC_FN_RPT �Ĵ����ṹ���塣��ַƫ����:0x0058����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      drx_wake_gtc_fn_rpt_reg;
    struct
    {
        unsigned long  gdrx_gtc_fn_low  : 11; /* bit[0-10] : DRX�����л�ʱ���ص�GTC��FN_LOW����ֵ�������� */
        unsigned long  reserved_0       : 5;  /* bit[11-15]: ���� */
        unsigned long  gdrx_gtc_fn_high : 11; /* bit[16-26]: DRX�����л�ʱ���ص�GTC��FN_HIGH����ֵ�������� */
        unsigned long  reserved_1       : 5;  /* bit[27-31]: ���� */
    } reg;
} GBBP_DRX_WAKE_GTC_FN_RPT_UNION;
#define GBBP_DRX_WAKE_GTC_FN_RPT_gdrx_gtc_fn_low_START   (0)
#define GBBP_DRX_WAKE_GTC_FN_RPT_gdrx_gtc_fn_low_END     (10)
#define GBBP_DRX_WAKE_GTC_FN_RPT_gdrx_gtc_fn_high_START  (16)
#define GBBP_DRX_WAKE_GTC_FN_RPT_gdrx_gtc_fn_high_END    (26)


/*****************************************************************************
 �ṹ��    : GBBP_GDRX_INT_MASK_STATE_RPT_UNION
 �ṹ˵��  : GDRX_INT_MASK_STATE_RPT �Ĵ����ṹ���塣��ַƫ����:0x005C����ֵ:0x00110000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      gdrx_int_mask_state_rpt_reg;
    struct
    {
        unsigned long  drx_int_state_cpu    : 1;  /* bit[0]    : DRXģ���ж�״̬�ϱ�ARM
                                                                 �ж�״̬�ϱ�����0x01200�Ĵ���bit24�ϱ�ֵ�� ������ */
        unsigned long  reserved_0           : 3;  /* bit[1-3]  : ���� */
        unsigned long  drx_int_state_dsp    : 1;  /* bit[4]    : DRXģ���ж�״̬�ϱ�PHY
                                                                 �ж�״̬�ϱ�����0x01200�Ĵ���bit24�ϱ�ֵ���������� */
        unsigned long  reserved_1           : 11; /* bit[5-15] : ���� */
        unsigned long  cpu_drx_int_mask_32k : 1;  /* bit[16]   : DRXģ���ж�����ARM����ֵ�ϱ���DRXģ����ж����μ���0xd1204�Ĵ���bit24����ֵ�������� */
        unsigned long  reserved_2           : 3;  /* bit[17-19]: ���� */
        unsigned long  dsp_drx_int_mask_32k : 1;  /* bit[20]   : DRXģ���ж�����PHY����ֵ�ϱ���DRXģ����ж����μ���0xD1214�Ĵ���bit24����ֵ�������� */
        unsigned long  reserved_3           : 11; /* bit[21-31]: ���� */
    } reg;
} GBBP_GDRX_INT_MASK_STATE_RPT_UNION;
#define GBBP_GDRX_INT_MASK_STATE_RPT_drx_int_state_cpu_START     (0)
#define GBBP_GDRX_INT_MASK_STATE_RPT_drx_int_state_cpu_END       (0)
#define GBBP_GDRX_INT_MASK_STATE_RPT_drx_int_state_dsp_START     (4)
#define GBBP_GDRX_INT_MASK_STATE_RPT_drx_int_state_dsp_END       (4)
#define GBBP_GDRX_INT_MASK_STATE_RPT_cpu_drx_int_mask_32k_START  (16)
#define GBBP_GDRX_INT_MASK_STATE_RPT_cpu_drx_int_mask_32k_END    (16)
#define GBBP_GDRX_INT_MASK_STATE_RPT_dsp_drx_int_mask_32k_START  (20)
#define GBBP_GDRX_INT_MASK_STATE_RPT_dsp_drx_int_mask_32k_END    (20)


/*****************************************************************************
 �ṹ��    : GBBP_DRX_TEST_PIN_SEL_UNION
 �ṹ˵��  : DRX_TEST_PIN_SEL �Ĵ����ṹ���塣��ַƫ����:0x0060����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      drx_test_pin_sel_reg;
    struct
    {
        unsigned long  gdrx_test_pin_sel      : 4;  /* bit[0-3] : GDRXģ���������ѡ���ź� */
        unsigned long  reserved               : 27; /* bit[4-30]: ���� */
        unsigned long  gdrx_test_pin_sel_flag : 1;  /* bit[31]  : GBBPģ�������testpinѡ���źţ����ź�Ϊ1ʱ��ѡ��ǵ�������GDRX��testpin������ѡ������������test_pin */
    } reg;
} GBBP_DRX_TEST_PIN_SEL_UNION;
#define GBBP_DRX_TEST_PIN_SEL_gdrx_test_pin_sel_START       (0)
#define GBBP_DRX_TEST_PIN_SEL_gdrx_test_pin_sel_END         (3)
#define GBBP_DRX_TEST_PIN_SEL_gdrx_test_pin_sel_flag_START  (31)
#define GBBP_DRX_TEST_PIN_SEL_gdrx_test_pin_sel_flag_END    (31)




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

#endif /* end of bbp_gsm_on_interface.h */
