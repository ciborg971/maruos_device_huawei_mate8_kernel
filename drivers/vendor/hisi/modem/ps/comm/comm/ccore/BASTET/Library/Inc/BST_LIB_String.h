
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifndef __BST_LIB_STRINT8U_H__
#define __BST_LIB_STRINT8U_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "BST_Platform.h"
//#include "string.h"
#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define BST_LIB_SHORT_STR_LEN           ( 128U )
#define BST_LIB_LONG_STR_LEN            ( 1024U )
#define BST_LIB_STR_BLOCK_SIZE          ( 128U )
#define BST_LIB_STR_NPO                 ( 0xFFFFU )
#define BST_LIB_IsStringInit(pStr)      ( 0!= pStr->usUsed )
#define BST_LIB_GetStringLen(pStr)      ( pStr->usUsed )
#define BST_LIB_GetStrDataPtr(pStr)     ( pStr->pData )
/*****************************************************************************
  5 ��/�ṹ����
*****************************************************************************/
typedef struct
{
    BST_CHAR               *pData;
    BST_UINT16              usSize;
    BST_UINT16              usUsed;
}BST_LIB_StrStru;

/*****************************************************************************
  4 ��������
*****************************************************************************/
/*****************************************************************************
  5 ��������
*****************************************************************************/
BST_VOID   BST_LIB_StrAddByte(
    BST_LIB_StrStru        *pStr,
    const BST_CHAR          cData );

BST_VOID   BST_LIB_StrClear(
    BST_LIB_StrStru        *pStr );

BST_VOID   BST_LIB_StrAddStr(
    BST_LIB_StrStru        *pStr,
    const BST_CHAR         *pcData );

BST_VOID   BST_LIB_StrAddBytes(
    BST_LIB_StrStru        *pStr,
    BST_CHAR               *pcData,
    BST_UINT16              usBufLen );

BST_BOOL   BST_LIB_StrInsert(
    BST_UINT16              usOfset,
    BST_LIB_StrStru        *pStr,
    BST_CHAR               *pcData );

BST_UINT16 BST_LIB_StrCmp(
    BST_UINT16              usOfset,
    const BST_CHAR         *pStr,
    const BST_CHAR         *pcData,
    BST_UINT16 usBufLen );

BST_UINT16 BST_LIB_StrFind(
    const BST_CHAR         *pStr,
    const BST_UINT16        usSrcLen,
    const BST_CHAR         *pcData,
    const BST_UINT16        usDstLen);


BST_ERR_ENUM_UINT8 BST_LIB_StrFill(
    BST_LIB_StrStru        *pStr,
    const BST_UINT8        *pucSrc,
    const BST_UINT16        ulLen );

BST_ERR_ENUM_UINT8  BST_LIB_StrReSize(
    BST_LIB_StrStru        *pStr,
    BST_UINT16              usLen );

BST_LIB_StrStru* BST_LIB_StrCreat(
    BST_UINT16              usLength );

BST_VOID BST_LIB_StrDelete(
    BST_LIB_StrStru         *pStr );

BST_UINT16 BST_LIB_StrLen(
    const BST_CHAR          *pcData );
/*zip ����*/
BST_CHAR *BST_ZLB_Uncompress(
    const BST_CHAR         *source,
    BST_INT32               comprlen,
    BST_UINT32             *uncomprlen );

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

