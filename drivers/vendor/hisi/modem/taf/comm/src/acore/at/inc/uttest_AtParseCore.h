

#ifndef __TEST_ATPARSECORE_H__
#define __TEST_ATPARSECORE_H__

/*****************************************************************************
  1 ����ͷ�ļ�����                            
*****************************************************************************/
#include "AtCheckFunc.h"
#include "ATCmdProc.h"
#include "AtCmdMsgProc.h"
#include "at_common.h"
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
#define    THIS_FILE_ID        PS_FILE_ID_AT_PARSECORE_C

#define PRIVATE
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
extern HI_LIST_S g_stCmdTblList;
extern AT_RESET_CTX_STRU                       g_stAtResetCtx;
extern AT_CMGF_MSG_FORMAT_ENUM_U8              g_enAtCmgfMsgFormat;
extern AT_PAR_CMD_ELEMENT_STRU g_stCmdElement[AT_MAX_CLIENT_NUM];
extern VOS_VOID   At_MsgProc(MsgBlock* pMsg);
extern VOS_UINT32 At_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase);
extern VOS_UINT32 AT_CheckHsUartUser(VOS_UINT8 ucIndex);
extern AT_RRETURN_CODE_ENUM atCmdDispatch (VOS_UINT8 ucIndex);
extern PRIVATE VOS_VOID atCmdMsgProc(VOS_UINT8 ucIndex, VOS_UINT8 *pData, VOS_UINT16 usLen);
extern VOS_UINT32 atfwParseSaveParam(VOS_UINT8* pStringBuf, VOS_UINT16 usLen);
extern VOS_UINT32 atFWSendMsg(VOS_UINT32 TaskId, IN VOS_VOID* pData, VOS_UINT32 uLen);
extern PRIVATE VOS_UINT32 atMatchCmdName (VOS_UINT8 ucClientId, VOS_UINT32 CmdType);
extern PRIVATE VOS_UINT8 AT_BlockCmdCheck(VOS_VOID);
extern PRIVATE VOS_UINT8 AT_BlockCmdProc(VOS_VOID);
extern VOS_VOID AT_BlockCmdTimeOutProc(VOS_UINT8 ucIndex);
extern VOS_VOID AT_CheckProcBlockCmd(VOS_VOID);
extern VOS_VOID AT_ClacCmdProc(VOS_VOID);
extern PRIVATE VOS_VOID AT_ClearBlockCmdInfo(VOS_UINT8 ucIndex);
extern VOS_VOID At_CmdMsgDistr(AT_MSG_STRU *pstMsg);
extern VOS_UINT32 At_CmdStreamRcv(VOS_UINT8 ucIndex, VOS_UINT8* pData, VOS_UINT16 usLen);
extern VOS_UINT32 At_CmdTestProcERROR(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_CmdTestProcOK(VOS_UINT8 ucIndex);
extern VOS_VOID At_CombineBlockCmdProc(VOS_UINT8 ucIndex);
extern VOS_UINT32  AT_DiscardInvalidChar(VOS_UINT8* pucData, VOS_UINT16 *pusLen);
extern VOS_VOID AT_DiscardInvalidCharForSms(TAF_UINT8* pData, TAF_UINT16 *pusLen);
extern VOS_UINT32 AT_FwSendClientMsg(VOS_UINT32 ulRcvPid, VOS_UINT32 ulMsgId, VOS_UINT16 usMsgParamSize, IN VOS_VOID *pMsgParam);
extern PRIVATE VOS_VOID AT_HoldBlockCmd(VOS_UINT8 ucIndex, VOS_UINT8 *pData, VOS_UINT16 usLen);
extern PRIVATE VOS_UINT32 At_MatchSmsCmdName(VOS_UINT8 ucIndex, VOS_CHAR *pszCmdName);
extern PRIVATE VOS_UINT32 AT_ParseCmdIsComb(VOS_UINT8 ucIndex, VOS_UINT8 *pData, VOS_UINT16 usLen);
extern PRIVATE VOS_UINT32 AT_ParseCmdIsPend(VOS_UINT8 ucIndex, VOS_UINT8 *pData, VOS_UINT16 usLen);
extern VOS_VOID AT_ParseCmdOver(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_ParseCmdType(IN VOS_UINT8 * pData, VOS_UINT16 usLen);
extern VOS_VOID At_ParseInit(VOS_VOID);
extern PRIVATE VOS_VOID AT_PendClientProc(VOS_UINT8 ucIndex, VOS_UINT8 *pData, VOS_UINT16 usLen);
extern VOS_VOID At_ReadyClientCmdProc(VOS_UINT8 ucIndex, VOS_UINT8 *pData, VOS_UINT16 usLen);
extern VOS_UINT32 AT_RegisterCmdTable(CONST_T AT_PAR_CMD_ELEMENT_STRU* pstCmdTblEntry, VOS_UINT16 usCmdNum);
extern PRIVATE VOS_VOID AT_ResetParseVariable();
extern VOS_UINT32 CmdParseProc(VOS_UINT8 ucClientId, VOS_UINT8 *pData, VOS_UINT16 usLen);
extern PRIVATE VOS_UINT32 CmdStringFormat(VOS_UINT8 ucClientId, VOS_UINT8 *pData,VOS_UINT16* pusLen);
extern PRIVATE VOS_BOOL DelCharIsPbCmd(VOS_UINT8 *pData, VOS_UINT16 usLen);
extern PRIVATE VOS_UINT32 FormatCmdStr (VOS_UINT8 *pData, VOS_UINT16 *pLen, VOS_UINT8 AtS3);
extern PRIVATE AT_RRETURN_CODE_ENUM fwCmdTestProc(VOS_UINT8 ucIndex, AT_PAR_CMD_ELEMENT_STRU* pstCmdElement);
extern PRIVATE VOS_UINT32 LimitedCmdProc(VOS_UINT8 ucClientId, VOS_UINT8 *pData, VOS_UINT16 usLen, AT_PAR_CMD_ELEMENT_STRU* pstCmdElement);
extern PRIVATE VOS_UINT32 ParseParam(AT_PAR_CMD_ELEMENT_STRU* pstCmdElement);
extern PRIVATE VOS_VOID RepeatCmdProc(AT_PARSE_CONTEXT_STRU* pstClientContext);
extern PRIVATE VOS_VOID SaveRepeatCmd(AT_PARSE_CONTEXT_STRU* pstClientContext, VOS_UINT8 *pData, VOS_UINT16 usLen);
extern PRIVATE VOS_UINT32 ScanBlankChar(IN OUT VOS_UINT8 *pData,IN OUT VOS_UINT16 *pLen);
extern PRIVATE VOS_UINT32 ScanCtlChar(IN OUT VOS_UINT8 *pData,IN OUT VOS_UINT16 *pLen);
extern PRIVATE VOS_UINT32 ScanDelChar(IN OUT VOS_UINT8 *pData,IN OUT VOS_UINT16 *pLen, VOS_UINT8 AtS5);

extern AT_PAR_CMD_ELEMENT_STRU* AT_GetCmdElementInfo(
    VOS_UINT8                          *pucCmdName,
    VOS_UINT32                          ulCmdType
);

extern TAF_UINT32 At_MatchCmdName (TAF_UINT16 ucIndex,TAF_UINT32 CmdType);

extern VOS_UINT32 AT_IsApPort(VOS_UINT8 ucIndex);

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

#endif /* end of AtParseCore.h */
