

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __BBP_GLB_ON_INTERFACE_H__
#define __BBP_GLB_ON_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/***======================================================================***
                     (1/1) register_define_bbp_on_glb
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    BBP����ģʽָʾ��0��W��1��TDS��2��1x��3��EV-DO��
   UNION�ṹ:  GLB_ON_MODE_SEL_UNION */
#define GLB_ON_MODE_SEL_ADDR                          (SOC_BBP_GLB_ON_BASE_ADDR + 0x1A00)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ������õ�RFIC2��λ�źţ�����Ч��0����λ��1���⸴λ��
             �ϵ��ʼ������Ϊ0������RFIC�ֲ�Ҫ��ά��һ��ʱ�������Ϊ1��
             �üĴ�������K3V5ʹ�á�
   UNION�ṹ:  GLB_ON_RFIC2_RSTN_UNION */
#define GLB_ON_RFIC2_RSTN_ADDR                        (SOC_BBP_GLB_ON_BASE_ADDR + 0x1A0C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ������õ�RFIC0��λ�źţ�����Ч��0����λ��1���⸴λ��
             �ϵ��ʼ������Ϊ0������RFIC�ֲ�Ҫ��ά��һ��ʱ�������Ϊ1��
             �üĴ�����CTU�ӿ�0x002C��ֲ������
   UNION�ṹ:  GLB_ON_RFIC0_RSTN_UNION */
#define GLB_ON_RFIC0_RSTN_ADDR                        (SOC_BBP_GLB_ON_BASE_ADDR + 0x1A10)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ������õ�RFIC1��λ�źţ�����Ч��0����λ��1���⸴λ��
             �ϵ��ʼ������Ϊ0������RFIC�ֲ�Ҫ��ά��һ��ʱ�������Ϊ1��
             �üĴ�����CTU�ӿ�0x032C��ֲ������
   UNION�ṹ:  GLB_ON_RFIC1_RSTN_UNION */
#define GLB_ON_RFIC1_RSTN_ADDR                        (SOC_BBP_GLB_ON_BASE_ADDR + 0x1A14)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      32k������ʱ����У׼��������ʹ���źţ������źţ���Ҫ����У׼���ڻ�У׼����ʱ��Ӧ������cpu_adjust_direction��cpu_adjust_period�������ô��ź�
   UNION�ṹ:  GLB_ON_COMM_TIMER_UPDATE_EN_UNION */
#define GLB_ON_COMM_TIMER_UPDATE_EN_ADDR              (SOC_BBP_GLB_ON_BASE_ADDR + 0x1A18)

/* �Ĵ���˵����
 bit[31]     32k������ʱ����ʱ��У׼����1��ʾÿcpu_adjust_period��ʱ�����ڣ�����1������
             0 ��ʾÿcpu_adjust_period��ʱ�����ڣ�����1������
 bit[30]     32k������ʱ����У׼ʹ�ܣ����ź�Ϊ1ʱ��У׼������Ч
 bit[29:24]  ����
 bit[23:0]   32k������ʱ����ʱ��У׼���ڣ���ʾÿcpu_adjust_period��ʱ�����ڣ����ٻ��߼���1������
   UNION�ṹ:  GLB_ON_COMM_TIMER_UPDATE_PARA_UNION */
#define GLB_ON_COMM_TIMER_UPDATE_PARA_ADDR            (SOC_BBP_GLB_ON_BASE_ADDR + 0x1A1C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      32k������ʱ����ʹ���źţ���Ҫʹ�ù�����ʱ��ʱ��������Ϊ1
   UNION�ṹ:  GLB_ON_COMM_TIMER_EN_UNION */
#define GLB_ON_COMM_TIMER_EN_ADDR                     (SOC_BBP_GLB_ON_BASE_ADDR + 0x1A20)

/* �Ĵ���˵����
   ��      ����32k������ʱ���ϱ��������á���������Ҫ׼ȷ�Ķ�ʱ��Ӧ��ͨ��BBP_COMM�ṩ�����涨ʱ���ܣ���ȡ��ģ��������ʱ���Ķ�ʱ��Ϣ
   UNION�ṹ ���� */
#define GLB_ON_COMM_TIMER_RPT1_ADDR                   (SOC_BBP_GLB_ON_BASE_ADDR + 0x1A24)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:0]   32KУ׼��ʱ���ϱ���������
   UNION�ṹ:  GLB_ON_COMM_TIMER_RPT2_UNION */
#define GLB_ON_COMM_TIMER_RPT2_ADDR                   (SOC_BBP_GLB_ON_BASE_ADDR + 0x1A28)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1]      SIM2ռ�ñ�־��������ڶ�д��BBP��ʹ��
 bit[0]      SIM1ռ�ñ�־��������ڶ�д��BBP��ʹ��
   UNION�ṹ:  GLB_ON_DSDS_SIM_FLAG_UNION */
#define GLB_ON_DSDS_SIM_FLAG_ADDR                     (SOC_BBP_GLB_ON_BASE_ADDR + 0x1A2C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      32K������ʱ���Ķ�ʱ�ж�
   UNION�ṹ:  GLB_ON_COMM_32K_INT_UNION */
#define GLB_ON_COMM_32K_INT_ADDR                      (SOC_BBP_GLB_ON_BASE_ADDR + 0x1A30)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      32K������ʱ���Ķ�ʱ�ж����μĴ�����1��ʾ���Σ�0��ʾ�ſ��ж�
   UNION�ṹ:  GLB_ON_COMM_32K_INT_MASK_UNION */
#define GLB_ON_COMM_32K_INT_MASK_ADDR                 (SOC_BBP_GLB_ON_BASE_ADDR + 0x1A34)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      32k������ʱ���ж�ʹ�ܼĴ�����1����ʾʹ���жϣ�0����ʾ��ʹ���жϡ�
   UNION�ṹ:  GLB_ON_COMM_32K_INT_EN_UNION */
#define GLB_ON_COMM_32K_INT_EN_ADDR                   (SOC_BBP_GLB_ON_BASE_ADDR + 0x1A38)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      32k������ʱ���ж�����Ĵ�����1����ʾ�����Ӧ����λ���жϣ�0����ʾ�������Ӧ����λ�õ��жϡ�
   UNION�ṹ:  GLB_ON_COMM_32K_INT3_CLR_UNION */
#define GLB_ON_COMM_32K_INT3_CLR_ADDR                 (SOC_BBP_GLB_ON_BASE_ADDR + 0x1A3C)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:0]   32Kʱ������Զ����ж����ڣ����÷�Χ��0~512s����λ��32kʱ�ӵ����ڸ�����ÿ��cpu_int_period��32kʱ�Ӻ����ڣ�����1���жϡ�ע�⣺��������ĵ���������N����Ӧ����N-1
   UNION�ṹ:  GLB_ON_COMM_32K_INT_PERIOD_UNION */
#define GLB_ON_COMM_32K_INT_PERIOD_ADDR               (SOC_BBP_GLB_ON_BASE_ADDR + 0x1A40)





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
                     (1/1) register_define_bbp_on_glb
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : GLB_ON_MODE_SEL_UNION
 �ṹ˵��  : MODE_SEL �Ĵ����ṹ���塣��ַƫ����:0x00����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      mode_sel_reg;
    struct
    {
        unsigned long  cpu_mode_sel : 2;  /* bit[0-1] : BBP����ģʽָʾ��0��W��1��TDS��2��1x��3��EV-DO�� */
        unsigned long  reserved     : 30; /* bit[2-31]: ���� */
    } reg;
} GLB_ON_MODE_SEL_UNION;
#define GLB_ON_MODE_SEL_cpu_mode_sel_START  (0)
#define GLB_ON_MODE_SEL_cpu_mode_sel_END    (1)


/*****************************************************************************
 �ṹ��    : GLB_ON_RFIC2_RSTN_UNION
 �ṹ˵��  : RFIC2_RSTN �Ĵ����ṹ���塣��ַƫ����:0x0C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      rfic2_rstn_reg;
    struct
    {
        unsigned long  rfic2_rstn : 1;  /* bit[0]   : ������õ�RFIC2��λ�źţ�����Ч��0����λ��1���⸴λ��
                                                      �ϵ��ʼ������Ϊ0������RFIC�ֲ�Ҫ��ά��һ��ʱ�������Ϊ1��
                                                      �üĴ�������K3V5ʹ�á� */
        unsigned long  reserved   : 31; /* bit[1-31]: ���� */
    } reg;
} GLB_ON_RFIC2_RSTN_UNION;
#define GLB_ON_RFIC2_RSTN_rfic2_rstn_START  (0)
#define GLB_ON_RFIC2_RSTN_rfic2_rstn_END    (0)


/*****************************************************************************
 �ṹ��    : GLB_ON_RFIC0_RSTN_UNION
 �ṹ˵��  : RFIC0_RSTN �Ĵ����ṹ���塣��ַƫ����:0x10����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      rfic0_rstn_reg;
    struct
    {
        unsigned long  rfic0_rstn : 1;  /* bit[0]   : ������õ�RFIC0��λ�źţ�����Ч��0����λ��1���⸴λ��
                                                      �ϵ��ʼ������Ϊ0������RFIC�ֲ�Ҫ��ά��һ��ʱ�������Ϊ1��
                                                      �üĴ�����CTU�ӿ�0x002C��ֲ������ */
        unsigned long  reserved   : 31; /* bit[1-31]: ���� */
    } reg;
} GLB_ON_RFIC0_RSTN_UNION;
#define GLB_ON_RFIC0_RSTN_rfic0_rstn_START  (0)
#define GLB_ON_RFIC0_RSTN_rfic0_rstn_END    (0)


/*****************************************************************************
 �ṹ��    : GLB_ON_RFIC1_RSTN_UNION
 �ṹ˵��  : RFIC1_RSTN �Ĵ����ṹ���塣��ַƫ����:0x14����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      rfic1_rstn_reg;
    struct
    {
        unsigned long  rfic1_rstn : 1;  /* bit[0]   : ������õ�RFIC1��λ�źţ�����Ч��0����λ��1���⸴λ��
                                                      �ϵ��ʼ������Ϊ0������RFIC�ֲ�Ҫ��ά��һ��ʱ�������Ϊ1��
                                                      �üĴ�����CTU�ӿ�0x032C��ֲ������ */
        unsigned long  reserved   : 31; /* bit[1-31]: ���� */
    } reg;
} GLB_ON_RFIC1_RSTN_UNION;
#define GLB_ON_RFIC1_RSTN_rfic1_rstn_START  (0)
#define GLB_ON_RFIC1_RSTN_rfic1_rstn_END    (0)


/*****************************************************************************
 �ṹ��    : GLB_ON_COMM_TIMER_UPDATE_EN_UNION
 �ṹ˵��  : COMM_TIMER_UPDATE_EN �Ĵ����ṹ���塣��ַƫ����:0x18����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      comm_timer_update_en_reg;
    struct
    {
        unsigned long  cpu_adj_period_update_en : 1;  /* bit[0]   : 32k������ʱ����У׼��������ʹ���źţ������źţ���Ҫ����У׼���ڻ�У׼����ʱ��Ӧ������cpu_adjust_direction��cpu_adjust_period�������ô��ź� */
        unsigned long  reserved                 : 31; /* bit[1-31]: ���� */
    } reg;
} GLB_ON_COMM_TIMER_UPDATE_EN_UNION;
#define GLB_ON_COMM_TIMER_UPDATE_EN_cpu_adj_period_update_en_START  (0)
#define GLB_ON_COMM_TIMER_UPDATE_EN_cpu_adj_period_update_en_END    (0)


/*****************************************************************************
 �ṹ��    : GLB_ON_COMM_TIMER_UPDATE_PARA_UNION
 �ṹ˵��  : COMM_TIMER_UPDATE_PARA �Ĵ����ṹ���塣��ַƫ����:0x1C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      comm_timer_update_para_reg;
    struct
    {
        unsigned long  cpu_adjust_period    : 24; /* bit[0-23] : 32k������ʱ����ʱ��У׼���ڣ���ʾÿcpu_adjust_period��ʱ�����ڣ����ٻ��߼���1������ */
        unsigned long  reserved             : 6;  /* bit[24-29]: ���� */
        unsigned long  cpu_adjust_en        : 1;  /* bit[30]   : 32k������ʱ����У׼ʹ�ܣ����ź�Ϊ1ʱ��У׼������Ч */
        unsigned long  cpu_adjust_direction : 1;  /* bit[31]   : 32k������ʱ����ʱ��У׼����1��ʾÿcpu_adjust_period��ʱ�����ڣ�����1������
                                                                 0 ��ʾÿcpu_adjust_period��ʱ�����ڣ�����1������ */
    } reg;
} GLB_ON_COMM_TIMER_UPDATE_PARA_UNION;
#define GLB_ON_COMM_TIMER_UPDATE_PARA_cpu_adjust_period_START     (0)
#define GLB_ON_COMM_TIMER_UPDATE_PARA_cpu_adjust_period_END       (23)
#define GLB_ON_COMM_TIMER_UPDATE_PARA_cpu_adjust_en_START         (30)
#define GLB_ON_COMM_TIMER_UPDATE_PARA_cpu_adjust_en_END           (30)
#define GLB_ON_COMM_TIMER_UPDATE_PARA_cpu_adjust_direction_START  (31)
#define GLB_ON_COMM_TIMER_UPDATE_PARA_cpu_adjust_direction_END    (31)


/*****************************************************************************
 �ṹ��    : GLB_ON_COMM_TIMER_EN_UNION
 �ṹ˵��  : COMM_TIMER_EN �Ĵ����ṹ���塣��ַƫ����:0x20����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      comm_timer_en_reg;
    struct
    {
        unsigned long  cpu_comm_timer_en : 1;  /* bit[0]   : 32k������ʱ����ʹ���źţ���Ҫʹ�ù�����ʱ��ʱ��������Ϊ1 */
        unsigned long  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} GLB_ON_COMM_TIMER_EN_UNION;
#define GLB_ON_COMM_TIMER_EN_cpu_comm_timer_en_START  (0)
#define GLB_ON_COMM_TIMER_EN_cpu_comm_timer_en_END    (0)


/*****************************************************************************
 �ṹ��    : GLB_ON_COMM_TIMER_RPT2_UNION
 �ṹ˵��  : COMM_TIMER_RPT2 �Ĵ����ṹ���塣��ַƫ����:0x28����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      comm_timer_rpt2_reg;
    struct
    {
        unsigned long  adjust_timer : 24; /* bit[0-23] : 32KУ׼��ʱ���ϱ��������� */
        unsigned long  reserved     : 8;  /* bit[24-31]: ���� */
    } reg;
} GLB_ON_COMM_TIMER_RPT2_UNION;
#define GLB_ON_COMM_TIMER_RPT2_adjust_timer_START  (0)
#define GLB_ON_COMM_TIMER_RPT2_adjust_timer_END    (23)


/*****************************************************************************
 �ṹ��    : GLB_ON_DSDS_SIM_FLAG_UNION
 �ṹ˵��  : DSDS_SIM_FLAG �Ĵ����ṹ���塣��ַƫ����:0x2C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      dsds_sim_flag_reg;
    struct
    {
        unsigned long  cpu_sim1_en : 1;  /* bit[0]   : SIM1ռ�ñ�־��������ڶ�д��BBP��ʹ�� */
        unsigned long  cpu_sim2_en : 1;  /* bit[1]   : SIM2ռ�ñ�־��������ڶ�д��BBP��ʹ�� */
        unsigned long  reserved    : 30; /* bit[2-31]: ���� */
    } reg;
} GLB_ON_DSDS_SIM_FLAG_UNION;
#define GLB_ON_DSDS_SIM_FLAG_cpu_sim1_en_START  (0)
#define GLB_ON_DSDS_SIM_FLAG_cpu_sim1_en_END    (0)
#define GLB_ON_DSDS_SIM_FLAG_cpu_sim2_en_START  (1)
#define GLB_ON_DSDS_SIM_FLAG_cpu_sim2_en_END    (1)


/*****************************************************************************
 �ṹ��    : GLB_ON_COMM_32K_INT_UNION
 �ṹ˵��  : COMM_32K_INT �Ĵ����ṹ���塣��ַƫ����:0x30����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      comm_32k_int_reg;
    struct
    {
        unsigned long  comm_32k_int_sta : 1;  /* bit[0]   : 32K������ʱ���Ķ�ʱ�ж� */
        unsigned long  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} GLB_ON_COMM_32K_INT_UNION;
#define GLB_ON_COMM_32K_INT_comm_32k_int_sta_START  (0)
#define GLB_ON_COMM_32K_INT_comm_32k_int_sta_END    (0)


/*****************************************************************************
 �ṹ��    : GLB_ON_COMM_32K_INT_MASK_UNION
 �ṹ˵��  : COMM_32K_INT_MASK �Ĵ����ṹ���塣��ַƫ����:0x34����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      comm_32k_int_mask_reg;
    struct
    {
        unsigned long  comm_32k_int_mask : 1;  /* bit[0]   : 32K������ʱ���Ķ�ʱ�ж����μĴ�����1��ʾ���Σ�0��ʾ�ſ��ж� */
        unsigned long  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} GLB_ON_COMM_32K_INT_MASK_UNION;
#define GLB_ON_COMM_32K_INT_MASK_comm_32k_int_mask_START  (0)
#define GLB_ON_COMM_32K_INT_MASK_comm_32k_int_mask_END    (0)


/*****************************************************************************
 �ṹ��    : GLB_ON_COMM_32K_INT_EN_UNION
 �ṹ˵��  : COMM_32K_INT_EN �Ĵ����ṹ���塣��ַƫ����:0x38����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      comm_32k_int_en_reg;
    struct
    {
        unsigned long  comm_32k_int_en : 1;  /* bit[0]   : 32k������ʱ���ж�ʹ�ܼĴ�����1����ʾʹ���жϣ�0����ʾ��ʹ���жϡ� */
        unsigned long  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} GLB_ON_COMM_32K_INT_EN_UNION;
#define GLB_ON_COMM_32K_INT_EN_comm_32k_int_en_START  (0)
#define GLB_ON_COMM_32K_INT_EN_comm_32k_int_en_END    (0)


/*****************************************************************************
 �ṹ��    : GLB_ON_COMM_32K_INT3_CLR_UNION
 �ṹ˵��  : COMM_32K_INT3_CLR �Ĵ����ṹ���塣��ַƫ����:0x3C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      comm_32k_int3_clr_reg;
    struct
    {
        unsigned long  comm_32k_int_clr : 1;  /* bit[0]   : 32k������ʱ���ж�����Ĵ�����1����ʾ�����Ӧ����λ���жϣ�0����ʾ�������Ӧ����λ�õ��жϡ� */
        unsigned long  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} GLB_ON_COMM_32K_INT3_CLR_UNION;
#define GLB_ON_COMM_32K_INT3_CLR_comm_32k_int_clr_START  (0)
#define GLB_ON_COMM_32K_INT3_CLR_comm_32k_int_clr_END    (0)


/*****************************************************************************
 �ṹ��    : GLB_ON_COMM_32K_INT_PERIOD_UNION
 �ṹ˵��  : COMM_32K_INT_PERIOD �Ĵ����ṹ���塣��ַƫ����:0x40����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned long      comm_32k_int_period_reg;
    struct
    {
        unsigned long  cpu_int_period : 24; /* bit[0-23] : 32Kʱ������Զ����ж����ڣ����÷�Χ��0~512s����λ��32kʱ�ӵ����ڸ�����ÿ��cpu_int_period��32kʱ�Ӻ����ڣ�����1���жϡ�ע�⣺��������ĵ���������N����Ӧ����N-1 */
        unsigned long  reserved       : 8;  /* bit[24-31]: ���� */
    } reg;
} GLB_ON_COMM_32K_INT_PERIOD_UNION;
#define GLB_ON_COMM_32K_INT_PERIOD_cpu_int_period_START  (0)
#define GLB_ON_COMM_32K_INT_PERIOD_cpu_int_period_END    (23)




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

#endif /* end of bbp_glb_on_interface.h */
