#ifndef __MDRV_CCORE_CRYPTO_H__
#define __MDRV_CCORE_CRYPTO_H__
#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
    CREATE_CRYPTO_KEY_ALGORITHM_MD5 = 0x0,
    CREATE_CRYPTO_KEY_ALGORITHM_SHA1,
    CREATE_CRYPTO_KEY_ALGORITHM_SHA256,
    CREATE_CRYPTO_KEY_ALGORITHM_MAX,
}CREATE_CRYPTO_KEY_ALGORITHM_E;

typedef enum
{
    CRYPTO_ALGORITHM_MD5 = 0x0,
    CRYPTO_ALGORITHM_SHA1,
    CRYPTO_ALGORITHM_SHA256,
    CRYPTO_ALGORITHM_MAX,
}CRYPTO_HASH_ALGORITHM_E;

typedef enum
{
    CRYPTO_ENCRYPT_ALGORITHM_AES_ECB = 0x0,
    CRYPTO_ENCRYPT_ALGORITHM_MAX,
}CRYPTO_ENCRYPT_ALGORITHM_E;

/*****************************************************************************
* �� �� ��  : mdrv_crypto_gen_key
*
* ��������  : ���������µ���Կ
*
* �������  : char *data   �������������Կ������
*             int len      ����������ݳ���(�ֽ�)
*             mdrv_crypto_gen_key_ALGORITHM algorithm  ���ڲ�����Կ���㷨
*             char *key    ���ɵ���Կ
*             int *klen    ��Ϊ����ʱ���key�Ļ������ĳ��ȡ���Ϊ���������������ɵ���Կ�ĳ��ȡ�(�ֽ�)
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ�ܣ�
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_crypto_gen_key (char *data, int len, CREATE_CRYPTO_KEY_ALGORITHM_E algorithm, char *key, int *klen);

/*****************************************************************************
* �� �� ��  : mdrv_crypto_hash
*
* ��������  : ����HASHֵ
*
* �������  : char *data   ���������Ҫ����HASHֵ������
*             int len      ����������ݳ���(�ֽ�)
*             CRYPTO_HASH_ALGORITHM_E algorithm  HASH�㷨
*             char *hash   ������ɵ�HASHֵ
*             int *hlen    ��Ϊ������������HASHֵ�Ļ������ĳ��ȣ���Ϊ���������������ɵ�HASHֵ�ĳ��ȣ��ֽڣ�
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ�ܣ�
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_crypto_hash (char *data, int len, CRYPTO_HASH_ALGORITHM_E algorithm, char *hash, int *hlen);

/*****************************************************************************
* �� �� ��  : mdrv_crypto_enc
*
* ��������  : AES����
*
* �������  : char *data   �����ܵ�����
*             int len      �������ݳ���(�ֽ�)
*             CRYPTO_ENCRYPT_ALGORITHM_E algorithm  �����㷨
*             char *key    ������Կ
*             int klen     ��Կ�ĳ���(�ֽ�)
*             char *cipher_data ���ܺ������
*             int *cipher_len  (�ֽ�)��Ϊ���������������ĵĻ������ĳ��ȡ���Ϊ���������������ɵ����ĵĳ���
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ�ܣ�
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_crypto_enc (char *data, int len, CRYPTO_ENCRYPT_ALGORITHM_E algorithm, char *key, int klen, char *cipher_data, int *cipher_len);

/*****************************************************************************
* �� �� ��  : mdrv_crypto_dec
*
* ��������  : AES����
*
* �������  : char *cipher_data  �����ܵ�����
*             int cipher_len     �������ݳ���(�ֽ�)
*             CRYPTO_ENCRYPT_ALGORITHM_E algorithm  �����㷨
*             char *key          ��Կ
*             int klen           ��Կ����
*             char *data         ���ܺ������
*             int *len           (byte)���룺���ܺ�����ݵĴ��buffer��buffer size�� (û�м��)����������ܺ�����ݳ��ȡ�
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ�ܣ�
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_crypto_dec (char *cipher_data,int cipher_len,CRYPTO_ENCRYPT_ALGORITHM_E algorithm, char *key, int klen, char *data, int *len);

/*****************************************************************************
* �� �� ��  : mdrv_crypto_enc_rsa
*
* ��������  : RSA����
*
* �������  : char *data     �����ܵ�����
*             int len        �������ݳ���(�ֽ�)
*             char *rsa_key  ��Կ
*             int rsa_klen   ��Կ����
*             char *cipher_data ���ܺ������
*             int *cipher_len   (�ֽ�)��Ϊ���������������ĵĻ������ĳ��ȡ���Ϊ���������������ɵ����ĵĳ��ȡ�
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ�ܣ�
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_crypto_enc_rsa (char *data, int len, char *rsa_key, int rsa_klen, char *cipher_data, int *cipher_len);

/*****************************************************************************
* �� �� ��  : mdrv_crypto_dec_rsa
*
* ��������  : RSA����
*
* �������  : char *cipher_data  �����ܵ�����
*             int cipher_len     �������ݳ���(�ֽ�)
*             char *rsa_key      ��Կ
*             int rsa_klen       ��Կ����
*             char *data         ���ܺ������
*             int *len           (byte)���룺���ܺ�����ݵĴ��buffer��buffer size�� (û�м��)����������ܺ�����ݳ��ȡ�
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ�ܣ�
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_crypto_dec_rsa (char *cipher_data, int cipher_len, char *rsa_key, int rsa_klen, char *data, int *len);

/*****************************************************************************
* �� �� ��  : mdrv_crypto_gen_rand
*
* ��������  : ���������
*
* �������  : char *rand_data  ��������buffer
*             int len          �����õ���������ֽ���
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ�ܣ�
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_crypto_gen_rand (char *rand_data, int len);

/*****************************************************************************
* �� �� ��  : mdrv_crypto_secboot_supported
*
* ��������  : ��ǰ�汾�Ƿ�֧�ְ�ȫ����
*
* �������  : unsigned char *pu8Data �Ƿ�֧�ְ�ȫ������־[1:֧��   0:��֧��]
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ�ܣ�
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_crypto_secboot_supported (unsigned char *pu8Data);

/*****************************************************************************
* �� �� ��  : mdrv_crypto_sec_started
*
* ��������  : ��ѯ��ǰ�汾�Ƿ��Ѿ����ð�ȫ����
*
* �������  : unsigned char *pu8Data �Ƿ��Ѿ����ð�ȫ������־[1:����   0:δ����]
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ�ܣ�
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_crypto_sec_started (unsigned char *pu8Data);

/*****************************************************************************
* �� �� ��  : mdrv_crypto_start_secure
*
* ��������  : ���ð�ȫ����
*
* �������  : void
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ�ܣ�
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_crypto_start_secure (void);

/*****************************************************************************
* �� �� ��  : mdrv_crypto_check_sec
*
* ��������  : ��ȫ�����ж�
*
* �������  : void
* �������  :
*
* �� �� ֵ  : 1����ȫ����0���ǰ�ȫ����
*
* ����˵��  :
*
*****************************************************************************/
unsigned int mdrv_crypto_check_sec (void);

#ifdef __cplusplus
}
#endif
#endif
