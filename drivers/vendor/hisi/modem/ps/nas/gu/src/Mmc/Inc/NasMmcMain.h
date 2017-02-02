/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMmcMain.h
  �� �� ��   : ����
  ��    ��   : zhoujun /40661
  ��������   : 2011��3��30��
  ����޸�   :
  ��������   : NasMain.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��3��30��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef _NAS_MMC_MAIN_
#define _NAS_MMC_MAIN_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "Nas_Mem.h"

#include "NasMmcCtx.h"
#include "NasMmcSndInternalMsg.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

VOS_VOID NAS_MMC_InitTask( VOS_VOID );

VOS_UINT32 NAS_MMC_InitPid(
    enum VOS_INIT_PHASE_DEFINE          ip
);

VOS_UINT32 NAS_MMC_ProcessMsgInFsm(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pMsg
);

VOS_UINT32 NAS_MMC_PreProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pMsg
);


VOS_VOID NAS_MMC_RegMainL1Fsm( VOS_VOID  );


VOS_VOID NAS_MMC_RegL2Fsm( VOS_VOID  );


VOS_VOID NAS_MMC_RegPreFsm( VOS_VOID  );

VOS_UINT32 NAS_MMC_FSM_ProcessEvent(
    VOS_UINT32                          ulCurState,
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pRcvMsg
);

VOS_VOID  NAS_MMC_InitCtx(
    NAS_MMC_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    NAS_MMC_CONTEXT_STRU                *pstMmcCtx
);

VOS_VOID NAS_MMC_RestoreFsmStack(
    NAS_MMC_CONTEXT_STRU               *pstPcMmcCtx
);

VOS_VOID NAS_MMC_ReloadFsmDesc(
    NAS_MMC_FSM_CTX_STRU               *pstFsmCtx,
    VOS_UINT32                          ulPcRecurFsmId
);


VOS_UINT32  NAS_MMC_ProcMsgPrio(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID  NAS_MMC_MsgProc(
    struct MsgCB                       *pstMsg
);

VOS_VOID  NAS_MMC_RegFsm( VOS_VOID );

VOS_UINT32  NAS_MMC_IsNeedCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
);


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasMmcMain.h */
