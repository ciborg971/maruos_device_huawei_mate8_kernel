/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_sd_sdio_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:22:52
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_SD_SDIO.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_SD_SDIO_INTERFACE_H__
#define __SOC_SD_SDIO_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) register_sd_sdio
 ****************************************************************************/
/* �Ĵ���˵�������ƼĴ�����
   λ����UNION�ṹ:  SOC_SD_SDIO_CTRL_UNION */
#define SOC_SD_SDIO_CTRL_ADDR(base)                   ((base) + (0x000))

/* �Ĵ���˵����ʱ�ӷ�Ƶϵ���Ĵ�����
   λ����UNION�ṹ:  SOC_SD_SDIO_CLKDIV_UNION */
#define SOC_SD_SDIO_CLKDIV_ADDR(base)                 ((base) + (0x008))

/* �Ĵ���˵����ʱ��ʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_SD_SDIO_CLKENA_UNION */
#define SOC_SD_SDIO_CLKENA_ADDR(base)                 ((base) + (0x010))

/* �Ĵ���˵������ʱ�Ĵ�����
   λ����UNION�ṹ:  SOC_SD_SDIO_TMOUT_UNION */
#define SOC_SD_SDIO_TMOUT_ADDR(base)                  ((base) + (0x014))

/* �Ĵ���˵���������ͼĴ�����
   λ����UNION�ṹ:  SOC_SD_SDIO_CTYPE_UNION */
#define SOC_SD_SDIO_CTYPE_ADDR(base)                  ((base) + (0x018))

/* �Ĵ���˵�������С���üĴ�����
   λ����UNION�ṹ:  SOC_SD_SDIO_BLKSIZ_UNION */
#define SOC_SD_SDIO_BLKSIZ_ADDR(base)                 ((base) + (0x01C))

/* �Ĵ���˵�����ֽ����Ĵ�����
   λ����UNION�ṹ:  SOC_SD_SDIO_BYTCNT_UNION */
#define SOC_SD_SDIO_BYTCNT_ADDR(base)                 ((base) + (0x020))

/* �Ĵ���˵�����ж����μĴ�����
   λ����UNION�ṹ:  SOC_SD_SDIO_INTMASK_UNION */
#define SOC_SD_SDIO_INTMASK_ADDR(base)                ((base) + (0x024))

/* �Ĵ���˵������������Ĵ�����
   λ����UNION�ṹ:  SOC_SD_SDIO_CMDARG_UNION */
#define SOC_SD_SDIO_CMDARG_ADDR(base)                 ((base) + (0x028))

/* �Ĵ���˵��������Ĵ�����
   λ����UNION�ṹ:  SOC_SD_SDIO_CMD_UNION */
#define SOC_SD_SDIO_CMD_ADDR(base)                    ((base) + (0x02C))

/* �Ĵ���˵������Ӧ�Ĵ���0��
   λ����UNION�ṹ:  SOC_SD_SDIO_RESP0_UNION */
#define SOC_SD_SDIO_RESP0_ADDR(base)                  ((base) + (0x030))

/* �Ĵ���˵������Ӧ�Ĵ���1��
   λ����UNION�ṹ:  SOC_SD_SDIO_RESP1_UNION */
#define SOC_SD_SDIO_RESP1_ADDR(base)                  ((base) + (0x034))

/* �Ĵ���˵������Ӧ�Ĵ���2��
   λ����UNION�ṹ:  SOC_SD_SDIO_RESP2_UNION */
#define SOC_SD_SDIO_RESP2_ADDR(base)                  ((base) + (0x038))

/* �Ĵ���˵������Ӧ�Ĵ���3��
   λ����UNION�ṹ:  SOC_SD_SDIO_RESP3_UNION */
#define SOC_SD_SDIO_RESP3_ADDR(base)                  ((base) + (0x03C))

/* �Ĵ���˵�������κ��ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SD_SDIO_MINTSTS_UNION */
#define SOC_SD_SDIO_MINTSTS_ADDR(base)                ((base) + (0x040))

/* �Ĵ���˵����ԭʼ�ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SD_SDIO_RINTSTS_UNION */
#define SOC_SD_SDIO_RINTSTS_ADDR(base)                ((base) + (0x044))

/* �Ĵ���˵��������״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SD_SDIO_STATUS_UNION */
#define SOC_SD_SDIO_STATUS_ADDR(base)                 ((base) + (0x048))

/* �Ĵ���˵����FIFOˮ��ֵ�Ĵ�����
   λ����UNION�ṹ:  SOC_SD_SDIO_FIFOTH_UNION */
#define SOC_SD_SDIO_FIFOTH_ADDR(base)                 ((base) + (0x04C))

/* �Ĵ���˵����ʱ�����üĴ���
   λ����UNION�ṹ:  SOC_SD_SDIO_GPIO_UNION */
#define SOC_SD_SDIO_GPIO_ADDR(base)                   ((base) + (0x058))

/* �Ĵ���˵�������͵�������byte��Ŀ�Ĵ�����
   λ����UNION�ṹ:  SOC_SD_SDIO_TCBCNT_UNION */
#define SOC_SD_SDIO_TCBCNT_ADDR(base)                 ((base) + (0x05C))

/* �Ĵ���˵����BIU FIFO�������ݵ�byte���Ĵ�����
   λ����UNION�ṹ:  SOC_SD_SDIO_TTBCNT_UNION */
#define SOC_SD_SDIO_TTBCNT_ADDR(base)                 ((base) + (0x060))

/* �Ĵ���˵�����û�ID�Ĵ�����
   λ����UNION�ṹ:  SOC_SD_SDIO_USRID_UNION */
#define SOC_SD_SDIO_USRID_ADDR(base)                  ((base) + (0x068))

/* �Ĵ���˵�����汾�Ĵ�����
   λ����UNION�ṹ:  SOC_SD_SDIO_VERID_UNION */
#define SOC_SD_SDIO_VERID_ADDR(base)                  ((base) + (0x06C))

/* �Ĵ���˵�������ð汾�Ĵ�����
   λ����UNION�ṹ:  SOC_SD_SDIO_HCON_UNION */
#define SOC_SD_SDIO_HCON_ADDR(base)                   ((base) + (0x070))

/* �Ĵ���˵����UHS-1�Ĵ�����
   λ����UNION�ṹ:  SOC_SD_SDIO_UHS_REG_UNION */
#define SOC_SD_SDIO_UHS_REG_ADDR(base)                ((base) + (0x074))

/* �Ĵ���˵��������DMA���üĴ�����
   λ����UNION�ṹ:  SOC_SD_SDIO_BMOD_UNION */
#define SOC_SD_SDIO_BMOD_ADDR(base)                   ((base) + (0x080))

/* �Ĵ���˵������������Ĵ�����
   λ����UNION�ṹ:  SOC_SD_SDIO_PLDMND_UNION */
#define SOC_SD_SDIO_PLDMND_ADDR(base)                 ((base) + (0x084))

/* �Ĵ���˵����������ʼ��ַ�Ĵ�����
   λ����UNION�ṹ:  SOC_SD_SDIO_DBADDR_UNION */
#define SOC_SD_SDIO_DBADDR_ADDR(base)                 ((base) + (0x088))

/* �Ĵ���˵��������DMA״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SD_SDIO_IDSTS_UNION */
#define SOC_SD_SDIO_IDSTS_ADDR(base)                  ((base) + (0x08C))

/* �Ĵ���˵��������DMA�ж�ʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_SD_SDIO_IDINTEN_UNION */
#define SOC_SD_SDIO_IDINTEN_ADDR(base)                ((base) + (0x090))

/* �Ĵ���˵������ǰ����������ַ�Ĵ�����
   λ����UNION�ṹ:  SOC_SD_SDIO_DSCADDR_UNION */
#define SOC_SD_SDIO_DSCADDR_ADDR(base)                ((base) + (0x094))

/* �Ĵ���˵������ǰ������������ַ�Ĵ�����
   λ����UNION�ṹ:  SOC_SD_SDIO_BUFADDR_UNION */
#define SOC_SD_SDIO_BUFADDR_ADDR(base)                ((base) + (0x098))

/* �Ĵ���˵���������޿��ƼĴ�����
   λ����UNION�ṹ:  SOC_SD_SDIO_CARDTHRCTL_UNION */
#define SOC_SD_SDIO_CARDTHRCTL_ADDR(base)             ((base) + (0x100))

/* �Ĵ���˵����UHS��չ�Ĵ�����
   λ����UNION�ṹ:  SOC_SD_SDIO_UHS_REG_EXT_UNION */
#define SOC_SD_SDIO_UHS_REG_EXT_ADDR(base)            ((base) + (0x108))

/* �Ĵ���˵����EMMC4.5DDRģʽstartbit���ƼĴ���
   λ����UNION�ṹ:  SOC_SD_SDIO_EMMC_DDR_REG_UNION */
#define SOC_SD_SDIO_EMMC_DDR_REG_ADDR(base)           ((base) + (0x10C))

/* �Ĵ���˵����ENALBEƫ�ƼĴ�����
   λ����UNION�ṹ:  SOC_SD_SDIO_ENABLE_SHIFT_UNION */
#define SOC_SD_SDIO_ENABLE_SHIFT_ADDR(base)           ((base) + (0x110))





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
                     (1/1) register_sd_sdio
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_CTRL_UNION
 �ṹ˵��  : CTRL �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  controller_reset  : 1;  /* bit[0]    : 1'b0:��Ч��
                                                             1'b1:��λ��������
                                                             ��bit������AHBʱ�����ں�����cclk_inʱ�����ں��Զ����㡣
                                                             ��λ�Ķ���BIU/CIU�ӿڡ�CIU����״̬����CTRL�Ĵ�����abort_read_data��send_irq_response��read_waitλ��
                                                             ��bit���ڲ�DMA��FIFO���ж��߼���Ӱ�졣 */
        unsigned int  fifo_reset        : 1;  /* bit[1]    : 1'b0:��Ч��
                                                             1'b1:��λ����fifoָ�룻
                                                             ��λ��ɺ��bit�Զ����㡣 */
        unsigned int  dma_reset         : 1;  /* bit[2]    : 1'b0:��Ч��
                                                             1'b1:��λ�ڲ�DMA�����߼���
                                                             ��bit��AHB����ʱ�Ӻ��Զ������ */
        unsigned int  reserved_0        : 1;  /* bit[3]    : ������ */
        unsigned int  int_enable        : 1;  /* bit[4]    : 1'b0:��ֹȫ���жϣ�
                                                             1'b1:ʹ��ȫ���жϡ� */
        unsigned int  dma_enable        : 1;  /* bit[5]    : 1'b0:��ֹDMA����ģʽ��
                                                             1'b1:ʹ��DMA����ģʽ�� */
        unsigned int  read_wait         : 1;  /* bit[6]    : 1'b0:��ֹ���ȴ���
                                                             1'b1:ʹ�ܶ��ȴ���
                                                             �ڸ�SDIO�����Ͷ��ȴ�����ʱʹ�á� */
        unsigned int  send_irq_response : 1;  /* bit[7]    : 1'b0:��Ч��
                                                             1'b1:�����Զ�IRQ�ظ���
                                                             ���ظ��Ѿ����ͣ���bit�Զ����㡣
                                                             Ϊ�˵ȴ�MMC�����жϣ�����������ָ��CMD40���ȴ�����MMC���жϻظ���ͬʱ�����������ϣ����Ҫͣ�����жϵȴ�״̬���ɽ���bit�á�1��������ָ��CMD40���ص�IDLE״̬�� */
        unsigned int  abort_read_data   : 1;  /* bit[8]    : 1'b0:��Ч��
                                                             1'b1:��SDIO�������з���suspendָ��������ѯ���Ƿ������suspend״̬������ѯ������subpend��������轫��bit��1��ʹ���ݴ���״̬���ص�idle״̬���ȴ���һ���鴫�䡣
                                                             ״̬���ص�idle״̬�󣬴�bit�Զ����㡣 */
        unsigned int  reserved_1        : 16; /* bit[9-24] : ������ */
        unsigned int  use_internal_dmac : 1;  /* bit[25]   : 1'b0:ͨ��slave�ӿڰ������ݣ�
                                                             1'b1:ͨ���ڲ�DMAC�������ݡ� */
        unsigned int  reserved_2        : 6;  /* bit[26-31]: ������ */
    } reg;
} SOC_SD_SDIO_CTRL_UNION;
#endif
#define SOC_SD_SDIO_CTRL_controller_reset_START   (0)
#define SOC_SD_SDIO_CTRL_controller_reset_END     (0)
#define SOC_SD_SDIO_CTRL_fifo_reset_START         (1)
#define SOC_SD_SDIO_CTRL_fifo_reset_END           (1)
#define SOC_SD_SDIO_CTRL_dma_reset_START          (2)
#define SOC_SD_SDIO_CTRL_dma_reset_END            (2)
#define SOC_SD_SDIO_CTRL_int_enable_START         (4)
#define SOC_SD_SDIO_CTRL_int_enable_END           (4)
#define SOC_SD_SDIO_CTRL_dma_enable_START         (5)
#define SOC_SD_SDIO_CTRL_dma_enable_END           (5)
#define SOC_SD_SDIO_CTRL_read_wait_START          (6)
#define SOC_SD_SDIO_CTRL_read_wait_END            (6)
#define SOC_SD_SDIO_CTRL_send_irq_response_START  (7)
#define SOC_SD_SDIO_CTRL_send_irq_response_END    (7)
#define SOC_SD_SDIO_CTRL_abort_read_data_START    (8)
#define SOC_SD_SDIO_CTRL_abort_read_data_END      (8)
#define SOC_SD_SDIO_CTRL_use_internal_dmac_START  (25)
#define SOC_SD_SDIO_CTRL_use_internal_dmac_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_CLKDIV_UNION
 �ṹ˵��  : CLKDIV �Ĵ����ṹ���塣��ַƫ����:0x008����ֵ:0x00000000�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶϵ���Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  clk_divider0 : 8;  /* bit[0-7] : ʱ�ӷ�Ƶϵ����
                                                       ʱ�ӷ�Ƶϵ��ֵΪ2XN�����磬NΪ0����2X0���޷�Ƶ����NΪ0x1ʱΪ2��Ƶ��NΪ0xFFʱΪ512��Ƶ�� */
        unsigned int  reserved     : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_SD_SDIO_CLKDIV_UNION;
#endif
#define SOC_SD_SDIO_CLKDIV_clk_divider0_START  (0)
#define SOC_SD_SDIO_CLKDIV_clk_divider0_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_CLKENA_UNION
 �ṹ˵��  : CLKENA �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x00000000�����:32
 �Ĵ���˵��: ʱ��ʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cclk_enable    : 1;  /* bit[0]    : 1'b0:ʱ�ӽ�ֹ��
                                                          1'b1:ʱ��ʹ�ܡ� */
        unsigned int  reserved_0     : 15; /* bit[1-15] : ������ */
        unsigned int  cclk_low_power : 1;  /* bit[16]   : 1'b0:��ֹ�͹���ģʽ
                                                          1'b1:ʹ�ܵ͹���ģʽ
                                                          ��MMC��SD����������idleģʽʱֹͣʱ�ӣ�SDIO���������Ҫ����жϣ���ʼ�ղ�����ֹͣ�� */
        unsigned int  reserved_1     : 15; /* bit[17-31]: ������ */
    } reg;
} SOC_SD_SDIO_CLKENA_UNION;
#endif
#define SOC_SD_SDIO_CLKENA_cclk_enable_START     (0)
#define SOC_SD_SDIO_CLKENA_cclk_enable_END       (0)
#define SOC_SD_SDIO_CLKENA_cclk_low_power_START  (16)
#define SOC_SD_SDIO_CLKENA_cclk_low_power_END    (16)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_TMOUT_UNION
 �ṹ˵��  : TMOUT �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0xFFFFFF40�����:32
 �Ĵ���˵��: ��ʱ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  response_timeout : 8;  /* bit[0-7] : Response��timeoutʱ��
                                                           ��ֵΪcclk_out�������� */
        unsigned int  data_timeout     : 24; /* bit[8-31]: �������ݵ�Timeoutʱ��
                                                           ��ֵΪcclk_out���������� */
    } reg;
} SOC_SD_SDIO_TMOUT_UNION;
#endif
#define SOC_SD_SDIO_TMOUT_response_timeout_START  (0)
#define SOC_SD_SDIO_TMOUT_response_timeout_END    (7)
#define SOC_SD_SDIO_TMOUT_data_timeout_START      (8)
#define SOC_SD_SDIO_TMOUT_data_timeout_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_CTYPE_UNION
 �ṹ˵��  : CTYPE �Ĵ����ṹ���塣��ַƫ����:0x018����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����ͼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  card_width4 : 1;  /* bit[0]    : 1'b0:1bitģʽ��
                                                       1'b1:4bitģʽ��
                                                       ����card_width8��Чʱ����1bit��4bit�����ò���Ч�� */
        unsigned int  reserved_0  : 15; /* bit[1-15] : ������ */
        unsigned int  card_width8 : 1;  /* bit[16]   : 1'b0:��8bitģʽ��
                                                       1'b1:8bitģʽ�� */
        unsigned int  reserved_1  : 15; /* bit[17-31]: ������ */
    } reg;
} SOC_SD_SDIO_CTYPE_UNION;
#endif
#define SOC_SD_SDIO_CTYPE_card_width4_START  (0)
#define SOC_SD_SDIO_CTYPE_card_width4_END    (0)
#define SOC_SD_SDIO_CTYPE_card_width8_START  (16)
#define SOC_SD_SDIO_CTYPE_card_width8_END    (16)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_BLKSIZ_UNION
 �ṹ˵��  : BLKSIZ �Ĵ����ṹ���塣��ַƫ����:0x01C����ֵ:0x00000200�����:32
 �Ĵ���˵��: ���С���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  block_size : 16; /* bit[0-15] : Block��С�� */
        unsigned int  reserved   : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_SD_SDIO_BLKSIZ_UNION;
#endif
#define SOC_SD_SDIO_BLKSIZ_block_size_START  (0)
#define SOC_SD_SDIO_BLKSIZ_block_size_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_BYTCNT_UNION
 �ṹ˵��  : BYTCNT �Ĵ����ṹ���塣��ַƫ����:0x020����ֵ:0x00000200�����:32
 �Ĵ���˵��: �ֽ����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  byte_count : 32; /* bit[0-31]: �����byte��Ŀ��ΪBlock��С����������
                                                     �����δ���峤�ȵĴ��䣬��üĴ�������Ϊ0��ͨ������send/abort����ʵ�����ݴ��䡣 */
    } reg;
} SOC_SD_SDIO_BYTCNT_UNION;
#endif
#define SOC_SD_SDIO_BYTCNT_byte_count_START  (0)
#define SOC_SD_SDIO_BYTCNT_byte_count_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_INTMASK_UNION
 �ṹ˵��  : INTMASK �Ĵ����ṹ���塣��ַƫ����:0x024����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж����μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_mask      : 16; /* bit[0-15] : �ж�����λ:
                                                         1'b0:�����ж�
                                                         1'b1:ʹ���ж�
                                                         bit 15 �C End-bit error (read)/Write no CRC (EBE)
                                                         bit 14 �C Auto command done (ACD)
                                                         bit 13 �C Start-bit error (SBE)
                                                         bit 12 �C Hardware locked write error (HLE)
                                                         bit 11 �C FIFO underrun/overrun error (FRUN)
                                                         bit 10 �C Data starvation-by-host timeout (HTO) /Volt_switch_int
                                                         bit 9 �C Data read timeout (DRTO)
                                                         bit 8 �C Response timeout (RTO)
                                                         bit 7 �C Data CRC error (DCRC)
                                                         bit 6 �C Response CRC error (RCRC)
                                                         bit 5 �C Receive FIFO data request (RXDR)
                                                         bit 4 �C Transmit FIFO data request (TXDR)
                                                         bit 3 �C Data transfer over (DTO)
                                                         bit 2 �C Command done (CD)
                                                         bit 1 �C Response error (RE)
                                                         bit 0 �C Card detect (CD) */
        unsigned int  sdio_int_mask : 1;  /* bit[16]   : SDIO�ж�����λ
                                                         1'b0:����SDIO�жϣ�
                                                         1'b1:ʹ��SDIO�жϡ� */
        unsigned int  reserved      : 15; /* bit[17-31]: reserved */
    } reg;
} SOC_SD_SDIO_INTMASK_UNION;
#endif
#define SOC_SD_SDIO_INTMASK_int_mask_START       (0)
#define SOC_SD_SDIO_INTMASK_int_mask_END         (15)
#define SOC_SD_SDIO_INTMASK_sdio_int_mask_START  (16)
#define SOC_SD_SDIO_INTMASK_sdio_int_mask_END    (16)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_CMDARG_UNION
 �ṹ˵��  : CMDARG �Ĵ����ṹ���塣��ַƫ����:0x028����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��������Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cmd_arg : 32; /* bit[0-31]: ��������� */
    } reg;
} SOC_SD_SDIO_CMDARG_UNION;
#endif
#define SOC_SD_SDIO_CMDARG_cmd_arg_START  (0)
#define SOC_SD_SDIO_CMDARG_cmd_arg_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_CMD_UNION
 �ṹ˵��  : CMD �Ĵ����ṹ���塣��ַƫ����:0x02C����ֵ:0x20000000�����:32
 �Ĵ���˵��: ����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cmd_index                   : 6;  /* bit[0-5]  : ������š� */
        unsigned int  response_expect             : 1;  /* bit[6]    : 1'b0:��response��
                                                                       1'b1:��response�� */
        unsigned int  response_length             : 1;  /* bit[7]    : 1'b0:��response��
                                                                       1'b1:��response�� */
        unsigned int  check_response_crc          : 1;  /* bit[8]    : 1'b0:�����CRC��
                                                                       1'b1:���CRC�� */
        unsigned int  data_expected               : 1;  /* bit[9]    : 1'b0:�����ݴ��䣻
                                                                       1'b1:�����ݴ��䡣 */
        unsigned int  read_write                  : 1;  /* bit[10]   : 1'b0:��������
                                                                       1'b1:д������ */
        unsigned int  transfer_mode               : 1;  /* bit[11]   : 1'b0:block���ݴ��䣻
                                                                       1'b1:stream���ݴ��䡣 */
        unsigned int  send_auto_stop              : 1;  /* bit[12]   : 1'b0�������ݴ������ʱ������stop���
                                                                       1'b1�������ݴ������ʱ�Զ�����stop�����
                                                                       �����ô�λʱ�����ݴ�����ɺ󣬿��������Զ�����stop��� */
        unsigned int  wait_prvdata_complete       : 1;  /* bit[13]   : 1'b0:���������������֮ǰ�����ݴ����Ƿ������
                                                                       1'b1:�ȴ�֮ǰ�����ݴ�����ɺ��ٷ������ */
        unsigned int  stop_abort_cmd              : 1;  /* bit[14]   : 1'b0��������stop/abort ���
                                                                       1'b1������stop/abort �����ֹ���ڽ��е����ݴ��䡣
                                                                       ��open_end�򶨳������ݴ���������ڽ���ʱ������������stop/abord����ֹͣ����ʱ����Ҫ���ô�λʹCIU������ȷ�ص�IDLE-state��
                                                                       �ù���ͬ��������Bootģʽ������Ҫ��ֹboot�����ݴ���ʱ������CMD26=diasble_boot��ͬʱ���ô�λΪ1�� */
        unsigned int  send_initialization         : 1;  /* bit[15]   : 1'b0:��������ǰ�����ͳ�ʼ�����У�
                                                                       1'b1:��������ǰ���ͳ�ʼ�����С�
                                                                       ���ϵ�ʱ���ڷ����κ�����ǰ�����������ͳ���ʼ�����У�������Ϊ��80��ʱ�����ڵ�1���С� */
        unsigned int  reserved_0                  : 5;  /* bit[16-20]: ���� */
        unsigned int  update_clock_registers_only : 1;  /* bit[21]   : 1'b0:�����������У�
                                                                       1'b1:���������ֻ���¿�ʱ�����ʱ�ӼĴ�����CLKDIV,CLKCRC,CLKENA��
                                                                       ÿ�θı俨ʱ��ʱ����Ҫ����bit����Ϊ1����ʱ������������͸�����Ҳ�������Command Done�жϡ� */
        unsigned int  reserved_1                  : 2;  /* bit[22-23]: ���� */
        unsigned int  enable_boot                 : 1;  /* bit[24]   : 1'b0:��Ч��
                                                                       1'b1:��bitֻ��bootģʽ�����ã������ͬʱ���ø�bit��start_cmd�����������boot����Ϊ��CMD��Ϊ�͡�
                                                                       disable_boot��enable_boot����ͬʱ��Ч */
        unsigned int  expect_boot_ack             : 1;  /* bit[25]   : 1'b0:��Ч��
                                                                       1'b1:ʹ��boot��Ӧ�������ͬʱʹ�ܴ�bit��enable_bootʱ�������������Boot pattern�źţ�Ϊ"0-1-0"���С� */
        unsigned int  disable_boot                : 1;  /* bit[26]   : 1'b0:��Ч��
                                                                       1'b1:ֹͣboot������
                                                                       disable_boot��enable_boot����ͬʱ��Ч�� */
        unsigned int  boot_mode                   : 1;  /* bit[27]   : 1'b0:bootģʽ��
                                                                       1'b1:��ѡbootģʽ�� */
        unsigned int  volt_switch                 : 1;  /* bit[28]   : 1'b0:�޵�ѹ�л���
                                                                       1'b1:��ѹ�л����������ΪCMD11�� */
        unsigned int  use_hold_reg                : 1;  /* bit[29]   : 1'b0:CMD��DATA�������ͨ��HOLD�Ĵ�����
                                                                       1'b1:CMD��DATA�����ͨ��HOLD�Ĵ����� */
        unsigned int  reserved_2                  : 1;  /* bit[30]   : ������ */
        unsigned int  start_cmd                   : 1;  /* bit[31]   : ����ʹ��λ�������CIUִ��ʱ����bitλ���㣬����bitΪ1ʱ�����д����Ĵ����ᷢ��hardware lock error�ж�
                                                                       �������ѷ��Ͳ���response�Ѿ����أ������Command Done�жϡ� */
    } reg;
} SOC_SD_SDIO_CMD_UNION;
#endif
#define SOC_SD_SDIO_CMD_cmd_index_START                    (0)
#define SOC_SD_SDIO_CMD_cmd_index_END                      (5)
#define SOC_SD_SDIO_CMD_response_expect_START              (6)
#define SOC_SD_SDIO_CMD_response_expect_END                (6)
#define SOC_SD_SDIO_CMD_response_length_START              (7)
#define SOC_SD_SDIO_CMD_response_length_END                (7)
#define SOC_SD_SDIO_CMD_check_response_crc_START           (8)
#define SOC_SD_SDIO_CMD_check_response_crc_END             (8)
#define SOC_SD_SDIO_CMD_data_expected_START                (9)
#define SOC_SD_SDIO_CMD_data_expected_END                  (9)
#define SOC_SD_SDIO_CMD_read_write_START                   (10)
#define SOC_SD_SDIO_CMD_read_write_END                     (10)
#define SOC_SD_SDIO_CMD_transfer_mode_START                (11)
#define SOC_SD_SDIO_CMD_transfer_mode_END                  (11)
#define SOC_SD_SDIO_CMD_send_auto_stop_START               (12)
#define SOC_SD_SDIO_CMD_send_auto_stop_END                 (12)
#define SOC_SD_SDIO_CMD_wait_prvdata_complete_START        (13)
#define SOC_SD_SDIO_CMD_wait_prvdata_complete_END          (13)
#define SOC_SD_SDIO_CMD_stop_abort_cmd_START               (14)
#define SOC_SD_SDIO_CMD_stop_abort_cmd_END                 (14)
#define SOC_SD_SDIO_CMD_send_initialization_START          (15)
#define SOC_SD_SDIO_CMD_send_initialization_END            (15)
#define SOC_SD_SDIO_CMD_update_clock_registers_only_START  (21)
#define SOC_SD_SDIO_CMD_update_clock_registers_only_END    (21)
#define SOC_SD_SDIO_CMD_enable_boot_START                  (24)
#define SOC_SD_SDIO_CMD_enable_boot_END                    (24)
#define SOC_SD_SDIO_CMD_expect_boot_ack_START              (25)
#define SOC_SD_SDIO_CMD_expect_boot_ack_END                (25)
#define SOC_SD_SDIO_CMD_disable_boot_START                 (26)
#define SOC_SD_SDIO_CMD_disable_boot_END                   (26)
#define SOC_SD_SDIO_CMD_boot_mode_START                    (27)
#define SOC_SD_SDIO_CMD_boot_mode_END                      (27)
#define SOC_SD_SDIO_CMD_volt_switch_START                  (28)
#define SOC_SD_SDIO_CMD_volt_switch_END                    (28)
#define SOC_SD_SDIO_CMD_use_hold_reg_START                 (29)
#define SOC_SD_SDIO_CMD_use_hold_reg_END                   (29)
#define SOC_SD_SDIO_CMD_start_cmd_START                    (31)
#define SOC_SD_SDIO_CMD_start_cmd_END                      (31)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_RESP0_UNION
 �ṹ˵��  : RESP0 �Ĵ����ṹ���塣��ַƫ����:0x030����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��Ӧ�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  resp0 : 32; /* bit[0-31]: response��[31:0]λ�� */
    } reg;
} SOC_SD_SDIO_RESP0_UNION;
#endif
#define SOC_SD_SDIO_RESP0_resp0_START  (0)
#define SOC_SD_SDIO_RESP0_resp0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_RESP1_UNION
 �ṹ˵��  : RESP1 �Ĵ����ṹ���塣��ַƫ����:0x034����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��Ӧ�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  resp1 : 32; /* bit[0-31]: ��response��[63:32]λ��
                                                ��CIU ����Auto-stop ���response �ͻᱻ�����ڸüĴ�������һ�������response ��Ȼ�ᱻ�����ڼĴ���RESP0�ڡ�Auto-stop ֻ�����ݴ���ʹ�ã��ظ�����һֱ�Ƕ�response�� */
    } reg;
} SOC_SD_SDIO_RESP1_UNION;
#endif
#define SOC_SD_SDIO_RESP1_resp1_START  (0)
#define SOC_SD_SDIO_RESP1_resp1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_RESP2_UNION
 �ṹ˵��  : RESP2 �Ĵ����ṹ���塣��ַƫ����:0x038����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��Ӧ�Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  resp2 : 32; /* bit[0-31]: ��response��[95:64]λ�� */
    } reg;
} SOC_SD_SDIO_RESP2_UNION;
#endif
#define SOC_SD_SDIO_RESP2_resp2_START  (0)
#define SOC_SD_SDIO_RESP2_resp2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_RESP3_UNION
 �ṹ˵��  : RESP3 �Ĵ����ṹ���塣��ַƫ����:0x03C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��Ӧ�Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  resp3 : 32; /* bit[0-31]: ��response��[127:96]λ�� */
    } reg;
} SOC_SD_SDIO_RESP3_UNION;
#endif
#define SOC_SD_SDIO_RESP3_resp3_START  (0)
#define SOC_SD_SDIO_RESP3_resp3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_MINTSTS_UNION
 �ṹ˵��  : MINTSTS �Ĵ����ṹ���塣��ַƫ����:0x040����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���κ��ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_status     : 16; /* bit[0-15] : �����ж�״̬λ:
                                                          1'b0:���ж�
                                                          1'b1:���ж�
                                                          bit 15 �C End-bit error (read)/Write no CRC(EBE)
                                                          bit 14 �C Auto command done (ACD)
                                                          bit 13 �C Start-bit error (SBE)
                                                          bit 12 �C Hardware locked write error(HLE)
                                                          bit 11 �C FIFO underrun/overrun error(FRUN)
                                                          bit 10 �C Data starvation by host timeout(HTO) /Volt_switch_int
                                                          bit 9 �C Data read timeout(DRTO)
                                                          bit 8 �C Response timeout(RTO)
                                                          bit 7 �C Data CRC error(DCRC)
                                                          bit 6 �C Response CRC error(RCRC)
                                                          bit 5 �C Receive FIFO data request(RXDR)
                                                          bit 4 �C Transmit FIFO data request(TXDR)
                                                          bit 3 �C Data transfer over(DTO)
                                                          bit 2 �C Command done(CD)
                                                          bit 1 �C Response error(RE)
                                                          bit 0 �C Card detect(CD) */
        unsigned int  sdio_interrupt : 1;  /* bit[16]   : ���κ�SDIO�ж�״̬λ��
                                                          1'b0:��SDIO�жϣ�
                                                          1'b1:��SDIO�жϡ� */
        unsigned int  reserved       : 15; /* bit[17-31]: ������ */
    } reg;
} SOC_SD_SDIO_MINTSTS_UNION;
#endif
#define SOC_SD_SDIO_MINTSTS_int_status_START      (0)
#define SOC_SD_SDIO_MINTSTS_int_status_END        (15)
#define SOC_SD_SDIO_MINTSTS_sdio_interrupt_START  (16)
#define SOC_SD_SDIO_MINTSTS_sdio_interrupt_END    (16)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_RINTSTS_UNION
 �ṹ˵��  : RINTSTS �Ĵ����ṹ���塣��ַƫ����:0x044����ֵ:0x00000000�����:32
 �Ĵ���˵��: ԭʼ�ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_status     : 16; /* bit[0-15] : ԭʼ�ж�״̬λ:
                                                          1'b0:���жϣ�
                                                          1'b1:���жϡ�
                                                          bit 15 �C End-bit error (read)/Write no CRC (EBE)
                                                          bit 14 �C Auto command done (ACD)
                                                          bit 13 �C Start-bit error (SBE)
                                                          bit 12 �C Hardware locked write error (HLE)
                                                          bit 11 �C FIFO underrun/overrun error (FRUN)
                                                          bit 10 �C Data starvation-by-host timeout (HTO) /Volt_switch_int
                                                          bit 9 �C Data read timeout (DRTO)
                                                          bit 8 �C Response timeout (RTO)
                                                          bit 7 �C Data CRC error (DCRC)
                                                          bit 6 �C Response CRC error (RCRC)
                                                          bit 5 �C Receive FIFO data request (RXDR)
                                                          bit 4 �C Transmit FIFO data request (TXDR)
                                                          bit 3 �C Data transfer over (DTO)
                                                          bit 2 �C Command done (CD)
                                                          bit 1 �C Response error (RE)
                                                          bit 0 �C Card detect (CD) */
        unsigned int  sdio_interrupt : 1;  /* bit[16]   : ԭʼSDIO�ж�״̬λ
                                                          1'b0:��SDIO�жϣ�
                                                          1'b1:��SDIO�жϡ� */
        unsigned int  reserved       : 15; /* bit[17-31]: ���� */
    } reg;
} SOC_SD_SDIO_RINTSTS_UNION;
#endif
#define SOC_SD_SDIO_RINTSTS_int_status_START      (0)
#define SOC_SD_SDIO_RINTSTS_int_status_END        (15)
#define SOC_SD_SDIO_RINTSTS_sdio_interrupt_START  (16)
#define SOC_SD_SDIO_RINTSTS_sdio_interrupt_END    (16)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_STATUS_UNION
 �ṹ˵��  : STATUS �Ĵ����ṹ���塣��ַƫ����:0x048����ֵ:0x00000406�����:32
 �Ĵ���˵��: ����״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fifo_rx_watermark  : 1;  /* bit[0]    : fifo�Ƿ�ﵽreceive watermark level
                                                              1'b0:δ�ﵽ
                                                              1'b1:�ﵽ */
        unsigned int  fifo_tx_watermark  : 1;  /* bit[1]    : fifo�Ƿ�ﵽtransmit watermark level
                                                              1'b0:δ�ﵽ
                                                              1'b1:�ﵽ */
        unsigned int  fifo_empty         : 1;  /* bit[2]    : fifo�Ƿ�Ϊ��
                                                              1'b0:�ǿ�
                                                              1'b1:�� */
        unsigned int  fifo_full          : 1;  /* bit[3]    : fifo�Ƿ�Ϊ��
                                                              1'b0:����
                                                              1'b1:�� */
        unsigned int  cmd_fsm_state      : 4;  /* bit[4-7]  : ����״̬��
                                                              0 �C Idle
                                                              1 �C Send init sequence
                                                              2 �C Tx cmd start bit
                                                              3 �C Tx cmd tx bit
                                                              4 �C Tx cmd index + arg
                                                              5 �C Tx cmd crc7
                                                              6 �C Tx cmd end bit
                                                              7 �C Rx resp start bit
                                                              8 �C Rx resp IRQ response
                                                              9 �C Rx resp tx bit
                                                              10 �C Rx resp cmd idx
                                                              11 �C Rx resp data
                                                              12 �C Rx resp crc7
                                                              13 �C Rx resp end bit
                                                              14 �C Cmd path wait NCC
                                                              15 �C Wait; CMD-to-response turnaround */
        unsigned int  data_3_status      : 1;  /* bit[8]    : ��Ӧcard_data[3]��check���Ƿ���λ��
                                                              1'b0:�޿���
                                                              1'b1:�п��� */
        unsigned int  data_busy          : 1;  /* bit[9]    : ԭʼ��card_data[0]�ķ���
                                                              1'b0:���У�
                                                              1'b1:��æ�� */
        unsigned int  data_state_mc_busy : 1;  /* bit[10]   : ���ݷ��ͺͽ���״̬���Ƿ�æ��
                                                              1'b0:idle��
                                                              1'b1:busy�� */
        unsigned int  response_index     : 6;  /* bit[11-16]: ǰһ��response����ţ��������������͵�auto-stop��response�� */
        unsigned int  fifo_count         : 13; /* bit[17-29]: FIFO����ֵ�� */
        unsigned int  dma_ack            : 1;  /* bit[30]   : DMAȷ���ź�״̬�� */
        unsigned int  dma_req            : 1;  /* bit[31]   : DMA�����źŵ�״̬�� */
    } reg;
} SOC_SD_SDIO_STATUS_UNION;
#endif
#define SOC_SD_SDIO_STATUS_fifo_rx_watermark_START   (0)
#define SOC_SD_SDIO_STATUS_fifo_rx_watermark_END     (0)
#define SOC_SD_SDIO_STATUS_fifo_tx_watermark_START   (1)
#define SOC_SD_SDIO_STATUS_fifo_tx_watermark_END     (1)
#define SOC_SD_SDIO_STATUS_fifo_empty_START          (2)
#define SOC_SD_SDIO_STATUS_fifo_empty_END            (2)
#define SOC_SD_SDIO_STATUS_fifo_full_START           (3)
#define SOC_SD_SDIO_STATUS_fifo_full_END             (3)
#define SOC_SD_SDIO_STATUS_cmd_fsm_state_START       (4)
#define SOC_SD_SDIO_STATUS_cmd_fsm_state_END         (7)
#define SOC_SD_SDIO_STATUS_data_3_status_START       (8)
#define SOC_SD_SDIO_STATUS_data_3_status_END         (8)
#define SOC_SD_SDIO_STATUS_data_busy_START           (9)
#define SOC_SD_SDIO_STATUS_data_busy_END             (9)
#define SOC_SD_SDIO_STATUS_data_state_mc_busy_START  (10)
#define SOC_SD_SDIO_STATUS_data_state_mc_busy_END    (10)
#define SOC_SD_SDIO_STATUS_response_index_START      (11)
#define SOC_SD_SDIO_STATUS_response_index_END        (16)
#define SOC_SD_SDIO_STATUS_fifo_count_START          (17)
#define SOC_SD_SDIO_STATUS_fifo_count_END            (29)
#define SOC_SD_SDIO_STATUS_dma_ack_START             (30)
#define SOC_SD_SDIO_STATUS_dma_ack_END               (30)
#define SOC_SD_SDIO_STATUS_dma_req_START             (31)
#define SOC_SD_SDIO_STATUS_dma_req_END               (31)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_FIFOTH_UNION
 �ṹ˵��  : FIFOTH �Ĵ����ṹ���塣��ַƫ����:0x04C����ֵ:0x00FF0000�����:32
 �Ĵ���˵��: FIFOˮ��ֵ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tx_wmark                         : 12; /* bit[0-11] : ��������ʱ��FIFO threshold watermark level����FIFO ����С�ڸ�ֵʱ��ʹ��DMA �������ݴ��������Ϊ�����ʣ
                                                                            ������ݣ����۸�ֵΪ���٣��������DMA ����
                                                                            �ڷ�DMA ģʽ��ʹ��RXDR �жϡ������ݴ�����ɺ����FIFO ����û�д��ڸ�ֵ����������жϡ�����Ҫ���������ѯDTD �ж�����ȡʣ������ݡ�
                                                                            ��DMA ģʽ�������ݴ������ʱ����ʹʣ������ݱ����޵ͣ�DMA ���ǻᷢ��single ���������ȡ���ݣ�ֱ������DTD �жϡ�
                                                                            ���ƣ�TX_WMark?FIFO_DEPTH�C2
                                                                            ���飺���ڣ�FIFO_DEPTH/2���C1 ʱ�������� */
        unsigned int  reserved_0                       : 4;  /* bit[12-15]: ���� */
        unsigned int  rx_wmark                         : 12; /* bit[16-27]: ������ʱ��FIFO threshold watermark level��
                                                                            ��FIFO �������ڸ�ֵʱ��ʹ��DMA �������ݴ��������Ϊ�����ʣ������ݣ����۸�ֵΪ���٣��������DMA����
                                                                            �ڷ�DMAģʽ��������FIFO��ֵ��RXDR���ж�ʹ��ʱ���򲻻����DMA request��
                                                                            �����ݴ�����ɺ����FIFO����û�д��ڸ�ֵ����������жϡ�����Ҫ���������ѯDTD �ж�����ȡʣ������ݡ�
                                                                            ��DMA ģʽ�������ݴ������ʱ����ʹʣ������ݱ����޵ͣ�DMA ���ǻᷢ��single ���������ȡ���ݣ�ֱ������DTD �жϡ�
                                                                            ���ƣ�RX_WMark?FIFO_DEPTH�C2��
                                                                            ���飺���ڣ�FIFO_DEPTH/2���C1 ʱ�������� */
        unsigned int  dw_dma_multiple_transaction_size : 3;  /* bit[28-30]: Burst Size����DMAC ��С��ͬ��
                                                                            000��1��
                                                                            001��4��
                                                                            010��8��
                                                                            011��16��
                                                                            100��32��
                                                                            101��64��
                                                                            110��128��
                                                                            111��256 */
        unsigned int  reserved_1                       : 1;  /* bit[31]   : ������ */
    } reg;
} SOC_SD_SDIO_FIFOTH_UNION;
#endif
#define SOC_SD_SDIO_FIFOTH_tx_wmark_START                          (0)
#define SOC_SD_SDIO_FIFOTH_tx_wmark_END                            (11)
#define SOC_SD_SDIO_FIFOTH_rx_wmark_START                          (16)
#define SOC_SD_SDIO_FIFOTH_rx_wmark_END                            (27)
#define SOC_SD_SDIO_FIFOTH_dw_dma_multiple_transaction_size_START  (28)
#define SOC_SD_SDIO_FIFOTH_dw_dma_multiple_transaction_size_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_GPIO_UNION
 �ṹ˵��  : GPIO �Ĵ����ṹ���塣��ַƫ����:0x058����ֵ:0x00FF0F00�����:32
 �Ĵ���˵��: ʱ�����üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0       : 8;  /* bit[0-7]  : ������ */
        unsigned int  div_cclk         : 4;  /* bit[8-11] : ��Ƶģ���ʱ�ӷ�Ƶϵ���� */
        unsigned int  reserved_1       : 1;  /* bit[12]   : ������ */
        unsigned int  use_delay_sample : 1;  /* bit[13]   : �ڲ���ʱ�Ӳ����������ݺ�ʹ��cclk_in_delay_sample�Ĵ����ݡ� */
        unsigned int  reserved_2       : 2;  /* bit[14-15]: ������ */
        unsigned int  enable_cclk      : 1;  /* bit[16]   : ��Ƶģ���ʱ��ʹ�ܡ� */
        unsigned int  reserved_3       : 15; /* bit[17-31]: ������ */
    } reg;
} SOC_SD_SDIO_GPIO_UNION;
#endif
#define SOC_SD_SDIO_GPIO_div_cclk_START          (8)
#define SOC_SD_SDIO_GPIO_div_cclk_END            (11)
#define SOC_SD_SDIO_GPIO_use_delay_sample_START  (13)
#define SOC_SD_SDIO_GPIO_use_delay_sample_END    (13)
#define SOC_SD_SDIO_GPIO_enable_cclk_START       (16)
#define SOC_SD_SDIO_GPIO_enable_cclk_END         (16)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_TCBCNT_UNION
 �ṹ˵��  : TCBCNT �Ĵ����ṹ���塣��ַƫ����:0x05C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���͵�������byte��Ŀ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  trans_card_byte_count : 32; /* bit[0-31]: ��CIU���͵�����byte��Ŀ�� */
    } reg;
} SOC_SD_SDIO_TCBCNT_UNION;
#endif
#define SOC_SD_SDIO_TCBCNT_trans_card_byte_count_START  (0)
#define SOC_SD_SDIO_TCBCNT_trans_card_byte_count_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_TTBCNT_UNION
 �ṹ˵��  : TTBCNT �Ĵ����ṹ���塣��ַƫ����:0x060����ֵ:0x00000000�����:32
 �Ĵ���˵��: BIU FIFO�������ݵ�byte���Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  trans_fifo_byte_count : 32; /* bit[0-31]: ���ߺ�FIFO֮�䴫�ݵ�byte��Ŀ�� */
    } reg;
} SOC_SD_SDIO_TTBCNT_UNION;
#endif
#define SOC_SD_SDIO_TTBCNT_trans_fifo_byte_count_START  (0)
#define SOC_SD_SDIO_TTBCNT_trans_fifo_byte_count_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_USRID_UNION
 �ṹ˵��  : USRID �Ĵ����ṹ���塣��ַƫ����:0x068����ֵ:0x07967797�����:32
 �Ĵ���˵��: �û�ID�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  usrid : 32; /* bit[0-31]: �û�ID�Ĵ����� */
    } reg;
} SOC_SD_SDIO_USRID_UNION;
#endif
#define SOC_SD_SDIO_USRID_usrid_START  (0)
#define SOC_SD_SDIO_USRID_usrid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_VERID_UNION
 �ṹ˵��  : VERID �Ĵ����ṹ���塣��ַƫ����:0x06C����ֵ:0x5342270A�����:32
 �Ĵ���˵��: �汾�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  verid : 32; /* bit[0-31]: �汾�Ĵ����� */
    } reg;
} SOC_SD_SDIO_VERID_UNION;
#endif
#define SOC_SD_SDIO_VERID_verid_START  (0)
#define SOC_SD_SDIO_VERID_verid_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_HCON_UNION
 �ṹ˵��  : HCON �Ĵ����ṹ���塣��ַƫ����:0x070����ֵ:0x00E42C81�����:32
 �Ĵ���˵��: ���ð汾�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hcon : 32; /* bit[0-31]: ���ð汾�Ĵ����� */
    } reg;
} SOC_SD_SDIO_HCON_UNION;
#endif
#define SOC_SD_SDIO_HCON_hcon_START  (0)
#define SOC_SD_SDIO_HCON_hcon_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_UHS_REG_UNION
 �ṹ˵��  : UHS_REG �Ĵ����ṹ���塣��ַƫ����:0x074����ֵ:0x00000000�����:32
 �Ĵ���˵��: UHS-1�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 16; /* bit[0-15] : ���� */
        unsigned int  ddr_reg  : 1;  /* bit[16]   : DDRģʽ��
                                                    1'b0: ��DDRģʽ��
                                                    1'b1: DDRģʽ�� */
        unsigned int  reserved_1: 15; /* bit[17-31]: ������ */
    } reg;
} SOC_SD_SDIO_UHS_REG_UNION;
#endif
#define SOC_SD_SDIO_UHS_REG_ddr_reg_START   (16)
#define SOC_SD_SDIO_UHS_REG_ddr_reg_END     (16)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_BMOD_UNION
 �ṹ˵��  : BMOD �Ĵ����ṹ���塣��ַƫ����:0x080����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����DMA���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  swr      : 1;  /* bit[0]    : ��λ��DMA��λ���е��ڲ��Ĵ�������bit��1��ʱ�����ں��Զ������㡣 */
        unsigned int  fb       : 1;  /* bit[1]    : �̶�burst���͡���DMA����ʱ�������ó�1��������ܵ������߹������� */
        unsigned int  dsl      : 5;  /* bit[2-6]  : ������ת�ĳ��ȡ� */
        unsigned int  de       : 1;  /* bit[7]    : IDMACʹ�ܡ� */
        unsigned int  pbl      : 3;  /* bit[8-10] : ����burst���ȣ�ֻ����������FIFOTH�Ĵ�����MSIZEֵ���Ӧ��Ҫ�ı�üĴ�����ֵ����д��Ӧ��ֵ��FIFOTH�Ĵ�����
                                                    3'b000:1
                                                    3'b001:4
                                                    3'b010:8
                                                    3'b011:16
                                                    3'b100:32
                                                    3'b101:64
                                                    3'b110:128
                                                    3'b111:256 */
        unsigned int  reserved : 21; /* bit[11-31]: ������ */
    } reg;
} SOC_SD_SDIO_BMOD_UNION;
#endif
#define SOC_SD_SDIO_BMOD_swr_START       (0)
#define SOC_SD_SDIO_BMOD_swr_END         (0)
#define SOC_SD_SDIO_BMOD_fb_START        (1)
#define SOC_SD_SDIO_BMOD_fb_END          (1)
#define SOC_SD_SDIO_BMOD_dsl_START       (2)
#define SOC_SD_SDIO_BMOD_dsl_END         (6)
#define SOC_SD_SDIO_BMOD_de_START        (7)
#define SOC_SD_SDIO_BMOD_de_END          (7)
#define SOC_SD_SDIO_BMOD_pbl_START       (8)
#define SOC_SD_SDIO_BMOD_pbl_END         (10)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_PLDMND_UNION
 �ṹ˵��  : PLDMND �Ĵ����ṹ���塣��ַƫ����:0x084����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��������Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pldmnd : 32; /* bit[0-31]: ��������е�OWNû�����ã���DMA��״̬�������suspend״̬�����üĴ���д�κ�ֵ����DMA״̬������������ȡ�����������������üĴ�����ֻд�Ĵ����� */
    } reg;
} SOC_SD_SDIO_PLDMND_UNION;
#endif
#define SOC_SD_SDIO_PLDMND_pldmnd_START  (0)
#define SOC_SD_SDIO_PLDMND_pldmnd_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_DBADDR_UNION
 �ṹ˵��  : DBADDR �Ĵ����ṹ���塣��ַƫ����:0x088����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������ʼ��ַ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sdl : 32; /* bit[0-31]: ������ʼ��ַ�� */
    } reg;
} SOC_SD_SDIO_DBADDR_UNION;
#endif
#define SOC_SD_SDIO_DBADDR_sdl_START  (0)
#define SOC_SD_SDIO_DBADDR_sdl_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_IDSTS_UNION
 �ṹ˵��  : IDSTS �Ĵ����ṹ���塣��ַƫ����:0x08C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����DMA״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ti       : 1;  /* bit[0]    : ���ݴ����жϣ�ָʾ��Ӧ�����������ݴ�������ɡ� */
        unsigned int  ri       : 1;  /* bit[1]    : �����жϣ�ָʾ���������ݽ�����ɡ� */
        unsigned int  fbe      : 1;  /* bit[2]    : ���ߴ����жϣ�Ϊ1ʱ��DMA��ֹ���е����߷��ʡ� */
        unsigned int  reserved_0: 1;  /* bit[3]    : ������ */
        unsigned int  du       : 1;  /* bit[4]    : �������������ж�(OWN=0) */
        unsigned int  ces      : 1;  /* bit[5]    : �������ж�ָʾ�������¼����ж�:
                                                    EBE �C End Bit Error
                                                    RTO �C Response Timeout/Boot Ack Timeout
                                                    RCRC �C Response CRC
                                                    SBE �C Start Bit Error
                                                    DRTO �C Data Read Timeout/BDS timeout
                                                    DCRC �C Data CRC for Receive
                                                    RE �C Response Error */
        unsigned int  reserved_1: 2;  /* bit[6-7]  : ������ */
        unsigned int  nis      : 1;  /* bit[8]    : �����ж�ָʾ��Ϊ���������жϵ����:
                                                    IDSTS[0]:�����ж�
                                                    IDSTS[1]:�����ж� */
        unsigned int  ais      : 1;  /* bit[9]    : �쳣�жϣ�Ϊ���������жϵ����:
                                                    IDSTS[2]:���ߴ����ж�
                                                    IDSTS[4]:DU�ж�
                                                    IDSTS[5]:�������ж� */
        unsigned int  eb       : 3;  /* bit[10-12]: ���ߴ���ָʾ������IDSTS[2]��Чʱ��Ч��
                                                    3'b001:д�������ߴ���
                                                    3'b010:���������ߴ���
                                                    ���������� */
        unsigned int  fsm      : 4;  /* bit[13-16]: DMA��ǰ״̬:
                                                    0 �C DMA_IDLE
                                                    1 �C DMA_SUSPEND
                                                    2 �C DESC_RD
                                                    3 �C DESC_CHK
                                                    4 �C DMA_RD_REQ_WAIT
                                                    5 �C DMA_WR_REQ_WAIT
                                                    6 �C DMA_RD
                                                    7 �C DMA_WR
                                                    8 �C DESC_CLOSE */
        unsigned int  reserved_2: 15; /* bit[17-31]: ������ */
    } reg;
} SOC_SD_SDIO_IDSTS_UNION;
#endif
#define SOC_SD_SDIO_IDSTS_ti_START        (0)
#define SOC_SD_SDIO_IDSTS_ti_END          (0)
#define SOC_SD_SDIO_IDSTS_ri_START        (1)
#define SOC_SD_SDIO_IDSTS_ri_END          (1)
#define SOC_SD_SDIO_IDSTS_fbe_START       (2)
#define SOC_SD_SDIO_IDSTS_fbe_END         (2)
#define SOC_SD_SDIO_IDSTS_du_START        (4)
#define SOC_SD_SDIO_IDSTS_du_END          (4)
#define SOC_SD_SDIO_IDSTS_ces_START       (5)
#define SOC_SD_SDIO_IDSTS_ces_END         (5)
#define SOC_SD_SDIO_IDSTS_nis_START       (8)
#define SOC_SD_SDIO_IDSTS_nis_END         (8)
#define SOC_SD_SDIO_IDSTS_ais_START       (9)
#define SOC_SD_SDIO_IDSTS_ais_END         (9)
#define SOC_SD_SDIO_IDSTS_eb_START        (10)
#define SOC_SD_SDIO_IDSTS_eb_END          (12)
#define SOC_SD_SDIO_IDSTS_fsm_START       (13)
#define SOC_SD_SDIO_IDSTS_fsm_END         (16)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_IDINTEN_UNION
 �ṹ˵��  : IDINTEN �Ĵ����ṹ���塣��ַƫ����:0x090����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����DMA�ж�ʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ti       : 1;  /* bit[0]    : ���ݴ����ж�ʹ�ܡ� */
        unsigned int  ri       : 1;  /* bit[1]    : ���������ݽ�������ж�ʹ�ܡ� */
        unsigned int  fbe      : 1;  /* bit[2]    : ���ߴ����ж�ʹ�ܡ� */
        unsigned int  reserved_0: 1;  /* bit[3]    : ������ */
        unsigned int  du       : 1;  /* bit[4]    : �����������ж�ʹ�ܡ� */
        unsigned int  ces      : 1;  /* bit[5]    : �������ж�ʹ�ܡ� */
        unsigned int  reserved_1: 2;  /* bit[6-7]  : ������ */
        unsigned int  ni       : 1;  /* bit[8]    : �����ж�ʹ�ܣ�
                                                    IDINTEN[0]:���ݴ�������жϣ�
                                                    IDINTEN[1]:��������������жϡ� */
        unsigned int  ai       : 1;  /* bit[9]    : �쳣�ж�ʹ�ܣ�
                                                    IDINTEN[2]:���ߴ������жϣ�
                                                    IDINTEN[4]:DU�жϣ�
                                                    IDINTEN[5]:�������жϡ� */
        unsigned int  reserved_2: 22; /* bit[10-31]: ������ */
    } reg;
} SOC_SD_SDIO_IDINTEN_UNION;
#endif
#define SOC_SD_SDIO_IDINTEN_ti_START        (0)
#define SOC_SD_SDIO_IDINTEN_ti_END          (0)
#define SOC_SD_SDIO_IDINTEN_ri_START        (1)
#define SOC_SD_SDIO_IDINTEN_ri_END          (1)
#define SOC_SD_SDIO_IDINTEN_fbe_START       (2)
#define SOC_SD_SDIO_IDINTEN_fbe_END         (2)
#define SOC_SD_SDIO_IDINTEN_du_START        (4)
#define SOC_SD_SDIO_IDINTEN_du_END          (4)
#define SOC_SD_SDIO_IDINTEN_ces_START       (5)
#define SOC_SD_SDIO_IDINTEN_ces_END         (5)
#define SOC_SD_SDIO_IDINTEN_ni_START        (8)
#define SOC_SD_SDIO_IDINTEN_ni_END          (8)
#define SOC_SD_SDIO_IDINTEN_ai_START        (9)
#define SOC_SD_SDIO_IDINTEN_ai_END          (9)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_DSCADDR_UNION
 �ṹ˵��  : DSCADDR �Ĵ����ṹ���塣��ַƫ����:0x094����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ǰ����������ַ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hda : 32; /* bit[0-31]: ��ǰ����������ַ�� */
    } reg;
} SOC_SD_SDIO_DSCADDR_UNION;
#endif
#define SOC_SD_SDIO_DSCADDR_hda_START  (0)
#define SOC_SD_SDIO_DSCADDR_hda_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_BUFADDR_UNION
 �ṹ˵��  : BUFADDR �Ĵ����ṹ���塣��ַƫ����:0x098����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ǰ������������ַ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hba : 32; /* bit[0-31]: ��ǰ������������ַ�� */
    } reg;
} SOC_SD_SDIO_BUFADDR_UNION;
#endif
#define SOC_SD_SDIO_BUFADDR_hba_START  (0)
#define SOC_SD_SDIO_BUFADDR_hba_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_CARDTHRCTL_UNION
 �ṹ˵��  : CARDTHRCTL �Ĵ����ṹ���塣��ַƫ����:0x100����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����޿��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  card_rd_thr_en     : 1;  /* bit[0]    : ��������ʹ�ܡ� */
        unsigned int  bsy_clr_int_en     : 1;  /* bit[1]    : busy clear�жϵ�ʹ�ܡ� */
        unsigned int  reserved_0         : 14; /* bit[2-15] : ������ */
        unsigned int  card_rd_threshhold : 11; /* bit[16-26]: �������ޡ� */
        unsigned int  reserved_1         : 5;  /* bit[27-31]: ������ */
    } reg;
} SOC_SD_SDIO_CARDTHRCTL_UNION;
#endif
#define SOC_SD_SDIO_CARDTHRCTL_card_rd_thr_en_START      (0)
#define SOC_SD_SDIO_CARDTHRCTL_card_rd_thr_en_END        (0)
#define SOC_SD_SDIO_CARDTHRCTL_bsy_clr_int_en_START      (1)
#define SOC_SD_SDIO_CARDTHRCTL_bsy_clr_int_en_END        (1)
#define SOC_SD_SDIO_CARDTHRCTL_card_rd_threshhold_START  (16)
#define SOC_SD_SDIO_CARDTHRCTL_card_rd_threshhold_END    (26)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_UHS_REG_EXT_UNION
 �ṹ˵��  : UHS_REG_EXT �Ĵ����ṹ���塣��ַƫ����:0x108����ֵ:0x00000000�����:32
 �Ĵ���˵��: UHS��չ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0            : 16; /* bit[0-15] : ������ */
        unsigned int  clk_smpl_phase_ctrl   : 5;  /* bit[16-20]: cclk_in_sampleʱ�ӵ���λ�� */
        unsigned int  clk_drv_phase_ctrl    : 5;  /* bit[21-25]: cclk_in_drvʱ�ӵ���λ�� */
        unsigned int  clk_samdly_phase_ctrl : 5;  /* bit[26-30]: cclk_in_sample_delayʱ�ӵ���λ�� */
        unsigned int  reserved_1            : 1;  /* bit[31]   : ������ */
    } reg;
} SOC_SD_SDIO_UHS_REG_EXT_UNION;
#endif
#define SOC_SD_SDIO_UHS_REG_EXT_clk_smpl_phase_ctrl_START    (16)
#define SOC_SD_SDIO_UHS_REG_EXT_clk_smpl_phase_ctrl_END      (20)
#define SOC_SD_SDIO_UHS_REG_EXT_clk_drv_phase_ctrl_START     (21)
#define SOC_SD_SDIO_UHS_REG_EXT_clk_drv_phase_ctrl_END       (25)
#define SOC_SD_SDIO_UHS_REG_EXT_clk_samdly_phase_ctrl_START  (26)
#define SOC_SD_SDIO_UHS_REG_EXT_clk_samdly_phase_ctrl_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_EMMC_DDR_REG_UNION
 �ṹ˵��  : EMMC_DDR_REG �Ĵ����ṹ���塣��ַƫ����:0x10C����ֵ:0x00000000�����:32
 �Ĵ���˵��: EMMC4.5DDRģʽstartbit���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  half_start_bit : 16; /* bit[0-15] : ����start_bit�ļ����ơ�����eMMC4.5��start-bit����Ϊ��
                                                          1.full-cycle (HALF_START_BIT = 0)��
                                                          2.����һ����������(HALF_START_BIT = 1)��
                                                          ��eMMC4.5ʹ�ù����У����ô�λΪ1����������Ϊ�㡣 */
        unsigned int  reserved       : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_SD_SDIO_EMMC_DDR_REG_UNION;
#endif
#define SOC_SD_SDIO_EMMC_DDR_REG_half_start_bit_START  (0)
#define SOC_SD_SDIO_EMMC_DDR_REG_half_start_bit_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SD_SDIO_ENABLE_SHIFT_UNION
 �ṹ˵��  : ENABLE_SHIFT �Ĵ����ṹ���塣��ַƫ����:0x110����ֵ:0x00000000�����:32
 �Ĵ���˵��: ENALBEƫ�ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enable_shift : 2;  /* bit[0-1] : ����Ĭ��enable�źŵ�ƫ������
                                                       00��Ĭ��ƫ����λ��
                                                       01��enableƫ�Ƶ���һ��ʱ�������أ�
                                                       10��enableƫ�Ƶ���һ��ʱ���½��أ�
                                                       11�������� */
        unsigned int  reserved     : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_SD_SDIO_ENABLE_SHIFT_UNION;
#endif
#define SOC_SD_SDIO_ENABLE_SHIFT_enable_shift_START  (0)
#define SOC_SD_SDIO_ENABLE_SHIFT_enable_shift_END    (1)






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

#endif /* end of soc_sd_sdio_interface.h */
