

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __BBP_COMMON_INTERFACE_H__
#define __BBP_COMMON_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/***======================================================================***
                     (1/3) register_define_ctu
 ***======================================================================***/
/* �Ĵ���˵����ͨ��0��Ӧ��ģ����ģ0����ģʽָʾ�Ĵ���
 bit[31:3]   ����
 bit[2:0]    ͨ��0��Ӧ����ģ������Ϊ��ģ0����ģʽָʾ����ʾLTE��W��Gm��Gs��TDS˭����ģ0��
             000��LTE ��ģ��
             001��W��ģ��
             010��TDS��ģ��
             011��Gm��ģ��
             100��Gs��ģ��
             101:C��ģ��
             110~111����Ч��
             ����ʱ�̣���ģ����ͨ�ų�������
   UNION�ṹ:  BBPCOMM_C0_PRIMARY_MODE_IND_UNION */
#define BBPCOMM_C0_PRIMARY_MODE_IND_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x0)

/* �Ĵ���˵������ģ0��Ӧ�Ĵ�ģ����ģ0����ģʽָʾ�Ĵ���
 bit[31:3]   ����
 bit[2:0]    ��ģ0��Ӧ�Ĵ�ģ������Ϊ��ģ0����ģʽָʾ����ʾ��ǰLTE/W/Gm/Gs/TDS˭�Ǵ�ģ0��
             000��LTE��ģ��
             001��W ��ģ��
             010��TDS��ģ��
             011��Gm��ģ��
             100��Gs��ģ��
             101:C��ģ��
             110~111����Ч��
             ����ʱ�̣���ģ����ͨ�ų�������
             ע��Լ����ģ0�̶���ͨ��0����ģ1�̶���ͨ��1��
   UNION�ṹ:  BBPCOMM_C0_SECOND_MODE_IND_UNION */
#define BBPCOMM_C0_SECOND_MODE_IND_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x4)

/* �Ĵ���˵�����Ĵ���
   ��      ����AFC0ֵ����
               [15:0]:AFC������ֵ
               [16]:AFC����ָʾ
               
               ����ʱ�̣�DSP����ģ�л�Ϊ��ģʱ���ã�DSP�Ӵ�ģ�л�Ϊ��ģʱ��ȡ���������ָʾ
               ��Чʱ�̣�������Ч
   UNION�ṹ ���� */
#define BBPCOMM_AFC0_VALUE_INTER_RAT_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xC)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    ͨ��0 AFC�����ź���Դ��
             3'b000������ģ���ƣ�
             3'b001��ǿ����Lģ���ƣ�
             3'b010��ǿ����Wģ���ƣ�
             3'b011��ǿ����TDSģ���ƣ�
             3'b100��ǿ����Gmģ���ƣ�
             3'b101��ǿ����Gsģ���ƣ�
             3'b110��ǿ����Cģ���ƣ�
             3'b111����Ч��
             �����á�
   UNION�ṹ:  BBPCOMM_C0_AFC_PDM_SELECT_MASK_UNION */
#define BBPCOMM_C0_AFC_PDM_SELECT_MASK_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x10)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    ͨ��0 ���߿��غ�PA�����ź���Դ��
             3'b000������ģ���ƣ�
             3'b001��ǿ����Lģ���ƣ�
             3'b010��ǿ����Wģ���ƣ�
             3'b011��ǿ����TDSģ���ƣ�
             3'b100��ǿ����Gmģ���ƣ�
             3'b101��ǿ����Gsģ���ƣ�
             3'b110��ǿ����Cģ���ƣ�
             3'b111����Ч��
             �����á�
   UNION�ṹ:  BBPCOMM_C0_ANT_SWITCH_PA_SELECT_MASK_UNION */
#define BBPCOMM_C0_ANT_SWITCH_PA_SELECT_MASK_ADDR     (SOC_BBP_COMM_BASE_ADDR + 0x14)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    ͨ��0 RFIC�����ź���Դ�������߿غ�SSI����
             3'b000������ģ���ƣ�
             3'b001��ǿ����Lģ���ƣ�
             3'b010��ǿ����Wģ���ƣ�
             3'b011��ǿ����TDSģ���ƣ�
             3'b100��ǿ����Gmģ���ƣ�
             3'b101��ǿ����Gsģ���ƣ�
             3'b110��ǿ����Cģ���ƣ�
             3'b111����Ч��
             �����á�
   UNION�ṹ:  BBPCOMM_C0_RFIC_SELECT_MASK_UNION */
#define BBPCOMM_C0_RFIC_SELECT_MASK_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x18)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    ͨ��0 MIPI�����ź���Դ��
             3'b000������ģ���ƣ�
             3'b001��ǿ����Lģ���ƣ�
             3'b010��ǿ����Wģ���ƣ�
             3'b011��ǿ����TDSģ���ƣ�
             3'b100��ǿ����Gmģ���ƣ�
             3'b101��ǿ����Gsģ���ƣ�
             3'b110��ǿ����Cģ���ƣ�
             ��������Ч��
             �����á�
   UNION�ṹ:  BBPCOMM_C0_MIPI_SELECT_MASK_UNION */
#define BBPCOMM_C0_MIPI_SELECT_MASK_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x1C)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    ͨ��0 ABB�����ź���Դ��
             3'b000������ģ���ƣ�
             3'b001��ǿ����Lģ���ƣ�
             3'b010��ǿ����Wģ���ƣ�
             3'b011��ǿ����TDSģ���ƣ�
             3'b100��ǿ����Gmģ���ƣ�
             3'b101��ǿ����Gsģ���ƣ�
             3'b110��ǿ����Cģ���ƣ�
             ��������Ч��
             �����á�
   UNION�ṹ:  BBPCOMM_C0_ABB_SELECT_MASK_UNION */
#define BBPCOMM_C0_ABB_SELECT_MASK_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x20)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    ͨ��0 PMU�����ź���Դ��
             3'b000������ģ���ƣ�
             3'b001��ǿ����Lģ���ƣ�
             3'b010��ǿ����Wģ���ƣ�
             3'b011��ǿ����TDSģ���ƣ�
             3'b100��ǿ����Gmģ���ƣ�
             3'b101��ǿ����Gsģ���ƣ�
             3'b110��ǿ����Cģ���ƣ�
             3'b111����Ч��
             �����á�
   UNION�ṹ:  BBPCOMM_C0_PMU_SELECT_MASK_UNION */
#define BBPCOMM_C0_PMU_SELECT_MASK_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x24)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    ��ǰͨ��0������֮ǰ�������ǿ��ģʽ��
             ע���������ڸ�����Χ������ABB��RF��PA��mipi�ȣ������Ľ���ǿ�䡣
             �����á�
   UNION�ṹ:  BBPCOMM_DSP_C0_SEL_MASK_UNION */
#define BBPCOMM_DSP_C0_SEL_MASK_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x28)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    ������õ�RFIC0��λ�źţ�����Ч��
             0����λ��1���⸴λ��
             �ϵ��ʼ������Ϊ0������RFIC�ֲ�Ҫ��ά��һ��ʱ�������Ϊ1��
             V3R3���üĴ������ܸ��ڼĴ���0x0334��bit[8]ʵ�֣�Ĭ��ֵ��Ϊ0���˴�ɾ����
             V7R2��λֵΪ0��
             V8R1���üĴ�������ɾ����
   UNION�ṹ:  BBPCOMM_DSP_RFIC0_RSTN_UNION */
#define BBPCOMM_DSP_RFIC0_RSTN_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x2C)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      0:ͨ��0��ģʹ��ͨ��0��ģafc������
             1:ͨ��0��ģʹ��ͨ��0��ģafc������
   UNION�ṹ:  BBPCOMM_C0_SECOND_AFC_MODE_UNION */
#define BBPCOMM_C0_SECOND_AFC_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x30)

/* �Ĵ���˵�����Ĵ���
   ��      ��������bbp_sys_0control��
               GU���漰��
   UNION�ṹ ���� */
#define BBPCOMM_BBP_SYS_0CONTROL_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x34)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      DSP�ȴ��ض������ʱ��־λ
             1:��ʱ  
   UNION�ṹ:  BBPCOMM_MIPI0_RD_OVERTIME_FLAG_DSP_UNION */
#define BBPCOMM_MIPI0_RD_OVERTIME_FLAG_DSP_ADDR       (SOC_BBP_COMM_BASE_ADDR + 0x38)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      DSP�ȴ��ض������ʱ��־λ
             1:��ʱ  
   UNION�ṹ:  BBPCOMM_SSI0_RD_OVERTIME_FLAG_DSP_UNION */
#define BBPCOMM_SSI0_RD_OVERTIME_FLAG_DSP_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x3C)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      DSP�ȴ��ض������ʱ��,�峭ʱ��־λ����
   UNION�ṹ:  BBPCOMM_MIPI0_RD_OVERTIME_CLR_UNION */
#define BBPCOMM_MIPI0_RD_OVERTIME_CLR_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x40)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      DSP�ȴ��ض������ʱ��,�峭ʱ��־λ����
   UNION�ṹ:  BBPCOMM_SSI0_RD_OVERTIME_CLR_UNION */
#define BBPCOMM_SSI0_RD_OVERTIME_CLR_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x44)

/* �Ĵ���˵�����Ĵ���
   ��      ����xbbp��SSI0 master�����ض���ָ��ʱ,DSP��ȡSSI�ض����,�ض���������ڴ�16�Ĵ���λ����dsp����,�ض������Ƿ���Ч�ο���־λ
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC0_1_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x48)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC0_2_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x4C)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC0_3_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x50)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC0_4_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x54)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC0_5_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x58)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC0_6_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x5C)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC0_7_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x60)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC0_8_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x64)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC0_9_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x68)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC0_10_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x6C)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC0_11_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x70)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC0_12_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x74)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC0_13_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x78)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC0_14_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x7C)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC0_15_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x80)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC0_16_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x84)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      ���лض�ָ��ִ�����,����ȡ�߻ض�����
             1:���лض�ָ������,DSP���԰�λ�ö�ȡSSI�ض����
   UNION�ṹ:  BBPCOMM_RD_RESULT_FLAG_RFIC0_UNION */
#define BBPCOMM_RD_RESULT_FLAG_RFIC0_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x88)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      1:DSPȡ�����лض����ݺ�,д��clr�ź����־λ
   UNION�ṹ:  BBPCOMM_RD_RESULT_FLAG_RFIC0_CLR_UNION */
#define BBPCOMM_RD_RESULT_FLAG_RFIC0_CLR_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x8C)

/* �Ĵ���˵�����Ĵ���
   ��      ����xbbp��MIPI0 master�����ض���ָ��ʱ,DSP��ȡMIPI�ض����,�ض���������ڴ�16�Ĵ���λ����dsp����,�ض������Ƿ���Ч�ο���־λ
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI0_1_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x90)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI0_2_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x94)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI0_3_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x98)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI0_4_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x9C)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI0_5_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xA0)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI0_6_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xA4)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI0_7_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xA8)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI0_8_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xAC)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI0_9_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xB0)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI0_10_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xB4)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI0_11_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xB8)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI0_12_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xBC)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI0_13_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC0)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI0_14_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC4)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI0_15_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC8)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI0_16_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xCC)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      ���лض�ָ��ִ�����,����ȡ�߻ض�����
             1:���лض�ָ������,DSP���԰�λ�ö�ȡSSI�ض����,�����������ֱ�ӿ���MIPI��־λ��ͬ
   UNION�ṹ:  BBPCOMM_RD_RESULT_FLAG_MIPI0_UNION */
#define BBPCOMM_RD_RESULT_FLAG_MIPI0_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xD0)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      1:DSPȡ�����лض����ݺ�,д��clr�ź����־λ,�����������ֱ�ӿ���MIPI��־λ��ͬ
   UNION�ṹ:  BBPCOMM_RD_RESULT_FLAG_MIPI0_CLR_UNION */
#define BBPCOMM_RD_RESULT_FLAG_MIPI0_CLR_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xD4)

/* �Ĵ���˵�����Ĵ���
   ��      ���������ֱ�ӿ���MIPI0 master,������xbbp���ͻض�ָ��ʱ,�ض�ָ���ŵ�32bit.
   UNION�ṹ ���� */
#define BBPCOMM_MIPI0_RD_DATA_LOW_SOFT_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xD8)

/* �Ĵ���˵�����Ĵ���
   ��      ���������ֱ�ӿ���MIPI0 master,������xbbp���ͻض�ָ��ʱ,�ض�ָ���Ÿ�32bit.
   UNION�ṹ ���� */
#define BBPCOMM_MIPI0_RD_DATA_HIGH_SOFT_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xDC)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      �����ֱ�ӿ���MIPI0 master,������xbbp���ͻض�ָ��ʱ,�ض�������Чָʾ
   UNION�ṹ:  BBPCOMM_RD_END_FLAG_MIPI0_SOFT_UNION */
#define BBPCOMM_RD_END_FLAG_MIPI0_SOFT_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xE0)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      �����ֱ�ӿ���MIPI0 master
             1:������Է���CFG_IND����mipi0
             0:����ȴ�mipi0��Ȩʹ��
   UNION�ṹ:  BBPCOMM_MIPI0_GRANT_DSP_UNION */
#define BBPCOMM_MIPI0_GRANT_DSP_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xE4)

/* �Ĵ���˵�����Ĵ���
   ��      ���������ֱ�ӿ���MIPI0 master,������xbbp����дָ��ʱ,дָ���32bit��
               ��MIPI��̬ʹ��mipi_dyn_exchg_en��Чʱ��MIPI��չָ��ʱ��dsp_mipi0_wdata_low[1:0]Ӧ����Ϊ0
   UNION�ṹ ���� */
#define BBPCOMM_DSP_MIPI0_WDATA_LOW_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xE8)

/* �Ĵ���˵�����Ĵ���
   ��      ���������ֱ�ӿ���MIPI0 master,������xbbp����дָ��ʱ,дָ���32bit��
               ��MIPI��̬ʹ��mipi_dyn_exchg_en��Ч��MIPI����չָ��ʱ��dsp_mipi0_wdata_high[1:0]Ӧ����Ϊ0
   UNION�ṹ ���� */
#define BBPCOMM_DSP_MIPI0_WDATA_HIGH_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xEC)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      �����ֱ�ӿ���MIPI0 master,���������ߴ�ָʾ,����xbbp��MIPI0�Ŀ���
   UNION�ṹ:  BBPCOMM_DSP_MIPI0_EN_IMI_UNION */
#define BBPCOMM_DSP_MIPI0_EN_IMI_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xF0)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      �����ֱ�ӿ���MIPI0 master,���ߴ�dsp_mipi0_en��,���������������
   UNION�ṹ:  BBPCOMM_DSP_MIPI0_CFG_IND_IMI_UNION */
#define BBPCOMM_DSP_MIPI0_CFG_IND_IMI_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xF4)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      �����ֱ�ӿ���MIPI0 master,ȡ�߻ض����ݺ�,���־λ����
   UNION�ṹ:  BBPCOMM_DSP_MIPI0_RD_CLR_UNION */
#define BBPCOMM_DSP_MIPI0_RD_CLR_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xF8)

/* �Ĵ���˵�����Ĵ���
 bit[31:9]   ����
 bit[8:8]    ���ǿ��ģʽabb0_rxb_blk_en.
 bit[7:7]    ���ǿ��ģʽabb0_rxa_blk_en.
 bit[6:6]    ���ǿ��ģʽabb0_rxb_en.
 bit[5:5]    ���ǿ��ģʽabb0_rxa_en.
 bit[4:4]    ���ǿ��ģʽabb0_tx_en.
 bit[3:1]    ���ǿ��ģʽabb0_mode_sel.
 bit[0:0]    ABB0�߿�ǿ��ģʽ��
             1����ʾ���ǿ�䣬��ʱ��������ǿ�����Ч��
             0����ʾ��CTU���ݸ�BBP������
             Ĭ��ֵΪ0��
             �����á�
   UNION�ṹ:  BBPCOMM_ABB0_LINE_CONTROL_CMD_UNION */
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xFC)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    V9R1�汾����������á�
   UNION�ṹ:  BBPCOMM_CH0_BBP_SEL_UNION */
#define BBPCOMM_CH0_BBP_SEL_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x100)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      cpu����mipi����,����Ϊ1������������, ����ʱ����Ϊ0
   UNION�ṹ:  BBPCOMM_CPU_MIPI0_FUNC_SEL_UNION */
#define BBPCOMM_CPU_MIPI0_FUNC_SEL_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x104)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      cpu����mipi����,������
   UNION�ṹ:  BBPCOMM_CPU_MIPI0_TEST_FUNC_UNION */
#define BBPCOMM_CPU_MIPI0_TEST_FUNC_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x108)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      cpu����mipi����, ������
   UNION�ṹ:  BBPCOMM_CPU_MIPI0_SCLK_TEST_UNION */
#define BBPCOMM_CPU_MIPI0_SCLK_TEST_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x10C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      cpu����mipi����, ������
   UNION�ṹ:  BBPCOMM_CPU_MIPI0_SDATA_TEST_UNION */
#define BBPCOMM_CPU_MIPI0_SDATA_TEST_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x110)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      cpu����mipi����,mipi0master���쳣�ź�
   UNION�ṹ:  BBPCOMM_DSP_MIPI0_CLR_IND_IMI_UNION */
#define BBPCOMM_DSP_MIPI0_CLR_IND_IMI_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x114)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      mipi0�洢����������ͬ��FIFO��λ�ź�
   UNION�ṹ:  BBPCOMM_CPU_MIPI0_FIFO_CLR_IMI_UNION */
#define BBPCOMM_CPU_MIPI0_FIFO_CLR_IMI_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x118)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ssi0�洢����������ͬ��FIFO��λ�ź�
   UNION�ṹ:  BBPCOMM_CPU_SSI0_FIFO_CLR_IMI_UNION */
#define BBPCOMM_CPU_SSI0_FIFO_CLR_IMI_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x11C)

/* �Ĵ���˵����
 bit[31:12]  ����
 bit[11]     Cģͨ��0 TX ABB��·ʱ���ſ���·�ź�
 bit[10]     Cģͨ��0 RX ABB��·ʱ���ſ���·�ź�
 bit[9]      G2ͨ��0 TX ABB��·ʱ���ſ���·�ź�
 bit[8]      G1ͨ��0 TX ABB��·ʱ���ſ���·�ź�
 bit[7]      Wģͨ��0 TX ABB��·ʱ���ſ���·�ź�
 bit[6]      TDSͨ��0 TX ABB��·ʱ���ſ���·�ź�
 bit[5]      Lģͨ��0 TX ABB��·ʱ���ſ���·�ź�
 bit[4]      G2ͨ��0 RX ABB��·ʱ���ſ���·�ź�
 bit[3]      G1ͨ��0 RX ABB��·ʱ���ſ���·�ź�
 bit[2]      Wģͨ��0 RX ABB��·ʱ���ſ���·�ź�
 bit[1]      TDSͨ��0 RX ABB��·ʱ���ſ���·�ź�
 bit[0]      Lģͨ��0 RX ABB��·ʱ���ſ���·�ź�
   UNION�ṹ:  BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_UNION */
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x120)

/* �Ĵ���˵����ͨ��1��Ӧ��ģ����ģ1����ģʽָʾ�Ĵ���
 bit[31:3]   ����
 bit[2:0]    ͨ��1��Ӧ����ģ������Ϊ��ģ1����ģʽָʾ����ʾLTE��W��Gm��Gs��TDS˭����ģ1��
             000��LTE ��ģ��
             001��W��ģ��
             010��TDS��ģ��
             011��Gm��ģ��
             100��Gs��ģ��
             101��C��ģ��
             110~111����Ч��
             ����ʱ�̣���ģ����ͨ�ų�������
   UNION�ṹ:  BBPCOMM_C1_PRIMARY_MODE_IND_UNION */
#define BBPCOMM_C1_PRIMARY_MODE_IND_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x300)

/* �Ĵ���˵������ģ1��Ӧ�Ĵ�ģ����ģ1����ģʽָʾ�Ĵ���
 bit[31:3]   ����
 bit[2:0]    ��ģ1��Ӧ�Ĵ�ģ������Ϊ��ģ1����ģʽָʾ����ʾLTE/W/Gm/Gs/TDS˭�Ǵ�ģ1��
             000��LTE��ģ��
             001��W ��ģ��
             010��TDS��ģ��
             011��Gm��ģ��
             100��Gs��ģ��
             101��C��ģ��
             110~111����Ч��
             ����ʱ�̣���ģ����ͨ�ų�������.
             ע��Լ����ģ0�̶���ͨ��0����ģ1�̶���ͨ��1��
   UNION�ṹ:  BBPCOMM_C1_SECOND_MODE_IND_UNION */
#define BBPCOMM_C1_SECOND_MODE_IND_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x304)

/* �Ĵ���˵�����Ĵ���
   ��      ����AFC1ֵ����
               [15:0]:AFC������ֵ
               [16]:AFC����ָʾ
               
               ����ʱ�̣�DSP����ģ�л�Ϊ��ģʱ���ã�DSP�Ӵ�ģ�л�Ϊ��ģʱ��ȡ���������ָʾ
               ��Чʱ�̣�������Ч
   UNION�ṹ ���� */
#define BBPCOMM_AFC1_VALUE_INTER_RAT_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x30C)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    ͨ��1 AFC�����ź���Դ��
             3'b000������ģ���ƣ�
             3'b001��ǿ����Lģ���ƣ�
             3'b010��ǿ����Wģ���ƣ�
             3'b011��ǿ����TDSģ���ƣ�
             3'b100��ǿ����Gmģ���ƣ�
             3'b101��ǿ����Gsģ���ƣ�
             3'b110��ǿ����Cģ���ƣ�
             3'b111����Ч��
             �����á�
   UNION�ṹ:  BBPCOMM_C1_AFC_PDM_SELECT_MASK_UNION */
#define BBPCOMM_C1_AFC_PDM_SELECT_MASK_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x310)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    ͨ��1 ���߿��غ�PA�����ź���Դ��
             3'b000������ģ���ƣ�
             3'b001��ǿ����Lģ���ƣ�
             3'b010��ǿ����Wģ���ƣ�
             3'b011��ǿ����TDSģ���ƣ�
             3'b100��ǿ����Gmģ���ƣ�
             3'b101��ǿ����Gsģ���ƣ�
             3'b110��ǿ����Cģ���ƣ�
             3'b111����Ч��
             �����á�
   UNION�ṹ:  BBPCOMM_C1_ANT_SWITCH_PA_SELECT_MASK_UNION */
#define BBPCOMM_C1_ANT_SWITCH_PA_SELECT_MASK_ADDR     (SOC_BBP_COMM_BASE_ADDR + 0x314)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    ͨ��1 RFIC�����ź���Դ�������߿غ�SSI����
             3'b000������ģ���ƣ�
             3'b001��ǿ����Lģ���ƣ�
             3'b010��ǿ����Wģ���ƣ�
             3'b011��ǿ����TDSģ���ƣ�
             3'b100��ǿ����Gmģ���ƣ�
             3'b101��ǿ����Gsģ���ƣ�
             3'b110��ǿ����Cģ���ƣ�
             3'b111����Ч��
             �����á�
   UNION�ṹ:  BBPCOMM_C1_RFIC_SELECT_MASK_UNION */
#define BBPCOMM_C1_RFIC_SELECT_MASK_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x318)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    ͨ��1 MIPI�����ź���Դ��
             3'b000������ģ���ƣ�
             3'b001��ǿ����Lģ���ƣ�
             3'b010��ǿ����Wģ���ƣ�
             3'b011��ǿ����TDSģ���ƣ�
             3'b100��ǿ����Gmģ���ƣ�
             3'b101��ǿ����Gsģ���ƣ�
             3'b110��ǿ����Cģ���ƣ�
             3'b111����Ч��
             �����á�
   UNION�ṹ:  BBPCOMM_C1_MIPI_SELECT_MASK_UNION */
#define BBPCOMM_C1_MIPI_SELECT_MASK_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x31C)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    ͨ��1 ABB�����ź���Դ��
             3'b000������ģ���ƣ�
             3'b001��ǿ����Lģ���ƣ�
             3'b010��ǿ����Wģ���ƣ�
             3'b011��ǿ����TDSģ���ƣ�
             3'b100��ǿ����Gmģ���ƣ�
             3'b101��ǿ����Gsģ���ƣ�
             3'b110��ǿ����Cģ���ƣ�
             3'b111����Ч��
             �����á�
   UNION�ṹ:  BBPCOMM_C1_ABB_SELECT_MASK_UNION */
#define BBPCOMM_C1_ABB_SELECT_MASK_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x320)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    ͨ��1 PMU�����ź���Դ��
             3'b000������ģ���ƣ�
             3'b001��ǿ����Lģ���ƣ�
             3'b010��ǿ����Wģ���ƣ�
             3'b011��ǿ����TDSģ���ƣ�
             3'b100��ǿ����Gmģ���ƣ�
             3'b101��ǿ����Gsģ���ƣ�
             3'b110��ǿ����Cģ���ƣ�
             3'b111����Ч��
             �����á�
   UNION�ṹ:  BBPCOMM_C1_PMU_SELECT_MASK_UNION */
#define BBPCOMM_C1_PMU_SELECT_MASK_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x324)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    ��ǰͨ��1������֮ǰ�� �����ǿ��ģʽ��
             ע���������ڸ�����Χ������ABB��RF��PA��mipi�ȣ������Ľ���ǿ�䡣
             �����á�
   UNION�ṹ:  BBPCOMM_DSP_C1_SEL_MASK_UNION */
#define BBPCOMM_DSP_C1_SEL_MASK_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x328)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    ������õ�RFIC1��λ�źš� ����Ч�� 
             0����λ��1���⸴λ��
             �ϵ��ʼ������Ϊ0������RFIC�ֲ�Ҫ��ά��һ��ʱ�������Ϊ1��
             
             V7R2��λֵΪ0��
             V8R1���üĴ�������ɾ����
   UNION�ṹ:  BBPCOMM_DSP_RFIC1_RSTN_UNION */
#define BBPCOMM_DSP_RFIC1_RSTN_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x32C)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      0:ͨ��1��ģʹ��ͨ��1��ģafc������
             1:ͨ��1��ģʹ��ͨ��1��ģafc������
   UNION�ṹ:  BBPCOMM_C1_SECOND_AFC_MODE_UNION */
#define BBPCOMM_C1_SECOND_AFC_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x330)

/* �Ĵ���˵�����Ĵ���
   ��      ����bit[1:0]�����ݲɼ�ģ�����ģʽ���á�
               2'bx0���ɼ�WBBP���ݣ�
               2'b01���ɼ�GBBP1���ݣ�
               2'b11���ɼ�GBBP2���ݡ�
               bit[7:2]��������
               bit[8]��V3R3��dsp_rfic0_rstn��������õ�RFIC0��λ�źţ�����Ч��0����λ��1���⸴λ���ϵ��ʼ������Ϊ0������RFIC�ֲ�Ҫ��ά��һ��ʱ�������Ϊ1��V9R1��������
               bit[31:9]��������
   UNION�ṹ ���� */
#define BBPCOMM_BBP_SYS_1CONTROL_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x334)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      DSP�ȴ��ض������ʱ��־λ
             1:��ʱ  
   UNION�ṹ:  BBPCOMM_MIPI1_RD_OVERTIME_FLAG_DSP_UNION */
#define BBPCOMM_MIPI1_RD_OVERTIME_FLAG_DSP_ADDR       (SOC_BBP_COMM_BASE_ADDR + 0x338)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      DSP�ȴ��ض������ʱ��־λ
             1:��ʱ  
   UNION�ṹ:  BBPCOMM_SSI1_RD_OVERTIME_FLAG_DSP_UNION */
#define BBPCOMM_SSI1_RD_OVERTIME_FLAG_DSP_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x33C)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      DSP�ȴ��ض������ʱ��,�峭ʱ��־λ����
   UNION�ṹ:  BBPCOMM_MIPI1_RD_OVERTIME_CLR_UNION */
#define BBPCOMM_MIPI1_RD_OVERTIME_CLR_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x340)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      DSP�ȴ��ض������ʱ��,�峭ʱ��־λ����
   UNION�ṹ:  BBPCOMM_SSI1_RD_OVERTIME_CLR_UNION */
#define BBPCOMM_SSI1_RD_OVERTIME_CLR_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x344)

/* �Ĵ���˵�����Ĵ���
   ��      ����xbbp��SSI1 master�����ض���ָ��ʱ,DSP��ȡSSI�ض����,�ض���������ڴ�16�Ĵ���λ����dsp����,�ض������Ƿ���Ч�ο���־λ
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC1_1_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x348)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC1_2_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x34C)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC1_3_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x350)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC1_4_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x354)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC1_5_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x358)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC1_6_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x35C)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC1_7_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x360)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC1_8_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x364)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC1_9_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x368)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC1_10_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x36C)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC1_11_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x370)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC1_12_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x374)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC1_13_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x378)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC1_14_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x37C)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC1_15_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x380)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC1_16_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x384)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      ���лض�ָ��ִ�����,����ȡ�߻ض�����
             1:���лض�ָ������,DSP���԰�λ�ö�ȡSSI�ض����
   UNION�ṹ:  BBPCOMM_RD_RESULT_FLAG_RFIC1_UNION */
#define BBPCOMM_RD_RESULT_FLAG_RFIC1_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x388)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      1:DSPȡ�����лض����ݺ�,д��clr�ź����־λ
   UNION�ṹ:  BBPCOMM_RD_RESULT_FLAG_RFIC1_CLR_UNION */
#define BBPCOMM_RD_RESULT_FLAG_RFIC1_CLR_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x38C)

/* �Ĵ���˵�����Ĵ���
   ��      ����xbbp��MIPI1 master�����ض���ָ��ʱ,DSP��ȡMIPI�ض����,�ض���������ڴ�16�Ĵ���λ����dsp����
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI1_1_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x390)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI1_2_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x394)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI1_3_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x398)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI1_4_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x39C)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI1_5_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x3A0)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI1_6_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x3A4)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI1_7_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x3A8)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI1_8_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x3AC)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI1_9_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x3B0)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI1_10_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x3B4)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI1_11_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x3B8)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI1_12_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x3BC)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI1_13_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x3C0)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI1_14_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x3C4)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI1_15_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x3C8)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI1_16_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x3CC)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      ���лض�ָ��ִ�����,����ȡ�߻ض�����
             1:���лض�ָ������,DSP���԰�λ�ö�ȡSSI�ض����,�����������ֱ�ӿ���MIPI��־λ��ͬ
   UNION�ṹ:  BBPCOMM_RD_RESULT_FLAG_MIPI1_UNION */
#define BBPCOMM_RD_RESULT_FLAG_MIPI1_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x3D0)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      1:DSPȡ�����лض����ݺ�,д��clr�ź����־λ,�����������ֱ�ӿ���MIPI��־λ��ͬ
   UNION�ṹ:  BBPCOMM_RD_RESULT_FLAG_MIPI1_CLR_UNION */
#define BBPCOMM_RD_RESULT_FLAG_MIPI1_CLR_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x3D4)

/* �Ĵ���˵�����Ĵ���
   ��      ���������ֱ�ӿ���MIPI1 master,������xbbp���ͻض�ָ��ʱ,�ض�ָ���ŵ�32bit.
   UNION�ṹ ���� */
#define BBPCOMM_MIPI1_RD_DATA_LOW_SOFT_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x3D8)

/* �Ĵ���˵�����Ĵ���
   ��      ���������ֱ�ӿ���MIPI1 master,������xbbp���ͻض�ָ��ʱ,�ض�ָ���Ÿ�32bit.
   UNION�ṹ ���� */
#define BBPCOMM_MIPI1_RD_DATA_HIGH_SOFT_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x3DC)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      �����ֱ�ӿ���MIPI1 master,������xbbp���ͻض�ָ��ʱ,�ض�������Чָʾ
   UNION�ṹ:  BBPCOMM_RD_END_FLAG_MIPI1_SOFT_UNION */
#define BBPCOMM_RD_END_FLAG_MIPI1_SOFT_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x3E0)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      �����ֱ�ӿ���MIPI1 master
             1:������Է���CFG_IND����mipi1
             0:����ȴ�mipi1��Ȩʹ��
   UNION�ṹ:  BBPCOMM_MIPI1_GRANT_DSP_UNION */
#define BBPCOMM_MIPI1_GRANT_DSP_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x3E4)

/* �Ĵ���˵�����Ĵ���
   ��      ���������ֱ�ӿ���MIPI1 master,������xbbp����дָ��ʱ,дָ���32bit��
               ��MIPI��̬ʹ��mipi_dyn_exchg_en��Ч����MIPI��չָ��ʱ
               dsp_mipi1_wdata_low[1:0]Ӧ����Ϊ1
   UNION�ṹ ���� */
#define BBPCOMM_DSP_MIPI1_WDATA_LOW_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x3E8)

/* �Ĵ���˵�����Ĵ���
   ��      ���������ֱ�ӿ���MIPI1 master,������xbbp����дָ��ʱ,дָ���32bit��
               ��MIPI��̬ʹ��mipi_dyn_exchg_en��Ч����MIPI����չָ��ʱ
               dsp_mipi1_wdata_high[1:0]Ӧ����Ϊ1
   UNION�ṹ ���� */
#define BBPCOMM_DSP_MIPI1_WDATA_HIGH_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x3EC)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      �����ֱ�ӿ���MIPI1 master,���������ߴ�ָʾ,����xbbp��MIPI1�Ŀ���
   UNION�ṹ:  BBPCOMM_DSP_MIPI1_EN_IMI_UNION */
#define BBPCOMM_DSP_MIPI1_EN_IMI_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x3F0)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      �����ֱ�ӿ���MIPI1 master,���ߴ�dsp_mipi1_en��,���������������
   UNION�ṹ:  BBPCOMM_DSP_MIPI1_CFG_IND_IMI_UNION */
#define BBPCOMM_DSP_MIPI1_CFG_IND_IMI_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x3F4)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      �����ֱ�ӿ���MIPI1 master,ȡ�߻ض����ݺ�,���־λ����
   UNION�ṹ:  BBPCOMM_DSP_MIPI1_RD_CLR_UNION */
#define BBPCOMM_DSP_MIPI1_RD_CLR_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x3F8)

/* �Ĵ���˵�����Ĵ���
 bit[31:9]   ����
 bit[8:8]    ���ǿ��ģʽabb1_rxb_blk_en.
 bit[7:7]    ���ǿ��ģʽabb1_rxa_blk_en.
 bit[6:6]    ���ǿ��ģʽabb1_rxb_en.
 bit[5:5]    ���ǿ��ģʽabb1_rxa_en.
 bit[4:4]    ���ǿ��ģʽabb1_tx_en.
 bit[3:1]    ���ǿ��ģʽabb1_mode_sel.
 bit[0:0]    ABB1�߿�ǿ��ģʽ��
             1����ʾ���ǿ�䣬��ʱ��������ǿ�����Ч��
             0����ʾ��CTU���ݸ�BBP������
             Ĭ��ֵΪ0��
             �����á�
   UNION�ṹ:  BBPCOMM_ABB1_LINE_CONTROL_CMD_UNION */
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x3FC)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    V9R1�汾����������á�
   UNION�ṹ:  BBPCOMM_CH1_BBP_SEL_UNION */
#define BBPCOMM_CH1_BBP_SEL_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x400)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      cpu����mipi����,����Ϊ1������������, ����ʱ����Ϊ0
   UNION�ṹ:  BBPCOMM_CPU_MIPI1_FUNC_SEL_UNION */
#define BBPCOMM_CPU_MIPI1_FUNC_SEL_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x404)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      cpu����mipi����,������
   UNION�ṹ:  BBPCOMM_CPU_MIPI1_TEST_FUNC_UNION */
#define BBPCOMM_CPU_MIPI1_TEST_FUNC_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x408)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      cpu����mipi����,������
   UNION�ṹ:  BBPCOMM_CPU_MIPI1_SCLK_TEST_UNION */
#define BBPCOMM_CPU_MIPI1_SCLK_TEST_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x40C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      cpu����mipi����,������
   UNION�ṹ:  BBPCOMM_CPU_MIPI1_SDATA_TEST_UNION */
#define BBPCOMM_CPU_MIPI1_SDATA_TEST_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x410)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      cpu����mipi����,mipi1master���쳣�ź�
   UNION�ṹ:  BBPCOMM_DSP_MIPI1_CLR_IND_IMI_UNION */
#define BBPCOMM_DSP_MIPI1_CLR_IND_IMI_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x414)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      mipi1�洢����������ͬ��FIFO��λ�ź�
   UNION�ṹ:  BBPCOMM_CPU_MIPI1_FIFO_CLR_IMI_UNION */
#define BBPCOMM_CPU_MIPI1_FIFO_CLR_IMI_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x418)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ssi1�洢����������ͬ��FIFO��λ�ź�
   UNION�ṹ:  BBPCOMM_CPU_SSI1_FIFO_CLR_IMI_UNION */
#define BBPCOMM_CPU_SSI1_FIFO_CLR_IMI_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x41C)

/* �Ĵ���˵����
 bit[31:12]  ����
 bit[11]     Cģͨ��1 TX ABB��·ʱ���ſ���·�ź�
 bit[10]     Cģͨ��1 RX ABB��·ʱ���ſ���·�ź�
 bit[9]      G2ͨ��1 TX ABB��·ʱ���ſ���·�ź�
 bit[8]      G1ͨ��1 TX ABB��·ʱ���ſ���·�ź�
 bit[7]      Wģͨ��1 TX ABB��·ʱ���ſ���·�ź�
 bit[6]      TDSͨ��1 TX ABB��·ʱ���ſ���·�ź�
 bit[5]      Lģͨ��1 TX ABB��·ʱ���ſ���·�ź�
 bit[4]      G2ͨ��1 RX ABB��·ʱ���ſ���·�ź�
 bit[3]      G1ͨ��1 RX ABB��·ʱ���ſ���·�ź�
 bit[2]      Wģͨ��1 RX ABB��·ʱ���ſ���·�ź�
 bit[1]      TDSͨ��1 RX ABB��·ʱ���ſ���·�ź�
 bit[0]      Lģͨ��1 RX ABB��·ʱ���ſ���·�ź�
   UNION�ṹ:  BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_UNION */
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x420)

/* �Ĵ���˵������ʱ����ʹ��ָʾ�Ĵ���
 bit[31:6]   ����
 bit[5:4]    ��ʾtiming_get_mode��Чʱbbe��ȡCģbbp���������1x��evdo����base_cnt��   00��1x��ʱ��01��evdo��ʱ��10�� base_cnt ��11����Ч��
             timing_get_mode��Чʱ���������ã�������
 bit[3:1]    ����
 bit[0]      �߼������㡣
             timing_get_mode��Ч��DSP��Ҫ��ȡ��ʱ��ϵʱ������Ч��CTU�߼����ݴ��ź�����LTE/W/Gm/Gs/TDS/C��ϵͳ��ʱ��CTU���ڲ���ʱ��DSP��ѯ��
             timing_get_mode��Ч��bbe16��Ҫ��ȡ��ʱ��ϵʱ������Ч��CTU�߼����ݴ��ź�����LTE/W/Gm/Gs/TDS/C��ϵͳ��ʱ��CTU���ڲ���ʱ��bbe16��ѯ��
             ����ʱ�̣������Ҫ���涨ʱ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_TIMING_GET_IND_UNION */
#define BBPCOMM_TIMING_GET_IND_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x610)

/* �Ĵ���˵������ʱ��־����Ĵ���
 bit[31:2]   ����
 bit[1]      �߼������㡣
             32������ʱ��Ϣ�ı�־������������timing_valid��־��
             ����ʱ�̣�DSP��ȡ��ʱ��Ϻ�����
             ��Чʱ�̣�������Ч
             ����Ϊ32K��ʱ��Ϣ���ϱ���ʱԶ��������ϵͳ�Ķ�ʱ��Ϣ�����Ե�������
             ��timing_get_mode��Ч��dsp���ƣ�
             timing_get_mode��Ч��bbe16���ƣ�
 bit[0]      �߼������㡣
             ��ʱ��־������������timing_valid��־��
             ����ʱ�̣�DSP��ȡ��ʱ��Ϻ�����
             ��Чʱ�̣�������Ч
             ��timing_get_mode��Ч��dsp���ƣ�
             timing_get_mode��Ч��bbe16���ƣ�
   UNION�ṹ:  BBPCOMM_TIMING_CLEAR_UNION */
#define BBPCOMM_TIMING_CLEAR_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x614)

/* �Ĵ���˵������ʱ�����ӳټĴ���
 bit[31:5]   ����
 bit[4:0]    CTU��⵽timing_get_ind��̶��ӳ�delay_cnt��CTUʱ�����ں�����timing_valid�źš�
             ����ʱ�̣��ϵ��ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_DELAY_CNT_UNION */
#define BBPCOMM_DELAY_CNT_ADDR                        (SOC_BBP_COMM_BASE_ADDR + 0x618)

/* �Ĵ���˵�����ж��ӳټĴ���
 bit[31:16]  ����
 bit[15:0]   CTU�ж��ϱ��ȴ�ʱ�䣬��λΪһ��CLK���ڡ�
             DSP����жϱ�־�Ĵ�����ĳ������bit��CTU�ϱ��жϵ�ƽ��Ҫ���ͣ������ʱ�жϱ�־�Ĵ������������ж�������Ч������ȴ�int_wait_cnt��ʱ�����ں�������CTU�ϱ��жϡ�
             ����ʱ�̣��ϵ��ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_WAIT_CNT_UNION */
#define BBPCOMM_INT_WAIT_CNT_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x61C)

/* �Ĵ���˵�����Ĵ���
 bit[31:2]   ����
 bit[1:0]    ��ƽ�źţ�����Ч��
             ��LTE��ģ��Ҫ����ϵͳ����ʱ�����ñ��Ĵ���Ϊ3����ϵͳ�������������ñ��Ĵ���Ϊ0��
             bit1:1��b0: lte_intrasys_valid������Ч����ǿ��Ϊ1��
             bit0:1��b0:
             lte_intersys_ingap_pre_ind������Ч����ǿ��Ϊ0��
             bit[1:0] = 11b: ��lte_intrasys_valid��lte_intersys_ingap_pre_ind������Ч��
             
             ����ʱ�̣�LTE��ģ��Ҫ����ϵͳ����ʱ�����ñ��Ĵ���Ϊ3����ϵͳ�������������ñ��Ĵ���Ϊ0��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_LTEBBP_INPUT_MASK_UNION */
#define BBPCOMM_LTEBBP_INPUT_MASK_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x620)

/* �Ĵ���˵�����Ĵ���
 bit[31:2]   ����
 bit[1:0]    ��ƽ�źţ�����Ч��
             ��W��ģ��Ҫ����ϵͳ����ʱ�����ñ��Ĵ���Ϊ3����ϵͳ�������������ñ��Ĵ���Ϊ0��
             bit1:1��b0:
              ��w_intrasys_valid������Ч����ǿ��Ϊ1��
             bit0:1��b0:
             w_intersys_ingap_pre_ind������Ч����ǿ��Ϊ0��
             bit[1:0] = 11b: ��w_intrasys_valid��w_intersys_ingap_pre_ind������Ч��
             
             ����ʱ�̣�W��ģ��Ҫ����ϵͳ����ʱ�����ñ��Ĵ���Ϊ3����ϵͳ�������������ñ��Ĵ���Ϊ0��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_WBBP_INPUT_MASK_UNION */
#define BBPCOMM_WBBP_INPUT_MASK_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x624)

/* �Ĵ���˵�����Ĵ���
 bit[31:2]   ����
 bit[1:0]    ��ƽ�źţ�����Ч��
             ��Gm��ģ��Ҫ����ϵͳ����ʱ�����ñ��Ĵ���Ϊ3����ϵͳ�������������ñ��Ĵ���Ϊ0��
             bit1:1��b0:
              ��gm_intrasys_valid������Ч����ǿ��Ϊ1��
             bit0:1��b0:
             gm_intersys_ingap_pre_ind������Ч����ǿ��Ϊ0��
             bit[1:0] = 11b: ��gm_intrasys_valid��gm_intersys_ingap_pre_ind������Ч��
             
             ����ʱ�̣�Gm��ģ��Ҫ����ϵͳ����ʱ�����ñ��Ĵ���Ϊ3����ϵͳ�������������ñ��Ĵ���Ϊ0��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_GMBBP_INPUT_MASK_UNION */
#define BBPCOMM_GMBBP_INPUT_MASK_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x628)

/* �Ĵ���˵�����Ĵ���
 bit[31:2]   ����
 bit[1:0]    ��ƽ�źţ�����Ч��
             ��Gs��ģ��Ҫ����ϵͳ����ʱ�����ñ��Ĵ���Ϊ3����ϵͳ�������������ñ��Ĵ���Ϊ0��
             bit1:1��b0:
              ��gs_intrasys_valid������Ч����ǿ��Ϊ1��
             bit0:1��b0:
             gs_intersys_ingap_pre_ind������Ч����ǿ��Ϊ0��
             bit[1:0] = 11b: ��gs_intrasys_valid��gs_intersys_ingap_pre_ind������Ч��
             
             ����ʱ�̣�Gs��ģ��Ҫ����ϵͳ����ʱ�����ñ��Ĵ���Ϊ3����ϵͳ�������������ñ��Ĵ���Ϊ0��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_GSBBP_INPUT_MASK_UNION */
#define BBPCOMM_GSBBP_INPUT_MASK_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x62C)

/* �Ĵ���˵�����Ĵ���
 bit[31:2]   ����
 bit[1:0]    ��ƽ�źţ�����Ч��
             ��TDS��ģ��Ҫ����ϵͳ����ʱ�����ñ��Ĵ���Ϊ3����ϵͳ�������������ñ��Ĵ���Ϊ0��
             bit1:1��b0:
              ��tds_intrasys_valid������Ч����ǿ��Ϊ1��
             bit0:1��b0:
             tds_intersys_ingap_pre_ind������Ч����ǿ��Ϊ0��
             bit[1:0] = 11b: ��tds_intrasys_valid��tds_intersys_ingap_pre_ind������Ч��
             
             ����ʱ�̣�TDS��ģ��Ҫ����ϵͳ����ʱ�����ñ��Ĵ���Ϊ3����ϵͳ�������������ñ��Ĵ���Ϊ0��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_TDSBBP_INPUT_MASK_UNION */
#define BBPCOMM_TDSBBP_INPUT_MASK_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x630)

/* �Ĵ���˵�����Ĵ���
   ��      ���������ṩLTE�ĸ�֡�ţ���LDSP���¡�ȡֵ��Χ��0��1223��
               
               ����ʱ�̣�
               ��Чʱ�̣�������Ч
   UNION�ṹ ���� */
#define BBPCOMM_LTE_MUX_FRAME_NUM_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x634)

/* �Ĵ���˵�����Ĵ���
   ��      ���������ṩTDS�ĸ�֡�ţ���TDSP���¡�ȡֵ��Χ��0��1223��
               
               ����ʱ�̣�
               ��Чʱ�̣�������Ч
   UNION�ṹ ���� */
#define BBPCOMM_TDS_MUX_FRAME_NUM_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x638)

/* �Ĵ���˵�����Ĵ���
   ��      ���������ṩw�ĸ�֡�ţ���wDSP���¡�
               ����ʱ�̣�
               ��Чʱ�̣�������Ч
   UNION�ṹ ���� */
#define BBPCOMM_W_MUX_FRAME_NUM_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x63C)

/* �Ĵ���˵�����Ĵ���
   ��      ����W/TD/GM/GS/CΪ��ģʱд�˼Ĵ�����LΪ��ģʱ��ȡ�˼Ĵ������˼Ĵ�����DSP֮����ж�д��BBP���ṩ�ӿڡ�
   UNION�ṹ ���� */
#define BBPCOMM_MEAS_FLAG_L_RD_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x640)

/* �Ĵ���˵�����Ĵ���
   ��      ����L/TD/GM/GS/CΪ��ģʱд�˼Ĵ�����WΪ��ģʱ��ȡ�˼Ĵ������˼Ĵ�����DSP֮����ж�д��BBP���ṩ�ӿڡ�
   UNION�ṹ ���� */
#define BBPCOMM_MEAS_FLAG_W_RD_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x644)

/* �Ĵ���˵�����Ĵ���
   ��      ����W/L/GM/GSΪ/C��ģʱд�˼Ĵ�����TDΪ��ģʱ��ȡ�˼Ĵ������˼Ĵ�����DSP֮����ж�д��BBP���ṩ�ӿڡ�
   UNION�ṹ ���� */
#define BBPCOMM_MEAS_FLAG_T_RD_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x648)

/* �Ĵ���˵�����Ĵ���
   ��      ����W/TD/L/GS/CΪ��ģʱд�˼Ĵ�����GMΪ��ģʱ��ȡ�˼Ĵ������˼Ĵ�����DSP֮����ж�д��BBP���ṩ�ӿڡ�
   UNION�ṹ ���� */
#define BBPCOMM_MEAS_FLAG_GM_RD_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x64C)

/* �Ĵ���˵�����Ĵ���
   ��      ����W/TD/GM/L/CΪ��ģʱд�˼Ĵ�����GSΪ��ģʱ��ȡ�˼Ĵ������˼Ĵ�����DSP֮����ж�д��BBP���ṩ�ӿڡ�
   UNION�ṹ ���� */
#define BBPCOMM_MEAS_FLAG_GS_RD_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x650)

/* �Ĵ���˵�����Ĵ���
   ��      ����LΪ��ģʱд�˼Ĵ�����W/TD/GM/GS/C��ģ��ȡ�˼Ĵ������˼Ĵ�����DSP֮����ж�д��BBP���ṩ�ӿڡ�
   UNION�ṹ ���� */
#define BBPCOMM_WAKE_FLAG_L_WR_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x654)

/* �Ĵ���˵�����Ĵ���
   ��      ����WΪ��ģʱд�˼Ĵ�����L/TD/GM/GS/C��ģ��ȡ�˼Ĵ������˼Ĵ�����DSP֮����ж�д��BBP���ṩ�ӿڡ�
   UNION�ṹ ���� */
#define BBPCOMM_WAKE_FLAG_W_WR_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x658)

/* �Ĵ���˵�����Ĵ���
   ��      ����TDΪ��ģʱд�˼Ĵ�����W/L/GM/GS/C��ģ��ȡ�˼Ĵ������˼Ĵ�����DSP֮����ж�д��BBP���ṩ�ӿڡ�
   UNION�ṹ ���� */
#define BBPCOMM_WAKE_FLAG_T_WR_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x65C)

/* �Ĵ���˵�����Ĵ���
   ��      ����GMΪ��ģʱд�˼Ĵ�����W/TD/L/GS/C��ģ��ȡ�˼Ĵ������˼Ĵ�����DSP֮����ж�д��BBP���ṩ�ӿڡ�
   UNION�ṹ ���� */
#define BBPCOMM_WAKE_FLAG_GM_WR_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x660)

/* �Ĵ���˵�����Ĵ���
   ��      ����GSΪ��ģʱд�˼Ĵ�����W/TD/GM/L/C��ģ��ȡ�˼Ĵ������˼Ĵ�����DSP֮����ж�д��BBP���ṩ�ӿڡ�
   UNION�ṹ ���� */
#define BBPCOMM_WAKE_FLAG_GS_WR_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x664)

/* �Ĵ���˵�����Ĵ���
 bit[31:6]   ����
 bit[5:4]    ��ʾo_timing_valid��Чʱ���ϱ�cģ�ļ�������bbe16����1x��evdo����base_cnt
             00��1x��ʱ
             01�� evdo��ʱ
             10�� basecent
 bit[3]      ����
 bit[2]      ��ʾbbe16��ȡ��ʱ��Ϣ��ʱ���ڳ�ʱ����ʱ����δ����o_timing_clear�źţ�
 bit[1]      32K������ʱ�ϱ���Ч��־������Ч��
             DSP����timing_get_ind�󣬲�ѯ�˱�־�����Ϊ�ߣ�����Ի�ȡ32K������ʱ���Ķ�ʱ��Ϣ��
             DSP��ȡ��ʱ��Ϻ�����comm_32k_timing_clear�Ĵ�����comm_32k_timing_valid����Ϊ��Ч��
             32K��ʱ�����ȶ�������comm_32k_timing_valid
             ����ʱ�̣�
             ��Чʱ�̣�������Ч
             ��timing_get_mode��Ч��dsp���ƣ�
             timing_get_mode��Ч��bbe16���ƣ�
 bit[0]      ��ʱ�ϱ���Ч��־������Ч��
             DSP����timing_get_ind�󣬲�ѯ�˱�־�����Ϊ�ߣ�����Ի�ȡLTE��W��Gm��Gs, TDS��ϵͳ��ʱ��
             DSP��ȡ��ʱ��Ϻ�����timing_clear�Ĵ�����timing_valid����Ϊ��Ч��
             CTU��⵽timing_get_ind��̶��ӳ�delay_cnt������timing_valid��
             
             ����ʱ�̣�
             ��Чʱ�̣�������Ч
             ��timing_get_mode��Ч��dsp���ƣ�
             timing_get_mode��Ч��bbe16���ƣ�
   UNION�ṹ:  BBPCOMM_TIMING_VALID_UNION */
#define BBPCOMM_TIMING_VALID_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x668)

/* �Ĵ���˵�����Ĵ���
 bit[31:20]  W��ϵͳ��ʱ��Ϣ����DSP ����timing_get_ind�����ϱ���
             �ϱ�ʱ�̣�timing_validΪ��ʱ�ϱ���Ч.
             [31:20]��ʾW��SFN������Դ��w_timing_b[11:0]������Χ0~4095��
 bit[19:16]  [19:16]Ϊʱ϶��������Χ0~14
 bit[15:4]   [15:4]Ϊʱ϶��chip��������Χ0~2559
 bit[3:0]    [3:0]Ϊchip��ʱ�Ӽ�������Χ0~15
   UNION�ṹ:  BBPCOMM_W_TIMING_DSP_UNION */
#define BBPCOMM_W_TIMING_DSP_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x66C)

/* �Ĵ���˵�����Ĵ���
 bit[31:22]  ����
 bit[21:0]   GM��FN������Դ��gm_timing_a[21:0]������DSP ����timing_get_ind�����ϱ�������[10:0]��ʾfn_low,��Χ0~1325��[21:11]��ʾfn_hign,��Χ0~2047��
             �ϱ�ʱ�̣�timing_validΪ��ʱ�ϱ���Ч
   UNION�ṹ:  BBPCOMM_GM_FN_DSP_UNION */
#define BBPCOMM_GM_FN_DSP_ADDR                        (SOC_BBP_COMM_BASE_ADDR + 0x670)

/* �Ĵ���˵�����Ĵ���
 bit[31:13]  ����
 bit[12:0]   GM��ϵͳ��ʱQb��Ϣ����DSP ����timing_get_ind�����ϱ���
              [12:0]��ʾ Gϵͳ��ʱ֡��Qb������Դ��gm_timing_b[12:0]������Χ0~4999��
             �ϱ�ʱ�̣�timing_validΪ��ʱ�ϱ���Ч
   UNION�ṹ:  BBPCOMM_GM_QB_DSP_UNION */
#define BBPCOMM_GM_QB_DSP_ADDR                        (SOC_BBP_COMM_BASE_ADDR + 0x674)

/* �Ĵ���˵�����Ĵ���
 bit[31:22]  ����
 bit[21:0]   GS��FN������Դ��gs_timing_a[21:0]������DSP ����timing_get_ind�����ϱ�������[10:0]��ʾfn_low,��Χ0~1325��[21:11]��ʾfn_hign,��Χ0~2047��
             �ϱ�ʱ�̣�timing_validΪ��ʱ�ϱ���Ч
   UNION�ṹ:  BBPCOMM_GS_FN_DSP_UNION */
#define BBPCOMM_GS_FN_DSP_ADDR                        (SOC_BBP_COMM_BASE_ADDR + 0x678)

/* �Ĵ���˵�����Ĵ���
 bit[31:13]  ����
 bit[12:0]   GS��ϵͳ��ʱQb��Ϣ����DSP ����timing_get_ind�����ϱ���
              [12:0]��ʾ GSϵͳ��ʱ֡��Qb������Դ��gs_timing_b[12:0]������Χ0~4999��
             �ϱ�ʱ�̣�timing_validΪ��ʱ�ϱ���Ч
   UNION�ṹ:  BBPCOMM_GS_QB_DSP_UNION */
#define BBPCOMM_GS_QB_DSP_ADDR                        (SOC_BBP_COMM_BASE_ADDR + 0x67C)

/* �Ĵ���˵�����Ĵ���
 bit[31:30]  ����
 bit[29:20]  LTE��ϵͳ��ʱ����DSP ����timing_get_ind�����ϱ����ϱ�ʱ�̣�timing_validΪ��ʱ�ϱ���Ч��
             ����:
             [29:20]��ʾSFN��������Χ0~1023
 bit[19:16]  [19:16]����֡����
 bit[15:15]  ����
 bit[14:0]   [14:0]����֡�ڼ����� 
   UNION�ṹ:  BBPCOMM_LTE_TIMING_DSP_UNION */
#define BBPCOMM_LTE_TIMING_DSP_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x680)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   TDS��ϵͳ��ʱ����DSP ����timing_get_ind�����ϱ������Ĵ����ϱ�����TDS��tcfsrϵͳ��֡��0~65535ѭ��������TDSʵ����Ч��֡��ΧΪ0~8191
             �ϱ�ʱ�̣�timing_validΪ��ʱ�ϱ���Ч
   UNION�ṹ:  BBPCOMM_TDS_TIMING1_DSP_UNION */
#define BBPCOMM_TDS_TIMING1_DSP_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x684)

/* �Ĵ���˵�����Ĵ���
 bit[31:20]  ����
 bit[19:0]   TDS��ϵͳ��ʱ����DSP ����timing_get_ind�����ϱ������Ĵ����ϱ�������TDS��framc֡����
             �ϱ�ʱ�̣�timing_validΪ��ʱ�ϱ���Ч
   UNION�ṹ:  BBPCOMM_TDS_TIMING2_DSP_UNION */
#define BBPCOMM_TDS_TIMING2_DSP_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x688)

/* �Ĵ���˵�����Ĵ���
   ��      ����CTU�ڲ���ʱ����DSP ����timing_get_ind�����ϱ���������ʹ��������
               �ϱ�ʱ�̣�timing_validΪ��ʱ�ϱ���Ч
   UNION�ṹ ���� */
#define BBPCOMM_CTU_TIMING_DSP_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x68C)

/* �Ĵ���˵�����Ĵ���
   ��      ����CTU�ڲ���ʱ����������ʱ�Ӿͼ�����������ͷ��ʼ��������ʹ��������
               �ϱ�ʱ�̣���ʱ��ȡ��
   UNION�ṹ ���� */
#define BBPCOMM_CTU_BASECNT1_DSP_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x690)

/* �Ĵ���˵�����Ĵ���
   ��      ����CTU�ڲ���ʱ��ʹ��clk_19m_bbp_socʱ�Ӽ�����
               ����ģ��int0��int1��int2��ʱ�̴����ϱ���
   UNION�ṹ ���� */
#define BBPCOMM_CTU_BASECNT2_DSP_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x694)

/* �Ĵ���˵�����Ĵ���
 bit[31:2]   ����
 bit[1]      w��ģ��ʵ�ʿ���RFָʾ����ƽ�źš�Ϊ1����W����RF����ͨ����Ϊ0�����ģ���Կ���RFͨ�������ڵ�RFICʱ��Ƶ��������źŵ�ѡͨ��
             w_intrasys_valid_delay�������ر�w_intrasys_valid�������ͺ��½���һ�¡�
 bit[0]      w��ģ�¿���RFָʾ����ƽ�źš�
             1��b0: W����RF����Ȩ��
             1��b1: W���п���RFȨ����ʵ������RF��w_intrasys_valid_delay�ź�Ϊ1����
   UNION�ṹ:  BBPCOMM_W_INTRASYS_VALID_UNION */
#define BBPCOMM_W_INTRASYS_VALID_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x698)

/* �Ĵ���˵�����Ĵ���
 bit[31:2]   ����
 bit[1]      gm��ģ��ʵ�ʿ���RFָʾ����ƽ�źš�Ϊ1����gm����RF����ͨ����Ϊ0�����ģ���Կ���RFͨ�������ڵ�RFICʱ��Ƶ��������źŵ�ѡͨ��
             gm_intrasys_valid_delay�������ر�gm_intrasys_valid�������ͺ��½���һ�¡�
 bit[0]      gm��ģ�¿���RFָʾ����ƽ�źš�
             1��b0: gm����RF����Ȩ��
             1��b1: gm���п���RFȨ����ʵ������RF��gm_intrasys_valid_delay�ź�Ϊ1����
   UNION�ṹ:  BBPCOMM_GM_INTRASYS_VALID_UNION */
#define BBPCOMM_GM_INTRASYS_VALID_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x69C)

/* �Ĵ���˵�����Ĵ���
 bit[31:2]   ����
 bit[1]      gs��ģ��ʵ�ʿ���RFָʾ����ƽ�źš�Ϊ1����gs����RF����ͨ����Ϊ0�����ģ���Կ���RFͨ�������ڵ�RFICʱ��Ƶ��������źŵ�ѡͨ��
             gs_intrasys_valid_delay�������ر�gs_intrasys_valid�������ͺ��½���һ�¡�
 bit[0]      gs��ģ�¿���RFָʾ����ƽ�źš�
             1��b0: gs����RF����Ȩ��
             1��b1: gs���п���RFȨ����ʵ������RF��gs_intrasys_valid_delay�ź�Ϊ1����
   UNION�ṹ:  BBPCOMM_GS_INTRASYS_VALID_UNION */
#define BBPCOMM_GS_INTRASYS_VALID_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x6A0)

/* �Ĵ���˵�����Ĵ���
 bit[31:2]   ����
 bit[1]      LTE��ģ��ʵ�ʿ���RFָʾ����ƽ�źš�Ϊ1����LTE����RF����ͨ����Ϊ0�����ģ���Կ���RFͨ�������ڵ�RFICʱ��Ƶ��������źŵ�ѡͨ��
             lte_intrasys_valid_delay�������ر�lte_intrasys_valid�������ͺ��½���һ�¡�
 bit[0]      Lte��ģ�¿���RFָʾ����ƽ�źš�
             1��b0: LTE����RF����Ȩ��
             1��b1: LTE���п���RFȨ����ʵ������RF��lte_intrasys_valid_delay�ź�Ϊ1����
   UNION�ṹ:  BBPCOMM_LTE_INTRASYS_VALID_UNION */
#define BBPCOMM_LTE_INTRASYS_VALID_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x6A4)

/* �Ĵ���˵�����Ĵ���
 bit[31:2]   ����
 bit[1]      TDS��ģ��ʵ�ʿ���RFָʾ����ƽ�źš�Ϊ1����TDS����RF����ͨ����Ϊ0�����ģ���Կ���RFͨ�������ڵ�RFICʱ��Ƶ��������źŵ�ѡͨ��
             tds_intrasys_valid_delay�������ر�tds_intrasys_valid�������ͺ��½���һ�¡�
 bit[0]      TDS��ģ�¿���RFָʾ����ƽ�źš�
             1��b0: TDS����RF����Ȩ��
             1��b1: TDS���п���RFȨ����ʵ������RF��tds_intrasys_valid_delay�ź�Ϊ1����
   UNION�ṹ:  BBPCOMM_TDS_INTRASYS_VALID_UNION */
#define BBPCOMM_TDS_INTRASYS_VALID_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x6A8)

/* �Ĵ���˵�����Ĵ���
 bit[31:9]   ����
 bit[8:6]    SSI2master�ȴ�ʱ��
 bit[5:3]    SSI1master�ȴ�ʱ��
 bit[2:0]    SSI0master�ȴ�ʱ��
   UNION�ṹ:  BBPCOMM_RFIC_CK_CFG_UNION */
#define BBPCOMM_RFIC_CK_CFG_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x6AC)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:8]   ͨ��xbbp��SSI master�����ض���ָ��ʱ,DSP�ȴ��ض������������
 bit[7:0]    ͨ��xbbp��MIPI master�����ض���ָ��ʱ,DSP�ȴ��ض������������
   UNION�ṹ:  BBPCOMM_DSP_WAITTIME_UNION */
#define BBPCOMM_DSP_WAITTIME_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x6B4)

/* �Ĵ���˵�����Ĵ���
   ��      ����CTU�ڲ�19.2M��������ʱ�������ϱ����
   UNION�ṹ ���� */
#define BBPCOMM_CTU_BASECNT_DSP_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x6B8)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      CTU�ڲ�19.2M��������ʱ�����������ȡʹ��
   UNION�ṹ:  BBPCOMM_DSP_CTU_TIMING_GET_IND_UNION */
#define BBPCOMM_DSP_CTU_TIMING_GET_IND_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x6BC)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      CTU�ڲ�19.2M��������ʱ�����������ȡ��Чָʾ
   UNION�ṹ:  BBPCOMM_CTU_TIMING_VALID_DSP_UNION */
#define BBPCOMM_CTU_TIMING_VALID_DSP_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x6C0)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      CTU�ڲ�19.2M��������ʱ�����������ȡ������ʹ��
   UNION�ṹ:  BBPCOMM_DSP_CTU_TIMING_CLR_UNION */
#define BBPCOMM_DSP_CTU_TIMING_CLR_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x6C4)

/* �Ĵ���˵�����Ĵ���
 bit[31:4]   ����
 bit[3:0]    ��ϵͳ�������͡�
             4��b0������3G��
             4��b1: 3G�����ѣ�
             4��d2: 3G ANR��
             ����Ԥ����
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_W_INTERSYS_MEASURE_TYPE_UNION */
#define BBPCOMM_W_INTERSYS_MEASURE_TYPE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x6C8)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    ��Ƶ��������ڵ�ָʾ��L����TDS/Gm/Gs��Ϊ��ģ��֪ͨW DSP W�����ĵ�Ƶ�����ڵ��
             ֻ������̬����Ҫ���á�
             ��ƽ�źţ�����Ч��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_W_MEASURE_REPORT_VALID_UNION */
#define BBPCOMM_W_MEASURE_REPORT_VALID_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x6CC)

/* �Ĵ���˵�����Ĵ���
   ��      ����Ԥ�����ж�int0��int1֮���offset��Ϣ����λus������ȡ��������
               ����ʱ�̣���ģ����W��ģ��ϵͳ����ʱ����
               ��Чʱ�̣�������Ч
   UNION�ṹ ���� */
#define BBPCOMM_W_PREINT_OFFSET_TIME_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x6D0)

/* �Ĵ���˵�����Ĵ���
   ��      ����W��Ϊ��ģʱ����ģ�����W������ϵͳ����ʱ�䳤�ȣ���֪WDSP����λus������ȡ����us��
               ����ʱ�̣���ģ����W��ģ��ϵͳ����ʱ����
               ��Чʱ�̣�������Ч
   UNION�ṹ ���� */
#define BBPCOMM_W_INTERSYS_MEASURE_TIME_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x6D4)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_W_RCV_LTE[15:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_W_RCV_LTE_UNION */
#define BBPCOMM_INT_CLEAR_W_RCV_LTE_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x6D8)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_W_RCV_TDS[15:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_W_RCV_TDS_UNION */
#define BBPCOMM_INT_CLEAR_W_RCV_TDS_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x6DC)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_W_RCV_GM[15:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_W_RCV_GM_UNION */
#define BBPCOMM_INT_CLEAR_W_RCV_GM_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x6E0)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_W_RCV_GS[15:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_W_RCV_GS_UNION */
#define BBPCOMM_INT_CLEAR_W_RCV_GS_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x6E4)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_W_RCV_W[15:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_W_RCV_W_UNION */
#define BBPCOMM_INT_CLEAR_W_RCV_W_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x6E8)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_W_INT012[2:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_W_INT012_UNION */
#define BBPCOMM_INT_CLEAR_W_INT012_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x6EC)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж����α�־����������INT_TYPE_W_RCV_LTE[15:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_W_RCV_LTE_UNION */
#define BBPCOMM_INT_MASK_W_RCV_LTE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x6F0)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж����α�־����������INT_TYPE_W_RCV_TDS[15:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_W_RCV_TDS_UNION */
#define BBPCOMM_INT_MASK_W_RCV_TDS_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x6F4)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж����α�־����������INT_TYPE_W_RCV_GM[15:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_W_RCV_GM_UNION */
#define BBPCOMM_INT_MASK_W_RCV_GM_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x6F8)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж����α�־����������INT_TYPE_W_RCV_GS[15:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_W_RCV_GS_UNION */
#define BBPCOMM_INT_MASK_W_RCV_GS_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x6FC)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж����α�־����������INT_TYPE_W_RCV_W[15:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_W_RCV_W_UNION */
#define BBPCOMM_INT_MASK_W_RCV_W_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x700)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    �ж����α�־����������INT_TYPE_W_INT012[2:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_W_INT012_UNION */
#define BBPCOMM_INT_MASK_W_INT012_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x704)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
             [0]: �ж�����0�� LTE����ģ����ǰ֪ͨW��ϵͳ���������жϡ�
             [1]: �ж�����1�� LTE����ģ����GAP�жϣ�֪ͨW������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
             [2]: �ж�����2�� LTE����ģ����GAP�жϡ�
             [3]: �ж�����3��LTE����ģ�����������жϡ�
             [4]: �ж�����4��LTE����ģ��ǿ��W�˳���ϵͳ�����жϡ�
             [5]: �ж�����5��LTE����ģ��֪ͨW�ϱ����β��������
             [6]: ������
             [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x06F0��int_mask_w_rcv_lte���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_W_RCV_LTE_UNION */
#define BBPCOMM_INT_TYPE_W_RCV_LTE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x708)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж�״̬��־0��1��2ֻ�е�TDS������ģʱ���ܲ�����
             
             [0]: �ж�����0�� TDS����ģ����ǰ֪ͨW��ϵͳ���������жϡ�
             [1]: �ж�����1�� TDS����ģ����GAP�жϣ�֪ͨW������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
             [2]: �ж�����2�� TDS����ģ����GAP�жϡ�
             [3]: �ж�����3��TDS����ģ�����������жϡ�
             [4]: �ж�����4��TDS����ģ��ǿ��W�˳���ϵͳ�����жϡ�
             [5]: �ж�����5��TDS����ģ��֪ͨW�ϱ����β��������
             [6]: �ж�����6��������
             [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x06F4��int_mask_w_rcv_tds���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_W_RCV_TDS_UNION */
#define BBPCOMM_INT_TYPE_W_RCV_TDS_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x70C)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
             [0]: �ж�����0��GM����ģ����ǰ֪ͨW��ϵͳ���������жϡ�
             [1]: �ж�����1��GM����ģ����GAP�жϣ�֪ͨW������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
             [2]: �ж�����2��GM����ģ����GAP�жϡ�
             [3]: �ж�����3��GM����ģ�����������жϡ�
             [4]: �ж�����4��GM����ģ��ǿ��W�˳���ϵͳ�����жϡ�
             [5]: �ж�����5��GM����ģ��֪ͨW�ϱ����β��������
             [6]: �ж�����6��������
             [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
             �ж�״̬��־0��1��2ֻ�е�GM������ģʱ���ܲ�����
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x06F8��int_mask_w_rcv_gm���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_W_RCV_GM_UNION */
#define BBPCOMM_INT_TYPE_W_RCV_GM_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x710)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   [0]: �ж�����0��GS����ģ����ǰ֪ͨW��ϵͳ���������жϡ�
             [1]: �ж�����1��GS����ģ����GAP�жϣ�֪ͨW������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
             [2]: �ж�����2��GS����ģ����GAP�жϡ�
             [3]: �ж�����3��GS����ģ�����������жϡ�
             [4]: �ж�����4��GS����ģ��ǿ��W�˳���ϵͳ�����жϡ�
             [5]: �ж�����5��GS����ģ��֪ͨW�ϱ����β��������
             [6]: �ж�����6��������
             [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
             �ж�״̬��־0��1��2ֻ�е�TDS������ģʱ���ܲ�����
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x06FC��int_mask_w_rcv_gs���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_W_RCV_GS_UNION */
#define BBPCOMM_INT_TYPE_W_RCV_GS_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x714)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
             [0]: �ж�����0��W����ģ����ǰ֪ͨW��Ƶ���������жϡ�
             [1]: �ж�����1��W����ģ����GAP�жϣ�֪ͨW������Ƶ������Ƶͨ�����ã������л��Ȳ�����
             [2]: �ж�����2��W����ģ����GAP�жϡ�
             [3]: �ж�����3��W����ģ������Ƶ�����������жϡ�
             [4]: �ж�����4��W����ģ��ǿ��W�˳���Ƶ�����жϡ�
             [5]: �ж�����5��W����ģ��֪ͨW�ϱ����β��������
             [6]: �ж�����6��������
             [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
             �ж�״̬��־0��1��2ֻ�е�W������ģʱ���ܲ�����
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x0700��int_mask_w_rcv_w���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_W_RCV_W_UNION */
#define BBPCOMM_INT_TYPE_W_RCV_W_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x718)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    ������ģ����int0��1��2���ϱ���(������Ƶ����ϵͳ����)��������Ч��
             [0]: W��ģʱ��CTU����֪ͨWDSP����int0�жϡ�
             [1]: W��ģʱ��CTU����֪ͨWDSP����int1�жϡ�
             [2]: W��ģʱ��CTU����֪ͨWDSP����int2�жϡ�
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x0704��int_mask_w_int012���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_W_INT012_UNION */
#define BBPCOMM_INT_TYPE_W_INT012_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x71C)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:3]   �߼������㡣����Ч��
             
             bit15~7����Ӧw_snd_lte_int_15 ~ 7��
             W DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_lte_rcv_w[15:7]����LDSP��
             ��Чʱ�̣�������Ч
             
             bit6����Ӧw_snd_lte_int_6��
             WDSPͨ���˼Ĵ�����������6�жϣ�int_type_lte_rcv_w[6]����LDSP��
             ��Чʱ�̣�������Ч
             
             bit5����Ӧw_snd_lte_int_5��
             W��ģʱ֪ͨLDSP L�������ڵ������Ч��
             W DSPͨ���˼Ĵ�����������5�жϣ�int_type_lte_rcv_w[5]����LDSP��
             ��Чʱ�̣�������Ч
             
             bit4����Ӧw_snd_lte_int_4��
             W��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
             W DSPͨ���˼Ĵ�����������4�жϣ�int_type_lte_rcv_w[4]����LDSP��
             ��Чʱ�̣�������Ч
             
             bit3����Ӧw_snd_lte_int_3��W��������ָʾ������Ч��
             ���ڴ����ж�����3 ��int_type_lte_rcv_w[3]����LDSP��L��ģ�¶�W������ϵͳ����ʱ�����W����������W DSP���ô˱�־Ϊ1�� 
             ��Чʱ�̣�������Ч
 bit[2:0]    ����
   UNION�ṹ:  BBPCOMM_W_SND_LTE_INT_13_UNION */
#define BBPCOMM_W_SND_LTE_INT_13_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x720)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:3]   �߼������㡣����Ч��
             
             bit15~7����Ӧw_snd_tds_int_15 ~ 7��
             W DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_tds_rcv_w[15:7]����TDSP��
             ��Чʱ�̣�������Ч
             
             bit6����Ӧw_snd_tds_int_6��
             WDSPͨ���˼Ĵ�����������6�жϣ�int_type_tds_rcv_w[6]����TDSP��
             ��Чʱ�̣�������Ч
             
             bit5����Ӧw_snd_tds_int_5��
             W��ģʱ֪ͨTDSP T�������ڵ������Ч��
             W DSPͨ���˼Ĵ�����������5�жϣ�int_type_tds_rcv_w[5]����TDSP��
             ��Чʱ�̣�������Ч
             
             bit4����Ӧw_snd_tds_int_4��
             W��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
             W DSPͨ���˼Ĵ�����������4�жϣ�int_type_tds_rcv_w[4]����TDSP��
             ��Чʱ�̣�������Ч
             
             bit3����Ӧw_snd_tds_int_3��W��������ָʾ������Ч��
             ���ڴ����ж�����3 ��int_type_tds_rcv_w[3]����TDSP��T��ģ�¶�W������ϵͳ����ʱ�����W����������W DSP���ô˱�־Ϊ1�� 
             ��Чʱ�̣�������Ч
 bit[2:0]    ����
   UNION�ṹ:  BBPCOMM_W_SND_TDS_INT_13_UNION */
#define BBPCOMM_W_SND_TDS_INT_13_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x724)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:3]   �߼������㡣����Ч��
             
             bit15~7����Ӧw_snd_gm_int_15 ~ 7��
             W DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_gm_rcv_w[15:7]����GMDSP��
             ��Чʱ�̣�������Ч
             
             bit6����Ӧw_snd_gm_int_6��
             WDSPͨ���˼Ĵ�����������6�жϣ�int_type_gm_rcv_w[6]����GMDSP��
             ��Чʱ�̣�������Ч
             
             bit5����Ӧw_snd_gm_int_5��
             W��ģʱ֪ͨGMDSP GM�������ڵ������Ч��
             W DSPͨ���˼Ĵ�����������5�жϣ�int_type_gm_rcv_w[5]����GMDSP��
             ��Чʱ�̣�������Ч
             
             bit4����Ӧw_snd_gm_int_4��
             W��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
             W DSPͨ���˼Ĵ�����������4�жϣ�int_type_gm_rcv_w[4]����GMDSP��
             ��Чʱ�̣�������Ч
             
             bit3����Ӧw_snd_gm_int_3��W��������ָʾ������Ч��
             ���ڴ����ж�����3 ��int_type_gm_rcv_w[3]����GMDSP��GM��ģ�¶�W������ϵͳ����ʱ�����W����������W DSP���ô˱�־Ϊ1�� 
             ��Чʱ�̣�������Ч
 bit[2:0]    ����
   UNION�ṹ:  BBPCOMM_W_SND_GM_INT_13_UNION */
#define BBPCOMM_W_SND_GM_INT_13_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x728)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:3]   �߼������㡣����Ч��
             
             bit15~7����Ӧw_snd_gs_int_15 ~ 7��
             W DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_gs_rcv_w[15:7]����GSDSP��
             ��Чʱ�̣�������Ч
             
             bit6����Ӧw_snd_gs_int_6��
             WDSPͨ���˼Ĵ�����������6�жϣ�int_type_gs_rcv_w[6]����GSDSP��
             ��Чʱ�̣�������Ч
             
             bit5����Ӧw_snd_gs_int_5��
             W��ģʱ֪ͨGSDSP GS�������ڵ������Ч��
             W DSPͨ���˼Ĵ�����������5�жϣ�int_type_gs_rcv_w[5]����GSDSP��
             ��Чʱ�̣�������Ч
             
             bit4����Ӧw_snd_gs_int_4��
             W��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
             W DSPͨ���˼Ĵ�����������4�жϣ�int_type_gs_rcv_w[4]����GSDSP��
             ��Чʱ�̣�������Ч
             
             bit3����Ӧw_snd_gs_int_3��W��������ָʾ������Ч��
             ���ڴ����ж�����3 ��int_type_gs_rcv_w[3]����GSDSP��GS��ģ�¶�W������ϵͳ����ʱ�����W����������W DSP���ô˱�־Ϊ1�� 
             ��Чʱ�̣�������Ч
 bit[2:0]    ����
   UNION�ṹ:  BBPCOMM_W_SND_GS_INT_13_UNION */
#define BBPCOMM_W_SND_GS_INT_13_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x72C)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:3]   �߼������㡣����Ч��
             
             bit15~7����Ӧw_snd_w_int_15 ~ 7��
             W DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_w_rcv_w[15:7]����WDSP��
             ��Чʱ�̣�������Ч
             
             bit6����Ӧw_snd_w_int_6��
             WDSPͨ���˼Ĵ�����������6�жϣ�int_type_w_rcv_w[6]����WDSP��
             ��Чʱ�̣�������Ч
             
             bit5����Ӧw_snd_w_int_5��
             W��ģʱ֪ͨWDSP W�������ڵ������Ч��
             W DSPͨ���˼Ĵ�����������5�жϣ�int_type_w_rcv_w[5]����WDSP��
             ��Чʱ�̣�������Ч
             
             bit4����Ӧw_snd_w_int_4��
             W��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
             W DSPͨ���˼Ĵ�����������4�жϣ�int_type_w_rcv_w[4]����WDSP��
             ��Чʱ�̣�������Ч
             
             bit3����Ӧw_snd_w_int_3��W��������ָʾ������Ч��
             ���ڴ����ж�����3 ��int_type_w_rcv_w[3]����WDSP��W��ģ�¶�W������ϵͳ����ʱ�����W����������W DSP���ô˱�־Ϊ1�� 
             ��Чʱ�̣�������Ч
 bit[2:0]    ����
   UNION�ṹ:  BBPCOMM_W_SND_W_INT_13_UNION */
#define BBPCOMM_W_SND_W_INT_13_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x730)

/* �Ĵ���˵�����Ĵ���
 bit[31:4]   ����
 bit[3:0]    ��ϵͳ�������͡�
             4��b0������LTE��
             4��b1��������LTE��
             ����Ԥ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_LTE_INTERSYS_MEASURE_TYPE_UNION */
#define BBPCOMM_LTE_INTERSYS_MEASURE_TYPE_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x734)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      ��Ƶ��������ڵ�ָʾ��W/Gm/Gs����TDS��Ϊ��ģ��֪ͨL DSP �����ĵ�Ƶ�����ڵ��
             ֻ������̬����Ҫ���ã���Gm��Lʱ����Ҫ���ã�
             ��ƽ�źţ�����Ч��
             
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_LTE_MEASURE_REPORT_VALID_UNION */
#define BBPCOMM_LTE_MEASURE_REPORT_VALID_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x738)

/* �Ĵ���˵�����Ĵ���
   ��      ����Ԥ�����ж�int0��int1֮���offset��Ϣ����λus������ȡ������
               ����ʱ�̣�ÿ������LTE��ģ��ϵͳ����ʱ����
               ��Чʱ�̣�������Ч
   UNION�ṹ ���� */
#define BBPCOMM_LTE_PREINT_OFFSET_TIME_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x73C)

/* �Ĵ���˵�����Ĵ���
   ��      ����LTE��Ϊ��ģʱ����ģ��ģ�����LTE������ϵͳ����ʱ�䳤��,��֪LTE DSP����λus������ȡ��
               ����ʱ�̣�ÿ������LTE��ģ��ϵͳ����ʱ����
               ��Чʱ�̣�������Ч
   UNION�ṹ ���� */
#define BBPCOMM_LTE_INTERSYS_MEASURE_TIME_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x740)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_LTE_RCV_LTE[15:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_LTE_RCV_LTE_UNION */
#define BBPCOMM_INT_CLEAR_LTE_RCV_LTE_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x744)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_LTE_RCV_TDS[15:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_LTE_RCV_TDS_UNION */
#define BBPCOMM_INT_CLEAR_LTE_RCV_TDS_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x748)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_LTE_RCV_GM[15:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_LTE_RCV_GM_UNION */
#define BBPCOMM_INT_CLEAR_LTE_RCV_GM_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x74C)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_LTE_RCV_GS[15:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_LTE_RCV_GS_UNION */
#define BBPCOMM_INT_CLEAR_LTE_RCV_GS_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x750)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_LTE_RCV_W[15:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_LTE_RCV_W_UNION */
#define BBPCOMM_INT_CLEAR_LTE_RCV_W_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x754)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_LTE_INT012[2:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_LTE_INT012_UNION */
#define BBPCOMM_INT_CLEAR_LTE_INT012_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x758)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж����α�־����������INT_TYPE_LTE_RCV_LTE[15:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_LTE_RCV_LTE_UNION */
#define BBPCOMM_INT_MASK_LTE_RCV_LTE_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x75C)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж����α�־����������INT_TYPE_LTE_RCV_TDS[15:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_LTE_RCV_TDS_UNION */
#define BBPCOMM_INT_MASK_LTE_RCV_TDS_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x760)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж����α�־����������INT_TYPE_LTE_RCV_GM[15:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_LTE_RCV_GM_UNION */
#define BBPCOMM_INT_MASK_LTE_RCV_GM_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x764)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж����α�־����������INT_TYPE_LTE_RCV_GS[15:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_LTE_RCV_GS_UNION */
#define BBPCOMM_INT_MASK_LTE_RCV_GS_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x768)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж����α�־����������INT_TYPE_LTE_RCV_W[15:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_LTE_RCV_W_UNION */
#define BBPCOMM_INT_MASK_LTE_RCV_W_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x76C)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    �ж����α�־����������INT_TYPE_LTE_INT012[2:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_LTE_INT012_UNION */
#define BBPCOMM_INT_MASK_LTE_INT012_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x770)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
             [0]: �ж�����0�� W����ģ����ǰ֪ͨLTE��ϵͳ���������жϡ�
             [1]: �ж�����1�� W����ģ����GAP�жϣ�֪ͨLTE������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
             [2]: �ж�����2�� W����ģ����GAP�жϡ�
             [3]: �ж�����3��W����ģ�����������жϡ�
             [4]: �ж�����4��W����ģ��ǿ��LTE�˳���ϵͳ�����жϡ�
             [5]: �ж�����5��W����ģ��֪ͨLTE�ϱ����β��������
             [6]: ������
             [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x076C��int_mask_lte_rcv_w���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_LTE_RCV_W_UNION */
#define BBPCOMM_INT_TYPE_LTE_RCV_W_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x774)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж�״̬��־0��1��2ֻ�е�TDS������ģʱ���ܲ�����
             [0]: �ж�����0�� TDS����ģ����ǰ֪ͨLTE��ϵͳ���������жϡ�
             [1]: �ж�����1�� TDS����ģ����GAP�жϣ�֪ͨLTE������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
             [2]: �ж�����2�� TDS����ģ����GAP�жϡ�
             [3]: �ж�����3��TDS����ģ�����������жϡ�
             [4]: �ж�����4��TDS����ģ��ǿ��LTE�˳���ϵͳ�����жϡ�
             [5]: �ж�����5��TDS����ģ��֪ͨLTE�ϱ����β��������
             [6]: �ж�����6��������
             [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x0760��int_mask_lte_rcv_tds���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_LTE_RCV_TDS_UNION */
#define BBPCOMM_INT_TYPE_LTE_RCV_TDS_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x778)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
             [0]: �ж�����0��GM����ģ����ǰ֪ͨLTE��ϵͳ���������жϡ�
             [1]: �ж�����1��GM����ģ����GAP�жϣ�֪ͨLTE������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
             [2]: �ж�����2��GM����ģ����GAP�жϡ�
             [3]: �ж�����3��GM����ģ�����������жϡ�
             [4]: �ж�����4��GM����ģ��ǿ��LTE�˳���ϵͳ�����жϡ�
             [5]: �ж�����5��GM����ģ��֪ͨLTE�ϱ����β��������
             [6]: �ж�����6��������
             [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
             �ж�״̬��־0��1��2ֻ�е�GM������ģʱ���ܲ�����
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x0764��int_mask_lte_rcv_gm���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_LTE_RCV_GM_UNION */
#define BBPCOMM_INT_TYPE_LTE_RCV_GM_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x77C)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   [0]: �ж�����0��GS����ģ����ǰ֪ͨLTE��ϵͳ���������жϡ�
             [1]: �ж�����1��GS����ģ����GAP�жϣ�֪ͨLTE������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
             [2]: �ж�����2��GS����ģ����GAP�жϡ�
             [3]: �ж�����3��GS����ģ�����������жϡ�
             [4]: �ж�����4��GS����ģ��ǿ��LTE�˳���ϵͳ�����жϡ�
             [5]: �ж�����5��GS����ģ��֪ͨLTE�ϱ����β��������
             [6]: �ж�����6��������
             [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
             �ж�״̬��־0��1��2ֻ�е�TDS������ģʱ���ܲ�����
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x0768��int_mask_lte_rcv_gs���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_LTE_RCV_GS_UNION */
#define BBPCOMM_INT_TYPE_LTE_RCV_GS_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x780)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
             [0]: �ж�����0��LTE����ģ����ǰ֪ͨLTE��Ƶ���������жϡ�
             [1]: �ж�����1��LTE����ģ����GAP�жϣ�֪ͨLTE������Ƶ������Ƶͨ�����ã������л��Ȳ�����
             [2]: �ж�����2��LTE����ģ����GAP�жϡ�
             [3]: �ж�����3��LTE����ģ������Ƶ�����������жϡ�
             [4]: �ж�����4��LTE����ģ��ǿ��LTE�˳���Ƶ�����жϡ�
             [5]: �ж�����5��LTE����ģ��֪ͨLTE�ϱ����β��������
             [6]: �ж�����6��������
             [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
             �ж�״̬��־0��1��2ֻ�е�LTE������ģʱ���ܲ�����
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x075C��int_mask_lte_rcv_lte���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_LTE_RCV_LTE_UNION */
#define BBPCOMM_INT_TYPE_LTE_RCV_LTE_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x784)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    ������ģ����int0��1��2���ϱ���(������Ƶ����ϵͳ����)��������Ч��
             [0]: L��ģʱ��CTU����֪ͨLDSP����int0�жϡ�
             [1]: L��ģʱ��CTU����֪ͨLDSP����int1�жϡ�
             [2]: L��ģʱ��CTU����֪ͨLDSP����int2�жϡ�
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x0770��int_mask_lte_int012���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_LTE_INT012_UNION */
#define BBPCOMM_INT_TYPE_LTE_INT012_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x788)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:3]   �߼������㡣����Ч��
             
             bit15~7����Ӧlte_snd_lte_int_15 ~ 7��
             L DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_lte_rcv_lte[15:7]����LDSP��
             ��Чʱ�̣�������Ч
             
             bit6����Ӧlte_snd_lte_int_6��
             LDSPͨ���˼Ĵ�����������6�жϣ�int_type_lte_rcv_lte[6]����LDSP��
             ��Чʱ�̣�������Ч
             
             bit5����Ӧlte_snd_lte_int_5��
             L��ģʱ֪ͨLDSP L�������ڵ������Ч��
             L DSPͨ���˼Ĵ�����������5�жϣ�int_type_lte_rcv_lte[5]����LDSP��
             ��Чʱ�̣�������Ч
             
             bit4����Ӧlte_snd_lte_int_4��
             L��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
             L DSPͨ���˼Ĵ�����������4�жϣ�int_type_lte_rcv_lte[4]����LDSP��
             ��Чʱ�̣�������Ч
             
             bit3����Ӧlte_snd_lte_int_3��L��������ָʾ������Ч��
             ���ڴ����ж�����3 ��int_type_lte_rcv_lte[3]����LDSP��L��ģ�¶�L������ϵͳ����ʱ�����L����������L DSP���ô˱�־Ϊ1�� 
             ��Чʱ�̣�������Ч
 bit[2:0]    ����
   UNION�ṹ:  BBPCOMM_LTE_SND_LTE_INT_13_UNION */
#define BBPCOMM_LTE_SND_LTE_INT_13_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x78C)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:3]   �߼������㡣����Ч��
             
             bit15~7����Ӧlte_snd_tds_int_15 ~ 7��
             L DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_tds_rcv_lte[15:7]����TDSDSP��
             ��Чʱ�̣�������Ч
             
             bit6����Ӧlte_snd_tds_int_6��
             LDSPͨ���˼Ĵ�����������6�жϣ�int_type_tds_rcv_lte[6]����TDSDSP��
             ��Чʱ�̣�������Ч
             
             bit5����Ӧlte_snd_tds_int_5��
             L��ģʱ֪ͨTDSDSP TDS�������ڵ������Ч��
             L DSPͨ���˼Ĵ�����������5�жϣ�int_type_tds_rcv_lte[5]����TDSDSP��
             ��Чʱ�̣�������Ч
             
             bit4����Ӧlte_snd_tds_int_4��
             L��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
             L DSPͨ���˼Ĵ�����������4�жϣ�int_type_tds_rcv_lte[4]����TDSDSP��
             ��Чʱ�̣�������Ч
             
             bit3����Ӧlte_snd_tds_int_3��L��������ָʾ������Ч��
             ���ڴ����ж�����3 ��int_type_tds_rcv_lte[3]����TDSDSP��TDS��ģ�¶�L������ϵͳ����ʱ�����L����������L DSP���ô˱�־Ϊ1�� 
             ��Чʱ�̣�������Ч
 bit[2:0]    ����
   UNION�ṹ:  BBPCOMM_LTE_SND_TDS_INT_13_UNION */
#define BBPCOMM_LTE_SND_TDS_INT_13_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x790)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:3]   �߼������㡣����Ч��
             
             bit15~7����Ӧlte_snd_gm_int_15 ~ 7��
             L DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_gm_rcv_lte[15:7]����GMDSP��
             ��Чʱ�̣�������Ч
             
             bit6����Ӧlte_snd_gm_int_6��
             LDSPͨ���˼Ĵ�����������6�жϣ�iint_type_gm_rcv_lte[6]����GMDSP��
             ��Чʱ�̣�������Ч
             
             bit5����Ӧlte_snd_gm_int_5��
             L��ģʱ֪ͨGMDSP GM�������ڵ������Ч��
             L DSPͨ���˼Ĵ�����������5�жϣ�int_type_gm_rcv_lte[5]����GMDSP��
             ��Чʱ�̣�������Ч
             
             bit4����Ӧlte_snd_gm_int_4��
             L��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
             L DSPͨ���˼Ĵ�����������4�жϣ�int_type_gm_rcv_lte[4]����GMDSP��
             ��Чʱ�̣�������Ч
             
             bit3����Ӧlte_snd_gm_int_3��L��������ָʾ������Ч��
             ���ڴ����ж�����3 ��int_type_gm_rcv_lte[3]����GMDSP��GM��ģ�¶�L������ϵͳ����ʱ�����L����������L DSP���ô˱�־Ϊ1�� 
             ��Чʱ�̣�������Ч
 bit[2:0]    ����
   UNION�ṹ:  BBPCOMM_LTE_SND_GM_INT_13_UNION */
#define BBPCOMM_LTE_SND_GM_INT_13_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x794)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:3]   �߼������㡣����Ч��
             
             bit15~7����Ӧlte_snd_gs_int_15 ~ 7��
             L DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_gs_rcv_lte[15:7]����GSDSP��
             ��Чʱ�̣�������Ч
             
             bit6����Ӧlte_snd_gs_int_6��
             LDSPͨ���˼Ĵ�����������6�жϣ�int_type_gs_rcv_lte[6]����GSDSP��
             ��Чʱ�̣�������Ч
             
             bit5����Ӧlte_snd_gs_int_5��
             L��ģʱ֪ͨGSDSP GS�������ڵ������Ч��
             L DSPͨ���˼Ĵ�����������5�жϣ�int_type_gs_rcv_lte[5]����GSDSP��
             ��Чʱ�̣�������Ч
             
             bit4����Ӧlte_snd_gs_int_4��
             L��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
             L DSPͨ���˼Ĵ�����������4�жϣ�int_type_gs_rcv_lte[4]����GSDSP��
             ��Чʱ�̣�������Ч
             
             bit3����Ӧlte_snd_gs_int_3��L��������ָʾ������Ч��
             ���ڴ����ж�����3 ��int_type_gs_rcv_lte[3]����GSDSP��GS��ģ�¶�L������ϵͳ����ʱ�����L����������L DSP���ô˱�־Ϊ1�� 
             ��Чʱ�̣�������Ч
 bit[2:0]    ����
   UNION�ṹ:  BBPCOMM_LTE_SND_GS_INT_13_UNION */
#define BBPCOMM_LTE_SND_GS_INT_13_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x798)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:3]   �߼������㡣����Ч��
             
             bit15~7����Ӧlte_snd_w_int_15 ~ 7��
             L DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_w_rcv_lte[15:7]����WDSP��
             ��Чʱ�̣�������Ч
             
             bit6����Ӧlte_snd_w_int_6��
             LDSPͨ���˼Ĵ�����������6�жϣ�int_type_w_rcv_lte[6]����WDSP��
             ��Чʱ�̣�������Ч
             
             bit5����Ӧlte_snd_w_int_5��
             L��ģʱ֪ͨWDSP W�������ڵ������Ч��
             L DSPͨ���˼Ĵ�����������5�жϣ�int_type_w_rcv_lte[5]����WDSP��
             ��Чʱ�̣�������Ч
             
             bit4����Ӧlte_snd_w_int_4��
             L��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
             L DSPͨ���˼Ĵ�����������4�жϣ�int_type_w_rcv_lte[4]����WDSP��
             ��Чʱ�̣�������Ч
             
             bit3����Ӧlte_snd_w_int_3��L��������ָʾ������Ч��
             ���ڴ����ж�����3 ��int_type_w_rcv_lte[3]����WDSP��W��ģ�¶�L������ϵͳ����ʱ�����L����������L DSP���ô˱�־Ϊ1�� 
             ��Чʱ�̣�������Ч
 bit[2:0]    ����
   UNION�ṹ:  BBPCOMM_LTE_SND_W_INT_13_UNION */
#define BBPCOMM_LTE_SND_W_INT_13_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x79C)

/* �Ĵ���˵�����Ĵ���
 bit[31:4]   ����
 bit[3:0]    ��ϵͳ�������� ��
             4��b0�� ����TDS
             4��b1�� ������TDS
             ����Ԥ��
             
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_TDS_INTERSYS_MEASURE_TYPE_UNION */
#define BBPCOMM_TDS_INTERSYS_MEASURE_TYPE_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x7A0)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      ��Ƶ��������ڵ�ָʾ��U/Gm/Gs����L��Ϊ��ģ��֪ͨT DSP W�����ĵ�Ƶ�����ڵ��
             ֻ������̬����Ҫ���ã���G��TDSʱ����Ҫ���ã�
             ��ƽ�źţ�����Ч��
             
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_TDS_MEASURE_REPORT_VALID_UNION */
#define BBPCOMM_TDS_MEASURE_REPORT_VALID_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x7A4)

/* �Ĵ���˵�����Ĵ���
   ��      ����Ԥ�����ж�int0��int1֮���offset��Ϣ����λus������ȡ������
               ����ʱ�̣���ģ����TDS��ģ��ϵͳ����ʱ����
               ��Чʱ�̣�������Ч
   UNION�ṹ ���� */
#define BBPCOMM_TDS_PREINT_OFFSET_TIME_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x7A8)

/* �Ĵ���˵�����Ĵ���
   ��      ��������ʱ�䳤�ȣ���֪TDS DSP����λus������ȡ����us��
               ����ʱ�̣���ģ����TDS��ģ��ϵͳ����ʱ����
               ��Чʱ�̣�������Ч
   UNION�ṹ ���� */
#define BBPCOMM_TDS_INTERSYS_MEASURE_TIME_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x7AC)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_TDS_RCV_LTE[15:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_TDS_RCV_LTE_UNION */
#define BBPCOMM_INT_CLEAR_TDS_RCV_LTE_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x7B0)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_TDS_RCV_TDS[15:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_TDS_RCV_TDS_UNION */
#define BBPCOMM_INT_CLEAR_TDS_RCV_TDS_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x7B4)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_TDS_RCV_GM[15:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_TDS_RCV_GM_UNION */
#define BBPCOMM_INT_CLEAR_TDS_RCV_GM_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x7B8)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_TDS_RCV_GS[15:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_TDS_RCV_GS_UNION */
#define BBPCOMM_INT_CLEAR_TDS_RCV_GS_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x7BC)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_TDS_RCV_W[15:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_TDS_RCV_W_UNION */
#define BBPCOMM_INT_CLEAR_TDS_RCV_W_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x7C0)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_TDS_INT012[2:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_TDS_INT012_UNION */
#define BBPCOMM_INT_CLEAR_TDS_INT012_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x7C4)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж����α�־����������INT_TYPE_TDS_RCV_LTE[15:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_TDS_RCV_LTE_UNION */
#define BBPCOMM_INT_MASK_TDS_RCV_LTE_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x7C8)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж����α�־����������INT_TYPE_TDS_RCV_TDS[15:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_TDS_RCV_TDS_UNION */
#define BBPCOMM_INT_MASK_TDS_RCV_TDS_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x7CC)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж����α�־����������INT_TYPE_TDS_RCV_GM[15:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_TDS_RCV_GM_UNION */
#define BBPCOMM_INT_MASK_TDS_RCV_GM_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x7D0)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж����α�־����������INT_TYPE_TDS_RCV_GS[15:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_TDS_RCV_GS_UNION */
#define BBPCOMM_INT_MASK_TDS_RCV_GS_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x7D4)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж����α�־����������INT_TYPE_TDS_RCV_W[15:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_TDS_RCV_W_UNION */
#define BBPCOMM_INT_MASK_TDS_RCV_W_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x7D8)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    �ж����α�־����������INT_TYPE_TDS_INT012[2:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_TDS_INT012_UNION */
#define BBPCOMM_INT_MASK_TDS_INT012_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x7DC)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
             [0]: �ж�����0�� LTE����ģ����ǰ֪ͨTDS��ϵͳ���������жϡ�
             [1]: �ж�����1�� LTE����ģ����GAP�жϣ�֪ͨTDS������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
             [2]: �ж�����2�� LTE����ģ����GAP�жϡ�
             [3]: �ж�����3��LTE����ģ�����������жϡ�
             [4]: �ж�����4��LTE����ģ��ǿ��TDS�˳���ϵͳ�����жϡ�
             [5]: �ж�����5��LTE����ģ��֪ͨTDS�ϱ����β��������
             [6]: ������
             [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x07C8��int_mask_tds_rcv_lte���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_TDS_RCV_LTE_UNION */
#define BBPCOMM_INT_TYPE_TDS_RCV_LTE_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x7E0)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж�״̬��־0��1��2ֻ�е�TDS������ģʱ���ܲ�����
             
             [0]: �ж�����0�� TDS����ģ����ǰ֪ͨTDS��ϵͳ���������жϡ�
             [1]: �ж�����1�� TDS����ģ����GAP�жϣ�֪ͨTDS������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
             [2]: �ж�����2�� TDS����ģ����GAP�жϡ�
             [3]: �ж�����3��TDS����ģ�����������жϡ�
             [4]: �ж�����4��TDS����ģ��ǿ��TDS�˳���ϵͳ�����жϡ�
             [5]: �ж�����5��TDS����ģ��֪ͨTDS�ϱ����β��������
             [6]: �ж�����6��������
             [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x07D8��int_mask_tds_rcv_w���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_TDS_RCV_W_UNION */
#define BBPCOMM_INT_TYPE_TDS_RCV_W_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x7E4)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
             [0]: �ж�����0��GM����ģ����ǰ֪ͨTDS��ϵͳ���������жϡ�
             [1]: �ж�����1��GM����ģ����GAP�жϣ�֪ͨTDS������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
             [2]: �ж�����2��GM����ģ����GAP�жϡ�
             [3]: �ж�����3��GM����ģ�����������жϡ�
             [4]: �ж�����4��GM����ģ��ǿ��TDS�˳���ϵͳ�����жϡ�
             [5]: �ж�����5��GM����ģ��֪ͨTDS�ϱ����β��������
             [6]: �ж�����6��������
             [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
             �ж�״̬��־0��1��2ֻ�е�GM������ģʱ���ܲ�����
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x07D0��int_mask_tds_rcv_gm���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_TDS_RCV_GM_UNION */
#define BBPCOMM_INT_TYPE_TDS_RCV_GM_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x7E8)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   [0]: �ж�����0��GS����ģ����ǰ֪ͨTDS��ϵͳ���������жϡ�
             [1]: �ж�����1��GS����ģ����GAP�жϣ�֪ͨTDS������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
             [2]: �ж�����2��GS����ģ����GAP�жϡ�
             [3]: �ж�����3��GS����ģ�����������жϡ�
             [4]: �ж�����4��GS����ģ��ǿ��TDS�˳���ϵͳ�����жϡ�
             [5]: �ж�����5��GS����ģ��֪ͨTDS�ϱ����β��������
             [6]: �ж�����6��������
             [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
             �ж�״̬��־0��1��2ֻ�е�TDS������ģʱ���ܲ�����
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x07D4��int_mask_tds_rcv_gs���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_TDS_RCV_GS_UNION */
#define BBPCOMM_INT_TYPE_TDS_RCV_GS_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x7EC)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
             [0]: �ж�����0��TDS����ģ����ǰ֪ͨTDS��Ƶ���������жϡ�
             [1]: �ж�����1��TDS����ģ����GAP�жϣ�֪ͨTDS������Ƶ������Ƶͨ�����ã������л��Ȳ�����
             [2]: �ж�����2��TDS����ģ����GAP�жϡ�
             [3]: �ж�����3��TDS����ģ������Ƶ�����������жϡ�
             [4]: �ж�����4��TDS����ģ��ǿ��TDS�˳���Ƶ�����жϡ�
             [5]: �ж�����5��TDS����ģ��֪ͨTDS�ϱ����β��������
             [6]: �ж�����6��������
             [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
             �ж�״̬��־0��1��2ֻ�е�TDS������ģʱ���ܲ�����
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x07CC��int_mask_tds_rcv_tds���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_TDS_RCV_TDS_UNION */
#define BBPCOMM_INT_TYPE_TDS_RCV_TDS_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x7F0)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    ������ģ����int0��1��2���ϱ���(������Ƶ����ϵͳ����)��������Ч��
             [0]: T��ģʱ��CTU����֪ͨTDSP����int0�жϡ�
             [1]: T��ģʱ��CTU����֪ͨTDSP����int1�жϡ�
             [2]: T��ģʱ��CTU����֪ͨTDSP����int2�жϡ�
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x07DC��int_mask_tds_int012���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_TDS_INT012_UNION */
#define BBPCOMM_INT_TYPE_TDS_INT012_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x7F4)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:3]   �߼������㡣����Ч��
             
             bit15~7����Ӧtds_snd_lte_int_15 ~ 7��
             TDS DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_lte_rcv_tds[15:7]����LDSP��
             ��Чʱ�̣�������Ч
             
             bit6����Ӧtds_snd_lte_int_6��
             TDSDSPͨ���˼Ĵ�����������6�жϣ�int_type_lte_rcv_tds[6]����LDSP��
             ��Чʱ�̣�������Ч
             
             bit5����Ӧtds_snd_lte_int_5��
             TDS��ģʱ֪ͨLDSP L�������ڵ������Ч��
             TDS DSPͨ���˼Ĵ�����������5�жϣ�int_type_lte_rcv_tds[5]����LDSP��
             ��Чʱ�̣�������Ч
             
             bit4����Ӧtds_snd_lte_int_4��
             TDS��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
             TDS DSPͨ���˼Ĵ�����������4�жϣ�int_type_lte_rcv_tds[4]����LDSP��
             ��Чʱ�̣�������Ч
             
             bit3����Ӧtds_snd_lte_int_3��TDS��������ָʾ������Ч��
             ���ڴ����ж�����3 ��int_type_lte_rcv_tds[3]����LDSP��L��ģ�¶�TDS������ϵͳ����ʱ�����TDS����������TDS DSP���ô˱�־Ϊ1�� 
             ��Чʱ�̣�������Ч
 bit[2:0]    ����
   UNION�ṹ:  BBPCOMM_TDS_SND_LTE_INT_13_UNION */
#define BBPCOMM_TDS_SND_LTE_INT_13_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x7F8)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:3]   �߼������㡣����Ч��
             
             bit15~7����Ӧtds_snd_tds_int_15 ~ 7��
             TDS DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_tds_rcv_tds[15:7]����TDSP��
             ��Чʱ�̣�������Ч
             
             bit6����Ӧtds_snd_tds_int_6��
             TDSDSPͨ���˼Ĵ�����������6�жϣ�int_type_tds_rcv_tds[6]����TDSP��
             ��Чʱ�̣�������Ч
             
             bit5����Ӧtds_snd_tds_int_5��
             TDS��ģʱ֪ͨTDSP T�������ڵ������Ч��
             TDS DSPͨ���˼Ĵ�����������5�жϣ�int_type_tds_rcv_tds[5]����TDSP��
             ��Чʱ�̣�������Ч
             
             bit4����Ӧtds_snd_tds_int_4��
             TDS��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
             TDS DSPͨ���˼Ĵ�����������4�жϣ�int_type_tds_rcv_tds[4]����TDSP��
             ��Чʱ�̣�������Ч
             
             bit3����Ӧtds_snd_tds_int_3��TDS��������ָʾ������Ч��
             ���ڴ����ж�����3 ��int_type_tds_rcv_tds[3]����TDSP��T��ģ�¶�TDS������ϵͳ����ʱ�����TDS����������TDS DSP���ô˱�־Ϊ1�� 
             ��Чʱ�̣�������Ч
 bit[2:0]    ����
   UNION�ṹ:  BBPCOMM_TDS_SND_TDS_INT_13_UNION */
#define BBPCOMM_TDS_SND_TDS_INT_13_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x7FC)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:3]   �߼������㡣����Ч��
             
             bit15~7����Ӧtds_snd_gm_int_15 ~ 7��
             TDS DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_gm_rcv_tds[15:7]����GMDSP��
             ��Чʱ�̣�������Ч
             
             bit6����Ӧtds_snd_gm_int_6��
             TDSDSPͨ���˼Ĵ�����������6�жϣ�int_type_gm_rcv_tds[6]����GMDSP��
             ��Чʱ�̣�������Ч
             
             bit5����Ӧtds_snd_gm_int_5��
             TDS��ģʱ֪ͨGMDSP GM�������ڵ������Ч��
             TDS DSPͨ���˼Ĵ�����������5�жϣ�int_type_gm_rcv_tds[5]����GMDSP��
             ��Чʱ�̣�������Ч
             
             bit4����Ӧtds_snd_gm_int_4��
             TDS��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
             TDS DSPͨ���˼Ĵ�����������4�жϣ�int_type_gm_rcv_tds[4]����GMDSP��
             ��Чʱ�̣�������Ч
             
             bit3����Ӧtds_snd_gm_int_3��TDS��������ָʾ������Ч��
             ���ڴ����ж�����3 ��int_type_gm_rcv_tds[3]����GMDSP��GM��ģ�¶�TDS������ϵͳ����ʱ�����TDS����������TDS DSP���ô˱�־Ϊ1�� 
             ��Чʱ�̣�������Ч
 bit[2:0]    ����
   UNION�ṹ:  BBPCOMM_TDS_SND_GM_INT_13_UNION */
#define BBPCOMM_TDS_SND_GM_INT_13_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x800)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:3]   �߼������㡣����Ч��
             
             bit15~7����Ӧtds_snd_gs_int_15 ~ 7��
             TDS DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_gs_rcv_tds[15:7]����GSDSP��
             ��Чʱ�̣�������Ч
             
             bit6����Ӧtds_snd_gs_int_6��
             TDSDSPͨ���˼Ĵ�����������6�жϣ�int_type_gs_rcv_tds[6]����GSDSP��
             ��Чʱ�̣�������Ч
             
             bit5����Ӧtds_snd_gs_int_5��
             TDS��ģʱ֪ͨGSDSP GS�������ڵ������Ч��
             TDS DSPͨ���˼Ĵ�����������5�жϣ�int_type_gs_rcv_tds[5]����GSDSP��
             ��Чʱ�̣�������Ч
             
             bit4����Ӧtds_snd_gs_int_4��
             TDS��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
             TDS DSPͨ���˼Ĵ�����������4�жϣ�int_type_gs_rcv_tds[4]����GSDSP��
             ��Чʱ�̣�������Ч
             
             bit3����Ӧtds_snd_gs_int_3��TDS��������ָʾ������Ч��
             ���ڴ����ж�����3 ��int_type_gs_rcv_tds[3]����GSDSP��GS��ģ�¶�TDS������ϵͳ����ʱ�����TDS����������TDS DSP���ô˱�־Ϊ1�� 
             ��Чʱ�̣�������Ч
 bit[2:0]    ����
   UNION�ṹ:  BBPCOMM_TDS_SND_GS_INT_13_UNION */
#define BBPCOMM_TDS_SND_GS_INT_13_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x804)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:3]   �߼������㡣����Ч��
             
             bit15~7����Ӧtds_snd_w_int_15 ~ 7��
             TDS DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_w_rcv_tds[15:7]����WDSP��
             ��Чʱ�̣�������Ч
             
             bit6����Ӧtds_snd_w_int_6��
             TDSDSPͨ���˼Ĵ�����������6�жϣ�int_type_w_rcv_tds[6]����WDSP��
             ��Чʱ�̣�������Ч
             
             bit5����Ӧtds_snd_w_int_5��
             TDS��ģʱ֪ͨWDSP W�������ڵ������Ч��
             TDS DSPͨ���˼Ĵ�����������5�жϣ�int_type_w_rcv_tds[5]����WDSP��
             ��Чʱ�̣�������Ч
             
             bit4����Ӧtds_snd_w_int_4��
             TDS��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
             TDS DSPͨ���˼Ĵ�����������4�жϣ�int_type_w_rcv_tds[4]����WDSP��
             ��Чʱ�̣�������Ч
             
             bit3����Ӧtds_snd_w_int_3��TDS��������ָʾ������Ч��
             ���ڴ����ж�����3 ��int_type_w_rcv_tds[3]����WDSP��W��ģ�¶�TDS������ϵͳ����ʱ�����TDS����������TDS DSP���ô˱�־Ϊ1�� 
             ��Чʱ�̣�������Ч
 bit[2:0]    ����
   UNION�ṹ:  BBPCOMM_TDS_SND_W_INT_13_UNION */
#define BBPCOMM_TDS_SND_W_INT_13_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x808)

/* �Ĵ���˵�����Ĵ���
 bit[31:4]   ����
 bit[3:0]    ��ϵͳ�������͡�
             4��d0������GM RSSI��
             4��d1: ����GM bsic verification��
             4��d2: ����GM bsic confirm��
             4��d3: ������GM��
             4��d4: 2G ANR��
             ����Ԥ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_GM_INTERSYS_MEASURE_TYPE_UNION */
#define BBPCOMM_GM_INTERSYS_MEASURE_TYPE_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x80C)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      ��Ƶ��������ڵ�ָʾ��L����TDS/W/Gs��Ϊ��ģ��֪ͨGM DSP GM�����ĵ�Ƶ�����ڵ��
             ֻ������̬����Ҫ���á�
             ��ƽ�źţ�����Ч��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_GM_MEASURE_REPORT_VALID_UNION */
#define BBPCOMM_GM_MEASURE_REPORT_VALID_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x810)

/* �Ĵ���˵�����Ĵ���
   ��      ����Ԥ�����ж�int0��int1֮���offset��Ϣ����λus������ȡ��������
               ����ʱ�̣���ģ����GM��ģ��ϵͳ����ʱ����
               ��Чʱ�̣�������Ч
   UNION�ṹ ���� */
#define BBPCOMM_GM_PREINT_OFFSET_TIME_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x814)

/* �Ĵ���˵�����Ĵ���
   ��      ����GM��Ϊ��ģʱ����ģ�����GM������ϵͳ����ʱ�䳤�ȣ���֪GMDSP����λus������ȡ����us��
               ����ʱ�̣���ģ����GM��ģ��ϵͳ����ʱ����
               ��Чʱ�̣�������Ч
   UNION�ṹ ���� */
#define BBPCOMM_GM_INTERSYS_MEASURE_TIME_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x818)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_GM_RCV_LTE[15:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_GM_RCV_LTE_UNION */
#define BBPCOMM_INT_CLEAR_GM_RCV_LTE_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x81C)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_GM_RCV_TDS[15:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_GM_RCV_TDS_UNION */
#define BBPCOMM_INT_CLEAR_GM_RCV_TDS_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x820)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_GM_RCV_GM[15:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_GM_RCV_GM_UNION */
#define BBPCOMM_INT_CLEAR_GM_RCV_GM_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x824)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_GM_RCV_GS[15:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_GM_RCV_GS_UNION */
#define BBPCOMM_INT_CLEAR_GM_RCV_GS_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x828)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_GM_RCV_W[15:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_GM_RCV_W_UNION */
#define BBPCOMM_INT_CLEAR_GM_RCV_W_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x82C)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_GM_INT012[2:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_GM_INT012_UNION */
#define BBPCOMM_INT_CLEAR_GM_INT012_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x830)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж����α�־����������INT_TYPE_GM_RCV_LTE[15:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_GM_RCV_LTE_UNION */
#define BBPCOMM_INT_MASK_GM_RCV_LTE_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x834)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж����α�־����������INT_TYPE_GM_RCV_TDS[15:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_GM_RCV_TDS_UNION */
#define BBPCOMM_INT_MASK_GM_RCV_TDS_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x838)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж����α�־����������INT_TYPE_GM_RCV_GM[15:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_GM_RCV_GM_UNION */
#define BBPCOMM_INT_MASK_GM_RCV_GM_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x83C)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж����α�־����������INT_TYPE_GM_RCV_GS[15:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_GM_RCV_GS_UNION */
#define BBPCOMM_INT_MASK_GM_RCV_GS_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x840)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж����α�־����������INT_TYPE_GM_RCV_W[15:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_GM_RCV_W_UNION */
#define BBPCOMM_INT_MASK_GM_RCV_W_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x844)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    �ж����α�־����������INT_TYPE_GM_INT012[2:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_GM_INT012_UNION */
#define BBPCOMM_INT_MASK_GM_INT012_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x848)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
             [0]: �ж�����0�� LTE����ģ����ǰ֪ͨGM��ϵͳ���������жϡ�
             [1]: �ж�����1�� LTE����ģ����GAP�жϣ�֪ͨGM������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
             [2]: �ж�����2�� LTE����ģ����GAP�жϡ�
             [3]: �ж�����3��LTE����ģ�����������жϡ�
             [4]: �ж�����4��LTE����ģ��ǿ��GM�˳���ϵͳ�����жϡ�
             [5]: �ж�����5��LTE����ģ��֪ͨGM�ϱ����β��������
             [6]: ������
             [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x0834��int_mask_gm_rcv_lte���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_GM_RCV_LTE_UNION */
#define BBPCOMM_INT_TYPE_GM_RCV_LTE_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x84C)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж�״̬��־0��1��2ֻ�е�TDS������ģʱ���ܲ�����
             
             [0]: �ж�����0�� TDS����ģ����ǰ֪ͨGM��ϵͳ���������жϡ�
             [1]: �ж�����1�� TDS����ģ����GAP�жϣ�֪ͨGM������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
             [2]: �ж�����2�� TDS����ģ����GAP�жϡ�
             [3]: �ж�����3��TDS����ģ�����������жϡ�
             [4]: �ж�����4��TDS����ģ��ǿ��GM�˳���ϵͳ�����жϡ�
             [5]: �ж�����5��TDS����ģ��֪ͨGM�ϱ����β��������
             [6]: �ж�����6��������
             [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x0838��int_mask_gm_rcv_tds���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_GM_RCV_TDS_UNION */
#define BBPCOMM_INT_TYPE_GM_RCV_TDS_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x850)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
             [0]: �ж�����0��W����ģ����ǰ֪ͨGM��ϵͳ���������жϡ�
             [1]: �ж�����1��W����ģ����GAP�жϣ�֪ͨGM������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
             [2]: �ж�����2��W����ģ����GAP�жϡ�
             [3]: �ж�����3��W����ģ�����������жϡ�
             [4]: �ж�����4��W����ģ��ǿ��GM�˳���ϵͳ�����жϡ�
             [5]: �ж�����5��W����ģ��֪ͨGM�ϱ����β��������
             [6]: �ж�����6��������
             [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
             �ж�״̬��־0��1��2ֻ�е�W������ģʱ���ܲ�����
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x0844��int_mask_gm_rcv_w���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_GM_RCV_W_UNION */
#define BBPCOMM_INT_TYPE_GM_RCV_W_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x854)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   [0]: �ж�����0��GS����ģ����ǰ֪ͨGM��ϵͳ���������жϡ�
             [1]: �ж�����1��GS����ģ����GAP�жϣ�֪ͨGM������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
             [2]: �ж�����2��GS����ģ����GAP�жϡ�
             [3]: �ж�����3��GS����ģ�����������жϡ�
             [4]: �ж�����4��GS����ģ��ǿ��GM�˳���ϵͳ�����жϡ�
             [5]: �ж�����5��GS����ģ��֪ͨGM�ϱ����β��������
             [6]: �ж�����6��������
             [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
             �ж�״̬��־0��1��2ֻ�е�TDS������ģʱ���ܲ�����
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x0840��int_mask_gm_rcv_gs���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_GM_RCV_GS_UNION */
#define BBPCOMM_INT_TYPE_GM_RCV_GS_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x858)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
             [0]: �ж�����0��GM����ģ����ǰ֪ͨGM��Ƶ���������жϡ�
             [1]: �ж�����1��GM����ģ����GAP�жϣ�֪ͨGM������Ƶ������Ƶͨ�����ã������л��Ȳ�����
             [2]: �ж�����2��GM����ģ����GAP�жϡ�
             [3]: �ж�����3��GM����ģ������Ƶ�����������жϡ�
             [4]: �ж�����4��GM����ģ��ǿ��GM�˳���Ƶ�����жϡ�
             [5]: �ж�����5��GM����ģ��֪ͨGM�ϱ����β��������
             [6]: �ж�����6��������
             [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
             �ж�״̬��־0��1��2ֻ�е�GM������ģʱ���ܲ�����
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x083C��int_mask_gm_rcv_gm���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_GM_RCV_GM_UNION */
#define BBPCOMM_INT_TYPE_GM_RCV_GM_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x85C)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    ������ģ����int0��1��2���ϱ���(������Ƶ����ϵͳ����)��������Ч��
             [0]: GM��ģʱ��CTU����֪ͨGMDSP����int0�жϡ�
             [1]: GM��ģʱ��CTU����֪ͨGMDSP����int1�жϡ�
             [2]: GM��ģʱ��CTU����֪ͨGMDSP����int2�жϡ�
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x0848��int_mask_gm_int012���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_GM_INT012_UNION */
#define BBPCOMM_INT_TYPE_GM_INT012_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x860)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:3]   �߼������㡣����Ч��
             
             bit15~7����Ӧgm_snd_lte_int_15 ~ 7��
             GM DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_lte_rcv_gm[15:7]����LTEDSP��
             ��Чʱ�̣�������Ч
             
             bit6����Ӧgm_snd_lte_int_6��
             GMDSPͨ���˼Ĵ�����������6�жϣ�int_type_lte_rcv_gm[6]����LTEDSP��
             ��Чʱ�̣�������Ч
             
             bit5����Ӧgm_snd_lte_int_5��
             GM��ģʱ֪ͨLTEDSP LTE�������ڵ������Ч��
             GM DSPͨ���˼Ĵ�����������5�жϣ�int_type_lte_rcv_gm[5]����LTEDSP��
             ��Чʱ�̣�������Ч
             
             bit4����Ӧgm_snd_lte_int_4��
             GM��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
             GM DSPͨ���˼Ĵ�����������4�жϣ�int_type_lte_rcv_gm[4]����LTEDSP��
             ��Чʱ�̣�������Ч
             
             bit3����Ӧgm_snd_lte_int_3��GM��������ָʾ������Ч��
             ���ڴ����ж�����3 ��int_type_lte_rcv_gm[3]����LTEDSP��LTE��ģ�¶�GM������ϵͳ����ʱ�����GM����������GM DSP���ô˱�־Ϊ1�� 
             ��Чʱ�̣�������Ч
 bit[2:0]    ����
   UNION�ṹ:  BBPCOMM_GM_SND_LTE_INT_13_UNION */
#define BBPCOMM_GM_SND_LTE_INT_13_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x864)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:3]   �߼������㡣����Ч��
             
             bit15~7����Ӧgm_snd_tds_int_15 ~ 7��
             GM DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_tds_rcv_gm[15:7]����TDSDSP��
             ��Чʱ�̣�������Ч
             
             bit6����Ӧgm_snd_tds_int_6��
             GMDSPͨ���˼Ĵ�����������6�жϣ�int_type_tds_rcv_gm[6]����TDSDSP��
             ��Чʱ�̣�������Ч
             
             bit5����Ӧgm_snd_tds_int_5��
             GM��ģʱ֪ͨTDSDSP tds�������ڵ������Ч��
             GM DSPͨ���˼Ĵ�����������5�жϣ�int_type_tds_rcv_gm[5]����TDSDSP��
             ��Чʱ�̣�������Ч
             
             bit4����Ӧgm_snd_tds_int_4��
             GM��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
             GM DSPͨ���˼Ĵ�����������4�жϣ�int_type_tds_rcv_gm[4]����TDSDSP��
             ��Чʱ�̣�������Ч
             
             bit3����Ӧgm_snd_tds_int_3��GM��������ָʾ������Ч��
             ���ڴ����ж�����3 ��int_type_tds_rcv_gm[3]����TDSDSP��tds��ģ�¶�GM������ϵͳ����ʱ�����GM����������GM DSP���ô˱�־Ϊ1�� 
             ��Чʱ�̣�������Ч
 bit[2:0]    ����
   UNION�ṹ:  BBPCOMM_GM_SND_TDS_INT_13_UNION */
#define BBPCOMM_GM_SND_TDS_INT_13_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x868)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:3]   �߼������㡣����Ч��
             
             bit15~7����Ӧgm_snd_gm_int_15 ~ 7��
             GM DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_gm_rcv_gm[15:7]����GMDSP��
             ��Чʱ�̣�������Ч
             
             bit6����Ӧgm_snd_gm_int_6��
             GMDSPͨ���˼Ĵ�����������6�жϣ�int_type_gm_rcv_gm[6]����GMDSP��
             ��Чʱ�̣�������Ч
             
             bit5����Ӧgm_snd_gm_int_5��
             GM��ģʱ֪ͨGMDSP GM�������ڵ������Ч��
             GM DSPͨ���˼Ĵ�����������5�жϣ�int_type_gm_rcv_gm[5]����GMDSP��
             ��Чʱ�̣�������Ч
             
             bit4����Ӧgm_snd_gm_int_4��
             GM��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
             GM DSPͨ���˼Ĵ�����������4�жϣ�int_type_gm_rcv_gm[4]����GMDSP��
             ��Чʱ�̣�������Ч
             
             bit3����Ӧgm_snd_gm_int_3��GM��������ָʾ������Ч��
             ���ڴ����ж�����3 ��int_type_gm_rcv_gm[3]����GMDSP��GM��ģ�¶�GM������ϵͳ����ʱ�����GM����������GM DSP���ô˱�־Ϊ1�� 
             ��Чʱ�̣�������Ч
 bit[2:0]    ����
   UNION�ṹ:  BBPCOMM_GM_SND_GM_INT_13_UNION */
#define BBPCOMM_GM_SND_GM_INT_13_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x86C)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:3]   �߼������㡣����Ч��
             
             bit15~7����Ӧgm_snd_gs_int_15 ~ 7��
             GM DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_gs_rcv_gm[15:7]����GSDSP��
             ��Чʱ�̣�������Ч
             
             bit6����Ӧgm_snd_gs_int_6��
             GMDSPͨ���˼Ĵ�����������6�жϣ�int_type_gs_rcv_gm[6]����GSDSP��
             ��Чʱ�̣�������Ч
             
             bit5����Ӧgm_snd_gs_int_5��
             GM��ģʱ֪ͨGSDSP GS�������ڵ������Ч��
             GM DSPͨ���˼Ĵ�����������5�жϣ�int_type_gs_rcv_gm[5]����GSDSP��
             ��Чʱ�̣�������Ч
             
             bit4����Ӧgm_snd_gs_int_4��
             GM��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
             GM DSPͨ���˼Ĵ�����������4�жϣ�int_type_gs_rcv_gm[4]����GSDSP��
             ��Чʱ�̣�������Ч
             
             bit3����Ӧgm_snd_gs_int_3��GM��������ָʾ������Ч��
             ���ڴ����ж�����3 ��int_type_gs_rcv_gm[3]����GSDSP��GS��ģ�¶�GM������ϵͳ����ʱ�����GM����������GM DSP���ô˱�־Ϊ1�� 
             ��Чʱ�̣�������Ч
 bit[2:0]    ����
   UNION�ṹ:  BBPCOMM_GM_SND_GS_INT_13_UNION */
#define BBPCOMM_GM_SND_GS_INT_13_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x870)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:3]   �߼������㡣����Ч��
             
             bit15~7����Ӧgm_snd_lte_int_15 ~ 7��
             GM DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_lte_rcv_gm[15:7]����LTEDSP��
             ��Чʱ�̣�������Ч
             
             bit6����Ӧgm_snd_lte_int_6��
             GMDSPͨ���˼Ĵ�����������6�жϣ�int_type_lte_rcv_gm[6]����LTEDSP��
             ��Чʱ�̣�������Ч
             
             bit5����Ӧgm_snd_lte_int_5��
             GM��ģʱ֪ͨLTEDSP LTE�������ڵ������Ч��
             GM DSPͨ���˼Ĵ�����������5�жϣ�int_type_lte_rcv_gm[5]����LTEDSP��
             ��Чʱ�̣�������Ч
             
             bit4����Ӧgm_snd_lte_int_4��
             GM��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
             GM DSPͨ���˼Ĵ�����������4�жϣ�int_type_lte_rcv_gm[4]����LTEDSP��
             ��Чʱ�̣�������Ч
             
             bit3����Ӧgm_snd_lte_int_3��GM��������ָʾ������Ч��
             ���ڴ����ж�����3 ��int_type_lte_rcv_gm[3]����LTEDSP��LTE��ģ�¶�GM������ϵͳ����ʱ�����GM����������GM DSP���ô˱�־Ϊ1�� 
             ��Чʱ�̣�������Ч
 bit[2:0]    ����
   UNION�ṹ:  BBPCOMM_GM_SND_W_INT_13_UNION */
#define BBPCOMM_GM_SND_W_INT_13_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x874)

/* �Ĵ���˵�����Ĵ���
 bit[31:4]   ����
 bit[3:0]    ��ϵͳ�������͡�
             4��d0������GS RSSI��
             4��d1: ����GS bsic verification��
             4��d2: ����GS bsic confirm��
             4��d3: ������GS
             4��d4: 2G ANR��
             ����Ԥ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_GS_INTERSYS_MEASURE_TYPE_UNION */
#define BBPCOMM_GS_INTERSYS_MEASURE_TYPE_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x878)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      ��Ƶ��������ڵ�ָʾ��L����TDS/W/Gm��Ϊ��ģ��֪ͨGS DSP GS�����ĵ�Ƶ�����ڵ��
             ֻ������̬����Ҫ���á�
             ��ƽ�źţ�����Ч��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_GS_MEASURE_REPORT_VALID_UNION */
#define BBPCOMM_GS_MEASURE_REPORT_VALID_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x87C)

/* �Ĵ���˵�����Ĵ���
   ��      ����Ԥ�����ж�int0��int1֮���offset��Ϣ����λus������ȡ��������
               ����ʱ�̣���ģ����GS��ģ��ϵͳ����ʱ����
               ��Чʱ�̣�������Ч
   UNION�ṹ ���� */
#define BBPCOMM_GS_PREINT_OFFSET_TIME_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x880)

/* �Ĵ���˵�����Ĵ���
   ��      ����GS��Ϊ��ģʱ����ģ�����GS������ϵͳ����ʱ�䳤�ȣ���֪GSDSP����λus������ȡ����us��
               ����ʱ�̣���ģ����GS��ģ��ϵͳ����ʱ����
               ��Чʱ�̣�������Ч
   UNION�ṹ ���� */
#define BBPCOMM_GS_INTERSYS_MEASURE_TIME_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x884)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_GS_RCV_LTE[15:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_GS_RCV_LTE_UNION */
#define BBPCOMM_INT_CLEAR_GS_RCV_LTE_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x888)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_GS_RCV_TDS[15:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_GS_RCV_TDS_UNION */
#define BBPCOMM_INT_CLEAR_GS_RCV_TDS_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x88C)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_GS_RCV_GM[15:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_GS_RCV_GM_UNION */
#define BBPCOMM_INT_CLEAR_GS_RCV_GM_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x890)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_GS_RCV_GS[15:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_GS_RCV_GS_UNION */
#define BBPCOMM_INT_CLEAR_GS_RCV_GS_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x894)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_GS_RCV_W[15:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_GS_RCV_W_UNION */
#define BBPCOMM_INT_CLEAR_GS_RCV_W_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x898)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_GS_INT012[2:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_GS_INT012_UNION */
#define BBPCOMM_INT_CLEAR_GS_INT012_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x89C)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж����α�־����������INT_TYPE_GS_RCV_LTE[15:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_GS_RCV_LTE_UNION */
#define BBPCOMM_INT_MASK_GS_RCV_LTE_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x8A0)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж����α�־����������INT_TYPE_GS_RCV_TDS[15:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_GS_RCV_TDS_UNION */
#define BBPCOMM_INT_MASK_GS_RCV_TDS_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x8A4)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж����α�־����������INT_TYPE_GS_RCV_GM[15:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_GS_RCV_GM_UNION */
#define BBPCOMM_INT_MASK_GS_RCV_GM_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x8A8)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж����α�־����������INT_TYPE_GS_RCV_GS[15:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_GS_RCV_GS_UNION */
#define BBPCOMM_INT_MASK_GS_RCV_GS_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x8AC)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж����α�־����������INT_TYPE_GS_RCV_W[15:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_GS_RCV_W_UNION */
#define BBPCOMM_INT_MASK_GS_RCV_W_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x8B0)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    �ж����α�־����������INT_TYPE_GS_INT012[2:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_GS_INT012_UNION */
#define BBPCOMM_INT_MASK_GS_INT012_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x8B4)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
             [0]: �ж�����0�� LTE����ģ����ǰ֪ͨGS��ϵͳ���������жϡ�
             [1]: �ж�����1�� LTE����ģ����GAP�жϣ�֪ͨGS������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
             [2]: �ж�����2�� LTE����ģ����GAP�жϡ�
             [3]: �ж�����3��LTE����ģ�����������жϡ�
             [4]: �ж�����4��LTE����ģ��ǿ��GS�˳���ϵͳ�����жϡ�
             [5]: �ж�����5��LTE����ģ��֪ͨGS�ϱ����β��������
             [6]: ������
             [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x08A0��int_mask_gs_rcv_lte���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_GS_RCV_LTE_UNION */
#define BBPCOMM_INT_TYPE_GS_RCV_LTE_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x8B8)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж�״̬��־0��1��2ֻ�е�TDS������ģʱ���ܲ�����
             
             [0]: �ж�����0�� TDS����ģ����ǰ֪ͨGS��ϵͳ���������жϡ�
             [1]: �ж�����1�� TDS����ģ����GAP�жϣ�֪ͨGS������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
             [2]: �ж�����2�� TDS����ģ����GAP�жϡ�
             [3]: �ж�����3��TDS����ģ�����������жϡ�
             [4]: �ж�����4��TDS����ģ��ǿ��GS�˳���ϵͳ�����жϡ�
             [5]: �ж�����5��TDS����ģ��֪ͨGS�ϱ����β��������
             [6]: �ж�����6��������
             [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x08A4��int_mask_gs_rcv_tds���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_GS_RCV_TDS_UNION */
#define BBPCOMM_INT_TYPE_GS_RCV_TDS_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x8BC)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
             [0]: �ж�����0��GM����ģ����ǰ֪ͨGS��ϵͳ���������жϡ�
             [1]: �ж�����1��GM����ģ����GAP�жϣ�֪ͨGS������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
             [2]: �ж�����2��GM����ģ����GAP�жϡ�
             [3]: �ж�����3��GM����ģ�����������жϡ�
             [4]: �ж�����4��GM����ģ��ǿ��GS�˳���ϵͳ�����жϡ�
             [5]: �ж�����5��GM����ģ��֪ͨGS�ϱ����β��������
             [6]: �ж�����6��������
             [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
             �ж�״̬��־0��1��2ֻ�е�GM������ģʱ���ܲ�����
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x08A8��int_mask_gs_rcv_gm���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_GS_RCV_GM_UNION */
#define BBPCOMM_INT_TYPE_GS_RCV_GM_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x8C0)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   [0]: �ж�����0��GS����ģ����ǰ֪ͨGS��ϵͳ���������жϡ�
             [1]: �ж�����1��GS����ģ����GAP�жϣ�֪ͨGS������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
             [2]: �ж�����2��GS����ģ����GAP�жϡ�
             [3]: �ж�����3��GS����ģ�����������жϡ�
             [4]: �ж�����4��GS����ģ��ǿ��GS�˳���ϵͳ�����жϡ�
             [5]: �ж�����5��GS����ģ��֪ͨGS�ϱ����β��������
             [6]: �ж�����6��������
             [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
             �ж�״̬��־0��1��2ֻ�е�TDS������ģʱ���ܲ�����
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x08AC��int_mask_gs_rcv_gs���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_GS_RCV_GS_UNION */
#define BBPCOMM_INT_TYPE_GS_RCV_GS_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x8C4)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
             [0]: �ж�����0��W����ģ����ǰ֪ͨGS��Ƶ���������жϡ�
             [1]: �ж�����1��W����ģ����GAP�жϣ�֪ͨGS������Ƶ������Ƶͨ�����ã������л��Ȳ�����
             [2]: �ж�����2��W����ģ����GAP�жϡ�
             [3]: �ж�����3��W����ģ������Ƶ�����������жϡ�
             [4]: �ж�����4��W����ģ��ǿ��GS�˳���Ƶ�����жϡ�
             [5]: �ж�����5��W����ģ��֪ͨGS�ϱ����β��������
             [6]: �ж�����6��������
             [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
             �ж�״̬��־0��1��2ֻ�е�W������ģʱ���ܲ�����
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x08B0��int_mask_gs_rcv_w���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_GS_RCV_W_UNION */
#define BBPCOMM_INT_TYPE_GS_RCV_W_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x8C8)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    ��ģ����int0��1��2���ϱ���(������Ƶ����ϵͳ����)��������Ч��
             [0]: GS��ģʱ��CTU����֪ͨGSDSP����int0�жϡ�
             [1]: GS��ģʱ��CTU����֪ͨGSDSP����int1�жϡ�
             [2]: GS��ģʱ��CTU����֪ͨGSDSP����int2�жϡ�
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x08B4��int_mask_gs_int012���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_GS_INT012_UNION */
#define BBPCOMM_INT_TYPE_GS_INT012_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x8CC)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:3]   �߼������㡣����Ч��
             
             bit15~7����Ӧgs_snd_lte_int_15 ~ 7��
             GS DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_lte_rcv_gs[15:7]����LTEDSP��
             ��Чʱ�̣�������Ч
             
             bit6����Ӧgs_snd_lte_int_6��
             GSDSPͨ���˼Ĵ�����������6�жϣ�int_type_lte_rcv_gs[6]����LTEDSP��
             ��Чʱ�̣�������Ч
             
             bit5����Ӧgs_snd_lte_int_5��
             GS��ģʱ֪ͨLTEDSP LTE�������ڵ������Ч��
             GS DSPͨ���˼Ĵ�����������5�жϣ�int_type_lte_rcv_gs[5]����LTEDSP��
             ��Чʱ�̣�������Ч
             
             bit4����Ӧgs_snd_lte_int_4��
             GS��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
             GS DSPͨ���˼Ĵ�����������4�жϣ�int_type_lte_rcv_gs[4]����LTEDSP��
             ��Чʱ�̣�������Ч
             
             bit3����Ӧgs_snd_lte_int_3��GS��������ָʾ������Ч��
             ���ڴ����ж�����3 ��int_type_lte_rcv_gs[3]����LTEDSP��LTE��ģ�¶�GS������ϵͳ����ʱ�����GS����������GS DSP���ô˱�־Ϊ1�� 
             ��Чʱ�̣�������Ч
 bit[2:0]    ����
   UNION�ṹ:  BBPCOMM_GS_SND_LTE_INT_13_UNION */
#define BBPCOMM_GS_SND_LTE_INT_13_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x8D0)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:3]   �߼������㡣����Ч��
             
             bit15~7����Ӧgs_snd_tds_int_15 ~ 7��
             GS DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_tds_rcv_gs[15:7]����TDSDSP��
             ��Чʱ�̣�������Ч
             
             bit6����Ӧgs_snd_tds_int_6��
             GSDSPͨ���˼Ĵ�����������6�жϣ�int_type_tds_rcv_gs[6]����TDSDSP��
             ��Чʱ�̣�������Ч
             
             bit5����Ӧgs_snd_tds_int_5��
             GS��ģʱ֪ͨTDSDSP TDS�������ڵ������Ч��
             GS DSPͨ���˼Ĵ�����������5�жϣ�int_type_tds_rcv_gs[5]����TDSDSP��
             ��Чʱ�̣�������Ч
             
             bit4����Ӧgs_snd_tds_int_4��
             GS��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
             GS DSPͨ���˼Ĵ�����������4�жϣ�int_type_tds_rcv_gs[4]����TDSDSP��
             ��Чʱ�̣�������Ч
             
             bit3����Ӧgs_snd_tds_int_3��GS��������ָʾ������Ч��
             ���ڴ����ж�����3 ��int_type_tds_rcv_gs[3]����TDSDSP��TDS��ģ�¶�GS������ϵͳ����ʱ�����GS����������GS DSP���ô˱�־Ϊ1�� 
             ��Чʱ�̣�������Ч
 bit[2:0]    ����
   UNION�ṹ:  BBPCOMM_GS_SND_TDS_INT_13_UNION */
#define BBPCOMM_GS_SND_TDS_INT_13_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x8D4)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:3]   �߼������㡣����Ч��
             
             bit15~7����Ӧgs_snd_gm_int_15 ~ 7��
             GS DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_gm_rcv_gs[15:7]����GMDSP��
             ��Чʱ�̣�������Ч
             
             bit6����Ӧgs_snd_gm_int_6��
             GSDSPͨ���˼Ĵ�����������6�жϣ�int_type_gm_rcv_gs[6]����GMDSP��
             ��Чʱ�̣�������Ч
             
             bit5����Ӧgs_snd_gm_int_5��
             GS��ģʱ֪ͨGMDSP GM�������ڵ������Ч��
             GS DSPͨ���˼Ĵ�����������5�жϣ�int_type_gm_rcv_gs[5]����GMDSP��
             ��Чʱ�̣�������Ч
             
             bit4����Ӧgs_snd_gm_int_4��
             GS��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
             GS DSPͨ���˼Ĵ�����������4�жϣ�int_type_gm_rcv_gs[4]����GMDSP��
             ��Чʱ�̣�������Ч
             
             bit3����Ӧgs_snd_gm_int_3��GS��������ָʾ������Ч��
             ���ڴ����ж�����3 ��int_type_gm_rcv_gs[3]����GMDSP��GM��ģ�¶�GS������ϵͳ����ʱ�����GS����������GS DSP���ô˱�־Ϊ1�� 
             ��Чʱ�̣�������Ч
 bit[2:0]    ����
   UNION�ṹ:  BBPCOMM_GS_SND_GM_INT_13_UNION */
#define BBPCOMM_GS_SND_GM_INT_13_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x8D8)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:3]   �߼������㡣����Ч��
             
             bit15~7����Ӧgs_snd_gs_int_15 ~ 7��
             GS DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_gs_rcv_gs[15:7]����GSDSP��
             ��Чʱ�̣�������Ч
             
             bit6����Ӧgs_snd_gs_int_6��
             GSDSPͨ���˼Ĵ�����������6�жϣ�int_type_gs_rcv_gs[6]����GSDSP��
             ��Чʱ�̣�������Ч
             
             bit5����Ӧgs_snd_gs_int_5��
             GS��ģʱ֪ͨGSDSP GS�������ڵ������Ч��
             GS DSPͨ���˼Ĵ�����������5�жϣ�int_type_gs_rcv_gs[5]����GSDSP��
             ��Чʱ�̣�������Ч
             
             bit4����Ӧgs_snd_gs_int_4��
             GS��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
             GS DSPͨ���˼Ĵ�����������4�жϣ�int_type_gs_rcv_gs[4]����GSDSP��
             ��Чʱ�̣�������Ч
             
             bit3����Ӧgs_snd_gs_int_3��GS��������ָʾ������Ч��
             ���ڴ����ж�����3 ��int_type_gs_rcv_gs[3]����GSDSP��GS��ģ�¶�GS������ϵͳ����ʱ�����GS����������GS DSP���ô˱�־Ϊ1�� 
             ��Чʱ�̣�������Ч
 bit[2:0]    ����
   UNION�ṹ:  BBPCOMM_GS_SND_GS_INT_13_UNION */
#define BBPCOMM_GS_SND_GS_INT_13_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x8DC)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:3]   �߼������㡣����Ч��
             
             bit15~7����Ӧgs_snd_w_int_15 ~ 7��
             GS DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_w_rcv_gs[15:7]����WDSP��
             ��Чʱ�̣�������Ч
             
             bit6����Ӧgs_snd_w_int_6��
             GSDSPͨ���˼Ĵ�����������6�жϣ�int_type_w_rcv_gs[6]����WDSP��
             ��Чʱ�̣�������Ч
             
             bit5����Ӧgs_snd_w_int_5��
             GS��ģʱ֪ͨWDSP W�������ڵ������Ч��
             GS DSPͨ���˼Ĵ�����������5�жϣ�int_type_w_rcv_gs[5]����WDSP��
             ��Чʱ�̣�������Ч
             
             bit4����Ӧgs_snd_w_int_4��
             GS��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
             GS DSPͨ���˼Ĵ�����������4�жϣ�int_type_w_rcv_gs[4]����WDSP��
             ��Чʱ�̣�������Ч
             
             bit3����Ӧgs_snd_w_int_3��GS��������ָʾ������Ч��
             ���ڴ����ж�����3 ��int_type_w_rcv_gs[3]����WDSP��W��ģ�¶�GS������ϵͳ����ʱ�����GS����������GS DSP���ô˱�־Ϊ1�� 
             ��Чʱ�̣�������Ч
 bit[2:0]    ����
   UNION�ṹ:  BBPCOMM_GS_SND_W_INT_13_UNION */
#define BBPCOMM_GS_SND_W_INT_13_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x8E0)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    V9R1�汾����������á�
   UNION�ṹ:  BBPCOMM_GBBP1_19M_SEL_UNION */
#define BBPCOMM_GBBP1_19M_SEL_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x8E4)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    V9R1�汾����������á�
   UNION�ṹ:  BBPCOMM_GBBP2_19M_SEL_UNION */
#define BBPCOMM_GBBP2_19M_SEL_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x8E8)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    V9R1�汾����������á�
   UNION�ṹ:  BBPCOMM_WBBP_19M_SEL_UNION */
#define BBPCOMM_WBBP_19M_SEL_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x8EC)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    V9R1�汾����������á�
   UNION�ṹ:  BBPCOMM_LBBP_19M_SEL_UNION */
#define BBPCOMM_LBBP_19M_SEL_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x8F0)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    V9R1�汾����������á�
   UNION�ṹ:  BBPCOMM_TBBP1_19M_SEL_UNION */
#define BBPCOMM_TBBP1_19M_SEL_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x8F4)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    V9R1�汾����������á�
   UNION�ṹ:  BBPCOMM_GBBP1_CLK_SEL_UNION */
#define BBPCOMM_GBBP1_CLK_SEL_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x8F8)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    V9R1�汾����������á�
   UNION�ṹ:  BBPCOMM_GBBP2_CLK_SEL_UNION */
#define BBPCOMM_GBBP2_CLK_SEL_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x8FC)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    V9R1�汾����������á�
   UNION�ṹ:  BBPCOMM_WBBP_CLK_SEL_UNION */
#define BBPCOMM_WBBP_CLK_SEL_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x900)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    V9R1�汾����������á�
   UNION�ṹ:  BBPCOMM_LBBP_CLK_SEL_UNION */
#define BBPCOMM_LBBP_CLK_SEL_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x904)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    V9R1�汾����������á�
   UNION�ṹ:  BBPCOMM_TBBP_CLK_SEL_UNION */
#define BBPCOMM_TBBP_CLK_SEL_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x908)

/* �Ĵ���˵�����Ĵ���
 bit[31:10]  ����
 bit[9:9]    1'b1��LTE��TXͨ·I·����ȡ��
             1'b0��LTE��TXͨ·I·���ݲ�ȡ��
 bit[8:8]    1'b1��LTE��TXͨ·Q·����ȡ��
             1'b0��LTE��TXͨ·Q·���ݲ�ȡ��
 bit[7:7]    1'b1��LTE��TXͨ·IQ·���ݽ���
             1'b0��LTE��TXͨ·IQ·���ݲ�����
             V3R3��֧��IQ�������ܡ�
 bit[6:6]    1'b1��LTE��RXAͨ·I·����ȡ��
             1'b0��LTE��RXAͨ·I·���ݲ�ȡ��
 bit[5:5]    1'b1��LTE��RXAͨ·Q·����ȡ��
             1'b0��LTE��RXAͨ·Q·���ݲ�ȡ��
 bit[4:4]    1'b1��LTE��RXAͨ·IQ·���ݽ���
             1'b0��LTE��RXAͨ·IQ·���ݲ�����
             V3R3��֧��IQ�������ܡ�
 bit[3:3]    1'b1��LTE��RXBͨ·I·����ȡ��
             1'b0��LTE��RXBͨ·I·���ݲ�ȡ��
 bit[2:2]    1'b1��LTE��RXBͨ·Q·����ȡ��
             1'b0��LTE��RXBͨ·Q·���ݲ�ȡ��
 bit[1:1]    1'b1��LTE��RXBͨ·IQ·���ݽ���
             1'b0��LTE��RXBͨ·IQ·���ݲ�����
             V3R3��֧��IQ�������ܡ�
 bit[0:0]    ����
   UNION�ṹ:  BBPCOMM_LTE_ABBIF_FMT_UNION */
#define BBPCOMM_LTE_ABBIF_FMT_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x90C)

/* �Ĵ���˵�����Ĵ���
 bit[31:10]  ����
 bit[9:9]    1'b1��W��TXͨ·I·����ȡ��
             1'b0��W��TXͨ·I·���ݲ�ȡ����
 bit[8:8]    1'b1��W��TXͨ·Q·����ȡ��
             1'b0��W��TXͨ·Q·���ݲ�ȡ��
 bit[7:7]    1'b1��W��TXͨ·IQ·���ݽ���
             1'b0��W��TXͨ·IQ·���ݲ�����
             V3R3��֧��IQ�������ܡ�
 bit[6:6]    1'b1��W��RXAͨ·I·����ȡ��
             1'b0��W��RXAͨ·I·���ݲ�ȡ��
 bit[5:5]    1'b1��W��RXAͨ·Q·����ȡ��
             1'b0��W��RXAͨ·Q·���ݲ�ȡ��
 bit[4:4]    1'b1��W��RXAͨ·IQ·���ݽ���
             1'b0��W��RXAͨ·IQ·���ݲ�����
             V3R3��֧��IQ�������ܡ�
 bit[3:3]    1'b1��W��RXBͨ·I·����ȡ��
             1'b0��W��RXBͨ·I·���ݲ�ȡ��
 bit[2:2]    1'b1��W��RXBͨ·Q·����ȡ��
             1'b0��W��RXBͨ·Q·���ݲ�ȡ��
 bit[1:1]    1'b1��W��RXBͨ·IQ·���ݽ���
             1'b0��W��RXBͨ·IQ·���ݲ�����
             V3R3��֧��IQ�������ܡ�
 bit[0:0]    ����
   UNION�ṹ:  BBPCOMM_W_ABBIF_FMT_UNION */
#define BBPCOMM_W_ABBIF_FMT_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x910)

/* �Ĵ���˵�����Ĵ���
 bit[31:10]  ����
 bit[9:9]    1'b1��TDS��TXͨ·I·����ȡ��
             1'b0��TDS��TXͨ·I·���ݲ�ȡ��
 bit[8:8]    1'b1��TDS��TXͨ·Q·����ȡ��
             1'b0��TDS��TXͨ·Q·���ݲ�ȡ��
 bit[7:7]    1'b1��TDS��TXͨ·IQ·���ݽ���
             1'b0��TDS��TXͨ·IQ·���ݲ�����
             V3R3��֧��IQ�������ܡ�
 bit[6:6]    1'b1��TDS��RXAͨ·I·����ȡ��
             1'b0��TDS��RXAͨ·I·���ݲ�ȡ��
 bit[5:5]    1'b1��TDS��RXAͨ·Q·����ȡ��
             1'b0��TDS��RXAͨ·Q·���ݲ�ȡ��
 bit[4:4]    1'b1��TDS��RXAͨ·IQ·���ݽ���
             1'b0��TDS��RXAͨ·IQ·���ݲ�����
             V3R3��֧��IQ�������ܡ�
 bit[3:3]    1'b1��TDS��RXBͨ·I·����ȡ��
             1'b0��TDS��RXBͨ·I·���ݲ�ȡ��
 bit[2:2]    1'b1��TDS��RXBͨ·Q·����ȡ��
             1'b0��TDS��RXBͨ·Q·���ݲ�ȡ��
 bit[1:1]    1'b1��TDS��RXBͨ·IQ·���ݽ���
             1'b0��TDS��RXBͨ·IQ·���ݲ�����
             V3R3��֧��IQ�������ܡ�
 bit[0:0]    ����
   UNION�ṹ:  BBPCOMM_TDS_ABBIF_FMT_UNION */
#define BBPCOMM_TDS_ABBIF_FMT_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x914)

/* �Ĵ���˵�����Ĵ���
 bit[31:10]  ����
 bit[9:9]    1'b1��GM��TXͨ·I·����ȡ��
             1'b0��GM��TXͨ·I·���ݲ�ȡ��
 bit[8:8]    1'b1��GM��TXͨ·Q·����ȡ��
             1'b0��GM��TXͨ·Q·���ݲ�ȡ��
 bit[7:7]    1'b1��GM��TXͨ·IQ·���ݽ���
             1'b0��GM��TXͨ·IQ·���ݲ�����
             V3R3��֧��IQ�������ܡ�
 bit[6:6]    1'b1��GM��RXAͨ·I·����ȡ��
             1'b0��GM��RXAͨ·I·���ݲ�ȡ��
 bit[5:5]    1'b1��GM��RXAͨ·Q·����ȡ��
             1'b0��GM��RXAͨ·Q·���ݲ�ȡ��
 bit[4:4]    1'b1��GM��RXAͨ·IQ·���ݽ���
             1'b0��GM��RXAͨ·IQ·���ݲ�����
             V3R3��֧��IQ�������ܡ�
 bit[3:3]    1'b1��GM��RXBͨ·I·����ȡ��
             1'b0��GM��RXBͨ·I·���ݲ�ȡ��
 bit[2:2]    1'b1��GM��RXBͨ·Q·����ȡ��
             1'b0��GM��RXBͨ·Q·���ݲ�ȡ��
 bit[1:1]    1'b1��GM��RXBͨ·IQ·���ݽ���
             1'b0��GM��RXBͨ·IQ·���ݲ�����
             V3R3��֧��IQ�������ܡ�
 bit[0:0]    ����
   UNION�ṹ:  BBPCOMM_GM_ABBIF_FMT_UNION */
#define BBPCOMM_GM_ABBIF_FMT_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x918)

/* �Ĵ���˵�����Ĵ���
 bit[31:10]  ����
 bit[9:9]    1'b1��GS��TXͨ·I·����ȡ��
             1'b0��GS��TXͨ·I·���ݲ�ȡ��
 bit[8:8]    1'b1��GS��TXͨ·Q·����ȡ��
             1'b0��GS��TXͨ·Q·���ݲ�ȡ��
 bit[7:7]    1'b1��GS��TXͨ·IQ·���ݽ���
             1'b0��GS��TXͨ·IQ·���ݲ�����
             V3R3��֧��IQ�������ܡ�
 bit[6:6]    1'b1��GS��RXAͨ·I·����ȡ��
             1'b0��GS��RXAͨ·I·���ݲ�ȡ��
 bit[5:5]    1'b1��GS��RXAͨ·Q·����ȡ��
             1'b0��GS��RXAͨ·Q·���ݲ�ȡ��
 bit[4:4]    1'b1��GS��RXAͨ·IQ·���ݽ���
             1'b0��GS��RXAͨ·IQ·���ݲ�����
             V3R3��֧��IQ�������ܡ�
 bit[3:3]    1'b1��GS��RXBͨ·I·����ȡ��
             1'b0��GS��RXBͨ·I·���ݲ�ȡ��
 bit[2:2]    1'b1��GS��RXBͨ·Q·����ȡ��
             1'b0��GS��RXBͨ·Q·���ݲ�ȡ��
 bit[1:1]    1'b1��GS��RXBͨ·IQ·���ݽ���
             1'b0��GS��RXBͨ·IQ·���ݲ�����
             V3R3��֧��IQ�������ܡ�
 bit[0:0]    ����
   UNION�ṹ:  BBPCOMM_GS_ABBIF_FMT_UNION */
#define BBPCOMM_GS_ABBIF_FMT_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x91C)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���3��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG0_FOR_USE_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x920)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���4��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG1_FOR_USE_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x924)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���4��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG2_FOR_USE_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x928)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���6��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG3_FOR_USE_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x92C)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���7��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG4_FOR_USE_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x930)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���8��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG5_FOR_USE_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x934)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���9��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG6_FOR_USE_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x938)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���7��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG7_FOR_USE_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x93C)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���8��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG8_FOR_USE_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x940)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���9��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG9_FOR_USE_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x944)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���10��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG10_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x948)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���11��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG11_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x94C)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���12��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG12_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x950)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���13��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG13_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x954)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���14��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG14_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x958)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���15��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG15_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x95C)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���16��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG16_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x960)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���17��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG17_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x964)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���18��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG18_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x968)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���19��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG19_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x96C)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���20��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG20_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x970)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���21��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG21_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x974)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���22��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG22_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x978)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���23��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG23_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x97C)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   �Ĵ���24��Ԥ������DSP֮�䴫����Ϣ��
 bit[0]      GSM1��ͨ����Ƶ����ģʽʹ�ܣ�
             1'b0����ʹ��
             1'b1��ʹ��
             
             V7R2������
   UNION�ṹ:  BBPCOMM_REG24_FOR_USE_UNION */
#define BBPCOMM_REG24_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x980)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   �Ĵ���25��Ԥ������DSP֮�䴫����Ϣ��
 bit[0]      GSM2��ͨ����Ƶ����ģʽʹ�ܣ�
             1'b0����ʹ��
             1'b1��ʹ��
             
             V7R2������
   UNION�ṹ:  BBPCOMM_REG25_FOR_USE_UNION */
#define BBPCOMM_REG25_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x984)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   �Ĵ���26��Ԥ������DSP֮�䴫����Ϣ��
 bit[2]      ͨ��1ӳ��ssi������ϵ��
             1'b0��ͨ��1ӳ�䵽ssi0
             1'b1��ͨ��1ӳ�䵽ssi1
             
             V7R2������
 bit[1]      ͨ��0ӳ��ssi������ϵ��
             1'b0��ͨ��0ӳ�䵽ssi0
             1'b1��ͨ��0ӳ�䵽ssi1
             
             V7R2������
 bit[0]      ssiͨ������ʹ�ܣ�
             1'b0��ͨ����
             1'b1��ͨ������
             
             V7R2������
   UNION�ṹ:  BBPCOMM_REG26_FOR_USE_UNION */
#define BBPCOMM_REG26_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x988)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   �Ĵ���27��Ԥ������DSP֮�䴫����Ϣ��
 bit[0]      �����RF��TCVR_ON ˫ͨ��һ��ʹ��
             1������ͨ����TCVR_ON���ߣ���2��ͨ����TCVR_ON�����ߣ�
             0�����ݸ���ͨ��״̬����
             
             V7R2������
   UNION�ṹ:  BBPCOMM_REG27_FOR_USE_UNION */
#define BBPCOMM_REG27_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x98C)

/* �Ĵ���˵�����Ĵ���
 bit[31:4]   �Ĵ���28��Ԥ������DSP֮�䴫����Ϣ��
 bit[3:1]    �����ABB_CFGģ���ѡͨ�ź�ch0_sel_abbǿ��ʱ������ֵ
             
             V7R2������
 bit[0]      �����ABB_CFGģ���ѡͨ�ź�ch1_sel_abb�Ƿ�ǿ��ʹ��
             1��ǿ�ƣ�ǿ��ֵΪch0_abb_sel_force_value
             0����ǿ�ƣ��߼��Կ�
             
             V7R2������
   UNION�ṹ:  BBPCOMM_REG28_FOR_USE_UNION */
#define BBPCOMM_REG28_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x990)

/* �Ĵ���˵�����Ĵ���
 bit[31:4]   �Ĵ���29��Ԥ������DSP֮�䴫����Ϣ��
 bit[3:1]    �����ABB_CFGģ���ѡͨ�ź�ch1_sel_abbǿ��ʱ������ֵ
             
             V7R2������
 bit[0]      �����ABB_CFGģ���ѡͨ�ź�ch1_sel_abb�Ƿ�ǿ��ʹ��
             1��ǿ�ƣ�ǿ��ֵΪch1_abb_sel_force_value
             0����ǿ�ƣ��߼��Կ�
             
             V7R2������
   UNION�ṹ:  BBPCOMM_REG29_FOR_USE_UNION */
#define BBPCOMM_REG29_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x994)

/* �Ĵ���˵�����Ĵ���
 bit[31:12]  �Ĵ���30��Ԥ������DSP֮�䴫����Ϣ��
 bit[11:0]   ch0��com2abb_line_ctrl_mode�л�ʱ��com2abb_rxa/b_enǿ�����͵�ʱ�䡣��λ������ʱ��
             
             V7R2������
   UNION�ṹ:  BBPCOMM_REG30_FOR_USE_UNION */
#define BBPCOMM_REG30_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x998)

/* �Ĵ���˵�����Ĵ���
 bit[31:12]  �Ĵ���31��Ԥ������DSP֮�䴫����Ϣ��
 bit[11:0]   ch1��com2abb_line_ctrl_mode�л�ʱ��com2abb_rxa/b_enǿ�����͵�ʱ�䡣��λ������ʱ��
             
             V7R2������
   UNION�ṹ:  BBPCOMM_REG31_FOR_USE_UNION */
#define BBPCOMM_REG31_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x99C)

/* �Ĵ���˵�����Ĵ���
 bit[31:5]   �Ĵ���32��Ԥ������DSP֮�䴫����Ϣ��
 bit[4]      
 bit[3:1]    ����
 bit[0]      
   UNION�ṹ:  BBPCOMM_REG32_FOR_USE_UNION */
#define BBPCOMM_REG32_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x9A0)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   �Ĵ���33��Ԥ������DSP֮�䴫����Ϣ��
 bit[0]      
   UNION�ṹ:  BBPCOMM_REG33_FOR_USE_UNION */
#define BBPCOMM_REG33_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x9A4)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���34��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG34_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x9A8)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���35��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG35_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x9AC)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���36��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG36_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x9B0)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���37��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG37_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x9B4)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���38��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG38_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x9B8)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���39��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG39_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x9BC)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���40��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG40_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x9C0)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���41��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG41_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x9C4)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���42��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG42_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x9C8)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���43��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG43_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x9CC)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���44��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG44_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x9D0)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���45��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG45_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x9D4)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���46��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG46_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x9D8)

/* �Ĵ���˵�����Ĵ���
   ��      �����Ĵ���47��Ԥ������DSP֮�䴫����Ϣ��
   UNION�ṹ ���� */
#define BBPCOMM_REG47_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x9DC)

/* �Ĵ���˵�����Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define BBPCOMM_DBG_REG0_CPU_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x9E0)

/* �Ĵ���˵�����Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define BBPCOMM_DBG_REG1_CPU_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x9E4)

/* �Ĵ���˵�����Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define BBPCOMM_DBG_REG2_CPU_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x9E8)

/* �Ĵ���˵�����Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define BBPCOMM_DBG_REG3_CPU_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x9EC)

/* �Ĵ���˵�����Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define BBPCOMM_DBG_REG4_CPU_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x9F0)

/* �Ĵ���˵�����Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define BBPCOMM_DBG_REG5_CPU_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x9F4)

/* �Ĵ���˵�����Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define BBPCOMM_DBG_REG6_CPU_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x9F8)

/* �Ĵ���˵�����Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define BBPCOMM_DBG_REG7_CPU_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x9FC)

/* �Ĵ���˵�����Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define BBPCOMM_DBG_REG8_CPU_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0xA00)

/* �Ĵ���˵�����Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define BBPCOMM_DBG_REG9_CPU_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0xA04)

/* �Ĵ���˵�����Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define BBPCOMM_DBG_REG10_CPU_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xA08)

/* �Ĵ���˵�����Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define BBPCOMM_DBG_REG11_CPU_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xA0C)

/* �Ĵ���˵�����Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define BBPCOMM_DBG_REG12_CPU_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xA10)

/* �Ĵ���˵�����Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define BBPCOMM_DBG_REG13_CPU_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xA14)

/* �Ĵ���˵�����Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define BBPCOMM_DBG_REG14_CPU_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xA18)

/* �Ĵ���˵�����Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define BBPCOMM_DBG_REG15_CPU_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xA1C)

/* �Ĵ���˵�����Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define BBPCOMM_DBG_REG16_CPU_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xA20)

/* �Ĵ���˵�����Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define BBPCOMM_DBG_REG17_CPU_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xA24)

/* �Ĵ���˵�����Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define BBPCOMM_DBG_REG18_CPU_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xA28)

/* �Ĵ���˵�����Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define BBPCOMM_DBG_REG19_CPU_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xA2C)

/* �Ĵ���˵�����ſ�ʱ�����üĴ���
 bit[31:2]   ����
 bit[1:1]    bbp_comm_dbgģ��ʱ��bypass�����źţ�
             1��ֱ��ʹ������ʱ�ӣ��������ſش�����ʱdsp_dbg_clk_gate_en������Ч��
             0����ʾ����dsp_dbg_clk_gate_en�����ſش���
 bit[0:0]    bbp_comm_dbgģ���ſ�ʱ��ʹ���źţ�
             1��ֱ��ʹ������ʱ�ӣ�δ�����ſأ�
             0������ʱ����Ч����ʱ���е͹���״̬��
   UNION�ṹ:  BBPCOMM_DBG_CLK_GATE_EN_UNION */
#define BBPCOMM_DBG_CLK_GATE_EN_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xA30)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23]     C MIPI0æ��־��
 bit[22]     C MIPI1æ��־��
 bit[21]     C SSI0æ��־��
 bit[20]     C SSI1æ��־��
 bit[19]     G1 MIPI0æ��־��
 bit[18]     G1 MIPI1æ��־��
 bit[17]     G2 MIPI0æ��־��
 bit[16]     G2 MIPI1æ��־��
 bit[15]     LTE MIPI0æ��־��
 bit[14]     LTE MIPI1æ��־��
 bit[13]     W MIPI0æ��־��
 bit[12]     W MIPI1æ��־��
 bit[11]     TDS MIPI0æ��־��
 bit[10]     TDS MIPI1æ��־��
 bit[9]      G1 SSI0æ��־��
 bit[8]      G1 SSI1æ��־��
 bit[7]      G2 SSI0æ��־��
 bit[6]      G2 SSI1æ��־��
 bit[5]      LTE SSI0æ��־��
 bit[4]      LTE SSI1æ��־��
 bit[3]      W SSI0æ��־��
 bit[2]      W SSI1æ��־��
 bit[1]      TDS SSI0æ��־��
 bit[0]      TDS SSI1æ��־��
   UNION�ṹ:  BBPCOMM_MIPI_SSI_BUSY_STATE_UNION */
#define BBPCOMM_MIPI_SSI_BUSY_STATE_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xA34)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    bbp_comm_dbgʹ���źţ�
             1��ʹ�ܣ�
             0����ʹ�ܡ�
   UNION�ṹ:  BBPCOMM_DBG_COMM_EN_UNION */
#define BBPCOMM_DBG_COMM_EN_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0xA38)

/* �Ĵ���˵����WΪ��ģʱ��Ӧͨ����ָʾ�Ĵ���
 bit[31:3]   ����
 bit[2:2]    WΪ��ģʱ��Ӧ��ͨ��ѡ���ź���Ч��ʽ��
             0����int1��Ч��
             1��������Ч��
 bit[1:0]    WΪ��ģʱ��Ӧ��ͨ��ѡ���źš�
             0��ѡ��ͨ��0��
             1��ѡ��ͨ��1��
             2��ѡ��ͨ��2��
             ����ʱ�̣���ģ����ͨ�ų�������
   UNION�ṹ:  BBPCOMM_S_W_CH_NUM_IND_UNION */
#define BBPCOMM_S_W_CH_NUM_IND_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0xA40)

/* �Ĵ���˵����LTEΪ��ģʱ��Ӧͨ����ָʾ�Ĵ���
 bit[31:2]   ����
 bit[1:1]    LTEΪ��ģʱ��Ӧ��ͨ��ѡ���ź���Ч��ʽ��
             0����int1��Ч��
             1��������Ч��
 bit[0:0]    LTEΪ��ģʱ��Ӧ��ͨ��ѡ���źš�
             0��ѡ��ͨ��0��
             1��ѡ��ͨ��1��
             ����ʱ�̣���ģ����ͨ�ų�������
   UNION�ṹ:  BBPCOMM_S_LTE_CH_NUM_IND_UNION */
#define BBPCOMM_S_LTE_CH_NUM_IND_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xA44)

/* �Ĵ���˵����TDSΪ��ģʱ��Ӧͨ����ָʾ�Ĵ���
 bit[31:2]   ����
 bit[1:1]    TDSΪ��ģʱ��Ӧ��ͨ��ѡ���ź���Ч��ʽ��
             0����int1��Ч��
             1��������Ч��
 bit[0:0]    TDSΪ��ģʱ��Ӧ��ͨ��ѡ���źš�
             0��ѡ��ͨ��0��
             1��ѡ��ͨ��1��
             ����ʱ�̣���ģ����ͨ�ų�������
   UNION�ṹ:  BBPCOMM_S_TDS_CH_NUM_IND_UNION */
#define BBPCOMM_S_TDS_CH_NUM_IND_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xA48)

/* �Ĵ���˵����GMΪ��ģʱ��Ӧͨ����ָʾ�Ĵ���
 bit[31:3]   ����
 bit[2:2]    GMΪ��ģʱ��Ӧ��ͨ��ѡ���ź���Ч��ʽ��
             0����int1��Ч��
             1��������Ч��
 bit[1:0]    GMΪ��ģʱ��Ӧ��ͨ��ѡ���źš�
             0��ѡ��ͨ��0��
             1��ѡ��ͨ��1��
             2��ѡ��ͨ��2��
             ����ʱ�̣���ģ����ͨ�ų�������
   UNION�ṹ:  BBPCOMM_S_GM_CH_NUM_IND_UNION */
#define BBPCOMM_S_GM_CH_NUM_IND_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xA4C)

/* �Ĵ���˵����GSΪ��ģʱ��Ӧͨ����ָʾ�Ĵ���
 bit[31:3]   ����
 bit[2:2]    GSΪ��ģʱ��Ӧ��ͨ��ѡ���ź���Ч��ʽ��
             0����int1��Ч��
             1��������Ч��
 bit[1:0]    GSΪ��ģʱ��Ӧ��ͨ��ѡ���źš�
             0��ѡ��ͨ��0��
             1��ѡ��ͨ��1��
             2��ѡ��ͨ��2��
             ����ʱ�̣���ģ����ͨ�ų�������
   UNION�ṹ:  BBPCOMM_S_GS_CH_NUM_IND_UNION */
#define BBPCOMM_S_GS_CH_NUM_IND_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xA50)

/* �Ĵ���˵����
 bit[31:6]   ����
 bit[5]      apt����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
 bit[4]      pmu����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
 bit[3]      abb rx����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
 bit[2]      abb tx����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
 bit[1]      mipi����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
 bit[0]      rf����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
   UNION�ṹ:  BBPCOMM_L_CH_SW_UNION */
#define BBPCOMM_L_CH_SW_ADDR                          (SOC_BBP_COMM_BASE_ADDR + 0xB00)

/* �Ĵ���˵����
 bit[31:6]   ����
 bit[5]      apt����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
 bit[4]      pmu����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
 bit[3]      abb rx����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
 bit[2]      abb tx����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
 bit[1]      mipi����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
 bit[0]      rf����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
   UNION�ṹ:  BBPCOMM_W_CH_SW_UNION */
#define BBPCOMM_W_CH_SW_ADDR                          (SOC_BBP_COMM_BASE_ADDR + 0xB04)

/* �Ĵ���˵����
 bit[31:6]   ����
 bit[5]      apt����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
 bit[4]      pmu����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
 bit[3]      abb rx����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
 bit[2]      abb tx����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
 bit[1]      mipi����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
 bit[0]      rf����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
   UNION�ṹ:  BBPCOMM_T_CH_SW_UNION */
#define BBPCOMM_T_CH_SW_ADDR                          (SOC_BBP_COMM_BASE_ADDR + 0xB08)

/* �Ĵ���˵����
 bit[31:6]   ����
 bit[5]      apt����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
 bit[4]      pmu����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
 bit[3]      abb rx����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
 bit[2]      abb tx����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
 bit[1]      mipi����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
 bit[0]      rf����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
   UNION�ṹ:  BBPCOMM_GM_CH_SW_UNION */
#define BBPCOMM_GM_CH_SW_ADDR                         (SOC_BBP_COMM_BASE_ADDR + 0xB0C)

/* �Ĵ���˵����
 bit[31:6]   ����
 bit[5]      apt����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
 bit[4]      pmu����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
 bit[3]      abb rx����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
 bit[2]      abb tx����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
 bit[1]      mipi����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
 bit[0]      rf����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
   UNION�ṹ:  BBPCOMM_GS_CH_SW_UNION */
#define BBPCOMM_GS_CH_SW_ADDR                         (SOC_BBP_COMM_BASE_ADDR + 0xB10)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      lteģ�����ͨ��0��tcvr_on�ź���Դ��
             1'b0��������lte bbp
             1'b1��������dsp����ֵ
   UNION�ṹ:  BBPCOMM_L_TCVR_SEL0_UNION */
#define BBPCOMM_L_TCVR_SEL0_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0xB20)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      lteģ�����ͨ��1��tcvr_on�ź���Դ��
             1'b0��������lte bbp
             1'b1��������dsp����ֵ
   UNION�ṹ:  BBPCOMM_L_TCVR_SEL1_UNION */
#define BBPCOMM_L_TCVR_SEL1_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0xB24)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      tdsģ�����ͨ��0��tcvr_on�ź���Դ��
             1'b0��������tds bbp
             1'b1��������dsp����ֵ
   UNION�ṹ:  BBPCOMM_T_TCVR_SEL0_UNION */
#define BBPCOMM_T_TCVR_SEL0_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0xB28)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      tdsģ�����ͨ��1��tcvr_on�ź���Դ��
             1'b0��������tds bbp
             1'b1��������dsp����ֵ
   UNION�ṹ:  BBPCOMM_T_TCVR_SEL1_UNION */
#define BBPCOMM_T_TCVR_SEL1_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0xB2C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      wcdmaģ�����ͨ��0��tcvr_on�ź���Դ��
             1'b0��������wcdma bbp
             1'b1��������dsp����ֵ
   UNION�ṹ:  BBPCOMM_W_TCVR_SEL0_UNION */
#define BBPCOMM_W_TCVR_SEL0_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0xB30)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      wcdmaģ�����ͨ��1��tcvr_on�ź���Դ����
             1'b0��������wcdma bbp
             1'b1��������dsp����ֵ
   UNION�ṹ:  BBPCOMM_W_TCVR_SEL1_UNION */
#define BBPCOMM_W_TCVR_SEL1_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0xB34)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      gsm��m�������ͨ��0��tcvr_on�ź���Դ��
             1'b0��������gsm��m�� bbp
             1'b1��������dsp����ֵ
   UNION�ṹ:  BBPCOMM_GM_TCVR_SEL0_UNION */
#define BBPCOMM_GM_TCVR_SEL0_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0xB38)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      gsm��m�������ͨ��1��tcvr_on�ź���Դ��
             1'b0��������gsm��m�� bbp
             1'b1��������dsp����ֵ
   UNION�ṹ:  BBPCOMM_GM_TCVR_SEL1_UNION */
#define BBPCOMM_GM_TCVR_SEL1_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0xB3C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      gsm��s�������ͨ��0��tcvr_on�ź���Դ��
             1'b0��������gsm��s�� bbp
             1'b1��������dsp����ֵ
   UNION�ṹ:  BBPCOMM_GS_TCVR_SEL0_UNION */
#define BBPCOMM_GS_TCVR_SEL0_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0xB40)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      gsm��s�������ͨ��1��tcvr_on�ź���Դ��
             1'b0��������gsm��s�� bbp
             1'b1��������dsp����ֵ
   UNION�ṹ:  BBPCOMM_GS_TCVR_SEL1_UNION */
#define BBPCOMM_GS_TCVR_SEL1_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0xB44)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      dsp���õ�lteģ�͸�ͨ��0 ��tcvr_onֵ
             
   UNION�ṹ:  BBPCOMM_L_TCVR_VALUE0_UNION */
#define BBPCOMM_L_TCVR_VALUE0_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xB48)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      dsp���õ�lteģ�͸�ͨ��1 ��tcvr_onֵ
             
   UNION�ṹ:  BBPCOMM_L_TCVR_VALUE1_UNION */
#define BBPCOMM_L_TCVR_VALUE1_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xB4C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      dsp���õ�tdsģ�͸�ͨ��0 ��tcvr_onֵ
             
   UNION�ṹ:  BBPCOMM_T_TCVR_VALUE0_UNION */
#define BBPCOMM_T_TCVR_VALUE0_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xB50)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      dsp���õ�tdsģ�͸�ͨ��1 ��tcvr_onֵ
             
   UNION�ṹ:  BBPCOMM_T_TCVR_VALUE1_UNION */
#define BBPCOMM_T_TCVR_VALUE1_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xB54)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      dsp���õ�wcdmaģ�͸�ͨ��0 ��tcvr_onֵ
             
   UNION�ṹ:  BBPCOMM_W_TCVR_VALUE0_UNION */
#define BBPCOMM_W_TCVR_VALUE0_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xB58)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      dsp���õ�wcdmaģ�͸�ͨ��1 ��tcvr_onֵ
             
   UNION�ṹ:  BBPCOMM_W_TCVR_VALUE1_UNION */
#define BBPCOMM_W_TCVR_VALUE1_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xB5C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      dsp���õ�gsm��m��ģ�͸�ͨ��0 ��tcvr_onֵ
             
   UNION�ṹ:  BBPCOMM_GM_TCVR_VALUE0_UNION */
#define BBPCOMM_GM_TCVR_VALUE0_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0xB60)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      dsp���õ�gsm��m��ģ�͸�ͨ��1��tcvr_onֵ
             
   UNION�ṹ:  BBPCOMM_GM_TCVR_VALUE1_UNION */
#define BBPCOMM_GM_TCVR_VALUE1_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0xB64)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      dsp���õ�gsm��s��ģ�͸�ͨ��0 ��tcvr_onֵ
             
   UNION�ṹ:  BBPCOMM_GS_TCVR_VALUE0_UNION */
#define BBPCOMM_GS_TCVR_VALUE0_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0xB68)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      dsp���õ�gsm��s��ģ�͸�ͨ��1 ��tcvr_onֵ
             
   UNION�ṹ:  BBPCOMM_GS_TCVR_VALUE1_UNION */
#define BBPCOMM_GS_TCVR_VALUE1_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0xB6C)

/* �Ĵ���˵����
 bit[31:19]  ����
 bit[18]     ͨ��2 ���������tcvr_on�ź�״̬
             
 bit[17]     ͨ��1 ���������tcvr_on�ź�״̬
             
 bit[16]     ͨ��0 ���������tcvr_on�ź�״̬
             
 bit[15:11]  ����
 bit[10]     c bbp�����ͨ��0 tcvr_on�ź�״̬
             
 bit[9]      ����
 bit[8]      gsm��s�� bbp�����ͨ��0 tcvr_on�ź�״̬
             
 bit[7]      ����
 bit[6]      gsm��m�� bbp�����ͨ��0 tcvr_on�ź�״̬
             
 bit[5]      ����
 bit[4]      wcdma bbp�����ͨ��0 tcvr_on�ź�״̬
             
 bit[3]      ����
 bit[2]      tds bbp�����ͨ��0 tcvr_on�ź�״̬
             
 bit[1]      lte bbp�����ͨ��1 tcvr_on�ź�״̬
             
 bit[0]      lte bbp�����ͨ��0 tcvr_on�ź�״̬
             
   UNION�ṹ:  BBPCOMM_RF_TCVR_STATE_UNION */
#define BBPCOMM_RF_TCVR_STATE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xB70)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      mipiͨ������ʹ�ܣ�
             1'b0��ͨ����
             1'b1��ͨ������
   UNION�ṹ:  BBPCOMM_MIPI_UNBIND_EN_UNION */
#define BBPCOMM_MIPI_UNBIND_EN_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0xB90)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ͨ��0ӳ��mipi������ϵ��
             1'b0��ͨ��0ӳ�䵽mipi0
             1'b1��ͨ��0ӳ�䵽mipi1
   UNION�ṹ:  BBPCOMM_MIPI_CH_SEL0_UNION */
#define BBPCOMM_MIPI_CH_SEL0_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0xB94)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ͨ��1ӳ��mipi������ϵ��
             1'b0��ͨ��1ӳ�䵽mipi0
             1'b1��ͨ��1ӳ�䵽mipi1
   UNION�ṹ:  BBPCOMM_MIPI_CH_SEL1_UNION */
#define BBPCOMM_MIPI_CH_SEL1_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0xB98)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    apt_pdm0/apt_vpen0�ź���Դ��
             2'd0��������ͨ��0
             2'd1��������ͨ��1
             2'd2��������ͨ��2
             2'd3��ǿ�Ƶ͵�ƽ���
   UNION�ṹ:  BBPCOMM_APT_CH_SEL0_UNION */
#define BBPCOMM_APT_CH_SEL0_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0xB9C)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    apt_pdm1/apt_vpen1�ź���Դ��
             2'd0��������ͨ��0
             2'd1��������ͨ��1
             2'd2��������ͨ��2
             2'd3��ǿ�Ƶ͵�ƽ���
   UNION�ṹ:  BBPCOMM_APT_CH_SEL1_UNION */
#define BBPCOMM_APT_CH_SEL1_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0xBA0)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    afc pdm0�ź���Դ��
             2'd0��������ͨ��0
             2'd1��������ͨ��1
             2'd2��������ͨ��2
             2'd3��ǿ�Ƶ͵�ƽ���
   UNION�ṹ:  BBPCOMM_AFC_CH_SEL0_UNION */
#define BBPCOMM_AFC_CH_SEL0_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0xBA4)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    afc pdm1�ź���Դ��
             2'd0��������ͨ��0
             2'd1��������ͨ��1
             2'd2��������ͨ��2
             2'd3��ǿ�Ƶ͵�ƽ���
   UNION�ṹ:  BBPCOMM_AFC_CH_SEL1_UNION */
#define BBPCOMM_AFC_CH_SEL1_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0xBA8)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ����
   UNION�ṹ:  BBPCOMM_ABB_TX_CH_SEL0_UNION */
#define BBPCOMM_ABB_TX_CH_SEL0_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0xBAC)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ����
   UNION�ṹ:  BBPCOMM_ABB_TX_CH_SEL1_UNION */
#define BBPCOMM_ABB_TX_CH_SEL1_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0xBB0)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    auxdac0�ź���Դ��
             2'd0��������ͨ��0
             2'd1��������ͨ��1
             2'd2��������ͨ��2
             2'd3��ǿ�Ƶ͵�ƽ���
   UNION�ṹ:  BBPCOMM_PMU_CH_SEL0_UNION */
#define BBPCOMM_PMU_CH_SEL0_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0xBB4)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    auxdac1�ź���Դ��
             2'd0��������ͨ��0
             2'd1��������ͨ��1
             2'd2��������ͨ��2
             2'd3��ǿ�Ƶ͵�ƽ���
   UNION�ṹ:  BBPCOMM_PMU_CH_SEL1_UNION */
#define BBPCOMM_PMU_CH_SEL1_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0xBB8)

/* �Ĵ���˵����
 bit[31:16]  ����
 bit[15:0]   ����
   UNION�ṹ:  BBPCOMM_VALID_NUM_UNION */
#define BBPCOMM_VALID_NUM_ADDR                        (SOC_BBP_COMM_BASE_ADDR + 0xBC0)

/* �Ĵ���˵����
 bit[31:16]  ����
 bit[15:0]   ����
   UNION�ṹ:  BBPCOMM_VALID_NUM1_UNION */
#define BBPCOMM_VALID_NUM1_ADDR                       (SOC_BBP_COMM_BASE_ADDR + 0xBC4)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_LTE_RCV_C[15:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_LTE_RCV_C_UNION */
#define BBPCOMM_INT_CLEAR_LTE_RCV_C_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC00)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж����α�־����������INT_TYPE_LTE_RCV_C[15:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_LTE_RCV_C_UNION */
#define BBPCOMM_INT_MASK_LTE_RCV_C_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC04)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
             [0]: �ж�����0�� C����ģ����ǰ֪ͨLTE��ϵͳ���������жϡ�
             [1]: �ж�����1�� C����ģ����GAP�жϣ�֪ͨLTE������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
             [2]: �ж�����2��C����ģ����GAP�жϡ�
             [3]: �ж�����3��C����ģ�����������жϡ�
             [4]: �ж�����4��C����ģ��ǿ��C�˳���ϵͳ�����жϡ�
             [5]: �ж�����5��C����ģ��֪ͨC�ϱ����β��������
             [6]: ������
             [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x0A84��int_mask_lte_rcv_c���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_LTE_RCV_C_UNION */
#define BBPCOMM_INT_TYPE_LTE_RCV_C_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC08)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:3]   �߼������㡣����Ч��
             
             bit15~7����Ӧlte_snd_c_int_15 ~ 7��
             LPHYͨ���˼Ĵ�����������15~7�жϣ�int_type_c_rcv_lte[15:7]����CPHY��
             ��Чʱ�̣�������Ч
             
             bit6����Ӧlte_snd_c_int_6��
             LPHYͨ���˼Ĵ�����������6�жϣ�int_type_lte_rcv_c[6]����LPHY��
             ��Чʱ�̣�������Ч
             
             bit5����Ӧc_snd_lte_int_5��
             L��ģʱ֪ͨLPHY L�������ڵ������Ч��
             LPHYͨ���˼Ĵ�����������5�жϣ�int_type_c_rcv_lte[5]����LPHY��
             ��Чʱ�̣�������Ч
             
             bit4����Ӧlte_snd_c_int_4��
             L��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
             LPHYͨ���˼Ĵ�����������4�жϣ�int_type_c_rcv_lte[4]����CPHY��
             ��Чʱ�̣�������Ч
             
             bit3����Ӧlte_snd_c_int_3��L��������ָʾ������Ч��
             ���ڴ����ж�����3 ��int_type_c_rcv_lte[3]����CPHY��C��ģ�¶�L������ϵͳ����ʱ�����L����������LPHY���ô˱�־Ϊ1�� 
             ��Чʱ�̣�������Ч
 bit[2:0]    ����
   UNION�ṹ:  BBPCOMM_LTE_SND_C_INT_13_UNION */
#define BBPCOMM_LTE_SND_C_INT_13_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xC0C)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:3]   �߼������㡣����Ч��
             
             bit15~7����Ӧc_snd_c_int_15 ~ 7��
             C DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_c_rcv_c[15:7]����C DSP��
             ��Чʱ�̣�������Ч
             
             bit6����Ӧc_snd_c_int_6��
             CDSPͨ���˼Ĵ�����������6�жϣ�int_type_c_rcv_c[6]����CDSP��
             ��Чʱ�̣�������Ч
             
             bit5����Ӧc_snd_c_int_5��
             C��ģʱ֪ͨCDSP C�������ڵ������Ч��
             C DSPͨ���˼Ĵ�����������5�жϣ�int_type_c_rcv_c[5]����CDSP��
             ��Чʱ�̣�������Ч
             
             bit4����Ӧc_snd_c_int_4��
             C��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
             C DSPͨ���˼Ĵ�����������4�жϣ�int_type_c_rcv_c[4]����CDSP��
             ��Чʱ�̣�������Ч
             
             bit3����Ӧc_snd_c_int_3��C��������ָʾ������Ч��
             ���ڴ����ж�����3 ��int_type_c_rcv_c[3]����CDSP��C��ģ�¶�C������ϵͳ����ʱ�����C����������C DSP���ô˱�־Ϊ1�� 
             ��Чʱ�̣�������Ч
 bit[2:0]    ����
   UNION�ṹ:  BBPCOMM_C_SND_C_INT_13_UNION */
#define BBPCOMM_C_SND_C_INT_13_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0xC10)

/* �Ĵ���˵�����Ĵ���
 bit[31:2]   ����
 bit[1:0]    ��ƽ�źţ�����Ч��
             ��C��ģ��Ҫ����ϵͳ����ʱ�����ñ��Ĵ���Ϊ3����ϵͳ�������������ñ��Ĵ���Ϊ0��
             bit1:1��b0:
              ��c_intrasys_valid������Ч����ǿ��Ϊ1��
             bit0:1��b0:
             c_intersys_ingap_pre_ind������Ч����ǿ��Ϊ0��
             bit[1:0] = 11b: ��c_intrasys_valid��c_intersys_ingap_pre_ind������Ч��
             ����ʱ�̣�TDS��ģ��Ҫ����ϵͳ����ʱ�����ñ��Ĵ���Ϊ3����ϵͳ�������������ñ��Ĵ���Ϊ0��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_CBBP_INPUT_MASK_UNION */
#define BBPCOMM_CBBP_INPUT_MASK_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xC14)

/* �Ĵ���˵�����Ĵ���
   ��      ����W/TD/GM/L/GSΪ��ģʱд�˼Ĵ�����GSΪ��ģʱ��ȡ�˼Ĵ������˼Ĵ�����DSP֮����ж�д��BBP���ṩ�ӿڡ�
   UNION�ṹ ���� */
#define BBPCOMM_MEAS_FLAG_C_RD_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0xC18)

/* �Ĵ���˵�����Ĵ���
   ��      ����CΪ��ģʱд�˼Ĵ�����W/TD/GM/L/GS��ģ��ȡ�˼Ĵ������˼Ĵ�����DSP֮����ж�д��BBP���ṩ�ӿڡ�
   UNION�ṹ ���� */
#define BBPCOMM_WAKE_FLAG_C_WR_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0xC1C)

/* �Ĵ���˵�����Ĵ���
 bit[31:30]  ����
 bit[29:0]   Cģ��ʱ��Ϣ�ϱ��� 
   UNION�ṹ:  BBPCOMM_C_TIMING_DSP_UNION */
#define BBPCOMM_C_TIMING_DSP_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0xC20)

/* �Ĵ���˵�����Ĵ���
 bit[31:2]   ����
 bit[1]      C��ģ��ʵ�ʿ���RFָʾ����ƽ�źš�Ϊ1����W����RF����ͨ����Ϊ0�����ģ���Կ���RFͨ�������ڵ�RFICʱ��Ƶ��������źŵ�ѡͨ��
             c_intrasys_valid_delay�������ر�c_intrasys_valid�������ͺ��½���һ�¡�
 bit[0]      C��ģ�¿���RFָʾ����ƽ�źš�
             1��b0: C����RF����Ȩ��
             1��b1: C���п���RFȨ����ʵ������RF��c_intrasys_valid_delay�ź�Ϊ1����
   UNION�ṹ:  BBPCOMM_C_INTRASYS_VALID_UNION */
#define BBPCOMM_C_INTRASYS_VALID_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xC24)

/* �Ĵ���˵�����Ĵ���
 bit[31:4]   ����
 bit[3:0]    ��ϵͳ�������͡�
             4��b0������C��
             4��b1: C�����ѣ�
             ����Ԥ����
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_C_INTERSYS_MEASURE_TYPE_UNION */
#define BBPCOMM_C_INTERSYS_MEASURE_TYPE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC28)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    ��Ƶ��������ڵ�ָʾ��L����TDS/Gm/Gs/U��Ϊ��ģ��֪ͨCPHY W�����ĵ�Ƶ�����ڵ��
             ֻ������̬����Ҫ���á�
             ��ƽ�źţ�����Ч��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_C_MEASURE_REPORT_VALID_UNION */
#define BBPCOMM_C_MEASURE_REPORT_VALID_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC2C)

/* �Ĵ���˵�����Ĵ���
   ��      ����Ԥ�����ж�int0��int1֮���offset��Ϣ����λus������ȡ��������
               ����ʱ�̣���ģ����C��ģ��ϵͳ����ʱ����
               ��Чʱ�̣�������Ч
   UNION�ṹ ���� */
#define BBPCOMM_C_PREINT_OFFSET_TIME_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xC30)

/* �Ĵ���˵�����Ĵ���
   ��      ����C��Ϊ��ģʱ����ģ�����C������ϵͳ����ʱ�䳤�ȣ���֪CPHY����λus������ȡ����us��
               ����ʱ�̣���ģ����C��ģ��ϵͳ����ʱ����
               ��Чʱ�̣�������Ч
   UNION�ṹ ���� */
#define BBPCOMM_C_INTERSYS_MEASURE_TIME_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC34)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_C_RCV_LTE[15:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_C_RCV_LTE_UNION */
#define BBPCOMM_INT_CLEAR_C_RCV_LTE_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC38)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_C_RCV_C[15:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_C_RCV_C_UNION */
#define BBPCOMM_INT_CLEAR_C_RCV_C_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xC3C)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    �߼������㡣
             �жϱ�־���ָʾ������Ч���������INT_TYPE_C_INT012[2:0]��Ӧbitλ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_CLEAR_C_INT012_UNION */
#define BBPCOMM_INT_CLEAR_C_INT012_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC40)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж����α�־����������INT_TYPE_C_RCV_LTE[15:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_C_RCV_LTE_UNION */
#define BBPCOMM_INT_MASK_C_RCV_LTE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC44)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж����α�־����������INT_TYPE_C_RCV_C[15:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_C_RCV_C_UNION */
#define BBPCOMM_INT_MASK_C_RCV_C_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xC48)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    �ж����α�־����������INT_TYPE_C_INT012[2:0]��Ӧbit�жϡ�
             0�������ж��ϱ���
             1��ʹ���ж��ϱ���
             ����ʱ�̣���ʼ��
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_INT_MASK_C_INT012_UNION */
#define BBPCOMM_INT_MASK_C_INT012_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xC4C)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
             [0]: �ж�����0�� LTE����ģ����ǰ֪ͨC��ϵͳ���������жϡ�
             [1]: �ж�����1�� LTE����ģ����GAP�жϣ�֪ͨC������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
             [2]: �ж�����2�� LTE����ģ����GAP�жϡ�
             [3]: �ж�����3��LTE����ģ�����������жϡ�
             [4]: �ж�����4��LTE����ģ��ǿ��C�˳���ϵͳ�����жϡ�
             [5]: �ж�����5��LTE����ģ��֪ͨC�ϱ����β��������
             [6]: ������
             [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x0B34��int_mask_c_rcv_lte���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_C_RCV_LTE_UNION */
#define BBPCOMM_INT_TYPE_C_RCV_LTE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC50)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
             [0]: �ж�����0��C����ģ����ǰ֪ͨLTE��Ƶ���������жϡ�
             [1]: �ж�����1��C����ģ����GAP�жϣ�֪ͨC������Ƶ������Ƶͨ�����ã������л��Ȳ�����
             [2]: �ж�����2��C����ģ����GAP�жϡ�
             [3]: �ж�����3��C����ģ������Ƶ�����������жϡ�
             [4]: �ж�����4��C����ģ��ǿ��C�˳���Ƶ�����жϡ�
             [5]: �ж�����5��C����ģ��֪ͨC�ϱ����β��������
             [6]: �ж�����6��������
             [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
             �ж�״̬��־0��1��2ֻ�е�LTE������ģʱ���ܲ�����
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x0B38��int_mask_c_rcv_c���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_C_RCV_C_UNION */
#define BBPCOMM_INT_TYPE_C_RCV_C_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xC54)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    ������ģ����int0��1��2���ϱ���(������Ƶ����ϵͳ����)��������Ч��
             [0]: C��ģʱ��CTU����֪ͨCPHY����int0�жϡ�
             [1]: C��ģʱ��CTU����֪ͨCPHY����int1�жϡ�
             [2]:CW��ģʱ��CTU����֪ͨCPHY����int2�жϡ�
             �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x0704��int_mask_c_int012���룬���ж��Ƿ���Ҫ����
   UNION�ṹ:  BBPCOMM_INT_TYPE_C_INT012_UNION */
#define BBPCOMM_INT_TYPE_C_INT012_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xC58)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:3]   �߼������㡣����Ч��
             
             bit15~7����Ӧc_snd_lte_int_15 ~ 7��
             CPHYͨ���˼Ĵ�����������15~7�жϣ�int_type_lte_rcv_c[15:7]����LPHY��
             ��Чʱ�̣�������Ч
             
             bit6����Ӧc_snd_lte_int_6��
             CPHYͨ���˼Ĵ�����������6�жϣ�int_type_lte_rcv_c[6]����LPHY��
             ��Чʱ�̣�������Ч
             
             bit5����Ӧc_snd_lte_int_5��
             C��ģʱ֪ͨCPHY L�������ڵ������Ч��
             CPHYͨ���˼Ĵ�����������5�жϣ�int_type_lte_rcv_c[5]����CPHY��
             ��Чʱ�̣�������Ч
             
             bit4����Ӧc_snd_lte_int_4��
             C��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
             CPHYͨ���˼Ĵ�����������4�жϣ�int_type_lte_rcv_c[4]����LPHY��
             ��Чʱ�̣�������Ч
             
             bit3����Ӧc_snd_lte_int_3��C��������ָʾ������Ч��
             ���ڴ����ж�����3 ��int_type_lte_rcv_c[3]����LPHY��L��ģ�¶�C������ϵͳ����ʱ�����C����������CPHY���ô˱�־Ϊ1�� 
             ��Чʱ�̣�������Ч
 bit[2:0]    ����
   UNION�ṹ:  BBPCOMM_C_SND_LTE_INT_13_UNION */
#define BBPCOMM_C_SND_LTE_INT_13_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xC5C)

/* �Ĵ���˵�����Ĵ���
 bit[31:10]  ����
 bit[9:9]    1'b1��C��TXͨ·I·����ȡ��
             1'b0��C��TXͨ·I·���ݲ�ȡ��
 bit[8:8]    1'b1��C��TXͨ·Q·����ȡ��
             1'b0��C��TXͨ·Q·���ݲ�ȡ��
 bit[7:7]    1'b1��C��TXͨ·IQ·���ݽ���
             1'b0��C��TXͨ·IQ·���ݲ�����
             V3R3��֧��IQ�������ܡ�
 bit[6:6]    1'b1��C��RXAͨ·I·����ȡ��
             1'b0��C��RXAͨ·I·���ݲ�ȡ��
 bit[5:5]    1'b1��C��RXAͨ·Q·����ȡ��
             1'b0��C��RXAͨ·Q·���ݲ�ȡ��
 bit[4:4]    1'b1��C��RXAͨ·IQ·���ݽ���
             1'b0��C��RXAͨ·IQ·���ݲ�����
             V3R3��֧��IQ�������ܡ�
 bit[3:3]    1'b1��C��RXBͨ·I·����ȡ��
             1'b0��C��RXBͨ·I·���ݲ�ȡ��
 bit[2:2]    1'b1��C��RXBͨ·Q·����ȡ��
             1'b0��C��RXBͨ·Q·���ݲ�ȡ��
 bit[1:1]    1'b1��C��RXBͨ·IQ·���ݽ���
             1'b0��C��RXBͨ·IQ·���ݲ�����
             V3R3��֧��IQ�������ܡ�
 bit[0:0]    ����
   UNION�ṹ:  BBPCOMM_C_ABBIF_FMT_UNION */
#define BBPCOMM_C_ABBIF_FMT_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0xC60)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      1'b0��TDS CTU�ж����������㣻
             1'b1��C CTU�ж����������㡣
   UNION�ṹ:  BBPCOMM_TDS_C_CTU_INT_SEL_UNION */
#define BBPCOMM_TDS_C_CTU_INT_SEL_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xC64)

/* �Ĵ���˵����CΪ��ģʱ��Ӧͨ����ָʾ�Ĵ���
 bit[31:3]   ����
 bit[2:2]    CΪ��ģʱ��Ӧ��ͨ��ѡ���ź���Ч��ʽ��
             0����int1��Ч��
             1��������Ч��
 bit[1:0]    CΪ��ģʱ��Ӧ��ͨ��ѡ���źš�
             0��ѡ��ͨ��0��
             1��ѡ��ͨ��1��
             2��ѡ��ͨ��2��
             ����ʱ�̣���ģ����ͨ�ų�������
   UNION�ṹ:  BBPCOMM_S_C_CH_NUM_IND_UNION */
#define BBPCOMM_S_C_CH_NUM_IND_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0xC68)

/* �Ĵ���˵����
 bit[31:6]   ����
 bit[5]      apt����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
 bit[4]      pmu����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
 bit[3]      abb rx����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
 bit[2]      abb tx����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
 bit[1]      mipi����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
 bit[0]      rf����ź��Ƿ񽻻���
             1'b0��0/1ͨ��������
             1'b1��0/1ͨ������
   UNION�ṹ:  BBPCOMM_C_CH_SW_UNION */
#define BBPCOMM_C_CH_SW_ADDR                          (SOC_BBP_COMM_BASE_ADDR + 0xC6C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      C�����ͨ��0��tcvr_on�ź���Դ��
             1'b0��������c bbp
             1'b1��������dsp����ֵ
   UNION�ṹ:  BBPCOMM_C_TCVR_SEL0_UNION */
#define BBPCOMM_C_TCVR_SEL0_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0xC70)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      C�����ͨ��1��tcvr_on�ź���Դ��
             1'b0��������c bbp
             1'b1��������dsp����ֵ
   UNION�ṹ:  BBPCOMM_C_TCVR_SEL1_UNION */
#define BBPCOMM_C_TCVR_SEL1_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0xC74)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      dsp���õ�cģ�͸�ͨ��0 ��tcvr_onֵ
             
   UNION�ṹ:  BBPCOMM_C_TCVR_VALUE0_UNION */
#define BBPCOMM_C_TCVR_VALUE0_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xC78)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      dsp���õ�cģ�͸�ͨ��1 ��tcvr_onֵ
             
   UNION�ṹ:  BBPCOMM_C_TCVR_VALUE1_UNION */
#define BBPCOMM_C_TCVR_VALUE1_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xC7C)

/* �Ĵ���˵�����Ĵ���
   ��      ����32K������ʱ���Ķ�ʱ��Ϣ����DSP ����timing_get_ind�����ϱ���
               
               �ϱ�ʱ�̣�comm_32k_timing_validΪ��ʱ�ϱ���Ч
   UNION�ṹ ���� */
#define BBPCOMM_COMM_32K_TIMING_RPT1_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xF00)

/* �Ĵ���˵�����Ĵ���
 bit[31:24]  ����
 bit[23:0]   32KУ׼��ʱ���Ķ�ʱ��Ϣ����DSP ����timing_get_ind�����ϱ���
             ������
             �ϱ�ʱ�̣�comm_32k_timing_validΪ��ʱ�ϱ���Ч
   UNION�ṹ:  BBPCOMM_COMM_32K_TIMING_RPT2_UNION */
#define BBPCOMM_COMM_32K_TIMING_RPT2_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xF04)

/* �Ĵ���˵�����Ĵ���
 bit[31:17]  ����
 bit[16]     ABB CH0 RXBͨ����CH1 RXBͨ����������ʹ���źţ�1��ʾ��Ч
 bit[15:0]   ABB CH0 RXB��CH1 RXBͨ�������ӳټ���ֵ����ͨ���л��Ļ���ʱ�䣬��������Ϊ����ʱ�ӣ�150M��������ֵ������ڵ���1��
   UNION�ṹ:  BBPCOMM_ABB_RXB_LOCK_MODE_UNION */
#define BBPCOMM_ABB_RXB_LOCK_MODE_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xF08)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ��ά�ɲ�İ�����
 bit[15:2]   ����
 bit[1]      ��ά�ɲ������ϱ�ģʽ��
             'b0���������������dbg_pkg_num�����ݰ����Զ�������
             'b1��ֻҪdbg_enΪ1���ϱ���û���ϱ��������ơ�
 bit[0]      ��ά�ɲ�ʹ���źţ���dbg_rpt_modeΪ0ʱ�߼����壬������Ҫд�塣
             1'b0����ά�ɲ⹦�ܲ�ʹ��                           
             1'b1����ά�ɲ⹦��ʹ��
   UNION�ṹ:  BBPCOMM_DBG_EN_UNION */
#define BBPCOMM_DBG_EN_ADDR                           (SOC_BBP_COMM_BASE_ADDR + 0xF80)

/* �Ĵ���˵�����Ĵ���
   ��      ������ά�ɲ��ϱ����ݰ�ID�Ż�ַ
   UNION�ṹ ���� */
#define BBPCOMM_DBG_ID_ADDR                           (SOC_BBP_COMM_BASE_ADDR + 0xF84)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   ��ά�ɲ��ڲ�����ָʾ��
             1���ϱ�mipi����
             2���ϱ�ssi����
             3������dbg�ϱ�����
             ����������
   UNION�ṹ:  BBPCOMM_DBG_FLT_UNION */
#define BBPCOMM_DBG_FLT_ADDR                          (SOC_BBP_COMM_BASE_ADDR + 0xF88)

/* �Ĵ���˵�����Ĵ���
 bit[31:25]  ����
 bit[24:0]   ��ά�ɲ���ѯ�����ϱ��ź�ʹ�ܣ�dbg_req_en[24:0]��Ӧreg[24:0],��dbg_req_en[24]Ϊ1��reg[24]������Ч��dbg_req_en[24]Ϊ0��reg[24]������Ч
   UNION�ṹ:  BBPCOMM_DBG_REQ_EN_UNION */
#define BBPCOMM_DBG_REQ_EN_ADDR                       (SOC_BBP_COMM_BASE_ADDR + 0xF8C)

/* �Ĵ���˵�����Ĵ���
 bit[31:2]   ����
 bit[1]      MIPI��ѯ���������źţ�1����������źţ�0����Ч
 bit[0]      MIPIͨ����̬�л�ʹ�ܣ�1����̬�л�������0����̬�л��ر�
   UNION�ṹ:  BBPCOMM_MIPI_DYN_EXCHG_UNION */
#define BBPCOMM_MIPI_DYN_EXCHG_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0xF90)

/* �Ĵ���˵�����Ĵ���
 bit[31:16]  ����
 bit[15:0]   dsp��ȡ��ʱ��Ϣ��ʱ����ʱ�䣬Ĭ��Ϊ0x4b00��1ms��
   UNION�ṹ:  BBPCOMM_TIMING_CLR_DELAY_CNT_UNION */
#define BBPCOMM_TIMING_CLR_DELAY_CNT_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xF94)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      ��ʱ��Ϣ�ϱ�ģʽѡ��timing_get_mode��Ч��dsp���ƣ�bbe16��arm��Ϊһ�׽ӿڻ�ȡ��ʱ��Ϣ
             timing_get_mode��Ч��bbe16��arm��Ϊ���׽ӿڻ�ȡ��ʱ��Ϣ
   UNION�ṹ:  BBPCOMM_TIMING_GET_MODE_UNION */
#define BBPCOMM_TIMING_GET_MODE_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xF98)

/* �Ĵ���˵�����Ĵ���
 bit[31:2]   ����
 bit[1]      �߼������㡣
             32������ʱ��Ϣ�ı�־������������timing_valid1��־��
             ����ʱ�̣�DSP��ȡ��ʱ��Ϻ�����
             ��Чʱ�̣�������Ч
             ����Ϊ32K��ʱ��Ϣ���ϱ���ʱԶ��������ϵͳ�Ķ�ʱ��Ϣ�����Ե�������
             ��timing_get_mode��Ч��arm���ƣ�
 bit[0]      �߼������㡣
             ��ʱ��־������������timing_valid1��־��
             ����ʱ�̣�DSP��ȡ��ʱ��Ϻ�����
             ��Чʱ�̣�������Ч��
             ��timing_get_mode��Ч��arm���ƣ�
   UNION�ṹ:  BBPCOMM_TIMING_CLEAR1_UNION */
#define BBPCOMM_TIMING_CLEAR1_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xF9C)

/* �Ĵ���˵�����Ĵ���
 bit[31:6]   ����
 bit[5:4]    ��ʾtiming_get_mode��Чʱarm��ȡcģbbp���������1x��evdo����base_cnt��   00��1x��ʱ��01��evdo��ʱ��10�� base_cnt ��11����Ч��
             timing_get_mode��Чʱ���������ã�������
 bit[3:1]    ����
 bit[0]      �߼������㡣
             timing_get_mode��Ч��arm��Ҫ��ȡ��ʱ��ϵʱ������Ч��CTU�߼����ݴ��ź�����LTE/W/Gm/Gs/TDS/C��ϵͳ��ʱ��CTU���ڲ���ʱ��arm��ѯ��
             ����ʱ�̣������Ҫ���涨ʱ
             ��Чʱ�̣�������Ч
   UNION�ṹ:  BBPCOMM_TIMING_GET_IND1_UNION */
#define BBPCOMM_TIMING_GET_IND1_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xF10)

/* �Ĵ���˵�����Ĵ���
 bit[31:6]   ����
 bit[5:4]    ��ʾo_timing_valid��Чʱ���ϱ��ļ�������arm����cģbbp��1x��evdo����base_cnt
             00��1x��ʱ
             01�� evdo��ʱ
             10�� basecent
 bit[3]      ����
 bit[2]      ��ʾarm��ȡ��ʱ��Ϣ��ʱ���ڳ�ʱ����ʱ����δ����o_timing_clear�źţ�
 bit[1]      32K������ʱ�ϱ���Ч��־������Ч��
             DSP����timing_get_ind1�󣬲�ѯ�˱�־�����Ϊ�ߣ�����Ի�ȡ32K������ʱ���Ķ�ʱ��Ϣ��
             DSP��ȡ��ʱ��Ϻ�����comm_32k_timing_clear1�Ĵ�����comm_32k_timing_valid1����Ϊ��Ч��
             32K��ʱ�����ȶ�������comm_32k_timing_valid1
             ����ʱ�̣�
             ��Чʱ�̣�������Ч
             ��timing_get_mode��Ч��arm���ƣ�
 bit[0]      ��ʱ�ϱ���Ч��־������Ч��
             DSP����timing_get_ind1�󣬲�ѯ�˱�־�����Ϊ�ߣ�����Ի�ȡLTE��W��Gm��Gs, TDS��ϵͳ��ʱ��
             DSP��ȡ��ʱ��Ϻ�����timing_clear1�Ĵ�����timing_valid1����Ϊ��Ч��
             CTU��⵽timing_get_ind1��̶��ӳ�delay_cnt������timing_valid1��
             
             ����ʱ�̣�
             ��Чʱ�̣�������Ч
             ��timing_get_mode��Ч��dsp���ƣ�
             timing_get_mode��Ч��bbe16���ƣ�
   UNION�ṹ:  BBPCOMM_TINMG_VALID1_UNION */
#define BBPCOMM_TINMG_VALID1_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0xF14)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ��ʾtiming_get_mode��Чʱbbe��ȡWģbbp���������sys_cnt����base_cnt��00�������ƣ���sys_cnt��01��base_cnt 10����Ч 11����Ч
             timing_get_mode��Чʱ���������ã�������
   UNION�ṹ:  BBPCOMM_TIMING_GET_W_SEL_UNION */
#define BBPCOMM_TIMING_GET_W_SEL_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xF18)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ��ʾo_timing_valid��Чʱ���ϱ�wģ�ļ�������bbe16����sys_cnt����base_cnt
             00�������ƣ��� sys_cnt
             01�� basecent 10����Ч  11����Ч 
   UNION�ṹ:  BBPCOMM_TIMING_VALID_W_SEL_UNION */
#define BBPCOMM_TIMING_VALID_W_SEL_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xF1C)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ��ʾtiming_get_mode��Чʱarm��ȡwģ���������sys_cnt����base_cnt��   00�������ƣ���sys_cnt��01��base_cnt�� 10����Ч 11 ��Ч
             timing_get_mode��Чʱ���������ã�������
   UNION�ṹ:  BBPCOMM_TIMING_GET_W_SEL1_UNION */
#define BBPCOMM_TIMING_GET_W_SEL1_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xF28)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ��ʾo_timing_valid��Чʱ���ϱ��ļ�������arm����wģbbp��sys_cnt����base_cnt
             00��sys_cnt��ʱ
             01��base_cnt��ʱ 
             10����Ч
             11����Ч
             
   UNION�ṹ:  BBPCOMM_TIMING_VALID_W_SEL1_UNION */
#define BBPCOMM_TIMING_VALID_W_SEL1_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xF2C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      comm����sc_pllʹ�ܣ�1��ͨ��comm����sc_pll��0����ͨ��comm����sc_pll
   UNION�ṹ:  BBPCOMM_CPU_CFG_SC_EN_UNION */
#define BBPCOMM_CPU_CFG_SC_EN_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xF30)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      comm��sc_pll�����ж�1ʹ�ܣ�1����Ч��0��Ч
   UNION�ṹ:  BBPCOMM_CPU_INT1_CFG_SC_EN_UNION */
#define BBPCOMM_CPU_INT1_CFG_SC_EN_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xF34)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      comm��sc_pll�����ж�2ʹ�ܣ�1����Ч��0��Ч
   UNION�ṹ:  BBPCOMM_CPU_INT2_CFG_SC_EN_UNION */
#define BBPCOMM_CPU_INT2_CFG_SC_EN_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xF38)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      �����sc_pll���õ���ģ��ind�ź�
   UNION�ṹ:  BBPCOMM_CPU_PRO_SOFT_CFG_SC_IND_UNION */
#define BBPCOMM_CPU_PRO_SOFT_CFG_SC_IND_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xF3C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      �����sc_pll���õĴ�ģ��ind�ź�
   UNION�ṹ:  BBPCOMM_CPU_SEC_SOFT_CFG_SC_IND_UNION */
#define BBPCOMM_CPU_SEC_SOFT_CFG_SC_IND_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xF40)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    0������ͨ��0����ģ��������sc_pll�ź�
             1������ͨ��1����ģ��������sc_pll�ź�
             2������ͨ��2����ģ��������sc_pll�ź�
   UNION�ṹ:  BBPCOMM_CPU_SC_CH_SEL_UNION */
#define BBPCOMM_CPU_SC_CH_SEL_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xF44)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    ctu�ж�ʱ��ѯ���������źţ�1���������㣻0����Ч��
   UNION�ṹ:  BBPCOMM_CTU_TIMING_ROBIN_CLR_IND_UNION */
#define BBPCOMM_CTU_TIMING_ROBIN_CLR_IND_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xF4C)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define BBPCOMM_BBC_REV0_ADDR                         (SOC_BBP_COMM_BASE_ADDR + 0xFE0)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define BBPCOMM_BBC_REV1_ADDR                         (SOC_BBP_COMM_BASE_ADDR + 0xFE4)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define BBPCOMM_BBC_REV2_ADDR                         (SOC_BBP_COMM_BASE_ADDR + 0xFE8)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define BBPCOMM_BBC_REV3_ADDR                         (SOC_BBP_COMM_BASE_ADDR + 0xFEC)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define BBPCOMM_BBC_REV4_ADDR                         (SOC_BBP_COMM_BASE_ADDR + 0xFF0)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2]      W SDRģʽ������ʱ��ѡ��0���������122mʱ�ӣ�1���������245mʱ�ӡ�
 bit[1]      W SDRģʽ����ʹ�ܡ�
 bit[0]      G SDRģʽ����ʹ�ܡ�
   UNION�ṹ:  BBPCOMM_GU_SDR_EN_UNION */
#define BBPCOMM_GU_SDR_EN_ADDR                        (SOC_BBP_COMM_BASE_ADDR + 0xFFC)

/* �Ĵ���˵����ͨ��2��Ӧ��ģ����ģ2����ģʽָʾ�Ĵ���
 bit[31:3]   ����
 bit[2:0]    ͨ��2��Ӧ����ģ������Ϊ��ģ0����ģʽָʾ����ʾLTE��W��Gm��Gs��TDS˭����ģ2��
             011��Gm��ģ��
             100��Gs��ģ��
             110~111����Ч��
             ����ʱ�̣���ģ����ͨ�ų�������
   UNION�ṹ:  BBPCOMM_C2_PRIMARY_MODE_IND_UNION */
#define BBPCOMM_C2_PRIMARY_MODE_IND_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xD00)

/* �Ĵ���˵������ģ2��Ӧ�Ĵ�ģ����ģ2����ģʽָʾ�Ĵ���
 bit[31:3]   ����
 bit[2:0]    ��ģ2��Ӧ�Ĵ�ģ������Ϊ��ģ2����ģʽָʾ����ʾ��ǰLTE/W/Gm/Gs/TDS˭�Ǵ�ģ2��
             000��LTE��ģ��
             001��W ��ģ��
             010��TDS��ģ��
             011��Gm��ģ��
             100��Gs��ģ��
             101:C��ģ��
             110~111����Ч��
             ����ʱ�̣���ģ����ͨ�ų�������
   UNION�ṹ:  BBPCOMM_C2_SECOND_MODE_IND_UNION */
#define BBPCOMM_C2_SECOND_MODE_IND_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xD04)

/* �Ĵ���˵�����Ĵ���
   ��      ����AFC2ֵ����
               [15:0]:AFC������ֵ
               [16]:AFC����ָʾ
               
               ����ʱ�̣�DSP����ģ�л�Ϊ��ģʱ���ã�DSP�Ӵ�ģ�л�Ϊ��ģʱ��ȡ���������ָʾ
               ��Чʱ�̣�������Ч
   UNION�ṹ ���� */
#define BBPCOMM_AFC2_VALUE_INTER_RAT_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xD0C)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    ͨ��2 AFC�����ź���Դ��
             3'b000������ģ���ƣ�
             3'b001��ǿ����Lģ���ƣ�
             3'b010��ǿ����Wģ���ƣ�
             3'b011��ǿ����TDSģ���ƣ�
             3'b100��ǿ����Gmģ���ƣ�
             3'b101��ǿ����Gsģ���ƣ�
             3'b110��ǿ����Cģ���ƣ�
             3'b111����Ч��
             �����á�
   UNION�ṹ:  BBPCOMM_C2_AFC_PDM_SELECT_MASK_UNION */
#define BBPCOMM_C2_AFC_PDM_SELECT_MASK_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xD10)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    ͨ��2 ���߿��غ�PA�����ź���Դ��
             3'b000������ģ���ƣ�
             3'b001��ǿ����Lģ���ƣ�
             3'b010��ǿ����Wģ���ƣ�
             3'b011��ǿ����TDSģ���ƣ�
             3'b100��ǿ����Gmģ���ƣ�
             3'b101��ǿ����Gsģ���ƣ�
             3'b110��ǿ����Cģ���ƣ�
             3'b111����Ч��
             �����á�
   UNION�ṹ:  BBPCOMM_C2_ANT_SWITCH_PA_SELECT_MASK_UNION */
#define BBPCOMM_C2_ANT_SWITCH_PA_SELECT_MASK_ADDR     (SOC_BBP_COMM_BASE_ADDR + 0xD14)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    ͨ��2 RFIC�����ź���Դ�������߿غ�SSI����
             3'b000������ģ���ƣ�
             3'b001��ǿ����Lģ���ƣ�
             3'b010��ǿ����Wģ���ƣ�
             3'b011��ǿ����TDSģ���ƣ�
             3'b100��ǿ����Gmģ���ƣ�
             3'b101��ǿ����Gsģ���ƣ�
             3'b110��ǿ����Cģ���ƣ�
             3'b111����Ч��
             �����á�
   UNION�ṹ:  BBPCOMM_C2_RFIC_SELECT_MASK_UNION */
#define BBPCOMM_C2_RFIC_SELECT_MASK_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xD18)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    ͨ��2 MIPI�����ź���Դ��
             3'b000������ģ���ƣ�
             3'b001��ǿ����Lģ���ƣ�
             3'b010��ǿ����Wģ���ƣ�
             3'b011��ǿ����TDSģ���ƣ�
             3'b100��ǿ����Gmģ���ƣ�
             3'b101��ǿ����Gsģ���ƣ�
             3'b110��ǿ����Cģ���ƣ�
             ��������Ч��
             �����á�
   UNION�ṹ:  BBPCOMM_C2_MIPI_SELECT_MASK_UNION */
#define BBPCOMM_C2_MIPI_SELECT_MASK_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xD1C)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    ͨ��2 ABB�����ź���Դ��
             3'b000������ģ���ƣ�
             3'b001��ǿ����Lģ���ƣ�
             3'b010��ǿ����Wģ���ƣ�
             3'b011��ǿ����TDSģ���ƣ�
             3'b100��ǿ����Gmģ���ƣ�
             3'b101��ǿ����Gsģ���ƣ�
             3'b110��ǿ����Cģ���ƣ�
             ��������Ч��
             �����á�
   UNION�ṹ:  BBPCOMM_C2_ABB_SELECT_MASK_UNION */
#define BBPCOMM_C2_ABB_SELECT_MASK_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xD20)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    ͨ��2 PMU�����ź���Դ��
             3'b000������ģ���ƣ�
             3'b001��ǿ����Lģ���ƣ�
             3'b010��ǿ����Wģ���ƣ�
             3'b011��ǿ����TDSģ���ƣ�
             3'b100��ǿ����Gmģ���ƣ�
             3'b101��ǿ����Gsģ���ƣ�
             3'b110��ǿ����Cģ���ƣ�
             3'b111����Ч��
             �����á�
   UNION�ṹ:  BBPCOMM_C2_PMU_SELECT_MASK_UNION */
#define BBPCOMM_C2_PMU_SELECT_MASK_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xD24)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    ��ǰͨ��2������֮ǰ�������ǿ��ģʽ��
             ע���������ڸ�����Χ������ABB��RF��PA��mipi�ȣ������Ľ���ǿ�䡣
             �����á�
   UNION�ṹ:  BBPCOMM_DSP_C2_SEL_MASK_UNION */
#define BBPCOMM_DSP_C2_SEL_MASK_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xD28)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    ������õ�RFIC2��λ�źţ�����Ч��
             0����λ��1���⸴λ��
             �ϵ��ʼ������Ϊ0������RFIC�ֲ�Ҫ��ά��һ��ʱ�������Ϊ1��
             V3R3���üĴ������ܸ��ڼĴ���0x0334��bit[8]ʵ�֣�Ĭ��ֵ��Ϊ0���˴�ɾ����
             V7R2��λֵΪ0��
             V8R1���üĴ�������ɾ����
   UNION�ṹ:  BBPCOMM_DSP_RFIC2_RSTN_UNION */
#define BBPCOMM_DSP_RFIC2_RSTN_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0xD2C)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      0:ͨ��2��ģʹ��ͨ��2��ģafc������
             1:ͨ��2��ģʹ��ͨ��2��ģafc������
   UNION�ṹ:  BBPCOMM_C2_SECOND_AFC_MODE_UNION */
#define BBPCOMM_C2_SECOND_AFC_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xD30)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      DSP�ȴ��ض������ʱ��־λ
             1:��ʱ  
   UNION�ṹ:  BBPCOMM_MIPI2_RD_OVERTIME_FLAG_DSP_UNION */
#define BBPCOMM_MIPI2_RD_OVERTIME_FLAG_DSP_ADDR       (SOC_BBP_COMM_BASE_ADDR + 0xD38)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      DSP�ȴ��ض������ʱ��־λ
             1:��ʱ  
   UNION�ṹ:  BBPCOMM_SSI2_RD_OVERTIME_FLAG_DSP_UNION */
#define BBPCOMM_SSI2_RD_OVERTIME_FLAG_DSP_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xD3C)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      DSP�ȴ��ض������ʱ��,�峭ʱ��־λ����
   UNION�ṹ:  BBPCOMM_MIPI2_RD_OVERTIME_CLR_UNION */
#define BBPCOMM_MIPI2_RD_OVERTIME_CLR_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xD40)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      DSP�ȴ��ض������ʱ��,�峭ʱ��־λ����
   UNION�ṹ:  BBPCOMM_SSI2_RD_OVERTIME_CLR_UNION */
#define BBPCOMM_SSI2_RD_OVERTIME_CLR_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xD44)

/* �Ĵ���˵�����Ĵ���
   ��      ����xbbp��SSI2 master�����ض���ָ��ʱ,DSP��ȡSSI�ض����,�ض���������ڴ�16�Ĵ���λ����dsp����,�ض������Ƿ���Ч�ο���־λ
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC2_1_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xD48)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC2_2_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xD4C)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC2_3_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xD50)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC2_4_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xD54)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC2_5_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xD58)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC2_6_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xD5C)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC2_7_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xD60)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC2_8_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xD64)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC2_9_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xD68)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC2_10_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xD6C)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC2_11_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xD70)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC2_12_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xD74)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC2_13_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xD78)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC2_14_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xD7C)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC2_15_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xD80)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_RFIC2_16_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xD84)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      ���лض�ָ��ִ�����,����ȡ�߻ض�����
             1:���лض�ָ������,DSP���԰�λ�ö�ȡSSI�ض����
   UNION�ṹ:  BBPCOMM_RD_RESULT_FLAG_RFIC2_UNION */
#define BBPCOMM_RD_RESULT_FLAG_RFIC2_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xD88)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      1:DSPȡ�����лض����ݺ�,д��clr�ź����־λ
   UNION�ṹ:  BBPCOMM_RD_RESULT_FLAG_RFIC2_CLR_UNION */
#define BBPCOMM_RD_RESULT_FLAG_RFIC2_CLR_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xD8C)

/* �Ĵ���˵�����Ĵ���
   ��      ����xbbp��MIPI2 master�����ض���ָ��ʱ,DSP��ȡMIPI�ض����,�ض���������ڴ�16�Ĵ���λ����dsp����,�ض������Ƿ���Ч�ο���־λ
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI2_1_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xD90)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI2_2_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xD94)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI2_3_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xD98)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI2_4_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xD9C)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI2_5_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xDA0)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI2_6_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xDA4)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI2_7_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xDA8)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI2_8_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xDAC)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI2_9_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xDB0)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI2_10_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xDB4)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI2_11_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xDB8)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI2_12_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xDBC)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI2_13_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xDC0)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI2_14_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xDC4)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI2_15_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xDC8)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI2_16_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xDCC)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      ���лض�ָ��ִ�����,����ȡ�߻ض�����
             1:���лض�ָ������,DSP���԰�λ�ö�ȡMIPI�ض����,�����������ֱ�ӿ���MIPI��־λ��ͬ
   UNION�ṹ:  BBPCOMM_RD_RESULT_FLAG_MIPI2_UNION */
#define BBPCOMM_RD_RESULT_FLAG_MIPI2_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xDD0)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      1:DSPȡ�����лض����ݺ�,д��clr�ź����־λ,�����������ֱ�ӿ���MIPI��־λ��ͬ
   UNION�ṹ:  BBPCOMM_RD_RESULT_FLAG_MIPI2_CLR_UNION */
#define BBPCOMM_RD_RESULT_FLAG_MIPI2_CLR_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xDD4)

/* �Ĵ���˵�����Ĵ���
   ��      ���������ֱ�ӿ���MIPI2 master,������xbbp���ͻض�ָ��ʱ,�ض�ָ���ŵ�32bit.
   UNION�ṹ ���� */
#define BBPCOMM_MIPI2_RD_DATA_LOW_SOFT_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xDD8)

/* �Ĵ���˵�����Ĵ���
   ��      ���������ֱ�ӿ���MIPI2 master,������xbbp���ͻض�ָ��ʱ,�ض�ָ���Ÿ�32bit.
   UNION�ṹ ���� */
#define BBPCOMM_MIPI2_RD_DATA_HIGH_SOFT_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xDDC)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      �����ֱ�ӿ���MIPI2 master,������xbbp���ͻض�ָ��ʱ,�ض�������Чָʾ
   UNION�ṹ:  BBPCOMM_RD_END_FLAG_MIPI2_SOFT_UNION */
#define BBPCOMM_RD_END_FLAG_MIPI2_SOFT_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xDE0)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      �����ֱ�ӿ���MIPI2 master
             1:������Է���CFG_IND����mipi0
             0:����ȴ�mipi2��Ȩʹ��
   UNION�ṹ:  BBPCOMM_MIPI2_GRANT_DSP_UNION */
#define BBPCOMM_MIPI2_GRANT_DSP_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xDE4)

/* �Ĵ���˵�����Ĵ���
   ��      ���������ֱ�ӿ���MIPI2 master,������xbbp����дָ��ʱ,дָ���32bit��
               ��MIPI��̬ʹ��mipi_dyn_exchg_en��Чʱ��MIPI��չָ��ʱ��dsp_mipi2_wdata_low[1��0]Ӧ����Ϊ0x2
   UNION�ṹ ���� */
#define BBPCOMM_DSP_MIPI2_WDATA_LOW_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xDE8)

/* �Ĵ���˵�����Ĵ���
   ��      ���������ֱ�ӿ���MIPI2 master,������xbbp����дָ��ʱ,дָ���32bit��
               ��MIPI��̬ʹ��mipi_dyn_exchg_en��Ч��MIPI����չָ��ʱ��dsp_mipi2_wdata_high[1��0]Ӧ����Ϊ:0x2
   UNION�ṹ ���� */
#define BBPCOMM_DSP_MIPI2_WDATA_HIGH_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xDEC)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      �����ֱ�ӿ���MIPI2 master,���������ߴ�ָʾ,����xbbp��MIPI0�Ŀ���
   UNION�ṹ:  BBPCOMM_DSP_MIPI2_EN_IMI_UNION */
#define BBPCOMM_DSP_MIPI2_EN_IMI_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xDF0)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      �����ֱ�ӿ���MIPI2 master,���ߴ�dsp_mipi0_en��,���������������
   UNION�ṹ:  BBPCOMM_DSP_MIPI2_CFG_IND_IMI_UNION */
#define BBPCOMM_DSP_MIPI2_CFG_IND_IMI_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xDF4)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      �����ֱ�ӿ���MIPI2 master,ȡ�߻ض����ݺ�,���־λ����
   UNION�ṹ:  BBPCOMM_DSP_MIPI2_RD_CLR_UNION */
#define BBPCOMM_DSP_MIPI2_RD_CLR_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xDF8)

/* �Ĵ���˵�����Ĵ���
 bit[31:9]   ����
 bit[8:8]    ���ǿ��ģʽabb2_rxb_blk_en.
 bit[7:7]    ���ǿ��ģʽabb2_rxa_blk_en.
 bit[6:6]    ���ǿ��ģʽabb2_rxb_en.
 bit[5:5]    ���ǿ��ģʽabb2_rxa_en.
 bit[4:4]    ���ǿ��ģʽabb2_tx_en.
 bit[3:1]    ���ǿ��ģʽabb2_mode_sel.
 bit[0:0]    ABB2�߿�ǿ��ģʽ��
             1����ʾ���ǿ�䣬��ʱ��������ǿ�����Ч��
             0����ʾ��CTU���ݸ�BBP������
             Ĭ��ֵΪ0��
             �����á�
   UNION�ṹ:  BBPCOMM_ABB2_LINE_CONTROL_CMD_UNION */
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xDFC)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    V9R1�汾����������á�
   UNION�ṹ:  BBPCOMM_CH2_BBP_SEL_UNION */
#define BBPCOMM_CH2_BBP_SEL_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0xE00)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      cpu����mipi����,����Ϊ1������������, ����ʱ����Ϊ0
   UNION�ṹ:  BBPCOMM_CPU_MIPI2_FUNC_SEL_UNION */
#define BBPCOMM_CPU_MIPI2_FUNC_SEL_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xE04)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      cpu����mipi����,������
   UNION�ṹ:  BBPCOMM_CPU_MIPI2_TEST_FUNC_UNION */
#define BBPCOMM_CPU_MIPI2_TEST_FUNC_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xE08)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      cpu����mipi����, ������
   UNION�ṹ:  BBPCOMM_CPU_MIPI2_SCLK_TEST_UNION */
#define BBPCOMM_CPU_MIPI2_SCLK_TEST_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xE0C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      cpu����mipi����, ������
   UNION�ṹ:  BBPCOMM_CPU_MIPI2_SDATA_TEST_UNION */
#define BBPCOMM_CPU_MIPI2_SDATA_TEST_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xE10)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      cpu����mipi����,mipi2master���쳣�ź�
   UNION�ṹ:  BBPCOMM_DSP_MIPI2_CLR_IND_IMI_UNION */
#define BBPCOMM_DSP_MIPI2_CLR_IND_IMI_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xE14)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      mipi2�洢����������ͬ��FIFO��λ�ź�
   UNION�ṹ:  BBPCOMM_CPU_MIPI2_FIFO_CLR_IMI_UNION */
#define BBPCOMM_CPU_MIPI2_FIFO_CLR_IMI_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xE18)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ssi2�洢����������ͬ��FIFO��λ�ź�
   UNION�ṹ:  BBPCOMM_CPU_SSI2_FIFO_CLR_IMI_UNION */
#define BBPCOMM_CPU_SSI2_FIFO_CLR_IMI_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xE1C)

/* �Ĵ���˵����
 bit[31:12]  ����
 bit[11]     Cģͨ��2 TX ABB��·ʱ���ſ���·�ź�
 bit[10]     Cģͨ��2 RX ABB��·ʱ���ſ���·�ź�
 bit[9]      G2ͨ��2 TX ABB��·ʱ���ſ���·�ź�
 bit[8]      G1ͨ��2 TX ABB��·ʱ���ſ���·�ź�
 bit[7]      Wģͨ��2 TX ABB��·ʱ���ſ���·�ź�
 bit[6]      TDSͨ��2 TX ABB��·ʱ���ſ���·�ź�
 bit[5]      Lģͨ��2 TX ABB��·ʱ���ſ���·�ź�
 bit[4]      G2ͨ��2 RX ABB��·ʱ���ſ���·�ź�
 bit[3]      G1ͨ��2 RX ABB��·ʱ���ſ���·�ź�
 bit[2]      Wģͨ��2 RX ABB��·ʱ���ſ���·�ź�
 bit[1]      TDSͨ��2 RX ABB��·ʱ���ſ���·�ź�
 bit[0]      Lģͨ��2 RX ABB��·ʱ���ſ���·�ź�
   UNION�ṹ:  BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_UNION */
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xE20)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      DSP�ȴ��ض������ʱ��־λ
             1:��ʱ  
   UNION�ṹ:  BBPCOMM_MIPI3_RD_OVERTIME_FLAG_DSP_UNION */
#define BBPCOMM_MIPI3_RD_OVERTIME_FLAG_DSP_ADDR       (SOC_BBP_COMM_BASE_ADDR + 0xE38)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      DSP�ȴ��ض������ʱ��,�峭ʱ��־λ����
   UNION�ṹ:  BBPCOMM_MIPI3_RD_OVERTIME_CLR_UNION */
#define BBPCOMM_MIPI3_RD_OVERTIME_CLR_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xE40)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      cpu����mipi����,����Ϊ1������������, ����ʱ����Ϊ0
   UNION�ṹ:  BBPCOMM_CPU_MIPI3_FUNC_SEL_UNION */
#define BBPCOMM_CPU_MIPI3_FUNC_SEL_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xE44)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      cpu����mipi����,������
   UNION�ṹ:  BBPCOMM_CPU_MIPI3_TEST_FUNC_UNION */
#define BBPCOMM_CPU_MIPI3_TEST_FUNC_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xE48)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      cpu����mipi����, ������
   UNION�ṹ:  BBPCOMM_CPU_MIPI3_SCLK_TEST_UNION */
#define BBPCOMM_CPU_MIPI3_SCLK_TEST_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xE4C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      cpu����mipi����, ������
   UNION�ṹ:  BBPCOMM_CPU_MIPI3_SDATA_TEST_UNION */
#define BBPCOMM_CPU_MIPI3_SDATA_TEST_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xE50)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      cpu����mipi����,mipi2master���쳣�ź�
   UNION�ṹ:  BBPCOMM_DSP_MIPI3_CLR_IND_IMI_UNION */
#define BBPCOMM_DSP_MIPI3_CLR_IND_IMI_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xE54)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      mipi3�洢����������ͬ��FIFO��λ�ź�
   UNION�ṹ:  BBPCOMM_CPU_MIPI3_FIFO_CLR_IMI_UNION */
#define BBPCOMM_CPU_MIPI3_FIFO_CLR_IMI_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xE58)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    apt_pdm2/apt_vpen2�ź���Դ��
             2'd0��������ͨ��0
             2'd1��������ͨ��1
             2'd2��������ͨ��2
             2'd3��ǿ�Ƶ͵�ƽ���
   UNION�ṹ:  BBPCOMM_APT_CH_SEL2_UNION */
#define BBPCOMM_APT_CH_SEL2_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0xE5C)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    afc pdm2�ź���Դ��
             2'd0��������ͨ��0
             2'd1��������ͨ��1
             2'd2��������ͨ��2
             2'd3��ǿ�Ƶ͵�ƽ���
   UNION�ṹ:  BBPCOMM_AFC_CH_SEL2_UNION */
#define BBPCOMM_AFC_CH_SEL2_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0xE60)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    auxdac2�ź���Դ��
             2'd0��������ͨ��0
             2'd1��������ͨ��1
             2'd2��������ͨ��2
             2'd3��ǿ�Ƶ͵�ƽ���
   UNION�ṹ:  BBPCOMM_PMU_CH_SEL2_UNION */
#define BBPCOMM_PMU_CH_SEL2_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0xE64)

/* �Ĵ���˵�����Ĵ���
   ��      ����xbbp��MIPI3 master�����ض���ָ��ʱ,DSP��ȡMIPI�ض����,�ض���������ڴ�16�Ĵ���λ����dsp����,�ض������Ƿ���Ч�ο���־λ
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI3_1_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xE90)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI3_2_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xE94)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI3_3_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xE98)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI3_4_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xE9C)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI3_5_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xEA0)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI3_6_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xEA4)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI3_7_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xEA8)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI3_8_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xEAC)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI3_9_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xEB0)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI3_10_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xEB4)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI3_11_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xEB8)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI3_12_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xEBC)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI3_13_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xEC0)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI3_14_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xEC4)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI3_15_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xEC8)

/* �Ĵ���˵�����Ĵ���
   ��      ����ͬ��
   UNION�ṹ ���� */
#define BBPCOMM_RD_RESULT_MIPI3_16_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xECC)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      ���лض�ָ��ִ�����,����ȡ�߻ض�����
             1:���лض�ָ������,DSP���԰�λ�ö�ȡMIPI�ض����,�����������ֱ�ӿ���MIPI��־λ��ͬ
   UNION�ṹ:  BBPCOMM_RD_RESULT_FLAG_MIPI3_UNION */
#define BBPCOMM_RD_RESULT_FLAG_MIPI3_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xED0)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      1:DSPȡ�����лض����ݺ�,д��clr�ź����־λ,�����������ֱ�ӿ���MIPI��־λ��ͬ
   UNION�ṹ:  BBPCOMM_RD_RESULT_FLAG_MIPI3_CLR_UNION */
#define BBPCOMM_RD_RESULT_FLAG_MIPI3_CLR_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xED4)

/* �Ĵ���˵�����Ĵ���
   ��      ���������ֱ�ӿ���MIPI3 master,������xbbp���ͻض�ָ��ʱ,�ض�ָ���ŵ�32bit.
   UNION�ṹ ���� */
#define BBPCOMM_MIPI3_RD_DATA_LOW_SOFT_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xED8)

/* �Ĵ���˵�����Ĵ���
   ��      ���������ֱ�ӿ���MIPI3 master,������xbbp���ͻض�ָ��ʱ,�ض�ָ���Ÿ�32bit.
   UNION�ṹ ���� */
#define BBPCOMM_MIPI3_RD_DATA_HIGH_SOFT_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xEDC)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      �����ֱ�ӿ���MIPI3 master,������xbbp���ͻض�ָ��ʱ,�ض�������Чָʾ
   UNION�ṹ:  BBPCOMM_RD_END_FLAG_MIPI3_SOFT_UNION */
#define BBPCOMM_RD_END_FLAG_MIPI3_SOFT_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xEE0)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      �����ֱ�ӿ���MIPI3 master
             1:������Է���CFG_IND����mipi0
             0:����ȴ�mipi3��Ȩʹ��
   UNION�ṹ:  BBPCOMM_MIPI3_GRANT_DSP_UNION */
#define BBPCOMM_MIPI3_GRANT_DSP_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xEE4)

/* �Ĵ���˵�����Ĵ���
   ��      ���������ֱ�ӿ���MIPI3 master,������xbbp����дָ��ʱ,дָ���32bit��
               ��MIPI��̬ʹ��mipi_dyn_exchg_en��Чʱ��MIPI��չָ��ʱ��dsp_mipi3_wdata_low[1��0]Ӧ����Ϊ0x3
   UNION�ṹ ���� */
#define BBPCOMM_DSP_MIPI3_WDATA_LOW_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xEE8)

/* �Ĵ���˵�����Ĵ���
   ��      ���������ֱ�ӿ���MIPI3 master,������xbbp����дָ��ʱ,дָ���32bit��
               ��MIPI��̬ʹ��mipi_dyn_exchg_en��Ч��MIPI����չָ��ʱ��dsp_mipi3_wdata_high[1��0]Ӧ����Ϊ0x3
   UNION�ṹ ���� */
#define BBPCOMM_DSP_MIPI3_WDATA_HIGH_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xEEC)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      �����ֱ�ӿ���MIPI3 master,���������ߴ�ָʾ,����xbbp��MIPI0�Ŀ���
   UNION�ṹ:  BBPCOMM_DSP_MIPI3_EN_IMI_UNION */
#define BBPCOMM_DSP_MIPI3_EN_IMI_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xEF0)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      �����ֱ�ӿ���MIPI3 master,���ߴ�dsp_mipi0_en��,���������������
   UNION�ṹ:  BBPCOMM_DSP_MIPI3_CFG_IND_IMI_UNION */
#define BBPCOMM_DSP_MIPI3_CFG_IND_IMI_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xEF4)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0]      �����ֱ�ӿ���MIPI3 master,ȡ�߻ض����ݺ�,���־λ����
   UNION�ṹ:  BBPCOMM_DSP_MIPI3_RD_CLR_UNION */
#define BBPCOMM_DSP_MIPI3_RD_CLR_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xEF8)

/* �Ĵ���˵�����Ĵ���
 bit[31:31]  ����
 bit[30:0]   LTEģ���߿����������ֵ
             lte_soft_antpa_en�ź���Чʱ��Ч
   UNION�ṹ:  BBPCOMM_LTE_SOFT_ANTPA_SEL_UNION */
#define BBPCOMM_LTE_SOFT_ANTPA_SEL_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xF50)

/* �Ĵ���˵�����Ĵ���
 bit[31:31]  ����
 bit[30:0]   wģ���߿����������ֵ
             w_soft_antpa_en�ź���Чʱ��Ч
   UNION�ṹ:  BBPCOMM_W_SOFT_ANTPA_SEL_UNION */
#define BBPCOMM_W_SOFT_ANTPA_SEL_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xF54)

/* �Ĵ���˵�����Ĵ���
 bit[31:31]  ����
 bit[30:0]   tdsģ���߿����������ֵ
             tds_soft_antpa_en�ź���Чʱ��Ч
   UNION�ṹ:  BBPCOMM_TDS_SOFT_ANTPA_SEL_UNION */
#define BBPCOMM_TDS_SOFT_ANTPA_SEL_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xF58)

/* �Ĵ���˵�����Ĵ���
 bit[31:31]  ����
 bit[30:0]   GMģ���߿����������ֵ
             gm_soft_antpa_en�ź���Чʱ��Ч
   UNION�ṹ:  BBPCOMM_GM_SOFT_ANTPA_SEL_UNION */
#define BBPCOMM_GM_SOFT_ANTPA_SEL_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xF5C)

/* �Ĵ���˵�����Ĵ���
 bit[31:31]  ����
 bit[30:0]   gsģ���߿����������ֵ
             gs_soft_antpa_en�ź���Чʱ��Ч
   UNION�ṹ:  BBPCOMM_GS_SOFT_ANTPA_SEL_UNION */
#define BBPCOMM_GS_SOFT_ANTPA_SEL_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xF60)

/* �Ĵ���˵�����Ĵ���
 bit[31:31]  ����
 bit[30:0]   Cģ���߿����������ֵ
             c_soft_antpa_en�ź���Чʱ��Ч
   UNION�ṹ:  BBPCOMM_C_SOFT_ANTPA_SEL_UNION */
#define BBPCOMM_C_SOFT_ANTPA_SEL_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xF64)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    LTEģ���߿����������ʹ��
             0��ʹ���߼�����ֵ
             1��ʹ���������ֵlte_soft_antpa_sel
   UNION�ṹ:  BBPCOMM_LTE_SOFT_ANTPA_EN_UNION */
#define BBPCOMM_LTE_SOFT_ANTPA_EN_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xF68)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    Wģ���߿����������ʹ��
             0��ʹ���߼�����ֵ
             1��ʹ���������ֵw_soft_antpa_sel
   UNION�ṹ:  BBPCOMM_W_SOFT_ANTPA_EN_UNION */
#define BBPCOMM_W_SOFT_ANTPA_EN_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xF6C)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    TDSģ���߿����������ʹ��
             0��ʹ���߼�����ֵ
             1��ʹ���������ֵtds_soft_antpa_sel
   UNION�ṹ:  BBPCOMM_TDS_SOFT_ANTPA_EN_UNION */
#define BBPCOMM_TDS_SOFT_ANTPA_EN_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xFA0)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    GMģ���߿����������ʹ��
             0��ʹ���߼�����ֵ
             1��ʹ���������ֵgm_soft_antpa_sel
   UNION�ṹ:  BBPCOMM_GM_SOFT_ANTPA_EN_UNION */
#define BBPCOMM_GM_SOFT_ANTPA_EN_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xFA4)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    GSģ���߿����������ʹ��
             0��ʹ���߼�����ֵ
             1��ʹ���������ֵgs_soft_antpa_sel
   UNION�ṹ:  BBPCOMM_GS_SOFT_ANTPA_EN_UNION */
#define BBPCOMM_GS_SOFT_ANTPA_EN_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xFA8)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    Cģ���߿����������ʹ��
             0��ʹ���߼�����ֵ
             1��ʹ���������ֵ_soft_antpa_sel
   UNION�ṹ:  BBPCOMM_C_SOFT_ANTPA_EN_UNION */
#define BBPCOMM_C_SOFT_ANTPA_EN_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xFAC)

/* �Ĵ���˵�����Ĵ���
 bit[31:31]  ����
 bit[30:0]   ͨ��0ģʽ��Чʱ������õ����߿�������ֵ
   UNION�ṹ:  BBPCOMM_CH0_SOFT_ANTPA_SEL_UNION */
#define BBPCOMM_CH0_SOFT_ANTPA_SEL_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xFB0)

/* �Ĵ���˵�����Ĵ���
 bit[31:31]  ����
 bit[30:0]   ͨ��1ģʽ��Чʱ������õ����߿�������ֵ
   UNION�ṹ:  BBPCOMM_CH1_SOFT_ANTPA_SEL_UNION */
#define BBPCOMM_CH1_SOFT_ANTPA_SEL_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xFB4)

/* �Ĵ���˵�����Ĵ���
 bit[31:31]  ����
 bit[30:0]   ͨ��2ģʽ��Чʱ������õ����߿�������ֵ
   UNION�ṹ:  BBPCOMM_CH2_SOFT_ANTPA_SEL_UNION */
#define BBPCOMM_CH2_SOFT_ANTPA_SEL_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xFB8)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    ����
   UNION�ṹ:  BBPCOMM_LTE_SOFT_RST_UNION */
#define BBPCOMM_LTE_SOFT_RST_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0xFC0)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    ����
   UNION�ṹ:  BBPCOMM_W_SOFT_RST_UNION */
#define BBPCOMM_W_SOFT_RST_ADDR                       (SOC_BBP_COMM_BASE_ADDR + 0xFC4)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    ����
   UNION�ṹ:  BBPCOMM_TDS_SOFT_RST_UNION */
#define BBPCOMM_TDS_SOFT_RST_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0xFC8)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    ����
   UNION�ṹ:  BBPCOMM_GM_SOFT_RST_UNION */
#define BBPCOMM_GM_SOFT_RST_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0xFCC)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    ����
   UNION�ṹ:  BBPCOMM_GS_SOFT_RST_UNION */
#define BBPCOMM_GS_SOFT_RST_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0xFD0)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    ����
   UNION�ṹ:  BBPCOMM_C_SOFT_RST_UNION */
#define BBPCOMM_C_SOFT_RST_ADDR                       (SOC_BBP_COMM_BASE_ADDR + 0xFD4)

/* �Ĵ���˵�����Ĵ���
 bit[31:4]   ����
 bit[3:0]    ��ά�ɲ�mipi�ɼ�����ͨ������ָʾ��
             dbg_mipi_ch_mask[X],X=0~3,��
             0��ͨ��X��mipi���ݲ��ɼ�
             1���ɼ�ͨ��X��mipi����
   UNION�ṹ:  BBPCOMM_DBG_MIPI_CH_MASK_UNION */
#define BBPCOMM_DBG_MIPI_CH_MASK_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xFD8)

/* �Ĵ���˵�����Ĵ���
 bit[31:3]   ����
 bit[2:0]    ��ά�ɲ�ssi�ɼ�����ͨ������ָʾ��
             dbg_ssi_ch_mask[X],X=0~2,��
             0��ͨ��X��mipi���ݲ��ɼ�
             1���ɼ�ͨ��X��mipi����
   UNION�ṹ:  BBPCOMM_DBG_SSI_CH_MASK_UNION */
#define BBPCOMM_DBG_SSI_CH_MASK_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xFDC)

/* �Ĵ���˵�����Ĵ���
 bit[31:4]   ����
 bit[3:0]    �����߿�ģʽѡ���źţ�bit[3:0]�ֱ����com2fem_antpa_sel[5:2]��ģʽѡ��
             com2fem_antpa_sel[2]��bit[0]Ϊ0ʱѡ��RFFE GPIO˫modem����Ժ��������ߵ�ƽ��Ч��������1ʱѡ��RFFE GPIO˫modem�����Ժ��������͵�ƽ��Ч�����Դ����ƣ�com2fem_antpa_sel[5:3]�ֱ���bit[3:1]��Ӧ���ơ�
   UNION�ṹ:  BBPCOMM_CPU_ANTPA_MODE_SEL_UNION */
#define BBPCOMM_CPU_ANTPA_MODE_SEL_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xFF4)

/* �Ĵ���˵�����Ĵ���
 bit[31:2]   ����
 bit[1:1]    0:com2abb_ch2_tx_en����com2fem_antpa_sel[30]����
             1:com2fem_antpa_sel[30]Ϊ1��com2abb_ch2_tx_enǿ�����ͣ�
             Ϊ0���߼����������
 bit[0:0]    0:com2abb_ch0/1_tx_en����com2fem_antpa_sel[29]����
             1:com2fem_antpa_sel[29]Ϊ1��com2abb_ch0/1_tx_enǿ�����ͣ�
             Ϊ0���߼����������
   UNION�ṹ:  BBPCOMM_CPU_ABB_CH_TX_MASK_SEL_UNION */
#define BBPCOMM_CPU_ABB_CH_TX_MASK_SEL_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xFF8)

/* �Ĵ���˵�����Ĵ���
 bit[31:2]   ����
 bit[1:0]    PD���˿�0�ź���Դ��
             2'd0��������ͨ��0
             2'd1��������ͨ��1
             2'd2��������ͨ��2
             2'd3��ǿ�Ƶ͵�ƽ���
   UNION�ṹ:  BBPCOMM_PD_CH_SEL0_UNION */
#define BBPCOMM_PD_CH_SEL0_ADDR                       (SOC_BBP_COMM_BASE_ADDR + 0x1000)

/* �Ĵ���˵�����Ĵ���
 bit[31:2]   ����
 bit[1:0]    PD���˿�1�ź���Դ��
             2'd0��������ͨ��0
             2'd1��������ͨ��1
             2'd2��������ͨ��2
             2'd3��ǿ�Ƶ͵�ƽ���
   UNION�ṹ:  BBPCOMM_PD_CH_SEL1_UNION */
#define BBPCOMM_PD_CH_SEL1_ADDR                       (SOC_BBP_COMM_BASE_ADDR + 0x1004)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    tcvr_on���pin��0�ź�Դѡ�񿪹أ�
             0��������ͨ��0���߼�ѡ�������
             1��������������������
             
   UNION�ṹ:  BBPCOMM_TCVR_ON_CFG_OUT0_UNION */
#define BBPCOMM_TCVR_ON_CFG_OUT0_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x1008)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    tcvr_on���pin��1�ź�Դѡ�񿪹أ�
             0��������ͨ��1���߼�ѡ�������
             1��������������������
             
   UNION�ṹ:  BBPCOMM_TCVR_ON_CFG_OUT1_UNION */
#define BBPCOMM_TCVR_ON_CFG_OUT1_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x100C)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    tcvr_on���pin��2�ź�Դѡ�񿪹أ�
             0��������ͨ��2���߼�ѡ�������
             1��������������������
             
   UNION�ṹ:  BBPCOMM_TCVR_ON_CFG_OUT2_UNION */
#define BBPCOMM_TCVR_ON_CFG_OUT2_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x1010)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    �������LTEģtcvr_on�źſ�����Χ
             tcvr_on��pin��0�ź����
             ����1Ϊ���ߣ�0Ϊ����
   UNION�ṹ:  BBPCOMM_LTE_TCVR_ON_CFG_PIN0_UNION */
#define BBPCOMM_LTE_TCVR_ON_CFG_PIN0_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x1014)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    �������Wģtcvr_on�źſ�����Χ
             tcvr_on��pin��0�ź����
             ����1Ϊ���ߣ�0Ϊ����
   UNION�ṹ:  BBPCOMM_W_TCVR_ON_CFG_PIN0_UNION */
#define BBPCOMM_W_TCVR_ON_CFG_PIN0_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x1018)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    �������TDSģtcvr_on�źſ�����Χ
             tcvr_on��pin��0�ź����
             ����1Ϊ���ߣ�0Ϊ����
   UNION�ṹ:  BBPCOMM_TDS_TCVR_ON_CFG_PIN0_UNION */
#define BBPCOMM_TDS_TCVR_ON_CFG_PIN0_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x101C)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    �������GMģtcvr_on�źſ�����Χ
             tcvr_on��pin��0�ź����
             ����1Ϊ���ߣ�0Ϊ����
   UNION�ṹ:  BBPCOMM_GM_TCVR_ON_CFG_PIN0_UNION */
#define BBPCOMM_GM_TCVR_ON_CFG_PIN0_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x1020)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    �������GSģtcvr_on�źſ�����Χ
             tcvr_on��pin��0�ź����
             ����1Ϊ���ߣ�0Ϊ����
   UNION�ṹ:  BBPCOMM_GS_TCVR_ON_CFG_PIN0_UNION */
#define BBPCOMM_GS_TCVR_ON_CFG_PIN0_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x1024)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    �������Cģtcvr_on�źſ�����Χ
             tcvr_on��pin��0�ź����
             ����1Ϊ���ߣ�0Ϊ����
   UNION�ṹ:  BBPCOMM_C_TCVR_ON_CFG_PIN0_UNION */
#define BBPCOMM_C_TCVR_ON_CFG_PIN0_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x1028)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    �������LTEģtcvr_on�źſ�����Χ
             tcvr_on��pin��1�ź����
             ����1Ϊ���ߣ�0Ϊ����
   UNION�ṹ:  BBPCOMM_LTE_TCVR_ON_CFG_PIN1_UNION */
#define BBPCOMM_LTE_TCVR_ON_CFG_PIN1_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x102C)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    �������Wģtcvr_on�źſ�����Χ
             tcvr_on��pin��1�ź����
             ����1Ϊ���ߣ�0Ϊ����
   UNION�ṹ:  BBPCOMM_W_TCVR_ON_CFG_PIN1_UNION */
#define BBPCOMM_W_TCVR_ON_CFG_PIN1_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x1030)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    �������TDSģtcvr_on�źſ�����Χ
             tcvr_on��pin��1�ź����
             ����1Ϊ���ߣ�0Ϊ����
   UNION�ṹ:  BBPCOMM_TDS_TCVR_ON_CFG_PIN1_UNION */
#define BBPCOMM_TDS_TCVR_ON_CFG_PIN1_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x1034)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    �������GMģtcvr_on�źſ�����Χ
             tcvr_on��pin��1�ź����
             ����1Ϊ���ߣ�0Ϊ����
   UNION�ṹ:  BBPCOMM_GM_TCVR_ON_CFG_PIN1_UNION */
#define BBPCOMM_GM_TCVR_ON_CFG_PIN1_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x1038)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    �������GSģtcvr_on�źſ�����Χ
             tcvr_on��pin��1�ź����
             ����1Ϊ���ߣ�0Ϊ����
   UNION�ṹ:  BBPCOMM_GS_TCVR_ON_CFG_PIN1_UNION */
#define BBPCOMM_GS_TCVR_ON_CFG_PIN1_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x103C)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    �������Cģtcvr_on�źſ�����Χ
             tcvr_on��pin��1�ź����
             ����1Ϊ���ߣ�0Ϊ����
   UNION�ṹ:  BBPCOMM_C_TCVR_ON_CFG_PIN1_UNION */
#define BBPCOMM_C_TCVR_ON_CFG_PIN1_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x1040)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    �������LTEģtcvr_on�źſ�����Χ
             tcvr_on��pin��2�ź����
             ����1Ϊ���ߣ�0Ϊ����
   UNION�ṹ:  BBPCOMM_LTE_TCVR_ON_CFG_PIN2_UNION */
#define BBPCOMM_LTE_TCVR_ON_CFG_PIN2_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x1044)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    �������Wģtcvr_on�źſ�����Χ
             tcvr_on��pin��2�ź����
             ����1Ϊ���ߣ�0Ϊ����
   UNION�ṹ:  BBPCOMM_W_TCVR_ON_CFG_PIN2_UNION */
#define BBPCOMM_W_TCVR_ON_CFG_PIN2_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x1048)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    �������TDSģtcvr_on�źſ�����Χ
             tcvr_on��pin��2�ź����
             ����1Ϊ���ߣ�0Ϊ����
   UNION�ṹ:  BBPCOMM_TDS_TCVR_ON_CFG_PIN2_UNION */
#define BBPCOMM_TDS_TCVR_ON_CFG_PIN2_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x104C)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    �������GMģtcvr_on�źſ�����Χ
             tcvr_on��pin��2�ź����
             ����1Ϊ���ߣ�0Ϊ����
   UNION�ṹ:  BBPCOMM_GM_TCVR_ON_CFG_PIN2_UNION */
#define BBPCOMM_GM_TCVR_ON_CFG_PIN2_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x1050)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    �������GSģtcvr_on�źſ�����Χ
             tcvr_on��pin��2�ź����
             ����1Ϊ���ߣ�0Ϊ����
   UNION�ṹ:  BBPCOMM_GS_TCVR_ON_CFG_PIN2_UNION */
#define BBPCOMM_GS_TCVR_ON_CFG_PIN2_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x1054)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    �������Cģtcvr_on�źſ�����Χ
             tcvr_on��pin��2�ź����
             ����1Ϊ���ߣ�0Ϊ����
   UNION�ṹ:  BBPCOMM_C_TCVR_ON_CFG_PIN2_UNION */
#define BBPCOMM_C_TCVR_ON_CFG_PIN2_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x1058)

/* �Ĵ���˵�����Ĵ���
 bit[31:6]   ����
 bit[5:0]    ��ͨ��ʵ�����tcvr_on�ӳٵ�����ֵ��
             ���֧��64��cycle����λΪ19.2M��
   UNION�ṹ:  BBPCOMM_TCVR_ON_DLY_CYCLE_UNION */
#define BBPCOMM_TCVR_ON_DLY_CYCLE_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x105C)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    tuner mipi�Զ������������μĴ���
             0��ʹ��tuner������
             1��bypass tuner��������tuner mipiָ��ܴ�CTUͨ��0���
   UNION�ṹ:  BBPCOMM_TUNER_MIPI_MSAK_UNION */
#define BBPCOMM_TUNER_MIPI_MSAK_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x1060)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    tuner gpio m0_line_p�߿����μĴ���
             0��ʹ��tuner���ֵ
             1��bypass tuner���ֵ��ʹ��CTU���ֵ
   UNION�ṹ:  BBPCOMM_TUNER_GPIO_M0_LINE_P_MASK_UNION */
#define BBPCOMM_TUNER_GPIO_M0_LINE_P_MASK_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x1064)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    tuner gpio m0_line_s�߿����μĴ���
             0��ʹ��tuner���ֵ
             1��bypass tuner���ֵ��ʹ��CTU���ֵ
   UNION�ṹ:  BBPCOMM_TUNER_GPIO_M0_LINE_S_MASK_UNION */
#define BBPCOMM_TUNER_GPIO_M0_LINE_S_MASK_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x1068)

/* �Ĵ���˵�����Ĵ���
 bit[31:1]   ����
 bit[0:0]    tuner gpio m1_line�߿����μĴ���
             0��ʹ��tuner���ֵ
             1��bypass tuner���ֵ��ʹ��CTU���ֵ
   UNION�ṹ:  BBPCOMM_TUNER_GPIO_M1_LINE_MASK_UNION */
#define BBPCOMM_TUNER_GPIO_M1_LINE_MASK_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x106C)



/***======================================================================***
                     (2/3) register_define_mipi_tuner
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31:5]   
 bit[4]      MIPI_tunerģ��
 bit[3:1]    
 bit[0]      MIPI_TUNERģ��ʹ�ܿ��أ�0��ʾ�رգ�1��ʾ�򿪡�
   UNION�ṹ:  BBPCOMM_MIPI_TUNER_EN_UNION */
#define BBPCOMM_MIPI_TUNER_EN_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x5C00)

/* �Ĵ���˵����
 bit[31:1]   
 bit[0]      MIPI����״̬����ʱ��������ʹ�ܣ�1��ʾ�򿪱������ܣ�0��ʾ�ر�
   UNION�ṹ:  BBPCOMM_FSM_OT_PRT_EN_UNION */
#define BBPCOMM_FSM_OT_PRT_EN_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x5C08)

/* �Ĵ���˵����
 bit[31:16]  
 bit[15:0]   ״̬����ʱ��ʱ��
   UNION�ṹ:  BBPCOMM_MIPI_OT_CNT_UNION */
#define BBPCOMM_MIPI_OT_CNT_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x5C0C)

/* �Ĵ���˵����
 bit[31:3]   
 bit[2]      ��ѯ״̬�ϱ�
 bit[1]      ��ѯ״̬�ϱ�
 bit[0]      ��ѯ״̬�ϱ�
   UNION�ṹ:  BBPCOMM_QUEUE_BUSY_IND_UNION */
#define BBPCOMM_QUEUE_BUSY_IND_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x5C10)

/* �Ĵ���˵����
 bit[31:24]  
 bit[23]     m1 fifo״̬�ϱ�
 bit[22]     m1 fifo״̬�ϱ�
 bit[21:16]  m1��ǰ״ֵ̬
 bit[15]     m0_s fifo״̬�ϱ�
 bit[14]     m0_s fifo״̬�ϱ�
 bit[13:8]   m0_s��ǰ״ֵ̬
 bit[7]      m0_p fifo״̬�ϱ�
 bit[6]      m0_p fifo״̬�ϱ�
 bit[5:0]    m0_p��ǰ״ֵ̬
   UNION�ṹ:  BBPCOMM_M_GEN_RPT_UNION */
#define BBPCOMM_M_GEN_RPT_ADDR                        (SOC_BBP_COMM_BASE_ADDR + 0x5C14)



/***======================================================================***
                     (3/3) register_define_mipi_tuner_mem
 ***======================================================================***/
/* �Ĵ���˵����mipi_RAM0
   ��      ����MIPI������ַΪ0xE1F84000 - 0xE1F851FC
   UNION�ṹ ���� */
#define BBPCOMM_MIPI_LUT_RAM_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x4000)
#define BBPCOMM_MIPI_LUT_RAM_MEMDEPTH  (1152)

/* �Ĵ���˵����mipi_RAM1
   ��      ����GPIO������ַΪ0xE1F85800-0xE1F8585C
   UNION�ṹ ���� */
#define BBPCOMM_GPIO_LUT_RAM_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x5800)
#define BBPCOMM_GPIO_LUT_RAM_MEMDEPTH  (24)





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
                     (1/3) register_define_ctu
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : BBPCOMM_C0_PRIMARY_MODE_IND_UNION
 �ṹ˵��  : C0_PRIMARY_MODE_IND �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000007�����:32
 �Ĵ���˵��: ͨ��0��Ӧ��ģ����ģ0����ģʽָʾ�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c0_primary_mode_ind_reg;
    struct
    {
        unsigned int  c0_primary_mode_ind : 3;  /* bit[0-2] : ͨ��0��Ӧ����ģ������Ϊ��ģ0����ģʽָʾ����ʾLTE��W��Gm��Gs��TDS˭����ģ0��
                                                              000��LTE ��ģ��
                                                              001��W��ģ��
                                                              010��TDS��ģ��
                                                              011��Gm��ģ��
                                                              100��Gs��ģ��
                                                              101:C��ģ��
                                                              110~111����Ч��
                                                              ����ʱ�̣���ģ����ͨ�ų������� */
        unsigned int  reserved            : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_C0_PRIMARY_MODE_IND_UNION;
#define BBPCOMM_C0_PRIMARY_MODE_IND_c0_primary_mode_ind_START  (0)
#define BBPCOMM_C0_PRIMARY_MODE_IND_c0_primary_mode_ind_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C0_SECOND_MODE_IND_UNION
 �ṹ˵��  : C0_SECOND_MODE_IND �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000007�����:32
 �Ĵ���˵��: ��ģ0��Ӧ�Ĵ�ģ����ģ0����ģʽָʾ�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c0_second_mode_ind_reg;
    struct
    {
        unsigned int  c0_second_mode_ind : 3;  /* bit[0-2] : ��ģ0��Ӧ�Ĵ�ģ������Ϊ��ģ0����ģʽָʾ����ʾ��ǰLTE/W/Gm/Gs/TDS˭�Ǵ�ģ0��
                                                             000��LTE��ģ��
                                                             001��W ��ģ��
                                                             010��TDS��ģ��
                                                             011��Gm��ģ��
                                                             100��Gs��ģ��
                                                             101:C��ģ��
                                                             110~111����Ч��
                                                             ����ʱ�̣���ģ����ͨ�ų�������
                                                             ע��Լ����ģ0�̶���ͨ��0����ģ1�̶���ͨ��1�� */
        unsigned int  reserved           : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_C0_SECOND_MODE_IND_UNION;
#define BBPCOMM_C0_SECOND_MODE_IND_c0_second_mode_ind_START  (0)
#define BBPCOMM_C0_SECOND_MODE_IND_c0_second_mode_ind_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C0_AFC_PDM_SELECT_MASK_UNION
 �ṹ˵��  : C0_AFC_PDM_SELECT_MASK �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c0_afc_pdm_select_mask_reg;
    struct
    {
        unsigned int  c0_afc_pdm_select_mask : 3;  /* bit[0-2] : ͨ��0 AFC�����ź���Դ��
                                                                 3'b000������ģ���ƣ�
                                                                 3'b001��ǿ����Lģ���ƣ�
                                                                 3'b010��ǿ����Wģ���ƣ�
                                                                 3'b011��ǿ����TDSģ���ƣ�
                                                                 3'b100��ǿ����Gmģ���ƣ�
                                                                 3'b101��ǿ����Gsģ���ƣ�
                                                                 3'b110��ǿ����Cģ���ƣ�
                                                                 3'b111����Ч��
                                                                 �����á� */
        unsigned int  reserved               : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_C0_AFC_PDM_SELECT_MASK_UNION;
#define BBPCOMM_C0_AFC_PDM_SELECT_MASK_c0_afc_pdm_select_mask_START  (0)
#define BBPCOMM_C0_AFC_PDM_SELECT_MASK_c0_afc_pdm_select_mask_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C0_ANT_SWITCH_PA_SELECT_MASK_UNION
 �ṹ˵��  : C0_ANT_SWITCH_PA_SELECT_MASK �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c0_ant_switch_pa_select_mask_reg;
    struct
    {
        unsigned int  c0_ant_switch_pa_select_mask : 3;  /* bit[0-2] : ͨ��0 ���߿��غ�PA�����ź���Դ��
                                                                       3'b000������ģ���ƣ�
                                                                       3'b001��ǿ����Lģ���ƣ�
                                                                       3'b010��ǿ����Wģ���ƣ�
                                                                       3'b011��ǿ����TDSģ���ƣ�
                                                                       3'b100��ǿ����Gmģ���ƣ�
                                                                       3'b101��ǿ����Gsģ���ƣ�
                                                                       3'b110��ǿ����Cģ���ƣ�
                                                                       3'b111����Ч��
                                                                       �����á� */
        unsigned int  reserved                     : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_C0_ANT_SWITCH_PA_SELECT_MASK_UNION;
#define BBPCOMM_C0_ANT_SWITCH_PA_SELECT_MASK_c0_ant_switch_pa_select_mask_START  (0)
#define BBPCOMM_C0_ANT_SWITCH_PA_SELECT_MASK_c0_ant_switch_pa_select_mask_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C0_RFIC_SELECT_MASK_UNION
 �ṹ˵��  : C0_RFIC_SELECT_MASK �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c0_rfic_select_mask_reg;
    struct
    {
        unsigned int  c0_rfic_select_mask : 3;  /* bit[0-2] : ͨ��0 RFIC�����ź���Դ�������߿غ�SSI����
                                                              3'b000������ģ���ƣ�
                                                              3'b001��ǿ����Lģ���ƣ�
                                                              3'b010��ǿ����Wģ���ƣ�
                                                              3'b011��ǿ����TDSģ���ƣ�
                                                              3'b100��ǿ����Gmģ���ƣ�
                                                              3'b101��ǿ����Gsģ���ƣ�
                                                              3'b110��ǿ����Cģ���ƣ�
                                                              3'b111����Ч��
                                                              �����á� */
        unsigned int  reserved            : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_C0_RFIC_SELECT_MASK_UNION;
#define BBPCOMM_C0_RFIC_SELECT_MASK_c0_rfic_select_mask_START  (0)
#define BBPCOMM_C0_RFIC_SELECT_MASK_c0_rfic_select_mask_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C0_MIPI_SELECT_MASK_UNION
 �ṹ˵��  : C0_MIPI_SELECT_MASK �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c0_mipi_select_mask_reg;
    struct
    {
        unsigned int  c0_mipi_select_mask : 3;  /* bit[0-2] : ͨ��0 MIPI�����ź���Դ��
                                                              3'b000������ģ���ƣ�
                                                              3'b001��ǿ����Lģ���ƣ�
                                                              3'b010��ǿ����Wģ���ƣ�
                                                              3'b011��ǿ����TDSģ���ƣ�
                                                              3'b100��ǿ����Gmģ���ƣ�
                                                              3'b101��ǿ����Gsģ���ƣ�
                                                              3'b110��ǿ����Cģ���ƣ�
                                                              ��������Ч��
                                                              �����á� */
        unsigned int  reserved            : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_C0_MIPI_SELECT_MASK_UNION;
#define BBPCOMM_C0_MIPI_SELECT_MASK_c0_mipi_select_mask_START  (0)
#define BBPCOMM_C0_MIPI_SELECT_MASK_c0_mipi_select_mask_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C0_ABB_SELECT_MASK_UNION
 �ṹ˵��  : C0_ABB_SELECT_MASK �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c0_abb_select_mask_reg;
    struct
    {
        unsigned int  c0_abb_select_mask : 3;  /* bit[0-2] : ͨ��0 ABB�����ź���Դ��
                                                             3'b000������ģ���ƣ�
                                                             3'b001��ǿ����Lģ���ƣ�
                                                             3'b010��ǿ����Wģ���ƣ�
                                                             3'b011��ǿ����TDSģ���ƣ�
                                                             3'b100��ǿ����Gmģ���ƣ�
                                                             3'b101��ǿ����Gsģ���ƣ�
                                                             3'b110��ǿ����Cģ���ƣ�
                                                             ��������Ч��
                                                             �����á� */
        unsigned int  reserved           : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_C0_ABB_SELECT_MASK_UNION;
#define BBPCOMM_C0_ABB_SELECT_MASK_c0_abb_select_mask_START  (0)
#define BBPCOMM_C0_ABB_SELECT_MASK_c0_abb_select_mask_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C0_PMU_SELECT_MASK_UNION
 �ṹ˵��  : C0_PMU_SELECT_MASK �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c0_pmu_select_mask_reg;
    struct
    {
        unsigned int  c0_pmu_select_mask : 3;  /* bit[0-2] : ͨ��0 PMU�����ź���Դ��
                                                             3'b000������ģ���ƣ�
                                                             3'b001��ǿ����Lģ���ƣ�
                                                             3'b010��ǿ����Wģ���ƣ�
                                                             3'b011��ǿ����TDSģ���ƣ�
                                                             3'b100��ǿ����Gmģ���ƣ�
                                                             3'b101��ǿ����Gsģ���ƣ�
                                                             3'b110��ǿ����Cģ���ƣ�
                                                             3'b111����Ч��
                                                             �����á� */
        unsigned int  reserved           : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_C0_PMU_SELECT_MASK_UNION;
#define BBPCOMM_C0_PMU_SELECT_MASK_c0_pmu_select_mask_START  (0)
#define BBPCOMM_C0_PMU_SELECT_MASK_c0_pmu_select_mask_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_DSP_C0_SEL_MASK_UNION
 �ṹ˵��  : DSP_C0_SEL_MASK �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dsp_c0_sel_mask_reg;
    struct
    {
        unsigned int  dsp_c0_sel_mask : 3;  /* bit[0-2] : ��ǰͨ��0������֮ǰ�������ǿ��ģʽ��
                                                          ע���������ڸ�����Χ������ABB��RF��PA��mipi�ȣ������Ľ���ǿ�䡣
                                                          �����á� */
        unsigned int  reserved        : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_DSP_C0_SEL_MASK_UNION;
#define BBPCOMM_DSP_C0_SEL_MASK_dsp_c0_sel_mask_START  (0)
#define BBPCOMM_DSP_C0_SEL_MASK_dsp_c0_sel_mask_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_DSP_RFIC0_RSTN_UNION
 �ṹ˵��  : DSP_RFIC0_RSTN �Ĵ����ṹ���塣��ַƫ����:0x002C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dsp_rfic0_rstn_reg;
    struct
    {
        unsigned int  dsp_rfic0_rstn : 1;  /* bit[0-0] : ������õ�RFIC0��λ�źţ�����Ч��
                                                         0����λ��1���⸴λ��
                                                         �ϵ��ʼ������Ϊ0������RFIC�ֲ�Ҫ��ά��һ��ʱ�������Ϊ1��
                                                         V3R3���üĴ������ܸ��ڼĴ���0x0334��bit[8]ʵ�֣�Ĭ��ֵ��Ϊ0���˴�ɾ����
                                                         V7R2��λֵΪ0��
                                                         V8R1���üĴ�������ɾ���� */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_DSP_RFIC0_RSTN_UNION;
#define BBPCOMM_DSP_RFIC0_RSTN_dsp_rfic0_rstn_START  (0)
#define BBPCOMM_DSP_RFIC0_RSTN_dsp_rfic0_rstn_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C0_SECOND_AFC_MODE_UNION
 �ṹ˵��  : C0_SECOND_AFC_MODE �Ĵ����ṹ���塣��ַƫ����:0x0030����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c0_second_afc_mode_reg;
    struct
    {
        unsigned int  c0_second_afc_mode : 1;  /* bit[0]   : 0:ͨ��0��ģʹ��ͨ��0��ģafc������
                                                             1:ͨ��0��ģʹ��ͨ��0��ģafc������ */
        unsigned int  reserved           : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_C0_SECOND_AFC_MODE_UNION;
#define BBPCOMM_C0_SECOND_AFC_MODE_c0_second_afc_mode_START  (0)
#define BBPCOMM_C0_SECOND_AFC_MODE_c0_second_afc_mode_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_MIPI0_RD_OVERTIME_FLAG_DSP_UNION
 �ṹ˵��  : MIPI0_RD_OVERTIME_FLAG_DSP �Ĵ����ṹ���塣��ַƫ����:0x0038����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      mipi0_rd_overtime_flag_dsp_reg;
    struct
    {
        unsigned int  mipi0_rd_overtime_flag_dsp : 1;  /* bit[0]   : DSP�ȴ��ض������ʱ��־λ
                                                                     1:��ʱ   */
        unsigned int  reserved                   : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_MIPI0_RD_OVERTIME_FLAG_DSP_UNION;
#define BBPCOMM_MIPI0_RD_OVERTIME_FLAG_DSP_mipi0_rd_overtime_flag_dsp_START  (0)
#define BBPCOMM_MIPI0_RD_OVERTIME_FLAG_DSP_mipi0_rd_overtime_flag_dsp_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_SSI0_RD_OVERTIME_FLAG_DSP_UNION
 �ṹ˵��  : SSI0_RD_OVERTIME_FLAG_DSP �Ĵ����ṹ���塣��ַƫ����:0x003C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      ssi0_rd_overtime_flag_dsp_reg;
    struct
    {
        unsigned int  ssi0_rd_overtime_flag_dsp : 1;  /* bit[0]   : DSP�ȴ��ض������ʱ��־λ
                                                                    1:��ʱ   */
        unsigned int  reserved                  : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_SSI0_RD_OVERTIME_FLAG_DSP_UNION;
#define BBPCOMM_SSI0_RD_OVERTIME_FLAG_DSP_ssi0_rd_overtime_flag_dsp_START  (0)
#define BBPCOMM_SSI0_RD_OVERTIME_FLAG_DSP_ssi0_rd_overtime_flag_dsp_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_MIPI0_RD_OVERTIME_CLR_UNION
 �ṹ˵��  : MIPI0_RD_OVERTIME_CLR �Ĵ����ṹ���塣��ַƫ����:0x0040����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      mipi0_rd_overtime_clr_reg;
    struct
    {
        unsigned int  mipi0_rd_overtime_clr_imi : 1;  /* bit[0]   : DSP�ȴ��ض������ʱ��,�峭ʱ��־λ���� */
        unsigned int  reserved                  : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_MIPI0_RD_OVERTIME_CLR_UNION;
#define BBPCOMM_MIPI0_RD_OVERTIME_CLR_mipi0_rd_overtime_clr_imi_START  (0)
#define BBPCOMM_MIPI0_RD_OVERTIME_CLR_mipi0_rd_overtime_clr_imi_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_SSI0_RD_OVERTIME_CLR_UNION
 �ṹ˵��  : SSI0_RD_OVERTIME_CLR �Ĵ����ṹ���塣��ַƫ����:0x0044����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      ssi0_rd_overtime_clr_reg;
    struct
    {
        unsigned int  ssi0_rd_overtime_clr_imi : 1;  /* bit[0]   : DSP�ȴ��ض������ʱ��,�峭ʱ��־λ���� */
        unsigned int  reserved                 : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_SSI0_RD_OVERTIME_CLR_UNION;
#define BBPCOMM_SSI0_RD_OVERTIME_CLR_ssi0_rd_overtime_clr_imi_START  (0)
#define BBPCOMM_SSI0_RD_OVERTIME_CLR_ssi0_rd_overtime_clr_imi_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_RD_RESULT_FLAG_RFIC0_UNION
 �ṹ˵��  : RD_RESULT_FLAG_RFIC0 �Ĵ����ṹ���塣��ַƫ����:0x0088����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_rfic0_reg;
    struct
    {
        unsigned int  rd_result_flag_rfic0 : 1;  /* bit[0]   : ���лض�ָ��ִ�����,����ȡ�߻ض�����
                                                               1:���лض�ָ������,DSP���԰�λ�ö�ȡSSI�ض���� */
        unsigned int  reserved             : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_RFIC0_UNION;
#define BBPCOMM_RD_RESULT_FLAG_RFIC0_rd_result_flag_rfic0_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_RFIC0_rd_result_flag_rfic0_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_RD_RESULT_FLAG_RFIC0_CLR_UNION
 �ṹ˵��  : RD_RESULT_FLAG_RFIC0_CLR �Ĵ����ṹ���塣��ַƫ����:0x008C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_rfic0_clr_reg;
    struct
    {
        unsigned int  rd_result_flag_rfic0_clr : 1;  /* bit[0]   : 1:DSPȡ�����лض����ݺ�,д��clr�ź����־λ */
        unsigned int  reserved                 : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_RFIC0_CLR_UNION;
#define BBPCOMM_RD_RESULT_FLAG_RFIC0_CLR_rd_result_flag_rfic0_clr_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_RFIC0_CLR_rd_result_flag_rfic0_clr_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_RD_RESULT_FLAG_MIPI0_UNION
 �ṹ˵��  : RD_RESULT_FLAG_MIPI0 �Ĵ����ṹ���塣��ַƫ����:0x00D0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_mipi0_reg;
    struct
    {
        unsigned int  rd_result_flag_mipi0 : 1;  /* bit[0]   : ���лض�ָ��ִ�����,����ȡ�߻ض�����
                                                               1:���лض�ָ������,DSP���԰�λ�ö�ȡSSI�ض����,�����������ֱ�ӿ���MIPI��־λ��ͬ */
        unsigned int  reserved             : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_MIPI0_UNION;
#define BBPCOMM_RD_RESULT_FLAG_MIPI0_rd_result_flag_mipi0_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_MIPI0_rd_result_flag_mipi0_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_RD_RESULT_FLAG_MIPI0_CLR_UNION
 �ṹ˵��  : RD_RESULT_FLAG_MIPI0_CLR �Ĵ����ṹ���塣��ַƫ����:0x00D4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_mipi0_clr_reg;
    struct
    {
        unsigned int  rd_result_flag_mipi0_clr : 1;  /* bit[0]   : 1:DSPȡ�����лض����ݺ�,д��clr�ź����־λ,�����������ֱ�ӿ���MIPI��־λ��ͬ */
        unsigned int  reserved                 : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_MIPI0_CLR_UNION;
#define BBPCOMM_RD_RESULT_FLAG_MIPI0_CLR_rd_result_flag_mipi0_clr_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_MIPI0_CLR_rd_result_flag_mipi0_clr_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_RD_END_FLAG_MIPI0_SOFT_UNION
 �ṹ˵��  : RD_END_FLAG_MIPI0_SOFT �Ĵ����ṹ���塣��ַƫ����:0x00E0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      rd_end_flag_mipi0_soft_reg;
    struct
    {
        unsigned int  rd_end_flag_mipi0_soft : 1;  /* bit[0]   : �����ֱ�ӿ���MIPI0 master,������xbbp���ͻض�ָ��ʱ,�ض�������Чָʾ */
        unsigned int  reserved               : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_RD_END_FLAG_MIPI0_SOFT_UNION;
#define BBPCOMM_RD_END_FLAG_MIPI0_SOFT_rd_end_flag_mipi0_soft_START  (0)
#define BBPCOMM_RD_END_FLAG_MIPI0_SOFT_rd_end_flag_mipi0_soft_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_MIPI0_GRANT_DSP_UNION
 �ṹ˵��  : MIPI0_GRANT_DSP �Ĵ����ṹ���塣��ַƫ����:0x00E4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      mipi0_grant_dsp_reg;
    struct
    {
        unsigned int  mipi0_grant_dsp : 1;  /* bit[0]   : �����ֱ�ӿ���MIPI0 master
                                                          1:������Է���CFG_IND����mipi0
                                                          0:����ȴ�mipi0��Ȩʹ�� */
        unsigned int  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_MIPI0_GRANT_DSP_UNION;
#define BBPCOMM_MIPI0_GRANT_DSP_mipi0_grant_dsp_START  (0)
#define BBPCOMM_MIPI0_GRANT_DSP_mipi0_grant_dsp_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_DSP_MIPI0_EN_IMI_UNION
 �ṹ˵��  : DSP_MIPI0_EN_IMI �Ĵ����ṹ���塣��ַƫ����:0x00F0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dsp_mipi0_en_imi_reg;
    struct
    {
        unsigned int  dsp_mipi0_en_imi : 1;  /* bit[0]   : �����ֱ�ӿ���MIPI0 master,���������ߴ�ָʾ,����xbbp��MIPI0�Ŀ��� */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_DSP_MIPI0_EN_IMI_UNION;
#define BBPCOMM_DSP_MIPI0_EN_IMI_dsp_mipi0_en_imi_START  (0)
#define BBPCOMM_DSP_MIPI0_EN_IMI_dsp_mipi0_en_imi_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_DSP_MIPI0_CFG_IND_IMI_UNION
 �ṹ˵��  : DSP_MIPI0_CFG_IND_IMI �Ĵ����ṹ���塣��ַƫ����:0x00F4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dsp_mipi0_cfg_ind_imi_reg;
    struct
    {
        unsigned int  dsp_mipi0_cfg_ind_imi : 1;  /* bit[0]   : �����ֱ�ӿ���MIPI0 master,���ߴ�dsp_mipi0_en��,��������������� */
        unsigned int  reserved              : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_DSP_MIPI0_CFG_IND_IMI_UNION;
#define BBPCOMM_DSP_MIPI0_CFG_IND_IMI_dsp_mipi0_cfg_ind_imi_START  (0)
#define BBPCOMM_DSP_MIPI0_CFG_IND_IMI_dsp_mipi0_cfg_ind_imi_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_DSP_MIPI0_RD_CLR_UNION
 �ṹ˵��  : DSP_MIPI0_RD_CLR �Ĵ����ṹ���塣��ַƫ����:0x00F8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dsp_mipi0_rd_clr_reg;
    struct
    {
        unsigned int  dsp_mipi0_rd_clr : 1;  /* bit[0]   : �����ֱ�ӿ���MIPI0 master,ȡ�߻ض����ݺ�,���־λ���� */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_DSP_MIPI0_RD_CLR_UNION;
#define BBPCOMM_DSP_MIPI0_RD_CLR_dsp_mipi0_rd_clr_START  (0)
#define BBPCOMM_DSP_MIPI0_RD_CLR_dsp_mipi0_rd_clr_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_ABB0_LINE_CONTROL_CMD_UNION
 �ṹ˵��  : ABB0_LINE_CONTROL_CMD �Ĵ����ṹ���塣��ַƫ����:0x00FC����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      abb0_line_control_cmd_reg;
    struct
    {
        unsigned int  abb0_line_control_cmd_sel : 1;  /* bit[0-0] : ABB0�߿�ǿ��ģʽ��
                                                                    1����ʾ���ǿ�䣬��ʱ��������ǿ�����Ч��
                                                                    0����ʾ��CTU���ݸ�BBP������
                                                                    Ĭ��ֵΪ0��
                                                                    �����á� */
        unsigned int  abb0_mode_sel_cmd         : 3;  /* bit[1-3] : ���ǿ��ģʽabb0_mode_sel. */
        unsigned int  abb0_tx_en_cmd            : 1;  /* bit[4-4] : ���ǿ��ģʽabb0_tx_en. */
        unsigned int  abb0_rxa_en_cmd           : 1;  /* bit[5-5] : ���ǿ��ģʽabb0_rxa_en. */
        unsigned int  abb0_rxb_en_cmd           : 1;  /* bit[6-6] : ���ǿ��ģʽabb0_rxb_en. */
        unsigned int  abb0_blka_en_cmd          : 1;  /* bit[7-7] : ���ǿ��ģʽabb0_rxa_blk_en. */
        unsigned int  abb0_blkb_en_cmd          : 1;  /* bit[8-8] : ���ǿ��ģʽabb0_rxb_blk_en. */
        unsigned int  reserved                  : 23; /* bit[9-31]: ���� */
    } reg;
} BBPCOMM_ABB0_LINE_CONTROL_CMD_UNION;
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_abb0_line_control_cmd_sel_START  (0)
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_abb0_line_control_cmd_sel_END    (0)
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_abb0_mode_sel_cmd_START          (1)
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_abb0_mode_sel_cmd_END            (3)
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_abb0_tx_en_cmd_START             (4)
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_abb0_tx_en_cmd_END               (4)
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_abb0_rxa_en_cmd_START            (5)
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_abb0_rxa_en_cmd_END              (5)
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_abb0_rxb_en_cmd_START            (6)
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_abb0_rxb_en_cmd_END              (6)
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_abb0_blka_en_cmd_START           (7)
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_abb0_blka_en_cmd_END             (7)
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_abb0_blkb_en_cmd_START           (8)
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_abb0_blkb_en_cmd_END             (8)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CH0_BBP_SEL_UNION
 �ṹ˵��  : CH0_BBP_SEL �Ĵ����ṹ���塣��ַƫ����:0x0100����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      ch0_bbp_sel_reg;
    struct
    {
        unsigned int  ch0_bbp_sel : 3;  /* bit[0-2] : V9R1�汾����������á� */
        unsigned int  reserved    : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_CH0_BBP_SEL_UNION;
#define BBPCOMM_CH0_BBP_SEL_ch0_bbp_sel_START  (0)
#define BBPCOMM_CH0_BBP_SEL_ch0_bbp_sel_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_MIPI0_FUNC_SEL_UNION
 �ṹ˵��  : CPU_MIPI0_FUNC_SEL �Ĵ����ṹ���塣��ַƫ����:0x0104����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi0_func_sel_reg;
    struct
    {
        unsigned int  cpu_mipi0_func_sel : 1;  /* bit[0]   : cpu����mipi����,����Ϊ1������������, ����ʱ����Ϊ0 */
        unsigned int  reserved           : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_CPU_MIPI0_FUNC_SEL_UNION;
#define BBPCOMM_CPU_MIPI0_FUNC_SEL_cpu_mipi0_func_sel_START  (0)
#define BBPCOMM_CPU_MIPI0_FUNC_SEL_cpu_mipi0_func_sel_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_MIPI0_TEST_FUNC_UNION
 �ṹ˵��  : CPU_MIPI0_TEST_FUNC �Ĵ����ṹ���塣��ַƫ����:0x0108����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi0_test_func_reg;
    struct
    {
        unsigned int  cpu_mipi0_test_func : 1;  /* bit[0]   : cpu����mipi����,������ */
        unsigned int  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_CPU_MIPI0_TEST_FUNC_UNION;
#define BBPCOMM_CPU_MIPI0_TEST_FUNC_cpu_mipi0_test_func_START  (0)
#define BBPCOMM_CPU_MIPI0_TEST_FUNC_cpu_mipi0_test_func_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_MIPI0_SCLK_TEST_UNION
 �ṹ˵��  : CPU_MIPI0_SCLK_TEST �Ĵ����ṹ���塣��ַƫ����:0x010C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi0_sclk_test_reg;
    struct
    {
        unsigned int  cpu_mipi0_sclk_test : 1;  /* bit[0]   : cpu����mipi����, ������ */
        unsigned int  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_CPU_MIPI0_SCLK_TEST_UNION;
#define BBPCOMM_CPU_MIPI0_SCLK_TEST_cpu_mipi0_sclk_test_START  (0)
#define BBPCOMM_CPU_MIPI0_SCLK_TEST_cpu_mipi0_sclk_test_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_MIPI0_SDATA_TEST_UNION
 �ṹ˵��  : CPU_MIPI0_SDATA_TEST �Ĵ����ṹ���塣��ַƫ����:0x0110����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi0_sdata_test_reg;
    struct
    {
        unsigned int  cpu_mipi0_sdata_test : 1;  /* bit[0]   : cpu����mipi����, ������ */
        unsigned int  reserved             : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_CPU_MIPI0_SDATA_TEST_UNION;
#define BBPCOMM_CPU_MIPI0_SDATA_TEST_cpu_mipi0_sdata_test_START  (0)
#define BBPCOMM_CPU_MIPI0_SDATA_TEST_cpu_mipi0_sdata_test_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_DSP_MIPI0_CLR_IND_IMI_UNION
 �ṹ˵��  : DSP_MIPI0_CLR_IND_IMI �Ĵ����ṹ���塣��ַƫ����:0x0114����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      dsp_mipi0_clr_ind_imi_reg;
    struct
    {
        unsigned int  dsp_mipi0_clr_ind_imi : 1;  /* bit[0]   : cpu����mipi����,mipi0master���쳣�ź� */
        unsigned int  reserved              : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_DSP_MIPI0_CLR_IND_IMI_UNION;
#define BBPCOMM_DSP_MIPI0_CLR_IND_IMI_dsp_mipi0_clr_ind_imi_START  (0)
#define BBPCOMM_DSP_MIPI0_CLR_IND_IMI_dsp_mipi0_clr_ind_imi_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_MIPI0_FIFO_CLR_IMI_UNION
 �ṹ˵��  : CPU_MIPI0_FIFO_CLR_IMI �Ĵ����ṹ���塣��ַƫ����:0x0118����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi0_fifo_clr_imi_reg;
    struct
    {
        unsigned int  cpu_mipi0_fifo_clr_imi : 1;  /* bit[0]   : mipi0�洢����������ͬ��FIFO��λ�ź� */
        unsigned int  reserved               : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_CPU_MIPI0_FIFO_CLR_IMI_UNION;
#define BBPCOMM_CPU_MIPI0_FIFO_CLR_IMI_cpu_mipi0_fifo_clr_imi_START  (0)
#define BBPCOMM_CPU_MIPI0_FIFO_CLR_IMI_cpu_mipi0_fifo_clr_imi_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_SSI0_FIFO_CLR_IMI_UNION
 �ṹ˵��  : CPU_SSI0_FIFO_CLR_IMI �Ĵ����ṹ���塣��ַƫ����:0x011C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_ssi0_fifo_clr_imi_reg;
    struct
    {
        unsigned int  cpu_ssi0_fifo_clr_imi : 1;  /* bit[0]   : ssi0�洢����������ͬ��FIFO��λ�ź� */
        unsigned int  reserved              : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_CPU_SSI0_FIFO_CLR_IMI_UNION;
#define BBPCOMM_CPU_SSI0_FIFO_CLR_IMI_cpu_ssi0_fifo_clr_imi_START  (0)
#define BBPCOMM_CPU_SSI0_FIFO_CLR_IMI_cpu_ssi0_fifo_clr_imi_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_UNION
 �ṹ˵��  : CPU_RX0_TX0_CKG_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x0120����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_rx0_tx0_ckg_bypass_reg;
    struct
    {
        unsigned int  cpu_rx0_lte_ckg_bypass : 1;  /* bit[0]    : Lģͨ��0 RX ABB��·ʱ���ſ���·�ź� */
        unsigned int  cpu_rx0_tds_ckg_bypass : 1;  /* bit[1]    : TDSͨ��0 RX ABB��·ʱ���ſ���·�ź� */
        unsigned int  cpu_rx0_w_ckg_bypass   : 1;  /* bit[2]    : Wģͨ��0 RX ABB��·ʱ���ſ���·�ź� */
        unsigned int  cpu_rx0_g1_ckg_bypass  : 1;  /* bit[3]    : G1ͨ��0 RX ABB��·ʱ���ſ���·�ź� */
        unsigned int  cpu_rx0_g2_ckg_bypass  : 1;  /* bit[4]    : G2ͨ��0 RX ABB��·ʱ���ſ���·�ź� */
        unsigned int  cpu_tx0_lte_ckg_bypass : 1;  /* bit[5]    : Lģͨ��0 TX ABB��·ʱ���ſ���·�ź� */
        unsigned int  cpu_tx0_tds_ckg_bypass : 1;  /* bit[6]    : TDSͨ��0 TX ABB��·ʱ���ſ���·�ź� */
        unsigned int  cpu_tx0_w_ckg_bypass   : 1;  /* bit[7]    : Wģͨ��0 TX ABB��·ʱ���ſ���·�ź� */
        unsigned int  cpu_tx0_g1_ckg_bypass  : 1;  /* bit[8]    : G1ͨ��0 TX ABB��·ʱ���ſ���·�ź� */
        unsigned int  cpu_tx0_g2_ckg_bypass  : 1;  /* bit[9]    : G2ͨ��0 TX ABB��·ʱ���ſ���·�ź� */
        unsigned int  cpu_rx0_c_ckg_bypass   : 1;  /* bit[10]   : Cģͨ��0 RX ABB��·ʱ���ſ���·�ź� */
        unsigned int  cpu_tx0_c_ckg_bypass   : 1;  /* bit[11]   : Cģͨ��0 TX ABB��·ʱ���ſ���·�ź� */
        unsigned int  reserved               : 20; /* bit[12-31]: ���� */
    } reg;
} BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_UNION;
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_rx0_lte_ckg_bypass_START  (0)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_rx0_lte_ckg_bypass_END    (0)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_rx0_tds_ckg_bypass_START  (1)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_rx0_tds_ckg_bypass_END    (1)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_rx0_w_ckg_bypass_START    (2)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_rx0_w_ckg_bypass_END      (2)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_rx0_g1_ckg_bypass_START   (3)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_rx0_g1_ckg_bypass_END     (3)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_rx0_g2_ckg_bypass_START   (4)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_rx0_g2_ckg_bypass_END     (4)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_tx0_lte_ckg_bypass_START  (5)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_tx0_lte_ckg_bypass_END    (5)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_tx0_tds_ckg_bypass_START  (6)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_tx0_tds_ckg_bypass_END    (6)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_tx0_w_ckg_bypass_START    (7)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_tx0_w_ckg_bypass_END      (7)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_tx0_g1_ckg_bypass_START   (8)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_tx0_g1_ckg_bypass_END     (8)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_tx0_g2_ckg_bypass_START   (9)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_tx0_g2_ckg_bypass_END     (9)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_rx0_c_ckg_bypass_START    (10)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_rx0_c_ckg_bypass_END      (10)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_tx0_c_ckg_bypass_START    (11)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_tx0_c_ckg_bypass_END      (11)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C1_PRIMARY_MODE_IND_UNION
 �ṹ˵��  : C1_PRIMARY_MODE_IND �Ĵ����ṹ���塣��ַƫ����:0x0300����ֵ:0x00000007�����:32
 �Ĵ���˵��: ͨ��1��Ӧ��ģ����ģ1����ģʽָʾ�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c1_primary_mode_ind_reg;
    struct
    {
        unsigned int  c1_primary_mode_ind : 3;  /* bit[0-2] : ͨ��1��Ӧ����ģ������Ϊ��ģ1����ģʽָʾ����ʾLTE��W��Gm��Gs��TDS˭����ģ1��
                                                              000��LTE ��ģ��
                                                              001��W��ģ��
                                                              010��TDS��ģ��
                                                              011��Gm��ģ��
                                                              100��Gs��ģ��
                                                              101��C��ģ��
                                                              110~111����Ч��
                                                              ����ʱ�̣���ģ����ͨ�ų������� */
        unsigned int  reserved            : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_C1_PRIMARY_MODE_IND_UNION;
#define BBPCOMM_C1_PRIMARY_MODE_IND_c1_primary_mode_ind_START  (0)
#define BBPCOMM_C1_PRIMARY_MODE_IND_c1_primary_mode_ind_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C1_SECOND_MODE_IND_UNION
 �ṹ˵��  : C1_SECOND_MODE_IND �Ĵ����ṹ���塣��ַƫ����:0x0304����ֵ:0x00000007�����:32
 �Ĵ���˵��: ��ģ1��Ӧ�Ĵ�ģ����ģ1����ģʽָʾ�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c1_second_mode_ind_reg;
    struct
    {
        unsigned int  c1_second_mode_ind : 3;  /* bit[0-2] : ��ģ1��Ӧ�Ĵ�ģ������Ϊ��ģ1����ģʽָʾ����ʾLTE/W/Gm/Gs/TDS˭�Ǵ�ģ1��
                                                             000��LTE��ģ��
                                                             001��W ��ģ��
                                                             010��TDS��ģ��
                                                             011��Gm��ģ��
                                                             100��Gs��ģ��
                                                             101��C��ģ��
                                                             110~111����Ч��
                                                             ����ʱ�̣���ģ����ͨ�ų�������.
                                                             ע��Լ����ģ0�̶���ͨ��0����ģ1�̶���ͨ��1�� */
        unsigned int  reserved           : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_C1_SECOND_MODE_IND_UNION;
#define BBPCOMM_C1_SECOND_MODE_IND_c1_second_mode_ind_START  (0)
#define BBPCOMM_C1_SECOND_MODE_IND_c1_second_mode_ind_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C1_AFC_PDM_SELECT_MASK_UNION
 �ṹ˵��  : C1_AFC_PDM_SELECT_MASK �Ĵ����ṹ���塣��ַƫ����:0x0310����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c1_afc_pdm_select_mask_reg;
    struct
    {
        unsigned int  c1_afc_pdm_select_mask : 3;  /* bit[0-2] : ͨ��1 AFC�����ź���Դ��
                                                                 3'b000������ģ���ƣ�
                                                                 3'b001��ǿ����Lģ���ƣ�
                                                                 3'b010��ǿ����Wģ���ƣ�
                                                                 3'b011��ǿ����TDSģ���ƣ�
                                                                 3'b100��ǿ����Gmģ���ƣ�
                                                                 3'b101��ǿ����Gsģ���ƣ�
                                                                 3'b110��ǿ����Cģ���ƣ�
                                                                 3'b111����Ч��
                                                                 �����á� */
        unsigned int  reserved               : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_C1_AFC_PDM_SELECT_MASK_UNION;
#define BBPCOMM_C1_AFC_PDM_SELECT_MASK_c1_afc_pdm_select_mask_START  (0)
#define BBPCOMM_C1_AFC_PDM_SELECT_MASK_c1_afc_pdm_select_mask_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C1_ANT_SWITCH_PA_SELECT_MASK_UNION
 �ṹ˵��  : C1_ANT_SWITCH_PA_SELECT_MASK �Ĵ����ṹ���塣��ַƫ����:0x0314����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c1_ant_switch_pa_select_mask_reg;
    struct
    {
        unsigned int  c1_ant_switch_pa_select_mask : 3;  /* bit[0-2] : ͨ��1 ���߿��غ�PA�����ź���Դ��
                                                                       3'b000������ģ���ƣ�
                                                                       3'b001��ǿ����Lģ���ƣ�
                                                                       3'b010��ǿ����Wģ���ƣ�
                                                                       3'b011��ǿ����TDSģ���ƣ�
                                                                       3'b100��ǿ����Gmģ���ƣ�
                                                                       3'b101��ǿ����Gsģ���ƣ�
                                                                       3'b110��ǿ����Cģ���ƣ�
                                                                       3'b111����Ч��
                                                                       �����á� */
        unsigned int  reserved                     : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_C1_ANT_SWITCH_PA_SELECT_MASK_UNION;
#define BBPCOMM_C1_ANT_SWITCH_PA_SELECT_MASK_c1_ant_switch_pa_select_mask_START  (0)
#define BBPCOMM_C1_ANT_SWITCH_PA_SELECT_MASK_c1_ant_switch_pa_select_mask_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C1_RFIC_SELECT_MASK_UNION
 �ṹ˵��  : C1_RFIC_SELECT_MASK �Ĵ����ṹ���塣��ַƫ����:0x0318����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c1_rfic_select_mask_reg;
    struct
    {
        unsigned int  c1_rfic_select_mask : 3;  /* bit[0-2] : ͨ��1 RFIC�����ź���Դ�������߿غ�SSI����
                                                              3'b000������ģ���ƣ�
                                                              3'b001��ǿ����Lģ���ƣ�
                                                              3'b010��ǿ����Wģ���ƣ�
                                                              3'b011��ǿ����TDSģ���ƣ�
                                                              3'b100��ǿ����Gmģ���ƣ�
                                                              3'b101��ǿ����Gsģ���ƣ�
                                                              3'b110��ǿ����Cģ���ƣ�
                                                              3'b111����Ч��
                                                              �����á� */
        unsigned int  reserved            : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_C1_RFIC_SELECT_MASK_UNION;
#define BBPCOMM_C1_RFIC_SELECT_MASK_c1_rfic_select_mask_START  (0)
#define BBPCOMM_C1_RFIC_SELECT_MASK_c1_rfic_select_mask_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C1_MIPI_SELECT_MASK_UNION
 �ṹ˵��  : C1_MIPI_SELECT_MASK �Ĵ����ṹ���塣��ַƫ����:0x031C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c1_mipi_select_mask_reg;
    struct
    {
        unsigned int  c1_mipi_select_mask : 3;  /* bit[0-2] : ͨ��1 MIPI�����ź���Դ��
                                                              3'b000������ģ���ƣ�
                                                              3'b001��ǿ����Lģ���ƣ�
                                                              3'b010��ǿ����Wģ���ƣ�
                                                              3'b011��ǿ����TDSģ���ƣ�
                                                              3'b100��ǿ����Gmģ���ƣ�
                                                              3'b101��ǿ����Gsģ���ƣ�
                                                              3'b110��ǿ����Cģ���ƣ�
                                                              3'b111����Ч��
                                                              �����á� */
        unsigned int  reserved            : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_C1_MIPI_SELECT_MASK_UNION;
#define BBPCOMM_C1_MIPI_SELECT_MASK_c1_mipi_select_mask_START  (0)
#define BBPCOMM_C1_MIPI_SELECT_MASK_c1_mipi_select_mask_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C1_ABB_SELECT_MASK_UNION
 �ṹ˵��  : C1_ABB_SELECT_MASK �Ĵ����ṹ���塣��ַƫ����:0x0320����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c1_abb_select_mask_reg;
    struct
    {
        unsigned int  c1_abb_select_mask : 3;  /* bit[0-2] : ͨ��1 ABB�����ź���Դ��
                                                             3'b000������ģ���ƣ�
                                                             3'b001��ǿ����Lģ���ƣ�
                                                             3'b010��ǿ����Wģ���ƣ�
                                                             3'b011��ǿ����TDSģ���ƣ�
                                                             3'b100��ǿ����Gmģ���ƣ�
                                                             3'b101��ǿ����Gsģ���ƣ�
                                                             3'b110��ǿ����Cģ���ƣ�
                                                             3'b111����Ч��
                                                             �����á� */
        unsigned int  reserved           : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_C1_ABB_SELECT_MASK_UNION;
#define BBPCOMM_C1_ABB_SELECT_MASK_c1_abb_select_mask_START  (0)
#define BBPCOMM_C1_ABB_SELECT_MASK_c1_abb_select_mask_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C1_PMU_SELECT_MASK_UNION
 �ṹ˵��  : C1_PMU_SELECT_MASK �Ĵ����ṹ���塣��ַƫ����:0x0324����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c1_pmu_select_mask_reg;
    struct
    {
        unsigned int  c1_pmu_select_mask : 3;  /* bit[0-2] : ͨ��1 PMU�����ź���Դ��
                                                             3'b000������ģ���ƣ�
                                                             3'b001��ǿ����Lģ���ƣ�
                                                             3'b010��ǿ����Wģ���ƣ�
                                                             3'b011��ǿ����TDSģ���ƣ�
                                                             3'b100��ǿ����Gmģ���ƣ�
                                                             3'b101��ǿ����Gsģ���ƣ�
                                                             3'b110��ǿ����Cģ���ƣ�
                                                             3'b111����Ч��
                                                             �����á� */
        unsigned int  reserved           : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_C1_PMU_SELECT_MASK_UNION;
#define BBPCOMM_C1_PMU_SELECT_MASK_c1_pmu_select_mask_START  (0)
#define BBPCOMM_C1_PMU_SELECT_MASK_c1_pmu_select_mask_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_DSP_C1_SEL_MASK_UNION
 �ṹ˵��  : DSP_C1_SEL_MASK �Ĵ����ṹ���塣��ַƫ����:0x0328����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dsp_c1_sel_mask_reg;
    struct
    {
        unsigned int  dsp_c1_sel_mask : 3;  /* bit[0-2] : ��ǰͨ��1������֮ǰ�� �����ǿ��ģʽ��
                                                          ע���������ڸ�����Χ������ABB��RF��PA��mipi�ȣ������Ľ���ǿ�䡣
                                                          �����á� */
        unsigned int  reserved        : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_DSP_C1_SEL_MASK_UNION;
#define BBPCOMM_DSP_C1_SEL_MASK_dsp_c1_sel_mask_START  (0)
#define BBPCOMM_DSP_C1_SEL_MASK_dsp_c1_sel_mask_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_DSP_RFIC1_RSTN_UNION
 �ṹ˵��  : DSP_RFIC1_RSTN �Ĵ����ṹ���塣��ַƫ����:0x032C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dsp_rfic1_rstn_reg;
    struct
    {
        unsigned int  dsp_rfic1_rstn : 1;  /* bit[0-0] : ������õ�RFIC1��λ�źš� ����Ч�� 
                                                         0����λ��1���⸴λ��
                                                         �ϵ��ʼ������Ϊ0������RFIC�ֲ�Ҫ��ά��һ��ʱ�������Ϊ1��
                                                         
                                                         V7R2��λֵΪ0��
                                                         V8R1���üĴ�������ɾ���� */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_DSP_RFIC1_RSTN_UNION;
#define BBPCOMM_DSP_RFIC1_RSTN_dsp_rfic1_rstn_START  (0)
#define BBPCOMM_DSP_RFIC1_RSTN_dsp_rfic1_rstn_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C1_SECOND_AFC_MODE_UNION
 �ṹ˵��  : C1_SECOND_AFC_MODE �Ĵ����ṹ���塣��ַƫ����:0x0330����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c1_second_afc_mode_reg;
    struct
    {
        unsigned int  c1_second_afc_mode : 1;  /* bit[0]   : 0:ͨ��1��ģʹ��ͨ��1��ģafc������
                                                             1:ͨ��1��ģʹ��ͨ��1��ģafc������ */
        unsigned int  reserved           : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_C1_SECOND_AFC_MODE_UNION;
#define BBPCOMM_C1_SECOND_AFC_MODE_c1_second_afc_mode_START  (0)
#define BBPCOMM_C1_SECOND_AFC_MODE_c1_second_afc_mode_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_MIPI1_RD_OVERTIME_FLAG_DSP_UNION
 �ṹ˵��  : MIPI1_RD_OVERTIME_FLAG_DSP �Ĵ����ṹ���塣��ַƫ����:0x0338����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      mipi1_rd_overtime_flag_dsp_reg;
    struct
    {
        unsigned int  mipi1_rd_overtime_flag_dsp : 1;  /* bit[0]   : DSP�ȴ��ض������ʱ��־λ
                                                                     1:��ʱ   */
        unsigned int  reserved                   : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_MIPI1_RD_OVERTIME_FLAG_DSP_UNION;
#define BBPCOMM_MIPI1_RD_OVERTIME_FLAG_DSP_mipi1_rd_overtime_flag_dsp_START  (0)
#define BBPCOMM_MIPI1_RD_OVERTIME_FLAG_DSP_mipi1_rd_overtime_flag_dsp_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_SSI1_RD_OVERTIME_FLAG_DSP_UNION
 �ṹ˵��  : SSI1_RD_OVERTIME_FLAG_DSP �Ĵ����ṹ���塣��ַƫ����:0x033C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      ssi1_rd_overtime_flag_dsp_reg;
    struct
    {
        unsigned int  ssi1_rd_overtime_flag_dsp : 1;  /* bit[0]   : DSP�ȴ��ض������ʱ��־λ
                                                                    1:��ʱ   */
        unsigned int  reserved                  : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_SSI1_RD_OVERTIME_FLAG_DSP_UNION;
#define BBPCOMM_SSI1_RD_OVERTIME_FLAG_DSP_ssi1_rd_overtime_flag_dsp_START  (0)
#define BBPCOMM_SSI1_RD_OVERTIME_FLAG_DSP_ssi1_rd_overtime_flag_dsp_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_MIPI1_RD_OVERTIME_CLR_UNION
 �ṹ˵��  : MIPI1_RD_OVERTIME_CLR �Ĵ����ṹ���塣��ַƫ����:0x0340����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      mipi1_rd_overtime_clr_reg;
    struct
    {
        unsigned int  mipi1_rd_overtime_clr_imi : 1;  /* bit[0]   : DSP�ȴ��ض������ʱ��,�峭ʱ��־λ���� */
        unsigned int  reserved                  : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_MIPI1_RD_OVERTIME_CLR_UNION;
#define BBPCOMM_MIPI1_RD_OVERTIME_CLR_mipi1_rd_overtime_clr_imi_START  (0)
#define BBPCOMM_MIPI1_RD_OVERTIME_CLR_mipi1_rd_overtime_clr_imi_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_SSI1_RD_OVERTIME_CLR_UNION
 �ṹ˵��  : SSI1_RD_OVERTIME_CLR �Ĵ����ṹ���塣��ַƫ����:0x0344����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      ssi1_rd_overtime_clr_reg;
    struct
    {
        unsigned int  ssi1_rd_overtime_clr_imi : 1;  /* bit[0]   : DSP�ȴ��ض������ʱ��,�峭ʱ��־λ���� */
        unsigned int  reserved                 : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_SSI1_RD_OVERTIME_CLR_UNION;
#define BBPCOMM_SSI1_RD_OVERTIME_CLR_ssi1_rd_overtime_clr_imi_START  (0)
#define BBPCOMM_SSI1_RD_OVERTIME_CLR_ssi1_rd_overtime_clr_imi_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_RD_RESULT_FLAG_RFIC1_UNION
 �ṹ˵��  : RD_RESULT_FLAG_RFIC1 �Ĵ����ṹ���塣��ַƫ����:0x0388����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_rfic1_reg;
    struct
    {
        unsigned int  rd_result_flag_rfic1 : 1;  /* bit[0]   : ���лض�ָ��ִ�����,����ȡ�߻ض�����
                                                               1:���лض�ָ������,DSP���԰�λ�ö�ȡSSI�ض���� */
        unsigned int  reserved             : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_RFIC1_UNION;
#define BBPCOMM_RD_RESULT_FLAG_RFIC1_rd_result_flag_rfic1_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_RFIC1_rd_result_flag_rfic1_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_RD_RESULT_FLAG_RFIC1_CLR_UNION
 �ṹ˵��  : RD_RESULT_FLAG_RFIC1_CLR �Ĵ����ṹ���塣��ַƫ����:0x038C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_rfic1_clr_reg;
    struct
    {
        unsigned int  rd_result_flag_rfic1_clr : 1;  /* bit[0]   : 1:DSPȡ�����лض����ݺ�,д��clr�ź����־λ */
        unsigned int  reserved                 : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_RFIC1_CLR_UNION;
#define BBPCOMM_RD_RESULT_FLAG_RFIC1_CLR_rd_result_flag_rfic1_clr_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_RFIC1_CLR_rd_result_flag_rfic1_clr_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_RD_RESULT_FLAG_MIPI1_UNION
 �ṹ˵��  : RD_RESULT_FLAG_MIPI1 �Ĵ����ṹ���塣��ַƫ����:0x03D0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_mipi1_reg;
    struct
    {
        unsigned int  rd_result_flag_mipi1 : 1;  /* bit[0]   : ���лض�ָ��ִ�����,����ȡ�߻ض�����
                                                               1:���лض�ָ������,DSP���԰�λ�ö�ȡSSI�ض����,�����������ֱ�ӿ���MIPI��־λ��ͬ */
        unsigned int  reserved             : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_MIPI1_UNION;
#define BBPCOMM_RD_RESULT_FLAG_MIPI1_rd_result_flag_mipi1_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_MIPI1_rd_result_flag_mipi1_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_RD_RESULT_FLAG_MIPI1_CLR_UNION
 �ṹ˵��  : RD_RESULT_FLAG_MIPI1_CLR �Ĵ����ṹ���塣��ַƫ����:0x03D4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_mipi1_clr_reg;
    struct
    {
        unsigned int  rd_result_flag_mipi1_clr : 1;  /* bit[0]   : 1:DSPȡ�����лض����ݺ�,д��clr�ź����־λ,�����������ֱ�ӿ���MIPI��־λ��ͬ */
        unsigned int  reserved                 : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_MIPI1_CLR_UNION;
#define BBPCOMM_RD_RESULT_FLAG_MIPI1_CLR_rd_result_flag_mipi1_clr_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_MIPI1_CLR_rd_result_flag_mipi1_clr_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_RD_END_FLAG_MIPI1_SOFT_UNION
 �ṹ˵��  : RD_END_FLAG_MIPI1_SOFT �Ĵ����ṹ���塣��ַƫ����:0x03E0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      rd_end_flag_mipi1_soft_reg;
    struct
    {
        unsigned int  rd_end_flag_mipi1_soft : 1;  /* bit[0]   : �����ֱ�ӿ���MIPI1 master,������xbbp���ͻض�ָ��ʱ,�ض�������Чָʾ */
        unsigned int  reserved               : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_RD_END_FLAG_MIPI1_SOFT_UNION;
#define BBPCOMM_RD_END_FLAG_MIPI1_SOFT_rd_end_flag_mipi1_soft_START  (0)
#define BBPCOMM_RD_END_FLAG_MIPI1_SOFT_rd_end_flag_mipi1_soft_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_MIPI1_GRANT_DSP_UNION
 �ṹ˵��  : MIPI1_GRANT_DSP �Ĵ����ṹ���塣��ַƫ����:0x03E4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      mipi1_grant_dsp_reg;
    struct
    {
        unsigned int  mipi1_grant_dsp : 1;  /* bit[0]   : �����ֱ�ӿ���MIPI1 master
                                                          1:������Է���CFG_IND����mipi1
                                                          0:����ȴ�mipi1��Ȩʹ�� */
        unsigned int  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_MIPI1_GRANT_DSP_UNION;
#define BBPCOMM_MIPI1_GRANT_DSP_mipi1_grant_dsp_START  (0)
#define BBPCOMM_MIPI1_GRANT_DSP_mipi1_grant_dsp_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_DSP_MIPI1_EN_IMI_UNION
 �ṹ˵��  : DSP_MIPI1_EN_IMI �Ĵ����ṹ���塣��ַƫ����:0x03F0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dsp_mipi1_en_imi_reg;
    struct
    {
        unsigned int  dsp_mipi1_en_imi : 1;  /* bit[0]   : �����ֱ�ӿ���MIPI1 master,���������ߴ�ָʾ,����xbbp��MIPI1�Ŀ��� */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_DSP_MIPI1_EN_IMI_UNION;
#define BBPCOMM_DSP_MIPI1_EN_IMI_dsp_mipi1_en_imi_START  (0)
#define BBPCOMM_DSP_MIPI1_EN_IMI_dsp_mipi1_en_imi_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_DSP_MIPI1_CFG_IND_IMI_UNION
 �ṹ˵��  : DSP_MIPI1_CFG_IND_IMI �Ĵ����ṹ���塣��ַƫ����:0x03F4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dsp_mipi1_cfg_ind_imi_reg;
    struct
    {
        unsigned int  dsp_mipi1_cfg_ind_imi : 1;  /* bit[0]   : �����ֱ�ӿ���MIPI1 master,���ߴ�dsp_mipi1_en��,��������������� */
        unsigned int  reserved              : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_DSP_MIPI1_CFG_IND_IMI_UNION;
#define BBPCOMM_DSP_MIPI1_CFG_IND_IMI_dsp_mipi1_cfg_ind_imi_START  (0)
#define BBPCOMM_DSP_MIPI1_CFG_IND_IMI_dsp_mipi1_cfg_ind_imi_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_DSP_MIPI1_RD_CLR_UNION
 �ṹ˵��  : DSP_MIPI1_RD_CLR �Ĵ����ṹ���塣��ַƫ����:0x03F8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dsp_mipi1_rd_clr_reg;
    struct
    {
        unsigned int  dsp_mipi1_rd_clr : 1;  /* bit[0]   : �����ֱ�ӿ���MIPI1 master,ȡ�߻ض����ݺ�,���־λ���� */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_DSP_MIPI1_RD_CLR_UNION;
#define BBPCOMM_DSP_MIPI1_RD_CLR_dsp_mipi1_rd_clr_START  (0)
#define BBPCOMM_DSP_MIPI1_RD_CLR_dsp_mipi1_rd_clr_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_ABB1_LINE_CONTROL_CMD_UNION
 �ṹ˵��  : ABB1_LINE_CONTROL_CMD �Ĵ����ṹ���塣��ַƫ����:0x03FC����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      abb1_line_control_cmd_reg;
    struct
    {
        unsigned int  abb1_line_control_cmd_sel : 1;  /* bit[0-0] : ABB1�߿�ǿ��ģʽ��
                                                                    1����ʾ���ǿ�䣬��ʱ��������ǿ�����Ч��
                                                                    0����ʾ��CTU���ݸ�BBP������
                                                                    Ĭ��ֵΪ0��
                                                                    �����á� */
        unsigned int  abb1_mode_sel_cmd         : 3;  /* bit[1-3] : ���ǿ��ģʽabb1_mode_sel. */
        unsigned int  abb1_tx_en_cmd            : 1;  /* bit[4-4] : ���ǿ��ģʽabb1_tx_en. */
        unsigned int  abb1_rxa_en_cmd           : 1;  /* bit[5-5] : ���ǿ��ģʽabb1_rxa_en. */
        unsigned int  abb1_rxb_en_cmd           : 1;  /* bit[6-6] : ���ǿ��ģʽabb1_rxb_en. */
        unsigned int  abb1_blka_en_cmd          : 1;  /* bit[7-7] : ���ǿ��ģʽabb1_rxa_blk_en. */
        unsigned int  abb1_blkb_en_cmd          : 1;  /* bit[8-8] : ���ǿ��ģʽabb1_rxb_blk_en. */
        unsigned int  reserved                  : 23; /* bit[9-31]: ���� */
    } reg;
} BBPCOMM_ABB1_LINE_CONTROL_CMD_UNION;
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_abb1_line_control_cmd_sel_START  (0)
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_abb1_line_control_cmd_sel_END    (0)
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_abb1_mode_sel_cmd_START          (1)
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_abb1_mode_sel_cmd_END            (3)
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_abb1_tx_en_cmd_START             (4)
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_abb1_tx_en_cmd_END               (4)
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_abb1_rxa_en_cmd_START            (5)
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_abb1_rxa_en_cmd_END              (5)
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_abb1_rxb_en_cmd_START            (6)
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_abb1_rxb_en_cmd_END              (6)
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_abb1_blka_en_cmd_START           (7)
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_abb1_blka_en_cmd_END             (7)
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_abb1_blkb_en_cmd_START           (8)
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_abb1_blkb_en_cmd_END             (8)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CH1_BBP_SEL_UNION
 �ṹ˵��  : CH1_BBP_SEL �Ĵ����ṹ���塣��ַƫ����:0x0400����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      ch1_bbp_sel_reg;
    struct
    {
        unsigned int  ch1_bbp_sel : 3;  /* bit[0-2] : V9R1�汾����������á� */
        unsigned int  reserved    : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_CH1_BBP_SEL_UNION;
#define BBPCOMM_CH1_BBP_SEL_ch1_bbp_sel_START  (0)
#define BBPCOMM_CH1_BBP_SEL_ch1_bbp_sel_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_MIPI1_FUNC_SEL_UNION
 �ṹ˵��  : CPU_MIPI1_FUNC_SEL �Ĵ����ṹ���塣��ַƫ����:0x0404����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi1_func_sel_reg;
    struct
    {
        unsigned int  cpu_mipi1_func_sel : 1;  /* bit[0]   : cpu����mipi����,����Ϊ1������������, ����ʱ����Ϊ0 */
        unsigned int  reserved           : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_CPU_MIPI1_FUNC_SEL_UNION;
#define BBPCOMM_CPU_MIPI1_FUNC_SEL_cpu_mipi1_func_sel_START  (0)
#define BBPCOMM_CPU_MIPI1_FUNC_SEL_cpu_mipi1_func_sel_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_MIPI1_TEST_FUNC_UNION
 �ṹ˵��  : CPU_MIPI1_TEST_FUNC �Ĵ����ṹ���塣��ַƫ����:0x0408����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi1_test_func_reg;
    struct
    {
        unsigned int  cpu_mipi1_test_func : 1;  /* bit[0]   : cpu����mipi����,������ */
        unsigned int  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_CPU_MIPI1_TEST_FUNC_UNION;
#define BBPCOMM_CPU_MIPI1_TEST_FUNC_cpu_mipi1_test_func_START  (0)
#define BBPCOMM_CPU_MIPI1_TEST_FUNC_cpu_mipi1_test_func_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_MIPI1_SCLK_TEST_UNION
 �ṹ˵��  : CPU_MIPI1_SCLK_TEST �Ĵ����ṹ���塣��ַƫ����:0x040C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi1_sclk_test_reg;
    struct
    {
        unsigned int  cpu_mipi1_sclk_test : 1;  /* bit[0]   : cpu����mipi����,������ */
        unsigned int  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_CPU_MIPI1_SCLK_TEST_UNION;
#define BBPCOMM_CPU_MIPI1_SCLK_TEST_cpu_mipi1_sclk_test_START  (0)
#define BBPCOMM_CPU_MIPI1_SCLK_TEST_cpu_mipi1_sclk_test_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_MIPI1_SDATA_TEST_UNION
 �ṹ˵��  : CPU_MIPI1_SDATA_TEST �Ĵ����ṹ���塣��ַƫ����:0x0410����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi1_sdata_test_reg;
    struct
    {
        unsigned int  cpu_mipi1_sdata_test : 1;  /* bit[0]   : cpu����mipi����,������ */
        unsigned int  reserved             : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_CPU_MIPI1_SDATA_TEST_UNION;
#define BBPCOMM_CPU_MIPI1_SDATA_TEST_cpu_mipi1_sdata_test_START  (0)
#define BBPCOMM_CPU_MIPI1_SDATA_TEST_cpu_mipi1_sdata_test_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_DSP_MIPI1_CLR_IND_IMI_UNION
 �ṹ˵��  : DSP_MIPI1_CLR_IND_IMI �Ĵ����ṹ���塣��ַƫ����:0x0414����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      dsp_mipi1_clr_ind_imi_reg;
    struct
    {
        unsigned int  dsp_mipi1_clr_ind_imi : 1;  /* bit[0]   : cpu����mipi����,mipi1master���쳣�ź� */
        unsigned int  reserved              : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_DSP_MIPI1_CLR_IND_IMI_UNION;
#define BBPCOMM_DSP_MIPI1_CLR_IND_IMI_dsp_mipi1_clr_ind_imi_START  (0)
#define BBPCOMM_DSP_MIPI1_CLR_IND_IMI_dsp_mipi1_clr_ind_imi_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_MIPI1_FIFO_CLR_IMI_UNION
 �ṹ˵��  : CPU_MIPI1_FIFO_CLR_IMI �Ĵ����ṹ���塣��ַƫ����:0x0418����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi1_fifo_clr_imi_reg;
    struct
    {
        unsigned int  cpu_mipi1_fifo_clr_imi : 1;  /* bit[0]   : mipi1�洢����������ͬ��FIFO��λ�ź� */
        unsigned int  reserved               : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_CPU_MIPI1_FIFO_CLR_IMI_UNION;
#define BBPCOMM_CPU_MIPI1_FIFO_CLR_IMI_cpu_mipi1_fifo_clr_imi_START  (0)
#define BBPCOMM_CPU_MIPI1_FIFO_CLR_IMI_cpu_mipi1_fifo_clr_imi_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_SSI1_FIFO_CLR_IMI_UNION
 �ṹ˵��  : CPU_SSI1_FIFO_CLR_IMI �Ĵ����ṹ���塣��ַƫ����:0x041C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_ssi1_fifo_clr_imi_reg;
    struct
    {
        unsigned int  cpu_ssi1_fifo_clr_imi : 1;  /* bit[0]   : ssi1�洢����������ͬ��FIFO��λ�ź� */
        unsigned int  reserved              : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_CPU_SSI1_FIFO_CLR_IMI_UNION;
#define BBPCOMM_CPU_SSI1_FIFO_CLR_IMI_cpu_ssi1_fifo_clr_imi_START  (0)
#define BBPCOMM_CPU_SSI1_FIFO_CLR_IMI_cpu_ssi1_fifo_clr_imi_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_UNION
 �ṹ˵��  : CPU_RX1_TX1_CKG_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x0420����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_rx1_tx1_ckg_bypass_reg;
    struct
    {
        unsigned int  cpu_rx1_lte_ckg_bypass : 1;  /* bit[0]    : Lģͨ��1 RX ABB��·ʱ���ſ���·�ź� */
        unsigned int  cpu_rx1_tds_ckg_bypass : 1;  /* bit[1]    : TDSͨ��1 RX ABB��·ʱ���ſ���·�ź� */
        unsigned int  cpu_rx1_w_ckg_bypass   : 1;  /* bit[2]    : Wģͨ��1 RX ABB��·ʱ���ſ���·�ź� */
        unsigned int  cpu_rx1_g1_ckg_bypass  : 1;  /* bit[3]    : G1ͨ��1 RX ABB��·ʱ���ſ���·�ź� */
        unsigned int  cpu_rx1_g2_ckg_bypass  : 1;  /* bit[4]    : G2ͨ��1 RX ABB��·ʱ���ſ���·�ź� */
        unsigned int  cpu_tx1_lte_ckg_bypass : 1;  /* bit[5]    : Lģͨ��1 TX ABB��·ʱ���ſ���·�ź� */
        unsigned int  cpu_tx1_tds_ckg_bypass : 1;  /* bit[6]    : TDSͨ��1 TX ABB��·ʱ���ſ���·�ź� */
        unsigned int  cpu_tx1_w_ckg_bypass   : 1;  /* bit[7]    : Wģͨ��1 TX ABB��·ʱ���ſ���·�ź� */
        unsigned int  cpu_tx1_g1_ckg_bypass  : 1;  /* bit[8]    : G1ͨ��1 TX ABB��·ʱ���ſ���·�ź� */
        unsigned int  cpu_tx1_g2_ckg_bypass  : 1;  /* bit[9]    : G2ͨ��1 TX ABB��·ʱ���ſ���·�ź� */
        unsigned int  cpu_rx1_c_ckg_bypass   : 1;  /* bit[10]   : Cģͨ��1 RX ABB��·ʱ���ſ���·�ź� */
        unsigned int  cpu_tx1_c_ckg_bypass   : 1;  /* bit[11]   : Cģͨ��1 TX ABB��·ʱ���ſ���·�ź� */
        unsigned int  reserved               : 20; /* bit[12-31]: ���� */
    } reg;
} BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_UNION;
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_rx1_lte_ckg_bypass_START  (0)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_rx1_lte_ckg_bypass_END    (0)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_rx1_tds_ckg_bypass_START  (1)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_rx1_tds_ckg_bypass_END    (1)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_rx1_w_ckg_bypass_START    (2)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_rx1_w_ckg_bypass_END      (2)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_rx1_g1_ckg_bypass_START   (3)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_rx1_g1_ckg_bypass_END     (3)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_rx1_g2_ckg_bypass_START   (4)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_rx1_g2_ckg_bypass_END     (4)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_tx1_lte_ckg_bypass_START  (5)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_tx1_lte_ckg_bypass_END    (5)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_tx1_tds_ckg_bypass_START  (6)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_tx1_tds_ckg_bypass_END    (6)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_tx1_w_ckg_bypass_START    (7)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_tx1_w_ckg_bypass_END      (7)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_tx1_g1_ckg_bypass_START   (8)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_tx1_g1_ckg_bypass_END     (8)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_tx1_g2_ckg_bypass_START   (9)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_tx1_g2_ckg_bypass_END     (9)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_rx1_c_ckg_bypass_START    (10)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_rx1_c_ckg_bypass_END      (10)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_tx1_c_ckg_bypass_START    (11)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_tx1_c_ckg_bypass_END      (11)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TIMING_GET_IND_UNION
 �ṹ˵��  : TIMING_GET_IND �Ĵ����ṹ���塣��ַƫ����:0x0610����ֵ:0x00000030�����:32
 �Ĵ���˵��: ��ʱ����ʹ��ָʾ�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      timing_get_ind_reg;
    struct
    {
        unsigned int  timing_get_ind   : 1;  /* bit[0]   : �߼������㡣
                                                           timing_get_mode��Ч��DSP��Ҫ��ȡ��ʱ��ϵʱ������Ч��CTU�߼����ݴ��ź�����LTE/W/Gm/Gs/TDS/C��ϵͳ��ʱ��CTU���ڲ���ʱ��DSP��ѯ��
                                                           timing_get_mode��Ч��bbe16��Ҫ��ȡ��ʱ��ϵʱ������Ч��CTU�߼����ݴ��ź�����LTE/W/Gm/Gs/TDS/C��ϵͳ��ʱ��CTU���ڲ���ʱ��bbe16��ѯ��
                                                           ����ʱ�̣������Ҫ���涨ʱ
                                                           ��Чʱ�̣�������Ч */
        unsigned int  reserved_0       : 3;  /* bit[1-3] : ���� */
        unsigned int  timing_get_c_sel : 2;  /* bit[4-5] : ��ʾtiming_get_mode��Чʱbbe��ȡCģbbp���������1x��evdo����base_cnt��   00��1x��ʱ��01��evdo��ʱ��10�� base_cnt ��11����Ч��
                                                           timing_get_mode��Чʱ���������ã������� */
        unsigned int  reserved_1       : 26; /* bit[6-31]: ���� */
    } reg;
} BBPCOMM_TIMING_GET_IND_UNION;
#define BBPCOMM_TIMING_GET_IND_timing_get_ind_START    (0)
#define BBPCOMM_TIMING_GET_IND_timing_get_ind_END      (0)
#define BBPCOMM_TIMING_GET_IND_timing_get_c_sel_START  (4)
#define BBPCOMM_TIMING_GET_IND_timing_get_c_sel_END    (5)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TIMING_CLEAR_UNION
 �ṹ˵��  : TIMING_CLEAR �Ĵ����ṹ���塣��ַƫ����:0x0614����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ʱ��־����Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      timing_clear_reg;
    struct
    {
        unsigned int  timing_clear          : 1;  /* bit[0]   : �߼������㡣
                                                                ��ʱ��־������������timing_valid��־��
                                                                ����ʱ�̣�DSP��ȡ��ʱ��Ϻ�����
                                                                ��Чʱ�̣�������Ч
                                                                ��timing_get_mode��Ч��dsp���ƣ�
                                                                timing_get_mode��Ч��bbe16���ƣ� */
        unsigned int  comm_32k_timing_clear : 1;  /* bit[1]   : �߼������㡣
                                                                32������ʱ��Ϣ�ı�־������������timing_valid��־��
                                                                ����ʱ�̣�DSP��ȡ��ʱ��Ϻ�����
                                                                ��Чʱ�̣�������Ч
                                                                ����Ϊ32K��ʱ��Ϣ���ϱ���ʱԶ��������ϵͳ�Ķ�ʱ��Ϣ�����Ե�������
                                                                ��timing_get_mode��Ч��dsp���ƣ�
                                                                timing_get_mode��Ч��bbe16���ƣ� */
        unsigned int  reserved              : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_TIMING_CLEAR_UNION;
#define BBPCOMM_TIMING_CLEAR_timing_clear_START           (0)
#define BBPCOMM_TIMING_CLEAR_timing_clear_END             (0)
#define BBPCOMM_TIMING_CLEAR_comm_32k_timing_clear_START  (1)
#define BBPCOMM_TIMING_CLEAR_comm_32k_timing_clear_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_DELAY_CNT_UNION
 �ṹ˵��  : DELAY_CNT �Ĵ����ṹ���塣��ַƫ����:0x0618����ֵ:0x0000000A�����:32
 �Ĵ���˵��: ��ʱ�����ӳټĴ���
*****************************************************************************/
typedef union
{
    unsigned int      delay_cnt_reg;
    struct
    {
        unsigned int  delay_cnt : 5;  /* bit[0-4] : CTU��⵽timing_get_ind��̶��ӳ�delay_cnt��CTUʱ�����ں�����timing_valid�źš�
                                                    ����ʱ�̣��ϵ��ʼ��
                                                    ��Чʱ�̣�������Ч */
        unsigned int  reserved  : 27; /* bit[5-31]: ���� */
    } reg;
} BBPCOMM_DELAY_CNT_UNION;
#define BBPCOMM_DELAY_CNT_delay_cnt_START  (0)
#define BBPCOMM_DELAY_CNT_delay_cnt_END    (4)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_WAIT_CNT_UNION
 �ṹ˵��  : INT_WAIT_CNT �Ĵ����ṹ���塣��ַƫ����:0x061C����ֵ:0x0000001E�����:32
 �Ĵ���˵��: �ж��ӳټĴ���
*****************************************************************************/
typedef union
{
    unsigned int      int_wait_cnt_reg;
    struct
    {
        unsigned int  int_wait_cnt : 16; /* bit[0-15] : CTU�ж��ϱ��ȴ�ʱ�䣬��λΪһ��CLK���ڡ�
                                                        DSP����жϱ�־�Ĵ�����ĳ������bit��CTU�ϱ��жϵ�ƽ��Ҫ���ͣ������ʱ�жϱ�־�Ĵ������������ж�������Ч������ȴ�int_wait_cnt��ʱ�����ں�������CTU�ϱ��жϡ�
                                                        ����ʱ�̣��ϵ��ʼ��
                                                        ��Чʱ�̣�������Ч */
        unsigned int  reserved     : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_WAIT_CNT_UNION;
#define BBPCOMM_INT_WAIT_CNT_int_wait_cnt_START  (0)
#define BBPCOMM_INT_WAIT_CNT_int_wait_cnt_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_LTEBBP_INPUT_MASK_UNION
 �ṹ˵��  : LTEBBP_INPUT_MASK �Ĵ����ṹ���塣��ַƫ����:0x0620����ֵ:0x00000003�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      ltebbp_input_mask_reg;
    struct
    {
        unsigned int  ltebbp_input_mask : 2;  /* bit[0-1] : ��ƽ�źţ�����Ч��
                                                            ��LTE��ģ��Ҫ����ϵͳ����ʱ�����ñ��Ĵ���Ϊ3����ϵͳ�������������ñ��Ĵ���Ϊ0��
                                                            bit1:1��b0: lte_intrasys_valid������Ч����ǿ��Ϊ1��
                                                            bit0:1��b0:
                                                            lte_intersys_ingap_pre_ind������Ч����ǿ��Ϊ0��
                                                            bit[1:0] = 11b: ��lte_intrasys_valid��lte_intersys_ingap_pre_ind������Ч��
                                                            
                                                            ����ʱ�̣�LTE��ģ��Ҫ����ϵͳ����ʱ�����ñ��Ĵ���Ϊ3����ϵͳ�������������ñ��Ĵ���Ϊ0��
                                                            ��Чʱ�̣�������Ч */
        unsigned int  reserved          : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_LTEBBP_INPUT_MASK_UNION;
#define BBPCOMM_LTEBBP_INPUT_MASK_ltebbp_input_mask_START  (0)
#define BBPCOMM_LTEBBP_INPUT_MASK_ltebbp_input_mask_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_WBBP_INPUT_MASK_UNION
 �ṹ˵��  : WBBP_INPUT_MASK �Ĵ����ṹ���塣��ַƫ����:0x0624����ֵ:0x00000003�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      wbbp_input_mask_reg;
    struct
    {
        unsigned int  wbbp_input_mask : 2;  /* bit[0-1] : ��ƽ�źţ�����Ч��
                                                          ��W��ģ��Ҫ����ϵͳ����ʱ�����ñ��Ĵ���Ϊ3����ϵͳ�������������ñ��Ĵ���Ϊ0��
                                                          bit1:1��b0:
                                                           ��w_intrasys_valid������Ч����ǿ��Ϊ1��
                                                          bit0:1��b0:
                                                          w_intersys_ingap_pre_ind������Ч����ǿ��Ϊ0��
                                                          bit[1:0] = 11b: ��w_intrasys_valid��w_intersys_ingap_pre_ind������Ч��
                                                          
                                                          ����ʱ�̣�W��ģ��Ҫ����ϵͳ����ʱ�����ñ��Ĵ���Ϊ3����ϵͳ�������������ñ��Ĵ���Ϊ0��
                                                          ��Чʱ�̣�������Ч */
        unsigned int  reserved        : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_WBBP_INPUT_MASK_UNION;
#define BBPCOMM_WBBP_INPUT_MASK_wbbp_input_mask_START  (0)
#define BBPCOMM_WBBP_INPUT_MASK_wbbp_input_mask_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GMBBP_INPUT_MASK_UNION
 �ṹ˵��  : GMBBP_INPUT_MASK �Ĵ����ṹ���塣��ַƫ����:0x0628����ֵ:0x00000003�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gmbbp_input_mask_reg;
    struct
    {
        unsigned int  gmbbp_input_mask : 2;  /* bit[0-1] : ��ƽ�źţ�����Ч��
                                                           ��Gm��ģ��Ҫ����ϵͳ����ʱ�����ñ��Ĵ���Ϊ3����ϵͳ�������������ñ��Ĵ���Ϊ0��
                                                           bit1:1��b0:
                                                            ��gm_intrasys_valid������Ч����ǿ��Ϊ1��
                                                           bit0:1��b0:
                                                           gm_intersys_ingap_pre_ind������Ч����ǿ��Ϊ0��
                                                           bit[1:0] = 11b: ��gm_intrasys_valid��gm_intersys_ingap_pre_ind������Ч��
                                                           
                                                           ����ʱ�̣�Gm��ģ��Ҫ����ϵͳ����ʱ�����ñ��Ĵ���Ϊ3����ϵͳ�������������ñ��Ĵ���Ϊ0��
                                                           ��Чʱ�̣�������Ч */
        unsigned int  reserved         : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_GMBBP_INPUT_MASK_UNION;
#define BBPCOMM_GMBBP_INPUT_MASK_gmbbp_input_mask_START  (0)
#define BBPCOMM_GMBBP_INPUT_MASK_gmbbp_input_mask_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GSBBP_INPUT_MASK_UNION
 �ṹ˵��  : GSBBP_INPUT_MASK �Ĵ����ṹ���塣��ַƫ����:0x062C����ֵ:0x00000003�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gsbbp_input_mask_reg;
    struct
    {
        unsigned int  gsbbp_input_mask : 2;  /* bit[0-1] : ��ƽ�źţ�����Ч��
                                                           ��Gs��ģ��Ҫ����ϵͳ����ʱ�����ñ��Ĵ���Ϊ3����ϵͳ�������������ñ��Ĵ���Ϊ0��
                                                           bit1:1��b0:
                                                            ��gs_intrasys_valid������Ч����ǿ��Ϊ1��
                                                           bit0:1��b0:
                                                           gs_intersys_ingap_pre_ind������Ч����ǿ��Ϊ0��
                                                           bit[1:0] = 11b: ��gs_intrasys_valid��gs_intersys_ingap_pre_ind������Ч��
                                                           
                                                           ����ʱ�̣�Gs��ģ��Ҫ����ϵͳ����ʱ�����ñ��Ĵ���Ϊ3����ϵͳ�������������ñ��Ĵ���Ϊ0��
                                                           ��Чʱ�̣�������Ч */
        unsigned int  reserved         : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_GSBBP_INPUT_MASK_UNION;
#define BBPCOMM_GSBBP_INPUT_MASK_gsbbp_input_mask_START  (0)
#define BBPCOMM_GSBBP_INPUT_MASK_gsbbp_input_mask_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TDSBBP_INPUT_MASK_UNION
 �ṹ˵��  : TDSBBP_INPUT_MASK �Ĵ����ṹ���塣��ַƫ����:0x0630����ֵ:0x00000003�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      tdsbbp_input_mask_reg;
    struct
    {
        unsigned int  tdsbbp_input_mask : 2;  /* bit[0-1] : ��ƽ�źţ�����Ч��
                                                            ��TDS��ģ��Ҫ����ϵͳ����ʱ�����ñ��Ĵ���Ϊ3����ϵͳ�������������ñ��Ĵ���Ϊ0��
                                                            bit1:1��b0:
                                                             ��tds_intrasys_valid������Ч����ǿ��Ϊ1��
                                                            bit0:1��b0:
                                                            tds_intersys_ingap_pre_ind������Ч����ǿ��Ϊ0��
                                                            bit[1:0] = 11b: ��tds_intrasys_valid��tds_intersys_ingap_pre_ind������Ч��
                                                            
                                                            ����ʱ�̣�TDS��ģ��Ҫ����ϵͳ����ʱ�����ñ��Ĵ���Ϊ3����ϵͳ�������������ñ��Ĵ���Ϊ0��
                                                            ��Чʱ�̣�������Ч */
        unsigned int  reserved          : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_TDSBBP_INPUT_MASK_UNION;
#define BBPCOMM_TDSBBP_INPUT_MASK_tdsbbp_input_mask_START  (0)
#define BBPCOMM_TDSBBP_INPUT_MASK_tdsbbp_input_mask_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TIMING_VALID_UNION
 �ṹ˵��  : TIMING_VALID �Ĵ����ṹ���塣��ַƫ����:0x0668����ֵ:0x00000030�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      timing_valid_reg;
    struct
    {
        unsigned int  o_timing_valid        : 1;  /* bit[0]   : ��ʱ�ϱ���Ч��־������Ч��
                                                                DSP����timing_get_ind�󣬲�ѯ�˱�־�����Ϊ�ߣ�����Ի�ȡLTE��W��Gm��Gs, TDS��ϵͳ��ʱ��
                                                                DSP��ȡ��ʱ��Ϻ�����timing_clear�Ĵ�����timing_valid����Ϊ��Ч��
                                                                CTU��⵽timing_get_ind��̶��ӳ�delay_cnt������timing_valid��
                                                                
                                                                ����ʱ�̣�
                                                                ��Чʱ�̣�������Ч
                                                                ��timing_get_mode��Ч��dsp���ƣ�
                                                                timing_get_mode��Ч��bbe16���ƣ� */
        unsigned int  comm_32k_timing_valid : 1;  /* bit[1]   : 32K������ʱ�ϱ���Ч��־������Ч��
                                                                DSP����timing_get_ind�󣬲�ѯ�˱�־�����Ϊ�ߣ�����Ի�ȡ32K������ʱ���Ķ�ʱ��Ϣ��
                                                                DSP��ȡ��ʱ��Ϻ�����comm_32k_timing_clear�Ĵ�����comm_32k_timing_valid����Ϊ��Ч��
                                                                32K��ʱ�����ȶ�������comm_32k_timing_valid
                                                                ����ʱ�̣�
                                                                ��Чʱ�̣�������Ч
                                                                ��timing_get_mode��Ч��dsp���ƣ�
                                                                timing_get_mode��Ч��bbe16���ƣ� */
        unsigned int  overtime_ind          : 1;  /* bit[2]   : ��ʾbbe16��ȡ��ʱ��Ϣ��ʱ���ڳ�ʱ����ʱ����δ����o_timing_clear�źţ� */
        unsigned int  reserved_0            : 1;  /* bit[3]   : ���� */
        unsigned int  timing_valid_c_sel    : 2;  /* bit[4-5] : ��ʾo_timing_valid��Чʱ���ϱ�cģ�ļ�������bbe16����1x��evdo����base_cnt
                                                                00��1x��ʱ
                                                                01�� evdo��ʱ
                                                                10�� basecent */
        unsigned int  reserved_1            : 26; /* bit[6-31]: ���� */
    } reg;
} BBPCOMM_TIMING_VALID_UNION;
#define BBPCOMM_TIMING_VALID_o_timing_valid_START         (0)
#define BBPCOMM_TIMING_VALID_o_timing_valid_END           (0)
#define BBPCOMM_TIMING_VALID_comm_32k_timing_valid_START  (1)
#define BBPCOMM_TIMING_VALID_comm_32k_timing_valid_END    (1)
#define BBPCOMM_TIMING_VALID_overtime_ind_START           (2)
#define BBPCOMM_TIMING_VALID_overtime_ind_END             (2)
#define BBPCOMM_TIMING_VALID_timing_valid_c_sel_START     (4)
#define BBPCOMM_TIMING_VALID_timing_valid_c_sel_END       (5)


/*****************************************************************************
 �ṹ��    : BBPCOMM_W_TIMING_DSP_UNION
 �ṹ˵��  : W_TIMING_DSP �Ĵ����ṹ���塣��ַƫ����:0x066C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      w_timing_dsp_reg;
    struct
    {
        unsigned int  w_clk_cnt_dsp  : 4;  /* bit[0-3]  : [3:0]Ϊchip��ʱ�Ӽ�������Χ0~15 */
        unsigned int  w_chip_cnt_dsp : 12; /* bit[4-15] : [15:4]Ϊʱ϶��chip��������Χ0~2559 */
        unsigned int  w_slot_cnt_dsp : 4;  /* bit[16-19]: [19:16]Ϊʱ϶��������Χ0~14 */
        unsigned int  w_sfn_dsp      : 12; /* bit[20-31]: W��ϵͳ��ʱ��Ϣ����DSP ����timing_get_ind�����ϱ���
                                                          �ϱ�ʱ�̣�timing_validΪ��ʱ�ϱ���Ч.
                                                          [31:20]��ʾW��SFN������Դ��w_timing_b[11:0]������Χ0~4095�� */
    } reg;
} BBPCOMM_W_TIMING_DSP_UNION;
#define BBPCOMM_W_TIMING_DSP_w_clk_cnt_dsp_START   (0)
#define BBPCOMM_W_TIMING_DSP_w_clk_cnt_dsp_END     (3)
#define BBPCOMM_W_TIMING_DSP_w_chip_cnt_dsp_START  (4)
#define BBPCOMM_W_TIMING_DSP_w_chip_cnt_dsp_END    (15)
#define BBPCOMM_W_TIMING_DSP_w_slot_cnt_dsp_START  (16)
#define BBPCOMM_W_TIMING_DSP_w_slot_cnt_dsp_END    (19)
#define BBPCOMM_W_TIMING_DSP_w_sfn_dsp_START       (20)
#define BBPCOMM_W_TIMING_DSP_w_sfn_dsp_END         (31)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GM_FN_DSP_UNION
 �ṹ˵��  : GM_FN_DSP �Ĵ����ṹ���塣��ַƫ����:0x0670����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gm_fn_dsp_reg;
    struct
    {
        unsigned int  o_gm_fn_dsp : 22; /* bit[0-21] : GM��FN������Դ��gm_timing_a[21:0]������DSP ����timing_get_ind�����ϱ�������[10:0]��ʾfn_low,��Χ0~1325��[21:11]��ʾfn_hign,��Χ0~2047��
                                                       �ϱ�ʱ�̣�timing_validΪ��ʱ�ϱ���Ч */
        unsigned int  reserved    : 10; /* bit[22-31]: ���� */
    } reg;
} BBPCOMM_GM_FN_DSP_UNION;
#define BBPCOMM_GM_FN_DSP_o_gm_fn_dsp_START  (0)
#define BBPCOMM_GM_FN_DSP_o_gm_fn_dsp_END    (21)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GM_QB_DSP_UNION
 �ṹ˵��  : GM_QB_DSP �Ĵ����ṹ���塣��ַƫ����:0x0674����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gm_qb_dsp_reg;
    struct
    {
        unsigned int  o_gm_qb_dsp : 13; /* bit[0-12] : GM��ϵͳ��ʱQb��Ϣ����DSP ����timing_get_ind�����ϱ���
                                                        [12:0]��ʾ Gϵͳ��ʱ֡��Qb������Դ��gm_timing_b[12:0]������Χ0~4999��
                                                       �ϱ�ʱ�̣�timing_validΪ��ʱ�ϱ���Ч */
        unsigned int  reserved    : 19; /* bit[13-31]: ���� */
    } reg;
} BBPCOMM_GM_QB_DSP_UNION;
#define BBPCOMM_GM_QB_DSP_o_gm_qb_dsp_START  (0)
#define BBPCOMM_GM_QB_DSP_o_gm_qb_dsp_END    (12)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GS_FN_DSP_UNION
 �ṹ˵��  : GS_FN_DSP �Ĵ����ṹ���塣��ַƫ����:0x0678����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gs_fn_dsp_reg;
    struct
    {
        unsigned int  gs_fn_dsp : 22; /* bit[0-21] : GS��FN������Դ��gs_timing_a[21:0]������DSP ����timing_get_ind�����ϱ�������[10:0]��ʾfn_low,��Χ0~1325��[21:11]��ʾfn_hign,��Χ0~2047��
                                                     �ϱ�ʱ�̣�timing_validΪ��ʱ�ϱ���Ч */
        unsigned int  reserved  : 10; /* bit[22-31]: ���� */
    } reg;
} BBPCOMM_GS_FN_DSP_UNION;
#define BBPCOMM_GS_FN_DSP_gs_fn_dsp_START  (0)
#define BBPCOMM_GS_FN_DSP_gs_fn_dsp_END    (21)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GS_QB_DSP_UNION
 �ṹ˵��  : GS_QB_DSP �Ĵ����ṹ���塣��ַƫ����:0x067C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gs_qb_dsp_reg;
    struct
    {
        unsigned int  o_gs_qb_dsp : 13; /* bit[0-12] : GS��ϵͳ��ʱQb��Ϣ����DSP ����timing_get_ind�����ϱ���
                                                        [12:0]��ʾ GSϵͳ��ʱ֡��Qb������Դ��gs_timing_b[12:0]������Χ0~4999��
                                                       �ϱ�ʱ�̣�timing_validΪ��ʱ�ϱ���Ч */
        unsigned int  reserved    : 19; /* bit[13-31]: ���� */
    } reg;
} BBPCOMM_GS_QB_DSP_UNION;
#define BBPCOMM_GS_QB_DSP_o_gs_qb_dsp_START  (0)
#define BBPCOMM_GS_QB_DSP_o_gs_qb_dsp_END    (12)


/*****************************************************************************
 �ṹ��    : BBPCOMM_LTE_TIMING_DSP_UNION
 �ṹ˵��  : LTE_TIMING_DSP �Ĵ����ṹ���塣��ַƫ����:0x0680����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      lte_timing_dsp_reg;
    struct
    {
        unsigned int  o_lte_sys_ts_cnt_dsp     : 15; /* bit[0-14] : [14:0]����֡�ڼ�����  */
        unsigned int  reserved_0               : 1;  /* bit[15-15]: ���� */
        unsigned int  o_lte_sys_subfrm_cnt_dsp : 4;  /* bit[16-19]: [19:16]����֡���� */
        unsigned int  o_lte_sfn_dsp            : 10; /* bit[20-29]: LTE��ϵͳ��ʱ����DSP ����timing_get_ind�����ϱ����ϱ�ʱ�̣�timing_validΪ��ʱ�ϱ���Ч��
                                                                    ����:
                                                                    [29:20]��ʾSFN��������Χ0~1023 */
        unsigned int  reserved_1               : 2;  /* bit[30-31]: ���� */
    } reg;
} BBPCOMM_LTE_TIMING_DSP_UNION;
#define BBPCOMM_LTE_TIMING_DSP_o_lte_sys_ts_cnt_dsp_START      (0)
#define BBPCOMM_LTE_TIMING_DSP_o_lte_sys_ts_cnt_dsp_END        (14)
#define BBPCOMM_LTE_TIMING_DSP_o_lte_sys_subfrm_cnt_dsp_START  (16)
#define BBPCOMM_LTE_TIMING_DSP_o_lte_sys_subfrm_cnt_dsp_END    (19)
#define BBPCOMM_LTE_TIMING_DSP_o_lte_sfn_dsp_START             (20)
#define BBPCOMM_LTE_TIMING_DSP_o_lte_sfn_dsp_END               (29)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TDS_TIMING1_DSP_UNION
 �ṹ˵��  : TDS_TIMING1_DSP �Ĵ����ṹ���塣��ַƫ����:0x0684����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      tds_timing1_dsp_reg;
    struct
    {
        unsigned int  o_tds_timing1_dsp : 16; /* bit[0-15] : TDS��ϵͳ��ʱ����DSP ����timing_get_ind�����ϱ������Ĵ����ϱ�����TDS��tcfsrϵͳ��֡��0~65535ѭ��������TDSʵ����Ч��֡��ΧΪ0~8191
                                                             �ϱ�ʱ�̣�timing_validΪ��ʱ�ϱ���Ч */
        unsigned int  reserved          : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_TDS_TIMING1_DSP_UNION;
#define BBPCOMM_TDS_TIMING1_DSP_o_tds_timing1_dsp_START  (0)
#define BBPCOMM_TDS_TIMING1_DSP_o_tds_timing1_dsp_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TDS_TIMING2_DSP_UNION
 �ṹ˵��  : TDS_TIMING2_DSP �Ĵ����ṹ���塣��ַƫ����:0x0688����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      tds_timing2_dsp_reg;
    struct
    {
        unsigned int  o_tds_timing2_dsp : 20; /* bit[0-19] : TDS��ϵͳ��ʱ����DSP ����timing_get_ind�����ϱ������Ĵ����ϱ�������TDS��framc֡����
                                                             �ϱ�ʱ�̣�timing_validΪ��ʱ�ϱ���Ч */
        unsigned int  reserved          : 12; /* bit[20-31]: ���� */
    } reg;
} BBPCOMM_TDS_TIMING2_DSP_UNION;
#define BBPCOMM_TDS_TIMING2_DSP_o_tds_timing2_dsp_START  (0)
#define BBPCOMM_TDS_TIMING2_DSP_o_tds_timing2_dsp_END    (19)


/*****************************************************************************
 �ṹ��    : BBPCOMM_W_INTRASYS_VALID_UNION
 �ṹ˵��  : W_INTRASYS_VALID �Ĵ����ṹ���塣��ַƫ����:0x0698����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      w_intrasys_valid_reg;
    struct
    {
        unsigned int  o_w_intrasys_valid       : 1;  /* bit[0]   : w��ģ�¿���RFָʾ����ƽ�źš�
                                                                   1��b0: W����RF����Ȩ��
                                                                   1��b1: W���п���RFȨ����ʵ������RF��w_intrasys_valid_delay�ź�Ϊ1���� */
        unsigned int  o_w_intrasys_valid_delay : 1;  /* bit[1]   : w��ģ��ʵ�ʿ���RFָʾ����ƽ�źš�Ϊ1����W����RF����ͨ����Ϊ0�����ģ���Կ���RFͨ�������ڵ�RFICʱ��Ƶ��������źŵ�ѡͨ��
                                                                   w_intrasys_valid_delay�������ر�w_intrasys_valid�������ͺ��½���һ�¡� */
        unsigned int  reserved                 : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_W_INTRASYS_VALID_UNION;
#define BBPCOMM_W_INTRASYS_VALID_o_w_intrasys_valid_START        (0)
#define BBPCOMM_W_INTRASYS_VALID_o_w_intrasys_valid_END          (0)
#define BBPCOMM_W_INTRASYS_VALID_o_w_intrasys_valid_delay_START  (1)
#define BBPCOMM_W_INTRASYS_VALID_o_w_intrasys_valid_delay_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GM_INTRASYS_VALID_UNION
 �ṹ˵��  : GM_INTRASYS_VALID �Ĵ����ṹ���塣��ַƫ����:0x069C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gm_intrasys_valid_reg;
    struct
    {
        unsigned int  o_gm_intrasys_valid       : 1;  /* bit[0]   : gm��ģ�¿���RFָʾ����ƽ�źš�
                                                                    1��b0: gm����RF����Ȩ��
                                                                    1��b1: gm���п���RFȨ����ʵ������RF��gm_intrasys_valid_delay�ź�Ϊ1���� */
        unsigned int  o_gm_intrasys_valid_delay : 1;  /* bit[1]   : gm��ģ��ʵ�ʿ���RFָʾ����ƽ�źš�Ϊ1����gm����RF����ͨ����Ϊ0�����ģ���Կ���RFͨ�������ڵ�RFICʱ��Ƶ��������źŵ�ѡͨ��
                                                                    gm_intrasys_valid_delay�������ر�gm_intrasys_valid�������ͺ��½���һ�¡� */
        unsigned int  reserved                  : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_GM_INTRASYS_VALID_UNION;
#define BBPCOMM_GM_INTRASYS_VALID_o_gm_intrasys_valid_START        (0)
#define BBPCOMM_GM_INTRASYS_VALID_o_gm_intrasys_valid_END          (0)
#define BBPCOMM_GM_INTRASYS_VALID_o_gm_intrasys_valid_delay_START  (1)
#define BBPCOMM_GM_INTRASYS_VALID_o_gm_intrasys_valid_delay_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GS_INTRASYS_VALID_UNION
 �ṹ˵��  : GS_INTRASYS_VALID �Ĵ����ṹ���塣��ַƫ����:0x06A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gs_intrasys_valid_reg;
    struct
    {
        unsigned int  o_gs_intrasys_valid       : 1;  /* bit[0]   : gs��ģ�¿���RFָʾ����ƽ�źš�
                                                                    1��b0: gs����RF����Ȩ��
                                                                    1��b1: gs���п���RFȨ����ʵ������RF��gs_intrasys_valid_delay�ź�Ϊ1���� */
        unsigned int  o_gs_intrasys_valid_delay : 1;  /* bit[1]   : gs��ģ��ʵ�ʿ���RFָʾ����ƽ�źš�Ϊ1����gs����RF����ͨ����Ϊ0�����ģ���Կ���RFͨ�������ڵ�RFICʱ��Ƶ��������źŵ�ѡͨ��
                                                                    gs_intrasys_valid_delay�������ر�gs_intrasys_valid�������ͺ��½���һ�¡� */
        unsigned int  reserved                  : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_GS_INTRASYS_VALID_UNION;
#define BBPCOMM_GS_INTRASYS_VALID_o_gs_intrasys_valid_START        (0)
#define BBPCOMM_GS_INTRASYS_VALID_o_gs_intrasys_valid_END          (0)
#define BBPCOMM_GS_INTRASYS_VALID_o_gs_intrasys_valid_delay_START  (1)
#define BBPCOMM_GS_INTRASYS_VALID_o_gs_intrasys_valid_delay_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_LTE_INTRASYS_VALID_UNION
 �ṹ˵��  : LTE_INTRASYS_VALID �Ĵ����ṹ���塣��ַƫ����:0x06A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      lte_intrasys_valid_reg;
    struct
    {
        unsigned int  o_lte_intrasys_valid       : 1;  /* bit[0]   : Lte��ģ�¿���RFָʾ����ƽ�źš�
                                                                     1��b0: LTE����RF����Ȩ��
                                                                     1��b1: LTE���п���RFȨ����ʵ������RF��lte_intrasys_valid_delay�ź�Ϊ1���� */
        unsigned int  o_lte_intrasys_valid_delay : 1;  /* bit[1]   : LTE��ģ��ʵ�ʿ���RFָʾ����ƽ�źš�Ϊ1����LTE����RF����ͨ����Ϊ0�����ģ���Կ���RFͨ�������ڵ�RFICʱ��Ƶ��������źŵ�ѡͨ��
                                                                     lte_intrasys_valid_delay�������ر�lte_intrasys_valid�������ͺ��½���һ�¡� */
        unsigned int  reserved                   : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_LTE_INTRASYS_VALID_UNION;
#define BBPCOMM_LTE_INTRASYS_VALID_o_lte_intrasys_valid_START        (0)
#define BBPCOMM_LTE_INTRASYS_VALID_o_lte_intrasys_valid_END          (0)
#define BBPCOMM_LTE_INTRASYS_VALID_o_lte_intrasys_valid_delay_START  (1)
#define BBPCOMM_LTE_INTRASYS_VALID_o_lte_intrasys_valid_delay_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TDS_INTRASYS_VALID_UNION
 �ṹ˵��  : TDS_INTRASYS_VALID �Ĵ����ṹ���塣��ַƫ����:0x06A8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      tds_intrasys_valid_reg;
    struct
    {
        unsigned int  o_tds_intrasys_valid       : 1;  /* bit[0]   : TDS��ģ�¿���RFָʾ����ƽ�źš�
                                                                     1��b0: TDS����RF����Ȩ��
                                                                     1��b1: TDS���п���RFȨ����ʵ������RF��tds_intrasys_valid_delay�ź�Ϊ1���� */
        unsigned int  o_tds_intrasys_valid_delay : 1;  /* bit[1]   : TDS��ģ��ʵ�ʿ���RFָʾ����ƽ�źš�Ϊ1����TDS����RF����ͨ����Ϊ0�����ģ���Կ���RFͨ�������ڵ�RFICʱ��Ƶ��������źŵ�ѡͨ��
                                                                     tds_intrasys_valid_delay�������ر�tds_intrasys_valid�������ͺ��½���һ�¡� */
        unsigned int  reserved                   : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_TDS_INTRASYS_VALID_UNION;
#define BBPCOMM_TDS_INTRASYS_VALID_o_tds_intrasys_valid_START        (0)
#define BBPCOMM_TDS_INTRASYS_VALID_o_tds_intrasys_valid_END          (0)
#define BBPCOMM_TDS_INTRASYS_VALID_o_tds_intrasys_valid_delay_START  (1)
#define BBPCOMM_TDS_INTRASYS_VALID_o_tds_intrasys_valid_delay_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_RFIC_CK_CFG_UNION
 �ṹ˵��  : RFIC_CK_CFG �Ĵ����ṹ���塣��ַƫ����:0x06AC����ֵ:0x00000049�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      rfic_ck_cfg_reg;
    struct
    {
        unsigned int  cpu_rfic0_ck_cfg : 3;  /* bit[0-2] : SSI0master�ȴ�ʱ�� */
        unsigned int  cpu_rfic1_ck_cfg : 3;  /* bit[3-5] : SSI1master�ȴ�ʱ�� */
        unsigned int  cpu_rfic2_ck_cfg : 3;  /* bit[6-8] : SSI2master�ȴ�ʱ�� */
        unsigned int  reserved         : 23; /* bit[9-31]: ���� */
    } reg;
} BBPCOMM_RFIC_CK_CFG_UNION;
#define BBPCOMM_RFIC_CK_CFG_cpu_rfic0_ck_cfg_START  (0)
#define BBPCOMM_RFIC_CK_CFG_cpu_rfic0_ck_cfg_END    (2)
#define BBPCOMM_RFIC_CK_CFG_cpu_rfic1_ck_cfg_START  (3)
#define BBPCOMM_RFIC_CK_CFG_cpu_rfic1_ck_cfg_END    (5)
#define BBPCOMM_RFIC_CK_CFG_cpu_rfic2_ck_cfg_START  (6)
#define BBPCOMM_RFIC_CK_CFG_cpu_rfic2_ck_cfg_END    (8)


/*****************************************************************************
 �ṹ��    : BBPCOMM_DSP_WAITTIME_UNION
 �ṹ˵��  : DSP_WAITTIME �Ĵ����ṹ���塣��ַƫ����:0x06B4����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dsp_waittime_reg;
    struct
    {
        unsigned int  dsp_mipi_wait_time : 8;  /* bit[0-7]  : ͨ��xbbp��MIPI master�����ض���ָ��ʱ,DSP�ȴ��ض������������ */
        unsigned int  dsp_ssi_wait_time  : 8;  /* bit[8-15] : ͨ��xbbp��SSI master�����ض���ָ��ʱ,DSP�ȴ��ض������������ */
        unsigned int  reserved           : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_DSP_WAITTIME_UNION;
#define BBPCOMM_DSP_WAITTIME_dsp_mipi_wait_time_START  (0)
#define BBPCOMM_DSP_WAITTIME_dsp_mipi_wait_time_END    (7)
#define BBPCOMM_DSP_WAITTIME_dsp_ssi_wait_time_START   (8)
#define BBPCOMM_DSP_WAITTIME_dsp_ssi_wait_time_END     (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_DSP_CTU_TIMING_GET_IND_UNION
 �ṹ˵��  : DSP_CTU_TIMING_GET_IND �Ĵ����ṹ���塣��ַƫ����:0x06BC����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dsp_ctu_timing_get_ind_reg;
    struct
    {
        unsigned int  dsp_ctu_timing_get_ind : 1;  /* bit[0]   : CTU�ڲ�19.2M��������ʱ�����������ȡʹ�� */
        unsigned int  reserved               : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_DSP_CTU_TIMING_GET_IND_UNION;
#define BBPCOMM_DSP_CTU_TIMING_GET_IND_dsp_ctu_timing_get_ind_START  (0)
#define BBPCOMM_DSP_CTU_TIMING_GET_IND_dsp_ctu_timing_get_ind_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CTU_TIMING_VALID_DSP_UNION
 �ṹ˵��  : CTU_TIMING_VALID_DSP �Ĵ����ṹ���塣��ַƫ����:0x06C0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      ctu_timing_valid_dsp_reg;
    struct
    {
        unsigned int  ctu_timing_valid_dsp : 1;  /* bit[0]   : CTU�ڲ�19.2M��������ʱ�����������ȡ��Чָʾ */
        unsigned int  reserved             : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_CTU_TIMING_VALID_DSP_UNION;
#define BBPCOMM_CTU_TIMING_VALID_DSP_ctu_timing_valid_dsp_START  (0)
#define BBPCOMM_CTU_TIMING_VALID_DSP_ctu_timing_valid_dsp_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_DSP_CTU_TIMING_CLR_UNION
 �ṹ˵��  : DSP_CTU_TIMING_CLR �Ĵ����ṹ���塣��ַƫ����:0x06C4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dsp_ctu_timing_clr_reg;
    struct
    {
        unsigned int  dsp_ctu_timing_clr : 1;  /* bit[0]   : CTU�ڲ�19.2M��������ʱ�����������ȡ������ʹ�� */
        unsigned int  reserved           : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_DSP_CTU_TIMING_CLR_UNION;
#define BBPCOMM_DSP_CTU_TIMING_CLR_dsp_ctu_timing_clr_START  (0)
#define BBPCOMM_DSP_CTU_TIMING_CLR_dsp_ctu_timing_clr_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_W_INTERSYS_MEASURE_TYPE_UNION
 �ṹ˵��  : W_INTERSYS_MEASURE_TYPE �Ĵ����ṹ���塣��ַƫ����:0x06C8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      w_intersys_measure_type_reg;
    struct
    {
        unsigned int  w_intersys_measure_type : 4;  /* bit[0-3] : ��ϵͳ�������͡�
                                                                  4��b0������3G��
                                                                  4��b1: 3G�����ѣ�
                                                                  4��d2: 3G ANR��
                                                                  ����Ԥ����
                                                                  ��Чʱ�̣�������Ч */
        unsigned int  reserved                : 28; /* bit[4-31]: ���� */
    } reg;
} BBPCOMM_W_INTERSYS_MEASURE_TYPE_UNION;
#define BBPCOMM_W_INTERSYS_MEASURE_TYPE_w_intersys_measure_type_START  (0)
#define BBPCOMM_W_INTERSYS_MEASURE_TYPE_w_intersys_measure_type_END    (3)


/*****************************************************************************
 �ṹ��    : BBPCOMM_W_MEASURE_REPORT_VALID_UNION
 �ṹ˵��  : W_MEASURE_REPORT_VALID �Ĵ����ṹ���塣��ַƫ����:0x06CC����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      w_measure_report_valid_reg;
    struct
    {
        unsigned int  w_measure_report_valid : 1;  /* bit[0-0] : ��Ƶ��������ڵ�ָʾ��L����TDS/Gm/Gs��Ϊ��ģ��֪ͨW DSP W�����ĵ�Ƶ�����ڵ��
                                                                 ֻ������̬����Ҫ���á�
                                                                 ��ƽ�źţ�����Ч��
                                                                 ��Чʱ�̣�������Ч */
        unsigned int  reserved               : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_W_MEASURE_REPORT_VALID_UNION;
#define BBPCOMM_W_MEASURE_REPORT_VALID_w_measure_report_valid_START  (0)
#define BBPCOMM_W_MEASURE_REPORT_VALID_w_measure_report_valid_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_W_RCV_LTE_UNION
 �ṹ˵��  : INT_CLEAR_W_RCV_LTE �Ĵ����ṹ���塣��ַƫ����:0x06D8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_w_rcv_lte_reg;
    struct
    {
        unsigned int  int_clear_w_rcv_lte : 16; /* bit[0-15] : �߼������㡣
                                                               �жϱ�־���ָʾ������Ч���������INT_TYPE_W_RCV_LTE[15:0]��Ӧbitλ
                                                               ��Чʱ�̣�������Ч */
        unsigned int  reserved            : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_W_RCV_LTE_UNION;
#define BBPCOMM_INT_CLEAR_W_RCV_LTE_int_clear_w_rcv_lte_START  (0)
#define BBPCOMM_INT_CLEAR_W_RCV_LTE_int_clear_w_rcv_lte_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_W_RCV_TDS_UNION
 �ṹ˵��  : INT_CLEAR_W_RCV_TDS �Ĵ����ṹ���塣��ַƫ����:0x06DC����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_w_rcv_tds_reg;
    struct
    {
        unsigned int  int_clear_w_rcv_tds : 16; /* bit[0-15] : �߼������㡣
                                                               �жϱ�־���ָʾ������Ч���������INT_TYPE_W_RCV_TDS[15:0]��Ӧbitλ
                                                               ��Чʱ�̣�������Ч */
        unsigned int  reserved            : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_W_RCV_TDS_UNION;
#define BBPCOMM_INT_CLEAR_W_RCV_TDS_int_clear_w_rcv_tds_START  (0)
#define BBPCOMM_INT_CLEAR_W_RCV_TDS_int_clear_w_rcv_tds_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_W_RCV_GM_UNION
 �ṹ˵��  : INT_CLEAR_W_RCV_GM �Ĵ����ṹ���塣��ַƫ����:0x06E0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_w_rcv_gm_reg;
    struct
    {
        unsigned int  int_clear_w_rcv_gm : 16; /* bit[0-15] : �߼������㡣
                                                              �жϱ�־���ָʾ������Ч���������INT_TYPE_W_RCV_GM[15:0]��Ӧbitλ
                                                              ��Чʱ�̣�������Ч */
        unsigned int  reserved           : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_W_RCV_GM_UNION;
#define BBPCOMM_INT_CLEAR_W_RCV_GM_int_clear_w_rcv_gm_START  (0)
#define BBPCOMM_INT_CLEAR_W_RCV_GM_int_clear_w_rcv_gm_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_W_RCV_GS_UNION
 �ṹ˵��  : INT_CLEAR_W_RCV_GS �Ĵ����ṹ���塣��ַƫ����:0x06E4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_w_rcv_gs_reg;
    struct
    {
        unsigned int  int_clear_w_rcv_gs : 16; /* bit[0-15] : �߼������㡣
                                                              �жϱ�־���ָʾ������Ч���������INT_TYPE_W_RCV_GS[15:0]��Ӧbitλ
                                                              ��Чʱ�̣�������Ч */
        unsigned int  reserved           : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_W_RCV_GS_UNION;
#define BBPCOMM_INT_CLEAR_W_RCV_GS_int_clear_w_rcv_gs_START  (0)
#define BBPCOMM_INT_CLEAR_W_RCV_GS_int_clear_w_rcv_gs_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_W_RCV_W_UNION
 �ṹ˵��  : INT_CLEAR_W_RCV_W �Ĵ����ṹ���塣��ַƫ����:0x06E8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_w_rcv_w_reg;
    struct
    {
        unsigned int  int_clear_w_rcv_w : 16; /* bit[0-15] : �߼������㡣
                                                             �жϱ�־���ָʾ������Ч���������INT_TYPE_W_RCV_W[15:0]��Ӧbitλ
                                                             ��Чʱ�̣�������Ч */
        unsigned int  reserved          : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_W_RCV_W_UNION;
#define BBPCOMM_INT_CLEAR_W_RCV_W_int_clear_w_rcv_w_START  (0)
#define BBPCOMM_INT_CLEAR_W_RCV_W_int_clear_w_rcv_w_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_W_INT012_UNION
 �ṹ˵��  : INT_CLEAR_W_INT012 �Ĵ����ṹ���塣��ַƫ����:0x06EC����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_w_int012_reg;
    struct
    {
        unsigned int  int_clear_w_int012 : 3;  /* bit[0-2] : �߼������㡣
                                                             �жϱ�־���ָʾ������Ч���������INT_TYPE_W_INT012[2:0]��Ӧbitλ
                                                             ��Чʱ�̣�������Ч */
        unsigned int  reserved           : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_W_INT012_UNION;
#define BBPCOMM_INT_CLEAR_W_INT012_int_clear_w_int012_START  (0)
#define BBPCOMM_INT_CLEAR_W_INT012_int_clear_w_int012_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_W_RCV_LTE_UNION
 �ṹ˵��  : INT_MASK_W_RCV_LTE �Ĵ����ṹ���塣��ַƫ����:0x06F0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_w_rcv_lte_reg;
    struct
    {
        unsigned int  int_mask_w_rcv_lte : 16; /* bit[0-15] : �ж����α�־����������INT_TYPE_W_RCV_LTE[15:0]��Ӧbit�жϡ�
                                                              0�������ж��ϱ���
                                                              1��ʹ���ж��ϱ���
                                                              ����ʱ�̣���ʼ��
                                                              ��Чʱ�̣�������Ч */
        unsigned int  reserved           : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_W_RCV_LTE_UNION;
#define BBPCOMM_INT_MASK_W_RCV_LTE_int_mask_w_rcv_lte_START  (0)
#define BBPCOMM_INT_MASK_W_RCV_LTE_int_mask_w_rcv_lte_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_W_RCV_TDS_UNION
 �ṹ˵��  : INT_MASK_W_RCV_TDS �Ĵ����ṹ���塣��ַƫ����:0x06F4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_w_rcv_tds_reg;
    struct
    {
        unsigned int  int_mask_w_rcv_tds : 16; /* bit[0-15] : �ж����α�־����������INT_TYPE_W_RCV_TDS[15:0]��Ӧbit�жϡ�
                                                              0�������ж��ϱ���
                                                              1��ʹ���ж��ϱ���
                                                              ����ʱ�̣���ʼ��
                                                              ��Чʱ�̣�������Ч */
        unsigned int  reserved           : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_W_RCV_TDS_UNION;
#define BBPCOMM_INT_MASK_W_RCV_TDS_int_mask_w_rcv_tds_START  (0)
#define BBPCOMM_INT_MASK_W_RCV_TDS_int_mask_w_rcv_tds_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_W_RCV_GM_UNION
 �ṹ˵��  : INT_MASK_W_RCV_GM �Ĵ����ṹ���塣��ַƫ����:0x06F8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_w_rcv_gm_reg;
    struct
    {
        unsigned int  int_mask_w_rcv_gm : 16; /* bit[0-15] : �ж����α�־����������INT_TYPE_W_RCV_GM[15:0]��Ӧbit�жϡ�
                                                             0�������ж��ϱ���
                                                             1��ʹ���ж��ϱ���
                                                             ����ʱ�̣���ʼ��
                                                             ��Чʱ�̣�������Ч */
        unsigned int  reserved          : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_W_RCV_GM_UNION;
#define BBPCOMM_INT_MASK_W_RCV_GM_int_mask_w_rcv_gm_START  (0)
#define BBPCOMM_INT_MASK_W_RCV_GM_int_mask_w_rcv_gm_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_W_RCV_GS_UNION
 �ṹ˵��  : INT_MASK_W_RCV_GS �Ĵ����ṹ���塣��ַƫ����:0x06FC����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_w_rcv_gs_reg;
    struct
    {
        unsigned int  int_mask_w_rcv_gs : 16; /* bit[0-15] : �ж����α�־����������INT_TYPE_W_RCV_GS[15:0]��Ӧbit�жϡ�
                                                             0�������ж��ϱ���
                                                             1��ʹ���ж��ϱ���
                                                             ����ʱ�̣���ʼ��
                                                             ��Чʱ�̣�������Ч */
        unsigned int  reserved          : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_W_RCV_GS_UNION;
#define BBPCOMM_INT_MASK_W_RCV_GS_int_mask_w_rcv_gs_START  (0)
#define BBPCOMM_INT_MASK_W_RCV_GS_int_mask_w_rcv_gs_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_W_RCV_W_UNION
 �ṹ˵��  : INT_MASK_W_RCV_W �Ĵ����ṹ���塣��ַƫ����:0x0700����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_w_rcv_w_reg;
    struct
    {
        unsigned int  int_mask_w_rcv_w : 16; /* bit[0-15] : �ж����α�־����������INT_TYPE_W_RCV_W[15:0]��Ӧbit�жϡ�
                                                            0�������ж��ϱ���
                                                            1��ʹ���ж��ϱ���
                                                            ����ʱ�̣���ʼ��
                                                            ��Чʱ�̣�������Ч */
        unsigned int  reserved         : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_W_RCV_W_UNION;
#define BBPCOMM_INT_MASK_W_RCV_W_int_mask_w_rcv_w_START  (0)
#define BBPCOMM_INT_MASK_W_RCV_W_int_mask_w_rcv_w_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_W_INT012_UNION
 �ṹ˵��  : INT_MASK_W_INT012 �Ĵ����ṹ���塣��ַƫ����:0x0704����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_w_int012_reg;
    struct
    {
        unsigned int  int_mask_w_int012 : 3;  /* bit[0-2] : �ж����α�־����������INT_TYPE_W_INT012[2:0]��Ӧbit�жϡ�
                                                            0�������ж��ϱ���
                                                            1��ʹ���ж��ϱ���
                                                            ����ʱ�̣���ʼ��
                                                            ��Чʱ�̣�������Ч */
        unsigned int  reserved          : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_W_INT012_UNION;
#define BBPCOMM_INT_MASK_W_INT012_int_mask_w_int012_START  (0)
#define BBPCOMM_INT_MASK_W_INT012_int_mask_w_int012_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_W_RCV_LTE_UNION
 �ṹ˵��  : INT_TYPE_W_RCV_LTE �Ĵ����ṹ���塣��ַƫ����:0x0708����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_w_rcv_lte_reg;
    struct
    {
        unsigned int  o_int_type_w_rcv_lte : 16; /* bit[0-15] : �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
                                                                [0]: �ж�����0�� LTE����ģ����ǰ֪ͨW��ϵͳ���������жϡ�
                                                                [1]: �ж�����1�� LTE����ģ����GAP�жϣ�֪ͨW������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
                                                                [2]: �ж�����2�� LTE����ģ����GAP�жϡ�
                                                                [3]: �ж�����3��LTE����ģ�����������жϡ�
                                                                [4]: �ж�����4��LTE����ģ��ǿ��W�˳���ϵͳ�����жϡ�
                                                                [5]: �ж�����5��LTE����ģ��֪ͨW�ϱ����β��������
                                                                [6]: ������
                                                                [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
                                                                �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x06F0��int_mask_w_rcv_lte���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved             : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_W_RCV_LTE_UNION;
#define BBPCOMM_INT_TYPE_W_RCV_LTE_o_int_type_w_rcv_lte_START  (0)
#define BBPCOMM_INT_TYPE_W_RCV_LTE_o_int_type_w_rcv_lte_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_W_RCV_TDS_UNION
 �ṹ˵��  : INT_TYPE_W_RCV_TDS �Ĵ����ṹ���塣��ַƫ����:0x070C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_w_rcv_tds_reg;
    struct
    {
        unsigned int  o_int_type_w_rcv_tds : 16; /* bit[0-15] : �ж�״̬��־0��1��2ֻ�е�TDS������ģʱ���ܲ�����
                                                                
                                                                [0]: �ж�����0�� TDS����ģ����ǰ֪ͨW��ϵͳ���������жϡ�
                                                                [1]: �ж�����1�� TDS����ģ����GAP�жϣ�֪ͨW������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
                                                                [2]: �ж�����2�� TDS����ģ����GAP�жϡ�
                                                                [3]: �ж�����3��TDS����ģ�����������жϡ�
                                                                [4]: �ж�����4��TDS����ģ��ǿ��W�˳���ϵͳ�����жϡ�
                                                                [5]: �ж�����5��TDS����ģ��֪ͨW�ϱ����β��������
                                                                [6]: �ж�����6��������
                                                                [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
                                                                �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x06F4��int_mask_w_rcv_tds���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved             : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_W_RCV_TDS_UNION;
#define BBPCOMM_INT_TYPE_W_RCV_TDS_o_int_type_w_rcv_tds_START  (0)
#define BBPCOMM_INT_TYPE_W_RCV_TDS_o_int_type_w_rcv_tds_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_W_RCV_GM_UNION
 �ṹ˵��  : INT_TYPE_W_RCV_GM �Ĵ����ṹ���塣��ַƫ����:0x0710����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_w_rcv_gm_reg;
    struct
    {
        unsigned int  o_int_type_w_rcv_gm : 16; /* bit[0-15] : �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
                                                               [0]: �ж�����0��GM����ģ����ǰ֪ͨW��ϵͳ���������жϡ�
                                                               [1]: �ж�����1��GM����ģ����GAP�жϣ�֪ͨW������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
                                                               [2]: �ж�����2��GM����ģ����GAP�жϡ�
                                                               [3]: �ж�����3��GM����ģ�����������жϡ�
                                                               [4]: �ж�����4��GM����ģ��ǿ��W�˳���ϵͳ�����жϡ�
                                                               [5]: �ж�����5��GM����ģ��֪ͨW�ϱ����β��������
                                                               [6]: �ж�����6��������
                                                               [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
                                                               �ж�״̬��־0��1��2ֻ�е�GM������ģʱ���ܲ�����
                                                               �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x06F8��int_mask_w_rcv_gm���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved            : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_W_RCV_GM_UNION;
#define BBPCOMM_INT_TYPE_W_RCV_GM_o_int_type_w_rcv_gm_START  (0)
#define BBPCOMM_INT_TYPE_W_RCV_GM_o_int_type_w_rcv_gm_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_W_RCV_GS_UNION
 �ṹ˵��  : INT_TYPE_W_RCV_GS �Ĵ����ṹ���塣��ַƫ����:0x0714����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_w_rcv_gs_reg;
    struct
    {
        unsigned int  o_int_type_w_rcv_gs : 16; /* bit[0-15] : [0]: �ж�����0��GS����ģ����ǰ֪ͨW��ϵͳ���������жϡ�
                                                               [1]: �ж�����1��GS����ģ����GAP�жϣ�֪ͨW������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
                                                               [2]: �ж�����2��GS����ģ����GAP�жϡ�
                                                               [3]: �ж�����3��GS����ģ�����������жϡ�
                                                               [4]: �ж�����4��GS����ģ��ǿ��W�˳���ϵͳ�����жϡ�
                                                               [5]: �ж�����5��GS����ģ��֪ͨW�ϱ����β��������
                                                               [6]: �ж�����6��������
                                                               [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
                                                               �ж�״̬��־0��1��2ֻ�е�TDS������ģʱ���ܲ�����
                                                               �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x06FC��int_mask_w_rcv_gs���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved            : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_W_RCV_GS_UNION;
#define BBPCOMM_INT_TYPE_W_RCV_GS_o_int_type_w_rcv_gs_START  (0)
#define BBPCOMM_INT_TYPE_W_RCV_GS_o_int_type_w_rcv_gs_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_W_RCV_W_UNION
 �ṹ˵��  : INT_TYPE_W_RCV_W �Ĵ����ṹ���塣��ַƫ����:0x0718����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_w_rcv_w_reg;
    struct
    {
        unsigned int  o_int_type_w_rcv_w : 16; /* bit[0-15] : �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
                                                              [0]: �ж�����0��W����ģ����ǰ֪ͨW��Ƶ���������жϡ�
                                                              [1]: �ж�����1��W����ģ����GAP�жϣ�֪ͨW������Ƶ������Ƶͨ�����ã������л��Ȳ�����
                                                              [2]: �ж�����2��W����ģ����GAP�жϡ�
                                                              [3]: �ж�����3��W����ģ������Ƶ�����������жϡ�
                                                              [4]: �ж�����4��W����ģ��ǿ��W�˳���Ƶ�����жϡ�
                                                              [5]: �ж�����5��W����ģ��֪ͨW�ϱ����β��������
                                                              [6]: �ж�����6��������
                                                              [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
                                                              �ж�״̬��־0��1��2ֻ�е�W������ģʱ���ܲ�����
                                                              �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x0700��int_mask_w_rcv_w���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved           : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_W_RCV_W_UNION;
#define BBPCOMM_INT_TYPE_W_RCV_W_o_int_type_w_rcv_w_START  (0)
#define BBPCOMM_INT_TYPE_W_RCV_W_o_int_type_w_rcv_w_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_W_INT012_UNION
 �ṹ˵��  : INT_TYPE_W_INT012 �Ĵ����ṹ���塣��ַƫ����:0x071C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_w_int012_reg;
    struct
    {
        unsigned int  o_int_type_w_int012 : 3;  /* bit[0-2] : ������ģ����int0��1��2���ϱ���(������Ƶ����ϵͳ����)��������Ч��
                                                              [0]: W��ģʱ��CTU����֪ͨWDSP����int0�жϡ�
                                                              [1]: W��ģʱ��CTU����֪ͨWDSP����int1�жϡ�
                                                              [2]: W��ģʱ��CTU����֪ͨWDSP����int2�жϡ�
                                                              �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x0704��int_mask_w_int012���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved            : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_W_INT012_UNION;
#define BBPCOMM_INT_TYPE_W_INT012_o_int_type_w_int012_START  (0)
#define BBPCOMM_INT_TYPE_W_INT012_o_int_type_w_int012_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_W_SND_LTE_INT_13_UNION
 �ṹ˵��  : W_SND_LTE_INT_13 �Ĵ����ṹ���塣��ַƫ����:0x0720����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      w_snd_lte_int_13_reg;
    struct
    {
        unsigned int  reserved_0       : 3;  /* bit[0-2]  : ���� */
        unsigned int  w_snd_lte_int_13 : 13; /* bit[3-15] : �߼������㡣����Ч��
                                                            
                                                            bit15~7����Ӧw_snd_lte_int_15 ~ 7��
                                                            W DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_lte_rcv_w[15:7]����LDSP��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit6����Ӧw_snd_lte_int_6��
                                                            WDSPͨ���˼Ĵ�����������6�жϣ�int_type_lte_rcv_w[6]����LDSP��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit5����Ӧw_snd_lte_int_5��
                                                            W��ģʱ֪ͨLDSP L�������ڵ������Ч��
                                                            W DSPͨ���˼Ĵ�����������5�жϣ�int_type_lte_rcv_w[5]����LDSP��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit4����Ӧw_snd_lte_int_4��
                                                            W��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
                                                            W DSPͨ���˼Ĵ�����������4�жϣ�int_type_lte_rcv_w[4]����LDSP��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit3����Ӧw_snd_lte_int_3��W��������ָʾ������Ч��
                                                            ���ڴ����ж�����3 ��int_type_lte_rcv_w[3]����LDSP��L��ģ�¶�W������ϵͳ����ʱ�����W����������W DSP���ô˱�־Ϊ1�� 
                                                            ��Чʱ�̣�������Ч */
        unsigned int  reserved_1       : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_W_SND_LTE_INT_13_UNION;
#define BBPCOMM_W_SND_LTE_INT_13_w_snd_lte_int_13_START  (3)
#define BBPCOMM_W_SND_LTE_INT_13_w_snd_lte_int_13_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_W_SND_TDS_INT_13_UNION
 �ṹ˵��  : W_SND_TDS_INT_13 �Ĵ����ṹ���塣��ַƫ����:0x0724����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      w_snd_tds_int_13_reg;
    struct
    {
        unsigned int  reserved_0       : 3;  /* bit[0-2]  : ���� */
        unsigned int  w_snd_tds_int_13 : 13; /* bit[3-15] : �߼������㡣����Ч��
                                                            
                                                            bit15~7����Ӧw_snd_tds_int_15 ~ 7��
                                                            W DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_tds_rcv_w[15:7]����TDSP��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit6����Ӧw_snd_tds_int_6��
                                                            WDSPͨ���˼Ĵ�����������6�жϣ�int_type_tds_rcv_w[6]����TDSP��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit5����Ӧw_snd_tds_int_5��
                                                            W��ģʱ֪ͨTDSP T�������ڵ������Ч��
                                                            W DSPͨ���˼Ĵ�����������5�жϣ�int_type_tds_rcv_w[5]����TDSP��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit4����Ӧw_snd_tds_int_4��
                                                            W��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
                                                            W DSPͨ���˼Ĵ�����������4�жϣ�int_type_tds_rcv_w[4]����TDSP��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit3����Ӧw_snd_tds_int_3��W��������ָʾ������Ч��
                                                            ���ڴ����ж�����3 ��int_type_tds_rcv_w[3]����TDSP��T��ģ�¶�W������ϵͳ����ʱ�����W����������W DSP���ô˱�־Ϊ1�� 
                                                            ��Чʱ�̣�������Ч */
        unsigned int  reserved_1       : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_W_SND_TDS_INT_13_UNION;
#define BBPCOMM_W_SND_TDS_INT_13_w_snd_tds_int_13_START  (3)
#define BBPCOMM_W_SND_TDS_INT_13_w_snd_tds_int_13_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_W_SND_GM_INT_13_UNION
 �ṹ˵��  : W_SND_GM_INT_13 �Ĵ����ṹ���塣��ַƫ����:0x0728����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      w_snd_gm_int_13_reg;
    struct
    {
        unsigned int  reserved_0      : 3;  /* bit[0-2]  : ���� */
        unsigned int  w_snd_gm_int_13 : 13; /* bit[3-15] : �߼������㡣����Ч��
                                                           
                                                           bit15~7����Ӧw_snd_gm_int_15 ~ 7��
                                                           W DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_gm_rcv_w[15:7]����GMDSP��
                                                           ��Чʱ�̣�������Ч
                                                           
                                                           bit6����Ӧw_snd_gm_int_6��
                                                           WDSPͨ���˼Ĵ�����������6�жϣ�int_type_gm_rcv_w[6]����GMDSP��
                                                           ��Чʱ�̣�������Ч
                                                           
                                                           bit5����Ӧw_snd_gm_int_5��
                                                           W��ģʱ֪ͨGMDSP GM�������ڵ������Ч��
                                                           W DSPͨ���˼Ĵ�����������5�жϣ�int_type_gm_rcv_w[5]����GMDSP��
                                                           ��Чʱ�̣�������Ч
                                                           
                                                           bit4����Ӧw_snd_gm_int_4��
                                                           W��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
                                                           W DSPͨ���˼Ĵ�����������4�жϣ�int_type_gm_rcv_w[4]����GMDSP��
                                                           ��Чʱ�̣�������Ч
                                                           
                                                           bit3����Ӧw_snd_gm_int_3��W��������ָʾ������Ч��
                                                           ���ڴ����ж�����3 ��int_type_gm_rcv_w[3]����GMDSP��GM��ģ�¶�W������ϵͳ����ʱ�����W����������W DSP���ô˱�־Ϊ1�� 
                                                           ��Чʱ�̣�������Ч */
        unsigned int  reserved_1      : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_W_SND_GM_INT_13_UNION;
#define BBPCOMM_W_SND_GM_INT_13_w_snd_gm_int_13_START  (3)
#define BBPCOMM_W_SND_GM_INT_13_w_snd_gm_int_13_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_W_SND_GS_INT_13_UNION
 �ṹ˵��  : W_SND_GS_INT_13 �Ĵ����ṹ���塣��ַƫ����:0x072C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      w_snd_gs_int_13_reg;
    struct
    {
        unsigned int  reserved_0      : 3;  /* bit[0-2]  : ���� */
        unsigned int  w_snd_gs_int_13 : 13; /* bit[3-15] : �߼������㡣����Ч��
                                                           
                                                           bit15~7����Ӧw_snd_gs_int_15 ~ 7��
                                                           W DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_gs_rcv_w[15:7]����GSDSP��
                                                           ��Чʱ�̣�������Ч
                                                           
                                                           bit6����Ӧw_snd_gs_int_6��
                                                           WDSPͨ���˼Ĵ�����������6�жϣ�int_type_gs_rcv_w[6]����GSDSP��
                                                           ��Чʱ�̣�������Ч
                                                           
                                                           bit5����Ӧw_snd_gs_int_5��
                                                           W��ģʱ֪ͨGSDSP GS�������ڵ������Ч��
                                                           W DSPͨ���˼Ĵ�����������5�жϣ�int_type_gs_rcv_w[5]����GSDSP��
                                                           ��Чʱ�̣�������Ч
                                                           
                                                           bit4����Ӧw_snd_gs_int_4��
                                                           W��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
                                                           W DSPͨ���˼Ĵ�����������4�жϣ�int_type_gs_rcv_w[4]����GSDSP��
                                                           ��Чʱ�̣�������Ч
                                                           
                                                           bit3����Ӧw_snd_gs_int_3��W��������ָʾ������Ч��
                                                           ���ڴ����ж�����3 ��int_type_gs_rcv_w[3]����GSDSP��GS��ģ�¶�W������ϵͳ����ʱ�����W����������W DSP���ô˱�־Ϊ1�� 
                                                           ��Чʱ�̣�������Ч */
        unsigned int  reserved_1      : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_W_SND_GS_INT_13_UNION;
#define BBPCOMM_W_SND_GS_INT_13_w_snd_gs_int_13_START  (3)
#define BBPCOMM_W_SND_GS_INT_13_w_snd_gs_int_13_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_W_SND_W_INT_13_UNION
 �ṹ˵��  : W_SND_W_INT_13 �Ĵ����ṹ���塣��ַƫ����:0x0730����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      w_snd_w_int_13_reg;
    struct
    {
        unsigned int  reserved_0     : 3;  /* bit[0-2]  : ���� */
        unsigned int  w_snd_w_int_13 : 13; /* bit[3-15] : �߼������㡣����Ч��
                                                          
                                                          bit15~7����Ӧw_snd_w_int_15 ~ 7��
                                                          W DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_w_rcv_w[15:7]����WDSP��
                                                          ��Чʱ�̣�������Ч
                                                          
                                                          bit6����Ӧw_snd_w_int_6��
                                                          WDSPͨ���˼Ĵ�����������6�жϣ�int_type_w_rcv_w[6]����WDSP��
                                                          ��Чʱ�̣�������Ч
                                                          
                                                          bit5����Ӧw_snd_w_int_5��
                                                          W��ģʱ֪ͨWDSP W�������ڵ������Ч��
                                                          W DSPͨ���˼Ĵ�����������5�жϣ�int_type_w_rcv_w[5]����WDSP��
                                                          ��Чʱ�̣�������Ч
                                                          
                                                          bit4����Ӧw_snd_w_int_4��
                                                          W��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
                                                          W DSPͨ���˼Ĵ�����������4�жϣ�int_type_w_rcv_w[4]����WDSP��
                                                          ��Чʱ�̣�������Ч
                                                          
                                                          bit3����Ӧw_snd_w_int_3��W��������ָʾ������Ч��
                                                          ���ڴ����ж�����3 ��int_type_w_rcv_w[3]����WDSP��W��ģ�¶�W������ϵͳ����ʱ�����W����������W DSP���ô˱�־Ϊ1�� 
                                                          ��Чʱ�̣�������Ч */
        unsigned int  reserved_1     : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_W_SND_W_INT_13_UNION;
#define BBPCOMM_W_SND_W_INT_13_w_snd_w_int_13_START  (3)
#define BBPCOMM_W_SND_W_INT_13_w_snd_w_int_13_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_LTE_INTERSYS_MEASURE_TYPE_UNION
 �ṹ˵��  : LTE_INTERSYS_MEASURE_TYPE �Ĵ����ṹ���塣��ַƫ����:0x0734����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      lte_intersys_measure_type_reg;
    struct
    {
        unsigned int  lte_intersys_measure_type : 4;  /* bit[0-3] : ��ϵͳ�������͡�
                                                                    4��b0������LTE��
                                                                    4��b1��������LTE��
                                                                    ����Ԥ��
                                                                    ��Чʱ�̣�������Ч */
        unsigned int  reserved                  : 28; /* bit[4-31]: ���� */
    } reg;
} BBPCOMM_LTE_INTERSYS_MEASURE_TYPE_UNION;
#define BBPCOMM_LTE_INTERSYS_MEASURE_TYPE_lte_intersys_measure_type_START  (0)
#define BBPCOMM_LTE_INTERSYS_MEASURE_TYPE_lte_intersys_measure_type_END    (3)


/*****************************************************************************
 �ṹ��    : BBPCOMM_LTE_MEASURE_REPORT_VALID_UNION
 �ṹ˵��  : LTE_MEASURE_REPORT_VALID �Ĵ����ṹ���塣��ַƫ����:0x0738����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      lte_measure_report_valid_reg;
    struct
    {
        unsigned int  lte_measure_report_valid : 1;  /* bit[0]   : ��Ƶ��������ڵ�ָʾ��W/Gm/Gs����TDS��Ϊ��ģ��֪ͨL DSP �����ĵ�Ƶ�����ڵ��
                                                                   ֻ������̬����Ҫ���ã���Gm��Lʱ����Ҫ���ã�
                                                                   ��ƽ�źţ�����Ч��
                                                                   
                                                                   ��Чʱ�̣�������Ч */
        unsigned int  reserved                 : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_LTE_MEASURE_REPORT_VALID_UNION;
#define BBPCOMM_LTE_MEASURE_REPORT_VALID_lte_measure_report_valid_START  (0)
#define BBPCOMM_LTE_MEASURE_REPORT_VALID_lte_measure_report_valid_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_LTE_RCV_LTE_UNION
 �ṹ˵��  : INT_CLEAR_LTE_RCV_LTE �Ĵ����ṹ���塣��ַƫ����:0x0744����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_lte_rcv_lte_reg;
    struct
    {
        unsigned int  int_clear_lte_rcv_lte : 16; /* bit[0-15] : �߼������㡣
                                                                 �жϱ�־���ָʾ������Ч���������INT_TYPE_LTE_RCV_LTE[15:0]��Ӧbitλ
                                                                 ��Чʱ�̣�������Ч */
        unsigned int  reserved              : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_LTE_RCV_LTE_UNION;
#define BBPCOMM_INT_CLEAR_LTE_RCV_LTE_int_clear_lte_rcv_lte_START  (0)
#define BBPCOMM_INT_CLEAR_LTE_RCV_LTE_int_clear_lte_rcv_lte_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_LTE_RCV_TDS_UNION
 �ṹ˵��  : INT_CLEAR_LTE_RCV_TDS �Ĵ����ṹ���塣��ַƫ����:0x0748����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_lte_rcv_tds_reg;
    struct
    {
        unsigned int  int_clear_lte_rcv_tds : 16; /* bit[0-15] : �߼������㡣
                                                                 �жϱ�־���ָʾ������Ч���������INT_TYPE_LTE_RCV_TDS[15:0]��Ӧbitλ
                                                                 ��Чʱ�̣�������Ч */
        unsigned int  reserved              : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_LTE_RCV_TDS_UNION;
#define BBPCOMM_INT_CLEAR_LTE_RCV_TDS_int_clear_lte_rcv_tds_START  (0)
#define BBPCOMM_INT_CLEAR_LTE_RCV_TDS_int_clear_lte_rcv_tds_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_LTE_RCV_GM_UNION
 �ṹ˵��  : INT_CLEAR_LTE_RCV_GM �Ĵ����ṹ���塣��ַƫ����:0x074C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_lte_rcv_gm_reg;
    struct
    {
        unsigned int  int_clear_lte_rcv_gm : 16; /* bit[0-15] : �߼������㡣
                                                                �жϱ�־���ָʾ������Ч���������INT_TYPE_LTE_RCV_GM[15:0]��Ӧbitλ
                                                                ��Чʱ�̣�������Ч */
        unsigned int  reserved             : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_LTE_RCV_GM_UNION;
#define BBPCOMM_INT_CLEAR_LTE_RCV_GM_int_clear_lte_rcv_gm_START  (0)
#define BBPCOMM_INT_CLEAR_LTE_RCV_GM_int_clear_lte_rcv_gm_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_LTE_RCV_GS_UNION
 �ṹ˵��  : INT_CLEAR_LTE_RCV_GS �Ĵ����ṹ���塣��ַƫ����:0x0750����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_lte_rcv_gs_reg;
    struct
    {
        unsigned int  int_clear_lte_rcv_gs : 16; /* bit[0-15] : �߼������㡣
                                                                �жϱ�־���ָʾ������Ч���������INT_TYPE_LTE_RCV_GS[15:0]��Ӧbitλ
                                                                ��Чʱ�̣�������Ч */
        unsigned int  reserved             : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_LTE_RCV_GS_UNION;
#define BBPCOMM_INT_CLEAR_LTE_RCV_GS_int_clear_lte_rcv_gs_START  (0)
#define BBPCOMM_INT_CLEAR_LTE_RCV_GS_int_clear_lte_rcv_gs_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_LTE_RCV_W_UNION
 �ṹ˵��  : INT_CLEAR_LTE_RCV_W �Ĵ����ṹ���塣��ַƫ����:0x0754����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_lte_rcv_w_reg;
    struct
    {
        unsigned int  int_clear_lte_rcv_w : 16; /* bit[0-15] : �߼������㡣
                                                               �жϱ�־���ָʾ������Ч���������INT_TYPE_LTE_RCV_W[15:0]��Ӧbitλ
                                                               ��Чʱ�̣�������Ч */
        unsigned int  reserved            : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_LTE_RCV_W_UNION;
#define BBPCOMM_INT_CLEAR_LTE_RCV_W_int_clear_lte_rcv_w_START  (0)
#define BBPCOMM_INT_CLEAR_LTE_RCV_W_int_clear_lte_rcv_w_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_LTE_INT012_UNION
 �ṹ˵��  : INT_CLEAR_LTE_INT012 �Ĵ����ṹ���塣��ַƫ����:0x0758����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_lte_int012_reg;
    struct
    {
        unsigned int  int_clear_lte_int012 : 3;  /* bit[0-2] : �߼������㡣
                                                               �жϱ�־���ָʾ������Ч���������INT_TYPE_LTE_INT012[2:0]��Ӧbitλ
                                                               ��Чʱ�̣�������Ч */
        unsigned int  reserved             : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_LTE_INT012_UNION;
#define BBPCOMM_INT_CLEAR_LTE_INT012_int_clear_lte_int012_START  (0)
#define BBPCOMM_INT_CLEAR_LTE_INT012_int_clear_lte_int012_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_LTE_RCV_LTE_UNION
 �ṹ˵��  : INT_MASK_LTE_RCV_LTE �Ĵ����ṹ���塣��ַƫ����:0x075C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_lte_rcv_lte_reg;
    struct
    {
        unsigned int  int_mask_lte_rcv_lte : 16; /* bit[0-15] : �ж����α�־����������INT_TYPE_LTE_RCV_LTE[15:0]��Ӧbit�жϡ�
                                                                0�������ж��ϱ���
                                                                1��ʹ���ж��ϱ���
                                                                ����ʱ�̣���ʼ��
                                                                ��Чʱ�̣�������Ч */
        unsigned int  reserved             : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_LTE_RCV_LTE_UNION;
#define BBPCOMM_INT_MASK_LTE_RCV_LTE_int_mask_lte_rcv_lte_START  (0)
#define BBPCOMM_INT_MASK_LTE_RCV_LTE_int_mask_lte_rcv_lte_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_LTE_RCV_TDS_UNION
 �ṹ˵��  : INT_MASK_LTE_RCV_TDS �Ĵ����ṹ���塣��ַƫ����:0x0760����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_lte_rcv_tds_reg;
    struct
    {
        unsigned int  int_mask_lte_rcv_tds : 16; /* bit[0-15] : �ж����α�־����������INT_TYPE_LTE_RCV_TDS[15:0]��Ӧbit�жϡ�
                                                                0�������ж��ϱ���
                                                                1��ʹ���ж��ϱ���
                                                                ����ʱ�̣���ʼ��
                                                                ��Чʱ�̣�������Ч */
        unsigned int  reserved             : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_LTE_RCV_TDS_UNION;
#define BBPCOMM_INT_MASK_LTE_RCV_TDS_int_mask_lte_rcv_tds_START  (0)
#define BBPCOMM_INT_MASK_LTE_RCV_TDS_int_mask_lte_rcv_tds_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_LTE_RCV_GM_UNION
 �ṹ˵��  : INT_MASK_LTE_RCV_GM �Ĵ����ṹ���塣��ַƫ����:0x0764����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_lte_rcv_gm_reg;
    struct
    {
        unsigned int  int_mask_lte_rcv_gm : 16; /* bit[0-15] : �ж����α�־����������INT_TYPE_LTE_RCV_GM[15:0]��Ӧbit�жϡ�
                                                               0�������ж��ϱ���
                                                               1��ʹ���ж��ϱ���
                                                               ����ʱ�̣���ʼ��
                                                               ��Чʱ�̣�������Ч */
        unsigned int  reserved            : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_LTE_RCV_GM_UNION;
#define BBPCOMM_INT_MASK_LTE_RCV_GM_int_mask_lte_rcv_gm_START  (0)
#define BBPCOMM_INT_MASK_LTE_RCV_GM_int_mask_lte_rcv_gm_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_LTE_RCV_GS_UNION
 �ṹ˵��  : INT_MASK_LTE_RCV_GS �Ĵ����ṹ���塣��ַƫ����:0x0768����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_lte_rcv_gs_reg;
    struct
    {
        unsigned int  int_mask_lte_rcv_gs : 16; /* bit[0-15] : �ж����α�־����������INT_TYPE_LTE_RCV_GS[15:0]��Ӧbit�жϡ�
                                                               0�������ж��ϱ���
                                                               1��ʹ���ж��ϱ���
                                                               ����ʱ�̣���ʼ��
                                                               ��Чʱ�̣�������Ч */
        unsigned int  reserved            : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_LTE_RCV_GS_UNION;
#define BBPCOMM_INT_MASK_LTE_RCV_GS_int_mask_lte_rcv_gs_START  (0)
#define BBPCOMM_INT_MASK_LTE_RCV_GS_int_mask_lte_rcv_gs_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_LTE_RCV_W_UNION
 �ṹ˵��  : INT_MASK_LTE_RCV_W �Ĵ����ṹ���塣��ַƫ����:0x076C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_lte_rcv_w_reg;
    struct
    {
        unsigned int  int_mask_lte_rcv_w : 16; /* bit[0-15] : �ж����α�־����������INT_TYPE_LTE_RCV_W[15:0]��Ӧbit�жϡ�
                                                              0�������ж��ϱ���
                                                              1��ʹ���ж��ϱ���
                                                              ����ʱ�̣���ʼ��
                                                              ��Чʱ�̣�������Ч */
        unsigned int  reserved           : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_LTE_RCV_W_UNION;
#define BBPCOMM_INT_MASK_LTE_RCV_W_int_mask_lte_rcv_w_START  (0)
#define BBPCOMM_INT_MASK_LTE_RCV_W_int_mask_lte_rcv_w_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_LTE_INT012_UNION
 �ṹ˵��  : INT_MASK_LTE_INT012 �Ĵ����ṹ���塣��ַƫ����:0x0770����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_lte_int012_reg;
    struct
    {
        unsigned int  int_mask_lte_int012 : 3;  /* bit[0-2] : �ж����α�־����������INT_TYPE_LTE_INT012[2:0]��Ӧbit�жϡ�
                                                              0�������ж��ϱ���
                                                              1��ʹ���ж��ϱ���
                                                              ����ʱ�̣���ʼ��
                                                              ��Чʱ�̣�������Ч */
        unsigned int  reserved            : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_LTE_INT012_UNION;
#define BBPCOMM_INT_MASK_LTE_INT012_int_mask_lte_int012_START  (0)
#define BBPCOMM_INT_MASK_LTE_INT012_int_mask_lte_int012_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_LTE_RCV_W_UNION
 �ṹ˵��  : INT_TYPE_LTE_RCV_W �Ĵ����ṹ���塣��ַƫ����:0x0774����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_lte_rcv_w_reg;
    struct
    {
        unsigned int  o_int_type_lte_rcv_w : 16; /* bit[0-15] : �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
                                                                [0]: �ж�����0�� W����ģ����ǰ֪ͨLTE��ϵͳ���������жϡ�
                                                                [1]: �ж�����1�� W����ģ����GAP�жϣ�֪ͨLTE������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
                                                                [2]: �ж�����2�� W����ģ����GAP�жϡ�
                                                                [3]: �ж�����3��W����ģ�����������жϡ�
                                                                [4]: �ж�����4��W����ģ��ǿ��LTE�˳���ϵͳ�����жϡ�
                                                                [5]: �ж�����5��W����ģ��֪ͨLTE�ϱ����β��������
                                                                [6]: ������
                                                                [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
                                                                �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x076C��int_mask_lte_rcv_w���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved             : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_LTE_RCV_W_UNION;
#define BBPCOMM_INT_TYPE_LTE_RCV_W_o_int_type_lte_rcv_w_START  (0)
#define BBPCOMM_INT_TYPE_LTE_RCV_W_o_int_type_lte_rcv_w_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_LTE_RCV_TDS_UNION
 �ṹ˵��  : INT_TYPE_LTE_RCV_TDS �Ĵ����ṹ���塣��ַƫ����:0x0778����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_lte_rcv_tds_reg;
    struct
    {
        unsigned int  o_int_type_lte_rcv_tds : 16; /* bit[0-15] : �ж�״̬��־0��1��2ֻ�е�TDS������ģʱ���ܲ�����
                                                                  [0]: �ж�����0�� TDS����ģ����ǰ֪ͨLTE��ϵͳ���������жϡ�
                                                                  [1]: �ж�����1�� TDS����ģ����GAP�жϣ�֪ͨLTE������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
                                                                  [2]: �ж�����2�� TDS����ģ����GAP�жϡ�
                                                                  [3]: �ж�����3��TDS����ģ�����������жϡ�
                                                                  [4]: �ж�����4��TDS����ģ��ǿ��LTE�˳���ϵͳ�����жϡ�
                                                                  [5]: �ж�����5��TDS����ģ��֪ͨLTE�ϱ����β��������
                                                                  [6]: �ж�����6��������
                                                                  [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
                                                                  �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x0760��int_mask_lte_rcv_tds���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved               : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_LTE_RCV_TDS_UNION;
#define BBPCOMM_INT_TYPE_LTE_RCV_TDS_o_int_type_lte_rcv_tds_START  (0)
#define BBPCOMM_INT_TYPE_LTE_RCV_TDS_o_int_type_lte_rcv_tds_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_LTE_RCV_GM_UNION
 �ṹ˵��  : INT_TYPE_LTE_RCV_GM �Ĵ����ṹ���塣��ַƫ����:0x077C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_lte_rcv_gm_reg;
    struct
    {
        unsigned int  o_int_type_lte_rcv_gm : 16; /* bit[0-15] : �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
                                                                 [0]: �ж�����0��GM����ģ����ǰ֪ͨLTE��ϵͳ���������жϡ�
                                                                 [1]: �ж�����1��GM����ģ����GAP�жϣ�֪ͨLTE������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
                                                                 [2]: �ж�����2��GM����ģ����GAP�жϡ�
                                                                 [3]: �ж�����3��GM����ģ�����������жϡ�
                                                                 [4]: �ж�����4��GM����ģ��ǿ��LTE�˳���ϵͳ�����жϡ�
                                                                 [5]: �ж�����5��GM����ģ��֪ͨLTE�ϱ����β��������
                                                                 [6]: �ж�����6��������
                                                                 [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
                                                                 �ж�״̬��־0��1��2ֻ�е�GM������ģʱ���ܲ�����
                                                                 �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x0764��int_mask_lte_rcv_gm���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved              : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_LTE_RCV_GM_UNION;
#define BBPCOMM_INT_TYPE_LTE_RCV_GM_o_int_type_lte_rcv_gm_START  (0)
#define BBPCOMM_INT_TYPE_LTE_RCV_GM_o_int_type_lte_rcv_gm_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_LTE_RCV_GS_UNION
 �ṹ˵��  : INT_TYPE_LTE_RCV_GS �Ĵ����ṹ���塣��ַƫ����:0x0780����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_lte_rcv_gs_reg;
    struct
    {
        unsigned int  o_int_type_lte_rcv_gs : 16; /* bit[0-15] : [0]: �ж�����0��GS����ģ����ǰ֪ͨLTE��ϵͳ���������жϡ�
                                                                 [1]: �ж�����1��GS����ģ����GAP�жϣ�֪ͨLTE������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
                                                                 [2]: �ж�����2��GS����ģ����GAP�жϡ�
                                                                 [3]: �ж�����3��GS����ģ�����������жϡ�
                                                                 [4]: �ж�����4��GS����ģ��ǿ��LTE�˳���ϵͳ�����жϡ�
                                                                 [5]: �ж�����5��GS����ģ��֪ͨLTE�ϱ����β��������
                                                                 [6]: �ж�����6��������
                                                                 [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
                                                                 �ж�״̬��־0��1��2ֻ�е�TDS������ģʱ���ܲ�����
                                                                 �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x0768��int_mask_lte_rcv_gs���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved              : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_LTE_RCV_GS_UNION;
#define BBPCOMM_INT_TYPE_LTE_RCV_GS_o_int_type_lte_rcv_gs_START  (0)
#define BBPCOMM_INT_TYPE_LTE_RCV_GS_o_int_type_lte_rcv_gs_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_LTE_RCV_LTE_UNION
 �ṹ˵��  : INT_TYPE_LTE_RCV_LTE �Ĵ����ṹ���塣��ַƫ����:0x0784����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_lte_rcv_lte_reg;
    struct
    {
        unsigned int  o_int_type_lte_rcv_lte : 16; /* bit[0-15] : �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
                                                                  [0]: �ж�����0��LTE����ģ����ǰ֪ͨLTE��Ƶ���������жϡ�
                                                                  [1]: �ж�����1��LTE����ģ����GAP�жϣ�֪ͨLTE������Ƶ������Ƶͨ�����ã������л��Ȳ�����
                                                                  [2]: �ж�����2��LTE����ģ����GAP�жϡ�
                                                                  [3]: �ж�����3��LTE����ģ������Ƶ�����������жϡ�
                                                                  [4]: �ж�����4��LTE����ģ��ǿ��LTE�˳���Ƶ�����жϡ�
                                                                  [5]: �ж�����5��LTE����ģ��֪ͨLTE�ϱ����β��������
                                                                  [6]: �ж�����6��������
                                                                  [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
                                                                  �ж�״̬��־0��1��2ֻ�е�LTE������ģʱ���ܲ�����
                                                                  �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x075C��int_mask_lte_rcv_lte���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved               : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_LTE_RCV_LTE_UNION;
#define BBPCOMM_INT_TYPE_LTE_RCV_LTE_o_int_type_lte_rcv_lte_START  (0)
#define BBPCOMM_INT_TYPE_LTE_RCV_LTE_o_int_type_lte_rcv_lte_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_LTE_INT012_UNION
 �ṹ˵��  : INT_TYPE_LTE_INT012 �Ĵ����ṹ���塣��ַƫ����:0x0788����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_lte_int012_reg;
    struct
    {
        unsigned int  o_int_type_lte_int012 : 3;  /* bit[0-2] : ������ģ����int0��1��2���ϱ���(������Ƶ����ϵͳ����)��������Ч��
                                                                [0]: L��ģʱ��CTU����֪ͨLDSP����int0�жϡ�
                                                                [1]: L��ģʱ��CTU����֪ͨLDSP����int1�жϡ�
                                                                [2]: L��ģʱ��CTU����֪ͨLDSP����int2�жϡ�
                                                                �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x0770��int_mask_lte_int012���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved              : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_LTE_INT012_UNION;
#define BBPCOMM_INT_TYPE_LTE_INT012_o_int_type_lte_int012_START  (0)
#define BBPCOMM_INT_TYPE_LTE_INT012_o_int_type_lte_int012_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_LTE_SND_LTE_INT_13_UNION
 �ṹ˵��  : LTE_SND_LTE_INT_13 �Ĵ����ṹ���塣��ַƫ����:0x078C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      lte_snd_lte_int_13_reg;
    struct
    {
        unsigned int  reserved_0         : 3;  /* bit[0-2]  : ���� */
        unsigned int  lte_snd_lte_int_13 : 13; /* bit[3-15] : �߼������㡣����Ч��
                                                              
                                                              bit15~7����Ӧlte_snd_lte_int_15 ~ 7��
                                                              L DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_lte_rcv_lte[15:7]����LDSP��
                                                              ��Чʱ�̣�������Ч
                                                              
                                                              bit6����Ӧlte_snd_lte_int_6��
                                                              LDSPͨ���˼Ĵ�����������6�жϣ�int_type_lte_rcv_lte[6]����LDSP��
                                                              ��Чʱ�̣�������Ч
                                                              
                                                              bit5����Ӧlte_snd_lte_int_5��
                                                              L��ģʱ֪ͨLDSP L�������ڵ������Ч��
                                                              L DSPͨ���˼Ĵ�����������5�жϣ�int_type_lte_rcv_lte[5]����LDSP��
                                                              ��Чʱ�̣�������Ч
                                                              
                                                              bit4����Ӧlte_snd_lte_int_4��
                                                              L��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
                                                              L DSPͨ���˼Ĵ�����������4�жϣ�int_type_lte_rcv_lte[4]����LDSP��
                                                              ��Чʱ�̣�������Ч
                                                              
                                                              bit3����Ӧlte_snd_lte_int_3��L��������ָʾ������Ч��
                                                              ���ڴ����ж�����3 ��int_type_lte_rcv_lte[3]����LDSP��L��ģ�¶�L������ϵͳ����ʱ�����L����������L DSP���ô˱�־Ϊ1�� 
                                                              ��Чʱ�̣�������Ч */
        unsigned int  reserved_1         : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_LTE_SND_LTE_INT_13_UNION;
#define BBPCOMM_LTE_SND_LTE_INT_13_lte_snd_lte_int_13_START  (3)
#define BBPCOMM_LTE_SND_LTE_INT_13_lte_snd_lte_int_13_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_LTE_SND_TDS_INT_13_UNION
 �ṹ˵��  : LTE_SND_TDS_INT_13 �Ĵ����ṹ���塣��ַƫ����:0x0790����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      lte_snd_tds_int_13_reg;
    struct
    {
        unsigned int  reserved_0         : 3;  /* bit[0-2]  : ���� */
        unsigned int  lte_snd_tds_int_13 : 13; /* bit[3-15] : �߼������㡣����Ч��
                                                              
                                                              bit15~7����Ӧlte_snd_tds_int_15 ~ 7��
                                                              L DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_tds_rcv_lte[15:7]����TDSDSP��
                                                              ��Чʱ�̣�������Ч
                                                              
                                                              bit6����Ӧlte_snd_tds_int_6��
                                                              LDSPͨ���˼Ĵ�����������6�жϣ�int_type_tds_rcv_lte[6]����TDSDSP��
                                                              ��Чʱ�̣�������Ч
                                                              
                                                              bit5����Ӧlte_snd_tds_int_5��
                                                              L��ģʱ֪ͨTDSDSP TDS�������ڵ������Ч��
                                                              L DSPͨ���˼Ĵ�����������5�жϣ�int_type_tds_rcv_lte[5]����TDSDSP��
                                                              ��Чʱ�̣�������Ч
                                                              
                                                              bit4����Ӧlte_snd_tds_int_4��
                                                              L��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
                                                              L DSPͨ���˼Ĵ�����������4�жϣ�int_type_tds_rcv_lte[4]����TDSDSP��
                                                              ��Чʱ�̣�������Ч
                                                              
                                                              bit3����Ӧlte_snd_tds_int_3��L��������ָʾ������Ч��
                                                              ���ڴ����ж�����3 ��int_type_tds_rcv_lte[3]����TDSDSP��TDS��ģ�¶�L������ϵͳ����ʱ�����L����������L DSP���ô˱�־Ϊ1�� 
                                                              ��Чʱ�̣�������Ч */
        unsigned int  reserved_1         : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_LTE_SND_TDS_INT_13_UNION;
#define BBPCOMM_LTE_SND_TDS_INT_13_lte_snd_tds_int_13_START  (3)
#define BBPCOMM_LTE_SND_TDS_INT_13_lte_snd_tds_int_13_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_LTE_SND_GM_INT_13_UNION
 �ṹ˵��  : LTE_SND_GM_INT_13 �Ĵ����ṹ���塣��ַƫ����:0x0794����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      lte_snd_gm_int_13_reg;
    struct
    {
        unsigned int  reserved_0        : 3;  /* bit[0-2]  : ���� */
        unsigned int  lte_snd_gm_int_13 : 13; /* bit[3-15] : �߼������㡣����Ч��
                                                             
                                                             bit15~7����Ӧlte_snd_gm_int_15 ~ 7��
                                                             L DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_gm_rcv_lte[15:7]����GMDSP��
                                                             ��Чʱ�̣�������Ч
                                                             
                                                             bit6����Ӧlte_snd_gm_int_6��
                                                             LDSPͨ���˼Ĵ�����������6�жϣ�iint_type_gm_rcv_lte[6]����GMDSP��
                                                             ��Чʱ�̣�������Ч
                                                             
                                                             bit5����Ӧlte_snd_gm_int_5��
                                                             L��ģʱ֪ͨGMDSP GM�������ڵ������Ч��
                                                             L DSPͨ���˼Ĵ�����������5�жϣ�int_type_gm_rcv_lte[5]����GMDSP��
                                                             ��Чʱ�̣�������Ч
                                                             
                                                             bit4����Ӧlte_snd_gm_int_4��
                                                             L��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
                                                             L DSPͨ���˼Ĵ�����������4�жϣ�int_type_gm_rcv_lte[4]����GMDSP��
                                                             ��Чʱ�̣�������Ч
                                                             
                                                             bit3����Ӧlte_snd_gm_int_3��L��������ָʾ������Ч��
                                                             ���ڴ����ж�����3 ��int_type_gm_rcv_lte[3]����GMDSP��GM��ģ�¶�L������ϵͳ����ʱ�����L����������L DSP���ô˱�־Ϊ1�� 
                                                             ��Чʱ�̣�������Ч */
        unsigned int  reserved_1        : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_LTE_SND_GM_INT_13_UNION;
#define BBPCOMM_LTE_SND_GM_INT_13_lte_snd_gm_int_13_START  (3)
#define BBPCOMM_LTE_SND_GM_INT_13_lte_snd_gm_int_13_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_LTE_SND_GS_INT_13_UNION
 �ṹ˵��  : LTE_SND_GS_INT_13 �Ĵ����ṹ���塣��ַƫ����:0x0798����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      lte_snd_gs_int_13_reg;
    struct
    {
        unsigned int  reserved_0        : 3;  /* bit[0-2]  : ���� */
        unsigned int  lte_snd_gs_int_13 : 13; /* bit[3-15] : �߼������㡣����Ч��
                                                             
                                                             bit15~7����Ӧlte_snd_gs_int_15 ~ 7��
                                                             L DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_gs_rcv_lte[15:7]����GSDSP��
                                                             ��Чʱ�̣�������Ч
                                                             
                                                             bit6����Ӧlte_snd_gs_int_6��
                                                             LDSPͨ���˼Ĵ�����������6�жϣ�int_type_gs_rcv_lte[6]����GSDSP��
                                                             ��Чʱ�̣�������Ч
                                                             
                                                             bit5����Ӧlte_snd_gs_int_5��
                                                             L��ģʱ֪ͨGSDSP GS�������ڵ������Ч��
                                                             L DSPͨ���˼Ĵ�����������5�жϣ�int_type_gs_rcv_lte[5]����GSDSP��
                                                             ��Чʱ�̣�������Ч
                                                             
                                                             bit4����Ӧlte_snd_gs_int_4��
                                                             L��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
                                                             L DSPͨ���˼Ĵ�����������4�жϣ�int_type_gs_rcv_lte[4]����GSDSP��
                                                             ��Чʱ�̣�������Ч
                                                             
                                                             bit3����Ӧlte_snd_gs_int_3��L��������ָʾ������Ч��
                                                             ���ڴ����ж�����3 ��int_type_gs_rcv_lte[3]����GSDSP��GS��ģ�¶�L������ϵͳ����ʱ�����L����������L DSP���ô˱�־Ϊ1�� 
                                                             ��Чʱ�̣�������Ч */
        unsigned int  reserved_1        : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_LTE_SND_GS_INT_13_UNION;
#define BBPCOMM_LTE_SND_GS_INT_13_lte_snd_gs_int_13_START  (3)
#define BBPCOMM_LTE_SND_GS_INT_13_lte_snd_gs_int_13_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_LTE_SND_W_INT_13_UNION
 �ṹ˵��  : LTE_SND_W_INT_13 �Ĵ����ṹ���塣��ַƫ����:0x079C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      lte_snd_w_int_13_reg;
    struct
    {
        unsigned int  reserved_0       : 3;  /* bit[0-2]  : ���� */
        unsigned int  lte_snd_w_int_13 : 13; /* bit[3-15] : �߼������㡣����Ч��
                                                            
                                                            bit15~7����Ӧlte_snd_w_int_15 ~ 7��
                                                            L DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_w_rcv_lte[15:7]����WDSP��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit6����Ӧlte_snd_w_int_6��
                                                            LDSPͨ���˼Ĵ�����������6�жϣ�int_type_w_rcv_lte[6]����WDSP��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit5����Ӧlte_snd_w_int_5��
                                                            L��ģʱ֪ͨWDSP W�������ڵ������Ч��
                                                            L DSPͨ���˼Ĵ�����������5�жϣ�int_type_w_rcv_lte[5]����WDSP��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit4����Ӧlte_snd_w_int_4��
                                                            L��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
                                                            L DSPͨ���˼Ĵ�����������4�жϣ�int_type_w_rcv_lte[4]����WDSP��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit3����Ӧlte_snd_w_int_3��L��������ָʾ������Ч��
                                                            ���ڴ����ж�����3 ��int_type_w_rcv_lte[3]����WDSP��W��ģ�¶�L������ϵͳ����ʱ�����L����������L DSP���ô˱�־Ϊ1�� 
                                                            ��Чʱ�̣�������Ч */
        unsigned int  reserved_1       : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_LTE_SND_W_INT_13_UNION;
#define BBPCOMM_LTE_SND_W_INT_13_lte_snd_w_int_13_START  (3)
#define BBPCOMM_LTE_SND_W_INT_13_lte_snd_w_int_13_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TDS_INTERSYS_MEASURE_TYPE_UNION
 �ṹ˵��  : TDS_INTERSYS_MEASURE_TYPE �Ĵ����ṹ���塣��ַƫ����:0x07A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      tds_intersys_measure_type_reg;
    struct
    {
        unsigned int  tds_intersys_measure_type : 4;  /* bit[0-3] : ��ϵͳ�������� ��
                                                                    4��b0�� ����TDS
                                                                    4��b1�� ������TDS
                                                                    ����Ԥ��
                                                                    
                                                                    ��Чʱ�̣�������Ч */
        unsigned int  reserved                  : 28; /* bit[4-31]: ���� */
    } reg;
} BBPCOMM_TDS_INTERSYS_MEASURE_TYPE_UNION;
#define BBPCOMM_TDS_INTERSYS_MEASURE_TYPE_tds_intersys_measure_type_START  (0)
#define BBPCOMM_TDS_INTERSYS_MEASURE_TYPE_tds_intersys_measure_type_END    (3)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TDS_MEASURE_REPORT_VALID_UNION
 �ṹ˵��  : TDS_MEASURE_REPORT_VALID �Ĵ����ṹ���塣��ַƫ����:0x07A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      tds_measure_report_valid_reg;
    struct
    {
        unsigned int  tds_measure_report_valid : 1;  /* bit[0]   : ��Ƶ��������ڵ�ָʾ��U/Gm/Gs����L��Ϊ��ģ��֪ͨT DSP W�����ĵ�Ƶ�����ڵ��
                                                                   ֻ������̬����Ҫ���ã���G��TDSʱ����Ҫ���ã�
                                                                   ��ƽ�źţ�����Ч��
                                                                   
                                                                   ��Чʱ�̣�������Ч */
        unsigned int  reserved                 : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_TDS_MEASURE_REPORT_VALID_UNION;
#define BBPCOMM_TDS_MEASURE_REPORT_VALID_tds_measure_report_valid_START  (0)
#define BBPCOMM_TDS_MEASURE_REPORT_VALID_tds_measure_report_valid_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_TDS_RCV_LTE_UNION
 �ṹ˵��  : INT_CLEAR_TDS_RCV_LTE �Ĵ����ṹ���塣��ַƫ����:0x07B0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_tds_rcv_lte_reg;
    struct
    {
        unsigned int  int_clear_tds_rcv_lte : 16; /* bit[0-15] : �߼������㡣
                                                                 �жϱ�־���ָʾ������Ч���������INT_TYPE_TDS_RCV_LTE[15:0]��Ӧbitλ
                                                                 ��Чʱ�̣�������Ч */
        unsigned int  reserved              : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_TDS_RCV_LTE_UNION;
#define BBPCOMM_INT_CLEAR_TDS_RCV_LTE_int_clear_tds_rcv_lte_START  (0)
#define BBPCOMM_INT_CLEAR_TDS_RCV_LTE_int_clear_tds_rcv_lte_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_TDS_RCV_TDS_UNION
 �ṹ˵��  : INT_CLEAR_TDS_RCV_TDS �Ĵ����ṹ���塣��ַƫ����:0x07B4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_tds_rcv_tds_reg;
    struct
    {
        unsigned int  int_clear_tds_rcv_tds : 16; /* bit[0-15] : �߼������㡣
                                                                 �жϱ�־���ָʾ������Ч���������INT_TYPE_TDS_RCV_TDS[15:0]��Ӧbitλ
                                                                 ��Чʱ�̣�������Ч */
        unsigned int  reserved              : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_TDS_RCV_TDS_UNION;
#define BBPCOMM_INT_CLEAR_TDS_RCV_TDS_int_clear_tds_rcv_tds_START  (0)
#define BBPCOMM_INT_CLEAR_TDS_RCV_TDS_int_clear_tds_rcv_tds_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_TDS_RCV_GM_UNION
 �ṹ˵��  : INT_CLEAR_TDS_RCV_GM �Ĵ����ṹ���塣��ַƫ����:0x07B8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_tds_rcv_gm_reg;
    struct
    {
        unsigned int  int_clear_tds_rcv_gm : 16; /* bit[0-15] : �߼������㡣
                                                                �жϱ�־���ָʾ������Ч���������INT_TYPE_TDS_RCV_GM[15:0]��Ӧbitλ
                                                                ��Чʱ�̣�������Ч */
        unsigned int  reserved             : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_TDS_RCV_GM_UNION;
#define BBPCOMM_INT_CLEAR_TDS_RCV_GM_int_clear_tds_rcv_gm_START  (0)
#define BBPCOMM_INT_CLEAR_TDS_RCV_GM_int_clear_tds_rcv_gm_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_TDS_RCV_GS_UNION
 �ṹ˵��  : INT_CLEAR_TDS_RCV_GS �Ĵ����ṹ���塣��ַƫ����:0x07BC����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_tds_rcv_gs_reg;
    struct
    {
        unsigned int  int_clear_tds_rcv_gs : 16; /* bit[0-15] : �߼������㡣
                                                                �жϱ�־���ָʾ������Ч���������INT_TYPE_TDS_RCV_GS[15:0]��Ӧbitλ
                                                                ��Чʱ�̣�������Ч */
        unsigned int  reserved             : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_TDS_RCV_GS_UNION;
#define BBPCOMM_INT_CLEAR_TDS_RCV_GS_int_clear_tds_rcv_gs_START  (0)
#define BBPCOMM_INT_CLEAR_TDS_RCV_GS_int_clear_tds_rcv_gs_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_TDS_RCV_W_UNION
 �ṹ˵��  : INT_CLEAR_TDS_RCV_W �Ĵ����ṹ���塣��ַƫ����:0x07C0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_tds_rcv_w_reg;
    struct
    {
        unsigned int  int_clear_tds_rcv_w : 16; /* bit[0-15] : �߼������㡣
                                                               �жϱ�־���ָʾ������Ч���������INT_TYPE_TDS_RCV_W[15:0]��Ӧbitλ
                                                               ��Чʱ�̣�������Ч */
        unsigned int  reserved            : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_TDS_RCV_W_UNION;
#define BBPCOMM_INT_CLEAR_TDS_RCV_W_int_clear_tds_rcv_w_START  (0)
#define BBPCOMM_INT_CLEAR_TDS_RCV_W_int_clear_tds_rcv_w_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_TDS_INT012_UNION
 �ṹ˵��  : INT_CLEAR_TDS_INT012 �Ĵ����ṹ���塣��ַƫ����:0x07C4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_tds_int012_reg;
    struct
    {
        unsigned int  int_clear_tds_int012 : 3;  /* bit[0-2] : �߼������㡣
                                                               �жϱ�־���ָʾ������Ч���������INT_TYPE_TDS_INT012[2:0]��Ӧbitλ
                                                               ��Чʱ�̣�������Ч */
        unsigned int  reserved             : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_TDS_INT012_UNION;
#define BBPCOMM_INT_CLEAR_TDS_INT012_int_clear_tds_int012_START  (0)
#define BBPCOMM_INT_CLEAR_TDS_INT012_int_clear_tds_int012_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_TDS_RCV_LTE_UNION
 �ṹ˵��  : INT_MASK_TDS_RCV_LTE �Ĵ����ṹ���塣��ַƫ����:0x07C8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_tds_rcv_lte_reg;
    struct
    {
        unsigned int  int_mask_tds_rcv_lte : 16; /* bit[0-15] : �ж����α�־����������INT_TYPE_TDS_RCV_LTE[15:0]��Ӧbit�жϡ�
                                                                0�������ж��ϱ���
                                                                1��ʹ���ж��ϱ���
                                                                ����ʱ�̣���ʼ��
                                                                ��Чʱ�̣�������Ч */
        unsigned int  reserved             : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_TDS_RCV_LTE_UNION;
#define BBPCOMM_INT_MASK_TDS_RCV_LTE_int_mask_tds_rcv_lte_START  (0)
#define BBPCOMM_INT_MASK_TDS_RCV_LTE_int_mask_tds_rcv_lte_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_TDS_RCV_TDS_UNION
 �ṹ˵��  : INT_MASK_TDS_RCV_TDS �Ĵ����ṹ���塣��ַƫ����:0x07CC����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_tds_rcv_tds_reg;
    struct
    {
        unsigned int  int_mask_tds_rcv_tds : 16; /* bit[0-15] : �ж����α�־����������INT_TYPE_TDS_RCV_TDS[15:0]��Ӧbit�жϡ�
                                                                0�������ж��ϱ���
                                                                1��ʹ���ж��ϱ���
                                                                ����ʱ�̣���ʼ��
                                                                ��Чʱ�̣�������Ч */
        unsigned int  reserved             : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_TDS_RCV_TDS_UNION;
#define BBPCOMM_INT_MASK_TDS_RCV_TDS_int_mask_tds_rcv_tds_START  (0)
#define BBPCOMM_INT_MASK_TDS_RCV_TDS_int_mask_tds_rcv_tds_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_TDS_RCV_GM_UNION
 �ṹ˵��  : INT_MASK_TDS_RCV_GM �Ĵ����ṹ���塣��ַƫ����:0x07D0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_tds_rcv_gm_reg;
    struct
    {
        unsigned int  int_mask_tds_rcv_gm : 16; /* bit[0-15] : �ж����α�־����������INT_TYPE_TDS_RCV_GM[15:0]��Ӧbit�жϡ�
                                                               0�������ж��ϱ���
                                                               1��ʹ���ж��ϱ���
                                                               ����ʱ�̣���ʼ��
                                                               ��Чʱ�̣�������Ч */
        unsigned int  reserved            : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_TDS_RCV_GM_UNION;
#define BBPCOMM_INT_MASK_TDS_RCV_GM_int_mask_tds_rcv_gm_START  (0)
#define BBPCOMM_INT_MASK_TDS_RCV_GM_int_mask_tds_rcv_gm_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_TDS_RCV_GS_UNION
 �ṹ˵��  : INT_MASK_TDS_RCV_GS �Ĵ����ṹ���塣��ַƫ����:0x07D4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_tds_rcv_gs_reg;
    struct
    {
        unsigned int  int_mask_tds_rcv_gs : 16; /* bit[0-15] : �ж����α�־����������INT_TYPE_TDS_RCV_GS[15:0]��Ӧbit�жϡ�
                                                               0�������ж��ϱ���
                                                               1��ʹ���ж��ϱ���
                                                               ����ʱ�̣���ʼ��
                                                               ��Чʱ�̣�������Ч */
        unsigned int  reserved            : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_TDS_RCV_GS_UNION;
#define BBPCOMM_INT_MASK_TDS_RCV_GS_int_mask_tds_rcv_gs_START  (0)
#define BBPCOMM_INT_MASK_TDS_RCV_GS_int_mask_tds_rcv_gs_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_TDS_RCV_W_UNION
 �ṹ˵��  : INT_MASK_TDS_RCV_W �Ĵ����ṹ���塣��ַƫ����:0x07D8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_tds_rcv_w_reg;
    struct
    {
        unsigned int  int_mask_tds_rcv_w : 16; /* bit[0-15] : �ж����α�־����������INT_TYPE_TDS_RCV_W[15:0]��Ӧbit�жϡ�
                                                              0�������ж��ϱ���
                                                              1��ʹ���ж��ϱ���
                                                              ����ʱ�̣���ʼ��
                                                              ��Чʱ�̣�������Ч */
        unsigned int  reserved           : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_TDS_RCV_W_UNION;
#define BBPCOMM_INT_MASK_TDS_RCV_W_int_mask_tds_rcv_w_START  (0)
#define BBPCOMM_INT_MASK_TDS_RCV_W_int_mask_tds_rcv_w_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_TDS_INT012_UNION
 �ṹ˵��  : INT_MASK_TDS_INT012 �Ĵ����ṹ���塣��ַƫ����:0x07DC����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_tds_int012_reg;
    struct
    {
        unsigned int  int_mask_tds_int012 : 3;  /* bit[0-2] : �ж����α�־����������INT_TYPE_TDS_INT012[2:0]��Ӧbit�жϡ�
                                                              0�������ж��ϱ���
                                                              1��ʹ���ж��ϱ���
                                                              ����ʱ�̣���ʼ��
                                                              ��Чʱ�̣�������Ч */
        unsigned int  reserved            : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_TDS_INT012_UNION;
#define BBPCOMM_INT_MASK_TDS_INT012_int_mask_tds_int012_START  (0)
#define BBPCOMM_INT_MASK_TDS_INT012_int_mask_tds_int012_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_TDS_RCV_LTE_UNION
 �ṹ˵��  : INT_TYPE_TDS_RCV_LTE �Ĵ����ṹ���塣��ַƫ����:0x07E0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_tds_rcv_lte_reg;
    struct
    {
        unsigned int  o_int_type_tds_rcv_lte : 16; /* bit[0-15] : �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
                                                                  [0]: �ж�����0�� LTE����ģ����ǰ֪ͨTDS��ϵͳ���������жϡ�
                                                                  [1]: �ж�����1�� LTE����ģ����GAP�жϣ�֪ͨTDS������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
                                                                  [2]: �ж�����2�� LTE����ģ����GAP�жϡ�
                                                                  [3]: �ж�����3��LTE����ģ�����������жϡ�
                                                                  [4]: �ж�����4��LTE����ģ��ǿ��TDS�˳���ϵͳ�����жϡ�
                                                                  [5]: �ж�����5��LTE����ģ��֪ͨTDS�ϱ����β��������
                                                                  [6]: ������
                                                                  [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
                                                                  �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x07C8��int_mask_tds_rcv_lte���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved               : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_TDS_RCV_LTE_UNION;
#define BBPCOMM_INT_TYPE_TDS_RCV_LTE_o_int_type_tds_rcv_lte_START  (0)
#define BBPCOMM_INT_TYPE_TDS_RCV_LTE_o_int_type_tds_rcv_lte_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_TDS_RCV_W_UNION
 �ṹ˵��  : INT_TYPE_TDS_RCV_W �Ĵ����ṹ���塣��ַƫ����:0x07E4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_tds_rcv_w_reg;
    struct
    {
        unsigned int  o_int_type_tds_rcv_w : 16; /* bit[0-15] : �ж�״̬��־0��1��2ֻ�е�TDS������ģʱ���ܲ�����
                                                                
                                                                [0]: �ж�����0�� TDS����ģ����ǰ֪ͨTDS��ϵͳ���������жϡ�
                                                                [1]: �ж�����1�� TDS����ģ����GAP�жϣ�֪ͨTDS������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
                                                                [2]: �ж�����2�� TDS����ģ����GAP�жϡ�
                                                                [3]: �ж�����3��TDS����ģ�����������жϡ�
                                                                [4]: �ж�����4��TDS����ģ��ǿ��TDS�˳���ϵͳ�����жϡ�
                                                                [5]: �ж�����5��TDS����ģ��֪ͨTDS�ϱ����β��������
                                                                [6]: �ж�����6��������
                                                                [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
                                                                �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x07D8��int_mask_tds_rcv_w���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved             : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_TDS_RCV_W_UNION;
#define BBPCOMM_INT_TYPE_TDS_RCV_W_o_int_type_tds_rcv_w_START  (0)
#define BBPCOMM_INT_TYPE_TDS_RCV_W_o_int_type_tds_rcv_w_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_TDS_RCV_GM_UNION
 �ṹ˵��  : INT_TYPE_TDS_RCV_GM �Ĵ����ṹ���塣��ַƫ����:0x07E8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_tds_rcv_gm_reg;
    struct
    {
        unsigned int  o_int_type_tds_rcv_gm : 16; /* bit[0-15] : �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
                                                                 [0]: �ж�����0��GM����ģ����ǰ֪ͨTDS��ϵͳ���������жϡ�
                                                                 [1]: �ж�����1��GM����ģ����GAP�жϣ�֪ͨTDS������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
                                                                 [2]: �ж�����2��GM����ģ����GAP�жϡ�
                                                                 [3]: �ж�����3��GM����ģ�����������жϡ�
                                                                 [4]: �ж�����4��GM����ģ��ǿ��TDS�˳���ϵͳ�����жϡ�
                                                                 [5]: �ж�����5��GM����ģ��֪ͨTDS�ϱ����β��������
                                                                 [6]: �ж�����6��������
                                                                 [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
                                                                 �ж�״̬��־0��1��2ֻ�е�GM������ģʱ���ܲ�����
                                                                 �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x07D0��int_mask_tds_rcv_gm���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved              : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_TDS_RCV_GM_UNION;
#define BBPCOMM_INT_TYPE_TDS_RCV_GM_o_int_type_tds_rcv_gm_START  (0)
#define BBPCOMM_INT_TYPE_TDS_RCV_GM_o_int_type_tds_rcv_gm_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_TDS_RCV_GS_UNION
 �ṹ˵��  : INT_TYPE_TDS_RCV_GS �Ĵ����ṹ���塣��ַƫ����:0x07EC����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_tds_rcv_gs_reg;
    struct
    {
        unsigned int  o_int_type_tds_rcv_gs : 16; /* bit[0-15] : [0]: �ж�����0��GS����ģ����ǰ֪ͨTDS��ϵͳ���������жϡ�
                                                                 [1]: �ж�����1��GS����ģ����GAP�жϣ�֪ͨTDS������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
                                                                 [2]: �ж�����2��GS����ģ����GAP�жϡ�
                                                                 [3]: �ж�����3��GS����ģ�����������жϡ�
                                                                 [4]: �ж�����4��GS����ģ��ǿ��TDS�˳���ϵͳ�����жϡ�
                                                                 [5]: �ж�����5��GS����ģ��֪ͨTDS�ϱ����β��������
                                                                 [6]: �ж�����6��������
                                                                 [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
                                                                 �ж�״̬��־0��1��2ֻ�е�TDS������ģʱ���ܲ�����
                                                                 �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x07D4��int_mask_tds_rcv_gs���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved              : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_TDS_RCV_GS_UNION;
#define BBPCOMM_INT_TYPE_TDS_RCV_GS_o_int_type_tds_rcv_gs_START  (0)
#define BBPCOMM_INT_TYPE_TDS_RCV_GS_o_int_type_tds_rcv_gs_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_TDS_RCV_TDS_UNION
 �ṹ˵��  : INT_TYPE_TDS_RCV_TDS �Ĵ����ṹ���塣��ַƫ����:0x07F0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_tds_rcv_tds_reg;
    struct
    {
        unsigned int  o_int_type_tds_rcv_tds : 16; /* bit[0-15] : �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
                                                                  [0]: �ж�����0��TDS����ģ����ǰ֪ͨTDS��Ƶ���������жϡ�
                                                                  [1]: �ж�����1��TDS����ģ����GAP�жϣ�֪ͨTDS������Ƶ������Ƶͨ�����ã������л��Ȳ�����
                                                                  [2]: �ж�����2��TDS����ģ����GAP�жϡ�
                                                                  [3]: �ж�����3��TDS����ģ������Ƶ�����������жϡ�
                                                                  [4]: �ж�����4��TDS����ģ��ǿ��TDS�˳���Ƶ�����жϡ�
                                                                  [5]: �ж�����5��TDS����ģ��֪ͨTDS�ϱ����β��������
                                                                  [6]: �ж�����6��������
                                                                  [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
                                                                  �ж�״̬��־0��1��2ֻ�е�TDS������ģʱ���ܲ�����
                                                                  �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x07CC��int_mask_tds_rcv_tds���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved               : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_TDS_RCV_TDS_UNION;
#define BBPCOMM_INT_TYPE_TDS_RCV_TDS_o_int_type_tds_rcv_tds_START  (0)
#define BBPCOMM_INT_TYPE_TDS_RCV_TDS_o_int_type_tds_rcv_tds_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_TDS_INT012_UNION
 �ṹ˵��  : INT_TYPE_TDS_INT012 �Ĵ����ṹ���塣��ַƫ����:0x07F4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_tds_int012_reg;
    struct
    {
        unsigned int  o_int_type_tds_int012 : 3;  /* bit[0-2] : ������ģ����int0��1��2���ϱ���(������Ƶ����ϵͳ����)��������Ч��
                                                                [0]: T��ģʱ��CTU����֪ͨTDSP����int0�жϡ�
                                                                [1]: T��ģʱ��CTU����֪ͨTDSP����int1�жϡ�
                                                                [2]: T��ģʱ��CTU����֪ͨTDSP����int2�жϡ�
                                                                �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x07DC��int_mask_tds_int012���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved              : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_TDS_INT012_UNION;
#define BBPCOMM_INT_TYPE_TDS_INT012_o_int_type_tds_int012_START  (0)
#define BBPCOMM_INT_TYPE_TDS_INT012_o_int_type_tds_int012_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TDS_SND_LTE_INT_13_UNION
 �ṹ˵��  : TDS_SND_LTE_INT_13 �Ĵ����ṹ���塣��ַƫ����:0x07F8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      tds_snd_lte_int_13_reg;
    struct
    {
        unsigned int  reserved_0         : 3;  /* bit[0-2]  : ���� */
        unsigned int  tds_snd_lte_int_13 : 13; /* bit[3-15] : �߼������㡣����Ч��
                                                              
                                                              bit15~7����Ӧtds_snd_lte_int_15 ~ 7��
                                                              TDS DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_lte_rcv_tds[15:7]����LDSP��
                                                              ��Чʱ�̣�������Ч
                                                              
                                                              bit6����Ӧtds_snd_lte_int_6��
                                                              TDSDSPͨ���˼Ĵ�����������6�жϣ�int_type_lte_rcv_tds[6]����LDSP��
                                                              ��Чʱ�̣�������Ч
                                                              
                                                              bit5����Ӧtds_snd_lte_int_5��
                                                              TDS��ģʱ֪ͨLDSP L�������ڵ������Ч��
                                                              TDS DSPͨ���˼Ĵ�����������5�жϣ�int_type_lte_rcv_tds[5]����LDSP��
                                                              ��Чʱ�̣�������Ч
                                                              
                                                              bit4����Ӧtds_snd_lte_int_4��
                                                              TDS��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
                                                              TDS DSPͨ���˼Ĵ�����������4�жϣ�int_type_lte_rcv_tds[4]����LDSP��
                                                              ��Чʱ�̣�������Ч
                                                              
                                                              bit3����Ӧtds_snd_lte_int_3��TDS��������ָʾ������Ч��
                                                              ���ڴ����ж�����3 ��int_type_lte_rcv_tds[3]����LDSP��L��ģ�¶�TDS������ϵͳ����ʱ�����TDS����������TDS DSP���ô˱�־Ϊ1�� 
                                                              ��Чʱ�̣�������Ч */
        unsigned int  reserved_1         : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_TDS_SND_LTE_INT_13_UNION;
#define BBPCOMM_TDS_SND_LTE_INT_13_tds_snd_lte_int_13_START  (3)
#define BBPCOMM_TDS_SND_LTE_INT_13_tds_snd_lte_int_13_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TDS_SND_TDS_INT_13_UNION
 �ṹ˵��  : TDS_SND_TDS_INT_13 �Ĵ����ṹ���塣��ַƫ����:0x07FC����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      tds_snd_tds_int_13_reg;
    struct
    {
        unsigned int  reserved_0         : 3;  /* bit[0-2]  : ���� */
        unsigned int  tds_snd_tds_int_13 : 13; /* bit[3-15] : �߼������㡣����Ч��
                                                              
                                                              bit15~7����Ӧtds_snd_tds_int_15 ~ 7��
                                                              TDS DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_tds_rcv_tds[15:7]����TDSP��
                                                              ��Чʱ�̣�������Ч
                                                              
                                                              bit6����Ӧtds_snd_tds_int_6��
                                                              TDSDSPͨ���˼Ĵ�����������6�жϣ�int_type_tds_rcv_tds[6]����TDSP��
                                                              ��Чʱ�̣�������Ч
                                                              
                                                              bit5����Ӧtds_snd_tds_int_5��
                                                              TDS��ģʱ֪ͨTDSP T�������ڵ������Ч��
                                                              TDS DSPͨ���˼Ĵ�����������5�жϣ�int_type_tds_rcv_tds[5]����TDSP��
                                                              ��Чʱ�̣�������Ч
                                                              
                                                              bit4����Ӧtds_snd_tds_int_4��
                                                              TDS��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
                                                              TDS DSPͨ���˼Ĵ�����������4�жϣ�int_type_tds_rcv_tds[4]����TDSP��
                                                              ��Чʱ�̣�������Ч
                                                              
                                                              bit3����Ӧtds_snd_tds_int_3��TDS��������ָʾ������Ч��
                                                              ���ڴ����ж�����3 ��int_type_tds_rcv_tds[3]����TDSP��T��ģ�¶�TDS������ϵͳ����ʱ�����TDS����������TDS DSP���ô˱�־Ϊ1�� 
                                                              ��Чʱ�̣�������Ч */
        unsigned int  reserved_1         : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_TDS_SND_TDS_INT_13_UNION;
#define BBPCOMM_TDS_SND_TDS_INT_13_tds_snd_tds_int_13_START  (3)
#define BBPCOMM_TDS_SND_TDS_INT_13_tds_snd_tds_int_13_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TDS_SND_GM_INT_13_UNION
 �ṹ˵��  : TDS_SND_GM_INT_13 �Ĵ����ṹ���塣��ַƫ����:0x0800����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      tds_snd_gm_int_13_reg;
    struct
    {
        unsigned int  reserved_0        : 3;  /* bit[0-2]  : ���� */
        unsigned int  tds_snd_gm_int_13 : 13; /* bit[3-15] : �߼������㡣����Ч��
                                                             
                                                             bit15~7����Ӧtds_snd_gm_int_15 ~ 7��
                                                             TDS DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_gm_rcv_tds[15:7]����GMDSP��
                                                             ��Чʱ�̣�������Ч
                                                             
                                                             bit6����Ӧtds_snd_gm_int_6��
                                                             TDSDSPͨ���˼Ĵ�����������6�жϣ�int_type_gm_rcv_tds[6]����GMDSP��
                                                             ��Чʱ�̣�������Ч
                                                             
                                                             bit5����Ӧtds_snd_gm_int_5��
                                                             TDS��ģʱ֪ͨGMDSP GM�������ڵ������Ч��
                                                             TDS DSPͨ���˼Ĵ�����������5�жϣ�int_type_gm_rcv_tds[5]����GMDSP��
                                                             ��Чʱ�̣�������Ч
                                                             
                                                             bit4����Ӧtds_snd_gm_int_4��
                                                             TDS��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
                                                             TDS DSPͨ���˼Ĵ�����������4�жϣ�int_type_gm_rcv_tds[4]����GMDSP��
                                                             ��Чʱ�̣�������Ч
                                                             
                                                             bit3����Ӧtds_snd_gm_int_3��TDS��������ָʾ������Ч��
                                                             ���ڴ����ж�����3 ��int_type_gm_rcv_tds[3]����GMDSP��GM��ģ�¶�TDS������ϵͳ����ʱ�����TDS����������TDS DSP���ô˱�־Ϊ1�� 
                                                             ��Чʱ�̣�������Ч */
        unsigned int  reserved_1        : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_TDS_SND_GM_INT_13_UNION;
#define BBPCOMM_TDS_SND_GM_INT_13_tds_snd_gm_int_13_START  (3)
#define BBPCOMM_TDS_SND_GM_INT_13_tds_snd_gm_int_13_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TDS_SND_GS_INT_13_UNION
 �ṹ˵��  : TDS_SND_GS_INT_13 �Ĵ����ṹ���塣��ַƫ����:0x0804����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      tds_snd_gs_int_13_reg;
    struct
    {
        unsigned int  reserved_0        : 3;  /* bit[0-2]  : ���� */
        unsigned int  tds_snd_gs_int_13 : 13; /* bit[3-15] : �߼������㡣����Ч��
                                                             
                                                             bit15~7����Ӧtds_snd_gs_int_15 ~ 7��
                                                             TDS DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_gs_rcv_tds[15:7]����GSDSP��
                                                             ��Чʱ�̣�������Ч
                                                             
                                                             bit6����Ӧtds_snd_gs_int_6��
                                                             TDSDSPͨ���˼Ĵ�����������6�жϣ�int_type_gs_rcv_tds[6]����GSDSP��
                                                             ��Чʱ�̣�������Ч
                                                             
                                                             bit5����Ӧtds_snd_gs_int_5��
                                                             TDS��ģʱ֪ͨGSDSP GS�������ڵ������Ч��
                                                             TDS DSPͨ���˼Ĵ�����������5�жϣ�int_type_gs_rcv_tds[5]����GSDSP��
                                                             ��Чʱ�̣�������Ч
                                                             
                                                             bit4����Ӧtds_snd_gs_int_4��
                                                             TDS��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
                                                             TDS DSPͨ���˼Ĵ�����������4�жϣ�int_type_gs_rcv_tds[4]����GSDSP��
                                                             ��Чʱ�̣�������Ч
                                                             
                                                             bit3����Ӧtds_snd_gs_int_3��TDS��������ָʾ������Ч��
                                                             ���ڴ����ж�����3 ��int_type_gs_rcv_tds[3]����GSDSP��GS��ģ�¶�TDS������ϵͳ����ʱ�����TDS����������TDS DSP���ô˱�־Ϊ1�� 
                                                             ��Чʱ�̣�������Ч */
        unsigned int  reserved_1        : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_TDS_SND_GS_INT_13_UNION;
#define BBPCOMM_TDS_SND_GS_INT_13_tds_snd_gs_int_13_START  (3)
#define BBPCOMM_TDS_SND_GS_INT_13_tds_snd_gs_int_13_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TDS_SND_W_INT_13_UNION
 �ṹ˵��  : TDS_SND_W_INT_13 �Ĵ����ṹ���塣��ַƫ����:0x0808����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      tds_snd_w_int_13_reg;
    struct
    {
        unsigned int  reserved_0       : 3;  /* bit[0-2]  : ���� */
        unsigned int  tds_snd_w_int_13 : 13; /* bit[3-15] : �߼������㡣����Ч��
                                                            
                                                            bit15~7����Ӧtds_snd_w_int_15 ~ 7��
                                                            TDS DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_w_rcv_tds[15:7]����WDSP��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit6����Ӧtds_snd_w_int_6��
                                                            TDSDSPͨ���˼Ĵ�����������6�жϣ�int_type_w_rcv_tds[6]����WDSP��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit5����Ӧtds_snd_w_int_5��
                                                            TDS��ģʱ֪ͨWDSP W�������ڵ������Ч��
                                                            TDS DSPͨ���˼Ĵ�����������5�жϣ�int_type_w_rcv_tds[5]����WDSP��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit4����Ӧtds_snd_w_int_4��
                                                            TDS��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
                                                            TDS DSPͨ���˼Ĵ�����������4�жϣ�int_type_w_rcv_tds[4]����WDSP��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit3����Ӧtds_snd_w_int_3��TDS��������ָʾ������Ч��
                                                            ���ڴ����ж�����3 ��int_type_w_rcv_tds[3]����WDSP��W��ģ�¶�TDS������ϵͳ����ʱ�����TDS����������TDS DSP���ô˱�־Ϊ1�� 
                                                            ��Чʱ�̣�������Ч */
        unsigned int  reserved_1       : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_TDS_SND_W_INT_13_UNION;
#define BBPCOMM_TDS_SND_W_INT_13_tds_snd_w_int_13_START  (3)
#define BBPCOMM_TDS_SND_W_INT_13_tds_snd_w_int_13_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GM_INTERSYS_MEASURE_TYPE_UNION
 �ṹ˵��  : GM_INTERSYS_MEASURE_TYPE �Ĵ����ṹ���塣��ַƫ����:0x080C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gm_intersys_measure_type_reg;
    struct
    {
        unsigned int  gm_intersys_measure_type : 4;  /* bit[0-3] : ��ϵͳ�������͡�
                                                                   4��d0������GM RSSI��
                                                                   4��d1: ����GM bsic verification��
                                                                   4��d2: ����GM bsic confirm��
                                                                   4��d3: ������GM��
                                                                   4��d4: 2G ANR��
                                                                   ����Ԥ��
                                                                   ��Чʱ�̣�������Ч */
        unsigned int  reserved                 : 28; /* bit[4-31]: ���� */
    } reg;
} BBPCOMM_GM_INTERSYS_MEASURE_TYPE_UNION;
#define BBPCOMM_GM_INTERSYS_MEASURE_TYPE_gm_intersys_measure_type_START  (0)
#define BBPCOMM_GM_INTERSYS_MEASURE_TYPE_gm_intersys_measure_type_END    (3)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GM_MEASURE_REPORT_VALID_UNION
 �ṹ˵��  : GM_MEASURE_REPORT_VALID �Ĵ����ṹ���塣��ַƫ����:0x0810����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gm_measure_report_valid_reg;
    struct
    {
        unsigned int  gm_measure_report_valid : 1;  /* bit[0]   : ��Ƶ��������ڵ�ָʾ��L����TDS/W/Gs��Ϊ��ģ��֪ͨGM DSP GM�����ĵ�Ƶ�����ڵ��
                                                                  ֻ������̬����Ҫ���á�
                                                                  ��ƽ�źţ�����Ч��
                                                                  ��Чʱ�̣�������Ч */
        unsigned int  reserved                : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_GM_MEASURE_REPORT_VALID_UNION;
#define BBPCOMM_GM_MEASURE_REPORT_VALID_gm_measure_report_valid_START  (0)
#define BBPCOMM_GM_MEASURE_REPORT_VALID_gm_measure_report_valid_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_GM_RCV_LTE_UNION
 �ṹ˵��  : INT_CLEAR_GM_RCV_LTE �Ĵ����ṹ���塣��ַƫ����:0x081C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_gm_rcv_lte_reg;
    struct
    {
        unsigned int  int_clear_gm_rcv_lte : 16; /* bit[0-15] : �߼������㡣
                                                                �жϱ�־���ָʾ������Ч���������INT_TYPE_GM_RCV_LTE[15:0]��Ӧbitλ
                                                                ��Чʱ�̣�������Ч */
        unsigned int  reserved             : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_GM_RCV_LTE_UNION;
#define BBPCOMM_INT_CLEAR_GM_RCV_LTE_int_clear_gm_rcv_lte_START  (0)
#define BBPCOMM_INT_CLEAR_GM_RCV_LTE_int_clear_gm_rcv_lte_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_GM_RCV_TDS_UNION
 �ṹ˵��  : INT_CLEAR_GM_RCV_TDS �Ĵ����ṹ���塣��ַƫ����:0x0820����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_gm_rcv_tds_reg;
    struct
    {
        unsigned int  int_clear_gm_rcv_tds : 16; /* bit[0-15] : �߼������㡣
                                                                �жϱ�־���ָʾ������Ч���������INT_TYPE_GM_RCV_TDS[15:0]��Ӧbitλ
                                                                ��Чʱ�̣�������Ч */
        unsigned int  reserved             : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_GM_RCV_TDS_UNION;
#define BBPCOMM_INT_CLEAR_GM_RCV_TDS_int_clear_gm_rcv_tds_START  (0)
#define BBPCOMM_INT_CLEAR_GM_RCV_TDS_int_clear_gm_rcv_tds_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_GM_RCV_GM_UNION
 �ṹ˵��  : INT_CLEAR_GM_RCV_GM �Ĵ����ṹ���塣��ַƫ����:0x0824����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_gm_rcv_gm_reg;
    struct
    {
        unsigned int  int_clear_gm_rcv_gm : 16; /* bit[0-15] : �߼������㡣
                                                               �жϱ�־���ָʾ������Ч���������INT_TYPE_GM_RCV_GM[15:0]��Ӧbitλ
                                                               ��Чʱ�̣�������Ч */
        unsigned int  reserved            : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_GM_RCV_GM_UNION;
#define BBPCOMM_INT_CLEAR_GM_RCV_GM_int_clear_gm_rcv_gm_START  (0)
#define BBPCOMM_INT_CLEAR_GM_RCV_GM_int_clear_gm_rcv_gm_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_GM_RCV_GS_UNION
 �ṹ˵��  : INT_CLEAR_GM_RCV_GS �Ĵ����ṹ���塣��ַƫ����:0x0828����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_gm_rcv_gs_reg;
    struct
    {
        unsigned int  int_clear_gm_rcv_gs : 16; /* bit[0-15] : �߼������㡣
                                                               �жϱ�־���ָʾ������Ч���������INT_TYPE_GM_RCV_GS[15:0]��Ӧbitλ
                                                               ��Чʱ�̣�������Ч */
        unsigned int  reserved            : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_GM_RCV_GS_UNION;
#define BBPCOMM_INT_CLEAR_GM_RCV_GS_int_clear_gm_rcv_gs_START  (0)
#define BBPCOMM_INT_CLEAR_GM_RCV_GS_int_clear_gm_rcv_gs_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_GM_RCV_W_UNION
 �ṹ˵��  : INT_CLEAR_GM_RCV_W �Ĵ����ṹ���塣��ַƫ����:0x082C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_gm_rcv_w_reg;
    struct
    {
        unsigned int  int_clear_gm_rcv_w : 16; /* bit[0-15] : �߼������㡣
                                                              �жϱ�־���ָʾ������Ч���������INT_TYPE_GM_RCV_W[15:0]��Ӧbitλ
                                                              ��Чʱ�̣�������Ч */
        unsigned int  reserved           : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_GM_RCV_W_UNION;
#define BBPCOMM_INT_CLEAR_GM_RCV_W_int_clear_gm_rcv_w_START  (0)
#define BBPCOMM_INT_CLEAR_GM_RCV_W_int_clear_gm_rcv_w_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_GM_INT012_UNION
 �ṹ˵��  : INT_CLEAR_GM_INT012 �Ĵ����ṹ���塣��ַƫ����:0x0830����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_gm_int012_reg;
    struct
    {
        unsigned int  int_clear_gm_int012 : 3;  /* bit[0-2] : �߼������㡣
                                                              �жϱ�־���ָʾ������Ч���������INT_TYPE_GM_INT012[2:0]��Ӧbitλ
                                                              ��Чʱ�̣�������Ч */
        unsigned int  reserved            : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_GM_INT012_UNION;
#define BBPCOMM_INT_CLEAR_GM_INT012_int_clear_gm_int012_START  (0)
#define BBPCOMM_INT_CLEAR_GM_INT012_int_clear_gm_int012_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_GM_RCV_LTE_UNION
 �ṹ˵��  : INT_MASK_GM_RCV_LTE �Ĵ����ṹ���塣��ַƫ����:0x0834����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_gm_rcv_lte_reg;
    struct
    {
        unsigned int  int_mask_gm_rcv_lte : 16; /* bit[0-15] : �ж����α�־����������INT_TYPE_GM_RCV_LTE[15:0]��Ӧbit�жϡ�
                                                               0�������ж��ϱ���
                                                               1��ʹ���ж��ϱ���
                                                               ����ʱ�̣���ʼ��
                                                               ��Чʱ�̣�������Ч */
        unsigned int  reserved            : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_GM_RCV_LTE_UNION;
#define BBPCOMM_INT_MASK_GM_RCV_LTE_int_mask_gm_rcv_lte_START  (0)
#define BBPCOMM_INT_MASK_GM_RCV_LTE_int_mask_gm_rcv_lte_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_GM_RCV_TDS_UNION
 �ṹ˵��  : INT_MASK_GM_RCV_TDS �Ĵ����ṹ���塣��ַƫ����:0x0838����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_gm_rcv_tds_reg;
    struct
    {
        unsigned int  int_mask_gm_rcv_tds : 16; /* bit[0-15] : �ж����α�־����������INT_TYPE_GM_RCV_TDS[15:0]��Ӧbit�жϡ�
                                                               0�������ж��ϱ���
                                                               1��ʹ���ж��ϱ���
                                                               ����ʱ�̣���ʼ��
                                                               ��Чʱ�̣�������Ч */
        unsigned int  reserved            : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_GM_RCV_TDS_UNION;
#define BBPCOMM_INT_MASK_GM_RCV_TDS_int_mask_gm_rcv_tds_START  (0)
#define BBPCOMM_INT_MASK_GM_RCV_TDS_int_mask_gm_rcv_tds_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_GM_RCV_GM_UNION
 �ṹ˵��  : INT_MASK_GM_RCV_GM �Ĵ����ṹ���塣��ַƫ����:0x083C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_gm_rcv_gm_reg;
    struct
    {
        unsigned int  int_mask_gm_rcv_gm : 16; /* bit[0-15] : �ж����α�־����������INT_TYPE_GM_RCV_GM[15:0]��Ӧbit�жϡ�
                                                              0�������ж��ϱ���
                                                              1��ʹ���ж��ϱ���
                                                              ����ʱ�̣���ʼ��
                                                              ��Чʱ�̣�������Ч */
        unsigned int  reserved           : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_GM_RCV_GM_UNION;
#define BBPCOMM_INT_MASK_GM_RCV_GM_int_mask_gm_rcv_gm_START  (0)
#define BBPCOMM_INT_MASK_GM_RCV_GM_int_mask_gm_rcv_gm_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_GM_RCV_GS_UNION
 �ṹ˵��  : INT_MASK_GM_RCV_GS �Ĵ����ṹ���塣��ַƫ����:0x0840����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_gm_rcv_gs_reg;
    struct
    {
        unsigned int  int_mask_gm_rcv_gs : 16; /* bit[0-15] : �ж����α�־����������INT_TYPE_GM_RCV_GS[15:0]��Ӧbit�жϡ�
                                                              0�������ж��ϱ���
                                                              1��ʹ���ж��ϱ���
                                                              ����ʱ�̣���ʼ��
                                                              ��Чʱ�̣�������Ч */
        unsigned int  reserved           : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_GM_RCV_GS_UNION;
#define BBPCOMM_INT_MASK_GM_RCV_GS_int_mask_gm_rcv_gs_START  (0)
#define BBPCOMM_INT_MASK_GM_RCV_GS_int_mask_gm_rcv_gs_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_GM_RCV_W_UNION
 �ṹ˵��  : INT_MASK_GM_RCV_W �Ĵ����ṹ���塣��ַƫ����:0x0844����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_gm_rcv_w_reg;
    struct
    {
        unsigned int  int_mask_gm_rcv_w : 16; /* bit[0-15] : �ж����α�־����������INT_TYPE_GM_RCV_W[15:0]��Ӧbit�жϡ�
                                                             0�������ж��ϱ���
                                                             1��ʹ���ж��ϱ���
                                                             ����ʱ�̣���ʼ��
                                                             ��Чʱ�̣�������Ч */
        unsigned int  reserved          : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_GM_RCV_W_UNION;
#define BBPCOMM_INT_MASK_GM_RCV_W_int_mask_gm_rcv_w_START  (0)
#define BBPCOMM_INT_MASK_GM_RCV_W_int_mask_gm_rcv_w_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_GM_INT012_UNION
 �ṹ˵��  : INT_MASK_GM_INT012 �Ĵ����ṹ���塣��ַƫ����:0x0848����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_gm_int012_reg;
    struct
    {
        unsigned int  int_mask_gm_int012 : 3;  /* bit[0-2] : �ж����α�־����������INT_TYPE_GM_INT012[2:0]��Ӧbit�жϡ�
                                                             0�������ж��ϱ���
                                                             1��ʹ���ж��ϱ���
                                                             ����ʱ�̣���ʼ��
                                                             ��Чʱ�̣�������Ч */
        unsigned int  reserved           : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_GM_INT012_UNION;
#define BBPCOMM_INT_MASK_GM_INT012_int_mask_gm_int012_START  (0)
#define BBPCOMM_INT_MASK_GM_INT012_int_mask_gm_int012_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_GM_RCV_LTE_UNION
 �ṹ˵��  : INT_TYPE_GM_RCV_LTE �Ĵ����ṹ���塣��ַƫ����:0x084C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_gm_rcv_lte_reg;
    struct
    {
        unsigned int  o_int_type_gm_rcv_lte : 16; /* bit[0-15] : �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
                                                                 [0]: �ж�����0�� LTE����ģ����ǰ֪ͨGM��ϵͳ���������жϡ�
                                                                 [1]: �ж�����1�� LTE����ģ����GAP�жϣ�֪ͨGM������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
                                                                 [2]: �ж�����2�� LTE����ģ����GAP�жϡ�
                                                                 [3]: �ж�����3��LTE����ģ�����������жϡ�
                                                                 [4]: �ж�����4��LTE����ģ��ǿ��GM�˳���ϵͳ�����жϡ�
                                                                 [5]: �ж�����5��LTE����ģ��֪ͨGM�ϱ����β��������
                                                                 [6]: ������
                                                                 [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
                                                                 �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x0834��int_mask_gm_rcv_lte���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved              : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_GM_RCV_LTE_UNION;
#define BBPCOMM_INT_TYPE_GM_RCV_LTE_o_int_type_gm_rcv_lte_START  (0)
#define BBPCOMM_INT_TYPE_GM_RCV_LTE_o_int_type_gm_rcv_lte_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_GM_RCV_TDS_UNION
 �ṹ˵��  : INT_TYPE_GM_RCV_TDS �Ĵ����ṹ���塣��ַƫ����:0x0850����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_gm_rcv_tds_reg;
    struct
    {
        unsigned int  o_int_type_gm_rcv_tds : 16; /* bit[0-15] : �ж�״̬��־0��1��2ֻ�е�TDS������ģʱ���ܲ�����
                                                                 
                                                                 [0]: �ж�����0�� TDS����ģ����ǰ֪ͨGM��ϵͳ���������жϡ�
                                                                 [1]: �ж�����1�� TDS����ģ����GAP�жϣ�֪ͨGM������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
                                                                 [2]: �ж�����2�� TDS����ģ����GAP�жϡ�
                                                                 [3]: �ж�����3��TDS����ģ�����������жϡ�
                                                                 [4]: �ж�����4��TDS����ģ��ǿ��GM�˳���ϵͳ�����жϡ�
                                                                 [5]: �ж�����5��TDS����ģ��֪ͨGM�ϱ����β��������
                                                                 [6]: �ж�����6��������
                                                                 [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
                                                                 �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x0838��int_mask_gm_rcv_tds���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved              : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_GM_RCV_TDS_UNION;
#define BBPCOMM_INT_TYPE_GM_RCV_TDS_o_int_type_gm_rcv_tds_START  (0)
#define BBPCOMM_INT_TYPE_GM_RCV_TDS_o_int_type_gm_rcv_tds_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_GM_RCV_W_UNION
 �ṹ˵��  : INT_TYPE_GM_RCV_W �Ĵ����ṹ���塣��ַƫ����:0x0854����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_gm_rcv_w_reg;
    struct
    {
        unsigned int  o_int_type_gm_rcv_w : 16; /* bit[0-15] : �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
                                                               [0]: �ж�����0��W����ģ����ǰ֪ͨGM��ϵͳ���������жϡ�
                                                               [1]: �ж�����1��W����ģ����GAP�жϣ�֪ͨGM������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
                                                               [2]: �ж�����2��W����ģ����GAP�жϡ�
                                                               [3]: �ж�����3��W����ģ�����������жϡ�
                                                               [4]: �ж�����4��W����ģ��ǿ��GM�˳���ϵͳ�����жϡ�
                                                               [5]: �ж�����5��W����ģ��֪ͨGM�ϱ����β��������
                                                               [6]: �ж�����6��������
                                                               [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
                                                               �ж�״̬��־0��1��2ֻ�е�W������ģʱ���ܲ�����
                                                               �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x0844��int_mask_gm_rcv_w���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved            : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_GM_RCV_W_UNION;
#define BBPCOMM_INT_TYPE_GM_RCV_W_o_int_type_gm_rcv_w_START  (0)
#define BBPCOMM_INT_TYPE_GM_RCV_W_o_int_type_gm_rcv_w_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_GM_RCV_GS_UNION
 �ṹ˵��  : INT_TYPE_GM_RCV_GS �Ĵ����ṹ���塣��ַƫ����:0x0858����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_gm_rcv_gs_reg;
    struct
    {
        unsigned int  o_int_type_gm_rcv_gs : 16; /* bit[0-15] : [0]: �ж�����0��GS����ģ����ǰ֪ͨGM��ϵͳ���������жϡ�
                                                                [1]: �ж�����1��GS����ģ����GAP�жϣ�֪ͨGM������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
                                                                [2]: �ж�����2��GS����ģ����GAP�жϡ�
                                                                [3]: �ж�����3��GS����ģ�����������жϡ�
                                                                [4]: �ж�����4��GS����ģ��ǿ��GM�˳���ϵͳ�����жϡ�
                                                                [5]: �ж�����5��GS����ģ��֪ͨGM�ϱ����β��������
                                                                [6]: �ж�����6��������
                                                                [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
                                                                �ж�״̬��־0��1��2ֻ�е�TDS������ģʱ���ܲ�����
                                                                �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x0840��int_mask_gm_rcv_gs���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved             : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_GM_RCV_GS_UNION;
#define BBPCOMM_INT_TYPE_GM_RCV_GS_o_int_type_gm_rcv_gs_START  (0)
#define BBPCOMM_INT_TYPE_GM_RCV_GS_o_int_type_gm_rcv_gs_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_GM_RCV_GM_UNION
 �ṹ˵��  : INT_TYPE_GM_RCV_GM �Ĵ����ṹ���塣��ַƫ����:0x085C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_gm_rcv_gm_reg;
    struct
    {
        unsigned int  o_int_type_gm_rcv_gm : 16; /* bit[0-15] : �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
                                                                [0]: �ж�����0��GM����ģ����ǰ֪ͨGM��Ƶ���������жϡ�
                                                                [1]: �ж�����1��GM����ģ����GAP�жϣ�֪ͨGM������Ƶ������Ƶͨ�����ã������л��Ȳ�����
                                                                [2]: �ж�����2��GM����ģ����GAP�жϡ�
                                                                [3]: �ж�����3��GM����ģ������Ƶ�����������жϡ�
                                                                [4]: �ж�����4��GM����ģ��ǿ��GM�˳���Ƶ�����жϡ�
                                                                [5]: �ж�����5��GM����ģ��֪ͨGM�ϱ����β��������
                                                                [6]: �ж�����6��������
                                                                [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
                                                                �ж�״̬��־0��1��2ֻ�е�GM������ģʱ���ܲ�����
                                                                �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x083C��int_mask_gm_rcv_gm���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved             : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_GM_RCV_GM_UNION;
#define BBPCOMM_INT_TYPE_GM_RCV_GM_o_int_type_gm_rcv_gm_START  (0)
#define BBPCOMM_INT_TYPE_GM_RCV_GM_o_int_type_gm_rcv_gm_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_GM_INT012_UNION
 �ṹ˵��  : INT_TYPE_GM_INT012 �Ĵ����ṹ���塣��ַƫ����:0x0860����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_gm_int012_reg;
    struct
    {
        unsigned int  o_int_type_gm_int012 : 3;  /* bit[0-2] : ������ģ����int0��1��2���ϱ���(������Ƶ����ϵͳ����)��������Ч��
                                                               [0]: GM��ģʱ��CTU����֪ͨGMDSP����int0�жϡ�
                                                               [1]: GM��ģʱ��CTU����֪ͨGMDSP����int1�жϡ�
                                                               [2]: GM��ģʱ��CTU����֪ͨGMDSP����int2�жϡ�
                                                               �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x0848��int_mask_gm_int012���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved             : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_GM_INT012_UNION;
#define BBPCOMM_INT_TYPE_GM_INT012_o_int_type_gm_int012_START  (0)
#define BBPCOMM_INT_TYPE_GM_INT012_o_int_type_gm_int012_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GM_SND_LTE_INT_13_UNION
 �ṹ˵��  : GM_SND_LTE_INT_13 �Ĵ����ṹ���塣��ַƫ����:0x0864����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gm_snd_lte_int_13_reg;
    struct
    {
        unsigned int  reserved_0        : 3;  /* bit[0-2]  : ���� */
        unsigned int  gm_snd_lte_int_13 : 13; /* bit[3-15] : �߼������㡣����Ч��
                                                             
                                                             bit15~7����Ӧgm_snd_lte_int_15 ~ 7��
                                                             GM DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_lte_rcv_gm[15:7]����LTEDSP��
                                                             ��Чʱ�̣�������Ч
                                                             
                                                             bit6����Ӧgm_snd_lte_int_6��
                                                             GMDSPͨ���˼Ĵ�����������6�жϣ�int_type_lte_rcv_gm[6]����LTEDSP��
                                                             ��Чʱ�̣�������Ч
                                                             
                                                             bit5����Ӧgm_snd_lte_int_5��
                                                             GM��ģʱ֪ͨLTEDSP LTE�������ڵ������Ч��
                                                             GM DSPͨ���˼Ĵ�����������5�жϣ�int_type_lte_rcv_gm[5]����LTEDSP��
                                                             ��Чʱ�̣�������Ч
                                                             
                                                             bit4����Ӧgm_snd_lte_int_4��
                                                             GM��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
                                                             GM DSPͨ���˼Ĵ�����������4�жϣ�int_type_lte_rcv_gm[4]����LTEDSP��
                                                             ��Чʱ�̣�������Ч
                                                             
                                                             bit3����Ӧgm_snd_lte_int_3��GM��������ָʾ������Ч��
                                                             ���ڴ����ж�����3 ��int_type_lte_rcv_gm[3]����LTEDSP��LTE��ģ�¶�GM������ϵͳ����ʱ�����GM����������GM DSP���ô˱�־Ϊ1�� 
                                                             ��Чʱ�̣�������Ч */
        unsigned int  reserved_1        : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_GM_SND_LTE_INT_13_UNION;
#define BBPCOMM_GM_SND_LTE_INT_13_gm_snd_lte_int_13_START  (3)
#define BBPCOMM_GM_SND_LTE_INT_13_gm_snd_lte_int_13_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GM_SND_TDS_INT_13_UNION
 �ṹ˵��  : GM_SND_TDS_INT_13 �Ĵ����ṹ���塣��ַƫ����:0x0868����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gm_snd_tds_int_13_reg;
    struct
    {
        unsigned int  reserved_0        : 3;  /* bit[0-2]  : ���� */
        unsigned int  gm_snd_tds_int_13 : 13; /* bit[3-15] : �߼������㡣����Ч��
                                                             
                                                             bit15~7����Ӧgm_snd_tds_int_15 ~ 7��
                                                             GM DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_tds_rcv_gm[15:7]����TDSDSP��
                                                             ��Чʱ�̣�������Ч
                                                             
                                                             bit6����Ӧgm_snd_tds_int_6��
                                                             GMDSPͨ���˼Ĵ�����������6�жϣ�int_type_tds_rcv_gm[6]����TDSDSP��
                                                             ��Чʱ�̣�������Ч
                                                             
                                                             bit5����Ӧgm_snd_tds_int_5��
                                                             GM��ģʱ֪ͨTDSDSP tds�������ڵ������Ч��
                                                             GM DSPͨ���˼Ĵ�����������5�жϣ�int_type_tds_rcv_gm[5]����TDSDSP��
                                                             ��Чʱ�̣�������Ч
                                                             
                                                             bit4����Ӧgm_snd_tds_int_4��
                                                             GM��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
                                                             GM DSPͨ���˼Ĵ�����������4�жϣ�int_type_tds_rcv_gm[4]����TDSDSP��
                                                             ��Чʱ�̣�������Ч
                                                             
                                                             bit3����Ӧgm_snd_tds_int_3��GM��������ָʾ������Ч��
                                                             ���ڴ����ж�����3 ��int_type_tds_rcv_gm[3]����TDSDSP��tds��ģ�¶�GM������ϵͳ����ʱ�����GM����������GM DSP���ô˱�־Ϊ1�� 
                                                             ��Чʱ�̣�������Ч */
        unsigned int  reserved_1        : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_GM_SND_TDS_INT_13_UNION;
#define BBPCOMM_GM_SND_TDS_INT_13_gm_snd_tds_int_13_START  (3)
#define BBPCOMM_GM_SND_TDS_INT_13_gm_snd_tds_int_13_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GM_SND_GM_INT_13_UNION
 �ṹ˵��  : GM_SND_GM_INT_13 �Ĵ����ṹ���塣��ַƫ����:0x086C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gm_snd_gm_int_13_reg;
    struct
    {
        unsigned int  reserved_0       : 3;  /* bit[0-2]  : ���� */
        unsigned int  gm_snd_gm_int_13 : 13; /* bit[3-15] : �߼������㡣����Ч��
                                                            
                                                            bit15~7����Ӧgm_snd_gm_int_15 ~ 7��
                                                            GM DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_gm_rcv_gm[15:7]����GMDSP��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit6����Ӧgm_snd_gm_int_6��
                                                            GMDSPͨ���˼Ĵ�����������6�жϣ�int_type_gm_rcv_gm[6]����GMDSP��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit5����Ӧgm_snd_gm_int_5��
                                                            GM��ģʱ֪ͨGMDSP GM�������ڵ������Ч��
                                                            GM DSPͨ���˼Ĵ�����������5�жϣ�int_type_gm_rcv_gm[5]����GMDSP��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit4����Ӧgm_snd_gm_int_4��
                                                            GM��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
                                                            GM DSPͨ���˼Ĵ�����������4�жϣ�int_type_gm_rcv_gm[4]����GMDSP��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit3����Ӧgm_snd_gm_int_3��GM��������ָʾ������Ч��
                                                            ���ڴ����ж�����3 ��int_type_gm_rcv_gm[3]����GMDSP��GM��ģ�¶�GM������ϵͳ����ʱ�����GM����������GM DSP���ô˱�־Ϊ1�� 
                                                            ��Чʱ�̣�������Ч */
        unsigned int  reserved_1       : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_GM_SND_GM_INT_13_UNION;
#define BBPCOMM_GM_SND_GM_INT_13_gm_snd_gm_int_13_START  (3)
#define BBPCOMM_GM_SND_GM_INT_13_gm_snd_gm_int_13_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GM_SND_GS_INT_13_UNION
 �ṹ˵��  : GM_SND_GS_INT_13 �Ĵ����ṹ���塣��ַƫ����:0x0870����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gm_snd_gs_int_13_reg;
    struct
    {
        unsigned int  reserved_0       : 3;  /* bit[0-2]  : ���� */
        unsigned int  gm_snd_gs_int_13 : 13; /* bit[3-15] : �߼������㡣����Ч��
                                                            
                                                            bit15~7����Ӧgm_snd_gs_int_15 ~ 7��
                                                            GM DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_gs_rcv_gm[15:7]����GSDSP��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit6����Ӧgm_snd_gs_int_6��
                                                            GMDSPͨ���˼Ĵ�����������6�жϣ�int_type_gs_rcv_gm[6]����GSDSP��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit5����Ӧgm_snd_gs_int_5��
                                                            GM��ģʱ֪ͨGSDSP GS�������ڵ������Ч��
                                                            GM DSPͨ���˼Ĵ�����������5�жϣ�int_type_gs_rcv_gm[5]����GSDSP��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit4����Ӧgm_snd_gs_int_4��
                                                            GM��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
                                                            GM DSPͨ���˼Ĵ�����������4�жϣ�int_type_gs_rcv_gm[4]����GSDSP��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit3����Ӧgm_snd_gs_int_3��GM��������ָʾ������Ч��
                                                            ���ڴ����ж�����3 ��int_type_gs_rcv_gm[3]����GSDSP��GS��ģ�¶�GM������ϵͳ����ʱ�����GM����������GM DSP���ô˱�־Ϊ1�� 
                                                            ��Чʱ�̣�������Ч */
        unsigned int  reserved_1       : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_GM_SND_GS_INT_13_UNION;
#define BBPCOMM_GM_SND_GS_INT_13_gm_snd_gs_int_13_START  (3)
#define BBPCOMM_GM_SND_GS_INT_13_gm_snd_gs_int_13_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GM_SND_W_INT_13_UNION
 �ṹ˵��  : GM_SND_W_INT_13 �Ĵ����ṹ���塣��ַƫ����:0x0874����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gm_snd_w_int_13_reg;
    struct
    {
        unsigned int  reserved_0      : 3;  /* bit[0-2]  : ���� */
        unsigned int  gm_snd_w_int_13 : 13; /* bit[3-15] : �߼������㡣����Ч��
                                                           
                                                           bit15~7����Ӧgm_snd_lte_int_15 ~ 7��
                                                           GM DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_lte_rcv_gm[15:7]����LTEDSP��
                                                           ��Чʱ�̣�������Ч
                                                           
                                                           bit6����Ӧgm_snd_lte_int_6��
                                                           GMDSPͨ���˼Ĵ�����������6�жϣ�int_type_lte_rcv_gm[6]����LTEDSP��
                                                           ��Чʱ�̣�������Ч
                                                           
                                                           bit5����Ӧgm_snd_lte_int_5��
                                                           GM��ģʱ֪ͨLTEDSP LTE�������ڵ������Ч��
                                                           GM DSPͨ���˼Ĵ�����������5�жϣ�int_type_lte_rcv_gm[5]����LTEDSP��
                                                           ��Чʱ�̣�������Ч
                                                           
                                                           bit4����Ӧgm_snd_lte_int_4��
                                                           GM��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
                                                           GM DSPͨ���˼Ĵ�����������4�жϣ�int_type_lte_rcv_gm[4]����LTEDSP��
                                                           ��Чʱ�̣�������Ч
                                                           
                                                           bit3����Ӧgm_snd_lte_int_3��GM��������ָʾ������Ч��
                                                           ���ڴ����ж�����3 ��int_type_lte_rcv_gm[3]����LTEDSP��LTE��ģ�¶�GM������ϵͳ����ʱ�����GM����������GM DSP���ô˱�־Ϊ1�� 
                                                           ��Чʱ�̣�������Ч */
        unsigned int  reserved_1      : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_GM_SND_W_INT_13_UNION;
#define BBPCOMM_GM_SND_W_INT_13_gm_snd_w_int_13_START  (3)
#define BBPCOMM_GM_SND_W_INT_13_gm_snd_w_int_13_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GS_INTERSYS_MEASURE_TYPE_UNION
 �ṹ˵��  : GS_INTERSYS_MEASURE_TYPE �Ĵ����ṹ���塣��ַƫ����:0x0878����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gs_intersys_measure_type_reg;
    struct
    {
        unsigned int  gs_intersys_measure_type : 4;  /* bit[0-3] : ��ϵͳ�������͡�
                                                                   4��d0������GS RSSI��
                                                                   4��d1: ����GS bsic verification��
                                                                   4��d2: ����GS bsic confirm��
                                                                   4��d3: ������GS
                                                                   4��d4: 2G ANR��
                                                                   ����Ԥ��
                                                                   ��Чʱ�̣�������Ч */
        unsigned int  reserved                 : 28; /* bit[4-31]: ���� */
    } reg;
} BBPCOMM_GS_INTERSYS_MEASURE_TYPE_UNION;
#define BBPCOMM_GS_INTERSYS_MEASURE_TYPE_gs_intersys_measure_type_START  (0)
#define BBPCOMM_GS_INTERSYS_MEASURE_TYPE_gs_intersys_measure_type_END    (3)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GS_MEASURE_REPORT_VALID_UNION
 �ṹ˵��  : GS_MEASURE_REPORT_VALID �Ĵ����ṹ���塣��ַƫ����:0x087C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gs_measure_report_valid_reg;
    struct
    {
        unsigned int  gs_measure_report_valid : 1;  /* bit[0]   : ��Ƶ��������ڵ�ָʾ��L����TDS/W/Gm��Ϊ��ģ��֪ͨGS DSP GS�����ĵ�Ƶ�����ڵ��
                                                                  ֻ������̬����Ҫ���á�
                                                                  ��ƽ�źţ�����Ч��
                                                                  ��Чʱ�̣�������Ч */
        unsigned int  reserved                : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_GS_MEASURE_REPORT_VALID_UNION;
#define BBPCOMM_GS_MEASURE_REPORT_VALID_gs_measure_report_valid_START  (0)
#define BBPCOMM_GS_MEASURE_REPORT_VALID_gs_measure_report_valid_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_GS_RCV_LTE_UNION
 �ṹ˵��  : INT_CLEAR_GS_RCV_LTE �Ĵ����ṹ���塣��ַƫ����:0x0888����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_gs_rcv_lte_reg;
    struct
    {
        unsigned int  int_clear_gs_rcv_lte : 16; /* bit[0-15] : �߼������㡣
                                                                �жϱ�־���ָʾ������Ч���������INT_TYPE_GS_RCV_LTE[15:0]��Ӧbitλ
                                                                ��Чʱ�̣�������Ч */
        unsigned int  reserved             : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_GS_RCV_LTE_UNION;
#define BBPCOMM_INT_CLEAR_GS_RCV_LTE_int_clear_gs_rcv_lte_START  (0)
#define BBPCOMM_INT_CLEAR_GS_RCV_LTE_int_clear_gs_rcv_lte_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_GS_RCV_TDS_UNION
 �ṹ˵��  : INT_CLEAR_GS_RCV_TDS �Ĵ����ṹ���塣��ַƫ����:0x088C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_gs_rcv_tds_reg;
    struct
    {
        unsigned int  int_clear_gs_rcv_tds : 16; /* bit[0-15] : �߼������㡣
                                                                �жϱ�־���ָʾ������Ч���������INT_TYPE_GS_RCV_TDS[15:0]��Ӧbitλ
                                                                ��Чʱ�̣�������Ч */
        unsigned int  reserved             : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_GS_RCV_TDS_UNION;
#define BBPCOMM_INT_CLEAR_GS_RCV_TDS_int_clear_gs_rcv_tds_START  (0)
#define BBPCOMM_INT_CLEAR_GS_RCV_TDS_int_clear_gs_rcv_tds_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_GS_RCV_GM_UNION
 �ṹ˵��  : INT_CLEAR_GS_RCV_GM �Ĵ����ṹ���塣��ַƫ����:0x0890����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_gs_rcv_gm_reg;
    struct
    {
        unsigned int  int_clear_gs_rcv_gm : 16; /* bit[0-15] : �߼������㡣
                                                               �жϱ�־���ָʾ������Ч���������INT_TYPE_GS_RCV_GM[15:0]��Ӧbitλ
                                                               ��Чʱ�̣�������Ч */
        unsigned int  reserved            : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_GS_RCV_GM_UNION;
#define BBPCOMM_INT_CLEAR_GS_RCV_GM_int_clear_gs_rcv_gm_START  (0)
#define BBPCOMM_INT_CLEAR_GS_RCV_GM_int_clear_gs_rcv_gm_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_GS_RCV_GS_UNION
 �ṹ˵��  : INT_CLEAR_GS_RCV_GS �Ĵ����ṹ���塣��ַƫ����:0x0894����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_gs_rcv_gs_reg;
    struct
    {
        unsigned int  int_clear_gs_rcv_gs : 16; /* bit[0-15] : �߼������㡣
                                                               �жϱ�־���ָʾ������Ч���������INT_TYPE_GS_RCV_GS[15:0]��Ӧbitλ
                                                               ��Чʱ�̣�������Ч */
        unsigned int  reserved            : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_GS_RCV_GS_UNION;
#define BBPCOMM_INT_CLEAR_GS_RCV_GS_int_clear_gs_rcv_gs_START  (0)
#define BBPCOMM_INT_CLEAR_GS_RCV_GS_int_clear_gs_rcv_gs_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_GS_RCV_W_UNION
 �ṹ˵��  : INT_CLEAR_GS_RCV_W �Ĵ����ṹ���塣��ַƫ����:0x0898����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_gs_rcv_w_reg;
    struct
    {
        unsigned int  int_clear_gs_rcv_w : 16; /* bit[0-15] : �߼������㡣
                                                              �жϱ�־���ָʾ������Ч���������INT_TYPE_GS_RCV_W[15:0]��Ӧbitλ
                                                              ��Чʱ�̣�������Ч */
        unsigned int  reserved           : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_GS_RCV_W_UNION;
#define BBPCOMM_INT_CLEAR_GS_RCV_W_int_clear_gs_rcv_w_START  (0)
#define BBPCOMM_INT_CLEAR_GS_RCV_W_int_clear_gs_rcv_w_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_GS_INT012_UNION
 �ṹ˵��  : INT_CLEAR_GS_INT012 �Ĵ����ṹ���塣��ַƫ����:0x089C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_gs_int012_reg;
    struct
    {
        unsigned int  int_clear_gs_int012 : 3;  /* bit[0-2] : �߼������㡣
                                                              �жϱ�־���ָʾ������Ч���������INT_TYPE_GS_INT012[2:0]��Ӧbitλ
                                                              ��Чʱ�̣�������Ч */
        unsigned int  reserved            : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_GS_INT012_UNION;
#define BBPCOMM_INT_CLEAR_GS_INT012_int_clear_gs_int012_START  (0)
#define BBPCOMM_INT_CLEAR_GS_INT012_int_clear_gs_int012_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_GS_RCV_LTE_UNION
 �ṹ˵��  : INT_MASK_GS_RCV_LTE �Ĵ����ṹ���塣��ַƫ����:0x08A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_gs_rcv_lte_reg;
    struct
    {
        unsigned int  int_mask_gs_rcv_lte : 16; /* bit[0-15] : �ж����α�־����������INT_TYPE_GS_RCV_LTE[15:0]��Ӧbit�жϡ�
                                                               0�������ж��ϱ���
                                                               1��ʹ���ж��ϱ���
                                                               ����ʱ�̣���ʼ��
                                                               ��Чʱ�̣�������Ч */
        unsigned int  reserved            : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_GS_RCV_LTE_UNION;
#define BBPCOMM_INT_MASK_GS_RCV_LTE_int_mask_gs_rcv_lte_START  (0)
#define BBPCOMM_INT_MASK_GS_RCV_LTE_int_mask_gs_rcv_lte_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_GS_RCV_TDS_UNION
 �ṹ˵��  : INT_MASK_GS_RCV_TDS �Ĵ����ṹ���塣��ַƫ����:0x08A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_gs_rcv_tds_reg;
    struct
    {
        unsigned int  int_mask_gs_rcv_tds : 16; /* bit[0-15] : �ж����α�־����������INT_TYPE_GS_RCV_TDS[15:0]��Ӧbit�жϡ�
                                                               0�������ж��ϱ���
                                                               1��ʹ���ж��ϱ���
                                                               ����ʱ�̣���ʼ��
                                                               ��Чʱ�̣�������Ч */
        unsigned int  reserved            : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_GS_RCV_TDS_UNION;
#define BBPCOMM_INT_MASK_GS_RCV_TDS_int_mask_gs_rcv_tds_START  (0)
#define BBPCOMM_INT_MASK_GS_RCV_TDS_int_mask_gs_rcv_tds_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_GS_RCV_GM_UNION
 �ṹ˵��  : INT_MASK_GS_RCV_GM �Ĵ����ṹ���塣��ַƫ����:0x08A8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_gs_rcv_gm_reg;
    struct
    {
        unsigned int  int_mask_gs_rcv_gm : 16; /* bit[0-15] : �ж����α�־����������INT_TYPE_GS_RCV_GM[15:0]��Ӧbit�жϡ�
                                                              0�������ж��ϱ���
                                                              1��ʹ���ж��ϱ���
                                                              ����ʱ�̣���ʼ��
                                                              ��Чʱ�̣�������Ч */
        unsigned int  reserved           : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_GS_RCV_GM_UNION;
#define BBPCOMM_INT_MASK_GS_RCV_GM_int_mask_gs_rcv_gm_START  (0)
#define BBPCOMM_INT_MASK_GS_RCV_GM_int_mask_gs_rcv_gm_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_GS_RCV_GS_UNION
 �ṹ˵��  : INT_MASK_GS_RCV_GS �Ĵ����ṹ���塣��ַƫ����:0x08AC����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_gs_rcv_gs_reg;
    struct
    {
        unsigned int  int_mask_gs_rcv_gs : 16; /* bit[0-15] : �ж����α�־����������INT_TYPE_GS_RCV_GS[15:0]��Ӧbit�жϡ�
                                                              0�������ж��ϱ���
                                                              1��ʹ���ж��ϱ���
                                                              ����ʱ�̣���ʼ��
                                                              ��Чʱ�̣�������Ч */
        unsigned int  reserved           : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_GS_RCV_GS_UNION;
#define BBPCOMM_INT_MASK_GS_RCV_GS_int_mask_gs_rcv_gs_START  (0)
#define BBPCOMM_INT_MASK_GS_RCV_GS_int_mask_gs_rcv_gs_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_GS_RCV_W_UNION
 �ṹ˵��  : INT_MASK_GS_RCV_W �Ĵ����ṹ���塣��ַƫ����:0x08B0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_gs_rcv_w_reg;
    struct
    {
        unsigned int  int_mask_gs_rcv_w : 16; /* bit[0-15] : �ж����α�־����������INT_TYPE_GS_RCV_W[15:0]��Ӧbit�жϡ�
                                                             0�������ж��ϱ���
                                                             1��ʹ���ж��ϱ���
                                                             ����ʱ�̣���ʼ��
                                                             ��Чʱ�̣�������Ч */
        unsigned int  reserved          : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_GS_RCV_W_UNION;
#define BBPCOMM_INT_MASK_GS_RCV_W_int_mask_gs_rcv_w_START  (0)
#define BBPCOMM_INT_MASK_GS_RCV_W_int_mask_gs_rcv_w_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_GS_INT012_UNION
 �ṹ˵��  : INT_MASK_GS_INT012 �Ĵ����ṹ���塣��ַƫ����:0x08B4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_gs_int012_reg;
    struct
    {
        unsigned int  int_mask_gs_int012 : 3;  /* bit[0-2] : �ж����α�־����������INT_TYPE_GS_INT012[2:0]��Ӧbit�жϡ�
                                                             0�������ж��ϱ���
                                                             1��ʹ���ж��ϱ���
                                                             ����ʱ�̣���ʼ��
                                                             ��Чʱ�̣�������Ч */
        unsigned int  reserved           : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_GS_INT012_UNION;
#define BBPCOMM_INT_MASK_GS_INT012_int_mask_gs_int012_START  (0)
#define BBPCOMM_INT_MASK_GS_INT012_int_mask_gs_int012_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_GS_RCV_LTE_UNION
 �ṹ˵��  : INT_TYPE_GS_RCV_LTE �Ĵ����ṹ���塣��ַƫ����:0x08B8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_gs_rcv_lte_reg;
    struct
    {
        unsigned int  o_int_type_gs_rcv_lte : 16; /* bit[0-15] : �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
                                                                 [0]: �ж�����0�� LTE����ģ����ǰ֪ͨGS��ϵͳ���������жϡ�
                                                                 [1]: �ж�����1�� LTE����ģ����GAP�жϣ�֪ͨGS������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
                                                                 [2]: �ж�����2�� LTE����ģ����GAP�жϡ�
                                                                 [3]: �ж�����3��LTE����ģ�����������жϡ�
                                                                 [4]: �ж�����4��LTE����ģ��ǿ��GS�˳���ϵͳ�����жϡ�
                                                                 [5]: �ж�����5��LTE����ģ��֪ͨGS�ϱ����β��������
                                                                 [6]: ������
                                                                 [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
                                                                 �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x08A0��int_mask_gs_rcv_lte���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved              : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_GS_RCV_LTE_UNION;
#define BBPCOMM_INT_TYPE_GS_RCV_LTE_o_int_type_gs_rcv_lte_START  (0)
#define BBPCOMM_INT_TYPE_GS_RCV_LTE_o_int_type_gs_rcv_lte_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_GS_RCV_TDS_UNION
 �ṹ˵��  : INT_TYPE_GS_RCV_TDS �Ĵ����ṹ���塣��ַƫ����:0x08BC����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_gs_rcv_tds_reg;
    struct
    {
        unsigned int  o_int_type_gs_rcv_tds : 16; /* bit[0-15] : �ж�״̬��־0��1��2ֻ�е�TDS������ģʱ���ܲ�����
                                                                 
                                                                 [0]: �ж�����0�� TDS����ģ����ǰ֪ͨGS��ϵͳ���������жϡ�
                                                                 [1]: �ж�����1�� TDS����ģ����GAP�жϣ�֪ͨGS������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
                                                                 [2]: �ж�����2�� TDS����ģ����GAP�жϡ�
                                                                 [3]: �ж�����3��TDS����ģ�����������жϡ�
                                                                 [4]: �ж�����4��TDS����ģ��ǿ��GS�˳���ϵͳ�����жϡ�
                                                                 [5]: �ж�����5��TDS����ģ��֪ͨGS�ϱ����β��������
                                                                 [6]: �ж�����6��������
                                                                 [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
                                                                 �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x08A4��int_mask_gs_rcv_tds���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved              : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_GS_RCV_TDS_UNION;
#define BBPCOMM_INT_TYPE_GS_RCV_TDS_o_int_type_gs_rcv_tds_START  (0)
#define BBPCOMM_INT_TYPE_GS_RCV_TDS_o_int_type_gs_rcv_tds_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_GS_RCV_GM_UNION
 �ṹ˵��  : INT_TYPE_GS_RCV_GM �Ĵ����ṹ���塣��ַƫ����:0x08C0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_gs_rcv_gm_reg;
    struct
    {
        unsigned int  o_int_type_gs_rcv_gm : 16; /* bit[0-15] : �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
                                                                [0]: �ж�����0��GM����ģ����ǰ֪ͨGS��ϵͳ���������жϡ�
                                                                [1]: �ж�����1��GM����ģ����GAP�жϣ�֪ͨGS������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
                                                                [2]: �ж�����2��GM����ģ����GAP�жϡ�
                                                                [3]: �ж�����3��GM����ģ�����������жϡ�
                                                                [4]: �ж�����4��GM����ģ��ǿ��GS�˳���ϵͳ�����жϡ�
                                                                [5]: �ж�����5��GM����ģ��֪ͨGS�ϱ����β��������
                                                                [6]: �ж�����6��������
                                                                [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
                                                                �ж�״̬��־0��1��2ֻ�е�GM������ģʱ���ܲ�����
                                                                �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x08A8��int_mask_gs_rcv_gm���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved             : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_GS_RCV_GM_UNION;
#define BBPCOMM_INT_TYPE_GS_RCV_GM_o_int_type_gs_rcv_gm_START  (0)
#define BBPCOMM_INT_TYPE_GS_RCV_GM_o_int_type_gs_rcv_gm_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_GS_RCV_GS_UNION
 �ṹ˵��  : INT_TYPE_GS_RCV_GS �Ĵ����ṹ���塣��ַƫ����:0x08C4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_gs_rcv_gs_reg;
    struct
    {
        unsigned int  o_int_type_gs_rcv_gs : 16; /* bit[0-15] : [0]: �ж�����0��GS����ģ����ǰ֪ͨGS��ϵͳ���������жϡ�
                                                                [1]: �ж�����1��GS����ģ����GAP�жϣ�֪ͨGS������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
                                                                [2]: �ж�����2��GS����ģ����GAP�жϡ�
                                                                [3]: �ж�����3��GS����ģ�����������жϡ�
                                                                [4]: �ж�����4��GS����ģ��ǿ��GS�˳���ϵͳ�����жϡ�
                                                                [5]: �ж�����5��GS����ģ��֪ͨGS�ϱ����β��������
                                                                [6]: �ж�����6��������
                                                                [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
                                                                �ж�״̬��־0��1��2ֻ�е�TDS������ģʱ���ܲ�����
                                                                �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x08AC��int_mask_gs_rcv_gs���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved             : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_GS_RCV_GS_UNION;
#define BBPCOMM_INT_TYPE_GS_RCV_GS_o_int_type_gs_rcv_gs_START  (0)
#define BBPCOMM_INT_TYPE_GS_RCV_GS_o_int_type_gs_rcv_gs_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_GS_RCV_W_UNION
 �ṹ˵��  : INT_TYPE_GS_RCV_W �Ĵ����ṹ���塣��ַƫ����:0x08C8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_gs_rcv_w_reg;
    struct
    {
        unsigned int  o_int_type_gs_rcv_w : 16; /* bit[0-15] : �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
                                                               [0]: �ж�����0��W����ģ����ǰ֪ͨGS��Ƶ���������жϡ�
                                                               [1]: �ж�����1��W����ģ����GAP�жϣ�֪ͨGS������Ƶ������Ƶͨ�����ã������л��Ȳ�����
                                                               [2]: �ж�����2��W����ģ����GAP�жϡ�
                                                               [3]: �ж�����3��W����ģ������Ƶ�����������жϡ�
                                                               [4]: �ж�����4��W����ģ��ǿ��GS�˳���Ƶ�����жϡ�
                                                               [5]: �ж�����5��W����ģ��֪ͨGS�ϱ����β��������
                                                               [6]: �ж�����6��������
                                                               [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
                                                               �ж�״̬��־0��1��2ֻ�е�W������ģʱ���ܲ�����
                                                               �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x08B0��int_mask_gs_rcv_w���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved            : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_GS_RCV_W_UNION;
#define BBPCOMM_INT_TYPE_GS_RCV_W_o_int_type_gs_rcv_w_START  (0)
#define BBPCOMM_INT_TYPE_GS_RCV_W_o_int_type_gs_rcv_w_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_GS_INT012_UNION
 �ṹ˵��  : INT_TYPE_GS_INT012 �Ĵ����ṹ���塣��ַƫ����:0x08CC����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_gs_int012_reg;
    struct
    {
        unsigned int  o_int_type_gs_int012 : 3;  /* bit[0-2] : ��ģ����int0��1��2���ϱ���(������Ƶ����ϵͳ����)��������Ч��
                                                               [0]: GS��ģʱ��CTU����֪ͨGSDSP����int0�жϡ�
                                                               [1]: GS��ģʱ��CTU����֪ͨGSDSP����int1�жϡ�
                                                               [2]: GS��ģʱ��CTU����֪ͨGSDSP����int2�жϡ�
                                                               �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x08B4��int_mask_gs_int012���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved             : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_GS_INT012_UNION;
#define BBPCOMM_INT_TYPE_GS_INT012_o_int_type_gs_int012_START  (0)
#define BBPCOMM_INT_TYPE_GS_INT012_o_int_type_gs_int012_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GS_SND_LTE_INT_13_UNION
 �ṹ˵��  : GS_SND_LTE_INT_13 �Ĵ����ṹ���塣��ַƫ����:0x08D0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gs_snd_lte_int_13_reg;
    struct
    {
        unsigned int  reserved_0        : 3;  /* bit[0-2]  : ���� */
        unsigned int  gs_snd_lte_int_13 : 13; /* bit[3-15] : �߼������㡣����Ч��
                                                             
                                                             bit15~7����Ӧgs_snd_lte_int_15 ~ 7��
                                                             GS DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_lte_rcv_gs[15:7]����LTEDSP��
                                                             ��Чʱ�̣�������Ч
                                                             
                                                             bit6����Ӧgs_snd_lte_int_6��
                                                             GSDSPͨ���˼Ĵ�����������6�жϣ�int_type_lte_rcv_gs[6]����LTEDSP��
                                                             ��Чʱ�̣�������Ч
                                                             
                                                             bit5����Ӧgs_snd_lte_int_5��
                                                             GS��ģʱ֪ͨLTEDSP LTE�������ڵ������Ч��
                                                             GS DSPͨ���˼Ĵ�����������5�жϣ�int_type_lte_rcv_gs[5]����LTEDSP��
                                                             ��Чʱ�̣�������Ч
                                                             
                                                             bit4����Ӧgs_snd_lte_int_4��
                                                             GS��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
                                                             GS DSPͨ���˼Ĵ�����������4�жϣ�int_type_lte_rcv_gs[4]����LTEDSP��
                                                             ��Чʱ�̣�������Ч
                                                             
                                                             bit3����Ӧgs_snd_lte_int_3��GS��������ָʾ������Ч��
                                                             ���ڴ����ж�����3 ��int_type_lte_rcv_gs[3]����LTEDSP��LTE��ģ�¶�GS������ϵͳ����ʱ�����GS����������GS DSP���ô˱�־Ϊ1�� 
                                                             ��Чʱ�̣�������Ч */
        unsigned int  reserved_1        : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_GS_SND_LTE_INT_13_UNION;
#define BBPCOMM_GS_SND_LTE_INT_13_gs_snd_lte_int_13_START  (3)
#define BBPCOMM_GS_SND_LTE_INT_13_gs_snd_lte_int_13_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GS_SND_TDS_INT_13_UNION
 �ṹ˵��  : GS_SND_TDS_INT_13 �Ĵ����ṹ���塣��ַƫ����:0x08D4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gs_snd_tds_int_13_reg;
    struct
    {
        unsigned int  reserved_0        : 3;  /* bit[0-2]  : ���� */
        unsigned int  gs_snd_tds_int_13 : 13; /* bit[3-15] : �߼������㡣����Ч��
                                                             
                                                             bit15~7����Ӧgs_snd_tds_int_15 ~ 7��
                                                             GS DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_tds_rcv_gs[15:7]����TDSDSP��
                                                             ��Чʱ�̣�������Ч
                                                             
                                                             bit6����Ӧgs_snd_tds_int_6��
                                                             GSDSPͨ���˼Ĵ�����������6�жϣ�int_type_tds_rcv_gs[6]����TDSDSP��
                                                             ��Чʱ�̣�������Ч
                                                             
                                                             bit5����Ӧgs_snd_tds_int_5��
                                                             GS��ģʱ֪ͨTDSDSP TDS�������ڵ������Ч��
                                                             GS DSPͨ���˼Ĵ�����������5�жϣ�int_type_tds_rcv_gs[5]����TDSDSP��
                                                             ��Чʱ�̣�������Ч
                                                             
                                                             bit4����Ӧgs_snd_tds_int_4��
                                                             GS��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
                                                             GS DSPͨ���˼Ĵ�����������4�жϣ�int_type_tds_rcv_gs[4]����TDSDSP��
                                                             ��Чʱ�̣�������Ч
                                                             
                                                             bit3����Ӧgs_snd_tds_int_3��GS��������ָʾ������Ч��
                                                             ���ڴ����ж�����3 ��int_type_tds_rcv_gs[3]����TDSDSP��TDS��ģ�¶�GS������ϵͳ����ʱ�����GS����������GS DSP���ô˱�־Ϊ1�� 
                                                             ��Чʱ�̣�������Ч */
        unsigned int  reserved_1        : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_GS_SND_TDS_INT_13_UNION;
#define BBPCOMM_GS_SND_TDS_INT_13_gs_snd_tds_int_13_START  (3)
#define BBPCOMM_GS_SND_TDS_INT_13_gs_snd_tds_int_13_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GS_SND_GM_INT_13_UNION
 �ṹ˵��  : GS_SND_GM_INT_13 �Ĵ����ṹ���塣��ַƫ����:0x08D8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gs_snd_gm_int_13_reg;
    struct
    {
        unsigned int  reserved_0       : 3;  /* bit[0-2]  : ���� */
        unsigned int  gs_snd_gm_int_13 : 13; /* bit[3-15] : �߼������㡣����Ч��
                                                            
                                                            bit15~7����Ӧgs_snd_gm_int_15 ~ 7��
                                                            GS DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_gm_rcv_gs[15:7]����GMDSP��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit6����Ӧgs_snd_gm_int_6��
                                                            GSDSPͨ���˼Ĵ�����������6�жϣ�int_type_gm_rcv_gs[6]����GMDSP��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit5����Ӧgs_snd_gm_int_5��
                                                            GS��ģʱ֪ͨGMDSP GM�������ڵ������Ч��
                                                            GS DSPͨ���˼Ĵ�����������5�жϣ�int_type_gm_rcv_gs[5]����GMDSP��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit4����Ӧgs_snd_gm_int_4��
                                                            GS��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
                                                            GS DSPͨ���˼Ĵ�����������4�жϣ�int_type_gm_rcv_gs[4]����GMDSP��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit3����Ӧgs_snd_gm_int_3��GS��������ָʾ������Ч��
                                                            ���ڴ����ж�����3 ��int_type_gm_rcv_gs[3]����GMDSP��GM��ģ�¶�GS������ϵͳ����ʱ�����GS����������GS DSP���ô˱�־Ϊ1�� 
                                                            ��Чʱ�̣�������Ч */
        unsigned int  reserved_1       : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_GS_SND_GM_INT_13_UNION;
#define BBPCOMM_GS_SND_GM_INT_13_gs_snd_gm_int_13_START  (3)
#define BBPCOMM_GS_SND_GM_INT_13_gs_snd_gm_int_13_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GS_SND_GS_INT_13_UNION
 �ṹ˵��  : GS_SND_GS_INT_13 �Ĵ����ṹ���塣��ַƫ����:0x08DC����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gs_snd_gs_int_13_reg;
    struct
    {
        unsigned int  reserved_0       : 3;  /* bit[0-2]  : ���� */
        unsigned int  gs_snd_gs_int_13 : 13; /* bit[3-15] : �߼������㡣����Ч��
                                                            
                                                            bit15~7����Ӧgs_snd_gs_int_15 ~ 7��
                                                            GS DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_gs_rcv_gs[15:7]����GSDSP��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit6����Ӧgs_snd_gs_int_6��
                                                            GSDSPͨ���˼Ĵ�����������6�жϣ�int_type_gs_rcv_gs[6]����GSDSP��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit5����Ӧgs_snd_gs_int_5��
                                                            GS��ģʱ֪ͨGSDSP GS�������ڵ������Ч��
                                                            GS DSPͨ���˼Ĵ�����������5�жϣ�int_type_gs_rcv_gs[5]����GSDSP��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit4����Ӧgs_snd_gs_int_4��
                                                            GS��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
                                                            GS DSPͨ���˼Ĵ�����������4�жϣ�int_type_gs_rcv_gs[4]����GSDSP��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit3����Ӧgs_snd_gs_int_3��GS��������ָʾ������Ч��
                                                            ���ڴ����ж�����3 ��int_type_gs_rcv_gs[3]����GSDSP��GS��ģ�¶�GS������ϵͳ����ʱ�����GS����������GS DSP���ô˱�־Ϊ1�� 
                                                            ��Чʱ�̣�������Ч */
        unsigned int  reserved_1       : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_GS_SND_GS_INT_13_UNION;
#define BBPCOMM_GS_SND_GS_INT_13_gs_snd_gs_int_13_START  (3)
#define BBPCOMM_GS_SND_GS_INT_13_gs_snd_gs_int_13_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GS_SND_W_INT_13_UNION
 �ṹ˵��  : GS_SND_W_INT_13 �Ĵ����ṹ���塣��ַƫ����:0x08E0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gs_snd_w_int_13_reg;
    struct
    {
        unsigned int  reserved_0      : 3;  /* bit[0-2]  : ���� */
        unsigned int  gs_snd_w_int_13 : 13; /* bit[3-15] : �߼������㡣����Ч��
                                                           
                                                           bit15~7����Ӧgs_snd_w_int_15 ~ 7��
                                                           GS DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_w_rcv_gs[15:7]����WDSP��
                                                           ��Чʱ�̣�������Ч
                                                           
                                                           bit6����Ӧgs_snd_w_int_6��
                                                           GSDSPͨ���˼Ĵ�����������6�жϣ�int_type_w_rcv_gs[6]����WDSP��
                                                           ��Чʱ�̣�������Ч
                                                           
                                                           bit5����Ӧgs_snd_w_int_5��
                                                           GS��ģʱ֪ͨWDSP W�������ڵ������Ч��
                                                           GS DSPͨ���˼Ĵ�����������5�жϣ�int_type_w_rcv_gs[5]����WDSP��
                                                           ��Чʱ�̣�������Ч
                                                           
                                                           bit4����Ӧgs_snd_w_int_4��
                                                           GS��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
                                                           GS DSPͨ���˼Ĵ�����������4�жϣ�int_type_w_rcv_gs[4]����WDSP��
                                                           ��Чʱ�̣�������Ч
                                                           
                                                           bit3����Ӧgs_snd_w_int_3��GS��������ָʾ������Ч��
                                                           ���ڴ����ж�����3 ��int_type_w_rcv_gs[3]����WDSP��W��ģ�¶�GS������ϵͳ����ʱ�����GS����������GS DSP���ô˱�־Ϊ1�� 
                                                           ��Чʱ�̣�������Ч */
        unsigned int  reserved_1      : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_GS_SND_W_INT_13_UNION;
#define BBPCOMM_GS_SND_W_INT_13_gs_snd_w_int_13_START  (3)
#define BBPCOMM_GS_SND_W_INT_13_gs_snd_w_int_13_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GBBP1_19M_SEL_UNION
 �ṹ˵��  : GBBP1_19M_SEL �Ĵ����ṹ���塣��ַƫ����:0x08E4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gbbp1_19m_sel_reg;
    struct
    {
        unsigned int  gbbp1_19m_sel : 2;  /* bit[0-1] : V9R1�汾����������á� */
        unsigned int  reserved      : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_GBBP1_19M_SEL_UNION;
#define BBPCOMM_GBBP1_19M_SEL_gbbp1_19m_sel_START  (0)
#define BBPCOMM_GBBP1_19M_SEL_gbbp1_19m_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GBBP2_19M_SEL_UNION
 �ṹ˵��  : GBBP2_19M_SEL �Ĵ����ṹ���塣��ַƫ����:0x08E8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gbbp2_19m_sel_reg;
    struct
    {
        unsigned int  gbbp2_19m_sel : 2;  /* bit[0-1] : V9R1�汾����������á� */
        unsigned int  reserved      : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_GBBP2_19M_SEL_UNION;
#define BBPCOMM_GBBP2_19M_SEL_gbbp2_19m_sel_START  (0)
#define BBPCOMM_GBBP2_19M_SEL_gbbp2_19m_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_WBBP_19M_SEL_UNION
 �ṹ˵��  : WBBP_19M_SEL �Ĵ����ṹ���塣��ַƫ����:0x08EC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      wbbp_19m_sel_reg;
    struct
    {
        unsigned int  wbbp_19m_sel : 2;  /* bit[0-1] : V9R1�汾����������á� */
        unsigned int  reserved     : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_WBBP_19M_SEL_UNION;
#define BBPCOMM_WBBP_19M_SEL_wbbp_19m_sel_START  (0)
#define BBPCOMM_WBBP_19M_SEL_wbbp_19m_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_LBBP_19M_SEL_UNION
 �ṹ˵��  : LBBP_19M_SEL �Ĵ����ṹ���塣��ַƫ����:0x08F0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      lbbp_19m_sel_reg;
    struct
    {
        unsigned int  lbbp_19m_sel : 2;  /* bit[0-1] : V9R1�汾����������á� */
        unsigned int  reserved     : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_LBBP_19M_SEL_UNION;
#define BBPCOMM_LBBP_19M_SEL_lbbp_19m_sel_START  (0)
#define BBPCOMM_LBBP_19M_SEL_lbbp_19m_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TBBP1_19M_SEL_UNION
 �ṹ˵��  : TBBP1_19M_SEL �Ĵ����ṹ���塣��ַƫ����:0x08F4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      tbbp1_19m_sel_reg;
    struct
    {
        unsigned int  tbbp_19m_sel : 2;  /* bit[0-1] : V9R1�汾����������á� */
        unsigned int  reserved     : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_TBBP1_19M_SEL_UNION;
#define BBPCOMM_TBBP1_19M_SEL_tbbp_19m_sel_START  (0)
#define BBPCOMM_TBBP1_19M_SEL_tbbp_19m_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GBBP1_CLK_SEL_UNION
 �ṹ˵��  : GBBP1_CLK_SEL �Ĵ����ṹ���塣��ַƫ����:0x08F8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gbbp1_clk_sel_reg;
    struct
    {
        unsigned int  gbbp1_clk_sel : 2;  /* bit[0-1] : V9R1�汾����������á� */
        unsigned int  reserved      : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_GBBP1_CLK_SEL_UNION;
#define BBPCOMM_GBBP1_CLK_SEL_gbbp1_clk_sel_START  (0)
#define BBPCOMM_GBBP1_CLK_SEL_gbbp1_clk_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GBBP2_CLK_SEL_UNION
 �ṹ˵��  : GBBP2_CLK_SEL �Ĵ����ṹ���塣��ַƫ����:0x08FC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gbbp2_clk_sel_reg;
    struct
    {
        unsigned int  gbbp2_clk_sel : 2;  /* bit[0-1] : V9R1�汾����������á� */
        unsigned int  reserved      : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_GBBP2_CLK_SEL_UNION;
#define BBPCOMM_GBBP2_CLK_SEL_gbbp2_clk_sel_START  (0)
#define BBPCOMM_GBBP2_CLK_SEL_gbbp2_clk_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_WBBP_CLK_SEL_UNION
 �ṹ˵��  : WBBP_CLK_SEL �Ĵ����ṹ���塣��ַƫ����:0x0900����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      wbbp_clk_sel_reg;
    struct
    {
        unsigned int  wbbp_clk_sel : 2;  /* bit[0-1] : V9R1�汾����������á� */
        unsigned int  reserved     : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_WBBP_CLK_SEL_UNION;
#define BBPCOMM_WBBP_CLK_SEL_wbbp_clk_sel_START  (0)
#define BBPCOMM_WBBP_CLK_SEL_wbbp_clk_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_LBBP_CLK_SEL_UNION
 �ṹ˵��  : LBBP_CLK_SEL �Ĵ����ṹ���塣��ַƫ����:0x0904����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      lbbp_clk_sel_reg;
    struct
    {
        unsigned int  lbbp_clk_sel : 2;  /* bit[0-1] : V9R1�汾����������á� */
        unsigned int  reserved     : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_LBBP_CLK_SEL_UNION;
#define BBPCOMM_LBBP_CLK_SEL_lbbp_clk_sel_START  (0)
#define BBPCOMM_LBBP_CLK_SEL_lbbp_clk_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TBBP_CLK_SEL_UNION
 �ṹ˵��  : TBBP_CLK_SEL �Ĵ����ṹ���塣��ַƫ����:0x0908����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      tbbp_clk_sel_reg;
    struct
    {
        unsigned int  tbbp_clk_sel : 2;  /* bit[0-1] : V9R1�汾����������á� */
        unsigned int  reserved     : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_TBBP_CLK_SEL_UNION;
#define BBPCOMM_TBBP_CLK_SEL_tbbp_clk_sel_START  (0)
#define BBPCOMM_TBBP_CLK_SEL_tbbp_clk_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_LTE_ABBIF_FMT_UNION
 �ṹ˵��  : LTE_ABBIF_FMT �Ĵ����ṹ���塣��ַƫ����:0x090C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      lte_abbif_fmt_reg;
    struct
    {
        unsigned int  reserved_0          : 1;  /* bit[0-0]  : ���� */
        unsigned int  lte_rxb_iq_exchange : 1;  /* bit[1-1]  : 1'b1��LTE��RXBͨ·IQ·���ݽ���
                                                               1'b0��LTE��RXBͨ·IQ·���ݲ�����
                                                               V3R3��֧��IQ�������ܡ� */
        unsigned int  lte_rxb_q_inv       : 1;  /* bit[2-2]  : 1'b1��LTE��RXBͨ·Q·����ȡ��
                                                               1'b0��LTE��RXBͨ·Q·���ݲ�ȡ�� */
        unsigned int  lte_rxb_i_inv       : 1;  /* bit[3-3]  : 1'b1��LTE��RXBͨ·I·����ȡ��
                                                               1'b0��LTE��RXBͨ·I·���ݲ�ȡ�� */
        unsigned int  lte_rxa_iq_exchange : 1;  /* bit[4-4]  : 1'b1��LTE��RXAͨ·IQ·���ݽ���
                                                               1'b0��LTE��RXAͨ·IQ·���ݲ�����
                                                               V3R3��֧��IQ�������ܡ� */
        unsigned int  lte_rxa_q_inv       : 1;  /* bit[5-5]  : 1'b1��LTE��RXAͨ·Q·����ȡ��
                                                               1'b0��LTE��RXAͨ·Q·���ݲ�ȡ�� */
        unsigned int  lte_rxa_i_inv       : 1;  /* bit[6-6]  : 1'b1��LTE��RXAͨ·I·����ȡ��
                                                               1'b0��LTE��RXAͨ·I·���ݲ�ȡ�� */
        unsigned int  lte_tx_iq_exchange  : 1;  /* bit[7-7]  : 1'b1��LTE��TXͨ·IQ·���ݽ���
                                                               1'b0��LTE��TXͨ·IQ·���ݲ�����
                                                               V3R3��֧��IQ�������ܡ� */
        unsigned int  lte_tx_q_inv        : 1;  /* bit[8-8]  : 1'b1��LTE��TXͨ·Q·����ȡ��
                                                               1'b0��LTE��TXͨ·Q·���ݲ�ȡ�� */
        unsigned int  lte_tx_i_inv        : 1;  /* bit[9-9]  : 1'b1��LTE��TXͨ·I·����ȡ��
                                                               1'b0��LTE��TXͨ·I·���ݲ�ȡ�� */
        unsigned int  reserved_1          : 22; /* bit[10-31]: ���� */
    } reg;
} BBPCOMM_LTE_ABBIF_FMT_UNION;
#define BBPCOMM_LTE_ABBIF_FMT_lte_rxb_iq_exchange_START  (1)
#define BBPCOMM_LTE_ABBIF_FMT_lte_rxb_iq_exchange_END    (1)
#define BBPCOMM_LTE_ABBIF_FMT_lte_rxb_q_inv_START        (2)
#define BBPCOMM_LTE_ABBIF_FMT_lte_rxb_q_inv_END          (2)
#define BBPCOMM_LTE_ABBIF_FMT_lte_rxb_i_inv_START        (3)
#define BBPCOMM_LTE_ABBIF_FMT_lte_rxb_i_inv_END          (3)
#define BBPCOMM_LTE_ABBIF_FMT_lte_rxa_iq_exchange_START  (4)
#define BBPCOMM_LTE_ABBIF_FMT_lte_rxa_iq_exchange_END    (4)
#define BBPCOMM_LTE_ABBIF_FMT_lte_rxa_q_inv_START        (5)
#define BBPCOMM_LTE_ABBIF_FMT_lte_rxa_q_inv_END          (5)
#define BBPCOMM_LTE_ABBIF_FMT_lte_rxa_i_inv_START        (6)
#define BBPCOMM_LTE_ABBIF_FMT_lte_rxa_i_inv_END          (6)
#define BBPCOMM_LTE_ABBIF_FMT_lte_tx_iq_exchange_START   (7)
#define BBPCOMM_LTE_ABBIF_FMT_lte_tx_iq_exchange_END     (7)
#define BBPCOMM_LTE_ABBIF_FMT_lte_tx_q_inv_START         (8)
#define BBPCOMM_LTE_ABBIF_FMT_lte_tx_q_inv_END           (8)
#define BBPCOMM_LTE_ABBIF_FMT_lte_tx_i_inv_START         (9)
#define BBPCOMM_LTE_ABBIF_FMT_lte_tx_i_inv_END           (9)


/*****************************************************************************
 �ṹ��    : BBPCOMM_W_ABBIF_FMT_UNION
 �ṹ˵��  : W_ABBIF_FMT �Ĵ����ṹ���塣��ַƫ����:0x0910����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      w_abbif_fmt_reg;
    struct
    {
        unsigned int  reserved_0        : 1;  /* bit[0-0]  : ���� */
        unsigned int  w_rxb_iq_exchange : 1;  /* bit[1-1]  : 1'b1��W��RXBͨ·IQ·���ݽ���
                                                             1'b0��W��RXBͨ·IQ·���ݲ�����
                                                             V3R3��֧��IQ�������ܡ� */
        unsigned int  w_rxb_q_inv       : 1;  /* bit[2-2]  : 1'b1��W��RXBͨ·Q·����ȡ��
                                                             1'b0��W��RXBͨ·Q·���ݲ�ȡ�� */
        unsigned int  w_rxb_i_inv       : 1;  /* bit[3-3]  : 1'b1��W��RXBͨ·I·����ȡ��
                                                             1'b0��W��RXBͨ·I·���ݲ�ȡ�� */
        unsigned int  w_rxa_iq_exchange : 1;  /* bit[4-4]  : 1'b1��W��RXAͨ·IQ·���ݽ���
                                                             1'b0��W��RXAͨ·IQ·���ݲ�����
                                                             V3R3��֧��IQ�������ܡ� */
        unsigned int  w_rxa_q_inv       : 1;  /* bit[5-5]  : 1'b1��W��RXAͨ·Q·����ȡ��
                                                             1'b0��W��RXAͨ·Q·���ݲ�ȡ�� */
        unsigned int  w_rxa_i_inv       : 1;  /* bit[6-6]  : 1'b1��W��RXAͨ·I·����ȡ��
                                                             1'b0��W��RXAͨ·I·���ݲ�ȡ�� */
        unsigned int  w_tx_iq_exchange  : 1;  /* bit[7-7]  : 1'b1��W��TXͨ·IQ·���ݽ���
                                                             1'b0��W��TXͨ·IQ·���ݲ�����
                                                             V3R3��֧��IQ�������ܡ� */
        unsigned int  w_tx_q_inv        : 1;  /* bit[8-8]  : 1'b1��W��TXͨ·Q·����ȡ��
                                                             1'b0��W��TXͨ·Q·���ݲ�ȡ�� */
        unsigned int  w_tx_i_inv        : 1;  /* bit[9-9]  : 1'b1��W��TXͨ·I·����ȡ��
                                                             1'b0��W��TXͨ·I·���ݲ�ȡ���� */
        unsigned int  reserved_1        : 22; /* bit[10-31]: ���� */
    } reg;
} BBPCOMM_W_ABBIF_FMT_UNION;
#define BBPCOMM_W_ABBIF_FMT_w_rxb_iq_exchange_START  (1)
#define BBPCOMM_W_ABBIF_FMT_w_rxb_iq_exchange_END    (1)
#define BBPCOMM_W_ABBIF_FMT_w_rxb_q_inv_START        (2)
#define BBPCOMM_W_ABBIF_FMT_w_rxb_q_inv_END          (2)
#define BBPCOMM_W_ABBIF_FMT_w_rxb_i_inv_START        (3)
#define BBPCOMM_W_ABBIF_FMT_w_rxb_i_inv_END          (3)
#define BBPCOMM_W_ABBIF_FMT_w_rxa_iq_exchange_START  (4)
#define BBPCOMM_W_ABBIF_FMT_w_rxa_iq_exchange_END    (4)
#define BBPCOMM_W_ABBIF_FMT_w_rxa_q_inv_START        (5)
#define BBPCOMM_W_ABBIF_FMT_w_rxa_q_inv_END          (5)
#define BBPCOMM_W_ABBIF_FMT_w_rxa_i_inv_START        (6)
#define BBPCOMM_W_ABBIF_FMT_w_rxa_i_inv_END          (6)
#define BBPCOMM_W_ABBIF_FMT_w_tx_iq_exchange_START   (7)
#define BBPCOMM_W_ABBIF_FMT_w_tx_iq_exchange_END     (7)
#define BBPCOMM_W_ABBIF_FMT_w_tx_q_inv_START         (8)
#define BBPCOMM_W_ABBIF_FMT_w_tx_q_inv_END           (8)
#define BBPCOMM_W_ABBIF_FMT_w_tx_i_inv_START         (9)
#define BBPCOMM_W_ABBIF_FMT_w_tx_i_inv_END           (9)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TDS_ABBIF_FMT_UNION
 �ṹ˵��  : TDS_ABBIF_FMT �Ĵ����ṹ���塣��ַƫ����:0x0914����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      tds_abbif_fmt_reg;
    struct
    {
        unsigned int  reserved_0          : 1;  /* bit[0-0]  : ���� */
        unsigned int  tds_rxb_iq_exchange : 1;  /* bit[1-1]  : 1'b1��TDS��RXBͨ·IQ·���ݽ���
                                                               1'b0��TDS��RXBͨ·IQ·���ݲ�����
                                                               V3R3��֧��IQ�������ܡ� */
        unsigned int  tds_rxb_q_inv       : 1;  /* bit[2-2]  : 1'b1��TDS��RXBͨ·Q·����ȡ��
                                                               1'b0��TDS��RXBͨ·Q·���ݲ�ȡ�� */
        unsigned int  tds_rxb_i_inv       : 1;  /* bit[3-3]  : 1'b1��TDS��RXBͨ·I·����ȡ��
                                                               1'b0��TDS��RXBͨ·I·���ݲ�ȡ�� */
        unsigned int  tds_rxa_iq_exchange : 1;  /* bit[4-4]  : 1'b1��TDS��RXAͨ·IQ·���ݽ���
                                                               1'b0��TDS��RXAͨ·IQ·���ݲ�����
                                                               V3R3��֧��IQ�������ܡ� */
        unsigned int  tds_rxa_q_inv       : 1;  /* bit[5-5]  : 1'b1��TDS��RXAͨ·Q·����ȡ��
                                                               1'b0��TDS��RXAͨ·Q·���ݲ�ȡ�� */
        unsigned int  tds_rxa_i_inv       : 1;  /* bit[6-6]  : 1'b1��TDS��RXAͨ·I·����ȡ��
                                                               1'b0��TDS��RXAͨ·I·���ݲ�ȡ�� */
        unsigned int  tds_tx_iq_exchange  : 1;  /* bit[7-7]  : 1'b1��TDS��TXͨ·IQ·���ݽ���
                                                               1'b0��TDS��TXͨ·IQ·���ݲ�����
                                                               V3R3��֧��IQ�������ܡ� */
        unsigned int  tds_tx_q_inv        : 1;  /* bit[8-8]  : 1'b1��TDS��TXͨ·Q·����ȡ��
                                                               1'b0��TDS��TXͨ·Q·���ݲ�ȡ�� */
        unsigned int  tds_tx_i_inv        : 1;  /* bit[9-9]  : 1'b1��TDS��TXͨ·I·����ȡ��
                                                               1'b0��TDS��TXͨ·I·���ݲ�ȡ�� */
        unsigned int  reserved_1          : 22; /* bit[10-31]: ���� */
    } reg;
} BBPCOMM_TDS_ABBIF_FMT_UNION;
#define BBPCOMM_TDS_ABBIF_FMT_tds_rxb_iq_exchange_START  (1)
#define BBPCOMM_TDS_ABBIF_FMT_tds_rxb_iq_exchange_END    (1)
#define BBPCOMM_TDS_ABBIF_FMT_tds_rxb_q_inv_START        (2)
#define BBPCOMM_TDS_ABBIF_FMT_tds_rxb_q_inv_END          (2)
#define BBPCOMM_TDS_ABBIF_FMT_tds_rxb_i_inv_START        (3)
#define BBPCOMM_TDS_ABBIF_FMT_tds_rxb_i_inv_END          (3)
#define BBPCOMM_TDS_ABBIF_FMT_tds_rxa_iq_exchange_START  (4)
#define BBPCOMM_TDS_ABBIF_FMT_tds_rxa_iq_exchange_END    (4)
#define BBPCOMM_TDS_ABBIF_FMT_tds_rxa_q_inv_START        (5)
#define BBPCOMM_TDS_ABBIF_FMT_tds_rxa_q_inv_END          (5)
#define BBPCOMM_TDS_ABBIF_FMT_tds_rxa_i_inv_START        (6)
#define BBPCOMM_TDS_ABBIF_FMT_tds_rxa_i_inv_END          (6)
#define BBPCOMM_TDS_ABBIF_FMT_tds_tx_iq_exchange_START   (7)
#define BBPCOMM_TDS_ABBIF_FMT_tds_tx_iq_exchange_END     (7)
#define BBPCOMM_TDS_ABBIF_FMT_tds_tx_q_inv_START         (8)
#define BBPCOMM_TDS_ABBIF_FMT_tds_tx_q_inv_END           (8)
#define BBPCOMM_TDS_ABBIF_FMT_tds_tx_i_inv_START         (9)
#define BBPCOMM_TDS_ABBIF_FMT_tds_tx_i_inv_END           (9)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GM_ABBIF_FMT_UNION
 �ṹ˵��  : GM_ABBIF_FMT �Ĵ����ṹ���塣��ַƫ����:0x0918����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gm_abbif_fmt_reg;
    struct
    {
        unsigned int  reserved_0         : 1;  /* bit[0-0]  : ���� */
        unsigned int  gm_rxb_iq_exchange : 1;  /* bit[1-1]  : 1'b1��GM��RXBͨ·IQ·���ݽ���
                                                              1'b0��GM��RXBͨ·IQ·���ݲ�����
                                                              V3R3��֧��IQ�������ܡ� */
        unsigned int  gm_rxb_q_inv       : 1;  /* bit[2-2]  : 1'b1��GM��RXBͨ·Q·����ȡ��
                                                              1'b0��GM��RXBͨ·Q·���ݲ�ȡ�� */
        unsigned int  gm_rxb_i_inv       : 1;  /* bit[3-3]  : 1'b1��GM��RXBͨ·I·����ȡ��
                                                              1'b0��GM��RXBͨ·I·���ݲ�ȡ�� */
        unsigned int  gm_rxa_iq_exchange : 1;  /* bit[4-4]  : 1'b1��GM��RXAͨ·IQ·���ݽ���
                                                              1'b0��GM��RXAͨ·IQ·���ݲ�����
                                                              V3R3��֧��IQ�������ܡ� */
        unsigned int  gm_rxa_q_inv       : 1;  /* bit[5-5]  : 1'b1��GM��RXAͨ·Q·����ȡ��
                                                              1'b0��GM��RXAͨ·Q·���ݲ�ȡ�� */
        unsigned int  gm_rxa_i_inv       : 1;  /* bit[6-6]  : 1'b1��GM��RXAͨ·I·����ȡ��
                                                              1'b0��GM��RXAͨ·I·���ݲ�ȡ�� */
        unsigned int  gm_tx_iq_exchange  : 1;  /* bit[7-7]  : 1'b1��GM��TXͨ·IQ·���ݽ���
                                                              1'b0��GM��TXͨ·IQ·���ݲ�����
                                                              V3R3��֧��IQ�������ܡ� */
        unsigned int  gm_tx_q_inv        : 1;  /* bit[8-8]  : 1'b1��GM��TXͨ·Q·����ȡ��
                                                              1'b0��GM��TXͨ·Q·���ݲ�ȡ�� */
        unsigned int  gm_tx_i_inv        : 1;  /* bit[9-9]  : 1'b1��GM��TXͨ·I·����ȡ��
                                                              1'b0��GM��TXͨ·I·���ݲ�ȡ�� */
        unsigned int  reserved_1         : 22; /* bit[10-31]: ���� */
    } reg;
} BBPCOMM_GM_ABBIF_FMT_UNION;
#define BBPCOMM_GM_ABBIF_FMT_gm_rxb_iq_exchange_START  (1)
#define BBPCOMM_GM_ABBIF_FMT_gm_rxb_iq_exchange_END    (1)
#define BBPCOMM_GM_ABBIF_FMT_gm_rxb_q_inv_START        (2)
#define BBPCOMM_GM_ABBIF_FMT_gm_rxb_q_inv_END          (2)
#define BBPCOMM_GM_ABBIF_FMT_gm_rxb_i_inv_START        (3)
#define BBPCOMM_GM_ABBIF_FMT_gm_rxb_i_inv_END          (3)
#define BBPCOMM_GM_ABBIF_FMT_gm_rxa_iq_exchange_START  (4)
#define BBPCOMM_GM_ABBIF_FMT_gm_rxa_iq_exchange_END    (4)
#define BBPCOMM_GM_ABBIF_FMT_gm_rxa_q_inv_START        (5)
#define BBPCOMM_GM_ABBIF_FMT_gm_rxa_q_inv_END          (5)
#define BBPCOMM_GM_ABBIF_FMT_gm_rxa_i_inv_START        (6)
#define BBPCOMM_GM_ABBIF_FMT_gm_rxa_i_inv_END          (6)
#define BBPCOMM_GM_ABBIF_FMT_gm_tx_iq_exchange_START   (7)
#define BBPCOMM_GM_ABBIF_FMT_gm_tx_iq_exchange_END     (7)
#define BBPCOMM_GM_ABBIF_FMT_gm_tx_q_inv_START         (8)
#define BBPCOMM_GM_ABBIF_FMT_gm_tx_q_inv_END           (8)
#define BBPCOMM_GM_ABBIF_FMT_gm_tx_i_inv_START         (9)
#define BBPCOMM_GM_ABBIF_FMT_gm_tx_i_inv_END           (9)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GS_ABBIF_FMT_UNION
 �ṹ˵��  : GS_ABBIF_FMT �Ĵ����ṹ���塣��ַƫ����:0x091C����ֵ:0x00000001�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gs_abbif_fmt_reg;
    struct
    {
        unsigned int  reserved_0         : 1;  /* bit[0-0]  : ���� */
        unsigned int  gs_rxb_iq_exchange : 1;  /* bit[1-1]  : 1'b1��GS��RXBͨ·IQ·���ݽ���
                                                              1'b0��GS��RXBͨ·IQ·���ݲ�����
                                                              V3R3��֧��IQ�������ܡ� */
        unsigned int  gs_rxb_q_inv       : 1;  /* bit[2-2]  : 1'b1��GS��RXBͨ·Q·����ȡ��
                                                              1'b0��GS��RXBͨ·Q·���ݲ�ȡ�� */
        unsigned int  gs_rxb_i_inv       : 1;  /* bit[3-3]  : 1'b1��GS��RXBͨ·I·����ȡ��
                                                              1'b0��GS��RXBͨ·I·���ݲ�ȡ�� */
        unsigned int  gs_rxa_iq_exchange : 1;  /* bit[4-4]  : 1'b1��GS��RXAͨ·IQ·���ݽ���
                                                              1'b0��GS��RXAͨ·IQ·���ݲ�����
                                                              V3R3��֧��IQ�������ܡ� */
        unsigned int  gs_rxa_q_inv       : 1;  /* bit[5-5]  : 1'b1��GS��RXAͨ·Q·����ȡ��
                                                              1'b0��GS��RXAͨ·Q·���ݲ�ȡ�� */
        unsigned int  gs_rxa_i_inv       : 1;  /* bit[6-6]  : 1'b1��GS��RXAͨ·I·����ȡ��
                                                              1'b0��GS��RXAͨ·I·���ݲ�ȡ�� */
        unsigned int  gs_tx_iq_exchange  : 1;  /* bit[7-7]  : 1'b1��GS��TXͨ·IQ·���ݽ���
                                                              1'b0��GS��TXͨ·IQ·���ݲ�����
                                                              V3R3��֧��IQ�������ܡ� */
        unsigned int  gs_tx_q_inv        : 1;  /* bit[8-8]  : 1'b1��GS��TXͨ·Q·����ȡ��
                                                              1'b0��GS��TXͨ·Q·���ݲ�ȡ�� */
        unsigned int  gs_tx_i_inv        : 1;  /* bit[9-9]  : 1'b1��GS��TXͨ·I·����ȡ��
                                                              1'b0��GS��TXͨ·I·���ݲ�ȡ�� */
        unsigned int  reserved_1         : 22; /* bit[10-31]: ���� */
    } reg;
} BBPCOMM_GS_ABBIF_FMT_UNION;
#define BBPCOMM_GS_ABBIF_FMT_gs_rxb_iq_exchange_START  (1)
#define BBPCOMM_GS_ABBIF_FMT_gs_rxb_iq_exchange_END    (1)
#define BBPCOMM_GS_ABBIF_FMT_gs_rxb_q_inv_START        (2)
#define BBPCOMM_GS_ABBIF_FMT_gs_rxb_q_inv_END          (2)
#define BBPCOMM_GS_ABBIF_FMT_gs_rxb_i_inv_START        (3)
#define BBPCOMM_GS_ABBIF_FMT_gs_rxb_i_inv_END          (3)
#define BBPCOMM_GS_ABBIF_FMT_gs_rxa_iq_exchange_START  (4)
#define BBPCOMM_GS_ABBIF_FMT_gs_rxa_iq_exchange_END    (4)
#define BBPCOMM_GS_ABBIF_FMT_gs_rxa_q_inv_START        (5)
#define BBPCOMM_GS_ABBIF_FMT_gs_rxa_q_inv_END          (5)
#define BBPCOMM_GS_ABBIF_FMT_gs_rxa_i_inv_START        (6)
#define BBPCOMM_GS_ABBIF_FMT_gs_rxa_i_inv_END          (6)
#define BBPCOMM_GS_ABBIF_FMT_gs_tx_iq_exchange_START   (7)
#define BBPCOMM_GS_ABBIF_FMT_gs_tx_iq_exchange_END     (7)
#define BBPCOMM_GS_ABBIF_FMT_gs_tx_q_inv_START         (8)
#define BBPCOMM_GS_ABBIF_FMT_gs_tx_q_inv_END           (8)
#define BBPCOMM_GS_ABBIF_FMT_gs_tx_i_inv_START         (9)
#define BBPCOMM_GS_ABBIF_FMT_gs_tx_i_inv_END           (9)


/*****************************************************************************
 �ṹ��    : BBPCOMM_REG24_FOR_USE_UNION
 �ṹ˵��  : REG24_FOR_USE �Ĵ����ṹ���塣��ַƫ����:0x0980����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      reg24_for_use_reg;
    struct
    {
        unsigned int  g1_overch_inter_meas_en : 1;  /* bit[0]   : GSM1��ͨ����Ƶ����ģʽʹ�ܣ�
                                                                  1'b0����ʹ��
                                                                  1'b1��ʹ��
                                                                  
                                                                  V7R2������ */
        unsigned int  reg24_for_use           : 31; /* bit[1-31]: �Ĵ���24��Ԥ������DSP֮�䴫����Ϣ�� */
    } reg;
} BBPCOMM_REG24_FOR_USE_UNION;
#define BBPCOMM_REG24_FOR_USE_g1_overch_inter_meas_en_START  (0)
#define BBPCOMM_REG24_FOR_USE_g1_overch_inter_meas_en_END    (0)
#define BBPCOMM_REG24_FOR_USE_reg24_for_use_START            (1)
#define BBPCOMM_REG24_FOR_USE_reg24_for_use_END              (31)


/*****************************************************************************
 �ṹ��    : BBPCOMM_REG25_FOR_USE_UNION
 �ṹ˵��  : REG25_FOR_USE �Ĵ����ṹ���塣��ַƫ����:0x0984����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      reg25_for_use_reg;
    struct
    {
        unsigned int  g2_overch_inter_meas_en : 1;  /* bit[0]   : GSM2��ͨ����Ƶ����ģʽʹ�ܣ�
                                                                  1'b0����ʹ��
                                                                  1'b1��ʹ��
                                                                  
                                                                  V7R2������ */
        unsigned int  reg25_for_use           : 31; /* bit[1-31]: �Ĵ���25��Ԥ������DSP֮�䴫����Ϣ�� */
    } reg;
} BBPCOMM_REG25_FOR_USE_UNION;
#define BBPCOMM_REG25_FOR_USE_g2_overch_inter_meas_en_START  (0)
#define BBPCOMM_REG25_FOR_USE_g2_overch_inter_meas_en_END    (0)
#define BBPCOMM_REG25_FOR_USE_reg25_for_use_START            (1)
#define BBPCOMM_REG25_FOR_USE_reg25_for_use_END              (31)


/*****************************************************************************
 �ṹ��    : BBPCOMM_REG26_FOR_USE_UNION
 �ṹ˵��  : REG26_FOR_USE �Ĵ����ṹ���塣��ַƫ����:0x0988����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      reg26_for_use_reg;
    struct
    {
        unsigned int  ssi_unbind_en : 1;  /* bit[0]   : ssiͨ������ʹ�ܣ�
                                                        1'b0��ͨ����
                                                        1'b1��ͨ������
                                                        
                                                        V7R2������ */
        unsigned int  ssi_ch_sel0   : 1;  /* bit[1]   : ͨ��0ӳ��ssi������ϵ��
                                                        1'b0��ͨ��0ӳ�䵽ssi0
                                                        1'b1��ͨ��0ӳ�䵽ssi1
                                                        
                                                        V7R2������ */
        unsigned int  ssi_ch_sel1   : 1;  /* bit[2]   : ͨ��1ӳ��ssi������ϵ��
                                                        1'b0��ͨ��1ӳ�䵽ssi0
                                                        1'b1��ͨ��1ӳ�䵽ssi1
                                                        
                                                        V7R2������ */
        unsigned int  reg26_for_use : 29; /* bit[3-31]: �Ĵ���26��Ԥ������DSP֮�䴫����Ϣ�� */
    } reg;
} BBPCOMM_REG26_FOR_USE_UNION;
#define BBPCOMM_REG26_FOR_USE_ssi_unbind_en_START  (0)
#define BBPCOMM_REG26_FOR_USE_ssi_unbind_en_END    (0)
#define BBPCOMM_REG26_FOR_USE_ssi_ch_sel0_START    (1)
#define BBPCOMM_REG26_FOR_USE_ssi_ch_sel0_END      (1)
#define BBPCOMM_REG26_FOR_USE_ssi_ch_sel1_START    (2)
#define BBPCOMM_REG26_FOR_USE_ssi_ch_sel1_END      (2)
#define BBPCOMM_REG26_FOR_USE_reg26_for_use_START  (3)
#define BBPCOMM_REG26_FOR_USE_reg26_for_use_END    (31)


/*****************************************************************************
 �ṹ��    : BBPCOMM_REG27_FOR_USE_UNION
 �ṹ˵��  : REG27_FOR_USE �Ĵ����ṹ���塣��ַƫ����:0x098C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      reg27_for_use_reg;
    struct
    {
        unsigned int  rf_tcvr_on_or_en : 1;  /* bit[0]   : �����RF��TCVR_ON ˫ͨ��һ��ʹ��
                                                           1������ͨ����TCVR_ON���ߣ���2��ͨ����TCVR_ON�����ߣ�
                                                           0�����ݸ���ͨ��״̬����
                                                           
                                                           V7R2������ */
        unsigned int  reg27_for_use    : 31; /* bit[1-31]: �Ĵ���27��Ԥ������DSP֮�䴫����Ϣ�� */
    } reg;
} BBPCOMM_REG27_FOR_USE_UNION;
#define BBPCOMM_REG27_FOR_USE_rf_tcvr_on_or_en_START  (0)
#define BBPCOMM_REG27_FOR_USE_rf_tcvr_on_or_en_END    (0)
#define BBPCOMM_REG27_FOR_USE_reg27_for_use_START     (1)
#define BBPCOMM_REG27_FOR_USE_reg27_for_use_END       (31)


/*****************************************************************************
 �ṹ��    : BBPCOMM_REG28_FOR_USE_UNION
 �ṹ˵��  : REG28_FOR_USE �Ĵ����ṹ���塣��ַƫ����:0x0990����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      reg28_for_use_reg;
    struct
    {
        unsigned int  ch0_abb_sel_force_en    : 1;  /* bit[0]   : �����ABB_CFGģ���ѡͨ�ź�ch1_sel_abb�Ƿ�ǿ��ʹ��
                                                                  1��ǿ�ƣ�ǿ��ֵΪch0_abb_sel_force_value
                                                                  0����ǿ�ƣ��߼��Կ�
                                                                  
                                                                  V7R2������ */
        unsigned int  ch0_abb_sel_force_value : 3;  /* bit[1-3] : �����ABB_CFGģ���ѡͨ�ź�ch0_sel_abbǿ��ʱ������ֵ
                                                                  
                                                                  V7R2������ */
        unsigned int  reg28_for_use           : 28; /* bit[4-31]: �Ĵ���28��Ԥ������DSP֮�䴫����Ϣ�� */
    } reg;
} BBPCOMM_REG28_FOR_USE_UNION;
#define BBPCOMM_REG28_FOR_USE_ch0_abb_sel_force_en_START     (0)
#define BBPCOMM_REG28_FOR_USE_ch0_abb_sel_force_en_END       (0)
#define BBPCOMM_REG28_FOR_USE_ch0_abb_sel_force_value_START  (1)
#define BBPCOMM_REG28_FOR_USE_ch0_abb_sel_force_value_END    (3)
#define BBPCOMM_REG28_FOR_USE_reg28_for_use_START            (4)
#define BBPCOMM_REG28_FOR_USE_reg28_for_use_END              (31)


/*****************************************************************************
 �ṹ��    : BBPCOMM_REG29_FOR_USE_UNION
 �ṹ˵��  : REG29_FOR_USE �Ĵ����ṹ���塣��ַƫ����:0x0994����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      reg29_for_use_reg;
    struct
    {
        unsigned int  ch1_abb_sel_force_en    : 1;  /* bit[0]   : �����ABB_CFGģ���ѡͨ�ź�ch1_sel_abb�Ƿ�ǿ��ʹ��
                                                                  1��ǿ�ƣ�ǿ��ֵΪch1_abb_sel_force_value
                                                                  0����ǿ�ƣ��߼��Կ�
                                                                  
                                                                  V7R2������ */
        unsigned int  ch1_abb_sel_force_value : 3;  /* bit[1-3] : �����ABB_CFGģ���ѡͨ�ź�ch1_sel_abbǿ��ʱ������ֵ
                                                                  
                                                                  V7R2������ */
        unsigned int  reg29_for_use           : 28; /* bit[4-31]: �Ĵ���29��Ԥ������DSP֮�䴫����Ϣ�� */
    } reg;
} BBPCOMM_REG29_FOR_USE_UNION;
#define BBPCOMM_REG29_FOR_USE_ch1_abb_sel_force_en_START     (0)
#define BBPCOMM_REG29_FOR_USE_ch1_abb_sel_force_en_END       (0)
#define BBPCOMM_REG29_FOR_USE_ch1_abb_sel_force_value_START  (1)
#define BBPCOMM_REG29_FOR_USE_ch1_abb_sel_force_value_END    (3)
#define BBPCOMM_REG29_FOR_USE_reg29_for_use_START            (4)
#define BBPCOMM_REG29_FOR_USE_reg29_for_use_END              (31)


/*****************************************************************************
 �ṹ��    : BBPCOMM_REG30_FOR_USE_UNION
 �ṹ˵��  : REG30_FOR_USE �Ĵ����ṹ���塣��ַƫ����:0x0998����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      reg30_for_use_reg;
    struct
    {
        unsigned int  ch0_rx_en_force_low_cnt : 12; /* bit[0-11] : ch0��com2abb_line_ctrl_mode�л�ʱ��com2abb_rxa/b_enǿ�����͵�ʱ�䡣��λ������ʱ��
                                                                   
                                                                   V7R2������ */
        unsigned int  reg30_for_use           : 20; /* bit[12-31]: �Ĵ���30��Ԥ������DSP֮�䴫����Ϣ�� */
    } reg;
} BBPCOMM_REG30_FOR_USE_UNION;
#define BBPCOMM_REG30_FOR_USE_ch0_rx_en_force_low_cnt_START  (0)
#define BBPCOMM_REG30_FOR_USE_ch0_rx_en_force_low_cnt_END    (11)
#define BBPCOMM_REG30_FOR_USE_reg30_for_use_START            (12)
#define BBPCOMM_REG30_FOR_USE_reg30_for_use_END              (31)


/*****************************************************************************
 �ṹ��    : BBPCOMM_REG31_FOR_USE_UNION
 �ṹ˵��  : REG31_FOR_USE �Ĵ����ṹ���塣��ַƫ����:0x099C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      reg31_for_use_reg;
    struct
    {
        unsigned int  ch1_rx_en_force_low_cnt : 12; /* bit[0-11] : ch1��com2abb_line_ctrl_mode�л�ʱ��com2abb_rxa/b_enǿ�����͵�ʱ�䡣��λ������ʱ��
                                                                   
                                                                   V7R2������ */
        unsigned int  reg31_for_use           : 20; /* bit[12-31]: �Ĵ���31��Ԥ������DSP֮�䴫����Ϣ�� */
    } reg;
} BBPCOMM_REG31_FOR_USE_UNION;
#define BBPCOMM_REG31_FOR_USE_ch1_rx_en_force_low_cnt_START  (0)
#define BBPCOMM_REG31_FOR_USE_ch1_rx_en_force_low_cnt_END    (11)
#define BBPCOMM_REG31_FOR_USE_reg31_for_use_START            (12)
#define BBPCOMM_REG31_FOR_USE_reg31_for_use_END              (31)


/*****************************************************************************
 �ṹ��    : BBPCOMM_REG32_FOR_USE_UNION
 �ṹ˵��  : REG32_FOR_USE �Ĵ����ṹ���塣��ַƫ����:0x09A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      reg32_for_use_reg;
    struct
    {
        unsigned int  ssi_cnt_sel   : 1;  /* bit[0]   :  */
        unsigned int  reserved      : 3;  /* bit[1-3] : ���� */
        unsigned int  mipi_cnt_sel  : 1;  /* bit[4]   :  */
        unsigned int  reg32_for_use : 27; /* bit[5-31]: �Ĵ���32��Ԥ������DSP֮�䴫����Ϣ�� */
    } reg;
} BBPCOMM_REG32_FOR_USE_UNION;
#define BBPCOMM_REG32_FOR_USE_ssi_cnt_sel_START    (0)
#define BBPCOMM_REG32_FOR_USE_ssi_cnt_sel_END      (0)
#define BBPCOMM_REG32_FOR_USE_mipi_cnt_sel_START   (4)
#define BBPCOMM_REG32_FOR_USE_mipi_cnt_sel_END     (4)
#define BBPCOMM_REG32_FOR_USE_reg32_for_use_START  (5)
#define BBPCOMM_REG32_FOR_USE_reg32_for_use_END    (31)


/*****************************************************************************
 �ṹ��    : BBPCOMM_REG33_FOR_USE_UNION
 �ṹ˵��  : REG33_FOR_USE �Ĵ����ṹ���塣��ַƫ����:0x09A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      reg33_for_use_reg;
    struct
    {
        unsigned int  ch_tx_clk_debug : 1;  /* bit[0]   :  */
        unsigned int  reg33_for_use   : 31; /* bit[1-31]: �Ĵ���33��Ԥ������DSP֮�䴫����Ϣ�� */
    } reg;
} BBPCOMM_REG33_FOR_USE_UNION;
#define BBPCOMM_REG33_FOR_USE_ch_tx_clk_debug_START  (0)
#define BBPCOMM_REG33_FOR_USE_ch_tx_clk_debug_END    (0)
#define BBPCOMM_REG33_FOR_USE_reg33_for_use_START    (1)
#define BBPCOMM_REG33_FOR_USE_reg33_for_use_END      (31)


/*****************************************************************************
 �ṹ��    : BBPCOMM_DBG_CLK_GATE_EN_UNION
 �ṹ˵��  : DBG_CLK_GATE_EN �Ĵ����ṹ���塣��ַƫ����:0x0A30����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ſ�ʱ�����üĴ���
*****************************************************************************/
typedef union
{
    unsigned int      dbg_clk_gate_en_reg;
    struct
    {
        unsigned int  dsp_dbg_clk_gate_en : 1;  /* bit[0-0] : bbp_comm_dbgģ���ſ�ʱ��ʹ���źţ�
                                                              1��ֱ��ʹ������ʱ�ӣ�δ�����ſأ�
                                                              0������ʱ����Ч����ʱ���е͹���״̬�� */
        unsigned int  dsp_dbg_clk_bypass  : 1;  /* bit[1-1] : bbp_comm_dbgģ��ʱ��bypass�����źţ�
                                                              1��ֱ��ʹ������ʱ�ӣ��������ſش�����ʱdsp_dbg_clk_gate_en������Ч��
                                                              0����ʾ����dsp_dbg_clk_gate_en�����ſش��� */
        unsigned int  reserved            : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_DBG_CLK_GATE_EN_UNION;
#define BBPCOMM_DBG_CLK_GATE_EN_dsp_dbg_clk_gate_en_START  (0)
#define BBPCOMM_DBG_CLK_GATE_EN_dsp_dbg_clk_gate_en_END    (0)
#define BBPCOMM_DBG_CLK_GATE_EN_dsp_dbg_clk_bypass_START   (1)
#define BBPCOMM_DBG_CLK_GATE_EN_dsp_dbg_clk_bypass_END     (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_MIPI_SSI_BUSY_STATE_UNION
 �ṹ˵��  : MIPI_SSI_BUSY_STATE �Ĵ����ṹ���塣��ַƫ����:0x0A34����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      mipi_ssi_busy_state_reg;
    struct
    {
        unsigned int  com2tds_busy_rf_ssi1 : 1;  /* bit[0]    : TDS SSI1æ��־�� */
        unsigned int  com2tds_busy_rf_ssi0 : 1;  /* bit[1]    : TDS SSI0æ��־�� */
        unsigned int  com2w_busy_rf_ssi1   : 1;  /* bit[2]    : W SSI1æ��־�� */
        unsigned int  com2w_busy_rf_ssi0   : 1;  /* bit[3]    : W SSI0æ��־�� */
        unsigned int  com2lte_busy_rf_ssi1 : 1;  /* bit[4]    : LTE SSI1æ��־�� */
        unsigned int  com2lte_busy_rf_ssi0 : 1;  /* bit[5]    : LTE SSI0æ��־�� */
        unsigned int  com2g2_busy_rf_ssi1  : 1;  /* bit[6]    : G2 SSI1æ��־�� */
        unsigned int  com2g2_busy_rf_ssi0  : 1;  /* bit[7]    : G2 SSI0æ��־�� */
        unsigned int  com2g1_busy_rf_ssi1  : 1;  /* bit[8]    : G1 SSI1æ��־�� */
        unsigned int  com2g1_busy_rf_ssi0  : 1;  /* bit[9]    : G1 SSI0æ��־�� */
        unsigned int  com2tds_busy_mipi1   : 1;  /* bit[10]   : TDS MIPI1æ��־�� */
        unsigned int  com2tds_busy_mipi0   : 1;  /* bit[11]   : TDS MIPI0æ��־�� */
        unsigned int  com2w_busy_mipi1     : 1;  /* bit[12]   : W MIPI1æ��־�� */
        unsigned int  com2w_busy_mipi0     : 1;  /* bit[13]   : W MIPI0æ��־�� */
        unsigned int  com2lte_busy_mipi1   : 1;  /* bit[14]   : LTE MIPI1æ��־�� */
        unsigned int  com2lte_busy_mipi0   : 1;  /* bit[15]   : LTE MIPI0æ��־�� */
        unsigned int  com2g2_busy_mipi1    : 1;  /* bit[16]   : G2 MIPI1æ��־�� */
        unsigned int  com2g2_busy_mipi0    : 1;  /* bit[17]   : G2 MIPI0æ��־�� */
        unsigned int  com2g1_busy_mipi1    : 1;  /* bit[18]   : G1 MIPI1æ��־�� */
        unsigned int  com2g1_busy_mipi0    : 1;  /* bit[19]   : G1 MIPI0æ��־�� */
        unsigned int  com2c_busy_rf_ssi1   : 1;  /* bit[20]   : C SSI1æ��־�� */
        unsigned int  com2c_busy_rf_ssi0   : 1;  /* bit[21]   : C SSI0æ��־�� */
        unsigned int  com2c_busy_mipi1     : 1;  /* bit[22]   : C MIPI1æ��־�� */
        unsigned int  com2c_busy_mipi0     : 1;  /* bit[23]   : C MIPI0æ��־�� */
        unsigned int  reserved             : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_MIPI_SSI_BUSY_STATE_UNION;
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2tds_busy_rf_ssi1_START  (0)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2tds_busy_rf_ssi1_END    (0)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2tds_busy_rf_ssi0_START  (1)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2tds_busy_rf_ssi0_END    (1)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2w_busy_rf_ssi1_START    (2)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2w_busy_rf_ssi1_END      (2)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2w_busy_rf_ssi0_START    (3)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2w_busy_rf_ssi0_END      (3)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2lte_busy_rf_ssi1_START  (4)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2lte_busy_rf_ssi1_END    (4)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2lte_busy_rf_ssi0_START  (5)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2lte_busy_rf_ssi0_END    (5)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2g2_busy_rf_ssi1_START   (6)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2g2_busy_rf_ssi1_END     (6)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2g2_busy_rf_ssi0_START   (7)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2g2_busy_rf_ssi0_END     (7)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2g1_busy_rf_ssi1_START   (8)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2g1_busy_rf_ssi1_END     (8)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2g1_busy_rf_ssi0_START   (9)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2g1_busy_rf_ssi0_END     (9)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2tds_busy_mipi1_START    (10)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2tds_busy_mipi1_END      (10)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2tds_busy_mipi0_START    (11)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2tds_busy_mipi0_END      (11)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2w_busy_mipi1_START      (12)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2w_busy_mipi1_END        (12)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2w_busy_mipi0_START      (13)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2w_busy_mipi0_END        (13)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2lte_busy_mipi1_START    (14)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2lte_busy_mipi1_END      (14)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2lte_busy_mipi0_START    (15)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2lte_busy_mipi0_END      (15)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2g2_busy_mipi1_START     (16)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2g2_busy_mipi1_END       (16)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2g2_busy_mipi0_START     (17)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2g2_busy_mipi0_END       (17)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2g1_busy_mipi1_START     (18)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2g1_busy_mipi1_END       (18)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2g1_busy_mipi0_START     (19)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2g1_busy_mipi0_END       (19)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2c_busy_rf_ssi1_START    (20)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2c_busy_rf_ssi1_END      (20)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2c_busy_rf_ssi0_START    (21)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2c_busy_rf_ssi0_END      (21)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2c_busy_mipi1_START      (22)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2c_busy_mipi1_END        (22)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2c_busy_mipi0_START      (23)
#define BBPCOMM_MIPI_SSI_BUSY_STATE_com2c_busy_mipi0_END        (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_DBG_COMM_EN_UNION
 �ṹ˵��  : DBG_COMM_EN �Ĵ����ṹ���塣��ַƫ����:0x0A38����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dbg_comm_en_reg;
    struct
    {
        unsigned int  dbg_comm_en : 1;  /* bit[0-0] : bbp_comm_dbgʹ���źţ�
                                                      1��ʹ�ܣ�
                                                      0����ʹ�ܡ� */
        unsigned int  reserved    : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_DBG_COMM_EN_UNION;
#define BBPCOMM_DBG_COMM_EN_dbg_comm_en_START  (0)
#define BBPCOMM_DBG_COMM_EN_dbg_comm_en_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_S_W_CH_NUM_IND_UNION
 �ṹ˵��  : S_W_CH_NUM_IND �Ĵ����ṹ���塣��ַƫ����:0x0A40����ֵ:0x00000000�����:32
 �Ĵ���˵��: WΪ��ģʱ��Ӧͨ����ָʾ�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      s_w_ch_num_ind_reg;
    struct
    {
        unsigned int  s_w_ch_num_ind     : 2;  /* bit[0-1] : WΪ��ģʱ��Ӧ��ͨ��ѡ���źš�
                                                             0��ѡ��ͨ��0��
                                                             1��ѡ��ͨ��1��
                                                             2��ѡ��ͨ��2��
                                                             ����ʱ�̣���ģ����ͨ�ų������� */
        unsigned int  s_w_ch_num_ind_sel : 1;  /* bit[2-2] : WΪ��ģʱ��Ӧ��ͨ��ѡ���ź���Ч��ʽ��
                                                             0����int1��Ч��
                                                             1��������Ч�� */
        unsigned int  reserved           : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_S_W_CH_NUM_IND_UNION;
#define BBPCOMM_S_W_CH_NUM_IND_s_w_ch_num_ind_START      (0)
#define BBPCOMM_S_W_CH_NUM_IND_s_w_ch_num_ind_END        (1)
#define BBPCOMM_S_W_CH_NUM_IND_s_w_ch_num_ind_sel_START  (2)
#define BBPCOMM_S_W_CH_NUM_IND_s_w_ch_num_ind_sel_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_S_LTE_CH_NUM_IND_UNION
 �ṹ˵��  : S_LTE_CH_NUM_IND �Ĵ����ṹ���塣��ַƫ����:0x0A44����ֵ:0x00000000�����:32
 �Ĵ���˵��: LTEΪ��ģʱ��Ӧͨ����ָʾ�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      s_lte_ch_num_ind_reg;
    struct
    {
        unsigned int  s_lte_ch_num_ind     : 1;  /* bit[0-0] : LTEΪ��ģʱ��Ӧ��ͨ��ѡ���źš�
                                                               0��ѡ��ͨ��0��
                                                               1��ѡ��ͨ��1��
                                                               ����ʱ�̣���ģ����ͨ�ų������� */
        unsigned int  s_lte_ch_num_ind_sel : 1;  /* bit[1-1] : LTEΪ��ģʱ��Ӧ��ͨ��ѡ���ź���Ч��ʽ��
                                                               0����int1��Ч��
                                                               1��������Ч�� */
        unsigned int  reserved             : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_S_LTE_CH_NUM_IND_UNION;
#define BBPCOMM_S_LTE_CH_NUM_IND_s_lte_ch_num_ind_START      (0)
#define BBPCOMM_S_LTE_CH_NUM_IND_s_lte_ch_num_ind_END        (0)
#define BBPCOMM_S_LTE_CH_NUM_IND_s_lte_ch_num_ind_sel_START  (1)
#define BBPCOMM_S_LTE_CH_NUM_IND_s_lte_ch_num_ind_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_S_TDS_CH_NUM_IND_UNION
 �ṹ˵��  : S_TDS_CH_NUM_IND �Ĵ����ṹ���塣��ַƫ����:0x0A48����ֵ:0x00000000�����:32
 �Ĵ���˵��: TDSΪ��ģʱ��Ӧͨ����ָʾ�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      s_tds_ch_num_ind_reg;
    struct
    {
        unsigned int  s_tds_ch_num_ind     : 1;  /* bit[0-0] : TDSΪ��ģʱ��Ӧ��ͨ��ѡ���źš�
                                                               0��ѡ��ͨ��0��
                                                               1��ѡ��ͨ��1��
                                                               ����ʱ�̣���ģ����ͨ�ų������� */
        unsigned int  s_tds_ch_num_ind_sel : 1;  /* bit[1-1] : TDSΪ��ģʱ��Ӧ��ͨ��ѡ���ź���Ч��ʽ��
                                                               0����int1��Ч��
                                                               1��������Ч�� */
        unsigned int  reserved             : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_S_TDS_CH_NUM_IND_UNION;
#define BBPCOMM_S_TDS_CH_NUM_IND_s_tds_ch_num_ind_START      (0)
#define BBPCOMM_S_TDS_CH_NUM_IND_s_tds_ch_num_ind_END        (0)
#define BBPCOMM_S_TDS_CH_NUM_IND_s_tds_ch_num_ind_sel_START  (1)
#define BBPCOMM_S_TDS_CH_NUM_IND_s_tds_ch_num_ind_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_S_GM_CH_NUM_IND_UNION
 �ṹ˵��  : S_GM_CH_NUM_IND �Ĵ����ṹ���塣��ַƫ����:0x0A4C����ֵ:0x00000000�����:32
 �Ĵ���˵��: GMΪ��ģʱ��Ӧͨ����ָʾ�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      s_gm_ch_num_ind_reg;
    struct
    {
        unsigned int  s_gm_ch_num_ind     : 2;  /* bit[0-1] : GMΪ��ģʱ��Ӧ��ͨ��ѡ���źš�
                                                              0��ѡ��ͨ��0��
                                                              1��ѡ��ͨ��1��
                                                              2��ѡ��ͨ��2��
                                                              ����ʱ�̣���ģ����ͨ�ų������� */
        unsigned int  s_gm_ch_num_ind_sel : 1;  /* bit[2-2] : GMΪ��ģʱ��Ӧ��ͨ��ѡ���ź���Ч��ʽ��
                                                              0����int1��Ч��
                                                              1��������Ч�� */
        unsigned int  reserved            : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_S_GM_CH_NUM_IND_UNION;
#define BBPCOMM_S_GM_CH_NUM_IND_s_gm_ch_num_ind_START      (0)
#define BBPCOMM_S_GM_CH_NUM_IND_s_gm_ch_num_ind_END        (1)
#define BBPCOMM_S_GM_CH_NUM_IND_s_gm_ch_num_ind_sel_START  (2)
#define BBPCOMM_S_GM_CH_NUM_IND_s_gm_ch_num_ind_sel_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_S_GS_CH_NUM_IND_UNION
 �ṹ˵��  : S_GS_CH_NUM_IND �Ĵ����ṹ���塣��ַƫ����:0x0A50����ֵ:0x00000000�����:32
 �Ĵ���˵��: GSΪ��ģʱ��Ӧͨ����ָʾ�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      s_gs_ch_num_ind_reg;
    struct
    {
        unsigned int  s_gs_ch_num_ind     : 2;  /* bit[0-1] : GSΪ��ģʱ��Ӧ��ͨ��ѡ���źš�
                                                              0��ѡ��ͨ��0��
                                                              1��ѡ��ͨ��1��
                                                              2��ѡ��ͨ��2��
                                                              ����ʱ�̣���ģ����ͨ�ų������� */
        unsigned int  s_gs_ch_num_ind_sel : 1;  /* bit[2-2] : GSΪ��ģʱ��Ӧ��ͨ��ѡ���ź���Ч��ʽ��
                                                              0����int1��Ч��
                                                              1��������Ч�� */
        unsigned int  reserved            : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_S_GS_CH_NUM_IND_UNION;
#define BBPCOMM_S_GS_CH_NUM_IND_s_gs_ch_num_ind_START      (0)
#define BBPCOMM_S_GS_CH_NUM_IND_s_gs_ch_num_ind_END        (1)
#define BBPCOMM_S_GS_CH_NUM_IND_s_gs_ch_num_ind_sel_START  (2)
#define BBPCOMM_S_GS_CH_NUM_IND_s_gs_ch_num_ind_sel_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_L_CH_SW_UNION
 �ṹ˵��  : L_CH_SW �Ĵ����ṹ���塣��ַƫ����:0x0B00����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      l_ch_sw_reg;
    struct
    {
        unsigned int  l_ch_sw_rf     : 1;  /* bit[0]   : rf����ź��Ƿ񽻻���
                                                         1'b0��0/1ͨ��������
                                                         1'b1��0/1ͨ������ */
        unsigned int  l_ch_sw_mipi   : 1;  /* bit[1]   : mipi����ź��Ƿ񽻻���
                                                         1'b0��0/1ͨ��������
                                                         1'b1��0/1ͨ������ */
        unsigned int  l_ch_sw_abb_tx : 1;  /* bit[2]   : abb tx����ź��Ƿ񽻻���
                                                         1'b0��0/1ͨ��������
                                                         1'b1��0/1ͨ������ */
        unsigned int  l_ch_sw_abb_rx : 1;  /* bit[3]   : abb rx����ź��Ƿ񽻻���
                                                         1'b0��0/1ͨ��������
                                                         1'b1��0/1ͨ������ */
        unsigned int  l_ch_sw_pmu    : 1;  /* bit[4]   : pmu����ź��Ƿ񽻻���
                                                         1'b0��0/1ͨ��������
                                                         1'b1��0/1ͨ������ */
        unsigned int  l_ch_sw_apt    : 1;  /* bit[5]   : apt����ź��Ƿ񽻻���
                                                         1'b0��0/1ͨ��������
                                                         1'b1��0/1ͨ������ */
        unsigned int  reserved       : 26; /* bit[6-31]: ���� */
    } reg;
} BBPCOMM_L_CH_SW_UNION;
#define BBPCOMM_L_CH_SW_l_ch_sw_rf_START      (0)
#define BBPCOMM_L_CH_SW_l_ch_sw_rf_END        (0)
#define BBPCOMM_L_CH_SW_l_ch_sw_mipi_START    (1)
#define BBPCOMM_L_CH_SW_l_ch_sw_mipi_END      (1)
#define BBPCOMM_L_CH_SW_l_ch_sw_abb_tx_START  (2)
#define BBPCOMM_L_CH_SW_l_ch_sw_abb_tx_END    (2)
#define BBPCOMM_L_CH_SW_l_ch_sw_abb_rx_START  (3)
#define BBPCOMM_L_CH_SW_l_ch_sw_abb_rx_END    (3)
#define BBPCOMM_L_CH_SW_l_ch_sw_pmu_START     (4)
#define BBPCOMM_L_CH_SW_l_ch_sw_pmu_END       (4)
#define BBPCOMM_L_CH_SW_l_ch_sw_apt_START     (5)
#define BBPCOMM_L_CH_SW_l_ch_sw_apt_END       (5)


/*****************************************************************************
 �ṹ��    : BBPCOMM_W_CH_SW_UNION
 �ṹ˵��  : W_CH_SW �Ĵ����ṹ���塣��ַƫ����:0x0B04����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      w_ch_sw_reg;
    struct
    {
        unsigned int  w_ch_sw_rf     : 1;  /* bit[0]   : rf����ź��Ƿ񽻻���
                                                         1'b0��0/1ͨ��������
                                                         1'b1��0/1ͨ������ */
        unsigned int  w_ch_sw_mipi   : 1;  /* bit[1]   : mipi����ź��Ƿ񽻻���
                                                         1'b0��0/1ͨ��������
                                                         1'b1��0/1ͨ������ */
        unsigned int  w_ch_sw_abb_tx : 1;  /* bit[2]   : abb tx����ź��Ƿ񽻻���
                                                         1'b0��0/1ͨ��������
                                                         1'b1��0/1ͨ������ */
        unsigned int  w_ch_sw_abb_rx : 1;  /* bit[3]   : abb rx����ź��Ƿ񽻻���
                                                         1'b0��0/1ͨ��������
                                                         1'b1��0/1ͨ������ */
        unsigned int  w_ch_sw_pmu    : 1;  /* bit[4]   : pmu����ź��Ƿ񽻻���
                                                         1'b0��0/1ͨ��������
                                                         1'b1��0/1ͨ������ */
        unsigned int  w_ch_sw_apt    : 1;  /* bit[5]   : apt����ź��Ƿ񽻻���
                                                         1'b0��0/1ͨ��������
                                                         1'b1��0/1ͨ������ */
        unsigned int  reserved       : 26; /* bit[6-31]: ���� */
    } reg;
} BBPCOMM_W_CH_SW_UNION;
#define BBPCOMM_W_CH_SW_w_ch_sw_rf_START      (0)
#define BBPCOMM_W_CH_SW_w_ch_sw_rf_END        (0)
#define BBPCOMM_W_CH_SW_w_ch_sw_mipi_START    (1)
#define BBPCOMM_W_CH_SW_w_ch_sw_mipi_END      (1)
#define BBPCOMM_W_CH_SW_w_ch_sw_abb_tx_START  (2)
#define BBPCOMM_W_CH_SW_w_ch_sw_abb_tx_END    (2)
#define BBPCOMM_W_CH_SW_w_ch_sw_abb_rx_START  (3)
#define BBPCOMM_W_CH_SW_w_ch_sw_abb_rx_END    (3)
#define BBPCOMM_W_CH_SW_w_ch_sw_pmu_START     (4)
#define BBPCOMM_W_CH_SW_w_ch_sw_pmu_END       (4)
#define BBPCOMM_W_CH_SW_w_ch_sw_apt_START     (5)
#define BBPCOMM_W_CH_SW_w_ch_sw_apt_END       (5)


/*****************************************************************************
 �ṹ��    : BBPCOMM_T_CH_SW_UNION
 �ṹ˵��  : T_CH_SW �Ĵ����ṹ���塣��ַƫ����:0x0B08����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      t_ch_sw_reg;
    struct
    {
        unsigned int  t_ch_sw_rf     : 1;  /* bit[0]   : rf����ź��Ƿ񽻻���
                                                         1'b0��0/1ͨ��������
                                                         1'b1��0/1ͨ������ */
        unsigned int  t_ch_sw_mipi   : 1;  /* bit[1]   : mipi����ź��Ƿ񽻻���
                                                         1'b0��0/1ͨ��������
                                                         1'b1��0/1ͨ������ */
        unsigned int  t_ch_sw_abb_tx : 1;  /* bit[2]   : abb tx����ź��Ƿ񽻻���
                                                         1'b0��0/1ͨ��������
                                                         1'b1��0/1ͨ������ */
        unsigned int  t_ch_sw_abb_rx : 1;  /* bit[3]   : abb rx����ź��Ƿ񽻻���
                                                         1'b0��0/1ͨ��������
                                                         1'b1��0/1ͨ������ */
        unsigned int  t_ch_sw_pmu    : 1;  /* bit[4]   : pmu����ź��Ƿ񽻻���
                                                         1'b0��0/1ͨ��������
                                                         1'b1��0/1ͨ������ */
        unsigned int  t_ch_sw_apt    : 1;  /* bit[5]   : apt����ź��Ƿ񽻻���
                                                         1'b0��0/1ͨ��������
                                                         1'b1��0/1ͨ������ */
        unsigned int  reserved       : 26; /* bit[6-31]: ���� */
    } reg;
} BBPCOMM_T_CH_SW_UNION;
#define BBPCOMM_T_CH_SW_t_ch_sw_rf_START      (0)
#define BBPCOMM_T_CH_SW_t_ch_sw_rf_END        (0)
#define BBPCOMM_T_CH_SW_t_ch_sw_mipi_START    (1)
#define BBPCOMM_T_CH_SW_t_ch_sw_mipi_END      (1)
#define BBPCOMM_T_CH_SW_t_ch_sw_abb_tx_START  (2)
#define BBPCOMM_T_CH_SW_t_ch_sw_abb_tx_END    (2)
#define BBPCOMM_T_CH_SW_t_ch_sw_abb_rx_START  (3)
#define BBPCOMM_T_CH_SW_t_ch_sw_abb_rx_END    (3)
#define BBPCOMM_T_CH_SW_t_ch_sw_pmu_START     (4)
#define BBPCOMM_T_CH_SW_t_ch_sw_pmu_END       (4)
#define BBPCOMM_T_CH_SW_t_ch_sw_apt_START     (5)
#define BBPCOMM_T_CH_SW_t_ch_sw_apt_END       (5)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GM_CH_SW_UNION
 �ṹ˵��  : GM_CH_SW �Ĵ����ṹ���塣��ַƫ����:0x0B0C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gm_ch_sw_reg;
    struct
    {
        unsigned int  gm_ch_sw_rf     : 1;  /* bit[0]   : rf����ź��Ƿ񽻻���
                                                          1'b0��0/1ͨ��������
                                                          1'b1��0/1ͨ������ */
        unsigned int  gm_ch_sw_mipi   : 1;  /* bit[1]   : mipi����ź��Ƿ񽻻���
                                                          1'b0��0/1ͨ��������
                                                          1'b1��0/1ͨ������ */
        unsigned int  gm_ch_sw_abb_tx : 1;  /* bit[2]   : abb tx����ź��Ƿ񽻻���
                                                          1'b0��0/1ͨ��������
                                                          1'b1��0/1ͨ������ */
        unsigned int  gm_ch_sw_abb_rx : 1;  /* bit[3]   : abb rx����ź��Ƿ񽻻���
                                                          1'b0��0/1ͨ��������
                                                          1'b1��0/1ͨ������ */
        unsigned int  gm_ch_sw_pmu    : 1;  /* bit[4]   : pmu����ź��Ƿ񽻻���
                                                          1'b0��0/1ͨ��������
                                                          1'b1��0/1ͨ������ */
        unsigned int  gm_ch_sw_apt    : 1;  /* bit[5]   : apt����ź��Ƿ񽻻���
                                                          1'b0��0/1ͨ��������
                                                          1'b1��0/1ͨ������ */
        unsigned int  reserved        : 26; /* bit[6-31]: ���� */
    } reg;
} BBPCOMM_GM_CH_SW_UNION;
#define BBPCOMM_GM_CH_SW_gm_ch_sw_rf_START      (0)
#define BBPCOMM_GM_CH_SW_gm_ch_sw_rf_END        (0)
#define BBPCOMM_GM_CH_SW_gm_ch_sw_mipi_START    (1)
#define BBPCOMM_GM_CH_SW_gm_ch_sw_mipi_END      (1)
#define BBPCOMM_GM_CH_SW_gm_ch_sw_abb_tx_START  (2)
#define BBPCOMM_GM_CH_SW_gm_ch_sw_abb_tx_END    (2)
#define BBPCOMM_GM_CH_SW_gm_ch_sw_abb_rx_START  (3)
#define BBPCOMM_GM_CH_SW_gm_ch_sw_abb_rx_END    (3)
#define BBPCOMM_GM_CH_SW_gm_ch_sw_pmu_START     (4)
#define BBPCOMM_GM_CH_SW_gm_ch_sw_pmu_END       (4)
#define BBPCOMM_GM_CH_SW_gm_ch_sw_apt_START     (5)
#define BBPCOMM_GM_CH_SW_gm_ch_sw_apt_END       (5)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GS_CH_SW_UNION
 �ṹ˵��  : GS_CH_SW �Ĵ����ṹ���塣��ַƫ����:0x0B10����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gs_ch_sw_reg;
    struct
    {
        unsigned int  gs_ch_sw_rf     : 1;  /* bit[0]   : rf����ź��Ƿ񽻻���
                                                          1'b0��0/1ͨ��������
                                                          1'b1��0/1ͨ������ */
        unsigned int  gs_ch_sw_mipi   : 1;  /* bit[1]   : mipi����ź��Ƿ񽻻���
                                                          1'b0��0/1ͨ��������
                                                          1'b1��0/1ͨ������ */
        unsigned int  gs_ch_sw_abb_tx : 1;  /* bit[2]   : abb tx����ź��Ƿ񽻻���
                                                          1'b0��0/1ͨ��������
                                                          1'b1��0/1ͨ������ */
        unsigned int  gs_ch_sw_abb_rx : 1;  /* bit[3]   : abb rx����ź��Ƿ񽻻���
                                                          1'b0��0/1ͨ��������
                                                          1'b1��0/1ͨ������ */
        unsigned int  gs_ch_sw_pmu    : 1;  /* bit[4]   : pmu����ź��Ƿ񽻻���
                                                          1'b0��0/1ͨ��������
                                                          1'b1��0/1ͨ������ */
        unsigned int  gs_ch_sw_apt    : 1;  /* bit[5]   : apt����ź��Ƿ񽻻���
                                                          1'b0��0/1ͨ��������
                                                          1'b1��0/1ͨ������ */
        unsigned int  reserved        : 26; /* bit[6-31]: ���� */
    } reg;
} BBPCOMM_GS_CH_SW_UNION;
#define BBPCOMM_GS_CH_SW_gs_ch_sw_rf_START      (0)
#define BBPCOMM_GS_CH_SW_gs_ch_sw_rf_END        (0)
#define BBPCOMM_GS_CH_SW_gs_ch_sw_mipi_START    (1)
#define BBPCOMM_GS_CH_SW_gs_ch_sw_mipi_END      (1)
#define BBPCOMM_GS_CH_SW_gs_ch_sw_abb_tx_START  (2)
#define BBPCOMM_GS_CH_SW_gs_ch_sw_abb_tx_END    (2)
#define BBPCOMM_GS_CH_SW_gs_ch_sw_abb_rx_START  (3)
#define BBPCOMM_GS_CH_SW_gs_ch_sw_abb_rx_END    (3)
#define BBPCOMM_GS_CH_SW_gs_ch_sw_pmu_START     (4)
#define BBPCOMM_GS_CH_SW_gs_ch_sw_pmu_END       (4)
#define BBPCOMM_GS_CH_SW_gs_ch_sw_apt_START     (5)
#define BBPCOMM_GS_CH_SW_gs_ch_sw_apt_END       (5)


/*****************************************************************************
 �ṹ��    : BBPCOMM_L_TCVR_SEL0_UNION
 �ṹ˵��  : L_TCVR_SEL0 �Ĵ����ṹ���塣��ַƫ����:0x0B20����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      l_tcvr_sel0_reg;
    struct
    {
        unsigned int  l_tcvr_sel0 : 1;  /* bit[0]   : lteģ�����ͨ��0��tcvr_on�ź���Դ��
                                                      1'b0��������lte bbp
                                                      1'b1��������dsp����ֵ */
        unsigned int  reserved    : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_L_TCVR_SEL0_UNION;
#define BBPCOMM_L_TCVR_SEL0_l_tcvr_sel0_START  (0)
#define BBPCOMM_L_TCVR_SEL0_l_tcvr_sel0_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_L_TCVR_SEL1_UNION
 �ṹ˵��  : L_TCVR_SEL1 �Ĵ����ṹ���塣��ַƫ����:0x0B24����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      l_tcvr_sel1_reg;
    struct
    {
        unsigned int  l_tcvr_sel1 : 1;  /* bit[0]   : lteģ�����ͨ��1��tcvr_on�ź���Դ��
                                                      1'b0��������lte bbp
                                                      1'b1��������dsp����ֵ */
        unsigned int  reserved    : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_L_TCVR_SEL1_UNION;
#define BBPCOMM_L_TCVR_SEL1_l_tcvr_sel1_START  (0)
#define BBPCOMM_L_TCVR_SEL1_l_tcvr_sel1_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_T_TCVR_SEL0_UNION
 �ṹ˵��  : T_TCVR_SEL0 �Ĵ����ṹ���塣��ַƫ����:0x0B28����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      t_tcvr_sel0_reg;
    struct
    {
        unsigned int  t_tcvr_sel0 : 1;  /* bit[0]   : tdsģ�����ͨ��0��tcvr_on�ź���Դ��
                                                      1'b0��������tds bbp
                                                      1'b1��������dsp����ֵ */
        unsigned int  reserved    : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_T_TCVR_SEL0_UNION;
#define BBPCOMM_T_TCVR_SEL0_t_tcvr_sel0_START  (0)
#define BBPCOMM_T_TCVR_SEL0_t_tcvr_sel0_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_T_TCVR_SEL1_UNION
 �ṹ˵��  : T_TCVR_SEL1 �Ĵ����ṹ���塣��ַƫ����:0x0B2C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      t_tcvr_sel1_reg;
    struct
    {
        unsigned int  t_tcvr_sel1 : 1;  /* bit[0]   : tdsģ�����ͨ��1��tcvr_on�ź���Դ��
                                                      1'b0��������tds bbp
                                                      1'b1��������dsp����ֵ */
        unsigned int  reserved    : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_T_TCVR_SEL1_UNION;
#define BBPCOMM_T_TCVR_SEL1_t_tcvr_sel1_START  (0)
#define BBPCOMM_T_TCVR_SEL1_t_tcvr_sel1_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_W_TCVR_SEL0_UNION
 �ṹ˵��  : W_TCVR_SEL0 �Ĵ����ṹ���塣��ַƫ����:0x0B30����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      w_tcvr_sel0_reg;
    struct
    {
        unsigned int  w_tcvr_sel0 : 1;  /* bit[0]   : wcdmaģ�����ͨ��0��tcvr_on�ź���Դ��
                                                      1'b0��������wcdma bbp
                                                      1'b1��������dsp����ֵ */
        unsigned int  reserved    : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_W_TCVR_SEL0_UNION;
#define BBPCOMM_W_TCVR_SEL0_w_tcvr_sel0_START  (0)
#define BBPCOMM_W_TCVR_SEL0_w_tcvr_sel0_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_W_TCVR_SEL1_UNION
 �ṹ˵��  : W_TCVR_SEL1 �Ĵ����ṹ���塣��ַƫ����:0x0B34����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      w_tcvr_sel1_reg;
    struct
    {
        unsigned int  w_tcvr_sel1 : 1;  /* bit[0]   : wcdmaģ�����ͨ��1��tcvr_on�ź���Դ����
                                                      1'b0��������wcdma bbp
                                                      1'b1��������dsp����ֵ */
        unsigned int  reserved    : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_W_TCVR_SEL1_UNION;
#define BBPCOMM_W_TCVR_SEL1_w_tcvr_sel1_START  (0)
#define BBPCOMM_W_TCVR_SEL1_w_tcvr_sel1_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GM_TCVR_SEL0_UNION
 �ṹ˵��  : GM_TCVR_SEL0 �Ĵ����ṹ���塣��ַƫ����:0x0B38����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gm_tcvr_sel0_reg;
    struct
    {
        unsigned int  gm_tcvr_sel0 : 1;  /* bit[0]   : gsm��m�������ͨ��0��tcvr_on�ź���Դ��
                                                       1'b0��������gsm��m�� bbp
                                                       1'b1��������dsp����ֵ */
        unsigned int  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_GM_TCVR_SEL0_UNION;
#define BBPCOMM_GM_TCVR_SEL0_gm_tcvr_sel0_START  (0)
#define BBPCOMM_GM_TCVR_SEL0_gm_tcvr_sel0_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GM_TCVR_SEL1_UNION
 �ṹ˵��  : GM_TCVR_SEL1 �Ĵ����ṹ���塣��ַƫ����:0x0B3C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gm_tcvr_sel1_reg;
    struct
    {
        unsigned int  gm_tcvr_sel1 : 1;  /* bit[0]   : gsm��m�������ͨ��1��tcvr_on�ź���Դ��
                                                       1'b0��������gsm��m�� bbp
                                                       1'b1��������dsp����ֵ */
        unsigned int  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_GM_TCVR_SEL1_UNION;
#define BBPCOMM_GM_TCVR_SEL1_gm_tcvr_sel1_START  (0)
#define BBPCOMM_GM_TCVR_SEL1_gm_tcvr_sel1_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GS_TCVR_SEL0_UNION
 �ṹ˵��  : GS_TCVR_SEL0 �Ĵ����ṹ���塣��ַƫ����:0x0B40����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gs_tcvr_sel0_reg;
    struct
    {
        unsigned int  gs_tcvr_sel0 : 1;  /* bit[0]   : gsm��s�������ͨ��0��tcvr_on�ź���Դ��
                                                       1'b0��������gsm��s�� bbp
                                                       1'b1��������dsp����ֵ */
        unsigned int  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_GS_TCVR_SEL0_UNION;
#define BBPCOMM_GS_TCVR_SEL0_gs_tcvr_sel0_START  (0)
#define BBPCOMM_GS_TCVR_SEL0_gs_tcvr_sel0_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GS_TCVR_SEL1_UNION
 �ṹ˵��  : GS_TCVR_SEL1 �Ĵ����ṹ���塣��ַƫ����:0x0B44����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gs_tcvr_sel1_reg;
    struct
    {
        unsigned int  gs_tcvr_sel1 : 1;  /* bit[0]   : gsm��s�������ͨ��1��tcvr_on�ź���Դ��
                                                       1'b0��������gsm��s�� bbp
                                                       1'b1��������dsp����ֵ */
        unsigned int  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_GS_TCVR_SEL1_UNION;
#define BBPCOMM_GS_TCVR_SEL1_gs_tcvr_sel1_START  (0)
#define BBPCOMM_GS_TCVR_SEL1_gs_tcvr_sel1_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_L_TCVR_VALUE0_UNION
 �ṹ˵��  : L_TCVR_VALUE0 �Ĵ����ṹ���塣��ַƫ����:0x0B48����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      l_tcvr_value0_reg;
    struct
    {
        unsigned int  l_tcvr_value0 : 1;  /* bit[0]   : dsp���õ�lteģ�͸�ͨ��0 ��tcvr_onֵ */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_L_TCVR_VALUE0_UNION;
#define BBPCOMM_L_TCVR_VALUE0_l_tcvr_value0_START  (0)
#define BBPCOMM_L_TCVR_VALUE0_l_tcvr_value0_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_L_TCVR_VALUE1_UNION
 �ṹ˵��  : L_TCVR_VALUE1 �Ĵ����ṹ���塣��ַƫ����:0x0B4C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      l_tcvr_value1_reg;
    struct
    {
        unsigned int  l_tcvr_value1 : 1;  /* bit[0]   : dsp���õ�lteģ�͸�ͨ��1 ��tcvr_onֵ */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_L_TCVR_VALUE1_UNION;
#define BBPCOMM_L_TCVR_VALUE1_l_tcvr_value1_START  (0)
#define BBPCOMM_L_TCVR_VALUE1_l_tcvr_value1_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_T_TCVR_VALUE0_UNION
 �ṹ˵��  : T_TCVR_VALUE0 �Ĵ����ṹ���塣��ַƫ����:0x0B50����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      t_tcvr_value0_reg;
    struct
    {
        unsigned int  t_tcvr_value0 : 1;  /* bit[0]   : dsp���õ�tdsģ�͸�ͨ��0 ��tcvr_onֵ */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_T_TCVR_VALUE0_UNION;
#define BBPCOMM_T_TCVR_VALUE0_t_tcvr_value0_START  (0)
#define BBPCOMM_T_TCVR_VALUE0_t_tcvr_value0_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_T_TCVR_VALUE1_UNION
 �ṹ˵��  : T_TCVR_VALUE1 �Ĵ����ṹ���塣��ַƫ����:0x0B54����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      t_tcvr_value1_reg;
    struct
    {
        unsigned int  t_tcvr_value1 : 1;  /* bit[0]   : dsp���õ�tdsģ�͸�ͨ��1 ��tcvr_onֵ */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_T_TCVR_VALUE1_UNION;
#define BBPCOMM_T_TCVR_VALUE1_t_tcvr_value1_START  (0)
#define BBPCOMM_T_TCVR_VALUE1_t_tcvr_value1_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_W_TCVR_VALUE0_UNION
 �ṹ˵��  : W_TCVR_VALUE0 �Ĵ����ṹ���塣��ַƫ����:0x0B58����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      w_tcvr_value0_reg;
    struct
    {
        unsigned int  w_tcvr_value0 : 1;  /* bit[0]   : dsp���õ�wcdmaģ�͸�ͨ��0 ��tcvr_onֵ */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_W_TCVR_VALUE0_UNION;
#define BBPCOMM_W_TCVR_VALUE0_w_tcvr_value0_START  (0)
#define BBPCOMM_W_TCVR_VALUE0_w_tcvr_value0_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_W_TCVR_VALUE1_UNION
 �ṹ˵��  : W_TCVR_VALUE1 �Ĵ����ṹ���塣��ַƫ����:0x0B5C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      w_tcvr_value1_reg;
    struct
    {
        unsigned int  w_tcvr_value1 : 1;  /* bit[0]   : dsp���õ�wcdmaģ�͸�ͨ��1 ��tcvr_onֵ */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_W_TCVR_VALUE1_UNION;
#define BBPCOMM_W_TCVR_VALUE1_w_tcvr_value1_START  (0)
#define BBPCOMM_W_TCVR_VALUE1_w_tcvr_value1_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GM_TCVR_VALUE0_UNION
 �ṹ˵��  : GM_TCVR_VALUE0 �Ĵ����ṹ���塣��ַƫ����:0x0B60����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gm_tcvr_value0_reg;
    struct
    {
        unsigned int  gm_tcvr_value0 : 1;  /* bit[0]   : dsp���õ�gsm��m��ģ�͸�ͨ��0 ��tcvr_onֵ */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_GM_TCVR_VALUE0_UNION;
#define BBPCOMM_GM_TCVR_VALUE0_gm_tcvr_value0_START  (0)
#define BBPCOMM_GM_TCVR_VALUE0_gm_tcvr_value0_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GM_TCVR_VALUE1_UNION
 �ṹ˵��  : GM_TCVR_VALUE1 �Ĵ����ṹ���塣��ַƫ����:0x0B64����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gm_tcvr_value1_reg;
    struct
    {
        unsigned int  gm_tcvr_value1 : 1;  /* bit[0]   : dsp���õ�gsm��m��ģ�͸�ͨ��1��tcvr_onֵ */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_GM_TCVR_VALUE1_UNION;
#define BBPCOMM_GM_TCVR_VALUE1_gm_tcvr_value1_START  (0)
#define BBPCOMM_GM_TCVR_VALUE1_gm_tcvr_value1_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GS_TCVR_VALUE0_UNION
 �ṹ˵��  : GS_TCVR_VALUE0 �Ĵ����ṹ���塣��ַƫ����:0x0B68����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gs_tcvr_value0_reg;
    struct
    {
        unsigned int  gs_tcvr_value0 : 1;  /* bit[0]   : dsp���õ�gsm��s��ģ�͸�ͨ��0 ��tcvr_onֵ */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_GS_TCVR_VALUE0_UNION;
#define BBPCOMM_GS_TCVR_VALUE0_gs_tcvr_value0_START  (0)
#define BBPCOMM_GS_TCVR_VALUE0_gs_tcvr_value0_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GS_TCVR_VALUE1_UNION
 �ṹ˵��  : GS_TCVR_VALUE1 �Ĵ����ṹ���塣��ַƫ����:0x0B6C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gs_tcvr_value1_reg;
    struct
    {
        unsigned int  gs_tcvr_value1 : 1;  /* bit[0]   : dsp���õ�gsm��s��ģ�͸�ͨ��1 ��tcvr_onֵ */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_GS_TCVR_VALUE1_UNION;
#define BBPCOMM_GS_TCVR_VALUE1_gs_tcvr_value1_START  (0)
#define BBPCOMM_GS_TCVR_VALUE1_gs_tcvr_value1_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_RF_TCVR_STATE_UNION
 �ṹ˵��  : RF_TCVR_STATE �Ĵ����ṹ���塣��ַƫ����:0x0B70����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      rf_tcvr_state_reg;
    struct
    {
        unsigned int  l_tcvr_state0  : 1;  /* bit[0]    : lte bbp�����ͨ��0 tcvr_on�ź�״̬ */
        unsigned int  l_tcvr_state1  : 1;  /* bit[1]    : lte bbp�����ͨ��1 tcvr_on�ź�״̬ */
        unsigned int  t_tcvr_state0  : 1;  /* bit[2]    : tds bbp�����ͨ��0 tcvr_on�ź�״̬ */
        unsigned int  reserved_0     : 1;  /* bit[3]    : ���� */
        unsigned int  w_tcvr_state0  : 1;  /* bit[4]    : wcdma bbp�����ͨ��0 tcvr_on�ź�״̬ */
        unsigned int  reserved_1     : 1;  /* bit[5]    : ���� */
        unsigned int  gm_tcvr_state0 : 1;  /* bit[6]    : gsm��m�� bbp�����ͨ��0 tcvr_on�ź�״̬ */
        unsigned int  reserved_2     : 1;  /* bit[7]    : ���� */
        unsigned int  gs_tcvr_state0 : 1;  /* bit[8]    : gsm��s�� bbp�����ͨ��0 tcvr_on�ź�״̬ */
        unsigned int  reserved_3     : 1;  /* bit[9]    : ���� */
        unsigned int  c_tcvr_state0  : 1;  /* bit[10]   : c bbp�����ͨ��0 tcvr_on�ź�״̬ */
        unsigned int  reserved_4     : 5;  /* bit[11-15]: ���� */
        unsigned int  ch_tcvr_state0 : 1;  /* bit[16]   : ͨ��0 ���������tcvr_on�ź�״̬ */
        unsigned int  ch_tcvr_state1 : 1;  /* bit[17]   : ͨ��1 ���������tcvr_on�ź�״̬ */
        unsigned int  ch_tcvr_state2 : 1;  /* bit[18]   : ͨ��2 ���������tcvr_on�ź�״̬ */
        unsigned int  reserved_5     : 13; /* bit[19-31]: ���� */
    } reg;
} BBPCOMM_RF_TCVR_STATE_UNION;
#define BBPCOMM_RF_TCVR_STATE_l_tcvr_state0_START   (0)
#define BBPCOMM_RF_TCVR_STATE_l_tcvr_state0_END     (0)
#define BBPCOMM_RF_TCVR_STATE_l_tcvr_state1_START   (1)
#define BBPCOMM_RF_TCVR_STATE_l_tcvr_state1_END     (1)
#define BBPCOMM_RF_TCVR_STATE_t_tcvr_state0_START   (2)
#define BBPCOMM_RF_TCVR_STATE_t_tcvr_state0_END     (2)
#define BBPCOMM_RF_TCVR_STATE_w_tcvr_state0_START   (4)
#define BBPCOMM_RF_TCVR_STATE_w_tcvr_state0_END     (4)
#define BBPCOMM_RF_TCVR_STATE_gm_tcvr_state0_START  (6)
#define BBPCOMM_RF_TCVR_STATE_gm_tcvr_state0_END    (6)
#define BBPCOMM_RF_TCVR_STATE_gs_tcvr_state0_START  (8)
#define BBPCOMM_RF_TCVR_STATE_gs_tcvr_state0_END    (8)
#define BBPCOMM_RF_TCVR_STATE_c_tcvr_state0_START   (10)
#define BBPCOMM_RF_TCVR_STATE_c_tcvr_state0_END     (10)
#define BBPCOMM_RF_TCVR_STATE_ch_tcvr_state0_START  (16)
#define BBPCOMM_RF_TCVR_STATE_ch_tcvr_state0_END    (16)
#define BBPCOMM_RF_TCVR_STATE_ch_tcvr_state1_START  (17)
#define BBPCOMM_RF_TCVR_STATE_ch_tcvr_state1_END    (17)
#define BBPCOMM_RF_TCVR_STATE_ch_tcvr_state2_START  (18)
#define BBPCOMM_RF_TCVR_STATE_ch_tcvr_state2_END    (18)


/*****************************************************************************
 �ṹ��    : BBPCOMM_MIPI_UNBIND_EN_UNION
 �ṹ˵��  : MIPI_UNBIND_EN �Ĵ����ṹ���塣��ַƫ����:0x0B90����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      mipi_unbind_en_reg;
    struct
    {
        unsigned int  mipi_unbind_en : 1;  /* bit[0]   : mipiͨ������ʹ�ܣ�
                                                         1'b0��ͨ����
                                                         1'b1��ͨ������ */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_MIPI_UNBIND_EN_UNION;
#define BBPCOMM_MIPI_UNBIND_EN_mipi_unbind_en_START  (0)
#define BBPCOMM_MIPI_UNBIND_EN_mipi_unbind_en_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_MIPI_CH_SEL0_UNION
 �ṹ˵��  : MIPI_CH_SEL0 �Ĵ����ṹ���塣��ַƫ����:0x0B94����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      mipi_ch_sel0_reg;
    struct
    {
        unsigned int  mipi_ch_sel0 : 1;  /* bit[0]   : ͨ��0ӳ��mipi������ϵ��
                                                       1'b0��ͨ��0ӳ�䵽mipi0
                                                       1'b1��ͨ��0ӳ�䵽mipi1 */
        unsigned int  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_MIPI_CH_SEL0_UNION;
#define BBPCOMM_MIPI_CH_SEL0_mipi_ch_sel0_START  (0)
#define BBPCOMM_MIPI_CH_SEL0_mipi_ch_sel0_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_MIPI_CH_SEL1_UNION
 �ṹ˵��  : MIPI_CH_SEL1 �Ĵ����ṹ���塣��ַƫ����:0x0B98����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      mipi_ch_sel1_reg;
    struct
    {
        unsigned int  mipi_ch_sel1 : 1;  /* bit[0]   : ͨ��1ӳ��mipi������ϵ��
                                                       1'b0��ͨ��1ӳ�䵽mipi0
                                                       1'b1��ͨ��1ӳ�䵽mipi1 */
        unsigned int  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_MIPI_CH_SEL1_UNION;
#define BBPCOMM_MIPI_CH_SEL1_mipi_ch_sel1_START  (0)
#define BBPCOMM_MIPI_CH_SEL1_mipi_ch_sel1_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_APT_CH_SEL0_UNION
 �ṹ˵��  : APT_CH_SEL0 �Ĵ����ṹ���塣��ַƫ����:0x0B9C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      apt_ch_sel0_reg;
    struct
    {
        unsigned int  apt_ch_sel0 : 2;  /* bit[0-1] : apt_pdm0/apt_vpen0�ź���Դ��
                                                      2'd0��������ͨ��0
                                                      2'd1��������ͨ��1
                                                      2'd2��������ͨ��2
                                                      2'd3��ǿ�Ƶ͵�ƽ��� */
        unsigned int  reserved    : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_APT_CH_SEL0_UNION;
#define BBPCOMM_APT_CH_SEL0_apt_ch_sel0_START  (0)
#define BBPCOMM_APT_CH_SEL0_apt_ch_sel0_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_APT_CH_SEL1_UNION
 �ṹ˵��  : APT_CH_SEL1 �Ĵ����ṹ���塣��ַƫ����:0x0BA0����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      apt_ch_sel1_reg;
    struct
    {
        unsigned int  apt_ch_sel1 : 2;  /* bit[0-1] : apt_pdm1/apt_vpen1�ź���Դ��
                                                      2'd0��������ͨ��0
                                                      2'd1��������ͨ��1
                                                      2'd2��������ͨ��2
                                                      2'd3��ǿ�Ƶ͵�ƽ��� */
        unsigned int  reserved    : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_APT_CH_SEL1_UNION;
#define BBPCOMM_APT_CH_SEL1_apt_ch_sel1_START  (0)
#define BBPCOMM_APT_CH_SEL1_apt_ch_sel1_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_AFC_CH_SEL0_UNION
 �ṹ˵��  : AFC_CH_SEL0 �Ĵ����ṹ���塣��ַƫ����:0x0BA4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      afc_ch_sel0_reg;
    struct
    {
        unsigned int  afc_ch_sel0 : 2;  /* bit[0-1] : afc pdm0�ź���Դ��
                                                      2'd0��������ͨ��0
                                                      2'd1��������ͨ��1
                                                      2'd2��������ͨ��2
                                                      2'd3��ǿ�Ƶ͵�ƽ��� */
        unsigned int  reserved    : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_AFC_CH_SEL0_UNION;
#define BBPCOMM_AFC_CH_SEL0_afc_ch_sel0_START  (0)
#define BBPCOMM_AFC_CH_SEL0_afc_ch_sel0_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_AFC_CH_SEL1_UNION
 �ṹ˵��  : AFC_CH_SEL1 �Ĵ����ṹ���塣��ַƫ����:0x0BA8����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      afc_ch_sel1_reg;
    struct
    {
        unsigned int  afc_ch_sel1 : 2;  /* bit[0-1] : afc pdm1�ź���Դ��
                                                      2'd0��������ͨ��0
                                                      2'd1��������ͨ��1
                                                      2'd2��������ͨ��2
                                                      2'd3��ǿ�Ƶ͵�ƽ��� */
        unsigned int  reserved    : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_AFC_CH_SEL1_UNION;
#define BBPCOMM_AFC_CH_SEL1_afc_ch_sel1_START  (0)
#define BBPCOMM_AFC_CH_SEL1_afc_ch_sel1_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_ABB_TX_CH_SEL0_UNION
 �ṹ˵��  : ABB_TX_CH_SEL0 �Ĵ����ṹ���塣��ַƫ����:0x0BAC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      abb_tx_ch_sel0_reg;
    struct
    {
        unsigned int  abb_tx_ch_sel0 : 1;  /* bit[0]   : ���� */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_ABB_TX_CH_SEL0_UNION;
#define BBPCOMM_ABB_TX_CH_SEL0_abb_tx_ch_sel0_START  (0)
#define BBPCOMM_ABB_TX_CH_SEL0_abb_tx_ch_sel0_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_ABB_TX_CH_SEL1_UNION
 �ṹ˵��  : ABB_TX_CH_SEL1 �Ĵ����ṹ���塣��ַƫ����:0x0BB0����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      abb_tx_ch_sel1_reg;
    struct
    {
        unsigned int  abb_tx_ch_sel1 : 1;  /* bit[0]   : ���� */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_ABB_TX_CH_SEL1_UNION;
#define BBPCOMM_ABB_TX_CH_SEL1_abb_tx_ch_sel1_START  (0)
#define BBPCOMM_ABB_TX_CH_SEL1_abb_tx_ch_sel1_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_PMU_CH_SEL0_UNION
 �ṹ˵��  : PMU_CH_SEL0 �Ĵ����ṹ���塣��ַƫ����:0x0BB4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      pmu_ch_sel0_reg;
    struct
    {
        unsigned int  pmu_ch_sel0 : 2;  /* bit[0-1] : auxdac0�ź���Դ��
                                                      2'd0��������ͨ��0
                                                      2'd1��������ͨ��1
                                                      2'd2��������ͨ��2
                                                      2'd3��ǿ�Ƶ͵�ƽ��� */
        unsigned int  reserved    : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_PMU_CH_SEL0_UNION;
#define BBPCOMM_PMU_CH_SEL0_pmu_ch_sel0_START  (0)
#define BBPCOMM_PMU_CH_SEL0_pmu_ch_sel0_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_PMU_CH_SEL1_UNION
 �ṹ˵��  : PMU_CH_SEL1 �Ĵ����ṹ���塣��ַƫ����:0x0BB8����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      pmu_ch_sel1_reg;
    struct
    {
        unsigned int  pmu_ch_sel1 : 2;  /* bit[0-1] : auxdac1�ź���Դ��
                                                      2'd0��������ͨ��0
                                                      2'd1��������ͨ��1
                                                      2'd2��������ͨ��2
                                                      2'd3��ǿ�Ƶ͵�ƽ��� */
        unsigned int  reserved    : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_PMU_CH_SEL1_UNION;
#define BBPCOMM_PMU_CH_SEL1_pmu_ch_sel1_START  (0)
#define BBPCOMM_PMU_CH_SEL1_pmu_ch_sel1_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_VALID_NUM_UNION
 �ṹ˵��  : VALID_NUM �Ĵ����ṹ���塣��ַƫ����:0x0BC0����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      valid_num_reg;
    struct
    {
        unsigned int  valid_num : 16; /* bit[0-15] : ���� */
        unsigned int  reserved  : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_VALID_NUM_UNION;
#define BBPCOMM_VALID_NUM_valid_num_START  (0)
#define BBPCOMM_VALID_NUM_valid_num_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_VALID_NUM1_UNION
 �ṹ˵��  : VALID_NUM1 �Ĵ����ṹ���塣��ַƫ����:0x0BC4����ֵ:0x00010001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      valid_num1_reg;
    struct
    {
        unsigned int  valid_num1 : 16; /* bit[0-15] : ���� */
        unsigned int  valid_num2 : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_VALID_NUM1_UNION;
#define BBPCOMM_VALID_NUM1_valid_num1_START  (0)
#define BBPCOMM_VALID_NUM1_valid_num1_END    (15)
#define BBPCOMM_VALID_NUM1_valid_num2_START  (16)
#define BBPCOMM_VALID_NUM1_valid_num2_END    (31)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_LTE_RCV_C_UNION
 �ṹ˵��  : INT_CLEAR_LTE_RCV_C �Ĵ����ṹ���塣��ַƫ����:0x0C00����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_lte_rcv_c_reg;
    struct
    {
        unsigned int  int_clear_lte_rcv_c : 16; /* bit[0-15] : �߼������㡣
                                                               �жϱ�־���ָʾ������Ч���������INT_TYPE_LTE_RCV_C[15:0]��Ӧbitλ
                                                               ��Чʱ�̣�������Ч */
        unsigned int  reserved            : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_LTE_RCV_C_UNION;
#define BBPCOMM_INT_CLEAR_LTE_RCV_C_int_clear_lte_rcv_c_START  (0)
#define BBPCOMM_INT_CLEAR_LTE_RCV_C_int_clear_lte_rcv_c_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_LTE_RCV_C_UNION
 �ṹ˵��  : INT_MASK_LTE_RCV_C �Ĵ����ṹ���塣��ַƫ����:0x0C04����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_lte_rcv_c_reg;
    struct
    {
        unsigned int  int_mask_lte_rcv_c : 16; /* bit[0-15] : �ж����α�־����������INT_TYPE_LTE_RCV_C[15:0]��Ӧbit�жϡ�
                                                              0�������ж��ϱ���
                                                              1��ʹ���ж��ϱ���
                                                              ����ʱ�̣���ʼ��
                                                              ��Чʱ�̣�������Ч */
        unsigned int  reserved           : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_LTE_RCV_C_UNION;
#define BBPCOMM_INT_MASK_LTE_RCV_C_int_mask_lte_rcv_c_START  (0)
#define BBPCOMM_INT_MASK_LTE_RCV_C_int_mask_lte_rcv_c_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_LTE_RCV_C_UNION
 �ṹ˵��  : INT_TYPE_LTE_RCV_C �Ĵ����ṹ���塣��ַƫ����:0x0C08����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_lte_rcv_c_reg;
    struct
    {
        unsigned int  o_int_type_lte_rcv_c : 16; /* bit[0-15] : �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
                                                                [0]: �ж�����0�� C����ģ����ǰ֪ͨLTE��ϵͳ���������жϡ�
                                                                [1]: �ж�����1�� C����ģ����GAP�жϣ�֪ͨLTE������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
                                                                [2]: �ж�����2��C����ģ����GAP�жϡ�
                                                                [3]: �ж�����3��C����ģ�����������жϡ�
                                                                [4]: �ж�����4��C����ģ��ǿ��C�˳���ϵͳ�����жϡ�
                                                                [5]: �ж�����5��C����ģ��֪ͨC�ϱ����β��������
                                                                [6]: ������
                                                                [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
                                                                �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x0A84��int_mask_lte_rcv_c���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved             : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_LTE_RCV_C_UNION;
#define BBPCOMM_INT_TYPE_LTE_RCV_C_o_int_type_lte_rcv_c_START  (0)
#define BBPCOMM_INT_TYPE_LTE_RCV_C_o_int_type_lte_rcv_c_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_LTE_SND_C_INT_13_UNION
 �ṹ˵��  : LTE_SND_C_INT_13 �Ĵ����ṹ���塣��ַƫ����:0x0C0C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      lte_snd_c_int_13_reg;
    struct
    {
        unsigned int  reserved_0       : 3;  /* bit[0-2]  : ���� */
        unsigned int  lte_snd_c_int_13 : 13; /* bit[3-15] : �߼������㡣����Ч��
                                                            
                                                            bit15~7����Ӧlte_snd_c_int_15 ~ 7��
                                                            LPHYͨ���˼Ĵ�����������15~7�жϣ�int_type_c_rcv_lte[15:7]����CPHY��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit6����Ӧlte_snd_c_int_6��
                                                            LPHYͨ���˼Ĵ�����������6�жϣ�int_type_lte_rcv_c[6]����LPHY��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit5����Ӧc_snd_lte_int_5��
                                                            L��ģʱ֪ͨLPHY L�������ڵ������Ч��
                                                            LPHYͨ���˼Ĵ�����������5�жϣ�int_type_c_rcv_lte[5]����LPHY��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit4����Ӧlte_snd_c_int_4��
                                                            L��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
                                                            LPHYͨ���˼Ĵ�����������4�жϣ�int_type_c_rcv_lte[4]����CPHY��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit3����Ӧlte_snd_c_int_3��L��������ָʾ������Ч��
                                                            ���ڴ����ж�����3 ��int_type_c_rcv_lte[3]����CPHY��C��ģ�¶�L������ϵͳ����ʱ�����L����������LPHY���ô˱�־Ϊ1�� 
                                                            ��Чʱ�̣�������Ч */
        unsigned int  reserved_1       : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_LTE_SND_C_INT_13_UNION;
#define BBPCOMM_LTE_SND_C_INT_13_lte_snd_c_int_13_START  (3)
#define BBPCOMM_LTE_SND_C_INT_13_lte_snd_c_int_13_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C_SND_C_INT_13_UNION
 �ṹ˵��  : C_SND_C_INT_13 �Ĵ����ṹ���塣��ַƫ����:0x0C10����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c_snd_c_int_13_reg;
    struct
    {
        unsigned int  reserved_0     : 3;  /* bit[0-2]  : ���� */
        unsigned int  c_snd_c_int_13 : 13; /* bit[3-15] : �߼������㡣����Ч��
                                                          
                                                          bit15~7����Ӧc_snd_c_int_15 ~ 7��
                                                          C DSPͨ���˼Ĵ�����������15~7�жϣ�int_type_c_rcv_c[15:7]����C DSP��
                                                          ��Чʱ�̣�������Ч
                                                          
                                                          bit6����Ӧc_snd_c_int_6��
                                                          CDSPͨ���˼Ĵ�����������6�жϣ�int_type_c_rcv_c[6]����CDSP��
                                                          ��Чʱ�̣�������Ч
                                                          
                                                          bit5����Ӧc_snd_c_int_5��
                                                          C��ģʱ֪ͨCDSP C�������ڵ������Ч��
                                                          C DSPͨ���˼Ĵ�����������5�жϣ�int_type_c_rcv_c[5]����CDSP��
                                                          ��Чʱ�̣�������Ч
                                                          
                                                          bit4����Ӧc_snd_c_int_4��
                                                          C��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
                                                          C DSPͨ���˼Ĵ�����������4�жϣ�int_type_c_rcv_c[4]����CDSP��
                                                          ��Чʱ�̣�������Ч
                                                          
                                                          bit3����Ӧc_snd_c_int_3��C��������ָʾ������Ч��
                                                          ���ڴ����ж�����3 ��int_type_c_rcv_c[3]����CDSP��C��ģ�¶�C������ϵͳ����ʱ�����C����������C DSP���ô˱�־Ϊ1�� 
                                                          ��Чʱ�̣�������Ч */
        unsigned int  reserved_1     : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_C_SND_C_INT_13_UNION;
#define BBPCOMM_C_SND_C_INT_13_c_snd_c_int_13_START  (3)
#define BBPCOMM_C_SND_C_INT_13_c_snd_c_int_13_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CBBP_INPUT_MASK_UNION
 �ṹ˵��  : CBBP_INPUT_MASK �Ĵ����ṹ���塣��ַƫ����:0x0C14����ֵ:0x00000003�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      cbbp_input_mask_reg;
    struct
    {
        unsigned int  cbbp_input_mask : 2;  /* bit[0-1] : ��ƽ�źţ�����Ч��
                                                          ��C��ģ��Ҫ����ϵͳ����ʱ�����ñ��Ĵ���Ϊ3����ϵͳ�������������ñ��Ĵ���Ϊ0��
                                                          bit1:1��b0:
                                                           ��c_intrasys_valid������Ч����ǿ��Ϊ1��
                                                          bit0:1��b0:
                                                          c_intersys_ingap_pre_ind������Ч����ǿ��Ϊ0��
                                                          bit[1:0] = 11b: ��c_intrasys_valid��c_intersys_ingap_pre_ind������Ч��
                                                          ����ʱ�̣�TDS��ģ��Ҫ����ϵͳ����ʱ�����ñ��Ĵ���Ϊ3����ϵͳ�������������ñ��Ĵ���Ϊ0��
                                                          ��Чʱ�̣�������Ч */
        unsigned int  reserved        : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_CBBP_INPUT_MASK_UNION;
#define BBPCOMM_CBBP_INPUT_MASK_cbbp_input_mask_START  (0)
#define BBPCOMM_CBBP_INPUT_MASK_cbbp_input_mask_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C_TIMING_DSP_UNION
 �ṹ˵��  : C_TIMING_DSP �Ĵ����ṹ���塣��ַƫ����:0x0C20����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c_timing_dsp_reg;
    struct
    {
        unsigned int  o_c_timing1_dsp : 30; /* bit[0-29] : Cģ��ʱ��Ϣ�ϱ���  */
        unsigned int  reserved        : 2;  /* bit[30-31]: ���� */
    } reg;
} BBPCOMM_C_TIMING_DSP_UNION;
#define BBPCOMM_C_TIMING_DSP_o_c_timing1_dsp_START  (0)
#define BBPCOMM_C_TIMING_DSP_o_c_timing1_dsp_END    (29)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C_INTRASYS_VALID_UNION
 �ṹ˵��  : C_INTRASYS_VALID �Ĵ����ṹ���塣��ַƫ����:0x0C24����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c_intrasys_valid_reg;
    struct
    {
        unsigned int  o_c_intrasys_valid       : 1;  /* bit[0]   : C��ģ�¿���RFָʾ����ƽ�źš�
                                                                   1��b0: C����RF����Ȩ��
                                                                   1��b1: C���п���RFȨ����ʵ������RF��c_intrasys_valid_delay�ź�Ϊ1���� */
        unsigned int  o_c_intrasys_valid_delay : 1;  /* bit[1]   : C��ģ��ʵ�ʿ���RFָʾ����ƽ�źš�Ϊ1����W����RF����ͨ����Ϊ0�����ģ���Կ���RFͨ�������ڵ�RFICʱ��Ƶ��������źŵ�ѡͨ��
                                                                   c_intrasys_valid_delay�������ر�c_intrasys_valid�������ͺ��½���һ�¡� */
        unsigned int  reserved                 : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_C_INTRASYS_VALID_UNION;
#define BBPCOMM_C_INTRASYS_VALID_o_c_intrasys_valid_START        (0)
#define BBPCOMM_C_INTRASYS_VALID_o_c_intrasys_valid_END          (0)
#define BBPCOMM_C_INTRASYS_VALID_o_c_intrasys_valid_delay_START  (1)
#define BBPCOMM_C_INTRASYS_VALID_o_c_intrasys_valid_delay_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C_INTERSYS_MEASURE_TYPE_UNION
 �ṹ˵��  : C_INTERSYS_MEASURE_TYPE �Ĵ����ṹ���塣��ַƫ����:0x0C28����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c_intersys_measure_type_reg;
    struct
    {
        unsigned int  c_intersys_measure_type : 4;  /* bit[0-3] : ��ϵͳ�������͡�
                                                                  4��b0������C��
                                                                  4��b1: C�����ѣ�
                                                                  ����Ԥ����
                                                                  ��Чʱ�̣�������Ч */
        unsigned int  reserved                : 28; /* bit[4-31]: ���� */
    } reg;
} BBPCOMM_C_INTERSYS_MEASURE_TYPE_UNION;
#define BBPCOMM_C_INTERSYS_MEASURE_TYPE_c_intersys_measure_type_START  (0)
#define BBPCOMM_C_INTERSYS_MEASURE_TYPE_c_intersys_measure_type_END    (3)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C_MEASURE_REPORT_VALID_UNION
 �ṹ˵��  : C_MEASURE_REPORT_VALID �Ĵ����ṹ���塣��ַƫ����:0x0C2C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c_measure_report_valid_reg;
    struct
    {
        unsigned int  c_measure_report_valid : 1;  /* bit[0-0] : ��Ƶ��������ڵ�ָʾ��L����TDS/Gm/Gs/U��Ϊ��ģ��֪ͨCPHY W�����ĵ�Ƶ�����ڵ��
                                                                 ֻ������̬����Ҫ���á�
                                                                 ��ƽ�źţ�����Ч��
                                                                 ��Чʱ�̣�������Ч */
        unsigned int  reserved               : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_C_MEASURE_REPORT_VALID_UNION;
#define BBPCOMM_C_MEASURE_REPORT_VALID_c_measure_report_valid_START  (0)
#define BBPCOMM_C_MEASURE_REPORT_VALID_c_measure_report_valid_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_C_RCV_LTE_UNION
 �ṹ˵��  : INT_CLEAR_C_RCV_LTE �Ĵ����ṹ���塣��ַƫ����:0x0C38����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_c_rcv_lte_reg;
    struct
    {
        unsigned int  int_clear_c_rcv_lte : 16; /* bit[0-15] : �߼������㡣
                                                               �жϱ�־���ָʾ������Ч���������INT_TYPE_C_RCV_LTE[15:0]��Ӧbitλ
                                                               ��Чʱ�̣�������Ч */
        unsigned int  reserved            : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_C_RCV_LTE_UNION;
#define BBPCOMM_INT_CLEAR_C_RCV_LTE_int_clear_c_rcv_lte_START  (0)
#define BBPCOMM_INT_CLEAR_C_RCV_LTE_int_clear_c_rcv_lte_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_C_RCV_C_UNION
 �ṹ˵��  : INT_CLEAR_C_RCV_C �Ĵ����ṹ���塣��ַƫ����:0x0C3C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_c_rcv_c_reg;
    struct
    {
        unsigned int  int_clear_c_rcv_c : 16; /* bit[0-15] : �߼������㡣
                                                             �жϱ�־���ָʾ������Ч���������INT_TYPE_C_RCV_C[15:0]��Ӧbitλ
                                                             ��Чʱ�̣�������Ч */
        unsigned int  reserved          : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_C_RCV_C_UNION;
#define BBPCOMM_INT_CLEAR_C_RCV_C_int_clear_c_rcv_c_START  (0)
#define BBPCOMM_INT_CLEAR_C_RCV_C_int_clear_c_rcv_c_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_CLEAR_C_INT012_UNION
 �ṹ˵��  : INT_CLEAR_C_INT012 �Ĵ����ṹ���塣��ַƫ����:0x0C40����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_c_int012_reg;
    struct
    {
        unsigned int  int_clear_c_int012 : 3;  /* bit[0-2] : �߼������㡣
                                                             �жϱ�־���ָʾ������Ч���������INT_TYPE_C_INT012[2:0]��Ӧbitλ
                                                             ��Чʱ�̣�������Ч */
        unsigned int  reserved           : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_INT_CLEAR_C_INT012_UNION;
#define BBPCOMM_INT_CLEAR_C_INT012_int_clear_c_int012_START  (0)
#define BBPCOMM_INT_CLEAR_C_INT012_int_clear_c_int012_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_C_RCV_LTE_UNION
 �ṹ˵��  : INT_MASK_C_RCV_LTE �Ĵ����ṹ���塣��ַƫ����:0x0C44����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_c_rcv_lte_reg;
    struct
    {
        unsigned int  int_mask_c_rcv_lte : 16; /* bit[0-15] : �ж����α�־����������INT_TYPE_C_RCV_LTE[15:0]��Ӧbit�жϡ�
                                                              0�������ж��ϱ���
                                                              1��ʹ���ж��ϱ���
                                                              ����ʱ�̣���ʼ��
                                                              ��Чʱ�̣�������Ч */
        unsigned int  reserved           : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_C_RCV_LTE_UNION;
#define BBPCOMM_INT_MASK_C_RCV_LTE_int_mask_c_rcv_lte_START  (0)
#define BBPCOMM_INT_MASK_C_RCV_LTE_int_mask_c_rcv_lte_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_C_RCV_C_UNION
 �ṹ˵��  : INT_MASK_C_RCV_C �Ĵ����ṹ���塣��ַƫ����:0x0C48����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_c_rcv_c_reg;
    struct
    {
        unsigned int  int_mask_c_rcv_c : 16; /* bit[0-15] : �ж����α�־����������INT_TYPE_C_RCV_C[15:0]��Ӧbit�жϡ�
                                                            0�������ж��ϱ���
                                                            1��ʹ���ж��ϱ���
                                                            ����ʱ�̣���ʼ��
                                                            ��Чʱ�̣�������Ч */
        unsigned int  reserved         : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_C_RCV_C_UNION;
#define BBPCOMM_INT_MASK_C_RCV_C_int_mask_c_rcv_c_START  (0)
#define BBPCOMM_INT_MASK_C_RCV_C_int_mask_c_rcv_c_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_MASK_C_INT012_UNION
 �ṹ˵��  : INT_MASK_C_INT012 �Ĵ����ṹ���塣��ַƫ����:0x0C4C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_c_int012_reg;
    struct
    {
        unsigned int  int_mask_c_int012 : 3;  /* bit[0-2] : �ж����α�־����������INT_TYPE_C_INT012[2:0]��Ӧbit�жϡ�
                                                            0�������ж��ϱ���
                                                            1��ʹ���ж��ϱ���
                                                            ����ʱ�̣���ʼ��
                                                            ��Чʱ�̣�������Ч */
        unsigned int  reserved          : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_INT_MASK_C_INT012_UNION;
#define BBPCOMM_INT_MASK_C_INT012_int_mask_c_int012_START  (0)
#define BBPCOMM_INT_MASK_C_INT012_int_mask_c_int012_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_C_RCV_LTE_UNION
 �ṹ˵��  : INT_TYPE_C_RCV_LTE �Ĵ����ṹ���塣��ַƫ����:0x0C50����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_c_rcv_lte_reg;
    struct
    {
        unsigned int  o_int_type_c_rcv_lte : 16; /* bit[0-15] : �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
                                                                [0]: �ж�����0�� LTE����ģ����ǰ֪ͨC��ϵͳ���������жϡ�
                                                                [1]: �ж�����1�� LTE����ģ����GAP�жϣ�֪ͨC������ϵͳ������Ƶͨ�����ã������л��Ȳ�����
                                                                [2]: �ж�����2�� LTE����ģ����GAP�жϡ�
                                                                [3]: �ж�����3��LTE����ģ�����������жϡ�
                                                                [4]: �ж�����4��LTE����ģ��ǿ��C�˳���ϵͳ�����жϡ�
                                                                [5]: �ж�����5��LTE����ģ��֪ͨC�ϱ����β��������
                                                                [6]: ������
                                                                [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
                                                                �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x0B34��int_mask_c_rcv_lte���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved             : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_C_RCV_LTE_UNION;
#define BBPCOMM_INT_TYPE_C_RCV_LTE_o_int_type_c_rcv_lte_START  (0)
#define BBPCOMM_INT_TYPE_C_RCV_LTE_o_int_type_c_rcv_lte_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_C_RCV_C_UNION
 �ṹ˵��  : INT_TYPE_C_RCV_C �Ĵ����ṹ���塣��ַƫ����:0x0C54����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_c_rcv_c_reg;
    struct
    {
        unsigned int  o_int_type_c_rcv_c : 16; /* bit[0-15] : �ж�״̬��־����bit������Ӧһ���ж����ͣ�����Ч��
                                                              [0]: �ж�����0��C����ģ����ǰ֪ͨLTE��Ƶ���������жϡ�
                                                              [1]: �ж�����1��C����ģ����GAP�жϣ�֪ͨC������Ƶ������Ƶͨ�����ã������л��Ȳ�����
                                                              [2]: �ж�����2��C����ģ����GAP�жϡ�
                                                              [3]: �ж�����3��C����ģ������Ƶ�����������жϡ�
                                                              [4]: �ж�����4��C����ģ��ǿ��C�˳���Ƶ�����жϡ�
                                                              [5]: �ж�����5��C����ģ��֪ͨC�ϱ����β��������
                                                              [6]: �ж�����6��������
                                                              [15:7]: ��Ӧ�ж�����[15:7]��Ԥ����
                                                              �ж�״̬��־0��1��2ֻ�е�LTE������ģʱ���ܲ�����
                                                              �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x0B38��int_mask_c_rcv_c���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved           : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_C_RCV_C_UNION;
#define BBPCOMM_INT_TYPE_C_RCV_C_o_int_type_c_rcv_c_START  (0)
#define BBPCOMM_INT_TYPE_C_RCV_C_o_int_type_c_rcv_c_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_INT_TYPE_C_INT012_UNION
 �ṹ˵��  : INT_TYPE_C_INT012 �Ĵ����ṹ���塣��ַƫ����:0x0C58����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      int_type_c_int012_reg;
    struct
    {
        unsigned int  o_int_type_c_int012 : 3;  /* bit[0-2] : ������ģ����int0��1��2���ϱ���(������Ƶ����ϵͳ����)��������Ч��
                                                              [0]: C��ģʱ��CTU����֪ͨCPHY����int0�жϡ�
                                                              [1]: C��ģʱ��CTU����֪ͨCPHY����int1�жϡ�
                                                              [2]:CW��ģʱ��CTU����֪ͨCPHY����int2�жϡ�
                                                              �����ȡ���ж�״̬�ϱ��Ĵ�������Ҫ��0x0704��int_mask_c_int012���룬���ж��Ƿ���Ҫ���� */
        unsigned int  reserved            : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_INT_TYPE_C_INT012_UNION;
#define BBPCOMM_INT_TYPE_C_INT012_o_int_type_c_int012_START  (0)
#define BBPCOMM_INT_TYPE_C_INT012_o_int_type_c_int012_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C_SND_LTE_INT_13_UNION
 �ṹ˵��  : C_SND_LTE_INT_13 �Ĵ����ṹ���塣��ַƫ����:0x0C5C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c_snd_lte_int_13_reg;
    struct
    {
        unsigned int  reserved_0       : 3;  /* bit[0-2]  : ���� */
        unsigned int  c_snd_lte_int_13 : 13; /* bit[3-15] : �߼������㡣����Ч��
                                                            
                                                            bit15~7����Ӧc_snd_lte_int_15 ~ 7��
                                                            CPHYͨ���˼Ĵ�����������15~7�жϣ�int_type_lte_rcv_c[15:7]����LPHY��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit6����Ӧc_snd_lte_int_6��
                                                            CPHYͨ���˼Ĵ�����������6�жϣ�int_type_lte_rcv_c[6]����LPHY��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit5����Ӧc_snd_lte_int_5��
                                                            C��ģʱ֪ͨCPHY L�������ڵ������Ч��
                                                            CPHYͨ���˼Ĵ�����������5�жϣ�int_type_lte_rcv_c[5]����CPHY��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit4����Ӧc_snd_lte_int_4��
                                                            C��ģʱǿ���˳���ϵͳ����ָʾ������Ч��
                                                            CPHYͨ���˼Ĵ�����������4�жϣ�int_type_lte_rcv_c[4]����LPHY��
                                                            ��Чʱ�̣�������Ч
                                                            
                                                            bit3����Ӧc_snd_lte_int_3��C��������ָʾ������Ч��
                                                            ���ڴ����ж�����3 ��int_type_lte_rcv_c[3]����LPHY��L��ģ�¶�C������ϵͳ����ʱ�����C����������CPHY���ô˱�־Ϊ1�� 
                                                            ��Чʱ�̣�������Ч */
        unsigned int  reserved_1       : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_C_SND_LTE_INT_13_UNION;
#define BBPCOMM_C_SND_LTE_INT_13_c_snd_lte_int_13_START  (3)
#define BBPCOMM_C_SND_LTE_INT_13_c_snd_lte_int_13_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C_ABBIF_FMT_UNION
 �ṹ˵��  : C_ABBIF_FMT �Ĵ����ṹ���塣��ַƫ����:0x0C60����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c_abbif_fmt_reg;
    struct
    {
        unsigned int  reserved_0        : 1;  /* bit[0-0]  : ���� */
        unsigned int  c_rxb_iq_exchange : 1;  /* bit[1-1]  : 1'b1��C��RXBͨ·IQ·���ݽ���
                                                             1'b0��C��RXBͨ·IQ·���ݲ�����
                                                             V3R3��֧��IQ�������ܡ� */
        unsigned int  c_rxb_q_inv       : 1;  /* bit[2-2]  : 1'b1��C��RXBͨ·Q·����ȡ��
                                                             1'b0��C��RXBͨ·Q·���ݲ�ȡ�� */
        unsigned int  c_rxb_i_inv       : 1;  /* bit[3-3]  : 1'b1��C��RXBͨ·I·����ȡ��
                                                             1'b0��C��RXBͨ·I·���ݲ�ȡ�� */
        unsigned int  c_rxa_iq_exchange : 1;  /* bit[4-4]  : 1'b1��C��RXAͨ·IQ·���ݽ���
                                                             1'b0��C��RXAͨ·IQ·���ݲ�����
                                                             V3R3��֧��IQ�������ܡ� */
        unsigned int  c_rxa_q_inv       : 1;  /* bit[5-5]  : 1'b1��C��RXAͨ·Q·����ȡ��
                                                             1'b0��C��RXAͨ·Q·���ݲ�ȡ�� */
        unsigned int  c_rxa_i_inv       : 1;  /* bit[6-6]  : 1'b1��C��RXAͨ·I·����ȡ��
                                                             1'b0��C��RXAͨ·I·���ݲ�ȡ�� */
        unsigned int  c_tx_iq_exchange  : 1;  /* bit[7-7]  : 1'b1��C��TXͨ·IQ·���ݽ���
                                                             1'b0��C��TXͨ·IQ·���ݲ�����
                                                             V3R3��֧��IQ�������ܡ� */
        unsigned int  c_tx_q_inv        : 1;  /* bit[8-8]  : 1'b1��C��TXͨ·Q·����ȡ��
                                                             1'b0��C��TXͨ·Q·���ݲ�ȡ�� */
        unsigned int  c_tx_i_inv        : 1;  /* bit[9-9]  : 1'b1��C��TXͨ·I·����ȡ��
                                                             1'b0��C��TXͨ·I·���ݲ�ȡ�� */
        unsigned int  reserved_1        : 22; /* bit[10-31]: ���� */
    } reg;
} BBPCOMM_C_ABBIF_FMT_UNION;
#define BBPCOMM_C_ABBIF_FMT_c_rxb_iq_exchange_START  (1)
#define BBPCOMM_C_ABBIF_FMT_c_rxb_iq_exchange_END    (1)
#define BBPCOMM_C_ABBIF_FMT_c_rxb_q_inv_START        (2)
#define BBPCOMM_C_ABBIF_FMT_c_rxb_q_inv_END          (2)
#define BBPCOMM_C_ABBIF_FMT_c_rxb_i_inv_START        (3)
#define BBPCOMM_C_ABBIF_FMT_c_rxb_i_inv_END          (3)
#define BBPCOMM_C_ABBIF_FMT_c_rxa_iq_exchange_START  (4)
#define BBPCOMM_C_ABBIF_FMT_c_rxa_iq_exchange_END    (4)
#define BBPCOMM_C_ABBIF_FMT_c_rxa_q_inv_START        (5)
#define BBPCOMM_C_ABBIF_FMT_c_rxa_q_inv_END          (5)
#define BBPCOMM_C_ABBIF_FMT_c_rxa_i_inv_START        (6)
#define BBPCOMM_C_ABBIF_FMT_c_rxa_i_inv_END          (6)
#define BBPCOMM_C_ABBIF_FMT_c_tx_iq_exchange_START   (7)
#define BBPCOMM_C_ABBIF_FMT_c_tx_iq_exchange_END     (7)
#define BBPCOMM_C_ABBIF_FMT_c_tx_q_inv_START         (8)
#define BBPCOMM_C_ABBIF_FMT_c_tx_q_inv_END           (8)
#define BBPCOMM_C_ABBIF_FMT_c_tx_i_inv_START         (9)
#define BBPCOMM_C_ABBIF_FMT_c_tx_i_inv_END           (9)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TDS_C_CTU_INT_SEL_UNION
 �ṹ˵��  : TDS_C_CTU_INT_SEL �Ĵ����ṹ���塣��ַƫ����:0x0C64����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      tds_c_ctu_int_sel_reg;
    struct
    {
        unsigned int  tds_c_ctu_int_sel : 1;  /* bit[0]   : 1'b0��TDS CTU�ж����������㣻
                                                            1'b1��C CTU�ж����������㡣 */
        unsigned int  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_TDS_C_CTU_INT_SEL_UNION;
#define BBPCOMM_TDS_C_CTU_INT_SEL_tds_c_ctu_int_sel_START  (0)
#define BBPCOMM_TDS_C_CTU_INT_SEL_tds_c_ctu_int_sel_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_S_C_CH_NUM_IND_UNION
 �ṹ˵��  : S_C_CH_NUM_IND �Ĵ����ṹ���塣��ַƫ����:0x0C68����ֵ:0x00000000�����:32
 �Ĵ���˵��: CΪ��ģʱ��Ӧͨ����ָʾ�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      s_c_ch_num_ind_reg;
    struct
    {
        unsigned int  s_c_ch_num_ind     : 2;  /* bit[0-1] : CΪ��ģʱ��Ӧ��ͨ��ѡ���źš�
                                                             0��ѡ��ͨ��0��
                                                             1��ѡ��ͨ��1��
                                                             2��ѡ��ͨ��2��
                                                             ����ʱ�̣���ģ����ͨ�ų������� */
        unsigned int  s_c_ch_num_ind_sel : 1;  /* bit[2-2] : CΪ��ģʱ��Ӧ��ͨ��ѡ���ź���Ч��ʽ��
                                                             0����int1��Ч��
                                                             1��������Ч�� */
        unsigned int  reserved           : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_S_C_CH_NUM_IND_UNION;
#define BBPCOMM_S_C_CH_NUM_IND_s_c_ch_num_ind_START      (0)
#define BBPCOMM_S_C_CH_NUM_IND_s_c_ch_num_ind_END        (1)
#define BBPCOMM_S_C_CH_NUM_IND_s_c_ch_num_ind_sel_START  (2)
#define BBPCOMM_S_C_CH_NUM_IND_s_c_ch_num_ind_sel_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C_CH_SW_UNION
 �ṹ˵��  : C_CH_SW �Ĵ����ṹ���塣��ַƫ����:0x0C6C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      c_ch_sw_reg;
    struct
    {
        unsigned int  c_ch_sw_rf     : 1;  /* bit[0]   : rf����ź��Ƿ񽻻���
                                                         1'b0��0/1ͨ��������
                                                         1'b1��0/1ͨ������ */
        unsigned int  c_ch_sw_mipi   : 1;  /* bit[1]   : mipi����ź��Ƿ񽻻���
                                                         1'b0��0/1ͨ��������
                                                         1'b1��0/1ͨ������ */
        unsigned int  c_ch_sw_abb_tx : 1;  /* bit[2]   : abb tx����ź��Ƿ񽻻���
                                                         1'b0��0/1ͨ��������
                                                         1'b1��0/1ͨ������ */
        unsigned int  c_ch_sw_abb_rx : 1;  /* bit[3]   : abb rx����ź��Ƿ񽻻���
                                                         1'b0��0/1ͨ��������
                                                         1'b1��0/1ͨ������ */
        unsigned int  c_ch_sw_pmu    : 1;  /* bit[4]   : pmu����ź��Ƿ񽻻���
                                                         1'b0��0/1ͨ��������
                                                         1'b1��0/1ͨ������ */
        unsigned int  c_ch_sw_apt    : 1;  /* bit[5]   : apt����ź��Ƿ񽻻���
                                                         1'b0��0/1ͨ��������
                                                         1'b1��0/1ͨ������ */
        unsigned int  reserved       : 26; /* bit[6-31]: ���� */
    } reg;
} BBPCOMM_C_CH_SW_UNION;
#define BBPCOMM_C_CH_SW_c_ch_sw_rf_START      (0)
#define BBPCOMM_C_CH_SW_c_ch_sw_rf_END        (0)
#define BBPCOMM_C_CH_SW_c_ch_sw_mipi_START    (1)
#define BBPCOMM_C_CH_SW_c_ch_sw_mipi_END      (1)
#define BBPCOMM_C_CH_SW_c_ch_sw_abb_tx_START  (2)
#define BBPCOMM_C_CH_SW_c_ch_sw_abb_tx_END    (2)
#define BBPCOMM_C_CH_SW_c_ch_sw_abb_rx_START  (3)
#define BBPCOMM_C_CH_SW_c_ch_sw_abb_rx_END    (3)
#define BBPCOMM_C_CH_SW_c_ch_sw_pmu_START     (4)
#define BBPCOMM_C_CH_SW_c_ch_sw_pmu_END       (4)
#define BBPCOMM_C_CH_SW_c_ch_sw_apt_START     (5)
#define BBPCOMM_C_CH_SW_c_ch_sw_apt_END       (5)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C_TCVR_SEL0_UNION
 �ṹ˵��  : C_TCVR_SEL0 �Ĵ����ṹ���塣��ַƫ����:0x0C70����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      c_tcvr_sel0_reg;
    struct
    {
        unsigned int  c_tcvr_sel0 : 1;  /* bit[0]   : C�����ͨ��0��tcvr_on�ź���Դ��
                                                      1'b0��������c bbp
                                                      1'b1��������dsp����ֵ */
        unsigned int  reserved    : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_C_TCVR_SEL0_UNION;
#define BBPCOMM_C_TCVR_SEL0_c_tcvr_sel0_START  (0)
#define BBPCOMM_C_TCVR_SEL0_c_tcvr_sel0_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C_TCVR_SEL1_UNION
 �ṹ˵��  : C_TCVR_SEL1 �Ĵ����ṹ���塣��ַƫ����:0x0C74����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      c_tcvr_sel1_reg;
    struct
    {
        unsigned int  c_tcvr_sel1 : 1;  /* bit[0]   : C�����ͨ��1��tcvr_on�ź���Դ��
                                                      1'b0��������c bbp
                                                      1'b1��������dsp����ֵ */
        unsigned int  reserved    : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_C_TCVR_SEL1_UNION;
#define BBPCOMM_C_TCVR_SEL1_c_tcvr_sel1_START  (0)
#define BBPCOMM_C_TCVR_SEL1_c_tcvr_sel1_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C_TCVR_VALUE0_UNION
 �ṹ˵��  : C_TCVR_VALUE0 �Ĵ����ṹ���塣��ַƫ����:0x0C78����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      c_tcvr_value0_reg;
    struct
    {
        unsigned int  c_tcvr_value0 : 1;  /* bit[0]   : dsp���õ�cģ�͸�ͨ��0 ��tcvr_onֵ */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_C_TCVR_VALUE0_UNION;
#define BBPCOMM_C_TCVR_VALUE0_c_tcvr_value0_START  (0)
#define BBPCOMM_C_TCVR_VALUE0_c_tcvr_value0_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C_TCVR_VALUE1_UNION
 �ṹ˵��  : C_TCVR_VALUE1 �Ĵ����ṹ���塣��ַƫ����:0x0C7C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      c_tcvr_value1_reg;
    struct
    {
        unsigned int  c_tcvr_value1 : 1;  /* bit[0]   : dsp���õ�cģ�͸�ͨ��1 ��tcvr_onֵ */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_C_TCVR_VALUE1_UNION;
#define BBPCOMM_C_TCVR_VALUE1_c_tcvr_value1_START  (0)
#define BBPCOMM_C_TCVR_VALUE1_c_tcvr_value1_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_COMM_32K_TIMING_RPT2_UNION
 �ṹ˵��  : COMM_32K_TIMING_RPT2 �Ĵ����ṹ���塣��ַƫ����:0x0F04����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      comm_32k_timing_rpt2_reg;
    struct
    {
        unsigned int  o_adjust_timing : 24; /* bit[0-23] : 32KУ׼��ʱ���Ķ�ʱ��Ϣ����DSP ����timing_get_ind�����ϱ���
                                                           ������
                                                           �ϱ�ʱ�̣�comm_32k_timing_validΪ��ʱ�ϱ���Ч */
        unsigned int  reserved        : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_COMM_32K_TIMING_RPT2_UNION;
#define BBPCOMM_COMM_32K_TIMING_RPT2_o_adjust_timing_START  (0)
#define BBPCOMM_COMM_32K_TIMING_RPT2_o_adjust_timing_END    (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_ABB_RXB_LOCK_MODE_UNION
 �ṹ˵��  : ABB_RXB_LOCK_MODE �Ĵ����ṹ���塣��ַƫ����:0x0F08����ֵ:0x00000001�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      abb_rxb_lock_mode_reg;
    struct
    {
        unsigned int  cpu_abb_mask_cnt_num : 16; /* bit[0-15] : ABB CH0 RXB��CH1 RXBͨ�������ӳټ���ֵ����ͨ���л��Ļ���ʱ�䣬��������Ϊ����ʱ�ӣ�150M��������ֵ������ڵ���1�� */
        unsigned int  cpu_abb_lock_en      : 1;  /* bit[16]   : ABB CH0 RXBͨ����CH1 RXBͨ����������ʹ���źţ�1��ʾ��Ч */
        unsigned int  reserved             : 15; /* bit[17-31]: ���� */
    } reg;
} BBPCOMM_ABB_RXB_LOCK_MODE_UNION;
#define BBPCOMM_ABB_RXB_LOCK_MODE_cpu_abb_mask_cnt_num_START  (0)
#define BBPCOMM_ABB_RXB_LOCK_MODE_cpu_abb_mask_cnt_num_END    (15)
#define BBPCOMM_ABB_RXB_LOCK_MODE_cpu_abb_lock_en_START       (16)
#define BBPCOMM_ABB_RXB_LOCK_MODE_cpu_abb_lock_en_END         (16)


/*****************************************************************************
 �ṹ��    : BBPCOMM_DBG_EN_UNION
 �ṹ˵��  : DBG_EN �Ĵ����ṹ���塣��ַƫ����:0x0F80����ֵ:0x00000002�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dbg_en_reg;
    struct
    {
        unsigned int  dbg_en       : 1;  /* bit[0]    : ��ά�ɲ�ʹ���źţ���dbg_rpt_modeΪ0ʱ�߼����壬������Ҫд�塣
                                                        1'b0����ά�ɲ⹦�ܲ�ʹ��                           
                                                        1'b1����ά�ɲ⹦��ʹ�� */
        unsigned int  dbg_rpt_mode : 1;  /* bit[1]    : ��ά�ɲ������ϱ�ģʽ��
                                                        'b0���������������dbg_pkg_num�����ݰ����Զ�������
                                                        'b1��ֻҪdbg_enΪ1���ϱ���û���ϱ��������ơ� */
        unsigned int  reserved     : 14; /* bit[2-15] : ���� */
        unsigned int  dbg_pkg_num  : 16; /* bit[16-31]: ��ά�ɲ�İ����� */
    } reg;
} BBPCOMM_DBG_EN_UNION;
#define BBPCOMM_DBG_EN_dbg_en_START        (0)
#define BBPCOMM_DBG_EN_dbg_en_END          (0)
#define BBPCOMM_DBG_EN_dbg_rpt_mode_START  (1)
#define BBPCOMM_DBG_EN_dbg_rpt_mode_END    (1)
#define BBPCOMM_DBG_EN_dbg_pkg_num_START   (16)
#define BBPCOMM_DBG_EN_dbg_pkg_num_END     (31)


/*****************************************************************************
 �ṹ��    : BBPCOMM_DBG_FLT_UNION
 �ṹ˵��  : DBG_FLT �Ĵ����ṹ���塣��ַƫ����:0x0F88����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dbg_flt_reg;
    struct
    {
        unsigned int  dbg_flt  : 16; /* bit[0-15] : ��ά�ɲ��ڲ�����ָʾ��
                                                    1���ϱ�mipi����
                                                    2���ϱ�ssi����
                                                    3������dbg�ϱ�����
                                                    ���������� */
        unsigned int  reserved : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_DBG_FLT_UNION;
#define BBPCOMM_DBG_FLT_dbg_flt_START   (0)
#define BBPCOMM_DBG_FLT_dbg_flt_END     (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_DBG_REQ_EN_UNION
 �ṹ˵��  : DBG_REQ_EN �Ĵ����ṹ���塣��ַƫ����:0x0F8C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dbg_req_en_reg;
    struct
    {
        unsigned int  _W       : 25; /* bit[0-24] : ��ά�ɲ���ѯ�����ϱ��ź�ʹ�ܣ�dbg_req_en[24:0]��Ӧreg[24:0],��dbg_req_en[24]Ϊ1��reg[24]������Ч��dbg_req_en[24]Ϊ0��reg[24]������Ч */
        unsigned int  reserved : 7;  /* bit[25-31]: ���� */
    } reg;
} BBPCOMM_DBG_REQ_EN_UNION;
#define BBPCOMM_DBG_REQ_EN__W_START        (0)
#define BBPCOMM_DBG_REQ_EN__W_END          (24)


/*****************************************************************************
 �ṹ��    : BBPCOMM_MIPI_DYN_EXCHG_UNION
 �ṹ˵��  : MIPI_DYN_EXCHG �Ĵ����ṹ���塣��ַƫ����:0x0F90����ֵ:0x00000001�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      mipi_dyn_exchg_reg;
    struct
    {
        unsigned int  mipi_dyn_exchg_en      : 1;  /* bit[0]   : MIPIͨ����̬�л�ʹ�ܣ�1����̬�л�������0����̬�л��ر� */
        unsigned int  mipi_robin_clr_ind_imi : 1;  /* bit[1]   : MIPI��ѯ���������źţ�1����������źţ�0����Ч */
        unsigned int  reserved               : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_MIPI_DYN_EXCHG_UNION;
#define BBPCOMM_MIPI_DYN_EXCHG_mipi_dyn_exchg_en_START       (0)
#define BBPCOMM_MIPI_DYN_EXCHG_mipi_dyn_exchg_en_END         (0)
#define BBPCOMM_MIPI_DYN_EXCHG_mipi_robin_clr_ind_imi_START  (1)
#define BBPCOMM_MIPI_DYN_EXCHG_mipi_robin_clr_ind_imi_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TIMING_CLR_DELAY_CNT_UNION
 �ṹ˵��  : TIMING_CLR_DELAY_CNT �Ĵ����ṹ���塣��ַƫ����:0x0F94����ֵ:0x00004B00�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      timing_clr_delay_cnt_reg;
    struct
    {
        unsigned int  timing_clr_delay_cnt : 16; /* bit[0-15] : dsp��ȡ��ʱ��Ϣ��ʱ����ʱ�䣬Ĭ��Ϊ0x4b00��1ms�� */
        unsigned int  reserved             : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_TIMING_CLR_DELAY_CNT_UNION;
#define BBPCOMM_TIMING_CLR_DELAY_CNT_timing_clr_delay_cnt_START  (0)
#define BBPCOMM_TIMING_CLR_DELAY_CNT_timing_clr_delay_cnt_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TIMING_GET_MODE_UNION
 �ṹ˵��  : TIMING_GET_MODE �Ĵ����ṹ���塣��ַƫ����:0x0F98����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      timing_get_mode_reg;
    struct
    {
        unsigned int  timing_get_mode : 1;  /* bit[0]   : ��ʱ��Ϣ�ϱ�ģʽѡ��timing_get_mode��Ч��dsp���ƣ�bbe16��arm��Ϊһ�׽ӿڻ�ȡ��ʱ��Ϣ
                                                          timing_get_mode��Ч��bbe16��arm��Ϊ���׽ӿڻ�ȡ��ʱ��Ϣ */
        unsigned int  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_TIMING_GET_MODE_UNION;
#define BBPCOMM_TIMING_GET_MODE_timing_get_mode_START  (0)
#define BBPCOMM_TIMING_GET_MODE_timing_get_mode_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TIMING_CLEAR1_UNION
 �ṹ˵��  : TIMING_CLEAR1 �Ĵ����ṹ���塣��ַƫ����:0x0F9C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      timing_clear1_reg;
    struct
    {
        unsigned int  timing_clear1          : 1;  /* bit[0]   : �߼������㡣
                                                                 ��ʱ��־������������timing_valid1��־��
                                                                 ����ʱ�̣�DSP��ȡ��ʱ��Ϻ�����
                                                                 ��Чʱ�̣�������Ч��
                                                                 ��timing_get_mode��Ч��arm���ƣ� */
        unsigned int  comm_32k_timing_clear1 : 1;  /* bit[1]   : �߼������㡣
                                                                 32������ʱ��Ϣ�ı�־������������timing_valid1��־��
                                                                 ����ʱ�̣�DSP��ȡ��ʱ��Ϻ�����
                                                                 ��Чʱ�̣�������Ч
                                                                 ����Ϊ32K��ʱ��Ϣ���ϱ���ʱԶ��������ϵͳ�Ķ�ʱ��Ϣ�����Ե�������
                                                                 ��timing_get_mode��Ч��arm���ƣ� */
        unsigned int  reserved               : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_TIMING_CLEAR1_UNION;
#define BBPCOMM_TIMING_CLEAR1_timing_clear1_START           (0)
#define BBPCOMM_TIMING_CLEAR1_timing_clear1_END             (0)
#define BBPCOMM_TIMING_CLEAR1_comm_32k_timing_clear1_START  (1)
#define BBPCOMM_TIMING_CLEAR1_comm_32k_timing_clear1_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TIMING_GET_IND1_UNION
 �ṹ˵��  : TIMING_GET_IND1 �Ĵ����ṹ���塣��ַƫ����:0x0F10����ֵ:0x00000030�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      timing_get_ind1_reg;
    struct
    {
        unsigned int  timing_get_ind1   : 1;  /* bit[0]   : �߼������㡣
                                                            timing_get_mode��Ч��arm��Ҫ��ȡ��ʱ��ϵʱ������Ч��CTU�߼����ݴ��ź�����LTE/W/Gm/Gs/TDS/C��ϵͳ��ʱ��CTU���ڲ���ʱ��arm��ѯ��
                                                            ����ʱ�̣������Ҫ���涨ʱ
                                                            ��Чʱ�̣�������Ч */
        unsigned int  reserved_0        : 3;  /* bit[1-3] : ���� */
        unsigned int  timing_get_c_sel1 : 2;  /* bit[4-5] : ��ʾtiming_get_mode��Чʱarm��ȡcģbbp���������1x��evdo����base_cnt��   00��1x��ʱ��01��evdo��ʱ��10�� base_cnt ��11����Ч��
                                                            timing_get_mode��Чʱ���������ã������� */
        unsigned int  reserved_1        : 26; /* bit[6-31]: ���� */
    } reg;
} BBPCOMM_TIMING_GET_IND1_UNION;
#define BBPCOMM_TIMING_GET_IND1_timing_get_ind1_START    (0)
#define BBPCOMM_TIMING_GET_IND1_timing_get_ind1_END      (0)
#define BBPCOMM_TIMING_GET_IND1_timing_get_c_sel1_START  (4)
#define BBPCOMM_TIMING_GET_IND1_timing_get_c_sel1_END    (5)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TINMG_VALID1_UNION
 �ṹ˵��  : TINMG_VALID1 �Ĵ����ṹ���塣��ַƫ����:0x0F14����ֵ:0x00000030�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      tinmg_valid1_reg;
    struct
    {
        unsigned int  o_timing_valid1        : 1;  /* bit[0]   : ��ʱ�ϱ���Ч��־������Ч��
                                                                 DSP����timing_get_ind1�󣬲�ѯ�˱�־�����Ϊ�ߣ�����Ի�ȡLTE��W��Gm��Gs, TDS��ϵͳ��ʱ��
                                                                 DSP��ȡ��ʱ��Ϻ�����timing_clear1�Ĵ�����timing_valid1����Ϊ��Ч��
                                                                 CTU��⵽timing_get_ind1��̶��ӳ�delay_cnt������timing_valid1��
                                                                 
                                                                 ����ʱ�̣�
                                                                 ��Чʱ�̣�������Ч
                                                                 ��timing_get_mode��Ч��dsp���ƣ�
                                                                 timing_get_mode��Ч��bbe16���ƣ� */
        unsigned int  comm_32k_timing_valid1 : 1;  /* bit[1]   : 32K������ʱ�ϱ���Ч��־������Ч��
                                                                 DSP����timing_get_ind1�󣬲�ѯ�˱�־�����Ϊ�ߣ�����Ի�ȡ32K������ʱ���Ķ�ʱ��Ϣ��
                                                                 DSP��ȡ��ʱ��Ϻ�����comm_32k_timing_clear1�Ĵ�����comm_32k_timing_valid1����Ϊ��Ч��
                                                                 32K��ʱ�����ȶ�������comm_32k_timing_valid1
                                                                 ����ʱ�̣�
                                                                 ��Чʱ�̣�������Ч
                                                                 ��timing_get_mode��Ч��arm���ƣ� */
        unsigned int  overtime_ind1          : 1;  /* bit[2]   : ��ʾarm��ȡ��ʱ��Ϣ��ʱ���ڳ�ʱ����ʱ����δ����o_timing_clear�źţ� */
        unsigned int  reserved_0             : 1;  /* bit[3]   : ���� */
        unsigned int  timing_valid_c_sel1    : 2;  /* bit[4-5] : ��ʾo_timing_valid��Чʱ���ϱ��ļ�������arm����cģbbp��1x��evdo����base_cnt
                                                                 00��1x��ʱ
                                                                 01�� evdo��ʱ
                                                                 10�� basecent */
        unsigned int  reserved_1             : 26; /* bit[6-31]: ���� */
    } reg;
} BBPCOMM_TINMG_VALID1_UNION;
#define BBPCOMM_TINMG_VALID1_o_timing_valid1_START         (0)
#define BBPCOMM_TINMG_VALID1_o_timing_valid1_END           (0)
#define BBPCOMM_TINMG_VALID1_comm_32k_timing_valid1_START  (1)
#define BBPCOMM_TINMG_VALID1_comm_32k_timing_valid1_END    (1)
#define BBPCOMM_TINMG_VALID1_overtime_ind1_START           (2)
#define BBPCOMM_TINMG_VALID1_overtime_ind1_END             (2)
#define BBPCOMM_TINMG_VALID1_timing_valid_c_sel1_START     (4)
#define BBPCOMM_TINMG_VALID1_timing_valid_c_sel1_END       (5)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TIMING_GET_W_SEL_UNION
 �ṹ˵��  : TIMING_GET_W_SEL �Ĵ����ṹ���塣��ַƫ����:0x0F18����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      timing_get_w_sel_reg;
    struct
    {
        unsigned int  timing_get_w_sel : 2;  /* bit[0-1] : ��ʾtiming_get_mode��Чʱbbe��ȡWģbbp���������sys_cnt����base_cnt��00�������ƣ���sys_cnt��01��base_cnt 10����Ч 11����Ч
                                                           timing_get_mode��Чʱ���������ã������� */
        unsigned int  reserved         : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_TIMING_GET_W_SEL_UNION;
#define BBPCOMM_TIMING_GET_W_SEL_timing_get_w_sel_START  (0)
#define BBPCOMM_TIMING_GET_W_SEL_timing_get_w_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TIMING_VALID_W_SEL_UNION
 �ṹ˵��  : TIMING_VALID_W_SEL �Ĵ����ṹ���塣��ַƫ����:0x0F1C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      timing_valid_w_sel_reg;
    struct
    {
        unsigned int  timing_valid_w_sel : 2;  /* bit[0-1] : ��ʾo_timing_valid��Чʱ���ϱ�wģ�ļ�������bbe16����sys_cnt����base_cnt
                                                             00�������ƣ��� sys_cnt
                                                             01�� basecent 10����Ч  11����Ч  */
        unsigned int  reserved           : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_TIMING_VALID_W_SEL_UNION;
#define BBPCOMM_TIMING_VALID_W_SEL_timing_valid_w_sel_START  (0)
#define BBPCOMM_TIMING_VALID_W_SEL_timing_valid_w_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TIMING_GET_W_SEL1_UNION
 �ṹ˵��  : TIMING_GET_W_SEL1 �Ĵ����ṹ���塣��ַƫ����:0x0F28����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      timing_get_w_sel1_reg;
    struct
    {
        unsigned int  timing_get_w_sel1 : 2;  /* bit[0-1] : ��ʾtiming_get_mode��Чʱarm��ȡwģ���������sys_cnt����base_cnt��   00�������ƣ���sys_cnt��01��base_cnt�� 10����Ч 11 ��Ч
                                                            timing_get_mode��Чʱ���������ã������� */
        unsigned int  reserved          : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_TIMING_GET_W_SEL1_UNION;
#define BBPCOMM_TIMING_GET_W_SEL1_timing_get_w_sel1_START  (0)
#define BBPCOMM_TIMING_GET_W_SEL1_timing_get_w_sel1_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TIMING_VALID_W_SEL1_UNION
 �ṹ˵��  : TIMING_VALID_W_SEL1 �Ĵ����ṹ���塣��ַƫ����:0x0F2C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      timing_valid_w_sel1_reg;
    struct
    {
        unsigned int  timing_valid_w_sel1 : 2;  /* bit[0-1] : ��ʾo_timing_valid��Чʱ���ϱ��ļ�������arm����wģbbp��sys_cnt����base_cnt
                                                              00��sys_cnt��ʱ
                                                              01��base_cnt��ʱ 
                                                              10����Ч
                                                              11����Ч */
        unsigned int  reserved            : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_TIMING_VALID_W_SEL1_UNION;
#define BBPCOMM_TIMING_VALID_W_SEL1_timing_valid_w_sel1_START  (0)
#define BBPCOMM_TIMING_VALID_W_SEL1_timing_valid_w_sel1_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_CFG_SC_EN_UNION
 �ṹ˵��  : CPU_CFG_SC_EN �Ĵ����ṹ���塣��ַƫ����:0x0F30����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_cfg_sc_en_reg;
    struct
    {
        unsigned int  cpu_cfg_sc_en : 1;  /* bit[0]   : comm����sc_pllʹ�ܣ�1��ͨ��comm����sc_pll��0����ͨ��comm����sc_pll */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_CPU_CFG_SC_EN_UNION;
#define BBPCOMM_CPU_CFG_SC_EN_cpu_cfg_sc_en_START  (0)
#define BBPCOMM_CPU_CFG_SC_EN_cpu_cfg_sc_en_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_INT1_CFG_SC_EN_UNION
 �ṹ˵��  : CPU_INT1_CFG_SC_EN �Ĵ����ṹ���塣��ַƫ����:0x0F34����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_int1_cfg_sc_en_reg;
    struct
    {
        unsigned int  cpu_int1_cfg_sc_en : 1;  /* bit[0]   : comm��sc_pll�����ж�1ʹ�ܣ�1����Ч��0��Ч */
        unsigned int  reserved           : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_CPU_INT1_CFG_SC_EN_UNION;
#define BBPCOMM_CPU_INT1_CFG_SC_EN_cpu_int1_cfg_sc_en_START  (0)
#define BBPCOMM_CPU_INT1_CFG_SC_EN_cpu_int1_cfg_sc_en_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_INT2_CFG_SC_EN_UNION
 �ṹ˵��  : CPU_INT2_CFG_SC_EN �Ĵ����ṹ���塣��ַƫ����:0x0F38����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_int2_cfg_sc_en_reg;
    struct
    {
        unsigned int  cpu_int2_cfg_sc_en : 1;  /* bit[0]   : comm��sc_pll�����ж�2ʹ�ܣ�1����Ч��0��Ч */
        unsigned int  reserved           : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_CPU_INT2_CFG_SC_EN_UNION;
#define BBPCOMM_CPU_INT2_CFG_SC_EN_cpu_int2_cfg_sc_en_START  (0)
#define BBPCOMM_CPU_INT2_CFG_SC_EN_cpu_int2_cfg_sc_en_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_PRO_SOFT_CFG_SC_IND_UNION
 �ṹ˵��  : CPU_PRO_SOFT_CFG_SC_IND �Ĵ����ṹ���塣��ַƫ����:0x0F3C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_pro_soft_cfg_sc_ind_reg;
    struct
    {
        unsigned int  cpu_pro_sfot_cfg_sc_ind : 1;  /* bit[0]   : �����sc_pll���õ���ģ��ind�ź� */
        unsigned int  reserved                : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_CPU_PRO_SOFT_CFG_SC_IND_UNION;
#define BBPCOMM_CPU_PRO_SOFT_CFG_SC_IND_cpu_pro_sfot_cfg_sc_ind_START  (0)
#define BBPCOMM_CPU_PRO_SOFT_CFG_SC_IND_cpu_pro_sfot_cfg_sc_ind_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_SEC_SOFT_CFG_SC_IND_UNION
 �ṹ˵��  : CPU_SEC_SOFT_CFG_SC_IND �Ĵ����ṹ���塣��ַƫ����:0x0F40����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_sec_soft_cfg_sc_ind_reg;
    struct
    {
        unsigned int  cpu_sec_sfot_cfg_sc_ind : 1;  /* bit[0]   : �����sc_pll���õĴ�ģ��ind�ź� */
        unsigned int  reserved                : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_CPU_SEC_SOFT_CFG_SC_IND_UNION;
#define BBPCOMM_CPU_SEC_SOFT_CFG_SC_IND_cpu_sec_sfot_cfg_sc_ind_START  (0)
#define BBPCOMM_CPU_SEC_SOFT_CFG_SC_IND_cpu_sec_sfot_cfg_sc_ind_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_SC_CH_SEL_UNION
 �ṹ˵��  : CPU_SC_CH_SEL �Ĵ����ṹ���塣��ַƫ����:0x0F44����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_sc_ch_sel_reg;
    struct
    {
        unsigned int  cpu_sc_ch_sel : 2;  /* bit[0-1] : 0������ͨ��0����ģ��������sc_pll�ź�
                                                        1������ͨ��1����ģ��������sc_pll�ź�
                                                        2������ͨ��2����ģ��������sc_pll�ź� */
        unsigned int  reserved      : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_CPU_SC_CH_SEL_UNION;
#define BBPCOMM_CPU_SC_CH_SEL_cpu_sc_ch_sel_START  (0)
#define BBPCOMM_CPU_SC_CH_SEL_cpu_sc_ch_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CTU_TIMING_ROBIN_CLR_IND_UNION
 �ṹ˵��  : CTU_TIMING_ROBIN_CLR_IND �Ĵ����ṹ���塣��ַƫ����:0x0F4C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      ctu_timing_robin_clr_ind_reg;
    struct
    {
        unsigned int  ctu_timing_robin_clr_ind : 1;  /* bit[0-0] : ctu�ж�ʱ��ѯ���������źţ�1���������㣻0����Ч�� */
        unsigned int  reserved                 : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_CTU_TIMING_ROBIN_CLR_IND_UNION;
#define BBPCOMM_CTU_TIMING_ROBIN_CLR_IND_ctu_timing_robin_clr_ind_START  (0)
#define BBPCOMM_CTU_TIMING_ROBIN_CLR_IND_ctu_timing_robin_clr_ind_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GU_SDR_EN_UNION
 �ṹ˵��  : GU_SDR_EN �Ĵ����ṹ���塣��ַƫ����:0x0FFC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gu_sdr_en_reg;
    struct
    {
        unsigned int  g_sdr_en          : 1;  /* bit[0]   : G SDRģʽ����ʹ�ܡ� */
        unsigned int  w_sdr_en          : 1;  /* bit[1]   : W SDRģʽ����ʹ�ܡ� */
        unsigned int  w_sdr_dec_clk_sel : 1;  /* bit[2]   : W SDRģʽ������ʱ��ѡ��0���������122mʱ�ӣ�1���������245mʱ�ӡ� */
        unsigned int  reserved          : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_GU_SDR_EN_UNION;
#define BBPCOMM_GU_SDR_EN_g_sdr_en_START           (0)
#define BBPCOMM_GU_SDR_EN_g_sdr_en_END             (0)
#define BBPCOMM_GU_SDR_EN_w_sdr_en_START           (1)
#define BBPCOMM_GU_SDR_EN_w_sdr_en_END             (1)
#define BBPCOMM_GU_SDR_EN_w_sdr_dec_clk_sel_START  (2)
#define BBPCOMM_GU_SDR_EN_w_sdr_dec_clk_sel_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C2_PRIMARY_MODE_IND_UNION
 �ṹ˵��  : C2_PRIMARY_MODE_IND �Ĵ����ṹ���塣��ַƫ����:0x0D00����ֵ:0x00000007�����:32
 �Ĵ���˵��: ͨ��2��Ӧ��ģ����ģ2����ģʽָʾ�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c2_primary_mode_ind_reg;
    struct
    {
        unsigned int  c2_primary_mode_ind : 3;  /* bit[0-2] : ͨ��2��Ӧ����ģ������Ϊ��ģ0����ģʽָʾ����ʾLTE��W��Gm��Gs��TDS˭����ģ2��
                                                              011��Gm��ģ��
                                                              100��Gs��ģ��
                                                              110~111����Ч��
                                                              ����ʱ�̣���ģ����ͨ�ų������� */
        unsigned int  reserved            : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_C2_PRIMARY_MODE_IND_UNION;
#define BBPCOMM_C2_PRIMARY_MODE_IND_c2_primary_mode_ind_START  (0)
#define BBPCOMM_C2_PRIMARY_MODE_IND_c2_primary_mode_ind_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C2_SECOND_MODE_IND_UNION
 �ṹ˵��  : C2_SECOND_MODE_IND �Ĵ����ṹ���塣��ַƫ����:0x0D04����ֵ:0x00000007�����:32
 �Ĵ���˵��: ��ģ2��Ӧ�Ĵ�ģ����ģ2����ģʽָʾ�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c2_second_mode_ind_reg;
    struct
    {
        unsigned int  c2_second_mode_ind : 3;  /* bit[0-2] : ��ģ2��Ӧ�Ĵ�ģ������Ϊ��ģ2����ģʽָʾ����ʾ��ǰLTE/W/Gm/Gs/TDS˭�Ǵ�ģ2��
                                                             000��LTE��ģ��
                                                             001��W ��ģ��
                                                             010��TDS��ģ��
                                                             011��Gm��ģ��
                                                             100��Gs��ģ��
                                                             101:C��ģ��
                                                             110~111����Ч��
                                                             ����ʱ�̣���ģ����ͨ�ų������� */
        unsigned int  reserved           : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_C2_SECOND_MODE_IND_UNION;
#define BBPCOMM_C2_SECOND_MODE_IND_c2_second_mode_ind_START  (0)
#define BBPCOMM_C2_SECOND_MODE_IND_c2_second_mode_ind_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C2_AFC_PDM_SELECT_MASK_UNION
 �ṹ˵��  : C2_AFC_PDM_SELECT_MASK �Ĵ����ṹ���塣��ַƫ����:0x0D10����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c2_afc_pdm_select_mask_reg;
    struct
    {
        unsigned int  c2_afc_pdm_select_mask : 3;  /* bit[0-2] : ͨ��2 AFC�����ź���Դ��
                                                                 3'b000������ģ���ƣ�
                                                                 3'b001��ǿ����Lģ���ƣ�
                                                                 3'b010��ǿ����Wģ���ƣ�
                                                                 3'b011��ǿ����TDSģ���ƣ�
                                                                 3'b100��ǿ����Gmģ���ƣ�
                                                                 3'b101��ǿ����Gsģ���ƣ�
                                                                 3'b110��ǿ����Cģ���ƣ�
                                                                 3'b111����Ч��
                                                                 �����á� */
        unsigned int  reserved               : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_C2_AFC_PDM_SELECT_MASK_UNION;
#define BBPCOMM_C2_AFC_PDM_SELECT_MASK_c2_afc_pdm_select_mask_START  (0)
#define BBPCOMM_C2_AFC_PDM_SELECT_MASK_c2_afc_pdm_select_mask_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C2_ANT_SWITCH_PA_SELECT_MASK_UNION
 �ṹ˵��  : C2_ANT_SWITCH_PA_SELECT_MASK �Ĵ����ṹ���塣��ַƫ����:0x0D14����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c2_ant_switch_pa_select_mask_reg;
    struct
    {
        unsigned int  c2_ant_switch_pa_select_mask : 3;  /* bit[0-2] : ͨ��2 ���߿��غ�PA�����ź���Դ��
                                                                       3'b000������ģ���ƣ�
                                                                       3'b001��ǿ����Lģ���ƣ�
                                                                       3'b010��ǿ����Wģ���ƣ�
                                                                       3'b011��ǿ����TDSģ���ƣ�
                                                                       3'b100��ǿ����Gmģ���ƣ�
                                                                       3'b101��ǿ����Gsģ���ƣ�
                                                                       3'b110��ǿ����Cģ���ƣ�
                                                                       3'b111����Ч��
                                                                       �����á� */
        unsigned int  reserved                     : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_C2_ANT_SWITCH_PA_SELECT_MASK_UNION;
#define BBPCOMM_C2_ANT_SWITCH_PA_SELECT_MASK_c2_ant_switch_pa_select_mask_START  (0)
#define BBPCOMM_C2_ANT_SWITCH_PA_SELECT_MASK_c2_ant_switch_pa_select_mask_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C2_RFIC_SELECT_MASK_UNION
 �ṹ˵��  : C2_RFIC_SELECT_MASK �Ĵ����ṹ���塣��ַƫ����:0x0D18����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c2_rfic_select_mask_reg;
    struct
    {
        unsigned int  c2_rfic_select_mask : 3;  /* bit[0-2] : ͨ��2 RFIC�����ź���Դ�������߿غ�SSI����
                                                              3'b000������ģ���ƣ�
                                                              3'b001��ǿ����Lģ���ƣ�
                                                              3'b010��ǿ����Wģ���ƣ�
                                                              3'b011��ǿ����TDSģ���ƣ�
                                                              3'b100��ǿ����Gmģ���ƣ�
                                                              3'b101��ǿ����Gsģ���ƣ�
                                                              3'b110��ǿ����Cģ���ƣ�
                                                              3'b111����Ч��
                                                              �����á� */
        unsigned int  reserved            : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_C2_RFIC_SELECT_MASK_UNION;
#define BBPCOMM_C2_RFIC_SELECT_MASK_c2_rfic_select_mask_START  (0)
#define BBPCOMM_C2_RFIC_SELECT_MASK_c2_rfic_select_mask_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C2_MIPI_SELECT_MASK_UNION
 �ṹ˵��  : C2_MIPI_SELECT_MASK �Ĵ����ṹ���塣��ַƫ����:0x0D1C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c2_mipi_select_mask_reg;
    struct
    {
        unsigned int  c2_mipi_select_mask : 3;  /* bit[0-2] : ͨ��2 MIPI�����ź���Դ��
                                                              3'b000������ģ���ƣ�
                                                              3'b001��ǿ����Lģ���ƣ�
                                                              3'b010��ǿ����Wģ���ƣ�
                                                              3'b011��ǿ����TDSģ���ƣ�
                                                              3'b100��ǿ����Gmģ���ƣ�
                                                              3'b101��ǿ����Gsģ���ƣ�
                                                              3'b110��ǿ����Cģ���ƣ�
                                                              ��������Ч��
                                                              �����á� */
        unsigned int  reserved            : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_C2_MIPI_SELECT_MASK_UNION;
#define BBPCOMM_C2_MIPI_SELECT_MASK_c2_mipi_select_mask_START  (0)
#define BBPCOMM_C2_MIPI_SELECT_MASK_c2_mipi_select_mask_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C2_ABB_SELECT_MASK_UNION
 �ṹ˵��  : C2_ABB_SELECT_MASK �Ĵ����ṹ���塣��ַƫ����:0x0D20����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c2_abb_select_mask_reg;
    struct
    {
        unsigned int  c2_abb_select_mask : 3;  /* bit[0-2] : ͨ��2 ABB�����ź���Դ��
                                                             3'b000������ģ���ƣ�
                                                             3'b001��ǿ����Lģ���ƣ�
                                                             3'b010��ǿ����Wģ���ƣ�
                                                             3'b011��ǿ����TDSģ���ƣ�
                                                             3'b100��ǿ����Gmģ���ƣ�
                                                             3'b101��ǿ����Gsģ���ƣ�
                                                             3'b110��ǿ����Cģ���ƣ�
                                                             ��������Ч��
                                                             �����á� */
        unsigned int  reserved           : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_C2_ABB_SELECT_MASK_UNION;
#define BBPCOMM_C2_ABB_SELECT_MASK_c2_abb_select_mask_START  (0)
#define BBPCOMM_C2_ABB_SELECT_MASK_c2_abb_select_mask_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C2_PMU_SELECT_MASK_UNION
 �ṹ˵��  : C2_PMU_SELECT_MASK �Ĵ����ṹ���塣��ַƫ����:0x0D24����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c2_pmu_select_mask_reg;
    struct
    {
        unsigned int  c2_pmu_select_mask : 3;  /* bit[0-2] : ͨ��2 PMU�����ź���Դ��
                                                             3'b000������ģ���ƣ�
                                                             3'b001��ǿ����Lģ���ƣ�
                                                             3'b010��ǿ����Wģ���ƣ�
                                                             3'b011��ǿ����TDSģ���ƣ�
                                                             3'b100��ǿ����Gmģ���ƣ�
                                                             3'b101��ǿ����Gsģ���ƣ�
                                                             3'b110��ǿ����Cģ���ƣ�
                                                             3'b111����Ч��
                                                             �����á� */
        unsigned int  reserved           : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_C2_PMU_SELECT_MASK_UNION;
#define BBPCOMM_C2_PMU_SELECT_MASK_c2_pmu_select_mask_START  (0)
#define BBPCOMM_C2_PMU_SELECT_MASK_c2_pmu_select_mask_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_DSP_C2_SEL_MASK_UNION
 �ṹ˵��  : DSP_C2_SEL_MASK �Ĵ����ṹ���塣��ַƫ����:0x0D28����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dsp_c2_sel_mask_reg;
    struct
    {
        unsigned int  dsp_c2_sel_mask : 3;  /* bit[0-2] : ��ǰͨ��2������֮ǰ�������ǿ��ģʽ��
                                                          ע���������ڸ�����Χ������ABB��RF��PA��mipi�ȣ������Ľ���ǿ�䡣
                                                          �����á� */
        unsigned int  reserved        : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_DSP_C2_SEL_MASK_UNION;
#define BBPCOMM_DSP_C2_SEL_MASK_dsp_c2_sel_mask_START  (0)
#define BBPCOMM_DSP_C2_SEL_MASK_dsp_c2_sel_mask_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_DSP_RFIC2_RSTN_UNION
 �ṹ˵��  : DSP_RFIC2_RSTN �Ĵ����ṹ���塣��ַƫ����:0x0D2C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dsp_rfic2_rstn_reg;
    struct
    {
        unsigned int  dsp_rfic2_rstn : 1;  /* bit[0-0] : ������õ�RFIC2��λ�źţ�����Ч��
                                                         0����λ��1���⸴λ��
                                                         �ϵ��ʼ������Ϊ0������RFIC�ֲ�Ҫ��ά��һ��ʱ�������Ϊ1��
                                                         V3R3���üĴ������ܸ��ڼĴ���0x0334��bit[8]ʵ�֣�Ĭ��ֵ��Ϊ0���˴�ɾ����
                                                         V7R2��λֵΪ0��
                                                         V8R1���üĴ�������ɾ���� */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_DSP_RFIC2_RSTN_UNION;
#define BBPCOMM_DSP_RFIC2_RSTN_dsp_rfic2_rstn_START  (0)
#define BBPCOMM_DSP_RFIC2_RSTN_dsp_rfic2_rstn_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C2_SECOND_AFC_MODE_UNION
 �ṹ˵��  : C2_SECOND_AFC_MODE �Ĵ����ṹ���塣��ַƫ����:0x0D30����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c2_second_afc_mode_reg;
    struct
    {
        unsigned int  c2_second_afc_mode : 1;  /* bit[0]   : 0:ͨ��2��ģʹ��ͨ��2��ģafc������
                                                             1:ͨ��2��ģʹ��ͨ��2��ģafc������ */
        unsigned int  reserved           : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_C2_SECOND_AFC_MODE_UNION;
#define BBPCOMM_C2_SECOND_AFC_MODE_c2_second_afc_mode_START  (0)
#define BBPCOMM_C2_SECOND_AFC_MODE_c2_second_afc_mode_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_MIPI2_RD_OVERTIME_FLAG_DSP_UNION
 �ṹ˵��  : MIPI2_RD_OVERTIME_FLAG_DSP �Ĵ����ṹ���塣��ַƫ����:0x0D38����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      mipi2_rd_overtime_flag_dsp_reg;
    struct
    {
        unsigned int  mipi2_rd_overtime_flag_dsp : 1;  /* bit[0]   : DSP�ȴ��ض������ʱ��־λ
                                                                     1:��ʱ   */
        unsigned int  reserved                   : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_MIPI2_RD_OVERTIME_FLAG_DSP_UNION;
#define BBPCOMM_MIPI2_RD_OVERTIME_FLAG_DSP_mipi2_rd_overtime_flag_dsp_START  (0)
#define BBPCOMM_MIPI2_RD_OVERTIME_FLAG_DSP_mipi2_rd_overtime_flag_dsp_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_SSI2_RD_OVERTIME_FLAG_DSP_UNION
 �ṹ˵��  : SSI2_RD_OVERTIME_FLAG_DSP �Ĵ����ṹ���塣��ַƫ����:0x0D3C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      ssi2_rd_overtime_flag_dsp_reg;
    struct
    {
        unsigned int  ssi2_rd_overtime_flag_dsp : 1;  /* bit[0]   : DSP�ȴ��ض������ʱ��־λ
                                                                    1:��ʱ   */
        unsigned int  reserved                  : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_SSI2_RD_OVERTIME_FLAG_DSP_UNION;
#define BBPCOMM_SSI2_RD_OVERTIME_FLAG_DSP_ssi2_rd_overtime_flag_dsp_START  (0)
#define BBPCOMM_SSI2_RD_OVERTIME_FLAG_DSP_ssi2_rd_overtime_flag_dsp_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_MIPI2_RD_OVERTIME_CLR_UNION
 �ṹ˵��  : MIPI2_RD_OVERTIME_CLR �Ĵ����ṹ���塣��ַƫ����:0x0D40����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      mipi2_rd_overtime_clr_reg;
    struct
    {
        unsigned int  mipi2_rd_overtime_clr_imi : 1;  /* bit[0]   : DSP�ȴ��ض������ʱ��,�峭ʱ��־λ���� */
        unsigned int  reserved                  : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_MIPI2_RD_OVERTIME_CLR_UNION;
#define BBPCOMM_MIPI2_RD_OVERTIME_CLR_mipi2_rd_overtime_clr_imi_START  (0)
#define BBPCOMM_MIPI2_RD_OVERTIME_CLR_mipi2_rd_overtime_clr_imi_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_SSI2_RD_OVERTIME_CLR_UNION
 �ṹ˵��  : SSI2_RD_OVERTIME_CLR �Ĵ����ṹ���塣��ַƫ����:0x0D44����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      ssi2_rd_overtime_clr_reg;
    struct
    {
        unsigned int  ssi2_rd_overtime_clr_imi : 1;  /* bit[0]   : DSP�ȴ��ض������ʱ��,�峭ʱ��־λ���� */
        unsigned int  reserved                 : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_SSI2_RD_OVERTIME_CLR_UNION;
#define BBPCOMM_SSI2_RD_OVERTIME_CLR_ssi2_rd_overtime_clr_imi_START  (0)
#define BBPCOMM_SSI2_RD_OVERTIME_CLR_ssi2_rd_overtime_clr_imi_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_RD_RESULT_FLAG_RFIC2_UNION
 �ṹ˵��  : RD_RESULT_FLAG_RFIC2 �Ĵ����ṹ���塣��ַƫ����:0x0D88����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_rfic2_reg;
    struct
    {
        unsigned int  rd_result_flag_rfic2 : 1;  /* bit[0]   : ���лض�ָ��ִ�����,����ȡ�߻ض�����
                                                               1:���лض�ָ������,DSP���԰�λ�ö�ȡSSI�ض���� */
        unsigned int  reserved             : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_RFIC2_UNION;
#define BBPCOMM_RD_RESULT_FLAG_RFIC2_rd_result_flag_rfic2_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_RFIC2_rd_result_flag_rfic2_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_RD_RESULT_FLAG_RFIC2_CLR_UNION
 �ṹ˵��  : RD_RESULT_FLAG_RFIC2_CLR �Ĵ����ṹ���塣��ַƫ����:0x0D8C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_rfic2_clr_reg;
    struct
    {
        unsigned int  rd_result_flag_rfic2_clr : 1;  /* bit[0]   : 1:DSPȡ�����лض����ݺ�,д��clr�ź����־λ */
        unsigned int  reserved                 : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_RFIC2_CLR_UNION;
#define BBPCOMM_RD_RESULT_FLAG_RFIC2_CLR_rd_result_flag_rfic2_clr_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_RFIC2_CLR_rd_result_flag_rfic2_clr_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_RD_RESULT_FLAG_MIPI2_UNION
 �ṹ˵��  : RD_RESULT_FLAG_MIPI2 �Ĵ����ṹ���塣��ַƫ����:0x0DD0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_mipi2_reg;
    struct
    {
        unsigned int  rd_result_flag_mipi2 : 1;  /* bit[0]   : ���лض�ָ��ִ�����,����ȡ�߻ض�����
                                                               1:���лض�ָ������,DSP���԰�λ�ö�ȡMIPI�ض����,�����������ֱ�ӿ���MIPI��־λ��ͬ */
        unsigned int  reserved             : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_MIPI2_UNION;
#define BBPCOMM_RD_RESULT_FLAG_MIPI2_rd_result_flag_mipi2_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_MIPI2_rd_result_flag_mipi2_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_RD_RESULT_FLAG_MIPI2_CLR_UNION
 �ṹ˵��  : RD_RESULT_FLAG_MIPI2_CLR �Ĵ����ṹ���塣��ַƫ����:0x0DD4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_mipi2_clr_reg;
    struct
    {
        unsigned int  rd_result_flag_mipi2_clr : 1;  /* bit[0]   : 1:DSPȡ�����лض����ݺ�,д��clr�ź����־λ,�����������ֱ�ӿ���MIPI��־λ��ͬ */
        unsigned int  reserved                 : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_MIPI2_CLR_UNION;
#define BBPCOMM_RD_RESULT_FLAG_MIPI2_CLR_rd_result_flag_mipi2_clr_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_MIPI2_CLR_rd_result_flag_mipi2_clr_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_RD_END_FLAG_MIPI2_SOFT_UNION
 �ṹ˵��  : RD_END_FLAG_MIPI2_SOFT �Ĵ����ṹ���塣��ַƫ����:0x0DE0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      rd_end_flag_mipi2_soft_reg;
    struct
    {
        unsigned int  rd_end_flag_mipi2_soft : 1;  /* bit[0]   : �����ֱ�ӿ���MIPI2 master,������xbbp���ͻض�ָ��ʱ,�ض�������Чָʾ */
        unsigned int  reserved               : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_RD_END_FLAG_MIPI2_SOFT_UNION;
#define BBPCOMM_RD_END_FLAG_MIPI2_SOFT_rd_end_flag_mipi2_soft_START  (0)
#define BBPCOMM_RD_END_FLAG_MIPI2_SOFT_rd_end_flag_mipi2_soft_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_MIPI2_GRANT_DSP_UNION
 �ṹ˵��  : MIPI2_GRANT_DSP �Ĵ����ṹ���塣��ַƫ����:0x0DE4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      mipi2_grant_dsp_reg;
    struct
    {
        unsigned int  mipi2_grant_dsp : 1;  /* bit[0]   : �����ֱ�ӿ���MIPI2 master
                                                          1:������Է���CFG_IND����mipi0
                                                          0:����ȴ�mipi2��Ȩʹ�� */
        unsigned int  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_MIPI2_GRANT_DSP_UNION;
#define BBPCOMM_MIPI2_GRANT_DSP_mipi2_grant_dsp_START  (0)
#define BBPCOMM_MIPI2_GRANT_DSP_mipi2_grant_dsp_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_DSP_MIPI2_EN_IMI_UNION
 �ṹ˵��  : DSP_MIPI2_EN_IMI �Ĵ����ṹ���塣��ַƫ����:0x0DF0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dsp_mipi2_en_imi_reg;
    struct
    {
        unsigned int  dsp_mipi2_en_imi : 1;  /* bit[0]   : �����ֱ�ӿ���MIPI2 master,���������ߴ�ָʾ,����xbbp��MIPI0�Ŀ��� */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_DSP_MIPI2_EN_IMI_UNION;
#define BBPCOMM_DSP_MIPI2_EN_IMI_dsp_mipi2_en_imi_START  (0)
#define BBPCOMM_DSP_MIPI2_EN_IMI_dsp_mipi2_en_imi_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_DSP_MIPI2_CFG_IND_IMI_UNION
 �ṹ˵��  : DSP_MIPI2_CFG_IND_IMI �Ĵ����ṹ���塣��ַƫ����:0x0DF4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dsp_mipi2_cfg_ind_imi_reg;
    struct
    {
        unsigned int  dsp_mipi2_cfg_ind_imi : 1;  /* bit[0]   : �����ֱ�ӿ���MIPI2 master,���ߴ�dsp_mipi0_en��,��������������� */
        unsigned int  reserved              : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_DSP_MIPI2_CFG_IND_IMI_UNION;
#define BBPCOMM_DSP_MIPI2_CFG_IND_IMI_dsp_mipi2_cfg_ind_imi_START  (0)
#define BBPCOMM_DSP_MIPI2_CFG_IND_IMI_dsp_mipi2_cfg_ind_imi_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_DSP_MIPI2_RD_CLR_UNION
 �ṹ˵��  : DSP_MIPI2_RD_CLR �Ĵ����ṹ���塣��ַƫ����:0x0DF8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dsp_mipi2_rd_clr_reg;
    struct
    {
        unsigned int  dsp_mipi2_rd_clr : 1;  /* bit[0]   : �����ֱ�ӿ���MIPI2 master,ȡ�߻ض����ݺ�,���־λ���� */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_DSP_MIPI2_RD_CLR_UNION;
#define BBPCOMM_DSP_MIPI2_RD_CLR_dsp_mipi2_rd_clr_START  (0)
#define BBPCOMM_DSP_MIPI2_RD_CLR_dsp_mipi2_rd_clr_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_ABB2_LINE_CONTROL_CMD_UNION
 �ṹ˵��  : ABB2_LINE_CONTROL_CMD �Ĵ����ṹ���塣��ַƫ����:0x0DFC����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      abb2_line_control_cmd_reg;
    struct
    {
        unsigned int  abb2_line_control_cmd_sel : 1;  /* bit[0-0] : ABB2�߿�ǿ��ģʽ��
                                                                    1����ʾ���ǿ�䣬��ʱ��������ǿ�����Ч��
                                                                    0����ʾ��CTU���ݸ�BBP������
                                                                    Ĭ��ֵΪ0��
                                                                    �����á� */
        unsigned int  abb2_mode_sel_cmd         : 3;  /* bit[1-3] : ���ǿ��ģʽabb2_mode_sel. */
        unsigned int  abb2_tx_en_cmd            : 1;  /* bit[4-4] : ���ǿ��ģʽabb2_tx_en. */
        unsigned int  abb2_rxa_en_cmd           : 1;  /* bit[5-5] : ���ǿ��ģʽabb2_rxa_en. */
        unsigned int  abb2_rxb_en_cmd           : 1;  /* bit[6-6] : ���ǿ��ģʽabb2_rxb_en. */
        unsigned int  abb2_blka_en_cmd          : 1;  /* bit[7-7] : ���ǿ��ģʽabb2_rxa_blk_en. */
        unsigned int  abb2_blkb_en_cmd          : 1;  /* bit[8-8] : ���ǿ��ģʽabb2_rxb_blk_en. */
        unsigned int  reserved                  : 23; /* bit[9-31]: ���� */
    } reg;
} BBPCOMM_ABB2_LINE_CONTROL_CMD_UNION;
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_abb2_line_control_cmd_sel_START  (0)
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_abb2_line_control_cmd_sel_END    (0)
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_abb2_mode_sel_cmd_START          (1)
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_abb2_mode_sel_cmd_END            (3)
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_abb2_tx_en_cmd_START             (4)
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_abb2_tx_en_cmd_END               (4)
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_abb2_rxa_en_cmd_START            (5)
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_abb2_rxa_en_cmd_END              (5)
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_abb2_rxb_en_cmd_START            (6)
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_abb2_rxb_en_cmd_END              (6)
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_abb2_blka_en_cmd_START           (7)
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_abb2_blka_en_cmd_END             (7)
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_abb2_blkb_en_cmd_START           (8)
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_abb2_blkb_en_cmd_END             (8)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CH2_BBP_SEL_UNION
 �ṹ˵��  : CH2_BBP_SEL �Ĵ����ṹ���塣��ַƫ����:0x0E00����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      ch2_bbp_sel_reg;
    struct
    {
        unsigned int  ch2_bbp_sel : 3;  /* bit[0-2] : V9R1�汾����������á� */
        unsigned int  reserved    : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_CH2_BBP_SEL_UNION;
#define BBPCOMM_CH2_BBP_SEL_ch2_bbp_sel_START  (0)
#define BBPCOMM_CH2_BBP_SEL_ch2_bbp_sel_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_MIPI2_FUNC_SEL_UNION
 �ṹ˵��  : CPU_MIPI2_FUNC_SEL �Ĵ����ṹ���塣��ַƫ����:0x0E04����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi2_func_sel_reg;
    struct
    {
        unsigned int  cpu_mipi2_func_sel : 1;  /* bit[0]   : cpu����mipi����,����Ϊ1������������, ����ʱ����Ϊ0 */
        unsigned int  reserved           : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_CPU_MIPI2_FUNC_SEL_UNION;
#define BBPCOMM_CPU_MIPI2_FUNC_SEL_cpu_mipi2_func_sel_START  (0)
#define BBPCOMM_CPU_MIPI2_FUNC_SEL_cpu_mipi2_func_sel_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_MIPI2_TEST_FUNC_UNION
 �ṹ˵��  : CPU_MIPI2_TEST_FUNC �Ĵ����ṹ���塣��ַƫ����:0x0E08����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi2_test_func_reg;
    struct
    {
        unsigned int  cpu_mipi2_test_func : 1;  /* bit[0]   : cpu����mipi����,������ */
        unsigned int  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_CPU_MIPI2_TEST_FUNC_UNION;
#define BBPCOMM_CPU_MIPI2_TEST_FUNC_cpu_mipi2_test_func_START  (0)
#define BBPCOMM_CPU_MIPI2_TEST_FUNC_cpu_mipi2_test_func_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_MIPI2_SCLK_TEST_UNION
 �ṹ˵��  : CPU_MIPI2_SCLK_TEST �Ĵ����ṹ���塣��ַƫ����:0x0E0C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi2_sclk_test_reg;
    struct
    {
        unsigned int  cpu_mipi2_sclk_test : 1;  /* bit[0]   : cpu����mipi����, ������ */
        unsigned int  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_CPU_MIPI2_SCLK_TEST_UNION;
#define BBPCOMM_CPU_MIPI2_SCLK_TEST_cpu_mipi2_sclk_test_START  (0)
#define BBPCOMM_CPU_MIPI2_SCLK_TEST_cpu_mipi2_sclk_test_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_MIPI2_SDATA_TEST_UNION
 �ṹ˵��  : CPU_MIPI2_SDATA_TEST �Ĵ����ṹ���塣��ַƫ����:0x0E10����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi2_sdata_test_reg;
    struct
    {
        unsigned int  cpu_mipi2_sdata_test : 1;  /* bit[0]   : cpu����mipi����, ������ */
        unsigned int  reserved             : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_CPU_MIPI2_SDATA_TEST_UNION;
#define BBPCOMM_CPU_MIPI2_SDATA_TEST_cpu_mipi2_sdata_test_START  (0)
#define BBPCOMM_CPU_MIPI2_SDATA_TEST_cpu_mipi2_sdata_test_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_DSP_MIPI2_CLR_IND_IMI_UNION
 �ṹ˵��  : DSP_MIPI2_CLR_IND_IMI �Ĵ����ṹ���塣��ַƫ����:0x0E14����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      dsp_mipi2_clr_ind_imi_reg;
    struct
    {
        unsigned int  dsp_mipi2_clr_ind_imi : 1;  /* bit[0]   : cpu����mipi����,mipi2master���쳣�ź� */
        unsigned int  reserved              : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_DSP_MIPI2_CLR_IND_IMI_UNION;
#define BBPCOMM_DSP_MIPI2_CLR_IND_IMI_dsp_mipi2_clr_ind_imi_START  (0)
#define BBPCOMM_DSP_MIPI2_CLR_IND_IMI_dsp_mipi2_clr_ind_imi_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_MIPI2_FIFO_CLR_IMI_UNION
 �ṹ˵��  : CPU_MIPI2_FIFO_CLR_IMI �Ĵ����ṹ���塣��ַƫ����:0x0E18����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi2_fifo_clr_imi_reg;
    struct
    {
        unsigned int  cpu_mipi2_fifo_clr_imi : 1;  /* bit[0]   : mipi2�洢����������ͬ��FIFO��λ�ź� */
        unsigned int  reserved               : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_CPU_MIPI2_FIFO_CLR_IMI_UNION;
#define BBPCOMM_CPU_MIPI2_FIFO_CLR_IMI_cpu_mipi2_fifo_clr_imi_START  (0)
#define BBPCOMM_CPU_MIPI2_FIFO_CLR_IMI_cpu_mipi2_fifo_clr_imi_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_SSI2_FIFO_CLR_IMI_UNION
 �ṹ˵��  : CPU_SSI2_FIFO_CLR_IMI �Ĵ����ṹ���塣��ַƫ����:0x0E1C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_ssi2_fifo_clr_imi_reg;
    struct
    {
        unsigned int  cpu_ssi2_fifo_clr_imi : 1;  /* bit[0]   : ssi2�洢����������ͬ��FIFO��λ�ź� */
        unsigned int  reserved              : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_CPU_SSI2_FIFO_CLR_IMI_UNION;
#define BBPCOMM_CPU_SSI2_FIFO_CLR_IMI_cpu_ssi2_fifo_clr_imi_START  (0)
#define BBPCOMM_CPU_SSI2_FIFO_CLR_IMI_cpu_ssi2_fifo_clr_imi_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_UNION
 �ṹ˵��  : CPU_RX2_TX0_CKG_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x0E20����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_rx2_tx0_ckg_bypass_reg;
    struct
    {
        unsigned int  cpu_rx2_lte_ckg_bypass : 1;  /* bit[0]    : Lģͨ��2 RX ABB��·ʱ���ſ���·�ź� */
        unsigned int  cpu_rx2_tds_ckg_bypass : 1;  /* bit[1]    : TDSͨ��2 RX ABB��·ʱ���ſ���·�ź� */
        unsigned int  cpu_rx2_w_ckg_bypass   : 1;  /* bit[2]    : Wģͨ��2 RX ABB��·ʱ���ſ���·�ź� */
        unsigned int  cpu_rx2_g1_ckg_bypass  : 1;  /* bit[3]    : G1ͨ��2 RX ABB��·ʱ���ſ���·�ź� */
        unsigned int  cpu_rx2_g2_ckg_bypass  : 1;  /* bit[4]    : G2ͨ��2 RX ABB��·ʱ���ſ���·�ź� */
        unsigned int  cpu_tx2_lte_ckg_bypass : 1;  /* bit[5]    : Lģͨ��2 TX ABB��·ʱ���ſ���·�ź� */
        unsigned int  cpu_tx2_tds_ckg_bypass : 1;  /* bit[6]    : TDSͨ��2 TX ABB��·ʱ���ſ���·�ź� */
        unsigned int  cpu_tx2_w_ckg_bypass   : 1;  /* bit[7]    : Wģͨ��2 TX ABB��·ʱ���ſ���·�ź� */
        unsigned int  cpu_tx2_g1_ckg_bypass  : 1;  /* bit[8]    : G1ͨ��2 TX ABB��·ʱ���ſ���·�ź� */
        unsigned int  cpu_tx2_g2_ckg_bypass  : 1;  /* bit[9]    : G2ͨ��2 TX ABB��·ʱ���ſ���·�ź� */
        unsigned int  cpu_rx2_c_ckg_bypass   : 1;  /* bit[10]   : Cģͨ��2 RX ABB��·ʱ���ſ���·�ź� */
        unsigned int  cpu_tx2_c_ckg_bypass   : 1;  /* bit[11]   : Cģͨ��2 TX ABB��·ʱ���ſ���·�ź� */
        unsigned int  reserved               : 20; /* bit[12-31]: ���� */
    } reg;
} BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_UNION;
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_rx2_lte_ckg_bypass_START  (0)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_rx2_lte_ckg_bypass_END    (0)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_rx2_tds_ckg_bypass_START  (1)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_rx2_tds_ckg_bypass_END    (1)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_rx2_w_ckg_bypass_START    (2)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_rx2_w_ckg_bypass_END      (2)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_rx2_g1_ckg_bypass_START   (3)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_rx2_g1_ckg_bypass_END     (3)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_rx2_g2_ckg_bypass_START   (4)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_rx2_g2_ckg_bypass_END     (4)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_tx2_lte_ckg_bypass_START  (5)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_tx2_lte_ckg_bypass_END    (5)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_tx2_tds_ckg_bypass_START  (6)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_tx2_tds_ckg_bypass_END    (6)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_tx2_w_ckg_bypass_START    (7)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_tx2_w_ckg_bypass_END      (7)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_tx2_g1_ckg_bypass_START   (8)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_tx2_g1_ckg_bypass_END     (8)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_tx2_g2_ckg_bypass_START   (9)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_tx2_g2_ckg_bypass_END     (9)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_rx2_c_ckg_bypass_START    (10)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_rx2_c_ckg_bypass_END      (10)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_tx2_c_ckg_bypass_START    (11)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_tx2_c_ckg_bypass_END      (11)


/*****************************************************************************
 �ṹ��    : BBPCOMM_MIPI3_RD_OVERTIME_FLAG_DSP_UNION
 �ṹ˵��  : MIPI3_RD_OVERTIME_FLAG_DSP �Ĵ����ṹ���塣��ַƫ����:0x0E38����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      mipi3_rd_overtime_flag_dsp_reg;
    struct
    {
        unsigned int  mipi3_rd_overtime_flag_dsp : 1;  /* bit[0]   : DSP�ȴ��ض������ʱ��־λ
                                                                     1:��ʱ   */
        unsigned int  reserved                   : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_MIPI3_RD_OVERTIME_FLAG_DSP_UNION;
#define BBPCOMM_MIPI3_RD_OVERTIME_FLAG_DSP_mipi3_rd_overtime_flag_dsp_START  (0)
#define BBPCOMM_MIPI3_RD_OVERTIME_FLAG_DSP_mipi3_rd_overtime_flag_dsp_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_MIPI3_RD_OVERTIME_CLR_UNION
 �ṹ˵��  : MIPI3_RD_OVERTIME_CLR �Ĵ����ṹ���塣��ַƫ����:0x0E40����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      mipi3_rd_overtime_clr_reg;
    struct
    {
        unsigned int  mipi3_rd_overtime_clr_imi : 1;  /* bit[0]   : DSP�ȴ��ض������ʱ��,�峭ʱ��־λ���� */
        unsigned int  reserved                  : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_MIPI3_RD_OVERTIME_CLR_UNION;
#define BBPCOMM_MIPI3_RD_OVERTIME_CLR_mipi3_rd_overtime_clr_imi_START  (0)
#define BBPCOMM_MIPI3_RD_OVERTIME_CLR_mipi3_rd_overtime_clr_imi_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_MIPI3_FUNC_SEL_UNION
 �ṹ˵��  : CPU_MIPI3_FUNC_SEL �Ĵ����ṹ���塣��ַƫ����:0x0E44����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi3_func_sel_reg;
    struct
    {
        unsigned int  cpu_mipi3_func_sel : 1;  /* bit[0]   : cpu����mipi����,����Ϊ1������������, ����ʱ����Ϊ0 */
        unsigned int  reserved           : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_CPU_MIPI3_FUNC_SEL_UNION;
#define BBPCOMM_CPU_MIPI3_FUNC_SEL_cpu_mipi3_func_sel_START  (0)
#define BBPCOMM_CPU_MIPI3_FUNC_SEL_cpu_mipi3_func_sel_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_MIPI3_TEST_FUNC_UNION
 �ṹ˵��  : CPU_MIPI3_TEST_FUNC �Ĵ����ṹ���塣��ַƫ����:0x0E48����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi3_test_func_reg;
    struct
    {
        unsigned int  cpu_mipi3_test_func : 1;  /* bit[0]   : cpu����mipi����,������ */
        unsigned int  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_CPU_MIPI3_TEST_FUNC_UNION;
#define BBPCOMM_CPU_MIPI3_TEST_FUNC_cpu_mipi3_test_func_START  (0)
#define BBPCOMM_CPU_MIPI3_TEST_FUNC_cpu_mipi3_test_func_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_MIPI3_SCLK_TEST_UNION
 �ṹ˵��  : CPU_MIPI3_SCLK_TEST �Ĵ����ṹ���塣��ַƫ����:0x0E4C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi3_sclk_test_reg;
    struct
    {
        unsigned int  cpu_mipi3_sclk_test : 1;  /* bit[0]   : cpu����mipi����, ������ */
        unsigned int  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_CPU_MIPI3_SCLK_TEST_UNION;
#define BBPCOMM_CPU_MIPI3_SCLK_TEST_cpu_mipi3_sclk_test_START  (0)
#define BBPCOMM_CPU_MIPI3_SCLK_TEST_cpu_mipi3_sclk_test_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_MIPI3_SDATA_TEST_UNION
 �ṹ˵��  : CPU_MIPI3_SDATA_TEST �Ĵ����ṹ���塣��ַƫ����:0x0E50����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi3_sdata_test_reg;
    struct
    {
        unsigned int  cpu_mipi3_sdata_test : 1;  /* bit[0]   : cpu����mipi����, ������ */
        unsigned int  reserved             : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_CPU_MIPI3_SDATA_TEST_UNION;
#define BBPCOMM_CPU_MIPI3_SDATA_TEST_cpu_mipi3_sdata_test_START  (0)
#define BBPCOMM_CPU_MIPI3_SDATA_TEST_cpu_mipi3_sdata_test_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_DSP_MIPI3_CLR_IND_IMI_UNION
 �ṹ˵��  : DSP_MIPI3_CLR_IND_IMI �Ĵ����ṹ���塣��ַƫ����:0x0E54����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      dsp_mipi3_clr_ind_imi_reg;
    struct
    {
        unsigned int  dsp_mipi3_clr_ind_imi : 1;  /* bit[0]   : cpu����mipi����,mipi2master���쳣�ź� */
        unsigned int  reserved              : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_DSP_MIPI3_CLR_IND_IMI_UNION;
#define BBPCOMM_DSP_MIPI3_CLR_IND_IMI_dsp_mipi3_clr_ind_imi_START  (0)
#define BBPCOMM_DSP_MIPI3_CLR_IND_IMI_dsp_mipi3_clr_ind_imi_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_MIPI3_FIFO_CLR_IMI_UNION
 �ṹ˵��  : CPU_MIPI3_FIFO_CLR_IMI �Ĵ����ṹ���塣��ַƫ����:0x0E58����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi3_fifo_clr_imi_reg;
    struct
    {
        unsigned int  cpu_mipi3_fifo_clr_imi : 1;  /* bit[0]   : mipi3�洢����������ͬ��FIFO��λ�ź� */
        unsigned int  reserved               : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_CPU_MIPI3_FIFO_CLR_IMI_UNION;
#define BBPCOMM_CPU_MIPI3_FIFO_CLR_IMI_cpu_mipi3_fifo_clr_imi_START  (0)
#define BBPCOMM_CPU_MIPI3_FIFO_CLR_IMI_cpu_mipi3_fifo_clr_imi_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_APT_CH_SEL2_UNION
 �ṹ˵��  : APT_CH_SEL2 �Ĵ����ṹ���塣��ַƫ����:0x0E5C����ֵ:0x00000002�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      apt_ch_sel2_reg;
    struct
    {
        unsigned int  apt_ch_sel2 : 2;  /* bit[0-1] : apt_pdm2/apt_vpen2�ź���Դ��
                                                      2'd0��������ͨ��0
                                                      2'd1��������ͨ��1
                                                      2'd2��������ͨ��2
                                                      2'd3��ǿ�Ƶ͵�ƽ��� */
        unsigned int  reserved    : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_APT_CH_SEL2_UNION;
#define BBPCOMM_APT_CH_SEL2_apt_ch_sel2_START  (0)
#define BBPCOMM_APT_CH_SEL2_apt_ch_sel2_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_AFC_CH_SEL2_UNION
 �ṹ˵��  : AFC_CH_SEL2 �Ĵ����ṹ���塣��ַƫ����:0x0E60����ֵ:0x00000002�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      afc_ch_sel2_reg;
    struct
    {
        unsigned int  afc_ch_sel2 : 2;  /* bit[0-1] : afc pdm2�ź���Դ��
                                                      2'd0��������ͨ��0
                                                      2'd1��������ͨ��1
                                                      2'd2��������ͨ��2
                                                      2'd3��ǿ�Ƶ͵�ƽ��� */
        unsigned int  reserved    : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_AFC_CH_SEL2_UNION;
#define BBPCOMM_AFC_CH_SEL2_afc_ch_sel2_START  (0)
#define BBPCOMM_AFC_CH_SEL2_afc_ch_sel2_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_PMU_CH_SEL2_UNION
 �ṹ˵��  : PMU_CH_SEL2 �Ĵ����ṹ���塣��ַƫ����:0x0E64����ֵ:0x00000002�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      pmu_ch_sel2_reg;
    struct
    {
        unsigned int  pmu_ch_sel2 : 2;  /* bit[0-1] : auxdac2�ź���Դ��
                                                      2'd0��������ͨ��0
                                                      2'd1��������ͨ��1
                                                      2'd2��������ͨ��2
                                                      2'd3��ǿ�Ƶ͵�ƽ��� */
        unsigned int  reserved    : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_PMU_CH_SEL2_UNION;
#define BBPCOMM_PMU_CH_SEL2_pmu_ch_sel2_START  (0)
#define BBPCOMM_PMU_CH_SEL2_pmu_ch_sel2_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_RD_RESULT_FLAG_MIPI3_UNION
 �ṹ˵��  : RD_RESULT_FLAG_MIPI3 �Ĵ����ṹ���塣��ַƫ����:0x0ED0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_mipi3_reg;
    struct
    {
        unsigned int  rd_result_flag_mipi3 : 1;  /* bit[0]   : ���лض�ָ��ִ�����,����ȡ�߻ض�����
                                                               1:���лض�ָ������,DSP���԰�λ�ö�ȡMIPI�ض����,�����������ֱ�ӿ���MIPI��־λ��ͬ */
        unsigned int  reserved             : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_MIPI3_UNION;
#define BBPCOMM_RD_RESULT_FLAG_MIPI3_rd_result_flag_mipi3_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_MIPI3_rd_result_flag_mipi3_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_RD_RESULT_FLAG_MIPI3_CLR_UNION
 �ṹ˵��  : RD_RESULT_FLAG_MIPI3_CLR �Ĵ����ṹ���塣��ַƫ����:0x0ED4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_mipi3_clr_reg;
    struct
    {
        unsigned int  rd_result_flag_mipi3_clr : 1;  /* bit[0]   : 1:DSPȡ�����лض����ݺ�,д��clr�ź����־λ,�����������ֱ�ӿ���MIPI��־λ��ͬ */
        unsigned int  reserved                 : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_MIPI3_CLR_UNION;
#define BBPCOMM_RD_RESULT_FLAG_MIPI3_CLR_rd_result_flag_mipi3_clr_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_MIPI3_CLR_rd_result_flag_mipi3_clr_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_RD_END_FLAG_MIPI3_SOFT_UNION
 �ṹ˵��  : RD_END_FLAG_MIPI3_SOFT �Ĵ����ṹ���塣��ַƫ����:0x0EE0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      rd_end_flag_mipi3_soft_reg;
    struct
    {
        unsigned int  rd_end_flag_mipi3_soft : 1;  /* bit[0]   : �����ֱ�ӿ���MIPI3 master,������xbbp���ͻض�ָ��ʱ,�ض�������Чָʾ */
        unsigned int  reserved               : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_RD_END_FLAG_MIPI3_SOFT_UNION;
#define BBPCOMM_RD_END_FLAG_MIPI3_SOFT_rd_end_flag_mipi3_soft_START  (0)
#define BBPCOMM_RD_END_FLAG_MIPI3_SOFT_rd_end_flag_mipi3_soft_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_MIPI3_GRANT_DSP_UNION
 �ṹ˵��  : MIPI3_GRANT_DSP �Ĵ����ṹ���塣��ַƫ����:0x0EE4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      mipi3_grant_dsp_reg;
    struct
    {
        unsigned int  mipi3_grant_dsp : 1;  /* bit[0]   : �����ֱ�ӿ���MIPI3 master
                                                          1:������Է���CFG_IND����mipi0
                                                          0:����ȴ�mipi3��Ȩʹ�� */
        unsigned int  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_MIPI3_GRANT_DSP_UNION;
#define BBPCOMM_MIPI3_GRANT_DSP_mipi3_grant_dsp_START  (0)
#define BBPCOMM_MIPI3_GRANT_DSP_mipi3_grant_dsp_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_DSP_MIPI3_EN_IMI_UNION
 �ṹ˵��  : DSP_MIPI3_EN_IMI �Ĵ����ṹ���塣��ַƫ����:0x0EF0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dsp_mipi3_en_imi_reg;
    struct
    {
        unsigned int  dsp_mipi3_en_imi : 1;  /* bit[0]   : �����ֱ�ӿ���MIPI3 master,���������ߴ�ָʾ,����xbbp��MIPI0�Ŀ��� */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_DSP_MIPI3_EN_IMI_UNION;
#define BBPCOMM_DSP_MIPI3_EN_IMI_dsp_mipi3_en_imi_START  (0)
#define BBPCOMM_DSP_MIPI3_EN_IMI_dsp_mipi3_en_imi_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_DSP_MIPI3_CFG_IND_IMI_UNION
 �ṹ˵��  : DSP_MIPI3_CFG_IND_IMI �Ĵ����ṹ���塣��ַƫ����:0x0EF4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dsp_mipi3_cfg_ind_imi_reg;
    struct
    {
        unsigned int  dsp_mipi3_cfg_ind_imi : 1;  /* bit[0]   : �����ֱ�ӿ���MIPI3 master,���ߴ�dsp_mipi0_en��,��������������� */
        unsigned int  reserved              : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_DSP_MIPI3_CFG_IND_IMI_UNION;
#define BBPCOMM_DSP_MIPI3_CFG_IND_IMI_dsp_mipi3_cfg_ind_imi_START  (0)
#define BBPCOMM_DSP_MIPI3_CFG_IND_IMI_dsp_mipi3_cfg_ind_imi_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_DSP_MIPI3_RD_CLR_UNION
 �ṹ˵��  : DSP_MIPI3_RD_CLR �Ĵ����ṹ���塣��ַƫ����:0x0EF8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dsp_mipi3_rd_clr_reg;
    struct
    {
        unsigned int  dsp_mipi3_rd_clr : 1;  /* bit[0]   : �����ֱ�ӿ���MIPI3 master,ȡ�߻ض����ݺ�,���־λ���� */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_DSP_MIPI3_RD_CLR_UNION;
#define BBPCOMM_DSP_MIPI3_RD_CLR_dsp_mipi3_rd_clr_START  (0)
#define BBPCOMM_DSP_MIPI3_RD_CLR_dsp_mipi3_rd_clr_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_LTE_SOFT_ANTPA_SEL_UNION
 �ṹ˵��  : LTE_SOFT_ANTPA_SEL �Ĵ����ṹ���塣��ַƫ����:0x0F50����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      lte_soft_antpa_sel_reg;
    struct
    {
        unsigned int  lte_soft_antpa_sel : 31; /* bit[0-30] : LTEģ���߿����������ֵ
                                                              lte_soft_antpa_en�ź���Чʱ��Ч */
        unsigned int  reserved           : 1;  /* bit[31-31]: ���� */
    } reg;
} BBPCOMM_LTE_SOFT_ANTPA_SEL_UNION;
#define BBPCOMM_LTE_SOFT_ANTPA_SEL_lte_soft_antpa_sel_START  (0)
#define BBPCOMM_LTE_SOFT_ANTPA_SEL_lte_soft_antpa_sel_END    (30)


/*****************************************************************************
 �ṹ��    : BBPCOMM_W_SOFT_ANTPA_SEL_UNION
 �ṹ˵��  : W_SOFT_ANTPA_SEL �Ĵ����ṹ���塣��ַƫ����:0x0F54����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      w_soft_antpa_sel_reg;
    struct
    {
        unsigned int  w_soft_antpa_sel : 31; /* bit[0-30] : wģ���߿����������ֵ
                                                            w_soft_antpa_en�ź���Чʱ��Ч */
        unsigned int  reserved         : 1;  /* bit[31-31]: ���� */
    } reg;
} BBPCOMM_W_SOFT_ANTPA_SEL_UNION;
#define BBPCOMM_W_SOFT_ANTPA_SEL_w_soft_antpa_sel_START  (0)
#define BBPCOMM_W_SOFT_ANTPA_SEL_w_soft_antpa_sel_END    (30)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TDS_SOFT_ANTPA_SEL_UNION
 �ṹ˵��  : TDS_SOFT_ANTPA_SEL �Ĵ����ṹ���塣��ַƫ����:0x0F58����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      tds_soft_antpa_sel_reg;
    struct
    {
        unsigned int  tds_soft_antpa_sel : 31; /* bit[0-30] : tdsģ���߿����������ֵ
                                                              tds_soft_antpa_en�ź���Чʱ��Ч */
        unsigned int  reserved           : 1;  /* bit[31-31]: ���� */
    } reg;
} BBPCOMM_TDS_SOFT_ANTPA_SEL_UNION;
#define BBPCOMM_TDS_SOFT_ANTPA_SEL_tds_soft_antpa_sel_START  (0)
#define BBPCOMM_TDS_SOFT_ANTPA_SEL_tds_soft_antpa_sel_END    (30)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GM_SOFT_ANTPA_SEL_UNION
 �ṹ˵��  : GM_SOFT_ANTPA_SEL �Ĵ����ṹ���塣��ַƫ����:0x0F5C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gm_soft_antpa_sel_reg;
    struct
    {
        unsigned int  gm_soft_antpa_sel : 31; /* bit[0-30] : GMģ���߿����������ֵ
                                                             gm_soft_antpa_en�ź���Чʱ��Ч */
        unsigned int  reserved          : 1;  /* bit[31-31]: ���� */
    } reg;
} BBPCOMM_GM_SOFT_ANTPA_SEL_UNION;
#define BBPCOMM_GM_SOFT_ANTPA_SEL_gm_soft_antpa_sel_START  (0)
#define BBPCOMM_GM_SOFT_ANTPA_SEL_gm_soft_antpa_sel_END    (30)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GS_SOFT_ANTPA_SEL_UNION
 �ṹ˵��  : GS_SOFT_ANTPA_SEL �Ĵ����ṹ���塣��ַƫ����:0x0F60����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gs_soft_antpa_sel_reg;
    struct
    {
        unsigned int  gs_soft_antpa_sel : 31; /* bit[0-30] : gsģ���߿����������ֵ
                                                             gs_soft_antpa_en�ź���Чʱ��Ч */
        unsigned int  reserved          : 1;  /* bit[31-31]: ���� */
    } reg;
} BBPCOMM_GS_SOFT_ANTPA_SEL_UNION;
#define BBPCOMM_GS_SOFT_ANTPA_SEL_gs_soft_antpa_sel_START  (0)
#define BBPCOMM_GS_SOFT_ANTPA_SEL_gs_soft_antpa_sel_END    (30)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C_SOFT_ANTPA_SEL_UNION
 �ṹ˵��  : C_SOFT_ANTPA_SEL �Ĵ����ṹ���塣��ַƫ����:0x0F64����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c_soft_antpa_sel_reg;
    struct
    {
        unsigned int  c_soft_antpa_sel : 31; /* bit[0-30] : Cģ���߿����������ֵ
                                                            c_soft_antpa_en�ź���Чʱ��Ч */
        unsigned int  reserved         : 1;  /* bit[31-31]: ���� */
    } reg;
} BBPCOMM_C_SOFT_ANTPA_SEL_UNION;
#define BBPCOMM_C_SOFT_ANTPA_SEL_c_soft_antpa_sel_START  (0)
#define BBPCOMM_C_SOFT_ANTPA_SEL_c_soft_antpa_sel_END    (30)


/*****************************************************************************
 �ṹ��    : BBPCOMM_LTE_SOFT_ANTPA_EN_UNION
 �ṹ˵��  : LTE_SOFT_ANTPA_EN �Ĵ����ṹ���塣��ַƫ����:0x0F68����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      lte_soft_antpa_en_reg;
    struct
    {
        unsigned int  lte_soft_antpa_en : 1;  /* bit[0-0] : LTEģ���߿����������ʹ��
                                                            0��ʹ���߼�����ֵ
                                                            1��ʹ���������ֵlte_soft_antpa_sel */
        unsigned int  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_LTE_SOFT_ANTPA_EN_UNION;
#define BBPCOMM_LTE_SOFT_ANTPA_EN_lte_soft_antpa_en_START  (0)
#define BBPCOMM_LTE_SOFT_ANTPA_EN_lte_soft_antpa_en_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_W_SOFT_ANTPA_EN_UNION
 �ṹ˵��  : W_SOFT_ANTPA_EN �Ĵ����ṹ���塣��ַƫ����:0x0F6C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      w_soft_antpa_en_reg;
    struct
    {
        unsigned int  w_soft_antpa_en : 1;  /* bit[0-0] : Wģ���߿����������ʹ��
                                                          0��ʹ���߼�����ֵ
                                                          1��ʹ���������ֵw_soft_antpa_sel */
        unsigned int  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_W_SOFT_ANTPA_EN_UNION;
#define BBPCOMM_W_SOFT_ANTPA_EN_w_soft_antpa_en_START  (0)
#define BBPCOMM_W_SOFT_ANTPA_EN_w_soft_antpa_en_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TDS_SOFT_ANTPA_EN_UNION
 �ṹ˵��  : TDS_SOFT_ANTPA_EN �Ĵ����ṹ���塣��ַƫ����:0x0FA0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      tds_soft_antpa_en_reg;
    struct
    {
        unsigned int  tds_soft_antpa_en : 1;  /* bit[0-0] : TDSģ���߿����������ʹ��
                                                            0��ʹ���߼�����ֵ
                                                            1��ʹ���������ֵtds_soft_antpa_sel */
        unsigned int  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_TDS_SOFT_ANTPA_EN_UNION;
#define BBPCOMM_TDS_SOFT_ANTPA_EN_tds_soft_antpa_en_START  (0)
#define BBPCOMM_TDS_SOFT_ANTPA_EN_tds_soft_antpa_en_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GM_SOFT_ANTPA_EN_UNION
 �ṹ˵��  : GM_SOFT_ANTPA_EN �Ĵ����ṹ���塣��ַƫ����:0x0FA4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gm_soft_antpa_en_reg;
    struct
    {
        unsigned int  gm_soft_antpa_en : 1;  /* bit[0-0] : GMģ���߿����������ʹ��
                                                           0��ʹ���߼�����ֵ
                                                           1��ʹ���������ֵgm_soft_antpa_sel */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_GM_SOFT_ANTPA_EN_UNION;
#define BBPCOMM_GM_SOFT_ANTPA_EN_gm_soft_antpa_en_START  (0)
#define BBPCOMM_GM_SOFT_ANTPA_EN_gm_soft_antpa_en_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GS_SOFT_ANTPA_EN_UNION
 �ṹ˵��  : GS_SOFT_ANTPA_EN �Ĵ����ṹ���塣��ַƫ����:0x0FA8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gs_soft_antpa_en_reg;
    struct
    {
        unsigned int  gs_soft_antpa_en : 1;  /* bit[0-0] : GSģ���߿����������ʹ��
                                                           0��ʹ���߼�����ֵ
                                                           1��ʹ���������ֵgs_soft_antpa_sel */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_GS_SOFT_ANTPA_EN_UNION;
#define BBPCOMM_GS_SOFT_ANTPA_EN_gs_soft_antpa_en_START  (0)
#define BBPCOMM_GS_SOFT_ANTPA_EN_gs_soft_antpa_en_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C_SOFT_ANTPA_EN_UNION
 �ṹ˵��  : C_SOFT_ANTPA_EN �Ĵ����ṹ���塣��ַƫ����:0x0FAC����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c_soft_antpa_en_reg;
    struct
    {
        unsigned int  c_soft_antpa_en : 1;  /* bit[0-0] : Cģ���߿����������ʹ��
                                                          0��ʹ���߼�����ֵ
                                                          1��ʹ���������ֵ_soft_antpa_sel */
        unsigned int  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_C_SOFT_ANTPA_EN_UNION;
#define BBPCOMM_C_SOFT_ANTPA_EN_c_soft_antpa_en_START  (0)
#define BBPCOMM_C_SOFT_ANTPA_EN_c_soft_antpa_en_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CH0_SOFT_ANTPA_SEL_UNION
 �ṹ˵��  : CH0_SOFT_ANTPA_SEL �Ĵ����ṹ���塣��ַƫ����:0x0FB0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      ch0_soft_antpa_sel_reg;
    struct
    {
        unsigned int  ch0_soft_antpa_sel : 31; /* bit[0-30] : ͨ��0ģʽ��Чʱ������õ����߿�������ֵ */
        unsigned int  reserved           : 1;  /* bit[31-31]: ���� */
    } reg;
} BBPCOMM_CH0_SOFT_ANTPA_SEL_UNION;
#define BBPCOMM_CH0_SOFT_ANTPA_SEL_ch0_soft_antpa_sel_START  (0)
#define BBPCOMM_CH0_SOFT_ANTPA_SEL_ch0_soft_antpa_sel_END    (30)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CH1_SOFT_ANTPA_SEL_UNION
 �ṹ˵��  : CH1_SOFT_ANTPA_SEL �Ĵ����ṹ���塣��ַƫ����:0x0FB4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      ch1_soft_antpa_sel_reg;
    struct
    {
        unsigned int  ch1_soft_antpa_sel : 31; /* bit[0-30] : ͨ��1ģʽ��Чʱ������õ����߿�������ֵ */
        unsigned int  reserved           : 1;  /* bit[31-31]: ���� */
    } reg;
} BBPCOMM_CH1_SOFT_ANTPA_SEL_UNION;
#define BBPCOMM_CH1_SOFT_ANTPA_SEL_ch1_soft_antpa_sel_START  (0)
#define BBPCOMM_CH1_SOFT_ANTPA_SEL_ch1_soft_antpa_sel_END    (30)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CH2_SOFT_ANTPA_SEL_UNION
 �ṹ˵��  : CH2_SOFT_ANTPA_SEL �Ĵ����ṹ���塣��ַƫ����:0x0FB8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      ch2_soft_antpa_sel_reg;
    struct
    {
        unsigned int  ch2_soft_antpa_sel : 31; /* bit[0-30] : ͨ��2ģʽ��Чʱ������õ����߿�������ֵ */
        unsigned int  reserved           : 1;  /* bit[31-31]: ���� */
    } reg;
} BBPCOMM_CH2_SOFT_ANTPA_SEL_UNION;
#define BBPCOMM_CH2_SOFT_ANTPA_SEL_ch2_soft_antpa_sel_START  (0)
#define BBPCOMM_CH2_SOFT_ANTPA_SEL_ch2_soft_antpa_sel_END    (30)


/*****************************************************************************
 �ṹ��    : BBPCOMM_LTE_SOFT_RST_UNION
 �ṹ˵��  : LTE_SOFT_RST �Ĵ����ṹ���塣��ַƫ����:0x0FC0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      lte_soft_rst_reg;
    struct
    {
        unsigned int  lte_soft_rst : 1;  /* bit[0-0] : ���� */
        unsigned int  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_LTE_SOFT_RST_UNION;
#define BBPCOMM_LTE_SOFT_RST_lte_soft_rst_START  (0)
#define BBPCOMM_LTE_SOFT_RST_lte_soft_rst_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_W_SOFT_RST_UNION
 �ṹ˵��  : W_SOFT_RST �Ĵ����ṹ���塣��ַƫ����:0x0FC4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      w_soft_rst_reg;
    struct
    {
        unsigned int  w_soft_rst : 1;  /* bit[0-0] : ���� */
        unsigned int  reserved   : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_W_SOFT_RST_UNION;
#define BBPCOMM_W_SOFT_RST_w_soft_rst_START  (0)
#define BBPCOMM_W_SOFT_RST_w_soft_rst_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TDS_SOFT_RST_UNION
 �ṹ˵��  : TDS_SOFT_RST �Ĵ����ṹ���塣��ַƫ����:0x0FC8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      tds_soft_rst_reg;
    struct
    {
        unsigned int  tds_soft_rst : 1;  /* bit[0-0] : ���� */
        unsigned int  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_TDS_SOFT_RST_UNION;
#define BBPCOMM_TDS_SOFT_RST_tds_soft_rst_START  (0)
#define BBPCOMM_TDS_SOFT_RST_tds_soft_rst_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GM_SOFT_RST_UNION
 �ṹ˵��  : GM_SOFT_RST �Ĵ����ṹ���塣��ַƫ����:0x0FCC����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gm_soft_rst_reg;
    struct
    {
        unsigned int  gm_soft_rst : 1;  /* bit[0-0] : ���� */
        unsigned int  reserved    : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_GM_SOFT_RST_UNION;
#define BBPCOMM_GM_SOFT_RST_gm_soft_rst_START  (0)
#define BBPCOMM_GM_SOFT_RST_gm_soft_rst_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GS_SOFT_RST_UNION
 �ṹ˵��  : GS_SOFT_RST �Ĵ����ṹ���塣��ַƫ����:0x0FD0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gs_soft_rst_reg;
    struct
    {
        unsigned int  gs_soft_rst : 1;  /* bit[0-0] : ���� */
        unsigned int  reserved    : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_GS_SOFT_RST_UNION;
#define BBPCOMM_GS_SOFT_RST_gs_soft_rst_START  (0)
#define BBPCOMM_GS_SOFT_RST_gs_soft_rst_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C_SOFT_RST_UNION
 �ṹ˵��  : C_SOFT_RST �Ĵ����ṹ���塣��ַƫ����:0x0FD4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c_soft_rst_reg;
    struct
    {
        unsigned int  c_soft_rst : 1;  /* bit[0-0] : ���� */
        unsigned int  reserved   : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_C_SOFT_RST_UNION;
#define BBPCOMM_C_SOFT_RST_c_soft_rst_START  (0)
#define BBPCOMM_C_SOFT_RST_c_soft_rst_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_DBG_MIPI_CH_MASK_UNION
 �ṹ˵��  : DBG_MIPI_CH_MASK �Ĵ����ṹ���塣��ַƫ����:0x0FD8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dbg_mipi_ch_mask_reg;
    struct
    {
        unsigned int  dbg_mipi_ch_mask : 4;  /* bit[0-3] : ��ά�ɲ�mipi�ɼ�����ͨ������ָʾ��
                                                           dbg_mipi_ch_mask[X],X=0~3,��
                                                           0��ͨ��X��mipi���ݲ��ɼ�
                                                           1���ɼ�ͨ��X��mipi���� */
        unsigned int  reserved         : 28; /* bit[4-31]: ���� */
    } reg;
} BBPCOMM_DBG_MIPI_CH_MASK_UNION;
#define BBPCOMM_DBG_MIPI_CH_MASK_dbg_mipi_ch_mask_START  (0)
#define BBPCOMM_DBG_MIPI_CH_MASK_dbg_mipi_ch_mask_END    (3)


/*****************************************************************************
 �ṹ��    : BBPCOMM_DBG_SSI_CH_MASK_UNION
 �ṹ˵��  : DBG_SSI_CH_MASK �Ĵ����ṹ���塣��ַƫ����:0x0FDC����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dbg_ssi_ch_mask_reg;
    struct
    {
        unsigned int  dbg_ssi_ch_mask : 3;  /* bit[0-2] : ��ά�ɲ�ssi�ɼ�����ͨ������ָʾ��
                                                          dbg_ssi_ch_mask[X],X=0~2,��
                                                          0��ͨ��X��mipi���ݲ��ɼ�
                                                          1���ɼ�ͨ��X��mipi���� */
        unsigned int  reserved        : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_DBG_SSI_CH_MASK_UNION;
#define BBPCOMM_DBG_SSI_CH_MASK_dbg_ssi_ch_mask_START  (0)
#define BBPCOMM_DBG_SSI_CH_MASK_dbg_ssi_ch_mask_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_ANTPA_MODE_SEL_UNION
 �ṹ˵��  : CPU_ANTPA_MODE_SEL �Ĵ����ṹ���塣��ַƫ����:0x0FF4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      cpu_antpa_mode_sel_reg;
    struct
    {
        unsigned int  cpu_antpa_mode_sel : 4;  /* bit[0-3] : �����߿�ģʽѡ���źţ�bit[3:0]�ֱ����com2fem_antpa_sel[5:2]��ģʽѡ��
                                                             com2fem_antpa_sel[2]��bit[0]Ϊ0ʱѡ��RFFE GPIO˫modem����Ժ��������ߵ�ƽ��Ч��������1ʱѡ��RFFE GPIO˫modem�����Ժ��������͵�ƽ��Ч�����Դ����ƣ�com2fem_antpa_sel[5:3]�ֱ���bit[3:1]��Ӧ���ơ� */
        unsigned int  reserved           : 28; /* bit[4-31]: ���� */
    } reg;
} BBPCOMM_CPU_ANTPA_MODE_SEL_UNION;
#define BBPCOMM_CPU_ANTPA_MODE_SEL_cpu_antpa_mode_sel_START  (0)
#define BBPCOMM_CPU_ANTPA_MODE_SEL_cpu_antpa_mode_sel_END    (3)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_ABB_CH_TX_MASK_SEL_UNION
 �ṹ˵��  : CPU_ABB_CH_TX_MASK_SEL �Ĵ����ṹ���塣��ַƫ����:0x0FF8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      cpu_abb_ch_tx_mask_sel_reg;
    struct
    {
        unsigned int  cpu_abb_ch0_tx_mask_sel : 1;  /* bit[0-0] : 0:com2abb_ch0/1_tx_en����com2fem_antpa_sel[29]����
                                                                  1:com2fem_antpa_sel[29]Ϊ1��com2abb_ch0/1_tx_enǿ�����ͣ�
                                                                  Ϊ0���߼���������� */
        unsigned int  cpu_abb_ch1_tx_mask_sel : 1;  /* bit[1-1] : 0:com2abb_ch2_tx_en����com2fem_antpa_sel[30]����
                                                                  1:com2fem_antpa_sel[30]Ϊ1��com2abb_ch2_tx_enǿ�����ͣ�
                                                                  Ϊ0���߼���������� */
        unsigned int  reserved                : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_CPU_ABB_CH_TX_MASK_SEL_UNION;
#define BBPCOMM_CPU_ABB_CH_TX_MASK_SEL_cpu_abb_ch0_tx_mask_sel_START  (0)
#define BBPCOMM_CPU_ABB_CH_TX_MASK_SEL_cpu_abb_ch0_tx_mask_sel_END    (0)
#define BBPCOMM_CPU_ABB_CH_TX_MASK_SEL_cpu_abb_ch1_tx_mask_sel_START  (1)
#define BBPCOMM_CPU_ABB_CH_TX_MASK_SEL_cpu_abb_ch1_tx_mask_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_PD_CH_SEL0_UNION
 �ṹ˵��  : PD_CH_SEL0 �Ĵ����ṹ���塣��ַƫ����:0x1000����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      pd_ch_sel0_reg;
    struct
    {
        unsigned int  pd_ch_sel0 : 2;  /* bit[0-1] : PD���˿�0�ź���Դ��
                                                     2'd0��������ͨ��0
                                                     2'd1��������ͨ��1
                                                     2'd2��������ͨ��2
                                                     2'd3��ǿ�Ƶ͵�ƽ��� */
        unsigned int  reserved   : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_PD_CH_SEL0_UNION;
#define BBPCOMM_PD_CH_SEL0_pd_ch_sel0_START  (0)
#define BBPCOMM_PD_CH_SEL0_pd_ch_sel0_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_PD_CH_SEL1_UNION
 �ṹ˵��  : PD_CH_SEL1 �Ĵ����ṹ���塣��ַƫ����:0x1004����ֵ:0x00000001�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      pd_ch_sel1_reg;
    struct
    {
        unsigned int  pd_ch_sel1 : 2;  /* bit[0-1] : PD���˿�1�ź���Դ��
                                                     2'd0��������ͨ��0
                                                     2'd1��������ͨ��1
                                                     2'd2��������ͨ��2
                                                     2'd3��ǿ�Ƶ͵�ƽ��� */
        unsigned int  reserved   : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_PD_CH_SEL1_UNION;
#define BBPCOMM_PD_CH_SEL1_pd_ch_sel1_START  (0)
#define BBPCOMM_PD_CH_SEL1_pd_ch_sel1_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TCVR_ON_CFG_OUT0_UNION
 �ṹ˵��  : TCVR_ON_CFG_OUT0 �Ĵ����ṹ���塣��ַƫ����:0x1008����ֵ:0x00000001�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      tcvr_on_cfg_out0_reg;
    struct
    {
        unsigned int  tcvr_on_cfg_out0 : 1;  /* bit[0-0] : tcvr_on���pin��0�ź�Դѡ�񿪹أ�
                                                           0��������ͨ��0���߼�ѡ�������
                                                           1�������������������� */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_TCVR_ON_CFG_OUT0_UNION;
#define BBPCOMM_TCVR_ON_CFG_OUT0_tcvr_on_cfg_out0_START  (0)
#define BBPCOMM_TCVR_ON_CFG_OUT0_tcvr_on_cfg_out0_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TCVR_ON_CFG_OUT1_UNION
 �ṹ˵��  : TCVR_ON_CFG_OUT1 �Ĵ����ṹ���塣��ַƫ����:0x100C����ֵ:0x00000001�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      tcvr_on_cfg_out1_reg;
    struct
    {
        unsigned int  tcvr_on_cfg_out1 : 1;  /* bit[0-0] : tcvr_on���pin��1�ź�Դѡ�񿪹أ�
                                                           0��������ͨ��1���߼�ѡ�������
                                                           1�������������������� */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_TCVR_ON_CFG_OUT1_UNION;
#define BBPCOMM_TCVR_ON_CFG_OUT1_tcvr_on_cfg_out1_START  (0)
#define BBPCOMM_TCVR_ON_CFG_OUT1_tcvr_on_cfg_out1_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TCVR_ON_CFG_OUT2_UNION
 �ṹ˵��  : TCVR_ON_CFG_OUT2 �Ĵ����ṹ���塣��ַƫ����:0x1010����ֵ:0x00000001�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      tcvr_on_cfg_out2_reg;
    struct
    {
        unsigned int  tcvr_on_cfg_out2 : 1;  /* bit[0-0] : tcvr_on���pin��2�ź�Դѡ�񿪹أ�
                                                           0��������ͨ��2���߼�ѡ�������
                                                           1�������������������� */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_TCVR_ON_CFG_OUT2_UNION;
#define BBPCOMM_TCVR_ON_CFG_OUT2_tcvr_on_cfg_out2_START  (0)
#define BBPCOMM_TCVR_ON_CFG_OUT2_tcvr_on_cfg_out2_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_LTE_TCVR_ON_CFG_PIN0_UNION
 �ṹ˵��  : LTE_TCVR_ON_CFG_PIN0 �Ĵ����ṹ���塣��ַƫ����:0x1014����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      lte_tcvr_on_cfg_pin0_reg;
    struct
    {
        unsigned int  lte_tcvr_on_cfg_pin0 : 1;  /* bit[0-0] : �������LTEģtcvr_on�źſ�����Χ
                                                               tcvr_on��pin��0�ź����
                                                               ����1Ϊ���ߣ�0Ϊ���� */
        unsigned int  reserved             : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_LTE_TCVR_ON_CFG_PIN0_UNION;
#define BBPCOMM_LTE_TCVR_ON_CFG_PIN0_lte_tcvr_on_cfg_pin0_START  (0)
#define BBPCOMM_LTE_TCVR_ON_CFG_PIN0_lte_tcvr_on_cfg_pin0_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_W_TCVR_ON_CFG_PIN0_UNION
 �ṹ˵��  : W_TCVR_ON_CFG_PIN0 �Ĵ����ṹ���塣��ַƫ����:0x1018����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      w_tcvr_on_cfg_pin0_reg;
    struct
    {
        unsigned int  w_tcvr_on_cfg_pin0 : 1;  /* bit[0-0] : �������Wģtcvr_on�źſ�����Χ
                                                             tcvr_on��pin��0�ź����
                                                             ����1Ϊ���ߣ�0Ϊ���� */
        unsigned int  reserved           : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_W_TCVR_ON_CFG_PIN0_UNION;
#define BBPCOMM_W_TCVR_ON_CFG_PIN0_w_tcvr_on_cfg_pin0_START  (0)
#define BBPCOMM_W_TCVR_ON_CFG_PIN0_w_tcvr_on_cfg_pin0_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TDS_TCVR_ON_CFG_PIN0_UNION
 �ṹ˵��  : TDS_TCVR_ON_CFG_PIN0 �Ĵ����ṹ���塣��ַƫ����:0x101C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      tds_tcvr_on_cfg_pin0_reg;
    struct
    {
        unsigned int  tds_tcvr_on_cfg_pin0 : 1;  /* bit[0-0] : �������TDSģtcvr_on�źſ�����Χ
                                                               tcvr_on��pin��0�ź����
                                                               ����1Ϊ���ߣ�0Ϊ���� */
        unsigned int  reserved             : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_TDS_TCVR_ON_CFG_PIN0_UNION;
#define BBPCOMM_TDS_TCVR_ON_CFG_PIN0_tds_tcvr_on_cfg_pin0_START  (0)
#define BBPCOMM_TDS_TCVR_ON_CFG_PIN0_tds_tcvr_on_cfg_pin0_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GM_TCVR_ON_CFG_PIN0_UNION
 �ṹ˵��  : GM_TCVR_ON_CFG_PIN0 �Ĵ����ṹ���塣��ַƫ����:0x1020����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gm_tcvr_on_cfg_pin0_reg;
    struct
    {
        unsigned int  gm_tcvr_on_cfg_pin0 : 1;  /* bit[0-0] : �������GMģtcvr_on�źſ�����Χ
                                                              tcvr_on��pin��0�ź����
                                                              ����1Ϊ���ߣ�0Ϊ���� */
        unsigned int  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_GM_TCVR_ON_CFG_PIN0_UNION;
#define BBPCOMM_GM_TCVR_ON_CFG_PIN0_gm_tcvr_on_cfg_pin0_START  (0)
#define BBPCOMM_GM_TCVR_ON_CFG_PIN0_gm_tcvr_on_cfg_pin0_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GS_TCVR_ON_CFG_PIN0_UNION
 �ṹ˵��  : GS_TCVR_ON_CFG_PIN0 �Ĵ����ṹ���塣��ַƫ����:0x1024����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gs_tcvr_on_cfg_pin0_reg;
    struct
    {
        unsigned int  gs_tcvr_on_cfg_pin0 : 1;  /* bit[0-0] : �������GSģtcvr_on�źſ�����Χ
                                                              tcvr_on��pin��0�ź����
                                                              ����1Ϊ���ߣ�0Ϊ���� */
        unsigned int  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_GS_TCVR_ON_CFG_PIN0_UNION;
#define BBPCOMM_GS_TCVR_ON_CFG_PIN0_gs_tcvr_on_cfg_pin0_START  (0)
#define BBPCOMM_GS_TCVR_ON_CFG_PIN0_gs_tcvr_on_cfg_pin0_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C_TCVR_ON_CFG_PIN0_UNION
 �ṹ˵��  : C_TCVR_ON_CFG_PIN0 �Ĵ����ṹ���塣��ַƫ����:0x1028����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c_tcvr_on_cfg_pin0_reg;
    struct
    {
        unsigned int  c_tcvr_on_cfg_pin0 : 1;  /* bit[0-0] : �������Cģtcvr_on�źſ�����Χ
                                                             tcvr_on��pin��0�ź����
                                                             ����1Ϊ���ߣ�0Ϊ���� */
        unsigned int  reserved           : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_C_TCVR_ON_CFG_PIN0_UNION;
#define BBPCOMM_C_TCVR_ON_CFG_PIN0_c_tcvr_on_cfg_pin0_START  (0)
#define BBPCOMM_C_TCVR_ON_CFG_PIN0_c_tcvr_on_cfg_pin0_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_LTE_TCVR_ON_CFG_PIN1_UNION
 �ṹ˵��  : LTE_TCVR_ON_CFG_PIN1 �Ĵ����ṹ���塣��ַƫ����:0x102C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      lte_tcvr_on_cfg_pin1_reg;
    struct
    {
        unsigned int  lte_tcvr_on_cfg_pin1 : 1;  /* bit[0-0] : �������LTEģtcvr_on�źſ�����Χ
                                                               tcvr_on��pin��1�ź����
                                                               ����1Ϊ���ߣ�0Ϊ���� */
        unsigned int  reserved             : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_LTE_TCVR_ON_CFG_PIN1_UNION;
#define BBPCOMM_LTE_TCVR_ON_CFG_PIN1_lte_tcvr_on_cfg_pin1_START  (0)
#define BBPCOMM_LTE_TCVR_ON_CFG_PIN1_lte_tcvr_on_cfg_pin1_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_W_TCVR_ON_CFG_PIN1_UNION
 �ṹ˵��  : W_TCVR_ON_CFG_PIN1 �Ĵ����ṹ���塣��ַƫ����:0x1030����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      w_tcvr_on_cfg_pin1_reg;
    struct
    {
        unsigned int  w_tcvr_on_cfg_pin1 : 1;  /* bit[0-0] : �������Wģtcvr_on�źſ�����Χ
                                                             tcvr_on��pin��1�ź����
                                                             ����1Ϊ���ߣ�0Ϊ���� */
        unsigned int  reserved           : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_W_TCVR_ON_CFG_PIN1_UNION;
#define BBPCOMM_W_TCVR_ON_CFG_PIN1_w_tcvr_on_cfg_pin1_START  (0)
#define BBPCOMM_W_TCVR_ON_CFG_PIN1_w_tcvr_on_cfg_pin1_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TDS_TCVR_ON_CFG_PIN1_UNION
 �ṹ˵��  : TDS_TCVR_ON_CFG_PIN1 �Ĵ����ṹ���塣��ַƫ����:0x1034����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      tds_tcvr_on_cfg_pin1_reg;
    struct
    {
        unsigned int  tds_tcvr_on_cfg_pin1 : 1;  /* bit[0-0] : �������TDSģtcvr_on�źſ�����Χ
                                                               tcvr_on��pin��1�ź����
                                                               ����1Ϊ���ߣ�0Ϊ���� */
        unsigned int  reserved             : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_TDS_TCVR_ON_CFG_PIN1_UNION;
#define BBPCOMM_TDS_TCVR_ON_CFG_PIN1_tds_tcvr_on_cfg_pin1_START  (0)
#define BBPCOMM_TDS_TCVR_ON_CFG_PIN1_tds_tcvr_on_cfg_pin1_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GM_TCVR_ON_CFG_PIN1_UNION
 �ṹ˵��  : GM_TCVR_ON_CFG_PIN1 �Ĵ����ṹ���塣��ַƫ����:0x1038����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gm_tcvr_on_cfg_pin1_reg;
    struct
    {
        unsigned int  gm_tcvr_on_cfg_pin1 : 1;  /* bit[0-0] : �������GMģtcvr_on�źſ�����Χ
                                                              tcvr_on��pin��1�ź����
                                                              ����1Ϊ���ߣ�0Ϊ���� */
        unsigned int  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_GM_TCVR_ON_CFG_PIN1_UNION;
#define BBPCOMM_GM_TCVR_ON_CFG_PIN1_gm_tcvr_on_cfg_pin1_START  (0)
#define BBPCOMM_GM_TCVR_ON_CFG_PIN1_gm_tcvr_on_cfg_pin1_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GS_TCVR_ON_CFG_PIN1_UNION
 �ṹ˵��  : GS_TCVR_ON_CFG_PIN1 �Ĵ����ṹ���塣��ַƫ����:0x103C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gs_tcvr_on_cfg_pin1_reg;
    struct
    {
        unsigned int  gs_tcvr_on_cfg_pin1 : 1;  /* bit[0-0] : �������GSģtcvr_on�źſ�����Χ
                                                              tcvr_on��pin��1�ź����
                                                              ����1Ϊ���ߣ�0Ϊ���� */
        unsigned int  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_GS_TCVR_ON_CFG_PIN1_UNION;
#define BBPCOMM_GS_TCVR_ON_CFG_PIN1_gs_tcvr_on_cfg_pin1_START  (0)
#define BBPCOMM_GS_TCVR_ON_CFG_PIN1_gs_tcvr_on_cfg_pin1_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C_TCVR_ON_CFG_PIN1_UNION
 �ṹ˵��  : C_TCVR_ON_CFG_PIN1 �Ĵ����ṹ���塣��ַƫ����:0x1040����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c_tcvr_on_cfg_pin1_reg;
    struct
    {
        unsigned int  c_tcvr_on_cfg_pin1 : 1;  /* bit[0-0] : �������Cģtcvr_on�źſ�����Χ
                                                             tcvr_on��pin��1�ź����
                                                             ����1Ϊ���ߣ�0Ϊ���� */
        unsigned int  reserved           : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_C_TCVR_ON_CFG_PIN1_UNION;
#define BBPCOMM_C_TCVR_ON_CFG_PIN1_c_tcvr_on_cfg_pin1_START  (0)
#define BBPCOMM_C_TCVR_ON_CFG_PIN1_c_tcvr_on_cfg_pin1_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_LTE_TCVR_ON_CFG_PIN2_UNION
 �ṹ˵��  : LTE_TCVR_ON_CFG_PIN2 �Ĵ����ṹ���塣��ַƫ����:0x1044����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      lte_tcvr_on_cfg_pin2_reg;
    struct
    {
        unsigned int  lte_tcvr_on_cfg_pin2 : 1;  /* bit[0-0] : �������LTEģtcvr_on�źſ�����Χ
                                                               tcvr_on��pin��2�ź����
                                                               ����1Ϊ���ߣ�0Ϊ���� */
        unsigned int  reserved             : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_LTE_TCVR_ON_CFG_PIN2_UNION;
#define BBPCOMM_LTE_TCVR_ON_CFG_PIN2_lte_tcvr_on_cfg_pin2_START  (0)
#define BBPCOMM_LTE_TCVR_ON_CFG_PIN2_lte_tcvr_on_cfg_pin2_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_W_TCVR_ON_CFG_PIN2_UNION
 �ṹ˵��  : W_TCVR_ON_CFG_PIN2 �Ĵ����ṹ���塣��ַƫ����:0x1048����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      w_tcvr_on_cfg_pin2_reg;
    struct
    {
        unsigned int  w_tcvr_on_cfg_pin2 : 1;  /* bit[0-0] : �������Wģtcvr_on�źſ�����Χ
                                                             tcvr_on��pin��2�ź����
                                                             ����1Ϊ���ߣ�0Ϊ���� */
        unsigned int  reserved           : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_W_TCVR_ON_CFG_PIN2_UNION;
#define BBPCOMM_W_TCVR_ON_CFG_PIN2_w_tcvr_on_cfg_pin2_START  (0)
#define BBPCOMM_W_TCVR_ON_CFG_PIN2_w_tcvr_on_cfg_pin2_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TDS_TCVR_ON_CFG_PIN2_UNION
 �ṹ˵��  : TDS_TCVR_ON_CFG_PIN2 �Ĵ����ṹ���塣��ַƫ����:0x104C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      tds_tcvr_on_cfg_pin2_reg;
    struct
    {
        unsigned int  tds_tcvr_on_cfg_pin2 : 1;  /* bit[0-0] : �������TDSģtcvr_on�źſ�����Χ
                                                               tcvr_on��pin��2�ź����
                                                               ����1Ϊ���ߣ�0Ϊ���� */
        unsigned int  reserved             : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_TDS_TCVR_ON_CFG_PIN2_UNION;
#define BBPCOMM_TDS_TCVR_ON_CFG_PIN2_tds_tcvr_on_cfg_pin2_START  (0)
#define BBPCOMM_TDS_TCVR_ON_CFG_PIN2_tds_tcvr_on_cfg_pin2_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GM_TCVR_ON_CFG_PIN2_UNION
 �ṹ˵��  : GM_TCVR_ON_CFG_PIN2 �Ĵ����ṹ���塣��ַƫ����:0x1050����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gm_tcvr_on_cfg_pin2_reg;
    struct
    {
        unsigned int  gm_tcvr_on_cfg_pin2 : 1;  /* bit[0-0] : �������GMģtcvr_on�źſ�����Χ
                                                              tcvr_on��pin��2�ź����
                                                              ����1Ϊ���ߣ�0Ϊ���� */
        unsigned int  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_GM_TCVR_ON_CFG_PIN2_UNION;
#define BBPCOMM_GM_TCVR_ON_CFG_PIN2_gm_tcvr_on_cfg_pin2_START  (0)
#define BBPCOMM_GM_TCVR_ON_CFG_PIN2_gm_tcvr_on_cfg_pin2_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GS_TCVR_ON_CFG_PIN2_UNION
 �ṹ˵��  : GS_TCVR_ON_CFG_PIN2 �Ĵ����ṹ���塣��ַƫ����:0x1054����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gs_tcvr_on_cfg_pin2_reg;
    struct
    {
        unsigned int  gs_tcvr_on_cfg_pin2 : 1;  /* bit[0-0] : �������GSģtcvr_on�źſ�����Χ
                                                              tcvr_on��pin��2�ź����
                                                              ����1Ϊ���ߣ�0Ϊ���� */
        unsigned int  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_GS_TCVR_ON_CFG_PIN2_UNION;
#define BBPCOMM_GS_TCVR_ON_CFG_PIN2_gs_tcvr_on_cfg_pin2_START  (0)
#define BBPCOMM_GS_TCVR_ON_CFG_PIN2_gs_tcvr_on_cfg_pin2_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_C_TCVR_ON_CFG_PIN2_UNION
 �ṹ˵��  : C_TCVR_ON_CFG_PIN2 �Ĵ����ṹ���塣��ַƫ����:0x1058����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      c_tcvr_on_cfg_pin2_reg;
    struct
    {
        unsigned int  c_tcvr_on_cfg_pin2 : 1;  /* bit[0-0] : �������Cģtcvr_on�źſ�����Χ
                                                             tcvr_on��pin��2�ź����
                                                             ����1Ϊ���ߣ�0Ϊ���� */
        unsigned int  reserved           : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_C_TCVR_ON_CFG_PIN2_UNION;
#define BBPCOMM_C_TCVR_ON_CFG_PIN2_c_tcvr_on_cfg_pin2_START  (0)
#define BBPCOMM_C_TCVR_ON_CFG_PIN2_c_tcvr_on_cfg_pin2_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TCVR_ON_DLY_CYCLE_UNION
 �ṹ˵��  : TCVR_ON_DLY_CYCLE �Ĵ����ṹ���塣��ַƫ����:0x105C����ֵ:0x0000001A�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      tcvr_on_dly_cycle_reg;
    struct
    {
        unsigned int  tcvr_on_dly_cycle : 6;  /* bit[0-5] : ��ͨ��ʵ�����tcvr_on�ӳٵ�����ֵ��
                                                            ���֧��64��cycle����λΪ19.2M�� */
        unsigned int  reserved          : 26; /* bit[6-31]: ���� */
    } reg;
} BBPCOMM_TCVR_ON_DLY_CYCLE_UNION;
#define BBPCOMM_TCVR_ON_DLY_CYCLE_tcvr_on_dly_cycle_START  (0)
#define BBPCOMM_TCVR_ON_DLY_CYCLE_tcvr_on_dly_cycle_END    (5)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TUNER_MIPI_MSAK_UNION
 �ṹ˵��  : TUNER_MIPI_MSAK �Ĵ����ṹ���塣��ַƫ����:0x1060����ֵ:0x00000001�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      tuner_mipi_msak_reg;
    struct
    {
        unsigned int  tuner_mipi_mask : 1;  /* bit[0-0] : tuner mipi�Զ������������μĴ���
                                                          0��ʹ��tuner������
                                                          1��bypass tuner��������tuner mipiָ��ܴ�CTUͨ��0��� */
        unsigned int  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_TUNER_MIPI_MSAK_UNION;
#define BBPCOMM_TUNER_MIPI_MSAK_tuner_mipi_mask_START  (0)
#define BBPCOMM_TUNER_MIPI_MSAK_tuner_mipi_mask_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TUNER_GPIO_M0_LINE_P_MASK_UNION
 �ṹ˵��  : TUNER_GPIO_M0_LINE_P_MASK �Ĵ����ṹ���塣��ַƫ����:0x1064����ֵ:0x00000001�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      tuner_gpio_m0_line_p_mask_reg;
    struct
    {
        unsigned int  tuner_gpio_m0_line_p_mask : 1;  /* bit[0-0] : tuner gpio m0_line_p�߿����μĴ���
                                                                    0��ʹ��tuner���ֵ
                                                                    1��bypass tuner���ֵ��ʹ��CTU���ֵ */
        unsigned int  reserved                  : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_TUNER_GPIO_M0_LINE_P_MASK_UNION;
#define BBPCOMM_TUNER_GPIO_M0_LINE_P_MASK_tuner_gpio_m0_line_p_mask_START  (0)
#define BBPCOMM_TUNER_GPIO_M0_LINE_P_MASK_tuner_gpio_m0_line_p_mask_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TUNER_GPIO_M0_LINE_S_MASK_UNION
 �ṹ˵��  : TUNER_GPIO_M0_LINE_S_MASK �Ĵ����ṹ���塣��ַƫ����:0x1068����ֵ:0x00000001�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      tuner_gpio_m0_line_s_mask_reg;
    struct
    {
        unsigned int  tuner_gpio_m0_line_s_mask : 1;  /* bit[0-0] : tuner gpio m0_line_s�߿����μĴ���
                                                                    0��ʹ��tuner���ֵ
                                                                    1��bypass tuner���ֵ��ʹ��CTU���ֵ */
        unsigned int  reserved                  : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_TUNER_GPIO_M0_LINE_S_MASK_UNION;
#define BBPCOMM_TUNER_GPIO_M0_LINE_S_MASK_tuner_gpio_m0_line_s_mask_START  (0)
#define BBPCOMM_TUNER_GPIO_M0_LINE_S_MASK_tuner_gpio_m0_line_s_mask_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TUNER_GPIO_M1_LINE_MASK_UNION
 �ṹ˵��  : TUNER_GPIO_M1_LINE_MASK �Ĵ����ṹ���塣��ַƫ����:0x106C����ֵ:0x00000001�����:32
 �Ĵ���˵��: �Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      tuner_gpio_m1_line_mask_reg;
    struct
    {
        unsigned int  tuner_gpio_m1_line_mask : 1;  /* bit[0-0] : tuner gpio m1_line�߿����μĴ���
                                                                  0��ʹ��tuner���ֵ
                                                                  1��bypass tuner���ֵ��ʹ��CTU���ֵ */
        unsigned int  reserved                : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_TUNER_GPIO_M1_LINE_MASK_UNION;
#define BBPCOMM_TUNER_GPIO_M1_LINE_MASK_tuner_gpio_m1_line_mask_START  (0)
#define BBPCOMM_TUNER_GPIO_M1_LINE_MASK_tuner_gpio_m1_line_mask_END    (0)


/***======================================================================***
                     (2/3) register_define_mipi_tuner
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : BBPCOMM_MIPI_TUNER_EN_UNION
 �ṹ˵��  : MIPI_TUNER_EN �Ĵ����ṹ���塣��ַƫ����:0x0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      mipi_tuner_en_reg;
    struct
    {
        unsigned int  cpu_mipi_tuner_en_imi        : 1;  /* bit[0]   : MIPI_TUNERģ��ʹ�ܿ��أ�0��ʾ�رգ�1��ʾ�򿪡� */
        unsigned int  reserved_0                   : 3;  /* bit[1-3] :  */
        unsigned int  cpu_mipi_tuner_queue_clr_imi : 1;  /* bit[4]   : MIPI_tunerģ�� */
        unsigned int  reserved_1                   : 27; /* bit[5-31]:  */
    } reg;
} BBPCOMM_MIPI_TUNER_EN_UNION;
#define BBPCOMM_MIPI_TUNER_EN_cpu_mipi_tuner_en_imi_START         (0)
#define BBPCOMM_MIPI_TUNER_EN_cpu_mipi_tuner_en_imi_END           (0)
#define BBPCOMM_MIPI_TUNER_EN_cpu_mipi_tuner_queue_clr_imi_START  (4)
#define BBPCOMM_MIPI_TUNER_EN_cpu_mipi_tuner_queue_clr_imi_END    (4)


/*****************************************************************************
 �ṹ��    : BBPCOMM_FSM_OT_PRT_EN_UNION
 �ṹ˵��  : FSM_OT_PRT_EN �Ĵ����ṹ���塣��ַƫ����:0x8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      fsm_ot_prt_en_reg;
    struct
    {
        unsigned int  fsm_ot_prt_en_imi : 1;  /* bit[0]   : MIPI����״̬����ʱ��������ʹ�ܣ�1��ʾ�򿪱������ܣ�0��ʾ�ر� */
        unsigned int  reserved          : 31; /* bit[1-31]:  */
    } reg;
} BBPCOMM_FSM_OT_PRT_EN_UNION;
#define BBPCOMM_FSM_OT_PRT_EN_fsm_ot_prt_en_imi_START  (0)
#define BBPCOMM_FSM_OT_PRT_EN_fsm_ot_prt_en_imi_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_MIPI_OT_CNT_UNION
 �ṹ˵��  : MIPI_OT_CNT �Ĵ����ṹ���塣��ַƫ����:0xC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      mipi_ot_cnt_reg;
    struct
    {
        unsigned int  mipi_ot_cnt : 16; /* bit[0-15] : ״̬����ʱ��ʱ�� */
        unsigned int  reserved    : 16; /* bit[16-31]:  */
    } reg;
} BBPCOMM_MIPI_OT_CNT_UNION;
#define BBPCOMM_MIPI_OT_CNT_mipi_ot_cnt_START  (0)
#define BBPCOMM_MIPI_OT_CNT_mipi_ot_cnt_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_QUEUE_BUSY_IND_UNION
 �ṹ˵��  : QUEUE_BUSY_IND �Ĵ����ṹ���塣��ַƫ����:0x10����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      queue_busy_ind_reg;
    struct
    {
        unsigned int  req0_busy : 1;  /* bit[0]   : ��ѯ״̬�ϱ� */
        unsigned int  req1_busy : 1;  /* bit[1]   : ��ѯ״̬�ϱ� */
        unsigned int  req2_busy : 1;  /* bit[2]   : ��ѯ״̬�ϱ� */
        unsigned int  reserved  : 29; /* bit[3-31]:  */
    } reg;
} BBPCOMM_QUEUE_BUSY_IND_UNION;
#define BBPCOMM_QUEUE_BUSY_IND_req0_busy_START  (0)
#define BBPCOMM_QUEUE_BUSY_IND_req0_busy_END    (0)
#define BBPCOMM_QUEUE_BUSY_IND_req1_busy_START  (1)
#define BBPCOMM_QUEUE_BUSY_IND_req1_busy_END    (1)
#define BBPCOMM_QUEUE_BUSY_IND_req2_busy_START  (2)
#define BBPCOMM_QUEUE_BUSY_IND_req2_busy_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_M_GEN_RPT_UNION
 �ṹ˵��  : M_GEN_RPT �Ĵ����ṹ���塣��ַƫ����:0x14����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      m_gen_rpt_reg;
    struct
    {
        unsigned int  m0_sync_status_p : 6;  /* bit[0-5]  : m0_p��ǰ״ֵ̬ */
        unsigned int  m0_p_fifo_empty  : 1;  /* bit[6]    : m0_p fifo״̬�ϱ� */
        unsigned int  m0_p_fifo_full   : 1;  /* bit[7]    : m0_p fifo״̬�ϱ� */
        unsigned int  m0_sync_status_s : 6;  /* bit[8-13] : m0_s��ǰ״ֵ̬ */
        unsigned int  m0_s_fifo_empty  : 1;  /* bit[14]   : m0_s fifo״̬�ϱ� */
        unsigned int  m0_s_fifo_full   : 1;  /* bit[15]   : m0_s fifo״̬�ϱ� */
        unsigned int  m1_sync_status   : 6;  /* bit[16-21]: m1��ǰ״ֵ̬ */
        unsigned int  m1_fifo_empty    : 1;  /* bit[22]   : m1 fifo״̬�ϱ� */
        unsigned int  m1_fifo_full     : 1;  /* bit[23]   : m1 fifo״̬�ϱ� */
        unsigned int  reserved         : 8;  /* bit[24-31]:  */
    } reg;
} BBPCOMM_M_GEN_RPT_UNION;
#define BBPCOMM_M_GEN_RPT_m0_sync_status_p_START  (0)
#define BBPCOMM_M_GEN_RPT_m0_sync_status_p_END    (5)
#define BBPCOMM_M_GEN_RPT_m0_p_fifo_empty_START   (6)
#define BBPCOMM_M_GEN_RPT_m0_p_fifo_empty_END     (6)
#define BBPCOMM_M_GEN_RPT_m0_p_fifo_full_START    (7)
#define BBPCOMM_M_GEN_RPT_m0_p_fifo_full_END      (7)
#define BBPCOMM_M_GEN_RPT_m0_sync_status_s_START  (8)
#define BBPCOMM_M_GEN_RPT_m0_sync_status_s_END    (13)
#define BBPCOMM_M_GEN_RPT_m0_s_fifo_empty_START   (14)
#define BBPCOMM_M_GEN_RPT_m0_s_fifo_empty_END     (14)
#define BBPCOMM_M_GEN_RPT_m0_s_fifo_full_START    (15)
#define BBPCOMM_M_GEN_RPT_m0_s_fifo_full_END      (15)
#define BBPCOMM_M_GEN_RPT_m1_sync_status_START    (16)
#define BBPCOMM_M_GEN_RPT_m1_sync_status_END      (21)
#define BBPCOMM_M_GEN_RPT_m1_fifo_empty_START     (22)
#define BBPCOMM_M_GEN_RPT_m1_fifo_empty_END       (22)
#define BBPCOMM_M_GEN_RPT_m1_fifo_full_START      (23)
#define BBPCOMM_M_GEN_RPT_m1_fifo_full_END        (23)


/***======================================================================***
                     (3/3) register_define_mipi_tuner_mem
 ***======================================================================***/


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

#endif /* end of bbp_common_interface.h */
