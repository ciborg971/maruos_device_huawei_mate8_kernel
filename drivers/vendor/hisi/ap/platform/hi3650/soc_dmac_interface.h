/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_dmac_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:19:53
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_DMAC.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_DMAC_INTERFACE_H__
#define __SOC_DMAC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) register_dmac
 ****************************************************************************/
/* �Ĵ���˵����������X���ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_DMAC_INT_STAT_UNION */
#define SOC_DMAC_INT_STAT_ADDR(base, in)              ((base) + (0x0000+0x40*(in)))

/* �Ĵ���˵����������X��ͨ����������ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_DMAC_INT_TC1_UNION */
#define SOC_DMAC_INT_TC1_ADDR(base, in)               ((base) + (0x0004+0x40*(in)))

/* �Ĵ���˵����������X������ڵ㴫������ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_DMAC_INT_TC2_UNION */
#define SOC_DMAC_INT_TC2_ADDR(base, in)               ((base) + (0x0008+0x40*(in)))

/* �Ĵ���˵����������X�����ô����ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_DMAC_INT_ERR1_UNION */
#define SOC_DMAC_INT_ERR1_ADDR(base, in)              ((base) + (0x000C+0x40*(in)))

/* �Ĵ���˵����������X�����ݴ�������ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_DMAC_INT_ERR2_UNION */
#define SOC_DMAC_INT_ERR2_ADDR(base, in)              ((base) + (0x0010+0x40*(in)))

/* �Ĵ���˵����������X�Ķ���������ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_DMAC_INT_ERR3_UNION */
#define SOC_DMAC_INT_ERR3_ADDR(base, in)              ((base) + (0x0014+0x40*(in)))

/* �Ĵ���˵����������X��ͨ����������ж����μĴ�����
   λ����UNION�ṹ:  SOC_DMAC_INT_TC1_MASK_UNION */
#define SOC_DMAC_INT_TC1_MASK_ADDR(base, in)          ((base) + (0x0018+0x40*(in)))

/* �Ĵ���˵����������X������ڵ㴫������ж����μĴ�����
   λ����UNION�ṹ:  SOC_DMAC_INT_TC2_MASK_UNION */
#define SOC_DMAC_INT_TC2_MASK_ADDR(base, in)          ((base) + (0x001C+0x40*(in)))

/* �Ĵ���˵����������X�����ô����ж����μĴ�����
   λ����UNION�ṹ:  SOC_DMAC_INT_ERR1_MASK_UNION */
#define SOC_DMAC_INT_ERR1_MASK_ADDR(base, in)         ((base) + (0x0020+0x40*(in)))

/* �Ĵ���˵����������X�����ݴ�������ж����μĴ�����
   λ����UNION�ṹ:  SOC_DMAC_INT_ERR2_MASK_UNION */
#define SOC_DMAC_INT_ERR2_MASK_ADDR(base, in)         ((base) + (0x0024+0x40*(in)))

/* �Ĵ���˵����������X�������ȡ�����ж����μĴ�����
   λ����UNION�ṹ:  SOC_DMAC_INT_ERR3_MASK_UNION */
#define SOC_DMAC_INT_ERR3_MASK_ADDR(base, in)         ((base) + (0x0028+0x40*(in)))

/* �Ĵ���˵����ԭʼͨ����������ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_DMAC_INT_TC1_RAW_UNION */
#define SOC_DMAC_INT_TC1_RAW_ADDR(base)               ((base) + (0x0600))

/* �Ĵ���˵����ԭʼ����ڵ㴫������ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_DMAC_INT_TC2_RAW_UNION */
#define SOC_DMAC_INT_TC2_RAW_ADDR(base)               ((base) + (0x0608))

/* �Ĵ���˵����ԭʼ���ô����ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_DMAC_INT_ERR1_RAW_UNION */
#define SOC_DMAC_INT_ERR1_RAW_ADDR(base)              ((base) + (0x0610))

/* �Ĵ���˵����ԭʼ���ݴ�������ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_DMAC_INT_ERR2_RAW_UNION */
#define SOC_DMAC_INT_ERR2_RAW_ADDR(base)              ((base) + (0x0618))

/* �Ĵ���˵����ԭʼ�����ȡ�����ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_DMAC_INT_ERR3_RAW_UNION */
#define SOC_DMAC_INT_ERR3_RAW_ADDR(base)              ((base) + (0x0620))

/* �Ĵ���˵��������������Ĵ�����
   λ����UNION�ṹ:  SOC_DMAC_SREQ_UNION */
#define SOC_DMAC_SREQ_ADDR(base)                      ((base) + (0x660))

/* �Ĵ���˵����ĩ�ε���������Ĵ�����
   λ����UNION�ṹ:  SOC_DMAC_LSREQ_UNION */
#define SOC_DMAC_LSREQ_ADDR(base)                     ((base) + (0x664))

/* �Ĵ���˵����ͻ����������Ĵ�����
   λ����UNION�ṹ:  SOC_DMAC_BREQ_UNION */
#define SOC_DMAC_BREQ_ADDR(base)                      ((base) + (0x668))

/* �Ĵ���˵����ĩ��ͻ����������Ĵ�����
   λ����UNION�ṹ:  SOC_DMAC_LBREQ_UNION */
#define SOC_DMAC_LBREQ_ADDR(base)                     ((base) + (0x66C))

/* �Ĵ���˵����������������Ĵ�����
   λ����UNION�ṹ:  SOC_DMAC_FREQ_UNION */
#define SOC_DMAC_FREQ_ADDR(base)                      ((base) + (0x670))

/* �Ĵ���˵����ĩ��������������Ĵ�����
   λ����UNION�ṹ:  SOC_DMAC_LFREQ_UNION */
#define SOC_DMAC_LFREQ_ADDR(base)                     ((base) + (0x674))

/* �Ĵ���˵�������ȼ����ƼĴ�����
   λ����UNION�ṹ:  SOC_DMAC_CH_PRI_UNION */
#define SOC_DMAC_CH_PRI_ADDR(base)                    ((base) + (0x688))

/* �Ĵ���˵����ȫ��DMA״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_DMAC_CH_STAT_UNION */
#define SOC_DMAC_CH_STAT_ADDR(base)                   ((base) + (0x690))

/* �Ĵ���˵����DMAȫ�ְ�ȫ���ƼĴ�����
   λ����UNION�ṹ:  SOC_DMAC_SEC_CTRL_UNION */
#define SOC_DMAC_SEC_CTRL_ADDR(base)                  ((base) + (0x0694))

/* �Ĵ���˵����DMAȫ�ֿ��ƼĴ�����
   λ����UNION�ṹ:  SOC_DMAC_DMA_CTRL_UNION */
#define SOC_DMAC_DMA_CTRL_ADDR(base)                  ((base) + (0x0698))

/* �Ĵ���˵����ͨ��X����ά����ʣ��size״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_DMAC_CX_CURR_CNT1_UNION */
#define SOC_DMAC_CX_CURR_CNT1_ADDR(base, cn)          ((base) + (0x0700+0x10*(cn)))

/* �Ĵ���˵����ͨ��X��һ����ά����ʣ��size״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_DMAC_CX_CURR_CNT0_UNION */
#define SOC_DMAC_CX_CURR_CNT0_ADDR(base, cn)          ((base) + (0x0704+0x10*(cn)))

/* �Ĵ���˵����ͨ��X��Դ��ַ�Ĵ�����
   λ����UNION�ṹ:  SOC_DMAC_CX_CURR_SRC_ADDR_UNION */
#define SOC_DMAC_CX_CURR_SRC_ADDR_ADDR(base, cn)      ((base) + (0x0708+0x10*(cn)))

/* �Ĵ���˵����ͨ��X��Ŀ�ĵ�ַ�Ĵ�����
   λ����UNION�ṹ:  SOC_DMAC_CX_CURR_DES_ADDR_UNION */
#define SOC_DMAC_CX_CURR_DES_ADDR_ADDR(base, cn)      ((base) + (0x070C+0x10*(cn)))

/* �Ĵ���˵����ͨ��X�������ַ�Ĵ�����
   λ����UNION�ṹ:  SOC_DMAC_CX_LLI_UNION */
#define SOC_DMAC_CX_LLI_ADDR(base, cn)                ((base) + (0x0800+0x40*(cn)))

/* �Ĵ���˵����ͨ��X�Ķ�ά��ַƫ�������üĴ�����
   λ����UNION�ṹ:  SOC_DMAC_CX_BINDX_UNION */
#define SOC_DMAC_CX_BINDX_ADDR(base, cn)              ((base) + (0x0804+0x40*(cn)))

/* �Ĵ���˵����ͨ��X����ά��ַƫ�������üĴ�����
   λ����UNION�ṹ:  SOC_DMAC_CX_CINDX_UNION */
#define SOC_DMAC_CX_CINDX_ADDR(base, cn)              ((base) + (0x0808+0x40*(cn)))

/* �Ĵ���˵����ͨ��X�Ĵ��䳤��1���üĴ�����
   λ����UNION�ṹ:  SOC_DMAC_CX_CNT1_UNION */
#define SOC_DMAC_CX_CNT1_ADDR(base, cn)               ((base) + (0x080C+0x40*(cn)))

/* �Ĵ���˵����ͨ��X�Ĵ��䳤�����üĴ�����
   λ����UNION�ṹ:  SOC_DMAC_CX_CNT0_UNION */
#define SOC_DMAC_CX_CNT0_ADDR(base, cn)               ((base) + (0x0810+0x40*(cn)))

/* �Ĵ���˵����ͨ��X��Դ��ַ�Ĵ�����
   λ����UNION�ṹ:  SOC_DMAC_CX_SRC_ADDR_UNION */
#define SOC_DMAC_CX_SRC_ADDR_ADDR(base, cn)           ((base) + (0x0814+0x40*(cn)))

/* �Ĵ���˵����ͨ��X��Ŀ�ĵ�ַ�Ĵ�����
   λ����UNION�ṹ:  SOC_DMAC_CX_DES_ADDR_UNION */
#define SOC_DMAC_CX_DES_ADDR_ADDR(base, cn)           ((base) + (0x0818+0x40*(cn)))

/* �Ĵ���˵����ͨ��X�����üĴ�����
   λ����UNION�ṹ:  SOC_DMAC_CX_CONFIG_UNION */
#define SOC_DMAC_CX_CONFIG_ADDR(base, cn)             ((base) + (0x081C+0x40*(cn)))

/* �Ĵ���˵����ͨ��X��AXI����������üĴ�����
   λ����UNION�ṹ:  SOC_DMAC_CX_AXI_CONF_UNION */
#define SOC_DMAC_CX_AXI_CONF_ADDR(base, cn)           ((base) + (0x0820+0x40*(cn)))





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
                     (1/1) register_dmac
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_DMAC_INT_STAT_UNION
 �ṹ˵��  : INT_STAT �Ĵ����ṹ���塣��ַƫ����:0x0000+0x40*(in)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������X���ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_stat : 16; /* bit[0-15] : DMAC��ͨ�������κ���ж�״̬��bit[15:0]�ֱ��Ӧͨ��15��0��
                                                    0��δ�����жϣ�
                                                    1���Ѳ����жϣ����ж�����������Ը�ͨ���Ĵ����жϻ�������жϡ� */
        unsigned int  reserved : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_DMAC_INT_STAT_UNION;
#endif
#define SOC_DMAC_INT_STAT_int_stat_START  (0)
#define SOC_DMAC_INT_STAT_int_stat_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_INT_TC1_UNION
 �ṹ˵��  : INT_TC1 �Ĵ����ṹ���塣��ַƫ����:0x0004+0x40*(in)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������X��ͨ����������ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_tc1  : 16; /* bit[0-15] : DMAC��ͨ���������κ��ͨ����������ж�״̬��bit[15:0]�ֱ��Ӧͨ��15��0��
                                                    0��δ������������жϣ�
                                                    1���Ѳ�����������жϡ� */
        unsigned int  reserved : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_DMAC_INT_TC1_UNION;
#endif
#define SOC_DMAC_INT_TC1_int_tc1_START   (0)
#define SOC_DMAC_INT_TC1_int_tc1_END     (15)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_INT_TC2_UNION
 �ṹ˵��  : INT_TC2 �Ĵ����ṹ���塣��ַƫ����:0x0008+0x40*(in)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������X������ڵ㴫������ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_tc2  : 16; /* bit[0-15] : DMAC��ͨ���������κ������ڵ㴫������ж�״̬��bit[15:0]�ֱ��Ӧͨ��15��0��
                                                    0��δ������������жϣ�
                                                    1���Ѳ�����������жϡ� */
        unsigned int  reserved : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_DMAC_INT_TC2_UNION;
#endif
#define SOC_DMAC_INT_TC2_int_tc2_START   (0)
#define SOC_DMAC_INT_TC2_int_tc2_END     (15)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_INT_ERR1_UNION
 �ṹ˵��  : INT_ERR1 �Ĵ����ṹ���塣��ַƫ����:0x000C+0x40*(in)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������X�����ô����ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_err1 : 16; /* bit[0-15] : DMAC��ͨ���������κ�����ô����ж�״̬��bit[15:0]�ֱ��Ӧͨ��15��0��
                                                    0��δ������������жϣ�
                                                    1�������˴�������жϡ�
                                                    ���жϿ������ԣ�
                                                    1������AcountΪ0��
                                                    2��ͨ������ʱָ���ͨ�����Ӻ�Ϊ��ͨ����
                                                    3��ͨ�����ӵ������ڵ�ͨ����ͨ����ĿС��16ʱ�Ż���������������
                                                    4��֧��narrow����ʱ������burst size��reservedֵ��
                                                    5��FIX����ʱ�����õ�ַ��burst size�����롣
                                                    6������flow_ctrl��reservedֵ��
                                                    7������chain_en��reservedֵ��
                                                    8������ڵ�����ó������������Ҳ�ᴥ�����ô����ж� */
        unsigned int  reserved : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_DMAC_INT_ERR1_UNION;
#endif
#define SOC_DMAC_INT_ERR1_int_err1_START  (0)
#define SOC_DMAC_INT_ERR1_int_err1_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_INT_ERR2_UNION
 �ṹ˵��  : INT_ERR2 �Ĵ����ṹ���塣��ַƫ����:0x0010+0x40*(in)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������X�����ݴ�������ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_err2 : 16; /* bit[0-15] : DMAC��ͨ���������κ�����ݴ�������ж�״̬��bit[15:0]�ֱ��Ӧͨ��15��0��
                                                    0��δ�����жϣ�
                                                    1���Ѳ����жϡ� */
        unsigned int  reserved : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_DMAC_INT_ERR2_UNION;
#endif
#define SOC_DMAC_INT_ERR2_int_err2_START  (0)
#define SOC_DMAC_INT_ERR2_int_err2_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_INT_ERR3_UNION
 �ṹ˵��  : INT_ERR3 �Ĵ����ṹ���塣��ַƫ����:0x0014+0x40*(in)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������X�Ķ���������ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_err3 : 16; /* bit[0-15] : DMAC��ͨ���������κ�Ķ���������ж�״̬��bit[15:0]�ֱ��Ӧͨ��15��0��
                                                    0��δ�����жϣ�
                                                    1���Ѳ����жϡ� */
        unsigned int  reserved : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_DMAC_INT_ERR3_UNION;
#endif
#define SOC_DMAC_INT_ERR3_int_err3_START  (0)
#define SOC_DMAC_INT_ERR3_int_err3_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_INT_TC1_MASK_UNION
 �ṹ˵��  : INT_TC1_MASK �Ĵ����ṹ���塣��ַƫ����:0x0018+0x40*(in)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������X��ͨ����������ж����μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_tc1_mask : 16; /* bit[0-15] : DMAC��ͨ����������ж����Σ�bit[15:0]�ֱ��Ӧͨ��15��0��
                                                        0�����α�ͨ���Ĵ�������жϡ�
                                                        1�������α�ͨ���Ĵ�������жϡ� */
        unsigned int  reserved     : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_DMAC_INT_TC1_MASK_UNION;
#endif
#define SOC_DMAC_INT_TC1_MASK_int_tc1_mask_START  (0)
#define SOC_DMAC_INT_TC1_MASK_int_tc1_mask_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_INT_TC2_MASK_UNION
 �ṹ˵��  : INT_TC2_MASK �Ĵ����ṹ���塣��ַƫ����:0x001C+0x40*(in)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������X������ڵ㴫������ж����μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_tc2_mask : 16; /* bit[0-15] : DMAC��ͨ������ڵ㴫������ж����Σ�bit[15:0]�ֱ��Ӧͨ��15��0��
                                                        0�����α�ͨ��������ڵ㴫������жϡ�
                                                        1�������α�ͨ��������ڵ㴫������жϡ� */
        unsigned int  reserved     : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_DMAC_INT_TC2_MASK_UNION;
#endif
#define SOC_DMAC_INT_TC2_MASK_int_tc2_mask_START  (0)
#define SOC_DMAC_INT_TC2_MASK_int_tc2_mask_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_INT_ERR1_MASK_UNION
 �ṹ˵��  : INT_ERR1_MASK �Ĵ����ṹ���塣��ַƫ����:0x0020+0x40*(in)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������X�����ô����ж����μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_err1_mask : 16; /* bit[0-15] : DMAC��ͨ�����ô����ж����Σ�bit[15:0]�ֱ��Ӧͨ��15��0��
                                                         0�����α�ͨ�������ô����жϡ�
                                                         1�������α�ͨ�������ô����жϡ� */
        unsigned int  reserved      : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_DMAC_INT_ERR1_MASK_UNION;
#endif
#define SOC_DMAC_INT_ERR1_MASK_int_err1_mask_START  (0)
#define SOC_DMAC_INT_ERR1_MASK_int_err1_mask_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_INT_ERR2_MASK_UNION
 �ṹ˵��  : INT_ERR2_MASK �Ĵ����ṹ���塣��ַƫ����:0x0024+0x40*(in)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������X�����ݴ�������ж����μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_err2_mask : 16; /* bit[0-15] : DMAC�����ݴ�������ж����Σ�bit[15:0]�ֱ��Ӧͨ��15��0��
                                                         0�����α�ͨ�������ݴ�������жϡ�
                                                         1�������α�ͨ�������ݴ�������жϡ� */
        unsigned int  reserved      : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_DMAC_INT_ERR2_MASK_UNION;
#endif
#define SOC_DMAC_INT_ERR2_MASK_int_err2_mask_START  (0)
#define SOC_DMAC_INT_ERR2_MASK_int_err2_mask_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_INT_ERR3_MASK_UNION
 �ṹ˵��  : INT_ERR3_MASK �Ĵ����ṹ���塣��ַƫ����:0x0028+0x40*(in)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������X�������ȡ�����ж����μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_err3_mask : 16; /* bit[0-15] : DMAC��ͨ�������ȡ�����ж����Σ�bit[15:0]�ֱ��Ӧͨ��15��0��
                                                         0�����α�ͨ���������ȡ�����жϡ�
                                                         1�������α�ͨ���������ȡ�����жϡ� */
        unsigned int  reserved      : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_DMAC_INT_ERR3_MASK_UNION;
#endif
#define SOC_DMAC_INT_ERR3_MASK_int_err3_mask_START  (0)
#define SOC_DMAC_INT_ERR3_MASK_int_err3_mask_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_INT_TC1_RAW_UNION
 �ṹ˵��  : INT_TC1_RAW �Ĵ����ṹ���塣��ַƫ����:0x0600����ֵ:0x00000000�����:32
 �Ĵ���˵��: ԭʼͨ����������ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_tc1_raw : 16; /* bit[0-15] : ��ͨ������ǰ��ͨ����������ж�״̬��bit[15:0]�ֱ��Ӧͨ��15��0��
                                                       ��:
                                                       0��δ����ͨ����������жϣ�
                                                       1��������ͨ����������жϡ�
                                                       д:
                                                       1:���ͨ����������жϡ�
                                                       0:����֮ǰ��ֵ�� */
        unsigned int  reserved    : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_DMAC_INT_TC1_RAW_UNION;
#endif
#define SOC_DMAC_INT_TC1_RAW_int_tc1_raw_START  (0)
#define SOC_DMAC_INT_TC1_RAW_int_tc1_raw_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_INT_TC2_RAW_UNION
 �ṹ˵��  : INT_TC2_RAW �Ĵ����ṹ���塣��ַƫ����:0x0608����ֵ:0x00000000�����:32
 �Ĵ���˵��: ԭʼ����ڵ㴫������ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_tc2_raw : 16; /* bit[0-15] : ��ͨ������ǰ������ڵ㴫������ж�״̬��bit[15:0]�ֱ��Ӧͨ��15��0��
                                                       ��:
                                                       0��δ�����ڵ���ɳ��жϣ�
                                                       1�������˽ڵ�����жϡ�
                                                       д:
                                                       1:����ڵ�����жϡ�
                                                       0:����֮ǰ��ֵ�� */
        unsigned int  reserved    : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_DMAC_INT_TC2_RAW_UNION;
#endif
#define SOC_DMAC_INT_TC2_RAW_int_tc2_raw_START  (0)
#define SOC_DMAC_INT_TC2_RAW_int_tc2_raw_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_INT_ERR1_RAW_UNION
 �ṹ˵��  : INT_ERR1_RAW �Ĵ����ṹ���塣��ַƫ����:0x0610����ֵ:0x00000000�����:32
 �Ĵ���˵��: ԭʼ���ô����ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_err1_raw : 16; /* bit[0-15] : ��ͨ������ǰ�����ô����ж�״̬��bit[15:0]�ֱ��Ӧͨ��15��0��
                                                        0��δ�������ô����жϣ�
                                                        1�����������ô����жϡ�
                                                        д:
                                                        1:������ô����жϡ�
                                                        0:����֮ǰ��ֵ�� */
        unsigned int  reserved     : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_DMAC_INT_ERR1_RAW_UNION;
#endif
#define SOC_DMAC_INT_ERR1_RAW_int_err1_raw_START  (0)
#define SOC_DMAC_INT_ERR1_RAW_int_err1_raw_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_INT_ERR2_RAW_UNION
 �ṹ˵��  : INT_ERR2_RAW �Ĵ����ṹ���塣��ַƫ����:0x0618����ֵ:0x00000000�����:32
 �Ĵ���˵��: ԭʼ���ݴ�������ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_err2_raw : 16; /* bit[0-15] : ��ͨ������ǰ�����ݴ�������ж�״̬��bit[15:0]�ֱ��Ӧͨ��15��0��
                                                        0��δ�������ݴ�������жϣ�
                                                        1�����������ݴ�������жϡ�
                                                        д:
                                                        1:������ݴ�������жϡ�
                                                        0:����֮ǰ��ֵ�� */
        unsigned int  reserved     : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_DMAC_INT_ERR2_RAW_UNION;
#endif
#define SOC_DMAC_INT_ERR2_RAW_int_err2_raw_START  (0)
#define SOC_DMAC_INT_ERR2_RAW_int_err2_raw_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_INT_ERR3_RAW_UNION
 �ṹ˵��  : INT_ERR3_RAW �Ĵ����ṹ���塣��ַƫ����:0x0620����ֵ:0x00000000�����:32
 �Ĵ���˵��: ԭʼ�����ȡ�����ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_err3_raw : 16; /* bit[0-15] : ��ͨ������ǰ�������ȡ�����ж�״̬��bit[15:0]�ֱ��Ӧͨ��15��0��
                                                        0��δ���������ȡ�����жϣ�
                                                        1�������������ȡ�����жϡ�
                                                        д:
                                                        1:��������ȡ�����жϡ�
                                                        0:����֮ǰ��ֵ�� */
        unsigned int  reserved     : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_DMAC_INT_ERR3_RAW_UNION;
#endif
#define SOC_DMAC_INT_ERR3_RAW_int_err3_raw_START  (0)
#define SOC_DMAC_INT_ERR3_RAW_int_err3_raw_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_SREQ_UNION
 �ṹ˵��  : SREQ �Ĵ����ṹ���塣��ַƫ����:0x660����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����������Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sreq : 32; /* bit[0-31]: ����������Ʋ���DMA single ��������
                                               ��д�üĴ���ʱ��
                                               0����Ӱ�죻
                                               1������DMA single �������󣬵��������ʱ�üĴ����е���Ӧλ�����㡣
                                               �����üĴ���ʱ��
                                               0����Ӧ����������δ����single��������
                                               1����Ӧ���������跢��single�������� */
    } reg;
} SOC_DMAC_SREQ_UNION;
#endif
#define SOC_DMAC_SREQ_sreq_START  (0)
#define SOC_DMAC_SREQ_sreq_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_LSREQ_UNION
 �ṹ˵��  : LSREQ �Ĵ����ṹ���塣��ַƫ����:0x664����ֵ:0x00000000�����:32
 �Ĵ���˵��: ĩ�ε���������Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lsreq : 32; /* bit[0-31]: ����������Ʋ���DMA last single ��������
                                                ��д�üĴ���ʱ��
                                                0����Ӱ�죻
                                                1������DMA last single �������󣬵��������ʱ�üĴ����е���Ӧλ�����㡣
                                                �����üĴ���ʱ��
                                                0����Ӧ����������δ����last single ��������
                                                1����Ӧ���������跢��last single�������� */
    } reg;
} SOC_DMAC_LSREQ_UNION;
#endif
#define SOC_DMAC_LSREQ_lsreq_START  (0)
#define SOC_DMAC_LSREQ_lsreq_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_BREQ_UNION
 �ṹ˵��  : BREQ �Ĵ����ṹ���塣��ַƫ����:0x668����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͻ����������Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  breq : 32; /* bit[0-31]: ����������Ʋ���DMA burst ��������
                                               ��д�üĴ���ʱ��
                                               0����Ӱ�죻
                                               1������DMA burst �������󣬵��������ʱ�üĴ����е���Ӧλ�����㡣
                                               �����üĴ���ʱ��
                                               0����Ӧ����������δ����burst ��������
                                               1����Ӧ���������跢��burst �������� */
    } reg;
} SOC_DMAC_BREQ_UNION;
#endif
#define SOC_DMAC_BREQ_breq_START  (0)
#define SOC_DMAC_BREQ_breq_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_LBREQ_UNION
 �ṹ˵��  : LBREQ �Ĵ����ṹ���塣��ַƫ����:0x66C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ĩ��ͻ����������Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lbreq : 32; /* bit[0-31]: ����������Ʋ���DMA last burst ��������
                                                ��д�üĴ���ʱ��
                                                0����Ӱ�죻
                                                1������DMA last burst �������󣬵��������ʱ�üĴ����е���Ӧλ�����㡣
                                                �����üĴ���ʱ��
                                                0����Ӧ����������δ����last burst ��������
                                                1����Ӧ���������跢��last burst�������� */
    } reg;
} SOC_DMAC_LBREQ_UNION;
#endif
#define SOC_DMAC_LBREQ_lbreq_START  (0)
#define SOC_DMAC_LBREQ_lbreq_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_FREQ_UNION
 �ṹ˵��  : FREQ �Ĵ����ṹ���塣��ַƫ����:0x670����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������������Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  freq : 32; /* bit[0-31]: ����������Ʋ���DMA flush ��������
                                               ��д�üĴ���ʱ��
                                               0����Ӱ�죻
                                               1������DMA flush �������󣬵��������ʱ�üĴ����е���Ӧλ�����㡣
                                               �����üĴ���ʱ��
                                               0����Ӧ����������δ����flush ��������
                                               1����Ӧ���������跢�� flush �������� */
    } reg;
} SOC_DMAC_FREQ_UNION;
#endif
#define SOC_DMAC_FREQ_freq_START  (0)
#define SOC_DMAC_FREQ_freq_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_LFREQ_UNION
 �ṹ˵��  : LFREQ �Ĵ����ṹ���塣��ַƫ����:0x674����ֵ:0x00000000�����:32
 �Ĵ���˵��: ĩ��������������Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lfreq : 32; /* bit[0-31]: ����������Ʋ���DMA last flush ��������
                                                ��д�üĴ���ʱ��
                                                0����Ӱ�죻
                                                1������DMA last flush �������󣬵��������ʱ�üĴ����е���Ӧλ�����㡣
                                                �����üĴ���ʱ��
                                                0����Ӧ����������δ����last flush ��������
                                                1����Ӧ���������跢��last flush �������� */
    } reg;
} SOC_DMAC_LFREQ_UNION;
#endif
#define SOC_DMAC_LFREQ_lfreq_START  (0)
#define SOC_DMAC_LFREQ_lfreq_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_CH_PRI_UNION
 �ṹ˵��  : CH_PRI �Ĵ����ṹ���塣��ַƫ����:0x688����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���ȼ����ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch0_pri  : 2;  /* bit[0-1]  : ͨ��0���ȼ�ģʽ���üĴ�����
                                                    2'b00��0���ȼ�����ߣ���
                                                    2'b01��1���ȼ���
                                                    2'b10��2���ȼ���
                                                    2'b11��3���ȼ�����ͣ��� */
        unsigned int  ch1_pri  : 2;  /* bit[2-3]  : ͨ��1���ȼ�ģʽ���üĴ�����
                                                    2'b00��0���ȼ�����ߣ���
                                                    2'b01��1���ȼ���
                                                    2'b10��2���ȼ���
                                                    2'b11��3���ȼ�����ͣ��� */
        unsigned int  ch2_pri  : 2;  /* bit[4-5]  : ͨ��2���ȼ�ģʽ���üĴ�����
                                                    2'b00��0���ȼ�����ߣ���
                                                    2'b01��1���ȼ���
                                                    2'b10��2���ȼ���
                                                    2'b11��3���ȼ�����ͣ��� */
        unsigned int  ch3_pri  : 2;  /* bit[6-7]  : ͨ��3���ȼ�ģʽ���üĴ�����
                                                    2'b00��0���ȼ�����ߣ���
                                                    2'b01��1���ȼ���
                                                    2'b10��2���ȼ���
                                                    2'b11��3���ȼ�����ͣ��� */
        unsigned int  ch4_pri  : 2;  /* bit[8-9]  : ͨ��4���ȼ�ģʽ���üĴ�����
                                                    2'b00��0���ȼ�����ߣ���
                                                    2'b01��1���ȼ���
                                                    2'b10��2���ȼ���
                                                    2'b11��3���ȼ�����ͣ��� */
        unsigned int  ch5_pri  : 2;  /* bit[10-11]: ͨ��5���ȼ�ģʽ���üĴ�����
                                                    2'b00��0���ȼ�����ߣ���
                                                    2'b01��1���ȼ���
                                                    2'b10��2���ȼ���
                                                    2'b11��3���ȼ�����ͣ��� */
        unsigned int  ch6_pri  : 2;  /* bit[12-13]: ͨ��6���ȼ�ģʽ���üĴ�����
                                                    2'b00��0���ȼ�����ߣ���
                                                    2'b01��1���ȼ���
                                                    2'b10��2���ȼ���
                                                    2'b11��3���ȼ�����ͣ��� */
        unsigned int  ch7_pri  : 2;  /* bit[14-15]: ͨ��7���ȼ�ģʽ���üĴ�����
                                                    2'b00��0���ȼ�����ߣ���
                                                    2'b01��1���ȼ���
                                                    2'b10��2���ȼ���
                                                    2'b11��3���ȼ�����ͣ��� */
        unsigned int  ch8_pri  : 2;  /* bit[16-17]: ͨ��8���ȼ�ģʽ���üĴ�����
                                                    2'b00��0���ȼ�����ߣ���
                                                    2'b01��1���ȼ���
                                                    2'b10��2���ȼ���
                                                    2'b11��3���ȼ�����ͣ��� */
        unsigned int  ch9_pri  : 2;  /* bit[18-19]: ͨ��9���ȼ�ģʽ���üĴ�����
                                                    2'b00��0���ȼ�����ߣ���
                                                    2'b01��1���ȼ���
                                                    2'b10��2���ȼ���
                                                    2'b11��3���ȼ�����ͣ��� */
        unsigned int  ch10_pri : 2;  /* bit[20-21]: ͨ��10���ȼ�ģʽ���üĴ�����
                                                    2'b00��0���ȼ�����ߣ���
                                                    2'b01��1���ȼ���
                                                    2'b10��2���ȼ���
                                                    2'b11��3���ȼ�����ͣ��� */
        unsigned int  ch11_pri : 2;  /* bit[22-23]: ͨ��11���ȼ�ģʽ���üĴ�����
                                                    2'b00��0���ȼ�����ߣ���
                                                    2'b01��1���ȼ���
                                                    2'b10��2���ȼ���
                                                    2'b11��3���ȼ�����ͣ��� */
        unsigned int  ch12_pri : 2;  /* bit[24-25]: ͨ��12���ȼ�ģʽ���üĴ�����
                                                    2'b00��0���ȼ�����ߣ���
                                                    2'b01��1���ȼ���
                                                    2'b10��2���ȼ���
                                                    2'b11��3���ȼ�����ͣ��� */
        unsigned int  ch13_pri : 2;  /* bit[26-27]: ͨ��13���ȼ�ģʽ���üĴ�����
                                                    2'b00��0���ȼ�����ߣ���
                                                    2'b01��1���ȼ���
                                                    2'b10��2���ȼ���
                                                    2'b11��3���ȼ�����ͣ��� */
        unsigned int  ch14_pri : 2;  /* bit[28-29]: ͨ��14���ȼ�ģʽ���üĴ�����
                                                    2'b00��0���ȼ�����ߣ���
                                                    2'b01��1���ȼ���
                                                    2'b10��2���ȼ���
                                                    2'b11��3���ȼ�����ͣ��� */
        unsigned int  ch15_pri : 2;  /* bit[30-31]: ͨ��15���ȼ�ģʽ���üĴ�����
                                                    2'b00��0���ȼ�����ߣ���
                                                    2'b01��1���ȼ���
                                                    2'b10��2���ȼ���
                                                    2'b11��3���ȼ�����ͣ��� */
    } reg;
} SOC_DMAC_CH_PRI_UNION;
#endif
#define SOC_DMAC_CH_PRI_ch0_pri_START   (0)
#define SOC_DMAC_CH_PRI_ch0_pri_END     (1)
#define SOC_DMAC_CH_PRI_ch1_pri_START   (2)
#define SOC_DMAC_CH_PRI_ch1_pri_END     (3)
#define SOC_DMAC_CH_PRI_ch2_pri_START   (4)
#define SOC_DMAC_CH_PRI_ch2_pri_END     (5)
#define SOC_DMAC_CH_PRI_ch3_pri_START   (6)
#define SOC_DMAC_CH_PRI_ch3_pri_END     (7)
#define SOC_DMAC_CH_PRI_ch4_pri_START   (8)
#define SOC_DMAC_CH_PRI_ch4_pri_END     (9)
#define SOC_DMAC_CH_PRI_ch5_pri_START   (10)
#define SOC_DMAC_CH_PRI_ch5_pri_END     (11)
#define SOC_DMAC_CH_PRI_ch6_pri_START   (12)
#define SOC_DMAC_CH_PRI_ch6_pri_END     (13)
#define SOC_DMAC_CH_PRI_ch7_pri_START   (14)
#define SOC_DMAC_CH_PRI_ch7_pri_END     (15)
#define SOC_DMAC_CH_PRI_ch8_pri_START   (16)
#define SOC_DMAC_CH_PRI_ch8_pri_END     (17)
#define SOC_DMAC_CH_PRI_ch9_pri_START   (18)
#define SOC_DMAC_CH_PRI_ch9_pri_END     (19)
#define SOC_DMAC_CH_PRI_ch10_pri_START  (20)
#define SOC_DMAC_CH_PRI_ch10_pri_END    (21)
#define SOC_DMAC_CH_PRI_ch11_pri_START  (22)
#define SOC_DMAC_CH_PRI_ch11_pri_END    (23)
#define SOC_DMAC_CH_PRI_ch12_pri_START  (24)
#define SOC_DMAC_CH_PRI_ch12_pri_END    (25)
#define SOC_DMAC_CH_PRI_ch13_pri_START  (26)
#define SOC_DMAC_CH_PRI_ch13_pri_END    (27)
#define SOC_DMAC_CH_PRI_ch14_pri_START  (28)
#define SOC_DMAC_CH_PRI_ch14_pri_END    (29)
#define SOC_DMAC_CH_PRI_ch15_pri_START  (30)
#define SOC_DMAC_CH_PRI_ch15_pri_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_CH_STAT_UNION
 �ṹ˵��  : CH_STAT �Ĵ����ṹ���塣��ַƫ����:0x690����ֵ:0x00000000�����:32
 �Ĵ���˵��: ȫ��DMA״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_stat  : 16; /* bit[0-15] : DMACͨ��ʹ�ܼĴ�����
                                                    1:��Ӧ��DMACͨ��Ŀǰ���ڹ�����
                                                    0:��Ӧ��DMACͨ��Ŀǰû�й����� */
        unsigned int  reserved : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_DMAC_CH_STAT_UNION;
#endif
#define SOC_DMAC_CH_STAT_ch_stat_START   (0)
#define SOC_DMAC_CH_STAT_ch_stat_END     (15)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_SEC_CTRL_UNION
 �ṹ˵��  : SEC_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0694����ֵ:0x00000002�����:32
 �Ĵ���˵��: DMAȫ�ְ�ȫ���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  global_sec    : 1;  /* bit[0]   : ȫ�ּĴ�����ȫ����(ֻ��ͨ����ȫ��������)��
                                                        0��CH_PRI��DMA_CTRLֻ�а�ȫ�������ܷ��ʣ�
                                                        1��CH_PRI��DMA_CTRL�����ܰ�ȫ�ͷǰ�ȫ�������� */
        unsigned int  intr_sec_ctrl : 1;  /* bit[1]   : �жϰ�ȫ����(ֻ��ͨ����ȫ��������)��
                                                        0����ȫ����ֻ�ܷ��ʰ�ȫͨ�����ж���Ϣ����ȫ�ж�ͨ��dma_intr�ϱ����ǰ�ȫ�ж�ͨ��dma_intr_ns�ϱ���
                                                        1����ȫ�����ܷ�������ͨ������Ϣ����ȫ�жϺͷǰ�ȫ�ж϶���ͨ��dma_intr�ϱ���dma_intr_nsֻ�ϱ��ǰ�ȫ�ж� */
        unsigned int  reserved      : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_DMAC_SEC_CTRL_UNION;
#endif
#define SOC_DMAC_SEC_CTRL_global_sec_START     (0)
#define SOC_DMAC_SEC_CTRL_global_sec_END       (0)
#define SOC_DMAC_SEC_CTRL_intr_sec_ctrl_START  (1)
#define SOC_DMAC_SEC_CTRL_intr_sec_ctrl_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_DMA_CTRL_UNION
 �ṹ˵��  : DMA_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0698����ֵ:0x00000000�����:32
 �Ĵ���˵��: DMAȫ�ֿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  halt_ack  : 1;  /* bit[0]   : DMA����HALT״̬ȷ�ϼĴ�����
                                                    ����
                                                    1��DMA�Ѿ�������HALT״̬
                                                    0��DMA��δ����HALT״̬
                                                    д��
                                                    1�����DMA HALT״̬
                                                    0����Ӱ�죬����ԭֵ */
        unsigned int  halt_req  : 1;  /* bit[1]   : DMA HALT�������üĴ�����
                                                    ����
                                                    1��DMA�Ѿ�������HALT���󵫻�δ����HALT״̬
                                                    0��DMA��û����HALT�������DMA�Ѿ�������HALT״̬
                                                    д��
                                                    1������DMA HALT����
                                                    0����Ӱ�죬����ԭֵ */
        unsigned int  reserved_0: 2;  /* bit[2-3] : ���� */
        unsigned int  conf_out4 : 1;  /* bit[4]   : ��Outstanding���궨��Ϊ8ʱ��
                                                    1��Outstanding��Ϊ4��
                                                    0��Outstanding��Ϊ8��
                                                    ��Outstanding���궨��Ϊ4ʱ����λ����д������λ0
                                                    ע�⣺�޸�Outstanding����ȴ�����ͨ������IDLE״̬ʱ�Ż���Ч����ӦCH_STAT�Ĵ���ȫΪ0�������޸���Ч */
        unsigned int  reserved_1: 27; /* bit[5-31]: ������ */
    } reg;
} SOC_DMAC_DMA_CTRL_UNION;
#endif
#define SOC_DMAC_DMA_CTRL_halt_ack_START   (0)
#define SOC_DMAC_DMA_CTRL_halt_ack_END     (0)
#define SOC_DMAC_DMA_CTRL_halt_req_START   (1)
#define SOC_DMAC_DMA_CTRL_halt_req_END     (1)
#define SOC_DMAC_DMA_CTRL_conf_out4_START  (4)
#define SOC_DMAC_DMA_CTRL_conf_out4_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_CX_CURR_CNT1_UNION
 �ṹ˵��  : CX_CURR_CNT1 �Ĵ����ṹ���塣��ַƫ����:0x0700+0x10*(cn)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͨ��X����ά����ʣ��size״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  curr_c_count : 16; /* bit[0-15] : ͨ��X��ǰ��ά����ʣ���Frame���� */
        unsigned int  reserved     : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_DMAC_CX_CURR_CNT1_UNION;
#endif
#define SOC_DMAC_CX_CURR_CNT1_curr_c_count_START  (0)
#define SOC_DMAC_CX_CURR_CNT1_curr_c_count_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_CX_CURR_CNT0_UNION
 �ṹ˵��  : CX_CURR_CNT0 �Ĵ����ṹ���塣��ַƫ����:0x0704+0x10*(cn)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͨ��X��һ����ά����ʣ��size״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  curr_a_count : 16; /* bit[0-15] : ͨ��X��ǰһά����ʣ���Byte���� */
        unsigned int  curr_b_count : 16; /* bit[16-31]: ͨ��X��ǰ��ά����ʣ���Array������ */
    } reg;
} SOC_DMAC_CX_CURR_CNT0_UNION;
#endif
#define SOC_DMAC_CX_CURR_CNT0_curr_a_count_START  (0)
#define SOC_DMAC_CX_CURR_CNT0_curr_a_count_END    (15)
#define SOC_DMAC_CX_CURR_CNT0_curr_b_count_START  (16)
#define SOC_DMAC_CX_CURR_CNT0_curr_b_count_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_CX_CURR_SRC_ADDR_UNION
 �ṹ˵��  : CX_CURR_SRC_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0708+0x10*(cn)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͨ��X��Դ��ַ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  curr_src_addr : 32; /* bit[0-31]: ͨ��X��ǰ���ڴ����Դ��ַ */
    } reg;
} SOC_DMAC_CX_CURR_SRC_ADDR_UNION;
#endif
#define SOC_DMAC_CX_CURR_SRC_ADDR_curr_src_addr_START  (0)
#define SOC_DMAC_CX_CURR_SRC_ADDR_curr_src_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_CX_CURR_DES_ADDR_UNION
 �ṹ˵��  : CX_CURR_DES_ADDR �Ĵ����ṹ���塣��ַƫ����:0x070C+0x10*(cn)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͨ��X��Ŀ�ĵ�ַ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  curr_des_addr : 32; /* bit[0-31]: ͨ��X��ǰ���ڴ����Ŀ�ĵ�ַ */
    } reg;
} SOC_DMAC_CX_CURR_DES_ADDR_UNION;
#endif
#define SOC_DMAC_CX_CURR_DES_ADDR_curr_des_addr_START  (0)
#define SOC_DMAC_CX_CURR_DES_ADDR_curr_des_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_CX_LLI_UNION
 �ṹ˵��  : CX_LLI �Ĵ����ṹ���塣��ַƫ����:0x0800+0x40*(cn)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͨ��X�������ַ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  chain_en : 2;  /* bit[0-1] : ͨ��������ʹ��:
                                                   00����������ʹ����Ч��ͨ������ʹ����Ч
                                                   01����������ʹ����Ч��ͨ������ʹ����Ч
                                                   10����������ʹ����Ч��ͨ������ʹ����Ч
                                                   11��reserved�����ø�reservedֵ���ϱ����ô����жϡ� */
        unsigned int  reserved : 3;  /* bit[2-4] : ������ */
        unsigned int  lli      : 27; /* bit[5-31]: ͨ��X����һ������ڵ��ַ��[31:5]λ�������ַʼ����256-bit���롣
                                                   ��ͨ������ʹ����Чʱ��[11:8]��ʾ���ӵ���һ��ͨ����id�� */
    } reg;
} SOC_DMAC_CX_LLI_UNION;
#endif
#define SOC_DMAC_CX_LLI_chain_en_START  (0)
#define SOC_DMAC_CX_LLI_chain_en_END    (1)
#define SOC_DMAC_CX_LLI_lli_START       (5)
#define SOC_DMAC_CX_LLI_lli_END         (31)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_CX_BINDX_UNION
 �ṹ˵��  : CX_BINDX �Ĵ����ṹ���塣��ַƫ����:0x0804+0x40*(cn)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͨ��X�Ķ�ά��ַƫ�������üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  des_bindx : 15; /* bit[0-14] : ��άĿ�ĵ�ַƫ�������ã�ָʾƫ�Ƶľ���ֵ������λ��bit15ָʾ */
        unsigned int  des_bsign : 1;  /* bit[15]   : ��άĿ�ĵ�ַƫ�Ʒ���λ��
                                                     1����
                                                     0���� */
        unsigned int  src_bindx : 15; /* bit[16-30]: ��άԴ��ַƫ�������ã�ָʾƫ�Ƶľ���ֵ������λ��bit31ָʾ */
        unsigned int  src_bsign : 1;  /* bit[31]   : ��άԴ��ַƫ�Ʒ���λ��
                                                     1����
                                                     0���� */
    } reg;
} SOC_DMAC_CX_BINDX_UNION;
#endif
#define SOC_DMAC_CX_BINDX_des_bindx_START  (0)
#define SOC_DMAC_CX_BINDX_des_bindx_END    (14)
#define SOC_DMAC_CX_BINDX_des_bsign_START  (15)
#define SOC_DMAC_CX_BINDX_des_bsign_END    (15)
#define SOC_DMAC_CX_BINDX_src_bindx_START  (16)
#define SOC_DMAC_CX_BINDX_src_bindx_END    (30)
#define SOC_DMAC_CX_BINDX_src_bsign_START  (31)
#define SOC_DMAC_CX_BINDX_src_bsign_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_CX_CINDX_UNION
 �ṹ˵��  : CX_CINDX �Ĵ����ṹ���塣��ַƫ����:0x0808+0x40*(cn)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͨ��X����ά��ַƫ�������üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  des_cindx : 15; /* bit[0-14] : ��άĿ�ĵ�ַƫ�������ã�ָʾƫ�Ƶľ���ֵ������λ��bit15ָʾ */
        unsigned int  des_csign : 1;  /* bit[15]   : ��άĿ�ĵ�ַƫ�Ʒ���λ��
                                                     1����
                                                     0���� */
        unsigned int  src_cindx : 15; /* bit[16-30]: ��άԴ��ַƫ�������ã�ָʾƫ�Ƶľ���ֵ������λ��bit31ָʾ */
        unsigned int  src_csign : 1;  /* bit[31]   : ��άԴ��ַƫ�Ʒ���λ��
                                                     1����
                                                     0���� */
    } reg;
} SOC_DMAC_CX_CINDX_UNION;
#endif
#define SOC_DMAC_CX_CINDX_des_cindx_START  (0)
#define SOC_DMAC_CX_CINDX_des_cindx_END    (14)
#define SOC_DMAC_CX_CINDX_des_csign_START  (15)
#define SOC_DMAC_CX_CINDX_des_csign_END    (15)
#define SOC_DMAC_CX_CINDX_src_cindx_START  (16)
#define SOC_DMAC_CX_CINDX_src_cindx_END    (30)
#define SOC_DMAC_CX_CINDX_src_csign_START  (31)
#define SOC_DMAC_CX_CINDX_src_csign_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_CX_CNT1_UNION
 �ṹ˵��  : CX_CNT1 �Ĵ����ṹ���塣��ַƫ����:0x080C+0x40*(cn)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͨ��X�Ĵ��䳤��1���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  c_count  : 16; /* bit[0-15] : ��ά���䳤������(1��65535)
                                                    ��һ��Block������Frame�ĸ�����0��ʾû����ά���䡣Frame�ĸ���Ϊc_count�ĸ�����1�� */
        unsigned int  reserved : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_DMAC_CX_CNT1_UNION;
#endif
#define SOC_DMAC_CX_CNT1_c_count_START   (0)
#define SOC_DMAC_CX_CNT1_c_count_END     (15)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_CX_CNT0_UNION
 �ṹ˵��  : CX_CNT0 �Ĵ����ṹ���塣��ַƫ����:0x0810+0x40*(cn)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͨ��X�Ĵ��䳤�����üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a_count : 16; /* bit[0-15] : һά���䳤������(1��65535)
                                                   ��һ��Array��������Сbytes��Ŀ��Acount����Ϊ0�ᴥ�����ô����жϡ� */
        unsigned int  b_count : 16; /* bit[16-31]: ��ά���䳤������(1��65535)
                                                   ��һ��Frame������Array�ĸ�����Frame��array����Ϊb_count��ֵ��1�� */
    } reg;
} SOC_DMAC_CX_CNT0_UNION;
#endif
#define SOC_DMAC_CX_CNT0_a_count_START  (0)
#define SOC_DMAC_CX_CNT0_a_count_END    (15)
#define SOC_DMAC_CX_CNT0_b_count_START  (16)
#define SOC_DMAC_CX_CNT0_b_count_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_CX_SRC_ADDR_UNION
 �ṹ˵��  : CX_SRC_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0814+0x40*(cn)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͨ��X��Դ��ַ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  src_addr : 32; /* bit[0-31]: ͨ��X��Դ��ַ */
    } reg;
} SOC_DMAC_CX_SRC_ADDR_UNION;
#endif
#define SOC_DMAC_CX_SRC_ADDR_src_addr_START  (0)
#define SOC_DMAC_CX_SRC_ADDR_src_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_CX_DES_ADDR_UNION
 �ṹ˵��  : CX_DES_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0818+0x40*(cn)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͨ��X��Ŀ�ĵ�ַ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  des_addr : 32; /* bit[0-31]: ͨ��X��Ŀ�ĵ�ַ */
    } reg;
} SOC_DMAC_CX_DES_ADDR_UNION;
#endif
#define SOC_DMAC_CX_DES_ADDR_des_addr_START  (0)
#define SOC_DMAC_CX_DES_ADDR_des_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_CX_CONFIG_UNION
 �ṹ˵��  : CX_CONFIG �Ĵ����ṹ���塣��ַƫ����:0x081C+0x40*(cn)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͨ��X�����üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_en     : 1;  /* bit[0]    : ��ǰͨ��ʹ�ܿ��ƣ�
                                                     ��д�üĴ��������Ƶ�ǰͨ�������У�
                                                     0��ͨ������/��λ��
                                                     1��ͨ��ʹ�ܡ�
                                                     �����üĴ�������ʾ��ǰͨ����״̬��
                                                     0��ͨ��ֹͣ�У�
                                                     1��ͨ��������(������ʹ��ʱ��ͨ��һֱʹ��)�� */
        unsigned int  itc_en    : 1;  /* bit[1]    : ����ڵ㴫������ж�ʹ�ܡ���λ�������õ�ǰ����ڵ㴫����ɺ��Ƿ񴥷��ڵ㴫������жϡ�
                                                     0����ǰ����ڵ㴫������Ժ󲻴�������ڵ㴫������жϣ�
                                                     1����ǰ����ڵ㴫������Ժ󴥷�����ڵ㴫������жϣ��������һ���ڵ㴫������Ժ�����ڵ㴫������жϲ��ᱻ������
                                                     ע�⣺���۸�bit����Ϊ0��1��ͨ����������ڵ㴫������Ժ�����ϱ�ͨ����������жϡ� */
        unsigned int  flow_ctrl : 2;  /* bit[2-3]  : �����ƺʹ������͡�
                                                     00���洢���ʹ洢��֮�䴫�䣬DMAC���أ�
                                                     01���洢��������֮�䴫�䣬DMAC���أ�
                                                     10���洢��������֮�䴫�䣬�������أ�
                                                     11��Reserved������reservedֵ���ϱ����ô����жϡ� */
        unsigned int  peri      : 6;  /* bit[4-9]  : ��������š�����Ǵ洢�����洢������Щλ�������ԡ�Ŀǰ���֧��32��������������bit9Ŀǰ�������ã�ʵ��ʹ�õ�Ϊbit8:bit4���ڲ�ͬ����������궨���������棬peri����Чֵ����������������Ч��Ŀ�仯������궨��ֻʹ��16������������peri��0��15��ֵ����Ч�ģ�����λ��ֵ�������ã����ǻᱻ���Ե��� */
        unsigned int  reserved_0: 2;  /* bit[10-11]: ������ */
        unsigned int  dw        : 3;  /* bit[12-14]: Ŀ�����ݿ�ȡ�
                                                     000��8bit
                                                     001��16bit
                                                     010��32bit
                                                     011��64bit
                                                     100��128bit
                                                     101��256bit
                                                     110��111��reserved */
        unsigned int  reserved_1: 1;  /* bit[15]   : ������ */
        unsigned int  sw        : 3;  /* bit[16-18]: Դ���ݿ�ȡ�
                                                     000��8bit
                                                     001��16bit
                                                     010��32bit
                                                     011��64bit
                                                     100��128bit
                                                     101��256bit
                                                     110��111��reserved */
        unsigned int  reserved_2: 1;  /* bit[19]   : ������ */
        unsigned int  dl        : 4;  /* bit[20-23]: Ŀ�Ĵ���burst���ȡ�
                                                     0000��burst lengthΪ1
                                                     0001��burst lengthΪ2
                                                     ��
                                                     1111��burst lengthΪ16 */
        unsigned int  sl        : 4;  /* bit[24-27]: Դ����burst���ȡ�
                                                     0000��burst lengthΪ1
                                                     0001��burst lengthΪ2
                                                     ��
                                                     1111��burst lengthΪ16 */
        unsigned int  dmode     : 1;  /* bit[28]   : Ŀ�ĵ�ַ�ĵ���ģʽ��
                                                     0:A-syncģʽ����ά�ĵ�ַƫ����һ��frame�����һ��array���׵�ַ����һ��frame�ĵ�һ��array���׵�ַ�����
                                                     1:AB_syncģʽ����ά�ĵ�ַƫ����һ��frame�ĵ�һ��array���׵�ַ����һ��frame�ĵ�һ��array���׵�ַ�ļ���� */
        unsigned int  smode     : 1;  /* bit[29]   : Դ��ַ�ĵ���ģʽ��
                                                     0:A-syncģʽ����ά�ĵ�ַƫ����һ��frame�����һ��array���׵�ַ����һ��frame�ĵ�һ��array���׵�ַ�����
                                                     1:AB_syncģʽ����ά�ĵ�ַƫ����һ��frame�ĵ�һ��array���׵�ַ����һ��frame�ĵ�һ��array���׵�ַ�ļ���� */
        unsigned int  di        : 1;  /* bit[30]   : Ŀ�ĵ�ַ�������á�
                                                     0��Ŀ�ĵ�ַ��������
                                                     1��Ŀ�ĵ�ַÿ��һ�����͵���һ�Ρ�
                                                     Ŀ���豸Ϊ����ʱĿ�ĵ�ַ��������Ŀ���豸Ϊ�洢��ʱĿ�ĵ�ַ������ */
        unsigned int  si        : 1;  /* bit[31]   : Դ��ַ�������á�
                                                     0��Դ��ַ��������
                                                     1��Դ��ַÿ��һ�����͵���һ�Ρ�
                                                     Դ�豸Ϊ����ʱԴ��ַ��������Դ�豸Ϊ�洢��ʱԴ��ַ������ */
    } reg;
} SOC_DMAC_CX_CONFIG_UNION;
#endif
#define SOC_DMAC_CX_CONFIG_ch_en_START      (0)
#define SOC_DMAC_CX_CONFIG_ch_en_END        (0)
#define SOC_DMAC_CX_CONFIG_itc_en_START     (1)
#define SOC_DMAC_CX_CONFIG_itc_en_END       (1)
#define SOC_DMAC_CX_CONFIG_flow_ctrl_START  (2)
#define SOC_DMAC_CX_CONFIG_flow_ctrl_END    (3)
#define SOC_DMAC_CX_CONFIG_peri_START       (4)
#define SOC_DMAC_CX_CONFIG_peri_END         (9)
#define SOC_DMAC_CX_CONFIG_dw_START         (12)
#define SOC_DMAC_CX_CONFIG_dw_END           (14)
#define SOC_DMAC_CX_CONFIG_sw_START         (16)
#define SOC_DMAC_CX_CONFIG_sw_END           (18)
#define SOC_DMAC_CX_CONFIG_dl_START         (20)
#define SOC_DMAC_CX_CONFIG_dl_END           (23)
#define SOC_DMAC_CX_CONFIG_sl_START         (24)
#define SOC_DMAC_CX_CONFIG_sl_END           (27)
#define SOC_DMAC_CX_CONFIG_dmode_START      (28)
#define SOC_DMAC_CX_CONFIG_dmode_END        (28)
#define SOC_DMAC_CX_CONFIG_smode_START      (29)
#define SOC_DMAC_CX_CONFIG_smode_END        (29)
#define SOC_DMAC_CX_CONFIG_di_START         (30)
#define SOC_DMAC_CX_CONFIG_di_END           (30)
#define SOC_DMAC_CX_CONFIG_si_START         (31)
#define SOC_DMAC_CX_CONFIG_si_END           (31)


/*****************************************************************************
 �ṹ��    : SOC_DMAC_CX_AXI_CONF_UNION
 �ṹ˵��  : CX_AXI_CONF �Ĵ����ṹ���塣��ַƫ����:0x0820+0x40*(cn)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͨ��X��AXI����������üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  aruser   : 5;  /* bit[0-4]  : bit[4]��DMAC���߼���һ���Բ�������
                                                    0��DMAC��SYS_BUS�������ж�һ���Բ�����
                                                    1��DMAC��CCI_BUS�����ж�һ���Բ�����
                                                    bit[3:0]:DMACͨ���ſ���
                                                    0-15����ʾDMAC 16��ͨ�� */
        unsigned int  arprot   : 3;  /* bit[5-7]  : ����AXI���߶���������ͣ���ѭAXI����Э�顣��awprot[18]&arprot[6]=1��ʱ�򣬱�ʾ��ǰDMA�߼�ͨ��Ϊ�ǰ�ȫ���������Ϊ��ȫ��arprotֻ�а�ȫ���䡣 */
        unsigned int  arcache  : 4;  /* bit[8-11] : ����AXI���߶�����cache�����ͣ���ѭAXI����Э�� */
        unsigned int  awuser   : 5;  /* bit[12-16]: bit[16]��DMAC���߼�дһ���Բ�������
                                                    0��DMAC��SYS_BUS��������дһ���Բ�����
                                                    1��DMAC��CCI_BUS������дһ���Բ�����
                                                    bit[15:12]:DMACͨ���ſ���
                                                    0-15����ʾDMAC 16��ͨ�� */
        unsigned int  awprot   : 3;  /* bit[17-19]: ����AXI����д��������ͣ���ѭAXI����Э�顣��awprot[18]&arprot[6]=1��ʱ�򣬱�ʾ��ǰDMA�߼�ͨ��Ϊ�ǰ�ȫ���������Ϊ��ȫ��awprotֻ�а�ȫ���䡣 */
        unsigned int  awcache  : 4;  /* bit[20-23]: ����AXI����д����cache�����ͣ���ѭAXI����Э�� */
        unsigned int  reserved : 8;  /* bit[24-31]: ������ */
    } reg;
} SOC_DMAC_CX_AXI_CONF_UNION;
#endif
#define SOC_DMAC_CX_AXI_CONF_aruser_START    (0)
#define SOC_DMAC_CX_AXI_CONF_aruser_END      (4)
#define SOC_DMAC_CX_AXI_CONF_arprot_START    (5)
#define SOC_DMAC_CX_AXI_CONF_arprot_END      (7)
#define SOC_DMAC_CX_AXI_CONF_arcache_START   (8)
#define SOC_DMAC_CX_AXI_CONF_arcache_END     (11)
#define SOC_DMAC_CX_AXI_CONF_awuser_START    (12)
#define SOC_DMAC_CX_AXI_CONF_awuser_END      (16)
#define SOC_DMAC_CX_AXI_CONF_awprot_START    (17)
#define SOC_DMAC_CX_AXI_CONF_awprot_END      (19)
#define SOC_DMAC_CX_AXI_CONF_awcache_START   (20)
#define SOC_DMAC_CX_AXI_CONF_awcache_END     (23)






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

#endif /* end of soc_dmac_interface.h */
