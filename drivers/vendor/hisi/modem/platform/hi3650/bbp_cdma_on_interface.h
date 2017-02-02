

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __BBP_CDMA_ON_INTERFACE_H__
#define __BBP_CDMA_ON_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/***======================================================================***
                     (1/1) register_define_c_drx
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31:21]  ����
 bit[20:16]  ʱ�Ӳ�������������ֶ�25ȡģ�Ľ����ʱ�Ӳ�������������ֱ�ʾ1��32kʱ���ڣ��ж��ٸ�122.88MHzʱ�ӡ�
 bit[15:11]  ����
 bit[10:0]   ʱ�Ӳ�������������ֳ���25�Ľ����ʱ�Ӳ�������������ֱ�ʾ1��32kʱ���ڣ��ж��ٸ�122.88MHzʱ�ӡ�
   UNION�ṹ:  CBBP_CK_MSR_INTERGER_1X_UNION */
#define CBBP_CK_MSR_INTERGER_1X_ADDR                  (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E00)

/* �Ĵ���˵����
 bit[31:11]  ����
 bit[10:0]   ʱ�Ӳ������С�����֡�����Ϊ1/2048��
   UNION�ṹ:  CBBP_CK_MSR_FRAC_1X_UNION */
#define CBBP_CK_MSR_FRAC_1X_ADDR                      (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E04)

/* �Ĵ���˵����
 bit[31:23]  ����
 bit[22:0]   ˯��ʱ�䣺�ӿ�ʼ˯�ߵ�����ʱ�̵�ʱ�䡣����32kʱ�Ӹ���
   UNION�ṹ:  CBBP_SLEEP_PERIOD_1X_UNION */
#define CBBP_SLEEP_PERIOD_1X_ADDR                     (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E08)

/* �Ĵ���˵����
 bit[31:12]  ����
 bit[11:0]   ��������ʱ����wakeup�жϣ����л�ϵͳ��ʱ֮���ʱ�䡣����Ϊ32kʱ�Ӹ��������ֵ��Ӧʱ��62.5ms��
   UNION�ṹ:  CBBP_CK_SWITCH_CNT_1X_UNION */
#define CBBP_CK_SWITCH_CNT_1X_ADDR                    (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E0C)

/* �Ĵ���˵����
 bit[31:12]  ����
 bit[11:0]   ����wakeupʱ�̻��ж೤ʱ�䣬BBP������˯ָʾ������Ϊ32kʱ�Ӹ�����
   UNION�ṹ:  CBBP_DEEP_SLEEP_CNT_1X_UNION */
#define CBBP_DEEP_SLEEP_CNT_1X_ADDR                   (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E10)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ����˯�ߵ�ģʽ��
             0����ʾ����˯��
             1����ʾ����ָ��ʱ���ٽ���˯��
             
   UNION�ṹ:  CBBP_SLEEP_MODE_UNION */
#define CBBP_SLEEP_MODE_ADDR                          (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E14)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:24]  
 bit[23:22]  ����
 bit[21:16]  
 bit[15:11]  ����
 bit[10:0]   ���ָ���Ľ���˯�ߵ�ʱ�̣�Sleep_mode=1ʱ��Ч��
             [29:24]��sys_cnt_1x_5p12s��ֵ��
             [21:16]��sys_cnt_1x_80ms��ֵ��
             [10:0]��sys_cnt_1x_1p25ms��ֵ��chip���ȣ�
             
   UNION�ṹ:  CBBP_SLEEP_TIME_1X_UNION */
#define CBBP_SLEEP_TIME_1X_ADDR                       (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E18)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ������õ�˯��ָ������źš� Sleep_mode=0ʱ����������˯�ߣ�Sleep_mode=1ʱ���ȴ����õ�ʱ�̽���˯��
   UNION�ṹ:  CBBP_SLEEP_START_1X_UNION */
#define CBBP_SLEEP_START_1X_ADDR                      (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E1C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ǿ�ƻ���ָ������źš�
   UNION�ṹ:  CBBP_SWITCH_UP_1X_UNION */
#define CBBP_SWITCH_UP_1X_ADDR                        (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E20)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��˯ָʾ��1��Ч
   UNION�ṹ:  CBBP_DEEP_SLEEP_IND_1X_UNION */
#define CBBP_DEEP_SLEEP_IND_1X_ADDR                   (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E24)

/* �Ĵ���˵����
 bit[31:23]  ����
 bit[22:0]   �ϱ���˯��ʱ�䣬��32kʱ�����ڸ�����ʾ��
   UNION�ṹ:  CBBP_SLEEP_CNT_32K_1X_UNION */
#define CBBP_SLEEP_CNT_32K_1X_ADDR                    (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E28)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      �������ࡣ
             0����ʾ��Ȼ���ѣ�
             1����ʾǿ�ƻ���
             
   UNION�ṹ:  CBBP_WAKEUP_TYPE_1X_UNION */
#define CBBP_WAKEUP_TYPE_1X_ADDR                      (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E2C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      BBP����˯��״ָ̬ʾ����sleep_start��ʼ��int_32k_to_sys�ڼ�Ϊ1������ʱ��Ϊ0��
   UNION�ṹ:  CBBP_SLEEP_STATUS_1X_UNION */
#define CBBP_SLEEP_STATUS_1X_ADDR                     (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E30)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      sys cnt����ѡ��
             0��ʾ2s
             1��ʾ5.12s
   UNION�ṹ:  CBBP_SYS_CNT_PERIOD_1X_UNION */
#define CBBP_SYS_CNT_PERIOD_1X_ADDR                   (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E34)

/* �Ĵ���˵����
 bit[31]     �ϱ�bbe16�����жϵ�ʹ��
 bit[30:10]  ����
 bit[9:8]    �ϱ�bbe16�����жϵ�clr
             bit0��1x�����жϣ�
             bit1��evdo�����ж�
 bit[7:2]    ����
 bit[1:0]    �ϱ�bbe16�����жϵ�mask��1��ʾ������Ӧ���ж�
             bit0��1x�����жϣ�
             bit1��evdo�����ж�
   UNION�ṹ:  CBBP_WAKEUP_INT_BBE16_UNION */
#define CBBP_WAKEUP_INT_BBE16_ADDR                    (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E50)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    �ϱ�bbe16�����жϵ�sta��1��ʾ��Ӧ���ж���Ч
             bit0��1x�����жϣ�
             bit1��evdo�����ж�
   UNION�ṹ:  CBBP_WAKEUP_INT_STA_BBE16_UNION */
#define CBBP_WAKEUP_INT_STA_BBE16_ADDR                (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E54)

/* �Ĵ���˵����
 bit[31]     �ϱ�arm�����жϵ�ʹ��
 bit[30:10]  ����
 bit[9:8]    �ϱ�arm�����жϵ�clr
             bit0��1x�����жϣ�
             bit1��evdo�����ж�
 bit[7:2]    ����
 bit[1:0]    �ϱ�arm�����жϵ�mask��1��ʾ������Ӧ���ж�
             bit0��1x�����жϣ�
             bit1��evdo�����ж�
   UNION�ṹ:  CBBP_WAKEUP_INT_ARM_UNION */
#define CBBP_WAKEUP_INT_ARM_ADDR                      (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E58)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    �ϱ�arm�����жϵ�sta��1��ʾ��Ӧ���ж�
             bit0��1x�����жϣ�
             bit1��evdo�����ж�
   UNION�ṹ:  CBBP_WAKEUP_INT_STA_ARM_UNION */
#define CBBP_WAKEUP_INT_STA_ARM_ADDR                  (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E5C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��Ȼ���������У�����Ѿ�׼���ý���ʱ���л��ж�
   UNION�ṹ:  CBBP_DSP_READY_IND_CDRX_1X_UNION */
#define CBBP_DSP_READY_IND_CDRX_1X_ADDR               (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E60)

/* �Ĵ���˵����
   ��      ����Ԥ��ʱ���л��жϺ󣬵ȴ�����ٸ�32kʱ�Ӻ��ٲ���ʱ���л��ж�
   UNION�ṹ ���� */
#define CBBP_DSP_SWITCH_DELAY_MAX_1X_ADDR             (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E64)

/* �Ĵ���˵����
   ��      ����Ԥ��ʱ���л��жϺ󣬵ȴ��˶೤ʱ���ٲ���ʱ���л��ж�
   UNION�ṹ ���� */
#define CBBP_SWITCH_DELAY_CNT_1X_ADDR                 (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E68)

/* �Ĵ���˵����
 bit[31:21]  ����
 bit[20:16]  ʱ�Ӳ�������������ֶ�25ȡģ�Ľ����ʱ�Ӳ�������������ֱ�ʾ1��32kʱ���ڣ��ж��ٸ�122.88MHzʱ�ӡ�
 bit[15:11]  ����
 bit[10:0]   ʱ�Ӳ�������������ֳ���25�Ľ����ʱ�Ӳ�������������ֱ�ʾ1��32kʱ���ڣ��ж��ٸ�122.88MHzʱ�ӡ�
   UNION�ṹ:  CBBP_CK_MSR_INTERGER_EVDO_UNION */
#define CBBP_CK_MSR_INTERGER_EVDO_ADDR                (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E80)

/* �Ĵ���˵����
 bit[31:11]  ����
 bit[10:0]   ʱ�Ӳ������С�����֡�����Ϊ1/2048��
   UNION�ṹ:  CBBP_CK_MSR_FRAC_EVDO_UNION */
#define CBBP_CK_MSR_FRAC_EVDO_ADDR                    (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E84)

/* �Ĵ���˵����
 bit[31:23]  ����
 bit[22:0]   ˯��ʱ�䣺�ӿ�ʼ˯�ߵ�����ʱ�̵�ʱ�䡣����32kʱ�Ӹ���
   UNION�ṹ:  CBBP_SLEEP_PERIOD_EVDO_UNION */
#define CBBP_SLEEP_PERIOD_EVDO_ADDR                   (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E88)

/* �Ĵ���˵����
 bit[31:12]  ����
 bit[11:0]   ��������ʱ����wakeup�жϣ����л�ϵͳ��ʱ֮���ʱ�䡣����Ϊ32kʱ�Ӹ��������ֵ��Ӧʱ��62.5ms��
   UNION�ṹ:  CBBP_CK_SWITCH_CNT_EVDO_UNION */
#define CBBP_CK_SWITCH_CNT_EVDO_ADDR                  (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E8C)

/* �Ĵ���˵����
 bit[31:12]  ����
 bit[11:0]   ����wakeupʱ�̻��ж೤ʱ�䣬BBP������˯ָʾ������Ϊ32kʱ�Ӹ�����
   UNION�ṹ:  CBBP_DEEP_SLEEP_CNT_EVDO_UNION */
#define CBBP_DEEP_SLEEP_CNT_EVDO_ADDR                 (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E90)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ����˯�ߵ�ģʽ��
             0����ʾ����˯��
             1����ʾ����ָ��ʱ���ٽ���˯��
             
   UNION�ṹ:  CBBP_SLEEP_MODE_EVDO_UNION */
#define CBBP_SLEEP_MODE_EVDO_ADDR                     (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E94)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:24]  
 bit[23:18]  ����
 bit[17:16]  
 bit[15]     ����
 bit[14:0]   ���ָ���Ľ���˯�ߵ�ʱ�̣�Sleep_mode=1ʱ��Ч��
             [29:24]��sys_cnt_evdo_5p12s��ֵ��
             [17:16]��sys_cnt_evdo_80ms��ֵ��
             [14:0]��sys_cnt_evdo_26ms��ֵ��
   UNION�ṹ:  CBBP_SLEEP_TIME_EVDO_UNION */
#define CBBP_SLEEP_TIME_EVDO_ADDR                     (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E98)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ������õ�˯��ָ������źš� Sleep_mode=0ʱ����������˯�ߣ�Sleep_mode=1ʱ���ȴ����õ�ʱ�̽���˯��
   UNION�ṹ:  CBBP_SLEEP_START_EVDO_UNION */
#define CBBP_SLEEP_START_EVDO_ADDR                    (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E9C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ǿ�ƻ���ָ������źš�
   UNION�ṹ:  CBBP_SWITCH_UP_EVDO_UNION */
#define CBBP_SWITCH_UP_EVDO_ADDR                      (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1EA0)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��˯ָʾ��1��Ч
   UNION�ṹ:  CBBP_DEEP_SLEEP_IND_EVDO_UNION */
#define CBBP_DEEP_SLEEP_IND_EVDO_ADDR                 (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1EA4)

/* �Ĵ���˵����
 bit[31:23]  ����
 bit[22:0]   �ϱ���˯��ʱ�䣬��32kʱ�����ڸ�����ʾ��
   UNION�ṹ:  CBBP_SLEEP_CNT_32K_EVDO_UNION */
#define CBBP_SLEEP_CNT_32K_EVDO_ADDR                  (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1EA8)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      �������ࡣ
             0����ʾ��Ȼ���ѣ�
             1����ʾǿ�ƻ���
             
   UNION�ṹ:  CBBP_WAKEUP_TYPE_EVDO_UNION */
#define CBBP_WAKEUP_TYPE_EVDO_ADDR                    (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1EAC)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      BBP����˯��״ָ̬ʾ����sleep_start��ʼ��int_32k_to_sys�ڼ�Ϊ1������ʱ��Ϊ0��
   UNION�ṹ:  CBBP_SLEEP_STATUS_EVDO_UNION */
#define CBBP_SLEEP_STATUS_EVDO_ADDR                   (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1EB0)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      sys cnt����ѡ��
             0��ʾ2s
             1��ʾ5.12s
   UNION�ṹ:  CBBP_SYS_CNT_PERIOD_EVDO_UNION */
#define CBBP_SYS_CNT_PERIOD_EVDO_ADDR                 (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1EB4)

/* �Ĵ���˵����
 bit[31]     �ϱ�bbe16ʱ���л��жϵ�ʹ��
 bit[30:12]  ����
 bit[11:8]   �ϱ�bbe16ʱ���л��жϵ�clr
             bit0��1x����ʱϵͳ��ʱ��32k�л���122M��
             bit1��1x˯��ʱϵͳ��ʱ��122M�л���32k
             bit2��evdo����ʱϵͳ��ʱ��32k�л���122M��
             bit3��evdo˯��ʱϵͳ��ʱ��122M�л���32k
 bit[7:4]    ����
 bit[3:0]    �ϱ�bbe16ʱ���л��жϵ�mask��1��ʾ������Ӧ���ж�
             bit0��1x����ʱϵͳ��ʱ��32k�л���122M��
             bit1��1x˯��ʱϵͳ��ʱ��122M�л���32k
             bit2��evdo����ʱϵͳ��ʱ��32k�л���122M��
             bit3��evdo˯��ʱϵͳ��ʱ��122M�л���32k
   UNION�ṹ:  CBBP_SWITCH_INT_BBE16_UNION */
#define CBBP_SWITCH_INT_BBE16_ADDR                    (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1ED0)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    �ϱ�bbe16ʱ���л��жϵ�sta��1��ʾ��Ӧ���ж�
             bit0��1x����ʱϵͳ��ʱ��32k�л���122M��
             bit1��1x˯��ʱϵͳ��ʱ��122M�л���32k
             bit2��evdo����ʱϵͳ��ʱ��32k�л���122M��
             bit3��evdo˯��ʱϵͳ��ʱ��122M�л���32k
   UNION�ṹ:  CBBP_SWITCH_INT_STA_BBE16_UNION */
#define CBBP_SWITCH_INT_STA_BBE16_ADDR                (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1ED4)

/* �Ĵ���˵����
 bit[31]     �ϱ�armʱ���л��жϵ�ʹ��
 bit[30:12]  ����
 bit[11:8]   �ϱ�armʱ���л��жϵ�clr
             bit0��1x����ʱϵͳ��ʱ��32k�л���122M��
             bit1��1x˯��ʱϵͳ��ʱ��122M�л���32k
             bit2��evdo����ʱϵͳ��ʱ��32k�л���122M��
             bit3��evdo˯��ʱϵͳ��ʱ��122M�л���32k
 bit[7:4]    ����
 bit[3:0]    �ϱ�armʱ���л��жϵ�mask��1��ʾ������Ӧ���ж�
             bit0��1x����ʱϵͳ��ʱ��32k�л���122M��
             bit1��1x˯��ʱϵͳ��ʱ��122M�л���32k
             bit2��evdo����ʱϵͳ��ʱ��32k�л���122M��
             bit3��evdo˯��ʱϵͳ��ʱ��122M�л���32k
   UNION�ṹ:  CBBP_SWITCH_INT_ARM_UNION */
#define CBBP_SWITCH_INT_ARM_ADDR                      (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1ED8)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    �ϱ�armʱ���л��жϵ�STA��1��ʾ��Ӧ���ж�
             bit0��1x����ʱϵͳ��ʱ��32k�л���122M��
             bit1��1x˯��ʱϵͳ��ʱ��122M�л���32k
             bit2��evdo����ʱϵͳ��ʱ��32k�л���122M��
             bit3��evdo˯��ʱϵͳ��ʱ��122M�л���32k
   UNION�ṹ:  CBBP_SWITCH_INT_STA_ARM_UNION */
#define CBBP_SWITCH_INT_STA_ARM_ADDR                  (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1EDC)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��Ȼ���������У�����Ѿ�׼���ý���ʱ���л��ж�
   UNION�ṹ:  CBBP_DSP_READY_IND_CDRX_EVDO_UNION */
#define CBBP_DSP_READY_IND_CDRX_EVDO_ADDR             (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1EE0)

/* �Ĵ���˵����
   ��      ����Ԥ��ʱ���л��жϺ󣬵ȴ�����ٸ�32kʱ�Ӻ��ٲ���ʱ���л��ж�
   UNION�ṹ ���� */
#define CBBP_DSP_SWITCH_DELAY_MAX_EVDO_ADDR           (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1EE4)

/* �Ĵ���˵����
   ��      ����Ԥ��ʱ���л��жϺ󣬵ȴ��˶೤ʱ���ٲ���ʱ���л��ж�
   UNION�ṹ ���� */
#define CBBP_SWITCH_DELAY_CNT_EVDO_ADDR               (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1EE8)





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
                     (1/1) register_define_c_drx
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : CBBP_CK_MSR_INTERGER_1X_UNION
 �ṹ˵��  : CK_MSR_INTERGER_1X �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ck_msr_interger_1x_reg;
    struct
    {
        unsigned long  ck_msr_integer_26ms_1x    : 11; /* bit[0-10] : ʱ�Ӳ�������������ֳ���25�Ľ����ʱ�Ӳ�������������ֱ�ʾ1��32kʱ���ڣ��ж��ٸ�122.88MHzʱ�ӡ� */
        unsigned long  reserved_0                : 5;  /* bit[11-15]: ���� */
        unsigned long  ck_msr_integer_1_4chip_1x : 5;  /* bit[16-20]: ʱ�Ӳ�������������ֶ�25ȡģ�Ľ����ʱ�Ӳ�������������ֱ�ʾ1��32kʱ���ڣ��ж��ٸ�122.88MHzʱ�ӡ� */
        unsigned long  reserved_1                : 11; /* bit[21-31]: ���� */
    } reg;
} CBBP_CK_MSR_INTERGER_1X_UNION;
#define CBBP_CK_MSR_INTERGER_1X_ck_msr_integer_26ms_1x_START     (0)
#define CBBP_CK_MSR_INTERGER_1X_ck_msr_integer_26ms_1x_END       (10)
#define CBBP_CK_MSR_INTERGER_1X_ck_msr_integer_1_4chip_1x_START  (16)
#define CBBP_CK_MSR_INTERGER_1X_ck_msr_integer_1_4chip_1x_END    (20)


/*****************************************************************************
 �ṹ��    : CBBP_CK_MSR_FRAC_1X_UNION
 �ṹ˵��  : CK_MSR_FRAC_1X �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ck_msr_frac_1x_reg;
    struct
    {
        unsigned long  ck_msr_frac_1x : 11; /* bit[0-10] : ʱ�Ӳ������С�����֡�����Ϊ1/2048�� */
        unsigned long  reserved       : 21; /* bit[11-31]: ���� */
    } reg;
} CBBP_CK_MSR_FRAC_1X_UNION;
#define CBBP_CK_MSR_FRAC_1X_ck_msr_frac_1x_START  (0)
#define CBBP_CK_MSR_FRAC_1X_ck_msr_frac_1x_END    (10)


/*****************************************************************************
 �ṹ��    : CBBP_SLEEP_PERIOD_1X_UNION
 �ṹ˵��  : SLEEP_PERIOD_1X �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sleep_period_1x_reg;
    struct
    {
        unsigned long  sleep_period_1x : 23; /* bit[0-22] : ˯��ʱ�䣺�ӿ�ʼ˯�ߵ�����ʱ�̵�ʱ�䡣����32kʱ�Ӹ��� */
        unsigned long  reserved        : 9;  /* bit[23-31]: ���� */
    } reg;
} CBBP_SLEEP_PERIOD_1X_UNION;
#define CBBP_SLEEP_PERIOD_1X_sleep_period_1x_START  (0)
#define CBBP_SLEEP_PERIOD_1X_sleep_period_1x_END    (22)


/*****************************************************************************
 �ṹ��    : CBBP_CK_SWITCH_CNT_1X_UNION
 �ṹ˵��  : CK_SWITCH_CNT_1X �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ck_switch_cnt_1x_reg;
    struct
    {
        unsigned long  ck_switch_cnt_1x : 12; /* bit[0-11] : ��������ʱ����wakeup�жϣ����л�ϵͳ��ʱ֮���ʱ�䡣����Ϊ32kʱ�Ӹ��������ֵ��Ӧʱ��62.5ms�� */
        unsigned long  reserved         : 20; /* bit[12-31]: ���� */
    } reg;
} CBBP_CK_SWITCH_CNT_1X_UNION;
#define CBBP_CK_SWITCH_CNT_1X_ck_switch_cnt_1x_START  (0)
#define CBBP_CK_SWITCH_CNT_1X_ck_switch_cnt_1x_END    (11)


/*****************************************************************************
 �ṹ��    : CBBP_DEEP_SLEEP_CNT_1X_UNION
 �ṹ˵��  : DEEP_SLEEP_CNT_1X �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      deep_sleep_cnt_1x_reg;
    struct
    {
        unsigned long  deep_sleep_cnt_1x : 12; /* bit[0-11] : ����wakeupʱ�̻��ж೤ʱ�䣬BBP������˯ָʾ������Ϊ32kʱ�Ӹ����� */
        unsigned long  reserved          : 20; /* bit[12-31]: ���� */
    } reg;
} CBBP_DEEP_SLEEP_CNT_1X_UNION;
#define CBBP_DEEP_SLEEP_CNT_1X_deep_sleep_cnt_1x_START  (0)
#define CBBP_DEEP_SLEEP_CNT_1X_deep_sleep_cnt_1x_END    (11)


/*****************************************************************************
 �ṹ��    : CBBP_SLEEP_MODE_UNION
 �ṹ˵��  : SLEEP_MODE �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sleep_mode_reg;
    struct
    {
        unsigned long  sleep_mode_1x : 1;  /* bit[0]   : ����˯�ߵ�ģʽ��
                                                         0����ʾ����˯��
                                                         1����ʾ����ָ��ʱ���ٽ���˯�� */
        unsigned long  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_SLEEP_MODE_UNION;
#define CBBP_SLEEP_MODE_sleep_mode_1x_START  (0)
#define CBBP_SLEEP_MODE_sleep_mode_1x_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_SLEEP_TIME_1X_UNION
 �ṹ˵��  : SLEEP_TIME_1X �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sleep_time_1x_reg;
    struct
    {
        unsigned long  sleep_time_1x_1p25ms : 11; /* bit[0-10] : ���ָ���Ľ���˯�ߵ�ʱ�̣�Sleep_mode=1ʱ��Ч��
                                                                 [29:24]��sys_cnt_1x_5p12s��ֵ��
                                                                 [21:16]��sys_cnt_1x_80ms��ֵ��
                                                                 [10:0]��sys_cnt_1x_1p25ms��ֵ��chip���ȣ� */
        unsigned long  reserved_0           : 5;  /* bit[11-15]: ���� */
        unsigned long  sleep_time_1x_80ms   : 6;  /* bit[16-21]:  */
        unsigned long  reserved_1           : 2;  /* bit[22-23]: ���� */
        unsigned long  sleep_time_1x_5p12s  : 6;  /* bit[24-29]:  */
        unsigned long  reserved_2           : 2;  /* bit[30-31]: ���� */
    } reg;
} CBBP_SLEEP_TIME_1X_UNION;
#define CBBP_SLEEP_TIME_1X_sleep_time_1x_1p25ms_START  (0)
#define CBBP_SLEEP_TIME_1X_sleep_time_1x_1p25ms_END    (10)
#define CBBP_SLEEP_TIME_1X_sleep_time_1x_80ms_START    (16)
#define CBBP_SLEEP_TIME_1X_sleep_time_1x_80ms_END      (21)
#define CBBP_SLEEP_TIME_1X_sleep_time_1x_5p12s_START   (24)
#define CBBP_SLEEP_TIME_1X_sleep_time_1x_5p12s_END     (29)


/*****************************************************************************
 �ṹ��    : CBBP_SLEEP_START_1X_UNION
 �ṹ˵��  : SLEEP_START_1X �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sleep_start_1x_reg;
    struct
    {
        unsigned long  sleep_start_1x : 1;  /* bit[0]   : ������õ�˯��ָ������źš� Sleep_mode=0ʱ����������˯�ߣ�Sleep_mode=1ʱ���ȴ����õ�ʱ�̽���˯�� */
        unsigned long  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_SLEEP_START_1X_UNION;
#define CBBP_SLEEP_START_1X_sleep_start_1x_START  (0)
#define CBBP_SLEEP_START_1X_sleep_start_1x_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_SWITCH_UP_1X_UNION
 �ṹ˵��  : SWITCH_UP_1X �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      switch_up_1x_reg;
    struct
    {
        unsigned long  switch_up_1x : 1;  /* bit[0]   : ǿ�ƻ���ָ������źš� */
        unsigned long  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_SWITCH_UP_1X_UNION;
#define CBBP_SWITCH_UP_1X_switch_up_1x_START  (0)
#define CBBP_SWITCH_UP_1X_switch_up_1x_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_DEEP_SLEEP_IND_1X_UNION
 �ṹ˵��  : DEEP_SLEEP_IND_1X �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      deep_sleep_ind_1x_reg;
    struct
    {
        unsigned long  deep_sleep_ind_1x : 1;  /* bit[0]   : ��˯ָʾ��1��Ч */
        unsigned long  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_DEEP_SLEEP_IND_1X_UNION;
#define CBBP_DEEP_SLEEP_IND_1X_deep_sleep_ind_1x_START  (0)
#define CBBP_DEEP_SLEEP_IND_1X_deep_sleep_ind_1x_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_SLEEP_CNT_32K_1X_UNION
 �ṹ˵��  : SLEEP_CNT_32K_1X �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sleep_cnt_32k_1x_reg;
    struct
    {
        unsigned long  sleep_cnt_32k_1x : 23; /* bit[0-22] : �ϱ���˯��ʱ�䣬��32kʱ�����ڸ�����ʾ�� */
        unsigned long  reserved         : 9;  /* bit[23-31]: ���� */
    } reg;
} CBBP_SLEEP_CNT_32K_1X_UNION;
#define CBBP_SLEEP_CNT_32K_1X_sleep_cnt_32k_1x_START  (0)
#define CBBP_SLEEP_CNT_32K_1X_sleep_cnt_32k_1x_END    (22)


/*****************************************************************************
 �ṹ��    : CBBP_WAKEUP_TYPE_1X_UNION
 �ṹ˵��  : WAKEUP_TYPE_1X �Ĵ����ṹ���塣��ַƫ����:0x002C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      wakeup_type_1x_reg;
    struct
    {
        unsigned long  wakeup_type_1x : 1;  /* bit[0]   : �������ࡣ
                                                          0����ʾ��Ȼ���ѣ�
                                                          1����ʾǿ�ƻ��� */
        unsigned long  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_WAKEUP_TYPE_1X_UNION;
#define CBBP_WAKEUP_TYPE_1X_wakeup_type_1x_START  (0)
#define CBBP_WAKEUP_TYPE_1X_wakeup_type_1x_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_SLEEP_STATUS_1X_UNION
 �ṹ˵��  : SLEEP_STATUS_1X �Ĵ����ṹ���塣��ַƫ����:0x0030����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sleep_status_1x_reg;
    struct
    {
        unsigned long  sleep_status_1x : 1;  /* bit[0]   : BBP����˯��״ָ̬ʾ����sleep_start��ʼ��int_32k_to_sys�ڼ�Ϊ1������ʱ��Ϊ0�� */
        unsigned long  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_SLEEP_STATUS_1X_UNION;
#define CBBP_SLEEP_STATUS_1X_sleep_status_1x_START  (0)
#define CBBP_SLEEP_STATUS_1X_sleep_status_1x_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_PERIOD_1X_UNION
 �ṹ˵��  : SYS_CNT_PERIOD_1X �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_period_1x_reg;
    struct
    {
        unsigned long  sys_cnt_period_1x : 1;  /* bit[0]   : sys cnt����ѡ��
                                                             0��ʾ2s
                                                             1��ʾ5.12s */
        unsigned long  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_SYS_CNT_PERIOD_1X_UNION;
#define CBBP_SYS_CNT_PERIOD_1X_sys_cnt_period_1x_START  (0)
#define CBBP_SYS_CNT_PERIOD_1X_sys_cnt_period_1x_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_WAKEUP_INT_BBE16_UNION
 �ṹ˵��  : WAKEUP_INT_BBE16 �Ĵ����ṹ���塣��ַƫ����:0x0050����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      wakeup_int_bbe16_reg;
    struct
    {
        unsigned long  cbbp_int01_mask_bbe16 : 2;  /* bit[0-1]  : �ϱ�bbe16�����жϵ�mask��1��ʾ������Ӧ���ж�
                                                                  bit0��1x�����жϣ�
                                                                  bit1��evdo�����ж� */
        unsigned long  reserved_0            : 6;  /* bit[2-7]  : ���� */
        unsigned long  cbbp_int01_clr_bbe16  : 2;  /* bit[8-9]  : �ϱ�bbe16�����жϵ�clr
                                                                  bit0��1x�����жϣ�
                                                                  bit1��evdo�����ж� */
        unsigned long  reserved_1            : 21; /* bit[10-30]: ���� */
        unsigned long  cbbp_int01_en_bbe16   : 1;  /* bit[31]   : �ϱ�bbe16�����жϵ�ʹ�� */
    } reg;
} CBBP_WAKEUP_INT_BBE16_UNION;
#define CBBP_WAKEUP_INT_BBE16_cbbp_int01_mask_bbe16_START  (0)
#define CBBP_WAKEUP_INT_BBE16_cbbp_int01_mask_bbe16_END    (1)
#define CBBP_WAKEUP_INT_BBE16_cbbp_int01_clr_bbe16_START   (8)
#define CBBP_WAKEUP_INT_BBE16_cbbp_int01_clr_bbe16_END     (9)
#define CBBP_WAKEUP_INT_BBE16_cbbp_int01_en_bbe16_START    (31)
#define CBBP_WAKEUP_INT_BBE16_cbbp_int01_en_bbe16_END      (31)


/*****************************************************************************
 �ṹ��    : CBBP_WAKEUP_INT_STA_BBE16_UNION
 �ṹ˵��  : WAKEUP_INT_STA_BBE16 �Ĵ����ṹ���塣��ַƫ����:0x0054����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      wakeup_int_sta_bbe16_reg;
    struct
    {
        unsigned long  cbbp_int01_sta_bbe16 : 2;  /* bit[0-1] : �ϱ�bbe16�����жϵ�sta��1��ʾ��Ӧ���ж���Ч
                                                                bit0��1x�����жϣ�
                                                                bit1��evdo�����ж� */
        unsigned long  reserved             : 30; /* bit[2-31]: ���� */
    } reg;
} CBBP_WAKEUP_INT_STA_BBE16_UNION;
#define CBBP_WAKEUP_INT_STA_BBE16_cbbp_int01_sta_bbe16_START  (0)
#define CBBP_WAKEUP_INT_STA_BBE16_cbbp_int01_sta_bbe16_END    (1)


/*****************************************************************************
 �ṹ��    : CBBP_WAKEUP_INT_ARM_UNION
 �ṹ˵��  : WAKEUP_INT_ARM �Ĵ����ṹ���塣��ַƫ����:0x0058����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      wakeup_int_arm_reg;
    struct
    {
        unsigned long  cbbp_int01_mask_arm : 2;  /* bit[0-1]  : �ϱ�arm�����жϵ�mask��1��ʾ������Ӧ���ж�
                                                                bit0��1x�����жϣ�
                                                                bit1��evdo�����ж� */
        unsigned long  reserved_0          : 6;  /* bit[2-7]  : ���� */
        unsigned long  cbbp_int01_clr_arm  : 2;  /* bit[8-9]  : �ϱ�arm�����жϵ�clr
                                                                bit0��1x�����жϣ�
                                                                bit1��evdo�����ж� */
        unsigned long  reserved_1          : 21; /* bit[10-30]: ���� */
        unsigned long  cbbp_int01_en_arm   : 1;  /* bit[31]   : �ϱ�arm�����жϵ�ʹ�� */
    } reg;
} CBBP_WAKEUP_INT_ARM_UNION;
#define CBBP_WAKEUP_INT_ARM_cbbp_int01_mask_arm_START  (0)
#define CBBP_WAKEUP_INT_ARM_cbbp_int01_mask_arm_END    (1)
#define CBBP_WAKEUP_INT_ARM_cbbp_int01_clr_arm_START   (8)
#define CBBP_WAKEUP_INT_ARM_cbbp_int01_clr_arm_END     (9)
#define CBBP_WAKEUP_INT_ARM_cbbp_int01_en_arm_START    (31)
#define CBBP_WAKEUP_INT_ARM_cbbp_int01_en_arm_END      (31)


/*****************************************************************************
 �ṹ��    : CBBP_WAKEUP_INT_STA_ARM_UNION
 �ṹ˵��  : WAKEUP_INT_STA_ARM �Ĵ����ṹ���塣��ַƫ����:0x005C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      wakeup_int_sta_arm_reg;
    struct
    {
        unsigned long  cbbp_int01_sta_arm : 2;  /* bit[0-1] : �ϱ�arm�����жϵ�sta��1��ʾ��Ӧ���ж�
                                                              bit0��1x�����жϣ�
                                                              bit1��evdo�����ж� */
        unsigned long  reserved           : 30; /* bit[2-31]: ���� */
    } reg;
} CBBP_WAKEUP_INT_STA_ARM_UNION;
#define CBBP_WAKEUP_INT_STA_ARM_cbbp_int01_sta_arm_START  (0)
#define CBBP_WAKEUP_INT_STA_ARM_cbbp_int01_sta_arm_END    (1)


/*****************************************************************************
 �ṹ��    : CBBP_DSP_READY_IND_CDRX_1X_UNION
 �ṹ˵��  : DSP_READY_IND_CDRX_1X �Ĵ����ṹ���塣��ַƫ����:0x0060����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_ready_ind_cdrx_1x_reg;
    struct
    {
        unsigned long  dsp_ready_ind_cdrx_1x : 1;  /* bit[0]   : ��Ȼ���������У�����Ѿ�׼���ý���ʱ���л��ж� */
        unsigned long  reserved              : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_DSP_READY_IND_CDRX_1X_UNION;
#define CBBP_DSP_READY_IND_CDRX_1X_dsp_ready_ind_cdrx_1x_START  (0)
#define CBBP_DSP_READY_IND_CDRX_1X_dsp_ready_ind_cdrx_1x_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_CK_MSR_INTERGER_EVDO_UNION
 �ṹ˵��  : CK_MSR_INTERGER_EVDO �Ĵ����ṹ���塣��ַƫ����:0x0080����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ck_msr_interger_evdo_reg;
    struct
    {
        unsigned long  ck_msr_integer_26ms_evdo    : 11; /* bit[0-10] : ʱ�Ӳ�������������ֳ���25�Ľ����ʱ�Ӳ�������������ֱ�ʾ1��32kʱ���ڣ��ж��ٸ�122.88MHzʱ�ӡ� */
        unsigned long  reserved_0                  : 5;  /* bit[11-15]: ���� */
        unsigned long  ck_msr_integer_1_4chip_evdo : 5;  /* bit[16-20]: ʱ�Ӳ�������������ֶ�25ȡģ�Ľ����ʱ�Ӳ�������������ֱ�ʾ1��32kʱ���ڣ��ж��ٸ�122.88MHzʱ�ӡ� */
        unsigned long  reserved_1                  : 11; /* bit[21-31]: ���� */
    } reg;
} CBBP_CK_MSR_INTERGER_EVDO_UNION;
#define CBBP_CK_MSR_INTERGER_EVDO_ck_msr_integer_26ms_evdo_START     (0)
#define CBBP_CK_MSR_INTERGER_EVDO_ck_msr_integer_26ms_evdo_END       (10)
#define CBBP_CK_MSR_INTERGER_EVDO_ck_msr_integer_1_4chip_evdo_START  (16)
#define CBBP_CK_MSR_INTERGER_EVDO_ck_msr_integer_1_4chip_evdo_END    (20)


/*****************************************************************************
 �ṹ��    : CBBP_CK_MSR_FRAC_EVDO_UNION
 �ṹ˵��  : CK_MSR_FRAC_EVDO �Ĵ����ṹ���塣��ַƫ����:0x0084����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ck_msr_frac_evdo_reg;
    struct
    {
        unsigned long  ck_msr_frac_evdo : 11; /* bit[0-10] : ʱ�Ӳ������С�����֡�����Ϊ1/2048�� */
        unsigned long  reserved         : 21; /* bit[11-31]: ���� */
    } reg;
} CBBP_CK_MSR_FRAC_EVDO_UNION;
#define CBBP_CK_MSR_FRAC_EVDO_ck_msr_frac_evdo_START  (0)
#define CBBP_CK_MSR_FRAC_EVDO_ck_msr_frac_evdo_END    (10)


/*****************************************************************************
 �ṹ��    : CBBP_SLEEP_PERIOD_EVDO_UNION
 �ṹ˵��  : SLEEP_PERIOD_EVDO �Ĵ����ṹ���塣��ַƫ����:0x0088����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sleep_period_evdo_reg;
    struct
    {
        unsigned long  sleep_period_evdo : 23; /* bit[0-22] : ˯��ʱ�䣺�ӿ�ʼ˯�ߵ�����ʱ�̵�ʱ�䡣����32kʱ�Ӹ��� */
        unsigned long  reserved          : 9;  /* bit[23-31]: ���� */
    } reg;
} CBBP_SLEEP_PERIOD_EVDO_UNION;
#define CBBP_SLEEP_PERIOD_EVDO_sleep_period_evdo_START  (0)
#define CBBP_SLEEP_PERIOD_EVDO_sleep_period_evdo_END    (22)


/*****************************************************************************
 �ṹ��    : CBBP_CK_SWITCH_CNT_EVDO_UNION
 �ṹ˵��  : CK_SWITCH_CNT_EVDO �Ĵ����ṹ���塣��ַƫ����:0x008C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ck_switch_cnt_evdo_reg;
    struct
    {
        unsigned long  ck_switch_cnt_evdo : 12; /* bit[0-11] : ��������ʱ����wakeup�жϣ����л�ϵͳ��ʱ֮���ʱ�䡣����Ϊ32kʱ�Ӹ��������ֵ��Ӧʱ��62.5ms�� */
        unsigned long  reserved           : 20; /* bit[12-31]: ���� */
    } reg;
} CBBP_CK_SWITCH_CNT_EVDO_UNION;
#define CBBP_CK_SWITCH_CNT_EVDO_ck_switch_cnt_evdo_START  (0)
#define CBBP_CK_SWITCH_CNT_EVDO_ck_switch_cnt_evdo_END    (11)


/*****************************************************************************
 �ṹ��    : CBBP_DEEP_SLEEP_CNT_EVDO_UNION
 �ṹ˵��  : DEEP_SLEEP_CNT_EVDO �Ĵ����ṹ���塣��ַƫ����:0x0090����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      deep_sleep_cnt_evdo_reg;
    struct
    {
        unsigned long  deep_sleep_cnt_evdo : 12; /* bit[0-11] : ����wakeupʱ�̻��ж೤ʱ�䣬BBP������˯ָʾ������Ϊ32kʱ�Ӹ����� */
        unsigned long  reserved            : 20; /* bit[12-31]: ���� */
    } reg;
} CBBP_DEEP_SLEEP_CNT_EVDO_UNION;
#define CBBP_DEEP_SLEEP_CNT_EVDO_deep_sleep_cnt_evdo_START  (0)
#define CBBP_DEEP_SLEEP_CNT_EVDO_deep_sleep_cnt_evdo_END    (11)


/*****************************************************************************
 �ṹ��    : CBBP_SLEEP_MODE_EVDO_UNION
 �ṹ˵��  : SLEEP_MODE_EVDO �Ĵ����ṹ���塣��ַƫ����:0x0094����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sleep_mode_evdo_reg;
    struct
    {
        unsigned long  sleep_mode_evdo : 1;  /* bit[0]   : ����˯�ߵ�ģʽ��
                                                           0����ʾ����˯��
                                                           1����ʾ����ָ��ʱ���ٽ���˯�� */
        unsigned long  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_SLEEP_MODE_EVDO_UNION;
#define CBBP_SLEEP_MODE_EVDO_sleep_mode_evdo_START  (0)
#define CBBP_SLEEP_MODE_EVDO_sleep_mode_evdo_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_SLEEP_TIME_EVDO_UNION
 �ṹ˵��  : SLEEP_TIME_EVDO �Ĵ����ṹ���塣��ַƫ����:0x0098����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sleep_time_evdo_reg;
    struct
    {
        unsigned long  sleep_time_evdo_26ms  : 15; /* bit[0-14] : ���ָ���Ľ���˯�ߵ�ʱ�̣�Sleep_mode=1ʱ��Ч��
                                                                  [29:24]��sys_cnt_evdo_5p12s��ֵ��
                                                                  [17:16]��sys_cnt_evdo_80ms��ֵ��
                                                                  [14:0]��sys_cnt_evdo_26ms��ֵ�� */
        unsigned long  reserved_0            : 1;  /* bit[15]   : ���� */
        unsigned long  sleep_time_evdo_80ms  : 2;  /* bit[16-17]:  */
        unsigned long  reserved_1            : 6;  /* bit[18-23]: ���� */
        unsigned long  sleep_time_evdo_5p12s : 6;  /* bit[24-29]:  */
        unsigned long  reserved_2            : 2;  /* bit[30-31]: ���� */
    } reg;
} CBBP_SLEEP_TIME_EVDO_UNION;
#define CBBP_SLEEP_TIME_EVDO_sleep_time_evdo_26ms_START   (0)
#define CBBP_SLEEP_TIME_EVDO_sleep_time_evdo_26ms_END     (14)
#define CBBP_SLEEP_TIME_EVDO_sleep_time_evdo_80ms_START   (16)
#define CBBP_SLEEP_TIME_EVDO_sleep_time_evdo_80ms_END     (17)
#define CBBP_SLEEP_TIME_EVDO_sleep_time_evdo_5p12s_START  (24)
#define CBBP_SLEEP_TIME_EVDO_sleep_time_evdo_5p12s_END    (29)


/*****************************************************************************
 �ṹ��    : CBBP_SLEEP_START_EVDO_UNION
 �ṹ˵��  : SLEEP_START_EVDO �Ĵ����ṹ���塣��ַƫ����:0x009C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sleep_start_evdo_reg;
    struct
    {
        unsigned long  sleep_start_evdo : 1;  /* bit[0]   : ������õ�˯��ָ������źš� Sleep_mode=0ʱ����������˯�ߣ�Sleep_mode=1ʱ���ȴ����õ�ʱ�̽���˯�� */
        unsigned long  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_SLEEP_START_EVDO_UNION;
#define CBBP_SLEEP_START_EVDO_sleep_start_evdo_START  (0)
#define CBBP_SLEEP_START_EVDO_sleep_start_evdo_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_SWITCH_UP_EVDO_UNION
 �ṹ˵��  : SWITCH_UP_EVDO �Ĵ����ṹ���塣��ַƫ����:0x00A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      switch_up_evdo_reg;
    struct
    {
        unsigned long  switch_up_evdo : 1;  /* bit[0]   : ǿ�ƻ���ָ������źš� */
        unsigned long  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_SWITCH_UP_EVDO_UNION;
#define CBBP_SWITCH_UP_EVDO_switch_up_evdo_START  (0)
#define CBBP_SWITCH_UP_EVDO_switch_up_evdo_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_DEEP_SLEEP_IND_EVDO_UNION
 �ṹ˵��  : DEEP_SLEEP_IND_EVDO �Ĵ����ṹ���塣��ַƫ����:0x00A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      deep_sleep_ind_evdo_reg;
    struct
    {
        unsigned long  deep_sleep_ind_evdo : 1;  /* bit[0]   : ��˯ָʾ��1��Ч */
        unsigned long  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_DEEP_SLEEP_IND_EVDO_UNION;
#define CBBP_DEEP_SLEEP_IND_EVDO_deep_sleep_ind_evdo_START  (0)
#define CBBP_DEEP_SLEEP_IND_EVDO_deep_sleep_ind_evdo_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_SLEEP_CNT_32K_EVDO_UNION
 �ṹ˵��  : SLEEP_CNT_32K_EVDO �Ĵ����ṹ���塣��ַƫ����:0x00A8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sleep_cnt_32k_evdo_reg;
    struct
    {
        unsigned long  sleep_cnt_32k_evdo : 23; /* bit[0-22] : �ϱ���˯��ʱ�䣬��32kʱ�����ڸ�����ʾ�� */
        unsigned long  reserved           : 9;  /* bit[23-31]: ���� */
    } reg;
} CBBP_SLEEP_CNT_32K_EVDO_UNION;
#define CBBP_SLEEP_CNT_32K_EVDO_sleep_cnt_32k_evdo_START  (0)
#define CBBP_SLEEP_CNT_32K_EVDO_sleep_cnt_32k_evdo_END    (22)


/*****************************************************************************
 �ṹ��    : CBBP_WAKEUP_TYPE_EVDO_UNION
 �ṹ˵��  : WAKEUP_TYPE_EVDO �Ĵ����ṹ���塣��ַƫ����:0x00AC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      wakeup_type_evdo_reg;
    struct
    {
        unsigned long  wakeup_type_evdo : 1;  /* bit[0]   : �������ࡣ
                                                            0����ʾ��Ȼ���ѣ�
                                                            1����ʾǿ�ƻ��� */
        unsigned long  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_WAKEUP_TYPE_EVDO_UNION;
#define CBBP_WAKEUP_TYPE_EVDO_wakeup_type_evdo_START  (0)
#define CBBP_WAKEUP_TYPE_EVDO_wakeup_type_evdo_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_SLEEP_STATUS_EVDO_UNION
 �ṹ˵��  : SLEEP_STATUS_EVDO �Ĵ����ṹ���塣��ַƫ����:0x00B0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sleep_status_evdo_reg;
    struct
    {
        unsigned long  sleep_status_evdo : 1;  /* bit[0]   : BBP����˯��״ָ̬ʾ����sleep_start��ʼ��int_32k_to_sys�ڼ�Ϊ1������ʱ��Ϊ0�� */
        unsigned long  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_SLEEP_STATUS_EVDO_UNION;
#define CBBP_SLEEP_STATUS_EVDO_sleep_status_evdo_START  (0)
#define CBBP_SLEEP_STATUS_EVDO_sleep_status_evdo_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_PERIOD_EVDO_UNION
 �ṹ˵��  : SYS_CNT_PERIOD_EVDO �Ĵ����ṹ���塣��ַƫ����:0x00B4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_period_evdo_reg;
    struct
    {
        unsigned long  sys_cnt_period_evdo : 1;  /* bit[0]   : sys cnt����ѡ��
                                                               0��ʾ2s
                                                               1��ʾ5.12s */
        unsigned long  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_SYS_CNT_PERIOD_EVDO_UNION;
#define CBBP_SYS_CNT_PERIOD_EVDO_sys_cnt_period_evdo_START  (0)
#define CBBP_SYS_CNT_PERIOD_EVDO_sys_cnt_period_evdo_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_SWITCH_INT_BBE16_UNION
 �ṹ˵��  : SWITCH_INT_BBE16 �Ĵ����ṹ���塣��ַƫ����:0x00D0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      switch_int_bbe16_reg;
    struct
    {
        unsigned long  cbbp_int02_mask_bbe16 : 4;  /* bit[0-3]  : �ϱ�bbe16ʱ���л��жϵ�mask��1��ʾ������Ӧ���ж�
                                                                  bit0��1x����ʱϵͳ��ʱ��32k�л���122M��
                                                                  bit1��1x˯��ʱϵͳ��ʱ��122M�л���32k
                                                                  bit2��evdo����ʱϵͳ��ʱ��32k�л���122M��
                                                                  bit3��evdo˯��ʱϵͳ��ʱ��122M�л���32k */
        unsigned long  reserved_0            : 4;  /* bit[4-7]  : ���� */
        unsigned long  cbbp_int02_clr_bbe16  : 4;  /* bit[8-11] : �ϱ�bbe16ʱ���л��жϵ�clr
                                                                  bit0��1x����ʱϵͳ��ʱ��32k�л���122M��
                                                                  bit1��1x˯��ʱϵͳ��ʱ��122M�л���32k
                                                                  bit2��evdo����ʱϵͳ��ʱ��32k�л���122M��
                                                                  bit3��evdo˯��ʱϵͳ��ʱ��122M�л���32k */
        unsigned long  reserved_1            : 19; /* bit[12-30]: ���� */
        unsigned long  cbbp_int02_en_bbe16   : 1;  /* bit[31]   : �ϱ�bbe16ʱ���л��жϵ�ʹ�� */
    } reg;
} CBBP_SWITCH_INT_BBE16_UNION;
#define CBBP_SWITCH_INT_BBE16_cbbp_int02_mask_bbe16_START  (0)
#define CBBP_SWITCH_INT_BBE16_cbbp_int02_mask_bbe16_END    (3)
#define CBBP_SWITCH_INT_BBE16_cbbp_int02_clr_bbe16_START   (8)
#define CBBP_SWITCH_INT_BBE16_cbbp_int02_clr_bbe16_END     (11)
#define CBBP_SWITCH_INT_BBE16_cbbp_int02_en_bbe16_START    (31)
#define CBBP_SWITCH_INT_BBE16_cbbp_int02_en_bbe16_END      (31)


/*****************************************************************************
 �ṹ��    : CBBP_SWITCH_INT_STA_BBE16_UNION
 �ṹ˵��  : SWITCH_INT_STA_BBE16 �Ĵ����ṹ���塣��ַƫ����:0x00D4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      switch_int_sta_bbe16_reg;
    struct
    {
        unsigned long  cbbp_int02_sta_bbe16 : 4;  /* bit[0-3] : �ϱ�bbe16ʱ���л��жϵ�sta��1��ʾ��Ӧ���ж�
                                                                bit0��1x����ʱϵͳ��ʱ��32k�л���122M��
                                                                bit1��1x˯��ʱϵͳ��ʱ��122M�л���32k
                                                                bit2��evdo����ʱϵͳ��ʱ��32k�л���122M��
                                                                bit3��evdo˯��ʱϵͳ��ʱ��122M�л���32k */
        unsigned long  reserved             : 28; /* bit[4-31]: ���� */
    } reg;
} CBBP_SWITCH_INT_STA_BBE16_UNION;
#define CBBP_SWITCH_INT_STA_BBE16_cbbp_int02_sta_bbe16_START  (0)
#define CBBP_SWITCH_INT_STA_BBE16_cbbp_int02_sta_bbe16_END    (3)


/*****************************************************************************
 �ṹ��    : CBBP_SWITCH_INT_ARM_UNION
 �ṹ˵��  : SWITCH_INT_ARM �Ĵ����ṹ���塣��ַƫ����:0x00D8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      switch_int_arm_reg;
    struct
    {
        unsigned long  cbbp_int02_mask_arm : 4;  /* bit[0-3]  : �ϱ�armʱ���л��жϵ�mask��1��ʾ������Ӧ���ж�
                                                                bit0��1x����ʱϵͳ��ʱ��32k�л���122M��
                                                                bit1��1x˯��ʱϵͳ��ʱ��122M�л���32k
                                                                bit2��evdo����ʱϵͳ��ʱ��32k�л���122M��
                                                                bit3��evdo˯��ʱϵͳ��ʱ��122M�л���32k */
        unsigned long  reserved_0          : 4;  /* bit[4-7]  : ���� */
        unsigned long  cbbp_int02_clr_arm  : 4;  /* bit[8-11] : �ϱ�armʱ���л��жϵ�clr
                                                                bit0��1x����ʱϵͳ��ʱ��32k�л���122M��
                                                                bit1��1x˯��ʱϵͳ��ʱ��122M�л���32k
                                                                bit2��evdo����ʱϵͳ��ʱ��32k�л���122M��
                                                                bit3��evdo˯��ʱϵͳ��ʱ��122M�л���32k */
        unsigned long  reserved_1          : 19; /* bit[12-30]: ���� */
        unsigned long  cbbp_int02_en_arm   : 1;  /* bit[31]   : �ϱ�armʱ���л��жϵ�ʹ�� */
    } reg;
} CBBP_SWITCH_INT_ARM_UNION;
#define CBBP_SWITCH_INT_ARM_cbbp_int02_mask_arm_START  (0)
#define CBBP_SWITCH_INT_ARM_cbbp_int02_mask_arm_END    (3)
#define CBBP_SWITCH_INT_ARM_cbbp_int02_clr_arm_START   (8)
#define CBBP_SWITCH_INT_ARM_cbbp_int02_clr_arm_END     (11)
#define CBBP_SWITCH_INT_ARM_cbbp_int02_en_arm_START    (31)
#define CBBP_SWITCH_INT_ARM_cbbp_int02_en_arm_END      (31)


/*****************************************************************************
 �ṹ��    : CBBP_SWITCH_INT_STA_ARM_UNION
 �ṹ˵��  : SWITCH_INT_STA_ARM �Ĵ����ṹ���塣��ַƫ����:0x00DC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      switch_int_sta_arm_reg;
    struct
    {
        unsigned long  cbbp_int02_sta_arm : 4;  /* bit[0-3] : �ϱ�armʱ���л��жϵ�STA��1��ʾ��Ӧ���ж�
                                                              bit0��1x����ʱϵͳ��ʱ��32k�л���122M��
                                                              bit1��1x˯��ʱϵͳ��ʱ��122M�л���32k
                                                              bit2��evdo����ʱϵͳ��ʱ��32k�л���122M��
                                                              bit3��evdo˯��ʱϵͳ��ʱ��122M�л���32k */
        unsigned long  reserved           : 28; /* bit[4-31]: ���� */
    } reg;
} CBBP_SWITCH_INT_STA_ARM_UNION;
#define CBBP_SWITCH_INT_STA_ARM_cbbp_int02_sta_arm_START  (0)
#define CBBP_SWITCH_INT_STA_ARM_cbbp_int02_sta_arm_END    (3)


/*****************************************************************************
 �ṹ��    : CBBP_DSP_READY_IND_CDRX_EVDO_UNION
 �ṹ˵��  : DSP_READY_IND_CDRX_EVDO �Ĵ����ṹ���塣��ַƫ����:0x00E0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_ready_ind_cdrx_evdo_reg;
    struct
    {
        unsigned long  dsp_ready_ind_cdrx_evdo : 1;  /* bit[0]   : ��Ȼ���������У�����Ѿ�׼���ý���ʱ���л��ж� */
        unsigned long  reserved                : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_DSP_READY_IND_CDRX_EVDO_UNION;
#define CBBP_DSP_READY_IND_CDRX_EVDO_dsp_ready_ind_cdrx_evdo_START  (0)
#define CBBP_DSP_READY_IND_CDRX_EVDO_dsp_ready_ind_cdrx_evdo_END    (0)




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

#endif /* end of bbp_cdma_on_interface.h */
