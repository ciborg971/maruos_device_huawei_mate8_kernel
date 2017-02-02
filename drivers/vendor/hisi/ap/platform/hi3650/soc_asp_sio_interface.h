/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_asp_sio_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:18:16
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_ASP_SIO.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_ASP_SIO_INTERFACE_H__
#define __SOC_ASP_SIO_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) register_define
 ****************************************************************************/
/* �Ĵ���˵�����汾�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_SIO_SIO_VERSION_UNION */
#define SOC_ASP_SIO_SIO_VERSION_ADDR(base)            ((base) + (0x03C))

/* �Ĵ���˵����ģʽ�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_SIO_SIO_MODE_UNION */
#define SOC_ASP_SIO_SIO_MODE_ADDR(base)               ((base) + (0x040))

/* �Ĵ���˵�����ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_SIO_SIO_INTSTATUS_UNION */
#define SOC_ASP_SIO_SIO_INTSTATUS_ADDR(base)          ((base) + (0x044))

/* �Ĵ���˵�����ж�����Ĵ���.
   λ����UNION�ṹ:  SOC_ASP_SIO_SIO_INTCLR_UNION */
#define SOC_ASP_SIO_SIO_INTCLR_ADDR(base)             ((base) + (0x048))

/* �Ĵ���˵����I2Sģʽ�����������ݷ��ͼĴ���
   λ����UNION�ṹ:  SOC_ASP_SIO_SIO_I2S_LEFT_XD_UNION */
#define SOC_ASP_SIO_SIO_I2S_LEFT_XD_ADDR(base)        ((base) + (0x04C))

/* �Ĵ���˵����I2Sģʽ�����������ݷ��ͼĴ���/PCMģʽ�µ����ݷ��ͼĴ���SIO_PCM_XD
   λ����UNION�ṹ:  SOC_ASP_SIO_SIO_I2S_RIGHT_XD_UNION */
#define SOC_ASP_SIO_SIO_I2S_RIGHT_XD_ADDR(base)       ((base) + (0x050))

/* �Ĵ���˵����I2Sģʽ�����������ݽ��ռĴ���
   λ����UNION�ṹ:  SOC_ASP_SIO_SIO_I2S_LEFT_RD_UNION */
#define SOC_ASP_SIO_SIO_I2S_LEFT_RD_ADDR(base)        ((base) + (0x054))

/* �Ĵ���˵����I2Sģʽ�����������ݽ��ռĴ���/PCMģʽ�½������ݼĴ���
   λ����UNION�ṹ:  SOC_ASP_SIO_SIO_I2S_RIGHT_RD_UNION */
#define SOC_ASP_SIO_SIO_I2S_RIGHT_RD_ADDR(base)       ((base) + (0x058))

/* �Ĵ���˵�������ƼĴ���ʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_ASP_SIO_SIO_CT_SET_UNION */
#define SOC_ASP_SIO_SIO_CT_SET_ADDR(base)             ((base) + (0x05C))

/* �Ĵ���˵�������ƼĴ�������Ĵ���
   λ����UNION�ṹ:  SOC_ASP_SIO_SIO_CT_CLR_UNION */
#define SOC_ASP_SIO_SIO_CT_CLR_ADDR(base)             ((base) + (0x060))

/* �Ĵ���˵����SIO����״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_SIO_SIO_RX_STA_UNION */
#define SOC_ASP_SIO_SIO_RX_STA_ADDR(base)             ((base) + (0x068))

/* �Ĵ���˵����SIO����״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_SIO_SIO_TX_STA_UNION */
#define SOC_ASP_SIO_SIO_TX_STA_ADDR(base)             ((base) + (0x06C))

/* �Ĵ���˵�������ݿ�ȼĴ���
   λ����UNION�ṹ:  SOC_ASP_SIO_SIO_DATA_WIDTH_SET_UNION */
#define SOC_ASP_SIO_SIO_DATA_WIDTH_SET_ADDR(base)     ((base) + (0x078))

/* �Ĵ���˵����I2S����������ʼλ�����ÿ��ƼĴ���
   λ����UNION�ṹ:  SOC_ASP_SIO_SIO_I2S_START_POS_UNION */
#define SOC_ASP_SIO_SIO_I2S_START_POS_ADDR(base)      ((base) + (0x07C))

/* �Ĵ���˵����I2S��������������ǰλ��״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_SIO_I2S_POS_FLAG_UNION */
#define SOC_ASP_SIO_I2S_POS_FLAG_ADDR(base)           ((base) + (0x080))

/* �Ĵ���˵������λ���ݷ�����չʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_ASP_SIO_SIO_SIGNED_EXT_UNION */
#define SOC_ASP_SIO_SIO_SIGNED_EXT_ADDR(base)         ((base) + (0x084))

/* �Ĵ���˵����I2S�����������ݺϲ�ʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_ASP_SIO_SIO_I2S_POS_MERGE_EN_UNION */
#define SOC_ASP_SIO_SIO_I2S_POS_MERGE_EN_ADDR(base)   ((base) + (0x088))

/* �Ĵ���˵�����ж����μĴ���
   λ����UNION�ṹ:  SOC_ASP_SIO_SIO_INTMASK_UNION */
#define SOC_ASP_SIO_SIO_INTMASK_ADDR(base)            ((base) + (0x08C))

/* �Ĵ���˵�������պϲ����ݼĴ���
   λ����UNION�ṹ:  SOC_ASP_SIO_SIO_I2S_DUAL_RX_CHN_UNION */
#define SOC_ASP_SIO_SIO_I2S_DUAL_RX_CHN_ADDR(base)    ((base) + (0x0A0))

/* �Ĵ���˵�������ͺϲ����ݼĴ���
   λ����UNION�ṹ:  SOC_ASP_SIO_SIO_I2S_DUAL_TX_CHN_UNION */
#define SOC_ASP_SIO_SIO_I2S_DUAL_TX_CHN_ADDR(base)    ((base) + (0x0C0))





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
                     (1/1) register_define
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_ASP_SIO_SIO_VERSION_UNION
 �ṹ˵��  : SIO_VERSION �Ĵ����ṹ���塣��ַƫ����:0x03C����ֵ:0x00000013�����:32
 �Ĵ���˵��: �汾�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  version  : 8;  /* bit[0-7] : sio�İ汾�� */
        unsigned int  sio_loop : 1;  /* bit[8]   : SIOѭ��������ģʽѡ��
                                                   0������ģʽ��
                                                   1��SIO���ͺͽ������ݻ���ģʽ������SIO���Բ��ԡ��ڸ�ģʽ�£���SIO�Ķ���ӿڴ���SIO���մ�����������SIO���ʹ���������ֱ�������� */
        unsigned int  reserved : 23; /* bit[9-31]: �汾�Ĵ�����������¼SIO�İ汾�źͽ���SIO�� */
    } reg;
} SOC_ASP_SIO_SIO_VERSION_UNION;
#endif
#define SOC_ASP_SIO_SIO_VERSION_version_START   (0)
#define SOC_ASP_SIO_SIO_VERSION_version_END     (7)
#define SOC_ASP_SIO_SIO_VERSION_sio_loop_START  (8)
#define SOC_ASP_SIO_SIO_VERSION_sio_loop_END    (8)


/*****************************************************************************
 �ṹ��    : SOC_ASP_SIO_SIO_MODE_UNION
 �ṹ˵��  : SIO_MODE �Ĵ����ṹ���塣��ַƫ����:0x040����ֵ:0x00000000�����:32
 �Ĵ���˵��: ģʽ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sio_mode   : 1;  /* bit[0]   : PCM/I2Sģʽѡ��
                                                     0��I2Sģʽ��
                                                     1��PCMģʽ�� */
        unsigned int  pcm_mode   : 1;  /* bit[1]   : PCMʱ��ģʽ��
                                                     0����׼ģʽ��
                                                     1���Զ���ģʽ�� */
        unsigned int  reserved_0 : 1;  /* bit[2]   : ��������������Ϊ0�� */
        unsigned int  ext_rec_en : 1;  /* bit[3]   : ��׼ģʽ�£�I2S�����������������ݣ�������������������PCMֻ����һ�����������ݡ�
                                                     ��·����ģʽ�£�����I2S��PCM������ͨ�����������á���ģʽ�£�ͨ�������ݿ�ȱ���Ϊ8bit��16bit��
                                                     0����׼��I2S��PCM����ģʽ��
                                                     1����չ��I2S��PCM��·����ģʽ�� */
        unsigned int  chn_num    : 2;  /* bit[4-5] : ��·���յ�ͨ����ѡ��
                                                     00��2 chn��
                                                     01��4 chn��
                                                     10��8 chn��
                                                     11��16 chn��. */
        unsigned int  clk_edge   : 1;  /* bit[6]   : PCM��·����ģʽ�£���������ʱ�ӱ���ѡ��
                                                     0���½�����Ч��
                                                     1����������Ч�� */
        unsigned int  reserved_1 : 25; /* bit[7-31]: ����ѡ��SIO�Ĺ���ģʽ */
    } reg;
} SOC_ASP_SIO_SIO_MODE_UNION;
#endif
#define SOC_ASP_SIO_SIO_MODE_sio_mode_START    (0)
#define SOC_ASP_SIO_SIO_MODE_sio_mode_END      (0)
#define SOC_ASP_SIO_SIO_MODE_pcm_mode_START    (1)
#define SOC_ASP_SIO_SIO_MODE_pcm_mode_END      (1)
#define SOC_ASP_SIO_SIO_MODE_ext_rec_en_START  (3)
#define SOC_ASP_SIO_SIO_MODE_ext_rec_en_END    (3)
#define SOC_ASP_SIO_SIO_MODE_chn_num_START     (4)
#define SOC_ASP_SIO_SIO_MODE_chn_num_END       (5)
#define SOC_ASP_SIO_SIO_MODE_clk_edge_START    (6)
#define SOC_ASP_SIO_SIO_MODE_clk_edge_END      (6)


/*****************************************************************************
 �ṹ��    : SOC_ASP_SIO_SIO_INTSTATUS_UNION
 �ṹ˵��  : SIO_INTSTATUS �Ĵ����ṹ���塣��ַƫ����:0x044����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rx_intr             : 1;  /* bit[0]   : ����FIFO������ֵ�ж���� 0��δ�����жϣ� 1���Ѳ����жϣ� */
        unsigned int  tx_intr             : 1;  /* bit[1]   : ����FIFO������ֵ�ж���� 0��δ�����жϣ� 1���Ѳ����жϣ� */
        unsigned int  rx_right_fifo_over  : 1;  /* bit[2]   : I2Sģʽ�£�����������FIFO�����жϣ�PCMģʽ����Ч 0��δ�����жϣ� 1���Ѳ����жϣ� */
        unsigned int  rx_left_fifo_over   : 1;  /* bit[3]   : I2Sģʽ�£�����������FIFO�����жϣ�PCMģʽ����Ч 0��δ�����жϣ� 1���Ѳ����жϣ� */
        unsigned int  tx_right_fifo_under : 1;  /* bit[4]   : I2Sģʽ�£�����������FIFO�����жϣ�PCMģʽ����Ч 0��δ�����жϣ� 1���Ѳ����жϣ� */
        unsigned int  tx_left_fifo_under  : 1;  /* bit[5]   : I2Sģʽ�£�����������FIFO�����жϣ�PCMģʽ����Ч 0��δ�����жϣ� 1���Ѳ����жϣ� */
        unsigned int  reserved            : 26; /* bit[6-31]:  */
    } reg;
} SOC_ASP_SIO_SIO_INTSTATUS_UNION;
#endif
#define SOC_ASP_SIO_SIO_INTSTATUS_rx_intr_START              (0)
#define SOC_ASP_SIO_SIO_INTSTATUS_rx_intr_END                (0)
#define SOC_ASP_SIO_SIO_INTSTATUS_tx_intr_START              (1)
#define SOC_ASP_SIO_SIO_INTSTATUS_tx_intr_END                (1)
#define SOC_ASP_SIO_SIO_INTSTATUS_rx_right_fifo_over_START   (2)
#define SOC_ASP_SIO_SIO_INTSTATUS_rx_right_fifo_over_END     (2)
#define SOC_ASP_SIO_SIO_INTSTATUS_rx_left_fifo_over_START    (3)
#define SOC_ASP_SIO_SIO_INTSTATUS_rx_left_fifo_over_END      (3)
#define SOC_ASP_SIO_SIO_INTSTATUS_tx_right_fifo_under_START  (4)
#define SOC_ASP_SIO_SIO_INTSTATUS_tx_right_fifo_under_END    (4)
#define SOC_ASP_SIO_SIO_INTSTATUS_tx_left_fifo_under_START   (5)
#define SOC_ASP_SIO_SIO_INTSTATUS_tx_left_fifo_under_END     (5)


/*****************************************************************************
 �ṹ��    : SOC_ASP_SIO_SIO_INTCLR_UNION
 �ṹ˵��  : SIO_INTCLR �Ĵ����ṹ���塣��ַƫ����:0x048����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�����Ĵ���.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rx_intr             : 1;  /* bit[0]   : ����FIFO������ֵ�ж���� */
        unsigned int  tx_intr             : 1;  /* bit[1]   : ����FIFO������ֵ�ж���� */
        unsigned int  rx_right_fifo_over  : 1;  /* bit[2]   : I2Sģʽ�£�����������FIFO�����жϣ�PCMģʽ����Ч */
        unsigned int  rx_left_fifo_over   : 1;  /* bit[3]   : I2Sģʽ�£�����������FIFO�����жϣ�PCMģʽ����Ч */
        unsigned int  tx_right_fifo_under : 1;  /* bit[4]   : I2Sģʽ�£�����������FIFO�����жϣ�PCMģʽ����Ч */
        unsigned int  tx_left_fifo_under  : 1;  /* bit[5]   : I2Sģʽ�£�����������FIFO�����жϣ�PCMģʽ����Ч */
        unsigned int  reserved            : 26; /* bit[6-31]: ��λ����Ĵ��� */
    } reg;
} SOC_ASP_SIO_SIO_INTCLR_UNION;
#endif
#define SOC_ASP_SIO_SIO_INTCLR_rx_intr_START              (0)
#define SOC_ASP_SIO_SIO_INTCLR_rx_intr_END                (0)
#define SOC_ASP_SIO_SIO_INTCLR_tx_intr_START              (1)
#define SOC_ASP_SIO_SIO_INTCLR_tx_intr_END                (1)
#define SOC_ASP_SIO_SIO_INTCLR_rx_right_fifo_over_START   (2)
#define SOC_ASP_SIO_SIO_INTCLR_rx_right_fifo_over_END     (2)
#define SOC_ASP_SIO_SIO_INTCLR_rx_left_fifo_over_START    (3)
#define SOC_ASP_SIO_SIO_INTCLR_rx_left_fifo_over_END      (3)
#define SOC_ASP_SIO_SIO_INTCLR_tx_right_fifo_under_START  (4)
#define SOC_ASP_SIO_SIO_INTCLR_tx_right_fifo_under_END    (4)
#define SOC_ASP_SIO_SIO_INTCLR_tx_left_fifo_under_START   (5)
#define SOC_ASP_SIO_SIO_INTCLR_tx_left_fifo_under_END     (5)


/*****************************************************************************
 �ṹ��    : SOC_ASP_SIO_SIO_I2S_LEFT_XD_UNION
 �ṹ˵��  : SIO_I2S_LEFT_XD �Ĵ����ṹ���塣��ַƫ����:0x04C����ֵ:0x00000000�����:32
 �Ĵ���˵��: I2Sģʽ�����������ݷ��ͼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tx_left_data : 32; /* bit[0-31]: I2Sģʽ�����������ݷ��ͼĴ�������Ч���ݷ��ڼĴ����ĵ�bit���򣬳�����Ч��ȵ�bitλ��SIOģ���Զ���0�� */
    } reg;
} SOC_ASP_SIO_SIO_I2S_LEFT_XD_UNION;
#endif
#define SOC_ASP_SIO_SIO_I2S_LEFT_XD_tx_left_data_START  (0)
#define SOC_ASP_SIO_SIO_I2S_LEFT_XD_tx_left_data_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_SIO_SIO_I2S_RIGHT_XD_UNION
 �ṹ˵��  : SIO_I2S_RIGHT_XD �Ĵ����ṹ���塣��ַƫ����:0x050����ֵ:0x00000000�����:32
 �Ĵ���˵��: I2Sģʽ�����������ݷ��ͼĴ���/PCMģʽ�µ����ݷ��ͼĴ���SIO_PCM_XD
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tx_right_data : 32; /* bit[0-31]: I2Sģʽ�����������ݷ��ͼĴ�������Ч���ݷ��ڼĴ����ĵ�bit���򣬳�����Ч��ȵ�bitλ��SIOģ���Զ���0��PCMģʽ�����ݷ��ͼĴ�����ֻ��[15:0]��Ч��Ϊ�ź�tx_data */
    } reg;
} SOC_ASP_SIO_SIO_I2S_RIGHT_XD_UNION;
#endif
#define SOC_ASP_SIO_SIO_I2S_RIGHT_XD_tx_right_data_START  (0)
#define SOC_ASP_SIO_SIO_I2S_RIGHT_XD_tx_right_data_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_SIO_SIO_I2S_LEFT_RD_UNION
 �ṹ˵��  : SIO_I2S_LEFT_RD �Ĵ����ṹ���塣��ַƫ����:0x054����ֵ:0x00000000�����:32
 �Ĵ���˵��: I2Sģʽ�����������ݽ��ռĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rx_left_data : 32; /* bit[0-31]: I2S���������ݽ��ռĴ�������Ч���ݷ��ڼĴ����ĵ�bit���򣬳�����Ч���ݿ�ȵ�bitλ�Զ���0 */
    } reg;
} SOC_ASP_SIO_SIO_I2S_LEFT_RD_UNION;
#endif
#define SOC_ASP_SIO_SIO_I2S_LEFT_RD_rx_left_data_START  (0)
#define SOC_ASP_SIO_SIO_I2S_LEFT_RD_rx_left_data_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_SIO_SIO_I2S_RIGHT_RD_UNION
 �ṹ˵��  : SIO_I2S_RIGHT_RD �Ĵ����ṹ���塣��ַƫ����:0x058����ֵ:0x00000000�����:32
 �Ĵ���˵��: I2Sģʽ�����������ݽ��ռĴ���/PCMģʽ�½������ݼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rx_right_data : 32; /* bit[0-31]: I2S���������ݽ��ռĴ�������Ч���ݷ��ڼĴ����ĵ�bit���򣬳�����Ч���ݿ�ȵ�bitλ�Զ���0��PCMģʽ�����ݽ��ռĴ�����ֻ��[15:0]��Ч��Ϊ�ź�rx_data */
    } reg;
} SOC_ASP_SIO_SIO_I2S_RIGHT_RD_UNION;
#endif
#define SOC_ASP_SIO_SIO_I2S_RIGHT_RD_rx_right_data_START  (0)
#define SOC_ASP_SIO_SIO_I2S_RIGHT_RD_rx_right_data_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_SIO_SIO_CT_SET_UNION
 �ṹ˵��  : SIO_CT_SET �Ĵ����ṹ���塣��ַƫ����:0x05C����ֵ:0x00008000�����:32
 �Ĵ���˵��: ���ƼĴ���ʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tx_fifo_threshold : 4;  /* bit[0-3]  : ����FIFO��ֵ��������ֵ�ᱨ�����жϺ�DMA���� */
        unsigned int  rx_fifo_threshold : 4;  /* bit[4-7]  : ����FIFO��ֵ��������ֵ�ᱨ�����жϺ�DMA���� */
        unsigned int  tx_data_merge_en  : 1;  /* bit[8]    : I2Sģʽ�·��͵����ݺϲ�ʹ�ܣ�����16bitλ�� 0����ֹ 1�����������ϲ���һ��32bit���ݴ���FIFO�У�������ռ�ݸ�16bit */
        unsigned int  rx_data_merge_en  : 1;  /* bit[9]    : I2Sģʽ�½��յ����ݺϲ�ʹ�ܣ�����16bitλ�� 0����ֹ 1�����������ϲ���һ��32bit���ݴ���FIFO�У�������ռ�ݸ�16bit */
        unsigned int  tx_fifo_disable   : 1;  /* bit[10]   : ����FIFO��ֹ 0��ʹ�ܣ�1����ֹ */
        unsigned int  rx_fifo_disable   : 1;  /* bit[11]   : ����FIFO��ֹ 0��ʹ�ܣ�1����ֹ */
        unsigned int  tx_enable         : 1;  /* bit[12]   : ����ͨ��ʹ�� 0����ֹ��1��ʹ�� */
        unsigned int  rx_enable         : 1;  /* bit[13]   : ����ͨ��ʹ�� 0����ֹ��1��ʹ�� */
        unsigned int  intr_en           : 1;  /* bit[14]   : �ж�ȫ��ʹ�� 0����ֹ��1��ʹ�� */
        unsigned int  rst_n             : 1;  /* bit[15]   : I2S/PCMͨ����λ���͵�ƽ��Ч�����ḴλCPU�ӿڼĴ����� */
        unsigned int  reserved          : 16; /* bit[16-31]: SIO���ƼĴ�������SIO����Ĵ����Ŀ��ƶ���һ�� */
    } reg;
} SOC_ASP_SIO_SIO_CT_SET_UNION;
#endif
#define SOC_ASP_SIO_SIO_CT_SET_tx_fifo_threshold_START  (0)
#define SOC_ASP_SIO_SIO_CT_SET_tx_fifo_threshold_END    (3)
#define SOC_ASP_SIO_SIO_CT_SET_rx_fifo_threshold_START  (4)
#define SOC_ASP_SIO_SIO_CT_SET_rx_fifo_threshold_END    (7)
#define SOC_ASP_SIO_SIO_CT_SET_tx_data_merge_en_START   (8)
#define SOC_ASP_SIO_SIO_CT_SET_tx_data_merge_en_END     (8)
#define SOC_ASP_SIO_SIO_CT_SET_rx_data_merge_en_START   (9)
#define SOC_ASP_SIO_SIO_CT_SET_rx_data_merge_en_END     (9)
#define SOC_ASP_SIO_SIO_CT_SET_tx_fifo_disable_START    (10)
#define SOC_ASP_SIO_SIO_CT_SET_tx_fifo_disable_END      (10)
#define SOC_ASP_SIO_SIO_CT_SET_rx_fifo_disable_START    (11)
#define SOC_ASP_SIO_SIO_CT_SET_rx_fifo_disable_END      (11)
#define SOC_ASP_SIO_SIO_CT_SET_tx_enable_START          (12)
#define SOC_ASP_SIO_SIO_CT_SET_tx_enable_END            (12)
#define SOC_ASP_SIO_SIO_CT_SET_rx_enable_START          (13)
#define SOC_ASP_SIO_SIO_CT_SET_rx_enable_END            (13)
#define SOC_ASP_SIO_SIO_CT_SET_intr_en_START            (14)
#define SOC_ASP_SIO_SIO_CT_SET_intr_en_END              (14)
#define SOC_ASP_SIO_SIO_CT_SET_rst_n_START              (15)
#define SOC_ASP_SIO_SIO_CT_SET_rst_n_END                (15)


/*****************************************************************************
 �ṹ��    : SOC_ASP_SIO_SIO_CT_CLR_UNION
 �ṹ˵��  : SIO_CT_CLR �Ĵ����ṹ���塣��ַƫ����:0x060����ֵ:0x00008000�����:32
 �Ĵ���˵��: ���ƼĴ�������Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tx_fifo_threshold : 4;  /* bit[0-3]  : ����FIFO��ֵ��������ֵ�ᱨ�����жϺ�DMA���� */
        unsigned int  rx_fifo_threshold : 4;  /* bit[4-7]  : ����FIFO��ֵ��������ֵ�ᱨ�����жϺ�DMA���� */
        unsigned int  tx_data_merge_en  : 1;  /* bit[8]    : I2Sģʽ�·��͵����ݺϲ�ʹ�ܣ�����16bitλ�� 0����ֹ 1�����������ϲ���һ��32bit���ݴ���FIFO�У�������ռ�ݸ�16bit */
        unsigned int  rx_data_merge_en  : 1;  /* bit[9]    : I2Sģʽ�½��յ����ݺϲ�ʹ�ܣ�����16bitλ�� 0����ֹ 1�����������ϲ���һ��32bit���ݴ���FIFO�У�������ռ�ݸ�16bit */
        unsigned int  tx_fifo_disable   : 1;  /* bit[10]   : ����FIFO��ֹ 0��ʹ�ܣ�1����ֹ */
        unsigned int  rx_fifo_disable   : 1;  /* bit[11]   : ����FIFO��ֹ 0��ʹ�ܣ�1����ֹ */
        unsigned int  tx_enable         : 1;  /* bit[12]   : ����ͨ��ʹ�� 0����ֹ��1��ʹ�� */
        unsigned int  rx_enable         : 1;  /* bit[13]   : ����ͨ��ʹ�� 0����ֹ��1��ʹ�� */
        unsigned int  intr_en           : 1;  /* bit[14]   : �ж�ȫ��ʹ�� 0����ֹ��1��ʹ�� */
        unsigned int  rst_n             : 1;  /* bit[15]   : I2S/PCMͨ����λ���͵�ƽ��Ч�����ḴλCPU�ӿڼĴ����� */
        unsigned int  reserved          : 16; /* bit[16-31]: SIO����Ĵ�������SIO���ƼĴ����Ŀ��ƶ���һ�� */
    } reg;
} SOC_ASP_SIO_SIO_CT_CLR_UNION;
#endif
#define SOC_ASP_SIO_SIO_CT_CLR_tx_fifo_threshold_START  (0)
#define SOC_ASP_SIO_SIO_CT_CLR_tx_fifo_threshold_END    (3)
#define SOC_ASP_SIO_SIO_CT_CLR_rx_fifo_threshold_START  (4)
#define SOC_ASP_SIO_SIO_CT_CLR_rx_fifo_threshold_END    (7)
#define SOC_ASP_SIO_SIO_CT_CLR_tx_data_merge_en_START   (8)
#define SOC_ASP_SIO_SIO_CT_CLR_tx_data_merge_en_END     (8)
#define SOC_ASP_SIO_SIO_CT_CLR_rx_data_merge_en_START   (9)
#define SOC_ASP_SIO_SIO_CT_CLR_rx_data_merge_en_END     (9)
#define SOC_ASP_SIO_SIO_CT_CLR_tx_fifo_disable_START    (10)
#define SOC_ASP_SIO_SIO_CT_CLR_tx_fifo_disable_END      (10)
#define SOC_ASP_SIO_SIO_CT_CLR_rx_fifo_disable_START    (11)
#define SOC_ASP_SIO_SIO_CT_CLR_rx_fifo_disable_END      (11)
#define SOC_ASP_SIO_SIO_CT_CLR_tx_enable_START          (12)
#define SOC_ASP_SIO_SIO_CT_CLR_tx_enable_END            (12)
#define SOC_ASP_SIO_SIO_CT_CLR_rx_enable_START          (13)
#define SOC_ASP_SIO_SIO_CT_CLR_rx_enable_END            (13)
#define SOC_ASP_SIO_SIO_CT_CLR_intr_en_START            (14)
#define SOC_ASP_SIO_SIO_CT_CLR_intr_en_END              (14)
#define SOC_ASP_SIO_SIO_CT_CLR_rst_n_START              (15)
#define SOC_ASP_SIO_SIO_CT_CLR_rst_n_END                (15)


/*****************************************************************************
 �ṹ��    : SOC_ASP_SIO_SIO_RX_STA_UNION
 �ṹ˵��  : SIO_RX_STA �Ĵ����ṹ���塣��ַƫ����:0x068����ֵ:0x00000000�����:32
 �Ĵ���˵��: SIO����״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rx_right_depth : 5;  /* bit[0-4]  : RX������FIFO��� */
        unsigned int  rx_left_depth  : 5;  /* bit[5-9]  : RX������FIFO��� */
        unsigned int  reserved       : 22; /* bit[10-31]: RX��������FIFO���ָʾ�Ĵ�����FIFO���Ϊ32 */
    } reg;
} SOC_ASP_SIO_SIO_RX_STA_UNION;
#endif
#define SOC_ASP_SIO_SIO_RX_STA_rx_right_depth_START  (0)
#define SOC_ASP_SIO_SIO_RX_STA_rx_right_depth_END    (4)
#define SOC_ASP_SIO_SIO_RX_STA_rx_left_depth_START   (5)
#define SOC_ASP_SIO_SIO_RX_STA_rx_left_depth_END     (9)


/*****************************************************************************
 �ṹ��    : SOC_ASP_SIO_SIO_TX_STA_UNION
 �ṹ˵��  : SIO_TX_STA �Ĵ����ṹ���塣��ַƫ����:0x06C����ֵ:0x00000000�����:32
 �Ĵ���˵��: SIO����״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tx_right_depth : 5;  /* bit[0-4]  : TX������FIFO��� */
        unsigned int  tx_left_depth  : 5;  /* bit[5-9]  : TX������FIFO��� */
        unsigned int  reserved       : 22; /* bit[10-31]: TX��������FIFO���ָʾ�Ĵ�����FIFO���Ϊ32 */
    } reg;
} SOC_ASP_SIO_SIO_TX_STA_UNION;
#endif
#define SOC_ASP_SIO_SIO_TX_STA_tx_right_depth_START  (0)
#define SOC_ASP_SIO_SIO_TX_STA_tx_right_depth_END    (4)
#define SOC_ASP_SIO_SIO_TX_STA_tx_left_depth_START   (5)
#define SOC_ASP_SIO_SIO_TX_STA_tx_left_depth_END     (9)


/*****************************************************************************
 �ṹ��    : SOC_ASP_SIO_SIO_DATA_WIDTH_SET_UNION
 �ṹ˵��  : SIO_DATA_WIDTH_SET �Ĵ����ṹ���塣��ַƫ����:0x078����ֵ:0x00000009�����:32
 �Ĵ���˵��: ���ݿ�ȼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tx_mode  : 3;  /* bit[0-2] : �������ݳ�������λ������I2Sģʽ�� 000������ 001:16bit�� 010:18bit�� 011:20bit�� 100:24bit�� 101:32bit�� 110-111���� ����PCMģʽ�� 000:8bit�� 001:16bit�� 010:32bit�� 011:64bit�� 100:128bit�� 101-111����  */
        unsigned int  rx_mode  : 3;  /* bit[3-5] : �������ݳ�������λ�� 000:8bit�� 001:16bit�� 010:18bit�� 011:20bit�� 100:24bit�� 101:32bit�� 110-111���� I2Sģʽ��֧��8bit��PCMģʽֻ֧��8bit��16bit */
        unsigned int  reserved_0: 2;  /* bit[6-7] :  */
        unsigned int  reserved_1: 24; /* bit[8-31]:  */
    } reg;
} SOC_ASP_SIO_SIO_DATA_WIDTH_SET_UNION;
#endif
#define SOC_ASP_SIO_SIO_DATA_WIDTH_SET_tx_mode_START   (0)
#define SOC_ASP_SIO_SIO_DATA_WIDTH_SET_tx_mode_END     (2)
#define SOC_ASP_SIO_SIO_DATA_WIDTH_SET_rx_mode_START   (3)
#define SOC_ASP_SIO_SIO_DATA_WIDTH_SET_rx_mode_END     (5)


/*****************************************************************************
 �ṹ��    : SOC_ASP_SIO_SIO_I2S_START_POS_UNION
 �ṹ˵��  : SIO_I2S_START_POS �Ĵ����ṹ���塣��ַƫ����:0x07C����ֵ:0x00000000�����:32
 �Ĵ���˵��: I2S����������ʼλ�����ÿ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  start_pos_read  : 1;  /* bit[0]   : ������FIFOʱ���ĸ�������ʼ���ʣ� 0����������1�������� */
        unsigned int  start_pos_write : 1;  /* bit[1]   : д����FIFOʱ���ĸ�������ʼ���ʣ� 0����������1�������� */
        unsigned int  reserved        : 30; /* bit[2-31]:  */
    } reg;
} SOC_ASP_SIO_SIO_I2S_START_POS_UNION;
#endif
#define SOC_ASP_SIO_SIO_I2S_START_POS_start_pos_read_START   (0)
#define SOC_ASP_SIO_SIO_I2S_START_POS_start_pos_read_END     (0)
#define SOC_ASP_SIO_SIO_I2S_START_POS_start_pos_write_START  (1)
#define SOC_ASP_SIO_SIO_I2S_START_POS_start_pos_write_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_ASP_SIO_I2S_POS_FLAG_UNION
 �ṹ˵��  : I2S_POS_FLAG �Ĵ����ṹ���塣��ַƫ����:0x080����ֵ:0x00000000�����:32
 �Ĵ���˵��: I2S��������������ǰλ��״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  start_pos_read  : 1;  /* bit[0]   : ��һ�ζ�����FIFOʱ���ĸ�������ʼ���ʣ�0����������1�������� */
        unsigned int  start_pos_write : 1;  /* bit[1]   : ��һ��д����FIFOʱ���ĸ�������ʼ���ʣ�0����������1�������� */
        unsigned int  reserved        : 30; /* bit[2-31]:  */
    } reg;
} SOC_ASP_SIO_I2S_POS_FLAG_UNION;
#endif
#define SOC_ASP_SIO_I2S_POS_FLAG_start_pos_read_START   (0)
#define SOC_ASP_SIO_I2S_POS_FLAG_start_pos_read_END     (0)
#define SOC_ASP_SIO_I2S_POS_FLAG_start_pos_write_START  (1)
#define SOC_ASP_SIO_I2S_POS_FLAG_start_pos_write_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_ASP_SIO_SIO_SIGNED_EXT_UNION
 �ṹ˵��  : SIO_SIGNED_EXT �Ĵ����ṹ���塣��ַƫ����:0x084����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��λ���ݷ�����չʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  signed_ext_en : 1;  /* bit[0]   : ��λ���ݷ�����չ�� 0����ֹ�� 1��ʹ�ܣ� */
        unsigned int  reserved      : 31; /* bit[1-31]: ����λ��չֻ�Խ���������Ч���Է���������Ч��PCMģʽ��I2Sģʽ�¶�֧�ָ���չ��֧�ֳ�32bit������λ�� */
    } reg;
} SOC_ASP_SIO_SIO_SIGNED_EXT_UNION;
#endif
#define SOC_ASP_SIO_SIO_SIGNED_EXT_signed_ext_en_START  (0)
#define SOC_ASP_SIO_SIO_SIGNED_EXT_signed_ext_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_ASP_SIO_SIO_I2S_POS_MERGE_EN_UNION
 �ṹ˵��  : SIO_I2S_POS_MERGE_EN �Ĵ����ṹ���塣��ַƫ����:0x088����ֵ:0x00000000�����:32
 �Ĵ���˵��: I2S�����������ݺϲ�ʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  merge_on : 1;  /* bit[0]   : I2Sģʽ�£������������ݲ�����ַ�ϲ� 0����ֹ�� 1��ʹ�ܣ� */
        unsigned int  reserved : 31; /* bit[1-31]: I2Sģʽ�£������������ݲ�����ַ�ϲ�ʹ�� */
    } reg;
} SOC_ASP_SIO_SIO_I2S_POS_MERGE_EN_UNION;
#endif
#define SOC_ASP_SIO_SIO_I2S_POS_MERGE_EN_merge_on_START  (0)
#define SOC_ASP_SIO_SIO_I2S_POS_MERGE_EN_merge_on_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_ASP_SIO_SIO_INTMASK_UNION
 �ṹ˵��  : SIO_INTMASK �Ĵ����ṹ���塣��ַƫ����:0x08C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж����μĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rx_intr             : 1;  /* bit[0]   : ����FIFO������ֵ�ж����Σ� 0�������Σ� 1�����Σ� */
        unsigned int  tx_intr             : 1;  /* bit[1]   : ����FIFO������ֵ�ж����Σ� 0�������Σ� 1�����Σ� */
        unsigned int  rx_right_fifo_over  : 1;  /* bit[2]   : I2Sģʽ�£�����������FIFO�����ж����Σ�PCMģʽ����Ч�� 0�������Σ� 1�����Σ� */
        unsigned int  rx_left_fifo_over   : 1;  /* bit[3]   : I2Sģʽ�£�����������FIFO�����ж����Σ�PCMģʽ����Ч�� 0�������Σ� 1�����Σ� */
        unsigned int  tx_right_fifo_under : 1;  /* bit[4]   : I2Sģʽ�£�����������FIFO�����ж����Σ�PCMģʽ����Ч�� 0�������Σ� 1�����Σ� */
        unsigned int  tx_left_fifo_under  : 1;  /* bit[5]   : I2Sģʽ�£�����������FIFO�����ж����Σ�PCMģʽ����Ч�� 0�������Σ� 1�����Σ� */
        unsigned int  reserved            : 26; /* bit[6-31]:  */
    } reg;
} SOC_ASP_SIO_SIO_INTMASK_UNION;
#endif
#define SOC_ASP_SIO_SIO_INTMASK_rx_intr_START              (0)
#define SOC_ASP_SIO_SIO_INTMASK_rx_intr_END                (0)
#define SOC_ASP_SIO_SIO_INTMASK_tx_intr_START              (1)
#define SOC_ASP_SIO_SIO_INTMASK_tx_intr_END                (1)
#define SOC_ASP_SIO_SIO_INTMASK_rx_right_fifo_over_START   (2)
#define SOC_ASP_SIO_SIO_INTMASK_rx_right_fifo_over_END     (2)
#define SOC_ASP_SIO_SIO_INTMASK_rx_left_fifo_over_START    (3)
#define SOC_ASP_SIO_SIO_INTMASK_rx_left_fifo_over_END      (3)
#define SOC_ASP_SIO_SIO_INTMASK_tx_right_fifo_under_START  (4)
#define SOC_ASP_SIO_SIO_INTMASK_tx_right_fifo_under_END    (4)
#define SOC_ASP_SIO_SIO_INTMASK_tx_left_fifo_under_START   (5)
#define SOC_ASP_SIO_SIO_INTMASK_tx_left_fifo_under_END     (5)


/*****************************************************************************
 �ṹ��    : SOC_ASP_SIO_SIO_I2S_DUAL_RX_CHN_UNION
 �ṹ˵��  : SIO_I2S_DUAL_RX_CHN �Ĵ����ṹ���塣��ַƫ����:0x0A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���պϲ����ݼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rx_data : 32; /* bit[0-31]: ��I2Sģʽ��������������ַ�ϲ�ʹ�ܵ������£���Ϊ��ȡ�������ݵļĴ��� */
    } reg;
} SOC_ASP_SIO_SIO_I2S_DUAL_RX_CHN_UNION;
#endif
#define SOC_ASP_SIO_SIO_I2S_DUAL_RX_CHN_rx_data_START  (0)
#define SOC_ASP_SIO_SIO_I2S_DUAL_RX_CHN_rx_data_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_SIO_SIO_I2S_DUAL_TX_CHN_UNION
 �ṹ˵��  : SIO_I2S_DUAL_TX_CHN �Ĵ����ṹ���塣��ַƫ����:0x0C0����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���ͺϲ����ݼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tx_data : 32; /* bit[0-31]: ��I2Sģʽ��������������ַ�ϲ�ʹ�ܵ������£���Ϊд���������ݵļĴ��� */
    } reg;
} SOC_ASP_SIO_SIO_I2S_DUAL_TX_CHN_UNION;
#endif
#define SOC_ASP_SIO_SIO_I2S_DUAL_TX_CHN_tx_data_START  (0)
#define SOC_ASP_SIO_SIO_I2S_DUAL_TX_CHN_tx_data_END    (31)






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

#endif /* end of soc_asp_sio_interface.h */
