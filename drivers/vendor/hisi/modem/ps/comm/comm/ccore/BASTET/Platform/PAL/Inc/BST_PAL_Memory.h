

#ifndef __BST_PAL_MEMORY_H__
#define __BST_PAL_MEMORY_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "BST_Platform.h"
#include "vos.h"
#ifdef __OS_VXWORKS__
#include <semLib.h>
#endif 
#include "PsCommonDef.h"
#include "TTFMem.h"
#include "TTFMemInterface.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define BST_OS_PalMalloc( ulSize )      ( PS_MEM_ALLOC( UEPS_PID_BASTET, ulSize) )
#define BST_OS_PalFree( pAddr )         ( PS_MEM_FREE( UEPS_PID_BASTET, pAddr ) )
#define BST_OS_PalSizeof( datatype )    ( sizeof( datatype ) )

#define BST_OS_PalMemInit()
#define BST_OS_PalMemset( pData,  ucValue, ulSize ) ( PS_MEM_SET( pData,  ucValue, ulSize ) )
#define BST_OS_PalMemcmp( pData1, pData2,  ulSize ) ( PS_MEM_CMP( pData1, pData2,  ulSize ) )
#define BST_OS_PalMemcpy( pDst,   pSrc,    ulSize ) ( PS_MEM_CPY( pDst,   pSrc,    ulSize ) )
#define BST_OS_PalMemmove(pDst,   pSrc,    ulSize ) ( PS_MEM_MOVE(pDst,   pSrc,    ulSize ) )

/*****************************************************************************
  5 ��/�ṹ����
*****************************************************************************/
typedef size_t                          BST_OS_MEMSIZE_T;

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif
