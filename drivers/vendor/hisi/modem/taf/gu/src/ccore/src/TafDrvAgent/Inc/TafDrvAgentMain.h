

#ifndef __DRVAGENTMAIN_H__
#define __DRVAGENTMAIN_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "TafDrvAgent.h"
#include  "TafDrvAgentMsgProc.h"
#include  "PsCommonDef.h"
#include  "MnComm.h"
#include  "ScInterface.h"


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
extern VOS_UINT16  *g_pusDrvAgentUsimTempTable;         /*SIM hkadcת����*/
extern VOS_UINT16  *g_pusDrvAgentBatTempTable;          /*Battery hkadcת����*/
extern VOS_UINT16  *g_pusDrvAgentAdcTable;              /*PA hkadcת����*/

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/*��Ϣ������ָ��*/
typedef VOS_UINT32 (*DRV_AGENT_MSG_PROC_FUNC)(VOS_VOID* pMsg);
typedef struct
{
    DRV_AGENT_MSG_TYPE_ENUM_UINT32      ulMsgType;
    DRV_AGENT_MSG_PROC_FUNC             pMsgProcFunc;
}DRV_AGENT_MSG_PROC_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_UINT32  DRVAGENT_Init(enum VOS_INIT_PHASE_DEFINE  ip);

VOS_VOID  DRVAGENT_DispatchMsg (struct MsgCB * pstMsg);

VOS_VOID DRVAGENT_ProcMsgFromAt(VOS_VOID *pMsg);

VOS_VOID DRVAGENT_ProcMsgFromSPY(VOS_VOID *pMsg);

VOS_VOID DRVAGENT_SendMsg(
    VOS_UINT32                          ulRcvPid,
    VOS_UINT32                          ulMsgId,
    VOS_UINT32                          ulLen,
    VOS_UINT8                          *pData
);
VOS_UINT8* DRVAGENT_GetSystemAppConfigAddr(VOS_VOID);

VOS_UINT32 DRVAGENT_TempReadInit(VOS_VOID);

DRV_AGENT_PERSONALIZATION_ERR_ENUM_UINT32 DRVAGENT_ConvertScErr(
    SC_ERROR_CODE_ENUM_UINT32           enErrCode
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

#endif /* end of TafDrvAgentMain.h */
