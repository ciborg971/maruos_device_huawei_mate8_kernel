

#ifndef  __BST_PAL_LOG_H__
#define  __BST_PAL_LOG_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "PsLogdef.h"
#include "OmCommon.h"
#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define BST_PAL_ERROR_LOG(MsgString)\
    BST_PAL_LOG( __FILE__, __LINE__, UEPS_PID_BASTET, LOG_LEVEL_ERROR, (MsgString) )
#define BST_PAL_ERROR_LOG1(MsgString,Para1)\
    BST_PAL_LOG1( __FILE__, __LINE__, UEPS_PID_BASTET, LOG_LEVEL_ERROR,  (MsgString), ((BST_INT32)Para1))
#define BST_PAL_ERROR_LOG2(MsgString,Para1,Para2)\
    BST_PAL_LOG2(  __FILE__, __LINE__, UEPS_PID_BASTET, LOG_LEVEL_ERROR, (MsgString), ((BST_INT32)Para1), ((BST_INT32)Para2) )
#define BST_PAL_ERROR_LOG3(MsgString,Para1,Para2,Para3)\
    BST_PAL_LOG3(  __FILE__, __LINE__, UEPS_PID_BASTET, LOG_LEVEL_ERROR, (MsgString),\
            ((BST_INT32)Para1), ((BST_INT32)Para2), ((BST_INT32)Para3) )
#define BST_PAL_ERROR_LOG4(MsgString,Para1,Para2,Para3,Para4)\
    BST_PAL_LOG4(  __FILE__, __LINE__, UEPS_PID_BASTET, LOG_LEVEL_ERROR, (MsgString),\
            ((BST_INT32)Para1), ((BST_INT32)Para2), ((BST_INT32)Para3), ((BST_INT32)Para4) )

#define BST_PAL_INFO_LOG(MsgString)\
    BST_PAL_LOG( __FILE__, __LINE__, UEPS_PID_BASTET, LOG_LEVEL_INFO, (MsgString) )
#define BST_PAL_INFO_LOG1(MsgString,Para1)\
    BST_PAL_LOG1( __FILE__, __LINE__, UEPS_PID_BASTET, LOG_LEVEL_INFO, (MsgString), ((BST_INT32)Para1))
#define BST_PAL_INFO_LOG2(MsgString,Para1,Para2)\
    BST_PAL_LOG2( __FILE__, __LINE__, UEPS_PID_BASTET, LOG_LEVEL_INFO, (MsgString), ((BST_INT32)Para1), ((BST_INT32)Para2) )
#define BST_PAL_INFO_LOG3(MsgString,Para1,Para2,Para3)\
    BST_PAL_LOG3( __FILE__, __LINE__, UEPS_PID_BASTET, LOG_LEVEL_INFO, (MsgString),\
            ((BST_INT32)Para1), ((BST_INT32)Para2), ((BST_INT32)Para3) )
#define BST_PAL_INFO_LOG4(MsgString,Para1,Para2,Para3,Para4)\
    BST_PAL_LOG4( __FILE__, __LINE__, UEPS_PID_BASTET, LOG_LEVEL_INFO, (MsgString),\
            ((BST_INT32)Para1), ((BST_INT32)Para2), ((BST_INT32)Para3), ((BST_INT32)Para4) )


/*****************************************************************************
  8 ��������
*****************************************************************************/

BST_VOID BST_PAL_LOG(
    const BST_CHAR *pcFileName,
    BST_UINT32 ulLineNum,
    BST_UINT32 ulModuleId, 
    BST_UINT32 ulLevel, 
    const BST_CHAR *pcString);

BST_VOID BST_PAL_LOG1(
    const BST_CHAR *pcFileName,
    BST_UINT32 ulLineNum,
    BST_UINT32 ulModuleId,
    BST_UINT32 ulLevel,
    const BST_CHAR *pcString,
    BST_INT32 lPara1);

BST_VOID BST_PAL_LOG2(
    const BST_CHAR *pcFileName,
    BST_UINT32 ulLineNum,
    BST_UINT32 ulModuleId,
    BST_UINT32 ulLevel, 
    const BST_CHAR *pcString,
    BST_INT32 lPara1,
    BST_INT32 lPara2);

BST_VOID BST_PAL_LOG3(
    const BST_CHAR *pcFileName,
    BST_UINT32 ulLineNum,
    BST_UINT32 ulModuleId,
    BST_UINT32 ulLevel,
    const BST_CHAR *pcString,
    BST_INT32 lPara1,
    BST_INT32 lPara2,
    BST_INT32 lPara3);

BST_VOID BST_PAL_LOG4(
    const BST_CHAR *pcFileName,
    BST_UINT32 ulLineNum,
    BST_UINT32 ulModuleId,
    BST_UINT32 ulLevel,
    const BST_CHAR *pcString,
    BST_INT32 lPara1,
    BST_INT32 lPara2,
    BST_INT32 lPara3,
    BST_INT32 lPara4);


BST_VOID BST_PAL_SetLogSwitch(BST_UINT32 ulLevel);

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
