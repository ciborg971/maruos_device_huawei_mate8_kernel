

#ifndef __TAFAPSMAIN_H__
#define __TAFAPSMAIN_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "Ps.h"
#include  "TafFsm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
extern TAF_STA_STRU                           g_astTafApsMainFsmStaTbl[];
#define TAF_APS_GetMainFsmStaTbl()            (g_astTafApsMainFsmStaTbl)


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
extern VOS_VOID  TAF_APS_InitTask( VOS_VOID );

extern VOS_UINT32 TAF_APS_ProcessMsgInFsm(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pMsg
);

extern VOS_UINT32 TAF_APS_PreProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pMsg
);


extern VOS_VOID TAF_APS_RegMainFsm( VOS_VOID  );


extern VOS_VOID TAF_APS_RegSubFsm( VOS_VOID  );


extern VOS_VOID TAF_APS_RegPreFsm( VOS_VOID  );

extern VOS_UINT32 TAF_APS_FSM_ProcessEvent(
    VOS_UINT32                          ulCurState,
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pRcvMsg,
    TAF_FSM_DESC_STRU                  *pstFsmDesc
);

extern VOS_VOID  TAF_APS_InitCtx( VOS_VOID );

extern VOS_VOID  TAF_APS_ProcMsg(
    struct MsgCB                       *pstMsg
);

extern VOS_VOID  TAF_APS_RegFsm( VOS_VOID );

extern VOS_VOID  TAF_APS_PostProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_APS_BuildEventType(
    struct MsgCB                       *pstMsg
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

#endif /* end of TafApsMain.h */
