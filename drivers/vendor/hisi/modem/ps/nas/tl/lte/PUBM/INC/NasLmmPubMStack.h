

#ifndef _NASLMMPUBMSTACK_H
#define _NASLMMPUBMSTACK_H


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include    "vos.h"

#include    "NasLmmPubMFsm.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
  5 STRUCT
*****************************************************************************/


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

extern  VOS_VOID    NAS_LMM_FSM_PushStackCombine(NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId);
extern  VOS_VOID    NAS_LMM_FSM_PushState(   NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId);
extern  VOS_VOID    NAS_LMM_FSM_PushTimer(  NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId);
extern  VOS_VOID    NAS_LMM_FSM_PushGlobPar(NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId);
extern  VOS_VOID    NAS_LMM_FSM_PopStackCombine( NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId);
extern  VOS_VOID    NAS_LMM_FSM_PopState(    NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId );
extern  VOS_VOID    NAS_LMM_FSM_PopTimer(    NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId);
extern  VOS_VOID    NAS_LMM_FSM_PopGlobPar(VOS_VOID);
extern  VOS_UINT32  NAS_LMM_FSM_GetStaAtStackBase(NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId);
extern  VOS_UINT32  NAS_LMM_FSM_GetStaAtStackTop(
                                        NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId);
extern  VOS_VOID    NAS_LMM_PrintFsmTimer(NAS_LMM_PARALLEL_FSM_ENUM_UINT16         enParallelFsmId);
extern  VOS_VOID    NAS_LMM_FSM_ClearStackCombine( NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId);

extern  VOS_VOID    NAS_LMM_FSM_ClearState( NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId );
extern  VOS_VOID    NAS_LMM_FSM_ClearTimer(  NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId);
extern  VOS_VOID    NAS_LMM_FSM_ClearGlobPar(VOS_VOID);
extern  VOS_VOID    NAS_LMM_FSM_ClearStackResource(VOS_VOID);
/*****************************************************************************
  9 OTHERS
*****************************************************************************/

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasLmmPubMStack.h*/
