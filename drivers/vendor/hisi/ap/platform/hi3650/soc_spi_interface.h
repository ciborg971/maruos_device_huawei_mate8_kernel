/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_spi_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:23:11
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_SPI.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_SPI_INTERFACE_H__
#define __SOC_SPI_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) register_spi
 ****************************************************************************/
/* �Ĵ���˵�������ƼĴ���0��
   λ����UNION�ṹ:  SOC_SPI_SPICR0_UNION */
#define SOC_SPI_SPICR0_ADDR(base)                     ((base) + (0x000))

/* �Ĵ���˵�������ƼĴ���1��
   λ����UNION�ṹ:  SOC_SPI_SPICR1_UNION */
#define SOC_SPI_SPICR1_ADDR(base)                     ((base) + (0x004))

/* �Ĵ���˵�������ݼĴ�����
   λ����UNION�ṹ:  SOC_SPI_SPIDR_UNION */
#define SOC_SPI_SPIDR_ADDR(base)                      ((base) + (0x008))

/* �Ĵ���˵����״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SPI_SPISR_UNION */
#define SOC_SPI_SPISR_ADDR(base)                      ((base) + (0x00C))

/* �Ĵ���˵����ʱ�ӷ�Ƶ�Ĵ�����
   λ����UNION�ṹ:  SOC_SPI_SPICPSR_UNION */
#define SOC_SPI_SPICPSR_ADDR(base)                    ((base) + (0x010))

/* �Ĵ���˵�����ж����μĴ�����
            ֵ��0����ʾ�����жϣ�ֵ��1����ʾ�������жϡ�
   λ����UNION�ṹ:  SOC_SPI_SPIIMSC_UNION */
#define SOC_SPI_SPIIMSC_ADDR(base)                    ((base) + (0x014))

/* �Ĵ���˵����ԭʼ�ж�״̬�Ĵ�����
            ֵ��0����ʾ���жϣ�ֵ��1����ʾ���жϡ�
   λ����UNION�ṹ:  SOC_SPI_SPIRIS_UNION */
#define SOC_SPI_SPIRIS_ADDR(base)                     ((base) + (0x018))

/* �Ĵ���˵�������κ��ж�״̬�Ĵ�����
            ֵ��0����ʾ���жϣ�ֵ��1����ʾ���жϡ�
   λ����UNION�ṹ:  SOC_SPI_SPIMIS_UNION */
#define SOC_SPI_SPIMIS_ADDR(base)                     ((base) + (0x01C))

/* �Ĵ���˵�����ж�����Ĵ�����
   λ����UNION�ṹ:  SOC_SPI_SPIICR_UNION */
#define SOC_SPI_SPIICR_ADDR(base)                     ((base) + (0x020))

/* �Ĵ���˵����DMA���ƼĴ�����
   λ����UNION�ṹ:  SOC_SPI_SPIDMACR_UNION */
#define SOC_SPI_SPIDMACR_ADDR(base)                   ((base) + (0x024))

/* �Ĵ���˵��������FIFO���ƼĴ�����
   λ����UNION�ṹ:  SOC_SPI_SPITXFIFOCR_UNION */
#define SOC_SPI_SPITXFIFOCR_ADDR(base)                ((base) + (0x028))

/* �Ĵ���˵��������FIFO���ƼĴ�����
   λ����UNION�ṹ:  SOC_SPI_SPIRXFIFOCR_UNION */
#define SOC_SPI_SPIRXFIFOCR_ADDR(base)                ((base) + (0x02C))





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
                     (1/1) register_spi
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_SPI_SPICR0_UNION
 �ṹ˵��  : SPICR0 �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x0000�����:16
 �Ĵ���˵��: ���ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  dss : 4;  /* bit[0-3] : ��������λ��
                                                0011��4bit�� 1000��9bit�� 1101��14bit��
                                                0100��5bit�� 1001��10bit�� 1110��15bit��
                                                0101��6bit�� 1010��11bit�� 1111��16bit��
                                                0110��7bit�� 1011��12bit�� ������������
                                                0111��8bit�� 1100��13bit��  */
        unsigned short  frf : 2;  /* bit[4-5] : ֡��ʽ��
                                                00��SPI֡��ʽ��
                                                ������������ */
        unsigned short  spo : 1;  /* bit[6]   : SPICLKOUT���ԣ����庬����μ�SPI֡��ʽ�� */
        unsigned short  sph : 1;  /* bit[7]   : SPICLKOUT��λ������μ�SPI֡��ʽ�� */
        unsigned short  scr : 8;  /* bit[8-15]: ����ʱ���ʣ�ȡֵ��Χ0��255��SCR��ֵ��������SPI���ͺͽ��յı����ʣ���ʽΪFSPICLK/��CPSDVSR����1+SCR������
                                                CPSDVSR��һ��2��254֮���ż�����ɼĴ���SPICPSR���á� */
    } reg;
} SOC_SPI_SPICR0_UNION;
#endif
#define SOC_SPI_SPICR0_dss_START  (0)
#define SOC_SPI_SPICR0_dss_END    (3)
#define SOC_SPI_SPICR0_frf_START  (4)
#define SOC_SPI_SPICR0_frf_END    (5)
#define SOC_SPI_SPICR0_spo_START  (6)
#define SOC_SPI_SPICR0_spo_END    (6)
#define SOC_SPI_SPICR0_sph_START  (7)
#define SOC_SPI_SPICR0_sph_END    (7)
#define SOC_SPI_SPICR0_scr_START  (8)
#define SOC_SPI_SPICR0_scr_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SPI_SPICR1_UNION
 �ṹ˵��  : SPICR1 �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x0000�����:16
 �Ĵ���˵��: ���ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  lbm      : 1;  /* bit[0]   : ���û���ģʽ��
                                                     0�������Ĵ��нӿڲ���ʹ�ܣ�
                                                     1�����ʹ�����λ�Ĵ�����������ڲ����ӵ����մ�����λ�Ĵ����������ϡ� */
        unsigned short  sse      : 1;  /* bit[1]   : ����SPIʹ�ܡ�
                                                     0����ʹ�ܣ�
                                                     1��ʹ�ܡ� */
        unsigned short  ms       : 1;  /* bit[2]   : ����Master����Slaveģʽ����λֻ����SPI����ֹʱ�ı䡣
                                                     0��Masterģʽ��Ĭ�ϣ���
                                                     1�������� */
        unsigned short  reserved : 13; /* bit[3-15]: ������ */
    } reg;
} SOC_SPI_SPICR1_UNION;
#endif
#define SOC_SPI_SPICR1_lbm_START       (0)
#define SOC_SPI_SPICR1_lbm_END         (0)
#define SOC_SPI_SPICR1_sse_START       (1)
#define SOC_SPI_SPICR1_sse_END         (1)
#define SOC_SPI_SPICR1_ms_START        (2)
#define SOC_SPI_SPICR1_ms_END          (2)


/*****************************************************************************
 �ṹ��    : SOC_SPI_SPIDR_UNION
 �ṹ˵��  : SPIDR �Ĵ����ṹ���塣��ַƫ����:0x008����ֵ:0x0000�����:16
 �Ĵ���˵��: ���ݼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  data : 16; /* bit[0-15]: ����/����FIFO��
                                                 ��������FIFO��
                                                 д������FIFO��
                                                 ������ݱ���������16������Ҷ��롣�����߼������Ը�λδʹ�õı���λ�������߼����Զ��������Ҷ��롣 */
    } reg;
} SOC_SPI_SPIDR_UNION;
#endif
#define SOC_SPI_SPIDR_data_START  (0)
#define SOC_SPI_SPIDR_data_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SPI_SPISR_UNION
 �ṹ˵��  : SPISR �Ĵ����ṹ���塣��ַƫ����:0x00C����ֵ:0x0003�����:16
 �Ĵ���˵��: ״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  tfe      : 1;  /* bit[0]   : ����FIFO�Ƿ��ѿա�
                                                     0��δ�գ�
                                                     1���ѿա� */
        unsigned short  tnf      : 1;  /* bit[1]   : ����FIFO�Ƿ�δ����
                                                     0��������
                                                     1��δ���� */
        unsigned short  rne      : 1;  /* bit[2]   : ����FIFO�Ƿ�δ�ա�
                                                     0���ѿգ�
                                                     1��δ�ա� */
        unsigned short  rff      : 1;  /* bit[3]   : ����FIFO�Ƿ�������
                                                     0��δ����
                                                     1�������� */
        unsigned short  bsy      : 1;  /* bit[4]   : SPIæ��ǡ�
                                                     0�����У�
                                                     1��æ�� */
        unsigned short  reserved : 11; /* bit[5-15]: ������ */
    } reg;
} SOC_SPI_SPISR_UNION;
#endif
#define SOC_SPI_SPISR_tfe_START       (0)
#define SOC_SPI_SPISR_tfe_END         (0)
#define SOC_SPI_SPISR_tnf_START       (1)
#define SOC_SPI_SPISR_tnf_END         (1)
#define SOC_SPI_SPISR_rne_START       (2)
#define SOC_SPI_SPISR_rne_END         (2)
#define SOC_SPI_SPISR_rff_START       (3)
#define SOC_SPI_SPISR_rff_END         (3)
#define SOC_SPI_SPISR_bsy_START       (4)
#define SOC_SPI_SPISR_bsy_END         (4)


/*****************************************************************************
 �ṹ��    : SOC_SPI_SPICPSR_UNION
 �ṹ˵��  : SPICPSR �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x0000�����:16
 �Ĵ���˵��: ʱ�ӷ�Ƶ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  cpsdvsr  : 8;  /* bit[0-7] : ʱ�ӷ�Ƶ���ӡ���ֵ������2��254֮���ż����ȡ��������ʱ��SPICLK��Ƶ�ʡ����λ������0���� */
        unsigned short  reserved : 8;  /* bit[8-15]: ������ */
    } reg;
} SOC_SPI_SPICPSR_UNION;
#endif
#define SOC_SPI_SPICPSR_cpsdvsr_START   (0)
#define SOC_SPI_SPICPSR_cpsdvsr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_SPI_SPIIMSC_UNION
 �ṹ˵��  : SPIIMSC �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x0000�����:16
 �Ĵ���˵��: �ж����μĴ�����
            ֵ��0����ʾ�����жϣ�ֵ��1����ʾ�������жϡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  rorim    : 1;  /* bit[0]   : ��������ж����Ρ�
                                                     0������FIFO����ж����Σ�
                                                     1������FIFO����жϲ����Ρ� */
        unsigned short  rtim     : 1;  /* bit[1]   : ���ճ�ʱ�жϡ�
                                                     0�����ճ�ʱ�ж����Σ�
                                                     1�����ճ�ʱ�жϲ����Ρ� */
        unsigned short  rxim     : 1;  /* bit[2]   : ����FIFO�ж����Ρ�
                                                     0����ջ����������жϱ����Σ�
                                                     1����ջ����������ж�δ�����Ρ� */
        unsigned short  txim     : 1;  /* bit[3]   : ����FIFO�ж����Ρ�
                                                     0����ջ����������жϱ����Σ�
                                                     1����ջ����������ж�δ�����Ρ� */
        unsigned short  reserved : 12; /* bit[4-15]: ������ */
    } reg;
} SOC_SPI_SPIIMSC_UNION;
#endif
#define SOC_SPI_SPIIMSC_rorim_START     (0)
#define SOC_SPI_SPIIMSC_rorim_END       (0)
#define SOC_SPI_SPIIMSC_rtim_START      (1)
#define SOC_SPI_SPIIMSC_rtim_END        (1)
#define SOC_SPI_SPIIMSC_rxim_START      (2)
#define SOC_SPI_SPIIMSC_rxim_END        (2)
#define SOC_SPI_SPIIMSC_txim_START      (3)
#define SOC_SPI_SPIIMSC_txim_END        (3)


/*****************************************************************************
 �ṹ��    : SOC_SPI_SPIRIS_UNION
 �ṹ˵��  : SPIRIS �Ĵ����ṹ���塣��ַƫ����:0x018����ֵ:0x0008�����:16
 �Ĵ���˵��: ԭʼ�ж�״̬�Ĵ�����
            ֵ��0����ʾ���жϣ�ֵ��1����ʾ���жϡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  rorris   : 1;  /* bit[0]   : ��������жϵ�ԭʼ�ж�״̬�� */
        unsigned short  rtris    : 1;  /* bit[1]   : ���ճ�ʱ�жϵ�ԭʼ�ж�״̬�� */
        unsigned short  rxris    : 1;  /* bit[2]   : ����FIFO�жϵ�ԭʼ�ж�״̬�� */
        unsigned short  txris    : 1;  /* bit[3]   : ����FIFO�жϵ�ԭʼ�ж�״̬�� */
        unsigned short  reserved : 12; /* bit[4-15]: ������ */
    } reg;
} SOC_SPI_SPIRIS_UNION;
#endif
#define SOC_SPI_SPIRIS_rorris_START    (0)
#define SOC_SPI_SPIRIS_rorris_END      (0)
#define SOC_SPI_SPIRIS_rtris_START     (1)
#define SOC_SPI_SPIRIS_rtris_END       (1)
#define SOC_SPI_SPIRIS_rxris_START     (2)
#define SOC_SPI_SPIRIS_rxris_END       (2)
#define SOC_SPI_SPIRIS_txris_START     (3)
#define SOC_SPI_SPIRIS_txris_END       (3)


/*****************************************************************************
 �ṹ��    : SOC_SPI_SPIMIS_UNION
 �ṹ˵��  : SPIMIS �Ĵ����ṹ���塣��ַƫ����:0x01C����ֵ:0x0000�����:16
 �Ĵ���˵��: ���κ��ж�״̬�Ĵ�����
            ֵ��0����ʾ���жϣ�ֵ��1����ʾ���жϡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  rormis   : 1;  /* bit[0]   : ��������ж����κ��״̬�� */
        unsigned short  rtmis    : 1;  /* bit[1]   : ���ճ�ʱ�ж����κ��״̬�� */
        unsigned short  rxmis    : 1;  /* bit[2]   : ����FIFO�ж����κ��״̬�� */
        unsigned short  txmis    : 1;  /* bit[3]   : ����FIFO�ж����κ��״̬�� */
        unsigned short  reserved : 12; /* bit[4-15]: ������ */
    } reg;
} SOC_SPI_SPIMIS_UNION;
#endif
#define SOC_SPI_SPIMIS_rormis_START    (0)
#define SOC_SPI_SPIMIS_rormis_END      (0)
#define SOC_SPI_SPIMIS_rtmis_START     (1)
#define SOC_SPI_SPIMIS_rtmis_END       (1)
#define SOC_SPI_SPIMIS_rxmis_START     (2)
#define SOC_SPI_SPIMIS_rxmis_END       (2)
#define SOC_SPI_SPIMIS_txmis_START     (3)
#define SOC_SPI_SPIMIS_txmis_END       (3)


/*****************************************************************************
 �ṹ��    : SOC_SPI_SPIICR_UNION
 �ṹ˵��  : SPIICR �Ĵ����ṹ���塣��ַƫ����:0x020����ֵ:0x0000�����:16
 �Ĵ���˵��: �ж�����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  roric    : 1;  /* bit[0]   : �����������жϡ� */
        unsigned short  rtic     : 1;  /* bit[1]   : ������ճ�ʱ�жϡ� */
        unsigned short  reserved : 14; /* bit[2-15]: ������ */
    } reg;
} SOC_SPI_SPIICR_UNION;
#endif
#define SOC_SPI_SPIICR_roric_START     (0)
#define SOC_SPI_SPIICR_roric_END       (0)
#define SOC_SPI_SPIICR_rtic_START      (1)
#define SOC_SPI_SPIICR_rtic_END        (1)


/*****************************************************************************
 �ṹ��    : SOC_SPI_SPIDMACR_UNION
 �ṹ˵��  : SPIDMACR �Ĵ����ṹ���塣��ַƫ����:0x024����ֵ:0x0000�����:16
 �Ĵ���˵��: DMA���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  rxdmae   : 1;  /* bit[0]   : DMA����FIFOʹ�ܼĴ�����
                                                     0����ֹ��
                                                     1��ʹ�ܡ� */
        unsigned short  txdmae   : 1;  /* bit[1]   : DMA����FIFOʹ�ܼĴ�����
                                                     0����ֹ��
                                                     1��ʹ�ܡ� */
        unsigned short  reserved : 14; /* bit[2-15]: ������ */
    } reg;
} SOC_SPI_SPIDMACR_UNION;
#endif
#define SOC_SPI_SPIDMACR_rxdmae_START    (0)
#define SOC_SPI_SPIDMACR_rxdmae_END      (0)
#define SOC_SPI_SPIDMACR_txdmae_START    (1)
#define SOC_SPI_SPIDMACR_txdmae_END      (1)


/*****************************************************************************
 �ṹ��    : SOC_SPI_SPITXFIFOCR_UNION
 �ṹ˵��  : SPITXFIFOCR �Ĵ����ṹ���塣��ַƫ����:0x028����ֵ:0x0009�����:16
 �Ĵ���˵��: ����FIFO���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  dmatxbrsize : 3;  /* bit[0-2] : ���÷���FIFO����DMA����burst�����ˮ�ߡ���������FIFO��������ĿС�ڻ����dmatxbrsize�����õ�����ʱ��DMATXBREQ��Ч��
                                                        000��255��
                                                        001��252��
                                                        010��248��
                                                        011��240��
                                                        100��224��
                                                        101��192��
                                                        110��192��
                                                        111��192�� */
        unsigned short  txintsize   : 3;  /* bit[3-5] : ���÷���FIFO�����жϵ�ˮ�ߡ���������FIFO��������ĿС�ڻ����TXINTSize�����õ�����ʱ��TXRIS��Ч��
                                                        000��1��
                                                        001��4��
                                                        010��8��
                                                        011��16��
                                                        100��32��
                                                        101��64��
                                                        110��128��
                                                        111��128�� */
        unsigned short  reserved    : 10; /* bit[6-15]: ������ */
    } reg;
} SOC_SPI_SPITXFIFOCR_UNION;
#endif
#define SOC_SPI_SPITXFIFOCR_dmatxbrsize_START  (0)
#define SOC_SPI_SPITXFIFOCR_dmatxbrsize_END    (2)
#define SOC_SPI_SPITXFIFOCR_txintsize_START    (3)
#define SOC_SPI_SPITXFIFOCR_txintsize_END      (5)


/*****************************************************************************
 �ṹ��    : SOC_SPI_SPIRXFIFOCR_UNION
 �ṹ˵��  : SPIRXFIFOCR �Ĵ����ṹ���塣��ַƫ����:0x02C����ֵ:0x0009�����:16
 �Ĵ���˵��: ����FIFO���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  dmarxbrsize : 3;  /* bit[0-2] : ���ý���FIFO����DMA����burst�����ˮ�ߡ���������FIFO��������Ŀ���ڻ����dmarxbrsize�����õ�����ʱ��DMARXBREQ��Ч���˴��ֳ���16λ��
                                                        000��1��
                                                        001��4��
                                                        010��8��
                                                        011��16��
                                                        100��32��
                                                        101��64��
                                                        110��64��
                                                        111��64�� */
        unsigned short  rxintsize   : 3;  /* bit[3-5] : ���ý���FIFO�����жϵ�ˮ�ߡ���������FIFO��������Ŀ���ڻ����rxintsize�����õ�����ʱ��RXRIS��Ч��
                                                        000��255��
                                                        001��252��
                                                        010��248��
                                                        011��240��
                                                        100��224��
                                                        101��192��
                                                        110��128��
                                                        111��32�� */
        unsigned short  reserved    : 10; /* bit[6-15]: ������ */
    } reg;
} SOC_SPI_SPIRXFIFOCR_UNION;
#endif
#define SOC_SPI_SPIRXFIFOCR_dmarxbrsize_START  (0)
#define SOC_SPI_SPIRXFIFOCR_dmarxbrsize_END    (2)
#define SOC_SPI_SPIRXFIFOCR_rxintsize_START    (3)
#define SOC_SPI_SPIRXFIFOCR_rxintsize_END      (5)






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

#endif /* end of soc_spi_interface.h */
