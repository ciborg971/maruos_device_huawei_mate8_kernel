/*************************************************************************
*   ��Ȩ����(C) 1987-2013, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  Drvinterface.h
*
*   ��    �� :  wangxiandong
*
*   ��    �� :  ���ļ�����Ϊ"Drvinterface.h", ����V7R1�����Э��ջ֮���API�ӿ�ͳ��
*
*   �޸ļ�¼ :  2013��1��21��  v1.00  wangxiandong ����
*************************************************************************/
#ifndef __BSP_CIPHER_H__
#define __BSP_CIPHER_H__

#include <osl_types.h>
#include <product_config.h>
#include <mdrv_cipher.h>
#include "kdf_balong.h"
#include "cipher_balong.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_CIPHER
int cipher_init(void);
#else
int cipher_init(void)
{return 0;}
#endif
int cipher_start_channel(unsigned int chn, unsigned int num, CIPHER_SUBMIT_TYPE_E subm_attr);
int mdrv_cipher_chn_idle(unsigned int chn);
int kdf_rw_key (KDF_OPS kdf_op, void * pDestAddr, unsigned int u32KeyIndex ,unsigned int u32ReadLength);
int mdrv_cipher_gen_key(KEY_CONFIG_INFO_S * pstKeyCfgInfo, S_CONFIG_INFO_S * pstSCfgInfo,
	unsigned int u32DestIndex, KEY_MAKE_S * pstKeyMake);


/*************************KDF HASH START **********************************/
/*****************************************************************************
* �� �� ��  : kdf_init
*
* ��������  : A��KDF���пռ������ʼ�������ڼ���HASHֵ����C������֮ǰʹ��
*
* �������  : ��
* �������  : ��
* �� �� ֵ  : 0    : ��ȷ
*             ���� : ����
*****************************************************************************/
int kdf_init(void);

int kdf_hash_init(void);
int kdfdev_init(void);
void kdfdev_exit(void);
/*****************************************************************************
* �� �� ��  : kdf_reg_init
*
* ��������  : A��KDF�Ĵ������ã����ڼ���HASHֵ����C������֮ǰʹ��
*
* �������  : ��
* �������  : ��
* �� �� ֵ  : ��
*****************************************************************************/
void kdf_reg_init(void);
/*****************************************************************************
* �� �� ��  : kdf_hash_setkey
*
* ��������  : A��KDF��������key�����ڼ���HASHֵ����C������֮ǰʹ��
*
* �������  : ����key���׵�ַ��Ĭ��key�ĳ��ȹ̶�Ϊ32�ֽ�
* �������  : ��
* �� �� ֵ  : 0    : ��ȷ
*             ���� : ����
*****************************************************************************/
int kdf_hash_setkey(void * key_addr);
/*****************************************************************************
* �� �� ��  : kdf_result_hash_get
*
* ��������  : A��KDF������ȡ���HASH����C������֮ǰʹ��
*
* �������  : ��
* �������  : out_hash : ���ڽ��ս��HASH���ڴ�ռ��׵�ַ��Ĭ������32�ֽ�
* �� �� ֵ  : 0    : ��ȷ
*             ���� : ����
*****************************************************************************/
int kdf_result_hash_get(void * out_hash);
/*****************************************************************************
* �� �� ��  : kdf_hash_make
*
* ��������  : A��KDF��������HASH����C������֮ǰʹ��
*
* �������  : sha_s_addr : �������ݵ��׵�ַ��������󳤶Ȳ��ܳ���512�ֽ�
*             sha_s_len  : �������ݵ�ʵ�ʳ��ȣ����ֽ�Ϊ��λ
* �������  : ��
* �� �� ֵ  : 0    : ��ȷ
*             ���� : ����
*****************************************************************************/
int kdf_hash_make(void * sha_s_addr, u32 sha_s_len);
/*************************KDF HASH END **********************************/

int bsp_cipher_set_channel_dma(int channel, int dma);

#ifdef __cplusplus
}
#endif

#endif /* end of __BSP_CIPHER_H__ */

