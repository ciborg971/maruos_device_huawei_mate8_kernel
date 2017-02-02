/*************************************************************************
*   ��Ȩ����(C) 1987-2020, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  security.h
*
*   ��    �� :  wuzechun
*
*   ��    �� :  security.c ��ͷ�ļ�
*
*   �޸ļ�¼ :  2011��8��10��  v1.00  wuzechun  ����
*
*************************************************************************/

#ifndef __SECURITY2_H__
#define __SECURITY2_H__

#include "drv_comm.h"

#define RSA_REG_MAX_DATA   0x80  /*RSA����ʱ���ݼĴ������С���ֽ���128Byte*/    

#define SHA1_PADDING_LENGTH_LIMIT   ((512-64)/8)  /*SHA1����ʱ���8λΪ����,����ǰ����56���ֽ�*/

#define HUK_LEN 16
#define SHA1_HASH_LEN 20
#define MD5_HASH_LEN 128

#define NV_RSA_PUB_KEY 5555 /*for compile*/

#define RSA_KEY_LEN 520
#define AES_KEY_LEN 32

BSP_S32 secSetRootCa( BSP_U8 *pBlBuf );

#endif /* security.h */

