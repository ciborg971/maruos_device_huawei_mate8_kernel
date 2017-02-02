

#ifndef __CARDLOCKCIPHER_H__
#define __CARDLOCKCIPHER_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "PsTypeDef.h"
#include "Hi_Config.h"
#include "PsCommonDef.h"
#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define CARDLOCK_CIPHER_CONTEXT_TOTAL_NUM                   (2)
#define CARDLOCK_CIPHER_CONTEXT_STATE_NUM                   (4)
#define CARDLOCK_CIPHER_CONTEXT_BUFFER_NUM                  (64)
#define CARDLOCK_CIPHER_CONTEXT_INNER_NUM                   (64)
#define CARDLOCK_CIPHER_CONTEXT_OUTER_NUM                   (64)

/*****************************************************************************
  3 STRUCT����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          aulTotal[CARDLOCK_CIPHER_CONTEXT_TOTAL_NUM];  /*!< number of bytes processed  */
    VOS_UINT32                          aulState[CARDLOCK_CIPHER_CONTEXT_STATE_NUM];  /*!< intermediate digest state  */
    VOS_UINT8                           aucBuffer[CARDLOCK_CIPHER_CONTEXT_BUFFER_NUM];/*!< data block being processed */
    VOS_UINT8                           aucIpad[CARDLOCK_CIPHER_CONTEXT_INNER_NUM];   /*!< HMAC: inner padding        */
    VOS_UINT8                           aucOpad[CARDLOCK_CIPHER_CONTEXT_OUTER_NUM];   /*!< HMAC: outer padding        */
}CARDLOCK_CIPHER_CONTEXT_STRU;

/*****************************************************************************
  4 ��������
*****************************************************************************/

extern VOS_VOID CardLockCipher( VOS_UINT8 *pucInput, VOS_INT32 ulInputLen, VOS_UINT8 aucOutput[16] );
extern VOS_VOID CardLockCipher_Finish( CARDLOCK_CIPHER_CONTEXT_STRU *pstCtx, VOS_UINT8 aucOutput[16] );
extern VOS_VOID CardLockCipher_Hmac(
                                                VOS_UINT8 *pucKey,
                                                VOS_INT32 lKeylen,
                                                VOS_UINT8 *pucInput,
                                                VOS_UINT32 ulInputLen,
                                                VOS_UINT8 aucOutput[16] );
extern VOS_VOID CardLockCipher_Hmac_Finish( CARDLOCK_CIPHER_CONTEXT_STRU *pstCtx, VOS_UINT8 aucOutput[16] );
extern VOS_VOID CardLockCipher_Hmac_Starts( CARDLOCK_CIPHER_CONTEXT_STRU *pstCtx, VOS_UINT8 *pucKey, VOS_INT32 lKeylen );
extern VOS_VOID CardLockCipher_Hmac_Update( CARDLOCK_CIPHER_CONTEXT_STRU *pstCtx, VOS_UINT8 *pucInput, VOS_INT32 lInputLen );
extern VOS_VOID CardLockCipher_Starts( CARDLOCK_CIPHER_CONTEXT_STRU *pstCtx );
extern VOS_VOID CardLockCipher_Update( CARDLOCK_CIPHER_CONTEXT_STRU *pstCtx, VOS_UINT8 *pucInput, VOS_INT32 lInputLen );

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of CardLockCipher.h */
