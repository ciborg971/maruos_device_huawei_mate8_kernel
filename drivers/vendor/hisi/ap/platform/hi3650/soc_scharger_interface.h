

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_SCHARGER_INTERFACE_H__
#define __SOC_SCHARGER_INTERFACE_H__

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
/* �Ĵ���˵����оƬ�汾�Ĵ���0��
   λ����UNION�ṹ:  SOC_SCHARGER_CHIP_VERSION_0_UNION */
#define SOC_SCHARGER_CHIP_VERSION_0_ADDR(base)        ((base) + (0x00))

/* �Ĵ���˵����оƬ�汾�Ĵ���1��
   λ����UNION�ṹ:  SOC_SCHARGER_CHIP_VERSION_1_UNION */
#define SOC_SCHARGER_CHIP_VERSION_1_ADDR(base)        ((base) + (0x01))

/* �Ĵ���˵����оƬ�汾�Ĵ���2��
   λ����UNION�ṹ:  SOC_SCHARGER_CHIP_VERSION_2_UNION */
#define SOC_SCHARGER_CHIP_VERSION_2_ADDR(base)        ((base) + (0x02))

/* �Ĵ���˵����оƬ�汾�Ĵ���3��
   λ����UNION�ṹ:  SOC_SCHARGER_CHIP_VERSION_3_UNION */
#define SOC_SCHARGER_CHIP_VERSION_3_ADDR(base)        ((base) + (0x03))

/* �Ĵ���˵����оƬ�汾�Ĵ���4��
   λ����UNION�ṹ:  SOC_SCHARGER_CHIP_VERSION_4_UNION */
#define SOC_SCHARGER_CHIP_VERSION_4_ADDR(base)        ((base) + (0x04))

/* �Ĵ���˵����оƬ�汾�Ĵ���5��
   λ����UNION�ṹ:  SOC_SCHARGER_CHIP_VERSION_5_UNION */
#define SOC_SCHARGER_CHIP_VERSION_5_ADDR(base)        ((base) + (0x05))

/* �Ĵ���˵����״̬��־0�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_STATUS0_UNION */
#define SOC_SCHARGER_STATUS0_ADDR(base)               ((base) + (0x06))

/* �Ĵ���˵����״̬��־1�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_STATUS1_UNION */
#define SOC_SCHARGER_STATUS1_ADDR(base)               ((base) + (0x07))

/* �Ĵ���˵����״̬��־2�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_STATUS2_UNION */
#define SOC_SCHARGER_STATUS2_ADDR(base)               ((base) + (0x08))

/* �Ĵ���˵�����ж�״̬��־0�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_IRQ_STATUS0_UNION */
#define SOC_SCHARGER_IRQ_STATUS0_ADDR(base)           ((base) + (0x09))

/* �Ĵ���˵�����ж�״̬��־1�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_IRQ_STATUS1_UNION */
#define SOC_SCHARGER_IRQ_STATUS1_ADDR(base)           ((base) + (0x0A))

/* �Ĵ���˵�����ж�״̬��־1�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_IRQ_STATUS2_UNION */
#define SOC_SCHARGER_IRQ_STATUS2_ADDR(base)           ((base) + (0x0B))

/* �Ĵ���˵�����ж�0�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_IRQ0_UNION */
#define SOC_SCHARGER_IRQ0_ADDR(base)                  ((base) + (0x0C))

/* �Ĵ���˵�����ж�1�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_IRQ1_UNION */
#define SOC_SCHARGER_IRQ1_ADDR(base)                  ((base) + (0x0D))

/* �Ĵ���˵�����ж�2�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_IRQ2_UNION */
#define SOC_SCHARGER_IRQ2_ADDR(base)                  ((base) + (0x0E))

/* �Ĵ���˵�������Ź��жϼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_WATCHDOG_IRQ_UNION */
#define SOC_SCHARGER_WATCHDOG_IRQ_ADDR(base)          ((base) + (0x0F))

/* �Ĵ���˵�����ж�����0�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_IRQ0_MASK_UNION */
#define SOC_SCHARGER_IRQ0_MASK_ADDR(base)             ((base) + (0x10))

/* �Ĵ���˵�����ж�����1�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_IRQ1_MASK_UNION */
#define SOC_SCHARGER_IRQ1_MASK_ADDR(base)             ((base) + (0x11))

/* �Ĵ���˵�����ж�����2�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_IRQ2_MASK_UNION */
#define SOC_SCHARGER_IRQ2_MASK_ADDR(base)             ((base) + (0x12))

/* �Ĵ���˵�������Ź��ж����μĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_WATCHDOG_IRQ_MASK_UNION */
#define SOC_SCHARGER_WATCHDOG_IRQ_MASK_ADDR(base)     ((base) + (0x13))

/* �Ĵ���˵����fcp slave ����״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_STATUIS_UNION */
#define SOC_SCHARGER_STATUIS_ADDR(base)               ((base) + (0x20))

/* �Ĵ���˵����XXXX��
   λ����UNION�ṹ:  SOC_SCHARGER_CNTL_UNION */
#define SOC_SCHARGER_CNTL_ADDR(base)                  ((base) + (0x21))

/* �Ĵ���˵����fcp ��д�������üĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_CMD_UNION */
#define SOC_SCHARGER_CMD_ADDR(base)                   ((base) + (0x24))

/* �Ĵ���˵����fcp ��д��ַ���üĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_ADDR_UNION */
#define SOC_SCHARGER_ADDR_ADDR(base)                  ((base) + (0x27))

/* �Ĵ���˵����fcp д���ݼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_DATA0_UNION */
#define SOC_SCHARGER_DATA0_ADDR(base)                 ((base) + (0x28))

/* �Ĵ���˵����FCP �ж�1�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_ISR1_UNION */
#define SOC_SCHARGER_ISR1_ADDR(base)                  ((base) + (0x39))

/* �Ĵ���˵����FCP �ж�2�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_ISR2_UNION */
#define SOC_SCHARGER_ISR2_ADDR(base)                  ((base) + (0x3A))

/* �Ĵ���˵����FCP �ж�����1�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_IMR1_UNION */
#define SOC_SCHARGER_IMR1_ADDR(base)                  ((base) + (0x3B))

/* �Ĵ���˵����FCP �ж�����2�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_IMR2_UNION */
#define SOC_SCHARGER_IMR2_ADDR(base)                  ((base) + (0x3C))

/* �Ĵ���˵����FCP�ж�3�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_FCP_IRQ3_UNION */
#define SOC_SCHARGER_FCP_IRQ3_ADDR(base)              ((base) + (0x3D))

/* �Ĵ���˵����FCP�ж�4�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_FCP_IRQ4_UNION */
#define SOC_SCHARGER_FCP_IRQ4_ADDR(base)              ((base) + (0x3E))

/* �Ĵ���˵����FCP�ж�5�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_FCP_IRQ5_UNION */
#define SOC_SCHARGER_FCP_IRQ5_ADDR(base)              ((base) + (0x3F))

/* �Ĵ���˵����FCP�ж�����3�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_FCP_IRQ3_MASK_UNION */
#define SOC_SCHARGER_FCP_IRQ3_MASK_ADDR(base)         ((base) + (0x40))

/* �Ĵ���˵����FCP�ж�����4�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_FCP_IRQ4_MASK_UNION */
#define SOC_SCHARGER_FCP_IRQ4_MASK_ADDR(base)         ((base) + (0x41))

/* �Ĵ���˵����FCP�ж�����5�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_FCP_IRQ5_MASK_UNION */
#define SOC_SCHARGER_FCP_IRQ5_MASK_ADDR(base)         ((base) + (0x42))

/* �Ĵ���˵������ѹ�����ƼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_FCP_CTRL_UNION */
#define SOC_SCHARGER_FCP_CTRL_ADDR(base)              ((base) + (0x43))

/* �Ĵ���˵������ѹ���Э��ģʽ2��λ���ƼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_FCP_MODE2_SET_UNION */
#define SOC_SCHARGER_FCP_MODE2_SET_ADDR(base)         ((base) + (0x44))

/* �Ĵ���˵������ѹ���Adapter���ƼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_FCP_ADAP_CTRL_UNION */
#define SOC_SCHARGER_FCP_ADAP_CTRL_ADDR(base)         ((base) + (0x45))

/* �Ĵ���˵����״̬��״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_MSTATE_UNION */
#define SOC_SCHARGER_MSTATE_ADDR(base)                ((base) + (0x46))

/* �Ĵ���˵����slave���ص����ݡ�
   λ����UNION�ṹ:  SOC_SCHARGER_FCP_RDATA_UNION */
#define SOC_SCHARGER_FCP_RDATA_ADDR(base)             ((base) + (0x47))

/* �Ĵ���˵����slave�������ݲɼ���ָʾ�źš�
   λ����UNION�ṹ:  SOC_SCHARGER_RDATA_READY_UNION */
#define SOC_SCHARGER_RDATA_READY_ADDR(base)           ((base) + (0x48))

/* �Ĵ���˵����crc ʹ�ܿ��ƼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_CRC_ENABLE_UNION */
#define SOC_SCHARGER_CRC_ENABLE_ADDR(base)            ((base) + (0x49))

/* �Ĵ���˵����crc ��ʼֵ��
   λ����UNION�ṹ:  SOC_SCHARGER_CRC_START_VALUE_UNION */
#define SOC_SCHARGER_CRC_START_VALUE_ADDR(base)       ((base) + (0x4A))

/* �Ĵ���˵��������������Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_SAMPLE_CNT_ADJ_UNION */
#define SOC_SCHARGER_SAMPLE_CNT_ADJ_ADDR(base)        ((base) + (0x4B))

/* �Ĵ���˵����RX ping ��С���ȸ�λ��
   λ����UNION�ṹ:  SOC_SCHARGER_RX_PING_WIDTH_MIN_H_UNION */
#define SOC_SCHARGER_RX_PING_WIDTH_MIN_H_ADDR(base)   ((base) + (0x4C))

/* �Ĵ���˵����RX ping ��С���ȵ�8λ
   λ����UNION�ṹ:  SOC_SCHARGER_RX_PING_WIDTH_MIN_L_UNION */
#define SOC_SCHARGER_RX_PING_WIDTH_MIN_L_ADDR(base)   ((base) + (0x4D))

/* �Ĵ���˵����RX ping ��󳤶ȸ�λ
   λ����UNION�ṹ:  SOC_SCHARGER_RX_PING_WIDTH_MAX_H_UNION */
#define SOC_SCHARGER_RX_PING_WIDTH_MAX_H_ADDR(base)   ((base) + (0x4E))

/* �Ĵ���˵����RX ping ��󳤶ȵ�8λ��
   λ����UNION�ṹ:  SOC_SCHARGER_RX_PING_WIDTH_MAX_L_UNION */
#define SOC_SCHARGER_RX_PING_WIDTH_MAX_L_ADDR(base)   ((base) + (0x4F))

/* �Ĵ���˵�������ݵȴ�ʱ��Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_DATA_WAIT_TIME_UNION */
#define SOC_SCHARGER_DATA_WAIT_TIME_ADDR(base)        ((base) + (0x50))

/* �Ĵ���˵�����������·��ʹ�����
   λ����UNION�ṹ:  SOC_SCHARGER_RETRY_CNT_UNION */
#define SOC_SCHARGER_RETRY_CNT_ADDR(base)             ((base) + (0x51))

/* �Ĵ���˵����FCP��λ���ƼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_FCP_SOFT_RST_CTRL_UNION */
#define SOC_SCHARGER_FCP_SOFT_RST_CTRL_ADDR(base)     ((base) + (0x52))

/* �Ĵ���˵����fcpֻ��Ԥ���Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_FCP_RO_RESERVE_UNION */
#define SOC_SCHARGER_FCP_RO_RESERVE_ADDR(base)        ((base) + (0x53))

/* �Ĵ���˵����FCP debug�Ĵ���0��
   λ����UNION�ṹ:  SOC_SCHARGER_FCP_DEBUG_REG0_UNION */
#define SOC_SCHARGER_FCP_DEBUG_REG0_ADDR(base)        ((base) + (0x54))

/* �Ĵ���˵����FCP debug�Ĵ���1��
   λ����UNION�ṹ:  SOC_SCHARGER_FCP_DEBUG_REG1_UNION */
#define SOC_SCHARGER_FCP_DEBUG_REG1_ADDR(base)        ((base) + (0x55))

/* �Ĵ���˵����FCP debug�Ĵ���2��
   λ����UNION�ṹ:  SOC_SCHARGER_FCP_DEBUG_REG2_UNION */
#define SOC_SCHARGER_FCP_DEBUG_REG2_ADDR(base)        ((base) + (0x56))

/* �Ĵ���˵����BUCK_REG0���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_BUCK_REG0_UNION */
#define SOC_SCHARGER_BUCK_REG0_ADDR(base)             ((base) + (0x60))

/* �Ĵ���˵����BUCK_REG1���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_BUCK_REG1_UNION */
#define SOC_SCHARGER_BUCK_REG1_ADDR(base)             ((base) + (0x61))

/* �Ĵ���˵����BUCK_REG2���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_BUCK_REG2_UNION */
#define SOC_SCHARGER_BUCK_REG2_ADDR(base)             ((base) + (0x62))

/* �Ĵ���˵����BUCK_REG3���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_BUCK_REG3_UNION */
#define SOC_SCHARGER_BUCK_REG3_ADDR(base)             ((base) + (0x63))

/* �Ĵ���˵����BUCK_REG4���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_BUCK_REG4_UNION */
#define SOC_SCHARGER_BUCK_REG4_ADDR(base)             ((base) + (0x64))

/* �Ĵ���˵����BUCK_REG5���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_BUCK_REG5_UNION */
#define SOC_SCHARGER_BUCK_REG5_ADDR(base)             ((base) + (0x65))

/* �Ĵ���˵����BUCK_REG6���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_BUCK_REG6_UNION */
#define SOC_SCHARGER_BUCK_REG6_ADDR(base)             ((base) + (0x66))

/* �Ĵ���˵����BUCK_REG7���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_BUCK_REG7_UNION */
#define SOC_SCHARGER_BUCK_REG7_ADDR(base)             ((base) + (0x67))

/* �Ĵ���˵����BUCK_REG8���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_BUCK_REG8_UNION */
#define SOC_SCHARGER_BUCK_REG8_ADDR(base)             ((base) + (0x68))

/* �Ĵ���˵����BUCK_REG9���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_BUCK_REG9_UNION */
#define SOC_SCHARGER_BUCK_REG9_ADDR(base)             ((base) + (0x69))

/* �Ĵ���˵����BUCK_REG10���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_BUCK_REG10_UNION */
#define SOC_SCHARGER_BUCK_REG10_ADDR(base)            ((base) + (0x6A))

/* �Ĵ���˵����BUCK_REG11���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_BUCK_REG11_UNION */
#define SOC_SCHARGER_BUCK_REG11_ADDR(base)            ((base) + (0x6B))

/* �Ĵ���˵����BUCK_REG12���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_BUCK_REG12_UNION */
#define SOC_SCHARGER_BUCK_REG12_ADDR(base)            ((base) + (0x6C))

/* �Ĵ���˵����BUCK_REG13���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_BUCK_REG13_UNION */
#define SOC_SCHARGER_BUCK_REG13_ADDR(base)            ((base) + (0x6D))

/* �Ĵ���˵����BUCK_REG14���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_BUCK_REG14_UNION */
#define SOC_SCHARGER_BUCK_REG14_ADDR(base)            ((base) + (0x6E))

/* �Ĵ���˵����BUCK_REG15���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_BUCK_REG15_UNION */
#define SOC_SCHARGER_BUCK_REG15_ADDR(base)            ((base) + (0x6F))

/* �Ĵ���˵����BUCK����������ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_BUCK_REG16_UNION */
#define SOC_SCHARGER_BUCK_REG16_ADDR(base)            ((base) + (0x70))

/* �Ĵ���˵����BUCK�������0�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_BUCK_RES_SEL0_UNION */
#define SOC_SCHARGER_BUCK_RES_SEL0_ADDR(base)         ((base) + (0x71))

/* �Ĵ���˵����BUCK�������1�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_BUCK_RES_SEL1_UNION */
#define SOC_SCHARGER_BUCK_RES_SEL1_ADDR(base)         ((base) + (0x72))

/* �Ĵ���˵����BUCK�������2�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_BUCK_RES_SEL2_UNION */
#define SOC_SCHARGER_BUCK_RES_SEL2_ADDR(base)         ((base) + (0x73))

/* �Ĵ���˵����BUCK�������3�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_BUCK_RES_SEL3_UNION */
#define SOC_SCHARGER_BUCK_RES_SEL3_ADDR(base)         ((base) + (0x74))

/* �Ĵ���˵����BUCK���ݵ���0�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_BUCK_CAP_SEL0_UNION */
#define SOC_SCHARGER_BUCK_CAP_SEL0_ADDR(base)         ((base) + (0x75))

/* �Ĵ���˵����BUCK���ݵ���1�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_BUCK_CAP_SEL1_UNION */
#define SOC_SCHARGER_BUCK_CAP_SEL1_ADDR(base)         ((base) + (0x76))

/* �Ĵ���˵����BUCKԤ��0�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_BUCK_RESERVE0_UNION */
#define SOC_SCHARGER_BUCK_RESERVE0_ADDR(base)         ((base) + (0x77))

/* �Ĵ���˵����BUCKԤ��1�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_BUCK_RESERVE1_UNION */
#define SOC_SCHARGER_BUCK_RESERVE1_ADDR(base)         ((base) + (0x78))

/* �Ĵ���˵����BUCKԤ��2�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_BUCK_RESERVE2_UNION */
#define SOC_SCHARGER_BUCK_RESERVE2_ADDR(base)         ((base) + (0x79))

/* �Ĵ���˵����BUCKԤ��3�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_BUCK_RESERVE3_UNION */
#define SOC_SCHARGER_BUCK_RESERVE3_ADDR(base)         ((base) + (0x7A))

/* �Ĵ���˵����BUCKԤ��0״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_BUCK_RESERVE0_STATE_UNION */
#define SOC_SCHARGER_BUCK_RESERVE0_STATE_ADDR(base)   ((base) + (0x7B))

/* �Ĵ���˵����BUCKԤ��1״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_BUCK_RESERVE1_STATE_UNION */
#define SOC_SCHARGER_BUCK_RESERVE1_STATE_ADDR(base)   ((base) + (0x7C))

/* �Ĵ���˵����OTG_REG0���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_OTG_REG0_UNION */
#define SOC_SCHARGER_OTG_REG0_ADDR(base)              ((base) + (0x80))

/* �Ĵ���˵����OTG_REG1���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_OTG_REG1_UNION */
#define SOC_SCHARGER_OTG_REG1_ADDR(base)              ((base) + (0x81))

/* �Ĵ���˵����OTG_REG2���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_OTG_REG2_UNION */
#define SOC_SCHARGER_OTG_REG2_ADDR(base)              ((base) + (0x82))

/* �Ĵ���˵����OTG_REG3���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_OTG_REG3_UNION */
#define SOC_SCHARGER_OTG_REG3_ADDR(base)              ((base) + (0x83))

/* �Ĵ���˵����OTG_REG4���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_OTG_REG4_UNION */
#define SOC_SCHARGER_OTG_REG4_ADDR(base)              ((base) + (0x84))

/* �Ĵ���˵����OTG_REG5���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_OTG_REG5_UNION */
#define SOC_SCHARGER_OTG_REG5_ADDR(base)              ((base) + (0x85))

/* �Ĵ���˵����OTG_REG6���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_OTG_REG6_UNION */
#define SOC_SCHARGER_OTG_REG6_ADDR(base)              ((base) + (0x86))

/* �Ĵ���˵����OTG_REG7���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_OTG_REG7_UNION */
#define SOC_SCHARGER_OTG_REG7_ADDR(base)              ((base) + (0x87))

/* �Ĵ���˵����OTG_REG8���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_OTG_REG8_UNION */
#define SOC_SCHARGER_OTG_REG8_ADDR(base)              ((base) + (0x88))

/* �Ĵ���˵����OTG�ڲ���ʱ���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_OTG_REG9_UNION */
#define SOC_SCHARGER_OTG_REG9_ADDR(base)              ((base) + (0x89))

/* �Ĵ���˵����OTG_TRIM����1�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_OTG_TRIM1_UNION */
#define SOC_SCHARGER_OTG_TRIM1_ADDR(base)             ((base) + (0x8A))

/* �Ĵ���˵����OTG_TRIM����2�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_OTG_TRIM2_UNION */
#define SOC_SCHARGER_OTG_TRIM2_ADDR(base)             ((base) + (0x8B))

/* �Ĵ���˵����OTGԤ��0�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_OTG_RESERVE_UNION */
#define SOC_SCHARGER_OTG_RESERVE_ADDR(base)           ((base) + (0x8C))

/* �Ĵ���˵����OTGԤ��1�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_OTG_RESERVE1_UNION */
#define SOC_SCHARGER_OTG_RESERVE1_ADDR(base)          ((base) + (0x8D))

/* �Ĵ���˵����OTGԤ��2�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_OTG_RESERVE2_UNION */
#define SOC_SCHARGER_OTG_RESERVE2_ADDR(base)          ((base) + (0x8E))

/* �Ĵ���˵����CHG_REG0���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_CHG_REG0_UNION */
#define SOC_SCHARGER_CHG_REG0_ADDR(base)              ((base) + (0x90))

/* �Ĵ���˵����CHG_REG1���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_CHG_REG1_UNION */
#define SOC_SCHARGER_CHG_REG1_ADDR(base)              ((base) + (0x91))

/* �Ĵ���˵����CHG_REG2���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_CHG_REG2_UNION */
#define SOC_SCHARGER_CHG_REG2_ADDR(base)              ((base) + (0x92))

/* �Ĵ���˵����CHG_REG3���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_CHG_REG3_UNION */
#define SOC_SCHARGER_CHG_REG3_ADDR(base)              ((base) + (0x93))

/* �Ĵ���˵����CHG_REG4���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_CHG_REG4_UNION */
#define SOC_SCHARGER_CHG_REG4_ADDR(base)              ((base) + (0x94))

/* �Ĵ���˵����CHG_REG5���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_CHG_REG5_UNION */
#define SOC_SCHARGER_CHG_REG5_ADDR(base)              ((base) + (0x95))

/* �Ĵ���˵����CHARGER��·����mos������ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_CHG_VRES_SEL_UNION */
#define SOC_SCHARGER_CHG_VRES_SEL_ADDR(base)          ((base) + (0x96))

/* �Ĵ���˵����CHARGER��·�������ݵ��ڡ�
   λ����UNION�ṹ:  SOC_SCHARGER_CHG_CAP_SEL_UNION */
#define SOC_SCHARGER_CHG_CAP_SEL_ADDR(base)           ((base) + (0x97))

/* �Ĵ���˵����CHG_REG6���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_CHG_REG6_UNION */
#define SOC_SCHARGER_CHG_REG6_ADDR(base)              ((base) + (0x98))

/* �Ĵ���˵����CHG_REG7���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_CHG_REG7_UNION */
#define SOC_SCHARGER_CHG_REG7_ADDR(base)              ((base) + (0x99))

/* �Ĵ���˵����CHG_REG8���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_CHG_REG8_UNION */
#define SOC_SCHARGER_CHG_REG8_ADDR(base)              ((base) + (0x9A))

/* �Ĵ���˵����CHG_REG9���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_CHG_REG9_UNION */
#define SOC_SCHARGER_CHG_REG9_ADDR(base)              ((base) + (0x9B))

/* �Ĵ���˵����CHG_RESVI1Ԥ���Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_CHG_RESVI1_UNION */
#define SOC_SCHARGER_CHG_RESVI1_ADDR(base)            ((base) + (0x9C))

/* �Ĵ���˵����CHG_RESVI2Ԥ���Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_CHG_RESVI2_UNION */
#define SOC_SCHARGER_CHG_RESVI2_ADDR(base)            ((base) + (0x9D))

/* �Ĵ���˵����CHG_RESVO1Ԥ���Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_CHG_RESVO1_UNION */
#define SOC_SCHARGER_CHG_RESVO1_ADDR(base)            ((base) + (0x9E))

/* �Ĵ���˵����CHG_RESVO2Ԥ���Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_CHG_RESVO2_UNION */
#define SOC_SCHARGER_CHG_RESVO2_ADDR(base)            ((base) + (0x9F))

/* �Ĵ���˵����DET_TOP_REG0���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_DET_TOP_REG0_UNION */
#define SOC_SCHARGER_DET_TOP_REG0_ADDR(base)          ((base) + (0xA0))

/* �Ĵ���˵����DET_TOP_REG1���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_DET_TOP_REG1_UNION */
#define SOC_SCHARGER_DET_TOP_REG1_ADDR(base)          ((base) + (0xA1))

/* �Ĵ���˵����THSD���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_THSD_ADJ_UNION */
#define SOC_SCHARGER_THSD_ADJ_ADDR(base)              ((base) + (0xA2))

/* �Ĵ���˵����SCHG_LOGIC���ƼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_SCHG_LOGIC_CTRL_UNION */
#define SOC_SCHARGER_SCHG_LOGIC_CTRL_ADDR(base)       ((base) + (0xA3))

/* �Ĵ���˵����BLOCK���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_BLOCK_CTRL_UNION */
#define SOC_SCHARGER_BLOCK_CTRL_ADDR(base)            ((base) + (0xA4))

/* �Ĵ���˵����REF_TOP���ڼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_REF_TOP_CTRL_UNION */
#define SOC_SCHARGER_REF_TOP_CTRL_ADDR(base)          ((base) + (0xA5))

/* �Ĵ���˵����ADC���ƼĴ���
   λ����UNION�ṹ:  SOC_SCHARGER_ADC_CTRL_UNION */
#define SOC_SCHARGER_ADC_CTRL_ADDR(base)              ((base) + (0xB0))

/* �Ĵ���˵����ADCת����ʼ�Ĵ���
   λ����UNION�ṹ:  SOC_SCHARGER_ADC_START_UNION */
#define SOC_SCHARGER_ADC_START_ADDR(base)             ((base) + (0xB1))

/* �Ĵ���˵����ADCת��״ָ̬ʾ�Ĵ���
   λ����UNION�ṹ:  SOC_SCHARGER_ADC_CONV_STATUS_UNION */
#define SOC_SCHARGER_ADC_CONV_STATUS_ADDR(base)       ((base) + (0xB2))

/* �Ĵ���˵����ADCת�������λ�Ĵ���
   λ����UNION�ṹ:  SOC_SCHARGER_ADC_DATA1_UNION */
#define SOC_SCHARGER_ADC_DATA1_ADDR(base)             ((base) + (0xB3))

/* �Ĵ���˵����ADCת�������λ�Ĵ���
   λ����UNION�ṹ:  SOC_SCHARGER_ADC_DATA0_UNION */
#define SOC_SCHARGER_ADC_DATA0_ADDR(base)             ((base) + (0xB4))

/* �Ĵ���˵����HKADC����IBIAS�������üĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_ADC_IBIAS_SEL_UNION */
#define SOC_SCHARGER_ADC_IBIAS_SEL_ADDR(base)         ((base) + (0xB5))

/* �Ĵ���˵����EFUSE����0�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_EFUSE_REG0_UNION */
#define SOC_SCHARGER_EFUSE_REG0_ADDR(base)            ((base) + (0xC0))

/* �Ĵ���˵����EFUSE����1�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_EFUSE_REG1_UNION */
#define SOC_SCHARGER_EFUSE_REG1_ADDR(base)            ((base) + (0xC1))

/* �Ĵ���˵����EFUSE��ַ�Ĵ�����Ӧ��ַ[7:0]��
   λ����UNION�ṹ:  SOC_SCHARGER_EFUSE_WE0_UNION */
#define SOC_SCHARGER_EFUSE_WE0_ADDR(base)             ((base) + (0xC2))

/* �Ĵ���˵����EFUSE��ַ�Ĵ�����Ӧ��ַ[15:8]��
   λ����UNION�ṹ:  SOC_SCHARGER_EFUSE_WE1_UNION */
#define SOC_SCHARGER_EFUSE_WE1_ADDR(base)             ((base) + (0xC3))

/* �Ĵ���˵����EFUSE��ַ�Ĵ�����Ӧ��ַ[23:16]��
   λ����UNION�ṹ:  SOC_SCHARGER_EFUSE_WE2_UNION */
#define SOC_SCHARGER_EFUSE_WE2_ADDR(base)             ((base) + (0xC4))

/* �Ĵ���˵����EFUSE��ַ�Ĵ�����Ӧ��ַ[31:24]��
   λ����UNION�ṹ:  SOC_SCHARGER_EFUSE_WE3_UNION */
#define SOC_SCHARGER_EFUSE_WE3_ADDR(base)             ((base) + (0xC5))

/* �Ĵ���˵����EFUSE��ַ�Ĵ�����Ӧ��ַ[39:32]��
   λ����UNION�ṹ:  SOC_SCHARGER_EFUSE_WE4_UNION */
#define SOC_SCHARGER_EFUSE_WE4_ADDR(base)             ((base) + (0xC6))

/* �Ĵ���˵����EFUSE��ַ�Ĵ�����Ӧ��ַ[47:40]��
   λ����UNION�ṹ:  SOC_SCHARGER_EFUSE_WE5_UNION */
#define SOC_SCHARGER_EFUSE_WE5_ADDR(base)             ((base) + (0xC7))

/* �Ĵ���˵����EFUSE��ַ�Ĵ�����Ӧ��ַ[55:48]��
   λ����UNION�ṹ:  SOC_SCHARGER_EFUSE_WE6_UNION */
#define SOC_SCHARGER_EFUSE_WE6_ADDR(base)             ((base) + (0xC8))

/* �Ĵ���˵����EFUSE��ַ�Ĵ�����Ӧ��ַ[63:56]��
   λ����UNION�ṹ:  SOC_SCHARGER_EFUSE_WE7_UNION */
#define SOC_SCHARGER_EFUSE_WE7_ADDR(base)             ((base) + (0xC9))

/* �Ĵ���˵����EFUSE���������Ӧ��ַ[7:0]��
   λ����UNION�ṹ:  SOC_SCHARGER_EFUSE_PDOB0_UNION */
#define SOC_SCHARGER_EFUSE_PDOB0_ADDR(base)           ((base) + (0xCA))

/* �Ĵ���˵����EFUSE���������Ӧ��ַ[15:8]��
   λ����UNION�ṹ:  SOC_SCHARGER_EFUSE_PDOB1_UNION */
#define SOC_SCHARGER_EFUSE_PDOB1_ADDR(base)           ((base) + (0xCB))

/* �Ĵ���˵����EFUSE���������Ӧ��ַ[23:16]��
   λ����UNION�ṹ:  SOC_SCHARGER_EFUSE_PDOB2_UNION */
#define SOC_SCHARGER_EFUSE_PDOB2_ADDR(base)           ((base) + (0xCC))

/* �Ĵ���˵����EFUSE���������Ӧ��ַ[31:24]��
   λ����UNION�ṹ:  SOC_SCHARGER_EFUSE_PDOB3_UNION */
#define SOC_SCHARGER_EFUSE_PDOB3_ADDR(base)           ((base) + (0xCD))

/* �Ĵ���˵����EFUSE���������Ӧ��ַ[39:32]��
   λ����UNION�ṹ:  SOC_SCHARGER_EFUSE_PDOB4_UNION */
#define SOC_SCHARGER_EFUSE_PDOB4_ADDR(base)           ((base) + (0xCE))

/* �Ĵ���˵����EFUSE���������Ӧ��ַ[47:40]��
   λ����UNION�ṹ:  SOC_SCHARGER_EFUSE_PDOB5_UNION */
#define SOC_SCHARGER_EFUSE_PDOB5_ADDR(base)           ((base) + (0xCF))

/* �Ĵ���˵����EFUSE���������Ӧ��ַ[55:48]��
   λ����UNION�ṹ:  SOC_SCHARGER_EFUSE_PDOB6_UNION */
#define SOC_SCHARGER_EFUSE_PDOB6_ADDR(base)           ((base) + (0xD0))

/* �Ĵ���˵����EFUSE���������Ӧ��ַ[63:56]��
   λ����UNION�ṹ:  SOC_SCHARGER_EFUSE_PDOB7_UNION */
#define SOC_SCHARGER_EFUSE_PDOB7_ADDR(base)           ((base) + (0xD1))

/* �Ĵ���˵����EFUSE��λ���ƼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_EFUSE_SOFT_RST_CTRL_UNION */
#define SOC_SCHARGER_EFUSE_SOFT_RST_CTRL_ADDR(base)   ((base) + (0xD2))

/* �Ĵ���˵����SYS����1�Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_SYS_RESVO1_UNION */
#define SOC_SCHARGER_SYS_RESVO1_ADDR(base)            ((base) + (0xE0))

/* �Ĵ���˵����SYS_RESVO2Ԥ���Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_SYS_RESVO2_UNION */
#define SOC_SCHARGER_SYS_RESVO2_ADDR(base)            ((base) + (0xE1))

/* �Ĵ���˵����SYS_RESVO3Ԥ���Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_SYS_RESVO3_UNION */
#define SOC_SCHARGER_SYS_RESVO3_ADDR(base)            ((base) + (0xE2))

/* �Ĵ���˵����SYS_RESVO4Ԥ���Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_SYS_RESVO4_UNION */
#define SOC_SCHARGER_SYS_RESVO4_ADDR(base)            ((base) + (0xE3))

/* �Ĵ���˵����SYS_RESVI1Ԥ���Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_SYS_RESVI1_UNION */
#define SOC_SCHARGER_SYS_RESVI1_ADDR(base)            ((base) + (0xE4))

/* �Ĵ���˵����SYS_RESVI2Ԥ���Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_SYS_RESVI2_UNION */
#define SOC_SCHARGER_SYS_RESVI2_ADDR(base)            ((base) + (0xE5))

/* �Ĵ���˵����2MHz�߾���ʱ��Ƶ���޵��Ĵ�����
   λ����UNION�ṹ:  SOC_SCHARGER_OSC_FCP_UNION */
#define SOC_SCHARGER_OSC_FCP_ADDR(base)               ((base) + (0xE6))

/* �Ĵ���˵����ȫ����λ���ƼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_GLB_SOFT_RST_CTRL_UNION */
#define SOC_SCHARGER_GLB_SOFT_RST_CTRL_ADDR(base)     ((base) + (0xE7))

/* �Ĵ���˵�������Ź���λ���ƼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_WATCHDOG_SOFT_RST_UNION */
#define SOC_SCHARGER_WATCHDOG_SOFT_RST_ADDR(base)     ((base) + (0xE8))

/* �Ĵ���˵����ι��ʱ����ƼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_WATCHDOG_CTRL_UNION */
#define SOC_SCHARGER_WATCHDOG_CTRL_ADDR(base)         ((base) + (0xE9))

/* �Ĵ���˵����clk gating���ƼĴ�����
   λ����UNION�ṹ:  SOC_SCHARGER_CLK_GATE_UNION */
#define SOC_SCHARGER_CLK_GATE_ADDR(base)              ((base) + (0xEA))





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
 �ṹ��    : SOC_SCHARGER_CHIP_VERSION_0_UNION
 �ṹ˵��  : CHIP_VERSION_0 �Ĵ����ṹ���塣��ַƫ����:0x00����ֵ:0x36�����:8
 �Ĵ���˵��: оƬ�汾�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chip_id2 : 8;  /* bit[0-7]: ASIC���ʾ��Ŀ���6�� */
    } reg;
} SOC_SCHARGER_CHIP_VERSION_0_UNION;
#endif
#define SOC_SCHARGER_CHIP_VERSION_0_chip_id2_START  (0)
#define SOC_SCHARGER_CHIP_VERSION_0_chip_id2_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_CHIP_VERSION_1_UNION
 �ṹ˵��  : CHIP_VERSION_1 �Ĵ����ṹ���塣��ַƫ����:0x01����ֵ:0x35�����:8
 �Ĵ���˵��: оƬ�汾�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chip_id3 : 8;  /* bit[0-7]: ASIC���ʾ��Ŀ���5�� */
    } reg;
} SOC_SCHARGER_CHIP_VERSION_1_UNION;
#endif
#define SOC_SCHARGER_CHIP_VERSION_1_chip_id3_START  (0)
#define SOC_SCHARGER_CHIP_VERSION_1_chip_id3_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_CHIP_VERSION_2_UNION
 �ṹ˵��  : CHIP_VERSION_2 �Ĵ����ṹ���塣��ַƫ����:0x02����ֵ:0x32�����:8
 �Ĵ���˵��: оƬ�汾�Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chip_id4 : 8;  /* bit[0-7]: ASIC���ʾ��Ŀ���2�� */
    } reg;
} SOC_SCHARGER_CHIP_VERSION_2_UNION;
#endif
#define SOC_SCHARGER_CHIP_VERSION_2_chip_id4_START  (0)
#define SOC_SCHARGER_CHIP_VERSION_2_chip_id4_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_CHIP_VERSION_3_UNION
 �ṹ˵��  : CHIP_VERSION_3 �Ĵ����ṹ���塣��ַƫ����:0x03����ֵ:0x33�����:8
 �Ĵ���˵��: оƬ�汾�Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chip_id5 : 8;  /* bit[0-7]: ASIC���ʾ��Ŀ���3�� */
    } reg;
} SOC_SCHARGER_CHIP_VERSION_3_UNION;
#endif
#define SOC_SCHARGER_CHIP_VERSION_3_chip_id5_START  (0)
#define SOC_SCHARGER_CHIP_VERSION_3_chip_id5_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_CHIP_VERSION_4_UNION
 �ṹ˵��  : CHIP_VERSION_4 �Ĵ����ṹ���塣��ַƫ����:0x04����ֵ:0x03�����:8
 �Ĵ���˵��: оƬ�汾�Ĵ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chip_id0 : 8;  /* bit[0-7]: �汾�Ĵ�������ʾV300��3�� */
    } reg;
} SOC_SCHARGER_CHIP_VERSION_4_UNION;
#endif
#define SOC_SCHARGER_CHIP_VERSION_4_chip_id0_START  (0)
#define SOC_SCHARGER_CHIP_VERSION_4_chip_id0_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_CHIP_VERSION_5_UNION
 �ṹ˵��  : CHIP_VERSION_5 �Ĵ����ṹ���塣��ַƫ����:0x05����ֵ:0x00�����:8
 �Ĵ���˵��: оƬ�汾�Ĵ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chip_id1 : 8;  /* bit[0-7]: �汾�Ĵ�������ʾV300��00�� */
    } reg;
} SOC_SCHARGER_CHIP_VERSION_5_UNION;
#endif
#define SOC_SCHARGER_CHIP_VERSION_5_chip_id1_START  (0)
#define SOC_SCHARGER_CHIP_VERSION_5_chip_id1_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_STATUS0_UNION
 �ṹ˵��  : STATUS0 �Ĵ����ṹ���塣��ַƫ����:0x06����ֵ:0x00�����:8
 �Ĵ���˵��: ״̬��־0�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_rechg_state : 1;  /* bit[0]  : ϵͳ�����״̬��¼�Ĵ�����
                                                          0��not in recharging state��
                                                          1��In recharging state�� */
        unsigned char  chg_therm_state : 1;  /* bit[1]  : ϵͳ�ȵ���״̬��¼�Ĵ�����
                                                          0��Normal��
                                                          1��In Thermal Regulation�� */
        unsigned char  chg_dpm_state   : 1;  /* bit[2]  : ϵͳdpm״̬��¼�Ĵ�����
                                                          0��Normal�� 
                                                          1��In dpm Regulation�� */
        unsigned char  chg_acl_state   : 1;  /* bit[3]  : ϵͳacl״̬��¼�Ĵ�����
                                                          0��Normal��
                                                          1��In acl Regulation�� */
        unsigned char  chg_chgstate    : 2;  /* bit[4-5]: ���״̬��¼�Ĵ�����
                                                          00��Not Charging��
                                                          01��Pre-charge��
                                                          10��Fast-charg��
                                                          11��Charge Termination Done�� */
        unsigned char  otg_on          : 1;  /* bit[6]  : boost״ָ̬ʾ��
                                                          0��OTG�رգ�
                                                          1��OTG������ */
        unsigned char  buck_ok         : 1;  /* bit[7]  : buck����״ָ̬ʾ��
                                                          0��buckû�й�����
                                                          1��buck�ڹ����� */
    } reg;
} SOC_SCHARGER_STATUS0_UNION;
#endif
#define SOC_SCHARGER_STATUS0_chg_rechg_state_START  (0)
#define SOC_SCHARGER_STATUS0_chg_rechg_state_END    (0)
#define SOC_SCHARGER_STATUS0_chg_therm_state_START  (1)
#define SOC_SCHARGER_STATUS0_chg_therm_state_END    (1)
#define SOC_SCHARGER_STATUS0_chg_dpm_state_START    (2)
#define SOC_SCHARGER_STATUS0_chg_dpm_state_END      (2)
#define SOC_SCHARGER_STATUS0_chg_acl_state_START    (3)
#define SOC_SCHARGER_STATUS0_chg_acl_state_END      (3)
#define SOC_SCHARGER_STATUS0_chg_chgstate_START     (4)
#define SOC_SCHARGER_STATUS0_chg_chgstate_END       (5)
#define SOC_SCHARGER_STATUS0_otg_on_START           (6)
#define SOC_SCHARGER_STATUS0_otg_on_END             (6)
#define SOC_SCHARGER_STATUS0_buck_ok_START          (7)
#define SOC_SCHARGER_STATUS0_buck_ok_END            (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_STATUS1_UNION
 �ṹ˵��  : STATUS1 �Ĵ����ṹ���塣��ַƫ����:0x07����ֵ:0x03�����:8
 �Ĵ���˵��: ״̬��־1�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  batfet_ctrl    : 1;  /* bit[0]  : ���ܿ���״̬�Ĵ�����
                                                         0���ر�batfet��
                                                         1����batfet�� */
        unsigned char  wdt_time_out_n : 1;  /* bit[1]  : 0: watchdog timer �����SOC�ڹ涨ʱ����û����watchdog timer�Ĵ��������ڹ涨ʱ����û�ж�wd_rst_n��0xE8���Ĵ���д1��
                                                         1: watchdog timer ����û�д��� ��watchdog timer������ */
        unsigned char  otg_en_in      : 1;  /* bit[2]  : OTGʹ�ܵ�ָʾ�źţ�
                                                         0��OTGû��ʹ�ܣ�
                                                         1��OTG�Ѿ�ʹ�ܣ� */
        unsigned char  chg_batfet_ocp : 1;  /* bit[3]  : batfet 12A ��������״ָ̬ʾ�Ĵ�����
                                                         0��û�й�����
                                                         1������������ */
        unsigned char  reserved       : 4;  /* bit[4-7]: ������ */
    } reg;
} SOC_SCHARGER_STATUS1_UNION;
#endif
#define SOC_SCHARGER_STATUS1_batfet_ctrl_START     (0)
#define SOC_SCHARGER_STATUS1_batfet_ctrl_END       (0)
#define SOC_SCHARGER_STATUS1_wdt_time_out_n_START  (1)
#define SOC_SCHARGER_STATUS1_wdt_time_out_n_END    (1)
#define SOC_SCHARGER_STATUS1_otg_en_in_START       (2)
#define SOC_SCHARGER_STATUS1_otg_en_in_END         (2)
#define SOC_SCHARGER_STATUS1_chg_batfet_ocp_START  (3)
#define SOC_SCHARGER_STATUS1_chg_batfet_ocp_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_STATUS2_UNION
 �ṹ˵��  : STATUS2 �Ĵ����ṹ���塣��ַƫ����:0x08����ֵ:0x00�����:8
 �Ĵ���˵��: ״̬��־2�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_state : 8;  /* bit[0-7]: OTG״ָ̬ʾ��
                                                    ע���ڲ������á� */
    } reg;
} SOC_SCHARGER_STATUS2_UNION;
#endif
#define SOC_SCHARGER_STATUS2_otg_state_START  (0)
#define SOC_SCHARGER_STATUS2_otg_state_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_IRQ_STATUS0_UNION
 �ṹ˵��  : IRQ_STATUS0 �Ĵ����ṹ���塣��ַƫ����:0x09����ֵ:0x00�����:8
 �Ĵ���˵��: �ж�״̬��־0�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otmp_140_r  : 1;  /* bit[0]: �¶�״̬��¼�Ĵ�����
                                                    0���¶�û���������¶�(140��)��
                                                    1���¶ȳ��������¶�(140��)�� */
        unsigned char  otg_ovp_r   : 1;  /* bit[1]: OTG�����ѹ״̬��¼�Ĵ�����
                                                    0��otg boost û�з�����ѹ��
                                                    1��otg boost ������ѹ�� */
        unsigned char  otg_uvp_r   : 1;  /* bit[2]: OTG���Ƿѹ״̬��¼�Ĵ�����
                                                    0��otg boost û�з���Ƿѹ��
                                                    1��otg boost ����Ƿѹ�� */
        unsigned char  otg_ocp_r   : 1;  /* bit[3]: OTG�������״̬��¼�Ĵ�����
                                                    0��otg û�з���������
                                                    1��otg ���������� */
        unsigned char  otg_scp_r   : 1;  /* bit[4]: OTG�����·״̬��¼�Ĵ�����
                                                    0��otg û�з�����·��
                                                    1��otg ������·�� */
        unsigned char  otmp_jreg_r : 1;  /* bit[5]: �¶ȳ����ȵ����¶�״̬��¼�Ĵ�����
                                                    0���¶�û�����ȵ��������¶ȣ�
                                                    1���¶ȳ����ȵ��������¶ȡ� */
        unsigned char  buck_ocp_r  : 1;  /* bit[6]: BUCK�������״̬��¼�Ĵ�����
                                                    0��buckû�з���������
                                                    1��buck���������� */
        unsigned char  buck_scp_r  : 1;  /* bit[7]: BUCK�����·״̬��¼�Ĵ�����
                                                    0��buckû�з�����·��
                                                    1��buck������·�� */
    } reg;
} SOC_SCHARGER_IRQ_STATUS0_UNION;
#endif
#define SOC_SCHARGER_IRQ_STATUS0_otmp_140_r_START   (0)
#define SOC_SCHARGER_IRQ_STATUS0_otmp_140_r_END     (0)
#define SOC_SCHARGER_IRQ_STATUS0_otg_ovp_r_START    (1)
#define SOC_SCHARGER_IRQ_STATUS0_otg_ovp_r_END      (1)
#define SOC_SCHARGER_IRQ_STATUS0_otg_uvp_r_START    (2)
#define SOC_SCHARGER_IRQ_STATUS0_otg_uvp_r_END      (2)
#define SOC_SCHARGER_IRQ_STATUS0_otg_ocp_r_START    (3)
#define SOC_SCHARGER_IRQ_STATUS0_otg_ocp_r_END      (3)
#define SOC_SCHARGER_IRQ_STATUS0_otg_scp_r_START    (4)
#define SOC_SCHARGER_IRQ_STATUS0_otg_scp_r_END      (4)
#define SOC_SCHARGER_IRQ_STATUS0_otmp_jreg_r_START  (5)
#define SOC_SCHARGER_IRQ_STATUS0_otmp_jreg_r_END    (5)
#define SOC_SCHARGER_IRQ_STATUS0_buck_ocp_r_START   (6)
#define SOC_SCHARGER_IRQ_STATUS0_buck_ocp_r_END     (6)
#define SOC_SCHARGER_IRQ_STATUS0_buck_scp_r_START   (7)
#define SOC_SCHARGER_IRQ_STATUS0_buck_scp_r_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_IRQ_STATUS1_UNION
 �ṹ˵��  : IRQ_STATUS1 �Ĵ����ṹ���塣��ַƫ����:0x0A����ֵ:0x00�����:8
 �Ĵ���˵��: �ж�״̬��־1�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  regn_ocp_r       : 1;  /* bit[0]: ldo5����״̬��¼�Ĵ�����
                                                         0��ldo5û�й�����
                                                         1��ldo5���������� */
        unsigned char  vbat_ovp_r       : 1;  /* bit[1]: vbat(charger IC���)��ѹ״̬��¼�Ĵ�����
                                                         0��û�й�ѹ��������vbat<102% ����
                                                         1����ѹ������vbat>104%���� */
        unsigned char  vbus_uvp_r       : 1;  /* bit[2]: vbusǷѹ״̬��¼�Ĵ�����
                                                         0��vbus û�з���Ƿѹ��
                                                         1��vbus ����Ƿѹ�� */
        unsigned char  vbus_ovp_r       : 1;  /* bit[3]: vbus��ѹ״̬��¼�Ĵ�����
                                                         0��vbus û�з�����ѹ��
                                                         1��vbus ������ѹ�� */
        unsigned char  sys_ocp_r        : 1;  /* bit[4]: ��ط���ŵ����״̬��¼�Ĵ�����
                                                         0��Normal��
                                                         1������ŵ������ */
        unsigned char  chg_fast_fault_r : 1;  /* bit[5]: ����fault״̬��¼�Ĵ�����
                                                         0��Normal�� 
                                                         1��In fast charging fault�� */
        unsigned char  chg_pre_fault_r  : 1;  /* bit[6]: Ԥ���fault״̬��¼�Ĵ�����
                                                         0��Normal��
                                                         1��In pre charging fault�� */
        unsigned char  chg_tri_fault_r  : 1;  /* bit[7]: ������fault״̬��¼�Ĵ�����
                                                         0��Normal��
                                                         1��In tricle charging fault�� */
    } reg;
} SOC_SCHARGER_IRQ_STATUS1_UNION;
#endif
#define SOC_SCHARGER_IRQ_STATUS1_regn_ocp_r_START        (0)
#define SOC_SCHARGER_IRQ_STATUS1_regn_ocp_r_END          (0)
#define SOC_SCHARGER_IRQ_STATUS1_vbat_ovp_r_START        (1)
#define SOC_SCHARGER_IRQ_STATUS1_vbat_ovp_r_END          (1)
#define SOC_SCHARGER_IRQ_STATUS1_vbus_uvp_r_START        (2)
#define SOC_SCHARGER_IRQ_STATUS1_vbus_uvp_r_END          (2)
#define SOC_SCHARGER_IRQ_STATUS1_vbus_ovp_r_START        (3)
#define SOC_SCHARGER_IRQ_STATUS1_vbus_ovp_r_END          (3)
#define SOC_SCHARGER_IRQ_STATUS1_sys_ocp_r_START         (4)
#define SOC_SCHARGER_IRQ_STATUS1_sys_ocp_r_END           (4)
#define SOC_SCHARGER_IRQ_STATUS1_chg_fast_fault_r_START  (5)
#define SOC_SCHARGER_IRQ_STATUS1_chg_fast_fault_r_END    (5)
#define SOC_SCHARGER_IRQ_STATUS1_chg_pre_fault_r_START   (6)
#define SOC_SCHARGER_IRQ_STATUS1_chg_pre_fault_r_END     (6)
#define SOC_SCHARGER_IRQ_STATUS1_chg_tri_fault_r_START   (7)
#define SOC_SCHARGER_IRQ_STATUS1_chg_tri_fault_r_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_IRQ_STATUS2_UNION
 �ṹ˵��  : IRQ_STATUS2 �Ĵ����ṹ���塣��ַƫ����:0x0B����ֵ:0x00�����:8
 �Ĵ���˵��: �ж�״̬��־1�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  bat_ltmp_r : 1;  /* bit[0]  : ����¶ȼ��״̬��¼�Ĵ�����
                                                     0�����û�з������¹��£���������
                                                     1����ص��¹��¡� */
        unsigned char  bat_htmp_r : 1;  /* bit[1]  : ����¶ȼ��״̬��¼�Ĵ�����
                                                     0�����û�з������¹��£���������
                                                     1����ظ��¹��¡� */
        unsigned char  reserved   : 6;  /* bit[2-7]: ������ */
    } reg;
} SOC_SCHARGER_IRQ_STATUS2_UNION;
#endif
#define SOC_SCHARGER_IRQ_STATUS2_bat_ltmp_r_START  (0)
#define SOC_SCHARGER_IRQ_STATUS2_bat_ltmp_r_END    (0)
#define SOC_SCHARGER_IRQ_STATUS2_bat_htmp_r_START  (1)
#define SOC_SCHARGER_IRQ_STATUS2_bat_htmp_r_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_IRQ0_UNION
 �ṹ˵��  : IRQ0 �Ĵ����ṹ���塣��ַƫ����:0x0C����ֵ:0x00�����:8
 �Ĵ���˵��: �ж�0�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otmp_140_r  : 1;  /* bit[0]: 0���޴��жϣ�
                                                    1���¶ȳ��������¶�(140��)�жϡ� */
        unsigned char  otg_ovp_r   : 1;  /* bit[1]: 0���޴��жϣ�
                                                    1��otg boost �����ѹ�жϡ� */
        unsigned char  otg_uvp_r   : 1;  /* bit[2]: 0���޴��жϣ�
                                                    1��otg boost ���Ƿѹ�жϡ� */
        unsigned char  otg_ocp_r   : 1;  /* bit[3]: 0���޴��жϣ�
                                                    1��otg ��������жϡ� */
        unsigned char  otg_scp_r   : 1;  /* bit[4]: 0���޴��жϣ�
                                                    1��otg �����·�жϡ� */
        unsigned char  otmp_jreg_r : 1;  /* bit[5]: 0���޴��жϣ�
                                                    1���¶ȳ����ȵ��������¶��жϡ� */
        unsigned char  buck_ocp_r  : 1;  /* bit[6]: 0���޴��жϣ�
                                                    1��BUCK��������жϡ� */
        unsigned char  buck_scp_r  : 1;  /* bit[7]: 0���޴��жϣ�
                                                    1��BUCK�����·�жϡ� */
    } reg;
} SOC_SCHARGER_IRQ0_UNION;
#endif
#define SOC_SCHARGER_IRQ0_otmp_140_r_START   (0)
#define SOC_SCHARGER_IRQ0_otmp_140_r_END     (0)
#define SOC_SCHARGER_IRQ0_otg_ovp_r_START    (1)
#define SOC_SCHARGER_IRQ0_otg_ovp_r_END      (1)
#define SOC_SCHARGER_IRQ0_otg_uvp_r_START    (2)
#define SOC_SCHARGER_IRQ0_otg_uvp_r_END      (2)
#define SOC_SCHARGER_IRQ0_otg_ocp_r_START    (3)
#define SOC_SCHARGER_IRQ0_otg_ocp_r_END      (3)
#define SOC_SCHARGER_IRQ0_otg_scp_r_START    (4)
#define SOC_SCHARGER_IRQ0_otg_scp_r_END      (4)
#define SOC_SCHARGER_IRQ0_otmp_jreg_r_START  (5)
#define SOC_SCHARGER_IRQ0_otmp_jreg_r_END    (5)
#define SOC_SCHARGER_IRQ0_buck_ocp_r_START   (6)
#define SOC_SCHARGER_IRQ0_buck_ocp_r_END     (6)
#define SOC_SCHARGER_IRQ0_buck_scp_r_START   (7)
#define SOC_SCHARGER_IRQ0_buck_scp_r_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_IRQ1_UNION
 �ṹ˵��  : IRQ1 �Ĵ����ṹ���塣��ַƫ����:0x0D����ֵ:0x00�����:8
 �Ĵ���˵��: �ж�1�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  regn_ocp_r       : 1;  /* bit[0]: 0���޴��жϣ�
                                                         1��ldo5��������жϡ� */
        unsigned char  vbat_ovp_r       : 1;  /* bit[1]: 0���޴��жϣ�
                                                         1��vbat(charger IC���)�����ѹ�жϡ� */
        unsigned char  vbus_uvp_r       : 1;  /* bit[2]: 0���޴��жϣ�
                                                         1��vbus���Ƿѹ�жϡ� */
        unsigned char  vbus_ovp_r       : 1;  /* bit[3]: 0���޴��жϣ�
                                                         1��vbus�����ѹ�жϡ� */
        unsigned char  sys_ocp_r        : 1;  /* bit[4]: 0���޴��жϣ�
                                                         1����ط���ŵ�����жϡ� */
        unsigned char  chg_fast_fault_r : 1;  /* bit[5]: 0���޴��жϣ�
                                                         1������fault�жϡ� */
        unsigned char  chg_pre_fault_r  : 1;  /* bit[6]: 0���޴��жϣ�
                                                         1��Ԥ���fault�жϡ� */
        unsigned char  chg_tri_fault_r  : 1;  /* bit[7]: 0���޴��жϣ�
                                                         1��������fault�жϡ� */
    } reg;
} SOC_SCHARGER_IRQ1_UNION;
#endif
#define SOC_SCHARGER_IRQ1_regn_ocp_r_START        (0)
#define SOC_SCHARGER_IRQ1_regn_ocp_r_END          (0)
#define SOC_SCHARGER_IRQ1_vbat_ovp_r_START        (1)
#define SOC_SCHARGER_IRQ1_vbat_ovp_r_END          (1)
#define SOC_SCHARGER_IRQ1_vbus_uvp_r_START        (2)
#define SOC_SCHARGER_IRQ1_vbus_uvp_r_END          (2)
#define SOC_SCHARGER_IRQ1_vbus_ovp_r_START        (3)
#define SOC_SCHARGER_IRQ1_vbus_ovp_r_END          (3)
#define SOC_SCHARGER_IRQ1_sys_ocp_r_START         (4)
#define SOC_SCHARGER_IRQ1_sys_ocp_r_END           (4)
#define SOC_SCHARGER_IRQ1_chg_fast_fault_r_START  (5)
#define SOC_SCHARGER_IRQ1_chg_fast_fault_r_END    (5)
#define SOC_SCHARGER_IRQ1_chg_pre_fault_r_START   (6)
#define SOC_SCHARGER_IRQ1_chg_pre_fault_r_END     (6)
#define SOC_SCHARGER_IRQ1_chg_tri_fault_r_START   (7)
#define SOC_SCHARGER_IRQ1_chg_tri_fault_r_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_IRQ2_UNION
 �ṹ˵��  : IRQ2 �Ĵ����ṹ���塣��ַƫ����:0x0E����ֵ:0x00�����:8
 �Ĵ���˵��: �ж�2�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  bat_ltmp_r : 1;  /* bit[0]  : 0���޴��жϣ�
                                                     1����ص��¹����жϡ� */
        unsigned char  bat_htmp_r : 1;  /* bit[1]  : 0���޴��жϣ�
                                                     1����ظ��¹����жϡ� */
        unsigned char  reserved   : 6;  /* bit[2-7]: ������ */
    } reg;
} SOC_SCHARGER_IRQ2_UNION;
#endif
#define SOC_SCHARGER_IRQ2_bat_ltmp_r_START  (0)
#define SOC_SCHARGER_IRQ2_bat_ltmp_r_END    (0)
#define SOC_SCHARGER_IRQ2_bat_htmp_r_START  (1)
#define SOC_SCHARGER_IRQ2_bat_htmp_r_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_WATCHDOG_IRQ_UNION
 �ṹ˵��  : WATCHDOG_IRQ �Ĵ����ṹ���塣��ַƫ����:0x0F����ֵ:0x00�����:8
 �Ĵ���˵��: ���Ź��жϼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  wdt_irq  : 1;  /* bit[0]  : ���Ź��ж��¼���
                                                   0��δ���������ж��¼���
                                                   1���������Ź��жϡ� */
        unsigned char  reserved : 7;  /* bit[1-7]: ������ */
    } reg;
} SOC_SCHARGER_WATCHDOG_IRQ_UNION;
#endif
#define SOC_SCHARGER_WATCHDOG_IRQ_wdt_irq_START   (0)
#define SOC_SCHARGER_WATCHDOG_IRQ_wdt_irq_END     (0)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_IRQ0_MASK_UNION
 �ṹ˵��  : IRQ0_MASK �Ĵ����ṹ���塣��ַƫ����:0x10����ֵ:0x48�����:8
 �Ĵ���˵��: �ж�����0�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otmp_140_mk  : 1;  /* bit[0]: 0��ʹ�ܸ��жϣ�(Ĭ�ϲ�����)
                                                     1�����θ��жϡ� */
        unsigned char  otg_ovp_mk   : 1;  /* bit[1]: 0��ʹ�ܸ��жϣ�(Ĭ�ϲ�����)
                                                     1�����θ��жϡ� */
        unsigned char  otg_uvp_mk   : 1;  /* bit[2]: 0��ʹ�ܸ��жϣ�(Ĭ�ϲ�����)
                                                     1�����θ��жϡ� */
        unsigned char  otg_ocp_mk   : 1;  /* bit[3]: 0��ʹ�ܸ��жϣ�
                                                     1�����θ��жϡ�(Ĭ������) */
        unsigned char  otg_scp_mk   : 1;  /* bit[4]: 0��ʹ�ܸ��жϣ�(Ĭ�ϲ�����)
                                                     1�����θ��жϡ� */
        unsigned char  otmp_jreg_mk : 1;  /* bit[5]: 0��ʹ�ܸ��жϣ�(Ĭ�ϲ�����)
                                                     1�����θ��жϡ� */
        unsigned char  buck_ocp_mk  : 1;  /* bit[6]: 0��ʹ�ܸ��жϣ�
                                                     1�����θ��жϡ���Ĭ�����Σ� */
        unsigned char  buck_scp_mk  : 1;  /* bit[7]: 0��ʹ�ܸ��жϣ�(Ĭ�ϲ�����)
                                                     1�����θ��жϡ� */
    } reg;
} SOC_SCHARGER_IRQ0_MASK_UNION;
#endif
#define SOC_SCHARGER_IRQ0_MASK_otmp_140_mk_START   (0)
#define SOC_SCHARGER_IRQ0_MASK_otmp_140_mk_END     (0)
#define SOC_SCHARGER_IRQ0_MASK_otg_ovp_mk_START    (1)
#define SOC_SCHARGER_IRQ0_MASK_otg_ovp_mk_END      (1)
#define SOC_SCHARGER_IRQ0_MASK_otg_uvp_mk_START    (2)
#define SOC_SCHARGER_IRQ0_MASK_otg_uvp_mk_END      (2)
#define SOC_SCHARGER_IRQ0_MASK_otg_ocp_mk_START    (3)
#define SOC_SCHARGER_IRQ0_MASK_otg_ocp_mk_END      (3)
#define SOC_SCHARGER_IRQ0_MASK_otg_scp_mk_START    (4)
#define SOC_SCHARGER_IRQ0_MASK_otg_scp_mk_END      (4)
#define SOC_SCHARGER_IRQ0_MASK_otmp_jreg_mk_START  (5)
#define SOC_SCHARGER_IRQ0_MASK_otmp_jreg_mk_END    (5)
#define SOC_SCHARGER_IRQ0_MASK_buck_ocp_mk_START   (6)
#define SOC_SCHARGER_IRQ0_MASK_buck_ocp_mk_END     (6)
#define SOC_SCHARGER_IRQ0_MASK_buck_scp_mk_START   (7)
#define SOC_SCHARGER_IRQ0_MASK_buck_scp_mk_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_IRQ1_MASK_UNION
 �ṹ˵��  : IRQ1_MASK �Ĵ����ṹ���塣��ַƫ����:0x11����ֵ:0x10�����:8
 �Ĵ���˵��: �ж�����1�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  regn_ocp_mk       : 1;  /* bit[0]: 0��ʹ�ܸ��жϣ�(Ĭ�ϲ�����)
                                                          1�����θ��жϡ� */
        unsigned char  vbat_ovp_mk       : 1;  /* bit[1]: 0��ʹ�ܸ��жϣ�(Ĭ�ϲ�����)
                                                          1�����θ��жϡ� */
        unsigned char  vbus_uvp_mk       : 1;  /* bit[2]: 0��ʹ�ܸ��жϣ�(Ĭ�ϲ�����)
                                                          1�����θ��жϡ� */
        unsigned char  vbus_ovp_mk       : 1;  /* bit[3]: 0��ʹ�ܸ��жϣ�(Ĭ�ϲ�����)
                                                          1�����θ��жϡ� */
        unsigned char  sys_ocp_mk        : 1;  /* bit[4]: 0��ʹ�ܸ��жϣ�
                                                          1�����θ��жϡ�(Ĭ������) */
        unsigned char  chg_fast_fault_mk : 1;  /* bit[5]: 0��ʹ�ܸ��жϣ�(Ĭ�ϲ�����)
                                                          1�����θ��жϡ� */
        unsigned char  chg_pre_fault_mk  : 1;  /* bit[6]: 0��ʹ�ܸ��жϣ�(Ĭ�ϲ�����)
                                                          1�����θ��жϡ� */
        unsigned char  chg_tri_fault_mk  : 1;  /* bit[7]: 0��ʹ�ܸ��жϣ�(Ĭ�ϲ�����)
                                                          1�����θ��жϡ� */
    } reg;
} SOC_SCHARGER_IRQ1_MASK_UNION;
#endif
#define SOC_SCHARGER_IRQ1_MASK_regn_ocp_mk_START        (0)
#define SOC_SCHARGER_IRQ1_MASK_regn_ocp_mk_END          (0)
#define SOC_SCHARGER_IRQ1_MASK_vbat_ovp_mk_START        (1)
#define SOC_SCHARGER_IRQ1_MASK_vbat_ovp_mk_END          (1)
#define SOC_SCHARGER_IRQ1_MASK_vbus_uvp_mk_START        (2)
#define SOC_SCHARGER_IRQ1_MASK_vbus_uvp_mk_END          (2)
#define SOC_SCHARGER_IRQ1_MASK_vbus_ovp_mk_START        (3)
#define SOC_SCHARGER_IRQ1_MASK_vbus_ovp_mk_END          (3)
#define SOC_SCHARGER_IRQ1_MASK_sys_ocp_mk_START         (4)
#define SOC_SCHARGER_IRQ1_MASK_sys_ocp_mk_END           (4)
#define SOC_SCHARGER_IRQ1_MASK_chg_fast_fault_mk_START  (5)
#define SOC_SCHARGER_IRQ1_MASK_chg_fast_fault_mk_END    (5)
#define SOC_SCHARGER_IRQ1_MASK_chg_pre_fault_mk_START   (6)
#define SOC_SCHARGER_IRQ1_MASK_chg_pre_fault_mk_END     (6)
#define SOC_SCHARGER_IRQ1_MASK_chg_tri_fault_mk_START   (7)
#define SOC_SCHARGER_IRQ1_MASK_chg_tri_fault_mk_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_IRQ2_MASK_UNION
 �ṹ˵��  : IRQ2_MASK �Ĵ����ṹ���塣��ַƫ����:0x12����ֵ:0x00�����:8
 �Ĵ���˵��: �ж�����2�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  bat_ltmp_mk : 1;  /* bit[0]  : 0��ʹ�ܸ��жϣ�(Ĭ�ϲ�����)
                                                      1�����θ��жϡ� */
        unsigned char  bat_htmp_mk : 1;  /* bit[1]  : 0��ʹ�ܸ��жϣ�(Ĭ�ϲ�����)
                                                      1�����θ��жϡ� */
        unsigned char  reserved    : 6;  /* bit[2-7]: ������ */
    } reg;
} SOC_SCHARGER_IRQ2_MASK_UNION;
#endif
#define SOC_SCHARGER_IRQ2_MASK_bat_ltmp_mk_START  (0)
#define SOC_SCHARGER_IRQ2_MASK_bat_ltmp_mk_END    (0)
#define SOC_SCHARGER_IRQ2_MASK_bat_htmp_mk_START  (1)
#define SOC_SCHARGER_IRQ2_MASK_bat_htmp_mk_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_WATCHDOG_IRQ_MASK_UNION
 �ṹ˵��  : WATCHDOG_IRQ_MASK �Ĵ����ṹ���塣��ַƫ����:0x13����ֵ:0x00�����:8
 �Ĵ���˵��: ���Ź��ж����μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  wdt_irq_mk : 1;  /* bit[0]  : 0��ʹ�ܸ��жϣ�
                                                     1�����θ��жϡ� */
        unsigned char  reserved   : 7;  /* bit[1-7]: ������ */
    } reg;
} SOC_SCHARGER_WATCHDOG_IRQ_MASK_UNION;
#endif
#define SOC_SCHARGER_WATCHDOG_IRQ_MASK_wdt_irq_mk_START  (0)
#define SOC_SCHARGER_WATCHDOG_IRQ_MASK_wdt_irq_mk_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_STATUIS_UNION
 �ṹ˵��  : STATUIS �Ĵ����ṹ���塣��ַƫ����:0x20����ֵ:0x00�����:8
 �Ĵ���˵��: fcp slave ����״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  attach   : 1;  /* bit[0]  : 0����⵽װ��δ���룻
                                                   1����⵽װ�ò��� */
        unsigned char  reserved : 5;  /* bit[1-5]: ������ */
        unsigned char  dvc      : 2;  /* bit[6-7]: 00�����û�п�ʼ�������ڼ��״̬��
                                                   01����⵽��ЧFCP slave��
                                                   10��������
                                                   11����⵽FCP slave�� */
    } reg;
} SOC_SCHARGER_STATUIS_UNION;
#endif
#define SOC_SCHARGER_STATUIS_attach_START    (0)
#define SOC_SCHARGER_STATUIS_attach_END      (0)
#define SOC_SCHARGER_STATUIS_dvc_START       (6)
#define SOC_SCHARGER_STATUIS_dvc_END         (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_CNTL_UNION
 �ṹ˵��  : CNTL �Ĵ����ṹ���塣��ַƫ����:0x21����ֵ:0x00�����:8
 �Ĵ���˵��: XXXX��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sndcmd   : 1;  /* bit[0]  : fcp master transaction ��ʼ���ƼĴ����� */
        unsigned char  reserved_0: 1;  /* bit[1]  : ������ */
        unsigned char  mstr_rst : 1;  /* bit[2]  : fcp master ����slave��λ�Ĵ����� */
        unsigned char  enable   : 1;  /* bit[3]  : fcp ʹ�ܿ��ƼĴ����� */
        unsigned char  reserved_1: 4;  /* bit[4-7]: ������ */
    } reg;
} SOC_SCHARGER_CNTL_UNION;
#endif
#define SOC_SCHARGER_CNTL_sndcmd_START    (0)
#define SOC_SCHARGER_CNTL_sndcmd_END      (0)
#define SOC_SCHARGER_CNTL_mstr_rst_START  (2)
#define SOC_SCHARGER_CNTL_mstr_rst_END    (2)
#define SOC_SCHARGER_CNTL_enable_START    (3)
#define SOC_SCHARGER_CNTL_enable_END      (3)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_CMD_UNION
 �ṹ˵��  : CMD �Ĵ����ṹ���塣��ַƫ����:0x24����ֵ:0x00�����:8
 �Ĵ���˵��: fcp ��д�������üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cmd : 8;  /* bit[0-7]: fcp ��д�������üĴ����� */
    } reg;
} SOC_SCHARGER_CMD_UNION;
#endif
#define SOC_SCHARGER_CMD_cmd_START  (0)
#define SOC_SCHARGER_CMD_cmd_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_ADDR_UNION
 �ṹ˵��  : ADDR �Ĵ����ṹ���塣��ַƫ����:0x27����ֵ:0x00�����:8
 �Ĵ���˵��: fcp ��д��ַ���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  addr : 8;  /* bit[0-7]: fcp ��д��ַ���üĴ����� */
    } reg;
} SOC_SCHARGER_ADDR_UNION;
#endif
#define SOC_SCHARGER_ADDR_addr_START  (0)
#define SOC_SCHARGER_ADDR_addr_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_DATA0_UNION
 �ṹ˵��  : DATA0 �Ĵ����ṹ���塣��ַƫ����:0x28����ֵ:0x00�����:8
 �Ĵ���˵��: fcp д���ݼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  data0 : 8;  /* bit[0-7]: fcp д���ݼĴ����� */
    } reg;
} SOC_SCHARGER_DATA0_UNION;
#endif
#define SOC_SCHARGER_DATA0_data0_START  (0)
#define SOC_SCHARGER_DATA0_data0_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_ISR1_UNION
 �ṹ˵��  : ISR1 �Ĵ����ṹ���塣��ַƫ����:0x39����ֵ:0x00�����:8
 �Ĵ���˵��: FCP �ж�1�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reserved_0: 3;  /* bit[0-2]: ������ */
        unsigned char  crcpar   : 1;  /* bit[3]  : Slaverû�����ݰ������жϣ�
                                                   0���޴��жϣ�
                                                   1�����жϡ� */
        unsigned char  nack     : 1;  /* bit[4]  : Slaver ����NACK�жϣ�
                                                   0���޴��жϣ�
                                                   1�����жϡ� */
        unsigned char  reserved_1: 1;  /* bit[5]  : ������ */
        unsigned char  ack      : 1;  /* bit[6]  : Slaver ����ACK�жϣ�
                                                   0���޴��жϣ�
                                                   1�����жϡ� */
        unsigned char  cmdcpl   : 1;  /* bit[7]  : FCP����ɹ�����жϣ�
                                                   0���޴��жϣ�
                                                   1�����жϡ� */
    } reg;
} SOC_SCHARGER_ISR1_UNION;
#endif
#define SOC_SCHARGER_ISR1_crcpar_START    (3)
#define SOC_SCHARGER_ISR1_crcpar_END      (3)
#define SOC_SCHARGER_ISR1_nack_START      (4)
#define SOC_SCHARGER_ISR1_nack_END        (4)
#define SOC_SCHARGER_ISR1_ack_START       (6)
#define SOC_SCHARGER_ISR1_ack_END         (6)
#define SOC_SCHARGER_ISR1_cmdcpl_START    (7)
#define SOC_SCHARGER_ISR1_cmdcpl_END      (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_ISR2_UNION
 �ṹ˵��  : ISR2 �Ĵ����ṹ���塣��ַƫ����:0x3A����ֵ:0x00�����:8
 �Ĵ���˵��: FCP �ж�2�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reserved_0: 1;  /* bit[0]  : ������ */
        unsigned char  protstat : 1;  /* bit[1]  : Slaver���״̬�仯�жϣ�
                                                   0���޴��жϣ�
                                                   1�����жϡ� */
        unsigned char  reserved_1: 1;  /* bit[2]  : ������ */
        unsigned char  parrx    : 1;  /* bit[3]  : Slaver��������parityУ������жϣ�
                                                   0���޴��жϣ�
                                                   1�����жϡ� */
        unsigned char  crcrx    : 1;  /* bit[4]  : Slaver��������crcУ������жϣ�
                                                   0���޴��жϣ�
                                                   1�����жϡ� */
        unsigned char  reserved_2: 3;  /* bit[5-7]: ������ */
    } reg;
} SOC_SCHARGER_ISR2_UNION;
#endif
#define SOC_SCHARGER_ISR2_protstat_START  (1)
#define SOC_SCHARGER_ISR2_protstat_END    (1)
#define SOC_SCHARGER_ISR2_parrx_START     (3)
#define SOC_SCHARGER_ISR2_parrx_END       (3)
#define SOC_SCHARGER_ISR2_crcrx_START     (4)
#define SOC_SCHARGER_ISR2_crcrx_END       (4)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_IMR1_UNION
 �ṹ˵��  : IMR1 �Ĵ����ṹ���塣��ַƫ����:0x3B����ֵ:0x00�����:8
 �Ĵ���˵��: FCP �ж�����1�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reserved_0: 3;  /* bit[0-2]: ������ */
        unsigned char  crcpar_mk : 1;  /* bit[3]  : crcpar�ж����μĴ�����
                                                    0�������Σ�
                                                    1�����Ρ� */
        unsigned char  nack_mk   : 1;  /* bit[4]  : nack�ж����μĴ�����
                                                    0�������Σ�
                                                    1�����Ρ� */
        unsigned char  reserved_1: 1;  /* bit[5]  : ������ */
        unsigned char  ack_mk    : 1;  /* bit[6]  : ack�ж����μĴ�����
                                                    0�������Σ�
                                                    1�����Ρ� */
        unsigned char  cmdcpl_mk : 1;  /* bit[7]  : cmdcpl�ж����μĴ�����
                                                    0�������Σ�
                                                    1�����Ρ� */
    } reg;
} SOC_SCHARGER_IMR1_UNION;
#endif
#define SOC_SCHARGER_IMR1_crcpar_mk_START  (3)
#define SOC_SCHARGER_IMR1_crcpar_mk_END    (3)
#define SOC_SCHARGER_IMR1_nack_mk_START    (4)
#define SOC_SCHARGER_IMR1_nack_mk_END      (4)
#define SOC_SCHARGER_IMR1_ack_mk_START     (6)
#define SOC_SCHARGER_IMR1_ack_mk_END       (6)
#define SOC_SCHARGER_IMR1_cmdcpl_mk_START  (7)
#define SOC_SCHARGER_IMR1_cmdcpl_mk_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_IMR2_UNION
 �ṹ˵��  : IMR2 �Ĵ����ṹ���塣��ַƫ����:0x3C����ֵ:0x00�����:8
 �Ĵ���˵��: FCP �ж�����2�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reserved_0  : 1;  /* bit[0]  : ������ */
        unsigned char  protstat_mk : 1;  /* bit[1]  : protstat�ж����μĴ�����
                                                      0�������Σ�
                                                      1�����Ρ� */
        unsigned char  reserved_1  : 1;  /* bit[2]  : ������ */
        unsigned char  parrx_mk    : 1;  /* bit[3]  : parrx�ж����μĴ�����
                                                      0�������Σ�
                                                      1�����Ρ� */
        unsigned char  crcrx_mk    : 1;  /* bit[4]  : crcrx�ж����μĴ�����
                                                      0�������Σ�
                                                      1�����Ρ� */
        unsigned char  reserved_2  : 3;  /* bit[5-7]: ������ */
    } reg;
} SOC_SCHARGER_IMR2_UNION;
#endif
#define SOC_SCHARGER_IMR2_protstat_mk_START  (1)
#define SOC_SCHARGER_IMR2_protstat_mk_END    (1)
#define SOC_SCHARGER_IMR2_parrx_mk_START     (3)
#define SOC_SCHARGER_IMR2_parrx_mk_END       (3)
#define SOC_SCHARGER_IMR2_crcrx_mk_START     (4)
#define SOC_SCHARGER_IMR2_crcrx_mk_END       (4)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_FCP_IRQ3_UNION
 �ṹ˵��  : FCP_IRQ3 �Ĵ����ṹ���塣��ַƫ����:0x3D����ֵ:0x00�����:8
 �Ĵ���˵��: FCP�ж�3�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  last_hand_fail_irq  : 1;  /* bit[0]: ���ݰ������������ʧ���жϣ�
                                                            0���޴��жϣ�
                                                            1�����жϡ� */
        unsigned char  tail_hand_fail_irq  : 1;  /* bit[1]: Slaver �������ݺ��һ�η���ping����ʧ���жϣ�
                                                            0���޴��жϣ�
                                                            1�����жϡ� */
        unsigned char  trans_hand_fail_irq : 1;  /* bit[2]: Master�������ݺ�����ʧ���жϣ�
                                                            0���޴��жϣ�
                                                            1�����жϡ� */
        unsigned char  init_hand_fail_irq  : 1;  /* bit[3]: ��ʼ������ʧ���жϣ�
                                                            0���޴��жϣ�
                                                            1�����жϡ� */
        unsigned char  rx_data_det_irq     : 1;  /* bit[4]: �Ȳ���slaver���ص������жϣ�
                                                            0���޴��жϣ�
                                                            1�����жϡ� */
        unsigned char  rx_head_det_irq     : 1;  /* bit[5]: �Ȳ���slaver���ص����ݰ�ͷ�жϣ�
                                                            0���޴��жϣ�
                                                            1�����жϡ� */
        unsigned char  cmd_err_irq         : 1;  /* bit[6]: SNDCMD��Ϊ������д�жϣ�
                                                            0���޴��жϣ�
                                                            1�����жϡ� */
        unsigned char  reserved            : 1;  /* bit[7]:  */
    } reg;
} SOC_SCHARGER_FCP_IRQ3_UNION;
#endif
#define SOC_SCHARGER_FCP_IRQ3_last_hand_fail_irq_START   (0)
#define SOC_SCHARGER_FCP_IRQ3_last_hand_fail_irq_END     (0)
#define SOC_SCHARGER_FCP_IRQ3_tail_hand_fail_irq_START   (1)
#define SOC_SCHARGER_FCP_IRQ3_tail_hand_fail_irq_END     (1)
#define SOC_SCHARGER_FCP_IRQ3_trans_hand_fail_irq_START  (2)
#define SOC_SCHARGER_FCP_IRQ3_trans_hand_fail_irq_END    (2)
#define SOC_SCHARGER_FCP_IRQ3_init_hand_fail_irq_START   (3)
#define SOC_SCHARGER_FCP_IRQ3_init_hand_fail_irq_END     (3)
#define SOC_SCHARGER_FCP_IRQ3_rx_data_det_irq_START      (4)
#define SOC_SCHARGER_FCP_IRQ3_rx_data_det_irq_END        (4)
#define SOC_SCHARGER_FCP_IRQ3_rx_head_det_irq_START      (5)
#define SOC_SCHARGER_FCP_IRQ3_rx_head_det_irq_END        (5)
#define SOC_SCHARGER_FCP_IRQ3_cmd_err_irq_START          (6)
#define SOC_SCHARGER_FCP_IRQ3_cmd_err_irq_END            (6)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_FCP_IRQ4_UNION
 �ṹ˵��  : FCP_IRQ4 �Ĵ����ṹ���塣��ַƫ����:0x3E����ֵ:0x00�����:8
 �Ĵ���˵��: FCP�ж�4�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  last_hand_no_respond_irq   : 1;  /* bit[0]  : ���ݰ��������Ȳ���slaver ping�жϣ�
                                                                     0���޴��жϣ�
                                                                     1�����жϡ� */
        unsigned char  tail_hand_no_respond_irq   : 1;  /* bit[1]  : Slaver �������ݺ��һ�η���ping���ֵȲ���slaver ping�жϣ�
                                                                     0���޴��жϣ�
                                                                     1�����жϡ� */
        unsigned char  trans_hand_no_respond_irq  : 1;  /* bit[2]  : Master�������ݺ����ֵȲ���slaver ping�жϣ�
                                                                     0���޴��жϣ�
                                                                     1�����жϡ� */
        unsigned char  init_hand_no_respond_irq   : 1;  /* bit[3]  : ��ʼ��slaverû��ping�����жϣ�
                                                                     0���޴��жϣ�
                                                                     1�����жϡ� */
        unsigned char  enable_hand_fail_irq       : 1;  /* bit[4]  : ͨ��enable����master ping������ʧ�ܣ�����ʧ�ܻ��Զ��ظ�����15�Σ���
                                                                     0���޴��жϣ�
                                                                     1�����жϡ� */
        unsigned char  enable_hand_no_respond_irq : 1;  /* bit[5]  : ͨ��enable����master ping��slaverû����Ӧ�жϣ�����ʧ�ܻ��Զ��ظ�����15�Σ���
                                                                     0���޴��жϣ�
                                                                     1�����жϡ� */
        unsigned char  reserved                   : 2;  /* bit[6-7]: ������ */
    } reg;
} SOC_SCHARGER_FCP_IRQ4_UNION;
#endif
#define SOC_SCHARGER_FCP_IRQ4_last_hand_no_respond_irq_START    (0)
#define SOC_SCHARGER_FCP_IRQ4_last_hand_no_respond_irq_END      (0)
#define SOC_SCHARGER_FCP_IRQ4_tail_hand_no_respond_irq_START    (1)
#define SOC_SCHARGER_FCP_IRQ4_tail_hand_no_respond_irq_END      (1)
#define SOC_SCHARGER_FCP_IRQ4_trans_hand_no_respond_irq_START   (2)
#define SOC_SCHARGER_FCP_IRQ4_trans_hand_no_respond_irq_END     (2)
#define SOC_SCHARGER_FCP_IRQ4_init_hand_no_respond_irq_START    (3)
#define SOC_SCHARGER_FCP_IRQ4_init_hand_no_respond_irq_END      (3)
#define SOC_SCHARGER_FCP_IRQ4_enable_hand_fail_irq_START        (4)
#define SOC_SCHARGER_FCP_IRQ4_enable_hand_fail_irq_END          (4)
#define SOC_SCHARGER_FCP_IRQ4_enable_hand_no_respond_irq_START  (5)
#define SOC_SCHARGER_FCP_IRQ4_enable_hand_no_respond_irq_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_FCP_IRQ5_UNION
 �ṹ˵��  : FCP_IRQ5 �Ĵ����ṹ���塣��ַƫ����:0x3F����ֵ:0x00�����:8
 �Ĵ���˵��: FCP�ж�5�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  fcp_set_d60m_r : 1;  /* bit[0]  : ֧�ָ�ѹ����Adapter�жϣ�fcp_set�˲�60ms����������أ��ϱ��жϣ���
                                                         0���޴��жϣ�
                                                         1�����жϡ�
                                                         ע����fcp_cmp_en=0ʱ��ģ���ͳ���fcp_set�ź���0�ġ� */
        unsigned char  fcp_en_det_int : 1;  /* bit[1]  : fcp_det_en&amp;fcp_cmp_en�ź�Ϊ�ߵ�ƽ��2s�ڣ�û���յ�fcp_set�������жϣ�
                                                         0���޴��жϣ�
                                                         1�����жϡ� */
        unsigned char  reserved       : 6;  /* bit[2-7]: ������ */
    } reg;
} SOC_SCHARGER_FCP_IRQ5_UNION;
#endif
#define SOC_SCHARGER_FCP_IRQ5_fcp_set_d60m_r_START  (0)
#define SOC_SCHARGER_FCP_IRQ5_fcp_set_d60m_r_END    (0)
#define SOC_SCHARGER_FCP_IRQ5_fcp_en_det_int_START  (1)
#define SOC_SCHARGER_FCP_IRQ5_fcp_en_det_int_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_FCP_IRQ3_MASK_UNION
 �ṹ˵��  : FCP_IRQ3_MASK �Ĵ����ṹ���塣��ַƫ����:0x40����ֵ:0x00�����:8
 �Ĵ���˵��: FCP�ж�����3�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  last_hand_fail_irq_mk  : 1;  /* bit[0]: 0��ʹ�ܸ��жϣ�
                                                               1�����θ��жϡ� */
        unsigned char  tail_hand_fail_irq_mk  : 1;  /* bit[1]: 0��ʹ�ܸ��жϣ�
                                                               1�����θ��жϡ� */
        unsigned char  trans_hand_fail_irq_mk : 1;  /* bit[2]: 0��ʹ�ܸ��жϣ�
                                                               1�����θ��жϡ� */
        unsigned char  init_hand_fail_irq_mk  : 1;  /* bit[3]: 0��ʹ�ܸ��жϣ�
                                                               1�����θ��жϡ� */
        unsigned char  rx_data_det_irq_mk     : 1;  /* bit[4]: 0��ʹ�ܸ��жϣ�
                                                               1�����θ��жϡ� */
        unsigned char  rx_head_det_irq_mk     : 1;  /* bit[5]: 0��ʹ�ܸ��жϣ�
                                                               1�����θ��жϡ� */
        unsigned char  cmd_err_irq_mk         : 1;  /* bit[6]: 0��ʹ�ܸ��жϣ�
                                                               1�����θ��жϡ� */
        unsigned char  reserved               : 1;  /* bit[7]: ������ */
    } reg;
} SOC_SCHARGER_FCP_IRQ3_MASK_UNION;
#endif
#define SOC_SCHARGER_FCP_IRQ3_MASK_last_hand_fail_irq_mk_START   (0)
#define SOC_SCHARGER_FCP_IRQ3_MASK_last_hand_fail_irq_mk_END     (0)
#define SOC_SCHARGER_FCP_IRQ3_MASK_tail_hand_fail_irq_mk_START   (1)
#define SOC_SCHARGER_FCP_IRQ3_MASK_tail_hand_fail_irq_mk_END     (1)
#define SOC_SCHARGER_FCP_IRQ3_MASK_trans_hand_fail_irq_mk_START  (2)
#define SOC_SCHARGER_FCP_IRQ3_MASK_trans_hand_fail_irq_mk_END    (2)
#define SOC_SCHARGER_FCP_IRQ3_MASK_init_hand_fail_irq_mk_START   (3)
#define SOC_SCHARGER_FCP_IRQ3_MASK_init_hand_fail_irq_mk_END     (3)
#define SOC_SCHARGER_FCP_IRQ3_MASK_rx_data_det_irq_mk_START      (4)
#define SOC_SCHARGER_FCP_IRQ3_MASK_rx_data_det_irq_mk_END        (4)
#define SOC_SCHARGER_FCP_IRQ3_MASK_rx_head_det_irq_mk_START      (5)
#define SOC_SCHARGER_FCP_IRQ3_MASK_rx_head_det_irq_mk_END        (5)
#define SOC_SCHARGER_FCP_IRQ3_MASK_cmd_err_irq_mk_START          (6)
#define SOC_SCHARGER_FCP_IRQ3_MASK_cmd_err_irq_mk_END            (6)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_FCP_IRQ4_MASK_UNION
 �ṹ˵��  : FCP_IRQ4_MASK �Ĵ����ṹ���塣��ַƫ����:0x41����ֵ:0x00�����:8
 �Ĵ���˵��: FCP�ж�����4�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  last_hand_no_respond_irq_mk   : 1;  /* bit[0]  : 0��ʹ�ܸ��жϣ�
                                                                        1�����θ��жϡ� */
        unsigned char  tail_hand_no_respond_irq_mk   : 1;  /* bit[1]  : 0��ʹ�ܸ��жϣ�
                                                                        1�����θ��жϡ� */
        unsigned char  trans_hand_no_respond_irq_mk  : 1;  /* bit[2]  : 0��ʹ�ܸ��жϣ�
                                                                        1�����θ��жϡ� */
        unsigned char  init_hand_no_respond_irq_mk   : 1;  /* bit[3]  : 0��ʹ�ܸ��жϣ�
                                                                        1�����θ��жϡ� */
        unsigned char  enable_hand_fail_irq_mk       : 1;  /* bit[4]  : 0��ʹ�ܸ��жϣ�
                                                                        1�����θ��жϡ� */
        unsigned char  enable_hand_no_respond_irq_mk : 1;  /* bit[5]  : 0��ʹ�ܸ��жϣ�
                                                                        1�����θ��жϡ� */
        unsigned char  reserved                      : 2;  /* bit[6-7]: ������ */
    } reg;
} SOC_SCHARGER_FCP_IRQ4_MASK_UNION;
#endif
#define SOC_SCHARGER_FCP_IRQ4_MASK_last_hand_no_respond_irq_mk_START    (0)
#define SOC_SCHARGER_FCP_IRQ4_MASK_last_hand_no_respond_irq_mk_END      (0)
#define SOC_SCHARGER_FCP_IRQ4_MASK_tail_hand_no_respond_irq_mk_START    (1)
#define SOC_SCHARGER_FCP_IRQ4_MASK_tail_hand_no_respond_irq_mk_END      (1)
#define SOC_SCHARGER_FCP_IRQ4_MASK_trans_hand_no_respond_irq_mk_START   (2)
#define SOC_SCHARGER_FCP_IRQ4_MASK_trans_hand_no_respond_irq_mk_END     (2)
#define SOC_SCHARGER_FCP_IRQ4_MASK_init_hand_no_respond_irq_mk_START    (3)
#define SOC_SCHARGER_FCP_IRQ4_MASK_init_hand_no_respond_irq_mk_END      (3)
#define SOC_SCHARGER_FCP_IRQ4_MASK_enable_hand_fail_irq_mk_START        (4)
#define SOC_SCHARGER_FCP_IRQ4_MASK_enable_hand_fail_irq_mk_END          (4)
#define SOC_SCHARGER_FCP_IRQ4_MASK_enable_hand_no_respond_irq_mk_START  (5)
#define SOC_SCHARGER_FCP_IRQ4_MASK_enable_hand_no_respond_irq_mk_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_FCP_IRQ5_MASK_UNION
 �ṹ˵��  : FCP_IRQ5_MASK �Ĵ����ṹ���塣��ַƫ����:0x42����ֵ:0x00�����:8
 �Ĵ���˵��: FCP�ж�����5�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  fcp_set_d60m_r_mk : 1;  /* bit[0]  : 0��ʹ�ܸ��жϣ�
                                                            1�����θ��жϡ� */
        unsigned char  fcp_en_det_int_mk : 1;  /* bit[1]  : 0��ʹ�ܸ��жϣ�
                                                            1�����θ��жϡ� */
        unsigned char  reserved          : 6;  /* bit[2-7]: ������ */
    } reg;
} SOC_SCHARGER_FCP_IRQ5_MASK_UNION;
#endif
#define SOC_SCHARGER_FCP_IRQ5_MASK_fcp_set_d60m_r_mk_START  (0)
#define SOC_SCHARGER_FCP_IRQ5_MASK_fcp_set_d60m_r_mk_END    (0)
#define SOC_SCHARGER_FCP_IRQ5_MASK_fcp_en_det_int_mk_START  (1)
#define SOC_SCHARGER_FCP_IRQ5_MASK_fcp_en_det_int_mk_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_FCP_CTRL_UNION
 �ṹ˵��  : FCP_CTRL �Ĵ����ṹ���塣��ַƫ����:0x43����ֵ:0x00�����:8
 �Ĵ���˵��: ��ѹ�����ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  fcp_clk_test : 1;  /* bit[0]  : ��ѹ���Ĳ���ģʽѡ��
                                                       0����������ģʽ��
                                                       1������ģʽ�� */
        unsigned char  fcp_mode     : 1;  /* bit[1]  : ��ѹ���ģʽѡ��
                                                       0��ģʽ1��
                                                       1��ģʽ2�� */
        unsigned char  fcp_cmp_en   : 1;  /* bit[2]  : ��ѹ���Э����Ƚ���ʹ�ܣ�
                                                       0���رռ��Ƚ�����
                                                       1�����Ƚ�����
                                                       ��ע�����Ź������쳣��üĴ����ᱻ��0���� */
        unsigned char  fcp_det_en   : 1;  /* bit[3]  : ��ѹ���Э����ʹ�ܣ�
                                                       0���رտ��Э���⹦�ܣ�
                                                       1���������Э���⹦�ܡ�
                                                       ��ע�����Ź������쳣��üĴ����ᱻ��0���� */
        unsigned char  reserved     : 4;  /* bit[4-7]: ������ */
    } reg;
} SOC_SCHARGER_FCP_CTRL_UNION;
#endif
#define SOC_SCHARGER_FCP_CTRL_fcp_clk_test_START  (0)
#define SOC_SCHARGER_FCP_CTRL_fcp_clk_test_END    (0)
#define SOC_SCHARGER_FCP_CTRL_fcp_mode_START      (1)
#define SOC_SCHARGER_FCP_CTRL_fcp_mode_END        (1)
#define SOC_SCHARGER_FCP_CTRL_fcp_cmp_en_START    (2)
#define SOC_SCHARGER_FCP_CTRL_fcp_cmp_en_END      (2)
#define SOC_SCHARGER_FCP_CTRL_fcp_det_en_START    (3)
#define SOC_SCHARGER_FCP_CTRL_fcp_det_en_END      (3)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_FCP_MODE2_SET_UNION
 �ṹ˵��  : FCP_MODE2_SET �Ĵ����ṹ���塣��ַƫ����:0x44����ֵ:0x00�����:8
 �Ĵ���˵��: ��ѹ���Э��ģʽ2��λ���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  fcp_mod2_set : 2;  /* bit[0-1]: ��ѹ���Э��ģʽ2��λ���ƣ�
                                                       00����0.6V,0V)
                                                       01: (3.3V,0.6V)
                                                       10: (0.6V,0.6V)
                                                       11: (3.3V,3.3V) */
        unsigned char  reserved     : 6;  /* bit[2-7]: ������ */
    } reg;
} SOC_SCHARGER_FCP_MODE2_SET_UNION;
#endif
#define SOC_SCHARGER_FCP_MODE2_SET_fcp_mod2_set_START  (0)
#define SOC_SCHARGER_FCP_MODE2_SET_fcp_mod2_set_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_FCP_ADAP_CTRL_UNION
 �ṹ˵��  : FCP_ADAP_CTRL �Ĵ����ṹ���塣��ַƫ����:0x45����ֵ:0x00�����:8
 �Ĵ���˵��: ��ѹ���Adapter���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  fcp_set_d60m_r : 1;  /* bit[0]  : ��ѹ����Adapter�жϣ�fcp_set_d60m_r�ж�״̬�Ĵ�������
                                                         0����֧�ָ�ѹ����Adapter��
                                                         1��֧�ָ�ѹ����Adapter�� */
        unsigned char  reserved       : 7;  /* bit[1-7]: ������ */
    } reg;
} SOC_SCHARGER_FCP_ADAP_CTRL_UNION;
#endif
#define SOC_SCHARGER_FCP_ADAP_CTRL_fcp_set_d60m_r_START  (0)
#define SOC_SCHARGER_FCP_ADAP_CTRL_fcp_set_d60m_r_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_MSTATE_UNION
 �ṹ˵��  : MSTATE �Ĵ����ṹ���塣��ַƫ����:0x46����ֵ:0x00�����:8
 �Ĵ���˵��: ״̬��״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  mstate   : 4;  /* bit[0-3]: FCP״̬��״̬�Ĵ����� */
        unsigned char  reserved : 4;  /* bit[4-7]: ������ */
    } reg;
} SOC_SCHARGER_MSTATE_UNION;
#endif
#define SOC_SCHARGER_MSTATE_mstate_START    (0)
#define SOC_SCHARGER_MSTATE_mstate_END      (3)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_FCP_RDATA_UNION
 �ṹ˵��  : FCP_RDATA �Ĵ����ṹ���塣��ַƫ����:0x47����ֵ:0x00�����:8
 �Ĵ���˵��: slave���ص����ݡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  fcp_rdata : 8;  /* bit[0-7]: I2Cͨ��master���ص�slaver�ļĴ���ֵ�� */
    } reg;
} SOC_SCHARGER_FCP_RDATA_UNION;
#endif
#define SOC_SCHARGER_FCP_RDATA_fcp_rdata_START  (0)
#define SOC_SCHARGER_FCP_RDATA_fcp_rdata_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_RDATA_READY_UNION
 �ṹ˵��  : RDATA_READY �Ĵ����ṹ���塣��ַƫ����:0x48����ֵ:0x00�����:8
 �Ĵ���˵��: slave�������ݲɼ���ָʾ�źš�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  fcp_rdata_ready : 1;  /* bit[0]  : I2Cͨ��master���ص�slaver�ļĴ���ֵ׼����ָʾ�źš� */
        unsigned char  reserved        : 7;  /* bit[1-7]: ������ */
    } reg;
} SOC_SCHARGER_RDATA_READY_UNION;
#endif
#define SOC_SCHARGER_RDATA_READY_fcp_rdata_ready_START  (0)
#define SOC_SCHARGER_RDATA_READY_fcp_rdata_ready_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_CRC_ENABLE_UNION
 �ṹ˵��  : CRC_ENABLE �Ĵ����ṹ���塣��ַƫ����:0x49����ֵ:0x01�����:8
 �Ĵ���˵��: crc ʹ�ܿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  crc_en   : 1;  /* bit[0]  : crc ʹ�ܿ��ƼĴ�����
                                                   0����ʹ�ܣ�
                                                   1��ʹ�ܡ� */
        unsigned char  reserved : 7;  /* bit[1-7]: ������ */
    } reg;
} SOC_SCHARGER_CRC_ENABLE_UNION;
#endif
#define SOC_SCHARGER_CRC_ENABLE_crc_en_START    (0)
#define SOC_SCHARGER_CRC_ENABLE_crc_en_END      (0)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_CRC_START_VALUE_UNION
 �ṹ˵��  : CRC_START_VALUE �Ĵ����ṹ���塣��ַƫ����:0x4A����ֵ:0x00�����:8
 �Ĵ���˵��: crc ��ʼֵ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  crc_start_val : 8;  /* bit[0-7]: crc ��ʼֵ�� */
    } reg;
} SOC_SCHARGER_CRC_START_VALUE_UNION;
#endif
#define SOC_SCHARGER_CRC_START_VALUE_crc_start_val_START  (0)
#define SOC_SCHARGER_CRC_START_VALUE_crc_start_val_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_SAMPLE_CNT_ADJ_UNION
 �ṹ˵��  : SAMPLE_CNT_ADJ �Ĵ����ṹ���塣��ַƫ����:0x4B����ֵ:0x00�����:8
 �Ĵ���˵��: ����������Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sample_cnt_adjust : 5;  /* bit[0-4]: ����slaver���������ֶ����ڼĴ�����Ϊ0ʱ��������Ϊ����slaver ping���ȵó�������������ֵʱ���������ھ�Ϊ����ֵ��
                                                            ע�������õ����ֵΪ28��5'b11100�� */
        unsigned char  reserved          : 3;  /* bit[5-7]: ������ */
    } reg;
} SOC_SCHARGER_SAMPLE_CNT_ADJ_UNION;
#endif
#define SOC_SCHARGER_SAMPLE_CNT_ADJ_sample_cnt_adjust_START  (0)
#define SOC_SCHARGER_SAMPLE_CNT_ADJ_sample_cnt_adjust_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_RX_PING_WIDTH_MIN_H_UNION
 �ṹ˵��  : RX_PING_WIDTH_MIN_H �Ĵ����ṹ���塣��ַƫ����:0x4C����ֵ:0x01�����:8
 �Ĵ���˵��: RX ping ��С���ȸ�λ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rx_ping_width_min_h : 1;  /* bit[0]  : Slaver ping�����Ч���ȸ�λ�� */
        unsigned char  reserved            : 7;  /* bit[1-7]: ������ */
    } reg;
} SOC_SCHARGER_RX_PING_WIDTH_MIN_H_UNION;
#endif
#define SOC_SCHARGER_RX_PING_WIDTH_MIN_H_rx_ping_width_min_h_START  (0)
#define SOC_SCHARGER_RX_PING_WIDTH_MIN_H_rx_ping_width_min_h_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_RX_PING_WIDTH_MIN_L_UNION
 �ṹ˵��  : RX_PING_WIDTH_MIN_L �Ĵ����ṹ���塣��ַƫ����:0x4D����ֵ:0x04�����:8
 �Ĵ���˵��: RX ping ��С���ȵ�8λ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rx_ping_width_min_l : 8;  /* bit[0-7]: Slaver ping�����Ч���ȵ�8λ�� */
    } reg;
} SOC_SCHARGER_RX_PING_WIDTH_MIN_L_UNION;
#endif
#define SOC_SCHARGER_RX_PING_WIDTH_MIN_L_rx_ping_width_min_l_START  (0)
#define SOC_SCHARGER_RX_PING_WIDTH_MIN_L_rx_ping_width_min_l_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_RX_PING_WIDTH_MAX_H_UNION
 �ṹ˵��  : RX_PING_WIDTH_MAX_H �Ĵ����ṹ���塣��ַƫ����:0x4E����ֵ:0x01�����:8
 �Ĵ���˵��: RX ping ��󳤶ȸ�λ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rx_ping_width_max_h : 1;  /* bit[0]  : Slaver ping���Ч���ȸ�λ�� */
        unsigned char  reserved            : 7;  /* bit[1-7]: ������ */
    } reg;
} SOC_SCHARGER_RX_PING_WIDTH_MAX_H_UNION;
#endif
#define SOC_SCHARGER_RX_PING_WIDTH_MAX_H_rx_ping_width_max_h_START  (0)
#define SOC_SCHARGER_RX_PING_WIDTH_MAX_H_rx_ping_width_max_h_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_RX_PING_WIDTH_MAX_L_UNION
 �ṹ˵��  : RX_PING_WIDTH_MAX_L �Ĵ����ṹ���塣��ַƫ����:0x4F����ֵ:0x8B�����:8
 �Ĵ���˵��: RX ping ��󳤶ȵ�8λ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rx_ping_width_max_l : 8;  /* bit[0-7]: Slaver ping���Ч���ȵ�8λ�� */
    } reg;
} SOC_SCHARGER_RX_PING_WIDTH_MAX_L_UNION;
#endif
#define SOC_SCHARGER_RX_PING_WIDTH_MAX_L_rx_ping_width_max_l_START  (0)
#define SOC_SCHARGER_RX_PING_WIDTH_MAX_L_rx_ping_width_max_l_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_DATA_WAIT_TIME_UNION
 �ṹ˵��  : DATA_WAIT_TIME �Ĵ����ṹ���塣��ַƫ����:0x50����ֵ:0x64�����:8
 �Ĵ���˵��: ���ݵȴ�ʱ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  data_wait_time : 7;  /* bit[0-6]: ���ݰ��ȴ�����ʱ��Ĵ�����ʵ������Ϊ����ֵ*4 cycle�� */
        unsigned char  reserved       : 1;  /* bit[7]  : ������ */
    } reg;
} SOC_SCHARGER_DATA_WAIT_TIME_UNION;
#endif
#define SOC_SCHARGER_DATA_WAIT_TIME_data_wait_time_START  (0)
#define SOC_SCHARGER_DATA_WAIT_TIME_data_wait_time_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_RETRY_CNT_UNION
 �ṹ˵��  : RETRY_CNT �Ĵ����ṹ���塣��ַƫ����:0x51����ֵ:0x03�����:8
 �Ĵ���˵��: �������·��ʹ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cmd_retry_config : 4;  /* bit[0-3]: ���ݰ�����master retry������ */
        unsigned char  reserved         : 4;  /* bit[4-7]: ������ */
    } reg;
} SOC_SCHARGER_RETRY_CNT_UNION;
#endif
#define SOC_SCHARGER_RETRY_CNT_cmd_retry_config_START  (0)
#define SOC_SCHARGER_RETRY_CNT_cmd_retry_config_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_FCP_SOFT_RST_CTRL_UNION
 �ṹ˵��  : FCP_SOFT_RST_CTRL �Ĵ����ṹ���塣��ַƫ����:0x52����ֵ:0x00�����:8
 �Ĵ���˵��: FCP��λ���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  fcp_soft_rst_cfg : 8;  /* bit[0-7]: FCPģ����λ�źţ�д��0x04���и�λ���Զ����㡣 */
    } reg;
} SOC_SCHARGER_FCP_SOFT_RST_CTRL_UNION;
#endif
#define SOC_SCHARGER_FCP_SOFT_RST_CTRL_fcp_soft_rst_cfg_START  (0)
#define SOC_SCHARGER_FCP_SOFT_RST_CTRL_fcp_soft_rst_cfg_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_FCP_RO_RESERVE_UNION
 �ṹ˵��  : FCP_RO_RESERVE �Ĵ����ṹ���塣��ַƫ����:0x53����ֵ:0x00�����:8
 �Ĵ���˵��: fcpֻ��Ԥ���Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  fcp_ro_reserve : 8;  /* bit[0-7]: fcpֻ��Ԥ���Ĵ����� */
    } reg;
} SOC_SCHARGER_FCP_RO_RESERVE_UNION;
#endif
#define SOC_SCHARGER_FCP_RO_RESERVE_fcp_ro_reserve_START  (0)
#define SOC_SCHARGER_FCP_RO_RESERVE_fcp_ro_reserve_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_FCP_DEBUG_REG0_UNION
 �ṹ˵��  : FCP_DEBUG_REG0 �Ĵ����ṹ���塣��ַƫ����:0x54����ֵ:0x00�����:8
 �Ĵ���˵��: FCP debug�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  slv_crc_err         : 1;  /* bit[0]  : Slaver����crcУ��״̬�� */
        unsigned char  resp_ack_parity_err : 1;  /* bit[1]  : Slaver���ص�ACK/NACK���ݵ�partityУ�顣 */
        unsigned char  rdata_parity_err    : 1;  /* bit[2]  : Slaver���صĶ����ݵ�parityУ�顣 */
        unsigned char  slv_crc_parity_err  : 1;  /* bit[3]  : Slaver���ص�CRC���ݵ�parityУ�顣 */
        unsigned char  reserved            : 4;  /* bit[4-7]: ������ */
    } reg;
} SOC_SCHARGER_FCP_DEBUG_REG0_UNION;
#endif
#define SOC_SCHARGER_FCP_DEBUG_REG0_slv_crc_err_START          (0)
#define SOC_SCHARGER_FCP_DEBUG_REG0_slv_crc_err_END            (0)
#define SOC_SCHARGER_FCP_DEBUG_REG0_resp_ack_parity_err_START  (1)
#define SOC_SCHARGER_FCP_DEBUG_REG0_resp_ack_parity_err_END    (1)
#define SOC_SCHARGER_FCP_DEBUG_REG0_rdata_parity_err_START     (2)
#define SOC_SCHARGER_FCP_DEBUG_REG0_rdata_parity_err_END       (2)
#define SOC_SCHARGER_FCP_DEBUG_REG0_slv_crc_parity_err_START   (3)
#define SOC_SCHARGER_FCP_DEBUG_REG0_slv_crc_parity_err_END     (3)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_FCP_DEBUG_REG1_UNION
 �ṹ˵��  : FCP_DEBUG_REG1 �Ĵ����ṹ���塣��ַƫ����:0x55����ֵ:0x00�����:8
 �Ĵ���˵��: FCP debug�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  resp_ack : 8;  /* bit[0-7]: FCP debug�Ĵ���1��Slaver���ص�ACK/NAC���ݡ� */
    } reg;
} SOC_SCHARGER_FCP_DEBUG_REG1_UNION;
#endif
#define SOC_SCHARGER_FCP_DEBUG_REG1_resp_ack_START  (0)
#define SOC_SCHARGER_FCP_DEBUG_REG1_resp_ack_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_FCP_DEBUG_REG2_UNION
 �ṹ˵��  : FCP_DEBUG_REG2 �Ĵ����ṹ���塣��ַƫ����:0x56����ֵ:0x00�����:8
 �Ĵ���˵��: FCP debug�Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  slv_crc : 8;  /* bit[0-7]: FCP debug�Ĵ���2��Slaver���ص�CRC���ݡ� */
    } reg;
} SOC_SCHARGER_FCP_DEBUG_REG2_UNION;
#endif
#define SOC_SCHARGER_FCP_DEBUG_REG2_slv_crc_START  (0)
#define SOC_SCHARGER_FCP_DEBUG_REG2_slv_crc_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_BUCK_REG0_UNION
 �ṹ˵��  : BUCK_REG0 �Ĵ����ṹ���塣��ַƫ����:0x60����ֵ:0x0A�����:8
 �Ĵ���˵��: BUCK_REG0���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_scp_vset : 2;  /* bit[0-1]: buck scp��λ���ã�
                                                        00��1V��
                                                        01��1.4V��
                                                        10��1.8V��
                                                        11��2.2V�� */
        unsigned char  buck_ilimit   : 5;  /* bit[2-6]: buckƽ���������趨������
                                                        00000��100mA��
                                                        00001��150mA��
                                                        00010��500mA��
                                                        00011��900mA��
                                                        00100��1A��
                                                        00101��1.2A��
                                                        00110��1.3A��
                                                        00111��1.4A��
                                                        01000��1.5A��
                                                        01001��1.6A��
                                                        01010��1.7A��
                                                        01011��1.8A��
                                                        01100��1.9A��
                                                        01101��2A��
                                                        01110��2.1A��
                                                        01111��2.2A��
                                                        10000��2.4A��
                                                        10001��2.6A��
                                                        10010��2.8A��
                                                        10011��3A��
                                                        10100��3.2A��
                                                        10101~11111:3.2A�� */
        unsigned char  reserved      : 1;  /* bit[7]  : ������ */
    } reg;
} SOC_SCHARGER_BUCK_REG0_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG0_buck_scp_vset_START  (0)
#define SOC_SCHARGER_BUCK_REG0_buck_scp_vset_END    (1)
#define SOC_SCHARGER_BUCK_REG0_buck_ilimit_START    (2)
#define SOC_SCHARGER_BUCK_REG0_buck_ilimit_END      (6)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_BUCK_REG1_UNION
 �ṹ˵��  : BUCK_REG1 �Ĵ����ṹ���塣��ַƫ����:0x61����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK_REG1���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_ocp_en_n : 1;  /* bit[0]  : 9/12V�ر�OCP���ܣ�
                                                        0: ���رգ�
                                                        1: �رա� */
        unsigned char  buck_pfm_en   : 1;  /* bit[1]  : pfmģʽʹ�ܿ��ƣ�
                                                        0����ʹ�ܣ�
                                                        1��ʹ�ܡ� */
        unsigned char  buck_scp_dis  : 1;  /* bit[2]  : buck scpʹ�������Σ�
                                                        0�������Σ�
                                                        1�����Ρ� */
        unsigned char  reserved      : 5;  /* bit[3-7]: ������ */
    } reg;
} SOC_SCHARGER_BUCK_REG1_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG1_buck_ocp_en_n_START  (0)
#define SOC_SCHARGER_BUCK_REG1_buck_ocp_en_n_END    (0)
#define SOC_SCHARGER_BUCK_REG1_buck_pfm_en_START    (1)
#define SOC_SCHARGER_BUCK_REG1_buck_pfm_en_END      (1)
#define SOC_SCHARGER_BUCK_REG1_buck_scp_dis_START   (2)
#define SOC_SCHARGER_BUCK_REG1_buck_scp_dis_END     (2)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_BUCK_REG2_UNION
 �ṹ˵��  : BUCK_REG2 �Ĵ����ṹ���塣��ַƫ����:0x62����ֵ:0x2C�����:8
 �Ĵ���˵��: BUCK_REG2���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_ocp_sel    : 2;  /* bit[0-1]: 12V����ʱOCP���Ƿ�����9V�����ϼ�500mA��Ĭ��Ϊ0����500mA��1��ʾ�����ӡ� */
        unsigned char  buck_dpm_sel    : 3;  /* bit[2-4]: DPM�����ѹ�趨��
                                                          000��82.5%��
                                                          001��85%��
                                                          010��87.5%��
                                                          011��90%��
                                                          100��92.5%��
                                                          101��95%�� */
        unsigned char  buck_sysmin_sel : 2;  /* bit[5-6]: Vsys��С�����ѹѡ��
                                                          00��3.4V��
                                                          01��3.5V��
                                                          10��3.6V��
                                                          11��3.7V�� */
        unsigned char  reserved        : 1;  /* bit[7]  : ������ */
    } reg;
} SOC_SCHARGER_BUCK_REG2_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG2_buck_ocp_sel_START     (0)
#define SOC_SCHARGER_BUCK_REG2_buck_ocp_sel_END       (1)
#define SOC_SCHARGER_BUCK_REG2_buck_dpm_sel_START     (2)
#define SOC_SCHARGER_BUCK_REG2_buck_dpm_sel_END       (4)
#define SOC_SCHARGER_BUCK_REG2_buck_sysmin_sel_START  (5)
#define SOC_SCHARGER_BUCK_REG2_buck_sysmin_sel_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_BUCK_REG3_UNION
 �ṹ˵��  : BUCK_REG3 �Ĵ����ṹ���塣��ַƫ����:0x63����ֵ:0x00�����:8
 �Ĵ���˵��: BUCK_REG3���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_gap      : 3;  /* bit[0-2]: buck gap��ѹ�޵��Ĵ������ڣ�
                                                        000��0��
                                                        001��-30mV��
                                                        010��-60mV��
                                                        011��-90mV��
                                                        100��0mV��
                                                        101��+30mV��
                                                        110��+60mV��
                                                        111��+90mV�� */
        unsigned char  buck_ilimit_k : 5;  /* bit[3-7]: buck�����������ڣ�
                                                        00000��0��
                                                        00001��+2.5%��
                                                        00010��+5%��
                                                        00011��+7.5%��
                                                        00100��+10%��
                                                        00101��+12.5%��
                                                        00110��+15%��
                                                        00111��+17.5%��
                                                        01000��+20%��
                                                        01001��+22.5%��
                                                        01010��+25%��
                                                        01011��+27.5%��
                                                        01100��+30%��
                                                        01101��+32.5%��
                                                        01110��+35%��
                                                        01111��+37.5%��
                                                        10000��0��
                                                        10001��-2.5%��
                                                        10010��-5%��
                                                        10011��-7.5%��
                                                        10100��-10%��
                                                        10101��-12.5%��
                                                        10110��-15%��
                                                        10111��-17.5%��
                                                        11000��-20%��
                                                        11001��-22.5%��
                                                        11010��-25%��
                                                        11011��-27.5%��
                                                        11100��-30%��
                                                        11101��-32.5%��
                                                        11110��-35%��
                                                        11111��-37.5%�� */
    } reg;
} SOC_SCHARGER_BUCK_REG3_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG3_buck_gap_START       (0)
#define SOC_SCHARGER_BUCK_REG3_buck_gap_END         (2)
#define SOC_SCHARGER_BUCK_REG3_buck_ilimit_k_START  (3)
#define SOC_SCHARGER_BUCK_REG3_buck_ilimit_k_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_BUCK_REG4_UNION
 �ṹ˵��  : BUCK_REG4 �Ĵ����ṹ���塣��ַƫ����:0x64����ֵ:0x40�����:8
 �Ĵ���˵��: BUCK_REG4���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_osc_otp_reg : 3;  /* bit[0-2]: buck osc trim�ĵ�Ч�Ĵ����� */
        unsigned char  buck_osc_frq     : 4;  /* bit[3-6]: osc����Ƶ�ʵ��ڣ�
                                                           0000��0.7M��
                                                           1111��3M�� */
        unsigned char  reserved         : 1;  /* bit[7]  : ������ */
    } reg;
} SOC_SCHARGER_BUCK_REG4_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG4_buck_osc_otp_reg_START  (0)
#define SOC_SCHARGER_BUCK_REG4_buck_osc_otp_reg_END    (2)
#define SOC_SCHARGER_BUCK_REG4_buck_osc_frq_START      (3)
#define SOC_SCHARGER_BUCK_REG4_buck_osc_frq_END        (6)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_BUCK_REG5_UNION
 �ṹ˵��  : BUCK_REG5 �Ĵ����ṹ���塣��ַƫ����:0x65����ֵ:0x01�����:8
 �Ĵ���˵��: BUCK_REG5���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_fullduty_en   : 1;  /* bit[0]  : buck����ֱͨʱ��������
                                                             0��������
                                                             1����������ǿ��offһ�Ρ� */
        unsigned char  buck_block_ctrl    : 3;  /* bit[1-3]: �������ܿ��� */
        unsigned char  buck_saw_peak_adj  : 2;  /* bit[4-5]: saw��ֵ���ڼĴ��� */
        unsigned char  buck_saw_vally_adj : 1;  /* bit[6]  : saw��ֵ���ڼĴ��� */
        unsigned char  buck_syn_en        : 1;  /* bit[7]  : ����buck�Ƿ���ࣺ
                                                             0�����ࣻ
                                                             1�������ࡣ */
    } reg;
} SOC_SCHARGER_BUCK_REG5_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG5_buck_fullduty_en_START    (0)
#define SOC_SCHARGER_BUCK_REG5_buck_fullduty_en_END      (0)
#define SOC_SCHARGER_BUCK_REG5_buck_block_ctrl_START     (1)
#define SOC_SCHARGER_BUCK_REG5_buck_block_ctrl_END       (3)
#define SOC_SCHARGER_BUCK_REG5_buck_saw_peak_adj_START   (4)
#define SOC_SCHARGER_BUCK_REG5_buck_saw_peak_adj_END     (5)
#define SOC_SCHARGER_BUCK_REG5_buck_saw_vally_adj_START  (6)
#define SOC_SCHARGER_BUCK_REG5_buck_saw_vally_adj_END    (6)
#define SOC_SCHARGER_BUCK_REG5_buck_syn_en_START         (7)
#define SOC_SCHARGER_BUCK_REG5_buck_syn_en_END           (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_BUCK_REG6_UNION
 �ṹ˵��  : BUCK_REG6 �Ĵ����ṹ���塣��ַƫ����:0x66����ֵ:0x51�����:8
 �Ĵ���˵��: BUCK_REG6���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_fullduty_offtime : 2;  /* bit[0-1]: ֱͨ��ǿ�ƹر��Ϲ�ʱ����ڼĴ�����
                                                                00��20nS��
                                                                01��30nS��
                                                                01��40nS��
                                                                11��50n�� */
        unsigned char  buck_min_offtime_sel  : 1;  /* bit[2]  : ��С�ض�ʱ������ */
        unsigned char  buck_min_ontime_sel   : 1;  /* bit[3]  : ��С��ͨʱ������ */
        unsigned char  buck_min_offtime      : 2;  /* bit[4-5]: ��С�ض�ʱ��ѡ�� */
        unsigned char  buck_min_ontime       : 2;  /* bit[6-7]: ��С��ͨʱ��ѡ�� */
    } reg;
} SOC_SCHARGER_BUCK_REG6_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG6_buck_fullduty_offtime_START  (0)
#define SOC_SCHARGER_BUCK_REG6_buck_fullduty_offtime_END    (1)
#define SOC_SCHARGER_BUCK_REG6_buck_min_offtime_sel_START   (2)
#define SOC_SCHARGER_BUCK_REG6_buck_min_offtime_sel_END     (2)
#define SOC_SCHARGER_BUCK_REG6_buck_min_ontime_sel_START    (3)
#define SOC_SCHARGER_BUCK_REG6_buck_min_ontime_sel_END      (3)
#define SOC_SCHARGER_BUCK_REG6_buck_min_offtime_START       (4)
#define SOC_SCHARGER_BUCK_REG6_buck_min_offtime_END         (5)
#define SOC_SCHARGER_BUCK_REG6_buck_min_ontime_START        (6)
#define SOC_SCHARGER_BUCK_REG6_buck_min_ontime_END          (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_BUCK_REG7_UNION
 �ṹ˵��  : BUCK_REG7 �Ĵ����ṹ���塣��ַƫ����:0x67����ֵ:0x25�����:8
 �Ĵ���˵��: BUCK_REG7���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_pfm_in             : 2;  /* bit[0-1]: ����pfm����� */
        unsigned char  buck_pfm_ibias_adj      : 2;  /* bit[2-3]: buck pfmģʽbias�������� */
        unsigned char  buck_fullduty_delaytime : 4;  /* bit[4-7]: ����ʱ��û�п��ض�����Ϊֱͨ��
                                                                  0001��4uS��
                                                                  0010��8uS��
                                                                  0100��16uS��
                                                                  1000��32uS�� */
    } reg;
} SOC_SCHARGER_BUCK_REG7_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG7_buck_pfm_in_START              (0)
#define SOC_SCHARGER_BUCK_REG7_buck_pfm_in_END                (1)
#define SOC_SCHARGER_BUCK_REG7_buck_pfm_ibias_adj_START       (2)
#define SOC_SCHARGER_BUCK_REG7_buck_pfm_ibias_adj_END         (3)
#define SOC_SCHARGER_BUCK_REG7_buck_fullduty_delaytime_START  (4)
#define SOC_SCHARGER_BUCK_REG7_buck_fullduty_delaytime_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_BUCK_REG8_UNION
 �ṹ˵��  : BUCK_REG8 �Ĵ����ṹ���塣��ַƫ����:0x68����ֵ:0x54�����:8
 �Ĵ���˵��: BUCK_REG8���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_offtime_judge_en    : 1;  /* bit[0]  : buck�¹ܿ���ʱ���⹦�ܵ�ʹ���ź� Ĭ��0���� */
        unsigned char  buck_offtime_judge_delay : 3;  /* bit[1-3]: ����ʱ�����жϷ����¹ܿ���ʱ��Ƚ϶� */
        unsigned char  buck_offtime_judge       : 2;  /* bit[4-5]: buck�¹ܿ���ʱ���⣬������sense��·׼��ʱ�� */
        unsigned char  buck_pfm_out             : 2;  /* bit[6-7]: �˳�pfm����� */
    } reg;
} SOC_SCHARGER_BUCK_REG8_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG8_buck_offtime_judge_en_START     (0)
#define SOC_SCHARGER_BUCK_REG8_buck_offtime_judge_en_END       (0)
#define SOC_SCHARGER_BUCK_REG8_buck_offtime_judge_delay_START  (1)
#define SOC_SCHARGER_BUCK_REG8_buck_offtime_judge_delay_END    (3)
#define SOC_SCHARGER_BUCK_REG8_buck_offtime_judge_START        (4)
#define SOC_SCHARGER_BUCK_REG8_buck_offtime_judge_END          (5)
#define SOC_SCHARGER_BUCK_REG8_buck_pfm_out_START              (6)
#define SOC_SCHARGER_BUCK_REG8_buck_pfm_out_END                (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_BUCK_REG9_UNION
 �ṹ˵��  : BUCK_REG9 �Ĵ����ṹ���塣��ַƫ����:0x69����ֵ:0xD5�����:8
 �Ĵ���˵��: BUCK_REG9���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_cmp_ibias_adj   : 1;  /* bit[0]  : buck�Ƚ����������ڼĴ�����
                                                               0��0.5uA��
                                                               1��2uA�� */
        unsigned char  buck_sft_maxduty_en  : 1;  /* bit[1]  : ������ʱ���ռ�ձ�����ʹ�ܿ��� */
        unsigned char  buck_9v_maxduty_adj  : 2;  /* bit[2-3]: 9V����ʱ���ռ�ձȵ��� */
        unsigned char  buck_12v_maxduty_adj : 2;  /* bit[4-5]: 12V����ʱ���ռ�ձȵ��� */
        unsigned char  buck_9v_maxduty_en   : 1;  /* bit[6]  : 9V����ʱ���ռ�ձ��Ƿ�ʹ�� */
        unsigned char  buck_12v_maxduty_en  : 1;  /* bit[7]  : 12V����ʱ���ռ�ձ��Ƿ�ʹ�� */
    } reg;
} SOC_SCHARGER_BUCK_REG9_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG9_buck_cmp_ibias_adj_START    (0)
#define SOC_SCHARGER_BUCK_REG9_buck_cmp_ibias_adj_END      (0)
#define SOC_SCHARGER_BUCK_REG9_buck_sft_maxduty_en_START   (1)
#define SOC_SCHARGER_BUCK_REG9_buck_sft_maxduty_en_END     (1)
#define SOC_SCHARGER_BUCK_REG9_buck_9v_maxduty_adj_START   (2)
#define SOC_SCHARGER_BUCK_REG9_buck_9v_maxduty_adj_END     (3)
#define SOC_SCHARGER_BUCK_REG9_buck_12v_maxduty_adj_START  (4)
#define SOC_SCHARGER_BUCK_REG9_buck_12v_maxduty_adj_END    (5)
#define SOC_SCHARGER_BUCK_REG9_buck_9v_maxduty_en_START    (6)
#define SOC_SCHARGER_BUCK_REG9_buck_9v_maxduty_en_END      (6)
#define SOC_SCHARGER_BUCK_REG9_buck_12v_maxduty_en_START   (7)
#define SOC_SCHARGER_BUCK_REG9_buck_12v_maxduty_en_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_BUCK_REG10_UNION
 �ṹ˵��  : BUCK_REG10 �Ĵ����ṹ���塣��ַƫ����:0x6A����ֵ:0x12�����:8
 �Ĵ���˵��: BUCK_REG10���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_hmos_fall    : 3;  /* bit[0-2]: �Ϲ��½�����������ѡ�� */
        unsigned char  buck_hmos_rise    : 3;  /* bit[3-5]: �Ϲ���������������ѡ�� */
        unsigned char  buck_sftstart_adj : 2;  /* bit[6-7]: buck������ʱ����ڼĴ��� */
    } reg;
} SOC_SCHARGER_BUCK_REG10_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG10_buck_hmos_fall_START     (0)
#define SOC_SCHARGER_BUCK_REG10_buck_hmos_fall_END       (2)
#define SOC_SCHARGER_BUCK_REG10_buck_hmos_rise_START     (3)
#define SOC_SCHARGER_BUCK_REG10_buck_hmos_rise_END       (5)
#define SOC_SCHARGER_BUCK_REG10_buck_sftstart_adj_START  (6)
#define SOC_SCHARGER_BUCK_REG10_buck_sftstart_adj_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_BUCK_REG11_UNION
 �ṹ˵��  : BUCK_REG11 �Ĵ����ṹ���塣��ַƫ����:0x6B����ֵ:0x48�����:8
 �Ĵ���˵��: BUCK_REG11���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_dt_lshs_delay : 2;  /* bit[0-1]: �¹ܵ��Ϲ����������ӳ�5ns��
                                                             ��λ��1 ���������Ƽ�5nS
                                                             ��λ��1 ���������Ƽ�5nS */
        unsigned char  buck_lmos_fall     : 3;  /* bit[2-4]: �¹��½�����������ѡ�� */
        unsigned char  buck_lmos_rise     : 3;  /* bit[5-7]: �¹���������������ѡ�� */
    } reg;
} SOC_SCHARGER_BUCK_REG11_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG11_buck_dt_lshs_delay_START  (0)
#define SOC_SCHARGER_BUCK_REG11_buck_dt_lshs_delay_END    (1)
#define SOC_SCHARGER_BUCK_REG11_buck_lmos_fall_START      (2)
#define SOC_SCHARGER_BUCK_REG11_buck_lmos_fall_END        (4)
#define SOC_SCHARGER_BUCK_REG11_buck_lmos_rise_START      (5)
#define SOC_SCHARGER_BUCK_REG11_buck_lmos_rise_END        (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_BUCK_REG12_UNION
 �ṹ˵��  : BUCK_REG12 �Ĵ����ṹ���塣��ַƫ����:0x6C����ֵ:0x01�����:8
 �Ĵ���˵��: BUCK_REG12���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_dmd_ibias   : 2;  /* bit[0-1]: buck_dmdƫ�õ������� */
        unsigned char  buck_dmd_dis     : 1;  /* bit[2]  : ѡ���Ƿ�����DMD���ܣ�
                                                           0�������Σ�
                                                           1�����Ρ� */
        unsigned char  buck_dmd_clamp   : 1;  /* bit[3]  : dmd�Ƚ������Ƕλʹ�ܣ�
                                                           0��Ƕλ��
                                                           1����Ƕλ�� */
        unsigned char  buck_ss_init_dis : 1;  /* bit[4]  : buck����ʱ�Ƿ�����initģ�飺
                                                           0�������Σ�
                                                           1������ */
        unsigned char  buck_ssmode_en   : 1;  /* bit[5]  : buck����ʱ�Ƿ�Ҫ�ȴ�VC�ٿ���driver��
                                                           0�����ȴ���
                                                           1���ȴ��� */
        unsigned char  buck_dt_hsls     : 1;  /* bit[6]  : �Ϲܵ��¹����������ӳ�5nS��
                                                           0������5nS��
                                                           1����5nS�� */
        unsigned char  buck_dt_lshs     : 1;  /* bit[7]  : �¹ܵ��Ϲܵ�����������ʽѡ��
                                                           0��������ʱ�䣻
                                                           1��������ʱ��(PWM)�� */
    } reg;
} SOC_SCHARGER_BUCK_REG12_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG12_buck_dmd_ibias_START    (0)
#define SOC_SCHARGER_BUCK_REG12_buck_dmd_ibias_END      (1)
#define SOC_SCHARGER_BUCK_REG12_buck_dmd_dis_START      (2)
#define SOC_SCHARGER_BUCK_REG12_buck_dmd_dis_END        (2)
#define SOC_SCHARGER_BUCK_REG12_buck_dmd_clamp_START    (3)
#define SOC_SCHARGER_BUCK_REG12_buck_dmd_clamp_END      (3)
#define SOC_SCHARGER_BUCK_REG12_buck_ss_init_dis_START  (4)
#define SOC_SCHARGER_BUCK_REG12_buck_ss_init_dis_END    (4)
#define SOC_SCHARGER_BUCK_REG12_buck_ssmode_en_START    (5)
#define SOC_SCHARGER_BUCK_REG12_buck_ssmode_en_END      (5)
#define SOC_SCHARGER_BUCK_REG12_buck_dt_hsls_START      (6)
#define SOC_SCHARGER_BUCK_REG12_buck_dt_hsls_END        (6)
#define SOC_SCHARGER_BUCK_REG12_buck_dt_lshs_START      (7)
#define SOC_SCHARGER_BUCK_REG12_buck_dt_lshs_END        (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_BUCK_REG13_UNION
 �ṹ˵��  : BUCK_REG13 �Ĵ����ṹ���塣��ַƫ����:0x6D����ֵ:0x39�����:8
 �Ĵ���˵��: BUCK_REG13���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_q1ocp_adj    : 2;  /* bit[0-1]: bcuk�Ϲ�ocp�����ڼĴ�����
                                                            00��1.8A��
                                                            01��2A��
                                                            10��2.2A��
                                                            11��2.4A�� */
        unsigned char  buck_sft_scp_en_n : 1;  /* bit[2]  : buck �������Ƿ���scp���ܣ�
                                                            0��������
                                                            1�����Ρ� */
        unsigned char  buck_dmd_sel      : 4;  /* bit[3-6]: DMD��ѡ��
                                                            0111:180mA */
        unsigned char  buck_dmd_delay    : 1;  /* bit[7]  : dmd���NG��ʱ��
                                                            1������15nS */
    } reg;
} SOC_SCHARGER_BUCK_REG13_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG13_buck_q1ocp_adj_START     (0)
#define SOC_SCHARGER_BUCK_REG13_buck_q1ocp_adj_END       (1)
#define SOC_SCHARGER_BUCK_REG13_buck_sft_scp_en_n_START  (2)
#define SOC_SCHARGER_BUCK_REG13_buck_sft_scp_en_n_END    (2)
#define SOC_SCHARGER_BUCK_REG13_buck_dmd_sel_START       (3)
#define SOC_SCHARGER_BUCK_REG13_buck_dmd_sel_END         (6)
#define SOC_SCHARGER_BUCK_REG13_buck_dmd_delay_START     (7)
#define SOC_SCHARGER_BUCK_REG13_buck_dmd_delay_END       (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_BUCK_REG14_UNION
 �ṹ˵��  : BUCK_REG14 �Ĵ����ṹ���塣��ַƫ����:0x6E����ֵ:0x55�����:8
 �Ĵ���˵��: BUCK_REG14���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_q1ocp_lpf_adj : 2;  /* bit[0-1]: buck�Ϲܼ��ʱ�˶�ʱ����ڣ�
                                                             00��50n��
                                                             01��75n��
                                                             10��90n��
                                                             11��100n�� */
        unsigned char  buck_q3ocp_lpf_adj : 2;  /* bit[2-3]: buck�¹ܼ��ʱ�˶�ʱ����ڣ�
                                                             00��50n��
                                                             01��75n��
                                                             10��90n��
                                                             11��100n�� */
        unsigned char  buck_ocp_vally     : 2;  /* bit[4-5]: buck �¹ܹ�ֵocp�����ڼĴ�����
                                                             00��1.5A��
                                                             01��1.7A��
                                                             10��1.9A��
                                                             11��2.2A */
        unsigned char  buck_ocp_peak      : 2;  /* bit[6-7]: buck �¹ܷ�ֵocp�����ڼĴ�����
                                                             00��2.5A��
                                                             01��2.8A��
                                                             10��3A��
                                                             11��3.2A */
    } reg;
} SOC_SCHARGER_BUCK_REG14_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG14_buck_q1ocp_lpf_adj_START  (0)
#define SOC_SCHARGER_BUCK_REG14_buck_q1ocp_lpf_adj_END    (1)
#define SOC_SCHARGER_BUCK_REG14_buck_q3ocp_lpf_adj_START  (2)
#define SOC_SCHARGER_BUCK_REG14_buck_q3ocp_lpf_adj_END    (3)
#define SOC_SCHARGER_BUCK_REG14_buck_ocp_vally_START      (4)
#define SOC_SCHARGER_BUCK_REG14_buck_ocp_vally_END        (5)
#define SOC_SCHARGER_BUCK_REG14_buck_ocp_peak_START       (6)
#define SOC_SCHARGER_BUCK_REG14_buck_ocp_peak_END         (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_BUCK_REG15_UNION
 �ṹ˵��  : BUCK_REG15 �Ĵ����ṹ���塣��ַƫ����:0x6F����ֵ:0x04�����:8
 �Ĵ���˵��: BUCK_REG15���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_ocp_mode_sel      : 1;  /* bit[0]  : buck ocpʱ������ѡ��
                                                                 0���ȷ�ֵ��⣻
                                                                 1��ֻ����ֵ�� */
        unsigned char  buck_ocp_sense_cap_adj : 1;  /* bit[1]  : buck ocp sense��·���˲����ݵ��ڣ�
                                                                 0�������ӵ��ݣ�
                                                                 1�����ӵ��ݡ� */
        unsigned char  buck_ocp_delay         : 2;  /* bit[2-3]: ����ocp��ǿ�ƹر��Ϲ�ʱ����ڣ�
                                                                 00��400nS��
                                                                 01��570nS��
                                                                 10��720nS��
                                                                 11��860nS�� */
        unsigned char  buck_sft_ocp_en        : 1;  /* bit[4]  : buck������ʱ�Ƿ��ϡ��¹�ocpͬʱ���: 
                                                                 0��ͬʱ��⣻
                                                                 1��ֻ����Ϲܡ� */
        unsigned char  reserved               : 3;  /* bit[5-7]: ������ */
    } reg;
} SOC_SCHARGER_BUCK_REG15_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG15_buck_ocp_mode_sel_START       (0)
#define SOC_SCHARGER_BUCK_REG15_buck_ocp_mode_sel_END         (0)
#define SOC_SCHARGER_BUCK_REG15_buck_ocp_sense_cap_adj_START  (1)
#define SOC_SCHARGER_BUCK_REG15_buck_ocp_sense_cap_adj_END    (1)
#define SOC_SCHARGER_BUCK_REG15_buck_ocp_delay_START          (2)
#define SOC_SCHARGER_BUCK_REG15_buck_ocp_delay_END            (3)
#define SOC_SCHARGER_BUCK_REG15_buck_sft_ocp_en_START         (4)
#define SOC_SCHARGER_BUCK_REG15_buck_sft_ocp_en_END           (4)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_BUCK_REG16_UNION
 �ṹ˵��  : BUCK_REG16 �Ĵ����ṹ���塣��ַƫ����:0x70����ֵ:0x15�����:8
 �Ĵ���˵��: BUCK����������ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_sd_sel      : 2;  /* bit[0-1]: ˫����������ӳ�ʱ�����λ��
                                                           00��25ns��
                                                           01��50ns��
                                                           10��75ns��
                                                           11��100ns�� */
        unsigned char  buck_st_sel      : 2;  /* bit[2-3]: ˫���������ʱ�����λ��
                                                           00��15ns��
                                                           01��30ns��
                                                           10��45ns��
                                                           11��60ns�� */
        unsigned char  buck_balance_sel : 1;  /* bit[4]  : �����������ѡ��
                                                           0�������رգ�
                                                           1������ʹ�ܡ� */
        unsigned char  reserved         : 3;  /* bit[5-7]: ������ */
    } reg;
} SOC_SCHARGER_BUCK_REG16_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG16_buck_sd_sel_START       (0)
#define SOC_SCHARGER_BUCK_REG16_buck_sd_sel_END         (1)
#define SOC_SCHARGER_BUCK_REG16_buck_st_sel_START       (2)
#define SOC_SCHARGER_BUCK_REG16_buck_st_sel_END         (3)
#define SOC_SCHARGER_BUCK_REG16_buck_balance_sel_START  (4)
#define SOC_SCHARGER_BUCK_REG16_buck_balance_sel_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_BUCK_RES_SEL0_UNION
 �ṹ˵��  : BUCK_RES_SEL0 �Ĵ����ṹ���塣��ַƫ����:0x71����ֵ:0x55�����:8
 �Ĵ���˵��: BUCK�������0�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_res4_sel : 2;  /* bit[0-1]: dpm��·preamp�絼���ڵ��裺
                                                        00��3.5K��
                                                        01��5.3K��
                                                        10��7.1K��
                                                        11��8.9K�� */
        unsigned char  buck_res3_sel : 2;  /* bit[2-3]: fast cc regulation ��·preamp�絼���ڵ��裺
                                                        00��35K��
                                                        01��70K��
                                                        10��105K��
                                                        11��140K�� */
        unsigned char  buck_res2_sel : 2;  /* bit[4-5]: cv regulation ��·preamp�絼���ڵ��裺
                                                        00��0.9K��
                                                        01��1.8K��
                                                        10��2.7K��
                                                        11��3.6K�� */
        unsigned char  buck_res1_sel : 2;  /* bit[6-7]: sys regulation ��·preamp�絼���ڵ��裺
                                                        00��1.8K��
                                                        01��2.7K��
                                                        10��3.6K��
                                                        11��4.5K�� */
    } reg;
} SOC_SCHARGER_BUCK_RES_SEL0_UNION;
#endif
#define SOC_SCHARGER_BUCK_RES_SEL0_buck_res4_sel_START  (0)
#define SOC_SCHARGER_BUCK_RES_SEL0_buck_res4_sel_END    (1)
#define SOC_SCHARGER_BUCK_RES_SEL0_buck_res3_sel_START  (2)
#define SOC_SCHARGER_BUCK_RES_SEL0_buck_res3_sel_END    (3)
#define SOC_SCHARGER_BUCK_RES_SEL0_buck_res2_sel_START  (4)
#define SOC_SCHARGER_BUCK_RES_SEL0_buck_res2_sel_END    (5)
#define SOC_SCHARGER_BUCK_RES_SEL0_buck_res1_sel_START  (6)
#define SOC_SCHARGER_BUCK_RES_SEL0_buck_res1_sel_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_BUCK_RES_SEL1_UNION
 �ṹ˵��  : BUCK_RES_SEL1 �Ĵ����ṹ���塣��ַƫ����:0x72����ֵ:0x55�����:8
 �Ĵ���˵��: BUCK�������1�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_res8_sel : 2;  /* bit[0-1]: ���Ͳ������粹������R2��
                                                        00��13K��
                                                        01��26K��
                                                        10��39K��
                                                        11��52K�� */
        unsigned char  buck_res7_sel : 2;  /* bit[2-3]: ���Ͳ������粹������R1��
                                                        00��535K��
                                                        01��1070K��
                                                        10��1605K��
                                                        11��2140K�� */
        unsigned char  buck_res6_sel : 2;  /* bit[4-5]: themal regulation��·preamp�絼���ڵ��裺
                                                        00��3.5K��
                                                        01��5.3K��
                                                        10��7.1K��
                                                        11��8.9K�� */
        unsigned char  buck_res5_sel : 2;  /* bit[6-7]: acl��·preamp�絼���ڵ��裺
                                                        00��54K��
                                                        01��108K��
                                                        10��162K��
                                                        11��216K�� */
    } reg;
} SOC_SCHARGER_BUCK_RES_SEL1_UNION;
#endif
#define SOC_SCHARGER_BUCK_RES_SEL1_buck_res8_sel_START  (0)
#define SOC_SCHARGER_BUCK_RES_SEL1_buck_res8_sel_END    (1)
#define SOC_SCHARGER_BUCK_RES_SEL1_buck_res7_sel_START  (2)
#define SOC_SCHARGER_BUCK_RES_SEL1_buck_res7_sel_END    (3)
#define SOC_SCHARGER_BUCK_RES_SEL1_buck_res6_sel_START  (4)
#define SOC_SCHARGER_BUCK_RES_SEL1_buck_res6_sel_END    (5)
#define SOC_SCHARGER_BUCK_RES_SEL1_buck_res5_sel_START  (6)
#define SOC_SCHARGER_BUCK_RES_SEL1_buck_res5_sel_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_BUCK_RES_SEL2_UNION
 �ṹ˵��  : BUCK_RES_SEL2 �Ĵ����ṹ���塣��ַƫ����:0x73����ֵ:0x59�����:8
 �Ĵ���˵��: BUCK�������2�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_res12_sel : 2;  /* bit[0-1]: cc��·�������裺
                                                         00�� 
                                                         01�� 
                                                         10�� 
                                                         11�� */
        unsigned char  buck_res11_sel : 2;  /* bit[2-3]: ���������·����ת��ѹ���裺
                                                         00��10K��
                                                         01��15K��
                                                         10��20K��
                                                         11��25K�� */
        unsigned char  buck_res10_sel : 2;  /* bit[4-5]: �������OTA������裺
                                                         00��5K��
                                                         01��10K��
                                                         10��15K��
                                                         11��20K�� */
        unsigned char  buck_res9_sel  : 2;  /* bit[6-7]: ���Ͳ������粹������R3��
                                                         00��106K��
                                                         01��212K��
                                                         10��318K��
                                                         11��424K�� */
    } reg;
} SOC_SCHARGER_BUCK_RES_SEL2_UNION;
#endif
#define SOC_SCHARGER_BUCK_RES_SEL2_buck_res12_sel_START  (0)
#define SOC_SCHARGER_BUCK_RES_SEL2_buck_res12_sel_END    (1)
#define SOC_SCHARGER_BUCK_RES_SEL2_buck_res11_sel_START  (2)
#define SOC_SCHARGER_BUCK_RES_SEL2_buck_res11_sel_END    (3)
#define SOC_SCHARGER_BUCK_RES_SEL2_buck_res10_sel_START  (4)
#define SOC_SCHARGER_BUCK_RES_SEL2_buck_res10_sel_END    (5)
#define SOC_SCHARGER_BUCK_RES_SEL2_buck_res9_sel_START   (6)
#define SOC_SCHARGER_BUCK_RES_SEL2_buck_res9_sel_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_BUCK_RES_SEL3_UNION
 �ṹ˵��  : BUCK_RES_SEL3 �Ĵ����ṹ���塣��ַƫ����:0x74����ֵ:0x05�����:8
 �Ĵ���˵��: BUCK�������3�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_res14_sel : 2;  /* bit[0-1]: acl��·�������裺
                                                         00�� 
                                                         01��
                                                         10�� 
                                                         11��  */
        unsigned char  buck_res13_sel : 2;  /* bit[2-3]: dpm��·�������裺
                                                         00�� 
                                                         01��
                                                         10�� 
                                                         11��  */
        unsigned char  reserved       : 4;  /* bit[4-7]: ������ */
    } reg;
} SOC_SCHARGER_BUCK_RES_SEL3_UNION;
#endif
#define SOC_SCHARGER_BUCK_RES_SEL3_buck_res14_sel_START  (0)
#define SOC_SCHARGER_BUCK_RES_SEL3_buck_res14_sel_END    (1)
#define SOC_SCHARGER_BUCK_RES_SEL3_buck_res13_sel_START  (2)
#define SOC_SCHARGER_BUCK_RES_SEL3_buck_res13_sel_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_BUCK_CAP_SEL0_UNION
 �ṹ˵��  : BUCK_CAP_SEL0 �Ĵ����ṹ���塣��ַƫ����:0x75����ֵ:0x55�����:8
 �Ĵ���˵��: BUCK���ݵ���0�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_cap4_sel : 2;  /* bit[0-1]: ������·�������ݣ�
                                                        00��4pF��
                                                        01��6pF��
                                                        10��8pF��
                                                        11��10pF�� */
        unsigned char  buck_cap3_sel : 2;  /* bit[2-3]: ���Ͳ������粹������C3��
                                                        00��50fF��
                                                        01��100fF��
                                                        10��150fF��
                                                        11��200fF�� */
        unsigned char  buck_cap2_sel : 2;  /* bit[4-5]: ���Ͳ������粹������C2��
                                                        00��1.2pF��
                                                        01��2.4pF��
                                                        10��3.6pF��
                                                        11��4.8pF�� */
        unsigned char  buck_cap1_sel : 2;  /* bit[6-7]: ���Ͳ������粹������C1��
                                                        00��41pF��
                                                        01��50pF��
                                                        10��59pF��
                                                        11��68pF�� */
    } reg;
} SOC_SCHARGER_BUCK_CAP_SEL0_UNION;
#endif
#define SOC_SCHARGER_BUCK_CAP_SEL0_buck_cap4_sel_START  (0)
#define SOC_SCHARGER_BUCK_CAP_SEL0_buck_cap4_sel_END    (1)
#define SOC_SCHARGER_BUCK_CAP_SEL0_buck_cap3_sel_START  (2)
#define SOC_SCHARGER_BUCK_CAP_SEL0_buck_cap3_sel_END    (3)
#define SOC_SCHARGER_BUCK_CAP_SEL0_buck_cap2_sel_START  (4)
#define SOC_SCHARGER_BUCK_CAP_SEL0_buck_cap2_sel_END    (5)
#define SOC_SCHARGER_BUCK_CAP_SEL0_buck_cap1_sel_START  (6)
#define SOC_SCHARGER_BUCK_CAP_SEL0_buck_cap1_sel_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_BUCK_CAP_SEL1_UNION
 �ṹ˵��  : BUCK_CAP_SEL1 �Ĵ����ṹ���塣��ַƫ����:0x76����ֵ:0x15�����:8
 �Ĵ���˵��: BUCK���ݵ���1�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_cap7_sel : 2;  /* bit[0-1]: acl��·�������ݣ�
                                                        00��3pF��
                                                        01��6pF��
                                                        10��9pF��
                                                        11��12pF�� */
        unsigned char  buck_cap6_sel : 2;  /* bit[2-3]: dpm��·�������ݣ�
                                                        00��1.2pF��
                                                        01��2.4pF��
                                                        10��3.6pF��
                                                        11��4.8pF�� */
        unsigned char  buck_cap5_sel : 2;  /* bit[4-5]: cc��·�������ݣ�
                                                        00��3pF��
                                                        01��6pF��
                                                        10��9pF��
                                                        11��12pF�� */
        unsigned char  reserved      : 2;  /* bit[6-7]: ������ */
    } reg;
} SOC_SCHARGER_BUCK_CAP_SEL1_UNION;
#endif
#define SOC_SCHARGER_BUCK_CAP_SEL1_buck_cap7_sel_START  (0)
#define SOC_SCHARGER_BUCK_CAP_SEL1_buck_cap7_sel_END    (1)
#define SOC_SCHARGER_BUCK_CAP_SEL1_buck_cap6_sel_START  (2)
#define SOC_SCHARGER_BUCK_CAP_SEL1_buck_cap6_sel_END    (3)
#define SOC_SCHARGER_BUCK_CAP_SEL1_buck_cap5_sel_START  (4)
#define SOC_SCHARGER_BUCK_CAP_SEL1_buck_cap5_sel_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_BUCK_RESERVE0_UNION
 �ṹ˵��  : BUCK_RESERVE0 �Ĵ����ṹ���塣��ַƫ����:0x77����ֵ:0x00�����:8
 �Ĵ���˵��: BUCKԤ��0�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_reserve0 : 8;
    } reg;
} SOC_SCHARGER_BUCK_RESERVE0_UNION;
#endif
#define SOC_SCHARGER_BUCK_RESERVE0_buck_reserve0_START  (0)
#define SOC_SCHARGER_BUCK_RESERVE0_buck_reserve0_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_BUCK_RESERVE1_UNION
 �ṹ˵��  : BUCK_RESERVE1 �Ĵ����ṹ���塣��ַƫ����:0x78����ֵ:0x00�����:8
 �Ĵ���˵��: BUCKԤ��1�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_reserve1 : 8;  /* bit[0-7]: <3> 5V����ʱ���Ƿ�ʹ��OCP��Ĭ��0��ʾʹ��
                                                        <5:4> dpm�޵����üĴ�����Ĭ��00 */
    } reg;
} SOC_SCHARGER_BUCK_RESERVE1_UNION;
#endif
#define SOC_SCHARGER_BUCK_RESERVE1_buck_reserve1_START  (0)
#define SOC_SCHARGER_BUCK_RESERVE1_buck_reserve1_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_BUCK_RESERVE2_UNION
 �ṹ˵��  : BUCK_RESERVE2 �Ĵ����ṹ���塣��ַƫ����:0x79����ֵ:0x00�����:8
 �Ĵ���˵��: BUCKԤ��2�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_reserve2 : 8;  /* bit[0-7]: <7> anti-reverbstģ��ʹ��
                                                        0���ر� 1��ʹ��
                                                        <6> anti-reverbstȥ��ʱ��ѡ��
                                                        0��32ms 1��8ms
                                                        <5:4> anti-reverbst��������
                                                        00:50mv
                                                        01:100mv
                                                        10:200mv
                                                        11:0mv
                                                        <3:2>buck_cap8��С����
                                                        00: 60pF
                                                        01��45pF
                                                        10: 30pF
                                                        11: 15pF
                                                        <1:0>buck����ģʽѡ��
                                                        00��Ĭ��ģʽ
                                                        01��ǿ����������ģʽ
                                                        10��ǿ�Ʋ�������ģʽ
                                                        11��Ĭ��ģʽ */
    } reg;
} SOC_SCHARGER_BUCK_RESERVE2_UNION;
#endif
#define SOC_SCHARGER_BUCK_RESERVE2_buck_reserve2_START  (0)
#define SOC_SCHARGER_BUCK_RESERVE2_buck_reserve2_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_BUCK_RESERVE3_UNION
 �ṹ˵��  : BUCK_RESERVE3 �Ĵ����ṹ���塣��ַƫ����:0x7A����ֵ:0x00�����:8
 �Ĵ���˵��: BUCKԤ��3�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_reserve3 : 8;  /* bit[0-7]: Ԥ���Ĵ��� */
    } reg;
} SOC_SCHARGER_BUCK_RESERVE3_UNION;
#endif
#define SOC_SCHARGER_BUCK_RESERVE3_buck_reserve3_START  (0)
#define SOC_SCHARGER_BUCK_RESERVE3_buck_reserve3_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_BUCK_RESERVE0_STATE_UNION
 �ṹ˵��  : BUCK_RESERVE0_STATE �Ĵ����ṹ���塣��ַƫ����:0x7B����ֵ:0x00�����:8
 �Ĵ���˵��: BUCKԤ��0״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_reserve0_state : 8;  /* bit[0-7]: Ԥ���Ĵ��� */
    } reg;
} SOC_SCHARGER_BUCK_RESERVE0_STATE_UNION;
#endif
#define SOC_SCHARGER_BUCK_RESERVE0_STATE_buck_reserve0_state_START  (0)
#define SOC_SCHARGER_BUCK_RESERVE0_STATE_buck_reserve0_state_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_BUCK_RESERVE1_STATE_UNION
 �ṹ˵��  : BUCK_RESERVE1_STATE �Ĵ����ṹ���塣��ַƫ����:0x7C����ֵ:0x00�����:8
 �Ĵ���˵��: BUCKԤ��1״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_reserve1_state : 8;  /* bit[0-7]: Ԥ���Ĵ��� */
    } reg;
} SOC_SCHARGER_BUCK_RESERVE1_STATE_UNION;
#endif
#define SOC_SCHARGER_BUCK_RESERVE1_STATE_buck_reserve1_state_START  (0)
#define SOC_SCHARGER_BUCK_RESERVE1_STATE_buck_reserve1_state_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_OTG_REG0_UNION
 �ṹ˵��  : OTG_REG0 �Ĵ����ṹ���塣��ַƫ����:0x80����ֵ:0x2F�����:8
 �Ĵ���˵��: OTG_REG0���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_scp_en  : 1;  /* bit[0]  : boost scp����ѡ��
                                                      0����·��ϵͳ���Զ��رգ����ϱ�����
                                                      1����·��ϵͳ�Զ��رգ� */
        unsigned char  otg_ocp_sys : 1;  /* bit[1]  : boost OCP����ѡ��
                                                      0���������ϱ���
                                                      1���������ϱ��� */
        unsigned char  otg_ocp_en  : 1;  /* bit[2]  : boost OCP����ѡ��
                                                      0��������������
                                                      1�������������� */
        unsigned char  otg_lim_set : 2;  /* bit[3-4]: boostƽ������ѡ��
                                                      00��500mA��
                                                      01��1A��
                                                      10��1.5A��
                                                      11��2A�� */
        unsigned char  otg_lim_en  : 1;  /* bit[5]  : boost ƽ������ģ��ʹ�ܣ�
                                                      0���ر�ƽ������ģ�飻
                                                      1��ʹ��ƽ������ģ�顣 */
        unsigned char  otg_en_int  : 1;  /* bit[6]  : otg_enʹ�����üĴ�����
                                                      0���رգ�
                                                      1��ʹ�ܡ� */
        unsigned char  reserved    : 1;  /* bit[7]  : ������ */
    } reg;
} SOC_SCHARGER_OTG_REG0_UNION;
#endif
#define SOC_SCHARGER_OTG_REG0_otg_scp_en_START   (0)
#define SOC_SCHARGER_OTG_REG0_otg_scp_en_END     (0)
#define SOC_SCHARGER_OTG_REG0_otg_ocp_sys_START  (1)
#define SOC_SCHARGER_OTG_REG0_otg_ocp_sys_END    (1)
#define SOC_SCHARGER_OTG_REG0_otg_ocp_en_START   (2)
#define SOC_SCHARGER_OTG_REG0_otg_ocp_en_END     (2)
#define SOC_SCHARGER_OTG_REG0_otg_lim_set_START  (3)
#define SOC_SCHARGER_OTG_REG0_otg_lim_set_END    (4)
#define SOC_SCHARGER_OTG_REG0_otg_lim_en_START   (5)
#define SOC_SCHARGER_OTG_REG0_otg_lim_en_END     (5)
#define SOC_SCHARGER_OTG_REG0_otg_en_int_START   (6)
#define SOC_SCHARGER_OTG_REG0_otg_en_int_END     (6)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_OTG_REG1_UNION
 �ṹ˵��  : OTG_REG1 �Ĵ����ṹ���塣��ַƫ����:0x81����ֵ:0x5D�����:8
 �Ĵ���˵��: OTG_REG1���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_vo        : 2;  /* bit[0-1]: OTG�����ѹ΢����
                                                        00�� 
                                                        01��
                                                        10�� 
                                                        11�� */
        unsigned char  otg_pfm_v_en  : 1;  /* bit[2]  : boost pfm_vʹ�ܣ�
                                                        0���ر�pfm��
                                                        1��ʹ��pfm�� */
        unsigned char  otg_ovp_en    : 1;  /* bit[3]  : boost ovpʹ�ܣ�
                                                        0���رչ�ѹ��·�����ϱ�����
                                                        1��ʹ�ܹ�ѹ��·���ϱ����� */
        unsigned char  otg_uvp_set_v : 2;  /* bit[4-5]: boost uvp��ѹ��ѡ��
                                                        00��
                                                        01�� 
                                                        10��
                                                        11��  */
        unsigned char  otg_uvp_en    : 1;  /* bit[6]  : boost uvpʹ�ܣ�
                                                        0���ر�Ƿѹ��·�����ϱ�����
                                                        1��ʹ��Ƿѹ��·���ϱ����� */
        unsigned char  reserved      : 1;  /* bit[7]  : ������ */
    } reg;
} SOC_SCHARGER_OTG_REG1_UNION;
#endif
#define SOC_SCHARGER_OTG_REG1_otg_vo_START         (0)
#define SOC_SCHARGER_OTG_REG1_otg_vo_END           (1)
#define SOC_SCHARGER_OTG_REG1_otg_pfm_v_en_START   (2)
#define SOC_SCHARGER_OTG_REG1_otg_pfm_v_en_END     (2)
#define SOC_SCHARGER_OTG_REG1_otg_ovp_en_START     (3)
#define SOC_SCHARGER_OTG_REG1_otg_ovp_en_END       (3)
#define SOC_SCHARGER_OTG_REG1_otg_uvp_set_v_START  (4)
#define SOC_SCHARGER_OTG_REG1_otg_uvp_set_v_END    (5)
#define SOC_SCHARGER_OTG_REG1_otg_uvp_en_START     (6)
#define SOC_SCHARGER_OTG_REG1_otg_uvp_en_END       (6)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_OTG_REG2_UNION
 �ṹ˵��  : OTG_REG2 �Ĵ����ṹ���塣��ַƫ����:0x82����ֵ:0x2B�����:8
 �Ĵ���˵��: OTG_REG2���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_slop_en   : 1;  /* bit[0]  : boost б�²���ʹ�ܣ�
                                                        0���ر�б�²�����
                                                        1��ʹ��б�²����� */
        unsigned char  otg_dmd       : 1;  /* bit[1]  : boost dmdʹ�ܣ�
                                                        0���رչ����⣻
                                                        1��ʹ�ܹ����⡣ */
        unsigned char  otg_skip_set  : 1;  /* bit[2]  : skip������Pmos�Ŀ���״̬��
                                                        0��PMOS�رգ�
                                                        1��PMOS������ */
        unsigned char  otg_ovp_set_t : 2;  /* bit[3-4]: boost ovpȥ��ʱ��ѡ��
                                                        00��0ms��
                                                        01��1ms��
                                                        10��2ms��
                                                        11��4ms�� */
        unsigned char  otg_uvp_set_t : 2;  /* bit[5-6]: boost uvpȥ��ʱ��ѡ��
                                                        00��0ms��
                                                        01��1ms��
                                                        10��2ms��
                                                        11��4ms�� */
        unsigned char  otg_scp_time  : 1;  /* bit[7]  : boost scpʱ��ѡ��
                                                        0��1ms��VOUT����0.85BAT���ϱ���·��
                                                        1��2ms��VOUT����0.85BAT���ϱ���·�� */
    } reg;
} SOC_SCHARGER_OTG_REG2_UNION;
#endif
#define SOC_SCHARGER_OTG_REG2_otg_slop_en_START    (0)
#define SOC_SCHARGER_OTG_REG2_otg_slop_en_END      (0)
#define SOC_SCHARGER_OTG_REG2_otg_dmd_START        (1)
#define SOC_SCHARGER_OTG_REG2_otg_dmd_END          (1)
#define SOC_SCHARGER_OTG_REG2_otg_skip_set_START   (2)
#define SOC_SCHARGER_OTG_REG2_otg_skip_set_END     (2)
#define SOC_SCHARGER_OTG_REG2_otg_ovp_set_t_START  (3)
#define SOC_SCHARGER_OTG_REG2_otg_ovp_set_t_END    (4)
#define SOC_SCHARGER_OTG_REG2_otg_uvp_set_t_START  (5)
#define SOC_SCHARGER_OTG_REG2_otg_uvp_set_t_END    (6)
#define SOC_SCHARGER_OTG_REG2_otg_scp_time_START   (7)
#define SOC_SCHARGER_OTG_REG2_otg_scp_time_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_OTG_REG3_UNION
 �ṹ˵��  : OTG_REG3 �Ĵ����ṹ���塣��ַƫ����:0x83����ֵ:0x94�����:8
 �Ĵ���˵��: OTG_REG3���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_clp_l_iav_set : 2;  /* bit[0-1]: boost EA_iavǯλ��·���ͣ���ƽѡ��
                                                            00��
                                                            01��
                                                            10��
                                                            11�� */
        unsigned char  otg_clp_l_iav_en  : 1;  /* bit[2]  : boost EA_iavǯλ��·���ͣ�ʹ�ܣ�
                                                            0���ر�ǯλ��·��
                                                            1��ʹ��ǯλ��·�� */
        unsigned char  otg_clp_h_iav_en  : 1;  /* bit[3]  : boost EA_iavǯλ��·���ߣ�ʹ�ܣ�
                                                            0���ر�ǯλ��·��
                                                            1��ʹ��ǯλ��·�� */
        unsigned char  otg_clp_l_en      : 1;  /* bit[4]  : boost EAǯλ��·���ͣ�ʹ�ܣ�
                                                            0���ر�ǯλ��·��
                                                            1��ʹ��ǯλ��·�� */
        unsigned char  otg_clp_h_en      : 1;  /* bit[5]  : boost EAǯλ��·���ߣ�ʹ�ܣ�
                                                            0���ر�ǯλ��·��
                                                            1��ʹ��ǯλ��·�� */
        unsigned char  otg_slop_set      : 2;  /* bit[6-7]: boost б�²�������ѡ��
                                                            00��1.5p��
                                                            01��2p��
                                                            10��2.5p��
                                                            11��3p�� */
    } reg;
} SOC_SCHARGER_OTG_REG3_UNION;
#endif
#define SOC_SCHARGER_OTG_REG3_otg_clp_l_iav_set_START  (0)
#define SOC_SCHARGER_OTG_REG3_otg_clp_l_iav_set_END    (1)
#define SOC_SCHARGER_OTG_REG3_otg_clp_l_iav_en_START   (2)
#define SOC_SCHARGER_OTG_REG3_otg_clp_l_iav_en_END     (2)
#define SOC_SCHARGER_OTG_REG3_otg_clp_h_iav_en_START   (3)
#define SOC_SCHARGER_OTG_REG3_otg_clp_h_iav_en_END     (3)
#define SOC_SCHARGER_OTG_REG3_otg_clp_l_en_START       (4)
#define SOC_SCHARGER_OTG_REG3_otg_clp_l_en_END         (4)
#define SOC_SCHARGER_OTG_REG3_otg_clp_h_en_START       (5)
#define SOC_SCHARGER_OTG_REG3_otg_clp_h_en_END         (5)
#define SOC_SCHARGER_OTG_REG3_otg_slop_set_START       (6)
#define SOC_SCHARGER_OTG_REG3_otg_slop_set_END         (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_OTG_REG4_UNION
 �ṹ˵��  : OTG_REG4 �Ĵ����ṹ���塣��ַƫ����:0x84����ֵ:0x65�����:8
 �Ĵ���˵��: OTG_REG4���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_ccom2_cmp  : 2;  /* bit[0-1]: boost EA����˲����ݣ���ֵ����ģ����
                                                         00��0.8pF��
                                                         01��1.1pF��
                                                         10��1.4pF��
                                                         11��1.7pF�� */
        unsigned char  otg_ccom1_cmp  : 2;  /* bit[2-3]: boost ����·�������ݣ���ֵ����ģ����
                                                         00��35pF��
                                                         01��40pF��
                                                         10��45pF��
                                                         11��50pF�� */
        unsigned char  otg_rcom_cmp   : 2;  /* bit[4-5]: boost ����·�������裨��ֵ����ģ����
                                                         00��320k����
                                                         01��280k����
                                                         10��240k����
                                                         11��200k���� */
        unsigned char  otg_clp_l_set  : 1;  /* bit[6]  : boost EA���ǯλֵ��VRAMPֱ����ƽֵ��ʧ����
                                                         0��27mv��
                                                         1��40mv�� */
        unsigned char  otg_pfm_iav_en : 1;  /* bit[7]  : boost iloop_pfmʹ�ܣ�
                                                         0���ر�iloop_pfm��
                                                          1��ʹ��iloop_pfm�� */
    } reg;
} SOC_SCHARGER_OTG_REG4_UNION;
#endif
#define SOC_SCHARGER_OTG_REG4_otg_ccom2_cmp_START   (0)
#define SOC_SCHARGER_OTG_REG4_otg_ccom2_cmp_END     (1)
#define SOC_SCHARGER_OTG_REG4_otg_ccom1_cmp_START   (2)
#define SOC_SCHARGER_OTG_REG4_otg_ccom1_cmp_END     (3)
#define SOC_SCHARGER_OTG_REG4_otg_rcom_cmp_START    (4)
#define SOC_SCHARGER_OTG_REG4_otg_rcom_cmp_END      (5)
#define SOC_SCHARGER_OTG_REG4_otg_clp_l_set_START   (6)
#define SOC_SCHARGER_OTG_REG4_otg_clp_l_set_END     (6)
#define SOC_SCHARGER_OTG_REG4_otg_pfm_iav_en_START  (7)
#define SOC_SCHARGER_OTG_REG4_otg_pfm_iav_en_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_OTG_REG5_UNION
 �ṹ˵��  : OTG_REG5 �Ĵ����ṹ���塣��ַƫ����:0x85����ֵ:0xA5�����:8
 �Ĵ���˵��: OTG_REG5���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_osc_ckmax : 2;  /* bit[0-1]: �����ŵ������uA����
                                                        00��13��
                                                        01��14��
                                                        10��15�� 11��16�� */
        unsigned char  otg_ccom_iav  : 2;  /* bit[2-3]: boost ������·���ݲ�����
                                                        00��20p��
                                                        01��25p��
                                                        10��30p��
                                                        11��35p�� */
        unsigned char  otg_rcom2_iav : 2;  /* bit[4-5]: boost ������·���貹����
                                                        00��620k����
                                                        01��580k����
                                                        10��440k����
                                                        11��300k���� */
        unsigned char  otg_rcom1_iav : 2;  /* bit[6-7]: boost ������·���貹����
                                                        00��1.2M����
                                                        01��1.6M����
                                                        10��2.0M����
                                                        11��2.4M���� */
    } reg;
} SOC_SCHARGER_OTG_REG5_UNION;
#endif
#define SOC_SCHARGER_OTG_REG5_otg_osc_ckmax_START  (0)
#define SOC_SCHARGER_OTG_REG5_otg_osc_ckmax_END    (1)
#define SOC_SCHARGER_OTG_REG5_otg_ccom_iav_START   (2)
#define SOC_SCHARGER_OTG_REG5_otg_ccom_iav_END     (3)
#define SOC_SCHARGER_OTG_REG5_otg_rcom2_iav_START  (4)
#define SOC_SCHARGER_OTG_REG5_otg_rcom2_iav_END    (5)
#define SOC_SCHARGER_OTG_REG5_otg_rcom1_iav_START  (6)
#define SOC_SCHARGER_OTG_REG5_otg_rcom1_iav_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_OTG_REG6_UNION
 �ṹ˵��  : OTG_REG6 �Ĵ����ṹ���塣��ַƫ����:0x86����ֵ:0x38�����:8
 �Ĵ���˵��: OTG_REG6���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_osc  : 4;  /* bit[0-3]: ����Ƶ�ʣ�MHz����
                                                   0000��2.01��
                                                   0001��1.98��
                                                   0010��1.94��
                                                   0011��1.90��
                                                   0100��1.86��
                                                   0101��1.81��
                                                   0110��1.74��
                                                   0111��1.65��
                                                   1000��1.54��
                                                   1001��1.41��
                                                   1010��1.27��
                                                   1011��1.11��
                                                   1100��0.92��
                                                   1101��0.73��
                                                   1110��0.50��
                                                   1111��0.31�� */
        unsigned char  otg_gm   : 3;  /* bit[4-6]: boost EA��gm�����趨(gm=2/R)��
                                                   000��90k����
                                                   001��80k����
                                                   010��70k����
                                                   011��60k����
                                                   100��40k����
                                                   101��30k����
                                                   110��20k����
                                                   111��10k���� */
        unsigned char  reserved : 1;  /* bit[7]  : ������ */
    } reg;
} SOC_SCHARGER_OTG_REG6_UNION;
#endif
#define SOC_SCHARGER_OTG_REG6_otg_osc_START   (0)
#define SOC_SCHARGER_OTG_REG6_otg_osc_END     (3)
#define SOC_SCHARGER_OTG_REG6_otg_gm_START    (4)
#define SOC_SCHARGER_OTG_REG6_otg_gm_END      (6)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_OTG_REG7_UNION
 �ṹ˵��  : OTG_REG7 �Ĵ����ṹ���塣��ַƫ����:0x87����ֵ:0x69�����:8
 �Ĵ���˵��: OTG_REG7���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_dmd_ofs  : 4;  /* bit[0-3]: boost DMDʧ����ѹ���ڣ�
                                                       0000��20mV (300mA)��
                                                       0001��16mV (240mA)��
                                                       0010��14mV (210mA)��
                                                       0011��12mV (180mA)��
                                                       0100��10mV (150mA)��
                                                       0101��8mV (120mA)��
                                                       0110��6mV (90mA)��
                                                       0111��4mV (60mA)��
                                                       1000��2mV (30mA)��
                                                       1001��0��
                                                       1010��-16mV (-180mA)��
                                                       1011��-32mV (-360mA)��
                                                       1100��-48mV (-540mA)��
                                                       1101��-64mV (-720mA)��
                                                       1110��-128mV (-900mA)��
                                                       1111��-256mV (-1080mA)�� */
        unsigned char  otg_ckmin    : 2;  /* bit[4-5]: NMOS��С��ͨʱ�䣺
                                                       00��40ns��
                                                       01��30ns��
                                                       10��20ns��
                                                       11��15ns�� */
        unsigned char  otg_lmos_ocp : 2;  /* bit[6-7]: boost �Ͷ�MOS������ֵ(A)��
                                                       00��2.8��
                                                       01��3.2��
                                                       10��3.6��
                                                       11��4.0�� */
    } reg;
} SOC_SCHARGER_OTG_REG7_UNION;
#endif
#define SOC_SCHARGER_OTG_REG7_otg_dmd_ofs_START   (0)
#define SOC_SCHARGER_OTG_REG7_otg_dmd_ofs_END     (3)
#define SOC_SCHARGER_OTG_REG7_otg_ckmin_START     (4)
#define SOC_SCHARGER_OTG_REG7_otg_ckmin_END       (5)
#define SOC_SCHARGER_OTG_REG7_otg_lmos_ocp_START  (6)
#define SOC_SCHARGER_OTG_REG7_otg_lmos_ocp_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_OTG_REG8_UNION
 �ṹ˵��  : OTG_REG8 �Ĵ����ṹ���塣��ַƫ����:0x88����ֵ:0x8F�����:8
 �Ĵ���˵��: OTG_REG8���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_down  : 2;  /* bit[0-1]: OTG�µ���ƣ�
                                                    00��
                                                    01��
                                                    10�� 
                                                    11�� */
        unsigned char  otg_hmos  : 1;  /* bit[2]  : OTG �Ϲܿ���ѡ��
                                                    0��ǿ�ƹرգ�
                                                    1���������ء� */
        unsigned char  otg_cmp   : 1;  /* bit[3]  : OTG ���Ƚ�������ѡ��
                                                    0��0.5uA��
                                                    1��2uA�� */
        unsigned char  otg_phase : 2;  /* bit[4-5]: OTG���ѡ��
                                                    00��һ·����
                                                    01����·����
                                                    10��һ����·ȫ����
                                                    10��һ����·ȫ���� */
        unsigned char  otg_rf    : 2;  /* bit[6-7]: ��е���ת��ѹ�迹��
                                                    00��0.5����ʵ��100k������
                                                    01��0.4����ʵ��80k������
                                                    10��0.3����ʵ��60k������
                                                    11��0.2����ʵ��40k������ */
    } reg;
} SOC_SCHARGER_OTG_REG8_UNION;
#endif
#define SOC_SCHARGER_OTG_REG8_otg_down_START   (0)
#define SOC_SCHARGER_OTG_REG8_otg_down_END     (1)
#define SOC_SCHARGER_OTG_REG8_otg_hmos_START   (2)
#define SOC_SCHARGER_OTG_REG8_otg_hmos_END     (2)
#define SOC_SCHARGER_OTG_REG8_otg_cmp_START    (3)
#define SOC_SCHARGER_OTG_REG8_otg_cmp_END      (3)
#define SOC_SCHARGER_OTG_REG8_otg_phase_START  (4)
#define SOC_SCHARGER_OTG_REG8_otg_phase_END    (5)
#define SOC_SCHARGER_OTG_REG8_otg_rf_START     (6)
#define SOC_SCHARGER_OTG_REG8_otg_rf_END       (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_OTG_REG9_UNION
 �ṹ˵��  : OTG_REG9 �Ĵ����ṹ���塣��ַƫ����:0x89����ֵ:0x05�����:8
 �Ĵ���˵��: OTG�ڲ���ʱ���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_delay2 : 2;  /* bit[0-1]: OTG�ڲ���ʱ������
                                                     00��
                                                     01��
                                                     10��
                                                     11�� */
        unsigned char  otg_delay1 : 2;  /* bit[2-3]: OTG�ڲ���ʱ������
                                                     00��
                                                     01��
                                                     10��
                                                     11�� */
        unsigned char  reserved   : 4;  /* bit[4-7]: ������ */
    } reg;
} SOC_SCHARGER_OTG_REG9_UNION;
#endif
#define SOC_SCHARGER_OTG_REG9_otg_delay2_START  (0)
#define SOC_SCHARGER_OTG_REG9_otg_delay2_END    (1)
#define SOC_SCHARGER_OTG_REG9_otg_delay1_START  (2)
#define SOC_SCHARGER_OTG_REG9_otg_delay1_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_OTG_TRIM1_UNION
 �ṹ˵��  : OTG_TRIM1 �Ĵ����ṹ���塣��ַƫ����:0x8A����ֵ:0x00�����:8
 �Ĵ���˵��: OTG_TRIM����1�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_trim1 : 8;  /* bit[0-7]: OTG trim���� */
    } reg;
} SOC_SCHARGER_OTG_TRIM1_UNION;
#endif
#define SOC_SCHARGER_OTG_TRIM1_otg_trim1_START  (0)
#define SOC_SCHARGER_OTG_TRIM1_otg_trim1_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_OTG_TRIM2_UNION
 �ṹ˵��  : OTG_TRIM2 �Ĵ����ṹ���塣��ַƫ����:0x8B����ֵ:0x00�����:8
 �Ĵ���˵��: OTG_TRIM����2�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_trim2 : 8;  /* bit[0-7]: OTG trim���� */
    } reg;
} SOC_SCHARGER_OTG_TRIM2_UNION;
#endif
#define SOC_SCHARGER_OTG_TRIM2_otg_trim2_START  (0)
#define SOC_SCHARGER_OTG_TRIM2_otg_trim2_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_OTG_RESERVE_UNION
 �ṹ˵��  : OTG_RESERVE �Ĵ����ṹ���塣��ַƫ����:0x8C����ֵ:0x00�����:8
 �Ĵ���˵��: OTGԤ��0�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_resved : 8;  /* bit[0-7]: Ԥ���Ĵ��� */
    } reg;
} SOC_SCHARGER_OTG_RESERVE_UNION;
#endif
#define SOC_SCHARGER_OTG_RESERVE_otg_resved_START  (0)
#define SOC_SCHARGER_OTG_RESERVE_otg_resved_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_OTG_RESERVE1_UNION
 �ṹ˵��  : OTG_RESERVE1 �Ĵ����ṹ���塣��ַƫ����:0x8D����ֵ:0x00�����:8
 �Ĵ���˵��: OTGԤ��1�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_resved1 : 8;  /* bit[0-7]: Ԥ���Ĵ��� */
    } reg;
} SOC_SCHARGER_OTG_RESERVE1_UNION;
#endif
#define SOC_SCHARGER_OTG_RESERVE1_otg_resved1_START  (0)
#define SOC_SCHARGER_OTG_RESERVE1_otg_resved1_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_OTG_RESERVE2_UNION
 �ṹ˵��  : OTG_RESERVE2 �Ĵ����ṹ���塣��ַƫ����:0x8E����ֵ:0x00�����:8
 �Ĵ���˵��: OTGԤ��2�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_resved2 : 8;  /* bit[0-7]: Ԥ���Ĵ��� */
    } reg;
} SOC_SCHARGER_OTG_RESERVE2_UNION;
#endif
#define SOC_SCHARGER_OTG_RESERVE2_otg_resved2_START  (0)
#define SOC_SCHARGER_OTG_RESERVE2_otg_resved2_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_CHG_REG0_UNION
 �ṹ˵��  : CHG_REG0 �Ĵ����ṹ���塣��ַƫ����:0x90����ֵ:0x14�����:8
 �Ĵ���˵��: CHG_REG0���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_pre_vchg    : 2;  /* bit[0-1]: Ԥ����ѹ��ֵ��С����λ��
                                                          00��2.8V��
                                                          01��3.0V��
                                                          10��3.1V��
                                                          11��3.2V�� */
        unsigned char  chg_pre_ichg    : 2;  /* bit[2-3]: Ԥ��������С����λ��
                                                          00��100mA��
                                                          01��200mA��
                                                          10��300mA��
                                                          11��400mA�� */
        unsigned char  batfet_ctrl_cfg : 1;  /* bit[4]  : batfet_ctrl���üĴ���
                                                          �üĴ��������ܵ�pwr_rst_n��λ�⣬���ܵ�ģ���͸���������һ���ź�dc_plug_n���ƣ�
                                                          0���ر�batfet��
                                                          1����batfet�� */
        unsigned char  chg_en          : 1;  /* bit[5]  : chargerʹ���źţ�
                                                          0���رգ�
                                                          1��ʹ�ܡ� */
        unsigned char  reserved        : 2;  /* bit[6-7]: ������ */
    } reg;
} SOC_SCHARGER_CHG_REG0_UNION;
#endif
#define SOC_SCHARGER_CHG_REG0_chg_pre_vchg_START     (0)
#define SOC_SCHARGER_CHG_REG0_chg_pre_vchg_END       (1)
#define SOC_SCHARGER_CHG_REG0_chg_pre_ichg_START     (2)
#define SOC_SCHARGER_CHG_REG0_chg_pre_ichg_END       (3)
#define SOC_SCHARGER_CHG_REG0_batfet_ctrl_cfg_START  (4)
#define SOC_SCHARGER_CHG_REG0_batfet_ctrl_cfg_END    (4)
#define SOC_SCHARGER_CHG_REG0_chg_en_START           (5)
#define SOC_SCHARGER_CHG_REG0_chg_en_END             (5)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_CHG_REG1_UNION
 �ṹ˵��  : CHG_REG1 �Ĵ����ṹ���塣��ַƫ����:0x91����ֵ:0x0E�����:8
 �Ĵ���˵��: CHG_REG1���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_fast_ichg : 5;  /* bit[0-4]: ���������С����λ��
                                                        00000��100mA��
                                                        00001��200mA��
                                                        00010��300mA��
                                                        00011��400mA��
                                                        00100��500mA��
                                                        00101��600mA��
                                                        00110��700mA��
                                                        00111��800mA��
                                                        01000��900mA��
                                                        01001��1000mA��
                                                        01010��1200mA��
                                                        01011��1400mA��
                                                        01100��1600mA��
                                                        01101��1800mA��
                                                        01110��2000mA��
                                                        01111��2100mA��
                                                        10000��2200mA��
                                                        10001��2300mA��
                                                        10010��2400mA��
                                                        10011��2500mA��
                                                        10100��2600mA��
                                                        10101��2700mA��
                                                        10110��2800mA��
                                                        10111��2900mA��
                                                        11000��3000mA��
                                                        11001��3200mA��
                                                        11010��3400mA��
                                                        11011��3600mA��
                                                        11100��3800mA��
                                                        11101��4000mA��
                                                        11110��4200mA��
                                                        11111��4500mA�� */
        unsigned char  reserved      : 3;  /* bit[5-7]: ������ */
    } reg;
} SOC_SCHARGER_CHG_REG1_UNION;
#endif
#define SOC_SCHARGER_CHG_REG1_chg_fast_ichg_START  (0)
#define SOC_SCHARGER_CHG_REG1_chg_fast_ichg_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_CHG_REG2_UNION
 �ṹ˵��  : CHG_REG2 �Ĵ����ṹ���塣��ַƫ����:0x92����ֵ:0x5A�����:8
 �Ĵ���˵��: CHG_REG2���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_term_ichg : 3;  /* bit[0-2]: ��ֹ��������ֵ����λ��
                                                        000��50mA��
                                                        001��100mA��
                                                        010��150mA��
                                                        011��200mA��
                                                        100��300mA��
                                                        101��400mA��
                                                        110��500mA��
                                                        111��600mA�� */
        unsigned char  chg_fast_vchg : 4;  /* bit[3-6]: ������ɵ�ѹ��ֵ��С����λ��
                                                        0000��3.8V��
                                                        0001��3.85V��
                                                        0010��3.9V��
                                                        0011��3.95V��
                                                        0100��4V��
                                                        0101��4.05V��
                                                        0110��4.1V��
                                                        0111��4.15V��
                                                        1000��4.2��
                                                        1001��4.25��
                                                        1010��4.3��
                                                        1011��4.35��
                                                        1100��4.4��
                                                        1101��4.45��
                                                        1110��4.5��
                                                        1111��4.5�� */
        unsigned char  reserved      : 1;  /* bit[7]  : ������ */
    } reg;
} SOC_SCHARGER_CHG_REG2_UNION;
#endif
#define SOC_SCHARGER_CHG_REG2_chg_term_ichg_START  (0)
#define SOC_SCHARGER_CHG_REG2_chg_term_ichg_END    (2)
#define SOC_SCHARGER_CHG_REG2_chg_fast_vchg_START  (3)
#define SOC_SCHARGER_CHG_REG2_chg_fast_vchg_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_CHG_REG3_UNION
 �ṹ˵��  : CHG_REG3 �Ĵ����ṹ���塣��ַƫ����:0x93����ֵ:0x40�����:8
 �Ĵ���˵��: CHG_REG3���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_gap_set       : 2;  /* bit[0-1]: SYS to BAT backward voltage gap����λ��
                                                            00��30mV��
                                                            01��10mV��
                                                            10��40mV��
                                                            11��50mV�� */
        unsigned char  chg_fastchg_timer : 2;  /* bit[2-3]: ��䰲ȫ��ʱ����Сʱ����
                                                            00��5 h��
                                                            01��8 h��
                                                            10��12 h��
                                                            11��20 h�� */
        unsigned char  chg_prechg_timer  : 2;  /* bit[4-5]: Ԥ����ʱ�������ӣ���
                                                            00��30min��
                                                            01��45min��
                                                            10��60min��
                                                            11��75min�� */
        unsigned char  chg_vrechg_hys    : 2;  /* bit[6-7]: ���³����͵�ѹ����λ��
                                                            00��50mV��
                                                            01��100mV��
                                                            10��150mV��
                                                            11��200mV�� */
    } reg;
} SOC_SCHARGER_CHG_REG3_UNION;
#endif
#define SOC_SCHARGER_CHG_REG3_chg_gap_set_START        (0)
#define SOC_SCHARGER_CHG_REG3_chg_gap_set_END          (1)
#define SOC_SCHARGER_CHG_REG3_chg_fastchg_timer_START  (2)
#define SOC_SCHARGER_CHG_REG3_chg_fastchg_timer_END    (3)
#define SOC_SCHARGER_CHG_REG3_chg_prechg_timer_START   (4)
#define SOC_SCHARGER_CHG_REG3_chg_prechg_timer_END     (5)
#define SOC_SCHARGER_CHG_REG3_chg_vrechg_hys_START     (6)
#define SOC_SCHARGER_CHG_REG3_chg_vrechg_hys_END       (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_CHG_REG4_UNION
 �ṹ˵��  : CHG_REG4 �Ĵ����ṹ���塣��ַƫ����:0x94����ֵ:0x04�����:8
 �Ĵ���˵��: CHG_REG4���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_bat_open     : 1;  /* bit[0]  : ��ز���λָʾ��
                                                           0�������λ��
                                                           1����ز���λ�� */
        unsigned char  chg_clk_div2_shd : 1;  /* bit[1]  : ��䰲ȫ��ʱ�����ȵ�����DPM�����зŻ�2��������������λ��
                                                           0��2X���ܲ����Σ�
                                                           1��2X�������Ρ� */
        unsigned char  chg_en_term      : 1;  /* bit[2]  : ��ֹ������λ��
                                                           0��Disabled��
                                                           1��Enabled�� */
        unsigned char  reserved         : 5;  /* bit[3-7]: ������ */
    } reg;
} SOC_SCHARGER_CHG_REG4_UNION;
#endif
#define SOC_SCHARGER_CHG_REG4_chg_bat_open_START      (0)
#define SOC_SCHARGER_CHG_REG4_chg_bat_open_END        (0)
#define SOC_SCHARGER_CHG_REG4_chg_clk_div2_shd_START  (1)
#define SOC_SCHARGER_CHG_REG4_chg_clk_div2_shd_END    (1)
#define SOC_SCHARGER_CHG_REG4_chg_en_term_START       (2)
#define SOC_SCHARGER_CHG_REG4_chg_en_term_END         (2)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_CHG_REG5_UNION
 �ṹ˵��  : CHG_REG5 �Ĵ����ṹ���塣��ַƫ����:0x95����ֵ:0x00�����:8
 �Ĵ���˵��: CHG_REG5���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_vclamp_set : 3;  /* bit[0-2]: ���ͨ�����貹��ǯλ��ѹ��
                                                         000��0mV��
                                                         001��50mV��
                                                         010��100mV��
                                                         011��150mV��
                                                         000��200mV��
                                                         101��250mV��
                                                         110��300mV��
                                                         111��350mV�� */
        unsigned char  chg_ir_set     : 3;  /* bit[3-5]: ���ͨ�����貹����
                                                         000��0mohm��
                                                         001��15mohm��
                                                         010��30mohm��
                                                         011��45mohm��
                                                         100��60mohm��
                                                         101��75mohm��
                                                         110��95mohm��
                                                         111��110mohm�� */
        unsigned char  reserved       : 2;  /* bit[6-7]: ������ */
    } reg;
} SOC_SCHARGER_CHG_REG5_UNION;
#endif
#define SOC_SCHARGER_CHG_REG5_chg_vclamp_set_START  (0)
#define SOC_SCHARGER_CHG_REG5_chg_vclamp_set_END    (2)
#define SOC_SCHARGER_CHG_REG5_chg_ir_set_START      (3)
#define SOC_SCHARGER_CHG_REG5_chg_ir_set_END        (5)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_CHG_VRES_SEL_UNION
 �ṹ˵��  : CHG_VRES_SEL �Ĵ����ṹ���塣��ַƫ����:0x96����ֵ:0x05�����:8
 �Ĵ���˵��: CHARGER��·����mos������ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_vres2_sel : 2;  /* bit[0-1]: charger��·����mos������� */
        unsigned char  chg_vres1_sel : 2;  /* bit[2-3]: charger��·����mos������� */
        unsigned char  reserved      : 4;  /* bit[4-7]: ������ */
    } reg;
} SOC_SCHARGER_CHG_VRES_SEL_UNION;
#endif
#define SOC_SCHARGER_CHG_VRES_SEL_chg_vres2_sel_START  (0)
#define SOC_SCHARGER_CHG_VRES_SEL_chg_vres2_sel_END    (1)
#define SOC_SCHARGER_CHG_VRES_SEL_chg_vres1_sel_START  (2)
#define SOC_SCHARGER_CHG_VRES_SEL_chg_vres1_sel_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_CHG_CAP_SEL_UNION
 �ṹ˵��  : CHG_CAP_SEL �Ĵ����ṹ���塣��ַƫ����:0x97����ֵ:0x55�����:8
 �Ĵ���˵��: CHARGER��·�������ݵ��ڡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_cap4_sel : 2;  /* bit[0-1]: charger��·�������ݵ��ڣ�
                                                       00��3pF��
                                                       01��6pF��
                                                       10��9pF��
                                                       11��12pF�� */
        unsigned char  chg_cap3_sel : 2;  /* bit[2-3]: charger��·�������ݵ��ڣ�
                                                       00��4.4pF��
                                                       01��8.8pF��
                                                       10��13.2pF��
                                                       11��15.6pF�� */
        unsigned char  chg_cap2_sel : 2;  /* bit[4-5]: charger��·�������ݵ��ڣ�
                                                       00��2.2pF��
                                                       01��4.4pF��
                                                       10��6.6pF��
                                                       11��8.8pF�� */
        unsigned char  chg_cap1_sel : 2;  /* bit[6-7]: charger��·�������ݵ��ڣ�
                                                       00��1.1pF��
                                                       01��2.2pF��
                                                       10��3.3pF��
                                                       11��4.4pF�� */
    } reg;
} SOC_SCHARGER_CHG_CAP_SEL_UNION;
#endif
#define SOC_SCHARGER_CHG_CAP_SEL_chg_cap4_sel_START  (0)
#define SOC_SCHARGER_CHG_CAP_SEL_chg_cap4_sel_END    (1)
#define SOC_SCHARGER_CHG_CAP_SEL_chg_cap3_sel_START  (2)
#define SOC_SCHARGER_CHG_CAP_SEL_chg_cap3_sel_END    (3)
#define SOC_SCHARGER_CHG_CAP_SEL_chg_cap2_sel_START  (4)
#define SOC_SCHARGER_CHG_CAP_SEL_chg_cap2_sel_END    (5)
#define SOC_SCHARGER_CHG_CAP_SEL_chg_cap1_sel_START  (6)
#define SOC_SCHARGER_CHG_CAP_SEL_chg_cap1_sel_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_CHG_REG6_UNION
 �ṹ˵��  : CHG_REG6 �Ĵ����ṹ���塣��ַƫ����:0x98����ֵ:0x40�����:8
 �Ĵ���˵��: CHG_REG6���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_ios_adj_ir : 5;  /* bit[0-4]: ���������ʧ��У����
                                                         00000��0mA��
                                                         00001��-25mA��
                                                         00010��-50mA��
                                                         00011��-75mA��
                                                         ��
                                                         ��
                                                         01111��-375mA��
                                                         10000��+25mA��
                                                         10001��+50mA��
                                                         10010��+75mA��
                                                         10011��+100mA��
                                                         ��
                                                         ��
                                                         11111��+400mA�� */
        unsigned char  chg_rechg_time : 2;  /* bit[5-6]: ���³��ģʽȥ��ʱ������λ��
                                                         00��0.1s��
                                                         01��1s��
                                                         10��2s��
                                                         11��4s�� */
        unsigned char  reserved       : 1;  /* bit[7]  : ������ */
    } reg;
} SOC_SCHARGER_CHG_REG6_UNION;
#endif
#define SOC_SCHARGER_CHG_REG6_chg_ios_adj_ir_START  (0)
#define SOC_SCHARGER_CHG_REG6_chg_ios_adj_ir_END    (4)
#define SOC_SCHARGER_CHG_REG6_chg_rechg_time_START  (5)
#define SOC_SCHARGER_CHG_REG6_chg_rechg_time_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_CHG_REG7_UNION
 �ṹ˵��  : CHG_REG7 �Ĵ����ṹ���塣��ַƫ����:0x99����ֵ:0x00�����:8
 �Ĵ���˵��: CHG_REG7���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_iscale_adj_gap : 3;  /* bit[0-2]: ������������У����
                                                             000��1X��
                                                             001��1.042X��
                                                             010��1.087X��
                                                             011��1.136X��
                                                             100��0.962X��
                                                             101��0.926X��
                                                             110��0.893X��
                                                             111��0.862X�� */
        unsigned char  chg_iscale_adj_ir  : 4;  /* bit[3-6]: ������������У����
                                                             0000��1X��
                                                             0001��1.020X��
                                                             0010��1.042X��
                                                             0011��1.064X��
                                                             0100��1.087X��
                                                             0101��1.111X��
                                                             0110��1.136X��
                                                             0111��1.163X��
                                                             1000��0.980X��
                                                             1001��0.962X��
                                                             1010��0.943X��
                                                             1011��0.926X��
                                                             1100��0.909X��
                                                             1101��0.893X��
                                                             1110��0.877X��
                                                             1111��0.862X�� */
        unsigned char  reserved           : 1;  /* bit[7]  : ������ */
    } reg;
} SOC_SCHARGER_CHG_REG7_UNION;
#endif
#define SOC_SCHARGER_CHG_REG7_chg_iscale_adj_gap_START  (0)
#define SOC_SCHARGER_CHG_REG7_chg_iscale_adj_gap_END    (2)
#define SOC_SCHARGER_CHG_REG7_chg_iscale_adj_ir_START   (3)
#define SOC_SCHARGER_CHG_REG7_chg_iscale_adj_ir_END     (6)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_CHG_REG8_UNION
 �ṹ˵��  : CHG_REG8 �Ĵ����ṹ���塣��ַƫ����:0x9A����ֵ:0x00�����:8
 �Ĵ���˵��: CHG_REG8���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_ios_adj_gap : 5;  /* bit[0-4]: ���������ʧ��У����
                                                          00000��0mA��
                                                          00001��-25mA��
                                                          00010��-50mA��
                                                          00011��-75mA��
                                                          ��
                                                          ��
                                                          01111��-375mA��
                                                          10000��+25mA��
                                                          10001��+50mA��
                                                          10010��+75mA��
                                                          10011��+100mA��
                                                          ��
                                                          ��
                                                          11111��+400mA�� */
        unsigned char  reserved        : 3;  /* bit[5-7]: ������ */
    } reg;
} SOC_SCHARGER_CHG_REG8_UNION;
#endif
#define SOC_SCHARGER_CHG_REG8_chg_ios_adj_gap_START  (0)
#define SOC_SCHARGER_CHG_REG8_chg_ios_adj_gap_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_CHG_REG9_UNION
 �ṹ˵��  : CHG_REG9 �Ĵ����ṹ���塣��ַƫ����:0x9B����ֵ:0x02�����:8
 �Ĵ���˵��: CHG_REG9���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_cp_src_sel : 1;  /* bit[0]  : charge pump�����Դѡ��
                                                         0��ѡ��battery��
                                                         1��ѡ��avdd_bas�� */
        unsigned char  chg_iref_clamp : 2;  /* bit[1-2]: �������ο���ѹǯλ��
                                                         00��100mV��
                                                         01��150mV��
                                                         10��200mV��
                                                         11��250mV�� */
        unsigned char  chg_ocp_shd    : 1;  /* bit[3]  : �ŵ����ocp��������λ��
                                                         0�������Σ�
                                                         1�����Ρ� */
        unsigned char  chg_cv_adj     : 4;  /* bit[4-7]: cv�Ĵ����޵�λ��
                                                         0000��0mV��
                                                         0001��-12.5mV��
                                                         0010��-25mV��
                                                         0011��-37.5mV��
                                                         0100��-50mV��
                                                         0101��-62.5mV��
                                                         0110��-75mV��
                                                         0111��-87.5mV��
                                                         1000��+12.5mV��
                                                         1001��+25mV��
                                                         1010��+37.5mV��
                                                         1011��+50mV��
                                                         1100��+62.5mV��
                                                         1101��+75mV��
                                                         1110��+87.5mV��
                                                         1111��+100mV�� */
    } reg;
} SOC_SCHARGER_CHG_REG9_UNION;
#endif
#define SOC_SCHARGER_CHG_REG9_chg_cp_src_sel_START  (0)
#define SOC_SCHARGER_CHG_REG9_chg_cp_src_sel_END    (0)
#define SOC_SCHARGER_CHG_REG9_chg_iref_clamp_START  (1)
#define SOC_SCHARGER_CHG_REG9_chg_iref_clamp_END    (2)
#define SOC_SCHARGER_CHG_REG9_chg_ocp_shd_START     (3)
#define SOC_SCHARGER_CHG_REG9_chg_ocp_shd_END       (3)
#define SOC_SCHARGER_CHG_REG9_chg_cv_adj_START      (4)
#define SOC_SCHARGER_CHG_REG9_chg_cv_adj_END        (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_CHG_RESVI1_UNION
 �ṹ˵��  : CHG_RESVI1 �Ĵ����ṹ���塣��ַƫ����:0x9C����ֵ:0x00�����:8
 �Ĵ���˵��: CHG_RESVI1Ԥ���Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_resvi1 : 8;  /* bit[0-7]: Ԥ���Ĵ��� */
    } reg;
} SOC_SCHARGER_CHG_RESVI1_UNION;
#endif
#define SOC_SCHARGER_CHG_RESVI1_chg_resvi1_START  (0)
#define SOC_SCHARGER_CHG_RESVI1_chg_resvi1_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_CHG_RESVI2_UNION
 �ṹ˵��  : CHG_RESVI2 �Ĵ����ṹ���塣��ַƫ����:0x9D����ֵ:0x00�����:8
 �Ĵ���˵��: CHG_RESVI2Ԥ���Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_resvi2 : 8;  /* bit[0-7]: Ԥ���Ĵ��� */
    } reg;
} SOC_SCHARGER_CHG_RESVI2_UNION;
#endif
#define SOC_SCHARGER_CHG_RESVI2_chg_resvi2_START  (0)
#define SOC_SCHARGER_CHG_RESVI2_chg_resvi2_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_CHG_RESVO1_UNION
 �ṹ˵��  : CHG_RESVO1 �Ĵ����ṹ���塣��ַƫ����:0x9E����ֵ:0x00�����:8
 �Ĵ���˵��: CHG_RESVO1Ԥ���Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_resvo1 : 8;  /* bit[0-7]: <7:1>Ԥ���Ĵ���
                                                     <0>400mA���¿�䵵λģʽѡ��
                                                     0:IRģʽ��
                                                     1��GAPģʽ�� */
    } reg;
} SOC_SCHARGER_CHG_RESVO1_UNION;
#endif
#define SOC_SCHARGER_CHG_RESVO1_chg_resvo1_START  (0)
#define SOC_SCHARGER_CHG_RESVO1_chg_resvo1_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_CHG_RESVO2_UNION
 �ṹ˵��  : CHG_RESVO2 �Ĵ����ṹ���塣��ַƫ����:0x9F����ֵ:0x00�����:8
 �Ĵ���˵��: CHG_RESVO2Ԥ���Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_resvo2 : 8;  /* bit[0-7]: Ԥ���Ĵ��� */
    } reg;
} SOC_SCHARGER_CHG_RESVO2_UNION;
#endif
#define SOC_SCHARGER_CHG_RESVO2_chg_resvo2_START  (0)
#define SOC_SCHARGER_CHG_RESVO2_chg_resvo2_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_DET_TOP_REG0_UNION
 �ṹ˵��  : DET_TOP_REG0 �Ĵ����ṹ���塣��ַƫ����:0xA0����ֵ:0x02�����:8
 �Ĵ���˵��: DET_TOP_REG0���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  bat_gd_shield : 1;  /* bit[0]  : ǿ��ʹbat_gdΪ�ߣ�
                                                        0����ǿ�ƣ���ģ���ж�bat_gd�Ƿ�Ϊ�ߵ�ƽ��
                                                        1��ǿ��ʹbat_gdΪ�ߵ�ƽ�� */
        unsigned char  bat_gd_sel    : 1;  /* bit[1]  : OTG�����ĵ�ص�ѹ�жϵ�λѡ��
                                                        0��3V��
                                                        1��2.8V�� */
        unsigned char  slp_vset      : 1;  /* bit[2]  : sleep���˳��ĵ�λѡ��
                                                        0��sleep���˳�Ϊ80mV��
                                                        1��sleep���˳�Ϊ120mV�� */
        unsigned char  vbus_vset     : 2;  /* bit[3-4]: �����������ѹ��λ���ã�
                                                        00��5V��
                                                        01��9V��
                                                        10&amp;11��12V�� */
        unsigned char  ts_ctrl       : 1;  /* bit[5]  : ���Ƶ���¶ȼ��ģ�飺
                                                        0���رգ�
                                                        1�������� */
        unsigned char  reserved      : 2;  /* bit[6-7]: ������ */
    } reg;
} SOC_SCHARGER_DET_TOP_REG0_UNION;
#endif
#define SOC_SCHARGER_DET_TOP_REG0_bat_gd_shield_START  (0)
#define SOC_SCHARGER_DET_TOP_REG0_bat_gd_shield_END    (0)
#define SOC_SCHARGER_DET_TOP_REG0_bat_gd_sel_START     (1)
#define SOC_SCHARGER_DET_TOP_REG0_bat_gd_sel_END       (1)
#define SOC_SCHARGER_DET_TOP_REG0_slp_vset_START       (2)
#define SOC_SCHARGER_DET_TOP_REG0_slp_vset_END         (2)
#define SOC_SCHARGER_DET_TOP_REG0_vbus_vset_START      (3)
#define SOC_SCHARGER_DET_TOP_REG0_vbus_vset_END        (4)
#define SOC_SCHARGER_DET_TOP_REG0_ts_ctrl_START        (5)
#define SOC_SCHARGER_DET_TOP_REG0_ts_ctrl_END          (5)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_DET_TOP_REG1_UNION
 �ṹ˵��  : DET_TOP_REG1 �Ĵ����ṹ���塣��ַƫ����:0xA1����ֵ:0x0A�����:8
 �Ĵ���˵��: DET_TOP_REG1���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_hot_hsys  : 2;  /* bit[0-1]: ��ع��ȼ��Ļ����¶ȵ�����
                                                        00��1%��
                                                        01��2%��
                                                        10��3%��
                                                        11��4%�� */
        unsigned char  chg_cold_hsys : 2;  /* bit[2-3]: ��ع�����Ļ����¶ȵ�����
                                                        00��1%��
                                                        01��2%��
                                                        10��3%��
                                                        11��4%�� */
        unsigned char  reserved      : 4;  /* bit[4-7]: ������ */
    } reg;
} SOC_SCHARGER_DET_TOP_REG1_UNION;
#endif
#define SOC_SCHARGER_DET_TOP_REG1_chg_hot_hsys_START   (0)
#define SOC_SCHARGER_DET_TOP_REG1_chg_hot_hsys_END     (1)
#define SOC_SCHARGER_DET_TOP_REG1_chg_cold_hsys_START  (2)
#define SOC_SCHARGER_DET_TOP_REG1_chg_cold_hsys_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_THSD_ADJ_UNION
 �ṹ˵��  : THSD_ADJ �Ĵ����ṹ���塣��ַƫ����:0xA2����ֵ:0x02�����:8
 �Ĵ���˵��: THSD���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  thsd_treg_set : 2;  /* bit[0-1]: �ȵ����¶ȵ�λѡ��
                                                        00��60�ȣ�
                                                        01��80�ȣ�
                                                        10��100�ȣ�
                                                        11��120�ȡ� */
        unsigned char  reserved      : 6;  /* bit[2-7]: ������ */
    } reg;
} SOC_SCHARGER_THSD_ADJ_UNION;
#endif
#define SOC_SCHARGER_THSD_ADJ_thsd_treg_set_START  (0)
#define SOC_SCHARGER_THSD_ADJ_thsd_treg_set_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_SCHG_LOGIC_CTRL_UNION
 �ṹ˵��  : SCHG_LOGIC_CTRL �Ĵ����ṹ���塣��ַƫ����:0xA3����ֵ:0x00�����:8
 �Ĵ���˵��: SCHG_LOGIC���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_enb        : 1;  /* bit[0]  : buckǿ�ƹرտ��ƣ�
                                                          0��buckʹ����ģ���Զ����ƣ�
                                                          1��buckǿ�ƹرա� */
        unsigned char  timer_test      : 1;  /* bit[1]  : ��ʱ������ģʽ��
                                                          0��оƬ��������ģʽ��
                                                          1������ģʽ��ͨ�����ź�ѡ���ʱʱ��̵ļ�ʱ��������ԡ� */
        unsigned char  regn_ocp_shield : 1;  /* bit[2]  : regn ocp�źŵ������źţ�
                                                          0��������regn_ocp��
                                                          1������regn_ocp�� */
        unsigned char  reserved        : 5;  /* bit[3-7]: ������ */
    } reg;
} SOC_SCHARGER_SCHG_LOGIC_CTRL_UNION;
#endif
#define SOC_SCHARGER_SCHG_LOGIC_CTRL_buck_enb_START         (0)
#define SOC_SCHARGER_SCHG_LOGIC_CTRL_buck_enb_END           (0)
#define SOC_SCHARGER_SCHG_LOGIC_CTRL_timer_test_START       (1)
#define SOC_SCHARGER_SCHG_LOGIC_CTRL_timer_test_END         (1)
#define SOC_SCHARGER_SCHG_LOGIC_CTRL_regn_ocp_shield_START  (2)
#define SOC_SCHARGER_SCHG_LOGIC_CTRL_regn_ocp_shield_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_BLOCK_CTRL_UNION
 �ṹ˵��  : BLOCK_CTRL �Ĵ����ṹ���塣��ַƫ����:0xA4����ֵ:0x00�����:8
 �Ĵ���˵��: BLOCK���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_500ma_mos : 1;  /* bit[0]  : OTG 500mA����ʱBLOCK�ܱ���ѡ��
                                                        0��20m ohm��ͨ�迹��
                                                        1��100m ohm��ͨ�迹�� */
        unsigned char  gate_gnd_ctrl : 1;  /* bit[1]  : BLOCK������ѡ��
                                                        0��block gate����vbus��
                                                        1��block gate����gnd�� */
        unsigned char  reserved      : 6;  /* bit[2-7]: ������ */
    } reg;
} SOC_SCHARGER_BLOCK_CTRL_UNION;
#endif
#define SOC_SCHARGER_BLOCK_CTRL_otg_500ma_mos_START  (0)
#define SOC_SCHARGER_BLOCK_CTRL_otg_500ma_mos_END    (0)
#define SOC_SCHARGER_BLOCK_CTRL_gate_gnd_ctrl_START  (1)
#define SOC_SCHARGER_BLOCK_CTRL_gate_gnd_ctrl_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_REF_TOP_CTRL_UNION
 �ṹ˵��  : REF_TOP_CTRL �Ĵ����ṹ���塣��ַƫ����:0xA5����ֵ:0x80�����:8
 �Ĵ���˵��: REF_TOP���ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ref_trim        : 7;  /* bit[0-6]: ��δ�޵���оƬ���б�̣��Ա�����ʵ�����޵���׼��ѹVREF�� */
        unsigned char  ibias_switch_en : 1;  /* bit[7]  : 0����ʹ�ܵ����л����ܣ�
                                                          1��ʹ�ܵ����л����ܡ� */
    } reg;
} SOC_SCHARGER_REF_TOP_CTRL_UNION;
#endif
#define SOC_SCHARGER_REF_TOP_CTRL_ref_trim_START         (0)
#define SOC_SCHARGER_REF_TOP_CTRL_ref_trim_END           (6)
#define SOC_SCHARGER_REF_TOP_CTRL_ibias_switch_en_START  (7)
#define SOC_SCHARGER_REF_TOP_CTRL_ibias_switch_en_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_ADC_CTRL_UNION
 �ṹ˵��  : ADC_CTRL �Ĵ����ṹ���塣��ַƫ����:0xB0����ֵ:0x00�����:8
 �Ĵ���˵��: ADC���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_ch_sel   : 2;  /* bit[0-1]: HKADC ����ͨ��ѡ��Ĵ�����Ĭ��0�� */
        unsigned char  hkadc_div_freq : 1;  /* bit[2]  : HKADC����Ƶ�ʽ�Ƶ��Ĭ��0������Ƶ��֧��5K �����ʣ� */
        unsigned char  hkadc_reset    : 1;  /* bit[3]  : HKADC�ڲ� �߼���λ���ƣ�
                                                         0������λ��
                                                         1��ǿ�Ƹ�λ�� */
        unsigned char  hkadc_en       : 1;  /* bit[4]  : HKADCʹ�ܣ���Ĭ��0��
                                                         0����������
                                                         1�������� */
        unsigned char  reserved       : 3;  /* bit[5-7]: ������ */
    } reg;
} SOC_SCHARGER_ADC_CTRL_UNION;
#endif
#define SOC_SCHARGER_ADC_CTRL_hkadc_ch_sel_START    (0)
#define SOC_SCHARGER_ADC_CTRL_hkadc_ch_sel_END      (1)
#define SOC_SCHARGER_ADC_CTRL_hkadc_div_freq_START  (2)
#define SOC_SCHARGER_ADC_CTRL_hkadc_div_freq_END    (2)
#define SOC_SCHARGER_ADC_CTRL_hkadc_reset_START     (3)
#define SOC_SCHARGER_ADC_CTRL_hkadc_reset_END       (3)
#define SOC_SCHARGER_ADC_CTRL_hkadc_en_START        (4)
#define SOC_SCHARGER_ADC_CTRL_hkadc_en_END          (4)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_ADC_START_UNION
 �ṹ˵��  : ADC_START �Ĵ����ṹ���塣��ַƫ����:0xB1����ֵ:0x00�����:8
 �Ĵ���˵��: ADCת����ʼ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_start    : 1;  /* bit[0]  : HKADC�������üĴ�����Ĭ��0��дһ�ε�ַ0xB1������0��1�����üĴ�������һ�η�ת������һ������ת��
                                                         ��ע����ֹ��HKADC����hkadc_start��ת��������(hkadc_valid=0)�ظ�����hkadc_start�źţ�����hkadc�ڲ��߼��ᷢ�����ң���Ҫ���¿���hkadc�����hkadc_reset�á�1��ǿ���߼���λ��
                                                         ע����Ҫ���ٳ���3��hkadc����ʱ��clk���ڣ�����ƵΪ3��125kʱ�ӣ���ƵΪ3��62.5kʱ�ӣ��������� */
        unsigned char  hkadc_reserved : 7;  /* bit[1-7]: ������ */
    } reg;
} SOC_SCHARGER_ADC_START_UNION;
#endif
#define SOC_SCHARGER_ADC_START_hkadc_start_START     (0)
#define SOC_SCHARGER_ADC_START_hkadc_start_END       (0)
#define SOC_SCHARGER_ADC_START_hkadc_reserved_START  (1)
#define SOC_SCHARGER_ADC_START_hkadc_reserved_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_ADC_CONV_STATUS_UNION
 �ṹ˵��  : ADC_CONV_STATUS �Ĵ����ṹ���塣��ַƫ����:0xB2����ֵ:0x00�����:8
 �Ĵ���˵��: ADCת��״ָ̬ʾ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_valid : 1;  /* bit[0]  : HKADC״̬����Ĵ�����
                                                      0��ת�������У�
                                                      1��ת����ϡ�
                                                      (ע����bit��ת����ʼʱ�������ͣ���ת�������󣬱�ɡ�1�������ҡ�1��һֱ��������һ��ת����ʼ) */
        unsigned char  reserved    : 7;  /* bit[1-7]: ������ */
    } reg;
} SOC_SCHARGER_ADC_CONV_STATUS_UNION;
#endif
#define SOC_SCHARGER_ADC_CONV_STATUS_hkadc_valid_START  (0)
#define SOC_SCHARGER_ADC_CONV_STATUS_hkadc_valid_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_ADC_DATA1_UNION
 �ṹ˵��  : ADC_DATA1 �Ĵ����ṹ���塣��ַƫ����:0xB3����ֵ:0x00�����:8
 �Ĵ���˵��: ADCת�������λ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_data11_8 : 4;  /* bit[0-3]: ADCת�������4λbit[11:8]�� */
        unsigned char  reserved       : 4;  /* bit[4-7]: ������ */
    } reg;
} SOC_SCHARGER_ADC_DATA1_UNION;
#endif
#define SOC_SCHARGER_ADC_DATA1_hkadc_data11_8_START  (0)
#define SOC_SCHARGER_ADC_DATA1_hkadc_data11_8_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_ADC_DATA0_UNION
 �ṹ˵��  : ADC_DATA0 �Ĵ����ṹ���塣��ַƫ����:0xB4����ֵ:0x00�����:8
 �Ĵ���˵��: ADCת�������λ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_data7_0 : 8;  /* bit[0-7]: ADCת�������8λbit[7:0]�� */
    } reg;
} SOC_SCHARGER_ADC_DATA0_UNION;
#endif
#define SOC_SCHARGER_ADC_DATA0_hkadc_data7_0_START  (0)
#define SOC_SCHARGER_ADC_DATA0_hkadc_data7_0_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_ADC_IBIAS_SEL_UNION
 �ṹ˵��  : ADC_IBIAS_SEL �Ĵ����ṹ���塣��ַƫ����:0xB5����ֵ:0x00�����:8
 �Ĵ���˵��: HKADC����IBIAS�������üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_ibias_sel : 8;  /* bit[0-7]: HKADC����ibias�������üĴ�����Ĭ��0 */
    } reg;
} SOC_SCHARGER_ADC_IBIAS_SEL_UNION;
#endif
#define SOC_SCHARGER_ADC_IBIAS_SEL_hkadc_ibias_sel_START  (0)
#define SOC_SCHARGER_ADC_IBIAS_SEL_hkadc_ibias_sel_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_EFUSE_REG0_UNION
 �ṹ˵��  : EFUSE_REG0 �Ĵ����ṹ���塣��ַƫ����:0xC0����ֵ:0x00�����:8
 �Ĵ���˵��: EFUSE����0�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_por_int_ro : 1;  /* bit[0]  : efuse_por_int״̬�Ĵ�����
                                                           0��eFuse������
                                                           1���Զ���64bits eFuseֵ���ص��Ĵ������档 */
        unsigned char  efuse_state      : 4;  /* bit[1-4]: EFUSE_CTRL״̬��״̬�Ĵ����� */
        unsigned char  reserved         : 3;  /* bit[5-7]: ������ */
    } reg;
} SOC_SCHARGER_EFUSE_REG0_UNION;
#endif
#define SOC_SCHARGER_EFUSE_REG0_efuse_por_int_ro_START  (0)
#define SOC_SCHARGER_EFUSE_REG0_efuse_por_int_ro_END    (0)
#define SOC_SCHARGER_EFUSE_REG0_efuse_state_START       (1)
#define SOC_SCHARGER_EFUSE_REG0_efuse_state_END         (4)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_EFUSE_REG1_UNION
 �ṹ˵��  : EFUSE_REG1 �Ĵ����ṹ���塣��ַƫ����:0xC1����ֵ:0x02�����:8
 �Ĵ���˵��: EFUSE����1�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_nr_cfg     : 1;  /* bit[0]: efuse_nr�źſ��ƼĴ��� */
        unsigned char  efuse_pgenb_cfg  : 1;  /* bit[1]: efuse_pgenb�źſ��ƼĴ��� */
        unsigned char  efuse_strobe_cfg : 1;  /* bit[2]: efuseд�����źŵ����� */
        unsigned char  efuse_rd_ctrl    : 1;  /* bit[3]: EFUSE�����ƼĴ����� */
        unsigned char  efuse_inctrl_sel : 1;  /* bit[4]: 0��EFUSE�ı���ź���оƬ�����Զ����ɣ��ڲ��Զ�����
                                                         1��EFUSE�ı��ʱ���ɼĴ����������ɣ��ڲ��ֶ����� */
        unsigned char  efuse_prog_sel   : 1;  /* bit[5]: 0��EFUSE�ı��ʱ����оƬ�ڲ�������
                                                         1��EFUSE�ı��ʱ�����ⲿD+�ܽ���ϡ� */
        unsigned char  efuse_prog_int   : 1;  /* bit[6]: efuse��̿����źš�
                                                         0��eFuse����̣�
                                                         1��eFuse��ʼ��̡� */
        unsigned char  reserved         : 1;  /* bit[7]: ������ */
    } reg;
} SOC_SCHARGER_EFUSE_REG1_UNION;
#endif
#define SOC_SCHARGER_EFUSE_REG1_efuse_nr_cfg_START      (0)
#define SOC_SCHARGER_EFUSE_REG1_efuse_nr_cfg_END        (0)
#define SOC_SCHARGER_EFUSE_REG1_efuse_pgenb_cfg_START   (1)
#define SOC_SCHARGER_EFUSE_REG1_efuse_pgenb_cfg_END     (1)
#define SOC_SCHARGER_EFUSE_REG1_efuse_strobe_cfg_START  (2)
#define SOC_SCHARGER_EFUSE_REG1_efuse_strobe_cfg_END    (2)
#define SOC_SCHARGER_EFUSE_REG1_efuse_rd_ctrl_START     (3)
#define SOC_SCHARGER_EFUSE_REG1_efuse_rd_ctrl_END       (3)
#define SOC_SCHARGER_EFUSE_REG1_efuse_inctrl_sel_START  (4)
#define SOC_SCHARGER_EFUSE_REG1_efuse_inctrl_sel_END    (4)
#define SOC_SCHARGER_EFUSE_REG1_efuse_prog_sel_START    (5)
#define SOC_SCHARGER_EFUSE_REG1_efuse_prog_sel_END      (5)
#define SOC_SCHARGER_EFUSE_REG1_efuse_prog_int_START    (6)
#define SOC_SCHARGER_EFUSE_REG1_efuse_prog_int_END      (6)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_EFUSE_WE0_UNION
 �ṹ˵��  : EFUSE_WE0 �Ĵ����ṹ���塣��ַƫ����:0xC2����ֵ:0x00�����:8
 �Ĵ���˵��: EFUSE��ַ�Ĵ�����Ӧ��ַ[7:0]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_we0_cfg : 8;  /* bit[0-7]: efuse��ַ�Ĵ�����Ӧ��ַwe0[7:0]�� */
    } reg;
} SOC_SCHARGER_EFUSE_WE0_UNION;
#endif
#define SOC_SCHARGER_EFUSE_WE0_efuse_we0_cfg_START  (0)
#define SOC_SCHARGER_EFUSE_WE0_efuse_we0_cfg_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_EFUSE_WE1_UNION
 �ṹ˵��  : EFUSE_WE1 �Ĵ����ṹ���塣��ַƫ����:0xC3����ֵ:0x00�����:8
 �Ĵ���˵��: EFUSE��ַ�Ĵ�����Ӧ��ַ[15:8]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_we1_cfg : 8;  /* bit[0-7]: efuse��ַ�Ĵ�����Ӧ��ַwe1[15:8] */
    } reg;
} SOC_SCHARGER_EFUSE_WE1_UNION;
#endif
#define SOC_SCHARGER_EFUSE_WE1_efuse_we1_cfg_START  (0)
#define SOC_SCHARGER_EFUSE_WE1_efuse_we1_cfg_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_EFUSE_WE2_UNION
 �ṹ˵��  : EFUSE_WE2 �Ĵ����ṹ���塣��ַƫ����:0xC4����ֵ:0x00�����:8
 �Ĵ���˵��: EFUSE��ַ�Ĵ�����Ӧ��ַ[23:16]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_we2_cfg : 8;  /* bit[0-7]: efuse��ַ�Ĵ�����Ӧ��ַwe2[23:16] */
    } reg;
} SOC_SCHARGER_EFUSE_WE2_UNION;
#endif
#define SOC_SCHARGER_EFUSE_WE2_efuse_we2_cfg_START  (0)
#define SOC_SCHARGER_EFUSE_WE2_efuse_we2_cfg_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_EFUSE_WE3_UNION
 �ṹ˵��  : EFUSE_WE3 �Ĵ����ṹ���塣��ַƫ����:0xC5����ֵ:0x00�����:8
 �Ĵ���˵��: EFUSE��ַ�Ĵ�����Ӧ��ַ[31:24]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_we3_cfg : 8;  /* bit[0-7]: efuse��ַ�Ĵ�����Ӧ��ַwe3[31:24] */
    } reg;
} SOC_SCHARGER_EFUSE_WE3_UNION;
#endif
#define SOC_SCHARGER_EFUSE_WE3_efuse_we3_cfg_START  (0)
#define SOC_SCHARGER_EFUSE_WE3_efuse_we3_cfg_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_EFUSE_WE4_UNION
 �ṹ˵��  : EFUSE_WE4 �Ĵ����ṹ���塣��ַƫ����:0xC6����ֵ:0x00�����:8
 �Ĵ���˵��: EFUSE��ַ�Ĵ�����Ӧ��ַ[39:32]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_we4_cfg : 8;  /* bit[0-7]: efuse��ַ�Ĵ�����Ӧ��ַwe4[39:32] */
    } reg;
} SOC_SCHARGER_EFUSE_WE4_UNION;
#endif
#define SOC_SCHARGER_EFUSE_WE4_efuse_we4_cfg_START  (0)
#define SOC_SCHARGER_EFUSE_WE4_efuse_we4_cfg_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_EFUSE_WE5_UNION
 �ṹ˵��  : EFUSE_WE5 �Ĵ����ṹ���塣��ַƫ����:0xC7����ֵ:0x00�����:8
 �Ĵ���˵��: EFUSE��ַ�Ĵ�����Ӧ��ַ[47:40]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_we5_cfg : 8;  /* bit[0-7]: efuse��ַ�Ĵ�����Ӧ��ַwe5[47:40] */
    } reg;
} SOC_SCHARGER_EFUSE_WE5_UNION;
#endif
#define SOC_SCHARGER_EFUSE_WE5_efuse_we5_cfg_START  (0)
#define SOC_SCHARGER_EFUSE_WE5_efuse_we5_cfg_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_EFUSE_WE6_UNION
 �ṹ˵��  : EFUSE_WE6 �Ĵ����ṹ���塣��ַƫ����:0xC8����ֵ:0x00�����:8
 �Ĵ���˵��: EFUSE��ַ�Ĵ�����Ӧ��ַ[55:48]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_we6_cfg : 8;  /* bit[0-7]: efuse��ַ�Ĵ�����Ӧ��ַwe6[55:48] */
    } reg;
} SOC_SCHARGER_EFUSE_WE6_UNION;
#endif
#define SOC_SCHARGER_EFUSE_WE6_efuse_we6_cfg_START  (0)
#define SOC_SCHARGER_EFUSE_WE6_efuse_we6_cfg_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_EFUSE_WE7_UNION
 �ṹ˵��  : EFUSE_WE7 �Ĵ����ṹ���塣��ַƫ����:0xC9����ֵ:0x00�����:8
 �Ĵ���˵��: EFUSE��ַ�Ĵ�����Ӧ��ַ[63:56]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_we7_cfg : 8;  /* bit[0-7]: efuse��ַ�Ĵ�����Ӧ��ַwe7[63:56] */
    } reg;
} SOC_SCHARGER_EFUSE_WE7_UNION;
#endif
#define SOC_SCHARGER_EFUSE_WE7_efuse_we7_cfg_START  (0)
#define SOC_SCHARGER_EFUSE_WE7_efuse_we7_cfg_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_EFUSE_PDOB0_UNION
 �ṹ˵��  : EFUSE_PDOB0 �Ĵ����ṹ���塣��ַƫ����:0xCA����ֵ:0x00�����:8
 �Ĵ���˵��: EFUSE���������Ӧ��ַ[7:0]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_pdob0 : 8;  /* bit[0-7]: efuse���������Ӧ��ַwe0[7:0] */
    } reg;
} SOC_SCHARGER_EFUSE_PDOB0_UNION;
#endif
#define SOC_SCHARGER_EFUSE_PDOB0_efuse_pdob0_START  (0)
#define SOC_SCHARGER_EFUSE_PDOB0_efuse_pdob0_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_EFUSE_PDOB1_UNION
 �ṹ˵��  : EFUSE_PDOB1 �Ĵ����ṹ���塣��ַƫ����:0xCB����ֵ:0x00�����:8
 �Ĵ���˵��: EFUSE���������Ӧ��ַ[15:8]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_pdob1 : 8;  /* bit[0-7]: efuse���������Ӧ��ַwe1[15:8] */
    } reg;
} SOC_SCHARGER_EFUSE_PDOB1_UNION;
#endif
#define SOC_SCHARGER_EFUSE_PDOB1_efuse_pdob1_START  (0)
#define SOC_SCHARGER_EFUSE_PDOB1_efuse_pdob1_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_EFUSE_PDOB2_UNION
 �ṹ˵��  : EFUSE_PDOB2 �Ĵ����ṹ���塣��ַƫ����:0xCC����ֵ:0x00�����:8
 �Ĵ���˵��: EFUSE���������Ӧ��ַ[23:16]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_pdob2 : 8;  /* bit[0-7]: efuse���������Ӧ��ַwe2[23:16] */
    } reg;
} SOC_SCHARGER_EFUSE_PDOB2_UNION;
#endif
#define SOC_SCHARGER_EFUSE_PDOB2_efuse_pdob2_START  (0)
#define SOC_SCHARGER_EFUSE_PDOB2_efuse_pdob2_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_EFUSE_PDOB3_UNION
 �ṹ˵��  : EFUSE_PDOB3 �Ĵ����ṹ���塣��ַƫ����:0xCD����ֵ:0x00�����:8
 �Ĵ���˵��: EFUSE���������Ӧ��ַ[31:24]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_pdob3 : 8;  /* bit[0-7]: efuse���������Ӧ��ַwe3[31:24] */
    } reg;
} SOC_SCHARGER_EFUSE_PDOB3_UNION;
#endif
#define SOC_SCHARGER_EFUSE_PDOB3_efuse_pdob3_START  (0)
#define SOC_SCHARGER_EFUSE_PDOB3_efuse_pdob3_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_EFUSE_PDOB4_UNION
 �ṹ˵��  : EFUSE_PDOB4 �Ĵ����ṹ���塣��ַƫ����:0xCE����ֵ:0x00�����:8
 �Ĵ���˵��: EFUSE���������Ӧ��ַ[39:32]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_pdob4 : 8;  /* bit[0-7]: efuse���������Ӧ��ַwe4[39:32] */
    } reg;
} SOC_SCHARGER_EFUSE_PDOB4_UNION;
#endif
#define SOC_SCHARGER_EFUSE_PDOB4_efuse_pdob4_START  (0)
#define SOC_SCHARGER_EFUSE_PDOB4_efuse_pdob4_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_EFUSE_PDOB5_UNION
 �ṹ˵��  : EFUSE_PDOB5 �Ĵ����ṹ���塣��ַƫ����:0xCF����ֵ:0x00�����:8
 �Ĵ���˵��: EFUSE���������Ӧ��ַ[47:40]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_pdob5 : 8;  /* bit[0-7]: efuse���������Ӧ��ַwe5[47:40] */
    } reg;
} SOC_SCHARGER_EFUSE_PDOB5_UNION;
#endif
#define SOC_SCHARGER_EFUSE_PDOB5_efuse_pdob5_START  (0)
#define SOC_SCHARGER_EFUSE_PDOB5_efuse_pdob5_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_EFUSE_PDOB6_UNION
 �ṹ˵��  : EFUSE_PDOB6 �Ĵ����ṹ���塣��ַƫ����:0xD0����ֵ:0x00�����:8
 �Ĵ���˵��: EFUSE���������Ӧ��ַ[55:48]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_pdob6 : 8;  /* bit[0-7]: efuse���������Ӧ��ַwe6[55:48] */
    } reg;
} SOC_SCHARGER_EFUSE_PDOB6_UNION;
#endif
#define SOC_SCHARGER_EFUSE_PDOB6_efuse_pdob6_START  (0)
#define SOC_SCHARGER_EFUSE_PDOB6_efuse_pdob6_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_EFUSE_PDOB7_UNION
 �ṹ˵��  : EFUSE_PDOB7 �Ĵ����ṹ���塣��ַƫ����:0xD1����ֵ:0x00�����:8
 �Ĵ���˵��: EFUSE���������Ӧ��ַ[63:56]��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_pdob7 : 8;  /* bit[0-7]: efuse���������Ӧ��ַwe7[63:56] */
    } reg;
} SOC_SCHARGER_EFUSE_PDOB7_UNION;
#endif
#define SOC_SCHARGER_EFUSE_PDOB7_efuse_pdob7_START  (0)
#define SOC_SCHARGER_EFUSE_PDOB7_efuse_pdob7_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_EFUSE_SOFT_RST_CTRL_UNION
 �ṹ˵��  : EFUSE_SOFT_RST_CTRL �Ĵ����ṹ���塣��ַƫ����:0xD2����ֵ:0x00�����:8
 �Ĵ���˵��: EFUSE��λ���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_soft_rst_cfg : 8;  /* bit[0-7]: EFUSEģ����λ�źţ�д��0x04���и�λ���Զ����㡣 */
    } reg;
} SOC_SCHARGER_EFUSE_SOFT_RST_CTRL_UNION;
#endif
#define SOC_SCHARGER_EFUSE_SOFT_RST_CTRL_efuse_soft_rst_cfg_START  (0)
#define SOC_SCHARGER_EFUSE_SOFT_RST_CTRL_efuse_soft_rst_cfg_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_SYS_RESVO1_UNION
 �ṹ˵��  : SYS_RESVO1 �Ĵ����ṹ���塣��ַƫ����:0xE0����ֵ:0x00�����:8
 �Ĵ���˵��: SYS����1�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sys_resvo1 : 8;  /* bit[0-7]: sys_resvo1<7:5>���Ĵ���Ԥ����
                                                     sys_resvo1<4:3>��VBUSǷѹ��ļĴ���ѡ��
                                                     00��Ƿѹ��Ϊ3.8V��
                                                     01��Ƿѹ��Ϊ7.4V��
                                                     10&amp;11��Ƿѹ��9.7V��
                                                     sys_resvo1<2:1>��VBUS��ѹ��ļĴ���ѡ��
                                                     00����ѹ��Ϊ6.5V��
                                                     01����ѹ��Ϊ10.5V��
                                                     10&amp;11����ѹ��13.5V��
                                                     sys_resvo1<0>��OTG������ʱʱ��ĵ�λѡ��
                                                     0����ʱ256ms��
                                                     1����ʱ128ms��
                                                     ע��VBUS�Ĺ�ѹ��Ƿѹ���ѡ��Ҫע��ƥ��vbus_vset�������ѹ��λѡ�� */
    } reg;
} SOC_SCHARGER_SYS_RESVO1_UNION;
#endif
#define SOC_SCHARGER_SYS_RESVO1_sys_resvo1_START  (0)
#define SOC_SCHARGER_SYS_RESVO1_sys_resvo1_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_SYS_RESVO2_UNION
 �ṹ˵��  : SYS_RESVO2 �Ĵ����ṹ���塣��ַƫ����:0xE1����ֵ:0x00�����:8
 �Ĵ���˵��: SYS_RESVO2Ԥ���Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sys_resvo2 : 8;  /* bit[0-7]: Ԥ���Ĵ��� */
    } reg;
} SOC_SCHARGER_SYS_RESVO2_UNION;
#endif
#define SOC_SCHARGER_SYS_RESVO2_sys_resvo2_START  (0)
#define SOC_SCHARGER_SYS_RESVO2_sys_resvo2_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_SYS_RESVO3_UNION
 �ṹ˵��  : SYS_RESVO3 �Ĵ����ṹ���塣��ַƫ����:0xE2����ֵ:0x00�����:8
 �Ĵ���˵��: SYS_RESVO3Ԥ���Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sys_resvo3 : 8;  /* bit[0-7]: Ԥ���Ĵ��� */
    } reg;
} SOC_SCHARGER_SYS_RESVO3_UNION;
#endif
#define SOC_SCHARGER_SYS_RESVO3_sys_resvo3_START  (0)
#define SOC_SCHARGER_SYS_RESVO3_sys_resvo3_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_SYS_RESVO4_UNION
 �ṹ˵��  : SYS_RESVO4 �Ĵ����ṹ���塣��ַƫ����:0xE3����ֵ:0x00�����:8
 �Ĵ���˵��: SYS_RESVO4Ԥ���Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sys_resvo4 : 8;  /* bit[0-7]: Ԥ���Ĵ��� */
    } reg;
} SOC_SCHARGER_SYS_RESVO4_UNION;
#endif
#define SOC_SCHARGER_SYS_RESVO4_sys_resvo4_START  (0)
#define SOC_SCHARGER_SYS_RESVO4_sys_resvo4_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_SYS_RESVI1_UNION
 �ṹ˵��  : SYS_RESVI1 �Ĵ����ṹ���塣��ַƫ����:0xE4����ֵ:0x00�����:8
 �Ĵ���˵��: SYS_RESVI1Ԥ���Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sys_resvi1 : 8;  /* bit[0-7]: Ԥ���Ĵ��� */
    } reg;
} SOC_SCHARGER_SYS_RESVI1_UNION;
#endif
#define SOC_SCHARGER_SYS_RESVI1_sys_resvi1_START  (0)
#define SOC_SCHARGER_SYS_RESVI1_sys_resvi1_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_SYS_RESVI2_UNION
 �ṹ˵��  : SYS_RESVI2 �Ĵ����ṹ���塣��ַƫ����:0xE5����ֵ:0x00�����:8
 �Ĵ���˵��: SYS_RESVI2Ԥ���Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sys_resvi2 : 8;  /* bit[0-7]: Ԥ���Ĵ��� */
    } reg;
} SOC_SCHARGER_SYS_RESVI2_UNION;
#endif
#define SOC_SCHARGER_SYS_RESVI2_sys_resvi2_START  (0)
#define SOC_SCHARGER_SYS_RESVI2_sys_resvi2_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_OSC_FCP_UNION
 �ṹ˵��  : OSC_FCP �Ĵ����ṹ���塣��ַƫ����:0xE6����ֵ:0x00�����:8
 �Ĵ���˵��: 2MHz�߾���ʱ��Ƶ���޵��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  osc_trimcode : 6;  /* bit[0-5]: ��2MHz�߾���ʱ��Ƶ�ʽ����޵� */
        unsigned char  reserved     : 2;  /* bit[6-7]: ������ */
    } reg;
} SOC_SCHARGER_OSC_FCP_UNION;
#endif
#define SOC_SCHARGER_OSC_FCP_osc_trimcode_START  (0)
#define SOC_SCHARGER_OSC_FCP_osc_trimcode_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_GLB_SOFT_RST_CTRL_UNION
 �ṹ˵��  : GLB_SOFT_RST_CTRL �Ĵ����ṹ���塣��ַƫ����:0xE7����ֵ:0x00�����:8
 �Ĵ���˵��: ȫ����λ���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  soft_rst_cfg : 8;  /* bit[0-7]: ȫ����λ�źţ�д��0x04���и�λ���Զ����㣬batfet_ctrl�Ĵ���������λ���ơ� */
    } reg;
} SOC_SCHARGER_GLB_SOFT_RST_CTRL_UNION;
#endif
#define SOC_SCHARGER_GLB_SOFT_RST_CTRL_soft_rst_cfg_START  (0)
#define SOC_SCHARGER_GLB_SOFT_RST_CTRL_soft_rst_cfg_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_WATCHDOG_SOFT_RST_UNION
 �ṹ˵��  : WATCHDOG_SOFT_RST �Ĵ����ṹ���塣��ַƫ����:0xE8����ֵ:0x00�����:8
 �Ĵ���˵��: ���Ź���λ���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  wd_rst_n : 1;  /* bit[0]  : д1�üĴ�����ϵͳwatchdog timer�������¼�ʱ(д1���Զ�����)
                                                   ���SoC������ʱ���ڲ��ԸüĴ���д��1����������λchg_en��watchdog_timer�Ĵ����� */
        unsigned char  reserved : 7;  /* bit[1-7]: ������ */
    } reg;
} SOC_SCHARGER_WATCHDOG_SOFT_RST_UNION;
#endif
#define SOC_SCHARGER_WATCHDOG_SOFT_RST_wd_rst_n_START  (0)
#define SOC_SCHARGER_WATCHDOG_SOFT_RST_wd_rst_n_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_WATCHDOG_CTRL_UNION
 �ṹ˵��  : WATCHDOG_CTRL �Ĵ����ṹ���塣��ַƫ����:0xE9����ֵ:0x00�����:8
 �Ĵ���˵��: ι��ʱ����ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  watchdog_timer : 2;  /* bit[0-1]: SOCÿ��һ��ʱ���wd_rst_n(0xE8)����һ�μĴ���д���������û��д�����¼������������Defaultģʽ����λchg_en��watchdog_timer�Ĵ�����������������Hostģʽ��
                                                         ϵͳwatchdog_timerʱ�����ã�
                                                         00��ϵͳwatchdog_timer�������Σ�
                                                         01��10s��
                                                         10��20s��
                                                         11��40s �� */
        unsigned char  reserved       : 6;  /* bit[2-7]: ������ */
    } reg;
} SOC_SCHARGER_WATCHDOG_CTRL_UNION;
#endif
#define SOC_SCHARGER_WATCHDOG_CTRL_watchdog_timer_START  (0)
#define SOC_SCHARGER_WATCHDOG_CTRL_watchdog_timer_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_SCHARGER_CLK_GATE_UNION
 �ṹ˵��  : CLK_GATE �Ĵ����ṹ���塣��ַƫ����:0xEA����ֵ:0x00�����:8
 �Ĵ���˵��: clk gating���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  red_clk_enable : 1;  /* bit[0]  : clk gating�Ĵ�����
                                                         0��gateʱ�ӣ�
                                                         1��ʹ��ʱ�ӡ� */
        unsigned char  reserved       : 7;  /* bit[1-7]: ������ */
    } reg;
} SOC_SCHARGER_CLK_GATE_UNION;
#endif
#define SOC_SCHARGER_CLK_GATE_red_clk_enable_START  (0)
#define SOC_SCHARGER_CLK_GATE_red_clk_enable_END    (0)






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

#endif /* end of soc_scharger_interface.h */
