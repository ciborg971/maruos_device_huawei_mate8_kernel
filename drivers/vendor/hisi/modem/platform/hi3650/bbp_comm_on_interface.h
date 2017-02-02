

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __BBP_COMM_ON_INTERFACE_H__
#define __BBP_COMM_ON_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/***======================================================================***
                     (1/2) register_define_afc_mix
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      0����ʾ����AFCѡ��PDM�����
             1����ʾ����ѡ��PWM���
   UNION�ṹ:  BBPCOMM_AFC_PWM_SEL_MIX_UNION */
#define BBPCOMM_AFC_PWM_SEL_MIX_ADDR                  (SOC_BBP_COMM_ON_BASE_ADDR + 0x1000)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      1����ʾ����AFCʹ�ܣ�
             0����ʾ����AFC��ʹ��
   UNION�ṹ:  BBPCOMM_AFC_EN_MIX_UNION */
#define BBPCOMM_AFC_EN_MIX_ADDR                       (SOC_BBP_COMM_ON_BASE_ADDR + 0x1004)

/* �Ĵ���˵����
 bit[31:12]  ����
 bit[11:0]   AFC����ֵ
   UNION�ṹ:  BBPCOMM_AFC_CFG_WIDTH_MIX_UNION */
#define BBPCOMM_AFC_CFG_WIDTH_MIX_ADDR                (SOC_BBP_COMM_ON_BASE_ADDR + 0x1008)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      1����ʾѡ������AFCֵ
             0����ʾѡ��BBP������AFCֵ
   UNION�ṹ:  BBPCOMM_AFC_CFG_SEL_MIX_UNION */
#define BBPCOMM_AFC_CFG_SEL_MIX_ADDR                  (SOC_BBP_COMM_ON_BASE_ADDR + 0x100C)



/***======================================================================***
                     (2/2) register_define_afc_mix_ch1
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      0����ʾ����AFCѡ��PDM�����
             1����ʾ����ѡ��PWM���
   UNION�ṹ:  BBPCOMM_AFC_PWM_SEL_MIX_CH1_UNION */
#define BBPCOMM_AFC_PWM_SEL_MIX_CH1_ADDR              (SOC_BBP_COMM_ON_BASE_ADDR + 0x1200)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      1����ʾ����AFCʹ�ܣ�
             0����ʾ����AFC��ʹ��
   UNION�ṹ:  BBPCOMM_AFC_EN_MIX_CH1_UNION */
#define BBPCOMM_AFC_EN_MIX_CH1_ADDR                   (SOC_BBP_COMM_ON_BASE_ADDR + 0x1204)

/* �Ĵ���˵����
 bit[31:12]  ����
 bit[11:0]   AFC����ֵ
   UNION�ṹ:  BBPCOMM_AFC_CFG_WIDTH_MIX_CH1_UNION */
#define BBPCOMM_AFC_CFG_WIDTH_MIX_CH1_ADDR            (SOC_BBP_COMM_ON_BASE_ADDR + 0x1208)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      1����ʾѡ������AFCֵ
             0����ʾѡ��BBP������AFCֵ
   UNION�ṹ:  BBPCOMM_AFC_CFG_SEL_MIX_CH1_UNION */
#define BBPCOMM_AFC_CFG_SEL_MIX_CH1_ADDR              (SOC_BBP_COMM_ON_BASE_ADDR + 0x120C)





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
                     (1/2) register_define_afc_mix
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : BBPCOMM_AFC_PWM_SEL_MIX_UNION
 �ṹ˵��  : AFC_PWM_SEL_MIX �Ĵ����ṹ���塣��ַƫ����:0x00����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      afc_pwm_sel_mix_reg;
    struct
    {
        unsigned long  afc_pwm_sel : 1;  /* bit[0]   : 0����ʾ����AFCѡ��PDM�����
                                                       1����ʾ����ѡ��PWM��� */
        unsigned long  reserved    : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_AFC_PWM_SEL_MIX_UNION;
#define BBPCOMM_AFC_PWM_SEL_MIX_afc_pwm_sel_START  (0)
#define BBPCOMM_AFC_PWM_SEL_MIX_afc_pwm_sel_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_AFC_EN_MIX_UNION
 �ṹ˵��  : AFC_EN_MIX �Ĵ����ṹ���塣��ַƫ����:0x04����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      afc_en_mix_reg;
    struct
    {
        unsigned long  afc_en   : 1;  /* bit[0]   : 1����ʾ����AFCʹ�ܣ�
                                                    0����ʾ����AFC��ʹ�� */
        unsigned long  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_AFC_EN_MIX_UNION;
#define BBPCOMM_AFC_EN_MIX_afc_en_START    (0)
#define BBPCOMM_AFC_EN_MIX_afc_en_END      (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_AFC_CFG_WIDTH_MIX_UNION
 �ṹ˵��  : AFC_CFG_WIDTH_MIX �Ĵ����ṹ���塣��ַƫ����:0x08����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      afc_cfg_width_mix_reg;
    struct
    {
        unsigned long  afc_cfg_width : 12; /* bit[0-11] : AFC����ֵ */
        unsigned long  reserved      : 20; /* bit[12-31]: ���� */
    } reg;
} BBPCOMM_AFC_CFG_WIDTH_MIX_UNION;
#define BBPCOMM_AFC_CFG_WIDTH_MIX_afc_cfg_width_START  (0)
#define BBPCOMM_AFC_CFG_WIDTH_MIX_afc_cfg_width_END    (11)


/*****************************************************************************
 �ṹ��    : BBPCOMM_AFC_CFG_SEL_MIX_UNION
 �ṹ˵��  : AFC_CFG_SEL_MIX �Ĵ����ṹ���塣��ַƫ����:0x0C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      afc_cfg_sel_mix_reg;
    struct
    {
        unsigned long  afc_cfg_sel : 1;  /* bit[0]   : 1����ʾѡ������AFCֵ
                                                       0����ʾѡ��BBP������AFCֵ */
        unsigned long  reserved    : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_AFC_CFG_SEL_MIX_UNION;
#define BBPCOMM_AFC_CFG_SEL_MIX_afc_cfg_sel_START  (0)
#define BBPCOMM_AFC_CFG_SEL_MIX_afc_cfg_sel_END    (0)


/***======================================================================***
                     (2/2) register_define_afc_mix_ch1
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : BBPCOMM_AFC_PWM_SEL_MIX_CH1_UNION
 �ṹ˵��  : AFC_PWM_SEL_MIX_CH1 �Ĵ����ṹ���塣��ַƫ����:0x00����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      afc_pwm_sel_mix_ch1_reg;
    struct
    {
        unsigned long  afc_pwm_sel_ch1 : 1;  /* bit[0]   : 0����ʾ����AFCѡ��PDM�����
                                                           1����ʾ����ѡ��PWM��� */
        unsigned long  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_AFC_PWM_SEL_MIX_CH1_UNION;
#define BBPCOMM_AFC_PWM_SEL_MIX_CH1_afc_pwm_sel_ch1_START  (0)
#define BBPCOMM_AFC_PWM_SEL_MIX_CH1_afc_pwm_sel_ch1_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_AFC_EN_MIX_CH1_UNION
 �ṹ˵��  : AFC_EN_MIX_CH1 �Ĵ����ṹ���塣��ַƫ����:0x04����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      afc_en_mix_ch1_reg;
    struct
    {
        unsigned long  afc_en_ch1 : 1;  /* bit[0]   : 1����ʾ����AFCʹ�ܣ�
                                                      0����ʾ����AFC��ʹ�� */
        unsigned long  reserved   : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_AFC_EN_MIX_CH1_UNION;
#define BBPCOMM_AFC_EN_MIX_CH1_afc_en_ch1_START  (0)
#define BBPCOMM_AFC_EN_MIX_CH1_afc_en_ch1_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_AFC_CFG_WIDTH_MIX_CH1_UNION
 �ṹ˵��  : AFC_CFG_WIDTH_MIX_CH1 �Ĵ����ṹ���塣��ַƫ����:0x08����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      afc_cfg_width_mix_ch1_reg;
    struct
    {
        unsigned long  afc_cfg_width_ch1 : 12; /* bit[0-11] : AFC����ֵ */
        unsigned long  reserved          : 20; /* bit[12-31]: ���� */
    } reg;
} BBPCOMM_AFC_CFG_WIDTH_MIX_CH1_UNION;
#define BBPCOMM_AFC_CFG_WIDTH_MIX_CH1_afc_cfg_width_ch1_START  (0)
#define BBPCOMM_AFC_CFG_WIDTH_MIX_CH1_afc_cfg_width_ch1_END    (11)


/*****************************************************************************
 �ṹ��    : BBPCOMM_AFC_CFG_SEL_MIX_CH1_UNION
 �ṹ˵��  : AFC_CFG_SEL_MIX_CH1 �Ĵ����ṹ���塣��ַƫ����:0x0C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      afc_cfg_sel_mix_ch1_reg;
    struct
    {
        unsigned long  afc_cfg_sel_ch1 : 1;  /* bit[0]   : 1����ʾѡ������AFCֵ
                                                           0����ʾѡ��BBP������AFCֵ */
        unsigned long  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_AFC_CFG_SEL_MIX_CH1_UNION;
#define BBPCOMM_AFC_CFG_SEL_MIX_CH1_afc_cfg_sel_ch1_START  (0)
#define BBPCOMM_AFC_CFG_SEL_MIX_CH1_afc_cfg_sel_ch1_END    (0)




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

#endif /* end of bbp_comm_on_interface.h */
