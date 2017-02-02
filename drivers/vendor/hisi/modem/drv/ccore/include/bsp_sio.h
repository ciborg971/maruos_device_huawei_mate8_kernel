/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : balong_sio.h
  �� �� ��   : ����
  ��    ��   : 
  ��������   : 
  ����޸�   :
  ��������   : drv_sio.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   :
    ��    ��   : 
    �޸�����   : 

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __BALONG_SIO_H__
#define __BALONG_SIO_H__

#include "bsp_memmap.h"
#include "drv_comm.h"
#include "bsp_clk.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define DRV_SIO_GET_STATUS_PTR()            (&g_stdrvsioctrl.stStatus)              /* ��ȡSIO״̬�Ĵ���ָ�� */
#define DRV_SIO_GET_INT_ISR_PTR()           (&g_stdrvsioctrl.stIsr)                 /* ��ȡSIO�жϻص�����ȫ�ֱ���*/
#define DRV_SIO_GET_CFG_PTR()               (&g_stdrvsioctrl)

#define HI_SIO_REG_ADDR(offs)               (HI_LTESIO_REGBASE_ADDR_VIRT + (offs))

/*ת���尴����д����*/
#define SIO_REG_WRITEBIT(uwAddr, uhwStartBit, uhwEndBit, swContent)    \
    BSP_REG_SETBITS(uwAddr, 0, uhwStartBit, uhwEndBit - uhwStartBit, swContent)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ʵ������  : DRV_SIO_INT_MASK_ENUM
 ��������  : SIO�����ж�����
*****************************************************************************/
typedef enum
{
    DRV_SIO_INT_MASK_RX_INTR            = 0x1,                                  /* ����FIFO������ֵ�ж�                 */
    DRV_SIO_INT_MASK_TX_INTR            = 0x2,                                  /* ����FIFO������ֵ�ж�                 */
    DRV_SIO_INT_MASK_RX_RIGHT_FIFO_OVER = 0x4,                                  /* I2Sģʽ��Ϊ����������FIFO������ж�  */
                                                                                /* PCMģʽ��ΪPCM����FIFO������ж�     */
    DRV_SIO_INT_MASK_RX_LEFT_FIFO_OVER  = 0x8,                                  /* ����������FIFO�����,ֻ��I2Sģʽ��Ч */
    DRV_SIO_INT_MASK_TX_RIGHT_FIFO_UNDER= 0x10,                                 /* I2Sģʽ��Ϊ����������FIFO������ж�  */
                                                                                /* PCMģʽ��ΪPCM����FIFO������ж�     */
    DRV_SIO_INT_MASK_TX_LEFT_FIFO_UNDER = 0x20,                                 /* ����������FIFO�����,ֻ��I2Sģʽ��Ч */
    DRV_SIO_INT_MASK_BUTT               = 0x40
}drv_sio_int_mask;

/*****************************************************************************
 ʵ������  : DRV_SIO_STATE_ENUM
 ��������  : SIO״̬��
*****************************************************************************/
typedef enum
{
    DRV_SIO_STATE_CLOSE                  = 0,                                    /* SIOʱ�ӹر� */
    DRV_SIO_STATE_OPEN,                                                          /* SIOʱ�Ӵ� */
    DRV_SIO_STATE_BUTT
}drv_sio_state_e;

/*****************************************************************************
 ʵ������  : DRV_SIO_SYNC_MODE_ENUM
 ��������  : SIOʱ�ӹ���ģʽ
*****************************************************************************/
typedef enum
{
    DRV_SIO_SYNC_MODE_SLAVE                  = 0,                                    /* SIO ��ģʽ */
    DRV_SIO_SYNC_MODE_MASTER,                                                        /* SIO ��ģʽ */
    DRV_SIO_SYNC_MODE_BUTT
}drv_sio_sync_mode_e;

/*****************************************************************************
 ʵ������  : DRV_SIO_MODE_ENUM
 ��������  : SIO����ģʽ
*****************************************************************************/
typedef enum
{
    DRV_SIO_MODE_I2S                            = 0,                /* SIO I2S����ģʽ */
    DRV_SIO_MODE_PCM,                                               /* SIO PCM����ģʽ */
    DRV_SIO_MODE_BUTT
}drv_sio_mode_e;

/*****************************************************************************
 ʵ������  : drv_sio_chn_num_e
 ��������  : SIO��·ѡ��
*****************************************************************************/
typedef enum
{
    DRV_SIO_CHN_2                            = 0,               
    DRV_SIO_CHN_4,                                               
    DRV_SIO_CHN_8,
    DRV_SIO_CHN_16,
    DRV_SIO_CHN_BUTT
}drv_sio_chn_num_e;

/*****************************************************************************
 ʵ������  : DRV_SIO_SAMPLING_ENUM
 ��������  : SIO������
*****************************************************************************/
typedef enum
{
    DRV_SIO_SAMPLING_8K                        = 8000,               /* ������Ϊ8k */
    DRV_SIO_SAMPLING_16K                       = 16000,              /* ������Ϊ16k */
    DRV_SIO_SAMPLING_48K                       = 48000,              /* ������Ϊ48k */
    DRV_SIO_SAMPLING_BUTT
}drv_sio_sample_e;

/*****************************************************************************
 ʵ������  : DRV_SIO_SAMPLING_ENUM
 ��������  : SIO������
*****************************************************************************/
typedef enum
{
    DRV_SIO_DMA_CTRL                            = 0,               /* DMA������ʽ */
    DRV_SIO_INT_CTRL,                                              /* �жϹ�����ʽ */
    DRV_SIO_POOL_CTRL,                                             /* ��ѯ��ʽ */
    DRV_SIO_CTRL_BUTT
}drv_sio_ctrl_e;

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
 �� �� ��  : drv_sio_int_func
 ��������  : SIO�жϴ���ص�����
 �������  : enIntType - �ж�����, �μ�DRV_SIO_INT_TYPE_ENUM_UINT16
             uwPara    - �û�����
 �������  : ��
 �� �� ֵ  : void
*****************************************************************************/
typedef void (*drv_sio_int_func)(
                drv_sio_int_mask enIntType,
                unsigned int                   uwPara);

/*****************************************************************************
 ʵ������  : drv_sio_int_isr_s
 ��������  : ����SIO�жϻص���������ʵ��
*****************************************************************************/
typedef struct
{
    drv_sio_int_func                      pfFunc;                                 /* �ص�����ָ�� */
    unsigned int                          uwPara;                               /* �ص�����     */
} drv_sio_int_isr_stru;

typedef void (*dma_int_func)(
                unsigned int                   uwPara);

/*****************************************************************************
 ʵ������  : DRV_DMA_CXISR_STRU
 ��������  : ����DMAͨ���ص���������ʵ��
*****************************************************************************/
typedef struct
{
    dma_int_func          pfFunc;         /* �ص�����ָ�� */
    unsigned int          uwPara;         /* �ص�����     */
} drv_dma_isr_stru;

typedef struct
{
   unsigned int       uwLli;              /* ͨ��Linked List Item��ַ     */
   unsigned short       uhwDstBIndex;       /* ͨ���Ķ�άĿ�ĵ�ַƫ�������ã�ռ��16bit */
   unsigned short       uhwSrcBIndex;       /* ͨ���Ķ�άԴ��ַƫ�������ã�ռ��16bit */
   unsigned short       uhwDstCIndex;       /* ͨ������άĿ�ĵ�ַƫ�������ã�ռ��16bit */
   unsigned short       uhwSrcCIndex;       /* ͨ������άԴ��ַƫ�������ã�ռ��16bit */
   unsigned short       uhwCCount;          /* ��ά���䳤������,��λFrame��ռ��16bit   */
   unsigned short       uhwRsv;             /* ����λ��ռ��16bit                    */
   unsigned short       uhwACount;          /* һά���䳤������,��λByte��ռ��16bit */
   unsigned short       uhwBCount;          /* ��ά���䳤������,��λArray��ռ��16bit  */
   unsigned int       uwSrcAddr;          /* ͨ��Դ��ַ                   */
   unsigned int       uwDstAddr;          /* ͨ��Ŀ�ĵ�ַ                 */
   unsigned int       uwConfig;           /* ͨ�����üĴ���               */

} drv_dma_cfg_stru __attribute__((aligned(32)));

/*****************************************************************************
 ʵ������  : pcm_data
 ��������  : PCM����ʵ��
*****************************************************************************/
typedef struct
{
    unsigned int * usBufA;
    unsigned int ulBufALen;
    unsigned int * usBufB;
    unsigned int ulBufBLen;
}pcm_data;

/*****************************************************************************
 ʵ������  : drv_sio_int_isr_s
 ��������  : ����SIO�жϻص���������ʵ��
*****************************************************************************/
typedef struct
{
    drv_dma_isr_stru                    pfFunc;                                 /* �ص�����ָ�� */
    drv_dma_cfg_stru                    play_cfg[2];
    drv_dma_cfg_stru                    record_cfg[2]; 
    unsigned int                        rx_channel_id;
    unsigned int                        tx_channel_id;
} dma_sio_cfg_stru;

/*****************************************************************************
 ʵ������  : drv_sio_status_struct
 ��������  : ����SIO״̬����ʵ��
*****************************************************************************/
typedef struct
{
    drv_sio_state_e               enOpen;                                       /* SIO����״̬ */
} drv_sio_status_stru;

/*****************************************************************************
 ʵ������  : drv_sio_ctrk_struct
 ��������  : ����SIO����ʵ��
*****************************************************************************/
typedef struct
{
    drv_sio_status_stru                 stStatus;                                       /* SIO����״̬ */
    drv_sio_mode_e                      enMode;                                         /* SIO�ӿ�ģʽ */
    drv_sio_sync_mode_e                 enSyncMode;                                    /* SIO����ģʽ */  
    drv_sio_chn_num_e                   chn_num;
    drv_sio_int_isr_stru                stIsr;                                          /* ����SIO�жϻص� */
    drv_sio_sample_e                    sample_rate;                                    /* ������ */     
    drv_sio_ctrl_e                      ctrl_mode;                                      /* �жϡ���ѯ����DMA��ʽ */
    struct clk                         *sio_clk;
    dma_sio_cfg_stru                    dma_cfg;
} drv_sio_ctrl_stru;

/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
void bsp_sio_close(void);
int bsp_sio_init(void);
void bsp_sio_isr(void);
int bsp_sio_open(
                       drv_sio_int_mask    enIntMask,
                       drv_sio_int_func    pfIntHandleFunc,
                       unsigned int        uwPara);

void bsp_sio_reset();
void bsp_sio_unreset();
void bsp_sio_set_mode(drv_sio_mode_e mode);
void bsp_sio_set_chn(drv_sio_chn_num_e chn_num);

#define DRV_SIO_DMA_LLI_LINK(uwAddr)        (((uwAddr) & 0xffffffe0UL) | (0x2UL))   /* ��������LLI������ */
#define DRV_SIO_DMA_LLI_CHAN(uhwChanNo)     (((unsigned int)(uhwChanNo) << 8)|(0x1UL))/* ͨ������LLI������ */
#define DRV_SIO_DMA_LLI_DISABLE             (0x0UL)                                 /* ����ģʽ��ʹ�������� */

#define DRV_SIO_DMA_MEM_SIO_CFG             (0x83311057)                            /* ���͵�MEM->SIO��DMA���ã�Դ��ַ������16bitλ��burst4 */
#define DRV_SIO_DMA_SIO_MEM_CFG             (0x43311047)                            /* ���͵�SIO->MEM��DMA���ã�Ŀ�ĵ�ַ������16bitλ��burst4 */
#define DRV_SIO_DMA_MEM_MEM_CFG             (0xfff33003)                            /* ���͵�MEM->MEM��DMA���ã���ַ˫�������64bitλ��burst1  */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif 
