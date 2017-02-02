

#ifndef __NASLMMTEST_H__
#define __NASLMMTEST_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "NasLmmPubMEntry.h"
#include  "NasEmmPubUGlobal.h"

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
extern VOS_VOID  NAS_LMM_CmdHelp( VOS_VOID );
extern VOS_VOID NAS_LMM_ShowAuxFsm(VOS_VOID);
extern VOS_VOID  NAS_LMM_ShowCommInfo(VOS_VOID);
extern VOS_VOID NAS_LMM_ShowConnInfo( VOS_VOID );
extern VOS_VOID NAS_LMM_ShowEmmFsmInfo(VOS_VOID);
extern VOS_VOID NAS_LMM_ShowForbidTalistInfo( APP_TA_LIST_STRU const *pstFtalist );
extern VOS_VOID NAS_LMM_ShowFsmstate
       (
           NAS_LMM_PARALLEL_FSM_ENUM_UINT16         enParallelFsmId
       );
extern VOS_VOID NAS_LMM_ShowGutiInfo( APP_GUTI_STRU const *pstGutiInfo );
extern VOS_VOID NAS_LMM_ShowImei( VOS_VOID );
extern VOS_VOID NAS_LMM_ShowImeisv(VOS_VOID);
extern VOS_VOID NAS_LMM_ShowImsi(VOS_VOID);
extern VOS_VOID NAS_LMM_ShowLastTaInfo( APP_TA_STRU const *pstLastTa );
extern VOS_VOID NAS_LMM_ShowMobilityInfo(VOS_VOID );
extern VOS_VOID NAS_LMM_ShowPlmn(VOS_UINT8 const *pucPlmnId);
extern VOS_VOID NAS_LMM_ShowPlmnInfo( VOS_VOID );
extern VOS_VOID NAS_LMM_ShowServStateInfo( VOS_VOID );
extern VOS_VOID NAS_LMM_ShowTac(VOS_UINT8 ucTac,VOS_UINT8 ucTacCnt);
extern VOS_VOID NAS_LMM_ShowTailistInfo( APP_TA_LIST_STRU const *pstTaiList );
extern VOS_VOID NAS_LMM_ShowTmsiInfo( VOS_VOID );
extern VOS_VOID NAS_LMM_ShowSysInfoCount( VOS_VOID );
extern VOS_VOID NAS_LMM_DebugInit(VOS_VOID);

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

#endif /* end of NasLmmTest.h */
