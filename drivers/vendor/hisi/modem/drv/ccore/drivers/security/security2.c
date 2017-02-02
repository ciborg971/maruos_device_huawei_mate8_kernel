/*************************************************************************
*   ��Ȩ����(C) 1987-2020, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  security.c
*
*   ��    �� :  wuzechun
*
*   ��    �� :  ��ɰ�ȫУ�龵��Ĺ���,����ʹ��
*                 OnChipRom����Ĵ���,�ڲ�ʹ��OnChipRom�����
*                 ��,Ҳ����ʹ�õ���������.
*
*   �޸ļ�¼ :  2011��8��10��  v1.00  wuzechun  ����
*
*************************************************************************/
#include "osl_malloc.h"
#include <string.h>
#include <stdio.h>
#include "securec.h"
#include <mdrv_crypto.h>
#include "security2.h"
#include "cipher_aes.h"
#include "rsa.h"
#include "ran.h"
#include "sha_alg.h"
#include "bsp_efuse.h"
#include "bsp_om.h"
#include "efuse_balong.h"
#include "hi_efuse.h"

/*lint --e{534, 801} */
//#define EFUSE_HUK_SIZE          (4)
//#define EFUSE_GROUP_SIZE        (4)

//#ifdef HI_K3_EFUSE
//#define EFUSE_GRP_HUK           (28)
//#else
//#define EFUSE_GRP_HUK           (4)
//#endif

/*
 FIXME: too many params in each function, change to use struct.
 FIXME: use uint instead int for len/size params.
 FIXME: change char to void*
*/
#define  security_print(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_SECURITY, "[SECURITY]: <%s> "fmt"\n", __FUNCTION__, ##__VA_ARGS__))

int param_check(char *data, int len, CREATE_CRYPTO_KEY_ALGORITHM_E algorithm, char *key, int *klen)
{
    if(data == NULL || key == NULL || klen == NULL)
    {
        security_print("ERROR param_check: param is NULL pointer!\n");
        return BSP_ERROR;
    }

    if(len<=0)
    {
        security_print("ERROR param_check: param is invalid!\n");
        return BSP_ERROR;
    }
    return BSP_OK;
}

/*****************************************************************************
* �� �� ��  : create_crypto_key
*
* ��������  : ʹ����������ݺ�HUK��������Կ����ǰ֧��MD5����SHA-1�㷨��
*
*             ������Կ�ķ���:
*             ��HUK���������������������ΪMD5��SHA-1�㷨�����룬������HASHֵ��
*
* �������  : data:      ����������Կ�����ݡ�
*             len:       ����������Կ�����ݳ��ȡ�(byte)
*             algorithm: Ҫʹ�õ���Կ�����㷨��
*             klen:      ��Ϊ������������key�Ļ������ĳ��ȡ�(byte)
*
* �������  : key:       ������ɵ���Կ��buffer�������16(MD5)/20(SHA-1)�ֽڡ�
*             klen:      ��Ϊ���������������ɵ���Կ�ĳ��ȡ�(byte)
*
* �� �� ֵ  : BSP_OK:    ���ɳɹ���
*             BSP_ERROR: ����ʧ�ܡ�
*
* ����˵��  : klenΪ����/��������������klen���������ڴ�����д�ء�
*             ���Ա���ֱ�Ӵ�������sizeof()�ĺ������ý����
*
*****************************************************************************/
int create_crypto_key_o(char *data, int len, CREATE_CRYPTO_KEY_ALGORITHM_E algorithm, char *key, int *klen)
{
    char* crypto_data = NULL;
    UINT8 i=0;

        if(BSP_OK != param_check(data,len,algorithm,key,klen))
        {
        security_print("ERROR create_crypto_key: param is invalid!\n");
        goto ERROR_EXIT;
        }

    crypto_data = (char*)osl_malloc((unsigned int)(len + HUK_LEN));

    if(crypto_data == NULL)
    {
        security_print("ERROR create_crypto_key: malloc failed!\n");
        goto ERROR_EXIT;
    }

    memset_s(crypto_data, (size_t)(len + HUK_LEN), 0, (size_t)(len + HUK_LEN));

	/* Read & Copy HUK.*/
	if(BSP_OK != bsp_efuse_read((u32*)crypto_data, EFUSE_GRP_HUK, (HUK_LEN/sizeof(uint32)) ))
	{
	    security_print("ERROR create_crypto_key: efuseRead failed!\n");
        goto ERROR_EXIT;
	}
    for(i=0;i<HUK_LEN;i++)
    {
            if(0 != *(((UINT8*)crypto_data)+i))
            {
                break;
            }
    }

    if(i>=HUK_LEN)
        {
            security_print("ERROR create_crypto_key: read_efuse NULL!\n");
            goto ERROR_EXIT;
    }


    // Copy user data.
    memcpy_s((void*)((UINT32)crypto_data + HUK_LEN), (size_t)len, data, (size_t)len);


    // Encrypt.
    switch(algorithm)
    {
    /*case CREATE_CRYPTO_KEY_ALGORITHM_MD5:*/
    /*case CREATE_CRYPTO_KEY_ALGORITHM_SHA1:*/
    case CREATE_CRYPTO_KEY_ALGORITHM_SHA256:
        if(BSP_OK != mdrv_crypto_hash(crypto_data, len + HUK_LEN, (CRYPTO_HASH_ALGORITHM_E)algorithm, key, klen))
        {
            security_print("ERROR create_crypto_key: mdrv_crypto_hash failed!\n");
            goto ERROR_EXIT;
        }

        break;

    default:
        security_print("ERROR create_crypto_key: unknown algorithm!\n");

        goto ERROR_EXIT;
    }

    osl_free(crypto_data);

#ifndef _DRV_LLT_
       /*REG_WRITE_32(PWR_SC_PERIPH_CLKDIS0, SOC_CLK_CLOSE_DIS0);*/
#endif
    return BSP_OK;

ERROR_EXIT:
    if(crypto_data != NULL)
    {
        osl_free(crypto_data);
    }

    return BSP_ERROR;
}

int mdrv_crypto_gen_key (char *data, int len, CREATE_CRYPTO_KEY_ALGORITHM_E algorithm, char *key, int *klen)
{
    if (create_crypto_key_o(data, len, algorithm, key, klen))
    {
        
        return BSP_ERROR;
    }
    
    return BSP_OK;
}
/*****************************************************************************
* �� �� ��  : mdrv_crypto_hash
*
* ��������  : ������������ݣ����16�ֽڵ�HASHֵ����ǰ֧��MD5����SHA-1�㷨��
*
* �������  : data:      ������HASHֵ�����ݡ�
*             len:       ������HASHֵ�����ݳ��ȡ�(byte)
*             algorithm: ��Ҫʹ�õ�HASH�㷨��
*             hlen:      ��Ϊ������������HASHֵ�Ļ������ĳ��ȡ�(byte)
*
* �������  : hash:      ������ɵ�HASHֵ��buffer�������16(MD5)/20(SHA-1)�ֽڡ�
*             hlen:      ��Ϊ���������������ɵ�HASHֵ�ĳ��ȡ�(byte)
*
* �� �� ֵ  : OK:        ���ɳɹ���
*             ERROR:     ����ʧ�ܡ�
*
* ����˵��  : hlenΪ����/��������������hlen���������ڴ�����д�ء�
*             ���Ա���ֱ�Ӵ�������sizeof()�ĺ������ý����
*
*****************************************************************************/
int crypto_hash_o(char *data, int len, CRYPTO_HASH_ALGORITHM_E algorithm, char *hash, int *hlen)
{
    if(data == NULL || hash == NULL || hlen == NULL)
    {
        security_print("ERROR mdrv_crypto_hash: param is NULL pointer!\n");
        return BSP_ERROR;
    }

    if(len<=0 )
    {
        security_print("ERROR mdrv_crypto_hash: param is invalid!\n");
        return BSP_ERROR;
    }

    switch(algorithm)
    {
    case CRYPTO_ALGORITHM_SHA256:

        if (*hlen < SHA256_DIGEST_LENGTH)
        {
            security_print("ERROR mdrv_crypto_hash: param hlen is invalid!(hash bufsize is too small)\n");
            return BSP_ERROR;
        }

        SHA256_Hash((unsigned char*)data,(unsigned long)len,(unsigned char*)hash);

        *hlen = SHA256_DIGEST_LENGTH;

        break;
    case CRYPTO_ALGORITHM_MD5:
    case CRYPTO_ALGORITHM_SHA1:
    default:
        security_print("ERROR mdrv_crypto_hash: unknown algorithm!\n");

        return BSP_ERROR;
    }

    return BSP_OK;
}/*lint !e429*/

int mdrv_crypto_hash (char *data, int len, CRYPTO_HASH_ALGORITHM_E algorithm, char *hash, int *hlen)
{
    if(crypto_hash_o(data, len,  algorithm, hash,  hlen))
    {
        
        return BSP_ERROR;
    }
    return BSP_OK;
}
/*****************************************************************************
* �� �� ��  : crypto_encrypt
*
* ��������  : ʹ��ָ������Կ��ָ�����㷨����������ݼ��ܣ�������ܺ�����ݡ�
*             ��ǰ֧��AES-ECB�㷨��
*
* �������  : data:        ���������ݡ�
*             len:         ���������ݳ��ȡ�(byte)
*             algorithm:   ����HASH�㷨��
*             key:         ��Կbuffer��
*             klen:        ��Կbuffer���ȡ�(byte)
*             cipher_len:  ���ܺ�����ݵĴ��buffer��buffer size��(byte)(û�м��)
*
* �������  : cipher_data: ���ܺ�����ݵĴ��buffer��
*             cipher_len:  ���ܺ�����ݵ�ʵ�ʳ��ȡ�(byte)
*
* �� �� ֵ  : BSP_OK:      ���ܳɹ���
*             BSP_ERROR:   ����ʧ�ܡ�
*
* ����˵��  : cipher_lenΪ����/��������������cipher_len���������ڴ�����д�ء�
*             ���Ա���ֱ�Ӵ�������sizeof()�ĺ������ý����
*
*****************************************************************************/
int crypto_encrypt_o (char *data, int len, CRYPTO_ENCRYPT_ALGORITHM_E algorithm, char *key, int klen, char *cipher_data, int *cipher_len)
{
    crypto_aes aes_ctx;
    int16 keybits = 0;
    if(data == NULL || key == NULL || cipher_data == NULL || cipher_len == NULL)
    {
        security_print("ERROR crypto_encrypt: param is NULL pointer!\n");
        return BSP_ERROR;
    }

    if(len<=0 || (klen != AES_KEY_LEN && klen != 16))
    {
        security_print("ERROR crypto_encrypt: param is invalid!\n");
        return BSP_ERROR;
    }
    if (klen == 16)
    {
        keybits = 128;/* [false alarm]:�� */
    }
    else if(klen == AES_KEY_LEN)
    {
        keybits = 256;/* [false alarm]:�� */
    }
    crypto_aes_init(&aes_ctx,(UINT8*)key,keybits,MODE_ECB,NULL);

    switch(algorithm)
    {
    case CRYPTO_ENCRYPT_ALGORITHM_AES_ECB:
        //if(0 != crypto_aes_encrypt_pad(&aes_ctx,data,len,cipher_data,cipher_len))
        if(0 != crypto_aes_encrypt_block(&aes_ctx,(UINT8*)data,len,(UINT8*)cipher_data,(int32*)cipher_len))
        {
            security_print("ERROR crypto_encrypt: crypto_aes_encrypt_pad failed!\n");
            return BSP_ERROR;
        }
        break;

    default:
        security_print("ERROR crypto_encrypt: unknown algorithm!\n");

        return BSP_ERROR;
    }

    return BSP_OK;
}

int mdrv_crypto_enc (char *data, int len, CRYPTO_ENCRYPT_ALGORITHM_E algorithm, char *key, int klen, char *cipher_data, int *cipher_len)
{
    if(crypto_encrypt_o(data, len, algorithm, key, klen, cipher_data, cipher_len))
    {
        
        return BSP_ERROR;        
    }
    return BSP_OK;
}

/*****************************************************************************
* �� �� ��  : crypto_decrypt
*
* ��������  : ʹ��ָ������Կ��ָ�����㷨����������ݽ��ܣ�������ܺ�����ݡ�
*             ��ǰ֧��AES-ECB�㷨��
*
* �������  :
*             cipher_data: ���ܵ����ݵĴ��buffer��
*             cipher_len:  �����ܵ����ݵ�ʵ�ʳ��ȡ�(byte)
*             algorithm:   ���ý����㷨����ֻ�ṩAES-ECB��
*             key:         ��Կbuffer��
*             klen:        ��Կbuffer���ȡ�(byte)
*             len:  ���ܺ�����ݵĴ��buffer��buffer size��(byte)(û�м��)
*
* �������  :
*             data:        ���ܺ�����ݡ�
*             len:         ���ܺ�����ݳ��ȡ�(byte)
*
* �� �� ֵ  : BSP_OK:      ���ܳɹ���
*             BSP_ERROR:   ����ʧ�ܡ�
*
* ����˵��  : lenΪ����/��������������len���������ڴ�����д�ء�
*             ���Ա���ֱ�Ӵ�������sizeof()�ĺ������ý����
*
*****************************************************************************/
int crypto_decrypt_o (char *cipher_data,int cipher_len,CRYPTO_ENCRYPT_ALGORITHM_E algorithm, char *key, int klen, char *data, int *len)
{
    crypto_aes aes_ctx;

    if((cipher_data == NULL) || (cipher_len == 0) || (data == NULL) || (key == NULL))
    {
        security_print("ERROR crypto_decrypt: param is NULL pointer!\n");
        return BSP_ERROR;
    }

    if(cipher_len<=0 || klen != AES_KEY_LEN)
    {
        security_print("ERROR crypto_decrypt: param is invalid!\n");
        return BSP_ERROR;
    }

    crypto_aes_init(&aes_ctx,(UINT8*)key,256,MODE_ECB,NULL);

    switch(algorithm)
    {
    case CRYPTO_ENCRYPT_ALGORITHM_AES_ECB:
        if(0 != crypto_aes_decrypt_block(&aes_ctx, (uint8 *)cipher_data, (int32)cipher_len, (uint8 *)data, (int32 *)len ))
        {
            security_print("ERROR crypto_decrypt: crypto_aes_decrypt_block failed!\n");
            return BSP_ERROR;
        }
        break;

    default:
        security_print("ERROR crypto_decrypt: unknown algorithm!\n");

        return BSP_ERROR;
    }

    return BSP_OK;
}

int mdrv_crypto_dec (char *cipher_data,int cipher_len,CRYPTO_ENCRYPT_ALGORITHM_E algorithm, char *key, int klen, char *data, int *len)
{
    if(crypto_decrypt_o(cipher_data,  cipher_len,  algorithm, key, klen,  data,  len))
    {
        
        return BSP_ERROR;
    }
    return BSP_OK; 
}
/*****************************************************************************
* �� �� ��  : mdrv_crypto_enc_rsa
*
* ��������  : ʹ�ñ�����NV�еĸ�����RSA��Կ������������ݼ��ܡ�
*             (��ȡʱ��Ҫͬ������ǩ����֤)
*
* �������  : data:        ���������ݡ�
*             len:         ���������ݳ��ȡ�(byte)
*             rsa_key:     RSA��Կbufferָ�롣
*             rsa_len:     RSA��Կbuffer���ȡ�(byte)
*             cipher_len:  ���ܺ�����ݵĴ��buffer��buffer size��(byte)(û�м��)
*
* �������  : cipher_data: ���ܺ�����ݵĴ��buffer��
*             cipher_len:  ���ܺ�����ݵ�ʵ�ʳ��ȡ�(byte)
*
* �� �� ֵ  : BSP_OK:      ���ܳɹ���
*             BSP_ERROR:   ����ʧ�ܡ�
*
* ����˵��  : cipher_lenΪ����/��������������cipher_len���������ڴ�����д�ء�
*             ���Ա���ֱ�Ӵ�������sizeof()�ĺ������ý����
*
*****************************************************************************/
int crypto_rsa_encrypt_o (char *data, int len, char *rsa_key, int rsa_klen, char *cipher_data, int *cipher_len)
{
    //rsa_public_key* p_rsa_key = (rsa_public_key*)rsa_key;/*ģA*/
    rsa_public_key* p_rsa_key = NULL;

    if(data == NULL || rsa_key == NULL || cipher_data == NULL || cipher_len == NULL)
    {
        security_print("ERROR mdrv_crypto_enc_rsa: param is NULL pointer!\n");
        return BSP_ERROR;
    }

    if(len <=0 || rsa_klen != RSA_KEY_LEN)
    {
        security_print("ERROR mdrv_crypto_enc_rsa: param is invalid!\n");
        return BSP_ERROR;
    }

    p_rsa_key = (rsa_public_key*)(rsa_key+rsa_klen/2);/*ģB*/

    if(0 != rsa_public_encrypt((UINT8*)data, (uint16)len, (UINT8*)cipher_data, (UINT16*)cipher_len, p_rsa_key))
    {
        security_print("ERROR mdrv_crypto_enc_rsa: rsa_private_encrypt failed!\n");
        return BSP_ERROR;
    }

    return BSP_OK;
}

int mdrv_crypto_enc_rsa (char *data, int len, char *rsa_key, int rsa_klen, char *cipher_data, int *cipher_len)
{
    if(crypto_rsa_encrypt_o( data,  len,  rsa_key,  rsa_klen,  cipher_data, cipher_len))
    {
        
        return BSP_ERROR;        
    }   
    return BSP_OK;
}
/*****************************************************************************
* �� �� ��  : mdrv_crypto_dec_rsa
*
* ��������  : ʹ�ñ�����NV�еĸ�����RSA��Կ������������ݽ��ܡ�
*
* �������  : cipher_data: ���������ݡ�
*             cipher_len:  ���������ݳ��ȡ�(byte)
*             rsa_key:     RSA��Կbufferָ��
*             rsa_len:     RSA��Կbuffer���ȡ�(byte)
*             len:         ���ܺ�����ݵĴ��buffer��buffer size��(byte)(û�м��)
*
* �������  : data:        ���ܺ�����ݵĴ��buffer��
*             len:         ���ܺ�����ݵ�ʵ�ʳ��ȡ�(byte)
*
* �� �� ֵ  : BSP_OK:      ���ܳɹ���
*             BSP_ERROR:   ����ʧ�ܡ�
*
* ����˵��  : lenΪ����/��������������len���������ڴ�����д�ء�
*             ���Ա���ֱ�Ӵ�������sizeof()�ĺ������ý����
*
*****************************************************************************/
int crypto_rsa_decrypt_o (char *cipher_data, int cipher_len, char *rsa_key, int rsa_klen, char *data, int *len)
{
    //rsa_public_key* p_rsa_key = (rsa_public_key*)rsa_key;/*ģA*/
    rsa_public_key* p_rsa_key = NULL;

    if(cipher_data == NULL || rsa_key == NULL || data == NULL || len == NULL)
    {
        security_print("ERROR mdrv_crypto_dec_rsa: param is NULL pointer!\n");
        return BSP_ERROR;
    }

    if(cipher_len <=0 || rsa_klen != RSA_KEY_LEN)
    {
        security_print("ERROR mdrv_crypto_dec_rsa: param is invalid!\n");
        return BSP_ERROR;
    }

    p_rsa_key = (rsa_public_key*)(rsa_key+rsa_klen/2);/*ģB*/

    if(0 != rsa_public_decrypt((UINT8*)cipher_data,(uint16)cipher_len,(UINT8*)data,(UINT16*)len,p_rsa_key))
    {
        security_print("ERROR mdrv_crypto_dec_rsa: rsa_public_decrypt failed!\n");
        return BSP_ERROR;
    }

    return BSP_OK;
}

int mdrv_crypto_dec_rsa (char *cipher_data, int cipher_len, char *rsa_key, int rsa_klen, char *data, int *len)
{
    if(crypto_rsa_decrypt_o(cipher_data, cipher_len, rsa_key,  rsa_klen,  data,  len))
    {
        
        return BSP_ERROR;        
    }
    return BSP_OK;
}
/*****************************************************************************
* �� �� ��  : crypto_rand
*
* ��������  : ��������ɽӿ�
*
* �������  : len:       �����õ���������ֽ���,ֻ֧��4�ֽڡ�(byte)
*
* �������  : rand_data: ��������buffer��
*
* �� �� ֵ  : BSP_OK:    ��ȡ������ɹ���
*             BSP_ERROR: ��ȡ�����ʧ�ܡ�
*
* ����˵��  : 1. ���ӿ���ʱ��Ϊ���ӻ�ȡ����������һ�ȡ�����ʱ��ǿ��ء�����
*                ��ͬһʱ�������������������á��������ý����ͬ�������
*
*             2. len����ֻ���ܴ���4��
*
*****************************************************************************/
int crypto_rand_o (char *rand_data, int len)
{
    if(NULL == rand_data)
    {
        security_print("ERROR crypto_rand: param rand_data is NULL pointer!\n");
        return BSP_ERROR;
    }

    if(len!=4)
    {
        security_print("ERROR crypto_rand: param len is invalid!\n");
        return BSP_ERROR;
    }
	/* coverity[secure_coding] */
    *(uint32*)rand_data = bsp_random();/* [false alarm]:coverity����ʱ�Ѿ��������� */

    return BSP_OK;
}

int mdrv_crypto_gen_rand (char *rand_data, int len)
{
        return crypto_rand_o(rand_data, len);
}

