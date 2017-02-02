

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "soc_interface.h"

#ifndef __BBP_GSM_INTERFACE_H__
#define __BBP_GSM_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/***======================================================================***
                     (1/9) register_define_gbbp_addr
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31]     ������������AFCֵʹ���źţ���ƽ�źţ�����Ч���ڴ��ź�Ϊ���ڼ䣬GBBP���ڽ���AFC�����жϣ������VCO��ֵ��cpu_soft_afc_value[13:0]�ṩ��
 bit[30:14]  ����
 bit[13:0]   ������������AFCֵ����cpu_soft_afc_renew��Чʱ������ֵ�����VCO��
   UNION�ṹ:  GBBP_CPU_SOFT_AFC_VALUE_UNION */
#define GBBP_CPU_SOFT_AFC_VALUE_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x1000)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ����������������AFCֵ�������źš����ź���cpu_soft_afc_en_imiΪ��ʱ����Ч��д1�߼������㡣
   UNION�ṹ:  GBBP_CPU_SOFT_VALUE_RENEW_UNION */
#define GBBP_CPU_SOFT_VALUE_RENEW_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0x1004)

/* �Ĵ���˵����
 bit[31:19]  ����
 bit[18:16]  8PSK���Ʒ�ʽ�£�CI�о�����ѡ���źţ�����ɸѡnb-afc�������С�ڸ����ޣ�afc_valui_i��afc_value_q�����0�����������ʵֵ��
             cpu_gmsk_ci_thres[2:0]=0 C>I
             cpu_gmsk_ci_thres[2:0]=1 C>4I
             cpu_gmsk_ci_thres[2:0]=2 C>8I
             cpu_gmsk_ci_thres[2:0]=3 C>16I
             cpu_gmsk_ci_thres[2:0]=4 C>32I
             cpu_gmsk_ci_thres[2:0]=5 C>64I
             cpu_gmsk_ci_thres[2:0]=6 C>128I
             cpu_gmsk_ci_thres[2:0]=7 ���о���ֱ�������
             Ĭ��ֵ��3��
 bit[15:3]   ����
 bit[2:0]    GMSK���Ʒ�ʽ�£�CI�о�����ѡ���źţ�����ɸѡnb-afc�������С�ڸ����ޣ�afc_valui_i��afc_value_q�����0�����������ʵֵ��
             cpu_psk_ci_thres[2:0]=0 C>I
             cpu_psk_ci_thres[2:0]=1 C>4I
             cpu_psk_ci_thres[2:0]=2 C>8I
             cpu_psk_ci_thres[2:0]=3 C>16I
             cpu_psk_ci_thres[2:0]=4 C>32I
             cpu_psk_ci_thres[2:0]=5 C>64I
             cpu_psk_ci_thres[2:0]=6 C>128I
             cpu_psk_ci_thres[2:0]=7 ���о���ֱ�������
             Ĭ��ֵ��3��
   UNION�ṹ:  GBBP_CPU_CI_THRES_CFG_UNION */
#define GBBP_CPU_CI_THRES_CFG_ADDR                    (SOC_BBP_GSM_BASE_ADDR + 0x1008)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    һ�׻����ڼ���NB-AFC��NB����ѡ���źţ�
             0����ʾѡ��1��NB�����㣻
             1����ʾѡ��2��NB�����㣻
             2����ʾѡ��4��NB�����㣻
             3����ʾѡ��8��NB�����㣻
             4����ʾѡ��16��NB�����㣻
             5����ʾѡ��32��NB�����㣻
             6����ʾѡ��64��NB�����㡣
             ��DRX�ڼ��Ƽ�����2��DRX�ڼ��Ƽ�����Ϊ0��
   UNION�ṹ:  GBBP_CPU_NB_AFC_NUM_UNION */
#define GBBP_CPU_NB_AFC_NUM_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x100C)

/* �Ĵ���˵����
 bit[31]     FB-AFC�����źţ�д1��Ч���߼�������
 bit[30:16]  ����
 bit[15]     AFC��ʼֵд��ʹ�ܣ�CPUд1���߼������㡣
 bit[14]     ����
 bit[13:0]   G AFC��ʼֵ��
             ��RFCMOSʹ�þ��巽��ʱ�����ø�ֵΪ14'h1fff�����V3R2����ϵͳ����������������ʱ��ʹ��ԭ��������ֵ��
   UNION�ṹ:  GBBP_CPU_AFC_CFG_UNION */
#define GBBP_CPU_AFC_CFG_ADDR                         (SOC_BBP_GSM_BASE_ADDR + 0x1010)

/* �Ĵ���˵����
 bit[31:19]  ����
 bit[18:0]   �ϱ���afcʵ������ۼ�ֵ��ֱ���ɳ��ۼ�ģ������������á�
   UNION�ṹ:  GBBP_AFC_VALUE_I_CPU_UNION */
#define GBBP_AFC_VALUE_I_CPU_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x1014)

/* �Ĵ���˵����
 bit[31:19]  ����
 bit[18:0]   �ϱ���afc�鲿����ۼ�ֵ��ֱ���ɳ��ۼ�ģ������������á�
   UNION�ṹ:  GBBP_AFC_VALUE_Q_CPU_UNION */
#define GBBP_AFC_VALUE_Q_CPU_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x1018)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    0��ʾʹ��10bit��PDMת��ģ�飻
             1��ʾʹ��12bit��PDMת��ģ�飻
             2��ʾʹ��14bit��PDMת��ģ�顣
   UNION�ṹ:  GBBP_CPU_AFC_PWM_WIDTH_SEL_UNION */
#define GBBP_CPU_AFC_PWM_WIDTH_SEL_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x101C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��ʾ���¿�ʼͳ��NB-AFC��NB-BURST������cpuд1���߼������㡣
             ��ʱ�������ǰ�ۼ�NB������Ӧ��NB-AFC�˲�ֵ�������ȸı�cpu_nb_afc_num�����ô�ֵΪ1��
   UNION�ṹ:  GBBP_CPU_NB_AFC_NUM_CLR_UNION */
#define GBBP_CPU_NB_AFC_NUM_CLR_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x1020)

/* �Ĵ���˵����
 bit[31:21]  ����
 bit[20:16]  ����FB-AFC�о����ܵ�FB���������䷶ΧΪ��17~31
             Ĭ������Ϊ��22
 bit[15:0]   ����
   UNION�ṹ:  GBBP_CPU_FB_KP_KINT_UNION */
#define GBBP_CPU_FB_KP_KINT_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x1024)

/* �Ĵ���˵����
 bit[31:27]  ����
 bit[26:16]  �ͺ�FB1215QB��timebase��FNģ2048������������Χ��0~2047�����á�
 bit[15:13]  ����
 bit[12:0]   �ͺ�FB1215QB��timebase��QB�����������á�
   UNION�ṹ:  GBBP_FB_TIMEBASE_RPT_UNION */
#define GBBP_FB_TIMEBASE_RPT_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x1028)

/* �Ĵ���˵����
 bit[31:27]  ����
 bit[26:16]  FB����֡λ��T1�������ϱ���
 bit[15:13]  ����
 bit[12:8]   FB����֡λ��T2�������ϱ���
 bit[7:6]    ����
 bit[5:0]    FB����֡λ��T3�������ϱ���
   UNION�ṹ:  GBBP_FB_FN_RPT_UNION */
#define GBBP_FB_FN_RPT_ADDR                           (SOC_BBP_GSM_BASE_ADDR + 0x102C)

/* �Ĵ���˵����
 bit[31:29]  ����
 bit[28:12]  FB�������ķ��Ÿ�������ֵ��
             ȱʡֵΪ17'd13906����Ӧ11֡+1ʱ϶������������ʱ�䳤�ȴ��ڸ�ֵʱ��FB����������
             ע��13906=11*1250+156
 bit[11:6]   ����
 bit[5:4]    SBͬ��ʧ�ܴ������ޡ�
             2'd0��ʹ�õ�����ֵΪ1��
             2'd1��ʹ�õ�����ֵΪ2��
             2'd2��ʹ�õ�����ֵΪ3��
             ��������Ч��
             ȱʡֵΪ2'd1��
 bit[3:2]    ����
 bit[1:0]    FBͬ��ʧ�ܴ������ޡ�
             2'd0��ʹ�õ�����ֵΪ1��
             2'd1��ʹ�õ�����ֵΪ2��
             2'd2��ʹ�õ�����ֵΪ3��
             2'd3��ʹ�õ�����ֵΪ4��
             ȱʡֵΪ2'd1��
   UNION�ṹ:  GBBP_CPU_FB_TIMES_THRES_UNION */
#define GBBP_CPU_FB_TIMES_THRES_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x1030)

/* �Ĵ���˵����
 bit[31:23]  ����
 bit[22:12]  FB�����ɹ������ޣ���FB�����õ������������ֵ���ڸ�����ʱ������Ϊ�����ɹ���ȱʡֵΪ512��
 bit[11:0]   ����
   UNION�ṹ:  GBBP_CPU_FB_ENERG_THRES_UNION */
#define GBBP_CPU_FB_ENERG_THRES_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x1034)

/* �Ĵ���˵����
 bit[31:16]  AFC�����16����VCTXO�Ŀ��Ƶ�ѹ�ź�
 bit[15:14]  ����
 bit[13:0]   AFC�����VCTXO���Ƶ�ѹ��
   UNION�ṹ:  GBBP_AFC_RPT_UNION */
#define GBBP_AFC_RPT_ADDR                             (SOC_BBP_GSM_BASE_ADDR + 0x1038)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  SB����λ�������FBλ�õ�ƫ����
 bit[15:13]  ����
 bit[12:0]   FB�����õ���FBʱ϶ͷλ�ã������gtc_timebase��λ�á�
   UNION�ṹ:  GBBP_FB_RPT1_UNION */
#define GBBP_FB_RPT1_ADDR                             (SOC_BBP_GSM_BASE_ADDR + 0x103C)

/* �Ĵ���˵����
 bit[31:19]  ����
 bit[18:0]   ����FB�������������ֵ�������á�
   UNION�ṹ:  GBBP_FB_RPT2_UNION */
#define GBBP_FB_RPT2_ADDR                             (SOC_BBP_GSM_BASE_ADDR + 0x1040)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  ����״̬���ϱ��źţ�
             0��Idle State��
             1��FB����״̬��
             2��AFC�ж�״̬��
             3��SB����״̬��
 bit[15:13]  ����
 bit[12:0]   SB�����������ֵ�����timebase��λ�ã���SB����ʧ�ܣ����ϱ�ֵ��Ч��
   UNION�ṹ:  GBBP_SB_POS_RPT1_UNION */
#define GBBP_SB_POS_RPT1_ADDR                         (SOC_BBP_GSM_BASE_ADDR + 0x1044)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:0]   SB��������ֵ�����ֵ�������á�
   UNION�ṹ:  GBBP_SB_SQUARE_RPT1_UNION */
#define GBBP_SB_SQUARE_RPT1_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x1048)

/* �Ĵ���˵����
 bit[31:13]  ����
 bit[12:0]   SB���������δ�ֵ�����timebase��λ�á�
   UNION�ṹ:  GBBP_SB_POS_RPT2_UNION */
#define GBBP_SB_POS_RPT2_ADDR                         (SOC_BBP_GSM_BASE_ADDR + 0x104C)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:0]   SB��������ֵ�Ĵδ�ֵ�������á�
   UNION�ṹ:  GBBP_SB_SQUARE_RPT2_UNION */
#define GBBP_SB_SQUARE_RPT2_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x1050)

/* �Ĵ���˵����
 bit[31:13]  ����
 bit[12:0]   SB��������������ֵ�����timebase��λ�á�
   UNION�ṹ:  GBBP_SB_POS_RPT3_UNION */
#define GBBP_SB_POS_RPT3_ADDR                         (SOC_BBP_GSM_BASE_ADDR + 0x1054)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:0]   SB��������ֵ�ĵ�����ֵ�������á�
   UNION�ṹ:  GBBP_SB_SQUARE_RPT3_UNION */
#define GBBP_SB_SQUARE_RPT3_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x1058)

/* �Ĵ���˵����
 bit[31:19]  ����
 bit[18:16]  
 bit[15:12]  ����
 bit[11:8]   �����ж�״̬������Ӧ�����жϵ�ԭ�򡣴��źŵ�int_srch_sync_cpu��Ч����Ч�������á���bit�������£�
             C01�������̰汾��
             4'd0����������������
             4'd1��FBδͬ����
             4'd2��AFCδ������
             4'd3��SB�������
             4'd5�����������ģʽ���ã���3'b000��
             4'd6����������������������ʹ���ź�gsp_srch_en��͡�
             111�����Ż����̰汾��
             4'd1��FBδͬ����
             4'd7��111����ģʽ�Ż��£���FB-AFC�����£�SB����ʧ�ܳ������ޣ���������ʧ�ܣ�
             4'd8��111����ģʽ�Ż��£���FB-AFCδ�����£�FB-AFC���������������ޣ���������ʧ�ܣ�
             4'd9��111����ģʽ�Ż��£����SB����ɹ���BSICֵ��ͬ��SB����ɹ������������ޣ���������ʧ�ܣ�
             �����á�
 bit[7:6]    ����
 bit[5:4]    ���ۼ�ģ����������״̬�ϱ��������á�
 bit[3:0]    ���ۼ�״̬�ϱ���
             4'd0������״̬��
             4'd1��ͬ������״̬��
             4'd2��NBä��⼰ͬ��λ�ø��£�
             4'd3��Ԥ�˲���
             4'd4��TVB��������
             4'd5��VALPP���С�
             �����á�
   UNION�ṹ:  GBBP_STATE_RPT_UNION */
#define GBBP_STATE_RPT_ADDR                           (SOC_BBP_GSM_BASE_ADDR + 0x105C)

/* �Ĵ���˵����
 bit[31]     ��ǰ����С�������ϱ���
             0����ʾ����С����
             1����ʾ������
 bit[30:28]  ��������ʱ��gsp_srch_mod�ϱ���
 bit[27:19]  ����
 bit[18:16]  �����ж�ʱ��gsp_srch_mod�ϱ���
 bit[15:13]  ����
 bit[12:0]   �����ж�����gtc_timebase�ϱ���
   UNION�ṹ:  GBBP_SRCH_QB_RPT_UNION */
#define GBBP_SRCH_QB_RPT_ADDR                         (SOC_BBP_GSM_BASE_ADDR + 0x1064)

/* �Ĵ���˵����
 bit[31:27]  ����
 bit[26:16]  �����ж�����λ�õ�gtc_fn_high�ϱ���
 bit[15:11]  ����
 bit[10:0]   �����ж�����λ�õ�gtc_fn_low�ϱ���
   UNION�ṹ:  GBBP_SRCH_FN_RPT_UNION */
#define GBBP_SRCH_FN_RPT_ADDR                         (SOC_BBP_GSM_BASE_ADDR + 0x106C)

/* �Ĵ���˵����
 bit[31:6]   ����
 bit[5:0]    001����ģʽ�£�SB��ǰ���շ��ŵĸ���������SB֮ǰ�����cpu_sb_advance_len�����ţ�����0~34��
   UNION�ṹ:  GBBP_SB_ADVANCE_LEN_CFG_UNION */
#define GBBP_SB_ADVANCE_LEN_CFG_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x1070)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  �����ж�ʱ��Ƶ����Ϣ�ϱ���
 bit[15:12]  ����
 bit[11:0]   ��������ʱ��Ƶ����Ϣ�ϱ���
   UNION�ṹ:  GBBP_SRCH_FRQ_RPT_UNION */
#define GBBP_SRCH_FRQ_RPT_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x107C)

/* �Ĵ���˵����
 bit[31]     NB-AFCһ�׻�����׻�״̬�ϱ���
             0����ʾ��ǰ����һ�׻���
             1����ʾ��ǰ���ڶ��׻���
 bit[30:0]   һ�׻���ǰNB-AFC��·�˲��ۼ������ϱ�ֵ
   UNION�ṹ:  GBBP_AFC_LOOP1_RPT_UNION */
#define GBBP_AFC_LOOP1_RPT_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x1078)

/* �Ĵ���˵����
 bit[31]     ����
 bit[30:0]   �ϵ��һ�׻�NB-AFC��·�˲��ۼ���������ֵ��
             ������cpu_afc_init_enΪ1����Ч��
             
   UNION�ṹ:  GBBP_CPU_AFC_LOOP1_CFG_UNION */
#define GBBP_CPU_AFC_LOOP1_CFG_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x1080)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  ����Ƶƫ״̬�ϱ���
 bit[15:0]   ����Ƶƫ������ϱ���
   UNION�ṹ:  GBBP_NCELL_NCO_RPT_UNION */
#define GBBP_NCELL_NCO_RPT_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x1084)

/* �Ĵ���˵����
 bit[31:26]  ����
 bit[25:16]  NB-AFC�㷨��λ����ֵ�ο����ޣ�����ֵ760��
 bit[15:10]  ����
 bit[9:0]    NB-AFC�㷨��λ����ֵ�ο����ޣ�����ֵ300��
   UNION�ṹ:  GBBP_AFC_PHASE_THRESHOLD_CFG_UNION */
#define GBBP_AFC_PHASE_THRESHOLD_CFG_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x108C)

/* �Ĵ���˵����
 bit[31:29]  ����
 bit[28:16]  NB-AFC�㷨ϵ��fcut�����ֵ������������˲������λ����ֵ������λ����ֵ�Ĳο����ޣ���ϵ��fcut��ֵ�͵��ڴ����ֵ������ֵ1024��
 bit[15:13]  ����
 bit[12:0]   NB-AFC�㷨ϵ��fcut����Сֵ������������˲������λ����ֵС����λ����ֵ�ο����ޣ���ϵ��fcut��ֵ�͵��ڴ���Сֵ������ֵ51��
   UNION�ṹ:  GBBP_AFC_FCUT_THRESHOLD_CFG_UNION */
#define GBBP_AFC_FCUT_THRESHOLD_CFG_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x1090)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    NB-AFC�㷨���˲�ϵ��ѡ��
             0��1/64��
             1��1/32��
             2��1/16��
             3��1/8��
   UNION�ṹ:  GBBP_AFC_ALPHA_SEL_UNION */
#define GBBP_AFC_ALPHA_SEL_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x1094)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17]     NB���ʹ��״̬�ϱ���
 bit[16]     ����ʹ��״̬�ϱ���
 bit[15:5]   ����
 bit[4]      д1��ʾ����TOA ALPHA�����ۼ�ֵ�������źţ��߼������㡣
 bit[3]      д1��ʾ����gsp_nb_afc_en�����źţ��߼������㡣
 bit[2]      д1��ʾ����gsp_agc_en�����źţ��߼������㡣
 bit[1]      д1��ʾ����gsp_nb_demod_en�����źţ��߼������㡣
 bit[0]      д1��ʾ����gsp_srch_en�����źţ��߼������㡣
   UNION�ṹ:  GBBP_CPU_SRCH_EN_CLR_UNION */
#define GBBP_CPU_SRCH_EN_CLR_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x1124)

/* �Ĵ���˵����
 bit[31:26]  ����
 bit[25:24]  NB���Ʒ�ʽ��һ���о�����ϱ���
 bit[23:18]  ����
 bit[17:16]  NB���Ʒ�ʽ�ϱ���
             0��GMSK���ƣ�
             1��8PSK���ƣ�
             2��DummyBurst��
 bit[15:13]  ����
 bit[12:0]   NBλ�ø����ϱ����Ƕ�ȡʱ�����һ�����BURST��λ�ã��������timebase��CPU������֡�ж��ж�ȡ������2QB��
   UNION�ṹ:  GBBP_NB_POS_RPT_UNION */
#define GBBP_NB_POS_RPT_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x1060)

/* �Ĵ���˵����
 bit[31]     1��ʾ���ŵ������Ż����á�
 bit[30:2]   ����
 bit[1:0]    8psk����������PSP_EN�Ĳ���alpha��
             0����Ӧ��ֵΪ8��
             1����Ӧ��ֵΪ16��
             2����Ӧ��ֵΪ24��
             3����Ч��
             Ĭ��ֵΪ1��
   UNION�ṹ:  GBBP_CPU_8PSK_PSP_ALPHA_PARA_UNION */
#define GBBP_CPU_8PSK_PSP_ALPHA_PARA_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x1068)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    alpha�˲�ϵ��ѡ��
             0����ʾѡ��ϵ��Ϊ1/2��
             1����ʾѡ��ϵ��Ϊ1/4��
             2����ʾѡ��ϵ��Ϊ1/8��
             3����ʾѡ��ϵ��Ϊ1/16��
             4����ʾѡ��ϵ��Ϊ1/32��
   UNION�ṹ:  GBBP_CPU_TOA_ALPHA_PARA_UNION */
#define GBBP_CPU_TOA_ALPHA_PARA_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x1074)

/* �Ĵ���˵����
 bit[31:19]  ����
 bit[18:16]  �׻��˲��о����ޣ����������������ı������������ޣ��������׻��˲�������NB�����÷�Χʱ1~7����ʾ1~7��������SB���̶�����Ϊ5����ʾ5����
 bit[15:8]   ����
 bit[7]      1��ʾ��·�ŵ������Ż����ܣ�
             0��ʾ���ŵ������Ż����ܡ�
 bit[6]      valpp����PSP����ʹ���źţ�1��Ч��
 bit[5:3]    ����
 bit[2:0]    �ŵ������Ż�����ϵ�����ӣ�ȡֵ1~5��Ĭ������2��
   UNION�ṹ:  GBBP_CPU_CH_EST_OPT_UNION */
#define GBBP_CPU_CH_EST_OPT_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x1088)

/* �Ĵ���˵����
 bit[31:16]  bit16~bit31��ʾ��ʱ϶�ĵ�һ���ڶ������������ĸ�ʱ϶���ĸ�BURST����ä����־�ϱ���0��ʶNB��1��ʶDB��
 bit[15:0]   bit0~bit15��ʾ��ʱ϶�ĵ�һ���ڶ������������ĸ�ʱ϶���ĸ�BURST����ä����־�ϱ���0��ʶGMSK��1��ʶ8PSK��
   UNION�ṹ:  GBBP_NB_MOD_TYPE_RPT_UNION */
#define GBBP_NB_MOD_TYPE_RPT_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x1098)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  bit16~bit23��ʾ��ʱ϶�ĵ��壬����ʱ϶������BURST���ͱ�־�ϱ���0��ʶNB��1��ʶDB��
 bit[15:8]   ����
 bit[7:0]    bit0~bit7��ʾ��ʱ϶�ĵ��壬����ʱ϶������BURST����ä����־�ϱ���0��ʶGMSK��1��ʶ8PSK��
   UNION�ṹ:  GBBP_NB_BURST_TYPE_RPT_UNION */
#define GBBP_NB_BURST_TYPE_RPT_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x10BC)

/* �Ĵ���˵����
 bit[31:19]  ����
 bit[18:0]   ��һ����һ��BURST���ǰ�ֲ�Cֵ�ϱ��������á�
   UNION�ṹ:  GBBP_GROSS_CARRIER_ENERGY1_UNION */
#define GBBP_GROSS_CARRIER_ENERGY1_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x109C)

/* �Ĵ���˵����
 bit[31:19]  ����
 bit[18:0]   ��һ����һ��BURST���ǰ�ֲ�Iֵ�ϱ��������á�
   UNION�ṹ:  GBBP_GROSS_INTERFERE_ENERGY1_UNION */
#define GBBP_GROSS_INTERFERE_ENERGY1_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x10A0)

/* �Ĵ���˵����
 bit[31:19]  ����
 bit[18:0]   �ڶ�����һ��BURST���ǰ�ֲ�Cֵ�ϱ��������á�
   UNION�ṹ:  GBBP_GROSS_CARRIER_ENERGY2_UNION */
#define GBBP_GROSS_CARRIER_ENERGY2_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x10A4)

/* �Ĵ���˵����
 bit[31:19]  ����
 bit[18:0]   �ڶ�����һ��BURST���ǰ�ֲ�Iֵ�ϱ��������á�
   UNION�ṹ:  GBBP_GROSS_INTERFERE_ENERGY2_UNION */
#define GBBP_GROSS_INTERFERE_ENERGY2_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x10A8)

/* �Ĵ���˵����
 bit[31:19]  ����
 bit[18:0]   ��������һ��BURST���ǰ�ֲ�Cֵ�ϱ��������á�
   UNION�ṹ:  GBBP_GROSS_CARRIER_ENERGY3_UNION */
#define GBBP_GROSS_CARRIER_ENERGY3_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x10AC)

/* �Ĵ���˵����
 bit[31:19]  ����
 bit[18:0]   ��������һ��BURST���ǰ�ֲ�Iֵ�ϱ��������á�
   UNION�ṹ:  GBBP_GROSS_INTERFERE_ENERGY3_UNION */
#define GBBP_GROSS_INTERFERE_ENERGY3_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x10B0)

/* �Ĵ���˵����
 bit[31:19]  ����
 bit[18:0]   ���Ľ���һ��BURST���ǰ�ֲ�Cֵ�ϱ��������á�
   UNION�ṹ:  GBBP_GROSS_CARRIER_ENERGY4_UNION */
#define GBBP_GROSS_CARRIER_ENERGY4_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x10B4)

/* �Ĵ���˵����
 bit[31:19]  ����
 bit[18:0]   ���Ľ���һ��BURST���ǰ�ֲ�Iֵ�ϱ��������á�
   UNION�ṹ:  GBBP_GROSS_INTERFERE_ENERGY4_UNION */
#define GBBP_GROSS_INTERFERE_ENERGY4_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x10B8)

/* �Ĵ���˵����
   ��      ������һ����һ��BURST���ǰ���BURST��MQƽ���ķ���ֵ�ϱ�����ӦBURSTΪDummyBurst�����ϱ���Ϣ��׼ȷ������ʹ�á�
   UNION�ṹ ���� */
#define GBBP_MQ1_FENZI1_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x10C0)

/* �Ĵ���˵����
   ��      ������һ����һ��BURST���ǰ���BURST��MQƽ���ķ�ĸֵ�ϱ�����ӦBURSTΪDummyBurst�����ϱ���Ϣ��׼ȷ������ʹ�á�
   UNION�ṹ ���� */
#define GBBP_MQ1_FENMU1_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x10C4)

/* �Ĵ���˵����
   ��      ������һ����һ��BURST�������BURST��MQƽ���ķ���ֵ�ϱ�����ӦBURSTΪDummyBurst�����ϱ���Ϣ��׼ȷ������ʹ�á�
   UNION�ṹ ���� */
#define GBBP_MQ2_FENZI1_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x10C8)

/* �Ĵ���˵����
   ��      ������һ����һ��BURST�������BURST��MQƽ���ķ�ĸֵ�ϱ�����ӦBURSTΪDummyBurst�����ϱ���Ϣ��׼ȷ������ʹ�á�
   UNION�ṹ ���� */
#define GBBP_MQ2_FENMU1_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x10CC)

/* �Ĵ���˵����
   ��      �����ڶ�����һ��BURST���ǰ���BURST��MQƽ���ķ���ֵ�ϱ�����ӦBURSTΪDummyBurst�����ϱ���Ϣ��׼ȷ������ʹ�á�
   UNION�ṹ ���� */
#define GBBP_MQ1_FENZI2_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x10D0)

/* �Ĵ���˵����
   ��      �����ڶ�����һ��BURST���ǰ���BURST��MQƽ���ķ�ĸֵ�ϱ�����ӦBURSTΪDummyBurst�����ϱ���Ϣ��׼ȷ������ʹ�á�
   UNION�ṹ ���� */
#define GBBP_MQ1_FENMU2_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x10D4)

/* �Ĵ���˵����
   ��      �����ڶ�����һ��BURST�������BURST��MQƽ���ķ���ֵ�ϱ�����ӦBURSTΪDummyBurst�����ϱ���Ϣ��׼ȷ������ʹ�á�
   UNION�ṹ ���� */
#define GBBP_MQ2_FENZI2_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x10D8)

/* �Ĵ���˵����
   ��      �����ڶ�����һ��BURST�������BURST��MQƽ���ķ�ĸֵ�ϱ�����ӦBURSTΪDummyBurst�����ϱ���Ϣ��׼ȷ������ʹ�á�
   UNION�ṹ ���� */
#define GBBP_MQ2_FENMU2_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x10DC)

/* �Ĵ���˵����
   ��      ������������һ��BURST���ǰ���BURST��MQƽ���ķ���ֵ�ϱ�����ӦBURSTΪDummyBurst�����ϱ���Ϣ��׼ȷ������ʹ�á�
   UNION�ṹ ���� */
#define GBBP_MQ1_FENZI3_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x10E0)

/* �Ĵ���˵����
   ��      ������������һ��BURST���ǰ���BURST��MQƽ���ķ�ĸֵ�ϱ�����ӦBURSTΪDummyBurst�����ϱ���Ϣ��׼ȷ������ʹ�á�
   UNION�ṹ ���� */
#define GBBP_MQ1_FENMU3_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x10E4)

/* �Ĵ���˵����
   ��      ������������һ��BURST�������BURST��MQƽ���ķ���ֵ�ϱ�����ӦBURSTΪDummyBurst�����ϱ���Ϣ��׼ȷ������ʹ�á�
   UNION�ṹ ���� */
#define GBBP_MQ2_FENZI3_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x10E8)

/* �Ĵ���˵����
   ��      ������������һ��BURST�������BURST��MQƽ���ķ�ĸֵ�ϱ�����ӦBURSTΪDummyBurst�����ϱ���Ϣ��׼ȷ������ʹ�á�
   UNION�ṹ ���� */
#define GBBP_MQ2_FENMU3_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x10EC)

/* �Ĵ���˵����
   ��      �������Ľ���һ��BURST���ǰ���BURST��MQƽ���ķ���ֵ�ϱ�����ӦBURSTΪDummyBurst�����ϱ���Ϣ��׼ȷ������ʹ�á�
   UNION�ṹ ���� */
#define GBBP_MQ1_FENZI4_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x10F0)

/* �Ĵ���˵����
   ��      �������Ľ���һ��BURST���ǰ���BURST��MQƽ���ķ�ĸֵ�ϱ�����ӦBURSTΪDummyBurst�����ϱ���Ϣ��׼ȷ������ʹ�á�
   UNION�ṹ ���� */
#define GBBP_MQ1_FENMU4_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x10F4)

/* �Ĵ���˵����
   ��      �������Ľ���һ��BURST�������BURST��MQƽ���ķ���ֵ�ϱ�����ӦBURSTΪDummyBurst�����ϱ���Ϣ��׼ȷ������ʹ�á�
   UNION�ṹ ���� */
#define GBBP_MQ2_FENZI4_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x10F8)

/* �Ĵ���˵����
   ��      �������Ľ���һ��BURST�������BURST��MQƽ���ķ�ĸֵ�ϱ�����ӦBURSTΪDummyBurst�����ϱ���Ϣ��׼ȷ������ʹ�á�
   UNION�ṹ ���� */
#define GBBP_MQ2_FENMU4_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x10FC)

/* �Ĵ���˵����
 bit[31]     ����
 bit[30:0]   ��ȡʱ��ǰ���burst��Ӧ���ز�����ֵ���޷�������
   UNION�ṹ:  GBBP_VALPP_CARRIER_ENERGY0_UNION */
#define GBBP_VALPP_CARRIER_ENERGY0_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x1100)

/* �Ĵ���˵����
 bit[31:26]  ����
 bit[25:0]   ��ȡʱ��ǰ���burst��Ӧ�ĸ�������ֵ���޷�������
   UNION�ṹ:  GBBP_VALPP_INTERFERE_ENERGY0_UNION */
#define GBBP_VALPP_INTERFERE_ENERGY0_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x1150)

/* �Ĵ���˵����
 bit[31]     ��ȡʱ����������Ϣ��Ч��־�������һ��NB���ʱ���ñ�־��1,CPU��ȡ���BURST����ϱ���Ϣ��Ӧ��ͨ��bit30�Ը�bit���㣬ָʾ����Ϣ�Ѿ���ȡ��
 bit[30]     ��demod_info_valid_flag0���㡣д1���㡣
 bit[29:28]  ��ȡʱ��ǰ�����BURST��Ӧ��һ���о��ĵ��Ʒ�ʽ��
             0��GMSK���ƣ�
             1��8PSK���ƣ�
             2��DummyBurst��
             �üĴ�������ʹ�á�
 bit[27:25]  ����
 bit[24]     ��ȡʱ�����burst�Ƿ�Ϊ�Ƿ�����ָʾ��1��ʾ�Ƿ�������0��ʾ��������Ĭ��ֵΪ0����ֵ��PHYͨ��GTCָ������������BBP��ʱ������жϴ������ϱ���
 bit[23]     ����
 bit[22:20]  ��ȡʱ��������burst��Ӧ��ʱ϶�ţ���ʱ϶����PHYͨ��GTCָ������������BBP��ʱ������жϴ������ϱ���
 bit[19:16]  ��ȡʱ��������burst��Ӧ��NBλ�õ��������ǲ����ʾ���з�������������ʾ��ǰ������������ʾ����������Χ��-4~+4��
 bit[15:14]  ��ȡʱ�����BURST�ĵ��Ʒ�ʽ��
             0��GSKM��
             1��8PSK��
             2��DummyBurst��
 bit[13:12]  ����
 bit[11:8]   SAIC��TOA�徶Cֵ���ֵ��Ӧ���ţ�
             ȡֵ��Χ0~4��
 bit[7:6]    ����
 bit[5:0]    ���6��ʱ϶��TOA����ѡ������
             bit0�����һ��burst��ѡ������
             bit1���ڶ���burst��ѡ������
             �����������ơ�
             0��ʾѡ��ǰ������ţ�1��ʾѡ��������ţ���Ҫ��nb_pos_adj�Ļ����ϼ���2QB��
   UNION�ṹ:  GBBP_VALPP_DEM_TYPE_TOA0_UNION */
#define GBBP_VALPP_DEM_TYPE_TOA0_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x1104)

/* �Ĵ���˵����
 bit[31]     ����
 bit[30:0]   ��ȡʱ��ǰ�ڶ���burst��Ӧ���ز�����ֵ���޷�������
   UNION�ṹ:  GBBP_VALPP_CARRIER_ENERGY1_UNION */
#define GBBP_VALPP_CARRIER_ENERGY1_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x1108)

/* �Ĵ���˵����
 bit[31:26]  ����
 bit[25:0]   ��ȡʱ��ǰ�ڶ���burst��Ӧ�ĸ�������ֵ���޷�������
   UNION�ṹ:  GBBP_VALPP_INTERFERE_ENERGY1_UNION */
#define GBBP_VALPP_INTERFERE_ENERGY1_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x1154)

/* �Ĵ���˵����
 bit[31]     ��ȡʱ�̵ڶ��������Ϣ��Ч��־�������һ��NB���ʱ���ñ�־��1,CPU��ȡ���BURST����ϱ���Ϣ��Ӧ��ͨ��дbit30�Ը�bit���㣬ָʾ����Ϣ�Ѿ���ȡ��
 bit[30]     ��demod_info_valid_flag1���㡣д1���㡣
 bit[29:28]  ��ȡʱ��ǰ�ĵڶ���BURST��Ӧ��һ���о��ĵ��Ʒ�ʽ��
             0��GMSK���ƣ�
             1��8PSK���ƣ�
             2��DummyBurst��
             �üĴ�������ʹ�á�
 bit[27:25]  ����
 bit[24]     ��ȡʱ�̵ڶ���burst�Ƿ�Ϊ�Ƿ�����ָʾ��1��ʾ�Ƿ�������0��ʾ��������Ĭ��ֵΪ0����ֵ��PHYͨ��GTCָ������������BBP��ʱ������жϴ������ϱ���
 bit[23]     ����
 bit[22:20]  ��ȡʱ�̵ڶ������burst��Ӧ��ʱ϶�ţ���ʱ϶����PHYͨ��GTCָ������������BBP��ʱ������жϴ������ϱ���
 bit[19:16]  ��ȡʱ�̵ڶ������burst��Ӧ��NBλ�õ��������ǲ����ʾ���з�������������ʾ��ǰ������������ʾ����������Χ��-4~+4��
 bit[15:14]  ��ȡʱ�̵ڶ���BURST�ĵ��Ʒ�ʽ��
             0��GSKM��
             1��8PSK��
             2��DummyBurst��
 bit[13:0]   ����
   UNION�ṹ:  GBBP_VALPP_DEM_TYPE_TOA1_UNION */
#define GBBP_VALPP_DEM_TYPE_TOA1_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x110C)

/* �Ĵ���˵����
 bit[31]     ����
 bit[30:0]   ��ȡʱ��ǰ������burst��Ӧ���ز�����ֵ���޷�������
   UNION�ṹ:  GBBP_VALPP_CARRIER_ENERGY2_UNION */
#define GBBP_VALPP_CARRIER_ENERGY2_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x1110)

/* �Ĵ���˵����
 bit[31:26]  ����
 bit[25:0]   ��ȡʱ��ǰ������burst��Ӧ�ĸ�������ֵ���޷�������
   UNION�ṹ:  GBBP_VALPP_INTERFERE_ENERGY2_UNION */
#define GBBP_VALPP_INTERFERE_ENERGY2_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x1158)

/* �Ĵ���˵����
 bit[31]     ��ȡʱ�̵����������Ϣ��Ч��־�������һ��NB���ʱ���ñ�־��1,CPU��ȡ���BURST����ϱ���Ϣ��Ӧ��ͨ��дbit30�Ը�bit���㣬ָʾ����Ϣ�Ѿ���ȡ��
 bit[30]     ��demod_info_valid_flag2���㡣д1���㡣
 bit[29:28]  ��ȡʱ��ǰ�ĵ�����BURST��Ӧ��һ���о��ĵ��Ʒ�ʽ��
             0��GMSK���ƣ�
             1��8PSK���ƣ�
             2��DummyBurst��
             �üĴ�������ʹ�á�
 bit[27:25]  ����
 bit[24]     ��ȡʱ�̵�����burst�Ƿ�Ϊ�Ƿ�����ָʾ��1��ʾ�Ƿ�������0��ʾ��������Ĭ��ֵΪ0����ֵ��PHYͨ��GTCָ������������BBP��ʱ������жϴ������ϱ���
 bit[23]     ����
 bit[22:20]  ��ȡʱ�̵��������burst��Ӧ��ʱ϶�ţ���ʱ϶����PHYͨ��GTCָ������������BBP��ʱ������жϴ������ϱ���
 bit[19:16]  ��ȡʱ�̵��������burst��Ӧ��NBλ�õ��������ǲ����ʾ���з�������������ʾ��ǰ������������ʾ����������Χ��-4~+4��
 bit[15:14]  ��ȡʱ�̵�����BURST�ĵ��Ʒ�ʽ��
             0��GSKM��
             1��8PSK��
             2��DummyBurst��
 bit[13:0]   ����
   UNION�ṹ:  GBBP_VALPP_DEM_TYPE_TOA2_UNION */
#define GBBP_VALPP_DEM_TYPE_TOA2_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x1114)

/* �Ĵ���˵����
 bit[31]     ����
 bit[30:0]   ��ȡʱ��ǰ���Ľ�burst��Ӧ���ز�����ֵ���޷�������
   UNION�ṹ:  GBBP_VALPP_CARRIER_ENERGY3_UNION */
#define GBBP_VALPP_CARRIER_ENERGY3_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x1118)

/* �Ĵ���˵����
 bit[31:26]  ����
 bit[25:0]   ��ȡʱ��ǰ���Ľ�burst��Ӧ�ĸ�������ֵ���޷�������
   UNION�ṹ:  GBBP_VALPP_INTERFERE_ENERGY3_UNION */
#define GBBP_VALPP_INTERFERE_ENERGY3_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x115C)

/* �Ĵ���˵����
 bit[31]     ��ȡʱ�̵��Ľ������Ϣ��Ч��־�������һ��NB���ʱ���ñ�־��1,CPU��ȡ���BURST����ϱ���Ϣ��Ӧ��дbit30�Ը�bit���㣬ָʾ����Ϣ�Ѿ���ȡ��
 bit[30]     ��demod_info_valid_flag3���㡣д1���㡣
 bit[29:28]  ��ȡʱ��ǰ�ĵ��Ľ�BURST��Ӧ��һ���о��ĵ��Ʒ�ʽ��
             0��GMSK���ƣ�
             1��8PSK���ƣ�
             2��DummyBurst��
             �üĴ�������ʹ�á�
 bit[27:25]  ����
 bit[24]     ��ȡʱ�̵��Ľ�burst�Ƿ�Ϊ�Ƿ�����ָʾ��1��ʾ�Ƿ�������0��ʾ��������Ĭ��ֵΪ0����ֵ��PHYͨ��GTCָ������������BBP��ʱ������жϴ������ϱ���
 bit[23]     ����
 bit[22:20]  ��ȡʱ�̵��Ľ����burst��Ӧ��ʱ϶�ţ���ʱ϶����PHYͨ��GTCָ������������BBP��ʱ������жϴ������ϱ���
 bit[19:16]  ��ȡʱ�̵��Ľ����burst��Ӧ��NBλ�õ��������ǲ����ʾ���з�������������ʾ��ǰ������������ʾ����������Χ��-4~+4��
 bit[15:14]  ��ȡʱ�̵��Ľ�BURST�ĵ��Ʒ�ʽ��
             0��GSKM��
             1��8PSK��
             2��DummyBurst��
 bit[13:0]   ����
   UNION�ṹ:  GBBP_VALPP_DEM_TYPE_TOA3_UNION */
#define GBBP_VALPP_DEM_TYPE_TOA3_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x111C)

/* �Ĵ���˵����
 bit[31:17]  ����
 bit[16]     HARQ����ǰ����λ��ָ�ģʽ����
             0:���ս����̬λ�����ָ�����
             1:���������ֵλ��ָ�����
             
 bit[15:2]   ����
 bit[1:0]    �����̬λ������
             2��d0����̬����λ��Ϊ0
             2��d1����̬����λ��Ϊ1
             2��d2����̬����λ��Ϊ2
             ����������
             
   UNION�ṹ:  GBBP_CPU_DEM_WIDTH_CFG_UNION */
#define GBBP_CPU_DEM_WIDTH_CFG_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x1120)

/* �Ĵ���˵����
 bit[31:20]  ����
 bit[19:16]  Dummy Burst�����о����ޣ�
             0�� threshold_db=4��
             1�� threshold_db=6��
             2�� threshold_db=8��
             3�� threshold_db=9��
             4�� threshold_db=10��
             5�� threshold_db=11��
             6�� threshold_db=12��
             7�� threshold_db=14��
             8�� threshold_db=16��
             9�� threshold_db=20��
             others�� ����
             
             
 bit[15:2]   ����
 bit[1:0]    ��������õ�Dummy ѵ���������͡�
             0��Dummy Burstѵ������ͬNB
             1��Dummy Burstѵ������ͬC0ģʽѵ������
             2��Dummy Burstѵ������ͬNBģʽѵ�������й̶���ӳ���ϵ��
             3������
             Ĭ��ֵ1��
             
   UNION�ṹ:  GBBP_CPU_DB_TYPE_CFG_UNION */
#define GBBP_CPU_DB_TYPE_CFG_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x1128)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      1��ʾ�򿪽��BEP���ܡ�
             0��ʾ���ν��BEP����
             
   UNION�ṹ:  GBBP_CPU_DEM_BEP_MODE_EN_UNION */
#define GBBP_CPU_DEM_BEP_MODE_EN_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x112C)

/* �Ĵ���˵����
 bit[31]     1��ʾVALPP_RAM �� CARRY_RAM ���ݰ���ģʽʹ�ܣ���cpu_valpp_carry_mode����Ϊ1ʱ��cpu_valpp_carry_en����Ϊ1ʱ�����ģ����VALPP RAMд���ݵ�ͬʱ���Ὣ�������ͬʱ���浽CARRY RAM��.
             ��λĬ��ֵΪ1
             
 bit[30:26]  ����
 bit[25:24]  ��ʾ��CARRY_RAM��VALPP_RAM��һ��BURST������ָʾ
                      00 ����ʾ����GMSK���Ƶ�SB�������
                      10 ����ʾ����GMSK���Ƶ�NB�������
                      11 ����ʾ����8PSK���Ƶ�NB�������
                      ��������ʾ����GMSK���Ƶ�NB�������
             ��λĬ��ֵΪ2��b10
             
 bit[23:16]  ����
 bit[15]     VALPP_RAM �� CARRY_RAM ���ݰ��Ʒ���ָʾ��1��ʾ��VALPP_RAM��CARRY_RAM��0��ʾ��CARRY_RAM��VALPP_RAM,������ģʽ�£���Ҫ��Ӧ������cpu_carry_burst_pos��ΪVALPP_RAMд���ݵ���ʼ��ַ.
             ��λĬ��ֵΪ1
             
 bit[14:7]   ����
 bit[6:0]    VALPP_RAM �� CARRY_RAM ���ݰ���Ŀ��BURSTλ��(carry to valpp)
   UNION�ṹ:  GBBP_CPU_VALPP_CARRY_CTRL_UNION */
#define GBBP_CPU_VALPP_CARRY_CTRL_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0x1130)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      VALPP_RAM �� CARRY_RAM ���ݰ��������źţ�ֻ��Դ�CARRY_RAM��VALPP_RAMģʽ��Ч,�߼�������
   UNION�ṹ:  GBBP_CPU_VALPP_CARRY_START_UNION */
#define GBBP_CPU_VALPP_CARRY_START_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x1134)

/* �Ĵ���˵����
 bit[31]     1 ��ʾ�̶�ѡ��ż·��0��ʾѡ�����· Ĭ��ֵΪ0��                     ���ź�����ѡ���ϱ���nb_pos_cpu, nb_pos_adj_cpu��C/I�ȡ�
 bit[30:27]  ����
 bit[26:24]  case(cpu_cross_delta)
             3��b000: R[i][i] = R[i][i] + (R[i][i] >>8) ;
             3��b001: R[i][i] = R[i][i] + (R[i][i] >>9) ;
             3��b010: R[i][i] = R[i][i] + (R[i][i] >>10) ;
             3��b011: R[i][i] = R[i][i] + (R[i][i] >>11) ;
             3��b100: R[i][i] = R[i][i];
             cpu_cross_delta�ź�������ѡ��Խ���Ԫ�صĴ���ʽ��Ĭ��ֵ��3��b010��
 bit[23:22]  ����
 bit[21:20]  GMSK CI�����ĵ���ϵ����Ĭ��ֵ��15(����Ϊ2��b00)����ѡֵ1��8
             2��b00:15
             2��b01: 8
             2��b10: 1
             Ĭ��ֵΪ2��b00
 bit[19:18]  ����
 bit[17:16]  PHY��֡ͷλ��������֡NBλ�õĵ�������
             ����ֵ��Χ��1��1�������ʾ��
             2��b11����ʾ��֡��NB����֡��ǰһ�����ţ�
             2��b01����ʾ��֡��NB����֡����һ�����ţ�
             2��b00 ����ʾ������֡����������ź���TDMA֡ͷ��560qb�Զ����㡣
 bit[15:10]  ����
 bit[9:8]    �о�������SAIC�˲����ֵ����λֵ��10��12���أ�Ĭ��ֵ��2��b01����ֵ������������ƫ�
             2��b00: 10;
             2��b01: 11;
             2��b10: 12;
 bit[7:2]    ����
 bit[1:0]    �о�����ǰ��SAIC�˲����ֵ����λֵ��11��13���أ�Ĭ��ֵ2��b01����ֵ������������ƫ�
             2��b00: 11
             2��b01: 12
             2��b10: 13
   UNION�ṹ:  GBBP_CPU_SAIC_CTRL_UNION */
#define GBBP_CPU_SAIC_CTRL_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x1138)

/* �Ĵ���˵����
 bit[31:22]  ����
 bit[21:0]   DummuBurst���DATA��������ϱ�
   UNION�ṹ:  GBBP_MAX_DB_DATA_ENERGY_RPT_UNION */
#define GBBP_MAX_DB_DATA_ENERGY_RPT_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x113C)

/* �Ĵ���˵����
   ��      ����DummuBurst���DB��������ϱ�
   UNION�ṹ ���� */
#define GBBP_MAX_DB_ENERGY_RPT_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x1140)

/* �Ĵ���˵����
 bit[31:19]  ����
 bit[18:16]  SBλ�ü���ʹ�õ����ľ�������Ȩֵ��Ĭ��ֵ0
             0��ʾȨֵΪ1��
             1��ʾȨֵΪ65/64��
             2��ʾȨֵΪ33/32��
             3��ʾȨֵΪ17/16��
             4��ʾȨֵΪ9/8��
             5��ʾȨֵΪ5/4��
 bit[15:9]   ����
 bit[8]      ���λ�ü̳�ʹ�����ľ�������Ȩ�㷨��1Ϊʹ�ã�Ĭ��ֵ0
 bit[7:5]    ����
 bit[4]      �ϱ���nb_pos��nb_pos_adjʹ�����ľ�������Ȩ�㷨��1Ϊʹ�ã�Ĭ��ֵ0
 bit[3]      ����
 bit[2:0]    NBλ�ü���ʹ�õ����ľ�������Ȩֵ��Ĭ��ֵ0
             ������sb��Ȩֵһ��
             
   UNION�ṹ:  GBBP_ENG_WEIGHT_UNION */
#define GBBP_ENG_WEIGHT_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x1144)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  ��ǰburstֱ��I·�ϱ�
 bit[15:8]   ����
 bit[7:0]    ��ǰburstֱ��Q·�ϱ�
   UNION�ṹ:  GBBP_LS_DC_CPU_UNION */
#define GBBP_LS_DC_CPU_ADDR                           (SOC_BBP_GSM_BASE_ADDR + 0x1160)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      LSȥֱ��TOA�ϱ�ʹ�ܣ�0��ʾ�رգ�1��ʾ�򿪡�
   UNION�ṹ:  GBBP_LS_TOA_RPT_EN_UNION */
#define GBBP_LS_TOA_RPT_EN_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x1164)

/* �Ĵ���˵����
 bit[31]     ����
 bit[30:13]  �ݵ�ǰʱ�̵ڶ�����FB���ڵ�FB�������
 bit[12:0]   �ݵ�ǰʱ�̵ڶ�����FB���ڵ�FBλ��
   UNION�ṹ:  GBBP_FB_2_POS_ENG_UNION */
#define GBBP_FB_2_POS_ENG_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x1168)

/* �Ĵ���˵����
 bit[31]     ����
 bit[30:13]  �ݵ�ǰʱ�̵�������FB���ڵ�FB�������
 bit[12:0]   �ݵ�ǰʱ�̵�������FB���ڵ�FBλ��
   UNION�ṹ:  GBBP_FB_3_POS_ENG_UNION */
#define GBBP_FB_3_POS_ENG_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x116C)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    SB���ݱ���״̬�ϱ�,ÿ��gsp_sb_save_start������
             00��δ����SB���ݴ洢 
             01������SB���ݴ洢���ұ������ 
             10������SB�洢�����������ǰ�쳣��ֹ��������ʹ�ܱ����ͣ���������Ч
   UNION�ṹ:  GBBP_SB_SAVE_STATUS_UNION */
#define GBBP_SB_SAVE_STATUS_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x1170)

/* �Ĵ���˵����
 bit[31:5]   ����
 bit[4]      110/111����ģʽʱ��AFC�������;
             0��ʾ�ӳٳ���Ϊ16��1��ʾ�ӳٳ���Ϊ2��
             ���cpu_11x_capt_disable=0���򲶻�̬�ӳٳ��ȹ̶�Ϊ2������̬�̶�Ϊ16��
 bit[3:1]    ����
 bit[0]      110/111����ģʽʱ�������벶��̬��ֱ�ӽ������̬��
   UNION�ṹ:  GBBP_SHORT_11X_CFG_UNION */
#define GBBP_SHORT_11X_CFG_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x1174)

/* �Ĵ���˵����
 bit[31]     ����101ģʽ���Ƿ�����FB��SB������ж�ʹ�ܣ�Ϊ1��ʾ��FB��SB���볬��34�����򱾴�����ʧ��
 bit[30:18]  ����
 bit[17:0]   ��ǰ����SB��FB�������ޣ������ڵ��ڸ�����ʱ������SB�������
   UNION�ṹ:  GBBP_FAST_101_CFG_UNION */
#define GBBP_FAST_101_CFG_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x1178)

/* �Ĵ���˵����
 bit[31]     ������������������һ�����ޣ�ʱ��ֹͣAFC��������ƽ�ź�
             1����ʾ����������ʱ������AFC������
             0����ʾ������������С����AFC����
             
 bit[30:19]  ����
 bit[18:0]   ֹͣAFC�������������ޣ���������ֵ���ڸ�����ʱ������CI��ֵ��Σ���������AFC
   UNION�ṹ:  GBBP_HEAVY_NOISE_CFG_UNION */
#define GBBP_HEAVY_NOISE_CFG_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x117C)

/* �Ĵ���˵����
   ��      ����bit31��FB�����жϣ�ÿ��FB���������ϱ�һ�Σ�
            bit29����������жϣ�
            bit28����ƽ���������ж�;
            bit24:ʱ�Ӳ����ж�;
            bit19:�ɱ���ж�7����;
            bit18:�ɱ���ж�6����;
            bit17:�ɱ���ж�5����;
            bit16:�ɱ���ж�4����;
            bit15:�ɱ���ж�3����;
            bit14:�ɱ���ж�2����;
            bit13:�ɱ���ж�1����;
            bit12:�ɱ���ж�0����;
            bit11:ʱ϶7�ж�����;
            bit10:ʱ϶6�ж�����;
            bit9:ʱ϶5�ж�����;
            bit8:ʱ϶4�ж�����;
            bit7:ʱ϶3�ж�����;
            bit6:ʱ϶2�ж�����;
            bit5:ʱ϶1�ж�����;
            bit4:ʱ϶0�ж�����,1��Ч;
            bit3:���������ϱ��ж�����;
            bit2:ͬ�������ж�����;
            bit1:GTC PAGE�ж�����;
            bit0:TDMA֡�ж�����1��ʾ�ж�����0��ʾ���ж���������bit����ͬ�ˡ�
   UNION�ṹ ���� */
#define GBBP_CPU_INT_STA_ADDR                         (SOC_BBP_GSM_BASE_ADDR + 0x1200)

/* �Ĵ���˵����
   ��      ����bit31��FB�����жϣ�ÿ��FB���������ϱ�һ�Σ�
            bit29����������жϣ�
            bit28����ƽ���������ж�;
            bit24:ʱ�Ӳ����ж�;
            bit19:�ɱ���ж�7�����ź�;
            bit18:�ɱ���ж�6�����ź�;
            bit17:�ɱ���ж�5�����ź�;
            bit16:�ɱ���ж�4�����ź�;
            bit15:�ɱ���ж�3�����ź�;
            bit14:�ɱ���ж�2�����ź�;
            bit13:�ɱ���ж�1�����ź�;
            bit12:�ɱ���ж�0�����ź�;
            bit11:ʱ϶7�ж������ź�;
            bit10:ʱ϶6�ж������ź�;
            bit9:ʱ϶5�ж������ź�;
            bit8:ʱ϶4�ж������ź�;
            bit7:ʱ϶3�ж������ź�;
            bit6:ʱ϶2�ж������ź�;
            bit5:ʱ϶1�ж������ź�;
            bit4:ʱ϶0�ж������ź�,1��Ч;
            bit3:���������ϱ��ж������ź�;
            bit2:ͬ�������ж������ź�;
            bit1:GTC PAGE�ж������ź�;
            bit0:TDMA֡�ж������źţ�1��ʾ�ж������ź����Σ�0��ʾ�жϲ����Σ�����bit����ͬ�ˡ�
   UNION�ṹ ���� */
#define GBBP_CPU_INT_MASK_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x1204)

/* �Ĵ���˵����
   ��      ����bit31��FB�����жϣ�ÿ��FB���������ϱ�һ�Σ�
            bit29����������жϣ�
            bit28����ƽ���������ж�;
            bit24:ʱ�Ӳ����ж�;
            bit19:�ɱ���ж�7��������;
            bit18:�ɱ���ж�6��������;
            bit17:�ɱ���ж�5��������;
            bit16:�ɱ���ж�4��������;
            bit15:�ɱ���ж�3��������;
            bit14:�ɱ���ж�2��������;
            bit13:�ɱ���ж�1��������;
            bit12:�ɱ���ж�0��������;
            bit11:ʱ϶7�ж���������;
            bit10:ʱ϶6�ж���������;
            bit9:ʱ϶5�ж���������;
            bit8:ʱ϶4�ж���������;
            bit7:ʱ϶3�ж���������;
            bit6:ʱ϶2�ж���������;
            bit5:ʱ϶1�ж���������;
            bit4:ʱ϶0�ж���������,1��Ч;
            bit3:���������ϱ��ж���������;
            bit2:ͬ�������ж���������;
            bit1:GTC PAGE�ж���������;
            bit0:TDMA֡�ж������źţ�1��ʾ�ж��������������0��ʾ�ж��������㲻���������bit����ͬ�ˡ�
   UNION�ṹ ���� */
#define GBBP_CPU_INT_CLR_ADDR                         (SOC_BBP_GSM_BASE_ADDR + 0x1208)

/* �Ĵ���˵����
   ��      ����bit31��FB�����жϣ�ÿ��FB���������ϱ�һ�Σ�
            bit29����������жϣ�
            bit28����ƽ���������ж�;
            bit27:ʱ�Ӳ����ж�;
            bit26:;CTU��ϵͳ�����ж�2��
            bit25:;CTU��ϵͳ�����ж�1��
            bit24:;CTU��ϵͳ�����ж�0��
            bit19:�ɱ���ж�7����;
            bit18:�ɱ���ж�6����;
            bit17:�ɱ���ж�5����;
            bit16:�ɱ���ж�4����;
            bit15:�ɱ���ж�3����;
            bit14:�ɱ���ж�2����;
            bit13:�ɱ���ж�1����;
            bit12:�ɱ���ж�0����;
            bit11:ʱ϶7�ж�����;
            bit10:ʱ϶6�ж�����;
            bit9:ʱ϶5�ж�����;
            bit8:ʱ϶4�ж�����;
            bit7:ʱ϶3�ж�����;
            bit6:ʱ϶2�ж�����;
            bit5:ʱ϶1�ж�����;
            bit4:ʱ϶0�ж�����,1��Ч;
            bit3:���������ϱ��ж�����;
            bit2:ͬ�������ж�����;
            bit1:GTC PAGE�ж�����;
            bit0:TDMA֡�ж�����1��ʾ�ж�����0��ʾ���ж���������bit����ͬ�ˡ�
   UNION�ṹ ���� */
#define GBBP_DSP_INT_STA_ADDR                         (SOC_BBP_GSM_BASE_ADDR + 0x1210)

/* �Ĵ���˵����
   ��      ����bit31��FB�����ж����μĴ�����ÿ��FB���������ϱ�һ�Σ�
            bit29����������ж����μĴ�����
            bit28����ƽ���������ж����μĴ���;
            bit27:ʱ�Ӳ����ж����μĴ���;
            bit26:;CTU��ϵͳ�����ж�2���μĴ�����
            bit25:;CTU��ϵͳ�����ж�1���μĴ�����
            bit24:;CTU��ϵͳ�����ж�0���μĴ�����
            bit19:�ɱ���ж�7���μĴ���;
            bit18:�ɱ���ж�6���μĴ���;
            bit17:�ɱ���ж�5���μĴ���;
            bit16:�ɱ���ж�4���μĴ���;
            bit15:�ɱ���ж�3���μĴ���;
            bit14:�ɱ���ж�2���μĴ���;
            bit13:�ɱ���ж�1���μĴ���;
            bit12:�ɱ���ж�0���μĴ���;
            bit11:ʱ϶7�ж����μĴ���;
            bit10:ʱ϶6�ж����μĴ���;
            bit9:ʱ϶5�ж����μĴ���;
            bit8:ʱ϶4�ж����μĴ���;
            bit7:ʱ϶3�ж����μĴ���;
            bit6:ʱ϶2�ж����μĴ���;
            bit5:ʱ϶1�ж����μĴ���;
            bit4:ʱ϶0�ж����μĴ���,1��Ч;
            bit3:���������ϱ��ж����μĴ���;
            bit2:ͬ�������ж����μĴ���;
            bit1:GTC PAGE�ж����μĴ���;
            bit0:TDMA֡�ж����μĴ�����1��ʾ�ж����μĴ�����0��ʾ���ж����μĴ���������bit����ͬ�ˡ�
   UNION�ṹ ���� */
#define GBBP_DSP_INT_MASK_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x1214)

/* �Ĵ���˵����
   ��      ����bit31��FB�����ж������źţ�
            bit29����������ж������źţ�
            bit28����ƽ���������ж������ź�;
            bit27:ʱ�Ӳ����ж������ź�;
            bit26:;CTU��ϵͳ�����ж�2�����źţ�
            bit25:;CTU��ϵͳ�����ж�1�����źţ�
            bit24:;CTU��ϵͳ�����ж�0�����źţ�
            bit19:�ɱ���ж�7�����ź�;
            bit18:�ɱ���ж�6�����ź�;
            bit17:�ɱ���ж�5�����ź�;
            bit16:�ɱ���ж�4�����ź�;
            bit15:�ɱ���ж�3�����ź�;
            bit14:�ɱ���ж�2�����ź�;
            bit13:�ɱ���ж�1�����ź�;
            bit12:�ɱ���ж�0�����ź�;
            bit11:ʱ϶7�ж������ź�;
            bit10:ʱ϶6�ж������ź�;
            bit9:ʱ϶5�ж������ź�;
            bit8:ʱ϶4�ж������ź�;
            bit7:ʱ϶3�ж������ź�;
            bit6:ʱ϶2�ж������ź�;
            bit5:ʱ϶1�ж������ź�;
            bit4:ʱ϶0�ж������ź�,1��Ч;
            bit3:���������ϱ��ж������ź�;
            bit2:ͬ�������ж������ź�;
            bit1:GTC PAGE�ж������ź�;
            bit0:TDMA֡�ж������źţ�1��ʾ�ж������źţ�0��ʾ���ж������źţ�����bit����ͬ�ˡ�
   UNION�ṹ ���� */
#define GBBP_DSP_INT_CLR_ADDR                         (SOC_BBP_GSM_BASE_ADDR + 0x1218)

/* �Ĵ���˵����
 bit[31:16]  Luise��Ƶ�Ż��㷨����õ���Ƶƫ����ֵ
 bit[15:9]   ����
 bit[8]      ��TCXOʹ���źţ����ڿ�������ǰ�����Ƿ񾭹�NCO��ƫ
 bit[7:1]    ����
 bit[0]      Luise��Ƶʹ��
   UNION�ṹ:  GBBP_ADDR_CPU_LUISE_AFC_UNION */
#define GBBP_ADDR_CPU_LUISE_AFC_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x1258)

/* �Ĵ���˵����
 bit[31:13]  ����
 bit[12:0]   ����˯��ģʽ�£�˯����ʼQbʱ�̣�TDMA��ʱ�̣��ò����ǻ���TDMAʱ��gtc_tdma_qb��
   UNION�ṹ:  GBBP_ADDR_GDRX_SLEEP_POINT_UNION */
#define GBBP_ADDR_GDRX_SLEEP_POINT_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x125C)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9:0]    ��ʱ��Ϣ��ON�����䵽OFF����������õĶ�ʱ��Ϣ������������ֵҪ����ȫ�����ݴ���ʱ�ӣ���λQB��Ĭ������16QB��
   UNION�ṹ:  GBBP_ADDR_CPU_TRANS_COMP_UNION */
#define GBBP_ADDR_CPU_TRANS_COMP_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x1260)

/* �Ĵ���˵����
 bit[31:27]  ����
 bit[26:16]  ��0����λУ׼�������ֵP��11�����з�������ȡֵ��Χ-1023~1023��
 bit[15:10]  ����
 bit[9:0]    ��0�����У׼�������ֵA��10�����з�������ȡֵ��Χ-511~511��
   UNION�ṹ:  GBBP_ADDR_RX_IQ_MISMATCH_REG0_UNION */
#define GBBP_ADDR_RX_IQ_MISMATCH_REG0_ADDR            (SOC_BBP_GSM_BASE_ADDR + 0x1270)

/* �Ĵ���˵����
 bit[31:27]  ����
 bit[26:16]  ��1����λУ׼�������ֵP��11�����з�������ȡֵ��Χ-1023~1023��
 bit[15:10]  ����
 bit[9:0]    ��1�����У׼�������ֵA��10�����з�������ȡֵ��Χ-511~511��
   UNION�ṹ:  GBBP_ADDR_RX_IQ_MISMATCH_REG1_UNION */
#define GBBP_ADDR_RX_IQ_MISMATCH_REG1_ADDR            (SOC_BBP_GSM_BASE_ADDR + 0x1274)

/* �Ĵ���˵����
 bit[31:27]  ����
 bit[26:16]  ��2����λУ׼�������ֵP��11�����з�������ȡֵ��Χ-1023~1023��
 bit[15:10]  ����
 bit[9:0]    ��2�����У׼�������ֵA��10�����з�������ȡֵ��Χ-511~511��
   UNION�ṹ:  GBBP_ADDR_RX_IQ_MISMATCH_REG2_UNION */
#define GBBP_ADDR_RX_IQ_MISMATCH_REG2_ADDR            (SOC_BBP_GSM_BASE_ADDR + 0x1278)

/* �Ĵ���˵����
 bit[31:27]  ����
 bit[26:16]  ��3����λУ׼�������ֵP��11�����з�������ȡֵ��Χ-1023~1023��
 bit[15:10]  ����
 bit[9:0]    ��3�����У׼�������ֵA��10�����з�������ȡֵ��Χ-511~511��
   UNION�ṹ:  GBBP_ADDR_RX_IQ_MISMATCH_REG3_UNION */
#define GBBP_ADDR_RX_IQ_MISMATCH_REG3_ADDR            (SOC_BBP_GSM_BASE_ADDR + 0x127C)

/* �Ĵ���˵����
 bit[31:27]  ����
 bit[26:16]  ��4����λУ׼�������ֵP��11�����з�������ȡֵ��Χ-1023~1023��
 bit[15:10]  ����
 bit[9:0]    ��4�����У׼�������ֵA��10�����з�������ȡֵ��Χ-511~511��
   UNION�ṹ:  GBBP_ADDR_RX_IQ_MISMATCH_REG4_UNION */
#define GBBP_ADDR_RX_IQ_MISMATCH_REG4_ADDR            (SOC_BBP_GSM_BASE_ADDR + 0x1280)

/* �Ĵ���˵����
 bit[31:20]  ����
 bit[19:16]  �ڵ��ƽ�������չ�����������
 bit[15:4]   ����
 bit[3:0]    ���һ��tx_rrx_data_ind_in��gmod_finish֮��ļ��clk��
   UNION�ṹ:  GBBP_ADDR_TX_RRC_EXT_UNION */
#define GBBP_ADDR_TX_RRC_EXT_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x1284)

/* �Ĵ���˵����
 bit[31:11]  ����
 bit[10:0]   SB���Ƶƫ�޷���Ĭ��ֵΪ1800MHz�����Ƶƫ760��900MHzʱ����380��
   UNION�ṹ:  GBBP_ADDR_MAX_PHI_DEV_UNION */
#define GBBP_ADDR_MAX_PHI_DEV_ADDR                    (SOC_BBP_GSM_BASE_ADDR + 0x1288)

/* �Ĵ���˵����
 bit[31:17]  ����
 bit[16]     HD3/5г������������·��0����ʾг���������ܲ���·�����Ƿ����г����������Ҫ�ο�gsp_hd35_cal_en���������1����ʾг������������·����V8R1�汾ʱ����ȫһ�¡�
 bit[15:1]   ����
 bit[0]      HD3/5��ʼ���ò�������RAMƹ�ҷ���ʹ�ܣ�1��ʾ����ƹ�ҷ��ʣ�0��ʾ�̶�����ƹRAM�ռ䣻�����ź�Ϊ1ʱ���߼��ڲ���TDMA֡ͷ�Զ��л�ƹ�ұ�־��
   UNION�ṹ:  GBBP_ADDR_HD35_PARA_REG_UNION */
#define GBBP_ADDR_HD35_PARA_REG_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x1290)

/* �Ĵ���˵����
 bit[31]     1��ʾSPI��Ƶ���Ʋ�����GTCģ�������0��ʾSPI��Ƶ���Ʋ�����CPU�ӿ�ģ�������Ĭ��ֵΪ1�����ź�ֻ������������TA�ϴ�ʱ����RF��Ƶ��ʱ���⣻��������¸��źŶ�Ӧ������Ϊ1
 bit[30:13]  ����
 bit[12:8]   CPU�ӿ����ñ�����Ҫ���͵�SPI������������00001��ʾһ������10000��ʾ16��������λĬ��ֵΪ5'b00100
 bit[7:0]    CPU�ӿ�����SPI���ڴ���������SPI DATA RAM����ʼλ�ã���λĬ��ֵΪ8'd0
   UNION�ṹ:  GBBP_CPU_SPI_RF_CFG_UNION */
#define GBBP_CPU_SPI_RF_CFG_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x1368)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      CPU����SPI���ݷ�������
   UNION�ṹ:  GBBP_CPU_SPI_RF_RD_UNION */
#define GBBP_CPU_SPI_RF_RD_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x136C)

/* �Ĵ���˵����
 bit[31]     28bit�����߿��ź�CPUдʹ��ָʾ�źš�
 bit[30:0]   �����߿�CPU�ӿ����ã����������NV�������
   UNION�ṹ:  GBBP_CPU_LINE_CTRL_UNION */
#define GBBP_CPU_LINE_CTRL_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x1364)

/* �Ĵ���˵����
 bit[31]     ����
 bit[30:0]   �����߿�ʵ���߿�״̬�������á�
   UNION�ṹ:  GBBP_GTC_GSP_LINE_STATE_RPT_UNION */
#define GBBP_GTC_GSP_LINE_STATE_RPT_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x1384)

/* �Ĵ���˵����
 bit[31]     ���һ��ʱ϶�����ٲ�����־�ϱ���1��ʾ��ǰΪ���ٲ�����0��ʾ��ǰΪ���ٲ�����
 bit[30:27]  ����
 bit[26:24]  ���һ��ʱ϶AAGC��λ�ϱ���
 bit[23:20]  ����
 bit[19:8]   ���һ��ʱ϶AGC RSSIֵ����λ0.125dBm���ϱ���CPU����ֵ���ǿտڵ�RSSIֵ��
 bit[7:3]    ����
 bit[2:0]    ���һ��ʱ϶AGC�����������档
   UNION�ṹ:  GBBP_AAGC_GAIN1_CPU_UNION */
#define GBBP_AAGC_GAIN1_CPU_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x1460)

/* �Ĵ���˵����
 bit[31]     �ν�һ��ʱ϶�����ٲ�����־�ϱ���1��ʾ��ǰΪ���ٲ�����0��ʾ��ǰΪ���ٲ�����
 bit[30:27]  ����
 bit[26:24]  �ν�һ��ʱ϶AAGC��λ�ϱ���
 bit[23:20]  ����
 bit[19:8]   �ν�һ��ʱ϶AGC RSSIֵ����λ0.125dBm���ϱ���CPU����ֵ���ǿտڵ�RSSIֵ��
 bit[7:3]    ����
 bit[2:0]    �ν�һ��ʱ϶AGC�����������档
   UNION�ṹ:  GBBP_AAGC_GAIN2_CPU_UNION */
#define GBBP_AAGC_GAIN2_CPU_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x1464)

/* �Ĵ���˵����
 bit[31]     �δν�һ��ʱ϶�����ٲ�����־�ϱ���1��ʾ��ǰΪ���ٲ�����0��ʾ��ǰΪ���ٲ�����
 bit[30:27]  ����
 bit[26:24]  �δν�һ��ʱ϶AAGC��λ�ϱ���
 bit[23:20]  ����
 bit[19:8]   �δν�һ��ʱ϶AGC RSSIֵ����λ0.125dBm���ϱ���CPU����ֵ���ǿտڵ�RSSIֵ��
 bit[7:3]    ����
 bit[2:0]    �δν�һ��ʱ϶AGC�����������档
   UNION�ṹ:  GBBP_AAGC_GAIN3_CPU_UNION */
#define GBBP_AAGC_GAIN3_CPU_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x1468)

/* �Ĵ���˵����
 bit[31]     ���Ľ�һ��ʱ϶�����ٲ�����־�ϱ���1��ʾ��ǰΪ���ٲ�����0��ʾ��ǰΪ���ٲ�����
 bit[30:27]  ����
 bit[26:24]  '���Ľ�һ��ʱ϶AAGC��λ�ϱ���
 bit[23:20]  ����
 bit[19:8]   '���Ľ�һ��ʱ϶AGC RSSIֵ����λ0.125dBm���ϱ���CPU����ֵ���ǿտڵ�RSSIֵ��
 bit[7:3]    ����
 bit[2:0]    '���Ľ�һ��ʱ϶AGC�����������档
   UNION�ṹ:  GBBP_AAGC_GAIN4_CPU_UNION */
#define GBBP_AAGC_GAIN4_CPU_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x146C)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17]     ����ģ����λ�źţ�д1��ģ�鸴λ��
 bit[16]     ���Ԥ����ģ����λ�źţ�д1��ģ�鸴λ��
 bit[15]     GTC��ʱģ����λ�źţ�д1��ģ�鸴λ��
 bit[14]     GTCģ����λ�źţ�д1��ģ�鸴λ��
             ע�⣺�ø�λ�ź����ú󣬽��ᵼ��ר���߿غ͹����߿ؾ���λ��0,��
 bit[13]     ����APCģ����λ�źţ�д1��ģ�鸴λ��
 bit[12]     ���е��ƺ���ģ����λ�źţ�д1��ģ�鸴λ��
 bit[11]     ���н��ģ�飨�����������ֺ����н����ز��֣���λ�źţ�д1��ģ�鸴λ��
 bit[10]     ��������ģ���г�ȥbit7��bit8��bit9ʣ�µ�����ģ����λ�źţ�д1��ģ�鸴λ��bit7��bit8��bit9��bit10��ͬ������������ģ����ơ�
 bit[9]      ��������ģ���н����������ֵ�洢/��ȡģ����λ�źţ�д1��ģ�鸴λ��bit7��bit8��bit9��bit10��ͬ������������ģ����ơ�
 bit[8]      ��������ģ����ȥ��֯/��֯��ȥ���/���ģ����λ�źţ�д1��ģ�鸴λ��bit7��bit8��bit9��bit10��ͬ������������ģ����ơ�
 bit[7]      ��������ģ����viterbiģ����λ�źţ�д1��ģ�鸴λ��bit7��bit8��bit9��bit10��ͬ������������ģ����ơ�
 bit[6]      �ŵ��˲�ģ����λ�źţ�д1��ģ�鸴λ��
 bit[5]      ��Ƶ���ģ����λ�źţ�д1��ģ�鸴λ��
 bit[4]      �Զ��������ģ����λ�źţ�д1��ģ�鸴λ��
 bit[3]      ���б���ģ����mapģ����λ�źţ�д1��ģ�鸴λ��
 bit[2]      ���б���ģ�飨�����б���mapģ�飩��λ�źţ�д1��ģ�鸴λ��Bit2��bit3��ͬ�������б���ģ����ơ�
 bit[1]      ���е���ģ����λ�źţ�д1��ģ�鸴λ��
 bit[0]      �ӽ���ģ����λ�źţ�д1��ģ�鸴λ��
   UNION�ṹ:  GBBP_ADDR_CPU_SOFT_RST_UNION */
#define GBBP_ADDR_CPU_SOFT_RST_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x1350)

/* �Ĵ���˵����
 bit[31:17]  ����
 bit[16]     ���Ԥ����ģ��CPU����ʱ����Чָʾ��1��ʾ��ʱ�ӣ�0��ʾû��ʱ�ӡ�
 bit[15]     ����
 bit[14]     GTCģ��CPU����ʱ����Чָʾ��1��ʾ��ʱ�ӣ�0��ʾû��ʱ�ӡ�
 bit[13]     ����APCģ��CPU����ʱ����Чָʾ��1��ʾ��ʱ�ӣ�0��ʾû��ʱ�ӡ�
 bit[12]     ���е��ƺ���ģ��CPU����ʱ����Чָʾ��1��ʾ��ʱ�ӣ�0��ʾû��ʱ�ӡ�
 bit[11]     ���н��ģ�飨�����������ֺ����н����ز��֣�CPU����ʱ����Чָʾ��1��ʾ��ʱ�ӣ�0��ʾû��ʱ�ӡ�
 bit[10]     ��������ģ�����bit7��bit8��bit9ʣ��ģ���CPU����ʱ����Чָʾ��1��ʾ��ʱ�ӣ�0��ʾû��ʱ�ӡ�
 bit[9]      ��������ģ���еĽ����������ֵ�洢/��ȡģ��CPU����ʱ����Чָʾ��1��ʾ��ʱ�ӣ�0��ʾû��ʱ�ӡ�
 bit[8]      ��������ģ���еĽ�֯/ȥ��֯�����/ȥ���ģ��CPU����ʱ����Чָʾ��1��ʾ��ʱ�ӣ�0��ʾû��ʱ�ӡ�
 bit[7]      ��������ģ���е�viterbiģ��CPU����ʱ����Чָʾ��1��ʾ��ʱ�ӣ�0��ʾû��ʱ�ӡ�bit7��bit8��bit9��bit10������������ģ�顣
 bit[6]      �ŵ��˲�Ī��CPU����ʱ����Чָʾ��1��ʾ��ʱ�ӣ�0��ʾû��ʱ�ӡ�
 bit[5]      ��Ƶ���ģ��CPU����ʱ����Чָʾ��1��ʾ��ʱ�ӣ�0��ʾû��ʱ�ӡ�
 bit[4]      �Զ��������ģ��CPU����ʱ����Чָʾ��1��ʾ��ʱ�ӣ�0��ʾû��ʱ�ӡ�
 bit[3]      ���б���mapģ��CPU����ʱ����Чָʾ��1��ʾ��ʱ�ӣ�0��ʾû��ʱ�ӡ�
 bit[2]      ���б���ģ�飨�������б���mapģ�飩CPU����ʱ����Чָʾ��1��ʾ��ʱ�ӣ�0��ʾû��ʱ�ӡ�bit2��bit3�������б���ģ�顣
 bit[1]      ���е���ģ��CPU����ʱ����Чָʾ��1��ʾ��ʱ�ӣ�0��ʾû��ʱ�ӡ�
 bit[0]      �ӽ���ģ��CPU����ʱ����Чָʾ��1��ʾ��ʱ�ӣ�0��ʾû��ʱ�ӡ�
   UNION�ṹ:  GBBP_ADDR_CPU_CLK_CTRL_UNION */
#define GBBP_ADDR_CPU_CLK_CTRL_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x1354)

/* �Ĵ���˵����
 bit[31:12]  ����
 bit[11]     ���н���������������ֺͽ��������ز��֣�ģ���Զ�ʱ���ſ�orCPUʱ���ſ�ѡ���źţ�1��ʾCPU�����ſأ�0��ʾ�Զ�ʱ���ſء�
 bit[10]     ��������ģ���г���bit7��bit8��bit9ʣ�µ�ģ���Զ�ʱ���ſ�orCPUʱ���ſ�ѡ���źţ�1��ʾCPU�����ſأ�0��ʾ�Զ�ʱ���ſء�
 bit[9]      ��������ģ���н����������ֵ�洢/��ȡģ���Զ�ʱ���ſ�orCPUʱ���ſ�ѡ���źţ�1��ʾCPU�����ſأ�0��ʾ�Զ�ʱ���ſء�
 bit[8]      ��������ģ���н�֯/ȥ��֯�����/ȥ���ģ���Զ�ʱ���ſ�orCPUʱ���ſ�ѡ���źţ�1��ʾCPU�����ſأ�0��ʾ�Զ�ʱ���ſء�
 bit[7]      ��������ģ����viterbiģ���Զ�ʱ���ſ�orCPUʱ���ſ�ѡ���źţ�1��ʾCPU�����ſأ�0��ʾ�Զ�ʱ���ſء�bit7��bit8��bit9��bit10������������ģ����ơ�
 bit[6]      �ŵ��˲�ģ���Զ�ʱ���ſ�orCPUʱ���ſ�ѡ���źţ�1��ʾCPU�����ſأ�0��ʾ�Զ�ʱ���ſء�
 bit[5]      ��Ƶ���ģ���Զ�ʱ���ſ�orCPUʱ���ſ�ѡ���źţ�1��ʾCPU�����ſأ�0��ʾ�Զ�ʱ���ſء�
 bit[4]      �Զ��������ģ���Զ�ʱ���ſ�orCPUʱ���ſ�ѡ���źţ�1��ʾCPU�����ſأ�0��ʾ�Զ�ʱ���ſء�
 bit[3]      ���б���map����ģ���Զ�ʱ���ſ�orCPUʱ���ſ�ѡ���źţ�1��ʾCPU�����ſأ�0��ʾ�Զ�ʱ���ſء�
 bit[2]      ���б��루����map����ģ�飩ģ���Զ�ʱ���ſ�orCPUʱ���ſ�ѡ���źţ�1��ʾCPU�����ſأ�0��ʾ�Զ�ʱ���ſء�bit2��bit3�������б���ģ�顣
 bit[1]      ���е���ģ���Զ�ʱ���ſ�orCPUʱ���ſ�ѡ���źţ�1��ʾCPU�����ſأ�0��ʾ�Զ�ʱ���ſء�
 bit[0]      �ӽ���ģ���Զ�ʱ���ſ�orCPUʱ���ſ�ѡ���źţ�1��ʾCPU�����ſأ�0��ʾ�Զ�ʱ���ſء�
   UNION�ṹ:  GBBP_ADDR_CPU_CLK_MODE_SEL_UNION */
#define GBBP_ADDR_CPU_CLK_MODE_SEL_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x1358)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17]     ����ģ��ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء�
 bit[16]     ���н��Ԥ����ģ��ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء�
 bit[15]     ����
 bit[14]     GTCģ��ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء�
 bit[13]     ����APCģ��ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء�
 bit[12]     ���е��ƺ���ģ��ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء�
 bit[11]     ���н���������������ֺ����н����ز��֣�ģ��ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء�
 bit[10]     ��������ģ���г���bit��bit8��bit9ʣ�µ�ģ��ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء�
 bit[9]      ��������ģ���н����������ֵ�洢/��ȡģ��ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء�
 bit[8]      ��������ģ���н�֯/ȥ���ʡ����/ȥ���ģ��ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء�
 bit[7]      ��������ģ����viterbiģ��ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء�bit7��bit8��bit9��bit10������������ģ�顣
 bit[6]      �ŵ��˲�ģ��ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء�
 bit[5]      ��Ƶ���ģ��ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء�
 bit[4]      �Զ��������ģ��ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء�
 bit[3]      ���б���ģ����mapģ��ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء�
 bit[2]      ���б���ģ�飨��ȥmap����ģ�飩ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء�bit2��bit3�������б���ģ�顣
 bit[1]      ���е���ģ��ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء�
 bit[0]      �ӽ���ģ��ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء�
   UNION�ṹ:  GBBP_ADDR_CPU_AUTO_CLK_BYPASS_UNION */
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_ADDR            (SOC_BBP_GSM_BASE_ADDR + 0x135C)

/* �Ĵ���˵����
 bit[31:9]   ����
 bit[8]      1��ʾDRX����ģʽʹ�ܣ���ʱGTCʱ��Ӧ���رգ�����DRX���Ѻ�Ķ�ʱά������ıȶԡ�����ʹ���¸��ź�Ӧ�ñ���0�������á�
 bit[7:5]    ����
 bit[4]      GTCģ�鹤��ʹ���źţ�������Ϊ���ź�Ϊ�ߣ�Ȼ��������GTC��
 bit[3]      1��ʾ�����޸�����ִ�е�GTCָ��ҳ����Ҫ�޸�ʱ������1���޸���ɺ���0��
 bit[2]      GTCָ����TDMA֡ͷ���Զ�ִ��ʹ�ܣ�Ĭ��Ϊ0��
 bit[1]      д1����ָ��ҳִ�У��ڲ�����һ��104Mʱ�����壬�����㣬д0�����塣
 bit[0]      0�����л�ָ��RAMҳ��1��ƹ���л�ָ��RAMҳ����λ���һ������ʱӦ���л�ָ��ҳ��
   UNION�ṹ:  GBBP_CPU_GTC_CFG_UNION */
#define GBBP_CPU_GTC_CFG_ADDR                         (SOC_BBP_GSM_BASE_ADDR + 0x1360)

/* �Ĵ���˵����
 bit[31:6]   ����
 bit[5]      ��ǰGTCָ��RAM��ƹ�ұ�־�ϱ��������á�
 bit[4]      GTCָ��RAMƹ���л�ʹ���ϱ��������á�
 bit[3]      ����
 bit[2]      1����ʾGTC����run����״̬�������á�
 bit[1]      1����ʾGTC����hold����start״̬�������á�
 bit[0]      1����ʾGTCû��GTCָ��ִ�У�0��ʾGTC����ִ�У������á�
   UNION�ṹ:  GBBP_GTC_STATE_RPT_UNION */
#define GBBP_GTC_STATE_RPT_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x1374)

/* �Ĵ���˵����
 bit[31:13]  ����
 bit[12:0]   TDMA��ʱ��TimeBaseʱ��ƫ���λqb����frm_offsetΪN����TimeBase������N-1��GTC�ڲ�������frac_cnt������95ʱ����һ��TDMA֡�ż�1�������á�
   UNION�ṹ:  GBBP_GTC_FRM_OFFSET_RPT_UNION */
#define GBBP_GTC_FRM_OFFSET_RPT_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x137C)

/* �Ĵ���˵����
 bit[31:13]  ����
 bit[12:0]   ֡�ж���TimeBaseʱ��ƫ���λqb�������á�
   UNION�ṹ:  GBBP_GTC_FRM_IT_OFFSET_RPT_UNION */
#define GBBP_GTC_FRM_IT_OFFSET_RPT_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x1380)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:24]  ����֡��ά�������е�T2��ʼֵ���ò���ֵ��cpu_gtc_t1_cnt,cpu_gtc_t2_cnt,cpu_gtc_fn_low,cpu_gtc_fn_highһ������GTC�ڲ�֡��ά���Ĵ����ĳ�ʼ������GTC��TDMA֡�߽紦��Ч������Ӧ����Ϊ��һ֡��֡�ŵ�T1ֵ��
 bit[23:21]  ����
 bit[20:16]  ����֡��ά�������е�T2��ʼֵ���ò���ֵ��cpu_gtc_t2_cnt,cpu_gtc_t3_cnt,cpu_gtc_fn_low,cpu_gtc_fn_highһ������GTC�ڲ�֡��ά���Ĵ����ĳ�ʼ������GTC��TDMA֡�߽紦��Ч������Ӧ����Ϊ��һ֡��֡�ŵ�T1ֵ��
 bit[15:11]  ����
 bit[10:0]   ����֡��ά�������е�T1��ʼֵ���ò���ֵ��cpu_gtc_t1_cnt,cpu_gtc_t3_cnt,cpu_gtc_fn_low,cpu_gtc_fn_highһ������GTC�ڲ�֡��ά���Ĵ����ĳ�ʼ������GTC��TDMA֡�߽紦��Ч������Ӧ����Ϊ��һ֡��֡�ŵ�T1ֵ��
   UNION�ṹ:  GBBP_CPU_GTC_T1_T2_T3_CNG_UNION */
#define GBBP_CPU_GTC_T1_T2_T3_CNG_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0x1388)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:24]  GTC�ڲ�ά����T3�������ϱ�
 bit[23:21]  ����
 bit[20:16]  GTC�ڲ�ά����T2�������ϱ�
 bit[15:11]  ����
 bit[10:0]   GTC�ڲ�ά����T1�������ϱ�
   UNION�ṹ:  GBBP_GTC_T1_T2_T3_RPT_CPU_UNION */
#define GBBP_GTC_T1_T2_T3_RPT_CPU_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0x138C)

/* �Ĵ���˵����
 bit[31]     cpu_gtc_frm_offset
             cpu_gtc_frm_it_offset
             ������Чָʾ�źţ��߼������㡣
 bit[30:29]  ����
 bit[28:16]  CPU���õ�gtc_frm_it_offset������
 bit[15:13]  ����
 bit[12:0]   CPU���õ�gtc_frm_offset������
   UNION�ṹ:  GBBP_CPU_GTC_FRM_OFFSET_CFG_UNION */
#define GBBP_CPU_GTC_FRM_OFFSET_CFG_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x1390)

/* �Ĵ���˵����
 bit[31]     ֡�ų�ʼ���źţ�1��Ч���߼������㡣��T1��T2��T3��fn_low��fn_high����д�����źŲſ�����1��
 bit[30:27]  ����
 bit[26:16]  CPU����TDMA֡�Ÿ�λ0~2047����λ�����󣬸�λ��1��CPU���ú���֡�߽紦��Ч������Ӧ����Ϊ��һ֡��֡�š�
 bit[15:11]  ����
 bit[10:0]   CPU����TDMA֡�ŵ�λ0~26*51-1ѭ��������CPU���ú���֡�߽紦��Ч������Ӧ����Ϊ��һ֡��֡�š�
   UNION�ṹ:  GBBP_CPU_GTC_FN_CNG_UNION */
#define GBBP_CPU_GTC_FN_CNG_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x1394)

/* �Ĵ���˵����
 bit[31:27]  ����
 bit[26:16]  GTC��ʱ֡�Ÿ�λ��
 bit[15:11]  ����
 bit[10:0]   GTC��ʱ֡�ŵ�λ��
   UNION�ṹ:  GBBP_GTC_FN_RPT_UNION */
#define GBBP_GTC_FN_RPT_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x1398)

/* �Ĵ���˵����
 bit[31:29]  ����
 bit[28:16]  ����ʱ��QB�ϱ�����Χ��0~4999����Ӧһ֡�ĳ��ȣ���ֵֻ�븴λʱ���йأ������á�
 bit[15:13]  ����
 bit[12:0]   ��ǰʱ��TDMA��QB����ֵ��0~4999��
   UNION�ṹ:  GBBP_GTC_QB_RPT_UNION */
#define GBBP_GTC_QB_RPT_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x139C)

/* �Ĵ���˵����
 bit[31:27]  ����
 bit[26:16]  ����ʱ��֡���ϱ�����ֵ�仯ʱ����gtc_timebase_qbΪ4999����������Χ0~26*51-1�������á�
 bit[15:13]  ����
 bit[12:0]   ����ʱ��QB�ϱ�����Χ��0~4999����Ӧһ֡�ĳ��ȣ���ֵֻ�븴λʱ���йأ������á�
   UNION�ṹ:  GBBP_TIMEBASE_RPT_UNION */
#define GBBP_TIMEBASE_RPT_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x13A8)

/* �Ĵ���˵����
 bit[31:9]   ����
 bit[8]      BLERͳ��ģʽ���ƣ�0��ʾÿ������CRC���������BLERͳ�ƣ�����HEAD��DATA��ͳ�ƣ�
             1��ʾֻͳ��ÿ��DATA������CRC���BLERֵ
             
 bit[7:5]    ����
 bit[4]      ���������ϱ�BER�����źţ������źţ�cpu��1���߼�������
 bit[3:1]    ����
 bit[0]      ���������ϱ�BLER�����źţ������źţ�cpu��1�߼�������
   UNION�ṹ:  GBBP_CPU_BLER_BER_CLR_UNION */
#define GBBP_CPU_BLER_BER_CLR_ADDR                    (SOC_BBP_GSM_BASE_ADDR + 0x1300)

/* �Ĵ���˵����
 bit[31]     ����
 bit[30:24]  AMR�����������codec_mode=11��Ӧ��AMR����֡cb_index
 bit[23]     ����
 bit[22:16]  AMR�����������codec_mode=10��Ӧ��AMR����֡cb_index
 bit[15]     ����
 bit[14:8]   AMR�����������codec_mode=01��Ӧ��AMR����֡cb_index
 bit[7]      ����
 bit[6:0]    AMR�����������codec_mode=00��Ӧ��AMR����֡cb_index
   UNION�ṹ:  GBBP_CPU_AMR_CB_INDEX_UNION */
#define GBBP_CPU_AMR_CB_INDEX_ADDR                    (SOC_BBP_GSM_BASE_ADDR + 0x1304)

/* �Ĵ���˵����
 bit[31:17]  ����
 bit[16]     ��AMR������������仯ʱ����Ҫ���ø��ź�Ϊ1
 bit[15:8]   ����
 bit[7:4]    ����֡BFI��������о����ޣ����÷�Χ0��8
 bit[3:2]    ����
 bit[1:0]    AMR�����������Ч����֡���͸���
             0 ��ʾ1��
             1 ��ʾ2��
             2 ��ʾ3��
             3 ��ʾ4��
             ����ҵ������ΪGMSK WBAMRʱ�����÷�ΧΪ0��2��
             
   UNION�ṹ:  GBBP_CPU_AMR_ACTIVE_SET_NUM_UNION */
#define GBBP_CPU_AMR_ACTIVE_SET_NUM_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x1308)

/* �Ĵ���˵����
   ��      �������������ϱ��ۼ�BLER������
   UNION�ṹ ���� */
#define GBBP_BLER_ERRR_RPT_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x130C)

/* �Ĵ���˵����
   ��      �������������ϱ��ۼ�BLER����
   UNION�ṹ ���� */
#define GBBP_BLER_TOTAL_RPT_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x1310)

/* �Ĵ���˵����
   ��      �������������ϱ��ۼ�BER������
   UNION�ṹ ���� */
#define GBBP_BER_ERRR_RPT_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x1314)

/* �Ĵ���˵����
   ��      �������������ϱ��ۼ�BER����
   UNION�ṹ ���� */
#define GBBP_BER_TOTAL_RPT_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x1318)

/* �Ĵ���˵����
 bit[31:16]  ����
 bit[15:0]   DummyBurst������������ϱ�
   UNION�ṹ:  GBBP_DB_BLER_ERR_RPT_UNION */
#define GBBP_DB_BLER_ERR_RPT_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x1484)

/* �Ĵ���˵����
 bit[31:8]   ����
 bit[7:0]    SB��������ϱ�
   UNION�ṹ:  GBBP_SB_BLER_ERR_RPT_UNION */
#define GBBP_SB_BLER_ERR_RPT_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x1488)

/* �Ĵ���˵����
 bit[31:16]  ����
 bit[15:0]   EDGEҵ��DATA��������ϱ�
   UNION�ṹ:  GBBP_DATA_BLER_ERR_RPT_UNION */
#define GBBP_DATA_BLER_ERR_RPT_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x148C)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29]     1��ʾ�о��������̣�������
 bit[28]     ��׷�ʽѡ��,0��ʾ��ף�1��ʾ����ף�������
 bit[27:26]  ����������ͣ�
             00��0״̬��ʼ����0״̬������
             01��0״̬��ʼ������0״̬������
             10�ӷ�0״̬��ʼ����0״̬������
             11��0״̬��ʼ������0״̬������
             ������
             
 bit[25:15]  ����������ݳ��ȣ�������
 bit[14:5]   �����������ݳ��ȣ�������ǰ���ݳ��ȣ�������
 bit[4]      ������������ȣ�0: 4;  1: 6��������
 bit[3:0]    ���������ָʾ��
             2=1/2,3=1/3,4=1/4����6=1/6��������
   UNION�ṹ:  GBBP_CODEC_PARA_REG1_UNION */
#define GBBP_CODEC_PARA_REG1_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x1320)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:28]  CRCԤ����ҵ���־�ź�
             00 ��Ԥ����
             01 ������
             10 USFԤ����_1
             11 USFԤ����_2
             ��������
             
 bit[27:21]  �������ɶ���ʽ3��������
 bit[20:14]  �������ɶ���ʽ2��������
 bit[13:7]   �������ɶ���ʽ1��������
 bit[6:0]    �������ɶ���ʽ0��������
   UNION�ṹ:  GBBP_CODEC_PARA_REG2_UNION */
#define GBBP_CODEC_PARA_REG2_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x1324)

/* �Ĵ���˵����
 bit[31:28]  �������ɶ���ʽ�����ţ�������
             
 bit[27:21]  ���ͼ���Ĵ�ױ���ţ�������
 bit[20:14]  ��ĸλ�õı������ɶ���ʽ��������
 bit[13:7]   �������ɶ���ʽ5��������
 bit[6:0]    �������ɶ���ʽ4��������
   UNION�ṹ:  GBBP_CODEC_PARA_REG3_UNION */
#define GBBP_CODEC_PARA_REG3_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x1328)

/* �Ĵ���˵����
 bit[31:29]  ����
 bit[28]     1��ʾ����CRCУ����̣�������
 bit[27]     1��ʾ�н�֯���̣�������
 bit[26:16]  �������ڽ�֯�н���bit��ţ�������
 bit[15:5]   �������ڽ�֯����ʼbit���
 bit[4:0]    ��֯��ʽ��ţ�������
   UNION�ṹ:  GBBP_CODEC_PARA_REG4_UNION */
#define GBBP_CODEC_PARA_REG4_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x132C)

/* �Ĵ���˵����
 bit[31]     1��ʾ����β����������
             0��ʾ������
             ��������
             
 bit[30]     ����
 bit[29:26]  CRC����ָʾ��������
 bit[25:23]  β���ز��㴦��ģʽ��
             bit25: 1��ʾ�������㴦��
                    0��ʾ���������㴦��
             bit24��bit23��
             00��ʾ��4����
             01��ʾ��6����
             10��ʾ��8����
             11��ʾ��32����
             ������
             
 bit[22:21]  ����ҵ�����ָʾ
             00 ��AFS��AHS��csҵ��
             01 AFS����AHSҵ��
             10 GPRSҵ��
             11 EGPRSҵ��
             ������
             
 bit[20:12]  CLASS2 bit��ʼλ�ã�������
 bit[11]     1��ʾ����CLASS2 bit��������
 bit[10]     ����
 bit[9:0]    ��Ϣbit����λ�ã�������
   UNION�ṹ:  GBBP_CODEC_PARA_REG5_UNION */
#define GBBP_CODEC_PARA_REG5_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x1330)

/* �Ĵ���˵����
 bit[31:29]  ����
 bit[28:24]  PS���HEADER CPSbit �ϱ���������
 bit[23]     ����
 bit[22:20]  PS��USF bit �ϱ���������
 bit[19]     ����
 bit[18:12]  �����ţ�������
 bit[11:0]   �������Ϣ�����ʼλ�ã�������
   UNION�ṹ:  GBBP_CODEC_PARA_REG6_UNION */
#define GBBP_CODEC_PARA_REG6_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x1334)

/* �Ĵ���˵����
 bit[31:22]  ����
 bit[21:16]  �����AMRҵ���ϱ�
 bit[15:4]   ����
 bit[3:0]    �����PSҵ���ϱ�
   UNION�ṹ:  GBBP_CODEC_PARA_REG7_UNION */
#define GBBP_CODEC_PARA_REG7_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x123C)

/* �Ĵ���˵����
 bit[31:27]  PSҵ����״̬��״̬��������
 bit[26]     ����
 bit[25:20]  AHSҵ����״̬��״̬��������
             
 bit[19:17]  ����
 bit[16:12]  AFSҵ����״̬��״̬��������
             
 bit[11]     ����
 bit[10:8]   HARQ�ϲ�������״̬��״̬��������
 bit[7:4]    ҵ��������֪��״̬��״̬��������
 bit[3:0]    ����ҵ������ж�״̬��״̬��������
   UNION�ṹ:  GBBP_DEC_STATE_RPT1_UNION */
#define GBBP_DEC_STATE_RPT1_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x1338)

/* �Ĵ���˵����
 bit[31]     ��������æ״̬��������
 bit[30:28]  ����
 bit[27:24]  CCU����״̬��������
 bit[23]     ����
 bit[22:20]  ȥ���ģ�鹤��״̬��������
 bit[19:16]  ��֯ģ�鹤��״̬��������
 bit[15:14]  ����
 bit[13:12]  ���������״̬��״̬��������
 bit[11:8]   VTB������״̬��״̬��������
             
 bit[7:0]    ����
   UNION�ṹ:  GBBP_DEC_STATE_RPT2_UNION */
#define GBBP_DEC_STATE_RPT2_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x133C)

/* �Ĵ���˵����
   ��      ����[5:0] ��ʾPS��CS��ҵ��ĵ�4��q bit����͵֡bit ��ֵ
            [13:8] ��ʾPS��CS��ҵ��ĵ�3��q bit����͵֡bit ��ֵ
            [21:16] ��ʾPS��CS��ҵ��ĵ�2��q bit����͵֡bit ��ֵ
            [27:24] ��ʾPS��CS��ҵ��ĵ�1��q bit����͵֡bit ��ֵ
            ��������
   UNION�ṹ ���� */
#define GBBP_Q_BIT_RPT1_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x1340)

/* �Ĵ���˵����
   ��      ����[5:0] ��ʾPS��CS��ҵ��ĵ�8��q bit����͵֡bit ��ֵ
            [13:8] ��ʾPS��CS��ҵ��ĵ�7��q bit����͵֡bit ��ֵ
            [21:16] ��ʾPS��CS��ҵ��ĵ�6��q bit����͵֡bit ��ֵ
            [27:24] ��ʾPS��CS��ҵ��ĵ�5��q bit����͵֡bit ��ֵ
            ��������
   UNION�ṹ ���� */
#define GBBP_Q_BIT_RPT2_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x1344)

/* �Ĵ���˵����
 bit[31:20]  ����
 bit[19:16]  �������������������ϱ�
 bit[15:4]   ����
 bit[3:0]    �����жϴ����������ϱ�
   UNION�ṹ:  GBBP_DEC_INT_TOTAL_UNION */
#define GBBP_DEC_INT_TOTAL_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x1348)

/* �Ĵ���˵����
 bit[31]     1��ʶ������֡����о�ΪBFI��
             0��ʶ������֡����о�����BFI
             
 bit[30:23]  ����
 bit[22:16]  CS������PBER�ϱ�
 bit[15:8]   ����
 bit[7:0]    CS������RSQ_METRIC�ϱ�
   UNION�ṹ:  GBBP_BFI_RSQ_METRIC_RPT_UNION */
#define GBBP_BFI_RSQ_METRIC_RPT_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x134C)

/* �Ĵ���˵����
   ��      ����[5:0] ��ʾPS��ҵ��ĵ�1��USF ����ǰ��ֵ
            [13:8] ��ʾPS��ҵ��ĵ�2��USF ����ǰ��ֵ
            [21:16] ��ʾPS��ҵ��ĵ�3��USF ����ǰ��ֵ
            [27:24] ��ʾPS��ҵ��ĵ�4��USF ����ǰ��ֵ
   UNION�ṹ ���� */
#define GBBP_USF_CORR_SOFTDATA1_RPT_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x1500)

/* �Ĵ���˵����
   ��      ����[5:0] ��ʾPS��ҵ��ĵ�5��USF ����ǰ��ֵ
            [13:8] ��ʾPS��ҵ��ĵ�6��USF ����ǰ��ֵ
            [21:16] ��ʾPS��ҵ��ĵ�7��USF ����ǰ��ֵ
            [27:24] ��ʾPS��ҵ��ĵ�8��USF ����ǰ��ֵ
   UNION�ṹ ���� */
#define GBBP_USF_CORR_SOFTDATA2_RPT_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x1504)

/* �Ĵ���˵����
   ��      ����[5:0] ��ʾPS��ҵ��ĵ�9��USF ����ǰ��ֵ
            [13:8] ��ʾPS��ҵ��ĵ�10��USF ����ǰ��ֵ
            [21:16] ��ʾPS��ҵ��ĵ�11��USF ����ǰ��ֵ
            [27:24] ��ʾPS��ҵ��ĵ�12��USF ����ǰ��ֵ
   UNION�ṹ ���� */
#define GBBP_USF_CORR_SOFTDATA3_RPT_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x1508)

/* �Ĵ���˵����
   ��      ����[5:0] ��ʾPS��ҵ��ĵ�13��USF ����ǰ��ֵ
            [13:8] ��ʾPS��ҵ��ĵ�14��USF ����ǰ��ֵ
            [21:16] ��ʾPS��ҵ��ĵ�15��USF ����ǰ��ֵ
            [27:24] ��ʾPS��ҵ��ĵ�16��USF ����ǰ��ֵ
   UNION�ṹ ���� */
#define GBBP_USF_CORR_SOFTDATA4_RPT_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x150C)

/* �Ĵ���˵����
   ��      ����[5:0] ��ʾPS��ҵ��ĵ�17��USF ����ǰ��ֵ
            [13:8] ��ʾPS��ҵ��ĵ�18��USF ����ǰ��ֵ
            [21:16] ��ʾPS��ҵ��ĵ�19��USF ����ǰ��ֵ
            [27:24] ��ʾPS��ҵ��ĵ�20��USF ����ǰ��ֵ
   UNION�ṹ ���� */
#define GBBP_USF_CORR_SOFTDATA5_RPT_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x1510)

/* �Ĵ���˵����
   ��      ����[5:0] ��ʾPS��ҵ��ĵ�21��USF ����ǰ��ֵ
            [13:8] ��ʾPS��ҵ��ĵ�22��USF ����ǰ��ֵ
            [21:16] ��ʾPS��ҵ��ĵ�23��USF ����ǰ��ֵ
            [27:24] ��ʾPS��ҵ��ĵ�24��USF ����ǰ��ֵ
   UNION�ṹ ���� */
#define GBBP_USF_CORR_SOFTDATA6_RPT_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x1514)

/* �Ĵ���˵����
   ��      ����[5:0] ��ʾPS��ҵ��ĵ�25��USF ����ǰ��ֵ
            [13:8] ��ʾPS��ҵ��ĵ�26��USF ����ǰ��ֵ
            [21:16] ��ʾPS��ҵ��ĵ�27��USF ����ǰ��ֵ
            [27:24] ��ʾPS��ҵ��ĵ�28��USF ����ǰ��ֵ
   UNION�ṹ ���� */
#define GBBP_USF_CORR_SOFTDATA7_RPT_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x1518)

/* �Ĵ���˵����
   ��      ����[5:0] ��ʾPS��ҵ��ĵ�29��USF ����ǰ��ֵ
            [13:8] ��ʾPS��ҵ��ĵ�30��USF ����ǰ��ֵ
            [21:16] ��ʾPS��ҵ��ĵ�31��USF ����ǰ��ֵ
            [27:24] ��ʾPS��ҵ��ĵ�32��USF ����ǰ��ֵ
   UNION�ṹ ���� */
#define GBBP_USF_CORR_SOFTDATA8_RPT_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x151C)

/* �Ĵ���˵����
   ��      ����[5:0] ��ʾPS��ҵ��ĵ�33��USF ����ǰ��ֵ
            [13:8] ��ʾPS��ҵ��ĵ�34��USF ����ǰ��ֵ
            [21:16] ��ʾPS��ҵ��ĵ�35��USF ����ǰ��ֵ
            [27:24] ��ʾPS��ҵ��ĵ�36��USF ����ǰ��ֵ
   UNION�ṹ ���� */
#define GBBP_USF_CORR_SOFTDATA9_RPT_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x1520)

/* �Ĵ���˵����
 bit[31:6]   ����
 bit[5:4]    00��ʾIDLE������״̬��                                     01��ʾRECV������״̬��                                     10��ʾCHECK��У��״̬��                                     11��Ч״̬
             ������
             
 bit[3:2]    ����
 bit[1:0]    00��ʾIDLE������״̬��                                     01��ʾINIT����ʼ��״̬��                                     10��ʾCODE������״̬��                                     11��ʾINTE����֯״̬��
             ������
             
   UNION�ṹ:  GBBP_UL_CODE_STATE_RPT_UNION */
#define GBBP_UL_CODE_STATE_RPT_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x13B0)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ����Ա���ģ���ڲ�RAM�����뽻֯��洢RAM�������źţ�ֻ�迪��������һ�¼��ɣ��߼�������
   UNION�ṹ:  GBBP_UL_CODE_RAM_RST_UNION */
#define GBBP_UL_CODE_RAM_RST_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x13B4)

/* �Ĵ���˵����
 bit[31:23]  ����
 bit[22:16]  �������ݿ鳤��
 bit[15:7]   ����
 bit[6:0]    ������ʼ���ַ
   UNION�ṹ:  GBBP_UL_CODE_RAM_RST_CFG_UNION */
#define GBBP_UL_CODE_RAM_RST_CFG_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x13B8)

/* �Ĵ���˵����
 bit[31:29]  ����
 bit[28:16]  DRX�����л�ʱGTC��ʱgtc_timebase�����������ã�104M�Ӳ��ϣ�����GTC������DRX�����Ƿ���ͬ����������
 bit[15:7]   ����
 bit[6:0]    DRX�����л�ʱGTC��ʱFRAC�����������ã�104M�Ӳ��ϣ�����GTC������DRX�����Ƿ���ͬ����������
   UNION�ṹ:  GBBP_WAKE_TEST_QB_FRAC_RPT_UNION */
#define GBBP_WAKE_TEST_QB_FRAC_RPT_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x1224)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:24]  DRX�����л�ʱGTC��ʱT3�����������ã�104M�Ӳ��ϣ�����GTC������DRX�����Ƿ���ͬ����������
 bit[23:21]  ����
 bit[20:16]  DRX�����л�ʱGTC��ʱT2�����������ã�104M�Ӳ��ϣ�����GTC������DRX�����Ƿ���ͬ����������
 bit[15:11]  ����
 bit[10:0]   DRX�����л�ʱGTC��ʱT1�����������ã�104M�Ӳ��ϣ�����GTC������DRX�����Ƿ���ͬ����������
   UNION�ṹ:  GBBP_WAKE_TEST_T1_T2_T3_RPT_UNION */
#define GBBP_WAKE_TEST_T1_T2_T3_RPT_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x1228)

/* �Ĵ���˵����
 bit[31:27]  ����
 bit[26:16]  DRX�����л�ʱ����ʱGTC��FN_HIGH����ֵ������DRX������
 bit[15:11]  ����
 bit[10:0]   DRX�����л�ʱ����ʱGTC��FN_LOW����ֵ������DRX������
   UNION�ṹ:  GBBP_WAKE_GTC_FN_RPT_UNION */
#define GBBP_WAKE_GTC_FN_RPT_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x122C)

/* �Ĵ���˵����
   ��      ����A51��A52
            �ӽ����㷨�����Kcֵ��32bit
   UNION�ṹ ���� */
#define GBBP_CPU_A5KC_LOW_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x1450)

/* �Ĵ���˵����
   ��      ����A51��A52
            �ӽ����㷨�����Kcֵ��32bit
   UNION�ṹ ���� */
#define GBBP_CPU_A5KC_HIGH_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x1454)

/* �Ĵ���˵����
 bit[31:9]   ����
 bit[8]      �ڲ�A53�����㷨bit���˳�����ã�������Ϊ1
 bit[7:5]    ����
 bit[4]      �ڲ�A53�����㷨bit���˳�����ã�������Ϊ0
 bit[3:1]    ����
 bit[0]      �ڲ�A53�ӽ����㷨bit���˳�����ã�������Ϊ0
   UNION�ṹ:  GBBP_CPU_A5_LSB_SEQ_SEL_UNION */
#define GBBP_CPU_A5_LSB_SEQ_SEL_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x1458)

/* �Ĵ���˵����
   ��      �������һ�ν���ʱ��ʹ�õ��������ݣ������ã�
            [31]��   gsp_dl_gsm_alg_sel��
            [30:29]��gsp_dl_fn_adj_flag[1:0]��
            [28]��   gsp_dl_deciph_en��
            [27:22]��gtc_t3_cnt[5:0]��
            [21:0]�� ����ʱ�õ�{t1, t3, t2}��
   UNION�ṹ ���� */
#define GBBP_DECIPH_CFG_INFO1_CPU_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0x1470)

/* �Ĵ���˵����
   ��      �������һ�ν���ʱ��ʹ�õ��������ݣ������ã�
            [31:21]��gtc_t1_cnt [10:0]��
            [20:16]��gtc_t2_cnt [4:0]��
            [15:5] ������ʱ�õ�t1��
            [4:0]  ������ʱ�õ�t2��
   UNION�ṹ ���� */
#define GBBP_DECIPH_CFG_INFO2_CPU_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0x1474)

/* �Ĵ���˵����
   ��      �������һ�μ���ʱ��ʹ�õ��������ݣ������ã�
            [31]��   gsp_ul_gsm_alg_sel��
            [30:29]��gsp_ul_fn_adj_flag[1:0]��
            [28]��   gsp_ul_ciph_en��
            [27:22]��gtc_t3_cnt[5:0]��
            [21:0]�� ����ʱ�õ�{t1, t3, t2}��
   UNION�ṹ ���� */
#define GBBP_CIPH_CFG_INFO1_CPU_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x1478)

/* �Ĵ���˵����
   ��      �������һ�μ���ʱ��ʹ�õ��������ݣ������ã�
            [31:21]��gtc_t1_cnt [10:0]��
            [20:16]��gtc_t2_cnt [4:0]��
            [15:5] ������ʱ�õ�t1��
            [4:0]  ������ʱ�õ�t2��
   UNION�ṹ ���� */
#define GBBP_CIPH_CFG_INFO2_CPU_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x147C)

/* �Ĵ���˵����
 bit[31:23]  ����
 bit[22:0]   2G�½���4G������GAP���ȡ���λ��QB��
             1��2GΪ��ģʱ����ϵͳGAP��󳤶�Ϊ���13*51-2֡���ң�����3305000Qb��
             2��cpu_2g4_gap_length�����÷�Χ��0~3305000QB��
             3��cpu_2g4_gap_length + cpu_2g4_int0_int1_dist�Ľ������Ӧ����23'h7f_ffff��
   UNION�ṹ:  GBBP_CPU_2G4_GAP_LENGTH_UNION */
#define GBBP_CPU_2G4_GAP_LENGTH_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x1248)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1]      �����һ֡��Ҫ����2G��4G�����ڵ�ǰ֡������ʱ϶�����ø��ź�Ϊ1��������cpu_int0_gen_qb�������㡣
 bit[0]      2G�½���4G�����ڼ䣬GPHY��ǰֹͣoccasion���źţ������źš�GBBP�յ����źź�����ֹͣgap_cnt���������ϱ�int2�������жϣ���������ͨ������ָʾ�ź�wg_intrasys_valid_delay�������㡣
   UNION�ṹ:  GBBP_CPU_2G4_GAP_STOP_UNION */
#define GBBP_CPU_2G4_GAP_STOP_ADDR                    (SOC_BBP_GSM_BASE_ADDR + 0x124C)

/* �Ĵ���˵����
 bit[31:20]  ����
 bit[19:16]  g_intrasys_valid_delay�����g_intrasys_valid���ӳ�ʱ�䡣֧���ӳ�1~3��SSIд�������ڣ���֤LTE�����һ����Ƶ����д�ꡣд��һ��SSI�֣�����ʱ��������27*52.08 = 1406.16 ns��Լ1.5QB ��Ĭ��ֵ����3��QB����
 bit[15:12]  ����
 bit[11:0]   2G��4Gʱ���ж�0���ж�1�ļ��ʱ�䡣��λ��QB��
             Ĭ��ֵ��108QB��Լ100us��
   UNION�ṹ:  GBBP_CPU_2G4_DIST_UNION */
#define GBBP_CPU_2G4_DIST_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x1250)

/* �Ĵ���˵����
 bit[31:26]  ����
 bit[25:24]  cpu_2g4_int0_en�źŴ����ļ����������ڹ۲�cpu_2g4_int0_en�ź��Ƿ���Ч�������Ч����ÿ�θü������Լ�1��ѭ������
 bit[23:18]  ����
 bit[17:16]  cpu_2g4_gap_stop�źŴ����ļ����������ڹ۲�cpu_2g4_gap_stop�ź��Ƿ���Ч�������Ч����ÿ�θü������Լ�1��ѭ������
 bit[15:13]  ����
 bit[12:0]   �����һ֡��Ҫ����2G��4G�����ڵ�ǰ֡������ʱ϶�����ø��źţ���ʾ����֡֡ͷ֮��cpu_2g4_int0_gen_qb��QB�������ж�0
   UNION�ṹ:  GBBP_CPU_2G4_INT0_GEN_QB_UNION */
#define GBBP_CPU_2G4_INT0_GEN_QB_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x1254)

/* �Ĵ���˵����
 bit[31:27]  ����
 bit[26:16]  2G��4Gʱ���ж�0��Ӧ��FN��11λ
 bit[15:13]  ����
 bit[12:0]   2G��4Gʱ���ж�0��Ӧ��timebase����λ��QB
   UNION�ṹ:  GBBP_CPU_2G4_INT0_TIMING_UNION */
#define GBBP_CPU_2G4_INT0_TIMING_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x1240)

/* �Ĵ���˵����
 bit[31:27]  ����
 bit[26:16]  2G��4Gʱ���ж�2��Ӧ��FN��11λ
 bit[15:13]  ����
 bit[12:0]   2G��4Gʱ���ж�2��Ӧ��timebase����λ��QB
   UNION�ṹ:  GBBP_CPU_2G4_INT2_TIMING_UNION */
#define GBBP_CPU_2G4_INT2_TIMING_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x1244)

/* �Ĵ���˵����
 bit[31:26]  ����
 bit[25:16]  FB-AFC�㷨��λ����ֵ�ο����ޣ�����ֵ760��
 bit[15:10]  ����
 bit[9:0]    FB-AFC�㷨��λ����ֵ�ο����ޣ�����ֵ500������300,400,500��
   UNION�ṹ:  GBBP_FB_AFC_PHASE_THRESHOLD_CFG_UNION */
#define GBBP_FB_AFC_PHASE_THRESHOLD_CFG_ADDR          (SOC_BBP_GSM_BASE_ADDR + 0x1230)

/* �Ĵ���˵����
 bit[31:26]  ����
 bit[25:16]  FB-AFC�㷨ϵ��fcut�����ֵ������������˲������λ����ֵ������λ����ֵ�Ĳο����ޣ���ϵ��fcut��ֵ�͵��ڴ����ֵ������ֵ1023��
 bit[15:10]  ����
 bit[9:0]    FB-AFC�㷨ϵ��fcut����Сֵ������������˲������λ����ֵС����λ����ֵ�ο����ޣ���ϵ��fcut��ֵ�͵��ڴ���Сֵ������ֵ51��
   UNION�ṹ:  GBBP_FB_FCUT_THRESHOLD_CFG_UNION */
#define GBBP_FB_FCUT_THRESHOLD_CFG_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x1234)

/* �Ĵ���˵����
 bit[31:26]  ����
 bit[25:16]  һ�׻�·�˲�����ʼ�����������ã�1023��
 bit[15]     ����
 bit[14:12]  �Գ����Ʊ����������䷶Χ0~7���������ã�4��
 bit[11:8]   Fcutֵ�̶�ʹ��FCutInit�ĸ���FB���롣���䷶Χ��5~10���������ã�10��
 bit[7:2]    ����
 bit[1:0]    FB-AFC�㷨���˲�ϵ��ѡ��
             0��1/32��
             1��1/16��
             2��1/8��
             3��1/4��
             ����ֵ1/32��
   UNION�ṹ:  GBBP_FB_AFC_ALPHA_SEL_UNION */
#define GBBP_FB_AFC_ALPHA_SEL_ADDR                    (SOC_BBP_GSM_BASE_ADDR + 0x1238)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:24]  ����SB����BSIC�ϱ���
 bit[23:18]  ����
 bit[17:16]  111�Ż��㷨������SB����CRC����BSICֵ��ͬ���ܴ���
             0��4�Σ�
             1��5�Σ�
             2��6�Σ�
             3��7�Ρ�
 bit[15:6]   ����
 bit[5:4]    111�Ż��㷨��FB-AFC����������SB����CRC����Ĵ�����ȡֵ��Χ0~3��
 bit[3:1]    ����
 bit[0]      111�����Ż�ģʽʹ�ܣ�1��־���Ż�ʹ�ܣ�0��־�ر��Ż�ʹ�ܣ�����001 111������
   UNION�ṹ:  GBBP_SRCH_OPT_CFG_UNION */
#define GBBP_SRCH_OPT_CFG_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x1480)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  RSSI ��������3����λdBm���Ƽ�-45
 bit[15:8]   RSSI ��������2����λdBm���Ƽ�-65
 bit[7:0]    RSSI ��������1����λdBm���Ƽ�-93
   UNION�ṹ:  GBBP_R2_RSSI1234_THRESHOLD_UNION */
#define GBBP_R2_RSSI1234_THRESHOLD_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x5204)

/* �Ĵ���˵����
 bit[31:24]  RSSI ��������7����λdBm���ݲ�ʹ�ã�Ĭ��ֵ-1
 bit[23:16]  RSSI ��������6����λdBm���ݲ�ʹ�ã�Ĭ��ֵΪ-1
 bit[15:8]   RSSI ��������5����λdBm���ݲ�ʹ�ã�Ĭ��ֵΪ-1
 bit[7:0]    RSSI ��������4����λdBm���ݲ�ʹ�ã�Ĭ��ֵΪ-1
   UNION�ṹ:  GBBP_R2_RSSI4567_THRESHOLD_UNION */
#define GBBP_R2_RSSI4567_THRESHOLD_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x5208)

/* �Ĵ���˵����
 bit[31]     ����AGC����ģʽѡ���ź�
             0������AGC����ģʽ���ղ�������gsp_fast_agc_modeѡ��
             1������AGC����ģʽ���ղ�������gsp_agc_measure_modeѡ��
 bit[30:25]  ����
 bit[24]     ���ͨ��ֱ��ƫ������ϸ������·���ܣ��ߵ�ƽ��Ч�����ź���Чʱ����ʾ����ϸ�������Խ������ݽ��з�������
 bit[23:16]  ����
 bit[15:12]  RSSI ���ͷ�Χ����λdBm��Ĭ��3��
 bit[11:9]   ����
 bit[8]      ���������ͨ��ֱ��ƫ������ϸ������·���ܣ��ߵ�ƽ��Ч�����ź���Чʱ����ʾ����ϸ�������Խ������ݽ��з�������
 bit[7:5]    ����
 bit[4:0]    ����AGC��������ÿ��֮��ȴ�ʱ�䣬��λsymbol��Ĭ��8��
   UNION�ṹ:  GBBP_AGC_WAIT_LEN_GTH_UNION */
#define GBBP_AGC_WAIT_LEN_GTH_ADDR                    (SOC_BBP_GSM_BASE_ADDR + 0x520C)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  RSSI ��������3����λdBm���Ƽ�-45
 bit[15:8]   RSSI ��������2����λdBm���Ƽ�-65
 bit[7:0]    RSSI ��������1����λdBm���Ƽ�-93
   UNION�ṹ:  GBBP_R3_RSSI1234_THRESHOLD_UNION */
#define GBBP_R3_RSSI1234_THRESHOLD_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x5210)

/* �Ĵ���˵����
 bit[31:24]  RSSI ��������7����λdBm���ݲ�ʹ�ã�Ĭ��ֵΪ-1
 bit[23:16]  RSSI ��������6����λdBm���ݲ�ʹ�ã�Ĭ��ֵΪ-1
 bit[15:8]   RSSI ��������5����λdBm���ݲ�ʹ�ã�Ĭ��ֵΪ-1
 bit[7:0]    RSSI ��������4����λdBm���ݲ�ʹ�ã�Ĭ��ֵΪ-1
   UNION�ṹ:  GBBP_R3_RSSI4567_THRESHOLD_UNION */
#define GBBP_R3_RSSI4567_THRESHOLD_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x521C)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:16]  ��·����ϸ����ƫ�üĴ���������λ���޷���������Ҳ���ǵ�ǰ��λ��ֱ��������������Ϊֱ��ƫ��У׼�Ĳο�ֵ������14bit�źŷֱ�ռ��IMI���ߵ�[29:16]��[13:0]����14bitΪI·�������14bitΪQ·�����
 bit[15:14]  ����
 bit[13:0]   ��·����ϸ����ƫ�üĴ���������λ���޷���������Ҳ���ǵ�ǰ��λ��ֱ��������������Ϊֱ��ƫ��У׼�Ĳο�ֵ������14bit�źŷֱ�ռ��IMI���ߵ�[29:16]��[13:0]����14bitΪI·�������14bitΪQ·�����
   UNION�ṹ:  GBBP_DC_IQ_REMOVE_RPT_UNION */
#define GBBP_DC_IQ_REMOVE_RPT_ADDR                    (SOC_BBP_GSM_BASE_ADDR + 0x5220)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:16]  ʱ϶ǰ����Q·ֱ��ƫ���ϱ�
 bit[15:14]  ����
 bit[13:0]   ʱ϶ǰ����I·ֱ��ƫ���ϱ�
   UNION�ṹ:  GBBP_DC_IQ_BURST_REMOVE_RPT_UNION */
#define GBBP_DC_IQ_BURST_REMOVE_RPT_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x5224)

/* �Ĵ���˵����
 bit[31:19]  ����
 bit[18:0]   SB���ǰ�ز�����ֵ�ϱ�
   UNION�ṹ:  GBBP_SB_THRES_C_UNION */
#define GBBP_SB_THRES_C_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x5230)

/* �Ĵ���˵����
 bit[31:19]  ����
 bit[18:0]   SB���ǰ��������ֵ�ϱ�
   UNION�ṹ:  GBBP_SB_THRES_I_UNION */
#define GBBP_SB_THRES_I_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x5234)

/* �Ĵ���˵����
 bit[31]     �����ٲ�����־��1��ʾ��ǰʱ���ٲ�����0��ʾ��ǰ�����ٲ�����
 bit[30:27]  ����
 bit[26:24]  ��ǰAAGC��λ�ϱ���
 bit[23:20]  ����
 bit[19:8]   RSSIֵ����λ��0.125dBm���ϱ���CPU����ֵ���ǿտڵ�RSSIֵ��
 bit[7:3]    ����
 bit[2:0]    AGC�����������档�ڿ���ģʽ���һ�ֺ�����ģʽ��ͳ�ƽ������ϱ���CPU��
   UNION�ṹ:  GBBP_AAGC_NEXT_GAIN_UNION */
#define GBBP_AAGC_NEXT_GAIN_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x5250)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  ��ǰ������RSSI��Ӧ��Ƶ��ţ�[27:26]Ϊband�ţ�band����Ƶ�εĹ�ϵ������Լ����壬[25:16]Ϊband�ڵ�Ƶ��ţ���ֵ��GTCָ�����ã�{GSP_RSSI_FRQ_HIGH_ADDR,GSP_RSSI_FRQ_LOW_ADDR},BBP������ʱ���ڲ����ж�һ���ϱ���
 bit[15:13]  ����
 bit[12:0]   �����ж�ʱ��TDMA֡QBֵ��
   UNION�ṹ:  GBBP_RSSI_QB_FRQ_UNION */
#define GBBP_RSSI_QB_FRQ_ADDR                         (SOC_BBP_GSM_BASE_ADDR + 0x5254)

/* �Ĵ���˵����
 bit[31:23]  ����
 bit[22:0]   DRSSI���������ǰ�����ϱ���
   UNION�ṹ:  GBBP_DRSSI_ENERGY_RPT_UNION */
#define GBBP_DRSSI_ENERGY_RPT_ADDR                    (SOC_BBP_GSM_BASE_ADDR + 0x5258)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  RSSIֵ����λ0.125dBm������ǿտ��ź�������Ϊ���ٲ����ڶ���RSSI�ϱ���
 bit[15:12]  ����
 bit[11:0]   RSSIֵ����λ0.125dBm������ǿտ��ź�������Ϊ���ٲ�����һ��RSSI�ϱ���
   UNION�ṹ:  GBBP_AGC_FAST1_2_RSSI_CPU_UNION */
#define GBBP_AGC_FAST1_2_RSSI_CPU_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0x525C)

/* �Ĵ���˵����
 bit[31:22]  ����
 bit[21:16]  NBҵ�������ж�����TDMA֡��ģ51����ֵ
 bit[15:6]   ����
 bit[5:0]    AGC�����ж�����TDMA֡��ģ51����ֵ
   UNION�ṹ:  GBBP_AGC_DEC_INT_T3_FN_UNION */
#define GBBP_AGC_DEC_INT_T3_FN_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5214)

/* �Ĵ���˵����
 bit[31:22]  ����
 bit[21:16]  ����ж�����TDMA֡��ģ51����ֵ
 bit[15:13]  ����
 bit[12:0]   ����ж�����TDMA QB����ֵ
   UNION�ṹ:  GBBP_DEM_INT_FN_QB_UNION */
#define GBBP_DEM_INT_FN_QB_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x5218)

/* �Ĵ���˵����
 bit[31]     8bit�����߿��ź�дʹ��ָʾ�ź�
 bit[30:8]   ����
 bit[7:0]    �����߿�CPU�ӿ����ã�����
             bit0��Ӧrf_tcvr_on,����ƵоƬ����ʹ���ź�
             bit1��Ӧrf_tx_en,����Ƶ���з��͹���ʹ���ź�
             bit2��Ӧrf_rst_n,����Ƶ��λ�����ź�
             bit3��Ӧabb_rxa_en,��ABB RXAͨ��ʹ���ź�
             bit4��Ӧabb_rxb_en,��ABB RXBͨ��ʹ���ź�
             bit5��Ӧabb_tx_en,��ABB TXͨ��ʹ���ź�
             bit6��Ӧgapc_en����Auxdacͨ��ʹ���ź�
   UNION�ṹ:  GBBP_CPU_EXT_LINE_CTRL_UNION */
#define GBBP_CPU_EXT_LINE_CTRL_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5E04)

/* �Ĵ���˵����
 bit[31:7]   ����
 bit[6:0]    �����߿�ʵ��״̬�������á�
             bit0��Ӧrf_tcvr_on,����ƵоƬ����ʹ���ź�
             bit1��Ӧrf_tx_en,����Ƶ���з��͹���ʹ���ź�
             bit2��Ӧrf_rst_n,����Ƶ��λ�����ź�
             bit3��Ӧabb_rxa_en,��ABB RXAͨ��ʹ���ź�
             bit4��Ӧabb_rxb_en,��ABB RXBͨ��ʹ���ź�
             bit5��Ӧabb_tx_en,��ABB TXͨ��ʹ���ź�
             bit6��Ӧgapc_en����Auxdacͨ��ʹ���ź�
   UNION�ṹ:  GBBP_CPU_GSP_EXT_LINE_STATE_RPT_UNION */
#define GBBP_CPU_GSP_EXT_LINE_STATE_RPT_ADDR          (SOC_BBP_GSM_BASE_ADDR + 0x5E08)

/* �Ĵ���˵����
 bit[31]     cpu_line01_sel_ctrl��Ч�����źţ��������ź�дΪ1��cpu_line01_sel_ctrl��Ӧ��������Ч���߼������㡣
             ע��Ҫ��bit[3:0]�������úš�
 bit[30:4]   ����
 bit[3:0]    bit0��Ӧ��ģMIPI�ʹ�ģMIPIͨ������ѡ��
             bit1��ӦAUXDAC0��AUXDAC1����ѡ��
             bit2��ӦABB CH0��ABB CH1ͨ������ѡ������V9R1����������ABBͨ������˸�����Ĭ������Ϊ0������Ķ���
             bit3��Ӧ��ģRFIC���ģRFICͨ������ѡ��
             GΪ��ģʱ������Ϊ4��d0��GΪ��ģʱ������Ϊ4��d9��
   UNION�ṹ:  GBBP_CPU_LINE01_SEL_CFG_UNION */
#define GBBP_CPU_LINE01_SEL_CFG_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x5E0C)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    ͨ��ѡ���ź�ʵ��״̬�������á�
             bit0��gtc_mipi01_sel��
             bit1��gtc_auxdac01_sel��
             bit2��gtc_abb01_sel��
             bit3��gtc_rf01_sel��
   UNION�ṹ:  GBBP_CPU_LINE01_SEL_STATE_RPT_UNION */
#define GBBP_CPU_LINE01_SEL_STATE_RPT_ADDR            (SOC_BBP_GSM_BASE_ADDR + 0x5E10)

/* �Ĵ���˵����
 bit[31]     AGCģ������ǰ��ͨ���������ֵ��RXCORR�����洢RAM��DC_OFFSET�洢RAM TDMA֡ͷƹ���л�ʹ��
             1��ʾ����ƹ���л�
             0��ʾ������ƹ���л����̶�Ϊƹҳ�������ź�Ϊ1ʱ���߼��ڲ���TDMA֡ͷ�Զ��л�ƹ�ұ�־��
 bit[30:0]   ����
   UNION�ṹ:  GBBP_CPU_OFC_RXCM_REG_UNION */
#define GBBP_CPU_OFC_RXCM_REG_ADDR                    (SOC_BBP_GSM_BASE_ADDR + 0x5360)

/* �Ĵ���˵����
 bit[31:13]  ����
 bit[12]     ����ͨ��ֱ��ƫ������ϸ������·���ܣ��ߵ�ƽ��Ч��
             ���ź���Чʱ���൱������ϸ�������Խ������ݽ��з�������
 bit[11:9]   ����
 bit[8]      ��������ѡ�����ã����ź���Ҫ��֡ͷ���档
             0����ʾѡ��1��symbol�е�1/3�����飻
             1����ʾѡ��1��symbol�е�2/4�����顣
 bit[7:6]    ����
 bit[5:4]    bit1:1��ʾʱӲ�����о�ģʽ��0��ʾʱ�������ģʽ����bitΪ0ʱ��bit0�������Ч������������żѡ���źţ�0��ʾѡ����������ż·���ݣ�1��ʾѡ������������·���ݡ�����8PSK�����������2'b11����ʱ����ֵ���������á�������ģʽ����������Ϊ2'bx1ģʽ��
 bit[3:0]    ����
   UNION�ṹ:  GBBP_CPU_SAMPLE_REG_UNION */
#define GBBP_CPU_SAMPLE_REG_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x536C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      AGCֱ��ƫִRAM��ͨ������RAM�ֶ��л�ָʾ�źţ����ź�Ϊ�����źţ������㡣
   UNION�ṹ:  GBBP_CPU_AGC_RAM_SWITCH_IND_UNION */
#define GBBP_CPU_AGC_RAM_SWITCH_IND_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x5370)

/* �Ĵ���˵����
 bit[31:25]  ����
 bit[24:16]  ���ǿ�����õ�DRSSIֵ����λ0.25dBm��
 bit[15:9]   ����
 bit[8:0]    DRSSIֵ�ϱ������ӦΪABB����źŵ���������λ0.25dBm��
   UNION�ṹ:  GBBP_DAGC_MULFACTOR_FIX_UNION */
#define GBBP_DAGC_MULFACTOR_FIX_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x537C)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:0]   �������߿�������ģʽ�µ�1��SPI�����֣�����SPI��������Ϸ�ʽ��μ������Ƶ�ֲᡣ���ּ�������ѡ��������gsp_rf_gain_word_sel��
   UNION�ṹ:  GBBP_CPU_MAIN_GAIN1_SPI_DATA_UNION */
#define GBBP_CPU_MAIN_GAIN1_SPI_DATA_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x5584)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:0]   �������߿�������ģʽ�µ�2��SPI�����֣�����SPI��������Ϸ�ʽ��μ������Ƶ�ֲᡣ���ּ�������ѡ��������gsp_rf_gain_word_sel��
   UNION�ṹ:  GBBP_CPU_MAIN_GAIN2_SPI_DATA_UNION */
#define GBBP_CPU_MAIN_GAIN2_SPI_DATA_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x5588)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:0]   �������߿�������ģʽ�µ�3��SPI�����֣�����SPI��������Ϸ�ʽ��μ������Ƶ�ֲᡣ���ּ�������ѡ��������gsp_rf_gain_word_sel��
   UNION�ṹ:  GBBP_CPU_MAIN_GAIN3_SPI_DATA_UNION */
#define GBBP_CPU_MAIN_GAIN3_SPI_DATA_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x558C)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:0]   �������߿�������ģʽ�µ�4��SPI�����֣�����SPI��������Ϸ�ʽ��μ������Ƶ�ֲᡣ���ּ�������ѡ��������gsp_rf_gain_word_sel��
   UNION�ṹ:  GBBP_CPU_MAIN_GAIN4_SPI_DATA_UNION */
#define GBBP_CPU_MAIN_GAIN4_SPI_DATA_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x5590)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:0]   �������߿�������ģʽ�µ�5��SPI�����֣�����SPI��������Ϸ�ʽ��μ������Ƶ�ֲᡣ���ּ�������ѡ��������gsp_rf_gain_word_sel��
   UNION�ṹ:  GBBP_CPU_MAIN_GAIN5_SPI_DATA_UNION */
#define GBBP_CPU_MAIN_GAIN5_SPI_DATA_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x5594)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:0]   �������߿�������ģʽ�µ�6��SPI�����֣�����SPI��������Ϸ�ʽ��μ������Ƶ�ֲᡣ���ּ�������ѡ��������gsp_rf_gain_word_sel��
   UNION�ṹ:  GBBP_CPU_MAIN_GAIN6_SPI_DATA_UNION */
#define GBBP_CPU_MAIN_GAIN6_SPI_DATA_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x5598)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:0]   �������߿�������ģʽ�µ�7��SPI�����֣�����SPI��������Ϸ�ʽ��μ������Ƶ�ֲᡣ���ּ�������ѡ��������gsp_rf_gain_word_sel��
   UNION�ṹ:  GBBP_CPU_MAIN_GAIN7_SPI_DATA_UNION */
#define GBBP_CPU_MAIN_GAIN7_SPI_DATA_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x559C)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:0]   �������߿�������ģʽ�µ�8��SPI�����֣�����SPI��������Ϸ�ʽ��μ������Ƶ�ֲᡣ���ּ�������ѡ��������gsp_rf_gain_word_sel��
   UNION�ṹ:  GBBP_CPU_MAIN_GAIN8_SPI_DATA_UNION */
#define GBBP_CPU_MAIN_GAIN8_SPI_DATA_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x55A0)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:0]   �ּ����߿�������ģʽ�µ�1��SPI�����֣�����SPI��������Ϸ�ʽ��μ������Ƶ�ֲᡣ���ּ�������ѡ��������gsp_rf_gain_word_sel��
   UNION�ṹ:  GBBP_CPU_DIV_GAIN1_SPI_DATA_UNION */
#define GBBP_CPU_DIV_GAIN1_SPI_DATA_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x55A4)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:0]   �ּ����߿�������ģʽ�µ�2��SPI�����֣�����SPI��������Ϸ�ʽ��μ������Ƶ�ֲᡣ���ּ�������ѡ��������gsp_rf_gain_word_sel��
   UNION�ṹ:  GBBP_CPU_DIV_GAIN2_SPI_DATA_UNION */
#define GBBP_CPU_DIV_GAIN2_SPI_DATA_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x55A8)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:0]   �ּ����߿�������ģʽ�µ�3��SPI�����֣�����SPI��������Ϸ�ʽ��μ������Ƶ�ֲᡣ���ּ�������ѡ��������gsp_rf_gain_word_sel��
   UNION�ṹ:  GBBP_CPU_DIV_GAIN3_SPI_DATA_UNION */
#define GBBP_CPU_DIV_GAIN3_SPI_DATA_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x55AC)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:0]   �ּ����߿�������ģʽ�µ�4��SPI�����֣�����SPI��������Ϸ�ʽ��μ������Ƶ�ֲᡣ���ּ�������ѡ��������gsp_rf_gain_word_sel��
   UNION�ṹ:  GBBP_CPU_DIV_GAIN4_SPI_DATA_UNION */
#define GBBP_CPU_DIV_GAIN4_SPI_DATA_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x55B0)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:0]   �ּ����߿�������ģʽ�µ�5��SPI�����֣�����SPI��������Ϸ�ʽ��μ������Ƶ�ֲᡣ���ּ�������ѡ��������gsp_rf_gain_word_sel��
   UNION�ṹ:  GBBP_CPU_DIV_GAIN5_SPI_DATA_UNION */
#define GBBP_CPU_DIV_GAIN5_SPI_DATA_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x55B4)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:0]   �ּ����߿�������ģʽ�µ�6��SPI�����֣�����SPI��������Ϸ�ʽ��μ������Ƶ�ֲᡣ���ּ�������ѡ��������gsp_rf_gain_word_sel��
   UNION�ṹ:  GBBP_CPU_DIV_GAIN6_SPI_DATA_UNION */
#define GBBP_CPU_DIV_GAIN6_SPI_DATA_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x55B8)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:0]   �ּ����߿�������ģʽ�µ�7��SPI�����֣�����SPI��������Ϸ�ʽ��μ������Ƶ�ֲᡣ���ּ�������ѡ��������gsp_rf_gain_word_sel��
   UNION�ṹ:  GBBP_CPU_DIV_GAIN7_SPI_DATA_UNION */
#define GBBP_CPU_DIV_GAIN7_SPI_DATA_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x55BC)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:0]   �ּ����߿�������ģʽ�µ�8��SPI�����֣�����SPI��������Ϸ�ʽ��μ������Ƶ�ֲᡣ���ּ�������ѡ��������gsp_rf_gain_word_sel��
   UNION�ṹ:  GBBP_CPU_DIV_GAIN8_SPI_DATA_UNION */
#define GBBP_CPU_DIV_GAIN8_SPI_DATA_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x55C0)

/* �Ĵ���˵����
 bit[31]     NB-AFC���Ʒ�ʽѡ��
             0��GTC���ƣ�
             1��CPU���ƣ�
             Ĭ��CPU���ơ�
 bit[30:2]   ����
 bit[1]      ���׻������ٽ׶ο��ƣ�
             0����ʾ�������ٸ��٣�
             1����ʾ���ÿ��ٸ��١�
 bit[0]      һ�׻�����׻�ѡ������źţ�
             0��ѡ��һ�׻���
             1��ѡ����׻���
   UNION�ṹ:  GBBP_NB_AFC_LOOP_SWITCH_UNION */
#define GBBP_NB_AFC_LOOP_SWITCH_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x5340)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9:0]    AFC Kֵ������Ĭ��ֵΪ10��d84��TCXO�����±���Ĭ��ֵ��DCXO�����¸���ʵ��ϵͳ���е�����
   UNION�ṹ:  GBBP_ADDR_AFC_K_VALUE_UNION */
#define GBBP_ADDR_AFC_K_VALUE_ADDR                    (SOC_BBP_GSM_BASE_ADDR + 0x5E00)


#define GBBP_ADDR_NB_AFC_LOOP_SLOW_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x5E14)


#define GBBP_ADDR_NB_AFC_LOOP_FAST_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x5E18)

/* �Ĵ���˵����
   ��      �������׻���ǰNB-AFC��·�˲��ۼ������ϱ�ֵ
   UNION�ṹ ���� */
#define GBBP_AFC_LOOP2_RPT_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x5E1C)

/* �Ĵ���˵����
   ��      �����ϵ����׻�NB-AFC��·�˲��ۼ���������ֵ��
            ������cpu_afc_init_enΪ1����Ч��
   UNION�ṹ ���� */
#define GBBP_CPU_AFC_LOOP2_CFG_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5E20)

/* �Ĵ���˵����
 bit[31:12]  ����
 bit[11:0]   ���ν���ж�ʱ�̶�Ӧ��Ƶ��
   UNION�ṹ:  GBBP_ADDR_DEM_INT_FRQ_UNION */
#define GBBP_ADDR_DEM_INT_FRQ_ADDR                    (SOC_BBP_GSM_BASE_ADDR + 0x5E2C)

/* �Ĵ���˵����
 bit[31:29]  ����
 bit[28:16]  ���������ж��ϱ�ʱ�ɶ�Ӧ��TDMA QB��Ϣ
 bit[15:12]  ����
 bit[11:0]   ���������ж��ϱ�ʱ�̶�Ӧ��Ƶ����Ϣ
   UNION�ṹ:  GBBP_ADDR_DEC_INT_FREQ_UNION */
#define GBBP_ADDR_DEC_INT_FREQ_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5E30)

/* �Ĵ���˵����
 bit[31:22]  ����
 bit[21:16]  [21:16] 6��b0 RO �����ж��ϱ�ʱ�̶�Ӧ��TDMA֡�ţ�gtc_t3_cnt��
 bit[15:13]  ����
 bit[12:0]   ���������ж��ϱ�ʱ�̶�Ӧ��TDMA QB
   UNION�ṹ:  GBBP_ADDR_SRCH_INT_TDMA_QB_UNION */
#define GBBP_ADDR_SRCH_INT_TDMA_QB_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x5E34)

/* �Ĵ���˵����
   ��      �����������һ��BURST���ǰ���BURST��MQƽ���ķ���ֵ�ϱ�����ӦBURSTΪDummyBurst�����ϱ���Ϣ��׼ȷ������ʹ�á�
   UNION�ṹ ���� */
#define GBBP_MQ1_FENZI5_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x530C)

/* �Ĵ���˵����
   ��      �����������һ��BURST���ǰ���BURST��MQƽ���ķ�ĸֵ�ϱ�����ӦBURSTΪDummyBurst�����ϱ���Ϣ��׼ȷ������ʹ�á�
   UNION�ṹ ���� */
#define GBBP_MQ1_FENMU5_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x5310)

/* �Ĵ���˵����
   ��      �����������һ��BURST�������BURST��MQƽ���ķ���ֵ�ϱ�����ӦBURSTΪDummyBurst�����ϱ���Ϣ��׼ȷ������ʹ�á�
   UNION�ṹ ���� */
#define GBBP_MQ2_FENZI5_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x5314)

/* �Ĵ���˵����
   ��      �����������һ��BURST�������BURST��MQƽ���ķ�ĸֵ�ϱ�����ӦBURSTΪDummyBurst�����ϱ���Ϣ��׼ȷ������ʹ�á�
   UNION�ṹ ���� */
#define GBBP_MQ2_FENMU5_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x5318)

/* �Ĵ���˵����
   ��      ������������һ��BURST���ǰ���BURST��MQƽ���ķ���ֵ�ϱ�����ӦBURSTΪDummyBurst�����ϱ���Ϣ��׼ȷ������ʹ�á�
   UNION�ṹ ���� */
#define GBBP_MQ1_FENZI6_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x531C)

/* �Ĵ���˵����
   ��      ������������һ��BURST���ǰ���BURST��MQƽ���ķ�ĸֵ�ϱ�����ӦBURSTΪDummyBurst�����ϱ���Ϣ��׼ȷ������ʹ�á�
   UNION�ṹ ���� */
#define GBBP_MQ1_FENMU6_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x5320)

/* �Ĵ���˵����
   ��      ������������һ��BURST�������BURST��MQƽ���ķ���ֵ�ϱ�����ӦBURSTΪDummyBurst�����ϱ���Ϣ��׼ȷ������ʹ�á�
   UNION�ṹ ���� */
#define GBBP_MQ2_FENZI6_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x5324)

/* �Ĵ���˵����
   ��      ������������һ��BURST�������BURST��MQƽ���ķ�ĸֵ�ϱ�����ӦBURSTΪDummyBurst�����ϱ���Ϣ��׼ȷ������ʹ�á�
   UNION�ṹ ���� */
#define GBBP_MQ2_FENMU6_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x5328)

/* �Ĵ���˵����
 bit[31]     ����
 bit[30:0]   ��ȡʱ��ǰ�����burst��Ӧ���ز�����ֵ���޷�������
   UNION�ṹ:  GBBP_VALPP_CARRIER_ENERGY4_UNION */
#define GBBP_VALPP_CARRIER_ENERGY4_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x532C)

/* �Ĵ���˵����
 bit[31:26]  ����
 bit[25:0]   ��ȡʱ��ǰ�����burst��Ӧ�ĸ�������ֵ���޷�������
   UNION�ṹ:  GBBP_VALPP_INTERFERE_ENERGY4_UNION */
#define GBBP_VALPP_INTERFERE_ENERGY4_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x5330)

/* �Ĵ���˵����
 bit[31]     ��ȡʱ�̵���������Ϣ��Ч��־�������һ��NB���ʱ���ñ�־��1,CPU��ȡ���BURST����ϱ���Ϣ��Ӧ��ͨ��дbit30�Ը�bit���㣬ָʾ����Ϣ�Ѿ���ȡ��
 bit[30]     ��demod_info_valid_flag4���㡣д1���㡣
 bit[29:28]  ��ȡʱ��ǰ�ĵ����BURST��Ӧ��һ���о��ĵ��Ʒ�ʽ��
             0��GMSK���ƣ�
             1��8PSK���ƣ�
             2��DummyBurst��
             �üĴ�������ʹ�á�
 bit[27:25]  ����
 bit[24]     ��ȡʱ�̵����burst�Ƿ�Ϊ�Ƿ�����ָʾ��1��ʾ�Ƿ�������0��ʾ��������Ĭ��ֵΪ0����ֵ��PHYͨ��GTCָ������������BBP��ʱ������жϴ������ϱ���
 bit[23]     ����
 bit[22:20]  ��ȡʱ�̵�������burst��Ӧ��ʱ϶�ţ���ʱ϶����PHYͨ��GTCָ������������BBP��ʱ������жϴ������ϱ���
 bit[19:16]  ��ȡʱ�̵�������burst��Ӧ��NBλ�õ��������ǲ����ʾ���з�������������ʾ��ǰ������������ʾ����������Χ��-4~+4��
 bit[15:14]  ��ȡʱ�̵����BURST�ĵ��Ʒ�ʽ��
             0��GSKM��
             1��8PSK��
             2��DummyBurst��
 bit[13:0]   ����
   UNION�ṹ:  GBBP_VALPP_DEM_TYPE_TOA4_UNION */
#define GBBP_VALPP_DEM_TYPE_TOA4_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x5298)

/* �Ĵ���˵����
 bit[31]     ����
 bit[30:0]   ��ȡʱ��ǰ������burst��Ӧ���ز�����ֵ���޷�������
   UNION�ṹ:  GBBP_VALPP_CARRIER_ENERGY5_UNION */
#define GBBP_VALPP_CARRIER_ENERGY5_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x5334)

/* �Ĵ���˵����
 bit[31:26]  ����
 bit[25:0]   ��ȡʱ��ǰ������burst��Ӧ�ĸ�������ֵ���޷�������
   UNION�ṹ:  GBBP_VALPP_INTERFERE_ENERGY5_UNION */
#define GBBP_VALPP_INTERFERE_ENERGY5_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x5338)

/* �Ĵ���˵����
 bit[31]     ��ȡʱ�̵����������Ϣ��Ч��־�������һ��NB���ʱ���ñ�־��1,CPU��ȡ���BURST����ϱ���Ϣ��Ӧ��ͨ��bit30�Ը�bit���㣬ָʾ����Ϣ�Ѿ���ȡ��
 bit[30]     ��demod_info_valid_flag5���㡣д1���㡣
 bit[29:28]  ��ȡʱ��ǰ�ĵ�����BURST��Ӧ��һ���о��ĵ��Ʒ�ʽ��
             0��GMSK���ƣ�
             1��8PSK���ƣ�
             2��DummyBurst��
             �üĴ�������ʹ�á�
 bit[27:25]  ����
 bit[24]     ��ȡʱ�̵�����burst�Ƿ�Ϊ�Ƿ�����ָʾ��1��ʾ�Ƿ�������0��ʾ��������Ĭ��ֵΪ0����ֵ��PHYͨ��GTCָ������������BBP��ʱ������жϴ������ϱ���
 bit[23]     ����
 bit[22:20]  ��ȡʱ�̵��������burst��Ӧ��ʱ϶�ţ���ʱ϶����PHYͨ��GTCָ������������BBP��ʱ������жϴ������ϱ���
 bit[19:16]  ��ȡʱ�̵��������burst��Ӧ��NBλ�õ��������ǲ����ʾ���з�������������ʾ��ǰ������������ʾ����������Χ��-4~+4��
 bit[15:14]  ��ȡʱ�̵�����BURST�ĵ��Ʒ�ʽ��
             0��GSKM��
             1��8PSK��
             2��DummyBurst��
 bit[13:0]   ����
   UNION�ṹ:  GBBP_VALPP_DEM_TYPE_TOA5_UNION */
#define GBBP_VALPP_DEM_TYPE_TOA5_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x533C)

/* �Ĵ���˵����
 bit[31]     NB��ƫʹ���źţ�0��ʾ�ر�Ƶƫ��⼰��ƫ��1��ʾ�򿪡�Ĭ��Ϊ0��
 bit[30]     SB��ƫʹ���źţ�0��ʾ�ر�Ƶƫ��⼰��ƫ��1��ʾ�򿪡�
             V9R1/V3R3��֧�ָù��ܣ���������Ϊ0��
             
 bit[29:24]  ����
 bit[23]     SBƵƫֵ�������ӣ�0��ʾϵ��Ϊ1.25��1��ʾϵ��Ϊ1
 bit[22:11]  ����
 bit[10:8]   ���ģ���ã���ƫ״̬��һ����״̬���о��Ƿ������ƫ����. ��Ӧ��·�ź��� EnergyThreshold����Ĭ��ֵ12�����壺ͨ���ŵ����Ƽ���ȫ�������Ͳ�����������ѡֵ9,10, 11,12,13,14,15��
             CPU��ֵ��Ӧ��ϵ��0-6��
             
 bit[7:3]    ����
 bit[2:0]    ���������ڽ��ģ���ڲ����о��Ƿ�����ƫ ��Ӧ��·�ź���CIThreshold��Ĭ��ֵ10��
             ��ѡֵ7,8,9,10,11,12,13��
             CPU��ֵ��Ӧ��ϵ��0-6��
             
   UNION�ṹ:  GBBP_CPU_JITTER_CORR_CFG1_UNION */
#define GBBP_CPU_JITTER_CORR_CFG1_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0x53B4)

/* �Ĵ���˵����
 bit[31]     ����
 bit[30:16]  SB jitterOn�㷨��ǰƵƫ�ϱ�
 bit[15]     ����
 bit[14:0]   JITTER ON�����㷨��ǰƵƫ�ϱ�
   UNION�ṹ:  GBBP_PHI_DEV_CPU_UNION */
#define GBBP_PHI_DEV_CPU_ADDR                         (SOC_BBP_GSM_BASE_ADDR + 0x53B8)

/* �Ĵ���˵����
 bit[31]     NBƵƫУ׼��Χ�̳�ʹ�ܣ�Ĭ��ֵ��1��
 bit[30:21]  ����
 bit[20:16]  �����оƬ���ã���ƫ���޷�����Ӧ��·�ź� FrOffLim ��Ĭ��ֵ20����ѡֵ14,16,18,20,22, 24��
 bit[15:12]  ����
 bit[11:8]   ��Ӧ����·�е�FrOffLim_STEP��ȡֵ��Χ5 6 7 8 9��Ĭ��ֵ��7
 bit[7:3]    ����
 bit[2:0]    ��Ӧ����·�е�SNR_THRES�����ڼ����ƫ��Χ fr_off_lim_act���Լ���������, Ĭ��ֵ100, ȡֵ��Χ90 95 100 105 110,CPU��ֵ��Ӧ0��4
   UNION�ṹ:  GBBP_CPU_JITTER_CORR_CFG2_UNION */
#define GBBP_CPU_JITTER_CORR_CFG2_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0x53BC)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ������ģʽ����Ӧ����жϺ��ȡѵ�����������ϱ�RAM���ϱ����ƿ���,��ʱ϶����ʹ��ƹ�Ҳ���ģʽ
             1��ʾCPU����ѵ�����������ϱ�RAM����ƹ��RAM����ģʽ��
             0��ʾCPU����ѵ�����������ϱ�RAM���÷�ƹ��RAM����ģʽ
             
   UNION�ṹ:  GBBP_CPU_TSC_SWITCH_EN_UNION */
#define GBBP_CPU_TSC_SWITCH_EN_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x53C4)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:16]  �˲���0��I·����p1��Ĭ��ֵ��14'd0��
 bit[15:14]  ����
 bit[13:0]   �˲���0��I·����p0��Ĭ��ֵ��14'd0��
   UNION�ṹ:  GBBP_CPU_FILTER0_P0_P1_UNION */
#define GBBP_CPU_FILTER0_P0_P1_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5800)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:16]  �˲���0��I·����p3��Ĭ��ֵ��14'd0��
 bit[15:14]  ����
 bit[13:0]   �˲���0��I·����p2��Ĭ��ֵ��14'd0��
   UNION�ṹ:  GBBP_CPU_FILTER0_P2_P3_UNION */
#define GBBP_CPU_FILTER0_P2_P3_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5804)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:16]  �˲���0��I·����p5��Ĭ��ֵ��14'd4096��
 bit[15:14]  ����
 bit[13:0]   �˲���0��I·����p4��Ĭ��ֵ��14'd0��
   UNION�ṹ:  GBBP_CPU_FILTER0_P4_P5_UNION */
#define GBBP_CPU_FILTER0_P4_P5_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5808)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:16]  �˲���3��I·����p1��Ĭ��ֵ��-14'd113��
 bit[15:14]  ����
 bit[13:0]   �˲���3��I·����p0��Ĭ��ֵ��-14'd167��
   UNION�ṹ:  GBBP_CPU_FILTER3_P0_P1_UNION */
#define GBBP_CPU_FILTER3_P0_P1_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x580C)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:16]  �˲���3��I·����p3��Ĭ��ֵ��14'd1018��
 bit[15:14]  ����
 bit[13:0]   �˲���3��I·����p2��Ĭ��ֵ��-14'd273��
   UNION�ṹ:  GBBP_CPU_FILTER3_P2_P3_UNION */
#define GBBP_CPU_FILTER3_P2_P3_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5810)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:16]  �˲���3��I·����p5��Ĭ��ֵ��14'd2228��
 bit[15:14]  ����
 bit[13:0]   �˲���3��I·����p4��Ĭ��ֵ��14'd377��
   UNION�ṹ:  GBBP_CPU_FILTER3_P4_P5_UNION */
#define GBBP_CPU_FILTER3_P4_P5_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5814)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:16]  �˲���1��I·����p1��Ĭ��ֵ��14'd168��
 bit[15:14]  ����
 bit[13:0]   �˲���1��I·����p0��Ĭ��ֵ��14'd17��
   UNION�ṹ:  GBBP_CPU_FILTER1_P0_P1_I_UNION */
#define GBBP_CPU_FILTER1_P0_P1_I_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x5818)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:16]  �˲���1��I·����p3��Ĭ��ֵ��14'd185��
 bit[15:14]  ����
 bit[13:0]   �˲���1��I·����p2��Ĭ��ֵ��14'd22��
   UNION�ṹ:  GBBP_CPU_FILTER1_P2_P3_I_UNION */
#define GBBP_CPU_FILTER1_P2_P3_I_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x581C)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:16]  �˲���1��I·����p5��Ĭ��ֵ��14'd1738��
 bit[15:14]  ����
 bit[13:0]   �˲���1��I·����p4��Ĭ��ֵ��14'd1116��
   UNION�ṹ:  GBBP_CPU_FILTER1_P4_P5_I_UNION */
#define GBBP_CPU_FILTER1_P4_P5_I_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x5820)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:16]  �˲���1��Q·����p1��Ĭ��ֵ��14'd219��
 bit[15:14]  ����
 bit[13:0]   �˲���1��Q·����p0��Ĭ��ֵ��14'd6��
   UNION�ṹ:  GBBP_CPU_FILTER1_P0_P1_Q_UNION */
#define GBBP_CPU_FILTER1_P0_P1_Q_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x5824)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:16]  �˲���1��Q·����p3��Ĭ��ֵ��-14'd377��
 bit[15:14]  ����
 bit[13:0]   �˲���1��Q·����p2��Ĭ��ֵ��14'd219��
   UNION�ṹ:  GBBP_CPU_FILTER1_P2_P3_Q_UNION */
#define GBBP_CPU_FILTER1_P2_P3_Q_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x5828)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:16]  �˲���1��Q·����p5��Ĭ��ֵ��14'd0��
 bit[15:14]  ����
 bit[13:0]   �˲���1��Q·����p4��Ĭ��ֵ��-14'd694��
   UNION�ṹ:  GBBP_CPU_FILTER1_P4_P5_Q_UNION */
#define GBBP_CPU_FILTER1_P4_P5_Q_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x582C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      1��dagc�������ݲ����˲�������ֱ�����
             0��dagc�������ݾ��˲�����������
             
   UNION�ṹ:  GBBP_CPU_GACI_DATA_BYPASS_UNION */
#define GBBP_CPU_GACI_DATA_BYPASS_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0x5880)

/* �Ĵ���˵����
 bit[31:19]  ����
 bit[18:16]  �о�����������
             3��b000:   5
             3��b001:   6
             3��b010:   7
             3��b011:   8
             3��b100:   9
             3��b101:   10
             Ĭ��ֵ:   6
             
 bit[15:3]   ����
 bit[2:0]    �о�����������
             3��b000:   2
             3��b001:   3
             3��b010:   4
             3��b011:   5
             3��b100:   6
             3��b101:   7
             3��b110:   8
             3��b111:   9
             Ĭ��ֵ:   5
             
   UNION�ṹ:  GBBP_CPU_GACI_PARA_UNION */
#define GBBP_CPU_GACI_PARA_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x5884)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    �����Ƶ��������ϱ�CPU���ֿ��ܵĸ���״̬��
             2��b00���޸���
             2��b01��+200Khz����
             2��b10��-200Khz����
             2��b11�� 200Khz����
             
   UNION�ṹ:  GBBP_GACI_INDEX_CPU_UNION */
#define GBBP_GACI_INDEX_CPU_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x58A0)

/* �Ĵ���˵����
 bit[31:26]  ����
 bit[25:0]   GACI��������ematrix_03_cpu_cpu��ematrix_12_cpu����
   UNION�ṹ:  GBBP_GACI_RACI_CPU_UNION */
#define GBBP_GACI_RACI_CPU_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x58A4)

/* �Ĵ���˵����
 bit[31:26]  ����
 bit[25:0]   GACI��������EMATRIX״̬�²������о��������ɾ�����ͨ������������������
   UNION�ṹ:  GBBP_GACI_RPOWER_CPU_UNION */
#define GBBP_GACI_RPOWER_CPU_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x58A8)

/* �Ĵ���˵����
 bit[31:26]  ����
 bit[25:0]   GACI��������EMATRIX״̬�²������о��������ɾ�����ͨ����������ز�����
   UNION�ṹ:  GBBP_GACI_EMATRIX_03_CPU_UNION */
#define GBBP_GACI_EMATRIX_03_CPU_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x58AC)

/* �Ĵ���˵����
 bit[31:26]  ����
 bit[25:0]   GACI��������EMATRIX״̬�²������о��������ɾ�����ͨ����������ز�����
   UNION�ṹ:  GBBP_GACI_EMATRIX_12_CPU_UNION */
#define GBBP_GACI_EMATRIX_12_CPU_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x58B0)

/* �Ĵ���˵����
 bit[31:21]  ����
 bit[20:0]   GACIδ������ͨ����ԭ����������������ENERGY1״̬����
   UNION�ṹ:  GBBP_GACI_AVG_ALL_CPU_UNION */
#define GBBP_GACI_AVG_ALL_CPU_ADDR                    (SOC_BBP_GSM_BASE_ADDR + 0x58B4)

/* �Ĵ���˵����
 bit[31:21]  ����
 bit[20:0]   GACI������ͨ����ԭ����������������ENERGY2״̬����
   UNION�ṹ:  GBBP_GACI_AVG_HP_CPU_UNION */
#define GBBP_GACI_AVG_HP_CPU_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x58B8)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    AMR����bit�Ż��㷨�����SPEECH CRC�ı������������÷�Χ0��3������������Ϊ1��4��Ĭ��ֵΪ3
             ����ҵ������ΪGMSK WBAMRʱ�����÷�ΧΪ0��2��
             
   UNION�ṹ:  GBBP_CPU_AMR_CRC_PRO_NUM_CFG_UNION */
#define GBBP_CPU_AMR_CRC_PRO_NUM_CFG_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x53CC)

/* �Ĵ���˵����
 bit[31:21]  ����
 bit[20:0]   AMR����bit�Ż��㷨��00��Ӧ���������
   UNION�ṹ:  GBBP_CPU_P0_PRIOR_REG_CFG_UNION */
#define GBBP_CPU_P0_PRIOR_REG_CFG_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0x53D0)

/* �Ĵ���˵����
 bit[31:21]  ����
 bit[20:0]   AMR����bit�Ż��㷨��01��Ӧ���������
   UNION�ṹ:  GBBP_CPU_P1_PRIOR_REG_CFG_UNION */
#define GBBP_CPU_P1_PRIOR_REG_CFG_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0x53D4)

/* �Ĵ���˵����
 bit[31:21]  ����
 bit[20:0]   AMR����bit�Ż��㷨��10��Ӧ���������
   UNION�ṹ:  GBBP_CPU_P2_PRIOR_REG_CFG_UNION */
#define GBBP_CPU_P2_PRIOR_REG_CFG_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0x53D8)

/* �Ĵ���˵����
 bit[31:21]  ����
 bit[20:0]   AMR����bit�Ż��㷨��11��Ӧ���������
             AFS���㷨�Ƽ�����Ϊ-6000��AHS���㷨�Ƽ�����Ϊ-4000
   UNION�ṹ:  GBBP_CPU_P3_PRIOR_REG_CFG_UNION */
#define GBBP_CPU_P3_PRIOR_REG_CFG_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0x53DC)

/* �Ĵ���˵����
 bit[31:16]  CMI����bit 1��Ӧ����������ϱ�
 bit[15:0]   CMI����bit 0��Ӧ����������ϱ�
   UNION�ṹ:  GBBP_CMI_P01_PRIOR_PRE_RPT_UNION */
#define GBBP_CMI_P01_PRIOR_PRE_RPT_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x5380)

/* �Ĵ���˵����
 bit[31:16]  CMI����bit 3��Ӧ����������ϱ�
 bit[15:0]   CMI����bit 2��Ӧ����������ϱ�
   UNION�ṹ:  GBBP_CMI_P23_PRIOR_PRE_RPT_UNION */
#define GBBP_CMI_P23_PRIOR_PRE_RPT_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x5384)

/* �Ĵ���˵����
 bit[31:16]  CMC����bit 1��Ӧ����������ϱ�
 bit[15:0]   CMC����bit 0��Ӧ����������ϱ�
   UNION�ṹ:  GBBP_CMC_P01_PRIOR_PRE_RPT_UNION */
#define GBBP_CMC_P01_PRIOR_PRE_RPT_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x5388)

/* �Ĵ���˵����
 bit[31:16]  CMC����bit 3��Ӧ����������ϱ�
 bit[15:0]   CMC����bit 2��Ӧ����������ϱ�
   UNION�ṹ:  GBBP_CMC_P23_PRIOR_PRE_RPT_UNION */
#define GBBP_CMC_P23_PRIOR_PRE_RPT_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x538C)

/* �Ĵ���˵����
 bit[31:16]  CMC����CMI ����bit 1��Ӧ����ʷ�������ֵ�����ڻָ�GBBP��CMC����CMI�������
 bit[15:0]   CMC����CMI ����bit 0��Ӧ����ʷ�������ֵ�����ڻָ�GBBP��CMC����CMI�������
   UNION�ṹ:  GBBP_CPU_P01_MAPPRE_CFG_UNION */
#define GBBP_CPU_P01_MAPPRE_CFG_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x5390)

/* �Ĵ���˵����
 bit[31:16]  CMC����CMI ����bit 3��Ӧ����ʷ�������ֵ�����ڻָ�GBBP��CMC����CMI�������
 bit[15:0]   CMC����CMI ����bit 2��Ӧ����ʷ�������ֵ�����ڻָ�GBBP��CMC����CMI�������
   UNION�ṹ:  GBBP_CPU_P23_MAPPRE_CFG_UNION */
#define GBBP_CPU_P23_MAPPRE_CFG_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x5394)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:16]  AMR�о��㷨�о������ޣ�AFS�Ƽ�ֵΪ233��AHS�Ƽ�ֵΪ230
 bit[15:9]   ����
 bit[8]      1��ʶ��ǰ�����ж�����������CMC����
             0��ʶ��ǰ�����ж�����������CMI���ڡ�
 bit[7:3]    ����
 bit[2]      1��ʶ����C02ͨ��״̬���о�NODATA��ģʽ
             0��ʶ����V3 AMR���������о���ʽ��
 bit[1]      0��ʶ����CMI����ʷ������ʣ�1��ʶ����CMC����ʷ�������
 bit[0]      1��ʶ��Ҫ������CMI����CMC����ʷ������ʣ����ź�����֮ǰ��Ҫ���������CPU_P01_MAPPRE_CFG��CPU_P23_MAPPRE_CFG�Ĵ���
   UNION�ṹ:  GBBP_CPU_CMC_CMI_LOAD_EN_UNION */
#define GBBP_CPU_CMC_CMI_LOAD_EN_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x5398)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:16]  AMR������֡��������ۼӺ��ϱ�
 bit[15:14]  ����
 bit[13:8]   AMR������֡�����ϱ�
 bit[7:6]    ����
 bit[5:0]    AMR����֡�����ϱ�
   UNION�ṹ:  GBBP_AMR_INFO1_RPT_UNION */
#define GBBP_AMR_INFO1_RPT_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x53F8)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2]      AMR�о��㷨��ʽ�ϱ�
 bit[1]      AMR�о��㷨��ʽ�ϱ�
 bit[0]      AMR�о��㷨��ʽ�ϱ�
   UNION�ṹ:  GBBP_AMR_INFO2_RPT_UNION */
#define GBBP_AMR_INFO2_RPT_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x53FC)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    AFS/AHS ��������о���ʽ���޲��������÷�Χ0��15���Ƽ�����Ϊ10
   UNION�ṹ:  GBBP_CPU_AMR_CORR_COEFF_CFG_UNION */
#define GBBP_CPU_AMR_CORR_COEFF_CFG_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x53E0)

/* �Ĵ���˵����
 bit[31:16]  VALPP RAM���ڷ��ʳ�ͻ������
             [31:28] DEM��CARRY���̷�������д��ͻ
             [27:20]  DEMAP��MAP���̷�������д��ͻ
             [23:20] DEMAP��CARRY���̷�������д��ͻ
             [19:16] DEMAP��DEMģ�鷢������д��ͻ
             
 bit[15:8]   ����
 bit[7:0]    [3:0] ��������������������������ó�ͻ�������ϱ�
             [7:4]��������������������б������ó�ͻ�������ϱ�
             
   UNION�ṹ:  GBBP_CODEC_WR_CONFLICT_CNT_UNION */
#define GBBP_CODEC_WR_CONFLICT_CNT_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x5718)

/* �Ĵ���˵����
 bit[31:17]  ����
 bit[16]     HARQ����ģʽ�£��Ƿ����CRC���������DDR���з��ʣ�1��ʾ����CRC�����ǿ�н����ݴ���HARQ MEM��0��ʾ����CRC��������ݴ���HARQ MEM��
 bit[15:1]   ����
 bit[0]      HARQ����ģʽ������ģʽѡ���źţ�1��ʾʹ������ģʽ��0��ʾʹ������ģʽ��
   UNION�ṹ:  GBBP_ADDR_HARQ_MODE_UNION */
#define GBBP_ADDR_HARQ_MODE_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x5A00)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      HARQ����ģʽ�£��쳣��λ�źţ������źţ�д1��λ��
   UNION�ṹ:  GBBP_ADDR_HARQ_INIT_EN_UNION */
#define GBBP_ADDR_HARQ_INIT_EN_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5A04)

/* �Ĵ���˵����
   ��      ����HARQ����ģʽ�£�CPU�����HARQ DDRд��������ַ��
   UNION�ṹ ���� */
#define GBBP_ADDR_HARQ_WR_BASE_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5A08)

/* �Ĵ���˵����
   ��      ����HARQ����ģʽ�£�CPU�����HARQ DDR����������ַ��
   UNION�ṹ ���� */
#define GBBP_ADDR_HARQ_RD_BASE_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5A0C)

/* �Ĵ���˵����
 bit[31:20]  ����
 bit[19:16]  HARQ����ģʽ�£������ж��쳣״̬�ϱ�ֵ��
             1��b1�����볬ʱ
             1��b0������δ��ʱ
             
 bit[15:4]   ����
 bit[3:0]    HARQ����ģʽ�£�DDRÿ��дFIFO��burst���ȡ�
   UNION�ṹ:  GBBP_ADDR_DDR_HARQ_CFG_UNION */
#define GBBP_ADDR_DDR_HARQ_CFG_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5A10)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      �����˲���ʹ���źţ��������Ƶ��ƺ������Ƿ񾭹�16�������˲�����Ĭ��ֵ��0��
   UNION�ṹ:  GBBP_ADDR_TX_RRC_PILTER_EN_UNION */
#define GBBP_ADDR_TX_RRC_PILTER_EN_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x5A14)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      HARQ����ģʽ�£�Harq Ramдʹ�ܳ�ʱ������·�źš����ź���Ч��ʾHarq Ramдʹ�ܲ�����ʱ������Ĭ��ֵΪ0����ʾ���г�ʱ������
   UNION�ṹ:  GBBP_ADDR_HARQ_RAM_WR_EN_BYPASS_UNION */
#define GBBP_ADDR_HARQ_RAM_WR_EN_BYPASS_ADDR          (SOC_BBP_GSM_BASE_ADDR + 0x5A18)

/* �Ĵ���˵����
 bit[31:17]  ����
 bit[16]     GBBP��ʱ����״̬�����źţ�д1��Ч�������㣬���ź���Чʱ��timing_get_state״̬����
 bit[15:1]   ����
 bit[0]      GBBP��ʱ���������źţ�д1��Ч�������㣬���ź���Чʱ��GBBP������ʱ���档
   UNION�ṹ:  GBBP_CPU_TIMING_GET_TRIGGER_UNION */
#define GBBP_CPU_TIMING_GET_TRIGGER_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0x5A20)

/* �Ĵ���˵����
 bit[31]     ��ʱ����״̬�ϱ�����cpu_timing_get_state_clr��Чʱ�ñ����ϱ��������㡣
 bit[30:27]  ����
 bit[26:16]  GTC��ʱʵ��֡�Ÿ�λ
 bit[15:11]  ����
 bit[10:0]   GTC��ʱʵ��֡�ŵ�λ
   UNION�ṹ:  GBBP_TIMING_GET_FN_RPT_UNION */
#define GBBP_TIMING_GET_FN_RPT_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5A24)

/* �Ĵ���˵����
 bit[31:29]  ����
 bit[28:16]  ����ʱ��QB�ϱ���������Χ0~4999����Ӧһ֡�ĳ��ȡ���ֵֻ�븴λʱ���йأ�������
 bit[15:13]  ����
 bit[12:0]   ��ǰʱ��TDMA��QB����ֵ
   UNION�ṹ:  GBBP_TIMING_GET_TIMEBASE_RPT_UNION */
#define GBBP_TIMING_GET_TIMEBASE_RPT_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x5A28)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      1��ʶ��LoopC����ʱ��͵֡bitλ�ù̶�����1��b0��
             0��ʶ��LoopC����ʱ��͵֡bitλ�÷��ؽ����ֵ�ķ���λ��
             
   UNION�ṹ:  GBBP_LOOPC_MODE_CFG_UNION */
#define GBBP_LOOPC_MODE_CFG_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x53F0)

/* �Ĵ���˵����
 bit[31:23]  ����
 bit[22:16]  ���б�����cbindex�ϱ�
 bit[15:10]  ����
 bit[9:8]    ���б������ʼλ���ϱ�
 bit[7:4]    ����
 bit[3:0]    ���б�������ϱ�
   UNION�ṹ:  GBBP_COD_CBINDEX_RPT_UNION */
#define GBBP_COD_CBINDEX_RPT_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x53F4)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  ���з���У׼ʱǿ��I·�������Ϊ����������
 bit[15:12]  ����
 bit[11:0]   ���з���У׼ʱǿ��Q·�������Ϊ����������
   UNION�ṹ:  GBBP_CPU_IQ_MOD_DTA_UNION */
#define GBBP_CPU_IQ_MOD_DTA_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x53C8)

/* �Ĵ���˵����
 bit[31:26]  ����
 bit[25:16]  8PSK���е��������������ӣ����ŷ���Ĭ��ԼΪ1023/1024=1��
 bit[15:10]  ����
 bit[9:0]    GMSK���е��������������ӣ����ŷ���Ĭ��ԼΪ921/1024=0.9��
   UNION�ṹ:  GBBP_TX_DATA_MULFACTOR_UNION */
#define GBBP_TX_DATA_MULFACTOR_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5374)

/* �Ĵ���˵����
 bit[31:12]  ����
 bit[11:0]   ʱ϶ȥֱ���������ޣ���ʱ϶ȥֱ���Ƿ�����ȡ���ڵ�ǰʱ϶��RSSI��С�������ڸ�����ʱ���������ʱ϶ȥֱ��ģʽ����֮��������Ĭ������-12'd1200���൱��-150dBm�����ڿտڽ����źŲ�����С�ڸ�ֵ���൱��Ĭ�ϲ���������ʱ϶ȥֱ����
   UNION�ṹ:  GBBP_SLOT_DCR_RSSI_THRESHOLD_UNION */
#define GBBP_SLOT_DCR_RSSI_THRESHOLD_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x5378)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:0]   GMSK���������ݣ�����󡢵���ǰ���ϱ���0��29���أ�˳��Ϊ�ӵ͵���
   UNION�ṹ:  GBBP_MOD_BIT0_RPT_UNION */
#define GBBP_MOD_BIT0_RPT_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x53A0)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:0]   GMSK���������ݣ�����󡢵���ǰ���ϱ���30��59���أ�˳��Ϊ�ӵ͵���
   UNION�ṹ:  GBBP_MOD_BIT1_RPT_UNION */
#define GBBP_MOD_BIT1_RPT_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x53A4)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:0]   GMSK���������ݣ�����󡢵���ǰ���ϱ���60��89���أ�˳��Ϊ�ӵ͵���
   UNION�ṹ:  GBBP_MOD_BIT2_RPT_UNION */
#define GBBP_MOD_BIT2_RPT_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x53A8)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:0]   GMSK���������ݣ�����󡢵���ǰ���ϱ���90��119���أ�˳��Ϊ�ӵ͵���
   UNION�ṹ:  GBBP_MOD_BIT3_RPT_UNION */
#define GBBP_MOD_BIT3_RPT_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x53AC)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:0]   GMSK���������ݣ�����󡢵���ǰ���ϱ���120��147���أ�˳��Ϊ�ӵ͵��ߡ���������148���أ�[29:27]������
   UNION�ṹ:  GBBP_MOD_BIT4_RPT_UNION */
#define GBBP_MOD_BIT4_RPT_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x53B0)

/* �Ĵ���˵����
 bit[31:26]  ����
 bit[25:16]  GSM TX IQ Mismatch��λУ�����ӣ��з�������
 bit[15:10]  ����
 bit[9:0]    GSM TX IQ Mismatch��ֵУ�����ӣ��з�������
   UNION�ṹ:  GBBP_TX_IQ_MISMATCH_COMP_UNION */
#define GBBP_TX_IQ_MISMATCH_COMP_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x58BC)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  GSM TX IQ Mismatch Q·ֱ��ƫ�ò���ֵ���з�������ע����������
 bit[15:12]  ����
 bit[11:0]   GSM TX IQ Mismatch I·ֱ��ƫ�ò���ֵ���з�������ע����������
   UNION�ṹ:  GBBP_TX_IQ_DC_OFFSET_COMP_UNION */
#define GBBP_TX_IQ_DC_OFFSET_COMP_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0x58C0)

/* �Ĵ���˵����
 bit[31:26]  ����
 bit[25:16]  ��������ʱ�����½������apc_rampĬ��ֵ��
             Ĭ��ֵΪ0��
             �����á�
             
 bit[15:9]   ����
 bit[8]      8psk��������ʹ���źš�
             1��ʾ8pskʹ���������£�0��ʾ8psk��ʹ���������¡�
             Ĭ��ֵΪ1��
             
 bit[7:1]    ����
 bit[0]      gmsk��������ʹ���źš�
             1��ʾgmskʹ���������£�0��ʾgmsk��ʹ���������¡�
             
   UNION�ṹ:  GBBP_TX_DIG_RMAP_MODE_SEL_UNION */
#define GBBP_TX_DIG_RMAP_MODE_SEL_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0x58C4)

/* �Ĵ���˵����
 bit[31:26]  ����
 bit[25:16]  ����ʹ�õ�gsp_pa_targetֵ�ϱ�
 bit[15:1]   ����
 bit[0]      GAPC����ϵ������RAMƹ�ҷ���ʹ�ܣ�1��ʾ����ƹ�ҷ��ʣ�0��ʾ�̶�����֡0ϵ���ռ䣻�����ź�Ϊ1ʱ���߼��ڲ���TDMA֡ͷ�Զ��л�ƹ�ұ�־
   UNION�ṹ:  GBBP_CPU_APC_SWITCH_EN_UNION */
#define GBBP_CPU_APC_SWITCH_EN_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x53C0)

/* �Ĵ���˵����
 bit[31:28]  16��GTCģ��Ĳ�������ѡ���ź�
 bit[27:24]  16��MODģ��Ĳ�������ѡ���ź�
 bit[23:20]  16��CODģ��Ĳ�������ѡ���ź�
 bit[19:16]  16��DECģ��Ĳ�������ѡ���ź�
 bit[15:12]  16��VTB_DEMģ��Ĳ���ѡ���ź�����
 bit[11:8]   16��SRCHģ��Ĳ�������ѡ���ź�
 bit[7:4]    16��MAUģ��Ĳ�������ѡ���ź�
 bit[3:0]    16��AGCģ��Ĳ�������ѡ���ź�
   UNION�ṹ:  GBBP_TEST_PIN_SEL_LOW_UNION */
#define GBBP_TEST_PIN_SEL_LOW_ADDR                    (SOC_BBP_GSM_BASE_ADDR + 0x5700)

/* �Ĵ���˵����
 bit[31:16]  ����TOA�����13���������У�����5�������ۼӣ�����9���ۼ�ֵ�����ϱ�Ϊ��ǰʱ϶����ۼ�ֵ��
 bit[15:12]  ����
 bit[11:8]   16��APCģ��Ĳ�������ѡ���ź�
 bit[7:4]    16��PREPROCESSģ��Ĳ�������ѡ���ź�
 bit[3:0]    16��PREFILTERģ��Ĳ�������ѡ���ź�
   UNION�ṹ:  GBBP_TEST_PIN_SEL_HIGH_UNION */
#define GBBP_TEST_PIN_SEL_HIGH_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5704)

/* �Ĵ���˵����
 bit[31:8]   ����
 bit[7:5]    0��ʾ����ѡ��DAGC������ݲ�������ؿ����ź�
             1��ʾ����ѡ��AGC�������ݲ�������ؿ����ź�
             2��ʾ����ѡ��DAGC����ͽ������ֵ���ݲ�������ؿ����ź�
             3��ʾ����ѡ��DAGC�����AGC�������ݲ�������ؿ����ź�
             4��ʾ���Թ۲��������������źź��ж��ź�
             
 bit[4:0]    0��ѡ��AGCģ��Ĳ�������
             1��ѡ����ۼ�ģ��Ĳ�������
             2��ѡ������ģ��Ĳ�������
             3��ѡ����ģ��Ĳ�������
             4��ѡ������ģ��Ĳ�������
             5��ѡ�����ģ��Ĳ�������
             6��ѡ�����ģ��Ĳ�������
             7��ѡ��GTCģ��Ĳ�������
             8��ѡ��A5 DECIPHģ��Ĳ�������
             9��ѡ��PREFILTERģ��Ĳ�������
             10��ѡ��PREPROCESSģ��Ĳ�������
             11��ѡ��APCģ��Ĳ�������
             13��ѡ��GRIFģ��Ĳ�������
             14��ѡ��A5 CIPHģ��Ĳ�������
             
   UNION�ṹ:  GBBP_TEST_MODULE_SEL_UNION */
#define GBBP_TEST_MODULE_SEL_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x5710)

/* �Ĵ���˵����
 bit[31:28]  4'd0: gsp_agc_fast_start�źŶ�Ӧ��gtc_tdma_qb����ֵ
             4'd1: gsp_agc_slow_start�źŶ�Ӧ��gtc_tdma_qb����ֵ
             4'd2: gsp_srch_start�źŶ�Ӧ��gtc_tdma_qb����ֵ
             4'd3: gsp_demod_start�źŶ�Ӧ��gtc_tdma_qb����ֵ
             4'd4: gsp_rx_start�źŶ�Ӧ��gtc_tdma_qb����ֵ
             4'd5: gsp_rx_stop�źŶ�Ӧ��gtc_tdma_qb����ֵ
             4'd6: gsp_dec_start�źŶ�Ӧ��gtc_tdma_qb����ֵ
             4'd7: gsp_ul_cod_start�źŶ�Ӧ��gtc_tdma_qb����ֵ
             4'd8: gsp_ul_map_start�źŶ�Ӧ��gtc_tdma_qb����ֵ
             4'd9: gsp_mod_start�źŶ�Ӧ��gtc_tdma_qb����ֵ
             4'd10: gsp_mod_stop�źŶ�Ӧ��gtc_tdma_qb����ֵ
             4'd11: gsp_pa_start�źŶ�Ӧ��gtc_tdma_qb����ֵ
             4'd12: gsp_pa_stop�źŶ�Ӧ��gtc_tdma_qb����ֵ
             4'd13: gsp_pa_single_start�źŶ�Ӧ��gtc_tdma_qb����ֵ
             4'd14: gsp_pa_change�źŶ�Ӧ��gtc_tdma_qb����ֵ
             ������
 bit[27:13]  ����
 bit[12:0]   ��ӦGTC�������ĸ��������ź�����tdma_qbֵ�ϱ���
   UNION�ṹ:  GBBP_GSP_START_TDMA_QB_RPT_UNION */
#define GBBP_GSP_START_TDMA_QB_RPT_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x5714)

/* �Ĵ���˵����
 bit[31]     TOA Alpha�˲�����ʹ���źš�1��ʾ���������о��Ƿ�ʹ��Alpha���ܡ�
 bit[30:16]  Ԥ��������Ĵ�����
 bit[15:0]   TOA Alpha�˲����ޡ�Ĭ��11'd796���뾶�����ۼ�ֵ����6bit�Ľ�����бȽϡ�
   UNION�ṹ:  GBBP_DSP_DEDICATE_CTRL_REG_UNION */
#define GBBP_DSP_DEDICATE_CTRL_REG_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x5720)

/* �Ĵ���˵����
   ��      ����PHYר�üĴ���8
   UNION�ṹ ���� */
#define GBBP_DSP_DEDICATE_REG8_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x574C)

/* �Ĵ���˵����
   ��      �����汾�Ĵ�����
   UNION�ṹ ���� */
#define GBBP_GBBP_VERSION_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x5760)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      �޷�trigger�źţ�����ƽ̨���ⶨλʹ�á�
   UNION�ṹ:  GBBP_ERR_TRIG_UNION */
#define GBBP_ERR_TRIG_ADDR                            (SOC_BBP_GSM_BASE_ADDR + 0x5764)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      V2R1�汾����bit����Ϊ1��������
   UNION�ṹ:  GBBP_GBBP_EDGE_VERSION_UNION */
#define GBBP_GBBP_EDGE_VERSION_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x5768)

/* �Ĵ���˵����
 bit[31:19]  ����
 bit[18:0]   �������һ��BURST���ǰ�ֲ�Cֵ�ϱ���������
   UNION�ṹ:  GBBP_GROSS_CARRIER_ENERGY5_UNION */
#define GBBP_GROSS_CARRIER_ENERGY5_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x529C)

/* �Ĵ���˵����
 bit[31:19]  ����
 bit[18:0]   �������һ��BURST���ǰ�ֲ�Iֵ�ϱ���������
   UNION�ṹ:  GBBP_GROSS_INTERFERE_ENERGY5_UNION */
#define GBBP_GROSS_INTERFERE_ENERGY5_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x5300)

/* �Ĵ���˵����
 bit[31:19]  ����
 bit[18:0]   ��������һ��BURST���ǰ�ֲ�Cֵ�ϱ���������
   UNION�ṹ:  GBBP_GROSS_CARRIER_ENERGY6_UNION */
#define GBBP_GROSS_CARRIER_ENERGY6_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x5304)

/* �Ĵ���˵����
 bit[31:19]  ����
 bit[18:0]   ��������һ��BURST���ǰ�ֲ�Iֵ�ϱ���������
   UNION�ṹ:  GBBP_GROSS_INTERFERE_ENERGY6_UNION */
#define GBBP_GROSS_INTERFERE_ENERGY6_ADDR             (SOC_BBP_GSM_BASE_ADDR + 0x5308)

/* �Ĵ���˵����
 bit[31]     �����һ��ʱ϶�����ٲ�����־�ϱ���1��ʾ��ǰΪ���ٲ�����0��ʾ��ǰΪ���ٲ�����
 bit[30:27]  ����
 bit[26:24]  �����һ��ʱ϶AAGC��λ�ϱ���
 bit[23:20]  ����
 bit[19:8]   �����һ��ʱ϶AGC RSSIֵ����λ0.125dBm���ϱ���CPU����ֵ���ǿտڵ�RSSIֵ��
 bit[7:3]    ����
 bit[2:0]    �����һ��ʱ϶AGC�����������档
   UNION�ṹ:  GBBP_AAGC_GAIN5_CPU_UNION */
#define GBBP_AAGC_GAIN5_CPU_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x5290)

/* �Ĵ���˵����
 bit[31]     ��Զһ��ʱ϶�����ٲ�����־�ϱ���1��ʾ��ǰΪ���ٲ�����0��ʾ��ǰΪ���ٲ�����
 bit[30:27]  ����
 bit[26:24]  ��Զһ��ʱ϶AAGC��λ�ϱ���
 bit[23:20]  ����
 bit[19:8]   ��Զһ��ʱ϶AGC RSSIֵ����λ0.125dBm���ϱ���CPU����ֵ���ǿտڵ�RSSIֵ��
 bit[7:3]    ����
 bit[2:0]    ��Զһ��ʱ϶AGC�����������档
   UNION�ṹ:  GBBP_AAGC_GAIN6_CPU_UNION */
#define GBBP_AAGC_GAIN6_CPU_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x5294)

/* �Ĵ���˵����
   ��      ����CPU��ȡGRIF FIFO���ݣ��������ݸ�ʽ��ο��������ݱ�
   UNION�ṹ ���� */
#define GBBP_CPU_GDUMP_FIFO_RD_ADDR_ADDR              (SOC_BBP_GSM_BASE_ADDR + 0xF000)

/* �Ĵ���˵����
 bit[31]     ����ģ�������ܣ�������ʱ���ſأ���������ģʽ����������Ҫ���ô��ź���Ч���ߵ�ƽ��ʾ�ù��ܴ򿪡�
 bit[30:24]  ����
 bit[23:16]  G���в��Լ�����
 bit[15:9]   ����
 bit[8]      ����ģ����������ѡ��
             0��ѡ��ʹ��GTC���ýӿ�
             1��ѡ��ʹ��CPU���ýӿ�
             Ĭ������Ϊ0��
 bit[7]      ����
 bit[6:4]    ��������Դѡ��
             0��ѡ������ŵ��˲����������ݣ�
             1��ѡ������ŵ��˲���������ݣ�
             2��ѡ�����AGC�������ݣ�
             3��ѡ�����AGCȥֱ���������ڲ��������ݣ�
             4��ѡ�����AGCȥֱ���������ڽ�������������ݣ�
             5��ѡ�����DAGC������ݣ������ڲ�����������ݣ�
             6�����з��͵������ݣ�
             7��
 bit[3]      ����
 bit[2:0]    FIFOˮ�����ѡ��
             0����ʾˮ�����2��
             1����ʾˮ�����4��
             2����ʾˮ�����8��
             3����ʾˮ�����16��
             4����ʾˮ�����32��
             5����ʾˮ�����64��
             6����ʾˮ�����128��
             7��
             SOCˮ�����֧��1~16
   UNION�ṹ:  GBBP_CPU_GDUMP_GEN_CONFIG_UNION */
#define GBBP_CPU_GDUMP_GEN_CONFIG_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0xF004)

/* �Ĵ���˵����
   ��      ����CPU���ò������ݸ�����ȫ0��ʾ�������ݸ������޳���
   UNION�ṹ ���� */
#define GBBP_CPU_GDUMP_LEN_CONFIG_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0xF008)

/* �Ĵ���˵����
 bit[31:13]  ����
 bit[12:0]   ��������ʱ�̲���ģʽ�£�������ʼλ�ã�35'h7ffffffff��ʾ����������������Ϊ35bit��[12:0]��Ĭ��ֵΪ��������ģʽ��
   UNION�ṹ:  GBBP_CPU_GDUMP_SAM_LOW_TIMING_UNION */
#define GBBP_CPU_GDUMP_SAM_LOW_TIMING_ADDR            (SOC_BBP_GSM_BASE_ADDR + 0xF00C)

/* �Ĵ���˵����
 bit[31:27]  ����
 bit[26:16]  ��������ʱ�̲���ģʽ�£�������ʼλ�ã�35'h7ffffffff��ʾ����������������Ϊ35bit��[34:24]��Ĭ��ֵΪ��������ģʽ��
 bit[15:11]  ����
 bit[10:0]   ��������ʱ�̲���ģʽ�£�������ʼλ�ã�35'h7ffffffff��ʾ����������������Ϊ35bit��[23:13]��Ĭ��ֵΪ��������ģʽ��
   UNION�ṹ:  GBBP_CPU_GDUMP_SAM_HIGH_TIMING_UNION */
#define GBBP_CPU_GDUMP_SAM_HIGH_TIMING_ADDR           (SOC_BBP_GSM_BASE_ADDR + 0xF010)

/* �Ĵ���˵����
 bit[31:17]  ����
 bit[16]     CPU�����첽FIFO�����źš�
 bit[15:9]   ����
 bit[8]      CPU���ò�������ֹͣ�źţ����������ݸ������޳�ʱ���ø��ź�ֹͣ������
 bit[7:1]    ����
 bit[0]      CPU���ò������������źš�
   UNION�ṹ:  GBBP_CPU_GDUMP_RECV_CONFIG_UNION */
#define GBBP_CPU_GDUMP_RECV_CONFIG_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0xF014)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  GSM�����ŵ��˲�����ϵ��1,12bit�з�����
 bit[15:12]  ����
 bit[11:0]   GSM�����ŵ��˲�����ϵ��0,12bit�з�����
   UNION�ṹ:  GBBP_ADDR_G_CH_PARA_1REG_UNION */
#define GBBP_ADDR_G_CH_PARA_1REG_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0xF294)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  GSM�����ŵ��˲�����ϵ��3,12bit�з�����
 bit[15:12]  ����
 bit[11:0]   GSM�����ŵ��˲�����ϵ��2,12bit�з�����
   UNION�ṹ:  GBBP_ADDR_G_CH_PARA_2REG_UNION */
#define GBBP_ADDR_G_CH_PARA_2REG_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0xF298)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  GSM�����ŵ��˲�����ϵ��5,12bit�з�����
 bit[15:12]  ����
 bit[11:0]   GSM�����ŵ��˲�����ϵ��4,12bit�з�����
   UNION�ṹ:  GBBP_ADDR_G_CH_PARA_3REG_UNION */
#define GBBP_ADDR_G_CH_PARA_3REG_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0xF29C)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  GSM�����ŵ��˲�����ϵ��7,12bit�з�����
 bit[15:12]  ����
 bit[11:0]   GSM�����ŵ��˲�����ϵ��6,12bit�з�����
   UNION�ṹ:  GBBP_ADDR_G_CH_PARA_4REG_UNION */
#define GBBP_ADDR_G_CH_PARA_4REG_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0xF2A0)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  GSM�����ŵ��˲�����ϵ��9,12bit�з�����
 bit[15:12]  ����
 bit[11:0]   GSM�����ŵ��˲�����ϵ��8,12bit�з�����
   UNION�ṹ:  GBBP_ADDR_G_CH_PARA_5REG_UNION */
#define GBBP_ADDR_G_CH_PARA_5REG_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0xF2A4)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  GSM�����ŵ��˲�����ϵ��11,12bit�з�����
 bit[15:12]  ����
 bit[11:0]   GSM�����ŵ��˲�����ϵ��10,12bit�з�����
   UNION�ṹ:  GBBP_ADDR_G_CH_PARA_6REG_UNION */
#define GBBP_ADDR_G_CH_PARA_6REG_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0xF2A8)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  GSM�����ŵ��˲�����ϵ��13,12bit�з�����
 bit[15:12]  ����
 bit[11:0]   GSM�����ŵ��˲�����ϵ��12,12bit�з�����
   UNION�ṹ:  GBBP_ADDR_G_CH_PARA_7REG_UNION */
#define GBBP_ADDR_G_CH_PARA_7REG_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0xF2AC)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  GSM�����ŵ��˲�����ϵ��15,12bit�з�����
 bit[15:12]  ����
 bit[11:0]   GSM�����ŵ��˲�����ϵ��14,12bit�з�����
   UNION�ṹ:  GBBP_ADDR_G_CH_PARA_8REG_UNION */
#define GBBP_ADDR_G_CH_PARA_8REG_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0xF2B0)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  GSM�����ŵ��˲�����ϵ��17,12bit�з�����
 bit[15:12]  ����
 bit[11:0]   GSM�����ŵ��˲�����ϵ��16,12bit�з�����
   UNION�ṹ:  GBBP_ADDR_G_CH_PARA_9REG_UNION */
#define GBBP_ADDR_G_CH_PARA_9REG_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0xF2B8)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  GSM�����ŵ��˲�����ϵ��19,12bit�з�����
 bit[15:12]  ����
 bit[11:0]   GSM�����ŵ��˲�����ϵ��18,12bit�з�����
   UNION�ṹ:  GBBP_ADDR_G_CH_PARA_10REG_UNION */
#define GBBP_ADDR_G_CH_PARA_10REG_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0xF2C4)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  GSM�����ŵ��˲�����ϵ��21,12bit�з�����
 bit[15:12]  ����
 bit[11:0]   GSM�����ŵ��˲�����ϵ��20,12bit�з�����
   UNION�ṹ:  GBBP_ADDR_G_CH_PARA_11REG_UNION */
#define GBBP_ADDR_G_CH_PARA_11REG_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0xF2C8)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  GSM�����ŵ��˲�����ϵ��23,12bit�з�����
 bit[15:12]  ����
 bit[11:0]   GSM�����ŵ��˲�����ϵ��22,12bit�з�����
   UNION�ṹ:  GBBP_ADDR_G_CH_PARA_12REG_UNION */
#define GBBP_ADDR_G_CH_PARA_12REG_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0xF2CC)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  GSM�����ŵ��˲�����ϵ��25,12bit�з�����
 bit[15:12]  ����
 bit[11:0]   GSM�����ŵ��˲�����ϵ��24,12bit�з�����
   UNION�ṹ:  GBBP_ADDR_G_CH_PARA_13REG_UNION */
#define GBBP_ADDR_G_CH_PARA_13REG_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0xF2D0)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  GSM�����ŵ��˲�����ϵ��27,12bit�з�����
 bit[15:12]  ����
 bit[11:0]   GSM�����ŵ��˲�����ϵ��26,12bit�з�����
   UNION�ṹ:  GBBP_ADDR_G_CH_PARA_14REG_UNION */
#define GBBP_ADDR_G_CH_PARA_14REG_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0xF2D4)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  GSM�����ŵ��˲�����ϵ��29,12bit�з�����
 bit[15:12]  ����
 bit[11:0]   GSM�����ŵ��˲�����ϵ��28,12bit�з�����
   UNION�ṹ:  GBBP_ADDR_G_CH_PARA_15REG_UNION */
#define GBBP_ADDR_G_CH_PARA_15REG_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0xF2D8)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  GSM�����ŵ��˲�����ϵ��31,12bit�з�����
 bit[15:12]  ����
 bit[11:0]   GSM�����ŵ��˲�����ϵ��30,12bit�з�����
   UNION�ṹ:  GBBP_ADDR_G_CH_PARA_16REG_UNION */
#define GBBP_ADDR_G_CH_PARA_16REG_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0xF2DC)

/* �Ĵ���˵����
 bit[31:12]  ����
 bit[11:0]   GSM�����ŵ��˲�����ϵ��32,12bit�з�����
   UNION�ṹ:  GBBP_ADDR_G_CH_PARA_17REG_UNION */
#define GBBP_ADDR_G_CH_PARA_17REG_ADDR                (SOC_BBP_GSM_BASE_ADDR + 0xF2E0)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  GSM����32���ŵ��˲�����ϵ��1,12bit�з�����
 bit[15:12]  ����
 bit[11:0]   GSM����32���ŵ��˲�����ϵ��0,12bit�з�����
   UNION�ṹ:  GBBP_ADDR_G_32CH_PARA_1REG_UNION */
#define GBBP_ADDR_G_32CH_PARA_1REG_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0xF31C)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  GSM����32���ŵ��˲�����ϵ��3,12bit�з�����
 bit[15:12]  ����
 bit[11:0]   GSM����32���ŵ��˲�����ϵ��2,12bit�з�����
   UNION�ṹ:  GBBP_ADDR_G_32CH_PARA_2REG_UNION */
#define GBBP_ADDR_G_32CH_PARA_2REG_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0xF320)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  GSM����32���ŵ��˲�����ϵ��5,12bit�з�����
 bit[15:12]  ����
 bit[11:0]   GSM����32���ŵ��˲�����ϵ��4,12bit�з�����
   UNION�ṹ:  GBBP_ADDR_G_32CH_PARA_3REG_UNION */
#define GBBP_ADDR_G_32CH_PARA_3REG_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0xF324)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  GSM����32���ŵ��˲�����ϵ��7,12bit�з�����
 bit[15:12]  ����
 bit[11:0]   GSM����32���ŵ��˲�����ϵ��6,12bit�з�����
   UNION�ṹ:  GBBP_ADDR_G_32CH_PARA_4REG_UNION */
#define GBBP_ADDR_G_32CH_PARA_4REG_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0xF328)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  GSM����32���ŵ��˲�����ϵ��9,12bit�з�����
 bit[15:12]  ����
 bit[11:0]   GSM����32���ŵ��˲�����ϵ��8,12bit�з�����
   UNION�ṹ:  GBBP_ADDR_G_32CH_PARA_5REG_UNION */
#define GBBP_ADDR_G_32CH_PARA_5REG_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0xF32C)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  GSM����32���ŵ��˲�����ϵ��11,12bit�з�����
 bit[15:12]  ����
 bit[11:0]   GSM����32���ŵ��˲�����ϵ��10,12bit�з�����
   UNION�ṹ:  GBBP_ADDR_G_32CH_PARA_6REG_UNION */
#define GBBP_ADDR_G_32CH_PARA_6REG_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0xF330)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  GSM����32���ŵ��˲�����ϵ��13,12bit�з�����
 bit[15:12]  ����
 bit[11:0]   GSM����32���ŵ��˲�����ϵ��12,12bit�з�����
   UNION�ṹ:  GBBP_ADDR_G_32CH_PARA_7REG_UNION */
#define GBBP_ADDR_G_32CH_PARA_7REG_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0xF334)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  GSM����32���ŵ��˲�����ϵ��15,12bit�з�����
 bit[15:12]  ����
 bit[11:0]   GSM����32���ŵ��˲�����ϵ��14,12bit�з�����
   UNION�ṹ:  GBBP_ADDR_G_32CH_PARA_8REG_UNION */
#define GBBP_ADDR_G_32CH_PARA_8REG_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0xF338)

/* �Ĵ���˵����
 bit[31:12]  ����
 bit[11:0]   GSM����32���ŵ��˲�����ϵ��16,12bit�з�����
   UNION�ṹ:  GBBP_ADDR_G_32CH_PARA_9REG_UNION */
#define GBBP_ADDR_G_32CH_PARA_9REG_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0xF33C)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:28]  ABB���н����˲���������ݽ�λ�޷�����ģʽѡ��2'd0�������������12bit���޷���14bit��2'd1�������������11bit���޷���14bit��2'd2�������������10bit���޷���14bit��Ĭ������2'd1��
 bit[27:26]  ����
 bit[25:24]  ABB���н����˲���������ݽ�λ�޷�����ģʽѡ��2'd0�������������12bit���޷���14bit��2'd1�������������11bit���޷���14bit��2'd2�������������10bit���޷���14bit��Ĭ������2'd1��
 bit[23:22]  ����
 bit[21:20]  ABB���н����˲���������ݽ�λ�޷�����ģʽѡ��2'd0�������������12bit���޷���14bit��2'd1�������������11bit���޷���14bit��2'd2�������������10bit���޷���14bit��Ĭ������2'd1��
 bit[19:18]  ����
 bit[17:16]  ABB���н����˲���������ݽ�λ�޷�����ģʽѡ��2'd0�������������12bit���޷���14bit��2'd1�������������11bit���޷���14bit��2'd2�������������10bit���޷���14bit��Ĭ������2'd1��
 bit[15:14]  ����
 bit[13:12]  ABB���н����˲���������ݽ�λ�޷�����ģʽѡ��2'd0�������������12bit���޷���14bit��2'd1�������������11bit���޷���14bit��2'd2�������������10bit���޷���14bit��Ĭ������2'd1��
 bit[11:10]  ����
 bit[9:8]    ABB���н����˲���������ݽ�λ�޷�����ģʽѡ��2'd0�������������12bit���޷���14bit��2'd1�������������11bit���޷���14bit��2'd2�������������10bit���޷���14bit��Ĭ������2'd1��
 bit[7:6]    ����
 bit[5:4]    ABB���н����˲���������ݽ�λ�޷�����ģʽѡ��2'd0�������������12bit���޷���14bit��2'd1�������������11bit���޷���14bit��2'd2�������������10bit���޷���14bit��Ĭ������2'd1��
 bit[3:2]    ����
 bit[1:0]    ABB���н����˲���������ݽ�λ�޷�����ģʽѡ��2'd0�������������12bit���޷���14bit��2'd1�������������11bit���޷���14bit��2'd2�������������10bit���޷���14bit��Ĭ������2'd1��
   UNION�ṹ:  GBBP_CLIP_MODE_SEL_UNION */
#define GBBP_CLIP_MODE_SEL_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0xF2E8)

/* �Ĵ���˵����
 bit[31:16]  1w2r˫��RAM��ʱ����
 bit[15:0]   1w2rw˫��RAM��ʱ����
   UNION�ṹ:  GBBP_ADDR_MEM_CTRL1_UNION */
#define GBBP_ADDR_MEM_CTRL1_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0xF018)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  ROM��ʱ����
 bit[15:0]   ����RAM��ʱ����
   UNION�ṹ:  GBBP_ADDR_MEM_CTRL2_UNION */
#define GBBP_ADDR_MEM_CTRL2_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0xF01C)



/***======================================================================***
                     (2/9) register_define_sdr_gdrx_guage
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31]     GDRXֹͣ���壬д1ֹͣ�������㣬д0�����塣
 bit[30]     ʱ��У׼ʹ�ܣ�д1�����������㣬д0�����塣
 bit[29:17]  ����
 bit[16:0]   ʱ��У׼32KHzʱ�Ӹ���
   UNION�ṹ:  GBBP_GDRX_GAUGE_EN_CNF_UNION */
#define GBBP_GDRX_GAUGE_EN_CNF_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x7000)

/* �Ĵ���˵����
 bit[31]     ˯��״̬��ѯ��1������˯�ߡ�
 bit[30]     ����״̬��ѯ��1�����ڲ�����
 bit[29:28]  ����
 bit[27:0]   ʱ��У׼���������������104M�Ӹ���
   UNION�ṹ:  GBBP_GAUGE_RESULT_RPT_UNION */
#define GBBP_GAUGE_RESULT_RPT_ADDR                    (SOC_BBP_GSM_BASE_ADDR + 0x7004)

/* �Ĵ���˵����
 bit[31:13]  ����
 bit[12:0]   IMIʱ�����κ��ж��ϱ�ʱGTC��TDMA QB������������
   UNION�ṹ:  GBBP_IMI_INT_TDMA_QB_UNION */
#define GBBP_IMI_INT_TDMA_QB_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x7008)

/* �Ĵ���˵����
 bit[31:13]  ����
 bit[12:0]   32Kʱ���ж��ϱ�ʱGTC��TDMA QB������������
   UNION�ṹ:  GBBP_SLEEP_INT_TDMA_QB_UNION */
#define GBBP_SLEEP_INT_TDMA_QB_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x700C)



/***======================================================================***
                     (3/9) register_define_g_fe_ctrl
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   ��RFCMOSʹ�þ��巽��ʱ�����gdsp���õ�У׼���¶Ȳ���NV��ֵ��
             ��NV��ֵ�ǿ���ʱ�������¶ȶ�Ӧ�������ߵĲ���ֵ��
   UNION�ṹ:  GBBP_G_AFC_THERM_COM_NV_UNION */
#define GBBP_G_AFC_THERM_COM_NV_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x8600)

/* �Ĵ���˵����
 bit[31:30]  ����
 bit[29:16]  ʹ�þ���AFC����ʱ�����RF��AFC������ֵ��
 bit[15:12]  ����
 bit[11:4]   ѡ���巽��ʱ�����ø�RF��TCXO SSI��ַbit��
 bit[3:1]    ����
 bit[0:0]    ����
   UNION�ṹ:  GBBP_G_RF_SSI_AFC_UNION */
#define GBBP_G_RF_SSI_AFC_ADDR                        (SOC_BBP_GSM_BASE_ADDR + 0x8604)

/* �Ĵ���˵����
 bit[31:29]  ����
 bit[28:28]  ʹ��CPU��ʽ��һ��RF-SSI�����Ƿ�����BBP COMMģ���״̬�źţ������á�
             0����ʾ������1��ʾδ������
 bit[27:25]  ����
 bit[24:24]  GDSPʹ��CPU��ʽ����һ��RF-SSI�������źš�
             �߼������㡣
 bit[23:16]  GDSPʹ��CPU��ʽ����һ��RF-SSI�ļĴ�����ַ��
 bit[15:0]   GDSPʹ��CPU��ʽ����һ��RF-SSI�ļĴ�����Ӧ�����ݡ�
   UNION�ṹ:  GBBP_G_RF_SSI_WRONE_CFG_UNION */
#define GBBP_G_RF_SSI_WRONE_CFG_ADDR                  (SOC_BBP_GSM_BASE_ADDR + 0x8608)

/* �Ĵ���˵����
 bit[31:17]  ����
 bit[16:16]  �� ssi����ʹ���ź�
 bit[15:13]  ����
 bit[12:12]  дһ��rf-ssi����ʹ���ź�
 bit[11:9]   ����
 bit[8:8]    g-afc ssi����ʹ���ź�
 bit[7:5]    ����
 bit[4:4]    g-rf-ram ssi����ʹ���ź�
 bit[3:1]    ����
 bit[0:0]    g-gagc ssi����ʹ���ź�
   UNION�ṹ:  GBBP_G_RF_SSI_REQ_EN_CFG_UNION */
#define GBBP_G_RF_SSI_REQ_EN_CFG_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x860C)

/* �Ĵ���˵����
 bit[31:13]  ����
 bit[12:12]  дssi-ram���ָʾ�źš�
             1����ʾ���ڻض���
             0����ʾ��ɻض�������
 bit[11:9]   ����
 bit[8:8]    �ض����ָʾ�źš�
             1����ʾ���ڻض���
             0����ʾ��ɻض�������
 bit[7:7]    ����
 bit[6:4]    RF-SSI�ض��Ĵ���������
             ����ֵΪ0~7����Ӧ�Ļض��Ĵ�������Ϊ1~8��
             ��ע������Ϊ0��ʾ�ض�һ���Ĵ�����
 bit[3:1]    ����
 bit[0:0]    ����RF-SSI�Ĵ����ض���
             �߼��������źš�
   UNION�ṹ:  GBBP_G_RF_SSI_RD_CFG_UNION */
#define GBBP_G_RF_SSI_RD_CFG_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x8610)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:0]   SSI�ض���������0��
   UNION�ṹ:  GBBP_G_RF_SSI_RD_0DATA_UNION */
#define GBBP_G_RF_SSI_RD_0DATA_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x8614)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:0]   SSI�ض���������1��
   UNION�ṹ:  GBBP_G_RF_SSI_RD_1DATA_UNION */
#define GBBP_G_RF_SSI_RD_1DATA_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x8618)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:0]   SSI�ض���������2��
   UNION�ṹ:  GBBP_G_RF_SSI_RD_2DATA_UNION */
#define GBBP_G_RF_SSI_RD_2DATA_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x861C)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:0]   SSI�ض���������3��
   UNION�ṹ:  GBBP_G_RF_SSI_RD_3DATA_UNION */
#define GBBP_G_RF_SSI_RD_3DATA_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x8620)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:0]   SSI�ض���������4��
   UNION�ṹ:  GBBP_G_RF_SSI_RD_4DATA_UNION */
#define GBBP_G_RF_SSI_RD_4DATA_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x8624)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:0]   SSI�ض���������5��
   UNION�ṹ:  GBBP_G_RF_SSI_RD_5DATA_UNION */
#define GBBP_G_RF_SSI_RD_5DATA_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x8628)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:0]   SSI�ض���������6��
   UNION�ṹ:  GBBP_G_RF_SSI_RD_6DATA_UNION */
#define GBBP_G_RF_SSI_RD_6DATA_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x862C)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:0]   SSI�ض���������7��
   UNION�ṹ:  GBBP_G_RF_SSI_RD_7DATA_UNION */
#define GBBP_G_RF_SSI_RD_7DATA_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x8630)

/* �Ĵ���˵����
 bit[31:5]   ����
 bit[4]      GTC��ʽMIPI�ͻ��˹���ʹ�ܿ��أ�1��ʾͨ���򿪣�0��ʾͨ���رա�
 bit[3:1]    ����
 bit[0]      CPU��ʽMIPI�ͻ��˹���ʹ�ܿ��أ�1��ʾͨ���򿪣�0��ʾͨ���رա�
   UNION�ṹ:  GBBP_G_MIPI_REQ_EN_CFG_UNION */
#define GBBP_G_MIPI_REQ_EN_CFG_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x8634)

/* �Ĵ���˵����
 bit[31:17]  ����
 bit[16:16]  �����ʽ����MIPI����ʱ�Ĵ��������źš�
 bit[15]     ����
 bit[14:8]   �����ʽ����MIPI����ʱ�����üĴ����ĸ��������÷�Χ��1��127��
 bit[7]      ����
 bit[6:0]    �����ʽ����MIPI����ʱ�����üĴ�������׵�ַ��
   UNION�ṹ:  GBBP_G_MIPI_CMD_CFG_UNION */
#define GBBP_G_MIPI_CMD_CFG_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x8638)

/* �Ĵ���˵����
 bit[31:17]  ����
 bit[16]     �������SSI״̬���쳣����ĸ�λ�����źš�
 bit[15:1]   ����
 bit[0]      �������MIPI״̬���쳣����ĸ�λ�����źš�
   UNION�ṹ:  GBBP_G_RF_SSI_MIPI_CLR_REG_UNION */
#define GBBP_G_RF_SSI_MIPI_CLR_REG_ADDR               (SOC_BBP_GSM_BASE_ADDR + 0x863C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ABB������������Ȼ�롢����ģʽѡ��
             1����ʾ��Ȼ�룬0����ʾ���룬GSMר�á�
   UNION�ṹ:  GBBP_G_ABB_CFG_SEL_UNION */
#define GBBP_G_ABB_CFG_SEL_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x8644)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0:0]    ��ģ��G�ķ�ʽѡ��
             0�������ѣ�
             1���Ǳ����ѡ�
   UNION�ṹ:  GBBP_G_MASTER_MEA_G_EN_UNION */
#define GBBP_G_MASTER_MEA_G_EN_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x8658)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:1]    ����ģʽʹ�ܡ�
 bit[0:0]    ����ģʽ�£�����ͨ��ʹ�ܿ��ء�
   UNION�ṹ:  GBBP_G_ABB_TRX_LOOP_EN_UNION */
#define GBBP_G_ABB_TRX_LOOP_EN_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x865C)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define GBBP_G_DBG_REG0_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x8660)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define GBBP_G_DBG_REG1_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x8664)

/* �Ĵ���˵����
 bit[31:27]  ����
 bit[26:16]  AuxDAC�򿪿��������ã��ÿ�������gtc_gapc_en�߿��ź������ط�����AuxDAC��
 bit[15:11]  ����
 bit[10:0]   AuxDAC�򿪿��������ã��ÿ�������gtc_gapc_en�߿��½��ط�����AuxDAC��
   UNION�ṹ:  GBBP_G_AUXDAC_EN_CFG_UNION */
#define GBBP_G_AUXDAC_EN_CFG_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x8690)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:2]    FIFO���ź��ϱ�
 bit[1:1]    FIFO���ź��ϱ�
 bit[0:0]    fifo��λ�źţ���FIFO״̬�쳣ʱ������Ϊ1����������
   UNION�ṹ:  GBBP_DATA_FIFO_RST_UNION */
#define GBBP_DATA_FIFO_RST_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x8694)



/***======================================================================***
                     (4/9) register_define_g_fe_ctrl_mem
 ***======================================================================***/
/* �Ĵ���˵����g��Ƶ����ƵH��rfic-ssi RAM
 bit[31:24]  ����
 bit[23:16]  g��Ƶ��ǿ���rfic-ssi RAM��
             ���ݣ�
             [23:16]��rfic�ļĴ�����ַ��
 bit[15:0]   g��Ƶ��ǿ���rfic-ssi RAM��
             ����
             [15:0]��rfic�ļĴ������ݡ�
   UNION�ṹ:  GBBP_G_RFIC_SSI_RAM_UNION */
#define GBBP_G_RFIC_SSI_RAM_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x8200)
#define GBBP_G_RFIC_SSI_RAM_MEMDEPTH  (192)

/* �Ĵ���˵����g��Ƶ����Ƶ��mipi RAM
   ��      ����g��Ƶ����Ƶ��mipi RAM,֧��128��ָ�
   UNION�ṹ ���� */
#define GBBP_G_MIPI_SSI_RAM_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x8000)
#define GBBP_G_MIPI_SSI_RAM_MEMDEPTH  (128)



/***======================================================================***
                     (5/9) register_define_gtc_mem
 ***======================================================================***/
/* �Ĵ���˵������Ч��ַ��Χ0x0000��0x07FF
 bit[31:16]  ����
 bit[15:0]   GTCָ������RAM��ÿ��32bit��ֻ�е�16bit��Ч��
   UNION�ṹ:  GBBP_GTC_CFG_RAM_UNION */
#define GBBP_GTC_CFG_RAM_ADDR                         (SOC_BBP_GSM_BASE_ADDR + 0x0)
#define GBBP_GTC_CFG_RAM_MEMDEPTH  (512)



/***======================================================================***
                     (6/9) register_define_g_addr_2x_mem
 ***======================================================================***/
/* �Ĵ���˵������Ч��ַ��Χ0x0000��0x039F
   ��      ���������ϱ�RAM��СΪ232X32bit
            �����ϱ�ram,��ʽ�μ�ǰ���˵��
   UNION�ṹ ���� */
#define GBBP_DEC_RPT_RAM_ADDR                         (SOC_BBP_GSM_BASE_ADDR + 0x2000)
#define GBBP_DEC_RPT_RAM_MEMDEPTH  (232)

/* �Ĵ���˵������Ч��ַ��Χ0x0800��0x0843
   ��      ����������ģʽ����Ӧ����жϺ��ȡѵ�����������ϱ�RAM����.
            ѵ�����������ϱ�RAM��д���ݣ���RAM���ڴ洢DAGC֮�󣬽��֮ǰ��ѵ��������ֵ�������Ⱥ�˳��Ϊ1+26+7,����TSCǰһ��symbol�ͺ�7��symbol ����ֵ��DAGC�������IQ���ݡ�ÿ�д��2�����ţ���ʽΪ{I1,Q1,I0,Q0}��˳������ҵ͡�
   UNION�ṹ ���� */
#define GBBP_TSC_RAM_ADDR                             (SOC_BBP_GSM_BASE_ADDR + 0x2800)
#define GBBP_TSC_RAM_MEMDEPTH  (16)

/* �Ĵ���˵������Ч��ַ��Χ0x0500��0x057F
   ��      ����GAPC����ϵ������RAM���洢�ṹ��ǰ���ͼʾ
   UNION�ṹ ���� */
#define GBBP_CPU_GAPC_CONFIG_RAM_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x2500)
#define GBBP_CPU_GAPC_CONFIG_RAM_MEMDEPTH  (32)

/* �Ĵ���˵��������GPHYֱ�����ɴ��룬�����г��˼Ĵ���
   ��      ����NB������Ϣ�ϱ�
   UNION�ṹ ���� */
#define GBBP_NB_DEC_RPT_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x2004)
#define GBBP_NB_DEC_RPT_MEMDEPTH  (1)

/* �Ĵ���˵��������GPHYֱ�����ɴ��룬�����г��˼Ĵ���
   ��      ����SB������Ϣ�ϱ�
   UNION�ṹ ���� */
#define GBBP_SB_DEC_RPT_ADDR                          (SOC_BBP_GSM_BASE_ADDR + 0x2398)
#define GBBP_SB_DEC_RPT_MEMDEPTH  (1)



/***======================================================================***
                     (7/9) register_define_g_addr_3x_mem
 ***======================================================================***/
/* �Ĵ���˵������Ч��ַ��Χ0x0000��0x027F
   ��      ����CPU�·��Ĵ��������ݣ����Բμ����������ݸ�ʽ˵��
   UNION�ṹ ���� */
#define GBBP_UL_CODE_CFG_RAM_ADDR                     (SOC_BBP_GSM_BASE_ADDR + 0x3000)
#define GBBP_UL_CODE_CFG_RAM_MEMDEPTH  (160)

/* �Ĵ���˵������Ч��ַ��Χ0x0300��0x031F
   ��      ����CPU�ӿ����õ�ȥ3��5��г��ģ�����RAM���ӿ�RAM��Ԥ��4�������ÿ�����ռ��2����ַ���ֱ�Ϊ3��г��������B������5��г��������C�������ɲμ����ݸ�ʽ˵������������ķ��ʵ�ַΪ8����ַ��BBP�ڲ�������֡ͷƹ�Ҵ���
   UNION�ṹ ���� */
#define GBBP_CPU_HD35_CONFIG_RAM_ADDR                 (SOC_BBP_GSM_BASE_ADDR + 0x3300)
#define GBBP_CPU_HD35_CONFIG_RAM_MEMDEPTH  (8)



/***======================================================================***
                     (8/9) register_define_g_addr_5x_mem
 ***======================================================================***/
/* �Ĵ���˵������Ч��ַ��Χ0x0400��0x055B
   ��      ����SB,NB�����ֵ��CPU�ӿڵİ���ram��4��6bit�����ֵ������ռ��imi_rddata��5��0��13��8��21��16��29��24bitλ��
   UNION�ṹ ���� */
#define GBBP_CARRY_RAM_ADDR                           (SOC_BBP_GSM_BASE_ADDR + 0x5400)
#define GBBP_CARRY_RAM_MEMDEPTH  (88)

/* �Ĵ���˵������Ч��ַ��Χ0x0600��0x0638
 bit[31:30]  ����
 bit[29:0]   CPU�·��Ĵ��������ݣ���30bit��Ч
   UNION�ṹ:  GBBP_UL_MAP_CFG_RAM_UNION */
#define GBBP_UL_MAP_CFG_RAM_ADDR                      (SOC_BBP_GSM_BASE_ADDR + 0x5600)
#define GBBP_UL_MAP_CFG_RAM_MEMDEPTH  (15)

/* �Ĵ���˵������Ч��ַ��Χ0x08C8��0x09FF
   ��      ����Ϊ�˱�������޷���ʱ��ÿʱ϶�Ľ���жϺ��ȡ�����ֵ�����ӱ��ϱ�RAM��
            ��0x5400~0x555b��ַ�У�ѡȡUSF bit��Ӧ�Ľ����ֵ�ϱ���ÿ��NB �̶��ϱ�13����ֵ��ÿ֡����ϱ�78����ֵ��
            ÿʱ϶����ֵ������ѡȡ0x5400~0x555b���е�0x00,0x10,0x20,0x30,0x34��0x44,0x54,0x64,0x94,0xa8,0xc0��13����ַ�����ݡ���0x5400���������ڣ���RAM���Դ洢6��ʱ϶��USF��ֵ����5400��ַ�����ܱ���1��ʱ϶����ֵ��
   UNION�ṹ ���� */
#define GBBP_USF_VALUE_RPT_RAM_ADDR                   (SOC_BBP_GSM_BASE_ADDR + 0x58C8)
#define GBBP_USF_VALUE_RPT_RAM_MEMDEPTH  (78)



/***======================================================================***
                     (9/9) register_define_g_addr_6x_mem
 ***======================================================================***/
/* �Ĵ���˵����ֱ��ƫִ����ֵ�ֵ�ֵ�洢RAM����0x00FF����
 bit[31:30]  ����
 bit[29:16]  ֱ��ƫִ����ֵ�ֵ�ֵ�洢RAM���ʵ�ַ��һ����ַ��ʾ28bit�����е�16bit�е�14bit��ʾI·����16bit�е�14bitΪQ·�����õ�14bitΪ�з�������
 bit[15:14]  ����
 bit[13:0]   ֱ��ƫִ����ֵ�ֵ�ֵ�洢RAM���ʵ�ַ��һ����ַ��ʾ28bit�����е�16bit�е�14bit��ʾI·����16bit�е�14bitΪQ·�����õ�14bitΪ�з�������
   UNION�ṹ:  GBBP_DC_OFFSET_RAM_UNION */
#define GBBP_DC_OFFSET_RAM_ADDR                       (SOC_BBP_GSM_BASE_ADDR + 0x6000)
#define GBBP_DC_OFFSET_RAM_MEMDEPTH  (64)

/* �Ĵ���˵����ǰ��ͨ���������ֵ�洢RAM����0x04FF����
 bit[31:11]  ����
 bit[10:0]   ǰ��ͨ���������ֵ�洢RAM��CHANNEL_GAIN�ο����òμ���19���˱���ʵ��ʹ��ʱ����Ҫ����ʵ���ó���
   UNION�ṹ:  GBBP_CHANNEL_GAIN_RAM_UNION */
#define GBBP_CHANNEL_GAIN_RAM_ADDR                    (SOC_BBP_GSM_BASE_ADDR + 0x6400)
#define GBBP_CHANNEL_GAIN_RAM_MEMDEPTH  (64)





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
                     (1/9) register_define_gbbp_addr
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : GBBP_CPU_SOFT_AFC_VALUE_UNION
 �ṹ˵��  : CPU_SOFT_AFC_VALUE �Ĵ����ṹ���塣��ַƫ����:0x1000����ֵ:0x00002000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_soft_afc_value_reg;
    struct
    {
        unsigned int  cpu_soft_afc_value  : 14; /* bit[0-13] : ������������AFCֵ����cpu_soft_afc_renew��Чʱ������ֵ�����VCO�� */
        unsigned int  reserved            : 17; /* bit[14-30]: ���� */
        unsigned int  cpu_soft_afc_en_imi : 1;  /* bit[31]   : ������������AFCֵʹ���źţ���ƽ�źţ�����Ч���ڴ��ź�Ϊ���ڼ䣬GBBP���ڽ���AFC�����жϣ������VCO��ֵ��cpu_soft_afc_value[13:0]�ṩ�� */
    } reg;
} GBBP_CPU_SOFT_AFC_VALUE_UNION;
#define GBBP_CPU_SOFT_AFC_VALUE_cpu_soft_afc_value_START   (0)
#define GBBP_CPU_SOFT_AFC_VALUE_cpu_soft_afc_value_END     (13)
#define GBBP_CPU_SOFT_AFC_VALUE_cpu_soft_afc_en_imi_START  (31)
#define GBBP_CPU_SOFT_AFC_VALUE_cpu_soft_afc_en_imi_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_SOFT_VALUE_RENEW_UNION
 �ṹ˵��  : CPU_SOFT_VALUE_RENEW �Ĵ����ṹ���塣��ַƫ����:0x1004����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_soft_value_renew_reg;
    struct
    {
        unsigned int  cpu_soft_afc_renew_imi : 1;  /* bit[0]   : ����������������AFCֵ�������źš����ź���cpu_soft_afc_en_imiΪ��ʱ����Ч��д1�߼������㡣 */
        unsigned int  reserved               : 31; /* bit[1-31]: ���� */
    } reg;
} GBBP_CPU_SOFT_VALUE_RENEW_UNION;
#define GBBP_CPU_SOFT_VALUE_RENEW_cpu_soft_afc_renew_imi_START  (0)
#define GBBP_CPU_SOFT_VALUE_RENEW_cpu_soft_afc_renew_imi_END    (0)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_CI_THRES_CFG_UNION
 �ṹ˵��  : CPU_CI_THRES_CFG �Ĵ����ṹ���塣��ַƫ����:0x1008����ֵ:0x00030003�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_ci_thres_cfg_reg;
    struct
    {
        unsigned int  cpu_gmsk_ci_thres : 3;  /* bit[0-2]  : GMSK���Ʒ�ʽ�£�CI�о�����ѡ���źţ�����ɸѡnb-afc�������С�ڸ����ޣ�afc_valui_i��afc_value_q�����0�����������ʵֵ��
                                                             cpu_psk_ci_thres[2:0]=0 C>I
                                                             cpu_psk_ci_thres[2:0]=1 C>4I
                                                             cpu_psk_ci_thres[2:0]=2 C>8I
                                                             cpu_psk_ci_thres[2:0]=3 C>16I
                                                             cpu_psk_ci_thres[2:0]=4 C>32I
                                                             cpu_psk_ci_thres[2:0]=5 C>64I
                                                             cpu_psk_ci_thres[2:0]=6 C>128I
                                                             cpu_psk_ci_thres[2:0]=7 ���о���ֱ�������
                                                             Ĭ��ֵ��3�� */
        unsigned int  reserved_0        : 13; /* bit[3-15] : ���� */
        unsigned int  cpu_psk_ci_thres  : 3;  /* bit[16-18]: 8PSK���Ʒ�ʽ�£�CI�о�����ѡ���źţ�����ɸѡnb-afc�������С�ڸ����ޣ�afc_valui_i��afc_value_q�����0�����������ʵֵ��
                                                             cpu_gmsk_ci_thres[2:0]=0 C>I
                                                             cpu_gmsk_ci_thres[2:0]=1 C>4I
                                                             cpu_gmsk_ci_thres[2:0]=2 C>8I
                                                             cpu_gmsk_ci_thres[2:0]=3 C>16I
                                                             cpu_gmsk_ci_thres[2:0]=4 C>32I
                                                             cpu_gmsk_ci_thres[2:0]=5 C>64I
                                                             cpu_gmsk_ci_thres[2:0]=6 C>128I
                                                             cpu_gmsk_ci_thres[2:0]=7 ���о���ֱ�������
                                                             Ĭ��ֵ��3�� */
        unsigned int  reserved_1        : 13; /* bit[19-31]: ���� */
    } reg;
} GBBP_CPU_CI_THRES_CFG_UNION;
#define GBBP_CPU_CI_THRES_CFG_cpu_gmsk_ci_thres_START  (0)
#define GBBP_CPU_CI_THRES_CFG_cpu_gmsk_ci_thres_END    (2)
#define GBBP_CPU_CI_THRES_CFG_cpu_psk_ci_thres_START   (16)
#define GBBP_CPU_CI_THRES_CFG_cpu_psk_ci_thres_END     (18)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_NB_AFC_NUM_UNION
 �ṹ˵��  : CPU_NB_AFC_NUM �Ĵ����ṹ���塣��ַƫ����:0x100C����ֵ:0x00000002�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_nb_afc_num_reg;
    struct
    {
        unsigned int  cpu_nb_afc_num : 3;  /* bit[0-2] : һ�׻����ڼ���NB-AFC��NB����ѡ���źţ�
                                                         0����ʾѡ��1��NB�����㣻
                                                         1����ʾѡ��2��NB�����㣻
                                                         2����ʾѡ��4��NB�����㣻
                                                         3����ʾѡ��8��NB�����㣻
                                                         4����ʾѡ��16��NB�����㣻
                                                         5����ʾѡ��32��NB�����㣻
                                                         6����ʾѡ��64��NB�����㡣
                                                         ��DRX�ڼ��Ƽ�����2��DRX�ڼ��Ƽ�����Ϊ0�� */
        unsigned int  reserved       : 29; /* bit[3-31]: ���� */
    } reg;
} GBBP_CPU_NB_AFC_NUM_UNION;
#define GBBP_CPU_NB_AFC_NUM_cpu_nb_afc_num_START  (0)
#define GBBP_CPU_NB_AFC_NUM_cpu_nb_afc_num_END    (2)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_AFC_CFG_UNION
 �ṹ˵��  : CPU_AFC_CFG �Ĵ����ṹ���塣��ַƫ����:0x1010����ֵ:0x00002000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_afc_cfg_reg;
    struct
    {
        unsigned int  cpu_afc_init        : 14; /* bit[0-13] : G AFC��ʼֵ��
                                                               ��RFCMOSʹ�þ��巽��ʱ�����ø�ֵΪ14'h1fff�����V3R2����ϵͳ����������������ʱ��ʹ��ԭ��������ֵ�� */
        unsigned int  reserved_0          : 1;  /* bit[14]   : ���� */
        unsigned int  cpu_afc_init_en_imi : 1;  /* bit[15]   : AFC��ʼֵд��ʹ�ܣ�CPUд1���߼������㡣 */
        unsigned int  reserved_1          : 15; /* bit[16-30]: ���� */
        unsigned int  cpu_fb_afc_clr_imi  : 1;  /* bit[31]   : FB-AFC�����źţ�д1��Ч���߼������� */
    } reg;
} GBBP_CPU_AFC_CFG_UNION;
#define GBBP_CPU_AFC_CFG_cpu_afc_init_START         (0)
#define GBBP_CPU_AFC_CFG_cpu_afc_init_END           (13)
#define GBBP_CPU_AFC_CFG_cpu_afc_init_en_imi_START  (15)
#define GBBP_CPU_AFC_CFG_cpu_afc_init_en_imi_END    (15)
#define GBBP_CPU_AFC_CFG_cpu_fb_afc_clr_imi_START   (31)
#define GBBP_CPU_AFC_CFG_cpu_fb_afc_clr_imi_END     (31)


/*****************************************************************************
 �ṹ��    : GBBP_AFC_VALUE_I_CPU_UNION
 �ṹ˵��  : AFC_VALUE_I_CPU �Ĵ����ṹ���塣��ַƫ����:0x1014����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      afc_value_i_cpu_reg;
    struct
    {
        unsigned int  afc_value_i : 19; /* bit[0-18] : �ϱ���afcʵ������ۼ�ֵ��ֱ���ɳ��ۼ�ģ������������á� */
        unsigned int  reserved    : 13; /* bit[19-31]: ���� */
    } reg;
} GBBP_AFC_VALUE_I_CPU_UNION;
#define GBBP_AFC_VALUE_I_CPU_afc_value_i_START  (0)
#define GBBP_AFC_VALUE_I_CPU_afc_value_i_END    (18)


/*****************************************************************************
 �ṹ��    : GBBP_AFC_VALUE_Q_CPU_UNION
 �ṹ˵��  : AFC_VALUE_Q_CPU �Ĵ����ṹ���塣��ַƫ����:0x1018����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      afc_value_q_cpu_reg;
    struct
    {
        unsigned int  afc_value_q : 19; /* bit[0-18] : �ϱ���afc�鲿����ۼ�ֵ��ֱ���ɳ��ۼ�ģ������������á� */
        unsigned int  reserved    : 13; /* bit[19-31]: ���� */
    } reg;
} GBBP_AFC_VALUE_Q_CPU_UNION;
#define GBBP_AFC_VALUE_Q_CPU_afc_value_q_START  (0)
#define GBBP_AFC_VALUE_Q_CPU_afc_value_q_END    (18)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_AFC_PWM_WIDTH_SEL_UNION
 �ṹ˵��  : CPU_AFC_PWM_WIDTH_SEL �Ĵ����ṹ���塣��ַƫ����:0x101C����ֵ:0x00000002�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_afc_pwm_width_sel_reg;
    struct
    {
        unsigned int  cpu_afc_pwm_width_sel : 2;  /* bit[0-1] : 0��ʾʹ��10bit��PDMת��ģ�飻
                                                                1��ʾʹ��12bit��PDMת��ģ�飻
                                                                2��ʾʹ��14bit��PDMת��ģ�顣 */
        unsigned int  reserved              : 30; /* bit[2-31]: ���� */
    } reg;
} GBBP_CPU_AFC_PWM_WIDTH_SEL_UNION;
#define GBBP_CPU_AFC_PWM_WIDTH_SEL_cpu_afc_pwm_width_sel_START  (0)
#define GBBP_CPU_AFC_PWM_WIDTH_SEL_cpu_afc_pwm_width_sel_END    (1)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_NB_AFC_NUM_CLR_UNION
 �ṹ˵��  : CPU_NB_AFC_NUM_CLR �Ĵ����ṹ���塣��ַƫ����:0x1020����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_nb_afc_num_clr_reg;
    struct
    {
        unsigned int  cpu_nb_afc_num_clr_imi : 1;  /* bit[0]   : ��ʾ���¿�ʼͳ��NB-AFC��NB-BURST������cpuд1���߼������㡣
                                                                 ��ʱ�������ǰ�ۼ�NB������Ӧ��NB-AFC�˲�ֵ�������ȸı�cpu_nb_afc_num�����ô�ֵΪ1�� */
        unsigned int  reserved               : 31; /* bit[1-31]: ���� */
    } reg;
} GBBP_CPU_NB_AFC_NUM_CLR_UNION;
#define GBBP_CPU_NB_AFC_NUM_CLR_cpu_nb_afc_num_clr_imi_START  (0)
#define GBBP_CPU_NB_AFC_NUM_CLR_cpu_nb_afc_num_clr_imi_END    (0)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_FB_KP_KINT_UNION
 �ṹ˵��  : CPU_FB_KP_KINT �Ĵ����ṹ���塣��ַƫ����:0x1024����ֵ:0x00160000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_fb_kp_kint_reg;
    struct
    {
        unsigned int  reserved_0       : 16; /* bit[0-15] : ���� */
        unsigned int  cpu_afc_maxfbnum : 5;  /* bit[16-20]: ����FB-AFC�о����ܵ�FB���������䷶ΧΪ��17~31
                                                            Ĭ������Ϊ��22 */
        unsigned int  reserved_1       : 11; /* bit[21-31]: ���� */
    } reg;
} GBBP_CPU_FB_KP_KINT_UNION;
#define GBBP_CPU_FB_KP_KINT_cpu_afc_maxfbnum_START  (16)
#define GBBP_CPU_FB_KP_KINT_cpu_afc_maxfbnum_END    (20)


/*****************************************************************************
 �ṹ��    : GBBP_FB_TIMEBASE_RPT_UNION
 �ṹ˵��  : FB_TIMEBASE_RPT �Ĵ����ṹ���塣��ַƫ����:0x1028����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      fb_timebase_rpt_reg;
    struct
    {
        unsigned int  fb_timebase_qb_rpt : 13; /* bit[0-12] : �ͺ�FB1215QB��timebase��QB�����������á� */
        unsigned int  reserved_0         : 3;  /* bit[13-15]: ���� */
        unsigned int  fb_timebase_fn_rpt : 11; /* bit[16-26]: �ͺ�FB1215QB��timebase��FNģ2048������������Χ��0~2047�����á� */
        unsigned int  reserved_1         : 5;  /* bit[27-31]: ���� */
    } reg;
} GBBP_FB_TIMEBASE_RPT_UNION;
#define GBBP_FB_TIMEBASE_RPT_fb_timebase_qb_rpt_START  (0)
#define GBBP_FB_TIMEBASE_RPT_fb_timebase_qb_rpt_END    (12)
#define GBBP_FB_TIMEBASE_RPT_fb_timebase_fn_rpt_START  (16)
#define GBBP_FB_TIMEBASE_RPT_fb_timebase_fn_rpt_END    (26)


/*****************************************************************************
 �ṹ��    : GBBP_FB_FN_RPT_UNION
 �ṹ˵��  : FB_FN_RPT �Ĵ����ṹ���塣��ַƫ����:0x102C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      fb_fn_rpt_reg;
    struct
    {
        unsigned int  fb_fn_rpt3 : 6;  /* bit[0-5]  : FB����֡λ��T3�������ϱ��� */
        unsigned int  reserved_0 : 2;  /* bit[6-7]  : ���� */
        unsigned int  fb_fn_rpt2 : 5;  /* bit[8-12] : FB����֡λ��T2�������ϱ��� */
        unsigned int  reserved_1 : 3;  /* bit[13-15]: ���� */
        unsigned int  fb_fn_rpt1 : 11; /* bit[16-26]: FB����֡λ��T1�������ϱ��� */
        unsigned int  reserved_2 : 5;  /* bit[27-31]: ���� */
    } reg;
} GBBP_FB_FN_RPT_UNION;
#define GBBP_FB_FN_RPT_fb_fn_rpt3_START  (0)
#define GBBP_FB_FN_RPT_fb_fn_rpt3_END    (5)
#define GBBP_FB_FN_RPT_fb_fn_rpt2_START  (8)
#define GBBP_FB_FN_RPT_fb_fn_rpt2_END    (12)
#define GBBP_FB_FN_RPT_fb_fn_rpt1_START  (16)
#define GBBP_FB_FN_RPT_fb_fn_rpt1_END    (26)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_FB_TIMES_THRES_UNION
 �ṹ˵��  : CPU_FB_TIMES_THRES �Ĵ����ṹ���塣��ַƫ����:0x1030����ֵ:0x03652011�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_fb_times_thres_reg;
    struct
    {
        unsigned int  cpu_fb_failed_thres : 2;  /* bit[0-1]  : FBͬ��ʧ�ܴ������ޡ�
                                                               2'd0��ʹ�õ�����ֵΪ1��
                                                               2'd1��ʹ�õ�����ֵΪ2��
                                                               2'd2��ʹ�õ�����ֵΪ3��
                                                               2'd3��ʹ�õ�����ֵΪ4��
                                                               ȱʡֵΪ2'd1�� */
        unsigned int  reserved_0          : 2;  /* bit[2-3]  : ���� */
        unsigned int  cpu_sb_failed_thres : 2;  /* bit[4-5]  : SBͬ��ʧ�ܴ������ޡ�
                                                               2'd0��ʹ�õ�����ֵΪ1��
                                                               2'd1��ʹ�õ�����ֵΪ2��
                                                               2'd2��ʹ�õ�����ֵΪ3��
                                                               ��������Ч��
                                                               ȱʡֵΪ2'd1�� */
        unsigned int  reserved_1          : 6;  /* bit[6-11] : ���� */
        unsigned int  cpu_fb_peak_window  : 17; /* bit[12-28]: FB�������ķ��Ÿ�������ֵ��
                                                               ȱʡֵΪ17'd13906����Ӧ11֡+1ʱ϶������������ʱ�䳤�ȴ��ڸ�ֵʱ��FB����������
                                                               ע��13906=11*1250+156 */
        unsigned int  reserved_2          : 3;  /* bit[29-31]: ���� */
    } reg;
} GBBP_CPU_FB_TIMES_THRES_UNION;
#define GBBP_CPU_FB_TIMES_THRES_cpu_fb_failed_thres_START  (0)
#define GBBP_CPU_FB_TIMES_THRES_cpu_fb_failed_thres_END    (1)
#define GBBP_CPU_FB_TIMES_THRES_cpu_sb_failed_thres_START  (4)
#define GBBP_CPU_FB_TIMES_THRES_cpu_sb_failed_thres_END    (5)
#define GBBP_CPU_FB_TIMES_THRES_cpu_fb_peak_window_START   (12)
#define GBBP_CPU_FB_TIMES_THRES_cpu_fb_peak_window_END     (28)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_FB_ENERG_THRES_UNION
 �ṹ˵��  : CPU_FB_ENERG_THRES �Ĵ����ṹ���塣��ַƫ����:0x1034����ֵ:0x00200000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_fb_energ_thres_reg;
    struct
    {
        unsigned int  reserved_0        : 12; /* bit[0-11] : ���� */
        unsigned int  cpu_fb_peak_thres : 11; /* bit[12-22]: FB�����ɹ������ޣ���FB�����õ������������ֵ���ڸ�����ʱ������Ϊ�����ɹ���ȱʡֵΪ512�� */
        unsigned int  reserved_1        : 9;  /* bit[23-31]: ���� */
    } reg;
} GBBP_CPU_FB_ENERG_THRES_UNION;
#define GBBP_CPU_FB_ENERG_THRES_cpu_fb_peak_thres_START  (12)
#define GBBP_CPU_FB_ENERG_THRES_cpu_fb_peak_thres_END    (22)


/*****************************************************************************
 �ṹ��    : GBBP_AFC_RPT_UNION
 �ṹ˵��  : AFC_RPT �Ĵ����ṹ���塣��ַƫ����:0x1038����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      afc_rpt_reg;
    struct
    {
        unsigned int  afc_vctxo_cpu       : 14; /* bit[0-13] : AFC�����VCTXO���Ƶ�ѹ�� */
        unsigned int  reserved            : 2;  /* bit[14-15]: ���� */
        unsigned int  afc_vctxo_16bit_cpu : 16; /* bit[16-31]: AFC�����16����VCTXO�Ŀ��Ƶ�ѹ�ź� */
    } reg;
} GBBP_AFC_RPT_UNION;
#define GBBP_AFC_RPT_afc_vctxo_cpu_START        (0)
#define GBBP_AFC_RPT_afc_vctxo_cpu_END          (13)
#define GBBP_AFC_RPT_afc_vctxo_16bit_cpu_START  (16)
#define GBBP_AFC_RPT_afc_vctxo_16bit_cpu_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_FB_RPT1_UNION
 �ṹ˵��  : FB_RPT1 �Ĵ����ṹ���塣��ַƫ����:0x103C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      fb_rpt1_reg;
    struct
    {
        unsigned int  fb_pos_cpu    : 13; /* bit[0-12] : FB�����õ���FBʱ϶ͷλ�ã������gtc_timebase��λ�á� */
        unsigned int  reserved_0    : 3;  /* bit[13-15]: ���� */
        unsigned int  sb_pos_offset : 8;  /* bit[16-23]: SB����λ�������FBλ�õ�ƫ���� */
        unsigned int  reserved_1    : 8;  /* bit[24-31]: ���� */
    } reg;
} GBBP_FB_RPT1_UNION;
#define GBBP_FB_RPT1_fb_pos_cpu_START     (0)
#define GBBP_FB_RPT1_fb_pos_cpu_END       (12)
#define GBBP_FB_RPT1_sb_pos_offset_START  (16)
#define GBBP_FB_RPT1_sb_pos_offset_END    (23)


/*****************************************************************************
 �ṹ��    : GBBP_FB_RPT2_UNION
 �ṹ˵��  : FB_RPT2 �Ĵ����ṹ���塣��ַƫ����:0x1040����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      fb_rpt2_reg;
    struct
    {
        unsigned int  fb_square_max_cpu : 19; /* bit[0-18] : ����FB�������������ֵ�������á� */
        unsigned int  reserved          : 13; /* bit[19-31]: ���� */
    } reg;
} GBBP_FB_RPT2_UNION;
#define GBBP_FB_RPT2_fb_square_max_cpu_START  (0)
#define GBBP_FB_RPT2_fb_square_max_cpu_END    (18)


/*****************************************************************************
 �ṹ��    : GBBP_SB_POS_RPT1_UNION
 �ṹ˵��  : SB_POS_RPT1 �Ĵ����ṹ���塣��ַƫ����:0x1044����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      sb_pos_rpt1_reg;
    struct
    {
        unsigned int  sb_pos_cpu   : 13; /* bit[0-12] : SB�����������ֵ�����timebase��λ�ã���SB����ʧ�ܣ����ϱ�ֵ��Ч�� */
        unsigned int  reserved_0   : 3;  /* bit[13-15]: ���� */
        unsigned int  srch_fsm_cpu : 2;  /* bit[16-17]: ����״̬���ϱ��źţ�
                                                        0��Idle State��
                                                        1��FB����״̬��
                                                        2��AFC�ж�״̬��
                                                        3��SB����״̬�� */
        unsigned int  reserved_1   : 14; /* bit[18-31]: ���� */
    } reg;
} GBBP_SB_POS_RPT1_UNION;
#define GBBP_SB_POS_RPT1_sb_pos_cpu_START    (0)
#define GBBP_SB_POS_RPT1_sb_pos_cpu_END      (12)
#define GBBP_SB_POS_RPT1_srch_fsm_cpu_START  (16)
#define GBBP_SB_POS_RPT1_srch_fsm_cpu_END    (17)


/*****************************************************************************
 �ṹ��    : GBBP_SB_SQUARE_RPT1_UNION
 �ṹ˵��  : SB_SQUARE_RPT1 �Ĵ����ṹ���塣��ַƫ����:0x1048����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      sb_square_rpt1_reg;
    struct
    {
        unsigned int  sb_square_cpu : 30; /* bit[0-29] : SB��������ֵ�����ֵ�������á� */
        unsigned int  reserved      : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_SB_SQUARE_RPT1_UNION;
#define GBBP_SB_SQUARE_RPT1_sb_square_cpu_START  (0)
#define GBBP_SB_SQUARE_RPT1_sb_square_cpu_END    (29)


/*****************************************************************************
 �ṹ��    : GBBP_SB_POS_RPT2_UNION
 �ṹ˵��  : SB_POS_RPT2 �Ĵ����ṹ���塣��ַƫ����:0x104C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      sb_pos_rpt2_reg;
    struct
    {
        unsigned int  sb_max2_pos_cpu : 13; /* bit[0-12] : SB���������δ�ֵ�����timebase��λ�á� */
        unsigned int  reserved        : 19; /* bit[13-31]: ���� */
    } reg;
} GBBP_SB_POS_RPT2_UNION;
#define GBBP_SB_POS_RPT2_sb_max2_pos_cpu_START  (0)
#define GBBP_SB_POS_RPT2_sb_max2_pos_cpu_END    (12)


/*****************************************************************************
 �ṹ��    : GBBP_SB_SQUARE_RPT2_UNION
 �ṹ˵��  : SB_SQUARE_RPT2 �Ĵ����ṹ���塣��ַƫ����:0x1050����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      sb_square_rpt2_reg;
    struct
    {
        unsigned int  sb_max2_square_cpu : 30; /* bit[0-29] : SB��������ֵ�Ĵδ�ֵ�������á� */
        unsigned int  reserved           : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_SB_SQUARE_RPT2_UNION;
#define GBBP_SB_SQUARE_RPT2_sb_max2_square_cpu_START  (0)
#define GBBP_SB_SQUARE_RPT2_sb_max2_square_cpu_END    (29)


/*****************************************************************************
 �ṹ��    : GBBP_SB_POS_RPT3_UNION
 �ṹ˵��  : SB_POS_RPT3 �Ĵ����ṹ���塣��ַƫ����:0x1054����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      sb_pos_rpt3_reg;
    struct
    {
        unsigned int  sb_max3_pos_cpu : 13; /* bit[0-12] : SB��������������ֵ�����timebase��λ�á� */
        unsigned int  reserved        : 19; /* bit[13-31]: ���� */
    } reg;
} GBBP_SB_POS_RPT3_UNION;
#define GBBP_SB_POS_RPT3_sb_max3_pos_cpu_START  (0)
#define GBBP_SB_POS_RPT3_sb_max3_pos_cpu_END    (12)


/*****************************************************************************
 �ṹ��    : GBBP_SB_SQUARE_RPT3_UNION
 �ṹ˵��  : SB_SQUARE_RPT3 �Ĵ����ṹ���塣��ַƫ����:0x1058����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      sb_square_rpt3_reg;
    struct
    {
        unsigned int  sb_max3_square_cpu : 30; /* bit[0-29] : SB��������ֵ�ĵ�����ֵ�������á� */
        unsigned int  reserved           : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_SB_SQUARE_RPT3_UNION;
#define GBBP_SB_SQUARE_RPT3_sb_max3_square_cpu_START  (0)
#define GBBP_SB_SQUARE_RPT3_sb_max3_square_cpu_END    (29)


/*****************************************************************************
 �ṹ��    : GBBP_STATE_RPT_UNION
 �ṹ˵��  : STATE_RPT �Ĵ����ṹ���塣��ַƫ����:0x105C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      state_rpt_reg;
    struct
    {
        unsigned int  mau_curr_state      : 4;  /* bit[0-3]  : ���ۼ�״̬�ϱ���
                                                               4'd0������״̬��
                                                               4'd1��ͬ������״̬��
                                                               4'd2��NBä��⼰ͬ��λ�ø��£�
                                                               4'd3��Ԥ�˲���
                                                               4'd4��TVB��������
                                                               4'd5��VALPP���С�
                                                               �����á� */
        unsigned int  srch_curr_state     : 2;  /* bit[4-5]  : ���ۼ�ģ����������״̬�ϱ��������á� */
        unsigned int  reserved_0          : 2;  /* bit[6-7]  : ���� */
        unsigned int  int_srch_status_cpu : 4;  /* bit[8-11] : �����ж�״̬������Ӧ�����жϵ�ԭ�򡣴��źŵ�int_srch_sync_cpu��Ч����Ч�������á���bit�������£�
                                                               C01�������̰汾��
                                                               4'd0����������������
                                                               4'd1��FBδͬ����
                                                               4'd2��AFCδ������
                                                               4'd3��SB�������
                                                               4'd5�����������ģʽ���ã���3'b000��
                                                               4'd6����������������������ʹ���ź�gsp_srch_en��͡�
                                                               111�����Ż����̰汾��
                                                               4'd1��FBδͬ����
                                                               4'd7��111����ģʽ�Ż��£���FB-AFC�����£�SB����ʧ�ܳ������ޣ���������ʧ�ܣ�
                                                               4'd8��111����ģʽ�Ż��£���FB-AFCδ�����£�FB-AFC���������������ޣ���������ʧ�ܣ�
                                                               4'd9��111����ģʽ�Ż��£����SB����ɹ���BSICֵ��ͬ��SB����ɹ������������ޣ���������ʧ�ܣ�
                                                               �����á� */
        unsigned int  reserved_1          : 4;  /* bit[12-15]: ���� */
        unsigned int  srch_status_cpu     : 3;  /* bit[16-18]:  */
        unsigned int  reserved_2          : 13; /* bit[19-31]: ���� */
    } reg;
} GBBP_STATE_RPT_UNION;
#define GBBP_STATE_RPT_mau_curr_state_START       (0)
#define GBBP_STATE_RPT_mau_curr_state_END         (3)
#define GBBP_STATE_RPT_srch_curr_state_START      (4)
#define GBBP_STATE_RPT_srch_curr_state_END        (5)
#define GBBP_STATE_RPT_int_srch_status_cpu_START  (8)
#define GBBP_STATE_RPT_int_srch_status_cpu_END    (11)
#define GBBP_STATE_RPT_srch_status_cpu_START      (16)
#define GBBP_STATE_RPT_srch_status_cpu_END        (18)


/*****************************************************************************
 �ṹ��    : GBBP_SRCH_QB_RPT_UNION
 �ṹ˵��  : SRCH_QB_RPT �Ĵ����ṹ���塣��ַƫ����:0x1064����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      srch_qb_rpt_reg;
    struct
    {
        unsigned int  srch_timebase_qb    : 13; /* bit[0-12] : �����ж�����gtc_timebase�ϱ��� */
        unsigned int  reserved_0          : 3;  /* bit[13-15]: ���� */
        unsigned int  srch_int_mod        : 3;  /* bit[16-18]: �����ж�ʱ��gsp_srch_mod�ϱ��� */
        unsigned int  reserved_1          : 9;  /* bit[19-27]: ���� */
        unsigned int  srch_start_mod      : 3;  /* bit[28-30]: ��������ʱ��gsp_srch_mod�ϱ��� */
        unsigned int  gsp_ncell_srch_flag : 1;  /* bit[31]   : ��ǰ����С�������ϱ���
                                                               0����ʾ����С����
                                                               1����ʾ������ */
    } reg;
} GBBP_SRCH_QB_RPT_UNION;
#define GBBP_SRCH_QB_RPT_srch_timebase_qb_START     (0)
#define GBBP_SRCH_QB_RPT_srch_timebase_qb_END       (12)
#define GBBP_SRCH_QB_RPT_srch_int_mod_START         (16)
#define GBBP_SRCH_QB_RPT_srch_int_mod_END           (18)
#define GBBP_SRCH_QB_RPT_srch_start_mod_START       (28)
#define GBBP_SRCH_QB_RPT_srch_start_mod_END         (30)
#define GBBP_SRCH_QB_RPT_gsp_ncell_srch_flag_START  (31)
#define GBBP_SRCH_QB_RPT_gsp_ncell_srch_flag_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_SRCH_FN_RPT_UNION
 �ṹ˵��  : SRCH_FN_RPT �Ĵ����ṹ���塣��ַƫ����:0x106C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      srch_fn_rpt_reg;
    struct
    {
        unsigned int  srch_fn_low  : 11; /* bit[0-10] : �����ж�����λ�õ�gtc_fn_low�ϱ��� */
        unsigned int  reserved_0   : 5;  /* bit[11-15]: ���� */
        unsigned int  srch_fn_high : 11; /* bit[16-26]: �����ж�����λ�õ�gtc_fn_high�ϱ��� */
        unsigned int  reserved_1   : 5;  /* bit[27-31]: ���� */
    } reg;
} GBBP_SRCH_FN_RPT_UNION;
#define GBBP_SRCH_FN_RPT_srch_fn_low_START   (0)
#define GBBP_SRCH_FN_RPT_srch_fn_low_END     (10)
#define GBBP_SRCH_FN_RPT_srch_fn_high_START  (16)
#define GBBP_SRCH_FN_RPT_srch_fn_high_END    (26)


/*****************************************************************************
 �ṹ��    : GBBP_SB_ADVANCE_LEN_CFG_UNION
 �ṹ˵��  : SB_ADVANCE_LEN_CFG �Ĵ����ṹ���塣��ַƫ����:0x1070����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      sb_advance_len_cfg_reg;
    struct
    {
        unsigned int  cpu_sb_advance_len : 6;  /* bit[0-5] : 001����ģʽ�£�SB��ǰ���շ��ŵĸ���������SB֮ǰ�����cpu_sb_advance_len�����ţ�����0~34�� */
        unsigned int  reserved           : 26; /* bit[6-31]: ���� */
    } reg;
} GBBP_SB_ADVANCE_LEN_CFG_UNION;
#define GBBP_SB_ADVANCE_LEN_CFG_cpu_sb_advance_len_START  (0)
#define GBBP_SB_ADVANCE_LEN_CFG_cpu_sb_advance_len_END    (5)


/*****************************************************************************
 �ṹ��    : GBBP_SRCH_FRQ_RPT_UNION
 �ṹ˵��  : SRCH_FRQ_RPT �Ĵ����ṹ���塣��ַƫ����:0x107C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      srch_frq_rpt_reg;
    struct
    {
        unsigned int  srch_start_frq : 12; /* bit[0-11] : ��������ʱ��Ƶ����Ϣ�ϱ��� */
        unsigned int  reserved_0     : 4;  /* bit[12-15]: ���� */
        unsigned int  srch_int_frq   : 12; /* bit[16-27]: �����ж�ʱ��Ƶ����Ϣ�ϱ��� */
        unsigned int  reserved_1     : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_SRCH_FRQ_RPT_UNION;
#define GBBP_SRCH_FRQ_RPT_srch_start_frq_START  (0)
#define GBBP_SRCH_FRQ_RPT_srch_start_frq_END    (11)
#define GBBP_SRCH_FRQ_RPT_srch_int_frq_START    (16)
#define GBBP_SRCH_FRQ_RPT_srch_int_frq_END      (27)


/*****************************************************************************
 �ṹ��    : GBBP_AFC_LOOP1_RPT_UNION
 �ṹ˵��  : AFC_LOOP1_RPT �Ĵ����ṹ���塣��ַƫ����:0x1078����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      afc_loop1_rpt_reg;
    struct
    {
        unsigned int  nbafc_1loop_cpu   : 31; /* bit[0-30]: һ�׻���ǰNB-AFC��·�˲��ۼ������ϱ�ֵ */
        unsigned int  gsp_nb_afc_switch : 1;  /* bit[31]  : NB-AFCһ�׻�����׻�״̬�ϱ���
                                                            0����ʾ��ǰ����һ�׻���
                                                            1����ʾ��ǰ���ڶ��׻��� */
    } reg;
} GBBP_AFC_LOOP1_RPT_UNION;
#define GBBP_AFC_LOOP1_RPT_nbafc_1loop_cpu_START    (0)
#define GBBP_AFC_LOOP1_RPT_nbafc_1loop_cpu_END      (30)
#define GBBP_AFC_LOOP1_RPT_gsp_nb_afc_switch_START  (31)
#define GBBP_AFC_LOOP1_RPT_gsp_nb_afc_switch_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_AFC_LOOP1_CFG_UNION
 �ṹ˵��  : CPU_AFC_LOOP1_CFG �Ĵ����ṹ���塣��ַƫ����:0x1080����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_afc_loop1_cfg_reg;
    struct
    {
        unsigned int  cpu_nbafc_1loop : 31; /* bit[0-30]: �ϵ��һ�׻�NB-AFC��·�˲��ۼ���������ֵ��
                                                          ������cpu_afc_init_enΪ1����Ч�� */
        unsigned int  reserved        : 1;  /* bit[31]  : ���� */
    } reg;
} GBBP_CPU_AFC_LOOP1_CFG_UNION;
#define GBBP_CPU_AFC_LOOP1_CFG_cpu_nbafc_1loop_START  (0)
#define GBBP_CPU_AFC_LOOP1_CFG_cpu_nbafc_1loop_END    (30)


/*****************************************************************************
 �ṹ��    : GBBP_NCELL_NCO_RPT_UNION
 �ṹ˵��  : NCELL_NCO_RPT �Ĵ����ṹ���塣��ַƫ����:0x1084����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      ncell_nco_rpt_reg;
    struct
    {
        unsigned int  ncell_nco_cpu    : 16; /* bit[0-15] : ����Ƶƫ������ϱ��� */
        unsigned int  ncell_nco_status : 2;  /* bit[16-17]: ����Ƶƫ״̬�ϱ��� */
        unsigned int  reserved         : 14; /* bit[18-31]: ���� */
    } reg;
} GBBP_NCELL_NCO_RPT_UNION;
#define GBBP_NCELL_NCO_RPT_ncell_nco_cpu_START     (0)
#define GBBP_NCELL_NCO_RPT_ncell_nco_cpu_END       (15)
#define GBBP_NCELL_NCO_RPT_ncell_nco_status_START  (16)
#define GBBP_NCELL_NCO_RPT_ncell_nco_status_END    (17)


/*****************************************************************************
 �ṹ��    : GBBP_AFC_PHASE_THRESHOLD_CFG_UNION
 �ṹ˵��  : AFC_PHASE_THRESHOLD_CFG �Ĵ����ṹ���塣��ַƫ����:0x108C����ֵ:0x02F8012C�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      afc_phase_threshold_cfg_reg;
    struct
    {
        unsigned int  cpu_afc_phase_min : 10; /* bit[0-9]  : NB-AFC�㷨��λ����ֵ�ο����ޣ�����ֵ300�� */
        unsigned int  reserved_0        : 6;  /* bit[10-15]: ���� */
        unsigned int  cpu_afc_phase_max : 10; /* bit[16-25]: NB-AFC�㷨��λ����ֵ�ο����ޣ�����ֵ760�� */
        unsigned int  reserved_1        : 6;  /* bit[26-31]: ���� */
    } reg;
} GBBP_AFC_PHASE_THRESHOLD_CFG_UNION;
#define GBBP_AFC_PHASE_THRESHOLD_CFG_cpu_afc_phase_min_START  (0)
#define GBBP_AFC_PHASE_THRESHOLD_CFG_cpu_afc_phase_min_END    (9)
#define GBBP_AFC_PHASE_THRESHOLD_CFG_cpu_afc_phase_max_START  (16)
#define GBBP_AFC_PHASE_THRESHOLD_CFG_cpu_afc_phase_max_END    (25)


/*****************************************************************************
 �ṹ��    : GBBP_AFC_FCUT_THRESHOLD_CFG_UNION
 �ṹ˵��  : AFC_FCUT_THRESHOLD_CFG �Ĵ����ṹ���塣��ַƫ����:0x1090����ֵ:0x04000033�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      afc_fcut_threshold_cfg_reg;
    struct
    {
        unsigned int  cpu_afc_fc_low  : 13; /* bit[0-12] : NB-AFC�㷨ϵ��fcut����Сֵ������������˲������λ����ֵС����λ����ֵ�ο����ޣ���ϵ��fcut��ֵ�͵��ڴ���Сֵ������ֵ51�� */
        unsigned int  reserved_0      : 3;  /* bit[13-15]: ���� */
        unsigned int  cpu_afc_fc_high : 13; /* bit[16-28]: NB-AFC�㷨ϵ��fcut�����ֵ������������˲������λ����ֵ������λ����ֵ�Ĳο����ޣ���ϵ��fcut��ֵ�͵��ڴ����ֵ������ֵ1024�� */
        unsigned int  reserved_1      : 3;  /* bit[29-31]: ���� */
    } reg;
} GBBP_AFC_FCUT_THRESHOLD_CFG_UNION;
#define GBBP_AFC_FCUT_THRESHOLD_CFG_cpu_afc_fc_low_START   (0)
#define GBBP_AFC_FCUT_THRESHOLD_CFG_cpu_afc_fc_low_END     (12)
#define GBBP_AFC_FCUT_THRESHOLD_CFG_cpu_afc_fc_high_START  (16)
#define GBBP_AFC_FCUT_THRESHOLD_CFG_cpu_afc_fc_high_END    (28)


/*****************************************************************************
 �ṹ��    : GBBP_AFC_ALPHA_SEL_UNION
 �ṹ˵��  : AFC_ALPHA_SEL �Ĵ����ṹ���塣��ַƫ����:0x1094����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      afc_alpha_sel_reg;
    struct
    {
        unsigned int  cpu_numerator_sel : 2;  /* bit[0-1] : NB-AFC�㷨���˲�ϵ��ѡ��
                                                            0��1/64��
                                                            1��1/32��
                                                            2��1/16��
                                                            3��1/8�� */
        unsigned int  reserved          : 30; /* bit[2-31]: ���� */
    } reg;
} GBBP_AFC_ALPHA_SEL_UNION;
#define GBBP_AFC_ALPHA_SEL_cpu_numerator_sel_START  (0)
#define GBBP_AFC_ALPHA_SEL_cpu_numerator_sel_END    (1)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_SRCH_EN_CLR_UNION
 �ṹ˵��  : CPU_SRCH_EN_CLR �Ĵ����ṹ���塣��ַƫ����:0x1124����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_srch_en_clr_reg;
    struct
    {
        unsigned int  cpu_srch_en_clr_imi          : 1;  /* bit[0]    : д1��ʾ����gsp_srch_en�����źţ��߼������㡣 */
        unsigned int  cpu_nb_demod_en_clr_imi      : 1;  /* bit[1]    : д1��ʾ����gsp_nb_demod_en�����źţ��߼������㡣 */
        unsigned int  cpu_agc_en_clr_imi           : 1;  /* bit[2]    : д1��ʾ����gsp_agc_en�����źţ��߼������㡣 */
        unsigned int  cpu_nb_afc_en_clr_imi        : 1;  /* bit[3]    : д1��ʾ����gsp_nb_afc_en�����źţ��߼������㡣 */
        unsigned int  cpu_alpha_toa_energy_clr_imi : 1;  /* bit[4]    : д1��ʾ����TOA ALPHA�����ۼ�ֵ�������źţ��߼������㡣 */
        unsigned int  reserved_0                   : 11; /* bit[5-15] : ���� */
        unsigned int  gsp_srch_en                  : 1;  /* bit[16]   : ����ʹ��״̬�ϱ��� */
        unsigned int  gsp_nb_demod_en              : 1;  /* bit[17]   : NB���ʹ��״̬�ϱ��� */
        unsigned int  reserved_1                   : 14; /* bit[18-31]: ���� */
    } reg;
} GBBP_CPU_SRCH_EN_CLR_UNION;
#define GBBP_CPU_SRCH_EN_CLR_cpu_srch_en_clr_imi_START           (0)
#define GBBP_CPU_SRCH_EN_CLR_cpu_srch_en_clr_imi_END             (0)
#define GBBP_CPU_SRCH_EN_CLR_cpu_nb_demod_en_clr_imi_START       (1)
#define GBBP_CPU_SRCH_EN_CLR_cpu_nb_demod_en_clr_imi_END         (1)
#define GBBP_CPU_SRCH_EN_CLR_cpu_agc_en_clr_imi_START            (2)
#define GBBP_CPU_SRCH_EN_CLR_cpu_agc_en_clr_imi_END              (2)
#define GBBP_CPU_SRCH_EN_CLR_cpu_nb_afc_en_clr_imi_START         (3)
#define GBBP_CPU_SRCH_EN_CLR_cpu_nb_afc_en_clr_imi_END           (3)
#define GBBP_CPU_SRCH_EN_CLR_cpu_alpha_toa_energy_clr_imi_START  (4)
#define GBBP_CPU_SRCH_EN_CLR_cpu_alpha_toa_energy_clr_imi_END    (4)
#define GBBP_CPU_SRCH_EN_CLR_gsp_srch_en_START                   (16)
#define GBBP_CPU_SRCH_EN_CLR_gsp_srch_en_END                     (16)
#define GBBP_CPU_SRCH_EN_CLR_gsp_nb_demod_en_START               (17)
#define GBBP_CPU_SRCH_EN_CLR_gsp_nb_demod_en_END                 (17)


/*****************************************************************************
 �ṹ��    : GBBP_NB_POS_RPT_UNION
 �ṹ˵��  : NB_POS_RPT �Ĵ����ṹ���塣��ַƫ����:0x1060����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      nb_pos_rpt_reg;
    struct
    {
        unsigned int  nb_pos_cpu         : 13; /* bit[0-12] : NBλ�ø����ϱ����Ƕ�ȡʱ�����һ�����BURST��λ�ã��������timebase��CPU������֡�ж��ж�ȡ������2QB�� */
        unsigned int  reserved_0         : 3;  /* bit[13-15]: ���� */
        unsigned int  mod_type_cpu       : 2;  /* bit[16-17]: NB���Ʒ�ʽ�ϱ���
                                                              0��GMSK���ƣ�
                                                              1��8PSK���ƣ�
                                                              2��DummyBurst�� */
        unsigned int  reserved_1         : 6;  /* bit[18-23]: ���� */
        unsigned int  mod_type_first_cpu : 2;  /* bit[24-25]: NB���Ʒ�ʽ��һ���о�����ϱ��� */
        unsigned int  reserved_2         : 6;  /* bit[26-31]: ���� */
    } reg;
} GBBP_NB_POS_RPT_UNION;
#define GBBP_NB_POS_RPT_nb_pos_cpu_START          (0)
#define GBBP_NB_POS_RPT_nb_pos_cpu_END            (12)
#define GBBP_NB_POS_RPT_mod_type_cpu_START        (16)
#define GBBP_NB_POS_RPT_mod_type_cpu_END          (17)
#define GBBP_NB_POS_RPT_mod_type_first_cpu_START  (24)
#define GBBP_NB_POS_RPT_mod_type_first_cpu_END    (25)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_8PSK_PSP_ALPHA_PARA_UNION
 �ṹ˵��  : CPU_8PSK_PSP_ALPHA_PARA �Ĵ����ṹ���塣��ַƫ����:0x1068����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_8psk_psp_alpha_para_reg;
    struct
    {
        unsigned int  cpu_8psk_psp_alpha_para : 2;  /* bit[0-1] : 8psk����������PSP_EN�Ĳ���alpha��
                                                                  0����Ӧ��ֵΪ8��
                                                                  1����Ӧ��ֵΪ16��
                                                                  2����Ӧ��ֵΪ24��
                                                                  3����Ч��
                                                                  Ĭ��ֵΪ1�� */
        unsigned int  reserved                : 29; /* bit[2-30]: ���� */
        unsigned int  cpu_opt_en              : 1;  /* bit[31]  : 1��ʾ���ŵ������Ż����á� */
    } reg;
} GBBP_CPU_8PSK_PSP_ALPHA_PARA_UNION;
#define GBBP_CPU_8PSK_PSP_ALPHA_PARA_cpu_8psk_psp_alpha_para_START  (0)
#define GBBP_CPU_8PSK_PSP_ALPHA_PARA_cpu_8psk_psp_alpha_para_END    (1)
#define GBBP_CPU_8PSK_PSP_ALPHA_PARA_cpu_opt_en_START               (31)
#define GBBP_CPU_8PSK_PSP_ALPHA_PARA_cpu_opt_en_END                 (31)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_TOA_ALPHA_PARA_UNION
 �ṹ˵��  : CPU_TOA_ALPHA_PARA �Ĵ����ṹ���塣��ַƫ����:0x1074����ֵ:0x00000004�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_toa_alpha_para_reg;
    struct
    {
        unsigned int  cpu_alpha_parameter : 3;  /* bit[0-2] : alpha�˲�ϵ��ѡ��
                                                              0����ʾѡ��ϵ��Ϊ1/2��
                                                              1����ʾѡ��ϵ��Ϊ1/4��
                                                              2����ʾѡ��ϵ��Ϊ1/8��
                                                              3����ʾѡ��ϵ��Ϊ1/16��
                                                              4����ʾѡ��ϵ��Ϊ1/32�� */
        unsigned int  reserved            : 29; /* bit[3-31]: ���� */
    } reg;
} GBBP_CPU_TOA_ALPHA_PARA_UNION;
#define GBBP_CPU_TOA_ALPHA_PARA_cpu_alpha_parameter_START  (0)
#define GBBP_CPU_TOA_ALPHA_PARA_cpu_alpha_parameter_END    (2)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_CH_EST_OPT_UNION
 �ṹ˵��  : CPU_CH_EST_OPT �Ĵ����ṹ���塣��ַƫ����:0x1088����ֵ:0x00050042�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_ch_est_opt_reg;
    struct
    {
        unsigned int  cpu_ch_est_opt_noise_alpha : 3;  /* bit[0-2]  : �ŵ������Ż�����ϵ�����ӣ�ȡֵ1~5��Ĭ������2�� */
        unsigned int  reserved_0                 : 3;  /* bit[3-5]  : ���� */
        unsigned int  cpu_valpp_opt_en           : 1;  /* bit[6]    : valpp����PSP����ʹ���źţ�1��Ч�� */
        unsigned int  cpu_ch_est_opt_bypass      : 1;  /* bit[7]    : 1��ʾ��·�ŵ������Ż����ܣ�
                                                                      0��ʾ���ŵ������Ż����ܡ� */
        unsigned int  reserved_1                 : 8;  /* bit[8-15] : ���� */
        unsigned int  cpu_white_filter_thres     : 3;  /* bit[16-18]: �׻��˲��о����ޣ����������������ı������������ޣ��������׻��˲�������NB�����÷�Χʱ1~7����ʾ1~7��������SB���̶�����Ϊ5����ʾ5���� */
        unsigned int  reserved_2                 : 13; /* bit[19-31]: ���� */
    } reg;
} GBBP_CPU_CH_EST_OPT_UNION;
#define GBBP_CPU_CH_EST_OPT_cpu_ch_est_opt_noise_alpha_START  (0)
#define GBBP_CPU_CH_EST_OPT_cpu_ch_est_opt_noise_alpha_END    (2)
#define GBBP_CPU_CH_EST_OPT_cpu_valpp_opt_en_START            (6)
#define GBBP_CPU_CH_EST_OPT_cpu_valpp_opt_en_END              (6)
#define GBBP_CPU_CH_EST_OPT_cpu_ch_est_opt_bypass_START       (7)
#define GBBP_CPU_CH_EST_OPT_cpu_ch_est_opt_bypass_END         (7)
#define GBBP_CPU_CH_EST_OPT_cpu_white_filter_thres_START      (16)
#define GBBP_CPU_CH_EST_OPT_cpu_white_filter_thres_END        (18)


/*****************************************************************************
 �ṹ��    : GBBP_NB_MOD_TYPE_RPT_UNION
 �ṹ˵��  : NB_MOD_TYPE_RPT �Ĵ����ṹ���塣��ַƫ����:0x1098����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      nb_mod_type_rpt_reg;
    struct
    {
        unsigned int  slot_demod_flag_cpu : 16; /* bit[0-15] : bit0~bit15��ʾ��ʱ϶�ĵ�һ���ڶ������������ĸ�ʱ϶���ĸ�BURST����ä����־�ϱ���0��ʶGMSK��1��ʶ8PSK�� */
        unsigned int  slot_burst_flag_cpu : 16; /* bit[16-31]: bit16~bit31��ʾ��ʱ϶�ĵ�һ���ڶ������������ĸ�ʱ϶���ĸ�BURST����ä����־�ϱ���0��ʶNB��1��ʶDB�� */
    } reg;
} GBBP_NB_MOD_TYPE_RPT_UNION;
#define GBBP_NB_MOD_TYPE_RPT_slot_demod_flag_cpu_START  (0)
#define GBBP_NB_MOD_TYPE_RPT_slot_demod_flag_cpu_END    (15)
#define GBBP_NB_MOD_TYPE_RPT_slot_burst_flag_cpu_START  (16)
#define GBBP_NB_MOD_TYPE_RPT_slot_burst_flag_cpu_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_NB_BURST_TYPE_RPT_UNION
 �ṹ˵��  : NB_BURST_TYPE_RPT �Ĵ����ṹ���塣��ַƫ����:0x10BC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      nb_burst_type_rpt_reg;
    struct
    {
        unsigned int  slot_demod_flag_high_cpu : 8;  /* bit[0-7]  : bit0~bit7��ʾ��ʱ϶�ĵ��壬����ʱ϶������BURST����ä����־�ϱ���0��ʶGMSK��1��ʶ8PSK�� */
        unsigned int  reserved_0               : 8;  /* bit[8-15] : ���� */
        unsigned int  slot_burst_flag_high_cpu : 8;  /* bit[16-23]: bit16~bit23��ʾ��ʱ϶�ĵ��壬����ʱ϶������BURST���ͱ�־�ϱ���0��ʶNB��1��ʶDB�� */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: ���� */
    } reg;
} GBBP_NB_BURST_TYPE_RPT_UNION;
#define GBBP_NB_BURST_TYPE_RPT_slot_demod_flag_high_cpu_START  (0)
#define GBBP_NB_BURST_TYPE_RPT_slot_demod_flag_high_cpu_END    (7)
#define GBBP_NB_BURST_TYPE_RPT_slot_burst_flag_high_cpu_START  (16)
#define GBBP_NB_BURST_TYPE_RPT_slot_burst_flag_high_cpu_END    (23)


/*****************************************************************************
 �ṹ��    : GBBP_GROSS_CARRIER_ENERGY1_UNION
 �ṹ˵��  : GROSS_CARRIER_ENERGY1 �Ĵ����ṹ���塣��ַƫ����:0x109C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gross_carrier_energy1_reg;
    struct
    {
        unsigned int  thres_c_1d : 19; /* bit[0-18] : ��һ����һ��BURST���ǰ�ֲ�Cֵ�ϱ��������á� */
        unsigned int  reserved   : 13; /* bit[19-31]: ���� */
    } reg;
} GBBP_GROSS_CARRIER_ENERGY1_UNION;
#define GBBP_GROSS_CARRIER_ENERGY1_thres_c_1d_START  (0)
#define GBBP_GROSS_CARRIER_ENERGY1_thres_c_1d_END    (18)


/*****************************************************************************
 �ṹ��    : GBBP_GROSS_INTERFERE_ENERGY1_UNION
 �ṹ˵��  : GROSS_INTERFERE_ENERGY1 �Ĵ����ṹ���塣��ַƫ����:0x10A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gross_interfere_energy1_reg;
    struct
    {
        unsigned int  thres_i_1d : 19; /* bit[0-18] : ��һ����һ��BURST���ǰ�ֲ�Iֵ�ϱ��������á� */
        unsigned int  reserved   : 13; /* bit[19-31]: ���� */
    } reg;
} GBBP_GROSS_INTERFERE_ENERGY1_UNION;
#define GBBP_GROSS_INTERFERE_ENERGY1_thres_i_1d_START  (0)
#define GBBP_GROSS_INTERFERE_ENERGY1_thres_i_1d_END    (18)


/*****************************************************************************
 �ṹ��    : GBBP_GROSS_CARRIER_ENERGY2_UNION
 �ṹ˵��  : GROSS_CARRIER_ENERGY2 �Ĵ����ṹ���塣��ַƫ����:0x10A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gross_carrier_energy2_reg;
    struct
    {
        unsigned int  thres_c_2d : 19; /* bit[0-18] : �ڶ�����һ��BURST���ǰ�ֲ�Cֵ�ϱ��������á� */
        unsigned int  reserved   : 13; /* bit[19-31]: ���� */
    } reg;
} GBBP_GROSS_CARRIER_ENERGY2_UNION;
#define GBBP_GROSS_CARRIER_ENERGY2_thres_c_2d_START  (0)
#define GBBP_GROSS_CARRIER_ENERGY2_thres_c_2d_END    (18)


/*****************************************************************************
 �ṹ��    : GBBP_GROSS_INTERFERE_ENERGY2_UNION
 �ṹ˵��  : GROSS_INTERFERE_ENERGY2 �Ĵ����ṹ���塣��ַƫ����:0x10A8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gross_interfere_energy2_reg;
    struct
    {
        unsigned int  thres_i_2d : 19; /* bit[0-18] : �ڶ�����һ��BURST���ǰ�ֲ�Iֵ�ϱ��������á� */
        unsigned int  reserved   : 13; /* bit[19-31]: ���� */
    } reg;
} GBBP_GROSS_INTERFERE_ENERGY2_UNION;
#define GBBP_GROSS_INTERFERE_ENERGY2_thres_i_2d_START  (0)
#define GBBP_GROSS_INTERFERE_ENERGY2_thres_i_2d_END    (18)


/*****************************************************************************
 �ṹ��    : GBBP_GROSS_CARRIER_ENERGY3_UNION
 �ṹ˵��  : GROSS_CARRIER_ENERGY3 �Ĵ����ṹ���塣��ַƫ����:0x10AC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gross_carrier_energy3_reg;
    struct
    {
        unsigned int  thres_c_3d : 19; /* bit[0-18] : ��������һ��BURST���ǰ�ֲ�Cֵ�ϱ��������á� */
        unsigned int  reserved   : 13; /* bit[19-31]: ���� */
    } reg;
} GBBP_GROSS_CARRIER_ENERGY3_UNION;
#define GBBP_GROSS_CARRIER_ENERGY3_thres_c_3d_START  (0)
#define GBBP_GROSS_CARRIER_ENERGY3_thres_c_3d_END    (18)


/*****************************************************************************
 �ṹ��    : GBBP_GROSS_INTERFERE_ENERGY3_UNION
 �ṹ˵��  : GROSS_INTERFERE_ENERGY3 �Ĵ����ṹ���塣��ַƫ����:0x10B0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gross_interfere_energy3_reg;
    struct
    {
        unsigned int  thres_i_3d : 19; /* bit[0-18] : ��������һ��BURST���ǰ�ֲ�Iֵ�ϱ��������á� */
        unsigned int  reserved   : 13; /* bit[19-31]: ���� */
    } reg;
} GBBP_GROSS_INTERFERE_ENERGY3_UNION;
#define GBBP_GROSS_INTERFERE_ENERGY3_thres_i_3d_START  (0)
#define GBBP_GROSS_INTERFERE_ENERGY3_thres_i_3d_END    (18)


/*****************************************************************************
 �ṹ��    : GBBP_GROSS_CARRIER_ENERGY4_UNION
 �ṹ˵��  : GROSS_CARRIER_ENERGY4 �Ĵ����ṹ���塣��ַƫ����:0x10B4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gross_carrier_energy4_reg;
    struct
    {
        unsigned int  thres_c_4d : 19; /* bit[0-18] : ���Ľ���һ��BURST���ǰ�ֲ�Cֵ�ϱ��������á� */
        unsigned int  reserved   : 13; /* bit[19-31]: ���� */
    } reg;
} GBBP_GROSS_CARRIER_ENERGY4_UNION;
#define GBBP_GROSS_CARRIER_ENERGY4_thres_c_4d_START  (0)
#define GBBP_GROSS_CARRIER_ENERGY4_thres_c_4d_END    (18)


/*****************************************************************************
 �ṹ��    : GBBP_GROSS_INTERFERE_ENERGY4_UNION
 �ṹ˵��  : GROSS_INTERFERE_ENERGY4 �Ĵ����ṹ���塣��ַƫ����:0x10B8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gross_interfere_energy4_reg;
    struct
    {
        unsigned int  thres_i_4d : 19; /* bit[0-18] : ���Ľ���һ��BURST���ǰ�ֲ�Iֵ�ϱ��������á� */
        unsigned int  reserved   : 13; /* bit[19-31]: ���� */
    } reg;
} GBBP_GROSS_INTERFERE_ENERGY4_UNION;
#define GBBP_GROSS_INTERFERE_ENERGY4_thres_i_4d_START  (0)
#define GBBP_GROSS_INTERFERE_ENERGY4_thres_i_4d_END    (18)


/*****************************************************************************
 �ṹ��    : GBBP_VALPP_CARRIER_ENERGY0_UNION
 �ṹ˵��  : VALPP_CARRIER_ENERGY0 �Ĵ����ṹ���塣��ַƫ����:0x1100����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_carrier_energy0_reg;
    struct
    {
        unsigned int  valpp_carrier_energy_cpu : 31; /* bit[0-30]: ��ȡʱ��ǰ���burst��Ӧ���ز�����ֵ���޷������� */
        unsigned int  reserved                 : 1;  /* bit[31]  : ���� */
    } reg;
} GBBP_VALPP_CARRIER_ENERGY0_UNION;
#define GBBP_VALPP_CARRIER_ENERGY0_valpp_carrier_energy_cpu_START  (0)
#define GBBP_VALPP_CARRIER_ENERGY0_valpp_carrier_energy_cpu_END    (30)


/*****************************************************************************
 �ṹ��    : GBBP_VALPP_INTERFERE_ENERGY0_UNION
 �ṹ˵��  : VALPP_INTERFERE_ENERGY0 �Ĵ����ṹ���塣��ַƫ����:0x1150����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_interfere_energy0_reg;
    struct
    {
        unsigned int  valpp_interfere_energy_cpu : 26; /* bit[0-25] : ��ȡʱ��ǰ���burst��Ӧ�ĸ�������ֵ���޷������� */
        unsigned int  reserved                   : 6;  /* bit[26-31]: ���� */
    } reg;
} GBBP_VALPP_INTERFERE_ENERGY0_UNION;
#define GBBP_VALPP_INTERFERE_ENERGY0_valpp_interfere_energy_cpu_START  (0)
#define GBBP_VALPP_INTERFERE_ENERGY0_valpp_interfere_energy_cpu_END    (25)


/*****************************************************************************
 �ṹ��    : GBBP_VALPP_DEM_TYPE_TOA0_UNION
 �ṹ˵��  : VALPP_DEM_TYPE_TOA0 �Ĵ����ṹ���塣��ַƫ����:0x1104����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_dem_type_toa0_reg;
    struct
    {
        unsigned int  toa_sel_result                 : 6;  /* bit[0-5]  : ���6��ʱ϶��TOA����ѡ������
                                                                          bit0�����һ��burst��ѡ������
                                                                          bit1���ڶ���burst��ѡ������
                                                                          �����������ơ�
                                                                          0��ʾѡ��ǰ������ţ�1��ʾѡ��������ţ���Ҫ��nb_pos_adj�Ļ����ϼ���2QB�� */
        unsigned int  reserved_0                     : 2;  /* bit[6-7]  : ���� */
        unsigned int  max_sum_index_cpu              : 4;  /* bit[8-11] : SAIC��TOA�徶Cֵ���ֵ��Ӧ���ţ�
                                                                          ȡֵ��Χ0~4�� */
        unsigned int  reserved_1                     : 2;  /* bit[12-13]: ���� */
        unsigned int  mod_type_1d                    : 2;  /* bit[14-15]: ��ȡʱ�����BURST�ĵ��Ʒ�ʽ��
                                                                          0��GSKM��
                                                                          1��8PSK��
                                                                          2��DummyBurst�� */
        unsigned int  nb_pos_adj_cpu_sav0            : 4;  /* bit[16-19]: ��ȡʱ��������burst��Ӧ��NBλ�õ��������ǲ����ʾ���з�������������ʾ��ǰ������������ʾ����������Χ��-4~+4�� */
        unsigned int  demod_slot_1d                  : 3;  /* bit[20-22]: ��ȡʱ��������burst��Ӧ��ʱ϶�ţ���ʱ϶����PHYͨ��GTCָ������������BBP��ʱ������жϴ������ϱ��� */
        unsigned int  reserved_2                     : 1;  /* bit[23]   : ���� */
        unsigned int  nserv_cell_ind_1d              : 1;  /* bit[24]   : ��ȡʱ�����burst�Ƿ�Ϊ�Ƿ�����ָʾ��1��ʾ�Ƿ�������0��ʾ��������Ĭ��ֵΪ0����ֵ��PHYͨ��GTCָ������������BBP��ʱ������жϴ������ϱ��� */
        unsigned int  reserved_3                     : 3;  /* bit[25-27]: ���� */
        unsigned int  mod_type_first_1d              : 2;  /* bit[28-29]: ��ȡʱ��ǰ�����BURST��Ӧ��һ���о��ĵ��Ʒ�ʽ��
                                                                          0��GMSK���ƣ�
                                                                          1��8PSK���ƣ�
                                                                          2��DummyBurst��
                                                                          �üĴ�������ʹ�á� */
        unsigned int  demod_info_valid_flag0_clr_imi : 1;  /* bit[30]   : ��demod_info_valid_flag0���㡣д1���㡣 */
        unsigned int  demod_info_valid_flag0         : 1;  /* bit[31]   : ��ȡʱ����������Ϣ��Ч��־�������һ��NB���ʱ���ñ�־��1,CPU��ȡ���BURST����ϱ���Ϣ��Ӧ��ͨ��bit30�Ը�bit���㣬ָʾ����Ϣ�Ѿ���ȡ�� */
    } reg;
} GBBP_VALPP_DEM_TYPE_TOA0_UNION;
#define GBBP_VALPP_DEM_TYPE_TOA0_toa_sel_result_START                  (0)
#define GBBP_VALPP_DEM_TYPE_TOA0_toa_sel_result_END                    (5)
#define GBBP_VALPP_DEM_TYPE_TOA0_max_sum_index_cpu_START               (8)
#define GBBP_VALPP_DEM_TYPE_TOA0_max_sum_index_cpu_END                 (11)
#define GBBP_VALPP_DEM_TYPE_TOA0_mod_type_1d_START                     (14)
#define GBBP_VALPP_DEM_TYPE_TOA0_mod_type_1d_END                       (15)
#define GBBP_VALPP_DEM_TYPE_TOA0_nb_pos_adj_cpu_sav0_START             (16)
#define GBBP_VALPP_DEM_TYPE_TOA0_nb_pos_adj_cpu_sav0_END               (19)
#define GBBP_VALPP_DEM_TYPE_TOA0_demod_slot_1d_START                   (20)
#define GBBP_VALPP_DEM_TYPE_TOA0_demod_slot_1d_END                     (22)
#define GBBP_VALPP_DEM_TYPE_TOA0_nserv_cell_ind_1d_START               (24)
#define GBBP_VALPP_DEM_TYPE_TOA0_nserv_cell_ind_1d_END                 (24)
#define GBBP_VALPP_DEM_TYPE_TOA0_mod_type_first_1d_START               (28)
#define GBBP_VALPP_DEM_TYPE_TOA0_mod_type_first_1d_END                 (29)
#define GBBP_VALPP_DEM_TYPE_TOA0_demod_info_valid_flag0_clr_imi_START  (30)
#define GBBP_VALPP_DEM_TYPE_TOA0_demod_info_valid_flag0_clr_imi_END    (30)
#define GBBP_VALPP_DEM_TYPE_TOA0_demod_info_valid_flag0_START          (31)
#define GBBP_VALPP_DEM_TYPE_TOA0_demod_info_valid_flag0_END            (31)


/*****************************************************************************
 �ṹ��    : GBBP_VALPP_CARRIER_ENERGY1_UNION
 �ṹ˵��  : VALPP_CARRIER_ENERGY1 �Ĵ����ṹ���塣��ַƫ����:0x1108����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_carrier_energy1_reg;
    struct
    {
        unsigned int  valpp_carrier_energy_1d_cpu : 31; /* bit[0-30]: ��ȡʱ��ǰ�ڶ���burst��Ӧ���ز�����ֵ���޷������� */
        unsigned int  reserved                    : 1;  /* bit[31]  : ���� */
    } reg;
} GBBP_VALPP_CARRIER_ENERGY1_UNION;
#define GBBP_VALPP_CARRIER_ENERGY1_valpp_carrier_energy_1d_cpu_START  (0)
#define GBBP_VALPP_CARRIER_ENERGY1_valpp_carrier_energy_1d_cpu_END    (30)


/*****************************************************************************
 �ṹ��    : GBBP_VALPP_INTERFERE_ENERGY1_UNION
 �ṹ˵��  : VALPP_INTERFERE_ENERGY1 �Ĵ����ṹ���塣��ַƫ����:0x1154����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_interfere_energy1_reg;
    struct
    {
        unsigned int  valpp_interfere_energy_1d_cpu : 26; /* bit[0-25] : ��ȡʱ��ǰ�ڶ���burst��Ӧ�ĸ�������ֵ���޷������� */
        unsigned int  reserved                      : 6;  /* bit[26-31]: ���� */
    } reg;
} GBBP_VALPP_INTERFERE_ENERGY1_UNION;
#define GBBP_VALPP_INTERFERE_ENERGY1_valpp_interfere_energy_1d_cpu_START  (0)
#define GBBP_VALPP_INTERFERE_ENERGY1_valpp_interfere_energy_1d_cpu_END    (25)


/*****************************************************************************
 �ṹ��    : GBBP_VALPP_DEM_TYPE_TOA1_UNION
 �ṹ˵��  : VALPP_DEM_TYPE_TOA1 �Ĵ����ṹ���塣��ַƫ����:0x110C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_dem_type_toa1_reg;
    struct
    {
        unsigned int  reserved_0                     : 14; /* bit[0-13] : ���� */
        unsigned int  mod_type_2d                    : 2;  /* bit[14-15]: ��ȡʱ�̵ڶ���BURST�ĵ��Ʒ�ʽ��
                                                                          0��GSKM��
                                                                          1��8PSK��
                                                                          2��DummyBurst�� */
        unsigned int  nb_pos_adj_cpu_sav1            : 4;  /* bit[16-19]: ��ȡʱ�̵ڶ������burst��Ӧ��NBλ�õ��������ǲ����ʾ���з�������������ʾ��ǰ������������ʾ����������Χ��-4~+4�� */
        unsigned int  demod_slot_2d                  : 3;  /* bit[20-22]: ��ȡʱ�̵ڶ������burst��Ӧ��ʱ϶�ţ���ʱ϶����PHYͨ��GTCָ������������BBP��ʱ������жϴ������ϱ��� */
        unsigned int  reserved_1                     : 1;  /* bit[23]   : ���� */
        unsigned int  nserv_cell_ind_2d              : 1;  /* bit[24]   : ��ȡʱ�̵ڶ���burst�Ƿ�Ϊ�Ƿ�����ָʾ��1��ʾ�Ƿ�������0��ʾ��������Ĭ��ֵΪ0����ֵ��PHYͨ��GTCָ������������BBP��ʱ������жϴ������ϱ��� */
        unsigned int  reserved_2                     : 3;  /* bit[25-27]: ���� */
        unsigned int  mod_type_first_2d              : 2;  /* bit[28-29]: ��ȡʱ��ǰ�ĵڶ���BURST��Ӧ��һ���о��ĵ��Ʒ�ʽ��
                                                                          0��GMSK���ƣ�
                                                                          1��8PSK���ƣ�
                                                                          2��DummyBurst��
                                                                          �üĴ�������ʹ�á� */
        unsigned int  demod_info_valid_flag1_clr_imi : 1;  /* bit[30]   : ��demod_info_valid_flag1���㡣д1���㡣 */
        unsigned int  demod_info_valid_flag1         : 1;  /* bit[31]   : ��ȡʱ�̵ڶ��������Ϣ��Ч��־�������һ��NB���ʱ���ñ�־��1,CPU��ȡ���BURST����ϱ���Ϣ��Ӧ��ͨ��дbit30�Ը�bit���㣬ָʾ����Ϣ�Ѿ���ȡ�� */
    } reg;
} GBBP_VALPP_DEM_TYPE_TOA1_UNION;
#define GBBP_VALPP_DEM_TYPE_TOA1_mod_type_2d_START                     (14)
#define GBBP_VALPP_DEM_TYPE_TOA1_mod_type_2d_END                       (15)
#define GBBP_VALPP_DEM_TYPE_TOA1_nb_pos_adj_cpu_sav1_START             (16)
#define GBBP_VALPP_DEM_TYPE_TOA1_nb_pos_adj_cpu_sav1_END               (19)
#define GBBP_VALPP_DEM_TYPE_TOA1_demod_slot_2d_START                   (20)
#define GBBP_VALPP_DEM_TYPE_TOA1_demod_slot_2d_END                     (22)
#define GBBP_VALPP_DEM_TYPE_TOA1_nserv_cell_ind_2d_START               (24)
#define GBBP_VALPP_DEM_TYPE_TOA1_nserv_cell_ind_2d_END                 (24)
#define GBBP_VALPP_DEM_TYPE_TOA1_mod_type_first_2d_START               (28)
#define GBBP_VALPP_DEM_TYPE_TOA1_mod_type_first_2d_END                 (29)
#define GBBP_VALPP_DEM_TYPE_TOA1_demod_info_valid_flag1_clr_imi_START  (30)
#define GBBP_VALPP_DEM_TYPE_TOA1_demod_info_valid_flag1_clr_imi_END    (30)
#define GBBP_VALPP_DEM_TYPE_TOA1_demod_info_valid_flag1_START          (31)
#define GBBP_VALPP_DEM_TYPE_TOA1_demod_info_valid_flag1_END            (31)


/*****************************************************************************
 �ṹ��    : GBBP_VALPP_CARRIER_ENERGY2_UNION
 �ṹ˵��  : VALPP_CARRIER_ENERGY2 �Ĵ����ṹ���塣��ַƫ����:0x1110����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_carrier_energy2_reg;
    struct
    {
        unsigned int  valpp_carrier_energy_2d_cpu : 31; /* bit[0-30]: ��ȡʱ��ǰ������burst��Ӧ���ز�����ֵ���޷������� */
        unsigned int  reserved                    : 1;  /* bit[31]  : ���� */
    } reg;
} GBBP_VALPP_CARRIER_ENERGY2_UNION;
#define GBBP_VALPP_CARRIER_ENERGY2_valpp_carrier_energy_2d_cpu_START  (0)
#define GBBP_VALPP_CARRIER_ENERGY2_valpp_carrier_energy_2d_cpu_END    (30)


/*****************************************************************************
 �ṹ��    : GBBP_VALPP_INTERFERE_ENERGY2_UNION
 �ṹ˵��  : VALPP_INTERFERE_ENERGY2 �Ĵ����ṹ���塣��ַƫ����:0x1158����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_interfere_energy2_reg;
    struct
    {
        unsigned int  valpp_interfere_energy_2d_cpu : 26; /* bit[0-25] : ��ȡʱ��ǰ������burst��Ӧ�ĸ�������ֵ���޷������� */
        unsigned int  reserved                      : 6;  /* bit[26-31]: ���� */
    } reg;
} GBBP_VALPP_INTERFERE_ENERGY2_UNION;
#define GBBP_VALPP_INTERFERE_ENERGY2_valpp_interfere_energy_2d_cpu_START  (0)
#define GBBP_VALPP_INTERFERE_ENERGY2_valpp_interfere_energy_2d_cpu_END    (25)


/*****************************************************************************
 �ṹ��    : GBBP_VALPP_DEM_TYPE_TOA2_UNION
 �ṹ˵��  : VALPP_DEM_TYPE_TOA2 �Ĵ����ṹ���塣��ַƫ����:0x1114����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_dem_type_toa2_reg;
    struct
    {
        unsigned int  reserved_0                     : 14; /* bit[0-13] : ���� */
        unsigned int  mod_type_3d                    : 2;  /* bit[14-15]: ��ȡʱ�̵�����BURST�ĵ��Ʒ�ʽ��
                                                                          0��GSKM��
                                                                          1��8PSK��
                                                                          2��DummyBurst�� */
        unsigned int  nb_pos_adj_cpu_sav2            : 4;  /* bit[16-19]: ��ȡʱ�̵��������burst��Ӧ��NBλ�õ��������ǲ����ʾ���з�������������ʾ��ǰ������������ʾ����������Χ��-4~+4�� */
        unsigned int  demod_slot_3d                  : 3;  /* bit[20-22]: ��ȡʱ�̵��������burst��Ӧ��ʱ϶�ţ���ʱ϶����PHYͨ��GTCָ������������BBP��ʱ������жϴ������ϱ��� */
        unsigned int  reserved_1                     : 1;  /* bit[23]   : ���� */
        unsigned int  nserv_cell_ind_3d              : 1;  /* bit[24]   : ��ȡʱ�̵�����burst�Ƿ�Ϊ�Ƿ�����ָʾ��1��ʾ�Ƿ�������0��ʾ��������Ĭ��ֵΪ0����ֵ��PHYͨ��GTCָ������������BBP��ʱ������жϴ������ϱ��� */
        unsigned int  reserved_2                     : 3;  /* bit[25-27]: ���� */
        unsigned int  mod_type_first_3d              : 2;  /* bit[28-29]: ��ȡʱ��ǰ�ĵ�����BURST��Ӧ��һ���о��ĵ��Ʒ�ʽ��
                                                                          0��GMSK���ƣ�
                                                                          1��8PSK���ƣ�
                                                                          2��DummyBurst��
                                                                          �üĴ�������ʹ�á� */
        unsigned int  demod_info_valid_flag2_clr_imi : 1;  /* bit[30]   : ��demod_info_valid_flag2���㡣д1���㡣 */
        unsigned int  demod_info_valid_flag2         : 1;  /* bit[31]   : ��ȡʱ�̵����������Ϣ��Ч��־�������һ��NB���ʱ���ñ�־��1,CPU��ȡ���BURST����ϱ���Ϣ��Ӧ��ͨ��дbit30�Ը�bit���㣬ָʾ����Ϣ�Ѿ���ȡ�� */
    } reg;
} GBBP_VALPP_DEM_TYPE_TOA2_UNION;
#define GBBP_VALPP_DEM_TYPE_TOA2_mod_type_3d_START                     (14)
#define GBBP_VALPP_DEM_TYPE_TOA2_mod_type_3d_END                       (15)
#define GBBP_VALPP_DEM_TYPE_TOA2_nb_pos_adj_cpu_sav2_START             (16)
#define GBBP_VALPP_DEM_TYPE_TOA2_nb_pos_adj_cpu_sav2_END               (19)
#define GBBP_VALPP_DEM_TYPE_TOA2_demod_slot_3d_START                   (20)
#define GBBP_VALPP_DEM_TYPE_TOA2_demod_slot_3d_END                     (22)
#define GBBP_VALPP_DEM_TYPE_TOA2_nserv_cell_ind_3d_START               (24)
#define GBBP_VALPP_DEM_TYPE_TOA2_nserv_cell_ind_3d_END                 (24)
#define GBBP_VALPP_DEM_TYPE_TOA2_mod_type_first_3d_START               (28)
#define GBBP_VALPP_DEM_TYPE_TOA2_mod_type_first_3d_END                 (29)
#define GBBP_VALPP_DEM_TYPE_TOA2_demod_info_valid_flag2_clr_imi_START  (30)
#define GBBP_VALPP_DEM_TYPE_TOA2_demod_info_valid_flag2_clr_imi_END    (30)
#define GBBP_VALPP_DEM_TYPE_TOA2_demod_info_valid_flag2_START          (31)
#define GBBP_VALPP_DEM_TYPE_TOA2_demod_info_valid_flag2_END            (31)


/*****************************************************************************
 �ṹ��    : GBBP_VALPP_CARRIER_ENERGY3_UNION
 �ṹ˵��  : VALPP_CARRIER_ENERGY3 �Ĵ����ṹ���塣��ַƫ����:0x1118����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_carrier_energy3_reg;
    struct
    {
        unsigned int  valpp_carrier_energy_3d_cpu : 31; /* bit[0-30]: ��ȡʱ��ǰ���Ľ�burst��Ӧ���ز�����ֵ���޷������� */
        unsigned int  reserved                    : 1;  /* bit[31]  : ���� */
    } reg;
} GBBP_VALPP_CARRIER_ENERGY3_UNION;
#define GBBP_VALPP_CARRIER_ENERGY3_valpp_carrier_energy_3d_cpu_START  (0)
#define GBBP_VALPP_CARRIER_ENERGY3_valpp_carrier_energy_3d_cpu_END    (30)


/*****************************************************************************
 �ṹ��    : GBBP_VALPP_INTERFERE_ENERGY3_UNION
 �ṹ˵��  : VALPP_INTERFERE_ENERGY3 �Ĵ����ṹ���塣��ַƫ����:0x115C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_interfere_energy3_reg;
    struct
    {
        unsigned int  valpp_interfere_energy_3d_cpu : 26; /* bit[0-25] : ��ȡʱ��ǰ���Ľ�burst��Ӧ�ĸ�������ֵ���޷������� */
        unsigned int  reserved                      : 6;  /* bit[26-31]: ���� */
    } reg;
} GBBP_VALPP_INTERFERE_ENERGY3_UNION;
#define GBBP_VALPP_INTERFERE_ENERGY3_valpp_interfere_energy_3d_cpu_START  (0)
#define GBBP_VALPP_INTERFERE_ENERGY3_valpp_interfere_energy_3d_cpu_END    (25)


/*****************************************************************************
 �ṹ��    : GBBP_VALPP_DEM_TYPE_TOA3_UNION
 �ṹ˵��  : VALPP_DEM_TYPE_TOA3 �Ĵ����ṹ���塣��ַƫ����:0x111C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_dem_type_toa3_reg;
    struct
    {
        unsigned int  reserved_0                     : 14; /* bit[0-13] : ���� */
        unsigned int  mod_type_4d                    : 2;  /* bit[14-15]: ��ȡʱ�̵��Ľ�BURST�ĵ��Ʒ�ʽ��
                                                                          0��GSKM��
                                                                          1��8PSK��
                                                                          2��DummyBurst�� */
        unsigned int  nb_pos_adj_cpu_sav3            : 4;  /* bit[16-19]: ��ȡʱ�̵��Ľ����burst��Ӧ��NBλ�õ��������ǲ����ʾ���з�������������ʾ��ǰ������������ʾ����������Χ��-4~+4�� */
        unsigned int  demod_slot_4d                  : 3;  /* bit[20-22]: ��ȡʱ�̵��Ľ����burst��Ӧ��ʱ϶�ţ���ʱ϶����PHYͨ��GTCָ������������BBP��ʱ������жϴ������ϱ��� */
        unsigned int  reserved_1                     : 1;  /* bit[23]   : ���� */
        unsigned int  nserv_cell_ind_4d              : 1;  /* bit[24]   : ��ȡʱ�̵��Ľ�burst�Ƿ�Ϊ�Ƿ�����ָʾ��1��ʾ�Ƿ�������0��ʾ��������Ĭ��ֵΪ0����ֵ��PHYͨ��GTCָ������������BBP��ʱ������жϴ������ϱ��� */
        unsigned int  reserved_2                     : 3;  /* bit[25-27]: ���� */
        unsigned int  mod_type_first_4d              : 2;  /* bit[28-29]: ��ȡʱ��ǰ�ĵ��Ľ�BURST��Ӧ��һ���о��ĵ��Ʒ�ʽ��
                                                                          0��GMSK���ƣ�
                                                                          1��8PSK���ƣ�
                                                                          2��DummyBurst��
                                                                          �üĴ�������ʹ�á� */
        unsigned int  demod_info_valid_flag3_clr_imi : 1;  /* bit[30]   : ��demod_info_valid_flag3���㡣д1���㡣 */
        unsigned int  demod_info_valid_flag3         : 1;  /* bit[31]   : ��ȡʱ�̵��Ľ������Ϣ��Ч��־�������һ��NB���ʱ���ñ�־��1,CPU��ȡ���BURST����ϱ���Ϣ��Ӧ��дbit30�Ը�bit���㣬ָʾ����Ϣ�Ѿ���ȡ�� */
    } reg;
} GBBP_VALPP_DEM_TYPE_TOA3_UNION;
#define GBBP_VALPP_DEM_TYPE_TOA3_mod_type_4d_START                     (14)
#define GBBP_VALPP_DEM_TYPE_TOA3_mod_type_4d_END                       (15)
#define GBBP_VALPP_DEM_TYPE_TOA3_nb_pos_adj_cpu_sav3_START             (16)
#define GBBP_VALPP_DEM_TYPE_TOA3_nb_pos_adj_cpu_sav3_END               (19)
#define GBBP_VALPP_DEM_TYPE_TOA3_demod_slot_4d_START                   (20)
#define GBBP_VALPP_DEM_TYPE_TOA3_demod_slot_4d_END                     (22)
#define GBBP_VALPP_DEM_TYPE_TOA3_nserv_cell_ind_4d_START               (24)
#define GBBP_VALPP_DEM_TYPE_TOA3_nserv_cell_ind_4d_END                 (24)
#define GBBP_VALPP_DEM_TYPE_TOA3_mod_type_first_4d_START               (28)
#define GBBP_VALPP_DEM_TYPE_TOA3_mod_type_first_4d_END                 (29)
#define GBBP_VALPP_DEM_TYPE_TOA3_demod_info_valid_flag3_clr_imi_START  (30)
#define GBBP_VALPP_DEM_TYPE_TOA3_demod_info_valid_flag3_clr_imi_END    (30)
#define GBBP_VALPP_DEM_TYPE_TOA3_demod_info_valid_flag3_START          (31)
#define GBBP_VALPP_DEM_TYPE_TOA3_demod_info_valid_flag3_END            (31)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_DEM_WIDTH_CFG_UNION
 �ṹ˵��  : CPU_DEM_WIDTH_CFG �Ĵ����ṹ���塣��ַƫ����:0x1120����ֵ:0x00010000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_dem_width_cfg_reg;
    struct
    {
        unsigned int  cpu_demod_width_adjust : 2;  /* bit[0-1]  : �����̬λ������
                                                                  2��d0����̬����λ��Ϊ0
                                                                  2��d1����̬����λ��Ϊ1
                                                                  2��d2����̬����λ��Ϊ2
                                                                  ���������� */
        unsigned int  reserved_0             : 14; /* bit[2-15] : ���� */
        unsigned int  cpu_harq_width_mode    : 1;  /* bit[16]   : HARQ����ǰ����λ��ָ�ģʽ����
                                                                  0:���ս����̬λ�����ָ�����
                                                                  1:���������ֵλ��ָ����� */
        unsigned int  reserved_1             : 15; /* bit[17-31]: ���� */
    } reg;
} GBBP_CPU_DEM_WIDTH_CFG_UNION;
#define GBBP_CPU_DEM_WIDTH_CFG_cpu_demod_width_adjust_START  (0)
#define GBBP_CPU_DEM_WIDTH_CFG_cpu_demod_width_adjust_END    (1)
#define GBBP_CPU_DEM_WIDTH_CFG_cpu_harq_width_mode_START     (16)
#define GBBP_CPU_DEM_WIDTH_CFG_cpu_harq_width_mode_END       (16)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_DB_TYPE_CFG_UNION
 �ṹ˵��  : CPU_DB_TYPE_CFG �Ĵ����ṹ���塣��ַƫ����:0x1128����ֵ:0x00040001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_db_type_cfg_reg;
    struct
    {
        unsigned int  cpu_db_type      : 2;  /* bit[0-1]  : ��������õ�Dummy ѵ���������͡�
                                                            0��Dummy Burstѵ������ͬNB
                                                            1��Dummy Burstѵ������ͬC0ģʽѵ������
                                                            2��Dummy Burstѵ������ͬNBģʽѵ�������й̶���ӳ���ϵ��
                                                            3������
                                                            Ĭ��ֵ1�� */
        unsigned int  reserved_0       : 14; /* bit[2-15] : ���� */
        unsigned int  cpu_db_threshold : 4;  /* bit[16-19]: Dummy Burst�����о����ޣ�
                                                            0�� threshold_db=4��
                                                            1�� threshold_db=6��
                                                            2�� threshold_db=8��
                                                            3�� threshold_db=9��
                                                            4�� threshold_db=10��
                                                            5�� threshold_db=11��
                                                            6�� threshold_db=12��
                                                            7�� threshold_db=14��
                                                            8�� threshold_db=16��
                                                            9�� threshold_db=20��
                                                            others�� ���� */
        unsigned int  reserved_1       : 12; /* bit[20-31]: ���� */
    } reg;
} GBBP_CPU_DB_TYPE_CFG_UNION;
#define GBBP_CPU_DB_TYPE_CFG_cpu_db_type_START       (0)
#define GBBP_CPU_DB_TYPE_CFG_cpu_db_type_END         (1)
#define GBBP_CPU_DB_TYPE_CFG_cpu_db_threshold_START  (16)
#define GBBP_CPU_DB_TYPE_CFG_cpu_db_threshold_END    (19)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_DEM_BEP_MODE_EN_UNION
 �ṹ˵��  : CPU_DEM_BEP_MODE_EN �Ĵ����ṹ���塣��ַƫ����:0x112C����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_dem_bep_mode_en_reg;
    struct
    {
        unsigned int  cpu_dem_bep_mode_en : 1;  /* bit[0]   : 1��ʾ�򿪽��BEP���ܡ�
                                                              0��ʾ���ν��BEP���� */
        unsigned int  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} GBBP_CPU_DEM_BEP_MODE_EN_UNION;
#define GBBP_CPU_DEM_BEP_MODE_EN_cpu_dem_bep_mode_en_START  (0)
#define GBBP_CPU_DEM_BEP_MODE_EN_cpu_dem_bep_mode_en_END    (0)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_VALPP_CARRY_CTRL_UNION
 �ṹ˵��  : CPU_VALPP_CARRY_CTRL �Ĵ����ṹ���塣��ַƫ����:0x1130����ֵ:0x82008000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_valpp_carry_ctrl_reg;
    struct
    {
        unsigned int  cpu_carry_burst_pos  : 7;  /* bit[0-6]  : VALPP_RAM �� CARRY_RAM ���ݰ���Ŀ��BURSTλ��(carry to valpp) */
        unsigned int  reserved_0           : 8;  /* bit[7-14] : ���� */
        unsigned int  cpu_valpp_carry_mode : 1;  /* bit[15]   : VALPP_RAM �� CARRY_RAM ���ݰ��Ʒ���ָʾ��1��ʾ��VALPP_RAM��CARRY_RAM��0��ʾ��CARRY_RAM��VALPP_RAM,������ģʽ�£���Ҫ��Ӧ������cpu_carry_burst_pos��ΪVALPP_RAMд���ݵ���ʼ��ַ.
                                                                ��λĬ��ֵΪ1 */
        unsigned int  reserved_1           : 8;  /* bit[16-23]: ���� */
        unsigned int  cpu_valpp_carry_type : 2;  /* bit[24-25]: ��ʾ��CARRY_RAM��VALPP_RAM��һ��BURST������ָʾ
                                                                         00 ����ʾ����GMSK���Ƶ�SB�������
                                                                         10 ����ʾ����GMSK���Ƶ�NB�������
                                                                         11 ����ʾ����8PSK���Ƶ�NB�������
                                                                         ��������ʾ����GMSK���Ƶ�NB�������
                                                                ��λĬ��ֵΪ2��b10 */
        unsigned int  reserved_2           : 5;  /* bit[26-30]: ���� */
        unsigned int  cpu_valpp_carry_en   : 1;  /* bit[31]   : 1��ʾVALPP_RAM �� CARRY_RAM ���ݰ���ģʽʹ�ܣ���cpu_valpp_carry_mode����Ϊ1ʱ��cpu_valpp_carry_en����Ϊ1ʱ�����ģ����VALPP RAMд���ݵ�ͬʱ���Ὣ�������ͬʱ���浽CARRY RAM��.
                                                                ��λĬ��ֵΪ1 */
    } reg;
} GBBP_CPU_VALPP_CARRY_CTRL_UNION;
#define GBBP_CPU_VALPP_CARRY_CTRL_cpu_carry_burst_pos_START   (0)
#define GBBP_CPU_VALPP_CARRY_CTRL_cpu_carry_burst_pos_END     (6)
#define GBBP_CPU_VALPP_CARRY_CTRL_cpu_valpp_carry_mode_START  (15)
#define GBBP_CPU_VALPP_CARRY_CTRL_cpu_valpp_carry_mode_END    (15)
#define GBBP_CPU_VALPP_CARRY_CTRL_cpu_valpp_carry_type_START  (24)
#define GBBP_CPU_VALPP_CARRY_CTRL_cpu_valpp_carry_type_END    (25)
#define GBBP_CPU_VALPP_CARRY_CTRL_cpu_valpp_carry_en_START    (31)
#define GBBP_CPU_VALPP_CARRY_CTRL_cpu_valpp_carry_en_END      (31)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_VALPP_CARRY_START_UNION
 �ṹ˵��  : CPU_VALPP_CARRY_START �Ĵ����ṹ���塣��ַƫ����:0x1134����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_valpp_carry_start_reg;
    struct
    {
        unsigned int  cpu_valpp_carry_start_imi : 1;  /* bit[0]   : VALPP_RAM �� CARRY_RAM ���ݰ��������źţ�ֻ��Դ�CARRY_RAM��VALPP_RAMģʽ��Ч,�߼������� */
        unsigned int  reserved                  : 31; /* bit[1-31]: ���� */
    } reg;
} GBBP_CPU_VALPP_CARRY_START_UNION;
#define GBBP_CPU_VALPP_CARRY_START_cpu_valpp_carry_start_imi_START  (0)
#define GBBP_CPU_VALPP_CARRY_START_cpu_valpp_carry_start_imi_END    (0)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_SAIC_CTRL_UNION
 �ṹ˵��  : CPU_SAIC_CTRL �Ĵ����ṹ���塣��ַƫ����:0x1138����ֵ:0x02000101�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_saic_ctrl_reg;
    struct
    {
        unsigned int  cpu_saic_shift_pre   : 2;  /* bit[0-1]  : �о�����ǰ��SAIC�˲����ֵ����λֵ��11��13���أ�Ĭ��ֵ2��b01����ֵ������������ƫ�
                                                                2��b00: 11
                                                                2��b01: 12
                                                                2��b10: 13 */
        unsigned int  reserved_0           : 6;  /* bit[2-7]  : ���� */
        unsigned int  cpu_saic_shift_aft   : 2;  /* bit[8-9]  : �о�������SAIC�˲����ֵ����λֵ��10��12���أ�Ĭ��ֵ��2��b01����ֵ������������ƫ�
                                                                2��b00: 10;
                                                                2��b01: 11;
                                                                2��b10: 12; */
        unsigned int  reserved_1           : 6;  /* bit[10-15]: ���� */
        unsigned int  cpu_renew_toa_pos    : 2;  /* bit[16-17]: PHY��֡ͷλ��������֡NBλ�õĵ�������
                                                                ����ֵ��Χ��1��1�������ʾ��
                                                                2��b11����ʾ��֡��NB����֡��ǰһ�����ţ�
                                                                2��b01����ʾ��֡��NB����֡����һ�����ţ�
                                                                2��b00 ����ʾ������֡����������ź���TDMA֡ͷ��560qb�Զ����㡣 */
        unsigned int  reserved_2           : 2;  /* bit[18-19]: ���� */
        unsigned int  cpu_gmsk_ci_beta     : 2;  /* bit[20-21]: GMSK CI�����ĵ���ϵ����Ĭ��ֵ��15(����Ϊ2��b00)����ѡֵ1��8
                                                                2��b00:15
                                                                2��b01: 8
                                                                2��b10: 1
                                                                Ĭ��ֵΪ2��b00 */
        unsigned int  reserved_3           : 2;  /* bit[22-23]: ���� */
        unsigned int  cpu_cross_delta      : 3;  /* bit[24-26]: case(cpu_cross_delta)
                                                                3��b000: R[i][i] = R[i][i] + (R[i][i] >>8) ;
                                                                3��b001: R[i][i] = R[i][i] + (R[i][i] >>9) ;
                                                                3��b010: R[i][i] = R[i][i] + (R[i][i] >>10) ;
                                                                3��b011: R[i][i] = R[i][i] + (R[i][i] >>11) ;
                                                                3��b100: R[i][i] = R[i][i];
                                                                cpu_cross_delta�ź�������ѡ��Խ���Ԫ�صĴ���ʽ��Ĭ��ֵ��3��b010�� */
        unsigned int  reserved_4           : 4;  /* bit[27-30]: ���� */
        unsigned int  cpu_nb_info_rpt_mode : 1;  /* bit[31]   : 1 ��ʾ�̶�ѡ��ż·��0��ʾѡ�����· Ĭ��ֵΪ0��                     ���ź�����ѡ���ϱ���nb_pos_cpu, nb_pos_adj_cpu��C/I�ȡ� */
    } reg;
} GBBP_CPU_SAIC_CTRL_UNION;
#define GBBP_CPU_SAIC_CTRL_cpu_saic_shift_pre_START    (0)
#define GBBP_CPU_SAIC_CTRL_cpu_saic_shift_pre_END      (1)
#define GBBP_CPU_SAIC_CTRL_cpu_saic_shift_aft_START    (8)
#define GBBP_CPU_SAIC_CTRL_cpu_saic_shift_aft_END      (9)
#define GBBP_CPU_SAIC_CTRL_cpu_renew_toa_pos_START     (16)
#define GBBP_CPU_SAIC_CTRL_cpu_renew_toa_pos_END       (17)
#define GBBP_CPU_SAIC_CTRL_cpu_gmsk_ci_beta_START      (20)
#define GBBP_CPU_SAIC_CTRL_cpu_gmsk_ci_beta_END        (21)
#define GBBP_CPU_SAIC_CTRL_cpu_cross_delta_START       (24)
#define GBBP_CPU_SAIC_CTRL_cpu_cross_delta_END         (26)
#define GBBP_CPU_SAIC_CTRL_cpu_nb_info_rpt_mode_START  (31)
#define GBBP_CPU_SAIC_CTRL_cpu_nb_info_rpt_mode_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_MAX_DB_DATA_ENERGY_RPT_UNION
 �ṹ˵��  : MAX_DB_DATA_ENERGY_RPT �Ĵ����ṹ���塣��ַƫ����:0x113C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      max_db_data_energy_rpt_reg;
    struct
    {
        unsigned int  max_data_energy_cpu : 22; /* bit[0-21] : DummuBurst���DATA��������ϱ� */
        unsigned int  reserved            : 10; /* bit[22-31]: ���� */
    } reg;
} GBBP_MAX_DB_DATA_ENERGY_RPT_UNION;
#define GBBP_MAX_DB_DATA_ENERGY_RPT_max_data_energy_cpu_START  (0)
#define GBBP_MAX_DB_DATA_ENERGY_RPT_max_data_energy_cpu_END    (21)


/*****************************************************************************
 �ṹ��    : GBBP_ENG_WEIGHT_UNION
 �ṹ˵��  : ENG_WEIGHT �Ĵ����ṹ���塣��ַƫ����:0x1144����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      eng_weight_reg;
    struct
    {
        unsigned int  cpu_mid_finger_weight : 3;  /* bit[0-2]  : NBλ�ü���ʹ�õ����ľ�������Ȩֵ��Ĭ��ֵ0
                                                                 ������sb��Ȩֵһ�� */
        unsigned int  reserved_0            : 1;  /* bit[3]    : ���� */
        unsigned int  cpu_rptpos_use_weight : 1;  /* bit[4]    : �ϱ���nb_pos��nb_pos_adjʹ�����ľ�������Ȩ�㷨��1Ϊʹ�ã�Ĭ��ֵ0 */
        unsigned int  reserved_1            : 3;  /* bit[5-7]  : ���� */
        unsigned int  cpu_dempos_use_weight : 1;  /* bit[8]    : ���λ�ü̳�ʹ�����ľ�������Ȩ�㷨��1Ϊʹ�ã�Ĭ��ֵ0 */
        unsigned int  reserved_2            : 7;  /* bit[9-15] : ���� */
        unsigned int  cpu_sb_finger_weight  : 3;  /* bit[16-18]: SBλ�ü���ʹ�õ����ľ�������Ȩֵ��Ĭ��ֵ0
                                                                 0��ʾȨֵΪ1��
                                                                 1��ʾȨֵΪ65/64��
                                                                 2��ʾȨֵΪ33/32��
                                                                 3��ʾȨֵΪ17/16��
                                                                 4��ʾȨֵΪ9/8��
                                                                 5��ʾȨֵΪ5/4�� */
        unsigned int  reserved_3            : 13; /* bit[19-31]: ���� */
    } reg;
} GBBP_ENG_WEIGHT_UNION;
#define GBBP_ENG_WEIGHT_cpu_mid_finger_weight_START  (0)
#define GBBP_ENG_WEIGHT_cpu_mid_finger_weight_END    (2)
#define GBBP_ENG_WEIGHT_cpu_rptpos_use_weight_START  (4)
#define GBBP_ENG_WEIGHT_cpu_rptpos_use_weight_END    (4)
#define GBBP_ENG_WEIGHT_cpu_dempos_use_weight_START  (8)
#define GBBP_ENG_WEIGHT_cpu_dempos_use_weight_END    (8)
#define GBBP_ENG_WEIGHT_cpu_sb_finger_weight_START   (16)
#define GBBP_ENG_WEIGHT_cpu_sb_finger_weight_END     (18)


/*****************************************************************************
 �ṹ��    : GBBP_LS_DC_CPU_UNION
 �ṹ˵��  : LS_DC_CPU �Ĵ����ṹ���塣��ַƫ����:0x1160����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      ls_dc_cpu_reg;
    struct
    {
        unsigned int  ls_dc_q_cpu : 8;  /* bit[0-7]  : ��ǰburstֱ��Q·�ϱ� */
        unsigned int  reserved_0  : 8;  /* bit[8-15] : ���� */
        unsigned int  ls_dc_i_cpu : 8;  /* bit[16-23]: ��ǰburstֱ��I·�ϱ� */
        unsigned int  reserved_1  : 8;  /* bit[24-31]: ���� */
    } reg;
} GBBP_LS_DC_CPU_UNION;
#define GBBP_LS_DC_CPU_ls_dc_q_cpu_START  (0)
#define GBBP_LS_DC_CPU_ls_dc_q_cpu_END    (7)
#define GBBP_LS_DC_CPU_ls_dc_i_cpu_START  (16)
#define GBBP_LS_DC_CPU_ls_dc_i_cpu_END    (23)


/*****************************************************************************
 �ṹ��    : GBBP_LS_TOA_RPT_EN_UNION
 �ṹ˵��  : LS_TOA_RPT_EN �Ĵ����ṹ���塣��ַƫ����:0x1164����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      ls_toa_rpt_en_reg;
    struct
    {
        unsigned int  cpu_ls_toa_rpt_en : 1;  /* bit[0]   : LSȥֱ��TOA�ϱ�ʹ�ܣ�0��ʾ�رգ�1��ʾ�򿪡� */
        unsigned int  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} GBBP_LS_TOA_RPT_EN_UNION;
#define GBBP_LS_TOA_RPT_EN_cpu_ls_toa_rpt_en_START  (0)
#define GBBP_LS_TOA_RPT_EN_cpu_ls_toa_rpt_en_END    (0)


/*****************************************************************************
 �ṹ��    : GBBP_FB_2_POS_ENG_UNION
 �ṹ˵��  : FB_2_POS_ENG �Ĵ����ṹ���塣��ַƫ����:0x1168����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      fb_2_pos_eng_reg;
    struct
    {
        unsigned int  fb_pos_2_cpu       : 13; /* bit[0-12] : �ݵ�ǰʱ�̵ڶ�����FB���ڵ�FBλ�� */
        unsigned int  fb_square_max2_cpu : 18; /* bit[13-30]: �ݵ�ǰʱ�̵ڶ�����FB���ڵ�FB������� */
        unsigned int  reserved           : 1;  /* bit[31]   : ���� */
    } reg;
} GBBP_FB_2_POS_ENG_UNION;
#define GBBP_FB_2_POS_ENG_fb_pos_2_cpu_START        (0)
#define GBBP_FB_2_POS_ENG_fb_pos_2_cpu_END          (12)
#define GBBP_FB_2_POS_ENG_fb_square_max2_cpu_START  (13)
#define GBBP_FB_2_POS_ENG_fb_square_max2_cpu_END    (30)


/*****************************************************************************
 �ṹ��    : GBBP_FB_3_POS_ENG_UNION
 �ṹ˵��  : FB_3_POS_ENG �Ĵ����ṹ���塣��ַƫ����:0x116C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      fb_3_pos_eng_reg;
    struct
    {
        unsigned int  fb_pos_3_cpu       : 13; /* bit[0-12] : �ݵ�ǰʱ�̵�������FB���ڵ�FBλ�� */
        unsigned int  fb_square_max3_cpu : 18; /* bit[13-30]: �ݵ�ǰʱ�̵�������FB���ڵ�FB������� */
        unsigned int  reserved           : 1;  /* bit[31]   : ���� */
    } reg;
} GBBP_FB_3_POS_ENG_UNION;
#define GBBP_FB_3_POS_ENG_fb_pos_3_cpu_START        (0)
#define GBBP_FB_3_POS_ENG_fb_pos_3_cpu_END          (12)
#define GBBP_FB_3_POS_ENG_fb_square_max3_cpu_START  (13)
#define GBBP_FB_3_POS_ENG_fb_square_max3_cpu_END    (30)


/*****************************************************************************
 �ṹ��    : GBBP_SB_SAVE_STATUS_UNION
 �ṹ˵��  : SB_SAVE_STATUS �Ĵ����ṹ���塣��ַƫ����:0x1170����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      sb_save_status_reg;
    struct
    {
        unsigned int  sb_save_status_cpu : 2;  /* bit[0-1] : SB���ݱ���״̬�ϱ�,ÿ��gsp_sb_save_start������
                                                             00��δ����SB���ݴ洢 
                                                             01������SB���ݴ洢���ұ������ 
                                                             10������SB�洢�����������ǰ�쳣��ֹ��������ʹ�ܱ����ͣ���������Ч */
        unsigned int  reserved           : 30; /* bit[2-31]: ���� */
    } reg;
} GBBP_SB_SAVE_STATUS_UNION;
#define GBBP_SB_SAVE_STATUS_sb_save_status_cpu_START  (0)
#define GBBP_SB_SAVE_STATUS_sb_save_status_cpu_END    (1)


/*****************************************************************************
 �ṹ��    : GBBP_SHORT_11X_CFG_UNION
 �ṹ˵��  : SHORT_11X_CFG �Ĵ����ṹ���塣��ַƫ����:0x1174����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      short_11x_cfg_reg;
    struct
    {
        unsigned int  cpu_11x_capt_disable : 1;  /* bit[0]   : 110/111����ģʽʱ�������벶��̬��ֱ�ӽ������̬�� */
        unsigned int  reserved_0           : 3;  /* bit[1-3] : ���� */
        unsigned int  cpu_afc_delay_sel    : 1;  /* bit[4]   : 110/111����ģʽʱ��AFC�������;
                                                               0��ʾ�ӳٳ���Ϊ16��1��ʾ�ӳٳ���Ϊ2��
                                                               ���cpu_11x_capt_disable=0���򲶻�̬�ӳٳ��ȹ̶�Ϊ2������̬�̶�Ϊ16�� */
        unsigned int  reserved_1           : 27; /* bit[5-31]: ���� */
    } reg;
} GBBP_SHORT_11X_CFG_UNION;
#define GBBP_SHORT_11X_CFG_cpu_11x_capt_disable_START  (0)
#define GBBP_SHORT_11X_CFG_cpu_11x_capt_disable_END    (0)
#define GBBP_SHORT_11X_CFG_cpu_afc_delay_sel_START     (4)
#define GBBP_SHORT_11X_CFG_cpu_afc_delay_sel_END       (4)


/*****************************************************************************
 �ṹ��    : GBBP_FAST_101_CFG_UNION
 �ṹ˵��  : FAST_101_CFG �Ĵ����ṹ���塣��ַƫ����:0x1178����ֵ:0x80000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      fast_101_cfg_reg;
    struct
    {
        unsigned int  cpu_fast_101_thresh     : 18; /* bit[0-17] : ��ǰ����SB��FB�������ޣ������ڵ��ڸ�����ʱ������SB������� */
        unsigned int  reserved                : 13; /* bit[18-30]: ���� */
        unsigned int  cpu_fast_101_dist_judge : 1;  /* bit[31]   : ����101ģʽ���Ƿ�����FB��SB������ж�ʹ�ܣ�Ϊ1��ʾ��FB��SB���볬��34�����򱾴�����ʧ�� */
    } reg;
} GBBP_FAST_101_CFG_UNION;
#define GBBP_FAST_101_CFG_cpu_fast_101_thresh_START      (0)
#define GBBP_FAST_101_CFG_cpu_fast_101_thresh_END        (17)
#define GBBP_FAST_101_CFG_cpu_fast_101_dist_judge_START  (31)
#define GBBP_FAST_101_CFG_cpu_fast_101_dist_judge_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_HEAVY_NOISE_CFG_UNION
 �ṹ˵��  : HEAVY_NOISE_CFG �Ĵ����ṹ���塣��ַƫ����:0x117C����ֵ:0x00007FFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      heavy_noise_cfg_reg;
    struct
    {
        unsigned int  cpu_noise_afc_thresh        : 19; /* bit[0-18] : ֹͣAFC�������������ޣ���������ֵ���ڸ�����ʱ������CI��ֵ��Σ���������AFC */
        unsigned int  reserved                    : 12; /* bit[19-30]: ���� */
        unsigned int  cpu_heavy_noise_afc_disable : 1;  /* bit[31]   : ������������������һ�����ޣ�ʱ��ֹͣAFC��������ƽ�ź�
                                                                       1����ʾ����������ʱ������AFC������
                                                                       0����ʾ������������С����AFC���� */
    } reg;
} GBBP_HEAVY_NOISE_CFG_UNION;
#define GBBP_HEAVY_NOISE_CFG_cpu_noise_afc_thresh_START         (0)
#define GBBP_HEAVY_NOISE_CFG_cpu_noise_afc_thresh_END           (18)
#define GBBP_HEAVY_NOISE_CFG_cpu_heavy_noise_afc_disable_START  (31)
#define GBBP_HEAVY_NOISE_CFG_cpu_heavy_noise_afc_disable_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_CPU_LUISE_AFC_UNION
 �ṹ˵��  : ADDR_CPU_LUISE_AFC �Ĵ����ṹ���塣��ַƫ����:0x1258����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_cpu_luise_afc_reg;
    struct
    {
        unsigned int  cpu_luise_afc_en_imi : 1;  /* bit[0]    : Luise��Ƶʹ�� */
        unsigned int  reserved_0           : 7;  /* bit[1-7]  : ���� */
        unsigned int  cpu_single_tcxo_en   : 1;  /* bit[8]    : ��TCXOʹ���źţ����ڿ�������ǰ�����Ƿ񾭹�NCO��ƫ */
        unsigned int  reserved_1           : 7;  /* bit[9-15] : ���� */
        unsigned int  luise_fed            : 16; /* bit[16-31]: Luise��Ƶ�Ż��㷨����õ���Ƶƫ����ֵ */
    } reg;
} GBBP_ADDR_CPU_LUISE_AFC_UNION;
#define GBBP_ADDR_CPU_LUISE_AFC_cpu_luise_afc_en_imi_START  (0)
#define GBBP_ADDR_CPU_LUISE_AFC_cpu_luise_afc_en_imi_END    (0)
#define GBBP_ADDR_CPU_LUISE_AFC_cpu_single_tcxo_en_START    (8)
#define GBBP_ADDR_CPU_LUISE_AFC_cpu_single_tcxo_en_END      (8)
#define GBBP_ADDR_CPU_LUISE_AFC_luise_fed_START             (16)
#define GBBP_ADDR_CPU_LUISE_AFC_luise_fed_END               (31)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_GDRX_SLEEP_POINT_UNION
 �ṹ˵��  : ADDR_GDRX_SLEEP_POINT �Ĵ����ṹ���塣��ַƫ����:0x125C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_gdrx_sleep_point_reg;
    struct
    {
        unsigned int  gdrx_sleep_point : 13; /* bit[0-12] : ����˯��ģʽ�£�˯����ʼQbʱ�̣�TDMA��ʱ�̣��ò����ǻ���TDMAʱ��gtc_tdma_qb�� */
        unsigned int  reserved         : 19; /* bit[13-31]: ���� */
    } reg;
} GBBP_ADDR_GDRX_SLEEP_POINT_UNION;
#define GBBP_ADDR_GDRX_SLEEP_POINT_gdrx_sleep_point_START  (0)
#define GBBP_ADDR_GDRX_SLEEP_POINT_gdrx_sleep_point_END    (12)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_CPU_TRANS_COMP_UNION
 �ṹ˵��  : ADDR_CPU_TRANS_COMP �Ĵ����ṹ���塣��ַƫ����:0x1260����ֵ:0x00000010�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_cpu_trans_comp_reg;
    struct
    {
        unsigned int  cpu_trans_comp : 10; /* bit[0-9]  : ��ʱ��Ϣ��ON�����䵽OFF����������õĶ�ʱ��Ϣ������������ֵҪ����ȫ�����ݴ���ʱ�ӣ���λQB��Ĭ������16QB�� */
        unsigned int  reserved       : 22; /* bit[10-31]: ���� */
    } reg;
} GBBP_ADDR_CPU_TRANS_COMP_UNION;
#define GBBP_ADDR_CPU_TRANS_COMP_cpu_trans_comp_START  (0)
#define GBBP_ADDR_CPU_TRANS_COMP_cpu_trans_comp_END    (9)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_RX_IQ_MISMATCH_REG0_UNION
 �ṹ˵��  : ADDR_RX_IQ_MISMATCH_REG0 �Ĵ����ṹ���塣��ַƫ����:0x1270����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_rx_iq_mismatch_reg0_reg;
    struct
    {
        unsigned int  cpu_iq_comp_amp0   : 10; /* bit[0-9]  : ��0�����У׼�������ֵA��10�����з�������ȡֵ��Χ-511~511�� */
        unsigned int  reserved_0         : 6;  /* bit[10-15]: ���� */
        unsigned int  cpu_iq_comp_phase0 : 11; /* bit[16-26]: ��0����λУ׼�������ֵP��11�����з�������ȡֵ��Χ-1023~1023�� */
        unsigned int  reserved_1         : 5;  /* bit[27-31]: ���� */
    } reg;
} GBBP_ADDR_RX_IQ_MISMATCH_REG0_UNION;
#define GBBP_ADDR_RX_IQ_MISMATCH_REG0_cpu_iq_comp_amp0_START    (0)
#define GBBP_ADDR_RX_IQ_MISMATCH_REG0_cpu_iq_comp_amp0_END      (9)
#define GBBP_ADDR_RX_IQ_MISMATCH_REG0_cpu_iq_comp_phase0_START  (16)
#define GBBP_ADDR_RX_IQ_MISMATCH_REG0_cpu_iq_comp_phase0_END    (26)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_RX_IQ_MISMATCH_REG1_UNION
 �ṹ˵��  : ADDR_RX_IQ_MISMATCH_REG1 �Ĵ����ṹ���塣��ַƫ����:0x1274����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_rx_iq_mismatch_reg1_reg;
    struct
    {
        unsigned int  cpu_iq_comp_amp1   : 10; /* bit[0-9]  : ��1�����У׼�������ֵA��10�����з�������ȡֵ��Χ-511~511�� */
        unsigned int  reserved_0         : 6;  /* bit[10-15]: ���� */
        unsigned int  cpu_iq_comp_phase1 : 11; /* bit[16-26]: ��1����λУ׼�������ֵP��11�����з�������ȡֵ��Χ-1023~1023�� */
        unsigned int  reserved_1         : 5;  /* bit[27-31]: ���� */
    } reg;
} GBBP_ADDR_RX_IQ_MISMATCH_REG1_UNION;
#define GBBP_ADDR_RX_IQ_MISMATCH_REG1_cpu_iq_comp_amp1_START    (0)
#define GBBP_ADDR_RX_IQ_MISMATCH_REG1_cpu_iq_comp_amp1_END      (9)
#define GBBP_ADDR_RX_IQ_MISMATCH_REG1_cpu_iq_comp_phase1_START  (16)
#define GBBP_ADDR_RX_IQ_MISMATCH_REG1_cpu_iq_comp_phase1_END    (26)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_RX_IQ_MISMATCH_REG2_UNION
 �ṹ˵��  : ADDR_RX_IQ_MISMATCH_REG2 �Ĵ����ṹ���塣��ַƫ����:0x1278����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_rx_iq_mismatch_reg2_reg;
    struct
    {
        unsigned int  cpu_iq_comp_amp2   : 10; /* bit[0-9]  : ��2�����У׼�������ֵA��10�����з�������ȡֵ��Χ-511~511�� */
        unsigned int  reserved_0         : 6;  /* bit[10-15]: ���� */
        unsigned int  cpu_iq_comp_phase2 : 11; /* bit[16-26]: ��2����λУ׼�������ֵP��11�����з�������ȡֵ��Χ-1023~1023�� */
        unsigned int  reserved_1         : 5;  /* bit[27-31]: ���� */
    } reg;
} GBBP_ADDR_RX_IQ_MISMATCH_REG2_UNION;
#define GBBP_ADDR_RX_IQ_MISMATCH_REG2_cpu_iq_comp_amp2_START    (0)
#define GBBP_ADDR_RX_IQ_MISMATCH_REG2_cpu_iq_comp_amp2_END      (9)
#define GBBP_ADDR_RX_IQ_MISMATCH_REG2_cpu_iq_comp_phase2_START  (16)
#define GBBP_ADDR_RX_IQ_MISMATCH_REG2_cpu_iq_comp_phase2_END    (26)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_RX_IQ_MISMATCH_REG3_UNION
 �ṹ˵��  : ADDR_RX_IQ_MISMATCH_REG3 �Ĵ����ṹ���塣��ַƫ����:0x127C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_rx_iq_mismatch_reg3_reg;
    struct
    {
        unsigned int  cpu_iq_comp_amp3   : 10; /* bit[0-9]  : ��3�����У׼�������ֵA��10�����з�������ȡֵ��Χ-511~511�� */
        unsigned int  reserved_0         : 6;  /* bit[10-15]: ���� */
        unsigned int  cpu_iq_comp_phase3 : 11; /* bit[16-26]: ��3����λУ׼�������ֵP��11�����з�������ȡֵ��Χ-1023~1023�� */
        unsigned int  reserved_1         : 5;  /* bit[27-31]: ���� */
    } reg;
} GBBP_ADDR_RX_IQ_MISMATCH_REG3_UNION;
#define GBBP_ADDR_RX_IQ_MISMATCH_REG3_cpu_iq_comp_amp3_START    (0)
#define GBBP_ADDR_RX_IQ_MISMATCH_REG3_cpu_iq_comp_amp3_END      (9)
#define GBBP_ADDR_RX_IQ_MISMATCH_REG3_cpu_iq_comp_phase3_START  (16)
#define GBBP_ADDR_RX_IQ_MISMATCH_REG3_cpu_iq_comp_phase3_END    (26)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_RX_IQ_MISMATCH_REG4_UNION
 �ṹ˵��  : ADDR_RX_IQ_MISMATCH_REG4 �Ĵ����ṹ���塣��ַƫ����:0x1280����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_rx_iq_mismatch_reg4_reg;
    struct
    {
        unsigned int  cpu_iq_comp_amp4   : 10; /* bit[0-9]  : ��4�����У׼�������ֵA��10�����з�������ȡֵ��Χ-511~511�� */
        unsigned int  reserved_0         : 6;  /* bit[10-15]: ���� */
        unsigned int  cpu_iq_comp_phase4 : 11; /* bit[16-26]: ��4����λУ׼�������ֵP��11�����з�������ȡֵ��Χ-1023~1023�� */
        unsigned int  reserved_1         : 5;  /* bit[27-31]: ���� */
    } reg;
} GBBP_ADDR_RX_IQ_MISMATCH_REG4_UNION;
#define GBBP_ADDR_RX_IQ_MISMATCH_REG4_cpu_iq_comp_amp4_START    (0)
#define GBBP_ADDR_RX_IQ_MISMATCH_REG4_cpu_iq_comp_amp4_END      (9)
#define GBBP_ADDR_RX_IQ_MISMATCH_REG4_cpu_iq_comp_phase4_START  (16)
#define GBBP_ADDR_RX_IQ_MISMATCH_REG4_cpu_iq_comp_phase4_END    (26)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_TX_RRC_EXT_UNION
 �ṹ˵��  : ADDR_TX_RRC_EXT �Ĵ����ṹ���塣��ַƫ����:0x1284����ֵ:0x00040006�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_tx_rrc_ext_reg;
    struct
    {
        unsigned int  cpu_tx_rrc_finish_interval : 4;  /* bit[0-3]  : ���һ��tx_rrx_data_ind_in��gmod_finish֮��ļ��clk�� */
        unsigned int  reserved_0                 : 12; /* bit[4-15] : ���� */
        unsigned int  cpu_tx_rrc_ext_num         : 4;  /* bit[16-19]: �ڵ��ƽ�������չ����������� */
        unsigned int  reserved_1                 : 12; /* bit[20-31]: ���� */
    } reg;
} GBBP_ADDR_TX_RRC_EXT_UNION;
#define GBBP_ADDR_TX_RRC_EXT_cpu_tx_rrc_finish_interval_START  (0)
#define GBBP_ADDR_TX_RRC_EXT_cpu_tx_rrc_finish_interval_END    (3)
#define GBBP_ADDR_TX_RRC_EXT_cpu_tx_rrc_ext_num_START          (16)
#define GBBP_ADDR_TX_RRC_EXT_cpu_tx_rrc_ext_num_END            (19)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_MAX_PHI_DEV_UNION
 �ṹ˵��  : ADDR_MAX_PHI_DEV �Ĵ����ṹ���塣��ַƫ����:0x1288����ֵ:0x000002F8�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_max_phi_dev_reg;
    struct
    {
        unsigned int  cpu_max_phi_dev : 11; /* bit[0-10] : SB���Ƶƫ�޷���Ĭ��ֵΪ1800MHz�����Ƶƫ760��900MHzʱ����380�� */
        unsigned int  reserved        : 21; /* bit[11-31]: ���� */
    } reg;
} GBBP_ADDR_MAX_PHI_DEV_UNION;
#define GBBP_ADDR_MAX_PHI_DEV_cpu_max_phi_dev_START  (0)
#define GBBP_ADDR_MAX_PHI_DEV_cpu_max_phi_dev_END    (10)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_HD35_PARA_REG_UNION
 �ṹ˵��  : ADDR_HD35_PARA_REG �Ĵ����ṹ���塣��ַƫ����:0x1290����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_hd35_para_reg_reg;
    struct
    {
        unsigned int  cpu_hd35_page_switch_en : 1;  /* bit[0]    : HD3/5��ʼ���ò�������RAMƹ�ҷ���ʹ�ܣ�1��ʾ����ƹ�ҷ��ʣ�0��ʾ�̶�����ƹRAM�ռ䣻�����ź�Ϊ1ʱ���߼��ڲ���TDMA֡ͷ�Զ��л�ƹ�ұ�־�� */
        unsigned int  reserved_0              : 15; /* bit[1-15] : ���� */
        unsigned int  cpu_hd35_cal_bypass     : 1;  /* bit[16]   : HD3/5г������������·��0����ʾг���������ܲ���·�����Ƿ����г����������Ҫ�ο�gsp_hd35_cal_en���������1����ʾг������������·����V8R1�汾ʱ����ȫһ�¡� */
        unsigned int  reserved_1              : 15; /* bit[17-31]: ���� */
    } reg;
} GBBP_ADDR_HD35_PARA_REG_UNION;
#define GBBP_ADDR_HD35_PARA_REG_cpu_hd35_page_switch_en_START  (0)
#define GBBP_ADDR_HD35_PARA_REG_cpu_hd35_page_switch_en_END    (0)
#define GBBP_ADDR_HD35_PARA_REG_cpu_hd35_cal_bypass_START      (16)
#define GBBP_ADDR_HD35_PARA_REG_cpu_hd35_cal_bypass_END        (16)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_SPI_RF_CFG_UNION
 �ṹ˵��  : CPU_SPI_RF_CFG �Ĵ����ṹ���塣��ַƫ����:0x1368����ֵ:0x80000400�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_spi_rf_cfg_reg;
    struct
    {
        unsigned int  cpu_spi_rd_start_addr  : 8;  /* bit[0-7]  : CPU�ӿ�����SPI���ڴ���������SPI DATA RAM����ʼλ�ã���λĬ��ֵΪ8'd0 */
        unsigned int  cpu_spi_trans_data_num : 5;  /* bit[8-12] : CPU�ӿ����ñ�����Ҫ���͵�SPI������������00001��ʾһ������10000��ʾ16��������λĬ��ֵΪ5'b00100 */
        unsigned int  reserved               : 18; /* bit[13-30]: ���� */
        unsigned int  spi_gtc_sel            : 1;  /* bit[31]   : 1��ʾSPI��Ƶ���Ʋ�����GTCģ�������0��ʾSPI��Ƶ���Ʋ�����CPU�ӿ�ģ�������Ĭ��ֵΪ1�����ź�ֻ������������TA�ϴ�ʱ����RF��Ƶ��ʱ���⣻��������¸��źŶ�Ӧ������Ϊ1 */
    } reg;
} GBBP_CPU_SPI_RF_CFG_UNION;
#define GBBP_CPU_SPI_RF_CFG_cpu_spi_rd_start_addr_START   (0)
#define GBBP_CPU_SPI_RF_CFG_cpu_spi_rd_start_addr_END     (7)
#define GBBP_CPU_SPI_RF_CFG_cpu_spi_trans_data_num_START  (8)
#define GBBP_CPU_SPI_RF_CFG_cpu_spi_trans_data_num_END    (12)
#define GBBP_CPU_SPI_RF_CFG_spi_gtc_sel_START             (31)
#define GBBP_CPU_SPI_RF_CFG_spi_gtc_sel_END               (31)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_SPI_RF_RD_UNION
 �ṹ˵��  : CPU_SPI_RF_RD �Ĵ����ṹ���塣��ַƫ����:0x136C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_spi_rf_rd_reg;
    struct
    {
        unsigned int  cpu_spi_rd_en_imi : 1;  /* bit[0]   : CPU����SPI���ݷ������� */
        unsigned int  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} GBBP_CPU_SPI_RF_RD_UNION;
#define GBBP_CPU_SPI_RF_RD_cpu_spi_rd_en_imi_START  (0)
#define GBBP_CPU_SPI_RF_RD_cpu_spi_rd_en_imi_END    (0)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_LINE_CTRL_UNION
 �ṹ˵��  : CPU_LINE_CTRL �Ĵ����ṹ���塣��ַƫ����:0x1364����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_line_ctrl_reg;
    struct
    {
        unsigned int  cpu_gtc_line_ctrl           : 31; /* bit[0-30]: �����߿�CPU�ӿ����ã����������NV������� */
        unsigned int  cpu_gtc_line_ctrl_wr_en_imi : 1;  /* bit[31]  : 28bit�����߿��ź�CPUдʹ��ָʾ�źš� */
    } reg;
} GBBP_CPU_LINE_CTRL_UNION;
#define GBBP_CPU_LINE_CTRL_cpu_gtc_line_ctrl_START            (0)
#define GBBP_CPU_LINE_CTRL_cpu_gtc_line_ctrl_END              (30)
#define GBBP_CPU_LINE_CTRL_cpu_gtc_line_ctrl_wr_en_imi_START  (31)
#define GBBP_CPU_LINE_CTRL_cpu_gtc_line_ctrl_wr_en_imi_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_GSP_LINE_STATE_RPT_UNION
 �ṹ˵��  : GTC_GSP_LINE_STATE_RPT �Ĵ����ṹ���塣��ַƫ����:0x1384����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gtc_gsp_line_state_rpt_reg;
    struct
    {
        unsigned int  gtc_ant_pa_sel : 31; /* bit[0-30]: �����߿�ʵ���߿�״̬�������á� */
        unsigned int  reserved       : 1;  /* bit[31]  : ���� */
    } reg;
} GBBP_GTC_GSP_LINE_STATE_RPT_UNION;
#define GBBP_GTC_GSP_LINE_STATE_RPT_gtc_ant_pa_sel_START  (0)
#define GBBP_GTC_GSP_LINE_STATE_RPT_gtc_ant_pa_sel_END    (30)


/*****************************************************************************
 �ṹ��    : GBBP_AAGC_GAIN1_CPU_UNION
 �ṹ˵��  : AAGC_GAIN1_CPU �Ĵ����ṹ���塣��ַƫ����:0x1460����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      aagc_gain1_cpu_reg;
    struct
    {
        unsigned int  next_gain_1d     : 3;  /* bit[0-2]  : ���һ��ʱ϶AGC�����������档 */
        unsigned int  reserved_0       : 5;  /* bit[3-7]  : ���� */
        unsigned int  rssi_1d          : 12; /* bit[8-19] : ���һ��ʱ϶AGC RSSIֵ����λ0.125dBm���ϱ���CPU����ֵ���ǿտڵ�RSSIֵ�� */
        unsigned int  reserved_1       : 4;  /* bit[20-23]: ���� */
        unsigned int  curr_gain_1d     : 3;  /* bit[24-26]: ���һ��ʱ϶AAGC��λ�ϱ��� */
        unsigned int  reserved_2       : 4;  /* bit[27-30]: ���� */
        unsigned int  agc_fast_flag_1d : 1;  /* bit[31]   : ���һ��ʱ϶�����ٲ�����־�ϱ���1��ʾ��ǰΪ���ٲ�����0��ʾ��ǰΪ���ٲ����� */
    } reg;
} GBBP_AAGC_GAIN1_CPU_UNION;
#define GBBP_AAGC_GAIN1_CPU_next_gain_1d_START      (0)
#define GBBP_AAGC_GAIN1_CPU_next_gain_1d_END        (2)
#define GBBP_AAGC_GAIN1_CPU_rssi_1d_START           (8)
#define GBBP_AAGC_GAIN1_CPU_rssi_1d_END             (19)
#define GBBP_AAGC_GAIN1_CPU_curr_gain_1d_START      (24)
#define GBBP_AAGC_GAIN1_CPU_curr_gain_1d_END        (26)
#define GBBP_AAGC_GAIN1_CPU_agc_fast_flag_1d_START  (31)
#define GBBP_AAGC_GAIN1_CPU_agc_fast_flag_1d_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_AAGC_GAIN2_CPU_UNION
 �ṹ˵��  : AAGC_GAIN2_CPU �Ĵ����ṹ���塣��ַƫ����:0x1464����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      aagc_gain2_cpu_reg;
    struct
    {
        unsigned int  next_gain_2d     : 3;  /* bit[0-2]  : �ν�һ��ʱ϶AGC�����������档 */
        unsigned int  reserved_0       : 5;  /* bit[3-7]  : ���� */
        unsigned int  rssi_2d          : 12; /* bit[8-19] : �ν�һ��ʱ϶AGC RSSIֵ����λ0.125dBm���ϱ���CPU����ֵ���ǿտڵ�RSSIֵ�� */
        unsigned int  reserved_1       : 4;  /* bit[20-23]: ���� */
        unsigned int  curr_gain_2d     : 3;  /* bit[24-26]: �ν�һ��ʱ϶AAGC��λ�ϱ��� */
        unsigned int  reserved_2       : 4;  /* bit[27-30]: ���� */
        unsigned int  agc_fast_flag_2d : 1;  /* bit[31]   : �ν�һ��ʱ϶�����ٲ�����־�ϱ���1��ʾ��ǰΪ���ٲ�����0��ʾ��ǰΪ���ٲ����� */
    } reg;
} GBBP_AAGC_GAIN2_CPU_UNION;
#define GBBP_AAGC_GAIN2_CPU_next_gain_2d_START      (0)
#define GBBP_AAGC_GAIN2_CPU_next_gain_2d_END        (2)
#define GBBP_AAGC_GAIN2_CPU_rssi_2d_START           (8)
#define GBBP_AAGC_GAIN2_CPU_rssi_2d_END             (19)
#define GBBP_AAGC_GAIN2_CPU_curr_gain_2d_START      (24)
#define GBBP_AAGC_GAIN2_CPU_curr_gain_2d_END        (26)
#define GBBP_AAGC_GAIN2_CPU_agc_fast_flag_2d_START  (31)
#define GBBP_AAGC_GAIN2_CPU_agc_fast_flag_2d_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_AAGC_GAIN3_CPU_UNION
 �ṹ˵��  : AAGC_GAIN3_CPU �Ĵ����ṹ���塣��ַƫ����:0x1468����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      aagc_gain3_cpu_reg;
    struct
    {
        unsigned int  next_gain_3d     : 3;  /* bit[0-2]  : �δν�һ��ʱ϶AGC�����������档 */
        unsigned int  reserved_0       : 5;  /* bit[3-7]  : ���� */
        unsigned int  rssi_3d          : 12; /* bit[8-19] : �δν�һ��ʱ϶AGC RSSIֵ����λ0.125dBm���ϱ���CPU����ֵ���ǿտڵ�RSSIֵ�� */
        unsigned int  reserved_1       : 4;  /* bit[20-23]: ���� */
        unsigned int  curr_gain_3d     : 3;  /* bit[24-26]: �δν�һ��ʱ϶AAGC��λ�ϱ��� */
        unsigned int  reserved_2       : 4;  /* bit[27-30]: ���� */
        unsigned int  agc_fast_flag_3d : 1;  /* bit[31]   : �δν�һ��ʱ϶�����ٲ�����־�ϱ���1��ʾ��ǰΪ���ٲ�����0��ʾ��ǰΪ���ٲ����� */
    } reg;
} GBBP_AAGC_GAIN3_CPU_UNION;
#define GBBP_AAGC_GAIN3_CPU_next_gain_3d_START      (0)
#define GBBP_AAGC_GAIN3_CPU_next_gain_3d_END        (2)
#define GBBP_AAGC_GAIN3_CPU_rssi_3d_START           (8)
#define GBBP_AAGC_GAIN3_CPU_rssi_3d_END             (19)
#define GBBP_AAGC_GAIN3_CPU_curr_gain_3d_START      (24)
#define GBBP_AAGC_GAIN3_CPU_curr_gain_3d_END        (26)
#define GBBP_AAGC_GAIN3_CPU_agc_fast_flag_3d_START  (31)
#define GBBP_AAGC_GAIN3_CPU_agc_fast_flag_3d_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_AAGC_GAIN4_CPU_UNION
 �ṹ˵��  : AAGC_GAIN4_CPU �Ĵ����ṹ���塣��ַƫ����:0x146C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      aagc_gain4_cpu_reg;
    struct
    {
        unsigned int  next_gain_4d     : 3;  /* bit[0-2]  : '���Ľ�һ��ʱ϶AGC�����������档 */
        unsigned int  reserved_0       : 5;  /* bit[3-7]  : ���� */
        unsigned int  rssi_4d          : 12; /* bit[8-19] : '���Ľ�һ��ʱ϶AGC RSSIֵ����λ0.125dBm���ϱ���CPU����ֵ���ǿտڵ�RSSIֵ�� */
        unsigned int  reserved_1       : 4;  /* bit[20-23]: ���� */
        unsigned int  curr_gain_4d     : 3;  /* bit[24-26]: '���Ľ�һ��ʱ϶AAGC��λ�ϱ��� */
        unsigned int  reserved_2       : 4;  /* bit[27-30]: ���� */
        unsigned int  agc_fast_flag_4d : 1;  /* bit[31]   : ���Ľ�һ��ʱ϶�����ٲ�����־�ϱ���1��ʾ��ǰΪ���ٲ�����0��ʾ��ǰΪ���ٲ����� */
    } reg;
} GBBP_AAGC_GAIN4_CPU_UNION;
#define GBBP_AAGC_GAIN4_CPU_next_gain_4d_START      (0)
#define GBBP_AAGC_GAIN4_CPU_next_gain_4d_END        (2)
#define GBBP_AAGC_GAIN4_CPU_rssi_4d_START           (8)
#define GBBP_AAGC_GAIN4_CPU_rssi_4d_END             (19)
#define GBBP_AAGC_GAIN4_CPU_curr_gain_4d_START      (24)
#define GBBP_AAGC_GAIN4_CPU_curr_gain_4d_END        (26)
#define GBBP_AAGC_GAIN4_CPU_agc_fast_flag_4d_START  (31)
#define GBBP_AAGC_GAIN4_CPU_agc_fast_flag_4d_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_CPU_SOFT_RST_UNION
 �ṹ˵��  : ADDR_CPU_SOFT_RST �Ĵ����ṹ���塣��ַƫ����:0x1350����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_cpu_soft_rst_reg;
    struct
    {
        unsigned int  cpu_gcipher_rst          : 1;  /* bit[0]    : �ӽ���ģ����λ�źţ�д1��ģ�鸴λ�� */
        unsigned int  cpu_gmod_rst             : 1;  /* bit[1]    : ���е���ģ����λ�źţ�д1��ģ�鸴λ�� */
        unsigned int  cpu_gulcod_rst           : 1;  /* bit[2]    : ���б���ģ�飨�����б���mapģ�飩��λ�źţ�д1��ģ�鸴λ��Bit2��bit3��ͬ�������б���ģ����ơ� */
        unsigned int  cpu_gulcod_map_rst       : 1;  /* bit[3]    : ���б���ģ����mapģ����λ�źţ�д1��ģ�鸴λ�� */
        unsigned int  cpu_gagc_rst             : 1;  /* bit[4]    : �Զ��������ģ����λ�źţ�д1��ģ�鸴λ�� */
        unsigned int  cpu_gaci_rst             : 1;  /* bit[5]    : ��Ƶ���ģ����λ�źţ�д1��ģ�鸴λ�� */
        unsigned int  cpu_gch_rst              : 1;  /* bit[6]    : �ŵ��˲�ģ����λ�źţ�д1��ģ�鸴λ�� */
        unsigned int  cpu_gdldec_vtb_top_rst   : 1;  /* bit[7]    : ��������ģ����viterbiģ����λ�źţ�д1��ģ�鸴λ��bit7��bit8��bit9��bit10��ͬ������������ģ����ơ� */
        unsigned int  cpu_gdldec_int_dpc_rst   : 1;  /* bit[8]    : ��������ģ����ȥ��֯/��֯��ȥ���/���ģ����λ�źţ�д1��ģ�鸴λ��bit7��bit8��bit9��bit10��ͬ������������ģ����ơ� */
        unsigned int  cpu_gdldec_valpp_ram_rst : 1;  /* bit[9]    : ��������ģ���н����������ֵ�洢/��ȡģ����λ�źţ�д1��ģ�鸴λ��bit7��bit8��bit9��bit10��ͬ������������ģ����ơ� */
        unsigned int  cpu_gdldec_top_rst       : 1;  /* bit[10]   : ��������ģ���г�ȥbit7��bit8��bit9ʣ�µ�����ģ����λ�źţ�д1��ģ�鸴λ��bit7��bit8��bit9��bit10��ͬ������������ģ����ơ� */
        unsigned int  cpu_gdldem_srch_rst      : 1;  /* bit[11]   : ���н��ģ�飨�����������ֺ����н����ز��֣���λ�źţ�д1��ģ�鸴λ�� */
        unsigned int  cpu_gmod_post_rst        : 1;  /* bit[12]   : ���е��ƺ���ģ����λ�źţ�д1��ģ�鸴λ�� */
        unsigned int  cpu_gapc_rst             : 1;  /* bit[13]   : ����APCģ����λ�źţ�д1��ģ�鸴λ�� */
        unsigned int  cpu_gtc_rst              : 1;  /* bit[14]   : GTCģ����λ�źţ�д1��ģ�鸴λ��
                                                                    ע�⣺�ø�λ�ź����ú󣬽��ᵼ��ר���߿غ͹����߿ؾ���λ��0,�� */
        unsigned int  cpu_gtc_timing_rst       : 1;  /* bit[15]   : GTC��ʱģ����λ�źţ�д1��ģ�鸴λ�� */
        unsigned int  cpu_gdldem_prepro_rst    : 1;  /* bit[16]   : ���Ԥ����ģ����λ�źţ�д1��ģ�鸴λ�� */
        unsigned int  cpu_dump_g_rst           : 1;  /* bit[17]   : ����ģ����λ�źţ�д1��ģ�鸴λ�� */
        unsigned int  reserved                 : 14; /* bit[18-31]: ���� */
    } reg;
} GBBP_ADDR_CPU_SOFT_RST_UNION;
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gcipher_rst_START           (0)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gcipher_rst_END             (0)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gmod_rst_START              (1)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gmod_rst_END                (1)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gulcod_rst_START            (2)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gulcod_rst_END              (2)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gulcod_map_rst_START        (3)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gulcod_map_rst_END          (3)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gagc_rst_START              (4)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gagc_rst_END                (4)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gaci_rst_START              (5)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gaci_rst_END                (5)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gch_rst_START               (6)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gch_rst_END                 (6)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gdldec_vtb_top_rst_START    (7)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gdldec_vtb_top_rst_END      (7)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gdldec_int_dpc_rst_START    (8)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gdldec_int_dpc_rst_END      (8)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gdldec_valpp_ram_rst_START  (9)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gdldec_valpp_ram_rst_END    (9)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gdldec_top_rst_START        (10)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gdldec_top_rst_END          (10)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gdldem_srch_rst_START       (11)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gdldem_srch_rst_END         (11)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gmod_post_rst_START         (12)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gmod_post_rst_END           (12)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gapc_rst_START              (13)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gapc_rst_END                (13)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gtc_rst_START               (14)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gtc_rst_END                 (14)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gtc_timing_rst_START        (15)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gtc_timing_rst_END          (15)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gdldem_prepro_rst_START     (16)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_gdldem_prepro_rst_END       (16)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_dump_g_rst_START            (17)
#define GBBP_ADDR_CPU_SOFT_RST_cpu_dump_g_rst_END              (17)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_CPU_CLK_CTRL_UNION
 �ṹ˵��  : ADDR_CPU_CLK_CTRL �Ĵ����ṹ���塣��ַƫ����:0x1354����ֵ:0x00017FFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_cpu_clk_ctrl_reg;
    struct
    {
        unsigned int  cpu_gcipher_clk_ctrl          : 1;  /* bit[0]    : �ӽ���ģ��CPU����ʱ����Чָʾ��1��ʾ��ʱ�ӣ�0��ʾû��ʱ�ӡ� */
        unsigned int  cpu_gmod_clk_ctrl             : 1;  /* bit[1]    : ���е���ģ��CPU����ʱ����Чָʾ��1��ʾ��ʱ�ӣ�0��ʾû��ʱ�ӡ� */
        unsigned int  cpu_gulcod_clk_ctrl           : 1;  /* bit[2]    : ���б���ģ�飨�������б���mapģ�飩CPU����ʱ����Чָʾ��1��ʾ��ʱ�ӣ�0��ʾû��ʱ�ӡ�bit2��bit3�������б���ģ�顣 */
        unsigned int  cpu_gulcod_map_clk_ctrl       : 1;  /* bit[3]    : ���б���mapģ��CPU����ʱ����Чָʾ��1��ʾ��ʱ�ӣ�0��ʾû��ʱ�ӡ� */
        unsigned int  cpu_gagc_clk_ctrl             : 1;  /* bit[4]    : �Զ��������ģ��CPU����ʱ����Чָʾ��1��ʾ��ʱ�ӣ�0��ʾû��ʱ�ӡ� */
        unsigned int  cpu_gaci_clk_ctrl             : 1;  /* bit[5]    : ��Ƶ���ģ��CPU����ʱ����Чָʾ��1��ʾ��ʱ�ӣ�0��ʾû��ʱ�ӡ� */
        unsigned int  cpu_gch_clk_ctrl              : 1;  /* bit[6]    : �ŵ��˲�Ī��CPU����ʱ����Чָʾ��1��ʾ��ʱ�ӣ�0��ʾû��ʱ�ӡ� */
        unsigned int  cpu_gdldec_vtb_top_clk_ctrl   : 1;  /* bit[7]    : ��������ģ���е�viterbiģ��CPU����ʱ����Чָʾ��1��ʾ��ʱ�ӣ�0��ʾû��ʱ�ӡ�bit7��bit8��bit9��bit10������������ģ�顣 */
        unsigned int  cpu_gdldec_int_dpc_clk_ctrl   : 1;  /* bit[8]    : ��������ģ���еĽ�֯/ȥ��֯�����/ȥ���ģ��CPU����ʱ����Чָʾ��1��ʾ��ʱ�ӣ�0��ʾû��ʱ�ӡ� */
        unsigned int  cpu_gdldec_valpp_ram_clk_ctrl : 1;  /* bit[9]    : ��������ģ���еĽ����������ֵ�洢/��ȡģ��CPU����ʱ����Чָʾ��1��ʾ��ʱ�ӣ�0��ʾû��ʱ�ӡ� */
        unsigned int  cpu_gdldec_top_clk_ctrl       : 1;  /* bit[10]   : ��������ģ�����bit7��bit8��bit9ʣ��ģ���CPU����ʱ����Чָʾ��1��ʾ��ʱ�ӣ�0��ʾû��ʱ�ӡ� */
        unsigned int  cpu_gdldem_srch_clk_ctrl      : 1;  /* bit[11]   : ���н��ģ�飨�����������ֺ����н����ز��֣�CPU����ʱ����Чָʾ��1��ʾ��ʱ�ӣ�0��ʾû��ʱ�ӡ� */
        unsigned int  cpu_gmod_post_clk_ctrl        : 1;  /* bit[12]   : ���е��ƺ���ģ��CPU����ʱ����Чָʾ��1��ʾ��ʱ�ӣ�0��ʾû��ʱ�ӡ� */
        unsigned int  cpu_gapc_clk_ctrl             : 1;  /* bit[13]   : ����APCģ��CPU����ʱ����Чָʾ��1��ʾ��ʱ�ӣ�0��ʾû��ʱ�ӡ� */
        unsigned int  cpu_gtc_clk_ctrl              : 1;  /* bit[14]   : GTCģ��CPU����ʱ����Чָʾ��1��ʾ��ʱ�ӣ�0��ʾû��ʱ�ӡ� */
        unsigned int  reserved_0                    : 1;  /* bit[15]   : ���� */
        unsigned int  cpu_gdldem_prepro_clk_ctrl    : 1;  /* bit[16]   : ���Ԥ����ģ��CPU����ʱ����Чָʾ��1��ʾ��ʱ�ӣ�0��ʾû��ʱ�ӡ� */
        unsigned int  reserved_1                    : 15; /* bit[17-31]: ���� */
    } reg;
} GBBP_ADDR_CPU_CLK_CTRL_UNION;
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gcipher_clk_ctrl_START           (0)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gcipher_clk_ctrl_END             (0)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gmod_clk_ctrl_START              (1)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gmod_clk_ctrl_END                (1)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gulcod_clk_ctrl_START            (2)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gulcod_clk_ctrl_END              (2)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gulcod_map_clk_ctrl_START        (3)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gulcod_map_clk_ctrl_END          (3)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gagc_clk_ctrl_START              (4)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gagc_clk_ctrl_END                (4)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gaci_clk_ctrl_START              (5)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gaci_clk_ctrl_END                (5)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gch_clk_ctrl_START               (6)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gch_clk_ctrl_END                 (6)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gdldec_vtb_top_clk_ctrl_START    (7)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gdldec_vtb_top_clk_ctrl_END      (7)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gdldec_int_dpc_clk_ctrl_START    (8)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gdldec_int_dpc_clk_ctrl_END      (8)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gdldec_valpp_ram_clk_ctrl_START  (9)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gdldec_valpp_ram_clk_ctrl_END    (9)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gdldec_top_clk_ctrl_START        (10)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gdldec_top_clk_ctrl_END          (10)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gdldem_srch_clk_ctrl_START       (11)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gdldem_srch_clk_ctrl_END         (11)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gmod_post_clk_ctrl_START         (12)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gmod_post_clk_ctrl_END           (12)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gapc_clk_ctrl_START              (13)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gapc_clk_ctrl_END                (13)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gtc_clk_ctrl_START               (14)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gtc_clk_ctrl_END                 (14)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gdldem_prepro_clk_ctrl_START     (16)
#define GBBP_ADDR_CPU_CLK_CTRL_cpu_gdldem_prepro_clk_ctrl_END       (16)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_CPU_CLK_MODE_SEL_UNION
 �ṹ˵��  : ADDR_CPU_CLK_MODE_SEL �Ĵ����ṹ���塣��ַƫ����:0x1358����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_cpu_clk_mode_sel_reg;
    struct
    {
        unsigned int  cpu_gcipher_ckg_mode_sel          : 1;  /* bit[0]    : �ӽ���ģ���Զ�ʱ���ſ�orCPUʱ���ſ�ѡ���źţ�1��ʾCPU�����ſأ�0��ʾ�Զ�ʱ���ſء� */
        unsigned int  cpu_gmod_ckg_mode_sel             : 1;  /* bit[1]    : ���е���ģ���Զ�ʱ���ſ�orCPUʱ���ſ�ѡ���źţ�1��ʾCPU�����ſأ�0��ʾ�Զ�ʱ���ſء� */
        unsigned int  cpu_gulcod_ckg_mode_sel           : 1;  /* bit[2]    : ���б��루����map����ģ�飩ģ���Զ�ʱ���ſ�orCPUʱ���ſ�ѡ���źţ�1��ʾCPU�����ſأ�0��ʾ�Զ�ʱ���ſء�bit2��bit3�������б���ģ�顣 */
        unsigned int  cpu_gulcod_map_ckg_mode_sel       : 1;  /* bit[3]    : ���б���map����ģ���Զ�ʱ���ſ�orCPUʱ���ſ�ѡ���źţ�1��ʾCPU�����ſأ�0��ʾ�Զ�ʱ���ſء� */
        unsigned int  cpu_gagc_ckg_mode_sel             : 1;  /* bit[4]    : �Զ��������ģ���Զ�ʱ���ſ�orCPUʱ���ſ�ѡ���źţ�1��ʾCPU�����ſأ�0��ʾ�Զ�ʱ���ſء� */
        unsigned int  cpu_gaci_ckg_mode_sel             : 1;  /* bit[5]    : ��Ƶ���ģ���Զ�ʱ���ſ�orCPUʱ���ſ�ѡ���źţ�1��ʾCPU�����ſأ�0��ʾ�Զ�ʱ���ſء� */
        unsigned int  cpu_gch_ckg_mode_sel              : 1;  /* bit[6]    : �ŵ��˲�ģ���Զ�ʱ���ſ�orCPUʱ���ſ�ѡ���źţ�1��ʾCPU�����ſأ�0��ʾ�Զ�ʱ���ſء� */
        unsigned int  cpu_gdldec_vtb_top_ckg_mode_sel   : 1;  /* bit[7]    : ��������ģ����viterbiģ���Զ�ʱ���ſ�orCPUʱ���ſ�ѡ���źţ�1��ʾCPU�����ſأ�0��ʾ�Զ�ʱ���ſء�bit7��bit8��bit9��bit10������������ģ����ơ� */
        unsigned int  cpu_gdldec_int_dpc_ckg_mode_sel   : 1;  /* bit[8]    : ��������ģ���н�֯/ȥ��֯�����/ȥ���ģ���Զ�ʱ���ſ�orCPUʱ���ſ�ѡ���źţ�1��ʾCPU�����ſأ�0��ʾ�Զ�ʱ���ſء� */
        unsigned int  cpu_gdldec_valpp_ram_ckg_mode_sel : 1;  /* bit[9]    : ��������ģ���н����������ֵ�洢/��ȡģ���Զ�ʱ���ſ�orCPUʱ���ſ�ѡ���źţ�1��ʾCPU�����ſأ�0��ʾ�Զ�ʱ���ſء� */
        unsigned int  cpu_gdldec_top_ckg_mode_sel       : 1;  /* bit[10]   : ��������ģ���г���bit7��bit8��bit9ʣ�µ�ģ���Զ�ʱ���ſ�orCPUʱ���ſ�ѡ���źţ�1��ʾCPU�����ſأ�0��ʾ�Զ�ʱ���ſء� */
        unsigned int  cpu_gdldem_srch_ckg_mode_sel      : 1;  /* bit[11]   : ���н���������������ֺͽ��������ز��֣�ģ���Զ�ʱ���ſ�orCPUʱ���ſ�ѡ���źţ�1��ʾCPU�����ſأ�0��ʾ�Զ�ʱ���ſء� */
        unsigned int  reserved                          : 20; /* bit[12-31]: ���� */
    } reg;
} GBBP_ADDR_CPU_CLK_MODE_SEL_UNION;
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gcipher_ckg_mode_sel_START           (0)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gcipher_ckg_mode_sel_END             (0)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gmod_ckg_mode_sel_START              (1)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gmod_ckg_mode_sel_END                (1)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gulcod_ckg_mode_sel_START            (2)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gulcod_ckg_mode_sel_END              (2)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gulcod_map_ckg_mode_sel_START        (3)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gulcod_map_ckg_mode_sel_END          (3)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gagc_ckg_mode_sel_START              (4)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gagc_ckg_mode_sel_END                (4)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gaci_ckg_mode_sel_START              (5)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gaci_ckg_mode_sel_END                (5)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gch_ckg_mode_sel_START               (6)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gch_ckg_mode_sel_END                 (6)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gdldec_vtb_top_ckg_mode_sel_START    (7)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gdldec_vtb_top_ckg_mode_sel_END      (7)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gdldec_int_dpc_ckg_mode_sel_START    (8)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gdldec_int_dpc_ckg_mode_sel_END      (8)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gdldec_valpp_ram_ckg_mode_sel_START  (9)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gdldec_valpp_ram_ckg_mode_sel_END    (9)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gdldec_top_ckg_mode_sel_START        (10)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gdldec_top_ckg_mode_sel_END          (10)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gdldem_srch_ckg_mode_sel_START       (11)
#define GBBP_ADDR_CPU_CLK_MODE_SEL_cpu_gdldem_srch_ckg_mode_sel_END         (11)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_CPU_AUTO_CLK_BYPASS_UNION
 �ṹ˵��  : ADDR_CPU_AUTO_CLK_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x135C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_cpu_auto_clk_bypass_reg;
    struct
    {
        unsigned int  cpu_gcipher_ckg_bypass          : 1;  /* bit[0]    : �ӽ���ģ��ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء� */
        unsigned int  cpu_gmod_ckg_bypass             : 1;  /* bit[1]    : ���е���ģ��ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء� */
        unsigned int  cpu_gulcod_ckg_bypass           : 1;  /* bit[2]    : ���б���ģ�飨��ȥmap����ģ�飩ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء�bit2��bit3�������б���ģ�顣 */
        unsigned int  cpu_gulcod_map_ckg_bypass       : 1;  /* bit[3]    : ���б���ģ����mapģ��ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء� */
        unsigned int  cpu_gagc_ckg_bypass             : 1;  /* bit[4]    : �Զ��������ģ��ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء� */
        unsigned int  cpu_gaci_ckg_bypass             : 1;  /* bit[5]    : ��Ƶ���ģ��ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء� */
        unsigned int  cpu_gch_ckg_bypass              : 1;  /* bit[6]    : �ŵ��˲�ģ��ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء� */
        unsigned int  cpu_gdldec_vtb_top_ckg_bypass   : 1;  /* bit[7]    : ��������ģ����viterbiģ��ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء�bit7��bit8��bit9��bit10������������ģ�顣 */
        unsigned int  cpu_gdldec_int_dpc_ckg_bypass   : 1;  /* bit[8]    : ��������ģ���н�֯/ȥ���ʡ����/ȥ���ģ��ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء� */
        unsigned int  cpu_gdldec_valpp_ram_ckg_bypass : 1;  /* bit[9]    : ��������ģ���н����������ֵ�洢/��ȡģ��ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء� */
        unsigned int  cpu_gdldec_top_ckg_bypass       : 1;  /* bit[10]   : ��������ģ���г���bit��bit8��bit9ʣ�µ�ģ��ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء� */
        unsigned int  cpu_gdldem_srch_ckg_bypass      : 1;  /* bit[11]   : ���н���������������ֺ����н����ز��֣�ģ��ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء� */
        unsigned int  cpu_gmod_post_ckg_bypass        : 1;  /* bit[12]   : ���е��ƺ���ģ��ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء� */
        unsigned int  cpu_gapc_ckg_bypass             : 1;  /* bit[13]   : ����APCģ��ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء� */
        unsigned int  cpu_gtc_ckg_bypass              : 1;  /* bit[14]   : GTCģ��ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء� */
        unsigned int  reserved_0                      : 1;  /* bit[15]   : ���� */
        unsigned int  cpu_gdldem_prepro_ckg_bypass    : 1;  /* bit[16]   : ���н��Ԥ����ģ��ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء� */
        unsigned int  dump_clkgate_bypass_g           : 1;  /* bit[17]   : ����ģ��ʱ���ſع���bypass��1��ʾʱ�ӳ�����0��ʾʹ���Զ�ʱ���ſػ���CPU����ʱ���ſء� */
        unsigned int  reserved_1                      : 14; /* bit[18-31]: ���� */
    } reg;
} GBBP_ADDR_CPU_AUTO_CLK_BYPASS_UNION;
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gcipher_ckg_bypass_START           (0)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gcipher_ckg_bypass_END             (0)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gmod_ckg_bypass_START              (1)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gmod_ckg_bypass_END                (1)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gulcod_ckg_bypass_START            (2)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gulcod_ckg_bypass_END              (2)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gulcod_map_ckg_bypass_START        (3)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gulcod_map_ckg_bypass_END          (3)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gagc_ckg_bypass_START              (4)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gagc_ckg_bypass_END                (4)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gaci_ckg_bypass_START              (5)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gaci_ckg_bypass_END                (5)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gch_ckg_bypass_START               (6)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gch_ckg_bypass_END                 (6)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gdldec_vtb_top_ckg_bypass_START    (7)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gdldec_vtb_top_ckg_bypass_END      (7)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gdldec_int_dpc_ckg_bypass_START    (8)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gdldec_int_dpc_ckg_bypass_END      (8)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gdldec_valpp_ram_ckg_bypass_START  (9)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gdldec_valpp_ram_ckg_bypass_END    (9)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gdldec_top_ckg_bypass_START        (10)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gdldec_top_ckg_bypass_END          (10)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gdldem_srch_ckg_bypass_START       (11)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gdldem_srch_ckg_bypass_END         (11)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gmod_post_ckg_bypass_START         (12)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gmod_post_ckg_bypass_END           (12)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gapc_ckg_bypass_START              (13)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gapc_ckg_bypass_END                (13)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gtc_ckg_bypass_START               (14)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gtc_ckg_bypass_END                 (14)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gdldem_prepro_ckg_bypass_START     (16)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_cpu_gdldem_prepro_ckg_bypass_END       (16)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_dump_clkgate_bypass_g_START            (17)
#define GBBP_ADDR_CPU_AUTO_CLK_BYPASS_dump_clkgate_bypass_g_END              (17)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_GTC_CFG_UNION
 �ṹ˵��  : CPU_GTC_CFG �Ĵ����ṹ���塣��ַƫ����:0x1360����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_gtc_cfg_reg;
    struct
    {
        unsigned int  gtc_page_switch_en_imi   : 1;  /* bit[0]   : 0�����л�ָ��RAMҳ��1��ƹ���л�ָ��RAMҳ����λ���һ������ʱӦ���л�ָ��ҳ�� */
        unsigned int  cpu_gtc_start_imi        : 1;  /* bit[1]   : д1����ָ��ҳִ�У��ڲ�����һ��104Mʱ�����壬�����㣬д0�����塣 */
        unsigned int  gtc_auto_run_imi         : 1;  /* bit[2]   : GTCָ����TDMA֡ͷ���Զ�ִ��ʹ�ܣ�Ĭ��Ϊ0�� */
        unsigned int  cpu_gtc_hold_page        : 1;  /* bit[3]   : 1��ʾ�����޸�����ִ�е�GTCָ��ҳ����Ҫ�޸�ʱ������1���޸���ɺ���0�� */
        unsigned int  gtc_pro_en_imi           : 1;  /* bit[4]   : GTCģ�鹤��ʹ���źţ�������Ϊ���ź�Ϊ�ߣ�Ȼ��������GTC�� */
        unsigned int  reserved_0               : 3;  /* bit[5-7] : ���� */
        unsigned int  cpu_drx_test_mode_en_imi : 1;  /* bit[8]   : 1��ʾDRX����ģʽʹ�ܣ���ʱGTCʱ��Ӧ���رգ�����DRX���Ѻ�Ķ�ʱά������ıȶԡ�����ʹ���¸��ź�Ӧ�ñ���0�������á� */
        unsigned int  reserved_1               : 23; /* bit[9-31]: ���� */
    } reg;
} GBBP_CPU_GTC_CFG_UNION;
#define GBBP_CPU_GTC_CFG_gtc_page_switch_en_imi_START    (0)
#define GBBP_CPU_GTC_CFG_gtc_page_switch_en_imi_END      (0)
#define GBBP_CPU_GTC_CFG_cpu_gtc_start_imi_START         (1)
#define GBBP_CPU_GTC_CFG_cpu_gtc_start_imi_END           (1)
#define GBBP_CPU_GTC_CFG_gtc_auto_run_imi_START          (2)
#define GBBP_CPU_GTC_CFG_gtc_auto_run_imi_END            (2)
#define GBBP_CPU_GTC_CFG_cpu_gtc_hold_page_START         (3)
#define GBBP_CPU_GTC_CFG_cpu_gtc_hold_page_END           (3)
#define GBBP_CPU_GTC_CFG_gtc_pro_en_imi_START            (4)
#define GBBP_CPU_GTC_CFG_gtc_pro_en_imi_END              (4)
#define GBBP_CPU_GTC_CFG_cpu_drx_test_mode_en_imi_START  (8)
#define GBBP_CPU_GTC_CFG_cpu_drx_test_mode_en_imi_END    (8)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_STATE_RPT_UNION
 �ṹ˵��  : GTC_STATE_RPT �Ĵ����ṹ���塣��ַƫ����:0x1374����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gtc_state_rpt_reg;
    struct
    {
        unsigned int  gtc_idle           : 1;  /* bit[0]   : 1����ʾGTCû��GTCָ��ִ�У�0��ʾGTC����ִ�У������á� */
        unsigned int  gtc_wait           : 1;  /* bit[1]   : 1����ʾGTC����hold����start״̬�������á� */
        unsigned int  gtc_run            : 1;  /* bit[2]   : 1����ʾGTC����run����״̬�������á� */
        unsigned int  reserved_0         : 1;  /* bit[3]   : ���� */
        unsigned int  gtc_page_switch_en : 1;  /* bit[4]   : GTCָ��RAMƹ���л�ʹ���ϱ��������á� */
        unsigned int  gtc_page_sel       : 1;  /* bit[5]   : ��ǰGTCָ��RAM��ƹ�ұ�־�ϱ��������á� */
        unsigned int  reserved_1         : 26; /* bit[6-31]: ���� */
    } reg;
} GBBP_GTC_STATE_RPT_UNION;
#define GBBP_GTC_STATE_RPT_gtc_idle_START            (0)
#define GBBP_GTC_STATE_RPT_gtc_idle_END              (0)
#define GBBP_GTC_STATE_RPT_gtc_wait_START            (1)
#define GBBP_GTC_STATE_RPT_gtc_wait_END              (1)
#define GBBP_GTC_STATE_RPT_gtc_run_START             (2)
#define GBBP_GTC_STATE_RPT_gtc_run_END               (2)
#define GBBP_GTC_STATE_RPT_gtc_page_switch_en_START  (4)
#define GBBP_GTC_STATE_RPT_gtc_page_switch_en_END    (4)
#define GBBP_GTC_STATE_RPT_gtc_page_sel_START        (5)
#define GBBP_GTC_STATE_RPT_gtc_page_sel_END          (5)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_FRM_OFFSET_RPT_UNION
 �ṹ˵��  : GTC_FRM_OFFSET_RPT �Ĵ����ṹ���塣��ַƫ����:0x137C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gtc_frm_offset_rpt_reg;
    struct
    {
        unsigned int  gtc_frm_offset : 13; /* bit[0-12] : TDMA��ʱ��TimeBaseʱ��ƫ���λqb����frm_offsetΪN����TimeBase������N-1��GTC�ڲ�������frac_cnt������95ʱ����һ��TDMA֡�ż�1�������á� */
        unsigned int  reserved       : 19; /* bit[13-31]: ���� */
    } reg;
} GBBP_GTC_FRM_OFFSET_RPT_UNION;
#define GBBP_GTC_FRM_OFFSET_RPT_gtc_frm_offset_START  (0)
#define GBBP_GTC_FRM_OFFSET_RPT_gtc_frm_offset_END    (12)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_FRM_IT_OFFSET_RPT_UNION
 �ṹ˵��  : GTC_FRM_IT_OFFSET_RPT �Ĵ����ṹ���塣��ַƫ����:0x1380����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gtc_frm_it_offset_rpt_reg;
    struct
    {
        unsigned int  gtc_frm_it_offset : 13; /* bit[0-12] : ֡�ж���TimeBaseʱ��ƫ���λqb�������á� */
        unsigned int  reserved          : 19; /* bit[13-31]: ���� */
    } reg;
} GBBP_GTC_FRM_IT_OFFSET_RPT_UNION;
#define GBBP_GTC_FRM_IT_OFFSET_RPT_gtc_frm_it_offset_START  (0)
#define GBBP_GTC_FRM_IT_OFFSET_RPT_gtc_frm_it_offset_END    (12)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_GTC_T1_T2_T3_CNG_UNION
 �ṹ˵��  : CPU_GTC_T1_T2_T3_CNG �Ĵ����ṹ���塣��ַƫ����:0x1388����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_gtc_t1_t2_t3_cng_reg;
    struct
    {
        unsigned int  cpu_gtc_t1_cnt : 11; /* bit[0-10] : ����֡��ά�������е�T1��ʼֵ���ò���ֵ��cpu_gtc_t1_cnt,cpu_gtc_t3_cnt,cpu_gtc_fn_low,cpu_gtc_fn_highһ������GTC�ڲ�֡��ά���Ĵ����ĳ�ʼ������GTC��TDMA֡�߽紦��Ч������Ӧ����Ϊ��һ֡��֡�ŵ�T1ֵ�� */
        unsigned int  reserved_0     : 5;  /* bit[11-15]: ���� */
        unsigned int  cpu_gtc_t2_cnt : 5;  /* bit[16-20]: ����֡��ά�������е�T2��ʼֵ���ò���ֵ��cpu_gtc_t2_cnt,cpu_gtc_t3_cnt,cpu_gtc_fn_low,cpu_gtc_fn_highһ������GTC�ڲ�֡��ά���Ĵ����ĳ�ʼ������GTC��TDMA֡�߽紦��Ч������Ӧ����Ϊ��һ֡��֡�ŵ�T1ֵ�� */
        unsigned int  reserved_1     : 3;  /* bit[21-23]: ���� */
        unsigned int  cpu_gtc_t3_cnt : 6;  /* bit[24-29]: ����֡��ά�������е�T2��ʼֵ���ò���ֵ��cpu_gtc_t1_cnt,cpu_gtc_t2_cnt,cpu_gtc_fn_low,cpu_gtc_fn_highһ������GTC�ڲ�֡��ά���Ĵ����ĳ�ʼ������GTC��TDMA֡�߽紦��Ч������Ӧ����Ϊ��һ֡��֡�ŵ�T1ֵ�� */
        unsigned int  reserved_2     : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_CPU_GTC_T1_T2_T3_CNG_UNION;
#define GBBP_CPU_GTC_T1_T2_T3_CNG_cpu_gtc_t1_cnt_START  (0)
#define GBBP_CPU_GTC_T1_T2_T3_CNG_cpu_gtc_t1_cnt_END    (10)
#define GBBP_CPU_GTC_T1_T2_T3_CNG_cpu_gtc_t2_cnt_START  (16)
#define GBBP_CPU_GTC_T1_T2_T3_CNG_cpu_gtc_t2_cnt_END    (20)
#define GBBP_CPU_GTC_T1_T2_T3_CNG_cpu_gtc_t3_cnt_START  (24)
#define GBBP_CPU_GTC_T1_T2_T3_CNG_cpu_gtc_t3_cnt_END    (29)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_T1_T2_T3_RPT_CPU_UNION
 �ṹ˵��  : GTC_T1_T2_T3_RPT_CPU �Ĵ����ṹ���塣��ַƫ����:0x138C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gtc_t1_t2_t3_rpt_cpu_reg;
    struct
    {
        unsigned int  gtc_t1_cnt : 11; /* bit[0-10] : GTC�ڲ�ά����T1�������ϱ� */
        unsigned int  reserved_0 : 5;  /* bit[11-15]: ���� */
        unsigned int  gtc_t2_cnt : 5;  /* bit[16-20]: GTC�ڲ�ά����T2�������ϱ� */
        unsigned int  reserved_1 : 3;  /* bit[21-23]: ���� */
        unsigned int  gtc_t3_cnt : 6;  /* bit[24-29]: GTC�ڲ�ά����T3�������ϱ� */
        unsigned int  reserved_2 : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_GTC_T1_T2_T3_RPT_CPU_UNION;
#define GBBP_GTC_T1_T2_T3_RPT_CPU_gtc_t1_cnt_START  (0)
#define GBBP_GTC_T1_T2_T3_RPT_CPU_gtc_t1_cnt_END    (10)
#define GBBP_GTC_T1_T2_T3_RPT_CPU_gtc_t2_cnt_START  (16)
#define GBBP_GTC_T1_T2_T3_RPT_CPU_gtc_t2_cnt_END    (20)
#define GBBP_GTC_T1_T2_T3_RPT_CPU_gtc_t3_cnt_START  (24)
#define GBBP_GTC_T1_T2_T3_RPT_CPU_gtc_t3_cnt_END    (29)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_GTC_FRM_OFFSET_CFG_UNION
 �ṹ˵��  : CPU_GTC_FRM_OFFSET_CFG �Ĵ����ṹ���塣��ַƫ����:0x1390����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_gtc_frm_offset_cfg_reg;
    struct
    {
        unsigned int  cpu_gtc_frm_offset           : 13; /* bit[0-12] : CPU���õ�gtc_frm_offset������ */
        unsigned int  reserved_0                   : 3;  /* bit[13-15]: ���� */
        unsigned int  cpu_gtc_frm_it_offset        : 13; /* bit[16-28]: CPU���õ�gtc_frm_it_offset������ */
        unsigned int  reserved_1                   : 2;  /* bit[29-30]: ���� */
        unsigned int  cpu_gtc_frm_offset_wr_en_imi : 1;  /* bit[31]   : cpu_gtc_frm_offset
                                                                        cpu_gtc_frm_it_offset
                                                                        ������Чָʾ�źţ��߼������㡣 */
    } reg;
} GBBP_CPU_GTC_FRM_OFFSET_CFG_UNION;
#define GBBP_CPU_GTC_FRM_OFFSET_CFG_cpu_gtc_frm_offset_START            (0)
#define GBBP_CPU_GTC_FRM_OFFSET_CFG_cpu_gtc_frm_offset_END              (12)
#define GBBP_CPU_GTC_FRM_OFFSET_CFG_cpu_gtc_frm_it_offset_START         (16)
#define GBBP_CPU_GTC_FRM_OFFSET_CFG_cpu_gtc_frm_it_offset_END           (28)
#define GBBP_CPU_GTC_FRM_OFFSET_CFG_cpu_gtc_frm_offset_wr_en_imi_START  (31)
#define GBBP_CPU_GTC_FRM_OFFSET_CFG_cpu_gtc_frm_offset_wr_en_imi_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_GTC_FN_CNG_UNION
 �ṹ˵��  : CPU_GTC_FN_CNG �Ĵ����ṹ���塣��ַƫ����:0x1394����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_gtc_fn_cng_reg;
    struct
    {
        unsigned int  cpu_gtc_fn_low       : 11; /* bit[0-10] : CPU����TDMA֡�ŵ�λ0~26*51-1ѭ��������CPU���ú���֡�߽紦��Ч������Ӧ����Ϊ��һ֡��֡�š� */
        unsigned int  reserved_0           : 5;  /* bit[11-15]: ���� */
        unsigned int  cpu_gtc_fn_high      : 11; /* bit[16-26]: CPU����TDMA֡�Ÿ�λ0~2047����λ�����󣬸�λ��1��CPU���ú���֡�߽紦��Ч������Ӧ����Ϊ��һ֡��֡�š� */
        unsigned int  reserved_1           : 4;  /* bit[27-30]: ���� */
        unsigned int  cpu_gtc_fn_wr_en_imi : 1;  /* bit[31]   : ֡�ų�ʼ���źţ�1��Ч���߼������㡣��T1��T2��T3��fn_low��fn_high����д�����źŲſ�����1�� */
    } reg;
} GBBP_CPU_GTC_FN_CNG_UNION;
#define GBBP_CPU_GTC_FN_CNG_cpu_gtc_fn_low_START        (0)
#define GBBP_CPU_GTC_FN_CNG_cpu_gtc_fn_low_END          (10)
#define GBBP_CPU_GTC_FN_CNG_cpu_gtc_fn_high_START       (16)
#define GBBP_CPU_GTC_FN_CNG_cpu_gtc_fn_high_END         (26)
#define GBBP_CPU_GTC_FN_CNG_cpu_gtc_fn_wr_en_imi_START  (31)
#define GBBP_CPU_GTC_FN_CNG_cpu_gtc_fn_wr_en_imi_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_FN_RPT_UNION
 �ṹ˵��  : GTC_FN_RPT �Ĵ����ṹ���塣��ַƫ����:0x1398����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gtc_fn_rpt_reg;
    struct
    {
        unsigned int  gtc_fn_low  : 11; /* bit[0-10] : GTC��ʱ֡�ŵ�λ�� */
        unsigned int  reserved_0  : 5;  /* bit[11-15]: ���� */
        unsigned int  gtc_fn_high : 11; /* bit[16-26]: GTC��ʱ֡�Ÿ�λ�� */
        unsigned int  reserved_1  : 5;  /* bit[27-31]: ���� */
    } reg;
} GBBP_GTC_FN_RPT_UNION;
#define GBBP_GTC_FN_RPT_gtc_fn_low_START   (0)
#define GBBP_GTC_FN_RPT_gtc_fn_low_END     (10)
#define GBBP_GTC_FN_RPT_gtc_fn_high_START  (16)
#define GBBP_GTC_FN_RPT_gtc_fn_high_END    (26)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_QB_RPT_UNION
 �ṹ˵��  : GTC_QB_RPT �Ĵ����ṹ���塣��ַƫ����:0x139C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gtc_qb_rpt_reg;
    struct
    {
        unsigned int  gtc_tdma_qb_imi  : 13; /* bit[0-12] : ��ǰʱ��TDMA��QB����ֵ��0~4999�� */
        unsigned int  reserved_0       : 3;  /* bit[13-15]: ���� */
        unsigned int  gtc_timebase_imi : 13; /* bit[16-28]: ����ʱ��QB�ϱ�����Χ��0~4999����Ӧһ֡�ĳ��ȣ���ֵֻ�븴λʱ���йأ������á� */
        unsigned int  reserved_1       : 3;  /* bit[29-31]: ���� */
    } reg;
} GBBP_GTC_QB_RPT_UNION;
#define GBBP_GTC_QB_RPT_gtc_tdma_qb_imi_START   (0)
#define GBBP_GTC_QB_RPT_gtc_tdma_qb_imi_END     (12)
#define GBBP_GTC_QB_RPT_gtc_timebase_imi_START  (16)
#define GBBP_GTC_QB_RPT_gtc_timebase_imi_END    (28)


/*****************************************************************************
 �ṹ��    : GBBP_TIMEBASE_RPT_UNION
 �ṹ˵��  : TIMEBASE_RPT �Ĵ����ṹ���塣��ַƫ����:0x13A8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      timebase_rpt_reg;
    struct
    {
        unsigned int  gtc_timebase_imi    : 13; /* bit[0-12] : ����ʱ��QB�ϱ�����Χ��0~4999����Ӧһ֡�ĳ��ȣ���ֵֻ�븴λʱ���йأ������á� */
        unsigned int  reserved_0          : 3;  /* bit[13-15]: ���� */
        unsigned int  gtc_timebase_fn_low : 11; /* bit[16-26]: ����ʱ��֡���ϱ�����ֵ�仯ʱ����gtc_timebase_qbΪ4999����������Χ0~26*51-1�������á� */
        unsigned int  reserved_1          : 5;  /* bit[27-31]: ���� */
    } reg;
} GBBP_TIMEBASE_RPT_UNION;
#define GBBP_TIMEBASE_RPT_gtc_timebase_imi_START     (0)
#define GBBP_TIMEBASE_RPT_gtc_timebase_imi_END       (12)
#define GBBP_TIMEBASE_RPT_gtc_timebase_fn_low_START  (16)
#define GBBP_TIMEBASE_RPT_gtc_timebase_fn_low_END    (26)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_BLER_BER_CLR_UNION
 �ṹ˵��  : CPU_BLER_BER_CLR �Ĵ����ṹ���塣��ַƫ����:0x1300����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_bler_ber_clr_reg;
    struct
    {
        unsigned int  cpu_bler_clr_imi : 1;  /* bit[0]   : ���������ϱ�BLER�����źţ������źţ�cpu��1�߼������� */
        unsigned int  reserved_0       : 3;  /* bit[1-3] : ���� */
        unsigned int  cpu_ber_clr_imi  : 1;  /* bit[4]   : ���������ϱ�BER�����źţ������źţ�cpu��1���߼������� */
        unsigned int  reserved_1       : 3;  /* bit[5-7] : ���� */
        unsigned int  cpu_bler_mode    : 1;  /* bit[8]   : BLERͳ��ģʽ���ƣ�0��ʾÿ������CRC���������BLERͳ�ƣ�����HEAD��DATA��ͳ�ƣ�
                                                           1��ʾֻͳ��ÿ��DATA������CRC���BLERֵ */
        unsigned int  reserved_2       : 23; /* bit[9-31]: ���� */
    } reg;
} GBBP_CPU_BLER_BER_CLR_UNION;
#define GBBP_CPU_BLER_BER_CLR_cpu_bler_clr_imi_START  (0)
#define GBBP_CPU_BLER_BER_CLR_cpu_bler_clr_imi_END    (0)
#define GBBP_CPU_BLER_BER_CLR_cpu_ber_clr_imi_START   (4)
#define GBBP_CPU_BLER_BER_CLR_cpu_ber_clr_imi_END     (4)
#define GBBP_CPU_BLER_BER_CLR_cpu_bler_mode_START     (8)
#define GBBP_CPU_BLER_BER_CLR_cpu_bler_mode_END       (8)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_AMR_CB_INDEX_UNION
 �ṹ˵��  : CPU_AMR_CB_INDEX �Ĵ����ṹ���塣��ַƫ����:0x1304����ֵ:0x0F0E0D0C�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_amr_cb_index_reg;
    struct
    {
        unsigned int  cpu_amr0_cb_index : 7;  /* bit[0-6]  : AMR�����������codec_mode=00��Ӧ��AMR����֡cb_index */
        unsigned int  reserved_0        : 1;  /* bit[7]    : ���� */
        unsigned int  cpu_amr1_cb_index : 7;  /* bit[8-14] : AMR�����������codec_mode=01��Ӧ��AMR����֡cb_index */
        unsigned int  reserved_1        : 1;  /* bit[15]   : ���� */
        unsigned int  cpu_amr2_cb_index : 7;  /* bit[16-22]: AMR�����������codec_mode=10��Ӧ��AMR����֡cb_index */
        unsigned int  reserved_2        : 1;  /* bit[23]   : ���� */
        unsigned int  cpu_amr3_cb_index : 7;  /* bit[24-30]: AMR�����������codec_mode=11��Ӧ��AMR����֡cb_index */
        unsigned int  reserved_3        : 1;  /* bit[31]   : ���� */
    } reg;
} GBBP_CPU_AMR_CB_INDEX_UNION;
#define GBBP_CPU_AMR_CB_INDEX_cpu_amr0_cb_index_START  (0)
#define GBBP_CPU_AMR_CB_INDEX_cpu_amr0_cb_index_END    (6)
#define GBBP_CPU_AMR_CB_INDEX_cpu_amr1_cb_index_START  (8)
#define GBBP_CPU_AMR_CB_INDEX_cpu_amr1_cb_index_END    (14)
#define GBBP_CPU_AMR_CB_INDEX_cpu_amr2_cb_index_START  (16)
#define GBBP_CPU_AMR_CB_INDEX_cpu_amr2_cb_index_END    (22)
#define GBBP_CPU_AMR_CB_INDEX_cpu_amr3_cb_index_START  (24)
#define GBBP_CPU_AMR_CB_INDEX_cpu_amr3_cb_index_END    (30)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_AMR_ACTIVE_SET_NUM_UNION
 �ṹ˵��  : CPU_AMR_ACTIVE_SET_NUM �Ĵ����ṹ���塣��ַƫ����:0x1308����ֵ:0x00000003�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_amr_active_set_num_reg;
    struct
    {
        unsigned int  cpu_amr_active_set_num            : 2;  /* bit[0-1]  : AMR�����������Ч����֡���͸���
                                                                             0 ��ʾ1��
                                                                             1 ��ʾ2��
                                                                             2 ��ʾ3��
                                                                             3 ��ʾ4��
                                                                             ����ҵ������ΪGMSK WBAMRʱ�����÷�ΧΪ0��2�� */
        unsigned int  reserved_0                        : 2;  /* bit[2-3]  : ���� */
        unsigned int  cpu_speech_bfi_thres              : 4;  /* bit[4-7]  : ����֡BFI��������о����ޣ����÷�Χ0��8 */
        unsigned int  reserved_1                        : 8;  /* bit[8-15] : ���� */
        unsigned int  cpu_amr_active_set_num_upflag_imi : 1;  /* bit[16]   : ��AMR������������仯ʱ����Ҫ���ø��ź�Ϊ1 */
        unsigned int  reserved_2                        : 15; /* bit[17-31]: ���� */
    } reg;
} GBBP_CPU_AMR_ACTIVE_SET_NUM_UNION;
#define GBBP_CPU_AMR_ACTIVE_SET_NUM_cpu_amr_active_set_num_START             (0)
#define GBBP_CPU_AMR_ACTIVE_SET_NUM_cpu_amr_active_set_num_END               (1)
#define GBBP_CPU_AMR_ACTIVE_SET_NUM_cpu_speech_bfi_thres_START               (4)
#define GBBP_CPU_AMR_ACTIVE_SET_NUM_cpu_speech_bfi_thres_END                 (7)
#define GBBP_CPU_AMR_ACTIVE_SET_NUM_cpu_amr_active_set_num_upflag_imi_START  (16)
#define GBBP_CPU_AMR_ACTIVE_SET_NUM_cpu_amr_active_set_num_upflag_imi_END    (16)


/*****************************************************************************
 �ṹ��    : GBBP_DB_BLER_ERR_RPT_UNION
 �ṹ˵��  : DB_BLER_ERR_RPT �Ĵ����ṹ���塣��ַƫ����:0x1484����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      db_bler_err_rpt_reg;
    struct
    {
        unsigned int  rxqual_db_bler_err : 16; /* bit[0-15] : DummyBurst������������ϱ� */
        unsigned int  reserved           : 16; /* bit[16-31]: ���� */
    } reg;
} GBBP_DB_BLER_ERR_RPT_UNION;
#define GBBP_DB_BLER_ERR_RPT_rxqual_db_bler_err_START  (0)
#define GBBP_DB_BLER_ERR_RPT_rxqual_db_bler_err_END    (15)


/*****************************************************************************
 �ṹ��    : GBBP_SB_BLER_ERR_RPT_UNION
 �ṹ˵��  : SB_BLER_ERR_RPT �Ĵ����ṹ���塣��ַƫ����:0x1488����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      sb_bler_err_rpt_reg;
    struct
    {
        unsigned int  rxqual_sb_bler_err : 8;  /* bit[0-7] : SB��������ϱ� */
        unsigned int  reserved           : 24; /* bit[8-31]: ���� */
    } reg;
} GBBP_SB_BLER_ERR_RPT_UNION;
#define GBBP_SB_BLER_ERR_RPT_rxqual_sb_bler_err_START  (0)
#define GBBP_SB_BLER_ERR_RPT_rxqual_sb_bler_err_END    (7)


/*****************************************************************************
 �ṹ��    : GBBP_DATA_BLER_ERR_RPT_UNION
 �ṹ˵��  : DATA_BLER_ERR_RPT �Ĵ����ṹ���塣��ַƫ����:0x148C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      data_bler_err_rpt_reg;
    struct
    {
        unsigned int  rxqual_data_bler_err : 16; /* bit[0-15] : EDGEҵ��DATA��������ϱ� */
        unsigned int  reserved             : 16; /* bit[16-31]: ���� */
    } reg;
} GBBP_DATA_BLER_ERR_RPT_UNION;
#define GBBP_DATA_BLER_ERR_RPT_rxqual_data_bler_err_START  (0)
#define GBBP_DATA_BLER_ERR_RPT_rxqual_data_bler_err_END    (15)


/*****************************************************************************
 �ṹ��    : GBBP_CODEC_PARA_REG1_UNION
 �ṹ˵��  : CODEC_PARA_REG1 �Ĵ����ṹ���塣��ַƫ����:0x1320����ֵ:0x10E40000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      codec_para_reg1_reg;
    struct
    {
        unsigned int  conv_rate        : 4;  /* bit[0-3]  : ���������ָʾ��
                                                            2=1/2,3=1/3,4=1/4����6=1/6�������� */
        unsigned int  conv_depth       : 1;  /* bit[4]    : ������������ȣ�0: 4;  1: 6�������� */
        unsigned int  vtb_codec_len    : 10; /* bit[5-14] : �����������ݳ��ȣ�������ǰ���ݳ��ȣ������� */
        unsigned int  vtb_cb_coded_len : 11; /* bit[15-25]: ����������ݳ��ȣ������� */
        unsigned int  codec_type       : 2;  /* bit[26-27]: ����������ͣ�
                                                            00��0״̬��ʼ����0״̬������
                                                            01��0״̬��ʼ������0״̬������
                                                            10�ӷ�0״̬��ʼ����0״̬������
                                                            11��0״̬��ʼ������0״̬������
                                                            ������ */
        unsigned int  punc_means       : 1;  /* bit[28]   : ��׷�ʽѡ��,0��ʾ��ף�1��ʾ����ף������� */
        unsigned int  vtb_codec_en     : 1;  /* bit[29]   : 1��ʾ�о��������̣������� */
        unsigned int  reserved         : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_CODEC_PARA_REG1_UNION;
#define GBBP_CODEC_PARA_REG1_conv_rate_START         (0)
#define GBBP_CODEC_PARA_REG1_conv_rate_END           (3)
#define GBBP_CODEC_PARA_REG1_conv_depth_START        (4)
#define GBBP_CODEC_PARA_REG1_conv_depth_END          (4)
#define GBBP_CODEC_PARA_REG1_vtb_codec_len_START     (5)
#define GBBP_CODEC_PARA_REG1_vtb_codec_len_END       (14)
#define GBBP_CODEC_PARA_REG1_vtb_cb_coded_len_START  (15)
#define GBBP_CODEC_PARA_REG1_vtb_cb_coded_len_END    (25)
#define GBBP_CODEC_PARA_REG1_codec_type_START        (26)
#define GBBP_CODEC_PARA_REG1_codec_type_END          (27)
#define GBBP_CODEC_PARA_REG1_punc_means_START        (28)
#define GBBP_CODEC_PARA_REG1_punc_means_END          (28)
#define GBBP_CODEC_PARA_REG1_vtb_codec_en_START      (29)
#define GBBP_CODEC_PARA_REG1_vtb_codec_en_END        (29)


/*****************************************************************************
 �ṹ��    : GBBP_CODEC_PARA_REG2_UNION
 �ṹ˵��  : CODEC_PARA_REG2 �Ĵ����ṹ���塣��ַƫ����:0x1324����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      codec_para_reg2_reg;
    struct
    {
        unsigned int  g0_poly         : 7;  /* bit[0-6]  : �������ɶ���ʽ0�������� */
        unsigned int  g1_poly         : 7;  /* bit[7-13] : �������ɶ���ʽ1�������� */
        unsigned int  g2_poly         : 7;  /* bit[14-20]: �������ɶ���ʽ2�������� */
        unsigned int  g3_poly         : 7;  /* bit[21-27]: �������ɶ���ʽ3�������� */
        unsigned int  crc_handle_flag : 2;  /* bit[28-29]: CRCԤ����ҵ���־�ź�
                                                           00 ��Ԥ����
                                                           01 ������
                                                           10 USFԤ����_1
                                                           11 USFԤ����_2
                                                           �������� */
        unsigned int  reserved        : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_CODEC_PARA_REG2_UNION;
#define GBBP_CODEC_PARA_REG2_g0_poly_START          (0)
#define GBBP_CODEC_PARA_REG2_g0_poly_END            (6)
#define GBBP_CODEC_PARA_REG2_g1_poly_START          (7)
#define GBBP_CODEC_PARA_REG2_g1_poly_END            (13)
#define GBBP_CODEC_PARA_REG2_g2_poly_START          (14)
#define GBBP_CODEC_PARA_REG2_g2_poly_END            (20)
#define GBBP_CODEC_PARA_REG2_g3_poly_START          (21)
#define GBBP_CODEC_PARA_REG2_g3_poly_END            (27)
#define GBBP_CODEC_PARA_REG2_crc_handle_flag_START  (28)
#define GBBP_CODEC_PARA_REG2_crc_handle_flag_END    (29)


/*****************************************************************************
 �ṹ��    : GBBP_CODEC_PARA_REG3_UNION
 �ṹ˵��  : CODEC_PARA_REG3 �Ĵ����ṹ���塣��ַƫ����:0x1328����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      codec_para_reg3_reg;
    struct
    {
        unsigned int  g4_poly            : 7;  /* bit[0-6]  : �������ɶ���ʽ4�������� */
        unsigned int  g5_poly            : 7;  /* bit[7-13] : �������ɶ���ʽ5�������� */
        unsigned int  denominator_g_poly : 7;  /* bit[14-20]: ��ĸλ�õı������ɶ���ʽ�������� */
        unsigned int  punc_rom_index     : 7;  /* bit[21-27]: ���ͼ���Ĵ�ױ���ţ������� */
        unsigned int  g_comb_index       : 4;  /* bit[28-31]: �������ɶ���ʽ�����ţ������� */
    } reg;
} GBBP_CODEC_PARA_REG3_UNION;
#define GBBP_CODEC_PARA_REG3_g4_poly_START             (0)
#define GBBP_CODEC_PARA_REG3_g4_poly_END               (6)
#define GBBP_CODEC_PARA_REG3_g5_poly_START             (7)
#define GBBP_CODEC_PARA_REG3_g5_poly_END               (13)
#define GBBP_CODEC_PARA_REG3_denominator_g_poly_START  (14)
#define GBBP_CODEC_PARA_REG3_denominator_g_poly_END    (20)
#define GBBP_CODEC_PARA_REG3_punc_rom_index_START      (21)
#define GBBP_CODEC_PARA_REG3_punc_rom_index_END        (27)
#define GBBP_CODEC_PARA_REG3_g_comb_index_START        (28)
#define GBBP_CODEC_PARA_REG3_g_comb_index_END          (31)


/*****************************************************************************
 �ṹ��    : GBBP_CODEC_PARA_REG4_UNION
 �ṹ˵��  : CODEC_PARA_REG4 �Ĵ����ṹ���塣��ַƫ����:0x132C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      codec_para_reg4_reg;
    struct
    {
        unsigned int  interleaving_formula_index : 5;  /* bit[0-4]  : ��֯��ʽ��ţ������� */
        unsigned int  vtb_k_start_pos            : 11; /* bit[5-15] : �������ڽ�֯����ʼbit��� */
        unsigned int  vtb_k_end_pos              : 11; /* bit[16-26]: �������ڽ�֯�н���bit��ţ������� */
        unsigned int  interleave_en              : 1;  /* bit[27]   : 1��ʾ�н�֯���̣������� */
        unsigned int  crc_exist_flag             : 1;  /* bit[28]   : 1��ʾ����CRCУ����̣������� */
        unsigned int  reserved                   : 3;  /* bit[29-31]: ���� */
    } reg;
} GBBP_CODEC_PARA_REG4_UNION;
#define GBBP_CODEC_PARA_REG4_interleaving_formula_index_START  (0)
#define GBBP_CODEC_PARA_REG4_interleaving_formula_index_END    (4)
#define GBBP_CODEC_PARA_REG4_vtb_k_start_pos_START             (5)
#define GBBP_CODEC_PARA_REG4_vtb_k_start_pos_END               (15)
#define GBBP_CODEC_PARA_REG4_vtb_k_end_pos_START               (16)
#define GBBP_CODEC_PARA_REG4_vtb_k_end_pos_END                 (26)
#define GBBP_CODEC_PARA_REG4_interleave_en_START               (27)
#define GBBP_CODEC_PARA_REG4_interleave_en_END                 (27)
#define GBBP_CODEC_PARA_REG4_crc_exist_flag_START              (28)
#define GBBP_CODEC_PARA_REG4_crc_exist_flag_END                (28)


/*****************************************************************************
 �ṹ��    : GBBP_CODEC_PARA_REG5_UNION
 �ṹ˵��  : CODEC_PARA_REG5 �Ĵ����ṹ���塣��ַƫ����:0x1330����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      codec_para_reg5_reg;
    struct
    {
        unsigned int  infom_end_pos         : 10; /* bit[0-9]  : ��Ϣbit����λ�ã������� */
        unsigned int  reserved_0            : 1;  /* bit[10]   : ���� */
        unsigned int  class2_bit_exist_flag : 1;  /* bit[11]   : 1��ʾ����CLASS2 bit�������� */
        unsigned int  class2_bit_start_pos  : 9;  /* bit[12-20]: CLASS2 bit��ʼλ�ã������� */
        unsigned int  trch_sort             : 2;  /* bit[21-22]: ����ҵ�����ָʾ
                                                                 00 ��AFS��AHS��csҵ��
                                                                 01 AFS����AHSҵ��
                                                                 10 GPRSҵ��
                                                                 11 EGPRSҵ��
                                                                 ������ */
        unsigned int  zero_fill_type        : 3;  /* bit[23-25]: β���ز��㴦��ģʽ��
                                                                 bit25: 1��ʾ�������㴦��
                                                                        0��ʾ���������㴦��
                                                                 bit24��bit23��
                                                                 00��ʾ��4����
                                                                 01��ʾ��6����
                                                                 10��ʾ��8����
                                                                 11��ʾ��32����
                                                                 ������ */
        unsigned int  crc_type              : 4;  /* bit[26-29]: CRC����ָʾ�������� */
        unsigned int  reserved_1            : 1;  /* bit[30]   : ���� */
        unsigned int  tail_exist_flag       : 1;  /* bit[31]   : 1��ʾ����β����������
                                                                 0��ʾ������
                                                                 �������� */
    } reg;
} GBBP_CODEC_PARA_REG5_UNION;
#define GBBP_CODEC_PARA_REG5_infom_end_pos_START          (0)
#define GBBP_CODEC_PARA_REG5_infom_end_pos_END            (9)
#define GBBP_CODEC_PARA_REG5_class2_bit_exist_flag_START  (11)
#define GBBP_CODEC_PARA_REG5_class2_bit_exist_flag_END    (11)
#define GBBP_CODEC_PARA_REG5_class2_bit_start_pos_START   (12)
#define GBBP_CODEC_PARA_REG5_class2_bit_start_pos_END     (20)
#define GBBP_CODEC_PARA_REG5_trch_sort_START              (21)
#define GBBP_CODEC_PARA_REG5_trch_sort_END                (22)
#define GBBP_CODEC_PARA_REG5_zero_fill_type_START         (23)
#define GBBP_CODEC_PARA_REG5_zero_fill_type_END           (25)
#define GBBP_CODEC_PARA_REG5_crc_type_START               (26)
#define GBBP_CODEC_PARA_REG5_crc_type_END                 (29)
#define GBBP_CODEC_PARA_REG5_tail_exist_flag_START        (31)
#define GBBP_CODEC_PARA_REG5_tail_exist_flag_END          (31)


/*****************************************************************************
 �ṹ��    : GBBP_CODEC_PARA_REG6_UNION
 �ṹ˵��  : CODEC_PARA_REG6 �Ĵ����ṹ���塣��ַƫ����:0x1334����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      codec_para_reg6_reg;
    struct
    {
        unsigned int  punc_rom_base_addr : 12; /* bit[0-11] : �������Ϣ�����ʼλ�ã������� */
        unsigned int  cb_index           : 7;  /* bit[12-18]: �����ţ������� */
        unsigned int  reserved_0         : 1;  /* bit[19]   : ���� */
        unsigned int  dcu_usf_bit        : 3;  /* bit[20-22]: PS��USF bit �ϱ��������� */
        unsigned int  reserved_1         : 1;  /* bit[23]   : ���� */
        unsigned int  cps_bit            : 5;  /* bit[24-28]: PS���HEADER CPSbit �ϱ��������� */
        unsigned int  reserved_2         : 3;  /* bit[29-31]: ���� */
    } reg;
} GBBP_CODEC_PARA_REG6_UNION;
#define GBBP_CODEC_PARA_REG6_punc_rom_base_addr_START  (0)
#define GBBP_CODEC_PARA_REG6_punc_rom_base_addr_END    (11)
#define GBBP_CODEC_PARA_REG6_cb_index_START            (12)
#define GBBP_CODEC_PARA_REG6_cb_index_END              (18)
#define GBBP_CODEC_PARA_REG6_dcu_usf_bit_START         (20)
#define GBBP_CODEC_PARA_REG6_dcu_usf_bit_END           (22)
#define GBBP_CODEC_PARA_REG6_cps_bit_START             (24)
#define GBBP_CODEC_PARA_REG6_cps_bit_END               (28)


/*****************************************************************************
 �ṹ��    : GBBP_CODEC_PARA_REG7_UNION
 �ṹ˵��  : CODEC_PARA_REG7 �Ĵ����ṹ���塣��ַƫ����:0x123C����ֵ:0x003F000F�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      codec_para_reg7_reg;
    struct
    {
        unsigned int  dcu_ps_codec_type  : 4;  /* bit[0-3]  : �����PSҵ���ϱ� */
        unsigned int  reserved_0         : 12; /* bit[4-15] : ���� */
        unsigned int  dcu_amr_frame_type : 6;  /* bit[16-21]: �����AMRҵ���ϱ� */
        unsigned int  reserved_1         : 10; /* bit[22-31]: ���� */
    } reg;
} GBBP_CODEC_PARA_REG7_UNION;
#define GBBP_CODEC_PARA_REG7_dcu_ps_codec_type_START   (0)
#define GBBP_CODEC_PARA_REG7_dcu_ps_codec_type_END     (3)
#define GBBP_CODEC_PARA_REG7_dcu_amr_frame_type_START  (16)
#define GBBP_CODEC_PARA_REG7_dcu_amr_frame_type_END    (21)


/*****************************************************************************
 �ṹ��    : GBBP_DEC_STATE_RPT1_UNION
 �ṹ˵��  : DEC_STATE_RPT1 �Ĵ����ṹ���塣��ַƫ����:0x1338����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      dec_state_rpt1_reg;
    struct
    {
        unsigned int  trch_sort_state_cpu : 4;  /* bit[0-3]  : ����ҵ������ж�״̬��״̬�������� */
        unsigned int  kn_pro_state_cpu    : 4;  /* bit[4-7]  : ҵ��������֪��״̬��״̬�������� */
        unsigned int  harq_pro_state_cpu  : 3;  /* bit[8-10] : HARQ�ϲ�������״̬��״̬�������� */
        unsigned int  reserved_0          : 1;  /* bit[11]   : ���� */
        unsigned int  ukn_afs_state_cpu   : 5;  /* bit[12-16]: AFSҵ����״̬��״̬�������� */
        unsigned int  reserved_1          : 3;  /* bit[17-19]: ���� */
        unsigned int  ukn_ahs_state_cpu   : 6;  /* bit[20-25]: AHSҵ����״̬��״̬�������� */
        unsigned int  reserved_2          : 1;  /* bit[26]   : ���� */
        unsigned int  ukn_ps_state_cpu    : 5;  /* bit[27-31]: PSҵ����״̬��״̬�������� */
    } reg;
} GBBP_DEC_STATE_RPT1_UNION;
#define GBBP_DEC_STATE_RPT1_trch_sort_state_cpu_START  (0)
#define GBBP_DEC_STATE_RPT1_trch_sort_state_cpu_END    (3)
#define GBBP_DEC_STATE_RPT1_kn_pro_state_cpu_START     (4)
#define GBBP_DEC_STATE_RPT1_kn_pro_state_cpu_END       (7)
#define GBBP_DEC_STATE_RPT1_harq_pro_state_cpu_START   (8)
#define GBBP_DEC_STATE_RPT1_harq_pro_state_cpu_END     (10)
#define GBBP_DEC_STATE_RPT1_ukn_afs_state_cpu_START    (12)
#define GBBP_DEC_STATE_RPT1_ukn_afs_state_cpu_END      (16)
#define GBBP_DEC_STATE_RPT1_ukn_ahs_state_cpu_START    (20)
#define GBBP_DEC_STATE_RPT1_ukn_ahs_state_cpu_END      (25)
#define GBBP_DEC_STATE_RPT1_ukn_ps_state_cpu_START     (27)
#define GBBP_DEC_STATE_RPT1_ukn_ps_state_cpu_END       (31)


/*****************************************************************************
 �ṹ��    : GBBP_DEC_STATE_RPT2_UNION
 �ṹ˵��  : DEC_STATE_RPT2 �Ĵ����ṹ���塣��ַƫ����:0x133C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      dec_state_rpt2_reg;
    struct
    {
        unsigned int  reserved_0           : 8;  /* bit[0-7]  : ���� */
        unsigned int  vtb_state_cpu        : 4;  /* bit[8-11] : VTB������״̬��״̬�������� */
        unsigned int  corr_state_cpu       : 2;  /* bit[12-13]: ���������״̬��״̬�������� */
        unsigned int  reserved_1           : 2;  /* bit[14-15]: ���� */
        unsigned int  interleave_state_cpu : 4;  /* bit[16-19]: ��֯ģ�鹤��״̬�������� */
        unsigned int  depunc_state_cpu     : 3;  /* bit[20-22]: ȥ���ģ�鹤��״̬�������� */
        unsigned int  reserved_2           : 1;  /* bit[23]   : ���� */
        unsigned int  ccu_state_cpu        : 4;  /* bit[24-27]: CCU����״̬�������� */
        unsigned int  reserved_3           : 3;  /* bit[28-30]: ���� */
        unsigned int  dec_busy_cpu         : 1;  /* bit[31]   : ��������æ״̬�������� */
    } reg;
} GBBP_DEC_STATE_RPT2_UNION;
#define GBBP_DEC_STATE_RPT2_vtb_state_cpu_START         (8)
#define GBBP_DEC_STATE_RPT2_vtb_state_cpu_END           (11)
#define GBBP_DEC_STATE_RPT2_corr_state_cpu_START        (12)
#define GBBP_DEC_STATE_RPT2_corr_state_cpu_END          (13)
#define GBBP_DEC_STATE_RPT2_interleave_state_cpu_START  (16)
#define GBBP_DEC_STATE_RPT2_interleave_state_cpu_END    (19)
#define GBBP_DEC_STATE_RPT2_depunc_state_cpu_START      (20)
#define GBBP_DEC_STATE_RPT2_depunc_state_cpu_END        (22)
#define GBBP_DEC_STATE_RPT2_ccu_state_cpu_START         (24)
#define GBBP_DEC_STATE_RPT2_ccu_state_cpu_END           (27)
#define GBBP_DEC_STATE_RPT2_dec_busy_cpu_START          (31)
#define GBBP_DEC_STATE_RPT2_dec_busy_cpu_END            (31)


/*****************************************************************************
 �ṹ��    : GBBP_DEC_INT_TOTAL_UNION
 �ṹ˵��  : DEC_INT_TOTAL �Ĵ����ṹ���塣��ַƫ����:0x1348����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      dec_int_total_reg;
    struct
    {
        unsigned int  dec_int_cnt : 4;  /* bit[0-3]  : �����жϴ����������ϱ� */
        unsigned int  reserved_0  : 12; /* bit[4-15] : ���� */
        unsigned int  dec_cnt     : 4;  /* bit[16-19]: �������������������ϱ� */
        unsigned int  reserved_1  : 12; /* bit[20-31]: ���� */
    } reg;
} GBBP_DEC_INT_TOTAL_UNION;
#define GBBP_DEC_INT_TOTAL_dec_int_cnt_START  (0)
#define GBBP_DEC_INT_TOTAL_dec_int_cnt_END    (3)
#define GBBP_DEC_INT_TOTAL_dec_cnt_START      (16)
#define GBBP_DEC_INT_TOTAL_dec_cnt_END        (19)


/*****************************************************************************
 �ṹ��    : GBBP_BFI_RSQ_METRIC_RPT_UNION
 �ṹ˵��  : BFI_RSQ_METRIC_RPT �Ĵ����ṹ���塣��ַƫ����:0x134C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bfi_rsq_metric_rpt_reg;
    struct
    {
        unsigned int  amr_rsq_metric         : 8;  /* bit[0-7]  : CS������RSQ_METRIC�ϱ� */
        unsigned int  reserved_0             : 8;  /* bit[8-15] : ���� */
        unsigned int  amr_pber               : 7;  /* bit[16-22]: CS������PBER�ϱ� */
        unsigned int  reserved_1             : 8;  /* bit[23-30]: ���� */
        unsigned int  speech_bfi_corr_result : 1;  /* bit[31]   : 1��ʶ������֡����о�ΪBFI��
                                                                  0��ʶ������֡����о�����BFI */
    } reg;
} GBBP_BFI_RSQ_METRIC_RPT_UNION;
#define GBBP_BFI_RSQ_METRIC_RPT_amr_rsq_metric_START          (0)
#define GBBP_BFI_RSQ_METRIC_RPT_amr_rsq_metric_END            (7)
#define GBBP_BFI_RSQ_METRIC_RPT_amr_pber_START                (16)
#define GBBP_BFI_RSQ_METRIC_RPT_amr_pber_END                  (22)
#define GBBP_BFI_RSQ_METRIC_RPT_speech_bfi_corr_result_START  (31)
#define GBBP_BFI_RSQ_METRIC_RPT_speech_bfi_corr_result_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_UL_CODE_STATE_RPT_UNION
 �ṹ˵��  : UL_CODE_STATE_RPT �Ĵ����ṹ���塣��ַƫ����:0x13B0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      ul_code_state_rpt_reg;
    struct
    {
        unsigned int  ul_code_state : 2;  /* bit[0-1] : 00��ʾIDLE������״̬��                                     01��ʾINIT����ʼ��״̬��                                     10��ʾCODE������״̬��                                     11��ʾINTE����֯״̬��
                                                        ������ */
        unsigned int  reserved_0    : 2;  /* bit[2-3] : ���� */
        unsigned int  ul_crc_state  : 2;  /* bit[4-5] : 00��ʾIDLE������״̬��                                     01��ʾRECV������״̬��                                     10��ʾCHECK��У��״̬��                                     11��Ч״̬
                                                        ������ */
        unsigned int  reserved_1    : 26; /* bit[6-31]: ���� */
    } reg;
} GBBP_UL_CODE_STATE_RPT_UNION;
#define GBBP_UL_CODE_STATE_RPT_ul_code_state_START  (0)
#define GBBP_UL_CODE_STATE_RPT_ul_code_state_END    (1)
#define GBBP_UL_CODE_STATE_RPT_ul_crc_state_START   (4)
#define GBBP_UL_CODE_STATE_RPT_ul_crc_state_END     (5)


/*****************************************************************************
 �ṹ��    : GBBP_UL_CODE_RAM_RST_UNION
 �ṹ˵��  : UL_CODE_RAM_RST �Ĵ����ṹ���塣��ַƫ����:0x13B4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      ul_code_ram_rst_reg;
    struct
    {
        unsigned int  cpu_ul_cod_ram_rst_imi : 1;  /* bit[0]   : ����Ա���ģ���ڲ�RAM�����뽻֯��洢RAM�������źţ�ֻ�迪��������һ�¼��ɣ��߼������� */
        unsigned int  reserved               : 31; /* bit[1-31]: ���� */
    } reg;
} GBBP_UL_CODE_RAM_RST_UNION;
#define GBBP_UL_CODE_RAM_RST_cpu_ul_cod_ram_rst_imi_START  (0)
#define GBBP_UL_CODE_RAM_RST_cpu_ul_cod_ram_rst_imi_END    (0)


/*****************************************************************************
 �ṹ��    : GBBP_UL_CODE_RAM_RST_CFG_UNION
 �ṹ˵��  : UL_CODE_RAM_RST_CFG �Ĵ����ṹ���塣��ַƫ����:0x13B8����ֵ:0x004D0000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      ul_code_ram_rst_cfg_reg;
    struct
    {
        unsigned int  cpu_ul_cod_ram_rst_addr   : 7;  /* bit[0-6]  : ������ʼ���ַ */
        unsigned int  reserved_0                : 9;  /* bit[7-15] : ���� */
        unsigned int  cpu_ul_cod_ram_rst_length : 7;  /* bit[16-22]: �������ݿ鳤�� */
        unsigned int  reserved_1                : 9;  /* bit[23-31]: ���� */
    } reg;
} GBBP_UL_CODE_RAM_RST_CFG_UNION;
#define GBBP_UL_CODE_RAM_RST_CFG_cpu_ul_cod_ram_rst_addr_START    (0)
#define GBBP_UL_CODE_RAM_RST_CFG_cpu_ul_cod_ram_rst_addr_END      (6)
#define GBBP_UL_CODE_RAM_RST_CFG_cpu_ul_cod_ram_rst_length_START  (16)
#define GBBP_UL_CODE_RAM_RST_CFG_cpu_ul_cod_ram_rst_length_END    (22)


/*****************************************************************************
 �ṹ��    : GBBP_WAKE_TEST_QB_FRAC_RPT_UNION
 �ṹ˵��  : WAKE_TEST_QB_FRAC_RPT �Ĵ����ṹ���塣��ַƫ����:0x1224����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      wake_test_qb_frac_rpt_reg;
    struct
    {
        unsigned int  gdrx_wake_frac     : 7;  /* bit[0-6]  : DRX�����л�ʱGTC��ʱFRAC�����������ã�104M�Ӳ��ϣ�����GTC������DRX�����Ƿ���ͬ���������� */
        unsigned int  reserved_0         : 9;  /* bit[7-15] : ���� */
        unsigned int  gdrx_wake_chip_cnt : 13; /* bit[16-28]: DRX�����л�ʱGTC��ʱgtc_timebase�����������ã�104M�Ӳ��ϣ�����GTC������DRX�����Ƿ���ͬ���������� */
        unsigned int  reserved_1         : 3;  /* bit[29-31]: ���� */
    } reg;
} GBBP_WAKE_TEST_QB_FRAC_RPT_UNION;
#define GBBP_WAKE_TEST_QB_FRAC_RPT_gdrx_wake_frac_START      (0)
#define GBBP_WAKE_TEST_QB_FRAC_RPT_gdrx_wake_frac_END        (6)
#define GBBP_WAKE_TEST_QB_FRAC_RPT_gdrx_wake_chip_cnt_START  (16)
#define GBBP_WAKE_TEST_QB_FRAC_RPT_gdrx_wake_chip_cnt_END    (28)


/*****************************************************************************
 �ṹ��    : GBBP_WAKE_TEST_T1_T2_T3_RPT_UNION
 �ṹ˵��  : WAKE_TEST_T1_T2_T3_RPT �Ĵ����ṹ���塣��ַƫ����:0x1228����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      wake_test_t1_t2_t3_rpt_reg;
    struct
    {
        unsigned int  gdrx_wake_t1_cnt : 11; /* bit[0-10] : DRX�����л�ʱGTC��ʱT1�����������ã�104M�Ӳ��ϣ�����GTC������DRX�����Ƿ���ͬ���������� */
        unsigned int  reserved_0       : 5;  /* bit[11-15]: ���� */
        unsigned int  gdrx_wake_t2_cnt : 5;  /* bit[16-20]: DRX�����л�ʱGTC��ʱT2�����������ã�104M�Ӳ��ϣ�����GTC������DRX�����Ƿ���ͬ���������� */
        unsigned int  reserved_1       : 3;  /* bit[21-23]: ���� */
        unsigned int  gdrx_wake_t3_cnt : 6;  /* bit[24-29]: DRX�����л�ʱGTC��ʱT3�����������ã�104M�Ӳ��ϣ�����GTC������DRX�����Ƿ���ͬ���������� */
        unsigned int  reserved_2       : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_WAKE_TEST_T1_T2_T3_RPT_UNION;
#define GBBP_WAKE_TEST_T1_T2_T3_RPT_gdrx_wake_t1_cnt_START  (0)
#define GBBP_WAKE_TEST_T1_T2_T3_RPT_gdrx_wake_t1_cnt_END    (10)
#define GBBP_WAKE_TEST_T1_T2_T3_RPT_gdrx_wake_t2_cnt_START  (16)
#define GBBP_WAKE_TEST_T1_T2_T3_RPT_gdrx_wake_t2_cnt_END    (20)
#define GBBP_WAKE_TEST_T1_T2_T3_RPT_gdrx_wake_t3_cnt_START  (24)
#define GBBP_WAKE_TEST_T1_T2_T3_RPT_gdrx_wake_t3_cnt_END    (29)


/*****************************************************************************
 �ṹ��    : GBBP_WAKE_GTC_FN_RPT_UNION
 �ṹ˵��  : WAKE_GTC_FN_RPT �Ĵ����ṹ���塣��ַƫ����:0x122C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      wake_gtc_fn_rpt_reg;
    struct
    {
        unsigned int  gdrx_wake_fn_low  : 11; /* bit[0-10] : DRX�����л�ʱ����ʱGTC��FN_LOW����ֵ������DRX������ */
        unsigned int  reserved_0        : 5;  /* bit[11-15]: ���� */
        unsigned int  gdrx_wake_fn_high : 11; /* bit[16-26]: DRX�����л�ʱ����ʱGTC��FN_HIGH����ֵ������DRX������ */
        unsigned int  reserved_1        : 5;  /* bit[27-31]: ���� */
    } reg;
} GBBP_WAKE_GTC_FN_RPT_UNION;
#define GBBP_WAKE_GTC_FN_RPT_gdrx_wake_fn_low_START   (0)
#define GBBP_WAKE_GTC_FN_RPT_gdrx_wake_fn_low_END     (10)
#define GBBP_WAKE_GTC_FN_RPT_gdrx_wake_fn_high_START  (16)
#define GBBP_WAKE_GTC_FN_RPT_gdrx_wake_fn_high_END    (26)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_A5_LSB_SEQ_SEL_UNION
 �ṹ˵��  : CPU_A5_LSB_SEQ_SEL �Ĵ����ṹ���塣��ַƫ����:0x1458����ֵ:0x00000100�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_a5_lsb_seq_sel_reg;
    struct
    {
        unsigned int  cpu_a5_sequence_lsb_sel : 1;  /* bit[0]   : �ڲ�A53�ӽ����㷨bit���˳�����ã�������Ϊ0 */
        unsigned int  reserved_0              : 3;  /* bit[1-3] : ���� */
        unsigned int  cpu_deciph_dir          : 1;  /* bit[4]   : �ڲ�A53�����㷨bit���˳�����ã�������Ϊ0 */
        unsigned int  reserved_1              : 3;  /* bit[5-7] : ���� */
        unsigned int  cpu_ciph_dir            : 1;  /* bit[8]   : �ڲ�A53�����㷨bit���˳�����ã�������Ϊ1 */
        unsigned int  reserved_2              : 23; /* bit[9-31]: ���� */
    } reg;
} GBBP_CPU_A5_LSB_SEQ_SEL_UNION;
#define GBBP_CPU_A5_LSB_SEQ_SEL_cpu_a5_sequence_lsb_sel_START  (0)
#define GBBP_CPU_A5_LSB_SEQ_SEL_cpu_a5_sequence_lsb_sel_END    (0)
#define GBBP_CPU_A5_LSB_SEQ_SEL_cpu_deciph_dir_START           (4)
#define GBBP_CPU_A5_LSB_SEQ_SEL_cpu_deciph_dir_END             (4)
#define GBBP_CPU_A5_LSB_SEQ_SEL_cpu_ciph_dir_START             (8)
#define GBBP_CPU_A5_LSB_SEQ_SEL_cpu_ciph_dir_END               (8)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_2G4_GAP_LENGTH_UNION
 �ṹ˵��  : CPU_2G4_GAP_LENGTH �Ĵ����ṹ���塣��ַƫ����:0x1248����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_2g4_gap_length_reg;
    struct
    {
        unsigned int  cpu_2g4_gap_length : 23; /* bit[0-22] : 2G�½���4G������GAP���ȡ���λ��QB��
                                                              1��2GΪ��ģʱ����ϵͳGAP��󳤶�Ϊ���13*51-2֡���ң�����3305000Qb��
                                                              2��cpu_2g4_gap_length�����÷�Χ��0~3305000QB��
                                                              3��cpu_2g4_gap_length + cpu_2g4_int0_int1_dist�Ľ������Ӧ����23'h7f_ffff�� */
        unsigned int  reserved           : 9;  /* bit[23-31]: ���� */
    } reg;
} GBBP_CPU_2G4_GAP_LENGTH_UNION;
#define GBBP_CPU_2G4_GAP_LENGTH_cpu_2g4_gap_length_START  (0)
#define GBBP_CPU_2G4_GAP_LENGTH_cpu_2g4_gap_length_END    (22)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_2G4_GAP_STOP_UNION
 �ṹ˵��  : CPU_2G4_GAP_STOP �Ĵ����ṹ���塣��ַƫ����:0x124C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_2g4_gap_stop_reg;
    struct
    {
        unsigned int  cpu_2g4_gap_stop_imi : 1;  /* bit[0]   : 2G�½���4G�����ڼ䣬GPHY��ǰֹͣoccasion���źţ������źš�GBBP�յ����źź�����ֹͣgap_cnt���������ϱ�int2�������жϣ���������ͨ������ָʾ�ź�wg_intrasys_valid_delay�������㡣 */
        unsigned int  cpu_2g4_int0_en_imi  : 1;  /* bit[1]   : �����һ֡��Ҫ����2G��4G�����ڵ�ǰ֡������ʱ϶�����ø��ź�Ϊ1��������cpu_int0_gen_qb�������㡣 */
        unsigned int  reserved             : 30; /* bit[2-31]: ���� */
    } reg;
} GBBP_CPU_2G4_GAP_STOP_UNION;
#define GBBP_CPU_2G4_GAP_STOP_cpu_2g4_gap_stop_imi_START  (0)
#define GBBP_CPU_2G4_GAP_STOP_cpu_2g4_gap_stop_imi_END    (0)
#define GBBP_CPU_2G4_GAP_STOP_cpu_2g4_int0_en_imi_START   (1)
#define GBBP_CPU_2G4_GAP_STOP_cpu_2g4_int0_en_imi_END     (1)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_2G4_DIST_UNION
 �ṹ˵��  : CPU_2G4_DIST �Ĵ����ṹ���塣��ַƫ����:0x1250����ֵ:0x0003006C�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_2g4_dist_reg;
    struct
    {
        unsigned int  cpu_2g4_int0_int1_dist : 12; /* bit[0-11] : 2G��4Gʱ���ж�0���ж�1�ļ��ʱ�䡣��λ��QB��
                                                                  Ĭ��ֵ��108QB��Լ100us�� */
        unsigned int  reserved_0             : 4;  /* bit[12-15]: ���� */
        unsigned int  cpu_g_intrasys_delay   : 4;  /* bit[16-19]: g_intrasys_valid_delay�����g_intrasys_valid���ӳ�ʱ�䡣֧���ӳ�1~3��SSIд�������ڣ���֤LTE�����һ����Ƶ����д�ꡣд��һ��SSI�֣�����ʱ��������27*52.08 = 1406.16 ns��Լ1.5QB ��Ĭ��ֵ����3��QB���� */
        unsigned int  reserved_1             : 12; /* bit[20-31]: ���� */
    } reg;
} GBBP_CPU_2G4_DIST_UNION;
#define GBBP_CPU_2G4_DIST_cpu_2g4_int0_int1_dist_START  (0)
#define GBBP_CPU_2G4_DIST_cpu_2g4_int0_int1_dist_END    (11)
#define GBBP_CPU_2G4_DIST_cpu_g_intrasys_delay_START    (16)
#define GBBP_CPU_2G4_DIST_cpu_g_intrasys_delay_END      (19)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_2G4_INT0_GEN_QB_UNION
 �ṹ˵��  : CPU_2G4_INT0_GEN_QB �Ĵ����ṹ���塣��ַƫ����:0x1254����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_2g4_int0_gen_qb_reg;
    struct
    {
        unsigned int  cpu_2g4_int0_gen_qb  : 13; /* bit[0-12] : �����һ֡��Ҫ����2G��4G�����ڵ�ǰ֡������ʱ϶�����ø��źţ���ʾ����֡֡ͷ֮��cpu_2g4_int0_gen_qb��QB�������ж�0 */
        unsigned int  reserved_0           : 3;  /* bit[13-15]: ���� */
        unsigned int  cpu_2g4_gap_stop_rpt : 2;  /* bit[16-17]: cpu_2g4_gap_stop�źŴ����ļ����������ڹ۲�cpu_2g4_gap_stop�ź��Ƿ���Ч�������Ч����ÿ�θü������Լ�1��ѭ������ */
        unsigned int  reserved_1           : 6;  /* bit[18-23]: ���� */
        unsigned int  cpu_2g4_int0_rpt     : 2;  /* bit[24-25]: cpu_2g4_int0_en�źŴ����ļ����������ڹ۲�cpu_2g4_int0_en�ź��Ƿ���Ч�������Ч����ÿ�θü������Լ�1��ѭ������ */
        unsigned int  reserved_2           : 6;  /* bit[26-31]: ���� */
    } reg;
} GBBP_CPU_2G4_INT0_GEN_QB_UNION;
#define GBBP_CPU_2G4_INT0_GEN_QB_cpu_2g4_int0_gen_qb_START   (0)
#define GBBP_CPU_2G4_INT0_GEN_QB_cpu_2g4_int0_gen_qb_END     (12)
#define GBBP_CPU_2G4_INT0_GEN_QB_cpu_2g4_gap_stop_rpt_START  (16)
#define GBBP_CPU_2G4_INT0_GEN_QB_cpu_2g4_gap_stop_rpt_END    (17)
#define GBBP_CPU_2G4_INT0_GEN_QB_cpu_2g4_int0_rpt_START      (24)
#define GBBP_CPU_2G4_INT0_GEN_QB_cpu_2g4_int0_rpt_END        (25)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_2G4_INT0_TIMING_UNION
 �ṹ˵��  : CPU_2G4_INT0_TIMING �Ĵ����ṹ���塣��ַƫ����:0x1240����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_2g4_int0_timing_reg;
    struct
    {
        unsigned int  g_int0_timebase_qb : 13; /* bit[0-12] : 2G��4Gʱ���ж�0��Ӧ��timebase����λ��QB */
        unsigned int  reserved_0         : 3;  /* bit[13-15]: ���� */
        unsigned int  g_int0_fn          : 11; /* bit[16-26]: 2G��4Gʱ���ж�0��Ӧ��FN��11λ */
        unsigned int  reserved_1         : 5;  /* bit[27-31]: ���� */
    } reg;
} GBBP_CPU_2G4_INT0_TIMING_UNION;
#define GBBP_CPU_2G4_INT0_TIMING_g_int0_timebase_qb_START  (0)
#define GBBP_CPU_2G4_INT0_TIMING_g_int0_timebase_qb_END    (12)
#define GBBP_CPU_2G4_INT0_TIMING_g_int0_fn_START           (16)
#define GBBP_CPU_2G4_INT0_TIMING_g_int0_fn_END             (26)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_2G4_INT2_TIMING_UNION
 �ṹ˵��  : CPU_2G4_INT2_TIMING �Ĵ����ṹ���塣��ַƫ����:0x1244����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_2g4_int2_timing_reg;
    struct
    {
        unsigned int  g_int2_timebase_qb : 13; /* bit[0-12] : 2G��4Gʱ���ж�2��Ӧ��timebase����λ��QB */
        unsigned int  reserved_0         : 3;  /* bit[13-15]: ���� */
        unsigned int  g_int2_fn          : 11; /* bit[16-26]: 2G��4Gʱ���ж�2��Ӧ��FN��11λ */
        unsigned int  reserved_1         : 5;  /* bit[27-31]: ���� */
    } reg;
} GBBP_CPU_2G4_INT2_TIMING_UNION;
#define GBBP_CPU_2G4_INT2_TIMING_g_int2_timebase_qb_START  (0)
#define GBBP_CPU_2G4_INT2_TIMING_g_int2_timebase_qb_END    (12)
#define GBBP_CPU_2G4_INT2_TIMING_g_int2_fn_START           (16)
#define GBBP_CPU_2G4_INT2_TIMING_g_int2_fn_END             (26)


/*****************************************************************************
 �ṹ��    : GBBP_FB_AFC_PHASE_THRESHOLD_CFG_UNION
 �ṹ˵��  : FB_AFC_PHASE_THRESHOLD_CFG �Ĵ����ṹ���塣��ַƫ����:0x1230����ֵ:0x02F801F4�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      fb_afc_phase_threshold_cfg_reg;
    struct
    {
        unsigned int  cpu_fb_afc_phase_min : 10; /* bit[0-9]  : FB-AFC�㷨��λ����ֵ�ο����ޣ�����ֵ500������300,400,500�� */
        unsigned int  reserved_0           : 6;  /* bit[10-15]: ���� */
        unsigned int  cpu_fb_afc_phase_max : 10; /* bit[16-25]: FB-AFC�㷨��λ����ֵ�ο����ޣ�����ֵ760�� */
        unsigned int  reserved_1           : 6;  /* bit[26-31]: ���� */
    } reg;
} GBBP_FB_AFC_PHASE_THRESHOLD_CFG_UNION;
#define GBBP_FB_AFC_PHASE_THRESHOLD_CFG_cpu_fb_afc_phase_min_START  (0)
#define GBBP_FB_AFC_PHASE_THRESHOLD_CFG_cpu_fb_afc_phase_min_END    (9)
#define GBBP_FB_AFC_PHASE_THRESHOLD_CFG_cpu_fb_afc_phase_max_START  (16)
#define GBBP_FB_AFC_PHASE_THRESHOLD_CFG_cpu_fb_afc_phase_max_END    (25)


/*****************************************************************************
 �ṹ��    : GBBP_FB_FCUT_THRESHOLD_CFG_UNION
 �ṹ˵��  : FB_FCUT_THRESHOLD_CFG �Ĵ����ṹ���塣��ַƫ����:0x1234����ֵ:0x03FF0033�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      fb_fcut_threshold_cfg_reg;
    struct
    {
        unsigned int  cpu_fb_afc_fc_low  : 10; /* bit[0-9]  : FB-AFC�㷨ϵ��fcut����Сֵ������������˲������λ����ֵС����λ����ֵ�ο����ޣ���ϵ��fcut��ֵ�͵��ڴ���Сֵ������ֵ51�� */
        unsigned int  reserved_0         : 6;  /* bit[10-15]: ���� */
        unsigned int  cpu_fb_afc_fc_high : 10; /* bit[16-25]: FB-AFC�㷨ϵ��fcut�����ֵ������������˲������λ����ֵ������λ����ֵ�Ĳο����ޣ���ϵ��fcut��ֵ�͵��ڴ����ֵ������ֵ1023�� */
        unsigned int  reserved_1         : 6;  /* bit[26-31]: ���� */
    } reg;
} GBBP_FB_FCUT_THRESHOLD_CFG_UNION;
#define GBBP_FB_FCUT_THRESHOLD_CFG_cpu_fb_afc_fc_low_START   (0)
#define GBBP_FB_FCUT_THRESHOLD_CFG_cpu_fb_afc_fc_low_END     (9)
#define GBBP_FB_FCUT_THRESHOLD_CFG_cpu_fb_afc_fc_high_START  (16)
#define GBBP_FB_FCUT_THRESHOLD_CFG_cpu_fb_afc_fc_high_END    (25)


/*****************************************************************************
 �ṹ��    : GBBP_FB_AFC_ALPHA_SEL_UNION
 �ṹ˵��  : FB_AFC_ALPHA_SEL �Ĵ����ṹ���塣��ַƫ����:0x1238����ֵ:0x03FF4A00�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      fb_afc_alpha_sel_reg;
    struct
    {
        unsigned int  cpu_fb_numerator_sel : 2;  /* bit[0-1]  : FB-AFC�㷨���˲�ϵ��ѡ��
                                                                0��1/32��
                                                                1��1/16��
                                                                2��1/8��
                                                                3��1/4��
                                                                ����ֵ1/32�� */
        unsigned int  reserved_0           : 6;  /* bit[2-7]  : ���� */
        unsigned int  cpu_fb_stage_num     : 4;  /* bit[8-11] : Fcutֵ�̶�ʹ��FCutInit�ĸ���FB���롣���䷶Χ��5~10���������ã�10�� */
        unsigned int  cpu_fb_rshift_num    : 3;  /* bit[12-14]: �Գ����Ʊ����������䷶Χ0~7���������ã�4�� */
        unsigned int  reserved_1           : 1;  /* bit[15]   : ���� */
        unsigned int  cpu_fcut_init        : 10; /* bit[16-25]: һ�׻�·�˲�����ʼ�����������ã�1023�� */
        unsigned int  reserved_2           : 6;  /* bit[26-31]: ���� */
    } reg;
} GBBP_FB_AFC_ALPHA_SEL_UNION;
#define GBBP_FB_AFC_ALPHA_SEL_cpu_fb_numerator_sel_START  (0)
#define GBBP_FB_AFC_ALPHA_SEL_cpu_fb_numerator_sel_END    (1)
#define GBBP_FB_AFC_ALPHA_SEL_cpu_fb_stage_num_START      (8)
#define GBBP_FB_AFC_ALPHA_SEL_cpu_fb_stage_num_END        (11)
#define GBBP_FB_AFC_ALPHA_SEL_cpu_fb_rshift_num_START     (12)
#define GBBP_FB_AFC_ALPHA_SEL_cpu_fb_rshift_num_END       (14)
#define GBBP_FB_AFC_ALPHA_SEL_cpu_fcut_init_START         (16)
#define GBBP_FB_AFC_ALPHA_SEL_cpu_fcut_init_END           (25)


/*****************************************************************************
 �ṹ��    : GBBP_SRCH_OPT_CFG_UNION
 �ṹ˵��  : SRCH_OPT_CFG �Ĵ����ṹ���塣��ַƫ����:0x1480����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      srch_opt_cfg_reg;
    struct
    {
        unsigned int  cpu_srch_opt_en            : 1;  /* bit[0]    : 111�����Ż�ģʽʹ�ܣ�1��־���Ż�ʹ�ܣ�0��־�ر��Ż�ʹ�ܣ�����001 111������ */
        unsigned int  reserved_0                 : 3;  /* bit[1-3]  : ���� */
        unsigned int  cpu_sb_lock_fail_threshold : 2;  /* bit[4-5]  : 111�Ż��㷨��FB-AFC����������SB����CRC����Ĵ�����ȡֵ��Χ0~3�� */
        unsigned int  reserved_1                 : 10; /* bit[6-15] : ���� */
        unsigned int  cpu_sb_bsic_threshold      : 2;  /* bit[16-17]: 111�Ż��㷨������SB����CRC����BSICֵ��ͬ���ܴ���
                                                                      0��4�Σ�
                                                                      1��5�Σ�
                                                                      2��6�Σ�
                                                                      3��7�Ρ� */
        unsigned int  reserved_2                 : 6;  /* bit[18-23]: ���� */
        unsigned int  sb_dec_bsic                : 6;  /* bit[24-29]: ����SB����BSIC�ϱ��� */
        unsigned int  reserved_3                 : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_SRCH_OPT_CFG_UNION;
#define GBBP_SRCH_OPT_CFG_cpu_srch_opt_en_START             (0)
#define GBBP_SRCH_OPT_CFG_cpu_srch_opt_en_END               (0)
#define GBBP_SRCH_OPT_CFG_cpu_sb_lock_fail_threshold_START  (4)
#define GBBP_SRCH_OPT_CFG_cpu_sb_lock_fail_threshold_END    (5)
#define GBBP_SRCH_OPT_CFG_cpu_sb_bsic_threshold_START       (16)
#define GBBP_SRCH_OPT_CFG_cpu_sb_bsic_threshold_END         (17)
#define GBBP_SRCH_OPT_CFG_sb_dec_bsic_START                 (24)
#define GBBP_SRCH_OPT_CFG_sb_dec_bsic_END                   (29)


/*****************************************************************************
 �ṹ��    : GBBP_R2_RSSI1234_THRESHOLD_UNION
 �ṹ˵��  : R2_RSSI1234_THRESHOLD �Ĵ����ṹ���塣��ַƫ����:0x5204����ֵ:0x00D3BFA3�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      r2_rssi1234_threshold_reg;
    struct
    {
        unsigned int  cpu_r2_rssi1_threshold : 8;  /* bit[0-7]  : RSSI ��������1����λdBm���Ƽ�-93 */
        unsigned int  cpu_r2_rssi2_threshold : 8;  /* bit[8-15] : RSSI ��������2����λdBm���Ƽ�-65 */
        unsigned int  cpu_r2_rssi3_threshold : 8;  /* bit[16-23]: RSSI ��������3����λdBm���Ƽ�-45 */
        unsigned int  reserved               : 8;  /* bit[24-31]: ���� */
    } reg;
} GBBP_R2_RSSI1234_THRESHOLD_UNION;
#define GBBP_R2_RSSI1234_THRESHOLD_cpu_r2_rssi1_threshold_START  (0)
#define GBBP_R2_RSSI1234_THRESHOLD_cpu_r2_rssi1_threshold_END    (7)
#define GBBP_R2_RSSI1234_THRESHOLD_cpu_r2_rssi2_threshold_START  (8)
#define GBBP_R2_RSSI1234_THRESHOLD_cpu_r2_rssi2_threshold_END    (15)
#define GBBP_R2_RSSI1234_THRESHOLD_cpu_r2_rssi3_threshold_START  (16)
#define GBBP_R2_RSSI1234_THRESHOLD_cpu_r2_rssi3_threshold_END    (23)


/*****************************************************************************
 �ṹ��    : GBBP_R2_RSSI4567_THRESHOLD_UNION
 �ṹ˵��  : R2_RSSI4567_THRESHOLD �Ĵ����ṹ���塣��ַƫ����:0x5208����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      r2_rssi4567_threshold_reg;
    struct
    {
        unsigned int  cpu_r2_rssi4_threshold : 8;  /* bit[0-7]  : RSSI ��������4����λdBm���ݲ�ʹ�ã�Ĭ��ֵΪ-1 */
        unsigned int  cpu_r2_rssi5_threshold : 8;  /* bit[8-15] : RSSI ��������5����λdBm���ݲ�ʹ�ã�Ĭ��ֵΪ-1 */
        unsigned int  cpu_r2_rssi6_threshold : 8;  /* bit[16-23]: RSSI ��������6����λdBm���ݲ�ʹ�ã�Ĭ��ֵΪ-1 */
        unsigned int  cpu_r2_rssi7_threshold : 8;  /* bit[24-31]: RSSI ��������7����λdBm���ݲ�ʹ�ã�Ĭ��ֵ-1 */
    } reg;
} GBBP_R2_RSSI4567_THRESHOLD_UNION;
#define GBBP_R2_RSSI4567_THRESHOLD_cpu_r2_rssi4_threshold_START  (0)
#define GBBP_R2_RSSI4567_THRESHOLD_cpu_r2_rssi4_threshold_END    (7)
#define GBBP_R2_RSSI4567_THRESHOLD_cpu_r2_rssi5_threshold_START  (8)
#define GBBP_R2_RSSI4567_THRESHOLD_cpu_r2_rssi5_threshold_END    (15)
#define GBBP_R2_RSSI4567_THRESHOLD_cpu_r2_rssi6_threshold_START  (16)
#define GBBP_R2_RSSI4567_THRESHOLD_cpu_r2_rssi6_threshold_END    (23)
#define GBBP_R2_RSSI4567_THRESHOLD_cpu_r2_rssi7_threshold_START  (24)
#define GBBP_R2_RSSI4567_THRESHOLD_cpu_r2_rssi7_threshold_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_AGC_WAIT_LEN_GTH_UNION
 �ṹ˵��  : AGC_WAIT_LEN_GTH �Ĵ����ṹ���塣��ַƫ����:0x520C����ֵ:0x00003008�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      agc_wait_len_gth_reg;
    struct
    {
        unsigned int  cpu_agc_wait           : 5;  /* bit[0-4]  : ����AGC��������ÿ��֮��ȴ�ʱ�䣬��λsymbol��Ĭ��8�� */
        unsigned int  reserved_0             : 3;  /* bit[5-7]  : ���� */
        unsigned int  cpu_dcr_recv_bypass    : 1;  /* bit[8]    : ���������ͨ��ֱ��ƫ������ϸ������·���ܣ��ߵ�ƽ��Ч�����ź���Чʱ����ʾ����ϸ�������Խ������ݽ��з������� */
        unsigned int  reserved_1             : 3;  /* bit[9-11] : ���� */
        unsigned int  cpu_rssi_hypersis      : 4;  /* bit[12-15]: RSSI ���ͷ�Χ����λdBm��Ĭ��3�� */
        unsigned int  reserved_2             : 8;  /* bit[16-23]: ���� */
        unsigned int  cpu_dcr_burst_mode     : 1;  /* bit[24]   : ���ͨ��ֱ��ƫ������ϸ������·���ܣ��ߵ�ƽ��Ч�����ź���Чʱ����ʾ����ϸ�������Խ������ݽ��з������� */
        unsigned int  reserved_3             : 6;  /* bit[25-30]: ���� */
        unsigned int  cpu_fast_threshold_sel : 1;  /* bit[31]   : ����AGC����ģʽѡ���ź�
                                                                  0������AGC����ģʽ���ղ�������gsp_fast_agc_modeѡ��
                                                                  1������AGC����ģʽ���ղ�������gsp_agc_measure_modeѡ�� */
    } reg;
} GBBP_AGC_WAIT_LEN_GTH_UNION;
#define GBBP_AGC_WAIT_LEN_GTH_cpu_agc_wait_START            (0)
#define GBBP_AGC_WAIT_LEN_GTH_cpu_agc_wait_END              (4)
#define GBBP_AGC_WAIT_LEN_GTH_cpu_dcr_recv_bypass_START     (8)
#define GBBP_AGC_WAIT_LEN_GTH_cpu_dcr_recv_bypass_END       (8)
#define GBBP_AGC_WAIT_LEN_GTH_cpu_rssi_hypersis_START       (12)
#define GBBP_AGC_WAIT_LEN_GTH_cpu_rssi_hypersis_END         (15)
#define GBBP_AGC_WAIT_LEN_GTH_cpu_dcr_burst_mode_START      (24)
#define GBBP_AGC_WAIT_LEN_GTH_cpu_dcr_burst_mode_END        (24)
#define GBBP_AGC_WAIT_LEN_GTH_cpu_fast_threshold_sel_START  (31)
#define GBBP_AGC_WAIT_LEN_GTH_cpu_fast_threshold_sel_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_R3_RSSI1234_THRESHOLD_UNION
 �ṹ˵��  : R3_RSSI1234_THRESHOLD �Ĵ����ṹ���塣��ַƫ����:0x5210����ֵ:0x00D3BFA3�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      r3_rssi1234_threshold_reg;
    struct
    {
        unsigned int  cpu_r3_rssi1_threshold : 8;  /* bit[0-7]  : RSSI ��������1����λdBm���Ƽ�-93 */
        unsigned int  cpu_r3_rssi2_threshold : 8;  /* bit[8-15] : RSSI ��������2����λdBm���Ƽ�-65 */
        unsigned int  cpu_r3_rssi3_threshold : 8;  /* bit[16-23]: RSSI ��������3����λdBm���Ƽ�-45 */
        unsigned int  reserved               : 8;  /* bit[24-31]: ���� */
    } reg;
} GBBP_R3_RSSI1234_THRESHOLD_UNION;
#define GBBP_R3_RSSI1234_THRESHOLD_cpu_r3_rssi1_threshold_START  (0)
#define GBBP_R3_RSSI1234_THRESHOLD_cpu_r3_rssi1_threshold_END    (7)
#define GBBP_R3_RSSI1234_THRESHOLD_cpu_r3_rssi2_threshold_START  (8)
#define GBBP_R3_RSSI1234_THRESHOLD_cpu_r3_rssi2_threshold_END    (15)
#define GBBP_R3_RSSI1234_THRESHOLD_cpu_r3_rssi3_threshold_START  (16)
#define GBBP_R3_RSSI1234_THRESHOLD_cpu_r3_rssi3_threshold_END    (23)


/*****************************************************************************
 �ṹ��    : GBBP_R3_RSSI4567_THRESHOLD_UNION
 �ṹ˵��  : R3_RSSI4567_THRESHOLD �Ĵ����ṹ���塣��ַƫ����:0x521C����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      r3_rssi4567_threshold_reg;
    struct
    {
        unsigned int  cpu_r3_rssi4_threshold : 8;  /* bit[0-7]  : RSSI ��������4����λdBm���ݲ�ʹ�ã�Ĭ��ֵΪ-1 */
        unsigned int  cpu_r3_rssi5_threshold : 8;  /* bit[8-15] : RSSI ��������5����λdBm���ݲ�ʹ�ã�Ĭ��ֵΪ-1 */
        unsigned int  cpu_r3_rssi6_threshold : 8;  /* bit[16-23]: RSSI ��������6����λdBm���ݲ�ʹ�ã�Ĭ��ֵΪ-1 */
        unsigned int  cpu_r3_rssi7_threshold : 8;  /* bit[24-31]: RSSI ��������7����λdBm���ݲ�ʹ�ã�Ĭ��ֵΪ-1 */
    } reg;
} GBBP_R3_RSSI4567_THRESHOLD_UNION;
#define GBBP_R3_RSSI4567_THRESHOLD_cpu_r3_rssi4_threshold_START  (0)
#define GBBP_R3_RSSI4567_THRESHOLD_cpu_r3_rssi4_threshold_END    (7)
#define GBBP_R3_RSSI4567_THRESHOLD_cpu_r3_rssi5_threshold_START  (8)
#define GBBP_R3_RSSI4567_THRESHOLD_cpu_r3_rssi5_threshold_END    (15)
#define GBBP_R3_RSSI4567_THRESHOLD_cpu_r3_rssi6_threshold_START  (16)
#define GBBP_R3_RSSI4567_THRESHOLD_cpu_r3_rssi6_threshold_END    (23)
#define GBBP_R3_RSSI4567_THRESHOLD_cpu_r3_rssi7_threshold_START  (24)
#define GBBP_R3_RSSI4567_THRESHOLD_cpu_r3_rssi7_threshold_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_DC_IQ_REMOVE_RPT_UNION
 �ṹ˵��  : DC_IQ_REMOVE_RPT �Ĵ����ṹ���塣��ַƫ����:0x5220����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      dc_iq_remove_rpt_reg;
    struct
    {
        unsigned int  dc_iq_remove_rpt_i : 14; /* bit[0-13] : ��·����ϸ����ƫ�üĴ���������λ���޷���������Ҳ���ǵ�ǰ��λ��ֱ��������������Ϊֱ��ƫ��У׼�Ĳο�ֵ������14bit�źŷֱ�ռ��IMI���ߵ�[29:16]��[13:0]����14bitΪI·�������14bitΪQ·����� */
        unsigned int  reserved_0         : 2;  /* bit[14-15]: ���� */
        unsigned int  dc_iq_remove_rpt_q : 14; /* bit[16-29]: ��·����ϸ����ƫ�üĴ���������λ���޷���������Ҳ���ǵ�ǰ��λ��ֱ��������������Ϊֱ��ƫ��У׼�Ĳο�ֵ������14bit�źŷֱ�ռ��IMI���ߵ�[29:16]��[13:0]����14bitΪI·�������14bitΪQ·����� */
        unsigned int  reserved_1         : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_DC_IQ_REMOVE_RPT_UNION;
#define GBBP_DC_IQ_REMOVE_RPT_dc_iq_remove_rpt_i_START  (0)
#define GBBP_DC_IQ_REMOVE_RPT_dc_iq_remove_rpt_i_END    (13)
#define GBBP_DC_IQ_REMOVE_RPT_dc_iq_remove_rpt_q_START  (16)
#define GBBP_DC_IQ_REMOVE_RPT_dc_iq_remove_rpt_q_END    (29)


/*****************************************************************************
 �ṹ��    : GBBP_DC_IQ_BURST_REMOVE_RPT_UNION
 �ṹ˵��  : DC_IQ_BURST_REMOVE_RPT �Ĵ����ṹ���塣��ַƫ����:0x5224����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      dc_iq_burst_remove_rpt_reg;
    struct
    {
        unsigned int  agc_data_i_dcr_rpt : 14; /* bit[0-13] : ʱ϶ǰ����I·ֱ��ƫ���ϱ� */
        unsigned int  reserved_0         : 2;  /* bit[14-15]: ���� */
        unsigned int  agc_data_q_dcr_rpt : 14; /* bit[16-29]: ʱ϶ǰ����Q·ֱ��ƫ���ϱ� */
        unsigned int  reserved_1         : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_DC_IQ_BURST_REMOVE_RPT_UNION;
#define GBBP_DC_IQ_BURST_REMOVE_RPT_agc_data_i_dcr_rpt_START  (0)
#define GBBP_DC_IQ_BURST_REMOVE_RPT_agc_data_i_dcr_rpt_END    (13)
#define GBBP_DC_IQ_BURST_REMOVE_RPT_agc_data_q_dcr_rpt_START  (16)
#define GBBP_DC_IQ_BURST_REMOVE_RPT_agc_data_q_dcr_rpt_END    (29)


/*****************************************************************************
 �ṹ��    : GBBP_SB_THRES_C_UNION
 �ṹ˵��  : SB_THRES_C �Ĵ����ṹ���塣��ַƫ����:0x5230����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      sb_thres_c_reg;
    struct
    {
        unsigned int  sb_thres_c : 19; /* bit[0-18] : SB���ǰ�ز�����ֵ�ϱ� */
        unsigned int  reserved   : 13; /* bit[19-31]: ���� */
    } reg;
} GBBP_SB_THRES_C_UNION;
#define GBBP_SB_THRES_C_sb_thres_c_START  (0)
#define GBBP_SB_THRES_C_sb_thres_c_END    (18)


/*****************************************************************************
 �ṹ��    : GBBP_SB_THRES_I_UNION
 �ṹ˵��  : SB_THRES_I �Ĵ����ṹ���塣��ַƫ����:0x5234����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      sb_thres_i_reg;
    struct
    {
        unsigned int  sb_thres_i : 19; /* bit[0-18] : SB���ǰ��������ֵ�ϱ� */
        unsigned int  reserved   : 13; /* bit[19-31]: ���� */
    } reg;
} GBBP_SB_THRES_I_UNION;
#define GBBP_SB_THRES_I_sb_thres_i_START  (0)
#define GBBP_SB_THRES_I_sb_thres_i_END    (18)


/*****************************************************************************
 �ṹ��    : GBBP_AAGC_NEXT_GAIN_UNION
 �ṹ˵��  : AAGC_NEXT_GAIN �Ĵ����ṹ���塣��ַƫ����:0x5250����ֵ:0x01000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      aagc_next_gain_reg;
    struct
    {
        unsigned int  aagc_next_gain_cpu : 3;  /* bit[0-2]  : AGC�����������档�ڿ���ģʽ���һ�ֺ�����ģʽ��ͳ�ƽ������ϱ���CPU�� */
        unsigned int  reserved_0         : 5;  /* bit[3-7]  : ���� */
        unsigned int  agc_rssi_125db_cpu : 12; /* bit[8-19] : RSSIֵ����λ��0.125dBm���ϱ���CPU����ֵ���ǿտڵ�RSSIֵ�� */
        unsigned int  reserved_1         : 4;  /* bit[20-23]: ���� */
        unsigned int  aagc_curr_gain     : 3;  /* bit[24-26]: ��ǰAAGC��λ�ϱ��� */
        unsigned int  reserved_2         : 4;  /* bit[27-30]: ���� */
        unsigned int  agc_fast_cal_flag  : 1;  /* bit[31]   : �����ٲ�����־��1��ʾ��ǰʱ���ٲ�����0��ʾ��ǰ�����ٲ����� */
    } reg;
} GBBP_AAGC_NEXT_GAIN_UNION;
#define GBBP_AAGC_NEXT_GAIN_aagc_next_gain_cpu_START  (0)
#define GBBP_AAGC_NEXT_GAIN_aagc_next_gain_cpu_END    (2)
#define GBBP_AAGC_NEXT_GAIN_agc_rssi_125db_cpu_START  (8)
#define GBBP_AAGC_NEXT_GAIN_agc_rssi_125db_cpu_END    (19)
#define GBBP_AAGC_NEXT_GAIN_aagc_curr_gain_START      (24)
#define GBBP_AAGC_NEXT_GAIN_aagc_curr_gain_END        (26)
#define GBBP_AAGC_NEXT_GAIN_agc_fast_cal_flag_START   (31)
#define GBBP_AAGC_NEXT_GAIN_agc_fast_cal_flag_END     (31)


/*****************************************************************************
 �ṹ��    : GBBP_RSSI_QB_FRQ_UNION
 �ṹ˵��  : RSSI_QB_FRQ �Ĵ����ṹ���塣��ַƫ����:0x5254����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      rssi_qb_frq_reg;
    struct
    {
        unsigned int  rssi_qb  : 13; /* bit[0-12] : �����ж�ʱ��TDMA֡QBֵ�� */
        unsigned int  reserved_0: 3;  /* bit[13-15]: ���� */
        unsigned int  rssi_frq : 12; /* bit[16-27]: ��ǰ������RSSI��Ӧ��Ƶ��ţ�[27:26]Ϊband�ţ�band����Ƶ�εĹ�ϵ������Լ����壬[25:16]Ϊband�ڵ�Ƶ��ţ���ֵ��GTCָ�����ã�{GSP_RSSI_FRQ_HIGH_ADDR,GSP_RSSI_FRQ_LOW_ADDR},BBP������ʱ���ڲ����ж�һ���ϱ��� */
        unsigned int  reserved_1: 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_RSSI_QB_FRQ_UNION;
#define GBBP_RSSI_QB_FRQ_rssi_qb_START   (0)
#define GBBP_RSSI_QB_FRQ_rssi_qb_END     (12)
#define GBBP_RSSI_QB_FRQ_rssi_frq_START  (16)
#define GBBP_RSSI_QB_FRQ_rssi_frq_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_DRSSI_ENERGY_RPT_UNION
 �ṹ˵��  : DRSSI_ENERGY_RPT �Ĵ����ṹ���塣��ַƫ����:0x5258����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      drssi_energy_rpt_reg;
    struct
    {
        unsigned int  drssi_energy_report_cpu : 23; /* bit[0-22] : DRSSI���������ǰ�����ϱ��� */
        unsigned int  reserved                : 9;  /* bit[23-31]: ���� */
    } reg;
} GBBP_DRSSI_ENERGY_RPT_UNION;
#define GBBP_DRSSI_ENERGY_RPT_drssi_energy_report_cpu_START  (0)
#define GBBP_DRSSI_ENERGY_RPT_drssi_energy_report_cpu_END    (22)


/*****************************************************************************
 �ṹ��    : GBBP_AGC_FAST1_2_RSSI_CPU_UNION
 �ṹ˵��  : AGC_FAST1_2_RSSI_CPU �Ĵ����ṹ���塣��ַƫ����:0x525C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      agc_fast1_2_rssi_cpu_reg;
    struct
    {
        unsigned int  agc_rssi_fast1_125db_cpu : 12; /* bit[0-11] : RSSIֵ����λ0.125dBm������ǿտ��ź�������Ϊ���ٲ�����һ��RSSI�ϱ��� */
        unsigned int  reserved_0               : 4;  /* bit[12-15]: ���� */
        unsigned int  agc_rssi_fast2_125db_cpu : 12; /* bit[16-27]: RSSIֵ����λ0.125dBm������ǿտ��ź�������Ϊ���ٲ����ڶ���RSSI�ϱ��� */
        unsigned int  reserved_1               : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_AGC_FAST1_2_RSSI_CPU_UNION;
#define GBBP_AGC_FAST1_2_RSSI_CPU_agc_rssi_fast1_125db_cpu_START  (0)
#define GBBP_AGC_FAST1_2_RSSI_CPU_agc_rssi_fast1_125db_cpu_END    (11)
#define GBBP_AGC_FAST1_2_RSSI_CPU_agc_rssi_fast2_125db_cpu_START  (16)
#define GBBP_AGC_FAST1_2_RSSI_CPU_agc_rssi_fast2_125db_cpu_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_AGC_DEC_INT_T3_FN_UNION
 �ṹ˵��  : AGC_DEC_INT_T3_FN �Ĵ����ṹ���塣��ַƫ����:0x5214����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      agc_dec_int_t3_fn_reg;
    struct
    {
        unsigned int  agc_int_tdma_fn : 6;  /* bit[0-5]  : AGC�����ж�����TDMA֡��ģ51����ֵ */
        unsigned int  reserved_0      : 10; /* bit[6-15] : ���� */
        unsigned int  dec_int_tdma_fn : 6;  /* bit[16-21]: NBҵ�������ж�����TDMA֡��ģ51����ֵ */
        unsigned int  reserved_1      : 10; /* bit[22-31]: ���� */
    } reg;
} GBBP_AGC_DEC_INT_T3_FN_UNION;
#define GBBP_AGC_DEC_INT_T3_FN_agc_int_tdma_fn_START  (0)
#define GBBP_AGC_DEC_INT_T3_FN_agc_int_tdma_fn_END    (5)
#define GBBP_AGC_DEC_INT_T3_FN_dec_int_tdma_fn_START  (16)
#define GBBP_AGC_DEC_INT_T3_FN_dec_int_tdma_fn_END    (21)


/*****************************************************************************
 �ṹ��    : GBBP_DEM_INT_FN_QB_UNION
 �ṹ˵��  : DEM_INT_FN_QB �Ĵ����ṹ���塣��ַƫ����:0x5218����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      dem_int_fn_qb_reg;
    struct
    {
        unsigned int  dem_int_tdma_qb : 13; /* bit[0-12] : ����ж�����TDMA QB����ֵ */
        unsigned int  reserved_0      : 3;  /* bit[13-15]: ���� */
        unsigned int  dem_int_tdma_fn : 6;  /* bit[16-21]: ����ж�����TDMA֡��ģ51����ֵ */
        unsigned int  reserved_1      : 10; /* bit[22-31]: ���� */
    } reg;
} GBBP_DEM_INT_FN_QB_UNION;
#define GBBP_DEM_INT_FN_QB_dem_int_tdma_qb_START  (0)
#define GBBP_DEM_INT_FN_QB_dem_int_tdma_qb_END    (12)
#define GBBP_DEM_INT_FN_QB_dem_int_tdma_fn_START  (16)
#define GBBP_DEM_INT_FN_QB_dem_int_tdma_fn_END    (21)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_EXT_LINE_CTRL_UNION
 �ṹ˵��  : CPU_EXT_LINE_CTRL �Ĵ����ṹ���塣��ַƫ����:0x5E04����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_ext_line_ctrl_reg;
    struct
    {
        unsigned int  cpu_gtc_ext_line_ctrl           : 8;  /* bit[0-7] : �����߿�CPU�ӿ����ã�����
                                                                          bit0��Ӧrf_tcvr_on,����ƵоƬ����ʹ���ź�
                                                                          bit1��Ӧrf_tx_en,����Ƶ���з��͹���ʹ���ź�
                                                                          bit2��Ӧrf_rst_n,����Ƶ��λ�����ź�
                                                                          bit3��Ӧabb_rxa_en,��ABB RXAͨ��ʹ���ź�
                                                                          bit4��Ӧabb_rxb_en,��ABB RXBͨ��ʹ���ź�
                                                                          bit5��Ӧabb_tx_en,��ABB TXͨ��ʹ���ź�
                                                                          bit6��Ӧgapc_en����Auxdacͨ��ʹ���ź� */
        unsigned int  reserved                        : 23; /* bit[8-30]: ���� */
        unsigned int  cpu_gtc_ext_line_ctrl_wr_en_imi : 1;  /* bit[31]  : 8bit�����߿��ź�дʹ��ָʾ�ź� */
    } reg;
} GBBP_CPU_EXT_LINE_CTRL_UNION;
#define GBBP_CPU_EXT_LINE_CTRL_cpu_gtc_ext_line_ctrl_START            (0)
#define GBBP_CPU_EXT_LINE_CTRL_cpu_gtc_ext_line_ctrl_END              (7)
#define GBBP_CPU_EXT_LINE_CTRL_cpu_gtc_ext_line_ctrl_wr_en_imi_START  (31)
#define GBBP_CPU_EXT_LINE_CTRL_cpu_gtc_ext_line_ctrl_wr_en_imi_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_GSP_EXT_LINE_STATE_RPT_UNION
 �ṹ˵��  : CPU_GSP_EXT_LINE_STATE_RPT �Ĵ����ṹ���塣��ַƫ����:0x5E08����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_gsp_ext_line_state_rpt_reg;
    struct
    {
        unsigned int  gtc_gsp_ext_line_ctrl : 7;  /* bit[0-6] : �����߿�ʵ��״̬�������á�
                                                                bit0��Ӧrf_tcvr_on,����ƵоƬ����ʹ���ź�
                                                                bit1��Ӧrf_tx_en,����Ƶ���з��͹���ʹ���ź�
                                                                bit2��Ӧrf_rst_n,����Ƶ��λ�����ź�
                                                                bit3��Ӧabb_rxa_en,��ABB RXAͨ��ʹ���ź�
                                                                bit4��Ӧabb_rxb_en,��ABB RXBͨ��ʹ���ź�
                                                                bit5��Ӧabb_tx_en,��ABB TXͨ��ʹ���ź�
                                                                bit6��Ӧgapc_en����Auxdacͨ��ʹ���ź� */
        unsigned int  reserved              : 25; /* bit[7-31]: ���� */
    } reg;
} GBBP_CPU_GSP_EXT_LINE_STATE_RPT_UNION;
#define GBBP_CPU_GSP_EXT_LINE_STATE_RPT_gtc_gsp_ext_line_ctrl_START  (0)
#define GBBP_CPU_GSP_EXT_LINE_STATE_RPT_gtc_gsp_ext_line_ctrl_END    (6)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_LINE01_SEL_CFG_UNION
 �ṹ˵��  : CPU_LINE01_SEL_CFG �Ĵ����ṹ���塣��ַƫ����:0x5E0C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_line01_sel_cfg_reg;
    struct
    {
        unsigned int  cpu_ext_line01_sel           : 4;  /* bit[0-3] : bit0��Ӧ��ģMIPI�ʹ�ģMIPIͨ������ѡ��
                                                                       bit1��ӦAUXDAC0��AUXDAC1����ѡ��
                                                                       bit2��ӦABB CH0��ABB CH1ͨ������ѡ������V9R1����������ABBͨ������˸�����Ĭ������Ϊ0������Ķ���
                                                                       bit3��Ӧ��ģRFIC���ģRFICͨ������ѡ��
                                                                       GΪ��ģʱ������Ϊ4��d0��GΪ��ģʱ������Ϊ4��d9�� */
        unsigned int  reserved                     : 27; /* bit[4-30]: ���� */
        unsigned int  cpu_ext_line01_sel_wr_en_imi : 1;  /* bit[31]  : cpu_line01_sel_ctrl��Ч�����źţ��������ź�дΪ1��cpu_line01_sel_ctrl��Ӧ��������Ч���߼������㡣
                                                                       ע��Ҫ��bit[3:0]�������úš� */
    } reg;
} GBBP_CPU_LINE01_SEL_CFG_UNION;
#define GBBP_CPU_LINE01_SEL_CFG_cpu_ext_line01_sel_START            (0)
#define GBBP_CPU_LINE01_SEL_CFG_cpu_ext_line01_sel_END              (3)
#define GBBP_CPU_LINE01_SEL_CFG_cpu_ext_line01_sel_wr_en_imi_START  (31)
#define GBBP_CPU_LINE01_SEL_CFG_cpu_ext_line01_sel_wr_en_imi_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_LINE01_SEL_STATE_RPT_UNION
 �ṹ˵��  : CPU_LINE01_SEL_STATE_RPT �Ĵ����ṹ���塣��ַƫ����:0x5E10����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_line01_sel_state_rpt_reg;
    struct
    {
        unsigned int  gtc_line01_sel_ctrl : 4;  /* bit[0-3] : ͨ��ѡ���ź�ʵ��״̬�������á�
                                                              bit0��gtc_mipi01_sel��
                                                              bit1��gtc_auxdac01_sel��
                                                              bit2��gtc_abb01_sel��
                                                              bit3��gtc_rf01_sel�� */
        unsigned int  reserved            : 28; /* bit[4-31]: ���� */
    } reg;
} GBBP_CPU_LINE01_SEL_STATE_RPT_UNION;
#define GBBP_CPU_LINE01_SEL_STATE_RPT_gtc_line01_sel_ctrl_START  (0)
#define GBBP_CPU_LINE01_SEL_STATE_RPT_gtc_line01_sel_ctrl_END    (3)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_OFC_RXCM_REG_UNION
 �ṹ˵��  : CPU_OFC_RXCM_REG �Ĵ����ṹ���塣��ַƫ����:0x5360����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_ofc_rxcm_reg_reg;
    struct
    {
        unsigned int  reserved               : 31; /* bit[0-30]: ���� */
        unsigned int  cpu_agc_page_switch_en : 1;  /* bit[31]  : AGCģ������ǰ��ͨ���������ֵ��RXCORR�����洢RAM��DC_OFFSET�洢RAM TDMA֡ͷƹ���л�ʹ��
                                                                 1��ʾ����ƹ���л�
                                                                 0��ʾ������ƹ���л����̶�Ϊƹҳ�������ź�Ϊ1ʱ���߼��ڲ���TDMA֡ͷ�Զ��л�ƹ�ұ�־�� */
    } reg;
} GBBP_CPU_OFC_RXCM_REG_UNION;
#define GBBP_CPU_OFC_RXCM_REG_cpu_agc_page_switch_en_START  (31)
#define GBBP_CPU_OFC_RXCM_REG_cpu_agc_page_switch_en_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_SAMPLE_REG_UNION
 �ṹ˵��  : CPU_SAMPLE_REG �Ĵ����ṹ���塣��ַƫ����:0x536C����ֵ:0x00000020�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_sample_reg_reg;
    struct
    {
        unsigned int  reserved_0               : 4;  /* bit[0-3]  : ���� */
        unsigned int  cpu_sample_sel_imi       : 2;  /* bit[4-5]  : bit1:1��ʾʱӲ�����о�ģʽ��0��ʾʱ�������ģʽ����bitΪ0ʱ��bit0�������Ч������������żѡ���źţ�0��ʾѡ����������ż·���ݣ�1��ʾѡ������������·���ݡ�����8PSK�����������2'b11����ʱ����ֵ���������á�������ģʽ����������Ϊ2'bx1ģʽ�� */
        unsigned int  reserved_1               : 2;  /* bit[6-7]  : ���� */
        unsigned int  cpu_sample_sel_group_imi : 1;  /* bit[8]    : ��������ѡ�����ã����ź���Ҫ��֡ͷ���档
                                                                    0����ʾѡ��1��symbol�е�1/3�����飻
                                                                    1����ʾѡ��1��symbol�е�2/4�����顣 */
        unsigned int  reserved_2               : 3;  /* bit[9-11] : ���� */
        unsigned int  cpu_dcr_bypass           : 1;  /* bit[12]   : ����ͨ��ֱ��ƫ������ϸ������·���ܣ��ߵ�ƽ��Ч��
                                                                    ���ź���Чʱ���൱������ϸ�������Խ������ݽ��з������� */
        unsigned int  reserved_3               : 19; /* bit[13-31]: ���� */
    } reg;
} GBBP_CPU_SAMPLE_REG_UNION;
#define GBBP_CPU_SAMPLE_REG_cpu_sample_sel_imi_START        (4)
#define GBBP_CPU_SAMPLE_REG_cpu_sample_sel_imi_END          (5)
#define GBBP_CPU_SAMPLE_REG_cpu_sample_sel_group_imi_START  (8)
#define GBBP_CPU_SAMPLE_REG_cpu_sample_sel_group_imi_END    (8)
#define GBBP_CPU_SAMPLE_REG_cpu_dcr_bypass_START            (12)
#define GBBP_CPU_SAMPLE_REG_cpu_dcr_bypass_END              (12)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_AGC_RAM_SWITCH_IND_UNION
 �ṹ˵��  : CPU_AGC_RAM_SWITCH_IND �Ĵ����ṹ���塣��ַƫ����:0x5370����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_agc_ram_switch_ind_reg;
    struct
    {
        unsigned int  cpu_agc_ram_switch_ind_imi : 1;  /* bit[0]   : AGCֱ��ƫִRAM��ͨ������RAM�ֶ��л�ָʾ�źţ����ź�Ϊ�����źţ������㡣 */
        unsigned int  reserved                   : 31; /* bit[1-31]: ���� */
    } reg;
} GBBP_CPU_AGC_RAM_SWITCH_IND_UNION;
#define GBBP_CPU_AGC_RAM_SWITCH_IND_cpu_agc_ram_switch_ind_imi_START  (0)
#define GBBP_CPU_AGC_RAM_SWITCH_IND_cpu_agc_ram_switch_ind_imi_END    (0)


/*****************************************************************************
 �ṹ��    : GBBP_DAGC_MULFACTOR_FIX_UNION
 �ṹ˵��  : DAGC_MULFACTOR_FIX �Ĵ����ṹ���塣��ַƫ����:0x537C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      dagc_mulfactor_fix_reg;
    struct
    {
        unsigned int  agc_drssi_25db_cpu      : 9;  /* bit[0-8]  : DRSSIֵ�ϱ������ӦΪABB����źŵ���������λ0.25dBm�� */
        unsigned int  reserved_0              : 7;  /* bit[9-15] : ���� */
        unsigned int  cpu_soft_agc_drssi_25db : 9;  /* bit[16-24]: ���ǿ�����õ�DRSSIֵ����λ0.25dBm�� */
        unsigned int  reserved_1              : 7;  /* bit[25-31]: ���� */
    } reg;
} GBBP_DAGC_MULFACTOR_FIX_UNION;
#define GBBP_DAGC_MULFACTOR_FIX_agc_drssi_25db_cpu_START       (0)
#define GBBP_DAGC_MULFACTOR_FIX_agc_drssi_25db_cpu_END         (8)
#define GBBP_DAGC_MULFACTOR_FIX_cpu_soft_agc_drssi_25db_START  (16)
#define GBBP_DAGC_MULFACTOR_FIX_cpu_soft_agc_drssi_25db_END    (24)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_MAIN_GAIN1_SPI_DATA_UNION
 �ṹ˵��  : CPU_MAIN_GAIN1_SPI_DATA �Ĵ����ṹ���塣��ַƫ����:0x5584����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_main_gain1_spi_data_reg;
    struct
    {
        unsigned int  cpu_main_gain1_spi_data : 24; /* bit[0-23] : �������߿�������ģʽ�µ�1��SPI�����֣�����SPI��������Ϸ�ʽ��μ������Ƶ�ֲᡣ���ּ�������ѡ��������gsp_rf_gain_word_sel�� */
        unsigned int  reserved                : 8;  /* bit[24-31]: ���� */
    } reg;
} GBBP_CPU_MAIN_GAIN1_SPI_DATA_UNION;
#define GBBP_CPU_MAIN_GAIN1_SPI_DATA_cpu_main_gain1_spi_data_START  (0)
#define GBBP_CPU_MAIN_GAIN1_SPI_DATA_cpu_main_gain1_spi_data_END    (23)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_MAIN_GAIN2_SPI_DATA_UNION
 �ṹ˵��  : CPU_MAIN_GAIN2_SPI_DATA �Ĵ����ṹ���塣��ַƫ����:0x5588����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_main_gain2_spi_data_reg;
    struct
    {
        unsigned int  cpu_main_gain2_spi_data : 24; /* bit[0-23] : �������߿�������ģʽ�µ�2��SPI�����֣�����SPI��������Ϸ�ʽ��μ������Ƶ�ֲᡣ���ּ�������ѡ��������gsp_rf_gain_word_sel�� */
        unsigned int  reserved                : 8;  /* bit[24-31]: ���� */
    } reg;
} GBBP_CPU_MAIN_GAIN2_SPI_DATA_UNION;
#define GBBP_CPU_MAIN_GAIN2_SPI_DATA_cpu_main_gain2_spi_data_START  (0)
#define GBBP_CPU_MAIN_GAIN2_SPI_DATA_cpu_main_gain2_spi_data_END    (23)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_MAIN_GAIN3_SPI_DATA_UNION
 �ṹ˵��  : CPU_MAIN_GAIN3_SPI_DATA �Ĵ����ṹ���塣��ַƫ����:0x558C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_main_gain3_spi_data_reg;
    struct
    {
        unsigned int  cpu_main_gain3_spi_data : 24; /* bit[0-23] : �������߿�������ģʽ�µ�3��SPI�����֣�����SPI��������Ϸ�ʽ��μ������Ƶ�ֲᡣ���ּ�������ѡ��������gsp_rf_gain_word_sel�� */
        unsigned int  reserved                : 8;  /* bit[24-31]: ���� */
    } reg;
} GBBP_CPU_MAIN_GAIN3_SPI_DATA_UNION;
#define GBBP_CPU_MAIN_GAIN3_SPI_DATA_cpu_main_gain3_spi_data_START  (0)
#define GBBP_CPU_MAIN_GAIN3_SPI_DATA_cpu_main_gain3_spi_data_END    (23)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_MAIN_GAIN4_SPI_DATA_UNION
 �ṹ˵��  : CPU_MAIN_GAIN4_SPI_DATA �Ĵ����ṹ���塣��ַƫ����:0x5590����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_main_gain4_spi_data_reg;
    struct
    {
        unsigned int  cpu_main_gain4_spi_data : 24; /* bit[0-23] : �������߿�������ģʽ�µ�4��SPI�����֣�����SPI��������Ϸ�ʽ��μ������Ƶ�ֲᡣ���ּ�������ѡ��������gsp_rf_gain_word_sel�� */
        unsigned int  reserved                : 8;  /* bit[24-31]: ���� */
    } reg;
} GBBP_CPU_MAIN_GAIN4_SPI_DATA_UNION;
#define GBBP_CPU_MAIN_GAIN4_SPI_DATA_cpu_main_gain4_spi_data_START  (0)
#define GBBP_CPU_MAIN_GAIN4_SPI_DATA_cpu_main_gain4_spi_data_END    (23)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_MAIN_GAIN5_SPI_DATA_UNION
 �ṹ˵��  : CPU_MAIN_GAIN5_SPI_DATA �Ĵ����ṹ���塣��ַƫ����:0x5594����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_main_gain5_spi_data_reg;
    struct
    {
        unsigned int  cpu_main_gain5_spi_data : 24; /* bit[0-23] : �������߿�������ģʽ�µ�5��SPI�����֣�����SPI��������Ϸ�ʽ��μ������Ƶ�ֲᡣ���ּ�������ѡ��������gsp_rf_gain_word_sel�� */
        unsigned int  reserved                : 8;  /* bit[24-31]: ���� */
    } reg;
} GBBP_CPU_MAIN_GAIN5_SPI_DATA_UNION;
#define GBBP_CPU_MAIN_GAIN5_SPI_DATA_cpu_main_gain5_spi_data_START  (0)
#define GBBP_CPU_MAIN_GAIN5_SPI_DATA_cpu_main_gain5_spi_data_END    (23)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_MAIN_GAIN6_SPI_DATA_UNION
 �ṹ˵��  : CPU_MAIN_GAIN6_SPI_DATA �Ĵ����ṹ���塣��ַƫ����:0x5598����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_main_gain6_spi_data_reg;
    struct
    {
        unsigned int  cpu_main_gain6_spi_data : 24; /* bit[0-23] : �������߿�������ģʽ�µ�6��SPI�����֣�����SPI��������Ϸ�ʽ��μ������Ƶ�ֲᡣ���ּ�������ѡ��������gsp_rf_gain_word_sel�� */
        unsigned int  reserved                : 8;  /* bit[24-31]: ���� */
    } reg;
} GBBP_CPU_MAIN_GAIN6_SPI_DATA_UNION;
#define GBBP_CPU_MAIN_GAIN6_SPI_DATA_cpu_main_gain6_spi_data_START  (0)
#define GBBP_CPU_MAIN_GAIN6_SPI_DATA_cpu_main_gain6_spi_data_END    (23)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_MAIN_GAIN7_SPI_DATA_UNION
 �ṹ˵��  : CPU_MAIN_GAIN7_SPI_DATA �Ĵ����ṹ���塣��ַƫ����:0x559C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_main_gain7_spi_data_reg;
    struct
    {
        unsigned int  cpu_main_gain7_spi_data : 24; /* bit[0-23] : �������߿�������ģʽ�µ�7��SPI�����֣�����SPI��������Ϸ�ʽ��μ������Ƶ�ֲᡣ���ּ�������ѡ��������gsp_rf_gain_word_sel�� */
        unsigned int  reserved                : 8;  /* bit[24-31]: ���� */
    } reg;
} GBBP_CPU_MAIN_GAIN7_SPI_DATA_UNION;
#define GBBP_CPU_MAIN_GAIN7_SPI_DATA_cpu_main_gain7_spi_data_START  (0)
#define GBBP_CPU_MAIN_GAIN7_SPI_DATA_cpu_main_gain7_spi_data_END    (23)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_MAIN_GAIN8_SPI_DATA_UNION
 �ṹ˵��  : CPU_MAIN_GAIN8_SPI_DATA �Ĵ����ṹ���塣��ַƫ����:0x55A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_main_gain8_spi_data_reg;
    struct
    {
        unsigned int  cpu_main_gain8_spi_data : 24; /* bit[0-23] : �������߿�������ģʽ�µ�8��SPI�����֣�����SPI��������Ϸ�ʽ��μ������Ƶ�ֲᡣ���ּ�������ѡ��������gsp_rf_gain_word_sel�� */
        unsigned int  reserved                : 8;  /* bit[24-31]: ���� */
    } reg;
} GBBP_CPU_MAIN_GAIN8_SPI_DATA_UNION;
#define GBBP_CPU_MAIN_GAIN8_SPI_DATA_cpu_main_gain8_spi_data_START  (0)
#define GBBP_CPU_MAIN_GAIN8_SPI_DATA_cpu_main_gain8_spi_data_END    (23)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_DIV_GAIN1_SPI_DATA_UNION
 �ṹ˵��  : CPU_DIV_GAIN1_SPI_DATA �Ĵ����ṹ���塣��ַƫ����:0x55A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_div_gain1_spi_data_reg;
    struct
    {
        unsigned int  cpu_div_gain1_spi_data : 24; /* bit[0-23] : �ּ����߿�������ģʽ�µ�1��SPI�����֣�����SPI��������Ϸ�ʽ��μ������Ƶ�ֲᡣ���ּ�������ѡ��������gsp_rf_gain_word_sel�� */
        unsigned int  reserved               : 8;  /* bit[24-31]: ���� */
    } reg;
} GBBP_CPU_DIV_GAIN1_SPI_DATA_UNION;
#define GBBP_CPU_DIV_GAIN1_SPI_DATA_cpu_div_gain1_spi_data_START  (0)
#define GBBP_CPU_DIV_GAIN1_SPI_DATA_cpu_div_gain1_spi_data_END    (23)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_DIV_GAIN2_SPI_DATA_UNION
 �ṹ˵��  : CPU_DIV_GAIN2_SPI_DATA �Ĵ����ṹ���塣��ַƫ����:0x55A8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_div_gain2_spi_data_reg;
    struct
    {
        unsigned int  cpu_div_gain2_spi_data : 24; /* bit[0-23] : �ּ����߿�������ģʽ�µ�2��SPI�����֣�����SPI��������Ϸ�ʽ��μ������Ƶ�ֲᡣ���ּ�������ѡ��������gsp_rf_gain_word_sel�� */
        unsigned int  reserved               : 8;  /* bit[24-31]: ���� */
    } reg;
} GBBP_CPU_DIV_GAIN2_SPI_DATA_UNION;
#define GBBP_CPU_DIV_GAIN2_SPI_DATA_cpu_div_gain2_spi_data_START  (0)
#define GBBP_CPU_DIV_GAIN2_SPI_DATA_cpu_div_gain2_spi_data_END    (23)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_DIV_GAIN3_SPI_DATA_UNION
 �ṹ˵��  : CPU_DIV_GAIN3_SPI_DATA �Ĵ����ṹ���塣��ַƫ����:0x55AC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_div_gain3_spi_data_reg;
    struct
    {
        unsigned int  cpu_div_gain3_spi_data : 24; /* bit[0-23] : �ּ����߿�������ģʽ�µ�3��SPI�����֣�����SPI��������Ϸ�ʽ��μ������Ƶ�ֲᡣ���ּ�������ѡ��������gsp_rf_gain_word_sel�� */
        unsigned int  reserved               : 8;  /* bit[24-31]: ���� */
    } reg;
} GBBP_CPU_DIV_GAIN3_SPI_DATA_UNION;
#define GBBP_CPU_DIV_GAIN3_SPI_DATA_cpu_div_gain3_spi_data_START  (0)
#define GBBP_CPU_DIV_GAIN3_SPI_DATA_cpu_div_gain3_spi_data_END    (23)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_DIV_GAIN4_SPI_DATA_UNION
 �ṹ˵��  : CPU_DIV_GAIN4_SPI_DATA �Ĵ����ṹ���塣��ַƫ����:0x55B0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_div_gain4_spi_data_reg;
    struct
    {
        unsigned int  cpu_div_gain4_spi_data : 24; /* bit[0-23] : �ּ����߿�������ģʽ�µ�4��SPI�����֣�����SPI��������Ϸ�ʽ��μ������Ƶ�ֲᡣ���ּ�������ѡ��������gsp_rf_gain_word_sel�� */
        unsigned int  reserved               : 8;  /* bit[24-31]: ���� */
    } reg;
} GBBP_CPU_DIV_GAIN4_SPI_DATA_UNION;
#define GBBP_CPU_DIV_GAIN4_SPI_DATA_cpu_div_gain4_spi_data_START  (0)
#define GBBP_CPU_DIV_GAIN4_SPI_DATA_cpu_div_gain4_spi_data_END    (23)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_DIV_GAIN5_SPI_DATA_UNION
 �ṹ˵��  : CPU_DIV_GAIN5_SPI_DATA �Ĵ����ṹ���塣��ַƫ����:0x55B4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_div_gain5_spi_data_reg;
    struct
    {
        unsigned int  cpu_div_gain5_spi_data : 24; /* bit[0-23] : �ּ����߿�������ģʽ�µ�5��SPI�����֣�����SPI��������Ϸ�ʽ��μ������Ƶ�ֲᡣ���ּ�������ѡ��������gsp_rf_gain_word_sel�� */
        unsigned int  reserved               : 8;  /* bit[24-31]: ���� */
    } reg;
} GBBP_CPU_DIV_GAIN5_SPI_DATA_UNION;
#define GBBP_CPU_DIV_GAIN5_SPI_DATA_cpu_div_gain5_spi_data_START  (0)
#define GBBP_CPU_DIV_GAIN5_SPI_DATA_cpu_div_gain5_spi_data_END    (23)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_DIV_GAIN6_SPI_DATA_UNION
 �ṹ˵��  : CPU_DIV_GAIN6_SPI_DATA �Ĵ����ṹ���塣��ַƫ����:0x55B8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_div_gain6_spi_data_reg;
    struct
    {
        unsigned int  cpu_div_gain6_spi_data : 24; /* bit[0-23] : �ּ����߿�������ģʽ�µ�6��SPI�����֣�����SPI��������Ϸ�ʽ��μ������Ƶ�ֲᡣ���ּ�������ѡ��������gsp_rf_gain_word_sel�� */
        unsigned int  reserved               : 8;  /* bit[24-31]: ���� */
    } reg;
} GBBP_CPU_DIV_GAIN6_SPI_DATA_UNION;
#define GBBP_CPU_DIV_GAIN6_SPI_DATA_cpu_div_gain6_spi_data_START  (0)
#define GBBP_CPU_DIV_GAIN6_SPI_DATA_cpu_div_gain6_spi_data_END    (23)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_DIV_GAIN7_SPI_DATA_UNION
 �ṹ˵��  : CPU_DIV_GAIN7_SPI_DATA �Ĵ����ṹ���塣��ַƫ����:0x55BC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_div_gain7_spi_data_reg;
    struct
    {
        unsigned int  cpu_div_gain7_spi_data : 24; /* bit[0-23] : �ּ����߿�������ģʽ�µ�7��SPI�����֣�����SPI��������Ϸ�ʽ��μ������Ƶ�ֲᡣ���ּ�������ѡ��������gsp_rf_gain_word_sel�� */
        unsigned int  reserved               : 8;  /* bit[24-31]: ���� */
    } reg;
} GBBP_CPU_DIV_GAIN7_SPI_DATA_UNION;
#define GBBP_CPU_DIV_GAIN7_SPI_DATA_cpu_div_gain7_spi_data_START  (0)
#define GBBP_CPU_DIV_GAIN7_SPI_DATA_cpu_div_gain7_spi_data_END    (23)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_DIV_GAIN8_SPI_DATA_UNION
 �ṹ˵��  : CPU_DIV_GAIN8_SPI_DATA �Ĵ����ṹ���塣��ַƫ����:0x55C0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_div_gain8_spi_data_reg;
    struct
    {
        unsigned int  cpu_div_gain8_spi_data : 24; /* bit[0-23] : �ּ����߿�������ģʽ�µ�8��SPI�����֣�����SPI��������Ϸ�ʽ��μ������Ƶ�ֲᡣ���ּ�������ѡ��������gsp_rf_gain_word_sel�� */
        unsigned int  reserved               : 8;  /* bit[24-31]: ���� */
    } reg;
} GBBP_CPU_DIV_GAIN8_SPI_DATA_UNION;
#define GBBP_CPU_DIV_GAIN8_SPI_DATA_cpu_div_gain8_spi_data_START  (0)
#define GBBP_CPU_DIV_GAIN8_SPI_DATA_cpu_div_gain8_spi_data_END    (23)


/*****************************************************************************
 �ṹ��    : GBBP_NB_AFC_LOOP_SWITCH_UNION
 �ṹ˵��  : NB_AFC_LOOP_SWITCH �Ĵ����ṹ���塣��ַƫ����:0x5340����ֵ:0x80000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      nb_afc_loop_switch_reg;
    struct
    {
        unsigned int  cpu_nb_afc_switch           : 1;  /* bit[0]   : һ�׻�����׻�ѡ������źţ�
                                                                      0��ѡ��һ�׻���
                                                                      1��ѡ����׻��� */
        unsigned int  cpu_nb_afc_slow_fast_switch : 1;  /* bit[1]   : ���׻������ٽ׶ο��ƣ�
                                                                      0����ʾ�������ٸ��٣�
                                                                      1����ʾ���ÿ��ٸ��١� */
        unsigned int  reserved                    : 29; /* bit[2-30]: ���� */
        unsigned int  cpu_nb_afc_sel              : 1;  /* bit[31]  : NB-AFC���Ʒ�ʽѡ��
                                                                      0��GTC���ƣ�
                                                                      1��CPU���ƣ�
                                                                      Ĭ��CPU���ơ� */
    } reg;
} GBBP_NB_AFC_LOOP_SWITCH_UNION;
#define GBBP_NB_AFC_LOOP_SWITCH_cpu_nb_afc_switch_START            (0)
#define GBBP_NB_AFC_LOOP_SWITCH_cpu_nb_afc_switch_END              (0)
#define GBBP_NB_AFC_LOOP_SWITCH_cpu_nb_afc_slow_fast_switch_START  (1)
#define GBBP_NB_AFC_LOOP_SWITCH_cpu_nb_afc_slow_fast_switch_END    (1)
#define GBBP_NB_AFC_LOOP_SWITCH_cpu_nb_afc_sel_START               (31)
#define GBBP_NB_AFC_LOOP_SWITCH_cpu_nb_afc_sel_END                 (31)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_AFC_K_VALUE_UNION
 �ṹ˵��  : ADDR_AFC_K_VALUE �Ĵ����ṹ���塣��ַƫ����:0x5E00����ֵ:0x00000054�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_afc_k_value_reg;
    struct
    {
        unsigned int  cpu_afc_k_factor : 10; /* bit[0-9]  : AFC Kֵ������Ĭ��ֵΪ10��d84��TCXO�����±���Ĭ��ֵ��DCXO�����¸���ʵ��ϵͳ���е����� */
        unsigned int  reserved         : 22; /* bit[10-31]: ���� */
    } reg;
} GBBP_ADDR_AFC_K_VALUE_UNION;
#define GBBP_ADDR_AFC_K_VALUE_cpu_afc_k_factor_START  (0)
#define GBBP_ADDR_AFC_K_VALUE_cpu_afc_k_factor_END    (9)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_NB_AFC_LOOP_SLOW_UNION
 �ṹ˵��  : ADDR_NB_AFC_LOOP_SLOW �Ĵ����ṹ���塣��ַƫ����:0x5E14����ֵ:0x00024661�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_nb_afc_loop_slow_reg;
    struct
    {
        unsigned int  cpu_shiftr_kint_slow : 2;  /* bit[0-1]  : ���ٵ����׶λ�·�˲���ϵ��Kint������λ����
                                                                0:8
                                                                1:9
                                                                2:10
                                                                3:11
                                                                Ĭ������:1 */
        unsigned int  reserved_0           : 2;  /* bit[2-3]  : ���� */
        unsigned int  cpu_shiftr_ki_slow   : 3;  /* bit[4-6]  : ���ٵ����׶λ�·�˲���ϵ��Ki������λ����
                                                                0:1
                                                                1:2
                                                                2:3
                                                                3:4
                                                                4:5
                                                                5:6
                                                                6:7
                                                                7:8
                                                                Ĭ������:6 */
        unsigned int  reserved_1           : 1;  /* bit[7]    : ���� */
        unsigned int  cpu_shiftl_kp_slow   : 3;  /* bit[8-10] : ���ٵ����׶λ�·�˲���ϵ��Kp������λ����
                                                                0:7
                                                                1:6
                                                                2:5
                                                                3:4
                                                                4:3
                                                                5:2
                                                                6:1
                                                                7:0
                                                                Ĭ������:6 */
        unsigned int  reserved_2           : 1;  /* bit[11]   : ���� */
        unsigned int  cpu_shiftr_ka_slow   : 3;  /* bit[12-14]: ���ٵ����׶λ�·�˲���ϵ��Ka������λ����
                                                                0��07��
                                                                1��08��
                                                                2��09��
                                                                3��10��
                                                                4��11��
                                                                5��12��
                                                                6��13��
                                                                7��14��
                                                                Ĭ�����ã�4�� */
        unsigned int  reserved_3           : 1;  /* bit[15]   : ���� */
        unsigned int  cpu_ka_slow          : 3;
        unsigned int  reserved_4           : 13; /* bit[19-31]: ���� */
    } reg;
} GBBP_ADDR_NB_AFC_LOOP_SLOW_UNION;
#define GBBP_ADDR_NB_AFC_LOOP_SLOW_cpu_shiftr_kint_slow_START  (0)
#define GBBP_ADDR_NB_AFC_LOOP_SLOW_cpu_shiftr_kint_slow_END    (1)
#define GBBP_ADDR_NB_AFC_LOOP_SLOW_cpu_shiftr_ki_slow_START    (4)
#define GBBP_ADDR_NB_AFC_LOOP_SLOW_cpu_shiftr_ki_slow_END      (6)
#define GBBP_ADDR_NB_AFC_LOOP_SLOW_cpu_shiftl_kp_slow_START    (8)
#define GBBP_ADDR_NB_AFC_LOOP_SLOW_cpu_shiftl_kp_slow_END      (10)
#define GBBP_ADDR_NB_AFC_LOOP_SLOW_cpu_shiftr_ka_slow_START    (12)
#define GBBP_ADDR_NB_AFC_LOOP_SLOW_cpu_shiftr_ka_slow_END      (14)
#define GBBP_ADDR_NB_AFC_LOOP_SLOW_cpu_ka_slow_START           (16)
#define GBBP_ADDR_NB_AFC_LOOP_SLOW_cpu_ka_slow_END             (18)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_NB_AFC_LOOP_FAST_UNION
 �ṹ˵��  : ADDR_NB_AFC_LOOP_FAST �Ĵ����ṹ���塣��ַƫ����:0x5E18����ֵ:0x00023651�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_nb_afc_loop_fast_reg;
    struct
    {
        unsigned int  cpu_shiftr_kint_fast : 2;  /* bit[0-1]  : ���ٵ����׶λ�·�˲���ϵ��Kint������λ����
                                                                0:8
                                                                1:9
                                                                2:10
                                                                3:11
                                                                Ĭ������:1 */
        unsigned int  reserved_0           : 2;  /* bit[2-3]  : ���� */
        unsigned int  cpu_shiftr_ki_fast   : 3;  /* bit[4-6]  : ���ٵ����׶λ�·�˲���ϵ��Ki������λ����
                                                                0:1
                                                                1:2
                                                                2:3
                                                                3:4
                                                                4:5
                                                                5:6
                                                                6:7
                                                                7:8
                                                                Ĭ������:1 */
        unsigned int  reserved_1           : 1;  /* bit[7]    : ���� */
        unsigned int  cpu_shiftl_kp_fast   : 3;  /* bit[8-10] : ���ٵ����׶λ�·�˲���ϵ��Kp������λ����
                                                                0:7
                                                                1:6
                                                                2:5
                                                                3:4
                                                                4:3
                                                                5:2
                                                                6:1
                                                                7:0
                                                                Ĭ������:6 */
        unsigned int  reserved_2           : 1;  /* bit[11]   : ���� */
        unsigned int  cpu_shiftr_ka_fast   : 3;  /* bit[12-14]: ���ٵ����׶λ�·�˲���ϵ��Ka������λ����
                                                                0��07��
                                                                1��08��
                                                                2��09��
                                                                3��10��
                                                                4��11��
                                                                5��12��
                                                                6��13��
                                                                7��14��
                                                                Ĭ�����ã�3�� */
        unsigned int  reserved_3           : 1;  /* bit[15]   : ���� */
        unsigned int  cpu_ka_fast          : 3;
        unsigned int  reserved_4           : 13; /* bit[19-31]: ���� */
    } reg;
} GBBP_ADDR_NB_AFC_LOOP_FAST_UNION;
#define GBBP_ADDR_NB_AFC_LOOP_FAST_cpu_shiftr_kint_fast_START  (0)
#define GBBP_ADDR_NB_AFC_LOOP_FAST_cpu_shiftr_kint_fast_END    (1)
#define GBBP_ADDR_NB_AFC_LOOP_FAST_cpu_shiftr_ki_fast_START    (4)
#define GBBP_ADDR_NB_AFC_LOOP_FAST_cpu_shiftr_ki_fast_END      (6)
#define GBBP_ADDR_NB_AFC_LOOP_FAST_cpu_shiftl_kp_fast_START    (8)
#define GBBP_ADDR_NB_AFC_LOOP_FAST_cpu_shiftl_kp_fast_END      (10)
#define GBBP_ADDR_NB_AFC_LOOP_FAST_cpu_shiftr_ka_fast_START    (12)
#define GBBP_ADDR_NB_AFC_LOOP_FAST_cpu_shiftr_ka_fast_END      (14)
#define GBBP_ADDR_NB_AFC_LOOP_FAST_cpu_ka_fast_START           (16)
#define GBBP_ADDR_NB_AFC_LOOP_FAST_cpu_ka_fast_END             (18)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_DEM_INT_FRQ_UNION
 �ṹ˵��  : ADDR_DEM_INT_FRQ �Ĵ����ṹ���塣��ַƫ����:0x5E2C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_dem_int_frq_reg;
    struct
    {
        unsigned int  dem_int_rssi_frq : 12; /* bit[0-11] : ���ν���ж�ʱ�̶�Ӧ��Ƶ�� */
        unsigned int  reserved         : 20; /* bit[12-31]: ���� */
    } reg;
} GBBP_ADDR_DEM_INT_FRQ_UNION;
#define GBBP_ADDR_DEM_INT_FRQ_dem_int_rssi_frq_START  (0)
#define GBBP_ADDR_DEM_INT_FRQ_dem_int_rssi_frq_END    (11)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_DEC_INT_FREQ_UNION
 �ṹ˵��  : ADDR_DEC_INT_FREQ �Ĵ����ṹ���塣��ַƫ����:0x5E30����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_dec_int_freq_reg;
    struct
    {
        unsigned int  dec_int_rssi_frq : 12; /* bit[0-11] : ���������ж��ϱ�ʱ�̶�Ӧ��Ƶ����Ϣ */
        unsigned int  reserved_0       : 4;  /* bit[12-15]: ���� */
        unsigned int  dec_int_tdma_qb  : 13; /* bit[16-28]: ���������ж��ϱ�ʱ�ɶ�Ӧ��TDMA QB��Ϣ */
        unsigned int  reserved_1       : 3;  /* bit[29-31]: ���� */
    } reg;
} GBBP_ADDR_DEC_INT_FREQ_UNION;
#define GBBP_ADDR_DEC_INT_FREQ_dec_int_rssi_frq_START  (0)
#define GBBP_ADDR_DEC_INT_FREQ_dec_int_rssi_frq_END    (11)
#define GBBP_ADDR_DEC_INT_FREQ_dec_int_tdma_qb_START   (16)
#define GBBP_ADDR_DEC_INT_FREQ_dec_int_tdma_qb_END     (28)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_SRCH_INT_TDMA_QB_UNION
 �ṹ˵��  : ADDR_SRCH_INT_TDMA_QB �Ĵ����ṹ���塣��ַƫ����:0x5E34����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_srch_int_tdma_qb_reg;
    struct
    {
        unsigned int  srch_tdma_qb     : 13; /* bit[0-12] : ���������ж��ϱ�ʱ�̶�Ӧ��TDMA QB */
        unsigned int  reserved_0       : 3;  /* bit[13-15]: ���� */
        unsigned int  srch_int_tdma_fn : 6;  /* bit[16-21]: [21:16] 6��b0 RO �����ж��ϱ�ʱ�̶�Ӧ��TDMA֡�ţ�gtc_t3_cnt�� */
        unsigned int  reserved_1       : 10; /* bit[22-31]: ���� */
    } reg;
} GBBP_ADDR_SRCH_INT_TDMA_QB_UNION;
#define GBBP_ADDR_SRCH_INT_TDMA_QB_srch_tdma_qb_START      (0)
#define GBBP_ADDR_SRCH_INT_TDMA_QB_srch_tdma_qb_END        (12)
#define GBBP_ADDR_SRCH_INT_TDMA_QB_srch_int_tdma_fn_START  (16)
#define GBBP_ADDR_SRCH_INT_TDMA_QB_srch_int_tdma_fn_END    (21)


/*****************************************************************************
 �ṹ��    : GBBP_VALPP_CARRIER_ENERGY4_UNION
 �ṹ˵��  : VALPP_CARRIER_ENERGY4 �Ĵ����ṹ���塣��ַƫ����:0x532C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_carrier_energy4_reg;
    struct
    {
        unsigned int  valpp_carrier_energy_4d_cpu : 31; /* bit[0-30]: ��ȡʱ��ǰ�����burst��Ӧ���ز�����ֵ���޷������� */
        unsigned int  reserved                    : 1;  /* bit[31]  : ���� */
    } reg;
} GBBP_VALPP_CARRIER_ENERGY4_UNION;
#define GBBP_VALPP_CARRIER_ENERGY4_valpp_carrier_energy_4d_cpu_START  (0)
#define GBBP_VALPP_CARRIER_ENERGY4_valpp_carrier_energy_4d_cpu_END    (30)


/*****************************************************************************
 �ṹ��    : GBBP_VALPP_INTERFERE_ENERGY4_UNION
 �ṹ˵��  : VALPP_INTERFERE_ENERGY4 �Ĵ����ṹ���塣��ַƫ����:0x5330����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_interfere_energy4_reg;
    struct
    {
        unsigned int  valpp_interfere_energy_4d_cpu : 26; /* bit[0-25] : ��ȡʱ��ǰ�����burst��Ӧ�ĸ�������ֵ���޷������� */
        unsigned int  reserved                      : 6;  /* bit[26-31]: ���� */
    } reg;
} GBBP_VALPP_INTERFERE_ENERGY4_UNION;
#define GBBP_VALPP_INTERFERE_ENERGY4_valpp_interfere_energy_4d_cpu_START  (0)
#define GBBP_VALPP_INTERFERE_ENERGY4_valpp_interfere_energy_4d_cpu_END    (25)


/*****************************************************************************
 �ṹ��    : GBBP_VALPP_DEM_TYPE_TOA4_UNION
 �ṹ˵��  : VALPP_DEM_TYPE_TOA4 �Ĵ����ṹ���塣��ַƫ����:0x5298����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_dem_type_toa4_reg;
    struct
    {
        unsigned int  reserved_0                     : 14; /* bit[0-13] : ���� */
        unsigned int  mod_type_5d                    : 2;  /* bit[14-15]: ��ȡʱ�̵����BURST�ĵ��Ʒ�ʽ��
                                                                          0��GSKM��
                                                                          1��8PSK��
                                                                          2��DummyBurst�� */
        unsigned int  nb_pos_adj_cpu_sav4            : 4;  /* bit[16-19]: ��ȡʱ�̵�������burst��Ӧ��NBλ�õ��������ǲ����ʾ���з�������������ʾ��ǰ������������ʾ����������Χ��-4~+4�� */
        unsigned int  demod_slot_5d                  : 3;  /* bit[20-22]: ��ȡʱ�̵�������burst��Ӧ��ʱ϶�ţ���ʱ϶����PHYͨ��GTCָ������������BBP��ʱ������жϴ������ϱ��� */
        unsigned int  reserved_1                     : 1;  /* bit[23]   : ���� */
        unsigned int  nserv_cell_ind_5d              : 1;  /* bit[24]   : ��ȡʱ�̵����burst�Ƿ�Ϊ�Ƿ�����ָʾ��1��ʾ�Ƿ�������0��ʾ��������Ĭ��ֵΪ0����ֵ��PHYͨ��GTCָ������������BBP��ʱ������жϴ������ϱ��� */
        unsigned int  reserved_2                     : 3;  /* bit[25-27]: ���� */
        unsigned int  mod_type_first_5d              : 2;  /* bit[28-29]: ��ȡʱ��ǰ�ĵ����BURST��Ӧ��һ���о��ĵ��Ʒ�ʽ��
                                                                          0��GMSK���ƣ�
                                                                          1��8PSK���ƣ�
                                                                          2��DummyBurst��
                                                                          �üĴ�������ʹ�á� */
        unsigned int  demod_info_valid_flag4_clr_imi : 1;  /* bit[30]   : ��demod_info_valid_flag4���㡣д1���㡣 */
        unsigned int  demod_info_valid_flag4         : 1;  /* bit[31]   : ��ȡʱ�̵���������Ϣ��Ч��־�������һ��NB���ʱ���ñ�־��1,CPU��ȡ���BURST����ϱ���Ϣ��Ӧ��ͨ��дbit30�Ը�bit���㣬ָʾ����Ϣ�Ѿ���ȡ�� */
    } reg;
} GBBP_VALPP_DEM_TYPE_TOA4_UNION;
#define GBBP_VALPP_DEM_TYPE_TOA4_mod_type_5d_START                     (14)
#define GBBP_VALPP_DEM_TYPE_TOA4_mod_type_5d_END                       (15)
#define GBBP_VALPP_DEM_TYPE_TOA4_nb_pos_adj_cpu_sav4_START             (16)
#define GBBP_VALPP_DEM_TYPE_TOA4_nb_pos_adj_cpu_sav4_END               (19)
#define GBBP_VALPP_DEM_TYPE_TOA4_demod_slot_5d_START                   (20)
#define GBBP_VALPP_DEM_TYPE_TOA4_demod_slot_5d_END                     (22)
#define GBBP_VALPP_DEM_TYPE_TOA4_nserv_cell_ind_5d_START               (24)
#define GBBP_VALPP_DEM_TYPE_TOA4_nserv_cell_ind_5d_END                 (24)
#define GBBP_VALPP_DEM_TYPE_TOA4_mod_type_first_5d_START               (28)
#define GBBP_VALPP_DEM_TYPE_TOA4_mod_type_first_5d_END                 (29)
#define GBBP_VALPP_DEM_TYPE_TOA4_demod_info_valid_flag4_clr_imi_START  (30)
#define GBBP_VALPP_DEM_TYPE_TOA4_demod_info_valid_flag4_clr_imi_END    (30)
#define GBBP_VALPP_DEM_TYPE_TOA4_demod_info_valid_flag4_START          (31)
#define GBBP_VALPP_DEM_TYPE_TOA4_demod_info_valid_flag4_END            (31)


/*****************************************************************************
 �ṹ��    : GBBP_VALPP_CARRIER_ENERGY5_UNION
 �ṹ˵��  : VALPP_CARRIER_ENERGY5 �Ĵ����ṹ���塣��ַƫ����:0x5334����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_carrier_energy5_reg;
    struct
    {
        unsigned int  valpp_carrier_energy_5d_cpu : 31; /* bit[0-30]: ��ȡʱ��ǰ������burst��Ӧ���ز�����ֵ���޷������� */
        unsigned int  reserved                    : 1;  /* bit[31]  : ���� */
    } reg;
} GBBP_VALPP_CARRIER_ENERGY5_UNION;
#define GBBP_VALPP_CARRIER_ENERGY5_valpp_carrier_energy_5d_cpu_START  (0)
#define GBBP_VALPP_CARRIER_ENERGY5_valpp_carrier_energy_5d_cpu_END    (30)


/*****************************************************************************
 �ṹ��    : GBBP_VALPP_INTERFERE_ENERGY5_UNION
 �ṹ˵��  : VALPP_INTERFERE_ENERGY5 �Ĵ����ṹ���塣��ַƫ����:0x5338����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_interfere_energy5_reg;
    struct
    {
        unsigned int  valpp_interfere_energy_5d_cpu : 26; /* bit[0-25] : ��ȡʱ��ǰ������burst��Ӧ�ĸ�������ֵ���޷������� */
        unsigned int  reserved                      : 6;  /* bit[26-31]: ���� */
    } reg;
} GBBP_VALPP_INTERFERE_ENERGY5_UNION;
#define GBBP_VALPP_INTERFERE_ENERGY5_valpp_interfere_energy_5d_cpu_START  (0)
#define GBBP_VALPP_INTERFERE_ENERGY5_valpp_interfere_energy_5d_cpu_END    (25)


/*****************************************************************************
 �ṹ��    : GBBP_VALPP_DEM_TYPE_TOA5_UNION
 �ṹ˵��  : VALPP_DEM_TYPE_TOA5 �Ĵ����ṹ���塣��ַƫ����:0x533C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      valpp_dem_type_toa5_reg;
    struct
    {
        unsigned int  reserved_0                     : 14; /* bit[0-13] : ���� */
        unsigned int  mod_type_6d                    : 2;  /* bit[14-15]: ��ȡʱ�̵�����BURST�ĵ��Ʒ�ʽ��
                                                                          0��GSKM��
                                                                          1��8PSK��
                                                                          2��DummyBurst�� */
        unsigned int  nb_pos_adj_cpu_sav5            : 4;  /* bit[16-19]: ��ȡʱ�̵��������burst��Ӧ��NBλ�õ��������ǲ����ʾ���з�������������ʾ��ǰ������������ʾ����������Χ��-4~+4�� */
        unsigned int  demod_slot_6d                  : 3;  /* bit[20-22]: ��ȡʱ�̵��������burst��Ӧ��ʱ϶�ţ���ʱ϶����PHYͨ��GTCָ������������BBP��ʱ������жϴ������ϱ��� */
        unsigned int  reserved_1                     : 1;  /* bit[23]   : ���� */
        unsigned int  nserv_cell_ind_6d              : 1;  /* bit[24]   : ��ȡʱ�̵�����burst�Ƿ�Ϊ�Ƿ�����ָʾ��1��ʾ�Ƿ�������0��ʾ��������Ĭ��ֵΪ0����ֵ��PHYͨ��GTCָ������������BBP��ʱ������жϴ������ϱ��� */
        unsigned int  reserved_2                     : 3;  /* bit[25-27]: ���� */
        unsigned int  mod_type_first_6d              : 2;  /* bit[28-29]: ��ȡʱ��ǰ�ĵ�����BURST��Ӧ��һ���о��ĵ��Ʒ�ʽ��
                                                                          0��GMSK���ƣ�
                                                                          1��8PSK���ƣ�
                                                                          2��DummyBurst��
                                                                          �üĴ�������ʹ�á� */
        unsigned int  demod_info_valid_flag5_clr_imi : 1;  /* bit[30]   : ��demod_info_valid_flag5���㡣д1���㡣 */
        unsigned int  demod_info_valid_flag5         : 1;  /* bit[31]   : ��ȡʱ�̵����������Ϣ��Ч��־�������һ��NB���ʱ���ñ�־��1,CPU��ȡ���BURST����ϱ���Ϣ��Ӧ��ͨ��bit30�Ը�bit���㣬ָʾ����Ϣ�Ѿ���ȡ�� */
    } reg;
} GBBP_VALPP_DEM_TYPE_TOA5_UNION;
#define GBBP_VALPP_DEM_TYPE_TOA5_mod_type_6d_START                     (14)
#define GBBP_VALPP_DEM_TYPE_TOA5_mod_type_6d_END                       (15)
#define GBBP_VALPP_DEM_TYPE_TOA5_nb_pos_adj_cpu_sav5_START             (16)
#define GBBP_VALPP_DEM_TYPE_TOA5_nb_pos_adj_cpu_sav5_END               (19)
#define GBBP_VALPP_DEM_TYPE_TOA5_demod_slot_6d_START                   (20)
#define GBBP_VALPP_DEM_TYPE_TOA5_demod_slot_6d_END                     (22)
#define GBBP_VALPP_DEM_TYPE_TOA5_nserv_cell_ind_6d_START               (24)
#define GBBP_VALPP_DEM_TYPE_TOA5_nserv_cell_ind_6d_END                 (24)
#define GBBP_VALPP_DEM_TYPE_TOA5_mod_type_first_6d_START               (28)
#define GBBP_VALPP_DEM_TYPE_TOA5_mod_type_first_6d_END                 (29)
#define GBBP_VALPP_DEM_TYPE_TOA5_demod_info_valid_flag5_clr_imi_START  (30)
#define GBBP_VALPP_DEM_TYPE_TOA5_demod_info_valid_flag5_clr_imi_END    (30)
#define GBBP_VALPP_DEM_TYPE_TOA5_demod_info_valid_flag5_START          (31)
#define GBBP_VALPP_DEM_TYPE_TOA5_demod_info_valid_flag5_END            (31)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_JITTER_CORR_CFG1_UNION
 �ṹ˵��  : CPU_JITTER_CORR_CFG1 �Ĵ����ṹ���塣��ַƫ����:0x53B4����ֵ:0x80000303�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_jitter_corr_cfg1_reg;
    struct
    {
        unsigned int  cpu_jitter_on_ci_thresh : 3;  /* bit[0-2]  : ���������ڽ��ģ���ڲ����о��Ƿ�����ƫ ��Ӧ��·�ź���CIThreshold��Ĭ��ֵ10��
                                                                   ��ѡֵ7,8,9,10,11,12,13��
                                                                   CPU��ֵ��Ӧ��ϵ��0-6�� */
        unsigned int  reserved_0              : 5;  /* bit[3-7]  : ���� */
        unsigned int  cpu_energy_thresh       : 3;  /* bit[8-10] : ���ģ���ã���ƫ״̬��һ����״̬���о��Ƿ������ƫ����. ��Ӧ��·�ź��� EnergyThreshold����Ĭ��ֵ12�����壺ͨ���ŵ����Ƽ���ȫ�������Ͳ�����������ѡֵ9,10, 11,12,13,14,15��
                                                                   CPU��ֵ��Ӧ��ϵ��0-6�� */
        unsigned int  reserved_1              : 12; /* bit[11-22]: ���� */
        unsigned int  cpu_sin_factor          : 1;  /* bit[23]   : SBƵƫֵ�������ӣ�0��ʾϵ��Ϊ1.25��1��ʾϵ��Ϊ1 */
        unsigned int  reserved_2              : 6;  /* bit[24-29]: ���� */
        unsigned int  cpu_sb_freq_corr_en     : 1;  /* bit[30]   : SB��ƫʹ���źţ�0��ʾ�ر�Ƶƫ��⼰��ƫ��1��ʾ�򿪡�
                                                                   V9R1/V3R3��֧�ָù��ܣ���������Ϊ0�� */
        unsigned int  cpu_freq_corr_en        : 1;  /* bit[31]   : NB��ƫʹ���źţ�0��ʾ�ر�Ƶƫ��⼰��ƫ��1��ʾ�򿪡�Ĭ��Ϊ0�� */
    } reg;
} GBBP_CPU_JITTER_CORR_CFG1_UNION;
#define GBBP_CPU_JITTER_CORR_CFG1_cpu_jitter_on_ci_thresh_START  (0)
#define GBBP_CPU_JITTER_CORR_CFG1_cpu_jitter_on_ci_thresh_END    (2)
#define GBBP_CPU_JITTER_CORR_CFG1_cpu_energy_thresh_START        (8)
#define GBBP_CPU_JITTER_CORR_CFG1_cpu_energy_thresh_END          (10)
#define GBBP_CPU_JITTER_CORR_CFG1_cpu_sin_factor_START           (23)
#define GBBP_CPU_JITTER_CORR_CFG1_cpu_sin_factor_END             (23)
#define GBBP_CPU_JITTER_CORR_CFG1_cpu_sb_freq_corr_en_START      (30)
#define GBBP_CPU_JITTER_CORR_CFG1_cpu_sb_freq_corr_en_END        (30)
#define GBBP_CPU_JITTER_CORR_CFG1_cpu_freq_corr_en_START         (31)
#define GBBP_CPU_JITTER_CORR_CFG1_cpu_freq_corr_en_END           (31)


/*****************************************************************************
 �ṹ��    : GBBP_PHI_DEV_CPU_UNION
 �ṹ˵��  : PHI_DEV_CPU �Ĵ����ṹ���塣��ַƫ����:0x53B8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      phi_dev_cpu_reg;
    struct
    {
        unsigned int  phi_dev_cpu    : 15; /* bit[0-14] : JITTER ON�����㷨��ǰƵƫ�ϱ� */
        unsigned int  reserved_0     : 1;  /* bit[15]   : ���� */
        unsigned int  sb_phi_dev_cpu : 15; /* bit[16-30]: SB jitterOn�㷨��ǰƵƫ�ϱ� */
        unsigned int  reserved_1     : 1;  /* bit[31]   : ���� */
    } reg;
} GBBP_PHI_DEV_CPU_UNION;
#define GBBP_PHI_DEV_CPU_phi_dev_cpu_START     (0)
#define GBBP_PHI_DEV_CPU_phi_dev_cpu_END       (14)
#define GBBP_PHI_DEV_CPU_sb_phi_dev_cpu_START  (16)
#define GBBP_PHI_DEV_CPU_sb_phi_dev_cpu_END    (30)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_JITTER_CORR_CFG2_UNION
 �ṹ˵��  : CPU_JITTER_CORR_CFG2 �Ĵ����ṹ���塣��ַƫ����:0x53BC����ֵ:0x80140702�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_jitter_corr_cfg2_reg;
    struct
    {
        unsigned int  cpu_snr_thresh     : 3;  /* bit[0-2]  : ��Ӧ����·�е�SNR_THRES�����ڼ����ƫ��Χ fr_off_lim_act���Լ���������, Ĭ��ֵ100, ȡֵ��Χ90 95 100 105 110,CPU��ֵ��Ӧ0��4 */
        unsigned int  reserved_0         : 5;  /* bit[3-7]  : ���� */
        unsigned int  cpu_froff_lim_step : 4;  /* bit[8-11] : ��Ӧ����·�е�FrOffLim_STEP��ȡֵ��Χ5 6 7 8 9��Ĭ��ֵ��7 */
        unsigned int  reserved_1         : 4;  /* bit[12-15]: ���� */
        unsigned int  cpu_frmoff_lim     : 5;  /* bit[16-20]: �����оƬ���ã���ƫ���޷�����Ӧ��·�ź� FrOffLim ��Ĭ��ֵ20����ѡֵ14,16,18,20,22, 24�� */
        unsigned int  reserved_2         : 10; /* bit[21-30]: ���� */
        unsigned int  cpu_feed_back_en   : 1;  /* bit[31]   : NBƵƫУ׼��Χ�̳�ʹ�ܣ�Ĭ��ֵ��1�� */
    } reg;
} GBBP_CPU_JITTER_CORR_CFG2_UNION;
#define GBBP_CPU_JITTER_CORR_CFG2_cpu_snr_thresh_START      (0)
#define GBBP_CPU_JITTER_CORR_CFG2_cpu_snr_thresh_END        (2)
#define GBBP_CPU_JITTER_CORR_CFG2_cpu_froff_lim_step_START  (8)
#define GBBP_CPU_JITTER_CORR_CFG2_cpu_froff_lim_step_END    (11)
#define GBBP_CPU_JITTER_CORR_CFG2_cpu_frmoff_lim_START      (16)
#define GBBP_CPU_JITTER_CORR_CFG2_cpu_frmoff_lim_END        (20)
#define GBBP_CPU_JITTER_CORR_CFG2_cpu_feed_back_en_START    (31)
#define GBBP_CPU_JITTER_CORR_CFG2_cpu_feed_back_en_END      (31)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_TSC_SWITCH_EN_UNION
 �ṹ˵��  : CPU_TSC_SWITCH_EN �Ĵ����ṹ���塣��ַƫ����:0x53C4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_tsc_switch_en_reg;
    struct
    {
        unsigned int  cpu_tsc_page_switch_en : 1;  /* bit[0]   : ������ģʽ����Ӧ����жϺ��ȡѵ�����������ϱ�RAM���ϱ����ƿ���,��ʱ϶����ʹ��ƹ�Ҳ���ģʽ
                                                                 1��ʾCPU����ѵ�����������ϱ�RAM����ƹ��RAM����ģʽ��
                                                                 0��ʾCPU����ѵ�����������ϱ�RAM���÷�ƹ��RAM����ģʽ */
        unsigned int  reserved               : 31; /* bit[1-31]: ���� */
    } reg;
} GBBP_CPU_TSC_SWITCH_EN_UNION;
#define GBBP_CPU_TSC_SWITCH_EN_cpu_tsc_page_switch_en_START  (0)
#define GBBP_CPU_TSC_SWITCH_EN_cpu_tsc_page_switch_en_END    (0)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_FILTER0_P0_P1_UNION
 �ṹ˵��  : CPU_FILTER0_P0_P1 �Ĵ����ṹ���塣��ַƫ����:0x5800����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_filter0_p0_p1_reg;
    struct
    {
        unsigned int  cpu_filter0_p0_i : 14; /* bit[0-13] : �˲���0��I·����p0��Ĭ��ֵ��14'd0�� */
        unsigned int  reserved_0       : 2;  /* bit[14-15]: ���� */
        unsigned int  cpu_filter0_p1_i : 14; /* bit[16-29]: �˲���0��I·����p1��Ĭ��ֵ��14'd0�� */
        unsigned int  reserved_1       : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_CPU_FILTER0_P0_P1_UNION;
#define GBBP_CPU_FILTER0_P0_P1_cpu_filter0_p0_i_START  (0)
#define GBBP_CPU_FILTER0_P0_P1_cpu_filter0_p0_i_END    (13)
#define GBBP_CPU_FILTER0_P0_P1_cpu_filter0_p1_i_START  (16)
#define GBBP_CPU_FILTER0_P0_P1_cpu_filter0_p1_i_END    (29)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_FILTER0_P2_P3_UNION
 �ṹ˵��  : CPU_FILTER0_P2_P3 �Ĵ����ṹ���塣��ַƫ����:0x5804����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_filter0_p2_p3_reg;
    struct
    {
        unsigned int  cpu_filter0_p2_i : 14; /* bit[0-13] : �˲���0��I·����p2��Ĭ��ֵ��14'd0�� */
        unsigned int  reserved_0       : 2;  /* bit[14-15]: ���� */
        unsigned int  cpu_filter0_p3_i : 14; /* bit[16-29]: �˲���0��I·����p3��Ĭ��ֵ��14'd0�� */
        unsigned int  reserved_1       : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_CPU_FILTER0_P2_P3_UNION;
#define GBBP_CPU_FILTER0_P2_P3_cpu_filter0_p2_i_START  (0)
#define GBBP_CPU_FILTER0_P2_P3_cpu_filter0_p2_i_END    (13)
#define GBBP_CPU_FILTER0_P2_P3_cpu_filter0_p3_i_START  (16)
#define GBBP_CPU_FILTER0_P2_P3_cpu_filter0_p3_i_END    (29)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_FILTER0_P4_P5_UNION
 �ṹ˵��  : CPU_FILTER0_P4_P5 �Ĵ����ṹ���塣��ַƫ����:0x5808����ֵ:0x10000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_filter0_p4_p5_reg;
    struct
    {
        unsigned int  cpu_filter0_p4_i : 14; /* bit[0-13] : �˲���0��I·����p4��Ĭ��ֵ��14'd0�� */
        unsigned int  reserved_0       : 2;  /* bit[14-15]: ���� */
        unsigned int  cpu_filter0_p5_i : 14; /* bit[16-29]: �˲���0��I·����p5��Ĭ��ֵ��14'd4096�� */
        unsigned int  reserved_1       : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_CPU_FILTER0_P4_P5_UNION;
#define GBBP_CPU_FILTER0_P4_P5_cpu_filter0_p4_i_START  (0)
#define GBBP_CPU_FILTER0_P4_P5_cpu_filter0_p4_i_END    (13)
#define GBBP_CPU_FILTER0_P4_P5_cpu_filter0_p5_i_START  (16)
#define GBBP_CPU_FILTER0_P4_P5_cpu_filter0_p5_i_END    (29)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_FILTER3_P0_P1_UNION
 �ṹ˵��  : CPU_FILTER3_P0_P1 �Ĵ����ṹ���塣��ַƫ����:0x580C����ֵ:0x3F8F3F59�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_filter3_p0_p1_reg;
    struct
    {
        unsigned int  cpu_filter3_p0_i : 14; /* bit[0-13] : �˲���3��I·����p0��Ĭ��ֵ��-14'd167�� */
        unsigned int  reserved_0       : 2;  /* bit[14-15]: ���� */
        unsigned int  cpu_filter3_p1_i : 14; /* bit[16-29]: �˲���3��I·����p1��Ĭ��ֵ��-14'd113�� */
        unsigned int  reserved_1       : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_CPU_FILTER3_P0_P1_UNION;
#define GBBP_CPU_FILTER3_P0_P1_cpu_filter3_p0_i_START  (0)
#define GBBP_CPU_FILTER3_P0_P1_cpu_filter3_p0_i_END    (13)
#define GBBP_CPU_FILTER3_P0_P1_cpu_filter3_p1_i_START  (16)
#define GBBP_CPU_FILTER3_P0_P1_cpu_filter3_p1_i_END    (29)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_FILTER3_P2_P3_UNION
 �ṹ˵��  : CPU_FILTER3_P2_P3 �Ĵ����ṹ���塣��ַƫ����:0x5810����ֵ:0x03FA3EEF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_filter3_p2_p3_reg;
    struct
    {
        unsigned int  cpu_filter3_p2_i : 14; /* bit[0-13] : �˲���3��I·����p2��Ĭ��ֵ��-14'd273�� */
        unsigned int  reserved_0       : 2;  /* bit[14-15]: ���� */
        unsigned int  cpu_filter3_p3_i : 14; /* bit[16-29]: �˲���3��I·����p3��Ĭ��ֵ��14'd1018�� */
        unsigned int  reserved_1       : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_CPU_FILTER3_P2_P3_UNION;
#define GBBP_CPU_FILTER3_P2_P3_cpu_filter3_p2_i_START  (0)
#define GBBP_CPU_FILTER3_P2_P3_cpu_filter3_p2_i_END    (13)
#define GBBP_CPU_FILTER3_P2_P3_cpu_filter3_p3_i_START  (16)
#define GBBP_CPU_FILTER3_P2_P3_cpu_filter3_p3_i_END    (29)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_FILTER3_P4_P5_UNION
 �ṹ˵��  : CPU_FILTER3_P4_P5 �Ĵ����ṹ���塣��ַƫ����:0x5814����ֵ:0x08B40179�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_filter3_p4_p5_reg;
    struct
    {
        unsigned int  cpu_filter3_p4_i : 14; /* bit[0-13] : �˲���3��I·����p4��Ĭ��ֵ��14'd377�� */
        unsigned int  reserved_0       : 2;  /* bit[14-15]: ���� */
        unsigned int  cpu_filter3_p5_i : 14; /* bit[16-29]: �˲���3��I·����p5��Ĭ��ֵ��14'd2228�� */
        unsigned int  reserved_1       : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_CPU_FILTER3_P4_P5_UNION;
#define GBBP_CPU_FILTER3_P4_P5_cpu_filter3_p4_i_START  (0)
#define GBBP_CPU_FILTER3_P4_P5_cpu_filter3_p4_i_END    (13)
#define GBBP_CPU_FILTER3_P4_P5_cpu_filter3_p5_i_START  (16)
#define GBBP_CPU_FILTER3_P4_P5_cpu_filter3_p5_i_END    (29)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_FILTER1_P0_P1_I_UNION
 �ṹ˵��  : CPU_FILTER1_P0_P1_I �Ĵ����ṹ���塣��ַƫ����:0x5818����ֵ:0x00A80011�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_filter1_p0_p1_i_reg;
    struct
    {
        unsigned int  cpu_filter1_p0_i : 14; /* bit[0-13] : �˲���1��I·����p0��Ĭ��ֵ��14'd17�� */
        unsigned int  reserved_0       : 2;  /* bit[14-15]: ���� */
        unsigned int  cpu_filter1_p1_i : 14; /* bit[16-29]: �˲���1��I·����p1��Ĭ��ֵ��14'd168�� */
        unsigned int  reserved_1       : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_CPU_FILTER1_P0_P1_I_UNION;
#define GBBP_CPU_FILTER1_P0_P1_I_cpu_filter1_p0_i_START  (0)
#define GBBP_CPU_FILTER1_P0_P1_I_cpu_filter1_p0_i_END    (13)
#define GBBP_CPU_FILTER1_P0_P1_I_cpu_filter1_p1_i_START  (16)
#define GBBP_CPU_FILTER1_P0_P1_I_cpu_filter1_p1_i_END    (29)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_FILTER1_P2_P3_I_UNION
 �ṹ˵��  : CPU_FILTER1_P2_P3_I �Ĵ����ṹ���塣��ַƫ����:0x581C����ֵ:0x00B90016�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_filter1_p2_p3_i_reg;
    struct
    {
        unsigned int  cpu_filter1_p2_i : 14; /* bit[0-13] : �˲���1��I·����p2��Ĭ��ֵ��14'd22�� */
        unsigned int  reserved_0       : 2;  /* bit[14-15]: ���� */
        unsigned int  cpu_filter1_p3_i : 14; /* bit[16-29]: �˲���1��I·����p3��Ĭ��ֵ��14'd185�� */
        unsigned int  reserved_1       : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_CPU_FILTER1_P2_P3_I_UNION;
#define GBBP_CPU_FILTER1_P2_P3_I_cpu_filter1_p2_i_START  (0)
#define GBBP_CPU_FILTER1_P2_P3_I_cpu_filter1_p2_i_END    (13)
#define GBBP_CPU_FILTER1_P2_P3_I_cpu_filter1_p3_i_START  (16)
#define GBBP_CPU_FILTER1_P2_P3_I_cpu_filter1_p3_i_END    (29)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_FILTER1_P4_P5_I_UNION
 �ṹ˵��  : CPU_FILTER1_P4_P5_I �Ĵ����ṹ���塣��ַƫ����:0x5820����ֵ:0x06CA045C�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_filter1_p4_p5_i_reg;
    struct
    {
        unsigned int  cpu_filter1_p4_i : 14; /* bit[0-13] : �˲���1��I·����p4��Ĭ��ֵ��14'd1116�� */
        unsigned int  reserved_0       : 2;  /* bit[14-15]: ���� */
        unsigned int  cpu_filter1_p5_i : 14; /* bit[16-29]: �˲���1��I·����p5��Ĭ��ֵ��14'd1738�� */
        unsigned int  reserved_1       : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_CPU_FILTER1_P4_P5_I_UNION;
#define GBBP_CPU_FILTER1_P4_P5_I_cpu_filter1_p4_i_START  (0)
#define GBBP_CPU_FILTER1_P4_P5_I_cpu_filter1_p4_i_END    (13)
#define GBBP_CPU_FILTER1_P4_P5_I_cpu_filter1_p5_i_START  (16)
#define GBBP_CPU_FILTER1_P4_P5_I_cpu_filter1_p5_i_END    (29)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_FILTER1_P0_P1_Q_UNION
 �ṹ˵��  : CPU_FILTER1_P0_P1_Q �Ĵ����ṹ���塣��ַƫ����:0x5824����ֵ:0x00DB0006�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_filter1_p0_p1_q_reg;
    struct
    {
        unsigned int  cpu_filter1_p0_q : 14; /* bit[0-13] : �˲���1��Q·����p0��Ĭ��ֵ��14'd6�� */
        unsigned int  reserved_0       : 2;  /* bit[14-15]: ���� */
        unsigned int  cpu_filter1_p1_q : 14; /* bit[16-29]: �˲���1��Q·����p1��Ĭ��ֵ��14'd219�� */
        unsigned int  reserved_1       : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_CPU_FILTER1_P0_P1_Q_UNION;
#define GBBP_CPU_FILTER1_P0_P1_Q_cpu_filter1_p0_q_START  (0)
#define GBBP_CPU_FILTER1_P0_P1_Q_cpu_filter1_p0_q_END    (13)
#define GBBP_CPU_FILTER1_P0_P1_Q_cpu_filter1_p1_q_START  (16)
#define GBBP_CPU_FILTER1_P0_P1_Q_cpu_filter1_p1_q_END    (29)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_FILTER1_P2_P3_Q_UNION
 �ṹ˵��  : CPU_FILTER1_P2_P3_Q �Ĵ����ṹ���塣��ַƫ����:0x5828����ֵ:0x3E8700DB�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_filter1_p2_p3_q_reg;
    struct
    {
        unsigned int  cpu_filter1_p2_q : 14; /* bit[0-13] : �˲���1��Q·����p2��Ĭ��ֵ��14'd219�� */
        unsigned int  reserved_0       : 2;  /* bit[14-15]: ���� */
        unsigned int  cpu_filter1_p3_q : 14; /* bit[16-29]: �˲���1��Q·����p3��Ĭ��ֵ��-14'd377�� */
        unsigned int  reserved_1       : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_CPU_FILTER1_P2_P3_Q_UNION;
#define GBBP_CPU_FILTER1_P2_P3_Q_cpu_filter1_p2_q_START  (0)
#define GBBP_CPU_FILTER1_P2_P3_Q_cpu_filter1_p2_q_END    (13)
#define GBBP_CPU_FILTER1_P2_P3_Q_cpu_filter1_p3_q_START  (16)
#define GBBP_CPU_FILTER1_P2_P3_Q_cpu_filter1_p3_q_END    (29)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_FILTER1_P4_P5_Q_UNION
 �ṹ˵��  : CPU_FILTER1_P4_P5_Q �Ĵ����ṹ���塣��ַƫ����:0x582C����ֵ:0x00003D4A�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_filter1_p4_p5_q_reg;
    struct
    {
        unsigned int  cpu_filter1_p4_q : 14; /* bit[0-13] : �˲���1��Q·����p4��Ĭ��ֵ��-14'd694�� */
        unsigned int  reserved_0       : 2;  /* bit[14-15]: ���� */
        unsigned int  cpu_filter1_p5_q : 14; /* bit[16-29]: �˲���1��Q·����p5��Ĭ��ֵ��14'd0�� */
        unsigned int  reserved_1       : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_CPU_FILTER1_P4_P5_Q_UNION;
#define GBBP_CPU_FILTER1_P4_P5_Q_cpu_filter1_p4_q_START  (0)
#define GBBP_CPU_FILTER1_P4_P5_Q_cpu_filter1_p4_q_END    (13)
#define GBBP_CPU_FILTER1_P4_P5_Q_cpu_filter1_p5_q_START  (16)
#define GBBP_CPU_FILTER1_P4_P5_Q_cpu_filter1_p5_q_END    (29)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_GACI_DATA_BYPASS_UNION
 �ṹ˵��  : CPU_GACI_DATA_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x5880����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_gaci_data_bypass_reg;
    struct
    {
        unsigned int  cpu_gaci_data_bypass : 1;  /* bit[0]   : 1��dagc�������ݲ����˲�������ֱ�����
                                                               0��dagc�������ݾ��˲����������� */
        unsigned int  reserved             : 31; /* bit[1-31]: ���� */
    } reg;
} GBBP_CPU_GACI_DATA_BYPASS_UNION;
#define GBBP_CPU_GACI_DATA_BYPASS_cpu_gaci_data_bypass_START  (0)
#define GBBP_CPU_GACI_DATA_BYPASS_cpu_gaci_data_bypass_END    (0)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_GACI_PARA_UNION
 �ṹ˵��  : CPU_GACI_PARA �Ĵ����ṹ���塣��ַƫ����:0x5884����ֵ:0x00010003�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_gaci_para_reg;
    struct
    {
        unsigned int  cpu_gaci_tpower : 3;  /* bit[0-2]  : �о�����������
                                                           3��b000:   2
                                                           3��b001:   3
                                                           3��b010:   4
                                                           3��b011:   5
                                                           3��b100:   6
                                                           3��b101:   7
                                                           3��b110:   8
                                                           3��b111:   9
                                                           Ĭ��ֵ:   5 */
        unsigned int  reserved_0      : 13; /* bit[3-15] : ���� */
        unsigned int  cpu_gaci_taci   : 3;  /* bit[16-18]: �о�����������
                                                           3��b000:   5
                                                           3��b001:   6
                                                           3��b010:   7
                                                           3��b011:   8
                                                           3��b100:   9
                                                           3��b101:   10
                                                           Ĭ��ֵ:   6 */
        unsigned int  reserved_1      : 13; /* bit[19-31]: ���� */
    } reg;
} GBBP_CPU_GACI_PARA_UNION;
#define GBBP_CPU_GACI_PARA_cpu_gaci_tpower_START  (0)
#define GBBP_CPU_GACI_PARA_cpu_gaci_tpower_END    (2)
#define GBBP_CPU_GACI_PARA_cpu_gaci_taci_START    (16)
#define GBBP_CPU_GACI_PARA_cpu_gaci_taci_END      (18)


/*****************************************************************************
 �ṹ��    : GBBP_GACI_INDEX_CPU_UNION
 �ṹ˵��  : GACI_INDEX_CPU �Ĵ����ṹ���塣��ַƫ����:0x58A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gaci_index_cpu_reg;
    struct
    {
        unsigned int  gaci_index_cpu : 2;  /* bit[0-1] : �����Ƶ��������ϱ�CPU���ֿ��ܵĸ���״̬��
                                                         2��b00���޸���
                                                         2��b01��+200Khz����
                                                         2��b10��-200Khz����
                                                         2��b11�� 200Khz���� */
        unsigned int  reserved       : 30; /* bit[2-31]: ���� */
    } reg;
} GBBP_GACI_INDEX_CPU_UNION;
#define GBBP_GACI_INDEX_CPU_gaci_index_cpu_START  (0)
#define GBBP_GACI_INDEX_CPU_gaci_index_cpu_END    (1)


/*****************************************************************************
 �ṹ��    : GBBP_GACI_RACI_CPU_UNION
 �ṹ˵��  : GACI_RACI_CPU �Ĵ����ṹ���塣��ַƫ����:0x58A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gaci_raci_cpu_reg;
    struct
    {
        unsigned int  raci_cpu : 26; /* bit[0-25] : GACI��������ematrix_03_cpu_cpu��ematrix_12_cpu���� */
        unsigned int  reserved : 6;  /* bit[26-31]: ���� */
    } reg;
} GBBP_GACI_RACI_CPU_UNION;
#define GBBP_GACI_RACI_CPU_raci_cpu_START  (0)
#define GBBP_GACI_RACI_CPU_raci_cpu_END    (25)


/*****************************************************************************
 �ṹ��    : GBBP_GACI_RPOWER_CPU_UNION
 �ṹ˵��  : GACI_RPOWER_CPU �Ĵ����ṹ���塣��ַƫ����:0x58A8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gaci_rpower_cpu_reg;
    struct
    {
        unsigned int  rpower_cpu : 26; /* bit[0-25] : GACI��������EMATRIX״̬�²������о��������ɾ�����ͨ������������������ */
        unsigned int  reserved   : 6;  /* bit[26-31]: ���� */
    } reg;
} GBBP_GACI_RPOWER_CPU_UNION;
#define GBBP_GACI_RPOWER_CPU_rpower_cpu_START  (0)
#define GBBP_GACI_RPOWER_CPU_rpower_cpu_END    (25)


/*****************************************************************************
 �ṹ��    : GBBP_GACI_EMATRIX_03_CPU_UNION
 �ṹ˵��  : GACI_EMATRIX_03_CPU �Ĵ����ṹ���塣��ַƫ����:0x58AC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gaci_ematrix_03_cpu_reg;
    struct
    {
        unsigned int  ematrix_03_cpu : 26; /* bit[0-25] : GACI��������EMATRIX״̬�²������о��������ɾ�����ͨ����������ز����� */
        unsigned int  reserved       : 6;  /* bit[26-31]: ���� */
    } reg;
} GBBP_GACI_EMATRIX_03_CPU_UNION;
#define GBBP_GACI_EMATRIX_03_CPU_ematrix_03_cpu_START  (0)
#define GBBP_GACI_EMATRIX_03_CPU_ematrix_03_cpu_END    (25)


/*****************************************************************************
 �ṹ��    : GBBP_GACI_EMATRIX_12_CPU_UNION
 �ṹ˵��  : GACI_EMATRIX_12_CPU �Ĵ����ṹ���塣��ַƫ����:0x58B0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gaci_ematrix_12_cpu_reg;
    struct
    {
        unsigned int  ematrix_12_cpu : 26; /* bit[0-25] : GACI��������EMATRIX״̬�²������о��������ɾ�����ͨ����������ز����� */
        unsigned int  reserved       : 6;  /* bit[26-31]: ���� */
    } reg;
} GBBP_GACI_EMATRIX_12_CPU_UNION;
#define GBBP_GACI_EMATRIX_12_CPU_ematrix_12_cpu_START  (0)
#define GBBP_GACI_EMATRIX_12_CPU_ematrix_12_cpu_END    (25)


/*****************************************************************************
 �ṹ��    : GBBP_GACI_AVG_ALL_CPU_UNION
 �ṹ˵��  : GACI_AVG_ALL_CPU �Ĵ����ṹ���塣��ַƫ����:0x58B4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gaci_avg_all_cpu_reg;
    struct
    {
        unsigned int  avg_all_cpu : 21; /* bit[0-20] : GACIδ������ͨ����ԭ����������������ENERGY1״̬���� */
        unsigned int  reserved    : 11; /* bit[21-31]: ���� */
    } reg;
} GBBP_GACI_AVG_ALL_CPU_UNION;
#define GBBP_GACI_AVG_ALL_CPU_avg_all_cpu_START  (0)
#define GBBP_GACI_AVG_ALL_CPU_avg_all_cpu_END    (20)


/*****************************************************************************
 �ṹ��    : GBBP_GACI_AVG_HP_CPU_UNION
 �ṹ˵��  : GACI_AVG_HP_CPU �Ĵ����ṹ���塣��ַƫ����:0x58B8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gaci_avg_hp_cpu_reg;
    struct
    {
        unsigned int  avg_hp_cpu : 21; /* bit[0-20] : GACI������ͨ����ԭ����������������ENERGY2״̬���� */
        unsigned int  reserved   : 11; /* bit[21-31]: ���� */
    } reg;
} GBBP_GACI_AVG_HP_CPU_UNION;
#define GBBP_GACI_AVG_HP_CPU_avg_hp_cpu_START  (0)
#define GBBP_GACI_AVG_HP_CPU_avg_hp_cpu_END    (20)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_AMR_CRC_PRO_NUM_CFG_UNION
 �ṹ˵��  : CPU_AMR_CRC_PRO_NUM_CFG �Ĵ����ṹ���塣��ַƫ����:0x53CC����ֵ:0x00000003�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_amr_crc_pro_num_cfg_reg;
    struct
    {
        unsigned int  cpu_amr_crc_prot_num : 2;  /* bit[0-1] : AMR����bit�Ż��㷨�����SPEECH CRC�ı������������÷�Χ0��3������������Ϊ1��4��Ĭ��ֵΪ3
                                                               ����ҵ������ΪGMSK WBAMRʱ�����÷�ΧΪ0��2�� */
        unsigned int  reserved             : 30; /* bit[2-31]: ���� */
    } reg;
} GBBP_CPU_AMR_CRC_PRO_NUM_CFG_UNION;
#define GBBP_CPU_AMR_CRC_PRO_NUM_CFG_cpu_amr_crc_prot_num_START  (0)
#define GBBP_CPU_AMR_CRC_PRO_NUM_CFG_cpu_amr_crc_prot_num_END    (1)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_P0_PRIOR_REG_CFG_UNION
 �ṹ˵��  : CPU_P0_PRIOR_REG_CFG �Ĵ����ṹ���塣��ַƫ����:0x53D0����ֵ:0x001FFFEB�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_p0_prior_reg_cfg_reg;
    struct
    {
        unsigned int  cpu_p0_prior : 21; /* bit[0-20] : AMR����bit�Ż��㷨��00��Ӧ��������� */
        unsigned int  reserved     : 11; /* bit[21-31]: ���� */
    } reg;
} GBBP_CPU_P0_PRIOR_REG_CFG_UNION;
#define GBBP_CPU_P0_PRIOR_REG_CFG_cpu_p0_prior_START  (0)
#define GBBP_CPU_P0_PRIOR_REG_CFG_cpu_p0_prior_END    (20)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_P1_PRIOR_REG_CFG_UNION
 �ṹ˵��  : CPU_P1_PRIOR_REG_CFG �Ĵ����ṹ���塣��ַƫ����:0x53D4����ֵ:0x001FFAA0�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_p1_prior_reg_cfg_reg;
    struct
    {
        unsigned int  cpu_p1_prior : 21; /* bit[0-20] : AMR����bit�Ż��㷨��01��Ӧ��������� */
        unsigned int  reserved     : 11; /* bit[21-31]: ���� */
    } reg;
} GBBP_CPU_P1_PRIOR_REG_CFG_UNION;
#define GBBP_CPU_P1_PRIOR_REG_CFG_cpu_p1_prior_START  (0)
#define GBBP_CPU_P1_PRIOR_REG_CFG_cpu_p1_prior_END    (20)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_P2_PRIOR_REG_CFG_UNION
 �ṹ˵��  : CPU_P2_PRIOR_REG_CFG �Ĵ����ṹ���塣��ַƫ����:0x53D8����ֵ:0x001FFFD6�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_p2_prior_reg_cfg_reg;
    struct
    {
        unsigned int  cpu_p2_prior : 21; /* bit[0-20] : AMR����bit�Ż��㷨��10��Ӧ��������� */
        unsigned int  reserved     : 11; /* bit[21-31]: ���� */
    } reg;
} GBBP_CPU_P2_PRIOR_REG_CFG_UNION;
#define GBBP_CPU_P2_PRIOR_REG_CFG_cpu_p2_prior_START  (0)
#define GBBP_CPU_P2_PRIOR_REG_CFG_cpu_p2_prior_END    (20)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_P3_PRIOR_REG_CFG_UNION
 �ṹ˵��  : CPU_P3_PRIOR_REG_CFG �Ĵ����ṹ���塣��ַƫ����:0x53DC����ֵ:0x001FFAA0�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_p3_prior_reg_cfg_reg;
    struct
    {
        unsigned int  cpu_p3_prior : 21; /* bit[0-20] : AMR����bit�Ż��㷨��11��Ӧ���������
                                                        AFS���㷨�Ƽ�����Ϊ-6000��AHS���㷨�Ƽ�����Ϊ-4000 */
        unsigned int  reserved     : 11; /* bit[21-31]: ���� */
    } reg;
} GBBP_CPU_P3_PRIOR_REG_CFG_UNION;
#define GBBP_CPU_P3_PRIOR_REG_CFG_cpu_p3_prior_START  (0)
#define GBBP_CPU_P3_PRIOR_REG_CFG_cpu_p3_prior_END    (20)


/*****************************************************************************
 �ṹ��    : GBBP_CMI_P01_PRIOR_PRE_RPT_UNION
 �ṹ˵��  : CMI_P01_PRIOR_PRE_RPT �Ĵ����ṹ���塣��ַƫ����:0x5380����ֵ:0x00010001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cmi_p01_prior_pre_rpt_reg;
    struct
    {
        unsigned int  mappre_0_cmi : 16; /* bit[0-15] : CMI����bit 0��Ӧ����������ϱ� */
        unsigned int  mappre_1_cmi : 16; /* bit[16-31]: CMI����bit 1��Ӧ����������ϱ� */
    } reg;
} GBBP_CMI_P01_PRIOR_PRE_RPT_UNION;
#define GBBP_CMI_P01_PRIOR_PRE_RPT_mappre_0_cmi_START  (0)
#define GBBP_CMI_P01_PRIOR_PRE_RPT_mappre_0_cmi_END    (15)
#define GBBP_CMI_P01_PRIOR_PRE_RPT_mappre_1_cmi_START  (16)
#define GBBP_CMI_P01_PRIOR_PRE_RPT_mappre_1_cmi_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_CMI_P23_PRIOR_PRE_RPT_UNION
 �ṹ˵��  : CMI_P23_PRIOR_PRE_RPT �Ĵ����ṹ���塣��ַƫ����:0x5384����ֵ:0x00010001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cmi_p23_prior_pre_rpt_reg;
    struct
    {
        unsigned int  mappre_2_cmi : 16; /* bit[0-15] : CMI����bit 2��Ӧ����������ϱ� */
        unsigned int  mappre_3_cmi : 16; /* bit[16-31]: CMI����bit 3��Ӧ����������ϱ� */
    } reg;
} GBBP_CMI_P23_PRIOR_PRE_RPT_UNION;
#define GBBP_CMI_P23_PRIOR_PRE_RPT_mappre_2_cmi_START  (0)
#define GBBP_CMI_P23_PRIOR_PRE_RPT_mappre_2_cmi_END    (15)
#define GBBP_CMI_P23_PRIOR_PRE_RPT_mappre_3_cmi_START  (16)
#define GBBP_CMI_P23_PRIOR_PRE_RPT_mappre_3_cmi_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_CMC_P01_PRIOR_PRE_RPT_UNION
 �ṹ˵��  : CMC_P01_PRIOR_PRE_RPT �Ĵ����ṹ���塣��ַƫ����:0x5388����ֵ:0x00010001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cmc_p01_prior_pre_rpt_reg;
    struct
    {
        unsigned int  mappre_0_cmc : 16; /* bit[0-15] : CMC����bit 0��Ӧ����������ϱ� */
        unsigned int  mappre_1_cmc : 16; /* bit[16-31]: CMC����bit 1��Ӧ����������ϱ� */
    } reg;
} GBBP_CMC_P01_PRIOR_PRE_RPT_UNION;
#define GBBP_CMC_P01_PRIOR_PRE_RPT_mappre_0_cmc_START  (0)
#define GBBP_CMC_P01_PRIOR_PRE_RPT_mappre_0_cmc_END    (15)
#define GBBP_CMC_P01_PRIOR_PRE_RPT_mappre_1_cmc_START  (16)
#define GBBP_CMC_P01_PRIOR_PRE_RPT_mappre_1_cmc_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_CMC_P23_PRIOR_PRE_RPT_UNION
 �ṹ˵��  : CMC_P23_PRIOR_PRE_RPT �Ĵ����ṹ���塣��ַƫ����:0x538C����ֵ:0x00010001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cmc_p23_prior_pre_rpt_reg;
    struct
    {
        unsigned int  mappre_2_cmc : 16; /* bit[0-15] : CMC����bit 2��Ӧ����������ϱ� */
        unsigned int  mappre_3_cmc : 16; /* bit[16-31]: CMC����bit 3��Ӧ����������ϱ� */
    } reg;
} GBBP_CMC_P23_PRIOR_PRE_RPT_UNION;
#define GBBP_CMC_P23_PRIOR_PRE_RPT_mappre_2_cmc_START  (0)
#define GBBP_CMC_P23_PRIOR_PRE_RPT_mappre_2_cmc_END    (15)
#define GBBP_CMC_P23_PRIOR_PRE_RPT_mappre_3_cmc_START  (16)
#define GBBP_CMC_P23_PRIOR_PRE_RPT_mappre_3_cmc_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_P01_MAPPRE_CFG_UNION
 �ṹ˵��  : CPU_P01_MAPPRE_CFG �Ĵ����ṹ���塣��ַƫ����:0x5390����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_p01_mappre_cfg_reg;
    struct
    {
        unsigned int  cpu_p0_mappre : 16; /* bit[0-15] : CMC����CMI ����bit 0��Ӧ����ʷ�������ֵ�����ڻָ�GBBP��CMC����CMI������� */
        unsigned int  cpu_p1_mappre : 16; /* bit[16-31]: CMC����CMI ����bit 1��Ӧ����ʷ�������ֵ�����ڻָ�GBBP��CMC����CMI������� */
    } reg;
} GBBP_CPU_P01_MAPPRE_CFG_UNION;
#define GBBP_CPU_P01_MAPPRE_CFG_cpu_p0_mappre_START  (0)
#define GBBP_CPU_P01_MAPPRE_CFG_cpu_p0_mappre_END    (15)
#define GBBP_CPU_P01_MAPPRE_CFG_cpu_p1_mappre_START  (16)
#define GBBP_CPU_P01_MAPPRE_CFG_cpu_p1_mappre_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_P23_MAPPRE_CFG_UNION
 �ṹ˵��  : CPU_P23_MAPPRE_CFG �Ĵ����ṹ���塣��ַƫ����:0x5394����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_p23_mappre_cfg_reg;
    struct
    {
        unsigned int  cpu_p2_mappre : 16; /* bit[0-15] : CMC����CMI ����bit 2��Ӧ����ʷ�������ֵ�����ڻָ�GBBP��CMC����CMI������� */
        unsigned int  cpu_p3_mappre : 16; /* bit[16-31]: CMC����CMI ����bit 3��Ӧ����ʷ�������ֵ�����ڻָ�GBBP��CMC����CMI������� */
    } reg;
} GBBP_CPU_P23_MAPPRE_CFG_UNION;
#define GBBP_CPU_P23_MAPPRE_CFG_cpu_p2_mappre_START  (0)
#define GBBP_CPU_P23_MAPPRE_CFG_cpu_p2_mappre_END    (15)
#define GBBP_CPU_P23_MAPPRE_CFG_cpu_p3_mappre_START  (16)
#define GBBP_CPU_P23_MAPPRE_CFG_cpu_p3_mappre_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_CMC_CMI_LOAD_EN_UNION
 �ṹ˵��  : CPU_CMC_CMI_LOAD_EN �Ĵ����ṹ���塣��ַƫ����:0x5398����ֵ:0x00360000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_cmc_cmi_load_en_reg;
    struct
    {
        unsigned int  cpu_cmi_cmc_mappre_load_en_imi : 1;  /* bit[0]    : 1��ʶ��Ҫ������CMI����CMC����ʷ������ʣ����ź�����֮ǰ��Ҫ���������CPU_P01_MAPPRE_CFG��CPU_P23_MAPPRE_CFG�Ĵ��� */
        unsigned int  cpu_cmi_cmc_mappre_load_mode   : 1;  /* bit[1]    : 0��ʶ����CMI����ʷ������ʣ�1��ʶ����CMC����ʷ������� */
        unsigned int  cpu_nodata_judge_mode          : 1;  /* bit[2]    : 1��ʶ����C02ͨ��״̬���о�NODATA��ģʽ
                                                                          0��ʶ����V3 AMR���������о���ʽ�� */
        unsigned int  reserved_0                     : 5;  /* bit[3-7]  : ���� */
        unsigned int  dec_cmc_cmi_rpt                : 1;  /* bit[8]    : 1��ʶ��ǰ�����ж�����������CMC����
                                                                          0��ʶ��ǰ�����ж�����������CMI���ڡ� */
        unsigned int  reserved_1                     : 7;  /* bit[9-15] : ���� */
        unsigned int  cpu_amr_corr_thresh            : 14; /* bit[16-29]: AMR�о��㷨�о������ޣ�AFS�Ƽ�ֵΪ233��AHS�Ƽ�ֵΪ230 */
        unsigned int  reserved_2                     : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_CPU_CMC_CMI_LOAD_EN_UNION;
#define GBBP_CPU_CMC_CMI_LOAD_EN_cpu_cmi_cmc_mappre_load_en_imi_START  (0)
#define GBBP_CPU_CMC_CMI_LOAD_EN_cpu_cmi_cmc_mappre_load_en_imi_END    (0)
#define GBBP_CPU_CMC_CMI_LOAD_EN_cpu_cmi_cmc_mappre_load_mode_START    (1)
#define GBBP_CPU_CMC_CMI_LOAD_EN_cpu_cmi_cmc_mappre_load_mode_END      (1)
#define GBBP_CPU_CMC_CMI_LOAD_EN_cpu_nodata_judge_mode_START           (2)
#define GBBP_CPU_CMC_CMI_LOAD_EN_cpu_nodata_judge_mode_END             (2)
#define GBBP_CPU_CMC_CMI_LOAD_EN_dec_cmc_cmi_rpt_START                 (8)
#define GBBP_CPU_CMC_CMI_LOAD_EN_dec_cmc_cmi_rpt_END                   (8)
#define GBBP_CPU_CMC_CMI_LOAD_EN_cpu_amr_corr_thresh_START             (16)
#define GBBP_CPU_CMC_CMI_LOAD_EN_cpu_amr_corr_thresh_END               (29)


/*****************************************************************************
 �ṹ��    : GBBP_AMR_INFO1_RPT_UNION
 �ṹ˵��  : AMR_INFO1_RPT �Ĵ����ṹ���塣��ַƫ����:0x53F8����ֵ:0x20003F3F�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      amr_info1_rpt_reg;
    struct
    {
        unsigned int  dcu_amr_frame_type : 6;  /* bit[0-5]  : AMR����֡�����ϱ� */
        unsigned int  reserved_0         : 2;  /* bit[6-7]  : ���� */
        unsigned int  max_sum_frame_type : 6;  /* bit[8-13] : AMR������֡�����ϱ� */
        unsigned int  reserved_1         : 2;  /* bit[14-15]: ���� */
        unsigned int  corr_max_sum       : 14; /* bit[16-29]: AMR������֡��������ۼӺ��ϱ� */
        unsigned int  reserved_2         : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_AMR_INFO1_RPT_UNION;
#define GBBP_AMR_INFO1_RPT_dcu_amr_frame_type_START  (0)
#define GBBP_AMR_INFO1_RPT_dcu_amr_frame_type_END    (5)
#define GBBP_AMR_INFO1_RPT_max_sum_frame_type_START  (8)
#define GBBP_AMR_INFO1_RPT_max_sum_frame_type_END    (13)
#define GBBP_AMR_INFO1_RPT_corr_max_sum_START        (16)
#define GBBP_AMR_INFO1_RPT_corr_max_sum_END          (29)


/*****************************************************************************
 �ṹ��    : GBBP_AMR_INFO2_RPT_UNION
 �ṹ˵��  : AMR_INFO2_RPT �Ĵ����ṹ���塣��ַƫ����:0x53FC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      amr_info2_rpt_reg;
    struct
    {
        unsigned int  abs_sum_g_corr_max_sum    : 1;  /* bit[0]   : AMR�о��㷨��ʽ�ϱ� */
        unsigned int  abs_sum_le_corr_rat_sum   : 1;  /* bit[1]   : AMR�о��㷨��ʽ�ϱ� */
        unsigned int  abs_sum_le_corr_onset_sum : 1;  /* bit[2]   : AMR�о��㷨��ʽ�ϱ� */
        unsigned int  reserved                  : 29; /* bit[3-31]: ���� */
    } reg;
} GBBP_AMR_INFO2_RPT_UNION;
#define GBBP_AMR_INFO2_RPT_abs_sum_g_corr_max_sum_START     (0)
#define GBBP_AMR_INFO2_RPT_abs_sum_g_corr_max_sum_END       (0)
#define GBBP_AMR_INFO2_RPT_abs_sum_le_corr_rat_sum_START    (1)
#define GBBP_AMR_INFO2_RPT_abs_sum_le_corr_rat_sum_END      (1)
#define GBBP_AMR_INFO2_RPT_abs_sum_le_corr_onset_sum_START  (2)
#define GBBP_AMR_INFO2_RPT_abs_sum_le_corr_onset_sum_END    (2)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_AMR_CORR_COEFF_CFG_UNION
 �ṹ˵��  : CPU_AMR_CORR_COEFF_CFG �Ĵ����ṹ���塣��ַƫ����:0x53E0����ֵ:0x0000000A�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_amr_corr_coeff_cfg_reg;
    struct
    {
        unsigned int  cpu_amr_corr_coeff : 4;  /* bit[0-3] : AFS/AHS ��������о���ʽ���޲��������÷�Χ0��15���Ƽ�����Ϊ10 */
        unsigned int  reserved           : 28; /* bit[4-31]: ���� */
    } reg;
} GBBP_CPU_AMR_CORR_COEFF_CFG_UNION;
#define GBBP_CPU_AMR_CORR_COEFF_CFG_cpu_amr_corr_coeff_START  (0)
#define GBBP_CPU_AMR_CORR_COEFF_CFG_cpu_amr_corr_coeff_END    (3)


/*****************************************************************************
 �ṹ��    : GBBP_CODEC_WR_CONFLICT_CNT_UNION
 �ṹ˵��  : CODEC_WR_CONFLICT_CNT �Ĵ����ṹ���塣��ַƫ����:0x5718����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      codec_wr_conflict_cnt_reg;
    struct
    {
        unsigned int  codec_conflict_cnt_cpu    : 8;  /* bit[0-7]  : [3:0] ��������������������������ó�ͻ�������ϱ�
                                                                     [7:4]��������������������б������ó�ͻ�������ϱ� */
        unsigned int  reserved                  : 8;  /* bit[8-15] : ���� */
        unsigned int  valpp_wr_conflict_cnt_cpu : 16; /* bit[16-31]: VALPP RAM���ڷ��ʳ�ͻ������
                                                                     [31:28] DEM��CARRY���̷�������д��ͻ
                                                                     [27:20]  DEMAP��MAP���̷�������д��ͻ
                                                                     [23:20] DEMAP��CARRY���̷�������д��ͻ
                                                                     [19:16] DEMAP��DEMģ�鷢������д��ͻ */
    } reg;
} GBBP_CODEC_WR_CONFLICT_CNT_UNION;
#define GBBP_CODEC_WR_CONFLICT_CNT_codec_conflict_cnt_cpu_START     (0)
#define GBBP_CODEC_WR_CONFLICT_CNT_codec_conflict_cnt_cpu_END       (7)
#define GBBP_CODEC_WR_CONFLICT_CNT_valpp_wr_conflict_cnt_cpu_START  (16)
#define GBBP_CODEC_WR_CONFLICT_CNT_valpp_wr_conflict_cnt_cpu_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_HARQ_MODE_UNION
 �ṹ˵��  : ADDR_HARQ_MODE �Ĵ����ṹ���塣��ַƫ����:0x5A00����ֵ:0x00010001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_harq_mode_reg;
    struct
    {
        unsigned int  cpu_harq_external_mode : 1;  /* bit[0]    : HARQ����ģʽ������ģʽѡ���źţ�1��ʾʹ������ģʽ��0��ʾʹ������ģʽ�� */
        unsigned int  reserved_0             : 15; /* bit[1-15] : ���� */
        unsigned int  cpu_harq_ddr_mode      : 1;  /* bit[16]   : HARQ����ģʽ�£��Ƿ����CRC���������DDR���з��ʣ�1��ʾ����CRC�����ǿ�н����ݴ���HARQ MEM��0��ʾ����CRC��������ݴ���HARQ MEM�� */
        unsigned int  reserved_1             : 15; /* bit[17-31]: ���� */
    } reg;
} GBBP_ADDR_HARQ_MODE_UNION;
#define GBBP_ADDR_HARQ_MODE_cpu_harq_external_mode_START  (0)
#define GBBP_ADDR_HARQ_MODE_cpu_harq_external_mode_END    (0)
#define GBBP_ADDR_HARQ_MODE_cpu_harq_ddr_mode_START       (16)
#define GBBP_ADDR_HARQ_MODE_cpu_harq_ddr_mode_END         (16)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_HARQ_INIT_EN_UNION
 �ṹ˵��  : ADDR_HARQ_INIT_EN �Ĵ����ṹ���塣��ַƫ����:0x5A04����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_harq_init_en_reg;
    struct
    {
        unsigned int  cpu_harq_init_en : 1;  /* bit[0]   : HARQ����ģʽ�£��쳣��λ�źţ������źţ�д1��λ�� */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} GBBP_ADDR_HARQ_INIT_EN_UNION;
#define GBBP_ADDR_HARQ_INIT_EN_cpu_harq_init_en_START  (0)
#define GBBP_ADDR_HARQ_INIT_EN_cpu_harq_init_en_END    (0)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_DDR_HARQ_CFG_UNION
 �ṹ˵��  : ADDR_DDR_HARQ_CFG �Ĵ����ṹ���塣��ַƫ����:0x5A10����ֵ:0x00000008�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_ddr_harq_cfg_reg;
    struct
    {
        unsigned int  g_beat_num       : 4;  /* bit[0-3]  : HARQ����ģʽ�£�DDRÿ��дFIFO��burst���ȡ� */
        unsigned int  reserved_0       : 12; /* bit[4-15] : ���� */
        unsigned int  dec_int_type_cpu : 4;  /* bit[16-19]: HARQ����ģʽ�£������ж��쳣״̬�ϱ�ֵ��
                                                            1��b1�����볬ʱ
                                                            1��b0������δ��ʱ */
        unsigned int  reserved_1       : 12; /* bit[20-31]: ���� */
    } reg;
} GBBP_ADDR_DDR_HARQ_CFG_UNION;
#define GBBP_ADDR_DDR_HARQ_CFG_g_beat_num_START        (0)
#define GBBP_ADDR_DDR_HARQ_CFG_g_beat_num_END          (3)
#define GBBP_ADDR_DDR_HARQ_CFG_dec_int_type_cpu_START  (16)
#define GBBP_ADDR_DDR_HARQ_CFG_dec_int_type_cpu_END    (19)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_TX_RRC_PILTER_EN_UNION
 �ṹ˵��  : ADDR_TX_RRC_PILTER_EN �Ĵ����ṹ���塣��ַƫ����:0x5A14����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_tx_rrc_pilter_en_reg;
    struct
    {
        unsigned int  cpu_tx_rrc_filter_en : 1;  /* bit[0]   : �����˲���ʹ���źţ��������Ƶ��ƺ������Ƿ񾭹�16�������˲�����Ĭ��ֵ��0�� */
        unsigned int  reserved             : 31; /* bit[1-31]: ���� */
    } reg;
} GBBP_ADDR_TX_RRC_PILTER_EN_UNION;
#define GBBP_ADDR_TX_RRC_PILTER_EN_cpu_tx_rrc_filter_en_START  (0)
#define GBBP_ADDR_TX_RRC_PILTER_EN_cpu_tx_rrc_filter_en_END    (0)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_HARQ_RAM_WR_EN_BYPASS_UNION
 �ṹ˵��  : ADDR_HARQ_RAM_WR_EN_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x5A18����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_harq_ram_wr_en_bypass_reg;
    struct
    {
        unsigned int  cpu_harq_ram_wr_en_bypass : 1;  /* bit[0]   : HARQ����ģʽ�£�Harq Ramдʹ�ܳ�ʱ������·�źš����ź���Ч��ʾHarq Ramдʹ�ܲ�����ʱ������Ĭ��ֵΪ0����ʾ���г�ʱ������ */
        unsigned int  reserved                  : 31; /* bit[1-31]: ���� */
    } reg;
} GBBP_ADDR_HARQ_RAM_WR_EN_BYPASS_UNION;
#define GBBP_ADDR_HARQ_RAM_WR_EN_BYPASS_cpu_harq_ram_wr_en_bypass_START  (0)
#define GBBP_ADDR_HARQ_RAM_WR_EN_BYPASS_cpu_harq_ram_wr_en_bypass_END    (0)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_TIMING_GET_TRIGGER_UNION
 �ṹ˵��  : CPU_TIMING_GET_TRIGGER �Ĵ����ṹ���塣��ַƫ����:0x5A20����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_timing_get_trigger_reg;
    struct
    {
        unsigned int  cpu_timing_get_trigger   : 1;  /* bit[0]    : GBBP��ʱ���������źţ�д1��Ч�������㣬���ź���Чʱ��GBBP������ʱ���档 */
        unsigned int  reserved_0               : 15; /* bit[1-15] : ���� */
        unsigned int  cpu_timing_get_state_clr : 1;  /* bit[16]   : GBBP��ʱ����״̬�����źţ�д1��Ч�������㣬���ź���Чʱ��timing_get_state״̬���� */
        unsigned int  reserved_1               : 15; /* bit[17-31]: ���� */
    } reg;
} GBBP_CPU_TIMING_GET_TRIGGER_UNION;
#define GBBP_CPU_TIMING_GET_TRIGGER_cpu_timing_get_trigger_START    (0)
#define GBBP_CPU_TIMING_GET_TRIGGER_cpu_timing_get_trigger_END      (0)
#define GBBP_CPU_TIMING_GET_TRIGGER_cpu_timing_get_state_clr_START  (16)
#define GBBP_CPU_TIMING_GET_TRIGGER_cpu_timing_get_state_clr_END    (16)


/*****************************************************************************
 �ṹ��    : GBBP_TIMING_GET_FN_RPT_UNION
 �ṹ˵��  : TIMING_GET_FN_RPT �Ĵ����ṹ���塣��ַƫ����:0x5A24����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      timing_get_fn_rpt_reg;
    struct
    {
        unsigned int  timing_get_fn_low   : 11; /* bit[0-10] : GTC��ʱʵ��֡�ŵ�λ */
        unsigned int  reserved_0          : 5;  /* bit[11-15]: ���� */
        unsigned int  timing_get_fn_high  : 11; /* bit[16-26]: GTC��ʱʵ��֡�Ÿ�λ */
        unsigned int  reserved_1          : 4;  /* bit[27-30]: ���� */
        unsigned int  timing_get_fn_state : 1;  /* bit[31]   : ��ʱ����״̬�ϱ�����cpu_timing_get_state_clr��Чʱ�ñ����ϱ��������㡣 */
    } reg;
} GBBP_TIMING_GET_FN_RPT_UNION;
#define GBBP_TIMING_GET_FN_RPT_timing_get_fn_low_START    (0)
#define GBBP_TIMING_GET_FN_RPT_timing_get_fn_low_END      (10)
#define GBBP_TIMING_GET_FN_RPT_timing_get_fn_high_START   (16)
#define GBBP_TIMING_GET_FN_RPT_timing_get_fn_high_END     (26)
#define GBBP_TIMING_GET_FN_RPT_timing_get_fn_state_START  (31)
#define GBBP_TIMING_GET_FN_RPT_timing_get_fn_state_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_TIMING_GET_TIMEBASE_RPT_UNION
 �ṹ˵��  : TIMING_GET_TIMEBASE_RPT �Ĵ����ṹ���塣��ַƫ����:0x5A28����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      timing_get_timebase_rpt_reg;
    struct
    {
        unsigned int  timing_get_tdma_qb  : 13; /* bit[0-12] : ��ǰʱ��TDMA��QB����ֵ */
        unsigned int  reserved_0          : 3;  /* bit[13-15]: ���� */
        unsigned int  timing_get_timebase : 13; /* bit[16-28]: ����ʱ��QB�ϱ���������Χ0~4999����Ӧһ֡�ĳ��ȡ���ֵֻ�븴λʱ���йأ������� */
        unsigned int  reserved_1          : 3;  /* bit[29-31]: ���� */
    } reg;
} GBBP_TIMING_GET_TIMEBASE_RPT_UNION;
#define GBBP_TIMING_GET_TIMEBASE_RPT_timing_get_tdma_qb_START   (0)
#define GBBP_TIMING_GET_TIMEBASE_RPT_timing_get_tdma_qb_END     (12)
#define GBBP_TIMING_GET_TIMEBASE_RPT_timing_get_timebase_START  (16)
#define GBBP_TIMING_GET_TIMEBASE_RPT_timing_get_timebase_END    (28)


/*****************************************************************************
 �ṹ��    : GBBP_LOOPC_MODE_CFG_UNION
 �ṹ˵��  : LOOPC_MODE_CFG �Ĵ����ṹ���塣��ַƫ����:0x53F0����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      loopc_mode_cfg_reg;
    struct
    {
        unsigned int  cpu_loopc_mode : 1;  /* bit[0]   : 1��ʶ��LoopC����ʱ��͵֡bitλ�ù̶�����1��b0��
                                                         0��ʶ��LoopC����ʱ��͵֡bitλ�÷��ؽ����ֵ�ķ���λ�� */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} GBBP_LOOPC_MODE_CFG_UNION;
#define GBBP_LOOPC_MODE_CFG_cpu_loopc_mode_START  (0)
#define GBBP_LOOPC_MODE_CFG_cpu_loopc_mode_END    (0)


/*****************************************************************************
 �ṹ��    : GBBP_COD_CBINDEX_RPT_UNION
 �ṹ˵��  : COD_CBINDEX_RPT �Ĵ����ṹ���塣��ַƫ����:0x53F4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cod_cbindex_rpt_reg;
    struct
    {
        unsigned int  cod_cnt             : 4;  /* bit[0-3]  : ���б�������ϱ� */
        unsigned int  reserved_0          : 4;  /* bit[4-7]  : ���� */
        unsigned int  gsp_ul_cb_start_pos : 2;  /* bit[8-9]  : ���б������ʼλ���ϱ� */
        unsigned int  reserved_1          : 6;  /* bit[10-15]: ���� */
        unsigned int  gsp_ul_cb1_index    : 7;  /* bit[16-22]: ���б�����cbindex�ϱ� */
        unsigned int  reserved_2          : 9;  /* bit[23-31]: ���� */
    } reg;
} GBBP_COD_CBINDEX_RPT_UNION;
#define GBBP_COD_CBINDEX_RPT_cod_cnt_START              (0)
#define GBBP_COD_CBINDEX_RPT_cod_cnt_END                (3)
#define GBBP_COD_CBINDEX_RPT_gsp_ul_cb_start_pos_START  (8)
#define GBBP_COD_CBINDEX_RPT_gsp_ul_cb_start_pos_END    (9)
#define GBBP_COD_CBINDEX_RPT_gsp_ul_cb1_index_START     (16)
#define GBBP_COD_CBINDEX_RPT_gsp_ul_cb1_index_END       (22)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_IQ_MOD_DTA_UNION
 �ṹ˵��  : CPU_IQ_MOD_DTA �Ĵ����ṹ���塣��ַƫ����:0x53C8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_iq_mod_dta_reg;
    struct
    {
        unsigned int  cpu_q_mod_data : 12; /* bit[0-11] : ���з���У׼ʱǿ��Q·�������Ϊ���������� */
        unsigned int  reserved_0     : 4;  /* bit[12-15]: ���� */
        unsigned int  cpu_i_mod_data : 12; /* bit[16-27]: ���з���У׼ʱǿ��I·�������Ϊ���������� */
        unsigned int  reserved_1     : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_CPU_IQ_MOD_DTA_UNION;
#define GBBP_CPU_IQ_MOD_DTA_cpu_q_mod_data_START  (0)
#define GBBP_CPU_IQ_MOD_DTA_cpu_q_mod_data_END    (11)
#define GBBP_CPU_IQ_MOD_DTA_cpu_i_mod_data_START  (16)
#define GBBP_CPU_IQ_MOD_DTA_cpu_i_mod_data_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_TX_DATA_MULFACTOR_UNION
 �ṹ˵��  : TX_DATA_MULFACTOR �Ĵ����ṹ���塣��ַƫ����:0x5374����ֵ:0x03FF0399�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      tx_data_mulfactor_reg;
    struct
    {
        unsigned int  cpu_gmsk_tx_data_mulfactor : 10; /* bit[0-9]  : GMSK���е��������������ӣ����ŷ���Ĭ��ԼΪ921/1024=0.9�� */
        unsigned int  reserved_0                 : 6;  /* bit[10-15]: ���� */
        unsigned int  cpu_psk_tx_data_mulfactor  : 10; /* bit[16-25]: 8PSK���е��������������ӣ����ŷ���Ĭ��ԼΪ1023/1024=1�� */
        unsigned int  reserved_1                 : 6;  /* bit[26-31]: ���� */
    } reg;
} GBBP_TX_DATA_MULFACTOR_UNION;
#define GBBP_TX_DATA_MULFACTOR_cpu_gmsk_tx_data_mulfactor_START  (0)
#define GBBP_TX_DATA_MULFACTOR_cpu_gmsk_tx_data_mulfactor_END    (9)
#define GBBP_TX_DATA_MULFACTOR_cpu_psk_tx_data_mulfactor_START   (16)
#define GBBP_TX_DATA_MULFACTOR_cpu_psk_tx_data_mulfactor_END     (25)


/*****************************************************************************
 �ṹ��    : GBBP_SLOT_DCR_RSSI_THRESHOLD_UNION
 �ṹ˵��  : SLOT_DCR_RSSI_THRESHOLD �Ĵ����ṹ���塣��ַƫ����:0x5378����ֵ:0x00000B50�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      slot_dcr_rssi_threshold_reg;
    struct
    {
        unsigned int  cpu_slot_dcr_rssi_threshold : 12; /* bit[0-11] : ʱ϶ȥֱ���������ޣ���ʱ϶ȥֱ���Ƿ�����ȡ���ڵ�ǰʱ϶��RSSI��С�������ڸ�����ʱ���������ʱ϶ȥֱ��ģʽ����֮��������Ĭ������-12'd1200���൱��-150dBm�����ڿտڽ����źŲ�����С�ڸ�ֵ���൱��Ĭ�ϲ���������ʱ϶ȥֱ���� */
        unsigned int  reserved                    : 20; /* bit[12-31]: ���� */
    } reg;
} GBBP_SLOT_DCR_RSSI_THRESHOLD_UNION;
#define GBBP_SLOT_DCR_RSSI_THRESHOLD_cpu_slot_dcr_rssi_threshold_START  (0)
#define GBBP_SLOT_DCR_RSSI_THRESHOLD_cpu_slot_dcr_rssi_threshold_END    (11)


/*****************************************************************************
 �ṹ��    : GBBP_MOD_BIT0_RPT_UNION
 �ṹ˵��  : MOD_BIT0_RPT �Ĵ����ṹ���塣��ַƫ����:0x53A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      mod_bit0_rpt_reg;
    struct
    {
        unsigned int  map_bit_0cpu : 30; /* bit[0-29] : GMSK���������ݣ�����󡢵���ǰ���ϱ���0��29���أ�˳��Ϊ�ӵ͵��� */
        unsigned int  reserved     : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_MOD_BIT0_RPT_UNION;
#define GBBP_MOD_BIT0_RPT_map_bit_0cpu_START  (0)
#define GBBP_MOD_BIT0_RPT_map_bit_0cpu_END    (29)


/*****************************************************************************
 �ṹ��    : GBBP_MOD_BIT1_RPT_UNION
 �ṹ˵��  : MOD_BIT1_RPT �Ĵ����ṹ���塣��ַƫ����:0x53A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      mod_bit1_rpt_reg;
    struct
    {
        unsigned int  map_bit_1cpu : 30; /* bit[0-29] : GMSK���������ݣ�����󡢵���ǰ���ϱ���30��59���أ�˳��Ϊ�ӵ͵��� */
        unsigned int  reserved     : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_MOD_BIT1_RPT_UNION;
#define GBBP_MOD_BIT1_RPT_map_bit_1cpu_START  (0)
#define GBBP_MOD_BIT1_RPT_map_bit_1cpu_END    (29)


/*****************************************************************************
 �ṹ��    : GBBP_MOD_BIT2_RPT_UNION
 �ṹ˵��  : MOD_BIT2_RPT �Ĵ����ṹ���塣��ַƫ����:0x53A8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      mod_bit2_rpt_reg;
    struct
    {
        unsigned int  map_bit_2cpu : 30; /* bit[0-29] : GMSK���������ݣ�����󡢵���ǰ���ϱ���60��89���أ�˳��Ϊ�ӵ͵��� */
        unsigned int  reserved     : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_MOD_BIT2_RPT_UNION;
#define GBBP_MOD_BIT2_RPT_map_bit_2cpu_START  (0)
#define GBBP_MOD_BIT2_RPT_map_bit_2cpu_END    (29)


/*****************************************************************************
 �ṹ��    : GBBP_MOD_BIT3_RPT_UNION
 �ṹ˵��  : MOD_BIT3_RPT �Ĵ����ṹ���塣��ַƫ����:0x53AC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      mod_bit3_rpt_reg;
    struct
    {
        unsigned int  map_bit_3cpu : 30; /* bit[0-29] : GMSK���������ݣ�����󡢵���ǰ���ϱ���90��119���أ�˳��Ϊ�ӵ͵��� */
        unsigned int  reserved     : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_MOD_BIT3_RPT_UNION;
#define GBBP_MOD_BIT3_RPT_map_bit_3cpu_START  (0)
#define GBBP_MOD_BIT3_RPT_map_bit_3cpu_END    (29)


/*****************************************************************************
 �ṹ��    : GBBP_MOD_BIT4_RPT_UNION
 �ṹ˵��  : MOD_BIT4_RPT �Ĵ����ṹ���塣��ַƫ����:0x53B0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      mod_bit4_rpt_reg;
    struct
    {
        unsigned int  map_bit_4cpu : 30; /* bit[0-29] : GMSK���������ݣ�����󡢵���ǰ���ϱ���120��147���أ�˳��Ϊ�ӵ͵��ߡ���������148���أ�[29:27]������ */
        unsigned int  reserved     : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_MOD_BIT4_RPT_UNION;
#define GBBP_MOD_BIT4_RPT_map_bit_4cpu_START  (0)
#define GBBP_MOD_BIT4_RPT_map_bit_4cpu_END    (29)


/*****************************************************************************
 �ṹ��    : GBBP_TX_IQ_MISMATCH_COMP_UNION
 �ṹ˵��  : TX_IQ_MISMATCH_COMP �Ĵ����ṹ���塣��ַƫ����:0x58BC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      tx_iq_mismatch_comp_reg;
    struct
    {
        unsigned int  cpu_g_tx_amp_comp   : 10; /* bit[0-9]  : GSM TX IQ Mismatch��ֵУ�����ӣ��з������� */
        unsigned int  reserved_0          : 6;  /* bit[10-15]: ���� */
        unsigned int  cpu_g_tx_phase_comp : 10; /* bit[16-25]: GSM TX IQ Mismatch��λУ�����ӣ��з������� */
        unsigned int  reserved_1          : 6;  /* bit[26-31]: ���� */
    } reg;
} GBBP_TX_IQ_MISMATCH_COMP_UNION;
#define GBBP_TX_IQ_MISMATCH_COMP_cpu_g_tx_amp_comp_START    (0)
#define GBBP_TX_IQ_MISMATCH_COMP_cpu_g_tx_amp_comp_END      (9)
#define GBBP_TX_IQ_MISMATCH_COMP_cpu_g_tx_phase_comp_START  (16)
#define GBBP_TX_IQ_MISMATCH_COMP_cpu_g_tx_phase_comp_END    (25)


/*****************************************************************************
 �ṹ��    : GBBP_TX_IQ_DC_OFFSET_COMP_UNION
 �ṹ˵��  : TX_IQ_DC_OFFSET_COMP �Ĵ����ṹ���塣��ַƫ����:0x58C0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      tx_iq_dc_offset_comp_reg;
    struct
    {
        unsigned int  cpu_g_tx_dc_offset_i : 12; /* bit[0-11] : GSM TX IQ Mismatch I·ֱ��ƫ�ò���ֵ���з�������ע���������� */
        unsigned int  reserved_0           : 4;  /* bit[12-15]: ���� */
        unsigned int  cpu_g_tx_dc_offset_q : 12; /* bit[16-27]: GSM TX IQ Mismatch Q·ֱ��ƫ�ò���ֵ���з�������ע���������� */
        unsigned int  reserved_1           : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_TX_IQ_DC_OFFSET_COMP_UNION;
#define GBBP_TX_IQ_DC_OFFSET_COMP_cpu_g_tx_dc_offset_i_START  (0)
#define GBBP_TX_IQ_DC_OFFSET_COMP_cpu_g_tx_dc_offset_i_END    (11)
#define GBBP_TX_IQ_DC_OFFSET_COMP_cpu_g_tx_dc_offset_q_START  (16)
#define GBBP_TX_IQ_DC_OFFSET_COMP_cpu_g_tx_dc_offset_q_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_TX_DIG_RMAP_MODE_SEL_UNION
 �ṹ˵��  : TX_DIG_RMAP_MODE_SEL �Ĵ����ṹ���塣��ַƫ����:0x58C4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      tx_dig_rmap_mode_sel_reg;
    struct
    {
        unsigned int  cpu_gmsk_digramp_en    : 1;  /* bit[0]    : gmsk��������ʹ���źš�
                                                                  1��ʾgmskʹ���������£�0��ʾgmsk��ʹ���������¡� */
        unsigned int  reserved_0             : 7;  /* bit[1-7]  : ���� */
        unsigned int  cpu_8psk_digramp_en    : 1;  /* bit[8]    : 8psk��������ʹ���źš�
                                                                  1��ʾ8pskʹ���������£�0��ʾ8psk��ʹ���������¡�
                                                                  Ĭ��ֵΪ1�� */
        unsigned int  reserved_1             : 7;  /* bit[9-15] : ���� */
        unsigned int  cpu_ramp_default_value : 10; /* bit[16-25]: ��������ʱ�����½������apc_rampĬ��ֵ��
                                                                  Ĭ��ֵΪ0��
                                                                  �����á� */
        unsigned int  reserved_2             : 6;  /* bit[26-31]: ���� */
    } reg;
} GBBP_TX_DIG_RMAP_MODE_SEL_UNION;
#define GBBP_TX_DIG_RMAP_MODE_SEL_cpu_gmsk_digramp_en_START     (0)
#define GBBP_TX_DIG_RMAP_MODE_SEL_cpu_gmsk_digramp_en_END       (0)
#define GBBP_TX_DIG_RMAP_MODE_SEL_cpu_8psk_digramp_en_START     (8)
#define GBBP_TX_DIG_RMAP_MODE_SEL_cpu_8psk_digramp_en_END       (8)
#define GBBP_TX_DIG_RMAP_MODE_SEL_cpu_ramp_default_value_START  (16)
#define GBBP_TX_DIG_RMAP_MODE_SEL_cpu_ramp_default_value_END    (25)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_APC_SWITCH_EN_UNION
 �ṹ˵��  : CPU_APC_SWITCH_EN �Ĵ����ṹ���塣��ַƫ����:0x53C0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_apc_switch_en_reg;
    struct
    {
        unsigned int  cpu_apc_page_switch_en : 1;  /* bit[0]    : GAPC����ϵ������RAMƹ�ҷ���ʹ�ܣ�1��ʾ����ƹ�ҷ��ʣ�0��ʾ�̶�����֡0ϵ���ռ䣻�����ź�Ϊ1ʱ���߼��ڲ���TDMA֡ͷ�Զ��л�ƹ�ұ�־ */
        unsigned int  reserved_0             : 15; /* bit[1-15] : ���� */
        unsigned int  gsp_pa_target          : 10; /* bit[16-25]: ����ʹ�õ�gsp_pa_targetֵ�ϱ� */
        unsigned int  reserved_1             : 6;  /* bit[26-31]: ���� */
    } reg;
} GBBP_CPU_APC_SWITCH_EN_UNION;
#define GBBP_CPU_APC_SWITCH_EN_cpu_apc_page_switch_en_START  (0)
#define GBBP_CPU_APC_SWITCH_EN_cpu_apc_page_switch_en_END    (0)
#define GBBP_CPU_APC_SWITCH_EN_gsp_pa_target_START           (16)
#define GBBP_CPU_APC_SWITCH_EN_gsp_pa_target_END             (25)


/*****************************************************************************
 �ṹ��    : GBBP_TEST_PIN_SEL_LOW_UNION
 �ṹ˵��  : TEST_PIN_SEL_LOW �Ĵ����ṹ���塣��ַƫ����:0x5700����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      test_pin_sel_low_reg;
    struct
    {
        unsigned int  agc_test_pin_sel  : 4;  /* bit[0-3]  : 16��AGCģ��Ĳ�������ѡ���ź� */
        unsigned int  mau_test_pin_sel  : 4;  /* bit[4-7]  : 16��MAUģ��Ĳ�������ѡ���ź� */
        unsigned int  srch_test_pin_sel : 4;  /* bit[8-11] : 16��SRCHģ��Ĳ�������ѡ���ź� */
        unsigned int  dem_test_pin_sel  : 4;  /* bit[12-15]: 16��VTB_DEMģ��Ĳ���ѡ���ź����� */
        unsigned int  dec_test_pin_sel  : 4;  /* bit[16-19]: 16��DECģ��Ĳ�������ѡ���ź� */
        unsigned int  cod_test_pin_sel  : 4;  /* bit[20-23]: 16��CODģ��Ĳ�������ѡ���ź� */
        unsigned int  mod_test_pin_sel  : 4;  /* bit[24-27]: 16��MODģ��Ĳ�������ѡ���ź� */
        unsigned int  gtc_test_pin_sel  : 4;  /* bit[28-31]: 16��GTCģ��Ĳ�������ѡ���ź� */
    } reg;
} GBBP_TEST_PIN_SEL_LOW_UNION;
#define GBBP_TEST_PIN_SEL_LOW_agc_test_pin_sel_START   (0)
#define GBBP_TEST_PIN_SEL_LOW_agc_test_pin_sel_END     (3)
#define GBBP_TEST_PIN_SEL_LOW_mau_test_pin_sel_START   (4)
#define GBBP_TEST_PIN_SEL_LOW_mau_test_pin_sel_END     (7)
#define GBBP_TEST_PIN_SEL_LOW_srch_test_pin_sel_START  (8)
#define GBBP_TEST_PIN_SEL_LOW_srch_test_pin_sel_END    (11)
#define GBBP_TEST_PIN_SEL_LOW_dem_test_pin_sel_START   (12)
#define GBBP_TEST_PIN_SEL_LOW_dem_test_pin_sel_END     (15)
#define GBBP_TEST_PIN_SEL_LOW_dec_test_pin_sel_START   (16)
#define GBBP_TEST_PIN_SEL_LOW_dec_test_pin_sel_END     (19)
#define GBBP_TEST_PIN_SEL_LOW_cod_test_pin_sel_START   (20)
#define GBBP_TEST_PIN_SEL_LOW_cod_test_pin_sel_END     (23)
#define GBBP_TEST_PIN_SEL_LOW_mod_test_pin_sel_START   (24)
#define GBBP_TEST_PIN_SEL_LOW_mod_test_pin_sel_END     (27)
#define GBBP_TEST_PIN_SEL_LOW_gtc_test_pin_sel_START   (28)
#define GBBP_TEST_PIN_SEL_LOW_gtc_test_pin_sel_END     (31)


/*****************************************************************************
 �ṹ��    : GBBP_TEST_PIN_SEL_HIGH_UNION
 �ṹ˵��  : TEST_PIN_SEL_HIGH �Ĵ����ṹ���塣��ַƫ����:0x5704����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      test_pin_sel_high_reg;
    struct
    {
        unsigned int  prefilter_test_pin_sel  : 4;  /* bit[0-3]  : 16��PREFILTERģ��Ĳ�������ѡ���ź� */
        unsigned int  preprocess_test_pin_sel : 4;  /* bit[4-7]  : 16��PREPROCESSģ��Ĳ�������ѡ���ź� */
        unsigned int  gapc_test_pin_sel       : 4;  /* bit[8-11] : 16��APCģ��Ĳ�������ѡ���ź� */
        unsigned int  reserved                : 4;  /* bit[12-15]: ���� */
        unsigned int  path_eng_max_sum        : 16; /* bit[16-31]: ����TOA�����13���������У�����5�������ۼӣ�����9���ۼ�ֵ�����ϱ�Ϊ��ǰʱ϶����ۼ�ֵ�� */
    } reg;
} GBBP_TEST_PIN_SEL_HIGH_UNION;
#define GBBP_TEST_PIN_SEL_HIGH_prefilter_test_pin_sel_START   (0)
#define GBBP_TEST_PIN_SEL_HIGH_prefilter_test_pin_sel_END     (3)
#define GBBP_TEST_PIN_SEL_HIGH_preprocess_test_pin_sel_START  (4)
#define GBBP_TEST_PIN_SEL_HIGH_preprocess_test_pin_sel_END    (7)
#define GBBP_TEST_PIN_SEL_HIGH_gapc_test_pin_sel_START        (8)
#define GBBP_TEST_PIN_SEL_HIGH_gapc_test_pin_sel_END          (11)
#define GBBP_TEST_PIN_SEL_HIGH_path_eng_max_sum_START         (16)
#define GBBP_TEST_PIN_SEL_HIGH_path_eng_max_sum_END           (31)


/*****************************************************************************
 �ṹ��    : GBBP_TEST_MODULE_SEL_UNION
 �ṹ˵��  : TEST_MODULE_SEL �Ĵ����ṹ���塣��ַƫ����:0x5710����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      test_module_sel_reg;
    struct
    {
        unsigned int  gbbp_module_test_sel_low  : 5;  /* bit[0-4] : 0��ѡ��AGCģ��Ĳ�������
                                                                    1��ѡ����ۼ�ģ��Ĳ�������
                                                                    2��ѡ������ģ��Ĳ�������
                                                                    3��ѡ����ģ��Ĳ�������
                                                                    4��ѡ������ģ��Ĳ�������
                                                                    5��ѡ�����ģ��Ĳ�������
                                                                    6��ѡ�����ģ��Ĳ�������
                                                                    7��ѡ��GTCģ��Ĳ�������
                                                                    8��ѡ��A5 DECIPHģ��Ĳ�������
                                                                    9��ѡ��PREFILTERģ��Ĳ�������
                                                                    10��ѡ��PREPROCESSģ��Ĳ�������
                                                                    11��ѡ��APCģ��Ĳ�������
                                                                    13��ѡ��GRIFģ��Ĳ�������
                                                                    14��ѡ��A5 CIPHģ��Ĳ������� */
        unsigned int  gbbp_module_test_sel_high : 3;  /* bit[5-7] : 0��ʾ����ѡ��DAGC������ݲ�������ؿ����ź�
                                                                    1��ʾ����ѡ��AGC�������ݲ�������ؿ����ź�
                                                                    2��ʾ����ѡ��DAGC����ͽ������ֵ���ݲ�������ؿ����ź�
                                                                    3��ʾ����ѡ��DAGC�����AGC�������ݲ�������ؿ����ź�
                                                                    4��ʾ���Թ۲��������������źź��ж��ź� */
        unsigned int  reserved                  : 24; /* bit[8-31]: ���� */
    } reg;
} GBBP_TEST_MODULE_SEL_UNION;
#define GBBP_TEST_MODULE_SEL_gbbp_module_test_sel_low_START   (0)
#define GBBP_TEST_MODULE_SEL_gbbp_module_test_sel_low_END     (4)
#define GBBP_TEST_MODULE_SEL_gbbp_module_test_sel_high_START  (5)
#define GBBP_TEST_MODULE_SEL_gbbp_module_test_sel_high_END    (7)


/*****************************************************************************
 �ṹ��    : GBBP_GSP_START_TDMA_QB_RPT_UNION
 �ṹ˵��  : GSP_START_TDMA_QB_RPT �Ĵ����ṹ���塣��ַƫ����:0x5714����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gsp_start_tdma_qb_rpt_reg;
    struct
    {
        unsigned int  gsp_start_tdma_qb    : 13; /* bit[0-12] : ��ӦGTC�������ĸ��������ź�����tdma_qbֵ�ϱ��� */
        unsigned int  reserved             : 15; /* bit[13-27]: ���� */
        unsigned int  cpu_sample_start_sel : 4;  /* bit[28-31]: 4'd0: gsp_agc_fast_start�źŶ�Ӧ��gtc_tdma_qb����ֵ
                                                                4'd1: gsp_agc_slow_start�źŶ�Ӧ��gtc_tdma_qb����ֵ
                                                                4'd2: gsp_srch_start�źŶ�Ӧ��gtc_tdma_qb����ֵ
                                                                4'd3: gsp_demod_start�źŶ�Ӧ��gtc_tdma_qb����ֵ
                                                                4'd4: gsp_rx_start�źŶ�Ӧ��gtc_tdma_qb����ֵ
                                                                4'd5: gsp_rx_stop�źŶ�Ӧ��gtc_tdma_qb����ֵ
                                                                4'd6: gsp_dec_start�źŶ�Ӧ��gtc_tdma_qb����ֵ
                                                                4'd7: gsp_ul_cod_start�źŶ�Ӧ��gtc_tdma_qb����ֵ
                                                                4'd8: gsp_ul_map_start�źŶ�Ӧ��gtc_tdma_qb����ֵ
                                                                4'd9: gsp_mod_start�źŶ�Ӧ��gtc_tdma_qb����ֵ
                                                                4'd10: gsp_mod_stop�źŶ�Ӧ��gtc_tdma_qb����ֵ
                                                                4'd11: gsp_pa_start�źŶ�Ӧ��gtc_tdma_qb����ֵ
                                                                4'd12: gsp_pa_stop�źŶ�Ӧ��gtc_tdma_qb����ֵ
                                                                4'd13: gsp_pa_single_start�źŶ�Ӧ��gtc_tdma_qb����ֵ
                                                                4'd14: gsp_pa_change�źŶ�Ӧ��gtc_tdma_qb����ֵ
                                                                ������ */
    } reg;
} GBBP_GSP_START_TDMA_QB_RPT_UNION;
#define GBBP_GSP_START_TDMA_QB_RPT_gsp_start_tdma_qb_START     (0)
#define GBBP_GSP_START_TDMA_QB_RPT_gsp_start_tdma_qb_END       (12)
#define GBBP_GSP_START_TDMA_QB_RPT_cpu_sample_start_sel_START  (28)
#define GBBP_GSP_START_TDMA_QB_RPT_cpu_sample_start_sel_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_DSP_DEDICATE_CTRL_REG_UNION
 �ṹ˵��  : DSP_DEDICATE_CTRL_REG �Ĵ����ṹ���塣��ַƫ����:0x5720����ֵ:0x8000031C�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      dsp_dedicate_ctrl_reg_reg;
    struct
    {
        unsigned int  cpu_alpha_noise_thresh    : 16; /* bit[0-15] : TOA Alpha�˲����ޡ�Ĭ��11'd796���뾶�����ۼ�ֵ����6bit�Ľ�����бȽϡ� */
        unsigned int  gbbp_redudant             : 15; /* bit[16-30]: Ԥ��������Ĵ����� */
        unsigned int  cpu_alpha_noise_thresh_en : 1;  /* bit[31]   : TOA Alpha�˲�����ʹ���źš�1��ʾ���������о��Ƿ�ʹ��Alpha���ܡ� */
    } reg;
} GBBP_DSP_DEDICATE_CTRL_REG_UNION;
#define GBBP_DSP_DEDICATE_CTRL_REG_cpu_alpha_noise_thresh_START     (0)
#define GBBP_DSP_DEDICATE_CTRL_REG_cpu_alpha_noise_thresh_END       (15)
#define GBBP_DSP_DEDICATE_CTRL_REG_gbbp_redudant_START              (16)
#define GBBP_DSP_DEDICATE_CTRL_REG_gbbp_redudant_END                (30)
#define GBBP_DSP_DEDICATE_CTRL_REG_cpu_alpha_noise_thresh_en_START  (31)
#define GBBP_DSP_DEDICATE_CTRL_REG_cpu_alpha_noise_thresh_en_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_ERR_TRIG_UNION
 �ṹ˵��  : ERR_TRIG �Ĵ����ṹ���塣��ַƫ����:0x5764����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      err_trig_reg;
    struct
    {
        unsigned int  err_trig : 1;  /* bit[0]   : �޷�trigger�źţ�����ƽ̨���ⶨλʹ�á� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} GBBP_ERR_TRIG_UNION;
#define GBBP_ERR_TRIG_err_trig_START  (0)
#define GBBP_ERR_TRIG_err_trig_END    (0)


/*****************************************************************************
 �ṹ��    : GBBP_GBBP_EDGE_VERSION_UNION
 �ṹ˵��  : GBBP_EDGE_VERSION �Ĵ����ṹ���塣��ַƫ����:0x5768����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gbbp_edge_version_reg;
    struct
    {
        unsigned int  edge_flag : 1;  /* bit[0]   : V2R1�汾����bit����Ϊ1�������� */
        unsigned int  reserved  : 31; /* bit[1-31]: ���� */
    } reg;
} GBBP_GBBP_EDGE_VERSION_UNION;
#define GBBP_GBBP_EDGE_VERSION_edge_flag_START  (0)
#define GBBP_GBBP_EDGE_VERSION_edge_flag_END    (0)


/*****************************************************************************
 �ṹ��    : GBBP_GROSS_CARRIER_ENERGY5_UNION
 �ṹ˵��  : GROSS_CARRIER_ENERGY5 �Ĵ����ṹ���塣��ַƫ����:0x529C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gross_carrier_energy5_reg;
    struct
    {
        unsigned int  thres_c_5d : 19; /* bit[0-18] : �������һ��BURST���ǰ�ֲ�Cֵ�ϱ��������� */
        unsigned int  reserved   : 13; /* bit[19-31]: ���� */
    } reg;
} GBBP_GROSS_CARRIER_ENERGY5_UNION;
#define GBBP_GROSS_CARRIER_ENERGY5_thres_c_5d_START  (0)
#define GBBP_GROSS_CARRIER_ENERGY5_thres_c_5d_END    (18)


/*****************************************************************************
 �ṹ��    : GBBP_GROSS_INTERFERE_ENERGY5_UNION
 �ṹ˵��  : GROSS_INTERFERE_ENERGY5 �Ĵ����ṹ���塣��ַƫ����:0x5300����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gross_interfere_energy5_reg;
    struct
    {
        unsigned int  thres_i_5d : 19; /* bit[0-18] : �������һ��BURST���ǰ�ֲ�Iֵ�ϱ��������� */
        unsigned int  reserved   : 13; /* bit[19-31]: ���� */
    } reg;
} GBBP_GROSS_INTERFERE_ENERGY5_UNION;
#define GBBP_GROSS_INTERFERE_ENERGY5_thres_i_5d_START  (0)
#define GBBP_GROSS_INTERFERE_ENERGY5_thres_i_5d_END    (18)


/*****************************************************************************
 �ṹ��    : GBBP_GROSS_CARRIER_ENERGY6_UNION
 �ṹ˵��  : GROSS_CARRIER_ENERGY6 �Ĵ����ṹ���塣��ַƫ����:0x5304����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gross_carrier_energy6_reg;
    struct
    {
        unsigned int  thres_c_6d : 19; /* bit[0-18] : ��������һ��BURST���ǰ�ֲ�Cֵ�ϱ��������� */
        unsigned int  reserved   : 13; /* bit[19-31]: ���� */
    } reg;
} GBBP_GROSS_CARRIER_ENERGY6_UNION;
#define GBBP_GROSS_CARRIER_ENERGY6_thres_c_6d_START  (0)
#define GBBP_GROSS_CARRIER_ENERGY6_thres_c_6d_END    (18)


/*****************************************************************************
 �ṹ��    : GBBP_GROSS_INTERFERE_ENERGY6_UNION
 �ṹ˵��  : GROSS_INTERFERE_ENERGY6 �Ĵ����ṹ���塣��ַƫ����:0x5308����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gross_interfere_energy6_reg;
    struct
    {
        unsigned int  thres_i_6d : 19; /* bit[0-18] : ��������һ��BURST���ǰ�ֲ�Iֵ�ϱ��������� */
        unsigned int  reserved   : 13; /* bit[19-31]: ���� */
    } reg;
} GBBP_GROSS_INTERFERE_ENERGY6_UNION;
#define GBBP_GROSS_INTERFERE_ENERGY6_thres_i_6d_START  (0)
#define GBBP_GROSS_INTERFERE_ENERGY6_thres_i_6d_END    (18)


/*****************************************************************************
 �ṹ��    : GBBP_AAGC_GAIN5_CPU_UNION
 �ṹ˵��  : AAGC_GAIN5_CPU �Ĵ����ṹ���塣��ַƫ����:0x5290����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      aagc_gain5_cpu_reg;
    struct
    {
        unsigned int  next_gain_5d     : 3;  /* bit[0-2]  : �����һ��ʱ϶AGC�����������档 */
        unsigned int  reserved_0       : 5;  /* bit[3-7]  : ���� */
        unsigned int  rssi_5d          : 12; /* bit[8-19] : �����һ��ʱ϶AGC RSSIֵ����λ0.125dBm���ϱ���CPU����ֵ���ǿտڵ�RSSIֵ�� */
        unsigned int  reserved_1       : 4;  /* bit[20-23]: ���� */
        unsigned int  curr_gain_5d     : 3;  /* bit[24-26]: �����һ��ʱ϶AAGC��λ�ϱ��� */
        unsigned int  reserved_2       : 4;  /* bit[27-30]: ���� */
        unsigned int  agc_fast_flag_5d : 1;  /* bit[31]   : �����һ��ʱ϶�����ٲ�����־�ϱ���1��ʾ��ǰΪ���ٲ�����0��ʾ��ǰΪ���ٲ����� */
    } reg;
} GBBP_AAGC_GAIN5_CPU_UNION;
#define GBBP_AAGC_GAIN5_CPU_next_gain_5d_START      (0)
#define GBBP_AAGC_GAIN5_CPU_next_gain_5d_END        (2)
#define GBBP_AAGC_GAIN5_CPU_rssi_5d_START           (8)
#define GBBP_AAGC_GAIN5_CPU_rssi_5d_END             (19)
#define GBBP_AAGC_GAIN5_CPU_curr_gain_5d_START      (24)
#define GBBP_AAGC_GAIN5_CPU_curr_gain_5d_END        (26)
#define GBBP_AAGC_GAIN5_CPU_agc_fast_flag_5d_START  (31)
#define GBBP_AAGC_GAIN5_CPU_agc_fast_flag_5d_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_AAGC_GAIN6_CPU_UNION
 �ṹ˵��  : AAGC_GAIN6_CPU �Ĵ����ṹ���塣��ַƫ����:0x5294����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      aagc_gain6_cpu_reg;
    struct
    {
        unsigned int  next_gain_6d     : 3;  /* bit[0-2]  : ��Զһ��ʱ϶AGC�����������档 */
        unsigned int  reserved_0       : 5;  /* bit[3-7]  : ���� */
        unsigned int  rssi_6d          : 12; /* bit[8-19] : ��Զһ��ʱ϶AGC RSSIֵ����λ0.125dBm���ϱ���CPU����ֵ���ǿտڵ�RSSIֵ�� */
        unsigned int  reserved_1       : 4;  /* bit[20-23]: ���� */
        unsigned int  curr_gain_6d     : 3;  /* bit[24-26]: ��Զһ��ʱ϶AAGC��λ�ϱ��� */
        unsigned int  reserved_2       : 4;  /* bit[27-30]: ���� */
        unsigned int  agc_fast_flag_6d : 1;  /* bit[31]   : ��Զһ��ʱ϶�����ٲ�����־�ϱ���1��ʾ��ǰΪ���ٲ�����0��ʾ��ǰΪ���ٲ����� */
    } reg;
} GBBP_AAGC_GAIN6_CPU_UNION;
#define GBBP_AAGC_GAIN6_CPU_next_gain_6d_START      (0)
#define GBBP_AAGC_GAIN6_CPU_next_gain_6d_END        (2)
#define GBBP_AAGC_GAIN6_CPU_rssi_6d_START           (8)
#define GBBP_AAGC_GAIN6_CPU_rssi_6d_END             (19)
#define GBBP_AAGC_GAIN6_CPU_curr_gain_6d_START      (24)
#define GBBP_AAGC_GAIN6_CPU_curr_gain_6d_END        (26)
#define GBBP_AAGC_GAIN6_CPU_agc_fast_flag_6d_START  (31)
#define GBBP_AAGC_GAIN6_CPU_agc_fast_flag_6d_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_GDUMP_GEN_CONFIG_UNION
 �ṹ˵��  : CPU_GDUMP_GEN_CONFIG �Ĵ����ṹ���塣��ַƫ����:0xf004����ֵ:0x00000013�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_gdump_gen_config_reg;
    struct
    {
        unsigned int  dump_fifo_watermarker_g : 3;  /* bit[0-2]  : FIFOˮ�����ѡ��
                                                                   0����ʾˮ�����2��
                                                                   1����ʾˮ�����4��
                                                                   2����ʾˮ�����8��
                                                                   3����ʾˮ�����16��
                                                                   4����ʾˮ�����32��
                                                                   5����ʾˮ�����64��
                                                                   6����ʾˮ�����128��
                                                                   7��
                                                                   SOCˮ�����֧��1~16 */
        unsigned int  reserved_0              : 1;  /* bit[3]    : ���� */
        unsigned int  cpu_sample_data_sel     : 3;  /* bit[4-6]  : ��������Դѡ��
                                                                   0��ѡ������ŵ��˲����������ݣ�
                                                                   1��ѡ������ŵ��˲���������ݣ�
                                                                   2��ѡ�����AGC�������ݣ�
                                                                   3��ѡ�����AGCȥֱ���������ڲ��������ݣ�
                                                                   4��ѡ�����AGCȥֱ���������ڽ�������������ݣ�
                                                                   5��ѡ�����DAGC������ݣ������ڲ�����������ݣ�
                                                                   6�����з��͵������ݣ�
                                                                   7�� */
        unsigned int  reserved_1              : 1;  /* bit[7]    : ���� */
        unsigned int  cpu_sample_config_sel   : 1;  /* bit[8]    : ����ģ����������ѡ��
                                                                   0��ѡ��ʹ��GTC���ýӿ�
                                                                   1��ѡ��ʹ��CPU���ýӿ�
                                                                   Ĭ������Ϊ0�� */
        unsigned int  reserved_2              : 7;  /* bit[9-15] : ���� */
        unsigned int  tx_test_cnt             : 8;  /* bit[16-23]: G���в��Լ����� */
        unsigned int  reserved_3              : 7;  /* bit[24-30]: ���� */
        unsigned int  dump_en_g               : 1;  /* bit[31]   : ����ģ�������ܣ�������ʱ���ſأ���������ģʽ����������Ҫ���ô��ź���Ч���ߵ�ƽ��ʾ�ù��ܴ򿪡� */
    } reg;
} GBBP_CPU_GDUMP_GEN_CONFIG_UNION;
#define GBBP_CPU_GDUMP_GEN_CONFIG_dump_fifo_watermarker_g_START  (0)
#define GBBP_CPU_GDUMP_GEN_CONFIG_dump_fifo_watermarker_g_END    (2)
#define GBBP_CPU_GDUMP_GEN_CONFIG_cpu_sample_data_sel_START      (4)
#define GBBP_CPU_GDUMP_GEN_CONFIG_cpu_sample_data_sel_END        (6)
#define GBBP_CPU_GDUMP_GEN_CONFIG_cpu_sample_config_sel_START    (8)
#define GBBP_CPU_GDUMP_GEN_CONFIG_cpu_sample_config_sel_END      (8)
#define GBBP_CPU_GDUMP_GEN_CONFIG_tx_test_cnt_START              (16)
#define GBBP_CPU_GDUMP_GEN_CONFIG_tx_test_cnt_END                (23)
#define GBBP_CPU_GDUMP_GEN_CONFIG_dump_en_g_START                (31)
#define GBBP_CPU_GDUMP_GEN_CONFIG_dump_en_g_END                  (31)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_GDUMP_SAM_LOW_TIMING_UNION
 �ṹ˵��  : CPU_GDUMP_SAM_LOW_TIMING �Ĵ����ṹ���塣��ַƫ����:0xf00C����ֵ:0x00001FFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_gdump_sam_low_timing_reg;
    struct
    {
        unsigned int  dump_gtc_tdma_qb : 13; /* bit[0-12] : ��������ʱ�̲���ģʽ�£�������ʼλ�ã�35'h7ffffffff��ʾ����������������Ϊ35bit��[12:0]��Ĭ��ֵΪ��������ģʽ�� */
        unsigned int  reserved         : 19; /* bit[13-31]: ���� */
    } reg;
} GBBP_CPU_GDUMP_SAM_LOW_TIMING_UNION;
#define GBBP_CPU_GDUMP_SAM_LOW_TIMING_dump_gtc_tdma_qb_START  (0)
#define GBBP_CPU_GDUMP_SAM_LOW_TIMING_dump_gtc_tdma_qb_END    (12)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_GDUMP_SAM_HIGH_TIMING_UNION
 �ṹ˵��  : CPU_GDUMP_SAM_HIGH_TIMING �Ĵ����ṹ���塣��ַƫ����:0xf010����ֵ:0x07FF07FF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_gdump_sam_high_timing_reg;
    struct
    {
        unsigned int  dump_gtc_fn_low  : 11; /* bit[0-10] : ��������ʱ�̲���ģʽ�£�������ʼλ�ã�35'h7ffffffff��ʾ����������������Ϊ35bit��[23:13]��Ĭ��ֵΪ��������ģʽ�� */
        unsigned int  reserved_0       : 5;  /* bit[11-15]: ���� */
        unsigned int  dump_gtc_fn_high : 11; /* bit[16-26]: ��������ʱ�̲���ģʽ�£�������ʼλ�ã�35'h7ffffffff��ʾ����������������Ϊ35bit��[34:24]��Ĭ��ֵΪ��������ģʽ�� */
        unsigned int  reserved_1       : 5;  /* bit[27-31]: ���� */
    } reg;
} GBBP_CPU_GDUMP_SAM_HIGH_TIMING_UNION;
#define GBBP_CPU_GDUMP_SAM_HIGH_TIMING_dump_gtc_fn_low_START   (0)
#define GBBP_CPU_GDUMP_SAM_HIGH_TIMING_dump_gtc_fn_low_END     (10)
#define GBBP_CPU_GDUMP_SAM_HIGH_TIMING_dump_gtc_fn_high_START  (16)
#define GBBP_CPU_GDUMP_SAM_HIGH_TIMING_dump_gtc_fn_high_END    (26)


/*****************************************************************************
 �ṹ��    : GBBP_CPU_GDUMP_RECV_CONFIG_UNION
 �ṹ˵��  : CPU_GDUMP_RECV_CONFIG �Ĵ����ṹ���塣��ַƫ����:0xf014����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_gdump_recv_config_reg;
    struct
    {
        unsigned int  cpu_rx_start : 1;  /* bit[0]    : CPU���ò������������źš� */
        unsigned int  reserved_0   : 7;  /* bit[1-7]  : ���� */
        unsigned int  cpu_rx_stop  : 1;  /* bit[8]    : CPU���ò�������ֹͣ�źţ����������ݸ������޳�ʱ���ø��ź�ֹͣ������ */
        unsigned int  reserved_1   : 7;  /* bit[9-15] : ���� */
        unsigned int  cpu_fifo_clr : 1;  /* bit[16]   : CPU�����첽FIFO�����źš� */
        unsigned int  reserved_2   : 15; /* bit[17-31]: ���� */
    } reg;
} GBBP_CPU_GDUMP_RECV_CONFIG_UNION;
#define GBBP_CPU_GDUMP_RECV_CONFIG_cpu_rx_start_START  (0)
#define GBBP_CPU_GDUMP_RECV_CONFIG_cpu_rx_start_END    (0)
#define GBBP_CPU_GDUMP_RECV_CONFIG_cpu_rx_stop_START   (8)
#define GBBP_CPU_GDUMP_RECV_CONFIG_cpu_rx_stop_END     (8)
#define GBBP_CPU_GDUMP_RECV_CONFIG_cpu_fifo_clr_START  (16)
#define GBBP_CPU_GDUMP_RECV_CONFIG_cpu_fifo_clr_END    (16)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_G_CH_PARA_1REG_UNION
 �ṹ˵��  : ADDR_G_CH_PARA_1REG �Ĵ����ṹ���塣��ַƫ����:0xf294����ֵ:0x0FFD0001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_1reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h0_ext : 12; /* bit[0-11] : GSM�����ŵ��˲�����ϵ��0,12bit�з����� */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: ���� */
        unsigned int  cpu_g_ch_h1_ext : 12; /* bit[16-27]: GSM�����ŵ��˲�����ϵ��1,12bit�з����� */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_ADDR_G_CH_PARA_1REG_UNION;
#define GBBP_ADDR_G_CH_PARA_1REG_cpu_g_ch_h0_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_1REG_cpu_g_ch_h0_ext_END    (11)
#define GBBP_ADDR_G_CH_PARA_1REG_cpu_g_ch_h1_ext_START  (16)
#define GBBP_ADDR_G_CH_PARA_1REG_cpu_g_ch_h1_ext_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_G_CH_PARA_2REG_UNION
 �ṹ˵��  : ADDR_G_CH_PARA_2REG �Ĵ����ṹ���塣��ַƫ����:0xf298����ֵ:0x0FFA0FFA�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_2reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h2_ext : 12; /* bit[0-11] : GSM�����ŵ��˲�����ϵ��2,12bit�з����� */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: ���� */
        unsigned int  cpu_g_ch_h3_ext : 12; /* bit[16-27]: GSM�����ŵ��˲�����ϵ��3,12bit�з����� */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_ADDR_G_CH_PARA_2REG_UNION;
#define GBBP_ADDR_G_CH_PARA_2REG_cpu_g_ch_h2_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_2REG_cpu_g_ch_h2_ext_END    (11)
#define GBBP_ADDR_G_CH_PARA_2REG_cpu_g_ch_h3_ext_START  (16)
#define GBBP_ADDR_G_CH_PARA_2REG_cpu_g_ch_h3_ext_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_G_CH_PARA_3REG_UNION
 �ṹ˵��  : ADDR_G_CH_PARA_3REG �Ĵ����ṹ���塣��ַƫ����:0xf29C����ֵ:0x00060FFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_3reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h4_ext : 12; /* bit[0-11] : GSM�����ŵ��˲�����ϵ��4,12bit�з����� */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: ���� */
        unsigned int  cpu_g_ch_h5_ext : 12; /* bit[16-27]: GSM�����ŵ��˲�����ϵ��5,12bit�з����� */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_ADDR_G_CH_PARA_3REG_UNION;
#define GBBP_ADDR_G_CH_PARA_3REG_cpu_g_ch_h4_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_3REG_cpu_g_ch_h4_ext_END    (11)
#define GBBP_ADDR_G_CH_PARA_3REG_cpu_g_ch_h5_ext_START  (16)
#define GBBP_ADDR_G_CH_PARA_3REG_cpu_g_ch_h5_ext_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_G_CH_PARA_4REG_UNION
 �ṹ˵��  : ADDR_G_CH_PARA_4REG �Ĵ����ṹ���塣��ַƫ����:0xf2A0����ֵ:0x000C000C�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_4reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h6_ext : 12; /* bit[0-11] : GSM�����ŵ��˲�����ϵ��6,12bit�з����� */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: ���� */
        unsigned int  cpu_g_ch_h7_ext : 12; /* bit[16-27]: GSM�����ŵ��˲�����ϵ��7,12bit�з����� */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_ADDR_G_CH_PARA_4REG_UNION;
#define GBBP_ADDR_G_CH_PARA_4REG_cpu_g_ch_h6_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_4REG_cpu_g_ch_h6_ext_END    (11)
#define GBBP_ADDR_G_CH_PARA_4REG_cpu_g_ch_h7_ext_START  (16)
#define GBBP_ADDR_G_CH_PARA_4REG_cpu_g_ch_h7_ext_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_G_CH_PARA_5REG_UNION
 �ṹ˵��  : ADDR_G_CH_PARA_5REG �Ĵ����ṹ���塣��ַƫ����:0xf2A4����ֵ:0x0FF40002�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_5reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h8_ext : 12; /* bit[0-11] : GSM�����ŵ��˲�����ϵ��8,12bit�з����� */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: ���� */
        unsigned int  cpu_g_ch_h9_ext : 12; /* bit[16-27]: GSM�����ŵ��˲�����ϵ��9,12bit�з����� */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_ADDR_G_CH_PARA_5REG_UNION;
#define GBBP_ADDR_G_CH_PARA_5REG_cpu_g_ch_h8_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_5REG_cpu_g_ch_h8_ext_END    (11)
#define GBBP_ADDR_G_CH_PARA_5REG_cpu_g_ch_h9_ext_START  (16)
#define GBBP_ADDR_G_CH_PARA_5REG_cpu_g_ch_h9_ext_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_G_CH_PARA_6REG_UNION
 �ṹ˵��  : ADDR_G_CH_PARA_6REG �Ĵ����ṹ���塣��ַƫ����:0xf2A8����ֵ:0x0FEB0FE9�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_6reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h10_ext : 12; /* bit[0-11] : GSM�����ŵ��˲�����ϵ��10,12bit�з����� */
        unsigned int  reserved_0       : 4;  /* bit[12-15]: ���� */
        unsigned int  cpu_g_ch_h11_ext : 12; /* bit[16-27]: GSM�����ŵ��˲�����ϵ��11,12bit�з����� */
        unsigned int  reserved_1       : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_ADDR_G_CH_PARA_6REG_UNION;
#define GBBP_ADDR_G_CH_PARA_6REG_cpu_g_ch_h10_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_6REG_cpu_g_ch_h10_ext_END    (11)
#define GBBP_ADDR_G_CH_PARA_6REG_cpu_g_ch_h11_ext_START  (16)
#define GBBP_ADDR_G_CH_PARA_6REG_cpu_g_ch_h11_ext_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_G_CH_PARA_7REG_UNION
 �ṹ˵��  : ADDR_G_CH_PARA_7REG �Ĵ����ṹ���塣��ַƫ����:0xf2AC����ֵ:0x00160FFD�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_7reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h12_ext : 12; /* bit[0-11] : GSM�����ŵ��˲�����ϵ��12,12bit�з����� */
        unsigned int  reserved_0       : 4;  /* bit[12-15]: ���� */
        unsigned int  cpu_g_ch_h13_ext : 12; /* bit[16-27]: GSM�����ŵ��˲�����ϵ��13,12bit�з����� */
        unsigned int  reserved_1       : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_ADDR_G_CH_PARA_7REG_UNION;
#define GBBP_ADDR_G_CH_PARA_7REG_cpu_g_ch_h12_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_7REG_cpu_g_ch_h12_ext_END    (11)
#define GBBP_ADDR_G_CH_PARA_7REG_cpu_g_ch_h13_ext_START  (16)
#define GBBP_ADDR_G_CH_PARA_7REG_cpu_g_ch_h13_ext_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_G_CH_PARA_8REG_UNION
 �ṹ˵��  : ADDR_G_CH_PARA_8REG �Ĵ����ṹ���塣��ַƫ����:0xf2B0����ֵ:0x00220027�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_8reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h14_ext : 12; /* bit[0-11] : GSM�����ŵ��˲�����ϵ��14,12bit�з����� */
        unsigned int  reserved_0       : 4;  /* bit[12-15]: ���� */
        unsigned int  cpu_g_ch_h15_ext : 12; /* bit[16-27]: GSM�����ŵ��˲�����ϵ��15,12bit�з����� */
        unsigned int  reserved_1       : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_ADDR_G_CH_PARA_8REG_UNION;
#define GBBP_ADDR_G_CH_PARA_8REG_cpu_g_ch_h14_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_8REG_cpu_g_ch_h14_ext_END    (11)
#define GBBP_ADDR_G_CH_PARA_8REG_cpu_g_ch_h15_ext_START  (16)
#define GBBP_ADDR_G_CH_PARA_8REG_cpu_g_ch_h15_ext_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_G_CH_PARA_9REG_UNION
 �ṹ˵��  : ADDR_G_CH_PARA_9REG �Ĵ����ṹ���塣��ַƫ����:0xf2B8����ֵ:0x0FDB0004�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_9reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h16_ext : 12; /* bit[0-11] : GSM�����ŵ��˲�����ϵ��16,12bit�з����� */
        unsigned int  reserved_0       : 4;  /* bit[12-15]: ���� */
        unsigned int  cpu_g_ch_h17_ext : 12; /* bit[16-27]: GSM�����ŵ��˲�����ϵ��17,12bit�з����� */
        unsigned int  reserved_1       : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_ADDR_G_CH_PARA_9REG_UNION;
#define GBBP_ADDR_G_CH_PARA_9REG_cpu_g_ch_h16_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_9REG_cpu_g_ch_h16_ext_END    (11)
#define GBBP_ADDR_G_CH_PARA_9REG_cpu_g_ch_h17_ext_START  (16)
#define GBBP_ADDR_G_CH_PARA_9REG_cpu_g_ch_h17_ext_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_G_CH_PARA_10REG_UNION
 �ṹ˵��  : ADDR_G_CH_PARA_10REG �Ĵ����ṹ���塣��ַƫ����:0xf2C4����ֵ:0x0FC90FBF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_10reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h18_ext : 12; /* bit[0-11] : GSM�����ŵ��˲�����ϵ��18,12bit�з����� */
        unsigned int  reserved_0       : 4;  /* bit[12-15]: ���� */
        unsigned int  cpu_g_ch_h19_ext : 12; /* bit[16-27]: GSM�����ŵ��˲�����ϵ��19,12bit�з����� */
        unsigned int  reserved_1       : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_ADDR_G_CH_PARA_10REG_UNION;
#define GBBP_ADDR_G_CH_PARA_10REG_cpu_g_ch_h18_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_10REG_cpu_g_ch_h18_ext_END    (11)
#define GBBP_ADDR_G_CH_PARA_10REG_cpu_g_ch_h19_ext_START  (16)
#define GBBP_ADDR_G_CH_PARA_10REG_cpu_g_ch_h19_ext_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_G_CH_PARA_11REG_UNION
 �ṹ˵��  : ADDR_G_CH_PARA_11REG �Ĵ����ṹ���塣��ַƫ����:0xf2C8����ֵ:0x00400FFC�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_11reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h20_ext : 12; /* bit[0-11] : GSM�����ŵ��˲�����ϵ��20,12bit�з����� */
        unsigned int  reserved_0       : 4;  /* bit[12-15]: ���� */
        unsigned int  cpu_g_ch_h21_ext : 12; /* bit[16-27]: GSM�����ŵ��˲�����ϵ��21,12bit�з����� */
        unsigned int  reserved_1       : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_ADDR_G_CH_PARA_11REG_UNION;
#define GBBP_ADDR_G_CH_PARA_11REG_cpu_g_ch_h20_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_11REG_cpu_g_ch_h20_ext_END    (11)
#define GBBP_ADDR_G_CH_PARA_11REG_cpu_g_ch_h21_ext_START  (16)
#define GBBP_ADDR_G_CH_PARA_11REG_cpu_g_ch_h21_ext_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_G_CH_PARA_12REG_UNION
 �ṹ˵��  : ADDR_G_CH_PARA_12REG �Ĵ����ṹ���塣��ַƫ����:0xf2CC����ֵ:0x005D006E�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_12reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h22_ext : 12; /* bit[0-11] : GSM�����ŵ��˲�����ϵ��22,12bit�з����� */
        unsigned int  reserved_0       : 4;  /* bit[12-15]: ���� */
        unsigned int  cpu_g_ch_h23_ext : 12; /* bit[16-27]: GSM�����ŵ��˲�����ϵ��23,12bit�з����� */
        unsigned int  reserved_1       : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_ADDR_G_CH_PARA_12REG_UNION;
#define GBBP_ADDR_G_CH_PARA_12REG_cpu_g_ch_h22_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_12REG_cpu_g_ch_h22_ext_END    (11)
#define GBBP_ADDR_G_CH_PARA_12REG_cpu_g_ch_h23_ext_START  (16)
#define GBBP_ADDR_G_CH_PARA_12REG_cpu_g_ch_h23_ext_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_G_CH_PARA_13REG_UNION
 �ṹ˵��  : ADDR_G_CH_PARA_13REG �Ĵ����ṹ���塣��ַƫ����:0xf2D0����ֵ:0x0F890005�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_13reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h24_ext : 12; /* bit[0-11] : GSM�����ŵ��˲�����ϵ��24,12bit�з����� */
        unsigned int  reserved_0       : 4;  /* bit[12-15]: ���� */
        unsigned int  cpu_g_ch_h25_ext : 12; /* bit[16-27]: GSM�����ŵ��˲�����ϵ��25,12bit�з����� */
        unsigned int  reserved_1       : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_ADDR_G_CH_PARA_13REG_UNION;
#define GBBP_ADDR_G_CH_PARA_13REG_cpu_g_ch_h24_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_13REG_cpu_g_ch_h24_ext_END    (11)
#define GBBP_ADDR_G_CH_PARA_13REG_cpu_g_ch_h25_ext_START  (16)
#define GBBP_ADDR_G_CH_PARA_13REG_cpu_g_ch_h25_ext_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_G_CH_PARA_14REG_UNION
 �ṹ˵��  : ADDR_G_CH_PARA_14REG �Ĵ����ṹ���塣��ַƫ����:0xf2D4����ֵ:0x0F490F31�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_14reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h26_ext : 12; /* bit[0-11] : GSM�����ŵ��˲�����ϵ��26,12bit�з����� */
        unsigned int  reserved_0       : 4;  /* bit[12-15]: ���� */
        unsigned int  cpu_g_ch_h27_ext : 12; /* bit[16-27]: GSM�����ŵ��˲�����ϵ��27,12bit�з����� */
        unsigned int  reserved_1       : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_ADDR_G_CH_PARA_14REG_UNION;
#define GBBP_ADDR_G_CH_PARA_14REG_cpu_g_ch_h26_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_14REG_cpu_g_ch_h26_ext_END    (11)
#define GBBP_ADDR_G_CH_PARA_14REG_cpu_g_ch_h27_ext_START  (16)
#define GBBP_ADDR_G_CH_PARA_14REG_cpu_g_ch_h27_ext_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_G_CH_PARA_15REG_UNION
 �ṹ˵��  : ADDR_G_CH_PARA_15REG �Ĵ����ṹ���塣��ַƫ����:0xf2D8����ֵ:0x01300FFB�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_15reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h28_ext : 12; /* bit[0-11] : GSM�����ŵ��˲�����ϵ��28,12bit�з����� */
        unsigned int  reserved_0       : 4;  /* bit[12-15]: ���� */
        unsigned int  cpu_g_ch_h29_ext : 12; /* bit[16-27]: GSM�����ŵ��˲�����ϵ��29,12bit�з����� */
        unsigned int  reserved_1       : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_ADDR_G_CH_PARA_15REG_UNION;
#define GBBP_ADDR_G_CH_PARA_15REG_cpu_g_ch_h28_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_15REG_cpu_g_ch_h28_ext_END    (11)
#define GBBP_ADDR_G_CH_PARA_15REG_cpu_g_ch_h29_ext_START  (16)
#define GBBP_ADDR_G_CH_PARA_15REG_cpu_g_ch_h29_ext_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_G_CH_PARA_16REG_UNION
 �ṹ˵��  : ADDR_G_CH_PARA_16REG �Ĵ����ṹ���塣��ַƫ����:0xf2DC����ֵ:0x03AE0293�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_16reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h30_ext : 12; /* bit[0-11] : GSM�����ŵ��˲�����ϵ��30,12bit�з����� */
        unsigned int  reserved_0       : 4;  /* bit[12-15]: ���� */
        unsigned int  cpu_g_ch_h31_ext : 12; /* bit[16-27]: GSM�����ŵ��˲�����ϵ��31,12bit�з����� */
        unsigned int  reserved_1       : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_ADDR_G_CH_PARA_16REG_UNION;
#define GBBP_ADDR_G_CH_PARA_16REG_cpu_g_ch_h30_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_16REG_cpu_g_ch_h30_ext_END    (11)
#define GBBP_ADDR_G_CH_PARA_16REG_cpu_g_ch_h31_ext_START  (16)
#define GBBP_ADDR_G_CH_PARA_16REG_cpu_g_ch_h31_ext_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_G_CH_PARA_17REG_UNION
 �ṹ˵��  : ADDR_G_CH_PARA_17REG �Ĵ����ṹ���塣��ַƫ����:0xf2E0����ֵ:0x00000419�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_ch_para_17reg_reg;
    struct
    {
        unsigned int  cpu_g_ch_h32_ext : 12; /* bit[0-11] : GSM�����ŵ��˲�����ϵ��32,12bit�з����� */
        unsigned int  reserved         : 20; /* bit[12-31]: ���� */
    } reg;
} GBBP_ADDR_G_CH_PARA_17REG_UNION;
#define GBBP_ADDR_G_CH_PARA_17REG_cpu_g_ch_h32_ext_START  (0)
#define GBBP_ADDR_G_CH_PARA_17REG_cpu_g_ch_h32_ext_END    (11)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_G_32CH_PARA_1REG_UNION
 �ṹ˵��  : ADDR_G_32CH_PARA_1REG �Ĵ����ṹ���塣��ַƫ����:0xf31C����ֵ:0x0FD80FEC�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_32ch_para_1reg_reg;
    struct
    {
        unsigned int  cpu_g_32ch_h0_ext : 12; /* bit[0-11] : GSM����32���ŵ��˲�����ϵ��0,12bit�з����� */
        unsigned int  reserved_0        : 4;  /* bit[12-15]: ���� */
        unsigned int  cpu_g_32ch_h1_ext : 12; /* bit[16-27]: GSM����32���ŵ��˲�����ϵ��1,12bit�з����� */
        unsigned int  reserved_1        : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_ADDR_G_32CH_PARA_1REG_UNION;
#define GBBP_ADDR_G_32CH_PARA_1REG_cpu_g_32ch_h0_ext_START  (0)
#define GBBP_ADDR_G_32CH_PARA_1REG_cpu_g_32ch_h0_ext_END    (11)
#define GBBP_ADDR_G_32CH_PARA_1REG_cpu_g_32ch_h1_ext_START  (16)
#define GBBP_ADDR_G_32CH_PARA_1REG_cpu_g_32ch_h1_ext_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_G_32CH_PARA_2REG_UNION
 �ṹ˵��  : ADDR_G_32CH_PARA_2REG �Ĵ����ṹ���塣��ַƫ����:0xf320����ֵ:0x0FE80FD0�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_32ch_para_2reg_reg;
    struct
    {
        unsigned int  cpu_g_32ch_h2_ext : 12; /* bit[0-11] : GSM����32���ŵ��˲�����ϵ��2,12bit�з����� */
        unsigned int  reserved_0        : 4;  /* bit[12-15]: ���� */
        unsigned int  cpu_g_32ch_h3_ext : 12; /* bit[16-27]: GSM����32���ŵ��˲�����ϵ��3,12bit�з����� */
        unsigned int  reserved_1        : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_ADDR_G_32CH_PARA_2REG_UNION;
#define GBBP_ADDR_G_32CH_PARA_2REG_cpu_g_32ch_h2_ext_START  (0)
#define GBBP_ADDR_G_32CH_PARA_2REG_cpu_g_32ch_h2_ext_END    (11)
#define GBBP_ADDR_G_32CH_PARA_2REG_cpu_g_32ch_h3_ext_START  (16)
#define GBBP_ADDR_G_32CH_PARA_2REG_cpu_g_32ch_h3_ext_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_G_32CH_PARA_3REG_UNION
 �ṹ˵��  : ADDR_G_32CH_PARA_3REG �Ĵ����ṹ���塣��ַƫ����:0xf324����ֵ:0x004C0018�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_32ch_para_3reg_reg;
    struct
    {
        unsigned int  cpu_g_32ch_h4_ext : 12; /* bit[0-11] : GSM����32���ŵ��˲�����ϵ��4,12bit�з����� */
        unsigned int  reserved_0        : 4;  /* bit[12-15]: ���� */
        unsigned int  cpu_g_32ch_h5_ext : 12; /* bit[16-27]: GSM����32���ŵ��˲�����ϵ��5,12bit�з����� */
        unsigned int  reserved_1        : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_ADDR_G_32CH_PARA_3REG_UNION;
#define GBBP_ADDR_G_32CH_PARA_3REG_cpu_g_32ch_h4_ext_START  (0)
#define GBBP_ADDR_G_32CH_PARA_3REG_cpu_g_32ch_h4_ext_END    (11)
#define GBBP_ADDR_G_32CH_PARA_3REG_cpu_g_32ch_h5_ext_START  (16)
#define GBBP_ADDR_G_32CH_PARA_3REG_cpu_g_32ch_h5_ext_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_G_32CH_PARA_4REG_UNION
 �ṹ˵��  : ADDR_G_32CH_PARA_4REG �Ĵ����ṹ���塣��ַƫ����:0xf328����ֵ:0x0038005C�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_32ch_para_4reg_reg;
    struct
    {
        unsigned int  cpu_g_32ch_h6_ext : 12; /* bit[0-11] : GSM����32���ŵ��˲�����ϵ��6,12bit�з����� */
        unsigned int  reserved_0        : 4;  /* bit[12-15]: ���� */
        unsigned int  cpu_g_32ch_h7_ext : 12; /* bit[16-27]: GSM����32���ŵ��˲�����ϵ��7,12bit�з����� */
        unsigned int  reserved_1        : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_ADDR_G_32CH_PARA_4REG_UNION;
#define GBBP_ADDR_G_32CH_PARA_4REG_cpu_g_32ch_h6_ext_START  (0)
#define GBBP_ADDR_G_32CH_PARA_4REG_cpu_g_32ch_h6_ext_END    (11)
#define GBBP_ADDR_G_32CH_PARA_4REG_cpu_g_32ch_h7_ext_START  (16)
#define GBBP_ADDR_G_32CH_PARA_4REG_cpu_g_32ch_h7_ext_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_G_32CH_PARA_5REG_UNION
 �ṹ˵��  : ADDR_G_32CH_PARA_5REG �Ĵ����ṹ���塣��ַƫ����:0xf32C����ֵ:0x0F780FE0�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_32ch_para_5reg_reg;
    struct
    {
        unsigned int  cpu_g_32ch_h8_ext : 12; /* bit[0-11] : GSM����32���ŵ��˲�����ϵ��8,12bit�з����� */
        unsigned int  reserved_0        : 4;  /* bit[12-15]: ���� */
        unsigned int  cpu_g_32ch_h9_ext : 12; /* bit[16-27]: GSM����32���ŵ��˲�����ϵ��9,12bit�з����� */
        unsigned int  reserved_1        : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_ADDR_G_32CH_PARA_5REG_UNION;
#define GBBP_ADDR_G_32CH_PARA_5REG_cpu_g_32ch_h8_ext_START  (0)
#define GBBP_ADDR_G_32CH_PARA_5REG_cpu_g_32ch_h8_ext_END    (11)
#define GBBP_ADDR_G_32CH_PARA_5REG_cpu_g_32ch_h9_ext_START  (16)
#define GBBP_ADDR_G_32CH_PARA_5REG_cpu_g_32ch_h9_ext_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_G_32CH_PARA_6REG_UNION
 �ṹ˵��  : ADDR_G_32CH_PARA_6REG �Ĵ����ṹ���塣��ַƫ����:0xf330����ֵ:0x0F700F40�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_32ch_para_6reg_reg;
    struct
    {
        unsigned int  cpu_g_32ch_h10_ext : 12; /* bit[0-11] : GSM����32���ŵ��˲�����ϵ��10,12bit�з����� */
        unsigned int  reserved_0         : 4;  /* bit[12-15]: ���� */
        unsigned int  cpu_g_32ch_h11_ext : 12; /* bit[16-27]: GSM����32���ŵ��˲�����ϵ��11,12bit�з����� */
        unsigned int  reserved_1         : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_ADDR_G_32CH_PARA_6REG_UNION;
#define GBBP_ADDR_G_32CH_PARA_6REG_cpu_g_32ch_h10_ext_START  (0)
#define GBBP_ADDR_G_32CH_PARA_6REG_cpu_g_32ch_h10_ext_END    (11)
#define GBBP_ADDR_G_32CH_PARA_6REG_cpu_g_32ch_h11_ext_START  (16)
#define GBBP_ADDR_G_32CH_PARA_6REG_cpu_g_32ch_h11_ext_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_G_32CH_PARA_7REG_UNION
 �ṹ˵��  : ADDR_G_32CH_PARA_7REG �Ĵ����ṹ���塣��ַƫ����:0xf334����ֵ:0x01480028�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_32ch_para_7reg_reg;
    struct
    {
        unsigned int  cpu_g_32ch_h12_ext : 12; /* bit[0-11] : GSM����32���ŵ��˲�����ϵ��12,12bit�з����� */
        unsigned int  reserved_0         : 4;  /* bit[12-15]: ���� */
        unsigned int  cpu_g_32ch_h13_ext : 12; /* bit[16-27]: GSM����32���ŵ��˲�����ϵ��13,12bit�з����� */
        unsigned int  reserved_1         : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_ADDR_G_32CH_PARA_7REG_UNION;
#define GBBP_ADDR_G_32CH_PARA_7REG_cpu_g_32ch_h12_ext_START  (0)
#define GBBP_ADDR_G_32CH_PARA_7REG_cpu_g_32ch_h12_ext_END    (11)
#define GBBP_ADDR_G_32CH_PARA_7REG_cpu_g_32ch_h13_ext_START  (16)
#define GBBP_ADDR_G_32CH_PARA_7REG_cpu_g_32ch_h13_ext_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_G_32CH_PARA_8REG_UNION
 �ṹ˵��  : ADDR_G_32CH_PARA_8REG �Ĵ����ṹ���塣��ַƫ����:0xf338����ֵ:0x037C0284�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_32ch_para_8reg_reg;
    struct
    {
        unsigned int  cpu_g_32ch_h14_ext : 12; /* bit[0-11] : GSM����32���ŵ��˲�����ϵ��14,12bit�з����� */
        unsigned int  reserved_0         : 4;  /* bit[12-15]: ���� */
        unsigned int  cpu_g_32ch_h15_ext : 12; /* bit[16-27]: GSM����32���ŵ��˲�����ϵ��15,12bit�з����� */
        unsigned int  reserved_1         : 4;  /* bit[28-31]: ���� */
    } reg;
} GBBP_ADDR_G_32CH_PARA_8REG_UNION;
#define GBBP_ADDR_G_32CH_PARA_8REG_cpu_g_32ch_h14_ext_START  (0)
#define GBBP_ADDR_G_32CH_PARA_8REG_cpu_g_32ch_h14_ext_END    (11)
#define GBBP_ADDR_G_32CH_PARA_8REG_cpu_g_32ch_h15_ext_START  (16)
#define GBBP_ADDR_G_32CH_PARA_8REG_cpu_g_32ch_h15_ext_END    (27)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_G_32CH_PARA_9REG_UNION
 �ṹ˵��  : ADDR_G_32CH_PARA_9REG �Ĵ����ṹ���塣��ַƫ����:0xf33C����ֵ:0x000003D8�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_g_32ch_para_9reg_reg;
    struct
    {
        unsigned int  cpu_g_32ch_h16_ext : 12; /* bit[0-11] : GSM����32���ŵ��˲�����ϵ��16,12bit�з����� */
        unsigned int  reserved           : 20; /* bit[12-31]: ���� */
    } reg;
} GBBP_ADDR_G_32CH_PARA_9REG_UNION;
#define GBBP_ADDR_G_32CH_PARA_9REG_cpu_g_32ch_h16_ext_START  (0)
#define GBBP_ADDR_G_32CH_PARA_9REG_cpu_g_32ch_h16_ext_END    (11)


/*****************************************************************************
 �ṹ��    : GBBP_CLIP_MODE_SEL_UNION
 �ṹ˵��  : CLIP_MODE_SEL �Ĵ����ṹ���塣��ַƫ����:0xf2E8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      clip_mode_sel_reg;
    struct
    {
        unsigned int  cpu_gain0_clip_mode_sel : 2;  /* bit[0-1]  : ABB���н����˲���������ݽ�λ�޷�����ģʽѡ��2'd0�������������12bit���޷���14bit��2'd1�������������11bit���޷���14bit��2'd2�������������10bit���޷���14bit��Ĭ������2'd1�� */
        unsigned int  reserved_0              : 2;  /* bit[2-3]  : ���� */
        unsigned int  cpu_gain1_clip_mode_sel : 2;  /* bit[4-5]  : ABB���н����˲���������ݽ�λ�޷�����ģʽѡ��2'd0�������������12bit���޷���14bit��2'd1�������������11bit���޷���14bit��2'd2�������������10bit���޷���14bit��Ĭ������2'd1�� */
        unsigned int  reserved_1              : 2;  /* bit[6-7]  : ���� */
        unsigned int  cpu_gain2_clip_mode_sel : 2;  /* bit[8-9]  : ABB���н����˲���������ݽ�λ�޷�����ģʽѡ��2'd0�������������12bit���޷���14bit��2'd1�������������11bit���޷���14bit��2'd2�������������10bit���޷���14bit��Ĭ������2'd1�� */
        unsigned int  reserved_2              : 2;  /* bit[10-11]: ���� */
        unsigned int  cpu_gain3_clip_mode_sel : 2;  /* bit[12-13]: ABB���н����˲���������ݽ�λ�޷�����ģʽѡ��2'd0�������������12bit���޷���14bit��2'd1�������������11bit���޷���14bit��2'd2�������������10bit���޷���14bit��Ĭ������2'd1�� */
        unsigned int  reserved_3              : 2;  /* bit[14-15]: ���� */
        unsigned int  cpu_gain4_clip_mode_sel : 2;  /* bit[16-17]: ABB���н����˲���������ݽ�λ�޷�����ģʽѡ��2'd0�������������12bit���޷���14bit��2'd1�������������11bit���޷���14bit��2'd2�������������10bit���޷���14bit��Ĭ������2'd1�� */
        unsigned int  reserved_4              : 2;  /* bit[18-19]: ���� */
        unsigned int  cpu_gain5_clip_mode_sel : 2;  /* bit[20-21]: ABB���н����˲���������ݽ�λ�޷�����ģʽѡ��2'd0�������������12bit���޷���14bit��2'd1�������������11bit���޷���14bit��2'd2�������������10bit���޷���14bit��Ĭ������2'd1�� */
        unsigned int  reserved_5              : 2;  /* bit[22-23]: ���� */
        unsigned int  cpu_gain6_clip_mode_sel : 2;  /* bit[24-25]: ABB���н����˲���������ݽ�λ�޷�����ģʽѡ��2'd0�������������12bit���޷���14bit��2'd1�������������11bit���޷���14bit��2'd2�������������10bit���޷���14bit��Ĭ������2'd1�� */
        unsigned int  reserved_6              : 2;  /* bit[26-27]: ���� */
        unsigned int  cpu_gain7_clip_mode_sel : 2;  /* bit[28-29]: ABB���н����˲���������ݽ�λ�޷�����ģʽѡ��2'd0�������������12bit���޷���14bit��2'd1�������������11bit���޷���14bit��2'd2�������������10bit���޷���14bit��Ĭ������2'd1�� */
        unsigned int  reserved_7              : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_CLIP_MODE_SEL_UNION;
#define GBBP_CLIP_MODE_SEL_cpu_gain0_clip_mode_sel_START  (0)
#define GBBP_CLIP_MODE_SEL_cpu_gain0_clip_mode_sel_END    (1)
#define GBBP_CLIP_MODE_SEL_cpu_gain1_clip_mode_sel_START  (4)
#define GBBP_CLIP_MODE_SEL_cpu_gain1_clip_mode_sel_END    (5)
#define GBBP_CLIP_MODE_SEL_cpu_gain2_clip_mode_sel_START  (8)
#define GBBP_CLIP_MODE_SEL_cpu_gain2_clip_mode_sel_END    (9)
#define GBBP_CLIP_MODE_SEL_cpu_gain3_clip_mode_sel_START  (12)
#define GBBP_CLIP_MODE_SEL_cpu_gain3_clip_mode_sel_END    (13)
#define GBBP_CLIP_MODE_SEL_cpu_gain4_clip_mode_sel_START  (16)
#define GBBP_CLIP_MODE_SEL_cpu_gain4_clip_mode_sel_END    (17)
#define GBBP_CLIP_MODE_SEL_cpu_gain5_clip_mode_sel_START  (20)
#define GBBP_CLIP_MODE_SEL_cpu_gain5_clip_mode_sel_END    (21)
#define GBBP_CLIP_MODE_SEL_cpu_gain6_clip_mode_sel_START  (24)
#define GBBP_CLIP_MODE_SEL_cpu_gain6_clip_mode_sel_END    (25)
#define GBBP_CLIP_MODE_SEL_cpu_gain7_clip_mode_sel_START  (28)
#define GBBP_CLIP_MODE_SEL_cpu_gain7_clip_mode_sel_END    (29)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_MEM_CTRL1_UNION
 �ṹ˵��  : ADDR_MEM_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0xf018����ֵ:0x03500057�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_mem_ctrl1_reg;
    struct
    {
        unsigned int  mem_ctrl_d_1rw2rw_w1 : 16; /* bit[0-15] : 1w2rw˫��RAM��ʱ���� */
        unsigned int  mem_ctrl_d_1w2r_w1   : 16; /* bit[16-31]: 1w2r˫��RAM��ʱ���� */
    } reg;
} GBBP_ADDR_MEM_CTRL1_UNION;
#define GBBP_ADDR_MEM_CTRL1_mem_ctrl_d_1rw2rw_w1_START  (0)
#define GBBP_ADDR_MEM_CTRL1_mem_ctrl_d_1rw2rw_w1_END    (15)
#define GBBP_ADDR_MEM_CTRL1_mem_ctrl_d_1w2r_w1_START    (16)
#define GBBP_ADDR_MEM_CTRL1_mem_ctrl_d_1w2r_w1_END      (31)


/*****************************************************************************
 �ṹ��    : GBBP_ADDR_MEM_CTRL2_UNION
 �ṹ˵��  : ADDR_MEM_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0xf01C����ֵ:0x00701050�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      addr_mem_ctrl2_reg;
    struct
    {
        unsigned int  mem_ctrl_s_w1 : 16; /* bit[0-15] : ����RAM��ʱ���� */
        unsigned int  rom_ctrl      : 8;  /* bit[16-23]: ROM��ʱ���� */
        unsigned int  reserved      : 8;  /* bit[24-31]: ���� */
    } reg;
} GBBP_ADDR_MEM_CTRL2_UNION;
#define GBBP_ADDR_MEM_CTRL2_mem_ctrl_s_w1_START  (0)
#define GBBP_ADDR_MEM_CTRL2_mem_ctrl_s_w1_END    (15)
#define GBBP_ADDR_MEM_CTRL2_rom_ctrl_START       (16)
#define GBBP_ADDR_MEM_CTRL2_rom_ctrl_END         (23)


/***======================================================================***
                     (2/9) register_define_sdr_gdrx_guage
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : GBBP_GDRX_GAUGE_EN_CNF_UNION
 �ṹ˵��  : GDRX_GAUGE_EN_CNF �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x0000000A�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gdrx_gauge_en_cnf_reg;
    struct
    {
        unsigned int  gdrx_gauge_len  : 17; /* bit[0-16] : ʱ��У׼32KHzʱ�Ӹ��� */
        unsigned int  reserved        : 13; /* bit[17-29]: ���� */
        unsigned int  gdrx_gauge_en   : 1;  /* bit[30]   : ʱ��У׼ʹ�ܣ�д1�����������㣬д0�����塣 */
        unsigned int  gdrx_gauge_stop : 1;  /* bit[31]   : GDRXֹͣ���壬д1ֹͣ�������㣬д0�����塣 */
    } reg;
} GBBP_GDRX_GAUGE_EN_CNF_UNION;
#define GBBP_GDRX_GAUGE_EN_CNF_gdrx_gauge_len_START   (0)
#define GBBP_GDRX_GAUGE_EN_CNF_gdrx_gauge_len_END     (16)
#define GBBP_GDRX_GAUGE_EN_CNF_gdrx_gauge_en_START    (30)
#define GBBP_GDRX_GAUGE_EN_CNF_gdrx_gauge_en_END      (30)
#define GBBP_GDRX_GAUGE_EN_CNF_gdrx_gauge_stop_START  (31)
#define GBBP_GDRX_GAUGE_EN_CNF_gdrx_gauge_stop_END    (31)


/*****************************************************************************
 �ṹ��    : GBBP_GAUGE_RESULT_RPT_UNION
 �ṹ˵��  : GAUGE_RESULT_RPT �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gauge_result_rpt_reg;
    struct
    {
        unsigned int  gdrx_gauge_result : 28; /* bit[0-27] : ʱ��У׼���������������104M�Ӹ��� */
        unsigned int  reserved          : 2;  /* bit[28-29]: ���� */
        unsigned int  gdrx_gauge_state  : 1;  /* bit[30]   : ����״̬��ѯ��1�����ڲ����� */
        unsigned int  gdrx_sleep_state  : 1;  /* bit[31]   : ˯��״̬��ѯ��1������˯�ߡ� */
    } reg;
} GBBP_GAUGE_RESULT_RPT_UNION;
#define GBBP_GAUGE_RESULT_RPT_gdrx_gauge_result_START  (0)
#define GBBP_GAUGE_RESULT_RPT_gdrx_gauge_result_END    (27)
#define GBBP_GAUGE_RESULT_RPT_gdrx_gauge_state_START   (30)
#define GBBP_GAUGE_RESULT_RPT_gdrx_gauge_state_END     (30)
#define GBBP_GAUGE_RESULT_RPT_gdrx_sleep_state_START   (31)
#define GBBP_GAUGE_RESULT_RPT_gdrx_sleep_state_END     (31)


/*****************************************************************************
 �ṹ��    : GBBP_IMI_INT_TDMA_QB_UNION
 �ṹ˵��  : IMI_INT_TDMA_QB �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      imi_int_tdma_qb_reg;
    struct
    {
        unsigned int  imi_int_tdma_qb : 13; /* bit[0-12] : IMIʱ�����κ��ж��ϱ�ʱGTC��TDMA QB������������ */
        unsigned int  reserved        : 19; /* bit[13-31]: ���� */
    } reg;
} GBBP_IMI_INT_TDMA_QB_UNION;
#define GBBP_IMI_INT_TDMA_QB_imi_int_tdma_qb_START  (0)
#define GBBP_IMI_INT_TDMA_QB_imi_int_tdma_qb_END    (12)


/*****************************************************************************
 �ṹ��    : GBBP_SLEEP_INT_TDMA_QB_UNION
 �ṹ˵��  : SLEEP_INT_TDMA_QB �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      sleep_int_tdma_qb_reg;
    struct
    {
        unsigned int  sleep_int_tdma_qb : 13; /* bit[0-12] : 32Kʱ���ж��ϱ�ʱGTC��TDMA QB������������ */
        unsigned int  reserved          : 19; /* bit[13-31]: ���� */
    } reg;
} GBBP_SLEEP_INT_TDMA_QB_UNION;
#define GBBP_SLEEP_INT_TDMA_QB_sleep_int_tdma_qb_START  (0)
#define GBBP_SLEEP_INT_TDMA_QB_sleep_int_tdma_qb_END    (12)


/***======================================================================***
                     (3/9) register_define_g_fe_ctrl
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : GBBP_G_AFC_THERM_COM_NV_UNION
 �ṹ˵��  : G_AFC_THERM_COM_NV �Ĵ����ṹ���塣��ַƫ����:0x0600����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      g_afc_therm_com_nv_reg;
    struct
    {
        unsigned int  cpu_g_afc_therm_com_nv : 15; /* bit[0-14] : ��RFCMOSʹ�þ��巽��ʱ�����gdsp���õ�У׼���¶Ȳ���NV��ֵ��
                                                                  ��NV��ֵ�ǿ���ʱ�������¶ȶ�Ӧ�������ߵĲ���ֵ�� */
        unsigned int  reserved               : 17; /* bit[15-31]: ���� */
    } reg;
} GBBP_G_AFC_THERM_COM_NV_UNION;
#define GBBP_G_AFC_THERM_COM_NV_cpu_g_afc_therm_com_nv_START  (0)
#define GBBP_G_AFC_THERM_COM_NV_cpu_g_afc_therm_com_nv_END    (14)


/*****************************************************************************
 �ṹ��    : GBBP_G_RF_SSI_AFC_UNION
 �ṹ˵��  : G_RF_SSI_AFC �Ĵ����ṹ���塣��ַƫ����:0x0604����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      g_rf_ssi_afc_reg;
    struct
    {
        unsigned int  reserved_0          : 1;  /* bit[0-0]  : ���� */
        unsigned int  reserved_1          : 3;  /* bit[1-3]  : ���� */
        unsigned int  cpu_rf_afc_reg_addr : 8;  /* bit[4-11] : ѡ���巽��ʱ�����ø�RF��TCXO SSI��ַbit�� */
        unsigned int  reserved_2          : 4;  /* bit[12-15]: ���� */
        unsigned int  rf_ssi_afc_data_cpu : 14; /* bit[16-29]: ʹ�þ���AFC����ʱ�����RF��AFC������ֵ�� */
        unsigned int  reserved_3          : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_G_RF_SSI_AFC_UNION;
#define GBBP_G_RF_SSI_AFC_cpu_rf_afc_reg_addr_START  (4)
#define GBBP_G_RF_SSI_AFC_cpu_rf_afc_reg_addr_END    (11)
#define GBBP_G_RF_SSI_AFC_rf_ssi_afc_data_cpu_START  (16)
#define GBBP_G_RF_SSI_AFC_rf_ssi_afc_data_cpu_END    (29)


/*****************************************************************************
 �ṹ��    : GBBP_G_RF_SSI_WRONE_CFG_UNION
 �ṹ˵��  : G_RF_SSI_WRONE_CFG �Ĵ����ṹ���塣��ַƫ����:0x0608����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      g_rf_ssi_wrone_cfg_reg;
    struct
    {
        unsigned int  cpu_rf_ssi_wrone_data    : 16; /* bit[0-15] : GDSPʹ��CPU��ʽ����һ��RF-SSI�ļĴ�����Ӧ�����ݡ� */
        unsigned int  cpu_rf_ssi_wrone_addr    : 8;  /* bit[16-23]: GDSPʹ��CPU��ʽ����һ��RF-SSI�ļĴ�����ַ�� */
        unsigned int  cpu_rf_ssi_wrone_ind_imi : 1;  /* bit[24-24]: GDSPʹ��CPU��ʽ����һ��RF-SSI�������źš�
                                                                    �߼������㡣 */
        unsigned int  reserved_0               : 3;  /* bit[25-27]: ���� */
        unsigned int  rf_ssi_wrone_end_cpu     : 1;  /* bit[28-28]: ʹ��CPU��ʽ��һ��RF-SSI�����Ƿ�����BBP COMMģ���״̬�źţ������á�
                                                                    0����ʾ������1��ʾδ������ */
        unsigned int  reserved_1               : 3;  /* bit[29-31]: ���� */
    } reg;
} GBBP_G_RF_SSI_WRONE_CFG_UNION;
#define GBBP_G_RF_SSI_WRONE_CFG_cpu_rf_ssi_wrone_data_START     (0)
#define GBBP_G_RF_SSI_WRONE_CFG_cpu_rf_ssi_wrone_data_END       (15)
#define GBBP_G_RF_SSI_WRONE_CFG_cpu_rf_ssi_wrone_addr_START     (16)
#define GBBP_G_RF_SSI_WRONE_CFG_cpu_rf_ssi_wrone_addr_END       (23)
#define GBBP_G_RF_SSI_WRONE_CFG_cpu_rf_ssi_wrone_ind_imi_START  (24)
#define GBBP_G_RF_SSI_WRONE_CFG_cpu_rf_ssi_wrone_ind_imi_END    (24)
#define GBBP_G_RF_SSI_WRONE_CFG_rf_ssi_wrone_end_cpu_START      (28)
#define GBBP_G_RF_SSI_WRONE_CFG_rf_ssi_wrone_end_cpu_END        (28)


/*****************************************************************************
 �ṹ��    : GBBP_G_RF_SSI_REQ_EN_CFG_UNION
 �ṹ˵��  : G_RF_SSI_REQ_EN_CFG �Ĵ����ṹ���塣��ַƫ����:0x060C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      g_rf_ssi_req_en_cfg_reg;
    struct
    {
        unsigned int  cpu_rf_ssi_gagc_en  : 1;  /* bit[0-0]  : g-gagc ssi����ʹ���ź� */
        unsigned int  reserved_0          : 3;  /* bit[1-3]  : ���� */
        unsigned int  cpu_rf_ssi_wrram_en : 1;  /* bit[4-4]  : g-rf-ram ssi����ʹ���ź� */
        unsigned int  reserved_1          : 3;  /* bit[5-7]  : ���� */
        unsigned int  cpu_rf_ssi_afc_en   : 1;  /* bit[8-8]  : g-afc ssi����ʹ���ź� */
        unsigned int  reserved_2          : 3;  /* bit[9-11] : ���� */
        unsigned int  cpu_rf_ssi_wrone_en : 1;  /* bit[12-12]: дһ��rf-ssi����ʹ���ź� */
        unsigned int  reserved_3          : 3;  /* bit[13-15]: ���� */
        unsigned int  cpu_rf_ssi_rd_en    : 1;  /* bit[16-16]: �� ssi����ʹ���ź� */
        unsigned int  reserved_4          : 15; /* bit[17-31]: ���� */
    } reg;
} GBBP_G_RF_SSI_REQ_EN_CFG_UNION;
#define GBBP_G_RF_SSI_REQ_EN_CFG_cpu_rf_ssi_gagc_en_START   (0)
#define GBBP_G_RF_SSI_REQ_EN_CFG_cpu_rf_ssi_gagc_en_END     (0)
#define GBBP_G_RF_SSI_REQ_EN_CFG_cpu_rf_ssi_wrram_en_START  (4)
#define GBBP_G_RF_SSI_REQ_EN_CFG_cpu_rf_ssi_wrram_en_END    (4)
#define GBBP_G_RF_SSI_REQ_EN_CFG_cpu_rf_ssi_afc_en_START    (8)
#define GBBP_G_RF_SSI_REQ_EN_CFG_cpu_rf_ssi_afc_en_END      (8)
#define GBBP_G_RF_SSI_REQ_EN_CFG_cpu_rf_ssi_wrone_en_START  (12)
#define GBBP_G_RF_SSI_REQ_EN_CFG_cpu_rf_ssi_wrone_en_END    (12)
#define GBBP_G_RF_SSI_REQ_EN_CFG_cpu_rf_ssi_rd_en_START     (16)
#define GBBP_G_RF_SSI_REQ_EN_CFG_cpu_rf_ssi_rd_en_END       (16)


/*****************************************************************************
 �ṹ��    : GBBP_G_RF_SSI_RD_CFG_UNION
 �ṹ˵��  : G_RF_SSI_RD_CFG �Ĵ����ṹ���塣��ַƫ����:0x0610����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      g_rf_ssi_rd_cfg_reg;
    struct
    {
        unsigned int  cpu_rf_ssi_rd_ind_imi : 1;  /* bit[0-0]  : ����RF-SSI�Ĵ����ض���
                                                                 �߼��������źš� */
        unsigned int  reserved_0            : 3;  /* bit[1-3]  : ���� */
        unsigned int  cpu_rf_ssi_rd_num     : 3;  /* bit[4-6]  : RF-SSI�ض��Ĵ���������
                                                                 ����ֵΪ0~7����Ӧ�Ļض��Ĵ�������Ϊ1~8��
                                                                 ��ע������Ϊ0��ʾ�ض�һ���Ĵ����� */
        unsigned int  reserved_1            : 1;  /* bit[7-7]  : ���� */
        unsigned int  rf_ssi_rd_end_cpu     : 1;  /* bit[8-8]  : �ض����ָʾ�źš�
                                                                 1����ʾ���ڻض���
                                                                 0����ʾ��ɻض������� */
        unsigned int  reserved_2            : 3;  /* bit[9-11] : ���� */
        unsigned int  rf_ssi_wrram_end_cpu  : 1;  /* bit[12-12]: дssi-ram���ָʾ�źš�
                                                                 1����ʾ���ڻض���
                                                                 0����ʾ��ɻض������� */
        unsigned int  reserved_3            : 19; /* bit[13-31]: ���� */
    } reg;
} GBBP_G_RF_SSI_RD_CFG_UNION;
#define GBBP_G_RF_SSI_RD_CFG_cpu_rf_ssi_rd_ind_imi_START  (0)
#define GBBP_G_RF_SSI_RD_CFG_cpu_rf_ssi_rd_ind_imi_END    (0)
#define GBBP_G_RF_SSI_RD_CFG_cpu_rf_ssi_rd_num_START      (4)
#define GBBP_G_RF_SSI_RD_CFG_cpu_rf_ssi_rd_num_END        (6)
#define GBBP_G_RF_SSI_RD_CFG_rf_ssi_rd_end_cpu_START      (8)
#define GBBP_G_RF_SSI_RD_CFG_rf_ssi_rd_end_cpu_END        (8)
#define GBBP_G_RF_SSI_RD_CFG_rf_ssi_wrram_end_cpu_START   (12)
#define GBBP_G_RF_SSI_RD_CFG_rf_ssi_wrram_end_cpu_END     (12)


/*****************************************************************************
 �ṹ��    : GBBP_G_RF_SSI_RD_0DATA_UNION
 �ṹ˵��  : G_RF_SSI_RD_0DATA �Ĵ����ṹ���塣��ַƫ����:0x0614����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      g_rf_ssi_rd_0data_reg;
    struct
    {
        unsigned int  cpu_rfic_ssi_rd_0data : 24; /* bit[0-23] : SSI�ض���������0�� */
        unsigned int  reserved              : 8;  /* bit[24-31]: ���� */
    } reg;
} GBBP_G_RF_SSI_RD_0DATA_UNION;
#define GBBP_G_RF_SSI_RD_0DATA_cpu_rfic_ssi_rd_0data_START  (0)
#define GBBP_G_RF_SSI_RD_0DATA_cpu_rfic_ssi_rd_0data_END    (23)


/*****************************************************************************
 �ṹ��    : GBBP_G_RF_SSI_RD_1DATA_UNION
 �ṹ˵��  : G_RF_SSI_RD_1DATA �Ĵ����ṹ���塣��ַƫ����:0x0618����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      g_rf_ssi_rd_1data_reg;
    struct
    {
        unsigned int  cpu_rfic_ssi_rd_1data : 24; /* bit[0-23] : SSI�ض���������1�� */
        unsigned int  reserved              : 8;  /* bit[24-31]: ���� */
    } reg;
} GBBP_G_RF_SSI_RD_1DATA_UNION;
#define GBBP_G_RF_SSI_RD_1DATA_cpu_rfic_ssi_rd_1data_START  (0)
#define GBBP_G_RF_SSI_RD_1DATA_cpu_rfic_ssi_rd_1data_END    (23)


/*****************************************************************************
 �ṹ��    : GBBP_G_RF_SSI_RD_2DATA_UNION
 �ṹ˵��  : G_RF_SSI_RD_2DATA �Ĵ����ṹ���塣��ַƫ����:0x061C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      g_rf_ssi_rd_2data_reg;
    struct
    {
        unsigned int  cpu_rfic_ssi_rd_2data : 24; /* bit[0-23] : SSI�ض���������2�� */
        unsigned int  reserved              : 8;  /* bit[24-31]: ���� */
    } reg;
} GBBP_G_RF_SSI_RD_2DATA_UNION;
#define GBBP_G_RF_SSI_RD_2DATA_cpu_rfic_ssi_rd_2data_START  (0)
#define GBBP_G_RF_SSI_RD_2DATA_cpu_rfic_ssi_rd_2data_END    (23)


/*****************************************************************************
 �ṹ��    : GBBP_G_RF_SSI_RD_3DATA_UNION
 �ṹ˵��  : G_RF_SSI_RD_3DATA �Ĵ����ṹ���塣��ַƫ����:0x0620����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      g_rf_ssi_rd_3data_reg;
    struct
    {
        unsigned int  cpu_rfic_ssi_rd_3data : 24; /* bit[0-23] : SSI�ض���������3�� */
        unsigned int  reserved              : 8;  /* bit[24-31]: ���� */
    } reg;
} GBBP_G_RF_SSI_RD_3DATA_UNION;
#define GBBP_G_RF_SSI_RD_3DATA_cpu_rfic_ssi_rd_3data_START  (0)
#define GBBP_G_RF_SSI_RD_3DATA_cpu_rfic_ssi_rd_3data_END    (23)


/*****************************************************************************
 �ṹ��    : GBBP_G_RF_SSI_RD_4DATA_UNION
 �ṹ˵��  : G_RF_SSI_RD_4DATA �Ĵ����ṹ���塣��ַƫ����:0x0624����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      g_rf_ssi_rd_4data_reg;
    struct
    {
        unsigned int  cpu_rfic_ssi_rd_4data : 24; /* bit[0-23] : SSI�ض���������4�� */
        unsigned int  reserved              : 8;  /* bit[24-31]: ���� */
    } reg;
} GBBP_G_RF_SSI_RD_4DATA_UNION;
#define GBBP_G_RF_SSI_RD_4DATA_cpu_rfic_ssi_rd_4data_START  (0)
#define GBBP_G_RF_SSI_RD_4DATA_cpu_rfic_ssi_rd_4data_END    (23)


/*****************************************************************************
 �ṹ��    : GBBP_G_RF_SSI_RD_5DATA_UNION
 �ṹ˵��  : G_RF_SSI_RD_5DATA �Ĵ����ṹ���塣��ַƫ����:0x0628����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      g_rf_ssi_rd_5data_reg;
    struct
    {
        unsigned int  cpu_rfic_ssi_rd_5data : 24; /* bit[0-23] : SSI�ض���������5�� */
        unsigned int  reserved              : 8;  /* bit[24-31]: ���� */
    } reg;
} GBBP_G_RF_SSI_RD_5DATA_UNION;
#define GBBP_G_RF_SSI_RD_5DATA_cpu_rfic_ssi_rd_5data_START  (0)
#define GBBP_G_RF_SSI_RD_5DATA_cpu_rfic_ssi_rd_5data_END    (23)


/*****************************************************************************
 �ṹ��    : GBBP_G_RF_SSI_RD_6DATA_UNION
 �ṹ˵��  : G_RF_SSI_RD_6DATA �Ĵ����ṹ���塣��ַƫ����:0x062C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      g_rf_ssi_rd_6data_reg;
    struct
    {
        unsigned int  cpu_rfic_ssi_rd_6data : 24; /* bit[0-23] : SSI�ض���������6�� */
        unsigned int  reserved              : 8;  /* bit[24-31]: ���� */
    } reg;
} GBBP_G_RF_SSI_RD_6DATA_UNION;
#define GBBP_G_RF_SSI_RD_6DATA_cpu_rfic_ssi_rd_6data_START  (0)
#define GBBP_G_RF_SSI_RD_6DATA_cpu_rfic_ssi_rd_6data_END    (23)


/*****************************************************************************
 �ṹ��    : GBBP_G_RF_SSI_RD_7DATA_UNION
 �ṹ˵��  : G_RF_SSI_RD_7DATA �Ĵ����ṹ���塣��ַƫ����:0x0630����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      g_rf_ssi_rd_7data_reg;
    struct
    {
        unsigned int  cpu_rfic_ssi_rd_7data : 24; /* bit[0-23] : SSI�ض���������7�� */
        unsigned int  reserved              : 8;  /* bit[24-31]: ���� */
    } reg;
} GBBP_G_RF_SSI_RD_7DATA_UNION;
#define GBBP_G_RF_SSI_RD_7DATA_cpu_rfic_ssi_rd_7data_START  (0)
#define GBBP_G_RF_SSI_RD_7DATA_cpu_rfic_ssi_rd_7data_END    (23)


/*****************************************************************************
 �ṹ��    : GBBP_G_MIPI_REQ_EN_CFG_UNION
 �ṹ˵��  : G_MIPI_REQ_EN_CFG �Ĵ����ṹ���塣��ַƫ����:0x0634����ֵ:0x00000011�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      g_mipi_req_en_cfg_reg;
    struct
    {
        unsigned int  cpu_mipi_cmd_cfg_en       : 1;  /* bit[0]   : CPU��ʽMIPI�ͻ��˹���ʹ�ܿ��أ�1��ʾͨ���򿪣�0��ʾͨ���رա� */
        unsigned int  reserved_0                : 3;  /* bit[1-3] : ���� */
        unsigned int  cpu_gtc_mipi_start_cfg_en : 1;  /* bit[4]   : GTC��ʽMIPI�ͻ��˹���ʹ�ܿ��أ�1��ʾͨ���򿪣�0��ʾͨ���رա� */
        unsigned int  reserved_1                : 27; /* bit[5-31]: ���� */
    } reg;
} GBBP_G_MIPI_REQ_EN_CFG_UNION;
#define GBBP_G_MIPI_REQ_EN_CFG_cpu_mipi_cmd_cfg_en_START        (0)
#define GBBP_G_MIPI_REQ_EN_CFG_cpu_mipi_cmd_cfg_en_END          (0)
#define GBBP_G_MIPI_REQ_EN_CFG_cpu_gtc_mipi_start_cfg_en_START  (4)
#define GBBP_G_MIPI_REQ_EN_CFG_cpu_gtc_mipi_start_cfg_en_END    (4)


/*****************************************************************************
 �ṹ��    : GBBP_G_MIPI_CMD_CFG_UNION
 �ṹ˵��  : G_MIPI_CMD_CFG �Ĵ����ṹ���塣��ַƫ����:0x0638����ֵ:0x00000100�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      g_mipi_cmd_cfg_reg;
    struct
    {
        unsigned int  cpu_mipi_cmd_ini_addr : 7;  /* bit[0-6]  : �����ʽ����MIPI����ʱ�����üĴ�������׵�ַ�� */
        unsigned int  reserved_0            : 1;  /* bit[7]    : ���� */
        unsigned int  cpu_mipi_cmd_num      : 7;  /* bit[8-14] : �����ʽ����MIPI����ʱ�����üĴ����ĸ��������÷�Χ��1��127�� */
        unsigned int  reserved_1            : 1;  /* bit[15]   : ���� */
        unsigned int  cpu_mipi_cmd_ind_imi  : 1;  /* bit[16-16]: �����ʽ����MIPI����ʱ�Ĵ��������źš� */
        unsigned int  reserved_2            : 15; /* bit[17-31]: ���� */
    } reg;
} GBBP_G_MIPI_CMD_CFG_UNION;
#define GBBP_G_MIPI_CMD_CFG_cpu_mipi_cmd_ini_addr_START  (0)
#define GBBP_G_MIPI_CMD_CFG_cpu_mipi_cmd_ini_addr_END    (6)
#define GBBP_G_MIPI_CMD_CFG_cpu_mipi_cmd_num_START       (8)
#define GBBP_G_MIPI_CMD_CFG_cpu_mipi_cmd_num_END         (14)
#define GBBP_G_MIPI_CMD_CFG_cpu_mipi_cmd_ind_imi_START   (16)
#define GBBP_G_MIPI_CMD_CFG_cpu_mipi_cmd_ind_imi_END     (16)


/*****************************************************************************
 �ṹ��    : GBBP_G_RF_SSI_MIPI_CLR_REG_UNION
 �ṹ˵��  : G_RF_SSI_MIPI_CLR_REG �Ĵ����ṹ���塣��ַƫ����:0x063C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      g_rf_ssi_mipi_clr_reg_reg;
    struct
    {
        unsigned int  cpu_mipi_clr_ind_imi   : 1;  /* bit[0]    : �������MIPI״̬���쳣����ĸ�λ�����źš� */
        unsigned int  reserved_0             : 15; /* bit[1-15] : ���� */
        unsigned int  cpu_rf_ssi_clr_ind_imi : 1;  /* bit[16]   : �������SSI״̬���쳣����ĸ�λ�����źš� */
        unsigned int  reserved_1             : 15; /* bit[17-31]: ���� */
    } reg;
} GBBP_G_RF_SSI_MIPI_CLR_REG_UNION;
#define GBBP_G_RF_SSI_MIPI_CLR_REG_cpu_mipi_clr_ind_imi_START    (0)
#define GBBP_G_RF_SSI_MIPI_CLR_REG_cpu_mipi_clr_ind_imi_END      (0)
#define GBBP_G_RF_SSI_MIPI_CLR_REG_cpu_rf_ssi_clr_ind_imi_START  (16)
#define GBBP_G_RF_SSI_MIPI_CLR_REG_cpu_rf_ssi_clr_ind_imi_END    (16)


/*****************************************************************************
 �ṹ��    : GBBP_G_ABB_CFG_SEL_UNION
 �ṹ˵��  : G_ABB_CFG_SEL �Ĵ����ṹ���塣��ַƫ����:0x0644����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      g_abb_cfg_sel_reg;
    struct
    {
        unsigned int  cpu_abb_code_sel_g : 1;  /* bit[0]   : ABB������������Ȼ�롢����ģʽѡ��
                                                             1����ʾ��Ȼ�룬0����ʾ���룬GSMר�á� */
        unsigned int  reserved           : 31; /* bit[1-31]: ���� */
    } reg;
} GBBP_G_ABB_CFG_SEL_UNION;
#define GBBP_G_ABB_CFG_SEL_cpu_abb_code_sel_g_START  (0)
#define GBBP_G_ABB_CFG_SEL_cpu_abb_code_sel_g_END    (0)


/*****************************************************************************
 �ṹ��    : GBBP_G_MASTER_MEA_G_EN_UNION
 �ṹ˵��  : G_MASTER_MEA_G_EN �Ĵ����ṹ���塣��ַƫ����:0x0658����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      g_master_mea_g_en_reg;
    struct
    {
        unsigned int  cpu_master_mea_g_en : 1;  /* bit[0-0] : ��ģ��G�ķ�ʽѡ��
                                                              0�������ѣ�
                                                              1���Ǳ����ѡ� */
        unsigned int  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} GBBP_G_MASTER_MEA_G_EN_UNION;
#define GBBP_G_MASTER_MEA_G_EN_cpu_master_mea_g_en_START  (0)
#define GBBP_G_MASTER_MEA_G_EN_cpu_master_mea_g_en_END    (0)


/*****************************************************************************
 �ṹ��    : GBBP_G_ABB_TRX_LOOP_EN_UNION
 �ṹ˵��  : G_ABB_TRX_LOOP_EN �Ĵ����ṹ���塣��ַƫ����:0x065C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      g_abb_trx_loop_en_reg;
    struct
    {
        unsigned int  cpu_gabb_trx_loop_tx_en : 1;  /* bit[0-0] : ����ģʽ�£�����ͨ��ʹ�ܿ��ء� */
        unsigned int  cpu_gabb_trx_loop_en    : 1;  /* bit[1-1] : ����ģʽʹ�ܡ� */
        unsigned int  reserved                : 30; /* bit[2-31]: ���� */
    } reg;
} GBBP_G_ABB_TRX_LOOP_EN_UNION;
#define GBBP_G_ABB_TRX_LOOP_EN_cpu_gabb_trx_loop_tx_en_START  (0)
#define GBBP_G_ABB_TRX_LOOP_EN_cpu_gabb_trx_loop_tx_en_END    (0)
#define GBBP_G_ABB_TRX_LOOP_EN_cpu_gabb_trx_loop_en_START     (1)
#define GBBP_G_ABB_TRX_LOOP_EN_cpu_gabb_trx_loop_en_END       (1)


/*****************************************************************************
 �ṹ��    : GBBP_G_AUXDAC_EN_CFG_UNION
 �ṹ˵��  : G_AUXDAC_EN_CFG �Ĵ����ṹ���塣��ַƫ����:0x0690����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      g_auxdac_en_cfg_reg;
    struct
    {
        unsigned int  cpu_g_auxdac_close_cfg : 11; /* bit[0-10] : AuxDAC�򿪿��������ã��ÿ�������gtc_gapc_en�߿��½��ط�����AuxDAC�� */
        unsigned int  reserved_0             : 5;  /* bit[11-15]: ���� */
        unsigned int  cpu_g_auxdac_open_cfg  : 11; /* bit[16-26]: AuxDAC�򿪿��������ã��ÿ�������gtc_gapc_en�߿��ź������ط�����AuxDAC�� */
        unsigned int  reserved_1             : 5;  /* bit[27-31]: ���� */
    } reg;
} GBBP_G_AUXDAC_EN_CFG_UNION;
#define GBBP_G_AUXDAC_EN_CFG_cpu_g_auxdac_close_cfg_START  (0)
#define GBBP_G_AUXDAC_EN_CFG_cpu_g_auxdac_close_cfg_END    (10)
#define GBBP_G_AUXDAC_EN_CFG_cpu_g_auxdac_open_cfg_START   (16)
#define GBBP_G_AUXDAC_EN_CFG_cpu_g_auxdac_open_cfg_END     (26)


/*****************************************************************************
 �ṹ��    : GBBP_DATA_FIFO_RST_UNION
 �ṹ˵��  : DATA_FIFO_RST �Ĵ����ṹ���塣��ַƫ����:0x0694����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      data_fifo_rst_reg;
    struct
    {
        unsigned int  data_fifo_rst       : 1;  /* bit[0-0] : fifo��λ�źţ���FIFO״̬�쳣ʱ������Ϊ1���������� */
        unsigned int  data_fifo_full_rpt  : 1;  /* bit[1-1] : FIFO���ź��ϱ� */
        unsigned int  data_fifo_empty_rpt : 1;  /* bit[2-2] : FIFO���ź��ϱ� */
        unsigned int  reserved            : 29; /* bit[3-31]: ���� */
    } reg;
} GBBP_DATA_FIFO_RST_UNION;
#define GBBP_DATA_FIFO_RST_data_fifo_rst_START        (0)
#define GBBP_DATA_FIFO_RST_data_fifo_rst_END          (0)
#define GBBP_DATA_FIFO_RST_data_fifo_full_rpt_START   (1)
#define GBBP_DATA_FIFO_RST_data_fifo_full_rpt_END     (1)
#define GBBP_DATA_FIFO_RST_data_fifo_empty_rpt_START  (2)
#define GBBP_DATA_FIFO_RST_data_fifo_empty_rpt_END    (2)


/***======================================================================***
                     (4/9) register_define_g_fe_ctrl_mem
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : GBBP_G_RFIC_SSI_RAM_UNION
 �ṹ˵��  : G_RFIC_SSI_RAM �Ĵ����ṹ���塣��ַƫ����:0x200����ֵ:0x00000000�����:32
 �Ĵ���˵��: g��Ƶ����ƵH��rfic-ssi RAM
*****************************************************************************/
typedef union
{
    unsigned int      g_rfic_ssi_ram_reg;
    struct
    {
        unsigned int  g_rfic_ssi_ram_data : 16; /* bit[0-15] : g��Ƶ��ǿ���rfic-ssi RAM��
                                                               ����
                                                               [15:0]��rfic�ļĴ������ݡ� */
        unsigned int  g_rfic_ssi_ram_addr : 8;  /* bit[16-23]: g��Ƶ��ǿ���rfic-ssi RAM��
                                                               ���ݣ�
                                                               [23:16]��rfic�ļĴ�����ַ�� */
        unsigned int  reserved            : 8;  /* bit[24-31]: ���� */
    } reg;
} GBBP_G_RFIC_SSI_RAM_UNION;
#define GBBP_G_RFIC_SSI_RAM_g_rfic_ssi_ram_data_START  (0)
#define GBBP_G_RFIC_SSI_RAM_g_rfic_ssi_ram_data_END    (15)
#define GBBP_G_RFIC_SSI_RAM_g_rfic_ssi_ram_addr_START  (16)
#define GBBP_G_RFIC_SSI_RAM_g_rfic_ssi_ram_addr_END    (23)


/***======================================================================***
                     (5/9) register_define_gtc_mem
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : GBBP_GTC_CFG_RAM_UNION
 �ṹ˵��  : GTC_CFG_RAM �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��Ч��ַ��Χ0x0000��0x07FF
*****************************************************************************/
typedef union
{
    unsigned int      gtc_cfg_ram_reg;
    struct
    {
        unsigned int  gtc_cfg_data : 16; /* bit[0-15] : GTCָ������RAM��ÿ��32bit��ֻ�е�16bit��Ч�� */
        unsigned int  reserved     : 16; /* bit[16-31]: ���� */
    } reg;
} GBBP_GTC_CFG_RAM_UNION;
#define GBBP_GTC_CFG_RAM_gtc_cfg_data_START  (0)
#define GBBP_GTC_CFG_RAM_gtc_cfg_data_END    (15)


/***======================================================================***
                     (6/9) register_define_g_addr_2x_mem
 ***======================================================================***/
/***======================================================================***
                     (7/9) register_define_g_addr_3x_mem
 ***======================================================================***/
/***======================================================================***
                     (8/9) register_define_g_addr_5x_mem
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : GBBP_UL_MAP_CFG_RAM_UNION
 �ṹ˵��  : UL_MAP_CFG_RAM �Ĵ����ṹ���塣��ַƫ����:0x0600����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��Ч��ַ��Χ0x0600��0x0638
*****************************************************************************/
typedef union
{
    unsigned int      ul_map_cfg_ram_reg;
    struct
    {
        unsigned int  ul_map_cfg_data : 30; /* bit[0-29] : CPU�·��Ĵ��������ݣ���30bit��Ч */
        unsigned int  reserved        : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_UL_MAP_CFG_RAM_UNION;
#define GBBP_UL_MAP_CFG_RAM_ul_map_cfg_data_START  (0)
#define GBBP_UL_MAP_CFG_RAM_ul_map_cfg_data_END    (29)


/***======================================================================***
                     (9/9) register_define_g_addr_6x_mem
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : GBBP_DC_OFFSET_RAM_UNION
 �ṹ˵��  : DC_OFFSET_RAM �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: ֱ��ƫִ����ֵ�ֵ�ֵ�洢RAM����0x00FF����
*****************************************************************************/
typedef union
{
    unsigned int      dc_offset_ram_reg;
    struct
    {
        unsigned int  dc_offset_rfic_i : 14; /* bit[0-13] : ֱ��ƫִ����ֵ�ֵ�ֵ�洢RAM���ʵ�ַ��һ����ַ��ʾ28bit�����е�16bit�е�14bit��ʾI·����16bit�е�14bitΪQ·�����õ�14bitΪ�з������� */
        unsigned int  reserved_0       : 2;  /* bit[14-15]: ���� */
        unsigned int  dc_offset_rfic_q : 14; /* bit[16-29]: ֱ��ƫִ����ֵ�ֵ�ֵ�洢RAM���ʵ�ַ��һ����ַ��ʾ28bit�����е�16bit�е�14bit��ʾI·����16bit�е�14bitΪQ·�����õ�14bitΪ�з������� */
        unsigned int  reserved_1       : 2;  /* bit[30-31]: ���� */
    } reg;
} GBBP_DC_OFFSET_RAM_UNION;
#define GBBP_DC_OFFSET_RAM_dc_offset_rfic_i_START  (0)
#define GBBP_DC_OFFSET_RAM_dc_offset_rfic_i_END    (13)
#define GBBP_DC_OFFSET_RAM_dc_offset_rfic_q_START  (16)
#define GBBP_DC_OFFSET_RAM_dc_offset_rfic_q_END    (29)


/*****************************************************************************
 �ṹ��    : GBBP_CHANNEL_GAIN_RAM_UNION
 �ṹ˵��  : CHANNEL_GAIN_RAM �Ĵ����ṹ���塣��ַƫ����:0x0400����ֵ:0x00000000�����:32
 �Ĵ���˵��: ǰ��ͨ���������ֵ�洢RAM����0x04FF����
*****************************************************************************/
typedef union
{
    unsigned int      channel_gain_ram_reg;
    struct
    {
        unsigned int  channel_gain_rfic : 11; /* bit[0-10] : ǰ��ͨ���������ֵ�洢RAM��CHANNEL_GAIN�ο����òμ���19���˱���ʵ��ʹ��ʱ����Ҫ����ʵ���ó��� */
        unsigned int  reserved          : 21; /* bit[11-31]: ���� */
    } reg;
} GBBP_CHANNEL_GAIN_RAM_UNION;
#define GBBP_CHANNEL_GAIN_RAM_channel_gain_rfic_START  (0)
#define GBBP_CHANNEL_GAIN_RAM_channel_gain_rfic_END    (10)




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

#endif /* end of bbp_gsm_interface.h */
