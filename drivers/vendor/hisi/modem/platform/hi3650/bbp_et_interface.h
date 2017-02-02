

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __BBP_ET_INTERFACE_H__
#define __BBP_ET_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/***======================================================================***
                     (1/1) register_define_et
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31:1]   ������
 bit[0]      et��λ�źš�
             1����ʾ��λ
             0����ʾ�帴λ
   UNION�ṹ:  ET_ET_SOFT_RST_UNION */
#define ET_ET_SOFT_RST_ADDR                           (SOC_BBP_ET_BASE_ADDR + 0x0)

/* �Ĵ���˵����
 bit[31:16]  spram mem_ctrl
 bit[15:0]   tpram mem_ctrl
   UNION�ṹ:  ET_ET_RAM_CTRL0_UNION */
#define ET_ET_RAM_CTRL0_ADDR                          (SOC_BBP_ET_BASE_ADDR + 0x4)

/* �Ĵ���˵����
 bit[31:8]   ������
 bit[7:6]    PA�ߵ�λƥ��ָʾ�źš�����߿��ź�com2et_tx_pa_mode����ֶ�
             ƥ�䣬����ȷ��PA�ǹ����ڸ�����ģʽ��
 bit[5:4]    PA�е�λƥ��ָʾ�źš�����߿��ź�com2et_tx_pa_mode��dsp_pa_high_ctrl��ƥ�䵫����ֶ�ƥ�䣬����ȷ��PA�ǹ�����������ģʽ��
 bit[3:0]    ������
   UNION�ṹ:  ET_PA_PARA_UNION */
#define ET_PA_PARA_ADDR                               (SOC_BBP_ET_BASE_ADDR + 0x8)

/* �Ĵ���˵����
 bit[31:9]   ������
 bit[8:0]    ��Ƶ����ͨ·�ӳ�����ֵ����com2et_tx_clkʱ��Ƶ�ʺ�����ͨ·������֮��Ϊ4:1ʱ��ȡֵ��ΧΪ0~508����Ϊ2:1ʱ��ȡֵ��ΧΪ0~254����λΪ����ͨ·ʱ�����ڡ�
             
   UNION�ṹ:  ET_RF_DATA_DLY_UNION */
#define ET_RF_DATA_DLY_ADDR                           (SOC_BBP_ET_BASE_ADDR + 0xC)

/* �Ĵ���˵����
 bit[31:2]   ������
 bit[1:0]    L/Wģʽѡ��
             01: LTE mode, 
             10: W mode, 
             00: L/W����Ч��ETģ����ʱ�ӣ����Զ�������λ����������״̬ʱ�⸴λ
             11: ��Ч״̬
             
             �����Lģ�е�Wģ��lw_mode_sel�仯����2'b01 -> 2'b00����λ�� -> 2'b10
   UNION�ṹ:  ET_LW_MODE_SEL_UNION */
#define ET_LW_MODE_SEL_ADDR                           (SOC_BBP_ET_BASE_ADDR + 0x10)

/* �Ĵ���˵����
 bit[31:1]   ������
 bit[0]      ����ر�ET0ͨ����
             1'b1 : ET0����������Ĭ��ֵ��
             1'b0 : ET0�رգ�ʱ���ſأ��߼���λ��
             
             ע���رմ˼Ĵ�����Ӱ��ET0 txͨ·���ݷ��͡�
   UNION�ṹ:  ET_SOFT_EN_UNION */
#define ET_SOFT_EN_ADDR                               (SOC_BBP_ET_BASE_ADDR + 0x14)

/* �Ĵ���˵����
   ��      ������λ�ð���һ����Ϊ256x32��RAM�����ڱ��湦�ʵ�ѹӳ����ұ���ͨ���������߷��ʸ�RAMʱ��������������λ��RAM�洢��Ԫ����λ֮��Ķ�Ӧ��ϵ���£�
            ������������λ    RAM��Ԫ����λ
               31:30            N/A
               29:16            29;16
               15:14            N/A
               13:0              13:0
            
            et����ͨ·����ʱ����ֹ���߶�д�ñ�
   UNION�ṹ ���� */
#define ET_PWR_VOLT_LUT_ADDR                          (SOC_BBP_ET_BASE_ADDR + 0x800)

/* �Ĵ���˵����
 bit[31:6]   ����
 bit[5]      ����ת��������Ƶ���ʹ��㹦��bypass�źš�
             
             0����bypass�ù��ܡ�
             1��bypass�ù��ܡ�
             
 bit[4]      �������FIR�˲���������·���ơ�
             
             0����bypass�ù��ܡ�
             1��bypass�ù��ܡ�
             
 bit[3]      Ⱥ�ӳ�IIR�˲���������·���ơ�
             
             0����bypass�ù��ܡ�
             1��bypass�ù��ܡ�
             
 bit[2]      ��ѹ������������·���ơ�
             
             0����bypass�ù��ܡ�
             1��bypass�ù��ܡ�
             
 bit[1]      �����ްڹ���bypass�źš�
             0����bypass�ù��ܡ�
             1��bypass�ù��ܡ�
 bit[0]      �����޵׹���bypass�źš�
             0����bypass�ù��ܡ�
             1��bypass�ù��ܡ�
   UNION�ṹ:  ET_ET_BYPASS_CTRL_UNION */
#define ET_ET_BYPASS_CTRL_ADDR                        (SOC_BBP_ET_BASE_ADDR + 0xC00)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ET�����Զ��ſ���·�źš�
             0���Զ��ſز���·��
             1���Զ��ſ���·��
   UNION�ṹ:  ET_ET_CKG_BYPASS_UNION */
#define ET_ET_CKG_BYPASS_ADDR                         (SOC_BBP_ET_BASE_ADDR + 0xC04)

/* �Ĵ���˵����
 bit[31:8]   ����
 bit[7:0]    ET�����ź�ͨ·�ӳ�����ֵ���ӳ����÷�Χ0~254����С�ӳٵ�λΪ1����·ʱ�����ڣ���122Mʱ�������8.138ns
   UNION�ṹ:  ET_ET_DELAY_PARA_UNION */
#define ET_ET_DELAY_PARA_ADDR                         (SOC_BBP_ET_BASE_ADDR + 0xC08)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��������������������ϲ���ѡ��
             1'b0: ��2���ϲ�����
             1'b1: �����ϲ���
   UNION�ṹ:  ET_ET_UPSAMPLE_SEL_UNION */
#define ET_ET_UPSAMPLE_SEL_ADDR                       (SOC_BBP_ET_BASE_ADDR + 0xC18)

/* �Ĵ���˵����
 bit[31:6]   ����
 bit[5:4]    ��0������ӳ��˲�����ֵ����ѡ��
             �˴������Ÿ����ʹ�ã�ֻ����Ĭ��ֵ2'b01 ��
             00����ʾ��ֵ�˲�������λ��x(n+1)��
             01����ʾ��ֵ�˲�������λ��x(n)��
             10����ʾ��ֵ�˲�������λ��x(n-1)��
             11����Ч���á�
 bit[3:2]    ����
 bit[1:0]    ��1������ӳ��˲�����ֵ����ѡ��
             �˴������Ÿ����ʹ�ã�ֻ����Ĭ��ֵ2'b01 ��
             00����ʾ��ֵ�˲�������λ��x(n+1)��
             01����ʾ��ֵ�˲�������λ��x(n)��
             10����ʾ��ֵ�˲�������λ��x(n-1)��
             11����Ч���á�
   UNION�ṹ:  ET_ET_INT_FILTER_CTRL_UNION */
#define ET_ET_INT_FILTER_CTRL_ADDR                    (SOC_BBP_ET_BASE_ADDR + 0xC1C)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  �����ӳ��˲���0��ϵ��0��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á�
 bit[15:12]  ����
 bit[11:0]   �����ӳ��˲���0��ϵ��1��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á�
   UNION�ṹ:  ET_ET_FINE_0DELAY_PARA_0_UNION */
#define ET_ET_FINE_0DELAY_PARA_0_ADDR                 (SOC_BBP_ET_BASE_ADDR + 0xC20)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  �����ӳ��˲���0��ϵ��2��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á�
 bit[15:12]  ����
 bit[11:0]   �����ӳ��˲���0��ϵ��3��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á�
   UNION�ṹ:  ET_ET_FINE_0DELAY_PARA_1_UNION */
#define ET_ET_FINE_0DELAY_PARA_1_ADDR                 (SOC_BBP_ET_BASE_ADDR + 0xC24)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  �����ӳ��˲���0��ϵ��4��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á�
 bit[15:12]  ����
 bit[11:0]   �����ӳ��˲���0��ϵ��5��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á�
   UNION�ṹ:  ET_ET_FINE_0DELAY_PARA_2_UNION */
#define ET_ET_FINE_0DELAY_PARA_2_ADDR                 (SOC_BBP_ET_BASE_ADDR + 0xC28)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  �����ӳ��˲���0��ϵ��6��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á�
 bit[15:12]  ����
 bit[11:0]   �����ӳ��˲���0��ϵ��7��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á�
   UNION�ṹ:  ET_ET_FINE_0DELAY_PARA_3_UNION */
#define ET_ET_FINE_0DELAY_PARA_3_ADDR                 (SOC_BBP_ET_BASE_ADDR + 0xC2C)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  �����ӳ��˲���0��ϵ��8��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á�
 bit[15:0]   ����
   UNION�ṹ:  ET_ET_FINE_0DELAY_PARA_4_UNION */
#define ET_ET_FINE_0DELAY_PARA_4_ADDR                 (SOC_BBP_ET_BASE_ADDR + 0xC30)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  �����ӳ��˲���1��ϵ��0��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á�
 bit[15:12]  ����
 bit[11:0]   �����ӳ��˲���1��ϵ��1��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á�
   UNION�ṹ:  ET_ET_FINE_1DELAY_PARA_0_UNION */
#define ET_ET_FINE_1DELAY_PARA_0_ADDR                 (SOC_BBP_ET_BASE_ADDR + 0xC34)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  �����ӳ��˲���1��ϵ��2��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á�
 bit[15:12]  ����
 bit[11:0]   �����ӳ��˲���1��ϵ��3��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á�
   UNION�ṹ:  ET_ET_FINE_1DELAY_PARA_1_UNION */
#define ET_ET_FINE_1DELAY_PARA_1_ADDR                 (SOC_BBP_ET_BASE_ADDR + 0xC38)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  �����ӳ��˲���1��ϵ��4��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á�
 bit[15:12]  ����
 bit[11:0]   �����ӳ��˲���1��ϵ��5��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á�
   UNION�ṹ:  ET_ET_FINE_1DELAY_PARA_2_UNION */
#define ET_ET_FINE_1DELAY_PARA_2_ADDR                 (SOC_BBP_ET_BASE_ADDR + 0xC3C)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  �����ӳ��˲���1��ϵ��6��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á�
 bit[15:12]  ����
 bit[11:0]   �����ӳ��˲���1��ϵ��7��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á�
   UNION�ṹ:  ET_ET_FINE_1DELAY_PARA_3_UNION */
#define ET_ET_FINE_1DELAY_PARA_3_ADDR                 (SOC_BBP_ET_BASE_ADDR + 0xC40)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  �����ӳ��˲���1��ϵ��8��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á�
 bit[15:0]   ����
   UNION�ṹ:  ET_ET_FINE_1DELAY_PARA_4_UNION */
#define ET_ET_FINE_1DELAY_PARA_4_ADDR                 (SOC_BBP_ET_BASE_ADDR + 0xC44)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    �ӳ�ȡ����ܵ��ӳٲ�����4bit�޷�������ȡֵN��0��15��
   UNION�ṹ:  ET_ET_ENV_PROC_PARA1_UNION */
#define ET_ET_ENV_PROC_PARA1_ADDR                     (SOC_BBP_ET_BASE_ADDR + 0xC4C)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  ����Detrough���������������޵����ޡ�12bit�޷�������
 bit[15:6]   ����
 bit[5:0]    ����Detrough�������޵����Ƴ�ϵ����6bit�޷�������
   UNION�ṹ:  ET_ET_ENV_PROC_PARA2_UNION */
#define ET_ET_ENV_PROC_PARA2_ADDR                     (SOC_BBP_ET_BASE_ADDR + 0xC50)

/* �Ĵ���˵����
 bit[31:14]  ����
 bit[13:0]   ��Ƶ���繦�ʼ��������������ڲ���ֵ��14λ�з�������Ĭ��ֵ-4840������0.0125dB����-60.5dB��
   UNION�ṹ:  ET_ET_ENV_PROC_PARA3_UNION */
#define ET_ET_ENV_PROC_PARA3_ADDR                     (SOC_BBP_ET_BASE_ADDR + 0xC54)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��dsp_pa_ctrl_mode=0ʱ����ʱ��������Ҫ�����ڸߡ�����������ģʽ�£�
             
             ��dsp_pa_ctrl_mode=1ʱ����ʱ���������Ҫ�����ڸ�����ģʽ�£��߿��ź�et_tx_pa_modeӦ��֤��Ĵ����ֶ�dsp_pa_high_ctrl��ֵ��ͬ��
   UNION�ṹ:  ET_ET_PA_CTRL_UNION */
#define ET_ET_PA_CTRL_ADDR                            (SOC_BBP_ET_BASE_ADDR + 0xC58)

/* �Ĵ���˵����
 bit[31:29]  ����
 bit[28:16]  �ް��������ޣ�ȱʡֵ1600��ȡֵ��Χ0~8191���޷�����
 bit[15:13]  ����
 bit[12:0]   �ް��������ޣ�W��Ĭ��ֵ1600��LTE���Զ��壬ȡֵ��Χ0~8191���޷�����
   UNION�ṹ:  ET_ET_LIMIT_ENV_SLEW_PARA_UNION */
#define ET_ET_LIMIT_ENV_SLEW_PARA_ADDR                (SOC_BBP_ET_BASE_ADDR + 0xC60)

/* �Ĵ���˵����
 bit[31:23]  ����
 bit[22:13]  ���߲��𲹳������ֶβ����Ÿ����ʹ�á���д��üĴ���ʱ��Ӧȷ�����ֶ�ʼ��д��0x000���з���������ά�ɲ⹦��
 bit[12:0]   ����ת����ǰʹ�õ�ƫ�ơ�13λ�з���ֵ��
   UNION�ṹ:  ET_ET_ENV_TOP_EXTRA_PARA_UNION */
#define ET_ET_ENV_TOP_EXTRA_PARA_ADDR                 (SOC_BBP_ET_BASE_ADDR + 0xC68)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  Ⱥ�ӳپ�����IIR�˲���ϵ��a11���з�������
 bit[15:12]  ����
 bit[11:0]   Ⱥ�ӳپ�����IIR�˲���ϵ��a12���з�������
   UNION�ṹ:  ET_ET_IIR_COEF_0_1_PARA_UNION */
#define ET_ET_IIR_COEF_0_1_PARA_ADDR                  (SOC_BBP_ET_BASE_ADDR + 0xC6C)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  Ⱥ�ӳپ�����IIR�˲���ϵ��b11���з�������
 bit[15:12]  ����
 bit[11:0]   Ⱥ�ӳپ�����IIR�˲���ϵ��b12���з�������
   UNION�ṹ:  ET_ET_IIR_COEF_2_3_PARA_UNION */
#define ET_ET_IIR_COEF_2_3_PARA_ADDR                  (SOC_BBP_ET_BASE_ADDR + 0xC70)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  Ⱥ�ӳپ�����IIR�˲���ϵ��b13���з�������
 bit[15:12]  ����
 bit[11:0]   Ⱥ�ӳپ�����IIR�˲���ϵ��a21���з�������
   UNION�ṹ:  ET_ET_IIR_COEF_4_5_PARA_UNION */
#define ET_ET_IIR_COEF_4_5_PARA_ADDR                  (SOC_BBP_ET_BASE_ADDR + 0xC74)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  Ⱥ�ӳپ�����IIR�˲���ϵ��a22���з�������
 bit[15:12]  ����
 bit[11:0]   Ⱥ�ӳپ�����IIR�˲���ϵ��b21���з�������
   UNION�ṹ:  ET_ET_IIR_COEF_6_7_PARA_UNION */
#define ET_ET_IIR_COEF_6_7_PARA_ADDR                  (SOC_BBP_ET_BASE_ADDR + 0xC78)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  Ⱥ�ӳپ�����IIR�˲���ϵ��b22���з�������
 bit[15:12]  ����
 bit[11:0]   Ⱥ�ӳپ�����IIR�˲���ϵ��b23���з�������
   UNION�ṹ:  ET_ET_IIR_COEF_8_9_PARA_UNION */
#define ET_ET_IIR_COEF_8_9_PARA_ADDR                  (SOC_BBP_ET_BASE_ADDR + 0xC7C)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  Ⱥ�ӳپ�����IIR�˲���ϵ��a31���з�������
 bit[15:12]  ����
 bit[11:0]   Ⱥ�ӳپ�����IIR�˲���ϵ��a32���з�������
   UNION�ṹ:  ET_ET_IIR_COEF_10_11_PARA_UNION */
#define ET_ET_IIR_COEF_10_11_PARA_ADDR                (SOC_BBP_ET_BASE_ADDR + 0xC80)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  Ⱥ�ӳپ�����IIR�˲���ϵ��b31���з�������
 bit[15:12]  ����
 bit[11:0]   Ⱥ�ӳپ�����IIR�˲���ϵ��b32���з�������
   UNION�ṹ:  ET_ET_IIR_COEF_12_13_PARA_UNION */
#define ET_ET_IIR_COEF_12_13_PARA_ADDR                (SOC_BBP_ET_BASE_ADDR + 0xC84)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  Ⱥ�ӳپ�����IIR�˲���ϵ��b33���з�������
 bit[15:0]   ����
   UNION�ṹ:  ET_ET_IIR_COEF_14_PARA_UNION */
#define ET_ET_IIR_COEF_14_PARA_ADDR                   (SOC_BBP_ET_BASE_ADDR + 0xC88)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:28]  Ⱥ�ӳپ�����IIR�˲���b33֧·����������λ�������ơ��޷���
             0:9
             1:10
             2:11
             3:12
 bit[27:26]  Ⱥ�ӳپ�����IIR�˲���b32֧·����������λ�������ơ�
             0:9
             1:10
             2:11
             3:12
 bit[25:24]  Ⱥ�ӳپ�����IIR�˲���b31֧·����������λ�������ơ�
             0:9
             1:10
             2:11
             3:12
 bit[23:22]  Ⱥ�ӳپ�����IIR�˲���a32֧·����������λ�������ơ�
             0:9
             1:10
             2:11
             3:12
 bit[21:20]  Ⱥ�ӳپ�����IIR�˲���a31����������λ�������ơ�
             0:9
             1:10
             2:11
             3:12
 bit[19:18]  Ⱥ�ӳپ�����IIR�˲���b23֧·����������λ�������ơ�
             0:9
             1:10
             2:11
             3:12
 bit[17:16]  Ⱥ�ӳپ�����IIR�˲���b22֧·����������λ�������ơ�
             0:9
             1:10
             2:11
             3:12
 bit[15:14]  Ⱥ�ӳپ�����IIR�˲���b21֧·����������λ�������ơ�
             0:9
             1:10
             2:11
             3:12
 bit[13:12]  Ⱥ�ӳپ�����IIR�˲���a22֧·����������λ�������ơ�
             0:9
             1:10
             2:11
             3:12
 bit[11:10]  Ⱥ�ӳپ�����IIR�˲���a21֧·����������λ�������ơ�
             0:9
             1:10
             2:11
             3:12
 bit[9:8]    Ⱥ�ӳپ�����IIR�˲���b13֧·����������λ�������ơ�
             0:9
             1:10
             2:11
             3:12
 bit[7:6]    Ⱥ�ӳپ�����IIR�˲���b12֧·����������λ�������ơ�
             0:9
             1:10
             2:11
             3:12
 bit[5:4]    Ⱥ�ӳپ�����IIR�˲���b11֧·����������λ�������ơ�
             0:9
             1:10
             2:11
             3:12
 bit[3:2]    Ⱥ�ӳپ�����IIR�˲���a12֧·����������λ�������ơ�
             0:9
             1:10
             2:11
             3:12
 bit[1:0]    Ⱥ�ӳپ�����IIR�˲���a11֧·����������λ�������ơ�
             0:9
             1:10
             2:11
             3:12
   UNION�ṹ:  ET_ET_IIR_SHIFT_PARA_UNION */
#define ET_ET_IIR_SHIFT_PARA_ADDR                     (SOC_BBP_ET_BASE_ADDR + 0xC8C)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  �������FIR�˲�����ͷ(1/z)^0��ϵ������Ӧ�����ӳ���С�����з�������
 bit[15:12]  ����
 bit[11:0]   �������FIR�˲�����ͷ(1/z)^1��ϵ�����з�������
   UNION�ṹ:  ET_ET_FIR_COEF_0_1_PARA_UNION */
#define ET_ET_FIR_COEF_0_1_PARA_ADDR                  (SOC_BBP_ET_BASE_ADDR + 0xC90)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  �������FIR�˲�����ͷ(1/z)^2��ϵ�����з�������
 bit[15:12]  ����
 bit[11:0]   �������FIR�˲�����ͷ(1/z)^3��ϵ�����з�������
   UNION�ṹ:  ET_ET_FIR_COEF_2_3_PARA_UNION */
#define ET_ET_FIR_COEF_2_3_PARA_ADDR                  (SOC_BBP_ET_BASE_ADDR + 0xC94)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  �������FIR�˲�����ͷ(1/z)^4��ϵ�����з�������
 bit[15:12]  ����
 bit[11:0]   �������FIR�˲�����ͷ(1/z)^5��ϵ�����з�������
   UNION�ṹ:  ET_ET_FIR_COEF_4_5_PARA_UNION */
#define ET_ET_FIR_COEF_4_5_PARA_ADDR                  (SOC_BBP_ET_BASE_ADDR + 0xC98)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  �������FIR�˲�����ͷ(1/z)^6��ϵ�����з�������
 bit[15:12]  ����
 bit[11:0]   �������FIR�˲�����ͷ(1/z)^7��ϵ�����з�������
   UNION�ṹ:  ET_ET_FIR_COEF_6_7_PARA_UNION */
#define ET_ET_FIR_COEF_6_7_PARA_ADDR                  (SOC_BBP_ET_BASE_ADDR + 0xC9C)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  �������FIR�˲�����ͷ(1/z)^8��ϵ�����з�������
 bit[15:12]  ����
 bit[11:0]   �������FIR�˲�����ͷ(1/z)^9��ϵ�����з�������
   UNION�ṹ:  ET_ET_FIR_COEF_8_9_PARA_UNION */
#define ET_ET_FIR_COEF_8_9_PARA_ADDR                  (SOC_BBP_ET_BASE_ADDR + 0xCA0)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  �������FIR�˲�����ͷ(1/z)^10��ϵ�����з�������
 bit[15:12]  ����
 bit[11:0]   �������FIR�˲�����ͷ(1/z)^11��ϵ�����з�������
   UNION�ṹ:  ET_ET_FIR_COEF_10_11_PARA_UNION */
#define ET_ET_FIR_COEF_10_11_PARA_ADDR                (SOC_BBP_ET_BASE_ADDR + 0xCA4)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  �������FIR�˲�����ͷ(1/z)^12��ϵ�����з�������
 bit[15:12]  ����
 bit[11:0]   �������FIR�˲�����ͷ(1/z)^13��ϵ�����з�������
   UNION�ṹ:  ET_ET_FIR_COEF_12_13_PARA_UNION */
#define ET_ET_FIR_COEF_12_13_PARA_ADDR                (SOC_BBP_ET_BASE_ADDR + 0xCA8)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  �������FIR�˲�����ͷ(1/z)^14��ϵ�����з�������
 bit[15:12]  ����
 bit[11:0]   �������FIR�˲�����ͷ(1/z)^15��ϵ�����з�������
   UNION�ṹ:  ET_ET_FIR_COEF_14_15_PARA_UNION */
#define ET_ET_FIR_COEF_14_15_PARA_ADDR                (SOC_BBP_ET_BASE_ADDR + 0xCAC)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  �������FIR�˲�����ͷ(1/z)^16��ϵ�����з�������
 bit[15:12]  ����
 bit[11:0]   �������FIR�˲�����ͷ(1/z)^17��ϵ�����з�������
   UNION�ṹ:  ET_ET_FIR_COEF_16_17_PARA_UNION */
#define ET_ET_FIR_COEF_16_17_PARA_ADDR                (SOC_BBP_ET_BASE_ADDR + 0xCB0)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  �������FIR�˲�����ͷ(1/z)^18��ϵ�����з�������
 bit[15:12]  ����
 bit[11:0]   �������FIR�˲�����ͷ(1/z)^19��ϵ�����з�������
   UNION�ṹ:  ET_ET_FIR_COEF_18_19_PARA_UNION */
#define ET_ET_FIR_COEF_18_19_PARA_ADDR                (SOC_BBP_ET_BASE_ADDR + 0xCB4)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  �������FIR�˲�����ͷ(1/z)^20��ϵ�����з�������
 bit[15:12]  ����
 bit[11:0]   �������FIR�˲�����ͷ(1/z)^21��ϵ�����з�������
   UNION�ṹ:  ET_ET_FIR_COEF_20_21_PARA_UNION */
#define ET_ET_FIR_COEF_20_21_PARA_ADDR                (SOC_BBP_ET_BASE_ADDR + 0xCB8)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  �������FIR�˲�����ͷ(1/z)^22��ϵ�����з�������
 bit[15:12]  ����
 bit[11:0]   �������FIR�˲�����ͷ(1/z)^23��ϵ�����з�������
   UNION�ṹ:  ET_ET_FIR_COEF_22_23_PARA_UNION */
#define ET_ET_FIR_COEF_22_23_PARA_ADDR                (SOC_BBP_ET_BASE_ADDR + 0xCBC)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  �������FIR�˲�����ͷ(1/z)^24��ϵ�����з�������
 bit[15:12]  ����
 bit[11:0]   �������FIR�˲�����ͷ(1/z)^25��ϵ�����з�������
   UNION�ṹ:  ET_ET_FIR_COEF_24_25_PARA_UNION */
#define ET_ET_FIR_COEF_24_25_PARA_ADDR                (SOC_BBP_ET_BASE_ADDR + 0xCC0)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  �������FIR�˲�����ͷ(1/z)^26��ϵ�����з�������
 bit[15:12]  ����
 bit[11:0]   �������FIR�˲�����ͷ(1/z)^27��ϵ�����з�������
   UNION�ṹ:  ET_ET_FIR_COEF_26_27_PARA_UNION */
#define ET_ET_FIR_COEF_26_27_PARA_ADDR                (SOC_BBP_ET_BASE_ADDR + 0xCC4)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  �������FIR�˲�����ͷ(1/z)^28��ϵ�����з�������
 bit[15:12]  ����
 bit[11:0]   �������FIR�˲�����ͷ(1/z)^29��ϵ�����з�������
   UNION�ṹ:  ET_ET_FIR_COEF_28_29_PARA_UNION */
#define ET_ET_FIR_COEF_28_29_PARA_ADDR                (SOC_BBP_ET_BASE_ADDR + 0xCC8)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  �������FIR�˲�����ͷ(1/z)^30��ϵ�����з�������
 bit[15:12]  ����
 bit[11:0]   �������FIR�˲�����ͷ(1/z)^31��ϵ�����з�������
   UNION�ṹ:  ET_ET_FIR_COEF_30_31_PARA_UNION */
#define ET_ET_FIR_COEF_30_31_PARA_ADDR                (SOC_BBP_ET_BASE_ADDR + 0xCCC)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  �������FIR�˲�����ͷ(1/z)^32��ϵ�����з�������
 bit[15:12]  ����
 bit[11:0]   �������FIR�˲�����ͷ(1/z)^33��ϵ�����з�������
   UNION�ṹ:  ET_ET_FIR_COEF_32_33_PARA_UNION */
#define ET_ET_FIR_COEF_32_33_PARA_ADDR                (SOC_BBP_ET_BASE_ADDR + 0xCD0)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  �������FIR�˲�����ͷ(1/z)^34��ϵ������Ӧ�����ӳ���󣩣��з�������
 bit[15:0]   ����
   UNION�ṹ:  ET_ET_FIR_COEF_34_PARA_UNION */
#define ET_ET_FIR_COEF_34_PARA_ADDR                   (SOC_BBP_ET_BASE_ADDR + 0xCD4)

/* �Ĵ���˵����
 bit[31:16]  ͨ��0����ctrl2proc_et_mode_en�½��ص��ӳ٣��޷�������
             ������ʱֵ��Ӧ����etͨ·����ʱ��
 bit[15:0]   t��ʱ��λΪ��·ʱ������
             ��t��ʱԼ����ϵ��
             t3 >= t1 ;
             t4 < t6 ;
             t4+t5 > t6+t7 ;
             
             ͨ��0����ctrl2swch_et_mode_sel, ctrl2swch_apt_pa_vcc_ind, ctrl2proc_et_mode_en���ӳ٣�
             ������ʱֵ��Ӧ����etͨ·����ʱ����ͬ��
             
             һ��t��ʱ�ο�ֵ��
             ��etͨ·�����ӳټĴ���ֵΪx����t1 = x + 'd51; t2 = 0;
             t3 = x + 'd51; 
             t4 = x + 'd51; t5 = 0; 
             t6 = x + 'd51; t7 = 0; 
             t8 = x + 'd96;
   UNION�ṹ:  ET_ET_CTRL_DELAY0_UNION */
#define ET_ET_CTRL_DELAY0_ADDR                        (SOC_BBP_ET_BASE_ADDR + 0xCE4)

/* �Ĵ���˵����
 bit[31:16]  et_ctrl�ڲ�ʹ�ã���ʱet_act_en
             
 bit[15:0]   ͨ��0����et2pad_et_mode_sel���ӳ٣��ݲ�ʹ�á�
   UNION�ṹ:  ET_ET_CTRL_DELAY1_UNION */
#define ET_ET_CTRL_DELAY1_ADDR                        (SOC_BBP_ET_BASE_ADDR + 0xCE8)

/* �Ĵ���˵����
 bit[31:16]  ͨ��0����et2abb_act_en�½��ص��ӳ�
 bit[15:0]   ͨ��0����et2abb_act_en�����ص��ӳ�
   UNION�ṹ:  ET_ET_CTRL_DELAY2_UNION */
#define ET_ET_CTRL_DELAY2_ADDR                        (SOC_BBP_ET_BASE_ADDR + 0xCEC)

/* �Ĵ���˵����
 bit[31:16]  ͨ��0����et2abb_et_mode_sel�½��ص��ӳ�
 bit[15:0]   ͨ��0����et2abb_et_mode_sel�����ص��ӳ�
   UNION�ṹ:  ET_ET_CTRL_DELAY3_UNION */
#define ET_ET_CTRL_DELAY3_ADDR                        (SOC_BBP_ET_BASE_ADDR + 0xCF0)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    
             λ[2]����ETMѡ��
             0��ʹ�õ�����ETM��Ĭ��ֵ��
             
             λ[1:0]������ETM����ģʽ��
             0������R2����ETM������                  
             1������TI����ETM����ģʽ1��
             2������TI����ETM����ģʽ2��
             3������TI����ETM����ģʽ2��
   UNION�ṹ:  ET_ET_CTRL_ETM_MODE_UNION */
#define ET_ET_CTRL_ETM_MODE_ADDR                      (SOC_BBP_ET_BASE_ADDR + 0xCF4)

/* �Ĵ���˵����
 bit[31:27]  ����
 bit[26:16]  �ò�����ʾPA�����湦�ʵ�ѹ���ұ��0���ƫ�Ƶ�ַ0x800������Ӧ�Ĺ���ֵ���ò���Ϊ11bit�޷���������λΪ0.0125dB��Ĭ��ֵΪ0��
 bit[15:11]  ����
 bit[10:0]   �ò�����ʾPA�����湦�ʵ�ѹ���ұ��0���ƫ�Ƶ�ַ0xA00������Ӧ�Ĺ���ֵ���ò���Ϊ11bit�޷���������λΪ0.0125dB��Ĭ��ֵΪ0��
   UNION�ṹ:  ET_ET_PA_THD_PARA_HIGH_UNION */
#define ET_ET_PA_THD_PARA_HIGH_ADDR                   (SOC_BBP_ET_BASE_ADDR + 0xC5C)

/* �Ĵ���˵����
 bit[31:1]   ������
 bit[0]      L/Wģʽ�л��Զ���λʹ��
             1����ģ�Զ���λ
             0����ģ��������λ
             
   UNION�ṹ:  ET_AUTO_RESET_UNION */
#define ET_AUTO_RESET_ADDR                            (SOC_BBP_ET_BASE_ADDR + 0xCF8)

/* �Ĵ���˵����
 bit[31:2]   ������
 bit[1]      ��bitֻ��APTУ׼ģʽ����Ч
             1'b1: ABB������ETģʽ
             1'b0: ABB������APTģʽ
 bit[0]      1'b1: ѡ��APTУ׼ģʽ
             1'b0: ��������ģʽ��Ĭ��ֵ
   UNION�ṹ:  ET_APT_CALIBRE_MODE_UNION */
#define ET_APT_CALIBRE_MODE_ADDR                      (SOC_BBP_ET_BASE_ADDR + 0xCFC)

/* �Ĵ���˵����
 bit[31:14]  ������
 bit[13:0]   ���У׼��ѹ���з�����
   UNION�ṹ:  ET_CALIBRE_VCC_UNION */
#define ET_CALIBRE_VCC_ADDR                           (SOC_BBP_ET_BASE_ADDR + 0xD00)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ����ͨ·�����֯˳��ѡ�� 
             0: �����ż��Ĭ��ֵ  
             1:��ż����
   UNION�ṹ:  ET_INTRLV_SEL_UNION */
#define ET_INTRLV_SEL_ADDR                            (SOC_BBP_ET_BASE_ADDR + 0xD04)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      �������Ƶͨ·�������ݶ���ָʾ,
             0:����
             1:�������־
   UNION�ṹ:  ET_ET_ALIGN_UNION */
#define ET_ET_ALIGN_ADDR                              (SOC_BBP_ET_BASE_ADDR + 0xD08)

/* �Ĵ���˵����
 bit[31:16]  ����
 bit[15:8]   ETģʽ��APTģʽ����
 bit[7:0]    APTģʽ��ETģʽ����
   UNION�ṹ:  ET_ET_STATUS_UNION */
#define ET_ET_STATUS_ADDR                             (SOC_BBP_ET_BASE_ADDR + 0xD0C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      д1'b1�������ϱ��Ĵ�������
   UNION�ṹ:  ET_ET_RPT_CLEAR_UNION */
#define ET_ET_RPT_CLEAR_ADDR                          (SOC_BBP_ET_BASE_ADDR + 0xD10)

/* �Ĵ���˵����
 bit[31:2]   
 bit[1:0]    [1]: force config enable;
             [0]: 1'b1, force select internal logic; 1'b0, force select lbus
   UNION�ṹ:  ET_LUT_RAM_SEL_UNION */
#define ET_LUT_RAM_SEL_ADDR                           (SOC_BBP_ET_BASE_ADDR + 0xD14)

/* �Ĵ���˵����
 bit[31:1]   
 bit[0]      ��������ѡ��
             1'b0:��������ģʽ��
             1'b1:ʹ��dbg��������ǿ�䣻
   UNION�ṹ:  ET_DBG_DAT_SEL_UNION */
#define ET_DBG_DAT_SEL_ADDR                           (SOC_BBP_ET_BASE_ADDR + 0xD18)

/* �Ĵ���˵����
 bit[31:10]  
 bit[9:0]    dbg�������ݣ�����ǿ������ת��������ֵ���޷��ţ���ά�ɲ�
   UNION�ṹ:  ET_DBG_DAT0_UNION */
#define ET_DBG_DAT0_ADDR                              (SOC_BBP_ET_BASE_ADDR + 0xD1C)

/* �Ĵ���˵����
 bit[31:3]   
 bit[2]      tx�����ӳ�ͬ����ʽ��
             1'b0: ��ʱ��Ч���ȴ�dly_para_ind�߿أ���̬����ʱʹ�á�
             1'b1: ������Ч������ͬ������̬����ʱʹ�á���Ĭ��ֵ��
 bit[1]      et�����ӳ�ͬ����ʽ��
             1'b0: ��ʱ��Ч���ȴ�dly_para_ind�߿أ���̬����ʱʹ�á�
             1'b1: ������Ч������ͬ������̬����ʱʹ�á���Ĭ��ֵ��
 bit[0]      usfd�����ӳ�ͬ����ʽ��
             1'b0: ��ʱ��Ч���ȴ�dly_para_ind�߿أ���̬����ʱʹ�á�
             1'b1: ������Ч������ͬ�������ھ�̬���á���Ĭ��ֵ��
   UNION�ṹ:  ET_SYNC_BYPASS_UNION */
#define ET_SYNC_BYPASS_ADDR                           (SOC_BBP_ET_BASE_ADDR + 0xD20)

/* �Ĵ���˵����
 bit[31:6]   
 bit[5:0]    RAMʱ���л���С���cycle������ά�ɲ⣬����ʹ��Ĭ��ֵ0x06
   UNION�ṹ:  ET_CK_SWCH_CNT_UNION */
#define ET_CK_SWCH_CNT_ADDR                           (SOC_BBP_ET_BASE_ADDR + 0xD24)

/* �Ĵ���˵����
 bit[31:4]   
 bit[3]      tx��̬��ʱ����
             1'b0: ֧�ֶ�̬������ʱ��tx������ʱÿ�ζ�̬����һ�����㡣
             1'b1: ��֧�ֶ�̬������ʱ��Ĭ��ֵ��
 bit[2]      tx��̬��ʱ����
             1'b0: ֧�ֶ�̬������ʱ��tx������ʱÿ�ζ�̬����һ�����㡣
             1'b1: ��֧�ֶ�̬������ʱ��Ĭ��ֵ��
 bit[1]      et��̬��ʱ����
             1'b0: ֧�ֶ�̬������ʱ��
             1'b1: ��֧�ֶ�̬������ʱ��Ĭ��ֵ��
 bit[0]      et��̬��ʱ����
             1'b0: ֧�ֶ�̬������ʱ��
             1'b1: ��֧�ֶ�̬������ʱ��Ĭ��ֵ��
   UNION�ṹ:  ET_DYM_ADJ_DISABLE_UNION */
#define ET_DYM_ADJ_DISABLE_ADDR                       (SOC_BBP_ET_BASE_ADDR + 0xD28)

/* �Ĵ���˵����
 bit[31:2]   
 bit[1]      �����ӳٶ�ʱ��Ч��ȷ����ʹ�ܣ�
             1'b1: ������ȷ���루Ĭ��ֵ��
             1'b0: �򿪾�ȷ����
 bit[0]      �����ӳٶ�ʱ��Чʱ�̣�
             1'b1: ż��ʱ����Ч
             1'b0: ����ʱ����Ч
   UNION�ṹ:  ET_DYM_FRAC_SEL_UNION */
#define ET_DYM_FRAC_SEL_ADDR                          (SOC_BBP_ET_BASE_ADDR + 0xD2C)

/* �Ĵ���˵����
 bit[31:1]   
 bit[0]      �Ĵ���ģ��ʱ���ſ����Σ�
             1'b1: ���θ��ſأ�ʱ�ӳ�����
             1'b0: �Ĵ���ģ��ʱ���Զ��ſ�
   UNION�ṹ:  ET_REG_CK_SEL_UNION */
#define ET_REG_CK_SEL_ADDR                            (SOC_BBP_ET_BASE_ADDR + 0xD30)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define ET_ET_RESERVE0_ADDR                           (SOC_BBP_ET_BASE_ADDR + 0xD34)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define ET_ET_RESERVE1_ADDR                           (SOC_BBP_ET_BASE_ADDR + 0xD38)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define ET_ET_RESERVE2_ADDR                           (SOC_BBP_ET_BASE_ADDR + 0xD3C)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define ET_ET_RESERVE3_ADDR                           (SOC_BBP_ET_BASE_ADDR + 0xD40)





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
                     (1/1) register_define_et
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : ET_ET_SOFT_RST_UNION
 �ṹ˵��  : ET_SOFT_RST �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_soft_rst_reg;
    struct
    {
        unsigned int  et_soft_rst : 1;  /* bit[0]   : et��λ�źš�
                                                      1����ʾ��λ
                                                      0����ʾ�帴λ */
        unsigned int  reserved    : 31; /* bit[1-31]: ������ */
    } reg;
} ET_ET_SOFT_RST_UNION;
#define ET_ET_SOFT_RST_et_soft_rst_START  (0)
#define ET_ET_SOFT_RST_et_soft_rst_END    (0)


/*****************************************************************************
 �ṹ��    : ET_ET_RAM_CTRL0_UNION
 �ṹ˵��  : ET_RAM_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x10500350�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_ram_ctrl0_reg;
    struct
    {
        unsigned int  et_tpram_ctrl : 16; /* bit[0-15] : tpram mem_ctrl */
        unsigned int  et_spram_ctrl : 16; /* bit[16-31]: spram mem_ctrl */
    } reg;
} ET_ET_RAM_CTRL0_UNION;
#define ET_ET_RAM_CTRL0_et_tpram_ctrl_START  (0)
#define ET_ET_RAM_CTRL0_et_tpram_ctrl_END    (15)
#define ET_ET_RAM_CTRL0_et_spram_ctrl_START  (16)
#define ET_ET_RAM_CTRL0_et_spram_ctrl_END    (31)


/*****************************************************************************
 �ṹ��    : ET_PA_PARA_UNION
 �ṹ˵��  : PA_PARA �Ĵ����ṹ���塣��ַƫ����:0x008����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      pa_para_reg;
    struct
    {
        unsigned int  reserved_0       : 4;  /* bit[0-3] : ������ */
        unsigned int  dsp_pa_mid_ctrl  : 2;  /* bit[4-5] : PA�е�λƥ��ָʾ�źš�����߿��ź�com2et_tx_pa_mode��dsp_pa_high_ctrl��ƥ�䵫����ֶ�ƥ�䣬����ȷ��PA�ǹ�����������ģʽ�� */
        unsigned int  dsp_pa_high_ctrl : 2;  /* bit[6-7] : PA�ߵ�λƥ��ָʾ�źš�����߿��ź�com2et_tx_pa_mode����ֶ�
                                                           ƥ�䣬����ȷ��PA�ǹ����ڸ�����ģʽ�� */
        unsigned int  reserved_1       : 24; /* bit[8-31]: ������ */
    } reg;
} ET_PA_PARA_UNION;
#define ET_PA_PARA_dsp_pa_mid_ctrl_START   (4)
#define ET_PA_PARA_dsp_pa_mid_ctrl_END     (5)
#define ET_PA_PARA_dsp_pa_high_ctrl_START  (6)
#define ET_PA_PARA_dsp_pa_high_ctrl_END    (7)


/*****************************************************************************
 �ṹ��    : ET_RF_DATA_DLY_UNION
 �ṹ˵��  : RF_DATA_DLY �Ĵ����ṹ���塣��ַƫ����:0x00C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      rf_data_dly_reg;
    struct
    {
        unsigned int  dsp_tx_dly_num : 9;  /* bit[0-8] : ��Ƶ����ͨ·�ӳ�����ֵ����com2et_tx_clkʱ��Ƶ�ʺ�����ͨ·������֮��Ϊ4:1ʱ��ȡֵ��ΧΪ0~508����Ϊ2:1ʱ��ȡֵ��ΧΪ0~254����λΪ����ͨ·ʱ�����ڡ� */
        unsigned int  reserved       : 23; /* bit[9-31]: ������ */
    } reg;
} ET_RF_DATA_DLY_UNION;
#define ET_RF_DATA_DLY_dsp_tx_dly_num_START  (0)
#define ET_RF_DATA_DLY_dsp_tx_dly_num_END    (8)


/*****************************************************************************
 �ṹ��    : ET_LW_MODE_SEL_UNION
 �ṹ˵��  : LW_MODE_SEL �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      lw_mode_sel_reg;
    struct
    {
        unsigned int  lw_mode_sel : 2;  /* bit[0-1] : L/Wģʽѡ��
                                                      01: LTE mode, 
                                                      10: W mode, 
                                                      00: L/W����Ч��ETģ����ʱ�ӣ����Զ�������λ����������״̬ʱ�⸴λ
                                                      11: ��Ч״̬
                                                      
                                                      �����Lģ�е�Wģ��lw_mode_sel�仯����2'b01 -> 2'b00����λ�� -> 2'b10 */
        unsigned int  reserved    : 30; /* bit[2-31]: ������ */
    } reg;
} ET_LW_MODE_SEL_UNION;
#define ET_LW_MODE_SEL_lw_mode_sel_START  (0)
#define ET_LW_MODE_SEL_lw_mode_sel_END    (1)


/*****************************************************************************
 �ṹ��    : ET_SOFT_EN_UNION
 �ṹ˵��  : SOFT_EN �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      soft_en_reg;
    struct
    {
        unsigned int  soft_en  : 1;  /* bit[0]   : ����ر�ET0ͨ����
                                                   1'b1 : ET0����������Ĭ��ֵ��
                                                   1'b0 : ET0�رգ�ʱ���ſأ��߼���λ��
                                                   
                                                   ע���رմ˼Ĵ�����Ӱ��ET0 txͨ·���ݷ��͡� */
        unsigned int  reserved : 31; /* bit[1-31]: ������ */
    } reg;
} ET_SOFT_EN_UNION;
#define ET_SOFT_EN_soft_en_START   (0)
#define ET_SOFT_EN_soft_en_END     (0)


/*****************************************************************************
 �ṹ��    : ET_ET_BYPASS_CTRL_UNION
 �ṹ˵��  : ET_BYPASS_CTRL �Ĵ����ṹ���塣��ַƫ����:0xC00����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_bypass_ctrl_reg;
    struct
    {
        unsigned int  et_linear_thd_bp      : 1;  /* bit[0]   : �����޵׹���bypass�źš�
                                                                0����bypass�ù��ܡ�
                                                                1��bypass�ù��ܡ� */
        unsigned int  et_swing_bp           : 1;  /* bit[1]   : �����ްڹ���bypass�źš�
                                                                0����bypass�ù��ܡ�
                                                                1��bypass�ù��ܡ� */
        unsigned int  et_voltage_adapter_bp : 1;  /* bit[2]   : ��ѹ������������·���ơ�
                                                                
                                                                0����bypass�ù��ܡ�
                                                                1��bypass�ù��ܡ� */
        unsigned int  et_iir_bp             : 1;  /* bit[3]   : Ⱥ�ӳ�IIR�˲���������·���ơ�
                                                                
                                                                0����bypass�ù��ܡ�
                                                                1��bypass�ù��ܡ� */
        unsigned int  et_fir_bp             : 1;  /* bit[4]   : �������FIR�˲���������·���ơ�
                                                                
                                                                0����bypass�ù��ܡ�
                                                                1��bypass�ù��ܡ� */
        unsigned int  log_calc_bp           : 1;  /* bit[5]   : ����ת��������Ƶ���ʹ��㹦��bypass�źš�
                                                                
                                                                0����bypass�ù��ܡ�
                                                                1��bypass�ù��ܡ� */
        unsigned int  reserved              : 26; /* bit[6-31]: ���� */
    } reg;
} ET_ET_BYPASS_CTRL_UNION;
#define ET_ET_BYPASS_CTRL_et_linear_thd_bp_START       (0)
#define ET_ET_BYPASS_CTRL_et_linear_thd_bp_END         (0)
#define ET_ET_BYPASS_CTRL_et_swing_bp_START            (1)
#define ET_ET_BYPASS_CTRL_et_swing_bp_END              (1)
#define ET_ET_BYPASS_CTRL_et_voltage_adapter_bp_START  (2)
#define ET_ET_BYPASS_CTRL_et_voltage_adapter_bp_END    (2)
#define ET_ET_BYPASS_CTRL_et_iir_bp_START              (3)
#define ET_ET_BYPASS_CTRL_et_iir_bp_END                (3)
#define ET_ET_BYPASS_CTRL_et_fir_bp_START              (4)
#define ET_ET_BYPASS_CTRL_et_fir_bp_END                (4)
#define ET_ET_BYPASS_CTRL_log_calc_bp_START            (5)
#define ET_ET_BYPASS_CTRL_log_calc_bp_END              (5)


/*****************************************************************************
 �ṹ��    : ET_ET_CKG_BYPASS_UNION
 �ṹ˵��  : ET_CKG_BYPASS �Ĵ����ṹ���塣��ַƫ����:0xC04����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_ckg_bypass_reg;
    struct
    {
        unsigned int  et_ckg_bypass : 1;  /* bit[0]   : ET�����Զ��ſ���·�źš�
                                                        0���Զ��ſز���·��
                                                        1���Զ��ſ���·�� */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} ET_ET_CKG_BYPASS_UNION;
#define ET_ET_CKG_BYPASS_et_ckg_bypass_START  (0)
#define ET_ET_CKG_BYPASS_et_ckg_bypass_END    (0)


/*****************************************************************************
 �ṹ��    : ET_ET_DELAY_PARA_UNION
 �ṹ˵��  : ET_DELAY_PARA �Ĵ����ṹ���塣��ַƫ����:0xC08����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_delay_para_reg;
    struct
    {
        unsigned int  dsp_et_dly_num : 8;  /* bit[0-7] : ET�����ź�ͨ·�ӳ�����ֵ���ӳ����÷�Χ0~254����С�ӳٵ�λΪ1����·ʱ�����ڣ���122Mʱ�������8.138ns */
        unsigned int  reserved       : 24; /* bit[8-31]: ���� */
    } reg;
} ET_ET_DELAY_PARA_UNION;
#define ET_ET_DELAY_PARA_dsp_et_dly_num_START  (0)
#define ET_ET_DELAY_PARA_dsp_et_dly_num_END    (7)


/*****************************************************************************
 �ṹ��    : ET_ET_UPSAMPLE_SEL_UNION
 �ṹ˵��  : ET_UPSAMPLE_SEL �Ĵ����ṹ���塣��ַƫ����:0xC18����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_upsample_sel_reg;
    struct
    {
        unsigned int  et_upsample_sel : 1;  /* bit[0]   : ��������������������ϲ���ѡ��
                                                          1'b0: ��2���ϲ�����
                                                          1'b1: �����ϲ��� */
        unsigned int  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} ET_ET_UPSAMPLE_SEL_UNION;
#define ET_ET_UPSAMPLE_SEL_et_upsample_sel_START  (0)
#define ET_ET_UPSAMPLE_SEL_et_upsample_sel_END    (0)


/*****************************************************************************
 �ṹ��    : ET_ET_INT_FILTER_CTRL_UNION
 �ṹ˵��  : ET_INT_FILTER_CTRL �Ĵ����ṹ���塣��ַƫ����:0xC1C����ֵ:0x00000011�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_int_filter_ctrl_reg;
    struct
    {
        unsigned int  dsp_int_1filter_center : 2;  /* bit[0-1] : ��1������ӳ��˲�����ֵ����ѡ��
                                                                 �˴������Ÿ����ʹ�ã�ֻ����Ĭ��ֵ2'b01 ��
                                                                 00����ʾ��ֵ�˲�������λ��x(n+1)��
                                                                 01����ʾ��ֵ�˲�������λ��x(n)��
                                                                 10����ʾ��ֵ�˲�������λ��x(n-1)��
                                                                 11����Ч���á� */
        unsigned int  reserved_0             : 2;  /* bit[2-3] : ���� */
        unsigned int  dsp_int_0filter_center : 2;  /* bit[4-5] : ��0������ӳ��˲�����ֵ����ѡ��
                                                                 �˴������Ÿ����ʹ�ã�ֻ����Ĭ��ֵ2'b01 ��
                                                                 00����ʾ��ֵ�˲�������λ��x(n+1)��
                                                                 01����ʾ��ֵ�˲�������λ��x(n)��
                                                                 10����ʾ��ֵ�˲�������λ��x(n-1)��
                                                                 11����Ч���á� */
        unsigned int  reserved_1             : 26; /* bit[6-31]: ���� */
    } reg;
} ET_ET_INT_FILTER_CTRL_UNION;
#define ET_ET_INT_FILTER_CTRL_dsp_int_1filter_center_START  (0)
#define ET_ET_INT_FILTER_CTRL_dsp_int_1filter_center_END    (1)
#define ET_ET_INT_FILTER_CTRL_dsp_int_0filter_center_START  (4)
#define ET_ET_INT_FILTER_CTRL_dsp_int_0filter_center_END    (5)


/*****************************************************************************
 �ṹ��    : ET_ET_FINE_0DELAY_PARA_0_UNION
 �ṹ˵��  : ET_FINE_0DELAY_PARA_0 �Ĵ����ṹ���塣��ַƫ����:0xC20����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fine_0delay_para_0_reg;
    struct
    {
        unsigned int  dsp_fine_0delay_1para : 12; /* bit[0-11] : �����ӳ��˲���0��ϵ��1��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á� */
        unsigned int  reserved_0            : 4;  /* bit[12-15]: ���� */
        unsigned int  dsp_fine_0delay_0para : 12; /* bit[16-27]: �����ӳ��˲���0��ϵ��0��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á� */
        unsigned int  reserved_1            : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_FINE_0DELAY_PARA_0_UNION;
#define ET_ET_FINE_0DELAY_PARA_0_dsp_fine_0delay_1para_START  (0)
#define ET_ET_FINE_0DELAY_PARA_0_dsp_fine_0delay_1para_END    (11)
#define ET_ET_FINE_0DELAY_PARA_0_dsp_fine_0delay_0para_START  (16)
#define ET_ET_FINE_0DELAY_PARA_0_dsp_fine_0delay_0para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_FINE_0DELAY_PARA_1_UNION
 �ṹ˵��  : ET_FINE_0DELAY_PARA_1 �Ĵ����ṹ���塣��ַƫ����:0xC24����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fine_0delay_para_1_reg;
    struct
    {
        unsigned int  dsp_fine_0delay_3para : 12; /* bit[0-11] : �����ӳ��˲���0��ϵ��3��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á� */
        unsigned int  reserved_0            : 4;  /* bit[12-15]: ���� */
        unsigned int  dsp_fine_0delay_2para : 12; /* bit[16-27]: �����ӳ��˲���0��ϵ��2��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á� */
        unsigned int  reserved_1            : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_FINE_0DELAY_PARA_1_UNION;
#define ET_ET_FINE_0DELAY_PARA_1_dsp_fine_0delay_3para_START  (0)
#define ET_ET_FINE_0DELAY_PARA_1_dsp_fine_0delay_3para_END    (11)
#define ET_ET_FINE_0DELAY_PARA_1_dsp_fine_0delay_2para_START  (16)
#define ET_ET_FINE_0DELAY_PARA_1_dsp_fine_0delay_2para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_FINE_0DELAY_PARA_2_UNION
 �ṹ˵��  : ET_FINE_0DELAY_PARA_2 �Ĵ����ṹ���塣��ַƫ����:0xC28����ֵ:0x07FF0000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fine_0delay_para_2_reg;
    struct
    {
        unsigned int  dsp_fine_0delay_5para : 12; /* bit[0-11] : �����ӳ��˲���0��ϵ��5��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á� */
        unsigned int  reserved_0            : 4;  /* bit[12-15]: ���� */
        unsigned int  dsp_fine_0delay_4para : 12; /* bit[16-27]: �����ӳ��˲���0��ϵ��4��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á� */
        unsigned int  reserved_1            : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_FINE_0DELAY_PARA_2_UNION;
#define ET_ET_FINE_0DELAY_PARA_2_dsp_fine_0delay_5para_START  (0)
#define ET_ET_FINE_0DELAY_PARA_2_dsp_fine_0delay_5para_END    (11)
#define ET_ET_FINE_0DELAY_PARA_2_dsp_fine_0delay_4para_START  (16)
#define ET_ET_FINE_0DELAY_PARA_2_dsp_fine_0delay_4para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_FINE_0DELAY_PARA_3_UNION
 �ṹ˵��  : ET_FINE_0DELAY_PARA_3 �Ĵ����ṹ���塣��ַƫ����:0xC2C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fine_0delay_para_3_reg;
    struct
    {
        unsigned int  dsp_fine_0delay_7para : 12; /* bit[0-11] : �����ӳ��˲���0��ϵ��7��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á� */
        unsigned int  reserved_0            : 4;  /* bit[12-15]: ���� */
        unsigned int  dsp_fine_0delay_6para : 12; /* bit[16-27]: �����ӳ��˲���0��ϵ��6��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á� */
        unsigned int  reserved_1            : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_FINE_0DELAY_PARA_3_UNION;
#define ET_ET_FINE_0DELAY_PARA_3_dsp_fine_0delay_7para_START  (0)
#define ET_ET_FINE_0DELAY_PARA_3_dsp_fine_0delay_7para_END    (11)
#define ET_ET_FINE_0DELAY_PARA_3_dsp_fine_0delay_6para_START  (16)
#define ET_ET_FINE_0DELAY_PARA_3_dsp_fine_0delay_6para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_FINE_0DELAY_PARA_4_UNION
 �ṹ˵��  : ET_FINE_0DELAY_PARA_4 �Ĵ����ṹ���塣��ַƫ����:0xC30����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fine_0delay_para_4_reg;
    struct
    {
        unsigned int  reserved_0            : 16; /* bit[0-15] : ���� */
        unsigned int  dsp_fine_0delay_8para : 12; /* bit[16-27]: �����ӳ��˲���0��ϵ��8��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á� */
        unsigned int  reserved_1            : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_FINE_0DELAY_PARA_4_UNION;
#define ET_ET_FINE_0DELAY_PARA_4_dsp_fine_0delay_8para_START  (16)
#define ET_ET_FINE_0DELAY_PARA_4_dsp_fine_0delay_8para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_FINE_1DELAY_PARA_0_UNION
 �ṹ˵��  : ET_FINE_1DELAY_PARA_0 �Ĵ����ṹ���塣��ַƫ����:0xC34����ֵ:0x0FE40069�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fine_1delay_para_0_reg;
    struct
    {
        unsigned int  dsp_fine_1delay_1para : 12; /* bit[0-11] : �����ӳ��˲���1��ϵ��1��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á� */
        unsigned int  reserved_0            : 4;  /* bit[12-15]: ���� */
        unsigned int  dsp_fine_1delay_0para : 12; /* bit[16-27]: �����ӳ��˲���1��ϵ��0��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á� */
        unsigned int  reserved_1            : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_FINE_1DELAY_PARA_0_UNION;
#define ET_ET_FINE_1DELAY_PARA_0_dsp_fine_1delay_1para_START  (0)
#define ET_ET_FINE_1DELAY_PARA_0_dsp_fine_1delay_1para_END    (11)
#define ET_ET_FINE_1DELAY_PARA_0_dsp_fine_1delay_0para_START  (16)
#define ET_ET_FINE_1DELAY_PARA_0_dsp_fine_1delay_0para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_FINE_1DELAY_PARA_1_UNION
 �ṹ˵��  : ET_FINE_1DELAY_PARA_1 �Ĵ����ṹ���塣��ַƫ����:0xC38����ֵ:0x0ED504A8�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fine_1delay_para_1_reg;
    struct
    {
        unsigned int  dsp_fine_1delay_3para : 12; /* bit[0-11] : �����ӳ��˲���1��ϵ��3��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á� */
        unsigned int  reserved_0            : 4;  /* bit[12-15]: ���� */
        unsigned int  dsp_fine_1delay_2para : 12; /* bit[16-27]: �����ӳ��˲���1��ϵ��2��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á� */
        unsigned int  reserved_1            : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_FINE_1DELAY_PARA_1_UNION;
#define ET_ET_FINE_1DELAY_PARA_1_dsp_fine_1delay_3para_START  (0)
#define ET_ET_FINE_1DELAY_PARA_1_dsp_fine_1delay_3para_END    (11)
#define ET_ET_FINE_1DELAY_PARA_1_dsp_fine_1delay_2para_START  (16)
#define ET_ET_FINE_1DELAY_PARA_1_dsp_fine_1delay_2para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_FINE_1DELAY_PARA_2_UNION
 �ṹ˵��  : ET_FINE_1DELAY_PARA_2 �Ĵ����ṹ���塣��ַƫ����:0xC3C����ֵ:0x05180E73�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fine_1delay_para_2_reg;
    struct
    {
        unsigned int  dsp_fine_1delay_5para : 12; /* bit[0-11] : �����ӳ��˲���1��ϵ��5��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á� */
        unsigned int  reserved_0            : 4;  /* bit[12-15]: ���� */
        unsigned int  dsp_fine_1delay_4para : 12; /* bit[16-27]: �����ӳ��˲���1��ϵ��4��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á� */
        unsigned int  reserved_1            : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_FINE_1DELAY_PARA_2_UNION;
#define ET_ET_FINE_1DELAY_PARA_2_dsp_fine_1delay_5para_START  (0)
#define ET_ET_FINE_1DELAY_PARA_2_dsp_fine_1delay_5para_END    (11)
#define ET_ET_FINE_1DELAY_PARA_2_dsp_fine_1delay_4para_START  (16)
#define ET_ET_FINE_1DELAY_PARA_2_dsp_fine_1delay_4para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_FINE_1DELAY_PARA_3_UNION
 �ṹ˵��  : ET_FINE_1DELAY_PARA_3 �Ĵ����ṹ���塣��ַƫ����:0xC40����ֵ:0x00B30FB5�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fine_1delay_para_3_reg;
    struct
    {
        unsigned int  dsp_fine_1delay_7para : 12; /* bit[0-11] : �����ӳ��˲���1��ϵ��7��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á� */
        unsigned int  reserved_0            : 4;  /* bit[12-15]: ���� */
        unsigned int  dsp_fine_1delay_6para : 12; /* bit[16-27]: �����ӳ��˲���1��ϵ��6��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á� */
        unsigned int  reserved_1            : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_FINE_1DELAY_PARA_3_UNION;
#define ET_ET_FINE_1DELAY_PARA_3_dsp_fine_1delay_7para_START  (0)
#define ET_ET_FINE_1DELAY_PARA_3_dsp_fine_1delay_7para_END    (11)
#define ET_ET_FINE_1DELAY_PARA_3_dsp_fine_1delay_6para_START  (16)
#define ET_ET_FINE_1DELAY_PARA_3_dsp_fine_1delay_6para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_FINE_1DELAY_PARA_4_UNION
 �ṹ˵��  : ET_FINE_1DELAY_PARA_4 �Ĵ����ṹ���塣��ַƫ����:0xC44����ֵ:0x00150000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fine_1delay_para_4_reg;
    struct
    {
        unsigned int  reserved_0            : 16; /* bit[0-15] : ���� */
        unsigned int  dsp_fine_1delay_8para : 12; /* bit[16-27]: �����ӳ��˲���1��ϵ��8��12bit�з������������������⹦��ʱ����ϵ����Ҫ�����н���֮ǰ������á� */
        unsigned int  reserved_1            : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_FINE_1DELAY_PARA_4_UNION;
#define ET_ET_FINE_1DELAY_PARA_4_dsp_fine_1delay_8para_START  (16)
#define ET_ET_FINE_1DELAY_PARA_4_dsp_fine_1delay_8para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_ENV_PROC_PARA1_UNION
 �ṹ˵��  : ET_ENV_PROC_PARA1 �Ĵ����ṹ���塣��ַƫ����:0xC4C����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_env_proc_para1_reg;
    struct
    {
        unsigned int  dsp_delay_max_num : 4;  /* bit[0-3] : �ӳ�ȡ����ܵ��ӳٲ�����4bit�޷�������ȡֵN��0��15�� */
        unsigned int  reserved          : 28; /* bit[4-31]: ���� */
    } reg;
} ET_ET_ENV_PROC_PARA1_UNION;
#define ET_ET_ENV_PROC_PARA1_dsp_delay_max_num_START  (0)
#define ET_ET_ENV_PROC_PARA1_dsp_delay_max_num_END    (3)


/*****************************************************************************
 �ṹ��    : ET_ET_ENV_PROC_PARA2_UNION
 �ṹ˵��  : ET_ENV_PROC_PARA2 �Ĵ����ṹ���塣��ַƫ����:0xC50����ֵ:0x00C8003C�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_env_proc_para2_reg;
    struct
    {
        unsigned int  dsp_env_ratio : 6;  /* bit[0-5]  : ����Detrough�������޵����Ƴ�ϵ����6bit�޷������� */
        unsigned int  reserved_0    : 10; /* bit[6-15] : ���� */
        unsigned int  dsp_env_knee  : 12; /* bit[16-27]: ����Detrough���������������޵����ޡ�12bit�޷������� */
        unsigned int  reserved_1    : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_ENV_PROC_PARA2_UNION;
#define ET_ET_ENV_PROC_PARA2_dsp_env_ratio_START  (0)
#define ET_ET_ENV_PROC_PARA2_dsp_env_ratio_END    (5)
#define ET_ET_ENV_PROC_PARA2_dsp_env_knee_START   (16)
#define ET_ET_ENV_PROC_PARA2_dsp_env_knee_END     (27)


/*****************************************************************************
 �ṹ��    : ET_ET_ENV_PROC_PARA3_UNION
 �ṹ˵��  : ET_ENV_PROC_PARA3 �Ĵ����ṹ���塣��ַƫ����:0xC54����ֵ:0x00002D18�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_env_proc_para3_reg;
    struct
    {
        unsigned int  dsp_power_offset_para : 14; /* bit[0-13] : ��Ƶ���繦�ʼ��������������ڲ���ֵ��14λ�з�������Ĭ��ֵ-4840������0.0125dB����-60.5dB�� */
        unsigned int  reserved              : 18; /* bit[14-31]: ���� */
    } reg;
} ET_ET_ENV_PROC_PARA3_UNION;
#define ET_ET_ENV_PROC_PARA3_dsp_power_offset_para_START  (0)
#define ET_ET_ENV_PROC_PARA3_dsp_power_offset_para_END    (13)


/*****************************************************************************
 �ṹ��    : ET_ET_PA_CTRL_UNION
 �ṹ˵��  : ET_PA_CTRL �Ĵ����ṹ���塣��ַƫ����:0xC58����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_pa_ctrl_reg;
    struct
    {
        unsigned int  dsp_pa_ctrl_mode : 1;  /* bit[0]   : ��dsp_pa_ctrl_mode=0ʱ����ʱ��������Ҫ�����ڸߡ�����������ģʽ�£�
                                                           
                                                           ��dsp_pa_ctrl_mode=1ʱ����ʱ���������Ҫ�����ڸ�����ģʽ�£��߿��ź�et_tx_pa_modeӦ��֤��Ĵ����ֶ�dsp_pa_high_ctrl��ֵ��ͬ�� */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} ET_ET_PA_CTRL_UNION;
#define ET_ET_PA_CTRL_dsp_pa_ctrl_mode_START  (0)
#define ET_ET_PA_CTRL_dsp_pa_ctrl_mode_END    (0)


/*****************************************************************************
 �ṹ��    : ET_ET_LIMIT_ENV_SLEW_PARA_UNION
 �ṹ˵��  : ET_LIMIT_ENV_SLEW_PARA �Ĵ����ṹ���塣��ַƫ����:0xC60����ֵ:0x06400640�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_limit_env_slew_para_reg;
    struct
    {
        unsigned int  dsp_down_slew_thd : 13; /* bit[0-12] : �ް��������ޣ�W��Ĭ��ֵ1600��LTE���Զ��壬ȡֵ��Χ0~8191���޷����� */
        unsigned int  reserved_0        : 3;  /* bit[13-15]: ���� */
        unsigned int  dsp_up_slew_thd   : 13; /* bit[16-28]: �ް��������ޣ�ȱʡֵ1600��ȡֵ��Χ0~8191���޷����� */
        unsigned int  reserved_1        : 3;  /* bit[29-31]: ���� */
    } reg;
} ET_ET_LIMIT_ENV_SLEW_PARA_UNION;
#define ET_ET_LIMIT_ENV_SLEW_PARA_dsp_down_slew_thd_START  (0)
#define ET_ET_LIMIT_ENV_SLEW_PARA_dsp_down_slew_thd_END    (12)
#define ET_ET_LIMIT_ENV_SLEW_PARA_dsp_up_slew_thd_START    (16)
#define ET_ET_LIMIT_ENV_SLEW_PARA_dsp_up_slew_thd_END      (28)


/*****************************************************************************
 �ṹ��    : ET_ET_ENV_TOP_EXTRA_PARA_UNION
 �ṹ˵��  : ET_ENV_TOP_EXTRA_PARA �Ĵ����ṹ���塣��ַƫ����:0xC68����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_env_top_extra_para_reg;
    struct
    {
        unsigned int  pre_offset         : 13; /* bit[0-12] : ����ת����ǰʹ�õ�ƫ�ơ�13λ�з���ֵ�� */
        unsigned int  dbb_tx_power_atten : 10; /* bit[13-22]: ���߲��𲹳������ֶβ����Ÿ����ʹ�á���д��üĴ���ʱ��Ӧȷ�����ֶ�ʼ��д��0x000���з���������ά�ɲ⹦�� */
        unsigned int  reserved           : 9;  /* bit[23-31]: ���� */
    } reg;
} ET_ET_ENV_TOP_EXTRA_PARA_UNION;
#define ET_ET_ENV_TOP_EXTRA_PARA_pre_offset_START          (0)
#define ET_ET_ENV_TOP_EXTRA_PARA_pre_offset_END            (12)
#define ET_ET_ENV_TOP_EXTRA_PARA_dbb_tx_power_atten_START  (13)
#define ET_ET_ENV_TOP_EXTRA_PARA_dbb_tx_power_atten_END    (22)


/*****************************************************************************
 �ṹ��    : ET_ET_IIR_COEF_0_1_PARA_UNION
 �ṹ˵��  : ET_IIR_COEF_0_1_PARA �Ĵ����ṹ���塣��ַƫ����:0xC6C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_iir_coef_0_1_para_reg;
    struct
    {
        unsigned int  iir_coef1_para : 12; /* bit[0-11] : Ⱥ�ӳپ�����IIR�˲���ϵ��a12���з������� */
        unsigned int  reserved_0     : 4;  /* bit[12-15]: ���� */
        unsigned int  iir_coef0_para : 12; /* bit[16-27]: Ⱥ�ӳپ�����IIR�˲���ϵ��a11���з������� */
        unsigned int  reserved_1     : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_IIR_COEF_0_1_PARA_UNION;
#define ET_ET_IIR_COEF_0_1_PARA_iir_coef1_para_START  (0)
#define ET_ET_IIR_COEF_0_1_PARA_iir_coef1_para_END    (11)
#define ET_ET_IIR_COEF_0_1_PARA_iir_coef0_para_START  (16)
#define ET_ET_IIR_COEF_0_1_PARA_iir_coef0_para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_IIR_COEF_2_3_PARA_UNION
 �ṹ˵��  : ET_IIR_COEF_2_3_PARA �Ĵ����ṹ���塣��ַƫ����:0xC70����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_iir_coef_2_3_para_reg;
    struct
    {
        unsigned int  iir_coef3_para : 12; /* bit[0-11] : Ⱥ�ӳپ�����IIR�˲���ϵ��b12���з������� */
        unsigned int  reserved_0     : 4;  /* bit[12-15]: ���� */
        unsigned int  iir_coef2_para : 12; /* bit[16-27]: Ⱥ�ӳپ�����IIR�˲���ϵ��b11���з������� */
        unsigned int  reserved_1     : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_IIR_COEF_2_3_PARA_UNION;
#define ET_ET_IIR_COEF_2_3_PARA_iir_coef3_para_START  (0)
#define ET_ET_IIR_COEF_2_3_PARA_iir_coef3_para_END    (11)
#define ET_ET_IIR_COEF_2_3_PARA_iir_coef2_para_START  (16)
#define ET_ET_IIR_COEF_2_3_PARA_iir_coef2_para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_IIR_COEF_4_5_PARA_UNION
 �ṹ˵��  : ET_IIR_COEF_4_5_PARA �Ĵ����ṹ���塣��ַƫ����:0xC74����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_iir_coef_4_5_para_reg;
    struct
    {
        unsigned int  iir_coef5_para : 12; /* bit[0-11] : Ⱥ�ӳپ�����IIR�˲���ϵ��a21���з������� */
        unsigned int  reserved_0     : 4;  /* bit[12-15]: ���� */
        unsigned int  iir_coef4_para : 12; /* bit[16-27]: Ⱥ�ӳپ�����IIR�˲���ϵ��b13���з������� */
        unsigned int  reserved_1     : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_IIR_COEF_4_5_PARA_UNION;
#define ET_ET_IIR_COEF_4_5_PARA_iir_coef5_para_START  (0)
#define ET_ET_IIR_COEF_4_5_PARA_iir_coef5_para_END    (11)
#define ET_ET_IIR_COEF_4_5_PARA_iir_coef4_para_START  (16)
#define ET_ET_IIR_COEF_4_5_PARA_iir_coef4_para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_IIR_COEF_6_7_PARA_UNION
 �ṹ˵��  : ET_IIR_COEF_6_7_PARA �Ĵ����ṹ���塣��ַƫ����:0xC78����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_iir_coef_6_7_para_reg;
    struct
    {
        unsigned int  iir_coef7_para : 12; /* bit[0-11] : Ⱥ�ӳپ�����IIR�˲���ϵ��b21���з������� */
        unsigned int  reserved_0     : 4;  /* bit[12-15]: ���� */
        unsigned int  iir_coef6_para : 12; /* bit[16-27]: Ⱥ�ӳپ�����IIR�˲���ϵ��a22���з������� */
        unsigned int  reserved_1     : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_IIR_COEF_6_7_PARA_UNION;
#define ET_ET_IIR_COEF_6_7_PARA_iir_coef7_para_START  (0)
#define ET_ET_IIR_COEF_6_7_PARA_iir_coef7_para_END    (11)
#define ET_ET_IIR_COEF_6_7_PARA_iir_coef6_para_START  (16)
#define ET_ET_IIR_COEF_6_7_PARA_iir_coef6_para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_IIR_COEF_8_9_PARA_UNION
 �ṹ˵��  : ET_IIR_COEF_8_9_PARA �Ĵ����ṹ���塣��ַƫ����:0xC7C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_iir_coef_8_9_para_reg;
    struct
    {
        unsigned int  iir_coef9_para : 12; /* bit[0-11] : Ⱥ�ӳپ�����IIR�˲���ϵ��b23���з������� */
        unsigned int  reserved_0     : 4;  /* bit[12-15]: ���� */
        unsigned int  iir_coef8_para : 12; /* bit[16-27]: Ⱥ�ӳپ�����IIR�˲���ϵ��b22���з������� */
        unsigned int  reserved_1     : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_IIR_COEF_8_9_PARA_UNION;
#define ET_ET_IIR_COEF_8_9_PARA_iir_coef9_para_START  (0)
#define ET_ET_IIR_COEF_8_9_PARA_iir_coef9_para_END    (11)
#define ET_ET_IIR_COEF_8_9_PARA_iir_coef8_para_START  (16)
#define ET_ET_IIR_COEF_8_9_PARA_iir_coef8_para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_IIR_COEF_10_11_PARA_UNION
 �ṹ˵��  : ET_IIR_COEF_10_11_PARA �Ĵ����ṹ���塣��ַƫ����:0xC80����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_iir_coef_10_11_para_reg;
    struct
    {
        unsigned int  iir_coef11_para : 12; /* bit[0-11] : Ⱥ�ӳپ�����IIR�˲���ϵ��a32���з������� */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: ���� */
        unsigned int  iir_coef10_para : 12; /* bit[16-27]: Ⱥ�ӳپ�����IIR�˲���ϵ��a31���з������� */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_IIR_COEF_10_11_PARA_UNION;
#define ET_ET_IIR_COEF_10_11_PARA_iir_coef11_para_START  (0)
#define ET_ET_IIR_COEF_10_11_PARA_iir_coef11_para_END    (11)
#define ET_ET_IIR_COEF_10_11_PARA_iir_coef10_para_START  (16)
#define ET_ET_IIR_COEF_10_11_PARA_iir_coef10_para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_IIR_COEF_12_13_PARA_UNION
 �ṹ˵��  : ET_IIR_COEF_12_13_PARA �Ĵ����ṹ���塣��ַƫ����:0xC84����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_iir_coef_12_13_para_reg;
    struct
    {
        unsigned int  iir_coef13_para : 12; /* bit[0-11] : Ⱥ�ӳپ�����IIR�˲���ϵ��b32���з������� */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: ���� */
        unsigned int  iir_coef12_para : 12; /* bit[16-27]: Ⱥ�ӳپ�����IIR�˲���ϵ��b31���з������� */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_IIR_COEF_12_13_PARA_UNION;
#define ET_ET_IIR_COEF_12_13_PARA_iir_coef13_para_START  (0)
#define ET_ET_IIR_COEF_12_13_PARA_iir_coef13_para_END    (11)
#define ET_ET_IIR_COEF_12_13_PARA_iir_coef12_para_START  (16)
#define ET_ET_IIR_COEF_12_13_PARA_iir_coef12_para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_IIR_COEF_14_PARA_UNION
 �ṹ˵��  : ET_IIR_COEF_14_PARA �Ĵ����ṹ���塣��ַƫ����:0xC88����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_iir_coef_14_para_reg;
    struct
    {
        unsigned int  reserved_0      : 16; /* bit[0-15] : ���� */
        unsigned int  iir_coef14_para : 12; /* bit[16-27]: Ⱥ�ӳپ�����IIR�˲���ϵ��b33���з������� */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_IIR_COEF_14_PARA_UNION;
#define ET_ET_IIR_COEF_14_PARA_iir_coef14_para_START  (16)
#define ET_ET_IIR_COEF_14_PARA_iir_coef14_para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_IIR_SHIFT_PARA_UNION
 �ṹ˵��  : ET_IIR_SHIFT_PARA �Ĵ����ṹ���塣��ַƫ����:0xC8C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_iir_shift_para_reg;
    struct
    {
        unsigned int  iir_shift0_para  : 2;  /* bit[0-1]  : Ⱥ�ӳپ�����IIR�˲���a11֧·����������λ�������ơ�
                                                            0:9
                                                            1:10
                                                            2:11
                                                            3:12 */
        unsigned int  iir_shift1_para  : 2;  /* bit[2-3]  : Ⱥ�ӳپ�����IIR�˲���a12֧·����������λ�������ơ�
                                                            0:9
                                                            1:10
                                                            2:11
                                                            3:12 */
        unsigned int  iir_shift2_para  : 2;  /* bit[4-5]  : Ⱥ�ӳپ�����IIR�˲���b11֧·����������λ�������ơ�
                                                            0:9
                                                            1:10
                                                            2:11
                                                            3:12 */
        unsigned int  iir_shift3_para  : 2;  /* bit[6-7]  : Ⱥ�ӳپ�����IIR�˲���b12֧·����������λ�������ơ�
                                                            0:9
                                                            1:10
                                                            2:11
                                                            3:12 */
        unsigned int  iir_shift4_para  : 2;  /* bit[8-9]  : Ⱥ�ӳپ�����IIR�˲���b13֧·����������λ�������ơ�
                                                            0:9
                                                            1:10
                                                            2:11
                                                            3:12 */
        unsigned int  iir_shift5_para  : 2;  /* bit[10-11]: Ⱥ�ӳپ�����IIR�˲���a21֧·����������λ�������ơ�
                                                            0:9
                                                            1:10
                                                            2:11
                                                            3:12 */
        unsigned int  iir_shift6_para  : 2;  /* bit[12-13]: Ⱥ�ӳپ�����IIR�˲���a22֧·����������λ�������ơ�
                                                            0:9
                                                            1:10
                                                            2:11
                                                            3:12 */
        unsigned int  iir_shift7_para  : 2;  /* bit[14-15]: Ⱥ�ӳپ�����IIR�˲���b21֧·����������λ�������ơ�
                                                            0:9
                                                            1:10
                                                            2:11
                                                            3:12 */
        unsigned int  iir_shift8_para  : 2;  /* bit[16-17]: Ⱥ�ӳپ�����IIR�˲���b22֧·����������λ�������ơ�
                                                            0:9
                                                            1:10
                                                            2:11
                                                            3:12 */
        unsigned int  iir_shift9_para  : 2;  /* bit[18-19]: Ⱥ�ӳپ�����IIR�˲���b23֧·����������λ�������ơ�
                                                            0:9
                                                            1:10
                                                            2:11
                                                            3:12 */
        unsigned int  iir_shift10_para : 2;  /* bit[20-21]: Ⱥ�ӳپ�����IIR�˲���a31����������λ�������ơ�
                                                            0:9
                                                            1:10
                                                            2:11
                                                            3:12 */
        unsigned int  iir_shift11_para : 2;  /* bit[22-23]: Ⱥ�ӳپ�����IIR�˲���a32֧·����������λ�������ơ�
                                                            0:9
                                                            1:10
                                                            2:11
                                                            3:12 */
        unsigned int  iir_shift12_para : 2;  /* bit[24-25]: Ⱥ�ӳپ�����IIR�˲���b31֧·����������λ�������ơ�
                                                            0:9
                                                            1:10
                                                            2:11
                                                            3:12 */
        unsigned int  iir_shift13_para : 2;  /* bit[26-27]: Ⱥ�ӳپ�����IIR�˲���b32֧·����������λ�������ơ�
                                                            0:9
                                                            1:10
                                                            2:11
                                                            3:12 */
        unsigned int  iir_shift14_para : 2;  /* bit[28-29]: Ⱥ�ӳپ�����IIR�˲���b33֧·����������λ�������ơ��޷���
                                                            0:9
                                                            1:10
                                                            2:11
                                                            3:12 */
        unsigned int  reserved         : 2;  /* bit[30-31]: ���� */
    } reg;
} ET_ET_IIR_SHIFT_PARA_UNION;
#define ET_ET_IIR_SHIFT_PARA_iir_shift0_para_START   (0)
#define ET_ET_IIR_SHIFT_PARA_iir_shift0_para_END     (1)
#define ET_ET_IIR_SHIFT_PARA_iir_shift1_para_START   (2)
#define ET_ET_IIR_SHIFT_PARA_iir_shift1_para_END     (3)
#define ET_ET_IIR_SHIFT_PARA_iir_shift2_para_START   (4)
#define ET_ET_IIR_SHIFT_PARA_iir_shift2_para_END     (5)
#define ET_ET_IIR_SHIFT_PARA_iir_shift3_para_START   (6)
#define ET_ET_IIR_SHIFT_PARA_iir_shift3_para_END     (7)
#define ET_ET_IIR_SHIFT_PARA_iir_shift4_para_START   (8)
#define ET_ET_IIR_SHIFT_PARA_iir_shift4_para_END     (9)
#define ET_ET_IIR_SHIFT_PARA_iir_shift5_para_START   (10)
#define ET_ET_IIR_SHIFT_PARA_iir_shift5_para_END     (11)
#define ET_ET_IIR_SHIFT_PARA_iir_shift6_para_START   (12)
#define ET_ET_IIR_SHIFT_PARA_iir_shift6_para_END     (13)
#define ET_ET_IIR_SHIFT_PARA_iir_shift7_para_START   (14)
#define ET_ET_IIR_SHIFT_PARA_iir_shift7_para_END     (15)
#define ET_ET_IIR_SHIFT_PARA_iir_shift8_para_START   (16)
#define ET_ET_IIR_SHIFT_PARA_iir_shift8_para_END     (17)
#define ET_ET_IIR_SHIFT_PARA_iir_shift9_para_START   (18)
#define ET_ET_IIR_SHIFT_PARA_iir_shift9_para_END     (19)
#define ET_ET_IIR_SHIFT_PARA_iir_shift10_para_START  (20)
#define ET_ET_IIR_SHIFT_PARA_iir_shift10_para_END    (21)
#define ET_ET_IIR_SHIFT_PARA_iir_shift11_para_START  (22)
#define ET_ET_IIR_SHIFT_PARA_iir_shift11_para_END    (23)
#define ET_ET_IIR_SHIFT_PARA_iir_shift12_para_START  (24)
#define ET_ET_IIR_SHIFT_PARA_iir_shift12_para_END    (25)
#define ET_ET_IIR_SHIFT_PARA_iir_shift13_para_START  (26)
#define ET_ET_IIR_SHIFT_PARA_iir_shift13_para_END    (27)
#define ET_ET_IIR_SHIFT_PARA_iir_shift14_para_START  (28)
#define ET_ET_IIR_SHIFT_PARA_iir_shift14_para_END    (29)


/*****************************************************************************
 �ṹ��    : ET_ET_FIR_COEF_0_1_PARA_UNION
 �ṹ˵��  : ET_FIR_COEF_0_1_PARA �Ĵ����ṹ���塣��ַƫ����:0xC90����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_0_1_para_reg;
    struct
    {
        unsigned int  fir_coef1_para : 12; /* bit[0-11] : �������FIR�˲�����ͷ(1/z)^1��ϵ�����з������� */
        unsigned int  reserved_0     : 4;  /* bit[12-15]: ���� */
        unsigned int  fir_coef0_para : 12; /* bit[16-27]: �������FIR�˲�����ͷ(1/z)^0��ϵ������Ӧ�����ӳ���С�����з������� */
        unsigned int  reserved_1     : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_FIR_COEF_0_1_PARA_UNION;
#define ET_ET_FIR_COEF_0_1_PARA_fir_coef1_para_START  (0)
#define ET_ET_FIR_COEF_0_1_PARA_fir_coef1_para_END    (11)
#define ET_ET_FIR_COEF_0_1_PARA_fir_coef0_para_START  (16)
#define ET_ET_FIR_COEF_0_1_PARA_fir_coef0_para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_FIR_COEF_2_3_PARA_UNION
 �ṹ˵��  : ET_FIR_COEF_2_3_PARA �Ĵ����ṹ���塣��ַƫ����:0xC94����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_2_3_para_reg;
    struct
    {
        unsigned int  fir_coef3_para : 12; /* bit[0-11] : �������FIR�˲�����ͷ(1/z)^3��ϵ�����з������� */
        unsigned int  reserved_0     : 4;  /* bit[12-15]: ���� */
        unsigned int  fir_coef2_para : 12; /* bit[16-27]: �������FIR�˲�����ͷ(1/z)^2��ϵ�����з������� */
        unsigned int  reserved_1     : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_FIR_COEF_2_3_PARA_UNION;
#define ET_ET_FIR_COEF_2_3_PARA_fir_coef3_para_START  (0)
#define ET_ET_FIR_COEF_2_3_PARA_fir_coef3_para_END    (11)
#define ET_ET_FIR_COEF_2_3_PARA_fir_coef2_para_START  (16)
#define ET_ET_FIR_COEF_2_3_PARA_fir_coef2_para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_FIR_COEF_4_5_PARA_UNION
 �ṹ˵��  : ET_FIR_COEF_4_5_PARA �Ĵ����ṹ���塣��ַƫ����:0xC98����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_4_5_para_reg;
    struct
    {
        unsigned int  fir_coef5_para : 12; /* bit[0-11] : �������FIR�˲�����ͷ(1/z)^5��ϵ�����з������� */
        unsigned int  reserved_0     : 4;  /* bit[12-15]: ���� */
        unsigned int  fir_coef4_para : 12; /* bit[16-27]: �������FIR�˲�����ͷ(1/z)^4��ϵ�����з������� */
        unsigned int  reserved_1     : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_FIR_COEF_4_5_PARA_UNION;
#define ET_ET_FIR_COEF_4_5_PARA_fir_coef5_para_START  (0)
#define ET_ET_FIR_COEF_4_5_PARA_fir_coef5_para_END    (11)
#define ET_ET_FIR_COEF_4_5_PARA_fir_coef4_para_START  (16)
#define ET_ET_FIR_COEF_4_5_PARA_fir_coef4_para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_FIR_COEF_6_7_PARA_UNION
 �ṹ˵��  : ET_FIR_COEF_6_7_PARA �Ĵ����ṹ���塣��ַƫ����:0xC9C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_6_7_para_reg;
    struct
    {
        unsigned int  fir_coef7_para : 12; /* bit[0-11] : �������FIR�˲�����ͷ(1/z)^7��ϵ�����з������� */
        unsigned int  reserved_0     : 4;  /* bit[12-15]: ���� */
        unsigned int  fir_coef6_para : 12; /* bit[16-27]: �������FIR�˲�����ͷ(1/z)^6��ϵ�����з������� */
        unsigned int  reserved_1     : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_FIR_COEF_6_7_PARA_UNION;
#define ET_ET_FIR_COEF_6_7_PARA_fir_coef7_para_START  (0)
#define ET_ET_FIR_COEF_6_7_PARA_fir_coef7_para_END    (11)
#define ET_ET_FIR_COEF_6_7_PARA_fir_coef6_para_START  (16)
#define ET_ET_FIR_COEF_6_7_PARA_fir_coef6_para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_FIR_COEF_8_9_PARA_UNION
 �ṹ˵��  : ET_FIR_COEF_8_9_PARA �Ĵ����ṹ���塣��ַƫ����:0xCA0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_8_9_para_reg;
    struct
    {
        unsigned int  fir_coef9_para : 12; /* bit[0-11] : �������FIR�˲�����ͷ(1/z)^9��ϵ�����з������� */
        unsigned int  reserved_0     : 4;  /* bit[12-15]: ���� */
        unsigned int  fir_coef8_para : 12; /* bit[16-27]: �������FIR�˲�����ͷ(1/z)^8��ϵ�����з������� */
        unsigned int  reserved_1     : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_FIR_COEF_8_9_PARA_UNION;
#define ET_ET_FIR_COEF_8_9_PARA_fir_coef9_para_START  (0)
#define ET_ET_FIR_COEF_8_9_PARA_fir_coef9_para_END    (11)
#define ET_ET_FIR_COEF_8_9_PARA_fir_coef8_para_START  (16)
#define ET_ET_FIR_COEF_8_9_PARA_fir_coef8_para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_FIR_COEF_10_11_PARA_UNION
 �ṹ˵��  : ET_FIR_COEF_10_11_PARA �Ĵ����ṹ���塣��ַƫ����:0xCA4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_10_11_para_reg;
    struct
    {
        unsigned int  fir_coef11_para : 12; /* bit[0-11] : �������FIR�˲�����ͷ(1/z)^11��ϵ�����з������� */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: ���� */
        unsigned int  fir_coef10_para : 12; /* bit[16-27]: �������FIR�˲�����ͷ(1/z)^10��ϵ�����з������� */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_FIR_COEF_10_11_PARA_UNION;
#define ET_ET_FIR_COEF_10_11_PARA_fir_coef11_para_START  (0)
#define ET_ET_FIR_COEF_10_11_PARA_fir_coef11_para_END    (11)
#define ET_ET_FIR_COEF_10_11_PARA_fir_coef10_para_START  (16)
#define ET_ET_FIR_COEF_10_11_PARA_fir_coef10_para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_FIR_COEF_12_13_PARA_UNION
 �ṹ˵��  : ET_FIR_COEF_12_13_PARA �Ĵ����ṹ���塣��ַƫ����:0xCA8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_12_13_para_reg;
    struct
    {
        unsigned int  fir_coef13_para : 12; /* bit[0-11] : �������FIR�˲�����ͷ(1/z)^13��ϵ�����з������� */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: ���� */
        unsigned int  fir_coef12_para : 12; /* bit[16-27]: �������FIR�˲�����ͷ(1/z)^12��ϵ�����з������� */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_FIR_COEF_12_13_PARA_UNION;
#define ET_ET_FIR_COEF_12_13_PARA_fir_coef13_para_START  (0)
#define ET_ET_FIR_COEF_12_13_PARA_fir_coef13_para_END    (11)
#define ET_ET_FIR_COEF_12_13_PARA_fir_coef12_para_START  (16)
#define ET_ET_FIR_COEF_12_13_PARA_fir_coef12_para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_FIR_COEF_14_15_PARA_UNION
 �ṹ˵��  : ET_FIR_COEF_14_15_PARA �Ĵ����ṹ���塣��ַƫ����:0xCAC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_14_15_para_reg;
    struct
    {
        unsigned int  fir_coef15_para : 12; /* bit[0-11] : �������FIR�˲�����ͷ(1/z)^15��ϵ�����з������� */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: ���� */
        unsigned int  fir_coef14_para : 12; /* bit[16-27]: �������FIR�˲�����ͷ(1/z)^14��ϵ�����з������� */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_FIR_COEF_14_15_PARA_UNION;
#define ET_ET_FIR_COEF_14_15_PARA_fir_coef15_para_START  (0)
#define ET_ET_FIR_COEF_14_15_PARA_fir_coef15_para_END    (11)
#define ET_ET_FIR_COEF_14_15_PARA_fir_coef14_para_START  (16)
#define ET_ET_FIR_COEF_14_15_PARA_fir_coef14_para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_FIR_COEF_16_17_PARA_UNION
 �ṹ˵��  : ET_FIR_COEF_16_17_PARA �Ĵ����ṹ���塣��ַƫ����:0xCB0����ֵ:0x000007FF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_16_17_para_reg;
    struct
    {
        unsigned int  fir_coef17_para : 12; /* bit[0-11] : �������FIR�˲�����ͷ(1/z)^17��ϵ�����з������� */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: ���� */
        unsigned int  fir_coef16_para : 12; /* bit[16-27]: �������FIR�˲�����ͷ(1/z)^16��ϵ�����з������� */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_FIR_COEF_16_17_PARA_UNION;
#define ET_ET_FIR_COEF_16_17_PARA_fir_coef17_para_START  (0)
#define ET_ET_FIR_COEF_16_17_PARA_fir_coef17_para_END    (11)
#define ET_ET_FIR_COEF_16_17_PARA_fir_coef16_para_START  (16)
#define ET_ET_FIR_COEF_16_17_PARA_fir_coef16_para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_FIR_COEF_18_19_PARA_UNION
 �ṹ˵��  : ET_FIR_COEF_18_19_PARA �Ĵ����ṹ���塣��ַƫ����:0xCB4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_18_19_para_reg;
    struct
    {
        unsigned int  fir_coef19_para : 12; /* bit[0-11] : �������FIR�˲�����ͷ(1/z)^19��ϵ�����з������� */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: ���� */
        unsigned int  fir_coef18_para : 12; /* bit[16-27]: �������FIR�˲�����ͷ(1/z)^18��ϵ�����з������� */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_FIR_COEF_18_19_PARA_UNION;
#define ET_ET_FIR_COEF_18_19_PARA_fir_coef19_para_START  (0)
#define ET_ET_FIR_COEF_18_19_PARA_fir_coef19_para_END    (11)
#define ET_ET_FIR_COEF_18_19_PARA_fir_coef18_para_START  (16)
#define ET_ET_FIR_COEF_18_19_PARA_fir_coef18_para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_FIR_COEF_20_21_PARA_UNION
 �ṹ˵��  : ET_FIR_COEF_20_21_PARA �Ĵ����ṹ���塣��ַƫ����:0xCB8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_20_21_para_reg;
    struct
    {
        unsigned int  fir_coef21_para : 12; /* bit[0-11] : �������FIR�˲�����ͷ(1/z)^21��ϵ�����з������� */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: ���� */
        unsigned int  fir_coef20_para : 12; /* bit[16-27]: �������FIR�˲�����ͷ(1/z)^20��ϵ�����з������� */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_FIR_COEF_20_21_PARA_UNION;
#define ET_ET_FIR_COEF_20_21_PARA_fir_coef21_para_START  (0)
#define ET_ET_FIR_COEF_20_21_PARA_fir_coef21_para_END    (11)
#define ET_ET_FIR_COEF_20_21_PARA_fir_coef20_para_START  (16)
#define ET_ET_FIR_COEF_20_21_PARA_fir_coef20_para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_FIR_COEF_22_23_PARA_UNION
 �ṹ˵��  : ET_FIR_COEF_22_23_PARA �Ĵ����ṹ���塣��ַƫ����:0xCBC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_22_23_para_reg;
    struct
    {
        unsigned int  fir_coef23_para : 12; /* bit[0-11] : �������FIR�˲�����ͷ(1/z)^23��ϵ�����з������� */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: ���� */
        unsigned int  fir_coef22_para : 12; /* bit[16-27]: �������FIR�˲�����ͷ(1/z)^22��ϵ�����з������� */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_FIR_COEF_22_23_PARA_UNION;
#define ET_ET_FIR_COEF_22_23_PARA_fir_coef23_para_START  (0)
#define ET_ET_FIR_COEF_22_23_PARA_fir_coef23_para_END    (11)
#define ET_ET_FIR_COEF_22_23_PARA_fir_coef22_para_START  (16)
#define ET_ET_FIR_COEF_22_23_PARA_fir_coef22_para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_FIR_COEF_24_25_PARA_UNION
 �ṹ˵��  : ET_FIR_COEF_24_25_PARA �Ĵ����ṹ���塣��ַƫ����:0xCC0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_24_25_para_reg;
    struct
    {
        unsigned int  fir_coef25_para : 12; /* bit[0-11] : �������FIR�˲�����ͷ(1/z)^25��ϵ�����з������� */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: ���� */
        unsigned int  fir_coef24_para : 12; /* bit[16-27]: �������FIR�˲�����ͷ(1/z)^24��ϵ�����з������� */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_FIR_COEF_24_25_PARA_UNION;
#define ET_ET_FIR_COEF_24_25_PARA_fir_coef25_para_START  (0)
#define ET_ET_FIR_COEF_24_25_PARA_fir_coef25_para_END    (11)
#define ET_ET_FIR_COEF_24_25_PARA_fir_coef24_para_START  (16)
#define ET_ET_FIR_COEF_24_25_PARA_fir_coef24_para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_FIR_COEF_26_27_PARA_UNION
 �ṹ˵��  : ET_FIR_COEF_26_27_PARA �Ĵ����ṹ���塣��ַƫ����:0xCC4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_26_27_para_reg;
    struct
    {
        unsigned int  fir_coef27_para : 12; /* bit[0-11] : �������FIR�˲�����ͷ(1/z)^27��ϵ�����з������� */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: ���� */
        unsigned int  fir_coef26_para : 12; /* bit[16-27]: �������FIR�˲�����ͷ(1/z)^26��ϵ�����з������� */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_FIR_COEF_26_27_PARA_UNION;
#define ET_ET_FIR_COEF_26_27_PARA_fir_coef27_para_START  (0)
#define ET_ET_FIR_COEF_26_27_PARA_fir_coef27_para_END    (11)
#define ET_ET_FIR_COEF_26_27_PARA_fir_coef26_para_START  (16)
#define ET_ET_FIR_COEF_26_27_PARA_fir_coef26_para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_FIR_COEF_28_29_PARA_UNION
 �ṹ˵��  : ET_FIR_COEF_28_29_PARA �Ĵ����ṹ���塣��ַƫ����:0xCC8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_28_29_para_reg;
    struct
    {
        unsigned int  fir_coef29_para : 12; /* bit[0-11] : �������FIR�˲�����ͷ(1/z)^29��ϵ�����з������� */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: ���� */
        unsigned int  fir_coef28_para : 12; /* bit[16-27]: �������FIR�˲�����ͷ(1/z)^28��ϵ�����з������� */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_FIR_COEF_28_29_PARA_UNION;
#define ET_ET_FIR_COEF_28_29_PARA_fir_coef29_para_START  (0)
#define ET_ET_FIR_COEF_28_29_PARA_fir_coef29_para_END    (11)
#define ET_ET_FIR_COEF_28_29_PARA_fir_coef28_para_START  (16)
#define ET_ET_FIR_COEF_28_29_PARA_fir_coef28_para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_FIR_COEF_30_31_PARA_UNION
 �ṹ˵��  : ET_FIR_COEF_30_31_PARA �Ĵ����ṹ���塣��ַƫ����:0xCCC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_30_31_para_reg;
    struct
    {
        unsigned int  fir_coef31_para : 12; /* bit[0-11] : �������FIR�˲�����ͷ(1/z)^31��ϵ�����з������� */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: ���� */
        unsigned int  fir_coef30_para : 12; /* bit[16-27]: �������FIR�˲�����ͷ(1/z)^30��ϵ�����з������� */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_FIR_COEF_30_31_PARA_UNION;
#define ET_ET_FIR_COEF_30_31_PARA_fir_coef31_para_START  (0)
#define ET_ET_FIR_COEF_30_31_PARA_fir_coef31_para_END    (11)
#define ET_ET_FIR_COEF_30_31_PARA_fir_coef30_para_START  (16)
#define ET_ET_FIR_COEF_30_31_PARA_fir_coef30_para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_FIR_COEF_32_33_PARA_UNION
 �ṹ˵��  : ET_FIR_COEF_32_33_PARA �Ĵ����ṹ���塣��ַƫ����:0xCD0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_32_33_para_reg;
    struct
    {
        unsigned int  fir_coef33_para : 12; /* bit[0-11] : �������FIR�˲�����ͷ(1/z)^33��ϵ�����з������� */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: ���� */
        unsigned int  fir_coef32_para : 12; /* bit[16-27]: �������FIR�˲�����ͷ(1/z)^32��ϵ�����з������� */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_FIR_COEF_32_33_PARA_UNION;
#define ET_ET_FIR_COEF_32_33_PARA_fir_coef33_para_START  (0)
#define ET_ET_FIR_COEF_32_33_PARA_fir_coef33_para_END    (11)
#define ET_ET_FIR_COEF_32_33_PARA_fir_coef32_para_START  (16)
#define ET_ET_FIR_COEF_32_33_PARA_fir_coef32_para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_FIR_COEF_34_PARA_UNION
 �ṹ˵��  : ET_FIR_COEF_34_PARA �Ĵ����ṹ���塣��ַƫ����:0xCD4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_fir_coef_34_para_reg;
    struct
    {
        unsigned int  reserved_0      : 16; /* bit[0-15] : ���� */
        unsigned int  fir_coef34_para : 12; /* bit[16-27]: �������FIR�˲�����ͷ(1/z)^34��ϵ������Ӧ�����ӳ���󣩣��з������� */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: ���� */
    } reg;
} ET_ET_FIR_COEF_34_PARA_UNION;
#define ET_ET_FIR_COEF_34_PARA_fir_coef34_para_START  (16)
#define ET_ET_FIR_COEF_34_PARA_fir_coef34_para_END    (27)


/*****************************************************************************
 �ṹ��    : ET_ET_CTRL_DELAY0_UNION
 �ṹ˵��  : ET_CTRL_DELAY0 �Ĵ����ṹ���塣��ַƫ����:0xCE4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_ctrl_delay0_reg;
    struct
    {
        unsigned int  ctrl_dly_t1 : 16; /* bit[0-15] : t��ʱ��λΪ��·ʱ������
                                                       ��t��ʱԼ����ϵ��
                                                       t3 >= t1 ;
                                                       t4 < t6 ;
                                                       t4+t5 > t6+t7 ;
                                                       
                                                       ͨ��0����ctrl2swch_et_mode_sel, ctrl2swch_apt_pa_vcc_ind, ctrl2proc_et_mode_en���ӳ٣�
                                                       ������ʱֵ��Ӧ����etͨ·����ʱ����ͬ��
                                                       
                                                       һ��t��ʱ�ο�ֵ��
                                                       ��etͨ·�����ӳټĴ���ֵΪx����t1 = x + 'd51; t2 = 0;
                                                       t3 = x + 'd51; 
                                                       t4 = x + 'd51; t5 = 0; 
                                                       t6 = x + 'd51; t7 = 0; 
                                                       t8 = x + 'd96; */
        unsigned int  ctrl_dly_t2 : 16; /* bit[16-31]: ͨ��0����ctrl2proc_et_mode_en�½��ص��ӳ٣��޷�������
                                                       ������ʱֵ��Ӧ����etͨ·����ʱ�� */
    } reg;
} ET_ET_CTRL_DELAY0_UNION;
#define ET_ET_CTRL_DELAY0_ctrl_dly_t1_START  (0)
#define ET_ET_CTRL_DELAY0_ctrl_dly_t1_END    (15)
#define ET_ET_CTRL_DELAY0_ctrl_dly_t2_START  (16)
#define ET_ET_CTRL_DELAY0_ctrl_dly_t2_END    (31)


/*****************************************************************************
 �ṹ��    : ET_ET_CTRL_DELAY1_UNION
 �ṹ˵��  : ET_CTRL_DELAY1 �Ĵ����ṹ���塣��ַƫ����:0xCE8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_ctrl_delay1_reg;
    struct
    {
        unsigned int  ctrl_dly_t3 : 16; /* bit[0-15] : ͨ��0����et2pad_et_mode_sel���ӳ٣��ݲ�ʹ�á� */
        unsigned int  ctrl_dly_t8 : 16; /* bit[16-31]: et_ctrl�ڲ�ʹ�ã���ʱet_act_en */
    } reg;
} ET_ET_CTRL_DELAY1_UNION;
#define ET_ET_CTRL_DELAY1_ctrl_dly_t3_START  (0)
#define ET_ET_CTRL_DELAY1_ctrl_dly_t3_END    (15)
#define ET_ET_CTRL_DELAY1_ctrl_dly_t8_START  (16)
#define ET_ET_CTRL_DELAY1_ctrl_dly_t8_END    (31)


/*****************************************************************************
 �ṹ��    : ET_ET_CTRL_DELAY2_UNION
 �ṹ˵��  : ET_CTRL_DELAY2 �Ĵ����ṹ���塣��ַƫ����:0xCEC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_ctrl_delay2_reg;
    struct
    {
        unsigned int  ctrl_dly_t5 : 16; /* bit[0-15] : ͨ��0����et2abb_act_en�����ص��ӳ� */
        unsigned int  ctrl_dly_t4 : 16; /* bit[16-31]: ͨ��0����et2abb_act_en�½��ص��ӳ� */
    } reg;
} ET_ET_CTRL_DELAY2_UNION;
#define ET_ET_CTRL_DELAY2_ctrl_dly_t5_START  (0)
#define ET_ET_CTRL_DELAY2_ctrl_dly_t5_END    (15)
#define ET_ET_CTRL_DELAY2_ctrl_dly_t4_START  (16)
#define ET_ET_CTRL_DELAY2_ctrl_dly_t4_END    (31)


/*****************************************************************************
 �ṹ��    : ET_ET_CTRL_DELAY3_UNION
 �ṹ˵��  : ET_CTRL_DELAY3 �Ĵ����ṹ���塣��ַƫ����:0xCF0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_ctrl_delay3_reg;
    struct
    {
        unsigned int  ctrl_dly_t6 : 16; /* bit[0-15] : ͨ��0����et2abb_et_mode_sel�����ص��ӳ� */
        unsigned int  ctrl_dly_t7 : 16; /* bit[16-31]: ͨ��0����et2abb_et_mode_sel�½��ص��ӳ� */
    } reg;
} ET_ET_CTRL_DELAY3_UNION;
#define ET_ET_CTRL_DELAY3_ctrl_dly_t6_START  (0)
#define ET_ET_CTRL_DELAY3_ctrl_dly_t6_END    (15)
#define ET_ET_CTRL_DELAY3_ctrl_dly_t7_START  (16)
#define ET_ET_CTRL_DELAY3_ctrl_dly_t7_END    (31)


/*****************************************************************************
 �ṹ��    : ET_ET_CTRL_ETM_MODE_UNION
 �ṹ˵��  : ET_CTRL_ETM_MODE �Ĵ����ṹ���塣��ַƫ����:0xCF4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_ctrl_etm_mode_reg;
    struct
    {
        unsigned int  ctrl_etm_mode : 3;  /* bit[0-2] : 
                                                        λ[2]����ETMѡ��
                                                        0��ʹ�õ�����ETM��Ĭ��ֵ��
                                                        
                                                        λ[1:0]������ETM����ģʽ��
                                                        0������R2����ETM������                  
                                                        1������TI����ETM����ģʽ1��
                                                        2������TI����ETM����ģʽ2��
                                                        3������TI����ETM����ģʽ2�� */
        unsigned int  reserved      : 29; /* bit[3-31]: ���� */
    } reg;
} ET_ET_CTRL_ETM_MODE_UNION;
#define ET_ET_CTRL_ETM_MODE_ctrl_etm_mode_START  (0)
#define ET_ET_CTRL_ETM_MODE_ctrl_etm_mode_END    (2)


/*****************************************************************************
 �ṹ��    : ET_ET_PA_THD_PARA_HIGH_UNION
 �ṹ˵��  : ET_PA_THD_PARA_HIGH �Ĵ����ṹ���塣��ַƫ����:0xC5C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_pa_thd_para_high_reg;
    struct
    {
        unsigned int  dsp_pa_mid_table_offset  : 11; /* bit[0-10] : �ò�����ʾPA�����湦�ʵ�ѹ���ұ��0���ƫ�Ƶ�ַ0xA00������Ӧ�Ĺ���ֵ���ò���Ϊ11bit�޷���������λΪ0.0125dB��Ĭ��ֵΪ0�� */
        unsigned int  reserved_0               : 5;  /* bit[11-15]: ���� */
        unsigned int  dsp_pa_high_table_offset : 11; /* bit[16-26]: �ò�����ʾPA�����湦�ʵ�ѹ���ұ��0���ƫ�Ƶ�ַ0x800������Ӧ�Ĺ���ֵ���ò���Ϊ11bit�޷���������λΪ0.0125dB��Ĭ��ֵΪ0�� */
        unsigned int  reserved_1               : 5;  /* bit[27-31]: ���� */
    } reg;
} ET_ET_PA_THD_PARA_HIGH_UNION;
#define ET_ET_PA_THD_PARA_HIGH_dsp_pa_mid_table_offset_START   (0)
#define ET_ET_PA_THD_PARA_HIGH_dsp_pa_mid_table_offset_END     (10)
#define ET_ET_PA_THD_PARA_HIGH_dsp_pa_high_table_offset_START  (16)
#define ET_ET_PA_THD_PARA_HIGH_dsp_pa_high_table_offset_END    (26)


/*****************************************************************************
 �ṹ��    : ET_AUTO_RESET_UNION
 �ṹ˵��  : AUTO_RESET �Ĵ����ṹ���塣��ַƫ����:0xCF8����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      auto_reset_reg;
    struct
    {
        unsigned int  mode_auto_reset_en : 1;  /* bit[0]   : L/Wģʽ�л��Զ���λʹ��
                                                             1����ģ�Զ���λ
                                                             0����ģ��������λ */
        unsigned int  reserved           : 31; /* bit[1-31]: ������ */
    } reg;
} ET_AUTO_RESET_UNION;
#define ET_AUTO_RESET_mode_auto_reset_en_START  (0)
#define ET_AUTO_RESET_mode_auto_reset_en_END    (0)


/*****************************************************************************
 �ṹ��    : ET_APT_CALIBRE_MODE_UNION
 �ṹ˵��  : APT_CALIBRE_MODE �Ĵ����ṹ���塣��ַƫ����:0xCFC����ֵ:0x0000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      apt_calibre_mode_reg;
    struct
    {
        unsigned int  calibre_sel          : 1;  /* bit[0]   : 1'b1: ѡ��APTУ׼ģʽ
                                                               1'b0: ��������ģʽ��Ĭ��ֵ */
        unsigned int  calibre_abb_mode_sel : 1;  /* bit[1]   : ��bitֻ��APTУ׼ģʽ����Ч
                                                               1'b1: ABB������ETģʽ
                                                               1'b0: ABB������APTģʽ */
        unsigned int  reserved             : 30; /* bit[2-31]: ������ */
    } reg;
} ET_APT_CALIBRE_MODE_UNION;
#define ET_APT_CALIBRE_MODE_calibre_sel_START           (0)
#define ET_APT_CALIBRE_MODE_calibre_sel_END             (0)
#define ET_APT_CALIBRE_MODE_calibre_abb_mode_sel_START  (1)
#define ET_APT_CALIBRE_MODE_calibre_abb_mode_sel_END    (1)


/*****************************************************************************
 �ṹ��    : ET_CALIBRE_VCC_UNION
 �ṹ˵��  : CALIBRE_VCC �Ĵ����ṹ���塣��ַƫ����:0xD00����ֵ:0x0000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      calibre_vcc_reg;
    struct
    {
        unsigned int  calibre_vcc : 14; /* bit[0-13] : ���У׼��ѹ���з����� */
        unsigned int  reserved    : 18; /* bit[14-31]: ������ */
    } reg;
} ET_CALIBRE_VCC_UNION;
#define ET_CALIBRE_VCC_calibre_vcc_START  (0)
#define ET_CALIBRE_VCC_calibre_vcc_END    (13)


/*****************************************************************************
 �ṹ��    : ET_INTRLV_SEL_UNION
 �ṹ˵��  : INTRLV_SEL �Ĵ����ṹ���塣��ַƫ����:0xD04����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      intrlv_sel_reg;
    struct
    {
        unsigned int  interleave_sel : 1;  /* bit[0]   : ����ͨ·�����֯˳��ѡ�� 
                                                         0: �����ż��Ĭ��ֵ  
                                                         1:��ż���� */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} ET_INTRLV_SEL_UNION;
#define ET_INTRLV_SEL_interleave_sel_START  (0)
#define ET_INTRLV_SEL_interleave_sel_END    (0)


/*****************************************************************************
 �ṹ��    : ET_ET_ALIGN_UNION
 �ṹ˵��  : ET_ALIGN �Ĵ����ṹ���塣��ַƫ����:0xD08����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_align_reg;
    struct
    {
        unsigned int  et_rf_align : 1;  /* bit[0]   : �������Ƶͨ·�������ݶ���ָʾ,
                                                      0:����
                                                      1:�������־ */
        unsigned int  reserved    : 31; /* bit[1-31]: ���� */
    } reg;
} ET_ET_ALIGN_UNION;
#define ET_ET_ALIGN_et_rf_align_START  (0)
#define ET_ET_ALIGN_et_rf_align_END    (0)


/*****************************************************************************
 �ṹ��    : ET_ET_STATUS_UNION
 �ṹ˵��  : ET_STATUS �Ĵ����ṹ���塣��ַƫ����:0xD0C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_status_reg;
    struct
    {
        unsigned int  apt2et_cnt : 8;  /* bit[0-7]  : APTģʽ��ETģʽ���� */
        unsigned int  et2apt_cnt : 8;  /* bit[8-15] : ETģʽ��APTģʽ���� */
        unsigned int  reserved   : 16; /* bit[16-31]: ���� */
    } reg;
} ET_ET_STATUS_UNION;
#define ET_ET_STATUS_apt2et_cnt_START  (0)
#define ET_ET_STATUS_apt2et_cnt_END    (7)
#define ET_ET_STATUS_et2apt_cnt_START  (8)
#define ET_ET_STATUS_et2apt_cnt_END    (15)


/*****************************************************************************
 �ṹ��    : ET_ET_RPT_CLEAR_UNION
 �ṹ˵��  : ET_RPT_CLEAR �Ĵ����ṹ���塣��ַƫ����:0xD10����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      et_rpt_clear_reg;
    struct
    {
        unsigned int  et_rpt_clear : 1;  /* bit[0]   : д1'b1�������ϱ��Ĵ������� */
        unsigned int  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} ET_ET_RPT_CLEAR_UNION;
#define ET_ET_RPT_CLEAR_et_rpt_clear_START  (0)
#define ET_ET_RPT_CLEAR_et_rpt_clear_END    (0)


/*****************************************************************************
 �ṹ��    : ET_LUT_RAM_SEL_UNION
 �ṹ˵��  : LUT_RAM_SEL �Ĵ����ṹ���塣��ַƫ����:0xD14����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      lut_ram_sel_reg;
    struct
    {
        unsigned int  lut_ram_sel : 2;  /* bit[0-1] : [1]: force config enable;
                                                      [0]: 1'b1, force select internal logic; 1'b0, force select lbus */
        unsigned int  reserved    : 30; /* bit[2-31]:  */
    } reg;
} ET_LUT_RAM_SEL_UNION;
#define ET_LUT_RAM_SEL_lut_ram_sel_START  (0)
#define ET_LUT_RAM_SEL_lut_ram_sel_END    (1)


/*****************************************************************************
 �ṹ��    : ET_DBG_DAT_SEL_UNION
 �ṹ˵��  : DBG_DAT_SEL �Ĵ����ṹ���塣��ַƫ����:0xD18����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      dbg_dat_sel_reg;
    struct
    {
        unsigned int  dbg_dat_sel : 1;  /* bit[0]   : ��������ѡ��
                                                      1'b0:��������ģʽ��
                                                      1'b1:ʹ��dbg��������ǿ�䣻 */
        unsigned int  reserved    : 31; /* bit[1-31]:  */
    } reg;
} ET_DBG_DAT_SEL_UNION;
#define ET_DBG_DAT_SEL_dbg_dat_sel_START  (0)
#define ET_DBG_DAT_SEL_dbg_dat_sel_END    (0)


/*****************************************************************************
 �ṹ��    : ET_DBG_DAT0_UNION
 �ṹ˵��  : DBG_DAT0 �Ĵ����ṹ���塣��ַƫ����:0xD1C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      dbg_dat0_reg;
    struct
    {
        unsigned int  dbg_log_dat : 10; /* bit[0-9]  : dbg�������ݣ�����ǿ������ת��������ֵ���޷��ţ���ά�ɲ� */
        unsigned int  reserved    : 22; /* bit[10-31]:  */
    } reg;
} ET_DBG_DAT0_UNION;
#define ET_DBG_DAT0_dbg_log_dat_START  (0)
#define ET_DBG_DAT0_dbg_log_dat_END    (9)


/*****************************************************************************
 �ṹ��    : ET_SYNC_BYPASS_UNION
 �ṹ˵��  : SYNC_BYPASS �Ĵ����ṹ���塣��ַƫ����:0xD20����ֵ:0x00000007�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      sync_bypass_reg;
    struct
    {
        unsigned int  usfd_sync_bp   : 1;  /* bit[0]   : usfd�����ӳ�ͬ����ʽ��
                                                         1'b0: ��ʱ��Ч���ȴ�dly_para_ind�߿أ���̬����ʱʹ�á�
                                                         1'b1: ������Ч������ͬ�������ھ�̬���á���Ĭ��ֵ�� */
        unsigned int  et_dly_sync_bp : 1;  /* bit[1]   : et�����ӳ�ͬ����ʽ��
                                                         1'b0: ��ʱ��Ч���ȴ�dly_para_ind�߿أ���̬����ʱʹ�á�
                                                         1'b1: ������Ч������ͬ������̬����ʱʹ�á���Ĭ��ֵ�� */
        unsigned int  tx_dly_sync_bp : 1;  /* bit[2]   : tx�����ӳ�ͬ����ʽ��
                                                         1'b0: ��ʱ��Ч���ȴ�dly_para_ind�߿أ���̬����ʱʹ�á�
                                                         1'b1: ������Ч������ͬ������̬����ʱʹ�á���Ĭ��ֵ�� */
        unsigned int  reserved       : 29; /* bit[3-31]:  */
    } reg;
} ET_SYNC_BYPASS_UNION;
#define ET_SYNC_BYPASS_usfd_sync_bp_START    (0)
#define ET_SYNC_BYPASS_usfd_sync_bp_END      (0)
#define ET_SYNC_BYPASS_et_dly_sync_bp_START  (1)
#define ET_SYNC_BYPASS_et_dly_sync_bp_END    (1)
#define ET_SYNC_BYPASS_tx_dly_sync_bp_START  (2)
#define ET_SYNC_BYPASS_tx_dly_sync_bp_END    (2)


/*****************************************************************************
 �ṹ��    : ET_CK_SWCH_CNT_UNION
 �ṹ˵��  : CK_SWCH_CNT �Ĵ����ṹ���塣��ַƫ����:0xD24����ֵ:0x00000006�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      ck_swch_cnt_reg;
    struct
    {
        unsigned int  ck_swch_cnt_num : 6;  /* bit[0-5] : RAMʱ���л���С���cycle������ά�ɲ⣬����ʹ��Ĭ��ֵ0x06 */
        unsigned int  reserved        : 26; /* bit[6-31]:  */
    } reg;
} ET_CK_SWCH_CNT_UNION;
#define ET_CK_SWCH_CNT_ck_swch_cnt_num_START  (0)
#define ET_CK_SWCH_CNT_ck_swch_cnt_num_END    (5)


/*****************************************************************************
 �ṹ��    : ET_DYM_ADJ_DISABLE_UNION
 �ṹ˵��  : DYM_ADJ_DISABLE �Ĵ����ṹ���塣��ַƫ����:0xD28����ֵ:0x0000000f�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      dym_adj_disable_reg;
    struct
    {
        unsigned int  et_dym_inc_disable : 1;  /* bit[0]   : et��̬��ʱ����
                                                             1'b0: ֧�ֶ�̬������ʱ��
                                                             1'b1: ��֧�ֶ�̬������ʱ��Ĭ��ֵ�� */
        unsigned int  et_dym_dec_disable : 1;  /* bit[1]   : et��̬��ʱ����
                                                             1'b0: ֧�ֶ�̬������ʱ��
                                                             1'b1: ��֧�ֶ�̬������ʱ��Ĭ��ֵ�� */
        unsigned int  tx_dym_inc_disable : 1;  /* bit[2]   : tx��̬��ʱ����
                                                             1'b0: ֧�ֶ�̬������ʱ��tx������ʱÿ�ζ�̬����һ�����㡣
                                                             1'b1: ��֧�ֶ�̬������ʱ��Ĭ��ֵ�� */
        unsigned int  tx_dym_dec_disable : 1;  /* bit[3]   : tx��̬��ʱ����
                                                             1'b0: ֧�ֶ�̬������ʱ��tx������ʱÿ�ζ�̬����һ�����㡣
                                                             1'b1: ��֧�ֶ�̬������ʱ��Ĭ��ֵ�� */
        unsigned int  reserved           : 28; /* bit[4-31]:  */
    } reg;
} ET_DYM_ADJ_DISABLE_UNION;
#define ET_DYM_ADJ_DISABLE_et_dym_inc_disable_START  (0)
#define ET_DYM_ADJ_DISABLE_et_dym_inc_disable_END    (0)
#define ET_DYM_ADJ_DISABLE_et_dym_dec_disable_START  (1)
#define ET_DYM_ADJ_DISABLE_et_dym_dec_disable_END    (1)
#define ET_DYM_ADJ_DISABLE_tx_dym_inc_disable_START  (2)
#define ET_DYM_ADJ_DISABLE_tx_dym_inc_disable_END    (2)
#define ET_DYM_ADJ_DISABLE_tx_dym_dec_disable_START  (3)
#define ET_DYM_ADJ_DISABLE_tx_dym_dec_disable_END    (3)


/*****************************************************************************
 �ṹ��    : ET_DYM_FRAC_SEL_UNION
 �ṹ˵��  : DYM_FRAC_SEL �Ĵ����ṹ���塣��ַƫ����:0xD2C����ֵ:0x00000003�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      dym_frac_sel_reg;
    struct
    {
        unsigned int  dym_frac_sel    : 1;  /* bit[0]   : �����ӳٶ�ʱ��Чʱ�̣�
                                                          1'b1: ż��ʱ����Ч
                                                          1'b0: ����ʱ����Ч */
        unsigned int  dym_frac_sel_bp : 1;  /* bit[1]   : �����ӳٶ�ʱ��Ч��ȷ����ʹ�ܣ�
                                                          1'b1: ������ȷ���루Ĭ��ֵ��
                                                          1'b0: �򿪾�ȷ���� */
        unsigned int  reserved        : 30; /* bit[2-31]:  */
    } reg;
} ET_DYM_FRAC_SEL_UNION;
#define ET_DYM_FRAC_SEL_dym_frac_sel_START     (0)
#define ET_DYM_FRAC_SEL_dym_frac_sel_END       (0)
#define ET_DYM_FRAC_SEL_dym_frac_sel_bp_START  (1)
#define ET_DYM_FRAC_SEL_dym_frac_sel_bp_END    (1)


/*****************************************************************************
 �ṹ��    : ET_REG_CK_SEL_UNION
 �ṹ˵��  : REG_CK_SEL �Ĵ����ṹ���塣��ַƫ����:0xD30����ֵ:0x0000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      reg_ck_sel_reg;
    struct
    {
        unsigned int  reg_ck_sel : 1;  /* bit[0]   : �Ĵ���ģ��ʱ���ſ����Σ�
                                                     1'b1: ���θ��ſأ�ʱ�ӳ�����
                                                     1'b0: �Ĵ���ģ��ʱ���Զ��ſ� */
        unsigned int  reserved   : 31; /* bit[1-31]:  */
    } reg;
} ET_REG_CK_SEL_UNION;
#define ET_REG_CK_SEL_reg_ck_sel_START  (0)
#define ET_REG_CK_SEL_reg_ck_sel_END    (0)




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

#endif /* end of bbp_et_interface.h */
