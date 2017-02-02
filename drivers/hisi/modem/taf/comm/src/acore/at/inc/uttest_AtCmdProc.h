

#ifndef __TEST_ATCMDPROC_H__
#define __TEST_ATCMDPROC_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#include "ATCmdProc.h"
#include "AtCheckFunc.h"
#include "PppInterface.h"

#include "UsimPsInterface.h"
#include "Taf_MmiStrParse.h"
#include "AppVcApi.h"
#include "AtDataProc.h"
#include "MnMsgApi.h"
#include "AtCmdMsgProc.h"
#include "AtInputProc.h"
#include "AtTestParaCmd.h"

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
extern VOS_UINT32  At_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase);
extern TAF_VOID At_MsgProc(MsgBlock* pMsg);

extern VOS_UINT32 LimitedCmdProc(VOS_UINT8 ucClientId, VOS_UINT8 *pData, VOS_UINT16 usLen, AT_PAR_CMD_ELEMENT_STRU* pstCmdElement);

extern VOS_VOID At_InterTimerOutProc(
    VOS_UINT8 ucIndex
);
extern TAF_UINT32  At_SendPduMsgAck(
    TAF_UINT8                           ucIndex,
    TAF_UINT8                           *pData,
    TAF_UINT32                          ulLen
);

extern TAF_UINT32 At_SmsTextProc ( TAF_UINT8 ucIndex, TAF_UINT8 *pData, TAF_UINT16 usLen);
extern TAF_UINT32 At_SmsPduProc ( TAF_UINT8 ucIndex, TAF_UINT8 *pData, TAF_UINT16 usLen);

extern VOS_VOID  AT_InitPort(VOS_VOID);
extern VOID Test_AT_InitMuxClientTab(VOS_VOID);

extern void UT_STUB_INIT(void);



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

#endif /* end of Test_AtCmdProc.h */
