
#ifndef __BST_CORE_REGISTRYTBLMNG_H__
#define __BST_CORE_REGISTRYTBLMNG_H__
/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_CORE_RegistryDefine.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define BST_CORE_OPENSSL_ERR            ( 0 )
#define BST_CORE_OPENSSL_SUCCESS        ( 1 )
#define BST_CORE_PID_LEN                ( 2 )
#define BST_CORE_NO_PID_CHECK           ( BST_NULL_PTR )
#define BST_CORE_IsPidValid(enParamId)  ( ( ( enParamId ) > BST_PID_INVALID ) \
                                        &&( ( enParamId ) < BST_PID_DEF_BUTT ) )

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
enum BST_CORE_PID_LEN_ENUM
{
    BST_CORE_PID_VAR_LEN                = 0,
    BST_CORE_PID_FIX_LEN
};
typedef BST_UINT8                       BST_CORE_PID_LEN_ENUM_UINT8;

/*****************************************************************************
  4 ����/�ṹ�嶨��
*****************************************************************************/
typedef BST_UINT16 BST_CORE_PID_LEN_T;

typedef BST_BOOL( *BST_CORE_PID_CHKFUN_T )( const BST_VOID *const   pvContent,
                                            BST_UINT16              usLen );

typedef struct
{
    BST_CORE_PID_ENUM_UINT16            enPid;
    BST_CORE_PID_LEN_T                  usLen;
    BST_VOID                           *pvContent;
} BST_CORE_PID_STRU;

typedef struct
{
    BST_CORE_PID_ENUM_UINT16            enPid;
    BST_CORE_PID_LEN_ENUM_UINT8         enLenType;
    BST_CORE_PID_LEN_T                  usPlen;
} BST_CORE_PID_LUT_STRU;

/*****************************************************************************
  8 ��������
*****************************************************************************/
BST_CORE_PID_LUT_STRU  *BST_CORE_GetPidHandle   ( BST_CORE_PID_ENUM_UINT16 enParamId );
#ifdef   BST_SSL_SUPPORT
BST_ERR_ENUM_UINT8      BST_CORE_EncryptChk     ( BST_CORE_PID_ENUM_UINT16  enPid,
                                                  const BST_VOID           *pvData,
                                                  BST_UINT16                usLen,
                                                  BST_VOID                **ppOutData,
                                                  BST_UINT16               *pusOutLen );
BST_ERR_ENUM_UINT8      BST_CORE_DencryptChk    ( BST_CORE_PID_ENUM_UINT16  enPid,
                                                  const BST_VOID           *pvData,
                                                  BST_UINT16                usLen,
                                                  BST_VOID                **ppOutData,
                                                  BST_UINT16               *pusOutLen );
#endif

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif


#endif
