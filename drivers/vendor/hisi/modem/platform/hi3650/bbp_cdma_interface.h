

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __BBP_CDMA_INTERFACE_H__
#define __BBP_CDMA_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/***======================================================================***
                     (1/20) register_define_c_glb
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31:16]  1w2r˫��RAM��ʱ���ơ�
 bit[15:0]   ����RAM��ʱ���ơ�
   UNION�ṹ:  CBBP_VIRAGE_RM_CTRL_C_0_UNION */
#define CBBP_VIRAGE_RM_CTRL_C_0_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x0)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  ROM��ʱ���ơ�
 bit[15:0]   1rw2rw˫��RAM��ʱ���ơ�
   UNION�ṹ:  CBBP_VIRAGE_RM_CTRL_C_1_UNION */
#define CBBP_VIRAGE_RM_CTRL_C_1_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x4)

/* �Ĵ���˵����
 bit[31:27]  ����
 bit[26]     G��ǰ������
 bit[25]     G���ж�
 bit[24]     G����ʱ
 bit[23]     G��ʱ�Ӳ���
 bit[22]     ��Ƶǰ�˿���ģ�顣
 bit[21]     ǰ�����ݽӿ�ģ�顣
 bit[20]     ����ģ�顣
 bit[19]     ����ģ�顣
 bit[18]     ��������ģ�顣
 bit[17]     �ж�ģ�顣
 bit[16]     ϵͳʱ����CLK���ơ��ڶԸ�ģ�����ʱ�ӿ���ʱ������Ӧbit��1��ʾ�򿪸�ģ���ʱ�ӣ���֮������Ӧbit��0��ʾ�رո�ģ���ʱ�ӡ�
             ��ʱģ�顣
 bit[15:11]  ����
 bit[10]     G��ǰ������
 bit[9]      G���ж�
 bit[8]      G����ʱ
 bit[7]      G��ʱ�Ӳ���
 bit[6]      ��Ƶǰ�˿���ģ�顣
 bit[5]      ǰ�����ݽӿ�ģ�顣
 bit[4]      ����ģ�顣
 bit[3]      ����ģ�顣
 bit[2]      ��������ģ�顣
 bit[1]      �ж�ģ�顣
 bit[0]      ϵͳʱ����RST���ơ��ڶԸ�ģ����и�λʱ������Ӧbit��1��֮���ٽ���Ӧbit��λΪ0��
             ��ʱģ�顣
   UNION�ṹ:  CBBP_SYS_RST_CTRL_C_UNION */
#define CBBP_SYS_RST_CTRL_C_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x8)

/* �Ĵ���˵����
 bit[31:26]  ����
 bit[25]     G���ж�
 bit[24]     G����ʱ
 bit[23]     G��ʱ�Ӳ���
 bit[22]     ��Ƶǰ�˿���ģ�顣
 bit[21]     ǰ�����ݽӿ�ģ�顣
 bit[20]     ����ģ�顣
 bit[19]     ����ģ�顣
 bit[18]     ��������ģ�顣
 bit[17]     �ж�ģ�顣
 bit[16]     IMI��ַƬѡ��������ʹ�ܣ��ߵ�ƽ��Ч�����ź���Ч��ʾ��Ӧģ��δ��ѡ��ʱ����BBP�ڲ���ģ��IMI��ַ��
             ��ʱģ�顣
 bit[15:10]  ����
 bit[9]      G���ж�
 bit[8]      G����ʱ
 bit[7]      G��ʱ�Ӳ���
 bit[6]      ��Ƶǰ�˿���ģ�顣
 bit[5]      ǰ�����ݽӿ�ģ�顣
 bit[4]      ����ģ�顣
 bit[3]      ����ģ�顣
 bit[2]      ��������ģ�顣
 bit[1]      �ж�ģ�顣
 bit[0]      IMIʱ����RST���ơ��ڶԸ�ģ����и�λʱ������Ӧbit��1��֮���ٽ���Ӧbit��λΪ0��
             ��ʱģ�顣
   UNION�ṹ:  CBBP_IMI_RST_CTRL_C_UNION */
#define CBBP_IMI_RST_CTRL_C_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xC)

/* �Ĵ���˵����
   ��      �����汾�Ĵ�����
   UNION�ṹ ���� */
#define CBBP_VERSION_C_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0x10)



/***======================================================================***
                     (2/20) register_define_c_timing
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:0]   ʱ�Ӳ���ʱ�䣬32kʱ�Ӹ������֧��5.12s��
             ˵����ȡֵΪ0�����塣
   UNION�ṹ:  CBBP_C_CK_MSR_PERIOD_UNION */
#define CBBP_C_CK_MSR_PERIOD_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x1000)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ʱ�Ӳ���ʹ�ܡ�BBP��������أ�����ʱ�Ӳ���������������Ϊ0��BBPֹͣʱ�Ӳ�����
   UNION�ṹ:  CBBP_C_CK_MSR_EN_UNION */
#define CBBP_C_CK_MSR_EN_ADDR                         (SOC_BBP_CDMA_BASE_ADDR + 0x1004)

/* �Ĵ���˵����
 bit[31]     ����
 bit[30:0]   ʱ�Ӳ���������ϱ�����ck_msr_period�ڵ�122.88MHzʱ�Ӹ���
   UNION�ṹ:  CBBP_CK_MSR_RPT_UNION */
#define CBBP_CK_MSR_RPT_ADDR                          (SOC_BBP_CDMA_BASE_ADDR + 0x1008)

/* �Ĵ���˵����
 bit[31:29]  ����
 bit[28:24]  
 bit[23:22]  
 bit[21:5]   
 bit[4:0]    ����sys_cnt_1x��ʱ�̣�
             [28:24]��base_cnt_2s�ϵ�ʱ�̣�ȡֵ��Χ0~24��
             [23:22]��base_cnt_80ms�ϵ�ʱ�̣�ȡֵ��Χ0~2��
             [21:5]��base_cnt_26ms�ϵ�ʱ�̣�ȡֵ��Χ0~32768*4-1��
             [4:0]��1/4chip�ڼ�����ȡֵ��Χ0~24
             
   UNION�ṹ:  CBBP_SYS_CNT_1X_GET_POS_UNION */
#define CBBP_SYS_CNT_1X_GET_POS_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x1020)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:24]  
 bit[23:18]  
 bit[17:5]   
 bit[4:0]    sys_cnt_get_posʱ��sys_cnt_1x��ֵ��
             [29:24]��sys_cnt_1x_5p12s��ֵ��
             [23:18]��sys_cnt_1x_80ms��ֵ��
             [17:5]��sys_cnt_1x_1p25ms��ֵ��ȡֵ��Χ0~1536*4-1��
             [4:0]��1/4chip�ڼ�����ȡֵ��Χ0~24
             
   UNION�ṹ:  CBBP_SYS_CNT_1X_GET_VALUE_UNION */
#define CBBP_SYS_CNT_1X_GET_VALUE_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x1024)

/* �Ĵ���˵����
   ��      ����sys_cnt_get_posʱ��sys_cnt_1x��ֵ����λ5.12s��2s
   UNION�ṹ ���� */
#define CBBP_SYS_CNT_1X_GET_VALUE_HIGH_ADDR           (SOC_BBP_CDMA_BASE_ADDR + 0x10B0)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:22]  
 bit[21:5]   
 bit[4:0]    1X��ʱͻ���sys_cnt_1x  80ms֡ͷ��base_cnt�ϵ�λ�á�
             Bit[4:0]��1/4chip�ڼ���0~24
             bit[21:5]��26ms�ڼ���0~32768*4-1
             bit[23:22]��80ms�ڼ���0~2
   UNION�ṹ:  CBBP_SYS_CNT_1X_80MS_POS_CFG_UNION */
#define CBBP_SYS_CNT_1X_80MS_POS_CFG_ADDR             (SOC_BBP_CDMA_BASE_ADDR + 0x10C4)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      Sys_cnt_1x��ʱ��ȡָʾ��
             BBP���յ���ָʾ�󣬵ȴ�base_cnt��sys_cnt_1x_get_posʱ�̣���sys_cnt_1x����Ϊsys_cnt_1x_get_value��
             
   UNION�ṹ:  CBBP_SYS_CNT_1X_GET_RDY_UNION */
#define CBBP_SYS_CNT_1X_GET_RDY_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x1028)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ϵͳ��ʱ��������
             0����ʾ����ߵ���6clk��
             1����ʾ���ұߵ���6clk��
             ˵������ʱ����100��ʱ�ӣ���ˣ�6clkʱ��Ϊ6/100chip
             
   UNION�ṹ:  CBBP_SYS_1X_CHANGE_DIRECTION_UNION */
#define CBBP_SYS_1X_CHANGE_DIRECTION_ADDR             (SOC_BBP_CDMA_BASE_ADDR + 0x102C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ϵͳ��ʱ����ָʾ��
             BBP�ڽ��յ���ָʾ���������PCG���ϵͳ��ʱ
             
   UNION�ṹ:  CBBP_SYS_1X_CHANGE_RDY_UNION */
#define CBBP_SYS_1X_CHANGE_RDY_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x1030)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      �����ȡsys_cnt_1x_80ms_pos��ָʾ��BBP���յ����źź����汾�صļ���ֵ
   UNION�ṹ:  CBBP_SYS_CNT_1X_80MS_POS_RD_UNION */
#define CBBP_SYS_CNT_1X_80MS_POS_RD_ADDR              (SOC_BBP_CDMA_BASE_ADDR + 0x1034)

/* �Ĵ���˵����
 bit[31:25]  ����
 bit[24]     sys_cnt_1x_80ms_pos��Чָʾ��1��ʾ��ȡ�Ľ����Ч
 bit[23:22]  
 bit[21:5]   
 bit[4:0]    sys_cnt_1x  80ms֡ͷ��base_cnt�ϵ�λ�á�
             Bit[4:0]��1/4chip�ڼ���0~24
             bit[21:5]��26ms�ڼ���0~32768*4-1
             bit[23:22]��80ms�ڼ���0~2
   UNION�ṹ:  CBBP_SYS_CNT_1X_80MS_POS_UNION */
#define CBBP_SYS_CNT_1X_80MS_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x1038)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      sys_cnt_1x_80ms_pos_valid�����źţ������sys_cnt_1x_80ms_pos��ȡ��ʹ�ô˼Ĵ���������Ч��־���
   UNION�ṹ:  CBBP_SYS_CNT_1X_80MS_POS_VALID_CLR_UNION */
#define CBBP_SYS_CNT_1X_80MS_POS_VALID_CLR_ADDR       (SOC_BBP_CDMA_BASE_ADDR + 0x103C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��ʱͻ��ʱ����ʱ�жϵ�maskָʾ��
             0����ʾ��mask��
             1����ʾmask���÷�Χ�ڵ��жϣ�
             
   UNION�ṹ:  CBBP_TIMING_INT_1X_MASK_UNION */
#define CBBP_TIMING_INT_1X_MASK_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x1040)

/* �Ĵ���˵����
 bit[31:11]  ����
 bit[10:0]   ��ʱͻ��ʱ����ʱ�жϵ�mask���䣬chipΪ��λ��
   UNION�ṹ:  CBBP_TIMING_INT_1X_MASK_DIS_UNION */
#define CBBP_TIMING_INT_1X_MASK_DIS_ADDR              (SOC_BBP_CDMA_BASE_ADDR + 0x1044)

/* �Ĵ���˵����
 bit[31:22]  ����
 bit[21:16]  
 bit[15:11]  ����
 bit[10:0]   Int1��sys_cnt_1x�ϵ�λ�ã�
             [21:16]��sys_cnt_1x_80ms��ֵ��
             [10:0]��sys_cnt_1x_1p25ms[15:5]��ֵ,chip���ȣ�
             
   UNION�ṹ:  CBBP_TIMING_INT1_SYS_CNT_1X_POS_UNION */
#define CBBP_TIMING_INT1_SYS_CNT_1X_POS_ADDR          (SOC_BBP_CDMA_BASE_ADDR + 0x1048)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    Int1�ж�����ѡ��
             0����ʾ�ж�����Ϊ64chip��
             1����ʾ�ж�����Ϊ128chip��
             2����ʾ�ж�����Ϊ256chip��
             3����ʾ�ж�����Ϊ512chip��
             4����ʾ�ж�����Ϊ1.25ms��
             5����ʾ�ж�����Ϊ5ms��
             6����ʾ�ж�����Ϊ10ms��
             7����ʾ�ж�����Ϊ20ms��
             8����ʾ�ж�����Ϊ40ms��
             9����ʾ�ж�����Ϊ80ms��
             10:��ʾ�ж�����Ϊ384chip��
             
   UNION�ṹ:  CBBP_TIMING_INT1_1X_PERIOD_UNION */
#define CBBP_TIMING_INT1_1X_PERIOD_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x104C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��ʱ�ж�int1��ʹ�ܡ�
             0����ʾ������int1�жϣ�
             1����ʾ����int1�жϣ�
             
   UNION�ṹ:  CBBP_TIMING_INT1_1X_EN_UNION */
#define CBBP_TIMING_INT1_1X_EN_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x1050)

/* �Ĵ���˵����
 bit[31:22]  ����
 bit[21:16]  
 bit[15:11]  ����
 bit[10:0]   Int��sys_cnt_1x�ϵ�λ�ã�
             [21:16]��sys_cnt_1x_80ms��ֵ��
             [10:0]��sys_cnt_1x_1p25ms[15:5]��ֵ,chip���ȣ�
             
   UNION�ṹ:  CBBP_TIMING_INT2_SYS_CNT_1X_POS_UNION */
#define CBBP_TIMING_INT2_SYS_CNT_1X_POS_ADDR          (SOC_BBP_CDMA_BASE_ADDR + 0x1054)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    Int�ж�����ѡ��
             0����ʾ�ж�����Ϊ64chip��
             1����ʾ�ж�����Ϊ128chip��
             2����ʾ�ж�����Ϊ256chip��
             3����ʾ�ж�����Ϊ512chip��
             4����ʾ�ж�����Ϊ1.25ms��
             5����ʾ�ж�����Ϊ5ms��
             6����ʾ�ж�����Ϊ10ms��
             7����ʾ�ж�����Ϊ20ms��
             8����ʾ�ж�����Ϊ40ms��
             9����ʾ�ж�����Ϊ80ms��
             10:��ʾ�ж�����Ϊ384chip��
             
   UNION�ṹ:  CBBP_TIMING_INT2_1X_PERIOD_UNION */
#define CBBP_TIMING_INT2_1X_PERIOD_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x1058)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��ʱ�ж�int��ʹ�ܡ�
             0����ʾ������int�жϣ�
             1����ʾ����int�жϣ�
             
   UNION�ṹ:  CBBP_TIMING_INT2_1X_EN_UNION */
#define CBBP_TIMING_INT2_1X_EN_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x105C)

/* �Ĵ���˵����
 bit[31:22]  ����
 bit[21:16]  
 bit[15:11]  ����
 bit[10:0]   Int��sys_cnt_1x�ϵ�λ�ã�
             [21:16]��sys_cnt_1x_80ms��ֵ��
             [10:0]��sys_cnt_1x_1p25ms[15:5]��ֵ,chip���ȣ�
             
   UNION�ṹ:  CBBP_TIMING_INT3_SYS_CNT_1X_POS_UNION */
#define CBBP_TIMING_INT3_SYS_CNT_1X_POS_ADDR          (SOC_BBP_CDMA_BASE_ADDR + 0x1060)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    Int�ж�����ѡ��
             0����ʾ�ж�����Ϊ64chip��
             1����ʾ�ж�����Ϊ128chip��
             2����ʾ�ж�����Ϊ256chip��
             3����ʾ�ж�����Ϊ512chip��
             4����ʾ�ж�����Ϊ1.25ms��
             5����ʾ�ж�����Ϊ5ms��
             6����ʾ�ж�����Ϊ10ms��
             7����ʾ�ж�����Ϊ20ms��
             8����ʾ�ж�����Ϊ40ms��
             9����ʾ�ж�����Ϊ80ms��
             10:��ʾ�ж�����Ϊ384chip��
             
   UNION�ṹ:  CBBP_TIMING_INT3_1X_PERIOD_UNION */
#define CBBP_TIMING_INT3_1X_PERIOD_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x1064)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��ʱ�ж�int��ʹ�ܡ�
             0����ʾ������int�жϣ�
             1����ʾ����int�жϣ�
             
   UNION�ṹ:  CBBP_TIMING_INT3_1X_EN_UNION */
#define CBBP_TIMING_INT3_1X_EN_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x1068)

/* �Ĵ���˵����
 bit[31:22]  ����
 bit[21:16]  
 bit[15:11]  ����
 bit[10:0]   Int��sys_cnt_1x�ϵ�λ�ã�
             [21:16]��sys_cnt_1x_80ms��ֵ��
             [10:0]��sys_cnt_1x_1p25ms[15:5]��ֵ,chip���ȣ�
             
   UNION�ṹ:  CBBP_TIMING_INT4_SYS_CNT_1X_POS_UNION */
#define CBBP_TIMING_INT4_SYS_CNT_1X_POS_ADDR          (SOC_BBP_CDMA_BASE_ADDR + 0x106C)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    Int�ж�����ѡ��
             0����ʾ�ж�����Ϊ64chip��
             1����ʾ�ж�����Ϊ128chip��
             2����ʾ�ж�����Ϊ256chip��
             3����ʾ�ж�����Ϊ512chip��
             4����ʾ�ж�����Ϊ1.25ms��
             5����ʾ�ж�����Ϊ5ms��
             6����ʾ�ж�����Ϊ10ms��
             7����ʾ�ж�����Ϊ20ms��
             8����ʾ�ж�����Ϊ40ms��
             9����ʾ�ж�����Ϊ80ms��
             10:��ʾ�ж�����Ϊ384chip��
             
   UNION�ṹ:  CBBP_TIMING_INT4_1X_PERIOD_UNION */
#define CBBP_TIMING_INT4_1X_PERIOD_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x1070)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��ʱ�ж�int��ʹ�ܡ�
             0����ʾ������int�жϣ�
             1����ʾ����int�жϣ�
             
   UNION�ṹ:  CBBP_TIMING_INT4_1X_EN_UNION */
#define CBBP_TIMING_INT4_1X_EN_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x1074)

/* �Ĵ���˵����
 bit[31:22]  ����
 bit[21:16]  
 bit[15:11]  ����
 bit[10:0]   Int��sys_cnt_1x�ϵ�λ�ã�
             [21:16]��sys_cnt_1x_80ms��ֵ��
             [10:0]��sys_cnt_1x_1p25ms[15:5]��ֵ,chip���ȣ�
             
   UNION�ṹ:  CBBP_TIMING_INT5_SYS_CNT_1X_POS_UNION */
#define CBBP_TIMING_INT5_SYS_CNT_1X_POS_ADDR          (SOC_BBP_CDMA_BASE_ADDR + 0x1078)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    Int�ж�����ѡ��
             0����ʾ�ж�����Ϊ64chip��
             1����ʾ�ж�����Ϊ128chip��
             2����ʾ�ж�����Ϊ256chip��
             3����ʾ�ж�����Ϊ512chip��
             4����ʾ�ж�����Ϊ1.25ms��
             5����ʾ�ж�����Ϊ5ms��
             6����ʾ�ж�����Ϊ10ms��
             7����ʾ�ж�����Ϊ20ms��
             8����ʾ�ж�����Ϊ40ms��
             9����ʾ�ж�����Ϊ80ms��
             10:��ʾ�ж�����Ϊ384chip��
             
   UNION�ṹ:  CBBP_TIMING_INT5_1X_PERIOD_UNION */
#define CBBP_TIMING_INT5_1X_PERIOD_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x107C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��ʱ�ж�int��ʹ�ܡ�
             0����ʾ������int�жϣ�
             1����ʾ����int�жϣ�
             
   UNION�ṹ:  CBBP_TIMING_INT5_1X_EN_UNION */
#define CBBP_TIMING_INT5_1X_EN_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x1080)

/* �Ĵ���˵����
 bit[31:22]  ����
 bit[21:16]  
 bit[15:11]  ����
 bit[10:0]   Int��sys_cnt_1x�ϵ�λ�ã�
             [21:16]��sys_cnt_1x_80ms��ֵ��
             [10:0]��sys_cnt_1x_1p25ms[15:5]��ֵ,chip���ȣ�
             
   UNION�ṹ:  CBBP_TIMING_INT6_SYS_CNT_1X_POS_UNION */
#define CBBP_TIMING_INT6_SYS_CNT_1X_POS_ADDR          (SOC_BBP_CDMA_BASE_ADDR + 0x1084)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    Int�ж�����ѡ��
             0����ʾ�ж�����Ϊ64chip��
             1����ʾ�ж�����Ϊ128chip��
             2����ʾ�ж�����Ϊ256chip��
             3����ʾ�ж�����Ϊ512chip��
             4����ʾ�ж�����Ϊ1.25ms��
             5����ʾ�ж�����Ϊ5ms��
             6����ʾ�ж�����Ϊ10ms��
             7����ʾ�ж�����Ϊ20ms��
             8����ʾ�ж�����Ϊ40ms��
             9����ʾ�ж�����Ϊ80ms��
             10:��ʾ�ж�����Ϊ384chip��
             
   UNION�ṹ:  CBBP_TIMING_INT6_1X_PERIOD_UNION */
#define CBBP_TIMING_INT6_1X_PERIOD_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x1088)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��ʱ�ж�int��ʹ�ܡ�
             0����ʾ������int�жϣ�
             1����ʾ����int�жϣ�
             
   UNION�ṹ:  CBBP_TIMING_INT6_1X_EN_UNION */
#define CBBP_TIMING_INT6_1X_EN_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x108C)

/* �Ĵ���˵����
 bit[31:6]   ����
 bit[5:0]    ��������ϱ��ж�ʱ��sys_cnt_1xֵ��mask��
             bit0��Ϊ1��ʾ�ϱ��ж�1ʱ�̵Ķ�ʱ��
             bit1��Ϊ1��ʾ�ϱ��ж�2ʱ�̵Ķ�ʱ��
             ��
             ע�⣺ͬһʱ��ֻ����1bitΪ1
   UNION�ṹ:  CBBP_SYS_CNT_1X_RPT_INT1_MASK_UNION */
#define CBBP_SYS_CNT_1X_RPT_INT1_MASK_ADDR            (SOC_BBP_CDMA_BASE_ADDR + 0x1090)

/* �Ĵ���˵����
 bit[31:22]  ����
 bit[21:16]  
 bit[15:5]   ����
 bit[4:0]    ������õĵ�һ���ϱ���ʱ��Ϣ���ж�ʱ�̵�sys_cnt_1x��ֵ��
             
             [21:16]��sys_cnt_1x_80ms��ֵ��
             [4:0]��sys_cnt_1x_1p25ms��ֵ,64chip���ȣ�
             
   UNION�ṹ:  CBBP_SYS_CNT_1X_RPT_INT1_UNION */
#define CBBP_SYS_CNT_1X_RPT_INT1_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x1094)

/* �Ĵ���˵����
 bit[31:6]   ����
 bit[5:0]    ��������ϱ��ж�ʱ��sys_cnt_1xֵ��mask��
             bit0��Ϊ1��ʾ�ϱ��ж�1ʱ�̵Ķ�ʱ��
             bit1��Ϊ1��ʾ�ϱ��ж�2ʱ�̵Ķ�ʱ��
             ��
             ע�⣺ͬһʱ��ֻ����1bitΪ1
   UNION�ṹ:  CBBP_SYS_CNT_1X_RPT_INT2_MASK_UNION */
#define CBBP_SYS_CNT_1X_RPT_INT2_MASK_ADDR            (SOC_BBP_CDMA_BASE_ADDR + 0x1098)

/* �Ĵ���˵����
 bit[31:22]  ����
 bit[21:16]  
 bit[15:5]   ����
 bit[4:0]    ������õĵ�2���ϱ���ʱ��Ϣ���ж�ʱ�̵�sys_cnt_1x��ֵ��
             
             [21:16]��sys_cnt_1x_80ms��ֵ��
             [4:0]��sys_cnt_1x_1p25ms��ֵ,64chip���ȣ�
             
   UNION�ṹ:  CBBP_SYS_CNT_1X_RPT_INT2_UNION */
#define CBBP_SYS_CNT_1X_RPT_INT2_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x109C)

/* �Ĵ���˵����
 bit[31:6]   ����
 bit[5:0]    ��������ϱ��ж�ʱ��sys_cnt_1xֵ��mask��
             bit0��Ϊ1��ʾ�ϱ��ж�1ʱ�̵Ķ�ʱ��
             bit1��Ϊ1��ʾ�ϱ��ж�2ʱ�̵Ķ�ʱ��
             ��
             ע�⣺ͬһʱ��ֻ����1bitΪ1
   UNION�ṹ:  CBBP_SYS_CNT_1X_RPT_INT3_MASK_UNION */
#define CBBP_SYS_CNT_1X_RPT_INT3_MASK_ADDR            (SOC_BBP_CDMA_BASE_ADDR + 0x10A0)

/* �Ĵ���˵����
 bit[31:22]  ����
 bit[21:16]  
 bit[15:5]   ����
 bit[4:0]    ������õĵ�3���ϱ���ʱ��Ϣ���ж�ʱ�̵�sys_cnt_1x��ֵ��
             
             [21:16]��sys_cnt_1x_80ms��ֵ��
             [4:0]��sys_cnt_1x_1p25ms��ֵ,64chip���ȣ�
             
   UNION�ṹ:  CBBP_SYS_CNT_1X_RPT_INT3_UNION */
#define CBBP_SYS_CNT_1X_RPT_INT3_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x10A4)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      1xϵͳ������sys_cnt_1x������
             0��ʾ����Ϊ2s��
             1��ʾ����Ϊ5.12s
   UNION�ṹ:  CBBP_SYS_CNT_1X_PERIOD_UNION */
#define CBBP_SYS_CNT_1X_PERIOD_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x10A8)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:24]  
 bit[23:22]  ����
 bit[21:16]  
 bit[15:11]  ����
 bit[10:0]   sys_cnt_1x��ֵ��
             [29:24]��sys_cnt_1x_5p12s��ֵ��
             [21:16]��sys_cnt_1x_80ms��ֵ��
             [10:0]��sys_cnt_1x_1p25ms��ֵ,chip���ȣ�
             
             ���ֱ�Ӷ�ȡ��BBPδ�����洦�����������ȡ2~3�Σ�ȷ�϶�ȡ���ȶ��Ľ����ʹ��
             
   UNION�ṹ:  CBBP_SYS_CNT_1X_RPT2_UNION */
#define CBBP_SYS_CNT_1X_RPT2_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x10B8)

/* �Ĵ���˵����
   ��      ����sys_cnt_1x��λ�ϱ��������SYS_CNT_1X_RPTһ���ϱ���
            ���ֱ�Ӷ�ȡ��BBPδ�����洦��
   UNION�ṹ ���� */
#define CBBP_SYS_CNT_1X_HIGH_RPT2_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x10BC)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��ǰϵͳ���Ƿ����1x��ʱ��
             1����ʾ����1x��ʱ��
             
   UNION�ṹ:  CBBP_C_TIMING_MODE_1X_UNION */
#define CBBP_C_TIMING_MODE_1X_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x10C0)

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
#define CBBP_SLEEP_TIME_1X_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0x10C8)

/* �Ĵ���˵����
 bit[31:5]   ����
 bit[4:0]    ����ʱ��ʹ�ô��пڴ��䶨ʱ��Ϣ��ʱ�䣬��λchip
   UNION�ṹ:  CBBP_SSI_TRANS_COMP_1X_UNION */
#define CBBP_SSI_TRANS_COMP_1X_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x10D0)

/* �Ĵ���˵����
 bit[31:29]  ����
 bit[28:24]  
 bit[23:22]  
 bit[21:5]   
 bit[4:0]    ����sys_cnt_evdo��ʱ�̣�
             [28:24]��base_cnt_2s�ϵ�ʱ�̣���ȡֵ��Χ0~24��
             [23:22]��base_cnt_80ms�ϵ�ʱ�̣�ȡֵ��Χ0~2��
             [21:5]��base_cnt_26ms�ϵ�ʱ�̣�ȡֵ��Χ0~32768*32-1��
             [4:0],1/4chip�ڼ�����ȡֵ��Χ0~24
             
   UNION�ṹ:  CBBP_SYS_CNT_EVDO_GET_POS_UNION */
#define CBBP_SYS_CNT_EVDO_GET_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x1100)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:24]  
 bit[23:22]  
 bit[21:5]   
 bit[4:0]    sys_cnt_evdo_get_posʱ��sys_cnt_evdo��ֵ��
             [28:24]��sys_cnt_evdo_5p12s��ֵ��
             [31:22]��sys_cnt_evdo_80ms��ֵ��
             [21:5]��sys_cnt_evdo_26ms��ֵ��
             [4:0]��1/4chip�ڼ�����0~24
             
   UNION�ṹ:  CBBP_SYS_CNT_EVDO_GET_VALUE_UNION */
#define CBBP_SYS_CNT_EVDO_GET_VALUE_ADDR              (SOC_BBP_CDMA_BASE_ADDR + 0x1104)

/* �Ĵ���˵����
   ��      ����sys_cnt_get_posʱ��sys_cnt_evdo��ֵ����λ5.12s��2s
   UNION�ṹ ���� */
#define CBBP_SYS_CNT_EVDO_GET_VALUE_HIGH_ADDR         (SOC_BBP_CDMA_BASE_ADDR + 0x1180)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:22]  
 bit[21:5]   
 bit[4:0]    ��ʱͻ���sys_cnt_evdo  80ms֡ͷ��base_cnt�ϵ�λ�á�
             Bit[4:0]��1/4chip�ڼ���0~24
             bit[21:5]��26ms�ڼ���0~32768*4-1
             bit[23:22]��80ms�ڼ���0~2
   UNION�ṹ:  CBBP_SYS_CNT_EVDO_80MS_POS_CFG_UNION */
#define CBBP_SYS_CNT_EVDO_80MS_POS_CFG_ADDR           (SOC_BBP_CDMA_BASE_ADDR + 0x1224)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      Sys_cnt_evdo��ʱ��ȡָʾ��
             BBP���յ���ָʾ�󣬵ȴ�base_cnt��sys_cnt_evdo_get_posʱ�̣���sys_cnt_evdo����Ϊsys_cnt_evdo_get_value��
             
   UNION�ṹ:  CBBP_SYS_CNT_EVDO_GET_RDY_UNION */
#define CBBP_SYS_CNT_EVDO_GET_RDY_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x1108)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ϵͳ��ʱ��������
             0����ʾ����ߵ���6clk��
             1����ʾ���ұߵ���6clk��
             ˵������ʱ����100��ʱ�ӣ���ˣ�6clkʱ��Ϊ6/100chip
             
   UNION�ṹ:  CBBP_SYS_EVDO_CHANGE_DIRECTION_UNION */
#define CBBP_SYS_EVDO_CHANGE_DIRECTION_ADDR           (SOC_BBP_CDMA_BASE_ADDR + 0x110C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ϵͳ��ʱ����ָʾ��
             BBP�ڽ��յ���ָʾ���������ʱ϶ͷ���ϵͳ��ʱ������
             
   UNION�ṹ:  CBBP_SYS_EVDO_CHANGE_RDY_UNION */
#define CBBP_SYS_EVDO_CHANGE_RDY_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x1110)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      �����ȡsys_cnt_evdo_80ms_pos��ָʾ
   UNION�ṹ:  CBBP_SYS_CNT_EVDO_80MS_POS_RD_UNION */
#define CBBP_SYS_CNT_EVDO_80MS_POS_RD_ADDR            (SOC_BBP_CDMA_BASE_ADDR + 0x1114)

/* �Ĵ���˵����
 bit[31]     ��ȡsys_cnt_evdo_80ms_pos��Чָʾ��1��Ч
 bit[30:24]  ����
 bit[23:22]  
 bit[21:5]   
 bit[4:0]    sys_cnt_evdo  80ms֡ͷ��base_cnt�ϵ�λ�á�
             Bit[4:0]��1/4chip�ڼ���0~24
             bit[21:5]��26ms�ڼ���0~32768*4-1
             bit[23:22]��80ms�ڼ���0~2
   UNION�ṹ:  CBBP_SYS_CNT_EVDO_80MS_POS_UNION */
#define CBBP_SYS_CNT_EVDO_80MS_POS_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x1118)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      sys_cnt_evdo_80ms_pos_valid�����ź�
   UNION�ṹ:  CBBP_SYS_CNT_EVDO_80MS_POS_VALID_CLR_UNION */
#define CBBP_SYS_CNT_EVDO_80MS_POS_VALID_CLR_ADDR     (SOC_BBP_CDMA_BASE_ADDR + 0x111C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��ʱͻ��ʱ����ʱ�жϵ�mask��
             0����ʾ��mask��
             1����ʾmask���÷�Χ�ڵ��жϣ�
             
   UNION�ṹ:  CBBP_TIMING_INT_EVDO_MASK_UNION */
#define CBBP_TIMING_INT_EVDO_MASK_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x1120)

/* �Ĵ���˵����
 bit[31:11]  ����
 bit[10:0]   ��ʱͻ��ʱ����ʱ�жϵ�mask���䣬chipΪ��λ��
   UNION�ṹ:  CBBP_TIMING_INT_EVDO_MASK_DIS_UNION */
#define CBBP_TIMING_INT_EVDO_MASK_DIS_ADDR            (SOC_BBP_CDMA_BASE_ADDR + 0x1124)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  
 bit[15]     ����
 bit[14:0]   Int��sys_cnt_evdo�ϵ�λ�ã�
             [17:16]��sys_cnt_evdo_80ms��ֵ��
             [14:0]��sys_cnt_evdo_26ms��ֵ��chip���ȣ�
             
   UNION�ṹ:  CBBP_TIMING_INT1_SYS_CNT_EVDO_POS_UNION */
#define CBBP_TIMING_INT1_SYS_CNT_EVDO_POS_ADDR        (SOC_BBP_CDMA_BASE_ADDR + 0x1128)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    Int�ж�����ѡ��
             0����ʾ�ж�����Ϊ64chip��
             1����ʾ�ж�����Ϊ128chip��
             2����ʾ�ж�����Ϊ256chip��
             3����ʾ�ж�����Ϊ512chip��
             4����ʾ�ж�����Ϊ1024chip��
             5����ʾ�ж�����Ϊ2048chip��
             6����ʾ�ж�����Ϊ4096chip��
             7����ʾ�ж�����Ϊ8192chip��
             8����ʾ�ж�����Ϊ16384chip��
             9����ʾ�ж�����Ϊ32768chip��
             10����ʾ�ж�����Ϊ80ms��
             
   UNION�ṹ:  CBBP_TIMING_INT1_EVDO_PERIOD_UNION */
#define CBBP_TIMING_INT1_EVDO_PERIOD_ADDR             (SOC_BBP_CDMA_BASE_ADDR + 0x112C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��ʱ�ж�int��ʹ�ܡ�
             0����ʾ������int�жϣ�
             1����ʾ����int�жϣ�
             
   UNION�ṹ:  CBBP_TIMING_INT1_EVDO_EN_UNION */
#define CBBP_TIMING_INT1_EVDO_EN_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x1130)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  
 bit[15]     ����
 bit[14:0]   Int��sys_cnt_evdo�ϵ�λ�ã�
             [17:16]��sys_cnt_evdo_80ms��ֵ��
             [14:0]��sys_cnt_evdo_26ms��ֵ��chip���ȣ�
             
   UNION�ṹ:  CBBP_TIMING_INT2_SYS_CNT_EVDO_POS_UNION */
#define CBBP_TIMING_INT2_SYS_CNT_EVDO_POS_ADDR        (SOC_BBP_CDMA_BASE_ADDR + 0x1134)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    Int�ж�����ѡ��
             0����ʾ�ж�����Ϊ64chip��
             1����ʾ�ж�����Ϊ128chip��
             2����ʾ�ж�����Ϊ256chip��
             3����ʾ�ж�����Ϊ512chip��
             4����ʾ�ж�����Ϊ1024chip��
             5����ʾ�ж�����Ϊ2048chip��
             6����ʾ�ж�����Ϊ4096chip��
             7����ʾ�ж�����Ϊ8192chip��
             8����ʾ�ж�����Ϊ16384chip��
             9����ʾ�ж�����Ϊ32768chip��
             10����ʾ�ж�����Ϊ80ms��
             
   UNION�ṹ:  CBBP_TIMING_INT2_EVDO_PERIOD_UNION */
#define CBBP_TIMING_INT2_EVDO_PERIOD_ADDR             (SOC_BBP_CDMA_BASE_ADDR + 0x1138)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��ʱ�ж�int��ʹ�ܡ�
             0����ʾ������int�жϣ�
             1����ʾ����int�жϣ�
             
   UNION�ṹ:  CBBP_TIMING_INT2_EVDO_EN_UNION */
#define CBBP_TIMING_INT2_EVDO_EN_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x113C)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  
 bit[15]     ����
 bit[14:0]   Int��sys_cnt_evdo�ϵ�λ�ã�
             [17:16]��sys_cnt_evdo_80ms��ֵ��
             [14:0]��sys_cnt_evdo_26ms��ֵ��chip���ȣ�
             
   UNION�ṹ:  CBBP_TIMING_INT3_SYS_CNT_EVDO_POS_UNION */
#define CBBP_TIMING_INT3_SYS_CNT_EVDO_POS_ADDR        (SOC_BBP_CDMA_BASE_ADDR + 0x1140)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    Int�ж�����ѡ��
             0����ʾ�ж�����Ϊ64chip��
             1����ʾ�ж�����Ϊ128chip��
             2����ʾ�ж�����Ϊ256chip��
             3����ʾ�ж�����Ϊ512chip��
             4����ʾ�ж�����Ϊ1024chip��
             5����ʾ�ж�����Ϊ2048chip��
             6����ʾ�ж�����Ϊ4096chip��
             7����ʾ�ж�����Ϊ8192chip��
             8����ʾ�ж�����Ϊ16384chip��
             9����ʾ�ж�����Ϊ32768chip��
             10����ʾ�ж�����Ϊ80ms��
             
   UNION�ṹ:  CBBP_TIMING_INT3_EVDO_PERIOD_UNION */
#define CBBP_TIMING_INT3_EVDO_PERIOD_ADDR             (SOC_BBP_CDMA_BASE_ADDR + 0x1144)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��ʱ�ж�int��ʹ�ܡ�
             0����ʾ������int�жϣ�
             1����ʾ����int�жϣ�
             
   UNION�ṹ:  CBBP_TIMING_INT3_EVDO_EN_UNION */
#define CBBP_TIMING_INT3_EVDO_EN_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x1148)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  
 bit[15]     ����
 bit[14:0]   Int��sys_cnt_evdo�ϵ�λ�ã�
             [17:16]��sys_cnt_evdo_80ms��ֵ��
             [14:0]��sys_cnt_evdo_26ms��ֵ��chip���ȣ�
             
   UNION�ṹ:  CBBP_TIMING_INT4_SYS_CNT_EVDO_POS_UNION */
#define CBBP_TIMING_INT4_SYS_CNT_EVDO_POS_ADDR        (SOC_BBP_CDMA_BASE_ADDR + 0x114C)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    Int�ж�����ѡ��
             0����ʾ�ж�����Ϊ64chip��
             1����ʾ�ж�����Ϊ128chip��
             2����ʾ�ж�����Ϊ256chip��
             3����ʾ�ж�����Ϊ512chip��
             4����ʾ�ж�����Ϊ1024chip��
             5����ʾ�ж�����Ϊ2048chip��
             6����ʾ�ж�����Ϊ4096chip��
             7����ʾ�ж�����Ϊ8192chip��
             8����ʾ�ж�����Ϊ16384chip��
             9����ʾ�ж�����Ϊ32768chip��
             10����ʾ�ж�����Ϊ80ms��
             
   UNION�ṹ:  CBBP_TIMING_INT4_EVDO_PERIOD_UNION */
#define CBBP_TIMING_INT4_EVDO_PERIOD_ADDR             (SOC_BBP_CDMA_BASE_ADDR + 0x1150)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��ʱ�ж�int��ʹ�ܡ�
             0����ʾ������int�жϣ�
             1����ʾ����int�жϣ�
             
   UNION�ṹ:  CBBP_TIMING_INT4_EVDO_EN_UNION */
#define CBBP_TIMING_INT4_EVDO_EN_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x1154)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  
 bit[15]     ����
 bit[14:0]   Int��sys_cnt_evdo�ϵ�λ�ã�
             [17:16]��sys_cnt_evdo_80ms��ֵ��
             [14:0]��sys_cnt_evdo_26ms��ֵ��chip���ȣ�
             
   UNION�ṹ:  CBBP_TIMING_INT5_SYS_CNT_EVDO_POS_UNION */
#define CBBP_TIMING_INT5_SYS_CNT_EVDO_POS_ADDR        (SOC_BBP_CDMA_BASE_ADDR + 0x1158)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    Int�ж�����ѡ��
             0����ʾ�ж�����Ϊ64chip��
             1����ʾ�ж�����Ϊ128chip��
             2����ʾ�ж�����Ϊ256chip��
             3����ʾ�ж�����Ϊ512chip��
             4����ʾ�ж�����Ϊ1024chip��
             5����ʾ�ж�����Ϊ2048chip��
             6����ʾ�ж�����Ϊ4096chip��
             7����ʾ�ж�����Ϊ8192chip��
             8����ʾ�ж�����Ϊ16384chip��
             9����ʾ�ж�����Ϊ32768chip��
             10����ʾ�ж�����Ϊ80ms��
             
   UNION�ṹ:  CBBP_TIMING_INT5_EVDO_PERIOD_UNION */
#define CBBP_TIMING_INT5_EVDO_PERIOD_ADDR             (SOC_BBP_CDMA_BASE_ADDR + 0x115C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��ʱ�ж�int��ʹ�ܡ�
             0����ʾ������int�жϣ�
             1����ʾ����int�жϣ�
             
   UNION�ṹ:  CBBP_TIMING_INT5_EVDO_EN_UNION */
#define CBBP_TIMING_INT5_EVDO_EN_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x1160)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  
 bit[15]     ����
 bit[14:0]   Int��sys_cnt_evdo�ϵ�λ�ã�
             [17:16]��sys_cnt_evdo_80ms��ֵ��
             [14:0]��sys_cnt_evdo_26ms��ֵ��chip���ȣ�
             
   UNION�ṹ:  CBBP_TIMING_INT6_SYS_CNT_EVDO_POS_UNION */
#define CBBP_TIMING_INT6_SYS_CNT_EVDO_POS_ADDR        (SOC_BBP_CDMA_BASE_ADDR + 0x1164)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    Int�ж�����ѡ��
             0����ʾ�ж�����Ϊ64chip��
             1����ʾ�ж�����Ϊ128chip��
             2����ʾ�ж�����Ϊ256chip��
             3����ʾ�ж�����Ϊ512chip��
             4����ʾ�ж�����Ϊ1024chip��
             5����ʾ�ж�����Ϊ2048chip��
             6����ʾ�ж�����Ϊ4096chip��
             7����ʾ�ж�����Ϊ8192chip��
             8����ʾ�ж�����Ϊ16384chip��
             9����ʾ�ж�����Ϊ32768chip��
             10����ʾ�ж�����Ϊ80ms��
             
   UNION�ṹ:  CBBP_TIMING_INT6_EVDO_PERIOD_UNION */
#define CBBP_TIMING_INT6_EVDO_PERIOD_ADDR             (SOC_BBP_CDMA_BASE_ADDR + 0x1168)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��ʱ�ж�int��ʹ�ܡ�
             0����ʾ������int�жϣ�
             1����ʾ����int�жϣ�
             
   UNION�ṹ:  CBBP_TIMING_INT6_EVDO_EN_UNION */
#define CBBP_TIMING_INT6_EVDO_EN_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x116C)

/* �Ĵ���˵����
 bit[31:6]   ����
 bit[5:0]    ��������ϱ��ж�ʱ��sys_cnt_evdoֵ��mask��
             bit0��Ϊ1��ʾ�ϱ��ж�1ʱ�̵Ķ�ʱ��
             bit1��Ϊ1��ʾ�ϱ��ж�2ʱ�̵Ķ�ʱ��
             ��
             ע�⣺ͬһʱ��ֻ����1bitΪ1
   UNION�ṹ:  CBBP_SYS_CNT_EVDO_RPT_INT1_MASK_UNION */
#define CBBP_SYS_CNT_EVDO_RPT_INT1_MASK_ADDR          (SOC_BBP_CDMA_BASE_ADDR + 0x1170)

/* �Ĵ���˵����
 bit[31:11]  ����
 bit[10:0]   ������õĵ�1���ϱ���ʱ��Ϣ���ж�ʱ�̵�sys_cnt_evdo��ֵ��
             
             [10:0]��sys_cnt_evdo��ֵ��64chip���ȣ�
             
             
   UNION�ṹ:  CBBP_SYS_CNT_EVDO_RPT_INT1_UNION */
#define CBBP_SYS_CNT_EVDO_RPT_INT1_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x1174)

/* �Ĵ���˵����
 bit[31:6]   ����
 bit[5:0]    ��������ϱ��ж�ʱ��sys_cnt_evdoֵ��mask��
             bit0��Ϊ1��ʾ�ϱ��ж�1ʱ�̵Ķ�ʱ��
             bit1��Ϊ1��ʾ�ϱ��ж�2ʱ�̵Ķ�ʱ��
             ��
             ע�⣺ͬһʱ��ֻ����1bitΪ1
   UNION�ṹ:  CBBP_SYS_CNT_EVDO_RPT_INT2_MASK_UNION */
#define CBBP_SYS_CNT_EVDO_RPT_INT2_MASK_ADDR          (SOC_BBP_CDMA_BASE_ADDR + 0x1178)

/* �Ĵ���˵����
 bit[31:11]  ����
 bit[10:0]   ������õĵ�1���ϱ���ʱ��Ϣ���ж�ʱ�̵�sys_cnt_evdo��ֵ��
             
             [10:0]��sys_cnt_evdo��ֵ��64chip���ȣ�
             
             
   UNION�ṹ:  CBBP_SYS_CNT_EVDO_RPT_INT2_UNION */
#define CBBP_SYS_CNT_EVDO_RPT_INT2_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x1184)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      1xϵͳ������sys_cnt_evdo������
             0��ʾ����Ϊ2s��
             1��ʾ����Ϊ5.12s
   UNION�ṹ:  CBBP_SYS_CNT_EVDO_PERIOD_UNION */
#define CBBP_SYS_CNT_EVDO_PERIOD_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x117C)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:24]  
 bit[23:18]  ����
 bit[17:16]  
 bit[15]     ����
 bit[14:0]   sys_cnt_evdo��ֵ��
             [29:24]��sys_cnt_evdo_5p12s��ֵ��
             [17:16]��sys_cnt_evdo_80ms��ֵ��
             [14:0]��sys_cnt_evdo_26ms��ֵ��chip���ȣ�
             
             ���ֱ�Ӷ�ȡBBP�����BBPδ�����洦�����������ȡ2~3�Σ�ȷ����ȡ���ȶ����
             
   UNION�ṹ:  CBBP_SYS_CNT_EVDO_RPT2_UNION */
#define CBBP_SYS_CNT_EVDO_RPT2_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x1188)

/* �Ĵ���˵����
   ��      ����sys_cnt_evdo��λ�ϱ��������SYS_CNT_EVDO_RPTһ���ϱ�
            
            ���������ȡ2~3�Σ�ȷ����ȡ���ȶ����
   UNION�ṹ ���� */
#define CBBP_SYS_CNT_EVDO_HIGH_RPT2_ADDR              (SOC_BBP_CDMA_BASE_ADDR + 0x118C)

/* �Ĵ���˵����
 bit[31:6]   ����
 bit[5:0]    ��������ϱ��ж�ʱ��sys_cnt_evdoֵ��mask��
             bit0��Ϊ1��ʾ�ϱ��ж�1ʱ�̵Ķ�ʱ��
             bit1��Ϊ1��ʾ�ϱ��ж�2ʱ�̵Ķ�ʱ��
             ��
             ע�⣺ͬһʱ��ֻ����1bitΪ1
   UNION�ṹ:  CBBP_SYS_CNT_EVDO_RPT_INT3_MASK_UNION */
#define CBBP_SYS_CNT_EVDO_RPT_INT3_MASK_ADDR          (SOC_BBP_CDMA_BASE_ADDR + 0x1190)

/* �Ĵ���˵����
 bit[31:11]  ����
 bit[10:0]   ������õĵ�1���ϱ���ʱ��Ϣ���ж�ʱ�̵�sys_cnt_evdo��ֵ��
             
             [10:0]��sys_cnt_evdo��ֵ��64chip���ȣ�
             
             
   UNION�ṹ:  CBBP_SYS_CNT_EVDO_RPT_INT3_UNION */
#define CBBP_SYS_CNT_EVDO_RPT_INT3_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x1194)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��ǰϵͳ���Ƿ����evdo��ʱ��
             1����ʾ����evdo��ʱ��
             
   UNION�ṹ:  CBBP_C_TIMING_MODE_EVDO_UNION */
#define CBBP_C_TIMING_MODE_EVDO_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x1198)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      C DBGģ�鶨ʱѡ��0��ʾѡ��1x��ʱ��1��ʾѡ��evdo��ʱ
   UNION�ṹ:  CBBP_C_TIMING_SEL_DBG_UNION */
#define CBBP_C_TIMING_SEL_DBG_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x1200)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ���ͬʱ��ȡ1x��evdo��ʱ��ָʾ�ź�
   UNION�ṹ:  CBBP_SYS_CNT_BOTH_RD_UNION */
#define CBBP_SYS_CNT_BOTH_RD_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x1204)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ���ͬʱ��ȡ1x��evdo��ʱ����Ч�źţ�1��ʾ�ϱ��Ľ����Ч
   UNION�ṹ:  CBBP_SYS_CNT_BOTH_RD_VALID_UNION */
#define CBBP_SYS_CNT_BOTH_RD_VALID_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x1208)

/* �Ĵ���˵����
 bit[31:29]  ����
 bit[28:24]  
 bit[23:18]  ����
 bit[17:16]  
 bit[15]     ����
 bit[14:0]   base_cnt��ֵ��
             [28:24]��base_cnt_2s�ϵ�ʱ�̣���ȡֵ��Χ0~24��
             [17:16]��base_cnt_80ms�ϵ�ʱ�̣�ȡֵ��Χ0~2��
             [14:0]��base_cnt_26ms�ϵ�ʱ�̣�ȡֵ��Χ0~32767��chip���ȣ�
             
   UNION�ṹ:  CBBP_BASE_CNT_BOTH_RPT_UNION */
#define CBBP_BASE_CNT_BOTH_RPT_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x120C)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:24]  
 bit[23:22]  ����
 bit[21:16]  
 bit[15:11]  ����
 bit[10:0]   sys_cnt_1x��ֵ��
             [29:24]��sys_cnt_1x_5p12s��ֵ��
             [21:16]��sys_cnt_1x_80ms��ֵ��
             [10:0]��sys_cnt_1x_1p25ms��ֵ,chip���ȣ�
   UNION�ṹ:  CBBP_SYS_CNT_1X_BOTH_RPT_UNION */
#define CBBP_SYS_CNT_1X_BOTH_RPT_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x1210)

/* �Ĵ���˵����
   ��      ����sys_cnt_1x��λ�ϱ��������SYS_CNT_1X_BOTH_RPTһ���ϱ�
   UNION�ṹ ���� */
#define CBBP_SYS_CNT_1X_HIGH_BOTH_RPT_ADDR            (SOC_BBP_CDMA_BASE_ADDR + 0x1214)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:24]  
 bit[23:18]  ����
 bit[17:16]  
 bit[15]     ����
 bit[14:0]   sys_cnt_evdo��ֵ��
             [29:24]��sys_cnt_evdo_5p12s��ֵ��
             [17:16]��sys_cnt_evdo_80ms��ֵ��
             [14:0]��sys_cnt_evdo_26ms��ֵ��chip���ȣ�
   UNION�ṹ:  CBBP_SYS_CNT_EVDO_BOTH_RPT_UNION */
#define CBBP_SYS_CNT_EVDO_BOTH_RPT_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x1218)

/* �Ĵ���˵����
   ��      ����sys_cnt_evdo��λ�ϱ��������SYS_CNT_EVDO_BOTH_RPTһ���ϱ�
            
   UNION�ṹ ���� */
#define CBBP_SYS_CNT_EVDO_HIGH_BOTH_RPT_ADDR          (SOC_BBP_CDMA_BASE_ADDR + 0x121C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ���ͬʱ��ȡ1x��evdo��ʱ����Чָʾ�źŵ������ź�
   UNION�ṹ:  CBBP_SYS_CNT_BOTH_RD_CLR_UNION */
#define CBBP_SYS_CNT_BOTH_RD_CLR_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x1220)

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
#define CBBP_SLEEP_TIME_EVDO_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x1228)

/* �Ĵ���˵����
 bit[31:5]   ����
 bit[4:0]    ����ʱ��ʹ�ô��пڴ��䶨ʱ��Ϣ��ʱ�䣬��λchip
   UNION�ṹ:  CBBP_SSI_TRANS_COMP_EVDO_UNION */
#define CBBP_SSI_TRANS_COMP_EVDO_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x122C)



/***======================================================================***
                     (3/20) register_define_c_intr
 ***======================================================================***/
/* �Ĵ���˵����
   ��      ������ʱ�ж�״̬�Ĵ�����1����ʾ��Ӧ����λ�����жϣ�0����ʾ��Ӧ����λ��û���жϡ�
            bit[0] CDMA 1X ���䶨ʱ�жϣ���������ÿ��ʱ϶����һ�Σ�DSP���ݴ��ж������¸�ʱ϶��RFIC SSI��MIPI�ȿ����֣���   
            bit[1] CDMA 1X���䶨ʱ�ж�2��       
            bit[2] CDMA 1X���䶨ʱ�ж�3��       
            bit[3] CDMA 1X���䶨ʱ�ж�4��       
            bit[4] CDMA 1X���䶨ʱ�ж�5��
            bit[5] CDMA 1X���䶨ʱ�ж�6��
            bit[6] Reserve for timing
            bit[7] Reserve for timing
            bit[8] Reserve for timing
            bit[9] Reserve for timing
            bit[10] Reserve for timing
            bit[11] Reserve for timing
            bit[12] Reserve for timing
            bit[13] Reserve for timing
            bit[14] Reserve for timing
            bit[15] Reserve for timing
            bit[16] CDMA EVDO���䶨ʱ�ж�16����������ÿ��ʱ϶����һ�Σ�DSP���ݴ��ж������¸�ʱ϶��RFIC SSI��MIPI�ȿ����֣���
            bit[17] CDMA EVDO���䶨ʱ�ж�17��
            bit[18] CDMA EVDO���䶨ʱ�ж�18��
            bit[19] CDMA EVDO���䶨ʱ�ж�19��
            bit[20] CDMA EVDO���䶨ʱ�ж�20��
            bit[21] CDMA EVDO���䶨ʱ�ж�21��
            bit[22] Reserve for timing
            bit[23] Reserve for timing
            bit[24] Reserve for timing
            bit[25] Reserve for timing
            bit[26] Reserve for timing
            bit[27] Reserve for timing
            bit[28] Reserve for timing
            bit[29] Reserve for timing
            bit[30] Reserve for timing
            bit[31] ʱ�Ӳ����ж�
   UNION�ṹ ���� */
#define CBBP_ARM_INT04_STA_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0x1800)

/* �Ĵ���˵����
   ��      �����ϱ���ARM�Ķ�ʱ�ж����μĴ�����1����ʾ������Ӧ����λ�õ��жϣ�0����ʾ��������Ӧ����λ�õ��жϡ�
   UNION�ṹ ���� */
#define CBBP_ARM_INT04_MASK_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x1804)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      �ж�04ʹ�ܼĴ�����1����ʾʹ���жϣ�0����ʾ��ʹ���жϡ�
   UNION�ṹ:  CBBP_ARM_INT04_EN_UNION */
#define CBBP_ARM_INT04_EN_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0x1808)

/* �Ĵ���˵����
   ��      ������ʱ�ж�����Ĵ�����1����ʾ�����Ӧ����λ���жϣ�0����ʾ�������Ӧ����λ�õ��жϡ�
   UNION�ṹ ���� */
#define CBBP_ARM_INT04_CLR_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0x180C)

/* �Ĵ���˵����
 bit[31:8]   ����
 bit[7]      ARM_INT04��ʱʹ�ܣ��ߵ�ƽ��Ч��
 bit[6:0]    ARM_INT04��ʱʱ�䡣
             ��ʱʱ�䵥λȡ����OVERTIME_BASE�����Ӧ��������OVERTIME_BASE
   UNION�ṹ:  CBBP_ARM_OVERTIME_CFG_UNION */
#define CBBP_ARM_OVERTIME_CFG_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x1810)

/* �Ĵ���˵����
 bit[31:16]  ����
 bit[15:0]   ���ж�©����ӳ�ʱ�䣬��λIMIʱ�ӡ�0����ֹ���ã�1����ʾ�ӳ�һ��IMIʱ�ӣ���������������Ϊ��0ֵ��
   UNION�ṹ:  CBBP_INT_DELAY_CLK_UNION */
#define CBBP_INT_DELAY_CLK_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0x1818)

/* �Ĵ���˵����
 bit[31:16]  ����
 bit[15:0]   arm_int04�жϳ�ʱ������
   UNION�ṹ:  CBBP_ARM_INT4_OT_NUM_UNION */
#define CBBP_ARM_INT4_OT_NUM_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x181C)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:0]   1ms��IMIʱ�Ӹ�����������ݵ�ǰIMIʱ��Ƶ�����ã�Ĭ��ֵΪIMIʱ��Ƶ��Ϊ200MHzʱ��1ms��ʱ�Ӹ�����
   UNION�ṹ:  CBBP_OVERTIME_BASE_UNION */
#define CBBP_OVERTIME_BASE_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0x1820)

/* �Ĵ���˵����
 bit[31:7]   ����
 bit[6:0]    �ྶ����/С�������ж�״̬�Ĵ�����1����ʾ��Ӧ����λ�����жϣ�0����ʾ��Ӧ����λ��û���жϡ�
             bit[0] �ྶ����/С��������Ԫ0�жϣ��ϱ�����Ϊ768chip(1x)/1024chip(evdo)/4096(evdo)       
             bit[1] �ྶ����/С��������Ԫ1�жϣ��ϱ�����Ϊ768chip(1x)/1024chip(evdo)/4096(evdo)��       
             bit[2] �ྶ����/С��������Ԫ2�жϣ��ϱ�����Ϊ768chip(1x)/1024chip(evdo)/4096(evdo)��       
             bit[3] �ྶ����/С��������Ԫ3�жϣ��ϱ�����Ϊ768chip(1x)/1024chip(evdo)/4096(evdo)��       
             bit[4] С�������Ͷྶ�������ݴ洢�����жϣ�
             bit[5] С���Ͷྶ�����ϲ��ж�0
             bit[6] С���Ͷྶ�����ϲ��ж�1
             ����������жϺϲ����絥Ԫ0�͵�Ԫ1�ϲ��ϱ�����ֻ�ϱ��ϲ��жϣ��������ϱ���Ԫ0��1���жϡ�
   UNION�ṹ:  CBBP_BBE16_INT03_STA_UNION */
#define CBBP_BBE16_INT03_STA_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x1830)

/* �Ĵ���˵����
 bit[31:7]   ����
 bit[6:0]    �ྶ����/С�������ж����μĴ�����1����ʾ������Ӧ����λ�õ��жϣ�0����ʾ��������Ӧ����λ�õ��жϡ�
   UNION�ṹ:  CBBP_BBE16_INT03_MASK_UNION */
#define CBBP_BBE16_INT03_MASK_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x1834)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      �ж�ʹ�ܼĴ�����1����ʾʹ���жϣ�0����ʾ��ʹ���жϡ�
   UNION�ṹ:  CBBP_BBE16_INT03_EN_UNION */
#define CBBP_BBE16_INT03_EN_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x1838)

/* �Ĵ���˵����
 bit[31:7]   ����
 bit[6:0]    �ྶ����/С�������ж�����Ĵ�����1����ʾ�����Ӧ����λ���жϣ�0����ʾ�������Ӧ����λ�õ��жϡ�
   UNION�ṹ:  CBBP_BBE16_INT03_CLR_UNION */
#define CBBP_BBE16_INT03_CLR_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x183C)

/* �Ĵ���˵����
   ��      ������ʱ�ж�״̬�Ĵ�����1����ʾ��Ӧ����λ�����жϣ�0����ʾ��Ӧ����λ��û���жϡ�
            bit[0] CDMA 1X ���䶨ʱ�жϣ���������ÿ��ʱ϶����һ�Σ�DSP���ݴ��ж������¸�ʱ϶��RFIC SSI��MIPI�ȿ����֣���   
            bit[1] CDMA 1X���䶨ʱ�ж�2��       
            bit[2] CDMA 1X���䶨ʱ�ж�3��       
            bit[3] CDMA 1X���䶨ʱ�ж�4��       
            bit[4] CDMA 1X���䶨ʱ�ж�5��
            bit[5] CDMA 1X���䶨ʱ�ж�6��
            bit[6] Reserve for timing
            bit[7] Reserve for timing
            bit[8] Reserve for timing
            bit[9] Reserve for timing
            bit[10] Reserve for timing
            bit[11] Reserve for timing
            bit[12] Reserve for timing
            bit[13] Reserve for timing
            bit[14] Reserve for timing
            bit[15] Reserve for timing
            bit[16] CDMA EVDO���䶨ʱ�ж�16����������ÿ��ʱ϶����һ�Σ�DSP���ݴ��ж������¸�ʱ϶��RFIC SSI��MIPI�ȿ����֣���
            bit[17] CDMA EVDO���䶨ʱ�ж�17��
            bit[18] CDMA EVDO���䶨ʱ�ж�18��
            bit[19] CDMA EVDO���䶨ʱ�ж�19��
            bit[20] CDMA EVDO���䶨ʱ�ж�20��
            bit[21] CDMA EVDO���䶨ʱ�ж�21��
            bit[22] Reserve for timing
            bit[23] Reserve for timing
            bit[24] Reserve for timing
            bit[25] Reserve for timing
            bit[26] Reserve for timing
            bit[27] Reserve for timing
            bit[28] Reserve for timing
            bit[29] Reserve for timing
            bit[30] Reserve for timing
            bit[31] ʱ�Ӳ����ж�
   UNION�ṹ ���� */
#define CBBP_BBE16_INT04_STA_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x1840)

/* �Ĵ���˵����
   ��      ������ʱ�ж����μĴ�����1����ʾ������Ӧ����λ�õ��жϣ�0����ʾ��������Ӧ����λ�õ��жϡ�
   UNION�ṹ ���� */
#define CBBP_BBE16_INT04_MASK_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x1844)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      �ж�04ʹ�ܼĴ�����1����ʾʹ���жϣ�0����ʾ��ʹ���жϡ�
   UNION�ṹ:  CBBP_BBE16_INT04_EN_UNION */
#define CBBP_BBE16_INT04_EN_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x1848)

/* �Ĵ���˵����
   ��      ������ʱ�ж�����Ĵ�����1����ʾ�����Ӧ����λ���жϣ�0����ʾ�������Ӧ����λ�õ��жϡ�
   UNION�ṹ ���� */
#define CBBP_BBE16_INT04_CLR_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x184C)

/* �Ĵ���˵����
 bit[31:5]   ����
 bit[4:0]    ����/�����ж�״̬�Ĵ�����1����ʾ��Ӧ����λ�����жϣ�0����ʾ��Ӧ����λ��û���жϡ�
             bit[0]������������жϣ�
             bit[1] Reserve for timing       
             bit[2] Reserve for timing
             bit[3] Reserve for timing
             bit[4]�����ϱ��жϣ�֪ͨ�����ȡ�������ݣ� 
   UNION�ṹ:  CBBP_BBE16_INT05_STA_UNION */
#define CBBP_BBE16_INT05_STA_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x1850)

/* �Ĵ���˵����
 bit[31:5]   ����
 bit[4:0]    ����/�����ж����μĴ�����1����ʾ������Ӧ����λ�õ��жϣ�0����ʾ��������Ӧ����λ�õ��жϡ�
   UNION�ṹ:  CBBP_BBE16_INT05_MASK_UNION */
#define CBBP_BBE16_INT05_MASK_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x1854)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      �ж�ʹ�ܼĴ�����1����ʾʹ���жϣ�0����ʾ��ʹ���жϡ�
   UNION�ṹ:  CBBP_BBE16_INT05_EN_UNION */
#define CBBP_BBE16_INT05_EN_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x1858)

/* �Ĵ���˵����
 bit[31:5]   ����
 bit[4:0]    ����/�����ж�����Ĵ�����1����ʾ�����Ӧ����λ���жϣ�0����ʾ�������Ӧ����λ�õ��жϡ�
   UNION�ṹ:  CBBP_BBE16_INT05_CLR_UNION */
#define CBBP_BBE16_INT05_CLR_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x185C)

/* �Ĵ���˵����
 bit[31:5]   ����
 bit[4:0]    ��Ƶ�ϱ�/���ݰ����ж�״̬�Ĵ�����1����ʾ��Ӧ����λ�����жϣ�0����ʾ��Ӧ����λ��û���жϡ�
             bit[0]ÿ��ʱ϶����һ�Σ�DSP�յ����жϺ��ȡPD����ټ��㣻
             bit[1]��������1ǰ�����ݰ��˳����ϱ��жϣ�   
             bit[2]��������2ǰ�����ݰ��˳����ϱ��жϣ�     
             bit[3]����ǰ�����ݰ��˳����ϱ��жϣ� 
             bit[4]����ǰ������BBPMST��������жϡ�
   UNION�ṹ:  CBBP_BBE16_INT06_STA_UNION */
#define CBBP_BBE16_INT06_STA_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x1860)

/* �Ĵ���˵����
 bit[31:5]   ����
 bit[4:0]    ��Ƶ�ϱ�/���ݰ����ж����μĴ�����1����ʾ������Ӧ����λ�õ��жϣ�0����ʾ��������Ӧ����λ�õ��жϡ�
   UNION�ṹ:  CBBP_BBE16_INT06_MASK_UNION */
#define CBBP_BBE16_INT06_MASK_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x1864)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      �ж�ʹ�ܼĴ�����1����ʾʹ���жϣ�0����ʾ��ʹ���жϡ�
   UNION�ṹ:  CBBP_BBE16_INT06_EN_UNION */
#define CBBP_BBE16_INT06_EN_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x1868)

/* �Ĵ���˵����
 bit[31:5]   ����
 bit[4:0]    ��Ƶ�ϱ�/���ݰ����ж�����Ĵ�����1����ʾ�����Ӧ����λ���жϣ�0����ʾ�������Ӧ����λ�õ��жϡ�
   UNION�ṹ:  CBBP_BBE16_INT06_CLR_UNION */
#define CBBP_BBE16_INT06_CLR_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x186C)

/* �Ĵ���˵����
 bit[31]     BBE16_INT06��ʱʹ�ܣ��ߵ�ƽ��Ч��
 bit[30:24]  BBE16_INT06��ʱʱ�䡣
             ��ʱʱ�䵥λȡ����OVERTIME_BASE�����Ӧ��������OVERTIME_BASE
 bit[23]     bbe16_INT05��ʱʹ�ܣ��ߵ�ƽ��Ч��
 bit[22:16]  bbe16_INT05��ʱʱ�䡣
             ��ʱʱ�䵥λȡ����OVERTIME_BASE�����Ӧ��������OVERTIME_BASE
 bit[15]     bbe16_INT04��ʱʹ�ܣ��ߵ�ƽ��Ч��
 bit[14:8]   bbe16_INT04��ʱʱ�䡣
             ��ʱʱ�䵥λȡ����OVERTIME_BASE�����Ӧ��������OVERTIME_BASE
 bit[7]      bbe16_INT03��ʱʹ�ܣ��ߵ�ƽ��Ч��
 bit[6:0]    bbe16_INT03��ʱʱ�䡣
             ��ʱʱ�䵥λȡ����OVERTIME_BASE�����Ӧ��������OVERTIME_BASE
   UNION�ṹ:  CBBP_BBE16_OVERTIME_CFG_UNION */
#define CBBP_BBE16_OVERTIME_CFG_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x1870)

/* �Ĵ���˵����
 bit[31:5]   ����
 bit[4:0]    �жϳ�ʱָʾ���ߵ�ƽ��Ч��
             bit[0]��bbe16_INT03��
             bit[1]��bbe16_INT04��
             bit[2]��bbe16_INT05��
             bit[3]��bbe16_INT06��
             bit[4]��arm_INT04��
   UNION�ṹ:  CBBP_INT_OVERTIME_FLAG_UNION */
#define CBBP_INT_OVERTIME_FLAG_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x1874)

/* �Ĵ���˵����
 bit[31:16]  BBE16_int04�жϳ�ʱ������
 bit[15:0]   bbe16_int03�жϳ�ʱ������
   UNION�ṹ:  CBBP_BBE16_INT34_OT_NUM_UNION */
#define CBBP_BBE16_INT34_OT_NUM_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x1878)

/* �Ĵ���˵����
 bit[31:16]  BBE16_int06�жϳ�ʱ������
 bit[15:0]   bbe16_int05�жϳ�ʱ������
   UNION�ṹ:  CBBP_BBE16_INT56_OT_NUM_UNION */
#define CBBP_BBE16_INT56_OT_NUM_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x187C)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9:5]    С���Ͷྶ����Group1�жϺϲ��ϱ�ģʽ��[8:5]��ʾ��Ӧ��Ԫ3~0�жϣ�bit[9]��ʾ�洢��Ԫ�жϣ�
             ��Ӧbit����Ϊ1��ʾ��Ӧ��Ԫ�ж���Group1�ϲ��ϱ����ϲ��жϵ�����˵�������ӿ�˵����ġ��жϡ��½�
 bit[4:0]    С���Ͷྶ����Group0�жϺϲ��ϱ�ģʽ��[3:0]��ʾ��Ӧ��Ԫ3~0�жϣ�bit[4]��ʾ�洢��Ԫ�жϣ�
             ��Ӧbit����Ϊ1��ʾ��Ӧ��Ԫ�ж���Group1�ϲ��ϱ����ϲ��жϵ�����˵�������ӿ�˵����ġ��жϡ��½�
   UNION�ṹ:  CBBP_CS_MPS_GRP_INT_MODE_UNION */
#define CBBP_CS_MPS_GRP_INT_MODE_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x1880)



/***======================================================================***
                     (4/20) register_define_c_cs_mps_store
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31:13]  ����
 bit[12:0]   �洢���ݳ��ȣ�chip��λ��
             ����Ŀǰ�㷨��
             1xС������ʱ���洢����2048chip
             EvdoС������ʱ���洢����64x32=2048chip��64x16=1024chip��64x8=512chip
             1xС������ʱ��64x12����ɣ�x4������ɣ�=3072chip��
             EvdoС������ʱ��96x4����ɣ�x8������ɣ�=3072chip��
             
   UNION�ṹ:  CBBP_DATA_STORE_LENGTH_UNION */
#define CBBP_DATA_STORE_LENGTH_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x2F00)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    ���ݴ洢��ʽ��
             0��ʾ�����洢��
             1��ʾÿ1024chip����64chip��
             2��ʾÿ1024chip����96chip��
             3��ʾÿ1024chip����128chip��
             4��ʾÿ1024chip����256chip��
             5��ʾÿ1024chip����512chip��
             
   UNION�ṹ:  CBBP_DATA_STORE_MODE_UNION */
#define CBBP_DATA_STORE_MODE_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x2F04)

/* �Ĵ���˵����
 bit[31:16]  ����
 bit[15:0]   �洢���ݵ���ʼλ�ã���base_cnt[21:6]�ϵ�λ�ã�1/2chip����
   UNION�ṹ:  CBBP_DATA_STORE_POS_UNION */
#define CBBP_DATA_STORE_POS_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x2F08)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      �洢��������ѡ��
             Ϊ0��ʾ�洢��������1������
             Ϊ1��ʾ�洢��������2������
             
   UNION�ṹ:  CBBP_DATA_STORE_ANT_UNION */
#define CBBP_DATA_STORE_ANT_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x2F0C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      �洢������ʼλ��ѡ���źţ�
             0��ʾ���Ծͽ���ʼ�洢���ݣ�
             1��ʾ����ȵ� Data_store_pos�����ܿ�ʼ�洢���ݣ�
             
   UNION�ṹ:  CBBP_DATA_STORE_POS_SEL_UNION */
#define CBBP_DATA_STORE_POS_SEL_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x2F10)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      �Զ�ʱ���ſ�bypass��1��ʾʱ�ӳ���
   UNION�ṹ:  CBBP_DATA_STORE_CK_BYPASS_UNION */
#define CBBP_DATA_STORE_CK_BYPASS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2F14)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ���ݴ洢ģ��ʹ�ܣ���Ϊ��ģ�����ʹ�ܣ������Ʊ�ģ���ʱ�ӿ���
             �� Data_store_start֮ǰ����Ϊ1���ڽ��յ��жϺ�����Ϊ0
             
   UNION�ṹ:  CBBP_DATA_STORE_EN_UNION */
#define CBBP_DATA_STORE_EN_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0x2F18)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      �洢�������������ź�
   UNION�ṹ:  CBBP_DATA_STORE_START_UNION */
#define CBBP_DATA_STORE_START_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x2F1C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      FPGAר��
             ������ȡ�������ݵĿ�ʼ�źţ�BBP��⵽���źź󣬽���ȡ��ַ�ָ�����һ�����ݵ�λ��
   UNION�ṹ:  CBBP_DSP_RD_DATA_START_UNION */
#define CBBP_DSP_RD_DATA_START_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x2F20)

/* �Ĵ���˵����
   ��      ����FPGAר��
            ����������BBP��ȡ�Ļ�������
   UNION�ṹ ���� */
#define CBBP_DSP_RD_DATA_ADDR                         (SOC_BBP_CDMA_BASE_ADDR + 0x2F24)



/***======================================================================***
                     (5/20) register_define_c_cs_mps_unit0
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ������Ԫʱ��Ƶ��ѡ��
             0����ʾ������Ԫ128��ʱ�ӣ�
             1����ʾ������Ԫ64��ʱ��
             Ĭ�ϲ���Ҫ�������
             
   UNION�ṹ:  CBBP_UNIT0_CLK_MODE_UNION */
#define CBBP_UNIT0_CLK_MODE_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x2000)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    ʹ���������ݶྶ��������С��������ʱ�����ٸ�����ۼӽ���ϱ�һ�Ρ�
             �˽ӿ���Ҫ�ǽ��afcʧ��ʱ��1x������ۼӳ���Ϊ64chip������ɽ���ϱ�����̫�ܼ������⡣
             ����1x��afcʧ��ʱ����������ȡ12����ÿ64x12=768chip�ڣ��ϱ���һ��64chip������ɽ����
             ����1x��afc����ʱ����������ȡ1����ÿ64x12=768chip�ϱ�һ������ۼӽ����
             ����evdoʱ����������ȡ1����ÿ1024chip��afcʧ������4096chip��afc�������ϱ�һ����ɽ����
             
   UNION�ṹ:  CBBP_UNIT0_CORR_RPT_PERIOD_UNION */
#define CBBP_UNIT0_CORR_RPT_PERIOD_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x2004)

/* �Ĵ���˵����
 bit[31:11]  ����
 bit[10:0]   ʹ����ɢ��������С������ʱ��ÿ����1024chip�ڵ�һ�����ݣ��ȴ��೤ʱ�䣬������һ��1024chip������λchip��
             �˽ӿ���Ҫ���ʹ����ɢ�����������С������ʱ���ж��ϱ��ܼ��������
             ���ڶྶ����ģʽ��BBP���������ۼӣ�������ʱ����������
   UNION�ṹ:  CBBP_UNIT0_CORR_WAIT_CHIP_UNION */
#define CBBP_UNIT0_CORR_WAIT_CHIP_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2008)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ������������ѡ��
             0����ʾ�����������1�����ݣ�
             1����ʾ�����������2�����ݣ�
             
   UNION�ṹ:  CBBP_UNIT0_ANT_SEL_UNION */
#define CBBP_UNIT0_ANT_SEL_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0x200C)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ģʽѡ��
             0����ʾ��ʼС������
             1����ʾpn�б�С������
             2����ʾ�ྶ������С�����������������ۼӣ�
             3����ʾС���������������ۼ��������ۼӣ�
             
   UNION�ṹ:  CBBP_UNIT0_MODE_UNION */
#define CBBP_UNIT0_MODE_ADDR                          (SOC_BBP_CDMA_BASE_ADDR + 0x2010)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9:0]    ����������λΪ64chip�����÷�ΧΪ1~512��
             
             ��ʼС������ʱ����֧��������������������Ϊ128����������Ϊ64*128=8192chip��
             PN�б�С������ʱ����֧������������������������̶�Ϊ64chip��
             �ྶ��������֧��ʵʱ������������������̶�50chip��
             С������ģʽ��С����������֧���������ݲ���������̶�Ϊ64chip
             
   UNION�ṹ:  CBBP_UNIT0_WIN_UNION */
#define CBBP_UNIT0_WIN_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0x2014)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��������ѡ��
             0����ʾʹ��ʵʱ���ݣ�
             1����ʾʹ�û��������
             
   UNION�ṹ:  CBBP_UNIT0_DATA_SEL_UNION */
#define CBBP_UNIT0_DATA_SEL_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x2018)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    �������ݵ�ģʽ���˲������������һ�λ�������ʱ�Ĳ���Data_store_mode��ͬ
             0��ʾ�����洢��
             1��ʾÿ1024chip�洢64chip��
             2��ʾÿ1024chip�洢96chip��
             3��ʾÿ1024chip�洢128chip��
             4��ʾÿ1024chip�洢256chip��
             5��ʾÿ1024chip�洢512chip��
             
   UNION�ṹ:  CBBP_UNIT0_DATA_STORE_MODE_UNION */
#define CBBP_UNIT0_DATA_STORE_MODE_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x201C)

/* �Ĵ���˵����
 bit[31:16]  ����
 bit[15:0]   ʹ��ʵʱ����ʱ���������ݵ���ʼλ�ã���base_cnt[21:6]�ϵ�λ�ã�1/2chip����
             
   UNION�ṹ:  CBBP_UNIT0_DATA_POS_UNION */
#define CBBP_UNIT0_DATA_POS_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x2020)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ʹ��ʵʱ����ʱ��Ч��
             0����ʾ���Ծͽ���ʼ������
             1������ȴ�Unit0_data_posʱ�����ܿ�ʼ������
             
   UNION�ṹ:  CBBP_UNIT0_DATA_POS_SEL_UNION */
#define CBBP_UNIT0_DATA_POS_SEL_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x2024)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    ��������ȡ����ʽ��
             0��ʾ����ȡ����
             1��ʾÿ1024chipȡ��64chip��
             2��ʾÿ1024chipȡ��96chip��
             3��ʾÿ1024chipȡ��128chip��
             4��ʾÿ1024chipȡ��256chip��
             5��ʾÿ1024chip�洢512chip��
             
             ˵����
             ����ʹ�û������ݣ�����Unit0_data_store_modeȷ���������ݵ�������ұ�������Unit0_data_mode<=Unit0_data_store_mode��
             ����ʹ��ʵʱ���ݣ����ʵ������ʱ���Ѿ������Unit0_data_posʱ�̣����������ȡ��ʱ����ʵ������ʱ�̿�ʼȡ��������ÿ1024chip���ȡ�����������64/96chip/128chip/256chipȡ��λ�ÿ�ʼȡ����
             
   UNION�ṹ:  CBBP_UNIT0_DATA_MODE_UNION */
#define CBBP_UNIT0_DATA_MODE_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x2028)

/* �Ĵ���˵����
 bit[31:5]   ����
 bit[4:0]    Pn�б�С������ʱ��pn offset������֧��1~16��
   UNION�ṹ:  CBBP_UNIT0_PN_NUM_UNION */
#define CBBP_UNIT0_PN_NUM_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0x202C)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    ��ɳ���
             0��32
             1��64
             2��96
             3��128
             4��256
             5��96*4=384
             6��64*12=768
             7��512
             �㷨�Ƽ���
             1xС����������ۼӳ��ȿ�����Ϊ64��128��256����Ӧ�ķ�����ۼӳ���Ϊ32��16��8��
             evdoС��������ɳ���Ϊ64��������ۼӳ���Ϊ32/16/8��
             1x�ྶ������ɳ���Ϊ64x12=768��afc��������64x1=64��afcʧ�������֣���Ӧ�ķ�����ۼӳ��ȷֱ�Ϊ8��96��
             Evdo�ྶ������ɳ���96x4=384��afc��������96x1=96��afcʧ��������Ӧ�ķ�����ۼӳ��ȷֱ�Ϊ8��32��
             
   UNION�ṹ:  CBBP_UNIT0_CORR_LENGTH_UNION */
#define CBBP_UNIT0_CORR_LENGTH_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x2030)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    ����ɳ���
             0��1
             1��2
             2��3
             3��4
             4��8
             5��16
             6��32
             7��96
             
             
             
             
   UNION�ṹ:  CBBP_UNIT0_NCORR_LENGTH_UNION */
#define CBBP_UNIT0_NCORR_LENGTH_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x2034)

/* �Ĵ���˵����
 bit[31:16]  ����
 bit[15:0]   ������������
   UNION�ṹ:  CBBP_UNIT0_ABS_TH_UNION */
#define CBBP_UNIT0_ABS_TH_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0x2038)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ������Ԫʹ���ź�
   UNION�ṹ:  CBBP_UNIT0_EN_UNION */
#define CBBP_UNIT0_EN_ADDR                            (SOC_BBP_CDMA_BASE_ADDR + 0x203C)

/* �Ĵ���˵����
 bit[31:16]  ����
 bit[15:0]   ��Ԫ0����С�������ϱ�����������
   UNION�ṹ:  CBBP_UNIT0_NOISE_ENERGY_UNION */
#define CBBP_UNIT0_NOISE_ENERGY_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x2040)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��Ԫ0�����ϱ�������ƫ��1/2chipָʾ���ྶ������С������ʱ��Ч��
             0����ʾ�ϱ���������������������ȫһ��
             1����ʾ�ϱ����������������������ƫ����1/2chip������ԭ�����õ�λ�ã�����ƫ����1/2chip
             
   UNION�ṹ:  CBBP_UNIT0_FRAME_SHIFT_UNION */
#define CBBP_UNIT0_FRAME_SHIFT_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x2044)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             ����Ƕྶ������С����������ʼС������ʱ����ʾ����Ԫ����������β��Ӧ��f-pich֡ͷλ�á�
             �����Pn�б�С����������ʾ��һ��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT0_PN0_FRAME_POS_UNION */
#define CBBP_UNIT0_PN0_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2048)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��2��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT0_PN1_FRAME_POS_UNION */
#define CBBP_UNIT0_PN1_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x204C)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��3��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT0_PN2_FRAME_POS_UNION */
#define CBBP_UNIT0_PN2_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2050)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[19:5]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��4��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT0_PN3_FRAME_POS_UNION */
#define CBBP_UNIT0_PN3_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2054)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��5��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT0_PN4_FRAME_POS_UNION */
#define CBBP_UNIT0_PN4_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2058)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��6��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT0_PN5_FRAME_POS_UNION */
#define CBBP_UNIT0_PN5_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x205C)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��7��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT0_PN6_FRAME_POS_UNION */
#define CBBP_UNIT0_PN6_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2060)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��8��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT0_PN7_FRAME_POS_UNION */
#define CBBP_UNIT0_PN7_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2064)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��9��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT0_PN8_FRAME_POS_UNION */
#define CBBP_UNIT0_PN8_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2068)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��10��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT0_PN9_FRAME_POS_UNION */
#define CBBP_UNIT0_PN9_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x206C)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��11��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT0_PN10_FRAME_POS_UNION */
#define CBBP_UNIT0_PN10_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2070)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��12��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT0_PN11_FRAME_POS_UNION */
#define CBBP_UNIT0_PN11_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2074)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��13��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT0_PN12_FRAME_POS_UNION */
#define CBBP_UNIT0_PN12_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2078)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��14��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT0_PN13_FRAME_POS_UNION */
#define CBBP_UNIT0_PN13_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x207C)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��15��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT0_PN14_FRAME_POS_UNION */
#define CBBP_UNIT0_PN14_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2080)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��16��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT0_PN15_FRAME_POS_UNION */
#define CBBP_UNIT0_PN15_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2084)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ����ģʽѡ��
             0��ʾ1x����
             1��ʾevdo����
   UNION�ṹ:  CBBP_UNIT0_CS_1X_MODE_UNION */
#define CBBP_UNIT0_CS_1X_MODE_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x2088)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2]      ������Ԫ�ϱ�ģ��ʱ���ſ�
             0��ʾʱ���ſ���Ч
             1��ʾʱ�ӳ���
 bit[1]      ������Ԫ�Ŷ�ģ��ʱ���ſ�
             0��ʾʱ���ſ���Ч
             1��ʾʱ�ӳ���
 bit[0]      ������Ԫ���Ʋ���ʱ���ſ�bypass
             0��ʾʱ���ſ���Ч
             1��ʾʱ�ӳ���
   UNION�ṹ:  CBBP_UNIT0_SRCH_CK_BYPASS_UNION */
#define CBBP_UNIT0_SRCH_CK_BYPASS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x208C)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    ���������˲�ϵ����
             0��1/2
             1:1/16
             2:1/32
             3:1/64
             4:1/128
             5:1/256
   UNION�ṹ:  CBBP_UNIT0_NOISE_ALPHER_COEF_UNION */
#define CBBP_UNIT0_NOISE_ALPHER_COEF_ADDR             (SOC_BBP_CDMA_BASE_ADDR + 0x2090)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9:0]    �ӻ���������ȡ��ƫ�ƣ�chip��λ��
             ʹ�ó�������ԶС����������������4096chip���ݣ�����ʱ��ÿ1024chip��ȡ�������ݣ���ȡλ���ɴ˼Ĵ���ȷ��
   UNION�ṹ:  CBBP_UNIT0_DATA_STORE_OFF_UNION */
#define CBBP_UNIT0_DATA_STORE_OFF_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2094)



/***======================================================================***
                     (6/20) register_define_c_cs_mps_unit1
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ������Ԫʱ��Ƶ��ѡ��
             0����ʾ������Ԫ128��ʱ�ӣ�
             1����ʾ������Ԫ64��ʱ��
             Ĭ�ϲ���Ҫ�������
             
   UNION�ṹ:  CBBP_UNIT1_CLK_MODE_UNION */
#define CBBP_UNIT1_CLK_MODE_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x2300)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    ʹ���������ݶྶ��������С��������ʱ�����ٸ�����ۼӽ���ϱ�һ�Ρ�
             �˽ӿ���Ҫ�ǽ��afcʧ��ʱ��1x������ۼӳ���Ϊ64chip������ɽ���ϱ�����̫�ܼ������⡣
             ����1x��afcʧ��ʱ����������ȡ12����ÿ64x12=768chip�ڣ��ϱ���һ��64chip������ɽ����
             ����1x��afc����ʱ����������ȡ1����ÿ64x12=768chip�ϱ�һ������ۼӽ����
             ����evdoʱ����������ȡ1����ÿ1024chip��afcʧ������4096chip��afc�������ϱ�һ����ɽ����
             
   UNION�ṹ:  CBBP_UNIT1_CORR_RPT_PERIOD_UNION */
#define CBBP_UNIT1_CORR_RPT_PERIOD_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x2304)

/* �Ĵ���˵����
 bit[31:11]  ����
 bit[10:0]   ʹ����ɢ��������С������ʱ��ÿ����1024chip�ڵ�һ�����ݣ��ȴ��೤ʱ�䣬������һ��1024chip������λchip��
             �˽ӿ���Ҫ���ʹ����ɢ�����������С������ʱ���ж��ϱ��ܼ��������
             ���ڶྶ����ģʽ��BBP���������ۼӣ�������ʱ����������
   UNION�ṹ:  CBBP_UNIT1_CORR_WAIT_CHIP_UNION */
#define CBBP_UNIT1_CORR_WAIT_CHIP_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2308)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ������������ѡ��
             0����ʾ�����������1�����ݣ�
             1����ʾ�����������2�����ݣ�
             
   UNION�ṹ:  CBBP_UNIT1_ANT_SEL_UNION */
#define CBBP_UNIT1_ANT_SEL_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0x230C)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ģʽѡ��
             0����ʾ��ʼС������
             1����ʾpn�б�С������
             2����ʾ�ྶ������С�����������������ۼӣ�
             3����ʾС���������������ۼ��������ۼӣ�
             
   UNION�ṹ:  CBBP_UNIT1_MODE_UNION */
#define CBBP_UNIT1_MODE_ADDR                          (SOC_BBP_CDMA_BASE_ADDR + 0x2310)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9:0]    ����������λΪ64chip�����÷�ΧΪ1~512��
             
             ��ʼС������ʱ����֧��������������������Ϊ128����������Ϊ64*128=8192chip��
             PN�б�С������ʱ����֧������������������������̶�Ϊ64chip��
             �ྶ��������֧��ʵʱ������������������̶�50chip��
             С������ģʽ��С����������֧���������ݲ���������̶�Ϊ64chip
             
   UNION�ṹ:  CBBP_UNIT1_WIN_UNION */
#define CBBP_UNIT1_WIN_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0x2314)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��������ѡ��
             0����ʾʹ��ʵʱ���ݣ�
             1����ʾʹ�û��������
             
   UNION�ṹ:  CBBP_UNIT1_DATA_SEL_UNION */
#define CBBP_UNIT1_DATA_SEL_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x2318)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    �������ݵ�ģʽ���˲������������һ�λ�������ʱ�Ĳ���Data_store_mode��ͬ
             0��ʾ�����洢��
             1��ʾÿ1024chip�洢64chip��
             2��ʾÿ1024chip�洢96chip��
             3��ʾÿ1024chip�洢128chip��
             4��ʾÿ1024chip�洢256chip
             5��ʾÿ1024chip�洢512chip��
             
   UNION�ṹ:  CBBP_UNIT1_DATA_STORE_MODE_UNION */
#define CBBP_UNIT1_DATA_STORE_MODE_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x231C)

/* �Ĵ���˵����
 bit[31:16]  ����
 bit[15:0]   ʹ��ʵʱ����ʱ���������ݵ���ʼλ�ã���base_cnt[21:6]�ϵ�λ�ã�1/2chip����
             
   UNION�ṹ:  CBBP_UNIT1_DATA_POS_UNION */
#define CBBP_UNIT1_DATA_POS_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x2320)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ʹ��ʵʱ����ʱ��Ч��
             0����ʾ���Ծͽ���ʼ������
             1������ȴ�Unit0_data_posʱ�����ܿ�ʼ������
             
   UNION�ṹ:  CBBP_UNIT1_DATA_POS_SEL_UNION */
#define CBBP_UNIT1_DATA_POS_SEL_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x2324)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    ��������ȡ����ʽ��
             0��ʾ����ȡ����
             1��ʾÿ1024chipȡ��64chip��
             2��ʾÿ1024chipȡ��96chip��
             3��ʾÿ1024chipȡ��128chip��
             4��ʾÿ1024chipȡ��256chip
             5��ʾÿ1024chip�洢512chip��
             
             ˵����
             ����ʹ�û������ݣ�����Unit0_data_store_modeȷ���������ݵ�������ұ�������Unit0_data_mode<=Unit0_data_store_mode��
             ����ʹ��ʵʱ���ݣ����ʵ������ʱ���Ѿ������Unit0_data_posʱ�̣����������ȡ��ʱ����ʵ������ʱ�̿�ʼȡ��������ÿ1024chip���ȡ�����������64/96chip/128chip/256chipȡ��λ�ÿ�ʼȡ����
             
   UNION�ṹ:  CBBP_UNIT1_DATA_MODE_UNION */
#define CBBP_UNIT1_DATA_MODE_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x2328)

/* �Ĵ���˵����
 bit[31:5]   ����
 bit[4:0]    Pn�б�С������ʱ��pn offset������֧��1~16��
   UNION�ṹ:  CBBP_UNIT1_PN_NUM_UNION */
#define CBBP_UNIT1_PN_NUM_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0x232C)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    ��ɳ���
             0��32
             1��64
             2��96
             3��128
             4��256
             5��96*4=384
             6��64*12=768
             7��512
             �㷨�Ƽ���
             1xС����������ۼӳ��ȿ�����Ϊ64��128��256����Ӧ�ķ�����ۼӳ���Ϊ32��16��8��
             evdoС��������ɳ���Ϊ64��������ۼӳ���Ϊ32/16/8��
             1x�ྶ������ɳ���Ϊ64x12=768��afc��������64x1=64��afcʧ�������֣���Ӧ�ķ�����ۼӳ��ȷֱ�Ϊ8��96��
             Evdo�ྶ������ɳ���96x4=384��afc��������96x1=96��afcʧ��������Ӧ�ķ�����ۼӳ��ȷֱ�Ϊ8��32��
             
   UNION�ṹ:  CBBP_UNIT1_CORR_LENGTH_UNION */
#define CBBP_UNIT1_CORR_LENGTH_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x2330)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    ����ɳ���
             0��1
             1��2
             2��3
             3��4
             4��8
             5��16
             6��32
             7��96
             
             
             
             
   UNION�ṹ:  CBBP_UNIT1_NCORR_LENGTH_UNION */
#define CBBP_UNIT1_NCORR_LENGTH_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x2334)

/* �Ĵ���˵����
 bit[31:16]  ����
 bit[15:0]   ������������
   UNION�ṹ:  CBBP_UNIT1_ABS_TH_UNION */
#define CBBP_UNIT1_ABS_TH_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0x2338)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ������Ԫʹ���ź�
   UNION�ṹ:  CBBP_UNIT1_EN_UNION */
#define CBBP_UNIT1_EN_ADDR                            (SOC_BBP_CDMA_BASE_ADDR + 0x233C)

/* �Ĵ���˵����
 bit[31:16]  ����
 bit[15:0]   ��Ԫ0����С�������ϱ�����������
   UNION�ṹ:  CBBP_UNIT1_NOISE_ENERGY_UNION */
#define CBBP_UNIT1_NOISE_ENERGY_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x2340)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��Ԫ0�����ϱ�������ƫ��1/2chipָʾ���ྶ������С������ʱ��Ч��
             0����ʾ�ϱ���������������������ȫһ��
             1����ʾ�ϱ����������������������ƫ����1/2chip������ԭ�����õ�λ�ã�����ƫ����1/2chip
             
   UNION�ṹ:  CBBP_UNIT1_FRAME_SHIFT_UNION */
#define CBBP_UNIT1_FRAME_SHIFT_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x2344)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             ����Ƕྶ������С����������ʼС������ʱ����ʾ����Ԫ����������β��Ӧ��f-pich֡ͷλ�á�
             �����Pn�б�С����������ʾ��һ��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT1_PN0_FRAME_POS_UNION */
#define CBBP_UNIT1_PN0_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2348)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��2��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT1_PN1_FRAME_POS_UNION */
#define CBBP_UNIT1_PN1_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x234C)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��3��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT1_PN2_FRAME_POS_UNION */
#define CBBP_UNIT1_PN2_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2350)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[19:5]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��4��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT1_PN3_FRAME_POS_UNION */
#define CBBP_UNIT1_PN3_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2354)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��5��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT1_PN4_FRAME_POS_UNION */
#define CBBP_UNIT1_PN4_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2358)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��6��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT1_PN5_FRAME_POS_UNION */
#define CBBP_UNIT1_PN5_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x235C)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��7��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT1_PN6_FRAME_POS_UNION */
#define CBBP_UNIT1_PN6_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2360)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��8��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT1_PN7_FRAME_POS_UNION */
#define CBBP_UNIT1_PN7_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2364)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��9��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT1_PN8_FRAME_POS_UNION */
#define CBBP_UNIT1_PN8_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2368)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��10��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT1_PN9_FRAME_POS_UNION */
#define CBBP_UNIT1_PN9_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x236C)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��11��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT1_PN10_FRAME_POS_UNION */
#define CBBP_UNIT1_PN10_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2370)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��12��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT1_PN11_FRAME_POS_UNION */
#define CBBP_UNIT1_PN11_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2374)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��13��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT1_PN12_FRAME_POS_UNION */
#define CBBP_UNIT1_PN12_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2378)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��14��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT1_PN13_FRAME_POS_UNION */
#define CBBP_UNIT1_PN13_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x237C)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��15��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT1_PN14_FRAME_POS_UNION */
#define CBBP_UNIT1_PN14_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2380)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��16��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT1_PN15_FRAME_POS_UNION */
#define CBBP_UNIT1_PN15_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2384)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ����ģʽѡ��
             0��ʾ1x����
             1��ʾevdo����
   UNION�ṹ:  CBBP_UNIT1_CS_1X_MODE_UNION */
#define CBBP_UNIT1_CS_1X_MODE_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x2388)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2]      ������Ԫ�ϱ�ģ��ʱ���ſ�
             0��ʾʱ���ſ���Ч
             1��ʾʱ�ӳ���
 bit[1]      ������Ԫ�Ŷ�ģ��ʱ���ſ�
             0��ʾʱ���ſ���Ч
             1��ʾʱ�ӳ���
 bit[0]      ������Ԫ���Ʋ���ʱ���ſ�bypass
             0��ʾʱ���ſ���Ч
             1��ʾʱ�ӳ���
   UNION�ṹ:  CBBP_UNIT1_SRCH_CK_BYPASS_UNION */
#define CBBP_UNIT1_SRCH_CK_BYPASS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x238C)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    ���������˲�ϵ����
             0��1/2
             1:1/16
             2:1/32
             3:1/64
             4:1/128
             5:1/256
   UNION�ṹ:  CBBP_UNIT1_NOISE_ALPHER_COEF_UNION */
#define CBBP_UNIT1_NOISE_ALPHER_COEF_ADDR             (SOC_BBP_CDMA_BASE_ADDR + 0x2390)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9:0]    �ӻ���������ȡ��ƫ�ƣ�chip��λ��
             ʹ�ó�������ԶС����������������4096chip���ݣ�����ʱ��ÿ1024chip��ȡ�������ݣ���ȡλ���ɴ˼Ĵ���ȷ��
   UNION�ṹ:  CBBP_UNIT1_DATA_STORE_OFF_UNION */
#define CBBP_UNIT1_DATA_STORE_OFF_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2394)



/***======================================================================***
                     (7/20) register_define_c_cs_mps_unit2
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ������Ԫʱ��Ƶ��ѡ��
             0����ʾ������Ԫ128��ʱ�ӣ�
             1����ʾ������Ԫ64��ʱ��
             Ĭ�ϲ���Ҫ�������
             
   UNION�ṹ:  CBBP_UNIT2_CLK_MODE_UNION */
#define CBBP_UNIT2_CLK_MODE_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x2600)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    ʹ���������ݶྶ��������С��������ʱ�����ٸ�����ۼӽ���ϱ�һ�Ρ�
             �˽ӿ���Ҫ�ǽ��afcʧ��ʱ��1x������ۼӳ���Ϊ64chip������ɽ���ϱ�����̫�ܼ������⡣
             ����1x��afcʧ��ʱ����������ȡ12����ÿ64x12=768chip�ڣ��ϱ���һ��64chip������ɽ����
             ����1x��afc����ʱ����������ȡ1����ÿ64x12=768chip�ϱ�һ������ۼӽ����
             ����evdoʱ����������ȡ1����ÿ1024chip��afcʧ������4096chip��afc�������ϱ�һ����ɽ����
             
   UNION�ṹ:  CBBP_UNIT2_CORR_RPT_PERIOD_UNION */
#define CBBP_UNIT2_CORR_RPT_PERIOD_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x2604)

/* �Ĵ���˵����
 bit[31:11]  ����
 bit[10:0]   ʹ����ɢ��������С������ʱ��ÿ����1024chip�ڵ�һ�����ݣ��ȴ��೤ʱ�䣬������һ��1024chip������λchip��
             �˽ӿ���Ҫ���ʹ����ɢ�����������С������ʱ���ж��ϱ��ܼ��������
             ���ڶྶ����ģʽ��BBP���������ۼӣ�������ʱ����������
   UNION�ṹ:  CBBP_UNIT2_CORR_WAIT_CHIP_UNION */
#define CBBP_UNIT2_CORR_WAIT_CHIP_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2608)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ������������ѡ��
             0����ʾ�����������1�����ݣ�
             1����ʾ�����������2�����ݣ�
             
   UNION�ṹ:  CBBP_UNIT2_ANT_SEL_UNION */
#define CBBP_UNIT2_ANT_SEL_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0x260C)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ģʽѡ��
             0����ʾ��ʼС������
             1����ʾpn�б�С������
             2����ʾ�ྶ������С�����������������ۼӣ�
             3����ʾС���������������ۼ��������ۼӣ�
             
   UNION�ṹ:  CBBP_UNIT2_MODE_UNION */
#define CBBP_UNIT2_MODE_ADDR                          (SOC_BBP_CDMA_BASE_ADDR + 0x2610)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9:0]    ����������λΪ64chip�����÷�ΧΪ1~512��
             
             ��ʼС������ʱ����֧��������������������Ϊ128����������Ϊ64*128=8192chip��
             PN�б�С������ʱ����֧������������������������̶�Ϊ64chip��
             �ྶ��������֧��ʵʱ������������������̶�50chip��
             С������ģʽ��С����������֧���������ݲ���������̶�Ϊ64chip
             
   UNION�ṹ:  CBBP_UNIT2_WIN_UNION */
#define CBBP_UNIT2_WIN_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0x2614)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��������ѡ��
             0����ʾʹ��ʵʱ���ݣ�
             1����ʾʹ�û��������
             
   UNION�ṹ:  CBBP_UNIT2_DATA_SEL_UNION */
#define CBBP_UNIT2_DATA_SEL_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x2618)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    �������ݵ�ģʽ���˲������������һ�λ�������ʱ�Ĳ���Data_store_mode��ͬ
             0��ʾ�����洢��
             1��ʾÿ1024chip�洢64chip��
             2��ʾÿ1024chip�洢96chip��
             3��ʾÿ1024chip�洢128chip��
             4��ʾÿ1024chip�洢256chip
             5��ʾÿ1024chip�洢512chip��
             
   UNION�ṹ:  CBBP_UNIT2_DATA_STORE_MODE_UNION */
#define CBBP_UNIT2_DATA_STORE_MODE_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x261C)

/* �Ĵ���˵����
 bit[31:16]  ����
 bit[15:0]   ʹ��ʵʱ����ʱ���������ݵ���ʼλ�ã���base_cnt[21:6]�ϵ�λ�ã�1/2chip����
             
   UNION�ṹ:  CBBP_UNIT2_DATA_POS_UNION */
#define CBBP_UNIT2_DATA_POS_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x2620)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ʹ��ʵʱ����ʱ��Ч��
             0����ʾ���Ծͽ���ʼ������
             1������ȴ�Unit0_data_posʱ�����ܿ�ʼ������
             
   UNION�ṹ:  CBBP_UNIT2_DATA_POS_SEL_UNION */
#define CBBP_UNIT2_DATA_POS_SEL_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x2624)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    ��������ȡ����ʽ��
             0��ʾ����ȡ����
             1��ʾÿ1024chipȡ��64chip��
             2��ʾÿ1024chipȡ��96chip��
             3��ʾÿ1024chipȡ��128chip��
             4��ʾÿ1024chipȡ��256chip
             5��ʾÿ1024chip�洢512chip��
             
             ˵����
             ����ʹ�û������ݣ�����Unit0_data_store_modeȷ���������ݵ�������ұ�������Unit0_data_mode<=Unit0_data_store_mode��
             ����ʹ��ʵʱ���ݣ����ʵ������ʱ���Ѿ������Unit0_data_posʱ�̣����������ȡ��ʱ����ʵ������ʱ�̿�ʼȡ��������ÿ1024chip���ȡ�����������64/96chip/128chip/256chipȡ��λ�ÿ�ʼȡ����
             
   UNION�ṹ:  CBBP_UNIT2_DATA_MODE_UNION */
#define CBBP_UNIT2_DATA_MODE_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x2628)

/* �Ĵ���˵����
 bit[31:5]   ����
 bit[4:0]    Pn�б�С������ʱ��pn offset������֧��1~16��
   UNION�ṹ:  CBBP_UNIT2_PN_NUM_UNION */
#define CBBP_UNIT2_PN_NUM_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0x262C)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    ��ɳ���
             0��32
             1��64
             2��96
             3��128
             4��256
             5��96*4=384
             6��64*12=768
             7��512
             �㷨�Ƽ���
             1xС����������ۼӳ��ȿ�����Ϊ64��128��256����Ӧ�ķ�����ۼӳ���Ϊ32��16��8��
             evdoС��������ɳ���Ϊ64��������ۼӳ���Ϊ32/16/8��
             1x�ྶ������ɳ���Ϊ64x12=768��afc��������64x1=64��afcʧ�������֣���Ӧ�ķ�����ۼӳ��ȷֱ�Ϊ8��96��
             Evdo�ྶ������ɳ���96x4=384��afc��������96x1=96��afcʧ��������Ӧ�ķ�����ۼӳ��ȷֱ�Ϊ8��32��
             
   UNION�ṹ:  CBBP_UNIT2_CORR_LENGTH_UNION */
#define CBBP_UNIT2_CORR_LENGTH_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x2630)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    ����ɳ���
             0��1
             1��2
             2��3
             3��4
             4��8
             5��16
             6��32
             7��96
             
             
             
             
   UNION�ṹ:  CBBP_UNIT2_NCORR_LENGTH_UNION */
#define CBBP_UNIT2_NCORR_LENGTH_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x2634)

/* �Ĵ���˵����
 bit[31:16]  ����
 bit[15:0]   ������������
   UNION�ṹ:  CBBP_UNIT2_ABS_TH_UNION */
#define CBBP_UNIT2_ABS_TH_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0x2638)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ������Ԫʹ���ź�
   UNION�ṹ:  CBBP_UNIT2_EN_UNION */
#define CBBP_UNIT2_EN_ADDR                            (SOC_BBP_CDMA_BASE_ADDR + 0x263C)

/* �Ĵ���˵����
 bit[31:16]  ����
 bit[15:0]   ��Ԫ0����С�������ϱ�����������
   UNION�ṹ:  CBBP_UNIT2_NOISE_ENERGY_UNION */
#define CBBP_UNIT2_NOISE_ENERGY_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x2640)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��Ԫ0�����ϱ�������ƫ��1/2chipָʾ���ྶ������С������ʱ��Ч��
             0����ʾ�ϱ���������������������ȫһ��
             1����ʾ�ϱ����������������������ƫ����1/2chip������ԭ�����õ�λ�ã�����ƫ����1/2chip
             
   UNION�ṹ:  CBBP_UNIT2_FRAME_SHIFT_UNION */
#define CBBP_UNIT2_FRAME_SHIFT_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x2644)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             ����Ƕྶ������С����������ʼС������ʱ����ʾ����Ԫ����������β��Ӧ��f-pich֡ͷλ�á�
             �����Pn�б�С����������ʾ��һ��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT2_PN0_FRAME_POS_UNION */
#define CBBP_UNIT2_PN0_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2648)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��2��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT2_PN1_FRAME_POS_UNION */
#define CBBP_UNIT2_PN1_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x264C)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��3��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT2_PN2_FRAME_POS_UNION */
#define CBBP_UNIT2_PN2_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2650)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[19:5]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��4��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT2_PN3_FRAME_POS_UNION */
#define CBBP_UNIT2_PN3_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2654)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��5��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT2_PN4_FRAME_POS_UNION */
#define CBBP_UNIT2_PN4_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2658)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��6��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT2_PN5_FRAME_POS_UNION */
#define CBBP_UNIT2_PN5_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x265C)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��7��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT2_PN6_FRAME_POS_UNION */
#define CBBP_UNIT2_PN6_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2660)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��8��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT2_PN7_FRAME_POS_UNION */
#define CBBP_UNIT2_PN7_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2664)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��9��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT2_PN8_FRAME_POS_UNION */
#define CBBP_UNIT2_PN8_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2668)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��10��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT2_PN9_FRAME_POS_UNION */
#define CBBP_UNIT2_PN9_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x266C)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��11��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT2_PN10_FRAME_POS_UNION */
#define CBBP_UNIT2_PN10_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2670)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��12��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT2_PN11_FRAME_POS_UNION */
#define CBBP_UNIT2_PN11_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2674)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��13��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT2_PN12_FRAME_POS_UNION */
#define CBBP_UNIT2_PN12_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2678)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��14��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT2_PN13_FRAME_POS_UNION */
#define CBBP_UNIT2_PN13_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x267C)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��15��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT2_PN14_FRAME_POS_UNION */
#define CBBP_UNIT2_PN14_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2680)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��16��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT2_PN15_FRAME_POS_UNION */
#define CBBP_UNIT2_PN15_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2684)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ����ģʽѡ��
             0��ʾ1x����
             1��ʾevdo����
   UNION�ṹ:  CBBP_UNIT2_CS_1X_MODE_UNION */
#define CBBP_UNIT2_CS_1X_MODE_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x2688)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2]      ������Ԫ�ϱ�ģ��ʱ���ſ�
             0��ʾʱ���ſ���Ч
             1��ʾʱ�ӳ���
 bit[1]      ������Ԫ�Ŷ�ģ��ʱ���ſ�
             0��ʾʱ���ſ���Ч
             1��ʾʱ�ӳ���
 bit[0]      ������Ԫ���Ʋ���ʱ���ſ�bypass
             0��ʾʱ���ſ���Ч
             1��ʾʱ�ӳ���
   UNION�ṹ:  CBBP_UNIT2_SRCH_CK_BYPASS_UNION */
#define CBBP_UNIT2_SRCH_CK_BYPASS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x268C)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    ���������˲�ϵ����
             0��1/2
             1:1/16
             2:1/32
             3:1/64
             4:1/128
             5:1/256
   UNION�ṹ:  CBBP_UNIT2_NOISE_ALPHER_COEF_UNION */
#define CBBP_UNIT2_NOISE_ALPHER_COEF_ADDR             (SOC_BBP_CDMA_BASE_ADDR + 0x2690)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9:0]    �ӻ���������ȡ��ƫ�ƣ�chip��λ��
             ʹ�ó�������ԶС����������������4096chip���ݣ�����ʱ��ÿ1024chip��ȡ�������ݣ���ȡλ���ɴ˼Ĵ���ȷ��
   UNION�ṹ:  CBBP_UNIT2_DATA_STORE_OFF_UNION */
#define CBBP_UNIT2_DATA_STORE_OFF_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2694)



/***======================================================================***
                     (8/20) register_define_c_cs_mps_unit3
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ������Ԫʱ��Ƶ��ѡ��
             0����ʾ������Ԫ128��ʱ�ӣ�
             1����ʾ������Ԫ64��ʱ��
             Ĭ�ϲ���Ҫ�������
             
   UNION�ṹ:  CBBP_UNIT3_CLK_MODE_UNION */
#define CBBP_UNIT3_CLK_MODE_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x2900)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    ʹ���������ݶྶ��������С��������ʱ�����ٸ�����ۼӽ���ϱ�һ�Ρ�
             �˽ӿ���Ҫ�ǽ��afcʧ��ʱ��1x������ۼӳ���Ϊ64chip������ɽ���ϱ�����̫�ܼ������⡣
             ����1x��afcʧ��ʱ����������ȡ12����ÿ64x12=768chip�ڣ��ϱ���һ��64chip������ɽ����
             ����1x��afc����ʱ����������ȡ1����ÿ64x12=768chip�ϱ�һ������ۼӽ����
             ����evdoʱ����������ȡ1����ÿ1024chip��afcʧ������4096chip��afc�������ϱ�һ����ɽ����
             
   UNION�ṹ:  CBBP_UNIT3_CORR_RPT_PERIOD_UNION */
#define CBBP_UNIT3_CORR_RPT_PERIOD_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x2904)

/* �Ĵ���˵����
 bit[31:11]  ����
 bit[10:0]   ʹ����ɢ��������С������ʱ��ÿ����1024chip�ڵ�һ�����ݣ��ȴ��೤ʱ�䣬������һ��1024chip������λchip��
             �˽ӿ���Ҫ���ʹ����ɢ�����������С������ʱ���ж��ϱ��ܼ��������
             ���ڶྶ����ģʽ��BBP���������ۼӣ�������ʱ����������
   UNION�ṹ:  CBBP_UNIT3_CORR_WAIT_CHIP_UNION */
#define CBBP_UNIT3_CORR_WAIT_CHIP_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2908)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ������������ѡ��
             0����ʾ�����������1�����ݣ�
             1����ʾ�����������2�����ݣ�
             
   UNION�ṹ:  CBBP_UNIT3_ANT_SEL_UNION */
#define CBBP_UNIT3_ANT_SEL_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0x290C)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ģʽѡ��
             0����ʾ��ʼС������
             1����ʾpn�б�С������
             2����ʾ�ྶ������С�����������������ۼӣ�
             3����ʾС���������������ۼ��������ۼӣ�
             
   UNION�ṹ:  CBBP_UNIT3_MODE_UNION */
#define CBBP_UNIT3_MODE_ADDR                          (SOC_BBP_CDMA_BASE_ADDR + 0x2910)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9:0]    ����������λΪ64chip�����÷�ΧΪ1~512��
             
             ��ʼС������ʱ����֧��������������������Ϊ128����������Ϊ64*128=8192chip��
             PN�б�С������ʱ����֧������������������������̶�Ϊ64chip��
             �ྶ��������֧��ʵʱ������������������̶�50chip��
             С������ģʽ��С����������֧���������ݲ���������̶�Ϊ64chip��
             
   UNION�ṹ:  CBBP_UNIT3_WIN_UNION */
#define CBBP_UNIT3_WIN_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0x2914)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��������ѡ��
             0����ʾʹ��ʵʱ���ݣ�
             1����ʾʹ�û��������
             
   UNION�ṹ:  CBBP_UNIT3_DATA_SEL_UNION */
#define CBBP_UNIT3_DATA_SEL_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x2918)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    �������ݵ�ģʽ���˲������������һ�λ�������ʱ�Ĳ���Data_store_mode��ͬ
             0��ʾ�����洢��
             1��ʾÿ1024chip�洢64chip��
             2��ʾÿ1024chip�洢96chip��
             3��ʾÿ1024chip�洢128chip��
             4��ʾÿ1024chip�洢256chip
             5��ʾÿ1024chip�洢512chip��
             
   UNION�ṹ:  CBBP_UNIT3_DATA_STORE_MODE_UNION */
#define CBBP_UNIT3_DATA_STORE_MODE_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x291C)

/* �Ĵ���˵����
 bit[31:16]  ����
 bit[15:0]   ʹ��ʵʱ����ʱ���������ݵ���ʼλ�ã���base_cnt[21:6]�ϵ�λ�ã�1/2chip����
             
   UNION�ṹ:  CBBP_UNIT3_DATA_POS_UNION */
#define CBBP_UNIT3_DATA_POS_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x2920)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ʹ��ʵʱ����ʱ��Ч��
             0����ʾ���Ծͽ���ʼ������
             1������ȴ�Unit0_data_posʱ�����ܿ�ʼ������
             
   UNION�ṹ:  CBBP_UNIT3_DATA_POS_SEL_UNION */
#define CBBP_UNIT3_DATA_POS_SEL_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x2924)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    ��������ȡ����ʽ��
             0��ʾ����ȡ����
             1��ʾÿ1024chipȡ��64chip��
             2��ʾÿ1024chipȡ��96chip��
             3��ʾÿ1024chipȡ��128chip��
             4��ʾÿ1024chipȡ��256chip
             5��ʾÿ1024chip�洢512chip��
             
             ˵����
             ����ʹ�û������ݣ�����Unit0_data_store_modeȷ���������ݵ�������ұ�������Unit0_data_mode<=Unit0_data_store_mode��
             ����ʹ��ʵʱ���ݣ����ʵ������ʱ���Ѿ������Unit0_data_posʱ�̣����������ȡ��ʱ����ʵ������ʱ�̿�ʼȡ��������ÿ1024chip���ȡ�����������64/96chip/128chip/256chipȡ��λ�ÿ�ʼȡ����
             
   UNION�ṹ:  CBBP_UNIT3_DATA_MODE_UNION */
#define CBBP_UNIT3_DATA_MODE_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x2928)

/* �Ĵ���˵����
 bit[31:5]   ����
 bit[4:0]    Pn�б�С������ʱ��pn offset������֧��1~16��
   UNION�ṹ:  CBBP_UNIT3_PN_NUM_UNION */
#define CBBP_UNIT3_PN_NUM_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0x292C)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    ��ɳ���
             0��32
             1��64
             2��96
             3��128
             4��256
             5��96*4=384
             6��64*12=768
             7��512
             �㷨�Ƽ���
             1xС����������ۼӳ��ȿ�����Ϊ64��128��256����Ӧ�ķ�����ۼӳ���Ϊ32��16��8��
             evdoС��������ɳ���Ϊ64��������ۼӳ���Ϊ32/16/8��
             1x�ྶ������ɳ���Ϊ64x12=768��afc��������64x1=64��afcʧ�������֣���Ӧ�ķ�����ۼӳ��ȷֱ�Ϊ8��96��
             Evdo�ྶ������ɳ���96x4=384��afc��������96x1=96��afcʧ��������Ӧ�ķ�����ۼӳ��ȷֱ�Ϊ8��32��
             
   UNION�ṹ:  CBBP_UNIT3_CORR_LENGTH_UNION */
#define CBBP_UNIT3_CORR_LENGTH_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x2930)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    ����ɳ���
             0��1
             1��2
             2��3
             3��4
             4��8
             5��16
             6��32
             7��96
             
             
             
             
   UNION�ṹ:  CBBP_UNIT3_NCORR_LENGTH_UNION */
#define CBBP_UNIT3_NCORR_LENGTH_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x2934)

/* �Ĵ���˵����
 bit[31:16]  ����
 bit[15:0]   ������������
   UNION�ṹ:  CBBP_UNIT3_ABS_TH_UNION */
#define CBBP_UNIT3_ABS_TH_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0x2938)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ������Ԫʹ���ź�
   UNION�ṹ:  CBBP_UNIT3_EN_UNION */
#define CBBP_UNIT3_EN_ADDR                            (SOC_BBP_CDMA_BASE_ADDR + 0x293C)

/* �Ĵ���˵����
 bit[31:16]  ����
 bit[15:0]   ��Ԫ0����С�������ϱ�����������
   UNION�ṹ:  CBBP_UNIT3_NOISE_ENERGY_UNION */
#define CBBP_UNIT3_NOISE_ENERGY_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x2940)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��Ԫ0�����ϱ�������ƫ��1/2chipָʾ���ྶ������С������ʱ��Ч��
             0����ʾ�ϱ���������������������ȫһ��
             1����ʾ�ϱ����������������������ƫ����1/2chip������ԭ�����õ�λ�ã�����ƫ����1/2chip
             
   UNION�ṹ:  CBBP_UNIT3_FRAME_SHIFT_UNION */
#define CBBP_UNIT3_FRAME_SHIFT_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x2944)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             ����Ƕྶ������С����������ʼС������ʱ����ʾ����Ԫ����������β��Ӧ��f-pich֡ͷλ�á�
             �����Pn�б�С����������ʾ��һ��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT3_PN0_FRAME_POS_UNION */
#define CBBP_UNIT3_PN0_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2948)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��2��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT3_PN1_FRAME_POS_UNION */
#define CBBP_UNIT3_PN1_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x294C)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��3��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT3_PN2_FRAME_POS_UNION */
#define CBBP_UNIT3_PN2_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2950)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[19:5]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��4��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT3_PN3_FRAME_POS_UNION */
#define CBBP_UNIT3_PN3_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2954)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��5��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT3_PN4_FRAME_POS_UNION */
#define CBBP_UNIT3_PN4_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2958)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��6��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT3_PN5_FRAME_POS_UNION */
#define CBBP_UNIT3_PN5_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x295C)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��7��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT3_PN6_FRAME_POS_UNION */
#define CBBP_UNIT3_PN6_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2960)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��8��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT3_PN7_FRAME_POS_UNION */
#define CBBP_UNIT3_PN7_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2964)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��9��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT3_PN8_FRAME_POS_UNION */
#define CBBP_UNIT3_PN8_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2968)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��10��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT3_PN9_FRAME_POS_UNION */
#define CBBP_UNIT3_PN9_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x296C)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��11��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT3_PN10_FRAME_POS_UNION */
#define CBBP_UNIT3_PN10_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2970)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��12��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT3_PN11_FRAME_POS_UNION */
#define CBBP_UNIT3_PN11_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2974)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��13��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT3_PN12_FRAME_POS_UNION */
#define CBBP_UNIT3_PN12_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2978)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��14��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT3_PN13_FRAME_POS_UNION */
#define CBBP_UNIT3_PN13_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x297C)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��15��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT3_PN14_FRAME_POS_UNION */
#define CBBP_UNIT3_PN14_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2980)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
             �����Pn�б�С����������ʾ��16��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ��
             
   UNION�ṹ:  CBBP_UNIT3_PN15_FRAME_POS_UNION */
#define CBBP_UNIT3_PN15_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2984)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ����ģʽѡ��
             0��ʾ1x����
             1��ʾevdo����
   UNION�ṹ:  CBBP_UNIT3_CS_1X_MODE_UNION */
#define CBBP_UNIT3_CS_1X_MODE_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x2988)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2]      ������Ԫ�ϱ�ģ��ʱ���ſ�
             0��ʾʱ���ſ���Ч
             1��ʾʱ�ӳ���
 bit[1]      ������Ԫ�Ŷ�ģ��ʱ���ſ�
             0��ʾʱ���ſ���Ч
             1��ʾʱ�ӳ���
 bit[0]      ������Ԫ���Ʋ���ʱ���ſ�bypass
             0��ʾʱ���ſ���Ч
             1��ʾʱ�ӳ���
   UNION�ṹ:  CBBP_UNIT3_SRCH_CK_BYPASS_UNION */
#define CBBP_UNIT3_SRCH_CK_BYPASS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x298C)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    ���������˲�ϵ����
             0��1/2
             1:1/16
             2:1/32
             3:1/64
             4:1/128
             5:1/256
   UNION�ṹ:  CBBP_UNIT3_NOISE_ALPHER_COEF_UNION */
#define CBBP_UNIT3_NOISE_ALPHER_COEF_ADDR             (SOC_BBP_CDMA_BASE_ADDR + 0x2990)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9:0]    �ӻ���������ȡ��ƫ�ƣ�chip��λ��
             ʹ�ó�������ԶС����������������4096chip���ݣ�����ʱ��ÿ1024chip��ȡ�������ݣ���ȡλ���ɴ˼Ĵ���ȷ��
   UNION�ṹ:  CBBP_UNIT3_DATA_STORE_OFF_UNION */
#define CBBP_UNIT3_DATA_STORE_OFF_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2994)



/***======================================================================***
                     (9/20) register_define_c_cs_mps_mem
 ***======================================================================***/
/* �Ĵ���˵�����ྶ������С�����������������ۼӣ�ʱ���ϱ�128�������
            ��һ���洢���Ϊf-pich֡ͷΪUnit0_pn0_frame_pos����ɽ�����ڶ����洢���Ϊf-pich֡ͷΪ(Unit0_frame_pos-1/2chip)����ɽ������..��
            Bit[31:16]ΪQ·�����
            Bit[15:0]ΪI·�����
            
            С���������������ۼ��������ۼӣ�ʱ���ϱ�128�������
            ��һ���洢���Ϊf-pich֡ͷΪUnit0_pn0_frame_pos�Ľ�����ڶ����洢���Ϊf-pich֡ͷΪ(Unit0_frame_pos-1/2chip)�Ľ������..��
            Bit[15:0]Ϊ������ۼӽ����
            
            
            С������ʱ��ʹ�õ�ַ0~31���ϱ�32�������
            Bit[31:16]Ϊ��������С��pilot�ŵ�֡ͷ��base_cnt[19:4]��λ�ã�
            Bit[15:0]Ϊ������С���ϱ�����
 bit[31:16]  �ྶ������С�����������������ۼӣ�ʱΪQ·��ɽ��
             С������ʱΪС��pilot�ŵ�֡ͷ��base_cnt[21:6]�ϵ�λ�ã�1/2chip���ȡ�
 bit[15:0]   �ྶ������С�����������������ۼӣ�ʱΪI·��ɽ����
             С���������������ۼ��������ۼӣ�ʱΪ������ۼ�����
             С������ʱΪС������
   UNION�ṹ:  CBBP_UNIT0_RPT_UNION */
#define CBBP_UNIT0_RPT_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0x3000)
#define CBBP_UNIT0_RPT_MEMDEPTH  (128)

/* �Ĵ���˵�����ྶ������С�����������������ۼӣ�ʱ���ϱ�128�������
            ��һ���洢���Ϊf-pich֡ͷΪUnit0_pn0_frame_pos����ɽ�����ڶ����洢���Ϊf-pich֡ͷΪ(Unit0_frame_pos-1/2chip)����ɽ������..��
            Bit[31:16]ΪQ·�����
            Bit[15:0]ΪI·�����
            
            С���������������ۼ��������ۼӣ�ʱ���ϱ�128�������
            ��һ���洢���Ϊf-pich֡ͷΪUnit0_pn0_frame_pos�Ľ�����ڶ����洢���Ϊf-pich֡ͷΪ(Unit0_frame_pos-1/2chip)�Ľ������..��
            Bit[15:0]Ϊ������ۼӽ����
            
            
            С������ʱ��ʹ�õ�ַ0~31���ϱ�32�������
            Bit[31:16]Ϊ��������С��pilot�ŵ�֡ͷ��base_cnt[19:4]��λ�ã�
            Bit[15:0]Ϊ������С���ϱ�����
 bit[31:16]  �ྶ������С�����������������ۼӣ�ʱΪQ·��ɽ��
             С������ʱΪС��pilot�ŵ�֡ͷ��base_cnt[21:6]�ϵ�λ�ã�1/2chip���ȡ�
 bit[15:0]   �ྶ������С�����������������ۼӣ�ʱΪI·��ɽ����
             С���������������ۼ��������ۼӣ�ʱΪ������ۼ�����
             С������ʱΪС������
   UNION�ṹ:  CBBP_UNIT1_RPT_UNION */
#define CBBP_UNIT1_RPT_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0x3200)
#define CBBP_UNIT1_RPT_MEMDEPTH  (128)

/* �Ĵ���˵�����ྶ������С�����������������ۼӣ�ʱ���ϱ�128�������
            ��һ���洢���Ϊf-pich֡ͷΪUnit0_pn0_frame_pos����ɽ�����ڶ����洢���Ϊf-pich֡ͷΪ(Unit0_frame_pos-1/2chip)����ɽ������..��
            Bit[31:16]ΪQ·�����
            Bit[15:0]ΪI·�����
            
            С���������������ۼ��������ۼӣ�ʱ���ϱ�128�������
            ��һ���洢���Ϊf-pich֡ͷΪUnit0_pn0_frame_pos�Ľ�����ڶ����洢���Ϊf-pich֡ͷΪ(Unit0_frame_pos-1/2chip)�Ľ������..��
            Bit[15:0]Ϊ������ۼӽ����
            
            
            С������ʱ��ʹ�õ�ַ0~31���ϱ�32�������
            Bit[31:16]Ϊ��������С��pilot�ŵ�֡ͷ��base_cnt[19:4]��λ�ã�
            Bit[15:0]Ϊ������С���ϱ�����
 bit[31:16]  �ྶ������С�����������������ۼӣ�ʱΪQ·��ɽ��
             С������ʱΪС��pilot�ŵ�֡ͷ��base_cnt[21:6]�ϵ�λ�ã�1/2chip���ȡ�
 bit[15:0]   �ྶ������С�����������������ۼӣ�ʱΪI·��ɽ����
             С���������������ۼ��������ۼӣ�ʱΪ������ۼ�����
             С������ʱΪС������
   UNION�ṹ:  CBBP_UNIT2_RPT_UNION */
#define CBBP_UNIT2_RPT_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0x3400)
#define CBBP_UNIT2_RPT_MEMDEPTH  (128)

/* �Ĵ���˵�����ྶ������С�����������������ۼӣ�ʱ���ϱ�128�������
            ��һ���洢���Ϊf-pich֡ͷΪUnit0_pn0_frame_pos����ɽ�����ڶ����洢���Ϊf-pich֡ͷΪ(Unit0_frame_pos-1/2chip)����ɽ������..��
            Bit[31:16]ΪQ·�����
            Bit[15:0]ΪI·�����
            
            С���������������ۼ��������ۼӣ�ʱ���ϱ�128�������
            ��һ���洢���Ϊf-pich֡ͷΪUnit0_pn0_frame_pos�Ľ�����ڶ����洢���Ϊf-pich֡ͷΪ(Unit0_frame_pos-1/2chip)�Ľ������..��
            Bit[15:0]Ϊ������ۼӽ����
            
            
            С������ʱ��ʹ�õ�ַ0~31���ϱ�32�������
            Bit[31:16]Ϊ��������С��pilot�ŵ�֡ͷ��base_cnt[19:4]��λ�ã�
            Bit[15:0]Ϊ������С���ϱ�����
 bit[31:16]  �ྶ������С�����������������ۼӣ�ʱΪQ·��ɽ��
             С������ʱΪС��pilot�ŵ�֡ͷ��base_cnt[21:6]�ϵ�λ�ã�1/2chip���ȡ�
 bit[15:0]   �ྶ������С�����������������ۼӣ�ʱΪI·��ɽ����
             С���������������ۼ��������ۼӣ�ʱΪ������ۼ�����
             С������ʱΪС������
   UNION�ṹ:  CBBP_UNIT3_RPT_UNION */
#define CBBP_UNIT3_RPT_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0x3600)
#define CBBP_UNIT3_RPT_MEMDEPTH  (128)



/***======================================================================***
                     (10/20) register_define_c_dldec
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ���뽨��ʹ�ܣ������������������������ɺ�����Ϊ1
   UNION�ṹ:  CBBP_DLDEC_ESTB_IND_UNION */
#define CBBP_DLDEC_ESTB_IND_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x4008)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ���������źţ�����������������������뽨��ʹ��������ɺ�����
   UNION�ṹ:  CBBP_DLDEC_DEC_START_UNION */
#define CBBP_DLDEC_DEC_START_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x400C)

/* �Ĵ���˵����
 bit[31:29]  ����
 bit[28:16]  ��Ϣ���س���
 bit[15:12]  �������ֶ������β�λ���Ѱ����ͬ���ŵ�����ʱ�ò�������Ϊ0�������ŵ��ò�������Ϊ8��6. 
 bit[11:9]   ����
 bit[8]      reserve_bitָʾ��1��ʾ����reserve����
 bit[7:5]    ����
 bit[4]      CRC�ڲ��Ĵ�����ʼ��״̬��
             0��ȫ0��1��ȫ1��
             
 bit[3:0]    CRC
   UNION�ṹ:  CBBP_PACKET_PARA_UNION */
#define CBBP_PACKET_PARA_ADDR                         (SOC_BBP_CDMA_BASE_ADDR + 0x4010)

/* �Ĵ���˵����
 bit[31:17]  ����
 bit[16]     ��Turbo����ģʽ�£�harq�ϲ�ʹ�ܡ�1����ʾ�����ʱΪ�����ݣ������harq�ϲ������򲻽��кϲ���0����ʾ��ֹ�ϲ�
 bit[15:13]  ����
 bit[12]     C����ģʽ��0��ʾ1X��1��ʾEVDO
 bit[11]     ����
 bit[10:8]   0: 1X���о�����������������; 1: 1X����TURBO���������������;2: EVDO����������������; 3: 1X �⽻֯���׽��ظ��������ģʽ; 4: ��VTB�������ģʽ; 5: ��TURBO�������ģʽ��
 bit[7:5]    ����
 bit[4]      1X turbo����ģʽ��0��ʾĬ��ģʽ��1��ʾ����ģʽ��
 bit[3]      ����
 bit[2:0]    �����ʣ�������Ϊ1/Rʱ������ΪR��
   UNION�ṹ:  CBBP_DEC_MODE_UNION */
#define CBBP_DEC_MODE_ADDR                            (SOC_BBP_CDMA_BASE_ADDR + 0x4014)

/* �Ĵ���˵����
 bit[31:17]  ����
 bit[16:0]   �����ʼ��״̬��
   UNION�ṹ:  CBBP_SCR_INIT_STATE_UNION */
#define CBBP_SCR_INIT_STATE_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x4018)

/* �Ĵ���˵����
 bit[31:12]  ����
 bit[11:8]   block��֯m������
 bit[7:0]    block��֯j������
   UNION�ṹ:  CBBP_BLOCK_INTL_PARA_UNION */
#define CBBP_BLOCK_INTL_PARA_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x401C)

/* �Ĵ���˵����
 bit[31:8]   ����
 bit[7:4]    permuting��֯m������
 bit[3]      ����
 bit[2:0]    permuting��֯k������
   UNION�ṹ:  CBBP_PERMUTING_INTL_PARA_UNION */
#define CBBP_PERMUTING_INTL_PARA_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x4020)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:12]  matrix��֯k����
 bit[11:8]   matrix��֯m����
 bit[7]      ����
 bit[6:4]    matrix��֯r����
 bit[3:0]    matrix��֯d����
   UNION�ṹ:  CBBP_MATRIX_INTL_PARA_UNION */
#define CBBP_MATRIX_INTL_PARA_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x4024)

/* �Ĵ���˵����
 bit[31:19]  ����
 bit[18:16]  0��Matrix Interleave��֯��EVDO ������ʹ�ã���1������Symbol Permuting��֯��EVDOʹ�ã���2������Bit-Reversal Order Interleave��֯��1Xʹ�ã���3������Forward-Backwards Bit-Reversal Order Interleave��֯��FOR_FCH_CCSH_INTERLEAVER_TYPE = 0,1Xʹ�ã���4������Forward-Backwards Bit-Reversal Order Interleave��֯��FOR_FCH_CCSH_INTERLEAVER_TYPE = 1,1Xʹ�ã���5������TYPE1 Block Interleave��֯��1Xʹ�ã�������ģ���ֹ���ã���6������TYPE2 Block Interleave��֯��1Xʹ�ã�������ģ���ֹ���ã���7������Reverse Interleave��EVDOʹ�ã�������ģ���ֹ���ã�
 bit[15]     ����
 bit[14:0]   ��֯����
   UNION�ṹ:  CBBP_INTL_PAPA_UNION */
#define CBBP_INTL_PAPA_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0x4028)

/* �Ĵ���˵����
 bit[31:25]  ����
 bit[24:0]   ���ͼ������ͱ���Ϊ��һ��״ָ̬ʾ��������ͼ��Ϊ11010ʱ����ʾ��һ�������������ݴ�ף���������ͨ����
   UNION�ṹ:  CBBP_PUNC_PATTERN_UNION */
#define CBBP_PUNC_PATTERN_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0x402C)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9:8]    0:���ݴ��ͼ�����������Ϣ������ERAMģʽ����Ҫͨ�����ͼ�����������Ϣ�ĳ�����
             1����ERAMģʽ�£����ݹ�ʽ��������Ϣ
             2��ERAMģʽ�£����ݹ�ʽ��������Ϣ
             
 bit[7:5]    ����
 bit[4:0]    �������
   UNION�ṹ:  CBBP_PUNC_PERIOD_UNION */
#define CBBP_PUNC_PERIOD_ADDR                         (SOC_BBP_CDMA_BASE_ADDR + 0x4030)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ���ǰ���ȣ����ظ��󳤶�
   UNION�ṹ:  CBBP_DLDEC_LEN_BEF_PUNC_UNION */
#define CBBP_DLDEC_LEN_BEF_PUNC_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x4034)

/* �Ĵ���˵����
 bit[31]     ����vtb����ģʽ,1��ʾ����vtb����ģʽ��
 bit[30:15]  ����
 bit[14:0]   ����ά�ر�����ǰLLR RAM�Ļ���ַ���ǳ���vtb����ʱ����Ϊ0,�������ʱ����ʵ��LLR��ʼλ�����á����糬������һ�����볤��Ϊ768�����ѵ�����г���Ϊ128����ڶ����������ַ����Ϊ����768-128��*code_rate/4��-1��
   UNION�ṹ:  CBBP_DLDEC_LONG_VTB_PARA_UNION */
#define CBBP_DLDEC_LONG_VTB_PARA_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x4038)

/* �Ĵ���˵����
 bit[31]     ά�ر������ʼ��״̬��Чʹ��
 bit[30:8]   ����
 bit[7:0]    ά�رȳ�ʼ��״̬������ǰ���ϱ��Ķ�Ӧʱ϶״̬���á�
   UNION�ṹ:  CBBP_VTB_INIT_STATE_UNION */
#define CBBP_VTB_INIT_STATE_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x403C)

/* �Ĵ���˵����
 bit[31:5]   ����
 bit[4]      ��ǿvtbʹ��
 bit[3:0]    ��ǿvtb���ݴ�����֧��1~8����������Ϊ4ʱ����ʾ����һ�������⣬��໹��3�����롣
   UNION�ṹ:  CBBP_EVTB_EN_UNION */
#define CBBP_EVTB_EN_ADDR                             (SOC_BBP_CDMA_BASE_ADDR + 0x4040)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      vtb����ģʽ��0��ʾ��0״̬��ʼ���ݣ�1��ʾ��������״̬��ʼ���ݡ�
   UNION�ṹ:  CBBP_VTB_TB_MODE_UNION */
#define CBBP_VTB_TB_MODE_ADDR                         (SOC_BBP_CDMA_BASE_ADDR + 0x4044)

/* �Ĵ���˵����
 bit[31:9]   ����
 bit[8:0]    vtb����״̬�ϱ�ʱ϶���ڳ�����顢Ѱ���ŵ���ͬ���ŵ�ʱ��Ҫ����ѵ�����Ƚ������á�
   UNION�ṹ:  CBBP_VTB_TB_RPT_SLOT_UNION */
#define CBBP_VTB_TB_RPT_SLOT_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x4048)

/* �Ĵ���˵����
 bit[31:9]   ����
 bit[8]      ���볬ʱ����ʹ��
 bit[7:6]    ����
 bit[5:0]    ����ģ�鳬ʱ��������ֵ��0ֵ�������ã�ʵ�ʳ�ʱ����ֵΪdldec_overtime_cfg *8192�����Ƽ�����ֵΪ16
   UNION�ṹ:  CBBP_DLDEC_OVERTIME_CFG_UNION */
#define CBBP_DLDEC_OVERTIME_CFG_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x404C)

/* �Ĵ���˵����
 bit[31:17]  ����
 bit[16]     Turbo������CRC��ȷ��ǰֹͣ����ʹ��0����ֹ
             1��ʹ��
             
 bit[15:13]  ����
 bit[12:8]   Turbo����������������������ó�16�������16�δ��������Ƿ�������ֹͣ������
 bit[7:4]    ����
 bit[3:0]    Turbo�������С����������������ó�9����������Ҫ9�δ���Ż�ֹͣ����
   UNION�ṹ:  CBBP_TURBO_ITER_NUM_C_UNION */
#define CBBP_TURBO_ITER_NUM_C_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x4050)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:24]  16��scale���ӣ�ÿ������λ��6bit
             SISO1��sf[i]=sf[2i-2]����1<=i<=8���� sf[i]=sf[14]����9<=i<=16��������iΪ��������
             SISO2�� sf[i]=sf[2i-1]����1<=i<=8���� sf[i]=sf[15]����9<=i<=16��������iΪ��������
 bit[23:22]  ����
 bit[21:16]  16��scale���ӣ�ÿ������λ��6bit
             SISO1��sf[i]=sf[2i-2]����1<=i<=8���� sf[i]=sf[14]����9<=i<=16��������iΪ��������
             SISO2�� sf[i]=sf[2i-1]����1<=i<=8���� sf[i]=sf[15]����9<=i<=16��������iΪ��������
 bit[15:14]  ����
 bit[13:8]   16��scale���ӣ�ÿ������λ��6bit
             SISO1��sf[i]=sf[2i-2]����1<=i<=8���� sf[i]=sf[14]����9<=i<=16��������iΪ��������
             SISO2�� sf[i]=sf[2i-1]����1<=i<=8���� sf[i]=sf[15]����9<=i<=16��������iΪ��������
 bit[7:6]    ����
 bit[5:0]    16��scale���ӣ�ÿ������λ��6bit
             SISO1��sf[i]=sf[2i-2]����1<=i<=8���� sf[i]=sf[14]����9<=i<=16��������iΪ��������
             SISO2�� sf[i]=sf[2i-1]����1<=i<=8���� sf[i]=sf[15]����9<=i<=16��������iΪ��������
   UNION�ṹ:  CBBP_TURBO_SCALE_1_4_C_UNION */
#define CBBP_TURBO_SCALE_1_4_C_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x4054)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:24]  16��scale���ӣ�ÿ������λ��6bit
             SISO1��sf[i]=sf[2i-2]����1<=i<=8���� sf[i]=sf[14]����9<=i<=16��������iΪ��������
             SISO2�� sf[i]=sf[2i-1]����1<=i<=8���� sf[i]=sf[15]����9<=i<=16��������iΪ��������
 bit[23:22]  ����
 bit[21:16]  16��scale���ӣ�ÿ������λ��6bit
             SISO1��sf[i]=sf[2i-2]����1<=i<=8���� sf[i]=sf[14]����9<=i<=16��������iΪ��������
             SISO2�� sf[i]=sf[2i-1]����1<=i<=8���� sf[i]=sf[15]����9<=i<=16��������iΪ��������
 bit[15:14]  ����
 bit[13:8]   16��scale���ӣ�ÿ������λ��6bit
             SISO1��sf[i]=sf[2i-2]����1<=i<=8���� sf[i]=sf[14]����9<=i<=16��������iΪ��������
             SISO2�� sf[i]=sf[2i-1]����1<=i<=8���� sf[i]=sf[15]����9<=i<=16��������iΪ��������
 bit[7:6]    ����
 bit[5:0]    16��scale���ӣ�ÿ������λ��6bit
             SISO1��sf[i]=sf[2i-2]����1<=i<=8���� sf[i]=sf[14]����9<=i<=16��������iΪ��������
             SISO2�� sf[i]=sf[2i-1]����1<=i<=8���� sf[i]=sf[15]����9<=i<=16��������iΪ��������
   UNION�ṹ:  CBBP_TURBO_SCALE_5_8_C_UNION */
#define CBBP_TURBO_SCALE_5_8_C_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x4058)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:24]  16��scale���ӣ�ÿ������λ��6bit
             SISO1��sf[i]=sf[2i-2]����1<=i<=8���� sf[i]=sf[14]����9<=i<=16��������iΪ��������
             SISO2�� sf[i]=sf[2i-1]����1<=i<=8���� sf[i]=sf[15]����9<=i<=16��������iΪ��������
 bit[23:22]  ����
 bit[21:16]  16��scale���ӣ�ÿ������λ��6bit
             SISO1��sf[i]=sf[2i-2]����1<=i<=8���� sf[i]=sf[14]����9<=i<=16��������iΪ��������
             SISO2�� sf[i]=sf[2i-1]����1<=i<=8���� sf[i]=sf[15]����9<=i<=16��������iΪ��������
 bit[15:14]  ����
 bit[13:8]   16��scale���ӣ�ÿ������λ��6bit
             SISO1��sf[i]=sf[2i-2]����1<=i<=8���� sf[i]=sf[14]����9<=i<=16��������iΪ��������
             SISO2�� sf[i]=sf[2i-1]����1<=i<=8���� sf[i]=sf[15]����9<=i<=16��������iΪ��������
 bit[7:6]    ����
 bit[5:0]    16��scale���ӣ�ÿ������λ��6bit
             SISO1��sf[i]=sf[2i-2]����1<=i<=8���� sf[i]=sf[14]����9<=i<=16��������iΪ��������
             SISO2�� sf[i]=sf[2i-1]����1<=i<=8���� sf[i]=sf[15]����9<=i<=16��������iΪ��������
   UNION�ṹ:  CBBP_TURBO_SCALE_9_12_C_UNION */
#define CBBP_TURBO_SCALE_9_12_C_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x405C)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:24]  16��scale���ӣ�ÿ������λ��6bit
             SISO1��sf[i]=sf[2i-2]����1<=i<=8���� sf[i]=sf[14]����9<=i<=16��������iΪ��������
             SISO2�� sf[i]=sf[2i-1]����1<=i<=8���� sf[i]=sf[15]����9<=i<=16��������iΪ��������
 bit[23:22]  ����
 bit[21:16]  16��scale���ӣ�ÿ������λ��6bit
             SISO1��sf[i]=sf[2i-2]����1<=i<=8���� sf[i]=sf[14]����9<=i<=16��������iΪ��������
             SISO2�� sf[i]=sf[2i-1]����1<=i<=8���� sf[i]=sf[15]����9<=i<=16��������iΪ��������
 bit[15:14]  ����
 bit[13:8]   16��scale���ӣ�ÿ������λ��6bit
             SISO1��sf[i]=sf[2i-2]����1<=i<=8���� sf[i]=sf[14]����9<=i<=16��������iΪ��������
             SISO2�� sf[i]=sf[2i-1]����1<=i<=8���� sf[i]=sf[15]����9<=i<=16��������iΪ��������
 bit[7:6]    ����
 bit[5:0]    16��scale���ӣ�ÿ������λ��6bit
             SISO1��sf[i]=sf[2i-2]����1<=i<=8���� sf[i]=sf[14]����9<=i<=16��������iΪ��������
             SISO2�� sf[i]=sf[2i-1]����1<=i<=8���� sf[i]=sf[15]����9<=i<=16��������iΪ��������
   UNION�ṹ:  CBBP_TURBO_SCALE_13_16_C_UNION */
#define CBBP_TURBO_SCALE_13_16_C_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x4060)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      1����ʾEVDO HARQ�ϲ�����������1λ�ٱ�����6λ������ֱ�ӱ�����6λ��
   UNION�ṹ:  CBBP_HARQ_COMB_SHIFT_IND_UNION */
#define CBBP_HARQ_COMB_SHIFT_IND_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x4064)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    LLR�·���������ָʾ��0����ʾSDR�������·��Ľ����LLR��Ϣ��1����ʾ1Xģʽ����ɽ⽻֯���׽��ظ����LLR��Ϣ��Ҳ��VTB����ǰLLR��Ϣ��2����ʾEVDOģʽ��ĳ�����̵�HARQ���LLR��Ϣ������ϢͬʱҲ������TURBO����ǰ��LLR��Ϣ����
             
   UNION�ṹ:  CBBP_DLDEC_WR_LLR_ORIG_UNION */
#define CBBP_DLDEC_WR_LLR_ORIG_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x4068)

/* �Ĵ���˵����
 bit[31:5]   ����
 bit[4:0]    ����ǰLLR�·�ˮ�ߣ�Ҳ���·�LLRʱ��burst���ͣ���֧������Ϊ1����������Ϊ2/4/8/16������16����ʾLLR�·�Ϊburst16����,DMA����λ�����Ϊ64��
   UNION�ṹ:  CBBP_DLDEC_WR_WATERLINE_UNION */
#define CBBP_DLDEC_WR_WATERLINE_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x406C)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    LLR�ϱ���������ָʾ��0����ʾSDR�������ϱ������LLR��Ϣ��1����ʾEVDOģʽ���ϱ�ĳ�����̵�HARQ���LLR��Ϣ������ϢͬʱҲ������TURBO����ǰ��LLR��Ϣ����2����ʾ1Xģʽ����ɽ⽻֯���׽��ظ����LLR��Ϣ�ϱ���
   UNION�ṹ:  CBBP_DLDEC_RD_LLR_ORIG_UNION */
#define CBBP_DLDEC_RD_LLR_ORIG_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x4070)

/* �Ĵ���˵����
 bit[31:5]   ����
 bit[4:0]    LLR�ض�ˮ�ߣ�Ҳ���ض�ʱ����burst���ͣ���֧������Ϊ1����������Ϊ2/4/8/16������16����ʾLLR�ض�Ϊburst16���ͣ�DMA����λ�����Ϊ64��
   UNION�ṹ:  CBBP_DLDEC_RD_WATERLINE_UNION */
#define CBBP_DLDEC_RD_WATERLINE_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x4074)

/* �Ĵ���˵����
 bit[31:21]  ����
 bit[20]     DMA������״̬�ϱ�
 bit[19:17]  ����
 bit[16]     DMAд����״̬�ϱ�
 bit[15:13]  ����
 bit[12]     �ض�LLRͨ����״̬�ϱ�
 bit[11:9]   ����
 bit[8]      �ض�LLRͨ����״̬�ϱ�
 bit[7:5]    ����
 bit[4]      �·�LLRͨ����״̬�ϱ�
 bit[3:1]    ����
 bit[0]      �·�LLRͨ����״̬�ϱ�
   UNION�ṹ:  CBBP_LLR_TRANS_FLAG_UNION */
#define CBBP_LLR_TRANS_FLAG_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x407C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ����bler��ά�ɲ�ͳ��ʹ��
   UNION�ṹ:  CBBP_BLER_ENABLE_UNION */
#define CBBP_BLER_ENABLE_ADDR                         (SOC_BBP_CDMA_BASE_ADDR + 0x4080)

/* �Ĵ���˵����
   ��      �����������ͳ��
   UNION�ṹ ���� */
#define CBBP_DLDEC_DEC_TOTAL_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x4084)

/* �Ĵ���˵����
   ��      ��������CRC����������ͳ��
   UNION�ṹ ���� */
#define CBBP_DLDEC_DEC_CRC_NOK_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x4088)

/* �Ĵ���˵����
   ��      ����������ɺ��ϱ��жϸ���ͳ��
   UNION�ṹ ���� */
#define CBBP_DLDEC_RPT_INT_NUM_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x408C)

/* �Ĵ���˵����
 bit[31:9]   ����
 bit[8]      vtb����æ��־
 bit[7:5]    ����
 bit[4]      ���볬ʱ��־
 bit[3:0]    ����״̬���ϱ�
   UNION�ṹ:  CBBP_DLDEC_STATE_UNION */
#define CBBP_DLDEC_STATE_ADDR                         (SOC_BBP_CDMA_BASE_ADDR + 0x4090)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      LLR�·���������ָʾ��Ϊ1��ʾ8λLLR��������1λ�ٱ�����6λ��Ϊ0��ʾֱ�ӽ�ȡ��6λ�������LLR�״��·�������Ҫ����Ϊ1������ǻض�ǰ�������LLRֵ����Ϊ�Ѿ���6λ�����ٴ��·�ʱ����Ҫ������ʱ����Ϊ0��
   UNION�ṹ:  CBBP_LLR_CLIP_IND_UNION */
#define CBBP_LLR_CLIP_IND_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0x4094)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      �ظ�ģʽѡ��0��ʾFIX DATA RATE�ظ�ģʽ��1��ʾflexible�ظ�ģʽ��
   UNION�ṹ:  CBBP_DLDEC_REPEAT_MODE_UNION */
#define CBBP_DLDEC_REPEAT_MODE_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x4098)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      LLR�ض��������壬ֻ����������ɺ��������״̬ʱ�ſ����á�Ѱ���ŵ���ͬ���ŵ��������жϺ����á�
   UNION�ṹ:  CBBP_DLDEC_LLR_RD_START_UNION */
#define CBBP_DLDEC_LLR_RD_START_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x409C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      EVDO�����ָʾ��1��ʾ�����Ϊ�����ݣ�0����ʾ������
   UNION�ṹ:  CBBP_DLDEC_NEW_BLK_IND_UNION */
#define CBBP_DLDEC_NEW_BLK_IND_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x40A0)

/* �Ĵ���˵����
 bit[31:5]   ����
 bit[4]      reserve�����ϱ�ʹ�ܣ�1��ʾ�ϱ�reserve���أ�0��ʾ���ϱ�
 bit[3:1]    ����
 bit[0]      �ϱ�ģʽ��1��ʾС��ģʽ��0��ʾ���ģʽ
   UNION�ṹ:  CBBP_RPT_MODE_UNION */
#define CBBP_RPT_MODE_ADDR                            (SOC_BBP_CDMA_BASE_ADDR + 0x40A4)

/* �Ĵ���˵����
 bit[31:13]  ����
 bit[12:0]   ����·�LLR������Ϊʵ��LLR��������4��������ȡ����
   UNION�ṹ:  CBBP_DLDEC_WR_LENGTH_UNION */
#define CBBP_DLDEC_WR_LENGTH_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x40AC)

/* �Ĵ���˵����
 bit[31:13]  ����
 bit[12:0]   ����ض�LLR������Ϊʵ��LLR��������4��������ȡ����
   UNION�ṹ:  CBBP_DLDEC_RD_LENGTH_UNION */
#define CBBP_DLDEC_RD_LENGTH_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x40B0)

/* �Ĵ���˵����
 bit[31]     CRCУ�����ϱ�
 bit[30:24]  ����
 bit[23:0]   CRCУ������ϱ�
   UNION�ṹ:  CBBP_CRC_RPT_UNION */
#define CBBP_CRC_RPT_ADDR                             (SOC_BBP_CDMA_BASE_ADDR + 0x40B4)

/* �Ĵ���˵����
 bit[31:5]   ����
 bit[4]      ����ģʽʱ�������ͨ��DMA��ֱ��ͨ�����߶�ȡLLR��ֵ��1��ʾ��һ��BURST��LLR���Զ�ȡ��0����ʾû��LLR�ɶ�ȡ��
 bit[3:1]    ����
 bit[0]      ����ģʽʱ�������ͨ��DMA��ֱ��ͨ�������·�LLR��ֵ��1��ʾ��һ��BURST��LLR�����·���0����ʾLLR�����·���
   UNION�ṹ:  CBBP_LLR_READY_UNION */
#define CBBP_LLR_READY_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0x40B8)

/* �Ĵ���˵����
 bit[31:5]   ����
 bit[4]      ����ģʽʱ������ɲ�ͨ��DMA��ֱ��ͨ�����߶�ȡLLR��ֵ��������һ��burst����ʱ������������,��dldec_llr_rd_ready��0
 bit[3:1]    ����
 bit[0]      ����ģʽʱ������ɲ�ͨ��DMA��ֱ��ͨ�������·�LLR��ֵ�����·���һ��burst����ʱ�������������壬��dldec_llr_wr_ready_clr��0
   UNION�ṹ:  CBBP_LLR_READY_CLR_UNION */
#define CBBP_LLR_READY_CLR_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0x40BC)

/* �Ĵ���˵����
 bit[31:8]   ����
 bit[7:0]    vtb״̬�ϱ���������һ��vtb����״̬������ʼ�����ڱ��������жϺ��´���������ǰ��Ч��
   UNION�ṹ:  CBBP_C_VTB_ST_RPT_UNION */
#define CBBP_C_VTB_ST_RPT_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0x40C0)

/* �Ĵ���˵����
 bit[31:12]  ����
 bit[11:0]   ä����HARQ�ش�ʱturbo����ǰ���ݵ�ƫ�Ƶ�ַ��HARQ�ش�ʱ�����ݽ��̺ż��㣬����0����ʱ���õ�ַ����Ϊ0������n��������Ϊ641*n��֧�����4�����̡�ä���ʱ������ʵ��LLR���ݳ��ȼ��㡣
   UNION�ṹ:  CBBP_C2TUBO_BASE_ADDR_UNION */
#define CBBP_C2TUBO_BASE_ADDR_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x40C4)

/* �Ĵ���˵����
 bit[31:9]   ����
 bit[8:0]    ʱ���ſ���·ʹ��
   UNION�ṹ:  CBBP_DLDEC_CKG_BYPASS_UNION */
#define CBBP_DLDEC_CKG_BYPASS_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x40C8)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      BERͳ��ʹ��
   UNION�ṹ:  CBBP_DLDEC_BER_EN_UNION */
#define CBBP_DLDEC_BER_EN_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0x40CC)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ���ظ���Ϊ1ʱ��berͳ����Ҫ������λ�ã���ʱ�����ź���1��������0��
   UNION�ṹ:  CBBP_DLDEC_RFPUN_EN_UNION */
#define CBBP_DLDEC_RFPUN_EN_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x40D0)

/* �Ĵ���˵����
 bit[31:13]  ����
 bit[12:0]   ���ʱ���Ҵ�·������ֵ����״̬����ֵ֮��
   UNION�ṹ:  CBBP_C_BLID_CM0_UNION */
#define CBBP_C_BLID_CM0_ADDR                          (SOC_BBP_CDMA_BASE_ADDR + 0x40D4)

/* �Ĵ���˵����
 bit[31:13]  ����
 bit[12:0]   ���ʱ���Ҵ�·������ֵ�����·������ֵ֮��
   UNION�ṹ:  CBBP_C_BLID_CM1_UNION */
#define CBBP_C_BLID_CM1_ADDR                          (SOC_BBP_CDMA_BASE_ADDR + 0x40D8)

/* �Ĵ���˵����
 bit[31:13]  ����
 bit[12:0]   Cģä�������ʱ�̴���·������ֵ�ϱ�
   UNION�ṹ:  CBBP_C_BLID_CM2_UNION */
#define CBBP_C_BLID_CM2_ADDR                          (SOC_BBP_CDMA_BASE_ADDR + 0x40DC)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ä���BER����bit��ͳ�ƽ��
   UNION�ṹ:  CBBP_DLDEC_BER_UNION */
#define CBBP_DLDEC_BER_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0x40E0)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ä�������ͳ��BER���ܱ�����
   UNION�ṹ:  CBBP_DLDEC_TOTAL_BERBIT_UNION */
#define CBBP_DLDEC_TOTAL_BERBIT_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x40E4)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      byte�ڴ�С��ָʾ��0��ʾС��ģʽ����byte�����λ�ŵ�λ���ݡ�1��ʾ���ģʽ��byte�����λ�����λ���ݡ�
   UNION�ṹ:  CBBP_BIT_ORDER_REVERSE_UNION */
#define CBBP_BIT_ORDER_REVERSE_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x40E8)

/* �Ĵ���˵����
 bit[31:5]   ����
 bit[4]      Wģ��turbo�����������жϷ������л����أ�Ĭ�ϴ�
             0���Ƚ��������εĵ�����������һ������Ϊ������
             1���Ƚ��������εĵ�����������һ������Ϊ������
 bit[3:1]    ����
 bit[0]      Wģ��Turbo��������ǰֹͣ����ʹ��0����ֹ
             1��ʹ��
             
   UNION�ṹ:  CBBP_TURBO_ITER_NUM_W_SDR_UNION */
#define CBBP_TURBO_ITER_NUM_W_SDR_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x40EC)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      1X��EVDOʱä���ָʾ��1��ʾ��ǰ�����Ҫ����ä�������
   UNION�ṹ:  CBBP_BLIND_DETECT_IND_UNION */
#define CBBP_BLIND_DETECT_IND_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x40F0)

/* �Ĵ���˵����
   ��      ������ʱ�������ϱ�
   UNION�ṹ ���� */
#define CBBP_DLDEC_OVERTIME_CB_CNT_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x40F4)

/* �Ĵ���˵����
 bit[31:5]   ����
 bit[4]      CPUֱ���·�LLRģʽ����ʱ��ͨ��DMA�·����ݣ�BBP DMA�������ߡ�
 bit[3:1]    ����
 bit[0]      CPUֱ�Ӷ�ȡLLRģʽ����ʱ��ͨ��DMA��ȡ���ݣ�BBP DMA�������ߡ�
   UNION�ṹ:  CBBP_CPU_ACCESS_LLR_MODE_UNION */
#define CBBP_CPU_ACCESS_LLR_MODE_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x40F8)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    LLR�����·�ģʽָʾ:0����ʾDMA burst�·�ģʽ��1����ʾDMA FLASHģʽ��2����ʾBBPMSTģʽ��
             DMA FLASHģʽ��BBPMSTģʽ��֧�ִ�TURBO LLR�����·���
   UNION�ṹ:  CBBP_LLR_TRANS_MODE_UNION */
#define CBBP_LLR_TRANS_MODE_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x40FC)



/***======================================================================***
                     (11/20) register_define_c_dldec_mem
 ***======================================================================***/
/* �Ĵ���˵����C�ϱ�����RAM
   ��      ����Cģ�����ϱ�������RAM�����Ϊ194��λ��Ϊ32bit��ÿ��32λ�ϱ�ֵռ�õ�ַ�ռ�һ����ַ�����ϱ�ֵ0��ַΪ0x5000���ϱ�ֵ1��ַΪ0x5004���������������ƣ��ϱ�ֵ193��ַΪ0x5304��
   UNION�ṹ ���� */
#define CBBP_C_RPT_DATA_RAM_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x5000)
#define CBBP_C_RPT_DATA_RAM_MEMDEPTH  (194)

/* �Ĵ���˵����LLR�·�FIFO
   ��      ����CģLLR�·�FIFOд���ݣ�ÿ��DMA���˷������ʸõ�ַд��һ���������ݡ�
   UNION�ṹ ���� */
#define CBBP_C_WR_LLR_FIFO_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0x5400)

/* �Ĵ���˵����LLR�ϱ�FIFO
   ��      ����CģLLR�ض�FIFO�����ݣ�ÿ��DMA���˷������ʸõ�ַ����һ���������ݡ�
   UNION�ṹ ���� */
#define CBBP_C_RD_LLR_FIFO_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0x5408)



/***======================================================================***
                     (12/20) register_define_c_ulcode
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ���б���ģ��ʹ�ܣ��������������б������������ɺ�����Ϊ1��
   UNION�ṹ:  CBBP_ULCODE_EN_UNION */
#define CBBP_ULCODE_EN_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0xB000)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ���б��������źţ��������������б�����������б��뽨��ʹ��������ɺ�����
   UNION�ṹ:  CBBP_ULCODE_START_UNION */
#define CBBP_ULCODE_START_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0xB004)

/* �Ĵ���˵����
 bit[31:17]  ����
 bit[16]     ���������·�С�˱��������ʽ��1����ʾС�˱�������ģʽ��Ч��0����ʾС�˱�������ģʽ��Ч��Ĭ��ֵ��0��
             ���������·�С�˱�������ģʽ��С��ģʽ����ͬʱ��Ч�������öԱ���������ϱ���ʽ��Ӱ�졣
 bit[15:1]   ����
 bit[0]      ���������·���ʽ�ͱ���������ϱ���ʽ��1����ʾС��ģʽ��Ĭ��ģʽ����0����ʾ���ģʽ��Ĭ��ֵ��1��
   UNION�ṹ:  CBBP_ULCODE_BIT_MODE_UNION */
#define CBBP_ULCODE_BIT_MODE_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xB008)

/* �Ĵ���˵����
 bit[31:17]  ����
 bit[16]     Reverse bit��ȡֵ��ȡֵ0��1��
 bit[15:1]   ����
 bit[0]      1Xģʽ��Reverse bit���ʹ�ܿ��أ�EVDOģʽ�¸ò�������Ϊ0��
   UNION�ṹ:  CBBP_ULCODE_RESERVE_BIT_UNION */
#define CBBP_ULCODE_RESERVE_BIT_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0xB00C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ͨ��ģʽ����ָʾ��1��EVDO��0:1X��Ĭ��ֵ��0��
   UNION�ṹ:  CBBP_ULCODE_TRAFFIC_TYPE_UNION */
#define CBBP_ULCODE_TRAFFIC_TYPE_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0xB010)

/* �Ĵ���˵����
 bit[31:19]  ����
 bit[18:16]  ���б����������ʣ�
             2��1/2��
             3��1/3��
             4��1/4��
             5��1/5�������������1/5����
 bit[15:1]   ����
 bit[0]      ����������ָʾ��1��TURBO��0:VTB��
             Ĭ��ֵ��0��
   UNION�ṹ:  CBBP_ULCODE_CODER_PARA_UNION */
#define CBBP_ULCODE_CODER_PARA_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xB014)

/* �Ĵ���˵����
 bit[31:14]  ����
 bit[13:0]   ��Ϣλ���ȣ�
             ��������²���CRC��Reverse bit��TAIL bit ���ȣ�TURBO�����²�����00����CRC��Reverse bit��TAIL bit ���ȡ�
   UNION�ṹ:  CBBP_ULCODE_LEN_PARA1_UNION */
#define CBBP_ULCODE_LEN_PARA1_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0xB018)

/* �Ĵ���˵����
 bit[31:17]  ����
 bit[16]     CRC�Ĵ�����ʼ��ֵ��1��ȫ1��0��ȫ0��
             Ĭ��ֵ��0��
 bit[15:4]   ����
 bit[3:0]    CRCУ�����ͣ�
             0:CRC-0��
             1:CRC-16-1��
             2:CRC-12��
             3:CRC-10��
             4:CRC-8��
             5:CRC-6-1��
             6:CRC-6-2��
             7:CRC-24��
             8:CRC-16-2��
             Ĭ��ֵ��0��
   UNION�ṹ:  CBBP_ULCODE_CRC_PARA_UNION */
#define CBBP_ULCODE_CRC_PARA_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xB01C)

/* �Ĵ���˵����
 bit[31:17]  ����
 bit[16:0]   ������������ࣻ
             SDR����������EVDOЭ�鶨����������������ø����б���ģ�顣
             1X�¹̶�����Ϊȫ0��
   UNION�ṹ:  CBBP_ULCODE_SCR_INIT_UNION */
#define CBBP_ULCODE_SCR_INIT_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xB020)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    ��֯������ģʽ��
             0�� Matrix Interleave��֯��
             1�� Symbol Permuting��֯��
             2������TYPE1 Block Interleave��֯��
             3������TYPE2 Block Interleave��֯��
             4������TYPE3 Block Interleave��֯��
             5������TYPE1 Block Interleave��֯��
             6������TYPE2 Block Interleave��֯��
             7������Reverse Interleave��
   UNION�ṹ:  CBBP_ULCODE_INTL_MODE_UNION */
#define CBBP_ULCODE_INTL_MODE_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0xB024)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:24]  ����Matrix Interleave��֯������EVDOʹ�ã�D��������������������󣩡�
 bit[23:19]  ����
 bit[18:16]  ����Matrix Interleave��֯������EVDOʹ�ã�R������
 bit[15:12]  ����
 bit[11:8]   ����Matrix Interleave��֯������EVDOʹ�ã�M������V0/V0`��V1/V1`Ӳ��ʹ��ʱ���м�1����
 bit[7:3]    ����
 bit[2:0]    ����Matrix Interleave��֯������EVDOʹ�ã�K������
   UNION�ṹ:  CBBP_ULCODE_MATRIX_PARA_UNION */
#define CBBP_ULCODE_MATRIX_PARA_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0xB028)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    ����Reverse Interleave ��֯������EVDOʹ�ã�m������
             ��ֵ��ʾʵ�ʲ�������λ�������
   UNION�ṹ:  CBBP_ULCODE_REVERSE_PARA_UNION */
#define CBBP_ULCODE_REVERSE_PARA_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0xB02C)

/* �Ĵ���˵����
 bit[31:24]  ����Block Interleave��֯������1Xʹ�ã�j������
 bit[23:20]  ����
 bit[19:16]  ����Block Interleave��֯������1Xʹ�ã�m������
 bit[15:2]   ����
 bit[1:0]    ����TYPE1 Block Interleave��֯ӳ���ѡ��
             0��At 9600 or 14400 bps 
             1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32
             1��At 4800 or 7200 bps 
             1 3 2 4 5 7 6 8 9 11 10 12 13 15 14 16 17 19 18 20 21 23 22 24 25 27 26 28 29 31 30 32
             2��At 2400 or 3600 bps 
             1 5 2 6 3 7 4 8 9 13 10 14 11 15 12 16 17 21 18 22 19 23 20 24 25 29 26 30 27 31 28 32
             3��At 1200 or 1800 bps 
             1 9 2 10 3 11 4 12 5 13 6 14 7 15 8 16 17 25 18 26 19 27 20 28 21 29 22 30 23 31 24 32
   UNION�ṹ:  CBBP_ULCODE_BLOCK_PARA_UNION */
#define CBBP_ULCODE_BLOCK_PARA_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xB030)

/* �Ĵ���˵����
 bit[31:16]  1X��ʹ�ã�1X�¼���Э�鶨���Symbol Repeation�󳤶ȣ�EVDO����Ӳ�����м���õ���
 bit[15:0]   1X�����ŵ���֯���ȣ�EVDO����Ӳ����������õ���
   UNION�ṹ:  CBBP_ULCODE_LEN_PARA2_UNION */
#define CBBP_ULCODE_LEN_PARA2_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0xB034)

/* �Ĵ���˵����
 bit[31:25]  ����
 bit[24:0]   1X��ʹ�ã�1X���޴��������ȫ1���д�װ���ʵ�ʵ�ͼ�����ã�EVDO��Ӳ���̶�ʹ��ȫ1ͼ����
   UNION�ṹ:  CBBP_ULCODE_PUNC_PATTERN_UNION */
#define CBBP_ULCODE_PUNC_PATTERN_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0xB038)

/* �Ĵ���˵����
 bit[31:21]  ����
 bit[20:16]  Symbol Puncture���ͼ����Ч���ȣ�
             5,9,12,18,24,25���Ǵ��ͼ��һ��ѭ����������Чָʾbit����
 bit[15:2]   ����
 bit[1:0]    ���ģʽ��
             0�� ���ݴ��ͼ�����������Ϣ������ERAMģʽ����Ҫͨ�����ͼ�����������Ϣ�ĳ�������
             1����ERAMģʽ�£����ݹ�ʽ��������Ϣ��
             2��ERAMģʽ�£����ݹ�ʽ��������Ϣ��
             
   UNION�ṹ:  CBBP_ULCODE_PUNC_PATTERN_LEN_UNION */
#define CBBP_ULCODE_PUNC_PATTERN_LEN_ADDR             (SOC_BBP_CDMA_BASE_ADDR + 0xB03C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0:0]    �ظ�ģʽ��
             0��Fix Data Rateģʽ��symbol repeat����ģʽ��
             1��Variable��Flexible Data Rateģʽ�� symbol repeat����ģʽ��
   UNION�ṹ:  CBBP_ULCODE_REPEAT_MODE_UNION */
#define CBBP_ULCODE_REPEAT_MODE_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0xB040)

/* �Ĵ���˵����
 bit[31:5]   ����
 bit[4:0]    ����ģ�鳬ʱ��������ֵ��0ֵ�������ã�ʵ�ʳ�ʱ����ֵΪulcod_overtime_cfg*8192���Ƽ�����ֵΪ15����̬��
   UNION�ṹ:  CBBP_ULCODE_OVERTIME_CFG_UNION */
#define CBBP_ULCODE_OVERTIME_CFG_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0xB044)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ���б���ͳ�Ƽ���ʹ�ܡ�
   UNION�ṹ:  CBBP_ULCODE_TIMES_EN_UNION */
#define CBBP_ULCODE_TIMES_EN_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xB048)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      æ�����״̬�ϱ���
             0���� 1��æ��
   UNION�ṹ:  CBBP_ULCODE_CODER_STATUS_UNION */
#define CBBP_ULCODE_CODER_STATUS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0xB04C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��ʾ����������̳�ʱ��
   UNION�ṹ:  CBBP_ULCODE_OVERTIME_FLAG_UNION */
#define CBBP_ULCODE_OVERTIME_FLAG_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0xB050)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    ���б���״̬�ϱ���
   UNION�ṹ:  CBBP_ULCODE_STATE_UNION */
#define CBBP_ULCODE_STATE_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0xB054)

/* �Ĵ���˵����
 bit[31:16]  �������������ϱ�����λ���㡣
 bit[15:0]   �����жϴ����ϱ�����λ���㡣
   UNION�ṹ:  CBBP_ULCODE_TIMES_UNION */
#define CBBP_ULCODE_TIMES_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0xB058)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    ���б�����Ʋ���ʱ���ſ�bypass
             [0]:CRCģ���ſ�bypass
             [1]:CODģ���ſ�bypass
             [2]:RMģ���ſ�bypass
             [3]:INTLģ���ſ�bypass
             0����ʾʱ���ſ���Ч��
             1����ʾʱ�ӳ�����
   UNION�ṹ:  CBBP_ULCODE_CKG_UNION */
#define CBBP_ULCODE_CKG_ADDR                          (SOC_BBP_CDMA_BASE_ADDR + 0xB05C)



/***======================================================================***
                     (13/20) register_define_c_ulcode_mem
 ***======================================================================***/
/* �Ĵ���˵�������б����ϱ�RAM
   ��      �������б����ϱ�RAMͨ��CPU�ӿ��ϱ������б����ϱ�RAM���Ϊ1281��λ��32bit��ÿ���ϱ���ռ�õ�ַ�ռ�һ����ַ���׵�ַΪ0x8000���������ƣ�β��ַΪ0x9400��
            0x8000��bit[15:0]�ϱ���������ݳ��ȣ�bit[31:16]�����塣
            0x8004~0x9400Ϊ�ϱ���������ݡ�
   UNION�ṹ ���� */
#define CBBP_ULCOD_RPT_RAM_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0x8000)
#define CBBP_ULCOD_RPT_RAM_MEMDEPTH  (1281)

/* �Ĵ���˵�������б����·�RAM
   ��      �������б������������ͨ��CPU�ӿ��·��������·�RAM�����б����·�RAM���Ϊ384��λ��32bit��ÿ����ռ�õ�ַ�ռ�һ����ַ���׵�ַΪ0xA000���������ƣ�β��ַΪ0xA5FC��
   UNION�ṹ ���� */
#define CBBP_ULCOD_CODEC_RAM_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xA000)
#define CBBP_ULCOD_CODEC_RAM_MEMDEPTH  (384)



/***======================================================================***
                     (14/20) register_define_c_fe_sdr_if
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31:29]  ����
 bit[28]     ����DMA����ģʽ��0��һ��burst�������32x32bit��1��һ��burst�������16x32bit��
 bit[27:25]  ����
 bit[24]     ���а���ģʽ��0��DMA��ʽ��1��BBPMaster��ʽ��
 bit[23:21]  ����
 bit[20]     ����SDR IFģ�����ֹͣģʽ��0������ֹͣ���������ֹͣ���ˣ�1���ﵽcpu_dlfe_sdr_data_length����İ������������Զ�ֹͣ���ˡ�
 bit[19:17]  ����
 bit[16]     ����SDR IFģ���������ģʽ��0��������������������������ˣ�1���������������cpu_dlfe_sdr_start_time�����ʱ���������ˡ�
             �ò�������Gģ��ʱ��Ч��
 bit[15:13]  ����
 bit[12]     ����SDR IFģ����շּ�ģʽ��0���ǽ��շּ���1�����շּ���
 bit[11:10]  ����
 bit[9:8]    ����SDR IFģ�鹤��ģʽ��0��1��ʾ��Cģ��2��ʾ1X��3��ʾEVDO��
             �ò�������Cģʱ��Ч��
 bit[7:5]    ����
 bit[4]      ����SDR IFģ�������ͣģʽ��0�����ּ�����������ͣ�źţ�1�����ּ��ø�����ͣ�źš�
 bit[3:1]    ����
 bit[0]      ����SDR IFģ��ʹ�ܣ��ߵ�ƽ��Ч��
   UNION�ṹ:  CBBP_DLFE_SDR_EN_UNION */
#define CBBP_DLFE_SDR_EN_ADDR                         (SOC_BBP_CDMA_BASE_ADDR + 0xE000)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ���а���ʱ���ſ�bypass�źţ��ߵ�ƽ��Ч����ʾʱ�ӳ�����
   UNION�ṹ:  CBBP_DLFE_SDR_CKG_BYS_UNION */
#define CBBP_DLFE_SDR_CKG_BYS_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0xE004)

/* �Ĵ���˵����
 bit[31:29]  ����
 bit[28]     ���зּ�BBPMaster���˸�λ���塣
 bit[27:25]  ����
 bit[24]     ���зּ�����ǿ��ֹͣ���塣�ڼ�⵽���зּ����˳�������á�
 bit[23:21]  ����
 bit[20]     ���зּ�����ֹͣ���塣
 bit[19:17]  ����
 bit[16]     ���зּ������������塣
 bit[15:13]  ����
 bit[12]     ��������BBPMaster���˸�λ���塣
 bit[11:9]   ����
 bit[8]      ������������ǿ��ֹͣ���塣�ڼ�⵽�����������˳�������á�
 bit[7:5]    ����
 bit[4]      ������������ֹͣ���塣
 bit[3:1]    ����
 bit[0]      �������������������塣
   UNION�ṹ:  CBBP_DLFE_SDR_START_STOP_UNION */
#define CBBP_DLFE_SDR_START_STOP_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0xE008)

/* �Ĵ���˵����
 bit[31:27]  ����
 bit[26:16]  ����ʱ϶ͷ���sys_cntʱ϶�߽����ǰ������λchip��
             �ò�������Cģʱ��Ч��
 bit[15:12]  ����
 bit[11:0]   ����Buffer��ȣ���λ32word�����ڼ���Buffer�׵�ַ��ʱ�����
             Cģ��Uģ��ʱ��һ��word��Ӧһ��chip��Gģ��ʱ��һ��word��Ӧһ��Qb��
   UNION�ṹ:  CBBP_DLFE_SDR_OFFSET_BUFF_DEPTH_UNION */
#define CBBP_DLFE_SDR_OFFSET_BUFF_DEPTH_ADDR          (SOC_BBP_CDMA_BASE_ADDR + 0xE00C)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  ���а�������������λ32word��
             �ò�������cpu_dlfe_sdr_stop_modeΪ1ʱ��Ч��
 bit[15:13]  ����
 bit[12:0]   Gģ��ʱ��gtc_timebase�ϵİ�������ʱ�̣���λQb����Χ0~4999��
   UNION�ṹ:  CBBP_DLFE_SDR_TIME_CTRL_UNION */
#define CBBP_DLFE_SDR_TIME_CTRL_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0xE010)

/* �Ĵ���˵����
 bit[31:16]  ����
 bit[15:0]   ����Buffer��ȣ���λword��
             Cģ��Uģ��ʱ��һ��word��Ӧһ��chip��Gģ��ʱ��һ��word��Ӧһ��Qb��
             ������Gģ��ʱʹ�á�
   UNION�ṹ:  CBBP_DLFE_SDR_WORD_DEPTH_UNION */
#define CBBP_DLFE_SDR_WORD_DEPTH_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0xE014)

/* �Ĵ���˵����
 bit[31:6]   ����
 bit[5:0]    ��������1��ǰ����word����
   UNION�ṹ:  CBBP_DLFE_SDR_AT1_RD_CHIP_RPT_UNION */
#define CBBP_DLFE_SDR_AT1_RD_CHIP_RPT_ADDR            (SOC_BBP_CDMA_BASE_ADDR + 0xE040)

/* �Ĵ���˵����
 bit[31:12]  ��������1��ǰ����ҳ��������cpu_dlfe_sdr_buffer_depthͳ�ơ�
 bit[11:0]   ��������1��ǰ���˿���������cpu_dlfe_sdr_buffer_depthͳ�ơ�
   UNION�ṹ:  CBBP_DLFE_SDR_AT1_RD_RPT_UNION */
#define CBBP_DLFE_SDR_AT1_RD_RPT_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0xE044)

/* �Ĵ���˵����
 bit[31:6]   ����
 bit[5:0]    ��������2��ǰ����word����
   UNION�ṹ:  CBBP_DLFE_SDR_AT2_RD_CHIP_RPT_UNION */
#define CBBP_DLFE_SDR_AT2_RD_CHIP_RPT_ADDR            (SOC_BBP_CDMA_BASE_ADDR + 0xE048)

/* �Ĵ���˵����
 bit[31:12]  ��������2��ǰ����ҳ��������cpu_dlfe_sdr_buffer_depthͳ�ơ�
 bit[11:0]   ��������2��ǰ���˿���������cpu_dlfe_sdr_buffer_depthͳ�ơ�
   UNION�ṹ:  CBBP_DLFE_SDR_AT2_RD_RPT_UNION */
#define CBBP_DLFE_SDR_AT2_RD_RPT_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0xE04C)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:0]   ��������1�������˺��һ�����ݶ�Ӧʱ�����
             Cģʱ���Ϊc_base_cnt����λchip��
             bit[14:0]��������Χ0~32767chip��ʱ�䳤��80/3ms��32768chip����
             bit[16:15]��������Χ0~2��ʱ�䳤��80ms��
             bit[21:17]��������Χ0~24��ʱ�䳤��2s��
             bit[27:22]���̶�Ϊ0��
             Gģ��ʱ���Ϊgtc_tdma_qb�ϵ�֡�ź�gtc_timebase�ϵ�Qb�š�
             bit[12:0]��gtc_timebase�ϵ�֡��Qb������������Χ0~4999Qb��
             bit[23:13]��gtc_tdma_qb�ϵ�fn_low֡������������Χ0~1325֡��
             bit[27:24]���̶�Ϊ0��
             Uģ��ʱ���Ϊbase_cnt��cfn��
             bit[7:0]��symbol��chip������������Χ0~255chip��
             bit[11:8]��slot��symbol������������Χ0~9symbol��
             bit[15:12]��֡��slot������������Χ0~14slot��
             bit[27:16]��cfn��
   UNION�ṹ:  CBBP_DLFE_SDR_AT1_1ST_STAMP_RPT_UNION */
#define CBBP_DLFE_SDR_AT1_1ST_STAMP_RPT_ADDR          (SOC_BBP_CDMA_BASE_ADDR + 0xE050)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:0]   ��������2�������˺��һ�����ݶ�Ӧbase_cntʱ�������λchip��
             ʱ�������ͬ�ϡ�
   UNION�ṹ:  CBBP_DLFE_SDR_AT2_1ST_STAMP_RPT_UNION */
#define CBBP_DLFE_SDR_AT2_1ST_STAMP_RPT_ADDR          (SOC_BBP_CDMA_BASE_ADDR + 0xE054)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:0]   ��������1�������˺�Buffer�׵�ַ���ݶ�Ӧʱ���������ʱ϶ͷ���档
             ʱ�������ͬ�ϡ�
             Cģ1xʱ϶ͷ��PCGͷ��CģEV-DOʱ϶ͷ��ʵ��ʱ϶ͷ��Gģ��ʱ϶ͷ��gtc_tdma_qb�ϵ�burstͷ��Uģ��ʱ϶ͷ��ʵ��ʱ϶ͷ��
   UNION�ṹ:  CBBP_DLFE_SDR_AT1_BUFFER_STAMP_RPT_UNION */
#define CBBP_DLFE_SDR_AT1_BUFFER_STAMP_RPT_ADDR       (SOC_BBP_CDMA_BASE_ADDR + 0xE058)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:0]   ��������2�������˺�Buffer�׵�ַ���ݶ�Ӧʱ���������ʱ϶ͷ���档
             ʱ�������ͬ�ϡ�
             ʱ϶ͷ����ͬ�ϡ�
   UNION�ṹ:  CBBP_DLFE_SDR_AT2_BUFFER_STAMP_RPT_UNION */
#define CBBP_DLFE_SDR_AT2_BUFFER_STAMP_RPT_ADDR       (SOC_BBP_CDMA_BASE_ADDR + 0xE05C)

/* �Ĵ���˵����
   ��      ������������1�������ݡ�
            Cģ��Uģ��ʱ�ɼ�DAGC�����ݣ�һ��word��Ӧһ��chip����ʽ���¡�
            bit[7:0]��chip������0 I·��
            bit[15:8]��chip������0 Q·��
            bit[23:16]��chip������1 I·��
            bit[31:24]��chip������1 Q·��
            Gģ��ʱ�ɼ�AD�����ݣ�һ��word��Ӧһ��Qb����ʽ���¡�
            bit[15:0]��Qb I·��
            bit[31:16]��Qb Q·��
   UNION�ṹ ���� */
#define CBBP_DLFE_SDR_AT1_DATA_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xE060)

/* �Ĵ���˵����
   ��      ������������2�������ݡ�
            Cģ��Uģ��ʱ�ɼ�DAGC�����ݣ�һ��word��Ӧһ��chip����ʽ���¡�
            bit[7:0]��chip������0 I·��
            bit[15:8]��chip������0 Q·��
            bit[23:16]��chip������1 I·��
            bit[31:24]��chip������1 Q·��
            Gģ��ʱ�ɼ�AD�����ݣ�һ��word��Ӧһ��Qb����ʽ���¡�
            bit[15:0]��Qb I·��
            bit[31:16]��Qb Q·��
   UNION�ṹ ���� */
#define CBBP_DLFE_SDR_AT2_DATA_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xE068)

/* �Ĵ���˵����
 bit[31:5]   ����
 bit[4]      ��������1���˳���ָʾ��
 bit[3:1]    ����
 bit[0]      ��������1����״̬��
   UNION�ṹ:  CBBP_DLFE_SDR_AT1_DUMP_EN_RPT_UNION */
#define CBBP_DLFE_SDR_AT1_DUMP_EN_RPT_ADDR            (SOC_BBP_CDMA_BASE_ADDR + 0xE070)

/* �Ĵ���˵����
 bit[31:5]   ����
 bit[4]      ��������2���˳���ָʾ��
 bit[3:1]    ����
 bit[0]      ��������2����״̬��
   UNION�ṹ:  CBBP_DLFE_SDR_AT2_DUMP_EN_RPT_UNION */
#define CBBP_DLFE_SDR_AT2_DUMP_EN_RPT_ADDR            (SOC_BBP_CDMA_BASE_ADDR + 0xE074)

/* �Ĵ���˵����
 bit[31:16]  ��������1��ǰ����ҳ��������cpu_dlfe_sdr_word_depthͳ�ơ�
             ������Gģ��ʱʹ�á�
 bit[15:0]   ��������1��ǰ��������������cpu_dlfe_sdr_word_depthͳ�ơ�
             ������Gģ��ʱʹ�á�
   UNION�ṹ:  CBBP_DLFE_SDR_AT1_RD_WORD_RPT_UNION */
#define CBBP_DLFE_SDR_AT1_RD_WORD_RPT_ADDR            (SOC_BBP_CDMA_BASE_ADDR + 0xE078)

/* �Ĵ���˵����
 bit[31:16]  ��������2��ǰ����ҳ��������cpu_dlfe_sdr_word_depthͳ�ơ�
             ������Gģ��ʱʹ�á�
 bit[15:0]   ��������2��ǰ��������������cpu_dlfe_sdr_word_depthͳ�ơ�
             ������Gģ��ʱʹ�á�
   UNION�ṹ:  CBBP_DLFE_SDR_AT2_RD_WORD_RPT_UNION */
#define CBBP_DLFE_SDR_AT2_RD_WORD_RPT_ADDR            (SOC_BBP_CDMA_BASE_ADDR + 0xE07C)

/* �Ĵ���˵����
 bit[31:25]  ����
 bit[24]     ���а���ģʽ��0��DMA��ʽ��1��BBPMaster��ʽ��
 bit[23:17]  ����
 bit[16]     Gģ�����з��Ͷ�ʱѡ��0������gtc_timebase��1������gtc_tdma_qb��
 bit[15:13]  ����
 bit[12]     Gģ�����з���ģʽ��0������ģʽ��1������ģʽ��
 bit[11:10]  ����
 bit[9:8]    ����SDR IFģ�鹤��ģʽ��0��1��ʾ��Cģ��2��ʾ1X��3��ʾEVDO��
             �ò�������Cģʱ��Ч��
 bit[7:5]    ����
 bit[4]      ����da_on���ߵ�ƽ��Ч��BBP��sys_cntʱ϶�߽�ͬ����ʹ�á�
             �ò�������Cģʱ��Ч��
 bit[3:1]    ����
 bit[0]      ����SDR IFģ��ʹ�ܣ��ߵ�ƽ��Ч��
   UNION�ṹ:  CBBP_ULFE_SDR_EN_UNION */
#define CBBP_ULFE_SDR_EN_ADDR                         (SOC_BBP_CDMA_BASE_ADDR + 0xE100)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ���а���ʱ���ſ�bypass�źţ��ߵ�ƽ��Ч����ʾʱ�ӳ�����
   UNION�ṹ:  CBBP_ULFE_SDR_CKG_UNION */
#define CBBP_ULFE_SDR_CKG_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0xE104)

/* �Ĵ���˵����
 bit[31:6]   ����
 bit[5]      BBPMaster���˸�λ���塣
 bit[4]      BBPMaster���˷�ʽ�£�Cģ���ݰ����������塣
 bit[3:2]    ����
 bit[1]      ����ȡ������ֹͣ���塣
             �ò�������Gģ��ʱ��Ч��
 bit[0]      ����ȡ�������������塣
             �ò�������Gģ��ʱ��Ч��
   UNION�ṹ:  CBBP_ULFE_SDR_START_UNION */
#define CBBP_ULFE_SDR_START_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xE108)

/* �Ĵ���˵����
 bit[31:27]  ����
 bit[26:16]  Cģʱ����ʾ����ACHʱ϶ͷ���sys_cntʱ϶�߽��ӳ�������λchip��
             Gģ��ʱ��bit[22:16]��ʾ�������ݷ��͵�Qb��clkʱ�̣�bit[26:23]�����塣
 bit[15:13]  ����
 bit[12:0]   Cģʱ����ʾ����ʱ϶ͷ���sys_cntʱ϶�߽���ǰ������λ1/4chip��
             Gģ��ʱ����ʾgtc_tdma_qb�ϵ��������ݷ���ʱ�̣���λQb����Χ0~4999��
   UNION�ṹ:  CBBP_ULFE_SDR_OFFSET_UNION */
#define CBBP_ULFE_SDR_OFFSET_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xE10C)

/* �Ĵ���˵����
 bit[31:29]  ����
 bit[28:16]  Cģʱ����ʾ������λ������ǰʱ϶ͷ��Чλ�ã���λ1/4chip��
             Gģ��ʱ��bit[27:16]��ʾ�����������һ��burst�������㣬ȡֵ��Χ0~2499��bit[28]�����塣
 bit[15:13]  ����
 bit[12:0]   Cģʱ����ʾ����dbb��������ǰʱ϶ͷ��Чλ�ã���λ1/4chip��
             Gģ��ʱ��bit[11:0]��ʾ�������ݵ�һ��burst��ʼ���㣬ȡֵ��Χ0~2499��bit[12]�����塣
   UNION�ṹ:  CBBP_ULFE_SDR_ACTIVE_TIME_UNION */
#define CBBP_ULFE_SDR_ACTIVE_TIME_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0xE110)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    Gģ��ʱ���������ݰ�����burst������ȡֵ��Χ0~5������ֵ��1��ʾʵ��burst������
   UNION�ṹ:  CBBP_ULFE_SDR_G_CFG_UNION */
#define CBBP_ULFE_SDR_G_CFG_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xE114)

/* �Ĵ���˵����
 bit[31:9]   ����
 bit[8]      ����BBPMaster�������ָʾ��
 bit[7:5]    ����
 bit[4]      ����BBPMaster���˳���ָʾ��
 bit[3:1]    ����
 bit[0]      ���а���״̬��
   UNION�ṹ:  CBBP_ULFE_SDR_DUMP_EN_RPT_UNION */
#define CBBP_ULFE_SDR_DUMP_EN_RPT_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0xE140)



/***======================================================================***
                     (15/20) register_define_c_fe_sdr_if_mem
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  Cģʱ����ʾ����ǰ������Q·��12�����з����������ÿ1/4 PCG��slotдһ�顣
             Gģ��ʱ����ʾ���з�������Q·��12�����з����������ÿ1/5 burstдһ�顣
 bit[15:12]  ����
 bit[11:0]   Cģʱ����ʾ����ǰ������I·��12�����з����������ÿ1/4 PCG��slotдһ�顣
             Gģ��ʱ����ʾ���з�������I·��12�����з����������ÿ1/5 burstдһ�顣
   UNION�ṹ:  CBBP_ULFE_SDR_RAM_UNION */
#define CBBP_ULFE_SDR_RAM_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0xE800)
#define CBBP_ULFE_SDR_RAM_MEMDEPTH  (512)



/***======================================================================***
                     (16/20) register_define_c_fe_ctrl
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  c_fe_ctrlģ�鹤��ģʽ��0��1��ʾ��Cģ��2��ʾ1X��3��ʾEVDO��
 bit[15]     ����
 bit[14]     C��ģʱ��c2com_intrasys_valid_delay����������SSI��MIPI��GPIO RAM����ʹ�ܣ��ߵ�ƽ��Ч��
 bit[13]     C��ģʱ��c2com_intrasys_valid_delay�½�������SSI��MIPI��GPIO RAM����ʹ�ܣ��ߵ�ƽ��Ч��
 bit[12]     C��ģʱ��com2c_master_intrasys_valid �½�������SSI��MIPI��GPIO RAM����ʹ�ܣ��ߵ�ƽ��Ч��
 bit[11:9]   ����
 bit[8]      �������intersys_ingap_pre_ind�ź�ֵ��
 bit[7:5]    ����
 bit[4]      ���������Ƶ��ϵͳ����ʹ���ź�ֵ��
 bit[3:2]    ����
 bit[1:0]    C�������ͣ�0��Ƶ��1��ϵͳ��2��ģ��
   UNION�ṹ:  CBBP_CTU_CFG_UNION */
#define CBBP_CTU_CFG_ADDR                             (SOC_BBP_CDMA_BASE_ADDR + 0xF000)

/* �Ĵ���˵����
 bit[31:17]  ����
 bit[16:0]   ���������Ƶ��ϵͳ����ʹ���ź���sys_cnt��Чʱ�̣���λchip��
   UNION�ṹ:  CBBP_CTU_MEAS_ACT_TIME_UNION */
#define CBBP_CTU_MEAS_ACT_TIME_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xF004)

/* �Ĵ���˵����
 bit[31:17]  ����
 bit[16:0]   �������intersys_ingap_pre_ind�ź���sys_cnt��Чʱ�̣���λchip��
   UNION�ṹ:  CBBP_CTU_INGAP_ACT_TIME_UNION */
#define CBBP_CTU_INGAP_ACT_TIME_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0xF008)

/* �Ĵ���˵����
 bit[31:17]  ����
 bit[16:0]   �������intrasys_valid�ź���0��sys_cnt��Чʱ�̣���λchip��
   UNION�ṹ:  CBBP_CTU_INTRA_CLR_ACT_TIME_UNION */
#define CBBP_CTU_INTRA_CLR_ACT_TIME_ADDR              (SOC_BBP_CDMA_BASE_ADDR + 0xF00C)

/* �Ĵ���˵����
 bit[31:17]  ����
 bit[16:0]   �������intrasys_valid�ź���1��sys_cnt��Чʱ�̣���λchip��
   UNION�ṹ:  CBBP_CTU_INTRA_SET_ACT_TIME_UNION */
#define CBBP_CTU_INTRA_SET_ACT_TIME_ADDR              (SOC_BBP_CDMA_BASE_ADDR + 0xF010)

/* �Ĵ���˵����
 bit[31:17]  ����
 bit[16:0]   �������intrasys_valid_delay�ź���0��sys_cnt��Чʱ�̣���λchip��
   UNION�ṹ:  CBBP_CTU_INTRA_DLY_CLR_ACT_TIME_UNION */
#define CBBP_CTU_INTRA_DLY_CLR_ACT_TIME_ADDR          (SOC_BBP_CDMA_BASE_ADDR + 0xF014)

/* �Ĵ���˵����
 bit[31:17]  ����
 bit[16:0]   �������intrasys_valid_delay�ź���1��sys_cnt��Чʱ�̣���λchip��
   UNION�ṹ:  CBBP_CTU_INTRA_DLY_SET_ACT_TIME_UNION */
#define CBBP_CTU_INTRA_DLY_SET_ACT_TIME_ADDR          (SOC_BBP_CDMA_BASE_ADDR + 0xF018)

/* �Ĵ���˵����
 bit[31:17]  ����
 bit[16:0]   �������ssi_mipi_stop�ź���0��sys_cnt��Чʱ�̣���λchip��
   UNION�ṹ:  CBBP_CTU_STOP_CLR_ACT_TIME_UNION */
#define CBBP_CTU_STOP_CLR_ACT_TIME_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0xF01C)

/* �Ĵ���˵����
 bit[31:17]  ����
 bit[16:0]   �������ssi_mipi_stop�ź���1��sys_cnt��Чʱ�̣���λchip��
   UNION�ṹ:  CBBP_CTU_STOP_SET_ACT_TIME_UNION */
#define CBBP_CTU_STOP_SET_ACT_TIME_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0xF020)

/* �Ĵ���˵����
 bit[31:11]  ����
 bit[10:0]   rfic_ssiÿʱ϶t2λ��(sys_cnt)���޷���������Χ[0,1535��2047]����λchip��BBP�ڴ�λ�ö�RFIC SSI RAM��ҳ������ʼ����RAM�����ַ������ݡ�ע�⣺��G SDRģʽ���ò���������active_time��ͬ
   UNION�ṹ:  CBBP_RFIC_START_TIME_UNION */
#define CBBP_RFIC_START_TIME_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xF040)

/* �Ĵ���˵����
 bit[31:13]  ����
 bit[12]     �Զ���ҳʹ�ܣ�0��������������ֶ���ҳ��1�����������ʱ���Զ���ҳ��
 bit[11]     ��ҳʹ�ܣ�0:����ҳ�������BBP��ʹ�õͶ�RAM��1����ҳ�������BBPƹ��ʹ�øߵ�����RAM��
 bit[10:4]   ÿ��ƹ��RAM��data_buffer��ʼ��ַ��
 bit[3]      ����
 bit[2]      0:ÿ��ctrl_buff��Ӧ���7�����ݡ�1:ÿ��ctrl_buff��Ӧ���3�����ݡ�
 bit[1]      0:ctrl_buffִ��������㣬1:ctrl_buffִ���������
 bit[0]      0:��ѯģʽ��DSPд��RAM���������ͣ�BBPѭ����������ctrlbuffer��ֱ��ȫ�����ݷ�����ɡ���ģʽ��������cpu_rfic_ssi_buffer_clr_modeΪ1
             1:�������ģʽ��DSP����ʱ϶��Ҫ���͵��������ݰ���Чʱ����ǰ�����������RAM�У�BBPֻ����һ��ctrlbuffer������ִ�С�
             
   UNION�ṹ:  CBBP_RFIC_SSI_STA_CFG_UNION */
#define CBBP_RFIC_SSI_STA_CFG_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0xF044)

/* �Ĵ���˵����
 bit[31:8]   ����
 bit[7]      ֹͣ����ģʽ��0��ʾ����ֹͣ�����������ݣ�1��ʾ��ǰctrl_buff��Ӧ���ݷ�����ɺ���ֹͣ��
 bit[6]      1��ʾֹͣ���͵�ǰRAM�����ݲ������ǰRAM�������ݡ�
 bit[5]      ����
 bit[4]      1��ʾ��ͣ���͵�ǰRAM�����ݡ������ź���Чʱ���������Ҫ��дRAM�е����ݣ�����Ҫ�ֶ���ҳ��ֱ���ڵ�ǰҳ������Hold������BBP���ͷ��ʼ����ִ��CtrlBuffer��ָ��
 bit[3:1]    ����
 bit[0]      ģ�鹤��ʹ�ܣ��ߵ�ƽ��Ч��
   UNION�ṹ:  CBBP_RFIC_SSI_DYN_CFG_UNION */
#define CBBP_RFIC_SSI_DYN_CFG_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0xF048)

/* �Ĵ���˵����
 bit[31:17]  ����
 bit[16]     C_FE_RFIC ǿ�Ʒ������塣cpu_rfic_ssi_force_en=1ʱ����Ч��
 bit[15:1]   ����
 bit[0]      д1���������źţ��ֶ�����ָ��ҳִ�У�cpu_rfic_ssi_auto_run=0ʱ����Ч��
   UNION�ṹ:  CBBP_RFIC_SSI_START_UNION */
#define CBBP_RFIC_SSI_START_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xF04C)

/* �Ĵ���˵����
 bit[31]     C_FE_RFIC ǿ�Ʒ���ʹ�ܡ��ر�cpu_rfic_ssi_pro_enʱʹ�ã����߹���״̬����cpu_rfic_ssi_hold_page��ͣ��ʹ�á�
 bit[30:25]  ����
 bit[24:0]   C_FE_RFIC ǿ�Ʒ������ݣ�cpu_rfic_ssi_force_en=1ʱ����Ч��
   UNION�ṹ:  CBBP_RFIC_SSI_FORCE_UNION */
#define CBBP_RFIC_SSI_FORCE_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xF050)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:12]  �쳣����״̬�ϱ�������ڵ�ǰָ��û��ִ���꣬��̬���ñ���д����ᴥ���쳣�ϱ�����bit����ֱ����£�
             [12]work_mode_sel���쳣��д
             [13]buffer_clr_mode���쳣��д
             [14]data_buffer_start_addr���쳣��д
 bit[11:5]   ��ǰִ�е���rfic_ctrl buff�ĵ�ַ
 bit[4]      BBP��ǰʹ��ƹ��RAM״̬�ϱ���
 bit[3]      ����
 bit[2:0]    rfic_ssi RAM����״̬�ϱ���
   UNION�ṹ:  CBBP_RFIC_STATE_RPT_UNION */
#define CBBP_RFIC_STATE_RPT_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xF054)

/* �Ĵ���˵����
 bit[31:11]  ����
 bit[10:0]   mipiÿʱ϶t2λ��(sys_cnt)���޷���������Χ[0,1535��2047]����λchip��BBP�ڴ�λ�ö�MIPI RAM��ҳ������ʼ����RAM�����ַ������ݡ�
             
   UNION�ṹ:  CBBP_MIPI_START_TIME_UNION */
#define CBBP_MIPI_START_TIME_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xF070)

/* �Ĵ���˵����
 bit[31:13]  ����
 bit[12]     �Զ���ҳʹ�ܣ�0��������������ֶ���ҳ��1�����������ʱ���Զ���ҳ��
 bit[11]     ��ҳʹ�ܣ�0:����ҳ�������BBP��ʹ�õͶ�RAM��1����ҳ�������BBPƹ��ʹ�øߵ�����RAM��
 bit[10:4]   ÿ��ƹ��RAM��data_buffer��ʼ��ַ��
 bit[3]      ����
 bit[2]      0:ÿ��ctrl_buff��Ӧ���3�����ݡ�1:ÿ��ctrl_buff��Ӧ���1�����ݡ�
 bit[1]      0:ctrl_buffִ��������㣬1:ctrl_buffִ���������
 bit[0]      0:��ѯģʽ��DSPд��RAM���������ͣ�BBPѭ����������ctrlbuffer��ֱ��ȫ�����ݷ�����ɡ�
             1:�������ģʽ��DSP����ʱ϶��Ҫ���͵��������ݰ���Чʱ����ǰ�����������RAM�У�BBPֻ����һ��ctrlbuffer������ִ�С�
             
   UNION�ṹ:  CBBP_MIPI_STA_CFG_UNION */
#define CBBP_MIPI_STA_CFG_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0xF074)

/* �Ĵ���˵����
 bit[31:8]   ����
 bit[7]      ֹͣ����ģʽ��0��ʾ����ֹͣ�����������ݣ�1��ʾ��ǰctrl_buff��Ӧ���ݷ�����ɺ���ֹͣ��
 bit[6]      1��ʾֹͣ���͵�ǰRAM�����ݲ������ǰRAM�������ݡ�
 bit[5]      ����
 bit[4]      1��ʾ��ͣ���͵�ǰRAM�����ݡ��÷���cpu_rfic_ssi_hold_page
 bit[3:1]    ����
 bit[0]      ģ�鹤��ʹ�ܣ��ߵ�ƽ��Ч��
   UNION�ṹ:  CBBP_MIPI_DYN_CFG_UNION */
#define CBBP_MIPI_DYN_CFG_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0xF078)

/* �Ĵ���˵����
 bit[31:5]   ����
 bit[4]      C_FE_MIPI ǿ�Ʒ������塣cpu_mipi_force_en=1ʱ����Ч��
 bit[3:1]    ����
 bit[0]      д1���������źţ��ֶ�����ָ��ҳִ�У�cpu_mipi_auto_run=0ʱ����Ч��
   UNION�ṹ:  CBBP_MIPI_START_UNION */
#define CBBP_MIPI_START_ADDR                          (SOC_BBP_CDMA_BASE_ADDR + 0xF07C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      C_FE_MIPI ǿ�Ʒ���ʹ�ܡ��ر�cpu_mipi_pro_enʱʹ�ã����߹���״̬����cpu_mipi_hold_page��ͣ��ʹ�á�
             ǿ��ʱ��mipi_force_data��������64bit���ߵͶ����ã���������ݲ���32bit���������ڸ�32bit���ҵ�32bit����Ϊ0��
   UNION�ṹ:  CBBP_MIPI_FORCE_EN_UNION */
#define CBBP_MIPI_FORCE_EN_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0xF080)

/* �Ĵ���˵����
   ��      ����C_FE_MIPI ǿ�Ʒ�������(�߰벿��)��cpu_mipi_force_en=1ʱ����Ч��
   UNION�ṹ ���� */
#define CBBP_MIPI_FORCE_DATA_H_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xF084)

/* �Ĵ���˵����
   ��      ����C_FE_MIPI ǿ�Ʒ�������(�Ͱ벿��)��cpu_mipi_force_en=1ʱ����Ч��
   UNION�ṹ ���� */
#define CBBP_MIPI_FORCE_DATA_L_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xF088)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:12]  �쳣����״̬�ϱ�������ڵ�ǰָ��û��ִ���꣬��̬���ñ���д����ᴥ���쳣�ϱ�����bit����ֱ����£�
             [12]work_mode_sel���쳣��д
             [13]buffer_clr_mode���쳣��д
             [14]data_buffer_start_addr���쳣��д
 bit[11:5]   ��ǰִ�е���rfic_ctrl buff�ĵ�ַ
 bit[4]      BBP��ǰʹ��RAM��ƹ��״̬�ϱ���
 bit[3]      ����
 bit[2:0]    mipi RAM���Ƶ�״̬���ϱ���
   UNION�ṹ:  CBBP_MIPI_STATE_RPT_UNION */
#define CBBP_MIPI_STATE_RPT_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xF08C)

/* �Ĵ���˵����
 bit[31:11]  ����
 bit[10:0]   GPIOÿʱ϶t2λ��(sys_cnt)���޷���������Χ[0,1535��2047]����λchip��BBP�ڴ�λ�ö�GPIO RAM��ҳ������ʼ����RAM�����ַ������ݡ�
             
   UNION�ṹ:  CBBP_GPIO_START_TIME_UNION */
#define CBBP_GPIO_START_TIME_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xF0A0)

/* �Ĵ���˵����
 bit[31:12]  ����
 bit[11]     �Զ���ҳʹ�ܣ�0��������������ֶ���ҳ��1�����������ʱ���Զ���ҳ��
 bit[10]     ��ҳʹ�ܣ�0:����ҳ�������BBP��ʹ�õͶ�RAM��1����ҳ�������BBPƹ��ʹ�øߵ�����RAM��
 bit[9:4]    ÿ��ƹ��RAM��data_buffer��ʼ��ַ��
 bit[3:2]    ����
 bit[1]      0:ctrl_buffִ��������㣬1:ctrl_buffִ���������
 bit[0]      0:��ѯģʽ��DSPд��RAM���������ͣ�BBPѭ����������ctrlbuffer��ֱ��ȫ�����ݷ�����ɡ�
             1:�������ģʽ��DSP����ʱ϶��Ҫ���͵��������ݰ���Чʱ����ǰ�����������RAM�У�BBPֻ����һ��ctrlbuffer������ִ�С�
             
   UNION�ṹ:  CBBP_GPIO_STA_CFG_UNION */
#define CBBP_GPIO_STA_CFG_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0xF0A4)

/* �Ĵ���˵����
 bit[31:9]   ����
 bit[8]      1��ʾֹͣ���͵�ǰRAM�����ݲ������ǰRAM�������ݡ�
 bit[7:5]    ����
 bit[4]      1��ʾ��ͣ���͵�ǰRAM�����ݡ�
 bit[3:1]    ����
 bit[0]      ģ�鹤��ʹ�ܣ��ߵ�ƽ��Ч��
   UNION�ṹ:  CBBP_GPIO_DYN_CFG_UNION */
#define CBBP_GPIO_DYN_CFG_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0xF0A8)

/* �Ĵ���˵����
 bit[31:5]   ����
 bit[4]      C_FE_GPIO ǿ�Ʒ������壬cpu_gpio_force_en=1ʱ����Ч��
 bit[3:1]    ����
 bit[0]      д1���������źţ��ֶ�����ָ��ҳִ�У�cpu_gpio_auto_run=0ʱ����Ч��
   UNION�ṹ:  CBBP_GPIO_START_UNION */
#define CBBP_GPIO_START_ADDR                          (SOC_BBP_CDMA_BASE_ADDR + 0xF0AC)

/* �Ĵ���˵����
 bit[31]     C_FE_GPIO ǿ�Ʒ���ʹ�ܣ��ر�cpu_gpio_pro_enʱʹ�ã����߹���״̬����cpu_gpio_hold_page��ͣ��ʹ�á�
 bit[30:0]   ����
   UNION�ṹ:  CBBP_GPIO_FORCE_EN_UNION */
#define CBBP_GPIO_FORCE_EN_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0xF0B0)

/* �Ĵ���˵����
   ��      ����C_FE_GPIO ǿ�Ʒ������ݣ�cpu_gpio_force_en=1ʱ����Ч��[31]=0��ʾant_pa_sel���ݣ�[31]=1��ʾabb_en�������߿�ֵ����[31]=1ʱ��bit0~bit9���α�ʾ��
            bit[0]:c_abb0_rxa_en,ABB Aͨ������ʹ��
            bit[1]:c_abb0_rxb_en,ABB Bͨ������ʹ��
            bit[2]:c_abb0_rxa_blk_en,ABB Aͨ��Block����ʹ��
            bit[3]:c_abb0_rxb_blk_en,ABB Bͨ��Block����ʹ��
            bit[4]:c_abb0_tx_en,ABB ����ͨ������ʹ��
            bit[5]:c2com_rf0_tcvr_on,RF �ܹ���ʹ��
            bit[6]:c2com_rf0_tx_en,RF TX����ʹ��
            bit[7]:����
            bit[9:8]:ABBͨ��ѡ��
            00����ʾAͨ��Ϊ������Bͨ��Ϊ�ּ���11����ʾAͨ��Ϊ�ּ���Bͨ��Ϊ������
            bit[30:10]:����
            bit[31]:Ϊ0ʱ����ʾ�����߿�ant_pa_sel����
            Ϊ1ʱ��ʾר���߿أ�ÿ��bit�ĺ���������bit[9:0]����
   UNION�ṹ ���� */
#define CBBP_GPIO_FORCE_DATA_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xF0B4)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:12]  �쳣����״̬�ϱ�������ڵ�ǰָ��û��ִ���꣬��̬���ñ���д����ᴥ���쳣�ϱ�����bit����ֱ����£�
             [12]work_mode_sel���쳣��д
             [13]buffer_clr_mode���쳣��д
             [14]data_buffer_start_addr���쳣��д
 bit[11]     ����
 bit[10:5]   ��ǰִ�е���gpio_ctrl buff�ĵ�ַ
 bit[4]      BBP��ǰʹ��ƹ��RAM״̬�ϱ���
 bit[3]      ����
 bit[2:0]    gpio RAM����״̬�ϱ���
   UNION�ṹ:  CBBP_GPIO_STATE_RPT_UNION */
#define CBBP_GPIO_STATE_RPT_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xF0B8)

/* �Ĵ���˵����
 bit[31]     ����
 bit[30:0]   �����߿�(antpa)�����ϱ���
   UNION�ṹ:  CBBP_GPIO_ANTPA_RPT_UNION */
#define CBBP_GPIO_ANTPA_RPT_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xF0BC)

/* �Ĵ���˵����
 bit[31]     ����
 bit[30:0]   ר���߿أ�gpio�߿أ��ϱ���bit[0]:c_abb0_rxa_en,ABB Aͨ������ʹ��
             bit[1]:c_abb0_rxb_en,ABB Bͨ������ʹ��
             bit[2]:c_abb0_rxa_blk_en,ABB Aͨ��Block����ʹ��
             bit[3]:c_abb0_rxb_blk_en,ABB Bͨ��Block����ʹ��
             bit[4]:c_abb0_tx_en,ABB ����ͨ������ʹ��
             bit[5]:c2com_rf0_tcvr_on,RF �ܹ���ʹ��
             bit[6]:c2com_rf0_tx_en,RF TX����ʹ��
             bit[30:7]:����
   UNION�ṹ:  CBBP_GPIO_LINE_CTRL_RPT_UNION */
#define CBBP_GPIO_LINE_CTRL_RPT_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0xF0C0)

/* �Ĵ���˵����
 bit[31:11]  ����
 bit[10:0]   HKADC SSIÿʱ϶t2λ��(sys_cnt)���޷���������Χ[0,1535��2047]����λchip��BBP�ڴ�λ�ö�HKADC SSI RAM���·��ͣ�����ʼ����RAM�����ַ������ݡ�
             ע�⣺��G SDRģʽ���ò���������active_time��ͬ
   UNION�ṹ:  CBBP_HKADC_START_TIME_UNION */
#define CBBP_HKADC_START_TIME_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0xF0D0)

/* �Ĵ���˵����
 bit[31:20]  ����
 bit[19]     �Զ�����ʹ�ܣ�0��������������ֶ����У�1�����������ʱ���Զ����С�
 bit[18:16]  hkadc ssi��ʱ��������λssi clock���ڡ�
 bit[15:11]  ����
 bit[10:4]   ÿ��ƹ��RAM��data_buffer��ʼ��ַ��
 bit[3:0]    ����
   UNION�ṹ:  CBBP_HKADC_STA_CFG_UNION */
#define CBBP_HKADC_STA_CFG_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0xF0D4)

/* �Ĵ���˵����
 bit[31:9]   ����
 bit[8]      1��ʾֹͣ���͵�ǰRAM�����ݲ������ǰRAM�������ݡ�
 bit[7:5]    ����
 bit[4]      1��ʾ��ͣ���͵�ǰRAM�����ݡ��÷�ͬcpu_rfic_ssi_hold_page
 bit[3:1]    ����
 bit[0]      ģ�鹤��ʹ�ܣ��ߵ�ƽ��Ч��
   UNION�ṹ:  CBBP_HKADC_DYN_CFG_UNION */
#define CBBP_HKADC_DYN_CFG_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0xF0D8)

/* �Ĵ���˵����
 bit[31:5]   ����
 bit[4:1]    ����
 bit[0]      д1���������źţ��ֶ�����ָ��ҳִ�У�cpu_hkadc_ssi_auto_run=0ʱ����Ч��
   UNION�ṹ:  CBBP_HKADC_START_UNION */
#define CBBP_HKADC_START_ADDR                         (SOC_BBP_CDMA_BASE_ADDR + 0xF0DC)

/* �Ĵ���˵����
 bit[31]     C_HKADC_SSI ǿ�Ʒ���ʹ�ܣ���ͬʱ����cpu_hkadc_ssi_pro_en=1�����߹���״̬����cpu_hkadc_ssi_hold_page��ͣ��ʹ�á�
 bit[30]     C_HKADC_SSI ǿ�Ʒ�������
 bit[29:17]  ����
 bit[16:0]   C_HKADC_SSI ǿ�Ʒ������ݣ�cpu_hkadc_force_en=1ʱ����Ч��
   UNION�ṹ:  CBBP_HKADC_FORCE_UNION */
#define CBBP_HKADC_FORCE_ADDR                         (SOC_BBP_CDMA_BASE_ADDR + 0xF0E0)

/* �Ĵ���˵����
 bit[31:9]   ����
 bit[8:0]    ���ӳ�ʱ�䣬��λ 19Mclock����
   UNION�ṹ:  CBBP_HKADC_RD_WAIT_UNION */
#define CBBP_HKADC_RD_WAIT_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0xF0E4)

/* �Ĵ���˵����
 bit[31:5]   ����
 bit[4]      PD�����Ч��־��������
 bit[3:1]    ����
 bit[0]      PD��ʱ��־��������
   UNION�ṹ:  CBBP_HKADC_CLR_UNION */
#define CBBP_HKADC_CLR_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0xF0E8)

/* �Ĵ���˵����
 bit[31:23]  ����
 bit[22:20]  �쳣����״̬�ϱ�������ڵ�ǰָ��û��ִ���꣬��̬���ñ���д����ᴥ���쳣�ϱ�����bit����ֱ����£�
             [20]work_mode_sel���쳣��д
             [21]buffer_clr_mode���쳣��д
             [22]data_buffer_start_addr���쳣��д
 bit[19:18]  ����
 bit[17:11]  ��ǰִ�е���hkadc_ctrl buff�ĵ�ַ
 bit[10:8]   SSI RAM����״̬�ϱ���
 bit[7:5]    ����
 bit[4]      PD�����Ч��־���ߵ�ƽ��Ч��
 bit[3:1]    ����
 bit[0]      PD��ʱ��־���ߵ�ƽ��Ч��
   UNION�ṹ:  CBBP_HKADC_FLAG_RPT_UNION */
#define CBBP_HKADC_FLAG_RPT_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xF0EC)

/* �Ĵ���˵����
 bit[31:16]  ��ʱ϶��1��PD�ض����,[13:8]��ʾ����ַ��[7:0]��ʾ�����ݣ��޷���������ͬ��
 bit[15:0]   ��ʱ϶��0��PD�ض������
   UNION�ṹ:  CBBP_HKADC_RESULT0_1_UNION */
#define CBBP_HKADC_RESULT0_1_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xF100)

/* �Ĵ���˵����
 bit[31:16]  ��ʱ϶��3��PD�ض������
 bit[15:0]   ��ʱ϶��2��PD�ض������
   UNION�ṹ:  CBBP_HKADC_RESULT2_3_UNION */
#define CBBP_HKADC_RESULT2_3_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xF104)

/* �Ĵ���˵����
 bit[31:16]  ��ʱ϶��5��PD�ض������
 bit[15:0]   ��ʱ϶��4��PD�ض������
   UNION�ṹ:  CBBP_HKADC_RESULT4_5_UNION */
#define CBBP_HKADC_RESULT4_5_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xF108)

/* �Ĵ���˵����
 bit[31:16]  ��ʱ϶��7��PD�ض������
 bit[15:0]   ��ʱ϶��6��PD�ض������
   UNION�ṹ:  CBBP_HKADC_RESULT6_7_UNION */
#define CBBP_HKADC_RESULT6_7_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xF10C)

/* �Ĵ���˵����
 bit[31:16]  ��ʱ϶��9��PD�ض������
 bit[15:0]   ��ʱ϶��8��PD�ض������
   UNION�ṹ:  CBBP_HKADC_RESULT8_9_UNION */
#define CBBP_HKADC_RESULT8_9_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xF110)

/* �Ĵ���˵����
 bit[31:16]  ��ʱ϶��11��PD�ض������
 bit[15:0]   ��ʱ϶��10��PD�ض������
   UNION�ṹ:  CBBP_HKADC_RESULT10_11_UNION */
#define CBBP_HKADC_RESULT10_11_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xF114)

/* �Ĵ���˵����
 bit[31:16]  ��ʱ϶��13��PD�ض������
 bit[15:0]   ��ʱ϶��12��PD�ض������
   UNION�ṹ:  CBBP_HKADC_RESUL12_13_UNION */
#define CBBP_HKADC_RESUL12_13_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0xF118)

/* �Ĵ���˵����
 bit[31:16]  ��ʱ϶��15��PD�ض������
 bit[15:0]   ��ʱ϶��14��PD�ض������
   UNION�ṹ:  CBBP_HKADC_RESULT14_15_UNION */
#define CBBP_HKADC_RESULT14_15_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xF11C)

/* �Ĵ���˵����
 bit[31:16]  ��ʱ϶��17��PD�ض������
 bit[15:0]   ��ʱ϶��16��PD�ض������
   UNION�ṹ:  CBBP_HKADC_RESULT16_17_UNION */
#define CBBP_HKADC_RESULT16_17_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xF120)

/* �Ĵ���˵����
 bit[31:16]  ��ʱ϶��19��PD�ض������
 bit[15:0]   ��ʱ϶��08��PD�ض������
   UNION�ṹ:  CBBP_HKADC_RESULT18_19_UNION */
#define CBBP_HKADC_RESULT18_19_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xF124)

/* �Ĵ���˵����
 bit[31:16]  ��ʱ϶��21��PD�ض������
 bit[15:0]   ��ʱ϶��20��PD�ض������
   UNION�ṹ:  CBBP_HKADC_RESULT20_21_UNION */
#define CBBP_HKADC_RESULT20_21_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xF128)

/* �Ĵ���˵����
 bit[31:16]  ��ʱ϶��23��PD�ض������
 bit[15:0]   ��ʱ϶��22��PD�ض������
   UNION�ṹ:  CBBP_HKADC_RESULT22_23_UNION */
#define CBBP_HKADC_RESULT22_23_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xF12C)

/* �Ĵ���˵����
 bit[31:16]  ��ʱ϶��25��PD�ض������
 bit[15:0]   ��ʱ϶��24��PD�ض������
   UNION�ṹ:  CBBP_HKADC_RESULT24_25_UNION */
#define CBBP_HKADC_RESULT24_25_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xF130)

/* �Ĵ���˵����
 bit[31:16]  ��ʱ϶��27��PD�ض������
 bit[15:0]   ��ʱ϶��26��PD�ض������
   UNION�ṹ:  CBBP_HKADC_RESULT26_27_UNION */
#define CBBP_HKADC_RESULT26_27_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xF134)

/* �Ĵ���˵����
 bit[31:16]  ��ʱ϶��29��PD�ض������
 bit[15:0]   ��ʱ϶��28��PD�ض������
   UNION�ṹ:  CBBP_HKADC_RESULT28_29_UNION */
#define CBBP_HKADC_RESULT28_29_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xF138)

/* �Ĵ���˵����
 bit[31:16]  ��ʱ϶��31��PD�ض������
 bit[15:0]   ��ʱ϶��30��PD�ض������
   UNION�ṹ:  CBBP_HKADC_RESULT30_31_UNION */
#define CBBP_HKADC_RESULT30_31_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xF13C)

/* �Ĵ���˵����
 bit[31:11]  ����
 bit[10:0]   ÿʱ϶/PCG����PA vbias�����ַ���ʱ��(sys_cnt)���޷���������Χ[0,1535��2047]����λchip��
   UNION�ṹ:  CBBP_AUXDAC_START_TIME_UNION */
#define CBBP_AUXDAC_START_TIME_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xF160)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:8]   ÿʱ϶������õ�vbias�����֣��޷�������
 bit[7:1]    ����
 bit[0]      AUXDACģ��ʹ�ܣ��ߵ�ƽ��Ч��
   UNION�ṹ:  CBBP_AUXDAC_SSI_CFG_UNION */
#define CBBP_AUXDAC_SSI_CFG_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xF164)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      w1_pulse�����д1ʱ�������壬���ڷ���aucxdac vbias�����֡�cpu_auxdac_force_en=1ʱ����Ч��
   UNION�ṹ:  CBBP_AUXDAC_START_UNION */
#define CBBP_AUXDAC_START_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0xF168)

/* �Ĵ���˵����
 bit[31]     auxdac ssiǿ�Ʒ���ʹ�ܣ��ߵ�ƽ��Ч��
 bit[30:1]   ����
 bit[0]      vbias�����ֵ�ַ
   UNION�ṹ:  CBBP_AUXDAC_FORCE_UNION */
#define CBBP_AUXDAC_FORCE_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0xF16C)

/* �Ĵ���˵����
 bit[31:27]  ����
 bit[26:16]  auxdac�رտ����֡�
 bit[15:11]  ����
 bit[10:0]   auxdac���������֡�
   UNION�ṹ:  CBBP_AUXDAC_CFG_UNION */
#define CBBP_AUXDAC_CFG_ADDR                          (SOC_BBP_CDMA_BASE_ADDR + 0xF170)

/* �Ĵ���˵����
 bit[31:11]  ����
 bit[10:0]   ÿʱ϶/PCG����PA APT�����ַ���ʱ��(sys_cnt)���޷���������Χ[0,1535��2047]����λchip��
   UNION�ṹ:  CBBP_APT_START_TIME_UNION */
#define CBBP_APT_START_TIME_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xF180)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:8]   ÿʱ϶������õ�APT�����֣��޷�������
 bit[7:1]    ����
 bit[0]      APTģ��ʹ�ܣ��ߵ�ƽ��Ч��ͬʱ�������Ϊ����DCDCоƬʹ�ܡ�
   UNION�ṹ:  CBBP_APT_CFG_UNION */
#define CBBP_APT_CFG_ADDR                             (SOC_BBP_CDMA_BASE_ADDR + 0xF184)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      w1_pulse�����д1ʱ�������壬���� ǿ�Ʒ���apt�����֡�
   UNION�ṹ:  CBBP_APT_START_UNION */
#define CBBP_APT_START_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0xF188)

/* �Ĵ���˵����
 bit[31]     apt pdmǿ�Ʒ���ʹ�ܣ��ߵ�ƽ��Ч��
 bit[30:1]   ����
 bit[0]      apt pdm�����ʽѡ��0��PWM��1��PDM
   UNION�ṹ:  CBBP_APT_FORCE_UNION */
#define CBBP_APT_FORCE_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0xF18C)

/* �Ĵ���˵����
 bit[31:11]  ����
 bit[10:0]   ÿʱ϶afc�����ַ���ʱ��(sys_cnt)���޷���������Χ[0,1535��2047]����λchip��
   UNION�ṹ:  CBBP_AFC_START_TIME_UNION */
#define CBBP_AFC_START_TIME_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xF1A0)

/* �Ĵ���˵����
 bit[31:21]  ����
 bit[20:8]   ÿʱ϶������õ�AFC�����֣��޷�������
 bit[7:2]    ����
 bit[1]      afc pdm������λ��ѡ�� 0��12bit 1��13bit.
 bit[0]      AFC PDM/PWMģʽѡ��0:PDMģʽ��1��PWM��ʽ
   UNION�ṹ:  CBBP_AFC_CFG_UNION */
#define CBBP_AFC_CFG_ADDR                             (SOC_BBP_CDMA_BASE_ADDR + 0xF1A4)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      w1_pulse�����д1ʱ�������壬����ǿ�Ʒ���afc�����֡�
   UNION�ṹ:  CBBP_AFC_START_UNION */
#define CBBP_AFC_START_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0xF1A8)

/* �Ĵ���˵����
 bit[31]     AFC PDMǿ�Ƹ���ʹ�ܣ��ߵ�ƽ��Ч��
 bit[30:0]   ����
   UNION�ṹ:  CBBP_AFC_FORCE_UNION */
#define CBBP_AFC_FORCE_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0xF1AC)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    ǰ�˿���ģ����Զ�ʱ���ſ���·�źţ�1��ʾ��·ʱ���ſأ���ʱ�ӳ�����0��ʾ�Զ�ʱ���ſ���Ч��
             [0] MIPI���Զ�ʱ���ſ���·����
             [1] RFIC_SSI���Զ�ʱ���ſ���·����
             [2] GPIO���Զ�ʱ���ſ���·����
   UNION�ṹ:  CBBP_CPU_FE_CTRL_CKG_BYPASS_UNION */
#define CBBP_CPU_FE_CTRL_CKG_BYPASS_ADDR              (SOC_BBP_CDMA_BASE_ADDR + 0xF1B0)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      �쳣����״̬�������������쳣״̬�ϱ������0x54[14:12], 0x8c[14:12], 0xb8[14:12], 0xec[22:20]�����������������쳣���һֱ���֡�
   UNION�ṹ:  CBBP_ERR_CONFIG_CLR_UNION */
#define CBBP_ERR_CONFIG_CLR_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xF1B4)

/* �Ĵ���˵����
 bit[31:9]   ����
 bit[8]      RF SSI����ָ����Ч��־����ʹ�ܣ������źţ���cpu_gpio_ctrl_valid_cfg֮�����ñ��ź�
 bit[7:5]    ����
 bit[4]      RF SSI����ָ����Ч��־����ʹ�ܣ������źţ���cpu_mipi_ctrl_valid_cfg֮�����ñ��ź�
 bit[3:1]    ����
 bit[0]      RF SSI����ָ����Ч��־����ʹ�ܣ������źţ���cpu_ssi_ctrl_valid_cfg֮�����ñ��ź�
   UNION�ṹ:  CBBP_CTRL_VALID_IND_CFG_UNION */
#define CBBP_CTRL_VALID_IND_CFG_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0xF1B8)

/* �Ĵ���˵����
   ��      ����RF SSI����ָ����Ч��־���ã�����ɿ���ָ�����ú����ñ��źţ�����ָʾ�ж�����Ч�Ŀ���ָ�ÿbit��Ӧ1������ָ�������0x0001���ʾֻ�е�0�е�ָ����Ч��0x1001���ʾ��0�к͵�12�е�ָ����Ч��
   UNION�ṹ ���� */
#define CBBP_SSI_CTRL_VALID_CFG_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0xF1BC)

/* �Ĵ���˵����
   ��      ����MIPI����ָ����Ч��־���ã�����ɿ���ָ�����ú����ñ��źţ�����ָʾ�ж�����Ч�Ŀ���ָ�ÿbit��Ӧ1������ָ�������0x0001���ʾֻ�е�0�е�ָ����Ч��0x1001���ʾ��0�к͵�12�е�ָ����Ч��
   UNION�ṹ ���� */
#define CBBP_MIPI_CTRL_VALID_CFG_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0xF1C0)

/* �Ĵ���˵����
   ��      ����GPIO����ָ����Ч��־���ã�����ɿ���ָ�����ú����ñ��źţ�����ָʾ�ж�����Ч�Ŀ���ָ�ÿbit��Ӧ1������ָ�������0x0001���ʾֻ�е�0�е�ָ����Ч��0x1001���ʾ��0�к͵�12�е�ָ����Ч��
   UNION�ṹ ���� */
#define CBBP_GPIO_CTRL_VALID_CFG_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0xF1C4)

/* �Ĵ���˵����
 bit[31:9]   ����
 bit[8]      GPIO����ָ����Ч��־ǿ�Ƹ�λ�������źš�1��Ч�����ú�����û�б�����Ŀ���ָ������ٴ�ִ�С�
 bit[7:5]    ����
 bit[4]      MIPI����ָ����Ч��־ǿ�Ƹ�λ�������źš�1��Ч�����ú�����û�б�����Ŀ���ָ������ٴ�ִ�С�
 bit[3:1]    ����
 bit[0]      RF SSI����ָ����Ч��־ǿ�Ƹ�λ�������źš�1��Ч�����ú�����û�б�����Ŀ���ָ������ٴ�ִ�С�
   UNION�ṹ:  CBBP_CTRL_VALID_FORCE_RESET_UNION */
#define CBBP_CTRL_VALID_FORCE_RESET_ADDR              (SOC_BBP_CDMA_BASE_ADDR + 0xF1CC)

/* �Ĵ���˵����
   ��      ����RF SSI��ǰҳ���CTRL_VALID��־�ϱ�
   UNION�ṹ ���� */
#define CBBP_SSI_CTRL_VALID_RPT_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0xF1D0)

/* �Ĵ���˵����
   ��      ����MIPI��ǰҳ���CTRL_VALID��־�ϱ�
   UNION�ṹ ���� */
#define CBBP_MIPI_CTRL_VALID_RPT_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0xF1D4)

/* �Ĵ���˵����
   ��      ����GPIO��ǰҳ���CTRL_VALID��־�ϱ�
   UNION�ṹ ���� */
#define CBBP_GPIO_CTRL_VALID_RPT_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0xF1D8)



/***======================================================================***
                     (17/20) register_define_c_fe_ctrl_mem
 ***======================================================================***/
/* �Ĵ���˵����ƹ��RAM��ctrlָ����������16��
 bit[31:27]  ����
 bit[26:24]  ��������ָ���Ӧ��rfic����ָ��ĸ�����3bit��0~7��Ӧ���ø���Ϊ0~7����0��ʾ������
 bit[23:17]  ����
 bit[16]     rficָ�����Ч��ʽ��1��ʾ������Ч��0��ʾ����Acitive Timing��ָʾʱ��λ����Ч
 bit[15:11]  ����
 bit[10:0]   rficָ�����Чʱ�̣�����S����Ϊ0ʱ��Ч������������Ϊϵͳʱ���Ӧ��λ�ã���ʱģ����Ҫ�������������ѡȡ��ǰ������ϵͳʱ�������ǰ�˿���ģ�飬����Ϊchip��CBBP�������������붨ʱģ������ľ���ʱ����бȽϣ�����ڶ��������
             ������Ȼ����þ���ʱ��С�ڶ�ʱ����ʱ��ʱ�����ȡ����Buffer���ݣ������ͣ�
             ���þ���ʱ�겻���ڶ�ʱ����ʱ�꣬������ȴ���
   UNION�ṹ:  CBBP_RFIC_SSI_CTRL_RAM_UNION */
#define CBBP_RFIC_SSI_CTRL_RAM_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xF800)
#define CBBP_RFIC_SSI_CTRL_RAM_MEMDEPTH  (16)

/* �Ĵ���˵����ƹ��RAM
 bit[31:25]  ����
 bit[24]     WR RF SSI��д��־��1��ʾ����0��ʾд
 bit[23:16]  Addr RF SSI��ַ��Ϣ
 bit[15:0]   �ò�����2�ֿ��ܵĸ�ʽ
             1��д��ʽ��[15:0]Data RF SSIд����ʱ��������Ϣ
             2) ����ʽ��
             [15:12]Buf Addr,��RF SSI������ʱ�ض��������Buffer��Ӧ��λ�ã��û���Bufferλ�ڹ���ǰ��ģ�飬��bbp_comm_fe
             [11]E RF SSI������ʱ������ָʾ���һ����������1��Ч��
             [10:0]����
   UNION�ṹ:  CBBP_RFIC_SSI_DATA_RAM_UNION */
#define CBBP_RFIC_SSI_DATA_RAM_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xF840)
#define CBBP_RFIC_SSI_DATA_RAM_MEMDEPTH  (112)

/* �Ĵ���˵����ƹ��RAM��ctrlָ����������16��
 bit[31:26]  ����
 bit[25:24]  ��������ָ���Ӧ��mipi����ָ��ĸ�����2bit��0~3��Ӧ���ø���Ϊ0~3����0��ʾ������
 bit[23:17]  ����
 bit[16]     mipiָ����Ч��ʽ��1��ʾ������Ч��0��ʾ����Acitive Timing��ָʾʱ��λ����Ч
 bit[15:11]  ����
 bit[10:0]   mipiָ����Чʱ�̣�����S����Ϊ0ʱ��Ч������������Ϊϵͳʱ���Ӧ��λ�ã���ʱģ����Ҫ�������������ѡȡ��ǰ������ϵͳʱ�������ǰ�˿���ģ�飬����Ϊchip��CBBP�������������붨ʱģ������ľ���ʱ����бȽϣ�����ڶ��������
             ������Ȼ����þ���ʱ��С�ڶ�ʱ����ʱ��ʱ�����ȡ����Buffer���ݣ������ͣ�
             ���þ���ʱ�겻���ڶ�ʱ����ʱ�꣬������ȴ���
   UNION�ṹ:  CBBP_MIPI_CTRL_RAM_UNION */
#define CBBP_MIPI_CTRL_RAM_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0xFA00)
#define CBBP_MIPI_CTRL_RAM_MEMDEPTH  (16)

/* �Ĵ���˵����ƹ��RAM
   ��      ����MIPIָ������ݻ���������96�У���ʽ���ӿ�˵����
   UNION�ṹ ���� */
#define CBBP_MIPI_DATA_RAM_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0xFA40)
#define CBBP_MIPI_DATA_RAM_MEMDEPTH  (96)

/* �Ĵ���˵����ƹ��RAM��ctrlָ����������32��
 bit[31:25]  GPIOһ��64����ַ,����ctrl_buff��data_buff��ַ��������1:1���䣬���ݸ�ʽ���ӿ�˵���顣����Ҫʹ�õĵ�ַ�����㡣Data��bit����ͬGPIO_FORCE_DATA�Ĵ���������
 bit[24]     ��������ָ���Ӧ��GPIO����ָ��ĸ�����1bit��1��Ӧ���ø���Ϊ1��0��ʾ������
 bit[23:17]  ����
 bit[16]     GPIOָ�����Ч��ʽ��1��ʾ������Ч��0��ʾ����Acitive Timing��ָʾʱ��λ����Ч
 bit[15:11]  ����
 bit[10:0]   GPIOָ�����Чʱ�̣�����S����Ϊ0ʱ��Ч������������Ϊϵͳʱ���Ӧ��λ�ã���ʱģ����Ҫ�������������ѡȡ��ǰ������ϵͳʱ�������ǰ�˿���ģ�飬����Ϊchip��CBBP�������������붨ʱģ������ľ���ʱ����бȽϣ�����ڶ��������
             ������Ȼ����þ���ʱ��С�ڶ�ʱ����ʱ��ʱ�����ȡ����Buffer���ݣ������ͣ�
             ���þ���ʱ�겻���ڶ�ʱ����ʱ�꣬������ȴ���
   UNION�ṹ:  CBBP_GPIO_CTRL_RAM_UNION */
#define CBBP_GPIO_CTRL_RAM_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0xFC00)
#define CBBP_GPIO_CTRL_RAM_MEMDEPTH  (32)

/* �Ĵ���˵����ƹ��RAM
 bit[31]     Ϊ0ʱ����ʾ�����߿�ant_pa_sel����
             Ϊ1ʱ��ʾר���߿أ�ÿ��bit�ĺ���������bit[6:0]����
 bit[30:0]   �߿���������
   UNION�ṹ:  CBBP_GPIO_DATA_RAM_UNION */
#define CBBP_GPIO_DATA_RAM_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0xFC80)
#define CBBP_GPIO_DATA_RAM_MEMDEPTH  (32)

/* �Ĵ���˵����ctrlָ����������16��
 bit[31:25]  ����
 bit[24]     ��������ָ���Ӧ��GPIO����ָ��ĸ�����3bit��0~7��Ӧ���ø���Ϊ0~7����0��ʾ������
 bit[23:17]  ����
 bit[16]     hkadcָ�����Ч��ʽ��1��ʾ������Ч��0��ʾ����Acitive Timing��ָʾʱ��λ����Ч
 bit[15:11]  ����
 bit[10:0]   hkadcָ�����Чʱ�̣�����S����Ϊ0ʱ��Ч������������Ϊϵͳʱ���Ӧ��λ�ã���ʱģ����Ҫ�������������ѡȡ��ǰ������ϵͳʱ�������ǰ�˿���ģ�飬����Ϊchip��CBBP�������������붨ʱģ������ľ���ʱ����бȽϣ�����ڶ��������
             ������Ȼ����þ���ʱ��С�ڶ�ʱ����ʱ��ʱ�����ȡ����Buffer���ݣ������ͣ�
             ���þ���ʱ�겻���ڶ�ʱ����ʱ�꣬������ȴ���
   UNION�ṹ:  CBBP_HKADC_SSI_CTRL_RAM_UNION */
#define CBBP_HKADC_SSI_CTRL_RAM_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0xFD00)
#define CBBP_HKADC_SSI_CTRL_RAM_MEMDEPTH  (64)

/* �Ĵ���˵����
 bit[31:17]  ����
 bit[16]     ����ָ������ͣ�0��ʾΪHKADC SSI����ָ�1��ʾΪHKADCͨ���������ָ��
 bit[15:0]   �ò�����3�ֿ��ܵĸ�ʽ���ֱ����£�
             1. ��hkadc_cfg_type=0ʱ�����bit[15]=0,��ʾд������[14:8]Ϊд��ַ��[7:0]Ϊд����
             2. ��hkadc_cfg_type=0ʱ�����bit[15]=1,��ʾ��������[14:8]Ϊд��ַ��[7:3]��ʾHKADC SSI������ʱ�ض��������Buffer��Ӧ��λ�ã��û���Bufferλ�ڱ�ģ���ڲ�����������С����Ϊ32
             [2]HKADC SSI������ʱ������ָʾ���һ����������1��Ч������bit��Ч��ǰ�˿���ģ���ڱ���HKADC SSI��������ɺ�����ж��ϱ������������ȡHKADC SSI�ض����
             3. ��hkadc_cfg_type=1ʱ�����bit[15]=0,��ʾHKADCͨ���������ָ�[15:1]Ϊ����λ��[0]Ϊ�����Ƿ���Ч
   UNION�ṹ:  CBBP_HKADC_SSI_DATA_RAM_UNION */
#define CBBP_HKADC_SSI_DATA_RAM_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0xFE00)
#define CBBP_HKADC_SSI_DATA_RAM_MEMDEPTH  (64)



/***======================================================================***
                     (18/20) register_define_sdr_gdrx_gauge
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31]     GDRXֹͣ���壬д1ֹͣ�������㣬д0�����塣
 bit[30]     ʱ��У׼ʹ�ܣ�д1�����������㣬д0�����塣
 bit[29:17]  ����
 bit[16:0]   ʱ��У׼32KHzʱ�Ӹ���
   UNION�ṹ:  CBBP_GDRX_GAUGE_EN_CNF_UNION */
#define CBBP_GDRX_GAUGE_EN_CNF_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xC000)

/* �Ĵ���˵����
 bit[31]     ˯��״̬��ѯ��1������˯�ߡ�
 bit[30]     ����״̬��ѯ��1�����ڲ�����
 bit[29:28]  ����
 bit[27:0]   ʱ��У׼���������������104M�Ӹ���
   UNION�ṹ:  CBBP_GAUGE_RESULT_RPT_UNION */
#define CBBP_GAUGE_RESULT_RPT_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0xC004)

/* �Ĵ���˵����
 bit[31:13]  ����
 bit[12:0]   IMIʱ���ж��ϱ�ʱGTC��TDMA QB������������
   UNION�ṹ:  CBBP_IMI_INT_TDMA_QB_UNION */
#define CBBP_IMI_INT_TDMA_QB_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xC008)

/* �Ĵ���˵����
 bit[31:13]  ����
 bit[12:0]   32Kʱ���ж��ϱ�ʱGTC��TDMA QB������������
   UNION�ṹ:  CBBP_SLEEP_INT_TDMA_QB_UNION */
#define CBBP_SLEEP_INT_TDMA_QB_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xC00C)



/***======================================================================***
                     (19/20) register_define_sdr_g_timing
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31:9]   ����
 bit[8]      1��ʾDRX����ģʽʹ�ܣ���ʱGTCʱ��Ӧ���رգ�����DRX���Ѻ�Ķ�ʱά������ıȶԡ�����ʹ���¸��ź�Ӧ�ñ���0��������
 bit[7:0]    ����
   UNION�ṹ:  CBBP_DRX_TEST_CFG_UNION */
#define CBBP_DRX_TEST_CFG_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0xC200)

/* �Ĵ���˵����
 bit[31:13]  ����
 bit[12:0]   ֡�ж���TimeBaseʱ��ƫ���λqb��������
   UNION�ṹ:  CBBP_G2_GTC_FRM_OFFSET_RPT_UNION */
#define CBBP_G2_GTC_FRM_OFFSET_RPT_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0xC204)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:24]  ����֡��ά�������е�T3��ʼֵ���ò���ֵ��cpu_gtc_t1_cnt��
             cpu_gtc_t2_cnt��cpu_gtc_fn_low��cpu_gtc_fn_highһ������GTC�ڲ�֡��ά���Ĵ����ĳ�ʼ������GTC��TDMA֡�߽紦��Ч,����Ӧ����Ϊ��һ֡��֡�ŵ�T3ֵ
             
 bit[23:21]  ����
 bit[20:16]  ����֡��ά�������е�T2��ʼֵ���ò���ֵ��cpu_gtc_t1_cnt����GTC��TDMA֡�߽紦��Ч,����Ӧ����Ϊ��һ֡��֡��
             cpu_gtc_t3_cnt��cpu_gtc_fn_low��cpu_gtc_fn_highһ������GTC�ڲ�֡��ά���Ĵ����ĳ�ʼ������GTC��TDMA֡�߽紦��Ч,����Ӧ����Ϊ��һ֡��֡�ŵ�T2ֵ
             
 bit[15:11]  ����
 bit[10:0]   ����֡��ά�������е�T1��ʼֵ���ò���ֵ��cpu_gtc_t2_cnt��cpu_gtc_t3_cnt��
             cpu_gtc_fn_low��cpu_gtc_fn_highһ������GTC�ڲ�֡��ά���Ĵ����ĳ�ʼ������GTC��TDMA֡�߽紦��Ч,����Ӧ����Ϊ��һ֡��֡�ŵ�T1ֵ
   UNION�ṹ:  CBBP_G2_CPU_GTC_T1_T2_T3_CNG_UNION */
#define CBBP_G2_CPU_GTC_T1_T2_T3_CNG_ADDR             (SOC_BBP_CDMA_BASE_ADDR + 0xC208)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:24]  GTC�ڲ�ά����T3�������ϱ�
 bit[23:21]  ����
 bit[20:16]  GTC�ڲ�ά����T2�������ϱ�
 bit[15:11]  ����
 bit[10:0]   GTC�ڲ�ά����T1�������ϱ�
   UNION�ṹ:  CBBP_G2_GTC_T1_T2_T3_RPT_CPU_UNION */
#define CBBP_G2_GTC_T1_T2_T3_RPT_CPU_ADDR             (SOC_BBP_CDMA_BASE_ADDR + 0xC20C)

/* �Ĵ���˵����
 bit[31]     CPU���õ�cpu_gtc_frm_offset��cpu_gtc_frm_it_offset������Чָʾ�źţ��߼������㡣(��ͬ���ͼĴ������ܷ���ͬһ��ַ����)
 bit[30:29]  ����
 bit[28:16]  CPU���õ�gtc_frm_it_offset����
 bit[15:13]  ����
 bit[12:0]   CPU���õ�gtc_frm_offset����
   UNION�ṹ:  CBBP_G2_CPU_GTC_FRM_OFFSET_CFG_UNION */
#define CBBP_G2_CPU_GTC_FRM_OFFSET_CFG_ADDR           (SOC_BBP_CDMA_BASE_ADDR + 0xC210)

/* �Ĵ���˵����
 bit[31]     ֡�ų�ʼ���źţ�1��Ч���߼������㣬ֻ�е���ҪT1,T2,T3��fn_low��fn_high��д��󷽿ɶԸ�bit��1
 bit[30:27]  ����
 bit[26:16]  CPU����TDMA֡�Ÿ�λ0~2047ѭ����������λ�����󣬸�λ�ż�1��CPU���ú���GTC��TDMA֡�߽紦��Ч,����Ӧ����Ϊ��һ֡��֡��
 bit[15:11]  ����
 bit[10:0]   CPU���õ�TDMA֡�ŵ�λ0~26x51-1ѭ������, CPU���ú���GTC��TDMA֡�߽紦��Ч,����Ӧ����Ϊ��һ֡��֡��
   UNION�ṹ:  CBBP_G2_CPU_GTC_FN_CFG_UNION */
#define CBBP_G2_CPU_GTC_FN_CFG_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xC214)

/* �Ĵ���˵����
 bit[31:27]  ����
 bit[26:16]  GTC��ʱʵ��֡�Ÿ�λ
 bit[15:11]  ����
 bit[10:0]   GTC��ʱʵ��֡�ŵ�λ
   UNION�ṹ:  CBBP_G2_GTC_FN_RPT_UNION */
#define CBBP_G2_GTC_FN_RPT_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0xC218)

/* �Ĵ���˵����
 bit[31:29]  ����
 bit[28:16]  ����ʱ��QB�ϱ���������Χ0~4999����Ӧһ֡�ĳ��ȡ���ֵֻ�븴λʱ���йأ�������
 bit[15:13]  ����
 bit[12:0]   ��ǰʱ��TDMA��QB����ֵ
   UNION�ṹ:  CBBP_GTC_QB_RPT_UNION */
#define CBBP_GTC_QB_RPT_ADDR                          (SOC_BBP_CDMA_BASE_ADDR + 0xC21C)

/* �Ĵ���˵����
 bit[31:27]  ����
 bit[26:16]  ����ʱ��֡���ϱ�����ֵ�仯ʱ����gtc_timebase_qbΪ4999����������Χ0~2047��������
 bit[15:13]  ����
 bit[12:0]   ����ʱ��QB�ϱ���������Χ0~4999����Ӧһ֡�ĳ��ȡ���ֵֻ�븴λʱ���йأ�������
   UNION�ṹ:  CBBP_TIMEBASE_RPT_UNION */
#define CBBP_TIMEBASE_RPT_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0xC220)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:0]   [0] TDMA֡�ж�����1��ʾ�ж�����0��ʾ���ж�������ͬ
             [1] GTC PAGE�ж�����
             [2] ͬ�������ж�����
             [3] ���������ϱ��ж�����
             [4] ʱ϶0�ж�����1��Ч
             [5] ʱ϶1�ж�����
             [6] ʱ϶2�ж�����
             [7] ʱ϶3�ж�����
             [8] ʱ϶4�ж�����
             [9] ʱ϶5�ж�����
             [10] ʱ϶6�ж�����
             [11] ʱ϶7�ж�����
             [12] �ɱ���ж�0����
             [13] �ɱ���ж�1����
             [14] �ɱ���ж�2����
             [15] �ɱ���ж�3����
             [16] �ɱ���ж�4����
             [17] �ɱ���ж�5����
             [18] �ɱ���ж�6����
             [19] �ɱ���ж�7����
             [23:20]����
             [24] ʱ�Ӳ����ж�
             [28] ��ƽ���������ж�
             [29] ��������ж�
   UNION�ṹ:  CBBP_G2_CPU_INT_STA_UNION */
#define CBBP_G2_CPU_INT_STA_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xC224)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:0]   [0] TDMA֡�ж������źţ�1��ʾ�ж��������Σ�0��ʾ���жϲ����Σ���ͬ
             [1] GTC PAGE�ж����μĴ���
             [2] ͬ�������ж����μĴ���
             [3] ���������ϱ��ж����μĴ���
             [4] ʱ϶0�ж����μĴ�����1��Ч
             [5] ʱ϶1�ж����μĴ���
             [6] ʱ϶2�ж����μĴ���
             [7] ʱ϶3�ж����μĴ���
             [8] ʱ϶4�ж����μĴ���
             [9] ʱ϶5�ж����μĴ���
             [10] ʱ϶6�ж����μĴ���
             [11] ʱ϶7�ж����μĴ���
             [12] �ɱ���ж�0���μĴ���
             [13] �ɱ���ж�1���μĴ���
             [14] �ɱ���ж�2���μĴ���
             [15] �ɱ���ж�3���μĴ���
             [16] �ɱ���ж�4���μĴ���
             [17] �ɱ���ж�5���μĴ���
             [18] �ɱ���ж�6���μĴ���
             [19] �ɱ���ж�7���μĴ���
             [24] ʱ�Ӳ����ж����μĴ���
             [28] ��ƽ���������ж����μĴ���
             [29] ��������ж����μĴ���
   UNION�ṹ:  CBBP_G2_CPU_INT_MASK_UNION */
#define CBBP_G2_CPU_INT_MASK_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xC228)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:0]   [0] TDMA֡�ж������źţ�1��ʾ�ж����������0��ʾ���жϲ����
             ����������ͬ
             [1] GTC PAGE�ж�����Ĵ���
             [2] ͬ�������ж������ź�
             [3] ���������ϱ��ж������ź�
             [4] ʱ϶0�ж������źţ�1��Ч
             [5] ʱ϶1�ж������ź�
             [6] ʱ϶2�ж������ź�
             [7] ʱ϶3�ж������ź�
             [8] ʱ϶4�ж������ź�
             [9] ʱ϶5�ж������ź�
             [10] ʱ϶6�ж������ź�
             [11] ʱ϶7�ж������ź�
             [12] �ɱ���ж�0�����ź�
             [13] �ɱ���ж�1�����ź�
             [14] �ɱ���ж�2�����ź�
             [15] �ɱ���ж�3�����ź�
             [16] �ɱ���ж�4�����ź�
             [17] �ɱ���ж�5�����ź�
             [18] �ɱ���ж�6�����ź�
             [19] �ɱ���ж�7�����ź�
             [24] ʱ�Ӳ����ж������ź�
             [28] ��ƽ���������ж������ź�
             [29] ��������ж������ź�
   UNION�ṹ:  CBBP_G2_CPU_INT_CLR_UNION */
#define CBBP_G2_CPU_INT_CLR_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xC22C)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:0]   [0] TDMA֡�ж�����1��ʾ�ж�����0��ʾ���ж�������ͬ
             [1] GTC PAGE�ж�����
             [2] ͬ�������ж�����
             [3] ���������ϱ��ж�����
             [4] ʱ϶0�ж�����1��Ч
             [5] ʱ϶1�ж�����
             [6] ʱ϶2�ж�����
             [7] ʱ϶3�ж�����
             [8] ʱ϶4�ж�����
             [9] ʱ϶5�ж�����
             [10] ʱ϶6�ж�����
             [11] ʱ϶7�ж�����
             [12] �ɱ���ж�0����
             [13] �ɱ���ж�1����
             [14] �ɱ���ж�2����
             [15] �ɱ���ж�3����
             [16] �ɱ���ж�4����
             [17] �ɱ���ж�5����
             [18] �ɱ���ж�6����
             [19] �ɱ���ж�7����
             [24] CTU��ϵͳ�����ж�0
             [25] CTU��ϵͳ�����ж�1
             [26] CTU��ϵͳ�����ж�2
             [27] ʱ�Ӳ����ж�
             [28] ��ƽ���������ж�
             [29]  ��������ж�
   UNION�ṹ:  CBBP_G2_DSP_INT_STA_UNION */
#define CBBP_G2_DSP_INT_STA_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xC230)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:0]   [0] TDMA֡�ж������źţ�1��ʾ�ж��������Σ�0��ʾ���жϲ�����
             [1] GTC PAGE�ж����μĴ���
             [2] ͬ�������ж����μĴ���
             [3] ���������ϱ��ж����μĴ���
             [4] ʱ϶0�ж����μĴ�����1��Ч
             [5] ʱ϶1�ж����μĴ���
             [6] ʱ϶2�ж����μĴ���
             [7] ʱ϶3�ж����μĴ���
             [8] ʱ϶4�ж����μĴ���
             [9] ʱ϶5�ж����μĴ���
             [10] ʱ϶6�ж����μĴ���
             [11] ʱ϶7�ж����μĴ���
             [12] �ɱ���ж�0���μĴ���
             [13] �ɱ���ж�1���μĴ���
             [14] �ɱ���ж�2���μĴ���
             [15] �ɱ���ж�3���μĴ���
             [16] �ɱ���ж�4���μĴ���
             [17] �ɱ���ж�5���μĴ���
             [18] �ɱ���ж�6���μĴ���
             [19] �ɱ���ж�7���μĴ���
             [24] CTU��ϵͳ�����ж�0
             [25] CTU��ϵͳ�����ж�1
             [26] CTU��ϵͳ�����ж�2
             [27] ʱ�Ӳ����ж�
             [28] ��ƽ���������ж����μĴ���
             [29] ��������ж����μĴ���
   UNION�ṹ:  CBBP_G2_DSP_INT_MASK_UNION */
#define CBBP_G2_DSP_INT_MASK_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xC234)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:0]   [0] TDMA֡�ж������źţ�1��ʾ�ж����������0��ʾ���жϲ����
             [1] GTC PAGE�ж�����Ĵ���
             [2] ͬ�������ж������ź�
             [3] ���������ϱ��ж������ź�
             [4] ʱ϶0�ж������źţ�1��Ч
             [5] ʱ϶1�ж������ź�
             [6] ʱ϶2�ж������ź�
             [7] ʱ϶3�ж������ź�
             [8] ʱ϶4�ж������ź�
             [9] ʱ϶5�ж������ź�
             [10] ʱ϶6�ж������ź�
             [11] ʱ϶7�ж������ź�
             [12] �ɱ���ж�0�����ź�
             [13] �ɱ���ж�1�����ź�
             [14] �ɱ���ж�2�����ź�
             [15] �ɱ���ж�3�����ź�
             [16] �ɱ���ж�4�����ź�
             [17] �ɱ���ж�5�����ź�
             [18] �ɱ���ж�6�����ź�
             [19] �ɱ���ж�7�����ź�
             [23:20]����
             [24] CTU��ϵͳ�����ж�0
             [25] CTU��ϵͳ�����ж�1
             [26] CTU��ϵͳ�����ж�2
             [27] ʱ�Ӳ����ж�
             [28] ��ƽ���������ж������ź�
             [29] ��������ж������ź�
   UNION�ṹ:  CBBP_G2_DSP_INT_CLR_UNION */
#define CBBP_G2_DSP_INT_CLR_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xC238)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  G�������ö�ʱ�ж�mask��
             bit16��1��ʾ����tdma֡��ʱ϶0���жϣ�
             bit17��1��ʾ����tdma֡��ʱ϶1���жϣ�
             ��
 bit[15:10]  ����
 bit[9:0]    G�������ö�ʱ�ж�ʱ϶��λ�ã�ȡֵ��Χ0~624����λQb
   UNION�ṹ:  CBBP_TDMA_SLOT_INT1_UNION */
#define CBBP_TDMA_SLOT_INT1_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xC240)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  G�������ö�ʱ�ж�mask��
             bit16��1��ʾ����tdma֡��ʱ϶0���жϣ�
             bit17��1��ʾ����tdma֡��ʱ϶1���жϣ�
             ��
 bit[15:10]  ����
 bit[9:0]    G�������ö�ʱ�ж�ʱ϶��λ�ã�ȡֵ��Χ0~624����λQb
   UNION�ṹ:  CBBP_TDMA_SLOT_INT2_UNION */
#define CBBP_TDMA_SLOT_INT2_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xC244)

/* �Ĵ���˵����
 bit[31:13]  ����
 bit[12:0]   ����˯��ģʽ�£�˯����ʼQbʱ�̣�TDMA��ʱ�̣��ò����ǻ���TDMAʱ��gtc_tdma_qb�ġ�
   UNION�ṹ:  CBBP_GDRX_SLEEP_POINT_UNION */
#define CBBP_GDRX_SLEEP_POINT_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0xC248)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9:0]    DRX�����Ż���ON����OFF����������λQb��Ĭ��ֵ16
   UNION�ṹ:  CBBP_CPU_TRANS_COMP_UNION */
#define CBBP_CPU_TRANS_COMP_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xC24C)



/***======================================================================***
                     (20/20) register_define_sdr_g_int
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      �͸�DSP��g���ж�ʹ�ܣ�1��ʾ���ж�
   UNION�ṹ:  CBBP_DSP_SDR_G_INT_EN_UNION */
#define CBBP_DSP_SDR_G_INT_EN_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0xC400)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    �ж������źţ��������1�������Ӧ��bit
             bit0��������g��ʱ�ж�1��
             bit1��������g��ʱ�ж�2��
             
   UNION�ṹ:  CBBP_DSP_SDR_G_INT_CLR_UNION */
#define CBBP_DSP_SDR_G_INT_CLR_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xC404)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    �ж�mask�źţ��������1����Ӧ��bit�жϲ�����
             bit0��������g��ʱ�ж�1��
             bit1��������g��ʱ�ж�2��
             
   UNION�ṹ:  CBBP_DSP_SDR_G_INT_MASK_UNION */
#define CBBP_DSP_SDR_G_INT_MASK_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0xC408)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    �ж�״̬�źţ�1��ʾ��Ӧ���ж��ϱ�
             bit0��������g��ʱ�ж�1��
             bit1��������g��ʱ�ж�2��
             
   UNION�ṹ:  CBBP_DSP_SDR_G_INT_STA_UNION */
#define CBBP_DSP_SDR_G_INT_STA_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xC40C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      �͸�ARM��g���ж�ʹ�ܣ�1��ʾ���ж�
   UNION�ṹ:  CBBP_ARM_SDR_G_INT_EN_UNION */
#define CBBP_ARM_SDR_G_INT_EN_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0xC410)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ARM�ж������źţ��������1�������Ӧ��bit
             bit0��������g��ʱ�ж�1��
             bit1��������g��ʱ�ж�2��
             
   UNION�ṹ:  CBBP_ARM_SDR_G_INT_CLR_UNION */
#define CBBP_ARM_SDR_G_INT_CLR_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xC414)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ARM�ж�mask�źţ��������1����Ӧ��bit�жϲ�����
             bit0��������g��ʱ�ж�1��
             bit1��������g��ʱ�ж�2��
             
   UNION�ṹ:  CBBP_ARM_SDR_G_INT_MASK_UNION */
#define CBBP_ARM_SDR_G_INT_MASK_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0xC418)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ARM�ж�״̬�źţ�1��ʾ��Ӧ���ж��ϱ�
             bit0��������g��ʱ�ж�1��
             bit1��������g��ʱ�ж�2��
             
   UNION�ṹ:  CBBP_ARM_SDR_G_INT_STA_UNION */
#define CBBP_ARM_SDR_G_INT_STA_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xC41C)





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
                     (1/20) register_define_c_glb
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : CBBP_VIRAGE_RM_CTRL_C_0_UNION
 �ṹ˵��  : VIRAGE_RM_CTRL_C_0 �Ĵ����ṹ���塣��ַƫ����:0x00����ֵ:0x03501050�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      virage_rm_ctrl_c_0_reg;
    struct
    {
        unsigned long  mem_ctrl_s_c      : 16; /* bit[0-15] : ����RAM��ʱ���ơ� */
        unsigned long  mem_ctrl_d_1w2r_c : 16; /* bit[16-31]: 1w2r˫��RAM��ʱ���ơ� */
    } reg;
} CBBP_VIRAGE_RM_CTRL_C_0_UNION;
#define CBBP_VIRAGE_RM_CTRL_C_0_mem_ctrl_s_c_START       (0)
#define CBBP_VIRAGE_RM_CTRL_C_0_mem_ctrl_s_c_END         (15)
#define CBBP_VIRAGE_RM_CTRL_C_0_mem_ctrl_d_1w2r_c_START  (16)
#define CBBP_VIRAGE_RM_CTRL_C_0_mem_ctrl_d_1w2r_c_END    (31)


/*****************************************************************************
 �ṹ��    : CBBP_VIRAGE_RM_CTRL_C_1_UNION
 �ṹ˵��  : VIRAGE_RM_CTRL_C_1 �Ĵ����ṹ���塣��ַƫ����:0x04����ֵ:0x00700057�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      virage_rm_ctrl_c_1_reg;
    struct
    {
        unsigned long  mem_ctrl_d_1rw2rw_c : 16; /* bit[0-15] : 1rw2rw˫��RAM��ʱ���ơ� */
        unsigned long  rom_ctrl_c          : 8;  /* bit[16-23]: ROM��ʱ���ơ� */
        unsigned long  reserved            : 8;  /* bit[24-31]: ���� */
    } reg;
} CBBP_VIRAGE_RM_CTRL_C_1_UNION;
#define CBBP_VIRAGE_RM_CTRL_C_1_mem_ctrl_d_1rw2rw_c_START  (0)
#define CBBP_VIRAGE_RM_CTRL_C_1_mem_ctrl_d_1rw2rw_c_END    (15)
#define CBBP_VIRAGE_RM_CTRL_C_1_rom_ctrl_c_START           (16)
#define CBBP_VIRAGE_RM_CTRL_C_1_rom_ctrl_c_END             (23)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_RST_CTRL_C_UNION
 �ṹ˵��  : SYS_RST_CTRL_C �Ĵ����ṹ���塣��ַƫ����:0x08����ֵ:0x007F0000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_rst_ctrl_c_reg;
    struct
    {
        unsigned long  sys_rst_ctrl_c_timing       : 1;  /* bit[0]    : ϵͳʱ����RST���ơ��ڶԸ�ģ����и�λʱ������Ӧbit��1��֮���ٽ���Ӧbit��λΪ0��
                                                                        ��ʱģ�顣 */
        unsigned long  sys_rst_ctrl_c_intr         : 1;  /* bit[1]    : �ж�ģ�顣 */
        unsigned long  sys_rst_ctrl_c_srch         : 1;  /* bit[2]    : ��������ģ�顣 */
        unsigned long  sys_rst_ctrl_c_dldec        : 1;  /* bit[3]    : ����ģ�顣 */
        unsigned long  sys_rst_ctrl_c_ulcode       : 1;  /* bit[4]    : ����ģ�顣 */
        unsigned long  sys_rst_ctrl_c_fe_sdr_if    : 1;  /* bit[5]    : ǰ�����ݽӿ�ģ�顣 */
        unsigned long  sys_rst_ctrl_c_fe_ctrl      : 1;  /* bit[6]    : ��Ƶǰ�˿���ģ�顣 */
        unsigned long  sys_rst_ctrl_sdr_gdrx_gauge : 1;  /* bit[7]    : G��ʱ�Ӳ��� */
        unsigned long  sys_rst_ctrl_sdr_g_timing   : 1;  /* bit[8]    : G����ʱ */
        unsigned long  sys_rst_ctrl_sdr_g_int      : 1;  /* bit[9]    : G���ж� */
        unsigned long  sys_rst_ctrl_sdr_g_fe_abb   : 1;  /* bit[10]   : G��ǰ������ */
        unsigned long  reserved_0                  : 5;  /* bit[11-15]: ���� */
        unsigned long  sys_clk_ctrl_c_timing       : 1;  /* bit[16]   : ϵͳʱ����CLK���ơ��ڶԸ�ģ�����ʱ�ӿ���ʱ������Ӧbit��1��ʾ�򿪸�ģ���ʱ�ӣ���֮������Ӧbit��0��ʾ�رո�ģ���ʱ�ӡ�
                                                                        ��ʱģ�顣 */
        unsigned long  sys_clk_ctrl_c_intr         : 1;  /* bit[17]   : �ж�ģ�顣 */
        unsigned long  sys_clk_ctrl_c_srch         : 1;  /* bit[18]   : ��������ģ�顣 */
        unsigned long  sys_clk_ctrl_c_dldec        : 1;  /* bit[19]   : ����ģ�顣 */
        unsigned long  sys_clk_ctrl_c_ulcode       : 1;  /* bit[20]   : ����ģ�顣 */
        unsigned long  sys_clk_ctrl_c_fe_sdr_if    : 1;  /* bit[21]   : ǰ�����ݽӿ�ģ�顣 */
        unsigned long  sys_clk_ctrl_c_fe_ctrl      : 1;  /* bit[22]   : ��Ƶǰ�˿���ģ�顣 */
        unsigned long  sys_clk_ctrl_sdr_gdrx_gauge : 1;  /* bit[23]   : G��ʱ�Ӳ��� */
        unsigned long  sys_clk_ctrl_sdr_g_timing   : 1;  /* bit[24]   : G����ʱ */
        unsigned long  sys_clk_ctrl_sdr_g_int      : 1;  /* bit[25]   : G���ж� */
        unsigned long  sys_clk_ctrl_sdr_g_fe_abb   : 1;  /* bit[26]   : G��ǰ������ */
        unsigned long  reserved_1                  : 5;  /* bit[27-31]: ���� */
    } reg;
} CBBP_SYS_RST_CTRL_C_UNION;
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_c_timing_START        (0)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_c_timing_END          (0)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_c_intr_START          (1)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_c_intr_END            (1)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_c_srch_START          (2)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_c_srch_END            (2)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_c_dldec_START         (3)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_c_dldec_END           (3)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_c_ulcode_START        (4)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_c_ulcode_END          (4)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_c_fe_sdr_if_START     (5)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_c_fe_sdr_if_END       (5)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_c_fe_ctrl_START       (6)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_c_fe_ctrl_END         (6)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_sdr_gdrx_gauge_START  (7)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_sdr_gdrx_gauge_END    (7)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_sdr_g_timing_START    (8)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_sdr_g_timing_END      (8)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_sdr_g_int_START       (9)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_sdr_g_int_END         (9)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_sdr_g_fe_abb_START    (10)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_sdr_g_fe_abb_END      (10)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_c_timing_START        (16)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_c_timing_END          (16)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_c_intr_START          (17)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_c_intr_END            (17)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_c_srch_START          (18)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_c_srch_END            (18)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_c_dldec_START         (19)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_c_dldec_END           (19)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_c_ulcode_START        (20)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_c_ulcode_END          (20)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_c_fe_sdr_if_START     (21)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_c_fe_sdr_if_END       (21)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_c_fe_ctrl_START       (22)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_c_fe_ctrl_END         (22)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_sdr_gdrx_gauge_START  (23)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_sdr_gdrx_gauge_END    (23)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_sdr_g_timing_START    (24)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_sdr_g_timing_END      (24)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_sdr_g_int_START       (25)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_sdr_g_int_END         (25)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_sdr_g_fe_abb_START    (26)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_sdr_g_fe_abb_END      (26)


/*****************************************************************************
 �ṹ��    : CBBP_IMI_RST_CTRL_C_UNION
 �ṹ˵��  : IMI_RST_CTRL_C �Ĵ����ṹ���塣��ַƫ����:0x0C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      imi_rst_ctrl_c_reg;
    struct
    {
        unsigned long  imi_rst_ctrl_c_timing        : 1;  /* bit[0]    : IMIʱ����RST���ơ��ڶԸ�ģ����и�λʱ������Ӧbit��1��֮���ٽ���Ӧbit��λΪ0��
                                                                         ��ʱģ�顣 */
        unsigned long  imi_rst_ctrl_c_intr          : 1;  /* bit[1]    : �ж�ģ�顣 */
        unsigned long  imi_rst_ctrl_c_srch          : 1;  /* bit[2]    : ��������ģ�顣 */
        unsigned long  imi_rst_ctrl_c_dldec         : 1;  /* bit[3]    : ����ģ�顣 */
        unsigned long  imi_rst_ctrl_c_ulcode        : 1;  /* bit[4]    : ����ģ�顣 */
        unsigned long  imi_rst_ctrl_c_fe_sdr_if     : 1;  /* bit[5]    : ǰ�����ݽӿ�ģ�顣 */
        unsigned long  imi_rst_ctrl_c_fe_ctrl       : 1;  /* bit[6]    : ��Ƶǰ�˿���ģ�顣 */
        unsigned long  imi_rst_ctrl_sdr_gdrx_gauge  : 1;  /* bit[7]    : G��ʱ�Ӳ��� */
        unsigned long  imi_rst_ctrl_sdr_g_timing    : 1;  /* bit[8]    : G����ʱ */
        unsigned long  imi_rst_ctrl_sdr_g_int       : 1;  /* bit[9]    : G���ж� */
        unsigned long  reserved_0                   : 6;  /* bit[10-15]: ���� */
        unsigned long  imi_addr_ctrl_c_timing       : 1;  /* bit[16]   : IMI��ַƬѡ��������ʹ�ܣ��ߵ�ƽ��Ч�����ź���Ч��ʾ��Ӧģ��δ��ѡ��ʱ����BBP�ڲ���ģ��IMI��ַ��
                                                                         ��ʱģ�顣 */
        unsigned long  imi_addr_ctrl_c_intr         : 1;  /* bit[17]   : �ж�ģ�顣 */
        unsigned long  imi_addr_ctrl_c_srch         : 1;  /* bit[18]   : ��������ģ�顣 */
        unsigned long  imi_addr_ctrl_c_dldec        : 1;  /* bit[19]   : ����ģ�顣 */
        unsigned long  imi_addr_ctrl_c_ulcode       : 1;  /* bit[20]   : ����ģ�顣 */
        unsigned long  imi_addr_ctrl_c_fe_sdr_if    : 1;  /* bit[21]   : ǰ�����ݽӿ�ģ�顣 */
        unsigned long  imi_addr_ctrl_c_fe_ctrl      : 1;  /* bit[22]   : ��Ƶǰ�˿���ģ�顣 */
        unsigned long  imi_addr_ctrl_sdr_gdrx_gauge : 1;  /* bit[23]   : G��ʱ�Ӳ��� */
        unsigned long  imi_addr_ctrl_sdr_g_timing   : 1;  /* bit[24]   : G����ʱ */
        unsigned long  imi_addr_ctrl_sdr_g_int      : 1;  /* bit[25]   : G���ж� */
        unsigned long  reserved_1                   : 6;  /* bit[26-31]: ���� */
    } reg;
} CBBP_IMI_RST_CTRL_C_UNION;
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_c_timing_START         (0)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_c_timing_END           (0)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_c_intr_START           (1)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_c_intr_END             (1)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_c_srch_START           (2)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_c_srch_END             (2)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_c_dldec_START          (3)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_c_dldec_END            (3)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_c_ulcode_START         (4)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_c_ulcode_END           (4)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_c_fe_sdr_if_START      (5)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_c_fe_sdr_if_END        (5)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_c_fe_ctrl_START        (6)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_c_fe_ctrl_END          (6)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_sdr_gdrx_gauge_START   (7)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_sdr_gdrx_gauge_END     (7)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_sdr_g_timing_START     (8)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_sdr_g_timing_END       (8)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_sdr_g_int_START        (9)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_sdr_g_int_END          (9)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_c_timing_START        (16)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_c_timing_END          (16)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_c_intr_START          (17)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_c_intr_END            (17)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_c_srch_START          (18)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_c_srch_END            (18)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_c_dldec_START         (19)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_c_dldec_END           (19)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_c_ulcode_START        (20)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_c_ulcode_END          (20)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_c_fe_sdr_if_START     (21)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_c_fe_sdr_if_END       (21)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_c_fe_ctrl_START       (22)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_c_fe_ctrl_END         (22)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_sdr_gdrx_gauge_START  (23)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_sdr_gdrx_gauge_END    (23)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_sdr_g_timing_START    (24)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_sdr_g_timing_END      (24)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_sdr_g_int_START       (25)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_sdr_g_int_END         (25)


/***======================================================================***
                     (2/20) register_define_c_timing
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : CBBP_C_CK_MSR_PERIOD_UNION
 �ṹ˵��  : C_CK_MSR_PERIOD �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      c_ck_msr_period_reg;
    struct
    {
        unsigned long  c_ck_msr_period : 18; /* bit[0-17] : ʱ�Ӳ���ʱ�䣬32kʱ�Ӹ������֧��5.12s��
                                                            ˵����ȡֵΪ0�����塣 */
        unsigned long  reserved        : 14; /* bit[18-31]: ���� */
    } reg;
} CBBP_C_CK_MSR_PERIOD_UNION;
#define CBBP_C_CK_MSR_PERIOD_c_ck_msr_period_START  (0)
#define CBBP_C_CK_MSR_PERIOD_c_ck_msr_period_END    (17)


/*****************************************************************************
 �ṹ��    : CBBP_C_CK_MSR_EN_UNION
 �ṹ˵��  : C_CK_MSR_EN �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      c_ck_msr_en_reg;
    struct
    {
        unsigned long  c_ck_msr_en : 1;  /* bit[0]   : ʱ�Ӳ���ʹ�ܡ�BBP��������أ�����ʱ�Ӳ���������������Ϊ0��BBPֹͣʱ�Ӳ����� */
        unsigned long  reserved    : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_C_CK_MSR_EN_UNION;
#define CBBP_C_CK_MSR_EN_c_ck_msr_en_START  (0)
#define CBBP_C_CK_MSR_EN_c_ck_msr_en_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_CK_MSR_RPT_UNION
 �ṹ˵��  : CK_MSR_RPT �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ck_msr_rpt_reg;
    struct
    {
        unsigned long  ck_msr_rpt : 31; /* bit[0-30]: ʱ�Ӳ���������ϱ�����ck_msr_period�ڵ�122.88MHzʱ�Ӹ��� */
        unsigned long  reserved   : 1;  /* bit[31]  : ���� */
    } reg;
} CBBP_CK_MSR_RPT_UNION;
#define CBBP_CK_MSR_RPT_ck_msr_rpt_START  (0)
#define CBBP_CK_MSR_RPT_ck_msr_rpt_END    (30)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_1X_GET_POS_UNION
 �ṹ˵��  : SYS_CNT_1X_GET_POS �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_1x_get_pos_reg;
    struct
    {
        unsigned long  sys_cnt_1x_get_pos_1_4chip : 5;  /* bit[0-4]  : ����sys_cnt_1x��ʱ�̣�
                                                                       [28:24]��base_cnt_2s�ϵ�ʱ�̣�ȡֵ��Χ0~24��
                                                                       [23:22]��base_cnt_80ms�ϵ�ʱ�̣�ȡֵ��Χ0~2��
                                                                       [21:5]��base_cnt_26ms�ϵ�ʱ�̣�ȡֵ��Χ0~32768*4-1��
                                                                       [4:0]��1/4chip�ڼ�����ȡֵ��Χ0~24 */
        unsigned long  sys_cnt_1x_get_pos_26ms    : 17; /* bit[5-21] :  */
        unsigned long  sys_cnt_1x_get_pos_80ms    : 2;  /* bit[22-23]:  */
        unsigned long  sys_cnt_1x_get_pos_2s      : 5;  /* bit[24-28]:  */
        unsigned long  reserved                   : 3;  /* bit[29-31]: ���� */
    } reg;
} CBBP_SYS_CNT_1X_GET_POS_UNION;
#define CBBP_SYS_CNT_1X_GET_POS_sys_cnt_1x_get_pos_1_4chip_START  (0)
#define CBBP_SYS_CNT_1X_GET_POS_sys_cnt_1x_get_pos_1_4chip_END    (4)
#define CBBP_SYS_CNT_1X_GET_POS_sys_cnt_1x_get_pos_26ms_START     (5)
#define CBBP_SYS_CNT_1X_GET_POS_sys_cnt_1x_get_pos_26ms_END       (21)
#define CBBP_SYS_CNT_1X_GET_POS_sys_cnt_1x_get_pos_80ms_START     (22)
#define CBBP_SYS_CNT_1X_GET_POS_sys_cnt_1x_get_pos_80ms_END       (23)
#define CBBP_SYS_CNT_1X_GET_POS_sys_cnt_1x_get_pos_2s_START       (24)
#define CBBP_SYS_CNT_1X_GET_POS_sys_cnt_1x_get_pos_2s_END         (28)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_1X_GET_VALUE_UNION
 �ṹ˵��  : SYS_CNT_1X_GET_VALUE �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_1x_get_value_reg;
    struct
    {
        unsigned long  sys_cnt_1x_get_value_1_4chip : 5;  /* bit[0-4]  : sys_cnt_get_posʱ��sys_cnt_1x��ֵ��
                                                                         [29:24]��sys_cnt_1x_5p12s��ֵ��
                                                                         [23:18]��sys_cnt_1x_80ms��ֵ��
                                                                         [17:5]��sys_cnt_1x_1p25ms��ֵ��ȡֵ��Χ0~1536*4-1��
                                                                         [4:0]��1/4chip�ڼ�����ȡֵ��Χ0~24 */
        unsigned long  sys_cnt_1x_get_value_26ms    : 13; /* bit[5-17] :  */
        unsigned long  sys_cnt_1x_get_value_80ms    : 6;  /* bit[18-23]:  */
        unsigned long  sys_cnt_1x_get_value_5p12s   : 6;  /* bit[24-29]:  */
        unsigned long  reserved                     : 2;  /* bit[30-31]: ���� */
    } reg;
} CBBP_SYS_CNT_1X_GET_VALUE_UNION;
#define CBBP_SYS_CNT_1X_GET_VALUE_sys_cnt_1x_get_value_1_4chip_START  (0)
#define CBBP_SYS_CNT_1X_GET_VALUE_sys_cnt_1x_get_value_1_4chip_END    (4)
#define CBBP_SYS_CNT_1X_GET_VALUE_sys_cnt_1x_get_value_26ms_START     (5)
#define CBBP_SYS_CNT_1X_GET_VALUE_sys_cnt_1x_get_value_26ms_END       (17)
#define CBBP_SYS_CNT_1X_GET_VALUE_sys_cnt_1x_get_value_80ms_START     (18)
#define CBBP_SYS_CNT_1X_GET_VALUE_sys_cnt_1x_get_value_80ms_END       (23)
#define CBBP_SYS_CNT_1X_GET_VALUE_sys_cnt_1x_get_value_5p12s_START    (24)
#define CBBP_SYS_CNT_1X_GET_VALUE_sys_cnt_1x_get_value_5p12s_END      (29)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_1X_80MS_POS_CFG_UNION
 �ṹ˵��  : SYS_CNT_1X_80MS_POS_CFG �Ĵ����ṹ���塣��ַƫ����:0x00C4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_1x_80ms_pos_cfg_reg;
    struct
    {
        unsigned long  sys_cnt_1x_80ms_pos_1_4chip_cfg : 5;  /* bit[0-4]  : 1X��ʱͻ���sys_cnt_1x  80ms֡ͷ��base_cnt�ϵ�λ�á�
                                                                            Bit[4:0]��1/4chip�ڼ���0~24
                                                                            bit[21:5]��26ms�ڼ���0~32768*4-1
                                                                            bit[23:22]��80ms�ڼ���0~2 */
        unsigned long  sys_cnt_1x_80ms_pos_26ms_cfg    : 17; /* bit[5-21] :  */
        unsigned long  sys_cnt_1x_80ms_pos_80ms_cfg    : 2;  /* bit[22-23]:  */
        unsigned long  reserved                        : 8;  /* bit[24-31]: ���� */
    } reg;
} CBBP_SYS_CNT_1X_80MS_POS_CFG_UNION;
#define CBBP_SYS_CNT_1X_80MS_POS_CFG_sys_cnt_1x_80ms_pos_1_4chip_cfg_START  (0)
#define CBBP_SYS_CNT_1X_80MS_POS_CFG_sys_cnt_1x_80ms_pos_1_4chip_cfg_END    (4)
#define CBBP_SYS_CNT_1X_80MS_POS_CFG_sys_cnt_1x_80ms_pos_26ms_cfg_START     (5)
#define CBBP_SYS_CNT_1X_80MS_POS_CFG_sys_cnt_1x_80ms_pos_26ms_cfg_END       (21)
#define CBBP_SYS_CNT_1X_80MS_POS_CFG_sys_cnt_1x_80ms_pos_80ms_cfg_START     (22)
#define CBBP_SYS_CNT_1X_80MS_POS_CFG_sys_cnt_1x_80ms_pos_80ms_cfg_END       (23)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_1X_GET_RDY_UNION
 �ṹ˵��  : SYS_CNT_1X_GET_RDY �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_1x_get_rdy_reg;
    struct
    {
        unsigned long  sys_cnt_1x_get_rdy : 1;  /* bit[0]   : Sys_cnt_1x��ʱ��ȡָʾ��
                                                              BBP���յ���ָʾ�󣬵ȴ�base_cnt��sys_cnt_1x_get_posʱ�̣���sys_cnt_1x����Ϊsys_cnt_1x_get_value�� */
        unsigned long  reserved           : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_SYS_CNT_1X_GET_RDY_UNION;
#define CBBP_SYS_CNT_1X_GET_RDY_sys_cnt_1x_get_rdy_START  (0)
#define CBBP_SYS_CNT_1X_GET_RDY_sys_cnt_1x_get_rdy_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_1X_CHANGE_DIRECTION_UNION
 �ṹ˵��  : SYS_1X_CHANGE_DIRECTION �Ĵ����ṹ���塣��ַƫ����:0x002C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_1x_change_direction_reg;
    struct
    {
        unsigned long  sys_1x_change_direction : 1;  /* bit[0]   : ϵͳ��ʱ��������
                                                                   0����ʾ����ߵ���6clk��
                                                                   1����ʾ���ұߵ���6clk��
                                                                   ˵������ʱ����100��ʱ�ӣ���ˣ�6clkʱ��Ϊ6/100chip */
        unsigned long  reserved                : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_SYS_1X_CHANGE_DIRECTION_UNION;
#define CBBP_SYS_1X_CHANGE_DIRECTION_sys_1x_change_direction_START  (0)
#define CBBP_SYS_1X_CHANGE_DIRECTION_sys_1x_change_direction_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_1X_CHANGE_RDY_UNION
 �ṹ˵��  : SYS_1X_CHANGE_RDY �Ĵ����ṹ���塣��ַƫ����:0x0030����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_1x_change_rdy_reg;
    struct
    {
        unsigned long  sys_1x_change_rdy : 1;  /* bit[0]   : ϵͳ��ʱ����ָʾ��
                                                             BBP�ڽ��յ���ָʾ���������PCG���ϵͳ��ʱ */
        unsigned long  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_SYS_1X_CHANGE_RDY_UNION;
#define CBBP_SYS_1X_CHANGE_RDY_sys_1x_change_rdy_START  (0)
#define CBBP_SYS_1X_CHANGE_RDY_sys_1x_change_rdy_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_1X_80MS_POS_RD_UNION
 �ṹ˵��  : SYS_CNT_1X_80MS_POS_RD �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_1x_80ms_pos_rd_reg;
    struct
    {
        unsigned long  sys_cnt_1x_80ms_pos_rd : 1;  /* bit[0]   : �����ȡsys_cnt_1x_80ms_pos��ָʾ��BBP���յ����źź����汾�صļ���ֵ */
        unsigned long  reserved               : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_SYS_CNT_1X_80MS_POS_RD_UNION;
#define CBBP_SYS_CNT_1X_80MS_POS_RD_sys_cnt_1x_80ms_pos_rd_START  (0)
#define CBBP_SYS_CNT_1X_80MS_POS_RD_sys_cnt_1x_80ms_pos_rd_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_1X_80MS_POS_UNION
 �ṹ˵��  : SYS_CNT_1X_80MS_POS �Ĵ����ṹ���塣��ַƫ����:0x0038����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_1x_80ms_pos_reg;
    struct
    {
        unsigned long  sys_cnt_1x_80ms_pos_1_4chip : 5;  /* bit[0-4]  : sys_cnt_1x  80ms֡ͷ��base_cnt�ϵ�λ�á�
                                                                        Bit[4:0]��1/4chip�ڼ���0~24
                                                                        bit[21:5]��26ms�ڼ���0~32768*4-1
                                                                        bit[23:22]��80ms�ڼ���0~2 */
        unsigned long  sys_cnt_1x_80ms_pos_26ms    : 17; /* bit[5-21] :  */
        unsigned long  sys_cnt_1x_80ms_pos_80ms    : 2;  /* bit[22-23]:  */
        unsigned long  sys_cnt_1x_80ms_pos_valid   : 1;  /* bit[24]   : sys_cnt_1x_80ms_pos��Чָʾ��1��ʾ��ȡ�Ľ����Ч */
        unsigned long  reserved                    : 7;  /* bit[25-31]: ���� */
    } reg;
} CBBP_SYS_CNT_1X_80MS_POS_UNION;
#define CBBP_SYS_CNT_1X_80MS_POS_sys_cnt_1x_80ms_pos_1_4chip_START  (0)
#define CBBP_SYS_CNT_1X_80MS_POS_sys_cnt_1x_80ms_pos_1_4chip_END    (4)
#define CBBP_SYS_CNT_1X_80MS_POS_sys_cnt_1x_80ms_pos_26ms_START     (5)
#define CBBP_SYS_CNT_1X_80MS_POS_sys_cnt_1x_80ms_pos_26ms_END       (21)
#define CBBP_SYS_CNT_1X_80MS_POS_sys_cnt_1x_80ms_pos_80ms_START     (22)
#define CBBP_SYS_CNT_1X_80MS_POS_sys_cnt_1x_80ms_pos_80ms_END       (23)
#define CBBP_SYS_CNT_1X_80MS_POS_sys_cnt_1x_80ms_pos_valid_START    (24)
#define CBBP_SYS_CNT_1X_80MS_POS_sys_cnt_1x_80ms_pos_valid_END      (24)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_1X_80MS_POS_VALID_CLR_UNION
 �ṹ˵��  : SYS_CNT_1X_80MS_POS_VALID_CLR �Ĵ����ṹ���塣��ַƫ����:0x003C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_1x_80ms_pos_valid_clr_reg;
    struct
    {
        unsigned long  sys_cnt_1x_80ms_pos_valid_clr : 1;  /* bit[0]   : sys_cnt_1x_80ms_pos_valid�����źţ������sys_cnt_1x_80ms_pos��ȡ��ʹ�ô˼Ĵ���������Ч��־��� */
        unsigned long  reserved                      : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_SYS_CNT_1X_80MS_POS_VALID_CLR_UNION;
#define CBBP_SYS_CNT_1X_80MS_POS_VALID_CLR_sys_cnt_1x_80ms_pos_valid_clr_START  (0)
#define CBBP_SYS_CNT_1X_80MS_POS_VALID_CLR_sys_cnt_1x_80ms_pos_valid_clr_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT_1X_MASK_UNION
 �ṹ˵��  : TIMING_INT_1X_MASK �Ĵ����ṹ���塣��ַƫ����:0x0040����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int_1x_mask_reg;
    struct
    {
        unsigned long  timing_int_1x_mask : 1;  /* bit[0]   : ��ʱͻ��ʱ����ʱ�жϵ�maskָʾ��
                                                              0����ʾ��mask��
                                                              1����ʾmask���÷�Χ�ڵ��жϣ� */
        unsigned long  reserved           : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_TIMING_INT_1X_MASK_UNION;
#define CBBP_TIMING_INT_1X_MASK_timing_int_1x_mask_START  (0)
#define CBBP_TIMING_INT_1X_MASK_timing_int_1x_mask_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT_1X_MASK_DIS_UNION
 �ṹ˵��  : TIMING_INT_1X_MASK_DIS �Ĵ����ṹ���塣��ַƫ����:0x0044����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int_1x_mask_dis_reg;
    struct
    {
        unsigned long  timing_int_1x_mask_dis : 11; /* bit[0-10] : ��ʱͻ��ʱ����ʱ�жϵ�mask���䣬chipΪ��λ�� */
        unsigned long  reserved               : 21; /* bit[11-31]: ���� */
    } reg;
} CBBP_TIMING_INT_1X_MASK_DIS_UNION;
#define CBBP_TIMING_INT_1X_MASK_DIS_timing_int_1x_mask_dis_START  (0)
#define CBBP_TIMING_INT_1X_MASK_DIS_timing_int_1x_mask_dis_END    (10)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT1_SYS_CNT_1X_POS_UNION
 �ṹ˵��  : TIMING_INT1_SYS_CNT_1X_POS �Ĵ����ṹ���塣��ַƫ����:0x0048����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int1_sys_cnt_1x_pos_reg;
    struct
    {
        unsigned long  timing_int1_sys_cnt_1x_1p25ms_pos : 11; /* bit[0-10] : Int1��sys_cnt_1x�ϵ�λ�ã�
                                                                              [21:16]��sys_cnt_1x_80ms��ֵ��
                                                                              [10:0]��sys_cnt_1x_1p25ms[15:5]��ֵ,chip���ȣ� */
        unsigned long  reserved_0                        : 5;  /* bit[11-15]: ���� */
        unsigned long  timing_int1_sys_cnt_1x_80ms_pos   : 6;  /* bit[16-21]:  */
        unsigned long  reserved_1                        : 10; /* bit[22-31]: ���� */
    } reg;
} CBBP_TIMING_INT1_SYS_CNT_1X_POS_UNION;
#define CBBP_TIMING_INT1_SYS_CNT_1X_POS_timing_int1_sys_cnt_1x_1p25ms_pos_START  (0)
#define CBBP_TIMING_INT1_SYS_CNT_1X_POS_timing_int1_sys_cnt_1x_1p25ms_pos_END    (10)
#define CBBP_TIMING_INT1_SYS_CNT_1X_POS_timing_int1_sys_cnt_1x_80ms_pos_START    (16)
#define CBBP_TIMING_INT1_SYS_CNT_1X_POS_timing_int1_sys_cnt_1x_80ms_pos_END      (21)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT1_1X_PERIOD_UNION
 �ṹ˵��  : TIMING_INT1_1X_PERIOD �Ĵ����ṹ���塣��ַƫ����:0x004C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int1_1x_period_reg;
    struct
    {
        unsigned long  timing_int1_1x_period : 4;  /* bit[0-3] : Int1�ж�����ѡ��
                                                                 0����ʾ�ж�����Ϊ64chip��
                                                                 1����ʾ�ж�����Ϊ128chip��
                                                                 2����ʾ�ж�����Ϊ256chip��
                                                                 3����ʾ�ж�����Ϊ512chip��
                                                                 4����ʾ�ж�����Ϊ1.25ms��
                                                                 5����ʾ�ж�����Ϊ5ms��
                                                                 6����ʾ�ж�����Ϊ10ms��
                                                                 7����ʾ�ж�����Ϊ20ms��
                                                                 8����ʾ�ж�����Ϊ40ms��
                                                                 9����ʾ�ж�����Ϊ80ms��
                                                                 10:��ʾ�ж�����Ϊ384chip�� */
        unsigned long  reserved              : 28; /* bit[4-31]: ���� */
    } reg;
} CBBP_TIMING_INT1_1X_PERIOD_UNION;
#define CBBP_TIMING_INT1_1X_PERIOD_timing_int1_1x_period_START  (0)
#define CBBP_TIMING_INT1_1X_PERIOD_timing_int1_1x_period_END    (3)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT1_1X_EN_UNION
 �ṹ˵��  : TIMING_INT1_1X_EN �Ĵ����ṹ���塣��ַƫ����:0x0050����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int1_1x_en_reg;
    struct
    {
        unsigned long  timing_int1_1x_en : 1;  /* bit[0]   : ��ʱ�ж�int1��ʹ�ܡ�
                                                             0����ʾ������int1�жϣ�
                                                             1����ʾ����int1�жϣ� */
        unsigned long  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_TIMING_INT1_1X_EN_UNION;
#define CBBP_TIMING_INT1_1X_EN_timing_int1_1x_en_START  (0)
#define CBBP_TIMING_INT1_1X_EN_timing_int1_1x_en_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT2_SYS_CNT_1X_POS_UNION
 �ṹ˵��  : TIMING_INT2_SYS_CNT_1X_POS �Ĵ����ṹ���塣��ַƫ����:0x0054����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int2_sys_cnt_1x_pos_reg;
    struct
    {
        unsigned long  timing_int2_sys_cnt_1x_1p25ms_pos : 11; /* bit[0-10] : Int��sys_cnt_1x�ϵ�λ�ã�
                                                                              [21:16]��sys_cnt_1x_80ms��ֵ��
                                                                              [10:0]��sys_cnt_1x_1p25ms[15:5]��ֵ,chip���ȣ� */
        unsigned long  reserved_0                        : 5;  /* bit[11-15]: ���� */
        unsigned long  timing_int2_sys_cnt_1x_80ms_pos   : 6;  /* bit[16-21]:  */
        unsigned long  reserved_1                        : 10; /* bit[22-31]: ���� */
    } reg;
} CBBP_TIMING_INT2_SYS_CNT_1X_POS_UNION;
#define CBBP_TIMING_INT2_SYS_CNT_1X_POS_timing_int2_sys_cnt_1x_1p25ms_pos_START  (0)
#define CBBP_TIMING_INT2_SYS_CNT_1X_POS_timing_int2_sys_cnt_1x_1p25ms_pos_END    (10)
#define CBBP_TIMING_INT2_SYS_CNT_1X_POS_timing_int2_sys_cnt_1x_80ms_pos_START    (16)
#define CBBP_TIMING_INT2_SYS_CNT_1X_POS_timing_int2_sys_cnt_1x_80ms_pos_END      (21)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT2_1X_PERIOD_UNION
 �ṹ˵��  : TIMING_INT2_1X_PERIOD �Ĵ����ṹ���塣��ַƫ����:0x0058����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int2_1x_period_reg;
    struct
    {
        unsigned long  timing_int2_1x_period : 4;  /* bit[0-3] : Int�ж�����ѡ��
                                                                 0����ʾ�ж�����Ϊ64chip��
                                                                 1����ʾ�ж�����Ϊ128chip��
                                                                 2����ʾ�ж�����Ϊ256chip��
                                                                 3����ʾ�ж�����Ϊ512chip��
                                                                 4����ʾ�ж�����Ϊ1.25ms��
                                                                 5����ʾ�ж�����Ϊ5ms��
                                                                 6����ʾ�ж�����Ϊ10ms��
                                                                 7����ʾ�ж�����Ϊ20ms��
                                                                 8����ʾ�ж�����Ϊ40ms��
                                                                 9����ʾ�ж�����Ϊ80ms��
                                                                 10:��ʾ�ж�����Ϊ384chip�� */
        unsigned long  reserved              : 28; /* bit[4-31]: ���� */
    } reg;
} CBBP_TIMING_INT2_1X_PERIOD_UNION;
#define CBBP_TIMING_INT2_1X_PERIOD_timing_int2_1x_period_START  (0)
#define CBBP_TIMING_INT2_1X_PERIOD_timing_int2_1x_period_END    (3)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT2_1X_EN_UNION
 �ṹ˵��  : TIMING_INT2_1X_EN �Ĵ����ṹ���塣��ַƫ����:0x005C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int2_1x_en_reg;
    struct
    {
        unsigned long  timing_int2_1x_en : 1;  /* bit[0]   : ��ʱ�ж�int��ʹ�ܡ�
                                                             0����ʾ������int�жϣ�
                                                             1����ʾ����int�жϣ� */
        unsigned long  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_TIMING_INT2_1X_EN_UNION;
#define CBBP_TIMING_INT2_1X_EN_timing_int2_1x_en_START  (0)
#define CBBP_TIMING_INT2_1X_EN_timing_int2_1x_en_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT3_SYS_CNT_1X_POS_UNION
 �ṹ˵��  : TIMING_INT3_SYS_CNT_1X_POS �Ĵ����ṹ���塣��ַƫ����:0x0060����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int3_sys_cnt_1x_pos_reg;
    struct
    {
        unsigned long  timing_int3_sys_cnt_1x_1p25ms_pos : 11; /* bit[0-10] : Int��sys_cnt_1x�ϵ�λ�ã�
                                                                              [21:16]��sys_cnt_1x_80ms��ֵ��
                                                                              [10:0]��sys_cnt_1x_1p25ms[15:5]��ֵ,chip���ȣ� */
        unsigned long  reserved_0                        : 5;  /* bit[11-15]: ���� */
        unsigned long  timing_int3_sys_cnt_1x_80ms_pos   : 6;  /* bit[16-21]:  */
        unsigned long  reserved_1                        : 10; /* bit[22-31]: ���� */
    } reg;
} CBBP_TIMING_INT3_SYS_CNT_1X_POS_UNION;
#define CBBP_TIMING_INT3_SYS_CNT_1X_POS_timing_int3_sys_cnt_1x_1p25ms_pos_START  (0)
#define CBBP_TIMING_INT3_SYS_CNT_1X_POS_timing_int3_sys_cnt_1x_1p25ms_pos_END    (10)
#define CBBP_TIMING_INT3_SYS_CNT_1X_POS_timing_int3_sys_cnt_1x_80ms_pos_START    (16)
#define CBBP_TIMING_INT3_SYS_CNT_1X_POS_timing_int3_sys_cnt_1x_80ms_pos_END      (21)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT3_1X_PERIOD_UNION
 �ṹ˵��  : TIMING_INT3_1X_PERIOD �Ĵ����ṹ���塣��ַƫ����:0x0064����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int3_1x_period_reg;
    struct
    {
        unsigned long  timing_int3_1x_period : 4;  /* bit[0-3] : Int�ж�����ѡ��
                                                                 0����ʾ�ж�����Ϊ64chip��
                                                                 1����ʾ�ж�����Ϊ128chip��
                                                                 2����ʾ�ж�����Ϊ256chip��
                                                                 3����ʾ�ж�����Ϊ512chip��
                                                                 4����ʾ�ж�����Ϊ1.25ms��
                                                                 5����ʾ�ж�����Ϊ5ms��
                                                                 6����ʾ�ж�����Ϊ10ms��
                                                                 7����ʾ�ж�����Ϊ20ms��
                                                                 8����ʾ�ж�����Ϊ40ms��
                                                                 9����ʾ�ж�����Ϊ80ms��
                                                                 10:��ʾ�ж�����Ϊ384chip�� */
        unsigned long  reserved              : 28; /* bit[4-31]: ���� */
    } reg;
} CBBP_TIMING_INT3_1X_PERIOD_UNION;
#define CBBP_TIMING_INT3_1X_PERIOD_timing_int3_1x_period_START  (0)
#define CBBP_TIMING_INT3_1X_PERIOD_timing_int3_1x_period_END    (3)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT3_1X_EN_UNION
 �ṹ˵��  : TIMING_INT3_1X_EN �Ĵ����ṹ���塣��ַƫ����:0x0068����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int3_1x_en_reg;
    struct
    {
        unsigned long  timing_int3_1x_en : 1;  /* bit[0]   : ��ʱ�ж�int��ʹ�ܡ�
                                                             0����ʾ������int�жϣ�
                                                             1����ʾ����int�жϣ� */
        unsigned long  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_TIMING_INT3_1X_EN_UNION;
#define CBBP_TIMING_INT3_1X_EN_timing_int3_1x_en_START  (0)
#define CBBP_TIMING_INT3_1X_EN_timing_int3_1x_en_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT4_SYS_CNT_1X_POS_UNION
 �ṹ˵��  : TIMING_INT4_SYS_CNT_1X_POS �Ĵ����ṹ���塣��ַƫ����:0x006C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int4_sys_cnt_1x_pos_reg;
    struct
    {
        unsigned long  timing_int4_sys_cnt_1x_1p25ms_pos : 11; /* bit[0-10] : Int��sys_cnt_1x�ϵ�λ�ã�
                                                                              [21:16]��sys_cnt_1x_80ms��ֵ��
                                                                              [10:0]��sys_cnt_1x_1p25ms[15:5]��ֵ,chip���ȣ� */
        unsigned long  reserved_0                        : 5;  /* bit[11-15]: ���� */
        unsigned long  timing_int4_sys_cnt_1x_80ms_pos   : 6;  /* bit[16-21]:  */
        unsigned long  reserved_1                        : 10; /* bit[22-31]: ���� */
    } reg;
} CBBP_TIMING_INT4_SYS_CNT_1X_POS_UNION;
#define CBBP_TIMING_INT4_SYS_CNT_1X_POS_timing_int4_sys_cnt_1x_1p25ms_pos_START  (0)
#define CBBP_TIMING_INT4_SYS_CNT_1X_POS_timing_int4_sys_cnt_1x_1p25ms_pos_END    (10)
#define CBBP_TIMING_INT4_SYS_CNT_1X_POS_timing_int4_sys_cnt_1x_80ms_pos_START    (16)
#define CBBP_TIMING_INT4_SYS_CNT_1X_POS_timing_int4_sys_cnt_1x_80ms_pos_END      (21)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT4_1X_PERIOD_UNION
 �ṹ˵��  : TIMING_INT4_1X_PERIOD �Ĵ����ṹ���塣��ַƫ����:0x0070����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int4_1x_period_reg;
    struct
    {
        unsigned long  timing_int4_1x_period : 4;  /* bit[0-3] : Int�ж�����ѡ��
                                                                 0����ʾ�ж�����Ϊ64chip��
                                                                 1����ʾ�ж�����Ϊ128chip��
                                                                 2����ʾ�ж�����Ϊ256chip��
                                                                 3����ʾ�ж�����Ϊ512chip��
                                                                 4����ʾ�ж�����Ϊ1.25ms��
                                                                 5����ʾ�ж�����Ϊ5ms��
                                                                 6����ʾ�ж�����Ϊ10ms��
                                                                 7����ʾ�ж�����Ϊ20ms��
                                                                 8����ʾ�ж�����Ϊ40ms��
                                                                 9����ʾ�ж�����Ϊ80ms��
                                                                 10:��ʾ�ж�����Ϊ384chip�� */
        unsigned long  reserved              : 28; /* bit[4-31]: ���� */
    } reg;
} CBBP_TIMING_INT4_1X_PERIOD_UNION;
#define CBBP_TIMING_INT4_1X_PERIOD_timing_int4_1x_period_START  (0)
#define CBBP_TIMING_INT4_1X_PERIOD_timing_int4_1x_period_END    (3)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT4_1X_EN_UNION
 �ṹ˵��  : TIMING_INT4_1X_EN �Ĵ����ṹ���塣��ַƫ����:0x0074����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int4_1x_en_reg;
    struct
    {
        unsigned long  timing_int4_1x_en : 1;  /* bit[0]   : ��ʱ�ж�int��ʹ�ܡ�
                                                             0����ʾ������int�жϣ�
                                                             1����ʾ����int�жϣ� */
        unsigned long  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_TIMING_INT4_1X_EN_UNION;
#define CBBP_TIMING_INT4_1X_EN_timing_int4_1x_en_START  (0)
#define CBBP_TIMING_INT4_1X_EN_timing_int4_1x_en_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT5_SYS_CNT_1X_POS_UNION
 �ṹ˵��  : TIMING_INT5_SYS_CNT_1X_POS �Ĵ����ṹ���塣��ַƫ����:0x0078����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int5_sys_cnt_1x_pos_reg;
    struct
    {
        unsigned long  timing_int5_sys_cnt_1x_1p25ms_pos : 11; /* bit[0-10] : Int��sys_cnt_1x�ϵ�λ�ã�
                                                                              [21:16]��sys_cnt_1x_80ms��ֵ��
                                                                              [10:0]��sys_cnt_1x_1p25ms[15:5]��ֵ,chip���ȣ� */
        unsigned long  reserved_0                        : 5;  /* bit[11-15]: ���� */
        unsigned long  timing_int5_sys_cnt_1x_80ms_pos   : 6;  /* bit[16-21]:  */
        unsigned long  reserved_1                        : 10; /* bit[22-31]: ���� */
    } reg;
} CBBP_TIMING_INT5_SYS_CNT_1X_POS_UNION;
#define CBBP_TIMING_INT5_SYS_CNT_1X_POS_timing_int5_sys_cnt_1x_1p25ms_pos_START  (0)
#define CBBP_TIMING_INT5_SYS_CNT_1X_POS_timing_int5_sys_cnt_1x_1p25ms_pos_END    (10)
#define CBBP_TIMING_INT5_SYS_CNT_1X_POS_timing_int5_sys_cnt_1x_80ms_pos_START    (16)
#define CBBP_TIMING_INT5_SYS_CNT_1X_POS_timing_int5_sys_cnt_1x_80ms_pos_END      (21)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT5_1X_PERIOD_UNION
 �ṹ˵��  : TIMING_INT5_1X_PERIOD �Ĵ����ṹ���塣��ַƫ����:0x007C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int5_1x_period_reg;
    struct
    {
        unsigned long  timing_int5_1x_period : 4;  /* bit[0-3] : Int�ж�����ѡ��
                                                                 0����ʾ�ж�����Ϊ64chip��
                                                                 1����ʾ�ж�����Ϊ128chip��
                                                                 2����ʾ�ж�����Ϊ256chip��
                                                                 3����ʾ�ж�����Ϊ512chip��
                                                                 4����ʾ�ж�����Ϊ1.25ms��
                                                                 5����ʾ�ж�����Ϊ5ms��
                                                                 6����ʾ�ж�����Ϊ10ms��
                                                                 7����ʾ�ж�����Ϊ20ms��
                                                                 8����ʾ�ж�����Ϊ40ms��
                                                                 9����ʾ�ж�����Ϊ80ms��
                                                                 10:��ʾ�ж�����Ϊ384chip�� */
        unsigned long  reserved              : 28; /* bit[4-31]: ���� */
    } reg;
} CBBP_TIMING_INT5_1X_PERIOD_UNION;
#define CBBP_TIMING_INT5_1X_PERIOD_timing_int5_1x_period_START  (0)
#define CBBP_TIMING_INT5_1X_PERIOD_timing_int5_1x_period_END    (3)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT5_1X_EN_UNION
 �ṹ˵��  : TIMING_INT5_1X_EN �Ĵ����ṹ���塣��ַƫ����:0x0080����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int5_1x_en_reg;
    struct
    {
        unsigned long  timing_int5_1x_en : 1;  /* bit[0]   : ��ʱ�ж�int��ʹ�ܡ�
                                                             0����ʾ������int�жϣ�
                                                             1����ʾ����int�жϣ� */
        unsigned long  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_TIMING_INT5_1X_EN_UNION;
#define CBBP_TIMING_INT5_1X_EN_timing_int5_1x_en_START  (0)
#define CBBP_TIMING_INT5_1X_EN_timing_int5_1x_en_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT6_SYS_CNT_1X_POS_UNION
 �ṹ˵��  : TIMING_INT6_SYS_CNT_1X_POS �Ĵ����ṹ���塣��ַƫ����:0x0084����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int6_sys_cnt_1x_pos_reg;
    struct
    {
        unsigned long  timing_int6_sys_cnt_1x_1p25ms_pos : 11; /* bit[0-10] : Int��sys_cnt_1x�ϵ�λ�ã�
                                                                              [21:16]��sys_cnt_1x_80ms��ֵ��
                                                                              [10:0]��sys_cnt_1x_1p25ms[15:5]��ֵ,chip���ȣ� */
        unsigned long  reserved_0                        : 5;  /* bit[11-15]: ���� */
        unsigned long  timing_int6_sys_cnt_1x_80ms_pos   : 6;  /* bit[16-21]:  */
        unsigned long  reserved_1                        : 10; /* bit[22-31]: ���� */
    } reg;
} CBBP_TIMING_INT6_SYS_CNT_1X_POS_UNION;
#define CBBP_TIMING_INT6_SYS_CNT_1X_POS_timing_int6_sys_cnt_1x_1p25ms_pos_START  (0)
#define CBBP_TIMING_INT6_SYS_CNT_1X_POS_timing_int6_sys_cnt_1x_1p25ms_pos_END    (10)
#define CBBP_TIMING_INT6_SYS_CNT_1X_POS_timing_int6_sys_cnt_1x_80ms_pos_START    (16)
#define CBBP_TIMING_INT6_SYS_CNT_1X_POS_timing_int6_sys_cnt_1x_80ms_pos_END      (21)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT6_1X_PERIOD_UNION
 �ṹ˵��  : TIMING_INT6_1X_PERIOD �Ĵ����ṹ���塣��ַƫ����:0x0088����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int6_1x_period_reg;
    struct
    {
        unsigned long  timing_int6_1x_period : 4;  /* bit[0-3] : Int�ж�����ѡ��
                                                                 0����ʾ�ж�����Ϊ64chip��
                                                                 1����ʾ�ж�����Ϊ128chip��
                                                                 2����ʾ�ж�����Ϊ256chip��
                                                                 3����ʾ�ж�����Ϊ512chip��
                                                                 4����ʾ�ж�����Ϊ1.25ms��
                                                                 5����ʾ�ж�����Ϊ5ms��
                                                                 6����ʾ�ж�����Ϊ10ms��
                                                                 7����ʾ�ж�����Ϊ20ms��
                                                                 8����ʾ�ж�����Ϊ40ms��
                                                                 9����ʾ�ж�����Ϊ80ms��
                                                                 10:��ʾ�ж�����Ϊ384chip�� */
        unsigned long  reserved              : 28; /* bit[4-31]: ���� */
    } reg;
} CBBP_TIMING_INT6_1X_PERIOD_UNION;
#define CBBP_TIMING_INT6_1X_PERIOD_timing_int6_1x_period_START  (0)
#define CBBP_TIMING_INT6_1X_PERIOD_timing_int6_1x_period_END    (3)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT6_1X_EN_UNION
 �ṹ˵��  : TIMING_INT6_1X_EN �Ĵ����ṹ���塣��ַƫ����:0x008C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int6_1x_en_reg;
    struct
    {
        unsigned long  timing_int6_1x_en : 1;  /* bit[0]   : ��ʱ�ж�int��ʹ�ܡ�
                                                             0����ʾ������int�жϣ�
                                                             1����ʾ����int�жϣ� */
        unsigned long  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_TIMING_INT6_1X_EN_UNION;
#define CBBP_TIMING_INT6_1X_EN_timing_int6_1x_en_START  (0)
#define CBBP_TIMING_INT6_1X_EN_timing_int6_1x_en_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_1X_RPT_INT1_MASK_UNION
 �ṹ˵��  : SYS_CNT_1X_RPT_INT1_MASK �Ĵ����ṹ���塣��ַƫ����:0x0090����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_1x_rpt_int1_mask_reg;
    struct
    {
        unsigned long  sys_cnt_1x_rpt_int1_mask : 6;  /* bit[0-5] : ��������ϱ��ж�ʱ��sys_cnt_1xֵ��mask��
                                                                    bit0��Ϊ1��ʾ�ϱ��ж�1ʱ�̵Ķ�ʱ��
                                                                    bit1��Ϊ1��ʾ�ϱ��ж�2ʱ�̵Ķ�ʱ��
                                                                    ��
                                                                    ע�⣺ͬһʱ��ֻ����1bitΪ1 */
        unsigned long  reserved                 : 26; /* bit[6-31]: ���� */
    } reg;
} CBBP_SYS_CNT_1X_RPT_INT1_MASK_UNION;
#define CBBP_SYS_CNT_1X_RPT_INT1_MASK_sys_cnt_1x_rpt_int1_mask_START  (0)
#define CBBP_SYS_CNT_1X_RPT_INT1_MASK_sys_cnt_1x_rpt_int1_mask_END    (5)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_1X_RPT_INT1_UNION
 �ṹ˵��  : SYS_CNT_1X_RPT_INT1 �Ĵ����ṹ���塣��ַƫ����:0x0094����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_1x_rpt_int1_reg;
    struct
    {
        unsigned long  sys_cnt_1x_1p25ms_rpt_int1 : 5;  /* bit[0-4]  : ������õĵ�һ���ϱ���ʱ��Ϣ���ж�ʱ�̵�sys_cnt_1x��ֵ��
                                                                       
                                                                       [21:16]��sys_cnt_1x_80ms��ֵ��
                                                                       [4:0]��sys_cnt_1x_1p25ms��ֵ,64chip���ȣ� */
        unsigned long  reserved_0                 : 11; /* bit[5-15] : ���� */
        unsigned long  sys_cnt_1x_80ms_rpt_int1   : 6;  /* bit[16-21]:  */
        unsigned long  reserved_1                 : 10; /* bit[22-31]: ���� */
    } reg;
} CBBP_SYS_CNT_1X_RPT_INT1_UNION;
#define CBBP_SYS_CNT_1X_RPT_INT1_sys_cnt_1x_1p25ms_rpt_int1_START  (0)
#define CBBP_SYS_CNT_1X_RPT_INT1_sys_cnt_1x_1p25ms_rpt_int1_END    (4)
#define CBBP_SYS_CNT_1X_RPT_INT1_sys_cnt_1x_80ms_rpt_int1_START    (16)
#define CBBP_SYS_CNT_1X_RPT_INT1_sys_cnt_1x_80ms_rpt_int1_END      (21)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_1X_RPT_INT2_MASK_UNION
 �ṹ˵��  : SYS_CNT_1X_RPT_INT2_MASK �Ĵ����ṹ���塣��ַƫ����:0x0098����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_1x_rpt_int2_mask_reg;
    struct
    {
        unsigned long  sys_cnt_1x_rpt_int2_mask : 6;  /* bit[0-5] : ��������ϱ��ж�ʱ��sys_cnt_1xֵ��mask��
                                                                    bit0��Ϊ1��ʾ�ϱ��ж�1ʱ�̵Ķ�ʱ��
                                                                    bit1��Ϊ1��ʾ�ϱ��ж�2ʱ�̵Ķ�ʱ��
                                                                    ��
                                                                    ע�⣺ͬһʱ��ֻ����1bitΪ1 */
        unsigned long  reserved                 : 26; /* bit[6-31]: ���� */
    } reg;
} CBBP_SYS_CNT_1X_RPT_INT2_MASK_UNION;
#define CBBP_SYS_CNT_1X_RPT_INT2_MASK_sys_cnt_1x_rpt_int2_mask_START  (0)
#define CBBP_SYS_CNT_1X_RPT_INT2_MASK_sys_cnt_1x_rpt_int2_mask_END    (5)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_1X_RPT_INT2_UNION
 �ṹ˵��  : SYS_CNT_1X_RPT_INT2 �Ĵ����ṹ���塣��ַƫ����:0x009C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_1x_rpt_int2_reg;
    struct
    {
        unsigned long  sys_cnt_1x_1p25ms_rpt_int2 : 5;  /* bit[0-4]  : ������õĵ�2���ϱ���ʱ��Ϣ���ж�ʱ�̵�sys_cnt_1x��ֵ��
                                                                       
                                                                       [21:16]��sys_cnt_1x_80ms��ֵ��
                                                                       [4:0]��sys_cnt_1x_1p25ms��ֵ,64chip���ȣ� */
        unsigned long  reserved_0                 : 11; /* bit[5-15] : ���� */
        unsigned long  sys_cnt_1x_80ms_rpt_int2   : 6;  /* bit[16-21]:  */
        unsigned long  reserved_1                 : 10; /* bit[22-31]: ���� */
    } reg;
} CBBP_SYS_CNT_1X_RPT_INT2_UNION;
#define CBBP_SYS_CNT_1X_RPT_INT2_sys_cnt_1x_1p25ms_rpt_int2_START  (0)
#define CBBP_SYS_CNT_1X_RPT_INT2_sys_cnt_1x_1p25ms_rpt_int2_END    (4)
#define CBBP_SYS_CNT_1X_RPT_INT2_sys_cnt_1x_80ms_rpt_int2_START    (16)
#define CBBP_SYS_CNT_1X_RPT_INT2_sys_cnt_1x_80ms_rpt_int2_END      (21)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_1X_RPT_INT3_MASK_UNION
 �ṹ˵��  : SYS_CNT_1X_RPT_INT3_MASK �Ĵ����ṹ���塣��ַƫ����:0x00A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_1x_rpt_int3_mask_reg;
    struct
    {
        unsigned long  sys_cnt_1x_rpt_int3_mask : 6;  /* bit[0-5] : ��������ϱ��ж�ʱ��sys_cnt_1xֵ��mask��
                                                                    bit0��Ϊ1��ʾ�ϱ��ж�1ʱ�̵Ķ�ʱ��
                                                                    bit1��Ϊ1��ʾ�ϱ��ж�2ʱ�̵Ķ�ʱ��
                                                                    ��
                                                                    ע�⣺ͬһʱ��ֻ����1bitΪ1 */
        unsigned long  reserved                 : 26; /* bit[6-31]: ���� */
    } reg;
} CBBP_SYS_CNT_1X_RPT_INT3_MASK_UNION;
#define CBBP_SYS_CNT_1X_RPT_INT3_MASK_sys_cnt_1x_rpt_int3_mask_START  (0)
#define CBBP_SYS_CNT_1X_RPT_INT3_MASK_sys_cnt_1x_rpt_int3_mask_END    (5)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_1X_RPT_INT3_UNION
 �ṹ˵��  : SYS_CNT_1X_RPT_INT3 �Ĵ����ṹ���塣��ַƫ����:0x00A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_1x_rpt_int3_reg;
    struct
    {
        unsigned long  sys_cnt_1x_1p25ms_rpt_int3 : 5;  /* bit[0-4]  : ������õĵ�3���ϱ���ʱ��Ϣ���ж�ʱ�̵�sys_cnt_1x��ֵ��
                                                                       
                                                                       [21:16]��sys_cnt_1x_80ms��ֵ��
                                                                       [4:0]��sys_cnt_1x_1p25ms��ֵ,64chip���ȣ� */
        unsigned long  reserved_0                 : 11; /* bit[5-15] : ���� */
        unsigned long  sys_cnt_1x_80ms_rpt_int3   : 6;  /* bit[16-21]:  */
        unsigned long  reserved_1                 : 10; /* bit[22-31]: ���� */
    } reg;
} CBBP_SYS_CNT_1X_RPT_INT3_UNION;
#define CBBP_SYS_CNT_1X_RPT_INT3_sys_cnt_1x_1p25ms_rpt_int3_START  (0)
#define CBBP_SYS_CNT_1X_RPT_INT3_sys_cnt_1x_1p25ms_rpt_int3_END    (4)
#define CBBP_SYS_CNT_1X_RPT_INT3_sys_cnt_1x_80ms_rpt_int3_START    (16)
#define CBBP_SYS_CNT_1X_RPT_INT3_sys_cnt_1x_80ms_rpt_int3_END      (21)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_1X_PERIOD_UNION
 �ṹ˵��  : SYS_CNT_1X_PERIOD �Ĵ����ṹ���塣��ַƫ����:0x00A8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_1x_period_reg;
    struct
    {
        unsigned long  sys_cnt_1x_period : 1;  /* bit[0]   : 1xϵͳ������sys_cnt_1x������
                                                             0��ʾ����Ϊ2s��
                                                             1��ʾ����Ϊ5.12s */
        unsigned long  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_SYS_CNT_1X_PERIOD_UNION;
#define CBBP_SYS_CNT_1X_PERIOD_sys_cnt_1x_period_START  (0)
#define CBBP_SYS_CNT_1X_PERIOD_sys_cnt_1x_period_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_1X_RPT2_UNION
 �ṹ˵��  : SYS_CNT_1X_RPT2 �Ĵ����ṹ���塣��ַƫ����:0x00B8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_1x_rpt2_reg;
    struct
    {
        unsigned long  sys_cnt_1x_1p25ms_rpt2 : 11; /* bit[0-10] : sys_cnt_1x��ֵ��
                                                                   [29:24]��sys_cnt_1x_5p12s��ֵ��
                                                                   [21:16]��sys_cnt_1x_80ms��ֵ��
                                                                   [10:0]��sys_cnt_1x_1p25ms��ֵ,chip���ȣ�
                                                                   
                                                                   ���ֱ�Ӷ�ȡ��BBPδ�����洦�����������ȡ2~3�Σ�ȷ�϶�ȡ���ȶ��Ľ����ʹ�� */
        unsigned long  reserved_0             : 5;  /* bit[11-15]: ���� */
        unsigned long  sys_cnt_1x_80ms_rpt2   : 6;  /* bit[16-21]:  */
        unsigned long  reserved_1             : 2;  /* bit[22-23]: ���� */
        unsigned long  sys_cnt_1x_5p12s_rpt2  : 6;  /* bit[24-29]:  */
        unsigned long  reserved_2             : 2;  /* bit[30-31]: ���� */
    } reg;
} CBBP_SYS_CNT_1X_RPT2_UNION;
#define CBBP_SYS_CNT_1X_RPT2_sys_cnt_1x_1p25ms_rpt2_START  (0)
#define CBBP_SYS_CNT_1X_RPT2_sys_cnt_1x_1p25ms_rpt2_END    (10)
#define CBBP_SYS_CNT_1X_RPT2_sys_cnt_1x_80ms_rpt2_START    (16)
#define CBBP_SYS_CNT_1X_RPT2_sys_cnt_1x_80ms_rpt2_END      (21)
#define CBBP_SYS_CNT_1X_RPT2_sys_cnt_1x_5p12s_rpt2_START   (24)
#define CBBP_SYS_CNT_1X_RPT2_sys_cnt_1x_5p12s_rpt2_END     (29)


/*****************************************************************************
 �ṹ��    : CBBP_C_TIMING_MODE_1X_UNION
 �ṹ˵��  : C_TIMING_MODE_1X �Ĵ����ṹ���塣��ַƫ����:0x00C0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      c_timing_mode_1x_reg;
    struct
    {
        unsigned long  c_timing_mode_1x : 1;  /* bit[0]   : ��ǰϵͳ���Ƿ����1x��ʱ��
                                                            1����ʾ����1x��ʱ�� */
        unsigned long  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_C_TIMING_MODE_1X_UNION;
#define CBBP_C_TIMING_MODE_1X_c_timing_mode_1x_START  (0)
#define CBBP_C_TIMING_MODE_1X_c_timing_mode_1x_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_SLEEP_TIME_1X_UNION
 �ṹ˵��  : SLEEP_TIME_1X �Ĵ����ṹ���塣��ַƫ����:0x00C8����ֵ:0x00000000�����:32
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
 �ṹ��    : CBBP_SSI_TRANS_COMP_1X_UNION
 �ṹ˵��  : SSI_TRANS_COMP_1X �Ĵ����ṹ���塣��ַƫ����:0x00D0����ֵ:0x0000000A�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ssi_trans_comp_1x_reg;
    struct
    {
        unsigned long  ssi_trans_comp_1x : 5;  /* bit[0-4] : ����ʱ��ʹ�ô��пڴ��䶨ʱ��Ϣ��ʱ�䣬��λchip */
        unsigned long  reserved          : 27; /* bit[5-31]: ���� */
    } reg;
} CBBP_SSI_TRANS_COMP_1X_UNION;
#define CBBP_SSI_TRANS_COMP_1X_ssi_trans_comp_1x_START  (0)
#define CBBP_SSI_TRANS_COMP_1X_ssi_trans_comp_1x_END    (4)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_EVDO_GET_POS_UNION
 �ṹ˵��  : SYS_CNT_EVDO_GET_POS �Ĵ����ṹ���塣��ַƫ����:0x0100����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_evdo_get_pos_reg;
    struct
    {
        unsigned long  sys_cnt_evdo_get_pos_1_4chip : 5;  /* bit[0-4]  : ����sys_cnt_evdo��ʱ�̣�
                                                                         [28:24]��base_cnt_2s�ϵ�ʱ�̣���ȡֵ��Χ0~24��
                                                                         [23:22]��base_cnt_80ms�ϵ�ʱ�̣�ȡֵ��Χ0~2��
                                                                         [21:5]��base_cnt_26ms�ϵ�ʱ�̣�ȡֵ��Χ0~32768*32-1��
                                                                         [4:0],1/4chip�ڼ�����ȡֵ��Χ0~24 */
        unsigned long  sys_cnt_evdo_get_pos_26ms    : 17; /* bit[5-21] :  */
        unsigned long  sys_cnt_evdo_get_pos_80ms    : 2;  /* bit[22-23]:  */
        unsigned long  sys_cnt_evdo_get_pos_2s      : 5;  /* bit[24-28]:  */
        unsigned long  reserved                     : 3;  /* bit[29-31]: ���� */
    } reg;
} CBBP_SYS_CNT_EVDO_GET_POS_UNION;
#define CBBP_SYS_CNT_EVDO_GET_POS_sys_cnt_evdo_get_pos_1_4chip_START  (0)
#define CBBP_SYS_CNT_EVDO_GET_POS_sys_cnt_evdo_get_pos_1_4chip_END    (4)
#define CBBP_SYS_CNT_EVDO_GET_POS_sys_cnt_evdo_get_pos_26ms_START     (5)
#define CBBP_SYS_CNT_EVDO_GET_POS_sys_cnt_evdo_get_pos_26ms_END       (21)
#define CBBP_SYS_CNT_EVDO_GET_POS_sys_cnt_evdo_get_pos_80ms_START     (22)
#define CBBP_SYS_CNT_EVDO_GET_POS_sys_cnt_evdo_get_pos_80ms_END       (23)
#define CBBP_SYS_CNT_EVDO_GET_POS_sys_cnt_evdo_get_pos_2s_START       (24)
#define CBBP_SYS_CNT_EVDO_GET_POS_sys_cnt_evdo_get_pos_2s_END         (28)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_EVDO_GET_VALUE_UNION
 �ṹ˵��  : SYS_CNT_EVDO_GET_VALUE �Ĵ����ṹ���塣��ַƫ����:0x0104����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_evdo_get_value_reg;
    struct
    {
        unsigned long  sys_cnt_evdo_get_value_1_4chip : 5;  /* bit[0-4]  : sys_cnt_evdo_get_posʱ��sys_cnt_evdo��ֵ��
                                                                           [28:24]��sys_cnt_evdo_5p12s��ֵ��
                                                                           [31:22]��sys_cnt_evdo_80ms��ֵ��
                                                                           [21:5]��sys_cnt_evdo_26ms��ֵ��
                                                                           [4:0]��1/4chip�ڼ�����0~24 */
        unsigned long  sys_cnt_evdo_get_value_26ms    : 17; /* bit[5-21] :  */
        unsigned long  sys_cnt_evdo_get_value_80ms    : 2;  /* bit[22-23]:  */
        unsigned long  sys_cnt_evdo_get_value_5p12s   : 6;  /* bit[24-29]:  */
        unsigned long  reserved                       : 2;  /* bit[30-31]: ���� */
    } reg;
} CBBP_SYS_CNT_EVDO_GET_VALUE_UNION;
#define CBBP_SYS_CNT_EVDO_GET_VALUE_sys_cnt_evdo_get_value_1_4chip_START  (0)
#define CBBP_SYS_CNT_EVDO_GET_VALUE_sys_cnt_evdo_get_value_1_4chip_END    (4)
#define CBBP_SYS_CNT_EVDO_GET_VALUE_sys_cnt_evdo_get_value_26ms_START     (5)
#define CBBP_SYS_CNT_EVDO_GET_VALUE_sys_cnt_evdo_get_value_26ms_END       (21)
#define CBBP_SYS_CNT_EVDO_GET_VALUE_sys_cnt_evdo_get_value_80ms_START     (22)
#define CBBP_SYS_CNT_EVDO_GET_VALUE_sys_cnt_evdo_get_value_80ms_END       (23)
#define CBBP_SYS_CNT_EVDO_GET_VALUE_sys_cnt_evdo_get_value_5p12s_START    (24)
#define CBBP_SYS_CNT_EVDO_GET_VALUE_sys_cnt_evdo_get_value_5p12s_END      (29)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_EVDO_80MS_POS_CFG_UNION
 �ṹ˵��  : SYS_CNT_EVDO_80MS_POS_CFG �Ĵ����ṹ���塣��ַƫ����:0x0224����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_evdo_80ms_pos_cfg_reg;
    struct
    {
        unsigned long  sys_cnt_evdo_80ms_pos_1_4chip_cfg : 5;  /* bit[0-4]  : ��ʱͻ���sys_cnt_evdo  80ms֡ͷ��base_cnt�ϵ�λ�á�
                                                                              Bit[4:0]��1/4chip�ڼ���0~24
                                                                              bit[21:5]��26ms�ڼ���0~32768*4-1
                                                                              bit[23:22]��80ms�ڼ���0~2 */
        unsigned long  sys_cnt_evdo_80ms_pos_26ms_cfg    : 17; /* bit[5-21] :  */
        unsigned long  sys_cnt_evdo_80ms_pos_80ms_cfg    : 2;  /* bit[22-23]:  */
        unsigned long  reserved                          : 8;  /* bit[24-31]: ���� */
    } reg;
} CBBP_SYS_CNT_EVDO_80MS_POS_CFG_UNION;
#define CBBP_SYS_CNT_EVDO_80MS_POS_CFG_sys_cnt_evdo_80ms_pos_1_4chip_cfg_START  (0)
#define CBBP_SYS_CNT_EVDO_80MS_POS_CFG_sys_cnt_evdo_80ms_pos_1_4chip_cfg_END    (4)
#define CBBP_SYS_CNT_EVDO_80MS_POS_CFG_sys_cnt_evdo_80ms_pos_26ms_cfg_START     (5)
#define CBBP_SYS_CNT_EVDO_80MS_POS_CFG_sys_cnt_evdo_80ms_pos_26ms_cfg_END       (21)
#define CBBP_SYS_CNT_EVDO_80MS_POS_CFG_sys_cnt_evdo_80ms_pos_80ms_cfg_START     (22)
#define CBBP_SYS_CNT_EVDO_80MS_POS_CFG_sys_cnt_evdo_80ms_pos_80ms_cfg_END       (23)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_EVDO_GET_RDY_UNION
 �ṹ˵��  : SYS_CNT_EVDO_GET_RDY �Ĵ����ṹ���塣��ַƫ����:0x0108����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_evdo_get_rdy_reg;
    struct
    {
        unsigned long  sys_cnt_evdo_get_rdy : 1;  /* bit[0]   : Sys_cnt_evdo��ʱ��ȡָʾ��
                                                                BBP���յ���ָʾ�󣬵ȴ�base_cnt��sys_cnt_evdo_get_posʱ�̣���sys_cnt_evdo����Ϊsys_cnt_evdo_get_value�� */
        unsigned long  reserved             : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_SYS_CNT_EVDO_GET_RDY_UNION;
#define CBBP_SYS_CNT_EVDO_GET_RDY_sys_cnt_evdo_get_rdy_START  (0)
#define CBBP_SYS_CNT_EVDO_GET_RDY_sys_cnt_evdo_get_rdy_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_EVDO_CHANGE_DIRECTION_UNION
 �ṹ˵��  : SYS_EVDO_CHANGE_DIRECTION �Ĵ����ṹ���塣��ַƫ����:0x010C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_evdo_change_direction_reg;
    struct
    {
        unsigned long  sys_evdo_change_direction : 1;  /* bit[0]   : ϵͳ��ʱ��������
                                                                     0����ʾ����ߵ���6clk��
                                                                     1����ʾ���ұߵ���6clk��
                                                                     ˵������ʱ����100��ʱ�ӣ���ˣ�6clkʱ��Ϊ6/100chip */
        unsigned long  reserved                  : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_SYS_EVDO_CHANGE_DIRECTION_UNION;
#define CBBP_SYS_EVDO_CHANGE_DIRECTION_sys_evdo_change_direction_START  (0)
#define CBBP_SYS_EVDO_CHANGE_DIRECTION_sys_evdo_change_direction_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_EVDO_CHANGE_RDY_UNION
 �ṹ˵��  : SYS_EVDO_CHANGE_RDY �Ĵ����ṹ���塣��ַƫ����:0x0110����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_evdo_change_rdy_reg;
    struct
    {
        unsigned long  sys_evdo_change_rdy : 1;  /* bit[0]   : ϵͳ��ʱ����ָʾ��
                                                               BBP�ڽ��յ���ָʾ���������ʱ϶ͷ���ϵͳ��ʱ������ */
        unsigned long  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_SYS_EVDO_CHANGE_RDY_UNION;
#define CBBP_SYS_EVDO_CHANGE_RDY_sys_evdo_change_rdy_START  (0)
#define CBBP_SYS_EVDO_CHANGE_RDY_sys_evdo_change_rdy_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_EVDO_80MS_POS_RD_UNION
 �ṹ˵��  : SYS_CNT_EVDO_80MS_POS_RD �Ĵ����ṹ���塣��ַƫ����:0x0114����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_evdo_80ms_pos_rd_reg;
    struct
    {
        unsigned long  sys_cnt_evdo_80ms_pos_rd : 1;  /* bit[0]   : �����ȡsys_cnt_evdo_80ms_pos��ָʾ */
        unsigned long  reserved                 : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_SYS_CNT_EVDO_80MS_POS_RD_UNION;
#define CBBP_SYS_CNT_EVDO_80MS_POS_RD_sys_cnt_evdo_80ms_pos_rd_START  (0)
#define CBBP_SYS_CNT_EVDO_80MS_POS_RD_sys_cnt_evdo_80ms_pos_rd_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_EVDO_80MS_POS_UNION
 �ṹ˵��  : SYS_CNT_EVDO_80MS_POS �Ĵ����ṹ���塣��ַƫ����:0x0118����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_evdo_80ms_pos_reg;
    struct
    {
        unsigned long  sys_cnt_evdo_80ms_pos_1_4chip : 5;  /* bit[0-4]  : sys_cnt_evdo  80ms֡ͷ��base_cnt�ϵ�λ�á�
                                                                          Bit[4:0]��1/4chip�ڼ���0~24
                                                                          bit[21:5]��26ms�ڼ���0~32768*4-1
                                                                          bit[23:22]��80ms�ڼ���0~2 */
        unsigned long  sys_cnt_evdo_80ms_pos_26ms    : 17; /* bit[5-21] :  */
        unsigned long  sys_cnt_evdo_80ms_pos_80ms    : 2;  /* bit[22-23]:  */
        unsigned long  reserved                      : 7;  /* bit[24-30]: ���� */
        unsigned long  sys_cnt_evdo_80ms_pos_valid   : 1;  /* bit[31]   : ��ȡsys_cnt_evdo_80ms_pos��Чָʾ��1��Ч */
    } reg;
} CBBP_SYS_CNT_EVDO_80MS_POS_UNION;
#define CBBP_SYS_CNT_EVDO_80MS_POS_sys_cnt_evdo_80ms_pos_1_4chip_START  (0)
#define CBBP_SYS_CNT_EVDO_80MS_POS_sys_cnt_evdo_80ms_pos_1_4chip_END    (4)
#define CBBP_SYS_CNT_EVDO_80MS_POS_sys_cnt_evdo_80ms_pos_26ms_START     (5)
#define CBBP_SYS_CNT_EVDO_80MS_POS_sys_cnt_evdo_80ms_pos_26ms_END       (21)
#define CBBP_SYS_CNT_EVDO_80MS_POS_sys_cnt_evdo_80ms_pos_80ms_START     (22)
#define CBBP_SYS_CNT_EVDO_80MS_POS_sys_cnt_evdo_80ms_pos_80ms_END       (23)
#define CBBP_SYS_CNT_EVDO_80MS_POS_sys_cnt_evdo_80ms_pos_valid_START    (31)
#define CBBP_SYS_CNT_EVDO_80MS_POS_sys_cnt_evdo_80ms_pos_valid_END      (31)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_EVDO_80MS_POS_VALID_CLR_UNION
 �ṹ˵��  : SYS_CNT_EVDO_80MS_POS_VALID_CLR �Ĵ����ṹ���塣��ַƫ����:0x011C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_evdo_80ms_pos_valid_clr_reg;
    struct
    {
        unsigned long  sys_cnt_evdo_80ms_pos_valid_clr : 1;  /* bit[0]   : sys_cnt_evdo_80ms_pos_valid�����ź� */
        unsigned long  reserved                        : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_SYS_CNT_EVDO_80MS_POS_VALID_CLR_UNION;
#define CBBP_SYS_CNT_EVDO_80MS_POS_VALID_CLR_sys_cnt_evdo_80ms_pos_valid_clr_START  (0)
#define CBBP_SYS_CNT_EVDO_80MS_POS_VALID_CLR_sys_cnt_evdo_80ms_pos_valid_clr_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT_EVDO_MASK_UNION
 �ṹ˵��  : TIMING_INT_EVDO_MASK �Ĵ����ṹ���塣��ַƫ����:0x0120����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int_evdo_mask_reg;
    struct
    {
        unsigned long  timing_int_evdo_mask : 1;  /* bit[0]   : ��ʱͻ��ʱ����ʱ�жϵ�mask��
                                                                0����ʾ��mask��
                                                                1����ʾmask���÷�Χ�ڵ��жϣ� */
        unsigned long  reserved             : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_TIMING_INT_EVDO_MASK_UNION;
#define CBBP_TIMING_INT_EVDO_MASK_timing_int_evdo_mask_START  (0)
#define CBBP_TIMING_INT_EVDO_MASK_timing_int_evdo_mask_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT_EVDO_MASK_DIS_UNION
 �ṹ˵��  : TIMING_INT_EVDO_MASK_DIS �Ĵ����ṹ���塣��ַƫ����:0x0124����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int_evdo_mask_dis_reg;
    struct
    {
        unsigned long  timing_int_evdo_mask_dis : 11; /* bit[0-10] : ��ʱͻ��ʱ����ʱ�жϵ�mask���䣬chipΪ��λ�� */
        unsigned long  reserved                 : 21; /* bit[11-31]: ���� */
    } reg;
} CBBP_TIMING_INT_EVDO_MASK_DIS_UNION;
#define CBBP_TIMING_INT_EVDO_MASK_DIS_timing_int_evdo_mask_dis_START  (0)
#define CBBP_TIMING_INT_EVDO_MASK_DIS_timing_int_evdo_mask_dis_END    (10)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT1_SYS_CNT_EVDO_POS_UNION
 �ṹ˵��  : TIMING_INT1_SYS_CNT_EVDO_POS �Ĵ����ṹ���塣��ַƫ����:0x0128����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int1_sys_cnt_evdo_pos_reg;
    struct
    {
        unsigned long  timing_int1_sys_cnt_evdo_26ms_pos : 15; /* bit[0-14] : Int��sys_cnt_evdo�ϵ�λ�ã�
                                                                              [17:16]��sys_cnt_evdo_80ms��ֵ��
                                                                              [14:0]��sys_cnt_evdo_26ms��ֵ��chip���ȣ� */
        unsigned long  reserved_0                        : 1;  /* bit[15]   : ���� */
        unsigned long  timing_int1_sys_cnt_evdo_80ms_pos : 2;  /* bit[16-17]:  */
        unsigned long  reserved_1                        : 14; /* bit[18-31]: ���� */
    } reg;
} CBBP_TIMING_INT1_SYS_CNT_EVDO_POS_UNION;
#define CBBP_TIMING_INT1_SYS_CNT_EVDO_POS_timing_int1_sys_cnt_evdo_26ms_pos_START  (0)
#define CBBP_TIMING_INT1_SYS_CNT_EVDO_POS_timing_int1_sys_cnt_evdo_26ms_pos_END    (14)
#define CBBP_TIMING_INT1_SYS_CNT_EVDO_POS_timing_int1_sys_cnt_evdo_80ms_pos_START  (16)
#define CBBP_TIMING_INT1_SYS_CNT_EVDO_POS_timing_int1_sys_cnt_evdo_80ms_pos_END    (17)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT1_EVDO_PERIOD_UNION
 �ṹ˵��  : TIMING_INT1_EVDO_PERIOD �Ĵ����ṹ���塣��ַƫ����:0x012C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int1_evdo_period_reg;
    struct
    {
        unsigned long  timing_int1_evdo_period : 4;  /* bit[0-3] : Int�ж�����ѡ��
                                                                   0����ʾ�ж�����Ϊ64chip��
                                                                   1����ʾ�ж�����Ϊ128chip��
                                                                   2����ʾ�ж�����Ϊ256chip��
                                                                   3����ʾ�ж�����Ϊ512chip��
                                                                   4����ʾ�ж�����Ϊ1024chip��
                                                                   5����ʾ�ж�����Ϊ2048chip��
                                                                   6����ʾ�ж�����Ϊ4096chip��
                                                                   7����ʾ�ж�����Ϊ8192chip��
                                                                   8����ʾ�ж�����Ϊ16384chip��
                                                                   9����ʾ�ж�����Ϊ32768chip��
                                                                   10����ʾ�ж�����Ϊ80ms�� */
        unsigned long  reserved                : 28; /* bit[4-31]: ���� */
    } reg;
} CBBP_TIMING_INT1_EVDO_PERIOD_UNION;
#define CBBP_TIMING_INT1_EVDO_PERIOD_timing_int1_evdo_period_START  (0)
#define CBBP_TIMING_INT1_EVDO_PERIOD_timing_int1_evdo_period_END    (3)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT1_EVDO_EN_UNION
 �ṹ˵��  : TIMING_INT1_EVDO_EN �Ĵ����ṹ���塣��ַƫ����:0x0130����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int1_evdo_en_reg;
    struct
    {
        unsigned long  timing_int1_evdo_en : 1;  /* bit[0]   : ��ʱ�ж�int��ʹ�ܡ�
                                                               0����ʾ������int�жϣ�
                                                               1����ʾ����int�жϣ� */
        unsigned long  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_TIMING_INT1_EVDO_EN_UNION;
#define CBBP_TIMING_INT1_EVDO_EN_timing_int1_evdo_en_START  (0)
#define CBBP_TIMING_INT1_EVDO_EN_timing_int1_evdo_en_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT2_SYS_CNT_EVDO_POS_UNION
 �ṹ˵��  : TIMING_INT2_SYS_CNT_EVDO_POS �Ĵ����ṹ���塣��ַƫ����:0x0134����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int2_sys_cnt_evdo_pos_reg;
    struct
    {
        unsigned long  timing_int2_sys_cnt_evdo_26ms_pos : 15; /* bit[0-14] : Int��sys_cnt_evdo�ϵ�λ�ã�
                                                                              [17:16]��sys_cnt_evdo_80ms��ֵ��
                                                                              [14:0]��sys_cnt_evdo_26ms��ֵ��chip���ȣ� */
        unsigned long  reserved_0                        : 1;  /* bit[15]   : ���� */
        unsigned long  timing_int2_sys_cnt_evdo_80ms_pos : 2;  /* bit[16-17]:  */
        unsigned long  reserved_1                        : 14; /* bit[18-31]: ���� */
    } reg;
} CBBP_TIMING_INT2_SYS_CNT_EVDO_POS_UNION;
#define CBBP_TIMING_INT2_SYS_CNT_EVDO_POS_timing_int2_sys_cnt_evdo_26ms_pos_START  (0)
#define CBBP_TIMING_INT2_SYS_CNT_EVDO_POS_timing_int2_sys_cnt_evdo_26ms_pos_END    (14)
#define CBBP_TIMING_INT2_SYS_CNT_EVDO_POS_timing_int2_sys_cnt_evdo_80ms_pos_START  (16)
#define CBBP_TIMING_INT2_SYS_CNT_EVDO_POS_timing_int2_sys_cnt_evdo_80ms_pos_END    (17)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT2_EVDO_PERIOD_UNION
 �ṹ˵��  : TIMING_INT2_EVDO_PERIOD �Ĵ����ṹ���塣��ַƫ����:0x0138����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int2_evdo_period_reg;
    struct
    {
        unsigned long  timing_int2_evdo_period : 4;  /* bit[0-3] : Int�ж�����ѡ��
                                                                   0����ʾ�ж�����Ϊ64chip��
                                                                   1����ʾ�ж�����Ϊ128chip��
                                                                   2����ʾ�ж�����Ϊ256chip��
                                                                   3����ʾ�ж�����Ϊ512chip��
                                                                   4����ʾ�ж�����Ϊ1024chip��
                                                                   5����ʾ�ж�����Ϊ2048chip��
                                                                   6����ʾ�ж�����Ϊ4096chip��
                                                                   7����ʾ�ж�����Ϊ8192chip��
                                                                   8����ʾ�ж�����Ϊ16384chip��
                                                                   9����ʾ�ж�����Ϊ32768chip��
                                                                   10����ʾ�ж�����Ϊ80ms�� */
        unsigned long  reserved                : 28; /* bit[4-31]: ���� */
    } reg;
} CBBP_TIMING_INT2_EVDO_PERIOD_UNION;
#define CBBP_TIMING_INT2_EVDO_PERIOD_timing_int2_evdo_period_START  (0)
#define CBBP_TIMING_INT2_EVDO_PERIOD_timing_int2_evdo_period_END    (3)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT2_EVDO_EN_UNION
 �ṹ˵��  : TIMING_INT2_EVDO_EN �Ĵ����ṹ���塣��ַƫ����:0x013C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int2_evdo_en_reg;
    struct
    {
        unsigned long  timing_int2_evdo_en : 1;  /* bit[0]   : ��ʱ�ж�int��ʹ�ܡ�
                                                               0����ʾ������int�жϣ�
                                                               1����ʾ����int�жϣ� */
        unsigned long  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_TIMING_INT2_EVDO_EN_UNION;
#define CBBP_TIMING_INT2_EVDO_EN_timing_int2_evdo_en_START  (0)
#define CBBP_TIMING_INT2_EVDO_EN_timing_int2_evdo_en_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT3_SYS_CNT_EVDO_POS_UNION
 �ṹ˵��  : TIMING_INT3_SYS_CNT_EVDO_POS �Ĵ����ṹ���塣��ַƫ����:0x0140����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int3_sys_cnt_evdo_pos_reg;
    struct
    {
        unsigned long  timing_int3_sys_cnt_evdo_26ms_pos : 15; /* bit[0-14] : Int��sys_cnt_evdo�ϵ�λ�ã�
                                                                              [17:16]��sys_cnt_evdo_80ms��ֵ��
                                                                              [14:0]��sys_cnt_evdo_26ms��ֵ��chip���ȣ� */
        unsigned long  reserved_0                        : 1;  /* bit[15]   : ���� */
        unsigned long  timing_int3_sys_cnt_evdo_80ms_pos : 2;  /* bit[16-17]:  */
        unsigned long  reserved_1                        : 14; /* bit[18-31]: ���� */
    } reg;
} CBBP_TIMING_INT3_SYS_CNT_EVDO_POS_UNION;
#define CBBP_TIMING_INT3_SYS_CNT_EVDO_POS_timing_int3_sys_cnt_evdo_26ms_pos_START  (0)
#define CBBP_TIMING_INT3_SYS_CNT_EVDO_POS_timing_int3_sys_cnt_evdo_26ms_pos_END    (14)
#define CBBP_TIMING_INT3_SYS_CNT_EVDO_POS_timing_int3_sys_cnt_evdo_80ms_pos_START  (16)
#define CBBP_TIMING_INT3_SYS_CNT_EVDO_POS_timing_int3_sys_cnt_evdo_80ms_pos_END    (17)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT3_EVDO_PERIOD_UNION
 �ṹ˵��  : TIMING_INT3_EVDO_PERIOD �Ĵ����ṹ���塣��ַƫ����:0x0144����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int3_evdo_period_reg;
    struct
    {
        unsigned long  timing_int3_evdo_period : 4;  /* bit[0-3] : Int�ж�����ѡ��
                                                                   0����ʾ�ж�����Ϊ64chip��
                                                                   1����ʾ�ж�����Ϊ128chip��
                                                                   2����ʾ�ж�����Ϊ256chip��
                                                                   3����ʾ�ж�����Ϊ512chip��
                                                                   4����ʾ�ж�����Ϊ1024chip��
                                                                   5����ʾ�ж�����Ϊ2048chip��
                                                                   6����ʾ�ж�����Ϊ4096chip��
                                                                   7����ʾ�ж�����Ϊ8192chip��
                                                                   8����ʾ�ж�����Ϊ16384chip��
                                                                   9����ʾ�ж�����Ϊ32768chip��
                                                                   10����ʾ�ж�����Ϊ80ms�� */
        unsigned long  reserved                : 28; /* bit[4-31]: ���� */
    } reg;
} CBBP_TIMING_INT3_EVDO_PERIOD_UNION;
#define CBBP_TIMING_INT3_EVDO_PERIOD_timing_int3_evdo_period_START  (0)
#define CBBP_TIMING_INT3_EVDO_PERIOD_timing_int3_evdo_period_END    (3)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT3_EVDO_EN_UNION
 �ṹ˵��  : TIMING_INT3_EVDO_EN �Ĵ����ṹ���塣��ַƫ����:0x0148����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int3_evdo_en_reg;
    struct
    {
        unsigned long  timing_int3_evdo_en : 1;  /* bit[0]   : ��ʱ�ж�int��ʹ�ܡ�
                                                               0����ʾ������int�жϣ�
                                                               1����ʾ����int�жϣ� */
        unsigned long  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_TIMING_INT3_EVDO_EN_UNION;
#define CBBP_TIMING_INT3_EVDO_EN_timing_int3_evdo_en_START  (0)
#define CBBP_TIMING_INT3_EVDO_EN_timing_int3_evdo_en_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT4_SYS_CNT_EVDO_POS_UNION
 �ṹ˵��  : TIMING_INT4_SYS_CNT_EVDO_POS �Ĵ����ṹ���塣��ַƫ����:0x014C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int4_sys_cnt_evdo_pos_reg;
    struct
    {
        unsigned long  timing_int4_sys_cnt_evdo_26ms_pos : 15; /* bit[0-14] : Int��sys_cnt_evdo�ϵ�λ�ã�
                                                                              [17:16]��sys_cnt_evdo_80ms��ֵ��
                                                                              [14:0]��sys_cnt_evdo_26ms��ֵ��chip���ȣ� */
        unsigned long  reserved_0                        : 1;  /* bit[15]   : ���� */
        unsigned long  timing_int4_sys_cnt_evdo_80ms_pos : 2;  /* bit[16-17]:  */
        unsigned long  reserved_1                        : 14; /* bit[18-31]: ���� */
    } reg;
} CBBP_TIMING_INT4_SYS_CNT_EVDO_POS_UNION;
#define CBBP_TIMING_INT4_SYS_CNT_EVDO_POS_timing_int4_sys_cnt_evdo_26ms_pos_START  (0)
#define CBBP_TIMING_INT4_SYS_CNT_EVDO_POS_timing_int4_sys_cnt_evdo_26ms_pos_END    (14)
#define CBBP_TIMING_INT4_SYS_CNT_EVDO_POS_timing_int4_sys_cnt_evdo_80ms_pos_START  (16)
#define CBBP_TIMING_INT4_SYS_CNT_EVDO_POS_timing_int4_sys_cnt_evdo_80ms_pos_END    (17)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT4_EVDO_PERIOD_UNION
 �ṹ˵��  : TIMING_INT4_EVDO_PERIOD �Ĵ����ṹ���塣��ַƫ����:0x0150����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int4_evdo_period_reg;
    struct
    {
        unsigned long  timing_int4_evdo_period : 4;  /* bit[0-3] : Int�ж�����ѡ��
                                                                   0����ʾ�ж�����Ϊ64chip��
                                                                   1����ʾ�ж�����Ϊ128chip��
                                                                   2����ʾ�ж�����Ϊ256chip��
                                                                   3����ʾ�ж�����Ϊ512chip��
                                                                   4����ʾ�ж�����Ϊ1024chip��
                                                                   5����ʾ�ж�����Ϊ2048chip��
                                                                   6����ʾ�ж�����Ϊ4096chip��
                                                                   7����ʾ�ж�����Ϊ8192chip��
                                                                   8����ʾ�ж�����Ϊ16384chip��
                                                                   9����ʾ�ж�����Ϊ32768chip��
                                                                   10����ʾ�ж�����Ϊ80ms�� */
        unsigned long  reserved                : 28; /* bit[4-31]: ���� */
    } reg;
} CBBP_TIMING_INT4_EVDO_PERIOD_UNION;
#define CBBP_TIMING_INT4_EVDO_PERIOD_timing_int4_evdo_period_START  (0)
#define CBBP_TIMING_INT4_EVDO_PERIOD_timing_int4_evdo_period_END    (3)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT4_EVDO_EN_UNION
 �ṹ˵��  : TIMING_INT4_EVDO_EN �Ĵ����ṹ���塣��ַƫ����:0x0154����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int4_evdo_en_reg;
    struct
    {
        unsigned long  timing_int4_evdo_en : 1;  /* bit[0]   : ��ʱ�ж�int��ʹ�ܡ�
                                                               0����ʾ������int�жϣ�
                                                               1����ʾ����int�жϣ� */
        unsigned long  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_TIMING_INT4_EVDO_EN_UNION;
#define CBBP_TIMING_INT4_EVDO_EN_timing_int4_evdo_en_START  (0)
#define CBBP_TIMING_INT4_EVDO_EN_timing_int4_evdo_en_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT5_SYS_CNT_EVDO_POS_UNION
 �ṹ˵��  : TIMING_INT5_SYS_CNT_EVDO_POS �Ĵ����ṹ���塣��ַƫ����:0x0158����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int5_sys_cnt_evdo_pos_reg;
    struct
    {
        unsigned long  timing_int5_sys_cnt_evdo_26ms_pos : 15; /* bit[0-14] : Int��sys_cnt_evdo�ϵ�λ�ã�
                                                                              [17:16]��sys_cnt_evdo_80ms��ֵ��
                                                                              [14:0]��sys_cnt_evdo_26ms��ֵ��chip���ȣ� */
        unsigned long  reserved_0                        : 1;  /* bit[15]   : ���� */
        unsigned long  timing_int5_sys_cnt_evdo_80ms_pos : 2;  /* bit[16-17]:  */
        unsigned long  reserved_1                        : 14; /* bit[18-31]: ���� */
    } reg;
} CBBP_TIMING_INT5_SYS_CNT_EVDO_POS_UNION;
#define CBBP_TIMING_INT5_SYS_CNT_EVDO_POS_timing_int5_sys_cnt_evdo_26ms_pos_START  (0)
#define CBBP_TIMING_INT5_SYS_CNT_EVDO_POS_timing_int5_sys_cnt_evdo_26ms_pos_END    (14)
#define CBBP_TIMING_INT5_SYS_CNT_EVDO_POS_timing_int5_sys_cnt_evdo_80ms_pos_START  (16)
#define CBBP_TIMING_INT5_SYS_CNT_EVDO_POS_timing_int5_sys_cnt_evdo_80ms_pos_END    (17)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT5_EVDO_PERIOD_UNION
 �ṹ˵��  : TIMING_INT5_EVDO_PERIOD �Ĵ����ṹ���塣��ַƫ����:0x015C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int5_evdo_period_reg;
    struct
    {
        unsigned long  timing_int5_evdo_period : 4;  /* bit[0-3] : Int�ж�����ѡ��
                                                                   0����ʾ�ж�����Ϊ64chip��
                                                                   1����ʾ�ж�����Ϊ128chip��
                                                                   2����ʾ�ж�����Ϊ256chip��
                                                                   3����ʾ�ж�����Ϊ512chip��
                                                                   4����ʾ�ж�����Ϊ1024chip��
                                                                   5����ʾ�ж�����Ϊ2048chip��
                                                                   6����ʾ�ж�����Ϊ4096chip��
                                                                   7����ʾ�ж�����Ϊ8192chip��
                                                                   8����ʾ�ж�����Ϊ16384chip��
                                                                   9����ʾ�ж�����Ϊ32768chip��
                                                                   10����ʾ�ж�����Ϊ80ms�� */
        unsigned long  reserved                : 28; /* bit[4-31]: ���� */
    } reg;
} CBBP_TIMING_INT5_EVDO_PERIOD_UNION;
#define CBBP_TIMING_INT5_EVDO_PERIOD_timing_int5_evdo_period_START  (0)
#define CBBP_TIMING_INT5_EVDO_PERIOD_timing_int5_evdo_period_END    (3)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT5_EVDO_EN_UNION
 �ṹ˵��  : TIMING_INT5_EVDO_EN �Ĵ����ṹ���塣��ַƫ����:0x0160����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int5_evdo_en_reg;
    struct
    {
        unsigned long  timing_int5_evdo_en : 1;  /* bit[0]   : ��ʱ�ж�int��ʹ�ܡ�
                                                               0����ʾ������int�жϣ�
                                                               1����ʾ����int�жϣ� */
        unsigned long  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_TIMING_INT5_EVDO_EN_UNION;
#define CBBP_TIMING_INT5_EVDO_EN_timing_int5_evdo_en_START  (0)
#define CBBP_TIMING_INT5_EVDO_EN_timing_int5_evdo_en_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT6_SYS_CNT_EVDO_POS_UNION
 �ṹ˵��  : TIMING_INT6_SYS_CNT_EVDO_POS �Ĵ����ṹ���塣��ַƫ����:0x0164����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int6_sys_cnt_evdo_pos_reg;
    struct
    {
        unsigned long  timing_int6_sys_cnt_evdo_26ms_pos : 15; /* bit[0-14] : Int��sys_cnt_evdo�ϵ�λ�ã�
                                                                              [17:16]��sys_cnt_evdo_80ms��ֵ��
                                                                              [14:0]��sys_cnt_evdo_26ms��ֵ��chip���ȣ� */
        unsigned long  reserved_0                        : 1;  /* bit[15]   : ���� */
        unsigned long  timing_int6_sys_cnt_evdo_80ms_pos : 2;  /* bit[16-17]:  */
        unsigned long  reserved_1                        : 14; /* bit[18-31]: ���� */
    } reg;
} CBBP_TIMING_INT6_SYS_CNT_EVDO_POS_UNION;
#define CBBP_TIMING_INT6_SYS_CNT_EVDO_POS_timing_int6_sys_cnt_evdo_26ms_pos_START  (0)
#define CBBP_TIMING_INT6_SYS_CNT_EVDO_POS_timing_int6_sys_cnt_evdo_26ms_pos_END    (14)
#define CBBP_TIMING_INT6_SYS_CNT_EVDO_POS_timing_int6_sys_cnt_evdo_80ms_pos_START  (16)
#define CBBP_TIMING_INT6_SYS_CNT_EVDO_POS_timing_int6_sys_cnt_evdo_80ms_pos_END    (17)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT6_EVDO_PERIOD_UNION
 �ṹ˵��  : TIMING_INT6_EVDO_PERIOD �Ĵ����ṹ���塣��ַƫ����:0x0168����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int6_evdo_period_reg;
    struct
    {
        unsigned long  timing_int6_evdo_period : 4;  /* bit[0-3] : Int�ж�����ѡ��
                                                                   0����ʾ�ж�����Ϊ64chip��
                                                                   1����ʾ�ж�����Ϊ128chip��
                                                                   2����ʾ�ж�����Ϊ256chip��
                                                                   3����ʾ�ж�����Ϊ512chip��
                                                                   4����ʾ�ж�����Ϊ1024chip��
                                                                   5����ʾ�ж�����Ϊ2048chip��
                                                                   6����ʾ�ж�����Ϊ4096chip��
                                                                   7����ʾ�ж�����Ϊ8192chip��
                                                                   8����ʾ�ж�����Ϊ16384chip��
                                                                   9����ʾ�ж�����Ϊ32768chip��
                                                                   10����ʾ�ж�����Ϊ80ms�� */
        unsigned long  reserved                : 28; /* bit[4-31]: ���� */
    } reg;
} CBBP_TIMING_INT6_EVDO_PERIOD_UNION;
#define CBBP_TIMING_INT6_EVDO_PERIOD_timing_int6_evdo_period_START  (0)
#define CBBP_TIMING_INT6_EVDO_PERIOD_timing_int6_evdo_period_END    (3)


/*****************************************************************************
 �ṹ��    : CBBP_TIMING_INT6_EVDO_EN_UNION
 �ṹ˵��  : TIMING_INT6_EVDO_EN �Ĵ����ṹ���塣��ַƫ����:0x016C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int6_evdo_en_reg;
    struct
    {
        unsigned long  timing_int6_evdo_en : 1;  /* bit[0]   : ��ʱ�ж�int��ʹ�ܡ�
                                                               0����ʾ������int�жϣ�
                                                               1����ʾ����int�жϣ� */
        unsigned long  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_TIMING_INT6_EVDO_EN_UNION;
#define CBBP_TIMING_INT6_EVDO_EN_timing_int6_evdo_en_START  (0)
#define CBBP_TIMING_INT6_EVDO_EN_timing_int6_evdo_en_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_EVDO_RPT_INT1_MASK_UNION
 �ṹ˵��  : SYS_CNT_EVDO_RPT_INT1_MASK �Ĵ����ṹ���塣��ַƫ����:0x0170����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_evdo_rpt_int1_mask_reg;
    struct
    {
        unsigned long  sys_cnt_evdo_rpt_int1_mask : 6;  /* bit[0-5] : ��������ϱ��ж�ʱ��sys_cnt_evdoֵ��mask��
                                                                      bit0��Ϊ1��ʾ�ϱ��ж�1ʱ�̵Ķ�ʱ��
                                                                      bit1��Ϊ1��ʾ�ϱ��ж�2ʱ�̵Ķ�ʱ��
                                                                      ��
                                                                      ע�⣺ͬһʱ��ֻ����1bitΪ1 */
        unsigned long  reserved                   : 26; /* bit[6-31]: ���� */
    } reg;
} CBBP_SYS_CNT_EVDO_RPT_INT1_MASK_UNION;
#define CBBP_SYS_CNT_EVDO_RPT_INT1_MASK_sys_cnt_evdo_rpt_int1_mask_START  (0)
#define CBBP_SYS_CNT_EVDO_RPT_INT1_MASK_sys_cnt_evdo_rpt_int1_mask_END    (5)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_EVDO_RPT_INT1_UNION
 �ṹ˵��  : SYS_CNT_EVDO_RPT_INT1 �Ĵ����ṹ���塣��ַƫ����:0x0174����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_evdo_rpt_int1_reg;
    struct
    {
        unsigned long  sys_cnt_evdo_rpt_int1 : 11; /* bit[0-10] : ������õĵ�1���ϱ���ʱ��Ϣ���ж�ʱ�̵�sys_cnt_evdo��ֵ��
                                                                  
                                                                  [10:0]��sys_cnt_evdo��ֵ��64chip���ȣ� */
        unsigned long  reserved              : 21; /* bit[11-31]: ���� */
    } reg;
} CBBP_SYS_CNT_EVDO_RPT_INT1_UNION;
#define CBBP_SYS_CNT_EVDO_RPT_INT1_sys_cnt_evdo_rpt_int1_START  (0)
#define CBBP_SYS_CNT_EVDO_RPT_INT1_sys_cnt_evdo_rpt_int1_END    (10)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_EVDO_RPT_INT2_MASK_UNION
 �ṹ˵��  : SYS_CNT_EVDO_RPT_INT2_MASK �Ĵ����ṹ���塣��ַƫ����:0x0178����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_evdo_rpt_int2_mask_reg;
    struct
    {
        unsigned long  sys_cnt_evdo_rpt_int2_mask : 6;  /* bit[0-5] : ��������ϱ��ж�ʱ��sys_cnt_evdoֵ��mask��
                                                                      bit0��Ϊ1��ʾ�ϱ��ж�1ʱ�̵Ķ�ʱ��
                                                                      bit1��Ϊ1��ʾ�ϱ��ж�2ʱ�̵Ķ�ʱ��
                                                                      ��
                                                                      ע�⣺ͬһʱ��ֻ����1bitΪ1 */
        unsigned long  reserved                   : 26; /* bit[6-31]: ���� */
    } reg;
} CBBP_SYS_CNT_EVDO_RPT_INT2_MASK_UNION;
#define CBBP_SYS_CNT_EVDO_RPT_INT2_MASK_sys_cnt_evdo_rpt_int2_mask_START  (0)
#define CBBP_SYS_CNT_EVDO_RPT_INT2_MASK_sys_cnt_evdo_rpt_int2_mask_END    (5)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_EVDO_RPT_INT2_UNION
 �ṹ˵��  : SYS_CNT_EVDO_RPT_INT2 �Ĵ����ṹ���塣��ַƫ����:0x0184����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_evdo_rpt_int2_reg;
    struct
    {
        unsigned long  sys_cnt_evdo_rpt_int2 : 11; /* bit[0-10] : ������õĵ�1���ϱ���ʱ��Ϣ���ж�ʱ�̵�sys_cnt_evdo��ֵ��
                                                                  
                                                                  [10:0]��sys_cnt_evdo��ֵ��64chip���ȣ� */
        unsigned long  reserved              : 21; /* bit[11-31]: ���� */
    } reg;
} CBBP_SYS_CNT_EVDO_RPT_INT2_UNION;
#define CBBP_SYS_CNT_EVDO_RPT_INT2_sys_cnt_evdo_rpt_int2_START  (0)
#define CBBP_SYS_CNT_EVDO_RPT_INT2_sys_cnt_evdo_rpt_int2_END    (10)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_EVDO_PERIOD_UNION
 �ṹ˵��  : SYS_CNT_EVDO_PERIOD �Ĵ����ṹ���塣��ַƫ����:0x017C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_evdo_period_reg;
    struct
    {
        unsigned long  sys_cnt_evdo_period : 1;  /* bit[0]   : 1xϵͳ������sys_cnt_evdo������
                                                               0��ʾ����Ϊ2s��
                                                               1��ʾ����Ϊ5.12s */
        unsigned long  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_SYS_CNT_EVDO_PERIOD_UNION;
#define CBBP_SYS_CNT_EVDO_PERIOD_sys_cnt_evdo_period_START  (0)
#define CBBP_SYS_CNT_EVDO_PERIOD_sys_cnt_evdo_period_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_EVDO_RPT2_UNION
 �ṹ˵��  : SYS_CNT_EVDO_RPT2 �Ĵ����ṹ���塣��ַƫ����:0x0188����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_evdo_rpt2_reg;
    struct
    {
        unsigned long  sys_cnt_evdo_26ms_rpt2  : 15; /* bit[0-14] : sys_cnt_evdo��ֵ��
                                                                    [29:24]��sys_cnt_evdo_5p12s��ֵ��
                                                                    [17:16]��sys_cnt_evdo_80ms��ֵ��
                                                                    [14:0]��sys_cnt_evdo_26ms��ֵ��chip���ȣ�
                                                                    
                                                                    ���ֱ�Ӷ�ȡBBP�����BBPδ�����洦�����������ȡ2~3�Σ�ȷ����ȡ���ȶ���� */
        unsigned long  reserved_0              : 1;  /* bit[15]   : ���� */
        unsigned long  sys_cnt_evdo_80ms_rpt2  : 2;  /* bit[16-17]:  */
        unsigned long  reserved_1              : 6;  /* bit[18-23]: ���� */
        unsigned long  sys_cnt_evdo_5p12s_rpt2 : 6;  /* bit[24-29]:  */
        unsigned long  reserved_2              : 2;  /* bit[30-31]: ���� */
    } reg;
} CBBP_SYS_CNT_EVDO_RPT2_UNION;
#define CBBP_SYS_CNT_EVDO_RPT2_sys_cnt_evdo_26ms_rpt2_START   (0)
#define CBBP_SYS_CNT_EVDO_RPT2_sys_cnt_evdo_26ms_rpt2_END     (14)
#define CBBP_SYS_CNT_EVDO_RPT2_sys_cnt_evdo_80ms_rpt2_START   (16)
#define CBBP_SYS_CNT_EVDO_RPT2_sys_cnt_evdo_80ms_rpt2_END     (17)
#define CBBP_SYS_CNT_EVDO_RPT2_sys_cnt_evdo_5p12s_rpt2_START  (24)
#define CBBP_SYS_CNT_EVDO_RPT2_sys_cnt_evdo_5p12s_rpt2_END    (29)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_EVDO_RPT_INT3_MASK_UNION
 �ṹ˵��  : SYS_CNT_EVDO_RPT_INT3_MASK �Ĵ����ṹ���塣��ַƫ����:0x0190����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_evdo_rpt_int3_mask_reg;
    struct
    {
        unsigned long  sys_cnt_evdo_rpt_int3_mask : 6;  /* bit[0-5] : ��������ϱ��ж�ʱ��sys_cnt_evdoֵ��mask��
                                                                      bit0��Ϊ1��ʾ�ϱ��ж�1ʱ�̵Ķ�ʱ��
                                                                      bit1��Ϊ1��ʾ�ϱ��ж�2ʱ�̵Ķ�ʱ��
                                                                      ��
                                                                      ע�⣺ͬһʱ��ֻ����1bitΪ1 */
        unsigned long  reserved                   : 26; /* bit[6-31]: ���� */
    } reg;
} CBBP_SYS_CNT_EVDO_RPT_INT3_MASK_UNION;
#define CBBP_SYS_CNT_EVDO_RPT_INT3_MASK_sys_cnt_evdo_rpt_int3_mask_START  (0)
#define CBBP_SYS_CNT_EVDO_RPT_INT3_MASK_sys_cnt_evdo_rpt_int3_mask_END    (5)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_EVDO_RPT_INT3_UNION
 �ṹ˵��  : SYS_CNT_EVDO_RPT_INT3 �Ĵ����ṹ���塣��ַƫ����:0x0194����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_evdo_rpt_int3_reg;
    struct
    {
        unsigned long  sys_cnt_evdo_rpt_int3 : 11; /* bit[0-10] : ������õĵ�1���ϱ���ʱ��Ϣ���ж�ʱ�̵�sys_cnt_evdo��ֵ��
                                                                  
                                                                  [10:0]��sys_cnt_evdo��ֵ��64chip���ȣ� */
        unsigned long  reserved              : 21; /* bit[11-31]: ���� */
    } reg;
} CBBP_SYS_CNT_EVDO_RPT_INT3_UNION;
#define CBBP_SYS_CNT_EVDO_RPT_INT3_sys_cnt_evdo_rpt_int3_START  (0)
#define CBBP_SYS_CNT_EVDO_RPT_INT3_sys_cnt_evdo_rpt_int3_END    (10)


/*****************************************************************************
 �ṹ��    : CBBP_C_TIMING_MODE_EVDO_UNION
 �ṹ˵��  : C_TIMING_MODE_EVDO �Ĵ����ṹ���塣��ַƫ����:0x0198����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      c_timing_mode_evdo_reg;
    struct
    {
        unsigned long  c_timing_mode_evdo : 1;  /* bit[0]   : ��ǰϵͳ���Ƿ����evdo��ʱ��
                                                              1����ʾ����evdo��ʱ�� */
        unsigned long  reserved           : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_C_TIMING_MODE_EVDO_UNION;
#define CBBP_C_TIMING_MODE_EVDO_c_timing_mode_evdo_START  (0)
#define CBBP_C_TIMING_MODE_EVDO_c_timing_mode_evdo_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_C_TIMING_SEL_DBG_UNION
 �ṹ˵��  : C_TIMING_SEL_DBG �Ĵ����ṹ���塣��ַƫ����:0x0200����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      c_timing_sel_dbg_reg;
    struct
    {
        unsigned long  c_timing_sel_dbg : 1;  /* bit[0]   : C DBGģ�鶨ʱѡ��0��ʾѡ��1x��ʱ��1��ʾѡ��evdo��ʱ */
        unsigned long  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_C_TIMING_SEL_DBG_UNION;
#define CBBP_C_TIMING_SEL_DBG_c_timing_sel_dbg_START  (0)
#define CBBP_C_TIMING_SEL_DBG_c_timing_sel_dbg_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_BOTH_RD_UNION
 �ṹ˵��  : SYS_CNT_BOTH_RD �Ĵ����ṹ���塣��ַƫ����:0x0204����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_both_rd_reg;
    struct
    {
        unsigned long  sys_cnt_both_rd : 1;  /* bit[0]   : ���ͬʱ��ȡ1x��evdo��ʱ��ָʾ�ź� */
        unsigned long  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_SYS_CNT_BOTH_RD_UNION;
#define CBBP_SYS_CNT_BOTH_RD_sys_cnt_both_rd_START  (0)
#define CBBP_SYS_CNT_BOTH_RD_sys_cnt_both_rd_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_BOTH_RD_VALID_UNION
 �ṹ˵��  : SYS_CNT_BOTH_RD_VALID �Ĵ����ṹ���塣��ַƫ����:0x0208����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_both_rd_valid_reg;
    struct
    {
        unsigned long  sys_cnt_both_rd_valid : 1;  /* bit[0]   : ���ͬʱ��ȡ1x��evdo��ʱ����Ч�źţ�1��ʾ�ϱ��Ľ����Ч */
        unsigned long  reserved              : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_SYS_CNT_BOTH_RD_VALID_UNION;
#define CBBP_SYS_CNT_BOTH_RD_VALID_sys_cnt_both_rd_valid_START  (0)
#define CBBP_SYS_CNT_BOTH_RD_VALID_sys_cnt_both_rd_valid_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_BASE_CNT_BOTH_RPT_UNION
 �ṹ˵��  : BASE_CNT_BOTH_RPT �Ĵ����ṹ���塣��ַƫ����:0x020C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      base_cnt_both_rpt_reg;
    struct
    {
        unsigned long  base_cnt_26ms_both_rpt : 15; /* bit[0-14] : base_cnt��ֵ��
                                                                   [28:24]��base_cnt_2s�ϵ�ʱ�̣���ȡֵ��Χ0~24��
                                                                   [17:16]��base_cnt_80ms�ϵ�ʱ�̣�ȡֵ��Χ0~2��
                                                                   [14:0]��base_cnt_26ms�ϵ�ʱ�̣�ȡֵ��Χ0~32767��chip���ȣ� */
        unsigned long  reserved_0             : 1;  /* bit[15]   : ���� */
        unsigned long  base_cnt_80ms_both_rpt : 2;  /* bit[16-17]:  */
        unsigned long  reserved_1             : 6;  /* bit[18-23]: ���� */
        unsigned long  base_cnt_2s_both_rpt   : 5;  /* bit[24-28]:  */
        unsigned long  reserved_2             : 3;  /* bit[29-31]: ���� */
    } reg;
} CBBP_BASE_CNT_BOTH_RPT_UNION;
#define CBBP_BASE_CNT_BOTH_RPT_base_cnt_26ms_both_rpt_START  (0)
#define CBBP_BASE_CNT_BOTH_RPT_base_cnt_26ms_both_rpt_END    (14)
#define CBBP_BASE_CNT_BOTH_RPT_base_cnt_80ms_both_rpt_START  (16)
#define CBBP_BASE_CNT_BOTH_RPT_base_cnt_80ms_both_rpt_END    (17)
#define CBBP_BASE_CNT_BOTH_RPT_base_cnt_2s_both_rpt_START    (24)
#define CBBP_BASE_CNT_BOTH_RPT_base_cnt_2s_both_rpt_END      (28)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_1X_BOTH_RPT_UNION
 �ṹ˵��  : SYS_CNT_1X_BOTH_RPT �Ĵ����ṹ���塣��ַƫ����:0x0210����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_1x_both_rpt_reg;
    struct
    {
        unsigned long  sys_cnt_1x_1p25ms_both_rpt : 11; /* bit[0-10] : sys_cnt_1x��ֵ��
                                                                       [29:24]��sys_cnt_1x_5p12s��ֵ��
                                                                       [21:16]��sys_cnt_1x_80ms��ֵ��
                                                                       [10:0]��sys_cnt_1x_1p25ms��ֵ,chip���ȣ� */
        unsigned long  reserved_0                 : 5;  /* bit[11-15]: ���� */
        unsigned long  sys_cnt_1x_80ms_both_rpt   : 6;  /* bit[16-21]:  */
        unsigned long  reserved_1                 : 2;  /* bit[22-23]: ���� */
        unsigned long  sys_cnt_1x_5p12s_both_rpt  : 6;  /* bit[24-29]:  */
        unsigned long  reserved_2                 : 2;  /* bit[30-31]: ���� */
    } reg;
} CBBP_SYS_CNT_1X_BOTH_RPT_UNION;
#define CBBP_SYS_CNT_1X_BOTH_RPT_sys_cnt_1x_1p25ms_both_rpt_START  (0)
#define CBBP_SYS_CNT_1X_BOTH_RPT_sys_cnt_1x_1p25ms_both_rpt_END    (10)
#define CBBP_SYS_CNT_1X_BOTH_RPT_sys_cnt_1x_80ms_both_rpt_START    (16)
#define CBBP_SYS_CNT_1X_BOTH_RPT_sys_cnt_1x_80ms_both_rpt_END      (21)
#define CBBP_SYS_CNT_1X_BOTH_RPT_sys_cnt_1x_5p12s_both_rpt_START   (24)
#define CBBP_SYS_CNT_1X_BOTH_RPT_sys_cnt_1x_5p12s_both_rpt_END     (29)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_EVDO_BOTH_RPT_UNION
 �ṹ˵��  : SYS_CNT_EVDO_BOTH_RPT �Ĵ����ṹ���塣��ַƫ����:0x0218����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_evdo_both_rpt_reg;
    struct
    {
        unsigned long  sys_cnt_evdo_26ms_both_rpt  : 15; /* bit[0-14] : sys_cnt_evdo��ֵ��
                                                                        [29:24]��sys_cnt_evdo_5p12s��ֵ��
                                                                        [17:16]��sys_cnt_evdo_80ms��ֵ��
                                                                        [14:0]��sys_cnt_evdo_26ms��ֵ��chip���ȣ� */
        unsigned long  reserved_0                  : 1;  /* bit[15]   : ���� */
        unsigned long  sys_cnt_evdo_80ms_both_rpt  : 2;  /* bit[16-17]:  */
        unsigned long  reserved_1                  : 6;  /* bit[18-23]: ���� */
        unsigned long  sys_cnt_evdo_5p12s_both_rpt : 6;  /* bit[24-29]:  */
        unsigned long  reserved_2                  : 2;  /* bit[30-31]: ���� */
    } reg;
} CBBP_SYS_CNT_EVDO_BOTH_RPT_UNION;
#define CBBP_SYS_CNT_EVDO_BOTH_RPT_sys_cnt_evdo_26ms_both_rpt_START   (0)
#define CBBP_SYS_CNT_EVDO_BOTH_RPT_sys_cnt_evdo_26ms_both_rpt_END     (14)
#define CBBP_SYS_CNT_EVDO_BOTH_RPT_sys_cnt_evdo_80ms_both_rpt_START   (16)
#define CBBP_SYS_CNT_EVDO_BOTH_RPT_sys_cnt_evdo_80ms_both_rpt_END     (17)
#define CBBP_SYS_CNT_EVDO_BOTH_RPT_sys_cnt_evdo_5p12s_both_rpt_START  (24)
#define CBBP_SYS_CNT_EVDO_BOTH_RPT_sys_cnt_evdo_5p12s_both_rpt_END    (29)


/*****************************************************************************
 �ṹ��    : CBBP_SYS_CNT_BOTH_RD_CLR_UNION
 �ṹ˵��  : SYS_CNT_BOTH_RD_CLR �Ĵ����ṹ���塣��ַƫ����:0x0220����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_both_rd_clr_reg;
    struct
    {
        unsigned long  sys_cnt_both_rd_clr : 1;  /* bit[0]   : ���ͬʱ��ȡ1x��evdo��ʱ����Чָʾ�źŵ������ź� */
        unsigned long  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_SYS_CNT_BOTH_RD_CLR_UNION;
#define CBBP_SYS_CNT_BOTH_RD_CLR_sys_cnt_both_rd_clr_START  (0)
#define CBBP_SYS_CNT_BOTH_RD_CLR_sys_cnt_both_rd_clr_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_SLEEP_TIME_EVDO_UNION
 �ṹ˵��  : SLEEP_TIME_EVDO �Ĵ����ṹ���塣��ַƫ����:0x0228����ֵ:0x00000000�����:32
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
 �ṹ��    : CBBP_SSI_TRANS_COMP_EVDO_UNION
 �ṹ˵��  : SSI_TRANS_COMP_EVDO �Ĵ����ṹ���塣��ַƫ����:0x022C����ֵ:0x0000000A�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ssi_trans_comp_evdo_reg;
    struct
    {
        unsigned long  ssi_trans_comp_evdo : 5;  /* bit[0-4] : ����ʱ��ʹ�ô��пڴ��䶨ʱ��Ϣ��ʱ�䣬��λchip */
        unsigned long  reserved            : 27; /* bit[5-31]: ���� */
    } reg;
} CBBP_SSI_TRANS_COMP_EVDO_UNION;
#define CBBP_SSI_TRANS_COMP_EVDO_ssi_trans_comp_evdo_START  (0)
#define CBBP_SSI_TRANS_COMP_EVDO_ssi_trans_comp_evdo_END    (4)


/***======================================================================***
                     (3/20) register_define_c_intr
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : CBBP_ARM_INT04_EN_UNION
 �ṹ˵��  : ARM_INT04_EN �Ĵ����ṹ���塣��ַƫ����:0x08����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_int04_en_reg;
    struct
    {
        unsigned long  c_arm_int04_en : 1;  /* bit[0]   : �ж�04ʹ�ܼĴ�����1����ʾʹ���жϣ�0����ʾ��ʹ���жϡ� */
        unsigned long  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_ARM_INT04_EN_UNION;
#define CBBP_ARM_INT04_EN_c_arm_int04_en_START  (0)
#define CBBP_ARM_INT04_EN_c_arm_int04_en_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_ARM_OVERTIME_CFG_UNION
 �ṹ˵��  : ARM_OVERTIME_CFG �Ĵ����ṹ���塣��ַƫ����:0x10����ֵ:0x0000001E�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_overtime_cfg_reg;
    struct
    {
        unsigned long  c_arm_int04_overtime : 7;  /* bit[0-6] : ARM_INT04��ʱʱ�䡣
                                                                ��ʱʱ�䵥λȡ����OVERTIME_BASE�����Ӧ��������OVERTIME_BASE */
        unsigned long  c_arm_int04_oten     : 1;  /* bit[7]   : ARM_INT04��ʱʹ�ܣ��ߵ�ƽ��Ч�� */
        unsigned long  reserved             : 24; /* bit[8-31]: ���� */
    } reg;
} CBBP_ARM_OVERTIME_CFG_UNION;
#define CBBP_ARM_OVERTIME_CFG_c_arm_int04_overtime_START  (0)
#define CBBP_ARM_OVERTIME_CFG_c_arm_int04_overtime_END    (6)
#define CBBP_ARM_OVERTIME_CFG_c_arm_int04_oten_START      (7)
#define CBBP_ARM_OVERTIME_CFG_c_arm_int04_oten_END        (7)


/*****************************************************************************
 �ṹ��    : CBBP_INT_DELAY_CLK_UNION
 �ṹ˵��  : INT_DELAY_CLK �Ĵ����ṹ���塣��ַƫ����:0x18����ֵ:0x0000000F�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      int_delay_clk_reg;
    struct
    {
        unsigned long  c_int_dly_clk : 16; /* bit[0-15] : ���ж�©����ӳ�ʱ�䣬��λIMIʱ�ӡ�0����ֹ���ã�1����ʾ�ӳ�һ��IMIʱ�ӣ���������������Ϊ��0ֵ�� */
        unsigned long  reserved      : 16; /* bit[16-31]: ���� */
    } reg;
} CBBP_INT_DELAY_CLK_UNION;
#define CBBP_INT_DELAY_CLK_c_int_dly_clk_START  (0)
#define CBBP_INT_DELAY_CLK_c_int_dly_clk_END    (15)


/*****************************************************************************
 �ṹ��    : CBBP_ARM_INT4_OT_NUM_UNION
 �ṹ˵��  : ARM_INT4_OT_NUM �Ĵ����ṹ���塣��ַƫ����:0x1C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_int4_ot_num_reg;
    struct
    {
        unsigned long  c_arm_int04_ot_num : 16; /* bit[0-15] : arm_int04�жϳ�ʱ������ */
        unsigned long  reserved           : 16; /* bit[16-31]: ���� */
    } reg;
} CBBP_ARM_INT4_OT_NUM_UNION;
#define CBBP_ARM_INT4_OT_NUM_c_arm_int04_ot_num_START  (0)
#define CBBP_ARM_INT4_OT_NUM_c_arm_int04_ot_num_END    (15)


/*****************************************************************************
 �ṹ��    : CBBP_OVERTIME_BASE_UNION
 �ṹ˵��  : OVERTIME_BASE �Ĵ����ṹ���塣��ַƫ����:0x20����ֵ:0x00030D40�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      overtime_base_reg;
    struct
    {
        unsigned long  c_overtime_base : 18; /* bit[0-17] : 1ms��IMIʱ�Ӹ�����������ݵ�ǰIMIʱ��Ƶ�����ã�Ĭ��ֵΪIMIʱ��Ƶ��Ϊ200MHzʱ��1ms��ʱ�Ӹ����� */
        unsigned long  reserved        : 14; /* bit[18-31]: ���� */
    } reg;
} CBBP_OVERTIME_BASE_UNION;
#define CBBP_OVERTIME_BASE_c_overtime_base_START  (0)
#define CBBP_OVERTIME_BASE_c_overtime_base_END    (17)


/*****************************************************************************
 �ṹ��    : CBBP_BBE16_INT03_STA_UNION
 �ṹ˵��  : BBE16_INT03_STA �Ĵ����ṹ���塣��ַƫ����:0x30����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbe16_int03_sta_reg;
    struct
    {
        unsigned long  bbe16_int03_sta : 7;  /* bit[0-6] : �ྶ����/С�������ж�״̬�Ĵ�����1����ʾ��Ӧ����λ�����жϣ�0����ʾ��Ӧ����λ��û���жϡ�
                                                           bit[0] �ྶ����/С��������Ԫ0�жϣ��ϱ�����Ϊ768chip(1x)/1024chip(evdo)/4096(evdo)       
                                                           bit[1] �ྶ����/С��������Ԫ1�жϣ��ϱ�����Ϊ768chip(1x)/1024chip(evdo)/4096(evdo)��       
                                                           bit[2] �ྶ����/С��������Ԫ2�жϣ��ϱ�����Ϊ768chip(1x)/1024chip(evdo)/4096(evdo)��       
                                                           bit[3] �ྶ����/С��������Ԫ3�жϣ��ϱ�����Ϊ768chip(1x)/1024chip(evdo)/4096(evdo)��       
                                                           bit[4] С�������Ͷྶ�������ݴ洢�����жϣ�
                                                           bit[5] С���Ͷྶ�����ϲ��ж�0
                                                           bit[6] С���Ͷྶ�����ϲ��ж�1
                                                           ����������жϺϲ����絥Ԫ0�͵�Ԫ1�ϲ��ϱ�����ֻ�ϱ��ϲ��жϣ��������ϱ���Ԫ0��1���жϡ� */
        unsigned long  reserved        : 25; /* bit[7-31]: ���� */
    } reg;
} CBBP_BBE16_INT03_STA_UNION;
#define CBBP_BBE16_INT03_STA_bbe16_int03_sta_START  (0)
#define CBBP_BBE16_INT03_STA_bbe16_int03_sta_END    (6)


/*****************************************************************************
 �ṹ��    : CBBP_BBE16_INT03_MASK_UNION
 �ṹ˵��  : BBE16_INT03_MASK �Ĵ����ṹ���塣��ַƫ����:0x34����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbe16_int03_mask_reg;
    struct
    {
        unsigned long  bbe16_int03_mask : 7;  /* bit[0-6] : �ྶ����/С�������ж����μĴ�����1����ʾ������Ӧ����λ�õ��жϣ�0����ʾ��������Ӧ����λ�õ��жϡ� */
        unsigned long  reserved         : 25; /* bit[7-31]: ���� */
    } reg;
} CBBP_BBE16_INT03_MASK_UNION;
#define CBBP_BBE16_INT03_MASK_bbe16_int03_mask_START  (0)
#define CBBP_BBE16_INT03_MASK_bbe16_int03_mask_END    (6)


/*****************************************************************************
 �ṹ��    : CBBP_BBE16_INT03_EN_UNION
 �ṹ˵��  : BBE16_INT03_EN �Ĵ����ṹ���塣��ַƫ����:0x38����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbe16_int03_en_reg;
    struct
    {
        unsigned long  bbe16_int03_en : 1;  /* bit[0]   : �ж�ʹ�ܼĴ�����1����ʾʹ���жϣ�0����ʾ��ʹ���жϡ� */
        unsigned long  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_BBE16_INT03_EN_UNION;
#define CBBP_BBE16_INT03_EN_bbe16_int03_en_START  (0)
#define CBBP_BBE16_INT03_EN_bbe16_int03_en_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_BBE16_INT03_CLR_UNION
 �ṹ˵��  : BBE16_INT03_CLR �Ĵ����ṹ���塣��ַƫ����:0x3C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbe16_int03_clr_reg;
    struct
    {
        unsigned long  bbe16_int03_clr : 7;  /* bit[0-6] : �ྶ����/С�������ж�����Ĵ�����1����ʾ�����Ӧ����λ���жϣ�0����ʾ�������Ӧ����λ�õ��жϡ� */
        unsigned long  reserved        : 25; /* bit[7-31]: ���� */
    } reg;
} CBBP_BBE16_INT03_CLR_UNION;
#define CBBP_BBE16_INT03_CLR_bbe16_int03_clr_START  (0)
#define CBBP_BBE16_INT03_CLR_bbe16_int03_clr_END    (6)


/*****************************************************************************
 �ṹ��    : CBBP_BBE16_INT04_EN_UNION
 �ṹ˵��  : BBE16_INT04_EN �Ĵ����ṹ���塣��ַƫ����:0x48����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbe16_int04_en_reg;
    struct
    {
        unsigned long  bbe16_int04_en : 1;  /* bit[0]   : �ж�04ʹ�ܼĴ�����1����ʾʹ���жϣ�0����ʾ��ʹ���жϡ� */
        unsigned long  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_BBE16_INT04_EN_UNION;
#define CBBP_BBE16_INT04_EN_bbe16_int04_en_START  (0)
#define CBBP_BBE16_INT04_EN_bbe16_int04_en_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_BBE16_INT05_STA_UNION
 �ṹ˵��  : BBE16_INT05_STA �Ĵ����ṹ���塣��ַƫ����:0x50����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbe16_int05_sta_reg;
    struct
    {
        unsigned long  bbe16_int05_sta : 5;  /* bit[0-4] : ����/�����ж�״̬�Ĵ�����1����ʾ��Ӧ����λ�����жϣ�0����ʾ��Ӧ����λ��û���жϡ�
                                                           bit[0]������������жϣ�
                                                           bit[1] Reserve for timing       
                                                           bit[2] Reserve for timing
                                                           bit[3] Reserve for timing
                                                           bit[4]�����ϱ��жϣ�֪ͨ�����ȡ�������ݣ�  */
        unsigned long  reserved        : 27; /* bit[5-31]: ���� */
    } reg;
} CBBP_BBE16_INT05_STA_UNION;
#define CBBP_BBE16_INT05_STA_bbe16_int05_sta_START  (0)
#define CBBP_BBE16_INT05_STA_bbe16_int05_sta_END    (4)


/*****************************************************************************
 �ṹ��    : CBBP_BBE16_INT05_MASK_UNION
 �ṹ˵��  : BBE16_INT05_MASK �Ĵ����ṹ���塣��ַƫ����:0x54����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbe16_int05_mask_reg;
    struct
    {
        unsigned long  bbe16_int05_mask : 5;  /* bit[0-4] : ����/�����ж����μĴ�����1����ʾ������Ӧ����λ�õ��жϣ�0����ʾ��������Ӧ����λ�õ��жϡ� */
        unsigned long  reserved         : 27; /* bit[5-31]: ���� */
    } reg;
} CBBP_BBE16_INT05_MASK_UNION;
#define CBBP_BBE16_INT05_MASK_bbe16_int05_mask_START  (0)
#define CBBP_BBE16_INT05_MASK_bbe16_int05_mask_END    (4)


/*****************************************************************************
 �ṹ��    : CBBP_BBE16_INT05_EN_UNION
 �ṹ˵��  : BBE16_INT05_EN �Ĵ����ṹ���塣��ַƫ����:0x58����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbe16_int05_en_reg;
    struct
    {
        unsigned long  bbe16_int05_en : 1;  /* bit[0]   : �ж�ʹ�ܼĴ�����1����ʾʹ���жϣ�0����ʾ��ʹ���жϡ� */
        unsigned long  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_BBE16_INT05_EN_UNION;
#define CBBP_BBE16_INT05_EN_bbe16_int05_en_START  (0)
#define CBBP_BBE16_INT05_EN_bbe16_int05_en_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_BBE16_INT05_CLR_UNION
 �ṹ˵��  : BBE16_INT05_CLR �Ĵ����ṹ���塣��ַƫ����:0x5C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbe16_int05_clr_reg;
    struct
    {
        unsigned long  bbe16_int05_clr : 5;  /* bit[0-4] : ����/�����ж�����Ĵ�����1����ʾ�����Ӧ����λ���жϣ�0����ʾ�������Ӧ����λ�õ��жϡ� */
        unsigned long  reserved        : 27; /* bit[5-31]: ���� */
    } reg;
} CBBP_BBE16_INT05_CLR_UNION;
#define CBBP_BBE16_INT05_CLR_bbe16_int05_clr_START  (0)
#define CBBP_BBE16_INT05_CLR_bbe16_int05_clr_END    (4)


/*****************************************************************************
 �ṹ��    : CBBP_BBE16_INT06_STA_UNION
 �ṹ˵��  : BBE16_INT06_STA �Ĵ����ṹ���塣��ַƫ����:0x60����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbe16_int06_sta_reg;
    struct
    {
        unsigned long  bbe16_int06_sta : 5;  /* bit[0-4] : ��Ƶ�ϱ�/���ݰ����ж�״̬�Ĵ�����1����ʾ��Ӧ����λ�����жϣ�0����ʾ��Ӧ����λ��û���жϡ�
                                                           bit[0]ÿ��ʱ϶����һ�Σ�DSP�յ����жϺ��ȡPD����ټ��㣻
                                                           bit[1]��������1ǰ�����ݰ��˳����ϱ��жϣ�   
                                                           bit[2]��������2ǰ�����ݰ��˳����ϱ��жϣ�     
                                                           bit[3]����ǰ�����ݰ��˳����ϱ��жϣ� 
                                                           bit[4]����ǰ������BBPMST��������жϡ� */
        unsigned long  reserved        : 27; /* bit[5-31]: ���� */
    } reg;
} CBBP_BBE16_INT06_STA_UNION;
#define CBBP_BBE16_INT06_STA_bbe16_int06_sta_START  (0)
#define CBBP_BBE16_INT06_STA_bbe16_int06_sta_END    (4)


/*****************************************************************************
 �ṹ��    : CBBP_BBE16_INT06_MASK_UNION
 �ṹ˵��  : BBE16_INT06_MASK �Ĵ����ṹ���塣��ַƫ����:0x64����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbe16_int06_mask_reg;
    struct
    {
        unsigned long  bbe16_int06_mask : 5;  /* bit[0-4] : ��Ƶ�ϱ�/���ݰ����ж����μĴ�����1����ʾ������Ӧ����λ�õ��жϣ�0����ʾ��������Ӧ����λ�õ��жϡ� */
        unsigned long  reserved         : 27; /* bit[5-31]: ���� */
    } reg;
} CBBP_BBE16_INT06_MASK_UNION;
#define CBBP_BBE16_INT06_MASK_bbe16_int06_mask_START  (0)
#define CBBP_BBE16_INT06_MASK_bbe16_int06_mask_END    (4)


/*****************************************************************************
 �ṹ��    : CBBP_BBE16_INT06_EN_UNION
 �ṹ˵��  : BBE16_INT06_EN �Ĵ����ṹ���塣��ַƫ����:0x68����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbe16_int06_en_reg;
    struct
    {
        unsigned long  bbe16_int06_en : 1;  /* bit[0]   : �ж�ʹ�ܼĴ�����1����ʾʹ���жϣ�0����ʾ��ʹ���жϡ� */
        unsigned long  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_BBE16_INT06_EN_UNION;
#define CBBP_BBE16_INT06_EN_bbe16_int06_en_START  (0)
#define CBBP_BBE16_INT06_EN_bbe16_int06_en_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_BBE16_INT06_CLR_UNION
 �ṹ˵��  : BBE16_INT06_CLR �Ĵ����ṹ���塣��ַƫ����:0x6C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbe16_int06_clr_reg;
    struct
    {
        unsigned long  bbe16_int06_clr : 5;  /* bit[0-4] : ��Ƶ�ϱ�/���ݰ����ж�����Ĵ�����1����ʾ�����Ӧ����λ���жϣ�0����ʾ�������Ӧ����λ�õ��жϡ� */
        unsigned long  reserved        : 27; /* bit[5-31]: ���� */
    } reg;
} CBBP_BBE16_INT06_CLR_UNION;
#define CBBP_BBE16_INT06_CLR_bbe16_int06_clr_START  (0)
#define CBBP_BBE16_INT06_CLR_bbe16_int06_clr_END    (4)


/*****************************************************************************
 �ṹ��    : CBBP_BBE16_OVERTIME_CFG_UNION
 �ṹ˵��  : BBE16_OVERTIME_CFG �Ĵ����ṹ���塣��ַƫ����:0x70����ֵ:0x1E1E1E1E�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbe16_overtime_cfg_reg;
    struct
    {
        unsigned long  bbe16_int03_overtime : 7;  /* bit[0-6]  : bbe16_INT03��ʱʱ�䡣
                                                                 ��ʱʱ�䵥λȡ����OVERTIME_BASE�����Ӧ��������OVERTIME_BASE */
        unsigned long  bbe16_int03_oten     : 1;  /* bit[7]    : bbe16_INT03��ʱʹ�ܣ��ߵ�ƽ��Ч�� */
        unsigned long  bbe16_int04_overtime : 7;  /* bit[8-14] : bbe16_INT04��ʱʱ�䡣
                                                                 ��ʱʱ�䵥λȡ����OVERTIME_BASE�����Ӧ��������OVERTIME_BASE */
        unsigned long  bbe16_int04_oten     : 1;  /* bit[15]   : bbe16_INT04��ʱʹ�ܣ��ߵ�ƽ��Ч�� */
        unsigned long  bbe16_int05_overtime : 7;  /* bit[16-22]: bbe16_INT05��ʱʱ�䡣
                                                                 ��ʱʱ�䵥λȡ����OVERTIME_BASE�����Ӧ��������OVERTIME_BASE */
        unsigned long  bbe16_int05_oten     : 1;  /* bit[23]   : bbe16_INT05��ʱʹ�ܣ��ߵ�ƽ��Ч�� */
        unsigned long  bbe16_int06_overtime : 7;  /* bit[24-30]: BBE16_INT06��ʱʱ�䡣
                                                                 ��ʱʱ�䵥λȡ����OVERTIME_BASE�����Ӧ��������OVERTIME_BASE */
        unsigned long  bbe16_int06_oten     : 1;  /* bit[31]   : BBE16_INT06��ʱʹ�ܣ��ߵ�ƽ��Ч�� */
    } reg;
} CBBP_BBE16_OVERTIME_CFG_UNION;
#define CBBP_BBE16_OVERTIME_CFG_bbe16_int03_overtime_START  (0)
#define CBBP_BBE16_OVERTIME_CFG_bbe16_int03_overtime_END    (6)
#define CBBP_BBE16_OVERTIME_CFG_bbe16_int03_oten_START      (7)
#define CBBP_BBE16_OVERTIME_CFG_bbe16_int03_oten_END        (7)
#define CBBP_BBE16_OVERTIME_CFG_bbe16_int04_overtime_START  (8)
#define CBBP_BBE16_OVERTIME_CFG_bbe16_int04_overtime_END    (14)
#define CBBP_BBE16_OVERTIME_CFG_bbe16_int04_oten_START      (15)
#define CBBP_BBE16_OVERTIME_CFG_bbe16_int04_oten_END        (15)
#define CBBP_BBE16_OVERTIME_CFG_bbe16_int05_overtime_START  (16)
#define CBBP_BBE16_OVERTIME_CFG_bbe16_int05_overtime_END    (22)
#define CBBP_BBE16_OVERTIME_CFG_bbe16_int05_oten_START      (23)
#define CBBP_BBE16_OVERTIME_CFG_bbe16_int05_oten_END        (23)
#define CBBP_BBE16_OVERTIME_CFG_bbe16_int06_overtime_START  (24)
#define CBBP_BBE16_OVERTIME_CFG_bbe16_int06_overtime_END    (30)
#define CBBP_BBE16_OVERTIME_CFG_bbe16_int06_oten_START      (31)
#define CBBP_BBE16_OVERTIME_CFG_bbe16_int06_oten_END        (31)


/*****************************************************************************
 �ṹ��    : CBBP_INT_OVERTIME_FLAG_UNION
 �ṹ˵��  : INT_OVERTIME_FLAG �Ĵ����ṹ���塣��ַƫ����:0x74����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      int_overtime_flag_reg;
    struct
    {
        unsigned long  int_overtime_set : 5;  /* bit[0-4] : �жϳ�ʱָʾ���ߵ�ƽ��Ч��
                                                            bit[0]��bbe16_INT03��
                                                            bit[1]��bbe16_INT04��
                                                            bit[2]��bbe16_INT05��
                                                            bit[3]��bbe16_INT06��
                                                            bit[4]��arm_INT04�� */
        unsigned long  reserved         : 27; /* bit[5-31]: ���� */
    } reg;
} CBBP_INT_OVERTIME_FLAG_UNION;
#define CBBP_INT_OVERTIME_FLAG_int_overtime_set_START  (0)
#define CBBP_INT_OVERTIME_FLAG_int_overtime_set_END    (4)


/*****************************************************************************
 �ṹ��    : CBBP_BBE16_INT34_OT_NUM_UNION
 �ṹ˵��  : BBE16_INT34_OT_NUM �Ĵ����ṹ���塣��ַƫ����:0x78����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbe16_int34_ot_num_reg;
    struct
    {
        unsigned long  bbe16_int03_ot_num : 16; /* bit[0-15] : bbe16_int03�жϳ�ʱ������ */
        unsigned long  bbe16_int04_ot_num : 16; /* bit[16-31]: BBE16_int04�жϳ�ʱ������ */
    } reg;
} CBBP_BBE16_INT34_OT_NUM_UNION;
#define CBBP_BBE16_INT34_OT_NUM_bbe16_int03_ot_num_START  (0)
#define CBBP_BBE16_INT34_OT_NUM_bbe16_int03_ot_num_END    (15)
#define CBBP_BBE16_INT34_OT_NUM_bbe16_int04_ot_num_START  (16)
#define CBBP_BBE16_INT34_OT_NUM_bbe16_int04_ot_num_END    (31)


/*****************************************************************************
 �ṹ��    : CBBP_BBE16_INT56_OT_NUM_UNION
 �ṹ˵��  : BBE16_INT56_OT_NUM �Ĵ����ṹ���塣��ַƫ����:0x7C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bbe16_int56_ot_num_reg;
    struct
    {
        unsigned long  bbe16_int05_ot_num : 16; /* bit[0-15] : bbe16_int05�жϳ�ʱ������ */
        unsigned long  bbe16_int06_ot_num : 16; /* bit[16-31]: BBE16_int06�жϳ�ʱ������ */
    } reg;
} CBBP_BBE16_INT56_OT_NUM_UNION;
#define CBBP_BBE16_INT56_OT_NUM_bbe16_int05_ot_num_START  (0)
#define CBBP_BBE16_INT56_OT_NUM_bbe16_int05_ot_num_END    (15)
#define CBBP_BBE16_INT56_OT_NUM_bbe16_int06_ot_num_START  (16)
#define CBBP_BBE16_INT56_OT_NUM_bbe16_int06_ot_num_END    (31)


/*****************************************************************************
 �ṹ��    : CBBP_CS_MPS_GRP_INT_MODE_UNION
 �ṹ˵��  : CS_MPS_GRP_INT_MODE �Ĵ����ṹ���塣��ַƫ����:0x0080����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      cs_mps_grp_int_mode_reg;
    struct
    {
        unsigned long  cs_mps_grp0_int_mode : 5;  /* bit[0-4]  : С���Ͷྶ����Group0�жϺϲ��ϱ�ģʽ��[3:0]��ʾ��Ӧ��Ԫ3~0�жϣ�bit[4]��ʾ�洢��Ԫ�жϣ�
                                                                 ��Ӧbit����Ϊ1��ʾ��Ӧ��Ԫ�ж���Group1�ϲ��ϱ����ϲ��жϵ�����˵�������ӿ�˵����ġ��жϡ��½� */
        unsigned long  cs_mps_grp1_int_mode : 5;  /* bit[5-9]  : С���Ͷྶ����Group1�жϺϲ��ϱ�ģʽ��[8:5]��ʾ��Ӧ��Ԫ3~0�жϣ�bit[9]��ʾ�洢��Ԫ�жϣ�
                                                                 ��Ӧbit����Ϊ1��ʾ��Ӧ��Ԫ�ж���Group1�ϲ��ϱ����ϲ��жϵ�����˵�������ӿ�˵����ġ��жϡ��½� */
        unsigned long  reserved             : 22; /* bit[10-31]: ���� */
    } reg;
} CBBP_CS_MPS_GRP_INT_MODE_UNION;
#define CBBP_CS_MPS_GRP_INT_MODE_cs_mps_grp0_int_mode_START  (0)
#define CBBP_CS_MPS_GRP_INT_MODE_cs_mps_grp0_int_mode_END    (4)
#define CBBP_CS_MPS_GRP_INT_MODE_cs_mps_grp1_int_mode_START  (5)
#define CBBP_CS_MPS_GRP_INT_MODE_cs_mps_grp1_int_mode_END    (9)


/***======================================================================***
                     (4/20) register_define_c_cs_mps_store
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : CBBP_DATA_STORE_LENGTH_UNION
 �ṹ˵��  : DATA_STORE_LENGTH �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      data_store_length_reg;
    struct
    {
        unsigned long  data_store_length : 13; /* bit[0-12] : �洢���ݳ��ȣ�chip��λ��
                                                              ����Ŀǰ�㷨��
                                                              1xС������ʱ���洢����2048chip
                                                              EvdoС������ʱ���洢����64x32=2048chip��64x16=1024chip��64x8=512chip
                                                              1xС������ʱ��64x12����ɣ�x4������ɣ�=3072chip��
                                                              EvdoС������ʱ��96x4����ɣ�x8������ɣ�=3072chip�� */
        unsigned long  reserved          : 19; /* bit[13-31]: ���� */
    } reg;
} CBBP_DATA_STORE_LENGTH_UNION;
#define CBBP_DATA_STORE_LENGTH_data_store_length_START  (0)
#define CBBP_DATA_STORE_LENGTH_data_store_length_END    (12)


/*****************************************************************************
 �ṹ��    : CBBP_DATA_STORE_MODE_UNION
 �ṹ˵��  : DATA_STORE_MODE �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      data_store_mode_reg;
    struct
    {
        unsigned long  data_store_mode : 3;  /* bit[0-2] : ���ݴ洢��ʽ��
                                                           0��ʾ�����洢��
                                                           1��ʾÿ1024chip����64chip��
                                                           2��ʾÿ1024chip����96chip��
                                                           3��ʾÿ1024chip����128chip��
                                                           4��ʾÿ1024chip����256chip��
                                                           5��ʾÿ1024chip����512chip�� */
        unsigned long  reserved        : 29; /* bit[3-31]: ���� */
    } reg;
} CBBP_DATA_STORE_MODE_UNION;
#define CBBP_DATA_STORE_MODE_data_store_mode_START  (0)
#define CBBP_DATA_STORE_MODE_data_store_mode_END    (2)


/*****************************************************************************
 �ṹ��    : CBBP_DATA_STORE_POS_UNION
 �ṹ˵��  : DATA_STORE_POS �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      data_store_pos_reg;
    struct
    {
        unsigned long  data_store_pos : 16; /* bit[0-15] : �洢���ݵ���ʼλ�ã���base_cnt[21:6]�ϵ�λ�ã�1/2chip���� */
        unsigned long  reserved       : 16; /* bit[16-31]: ���� */
    } reg;
} CBBP_DATA_STORE_POS_UNION;
#define CBBP_DATA_STORE_POS_data_store_pos_START  (0)
#define CBBP_DATA_STORE_POS_data_store_pos_END    (15)


/*****************************************************************************
 �ṹ��    : CBBP_DATA_STORE_ANT_UNION
 �ṹ˵��  : DATA_STORE_ANT �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      data_store_ant_reg;
    struct
    {
        unsigned long  data_store_ant : 1;  /* bit[0]   : �洢��������ѡ��
                                                          Ϊ0��ʾ�洢��������1������
                                                          Ϊ1��ʾ�洢��������2������ */
        unsigned long  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_DATA_STORE_ANT_UNION;
#define CBBP_DATA_STORE_ANT_data_store_ant_START  (0)
#define CBBP_DATA_STORE_ANT_data_store_ant_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_DATA_STORE_POS_SEL_UNION
 �ṹ˵��  : DATA_STORE_POS_SEL �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      data_store_pos_sel_reg;
    struct
    {
        unsigned long  data_store_pos_sel : 1;  /* bit[0]   : �洢������ʼλ��ѡ���źţ�
                                                              0��ʾ���Ծͽ���ʼ�洢���ݣ�
                                                              1��ʾ����ȵ� Data_store_pos�����ܿ�ʼ�洢���ݣ� */
        unsigned long  reserved           : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_DATA_STORE_POS_SEL_UNION;
#define CBBP_DATA_STORE_POS_SEL_data_store_pos_sel_START  (0)
#define CBBP_DATA_STORE_POS_SEL_data_store_pos_sel_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_DATA_STORE_CK_BYPASS_UNION
 �ṹ˵��  : DATA_STORE_CK_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      data_store_ck_bypass_reg;
    struct
    {
        unsigned long  data_store_ck_bypass : 1;  /* bit[0]   : �Զ�ʱ���ſ�bypass��1��ʾʱ�ӳ��� */
        unsigned long  reserved             : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_DATA_STORE_CK_BYPASS_UNION;
#define CBBP_DATA_STORE_CK_BYPASS_data_store_ck_bypass_START  (0)
#define CBBP_DATA_STORE_CK_BYPASS_data_store_ck_bypass_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_DATA_STORE_EN_UNION
 �ṹ˵��  : DATA_STORE_EN �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      data_store_en_reg;
    struct
    {
        unsigned long  data_store_en : 1;  /* bit[0]   : ���ݴ洢ģ��ʹ�ܣ���Ϊ��ģ�����ʹ�ܣ������Ʊ�ģ���ʱ�ӿ���
                                                         �� Data_store_start֮ǰ����Ϊ1���ڽ��յ��жϺ�����Ϊ0 */
        unsigned long  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_DATA_STORE_EN_UNION;
#define CBBP_DATA_STORE_EN_data_store_en_START  (0)
#define CBBP_DATA_STORE_EN_data_store_en_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_DATA_STORE_START_UNION
 �ṹ˵��  : DATA_STORE_START �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      data_store_start_reg;
    struct
    {
        unsigned long  data_store_start : 1;  /* bit[0]   : �洢�������������ź� */
        unsigned long  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_DATA_STORE_START_UNION;
#define CBBP_DATA_STORE_START_data_store_start_START  (0)
#define CBBP_DATA_STORE_START_data_store_start_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_DSP_RD_DATA_START_UNION
 �ṹ˵��  : DSP_RD_DATA_START �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_rd_data_start_reg;
    struct
    {
        unsigned long  dsp_rd_data_start : 1;  /* bit[0]   : FPGAר��
                                                             ������ȡ�������ݵĿ�ʼ�źţ�BBP��⵽���źź󣬽���ȡ��ַ�ָ�����һ�����ݵ�λ�� */
        unsigned long  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_DSP_RD_DATA_START_UNION;
#define CBBP_DSP_RD_DATA_START_dsp_rd_data_start_START  (0)
#define CBBP_DSP_RD_DATA_START_dsp_rd_data_start_END    (0)


/***======================================================================***
                     (5/20) register_define_c_cs_mps_unit0
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_CLK_MODE_UNION
 �ṹ˵��  : UNIT0_CLK_MODE �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_clk_mode_reg;
    struct
    {
        unsigned long  unit0_clk_mode : 1;  /* bit[0]   : ������Ԫʱ��Ƶ��ѡ��
                                                          0����ʾ������Ԫ128��ʱ�ӣ�
                                                          1����ʾ������Ԫ64��ʱ��
                                                          Ĭ�ϲ���Ҫ������� */
        unsigned long  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_UNIT0_CLK_MODE_UNION;
#define CBBP_UNIT0_CLK_MODE_unit0_clk_mode_START  (0)
#define CBBP_UNIT0_CLK_MODE_unit0_clk_mode_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_CORR_RPT_PERIOD_UNION
 �ṹ˵��  : UNIT0_CORR_RPT_PERIOD �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_corr_rpt_period_reg;
    struct
    {
        unsigned long  unit0_corr_rpt_period : 4;  /* bit[0-3] : ʹ���������ݶྶ��������С��������ʱ�����ٸ�����ۼӽ���ϱ�һ�Ρ�
                                                                 �˽ӿ���Ҫ�ǽ��afcʧ��ʱ��1x������ۼӳ���Ϊ64chip������ɽ���ϱ�����̫�ܼ������⡣
                                                                 ����1x��afcʧ��ʱ����������ȡ12����ÿ64x12=768chip�ڣ��ϱ���һ��64chip������ɽ����
                                                                 ����1x��afc����ʱ����������ȡ1����ÿ64x12=768chip�ϱ�һ������ۼӽ����
                                                                 ����evdoʱ����������ȡ1����ÿ1024chip��afcʧ������4096chip��afc�������ϱ�һ����ɽ���� */
        unsigned long  reserved              : 28; /* bit[4-31]: ���� */
    } reg;
} CBBP_UNIT0_CORR_RPT_PERIOD_UNION;
#define CBBP_UNIT0_CORR_RPT_PERIOD_unit0_corr_rpt_period_START  (0)
#define CBBP_UNIT0_CORR_RPT_PERIOD_unit0_corr_rpt_period_END    (3)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_CORR_WAIT_CHIP_UNION
 �ṹ˵��  : UNIT0_CORR_WAIT_CHIP �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_corr_wait_chip_reg;
    struct
    {
        unsigned long  unit0_corr_wait_chip : 11; /* bit[0-10] : ʹ����ɢ��������С������ʱ��ÿ����1024chip�ڵ�һ�����ݣ��ȴ��೤ʱ�䣬������һ��1024chip������λchip��
                                                                 �˽ӿ���Ҫ���ʹ����ɢ�����������С������ʱ���ж��ϱ��ܼ��������
                                                                 ���ڶྶ����ģʽ��BBP���������ۼӣ�������ʱ���������� */
        unsigned long  reserved             : 21; /* bit[11-31]: ���� */
    } reg;
} CBBP_UNIT0_CORR_WAIT_CHIP_UNION;
#define CBBP_UNIT0_CORR_WAIT_CHIP_unit0_corr_wait_chip_START  (0)
#define CBBP_UNIT0_CORR_WAIT_CHIP_unit0_corr_wait_chip_END    (10)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_ANT_SEL_UNION
 �ṹ˵��  : UNIT0_ANT_SEL �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_ant_sel_reg;
    struct
    {
        unsigned long  unit0_ant_sel : 1;  /* bit[0]   : ������������ѡ��
                                                         0����ʾ�����������1�����ݣ�
                                                         1����ʾ�����������2�����ݣ� */
        unsigned long  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_UNIT0_ANT_SEL_UNION;
#define CBBP_UNIT0_ANT_SEL_unit0_ant_sel_START  (0)
#define CBBP_UNIT0_ANT_SEL_unit0_ant_sel_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_MODE_UNION
 �ṹ˵��  : UNIT0_MODE �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_mode_reg;
    struct
    {
        unsigned long  unit0_mode : 2;  /* bit[0-1] : ģʽѡ��
                                                      0����ʾ��ʼС������
                                                      1����ʾpn�б�С������
                                                      2����ʾ�ྶ������С�����������������ۼӣ�
                                                      3����ʾС���������������ۼ��������ۼӣ� */
        unsigned long  reserved   : 30; /* bit[2-31]: ���� */
    } reg;
} CBBP_UNIT0_MODE_UNION;
#define CBBP_UNIT0_MODE_unit0_mode_START  (0)
#define CBBP_UNIT0_MODE_unit0_mode_END    (1)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_WIN_UNION
 �ṹ˵��  : UNIT0_WIN �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_win_reg;
    struct
    {
        unsigned long  unit0_win : 10; /* bit[0-9]  : ����������λΪ64chip�����÷�ΧΪ1~512��
                                                      
                                                      ��ʼС������ʱ����֧��������������������Ϊ128����������Ϊ64*128=8192chip��
                                                      PN�б�С������ʱ����֧������������������������̶�Ϊ64chip��
                                                      �ྶ��������֧��ʵʱ������������������̶�50chip��
                                                      С������ģʽ��С����������֧���������ݲ���������̶�Ϊ64chip */
        unsigned long  reserved  : 22; /* bit[10-31]: ���� */
    } reg;
} CBBP_UNIT0_WIN_UNION;
#define CBBP_UNIT0_WIN_unit0_win_START  (0)
#define CBBP_UNIT0_WIN_unit0_win_END    (9)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_DATA_SEL_UNION
 �ṹ˵��  : UNIT0_DATA_SEL �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_data_sel_reg;
    struct
    {
        unsigned long  unit0_data_sel : 1;  /* bit[0]   : ��������ѡ��
                                                          0����ʾʹ��ʵʱ���ݣ�
                                                          1����ʾʹ�û�������� */
        unsigned long  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_UNIT0_DATA_SEL_UNION;
#define CBBP_UNIT0_DATA_SEL_unit0_data_sel_START  (0)
#define CBBP_UNIT0_DATA_SEL_unit0_data_sel_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_DATA_STORE_MODE_UNION
 �ṹ˵��  : UNIT0_DATA_STORE_MODE �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_data_store_mode_reg;
    struct
    {
        unsigned long  unit0_data_store_mode : 3;  /* bit[0-2] : �������ݵ�ģʽ���˲������������һ�λ�������ʱ�Ĳ���Data_store_mode��ͬ
                                                                 0��ʾ�����洢��
                                                                 1��ʾÿ1024chip�洢64chip��
                                                                 2��ʾÿ1024chip�洢96chip��
                                                                 3��ʾÿ1024chip�洢128chip��
                                                                 4��ʾÿ1024chip�洢256chip��
                                                                 5��ʾÿ1024chip�洢512chip�� */
        unsigned long  reserved              : 29; /* bit[3-31]: ���� */
    } reg;
} CBBP_UNIT0_DATA_STORE_MODE_UNION;
#define CBBP_UNIT0_DATA_STORE_MODE_unit0_data_store_mode_START  (0)
#define CBBP_UNIT0_DATA_STORE_MODE_unit0_data_store_mode_END    (2)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_DATA_POS_UNION
 �ṹ˵��  : UNIT0_DATA_POS �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_data_pos_reg;
    struct
    {
        unsigned long  unit0_data_pos : 16; /* bit[0-15] : ʹ��ʵʱ����ʱ���������ݵ���ʼλ�ã���base_cnt[21:6]�ϵ�λ�ã�1/2chip���� */
        unsigned long  reserved       : 16; /* bit[16-31]: ���� */
    } reg;
} CBBP_UNIT0_DATA_POS_UNION;
#define CBBP_UNIT0_DATA_POS_unit0_data_pos_START  (0)
#define CBBP_UNIT0_DATA_POS_unit0_data_pos_END    (15)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_DATA_POS_SEL_UNION
 �ṹ˵��  : UNIT0_DATA_POS_SEL �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_data_pos_sel_reg;
    struct
    {
        unsigned long  unit0_data_pos_sel : 1;  /* bit[0]   : ʹ��ʵʱ����ʱ��Ч��
                                                              0����ʾ���Ծͽ���ʼ������
                                                              1������ȴ�Unit0_data_posʱ�����ܿ�ʼ������ */
        unsigned long  reserved           : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_UNIT0_DATA_POS_SEL_UNION;
#define CBBP_UNIT0_DATA_POS_SEL_unit0_data_pos_sel_START  (0)
#define CBBP_UNIT0_DATA_POS_SEL_unit0_data_pos_sel_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_DATA_MODE_UNION
 �ṹ˵��  : UNIT0_DATA_MODE �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_data_mode_reg;
    struct
    {
        unsigned long  unit0_data_mode : 3;  /* bit[0-2] : ��������ȡ����ʽ��
                                                           0��ʾ����ȡ����
                                                           1��ʾÿ1024chipȡ��64chip��
                                                           2��ʾÿ1024chipȡ��96chip��
                                                           3��ʾÿ1024chipȡ��128chip��
                                                           4��ʾÿ1024chipȡ��256chip��
                                                           5��ʾÿ1024chip�洢512chip��
                                                           
                                                           ˵����
                                                           ����ʹ�û������ݣ�����Unit0_data_store_modeȷ���������ݵ�������ұ�������Unit0_data_mode<=Unit0_data_store_mode��
                                                           ����ʹ��ʵʱ���ݣ����ʵ������ʱ���Ѿ������Unit0_data_posʱ�̣����������ȡ��ʱ����ʵ������ʱ�̿�ʼȡ��������ÿ1024chip���ȡ�����������64/96chip/128chip/256chipȡ��λ�ÿ�ʼȡ���� */
        unsigned long  reserved        : 29; /* bit[3-31]: ���� */
    } reg;
} CBBP_UNIT0_DATA_MODE_UNION;
#define CBBP_UNIT0_DATA_MODE_unit0_data_mode_START  (0)
#define CBBP_UNIT0_DATA_MODE_unit0_data_mode_END    (2)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_PN_NUM_UNION
 �ṹ˵��  : UNIT0_PN_NUM �Ĵ����ṹ���塣��ַƫ����:0x002C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn_num_reg;
    struct
    {
        unsigned long  unit0_pn_num : 5;  /* bit[0-4] : Pn�б�С������ʱ��pn offset������֧��1~16�� */
        unsigned long  reserved     : 27; /* bit[5-31]: ���� */
    } reg;
} CBBP_UNIT0_PN_NUM_UNION;
#define CBBP_UNIT0_PN_NUM_unit0_pn_num_START  (0)
#define CBBP_UNIT0_PN_NUM_unit0_pn_num_END    (4)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_CORR_LENGTH_UNION
 �ṹ˵��  : UNIT0_CORR_LENGTH �Ĵ����ṹ���塣��ַƫ����:0x0030����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_corr_length_reg;
    struct
    {
        unsigned long  unit0_corr_length : 4;  /* bit[0-3] : ��ɳ���
                                                             0��32
                                                             1��64
                                                             2��96
                                                             3��128
                                                             4��256
                                                             5��96*4=384
                                                             6��64*12=768
                                                             7��512
                                                             �㷨�Ƽ���
                                                             1xС����������ۼӳ��ȿ�����Ϊ64��128��256����Ӧ�ķ�����ۼӳ���Ϊ32��16��8��
                                                             evdoС��������ɳ���Ϊ64��������ۼӳ���Ϊ32/16/8��
                                                             1x�ྶ������ɳ���Ϊ64x12=768��afc��������64x1=64��afcʧ�������֣���Ӧ�ķ�����ۼӳ��ȷֱ�Ϊ8��96��
                                                             Evdo�ྶ������ɳ���96x4=384��afc��������96x1=96��afcʧ��������Ӧ�ķ�����ۼӳ��ȷֱ�Ϊ8��32�� */
        unsigned long  reserved          : 28; /* bit[4-31]: ���� */
    } reg;
} CBBP_UNIT0_CORR_LENGTH_UNION;
#define CBBP_UNIT0_CORR_LENGTH_unit0_corr_length_START  (0)
#define CBBP_UNIT0_CORR_LENGTH_unit0_corr_length_END    (3)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_NCORR_LENGTH_UNION
 �ṹ˵��  : UNIT0_NCORR_LENGTH �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_ncorr_length_reg;
    struct
    {
        unsigned long  unit0_ncorr_lenth : 3;  /* bit[0-2] : ����ɳ���
                                                             0��1
                                                             1��2
                                                             2��3
                                                             3��4
                                                             4��8
                                                             5��16
                                                             6��32
                                                             7��96 */
        unsigned long  reserved          : 29; /* bit[3-31]: ���� */
    } reg;
} CBBP_UNIT0_NCORR_LENGTH_UNION;
#define CBBP_UNIT0_NCORR_LENGTH_unit0_ncorr_lenth_START  (0)
#define CBBP_UNIT0_NCORR_LENGTH_unit0_ncorr_lenth_END    (2)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_ABS_TH_UNION
 �ṹ˵��  : UNIT0_ABS_TH �Ĵ����ṹ���塣��ַƫ����:0x0038����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_abs_th_reg;
    struct
    {
        unsigned long  unit0_abs_th : 16; /* bit[0-15] : ������������ */
        unsigned long  reserved     : 16; /* bit[16-31]: ���� */
    } reg;
} CBBP_UNIT0_ABS_TH_UNION;
#define CBBP_UNIT0_ABS_TH_unit0_abs_th_START  (0)
#define CBBP_UNIT0_ABS_TH_unit0_abs_th_END    (15)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_EN_UNION
 �ṹ˵��  : UNIT0_EN �Ĵ����ṹ���塣��ַƫ����:0x003C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_en_reg;
    struct
    {
        unsigned long  unit0_en : 1;  /* bit[0]   : ������Ԫʹ���ź� */
        unsigned long  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_UNIT0_EN_UNION;
#define CBBP_UNIT0_EN_unit0_en_START  (0)
#define CBBP_UNIT0_EN_unit0_en_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_NOISE_ENERGY_UNION
 �ṹ˵��  : UNIT0_NOISE_ENERGY �Ĵ����ṹ���塣��ַƫ����:0x0040����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_noise_energy_reg;
    struct
    {
        unsigned long  unit0_noise_energy : 16; /* bit[0-15] : ��Ԫ0����С�������ϱ����������� */
        unsigned long  reserved           : 16; /* bit[16-31]: ���� */
    } reg;
} CBBP_UNIT0_NOISE_ENERGY_UNION;
#define CBBP_UNIT0_NOISE_ENERGY_unit0_noise_energy_START  (0)
#define CBBP_UNIT0_NOISE_ENERGY_unit0_noise_energy_END    (15)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_FRAME_SHIFT_UNION
 �ṹ˵��  : UNIT0_FRAME_SHIFT �Ĵ����ṹ���塣��ַƫ����:0x0044����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_frame_shift_reg;
    struct
    {
        unsigned long  unit0_frame_shft : 1;  /* bit[0]   : ��Ԫ0�����ϱ�������ƫ��1/2chipָʾ���ྶ������С������ʱ��Ч��
                                                            0����ʾ�ϱ���������������������ȫһ��
                                                            1����ʾ�ϱ����������������������ƫ����1/2chip������ԭ�����õ�λ�ã�����ƫ����1/2chip */
        unsigned long  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_UNIT0_FRAME_SHIFT_UNION;
#define CBBP_UNIT0_FRAME_SHIFT_unit0_frame_shft_START  (0)
#define CBBP_UNIT0_FRAME_SHIFT_unit0_frame_shft_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_PN0_FRAME_POS_UNION
 �ṹ˵��  : UNIT0_PN0_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0048����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn0_frame_pos_reg;
    struct
    {
        unsigned long  unit0_pn0_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                ����Ƕྶ������С����������ʼС������ʱ����ʾ����Ԫ����������β��Ӧ��f-pich֡ͷλ�á�
                                                                �����Pn�б�С����������ʾ��һ��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT0_PN0_FRAME_POS_UNION;
#define CBBP_UNIT0_PN0_FRAME_POS_unit0_pn0_frame_pos_START  (0)
#define CBBP_UNIT0_PN0_FRAME_POS_unit0_pn0_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_PN1_FRAME_POS_UNION
 �ṹ˵��  : UNIT0_PN1_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x004C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn1_frame_pos_reg;
    struct
    {
        unsigned long  unit0_pn1_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��2��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT0_PN1_FRAME_POS_UNION;
#define CBBP_UNIT0_PN1_FRAME_POS_unit0_pn1_frame_pos_START  (0)
#define CBBP_UNIT0_PN1_FRAME_POS_unit0_pn1_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_PN2_FRAME_POS_UNION
 �ṹ˵��  : UNIT0_PN2_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0050����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn2_frame_pos_reg;
    struct
    {
        unsigned long  unit0_pn2_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��3��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT0_PN2_FRAME_POS_UNION;
#define CBBP_UNIT0_PN2_FRAME_POS_unit0_pn2_frame_pos_START  (0)
#define CBBP_UNIT0_PN2_FRAME_POS_unit0_pn2_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_PN3_FRAME_POS_UNION
 �ṹ˵��  : UNIT0_PN3_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0054����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn3_frame_pos_reg;
    struct
    {
        unsigned long  unit0_pn3_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[19:5]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��4��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT0_PN3_FRAME_POS_UNION;
#define CBBP_UNIT0_PN3_FRAME_POS_unit0_pn3_frame_pos_START  (0)
#define CBBP_UNIT0_PN3_FRAME_POS_unit0_pn3_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_PN4_FRAME_POS_UNION
 �ṹ˵��  : UNIT0_PN4_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0058����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn4_frame_pos_reg;
    struct
    {
        unsigned long  unit0_pn4_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��5��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT0_PN4_FRAME_POS_UNION;
#define CBBP_UNIT0_PN4_FRAME_POS_unit0_pn4_frame_pos_START  (0)
#define CBBP_UNIT0_PN4_FRAME_POS_unit0_pn4_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_PN5_FRAME_POS_UNION
 �ṹ˵��  : UNIT0_PN5_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x005C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn5_frame_pos_reg;
    struct
    {
        unsigned long  unit0_pn5_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��6��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT0_PN5_FRAME_POS_UNION;
#define CBBP_UNIT0_PN5_FRAME_POS_unit0_pn5_frame_pos_START  (0)
#define CBBP_UNIT0_PN5_FRAME_POS_unit0_pn5_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_PN6_FRAME_POS_UNION
 �ṹ˵��  : UNIT0_PN6_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0060����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn6_frame_pos_reg;
    struct
    {
        unsigned long  unit0_pn6_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��7��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT0_PN6_FRAME_POS_UNION;
#define CBBP_UNIT0_PN6_FRAME_POS_unit0_pn6_frame_pos_START  (0)
#define CBBP_UNIT0_PN6_FRAME_POS_unit0_pn6_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_PN7_FRAME_POS_UNION
 �ṹ˵��  : UNIT0_PN7_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0064����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn7_frame_pos_reg;
    struct
    {
        unsigned long  unit0_pn7_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��8��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT0_PN7_FRAME_POS_UNION;
#define CBBP_UNIT0_PN7_FRAME_POS_unit0_pn7_frame_pos_START  (0)
#define CBBP_UNIT0_PN7_FRAME_POS_unit0_pn7_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_PN8_FRAME_POS_UNION
 �ṹ˵��  : UNIT0_PN8_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0068����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn8_frame_pos_reg;
    struct
    {
        unsigned long  unit0_pn8_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��9��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT0_PN8_FRAME_POS_UNION;
#define CBBP_UNIT0_PN8_FRAME_POS_unit0_pn8_frame_pos_START  (0)
#define CBBP_UNIT0_PN8_FRAME_POS_unit0_pn8_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_PN9_FRAME_POS_UNION
 �ṹ˵��  : UNIT0_PN9_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x006C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn9_frame_pos_reg;
    struct
    {
        unsigned long  unit0_pn9_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��10��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT0_PN9_FRAME_POS_UNION;
#define CBBP_UNIT0_PN9_FRAME_POS_unit0_pn9_frame_pos_START  (0)
#define CBBP_UNIT0_PN9_FRAME_POS_unit0_pn9_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_PN10_FRAME_POS_UNION
 �ṹ˵��  : UNIT0_PN10_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0070����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn10_frame_pos_reg;
    struct
    {
        unsigned long  unit0_pn10_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                 �����Pn�б�С����������ʾ��11��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved             : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT0_PN10_FRAME_POS_UNION;
#define CBBP_UNIT0_PN10_FRAME_POS_unit0_pn10_frame_pos_START  (0)
#define CBBP_UNIT0_PN10_FRAME_POS_unit0_pn10_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_PN11_FRAME_POS_UNION
 �ṹ˵��  : UNIT0_PN11_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0074����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn11_frame_pos_reg;
    struct
    {
        unsigned long  unit0_pn11_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                 �����Pn�б�С����������ʾ��12��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved             : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT0_PN11_FRAME_POS_UNION;
#define CBBP_UNIT0_PN11_FRAME_POS_unit0_pn11_frame_pos_START  (0)
#define CBBP_UNIT0_PN11_FRAME_POS_unit0_pn11_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_PN12_FRAME_POS_UNION
 �ṹ˵��  : UNIT0_PN12_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0078����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn12_frame_pos_reg;
    struct
    {
        unsigned long  unit0_pn12_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                 �����Pn�б�С����������ʾ��13��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved             : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT0_PN12_FRAME_POS_UNION;
#define CBBP_UNIT0_PN12_FRAME_POS_unit0_pn12_frame_pos_START  (0)
#define CBBP_UNIT0_PN12_FRAME_POS_unit0_pn12_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_PN13_FRAME_POS_UNION
 �ṹ˵��  : UNIT0_PN13_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x007C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn13_frame_pos_reg;
    struct
    {
        unsigned long  unit0_pn13_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                 �����Pn�б�С����������ʾ��14��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved             : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT0_PN13_FRAME_POS_UNION;
#define CBBP_UNIT0_PN13_FRAME_POS_unit0_pn13_frame_pos_START  (0)
#define CBBP_UNIT0_PN13_FRAME_POS_unit0_pn13_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_PN14_FRAME_POS_UNION
 �ṹ˵��  : UNIT0_PN14_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0080����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn14_frame_pos_reg;
    struct
    {
        unsigned long  unit0_pn14_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                 �����Pn�б�С����������ʾ��15��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved             : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT0_PN14_FRAME_POS_UNION;
#define CBBP_UNIT0_PN14_FRAME_POS_unit0_pn14_frame_pos_START  (0)
#define CBBP_UNIT0_PN14_FRAME_POS_unit0_pn14_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_PN15_FRAME_POS_UNION
 �ṹ˵��  : UNIT0_PN15_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0084����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn15_frame_pos_reg;
    struct
    {
        unsigned long  unit0_pn15_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                 �����Pn�б�С����������ʾ��16��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved             : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT0_PN15_FRAME_POS_UNION;
#define CBBP_UNIT0_PN15_FRAME_POS_unit0_pn15_frame_pos_START  (0)
#define CBBP_UNIT0_PN15_FRAME_POS_unit0_pn15_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_CS_1X_MODE_UNION
 �ṹ˵��  : UNIT0_CS_1X_MODE �Ĵ����ṹ���塣��ַƫ����:0x0088����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_cs_1x_mode_reg;
    struct
    {
        unsigned long  unit0_cs_1x_mode : 1;  /* bit[0]   : ����ģʽѡ��
                                                            0��ʾ1x����
                                                            1��ʾevdo���� */
        unsigned long  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_UNIT0_CS_1X_MODE_UNION;
#define CBBP_UNIT0_CS_1X_MODE_unit0_cs_1x_mode_START  (0)
#define CBBP_UNIT0_CS_1X_MODE_unit0_cs_1x_mode_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_SRCH_CK_BYPASS_UNION
 �ṹ˵��  : UNIT0_SRCH_CK_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x008C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_srch_ck_bypass_reg;
    struct
    {
        unsigned long  unit0_ctrl_pass   : 1;  /* bit[0]   : ������Ԫ���Ʋ���ʱ���ſ�bypass
                                                             0��ʾʱ���ſ���Ч
                                                             1��ʾʱ�ӳ��� */
        unsigned long  unit0_sort_bypass : 1;  /* bit[1]   : ������Ԫ�Ŷ�ģ��ʱ���ſ�
                                                             0��ʾʱ���ſ���Ч
                                                             1��ʾʱ�ӳ��� */
        unsigned long  unit0_rpt_bypass  : 1;  /* bit[2]   : ������Ԫ�ϱ�ģ��ʱ���ſ�
                                                             0��ʾʱ���ſ���Ч
                                                             1��ʾʱ�ӳ��� */
        unsigned long  reserved          : 29; /* bit[3-31]: ���� */
    } reg;
} CBBP_UNIT0_SRCH_CK_BYPASS_UNION;
#define CBBP_UNIT0_SRCH_CK_BYPASS_unit0_ctrl_pass_START    (0)
#define CBBP_UNIT0_SRCH_CK_BYPASS_unit0_ctrl_pass_END      (0)
#define CBBP_UNIT0_SRCH_CK_BYPASS_unit0_sort_bypass_START  (1)
#define CBBP_UNIT0_SRCH_CK_BYPASS_unit0_sort_bypass_END    (1)
#define CBBP_UNIT0_SRCH_CK_BYPASS_unit0_rpt_bypass_START   (2)
#define CBBP_UNIT0_SRCH_CK_BYPASS_unit0_rpt_bypass_END     (2)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_NOISE_ALPHER_COEF_UNION
 �ṹ˵��  : UNIT0_NOISE_ALPHER_COEF �Ĵ����ṹ���塣��ַƫ����:0x0090����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_noise_alpher_coef_reg;
    struct
    {
        unsigned long  unit0_noise_alpher_coef : 3;  /* bit[0-2] : ���������˲�ϵ����
                                                                   0��1/2
                                                                   1:1/16
                                                                   2:1/32
                                                                   3:1/64
                                                                   4:1/128
                                                                   5:1/256 */
        unsigned long  reserved                : 29; /* bit[3-31]: ���� */
    } reg;
} CBBP_UNIT0_NOISE_ALPHER_COEF_UNION;
#define CBBP_UNIT0_NOISE_ALPHER_COEF_unit0_noise_alpher_coef_START  (0)
#define CBBP_UNIT0_NOISE_ALPHER_COEF_unit0_noise_alpher_coef_END    (2)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_DATA_STORE_OFF_UNION
 �ṹ˵��  : UNIT0_DATA_STORE_OFF �Ĵ����ṹ���塣��ַƫ����:0x0094����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_data_store_off_reg;
    struct
    {
        unsigned long  unit0_data_store_off : 10; /* bit[0-9]  : �ӻ���������ȡ��ƫ�ƣ�chip��λ��
                                                                 ʹ�ó�������ԶС����������������4096chip���ݣ�����ʱ��ÿ1024chip��ȡ�������ݣ���ȡλ���ɴ˼Ĵ���ȷ�� */
        unsigned long  reserved             : 22; /* bit[10-31]: ���� */
    } reg;
} CBBP_UNIT0_DATA_STORE_OFF_UNION;
#define CBBP_UNIT0_DATA_STORE_OFF_unit0_data_store_off_START  (0)
#define CBBP_UNIT0_DATA_STORE_OFF_unit0_data_store_off_END    (9)


/***======================================================================***
                     (6/20) register_define_c_cs_mps_unit1
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_CLK_MODE_UNION
 �ṹ˵��  : UNIT1_CLK_MODE �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_clk_mode_reg;
    struct
    {
        unsigned long  unit1_clk_mode : 1;  /* bit[0]   : ������Ԫʱ��Ƶ��ѡ��
                                                          0����ʾ������Ԫ128��ʱ�ӣ�
                                                          1����ʾ������Ԫ64��ʱ��
                                                          Ĭ�ϲ���Ҫ������� */
        unsigned long  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_UNIT1_CLK_MODE_UNION;
#define CBBP_UNIT1_CLK_MODE_unit1_clk_mode_START  (0)
#define CBBP_UNIT1_CLK_MODE_unit1_clk_mode_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_CORR_RPT_PERIOD_UNION
 �ṹ˵��  : UNIT1_CORR_RPT_PERIOD �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_corr_rpt_period_reg;
    struct
    {
        unsigned long  unit1_corr_rpt_period : 4;  /* bit[0-3] : ʹ���������ݶྶ��������С��������ʱ�����ٸ�����ۼӽ���ϱ�һ�Ρ�
                                                                 �˽ӿ���Ҫ�ǽ��afcʧ��ʱ��1x������ۼӳ���Ϊ64chip������ɽ���ϱ�����̫�ܼ������⡣
                                                                 ����1x��afcʧ��ʱ����������ȡ12����ÿ64x12=768chip�ڣ��ϱ���һ��64chip������ɽ����
                                                                 ����1x��afc����ʱ����������ȡ1����ÿ64x12=768chip�ϱ�һ������ۼӽ����
                                                                 ����evdoʱ����������ȡ1����ÿ1024chip��afcʧ������4096chip��afc�������ϱ�һ����ɽ���� */
        unsigned long  reserved              : 28; /* bit[4-31]: ���� */
    } reg;
} CBBP_UNIT1_CORR_RPT_PERIOD_UNION;
#define CBBP_UNIT1_CORR_RPT_PERIOD_unit1_corr_rpt_period_START  (0)
#define CBBP_UNIT1_CORR_RPT_PERIOD_unit1_corr_rpt_period_END    (3)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_CORR_WAIT_CHIP_UNION
 �ṹ˵��  : UNIT1_CORR_WAIT_CHIP �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_corr_wait_chip_reg;
    struct
    {
        unsigned long  unit1_corr_wait_chip : 11; /* bit[0-10] : ʹ����ɢ��������С������ʱ��ÿ����1024chip�ڵ�һ�����ݣ��ȴ��೤ʱ�䣬������һ��1024chip������λchip��
                                                                 �˽ӿ���Ҫ���ʹ����ɢ�����������С������ʱ���ж��ϱ��ܼ��������
                                                                 ���ڶྶ����ģʽ��BBP���������ۼӣ�������ʱ���������� */
        unsigned long  reserved             : 21; /* bit[11-31]: ���� */
    } reg;
} CBBP_UNIT1_CORR_WAIT_CHIP_UNION;
#define CBBP_UNIT1_CORR_WAIT_CHIP_unit1_corr_wait_chip_START  (0)
#define CBBP_UNIT1_CORR_WAIT_CHIP_unit1_corr_wait_chip_END    (10)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_ANT_SEL_UNION
 �ṹ˵��  : UNIT1_ANT_SEL �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_ant_sel_reg;
    struct
    {
        unsigned long  unit1_ant_sel : 1;  /* bit[0]   : ������������ѡ��
                                                         0����ʾ�����������1�����ݣ�
                                                         1����ʾ�����������2�����ݣ� */
        unsigned long  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_UNIT1_ANT_SEL_UNION;
#define CBBP_UNIT1_ANT_SEL_unit1_ant_sel_START  (0)
#define CBBP_UNIT1_ANT_SEL_unit1_ant_sel_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_MODE_UNION
 �ṹ˵��  : UNIT1_MODE �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_mode_reg;
    struct
    {
        unsigned long  unit1_mode : 2;  /* bit[0-1] : ģʽѡ��
                                                      0����ʾ��ʼС������
                                                      1����ʾpn�б�С������
                                                      2����ʾ�ྶ������С�����������������ۼӣ�
                                                      3����ʾС���������������ۼ��������ۼӣ� */
        unsigned long  reserved   : 30; /* bit[2-31]: ���� */
    } reg;
} CBBP_UNIT1_MODE_UNION;
#define CBBP_UNIT1_MODE_unit1_mode_START  (0)
#define CBBP_UNIT1_MODE_unit1_mode_END    (1)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_WIN_UNION
 �ṹ˵��  : UNIT1_WIN �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_win_reg;
    struct
    {
        unsigned long  unit1_win : 10; /* bit[0-9]  : ����������λΪ64chip�����÷�ΧΪ1~512��
                                                      
                                                      ��ʼС������ʱ����֧��������������������Ϊ128����������Ϊ64*128=8192chip��
                                                      PN�б�С������ʱ����֧������������������������̶�Ϊ64chip��
                                                      �ྶ��������֧��ʵʱ������������������̶�50chip��
                                                      С������ģʽ��С����������֧���������ݲ���������̶�Ϊ64chip */
        unsigned long  reserved  : 22; /* bit[10-31]: ���� */
    } reg;
} CBBP_UNIT1_WIN_UNION;
#define CBBP_UNIT1_WIN_unit1_win_START  (0)
#define CBBP_UNIT1_WIN_unit1_win_END    (9)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_DATA_SEL_UNION
 �ṹ˵��  : UNIT1_DATA_SEL �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_data_sel_reg;
    struct
    {
        unsigned long  unit1_data_sel : 1;  /* bit[0]   : ��������ѡ��
                                                          0����ʾʹ��ʵʱ���ݣ�
                                                          1����ʾʹ�û�������� */
        unsigned long  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_UNIT1_DATA_SEL_UNION;
#define CBBP_UNIT1_DATA_SEL_unit1_data_sel_START  (0)
#define CBBP_UNIT1_DATA_SEL_unit1_data_sel_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_DATA_STORE_MODE_UNION
 �ṹ˵��  : UNIT1_DATA_STORE_MODE �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_data_store_mode_reg;
    struct
    {
        unsigned long  unit1_data_store_mode : 3;  /* bit[0-2] : �������ݵ�ģʽ���˲������������һ�λ�������ʱ�Ĳ���Data_store_mode��ͬ
                                                                 0��ʾ�����洢��
                                                                 1��ʾÿ1024chip�洢64chip��
                                                                 2��ʾÿ1024chip�洢96chip��
                                                                 3��ʾÿ1024chip�洢128chip��
                                                                 4��ʾÿ1024chip�洢256chip
                                                                 5��ʾÿ1024chip�洢512chip�� */
        unsigned long  reserved              : 29; /* bit[3-31]: ���� */
    } reg;
} CBBP_UNIT1_DATA_STORE_MODE_UNION;
#define CBBP_UNIT1_DATA_STORE_MODE_unit1_data_store_mode_START  (0)
#define CBBP_UNIT1_DATA_STORE_MODE_unit1_data_store_mode_END    (2)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_DATA_POS_UNION
 �ṹ˵��  : UNIT1_DATA_POS �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_data_pos_reg;
    struct
    {
        unsigned long  unit1_data_pos : 16; /* bit[0-15] : ʹ��ʵʱ����ʱ���������ݵ���ʼλ�ã���base_cnt[21:6]�ϵ�λ�ã�1/2chip���� */
        unsigned long  reserved       : 16; /* bit[16-31]: ���� */
    } reg;
} CBBP_UNIT1_DATA_POS_UNION;
#define CBBP_UNIT1_DATA_POS_unit1_data_pos_START  (0)
#define CBBP_UNIT1_DATA_POS_unit1_data_pos_END    (15)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_DATA_POS_SEL_UNION
 �ṹ˵��  : UNIT1_DATA_POS_SEL �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_data_pos_sel_reg;
    struct
    {
        unsigned long  unit1_data_pos_sel : 1;  /* bit[0]   : ʹ��ʵʱ����ʱ��Ч��
                                                              0����ʾ���Ծͽ���ʼ������
                                                              1������ȴ�Unit0_data_posʱ�����ܿ�ʼ������ */
        unsigned long  reserved           : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_UNIT1_DATA_POS_SEL_UNION;
#define CBBP_UNIT1_DATA_POS_SEL_unit1_data_pos_sel_START  (0)
#define CBBP_UNIT1_DATA_POS_SEL_unit1_data_pos_sel_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_DATA_MODE_UNION
 �ṹ˵��  : UNIT1_DATA_MODE �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_data_mode_reg;
    struct
    {
        unsigned long  unit1_data_mode : 3;  /* bit[0-2] : ��������ȡ����ʽ��
                                                           0��ʾ����ȡ����
                                                           1��ʾÿ1024chipȡ��64chip��
                                                           2��ʾÿ1024chipȡ��96chip��
                                                           3��ʾÿ1024chipȡ��128chip��
                                                           4��ʾÿ1024chipȡ��256chip
                                                           5��ʾÿ1024chip�洢512chip��
                                                           
                                                           ˵����
                                                           ����ʹ�û������ݣ�����Unit0_data_store_modeȷ���������ݵ�������ұ�������Unit0_data_mode<=Unit0_data_store_mode��
                                                           ����ʹ��ʵʱ���ݣ����ʵ������ʱ���Ѿ������Unit0_data_posʱ�̣����������ȡ��ʱ����ʵ������ʱ�̿�ʼȡ��������ÿ1024chip���ȡ�����������64/96chip/128chip/256chipȡ��λ�ÿ�ʼȡ���� */
        unsigned long  reserved        : 29; /* bit[3-31]: ���� */
    } reg;
} CBBP_UNIT1_DATA_MODE_UNION;
#define CBBP_UNIT1_DATA_MODE_unit1_data_mode_START  (0)
#define CBBP_UNIT1_DATA_MODE_unit1_data_mode_END    (2)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_PN_NUM_UNION
 �ṹ˵��  : UNIT1_PN_NUM �Ĵ����ṹ���塣��ַƫ����:0x002C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn_num_reg;
    struct
    {
        unsigned long  unit1_pn_num : 5;  /* bit[0-4] : Pn�б�С������ʱ��pn offset������֧��1~16�� */
        unsigned long  reserved     : 27; /* bit[5-31]: ���� */
    } reg;
} CBBP_UNIT1_PN_NUM_UNION;
#define CBBP_UNIT1_PN_NUM_unit1_pn_num_START  (0)
#define CBBP_UNIT1_PN_NUM_unit1_pn_num_END    (4)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_CORR_LENGTH_UNION
 �ṹ˵��  : UNIT1_CORR_LENGTH �Ĵ����ṹ���塣��ַƫ����:0x0030����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_corr_length_reg;
    struct
    {
        unsigned long  unit1_corr_length : 4;  /* bit[0-3] : ��ɳ���
                                                             0��32
                                                             1��64
                                                             2��96
                                                             3��128
                                                             4��256
                                                             5��96*4=384
                                                             6��64*12=768
                                                             7��512
                                                             �㷨�Ƽ���
                                                             1xС����������ۼӳ��ȿ�����Ϊ64��128��256����Ӧ�ķ�����ۼӳ���Ϊ32��16��8��
                                                             evdoС��������ɳ���Ϊ64��������ۼӳ���Ϊ32/16/8��
                                                             1x�ྶ������ɳ���Ϊ64x12=768��afc��������64x1=64��afcʧ�������֣���Ӧ�ķ�����ۼӳ��ȷֱ�Ϊ8��96��
                                                             Evdo�ྶ������ɳ���96x4=384��afc��������96x1=96��afcʧ��������Ӧ�ķ�����ۼӳ��ȷֱ�Ϊ8��32�� */
        unsigned long  reserved          : 28; /* bit[4-31]: ���� */
    } reg;
} CBBP_UNIT1_CORR_LENGTH_UNION;
#define CBBP_UNIT1_CORR_LENGTH_unit1_corr_length_START  (0)
#define CBBP_UNIT1_CORR_LENGTH_unit1_corr_length_END    (3)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_NCORR_LENGTH_UNION
 �ṹ˵��  : UNIT1_NCORR_LENGTH �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_ncorr_length_reg;
    struct
    {
        unsigned long  unit1_ncorr_lenth : 3;  /* bit[0-2] : ����ɳ���
                                                             0��1
                                                             1��2
                                                             2��3
                                                             3��4
                                                             4��8
                                                             5��16
                                                             6��32
                                                             7��96 */
        unsigned long  reserved          : 29; /* bit[3-31]: ���� */
    } reg;
} CBBP_UNIT1_NCORR_LENGTH_UNION;
#define CBBP_UNIT1_NCORR_LENGTH_unit1_ncorr_lenth_START  (0)
#define CBBP_UNIT1_NCORR_LENGTH_unit1_ncorr_lenth_END    (2)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_ABS_TH_UNION
 �ṹ˵��  : UNIT1_ABS_TH �Ĵ����ṹ���塣��ַƫ����:0x0038����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_abs_th_reg;
    struct
    {
        unsigned long  unit1_abs_th : 16; /* bit[0-15] : ������������ */
        unsigned long  reserved     : 16; /* bit[16-31]: ���� */
    } reg;
} CBBP_UNIT1_ABS_TH_UNION;
#define CBBP_UNIT1_ABS_TH_unit1_abs_th_START  (0)
#define CBBP_UNIT1_ABS_TH_unit1_abs_th_END    (15)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_EN_UNION
 �ṹ˵��  : UNIT1_EN �Ĵ����ṹ���塣��ַƫ����:0x003C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_en_reg;
    struct
    {
        unsigned long  unit1_en : 1;  /* bit[0]   : ������Ԫʹ���ź� */
        unsigned long  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_UNIT1_EN_UNION;
#define CBBP_UNIT1_EN_unit1_en_START  (0)
#define CBBP_UNIT1_EN_unit1_en_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_NOISE_ENERGY_UNION
 �ṹ˵��  : UNIT1_NOISE_ENERGY �Ĵ����ṹ���塣��ַƫ����:0x0040����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_noise_energy_reg;
    struct
    {
        unsigned long  unit1_noise_energy : 16; /* bit[0-15] : ��Ԫ0����С�������ϱ����������� */
        unsigned long  reserved           : 16; /* bit[16-31]: ���� */
    } reg;
} CBBP_UNIT1_NOISE_ENERGY_UNION;
#define CBBP_UNIT1_NOISE_ENERGY_unit1_noise_energy_START  (0)
#define CBBP_UNIT1_NOISE_ENERGY_unit1_noise_energy_END    (15)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_FRAME_SHIFT_UNION
 �ṹ˵��  : UNIT1_FRAME_SHIFT �Ĵ����ṹ���塣��ַƫ����:0x0044����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_frame_shift_reg;
    struct
    {
        unsigned long  unit1_frame_shft : 1;  /* bit[0]   : ��Ԫ0�����ϱ�������ƫ��1/2chipָʾ���ྶ������С������ʱ��Ч��
                                                            0����ʾ�ϱ���������������������ȫһ��
                                                            1����ʾ�ϱ����������������������ƫ����1/2chip������ԭ�����õ�λ�ã�����ƫ����1/2chip */
        unsigned long  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_UNIT1_FRAME_SHIFT_UNION;
#define CBBP_UNIT1_FRAME_SHIFT_unit1_frame_shft_START  (0)
#define CBBP_UNIT1_FRAME_SHIFT_unit1_frame_shft_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_PN0_FRAME_POS_UNION
 �ṹ˵��  : UNIT1_PN0_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0048����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn0_frame_pos_reg;
    struct
    {
        unsigned long  unit1_pn0_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                ����Ƕྶ������С����������ʼС������ʱ����ʾ����Ԫ����������β��Ӧ��f-pich֡ͷλ�á�
                                                                �����Pn�б�С����������ʾ��һ��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT1_PN0_FRAME_POS_UNION;
#define CBBP_UNIT1_PN0_FRAME_POS_unit1_pn0_frame_pos_START  (0)
#define CBBP_UNIT1_PN0_FRAME_POS_unit1_pn0_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_PN1_FRAME_POS_UNION
 �ṹ˵��  : UNIT1_PN1_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x004C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn1_frame_pos_reg;
    struct
    {
        unsigned long  unit1_pn1_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��2��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT1_PN1_FRAME_POS_UNION;
#define CBBP_UNIT1_PN1_FRAME_POS_unit1_pn1_frame_pos_START  (0)
#define CBBP_UNIT1_PN1_FRAME_POS_unit1_pn1_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_PN2_FRAME_POS_UNION
 �ṹ˵��  : UNIT1_PN2_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0050����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn2_frame_pos_reg;
    struct
    {
        unsigned long  unit1_pn2_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��3��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT1_PN2_FRAME_POS_UNION;
#define CBBP_UNIT1_PN2_FRAME_POS_unit1_pn2_frame_pos_START  (0)
#define CBBP_UNIT1_PN2_FRAME_POS_unit1_pn2_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_PN3_FRAME_POS_UNION
 �ṹ˵��  : UNIT1_PN3_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0054����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn3_frame_pos_reg;
    struct
    {
        unsigned long  unit1_pn3_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[19:5]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��4��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT1_PN3_FRAME_POS_UNION;
#define CBBP_UNIT1_PN3_FRAME_POS_unit1_pn3_frame_pos_START  (0)
#define CBBP_UNIT1_PN3_FRAME_POS_unit1_pn3_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_PN4_FRAME_POS_UNION
 �ṹ˵��  : UNIT1_PN4_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0058����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn4_frame_pos_reg;
    struct
    {
        unsigned long  unit1_pn4_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��5��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT1_PN4_FRAME_POS_UNION;
#define CBBP_UNIT1_PN4_FRAME_POS_unit1_pn4_frame_pos_START  (0)
#define CBBP_UNIT1_PN4_FRAME_POS_unit1_pn4_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_PN5_FRAME_POS_UNION
 �ṹ˵��  : UNIT1_PN5_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x005C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn5_frame_pos_reg;
    struct
    {
        unsigned long  unit1_pn5_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��6��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT1_PN5_FRAME_POS_UNION;
#define CBBP_UNIT1_PN5_FRAME_POS_unit1_pn5_frame_pos_START  (0)
#define CBBP_UNIT1_PN5_FRAME_POS_unit1_pn5_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_PN6_FRAME_POS_UNION
 �ṹ˵��  : UNIT1_PN6_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0060����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn6_frame_pos_reg;
    struct
    {
        unsigned long  unit1_pn6_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��7��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT1_PN6_FRAME_POS_UNION;
#define CBBP_UNIT1_PN6_FRAME_POS_unit1_pn6_frame_pos_START  (0)
#define CBBP_UNIT1_PN6_FRAME_POS_unit1_pn6_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_PN7_FRAME_POS_UNION
 �ṹ˵��  : UNIT1_PN7_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0064����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn7_frame_pos_reg;
    struct
    {
        unsigned long  unit1_pn7_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��8��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT1_PN7_FRAME_POS_UNION;
#define CBBP_UNIT1_PN7_FRAME_POS_unit1_pn7_frame_pos_START  (0)
#define CBBP_UNIT1_PN7_FRAME_POS_unit1_pn7_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_PN8_FRAME_POS_UNION
 �ṹ˵��  : UNIT1_PN8_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0068����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn8_frame_pos_reg;
    struct
    {
        unsigned long  unit1_pn8_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��9��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT1_PN8_FRAME_POS_UNION;
#define CBBP_UNIT1_PN8_FRAME_POS_unit1_pn8_frame_pos_START  (0)
#define CBBP_UNIT1_PN8_FRAME_POS_unit1_pn8_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_PN9_FRAME_POS_UNION
 �ṹ˵��  : UNIT1_PN9_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x006C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn9_frame_pos_reg;
    struct
    {
        unsigned long  unit1_pn9_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��10��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT1_PN9_FRAME_POS_UNION;
#define CBBP_UNIT1_PN9_FRAME_POS_unit1_pn9_frame_pos_START  (0)
#define CBBP_UNIT1_PN9_FRAME_POS_unit1_pn9_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_PN10_FRAME_POS_UNION
 �ṹ˵��  : UNIT1_PN10_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0070����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn10_frame_pos_reg;
    struct
    {
        unsigned long  unit1_pn10_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                 �����Pn�б�С����������ʾ��11��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved             : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT1_PN10_FRAME_POS_UNION;
#define CBBP_UNIT1_PN10_FRAME_POS_unit1_pn10_frame_pos_START  (0)
#define CBBP_UNIT1_PN10_FRAME_POS_unit1_pn10_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_PN11_FRAME_POS_UNION
 �ṹ˵��  : UNIT1_PN11_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0074����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn11_frame_pos_reg;
    struct
    {
        unsigned long  unit1_pn11_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                 �����Pn�б�С����������ʾ��12��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved             : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT1_PN11_FRAME_POS_UNION;
#define CBBP_UNIT1_PN11_FRAME_POS_unit1_pn11_frame_pos_START  (0)
#define CBBP_UNIT1_PN11_FRAME_POS_unit1_pn11_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_PN12_FRAME_POS_UNION
 �ṹ˵��  : UNIT1_PN12_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0078����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn12_frame_pos_reg;
    struct
    {
        unsigned long  unit1_pn12_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                 �����Pn�б�С����������ʾ��13��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved             : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT1_PN12_FRAME_POS_UNION;
#define CBBP_UNIT1_PN12_FRAME_POS_unit1_pn12_frame_pos_START  (0)
#define CBBP_UNIT1_PN12_FRAME_POS_unit1_pn12_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_PN13_FRAME_POS_UNION
 �ṹ˵��  : UNIT1_PN13_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x007C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn13_frame_pos_reg;
    struct
    {
        unsigned long  unit1_pn13_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                 �����Pn�б�С����������ʾ��14��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved             : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT1_PN13_FRAME_POS_UNION;
#define CBBP_UNIT1_PN13_FRAME_POS_unit1_pn13_frame_pos_START  (0)
#define CBBP_UNIT1_PN13_FRAME_POS_unit1_pn13_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_PN14_FRAME_POS_UNION
 �ṹ˵��  : UNIT1_PN14_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0080����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn14_frame_pos_reg;
    struct
    {
        unsigned long  unit1_pn14_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                 �����Pn�б�С����������ʾ��15��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved             : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT1_PN14_FRAME_POS_UNION;
#define CBBP_UNIT1_PN14_FRAME_POS_unit1_pn14_frame_pos_START  (0)
#define CBBP_UNIT1_PN14_FRAME_POS_unit1_pn14_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_PN15_FRAME_POS_UNION
 �ṹ˵��  : UNIT1_PN15_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0084����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn15_frame_pos_reg;
    struct
    {
        unsigned long  unit1_pn15_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                 �����Pn�б�С����������ʾ��16��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved             : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT1_PN15_FRAME_POS_UNION;
#define CBBP_UNIT1_PN15_FRAME_POS_unit1_pn15_frame_pos_START  (0)
#define CBBP_UNIT1_PN15_FRAME_POS_unit1_pn15_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_CS_1X_MODE_UNION
 �ṹ˵��  : UNIT1_CS_1X_MODE �Ĵ����ṹ���塣��ַƫ����:0x0088����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_cs_1x_mode_reg;
    struct
    {
        unsigned long  unit1_cs_1x_mode : 1;  /* bit[0]   : ����ģʽѡ��
                                                            0��ʾ1x����
                                                            1��ʾevdo���� */
        unsigned long  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_UNIT1_CS_1X_MODE_UNION;
#define CBBP_UNIT1_CS_1X_MODE_unit1_cs_1x_mode_START  (0)
#define CBBP_UNIT1_CS_1X_MODE_unit1_cs_1x_mode_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_SRCH_CK_BYPASS_UNION
 �ṹ˵��  : UNIT1_SRCH_CK_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x008C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_srch_ck_bypass_reg;
    struct
    {
        unsigned long  unit1_ctrl_pass   : 1;  /* bit[0]   : ������Ԫ���Ʋ���ʱ���ſ�bypass
                                                             0��ʾʱ���ſ���Ч
                                                             1��ʾʱ�ӳ��� */
        unsigned long  unit1_sort_bypass : 1;  /* bit[1]   : ������Ԫ�Ŷ�ģ��ʱ���ſ�
                                                             0��ʾʱ���ſ���Ч
                                                             1��ʾʱ�ӳ��� */
        unsigned long  unit1_rpt_bypass  : 1;  /* bit[2]   : ������Ԫ�ϱ�ģ��ʱ���ſ�
                                                             0��ʾʱ���ſ���Ч
                                                             1��ʾʱ�ӳ��� */
        unsigned long  reserved          : 29; /* bit[3-31]: ���� */
    } reg;
} CBBP_UNIT1_SRCH_CK_BYPASS_UNION;
#define CBBP_UNIT1_SRCH_CK_BYPASS_unit1_ctrl_pass_START    (0)
#define CBBP_UNIT1_SRCH_CK_BYPASS_unit1_ctrl_pass_END      (0)
#define CBBP_UNIT1_SRCH_CK_BYPASS_unit1_sort_bypass_START  (1)
#define CBBP_UNIT1_SRCH_CK_BYPASS_unit1_sort_bypass_END    (1)
#define CBBP_UNIT1_SRCH_CK_BYPASS_unit1_rpt_bypass_START   (2)
#define CBBP_UNIT1_SRCH_CK_BYPASS_unit1_rpt_bypass_END     (2)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_NOISE_ALPHER_COEF_UNION
 �ṹ˵��  : UNIT1_NOISE_ALPHER_COEF �Ĵ����ṹ���塣��ַƫ����:0x0090����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_noise_alpher_coef_reg;
    struct
    {
        unsigned long  unit1_noise_alpher_coef : 3;  /* bit[0-2] : ���������˲�ϵ����
                                                                   0��1/2
                                                                   1:1/16
                                                                   2:1/32
                                                                   3:1/64
                                                                   4:1/128
                                                                   5:1/256 */
        unsigned long  reserved                : 29; /* bit[3-31]: ���� */
    } reg;
} CBBP_UNIT1_NOISE_ALPHER_COEF_UNION;
#define CBBP_UNIT1_NOISE_ALPHER_COEF_unit1_noise_alpher_coef_START  (0)
#define CBBP_UNIT1_NOISE_ALPHER_COEF_unit1_noise_alpher_coef_END    (2)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_DATA_STORE_OFF_UNION
 �ṹ˵��  : UNIT1_DATA_STORE_OFF �Ĵ����ṹ���塣��ַƫ����:0x0094����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_data_store_off_reg;
    struct
    {
        unsigned long  unit1_data_store_off : 10; /* bit[0-9]  : �ӻ���������ȡ��ƫ�ƣ�chip��λ��
                                                                 ʹ�ó�������ԶС����������������4096chip���ݣ�����ʱ��ÿ1024chip��ȡ�������ݣ���ȡλ���ɴ˼Ĵ���ȷ�� */
        unsigned long  reserved             : 22; /* bit[10-31]: ���� */
    } reg;
} CBBP_UNIT1_DATA_STORE_OFF_UNION;
#define CBBP_UNIT1_DATA_STORE_OFF_unit1_data_store_off_START  (0)
#define CBBP_UNIT1_DATA_STORE_OFF_unit1_data_store_off_END    (9)


/***======================================================================***
                     (7/20) register_define_c_cs_mps_unit2
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_CLK_MODE_UNION
 �ṹ˵��  : UNIT2_CLK_MODE �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_clk_mode_reg;
    struct
    {
        unsigned long  unit2_clk_mode : 1;  /* bit[0]   : ������Ԫʱ��Ƶ��ѡ��
                                                          0����ʾ������Ԫ128��ʱ�ӣ�
                                                          1����ʾ������Ԫ64��ʱ��
                                                          Ĭ�ϲ���Ҫ������� */
        unsigned long  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_UNIT2_CLK_MODE_UNION;
#define CBBP_UNIT2_CLK_MODE_unit2_clk_mode_START  (0)
#define CBBP_UNIT2_CLK_MODE_unit2_clk_mode_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_CORR_RPT_PERIOD_UNION
 �ṹ˵��  : UNIT2_CORR_RPT_PERIOD �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_corr_rpt_period_reg;
    struct
    {
        unsigned long  unit2_corr_rpt_period : 4;  /* bit[0-3] : ʹ���������ݶྶ��������С��������ʱ�����ٸ�����ۼӽ���ϱ�һ�Ρ�
                                                                 �˽ӿ���Ҫ�ǽ��afcʧ��ʱ��1x������ۼӳ���Ϊ64chip������ɽ���ϱ�����̫�ܼ������⡣
                                                                 ����1x��afcʧ��ʱ����������ȡ12����ÿ64x12=768chip�ڣ��ϱ���һ��64chip������ɽ����
                                                                 ����1x��afc����ʱ����������ȡ1����ÿ64x12=768chip�ϱ�һ������ۼӽ����
                                                                 ����evdoʱ����������ȡ1����ÿ1024chip��afcʧ������4096chip��afc�������ϱ�һ����ɽ���� */
        unsigned long  reserved              : 28; /* bit[4-31]: ���� */
    } reg;
} CBBP_UNIT2_CORR_RPT_PERIOD_UNION;
#define CBBP_UNIT2_CORR_RPT_PERIOD_unit2_corr_rpt_period_START  (0)
#define CBBP_UNIT2_CORR_RPT_PERIOD_unit2_corr_rpt_period_END    (3)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_CORR_WAIT_CHIP_UNION
 �ṹ˵��  : UNIT2_CORR_WAIT_CHIP �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_corr_wait_chip_reg;
    struct
    {
        unsigned long  unit2_corr_wait_chip : 11; /* bit[0-10] : ʹ����ɢ��������С������ʱ��ÿ����1024chip�ڵ�һ�����ݣ��ȴ��೤ʱ�䣬������һ��1024chip������λchip��
                                                                 �˽ӿ���Ҫ���ʹ����ɢ�����������С������ʱ���ж��ϱ��ܼ��������
                                                                 ���ڶྶ����ģʽ��BBP���������ۼӣ�������ʱ���������� */
        unsigned long  reserved             : 21; /* bit[11-31]: ���� */
    } reg;
} CBBP_UNIT2_CORR_WAIT_CHIP_UNION;
#define CBBP_UNIT2_CORR_WAIT_CHIP_unit2_corr_wait_chip_START  (0)
#define CBBP_UNIT2_CORR_WAIT_CHIP_unit2_corr_wait_chip_END    (10)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_ANT_SEL_UNION
 �ṹ˵��  : UNIT2_ANT_SEL �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_ant_sel_reg;
    struct
    {
        unsigned long  unit2_ant_sel : 1;  /* bit[0]   : ������������ѡ��
                                                         0����ʾ�����������1�����ݣ�
                                                         1����ʾ�����������2�����ݣ� */
        unsigned long  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_UNIT2_ANT_SEL_UNION;
#define CBBP_UNIT2_ANT_SEL_unit2_ant_sel_START  (0)
#define CBBP_UNIT2_ANT_SEL_unit2_ant_sel_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_MODE_UNION
 �ṹ˵��  : UNIT2_MODE �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_mode_reg;
    struct
    {
        unsigned long  unit2_mode : 2;  /* bit[0-1] : ģʽѡ��
                                                      0����ʾ��ʼС������
                                                      1����ʾpn�б�С������
                                                      2����ʾ�ྶ������С�����������������ۼӣ�
                                                      3����ʾС���������������ۼ��������ۼӣ� */
        unsigned long  reserved   : 30; /* bit[2-31]: ���� */
    } reg;
} CBBP_UNIT2_MODE_UNION;
#define CBBP_UNIT2_MODE_unit2_mode_START  (0)
#define CBBP_UNIT2_MODE_unit2_mode_END    (1)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_WIN_UNION
 �ṹ˵��  : UNIT2_WIN �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_win_reg;
    struct
    {
        unsigned long  unit2_win : 10; /* bit[0-9]  : ����������λΪ64chip�����÷�ΧΪ1~512��
                                                      
                                                      ��ʼС������ʱ����֧��������������������Ϊ128����������Ϊ64*128=8192chip��
                                                      PN�б�С������ʱ����֧������������������������̶�Ϊ64chip��
                                                      �ྶ��������֧��ʵʱ������������������̶�50chip��
                                                      С������ģʽ��С����������֧���������ݲ���������̶�Ϊ64chip */
        unsigned long  reserved  : 22; /* bit[10-31]: ���� */
    } reg;
} CBBP_UNIT2_WIN_UNION;
#define CBBP_UNIT2_WIN_unit2_win_START  (0)
#define CBBP_UNIT2_WIN_unit2_win_END    (9)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_DATA_SEL_UNION
 �ṹ˵��  : UNIT2_DATA_SEL �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_data_sel_reg;
    struct
    {
        unsigned long  unit2_data_sel : 1;  /* bit[0]   : ��������ѡ��
                                                          0����ʾʹ��ʵʱ���ݣ�
                                                          1����ʾʹ�û�������� */
        unsigned long  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_UNIT2_DATA_SEL_UNION;
#define CBBP_UNIT2_DATA_SEL_unit2_data_sel_START  (0)
#define CBBP_UNIT2_DATA_SEL_unit2_data_sel_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_DATA_STORE_MODE_UNION
 �ṹ˵��  : UNIT2_DATA_STORE_MODE �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_data_store_mode_reg;
    struct
    {
        unsigned long  unit2_data_store_mode : 3;  /* bit[0-2] : �������ݵ�ģʽ���˲������������һ�λ�������ʱ�Ĳ���Data_store_mode��ͬ
                                                                 0��ʾ�����洢��
                                                                 1��ʾÿ1024chip�洢64chip��
                                                                 2��ʾÿ1024chip�洢96chip��
                                                                 3��ʾÿ1024chip�洢128chip��
                                                                 4��ʾÿ1024chip�洢256chip
                                                                 5��ʾÿ1024chip�洢512chip�� */
        unsigned long  reserved              : 29; /* bit[3-31]: ���� */
    } reg;
} CBBP_UNIT2_DATA_STORE_MODE_UNION;
#define CBBP_UNIT2_DATA_STORE_MODE_unit2_data_store_mode_START  (0)
#define CBBP_UNIT2_DATA_STORE_MODE_unit2_data_store_mode_END    (2)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_DATA_POS_UNION
 �ṹ˵��  : UNIT2_DATA_POS �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_data_pos_reg;
    struct
    {
        unsigned long  unit2_data_pos : 16; /* bit[0-15] : ʹ��ʵʱ����ʱ���������ݵ���ʼλ�ã���base_cnt[21:6]�ϵ�λ�ã�1/2chip���� */
        unsigned long  reserved       : 16; /* bit[16-31]: ���� */
    } reg;
} CBBP_UNIT2_DATA_POS_UNION;
#define CBBP_UNIT2_DATA_POS_unit2_data_pos_START  (0)
#define CBBP_UNIT2_DATA_POS_unit2_data_pos_END    (15)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_DATA_POS_SEL_UNION
 �ṹ˵��  : UNIT2_DATA_POS_SEL �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_data_pos_sel_reg;
    struct
    {
        unsigned long  unit2_data_pos_sel : 1;  /* bit[0]   : ʹ��ʵʱ����ʱ��Ч��
                                                              0����ʾ���Ծͽ���ʼ������
                                                              1������ȴ�Unit0_data_posʱ�����ܿ�ʼ������ */
        unsigned long  reserved           : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_UNIT2_DATA_POS_SEL_UNION;
#define CBBP_UNIT2_DATA_POS_SEL_unit2_data_pos_sel_START  (0)
#define CBBP_UNIT2_DATA_POS_SEL_unit2_data_pos_sel_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_DATA_MODE_UNION
 �ṹ˵��  : UNIT2_DATA_MODE �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_data_mode_reg;
    struct
    {
        unsigned long  unit2_data_mode : 3;  /* bit[0-2] : ��������ȡ����ʽ��
                                                           0��ʾ����ȡ����
                                                           1��ʾÿ1024chipȡ��64chip��
                                                           2��ʾÿ1024chipȡ��96chip��
                                                           3��ʾÿ1024chipȡ��128chip��
                                                           4��ʾÿ1024chipȡ��256chip
                                                           5��ʾÿ1024chip�洢512chip��
                                                           
                                                           ˵����
                                                           ����ʹ�û������ݣ�����Unit0_data_store_modeȷ���������ݵ�������ұ�������Unit0_data_mode<=Unit0_data_store_mode��
                                                           ����ʹ��ʵʱ���ݣ����ʵ������ʱ���Ѿ������Unit0_data_posʱ�̣����������ȡ��ʱ����ʵ������ʱ�̿�ʼȡ��������ÿ1024chip���ȡ�����������64/96chip/128chip/256chipȡ��λ�ÿ�ʼȡ���� */
        unsigned long  reserved        : 29; /* bit[3-31]: ���� */
    } reg;
} CBBP_UNIT2_DATA_MODE_UNION;
#define CBBP_UNIT2_DATA_MODE_unit2_data_mode_START  (0)
#define CBBP_UNIT2_DATA_MODE_unit2_data_mode_END    (2)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_PN_NUM_UNION
 �ṹ˵��  : UNIT2_PN_NUM �Ĵ����ṹ���塣��ַƫ����:0x002C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn_num_reg;
    struct
    {
        unsigned long  unit2_pn_num : 5;  /* bit[0-4] : Pn�б�С������ʱ��pn offset������֧��1~16�� */
        unsigned long  reserved     : 27; /* bit[5-31]: ���� */
    } reg;
} CBBP_UNIT2_PN_NUM_UNION;
#define CBBP_UNIT2_PN_NUM_unit2_pn_num_START  (0)
#define CBBP_UNIT2_PN_NUM_unit2_pn_num_END    (4)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_CORR_LENGTH_UNION
 �ṹ˵��  : UNIT2_CORR_LENGTH �Ĵ����ṹ���塣��ַƫ����:0x0030����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_corr_length_reg;
    struct
    {
        unsigned long  unit2_corr_length : 4;  /* bit[0-3] : ��ɳ���
                                                             0��32
                                                             1��64
                                                             2��96
                                                             3��128
                                                             4��256
                                                             5��96*4=384
                                                             6��64*12=768
                                                             7��512
                                                             �㷨�Ƽ���
                                                             1xС����������ۼӳ��ȿ�����Ϊ64��128��256����Ӧ�ķ�����ۼӳ���Ϊ32��16��8��
                                                             evdoС��������ɳ���Ϊ64��������ۼӳ���Ϊ32/16/8��
                                                             1x�ྶ������ɳ���Ϊ64x12=768��afc��������64x1=64��afcʧ�������֣���Ӧ�ķ�����ۼӳ��ȷֱ�Ϊ8��96��
                                                             Evdo�ྶ������ɳ���96x4=384��afc��������96x1=96��afcʧ��������Ӧ�ķ�����ۼӳ��ȷֱ�Ϊ8��32�� */
        unsigned long  reserved          : 28; /* bit[4-31]: ���� */
    } reg;
} CBBP_UNIT2_CORR_LENGTH_UNION;
#define CBBP_UNIT2_CORR_LENGTH_unit2_corr_length_START  (0)
#define CBBP_UNIT2_CORR_LENGTH_unit2_corr_length_END    (3)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_NCORR_LENGTH_UNION
 �ṹ˵��  : UNIT2_NCORR_LENGTH �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_ncorr_length_reg;
    struct
    {
        unsigned long  unit2_ncorr_lenth : 3;  /* bit[0-2] : ����ɳ���
                                                             0��1
                                                             1��2
                                                             2��3
                                                             3��4
                                                             4��8
                                                             5��16
                                                             6��32
                                                             7��96 */
        unsigned long  reserved          : 29; /* bit[3-31]: ���� */
    } reg;
} CBBP_UNIT2_NCORR_LENGTH_UNION;
#define CBBP_UNIT2_NCORR_LENGTH_unit2_ncorr_lenth_START  (0)
#define CBBP_UNIT2_NCORR_LENGTH_unit2_ncorr_lenth_END    (2)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_ABS_TH_UNION
 �ṹ˵��  : UNIT2_ABS_TH �Ĵ����ṹ���塣��ַƫ����:0x0038����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_abs_th_reg;
    struct
    {
        unsigned long  unit2_abs_th : 16; /* bit[0-15] : ������������ */
        unsigned long  reserved     : 16; /* bit[16-31]: ���� */
    } reg;
} CBBP_UNIT2_ABS_TH_UNION;
#define CBBP_UNIT2_ABS_TH_unit2_abs_th_START  (0)
#define CBBP_UNIT2_ABS_TH_unit2_abs_th_END    (15)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_EN_UNION
 �ṹ˵��  : UNIT2_EN �Ĵ����ṹ���塣��ַƫ����:0x003C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_en_reg;
    struct
    {
        unsigned long  unit2_en : 1;  /* bit[0]   : ������Ԫʹ���ź� */
        unsigned long  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_UNIT2_EN_UNION;
#define CBBP_UNIT2_EN_unit2_en_START  (0)
#define CBBP_UNIT2_EN_unit2_en_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_NOISE_ENERGY_UNION
 �ṹ˵��  : UNIT2_NOISE_ENERGY �Ĵ����ṹ���塣��ַƫ����:0x0040����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_noise_energy_reg;
    struct
    {
        unsigned long  unit2_noise_energy : 16; /* bit[0-15] : ��Ԫ0����С�������ϱ����������� */
        unsigned long  reserved           : 16; /* bit[16-31]: ���� */
    } reg;
} CBBP_UNIT2_NOISE_ENERGY_UNION;
#define CBBP_UNIT2_NOISE_ENERGY_unit2_noise_energy_START  (0)
#define CBBP_UNIT2_NOISE_ENERGY_unit2_noise_energy_END    (15)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_FRAME_SHIFT_UNION
 �ṹ˵��  : UNIT2_FRAME_SHIFT �Ĵ����ṹ���塣��ַƫ����:0x0044����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_frame_shift_reg;
    struct
    {
        unsigned long  unit2_frame_shft : 1;  /* bit[0]   : ��Ԫ0�����ϱ�������ƫ��1/2chipָʾ���ྶ������С������ʱ��Ч��
                                                            0����ʾ�ϱ���������������������ȫһ��
                                                            1����ʾ�ϱ����������������������ƫ����1/2chip������ԭ�����õ�λ�ã�����ƫ����1/2chip */
        unsigned long  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_UNIT2_FRAME_SHIFT_UNION;
#define CBBP_UNIT2_FRAME_SHIFT_unit2_frame_shft_START  (0)
#define CBBP_UNIT2_FRAME_SHIFT_unit2_frame_shft_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_PN0_FRAME_POS_UNION
 �ṹ˵��  : UNIT2_PN0_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0048����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn0_frame_pos_reg;
    struct
    {
        unsigned long  unit2_pn0_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                ����Ƕྶ������С����������ʼС������ʱ����ʾ����Ԫ����������β��Ӧ��f-pich֡ͷλ�á�
                                                                �����Pn�б�С����������ʾ��һ��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT2_PN0_FRAME_POS_UNION;
#define CBBP_UNIT2_PN0_FRAME_POS_unit2_pn0_frame_pos_START  (0)
#define CBBP_UNIT2_PN0_FRAME_POS_unit2_pn0_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_PN1_FRAME_POS_UNION
 �ṹ˵��  : UNIT2_PN1_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x004C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn1_frame_pos_reg;
    struct
    {
        unsigned long  unit2_pn1_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��2��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT2_PN1_FRAME_POS_UNION;
#define CBBP_UNIT2_PN1_FRAME_POS_unit2_pn1_frame_pos_START  (0)
#define CBBP_UNIT2_PN1_FRAME_POS_unit2_pn1_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_PN2_FRAME_POS_UNION
 �ṹ˵��  : UNIT2_PN2_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0050����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn2_frame_pos_reg;
    struct
    {
        unsigned long  unit2_pn2_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��3��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT2_PN2_FRAME_POS_UNION;
#define CBBP_UNIT2_PN2_FRAME_POS_unit2_pn2_frame_pos_START  (0)
#define CBBP_UNIT2_PN2_FRAME_POS_unit2_pn2_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_PN3_FRAME_POS_UNION
 �ṹ˵��  : UNIT2_PN3_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0054����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn3_frame_pos_reg;
    struct
    {
        unsigned long  unit2_pn3_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[19:5]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��4��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT2_PN3_FRAME_POS_UNION;
#define CBBP_UNIT2_PN3_FRAME_POS_unit2_pn3_frame_pos_START  (0)
#define CBBP_UNIT2_PN3_FRAME_POS_unit2_pn3_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_PN4_FRAME_POS_UNION
 �ṹ˵��  : UNIT2_PN4_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0058����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn4_frame_pos_reg;
    struct
    {
        unsigned long  unit2_pn4_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��5��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT2_PN4_FRAME_POS_UNION;
#define CBBP_UNIT2_PN4_FRAME_POS_unit2_pn4_frame_pos_START  (0)
#define CBBP_UNIT2_PN4_FRAME_POS_unit2_pn4_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_PN5_FRAME_POS_UNION
 �ṹ˵��  : UNIT2_PN5_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x005C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn5_frame_pos_reg;
    struct
    {
        unsigned long  unit2_pn5_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��6��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT2_PN5_FRAME_POS_UNION;
#define CBBP_UNIT2_PN5_FRAME_POS_unit2_pn5_frame_pos_START  (0)
#define CBBP_UNIT2_PN5_FRAME_POS_unit2_pn5_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_PN6_FRAME_POS_UNION
 �ṹ˵��  : UNIT2_PN6_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0060����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn6_frame_pos_reg;
    struct
    {
        unsigned long  unit2_pn6_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��7��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT2_PN6_FRAME_POS_UNION;
#define CBBP_UNIT2_PN6_FRAME_POS_unit2_pn6_frame_pos_START  (0)
#define CBBP_UNIT2_PN6_FRAME_POS_unit2_pn6_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_PN7_FRAME_POS_UNION
 �ṹ˵��  : UNIT2_PN7_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0064����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn7_frame_pos_reg;
    struct
    {
        unsigned long  unit2_pn7_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��8��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT2_PN7_FRAME_POS_UNION;
#define CBBP_UNIT2_PN7_FRAME_POS_unit2_pn7_frame_pos_START  (0)
#define CBBP_UNIT2_PN7_FRAME_POS_unit2_pn7_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_PN8_FRAME_POS_UNION
 �ṹ˵��  : UNIT2_PN8_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0068����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn8_frame_pos_reg;
    struct
    {
        unsigned long  unit2_pn8_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��9��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT2_PN8_FRAME_POS_UNION;
#define CBBP_UNIT2_PN8_FRAME_POS_unit2_pn8_frame_pos_START  (0)
#define CBBP_UNIT2_PN8_FRAME_POS_unit2_pn8_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_PN9_FRAME_POS_UNION
 �ṹ˵��  : UNIT2_PN9_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x006C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn9_frame_pos_reg;
    struct
    {
        unsigned long  unit2_pn9_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��10��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT2_PN9_FRAME_POS_UNION;
#define CBBP_UNIT2_PN9_FRAME_POS_unit2_pn9_frame_pos_START  (0)
#define CBBP_UNIT2_PN9_FRAME_POS_unit2_pn9_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_PN10_FRAME_POS_UNION
 �ṹ˵��  : UNIT2_PN10_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0070����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn10_frame_pos_reg;
    struct
    {
        unsigned long  unit2_pn10_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                 �����Pn�б�С����������ʾ��11��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved             : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT2_PN10_FRAME_POS_UNION;
#define CBBP_UNIT2_PN10_FRAME_POS_unit2_pn10_frame_pos_START  (0)
#define CBBP_UNIT2_PN10_FRAME_POS_unit2_pn10_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_PN11_FRAME_POS_UNION
 �ṹ˵��  : UNIT2_PN11_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0074����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn11_frame_pos_reg;
    struct
    {
        unsigned long  unit2_pn11_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                 �����Pn�б�С����������ʾ��12��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved             : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT2_PN11_FRAME_POS_UNION;
#define CBBP_UNIT2_PN11_FRAME_POS_unit2_pn11_frame_pos_START  (0)
#define CBBP_UNIT2_PN11_FRAME_POS_unit2_pn11_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_PN12_FRAME_POS_UNION
 �ṹ˵��  : UNIT2_PN12_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0078����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn12_frame_pos_reg;
    struct
    {
        unsigned long  unit2_pn12_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                 �����Pn�б�С����������ʾ��13��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved             : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT2_PN12_FRAME_POS_UNION;
#define CBBP_UNIT2_PN12_FRAME_POS_unit2_pn12_frame_pos_START  (0)
#define CBBP_UNIT2_PN12_FRAME_POS_unit2_pn12_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_PN13_FRAME_POS_UNION
 �ṹ˵��  : UNIT2_PN13_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x007C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn13_frame_pos_reg;
    struct
    {
        unsigned long  unit2_pn13_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                 �����Pn�б�С����������ʾ��14��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved             : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT2_PN13_FRAME_POS_UNION;
#define CBBP_UNIT2_PN13_FRAME_POS_unit2_pn13_frame_pos_START  (0)
#define CBBP_UNIT2_PN13_FRAME_POS_unit2_pn13_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_PN14_FRAME_POS_UNION
 �ṹ˵��  : UNIT2_PN14_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0080����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn14_frame_pos_reg;
    struct
    {
        unsigned long  unit2_pn14_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                 �����Pn�б�С����������ʾ��15��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved             : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT2_PN14_FRAME_POS_UNION;
#define CBBP_UNIT2_PN14_FRAME_POS_unit2_pn14_frame_pos_START  (0)
#define CBBP_UNIT2_PN14_FRAME_POS_unit2_pn14_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_PN15_FRAME_POS_UNION
 �ṹ˵��  : UNIT2_PN15_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0084����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn15_frame_pos_reg;
    struct
    {
        unsigned long  unit2_pn15_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                 �����Pn�б�С����������ʾ��16��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved             : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT2_PN15_FRAME_POS_UNION;
#define CBBP_UNIT2_PN15_FRAME_POS_unit2_pn15_frame_pos_START  (0)
#define CBBP_UNIT2_PN15_FRAME_POS_unit2_pn15_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_CS_1X_MODE_UNION
 �ṹ˵��  : UNIT2_CS_1X_MODE �Ĵ����ṹ���塣��ַƫ����:0x0088����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_cs_1x_mode_reg;
    struct
    {
        unsigned long  unit2_cs_1x_mode : 1;  /* bit[0]   : ����ģʽѡ��
                                                            0��ʾ1x����
                                                            1��ʾevdo���� */
        unsigned long  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_UNIT2_CS_1X_MODE_UNION;
#define CBBP_UNIT2_CS_1X_MODE_unit2_cs_1x_mode_START  (0)
#define CBBP_UNIT2_CS_1X_MODE_unit2_cs_1x_mode_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_SRCH_CK_BYPASS_UNION
 �ṹ˵��  : UNIT2_SRCH_CK_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x008C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_srch_ck_bypass_reg;
    struct
    {
        unsigned long  unit2_ctrl_pass   : 1;  /* bit[0]   : ������Ԫ���Ʋ���ʱ���ſ�bypass
                                                             0��ʾʱ���ſ���Ч
                                                             1��ʾʱ�ӳ��� */
        unsigned long  unit2_sort_bypass : 1;  /* bit[1]   : ������Ԫ�Ŷ�ģ��ʱ���ſ�
                                                             0��ʾʱ���ſ���Ч
                                                             1��ʾʱ�ӳ��� */
        unsigned long  unit2_rpt_bypass  : 1;  /* bit[2]   : ������Ԫ�ϱ�ģ��ʱ���ſ�
                                                             0��ʾʱ���ſ���Ч
                                                             1��ʾʱ�ӳ��� */
        unsigned long  reserved          : 29; /* bit[3-31]: ���� */
    } reg;
} CBBP_UNIT2_SRCH_CK_BYPASS_UNION;
#define CBBP_UNIT2_SRCH_CK_BYPASS_unit2_ctrl_pass_START    (0)
#define CBBP_UNIT2_SRCH_CK_BYPASS_unit2_ctrl_pass_END      (0)
#define CBBP_UNIT2_SRCH_CK_BYPASS_unit2_sort_bypass_START  (1)
#define CBBP_UNIT2_SRCH_CK_BYPASS_unit2_sort_bypass_END    (1)
#define CBBP_UNIT2_SRCH_CK_BYPASS_unit2_rpt_bypass_START   (2)
#define CBBP_UNIT2_SRCH_CK_BYPASS_unit2_rpt_bypass_END     (2)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_NOISE_ALPHER_COEF_UNION
 �ṹ˵��  : UNIT2_NOISE_ALPHER_COEF �Ĵ����ṹ���塣��ַƫ����:0x0090����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_noise_alpher_coef_reg;
    struct
    {
        unsigned long  unit2_noise_alpher_coef : 3;  /* bit[0-2] : ���������˲�ϵ����
                                                                   0��1/2
                                                                   1:1/16
                                                                   2:1/32
                                                                   3:1/64
                                                                   4:1/128
                                                                   5:1/256 */
        unsigned long  reserved                : 29; /* bit[3-31]: ���� */
    } reg;
} CBBP_UNIT2_NOISE_ALPHER_COEF_UNION;
#define CBBP_UNIT2_NOISE_ALPHER_COEF_unit2_noise_alpher_coef_START  (0)
#define CBBP_UNIT2_NOISE_ALPHER_COEF_unit2_noise_alpher_coef_END    (2)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_DATA_STORE_OFF_UNION
 �ṹ˵��  : UNIT2_DATA_STORE_OFF �Ĵ����ṹ���塣��ַƫ����:0x0094����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_data_store_off_reg;
    struct
    {
        unsigned long  unit2_data_store_off : 10; /* bit[0-9]  : �ӻ���������ȡ��ƫ�ƣ�chip��λ��
                                                                 ʹ�ó�������ԶС����������������4096chip���ݣ�����ʱ��ÿ1024chip��ȡ�������ݣ���ȡλ���ɴ˼Ĵ���ȷ�� */
        unsigned long  reserved             : 22; /* bit[10-31]: ���� */
    } reg;
} CBBP_UNIT2_DATA_STORE_OFF_UNION;
#define CBBP_UNIT2_DATA_STORE_OFF_unit2_data_store_off_START  (0)
#define CBBP_UNIT2_DATA_STORE_OFF_unit2_data_store_off_END    (9)


/***======================================================================***
                     (8/20) register_define_c_cs_mps_unit3
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_CLK_MODE_UNION
 �ṹ˵��  : UNIT3_CLK_MODE �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_clk_mode_reg;
    struct
    {
        unsigned long  unit3_clk_mode : 1;  /* bit[0]   : ������Ԫʱ��Ƶ��ѡ��
                                                          0����ʾ������Ԫ128��ʱ�ӣ�
                                                          1����ʾ������Ԫ64��ʱ��
                                                          Ĭ�ϲ���Ҫ������� */
        unsigned long  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_UNIT3_CLK_MODE_UNION;
#define CBBP_UNIT3_CLK_MODE_unit3_clk_mode_START  (0)
#define CBBP_UNIT3_CLK_MODE_unit3_clk_mode_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_CORR_RPT_PERIOD_UNION
 �ṹ˵��  : UNIT3_CORR_RPT_PERIOD �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_corr_rpt_period_reg;
    struct
    {
        unsigned long  unit3_corr_rpt_period : 4;  /* bit[0-3] : ʹ���������ݶྶ��������С��������ʱ�����ٸ�����ۼӽ���ϱ�һ�Ρ�
                                                                 �˽ӿ���Ҫ�ǽ��afcʧ��ʱ��1x������ۼӳ���Ϊ64chip������ɽ���ϱ�����̫�ܼ������⡣
                                                                 ����1x��afcʧ��ʱ����������ȡ12����ÿ64x12=768chip�ڣ��ϱ���һ��64chip������ɽ����
                                                                 ����1x��afc����ʱ����������ȡ1����ÿ64x12=768chip�ϱ�һ������ۼӽ����
                                                                 ����evdoʱ����������ȡ1����ÿ1024chip��afcʧ������4096chip��afc�������ϱ�һ����ɽ���� */
        unsigned long  reserved              : 28; /* bit[4-31]: ���� */
    } reg;
} CBBP_UNIT3_CORR_RPT_PERIOD_UNION;
#define CBBP_UNIT3_CORR_RPT_PERIOD_unit3_corr_rpt_period_START  (0)
#define CBBP_UNIT3_CORR_RPT_PERIOD_unit3_corr_rpt_period_END    (3)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_CORR_WAIT_CHIP_UNION
 �ṹ˵��  : UNIT3_CORR_WAIT_CHIP �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_corr_wait_chip_reg;
    struct
    {
        unsigned long  unit3_corr_wait_chip : 11; /* bit[0-10] : ʹ����ɢ��������С������ʱ��ÿ����1024chip�ڵ�һ�����ݣ��ȴ��೤ʱ�䣬������һ��1024chip������λchip��
                                                                 �˽ӿ���Ҫ���ʹ����ɢ�����������С������ʱ���ж��ϱ��ܼ��������
                                                                 ���ڶྶ����ģʽ��BBP���������ۼӣ�������ʱ���������� */
        unsigned long  reserved             : 21; /* bit[11-31]: ���� */
    } reg;
} CBBP_UNIT3_CORR_WAIT_CHIP_UNION;
#define CBBP_UNIT3_CORR_WAIT_CHIP_unit3_corr_wait_chip_START  (0)
#define CBBP_UNIT3_CORR_WAIT_CHIP_unit3_corr_wait_chip_END    (10)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_ANT_SEL_UNION
 �ṹ˵��  : UNIT3_ANT_SEL �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_ant_sel_reg;
    struct
    {
        unsigned long  unit3_ant_sel : 1;  /* bit[0]   : ������������ѡ��
                                                         0����ʾ�����������1�����ݣ�
                                                         1����ʾ�����������2�����ݣ� */
        unsigned long  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_UNIT3_ANT_SEL_UNION;
#define CBBP_UNIT3_ANT_SEL_unit3_ant_sel_START  (0)
#define CBBP_UNIT3_ANT_SEL_unit3_ant_sel_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_MODE_UNION
 �ṹ˵��  : UNIT3_MODE �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_mode_reg;
    struct
    {
        unsigned long  unit3_mode : 2;  /* bit[0-1] : ģʽѡ��
                                                      0����ʾ��ʼС������
                                                      1����ʾpn�б�С������
                                                      2����ʾ�ྶ������С�����������������ۼӣ�
                                                      3����ʾС���������������ۼ��������ۼӣ� */
        unsigned long  reserved   : 30; /* bit[2-31]: ���� */
    } reg;
} CBBP_UNIT3_MODE_UNION;
#define CBBP_UNIT3_MODE_unit3_mode_START  (0)
#define CBBP_UNIT3_MODE_unit3_mode_END    (1)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_WIN_UNION
 �ṹ˵��  : UNIT3_WIN �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_win_reg;
    struct
    {
        unsigned long  unit3_win : 10; /* bit[0-9]  : ����������λΪ64chip�����÷�ΧΪ1~512��
                                                      
                                                      ��ʼС������ʱ����֧��������������������Ϊ128����������Ϊ64*128=8192chip��
                                                      PN�б�С������ʱ����֧������������������������̶�Ϊ64chip��
                                                      �ྶ��������֧��ʵʱ������������������̶�50chip��
                                                      С������ģʽ��С����������֧���������ݲ���������̶�Ϊ64chip�� */
        unsigned long  reserved  : 22; /* bit[10-31]: ���� */
    } reg;
} CBBP_UNIT3_WIN_UNION;
#define CBBP_UNIT3_WIN_unit3_win_START  (0)
#define CBBP_UNIT3_WIN_unit3_win_END    (9)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_DATA_SEL_UNION
 �ṹ˵��  : UNIT3_DATA_SEL �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_data_sel_reg;
    struct
    {
        unsigned long  unit3_data_sel : 1;  /* bit[0]   : ��������ѡ��
                                                          0����ʾʹ��ʵʱ���ݣ�
                                                          1����ʾʹ�û�������� */
        unsigned long  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_UNIT3_DATA_SEL_UNION;
#define CBBP_UNIT3_DATA_SEL_unit3_data_sel_START  (0)
#define CBBP_UNIT3_DATA_SEL_unit3_data_sel_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_DATA_STORE_MODE_UNION
 �ṹ˵��  : UNIT3_DATA_STORE_MODE �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_data_store_mode_reg;
    struct
    {
        unsigned long  unit3_data_store_mode : 3;  /* bit[0-2] : �������ݵ�ģʽ���˲������������һ�λ�������ʱ�Ĳ���Data_store_mode��ͬ
                                                                 0��ʾ�����洢��
                                                                 1��ʾÿ1024chip�洢64chip��
                                                                 2��ʾÿ1024chip�洢96chip��
                                                                 3��ʾÿ1024chip�洢128chip��
                                                                 4��ʾÿ1024chip�洢256chip
                                                                 5��ʾÿ1024chip�洢512chip�� */
        unsigned long  reserved              : 29; /* bit[3-31]: ���� */
    } reg;
} CBBP_UNIT3_DATA_STORE_MODE_UNION;
#define CBBP_UNIT3_DATA_STORE_MODE_unit3_data_store_mode_START  (0)
#define CBBP_UNIT3_DATA_STORE_MODE_unit3_data_store_mode_END    (2)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_DATA_POS_UNION
 �ṹ˵��  : UNIT3_DATA_POS �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_data_pos_reg;
    struct
    {
        unsigned long  unit3_data_pos : 16; /* bit[0-15] : ʹ��ʵʱ����ʱ���������ݵ���ʼλ�ã���base_cnt[21:6]�ϵ�λ�ã�1/2chip���� */
        unsigned long  reserved       : 16; /* bit[16-31]: ���� */
    } reg;
} CBBP_UNIT3_DATA_POS_UNION;
#define CBBP_UNIT3_DATA_POS_unit3_data_pos_START  (0)
#define CBBP_UNIT3_DATA_POS_unit3_data_pos_END    (15)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_DATA_POS_SEL_UNION
 �ṹ˵��  : UNIT3_DATA_POS_SEL �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_data_pos_sel_reg;
    struct
    {
        unsigned long  unit3_data_pos_sel : 1;  /* bit[0]   : ʹ��ʵʱ����ʱ��Ч��
                                                              0����ʾ���Ծͽ���ʼ������
                                                              1������ȴ�Unit0_data_posʱ�����ܿ�ʼ������ */
        unsigned long  reserved           : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_UNIT3_DATA_POS_SEL_UNION;
#define CBBP_UNIT3_DATA_POS_SEL_unit3_data_pos_sel_START  (0)
#define CBBP_UNIT3_DATA_POS_SEL_unit3_data_pos_sel_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_DATA_MODE_UNION
 �ṹ˵��  : UNIT3_DATA_MODE �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_data_mode_reg;
    struct
    {
        unsigned long  unit3_data_mode : 3;  /* bit[0-2] : ��������ȡ����ʽ��
                                                           0��ʾ����ȡ����
                                                           1��ʾÿ1024chipȡ��64chip��
                                                           2��ʾÿ1024chipȡ��96chip��
                                                           3��ʾÿ1024chipȡ��128chip��
                                                           4��ʾÿ1024chipȡ��256chip
                                                           5��ʾÿ1024chip�洢512chip��
                                                           
                                                           ˵����
                                                           ����ʹ�û������ݣ�����Unit0_data_store_modeȷ���������ݵ�������ұ�������Unit0_data_mode<=Unit0_data_store_mode��
                                                           ����ʹ��ʵʱ���ݣ����ʵ������ʱ���Ѿ������Unit0_data_posʱ�̣����������ȡ��ʱ����ʵ������ʱ�̿�ʼȡ��������ÿ1024chip���ȡ�����������64/96chip/128chip/256chipȡ��λ�ÿ�ʼȡ���� */
        unsigned long  reserved        : 29; /* bit[3-31]: ���� */
    } reg;
} CBBP_UNIT3_DATA_MODE_UNION;
#define CBBP_UNIT3_DATA_MODE_unit3_data_mode_START  (0)
#define CBBP_UNIT3_DATA_MODE_unit3_data_mode_END    (2)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_PN_NUM_UNION
 �ṹ˵��  : UNIT3_PN_NUM �Ĵ����ṹ���塣��ַƫ����:0x002C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn_num_reg;
    struct
    {
        unsigned long  unit3_pn_num : 5;  /* bit[0-4] : Pn�б�С������ʱ��pn offset������֧��1~16�� */
        unsigned long  reserved     : 27; /* bit[5-31]: ���� */
    } reg;
} CBBP_UNIT3_PN_NUM_UNION;
#define CBBP_UNIT3_PN_NUM_unit3_pn_num_START  (0)
#define CBBP_UNIT3_PN_NUM_unit3_pn_num_END    (4)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_CORR_LENGTH_UNION
 �ṹ˵��  : UNIT3_CORR_LENGTH �Ĵ����ṹ���塣��ַƫ����:0x0030����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_corr_length_reg;
    struct
    {
        unsigned long  unit3_corr_length : 4;  /* bit[0-3] : ��ɳ���
                                                             0��32
                                                             1��64
                                                             2��96
                                                             3��128
                                                             4��256
                                                             5��96*4=384
                                                             6��64*12=768
                                                             7��512
                                                             �㷨�Ƽ���
                                                             1xС����������ۼӳ��ȿ�����Ϊ64��128��256����Ӧ�ķ�����ۼӳ���Ϊ32��16��8��
                                                             evdoС��������ɳ���Ϊ64��������ۼӳ���Ϊ32/16/8��
                                                             1x�ྶ������ɳ���Ϊ64x12=768��afc��������64x1=64��afcʧ�������֣���Ӧ�ķ�����ۼӳ��ȷֱ�Ϊ8��96��
                                                             Evdo�ྶ������ɳ���96x4=384��afc��������96x1=96��afcʧ��������Ӧ�ķ�����ۼӳ��ȷֱ�Ϊ8��32�� */
        unsigned long  reserved          : 28; /* bit[4-31]: ���� */
    } reg;
} CBBP_UNIT3_CORR_LENGTH_UNION;
#define CBBP_UNIT3_CORR_LENGTH_unit3_corr_length_START  (0)
#define CBBP_UNIT3_CORR_LENGTH_unit3_corr_length_END    (3)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_NCORR_LENGTH_UNION
 �ṹ˵��  : UNIT3_NCORR_LENGTH �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_ncorr_length_reg;
    struct
    {
        unsigned long  unit3_ncorr_lenth : 3;  /* bit[0-2] : ����ɳ���
                                                             0��1
                                                             1��2
                                                             2��3
                                                             3��4
                                                             4��8
                                                             5��16
                                                             6��32
                                                             7��96 */
        unsigned long  reserved          : 29; /* bit[3-31]: ���� */
    } reg;
} CBBP_UNIT3_NCORR_LENGTH_UNION;
#define CBBP_UNIT3_NCORR_LENGTH_unit3_ncorr_lenth_START  (0)
#define CBBP_UNIT3_NCORR_LENGTH_unit3_ncorr_lenth_END    (2)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_ABS_TH_UNION
 �ṹ˵��  : UNIT3_ABS_TH �Ĵ����ṹ���塣��ַƫ����:0x0038����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_abs_th_reg;
    struct
    {
        unsigned long  unit3_abs_th : 16; /* bit[0-15] : ������������ */
        unsigned long  reserved     : 16; /* bit[16-31]: ���� */
    } reg;
} CBBP_UNIT3_ABS_TH_UNION;
#define CBBP_UNIT3_ABS_TH_unit3_abs_th_START  (0)
#define CBBP_UNIT3_ABS_TH_unit3_abs_th_END    (15)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_EN_UNION
 �ṹ˵��  : UNIT3_EN �Ĵ����ṹ���塣��ַƫ����:0x003C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_en_reg;
    struct
    {
        unsigned long  unit3_en : 1;  /* bit[0]   : ������Ԫʹ���ź� */
        unsigned long  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_UNIT3_EN_UNION;
#define CBBP_UNIT3_EN_unit3_en_START  (0)
#define CBBP_UNIT3_EN_unit3_en_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_NOISE_ENERGY_UNION
 �ṹ˵��  : UNIT3_NOISE_ENERGY �Ĵ����ṹ���塣��ַƫ����:0x0040����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_noise_energy_reg;
    struct
    {
        unsigned long  unit3_noise_energy : 16; /* bit[0-15] : ��Ԫ0����С�������ϱ����������� */
        unsigned long  reserved           : 16; /* bit[16-31]: ���� */
    } reg;
} CBBP_UNIT3_NOISE_ENERGY_UNION;
#define CBBP_UNIT3_NOISE_ENERGY_unit3_noise_energy_START  (0)
#define CBBP_UNIT3_NOISE_ENERGY_unit3_noise_energy_END    (15)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_FRAME_SHIFT_UNION
 �ṹ˵��  : UNIT3_FRAME_SHIFT �Ĵ����ṹ���塣��ַƫ����:0x0044����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_frame_shift_reg;
    struct
    {
        unsigned long  unit3_frame_shft : 1;  /* bit[0]   : ��Ԫ0�����ϱ�������ƫ��1/2chipָʾ���ྶ������С������ʱ��Ч��
                                                            0����ʾ�ϱ���������������������ȫһ��
                                                            1����ʾ�ϱ����������������������ƫ����1/2chip������ԭ�����õ�λ�ã�����ƫ����1/2chip */
        unsigned long  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_UNIT3_FRAME_SHIFT_UNION;
#define CBBP_UNIT3_FRAME_SHIFT_unit3_frame_shft_START  (0)
#define CBBP_UNIT3_FRAME_SHIFT_unit3_frame_shft_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_PN0_FRAME_POS_UNION
 �ṹ˵��  : UNIT3_PN0_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0048����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn0_frame_pos_reg;
    struct
    {
        unsigned long  unit3_pn0_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                ����Ƕྶ������С����������ʼС������ʱ����ʾ����Ԫ����������β��Ӧ��f-pich֡ͷλ�á�
                                                                �����Pn�б�С����������ʾ��һ��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT3_PN0_FRAME_POS_UNION;
#define CBBP_UNIT3_PN0_FRAME_POS_unit3_pn0_frame_pos_START  (0)
#define CBBP_UNIT3_PN0_FRAME_POS_unit3_pn0_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_PN1_FRAME_POS_UNION
 �ṹ˵��  : UNIT3_PN1_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x004C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn1_frame_pos_reg;
    struct
    {
        unsigned long  unit3_pn1_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��2��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT3_PN1_FRAME_POS_UNION;
#define CBBP_UNIT3_PN1_FRAME_POS_unit3_pn1_frame_pos_START  (0)
#define CBBP_UNIT3_PN1_FRAME_POS_unit3_pn1_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_PN2_FRAME_POS_UNION
 �ṹ˵��  : UNIT3_PN2_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0050����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn2_frame_pos_reg;
    struct
    {
        unsigned long  unit3_pn2_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��3��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT3_PN2_FRAME_POS_UNION;
#define CBBP_UNIT3_PN2_FRAME_POS_unit3_pn2_frame_pos_START  (0)
#define CBBP_UNIT3_PN2_FRAME_POS_unit3_pn2_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_PN3_FRAME_POS_UNION
 �ṹ˵��  : UNIT3_PN3_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0054����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn3_frame_pos_reg;
    struct
    {
        unsigned long  unit3_pn3_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[19:5]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��4��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT3_PN3_FRAME_POS_UNION;
#define CBBP_UNIT3_PN3_FRAME_POS_unit3_pn3_frame_pos_START  (0)
#define CBBP_UNIT3_PN3_FRAME_POS_unit3_pn3_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_PN4_FRAME_POS_UNION
 �ṹ˵��  : UNIT3_PN4_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0058����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn4_frame_pos_reg;
    struct
    {
        unsigned long  unit3_pn4_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��5��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT3_PN4_FRAME_POS_UNION;
#define CBBP_UNIT3_PN4_FRAME_POS_unit3_pn4_frame_pos_START  (0)
#define CBBP_UNIT3_PN4_FRAME_POS_unit3_pn4_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_PN5_FRAME_POS_UNION
 �ṹ˵��  : UNIT3_PN5_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x005C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn5_frame_pos_reg;
    struct
    {
        unsigned long  unit3_pn5_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��6��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT3_PN5_FRAME_POS_UNION;
#define CBBP_UNIT3_PN5_FRAME_POS_unit3_pn5_frame_pos_START  (0)
#define CBBP_UNIT3_PN5_FRAME_POS_unit3_pn5_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_PN6_FRAME_POS_UNION
 �ṹ˵��  : UNIT3_PN6_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0060����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn6_frame_pos_reg;
    struct
    {
        unsigned long  unit3_pn6_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��7��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT3_PN6_FRAME_POS_UNION;
#define CBBP_UNIT3_PN6_FRAME_POS_unit3_pn6_frame_pos_START  (0)
#define CBBP_UNIT3_PN6_FRAME_POS_unit3_pn6_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_PN7_FRAME_POS_UNION
 �ṹ˵��  : UNIT3_PN7_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0064����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn7_frame_pos_reg;
    struct
    {
        unsigned long  unit3_pn7_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��8��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT3_PN7_FRAME_POS_UNION;
#define CBBP_UNIT3_PN7_FRAME_POS_unit3_pn7_frame_pos_START  (0)
#define CBBP_UNIT3_PN7_FRAME_POS_unit3_pn7_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_PN8_FRAME_POS_UNION
 �ṹ˵��  : UNIT3_PN8_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0068����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn8_frame_pos_reg;
    struct
    {
        unsigned long  unit3_pn8_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��9��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT3_PN8_FRAME_POS_UNION;
#define CBBP_UNIT3_PN8_FRAME_POS_unit3_pn8_frame_pos_START  (0)
#define CBBP_UNIT3_PN8_FRAME_POS_unit3_pn8_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_PN9_FRAME_POS_UNION
 �ṹ˵��  : UNIT3_PN9_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x006C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn9_frame_pos_reg;
    struct
    {
        unsigned long  unit3_pn9_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                �����Pn�б�С����������ʾ��10��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved            : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT3_PN9_FRAME_POS_UNION;
#define CBBP_UNIT3_PN9_FRAME_POS_unit3_pn9_frame_pos_START  (0)
#define CBBP_UNIT3_PN9_FRAME_POS_unit3_pn9_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_PN10_FRAME_POS_UNION
 �ṹ˵��  : UNIT3_PN10_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0070����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn10_frame_pos_reg;
    struct
    {
        unsigned long  unit3_pn10_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                 �����Pn�б�С����������ʾ��11��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved             : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT3_PN10_FRAME_POS_UNION;
#define CBBP_UNIT3_PN10_FRAME_POS_unit3_pn10_frame_pos_START  (0)
#define CBBP_UNIT3_PN10_FRAME_POS_unit3_pn10_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_PN11_FRAME_POS_UNION
 �ṹ˵��  : UNIT3_PN11_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0074����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn11_frame_pos_reg;
    struct
    {
        unsigned long  unit3_pn11_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                 �����Pn�б�С����������ʾ��12��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved             : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT3_PN11_FRAME_POS_UNION;
#define CBBP_UNIT3_PN11_FRAME_POS_unit3_pn11_frame_pos_START  (0)
#define CBBP_UNIT3_PN11_FRAME_POS_unit3_pn11_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_PN12_FRAME_POS_UNION
 �ṹ˵��  : UNIT3_PN12_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0078����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn12_frame_pos_reg;
    struct
    {
        unsigned long  unit3_pn12_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                 �����Pn�б�С����������ʾ��13��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved             : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT3_PN12_FRAME_POS_UNION;
#define CBBP_UNIT3_PN12_FRAME_POS_unit3_pn12_frame_pos_START  (0)
#define CBBP_UNIT3_PN12_FRAME_POS_unit3_pn12_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_PN13_FRAME_POS_UNION
 �ṹ˵��  : UNIT3_PN13_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x007C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn13_frame_pos_reg;
    struct
    {
        unsigned long  unit3_pn13_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                 �����Pn�б�С����������ʾ��14��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved             : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT3_PN13_FRAME_POS_UNION;
#define CBBP_UNIT3_PN13_FRAME_POS_unit3_pn13_frame_pos_START  (0)
#define CBBP_UNIT3_PN13_FRAME_POS_unit3_pn13_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_PN14_FRAME_POS_UNION
 �ṹ˵��  : UNIT3_PN14_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0080����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn14_frame_pos_reg;
    struct
    {
        unsigned long  unit3_pn14_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                 �����Pn�б�С����������ʾ��15��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved             : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT3_PN14_FRAME_POS_UNION;
#define CBBP_UNIT3_PN14_FRAME_POS_unit3_pn14_frame_pos_START  (0)
#define CBBP_UNIT3_PN14_FRAME_POS_unit3_pn14_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_PN15_FRAME_POS_UNION
 �ṹ˵��  : UNIT3_PN15_FRAME_POS �Ĵ����ṹ���塣��ַƫ����:0x0084����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn15_frame_pos_reg;
    struct
    {
        unsigned long  unit3_pn15_frame_pos : 15; /* bit[0-14] : ��������β��Ӧ��f-pich�ŵ�֡ͷλ�ã���base_cnt[21:7]�ϵ�λ�ã�chip���ȡ�
                                                                 �����Pn�б�С����������ʾ��16��pn offset��Ӧ����������β��f-pich�ŵ�֡ͷλ�� */
        unsigned long  reserved             : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_UNIT3_PN15_FRAME_POS_UNION;
#define CBBP_UNIT3_PN15_FRAME_POS_unit3_pn15_frame_pos_START  (0)
#define CBBP_UNIT3_PN15_FRAME_POS_unit3_pn15_frame_pos_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_CS_1X_MODE_UNION
 �ṹ˵��  : UNIT3_CS_1X_MODE �Ĵ����ṹ���塣��ַƫ����:0x0088����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_cs_1x_mode_reg;
    struct
    {
        unsigned long  unit3_cs_1x_mode : 1;  /* bit[0]   : ����ģʽѡ��
                                                            0��ʾ1x����
                                                            1��ʾevdo���� */
        unsigned long  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_UNIT3_CS_1X_MODE_UNION;
#define CBBP_UNIT3_CS_1X_MODE_unit3_cs_1x_mode_START  (0)
#define CBBP_UNIT3_CS_1X_MODE_unit3_cs_1x_mode_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_SRCH_CK_BYPASS_UNION
 �ṹ˵��  : UNIT3_SRCH_CK_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x008C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_srch_ck_bypass_reg;
    struct
    {
        unsigned long  unit3_ctrl_pass   : 1;  /* bit[0]   : ������Ԫ���Ʋ���ʱ���ſ�bypass
                                                             0��ʾʱ���ſ���Ч
                                                             1��ʾʱ�ӳ��� */
        unsigned long  unit3_sort_bypass : 1;  /* bit[1]   : ������Ԫ�Ŷ�ģ��ʱ���ſ�
                                                             0��ʾʱ���ſ���Ч
                                                             1��ʾʱ�ӳ��� */
        unsigned long  unit3_rpt_bypass  : 1;  /* bit[2]   : ������Ԫ�ϱ�ģ��ʱ���ſ�
                                                             0��ʾʱ���ſ���Ч
                                                             1��ʾʱ�ӳ��� */
        unsigned long  reserved          : 29; /* bit[3-31]: ���� */
    } reg;
} CBBP_UNIT3_SRCH_CK_BYPASS_UNION;
#define CBBP_UNIT3_SRCH_CK_BYPASS_unit3_ctrl_pass_START    (0)
#define CBBP_UNIT3_SRCH_CK_BYPASS_unit3_ctrl_pass_END      (0)
#define CBBP_UNIT3_SRCH_CK_BYPASS_unit3_sort_bypass_START  (1)
#define CBBP_UNIT3_SRCH_CK_BYPASS_unit3_sort_bypass_END    (1)
#define CBBP_UNIT3_SRCH_CK_BYPASS_unit3_rpt_bypass_START   (2)
#define CBBP_UNIT3_SRCH_CK_BYPASS_unit3_rpt_bypass_END     (2)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_NOISE_ALPHER_COEF_UNION
 �ṹ˵��  : UNIT3_NOISE_ALPHER_COEF �Ĵ����ṹ���塣��ַƫ����:0x0090����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_noise_alpher_coef_reg;
    struct
    {
        unsigned long  unit3_noise_alpher_coef : 3;  /* bit[0-2] : ���������˲�ϵ����
                                                                   0��1/2
                                                                   1:1/16
                                                                   2:1/32
                                                                   3:1/64
                                                                   4:1/128
                                                                   5:1/256 */
        unsigned long  reserved                : 29; /* bit[3-31]: ���� */
    } reg;
} CBBP_UNIT3_NOISE_ALPHER_COEF_UNION;
#define CBBP_UNIT3_NOISE_ALPHER_COEF_unit3_noise_alpher_coef_START  (0)
#define CBBP_UNIT3_NOISE_ALPHER_COEF_unit3_noise_alpher_coef_END    (2)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_DATA_STORE_OFF_UNION
 �ṹ˵��  : UNIT3_DATA_STORE_OFF �Ĵ����ṹ���塣��ַƫ����:0x0094����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_data_store_off_reg;
    struct
    {
        unsigned long  unit3_data_store_off : 10; /* bit[0-9]  : �ӻ���������ȡ��ƫ�ƣ�chip��λ��
                                                                 ʹ�ó�������ԶС����������������4096chip���ݣ�����ʱ��ÿ1024chip��ȡ�������ݣ���ȡλ���ɴ˼Ĵ���ȷ�� */
        unsigned long  reserved             : 22; /* bit[10-31]: ���� */
    } reg;
} CBBP_UNIT3_DATA_STORE_OFF_UNION;
#define CBBP_UNIT3_DATA_STORE_OFF_unit3_data_store_off_START  (0)
#define CBBP_UNIT3_DATA_STORE_OFF_unit3_data_store_off_END    (9)


/***======================================================================***
                     (9/20) register_define_c_cs_mps_mem
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : CBBP_UNIT0_RPT_UNION
 �ṹ˵��  : UNIT0_RPT �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ྶ������С�����������������ۼӣ�ʱ���ϱ�128�������
            ��һ���洢���Ϊf-pich֡ͷΪUnit0_pn0_frame_pos����ɽ�����ڶ����洢���Ϊf-pich֡ͷΪ(Unit0_frame_pos-1/2chip)����ɽ������..��
            Bit[31:16]ΪQ·�����
            Bit[15:0]ΪI·�����
            
            С���������������ۼ��������ۼӣ�ʱ���ϱ�128�������
            ��һ���洢���Ϊf-pich֡ͷΪUnit0_pn0_frame_pos�Ľ�����ڶ����洢���Ϊf-pich֡ͷΪ(Unit0_frame_pos-1/2chip)�Ľ������..��
            Bit[15:0]Ϊ������ۼӽ����
            
            
            С������ʱ��ʹ�õ�ַ0~31���ϱ�32�������
            Bit[31:16]Ϊ��������С��pilot�ŵ�֡ͷ��base_cnt[19:4]��λ�ã�
            Bit[15:0]Ϊ������С���ϱ�����
*****************************************************************************/
typedef union
{
    unsigned long      unit0_rpt_reg;
    struct
    {
        unsigned long  unit0_rpt_low  : 16; /* bit[0-15] : �ྶ������С�����������������ۼӣ�ʱΪI·��ɽ����
                                                           С���������������ۼ��������ۼӣ�ʱΪ������ۼ�����
                                                           С������ʱΪС������ */
        unsigned long  unit0_rpt_high : 16; /* bit[16-31]: �ྶ������С�����������������ۼӣ�ʱΪQ·��ɽ��
                                                           С������ʱΪС��pilot�ŵ�֡ͷ��base_cnt[21:6]�ϵ�λ�ã�1/2chip���ȡ� */
    } reg;
} CBBP_UNIT0_RPT_UNION;
#define CBBP_UNIT0_RPT_unit0_rpt_low_START   (0)
#define CBBP_UNIT0_RPT_unit0_rpt_low_END     (15)
#define CBBP_UNIT0_RPT_unit0_rpt_high_START  (16)
#define CBBP_UNIT0_RPT_unit0_rpt_high_END    (31)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT1_RPT_UNION
 �ṹ˵��  : UNIT1_RPT �Ĵ����ṹ���塣��ַƫ����:0x0200����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ྶ������С�����������������ۼӣ�ʱ���ϱ�128�������
            ��һ���洢���Ϊf-pich֡ͷΪUnit0_pn0_frame_pos����ɽ�����ڶ����洢���Ϊf-pich֡ͷΪ(Unit0_frame_pos-1/2chip)����ɽ������..��
            Bit[31:16]ΪQ·�����
            Bit[15:0]ΪI·�����
            
            С���������������ۼ��������ۼӣ�ʱ���ϱ�128�������
            ��һ���洢���Ϊf-pich֡ͷΪUnit0_pn0_frame_pos�Ľ�����ڶ����洢���Ϊf-pich֡ͷΪ(Unit0_frame_pos-1/2chip)�Ľ������..��
            Bit[15:0]Ϊ������ۼӽ����
            
            
            С������ʱ��ʹ�õ�ַ0~31���ϱ�32�������
            Bit[31:16]Ϊ��������С��pilot�ŵ�֡ͷ��base_cnt[19:4]��λ�ã�
            Bit[15:0]Ϊ������С���ϱ�����
*****************************************************************************/
typedef union
{
    unsigned long      unit1_rpt_reg;
    struct
    {
        unsigned long  unit1_rpt_low  : 16; /* bit[0-15] : �ྶ������С�����������������ۼӣ�ʱΪI·��ɽ����
                                                           С���������������ۼ��������ۼӣ�ʱΪ������ۼ�����
                                                           С������ʱΪС������ */
        unsigned long  unit1_rpt_high : 16; /* bit[16-31]: �ྶ������С�����������������ۼӣ�ʱΪQ·��ɽ��
                                                           С������ʱΪС��pilot�ŵ�֡ͷ��base_cnt[21:6]�ϵ�λ�ã�1/2chip���ȡ� */
    } reg;
} CBBP_UNIT1_RPT_UNION;
#define CBBP_UNIT1_RPT_unit1_rpt_low_START   (0)
#define CBBP_UNIT1_RPT_unit1_rpt_low_END     (15)
#define CBBP_UNIT1_RPT_unit1_rpt_high_START  (16)
#define CBBP_UNIT1_RPT_unit1_rpt_high_END    (31)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT2_RPT_UNION
 �ṹ˵��  : UNIT2_RPT �Ĵ����ṹ���塣��ַƫ����:0x0400����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ྶ������С�����������������ۼӣ�ʱ���ϱ�128�������
            ��һ���洢���Ϊf-pich֡ͷΪUnit0_pn0_frame_pos����ɽ�����ڶ����洢���Ϊf-pich֡ͷΪ(Unit0_frame_pos-1/2chip)����ɽ������..��
            Bit[31:16]ΪQ·�����
            Bit[15:0]ΪI·�����
            
            С���������������ۼ��������ۼӣ�ʱ���ϱ�128�������
            ��һ���洢���Ϊf-pich֡ͷΪUnit0_pn0_frame_pos�Ľ�����ڶ����洢���Ϊf-pich֡ͷΪ(Unit0_frame_pos-1/2chip)�Ľ������..��
            Bit[15:0]Ϊ������ۼӽ����
            
            
            С������ʱ��ʹ�õ�ַ0~31���ϱ�32�������
            Bit[31:16]Ϊ��������С��pilot�ŵ�֡ͷ��base_cnt[19:4]��λ�ã�
            Bit[15:0]Ϊ������С���ϱ�����
*****************************************************************************/
typedef union
{
    unsigned long      unit2_rpt_reg;
    struct
    {
        unsigned long  unit2_rpt_low  : 16; /* bit[0-15] : �ྶ������С�����������������ۼӣ�ʱΪI·��ɽ����
                                                           С���������������ۼ��������ۼӣ�ʱΪ������ۼ�����
                                                           С������ʱΪС������ */
        unsigned long  unit2_rpt_high : 16; /* bit[16-31]: �ྶ������С�����������������ۼӣ�ʱΪQ·��ɽ��
                                                           С������ʱΪС��pilot�ŵ�֡ͷ��base_cnt[21:6]�ϵ�λ�ã�1/2chip���ȡ� */
    } reg;
} CBBP_UNIT2_RPT_UNION;
#define CBBP_UNIT2_RPT_unit2_rpt_low_START   (0)
#define CBBP_UNIT2_RPT_unit2_rpt_low_END     (15)
#define CBBP_UNIT2_RPT_unit2_rpt_high_START  (16)
#define CBBP_UNIT2_RPT_unit2_rpt_high_END    (31)


/*****************************************************************************
 �ṹ��    : CBBP_UNIT3_RPT_UNION
 �ṹ˵��  : UNIT3_RPT �Ĵ����ṹ���塣��ַƫ����:0x0600����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ྶ������С�����������������ۼӣ�ʱ���ϱ�128�������
            ��һ���洢���Ϊf-pich֡ͷΪUnit0_pn0_frame_pos����ɽ�����ڶ����洢���Ϊf-pich֡ͷΪ(Unit0_frame_pos-1/2chip)����ɽ������..��
            Bit[31:16]ΪQ·�����
            Bit[15:0]ΪI·�����
            
            С���������������ۼ��������ۼӣ�ʱ���ϱ�128�������
            ��һ���洢���Ϊf-pich֡ͷΪUnit0_pn0_frame_pos�Ľ�����ڶ����洢���Ϊf-pich֡ͷΪ(Unit0_frame_pos-1/2chip)�Ľ������..��
            Bit[15:0]Ϊ������ۼӽ����
            
            
            С������ʱ��ʹ�õ�ַ0~31���ϱ�32�������
            Bit[31:16]Ϊ��������С��pilot�ŵ�֡ͷ��base_cnt[19:4]��λ�ã�
            Bit[15:0]Ϊ������С���ϱ�����
*****************************************************************************/
typedef union
{
    unsigned long      unit3_rpt_reg;
    struct
    {
        unsigned long  unit3_rpt_low  : 16; /* bit[0-15] : �ྶ������С�����������������ۼӣ�ʱΪI·��ɽ����
                                                           С���������������ۼ��������ۼӣ�ʱΪ������ۼ�����
                                                           С������ʱΪС������ */
        unsigned long  unit3_rpt_high : 16; /* bit[16-31]: �ྶ������С�����������������ۼӣ�ʱΪQ·��ɽ��
                                                           С������ʱΪС��pilot�ŵ�֡ͷ��base_cnt[21:6]�ϵ�λ�ã�1/2chip���ȡ� */
    } reg;
} CBBP_UNIT3_RPT_UNION;
#define CBBP_UNIT3_RPT_unit3_rpt_low_START   (0)
#define CBBP_UNIT3_RPT_unit3_rpt_low_END     (15)
#define CBBP_UNIT3_RPT_unit3_rpt_high_START  (16)
#define CBBP_UNIT3_RPT_unit3_rpt_high_END    (31)


/***======================================================================***
                     (10/20) register_define_c_dldec
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : CBBP_DLDEC_ESTB_IND_UNION
 �ṹ˵��  : DLDEC_ESTB_IND �Ĵ����ṹ���塣��ַƫ����:0x008����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_estb_ind_reg;
    struct
    {
        unsigned long  dldec_estb_ind : 1;  /* bit[0]   : ���뽨��ʹ�ܣ������������������������ɺ�����Ϊ1 */
        unsigned long  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_DLDEC_ESTB_IND_UNION;
#define CBBP_DLDEC_ESTB_IND_dldec_estb_ind_START  (0)
#define CBBP_DLDEC_ESTB_IND_dldec_estb_ind_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_DLDEC_DEC_START_UNION
 �ṹ˵��  : DLDEC_DEC_START �Ĵ����ṹ���塣��ַƫ����:0x00C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_dec_start_reg;
    struct
    {
        unsigned long  dldec_dec_start : 1;  /* bit[0]   : ���������źţ�����������������������뽨��ʹ��������ɺ����� */
        unsigned long  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_DLDEC_DEC_START_UNION;
#define CBBP_DLDEC_DEC_START_dldec_dec_start_START  (0)
#define CBBP_DLDEC_DEC_START_dldec_dec_start_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_PACKET_PARA_UNION
 �ṹ˵��  : PACKET_PARA �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      packet_para_reg;
    struct
    {
        unsigned long  dldec_crc_type              : 4;  /* bit[0-3]  : CRC */
        unsigned long  dldec_crc_init_state        : 1;  /* bit[4]    : CRC�ڲ��Ĵ�����ʼ��״̬��
                                                                        0��ȫ0��1��ȫ1�� */
        unsigned long  reserved_0                  : 3;  /* bit[5-7]  : ���� */
        unsigned long  dldec_reserve_bit_exist_ind : 1;  /* bit[8]    : reserve_bitָʾ��1��ʾ����reserve���� */
        unsigned long  reserved_1                  : 3;  /* bit[9-11] : ���� */
        unsigned long  dldec_tail_len              : 4;  /* bit[12-15]: �������ֶ������β�λ���Ѱ����ͬ���ŵ�����ʱ�ò�������Ϊ0�������ŵ��ò�������Ϊ8��6.  */
        unsigned long  dldec_info_len              : 13; /* bit[16-28]: ��Ϣ���س��� */
        unsigned long  reserved_2                  : 3;  /* bit[29-31]: ���� */
    } reg;
} CBBP_PACKET_PARA_UNION;
#define CBBP_PACKET_PARA_dldec_crc_type_START               (0)
#define CBBP_PACKET_PARA_dldec_crc_type_END                 (3)
#define CBBP_PACKET_PARA_dldec_crc_init_state_START         (4)
#define CBBP_PACKET_PARA_dldec_crc_init_state_END           (4)
#define CBBP_PACKET_PARA_dldec_reserve_bit_exist_ind_START  (8)
#define CBBP_PACKET_PARA_dldec_reserve_bit_exist_ind_END    (8)
#define CBBP_PACKET_PARA_dldec_tail_len_START               (12)
#define CBBP_PACKET_PARA_dldec_tail_len_END                 (15)
#define CBBP_PACKET_PARA_dldec_info_len_START               (16)
#define CBBP_PACKET_PARA_dldec_info_len_END                 (28)


/*****************************************************************************
 �ṹ��    : CBBP_DEC_MODE_UNION
 �ṹ˵��  : DEC_MODE �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dec_mode_reg;
    struct
    {
        unsigned long  dldec_code_rate    : 3;  /* bit[0-2]  : �����ʣ�������Ϊ1/Rʱ������ΪR�� */
        unsigned long  reserved_0         : 1;  /* bit[3]    : ���� */
        unsigned long  turbo_mode         : 1;  /* bit[4]    : 1X turbo����ģʽ��0��ʾĬ��ģʽ��1��ʾ����ģʽ�� */
        unsigned long  reserved_1         : 3;  /* bit[5-7]  : ���� */
        unsigned long  dldec_dec_mode     : 3;  /* bit[8-10] : 0: 1X���о�����������������; 1: 1X����TURBO���������������;2: EVDO����������������; 3: 1X �⽻֯���׽��ظ��������ģʽ; 4: ��VTB�������ģʽ; 5: ��TURBO�������ģʽ�� */
        unsigned long  reserved_2         : 1;  /* bit[11]   : ���� */
        unsigned long  dldec_traffic_type : 1;  /* bit[12]   : C����ģʽ��0��ʾ1X��1��ʾEVDO */
        unsigned long  reserved_3         : 3;  /* bit[13-15]: ���� */
        unsigned long  dldec_harq_mode    : 1;  /* bit[16]   : ��Turbo����ģʽ�£�harq�ϲ�ʹ�ܡ�1����ʾ�����ʱΪ�����ݣ������harq�ϲ������򲻽��кϲ���0����ʾ��ֹ�ϲ� */
        unsigned long  reserved_4         : 15; /* bit[17-31]: ���� */
    } reg;
} CBBP_DEC_MODE_UNION;
#define CBBP_DEC_MODE_dldec_code_rate_START     (0)
#define CBBP_DEC_MODE_dldec_code_rate_END       (2)
#define CBBP_DEC_MODE_turbo_mode_START          (4)
#define CBBP_DEC_MODE_turbo_mode_END            (4)
#define CBBP_DEC_MODE_dldec_dec_mode_START      (8)
#define CBBP_DEC_MODE_dldec_dec_mode_END        (10)
#define CBBP_DEC_MODE_dldec_traffic_type_START  (12)
#define CBBP_DEC_MODE_dldec_traffic_type_END    (12)
#define CBBP_DEC_MODE_dldec_harq_mode_START     (16)
#define CBBP_DEC_MODE_dldec_harq_mode_END       (16)


/*****************************************************************************
 �ṹ��    : CBBP_SCR_INIT_STATE_UNION
 �ṹ˵��  : SCR_INIT_STATE �Ĵ����ṹ���塣��ַƫ����:0x018����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      scr_init_state_reg;
    struct
    {
        unsigned long  dldec_scramble_init_state : 17; /* bit[0-16] : �����ʼ��״̬�� */
        unsigned long  reserved                  : 15; /* bit[17-31]: ���� */
    } reg;
} CBBP_SCR_INIT_STATE_UNION;
#define CBBP_SCR_INIT_STATE_dldec_scramble_init_state_START  (0)
#define CBBP_SCR_INIT_STATE_dldec_scramble_init_state_END    (16)


/*****************************************************************************
 �ṹ��    : CBBP_BLOCK_INTL_PARA_UNION
 �ṹ˵��  : BLOCK_INTL_PARA �Ĵ����ṹ���塣��ַƫ����:0x01C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      block_intl_para_reg;
    struct
    {
        unsigned long  dldec_block_intl_j_para : 8;  /* bit[0-7]  : block��֯j������ */
        unsigned long  dldec_block_intl_m_para : 4;  /* bit[8-11] : block��֯m������ */
        unsigned long  reserved                : 20; /* bit[12-31]: ���� */
    } reg;
} CBBP_BLOCK_INTL_PARA_UNION;
#define CBBP_BLOCK_INTL_PARA_dldec_block_intl_j_para_START  (0)
#define CBBP_BLOCK_INTL_PARA_dldec_block_intl_j_para_END    (7)
#define CBBP_BLOCK_INTL_PARA_dldec_block_intl_m_para_START  (8)
#define CBBP_BLOCK_INTL_PARA_dldec_block_intl_m_para_END    (11)


/*****************************************************************************
 �ṹ��    : CBBP_PERMUTING_INTL_PARA_UNION
 �ṹ˵��  : PERMUTING_INTL_PARA �Ĵ����ṹ���塣��ַƫ����:0x020����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      permuting_intl_para_reg;
    struct
    {
        unsigned long  dldec_permuting_intl_k_para : 3;  /* bit[0-2] : permuting��֯k������ */
        unsigned long  reserved_0                  : 1;  /* bit[3]   : ���� */
        unsigned long  dldec_permuting_intl_m_para : 4;  /* bit[4-7] : permuting��֯m������ */
        unsigned long  reserved_1                  : 24; /* bit[8-31]: ���� */
    } reg;
} CBBP_PERMUTING_INTL_PARA_UNION;
#define CBBP_PERMUTING_INTL_PARA_dldec_permuting_intl_k_para_START  (0)
#define CBBP_PERMUTING_INTL_PARA_dldec_permuting_intl_k_para_END    (2)
#define CBBP_PERMUTING_INTL_PARA_dldec_permuting_intl_m_para_START  (4)
#define CBBP_PERMUTING_INTL_PARA_dldec_permuting_intl_m_para_END    (7)


/*****************************************************************************
 �ṹ��    : CBBP_MATRIX_INTL_PARA_UNION
 �ṹ˵��  : MATRIX_INTL_PARA �Ĵ����ṹ���塣��ַƫ����:0x024����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      matrix_intl_para_reg;
    struct
    {
        unsigned long  dldec_matrix_intl_d_para : 4;  /* bit[0-3]  : matrix��֯d���� */
        unsigned long  dldec_matrix_intl_r_para : 3;  /* bit[4-6]  : matrix��֯r���� */
        unsigned long  reserved_0               : 1;  /* bit[7]    : ���� */
        unsigned long  dldec_matrix_intl_m_para : 4;  /* bit[8-11] : matrix��֯m���� */
        unsigned long  dldec_matrix_intl_k_para : 3;  /* bit[12-14]: matrix��֯k���� */
        unsigned long  reserved_1               : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_MATRIX_INTL_PARA_UNION;
#define CBBP_MATRIX_INTL_PARA_dldec_matrix_intl_d_para_START  (0)
#define CBBP_MATRIX_INTL_PARA_dldec_matrix_intl_d_para_END    (3)
#define CBBP_MATRIX_INTL_PARA_dldec_matrix_intl_r_para_START  (4)
#define CBBP_MATRIX_INTL_PARA_dldec_matrix_intl_r_para_END    (6)
#define CBBP_MATRIX_INTL_PARA_dldec_matrix_intl_m_para_START  (8)
#define CBBP_MATRIX_INTL_PARA_dldec_matrix_intl_m_para_END    (11)
#define CBBP_MATRIX_INTL_PARA_dldec_matrix_intl_k_para_START  (12)
#define CBBP_MATRIX_INTL_PARA_dldec_matrix_intl_k_para_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_INTL_PAPA_UNION
 �ṹ˵��  : INTL_PAPA �Ĵ����ṹ���塣��ַƫ����:0x028����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      intl_papa_reg;
    struct
    {
        unsigned long  dldec_block_intl_len : 15; /* bit[0-14] : ��֯���� */
        unsigned long  reserved_0           : 1;  /* bit[15]   : ���� */
        unsigned long  dldec_intl_mode      : 3;  /* bit[16-18]: 0��Matrix Interleave��֯��EVDO ������ʹ�ã���1������Symbol Permuting��֯��EVDOʹ�ã���2������Bit-Reversal Order Interleave��֯��1Xʹ�ã���3������Forward-Backwards Bit-Reversal Order Interleave��֯��FOR_FCH_CCSH_INTERLEAVER_TYPE = 0,1Xʹ�ã���4������Forward-Backwards Bit-Reversal Order Interleave��֯��FOR_FCH_CCSH_INTERLEAVER_TYPE = 1,1Xʹ�ã���5������TYPE1 Block Interleave��֯��1Xʹ�ã�������ģ���ֹ���ã���6������TYPE2 Block Interleave��֯��1Xʹ�ã�������ģ���ֹ���ã���7������Reverse Interleave��EVDOʹ�ã�������ģ���ֹ���ã� */
        unsigned long  reserved_1           : 13; /* bit[19-31]: ���� */
    } reg;
} CBBP_INTL_PAPA_UNION;
#define CBBP_INTL_PAPA_dldec_block_intl_len_START  (0)
#define CBBP_INTL_PAPA_dldec_block_intl_len_END    (14)
#define CBBP_INTL_PAPA_dldec_intl_mode_START       (16)
#define CBBP_INTL_PAPA_dldec_intl_mode_END         (18)


/*****************************************************************************
 �ṹ��    : CBBP_PUNC_PATTERN_UNION
 �ṹ˵��  : PUNC_PATTERN �Ĵ����ṹ���塣��ַƫ����:0x02C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      punc_pattern_reg;
    struct
    {
        unsigned long  dldec_punc_pattern : 25; /* bit[0-24] : ���ͼ������ͱ���Ϊ��һ��״ָ̬ʾ��������ͼ��Ϊ11010ʱ����ʾ��һ�������������ݴ�ף���������ͨ���� */
        unsigned long  reserved           : 7;  /* bit[25-31]: ���� */
    } reg;
} CBBP_PUNC_PATTERN_UNION;
#define CBBP_PUNC_PATTERN_dldec_punc_pattern_START  (0)
#define CBBP_PUNC_PATTERN_dldec_punc_pattern_END    (24)


/*****************************************************************************
 �ṹ��    : CBBP_PUNC_PERIOD_UNION
 �ṹ˵��  : PUNC_PERIOD �Ĵ����ṹ���塣��ַƫ����:0x030����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      punc_period_reg;
    struct
    {
        unsigned long  dldec_punc_period : 5;  /* bit[0-4]  : ������� */
        unsigned long  reserved_0        : 3;  /* bit[5-7]  : ���� */
        unsigned long  dldec_punc_mode   : 2;  /* bit[8-9]  : 0:���ݴ��ͼ�����������Ϣ������ERAMģʽ����Ҫͨ�����ͼ�����������Ϣ�ĳ�����
                                                              1����ERAMģʽ�£����ݹ�ʽ��������Ϣ
                                                              2��ERAMģʽ�£����ݹ�ʽ��������Ϣ */
        unsigned long  reserved_1        : 22; /* bit[10-31]: ���� */
    } reg;
} CBBP_PUNC_PERIOD_UNION;
#define CBBP_PUNC_PERIOD_dldec_punc_period_START  (0)
#define CBBP_PUNC_PERIOD_dldec_punc_period_END    (4)
#define CBBP_PUNC_PERIOD_dldec_punc_mode_START    (8)
#define CBBP_PUNC_PERIOD_dldec_punc_mode_END      (9)


/*****************************************************************************
 �ṹ��    : CBBP_DLDEC_LEN_BEF_PUNC_UNION
 �ṹ˵��  : DLDEC_LEN_BEF_PUNC �Ĵ����ṹ���塣��ַƫ����:0x034����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_len_bef_punc_reg;
    struct
    {
        unsigned long  dldec_len_bef_punc : 15; /* bit[0-14] : ���ǰ���ȣ����ظ��󳤶� */
        unsigned long  reserved           : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_DLDEC_LEN_BEF_PUNC_UNION;
#define CBBP_DLDEC_LEN_BEF_PUNC_dldec_len_bef_punc_START  (0)
#define CBBP_DLDEC_LEN_BEF_PUNC_dldec_len_bef_punc_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_DLDEC_LONG_VTB_PARA_UNION
 �ṹ˵��  : DLDEC_LONG_VTB_PARA �Ĵ����ṹ���塣��ַƫ����:0x038����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_long_vtb_para_reg;
    struct
    {
        unsigned long  dldec_vtb_llr_base_addr : 15; /* bit[0-14] : ����ά�ر�����ǰLLR RAM�Ļ���ַ���ǳ���vtb����ʱ����Ϊ0,�������ʱ����ʵ��LLR��ʼλ�����á����糬������һ�����볤��Ϊ768�����ѵ�����г���Ϊ128����ڶ����������ַ����Ϊ����768-128��*code_rate/4��-1�� */
        unsigned long  reserved                : 16; /* bit[15-30]: ���� */
        unsigned long  dldec_long_vtb_mode     : 1;  /* bit[31]   : ����vtb����ģʽ,1��ʾ����vtb����ģʽ�� */
    } reg;
} CBBP_DLDEC_LONG_VTB_PARA_UNION;
#define CBBP_DLDEC_LONG_VTB_PARA_dldec_vtb_llr_base_addr_START  (0)
#define CBBP_DLDEC_LONG_VTB_PARA_dldec_vtb_llr_base_addr_END    (14)
#define CBBP_DLDEC_LONG_VTB_PARA_dldec_long_vtb_mode_START      (31)
#define CBBP_DLDEC_LONG_VTB_PARA_dldec_long_vtb_mode_END        (31)


/*****************************************************************************
 �ṹ��    : CBBP_VTB_INIT_STATE_UNION
 �ṹ˵��  : VTB_INIT_STATE �Ĵ����ṹ���塣��ַƫ����:0x03C����ֵ:0x80000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      vtb_init_state_reg;
    struct
    {
        unsigned long  dldec_vtb_init_state    : 8;  /* bit[0-7] : ά�رȳ�ʼ��״̬������ǰ���ϱ��Ķ�Ӧʱ϶״̬���á� */
        unsigned long  reserved                : 23; /* bit[8-30]: ���� */
        unsigned long  dldec_vtb_init_state_en : 1;  /* bit[31]  : ά�ر������ʼ��״̬��Чʹ�� */
    } reg;
} CBBP_VTB_INIT_STATE_UNION;
#define CBBP_VTB_INIT_STATE_dldec_vtb_init_state_START     (0)
#define CBBP_VTB_INIT_STATE_dldec_vtb_init_state_END       (7)
#define CBBP_VTB_INIT_STATE_dldec_vtb_init_state_en_START  (31)
#define CBBP_VTB_INIT_STATE_dldec_vtb_init_state_en_END    (31)


/*****************************************************************************
 �ṹ��    : CBBP_EVTB_EN_UNION
 �ṹ˵��  : EVTB_EN �Ĵ����ṹ���塣��ַƫ����:0x040����ֵ:0x00000010�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      evtb_en_reg;
    struct
    {
        unsigned long  evtb_traceback_num : 4;  /* bit[0-3] : ��ǿvtb���ݴ�����֧��1~8����������Ϊ4ʱ����ʾ����һ�������⣬��໹��3�����롣 */
        unsigned long  evtb_en            : 1;  /* bit[4]   : ��ǿvtbʹ�� */
        unsigned long  reserved           : 27; /* bit[5-31]: ���� */
    } reg;
} CBBP_EVTB_EN_UNION;
#define CBBP_EVTB_EN_evtb_traceback_num_START  (0)
#define CBBP_EVTB_EN_evtb_traceback_num_END    (3)
#define CBBP_EVTB_EN_evtb_en_START             (4)
#define CBBP_EVTB_EN_evtb_en_END               (4)


/*****************************************************************************
 �ṹ��    : CBBP_VTB_TB_MODE_UNION
 �ṹ˵��  : VTB_TB_MODE �Ĵ����ṹ���塣��ַƫ����:0x044����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      vtb_tb_mode_reg;
    struct
    {
        unsigned long  dldec_vtb_tb_mode : 1;  /* bit[0]   : vtb����ģʽ��0��ʾ��0״̬��ʼ���ݣ�1��ʾ��������״̬��ʼ���ݡ� */
        unsigned long  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_VTB_TB_MODE_UNION;
#define CBBP_VTB_TB_MODE_dldec_vtb_tb_mode_START  (0)
#define CBBP_VTB_TB_MODE_dldec_vtb_tb_mode_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_VTB_TB_RPT_SLOT_UNION
 �ṹ˵��  : VTB_TB_RPT_SLOT �Ĵ����ṹ���塣��ַƫ����:0x048����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      vtb_tb_rpt_slot_reg;
    struct
    {
        unsigned long  vtb_tb_rpt_slot : 9;  /* bit[0-8] : vtb����״̬�ϱ�ʱ϶���ڳ�����顢Ѱ���ŵ���ͬ���ŵ�ʱ��Ҫ����ѵ�����Ƚ������á� */
        unsigned long  reserved        : 23; /* bit[9-31]: ���� */
    } reg;
} CBBP_VTB_TB_RPT_SLOT_UNION;
#define CBBP_VTB_TB_RPT_SLOT_vtb_tb_rpt_slot_START  (0)
#define CBBP_VTB_TB_RPT_SLOT_vtb_tb_rpt_slot_END    (8)


/*****************************************************************************
 �ṹ��    : CBBP_DLDEC_OVERTIME_CFG_UNION
 �ṹ˵��  : DLDEC_OVERTIME_CFG �Ĵ����ṹ���塣��ַƫ����:0x04C����ֵ:0x00000010�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_overtime_cfg_reg;
    struct
    {
        unsigned long  dldec_overtime_cfg : 6;  /* bit[0-5] : ����ģ�鳬ʱ��������ֵ��0ֵ�������ã�ʵ�ʳ�ʱ����ֵΪdldec_overtime_cfg *8192�����Ƽ�����ֵΪ16 */
        unsigned long  reserved_0         : 2;  /* bit[6-7] : ���� */
        unsigned long  dldec_overtime_en  : 1;  /* bit[8]   : ���볬ʱ����ʹ�� */
        unsigned long  reserved_1         : 23; /* bit[9-31]: ���� */
    } reg;
} CBBP_DLDEC_OVERTIME_CFG_UNION;
#define CBBP_DLDEC_OVERTIME_CFG_dldec_overtime_cfg_START  (0)
#define CBBP_DLDEC_OVERTIME_CFG_dldec_overtime_cfg_END    (5)
#define CBBP_DLDEC_OVERTIME_CFG_dldec_overtime_en_START   (8)
#define CBBP_DLDEC_OVERTIME_CFG_dldec_overtime_en_END     (8)


/*****************************************************************************
 �ṹ��    : CBBP_TURBO_ITER_NUM_C_UNION
 �ṹ˵��  : TURBO_ITER_NUM_C �Ĵ����ṹ���塣��ַƫ����:0x050����ֵ:0x00011009�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      turbo_iter_num_c_reg;
    struct
    {
        unsigned long  c_turbo_min_iter_num : 4;  /* bit[0-3]  : Turbo�������С����������������ó�9����������Ҫ9�δ���Ż�ֹͣ���� */
        unsigned long  reserved_0           : 4;  /* bit[4-7]  : ���� */
        unsigned long  c_turbo_max_iter_num : 5;  /* bit[8-12] : Turbo����������������������ó�16�������16�δ��������Ƿ�������ֹͣ������ */
        unsigned long  reserved_1           : 3;  /* bit[13-15]: ���� */
        unsigned long  c_tc_crcok_stop_en   : 1;  /* bit[16]   : Turbo������CRC��ȷ��ǰֹͣ����ʹ��0����ֹ
                                                                 1��ʹ�� */
        unsigned long  reserved_2           : 15; /* bit[17-31]: ���� */
    } reg;
} CBBP_TURBO_ITER_NUM_C_UNION;
#define CBBP_TURBO_ITER_NUM_C_c_turbo_min_iter_num_START  (0)
#define CBBP_TURBO_ITER_NUM_C_c_turbo_min_iter_num_END    (3)
#define CBBP_TURBO_ITER_NUM_C_c_turbo_max_iter_num_START  (8)
#define CBBP_TURBO_ITER_NUM_C_c_turbo_max_iter_num_END    (12)
#define CBBP_TURBO_ITER_NUM_C_c_tc_crcok_stop_en_START    (16)
#define CBBP_TURBO_ITER_NUM_C_c_tc_crcok_stop_en_END      (16)


/*****************************************************************************
 �ṹ��    : CBBP_TURBO_SCALE_1_4_C_UNION
 �ṹ˵��  : TURBO_SCALE_1_4_C �Ĵ����ṹ���塣��ַƫ����:0x054����ֵ:0x29292323�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      turbo_scale_1_4_c_reg;
    struct
    {
        unsigned long  c_turbo_scale01 : 6;  /* bit[0-5]  : 16��scale���ӣ�ÿ������λ��6bit
                                                            SISO1��sf[i]=sf[2i-2]����1<=i<=8���� sf[i]=sf[14]����9<=i<=16��������iΪ��������
                                                            SISO2�� sf[i]=sf[2i-1]����1<=i<=8���� sf[i]=sf[15]����9<=i<=16��������iΪ�������� */
        unsigned long  reserved_0      : 2;  /* bit[6-7]  : ���� */
        unsigned long  c_turbo_scale02 : 6;  /* bit[8-13] : 16��scale���ӣ�ÿ������λ��6bit
                                                            SISO1��sf[i]=sf[2i-2]����1<=i<=8���� sf[i]=sf[14]����9<=i<=16��������iΪ��������
                                                            SISO2�� sf[i]=sf[2i-1]����1<=i<=8���� sf[i]=sf[15]����9<=i<=16��������iΪ�������� */
        unsigned long  reserved_1      : 2;  /* bit[14-15]: ���� */
        unsigned long  c_turbo_scale03 : 6;  /* bit[16-21]: 16��scale���ӣ�ÿ������λ��6bit
                                                            SISO1��sf[i]=sf[2i-2]����1<=i<=8���� sf[i]=sf[14]����9<=i<=16��������iΪ��������
                                                            SISO2�� sf[i]=sf[2i-1]����1<=i<=8���� sf[i]=sf[15]����9<=i<=16��������iΪ�������� */
        unsigned long  reserved_2      : 2;  /* bit[22-23]: ���� */
        unsigned long  c_turbo_scale04 : 6;  /* bit[24-29]: 16��scale���ӣ�ÿ������λ��6bit
                                                            SISO1��sf[i]=sf[2i-2]����1<=i<=8���� sf[i]=sf[14]����9<=i<=16��������iΪ��������
                                                            SISO2�� sf[i]=sf[2i-1]����1<=i<=8���� sf[i]=sf[15]����9<=i<=16��������iΪ�������� */
        unsigned long  reserved_3      : 2;  /* bit[30-31]: ���� */
    } reg;
} CBBP_TURBO_SCALE_1_4_C_UNION;
#define CBBP_TURBO_SCALE_1_4_C_c_turbo_scale01_START  (0)
#define CBBP_TURBO_SCALE_1_4_C_c_turbo_scale01_END    (5)
#define CBBP_TURBO_SCALE_1_4_C_c_turbo_scale02_START  (8)
#define CBBP_TURBO_SCALE_1_4_C_c_turbo_scale02_END    (13)
#define CBBP_TURBO_SCALE_1_4_C_c_turbo_scale03_START  (16)
#define CBBP_TURBO_SCALE_1_4_C_c_turbo_scale03_END    (21)
#define CBBP_TURBO_SCALE_1_4_C_c_turbo_scale04_START  (24)
#define CBBP_TURBO_SCALE_1_4_C_c_turbo_scale04_END    (29)


/*****************************************************************************
 �ṹ��    : CBBP_TURBO_SCALE_5_8_C_UNION
 �ṹ˵��  : TURBO_SCALE_5_8_C �Ĵ����ṹ���塣��ַƫ����:0x058����ֵ:0x30302C2C�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      turbo_scale_5_8_c_reg;
    struct
    {
        unsigned long  c_turbo_scale05 : 6;  /* bit[0-5]  : 16��scale���ӣ�ÿ������λ��6bit
                                                            SISO1��sf[i]=sf[2i-2]����1<=i<=8���� sf[i]=sf[14]����9<=i<=16��������iΪ��������
                                                            SISO2�� sf[i]=sf[2i-1]����1<=i<=8���� sf[i]=sf[15]����9<=i<=16��������iΪ�������� */
        unsigned long  reserved_0      : 2;  /* bit[6-7]  : ���� */
        unsigned long  c_turbo_scale06 : 6;  /* bit[8-13] : 16��scale���ӣ�ÿ������λ��6bit
                                                            SISO1��sf[i]=sf[2i-2]����1<=i<=8���� sf[i]=sf[14]����9<=i<=16��������iΪ��������
                                                            SISO2�� sf[i]=sf[2i-1]����1<=i<=8���� sf[i]=sf[15]����9<=i<=16��������iΪ�������� */
        unsigned long  reserved_1      : 2;  /* bit[14-15]: ���� */
        unsigned long  c_turbo_scale07 : 6;  /* bit[16-21]: 16��scale���ӣ�ÿ������λ��6bit
                                                            SISO1��sf[i]=sf[2i-2]����1<=i<=8���� sf[i]=sf[14]����9<=i<=16��������iΪ��������
                                                            SISO2�� sf[i]=sf[2i-1]����1<=i<=8���� sf[i]=sf[15]����9<=i<=16��������iΪ�������� */
        unsigned long  reserved_2      : 2;  /* bit[22-23]: ���� */
        unsigned long  c_turbo_scale08 : 6;  /* bit[24-29]: 16��scale���ӣ�ÿ������λ��6bit
                                                            SISO1��sf[i]=sf[2i-2]����1<=i<=8���� sf[i]=sf[14]����9<=i<=16��������iΪ��������
                                                            SISO2�� sf[i]=sf[2i-1]����1<=i<=8���� sf[i]=sf[15]����9<=i<=16��������iΪ�������� */
        unsigned long  reserved_3      : 2;  /* bit[30-31]: ���� */
    } reg;
} CBBP_TURBO_SCALE_5_8_C_UNION;
#define CBBP_TURBO_SCALE_5_8_C_c_turbo_scale05_START  (0)
#define CBBP_TURBO_SCALE_5_8_C_c_turbo_scale05_END    (5)
#define CBBP_TURBO_SCALE_5_8_C_c_turbo_scale06_START  (8)
#define CBBP_TURBO_SCALE_5_8_C_c_turbo_scale06_END    (13)
#define CBBP_TURBO_SCALE_5_8_C_c_turbo_scale07_START  (16)
#define CBBP_TURBO_SCALE_5_8_C_c_turbo_scale07_END    (21)
#define CBBP_TURBO_SCALE_5_8_C_c_turbo_scale08_START  (24)
#define CBBP_TURBO_SCALE_5_8_C_c_turbo_scale08_END    (29)


/*****************************************************************************
 �ṹ��    : CBBP_TURBO_SCALE_9_12_C_UNION
 �ṹ˵��  : TURBO_SCALE_9_12_C �Ĵ����ṹ���塣��ַƫ����:0x05C����ֵ:0x33333030�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      turbo_scale_9_12_c_reg;
    struct
    {
        unsigned long  c_turbo_scale09 : 6;  /* bit[0-5]  : 16��scale���ӣ�ÿ������λ��6bit
                                                            SISO1��sf[i]=sf[2i-2]����1<=i<=8���� sf[i]=sf[14]����9<=i<=16��������iΪ��������
                                                            SISO2�� sf[i]=sf[2i-1]����1<=i<=8���� sf[i]=sf[15]����9<=i<=16��������iΪ�������� */
        unsigned long  reserved_0      : 2;  /* bit[6-7]  : ���� */
        unsigned long  c_turbo_scale10 : 6;  /* bit[8-13] : 16��scale���ӣ�ÿ������λ��6bit
                                                            SISO1��sf[i]=sf[2i-2]����1<=i<=8���� sf[i]=sf[14]����9<=i<=16��������iΪ��������
                                                            SISO2�� sf[i]=sf[2i-1]����1<=i<=8���� sf[i]=sf[15]����9<=i<=16��������iΪ�������� */
        unsigned long  reserved_1      : 2;  /* bit[14-15]: ���� */
        unsigned long  c_turbo_scale11 : 6;  /* bit[16-21]: 16��scale���ӣ�ÿ������λ��6bit
                                                            SISO1��sf[i]=sf[2i-2]����1<=i<=8���� sf[i]=sf[14]����9<=i<=16��������iΪ��������
                                                            SISO2�� sf[i]=sf[2i-1]����1<=i<=8���� sf[i]=sf[15]����9<=i<=16��������iΪ�������� */
        unsigned long  reserved_2      : 2;  /* bit[22-23]: ���� */
        unsigned long  c_turbo_scale12 : 6;  /* bit[24-29]: 16��scale���ӣ�ÿ������λ��6bit
                                                            SISO1��sf[i]=sf[2i-2]����1<=i<=8���� sf[i]=sf[14]����9<=i<=16��������iΪ��������
                                                            SISO2�� sf[i]=sf[2i-1]����1<=i<=8���� sf[i]=sf[15]����9<=i<=16��������iΪ�������� */
        unsigned long  reserved_3      : 2;  /* bit[30-31]: ���� */
    } reg;
} CBBP_TURBO_SCALE_9_12_C_UNION;
#define CBBP_TURBO_SCALE_9_12_C_c_turbo_scale09_START  (0)
#define CBBP_TURBO_SCALE_9_12_C_c_turbo_scale09_END    (5)
#define CBBP_TURBO_SCALE_9_12_C_c_turbo_scale10_START  (8)
#define CBBP_TURBO_SCALE_9_12_C_c_turbo_scale10_END    (13)
#define CBBP_TURBO_SCALE_9_12_C_c_turbo_scale11_START  (16)
#define CBBP_TURBO_SCALE_9_12_C_c_turbo_scale11_END    (21)
#define CBBP_TURBO_SCALE_9_12_C_c_turbo_scale12_START  (24)
#define CBBP_TURBO_SCALE_9_12_C_c_turbo_scale12_END    (29)


/*****************************************************************************
 �ṹ��    : CBBP_TURBO_SCALE_13_16_C_UNION
 �ṹ˵��  : TURBO_SCALE_13_16_C �Ĵ����ṹ���塣��ַƫ����:0x060����ֵ:0x39393636�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      turbo_scale_13_16_c_reg;
    struct
    {
        unsigned long  c_turbo_scale13 : 6;  /* bit[0-5]  : 16��scale���ӣ�ÿ������λ��6bit
                                                            SISO1��sf[i]=sf[2i-2]����1<=i<=8���� sf[i]=sf[14]����9<=i<=16��������iΪ��������
                                                            SISO2�� sf[i]=sf[2i-1]����1<=i<=8���� sf[i]=sf[15]����9<=i<=16��������iΪ�������� */
        unsigned long  reserved_0      : 2;  /* bit[6-7]  : ���� */
        unsigned long  c_turbo_scale14 : 6;  /* bit[8-13] : 16��scale���ӣ�ÿ������λ��6bit
                                                            SISO1��sf[i]=sf[2i-2]����1<=i<=8���� sf[i]=sf[14]����9<=i<=16��������iΪ��������
                                                            SISO2�� sf[i]=sf[2i-1]����1<=i<=8���� sf[i]=sf[15]����9<=i<=16��������iΪ�������� */
        unsigned long  reserved_1      : 2;  /* bit[14-15]: ���� */
        unsigned long  c_turbo_scale15 : 6;  /* bit[16-21]: 16��scale���ӣ�ÿ������λ��6bit
                                                            SISO1��sf[i]=sf[2i-2]����1<=i<=8���� sf[i]=sf[14]����9<=i<=16��������iΪ��������
                                                            SISO2�� sf[i]=sf[2i-1]����1<=i<=8���� sf[i]=sf[15]����9<=i<=16��������iΪ�������� */
        unsigned long  reserved_2      : 2;  /* bit[22-23]: ���� */
        unsigned long  c_turbo_scale16 : 6;  /* bit[24-29]: 16��scale���ӣ�ÿ������λ��6bit
                                                            SISO1��sf[i]=sf[2i-2]����1<=i<=8���� sf[i]=sf[14]����9<=i<=16��������iΪ��������
                                                            SISO2�� sf[i]=sf[2i-1]����1<=i<=8���� sf[i]=sf[15]����9<=i<=16��������iΪ�������� */
        unsigned long  reserved_3      : 2;  /* bit[30-31]: ���� */
    } reg;
} CBBP_TURBO_SCALE_13_16_C_UNION;
#define CBBP_TURBO_SCALE_13_16_C_c_turbo_scale13_START  (0)
#define CBBP_TURBO_SCALE_13_16_C_c_turbo_scale13_END    (5)
#define CBBP_TURBO_SCALE_13_16_C_c_turbo_scale14_START  (8)
#define CBBP_TURBO_SCALE_13_16_C_c_turbo_scale14_END    (13)
#define CBBP_TURBO_SCALE_13_16_C_c_turbo_scale15_START  (16)
#define CBBP_TURBO_SCALE_13_16_C_c_turbo_scale15_END    (21)
#define CBBP_TURBO_SCALE_13_16_C_c_turbo_scale16_START  (24)
#define CBBP_TURBO_SCALE_13_16_C_c_turbo_scale16_END    (29)


/*****************************************************************************
 �ṹ��    : CBBP_HARQ_COMB_SHIFT_IND_UNION
 �ṹ˵��  : HARQ_COMB_SHIFT_IND �Ĵ����ṹ���塣��ַƫ����:0x064����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      harq_comb_shift_ind_reg;
    struct
    {
        unsigned long  harq_comb_shift_ind : 1;  /* bit[0]   : 1����ʾEVDO HARQ�ϲ�����������1λ�ٱ�����6λ������ֱ�ӱ�����6λ�� */
        unsigned long  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_HARQ_COMB_SHIFT_IND_UNION;
#define CBBP_HARQ_COMB_SHIFT_IND_harq_comb_shift_ind_START  (0)
#define CBBP_HARQ_COMB_SHIFT_IND_harq_comb_shift_ind_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_DLDEC_WR_LLR_ORIG_UNION
 �ṹ˵��  : DLDEC_WR_LLR_ORIG �Ĵ����ṹ���塣��ַƫ����:0x068����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_wr_llr_orig_reg;
    struct
    {
        unsigned long  dldec_wr_llr_orig : 2;  /* bit[0-1] : LLR�·���������ָʾ��0����ʾSDR�������·��Ľ����LLR��Ϣ��1����ʾ1Xģʽ����ɽ⽻֯���׽��ظ����LLR��Ϣ��Ҳ��VTB����ǰLLR��Ϣ��2����ʾEVDOģʽ��ĳ�����̵�HARQ���LLR��Ϣ������ϢͬʱҲ������TURBO����ǰ��LLR��Ϣ���� */
        unsigned long  reserved          : 30; /* bit[2-31]: ���� */
    } reg;
} CBBP_DLDEC_WR_LLR_ORIG_UNION;
#define CBBP_DLDEC_WR_LLR_ORIG_dldec_wr_llr_orig_START  (0)
#define CBBP_DLDEC_WR_LLR_ORIG_dldec_wr_llr_orig_END    (1)


/*****************************************************************************
 �ṹ��    : CBBP_DLDEC_WR_WATERLINE_UNION
 �ṹ˵��  : DLDEC_WR_WATERLINE �Ĵ����ṹ���塣��ַƫ����:0x06C����ֵ:0x00000010�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_wr_waterline_reg;
    struct
    {
        unsigned long  dldec_wr_waterline : 5;  /* bit[0-4] : ����ǰLLR�·�ˮ�ߣ�Ҳ���·�LLRʱ��burst���ͣ���֧������Ϊ1����������Ϊ2/4/8/16������16����ʾLLR�·�Ϊburst16����,DMA����λ�����Ϊ64�� */
        unsigned long  reserved           : 27; /* bit[5-31]: ���� */
    } reg;
} CBBP_DLDEC_WR_WATERLINE_UNION;
#define CBBP_DLDEC_WR_WATERLINE_dldec_wr_waterline_START  (0)
#define CBBP_DLDEC_WR_WATERLINE_dldec_wr_waterline_END    (4)


/*****************************************************************************
 �ṹ��    : CBBP_DLDEC_RD_LLR_ORIG_UNION
 �ṹ˵��  : DLDEC_RD_LLR_ORIG �Ĵ����ṹ���塣��ַƫ����:0x070����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_rd_llr_orig_reg;
    struct
    {
        unsigned long  dldec_rd_llr_orig : 2;  /* bit[0-1] : LLR�ϱ���������ָʾ��0����ʾSDR�������ϱ������LLR��Ϣ��1����ʾEVDOģʽ���ϱ�ĳ�����̵�HARQ���LLR��Ϣ������ϢͬʱҲ������TURBO����ǰ��LLR��Ϣ����2����ʾ1Xģʽ����ɽ⽻֯���׽��ظ����LLR��Ϣ�ϱ��� */
        unsigned long  reserved          : 30; /* bit[2-31]: ���� */
    } reg;
} CBBP_DLDEC_RD_LLR_ORIG_UNION;
#define CBBP_DLDEC_RD_LLR_ORIG_dldec_rd_llr_orig_START  (0)
#define CBBP_DLDEC_RD_LLR_ORIG_dldec_rd_llr_orig_END    (1)


/*****************************************************************************
 �ṹ��    : CBBP_DLDEC_RD_WATERLINE_UNION
 �ṹ˵��  : DLDEC_RD_WATERLINE �Ĵ����ṹ���塣��ַƫ����:0x074����ֵ:0x00000010�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_rd_waterline_reg;
    struct
    {
        unsigned long  dldec_rd_waterline : 5;  /* bit[0-4] : LLR�ض�ˮ�ߣ�Ҳ���ض�ʱ����burst���ͣ���֧������Ϊ1����������Ϊ2/4/8/16������16����ʾLLR�ض�Ϊburst16���ͣ�DMA����λ�����Ϊ64�� */
        unsigned long  reserved           : 27; /* bit[5-31]: ���� */
    } reg;
} CBBP_DLDEC_RD_WATERLINE_UNION;
#define CBBP_DLDEC_RD_WATERLINE_dldec_rd_waterline_START  (0)
#define CBBP_DLDEC_RD_WATERLINE_dldec_rd_waterline_END    (4)


/*****************************************************************************
 �ṹ��    : CBBP_LLR_TRANS_FLAG_UNION
 �ṹ˵��  : LLR_TRANS_FLAG �Ĵ����ṹ���塣��ַƫ����:0x07C����ֵ:0x00001010�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      llr_trans_flag_reg;
    struct
    {
        unsigned long  dldec_wr_chnl_full  : 1;  /* bit[0]    : �·�LLRͨ����״̬�ϱ� */
        unsigned long  reserved_0          : 3;  /* bit[1-3]  : ���� */
        unsigned long  dldec_wr_chnl_empty : 1;  /* bit[4]    : �·�LLRͨ����״̬�ϱ� */
        unsigned long  reserved_1          : 3;  /* bit[5-7]  : ���� */
        unsigned long  dldec_rd_chnl_full  : 1;  /* bit[8]    : �ض�LLRͨ����״̬�ϱ� */
        unsigned long  reserved_2          : 3;  /* bit[9-11] : ���� */
        unsigned long  dldec_rd_chnl_empty : 1;  /* bit[12]   : �ض�LLRͨ����״̬�ϱ� */
        unsigned long  reserved_3          : 3;  /* bit[13-15]: ���� */
        unsigned long  dldec_dma_wr_breq   : 1;  /* bit[16]   : DMAд����״̬�ϱ� */
        unsigned long  reserved_4          : 3;  /* bit[17-19]: ���� */
        unsigned long  dldec_dma_rd_breq   : 1;  /* bit[20]   : DMA������״̬�ϱ� */
        unsigned long  reserved_5          : 11; /* bit[21-31]: ���� */
    } reg;
} CBBP_LLR_TRANS_FLAG_UNION;
#define CBBP_LLR_TRANS_FLAG_dldec_wr_chnl_full_START   (0)
#define CBBP_LLR_TRANS_FLAG_dldec_wr_chnl_full_END     (0)
#define CBBP_LLR_TRANS_FLAG_dldec_wr_chnl_empty_START  (4)
#define CBBP_LLR_TRANS_FLAG_dldec_wr_chnl_empty_END    (4)
#define CBBP_LLR_TRANS_FLAG_dldec_rd_chnl_full_START   (8)
#define CBBP_LLR_TRANS_FLAG_dldec_rd_chnl_full_END     (8)
#define CBBP_LLR_TRANS_FLAG_dldec_rd_chnl_empty_START  (12)
#define CBBP_LLR_TRANS_FLAG_dldec_rd_chnl_empty_END    (12)
#define CBBP_LLR_TRANS_FLAG_dldec_dma_wr_breq_START    (16)
#define CBBP_LLR_TRANS_FLAG_dldec_dma_wr_breq_END      (16)
#define CBBP_LLR_TRANS_FLAG_dldec_dma_rd_breq_START    (20)
#define CBBP_LLR_TRANS_FLAG_dldec_dma_rd_breq_END      (20)


/*****************************************************************************
 �ṹ��    : CBBP_BLER_ENABLE_UNION
 �ṹ˵��  : BLER_ENABLE �Ĵ����ṹ���塣��ַƫ����:0x080����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bler_enable_reg;
    struct
    {
        unsigned long  dldec_bler_en : 1;  /* bit[0]   : ����bler��ά�ɲ�ͳ��ʹ�� */
        unsigned long  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_BLER_ENABLE_UNION;
#define CBBP_BLER_ENABLE_dldec_bler_en_START  (0)
#define CBBP_BLER_ENABLE_dldec_bler_en_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_DLDEC_STATE_UNION
 �ṹ˵��  : DLDEC_STATE �Ĵ����ṹ���塣��ַƫ����:0x090����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_state_reg;
    struct
    {
        unsigned long  dldec_state         : 4;  /* bit[0-3] : ����״̬���ϱ� */
        unsigned long  dldec_overtime_flag : 1;  /* bit[4]   : ���볬ʱ��־ */
        unsigned long  reserved_0          : 3;  /* bit[5-7] : ���� */
        unsigned long  c_vtb_busy          : 1;  /* bit[8]   : vtb����æ��־ */
        unsigned long  reserved_1          : 23; /* bit[9-31]: ���� */
    } reg;
} CBBP_DLDEC_STATE_UNION;
#define CBBP_DLDEC_STATE_dldec_state_START          (0)
#define CBBP_DLDEC_STATE_dldec_state_END            (3)
#define CBBP_DLDEC_STATE_dldec_overtime_flag_START  (4)
#define CBBP_DLDEC_STATE_dldec_overtime_flag_END    (4)
#define CBBP_DLDEC_STATE_c_vtb_busy_START           (8)
#define CBBP_DLDEC_STATE_c_vtb_busy_END             (8)


/*****************************************************************************
 �ṹ��    : CBBP_LLR_CLIP_IND_UNION
 �ṹ˵��  : LLR_CLIP_IND �Ĵ����ṹ���塣��ַƫ����:0x094����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      llr_clip_ind_reg;
    struct
    {
        unsigned long  dldec_trans_llr_clip_ind : 1;  /* bit[0]   : LLR�·���������ָʾ��Ϊ1��ʾ8λLLR��������1λ�ٱ�����6λ��Ϊ0��ʾֱ�ӽ�ȡ��6λ�������LLR�״��·�������Ҫ����Ϊ1������ǻض�ǰ�������LLRֵ����Ϊ�Ѿ���6λ�����ٴ��·�ʱ����Ҫ������ʱ����Ϊ0�� */
        unsigned long  reserved                 : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_LLR_CLIP_IND_UNION;
#define CBBP_LLR_CLIP_IND_dldec_trans_llr_clip_ind_START  (0)
#define CBBP_LLR_CLIP_IND_dldec_trans_llr_clip_ind_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_DLDEC_REPEAT_MODE_UNION
 �ṹ˵��  : DLDEC_REPEAT_MODE �Ĵ����ṹ���塣��ַƫ����:0x098����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_repeat_mode_reg;
    struct
    {
        unsigned long  dldec_repeat_mode : 1;  /* bit[0]   : �ظ�ģʽѡ��0��ʾFIX DATA RATE�ظ�ģʽ��1��ʾflexible�ظ�ģʽ�� */
        unsigned long  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_DLDEC_REPEAT_MODE_UNION;
#define CBBP_DLDEC_REPEAT_MODE_dldec_repeat_mode_START  (0)
#define CBBP_DLDEC_REPEAT_MODE_dldec_repeat_mode_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_DLDEC_LLR_RD_START_UNION
 �ṹ˵��  : DLDEC_LLR_RD_START �Ĵ����ṹ���塣��ַƫ����:0x09C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_llr_rd_start_reg;
    struct
    {
        unsigned long  dldec_llr_rd_start : 1;  /* bit[0]   : LLR�ض��������壬ֻ����������ɺ��������״̬ʱ�ſ����á�Ѱ���ŵ���ͬ���ŵ��������жϺ����á� */
        unsigned long  reserved           : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_DLDEC_LLR_RD_START_UNION;
#define CBBP_DLDEC_LLR_RD_START_dldec_llr_rd_start_START  (0)
#define CBBP_DLDEC_LLR_RD_START_dldec_llr_rd_start_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_DLDEC_NEW_BLK_IND_UNION
 �ṹ˵��  : DLDEC_NEW_BLK_IND �Ĵ����ṹ���塣��ַƫ����:0x0A0����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_new_blk_ind_reg;
    struct
    {
        unsigned long  dldec_new_blk_ind : 1;  /* bit[0]   : EVDO�����ָʾ��1��ʾ�����Ϊ�����ݣ�0����ʾ������ */
        unsigned long  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_DLDEC_NEW_BLK_IND_UNION;
#define CBBP_DLDEC_NEW_BLK_IND_dldec_new_blk_ind_START  (0)
#define CBBP_DLDEC_NEW_BLK_IND_dldec_new_blk_ind_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_RPT_MODE_UNION
 �ṹ˵��  : RPT_MODE �Ĵ����ṹ���塣��ַƫ����:0x0A4����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      rpt_mode_reg;
    struct
    {
        unsigned long  dldec_rpt_mode           : 1;  /* bit[0]   : �ϱ�ģʽ��1��ʾС��ģʽ��0��ʾ���ģʽ */
        unsigned long  reserved_0               : 3;  /* bit[1-3] : ���� */
        unsigned long  dldec_reserve_bit_rpt_en : 1;  /* bit[4]   : reserve�����ϱ�ʹ�ܣ�1��ʾ�ϱ�reserve���أ�0��ʾ���ϱ� */
        unsigned long  reserved_1               : 27; /* bit[5-31]: ���� */
    } reg;
} CBBP_RPT_MODE_UNION;
#define CBBP_RPT_MODE_dldec_rpt_mode_START            (0)
#define CBBP_RPT_MODE_dldec_rpt_mode_END              (0)
#define CBBP_RPT_MODE_dldec_reserve_bit_rpt_en_START  (4)
#define CBBP_RPT_MODE_dldec_reserve_bit_rpt_en_END    (4)


/*****************************************************************************
 �ṹ��    : CBBP_DLDEC_WR_LENGTH_UNION
 �ṹ˵��  : DLDEC_WR_LENGTH �Ĵ����ṹ���塣��ַƫ����:0x0AC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_wr_length_reg;
    struct
    {
        unsigned long  dldec_wr_length : 13; /* bit[0-12] : ����·�LLR������Ϊʵ��LLR��������4��������ȡ���� */
        unsigned long  reserved        : 19; /* bit[13-31]: ���� */
    } reg;
} CBBP_DLDEC_WR_LENGTH_UNION;
#define CBBP_DLDEC_WR_LENGTH_dldec_wr_length_START  (0)
#define CBBP_DLDEC_WR_LENGTH_dldec_wr_length_END    (12)


/*****************************************************************************
 �ṹ��    : CBBP_DLDEC_RD_LENGTH_UNION
 �ṹ˵��  : DLDEC_RD_LENGTH �Ĵ����ṹ���塣��ַƫ����:0x0B0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_rd_length_reg;
    struct
    {
        unsigned long  dldec_rd_length : 13; /* bit[0-12] : ����ض�LLR������Ϊʵ��LLR��������4��������ȡ���� */
        unsigned long  reserved        : 19; /* bit[13-31]: ���� */
    } reg;
} CBBP_DLDEC_RD_LENGTH_UNION;
#define CBBP_DLDEC_RD_LENGTH_dldec_rd_length_START  (0)
#define CBBP_DLDEC_RD_LENGTH_dldec_rd_length_END    (12)


/*****************************************************************************
 �ṹ��    : CBBP_CRC_RPT_UNION
 �ṹ˵��  : CRC_RPT �Ĵ����ṹ���塣��ַƫ����:0x0B4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      crc_rpt_reg;
    struct
    {
        unsigned long  dldec_crc_bit_rpt : 24; /* bit[0-23] : CRCУ������ϱ� */
        unsigned long  reserved          : 7;  /* bit[24-30]: ���� */
        unsigned long  dldec_crc_result  : 1;  /* bit[31]   : CRCУ�����ϱ� */
    } reg;
} CBBP_CRC_RPT_UNION;
#define CBBP_CRC_RPT_dldec_crc_bit_rpt_START  (0)
#define CBBP_CRC_RPT_dldec_crc_bit_rpt_END    (23)
#define CBBP_CRC_RPT_dldec_crc_result_START   (31)
#define CBBP_CRC_RPT_dldec_crc_result_END     (31)


/*****************************************************************************
 �ṹ��    : CBBP_LLR_READY_UNION
 �ṹ˵��  : LLR_READY �Ĵ����ṹ���塣��ַƫ����:0x0B8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      llr_ready_reg;
    struct
    {
        unsigned long  dldec_llr_wr_ready : 1;  /* bit[0]   : ����ģʽʱ�������ͨ��DMA��ֱ��ͨ�������·�LLR��ֵ��1��ʾ��һ��BURST��LLR�����·���0����ʾLLR�����·��� */
        unsigned long  reserved_0         : 3;  /* bit[1-3] : ���� */
        unsigned long  dldec_llr_rd_ready : 1;  /* bit[4]   : ����ģʽʱ�������ͨ��DMA��ֱ��ͨ�����߶�ȡLLR��ֵ��1��ʾ��һ��BURST��LLR���Զ�ȡ��0����ʾû��LLR�ɶ�ȡ�� */
        unsigned long  reserved_1         : 27; /* bit[5-31]: ���� */
    } reg;
} CBBP_LLR_READY_UNION;
#define CBBP_LLR_READY_dldec_llr_wr_ready_START  (0)
#define CBBP_LLR_READY_dldec_llr_wr_ready_END    (0)
#define CBBP_LLR_READY_dldec_llr_rd_ready_START  (4)
#define CBBP_LLR_READY_dldec_llr_rd_ready_END    (4)


/*****************************************************************************
 �ṹ��    : CBBP_LLR_READY_CLR_UNION
 �ṹ˵��  : LLR_READY_CLR �Ĵ����ṹ���塣��ַƫ����:0x0BC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      llr_ready_clr_reg;
    struct
    {
        unsigned long  dldec_llr_wr_ready_clr : 1;  /* bit[0]   : ����ģʽʱ������ɲ�ͨ��DMA��ֱ��ͨ�������·�LLR��ֵ�����·���һ��burst����ʱ�������������壬��dldec_llr_wr_ready_clr��0 */
        unsigned long  reserved_0             : 3;  /* bit[1-3] : ���� */
        unsigned long  dldec_llr_rd_ready_clr : 1;  /* bit[4]   : ����ģʽʱ������ɲ�ͨ��DMA��ֱ��ͨ�����߶�ȡLLR��ֵ��������һ��burst����ʱ������������,��dldec_llr_rd_ready��0 */
        unsigned long  reserved_1             : 27; /* bit[5-31]: ���� */
    } reg;
} CBBP_LLR_READY_CLR_UNION;
#define CBBP_LLR_READY_CLR_dldec_llr_wr_ready_clr_START  (0)
#define CBBP_LLR_READY_CLR_dldec_llr_wr_ready_clr_END    (0)
#define CBBP_LLR_READY_CLR_dldec_llr_rd_ready_clr_START  (4)
#define CBBP_LLR_READY_CLR_dldec_llr_rd_ready_clr_END    (4)


/*****************************************************************************
 �ṹ��    : CBBP_C_VTB_ST_RPT_UNION
 �ṹ˵��  : C_VTB_ST_RPT �Ĵ����ṹ���塣��ַƫ����:0x0C0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      c_vtb_st_rpt_reg;
    struct
    {
        unsigned long  c_vtb_st_rpt : 8;  /* bit[0-7] : vtb״̬�ϱ���������һ��vtb����״̬������ʼ�����ڱ��������жϺ��´���������ǰ��Ч�� */
        unsigned long  reserved     : 24; /* bit[8-31]: ���� */
    } reg;
} CBBP_C_VTB_ST_RPT_UNION;
#define CBBP_C_VTB_ST_RPT_c_vtb_st_rpt_START  (0)
#define CBBP_C_VTB_ST_RPT_c_vtb_st_rpt_END    (7)


/*****************************************************************************
 �ṹ��    : CBBP_C2TUBO_BASE_ADDR_UNION
 �ṹ˵��  : C2TUBO_BASE_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0C4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      c2tubo_base_addr_reg;
    struct
    {
        unsigned long  c2tubo_base_addr : 12; /* bit[0-11] : ä����HARQ�ش�ʱturbo����ǰ���ݵ�ƫ�Ƶ�ַ��HARQ�ش�ʱ�����ݽ��̺ż��㣬����0����ʱ���õ�ַ����Ϊ0������n��������Ϊ641*n��֧�����4�����̡�ä���ʱ������ʵ��LLR���ݳ��ȼ��㡣 */
        unsigned long  reserved         : 20; /* bit[12-31]: ���� */
    } reg;
} CBBP_C2TUBO_BASE_ADDR_UNION;
#define CBBP_C2TUBO_BASE_ADDR_c2tubo_base_addr_START  (0)
#define CBBP_C2TUBO_BASE_ADDR_c2tubo_base_addr_END    (11)


/*****************************************************************************
 �ṹ��    : CBBP_DLDEC_CKG_BYPASS_UNION
 �ṹ˵��  : DLDEC_CKG_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x0C8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_ckg_bypass_reg;
    struct
    {
        unsigned long  dldec_ckg_bypass : 9;  /* bit[0-8] : ʱ���ſ���·ʹ�� */
        unsigned long  reserved         : 23; /* bit[9-31]: ���� */
    } reg;
} CBBP_DLDEC_CKG_BYPASS_UNION;
#define CBBP_DLDEC_CKG_BYPASS_dldec_ckg_bypass_START  (0)
#define CBBP_DLDEC_CKG_BYPASS_dldec_ckg_bypass_END    (8)


/*****************************************************************************
 �ṹ��    : CBBP_DLDEC_BER_EN_UNION
 �ṹ˵��  : DLDEC_BER_EN �Ĵ����ṹ���塣��ַƫ����:0x0CC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_ber_en_reg;
    struct
    {
        unsigned long  dldec_ber_en : 1;  /* bit[0]   : BERͳ��ʹ�� */
        unsigned long  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_DLDEC_BER_EN_UNION;
#define CBBP_DLDEC_BER_EN_dldec_ber_en_START  (0)
#define CBBP_DLDEC_BER_EN_dldec_ber_en_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_DLDEC_RFPUN_EN_UNION
 �ṹ˵��  : DLDEC_RFPUN_EN �Ĵ����ṹ���塣��ַƫ����:0x0D0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_rfpun_en_reg;
    struct
    {
        unsigned long  dldec_rfpun_en : 1;  /* bit[0]   : ���ظ���Ϊ1ʱ��berͳ����Ҫ������λ�ã���ʱ�����ź���1��������0�� */
        unsigned long  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_DLDEC_RFPUN_EN_UNION;
#define CBBP_DLDEC_RFPUN_EN_dldec_rfpun_en_START  (0)
#define CBBP_DLDEC_RFPUN_EN_dldec_rfpun_en_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_C_BLID_CM0_UNION
 �ṹ˵��  : C_BLID_CM0 �Ĵ����ṹ���塣��ַƫ����:0x0D4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      c_blid_cm0_reg;
    struct
    {
        unsigned long  c_blid_cm0 : 13; /* bit[0-12] : ���ʱ���Ҵ�·������ֵ����״̬����ֵ֮�� */
        unsigned long  reserved   : 19; /* bit[13-31]: ���� */
    } reg;
} CBBP_C_BLID_CM0_UNION;
#define CBBP_C_BLID_CM0_c_blid_cm0_START  (0)
#define CBBP_C_BLID_CM0_c_blid_cm0_END    (12)


/*****************************************************************************
 �ṹ��    : CBBP_C_BLID_CM1_UNION
 �ṹ˵��  : C_BLID_CM1 �Ĵ����ṹ���塣��ַƫ����:0x0D8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      c_blid_cm1_reg;
    struct
    {
        unsigned long  c_blid_cm1 : 13; /* bit[0-12] : ���ʱ���Ҵ�·������ֵ�����·������ֵ֮�� */
        unsigned long  reserved   : 19; /* bit[13-31]: ���� */
    } reg;
} CBBP_C_BLID_CM1_UNION;
#define CBBP_C_BLID_CM1_c_blid_cm1_START  (0)
#define CBBP_C_BLID_CM1_c_blid_cm1_END    (12)


/*****************************************************************************
 �ṹ��    : CBBP_C_BLID_CM2_UNION
 �ṹ˵��  : C_BLID_CM2 �Ĵ����ṹ���塣��ַƫ����:0x0DC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      c_blid_cm2_reg;
    struct
    {
        unsigned long  c_blid_cm2 : 13; /* bit[0-12] : Cģä�������ʱ�̴���·������ֵ�ϱ� */
        unsigned long  reserved   : 19; /* bit[13-31]: ���� */
    } reg;
} CBBP_C_BLID_CM2_UNION;
#define CBBP_C_BLID_CM2_c_blid_cm2_START  (0)
#define CBBP_C_BLID_CM2_c_blid_cm2_END    (12)


/*****************************************************************************
 �ṹ��    : CBBP_DLDEC_BER_UNION
 �ṹ˵��  : DLDEC_BER �Ĵ����ṹ���塣��ַƫ����:0x0E0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_ber_reg;
    struct
    {
        unsigned long  dldec_ber : 15; /* bit[0-14] : ä���BER����bit��ͳ�ƽ�� */
        unsigned long  reserved  : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_DLDEC_BER_UNION;
#define CBBP_DLDEC_BER_dldec_ber_START  (0)
#define CBBP_DLDEC_BER_dldec_ber_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_DLDEC_TOTAL_BERBIT_UNION
 �ṹ˵��  : DLDEC_TOTAL_BERBIT �Ĵ����ṹ���塣��ַƫ����:0x0E4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_total_berbit_reg;
    struct
    {
        unsigned long  dldec_total_berbit : 15; /* bit[0-14] : ä�������ͳ��BER���ܱ����� */
        unsigned long  reserved           : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_DLDEC_TOTAL_BERBIT_UNION;
#define CBBP_DLDEC_TOTAL_BERBIT_dldec_total_berbit_START  (0)
#define CBBP_DLDEC_TOTAL_BERBIT_dldec_total_berbit_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_BIT_ORDER_REVERSE_UNION
 �ṹ˵��  : BIT_ORDER_REVERSE �Ĵ����ṹ���塣��ַƫ����:0x0E8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      bit_order_reverse_reg;
    struct
    {
        unsigned long  bit_order_reverse : 1;  /* bit[0]   : byte�ڴ�С��ָʾ��0��ʾС��ģʽ����byte�����λ�ŵ�λ���ݡ�1��ʾ���ģʽ��byte�����λ�����λ���ݡ� */
        unsigned long  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_BIT_ORDER_REVERSE_UNION;
#define CBBP_BIT_ORDER_REVERSE_bit_order_reverse_START  (0)
#define CBBP_BIT_ORDER_REVERSE_bit_order_reverse_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_TURBO_ITER_NUM_W_SDR_UNION
 �ṹ˵��  : TURBO_ITER_NUM_W_SDR �Ĵ����ṹ���塣��ַƫ����:0x0EC����ֵ:0x00000011�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      turbo_iter_num_w_sdr_reg;
    struct
    {
        unsigned long  wsdr_turbo_iter_over_en    : 1;  /* bit[0]   : Wģ��Turbo��������ǰֹͣ����ʹ��0����ֹ
                                                                      1��ʹ�� */
        unsigned long  reserved_0                 : 3;  /* bit[1-3] : ���� */
        unsigned long  wsdr_conv_judge_enhance_en : 1;  /* bit[4]   : Wģ��turbo�����������жϷ������л����أ�Ĭ�ϴ�
                                                                      0���Ƚ��������εĵ�����������һ������Ϊ������
                                                                      1���Ƚ��������εĵ�����������һ������Ϊ������ */
        unsigned long  reserved_1                 : 27; /* bit[5-31]: ���� */
    } reg;
} CBBP_TURBO_ITER_NUM_W_SDR_UNION;
#define CBBP_TURBO_ITER_NUM_W_SDR_wsdr_turbo_iter_over_en_START     (0)
#define CBBP_TURBO_ITER_NUM_W_SDR_wsdr_turbo_iter_over_en_END       (0)
#define CBBP_TURBO_ITER_NUM_W_SDR_wsdr_conv_judge_enhance_en_START  (4)
#define CBBP_TURBO_ITER_NUM_W_SDR_wsdr_conv_judge_enhance_en_END    (4)


/*****************************************************************************
 �ṹ��    : CBBP_BLIND_DETECT_IND_UNION
 �ṹ˵��  : BLIND_DETECT_IND �Ĵ����ṹ���塣��ַƫ����:0x0F0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      blind_detect_ind_reg;
    struct
    {
        unsigned long  blind_detect_ind : 1;  /* bit[0]   : 1X��EVDOʱä���ָʾ��1��ʾ��ǰ�����Ҫ����ä������� */
        unsigned long  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_BLIND_DETECT_IND_UNION;
#define CBBP_BLIND_DETECT_IND_blind_detect_ind_START  (0)
#define CBBP_BLIND_DETECT_IND_blind_detect_ind_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_CPU_ACCESS_LLR_MODE_UNION
 �ṹ˵��  : CPU_ACCESS_LLR_MODE �Ĵ����ṹ���塣��ַƫ����:0x0F8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      cpu_access_llr_mode_reg;
    struct
    {
        unsigned long  cpu_access_llr_rd_mode : 1;  /* bit[0]   : CPUֱ�Ӷ�ȡLLRģʽ����ʱ��ͨ��DMA��ȡ���ݣ�BBP DMA�������ߡ� */
        unsigned long  reserved_0             : 3;  /* bit[1-3] : ���� */
        unsigned long  cpu_access_llr_wr_mode : 1;  /* bit[4]   : CPUֱ���·�LLRģʽ����ʱ��ͨ��DMA�·����ݣ�BBP DMA�������ߡ� */
        unsigned long  reserved_1             : 27; /* bit[5-31]: ���� */
    } reg;
} CBBP_CPU_ACCESS_LLR_MODE_UNION;
#define CBBP_CPU_ACCESS_LLR_MODE_cpu_access_llr_rd_mode_START  (0)
#define CBBP_CPU_ACCESS_LLR_MODE_cpu_access_llr_rd_mode_END    (0)
#define CBBP_CPU_ACCESS_LLR_MODE_cpu_access_llr_wr_mode_START  (4)
#define CBBP_CPU_ACCESS_LLR_MODE_cpu_access_llr_wr_mode_END    (4)


/*****************************************************************************
 �ṹ��    : CBBP_LLR_TRANS_MODE_UNION
 �ṹ˵��  : LLR_TRANS_MODE �Ĵ����ṹ���塣��ַƫ����:0x0FC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      llr_trans_mode_reg;
    struct
    {
        unsigned long  llr_trans_mode : 2;  /* bit[0-1] : LLR�����·�ģʽָʾ:0����ʾDMA burst�·�ģʽ��1����ʾDMA FLASHģʽ��2����ʾBBPMSTģʽ��
                                                          DMA FLASHģʽ��BBPMSTģʽ��֧�ִ�TURBO LLR�����·��� */
        unsigned long  reserved       : 30; /* bit[2-31]: ���� */
    } reg;
} CBBP_LLR_TRANS_MODE_UNION;
#define CBBP_LLR_TRANS_MODE_llr_trans_mode_START  (0)
#define CBBP_LLR_TRANS_MODE_llr_trans_mode_END    (1)


/***======================================================================***
                     (11/20) register_define_c_dldec_mem
 ***======================================================================***/
/***======================================================================***
                     (12/20) register_define_c_ulcode
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : CBBP_ULCODE_EN_UNION
 �ṹ˵��  : ULCODE_EN �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_en_reg;
    struct
    {
        unsigned long  cpu_ulcode_en : 1;  /* bit[0]   : ���б���ģ��ʹ�ܣ��������������б������������ɺ�����Ϊ1�� */
        unsigned long  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_ULCODE_EN_UNION;
#define CBBP_ULCODE_EN_cpu_ulcode_en_START  (0)
#define CBBP_ULCODE_EN_cpu_ulcode_en_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_ULCODE_START_UNION
 �ṹ˵��  : ULCODE_START �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_start_reg;
    struct
    {
        unsigned long  cpu_ulcode_start : 1;  /* bit[0]   : ���б��������źţ��������������б�����������б��뽨��ʹ��������ɺ����� */
        unsigned long  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_ULCODE_START_UNION;
#define CBBP_ULCODE_START_cpu_ulcode_start_START  (0)
#define CBBP_ULCODE_START_cpu_ulcode_start_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_ULCODE_BIT_MODE_UNION
 �ṹ˵��  : ULCODE_BIT_MODE �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_bit_mode_reg;
    struct
    {
        unsigned long  cpu_ulcode_bit_mode          : 1;  /* bit[0]    : ���������·���ʽ�ͱ���������ϱ���ʽ��1����ʾС��ģʽ��Ĭ��ģʽ����0����ʾ���ģʽ��Ĭ��ֵ��1�� */
        unsigned long  reserved_0                   : 15; /* bit[1-15] : ���� */
        unsigned long  cpu_ulcode_bit_order_reverse : 1;  /* bit[16]   : ���������·�С�˱��������ʽ��1����ʾС�˱�������ģʽ��Ч��0����ʾС�˱�������ģʽ��Ч��Ĭ��ֵ��0��
                                                                         ���������·�С�˱�������ģʽ��С��ģʽ����ͬʱ��Ч�������öԱ���������ϱ���ʽ��Ӱ�졣 */
        unsigned long  reserved_1                   : 15; /* bit[17-31]: ���� */
    } reg;
} CBBP_ULCODE_BIT_MODE_UNION;
#define CBBP_ULCODE_BIT_MODE_cpu_ulcode_bit_mode_START           (0)
#define CBBP_ULCODE_BIT_MODE_cpu_ulcode_bit_mode_END             (0)
#define CBBP_ULCODE_BIT_MODE_cpu_ulcode_bit_order_reverse_START  (16)
#define CBBP_ULCODE_BIT_MODE_cpu_ulcode_bit_order_reverse_END    (16)


/*****************************************************************************
 �ṹ��    : CBBP_ULCODE_RESERVE_BIT_UNION
 �ṹ˵��  : ULCODE_RESERVE_BIT �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_reserve_bit_reg;
    struct
    {
        unsigned long  cpu_ulcode_reserve_bit_exist_ind : 1;  /* bit[0]    : 1Xģʽ��Reverse bit���ʹ�ܿ��أ�EVDOģʽ�¸ò�������Ϊ0�� */
        unsigned long  reserved_0                       : 15; /* bit[1-15] : ���� */
        unsigned long  cpu_ulcode_reserve_bit_value     : 1;  /* bit[16]   : Reverse bit��ȡֵ��ȡֵ0��1�� */
        unsigned long  reserved_1                       : 15; /* bit[17-31]: ���� */
    } reg;
} CBBP_ULCODE_RESERVE_BIT_UNION;
#define CBBP_ULCODE_RESERVE_BIT_cpu_ulcode_reserve_bit_exist_ind_START  (0)
#define CBBP_ULCODE_RESERVE_BIT_cpu_ulcode_reserve_bit_exist_ind_END    (0)
#define CBBP_ULCODE_RESERVE_BIT_cpu_ulcode_reserve_bit_value_START      (16)
#define CBBP_ULCODE_RESERVE_BIT_cpu_ulcode_reserve_bit_value_END        (16)


/*****************************************************************************
 �ṹ��    : CBBP_ULCODE_TRAFFIC_TYPE_UNION
 �ṹ˵��  : ULCODE_TRAFFIC_TYPE �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_traffic_type_reg;
    struct
    {
        unsigned long  cpu_ulcode_traffic_type : 1;  /* bit[0]   : ͨ��ģʽ����ָʾ��1��EVDO��0:1X��Ĭ��ֵ��0�� */
        unsigned long  reserved                : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_ULCODE_TRAFFIC_TYPE_UNION;
#define CBBP_ULCODE_TRAFFIC_TYPE_cpu_ulcode_traffic_type_START  (0)
#define CBBP_ULCODE_TRAFFIC_TYPE_cpu_ulcode_traffic_type_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_ULCODE_CODER_PARA_UNION
 �ṹ˵��  : ULCODE_CODER_PARA �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_coder_para_reg;
    struct
    {
        unsigned long  cpu_ulcode_coder_type : 1;  /* bit[0]    : ����������ָʾ��1��TURBO��0:VTB��
                                                                  Ĭ��ֵ��0�� */
        unsigned long  reserved_0            : 15; /* bit[1-15] : ���� */
        unsigned long  cpu_ulcode_coder_rate : 3;  /* bit[16-18]: ���б����������ʣ�
                                                                  2��1/2��
                                                                  3��1/3��
                                                                  4��1/4��
                                                                  5��1/5�������������1/5���� */
        unsigned long  reserved_1            : 13; /* bit[19-31]: ���� */
    } reg;
} CBBP_ULCODE_CODER_PARA_UNION;
#define CBBP_ULCODE_CODER_PARA_cpu_ulcode_coder_type_START  (0)
#define CBBP_ULCODE_CODER_PARA_cpu_ulcode_coder_type_END    (0)
#define CBBP_ULCODE_CODER_PARA_cpu_ulcode_coder_rate_START  (16)
#define CBBP_ULCODE_CODER_PARA_cpu_ulcode_coder_rate_END    (18)


/*****************************************************************************
 �ṹ��    : CBBP_ULCODE_LEN_PARA1_UNION
 �ṹ˵��  : ULCODE_LEN_PARA1 �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_len_para1_reg;
    struct
    {
        unsigned long  cpu_ulcode_info_len : 14; /* bit[0-13] : ��Ϣλ���ȣ�
                                                                ��������²���CRC��Reverse bit��TAIL bit ���ȣ�TURBO�����²�����00����CRC��Reverse bit��TAIL bit ���ȡ� */
        unsigned long  reserved            : 18; /* bit[14-31]: ���� */
    } reg;
} CBBP_ULCODE_LEN_PARA1_UNION;
#define CBBP_ULCODE_LEN_PARA1_cpu_ulcode_info_len_START  (0)
#define CBBP_ULCODE_LEN_PARA1_cpu_ulcode_info_len_END    (13)


/*****************************************************************************
 �ṹ��    : CBBP_ULCODE_CRC_PARA_UNION
 �ṹ˵��  : ULCODE_CRC_PARA �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_crc_para_reg;
    struct
    {
        unsigned long  cpu_ulcode_crc_type       : 4;  /* bit[0-3]  : CRCУ�����ͣ�
                                                                      0:CRC-0��
                                                                      1:CRC-16-1��
                                                                      2:CRC-12��
                                                                      3:CRC-10��
                                                                      4:CRC-8��
                                                                      5:CRC-6-1��
                                                                      6:CRC-6-2��
                                                                      7:CRC-24��
                                                                      8:CRC-16-2��
                                                                      Ĭ��ֵ��0�� */
        unsigned long  reserved_0                : 12; /* bit[4-15] : ���� */
        unsigned long  cpu_ulcode_crc_init_state : 1;  /* bit[16]   : CRC�Ĵ�����ʼ��ֵ��1��ȫ1��0��ȫ0��
                                                                      Ĭ��ֵ��0�� */
        unsigned long  reserved_1                : 15; /* bit[17-31]: ���� */
    } reg;
} CBBP_ULCODE_CRC_PARA_UNION;
#define CBBP_ULCODE_CRC_PARA_cpu_ulcode_crc_type_START        (0)
#define CBBP_ULCODE_CRC_PARA_cpu_ulcode_crc_type_END          (3)
#define CBBP_ULCODE_CRC_PARA_cpu_ulcode_crc_init_state_START  (16)
#define CBBP_ULCODE_CRC_PARA_cpu_ulcode_crc_init_state_END    (16)


/*****************************************************************************
 �ṹ��    : CBBP_ULCODE_SCR_INIT_UNION
 �ṹ˵��  : ULCODE_SCR_INIT �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_scr_init_reg;
    struct
    {
        unsigned long  cpu_ulcode_scramble_init_state : 17; /* bit[0-16] : ������������ࣻ
                                                                           SDR����������EVDOЭ�鶨����������������ø����б���ģ�顣
                                                                           1X�¹̶�����Ϊȫ0�� */
        unsigned long  reserved                       : 15; /* bit[17-31]: ���� */
    } reg;
} CBBP_ULCODE_SCR_INIT_UNION;
#define CBBP_ULCODE_SCR_INIT_cpu_ulcode_scramble_init_state_START  (0)
#define CBBP_ULCODE_SCR_INIT_cpu_ulcode_scramble_init_state_END    (16)


/*****************************************************************************
 �ṹ��    : CBBP_ULCODE_INTL_MODE_UNION
 �ṹ˵��  : ULCODE_INTL_MODE �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_intl_mode_reg;
    struct
    {
        unsigned long  cpu_ulcode_intl_mode : 3;  /* bit[0-2] : ��֯������ģʽ��
                                                                0�� Matrix Interleave��֯��
                                                                1�� Symbol Permuting��֯��
                                                                2������TYPE1 Block Interleave��֯��
                                                                3������TYPE2 Block Interleave��֯��
                                                                4������TYPE3 Block Interleave��֯��
                                                                5������TYPE1 Block Interleave��֯��
                                                                6������TYPE2 Block Interleave��֯��
                                                                7������Reverse Interleave�� */
        unsigned long  reserved             : 29; /* bit[3-31]: ���� */
    } reg;
} CBBP_ULCODE_INTL_MODE_UNION;
#define CBBP_ULCODE_INTL_MODE_cpu_ulcode_intl_mode_START  (0)
#define CBBP_ULCODE_INTL_MODE_cpu_ulcode_intl_mode_END    (2)


/*****************************************************************************
 �ṹ��    : CBBP_ULCODE_MATRIX_PARA_UNION
 �ṹ˵��  : ULCODE_MATRIX_PARA �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_matrix_para_reg;
    struct
    {
        unsigned long  cpu_ulcode_matrix_intl_k_para : 3;  /* bit[0-2]  : ����Matrix Interleave��֯������EVDOʹ�ã�K������ */
        unsigned long  reserved_0                    : 5;  /* bit[3-7]  : ���� */
        unsigned long  cpu_ulcode_matrix_intl_m_para : 4;  /* bit[8-11] : ����Matrix Interleave��֯������EVDOʹ�ã�M������V0/V0`��V1/V1`Ӳ��ʹ��ʱ���м�1���� */
        unsigned long  reserved_1                    : 4;  /* bit[12-15]: ���� */
        unsigned long  cpu_ulcode_matrix_intl_r_para : 3;  /* bit[16-18]: ����Matrix Interleave��֯������EVDOʹ�ã�R������ */
        unsigned long  reserved_2                    : 5;  /* bit[19-23]: ���� */
        unsigned long  cpu_ulcode_matrix_intl_d_para : 4;  /* bit[24-27]: ����Matrix Interleave��֯������EVDOʹ�ã�D��������������������󣩡� */
        unsigned long  reserved_3                    : 4;  /* bit[28-31]: ���� */
    } reg;
} CBBP_ULCODE_MATRIX_PARA_UNION;
#define CBBP_ULCODE_MATRIX_PARA_cpu_ulcode_matrix_intl_k_para_START  (0)
#define CBBP_ULCODE_MATRIX_PARA_cpu_ulcode_matrix_intl_k_para_END    (2)
#define CBBP_ULCODE_MATRIX_PARA_cpu_ulcode_matrix_intl_m_para_START  (8)
#define CBBP_ULCODE_MATRIX_PARA_cpu_ulcode_matrix_intl_m_para_END    (11)
#define CBBP_ULCODE_MATRIX_PARA_cpu_ulcode_matrix_intl_r_para_START  (16)
#define CBBP_ULCODE_MATRIX_PARA_cpu_ulcode_matrix_intl_r_para_END    (18)
#define CBBP_ULCODE_MATRIX_PARA_cpu_ulcode_matrix_intl_d_para_START  (24)
#define CBBP_ULCODE_MATRIX_PARA_cpu_ulcode_matrix_intl_d_para_END    (27)


/*****************************************************************************
 �ṹ��    : CBBP_ULCODE_REVERSE_PARA_UNION
 �ṹ˵��  : ULCODE_REVERSE_PARA �Ĵ����ṹ���塣��ַƫ����:0x002C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_reverse_para_reg;
    struct
    {
        unsigned long  cpu_ulcode_reverse_intl_m_para : 4;  /* bit[0-3] : ����Reverse Interleave ��֯������EVDOʹ�ã�m������
                                                                          ��ֵ��ʾʵ�ʲ�������λ������� */
        unsigned long  reserved                       : 28; /* bit[4-31]: ���� */
    } reg;
} CBBP_ULCODE_REVERSE_PARA_UNION;
#define CBBP_ULCODE_REVERSE_PARA_cpu_ulcode_reverse_intl_m_para_START  (0)
#define CBBP_ULCODE_REVERSE_PARA_cpu_ulcode_reverse_intl_m_para_END    (3)


/*****************************************************************************
 �ṹ��    : CBBP_ULCODE_BLOCK_PARA_UNION
 �ṹ˵��  : ULCODE_BLOCK_PARA �Ĵ����ṹ���塣��ַƫ����:0x0030����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_block_para_reg;
    struct
    {
        unsigned long  cpu_ulcode_ty1_blk_intl_table_sel : 2;  /* bit[0-1]  : ����TYPE1 Block Interleave��֯ӳ���ѡ��
                                                                              0��At 9600 or 14400 bps 
                                                                              1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32
                                                                              1��At 4800 or 7200 bps 
                                                                              1 3 2 4 5 7 6 8 9 11 10 12 13 15 14 16 17 19 18 20 21 23 22 24 25 27 26 28 29 31 30 32
                                                                              2��At 2400 or 3600 bps 
                                                                              1 5 2 6 3 7 4 8 9 13 10 14 11 15 12 16 17 21 18 22 19 23 20 24 25 29 26 30 27 31 28 32
                                                                              3��At 1200 or 1800 bps 
                                                                              1 9 2 10 3 11 4 12 5 13 6 14 7 15 8 16 17 25 18 26 19 27 20 28 21 29 22 30 23 31 24 32 */
        unsigned long  reserved_0                        : 14; /* bit[2-15] : ���� */
        unsigned long  cpu_ulcode_block_intl_m_para      : 4;  /* bit[16-19]: ����Block Interleave��֯������1Xʹ�ã�m������ */
        unsigned long  reserved_1                        : 4;  /* bit[20-23]: ���� */
        unsigned long  cpu_ulcode_block_intl_j_para      : 8;  /* bit[24-31]: ����Block Interleave��֯������1Xʹ�ã�j������ */
    } reg;
} CBBP_ULCODE_BLOCK_PARA_UNION;
#define CBBP_ULCODE_BLOCK_PARA_cpu_ulcode_ty1_blk_intl_table_sel_START  (0)
#define CBBP_ULCODE_BLOCK_PARA_cpu_ulcode_ty1_blk_intl_table_sel_END    (1)
#define CBBP_ULCODE_BLOCK_PARA_cpu_ulcode_block_intl_m_para_START       (16)
#define CBBP_ULCODE_BLOCK_PARA_cpu_ulcode_block_intl_m_para_END         (19)
#define CBBP_ULCODE_BLOCK_PARA_cpu_ulcode_block_intl_j_para_START       (24)
#define CBBP_ULCODE_BLOCK_PARA_cpu_ulcode_block_intl_j_para_END         (31)


/*****************************************************************************
 �ṹ��    : CBBP_ULCODE_LEN_PARA2_UNION
 �ṹ˵��  : ULCODE_LEN_PARA2 �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_len_para2_reg;
    struct
    {
        unsigned long  cpu_ulcode_intl_len     : 16; /* bit[0-15] : 1X�����ŵ���֯���ȣ�EVDO����Ӳ����������õ��� */
        unsigned long  cpu_ulcode_len_bef_punc : 16; /* bit[16-31]: 1X��ʹ�ã�1X�¼���Э�鶨���Symbol Repeation�󳤶ȣ�EVDO����Ӳ�����м���õ��� */
    } reg;
} CBBP_ULCODE_LEN_PARA2_UNION;
#define CBBP_ULCODE_LEN_PARA2_cpu_ulcode_intl_len_START      (0)
#define CBBP_ULCODE_LEN_PARA2_cpu_ulcode_intl_len_END        (15)
#define CBBP_ULCODE_LEN_PARA2_cpu_ulcode_len_bef_punc_START  (16)
#define CBBP_ULCODE_LEN_PARA2_cpu_ulcode_len_bef_punc_END    (31)


/*****************************************************************************
 �ṹ��    : CBBP_ULCODE_PUNC_PATTERN_UNION
 �ṹ˵��  : ULCODE_PUNC_PATTERN �Ĵ����ṹ���塣��ַƫ����:0x0038����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_punc_pattern_reg;
    struct
    {
        unsigned long  cpu_ulcode_punc_pattern : 25; /* bit[0-24] : 1X��ʹ�ã�1X���޴��������ȫ1���д�װ���ʵ�ʵ�ͼ�����ã�EVDO��Ӳ���̶�ʹ��ȫ1ͼ���� */
        unsigned long  reserved                : 7;  /* bit[25-31]: ���� */
    } reg;
} CBBP_ULCODE_PUNC_PATTERN_UNION;
#define CBBP_ULCODE_PUNC_PATTERN_cpu_ulcode_punc_pattern_START  (0)
#define CBBP_ULCODE_PUNC_PATTERN_cpu_ulcode_punc_pattern_END    (24)


/*****************************************************************************
 �ṹ��    : CBBP_ULCODE_PUNC_PATTERN_LEN_UNION
 �ṹ˵��  : ULCODE_PUNC_PATTERN_LEN �Ĵ����ṹ���塣��ַƫ����:0x003C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_punc_pattern_len_reg;
    struct
    {
        unsigned long  cpu_ulcode_punc_mode        : 2;  /* bit[0-1]  : ���ģʽ��
                                                                        0�� ���ݴ��ͼ�����������Ϣ������ERAMģʽ����Ҫͨ�����ͼ�����������Ϣ�ĳ�������
                                                                        1����ERAMģʽ�£����ݹ�ʽ��������Ϣ��
                                                                        2��ERAMģʽ�£����ݹ�ʽ��������Ϣ�� */
        unsigned long  reserved_0                  : 14; /* bit[2-15] : ���� */
        unsigned long  cpu_ulcode_punc_pattern_len : 5;  /* bit[16-20]: Symbol Puncture���ͼ����Ч���ȣ�
                                                                        5,9,12,18,24,25���Ǵ��ͼ��һ��ѭ����������Чָʾbit���� */
        unsigned long  reserved_1                  : 11; /* bit[21-31]: ���� */
    } reg;
} CBBP_ULCODE_PUNC_PATTERN_LEN_UNION;
#define CBBP_ULCODE_PUNC_PATTERN_LEN_cpu_ulcode_punc_mode_START         (0)
#define CBBP_ULCODE_PUNC_PATTERN_LEN_cpu_ulcode_punc_mode_END           (1)
#define CBBP_ULCODE_PUNC_PATTERN_LEN_cpu_ulcode_punc_pattern_len_START  (16)
#define CBBP_ULCODE_PUNC_PATTERN_LEN_cpu_ulcode_punc_pattern_len_END    (20)


/*****************************************************************************
 �ṹ��    : CBBP_ULCODE_REPEAT_MODE_UNION
 �ṹ˵��  : ULCODE_REPEAT_MODE �Ĵ����ṹ���塣��ַƫ����:0x0040����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_repeat_mode_reg;
    struct
    {
        unsigned long  cpu_ulcode_repeat_mode : 1;  /* bit[0-0] : �ظ�ģʽ��
                                                                  0��Fix Data Rateģʽ��symbol repeat����ģʽ��
                                                                  1��Variable��Flexible Data Rateģʽ�� symbol repeat����ģʽ�� */
        unsigned long  reserved               : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_ULCODE_REPEAT_MODE_UNION;
#define CBBP_ULCODE_REPEAT_MODE_cpu_ulcode_repeat_mode_START  (0)
#define CBBP_ULCODE_REPEAT_MODE_cpu_ulcode_repeat_mode_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_ULCODE_OVERTIME_CFG_UNION
 �ṹ˵��  : ULCODE_OVERTIME_CFG �Ĵ����ṹ���塣��ַƫ����:0x0044����ֵ:0x0000000F�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_overtime_cfg_reg;
    struct
    {
        unsigned long  cpu_ulcode_overtime_cfg : 5;  /* bit[0-4] : ����ģ�鳬ʱ��������ֵ��0ֵ�������ã�ʵ�ʳ�ʱ����ֵΪulcod_overtime_cfg*8192���Ƽ�����ֵΪ15����̬�� */
        unsigned long  reserved                : 27; /* bit[5-31]: ���� */
    } reg;
} CBBP_ULCODE_OVERTIME_CFG_UNION;
#define CBBP_ULCODE_OVERTIME_CFG_cpu_ulcode_overtime_cfg_START  (0)
#define CBBP_ULCODE_OVERTIME_CFG_cpu_ulcode_overtime_cfg_END    (4)


/*****************************************************************************
 �ṹ��    : CBBP_ULCODE_TIMES_EN_UNION
 �ṹ˵��  : ULCODE_TIMES_EN �Ĵ����ṹ���塣��ַƫ����:0x0048����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_times_en_reg;
    struct
    {
        unsigned long  cpu_ulcode_times_en : 1;  /* bit[0]   : ���б���ͳ�Ƽ���ʹ�ܡ� */
        unsigned long  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_ULCODE_TIMES_EN_UNION;
#define CBBP_ULCODE_TIMES_EN_cpu_ulcode_times_en_START  (0)
#define CBBP_ULCODE_TIMES_EN_cpu_ulcode_times_en_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_ULCODE_CODER_STATUS_UNION
 �ṹ˵��  : ULCODE_CODER_STATUS �Ĵ����ṹ���塣��ַƫ����:0x004C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_coder_status_reg;
    struct
    {
        unsigned long  ulcode_coder_status_cpu : 1;  /* bit[0]   : æ�����״̬�ϱ���
                                                                   0���� 1��æ�� */
        unsigned long  reserved                : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_ULCODE_CODER_STATUS_UNION;
#define CBBP_ULCODE_CODER_STATUS_ulcode_coder_status_cpu_START  (0)
#define CBBP_ULCODE_CODER_STATUS_ulcode_coder_status_cpu_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_ULCODE_OVERTIME_FLAG_UNION
 �ṹ˵��  : ULCODE_OVERTIME_FLAG �Ĵ����ṹ���塣��ַƫ����:0x0050����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_overtime_flag_reg;
    struct
    {
        unsigned long  ulcode_overtime_flag_cpu : 1;  /* bit[0]   : ��ʾ����������̳�ʱ�� */
        unsigned long  reserved                 : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_ULCODE_OVERTIME_FLAG_UNION;
#define CBBP_ULCODE_OVERTIME_FLAG_ulcode_overtime_flag_cpu_START  (0)
#define CBBP_ULCODE_OVERTIME_FLAG_ulcode_overtime_flag_cpu_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_ULCODE_STATE_UNION
 �ṹ˵��  : ULCODE_STATE �Ĵ����ṹ���塣��ַƫ����:0x0054����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_state_reg;
    struct
    {
        unsigned long  ulcode_state_cpu : 3;  /* bit[0-2] : ���б���״̬�ϱ��� */
        unsigned long  reserved         : 29; /* bit[3-31]: ���� */
    } reg;
} CBBP_ULCODE_STATE_UNION;
#define CBBP_ULCODE_STATE_ulcode_state_cpu_START  (0)
#define CBBP_ULCODE_STATE_ulcode_state_cpu_END    (2)


/*****************************************************************************
 �ṹ��    : CBBP_ULCODE_TIMES_UNION
 �ṹ˵��  : ULCODE_TIMES �Ĵ����ṹ���塣��ַƫ����:0x0058����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_times_reg;
    struct
    {
        unsigned long  ulcode_int_times_cpu   : 16; /* bit[0-15] : �����жϴ����ϱ�����λ���㡣 */
        unsigned long  ulcode_start_times_cpu : 16; /* bit[16-31]: �������������ϱ�����λ���㡣 */
    } reg;
} CBBP_ULCODE_TIMES_UNION;
#define CBBP_ULCODE_TIMES_ulcode_int_times_cpu_START    (0)
#define CBBP_ULCODE_TIMES_ulcode_int_times_cpu_END      (15)
#define CBBP_ULCODE_TIMES_ulcode_start_times_cpu_START  (16)
#define CBBP_ULCODE_TIMES_ulcode_start_times_cpu_END    (31)


/*****************************************************************************
 �ṹ��    : CBBP_ULCODE_CKG_UNION
 �ṹ˵��  : ULCODE_CKG �Ĵ����ṹ���塣��ַƫ����:0x005C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_ckg_reg;
    struct
    {
        unsigned long  cpu_ulcode_ckg_bypass : 4;  /* bit[0-3] : ���б�����Ʋ���ʱ���ſ�bypass
                                                                 [0]:CRCģ���ſ�bypass
                                                                 [1]:CODģ���ſ�bypass
                                                                 [2]:RMģ���ſ�bypass
                                                                 [3]:INTLģ���ſ�bypass
                                                                 0����ʾʱ���ſ���Ч��
                                                                 1����ʾʱ�ӳ����� */
        unsigned long  reserved              : 28; /* bit[4-31]: ���� */
    } reg;
} CBBP_ULCODE_CKG_UNION;
#define CBBP_ULCODE_CKG_cpu_ulcode_ckg_bypass_START  (0)
#define CBBP_ULCODE_CKG_cpu_ulcode_ckg_bypass_END    (3)


/***======================================================================***
                     (13/20) register_define_c_ulcode_mem
 ***======================================================================***/
/***======================================================================***
                     (14/20) register_define_c_fe_sdr_if
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : CBBP_DLFE_SDR_EN_UNION
 �ṹ˵��  : DLFE_SDR_EN �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x00001000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_en_reg;
    struct
    {
        unsigned long  cpu_dlfe_sdr_en              : 1;  /* bit[0]    : ����SDR IFģ��ʹ�ܣ��ߵ�ƽ��Ч�� */
        unsigned long  reserved_0                   : 3;  /* bit[1-3]  : ���� */
        unsigned long  cpu_dlfe_sdr_start_stop_mode : 1;  /* bit[4]    : ����SDR IFģ�������ͣģʽ��0�����ּ�����������ͣ�źţ�1�����ּ��ø�����ͣ�źš� */
        unsigned long  reserved_1                   : 3;  /* bit[5-7]  : ���� */
        unsigned long  cpu_dlfe_sdr_mode            : 2;  /* bit[8-9]  : ����SDR IFģ�鹤��ģʽ��0��1��ʾ��Cģ��2��ʾ1X��3��ʾEVDO��
                                                                         �ò�������Cģʱ��Ч�� */
        unsigned long  reserved_2                   : 2;  /* bit[10-11]: ���� */
        unsigned long  cpu_dlfe_sdr_rx_mode         : 1;  /* bit[12]   : ����SDR IFģ����շּ�ģʽ��0���ǽ��շּ���1�����շּ��� */
        unsigned long  reserved_3                   : 3;  /* bit[13-15]: ���� */
        unsigned long  cpu_dlfe_sdr_start_mode      : 1;  /* bit[16]   : ����SDR IFģ���������ģʽ��0��������������������������ˣ�1���������������cpu_dlfe_sdr_start_time�����ʱ���������ˡ�
                                                                         �ò�������Gģ��ʱ��Ч�� */
        unsigned long  reserved_4                   : 3;  /* bit[17-19]: ���� */
        unsigned long  cpu_dlfe_sdr_stop_mode       : 1;  /* bit[20]   : ����SDR IFģ�����ֹͣģʽ��0������ֹͣ���������ֹͣ���ˣ�1���ﵽcpu_dlfe_sdr_data_length����İ������������Զ�ֹͣ���ˡ� */
        unsigned long  reserved_5                   : 3;  /* bit[21-23]: ���� */
        unsigned long  cpu_dlfe_sdr_trans_mode      : 1;  /* bit[24]   : ���а���ģʽ��0��DMA��ʽ��1��BBPMaster��ʽ�� */
        unsigned long  reserved_6                   : 3;  /* bit[25-27]: ���� */
        unsigned long  cpu_dlfe_sdr_dma_mode        : 1;  /* bit[28]   : ����DMA����ģʽ��0��һ��burst�������32x32bit��1��һ��burst�������16x32bit�� */
        unsigned long  reserved_7                   : 3;  /* bit[29-31]: ���� */
    } reg;
} CBBP_DLFE_SDR_EN_UNION;
#define CBBP_DLFE_SDR_EN_cpu_dlfe_sdr_en_START               (0)
#define CBBP_DLFE_SDR_EN_cpu_dlfe_sdr_en_END                 (0)
#define CBBP_DLFE_SDR_EN_cpu_dlfe_sdr_start_stop_mode_START  (4)
#define CBBP_DLFE_SDR_EN_cpu_dlfe_sdr_start_stop_mode_END    (4)
#define CBBP_DLFE_SDR_EN_cpu_dlfe_sdr_mode_START             (8)
#define CBBP_DLFE_SDR_EN_cpu_dlfe_sdr_mode_END               (9)
#define CBBP_DLFE_SDR_EN_cpu_dlfe_sdr_rx_mode_START          (12)
#define CBBP_DLFE_SDR_EN_cpu_dlfe_sdr_rx_mode_END            (12)
#define CBBP_DLFE_SDR_EN_cpu_dlfe_sdr_start_mode_START       (16)
#define CBBP_DLFE_SDR_EN_cpu_dlfe_sdr_start_mode_END         (16)
#define CBBP_DLFE_SDR_EN_cpu_dlfe_sdr_stop_mode_START        (20)
#define CBBP_DLFE_SDR_EN_cpu_dlfe_sdr_stop_mode_END          (20)
#define CBBP_DLFE_SDR_EN_cpu_dlfe_sdr_trans_mode_START       (24)
#define CBBP_DLFE_SDR_EN_cpu_dlfe_sdr_trans_mode_END         (24)
#define CBBP_DLFE_SDR_EN_cpu_dlfe_sdr_dma_mode_START         (28)
#define CBBP_DLFE_SDR_EN_cpu_dlfe_sdr_dma_mode_END           (28)


/*****************************************************************************
 �ṹ��    : CBBP_DLFE_SDR_CKG_BYS_UNION
 �ṹ˵��  : DLFE_SDR_CKG_BYS �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_ckg_bys_reg;
    struct
    {
        unsigned long  cpu_dlfe_sdr_ckg_bypass : 1;  /* bit[0]   : ���а���ʱ���ſ�bypass�źţ��ߵ�ƽ��Ч����ʾʱ�ӳ����� */
        unsigned long  reserved                : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_DLFE_SDR_CKG_BYS_UNION;
#define CBBP_DLFE_SDR_CKG_BYS_cpu_dlfe_sdr_ckg_bypass_START  (0)
#define CBBP_DLFE_SDR_CKG_BYS_cpu_dlfe_sdr_ckg_bypass_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_DLFE_SDR_START_STOP_UNION
 �ṹ˵��  : DLFE_SDR_START_STOP �Ĵ����ṹ���塣��ַƫ����:0x008����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_start_stop_reg;
    struct
    {
        unsigned long  cpu_dlfe_at1_sdr_start      : 1;  /* bit[0]    : �������������������塣 */
        unsigned long  reserved_0                  : 3;  /* bit[1-3]  : ���� */
        unsigned long  cpu_dlfe_at1_sdr_stop       : 1;  /* bit[4]    : ������������ֹͣ���塣 */
        unsigned long  reserved_1                  : 3;  /* bit[5-7]  : ���� */
        unsigned long  cpu_dlfe_at1_sdr_force_stop : 1;  /* bit[8]    : ������������ǿ��ֹͣ���塣�ڼ�⵽�����������˳�������á� */
        unsigned long  reserved_2                  : 3;  /* bit[9-11] : ���� */
        unsigned long  cpu_dlfe_at1_sdr_trans_clr  : 1;  /* bit[12]   : ��������BBPMaster���˸�λ���塣 */
        unsigned long  reserved_3                  : 3;  /* bit[13-15]: ���� */
        unsigned long  cpu_dlfe_at2_sdr_start      : 1;  /* bit[16]   : ���зּ������������塣 */
        unsigned long  reserved_4                  : 3;  /* bit[17-19]: ���� */
        unsigned long  cpu_dlfe_at2_sdr_stop       : 1;  /* bit[20]   : ���зּ�����ֹͣ���塣 */
        unsigned long  reserved_5                  : 3;  /* bit[21-23]: ���� */
        unsigned long  cpu_dlfe_at2_sdr_force_stop : 1;  /* bit[24]   : ���зּ�����ǿ��ֹͣ���塣�ڼ�⵽���зּ����˳�������á� */
        unsigned long  reserved_6                  : 3;  /* bit[25-27]: ���� */
        unsigned long  cpu_dlfe_at2_sdr_trans_clr  : 1;  /* bit[28]   : ���зּ�BBPMaster���˸�λ���塣 */
        unsigned long  reserved_7                  : 3;  /* bit[29-31]: ���� */
    } reg;
} CBBP_DLFE_SDR_START_STOP_UNION;
#define CBBP_DLFE_SDR_START_STOP_cpu_dlfe_at1_sdr_start_START       (0)
#define CBBP_DLFE_SDR_START_STOP_cpu_dlfe_at1_sdr_start_END         (0)
#define CBBP_DLFE_SDR_START_STOP_cpu_dlfe_at1_sdr_stop_START        (4)
#define CBBP_DLFE_SDR_START_STOP_cpu_dlfe_at1_sdr_stop_END          (4)
#define CBBP_DLFE_SDR_START_STOP_cpu_dlfe_at1_sdr_force_stop_START  (8)
#define CBBP_DLFE_SDR_START_STOP_cpu_dlfe_at1_sdr_force_stop_END    (8)
#define CBBP_DLFE_SDR_START_STOP_cpu_dlfe_at1_sdr_trans_clr_START   (12)
#define CBBP_DLFE_SDR_START_STOP_cpu_dlfe_at1_sdr_trans_clr_END     (12)
#define CBBP_DLFE_SDR_START_STOP_cpu_dlfe_at2_sdr_start_START       (16)
#define CBBP_DLFE_SDR_START_STOP_cpu_dlfe_at2_sdr_start_END         (16)
#define CBBP_DLFE_SDR_START_STOP_cpu_dlfe_at2_sdr_stop_START        (20)
#define CBBP_DLFE_SDR_START_STOP_cpu_dlfe_at2_sdr_stop_END          (20)
#define CBBP_DLFE_SDR_START_STOP_cpu_dlfe_at2_sdr_force_stop_START  (24)
#define CBBP_DLFE_SDR_START_STOP_cpu_dlfe_at2_sdr_force_stop_END    (24)
#define CBBP_DLFE_SDR_START_STOP_cpu_dlfe_at2_sdr_trans_clr_START   (28)
#define CBBP_DLFE_SDR_START_STOP_cpu_dlfe_at2_sdr_trans_clr_END     (28)


/*****************************************************************************
 �ṹ��    : CBBP_DLFE_SDR_OFFSET_BUFF_DEPTH_UNION
 �ṹ˵��  : DLFE_SDR_OFFSET_BUFF_DEPTH �Ĵ����ṹ���塣��ַƫ����:0x00C����ֵ:0x0000007F�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_offset_buff_depth_reg;
    struct
    {
        unsigned long  cpu_dlfe_sdr_buffer_depth : 12; /* bit[0-11] : ����Buffer��ȣ���λ32word�����ڼ���Buffer�׵�ַ��ʱ�����
                                                                      Cģ��Uģ��ʱ��һ��word��Ӧһ��chip��Gģ��ʱ��һ��word��Ӧһ��Qb�� */
        unsigned long  reserved_0                : 4;  /* bit[12-15]: ���� */
        unsigned long  cpu_dlfe_slot_head_offset : 11; /* bit[16-26]: ����ʱ϶ͷ���sys_cntʱ϶�߽����ǰ������λchip��
                                                                      �ò�������Cģʱ��Ч�� */
        unsigned long  reserved_1                : 5;  /* bit[27-31]: ���� */
    } reg;
} CBBP_DLFE_SDR_OFFSET_BUFF_DEPTH_UNION;
#define CBBP_DLFE_SDR_OFFSET_BUFF_DEPTH_cpu_dlfe_sdr_buffer_depth_START  (0)
#define CBBP_DLFE_SDR_OFFSET_BUFF_DEPTH_cpu_dlfe_sdr_buffer_depth_END    (11)
#define CBBP_DLFE_SDR_OFFSET_BUFF_DEPTH_cpu_dlfe_slot_head_offset_START  (16)
#define CBBP_DLFE_SDR_OFFSET_BUFF_DEPTH_cpu_dlfe_slot_head_offset_END    (26)


/*****************************************************************************
 �ṹ��    : CBBP_DLFE_SDR_TIME_CTRL_UNION
 �ṹ˵��  : DLFE_SDR_TIME_CTRL �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_time_ctrl_reg;
    struct
    {
        unsigned long  cpu_dlfe_sdr_start_time  : 13; /* bit[0-12] : Gģ��ʱ��gtc_timebase�ϵİ�������ʱ�̣���λQb����Χ0~4999�� */
        unsigned long  reserved_0               : 3;  /* bit[13-15]: ���� */
        unsigned long  cpu_dlfe_sdr_data_length : 12; /* bit[16-27]: ���а�������������λ32word��
                                                                     �ò�������cpu_dlfe_sdr_stop_modeΪ1ʱ��Ч�� */
        unsigned long  reserved_1               : 4;  /* bit[28-31]: ���� */
    } reg;
} CBBP_DLFE_SDR_TIME_CTRL_UNION;
#define CBBP_DLFE_SDR_TIME_CTRL_cpu_dlfe_sdr_start_time_START   (0)
#define CBBP_DLFE_SDR_TIME_CTRL_cpu_dlfe_sdr_start_time_END     (12)
#define CBBP_DLFE_SDR_TIME_CTRL_cpu_dlfe_sdr_data_length_START  (16)
#define CBBP_DLFE_SDR_TIME_CTRL_cpu_dlfe_sdr_data_length_END    (27)


/*****************************************************************************
 �ṹ��    : CBBP_DLFE_SDR_WORD_DEPTH_UNION
 �ṹ˵��  : DLFE_SDR_WORD_DEPTH �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_word_depth_reg;
    struct
    {
        unsigned long  cpu_dlfe_sdr_word_depth : 16; /* bit[0-15] : ����Buffer��ȣ���λword��
                                                                    Cģ��Uģ��ʱ��һ��word��Ӧһ��chip��Gģ��ʱ��һ��word��Ӧһ��Qb��
                                                                    ������Gģ��ʱʹ�á� */
        unsigned long  reserved                : 16; /* bit[16-31]: ���� */
    } reg;
} CBBP_DLFE_SDR_WORD_DEPTH_UNION;
#define CBBP_DLFE_SDR_WORD_DEPTH_cpu_dlfe_sdr_word_depth_START  (0)
#define CBBP_DLFE_SDR_WORD_DEPTH_cpu_dlfe_sdr_word_depth_END    (15)


/*****************************************************************************
 �ṹ��    : CBBP_DLFE_SDR_AT1_RD_CHIP_RPT_UNION
 �ṹ˵��  : DLFE_SDR_AT1_RD_CHIP_RPT �Ĵ����ṹ���塣��ַƫ����:0x040����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_at1_rd_chip_rpt_reg;
    struct
    {
        unsigned long  dlfe_sdr_at1_rd_chip_cnt_cpu : 6;  /* bit[0-5] : ��������1��ǰ����word���� */
        unsigned long  reserved                     : 26; /* bit[6-31]: ���� */
    } reg;
} CBBP_DLFE_SDR_AT1_RD_CHIP_RPT_UNION;
#define CBBP_DLFE_SDR_AT1_RD_CHIP_RPT_dlfe_sdr_at1_rd_chip_cnt_cpu_START  (0)
#define CBBP_DLFE_SDR_AT1_RD_CHIP_RPT_dlfe_sdr_at1_rd_chip_cnt_cpu_END    (5)


/*****************************************************************************
 �ṹ��    : CBBP_DLFE_SDR_AT1_RD_RPT_UNION
 �ṹ˵��  : DLFE_SDR_AT1_RD_RPT �Ĵ����ṹ���塣��ַƫ����:0x044����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_at1_rd_rpt_reg;
    struct
    {
        unsigned long  dlfe_sdr_at1_rd_block_cnt_cpu : 12; /* bit[0-11] : ��������1��ǰ���˿���������cpu_dlfe_sdr_buffer_depthͳ�ơ� */
        unsigned long  dlfe_sdr_at1_rd_page_cnt_cpu  : 20; /* bit[12-31]: ��������1��ǰ����ҳ��������cpu_dlfe_sdr_buffer_depthͳ�ơ� */
    } reg;
} CBBP_DLFE_SDR_AT1_RD_RPT_UNION;
#define CBBP_DLFE_SDR_AT1_RD_RPT_dlfe_sdr_at1_rd_block_cnt_cpu_START  (0)
#define CBBP_DLFE_SDR_AT1_RD_RPT_dlfe_sdr_at1_rd_block_cnt_cpu_END    (11)
#define CBBP_DLFE_SDR_AT1_RD_RPT_dlfe_sdr_at1_rd_page_cnt_cpu_START   (12)
#define CBBP_DLFE_SDR_AT1_RD_RPT_dlfe_sdr_at1_rd_page_cnt_cpu_END     (31)


/*****************************************************************************
 �ṹ��    : CBBP_DLFE_SDR_AT2_RD_CHIP_RPT_UNION
 �ṹ˵��  : DLFE_SDR_AT2_RD_CHIP_RPT �Ĵ����ṹ���塣��ַƫ����:0x048����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_at2_rd_chip_rpt_reg;
    struct
    {
        unsigned long  dlfe_sdr_at2_rd_chip_cnt_cpu : 6;  /* bit[0-5] : ��������2��ǰ����word���� */
        unsigned long  reserved                     : 26; /* bit[6-31]: ���� */
    } reg;
} CBBP_DLFE_SDR_AT2_RD_CHIP_RPT_UNION;
#define CBBP_DLFE_SDR_AT2_RD_CHIP_RPT_dlfe_sdr_at2_rd_chip_cnt_cpu_START  (0)
#define CBBP_DLFE_SDR_AT2_RD_CHIP_RPT_dlfe_sdr_at2_rd_chip_cnt_cpu_END    (5)


/*****************************************************************************
 �ṹ��    : CBBP_DLFE_SDR_AT2_RD_RPT_UNION
 �ṹ˵��  : DLFE_SDR_AT2_RD_RPT �Ĵ����ṹ���塣��ַƫ����:0x04C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_at2_rd_rpt_reg;
    struct
    {
        unsigned long  dlfe_sdr_at2_rd_block_cnt_cpu : 12; /* bit[0-11] : ��������2��ǰ���˿���������cpu_dlfe_sdr_buffer_depthͳ�ơ� */
        unsigned long  dlfe_sdr_at2_rd_page_cnt_cpu  : 20; /* bit[12-31]: ��������2��ǰ����ҳ��������cpu_dlfe_sdr_buffer_depthͳ�ơ� */
    } reg;
} CBBP_DLFE_SDR_AT2_RD_RPT_UNION;
#define CBBP_DLFE_SDR_AT2_RD_RPT_dlfe_sdr_at2_rd_block_cnt_cpu_START  (0)
#define CBBP_DLFE_SDR_AT2_RD_RPT_dlfe_sdr_at2_rd_block_cnt_cpu_END    (11)
#define CBBP_DLFE_SDR_AT2_RD_RPT_dlfe_sdr_at2_rd_page_cnt_cpu_START   (12)
#define CBBP_DLFE_SDR_AT2_RD_RPT_dlfe_sdr_at2_rd_page_cnt_cpu_END     (31)


/*****************************************************************************
 �ṹ��    : CBBP_DLFE_SDR_AT1_1ST_STAMP_RPT_UNION
 �ṹ˵��  : DLFE_SDR_AT1_1ST_STAMP_RPT �Ĵ����ṹ���塣��ַƫ����:0x050����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_at1_1st_stamp_rpt_reg;
    struct
    {
        unsigned long  dlfe_sdr_at1_1st_stamp_cpu : 28; /* bit[0-27] : ��������1�������˺��һ�����ݶ�Ӧʱ�����
                                                                       Cģʱ���Ϊc_base_cnt����λchip��
                                                                       bit[14:0]��������Χ0~32767chip��ʱ�䳤��80/3ms��32768chip����
                                                                       bit[16:15]��������Χ0~2��ʱ�䳤��80ms��
                                                                       bit[21:17]��������Χ0~24��ʱ�䳤��2s��
                                                                       bit[27:22]���̶�Ϊ0��
                                                                       Gģ��ʱ���Ϊgtc_tdma_qb�ϵ�֡�ź�gtc_timebase�ϵ�Qb�š�
                                                                       bit[12:0]��gtc_timebase�ϵ�֡��Qb������������Χ0~4999Qb��
                                                                       bit[23:13]��gtc_tdma_qb�ϵ�fn_low֡������������Χ0~1325֡��
                                                                       bit[27:24]���̶�Ϊ0��
                                                                       Uģ��ʱ���Ϊbase_cnt��cfn��
                                                                       bit[7:0]��symbol��chip������������Χ0~255chip��
                                                                       bit[11:8]��slot��symbol������������Χ0~9symbol��
                                                                       bit[15:12]��֡��slot������������Χ0~14slot��
                                                                       bit[27:16]��cfn�� */
        unsigned long  reserved                   : 4;  /* bit[28-31]: ���� */
    } reg;
} CBBP_DLFE_SDR_AT1_1ST_STAMP_RPT_UNION;
#define CBBP_DLFE_SDR_AT1_1ST_STAMP_RPT_dlfe_sdr_at1_1st_stamp_cpu_START  (0)
#define CBBP_DLFE_SDR_AT1_1ST_STAMP_RPT_dlfe_sdr_at1_1st_stamp_cpu_END    (27)


/*****************************************************************************
 �ṹ��    : CBBP_DLFE_SDR_AT2_1ST_STAMP_RPT_UNION
 �ṹ˵��  : DLFE_SDR_AT2_1ST_STAMP_RPT �Ĵ����ṹ���塣��ַƫ����:0x054����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_at2_1st_stamp_rpt_reg;
    struct
    {
        unsigned long  dlfe_sdr_at2_1st_stamp_cpu : 28; /* bit[0-27] : ��������2�������˺��һ�����ݶ�Ӧbase_cntʱ�������λchip��
                                                                       ʱ�������ͬ�ϡ� */
        unsigned long  reserved                   : 4;  /* bit[28-31]: ���� */
    } reg;
} CBBP_DLFE_SDR_AT2_1ST_STAMP_RPT_UNION;
#define CBBP_DLFE_SDR_AT2_1ST_STAMP_RPT_dlfe_sdr_at2_1st_stamp_cpu_START  (0)
#define CBBP_DLFE_SDR_AT2_1ST_STAMP_RPT_dlfe_sdr_at2_1st_stamp_cpu_END    (27)


/*****************************************************************************
 �ṹ��    : CBBP_DLFE_SDR_AT1_BUFFER_STAMP_RPT_UNION
 �ṹ˵��  : DLFE_SDR_AT1_BUFFER_STAMP_RPT �Ĵ����ṹ���塣��ַƫ����:0x058����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_at1_buffer_stamp_rpt_reg;
    struct
    {
        unsigned long  dlfe_sdr_at1_bufferhead_stamp_cpu : 28; /* bit[0-27] : ��������1�������˺�Buffer�׵�ַ���ݶ�Ӧʱ���������ʱ϶ͷ���档
                                                                              ʱ�������ͬ�ϡ�
                                                                              Cģ1xʱ϶ͷ��PCGͷ��CģEV-DOʱ϶ͷ��ʵ��ʱ϶ͷ��Gģ��ʱ϶ͷ��gtc_tdma_qb�ϵ�burstͷ��Uģ��ʱ϶ͷ��ʵ��ʱ϶ͷ�� */
        unsigned long  reserved                          : 4;  /* bit[28-31]: ���� */
    } reg;
} CBBP_DLFE_SDR_AT1_BUFFER_STAMP_RPT_UNION;
#define CBBP_DLFE_SDR_AT1_BUFFER_STAMP_RPT_dlfe_sdr_at1_bufferhead_stamp_cpu_START  (0)
#define CBBP_DLFE_SDR_AT1_BUFFER_STAMP_RPT_dlfe_sdr_at1_bufferhead_stamp_cpu_END    (27)


/*****************************************************************************
 �ṹ��    : CBBP_DLFE_SDR_AT2_BUFFER_STAMP_RPT_UNION
 �ṹ˵��  : DLFE_SDR_AT2_BUFFER_STAMP_RPT �Ĵ����ṹ���塣��ַƫ����:0x05C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_at2_buffer_stamp_rpt_reg;
    struct
    {
        unsigned long  dlfe_sdr_at2_bufferhead_stamp_cpu : 28; /* bit[0-27] : ��������2�������˺�Buffer�׵�ַ���ݶ�Ӧʱ���������ʱ϶ͷ���档
                                                                              ʱ�������ͬ�ϡ�
                                                                              ʱ϶ͷ����ͬ�ϡ� */
        unsigned long  reserved                          : 4;  /* bit[28-31]: ���� */
    } reg;
} CBBP_DLFE_SDR_AT2_BUFFER_STAMP_RPT_UNION;
#define CBBP_DLFE_SDR_AT2_BUFFER_STAMP_RPT_dlfe_sdr_at2_bufferhead_stamp_cpu_START  (0)
#define CBBP_DLFE_SDR_AT2_BUFFER_STAMP_RPT_dlfe_sdr_at2_bufferhead_stamp_cpu_END    (27)


/*****************************************************************************
 �ṹ��    : CBBP_DLFE_SDR_AT1_DUMP_EN_RPT_UNION
 �ṹ˵��  : DLFE_SDR_AT1_DUMP_EN_RPT �Ĵ����ṹ���塣��ַƫ����:0x070����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_at1_dump_en_rpt_reg;
    struct
    {
        unsigned long  dlfe_sdr_at1_dump_en : 1;  /* bit[0]   : ��������1����״̬�� */
        unsigned long  reserved_0           : 3;  /* bit[1-3] : ���� */
        unsigned long  dlfe_sdr_at1_err_sta : 1;  /* bit[4]   : ��������1���˳���ָʾ�� */
        unsigned long  reserved_1           : 27; /* bit[5-31]: ���� */
    } reg;
} CBBP_DLFE_SDR_AT1_DUMP_EN_RPT_UNION;
#define CBBP_DLFE_SDR_AT1_DUMP_EN_RPT_dlfe_sdr_at1_dump_en_START  (0)
#define CBBP_DLFE_SDR_AT1_DUMP_EN_RPT_dlfe_sdr_at1_dump_en_END    (0)
#define CBBP_DLFE_SDR_AT1_DUMP_EN_RPT_dlfe_sdr_at1_err_sta_START  (4)
#define CBBP_DLFE_SDR_AT1_DUMP_EN_RPT_dlfe_sdr_at1_err_sta_END    (4)


/*****************************************************************************
 �ṹ��    : CBBP_DLFE_SDR_AT2_DUMP_EN_RPT_UNION
 �ṹ˵��  : DLFE_SDR_AT2_DUMP_EN_RPT �Ĵ����ṹ���塣��ַƫ����:0x074����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_at2_dump_en_rpt_reg;
    struct
    {
        unsigned long  dlfe_sdr_at2_dump_en : 1;  /* bit[0]   : ��������2����״̬�� */
        unsigned long  reserved_0           : 3;  /* bit[1-3] : ���� */
        unsigned long  dlfe_sdr_at2_err_sta : 1;  /* bit[4]   : ��������2���˳���ָʾ�� */
        unsigned long  reserved_1           : 27; /* bit[5-31]: ���� */
    } reg;
} CBBP_DLFE_SDR_AT2_DUMP_EN_RPT_UNION;
#define CBBP_DLFE_SDR_AT2_DUMP_EN_RPT_dlfe_sdr_at2_dump_en_START  (0)
#define CBBP_DLFE_SDR_AT2_DUMP_EN_RPT_dlfe_sdr_at2_dump_en_END    (0)
#define CBBP_DLFE_SDR_AT2_DUMP_EN_RPT_dlfe_sdr_at2_err_sta_START  (4)
#define CBBP_DLFE_SDR_AT2_DUMP_EN_RPT_dlfe_sdr_at2_err_sta_END    (4)


/*****************************************************************************
 �ṹ��    : CBBP_DLFE_SDR_AT1_RD_WORD_RPT_UNION
 �ṹ˵��  : DLFE_SDR_AT1_RD_WORD_RPT �Ĵ����ṹ���塣��ַƫ����:0x078����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_at1_rd_word_rpt_reg;
    struct
    {
        unsigned long  dlfe_sdr_at1_rd_word_cnt_cpu : 16; /* bit[0-15] : ��������1��ǰ��������������cpu_dlfe_sdr_word_depthͳ�ơ�
                                                                         ������Gģ��ʱʹ�á� */
        unsigned long  dlfe_sdr_at1_rd_seg_cnt_cpu  : 16; /* bit[16-31]: ��������1��ǰ����ҳ��������cpu_dlfe_sdr_word_depthͳ�ơ�
                                                                         ������Gģ��ʱʹ�á� */
    } reg;
} CBBP_DLFE_SDR_AT1_RD_WORD_RPT_UNION;
#define CBBP_DLFE_SDR_AT1_RD_WORD_RPT_dlfe_sdr_at1_rd_word_cnt_cpu_START  (0)
#define CBBP_DLFE_SDR_AT1_RD_WORD_RPT_dlfe_sdr_at1_rd_word_cnt_cpu_END    (15)
#define CBBP_DLFE_SDR_AT1_RD_WORD_RPT_dlfe_sdr_at1_rd_seg_cnt_cpu_START   (16)
#define CBBP_DLFE_SDR_AT1_RD_WORD_RPT_dlfe_sdr_at1_rd_seg_cnt_cpu_END     (31)


/*****************************************************************************
 �ṹ��    : CBBP_DLFE_SDR_AT2_RD_WORD_RPT_UNION
 �ṹ˵��  : DLFE_SDR_AT2_RD_WORD_RPT �Ĵ����ṹ���塣��ַƫ����:0x07C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_at2_rd_word_rpt_reg;
    struct
    {
        unsigned long  dlfe_sdr_at2_rd_word_cnt_cpu : 16; /* bit[0-15] : ��������2��ǰ��������������cpu_dlfe_sdr_word_depthͳ�ơ�
                                                                         ������Gģ��ʱʹ�á� */
        unsigned long  dlfe_sdr_at2_rd_seg_cnt_cpu  : 16; /* bit[16-31]: ��������2��ǰ����ҳ��������cpu_dlfe_sdr_word_depthͳ�ơ�
                                                                         ������Gģ��ʱʹ�á� */
    } reg;
} CBBP_DLFE_SDR_AT2_RD_WORD_RPT_UNION;
#define CBBP_DLFE_SDR_AT2_RD_WORD_RPT_dlfe_sdr_at2_rd_word_cnt_cpu_START  (0)
#define CBBP_DLFE_SDR_AT2_RD_WORD_RPT_dlfe_sdr_at2_rd_word_cnt_cpu_END    (15)
#define CBBP_DLFE_SDR_AT2_RD_WORD_RPT_dlfe_sdr_at2_rd_seg_cnt_cpu_START   (16)
#define CBBP_DLFE_SDR_AT2_RD_WORD_RPT_dlfe_sdr_at2_rd_seg_cnt_cpu_END     (31)


/*****************************************************************************
 �ṹ��    : CBBP_ULFE_SDR_EN_UNION
 �ṹ˵��  : ULFE_SDR_EN �Ĵ����ṹ���塣��ַƫ����:0x100����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ulfe_sdr_en_reg;
    struct
    {
        unsigned long  cpu_ulfe_sdr_en            : 1;  /* bit[0]    : ����SDR IFģ��ʹ�ܣ��ߵ�ƽ��Ч�� */
        unsigned long  reserved_0                 : 3;  /* bit[1-3]  : ���� */
        unsigned long  cpu_ulfe_sdr_da_on         : 1;  /* bit[4]    : ����da_on���ߵ�ƽ��Ч��BBP��sys_cntʱ϶�߽�ͬ����ʹ�á�
                                                                       �ò�������Cģʱ��Ч�� */
        unsigned long  reserved_1                 : 3;  /* bit[5-7]  : ���� */
        unsigned long  cpu_ulfe_sdr_mode          : 2;  /* bit[8-9]  : ����SDR IFģ�鹤��ģʽ��0��1��ʾ��Cģ��2��ʾ1X��3��ʾEVDO��
                                                                       �ò�������Cģʱ��Ч�� */
        unsigned long  reserved_2                 : 2;  /* bit[10-11]: ���� */
        unsigned long  cpu_ulfe_sdr_g_mode        : 1;  /* bit[12]   : Gģ�����з���ģʽ��0������ģʽ��1������ģʽ�� */
        unsigned long  reserved_3                 : 3;  /* bit[13-15]: ���� */
        unsigned long  cpu_ulfe_sdr_g_timing_mode : 1;  /* bit[16]   : Gģ�����з��Ͷ�ʱѡ��0������gtc_timebase��1������gtc_tdma_qb�� */
        unsigned long  reserved_4                 : 7;  /* bit[17-23]: ���� */
        unsigned long  cpu_ulfe_sdr_trans_mode    : 1;  /* bit[24]   : ���а���ģʽ��0��DMA��ʽ��1��BBPMaster��ʽ�� */
        unsigned long  reserved_5                 : 7;  /* bit[25-31]: ���� */
    } reg;
} CBBP_ULFE_SDR_EN_UNION;
#define CBBP_ULFE_SDR_EN_cpu_ulfe_sdr_en_START             (0)
#define CBBP_ULFE_SDR_EN_cpu_ulfe_sdr_en_END               (0)
#define CBBP_ULFE_SDR_EN_cpu_ulfe_sdr_da_on_START          (4)
#define CBBP_ULFE_SDR_EN_cpu_ulfe_sdr_da_on_END            (4)
#define CBBP_ULFE_SDR_EN_cpu_ulfe_sdr_mode_START           (8)
#define CBBP_ULFE_SDR_EN_cpu_ulfe_sdr_mode_END             (9)
#define CBBP_ULFE_SDR_EN_cpu_ulfe_sdr_g_mode_START         (12)
#define CBBP_ULFE_SDR_EN_cpu_ulfe_sdr_g_mode_END           (12)
#define CBBP_ULFE_SDR_EN_cpu_ulfe_sdr_g_timing_mode_START  (16)
#define CBBP_ULFE_SDR_EN_cpu_ulfe_sdr_g_timing_mode_END    (16)
#define CBBP_ULFE_SDR_EN_cpu_ulfe_sdr_trans_mode_START     (24)
#define CBBP_ULFE_SDR_EN_cpu_ulfe_sdr_trans_mode_END       (24)


/*****************************************************************************
 �ṹ��    : CBBP_ULFE_SDR_CKG_UNION
 �ṹ˵��  : ULFE_SDR_CKG �Ĵ����ṹ���塣��ַƫ����:0x104����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ulfe_sdr_ckg_reg;
    struct
    {
        unsigned long  cpu_ulfe_sdr_ckg_bypass : 1;  /* bit[0]   : ���а���ʱ���ſ�bypass�źţ��ߵ�ƽ��Ч����ʾʱ�ӳ����� */
        unsigned long  reserved                : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_ULFE_SDR_CKG_UNION;
#define CBBP_ULFE_SDR_CKG_cpu_ulfe_sdr_ckg_bypass_START  (0)
#define CBBP_ULFE_SDR_CKG_cpu_ulfe_sdr_ckg_bypass_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_ULFE_SDR_START_UNION
 �ṹ˵��  : ULFE_SDR_START �Ĵ����ṹ���塣��ַƫ����:0x108����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ulfe_sdr_start_reg;
    struct
    {
        unsigned long  cpu_ulfe_sdr_g_start     : 1;  /* bit[0]   : ����ȡ�������������塣
                                                                    �ò�������Gģ��ʱ��Ч�� */
        unsigned long  cpu_ulfe_sdr_g_stop      : 1;  /* bit[1]   : ����ȡ������ֹͣ���塣
                                                                    �ò�������Gģ��ʱ��Ч�� */
        unsigned long  reserved_0               : 2;  /* bit[2-3] : ���� */
        unsigned long  cpu_ulfe_sdr_trans_start : 1;  /* bit[4]   : BBPMaster���˷�ʽ�£�Cģ���ݰ����������塣 */
        unsigned long  cpu_ulfe_sdr_trans_clr   : 1;  /* bit[5]   : BBPMaster���˸�λ���塣 */
        unsigned long  reserved_1               : 26; /* bit[6-31]: ���� */
    } reg;
} CBBP_ULFE_SDR_START_UNION;
#define CBBP_ULFE_SDR_START_cpu_ulfe_sdr_g_start_START      (0)
#define CBBP_ULFE_SDR_START_cpu_ulfe_sdr_g_start_END        (0)
#define CBBP_ULFE_SDR_START_cpu_ulfe_sdr_g_stop_START       (1)
#define CBBP_ULFE_SDR_START_cpu_ulfe_sdr_g_stop_END         (1)
#define CBBP_ULFE_SDR_START_cpu_ulfe_sdr_trans_start_START  (4)
#define CBBP_ULFE_SDR_START_cpu_ulfe_sdr_trans_start_END    (4)
#define CBBP_ULFE_SDR_START_cpu_ulfe_sdr_trans_clr_START    (5)
#define CBBP_ULFE_SDR_START_cpu_ulfe_sdr_trans_clr_END      (5)


/*****************************************************************************
 �ṹ��    : CBBP_ULFE_SDR_OFFSET_UNION
 �ṹ˵��  : ULFE_SDR_OFFSET �Ĵ����ṹ���塣��ַƫ����:0x10C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ulfe_sdr_offset_reg;
    struct
    {
        unsigned long  cpu_ulfe_slot_offset : 13; /* bit[0-12] : Cģʱ����ʾ����ʱ϶ͷ���sys_cntʱ϶�߽���ǰ������λ1/4chip��
                                                                 Gģ��ʱ����ʾgtc_tdma_qb�ϵ��������ݷ���ʱ�̣���λQb����Χ0~4999�� */
        unsigned long  reserved_0           : 3;  /* bit[13-15]: ���� */
        unsigned long  cpu_ulfe_ach_offset  : 11; /* bit[16-26]: Cģʱ����ʾ����ACHʱ϶ͷ���sys_cntʱ϶�߽��ӳ�������λchip��
                                                                 Gģ��ʱ��bit[22:16]��ʾ�������ݷ��͵�Qb��clkʱ�̣�bit[26:23]�����塣 */
        unsigned long  reserved_1           : 5;  /* bit[27-31]: ���� */
    } reg;
} CBBP_ULFE_SDR_OFFSET_UNION;
#define CBBP_ULFE_SDR_OFFSET_cpu_ulfe_slot_offset_START  (0)
#define CBBP_ULFE_SDR_OFFSET_cpu_ulfe_slot_offset_END    (12)
#define CBBP_ULFE_SDR_OFFSET_cpu_ulfe_ach_offset_START   (16)
#define CBBP_ULFE_SDR_OFFSET_cpu_ulfe_ach_offset_END     (26)


/*****************************************************************************
 �ṹ��    : CBBP_ULFE_SDR_ACTIVE_TIME_UNION
 �ṹ˵��  : ULFE_SDR_ACTIVE_TIME �Ĵ����ṹ���塣��ַƫ����:0x110����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ulfe_sdr_active_time_reg;
    struct
    {
        unsigned long  cpu_ulfe_dbb_active_time        : 13; /* bit[0-12] : Cģʱ����ʾ����dbb��������ǰʱ϶ͷ��Чλ�ã���λ1/4chip��
                                                                            Gģ��ʱ��bit[11:0]��ʾ�������ݵ�һ��burst��ʼ���㣬ȡֵ��Χ0~2499��bit[12]�����塣 */
        unsigned long  reserved_0                      : 3;  /* bit[13-15]: ���� */
        unsigned long  cpu_ulfe_phase_comp_active_time : 13; /* bit[16-28]: Cģʱ����ʾ������λ������ǰʱ϶ͷ��Чλ�ã���λ1/4chip��
                                                                            Gģ��ʱ��bit[27:16]��ʾ�����������һ��burst�������㣬ȡֵ��Χ0~2499��bit[28]�����塣 */
        unsigned long  reserved_1                      : 3;  /* bit[29-31]: ���� */
    } reg;
} CBBP_ULFE_SDR_ACTIVE_TIME_UNION;
#define CBBP_ULFE_SDR_ACTIVE_TIME_cpu_ulfe_dbb_active_time_START         (0)
#define CBBP_ULFE_SDR_ACTIVE_TIME_cpu_ulfe_dbb_active_time_END           (12)
#define CBBP_ULFE_SDR_ACTIVE_TIME_cpu_ulfe_phase_comp_active_time_START  (16)
#define CBBP_ULFE_SDR_ACTIVE_TIME_cpu_ulfe_phase_comp_active_time_END    (28)


/*****************************************************************************
 �ṹ��    : CBBP_ULFE_SDR_G_CFG_UNION
 �ṹ˵��  : ULFE_SDR_G_CFG �Ĵ����ṹ���塣��ַƫ����:0x114����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ulfe_sdr_g_cfg_reg;
    struct
    {
        unsigned long  cpu_ulfe_sdr_g_burst_num : 3;  /* bit[0-2] : Gģ��ʱ���������ݰ�����burst������ȡֵ��Χ0~5������ֵ��1��ʾʵ��burst������ */
        unsigned long  reserved                 : 29; /* bit[3-31]: ���� */
    } reg;
} CBBP_ULFE_SDR_G_CFG_UNION;
#define CBBP_ULFE_SDR_G_CFG_cpu_ulfe_sdr_g_burst_num_START  (0)
#define CBBP_ULFE_SDR_G_CFG_cpu_ulfe_sdr_g_burst_num_END    (2)


/*****************************************************************************
 �ṹ��    : CBBP_ULFE_SDR_DUMP_EN_RPT_UNION
 �ṹ˵��  : ULFE_SDR_DUMP_EN_RPT �Ĵ����ṹ���塣��ַƫ����:0x140����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ulfe_sdr_dump_en_rpt_reg;
    struct
    {
        unsigned long  ulfe_sdr_dump_en   : 1;  /* bit[0]   : ���а���״̬�� */
        unsigned long  reserved_0         : 3;  /* bit[1-3] : ���� */
        unsigned long  ulfe_sdr_err_sta   : 1;  /* bit[4]   : ����BBPMaster���˳���ָʾ�� */
        unsigned long  reserved_1         : 3;  /* bit[5-7] : ���� */
        unsigned long  ulfe_sdr_trans_sta : 1;  /* bit[8]   : ����BBPMaster�������ָʾ�� */
        unsigned long  reserved_2         : 23; /* bit[9-31]: ���� */
    } reg;
} CBBP_ULFE_SDR_DUMP_EN_RPT_UNION;
#define CBBP_ULFE_SDR_DUMP_EN_RPT_ulfe_sdr_dump_en_START    (0)
#define CBBP_ULFE_SDR_DUMP_EN_RPT_ulfe_sdr_dump_en_END      (0)
#define CBBP_ULFE_SDR_DUMP_EN_RPT_ulfe_sdr_err_sta_START    (4)
#define CBBP_ULFE_SDR_DUMP_EN_RPT_ulfe_sdr_err_sta_END      (4)
#define CBBP_ULFE_SDR_DUMP_EN_RPT_ulfe_sdr_trans_sta_START  (8)
#define CBBP_ULFE_SDR_DUMP_EN_RPT_ulfe_sdr_trans_sta_END    (8)


/***======================================================================***
                     (15/20) register_define_c_fe_sdr_if_mem
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : CBBP_ULFE_SDR_RAM_UNION
 �ṹ˵��  : ULFE_SDR_RAM �Ĵ����ṹ���塣��ַƫ����:0x800����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ulfe_sdr_ram_reg;
    struct
    {
        unsigned long  ulfe_sdr_data_i : 12; /* bit[0-11] : Cģʱ����ʾ����ǰ������I·��12�����з����������ÿ1/4 PCG��slotдһ�顣
                                                            Gģ��ʱ����ʾ���з�������I·��12�����з����������ÿ1/5 burstдһ�顣 */
        unsigned long  reserved_0      : 4;  /* bit[12-15]: ���� */
        unsigned long  ulfe_sdr_data_q : 12; /* bit[16-27]: Cģʱ����ʾ����ǰ������Q·��12�����з����������ÿ1/4 PCG��slotдһ�顣
                                                            Gģ��ʱ����ʾ���з�������Q·��12�����з����������ÿ1/5 burstдһ�顣 */
        unsigned long  reserved_1      : 4;  /* bit[28-31]: ���� */
    } reg;
} CBBP_ULFE_SDR_RAM_UNION;
#define CBBP_ULFE_SDR_RAM_ulfe_sdr_data_i_START  (0)
#define CBBP_ULFE_SDR_RAM_ulfe_sdr_data_i_END    (11)
#define CBBP_ULFE_SDR_RAM_ulfe_sdr_data_q_START  (16)
#define CBBP_ULFE_SDR_RAM_ulfe_sdr_data_q_END    (27)


/***======================================================================***
                     (16/20) register_define_c_fe_ctrl
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : CBBP_CTU_CFG_UNION
 �ṹ˵��  : CTU_CFG �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x00000100�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ctu_cfg_reg;
    struct
    {
        unsigned long  cpu_ctu_meas_type                   : 2;  /* bit[0-1]  : C�������ͣ�0��Ƶ��1��ϵͳ��2��ģ�� */
        unsigned long  reserved_0                          : 2;  /* bit[2-3]  : ���� */
        unsigned long  cpu_ctu_meas_en_value               : 1;  /* bit[4]    : ���������Ƶ��ϵͳ����ʹ���ź�ֵ�� */
        unsigned long  reserved_1                          : 3;  /* bit[5-7]  : ���� */
        unsigned long  cpu_ctu_intersys_ingap_value        : 1;  /* bit[8]    : �������intersys_ingap_pre_ind�ź�ֵ�� */
        unsigned long  reserved_2                          : 3;  /* bit[9-11] : ���� */
        unsigned long  cpu_ctu_master_meas_c_en            : 1;  /* bit[12]   : C��ģʱ��com2c_master_intrasys_valid �½�������SSI��MIPI��GPIO RAM����ʹ�ܣ��ߵ�ƽ��Ч�� */
        unsigned long  cpu_ctu_intrasys_valid_delay_neg_en : 1;  /* bit[13]   : C��ģʱ��c2com_intrasys_valid_delay�½�������SSI��MIPI��GPIO RAM����ʹ�ܣ��ߵ�ƽ��Ч�� */
        unsigned long  cpu_ctu_intrasys_valid_delay_pos_en : 1;  /* bit[14]   : C��ģʱ��c2com_intrasys_valid_delay����������SSI��MIPI��GPIO RAM����ʹ�ܣ��ߵ�ƽ��Ч�� */
        unsigned long  reserved_3                          : 1;  /* bit[15]   : ���� */
        unsigned long  cpu_c_fe_ctrl_mode                  : 2;  /* bit[16-17]: c_fe_ctrlģ�鹤��ģʽ��0��1��ʾ��Cģ��2��ʾ1X��3��ʾEVDO�� */
        unsigned long  reserved_4                          : 14; /* bit[18-31]: ���� */
    } reg;
} CBBP_CTU_CFG_UNION;
#define CBBP_CTU_CFG_cpu_ctu_meas_type_START                    (0)
#define CBBP_CTU_CFG_cpu_ctu_meas_type_END                      (1)
#define CBBP_CTU_CFG_cpu_ctu_meas_en_value_START                (4)
#define CBBP_CTU_CFG_cpu_ctu_meas_en_value_END                  (4)
#define CBBP_CTU_CFG_cpu_ctu_intersys_ingap_value_START         (8)
#define CBBP_CTU_CFG_cpu_ctu_intersys_ingap_value_END           (8)
#define CBBP_CTU_CFG_cpu_ctu_master_meas_c_en_START             (12)
#define CBBP_CTU_CFG_cpu_ctu_master_meas_c_en_END               (12)
#define CBBP_CTU_CFG_cpu_ctu_intrasys_valid_delay_neg_en_START  (13)
#define CBBP_CTU_CFG_cpu_ctu_intrasys_valid_delay_neg_en_END    (13)
#define CBBP_CTU_CFG_cpu_ctu_intrasys_valid_delay_pos_en_START  (14)
#define CBBP_CTU_CFG_cpu_ctu_intrasys_valid_delay_pos_en_END    (14)
#define CBBP_CTU_CFG_cpu_c_fe_ctrl_mode_START                   (16)
#define CBBP_CTU_CFG_cpu_c_fe_ctrl_mode_END                     (17)


/*****************************************************************************
 �ṹ��    : CBBP_CTU_MEAS_ACT_TIME_UNION
 �ṹ˵��  : CTU_MEAS_ACT_TIME �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ctu_meas_act_time_reg;
    struct
    {
        unsigned long  cpu_ctu_meas_en_active_time : 17; /* bit[0-16] : ���������Ƶ��ϵͳ����ʹ���ź���sys_cnt��Чʱ�̣���λchip�� */
        unsigned long  reserved                    : 15; /* bit[17-31]: ���� */
    } reg;
} CBBP_CTU_MEAS_ACT_TIME_UNION;
#define CBBP_CTU_MEAS_ACT_TIME_cpu_ctu_meas_en_active_time_START  (0)
#define CBBP_CTU_MEAS_ACT_TIME_cpu_ctu_meas_en_active_time_END    (16)


/*****************************************************************************
 �ṹ��    : CBBP_CTU_INGAP_ACT_TIME_UNION
 �ṹ˵��  : CTU_INGAP_ACT_TIME �Ĵ����ṹ���塣��ַƫ����:0x008����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ctu_ingap_act_time_reg;
    struct
    {
        unsigned long  cpu_ctu_intersys_ingap_active_time : 17; /* bit[0-16] : �������intersys_ingap_pre_ind�ź���sys_cnt��Чʱ�̣���λchip�� */
        unsigned long  reserved                           : 15; /* bit[17-31]: ���� */
    } reg;
} CBBP_CTU_INGAP_ACT_TIME_UNION;
#define CBBP_CTU_INGAP_ACT_TIME_cpu_ctu_intersys_ingap_active_time_START  (0)
#define CBBP_CTU_INGAP_ACT_TIME_cpu_ctu_intersys_ingap_active_time_END    (16)


/*****************************************************************************
 �ṹ��    : CBBP_CTU_INTRA_CLR_ACT_TIME_UNION
 �ṹ˵��  : CTU_INTRA_CLR_ACT_TIME �Ĵ����ṹ���塣��ַƫ����:0x00C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ctu_intra_clr_act_time_reg;
    struct
    {
        unsigned long  cpu_ctu_intrasys_valid_clr_active_time : 17; /* bit[0-16] : �������intrasys_valid�ź���0��sys_cnt��Чʱ�̣���λchip�� */
        unsigned long  reserved                               : 15; /* bit[17-31]: ���� */
    } reg;
} CBBP_CTU_INTRA_CLR_ACT_TIME_UNION;
#define CBBP_CTU_INTRA_CLR_ACT_TIME_cpu_ctu_intrasys_valid_clr_active_time_START  (0)
#define CBBP_CTU_INTRA_CLR_ACT_TIME_cpu_ctu_intrasys_valid_clr_active_time_END    (16)


/*****************************************************************************
 �ṹ��    : CBBP_CTU_INTRA_SET_ACT_TIME_UNION
 �ṹ˵��  : CTU_INTRA_SET_ACT_TIME �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ctu_intra_set_act_time_reg;
    struct
    {
        unsigned long  cpu_ctu_intrasys_valid_set_active_time : 17; /* bit[0-16] : �������intrasys_valid�ź���1��sys_cnt��Чʱ�̣���λchip�� */
        unsigned long  reserved                               : 15; /* bit[17-31]: ���� */
    } reg;
} CBBP_CTU_INTRA_SET_ACT_TIME_UNION;
#define CBBP_CTU_INTRA_SET_ACT_TIME_cpu_ctu_intrasys_valid_set_active_time_START  (0)
#define CBBP_CTU_INTRA_SET_ACT_TIME_cpu_ctu_intrasys_valid_set_active_time_END    (16)


/*****************************************************************************
 �ṹ��    : CBBP_CTU_INTRA_DLY_CLR_ACT_TIME_UNION
 �ṹ˵��  : CTU_INTRA_DLY_CLR_ACT_TIME �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ctu_intra_dly_clr_act_time_reg;
    struct
    {
        unsigned long  cpu_ctu_intrasys_valid_delay_clr_active_time : 17; /* bit[0-16] : �������intrasys_valid_delay�ź���0��sys_cnt��Чʱ�̣���λchip�� */
        unsigned long  reserved                                     : 15; /* bit[17-31]: ���� */
    } reg;
} CBBP_CTU_INTRA_DLY_CLR_ACT_TIME_UNION;
#define CBBP_CTU_INTRA_DLY_CLR_ACT_TIME_cpu_ctu_intrasys_valid_delay_clr_active_time_START  (0)
#define CBBP_CTU_INTRA_DLY_CLR_ACT_TIME_cpu_ctu_intrasys_valid_delay_clr_active_time_END    (16)


/*****************************************************************************
 �ṹ��    : CBBP_CTU_INTRA_DLY_SET_ACT_TIME_UNION
 �ṹ˵��  : CTU_INTRA_DLY_SET_ACT_TIME �Ĵ����ṹ���塣��ַƫ����:0x018����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ctu_intra_dly_set_act_time_reg;
    struct
    {
        unsigned long  cpu_ctu_intrasys_valid_delay_set_active_time : 17; /* bit[0-16] : �������intrasys_valid_delay�ź���1��sys_cnt��Чʱ�̣���λchip�� */
        unsigned long  reserved                                     : 15; /* bit[17-31]: ���� */
    } reg;
} CBBP_CTU_INTRA_DLY_SET_ACT_TIME_UNION;
#define CBBP_CTU_INTRA_DLY_SET_ACT_TIME_cpu_ctu_intrasys_valid_delay_set_active_time_START  (0)
#define CBBP_CTU_INTRA_DLY_SET_ACT_TIME_cpu_ctu_intrasys_valid_delay_set_active_time_END    (16)


/*****************************************************************************
 �ṹ��    : CBBP_CTU_STOP_CLR_ACT_TIME_UNION
 �ṹ˵��  : CTU_STOP_CLR_ACT_TIME �Ĵ����ṹ���塣��ַƫ����:0x01C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ctu_stop_clr_act_time_reg;
    struct
    {
        unsigned long  cpu_ctu_ssi_mipi_stop_clr_active_time : 17; /* bit[0-16] : �������ssi_mipi_stop�ź���0��sys_cnt��Чʱ�̣���λchip�� */
        unsigned long  reserved                              : 15; /* bit[17-31]: ���� */
    } reg;
} CBBP_CTU_STOP_CLR_ACT_TIME_UNION;
#define CBBP_CTU_STOP_CLR_ACT_TIME_cpu_ctu_ssi_mipi_stop_clr_active_time_START  (0)
#define CBBP_CTU_STOP_CLR_ACT_TIME_cpu_ctu_ssi_mipi_stop_clr_active_time_END    (16)


/*****************************************************************************
 �ṹ��    : CBBP_CTU_STOP_SET_ACT_TIME_UNION
 �ṹ˵��  : CTU_STOP_SET_ACT_TIME �Ĵ����ṹ���塣��ַƫ����:0x020����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ctu_stop_set_act_time_reg;
    struct
    {
        unsigned long  cpu_ctu_ssi_mipi_stop_set_active_time : 17; /* bit[0-16] : �������ssi_mipi_stop�ź���1��sys_cnt��Чʱ�̣���λchip�� */
        unsigned long  reserved                              : 15; /* bit[17-31]: ���� */
    } reg;
} CBBP_CTU_STOP_SET_ACT_TIME_UNION;
#define CBBP_CTU_STOP_SET_ACT_TIME_cpu_ctu_ssi_mipi_stop_set_active_time_START  (0)
#define CBBP_CTU_STOP_SET_ACT_TIME_cpu_ctu_ssi_mipi_stop_set_active_time_END    (16)


/*****************************************************************************
 �ṹ��    : CBBP_RFIC_START_TIME_UNION
 �ṹ˵��  : RFIC_START_TIME �Ĵ����ṹ���塣��ַƫ����:0x040����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      rfic_start_time_reg;
    struct
    {
        unsigned long  cpu_rfic_ssi_auto_run_time : 11; /* bit[0-10] : rfic_ssiÿʱ϶t2λ��(sys_cnt)���޷���������Χ[0,1535��2047]����λchip��BBP�ڴ�λ�ö�RFIC SSI RAM��ҳ������ʼ����RAM�����ַ������ݡ�ע�⣺��G SDRģʽ���ò���������active_time��ͬ */
        unsigned long  reserved                   : 21; /* bit[11-31]: ���� */
    } reg;
} CBBP_RFIC_START_TIME_UNION;
#define CBBP_RFIC_START_TIME_cpu_rfic_ssi_auto_run_time_START  (0)
#define CBBP_RFIC_START_TIME_cpu_rfic_ssi_auto_run_time_END    (10)


/*****************************************************************************
 �ṹ��    : CBBP_RFIC_SSI_STA_CFG_UNION
 �ṹ˵��  : RFIC_SSI_STA_CFG �Ĵ����ṹ���塣��ַƫ����:0x044����ֵ:0x00001902�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      rfic_ssi_sta_cfg_reg;
    struct
    {
        unsigned long  cpu_rfic_ssi_work_mode_sel          : 1;  /* bit[0]    : 0:��ѯģʽ��DSPд��RAM���������ͣ�BBPѭ����������ctrlbuffer��ֱ��ȫ�����ݷ�����ɡ���ģʽ��������cpu_rfic_ssi_buffer_clr_modeΪ1
                                                                                1:�������ģʽ��DSP����ʱ϶��Ҫ���͵��������ݰ���Чʱ����ǰ�����������RAM�У�BBPֻ����һ��ctrlbuffer������ִ�С� */
        unsigned long  cpu_rfic_ssi_buffer_clr_mode        : 1;  /* bit[1]    : 0:ctrl_buffִ��������㣬1:ctrl_buffִ��������� */
        unsigned long  cpu_rfic_ssi_buffer_mode            : 1;  /* bit[2]    : 0:ÿ��ctrl_buff��Ӧ���7�����ݡ�1:ÿ��ctrl_buff��Ӧ���3�����ݡ� */
        unsigned long  reserved_0                          : 1;  /* bit[3]    : ���� */
        unsigned long  cpu_rfic_ssi_data_buffer_start_addr : 7;  /* bit[4-10] : ÿ��ƹ��RAM��data_buffer��ʼ��ַ�� */
        unsigned long  cpu_rfic_ssi_page_switch_en         : 1;  /* bit[11]   : ��ҳʹ�ܣ�0:����ҳ�������BBP��ʹ�õͶ�RAM��1����ҳ�������BBPƹ��ʹ�øߵ�����RAM�� */
        unsigned long  cpu_rfic_ssi_auto_run               : 1;  /* bit[12]   : �Զ���ҳʹ�ܣ�0��������������ֶ���ҳ��1�����������ʱ���Զ���ҳ�� */
        unsigned long  reserved_1                          : 19; /* bit[13-31]: ���� */
    } reg;
} CBBP_RFIC_SSI_STA_CFG_UNION;
#define CBBP_RFIC_SSI_STA_CFG_cpu_rfic_ssi_work_mode_sel_START           (0)
#define CBBP_RFIC_SSI_STA_CFG_cpu_rfic_ssi_work_mode_sel_END             (0)
#define CBBP_RFIC_SSI_STA_CFG_cpu_rfic_ssi_buffer_clr_mode_START         (1)
#define CBBP_RFIC_SSI_STA_CFG_cpu_rfic_ssi_buffer_clr_mode_END           (1)
#define CBBP_RFIC_SSI_STA_CFG_cpu_rfic_ssi_buffer_mode_START             (2)
#define CBBP_RFIC_SSI_STA_CFG_cpu_rfic_ssi_buffer_mode_END               (2)
#define CBBP_RFIC_SSI_STA_CFG_cpu_rfic_ssi_data_buffer_start_addr_START  (4)
#define CBBP_RFIC_SSI_STA_CFG_cpu_rfic_ssi_data_buffer_start_addr_END    (10)
#define CBBP_RFIC_SSI_STA_CFG_cpu_rfic_ssi_page_switch_en_START          (11)
#define CBBP_RFIC_SSI_STA_CFG_cpu_rfic_ssi_page_switch_en_END            (11)
#define CBBP_RFIC_SSI_STA_CFG_cpu_rfic_ssi_auto_run_START                (12)
#define CBBP_RFIC_SSI_STA_CFG_cpu_rfic_ssi_auto_run_END                  (12)


/*****************************************************************************
 �ṹ��    : CBBP_RFIC_SSI_DYN_CFG_UNION
 �ṹ˵��  : RFIC_SSI_DYN_CFG �Ĵ����ṹ���塣��ַƫ����:0x048����ֵ:0x00000080�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      rfic_ssi_dyn_cfg_reg;
    struct
    {
        unsigned long  cpu_rfic_ssi_pro_en    : 1;  /* bit[0]   : ģ�鹤��ʹ�ܣ��ߵ�ƽ��Ч�� */
        unsigned long  reserved_0             : 3;  /* bit[1-3] : ���� */
        unsigned long  cpu_rfic_ssi_hold_page : 1;  /* bit[4]   : 1��ʾ��ͣ���͵�ǰRAM�����ݡ������ź���Чʱ���������Ҫ��дRAM�е����ݣ�����Ҫ�ֶ���ҳ��ֱ���ڵ�ǰҳ������Hold������BBP���ͷ��ʼ����ִ��CtrlBuffer��ָ�� */
        unsigned long  reserved_1             : 1;  /* bit[5]   : ���� */
        unsigned long  cpu_rfic_ssi_stop_page : 1;  /* bit[6]   : 1��ʾֹͣ���͵�ǰRAM�����ݲ������ǰRAM�������ݡ� */
        unsigned long  cpu_rfic_ssi_stop_mode : 1;  /* bit[7]   : ֹͣ����ģʽ��0��ʾ����ֹͣ�����������ݣ�1��ʾ��ǰctrl_buff��Ӧ���ݷ�����ɺ���ֹͣ�� */
        unsigned long  reserved_2             : 24; /* bit[8-31]: ���� */
    } reg;
} CBBP_RFIC_SSI_DYN_CFG_UNION;
#define CBBP_RFIC_SSI_DYN_CFG_cpu_rfic_ssi_pro_en_START     (0)
#define CBBP_RFIC_SSI_DYN_CFG_cpu_rfic_ssi_pro_en_END       (0)
#define CBBP_RFIC_SSI_DYN_CFG_cpu_rfic_ssi_hold_page_START  (4)
#define CBBP_RFIC_SSI_DYN_CFG_cpu_rfic_ssi_hold_page_END    (4)
#define CBBP_RFIC_SSI_DYN_CFG_cpu_rfic_ssi_stop_page_START  (6)
#define CBBP_RFIC_SSI_DYN_CFG_cpu_rfic_ssi_stop_page_END    (6)
#define CBBP_RFIC_SSI_DYN_CFG_cpu_rfic_ssi_stop_mode_START  (7)
#define CBBP_RFIC_SSI_DYN_CFG_cpu_rfic_ssi_stop_mode_END    (7)


/*****************************************************************************
 �ṹ��    : CBBP_RFIC_SSI_START_UNION
 �ṹ˵��  : RFIC_SSI_START �Ĵ����ṹ���塣��ַƫ����:0x04C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      rfic_ssi_start_reg;
    struct
    {
        unsigned long  cpu_rfic_ssi_page_start  : 1;  /* bit[0]    : д1���������źţ��ֶ�����ָ��ҳִ�У�cpu_rfic_ssi_auto_run=0ʱ����Ч�� */
        unsigned long  reserved_0               : 15; /* bit[1-15] : ���� */
        unsigned long  cpu_rfic_ssi_force_pulse : 1;  /* bit[16]   : C_FE_RFIC ǿ�Ʒ������塣cpu_rfic_ssi_force_en=1ʱ����Ч�� */
        unsigned long  reserved_1               : 15; /* bit[17-31]: ���� */
    } reg;
} CBBP_RFIC_SSI_START_UNION;
#define CBBP_RFIC_SSI_START_cpu_rfic_ssi_page_start_START   (0)
#define CBBP_RFIC_SSI_START_cpu_rfic_ssi_page_start_END     (0)
#define CBBP_RFIC_SSI_START_cpu_rfic_ssi_force_pulse_START  (16)
#define CBBP_RFIC_SSI_START_cpu_rfic_ssi_force_pulse_END    (16)


/*****************************************************************************
 �ṹ��    : CBBP_RFIC_SSI_FORCE_UNION
 �ṹ˵��  : RFIC_SSI_FORCE �Ĵ����ṹ���塣��ַƫ����:0x0050����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      rfic_ssi_force_reg;
    struct
    {
        unsigned long  cpu_rfic_ssi_force_data : 25; /* bit[0-24] : C_FE_RFIC ǿ�Ʒ������ݣ�cpu_rfic_ssi_force_en=1ʱ����Ч�� */
        unsigned long  reserved                : 6;  /* bit[25-30]: ���� */
        unsigned long  cpu_rfic_ssi_force_en   : 1;  /* bit[31]   : C_FE_RFIC ǿ�Ʒ���ʹ�ܡ��ر�cpu_rfic_ssi_pro_enʱʹ�ã����߹���״̬����cpu_rfic_ssi_hold_page��ͣ��ʹ�á� */
    } reg;
} CBBP_RFIC_SSI_FORCE_UNION;
#define CBBP_RFIC_SSI_FORCE_cpu_rfic_ssi_force_data_START  (0)
#define CBBP_RFIC_SSI_FORCE_cpu_rfic_ssi_force_data_END    (24)
#define CBBP_RFIC_SSI_FORCE_cpu_rfic_ssi_force_en_START    (31)
#define CBBP_RFIC_SSI_FORCE_cpu_rfic_ssi_force_en_END      (31)


/*****************************************************************************
 �ṹ��    : CBBP_RFIC_STATE_RPT_UNION
 �ṹ˵��  : RFIC_STATE_RPT �Ĵ����ṹ���塣��ַƫ����:0x0054����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      rfic_state_rpt_reg;
    struct
    {
        unsigned long  rfic_ssi_curr_state_rpt : 3;  /* bit[0-2]  : rfic_ssi RAM����״̬�ϱ��� */
        unsigned long  reserved_0              : 1;  /* bit[3]    : ���� */
        unsigned long  rfic_ssi_page_sel_rpt   : 1;  /* bit[4]    : BBP��ǰʹ��ƹ��RAM״̬�ϱ��� */
        unsigned long  rfic_rd_ctrl_buff_addr  : 7;  /* bit[5-11] : ��ǰִ�е���rfic_ctrl buff�ĵ�ַ */
        unsigned long  rfic_err_config_rpt     : 3;  /* bit[12-14]: �쳣����״̬�ϱ�������ڵ�ǰָ��û��ִ���꣬��̬���ñ���д����ᴥ���쳣�ϱ�����bit����ֱ����£�
                                                                    [12]work_mode_sel���쳣��д
                                                                    [13]buffer_clr_mode���쳣��д
                                                                    [14]data_buffer_start_addr���쳣��д */
        unsigned long  reserved_1              : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_RFIC_STATE_RPT_UNION;
#define CBBP_RFIC_STATE_RPT_rfic_ssi_curr_state_rpt_START  (0)
#define CBBP_RFIC_STATE_RPT_rfic_ssi_curr_state_rpt_END    (2)
#define CBBP_RFIC_STATE_RPT_rfic_ssi_page_sel_rpt_START    (4)
#define CBBP_RFIC_STATE_RPT_rfic_ssi_page_sel_rpt_END      (4)
#define CBBP_RFIC_STATE_RPT_rfic_rd_ctrl_buff_addr_START   (5)
#define CBBP_RFIC_STATE_RPT_rfic_rd_ctrl_buff_addr_END     (11)
#define CBBP_RFIC_STATE_RPT_rfic_err_config_rpt_START      (12)
#define CBBP_RFIC_STATE_RPT_rfic_err_config_rpt_END        (14)


/*****************************************************************************
 �ṹ��    : CBBP_MIPI_START_TIME_UNION
 �ṹ˵��  : MIPI_START_TIME �Ĵ����ṹ���塣��ַƫ����:0x070����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      mipi_start_time_reg;
    struct
    {
        unsigned long  cpu_mipi_auto_run_time : 11; /* bit[0-10] : mipiÿʱ϶t2λ��(sys_cnt)���޷���������Χ[0,1535��2047]����λchip��BBP�ڴ�λ�ö�MIPI RAM��ҳ������ʼ����RAM�����ַ������ݡ� */
        unsigned long  reserved               : 21; /* bit[11-31]: ���� */
    } reg;
} CBBP_MIPI_START_TIME_UNION;
#define CBBP_MIPI_START_TIME_cpu_mipi_auto_run_time_START  (0)
#define CBBP_MIPI_START_TIME_cpu_mipi_auto_run_time_END    (10)


/*****************************************************************************
 �ṹ��    : CBBP_MIPI_STA_CFG_UNION
 �ṹ˵��  : MIPI_STA_CFG �Ĵ����ṹ���塣��ַƫ����:0x074����ֵ:0x00001902�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      mipi_sta_cfg_reg;
    struct
    {
        unsigned long  cpu_mipi_work_mode_sel          : 1;  /* bit[0]    : 0:��ѯģʽ��DSPд��RAM���������ͣ�BBPѭ����������ctrlbuffer��ֱ��ȫ�����ݷ�����ɡ�
                                                                            1:�������ģʽ��DSP����ʱ϶��Ҫ���͵��������ݰ���Чʱ����ǰ�����������RAM�У�BBPֻ����һ��ctrlbuffer������ִ�С� */
        unsigned long  cpu_mipi_buffer_clr_mode        : 1;  /* bit[1]    : 0:ctrl_buffִ��������㣬1:ctrl_buffִ��������� */
        unsigned long  cpu_mipi_buffer_mode            : 1;  /* bit[2]    : 0:ÿ��ctrl_buff��Ӧ���3�����ݡ�1:ÿ��ctrl_buff��Ӧ���1�����ݡ� */
        unsigned long  reserved_0                      : 1;  /* bit[3]    : ���� */
        unsigned long  cpu_mipi_data_buffer_start_addr : 7;  /* bit[4-10] : ÿ��ƹ��RAM��data_buffer��ʼ��ַ�� */
        unsigned long  cpu_mipi_page_switch_en         : 1;  /* bit[11]   : ��ҳʹ�ܣ�0:����ҳ�������BBP��ʹ�õͶ�RAM��1����ҳ�������BBPƹ��ʹ�øߵ�����RAM�� */
        unsigned long  cpu_mipi_auto_run               : 1;  /* bit[12]   : �Զ���ҳʹ�ܣ�0��������������ֶ���ҳ��1�����������ʱ���Զ���ҳ�� */
        unsigned long  reserved_1                      : 19; /* bit[13-31]: ���� */
    } reg;
} CBBP_MIPI_STA_CFG_UNION;
#define CBBP_MIPI_STA_CFG_cpu_mipi_work_mode_sel_START           (0)
#define CBBP_MIPI_STA_CFG_cpu_mipi_work_mode_sel_END             (0)
#define CBBP_MIPI_STA_CFG_cpu_mipi_buffer_clr_mode_START         (1)
#define CBBP_MIPI_STA_CFG_cpu_mipi_buffer_clr_mode_END           (1)
#define CBBP_MIPI_STA_CFG_cpu_mipi_buffer_mode_START             (2)
#define CBBP_MIPI_STA_CFG_cpu_mipi_buffer_mode_END               (2)
#define CBBP_MIPI_STA_CFG_cpu_mipi_data_buffer_start_addr_START  (4)
#define CBBP_MIPI_STA_CFG_cpu_mipi_data_buffer_start_addr_END    (10)
#define CBBP_MIPI_STA_CFG_cpu_mipi_page_switch_en_START          (11)
#define CBBP_MIPI_STA_CFG_cpu_mipi_page_switch_en_END            (11)
#define CBBP_MIPI_STA_CFG_cpu_mipi_auto_run_START                (12)
#define CBBP_MIPI_STA_CFG_cpu_mipi_auto_run_END                  (12)


/*****************************************************************************
 �ṹ��    : CBBP_MIPI_DYN_CFG_UNION
 �ṹ˵��  : MIPI_DYN_CFG �Ĵ����ṹ���塣��ַƫ����:0x078����ֵ:0x00000080�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      mipi_dyn_cfg_reg;
    struct
    {
        unsigned long  cpu_mipi_pro_en    : 1;  /* bit[0]   : ģ�鹤��ʹ�ܣ��ߵ�ƽ��Ч�� */
        unsigned long  reserved_0         : 3;  /* bit[1-3] : ���� */
        unsigned long  cpu_mipi_hold_page : 1;  /* bit[4]   : 1��ʾ��ͣ���͵�ǰRAM�����ݡ��÷���cpu_rfic_ssi_hold_page */
        unsigned long  reserved_1         : 1;  /* bit[5]   : ���� */
        unsigned long  cpu_mipi_stop_page : 1;  /* bit[6]   : 1��ʾֹͣ���͵�ǰRAM�����ݲ������ǰRAM�������ݡ� */
        unsigned long  cpu_mipi_stop_mode : 1;  /* bit[7]   : ֹͣ����ģʽ��0��ʾ����ֹͣ�����������ݣ�1��ʾ��ǰctrl_buff��Ӧ���ݷ�����ɺ���ֹͣ�� */
        unsigned long  reserved_2         : 24; /* bit[8-31]: ���� */
    } reg;
} CBBP_MIPI_DYN_CFG_UNION;
#define CBBP_MIPI_DYN_CFG_cpu_mipi_pro_en_START     (0)
#define CBBP_MIPI_DYN_CFG_cpu_mipi_pro_en_END       (0)
#define CBBP_MIPI_DYN_CFG_cpu_mipi_hold_page_START  (4)
#define CBBP_MIPI_DYN_CFG_cpu_mipi_hold_page_END    (4)
#define CBBP_MIPI_DYN_CFG_cpu_mipi_stop_page_START  (6)
#define CBBP_MIPI_DYN_CFG_cpu_mipi_stop_page_END    (6)
#define CBBP_MIPI_DYN_CFG_cpu_mipi_stop_mode_START  (7)
#define CBBP_MIPI_DYN_CFG_cpu_mipi_stop_mode_END    (7)


/*****************************************************************************
 �ṹ��    : CBBP_MIPI_START_UNION
 �ṹ˵��  : MIPI_START �Ĵ����ṹ���塣��ַƫ����:0x07C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      mipi_start_reg;
    struct
    {
        unsigned long  cpu_mipi_page_start  : 1;  /* bit[0]   : д1���������źţ��ֶ�����ָ��ҳִ�У�cpu_mipi_auto_run=0ʱ����Ч�� */
        unsigned long  reserved_0           : 3;  /* bit[1-3] : ���� */
        unsigned long  cpu_mipi_force_pulse : 1;  /* bit[4]   : C_FE_MIPI ǿ�Ʒ������塣cpu_mipi_force_en=1ʱ����Ч�� */
        unsigned long  reserved_1           : 27; /* bit[5-31]: ���� */
    } reg;
} CBBP_MIPI_START_UNION;
#define CBBP_MIPI_START_cpu_mipi_page_start_START   (0)
#define CBBP_MIPI_START_cpu_mipi_page_start_END     (0)
#define CBBP_MIPI_START_cpu_mipi_force_pulse_START  (4)
#define CBBP_MIPI_START_cpu_mipi_force_pulse_END    (4)


/*****************************************************************************
 �ṹ��    : CBBP_MIPI_FORCE_EN_UNION
 �ṹ˵��  : MIPI_FORCE_EN �Ĵ����ṹ���塣��ַƫ����:0x080����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      mipi_force_en_reg;
    struct
    {
        unsigned long  cpu_mipi_force_en : 1;  /* bit[0]   : C_FE_MIPI ǿ�Ʒ���ʹ�ܡ��ر�cpu_mipi_pro_enʱʹ�ã����߹���״̬����cpu_mipi_hold_page��ͣ��ʹ�á�
                                                             ǿ��ʱ��mipi_force_data��������64bit���ߵͶ����ã���������ݲ���32bit���������ڸ�32bit���ҵ�32bit����Ϊ0�� */
        unsigned long  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_MIPI_FORCE_EN_UNION;
#define CBBP_MIPI_FORCE_EN_cpu_mipi_force_en_START  (0)
#define CBBP_MIPI_FORCE_EN_cpu_mipi_force_en_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_MIPI_STATE_RPT_UNION
 �ṹ˵��  : MIPI_STATE_RPT �Ĵ����ṹ���塣��ַƫ����:0x08C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      mipi_state_rpt_reg;
    struct
    {
        unsigned long  mipi_curr_state_rpt    : 3;  /* bit[0-2]  : mipi RAM���Ƶ�״̬���ϱ��� */
        unsigned long  reserved_0             : 1;  /* bit[3]    : ���� */
        unsigned long  mipi_page_sel_rpt      : 1;  /* bit[4]    : BBP��ǰʹ��RAM��ƹ��״̬�ϱ��� */
        unsigned long  mipi_rd_ctrl_buff_addr : 7;  /* bit[5-11] : ��ǰִ�е���rfic_ctrl buff�ĵ�ַ */
        unsigned long  mipi_err_config_rpt    : 3;  /* bit[12-14]: �쳣����״̬�ϱ�������ڵ�ǰָ��û��ִ���꣬��̬���ñ���д����ᴥ���쳣�ϱ�����bit����ֱ����£�
                                                                   [12]work_mode_sel���쳣��д
                                                                   [13]buffer_clr_mode���쳣��д
                                                                   [14]data_buffer_start_addr���쳣��д */
        unsigned long  reserved_1             : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_MIPI_STATE_RPT_UNION;
#define CBBP_MIPI_STATE_RPT_mipi_curr_state_rpt_START     (0)
#define CBBP_MIPI_STATE_RPT_mipi_curr_state_rpt_END       (2)
#define CBBP_MIPI_STATE_RPT_mipi_page_sel_rpt_START       (4)
#define CBBP_MIPI_STATE_RPT_mipi_page_sel_rpt_END         (4)
#define CBBP_MIPI_STATE_RPT_mipi_rd_ctrl_buff_addr_START  (5)
#define CBBP_MIPI_STATE_RPT_mipi_rd_ctrl_buff_addr_END    (11)
#define CBBP_MIPI_STATE_RPT_mipi_err_config_rpt_START     (12)
#define CBBP_MIPI_STATE_RPT_mipi_err_config_rpt_END       (14)


/*****************************************************************************
 �ṹ��    : CBBP_GPIO_START_TIME_UNION
 �ṹ˵��  : GPIO_START_TIME �Ĵ����ṹ���塣��ַƫ����:0x0A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      gpio_start_time_reg;
    struct
    {
        unsigned long  cpu_gpio_auto_run_time : 11; /* bit[0-10] : GPIOÿʱ϶t2λ��(sys_cnt)���޷���������Χ[0,1535��2047]����λchip��BBP�ڴ�λ�ö�GPIO RAM��ҳ������ʼ����RAM�����ַ������ݡ� */
        unsigned long  reserved               : 21; /* bit[11-31]: ���� */
    } reg;
} CBBP_GPIO_START_TIME_UNION;
#define CBBP_GPIO_START_TIME_cpu_gpio_auto_run_time_START  (0)
#define CBBP_GPIO_START_TIME_cpu_gpio_auto_run_time_END    (10)


/*****************************************************************************
 �ṹ��    : CBBP_GPIO_STA_CFG_UNION
 �ṹ˵��  : GPIO_STA_CFG �Ĵ����ṹ���塣��ַƫ����:0x0A4����ֵ:0x00000600�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      gpio_sta_cfg_reg;
    struct
    {
        unsigned long  cpu_gpio_work_mode_sel          : 1;  /* bit[0]    : 0:��ѯģʽ��DSPд��RAM���������ͣ�BBPѭ����������ctrlbuffer��ֱ��ȫ�����ݷ�����ɡ�
                                                                            1:�������ģʽ��DSP����ʱ϶��Ҫ���͵��������ݰ���Чʱ����ǰ�����������RAM�У�BBPֻ����һ��ctrlbuffer������ִ�С� */
        unsigned long  cpu_gpio_buffer_clr_mode        : 1;  /* bit[1]    : 0:ctrl_buffִ��������㣬1:ctrl_buffִ��������� */
        unsigned long  reserved_0                      : 2;  /* bit[2-3]  : ���� */
        unsigned long  cpu_gpio_data_buffer_start_addr : 6;  /* bit[4-9]  : ÿ��ƹ��RAM��data_buffer��ʼ��ַ�� */
        unsigned long  cpu_gpio_page_switch_en         : 1;  /* bit[10]   : ��ҳʹ�ܣ�0:����ҳ�������BBP��ʹ�õͶ�RAM��1����ҳ�������BBPƹ��ʹ�øߵ�����RAM�� */
        unsigned long  cpu_gpio_auto_run               : 1;  /* bit[11]   : �Զ���ҳʹ�ܣ�0��������������ֶ���ҳ��1�����������ʱ���Զ���ҳ�� */
        unsigned long  reserved_1                      : 20; /* bit[12-31]: ���� */
    } reg;
} CBBP_GPIO_STA_CFG_UNION;
#define CBBP_GPIO_STA_CFG_cpu_gpio_work_mode_sel_START           (0)
#define CBBP_GPIO_STA_CFG_cpu_gpio_work_mode_sel_END             (0)
#define CBBP_GPIO_STA_CFG_cpu_gpio_buffer_clr_mode_START         (1)
#define CBBP_GPIO_STA_CFG_cpu_gpio_buffer_clr_mode_END           (1)
#define CBBP_GPIO_STA_CFG_cpu_gpio_data_buffer_start_addr_START  (4)
#define CBBP_GPIO_STA_CFG_cpu_gpio_data_buffer_start_addr_END    (9)
#define CBBP_GPIO_STA_CFG_cpu_gpio_page_switch_en_START          (10)
#define CBBP_GPIO_STA_CFG_cpu_gpio_page_switch_en_END            (10)
#define CBBP_GPIO_STA_CFG_cpu_gpio_auto_run_START                (11)
#define CBBP_GPIO_STA_CFG_cpu_gpio_auto_run_END                  (11)


/*****************************************************************************
 �ṹ��    : CBBP_GPIO_DYN_CFG_UNION
 �ṹ˵��  : GPIO_DYN_CFG �Ĵ����ṹ���塣��ַƫ����:0x0A8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      gpio_dyn_cfg_reg;
    struct
    {
        unsigned long  cpu_gpio_pro_en    : 1;  /* bit[0]   : ģ�鹤��ʹ�ܣ��ߵ�ƽ��Ч�� */
        unsigned long  reserved_0         : 3;  /* bit[1-3] : ���� */
        unsigned long  cpu_gpio_hold_page : 1;  /* bit[4]   : 1��ʾ��ͣ���͵�ǰRAM�����ݡ� */
        unsigned long  reserved_1         : 3;  /* bit[5-7] : ���� */
        unsigned long  cpu_gpio_stop_page : 1;  /* bit[8]   : 1��ʾֹͣ���͵�ǰRAM�����ݲ������ǰRAM�������ݡ� */
        unsigned long  reserved_2         : 23; /* bit[9-31]: ���� */
    } reg;
} CBBP_GPIO_DYN_CFG_UNION;
#define CBBP_GPIO_DYN_CFG_cpu_gpio_pro_en_START     (0)
#define CBBP_GPIO_DYN_CFG_cpu_gpio_pro_en_END       (0)
#define CBBP_GPIO_DYN_CFG_cpu_gpio_hold_page_START  (4)
#define CBBP_GPIO_DYN_CFG_cpu_gpio_hold_page_END    (4)
#define CBBP_GPIO_DYN_CFG_cpu_gpio_stop_page_START  (8)
#define CBBP_GPIO_DYN_CFG_cpu_gpio_stop_page_END    (8)


/*****************************************************************************
 �ṹ��    : CBBP_GPIO_START_UNION
 �ṹ˵��  : GPIO_START �Ĵ����ṹ���塣��ַƫ����:0x0AC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      gpio_start_reg;
    struct
    {
        unsigned long  cpu_gpio_page_start  : 1;  /* bit[0]   : д1���������źţ��ֶ�����ָ��ҳִ�У�cpu_gpio_auto_run=0ʱ����Ч�� */
        unsigned long  reserved_0           : 3;  /* bit[1-3] : ���� */
        unsigned long  cpu_gpio_force_pulse : 1;  /* bit[4]   : C_FE_GPIO ǿ�Ʒ������壬cpu_gpio_force_en=1ʱ����Ч�� */
        unsigned long  reserved_1           : 27; /* bit[5-31]: ���� */
    } reg;
} CBBP_GPIO_START_UNION;
#define CBBP_GPIO_START_cpu_gpio_page_start_START   (0)
#define CBBP_GPIO_START_cpu_gpio_page_start_END     (0)
#define CBBP_GPIO_START_cpu_gpio_force_pulse_START  (4)
#define CBBP_GPIO_START_cpu_gpio_force_pulse_END    (4)


/*****************************************************************************
 �ṹ��    : CBBP_GPIO_FORCE_EN_UNION
 �ṹ˵��  : GPIO_FORCE_EN �Ĵ����ṹ���塣��ַƫ����:0x0B0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      gpio_force_en_reg;
    struct
    {
        unsigned long  reserved          : 31; /* bit[0-30]: ���� */
        unsigned long  cpu_gpio_force_en : 1;  /* bit[31]  : C_FE_GPIO ǿ�Ʒ���ʹ�ܣ��ر�cpu_gpio_pro_enʱʹ�ã����߹���״̬����cpu_gpio_hold_page��ͣ��ʹ�á� */
    } reg;
} CBBP_GPIO_FORCE_EN_UNION;
#define CBBP_GPIO_FORCE_EN_cpu_gpio_force_en_START  (31)
#define CBBP_GPIO_FORCE_EN_cpu_gpio_force_en_END    (31)


/*****************************************************************************
 �ṹ��    : CBBP_GPIO_STATE_RPT_UNION
 �ṹ˵��  : GPIO_STATE_RPT �Ĵ����ṹ���塣��ַƫ����:0x0B8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      gpio_state_rpt_reg;
    struct
    {
        unsigned long  gpio_curr_state_rpt    : 3;  /* bit[0-2]  : gpio RAM����״̬�ϱ��� */
        unsigned long  reserved_0             : 1;  /* bit[3]    : ���� */
        unsigned long  gpio_page_sel_rpt      : 1;  /* bit[4]    : BBP��ǰʹ��ƹ��RAM״̬�ϱ��� */
        unsigned long  gpio_rd_ctrl_buff_addr : 6;  /* bit[5-10] : ��ǰִ�е���gpio_ctrl buff�ĵ�ַ */
        unsigned long  reserved_1             : 1;  /* bit[11]   : ���� */
        unsigned long  gpio_err_config_rpt    : 3;  /* bit[12-14]: �쳣����״̬�ϱ�������ڵ�ǰָ��û��ִ���꣬��̬���ñ���д����ᴥ���쳣�ϱ�����bit����ֱ����£�
                                                                   [12]work_mode_sel���쳣��д
                                                                   [13]buffer_clr_mode���쳣��д
                                                                   [14]data_buffer_start_addr���쳣��д */
        unsigned long  reserved_2             : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_GPIO_STATE_RPT_UNION;
#define CBBP_GPIO_STATE_RPT_gpio_curr_state_rpt_START     (0)
#define CBBP_GPIO_STATE_RPT_gpio_curr_state_rpt_END       (2)
#define CBBP_GPIO_STATE_RPT_gpio_page_sel_rpt_START       (4)
#define CBBP_GPIO_STATE_RPT_gpio_page_sel_rpt_END         (4)
#define CBBP_GPIO_STATE_RPT_gpio_rd_ctrl_buff_addr_START  (5)
#define CBBP_GPIO_STATE_RPT_gpio_rd_ctrl_buff_addr_END    (10)
#define CBBP_GPIO_STATE_RPT_gpio_err_config_rpt_START     (12)
#define CBBP_GPIO_STATE_RPT_gpio_err_config_rpt_END       (14)


/*****************************************************************************
 �ṹ��    : CBBP_GPIO_ANTPA_RPT_UNION
 �ṹ˵��  : GPIO_ANTPA_RPT �Ĵ����ṹ���塣��ַƫ����:0x0BC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      gpio_antpa_rpt_reg;
    struct
    {
        unsigned long  gpio_antpa_sel_rpt : 31; /* bit[0-30]: �����߿�(antpa)�����ϱ��� */
        unsigned long  reserved           : 1;  /* bit[31]  : ���� */
    } reg;
} CBBP_GPIO_ANTPA_RPT_UNION;
#define CBBP_GPIO_ANTPA_RPT_gpio_antpa_sel_rpt_START  (0)
#define CBBP_GPIO_ANTPA_RPT_gpio_antpa_sel_rpt_END    (30)


/*****************************************************************************
 �ṹ��    : CBBP_GPIO_LINE_CTRL_RPT_UNION
 �ṹ˵��  : GPIO_LINE_CTRL_RPT �Ĵ����ṹ���塣��ַƫ����:0x0C0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      gpio_line_ctrl_rpt_reg;
    struct
    {
        unsigned long  gpio_line_ctrl_rpt : 31; /* bit[0-30]: ר���߿أ�gpio�߿أ��ϱ���bit[0]:c_abb0_rxa_en,ABB Aͨ������ʹ��
                                                              bit[1]:c_abb0_rxb_en,ABB Bͨ������ʹ��
                                                              bit[2]:c_abb0_rxa_blk_en,ABB Aͨ��Block����ʹ��
                                                              bit[3]:c_abb0_rxb_blk_en,ABB Bͨ��Block����ʹ��
                                                              bit[4]:c_abb0_tx_en,ABB ����ͨ������ʹ��
                                                              bit[5]:c2com_rf0_tcvr_on,RF �ܹ���ʹ��
                                                              bit[6]:c2com_rf0_tx_en,RF TX����ʹ��
                                                              bit[30:7]:���� */
        unsigned long  reserved           : 1;  /* bit[31]  : ���� */
    } reg;
} CBBP_GPIO_LINE_CTRL_RPT_UNION;
#define CBBP_GPIO_LINE_CTRL_RPT_gpio_line_ctrl_rpt_START  (0)
#define CBBP_GPIO_LINE_CTRL_RPT_gpio_line_ctrl_rpt_END    (30)


/*****************************************************************************
 �ṹ��    : CBBP_HKADC_START_TIME_UNION
 �ṹ˵��  : HKADC_START_TIME �Ĵ����ṹ���塣��ַƫ����:0x0D0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_start_time_reg;
    struct
    {
        unsigned long  cpu_hkadc_ssi_auto_run_time : 11; /* bit[0-10] : HKADC SSIÿʱ϶t2λ��(sys_cnt)���޷���������Χ[0,1535��2047]����λchip��BBP�ڴ�λ�ö�HKADC SSI RAM���·��ͣ�����ʼ����RAM�����ַ������ݡ�
                                                                        ע�⣺��G SDRģʽ���ò���������active_time��ͬ */
        unsigned long  reserved                    : 21; /* bit[11-31]: ���� */
    } reg;
} CBBP_HKADC_START_TIME_UNION;
#define CBBP_HKADC_START_TIME_cpu_hkadc_ssi_auto_run_time_START  (0)
#define CBBP_HKADC_START_TIME_cpu_hkadc_ssi_auto_run_time_END    (10)


/*****************************************************************************
 �ṹ��    : CBBP_HKADC_STA_CFG_UNION
 �ṹ˵��  : HKADC_STA_CFG �Ĵ����ṹ���塣��ַƫ����:0x0D4����ֵ:0x00000400�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_sta_cfg_reg;
    struct
    {
        unsigned long  reserved_0                           : 4;  /* bit[0-3]  : ���� */
        unsigned long  cpu_hkadc_ssi_data_buffer_start_addr : 7;  /* bit[4-10] : ÿ��ƹ��RAM��data_buffer��ʼ��ַ�� */
        unsigned long  reserved_1                           : 5;  /* bit[11-15]: ���� */
        unsigned long  cpu_hkadc_ssi_clk_cfg                : 3;  /* bit[16-18]: hkadc ssi��ʱ��������λssi clock���ڡ� */
        unsigned long  cpu_hkadc_ssi_auto_run               : 1;  /* bit[19]   : �Զ�����ʹ�ܣ�0��������������ֶ����У�1�����������ʱ���Զ����С� */
        unsigned long  reserved_2                           : 12; /* bit[20-31]: ���� */
    } reg;
} CBBP_HKADC_STA_CFG_UNION;
#define CBBP_HKADC_STA_CFG_cpu_hkadc_ssi_data_buffer_start_addr_START  (4)
#define CBBP_HKADC_STA_CFG_cpu_hkadc_ssi_data_buffer_start_addr_END    (10)
#define CBBP_HKADC_STA_CFG_cpu_hkadc_ssi_clk_cfg_START                 (16)
#define CBBP_HKADC_STA_CFG_cpu_hkadc_ssi_clk_cfg_END                   (18)
#define CBBP_HKADC_STA_CFG_cpu_hkadc_ssi_auto_run_START                (19)
#define CBBP_HKADC_STA_CFG_cpu_hkadc_ssi_auto_run_END                  (19)


/*****************************************************************************
 �ṹ��    : CBBP_HKADC_DYN_CFG_UNION
 �ṹ˵��  : HKADC_DYN_CFG �Ĵ����ṹ���塣��ַƫ����:0x0D8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_dyn_cfg_reg;
    struct
    {
        unsigned long  cpu_hkadc_ssi_pro_en    : 1;  /* bit[0]   : ģ�鹤��ʹ�ܣ��ߵ�ƽ��Ч�� */
        unsigned long  reserved_0              : 3;  /* bit[1-3] : ���� */
        unsigned long  cpu_hkadc_ssi_hold_page : 1;  /* bit[4]   : 1��ʾ��ͣ���͵�ǰRAM�����ݡ��÷�ͬcpu_rfic_ssi_hold_page */
        unsigned long  reserved_1              : 3;  /* bit[5-7] : ���� */
        unsigned long  cpu_hkadc_ssi_stop_page : 1;  /* bit[8]   : 1��ʾֹͣ���͵�ǰRAM�����ݲ������ǰRAM�������ݡ� */
        unsigned long  reserved_2              : 23; /* bit[9-31]: ���� */
    } reg;
} CBBP_HKADC_DYN_CFG_UNION;
#define CBBP_HKADC_DYN_CFG_cpu_hkadc_ssi_pro_en_START     (0)
#define CBBP_HKADC_DYN_CFG_cpu_hkadc_ssi_pro_en_END       (0)
#define CBBP_HKADC_DYN_CFG_cpu_hkadc_ssi_hold_page_START  (4)
#define CBBP_HKADC_DYN_CFG_cpu_hkadc_ssi_hold_page_END    (4)
#define CBBP_HKADC_DYN_CFG_cpu_hkadc_ssi_stop_page_START  (8)
#define CBBP_HKADC_DYN_CFG_cpu_hkadc_ssi_stop_page_END    (8)


/*****************************************************************************
 �ṹ��    : CBBP_HKADC_START_UNION
 �ṹ˵��  : HKADC_START �Ĵ����ṹ���塣��ַƫ����:0x0DC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_start_reg;
    struct
    {
        unsigned long  cpu_hkadc_ssi_page_start : 1;  /* bit[0]   : д1���������źţ��ֶ�����ָ��ҳִ�У�cpu_hkadc_ssi_auto_run=0ʱ����Ч�� */
        unsigned long  reserved_0               : 4;  /* bit[1-4] : ���� */
        unsigned long  reserved_1               : 27; /* bit[5-31]: ���� */
    } reg;
} CBBP_HKADC_START_UNION;
#define CBBP_HKADC_START_cpu_hkadc_ssi_page_start_START  (0)
#define CBBP_HKADC_START_cpu_hkadc_ssi_page_start_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_HKADC_FORCE_UNION
 �ṹ˵��  : HKADC_FORCE �Ĵ����ṹ���塣��ַƫ����:0x0E0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_force_reg;
    struct
    {
        unsigned long  cpu_hkadc_ssi_force_data  : 17; /* bit[0-16] : C_HKADC_SSI ǿ�Ʒ������ݣ�cpu_hkadc_force_en=1ʱ����Ч�� */
        unsigned long  reserved                  : 13; /* bit[17-29]: ���� */
        unsigned long  cpu_hkadc_ssi_force_pulse : 1;  /* bit[30]   : C_HKADC_SSI ǿ�Ʒ������� */
        unsigned long  cpu_hkadc_ssi_force_en    : 1;  /* bit[31]   : C_HKADC_SSI ǿ�Ʒ���ʹ�ܣ���ͬʱ����cpu_hkadc_ssi_pro_en=1�����߹���״̬����cpu_hkadc_ssi_hold_page��ͣ��ʹ�á� */
    } reg;
} CBBP_HKADC_FORCE_UNION;
#define CBBP_HKADC_FORCE_cpu_hkadc_ssi_force_data_START   (0)
#define CBBP_HKADC_FORCE_cpu_hkadc_ssi_force_data_END     (16)
#define CBBP_HKADC_FORCE_cpu_hkadc_ssi_force_pulse_START  (30)
#define CBBP_HKADC_FORCE_cpu_hkadc_ssi_force_pulse_END    (30)
#define CBBP_HKADC_FORCE_cpu_hkadc_ssi_force_en_START     (31)
#define CBBP_HKADC_FORCE_cpu_hkadc_ssi_force_en_END       (31)


/*****************************************************************************
 �ṹ��    : CBBP_HKADC_RD_WAIT_UNION
 �ṹ˵��  : HKADC_RD_WAIT �Ĵ����ṹ���塣��ַƫ����:0x0E4����ֵ:0x0000002A�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_rd_wait_reg;
    struct
    {
        unsigned long  cpu_hkadc_ssi_rd_wait_time : 9;  /* bit[0-8] : ���ӳ�ʱ�䣬��λ 19Mclock���� */
        unsigned long  reserved                   : 23; /* bit[9-31]: ���� */
    } reg;
} CBBP_HKADC_RD_WAIT_UNION;
#define CBBP_HKADC_RD_WAIT_cpu_hkadc_ssi_rd_wait_time_START  (0)
#define CBBP_HKADC_RD_WAIT_cpu_hkadc_ssi_rd_wait_time_END    (8)


/*****************************************************************************
 �ṹ��    : CBBP_HKADC_CLR_UNION
 �ṹ˵��  : HKADC_CLR �Ĵ����ṹ���塣��ַƫ����:0x0E8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_clr_reg;
    struct
    {
        unsigned long  cpu_hkadc_ssi_rd_overtime_clr    : 1;  /* bit[0]   : PD��ʱ��־�������� */
        unsigned long  reserved_0                       : 3;  /* bit[1-3] : ���� */
        unsigned long  cpu_hkadc_ssi_rd_result_flag_clr : 1;  /* bit[4]   : PD�����Ч��־�������� */
        unsigned long  reserved_1                       : 27; /* bit[5-31]: ���� */
    } reg;
} CBBP_HKADC_CLR_UNION;
#define CBBP_HKADC_CLR_cpu_hkadc_ssi_rd_overtime_clr_START     (0)
#define CBBP_HKADC_CLR_cpu_hkadc_ssi_rd_overtime_clr_END       (0)
#define CBBP_HKADC_CLR_cpu_hkadc_ssi_rd_result_flag_clr_START  (4)
#define CBBP_HKADC_CLR_cpu_hkadc_ssi_rd_result_flag_clr_END    (4)


/*****************************************************************************
 �ṹ��    : CBBP_HKADC_FLAG_RPT_UNION
 �ṹ˵��  : HKADC_FLAG_RPT �Ĵ����ṹ���塣��ַƫ����:0x0EC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_flag_rpt_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_overtime_flag_cpu : 1;  /* bit[0]    : PD��ʱ��־���ߵ�ƽ��Ч�� */
        unsigned long  reserved_0                     : 3;  /* bit[1-3]  : ���� */
        unsigned long  hkadc_ssi_rd_result_flag_cpu   : 1;  /* bit[4]    : PD�����Ч��־���ߵ�ƽ��Ч�� */
        unsigned long  reserved_1                     : 3;  /* bit[5-7]  : ���� */
        unsigned long  hkadc_ssi_curr_state_rpt       : 3;  /* bit[8-10] : SSI RAM����״̬�ϱ��� */
        unsigned long  hkadc_rd_ctrl_buff_addr        : 7;  /* bit[11-17]: ��ǰִ�е���hkadc_ctrl buff�ĵ�ַ */
        unsigned long  reserved_2                     : 2;  /* bit[18-19]: ���� */
        unsigned long  hkadc_err_config_rpt           : 3;  /* bit[20-22]: �쳣����״̬�ϱ�������ڵ�ǰָ��û��ִ���꣬��̬���ñ���д����ᴥ���쳣�ϱ�����bit����ֱ����£�
                                                                           [20]work_mode_sel���쳣��д
                                                                           [21]buffer_clr_mode���쳣��д
                                                                           [22]data_buffer_start_addr���쳣��д */
        unsigned long  reserved_3                     : 9;  /* bit[23-31]: ���� */
    } reg;
} CBBP_HKADC_FLAG_RPT_UNION;
#define CBBP_HKADC_FLAG_RPT_hkadc_ssi_rd_overtime_flag_cpu_START  (0)
#define CBBP_HKADC_FLAG_RPT_hkadc_ssi_rd_overtime_flag_cpu_END    (0)
#define CBBP_HKADC_FLAG_RPT_hkadc_ssi_rd_result_flag_cpu_START    (4)
#define CBBP_HKADC_FLAG_RPT_hkadc_ssi_rd_result_flag_cpu_END      (4)
#define CBBP_HKADC_FLAG_RPT_hkadc_ssi_curr_state_rpt_START        (8)
#define CBBP_HKADC_FLAG_RPT_hkadc_ssi_curr_state_rpt_END          (10)
#define CBBP_HKADC_FLAG_RPT_hkadc_rd_ctrl_buff_addr_START         (11)
#define CBBP_HKADC_FLAG_RPT_hkadc_rd_ctrl_buff_addr_END           (17)
#define CBBP_HKADC_FLAG_RPT_hkadc_err_config_rpt_START            (20)
#define CBBP_HKADC_FLAG_RPT_hkadc_err_config_rpt_END              (22)


/*****************************************************************************
 �ṹ��    : CBBP_HKADC_RESULT0_1_UNION
 �ṹ˵��  : HKADC_RESULT0_1 �Ĵ����ṹ���塣��ַƫ����:0x0100����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_result0_1_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_result_0_cpu : 16; /* bit[0-15] : ��ʱ϶��0��PD�ض������ */
        unsigned long  hkadc_ssi_rd_result_1_cpu : 16; /* bit[16-31]: ��ʱ϶��1��PD�ض����,[13:8]��ʾ����ַ��[7:0]��ʾ�����ݣ��޷���������ͬ�� */
    } reg;
} CBBP_HKADC_RESULT0_1_UNION;
#define CBBP_HKADC_RESULT0_1_hkadc_ssi_rd_result_0_cpu_START  (0)
#define CBBP_HKADC_RESULT0_1_hkadc_ssi_rd_result_0_cpu_END    (15)
#define CBBP_HKADC_RESULT0_1_hkadc_ssi_rd_result_1_cpu_START  (16)
#define CBBP_HKADC_RESULT0_1_hkadc_ssi_rd_result_1_cpu_END    (31)


/*****************************************************************************
 �ṹ��    : CBBP_HKADC_RESULT2_3_UNION
 �ṹ˵��  : HKADC_RESULT2_3 �Ĵ����ṹ���塣��ַƫ����:0x0104����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_result2_3_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_result_2_cpu : 16; /* bit[0-15] : ��ʱ϶��2��PD�ض������ */
        unsigned long  hkadc_ssi_rd_result_3_cpu : 16; /* bit[16-31]: ��ʱ϶��3��PD�ض������ */
    } reg;
} CBBP_HKADC_RESULT2_3_UNION;
#define CBBP_HKADC_RESULT2_3_hkadc_ssi_rd_result_2_cpu_START  (0)
#define CBBP_HKADC_RESULT2_3_hkadc_ssi_rd_result_2_cpu_END    (15)
#define CBBP_HKADC_RESULT2_3_hkadc_ssi_rd_result_3_cpu_START  (16)
#define CBBP_HKADC_RESULT2_3_hkadc_ssi_rd_result_3_cpu_END    (31)


/*****************************************************************************
 �ṹ��    : CBBP_HKADC_RESULT4_5_UNION
 �ṹ˵��  : HKADC_RESULT4_5 �Ĵ����ṹ���塣��ַƫ����:0x0108����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_result4_5_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_result_4_cpu : 16; /* bit[0-15] : ��ʱ϶��4��PD�ض������ */
        unsigned long  hkadc_ssi_rd_result_5_cpu : 16; /* bit[16-31]: ��ʱ϶��5��PD�ض������ */
    } reg;
} CBBP_HKADC_RESULT4_5_UNION;
#define CBBP_HKADC_RESULT4_5_hkadc_ssi_rd_result_4_cpu_START  (0)
#define CBBP_HKADC_RESULT4_5_hkadc_ssi_rd_result_4_cpu_END    (15)
#define CBBP_HKADC_RESULT4_5_hkadc_ssi_rd_result_5_cpu_START  (16)
#define CBBP_HKADC_RESULT4_5_hkadc_ssi_rd_result_5_cpu_END    (31)


/*****************************************************************************
 �ṹ��    : CBBP_HKADC_RESULT6_7_UNION
 �ṹ˵��  : HKADC_RESULT6_7 �Ĵ����ṹ���塣��ַƫ����:0x010C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_result6_7_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_result_6_cpu : 16; /* bit[0-15] : ��ʱ϶��6��PD�ض������ */
        unsigned long  hkadc_ssi_rd_result_7_cpu : 16; /* bit[16-31]: ��ʱ϶��7��PD�ض������ */
    } reg;
} CBBP_HKADC_RESULT6_7_UNION;
#define CBBP_HKADC_RESULT6_7_hkadc_ssi_rd_result_6_cpu_START  (0)
#define CBBP_HKADC_RESULT6_7_hkadc_ssi_rd_result_6_cpu_END    (15)
#define CBBP_HKADC_RESULT6_7_hkadc_ssi_rd_result_7_cpu_START  (16)
#define CBBP_HKADC_RESULT6_7_hkadc_ssi_rd_result_7_cpu_END    (31)


/*****************************************************************************
 �ṹ��    : CBBP_HKADC_RESULT8_9_UNION
 �ṹ˵��  : HKADC_RESULT8_9 �Ĵ����ṹ���塣��ַƫ����:0x0110����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_result8_9_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_result_8_cpu : 16; /* bit[0-15] : ��ʱ϶��8��PD�ض������ */
        unsigned long  hkadc_ssi_rd_result_9_cpu : 16; /* bit[16-31]: ��ʱ϶��9��PD�ض������ */
    } reg;
} CBBP_HKADC_RESULT8_9_UNION;
#define CBBP_HKADC_RESULT8_9_hkadc_ssi_rd_result_8_cpu_START  (0)
#define CBBP_HKADC_RESULT8_9_hkadc_ssi_rd_result_8_cpu_END    (15)
#define CBBP_HKADC_RESULT8_9_hkadc_ssi_rd_result_9_cpu_START  (16)
#define CBBP_HKADC_RESULT8_9_hkadc_ssi_rd_result_9_cpu_END    (31)


/*****************************************************************************
 �ṹ��    : CBBP_HKADC_RESULT10_11_UNION
 �ṹ˵��  : HKADC_RESULT10_11 �Ĵ����ṹ���塣��ַƫ����:0x0114����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_result10_11_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_result_10_cpu : 16; /* bit[0-15] : ��ʱ϶��10��PD�ض������ */
        unsigned long  hkadc_ssi_rd_result_11_cpu : 16; /* bit[16-31]: ��ʱ϶��11��PD�ض������ */
    } reg;
} CBBP_HKADC_RESULT10_11_UNION;
#define CBBP_HKADC_RESULT10_11_hkadc_ssi_rd_result_10_cpu_START  (0)
#define CBBP_HKADC_RESULT10_11_hkadc_ssi_rd_result_10_cpu_END    (15)
#define CBBP_HKADC_RESULT10_11_hkadc_ssi_rd_result_11_cpu_START  (16)
#define CBBP_HKADC_RESULT10_11_hkadc_ssi_rd_result_11_cpu_END    (31)


/*****************************************************************************
 �ṹ��    : CBBP_HKADC_RESUL12_13_UNION
 �ṹ˵��  : HKADC_RESUL12_13 �Ĵ����ṹ���塣��ַƫ����:0x0118����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_resul12_13_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_result_12_cpu : 16; /* bit[0-15] : ��ʱ϶��12��PD�ض������ */
        unsigned long  hkadc_ssi_rd_result_13_cpu : 16; /* bit[16-31]: ��ʱ϶��13��PD�ض������ */
    } reg;
} CBBP_HKADC_RESUL12_13_UNION;
#define CBBP_HKADC_RESUL12_13_hkadc_ssi_rd_result_12_cpu_START  (0)
#define CBBP_HKADC_RESUL12_13_hkadc_ssi_rd_result_12_cpu_END    (15)
#define CBBP_HKADC_RESUL12_13_hkadc_ssi_rd_result_13_cpu_START  (16)
#define CBBP_HKADC_RESUL12_13_hkadc_ssi_rd_result_13_cpu_END    (31)


/*****************************************************************************
 �ṹ��    : CBBP_HKADC_RESULT14_15_UNION
 �ṹ˵��  : HKADC_RESULT14_15 �Ĵ����ṹ���塣��ַƫ����:0x011C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_result14_15_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_result_14_cpu : 16; /* bit[0-15] : ��ʱ϶��14��PD�ض������ */
        unsigned long  hkadc_ssi_rd_result_15_cpu : 16; /* bit[16-31]: ��ʱ϶��15��PD�ض������ */
    } reg;
} CBBP_HKADC_RESULT14_15_UNION;
#define CBBP_HKADC_RESULT14_15_hkadc_ssi_rd_result_14_cpu_START  (0)
#define CBBP_HKADC_RESULT14_15_hkadc_ssi_rd_result_14_cpu_END    (15)
#define CBBP_HKADC_RESULT14_15_hkadc_ssi_rd_result_15_cpu_START  (16)
#define CBBP_HKADC_RESULT14_15_hkadc_ssi_rd_result_15_cpu_END    (31)


/*****************************************************************************
 �ṹ��    : CBBP_HKADC_RESULT16_17_UNION
 �ṹ˵��  : HKADC_RESULT16_17 �Ĵ����ṹ���塣��ַƫ����:0x0120����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_result16_17_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_result_16_cpu : 16; /* bit[0-15] : ��ʱ϶��16��PD�ض������ */
        unsigned long  hkadc_ssi_rd_result_17_cpu : 16; /* bit[16-31]: ��ʱ϶��17��PD�ض������ */
    } reg;
} CBBP_HKADC_RESULT16_17_UNION;
#define CBBP_HKADC_RESULT16_17_hkadc_ssi_rd_result_16_cpu_START  (0)
#define CBBP_HKADC_RESULT16_17_hkadc_ssi_rd_result_16_cpu_END    (15)
#define CBBP_HKADC_RESULT16_17_hkadc_ssi_rd_result_17_cpu_START  (16)
#define CBBP_HKADC_RESULT16_17_hkadc_ssi_rd_result_17_cpu_END    (31)


/*****************************************************************************
 �ṹ��    : CBBP_HKADC_RESULT18_19_UNION
 �ṹ˵��  : HKADC_RESULT18_19 �Ĵ����ṹ���塣��ַƫ����:0x0124����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_result18_19_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_result_18_cpu : 16; /* bit[0-15] : ��ʱ϶��08��PD�ض������ */
        unsigned long  hkadc_ssi_rd_result_19_cpu : 16; /* bit[16-31]: ��ʱ϶��19��PD�ض������ */
    } reg;
} CBBP_HKADC_RESULT18_19_UNION;
#define CBBP_HKADC_RESULT18_19_hkadc_ssi_rd_result_18_cpu_START  (0)
#define CBBP_HKADC_RESULT18_19_hkadc_ssi_rd_result_18_cpu_END    (15)
#define CBBP_HKADC_RESULT18_19_hkadc_ssi_rd_result_19_cpu_START  (16)
#define CBBP_HKADC_RESULT18_19_hkadc_ssi_rd_result_19_cpu_END    (31)


/*****************************************************************************
 �ṹ��    : CBBP_HKADC_RESULT20_21_UNION
 �ṹ˵��  : HKADC_RESULT20_21 �Ĵ����ṹ���塣��ַƫ����:0x0128����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_result20_21_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_result_20_cpu : 16; /* bit[0-15] : ��ʱ϶��20��PD�ض������ */
        unsigned long  hkadc_ssi_rd_result_21_cpu : 16; /* bit[16-31]: ��ʱ϶��21��PD�ض������ */
    } reg;
} CBBP_HKADC_RESULT20_21_UNION;
#define CBBP_HKADC_RESULT20_21_hkadc_ssi_rd_result_20_cpu_START  (0)
#define CBBP_HKADC_RESULT20_21_hkadc_ssi_rd_result_20_cpu_END    (15)
#define CBBP_HKADC_RESULT20_21_hkadc_ssi_rd_result_21_cpu_START  (16)
#define CBBP_HKADC_RESULT20_21_hkadc_ssi_rd_result_21_cpu_END    (31)


/*****************************************************************************
 �ṹ��    : CBBP_HKADC_RESULT22_23_UNION
 �ṹ˵��  : HKADC_RESULT22_23 �Ĵ����ṹ���塣��ַƫ����:0x012C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_result22_23_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_result_22_cpu : 16; /* bit[0-15] : ��ʱ϶��22��PD�ض������ */
        unsigned long  hkadc_ssi_rd_result_23_cpu : 16; /* bit[16-31]: ��ʱ϶��23��PD�ض������ */
    } reg;
} CBBP_HKADC_RESULT22_23_UNION;
#define CBBP_HKADC_RESULT22_23_hkadc_ssi_rd_result_22_cpu_START  (0)
#define CBBP_HKADC_RESULT22_23_hkadc_ssi_rd_result_22_cpu_END    (15)
#define CBBP_HKADC_RESULT22_23_hkadc_ssi_rd_result_23_cpu_START  (16)
#define CBBP_HKADC_RESULT22_23_hkadc_ssi_rd_result_23_cpu_END    (31)


/*****************************************************************************
 �ṹ��    : CBBP_HKADC_RESULT24_25_UNION
 �ṹ˵��  : HKADC_RESULT24_25 �Ĵ����ṹ���塣��ַƫ����:0x0130����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_result24_25_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_result_24_cpu : 16; /* bit[0-15] : ��ʱ϶��24��PD�ض������ */
        unsigned long  hkadc_ssi_rd_result_25_cpu : 16; /* bit[16-31]: ��ʱ϶��25��PD�ض������ */
    } reg;
} CBBP_HKADC_RESULT24_25_UNION;
#define CBBP_HKADC_RESULT24_25_hkadc_ssi_rd_result_24_cpu_START  (0)
#define CBBP_HKADC_RESULT24_25_hkadc_ssi_rd_result_24_cpu_END    (15)
#define CBBP_HKADC_RESULT24_25_hkadc_ssi_rd_result_25_cpu_START  (16)
#define CBBP_HKADC_RESULT24_25_hkadc_ssi_rd_result_25_cpu_END    (31)


/*****************************************************************************
 �ṹ��    : CBBP_HKADC_RESULT26_27_UNION
 �ṹ˵��  : HKADC_RESULT26_27 �Ĵ����ṹ���塣��ַƫ����:0x0134����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_result26_27_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_result_26_cpu : 16; /* bit[0-15] : ��ʱ϶��26��PD�ض������ */
        unsigned long  hkadc_ssi_rd_result_27_cpu : 16; /* bit[16-31]: ��ʱ϶��27��PD�ض������ */
    } reg;
} CBBP_HKADC_RESULT26_27_UNION;
#define CBBP_HKADC_RESULT26_27_hkadc_ssi_rd_result_26_cpu_START  (0)
#define CBBP_HKADC_RESULT26_27_hkadc_ssi_rd_result_26_cpu_END    (15)
#define CBBP_HKADC_RESULT26_27_hkadc_ssi_rd_result_27_cpu_START  (16)
#define CBBP_HKADC_RESULT26_27_hkadc_ssi_rd_result_27_cpu_END    (31)


/*****************************************************************************
 �ṹ��    : CBBP_HKADC_RESULT28_29_UNION
 �ṹ˵��  : HKADC_RESULT28_29 �Ĵ����ṹ���塣��ַƫ����:0x0138����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_result28_29_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_result_28_cpu : 16; /* bit[0-15] : ��ʱ϶��28��PD�ض������ */
        unsigned long  hkadc_ssi_rd_result_29_cpu : 16; /* bit[16-31]: ��ʱ϶��29��PD�ض������ */
    } reg;
} CBBP_HKADC_RESULT28_29_UNION;
#define CBBP_HKADC_RESULT28_29_hkadc_ssi_rd_result_28_cpu_START  (0)
#define CBBP_HKADC_RESULT28_29_hkadc_ssi_rd_result_28_cpu_END    (15)
#define CBBP_HKADC_RESULT28_29_hkadc_ssi_rd_result_29_cpu_START  (16)
#define CBBP_HKADC_RESULT28_29_hkadc_ssi_rd_result_29_cpu_END    (31)


/*****************************************************************************
 �ṹ��    : CBBP_HKADC_RESULT30_31_UNION
 �ṹ˵��  : HKADC_RESULT30_31 �Ĵ����ṹ���塣��ַƫ����:0x013C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_result30_31_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_result_30_cpu : 16; /* bit[0-15] : ��ʱ϶��30��PD�ض������ */
        unsigned long  hkadc_ssi_rd_result_31_cpu : 16; /* bit[16-31]: ��ʱ϶��31��PD�ض������ */
    } reg;
} CBBP_HKADC_RESULT30_31_UNION;
#define CBBP_HKADC_RESULT30_31_hkadc_ssi_rd_result_30_cpu_START  (0)
#define CBBP_HKADC_RESULT30_31_hkadc_ssi_rd_result_30_cpu_END    (15)
#define CBBP_HKADC_RESULT30_31_hkadc_ssi_rd_result_31_cpu_START  (16)
#define CBBP_HKADC_RESULT30_31_hkadc_ssi_rd_result_31_cpu_END    (31)


/*****************************************************************************
 �ṹ��    : CBBP_AUXDAC_START_TIME_UNION
 �ṹ˵��  : AUXDAC_START_TIME �Ĵ����ṹ���塣��ַƫ����:0x160����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      auxdac_start_time_reg;
    struct
    {
        unsigned long  cpu_auxdac_active_time : 11; /* bit[0-10] : ÿʱ϶/PCG����PA vbias�����ַ���ʱ��(sys_cnt)���޷���������Χ[0,1535��2047]����λchip�� */
        unsigned long  reserved               : 21; /* bit[11-31]: ���� */
    } reg;
} CBBP_AUXDAC_START_TIME_UNION;
#define CBBP_AUXDAC_START_TIME_cpu_auxdac_active_time_START  (0)
#define CBBP_AUXDAC_START_TIME_cpu_auxdac_active_time_END    (10)


/*****************************************************************************
 �ṹ��    : CBBP_AUXDAC_SSI_CFG_UNION
 �ṹ˵��  : AUXDAC_SSI_CFG �Ĵ����ṹ���塣��ַƫ����:0x164����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      auxdac_ssi_cfg_reg;
    struct
    {
        unsigned long  cpu_auxdac_en   : 1;  /* bit[0]    : AUXDACģ��ʹ�ܣ��ߵ�ƽ��Ч�� */
        unsigned long  reserved_0      : 7;  /* bit[1-7]  : ���� */
        unsigned long  cpu_auxdac_data : 10; /* bit[8-17] : ÿʱ϶������õ�vbias�����֣��޷������� */
        unsigned long  reserved_1      : 14; /* bit[18-31]: ���� */
    } reg;
} CBBP_AUXDAC_SSI_CFG_UNION;
#define CBBP_AUXDAC_SSI_CFG_cpu_auxdac_en_START    (0)
#define CBBP_AUXDAC_SSI_CFG_cpu_auxdac_en_END      (0)
#define CBBP_AUXDAC_SSI_CFG_cpu_auxdac_data_START  (8)
#define CBBP_AUXDAC_SSI_CFG_cpu_auxdac_data_END    (17)


/*****************************************************************************
 �ṹ��    : CBBP_AUXDAC_START_UNION
 �ṹ˵��  : AUXDAC_START �Ĵ����ṹ���塣��ַƫ����:0x168����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      auxdac_start_reg;
    struct
    {
        unsigned long  cpu_auxdac_start : 1;  /* bit[0]   : w1_pulse�����д1ʱ�������壬���ڷ���aucxdac vbias�����֡�cpu_auxdac_force_en=1ʱ����Ч�� */
        unsigned long  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_AUXDAC_START_UNION;
#define CBBP_AUXDAC_START_cpu_auxdac_start_START  (0)
#define CBBP_AUXDAC_START_cpu_auxdac_start_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_AUXDAC_FORCE_UNION
 �ṹ˵��  : AUXDAC_FORCE �Ĵ����ṹ���塣��ַƫ����:0x16C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      auxdac_force_reg;
    struct
    {
        unsigned long  cpu_auxdac_addr     : 1;  /* bit[0]   : vbias�����ֵ�ַ */
        unsigned long  reserved            : 30; /* bit[1-30]: ���� */
        unsigned long  cpu_auxdac_force_en : 1;  /* bit[31]  : auxdac ssiǿ�Ʒ���ʹ�ܣ��ߵ�ƽ��Ч�� */
    } reg;
} CBBP_AUXDAC_FORCE_UNION;
#define CBBP_AUXDAC_FORCE_cpu_auxdac_addr_START      (0)
#define CBBP_AUXDAC_FORCE_cpu_auxdac_addr_END        (0)
#define CBBP_AUXDAC_FORCE_cpu_auxdac_force_en_START  (31)
#define CBBP_AUXDAC_FORCE_cpu_auxdac_force_en_END    (31)


/*****************************************************************************
 �ṹ��    : CBBP_AUXDAC_CFG_UNION
 �ṹ˵��  : AUXDAC_CFG �Ĵ����ṹ���塣��ַƫ����:0x170����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      auxdac_cfg_reg;
    struct
    {
        unsigned long  cpu_auxdac_open_cfg  : 11; /* bit[0-10] : auxdac���������֡� */
        unsigned long  reserved_0           : 5;  /* bit[11-15]: ���� */
        unsigned long  cpu_auxdac_close_cfg : 11; /* bit[16-26]: auxdac�رտ����֡� */
        unsigned long  reserved_1           : 5;  /* bit[27-31]: ���� */
    } reg;
} CBBP_AUXDAC_CFG_UNION;
#define CBBP_AUXDAC_CFG_cpu_auxdac_open_cfg_START   (0)
#define CBBP_AUXDAC_CFG_cpu_auxdac_open_cfg_END     (10)
#define CBBP_AUXDAC_CFG_cpu_auxdac_close_cfg_START  (16)
#define CBBP_AUXDAC_CFG_cpu_auxdac_close_cfg_END    (26)


/*****************************************************************************
 �ṹ��    : CBBP_APT_START_TIME_UNION
 �ṹ˵��  : APT_START_TIME �Ĵ����ṹ���塣��ַƫ����:0x180����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      apt_start_time_reg;
    struct
    {
        unsigned long  cpu_apt_active_time : 11; /* bit[0-10] : ÿʱ϶/PCG����PA APT�����ַ���ʱ��(sys_cnt)���޷���������Χ[0,1535��2047]����λchip�� */
        unsigned long  reserved            : 21; /* bit[11-31]: ���� */
    } reg;
} CBBP_APT_START_TIME_UNION;
#define CBBP_APT_START_TIME_cpu_apt_active_time_START  (0)
#define CBBP_APT_START_TIME_cpu_apt_active_time_END    (10)


/*****************************************************************************
 �ṹ��    : CBBP_APT_CFG_UNION
 �ṹ˵��  : APT_CFG �Ĵ����ṹ���塣��ַƫ����:0x184����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      apt_cfg_reg;
    struct
    {
        unsigned long  cpu_apt_en   : 1;  /* bit[0]    : APTģ��ʹ�ܣ��ߵ�ƽ��Ч��ͬʱ�������Ϊ����DCDCоƬʹ�ܡ� */
        unsigned long  reserved_0   : 7;  /* bit[1-7]  : ���� */
        unsigned long  cpu_apt_data : 7;  /* bit[8-14] : ÿʱ϶������õ�APT�����֣��޷������� */
        unsigned long  reserved_1   : 17; /* bit[15-31]: ���� */
    } reg;
} CBBP_APT_CFG_UNION;
#define CBBP_APT_CFG_cpu_apt_en_START    (0)
#define CBBP_APT_CFG_cpu_apt_en_END      (0)
#define CBBP_APT_CFG_cpu_apt_data_START  (8)
#define CBBP_APT_CFG_cpu_apt_data_END    (14)


/*****************************************************************************
 �ṹ��    : CBBP_APT_START_UNION
 �ṹ˵��  : APT_START �Ĵ����ṹ���塣��ַƫ����:0x188����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      apt_start_reg;
    struct
    {
        unsigned long  cpu_apt_start : 1;  /* bit[0]   : w1_pulse�����д1ʱ�������壬���� ǿ�Ʒ���apt�����֡� */
        unsigned long  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_APT_START_UNION;
#define CBBP_APT_START_cpu_apt_start_START  (0)
#define CBBP_APT_START_cpu_apt_start_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_APT_FORCE_UNION
 �ṹ˵��  : APT_FORCE �Ĵ����ṹ���塣��ַƫ����:0x18C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      apt_force_reg;
    struct
    {
        unsigned long  cpu_apt_pwm_sel  : 1;  /* bit[0]   : apt pdm�����ʽѡ��0��PWM��1��PDM */
        unsigned long  reserved         : 30; /* bit[1-30]: ���� */
        unsigned long  cpu_apt_force_en : 1;  /* bit[31]  : apt pdmǿ�Ʒ���ʹ�ܣ��ߵ�ƽ��Ч�� */
    } reg;
} CBBP_APT_FORCE_UNION;
#define CBBP_APT_FORCE_cpu_apt_pwm_sel_START   (0)
#define CBBP_APT_FORCE_cpu_apt_pwm_sel_END     (0)
#define CBBP_APT_FORCE_cpu_apt_force_en_START  (31)
#define CBBP_APT_FORCE_cpu_apt_force_en_END    (31)


/*****************************************************************************
 �ṹ��    : CBBP_AFC_START_TIME_UNION
 �ṹ˵��  : AFC_START_TIME �Ĵ����ṹ���塣��ַƫ����:0x1A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      afc_start_time_reg;
    struct
    {
        unsigned long  cpu_afc_active_time : 11; /* bit[0-10] : ÿʱ϶afc�����ַ���ʱ��(sys_cnt)���޷���������Χ[0,1535��2047]����λchip�� */
        unsigned long  reserved            : 21; /* bit[11-31]: ���� */
    } reg;
} CBBP_AFC_START_TIME_UNION;
#define CBBP_AFC_START_TIME_cpu_afc_active_time_START  (0)
#define CBBP_AFC_START_TIME_cpu_afc_active_time_END    (10)


/*****************************************************************************
 �ṹ��    : CBBP_AFC_CFG_UNION
 �ṹ˵��  : AFC_CFG �Ĵ����ṹ���塣��ַƫ����:0x1A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      afc_cfg_reg;
    struct
    {
        unsigned long  cpu_c_afc_pdmpwm_sel : 1;  /* bit[0]    : AFC PDM/PWMģʽѡ��0:PDMģʽ��1��PWM��ʽ */
        unsigned long  cpu_c_afc_width_sel  : 1;  /* bit[1]    : afc pdm������λ��ѡ�� 0��12bit 1��13bit. */
        unsigned long  reserved_0           : 6;  /* bit[2-7]  : ���� */
        unsigned long  cpu_c_afc_data       : 13; /* bit[8-20] : ÿʱ϶������õ�AFC�����֣��޷������� */
        unsigned long  reserved_1           : 11; /* bit[21-31]: ���� */
    } reg;
} CBBP_AFC_CFG_UNION;
#define CBBP_AFC_CFG_cpu_c_afc_pdmpwm_sel_START  (0)
#define CBBP_AFC_CFG_cpu_c_afc_pdmpwm_sel_END    (0)
#define CBBP_AFC_CFG_cpu_c_afc_width_sel_START   (1)
#define CBBP_AFC_CFG_cpu_c_afc_width_sel_END     (1)
#define CBBP_AFC_CFG_cpu_c_afc_data_START        (8)
#define CBBP_AFC_CFG_cpu_c_afc_data_END          (20)


/*****************************************************************************
 �ṹ��    : CBBP_AFC_START_UNION
 �ṹ˵��  : AFC_START �Ĵ����ṹ���塣��ַƫ����:0x1A8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      afc_start_reg;
    struct
    {
        unsigned long  cpu_c_afc_start : 1;  /* bit[0]   : w1_pulse�����д1ʱ�������壬����ǿ�Ʒ���afc�����֡� */
        unsigned long  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_AFC_START_UNION;
#define CBBP_AFC_START_cpu_c_afc_start_START  (0)
#define CBBP_AFC_START_cpu_c_afc_start_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_AFC_FORCE_UNION
 �ṹ˵��  : AFC_FORCE �Ĵ����ṹ���塣��ַƫ����:0x1AC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      afc_force_reg;
    struct
    {
        unsigned long  reserved           : 31; /* bit[0-30]: ���� */
        unsigned long  cpu_c_afc_force_en : 1;  /* bit[31]  : AFC PDMǿ�Ƹ���ʹ�ܣ��ߵ�ƽ��Ч�� */
    } reg;
} CBBP_AFC_FORCE_UNION;
#define CBBP_AFC_FORCE_cpu_c_afc_force_en_START  (31)
#define CBBP_AFC_FORCE_cpu_c_afc_force_en_END    (31)


/*****************************************************************************
 �ṹ��    : CBBP_CPU_FE_CTRL_CKG_BYPASS_UNION
 �ṹ˵��  : CPU_FE_CTRL_CKG_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x1B0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      cpu_fe_ctrl_ckg_bypass_reg;
    struct
    {
        unsigned long  cpu_fe_ctrl_ckg_bypass : 3;  /* bit[0-2] : ǰ�˿���ģ����Զ�ʱ���ſ���·�źţ�1��ʾ��·ʱ���ſأ���ʱ�ӳ�����0��ʾ�Զ�ʱ���ſ���Ч��
                                                                  [0] MIPI���Զ�ʱ���ſ���·����
                                                                  [1] RFIC_SSI���Զ�ʱ���ſ���·����
                                                                  [2] GPIO���Զ�ʱ���ſ���·���� */
        unsigned long  reserved               : 29; /* bit[3-31]: ���� */
    } reg;
} CBBP_CPU_FE_CTRL_CKG_BYPASS_UNION;
#define CBBP_CPU_FE_CTRL_CKG_BYPASS_cpu_fe_ctrl_ckg_bypass_START  (0)
#define CBBP_CPU_FE_CTRL_CKG_BYPASS_cpu_fe_ctrl_ckg_bypass_END    (2)


/*****************************************************************************
 �ṹ��    : CBBP_ERR_CONFIG_CLR_UNION
 �ṹ˵��  : ERR_CONFIG_CLR �Ĵ����ṹ���塣��ַƫ����:0x1B4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      err_config_clr_reg;
    struct
    {
        unsigned long  cpu_err_config_clr : 1;  /* bit[0]   : �쳣����״̬�������������쳣״̬�ϱ������0x54[14:12], 0x8c[14:12], 0xb8[14:12], 0xec[22:20]�����������������쳣���һֱ���֡� */
        unsigned long  reserved           : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_ERR_CONFIG_CLR_UNION;
#define CBBP_ERR_CONFIG_CLR_cpu_err_config_clr_START  (0)
#define CBBP_ERR_CONFIG_CLR_cpu_err_config_clr_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_CTRL_VALID_IND_CFG_UNION
 �ṹ˵��  : CTRL_VALID_IND_CFG �Ĵ����ṹ���塣��ַƫ����:0x1B8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ctrl_valid_ind_cfg_reg;
    struct
    {
        unsigned long  cpu_ssi_valid_cfg_ind  : 1;  /* bit[0]   : RF SSI����ָ����Ч��־����ʹ�ܣ������źţ���cpu_ssi_ctrl_valid_cfg֮�����ñ��ź� */
        unsigned long  reserved_0             : 3;  /* bit[1-3] : ���� */
        unsigned long  cpu_mipi_valid_cfg_ind : 1;  /* bit[4]   : RF SSI����ָ����Ч��־����ʹ�ܣ������źţ���cpu_mipi_ctrl_valid_cfg֮�����ñ��ź� */
        unsigned long  reserved_1             : 3;  /* bit[5-7] : ���� */
        unsigned long  cpu_gpio_valid_cfg_ind : 1;  /* bit[8]   : RF SSI����ָ����Ч��־����ʹ�ܣ������źţ���cpu_gpio_ctrl_valid_cfg֮�����ñ��ź� */
        unsigned long  reserved_2             : 23; /* bit[9-31]: ���� */
    } reg;
} CBBP_CTRL_VALID_IND_CFG_UNION;
#define CBBP_CTRL_VALID_IND_CFG_cpu_ssi_valid_cfg_ind_START   (0)
#define CBBP_CTRL_VALID_IND_CFG_cpu_ssi_valid_cfg_ind_END     (0)
#define CBBP_CTRL_VALID_IND_CFG_cpu_mipi_valid_cfg_ind_START  (4)
#define CBBP_CTRL_VALID_IND_CFG_cpu_mipi_valid_cfg_ind_END    (4)
#define CBBP_CTRL_VALID_IND_CFG_cpu_gpio_valid_cfg_ind_START  (8)
#define CBBP_CTRL_VALID_IND_CFG_cpu_gpio_valid_cfg_ind_END    (8)


/*****************************************************************************
 �ṹ��    : CBBP_CTRL_VALID_FORCE_RESET_UNION
 �ṹ˵��  : CTRL_VALID_FORCE_RESET �Ĵ����ṹ���塣��ַƫ����:0x1CC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      ctrl_valid_force_reset_reg;
    struct
    {
        unsigned long  cpu_ssi_valid_reset_ind  : 1;  /* bit[0]   : RF SSI����ָ����Ч��־ǿ�Ƹ�λ�������źš�1��Ч�����ú�����û�б�����Ŀ���ָ������ٴ�ִ�С� */
        unsigned long  reserved_0               : 3;  /* bit[1-3] : ���� */
        unsigned long  cpu_mipi_valid_reset_ind : 1;  /* bit[4]   : MIPI����ָ����Ч��־ǿ�Ƹ�λ�������źš�1��Ч�����ú�����û�б�����Ŀ���ָ������ٴ�ִ�С� */
        unsigned long  reserved_1               : 3;  /* bit[5-7] : ���� */
        unsigned long  cpu_gpio_valid_reset_ind : 1;  /* bit[8]   : GPIO����ָ����Ч��־ǿ�Ƹ�λ�������źš�1��Ч�����ú�����û�б�����Ŀ���ָ������ٴ�ִ�С� */
        unsigned long  reserved_2               : 23; /* bit[9-31]: ���� */
    } reg;
} CBBP_CTRL_VALID_FORCE_RESET_UNION;
#define CBBP_CTRL_VALID_FORCE_RESET_cpu_ssi_valid_reset_ind_START   (0)
#define CBBP_CTRL_VALID_FORCE_RESET_cpu_ssi_valid_reset_ind_END     (0)
#define CBBP_CTRL_VALID_FORCE_RESET_cpu_mipi_valid_reset_ind_START  (4)
#define CBBP_CTRL_VALID_FORCE_RESET_cpu_mipi_valid_reset_ind_END    (4)
#define CBBP_CTRL_VALID_FORCE_RESET_cpu_gpio_valid_reset_ind_START  (8)
#define CBBP_CTRL_VALID_FORCE_RESET_cpu_gpio_valid_reset_ind_END    (8)


/***======================================================================***
                     (17/20) register_define_c_fe_ctrl_mem
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : CBBP_RFIC_SSI_CTRL_RAM_UNION
 �ṹ˵��  : RFIC_SSI_CTRL_RAM �Ĵ����ṹ���塣��ַƫ����:0x800����ֵ:0x00000000�����:32
 �Ĵ���˵��: ƹ��RAM��ctrlָ����������16��
*****************************************************************************/
typedef union
{
    unsigned long      rfic_ssi_ctrl_ram_reg;
    struct
    {
        unsigned long  rfic_start_time : 11; /* bit[0-10] : rficָ�����Чʱ�̣�����S����Ϊ0ʱ��Ч������������Ϊϵͳʱ���Ӧ��λ�ã���ʱģ����Ҫ�������������ѡȡ��ǰ������ϵͳʱ�������ǰ�˿���ģ�飬����Ϊchip��CBBP�������������붨ʱģ������ľ���ʱ����бȽϣ�����ڶ��������
                                                            ������Ȼ����þ���ʱ��С�ڶ�ʱ����ʱ��ʱ�����ȡ����Buffer���ݣ������ͣ�
                                                            ���þ���ʱ�겻���ڶ�ʱ����ʱ�꣬������ȴ��� */
        unsigned long  reserved_0      : 5;  /* bit[11-15]: ���� */
        unsigned long  rfic_s_value    : 1;  /* bit[16]   : rficָ�����Ч��ʽ��1��ʾ������Ч��0��ʾ����Acitive Timing��ָʾʱ��λ����Ч */
        unsigned long  reserved_1      : 7;  /* bit[17-23]: ���� */
        unsigned long  rfic_num        : 3;  /* bit[24-26]: ��������ָ���Ӧ��rfic����ָ��ĸ�����3bit��0~7��Ӧ���ø���Ϊ0~7����0��ʾ������ */
        unsigned long  reserved_2      : 5;  /* bit[27-31]: ���� */
    } reg;
} CBBP_RFIC_SSI_CTRL_RAM_UNION;
#define CBBP_RFIC_SSI_CTRL_RAM_rfic_start_time_START  (0)
#define CBBP_RFIC_SSI_CTRL_RAM_rfic_start_time_END    (10)
#define CBBP_RFIC_SSI_CTRL_RAM_rfic_s_value_START     (16)
#define CBBP_RFIC_SSI_CTRL_RAM_rfic_s_value_END       (16)
#define CBBP_RFIC_SSI_CTRL_RAM_rfic_num_START         (24)
#define CBBP_RFIC_SSI_CTRL_RAM_rfic_num_END           (26)


/*****************************************************************************
 �ṹ��    : CBBP_RFIC_SSI_DATA_RAM_UNION
 �ṹ˵��  : RFIC_SSI_DATA_RAM �Ĵ����ṹ���塣��ַƫ����:0x840����ֵ:0x00000000�����:32
 �Ĵ���˵��: ƹ��RAM
*****************************************************************************/
typedef union
{
    unsigned long      rfic_ssi_data_ram_reg;
    struct
    {
        unsigned long  rfic_ssi_data    : 16; /* bit[0-15] : �ò�����2�ֿ��ܵĸ�ʽ
                                                             1��д��ʽ��[15:0]Data RF SSIд����ʱ��������Ϣ
                                                             2) ����ʽ��
                                                             [15:12]Buf Addr,��RF SSI������ʱ�ض��������Buffer��Ӧ��λ�ã��û���Bufferλ�ڹ���ǰ��ģ�飬��bbp_comm_fe
                                                             [11]E RF SSI������ʱ������ָʾ���һ����������1��Ч��
                                                             [10:0]���� */
        unsigned long  rfic_data_addr   : 8;  /* bit[16-23]: Addr RF SSI��ַ��Ϣ */
        unsigned long  rfic_ssi_wr_flag : 1;  /* bit[24]   : WR RF SSI��д��־��1��ʾ����0��ʾд */
        unsigned long  reserved         : 7;  /* bit[25-31]: ���� */
    } reg;
} CBBP_RFIC_SSI_DATA_RAM_UNION;
#define CBBP_RFIC_SSI_DATA_RAM_rfic_ssi_data_START     (0)
#define CBBP_RFIC_SSI_DATA_RAM_rfic_ssi_data_END       (15)
#define CBBP_RFIC_SSI_DATA_RAM_rfic_data_addr_START    (16)
#define CBBP_RFIC_SSI_DATA_RAM_rfic_data_addr_END      (23)
#define CBBP_RFIC_SSI_DATA_RAM_rfic_ssi_wr_flag_START  (24)
#define CBBP_RFIC_SSI_DATA_RAM_rfic_ssi_wr_flag_END    (24)


/*****************************************************************************
 �ṹ��    : CBBP_MIPI_CTRL_RAM_UNION
 �ṹ˵��  : MIPI_CTRL_RAM �Ĵ����ṹ���塣��ַƫ����:0xA00����ֵ:0x00000000�����:32
 �Ĵ���˵��: ƹ��RAM��ctrlָ����������16��
*****************************************************************************/
typedef union
{
    unsigned long      mipi_ctrl_ram_reg;
    struct
    {
        unsigned long  mipi_start_time : 11; /* bit[0-10] : mipiָ����Чʱ�̣�����S����Ϊ0ʱ��Ч������������Ϊϵͳʱ���Ӧ��λ�ã���ʱģ����Ҫ�������������ѡȡ��ǰ������ϵͳʱ�������ǰ�˿���ģ�飬����Ϊchip��CBBP�������������붨ʱģ������ľ���ʱ����бȽϣ�����ڶ��������
                                                            ������Ȼ����þ���ʱ��С�ڶ�ʱ����ʱ��ʱ�����ȡ����Buffer���ݣ������ͣ�
                                                            ���þ���ʱ�겻���ڶ�ʱ����ʱ�꣬������ȴ��� */
        unsigned long  reserved_0      : 5;  /* bit[11-15]: ���� */
        unsigned long  mipi_s_value    : 1;  /* bit[16]   : mipiָ����Ч��ʽ��1��ʾ������Ч��0��ʾ����Acitive Timing��ָʾʱ��λ����Ч */
        unsigned long  reserved_1      : 7;  /* bit[17-23]: ���� */
        unsigned long  mipi_num        : 2;  /* bit[24-25]: ��������ָ���Ӧ��mipi����ָ��ĸ�����2bit��0~3��Ӧ���ø���Ϊ0~3����0��ʾ������ */
        unsigned long  reserved_2      : 6;  /* bit[26-31]: ���� */
    } reg;
} CBBP_MIPI_CTRL_RAM_UNION;
#define CBBP_MIPI_CTRL_RAM_mipi_start_time_START  (0)
#define CBBP_MIPI_CTRL_RAM_mipi_start_time_END    (10)
#define CBBP_MIPI_CTRL_RAM_mipi_s_value_START     (16)
#define CBBP_MIPI_CTRL_RAM_mipi_s_value_END       (16)
#define CBBP_MIPI_CTRL_RAM_mipi_num_START         (24)
#define CBBP_MIPI_CTRL_RAM_mipi_num_END           (25)


/*****************************************************************************
 �ṹ��    : CBBP_GPIO_CTRL_RAM_UNION
 �ṹ˵��  : GPIO_CTRL_RAM �Ĵ����ṹ���塣��ַƫ����:0xC00����ֵ:0x00000000�����:32
 �Ĵ���˵��: ƹ��RAM��ctrlָ����������32��
*****************************************************************************/
typedef union
{
    unsigned long      gpio_ctrl_ram_reg;
    struct
    {
        unsigned long  gpio_start_time : 11; /* bit[0-10] : GPIOָ�����Чʱ�̣�����S����Ϊ0ʱ��Ч������������Ϊϵͳʱ���Ӧ��λ�ã���ʱģ����Ҫ�������������ѡȡ��ǰ������ϵͳʱ�������ǰ�˿���ģ�飬����Ϊchip��CBBP�������������붨ʱģ������ľ���ʱ����бȽϣ�����ڶ��������
                                                            ������Ȼ����þ���ʱ��С�ڶ�ʱ����ʱ��ʱ�����ȡ����Buffer���ݣ������ͣ�
                                                            ���þ���ʱ�겻���ڶ�ʱ����ʱ�꣬������ȴ��� */
        unsigned long  reserved_0      : 5;  /* bit[11-15]: ���� */
        unsigned long  gpio_s_value    : 1;  /* bit[16]   : GPIOָ�����Ч��ʽ��1��ʾ������Ч��0��ʾ����Acitive Timing��ָʾʱ��λ����Ч */
        unsigned long  reserved_1      : 7;  /* bit[17-23]: ���� */
        unsigned long  gpio_num        : 1;  /* bit[24]   : ��������ָ���Ӧ��GPIO����ָ��ĸ�����1bit��1��Ӧ���ø���Ϊ1��0��ʾ������ */
        unsigned long  gpio_ram_value  : 7;  /* bit[25-31]: GPIOһ��64����ַ,����ctrl_buff��data_buff��ַ��������1:1���䣬���ݸ�ʽ���ӿ�˵���顣����Ҫʹ�õĵ�ַ�����㡣Data��bit����ͬGPIO_FORCE_DATA�Ĵ��������� */
    } reg;
} CBBP_GPIO_CTRL_RAM_UNION;
#define CBBP_GPIO_CTRL_RAM_gpio_start_time_START  (0)
#define CBBP_GPIO_CTRL_RAM_gpio_start_time_END    (10)
#define CBBP_GPIO_CTRL_RAM_gpio_s_value_START     (16)
#define CBBP_GPIO_CTRL_RAM_gpio_s_value_END       (16)
#define CBBP_GPIO_CTRL_RAM_gpio_num_START         (24)
#define CBBP_GPIO_CTRL_RAM_gpio_num_END           (24)
#define CBBP_GPIO_CTRL_RAM_gpio_ram_value_START   (25)
#define CBBP_GPIO_CTRL_RAM_gpio_ram_value_END     (31)


/*****************************************************************************
 �ṹ��    : CBBP_GPIO_DATA_RAM_UNION
 �ṹ˵��  : GPIO_DATA_RAM �Ĵ����ṹ���塣��ַƫ����:0xC80����ֵ:0x00000000�����:32
 �Ĵ���˵��: ƹ��RAM
*****************************************************************************/
typedef union
{
    unsigned long      gpio_data_ram_reg;
    struct
    {
        unsigned long  gpio_data      : 31; /* bit[0-30]: �߿��������� */
        unsigned long  gpio_data_head : 1;  /* bit[31]  : Ϊ0ʱ����ʾ�����߿�ant_pa_sel����
                                                          Ϊ1ʱ��ʾר���߿أ�ÿ��bit�ĺ���������bit[6:0]���� */
    } reg;
} CBBP_GPIO_DATA_RAM_UNION;
#define CBBP_GPIO_DATA_RAM_gpio_data_START       (0)
#define CBBP_GPIO_DATA_RAM_gpio_data_END         (30)
#define CBBP_GPIO_DATA_RAM_gpio_data_head_START  (31)
#define CBBP_GPIO_DATA_RAM_gpio_data_head_END    (31)


/*****************************************************************************
 �ṹ��    : CBBP_HKADC_SSI_CTRL_RAM_UNION
 �ṹ˵��  : HKADC_SSI_CTRL_RAM �Ĵ����ṹ���塣��ַƫ����:0xD00����ֵ:0x00000000�����:32
 �Ĵ���˵��: ctrlָ����������16��
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_ssi_ctrl_ram_reg;
    struct
    {
        unsigned long  hkadc_start_time : 11; /* bit[0-10] : hkadcָ�����Чʱ�̣�����S����Ϊ0ʱ��Ч������������Ϊϵͳʱ���Ӧ��λ�ã���ʱģ����Ҫ�������������ѡȡ��ǰ������ϵͳʱ�������ǰ�˿���ģ�飬����Ϊchip��CBBP�������������붨ʱģ������ľ���ʱ����бȽϣ�����ڶ��������
                                                             ������Ȼ����þ���ʱ��С�ڶ�ʱ����ʱ��ʱ�����ȡ����Buffer���ݣ������ͣ�
                                                             ���þ���ʱ�겻���ڶ�ʱ����ʱ�꣬������ȴ��� */
        unsigned long  reserved_0       : 5;  /* bit[11-15]: ���� */
        unsigned long  hkadc_s_value    : 1;  /* bit[16]   : hkadcָ�����Ч��ʽ��1��ʾ������Ч��0��ʾ����Acitive Timing��ָʾʱ��λ����Ч */
        unsigned long  reserved_1       : 7;  /* bit[17-23]: ���� */
        unsigned long  hkadc_num        : 1;  /* bit[24]   : ��������ָ���Ӧ��GPIO����ָ��ĸ�����3bit��0~7��Ӧ���ø���Ϊ0~7����0��ʾ������ */
        unsigned long  reserved_2       : 7;  /* bit[25-31]: ���� */
    } reg;
} CBBP_HKADC_SSI_CTRL_RAM_UNION;
#define CBBP_HKADC_SSI_CTRL_RAM_hkadc_start_time_START  (0)
#define CBBP_HKADC_SSI_CTRL_RAM_hkadc_start_time_END    (10)
#define CBBP_HKADC_SSI_CTRL_RAM_hkadc_s_value_START     (16)
#define CBBP_HKADC_SSI_CTRL_RAM_hkadc_s_value_END       (16)
#define CBBP_HKADC_SSI_CTRL_RAM_hkadc_num_START         (24)
#define CBBP_HKADC_SSI_CTRL_RAM_hkadc_num_END           (24)


/*****************************************************************************
 �ṹ��    : CBBP_HKADC_SSI_DATA_RAM_UNION
 �ṹ˵��  : HKADC_SSI_DATA_RAM �Ĵ����ṹ���塣��ַƫ����:0xD40����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_ssi_data_ram_reg;
    struct
    {
        unsigned long  hkadc_data     : 16; /* bit[0-15] : �ò�����3�ֿ��ܵĸ�ʽ���ֱ����£�
                                                           1. ��hkadc_cfg_type=0ʱ�����bit[15]=0,��ʾд������[14:8]Ϊд��ַ��[7:0]Ϊд����
                                                           2. ��hkadc_cfg_type=0ʱ�����bit[15]=1,��ʾ��������[14:8]Ϊд��ַ��[7:3]��ʾHKADC SSI������ʱ�ض��������Buffer��Ӧ��λ�ã��û���Bufferλ�ڱ�ģ���ڲ�����������С����Ϊ32
                                                           [2]HKADC SSI������ʱ������ָʾ���һ����������1��Ч������bit��Ч��ǰ�˿���ģ���ڱ���HKADC SSI��������ɺ�����ж��ϱ������������ȡHKADC SSI�ض����
                                                           3. ��hkadc_cfg_type=1ʱ�����bit[15]=0,��ʾHKADCͨ���������ָ�[15:1]Ϊ����λ��[0]Ϊ�����Ƿ���Ч */
        unsigned long  hkadc_cfg_type : 1;  /* bit[16]   : ����ָ������ͣ�0��ʾΪHKADC SSI����ָ�1��ʾΪHKADCͨ���������ָ�� */
        unsigned long  reserved       : 15; /* bit[17-31]: ���� */
    } reg;
} CBBP_HKADC_SSI_DATA_RAM_UNION;
#define CBBP_HKADC_SSI_DATA_RAM_hkadc_data_START      (0)
#define CBBP_HKADC_SSI_DATA_RAM_hkadc_data_END        (15)
#define CBBP_HKADC_SSI_DATA_RAM_hkadc_cfg_type_START  (16)
#define CBBP_HKADC_SSI_DATA_RAM_hkadc_cfg_type_END    (16)


/***======================================================================***
                     (18/20) register_define_sdr_gdrx_gauge
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : CBBP_GDRX_GAUGE_EN_CNF_UNION
 �ṹ˵��  : GDRX_GAUGE_EN_CNF �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x0000000A�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      gdrx_gauge_en_cnf_reg;
    struct
    {
        unsigned long  gdrx_gauge_len  : 17; /* bit[0-16] : ʱ��У׼32KHzʱ�Ӹ��� */
        unsigned long  reserved        : 13; /* bit[17-29]: ���� */
        unsigned long  gdrx_gauge_en   : 1;  /* bit[30]   : ʱ��У׼ʹ�ܣ�д1�����������㣬д0�����塣 */
        unsigned long  gdrx_gauge_stop : 1;  /* bit[31]   : GDRXֹͣ���壬д1ֹͣ�������㣬д0�����塣 */
    } reg;
} CBBP_GDRX_GAUGE_EN_CNF_UNION;
#define CBBP_GDRX_GAUGE_EN_CNF_gdrx_gauge_len_START   (0)
#define CBBP_GDRX_GAUGE_EN_CNF_gdrx_gauge_len_END     (16)
#define CBBP_GDRX_GAUGE_EN_CNF_gdrx_gauge_en_START    (30)
#define CBBP_GDRX_GAUGE_EN_CNF_gdrx_gauge_en_END      (30)
#define CBBP_GDRX_GAUGE_EN_CNF_gdrx_gauge_stop_START  (31)
#define CBBP_GDRX_GAUGE_EN_CNF_gdrx_gauge_stop_END    (31)


/*****************************************************************************
 �ṹ��    : CBBP_GAUGE_RESULT_RPT_UNION
 �ṹ˵��  : GAUGE_RESULT_RPT �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      gauge_result_rpt_reg;
    struct
    {
        unsigned long  gdrx_gauge_result : 28; /* bit[0-27] : ʱ��У׼���������������104M�Ӹ��� */
        unsigned long  reserved          : 2;  /* bit[28-29]: ���� */
        unsigned long  gdrx_gauge_state  : 1;  /* bit[30]   : ����״̬��ѯ��1�����ڲ����� */
        unsigned long  gdrx_sleep_state  : 1;  /* bit[31]   : ˯��״̬��ѯ��1������˯�ߡ� */
    } reg;
} CBBP_GAUGE_RESULT_RPT_UNION;
#define CBBP_GAUGE_RESULT_RPT_gdrx_gauge_result_START  (0)
#define CBBP_GAUGE_RESULT_RPT_gdrx_gauge_result_END    (27)
#define CBBP_GAUGE_RESULT_RPT_gdrx_gauge_state_START   (30)
#define CBBP_GAUGE_RESULT_RPT_gdrx_gauge_state_END     (30)
#define CBBP_GAUGE_RESULT_RPT_gdrx_sleep_state_START   (31)
#define CBBP_GAUGE_RESULT_RPT_gdrx_sleep_state_END     (31)


/*****************************************************************************
 �ṹ��    : CBBP_IMI_INT_TDMA_QB_UNION
 �ṹ˵��  : IMI_INT_TDMA_QB �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      imi_int_tdma_qb_reg;
    struct
    {
        unsigned long  imi_int_tdma_qb : 13; /* bit[0-12] : IMIʱ���ж��ϱ�ʱGTC��TDMA QB������������ */
        unsigned long  reserved        : 19; /* bit[13-31]: ���� */
    } reg;
} CBBP_IMI_INT_TDMA_QB_UNION;
#define CBBP_IMI_INT_TDMA_QB_imi_int_tdma_qb_START  (0)
#define CBBP_IMI_INT_TDMA_QB_imi_int_tdma_qb_END    (12)


/*****************************************************************************
 �ṹ��    : CBBP_SLEEP_INT_TDMA_QB_UNION
 �ṹ˵��  : SLEEP_INT_TDMA_QB �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      sleep_int_tdma_qb_reg;
    struct
    {
        unsigned long  sleep_int_tdma_qb : 13; /* bit[0-12] : 32Kʱ���ж��ϱ�ʱGTC��TDMA QB������������ */
        unsigned long  reserved          : 19; /* bit[13-31]: ���� */
    } reg;
} CBBP_SLEEP_INT_TDMA_QB_UNION;
#define CBBP_SLEEP_INT_TDMA_QB_sleep_int_tdma_qb_START  (0)
#define CBBP_SLEEP_INT_TDMA_QB_sleep_int_tdma_qb_END    (12)


/***======================================================================***
                     (19/20) register_define_sdr_g_timing
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : CBBP_DRX_TEST_CFG_UNION
 �ṹ˵��  : DRX_TEST_CFG �Ĵ����ṹ���塣��ַƫ����:0x00����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      drx_test_cfg_reg;
    struct
    {
        unsigned long  reserved_0           : 8;  /* bit[0-7] : ���� */
        unsigned long  cpu_drx_test_mode_en : 1;  /* bit[8]   : 1��ʾDRX����ģʽʹ�ܣ���ʱGTCʱ��Ӧ���رգ�����DRX���Ѻ�Ķ�ʱά������ıȶԡ�����ʹ���¸��ź�Ӧ�ñ���0�������� */
        unsigned long  reserved_1           : 23; /* bit[9-31]: ���� */
    } reg;
} CBBP_DRX_TEST_CFG_UNION;
#define CBBP_DRX_TEST_CFG_cpu_drx_test_mode_en_START  (8)
#define CBBP_DRX_TEST_CFG_cpu_drx_test_mode_en_END    (8)


/*****************************************************************************
 �ṹ��    : CBBP_G2_GTC_FRM_OFFSET_RPT_UNION
 �ṹ˵��  : G2_GTC_FRM_OFFSET_RPT �Ĵ����ṹ���塣��ַƫ����:0x04����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      g2_gtc_frm_offset_rpt_reg;
    struct
    {
        unsigned long  gtc_frm_it_offset : 13; /* bit[0-12] : ֡�ж���TimeBaseʱ��ƫ���λqb�������� */
        unsigned long  reserved          : 19; /* bit[13-31]: ���� */
    } reg;
} CBBP_G2_GTC_FRM_OFFSET_RPT_UNION;
#define CBBP_G2_GTC_FRM_OFFSET_RPT_gtc_frm_it_offset_START  (0)
#define CBBP_G2_GTC_FRM_OFFSET_RPT_gtc_frm_it_offset_END    (12)


/*****************************************************************************
 �ṹ��    : CBBP_G2_CPU_GTC_T1_T2_T3_CNG_UNION
 �ṹ˵��  : G2_CPU_GTC_T1_T2_T3_CNG �Ĵ����ṹ���塣��ַƫ����:0x08����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      g2_cpu_gtc_t1_t2_t3_cng_reg;
    struct
    {
        unsigned long  cpu_gtc_t1_cnt : 11; /* bit[0-10] : ����֡��ά�������е�T1��ʼֵ���ò���ֵ��cpu_gtc_t2_cnt��cpu_gtc_t3_cnt��
                                                           cpu_gtc_fn_low��cpu_gtc_fn_highһ������GTC�ڲ�֡��ά���Ĵ����ĳ�ʼ������GTC��TDMA֡�߽紦��Ч,����Ӧ����Ϊ��һ֡��֡�ŵ�T1ֵ */
        unsigned long  reserved_0     : 5;  /* bit[11-15]: ���� */
        unsigned long  cpu_gtc_t2_cnt : 5;  /* bit[16-20]: ����֡��ά�������е�T2��ʼֵ���ò���ֵ��cpu_gtc_t1_cnt����GTC��TDMA֡�߽紦��Ч,����Ӧ����Ϊ��һ֡��֡��
                                                           cpu_gtc_t3_cnt��cpu_gtc_fn_low��cpu_gtc_fn_highһ������GTC�ڲ�֡��ά���Ĵ����ĳ�ʼ������GTC��TDMA֡�߽紦��Ч,����Ӧ����Ϊ��һ֡��֡�ŵ�T2ֵ */
        unsigned long  reserved_1     : 3;  /* bit[21-23]: ���� */
        unsigned long  cpu_gtc_t3_cnt : 6;  /* bit[24-29]: ����֡��ά�������е�T3��ʼֵ���ò���ֵ��cpu_gtc_t1_cnt��
                                                           cpu_gtc_t2_cnt��cpu_gtc_fn_low��cpu_gtc_fn_highһ������GTC�ڲ�֡��ά���Ĵ����ĳ�ʼ������GTC��TDMA֡�߽紦��Ч,����Ӧ����Ϊ��һ֡��֡�ŵ�T3ֵ */
        unsigned long  reserved_2     : 2;  /* bit[30-31]: ���� */
    } reg;
} CBBP_G2_CPU_GTC_T1_T2_T3_CNG_UNION;
#define CBBP_G2_CPU_GTC_T1_T2_T3_CNG_cpu_gtc_t1_cnt_START  (0)
#define CBBP_G2_CPU_GTC_T1_T2_T3_CNG_cpu_gtc_t1_cnt_END    (10)
#define CBBP_G2_CPU_GTC_T1_T2_T3_CNG_cpu_gtc_t2_cnt_START  (16)
#define CBBP_G2_CPU_GTC_T1_T2_T3_CNG_cpu_gtc_t2_cnt_END    (20)
#define CBBP_G2_CPU_GTC_T1_T2_T3_CNG_cpu_gtc_t3_cnt_START  (24)
#define CBBP_G2_CPU_GTC_T1_T2_T3_CNG_cpu_gtc_t3_cnt_END    (29)


/*****************************************************************************
 �ṹ��    : CBBP_G2_GTC_T1_T2_T3_RPT_CPU_UNION
 �ṹ˵��  : G2_GTC_T1_T2_T3_RPT_CPU �Ĵ����ṹ���塣��ַƫ����:0x0C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      g2_gtc_t1_t2_t3_rpt_cpu_reg;
    struct
    {
        unsigned long  gtc_t1_cnt : 11; /* bit[0-10] : GTC�ڲ�ά����T1�������ϱ� */
        unsigned long  reserved_0 : 5;  /* bit[11-15]: ���� */
        unsigned long  gtc_t2_cnt : 5;  /* bit[16-20]: GTC�ڲ�ά����T2�������ϱ� */
        unsigned long  reserved_1 : 3;  /* bit[21-23]: ���� */
        unsigned long  gtc_t3_cnt : 6;  /* bit[24-29]: GTC�ڲ�ά����T3�������ϱ� */
        unsigned long  reserved_2 : 2;  /* bit[30-31]: ���� */
    } reg;
} CBBP_G2_GTC_T1_T2_T3_RPT_CPU_UNION;
#define CBBP_G2_GTC_T1_T2_T3_RPT_CPU_gtc_t1_cnt_START  (0)
#define CBBP_G2_GTC_T1_T2_T3_RPT_CPU_gtc_t1_cnt_END    (10)
#define CBBP_G2_GTC_T1_T2_T3_RPT_CPU_gtc_t2_cnt_START  (16)
#define CBBP_G2_GTC_T1_T2_T3_RPT_CPU_gtc_t2_cnt_END    (20)
#define CBBP_G2_GTC_T1_T2_T3_RPT_CPU_gtc_t3_cnt_START  (24)
#define CBBP_G2_GTC_T1_T2_T3_RPT_CPU_gtc_t3_cnt_END    (29)


/*****************************************************************************
 �ṹ��    : CBBP_G2_CPU_GTC_FRM_OFFSET_CFG_UNION
 �ṹ˵��  : G2_CPU_GTC_FRM_OFFSET_CFG �Ĵ����ṹ���塣��ַƫ����:0x10����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      g2_cpu_gtc_frm_offset_cfg_reg;
    struct
    {
        unsigned long  cpu_gtc_frm_offset       : 13; /* bit[0-12] : CPU���õ�gtc_frm_offset���� */
        unsigned long  reserved_0               : 3;  /* bit[13-15]: ���� */
        unsigned long  cpu_gtc_frm_it_offset    : 13; /* bit[16-28]: CPU���õ�gtc_frm_it_offset���� */
        unsigned long  reserved_1               : 2;  /* bit[29-30]: ���� */
        unsigned long  cpu_gtc_frm_offset_wr_en : 1;  /* bit[31]   : CPU���õ�cpu_gtc_frm_offset��cpu_gtc_frm_it_offset������Чָʾ�źţ��߼������㡣(��ͬ���ͼĴ������ܷ���ͬһ��ַ����) */
    } reg;
} CBBP_G2_CPU_GTC_FRM_OFFSET_CFG_UNION;
#define CBBP_G2_CPU_GTC_FRM_OFFSET_CFG_cpu_gtc_frm_offset_START        (0)
#define CBBP_G2_CPU_GTC_FRM_OFFSET_CFG_cpu_gtc_frm_offset_END          (12)
#define CBBP_G2_CPU_GTC_FRM_OFFSET_CFG_cpu_gtc_frm_it_offset_START     (16)
#define CBBP_G2_CPU_GTC_FRM_OFFSET_CFG_cpu_gtc_frm_it_offset_END       (28)
#define CBBP_G2_CPU_GTC_FRM_OFFSET_CFG_cpu_gtc_frm_offset_wr_en_START  (31)
#define CBBP_G2_CPU_GTC_FRM_OFFSET_CFG_cpu_gtc_frm_offset_wr_en_END    (31)


/*****************************************************************************
 �ṹ��    : CBBP_G2_CPU_GTC_FN_CFG_UNION
 �ṹ˵��  : G2_CPU_GTC_FN_CFG �Ĵ����ṹ���塣��ַƫ����:0x14����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      g2_cpu_gtc_fn_cfg_reg;
    struct
    {
        unsigned long  cpu_gtc_fn_low   : 11; /* bit[0-10] : CPU���õ�TDMA֡�ŵ�λ0~26x51-1ѭ������, CPU���ú���GTC��TDMA֡�߽紦��Ч,����Ӧ����Ϊ��һ֡��֡�� */
        unsigned long  reserved_0       : 5;  /* bit[11-15]: ���� */
        unsigned long  cpu_gtc_fn_high  : 11; /* bit[16-26]: CPU����TDMA֡�Ÿ�λ0~2047ѭ����������λ�����󣬸�λ�ż�1��CPU���ú���GTC��TDMA֡�߽紦��Ч,����Ӧ����Ϊ��һ֡��֡�� */
        unsigned long  reserved_1       : 4;  /* bit[27-30]: ���� */
        unsigned long  cpu_gtc_fn_wr_en : 1;  /* bit[31]   : ֡�ų�ʼ���źţ�1��Ч���߼������㣬ֻ�е���ҪT1,T2,T3��fn_low��fn_high��д��󷽿ɶԸ�bit��1 */
    } reg;
} CBBP_G2_CPU_GTC_FN_CFG_UNION;
#define CBBP_G2_CPU_GTC_FN_CFG_cpu_gtc_fn_low_START    (0)
#define CBBP_G2_CPU_GTC_FN_CFG_cpu_gtc_fn_low_END      (10)
#define CBBP_G2_CPU_GTC_FN_CFG_cpu_gtc_fn_high_START   (16)
#define CBBP_G2_CPU_GTC_FN_CFG_cpu_gtc_fn_high_END     (26)
#define CBBP_G2_CPU_GTC_FN_CFG_cpu_gtc_fn_wr_en_START  (31)
#define CBBP_G2_CPU_GTC_FN_CFG_cpu_gtc_fn_wr_en_END    (31)


/*****************************************************************************
 �ṹ��    : CBBP_G2_GTC_FN_RPT_UNION
 �ṹ˵��  : G2_GTC_FN_RPT �Ĵ����ṹ���塣��ַƫ����:0x18����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      g2_gtc_fn_rpt_reg;
    struct
    {
        unsigned long  gtc_fn_low  : 11; /* bit[0-10] : GTC��ʱʵ��֡�ŵ�λ */
        unsigned long  reserved_0  : 5;  /* bit[11-15]: ���� */
        unsigned long  gtc_fn_high : 11; /* bit[16-26]: GTC��ʱʵ��֡�Ÿ�λ */
        unsigned long  reserved_1  : 5;  /* bit[27-31]: ���� */
    } reg;
} CBBP_G2_GTC_FN_RPT_UNION;
#define CBBP_G2_GTC_FN_RPT_gtc_fn_low_START   (0)
#define CBBP_G2_GTC_FN_RPT_gtc_fn_low_END     (10)
#define CBBP_G2_GTC_FN_RPT_gtc_fn_high_START  (16)
#define CBBP_G2_GTC_FN_RPT_gtc_fn_high_END    (26)


/*****************************************************************************
 �ṹ��    : CBBP_GTC_QB_RPT_UNION
 �ṹ˵��  : GTC_QB_RPT �Ĵ����ṹ���塣��ַƫ����:0x1C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      gtc_qb_rpt_reg;
    struct
    {
        unsigned long  gtc_tdma_qb  : 13; /* bit[0-12] : ��ǰʱ��TDMA��QB����ֵ */
        unsigned long  reserved_0   : 3;  /* bit[13-15]: ���� */
        unsigned long  gtc_timebase : 13; /* bit[16-28]: ����ʱ��QB�ϱ���������Χ0~4999����Ӧһ֡�ĳ��ȡ���ֵֻ�븴λʱ���йأ������� */
        unsigned long  reserved_1   : 3;  /* bit[29-31]: ���� */
    } reg;
} CBBP_GTC_QB_RPT_UNION;
#define CBBP_GTC_QB_RPT_gtc_tdma_qb_START   (0)
#define CBBP_GTC_QB_RPT_gtc_tdma_qb_END     (12)
#define CBBP_GTC_QB_RPT_gtc_timebase_START  (16)
#define CBBP_GTC_QB_RPT_gtc_timebase_END    (28)


/*****************************************************************************
 �ṹ��    : CBBP_TIMEBASE_RPT_UNION
 �ṹ˵��  : TIMEBASE_RPT �Ĵ����ṹ���塣��ַƫ����:0x20����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      timebase_rpt_reg;
    struct
    {
        unsigned long  gtc_timebase_qb     : 13; /* bit[0-12] : ����ʱ��QB�ϱ���������Χ0~4999����Ӧһ֡�ĳ��ȡ���ֵֻ�븴λʱ���йأ������� */
        unsigned long  reserved_0          : 3;  /* bit[13-15]: ���� */
        unsigned long  gtc_timebase_fn_low : 11; /* bit[16-26]: ����ʱ��֡���ϱ�����ֵ�仯ʱ����gtc_timebase_qbΪ4999����������Χ0~2047�������� */
        unsigned long  reserved_1          : 5;  /* bit[27-31]: ���� */
    } reg;
} CBBP_TIMEBASE_RPT_UNION;
#define CBBP_TIMEBASE_RPT_gtc_timebase_qb_START      (0)
#define CBBP_TIMEBASE_RPT_gtc_timebase_qb_END        (12)
#define CBBP_TIMEBASE_RPT_gtc_timebase_fn_low_START  (16)
#define CBBP_TIMEBASE_RPT_gtc_timebase_fn_low_END    (26)


/*****************************************************************************
 �ṹ��    : CBBP_G2_CPU_INT_STA_UNION
 �ṹ˵��  : G2_CPU_INT_STA �Ĵ����ṹ���塣��ַƫ����:0x24����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      g2_cpu_int_sta_reg;
    struct
    {
        unsigned long  int_state_cpu : 30; /* bit[0-29] : [0] TDMA֡�ж�����1��ʾ�ж�����0��ʾ���ж�������ͬ
                                                          [1] GTC PAGE�ж�����
                                                          [2] ͬ�������ж�����
                                                          [3] ���������ϱ��ж�����
                                                          [4] ʱ϶0�ж�����1��Ч
                                                          [5] ʱ϶1�ж�����
                                                          [6] ʱ϶2�ж�����
                                                          [7] ʱ϶3�ж�����
                                                          [8] ʱ϶4�ж�����
                                                          [9] ʱ϶5�ж�����
                                                          [10] ʱ϶6�ж�����
                                                          [11] ʱ϶7�ж�����
                                                          [12] �ɱ���ж�0����
                                                          [13] �ɱ���ж�1����
                                                          [14] �ɱ���ж�2����
                                                          [15] �ɱ���ж�3����
                                                          [16] �ɱ���ж�4����
                                                          [17] �ɱ���ж�5����
                                                          [18] �ɱ���ж�6����
                                                          [19] �ɱ���ж�7����
                                                          [23:20]����
                                                          [24] ʱ�Ӳ����ж�
                                                          [28] ��ƽ���������ж�
                                                          [29] ��������ж� */
        unsigned long  reserved      : 2;  /* bit[30-31]: ���� */
    } reg;
} CBBP_G2_CPU_INT_STA_UNION;
#define CBBP_G2_CPU_INT_STA_int_state_cpu_START  (0)
#define CBBP_G2_CPU_INT_STA_int_state_cpu_END    (29)


/*****************************************************************************
 �ṹ��    : CBBP_G2_CPU_INT_MASK_UNION
 �ṹ˵��  : G2_CPU_INT_MASK �Ĵ����ṹ���塣��ַƫ����:0x28����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      g2_cpu_int_mask_reg;
    struct
    {
        unsigned long  cpu_int_mask : 30; /* bit[0-29] : [0] TDMA֡�ж������źţ�1��ʾ�ж��������Σ�0��ʾ���жϲ����Σ���ͬ
                                                         [1] GTC PAGE�ж����μĴ���
                                                         [2] ͬ�������ж����μĴ���
                                                         [3] ���������ϱ��ж����μĴ���
                                                         [4] ʱ϶0�ж����μĴ�����1��Ч
                                                         [5] ʱ϶1�ж����μĴ���
                                                         [6] ʱ϶2�ж����μĴ���
                                                         [7] ʱ϶3�ж����μĴ���
                                                         [8] ʱ϶4�ж����μĴ���
                                                         [9] ʱ϶5�ж����μĴ���
                                                         [10] ʱ϶6�ж����μĴ���
                                                         [11] ʱ϶7�ж����μĴ���
                                                         [12] �ɱ���ж�0���μĴ���
                                                         [13] �ɱ���ж�1���μĴ���
                                                         [14] �ɱ���ж�2���μĴ���
                                                         [15] �ɱ���ж�3���μĴ���
                                                         [16] �ɱ���ж�4���μĴ���
                                                         [17] �ɱ���ж�5���μĴ���
                                                         [18] �ɱ���ж�6���μĴ���
                                                         [19] �ɱ���ж�7���μĴ���
                                                         [24] ʱ�Ӳ����ж����μĴ���
                                                         [28] ��ƽ���������ж����μĴ���
                                                         [29] ��������ж����μĴ��� */
        unsigned long  reserved     : 2;  /* bit[30-31]: ���� */
    } reg;
} CBBP_G2_CPU_INT_MASK_UNION;
#define CBBP_G2_CPU_INT_MASK_cpu_int_mask_START  (0)
#define CBBP_G2_CPU_INT_MASK_cpu_int_mask_END    (29)


/*****************************************************************************
 �ṹ��    : CBBP_G2_CPU_INT_CLR_UNION
 �ṹ˵��  : G2_CPU_INT_CLR �Ĵ����ṹ���塣��ַƫ����:0x2C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      g2_cpu_int_clr_reg;
    struct
    {
        unsigned long  cpu_int_clr : 30; /* bit[0-29] : [0] TDMA֡�ж������źţ�1��ʾ�ж����������0��ʾ���жϲ����
                                                        ����������ͬ
                                                        [1] GTC PAGE�ж�����Ĵ���
                                                        [2] ͬ�������ж������ź�
                                                        [3] ���������ϱ��ж������ź�
                                                        [4] ʱ϶0�ж������źţ�1��Ч
                                                        [5] ʱ϶1�ж������ź�
                                                        [6] ʱ϶2�ж������ź�
                                                        [7] ʱ϶3�ж������ź�
                                                        [8] ʱ϶4�ж������ź�
                                                        [9] ʱ϶5�ж������ź�
                                                        [10] ʱ϶6�ж������ź�
                                                        [11] ʱ϶7�ж������ź�
                                                        [12] �ɱ���ж�0�����ź�
                                                        [13] �ɱ���ж�1�����ź�
                                                        [14] �ɱ���ж�2�����ź�
                                                        [15] �ɱ���ж�3�����ź�
                                                        [16] �ɱ���ж�4�����ź�
                                                        [17] �ɱ���ж�5�����ź�
                                                        [18] �ɱ���ж�6�����ź�
                                                        [19] �ɱ���ж�7�����ź�
                                                        [24] ʱ�Ӳ����ж������ź�
                                                        [28] ��ƽ���������ж������ź�
                                                        [29] ��������ж������ź� */
        unsigned long  reserved    : 2;  /* bit[30-31]: ���� */
    } reg;
} CBBP_G2_CPU_INT_CLR_UNION;
#define CBBP_G2_CPU_INT_CLR_cpu_int_clr_START  (0)
#define CBBP_G2_CPU_INT_CLR_cpu_int_clr_END    (29)


/*****************************************************************************
 �ṹ��    : CBBP_G2_DSP_INT_STA_UNION
 �ṹ˵��  : G2_DSP_INT_STA �Ĵ����ṹ���塣��ַƫ����:0x30����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      g2_dsp_int_sta_reg;
    struct
    {
        unsigned long  dsp_int_sta : 30; /* bit[0-29] : [0] TDMA֡�ж�����1��ʾ�ж�����0��ʾ���ж�������ͬ
                                                        [1] GTC PAGE�ж�����
                                                        [2] ͬ�������ж�����
                                                        [3] ���������ϱ��ж�����
                                                        [4] ʱ϶0�ж�����1��Ч
                                                        [5] ʱ϶1�ж�����
                                                        [6] ʱ϶2�ж�����
                                                        [7] ʱ϶3�ж�����
                                                        [8] ʱ϶4�ж�����
                                                        [9] ʱ϶5�ж�����
                                                        [10] ʱ϶6�ж�����
                                                        [11] ʱ϶7�ж�����
                                                        [12] �ɱ���ж�0����
                                                        [13] �ɱ���ж�1����
                                                        [14] �ɱ���ж�2����
                                                        [15] �ɱ���ж�3����
                                                        [16] �ɱ���ж�4����
                                                        [17] �ɱ���ж�5����
                                                        [18] �ɱ���ж�6����
                                                        [19] �ɱ���ж�7����
                                                        [24] CTU��ϵͳ�����ж�0
                                                        [25] CTU��ϵͳ�����ж�1
                                                        [26] CTU��ϵͳ�����ж�2
                                                        [27] ʱ�Ӳ����ж�
                                                        [28] ��ƽ���������ж�
                                                        [29]  ��������ж� */
        unsigned long  reserved    : 2;  /* bit[30-31]: ���� */
    } reg;
} CBBP_G2_DSP_INT_STA_UNION;
#define CBBP_G2_DSP_INT_STA_dsp_int_sta_START  (0)
#define CBBP_G2_DSP_INT_STA_dsp_int_sta_END    (29)


/*****************************************************************************
 �ṹ��    : CBBP_G2_DSP_INT_MASK_UNION
 �ṹ˵��  : G2_DSP_INT_MASK �Ĵ����ṹ���塣��ַƫ����:0x34����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      g2_dsp_int_mask_reg;
    struct
    {
        unsigned long  dsp_int_mask : 30; /* bit[0-29] : [0] TDMA֡�ж������źţ�1��ʾ�ж��������Σ�0��ʾ���жϲ�����
                                                         [1] GTC PAGE�ж����μĴ���
                                                         [2] ͬ�������ж����μĴ���
                                                         [3] ���������ϱ��ж����μĴ���
                                                         [4] ʱ϶0�ж����μĴ�����1��Ч
                                                         [5] ʱ϶1�ж����μĴ���
                                                         [6] ʱ϶2�ж����μĴ���
                                                         [7] ʱ϶3�ж����μĴ���
                                                         [8] ʱ϶4�ж����μĴ���
                                                         [9] ʱ϶5�ж����μĴ���
                                                         [10] ʱ϶6�ж����μĴ���
                                                         [11] ʱ϶7�ж����μĴ���
                                                         [12] �ɱ���ж�0���μĴ���
                                                         [13] �ɱ���ж�1���μĴ���
                                                         [14] �ɱ���ж�2���μĴ���
                                                         [15] �ɱ���ж�3���μĴ���
                                                         [16] �ɱ���ж�4���μĴ���
                                                         [17] �ɱ���ж�5���μĴ���
                                                         [18] �ɱ���ж�6���μĴ���
                                                         [19] �ɱ���ж�7���μĴ���
                                                         [24] CTU��ϵͳ�����ж�0
                                                         [25] CTU��ϵͳ�����ж�1
                                                         [26] CTU��ϵͳ�����ж�2
                                                         [27] ʱ�Ӳ����ж�
                                                         [28] ��ƽ���������ж����μĴ���
                                                         [29] ��������ж����μĴ��� */
        unsigned long  reserved     : 2;  /* bit[30-31]: ���� */
    } reg;
} CBBP_G2_DSP_INT_MASK_UNION;
#define CBBP_G2_DSP_INT_MASK_dsp_int_mask_START  (0)
#define CBBP_G2_DSP_INT_MASK_dsp_int_mask_END    (29)


/*****************************************************************************
 �ṹ��    : CBBP_G2_DSP_INT_CLR_UNION
 �ṹ˵��  : G2_DSP_INT_CLR �Ĵ����ṹ���塣��ַƫ����:0x38����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      g2_dsp_int_clr_reg;
    struct
    {
        unsigned long  dsp_int_clr : 30; /* bit[0-29] : [0] TDMA֡�ж������źţ�1��ʾ�ж����������0��ʾ���жϲ����
                                                        [1] GTC PAGE�ж�����Ĵ���
                                                        [2] ͬ�������ж������ź�
                                                        [3] ���������ϱ��ж������ź�
                                                        [4] ʱ϶0�ж������źţ�1��Ч
                                                        [5] ʱ϶1�ж������ź�
                                                        [6] ʱ϶2�ж������ź�
                                                        [7] ʱ϶3�ж������ź�
                                                        [8] ʱ϶4�ж������ź�
                                                        [9] ʱ϶5�ж������ź�
                                                        [10] ʱ϶6�ж������ź�
                                                        [11] ʱ϶7�ж������ź�
                                                        [12] �ɱ���ж�0�����ź�
                                                        [13] �ɱ���ж�1�����ź�
                                                        [14] �ɱ���ж�2�����ź�
                                                        [15] �ɱ���ж�3�����ź�
                                                        [16] �ɱ���ж�4�����ź�
                                                        [17] �ɱ���ж�5�����ź�
                                                        [18] �ɱ���ж�6�����ź�
                                                        [19] �ɱ���ж�7�����ź�
                                                        [23:20]����
                                                        [24] CTU��ϵͳ�����ж�0
                                                        [25] CTU��ϵͳ�����ж�1
                                                        [26] CTU��ϵͳ�����ж�2
                                                        [27] ʱ�Ӳ����ж�
                                                        [28] ��ƽ���������ж������ź�
                                                        [29] ��������ж������ź� */
        unsigned long  reserved    : 2;  /* bit[30-31]: ���� */
    } reg;
} CBBP_G2_DSP_INT_CLR_UNION;
#define CBBP_G2_DSP_INT_CLR_dsp_int_clr_START  (0)
#define CBBP_G2_DSP_INT_CLR_dsp_int_clr_END    (29)


/*****************************************************************************
 �ṹ��    : CBBP_TDMA_SLOT_INT1_UNION
 �ṹ˵��  : TDMA_SLOT_INT1 �Ĵ����ṹ���塣��ַƫ����:0x40����ֵ:0x00FF0000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      tdma_slot_int1_reg;
    struct
    {
        unsigned long  tdma_slot_int1_offset : 10; /* bit[0-9]  : G�������ö�ʱ�ж�ʱ϶��λ�ã�ȡֵ��Χ0~624����λQb */
        unsigned long  reserved_0            : 6;  /* bit[10-15]: ���� */
        unsigned long  tdma_slot_int1_mask   : 8;  /* bit[16-23]: G�������ö�ʱ�ж�mask��
                                                                  bit16��1��ʾ����tdma֡��ʱ϶0���жϣ�
                                                                  bit17��1��ʾ����tdma֡��ʱ϶1���жϣ�
                                                                  �� */
        unsigned long  reserved_1            : 8;  /* bit[24-31]: ���� */
    } reg;
} CBBP_TDMA_SLOT_INT1_UNION;
#define CBBP_TDMA_SLOT_INT1_tdma_slot_int1_offset_START  (0)
#define CBBP_TDMA_SLOT_INT1_tdma_slot_int1_offset_END    (9)
#define CBBP_TDMA_SLOT_INT1_tdma_slot_int1_mask_START    (16)
#define CBBP_TDMA_SLOT_INT1_tdma_slot_int1_mask_END      (23)


/*****************************************************************************
 �ṹ��    : CBBP_TDMA_SLOT_INT2_UNION
 �ṹ˵��  : TDMA_SLOT_INT2 �Ĵ����ṹ���塣��ַƫ����:0x44����ֵ:0x00FF0000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      tdma_slot_int2_reg;
    struct
    {
        unsigned long  tdma_slot_int2_offset : 10; /* bit[0-9]  : G�������ö�ʱ�ж�ʱ϶��λ�ã�ȡֵ��Χ0~624����λQb */
        unsigned long  reserved_0            : 6;  /* bit[10-15]: ���� */
        unsigned long  tdma_slot_int2_mask   : 8;  /* bit[16-23]: G�������ö�ʱ�ж�mask��
                                                                  bit16��1��ʾ����tdma֡��ʱ϶0���жϣ�
                                                                  bit17��1��ʾ����tdma֡��ʱ϶1���жϣ�
                                                                  �� */
        unsigned long  reserved_1            : 8;  /* bit[24-31]: ���� */
    } reg;
} CBBP_TDMA_SLOT_INT2_UNION;
#define CBBP_TDMA_SLOT_INT2_tdma_slot_int2_offset_START  (0)
#define CBBP_TDMA_SLOT_INT2_tdma_slot_int2_offset_END    (9)
#define CBBP_TDMA_SLOT_INT2_tdma_slot_int2_mask_START    (16)
#define CBBP_TDMA_SLOT_INT2_tdma_slot_int2_mask_END      (23)


/*****************************************************************************
 �ṹ��    : CBBP_GDRX_SLEEP_POINT_UNION
 �ṹ˵��  : GDRX_SLEEP_POINT �Ĵ����ṹ���塣��ַƫ����:0x048����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      gdrx_sleep_point_reg;
    struct
    {
        unsigned long  gdrx_sleep_point : 13; /* bit[0-12] : ����˯��ģʽ�£�˯����ʼQbʱ�̣�TDMA��ʱ�̣��ò����ǻ���TDMAʱ��gtc_tdma_qb�ġ� */
        unsigned long  reserved         : 19; /* bit[13-31]: ���� */
    } reg;
} CBBP_GDRX_SLEEP_POINT_UNION;
#define CBBP_GDRX_SLEEP_POINT_gdrx_sleep_point_START  (0)
#define CBBP_GDRX_SLEEP_POINT_gdrx_sleep_point_END    (12)


/*****************************************************************************
 �ṹ��    : CBBP_CPU_TRANS_COMP_UNION
 �ṹ˵��  : CPU_TRANS_COMP �Ĵ����ṹ���塣��ַƫ����:0x04C����ֵ:0x00000010�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      cpu_trans_comp_reg;
    struct
    {
        unsigned long  cpu_trans_comp : 10; /* bit[0-9]  : DRX�����Ż���ON����OFF����������λQb��Ĭ��ֵ16 */
        unsigned long  reserved       : 22; /* bit[10-31]: ���� */
    } reg;
} CBBP_CPU_TRANS_COMP_UNION;
#define CBBP_CPU_TRANS_COMP_cpu_trans_comp_START  (0)
#define CBBP_CPU_TRANS_COMP_cpu_trans_comp_END    (9)


/***======================================================================***
                     (20/20) register_define_sdr_g_int
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : CBBP_DSP_SDR_G_INT_EN_UNION
 �ṹ˵��  : DSP_SDR_G_INT_EN �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_sdr_g_int_en_reg;
    struct
    {
        unsigned long  dsp_sdr_g_int_en : 1;  /* bit[0]   : �͸�DSP��g���ж�ʹ�ܣ�1��ʾ���ж� */
        unsigned long  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_DSP_SDR_G_INT_EN_UNION;
#define CBBP_DSP_SDR_G_INT_EN_dsp_sdr_g_int_en_START  (0)
#define CBBP_DSP_SDR_G_INT_EN_dsp_sdr_g_int_en_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_DSP_SDR_G_INT_CLR_UNION
 �ṹ˵��  : DSP_SDR_G_INT_CLR �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_sdr_g_int_clr_reg;
    struct
    {
        unsigned long  dsp_sdr_g_int_clr : 2;  /* bit[0-1] : �ж������źţ��������1�������Ӧ��bit
                                                             bit0��������g��ʱ�ж�1��
                                                             bit1��������g��ʱ�ж�2�� */
        unsigned long  reserved          : 30; /* bit[2-31]: ���� */
    } reg;
} CBBP_DSP_SDR_G_INT_CLR_UNION;
#define CBBP_DSP_SDR_G_INT_CLR_dsp_sdr_g_int_clr_START  (0)
#define CBBP_DSP_SDR_G_INT_CLR_dsp_sdr_g_int_clr_END    (1)


/*****************************************************************************
 �ṹ��    : CBBP_DSP_SDR_G_INT_MASK_UNION
 �ṹ˵��  : DSP_SDR_G_INT_MASK �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000003�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_sdr_g_int_mask_reg;
    struct
    {
        unsigned long  dsp_sdr_g_int_mask : 2;  /* bit[0-1] : �ж�mask�źţ��������1����Ӧ��bit�жϲ�����
                                                              bit0��������g��ʱ�ж�1��
                                                              bit1��������g��ʱ�ж�2�� */
        unsigned long  reserved           : 30; /* bit[2-31]: ���� */
    } reg;
} CBBP_DSP_SDR_G_INT_MASK_UNION;
#define CBBP_DSP_SDR_G_INT_MASK_dsp_sdr_g_int_mask_START  (0)
#define CBBP_DSP_SDR_G_INT_MASK_dsp_sdr_g_int_mask_END    (1)


/*****************************************************************************
 �ṹ��    : CBBP_DSP_SDR_G_INT_STA_UNION
 �ṹ˵��  : DSP_SDR_G_INT_STA �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_sdr_g_int_sta_reg;
    struct
    {
        unsigned long  dsp_sdr_g_int_sta : 2;  /* bit[0-1] : �ж�״̬�źţ�1��ʾ��Ӧ���ж��ϱ�
                                                             bit0��������g��ʱ�ж�1��
                                                             bit1��������g��ʱ�ж�2�� */
        unsigned long  reserved          : 30; /* bit[2-31]: ���� */
    } reg;
} CBBP_DSP_SDR_G_INT_STA_UNION;
#define CBBP_DSP_SDR_G_INT_STA_dsp_sdr_g_int_sta_START  (0)
#define CBBP_DSP_SDR_G_INT_STA_dsp_sdr_g_int_sta_END    (1)


/*****************************************************************************
 �ṹ��    : CBBP_ARM_SDR_G_INT_EN_UNION
 �ṹ˵��  : ARM_SDR_G_INT_EN �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_sdr_g_int_en_reg;
    struct
    {
        unsigned long  arm_sdr_g_int_en : 1;  /* bit[0]   : �͸�ARM��g���ж�ʹ�ܣ�1��ʾ���ж� */
        unsigned long  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} CBBP_ARM_SDR_G_INT_EN_UNION;
#define CBBP_ARM_SDR_G_INT_EN_arm_sdr_g_int_en_START  (0)
#define CBBP_ARM_SDR_G_INT_EN_arm_sdr_g_int_en_END    (0)


/*****************************************************************************
 �ṹ��    : CBBP_ARM_SDR_G_INT_CLR_UNION
 �ṹ˵��  : ARM_SDR_G_INT_CLR �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_sdr_g_int_clr_reg;
    struct
    {
        unsigned long  arm_sdr_g_int_clr : 2;  /* bit[0-1] : ARM�ж������źţ��������1�������Ӧ��bit
                                                             bit0��������g��ʱ�ж�1��
                                                             bit1��������g��ʱ�ж�2�� */
        unsigned long  reserved          : 30; /* bit[2-31]: ���� */
    } reg;
} CBBP_ARM_SDR_G_INT_CLR_UNION;
#define CBBP_ARM_SDR_G_INT_CLR_arm_sdr_g_int_clr_START  (0)
#define CBBP_ARM_SDR_G_INT_CLR_arm_sdr_g_int_clr_END    (1)


/*****************************************************************************
 �ṹ��    : CBBP_ARM_SDR_G_INT_MASK_UNION
 �ṹ˵��  : ARM_SDR_G_INT_MASK �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000003�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_sdr_g_int_mask_reg;
    struct
    {
        unsigned long  arm_sdr_g_int_mask : 2;  /* bit[0-1] : ARM�ж�mask�źţ��������1����Ӧ��bit�жϲ�����
                                                              bit0��������g��ʱ�ж�1��
                                                              bit1��������g��ʱ�ж�2�� */
        unsigned long  reserved           : 30; /* bit[2-31]: ���� */
    } reg;
} CBBP_ARM_SDR_G_INT_MASK_UNION;
#define CBBP_ARM_SDR_G_INT_MASK_arm_sdr_g_int_mask_START  (0)
#define CBBP_ARM_SDR_G_INT_MASK_arm_sdr_g_int_mask_END    (1)


/*****************************************************************************
 �ṹ��    : CBBP_ARM_SDR_G_INT_STA_UNION
 �ṹ˵��  : ARM_SDR_G_INT_STA �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_sdr_g_int_sta_reg;
    struct
    {
        unsigned long  arm_sdr_g_int_sta : 2;  /* bit[0-1] : ARM�ж�״̬�źţ�1��ʾ��Ӧ���ж��ϱ�
                                                             bit0��������g��ʱ�ж�1��
                                                             bit1��������g��ʱ�ж�2�� */
        unsigned long  reserved          : 30; /* bit[2-31]: ���� */
    } reg;
} CBBP_ARM_SDR_G_INT_STA_UNION;
#define CBBP_ARM_SDR_G_INT_STA_arm_sdr_g_int_sta_START  (0)
#define CBBP_ARM_SDR_G_INT_STA_arm_sdr_g_int_sta_END    (1)




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

#endif /* end of bbp_cdma_interface.h */
