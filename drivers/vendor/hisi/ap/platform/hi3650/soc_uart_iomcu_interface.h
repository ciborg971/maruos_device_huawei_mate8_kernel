/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_uart_iomcu_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:23:20
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_UART_IOMCU.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_UART_IOMCU_INTERFACE_H__
#define __SOC_UART_IOMCU_INTERFACE_H__

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
/* �Ĵ���˵�������ݼĴ�����
   λ����UNION�ṹ:  SOC_UART_IOMCU_UARTDR_UNION */
#define SOC_UART_IOMCU_UARTDR_ADDR(base)              ((base) + (0x000))

/* �Ĵ���˵��������״̬�Ĵ���/��������Ĵ�����
   λ����UNION�ṹ:  SOC_UART_IOMCU_UARTRSR_UARTECR_UNION */
#define SOC_UART_IOMCU_UARTRSR_UARTECR_ADDR(base)     ((base) + (0x004))

/* �Ĵ���˵������ǩ�Ĵ�����
   λ����UNION�ṹ:  SOC_UART_IOMCU_UARTFR_UNION */
#define SOC_UART_IOMCU_UARTFR_ADDR(base)              ((base) + (0x018))

/* �Ĵ���˵����IrDA�͹��ļ������Ĵ�����
   λ����UNION�ṹ:  SOC_UART_IOMCU_UARTLPR_UNION */
#define SOC_UART_IOMCU_UARTLPR_ADDR(base)             ((base) + (0x020))

/* �Ĵ���˵���������ʼĴ�����
   λ����UNION�ṹ:  SOC_UART_IOMCU_UARTIBRD_UNION */
#define SOC_UART_IOMCU_UARTIBRD_ADDR(base)            ((base) + (0x024))

/* �Ĵ���˵���������ʼĴ�����
   λ����UNION�ṹ:  SOC_UART_IOMCU_UARTFBRD_UNION */
#define SOC_UART_IOMCU_UARTFBRD_ADDR(base)            ((base) + (0x028))

/* �Ĵ���˵�����߿أ�line control���Ĵ�����
   λ����UNION�ṹ:  SOC_UART_IOMCU_UARTLCR_H_UNION */
#define SOC_UART_IOMCU_UARTLCR_H_ADDR(base)           ((base) + (0x02C))

/* �Ĵ���˵�������ƼĴ�����
   λ����UNION�ṹ:  SOC_UART_IOMCU_UARTCR_UNION */
#define SOC_UART_IOMCU_UARTCR_ADDR(base)              ((base) + (0x030))

/* �Ĵ���˵�����ж�FIFO levelѡ��Ĵ�����
            ����FIFO�ͽ���FIFO����ȶ���16��
   λ����UNION�ṹ:  SOC_UART_IOMCU_UARTIFLS_UNION */
#define SOC_UART_IOMCU_UARTIFLS_ADDR(base)            ((base) + (0x034))

/* �Ĵ���˵�����ж����ε�����/���ѡ��Ĵ�����
            ֵ��0����ʾ�жϱ����Σ�ֵ��1����ʾ�жϱ����á�
   λ����UNION�ṹ:  SOC_UART_IOMCU_UARTIMSC_UNION */
#define SOC_UART_IOMCU_UARTIMSC_ADDR(base)            ((base) + (0x038))

/* �Ĵ���˵����ԭʼ�ж�״̬�Ĵ�����
            ��λʱ����modem�жϣ�bit[1]���⣬����bitȫ�����㡣modem�жϸ�λ��״̬��ȷ����ֵ��0����ʾ���ж�δ������ֵ��1����ʾ���ж��Ѵ�����
   λ����UNION�ṹ:  SOC_UART_IOMCU_UARTRIS_UNION */
#define SOC_UART_IOMCU_UARTRIS_ADDR(base)             ((base) + (0x03C))

/* �Ĵ���˵�������κ��ж�״̬�Ĵ�����
            ��λʱ����modem�жϣ�bit[1]���⣬����bitȫ�����㡣modem�жϸ�λ��״̬��ȷ����ֵ��0����ʾ���ж�δ������ֵ��1����ʾ���ж��Ѵ�����
   λ����UNION�ṹ:  SOC_UART_IOMCU_UARTMIS_UNION */
#define SOC_UART_IOMCU_UARTMIS_ADDR(base)             ((base) + (0x040))

/* �Ĵ���˵�����ж�����Ĵ�����
            д��1�������Ӧ�жϣ�д��0���������á�
   λ����UNION�ṹ:  SOC_UART_IOMCU_UARTICR_UNION */
#define SOC_UART_IOMCU_UARTICR_ADDR(base)             ((base) + (0x044))

/* �Ĵ���˵����DMA���ƼĴ�����
   λ����UNION�ṹ:  SOC_UART_IOMCU_UARTDMACR_UNION */
#define SOC_UART_IOMCU_UARTDMACR_ADDR(base)           ((base) + (0x048))





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
 �ṹ��    : SOC_UART_IOMCU_UARTDR_UNION
 �ṹ˵��  : UARTDR �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x0000�����:16
 �Ĵ���˵��: ���ݼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  data     : 8;  /* bit[0-7]  : ���պͷ��͵����ݡ� */
        unsigned short  fe       : 1;  /* bit[8]    : Framing����
                                                      0�������壻
                                                      1�����յ����ַ���ֹͣλ������Ч��ֹͣλΪ1����
                                                      FIFOģʽ�£��ô�����FIFO�������ַ�������� */
        unsigned short  pe       : 1;  /* bit[9]    : Parity����
                                                      0�������壻
                                                      1���������ݵ�У�����ͼĴ���UARTLCR_H�е����ò�ƥ�䡣
                                                      FIFOģʽ�£��ô�����FIFO�������ַ�������� */
        unsigned short  be       : 1;  /* bit[10]   : Break����
                                                      0�������壻
                                                      1��break��������⵽���������ݵ����뱣�ֵ͵�ʱ���һ��ȫ�ִ��䣨����Ϊstart��data��parity��stop bit��ʱ�仹Ҫ����
                                                      ��break����ʱ��ֻ��һ��0�ַ�����FIFO�С������������Ϊ1��marking state������һ����Ч����ʼλ������ʱ����һ���ַ��ű�ʹ�ܡ� 
                                                      FIFOģʽ�£��ô�����FIFO�������ַ�������� */
        unsigned short  oe       : 1;  /* bit[11]   : Overrun����
                                                      0������FIFO�п�λ����һ���µ��ַ�д��FIFO�У�
                                                      1������FIFO��ʱ���������ݵ�� */
        unsigned short  reserved : 4;  /* bit[12-15]: ������ */
    } reg;
} SOC_UART_IOMCU_UARTDR_UNION;
#endif
#define SOC_UART_IOMCU_UARTDR_data_START      (0)
#define SOC_UART_IOMCU_UARTDR_data_END        (7)
#define SOC_UART_IOMCU_UARTDR_fe_START        (8)
#define SOC_UART_IOMCU_UARTDR_fe_END          (8)
#define SOC_UART_IOMCU_UARTDR_pe_START        (9)
#define SOC_UART_IOMCU_UARTDR_pe_END          (9)
#define SOC_UART_IOMCU_UARTDR_be_START        (10)
#define SOC_UART_IOMCU_UARTDR_be_END          (10)
#define SOC_UART_IOMCU_UARTDR_oe_START        (11)
#define SOC_UART_IOMCU_UARTDR_oe_END          (11)


/*****************************************************************************
 �ṹ��    : SOC_UART_IOMCU_UARTRSR_UARTECR_UNION
 �ṹ˵��  : UARTRSR_UARTECR �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x0000�����:16
 �Ĵ���˵��: ����״̬�Ĵ���/��������Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  fe       : 1;  /* bit[0]   : Framing����
                                                     0��д�Ĵ���UARTECR��
                                                     1�����յ����ַ���ֹͣλ������ЧֹͣλΪ1���� */
        unsigned short  pe       : 1;  /* bit[1]   : Parity����
                                                     0��д�Ĵ���UARTECR��
                                                     1���������ݵ�У�����ͼĴ���UARTLCR_H�е����ò�ƥ�䡣
                                                     FIFOģʽ�£��ô�����FIFO�������ַ�������� */
        unsigned short  be       : 1;  /* bit[2]   : Break����
                                                     0��д�Ĵ���UARTECR��
                                                     1��Break��������⵽����ʾ�������ݵ����뱣�ֵ͵�ʱ���һ��ȫ�ִ��䣨������start��data��parity��stop bit��ʱ�仹Ҫ����
                                                     ��Break����ʱ��ֻ��һ��0�ַ�����FIFO�С�ֻ�е����������Ϊ1��marking state������һ����Ч����ʼλ������ʱ����һ���ַ��ű�ʹ�ܡ�
                                                     FIFOģʽ�£��ô�����FIFO�������ַ�������� */
        unsigned short  oe       : 1;  /* bit[3]   : Overrun����
                                                     0��д�Ĵ���UARTECR��
                                                     1������FIFO���ҽ�����һ�����ݡ�
                                                     ��FIFO��ʱ��FIFO�е����ݱ�����Ч����Ϊ��������һ������д��FIFO�У�ֻ����λ�Ĵ����������CPU�������̶��������ڿ�FIFO�� */
        unsigned short  reserved_0: 1;  /* bit[4]   : ��������ʱ���������Ԥ֪������ */
        unsigned short  cer      : 3;  /* bit[5-7] : дʱ���framing��parity��break��overrun������д��ֵ��С�޹أ��� */
        unsigned short  reserved_1: 8;  /* bit[8-15]: ������ */
    } reg;
} SOC_UART_IOMCU_UARTRSR_UARTECR_UNION;
#endif
#define SOC_UART_IOMCU_UARTRSR_UARTECR_fe_START        (0)
#define SOC_UART_IOMCU_UARTRSR_UARTECR_fe_END          (0)
#define SOC_UART_IOMCU_UARTRSR_UARTECR_pe_START        (1)
#define SOC_UART_IOMCU_UARTRSR_UARTECR_pe_END          (1)
#define SOC_UART_IOMCU_UARTRSR_UARTECR_be_START        (2)
#define SOC_UART_IOMCU_UARTRSR_UARTECR_be_END          (2)
#define SOC_UART_IOMCU_UARTRSR_UARTECR_oe_START        (3)
#define SOC_UART_IOMCU_UARTRSR_UARTECR_oe_END          (3)
#define SOC_UART_IOMCU_UARTRSR_UARTECR_cer_START       (5)
#define SOC_UART_IOMCU_UARTRSR_UARTECR_cer_END         (7)


/*****************************************************************************
 �ṹ��    : SOC_UART_IOMCU_UARTFR_UNION
 �ṹ˵��  : UARTFR �Ĵ����ṹ���塣��ַƫ����:0x018����ֵ:0x0091�����:16
 �Ĵ���˵��: ��ǩ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  cts      : 1;  /* bit[0]   : UART ������clear to send��
                                                     ��λ��UART clear to send modem status��nUARTCTS����ȡ������Modem״̬������Ϊ0����λΪ1�� */
        unsigned short  reserved_0: 2;  /* bit[1-2] : ������ */
        unsigned short  busy     : 1;  /* bit[3]   : UART busy��ǡ�
                                                     0��UART is not busy��
                                                     1��UART���ڷ������ݡ���λһֱ���ֵ������ֽڣ��������е�ֹͣλ������λ�Ĵ����з��ͳ�ȥ��
                                                     һ������FIFO�ǿգ���λ����λ����UART�Ƿ�ʹ���޹ء� */
        unsigned short  rxfe     : 1;  /* bit[4]   : ����ȡ���ڼĴ���UARTLCR_H[fen]ֵ��
                                                     l FIFO��ֹ�������ձ��ּĴ�����ʱ����λ��λ��
                                                     l FIFOʹ�ܣ�������FIFOΪ��ʱ����λ��λ�� */
        unsigned short  txff     : 1;  /* bit[5]   : ����ȡ���ڼĴ���UARTLCR_H[fen]ֵ��
                                                     l FIFO��ֹ�������ͱ��ּĴ�����ʱ����λ��λ��
                                                     l FIFOʹ�ܣ�������FIFOΪ��ʱ����λ��λ�� */
        unsigned short  rxff     : 1;  /* bit[6]   : ����ȡ���ڼĴ���UARTLCR_H[fen]ֵ��
                                                     l FIFO��ֹ�������ձ��ּĴ�����ʱ����λ��λ��
                                                     l FIFOʹ�ܣ�������FIFOΪ��ʱ����λ��λ�� */
        unsigned short  txfe     : 1;  /* bit[7]   : ����ȡ���ڼĴ���UARTLCR_H[fen]ֵ��
                                                     l FIFO��ֹ�������ͱ��ּĴ�����ʱ����λ��λ��
                                                     l FIFOʹ�ܣ�������FIFOΪ��ʱ����λ��λ�� */
        unsigned short  reserved_1: 8;  /* bit[8-15]: ������ */
    } reg;
} SOC_UART_IOMCU_UARTFR_UNION;
#endif
#define SOC_UART_IOMCU_UARTFR_cts_START       (0)
#define SOC_UART_IOMCU_UARTFR_cts_END         (0)
#define SOC_UART_IOMCU_UARTFR_busy_START      (3)
#define SOC_UART_IOMCU_UARTFR_busy_END        (3)
#define SOC_UART_IOMCU_UARTFR_rxfe_START      (4)
#define SOC_UART_IOMCU_UARTFR_rxfe_END        (4)
#define SOC_UART_IOMCU_UARTFR_txff_START      (5)
#define SOC_UART_IOMCU_UARTFR_txff_END        (5)
#define SOC_UART_IOMCU_UARTFR_rxff_START      (6)
#define SOC_UART_IOMCU_UARTFR_rxff_END        (6)
#define SOC_UART_IOMCU_UARTFR_txfe_START      (7)
#define SOC_UART_IOMCU_UARTFR_txfe_END        (7)


/*****************************************************************************
 �ṹ��    : SOC_UART_IOMCU_UARTLPR_UNION
 �ṹ˵��  : UARTLPR �Ĵ����ṹ���塣��ַƫ����:0x020����ֵ:0x0000�����:16
 �Ĵ���˵��: IrDA�͹��ļ������Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  lrda     : 8;  /* bit[0-7] : 8bit�͹��ķ�Ƶֵ�� */
        unsigned short  reserved : 8;  /* bit[8-15]: ������ */
    } reg;
} SOC_UART_IOMCU_UARTLPR_UNION;
#endif
#define SOC_UART_IOMCU_UARTLPR_lrda_START      (0)
#define SOC_UART_IOMCU_UARTLPR_lrda_END        (7)


/*****************************************************************************
 �ṹ��    : SOC_UART_IOMCU_UARTIBRD_UNION
 �ṹ˵��  : UARTIBRD �Ĵ����ṹ���塣��ַƫ����:0x024����ֵ:0x0000�����:16
 �Ĵ���˵��: �����ʼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  baud_divint : 16; /* bit[0-15]: �����ʷ�Ƶֵ���������֡� */
    } reg;
} SOC_UART_IOMCU_UARTIBRD_UNION;
#endif
#define SOC_UART_IOMCU_UARTIBRD_baud_divint_START  (0)
#define SOC_UART_IOMCU_UARTIBRD_baud_divint_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_UART_IOMCU_UARTFBRD_UNION
 �ṹ˵��  : UARTFBRD �Ĵ����ṹ���塣��ַƫ����:0x028����ֵ:0x0000�����:16
 �Ĵ���˵��: �����ʼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  baud_divfrac : 6;  /* bit[0-5] : �����ʷ�Ƶֵ��С�����֡� */
        unsigned short  reserved     : 10; /* bit[6-15]: ������ */
    } reg;
} SOC_UART_IOMCU_UARTFBRD_UNION;
#endif
#define SOC_UART_IOMCU_UARTFBRD_baud_divfrac_START  (0)
#define SOC_UART_IOMCU_UARTFBRD_baud_divfrac_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_UART_IOMCU_UARTLCR_H_UNION
 �ṹ˵��  : UARTLCR_H �Ĵ����ṹ���塣��ַƫ����:0x02C����ֵ:0x0000�����:16
 �Ĵ���˵��: �߿أ�line control���Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  brk      : 1;  /* bit[0]   : Send break��
                                                     0������ɵ�ǰ�ַ��ķ��ͺ�UART���Ͷ˲�����������͵�ƽ��
                                                     1������ɵ�ǰ�ַ��ķ��ͺ�UART���Ͷ���������͵�ƽ��Ҫ��ȷ��ִ��Break����������λ�á�1����ʱ����볬��2������֡��
                                                     ������ʹ���У���λ�������㡣 */
        unsigned short  pen      : 1;  /* bit[1]   : У��ʹ�ܡ�
                                                     0������У�飻
                                                     1�����ͷ������У�飬���շ�����У�顣 */
        unsigned short  eps      : 1;  /* bit[2]   : ��żУ��ѡ��
                                                     0���ڷ��ͺͽ��չ�����������У�������У�飻
                                                     1���ڷ��ͺͽ��չ���������żУ�����żУ�顣
                                                     ��penΪ��0��ʱ����λ�������á� */
        unsigned short  stp2     : 1;  /* bit[3]   : ѡ��2bit��ֹͣλ��
                                                     0�����ͺͽ���FIFO��ֹ��
                                                     1�����͵�֡β��2bit��ֹͣλ��
                                                     �����߼��ڽ���ʱ�����2bit��ֹͣλ�� */
        unsigned short  fen      : 1;  /* bit[4]   : FIFOʹ�ܡ�
                                                     0�����ͺͽ���FIFO��ֹ��
                                                     1�����ͺͽ���FIFOʹ�ܡ� */
        unsigned short  wlen     : 2;  /* bit[5-6] : ���ͺͽ���һ֡������λ����Ŀ��
                                                     00��5bit��
                                                     01��6bit��
                                                     10��7bit��
                                                     11��8bit�� */
        unsigned short  sps      : 1;  /* bit[7]   : Stick parityѡ��
                                                     0��bit[1]��bit[2]��bit[7]����λ��
                                                     1��bit[1]��bit[7]����λ��bit[2]Ϊ��0����
                                                     ��bit[1]��bit[2]��bit[7]�������㣬��Stick parity��ֹ�� */
        unsigned short  reserved : 8;  /* bit[8-15]: ������ */
    } reg;
} SOC_UART_IOMCU_UARTLCR_H_UNION;
#endif
#define SOC_UART_IOMCU_UARTLCR_H_brk_START       (0)
#define SOC_UART_IOMCU_UARTLCR_H_brk_END         (0)
#define SOC_UART_IOMCU_UARTLCR_H_pen_START       (1)
#define SOC_UART_IOMCU_UARTLCR_H_pen_END         (1)
#define SOC_UART_IOMCU_UARTLCR_H_eps_START       (2)
#define SOC_UART_IOMCU_UARTLCR_H_eps_END         (2)
#define SOC_UART_IOMCU_UARTLCR_H_stp2_START      (3)
#define SOC_UART_IOMCU_UARTLCR_H_stp2_END        (3)
#define SOC_UART_IOMCU_UARTLCR_H_fen_START       (4)
#define SOC_UART_IOMCU_UARTLCR_H_fen_END         (4)
#define SOC_UART_IOMCU_UARTLCR_H_wlen_START      (5)
#define SOC_UART_IOMCU_UARTLCR_H_wlen_END        (6)
#define SOC_UART_IOMCU_UARTLCR_H_sps_START       (7)
#define SOC_UART_IOMCU_UARTLCR_H_sps_END         (7)


/*****************************************************************************
 �ṹ��    : SOC_UART_IOMCU_UARTCR_UNION
 �ṹ˵��  : UARTCR �Ĵ����ṹ���塣��ַƫ����:0x030����ֵ:0x0300�����:16
 �Ĵ���˵��: ���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  uarten   : 1;  /* bit[0]    : ʹ��UART��
                                                      0��UART��ʹ�ܡ�
                                                      1��UARTʹ�ܡ�����ͨ��UART���źŻ�SIR���źţ�ȡ����[SIREN]�����ã����з��ͺͽ��ա�
                                                      ����ڷ��ͺͽ��չ����н�ֹUART��������ֹ֮ͣǰ������ǰ�ַ��Ĵ��͡� */
        unsigned short  siren    : 1;  /* bit[1]    : ʹ��IrDA SIR���롣
                                                      0��IrDA SIR���벻ʹ�ܡ�
                                                      1��IrDA SIR����ʹ�ܣ����UARTû��ʹ�ܣ����λ�������á�
                                                      IrDA SIR����ʹ�ܣ����ݴ�nSIROUT���ͣ���SIRIN���ա�UARTTXD����marking state����Ϊ��1��������UARTRXD�ϵ��źź�modem״̬���벻�����á�
                                                      IrDA SIR�����ֹ��nSIROUT����Ϊ0�������͹����壩��SIRIN������źŲ������á� */
        unsigned short  sirlp    : 1;  /* bit[2]    : SIR�͹���ģʽ����λѡ��IrDA�ı���ģʽ��
                                                      0���͵�ƽ�����Կ��Ϊ3/16�������ڵ����壨����Ч�����з��ͣ�
                                                      1���͵�ƽ�����Կ��Ϊ3��IrPBaud16���ڵ�������з��͡�
                                                      ��λ�á�1�����Խ��͹��ģ���Ҳ�����̷��͵ľ��롣 */
        unsigned short  reserved_0: 4;  /* bit[3-6]  : ���������޸ġ� */
        unsigned short  lbe      : 1;  /* bit[7]    : ʹ��Loop Back��
                                                      0��Loop Back��ʹ�ܡ�
                                                      1��Loop Backʹ�ܡ�
                                                      ��λʱ��λ���㡣 */
        unsigned short  txe      : 1;  /* bit[8]    : ʹ��UART���͡�
                                                      0����ʹ��UART���͡�
                                                      1��UART����ʹ�ܡ�UART��SIR��ȡ����[siren]�����ã���ʼ�������ݡ�
                                                      �ڷ��͹��������UART����ֹ����ǰ�ַ��ķ���������ֹ֮ͣǰ������ */
        unsigned short  rxe      : 1;  /* bit[9]    : ʹ��UART���ա�
                                                      0����ʹ��UART���ա�
                                                      1��UART����ʹ�ܡ�UART��SIR��ȡ����[siren]�����ã���ʼ�������ݡ�
                                                      �ڽ��չ��������UART����ֹ����ǰ�ַ��Ľ���������ֹ֮ͣǰ������ */
        unsigned short  reserved_1: 1;  /* bit[10]   : ������ */
        unsigned short  rts      : 1;  /* bit[11]   : UART request to Send��
                                                      ��λΪUART Request to Send modem status�źţ�nUARTRTS����ȡ��������λΪ��1��ʱ����ź�Ϊ��0���� */
        unsigned short  reserved_2: 2;  /* bit[12-13]: ������ */
        unsigned short  rtsen    : 1;  /* bit[14]   : ʹ��RTSӲ�����ء�
                                                      0����ʹ��RTSӲ�����ء�
                                                      1��ʹ��RTSӲ�����أ�ֻ�е�����FIFO�пռ�ʱ������������ݡ� */
        unsigned short  ctsen    : 1;  /* bit[15]   : ʹ��CTSӲ�����ء�
                                                      0����ʹ��CTSӲ�����ء�
                                                      1��ʹ��CTSӲ�����أ�ֻ�е�nUARTCTS�ź���Чʱ�ŷ������ݡ� */
    } reg;
} SOC_UART_IOMCU_UARTCR_UNION;
#endif
#define SOC_UART_IOMCU_UARTCR_uarten_START    (0)
#define SOC_UART_IOMCU_UARTCR_uarten_END      (0)
#define SOC_UART_IOMCU_UARTCR_siren_START     (1)
#define SOC_UART_IOMCU_UARTCR_siren_END       (1)
#define SOC_UART_IOMCU_UARTCR_sirlp_START     (2)
#define SOC_UART_IOMCU_UARTCR_sirlp_END       (2)
#define SOC_UART_IOMCU_UARTCR_lbe_START       (7)
#define SOC_UART_IOMCU_UARTCR_lbe_END         (7)
#define SOC_UART_IOMCU_UARTCR_txe_START       (8)
#define SOC_UART_IOMCU_UARTCR_txe_END         (8)
#define SOC_UART_IOMCU_UARTCR_rxe_START       (9)
#define SOC_UART_IOMCU_UARTCR_rxe_END         (9)
#define SOC_UART_IOMCU_UARTCR_rts_START       (11)
#define SOC_UART_IOMCU_UARTCR_rts_END         (11)
#define SOC_UART_IOMCU_UARTCR_rtsen_START     (14)
#define SOC_UART_IOMCU_UARTCR_rtsen_END       (14)
#define SOC_UART_IOMCU_UARTCR_ctsen_START     (15)
#define SOC_UART_IOMCU_UARTCR_ctsen_END       (15)


/*****************************************************************************
 �ṹ��    : SOC_UART_IOMCU_UARTIFLS_UNION
 �ṹ˵��  : UARTIFLS �Ĵ����ṹ���塣��ַƫ����:0x034����ֵ:0x0012�����:16
 �Ĵ���˵��: �ж�FIFO levelѡ��Ĵ�����
            ����FIFO�ͽ���FIFO����ȶ���16��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  txiflsel : 3;  /* bit[0-2] : �����ж�FIFO��levelѡ�񣬷����жϵĴ��������¡�
                                                     000������FIFO��ʼ?1/8 full��
                                                     001������FIFO��ʼ?1/4 full��
                                                     011������FIFO��ʼ?3/4 full��
                                                     100������FIFO��ʼ?7/8 full��
                                                     101��111�������� */
        unsigned short  rxiflsel : 3;  /* bit[3-5] : �����ж�FIFO��levelѡ�񣬽����жϵĴ��������¡�
                                                     000������FIFO��ʼ|1/8 full��
                                                     001������FIFO��ʼ|1/4 full��
                                                     010������FIFO��ʼ|1/2 full��
                                                     011������FIFO��ʼ|3/4 full��
                                                     100������FIFO��ʼ|7/8 full��
                                                     101��111�������� */
        unsigned short  reserved : 10; /* bit[6-15]: ������ */
    } reg;
} SOC_UART_IOMCU_UARTIFLS_UNION;
#endif
#define SOC_UART_IOMCU_UARTIFLS_txiflsel_START  (0)
#define SOC_UART_IOMCU_UARTIFLS_txiflsel_END    (2)
#define SOC_UART_IOMCU_UARTIFLS_rxiflsel_START  (3)
#define SOC_UART_IOMCU_UARTIFLS_rxiflsel_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_UART_IOMCU_UARTIMSC_UNION
 �ṹ˵��  : UARTIMSC �Ĵ����ṹ���塣��ַƫ����:0x038����ֵ:0x0000�����:16
 �Ĵ���˵��: �ж����ε�����/���ѡ��Ĵ�����
            ֵ��0����ʾ�жϱ����Σ�ֵ��1����ʾ�жϱ����á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  reserved_0: 1;  /* bit[0]    : ������ */
        unsigned short  ctsmim   : 1;  /* bit[1]    : nUARTCTS modem�жϵ�����״̬�� */
        unsigned short  reserved_1: 2;  /* bit[2-3]  : ������ */
        unsigned short  rxim     : 1;  /* bit[4]    : �����жϵ�����״̬�� */
        unsigned short  txim     : 1;  /* bit[5]    : �����жϵ�����״̬�� */
        unsigned short  rtim     : 1;  /* bit[6]    : ���ճ�ʱ�жϵ�����״̬�� */
        unsigned short  feim     : 1;  /* bit[7]    : Framing�����жϵ�����״̬�� */
        unsigned short  peim     : 1;  /* bit[8]    : Parity�����жϵ�����״̬�� */
        unsigned short  beim     : 1;  /* bit[9]    : Break�����жϵ�����״̬�� */
        unsigned short  oeim     : 1;  /* bit[10]   : Overrun�����жϵ�����״̬�� */
        unsigned short  reserved_2: 5;  /* bit[11-15]: ������ */
    } reg;
} SOC_UART_IOMCU_UARTIMSC_UNION;
#endif
#define SOC_UART_IOMCU_UARTIMSC_ctsmim_START    (1)
#define SOC_UART_IOMCU_UARTIMSC_ctsmim_END      (1)
#define SOC_UART_IOMCU_UARTIMSC_rxim_START      (4)
#define SOC_UART_IOMCU_UARTIMSC_rxim_END        (4)
#define SOC_UART_IOMCU_UARTIMSC_txim_START      (5)
#define SOC_UART_IOMCU_UARTIMSC_txim_END        (5)
#define SOC_UART_IOMCU_UARTIMSC_rtim_START      (6)
#define SOC_UART_IOMCU_UARTIMSC_rtim_END        (6)
#define SOC_UART_IOMCU_UARTIMSC_feim_START      (7)
#define SOC_UART_IOMCU_UARTIMSC_feim_END        (7)
#define SOC_UART_IOMCU_UARTIMSC_peim_START      (8)
#define SOC_UART_IOMCU_UARTIMSC_peim_END        (8)
#define SOC_UART_IOMCU_UARTIMSC_beim_START      (9)
#define SOC_UART_IOMCU_UARTIMSC_beim_END        (9)
#define SOC_UART_IOMCU_UARTIMSC_oeim_START      (10)
#define SOC_UART_IOMCU_UARTIMSC_oeim_END        (10)


/*****************************************************************************
 �ṹ��    : SOC_UART_IOMCU_UARTRIS_UNION
 �ṹ˵��  : UARTRIS �Ĵ����ṹ���塣��ַƫ����:0x03C����ֵ:0x0000�����:16
 �Ĵ���˵��: ԭʼ�ж�״̬�Ĵ�����
            ��λʱ����modem�жϣ�bit[1]���⣬����bitȫ�����㡣modem�жϸ�λ��״̬��ȷ����ֵ��0����ʾ���ж�δ������ֵ��1����ʾ���ж��Ѵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  reserved_0: 1;  /* bit[0]    : ������ */
        unsigned short  ctsmris  : 1;  /* bit[1]    : ԭʼ��nUARTCTS modem�ж�״̬�� */
        unsigned short  reserved_1: 2;  /* bit[2-3]  : ������ */
        unsigned short  rxris    : 1;  /* bit[4]    : ԭʼ�Ľ����ж�״̬�� */
        unsigned short  txris    : 1;  /* bit[5]    : ԭʼ�ķ����ж�״̬�� */
        unsigned short  rtris    : 1;  /* bit[6]    : ԭʼ�Ľ��ճ�ʱ�ж�״̬�� */
        unsigned short  feris    : 1;  /* bit[7]    : ԭʼ��Framing�����ж�״̬�� */
        unsigned short  peris    : 1;  /* bit[8]    : ԭʼ��Parity�����ж�״̬�� */
        unsigned short  beris    : 1;  /* bit[9]    : ԭʼ��Break�����ж�״̬�� */
        unsigned short  oeris    : 1;  /* bit[10]   : ԭʼ��Overrun�����ж�״̬�� */
        unsigned short  reserved_2: 5;  /* bit[11-15]: ������ */
    } reg;
} SOC_UART_IOMCU_UARTRIS_UNION;
#endif
#define SOC_UART_IOMCU_UARTRIS_ctsmris_START   (1)
#define SOC_UART_IOMCU_UARTRIS_ctsmris_END     (1)
#define SOC_UART_IOMCU_UARTRIS_rxris_START     (4)
#define SOC_UART_IOMCU_UARTRIS_rxris_END       (4)
#define SOC_UART_IOMCU_UARTRIS_txris_START     (5)
#define SOC_UART_IOMCU_UARTRIS_txris_END       (5)
#define SOC_UART_IOMCU_UARTRIS_rtris_START     (6)
#define SOC_UART_IOMCU_UARTRIS_rtris_END       (6)
#define SOC_UART_IOMCU_UARTRIS_feris_START     (7)
#define SOC_UART_IOMCU_UARTRIS_feris_END       (7)
#define SOC_UART_IOMCU_UARTRIS_peris_START     (8)
#define SOC_UART_IOMCU_UARTRIS_peris_END       (8)
#define SOC_UART_IOMCU_UARTRIS_beris_START     (9)
#define SOC_UART_IOMCU_UARTRIS_beris_END       (9)
#define SOC_UART_IOMCU_UARTRIS_oeris_START     (10)
#define SOC_UART_IOMCU_UARTRIS_oeris_END       (10)


/*****************************************************************************
 �ṹ��    : SOC_UART_IOMCU_UARTMIS_UNION
 �ṹ˵��  : UARTMIS �Ĵ����ṹ���塣��ַƫ����:0x040����ֵ:0x0000�����:16
 �Ĵ���˵��: ���κ��ж�״̬�Ĵ�����
            ��λʱ����modem�жϣ�bit[1]���⣬����bitȫ�����㡣modem�жϸ�λ��״̬��ȷ����ֵ��0����ʾ���ж�δ������ֵ��1����ʾ���ж��Ѵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  reserved_0: 1;  /* bit[0]    : ������ */
        unsigned short  ctsmmis  : 1;  /* bit[1]    : ���κ��nUARTCTS modem�ж�״̬�� */
        unsigned short  reserved_1: 2;  /* bit[2-3]  : ������ */
        unsigned short  rxmis    : 1;  /* bit[4]    : ���κ�Ľ����ж�״̬�� */
        unsigned short  txmis    : 1;  /* bit[5]    : ���κ�ķ����ж�״̬�� */
        unsigned short  rtmis    : 1;  /* bit[6]    : ���κ�Ľ��ճ�ʱ�ж�״̬�� */
        unsigned short  femis    : 1;  /* bit[7]    : ���κ��Framing�����ж�״̬�� */
        unsigned short  pemis    : 1;  /* bit[8]    : ���κ��Parity�����ж�״̬�� */
        unsigned short  bemis    : 1;  /* bit[9]    : ���κ��Break�����ж�״̬�� */
        unsigned short  oemis    : 1;  /* bit[10]   : ���κ��Overrun�����ж�״̬�� */
        unsigned short  reserved_2: 5;  /* bit[11-15]: ������ */
    } reg;
} SOC_UART_IOMCU_UARTMIS_UNION;
#endif
#define SOC_UART_IOMCU_UARTMIS_ctsmmis_START   (1)
#define SOC_UART_IOMCU_UARTMIS_ctsmmis_END     (1)
#define SOC_UART_IOMCU_UARTMIS_rxmis_START     (4)
#define SOC_UART_IOMCU_UARTMIS_rxmis_END       (4)
#define SOC_UART_IOMCU_UARTMIS_txmis_START     (5)
#define SOC_UART_IOMCU_UARTMIS_txmis_END       (5)
#define SOC_UART_IOMCU_UARTMIS_rtmis_START     (6)
#define SOC_UART_IOMCU_UARTMIS_rtmis_END       (6)
#define SOC_UART_IOMCU_UARTMIS_femis_START     (7)
#define SOC_UART_IOMCU_UARTMIS_femis_END       (7)
#define SOC_UART_IOMCU_UARTMIS_pemis_START     (8)
#define SOC_UART_IOMCU_UARTMIS_pemis_END       (8)
#define SOC_UART_IOMCU_UARTMIS_bemis_START     (9)
#define SOC_UART_IOMCU_UARTMIS_bemis_END       (9)
#define SOC_UART_IOMCU_UARTMIS_oemis_START     (10)
#define SOC_UART_IOMCU_UARTMIS_oemis_END       (10)


/*****************************************************************************
 �ṹ��    : SOC_UART_IOMCU_UARTICR_UNION
 �ṹ˵��  : UARTICR �Ĵ����ṹ���塣��ַƫ����:0x044����ֵ:0x0000�����:16
 �Ĵ���˵��: �ж�����Ĵ�����
            д��1�������Ӧ�жϣ�д��0���������á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  reserved_0: 1;  /* bit[0]    : ������ */
        unsigned short  ctsic    : 1;  /* bit[1]    : ���nUARTCTS modem�жϡ� */
        unsigned short  reserved_1: 2;  /* bit[2-3]  : ������ */
        unsigned short  rxic     : 1;  /* bit[4]    : ��������жϡ� */
        unsigned short  txic     : 1;  /* bit[5]    : ��������жϡ� */
        unsigned short  rtic     : 1;  /* bit[6]    : ������ճ�ʱ�жϡ� */
        unsigned short  feic     : 1;  /* bit[7]    : ���Framing�����жϡ� */
        unsigned short  peic     : 1;  /* bit[8]    : ���Parity�����жϡ� */
        unsigned short  beic     : 1;  /* bit[9]    : ���Break�����жϡ� */
        unsigned short  oeic     : 1;  /* bit[10]   : ���Overrun�����жϡ� */
        unsigned short  reserved_2: 5;  /* bit[11-15]: ������ */
    } reg;
} SOC_UART_IOMCU_UARTICR_UNION;
#endif
#define SOC_UART_IOMCU_UARTICR_ctsic_START     (1)
#define SOC_UART_IOMCU_UARTICR_ctsic_END       (1)
#define SOC_UART_IOMCU_UARTICR_rxic_START      (4)
#define SOC_UART_IOMCU_UARTICR_rxic_END        (4)
#define SOC_UART_IOMCU_UARTICR_txic_START      (5)
#define SOC_UART_IOMCU_UARTICR_txic_END        (5)
#define SOC_UART_IOMCU_UARTICR_rtic_START      (6)
#define SOC_UART_IOMCU_UARTICR_rtic_END        (6)
#define SOC_UART_IOMCU_UARTICR_feic_START      (7)
#define SOC_UART_IOMCU_UARTICR_feic_END        (7)
#define SOC_UART_IOMCU_UARTICR_peic_START      (8)
#define SOC_UART_IOMCU_UARTICR_peic_END        (8)
#define SOC_UART_IOMCU_UARTICR_beic_START      (9)
#define SOC_UART_IOMCU_UARTICR_beic_END        (9)
#define SOC_UART_IOMCU_UARTICR_oeic_START      (10)
#define SOC_UART_IOMCU_UARTICR_oeic_END        (10)


/*****************************************************************************
 �ṹ��    : SOC_UART_IOMCU_UARTDMACR_UNION
 �ṹ˵��  : UARTDMACR �Ĵ����ṹ���塣��ַƫ����:0x048����ֵ:0x0000�����:16
 �Ĵ���˵��: DMA���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  rxdmae   : 1;  /* bit[0]   : ����FIFO��DMAʹ�ܡ�
                                                     0����ʹ�ܽ���FIFO��DMA��
                                                     1��ʹ�ܽ���FIFO��DMA�� */
        unsigned short  txdmae   : 1;  /* bit[1]   : ����FIFO��DMAʹ�ܡ�
                                                     0����ʹ�ܷ���FIFO��DMA��
                                                     1��ʹ�ܷ���FIFO��DMA�� */
        unsigned short  dmaonerr : 1;  /* bit[2]   : DMA on Error��
                                                     0����UART�����ж���Чʱ��DMA�����������UARTRXDMASREQ��UARTRXDMABREQ��ʹ�ܡ�
                                                     1����UART�����ж���Чʱ��DMA�����������UARTRXDMASREQ��UARTRXDMABREQ����ʹ�ܡ� */
        unsigned short  reserved : 13; /* bit[3-15]: ������ */
    } reg;
} SOC_UART_IOMCU_UARTDMACR_UNION;
#endif
#define SOC_UART_IOMCU_UARTDMACR_rxdmae_START    (0)
#define SOC_UART_IOMCU_UARTDMACR_rxdmae_END      (0)
#define SOC_UART_IOMCU_UARTDMACR_txdmae_START    (1)
#define SOC_UART_IOMCU_UARTDMACR_txdmae_END      (1)
#define SOC_UART_IOMCU_UARTDMACR_dmaonerr_START  (2)
#define SOC_UART_IOMCU_UARTDMACR_dmaonerr_END    (2)






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

#endif /* end of soc_uart_iomcu_interface.h */
