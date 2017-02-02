

#ifndef __TEST_ATCOMBINECMD_H__
#define __TEST_ATCOMBINECMD_H__

/*****************************************************************************
  1 ����ͷ�ļ�����                            
*****************************************************************************/
#include "AtCheckFunc.h"

#include "ATCmdProc.h"

#include "TafTypeDef.h"
#include "hi_list.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨�� 
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_AT_COMBINEDCMD_C
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

extern PRIVATE VOS_UINT32 At_BasicCombineCmdParse(HI_LIST_S* pstCombList, VOS_UINT8 *pDataIn, VOS_UINT16 usLenIn);
extern VOS_UINT32 At_BasicExCombineCmdParse(HI_LIST_S* pstCombList, VOS_UINT8 *pDataIn, VOS_UINT16 usLenIn, VOS_UINT16 usFirIndex);
extern VOS_BOOL At_CombCmdisFinal(VOS_UINT8 ucIndex);
extern VOS_VOID At_CombCmdProcAfterCmd(VOS_UINT8 ucClientId);
extern VOS_UINT32 At_CombineCmdChkProc(VOS_UINT8 ucClientId, IN VOS_UINT8 *pDataIn, VOS_UINT16 usLenIn);
extern PRIVATE VOS_UINT32 At_CombineCmdPreProc(HI_LIST_S* pstCombList, VOS_UINT8 *pDataIn, VOS_UINT16 usLenIn);
extern VOS_UINT32 At_CombineCmdProc(VOS_UINT8 ucClientId);
extern VOS_UINT32 At_GetFirstCmdLen(IN VOS_UINT8 *pData, VOS_UINT16 usLen);
extern VOS_UINT32 At_GetSecondAddr(VOS_UINT8 *pData,VOS_UINT16 usLen, VOS_UINT8** ppDataOut);
extern VOS_VOID At_PrintCombinCmd(VOS_VOID);
extern VOS_VOID At_ResetCombinCmdInfo(HI_LIST_S* pstCombList);
extern VOS_VOID At_ResetCombinParseInfo(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_SemicolonCmdParse(HI_LIST_S* pstCombList, VOS_UINT8 *pDataIn, VOS_UINT16 usLenIn);
extern PRIVATE VOS_UINT32 At_StoreSubCombCmd(HI_LIST_S* pstCombList, VOS_UINT8 *pDataIn, VOS_UINT16 usLenIn);
extern PRIVATE VOS_VOID At_UpStringCmdName(VOS_UINT8 *pData, VOS_UINT16 usLen);

extern VOS_VOID At_FilterDCmdSpecCharacter(
    VOS_UINT32                  *pulParaLen,
    VOS_UINT8                   *pucPara
);

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

#endif /* end of Test_AtCombinecmd.h */
