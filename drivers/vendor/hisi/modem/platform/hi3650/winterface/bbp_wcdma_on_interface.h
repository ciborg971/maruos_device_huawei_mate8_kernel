

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __BBP_WCDMA_ON_INTERFACE_H__
#define __BBP_WCDMA_ON_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/***======================================================================***
                     (1/3) register_define_ck_1
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31:11]  ����
 bit[10:0]   ʱ�Ӳ���С�����֣���ck_msr_counter����ck_msr_period��С�����֡�
             ע�⣺DSP����ʱ���������������2048�����ø�BBPʹ�á�
   UNION�ṹ:  WBBP_CK_MSR_FRAC_UNION */
#define WBBP_CK_MSR_FRAC_ADDR                         (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C08)

/* �Ĵ���˵����
 bit[31:11]  ����
 bit[10:0]   ʱ�Ӳ����������֣���ck_msr_counter����ck_msr_period���������֡�
   UNION�ṹ:  WBBP_CK_MSR_INTEGER_UNION */
#define WBBP_CK_MSR_INTEGER_ADDR                      (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C0C)

/* �Ĵ���˵����
 bit[31:12]  ����
 bit[11:0]   ������˯ָʾ��10ms֡��������ʾ�ڻ���֮ǰ�೤ʱ���ڣ�BBP������˯ָʾ����λ��10ms��
   UNION�ṹ:  WBBP_DEEP_SLEEP_THRESHOLD_UNION */
#define WBBP_DEEP_SLEEP_THRESHOLD_ADDR                (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C2C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      �ϱ�ARM����˯ָʾ��1����ʾ��ʱ���뻽��ʱ�̵�ʱ��С��deep_sleep_threshold���õ�ʱ�䣻0����ʾ��ʱ���뻽��ʱ�̵�ʱ�����deep_sleep_threshold���õ�ʱ�䡣
   UNION�ṹ:  WBBP_DEEP_SLEEP_IND_1CARD_UNION */
#define WBBP_DEEP_SLEEP_IND_1CARD_ADDR                (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C30)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      BBP���ѷ�ʽ��1����ʾCPUǿ�ƻ��ѣ�0����ʾBBP��������ʱ�̻��ѡ�
   UNION�ṹ:  WBBP_BBP_WAKEUP_TYPE_2CARD_UNION */
#define WBBP_BBP_WAKEUP_TYPE_2CARD_ADDR               (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C48)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      BBP˯�߲�ѯ��־��1����ʾBBP����˯��״̬��0����ʾBBP���ڻ���״̬��
   UNION�ṹ:  WBBP_BBP_SLEEP_STATUS_2CARD_UNION */
#define WBBP_BBP_SLEEP_STATUS_2CARD_ADDR              (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C4C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      �ϱ�ARM����˯ָʾ��1����ʾ��ʱ���뻽��ʱ�̵�ʱ��С��deep_sleep_threshold���õ�ʱ�䣻0����ʾ��ʱ���뻽��ʱ�̵�ʱ�����deep_sleep_threshold���õ�ʱ�䡣
   UNION�ṹ:  WBBP_DEEP_SLEEP_IND_2CARD_UNION */
#define WBBP_DEEP_SLEEP_IND_2CARD_ADDR                (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C50)

/* �Ĵ���˵����
 bit[31:28]  ˯���ڼ�ϵͳ֡��ʱ������slot����ֵ��
             ע�⣺����ڲ�ѯʱ����������ȡ���Σ�������ε�ֵ��ͬ�����ʾ��ȡ�Ľ����ȷ��
 bit[27:16]  ˯���ڼ�ϵͳ֡��ʱ������chip����ֵ��
             ע�⣺����ڲ�ѯʱ����������ȡ���Σ�������ε�ֵ��ͬ�����ʾ��ȡ�Ľ����ȷ��
 bit[15:12]  ˯���ڼ�ϵͳ֡��ʱ������clk����ֵ��
             ע�⣺����ڲ�ѯʱ����������ȡ���Σ�������ε�ֵ��ͬ�����ʾ��ȡ�Ľ����ȷ��
 bit[11:0]   ˯���ڼ�SFN��
             ע�⣺����ڲ�ѯʱ����������ȡ���Σ�������ε�ֵ��ͬ�����ʾ��ȡ�Ľ����ȷ��
   UNION�ṹ:  WBBP_SYS_CNT_SLEEP_2CARD_UNION */
#define WBBP_SYS_CNT_SLEEP_2CARD_ADDR                 (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C54)

/* �Ĵ���˵����
 bit[31:28]  ˯���ڼ�ϵͳ֡��ʱ������slot����ֵ��
             ע�⣺����ڲ�ѯʱ����������ȡ���Σ�������ε�ֵ��ͬ�����ʾ��ȡ�Ľ����ȷ��
 bit[27:16]  ˯���ڼ�ϵͳ֡��ʱ������chip����ֵ��
             ע�⣺����ڲ�ѯʱ����������ȡ���Σ�������ε�ֵ��ͬ�����ʾ��ȡ�Ľ����ȷ��
 bit[15:12]  ˯���ڼ�ϵͳ֡��ʱ������clk����ֵ��
             ע�⣺����ڲ�ѯʱ����������ȡ���Σ�������ε�ֵ��ͬ�����ʾ��ȡ�Ľ����ȷ��
 bit[11:0]   ˯���ڼ�SFN��
             ע�⣺����ڲ�ѯʱ����������ȡ���Σ�������ε�ֵ��ͬ�����ʾ��ȡ�Ľ����ȷ��
   UNION�ṹ:  WBBP_SYS_CNT_SLEEP_1CARD_UNION */
#define WBBP_SYS_CNT_SLEEP_1CARD_ADDR                 (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C64)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      BBP���ѷ�ʽ��1����ʾCPUǿ�ƻ��ѣ�0����ʾBBP��������ʱ�̻��ѡ�
   UNION�ṹ:  WBBP_BBP_WAKEUP_TYPE_1CARD_UNION */
#define WBBP_BBP_WAKEUP_TYPE_1CARD_ADDR               (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C70)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      BBP˯�߲�ѯ��־��1����ʾBBP����˯��״̬��0����ʾBBP���ڻ���״̬��
   UNION�ṹ:  WBBP_BBP_SLEEP_STATUS_1CARD_UNION */
#define WBBP_BBP_SLEEP_STATUS_1CARD_ADDR              (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C74)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    �ж�״̬�Ĵ�����1����ʾ��Ӧ����λ�����жϣ�0����ʾ��Ӧ����λ��û���жϡ�
   UNION�ṹ:  WBBP_ARM_INT02_STA_UNION */
#define WBBP_ARM_INT02_STA_ADDR                       (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C80)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      �ж�ʹ�ܼĴ�����1����ʾʹ���жϣ�0����ʾ��ʹ���жϡ�
   UNION�ṹ:  WBBP_ARM_INT02_EN_UNION */
#define WBBP_ARM_INT02_EN_ADDR                        (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C88)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    �ж�״̬�Ĵ�����1����ʾ��Ӧ����λ�����жϣ�0����ʾ��Ӧ����λ��û���жϡ�
   UNION�ṹ:  WBBP_ARM_INT03_STA_UNION */
#define WBBP_ARM_INT03_STA_ADDR                       (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C90)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      �ж�ʹ�ܼĴ�����1����ʾʹ���жϣ�0����ʾ��ʹ���жϡ�
   UNION�ṹ:  WBBP_ARM_INT03_EN_UNION */
#define WBBP_ARM_INT03_EN_ADDR                        (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C98)

/* �Ĵ���˵����
 bit[31:7]   ����
 bit[6]      Card2 DRX RST���ƣ�����IMIʱ����RST��
             ��λʱ������bit��1��֮���ٽ���bit��λΪ0��
 bit[5]      Card2 DRX RST���ƣ�����32kʱ����RST��
             ��λʱ������bit��1��֮���ٽ���bit��λΪ0��
 bit[4]      Card2 DRX RST���ƣ�����61Mʱ����RST��
             ��λʱ������bit��1��֮���ٽ���bit��λΪ0��
 bit[3]      ����
 bit[2]      Card1 DRX RST���ƣ�����IMIʱ����RST��
             ��λʱ������bit��1��֮���ٽ���bit��λΪ0��
 bit[1]      Card1 DRX RST���ƣ�����32kʱ����RST��
             ��λʱ������bit��1��֮���ٽ���bit��λΪ0��
 bit[0]      Card1 DRX RST���ƣ�����61Mʱ����RST��
             ��λʱ������bit��1��֮���ٽ���bit��λΪ0��
   UNION�ṹ:  WBBP_DRX_RST_CON_UNION */
#define WBBP_DRX_RST_CON_ADDR                         (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1CC0)

/* �Ĵ���˵����
 bit[31]     DRX̬AFCֵָʾ��
 bit[30:12]  ����
 bit[11:0]   DRX̬AFCֵ��
   UNION�ṹ:  WBBP_DRX_AFC_VALUE_UNION */
#define WBBP_DRX_AFC_VALUE_ADDR                       (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1CC4)

/* �Ĵ���˵����
   ��      �������Ѻ�ʱ���л��жϱ�ԭ��Ԥ����ʱ�����˶���32kʱ������
   UNION�ṹ ���� */
#define WBBP_SWITCH_DELAY_CNT_1CARD_ADDR              (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1CC8)

/* �Ĵ���˵����
   ��      �������Ѻ�ʱ���л��жϱ�ԭ��Ԥ����ʱ�����˶���32kʱ������
   UNION�ṹ ���� */
#define WBBP_SWITCH_DELAY_CNT_2CARD_ADDR              (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1CCC)



/***======================================================================***
                     (2/3) register_define_ck_2
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ����˯��ģʽʹ�ܡ�1����ʾBBP��������˯�ߣ�0����Ч��BBP�ڲ������źŴ���Ϊ�����źš�
   UNION�ṹ:  WBBP_SLEEP_EN_1CARD_UNION */
#define WBBP_SLEEP_EN_1CARD_ADDR                      (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C00)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      CPUǿ�ƻ���ʹ�ܡ�1����ʾBBP�������ѣ�0����Ч��BBP�ڲ������źŴ���Ϊ�����źš�
   UNION�ṹ:  WBBP_SWITCH_UP_1CARD_UNION */
#define WBBP_SWITCH_UP_1CARD_ADDR                     (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C04)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��Ȼ���������У�DSPָʾBBP����ʱ���л��жϵ����á�����Ѿ��ﵽʱ���л�ʱ�̣���DSPû�����ô˼Ĵ�������BBP����ά��32k��ʱ��ֱ��DSP���ô˼Ĵ���λ�ã��ٲ���ʱ���л��ж�
   UNION�ṹ:  WBBP_DSP_READY_IND_1CARD_UNION */
#define WBBP_DSP_READY_IND_1CARD_ADDR                 (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C10)

/* �Ĵ���˵����
 bit[31:12]  ����
 bit[11:0]   �ӻ���ʱ�̵�ʱ���л�ʱ��32.768kʱ�Ӹ�����
   UNION�ṹ:  WBBP_CK_SWITCH_CNT_1CARD_UNION */
#define WBBP_CK_SWITCH_CNT_1CARD_ADDR                 (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C14)

/* �Ĵ���˵����
 bit[31:12]  ����
 bit[11:0]   ����ʱ��SFNֵ��
   UNION�ṹ:  WBBP_CK_WAKE_SFN_1CARD_UNION */
#define WBBP_CK_WAKE_SFN_1CARD_ADDR                   (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C18)

/* �Ĵ���˵����
 bit[31:20]  ����
 bit[19:16]  ����ʱ��֡�ڼ���ֵslot������
 bit[15:4]   ����ʱ��֡�ڼ���ֵchip������
 bit[3:0]    ����ʱ��֡�ڼ���ֵclk������
   UNION�ṹ:  WBBP_CK_WAKE_CNT_1CARD_UNION */
#define WBBP_CK_WAKE_CNT_1CARD_ADDR                   (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C1C)

/* �Ĵ���˵����
   ��      ������Ȼ���������У�Ԥ��ʱ���л��жϺ����ȴ��೤ʱ���ٲ���ʱ���л��ж�
   UNION�ṹ ���� */
#define WBBP_SWITCH_DELAY_MAX_1CARD_ADDR              (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C20)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      �ж����μĴ�����1����ʾ������Ӧ����λ�õ��жϣ�0����ʾ��������Ӧ����λ�õ��жϡ�
   UNION�ṹ:  WBBP_ARM_INT02_MASK_1CARD_UNION */
#define WBBP_ARM_INT02_MASK_1CARD_ADDR                (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C84)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      �ж�����Ĵ�����1����ʾ�����Ӧ����λ���жϣ�0����ʾ�������Ӧ����λ�õ��жϡ�
   UNION�ṹ:  WBBP_ARM_INT02_CLR_1CARD_UNION */
#define WBBP_ARM_INT02_CLR_1CARD_ADDR                 (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C8C)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    �ж����μĴ�����1����ʾ������Ӧ����λ�õ��жϣ�0����ʾ��������Ӧ����λ�õ��жϡ�
   UNION�ṹ:  WBBP_ARM_INT03_MASK_1CARD_UNION */
#define WBBP_ARM_INT03_MASK_1CARD_ADDR                (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C94)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    �ж�����Ĵ�����1����ʾ�����Ӧ����λ���жϣ�0����ʾ�������Ӧ����λ�õ��жϡ�
   UNION�ṹ:  WBBP_ARM_INT03_CLR_1CARD_UNION */
#define WBBP_ARM_INT03_CLR_1CARD_ADDR                 (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C9C)



/***======================================================================***
                     (3/3) register_define_ck_3
 ***======================================================================***/
/* �Ĵ���˵����
   ��      ������Ȼ���������У�Ԥ��ʱ���л��жϺ����ȴ��೤ʱ���ٲ���ʱ���л��ж�
   UNION�ṹ ���� */
#define WBBP_SWITCH_DELAY_MAX_2CARD_ADDR              (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C24)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ����˯��ģʽʹ�ܡ�1����ʾBBP��������˯�ߣ�0����Ч��BBP�ڲ������źŴ���Ϊ�����źš�
   UNION�ṹ:  WBBP_SLEEP_EN_2CARD_UNION */
#define WBBP_SLEEP_EN_2CARD_ADDR                      (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C34)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      CPUǿ�ƻ���ʹ�ܡ�1����ʾBBP�������ѣ�0����Ч��BBP�ڲ������źŴ���Ϊ�����źš�
   UNION�ṹ:  WBBP_SWITCH_UP_2CARD_UNION */
#define WBBP_SWITCH_UP_2CARD_ADDR                     (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C38)

/* �Ĵ���˵����
 bit[31:12]  ����
 bit[11:0]   �ӻ���ʱ�̵�ʱ���л�ʱ��32.768kʱ�Ӹ�����
   UNION�ṹ:  WBBP_CK_SWITCH_CNT_2CARD_UNION */
#define WBBP_CK_SWITCH_CNT_2CARD_ADDR                 (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C3C)

/* �Ĵ���˵����
 bit[31:12]  ����
 bit[11:0]   ����ʱ��SFNֵ��
   UNION�ṹ:  WBBP_CK_WAKE_SFN_2CARD_UNION */
#define WBBP_CK_WAKE_SFN_2CARD_ADDR                   (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C40)

/* �Ĵ���˵����
 bit[31:20]  ����
 bit[19:16]  ����ʱ��֡�ڼ���ֵslot������
 bit[15:4]   ����ʱ��֡�ڼ���ֵchip������
 bit[3:0]    ����ʱ��֡�ڼ���ֵclk������
   UNION�ṹ:  WBBP_CK_WAKE_CNT_2CARD_UNION */
#define WBBP_CK_WAKE_CNT_2CARD_ADDR                   (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C44)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��Ȼ���������У�DSPָʾBBP����ʱ���л��жϵ����á�����Ѿ��ﵽʱ���л�ʱ�̣���DSPû�����ô˼Ĵ�������BBP����ά��32k��ʱ��ֱ��DSP���ô˼Ĵ���λ�ã��ٲ���ʱ���л��ж�
   UNION�ṹ:  WBBP_DSP_READY_IND_2CARD_UNION */
#define WBBP_DSP_READY_IND_2CARD_ADDR                 (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1C68)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1]      �ж����μĴ�����1����ʾ������Ӧ����λ�õ��жϣ�0����ʾ��������Ӧ����λ�õ��жϡ�
 bit[0]      ����
   UNION�ṹ:  WBBP_ARM_INT02_MASK_2CARD_UNION */
#define WBBP_ARM_INT02_MASK_2CARD_ADDR                (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1CA0)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1]      �ж�����Ĵ�����1����ʾ�����Ӧ����λ���жϣ�0����ʾ�������Ӧ����λ�õ��жϡ�
 bit[0]      ����
   UNION�ṹ:  WBBP_ARM_INT02_CLR_2CARD_UNION */
#define WBBP_ARM_INT02_CLR_2CARD_ADDR                 (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1CA4)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:2]    �ж����μĴ�����1����ʾ������Ӧ����λ�õ��жϣ�0����ʾ��������Ӧ����λ�õ��жϡ�
 bit[1:0]    ����
   UNION�ṹ:  WBBP_ARM_INT03_MASK_2CARD_UNION */
#define WBBP_ARM_INT03_MASK_2CARD_ADDR                (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1CA8)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:2]    �ж�����Ĵ�����1����ʾ�����Ӧ����λ���жϣ�0����ʾ�������Ӧ����λ�õ��жϡ�
 bit[1:0]    ����
   UNION�ṹ:  WBBP_ARM_INT03_CLR_2CARD_UNION */
#define WBBP_ARM_INT03_CLR_2CARD_ADDR                 (SOC_BBP_WCDMA_ON_BASE_ADDR + 0x1CAC)





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
                     (1/3) register_define_ck_1
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : WBBP_CK_MSR_FRAC_UNION
 �ṹ˵��  : CK_MSR_FRAC �Ĵ����ṹ���塣��ַƫ����:0x08����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ck_msr_frac_reg;
    struct
    {
        unsigned long  ck_msr_frac : 11; /* bit[0-10] : ʱ�Ӳ���С�����֣���ck_msr_counter����ck_msr_period��С�����֡�
                                                        ע�⣺DSP����ʱ���������������2048�����ø�BBPʹ�á� */
        unsigned long  reserved    : 21; /* bit[11-31]: ���� */
    } reg;
} WBBP_CK_MSR_FRAC_UNION;
#define WBBP_CK_MSR_FRAC_ck_msr_frac_START  (0)
#define WBBP_CK_MSR_FRAC_ck_msr_frac_END    (10)


/*****************************************************************************
 �ṹ��    : WBBP_CK_MSR_INTEGER_UNION
 �ṹ˵��  : CK_MSR_INTEGER �Ĵ����ṹ���塣��ַƫ����:0x0C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ck_msr_integer_reg;
    struct
    {
        unsigned long  ck_msr_integer : 11; /* bit[0-10] : ʱ�Ӳ����������֣���ck_msr_counter����ck_msr_period���������֡� */
        unsigned long  reserved       : 21; /* bit[11-31]: ���� */
    } reg;
} WBBP_CK_MSR_INTEGER_UNION;
#define WBBP_CK_MSR_INTEGER_ck_msr_integer_START  (0)
#define WBBP_CK_MSR_INTEGER_ck_msr_integer_END    (10)


/*****************************************************************************
 �ṹ��    : WBBP_DEEP_SLEEP_THRESHOLD_UNION
 �ṹ˵��  : DEEP_SLEEP_THRESHOLD �Ĵ����ṹ���塣��ַƫ����:0x2C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      deep_sleep_threshold_reg;
    struct
    {
        unsigned long  deep_sleep_threshold : 12; /* bit[0-11] : ������˯ָʾ��10ms֡��������ʾ�ڻ���֮ǰ�೤ʱ���ڣ�BBP������˯ָʾ����λ��10ms�� */
        unsigned long  reserved             : 20; /* bit[12-31]: ���� */
    } reg;
} WBBP_DEEP_SLEEP_THRESHOLD_UNION;
#define WBBP_DEEP_SLEEP_THRESHOLD_deep_sleep_threshold_START  (0)
#define WBBP_DEEP_SLEEP_THRESHOLD_deep_sleep_threshold_END    (11)


/*****************************************************************************
 �ṹ��    : WBBP_DEEP_SLEEP_IND_1CARD_UNION
 �ṹ˵��  : DEEP_SLEEP_IND_1CARD �Ĵ����ṹ���塣��ַƫ����:0x30����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      deep_sleep_ind_1card_reg;
    struct
    {
        unsigned long  deep_sleep_ind_1card : 1;  /* bit[0]   : �ϱ�ARM����˯ָʾ��1����ʾ��ʱ���뻽��ʱ�̵�ʱ��С��deep_sleep_threshold���õ�ʱ�䣻0����ʾ��ʱ���뻽��ʱ�̵�ʱ�����deep_sleep_threshold���õ�ʱ�䡣 */
        unsigned long  reserved             : 31; /* bit[1-31]: ���� */
    } reg;
} WBBP_DEEP_SLEEP_IND_1CARD_UNION;
#define WBBP_DEEP_SLEEP_IND_1CARD_deep_sleep_ind_1card_START  (0)
#define WBBP_DEEP_SLEEP_IND_1CARD_deep_sleep_ind_1card_END    (0)


/*****************************************************************************
 �ṹ��    : WBBP_BBP_WAKEUP_TYPE_2CARD_UNION
 �ṹ˵��  : BBP_WAKEUP_TYPE_2CARD �Ĵ����ṹ���塣��ַƫ����:0x48����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbp_wakeup_type_2card_reg;
    struct
    {
        unsigned long  bbp_wakeup_type_2card : 1;  /* bit[0]   : BBP���ѷ�ʽ��1����ʾCPUǿ�ƻ��ѣ�0����ʾBBP��������ʱ�̻��ѡ� */
        unsigned long  reserved              : 31; /* bit[1-31]: ���� */
    } reg;
} WBBP_BBP_WAKEUP_TYPE_2CARD_UNION;
#define WBBP_BBP_WAKEUP_TYPE_2CARD_bbp_wakeup_type_2card_START  (0)
#define WBBP_BBP_WAKEUP_TYPE_2CARD_bbp_wakeup_type_2card_END    (0)


/*****************************************************************************
 �ṹ��    : WBBP_BBP_SLEEP_STATUS_2CARD_UNION
 �ṹ˵��  : BBP_SLEEP_STATUS_2CARD �Ĵ����ṹ���塣��ַƫ����:0x4C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbp_sleep_status_2card_reg;
    struct
    {
        unsigned long  bbp_sleep_status_2card : 1;  /* bit[0]   : BBP˯�߲�ѯ��־��1����ʾBBP����˯��״̬��0����ʾBBP���ڻ���״̬�� */
        unsigned long  reserved               : 31; /* bit[1-31]: ���� */
    } reg;
} WBBP_BBP_SLEEP_STATUS_2CARD_UNION;
#define WBBP_BBP_SLEEP_STATUS_2CARD_bbp_sleep_status_2card_START  (0)
#define WBBP_BBP_SLEEP_STATUS_2CARD_bbp_sleep_status_2card_END    (0)


/*****************************************************************************
 �ṹ��    : WBBP_DEEP_SLEEP_IND_2CARD_UNION
 �ṹ˵��  : DEEP_SLEEP_IND_2CARD �Ĵ����ṹ���塣��ַƫ����:0x50����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      deep_sleep_ind_2card_reg;
    struct
    {
        unsigned long  deep_sleep_ind_2card : 1;  /* bit[0]   : �ϱ�ARM����˯ָʾ��1����ʾ��ʱ���뻽��ʱ�̵�ʱ��С��deep_sleep_threshold���õ�ʱ�䣻0����ʾ��ʱ���뻽��ʱ�̵�ʱ�����deep_sleep_threshold���õ�ʱ�䡣 */
        unsigned long  reserved             : 31; /* bit[1-31]: ���� */
    } reg;
} WBBP_DEEP_SLEEP_IND_2CARD_UNION;
#define WBBP_DEEP_SLEEP_IND_2CARD_deep_sleep_ind_2card_START  (0)
#define WBBP_DEEP_SLEEP_IND_2CARD_deep_sleep_ind_2card_END    (0)


/*****************************************************************************
 �ṹ��    : WBBP_SYS_CNT_SLEEP_2CARD_UNION
 �ṹ˵��  : SYS_CNT_SLEEP_2CARD �Ĵ����ṹ���塣��ַƫ����:0x54����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_sleep_2card_reg;
    struct
    {
        unsigned long  wake_sfn_2card      : 12; /* bit[0-11] : ˯���ڼ�SFN��
                                                                ע�⣺����ڲ�ѯʱ����������ȡ���Σ�������ε�ֵ��ͬ�����ʾ��ȡ�Ľ����ȷ�� */
        unsigned long  wake_cnt_2card_clk  : 4;  /* bit[12-15]: ˯���ڼ�ϵͳ֡��ʱ������clk����ֵ��
                                                                ע�⣺����ڲ�ѯʱ����������ȡ���Σ�������ε�ֵ��ͬ�����ʾ��ȡ�Ľ����ȷ�� */
        unsigned long  wake_cnt_2card_chip : 12; /* bit[16-27]: ˯���ڼ�ϵͳ֡��ʱ������chip����ֵ��
                                                                ע�⣺����ڲ�ѯʱ����������ȡ���Σ�������ε�ֵ��ͬ�����ʾ��ȡ�Ľ����ȷ�� */
        unsigned long  wake_cnt_2card_slot : 4;  /* bit[28-31]: ˯���ڼ�ϵͳ֡��ʱ������slot����ֵ��
                                                                ע�⣺����ڲ�ѯʱ����������ȡ���Σ�������ε�ֵ��ͬ�����ʾ��ȡ�Ľ����ȷ�� */
    } reg;
} WBBP_SYS_CNT_SLEEP_2CARD_UNION;
#define WBBP_SYS_CNT_SLEEP_2CARD_wake_sfn_2card_START       (0)
#define WBBP_SYS_CNT_SLEEP_2CARD_wake_sfn_2card_END         (11)
#define WBBP_SYS_CNT_SLEEP_2CARD_wake_cnt_2card_clk_START   (12)
#define WBBP_SYS_CNT_SLEEP_2CARD_wake_cnt_2card_clk_END     (15)
#define WBBP_SYS_CNT_SLEEP_2CARD_wake_cnt_2card_chip_START  (16)
#define WBBP_SYS_CNT_SLEEP_2CARD_wake_cnt_2card_chip_END    (27)
#define WBBP_SYS_CNT_SLEEP_2CARD_wake_cnt_2card_slot_START  (28)
#define WBBP_SYS_CNT_SLEEP_2CARD_wake_cnt_2card_slot_END    (31)


/*****************************************************************************
 �ṹ��    : WBBP_SYS_CNT_SLEEP_1CARD_UNION
 �ṹ˵��  : SYS_CNT_SLEEP_1CARD �Ĵ����ṹ���塣��ַƫ����:0x64����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_sleep_1card_reg;
    struct
    {
        unsigned long  wake_sfn_1card      : 12; /* bit[0-11] : ˯���ڼ�SFN��
                                                                ע�⣺����ڲ�ѯʱ����������ȡ���Σ�������ε�ֵ��ͬ�����ʾ��ȡ�Ľ����ȷ�� */
        unsigned long  wake_cnt_1card_clk  : 4;  /* bit[12-15]: ˯���ڼ�ϵͳ֡��ʱ������clk����ֵ��
                                                                ע�⣺����ڲ�ѯʱ����������ȡ���Σ�������ε�ֵ��ͬ�����ʾ��ȡ�Ľ����ȷ�� */
        unsigned long  wake_cnt_1card_chip : 12; /* bit[16-27]: ˯���ڼ�ϵͳ֡��ʱ������chip����ֵ��
                                                                ע�⣺����ڲ�ѯʱ����������ȡ���Σ�������ε�ֵ��ͬ�����ʾ��ȡ�Ľ����ȷ�� */
        unsigned long  wake_cnt_1card_slot : 4;  /* bit[28-31]: ˯���ڼ�ϵͳ֡��ʱ������slot����ֵ��
                                                                ע�⣺����ڲ�ѯʱ����������ȡ���Σ�������ε�ֵ��ͬ�����ʾ��ȡ�Ľ����ȷ�� */
    } reg;
} WBBP_SYS_CNT_SLEEP_1CARD_UNION;
#define WBBP_SYS_CNT_SLEEP_1CARD_wake_sfn_1card_START       (0)
#define WBBP_SYS_CNT_SLEEP_1CARD_wake_sfn_1card_END         (11)
#define WBBP_SYS_CNT_SLEEP_1CARD_wake_cnt_1card_clk_START   (12)
#define WBBP_SYS_CNT_SLEEP_1CARD_wake_cnt_1card_clk_END     (15)
#define WBBP_SYS_CNT_SLEEP_1CARD_wake_cnt_1card_chip_START  (16)
#define WBBP_SYS_CNT_SLEEP_1CARD_wake_cnt_1card_chip_END    (27)
#define WBBP_SYS_CNT_SLEEP_1CARD_wake_cnt_1card_slot_START  (28)
#define WBBP_SYS_CNT_SLEEP_1CARD_wake_cnt_1card_slot_END    (31)


/*****************************************************************************
 �ṹ��    : WBBP_BBP_WAKEUP_TYPE_1CARD_UNION
 �ṹ˵��  : BBP_WAKEUP_TYPE_1CARD �Ĵ����ṹ���塣��ַƫ����:0x70����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbp_wakeup_type_1card_reg;
    struct
    {
        unsigned long  bbp_wakeup_type_1card : 1;  /* bit[0]   : BBP���ѷ�ʽ��1����ʾCPUǿ�ƻ��ѣ�0����ʾBBP��������ʱ�̻��ѡ� */
        unsigned long  reserved              : 31; /* bit[1-31]: ���� */
    } reg;
} WBBP_BBP_WAKEUP_TYPE_1CARD_UNION;
#define WBBP_BBP_WAKEUP_TYPE_1CARD_bbp_wakeup_type_1card_START  (0)
#define WBBP_BBP_WAKEUP_TYPE_1CARD_bbp_wakeup_type_1card_END    (0)


/*****************************************************************************
 �ṹ��    : WBBP_BBP_SLEEP_STATUS_1CARD_UNION
 �ṹ˵��  : BBP_SLEEP_STATUS_1CARD �Ĵ����ṹ���塣��ַƫ����:0x74����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbp_sleep_status_1card_reg;
    struct
    {
        unsigned long  bbp_sleep_status_1card : 1;  /* bit[0]   : BBP˯�߲�ѯ��־��1����ʾBBP����˯��״̬��0����ʾBBP���ڻ���״̬�� */
        unsigned long  reserved               : 31; /* bit[1-31]: ���� */
    } reg;
} WBBP_BBP_SLEEP_STATUS_1CARD_UNION;
#define WBBP_BBP_SLEEP_STATUS_1CARD_bbp_sleep_status_1card_START  (0)
#define WBBP_BBP_SLEEP_STATUS_1CARD_bbp_sleep_status_1card_END    (0)


/*****************************************************************************
 �ṹ��    : WBBP_ARM_INT02_STA_UNION
 �ṹ˵��  : ARM_INT02_STA �Ĵ����ṹ���塣��ַƫ����:0x80����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_int02_sta_reg;
    struct
    {
        unsigned long  arm_int02_sta : 2;  /* bit[0-1] : �ж�״̬�Ĵ�����1����ʾ��Ӧ����λ�����жϣ�0����ʾ��Ӧ����λ��û���жϡ� */
        unsigned long  reserved      : 30; /* bit[2-31]: ���� */
    } reg;
} WBBP_ARM_INT02_STA_UNION;
#define WBBP_ARM_INT02_STA_arm_int02_sta_START  (0)
#define WBBP_ARM_INT02_STA_arm_int02_sta_END    (1)


/*****************************************************************************
 �ṹ��    : WBBP_ARM_INT02_EN_UNION
 �ṹ˵��  : ARM_INT02_EN �Ĵ����ṹ���塣��ַƫ����:0x88����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_int02_en_reg;
    struct
    {
        unsigned long  arm_int02_en : 1;  /* bit[0]   : �ж�ʹ�ܼĴ�����1����ʾʹ���жϣ�0����ʾ��ʹ���жϡ� */
        unsigned long  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} WBBP_ARM_INT02_EN_UNION;
#define WBBP_ARM_INT02_EN_arm_int02_en_START  (0)
#define WBBP_ARM_INT02_EN_arm_int02_en_END    (0)


/*****************************************************************************
 �ṹ��    : WBBP_ARM_INT03_STA_UNION
 �ṹ˵��  : ARM_INT03_STA �Ĵ����ṹ���塣��ַƫ����:0x90����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_int03_sta_reg;
    struct
    {
        unsigned long  arm_int03_sta : 4;  /* bit[0-3] : �ж�״̬�Ĵ�����1����ʾ��Ӧ����λ�����жϣ�0����ʾ��Ӧ����λ��û���жϡ� */
        unsigned long  reserved      : 28; /* bit[4-31]: ���� */
    } reg;
} WBBP_ARM_INT03_STA_UNION;
#define WBBP_ARM_INT03_STA_arm_int03_sta_START  (0)
#define WBBP_ARM_INT03_STA_arm_int03_sta_END    (3)


/*****************************************************************************
 �ṹ��    : WBBP_ARM_INT03_EN_UNION
 �ṹ˵��  : ARM_INT03_EN �Ĵ����ṹ���塣��ַƫ����:0x98����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_int03_en_reg;
    struct
    {
        unsigned long  arm_int03_en : 1;  /* bit[0]   : �ж�ʹ�ܼĴ�����1����ʾʹ���жϣ�0����ʾ��ʹ���жϡ� */
        unsigned long  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} WBBP_ARM_INT03_EN_UNION;
#define WBBP_ARM_INT03_EN_arm_int03_en_START  (0)
#define WBBP_ARM_INT03_EN_arm_int03_en_END    (0)


/*****************************************************************************
 �ṹ��    : WBBP_DRX_RST_CON_UNION
 �ṹ˵��  : DRX_RST_CON �Ĵ����ṹ���塣��ַƫ����:0xC0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      drx_rst_con_reg;
    struct
    {
        unsigned long  drx_rst_control_1card_sys : 1;  /* bit[0]   : Card1 DRX RST���ƣ�����61Mʱ����RST��
                                                                     ��λʱ������bit��1��֮���ٽ���bit��λΪ0�� */
        unsigned long  drx_rst_control_1card_32k : 1;  /* bit[1]   : Card1 DRX RST���ƣ�����32kʱ����RST��
                                                                     ��λʱ������bit��1��֮���ٽ���bit��λΪ0�� */
        unsigned long  drx_rst_control_1card_imi : 1;  /* bit[2]   : Card1 DRX RST���ƣ�����IMIʱ����RST��
                                                                     ��λʱ������bit��1��֮���ٽ���bit��λΪ0�� */
        unsigned long  reserved_0                : 1;  /* bit[3]   : ���� */
        unsigned long  drx_rst_control_2card_sys : 1;  /* bit[4]   : Card2 DRX RST���ƣ�����61Mʱ����RST��
                                                                     ��λʱ������bit��1��֮���ٽ���bit��λΪ0�� */
        unsigned long  drx_rst_control_2card_32k : 1;  /* bit[5]   : Card2 DRX RST���ƣ�����32kʱ����RST��
                                                                     ��λʱ������bit��1��֮���ٽ���bit��λΪ0�� */
        unsigned long  drx_rst_control_2card_imi : 1;  /* bit[6]   : Card2 DRX RST���ƣ�����IMIʱ����RST��
                                                                     ��λʱ������bit��1��֮���ٽ���bit��λΪ0�� */
        unsigned long  reserved_1                : 25; /* bit[7-31]: ���� */
    } reg;
} WBBP_DRX_RST_CON_UNION;
#define WBBP_DRX_RST_CON_drx_rst_control_1card_sys_START  (0)
#define WBBP_DRX_RST_CON_drx_rst_control_1card_sys_END    (0)
#define WBBP_DRX_RST_CON_drx_rst_control_1card_32k_START  (1)
#define WBBP_DRX_RST_CON_drx_rst_control_1card_32k_END    (1)
#define WBBP_DRX_RST_CON_drx_rst_control_1card_imi_START  (2)
#define WBBP_DRX_RST_CON_drx_rst_control_1card_imi_END    (2)
#define WBBP_DRX_RST_CON_drx_rst_control_2card_sys_START  (4)
#define WBBP_DRX_RST_CON_drx_rst_control_2card_sys_END    (4)
#define WBBP_DRX_RST_CON_drx_rst_control_2card_32k_START  (5)
#define WBBP_DRX_RST_CON_drx_rst_control_2card_32k_END    (5)
#define WBBP_DRX_RST_CON_drx_rst_control_2card_imi_START  (6)
#define WBBP_DRX_RST_CON_drx_rst_control_2card_imi_END    (6)


/*****************************************************************************
 �ṹ��    : WBBP_DRX_AFC_VALUE_UNION
 �ṹ˵��  : DRX_AFC_VALUE �Ĵ����ṹ���塣��ַƫ����:0xC4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      drx_afc_value_reg;
    struct
    {
        unsigned long  cpu_wdrx_afc_value : 12; /* bit[0-11] : DRX̬AFCֵ�� */
        unsigned long  reserved           : 19; /* bit[12-30]: ���� */
        unsigned long  cpu_wdrx_afc_ind   : 1;  /* bit[31]   : DRX̬AFCֵָʾ�� */
    } reg;
} WBBP_DRX_AFC_VALUE_UNION;
#define WBBP_DRX_AFC_VALUE_cpu_wdrx_afc_value_START  (0)
#define WBBP_DRX_AFC_VALUE_cpu_wdrx_afc_value_END    (11)
#define WBBP_DRX_AFC_VALUE_cpu_wdrx_afc_ind_START    (31)
#define WBBP_DRX_AFC_VALUE_cpu_wdrx_afc_ind_END      (31)


/***======================================================================***
                     (2/3) register_define_ck_2
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : WBBP_SLEEP_EN_1CARD_UNION
 �ṹ˵��  : SLEEP_EN_1CARD �Ĵ����ṹ���塣��ַƫ����:0x00����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sleep_en_1card_reg;
    struct
    {
        unsigned long  sleep_en_1card : 1;  /* bit[0]   : ����˯��ģʽʹ�ܡ�1����ʾBBP��������˯�ߣ�0����Ч��BBP�ڲ������źŴ���Ϊ�����źš� */
        unsigned long  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} WBBP_SLEEP_EN_1CARD_UNION;
#define WBBP_SLEEP_EN_1CARD_sleep_en_1card_START  (0)
#define WBBP_SLEEP_EN_1CARD_sleep_en_1card_END    (0)


/*****************************************************************************
 �ṹ��    : WBBP_SWITCH_UP_1CARD_UNION
 �ṹ˵��  : SWITCH_UP_1CARD �Ĵ����ṹ���塣��ַƫ����:0x04����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      switch_up_1card_reg;
    struct
    {
        unsigned long  switch_up_1card : 1;  /* bit[0]   : CPUǿ�ƻ���ʹ�ܡ�1����ʾBBP�������ѣ�0����Ч��BBP�ڲ������źŴ���Ϊ�����źš� */
        unsigned long  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} WBBP_SWITCH_UP_1CARD_UNION;
#define WBBP_SWITCH_UP_1CARD_switch_up_1card_START  (0)
#define WBBP_SWITCH_UP_1CARD_switch_up_1card_END    (0)


/*****************************************************************************
 �ṹ��    : WBBP_DSP_READY_IND_1CARD_UNION
 �ṹ˵��  : DSP_READY_IND_1CARD �Ĵ����ṹ���塣��ַƫ����:0x10����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_ready_ind_1card_reg;
    struct
    {
        unsigned long  dsp_ready_ind_1card : 1;  /* bit[0]   : ��Ȼ���������У�DSPָʾBBP����ʱ���л��жϵ����á�����Ѿ��ﵽʱ���л�ʱ�̣���DSPû�����ô˼Ĵ�������BBP����ά��32k��ʱ��ֱ��DSP���ô˼Ĵ���λ�ã��ٲ���ʱ���л��ж� */
        unsigned long  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} WBBP_DSP_READY_IND_1CARD_UNION;
#define WBBP_DSP_READY_IND_1CARD_dsp_ready_ind_1card_START  (0)
#define WBBP_DSP_READY_IND_1CARD_dsp_ready_ind_1card_END    (0)


/*****************************************************************************
 �ṹ��    : WBBP_CK_SWITCH_CNT_1CARD_UNION
 �ṹ˵��  : CK_SWITCH_CNT_1CARD �Ĵ����ṹ���塣��ַƫ����:0x14����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ck_switch_cnt_1card_reg;
    struct
    {
        unsigned long  ck_switch_cnt_1card : 12; /* bit[0-11] : �ӻ���ʱ�̵�ʱ���л�ʱ��32.768kʱ�Ӹ����� */
        unsigned long  reserved            : 20; /* bit[12-31]: ���� */
    } reg;
} WBBP_CK_SWITCH_CNT_1CARD_UNION;
#define WBBP_CK_SWITCH_CNT_1CARD_ck_switch_cnt_1card_START  (0)
#define WBBP_CK_SWITCH_CNT_1CARD_ck_switch_cnt_1card_END    (11)


/*****************************************************************************
 �ṹ��    : WBBP_CK_WAKE_SFN_1CARD_UNION
 �ṹ˵��  : CK_WAKE_SFN_1CARD �Ĵ����ṹ���塣��ַƫ����:0x18����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ck_wake_sfn_1card_reg;
    struct
    {
        unsigned long  ck_wake_sfn_1card : 12; /* bit[0-11] : ����ʱ��SFNֵ�� */
        unsigned long  reserved          : 20; /* bit[12-31]: ���� */
    } reg;
} WBBP_CK_WAKE_SFN_1CARD_UNION;
#define WBBP_CK_WAKE_SFN_1CARD_ck_wake_sfn_1card_START  (0)
#define WBBP_CK_WAKE_SFN_1CARD_ck_wake_sfn_1card_END    (11)


/*****************************************************************************
 �ṹ��    : WBBP_CK_WAKE_CNT_1CARD_UNION
 �ṹ˵��  : CK_WAKE_CNT_1CARD �Ĵ����ṹ���塣��ַƫ����:0x1C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ck_wake_cnt_1card_reg;
    struct
    {
        unsigned long  ck_wake_cnt_1card_clk  : 4;  /* bit[0-3]  : ����ʱ��֡�ڼ���ֵclk������ */
        unsigned long  ck_wake_cnt_1card_chip : 12; /* bit[4-15] : ����ʱ��֡�ڼ���ֵchip������ */
        unsigned long  ck_wake_cnt_1card_slot : 4;  /* bit[16-19]: ����ʱ��֡�ڼ���ֵslot������ */
        unsigned long  reserved               : 12; /* bit[20-31]: ���� */
    } reg;
} WBBP_CK_WAKE_CNT_1CARD_UNION;
#define WBBP_CK_WAKE_CNT_1CARD_ck_wake_cnt_1card_clk_START   (0)
#define WBBP_CK_WAKE_CNT_1CARD_ck_wake_cnt_1card_clk_END     (3)
#define WBBP_CK_WAKE_CNT_1CARD_ck_wake_cnt_1card_chip_START  (4)
#define WBBP_CK_WAKE_CNT_1CARD_ck_wake_cnt_1card_chip_END    (15)
#define WBBP_CK_WAKE_CNT_1CARD_ck_wake_cnt_1card_slot_START  (16)
#define WBBP_CK_WAKE_CNT_1CARD_ck_wake_cnt_1card_slot_END    (19)


/*****************************************************************************
 �ṹ��    : WBBP_ARM_INT02_MASK_1CARD_UNION
 �ṹ˵��  : ARM_INT02_MASK_1CARD �Ĵ����ṹ���塣��ַƫ����:0x84����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_int02_mask_1card_reg;
    struct
    {
        unsigned long  arm_int02_mask_1card : 1;  /* bit[0]   : �ж����μĴ�����1����ʾ������Ӧ����λ�õ��жϣ�0����ʾ��������Ӧ����λ�õ��жϡ� */
        unsigned long  reserved             : 31; /* bit[1-31]: ���� */
    } reg;
} WBBP_ARM_INT02_MASK_1CARD_UNION;
#define WBBP_ARM_INT02_MASK_1CARD_arm_int02_mask_1card_START  (0)
#define WBBP_ARM_INT02_MASK_1CARD_arm_int02_mask_1card_END    (0)


/*****************************************************************************
 �ṹ��    : WBBP_ARM_INT02_CLR_1CARD_UNION
 �ṹ˵��  : ARM_INT02_CLR_1CARD �Ĵ����ṹ���塣��ַƫ����:0x8C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_int02_clr_1card_reg;
    struct
    {
        unsigned long  arm_int02_clr_1card : 1;  /* bit[0]   : �ж�����Ĵ�����1����ʾ�����Ӧ����λ���жϣ�0����ʾ�������Ӧ����λ�õ��жϡ� */
        unsigned long  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} WBBP_ARM_INT02_CLR_1CARD_UNION;
#define WBBP_ARM_INT02_CLR_1CARD_arm_int02_clr_1card_START  (0)
#define WBBP_ARM_INT02_CLR_1CARD_arm_int02_clr_1card_END    (0)


/*****************************************************************************
 �ṹ��    : WBBP_ARM_INT03_MASK_1CARD_UNION
 �ṹ˵��  : ARM_INT03_MASK_1CARD �Ĵ����ṹ���塣��ַƫ����:0x94����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_int03_mask_1card_reg;
    struct
    {
        unsigned long  arm_int03_mask_1card : 2;  /* bit[0-1] : �ж����μĴ�����1����ʾ������Ӧ����λ�õ��жϣ�0����ʾ��������Ӧ����λ�õ��жϡ� */
        unsigned long  reserved             : 30; /* bit[2-31]: ���� */
    } reg;
} WBBP_ARM_INT03_MASK_1CARD_UNION;
#define WBBP_ARM_INT03_MASK_1CARD_arm_int03_mask_1card_START  (0)
#define WBBP_ARM_INT03_MASK_1CARD_arm_int03_mask_1card_END    (1)


/*****************************************************************************
 �ṹ��    : WBBP_ARM_INT03_CLR_1CARD_UNION
 �ṹ˵��  : ARM_INT03_CLR_1CARD �Ĵ����ṹ���塣��ַƫ����:0x9C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_int03_clr_1card_reg;
    struct
    {
        unsigned long  arm_int03_clr_1card : 2;  /* bit[0-1] : �ж�����Ĵ�����1����ʾ�����Ӧ����λ���жϣ�0����ʾ�������Ӧ����λ�õ��жϡ� */
        unsigned long  reserved            : 30; /* bit[2-31]: ���� */
    } reg;
} WBBP_ARM_INT03_CLR_1CARD_UNION;
#define WBBP_ARM_INT03_CLR_1CARD_arm_int03_clr_1card_START  (0)
#define WBBP_ARM_INT03_CLR_1CARD_arm_int03_clr_1card_END    (1)


/***======================================================================***
                     (3/3) register_define_ck_3
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : WBBP_SLEEP_EN_2CARD_UNION
 �ṹ˵��  : SLEEP_EN_2CARD �Ĵ����ṹ���塣��ַƫ����:0x34����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sleep_en_2card_reg;
    struct
    {
        unsigned long  sleep_en_2card : 1;  /* bit[0]   : ����˯��ģʽʹ�ܡ�1����ʾBBP��������˯�ߣ�0����Ч��BBP�ڲ������źŴ���Ϊ�����źš� */
        unsigned long  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} WBBP_SLEEP_EN_2CARD_UNION;
#define WBBP_SLEEP_EN_2CARD_sleep_en_2card_START  (0)
#define WBBP_SLEEP_EN_2CARD_sleep_en_2card_END    (0)


/*****************************************************************************
 �ṹ��    : WBBP_SWITCH_UP_2CARD_UNION
 �ṹ˵��  : SWITCH_UP_2CARD �Ĵ����ṹ���塣��ַƫ����:0x38����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      switch_up_2card_reg;
    struct
    {
        unsigned long  switch_up_2card : 1;  /* bit[0]   : CPUǿ�ƻ���ʹ�ܡ�1����ʾBBP�������ѣ�0����Ч��BBP�ڲ������źŴ���Ϊ�����źš� */
        unsigned long  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} WBBP_SWITCH_UP_2CARD_UNION;
#define WBBP_SWITCH_UP_2CARD_switch_up_2card_START  (0)
#define WBBP_SWITCH_UP_2CARD_switch_up_2card_END    (0)


/*****************************************************************************
 �ṹ��    : WBBP_CK_SWITCH_CNT_2CARD_UNION
 �ṹ˵��  : CK_SWITCH_CNT_2CARD �Ĵ����ṹ���塣��ַƫ����:0x3C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ck_switch_cnt_2card_reg;
    struct
    {
        unsigned long  ck_switch_cnt_2card : 12; /* bit[0-11] : �ӻ���ʱ�̵�ʱ���л�ʱ��32.768kʱ�Ӹ����� */
        unsigned long  reserved            : 20; /* bit[12-31]: ���� */
    } reg;
} WBBP_CK_SWITCH_CNT_2CARD_UNION;
#define WBBP_CK_SWITCH_CNT_2CARD_ck_switch_cnt_2card_START  (0)
#define WBBP_CK_SWITCH_CNT_2CARD_ck_switch_cnt_2card_END    (11)


/*****************************************************************************
 �ṹ��    : WBBP_CK_WAKE_SFN_2CARD_UNION
 �ṹ˵��  : CK_WAKE_SFN_2CARD �Ĵ����ṹ���塣��ַƫ����:0x40����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ck_wake_sfn_2card_reg;
    struct
    {
        unsigned long  ck_wake_sfn_2card : 12; /* bit[0-11] : ����ʱ��SFNֵ�� */
        unsigned long  reserved          : 20; /* bit[12-31]: ���� */
    } reg;
} WBBP_CK_WAKE_SFN_2CARD_UNION;
#define WBBP_CK_WAKE_SFN_2CARD_ck_wake_sfn_2card_START  (0)
#define WBBP_CK_WAKE_SFN_2CARD_ck_wake_sfn_2card_END    (11)


/*****************************************************************************
 �ṹ��    : WBBP_CK_WAKE_CNT_2CARD_UNION
 �ṹ˵��  : CK_WAKE_CNT_2CARD �Ĵ����ṹ���塣��ַƫ����:0x44����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ck_wake_cnt_2card_reg;
    struct
    {
        unsigned long  ck_wake_cnt_2card_clk  : 4;  /* bit[0-3]  : ����ʱ��֡�ڼ���ֵclk������ */
        unsigned long  ck_wake_cnt_2card_chip : 12; /* bit[4-15] : ����ʱ��֡�ڼ���ֵchip������ */
        unsigned long  ck_wake_cnt_2card_slot : 4;  /* bit[16-19]: ����ʱ��֡�ڼ���ֵslot������ */
        unsigned long  reserved               : 12; /* bit[20-31]: ���� */
    } reg;
} WBBP_CK_WAKE_CNT_2CARD_UNION;
#define WBBP_CK_WAKE_CNT_2CARD_ck_wake_cnt_2card_clk_START   (0)
#define WBBP_CK_WAKE_CNT_2CARD_ck_wake_cnt_2card_clk_END     (3)
#define WBBP_CK_WAKE_CNT_2CARD_ck_wake_cnt_2card_chip_START  (4)
#define WBBP_CK_WAKE_CNT_2CARD_ck_wake_cnt_2card_chip_END    (15)
#define WBBP_CK_WAKE_CNT_2CARD_ck_wake_cnt_2card_slot_START  (16)
#define WBBP_CK_WAKE_CNT_2CARD_ck_wake_cnt_2card_slot_END    (19)


/*****************************************************************************
 �ṹ��    : WBBP_DSP_READY_IND_2CARD_UNION
 �ṹ˵��  : DSP_READY_IND_2CARD �Ĵ����ṹ���塣��ַƫ����:0x68����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_ready_ind_2card_reg;
    struct
    {
        unsigned long  dsp_ready_ind_2card : 1;  /* bit[0]   : ��Ȼ���������У�DSPָʾBBP����ʱ���л��жϵ����á�����Ѿ��ﵽʱ���л�ʱ�̣���DSPû�����ô˼Ĵ�������BBP����ά��32k��ʱ��ֱ��DSP���ô˼Ĵ���λ�ã��ٲ���ʱ���л��ж� */
        unsigned long  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} WBBP_DSP_READY_IND_2CARD_UNION;
#define WBBP_DSP_READY_IND_2CARD_dsp_ready_ind_2card_START  (0)
#define WBBP_DSP_READY_IND_2CARD_dsp_ready_ind_2card_END    (0)


/*****************************************************************************
 �ṹ��    : WBBP_ARM_INT02_MASK_2CARD_UNION
 �ṹ˵��  : ARM_INT02_MASK_2CARD �Ĵ����ṹ���塣��ַƫ����:0xA0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_int02_mask_2card_reg;
    struct
    {
        unsigned long  reserved_0           : 1;  /* bit[0]   : ���� */
        unsigned long  arm_int02_mask_2card : 1;  /* bit[1]   : �ж����μĴ�����1����ʾ������Ӧ����λ�õ��жϣ�0����ʾ��������Ӧ����λ�õ��жϡ� */
        unsigned long  reserved_1           : 30; /* bit[2-31]: ���� */
    } reg;
} WBBP_ARM_INT02_MASK_2CARD_UNION;
#define WBBP_ARM_INT02_MASK_2CARD_arm_int02_mask_2card_START  (1)
#define WBBP_ARM_INT02_MASK_2CARD_arm_int02_mask_2card_END    (1)


/*****************************************************************************
 �ṹ��    : WBBP_ARM_INT02_CLR_2CARD_UNION
 �ṹ˵��  : ARM_INT02_CLR_2CARD �Ĵ����ṹ���塣��ַƫ����:0xA4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_int02_clr_2card_reg;
    struct
    {
        unsigned long  reserved_0          : 1;  /* bit[0]   : ���� */
        unsigned long  arm_int02_clr_2card : 1;  /* bit[1]   : �ж�����Ĵ�����1����ʾ�����Ӧ����λ���жϣ�0����ʾ�������Ӧ����λ�õ��жϡ� */
        unsigned long  reserved_1          : 30; /* bit[2-31]: ���� */
    } reg;
} WBBP_ARM_INT02_CLR_2CARD_UNION;
#define WBBP_ARM_INT02_CLR_2CARD_arm_int02_clr_2card_START  (1)
#define WBBP_ARM_INT02_CLR_2CARD_arm_int02_clr_2card_END    (1)


/*****************************************************************************
 �ṹ��    : WBBP_ARM_INT03_MASK_2CARD_UNION
 �ṹ˵��  : ARM_INT03_MASK_2CARD �Ĵ����ṹ���塣��ַƫ����:0xA8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_int03_mask_2card_reg;
    struct
    {
        unsigned long  reserved_0           : 2;  /* bit[0-1] : ���� */
        unsigned long  arm_int03_mask_2card : 2;  /* bit[2-3] : �ж����μĴ�����1����ʾ������Ӧ����λ�õ��жϣ�0����ʾ��������Ӧ����λ�õ��жϡ� */
        unsigned long  reserved_1           : 28; /* bit[4-31]: ���� */
    } reg;
} WBBP_ARM_INT03_MASK_2CARD_UNION;
#define WBBP_ARM_INT03_MASK_2CARD_arm_int03_mask_2card_START  (2)
#define WBBP_ARM_INT03_MASK_2CARD_arm_int03_mask_2card_END    (3)


/*****************************************************************************
 �ṹ��    : WBBP_ARM_INT03_CLR_2CARD_UNION
 �ṹ˵��  : ARM_INT03_CLR_2CARD �Ĵ����ṹ���塣��ַƫ����:0xAC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_int03_clr_2card_reg;
    struct
    {
        unsigned long  reserved_0          : 2;  /* bit[0-1] : ���� */
        unsigned long  arm_int03_clr_2card : 2;  /* bit[2-3] : �ж�����Ĵ�����1����ʾ�����Ӧ����λ���жϣ�0����ʾ�������Ӧ����λ�õ��жϡ� */
        unsigned long  reserved_1          : 28; /* bit[4-31]: ���� */
    } reg;
} WBBP_ARM_INT03_CLR_2CARD_UNION;
#define WBBP_ARM_INT03_CLR_2CARD_arm_int03_clr_2card_START  (2)
#define WBBP_ARM_INT03_CLR_2CARD_arm_int03_clr_2card_END    (3)




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

#endif /* end of bbp_wcdma_on_interface.h */
