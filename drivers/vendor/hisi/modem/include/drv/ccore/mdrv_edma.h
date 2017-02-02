#ifndef __MDRV_CCORE_EDMA_H__
#define __MDRV_CCORE_EDMA_H__
#ifdef __cplusplus
extern "C"
{
#endif



#define BALONG_DMA_INT_DONE           1          /*DMA��������ж�*/
#define BALONG_DMA_INT_LLT_DONE       2          /*��ʽDMA�ڵ㴫������ж�*/
#define BALONG_DMA_INT_CONFIG_ERR     4          /*DMA���ô����µ��ж�*/
#define BALONG_DMA_INT_TRANSFER_ERR   8          /*DMA��������µ��ж�*/
#define BALONG_DMA_INT_READ_ERR       16         /*DMA����������µ��ж�*/

/* EDMAC���䷽����*/
#define BALONG_DMA_P2M      1
#define BALONG_DMA_M2P      2
#define BALONG_DMA_M2M      3

/* ͨ��״̬ */

#define   EDMA_CHN_FREE          1   /* ͨ������ */
#define   EDMA_CHN_BUSY          0   /* ͨ��æ */


/* EDMA����λ��Դ��Ŀ�ĵ�ַԼ��Ϊһ�µ�ֵ */
#define   EDMA_TRANS_WIDTH_8       0x0   /* 8bitλ��*/
#define   EDMA_TRANS_WIDTH_16      0x1   /* 16bitλ��*/
#define   EDMA_TRANS_WIDTH_32      0x2   /* 32bitλ��*/
#define   EDMA_TRANS_WIDTH_64      0x3   /* 64bitλ��*/

/*  EDMA burst length, ȡֵ��Χ0~15����ʾ��burst����Ϊ1~16*/
#define   EDMA_BUR_LEN_1    0x0    /* burst���ȣ���һ�δ���ĸ���Ϊ1��*/
#define   EDMA_BUR_LEN_2    0x1    /* burst���ȣ���һ�δ���ĸ���Ϊ2��*/
#define   EDMA_BUR_LEN_3    0x2   /* burst���ȣ���һ�δ���ĸ���Ϊ3��*/
#define   EDMA_BUR_LEN_4    0x3   /* burst���ȣ���һ�δ���ĸ���Ϊ4��*/
#define   EDMA_BUR_LEN_5    0x4   /* burst���ȣ���һ�δ���ĸ���Ϊ5��*/
#define   EDMA_BUR_LEN_6    0x5   /* burst���ȣ���һ�δ���ĸ���Ϊ6��*/
#define   EDMA_BUR_LEN_7    0x6   /* burst���ȣ���һ�δ���ĸ���Ϊ7��*/
#define   EDMA_BUR_LEN_8    0x7   /* burst���ȣ���һ�δ���ĸ���Ϊ8��*/
#define   EDMA_BUR_LEN_9    0x8   /* burst���ȣ���һ�δ���ĸ���Ϊ9��*/
#define   EDMA_BUR_LEN_10   0x9   /* burst���ȣ���һ�δ���ĸ���Ϊ10��*/
#define   EDMA_BUR_LEN_11   0xa   /* burst���ȣ���һ�δ���ĸ���Ϊ11��*/
#define   EDMA_BUR_LEN_12   0xb   /* burst���ȣ���һ�δ���ĸ���Ϊ12��*/
#define   EDMA_BUR_LEN_13   0xc   /* burst���ȣ���һ�δ���ĸ���Ϊ13��*/
#define   EDMA_BUR_LEN_14   0xd   /* burst���ȣ���һ�δ���ĸ���Ϊ14��*/
#define   EDMA_BUR_LEN_15   0xe   /* burst���ȣ���һ�δ���ĸ���Ϊ15��*/
#define   EDMA_BUR_LEN_16   0xf   /* burst���ȣ���һ�δ���ĸ���Ϊ16��*/


/* EDMA ��Ӧ�ľ���λ����EDMA  �Ĵ������ú�
       EDMAC_BASIC_CONFIG��BALONG_DMA_SET_LLI��BALONG_DMA_SET_CONFIG ʹ��*/
/*config------Bit 31*/
#define EDMAC_TRANSFER_CONFIG_SOUR_INC      (0X80000000)
/*Bit 30*/
#define EDMAC_TRANSFER_CONFIG_DEST_INC      (0X40000000)
#define EDMAC_TRANSFER_CONFIG_BOTH_INC      (0XC0000000)

/*Bit 27-24*/
#define EDMAC_TRANSFER_CONFIG_SOUR_BURST_LENGTH_MASK     (0xF000000)
#define EDMAC_TRANSFER_CONFIG_SOUR_BURST_LENGTH( _len )  ((unsigned int)((_len)<<24))
/*Bit 23-20*/
#define EDMAC_TRANSFER_CONFIG_DEST_BURST_LENGTH_MASK     (0xF00000)
#define EDMAC_TRANSFER_CONFIG_DEST_BURST_LENGTH( _len )  ((unsigned int)((_len)<<20))

/*Bit18-16*/
#define EDMAC_TRANSFER_CONFIG_SOUR_WIDTH_MASK     (0x70000)
#define EDMAC_TRANSFER_CONFIG_SOUR_WIDTH( _len )  ((unsigned int)((_len)<<16))
/*Bit14-12*/
#define EDMAC_TRANSFER_CONFIG_DEST_WIDTH_MASK     (0x7000)
#define EDMAC_TRANSFER_CONFIG_DEST_WIDTH( _len )  ((unsigned int)((_len)<<12))

/*Bit9-4*/
#define EDMAC_TRANSFER_CONFIG_REQUEST( _ulReg )    ( (_ulReg ) << 4)
/*Bit3-2*/
#define EDMAC_TRANSFER_CONFIG_FLOW_DMAC( _len )    ((unsigned int)((_len)<<2))

#define EDMAC_TRANSFER_CONFIG_INT_TC_ENABLE            ( 0x2 )
#define EDMAC_TRANSFER_CONFIG_INT_TC_DISABLE           ( 0x0 )

#define EDMAC_TRANSFER_CONFIG_CHANNEL_ENABLE           ( 0x1 )
#define EDMAC_TRANSFER_CONFIG_CHANNEL_DISABLE          ( 0x0 )
#define EDMAC_NEXT_LLI_ENABLE       0x2           /* Bit 1 */
/*Bit 15*/
#define EDMAC_TRANSFER_CONFIG_EXIT_ADD_MODE_A_SYNC     ( 0UL )
#define EDMAC_TRANSFER_CONFIG_EXIT_ADD_MODE_AB_SYNC    ( 0x00008000 )

#define P2M_CONFIG   (EDMAC_TRANSFER_CONFIG_FLOW_DMAC(MEM_PRF_DMA) | EDMAC_TRANSFER_CONFIG_DEST_INC)
#define M2P_CONFIG   (EDMAC_TRANSFER_CONFIG_FLOW_DMAC(MEM_PRF_DMA) | EDMAC_TRANSFER_CONFIG_SOUR_INC)
#define M2M_CONFIG   (EDMAC_TRANSFER_CONFIG_FLOW_DMAC(MEM_MEM_DMA) | EDMAC_TRANSFER_CONFIG_SOUR_INC | EDMAC_TRANSFER_CONFIG_DEST_INC)

#define EDMAC_MAKE_LLI_ADDR( _p )   (unsigned int)( (unsigned int)(_p) & 0xFFFFFFE0 )

/*edma �������͡�*/
typedef enum _BALONG_DMA_REQ
{

    EDMA_SPI0_RX = 0,
    EDMA_SPI0_TX,
    EDMA_SPI1_RX,
    EDMA_SPI1_TX,       /* Acore drv lcd ˢ��   ʵ�ʷ���ͨ�� edma ch16 - 14 */
    EDMA_LTESIO_RX,     /* HIFI                  ʵ�ʷ���ͨ�� edma ch16 - 8  */
    EDMA_LTESIO_TX,     /* HIFI                  ʵ�ʷ���ͨ�� edma ch16 - 9  */
    RESERVE_0,
    RESERVE_1,
    EDMA_HSUART_RX = 8, /* Acore drv ������������ ʵ�ʷ���ͨ�� edma ch16-12 */
    EDMA_HSUART_TX,      /* Acore drv ������������ ʵ�ʷ���ͨ�� edma ch16-13 */
    EDMA_UART0_RX,
    EDMA_UART0_TX,
    EDMA_UART1_RX,
    EDMA_UART1_TX,
    EDMA_UART2_RX,
    EDMA_UART2_TX,
    EDMA_SCI0_RX = 0x10, /* Acore drv SIM��1��  ʵ�ʷ���ͨ�� edma ch16-10 */
    EDMA_SCI_RX  = 0x10,
    EDMA_SCI0_TX,          /* Acore drv SIM��1��  ʵ�ʷ���ͨ�� edma ch16-10 */
    EDMA_SCI1_RX,          /* Acore drv SIM��2��  ʵ�ʷ���ͨ�� edma ch16-11 */
    EDMA_SCI1_TX,          /* Acore drv SIM��2��  ʵ�ʷ���ͨ�� edma ch16-11 */
    EDMA_GBBP0_DBG = 0x14,
    EDMA_BBP_DBG   = 0x14, /* gudsp ������ bbp���� ʵ�ʷ���ͨ�� edma ch16-6 */
    EDMA_GBBP1_GRIF = 0x15,
    EDMA_BBP_GRIF   = 0x15,/* gudsp ������ bbp���� ʵ�ʷ���ͨ�� edma ch16-6  */
    EDMA_AMON_SOC = 0x16,     /* Acore AXIMON ʵ�ʷ���ͨ�� edma ch16-15 */
    EDMA_AMON_CPUFAST = 0x17,/* Acore AXIMON ʵ�ʷ���ͨ�� edma ch16-15 */
    /* gudsp ������ M2M */
    /* EDMA_GBBP0_DBG Ϊgudspʹ�� EDMA_BBP_DBG  ʵ�ʷ���ͨ�� edma ch16 - 6  */
    EDMA_MEMORY_DSP_1,  /* ����turbo����  ʵ�ʷ���ͨ�� edma ch4  - 0  */
    EDMA_MEMORY_DSP_2,          /* ����viterb���� ʵ�ʷ���ͨ�� edma ch4  - 1  */
    /*TL��GU���� ch16 - 2��Ϊ����ÿ������ǰ��鵱ǰͨ���Ƿ����***/
    EDMA_MEMORY_DSP_3,          /* ����CQI�����   ʵ�ʷ���ͨ�� edma ch16 - 2 */
    EDMA_MEMORY_DSP_4,          /* �������б���     ʵ�ʷ���ͨ�� edma ch4  - 2 */
    EDMA_MEMORY_DSP_5,          /* ����APT�����   ʵ�ʷ���ͨ�� edma ch4  - 3 */
    EDMA_MEMORY_DSP_6 ,  /* GUDSP/AHB���� ʵ�ʷ���ͨ�� edma ch16 - 7 */

    EDMA_PWC_LDSP_TCM,        /* Mcore  drv   ʵ�ʷ���ͨ�� edma ch16 - 0  */
    EDMA_PWC_TDSP_TCM,         /* Mcore  drv   ʵ�ʷ���ͨ�� edma ch16 - 1  */
    EDMA_MEMORY_1 = 0x20,
    EDMA_MEMORY_2,
    EDMA_MEMORY_3,
    EDMA_MEMORY_4,
    EDMA_DSP_GRIF = 0x24,
    EDMA_PWC_CDSP_TCM = 0x25,         /* Mcore  drv   ʵ�ʷ���ͨ��   */
    EDMA_CPS_L2_UP,
    EDMA_CPS_L2_DOWN,
    EDMA_G1_GTC,
    EDMA_G2_GTC,
    EDMA_REQ_MAX,               /*����豸����С�ڴ�ֵ����Ϊ�Ƿ�����*/

    EDMA_BUTT
} BALONG_DMA_REQ_E;

/**** V8 �ṩ��LPHY�� edmaͨ����    ---- start**/
/* V7 �ṩ��LPHY�� edmaͨ���� ��platform��drv_edma_enum.h��*/
#define     EDMA_LDSP_NV_LOADING         (2)           /* edma chanl 2 , for LDSP*/
#define     EDMA_LDSP_API_USED_0         (3)           /* edma chanl 3 , for LDSP*/
#define     EDMA_LDSP_API_USED_1         (4)           /* edma chanl 4 , for LDSP*/
#define     EDMA_LDSP_CSU_SDR            (5)           /* edma chanl 5 , for LDSP*/
#define     EDMA_LDSP_EMU_SDR            (6)           /* edma chanl 6, for LDSP*/
#define     EDMA_LDSP_LCS_SDR            (0xffff)      /* û��ʵ����; , stub for LDSP*/

/*EDMAC�������봫������*/
typedef enum tagEDMA_TRANS_TYPE
{
    MEM_MEM_DMA = 0x00,    /* �ڴ浽�ڴ棬DMA����*/
    MEM_PRF_DMA = 0x01,    /* �ڴ������裬DMA����*/
    MEM_PRF_PRF = 0x10     /* �ڴ������裬��������*/
} EDMA_TRANS_TYPE_E;

/*��ʽ����ʱ�Ľڵ���Ϣ��*/
typedef struct _BALONG_DMA_CB
{
    volatile unsigned int lli;     /*ָ���¸�LLI*/
    volatile unsigned int bindx;
    volatile unsigned int cindx;
    volatile unsigned int cnt1;
    volatile unsigned int cnt0;  /*�鴫�����LLI�����ÿ���ڵ����ݳ��� <= 65535�ֽ�*/
    volatile unsigned int src_addr; /*�����ַ*/
    volatile unsigned int des_addr; /*�����ַ*/
    volatile unsigned int config;
} BALONG_DMA_CB_S __attribute__ ((aligned (32)));

typedef void (*channel_isr)(unsigned int channel_arg,unsigned int int_status);
/*****************************************************************************
	 *  �� �� ��  : mdrv_edma_basic_config
	 *  ��������  :  ��������edmaͨ����Դ��Ŀ�ĵ�burst width��len��
	                                ʵ��Ϊ�꣬�õ�һ��u32��ֵ��
	 *  �������  :
	 *
	 *  �������  : ��
	 *  �� �� ֵ  :
     	 *
	 ******************************************************************************/
    /*unsigned int mdrv_edma_basic_config (unsigned int burst_width, unsigned int burst_len);*/
	#define mdrv_edma_basic_config(burst_width,burst_len) \
		( EDMAC_TRANSFER_CONFIG_SOUR_BURST_LENGTH(burst_len) | EDMAC_TRANSFER_CONFIG_DEST_BURST_LENGTH(burst_len) \
		| EDMAC_TRANSFER_CONFIG_SOUR_WIDTH(burst_width) | EDMAC_TRANSFER_CONFIG_DEST_WIDTH(burst_width) )

/*****************************************************************************
	 *  �� �� ��  : mdrv_edma_set_lli
	 *  ��������  :  ����������ʱ�����ýڵ���ϢBALONG_DMA_CB��lli�
	 *                             ����lli�Ĵ�������һ������ڵ��ַ��ʹ�ܡ�
	 *                             �ú�ʵ�֣��õ�����ֵ
	 *  �������  :addr Ϊ�����ַ
	 *
	 *  �������  : ��
	 *  �� �� ֵ  : 0	���һ���ڵ�����á�
        *                        32λ��ֵ	"�ڵ��ַ"��"ʹ��"��Ӧ����λ������"
     	 *
	 ******************************************************************************/
/*unsigned int mdrv_edma_set_lli (unsigned int addr, unsigned int last);*/
 /*��ȷ���Ƿ��ú�ʵ��*/
#define mdrv_edma_set_lli(addr,last)  ((last)?0:(EDMAC_MAKE_LLI_ADDR(addr) | EDMAC_NEXT_LLI_ENABLE))



/*****************************************************************************
 �� �� ��  : mdrv_edma_set_config
 ��������  : ���ڸ����û��·�EDMA������Ϣ����config�Ĵ�����Ϣ�����ظ��û�
 �������  : req         �߼������
             direction   ���䷽��
             burst_width burst����λ��
             burst_len   burst���䳤��
 �������  : ��
 �� �� ֵ  : 0-ʧ�ܣ�����-���ɵļĴ�����Ϣ
 ���ú���  : NA
 ��������  : NA
*
******************************************************************************/
unsigned int mdrv_edma_set_config(BALONG_DMA_REQ_E req, unsigned int direction, unsigned int burst_width, unsigned int burst_len);

/*****************************************************************************
	 *  �� �� ��  : mdrv_edma_get_curr_trans_addr
	 *  ��������  :  ���ĳͨ����ǰ�Ĵ����ַ��
	 *  �������  :  channel_id : ͨ��ID������ xx_channel_init�����ķ���ֵ
	 *
	 *  �������  : ��
	 *  �� �� ֵ  : 	����ֵ:	��ȡ��õĵ�ǰͨ�������ַ�Ĵ�����ֵ
        *                         -1	          :    ʧ�ܣ���������
     	 *
	 ******************************************************************************/
int mdrv_edma_get_curr_trans_addr (unsigned int channel_id);

/*****************************************************************************
	 *  �� �� ��  : mdrv_edma_chan_stop
	 *  ��������  :  ֹͣĳͨ���Ĵ��䡣
	 *  �������  : channel_id 
	 *
	 *  �������  : ��
	 *  �� �� ֵ  :����	�ɹ������ص�ǰ�����ַ
        *                        -1	   ʧ��
     	 *
	 ******************************************************************************/
int mdrv_edma_chan_stop (unsigned int channel_id);

/*****************************************************************************
	 *  �� �� ��  : mdrv_edma_chan_get_lli_addr
	 *  ��������  :  ���ָ��DMAͨ����lli���ƿ��׵�ַ��
	 *  �������  :
	 *
	 *  �������  : ��
	 *  �� �� ֵ  : 0	      ʧ�ܣ����ؿ�ָ��
        *                        ����   �ɹ������ؼĴ���lli���ƿ�ĵ�ַ
     	 *
	 ******************************************************************************/
BALONG_DMA_CB_S * mdrv_edma_chan_get_lli_addr (unsigned int channel_id);

/*****************************************************************************
	 *  �� �� ��  : mdrv_edma_chan_init
	 *  ��������  :  ��������ŷ���ͨ����ע��ͨ���жϻص���������ʼ����������ź������������д��config�Ĵ�����
	 *  �������  : req		     ���������
        *                            pFunc		     �ϲ�ע���DMA�жϴ�������ΪNULLʱ��ʾ����Ҫע�ᡣ
        *                            channel_arg	     pFunc�Ĳ���1
        *                            int_flag	            pFunc�Ĳ���2����ʾ����������ж�����
	 *
	 *  �������  : ��
	 *  �� �� ֵ  :  0	       �����ɹ���
        *                           ����	����ʧ�ܡ�
     	 *
	 ******************************************************************************/
int mdrv_edma_chan_init (BALONG_DMA_REQ_E req, channel_isr pFunc, unsigned int channel_arg, unsigned int int_flag);

/*****************************************************************************
	 *  �� �� ��  : mdrv_edma_chan_config
	 *  ��������  :  ����ʽEDMA����ʱ�����ñ���������ͨ����������ʽEDMA����ʱ������Ҫʹ�ñ�������
	 *  �������  :  channel_id : ͨ��ID������balong_dma_channel_init�����ķ���ֵ
               direction : DMA���䷽��, ȡֵΪBALONG_DMA_P2M��BALONG_DMA_M2P��
                           BALONG_DMA_M2M֮һ
               burst_width��ȡֵΪ0��1��2��3����ʾ��burstλ��Ϊ8��16��32��64bit
               burst_len��ȡֵ��Χ0~15����ʾ��burst����Ϊ1~16
	 *
	 *  �������  : ��
	 *  �� �� ֵ  :  0	       �����ɹ���
        *                           ����	����ʧ�ܡ�
     	 *
	 ******************************************************************************/
int mdrv_edma_chan_config (unsigned int channel_id, unsigned int direction,unsigned int burst_width, unsigned int burst_len);

/*****************************************************************************
	 *  �� �� ��  : mdrv_edma_chan_dest_config
	 *  ��������  :  BBP GRIF��������Ŀ������λ��ͳ���ʱ���á��������β�ʹ�á�
                       ʹ��ʱ���ýӿ���balong_dma_channel_set_config֮����á�
	 *  �������  :  channel_id��ͨ��ID������balong_dma_channel_init�����ķ���ֵ
               burst_width��ȡֵΪ0��1��2��3����ʾ��burstλ��Ϊ8��16��32��64bit
               burst_len��ȡֵ��Χ0~15����ʾ��burst����Ϊ1~16
	 *
	 *  �������  : ��
	 *  �� �� ֵ  :  0	       �����ɹ���
        *                           ����	����ʧ�ܡ�
     	 *
	 ******************************************************************************/
int mdrv_edma_chan_dest_config(unsigned int channel_id, unsigned int dest_width, unsigned int dest_len);

/*****************************************************************************
	 *  �� �� ��  : mdrv_edma_chan_start
	 *  ��������  :  ����һ��ͬ��DMA���䣬DMA������ɺ�ŷ��أ�����Ҫע���ж�
	 *  �������  : channel_id��ͨ��ID,����balong_dma_channel_init�����ķ���ֵ
               src_addr�����ݴ���Դ��ַ�������������ַ
               des_addr�����ݴ���Ŀ�ĵ�ַ�������������ַ
               len�����ݴ��䳤�ȣ���λ���ֽڣ�һ�δ������ݵ���󳤶���65535�ֽ�
	 *
	 *  �������  : ��
	 *  �� �� ֵ  :  0	       �����ɹ���
        *                           ����	����ʧ�ܡ�
     	 *
	 ******************************************************************************/
int mdrv_edma_chan_start(unsigned int channel_id, unsigned int src_addr, unsigned int des_addr, unsigned int len);

/*****************************************************************************
	 *  �� �� ��  : mdrv_edma_chan_async_start
	 *  ��������  :  ����һ���첽DMA���䣬����DMA��ͷ��أ����ȴ���
	                   ��Ҫע���жϴ�����������DMA��������жϡ�
					   ���ߣ���ע���жϴ�������ʹ��balong_dma_channel_is_idle������ѯ
               DMA�����Ƿ����
	 *  �������  :   channel_id��ͨ��ID,����balong_dma_channel_init�����ķ���ֵ
               src_addr�����ݴ���Դ��ַ�������������ַ
               des_addr�����ݴ���Ŀ�ĵ�ַ�������������ַ
               len�����ݴ��䳤�ȣ���λ���ֽڣ�һ�δ������ݵ���󳤶���65535�ֽ�
	 *
	 *  �������  : ��
	 *  �� �� ֵ  :  0	       �����ɹ���
        *                           ����	����ʧ�ܡ�
     	 *
	 ******************************************************************************/
int mdrv_edma_chan_async_start(unsigned int channel_id, unsigned int src_addr, unsigned int des_addr, unsigned int len);

/*****************************************************************************
	 *  �� �� ��  : mdrv_edma_chan_lli_start
	 *  ��������  :  ������ʽ���䣬���нڵ㴫����ɺ󷵻ء�
	 			��ʽDMA��ÿ���ڵ����������䳤��Ϊ65535�ֽڡ�
               ע�⣺���ô˺���ǰ���������ú�������ƿ顣
	 *  �������  :
	 *
	 *  �������  : ��
	 *  �� �� ֵ  :  0	       �����ɹ���
        *                           ����	����ʧ�ܡ�
     	 *
	 ******************************************************************************/
int mdrv_edma_chan_lli_start(unsigned int channel_id);

/*****************************************************************************
	 *  �� �� ��  : mdrv_edma_chan_lli_async_start
	 *  ��������  :  ������ʽ���䣬�����󲻵ȴ�������ɣ�ֱ�ӷ���
               ��ʽDMA��ÿ���ڵ����������䳤��Ϊ65535�ֽڡ�
               ע�⣺���ô˺���ǰ���������ú�������ƿ顣
	 *  �������  :
	 *
	 *  �������  : ��
	 *  �� �� ֵ  :  0	       �����ɹ���
        *                           ����	����ʧ�ܡ�
     	 *
	 ******************************************************************************/
int mdrv_edma_chan_lli_async_start(unsigned int channel_id);

/*****************************************************************************
	 *  �� �� ��  : mdrv_edma_chan_is_idle
	 *  ��������  :  ��ѯDMAͨ���Ƿ���С�
	 *  �������  :
	 *
	 *  �������  : ��
	 *  �� �� ֵ  : 	0		ͨ������
	 *                         1		ͨ��æ
	 *                        ����		��ѯʧ��
     	 *
	 ******************************************************************************/
int mdrv_edma_chan_is_idle(unsigned int channel_id);

#ifdef __cplusplus
}
#endif
#endif

