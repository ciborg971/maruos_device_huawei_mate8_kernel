/*************************************************************************
*   ��Ȩ����(C) 2008-2013, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  kdf_balong.h
*
*   ��    �� :  wangxiandong
*
*   ��    �� :  kdf����ʵ��ͷ�ļ�
*
*   �޸ļ�¼ :  2013��03��12��  v1.00  wangxiandong ����
*************************************************************************/
#ifndef	_KDF_BALONG_H_
#define	_KDF_BALONG_H_

#include <osl_types.h>
#include <osl_sem.h>
#include "cipher_balong.h"

#ifdef __cplusplus
extern "C" {
#endif


#define KDF_BD_NUM          2
#define KDF_RD_NUM          KDF_BD_NUM
#define KDF_SHA_KEY_MAX_LEN 32
#define KDF_SHA_S_MAX_LEN   512

#define KDF_CH_BUSY         (0x1U << 31)
#define KDF_RD_VALID        (0x1U << 31)
#define KDF_RD_CHECK_ERR    (0x3U << 29)

#define	KDF_TIME_RATIO	(32768)	/*one second*/
#define	KDF_TEN_MS		(KDF_TIME_RATIO/100)

#define KDF_RPTR_OFFSET		16

/*lint -e760*/
#define CIPHER_BSWAP32(val) \
        (((val) >> 24) | (((val) >> 8) & 0x0000ff00) | \
        (((val) << 8) & 0x00ff0000) | ((val) << 24))
/*lint +e760*/
typedef enum tagKDF_OPS
{
	KDF_OPS_KEY_MAKE  = 0,
	KDF_OPS_KEY_WRITE = 1,
	KDF_OPS_KEY_READ  = 2
}KDF_OPS;

struct kdf_bd
{
	u32 cfg;
	u32 addr;
};

struct kdf_rd
{
	u32 addr;
	u32 cfg;
};
struct kdf_debug
{
	unsigned int timeout;
};

/*lint -e959*/
struct kdf_chn_ctl
{
	void *          reg_base;
	struct kdf_bd * bd_fifo_base;
	struct kdf_rd * rd_fifo_base;
	void *          key_s_buf;
	unsigned int    bd_w_idx;
	unsigned int    rd_r_idx;
	osl_sem_id      kdf_sem;
	struct kdf_debug *kdf_dbg;
};
/*lint +e959*/

#ifdef __cplusplus
}
#endif

#endif /* _KDF_BALONG_H_ */
