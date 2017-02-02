/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_sci_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-23 11:27:34
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��23��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_SCI.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_SCI_INTERFACE_H__
#define __SOC_SCI_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) SCI0
 ****************************************************************************/
/* �Ĵ���˵����SCI���ݼĴ��������ڷ��ͻ�����ַ�����SCI����������ݽӿڡ�
            ���ֻ��������SCI_CR1[mode]Ϊ1֮�󣬲ſɶԴ˼Ĵ�������д��������SCI_CR1[mode]Ϊ0ʱ���������ԶԸüĴ�����д���������������á�
   λ����UNION�ṹ:  SOC_SCI_DATA_UNION */
#define SOC_SCI_DATA_ADDR(base)                       ((base) + (0x0000))

/* �Ĵ���˵����SCI���ƼĴ��������ڿ���ʱ��ֹͣ����żУ�顢�������֡�����λ����ȹ��ܡ�
   λ����UNION�ṹ:  SOC_SCI_CR0_UNION */
#define SOC_SCI_CR0_ADDR(base)                        ((base) + (0x0004))

/* �Ĵ���˵����SCI���ƼĴ��������ڿ���ͬ��/�첽������ģʽ�����ͽ���ģʽ���鳬ʱ��ATR��ʱ�ȹ��ܡ�
   λ����UNION�ṹ:  SOC_SCI_CR1_UNION */
#define SOC_SCI_CR1_ADDR(base)                        ((base) + (0x0008))

/* �Ĵ���˵����SCI���ƼĴ�����д�üĴ�������Ӧλ�ᴥ��SCI�Կ��ļ���ͷŻ���λ��������SCI�������ͷſ���״̬ʱ���ԸüĴ�����д�����������ԡ�������ʱ�򣬶�SCI_CR2[finish]д1��ʹSCI�������Ϳ��ͷ����С�
            (CH)
            (CL)����ԸüĴ�����д���������ں��ʵĿ������׶ν��С������ʵ�д������������Ԥ�ڵĺ����
            (CL)ֻ�е����ܿ�������֮��������ܶԿ�������λ������
   λ����UNION�ṹ:  SOC_SCI_CR2_UNION */
#define SOC_SCI_CR2_ADDR(base)                        ((base) + (0x000C))

/* �Ĵ���˵�������ܿ�ʱ��Ƶ�ʼĴ������üĴ����������ⲿ���ܿ�ʱ�ӵķ�Ƶ���ӡ����ܿ�ʱ��Ƶ�ʵļ��㹫ʽΪ��FSCI_CLK=(FREFCLK)/(clkicc+1)x2 �����У�FSCI_CLKΪʱ��Ƶ�ʣ�FREFCLKΪ�ο�ʱ��Ƶ�ʣ�clkiccΪSCI_CLKICC[clkicc]���õ�ֵ��
   λ����UNION�ṹ:  SOC_SCI_CLKICC_UNION */
#define SOC_SCI_CLKICC_ADDR(base)                     ((base) + (0x0010))

/* �Ĵ���˵����ETU��SCI_BAUD�������Ĵ��������ڼ���ETU��������Ϊ5��255֮�������ֵ��ETU�ļ��㹫ʽΪ��Etu=(1+baud) x value��baudΪSCI_BAUD[baud]���õ�ֵ��valueΪSCI_VALUE[value]���õ�ֵ��
   λ����UNION�ṹ:  SOC_SCI_VALUE_UNION */
#define SOC_SCI_VALUE_ADDR(base)                      ((base) + (0x0014))

/* �Ĵ���˵����������ʱ�ӷ�Ƶֵ�Ĵ��������ڼ���ETU����������Ϊ0x1��0xFFFF֮�������ֵ����μ���SCI_VALUE����ETU�ļ��㹫ʽ��
   λ����UNION�ṹ:  SOC_SCI_BAUD_UNION */
#define SOC_SCI_BAUD_ADDR(base)                       ((base) + (0x0018))

/* �Ĵ���˵�������ͽ���FIFO�������ֵ�Ĵ�����
            (NH)
            (NL)TXFIFO�е��ַ�ֻ���ڳɹ����ͺ�Żᱻ�Ƴ���
   λ����UNION�ṹ:  SOC_SCI_TIDE_UNION */
#define SOC_SCI_TIDE_ADDR(base)                       ((base) + (0x001C))

/* �Ĵ���˵����DMA���ƼĴ��������ڿ���DMA���ͺͽ������ݡ�
   λ����UNION�ṹ:  SOC_SCI_DMACR_UNION */
#define SOC_SCI_DMACR_ADDR(base)                      ((base) + (0x0020))

/* �Ĵ���˵�������ܿ������ȶ�ʱ��Ĵ����������ܿ�����ź�SCI_DETECT�ź���Ч����Ҫ�ȶ�����SCI_STABLE�Ĵ���ֵ��Ӧ�Ĺ̶���ʱ��TSTABLE������TSTABLEʱ�䣨��λΪ�룩�󴥷�cardinintr�жϣ��������ܿ�����ȷ���롣
   λ����UNION�ṹ:  SOC_SCI_STABLE_UNION */
#define SOC_SCI_STABLE_ADDR(base)                     ((base) + (0x0024))

/* �Ĵ���˵�������ܿ�����ʱ��Ĵ������üĴ�����[atime]λ����ָʾ����λ�ͼ����3���׶εĳ���ʱ�䡣
            (NH)
            (NL)Ϊ���㿨��λ��Ҫ��SCI_ATIME[atime]����Ϊ40000���ӿڿ�ʱ�ӣ�SCI_CLK�����ڡ�
            (NL)�ò���Ҳ�����������ܿ��Ե�Դ�ȶ���Ҫ��
   λ����UNION�ṹ:  SOC_SCI_ATIME_UNION */
#define SOC_SCI_ATIME_ADDR(base)                      ((base) + (0x0028))

/* �Ĵ���˵�������ܿ��ͷ�ʱ��Ĵ������üĴ�����{dtime]λ����ָʾ���ͷŵ�3���׶εĳ���ʱ�䣬��λΪSCI�ο�ʱ�����ڡ�
   λ����UNION�ṹ:  SOC_SCI_DTIME_UNION */
#define SOC_SCI_DTIME_ADDR(base)                      ((base) + (0x002C))

/* �Ĵ���˵�����ȴ���ʼ����ATRʱ����ֵ�Ĵ������������ܿ�ʱ�Ӷ����˴����ܿ���λ��������ʼ����ATR��һ���ַ���ʱ����ֵ��ATR�ȴ���ʼ���ճ�ʱ��ᴥ��atrstoutintr�жϣ���SCI_RIS[atrstoutim]��1��
            (NH)SCI_ATRSTIME[atrstime]���������ʼ��Ϊ40000��SCI_CLK�ӿڿ�ʱ�����ڡ�
   λ����UNION�ṹ:  SOC_SCI_ATRSTIME_UNION */
#define SOC_SCI_ATRSTIME_ADDR(base)                   ((base) + (0x0030))

/* �Ĵ���˵��������ATRʱ����ֵ�Ĵ�����SCI�ڽ���ATR�����У��ӵ�һ��ATR�ַ���ʼ���յ����һ��ATR�ַ����ս�������������üĴ����������ʱ�䣨��ETUΪ��λ�����ᴥ���жϣ���SCI_RIS[atrdtoutris]��1��
            (NH)
            (NL)��ʹ�øüĴ���֮ǰ������������SCI_CR1[atrden]Ϊ1����ʹ�ܳ�ʱ�������ơ�
            (NL)����Э�飬�üĴ�����������Ϊ19200��ETU����0x4B00��
   λ����UNION�ṹ:  SOC_SCI_ATRDTIME_UNION */
#define SOC_SCI_ATRDTIME_ADDR(base)                   ((base) + (0x0034))

/* �Ĵ���˵����ʱ��ֹͣʱ��Ĵ�����������ʱ��ֹͣʱ������SCI_STOPTIME�������ʱ�䣨��λΪSCI�ӿڿ�ʱ��SCI_CLK���ڣ������ܿ�ʱ����Ч���������жϣ���SCI_RIS[clkstpris]��1��
            (NH)����Э�飬��ֵ��СΪ1860��SCIʱ�����ڣ���SCI_STOPTIME[stoptime]��Ҫ����Ϊ0x744��
   λ����UNION�ṹ:  SOC_SCI_STOPTIME_UNION */
#define SOC_SCI_STOPTIME_ADDR(base)                   ((base) + (0x0038))

/* �Ĵ���˵�������ܿ�ʱ�ӻָ�ʱ��Ĵ�����������ʱ�ӻָ�ʱ������SCI_STARTTIME�������ʱ�䣨��λΪSCI�ӿڿ�ʱ��SCI_CLK���ڣ���SCI�����ܿ����ܽ������ݴ��䣬�������жϣ���SCI_RIS[clkactris]��1��
            (NH)����Э�飬��ֵ��СӦΪ700��SCIʱ�����ڣ���SCI_STARTTIME[starttimr]������Ҫ����Ϊ0x2BC��
   λ����UNION�ṹ:  SOC_SCI_STARTTIME_UNION */
#define SOC_SCI_STARTTIME_ADDR(base)                  ((base) + (0x003C))

/* �Ĵ���˵�������ͽ������Դ����Ĵ������üĴ��������˷��ͻ���������ش��Ĵ�������������Ϊ��
            (I)��SCI_CR0[txnak]ʹ��ʱ��SCI�����շ��Ƿ��ʶУ�����SCI_RETRY[rxretry]�������У���������´����������������������txerrintr�жϣ���SCI_RIS[txerrris]��1��
            (I)��SCI_CR0[rxnak]ʹ��ʱ��SCI����յ��������Ƿ����У�����SCI_RETRY[txretry]�������У���������´��������������������ô�����Ȼ���մ��󣬽�SCI_DATA[parity]��1��
   λ����UNION�ṹ:  SOC_SCI_RETRY_UNION */
#define SOC_SCI_RETRY_ADDR(base)                      ((base) + (0x0040))

/* �Ĵ���˵���������ַ������ʱ��ֵ��16λ�Ĵ�����
            SCI_CHTIME�Ĵ�������ӿ����յ������������ַ�����ʼ��֮����������ʱ��������ETUΪ��λ����������յ����ַ������ʱ�ᴥ��chtoutintr�жϣ���SCI_RIS[chtoutris]��1��
            (CH)SCI_CHTIME�Ĵ������ɵ�16λ�Ĵ���SCI_CHTIMELS�͸�16λ�Ĵ���SCI_CHTIMEMS��ɡ������дSCI_CHTIMEMSʱ��SCI_CHTIME����������Ч����дSCI_CHTIMELSʱSCI_CHTIME�Ż���Ч���������SCI_CHTIME���������ø�16λ�������õ�16λ��
   λ����UNION�ṹ:  SOC_SCI_CHTIMELS_UNION */
#define SOC_SCI_CHTIMELS_ADDR(base)                   ((base) + (0x0044))

/* �Ĵ���˵���������ַ������ʱ��ֵ��16λ�Ĵ�����
   λ����UNION�ṹ:  SOC_SCI_CHTIMEMS_UNION */
#define SOC_SCI_CHTIMEMS_ADDR(base)                   ((base) + (0x0048))

/* �Ĵ���˵�������տ�����ʱ��ֵ��16λ�Ĵ�����
            SCI_BLKTIME������տ���������ʱ��������ETUΪ��λ������ʱ��������ʼʱ�������һ�����͵������ַ�����ʼ�أ������ǵ�һ���ӿ����صĽ����ַ�ʱ�̡������ʱ�ᴥ��blktoutintr�жϣ���SCI_RIS[blkoutim]��1��
            (CH)SCI_BLKTIME�Ĵ������ɵ�16λ�Ĵ���SCI_BLKTIMELS�͸�16λ�Ĵ���SCI_BLKTIMEMS��ɡ������дSCI_BLKTIMEMSʱ��SCI_BLKTIME����������Ч��дSCI_BLKTIMELSʱSCI_BLKTIME�Ż���Ч���������SCI_BLKTIME���������ø�16λ�������õ�16λ��
   λ����UNION�ṹ:  SOC_SCI_BLKTIMELS_UNION */
#define SOC_SCI_BLKTIMELS_ADDR(base)                  ((base) + (0x004C))

/* �Ĵ���˵�������տ�����ʱ��ֵ��16λ�Ĵ�����
   λ����UNION�ṹ:  SOC_SCI_BLKTIMEMS_UNION */
#define SOC_SCI_BLKTIMEMS_ADDR(base)                  ((base) + (0x0050))

/* �Ĵ���˵�����ַ��䱣��ʱ�����Ĵ������üĴ������嵱SCI�����������ַ�ʱ�����������ַ���ʼ��֮����С����Ķ��Ᵽ��ʱ�䣨��ETUΪ��λ��������Э���ж����ȫ�ֽӿ��ֽ�TC1����ATR�����еõ���������
   λ����UNION�ṹ:  SOC_SCI_CHGUARD_UNION */
#define SOC_SCI_CHGUARD_ADDR(base)                    ((base) + (0x0054))

/* �Ĵ���˵������䱣��ʱ�����Ĵ����������������ַ��Ĵ��䷽���෴ʱ������ʼ��֮���ʱ����ΪSCI_BLKGUARD��
   λ����UNION�ṹ:  SOC_SCI_BLKGUARD_UNION */
#define SOC_SCI_BLKGUARD_ADDR(base)                   ((base) + (0x0058))

/* �Ĵ���˵��������FIFO����ʱ��ֵ�Ĵ�����������FIFO�����ַ��ҳ���SCI_RXTIME�������ʱ����Ȼû�б��������򴥷����ն���ʱ�ж�scirtout��SCI_RIS[rtoutris]����1��
            (CH)����ʹ�ý���FIFO����ʱ�жϹ���ʱ��SCI_RXTIME[rxtime]����Ϊ0x0000��
   λ����UNION�ṹ:  SOC_SCI_RXTIME_UNION */
#define SOC_SCI_RXTIME_ADDR(base)                     ((base) + (0x005C))

/* �Ĵ���˵����FIFO״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SCI_FIFOSTATUS_UNION */
#define SOC_SCI_FIFOSTATUS_ADDR(base)                 ((base) + (0x0060))

/* �Ĵ���˵��������FIFO���ݸ����Ĵ�����
            (NH)
            (NL)���üĴ������ط���FIFO���ַ��ĸ��������������ڷ��͵��ַ�����
            (NL)�������ַ��������ִ���T0Э�飩�������ش����������������ֵ����SCI_RETRY�ж��壩���ᴥ��txerr�жϣ���SCI_RIS[txerrris]��1����ʱ�ڽ�����һ�δ���֮ǰ������FIFO���뱻��գ�д�üĴ�������
   λ����UNION�ṹ:  SOC_SCI_TXCOUNT_UNION */
#define SOC_SCI_TXCOUNT_ADDR(base)                    ((base) + (0x0064))

/* �Ĵ���˵��������FIFO���ݸ����Ĵ�����
   λ����UNION�ṹ:  SOC_SCI_RXCOUNT_UNION */
#define SOC_SCI_RXCOUNT_ADDR(base)                    ((base) + (0x0068))

/* �Ĵ���˵�����ж����μĴ�����BitֵΪ0��ʾ���Σ�Ϊ1��ʾ�����Ρ�
   λ����UNION�ṹ:  SOC_SCI_IMSC_UNION */
#define SOC_SCI_IMSC_ADDR(base)                       ((base) + (0x006C))

/* �Ĵ���˵����ԭʼ�жϼĴ������üĴ��������ж�����֮ǰ��ԭʼ�жϡ�BitֵΪ0��ʾ���жϣ�Ϊ1��ʾ���жϡ�
   λ����UNION�ṹ:  SOC_SCI_RIS_UNION */
#define SOC_SCI_RIS_ADDR(base)                        ((base) + (0x0070))

/* �Ĵ���˵�������κ��жϼĴ������üĴ����ǳ�ʼ�жϾ������κ�Ľ����BitֵΪ0��ʾ���жϣ�Ϊ1��ʾ���жϡ�
   λ����UNION�ṹ:  SOC_SCI_MIS_UNION */
#define SOC_SCI_MIS_ADDR(base)                        ((base) + (0x0074))

/* �Ĵ���˵�����ж�����Ĵ�����BitֵΪ0��ʾ������жϣ�Ϊ1��ʾ����жϡ�
   λ����UNION�ṹ:  SOC_SCI_ICR_UNION */
#define SOC_SCI_ICR_ADDR(base)                        ((base) + (0x0078))

/* �Ĵ���˵����ͬ��ģʽ����Ĵ������üĴ�������ͬ��ģʽ������ʹ�ܡ�ʱ��ʹ�ܡ���λ�͵�Դ���Ƶȣ����ṩ״̬�Ĵ�������Ӧ��״̬λ�ڼ���ͷš��ȸ�λ�������Զ����¡�
   λ����UNION�ṹ:  SOC_SCI_SYNCACT_UNION */
#define SOC_SCI_SYNCACT_ADDR(base)                    ((base) + (0x007C))

/* �Ĵ���˵����ͬ��ģʽ����ʱ�Ӻ��������Ĵ������üĴ������ڿ���ͬ��ģʽ�·���ʱ�Ӻ����ݡ�
   λ����UNION�ṹ:  SOC_SCI_SYNCTX_UNION */
#define SOC_SCI_SYNCTX_ADDR(base)                     ((base) + (0x0080))

/* �Ĵ���˵����ͬ��ģʽ����ʱ�Ӻ��������Ĵ������üĴ������ڿ���ͬ��ģʽ�½���ʱ�Ӻ����ݡ�
   λ����UNION�ṹ:  SOC_SCI_SYNCRX_UNION */
#define SOC_SCI_SYNCRX_ADDR(base)                     ((base) + (0x0084))





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
                     (1/1) SCI0
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_SCI_DATA_UNION
 �ṹ˵��  : DATA �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x0000�����:16
 �Ĵ���˵��: SCI���ݼĴ��������ڷ��ͻ�����ַ�����SCI����������ݽӿڡ�
            ���ֻ��������SCI_CR1[mode]Ϊ1֮�󣬲ſɶԴ˼Ĵ�������д��������SCI_CR1[mode]Ϊ0ʱ���������ԶԸüĴ�����д���������������á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  scidata  : 8;  /* bit[0-7] : 8bit�ַ���д���ݡ� */
        unsigned short  parity   : 1;  /* bit[8]   : ��żУ������־λ������ʱ��λ������һ���ͣ�����ʱ������ݸ�λ�ж���żУ���Ƿ���ȷ��
                                                     0����ȷ��
                                                     1������ */
        unsigned short  reserved : 7;  /* bit[9-15]: ������ */
    } reg;
} SOC_SCI_DATA_UNION;
#endif
#define SOC_SCI_DATA_scidata_START   (0)
#define SOC_SCI_DATA_scidata_END     (7)
#define SOC_SCI_DATA_parity_START    (8)
#define SOC_SCI_DATA_parity_END      (8)


/*****************************************************************************
 �ṹ��    : SOC_SCI_CR0_UNION
 �ṹ˵��  : CR0 �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x0000�����:16
 �Ĵ���˵��: SCI���ƼĴ��������ڿ���ʱ��ֹͣ����żУ�顢�������֡�����λ����ȹ��ܡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  sense    : 1;  /* bit[0]   : ���ݱ��غ�У����ؼ����λ���ơ�
                                                     0��ֱ�Ӽ�⣻
                                                     1��ȡ������IO���ϵ����ݺ�У��λ�� */
        unsigned short  order    : 1;  /* bit[1]   : �ַ��ĸߵ�λ˳��
                                                     0����ʼλ��start bit�����ȷ���/�������λ��
                                                     1����ʼλ��start bit�����ȷ���/�������λ�� */
        unsigned short  txparity : 1;  /* bit[2]   : ����ģʽ�µ�У�鷽ʽ���ơ�
                                                     0��żУ�飻
                                                     1����У�顣 */
        unsigned short  txnak    : 1;  /* bit[3]   : �ڷ���ģʽ�µ���Ϊ���ơ�
                                                     0��SCI�������շ��Ƿ�I/O�����ͣ�
                                                     1��SCI�����շ��Ƿ�I/O������ָʾУ����� */
        unsigned short  rxparity : 1;  /* bit[4]   : ����ģʽ�µ�У�鷽ʽ���ơ�
                                                     0��żУ�飻
                                                     1����У�顣 */
        unsigned short  rxnak    : 1;  /* bit[5]   : �ڽ���ģʽ�µ���Ϊ���ơ�
                                                     0����⵽��żУ�����ʱ��I/O�߲����ͣ�
                                                     1����⵽��żУ�����ʱ��I/O�����͡� */
        unsigned short  clkdis   : 1;  /* bit[6]   : ʱ�ӵ�������ֹͣ����λ��
                                                     0������ʱ�ӣ�
                                                     1��ֹͣʱ�ӡ� */
        unsigned short  clkval   : 1;  /* bit[7]   : ���ܿ�ʱ�ӱ���״̬���ơ�
                                                     0��inactiveʱ��ʱ�ӱ��ֵ͵�ƽ��1��inactiveʱ��ʱ�ӱ��ָߵ�ƽ�� */
        unsigned short  reserved : 8;  /* bit[8-15]: ������ */
    } reg;
} SOC_SCI_CR0_UNION;
#endif
#define SOC_SCI_CR0_sense_START     (0)
#define SOC_SCI_CR0_sense_END       (0)
#define SOC_SCI_CR0_order_START     (1)
#define SOC_SCI_CR0_order_END       (1)
#define SOC_SCI_CR0_txparity_START  (2)
#define SOC_SCI_CR0_txparity_END    (2)
#define SOC_SCI_CR0_txnak_START     (3)
#define SOC_SCI_CR0_txnak_END       (3)
#define SOC_SCI_CR0_rxparity_START  (4)
#define SOC_SCI_CR0_rxparity_END    (4)
#define SOC_SCI_CR0_rxnak_START     (5)
#define SOC_SCI_CR0_rxnak_END       (5)
#define SOC_SCI_CR0_clkdis_START    (6)
#define SOC_SCI_CR0_clkdis_END      (6)
#define SOC_SCI_CR0_clkval_START    (7)
#define SOC_SCI_CR0_clkval_END      (7)


/*****************************************************************************
 �ṹ��    : SOC_SCI_CR1_UNION
 �ṹ˵��  : CR1 �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x0000�����:16
 �Ĵ���˵��: SCI���ƼĴ��������ڿ���ͬ��/�첽������ģʽ�����ͽ���ģʽ���鳬ʱ��ATR��ʱ�ȹ��ܡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  atrden   : 1;  /* bit[0]   : ATR timeoutʹ�ܿ��ơ�
                                                     0����ֹ��
                                                     1��ʹ�ܡ� */
        unsigned short  blken    : 1;  /* bit[1]   : Block timeoutʹ�ܿ��ơ�
                                                     0����ֹ��
                                                     1��ʹ�ܡ� */
        unsigned short  mode     : 1;  /* bit[2]   : ����/����ģʽ���á�
                                                     0������ģʽ��
                                                     1������ģʽ�� */
        unsigned short  clkz1    : 1;  /* bit[3]   : SCICLK�ź�����ģʽѡ���źš�
                                                     1��SCICLK�ź�����Ϊ������open drain����
                                                     0��SCICLK�ź�����Ϊbuffer output�� */
        unsigned short  bgten    : 1;  /* bit[4]   : Block guard timerʹ�ܿ��ơ�
                                                     0����ֹ��
                                                     1��ʹ�ܡ� */
        unsigned short  exdbnce  : 1;  /* bit[5]   : ��ȥ����·ʹ�ܡ�ʹ�÷�����μ�SCI_STABLE��˵����
                                                     0��ʹ�������ڲ�debounce time��
                                                     1����·�ڲ�debounce time�Ĳ��ɱ�̲��֡� */
        unsigned short  synccard : 1;  /* bit[6]   : ����ͬ��/�첽������ģʽ��
                                                     0���첽ģʽ��
                                                     1��ͬ��ģʽ�� */
        unsigned short  reserved : 9;  /* bit[7-15]: ������ */
    } reg;
} SOC_SCI_CR1_UNION;
#endif
#define SOC_SCI_CR1_atrden_START    (0)
#define SOC_SCI_CR1_atrden_END      (0)
#define SOC_SCI_CR1_blken_START     (1)
#define SOC_SCI_CR1_blken_END       (1)
#define SOC_SCI_CR1_mode_START      (2)
#define SOC_SCI_CR1_mode_END        (2)
#define SOC_SCI_CR1_clkz1_START     (3)
#define SOC_SCI_CR1_clkz1_END       (3)
#define SOC_SCI_CR1_bgten_START     (4)
#define SOC_SCI_CR1_bgten_END       (4)
#define SOC_SCI_CR1_exdbnce_START   (5)
#define SOC_SCI_CR1_exdbnce_END     (5)
#define SOC_SCI_CR1_synccard_START  (6)
#define SOC_SCI_CR1_synccard_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_SCI_CR2_UNION
 �ṹ˵��  : CR2 �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x0000�����:16
 �Ĵ���˵��: SCI���ƼĴ�����д�üĴ�������Ӧλ�ᴥ��SCI�Կ��ļ���ͷŻ���λ��������SCI�������ͷſ���״̬ʱ���ԸüĴ�����д�����������ԡ�������ʱ�򣬶�SCI_CR2[finish]д1��ʹSCI�������Ϳ��ͷ����С�
            (CH)
            (CL)����ԸüĴ�����д���������ں��ʵĿ������׶ν��С������ʵ�д������������Ԥ�ڵĺ����
            (CL)ֻ�е����ܿ�������֮��������ܶԿ�������λ������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  startup  : 1;  /* bit[0]   : �������ܿ�������
                                                     0����Ч��
                                                     1���������ܿ���
                                                     <B>ע�⣺�������ܿ��������豸��⵽���λ��д������д��Ч��</B> */
        unsigned short  finish   : 1;  /* bit[1]   : �ͷ����ܿ�������
                                                     0����Ч��
                                                     1���ͷ����ܿ���
                                                     <B>ע�⣺�������ܿ��������豸��⵽���λ��д������д��Ч��</B> */
        unsigned short  wreset   : 1;  /* bit[2]   : �Կ�����λ������
                                                     0����Ч��
                                                     1�������ܿ�������λ������
                                                     <B>ע�⣺���ڼ���������ɺ��λ��д������д��Ч��</B> */
        unsigned short  reserved : 13; /* bit[3-15]: ������ */
    } reg;
} SOC_SCI_CR2_UNION;
#endif
#define SOC_SCI_CR2_startup_START   (0)
#define SOC_SCI_CR2_startup_END     (0)
#define SOC_SCI_CR2_finish_START    (1)
#define SOC_SCI_CR2_finish_END      (1)
#define SOC_SCI_CR2_wreset_START    (2)
#define SOC_SCI_CR2_wreset_END      (2)


/*****************************************************************************
 �ṹ��    : SOC_SCI_CLKICC_UNION
 �ṹ˵��  : CLKICC �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x0000�����:16
 �Ĵ���˵��: ���ܿ�ʱ��Ƶ�ʼĴ������üĴ����������ⲿ���ܿ�ʱ�ӵķ�Ƶ���ӡ����ܿ�ʱ��Ƶ�ʵļ��㹫ʽΪ��FSCI_CLK=(FREFCLK)/(clkicc+1)x2 �����У�FSCI_CLKΪʱ��Ƶ�ʣ�FREFCLKΪ�ο�ʱ��Ƶ�ʣ�clkiccΪSCI_CLKICC[clkicc]���õ�ֵ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  clkicc   : 8;  /* bit[0-7] : ���ܿ�ʱ�ӵķ�Ƶϵ�����ɲο�ʱ�ӷ�Ƶ�õ�����������Ϊ0��255�� */
        unsigned short  reserved : 8;  /* bit[8-15]: ������ */
    } reg;
} SOC_SCI_CLKICC_UNION;
#endif
#define SOC_SCI_CLKICC_clkicc_START    (0)
#define SOC_SCI_CLKICC_clkicc_END      (7)


/*****************************************************************************
 �ṹ��    : SOC_SCI_VALUE_UNION
 �ṹ˵��  : VALUE �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x0000�����:16
 �Ĵ���˵��: ETU��SCI_BAUD�������Ĵ��������ڼ���ETU��������Ϊ5��255֮�������ֵ��ETU�ļ��㹫ʽΪ��Etu=(1+baud) x value��baudΪSCI_BAUD[baud]���õ�ֵ��valueΪSCI_VALUE[value]���õ�ֵ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  value    : 8;  /* bit[0-7] : ÿ��ETU��Elementary Time Unit����SCIBAUD��������Ŀ�� */
        unsigned short  reserved : 8;  /* bit[8-15]: ������ */
    } reg;
} SOC_SCI_VALUE_UNION;
#endif
#define SOC_SCI_VALUE_value_START     (0)
#define SOC_SCI_VALUE_value_END       (7)


/*****************************************************************************
 �ṹ��    : SOC_SCI_BAUD_UNION
 �ṹ˵��  : BAUD �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x0000�����:16
 �Ĵ���˵��: ������ʱ�ӷ�Ƶֵ�Ĵ��������ڼ���ETU����������Ϊ0x1��0xFFFF֮�������ֵ����μ���SCI_VALUE����ETU�ļ��㹫ʽ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  baud : 16; /* bit[0-15]: �����ʵ�ʱ�ӷ�Ƶֵ�� */
    } reg;
} SOC_SCI_BAUD_UNION;
#endif
#define SOC_SCI_BAUD_baud_START  (0)
#define SOC_SCI_BAUD_baud_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SCI_TIDE_UNION
 �ṹ˵��  : TIDE �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x0000�����:16
 �Ĵ���˵��: ���ͽ���FIFO�������ֵ�Ĵ�����
            (NH)
            (NL)TXFIFO�е��ַ�ֻ���ڳɹ����ͺ�Żᱻ�Ƴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  txtide   : 6;  /* bit[0-5]  : ����SCITXTIDEINTR�жϵĴ���ֵ��
                                                      TXFIFO�е��ַ�����С�ڻ����SCI_TIDE[txtide]ʱ�ᴥ��txtideintr�жϡ� */
        unsigned short  rxtide   : 6;  /* bit[6-11] : ����SCIRXTIDEINTR�жϵĴ���ֵ��
                                                      RXFIFO�е��ַ��������ڻ����SCI_TIDE[rxtide]ʱ�ᴥ��rxtideintr�жϡ� */
        unsigned short  reserved : 4;  /* bit[12-15]: ������ */
    } reg;
} SOC_SCI_TIDE_UNION;
#endif
#define SOC_SCI_TIDE_txtide_START    (0)
#define SOC_SCI_TIDE_txtide_END      (5)
#define SOC_SCI_TIDE_rxtide_START    (6)
#define SOC_SCI_TIDE_rxtide_END      (11)


/*****************************************************************************
 �ṹ��    : SOC_SCI_DMACR_UNION
 �ṹ˵��  : DMACR �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x0000�����:16
 �Ĵ���˵��: DMA���ƼĴ��������ڿ���DMA���ͺͽ������ݡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  rxdmae   : 1;  /* bit[0]   : ����FIFO��DAMʹ��λ��
                                                     0����ֹ��
                                                     1��ʹ�ܡ� */
        unsigned short  txdmae   : 1;  /* bit[1]   : ����FIFO��DMAʹ��λ��
                                                     0����ֹ��
                                                     1��ʹ�ܡ� */
        unsigned short  reserved : 14; /* bit[2-15]: ������ */
    } reg;
} SOC_SCI_DMACR_UNION;
#endif
#define SOC_SCI_DMACR_rxdmae_START    (0)
#define SOC_SCI_DMACR_rxdmae_END      (0)
#define SOC_SCI_DMACR_txdmae_START    (1)
#define SOC_SCI_DMACR_txdmae_END      (1)


/*****************************************************************************
 �ṹ��    : SOC_SCI_STABLE_UNION
 �ṹ˵��  : STABLE �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x0000�����:16
 �Ĵ���˵��: ���ܿ������ȶ�ʱ��Ĵ����������ܿ�����ź�SCI_DETECT�ź���Ч����Ҫ�ȶ�����SCI_STABLE�Ĵ���ֵ��Ӧ�Ĺ̶���ʱ��TSTABLE������TSTABLEʱ�䣨��λΪ�룩�󴥷�cardinintr�жϣ��������ܿ�����ȷ���롣
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  stable   : 10; /* bit[0-9]  : ���忨����źű����ȶ��ߵ�ƽ��ʱ�䡣 */
        unsigned short  reserved : 6;  /* bit[10-15]: ������ */
    } reg;
} SOC_SCI_STABLE_UNION;
#endif
#define SOC_SCI_STABLE_stable_START    (0)
#define SOC_SCI_STABLE_stable_END      (9)


/*****************************************************************************
 �ṹ��    : SOC_SCI_ATIME_UNION
 �ṹ˵��  : ATIME �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x0000�����:16
 �Ĵ���˵��: ���ܿ�����ʱ��Ĵ������üĴ�����[atime]λ����ָʾ����λ�ͼ����3���׶εĳ���ʱ�䡣
            (NH)
            (NL)Ϊ���㿨��λ��Ҫ��SCI_ATIME[atime]����Ϊ40000���ӿڿ�ʱ�ӣ�SCI_CLK�����ڡ�
            (NL)�ò���Ҳ�����������ܿ��Ե�Դ�ȶ���Ҫ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  atime : 16; /* bit[0-15]: ���忨�������е�3���׶��У�ÿ���׶εĳ���ʱ�䣨SCI�ӿڿ�ʱ��SCI_CLK���������� */
    } reg;
} SOC_SCI_ATIME_UNION;
#endif
#define SOC_SCI_ATIME_atime_START  (0)
#define SOC_SCI_ATIME_atime_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SCI_DTIME_UNION
 �ṹ˵��  : DTIME �Ĵ����ṹ���塣��ַƫ����:0x002C����ֵ:0x0000�����:16
 �Ĵ���˵��: ���ܿ��ͷ�ʱ��Ĵ������üĴ�����{dtime]λ����ָʾ���ͷŵ�3���׶εĳ���ʱ�䣬��λΪSCI�ο�ʱ�����ڡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  dtime : 16; /* bit[0-15]: ���忨�ͷ����е�3���׶��У�ÿ���׶εĳ���ʱ�䣨SCI�ο�ʱ������������ */
    } reg;
} SOC_SCI_DTIME_UNION;
#endif
#define SOC_SCI_DTIME_dtime_START  (0)
#define SOC_SCI_DTIME_dtime_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SCI_ATRSTIME_UNION
 �ṹ˵��  : ATRSTIME �Ĵ����ṹ���塣��ַƫ����:0x0030����ֵ:0x0000�����:16
 �Ĵ���˵��: �ȴ���ʼ����ATRʱ����ֵ�Ĵ������������ܿ�ʱ�Ӷ����˴����ܿ���λ��������ʼ����ATR��һ���ַ���ʱ����ֵ��ATR�ȴ���ʼ���ճ�ʱ��ᴥ��atrstoutintr�жϣ���SCI_RIS[atrstoutim]��1��
            (NH)SCI_ATRSTIME[atrstime]���������ʼ��Ϊ40000��SCI_CLK�ӿڿ�ʱ�����ڡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  atrstime : 16; /* bit[0-15]: ����ATR����������ʱ����ֵʱ�䣨SCI�ӿڿ�ʱ��SCI_CLK���������� */
    } reg;
} SOC_SCI_ATRSTIME_UNION;
#endif
#define SOC_SCI_ATRSTIME_atrstime_START  (0)
#define SOC_SCI_ATRSTIME_atrstime_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SCI_ATRDTIME_UNION
 �ṹ˵��  : ATRDTIME �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x0000�����:16
 �Ĵ���˵��: ����ATRʱ����ֵ�Ĵ�����SCI�ڽ���ATR�����У��ӵ�һ��ATR�ַ���ʼ���յ����һ��ATR�ַ����ս�������������üĴ����������ʱ�䣨��ETUΪ��λ�����ᴥ���жϣ���SCI_RIS[atrdtoutris]��1��
            (NH)
            (NL)��ʹ�øüĴ���֮ǰ������������SCI_CR1[atrden]Ϊ1����ʹ�ܳ�ʱ�������ơ�
            (NL)����Э�飬�üĴ�����������Ϊ19200��ETU����0x4B00��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  atrdtime : 16; /* bit[0-15]: ����ӵ�һ��ATR�ַ���ʼλ�����ATR���ճ�ʱ����ֵ����ETUΪ��λ���� */
    } reg;
} SOC_SCI_ATRDTIME_UNION;
#endif
#define SOC_SCI_ATRDTIME_atrdtime_START  (0)
#define SOC_SCI_ATRDTIME_atrdtime_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SCI_STOPTIME_UNION
 �ṹ˵��  : STOPTIME �Ĵ����ṹ���塣��ַƫ����:0x0038����ֵ:0x0000�����:16
 �Ĵ���˵��: ʱ��ֹͣʱ��Ĵ�����������ʱ��ֹͣʱ������SCI_STOPTIME�������ʱ�䣨��λΪSCI�ӿڿ�ʱ��SCI_CLK���ڣ������ܿ�ʱ����Ч���������жϣ���SCI_RIS[clkstpris]��1��
            (NH)����Э�飬��ֵ��СΪ1860��SCIʱ�����ڣ���SCI_STOPTIME[stoptime]��Ҫ����Ϊ0x744��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  stoptime : 12; /* bit[0-11] : ���ܿ�ʱ��ֹͣʱ�䣨SCI���ܿ�ʱ��SCI_CLK�������������ӿ�ʱ��ֹͣ����Ϊinactive������ʱ�䡣 */
        unsigned short  reserved : 4;  /* bit[12-15]: ������ */
    } reg;
} SOC_SCI_STOPTIME_UNION;
#endif
#define SOC_SCI_STOPTIME_stoptime_START  (0)
#define SOC_SCI_STOPTIME_stoptime_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SCI_STARTTIME_UNION
 �ṹ˵��  : STARTTIME �Ĵ����ṹ���塣��ַƫ����:0x003C����ֵ:0x0000�����:16
 �Ĵ���˵��: ���ܿ�ʱ�ӻָ�ʱ��Ĵ�����������ʱ�ӻָ�ʱ������SCI_STARTTIME�������ʱ�䣨��λΪSCI�ӿڿ�ʱ��SCI_CLK���ڣ���SCI�����ܿ����ܽ������ݴ��䣬�������жϣ���SCI_RIS[clkactris]��1��
            (NH)����Э�飬��ֵ��СӦΪ700��SCIʱ�����ڣ���SCI_STARTTIME[starttimr]������Ҫ����Ϊ0x2BC��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  starttime : 12; /* bit[0-11] : ���忪ʼ������ʱ�ӵ����ݴ����ܹ����У�active��������̳�����ʱ�䣨SCI�ӿڿ�ʱ��SCI_CLK���������� */
        unsigned short  reserved  : 4;  /* bit[12-15]: ������ */
    } reg;
} SOC_SCI_STARTTIME_UNION;
#endif
#define SOC_SCI_STARTTIME_starttime_START  (0)
#define SOC_SCI_STARTTIME_starttime_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_SCI_RETRY_UNION
 �ṹ˵��  : RETRY �Ĵ����ṹ���塣��ַƫ����:0x0040����ֵ:0x0000�����:16
 �Ĵ���˵��: ���ͽ������Դ����Ĵ������üĴ��������˷��ͻ���������ش��Ĵ�������������Ϊ��
            (I)��SCI_CR0[txnak]ʹ��ʱ��SCI�����շ��Ƿ��ʶУ�����SCI_RETRY[rxretry]�������У���������´����������������������txerrintr�жϣ���SCI_RIS[txerrris]��1��
            (I)��SCI_CR0[rxnak]ʹ��ʱ��SCI����յ��������Ƿ����У�����SCI_RETRY[txretry]�������У���������´��������������������ô�����Ȼ���մ��󣬽�SCI_DATA[parity]��1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  txretry  : 3;  /* bit[0-2] : ���嵱���ͳ���У�����ʱ�����ķ������Դ����� */
        unsigned short  rxretry  : 3;  /* bit[3-5] : ���嵱���ճ���У�����ʱ�����Ľ������Դ����� */
        unsigned short  reserved : 10; /* bit[6-15]: ������ */
    } reg;
} SOC_SCI_RETRY_UNION;
#endif
#define SOC_SCI_RETRY_txretry_START   (0)
#define SOC_SCI_RETRY_txretry_END     (2)
#define SOC_SCI_RETRY_rxretry_START   (3)
#define SOC_SCI_RETRY_rxretry_END     (5)


/*****************************************************************************
 �ṹ��    : SOC_SCI_CHTIMELS_UNION
 �ṹ˵��  : CHTIMELS �Ĵ����ṹ���塣��ַƫ����:0x0044����ֵ:0x0000�����:16
 �Ĵ���˵��: �����ַ������ʱ��ֵ��16λ�Ĵ�����
            SCI_CHTIME�Ĵ�������ӿ����յ������������ַ�����ʼ��֮����������ʱ��������ETUΪ��λ����������յ����ַ������ʱ�ᴥ��chtoutintr�жϣ���SCI_RIS[chtoutris]��1��
            (CH)SCI_CHTIME�Ĵ������ɵ�16λ�Ĵ���SCI_CHTIMELS�͸�16λ�Ĵ���SCI_CHTIMEMS��ɡ������дSCI_CHTIMEMSʱ��SCI_CHTIME����������Ч����дSCI_CHTIMELSʱSCI_CHTIME�Ż���Ч���������SCI_CHTIME���������ø�16λ�������õ�16λ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  chtimels : 16; /* bit[0-15]: ��������ַ������ʱ��ֵ�Ĵ���SCICHTIME�ĵ�16λ�� */
    } reg;
} SOC_SCI_CHTIMELS_UNION;
#endif
#define SOC_SCI_CHTIMELS_chtimels_START  (0)
#define SOC_SCI_CHTIMELS_chtimels_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SCI_CHTIMEMS_UNION
 �ṹ˵��  : CHTIMEMS �Ĵ����ṹ���塣��ַƫ����:0x0048����ֵ:0x0000�����:16
 �Ĵ���˵��: �����ַ������ʱ��ֵ��16λ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  chtimems : 16; /* bit[0-15]: ��������ַ������ʱ��ֵ�Ĵ���SCICHTIME�ĸ�16λ�� */
    } reg;
} SOC_SCI_CHTIMEMS_UNION;
#endif
#define SOC_SCI_CHTIMEMS_chtimems_START  (0)
#define SOC_SCI_CHTIMEMS_chtimems_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SCI_BLKTIMELS_UNION
 �ṹ˵��  : BLKTIMELS �Ĵ����ṹ���塣��ַƫ����:0x004C����ֵ:0x0000�����:16
 �Ĵ���˵��: ���տ�����ʱ��ֵ��16λ�Ĵ�����
            SCI_BLKTIME������տ���������ʱ��������ETUΪ��λ������ʱ��������ʼʱ�������һ�����͵������ַ�����ʼ�أ������ǵ�һ���ӿ����صĽ����ַ�ʱ�̡������ʱ�ᴥ��blktoutintr�жϣ���SCI_RIS[blkoutim]��1��
            (CH)SCI_BLKTIME�Ĵ������ɵ�16λ�Ĵ���SCI_BLKTIMELS�͸�16λ�Ĵ���SCI_BLKTIMEMS��ɡ������дSCI_BLKTIMEMSʱ��SCI_BLKTIME����������Ч��дSCI_BLKTIMELSʱSCI_BLKTIME�Ż���Ч���������SCI_BLKTIME���������ø�16λ�������õ�16λ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  blktimels : 16; /* bit[0-15]: ������տ�����ʱ��ֵ�Ĵ���SCIBLKTIME�ĵ�16λ�� */
    } reg;
} SOC_SCI_BLKTIMELS_UNION;
#endif
#define SOC_SCI_BLKTIMELS_blktimels_START  (0)
#define SOC_SCI_BLKTIMELS_blktimels_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SCI_BLKTIMEMS_UNION
 �ṹ˵��  : BLKTIMEMS �Ĵ����ṹ���塣��ַƫ����:0x0050����ֵ:0x0000�����:16
 �Ĵ���˵��: ���տ�����ʱ��ֵ��16λ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  blktimems : 16; /* bit[0-15]: ������տ�����ʱ��ֵ�Ĵ���SCIBLKTIME���ĸ�16λ�� */
    } reg;
} SOC_SCI_BLKTIMEMS_UNION;
#endif
#define SOC_SCI_BLKTIMEMS_blktimems_START  (0)
#define SOC_SCI_BLKTIMEMS_blktimems_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SCI_CHGUARD_UNION
 �ṹ˵��  : CHGUARD �Ĵ����ṹ���塣��ַƫ����:0x0054����ֵ:0x0000�����:16
 �Ĵ���˵��: �ַ��䱣��ʱ�����Ĵ������üĴ������嵱SCI�����������ַ�ʱ�����������ַ���ʼ��֮����С����Ķ��Ᵽ��ʱ�䣨��ETUΪ��λ��������Э���ж����ȫ�ֽӿ��ֽ�TC1����ATR�����еõ���������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  scichguard : 8;  /* bit[0-7] : �ַ��䱣��ʱ��������ETUΪ��λ���������������ַ���ʼλ֮������ʱ�䡣 */
        unsigned short  reserved   : 8;  /* bit[8-15]: ������ */
    } reg;
} SOC_SCI_CHGUARD_UNION;
#endif
#define SOC_SCI_CHGUARD_scichguard_START  (0)
#define SOC_SCI_CHGUARD_scichguard_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCI_BLKGUARD_UNION
 �ṹ˵��  : BLKGUARD �Ĵ����ṹ���塣��ַƫ����:0x0058����ֵ:0x0000�����:16
 �Ĵ���˵��: ��䱣��ʱ�����Ĵ����������������ַ��Ĵ��䷽���෴ʱ������ʼ��֮���ʱ����ΪSCI_BLKGUARD��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  sciblkguard : 8;  /* bit[0-7] : ���������������෴�����ַ�֮������ʱ�䣨��ETUΪ��λ���� */
        unsigned short  reserved    : 8;  /* bit[8-15]: ������ */
    } reg;
} SOC_SCI_BLKGUARD_UNION;
#endif
#define SOC_SCI_BLKGUARD_sciblkguard_START  (0)
#define SOC_SCI_BLKGUARD_sciblkguard_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_SCI_RXTIME_UNION
 �ṹ˵��  : RXTIME �Ĵ����ṹ���塣��ַƫ����:0x005C����ֵ:0x0000�����:16
 �Ĵ���˵��: ����FIFO����ʱ��ֵ�Ĵ�����������FIFO�����ַ��ҳ���SCI_RXTIME�������ʱ����Ȼû�б��������򴥷����ն���ʱ�ж�scirtout��SCI_RIS[rtoutris]����1��
            (CH)����ʹ�ý���FIFO����ʱ�жϹ���ʱ��SCI_RXTIME[rxtime]����Ϊ0x0000��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  rxtime : 16; /* bit[0-15]: ���ն���ʱʱ��ֵ��SCI�ӿڿ�ʱ��SCI_CLK���������� */
    } reg;
} SOC_SCI_RXTIME_UNION;
#endif
#define SOC_SCI_RXTIME_rxtime_START  (0)
#define SOC_SCI_RXTIME_rxtime_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SCI_FIFOSTATUS_UNION
 �ṹ˵��  : FIFOSTATUS �Ĵ����ṹ���塣��ַƫ����:0x0060����ֵ:0x000A�����:16
 �Ĵ���˵��: FIFO״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  txff     : 1;  /* bit[0]   : ����FIFO��״̬��
                                                     0��δ����
                                                     1������ */
        unsigned short  txfe     : 1;  /* bit[1]   : ����FIFO��״̬��
                                                     0���ǿգ�
                                                     1���ա� */
        unsigned short  rxff     : 1;  /* bit[2]   : ����FIFO��״̬��
                                                     0��δ����
                                                     1������ */
        unsigned short  rxfe     : 1;  /* bit[3]   : ����FIFO��״̬��
                                                     0���ǿգ�
                                                     1���ա� */
        unsigned short  reserved : 12; /* bit[4-15]: ������ */
    } reg;
} SOC_SCI_FIFOSTATUS_UNION;
#endif
#define SOC_SCI_FIFOSTATUS_txff_START      (0)
#define SOC_SCI_FIFOSTATUS_txff_END        (0)
#define SOC_SCI_FIFOSTATUS_txfe_START      (1)
#define SOC_SCI_FIFOSTATUS_txfe_END        (1)
#define SOC_SCI_FIFOSTATUS_rxff_START      (2)
#define SOC_SCI_FIFOSTATUS_rxff_END        (2)
#define SOC_SCI_FIFOSTATUS_rxfe_START      (3)
#define SOC_SCI_FIFOSTATUS_rxfe_END        (3)


/*****************************************************************************
 �ṹ��    : SOC_SCI_TXCOUNT_UNION
 �ṹ˵��  : TXCOUNT �Ĵ����ṹ���塣��ַƫ����:0x0064����ֵ:0x0000�����:16
 �Ĵ���˵��: ����FIFO���ݸ����Ĵ�����
            (NH)
            (NL)���üĴ������ط���FIFO���ַ��ĸ��������������ڷ��͵��ַ�����
            (NL)�������ַ��������ִ���T0Э�飩�������ش����������������ֵ����SCI_RETRY�ж��壩���ᴥ��txerr�жϣ���SCI_RIS[txerrris]��1����ʱ�ڽ�����һ�δ���֮ǰ������FIFO���뱻��գ�д�üĴ�������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  txcount  : 6;  /* bit[0-5] : ���üĴ������ط���FIFO�е��ַ�����д�üĴ���������ֵ������շ���FIFO�� */
        unsigned short  reserved : 10; /* bit[6-15]: ������ */
    } reg;
} SOC_SCI_TXCOUNT_UNION;
#endif
#define SOC_SCI_TXCOUNT_txcount_START   (0)
#define SOC_SCI_TXCOUNT_txcount_END     (5)


/*****************************************************************************
 �ṹ��    : SOC_SCI_RXCOUNT_UNION
 �ṹ˵��  : RXCOUNT �Ĵ����ṹ���塣��ַƫ����:0x0068����ֵ:0x0000�����:16
 �Ĵ���˵��: ����FIFO���ݸ����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  rxcount  : 6;  /* bit[0-5] : ���üĴ������ؽ���FIFO�е��ַ�����д�üĴ���������ֵ������ս���FIFO�� */
        unsigned short  reserved : 10; /* bit[6-15]: ������ */
    } reg;
} SOC_SCI_RXCOUNT_UNION;
#endif
#define SOC_SCI_RXCOUNT_rxcount_START   (0)
#define SOC_SCI_RXCOUNT_rxcount_END     (5)


/*****************************************************************************
 �ṹ��    : SOC_SCI_IMSC_UNION
 �ṹ˵��  : IMSC �Ĵ����ṹ���塣��ַƫ����:0x006C����ֵ:0x0000�����:16
 �Ĵ���˵��: �ж����μĴ�����BitֵΪ0��ʾ���Σ�Ϊ1��ʾ�����Ρ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  cardinim   : 1;  /* bit[0] : ���ܿ������ж����Ρ� */
        unsigned short  cardoutim  : 1;  /* bit[1] : ���ܿ��γ��ж����Ρ� */
        unsigned short  cardupim   : 1;  /* bit[2] : ���ܿ������ж����Ρ� */
        unsigned short  carddnim   : 1;  /* bit[3] : ���ܿ��ͷ��ж����Ρ� */
        unsigned short  txerrim    : 1;  /* bit[4] : ���ʹ����ж����Ρ� */
        unsigned short  atrstoutim : 1;  /* bit[5] : ATR�ȴ���ʱ�ж����Ρ� */
        unsigned short  atrdtoutim : 1;  /* bit[6] : ATR���ճ�ʱ�ж����Ρ� */
        unsigned short  blktoutim  : 1;  /* bit[7] : ������ʱ�ж����Ρ� */
        unsigned short  chtoutim   : 1;  /* bit[8] : �ַ������ʱ�ж����Ρ� */
        unsigned short  rtoutim    : 1;  /* bit[9] : ����ʱ�ж����Ρ� */
        unsigned short  rorim      : 1;  /* bit[10]: ���չ����ж����Ρ� */
        unsigned short  clkstpim   : 1;  /* bit[11]: ���ܿ�ʱ��ֹͣ�ж����Ρ� */
        unsigned short  clkactim   : 1;  /* bit[12]: ���ܿ�ʱ�ӻָ��ж����Ρ� */
        unsigned short  rxtideim   : 1;  /* bit[13]: ����FIFO����ж����Ρ� */
        unsigned short  txtideim   : 1;  /* bit[14]: ����FIFO����ж����Ρ� */
        unsigned short  reserved   : 1;  /* bit[15]: ������ */
    } reg;
} SOC_SCI_IMSC_UNION;
#endif
#define SOC_SCI_IMSC_cardinim_START    (0)
#define SOC_SCI_IMSC_cardinim_END      (0)
#define SOC_SCI_IMSC_cardoutim_START   (1)
#define SOC_SCI_IMSC_cardoutim_END     (1)
#define SOC_SCI_IMSC_cardupim_START    (2)
#define SOC_SCI_IMSC_cardupim_END      (2)
#define SOC_SCI_IMSC_carddnim_START    (3)
#define SOC_SCI_IMSC_carddnim_END      (3)
#define SOC_SCI_IMSC_txerrim_START     (4)
#define SOC_SCI_IMSC_txerrim_END       (4)
#define SOC_SCI_IMSC_atrstoutim_START  (5)
#define SOC_SCI_IMSC_atrstoutim_END    (5)
#define SOC_SCI_IMSC_atrdtoutim_START  (6)
#define SOC_SCI_IMSC_atrdtoutim_END    (6)
#define SOC_SCI_IMSC_blktoutim_START   (7)
#define SOC_SCI_IMSC_blktoutim_END     (7)
#define SOC_SCI_IMSC_chtoutim_START    (8)
#define SOC_SCI_IMSC_chtoutim_END      (8)
#define SOC_SCI_IMSC_rtoutim_START     (9)
#define SOC_SCI_IMSC_rtoutim_END       (9)
#define SOC_SCI_IMSC_rorim_START       (10)
#define SOC_SCI_IMSC_rorim_END         (10)
#define SOC_SCI_IMSC_clkstpim_START    (11)
#define SOC_SCI_IMSC_clkstpim_END      (11)
#define SOC_SCI_IMSC_clkactim_START    (12)
#define SOC_SCI_IMSC_clkactim_END      (12)
#define SOC_SCI_IMSC_rxtideim_START    (13)
#define SOC_SCI_IMSC_rxtideim_END      (13)
#define SOC_SCI_IMSC_txtideim_START    (14)
#define SOC_SCI_IMSC_txtideim_END      (14)


/*****************************************************************************
 �ṹ��    : SOC_SCI_RIS_UNION
 �ṹ˵��  : RIS �Ĵ����ṹ���塣��ַƫ����:0x0070����ֵ:0x0000�����:16
 �Ĵ���˵��: ԭʼ�жϼĴ������üĴ��������ж�����֮ǰ��ԭʼ�жϡ�BitֵΪ0��ʾ���жϣ�Ϊ1��ʾ���жϡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  cardinris   : 1;  /* bit[0] : ���ܿ�����ԭʼ�ж�״̬�� */
        unsigned short  cardoutris  : 1;  /* bit[1] : ���ܿ��γ�ԭʼ�ж�״̬�� */
        unsigned short  cardupris   : 1;  /* bit[2] : ���ܿ�����ԭʼ�ж�״̬�� */
        unsigned short  carddnris   : 1;  /* bit[3] : ���ܿ��ͷ�ԭʼ�ж�״̬�� */
        unsigned short  txerrris    : 1;  /* bit[4] : ���ʹ���ԭʼ�ж�״̬���������ַ����ִ����ش������ﵽ��Ԥ��ֵ���Ա���ʱ��1�� */
        unsigned short  atrstoutris : 1;  /* bit[5] : ATR�ȴ���ʱԭʼ�ж�״̬�� */
        unsigned short  atrdtoutris : 1;  /* bit[6] : ATR���ճ�ʱԭʼ�ж�״̬�� */
        unsigned short  blktoutris  : 1;  /* bit[7] : ������ʱԭʼ�ж�״̬�� */
        unsigned short  chtoutris   : 1;  /* bit[8] : �ַ������ʱԭʼ�ж�״̬�� */
        unsigned short  rtoutris    : 1;  /* bit[9] : ����ʱԭʼ�ж�״̬��������FIFO�����ݣ���CPU��Ԥ��ʱ����û��ȡ��ʱ��1�� */
        unsigned short  rorris      : 1;  /* bit[10]: ���չ���ԭʼ�ж�״̬��������FIFO������״̬���ֽ������µ��ַ�ʱ��1�� */
        unsigned short  clkstpris   : 1;  /* bit[11]: ���ܿ�ʱ��ֹͣԭʼ�ж�״̬�� */
        unsigned short  clkactris   : 1;  /* bit[12]: ���ܿ�ʱ�ӻָ�ԭʼ�ж�״̬�� */
        unsigned short  rxtideris   : 1;  /* bit[13]: ����FIFO���ԭʼ�ж�״̬��������FIFO���ַ��ĸ������ڻ������ֵʱ��1�� */
        unsigned short  txtideris   : 1;  /* bit[14]: ����FIFO���ԭʼ�ж�״̬��������FIFO���ַ��ĸ������ڻ������ֵʱ��1�� */
        unsigned short  reserved    : 1;  /* bit[15]: ������ */
    } reg;
} SOC_SCI_RIS_UNION;
#endif
#define SOC_SCI_RIS_cardinris_START    (0)
#define SOC_SCI_RIS_cardinris_END      (0)
#define SOC_SCI_RIS_cardoutris_START   (1)
#define SOC_SCI_RIS_cardoutris_END     (1)
#define SOC_SCI_RIS_cardupris_START    (2)
#define SOC_SCI_RIS_cardupris_END      (2)
#define SOC_SCI_RIS_carddnris_START    (3)
#define SOC_SCI_RIS_carddnris_END      (3)
#define SOC_SCI_RIS_txerrris_START     (4)
#define SOC_SCI_RIS_txerrris_END       (4)
#define SOC_SCI_RIS_atrstoutris_START  (5)
#define SOC_SCI_RIS_atrstoutris_END    (5)
#define SOC_SCI_RIS_atrdtoutris_START  (6)
#define SOC_SCI_RIS_atrdtoutris_END    (6)
#define SOC_SCI_RIS_blktoutris_START   (7)
#define SOC_SCI_RIS_blktoutris_END     (7)
#define SOC_SCI_RIS_chtoutris_START    (8)
#define SOC_SCI_RIS_chtoutris_END      (8)
#define SOC_SCI_RIS_rtoutris_START     (9)
#define SOC_SCI_RIS_rtoutris_END       (9)
#define SOC_SCI_RIS_rorris_START       (10)
#define SOC_SCI_RIS_rorris_END         (10)
#define SOC_SCI_RIS_clkstpris_START    (11)
#define SOC_SCI_RIS_clkstpris_END      (11)
#define SOC_SCI_RIS_clkactris_START    (12)
#define SOC_SCI_RIS_clkactris_END      (12)
#define SOC_SCI_RIS_rxtideris_START    (13)
#define SOC_SCI_RIS_rxtideris_END      (13)
#define SOC_SCI_RIS_txtideris_START    (14)
#define SOC_SCI_RIS_txtideris_END      (14)


/*****************************************************************************
 �ṹ��    : SOC_SCI_MIS_UNION
 �ṹ˵��  : MIS �Ĵ����ṹ���塣��ַƫ����:0x0074����ֵ:0x0000�����:16
 �Ĵ���˵��: ���κ��жϼĴ������üĴ����ǳ�ʼ�жϾ������κ�Ľ����BitֵΪ0��ʾ���жϣ�Ϊ1��ʾ���жϡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  cardinmis   : 1;  /* bit[0] : ���ܿ��������κ��ж�״̬�� */
        unsigned short  cardoutmis  : 1;  /* bit[1] : ���ܿ��γ����κ��ж�״̬�� */
        unsigned short  cardupmis   : 1;  /* bit[2] : ���ܿ��������κ��ж�״̬�� */
        unsigned short  carddnmis   : 1;  /* bit[3] : ���ܿ��ͷ����κ��ж�״̬�� */
        unsigned short  txerrmis    : 1;  /* bit[4] : ���ʹ������κ��ж�״̬�� */
        unsigned short  atrstoutim  : 1;  /* bit[5] : ATR�ȴ���ʱ���κ��ж�״̬�� */
        unsigned short  atrdtoutmis : 1;  /* bit[6] : ATR���ճ�ʱ���κ��ж�״̬�� */
        unsigned short  blktoutmis  : 1;  /* bit[7] : ������ʱ���κ��ж�״̬�� */
        unsigned short  chtoutmis   : 1;  /* bit[8] : �ַ������ʱ���κ��ж�״̬�� */
        unsigned short  rtoutmis    : 1;  /* bit[9] : ����ʱ���κ��ж�״̬�� */
        unsigned short  rormis      : 1;  /* bit[10]: ���չ������κ��ж�״̬�� */
        unsigned short  clkstpmis   : 1;  /* bit[11]: ���ܿ�ʱ��ֹͣ���κ��ж�״̬�� */
        unsigned short  clkactmis   : 1;  /* bit[12]: ���ܿ�ʱ�ӻָ����κ��ж�״̬�� */
        unsigned short  rxtidemis   : 1;  /* bit[13]: ����FIFO������κ��ж�״̬�� */
        unsigned short  txtidemis   : 1;  /* bit[14]: ����FIFO������κ��ж�״̬�� */
        unsigned short  reserved    : 1;  /* bit[15]: ������ */
    } reg;
} SOC_SCI_MIS_UNION;
#endif
#define SOC_SCI_MIS_cardinmis_START    (0)
#define SOC_SCI_MIS_cardinmis_END      (0)
#define SOC_SCI_MIS_cardoutmis_START   (1)
#define SOC_SCI_MIS_cardoutmis_END     (1)
#define SOC_SCI_MIS_cardupmis_START    (2)
#define SOC_SCI_MIS_cardupmis_END      (2)
#define SOC_SCI_MIS_carddnmis_START    (3)
#define SOC_SCI_MIS_carddnmis_END      (3)
#define SOC_SCI_MIS_txerrmis_START     (4)
#define SOC_SCI_MIS_txerrmis_END       (4)
#define SOC_SCI_MIS_atrstoutim_START   (5)
#define SOC_SCI_MIS_atrstoutim_END     (5)
#define SOC_SCI_MIS_atrdtoutmis_START  (6)
#define SOC_SCI_MIS_atrdtoutmis_END    (6)
#define SOC_SCI_MIS_blktoutmis_START   (7)
#define SOC_SCI_MIS_blktoutmis_END     (7)
#define SOC_SCI_MIS_chtoutmis_START    (8)
#define SOC_SCI_MIS_chtoutmis_END      (8)
#define SOC_SCI_MIS_rtoutmis_START     (9)
#define SOC_SCI_MIS_rtoutmis_END       (9)
#define SOC_SCI_MIS_rormis_START       (10)
#define SOC_SCI_MIS_rormis_END         (10)
#define SOC_SCI_MIS_clkstpmis_START    (11)
#define SOC_SCI_MIS_clkstpmis_END      (11)
#define SOC_SCI_MIS_clkactmis_START    (12)
#define SOC_SCI_MIS_clkactmis_END      (12)
#define SOC_SCI_MIS_rxtidemis_START    (13)
#define SOC_SCI_MIS_rxtidemis_END      (13)
#define SOC_SCI_MIS_txtidemis_START    (14)
#define SOC_SCI_MIS_txtidemis_END      (14)


/*****************************************************************************
 �ṹ��    : SOC_SCI_ICR_UNION
 �ṹ˵��  : ICR �Ĵ����ṹ���塣��ַƫ����:0x0078����ֵ:0x0000�����:16
 �Ĵ���˵��: �ж�����Ĵ�����BitֵΪ0��ʾ������жϣ�Ϊ1��ʾ����жϡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  cardinic   : 1;  /* bit[0]    : ���ܿ������ж������ */
        unsigned short  cardoutic  : 1;  /* bit[1]    : ���ܿ��γ��ж������ */
        unsigned short  cardupic   : 1;  /* bit[2]    : ���ܿ������ж������ */
        unsigned short  carddnic   : 1;  /* bit[3]    : ���ܿ��ͷ��ж������ */
        unsigned short  txerric    : 1;  /* bit[4]    : ���ʹ����ж������ */
        unsigned short  atrstoutic : 1;  /* bit[5]    : ATR�ȴ���ʱ�ж������ */
        unsigned short  atrdtoutic : 1;  /* bit[6]    : ATR���ճ�ʱ�ж������ */
        unsigned short  blktoutic  : 1;  /* bit[7]    : ������ʱ�ж������ */
        unsigned short  chtoutic   : 1;  /* bit[8]    : �ַ������ʱ�ж������ */
        unsigned short  rtoutic    : 1;  /* bit[9]    : ����ʱ�ж������ */
        unsigned short  roric      : 1;  /* bit[10]   : ���չ����ж������ */
        unsigned short  clkstpic   : 1;  /* bit[11]   : ���ܿ�ʱ��ֹͣ�ж������ */
        unsigned short  clkactic   : 1;  /* bit[12]   : ���ܿ�ʱ�ӻָ��ж������ */
        unsigned short  reserved   : 3;  /* bit[13-15]: ������ */
    } reg;
} SOC_SCI_ICR_UNION;
#endif
#define SOC_SCI_ICR_cardinic_START    (0)
#define SOC_SCI_ICR_cardinic_END      (0)
#define SOC_SCI_ICR_cardoutic_START   (1)
#define SOC_SCI_ICR_cardoutic_END     (1)
#define SOC_SCI_ICR_cardupic_START    (2)
#define SOC_SCI_ICR_cardupic_END      (2)
#define SOC_SCI_ICR_carddnic_START    (3)
#define SOC_SCI_ICR_carddnic_END      (3)
#define SOC_SCI_ICR_txerric_START     (4)
#define SOC_SCI_ICR_txerric_END       (4)
#define SOC_SCI_ICR_atrstoutic_START  (5)
#define SOC_SCI_ICR_atrstoutic_END    (5)
#define SOC_SCI_ICR_atrdtoutic_START  (6)
#define SOC_SCI_ICR_atrdtoutic_END    (6)
#define SOC_SCI_ICR_blktoutic_START   (7)
#define SOC_SCI_ICR_blktoutic_END     (7)
#define SOC_SCI_ICR_chtoutic_START    (8)
#define SOC_SCI_ICR_chtoutic_END      (8)
#define SOC_SCI_ICR_rtoutic_START     (9)
#define SOC_SCI_ICR_rtoutic_END       (9)
#define SOC_SCI_ICR_roric_START       (10)
#define SOC_SCI_ICR_roric_END         (10)
#define SOC_SCI_ICR_clkstpic_START    (11)
#define SOC_SCI_ICR_clkstpic_END      (11)
#define SOC_SCI_ICR_clkactic_START    (12)
#define SOC_SCI_ICR_clkactic_END      (12)


/*****************************************************************************
 �ṹ��    : SOC_SCI_SYNCACT_UNION
 �ṹ˵��  : SYNCACT �Ĵ����ṹ���塣��ַƫ����:0x007C����ֵ:0x0000�����:16
 �Ĵ���˵��: ͬ��ģʽ����Ĵ������üĴ�������ͬ��ģʽ������ʹ�ܡ�ʱ��ʹ�ܡ���λ�͵�Դ���Ƶȣ����ṩ״̬�Ĵ�������Ӧ��״̬λ�ڼ���ͷš��ȸ�λ�������Զ����¡�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  power         : 1;  /* bit[0]    : ���ƿ���Դ��VCC��ʹ�ܡ�
                                                           0��ʹ�ܣ�
                                                           1����ֹ�� */
        unsigned short  creset        : 1;  /* bit[1]    : ����λ�źſ���ʹ�ܡ�
                                                           0��ʹ�ܣ�
                                                           1����ֹ�� */
        unsigned short  clken         : 1;  /* bit[2]    : SCIʱ�����ʹ�ܡ�
                                                           0����ֹ��
                                                           1��ʹ�ܡ� */
        unsigned short  dataen        : 1;  /* bit[3]    : SCI�������ʹ�ܡ�
                                                           0����ֹ��
                                                           1��ʹ�ܡ� */
        unsigned short  reserved_0    : 1;  /* bit[4]    : ������ */
        unsigned short  nsciclkouten  : 1;  /* bit[5]    : ����buffer����̬����ʹ�ܡ�
                                                           0��ʹ�ܣ�
                                                           1����ֹ�� */
        unsigned short  nsciclken     : 1;  /* bit[6]    : ʱ�ӵ��ⲿoffchip buffer����̬����ʹ�ܡ�
                                                           0��ʹ�ܣ�
                                                           1����ֹ�� */
        unsigned short  sciclkout     : 1;  /* bit[7]    : SCIʱ�����ʹ�ܡ�
                                                           0��ʹ�ܣ�
                                                           1����ֹ�� */
        unsigned short  nscidataouten : 1;  /* bit[8]    : ����buffer����̬����ʹ�ܡ�
                                                           0��ʹ�ܣ�
                                                           1����ֹ�� */
        unsigned short  nscidataen    : 1;  /* bit[9]    : ���ݵ��ⲿoffchip buffer����̬����ʹ�ܡ�
                                                           0��ʹ�ܣ�
                                                           1����ֹ�� */
        unsigned short  cardpresent   : 1;  /* bit[10]   : ���ܿ�����״̬λ��
                                                           0�������ܿ���
                                                           1�������ܿ��� */
        unsigned short  reserved_1    : 5;  /* bit[11-15]: ������ */
    } reg;
} SOC_SCI_SYNCACT_UNION;
#endif
#define SOC_SCI_SYNCACT_power_START          (0)
#define SOC_SCI_SYNCACT_power_END            (0)
#define SOC_SCI_SYNCACT_creset_START         (1)
#define SOC_SCI_SYNCACT_creset_END           (1)
#define SOC_SCI_SYNCACT_clken_START          (2)
#define SOC_SCI_SYNCACT_clken_END            (2)
#define SOC_SCI_SYNCACT_dataen_START         (3)
#define SOC_SCI_SYNCACT_dataen_END           (3)
#define SOC_SCI_SYNCACT_nsciclkouten_START   (5)
#define SOC_SCI_SYNCACT_nsciclkouten_END     (5)
#define SOC_SCI_SYNCACT_nsciclken_START      (6)
#define SOC_SCI_SYNCACT_nsciclken_END        (6)
#define SOC_SCI_SYNCACT_sciclkout_START      (7)
#define SOC_SCI_SYNCACT_sciclkout_END        (7)
#define SOC_SCI_SYNCACT_nscidataouten_START  (8)
#define SOC_SCI_SYNCACT_nscidataouten_END    (8)
#define SOC_SCI_SYNCACT_nscidataen_START     (9)
#define SOC_SCI_SYNCACT_nscidataen_END       (9)
#define SOC_SCI_SYNCACT_cardpresent_START    (10)
#define SOC_SCI_SYNCACT_cardpresent_END      (10)


/*****************************************************************************
 �ṹ��    : SOC_SCI_SYNCTX_UNION
 �ṹ˵��  : SYNCTX �Ĵ����ṹ���塣��ַƫ����:0x0080����ֵ:0x0000�����:16
 �Ĵ���˵��: ͬ��ģʽ����ʱ�Ӻ��������Ĵ������üĴ������ڿ���ͬ��ģʽ�·���ʱ�Ӻ����ݡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  wdata    : 1;  /* bit[0]   : ͬ��ģʽ��SCI����ʹ�ܡ�
                                                     0��ʹ�ܣ�
                                                     1����ֹ�� */
        unsigned short  wclk     : 1;  /* bit[1]   : ͬ��ģʽ��SCIʱ��ʹ�ܡ�
                                                     0��ʹ�ܣ�
                                                     1����ֹ�� */
        unsigned short  wdataen  : 1;  /* bit[2]   : ͬ��ģʽ�£���λΪSCI�������ʹ�ܡ�
                                                     0����ֹ��
                                                     1��ʹ�ܡ� */
        unsigned short  wclken   : 1;  /* bit[3]   : ͬ��ģʽ�£���λΪʱ�ӵ��ⲿoff chip buffer����̬ʹ�ܿ��ơ�
                                                     0��ʹ�ܣ�
                                                     1����ֹ�� */
        unsigned short  wrst     : 1;  /* bit[4]   : ͬ��ģʽ�£���λΪ����λ�ź�ʹ�ܡ�
                                                     0����ֹ��
                                                     1��ʹ�ܡ� */
        unsigned short  reserved_0: 1;  /* bit[5]   : ������ */
        unsigned short  reserved_1: 10; /* bit[6-15]: ������ */
    } reg;
} SOC_SCI_SYNCTX_UNION;
#endif
#define SOC_SCI_SYNCTX_wdata_START     (0)
#define SOC_SCI_SYNCTX_wdata_END       (0)
#define SOC_SCI_SYNCTX_wclk_START      (1)
#define SOC_SCI_SYNCTX_wclk_END        (1)
#define SOC_SCI_SYNCTX_wdataen_START   (2)
#define SOC_SCI_SYNCTX_wdataen_END     (2)
#define SOC_SCI_SYNCTX_wclken_START    (3)
#define SOC_SCI_SYNCTX_wclken_END      (3)
#define SOC_SCI_SYNCTX_wrst_START      (4)
#define SOC_SCI_SYNCTX_wrst_END        (4)


/*****************************************************************************
 �ṹ��    : SOC_SCI_SYNCRX_UNION
 �ṹ˵��  : SYNCRX �Ĵ����ṹ���塣��ַƫ����:0x0084����ֵ:0x0000�����:16
 �Ĵ���˵��: ͬ��ģʽ����ʱ�Ӻ��������Ĵ������üĴ������ڿ���ͬ��ģʽ�½���ʱ�Ӻ����ݡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  rdata    : 1;  /* bit[0]   : ����ԭʼֵ�� */
        unsigned short  rclk     : 1;  /* bit[1]   : ʱ��ԭʼֵ�� */
        unsigned short  reserved : 14; /* bit[2-15]: ������ */
    } reg;
} SOC_SCI_SYNCRX_UNION;
#endif
#define SOC_SCI_SYNCRX_rdata_START     (0)
#define SOC_SCI_SYNCRX_rdata_END       (0)
#define SOC_SCI_SYNCRX_rclk_START      (1)
#define SOC_SCI_SYNCRX_rclk_END        (1)






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

#endif /* end of soc_sci_interface.h */
