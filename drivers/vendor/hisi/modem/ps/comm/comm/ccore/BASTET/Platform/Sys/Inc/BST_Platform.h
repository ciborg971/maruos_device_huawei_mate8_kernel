

#ifndef  __BST_PLATFORM_H__
#define  __BST_PLATFORM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "BST_Config.h"
#include "BST_Typedefine.h"
#include "BST_OS_Log.h"
#include "BST_SYS_MntnInterface.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define BST_INVALID_SNID                ( 0xFFFFU )

#if (BST_OS_VER == BST_WIN32)
#define BST_OS_S_IN_MIN                 ( 1U )
#else
#define BST_OS_S_IN_MIN                 ( 60U )
#endif

#define BST_OS_MS_IN_S                  ( 1000U )
#define BST_OS_MAX_UINT32               ( 0xFFFFFFFF )
typedef BST_VOID (*BST_OS_THREAD_T)(BST_VOID *pvArg);
#define BST_SYS_SUPPORT_NONE            ( 0x00U )
#define BST_SYS_SUPPORT_TCP_SHORT       ( 0x01U )
#define BST_SYS_SUPPORT_TCP_SHORT_SSL   ( 0x02U )
#define BST_SYS_SUPPORT_TCP_LONG        ( 0x04U )
#define BST_SYS_SUPPORT_TCP_LONG_SSL    ( 0x08U )
#define BST_SYS_SUPPORT_UDP             ( 0x10U )
#define BST_SYS_SUPPORT_UDP_SSL         ( 0x20U )

#define BST_SetThreadInitFlag( ulFlag ) \
                                        {\
                                            g_BstThreadInitFlags |= (ulFlag);\
                                            BST_RLS_LOG1("Bastet Threads 0x%x Init Success", (ulFlag) );\
                                        }

#define BST_GetThreadInitFlag()         ( g_BstThreadInitFlags )
#define BST_ClrThreadInitFlag()         ( g_BstThreadInitFlags = BST_NONE_THERAD_FLAG )

/*����BASTET�����¼�*//*����DOPRA�ֲᣬ�¼���16λΪϵͳ�������û�ʹ�õ�16λ��OSA��ʹ�ô�ȷ��*/
#define  BST_CDS_EVENT_BASE             (0x00000000)
#define  BST_CDS_EVENT_RCV_DL_PROC      (BST_CDS_EVENT_BASE | 0x0001)   /*����RCV�����¼�*/


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  6 UNION����
*****************************************************************************/


/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/
extern BST_UINT32 g_BstThreadInitFlags;
/*****************************************************************************
  8 ��������
*****************************************************************************/
BST_VOID BST_SYS_InitPlatform( BST_VOID );
BST_VOID BST_SYS_ApiSndEvtToBastet( BST_UINT32 ulEvent );
BST_BOOL BST_SYS_ApiGetSupported(BST_VOID);
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
