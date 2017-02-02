

#ifndef __TEST_ATPARSECMD_H__
#define __TEST_ATPARSECMD_H__

/*****************************************************************************
  1 ����ͷ�ļ�����                            
*****************************************************************************/
#include "ATCmdProc.h"
#include "AtCheckFunc.h"
#include "AtParseCmd.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨�� 
*****************************************************************************/
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

extern VOS_UINT32 atAuc2ul(IN VOS_UINT8 *nptr,VOS_UINT16 usLen,OUT VOS_UINT32 *pRtn);
extern AT_STATE_TYPE_ENUM atFindNextMainState(IN AT_MAIN_STATE_STRU *pMainStateTab,
           VOS_UINT8 ucInputChar, IN AT_STATE_TYPE_ENUM InputState);
extern AT_STATE_TYPE_ENUM atFindNextSubState(IN AT_SUB_STATE_STRU *pSubStateTab,VOS_UINT8 ucInputChar);
extern VOS_VOID atRangeCopy(OUT VOS_UINT8 *pucDst,IN VOS_UINT8 * pucBegain,IN VOS_UINT8 * pucEnd);
extern VOS_UINT32 atRangeToU32(IN VOS_UINT8 *pucBegain,IN VOS_UINT8 *pucEnd);
extern TAF_UINT32 At_Auc2ul(TAF_UINT8 *nptr,TAF_UINT16 usLen,TAF_UINT32 *pRtn);
extern TAF_VOID At_RangeCopy(TAF_UINT8 *pucDst,TAF_UINT8 * pucBegain, TAF_UINT8 * pucEnd);
extern TAF_UINT32 At_RangeToU32(TAF_UINT8 * pucBegain, TAF_UINT8 * pucEnd);
extern TAF_UINT32 At_String2Hex(TAF_UINT8 *nptr,TAF_UINT16 usLen,TAF_UINT32 *pRtn);
extern TAF_UINT32 At_UpString(TAF_UINT8 *pData,TAF_UINT16 usLen);
extern PRIVATE VOS_UINT32 auc2ulDec(IN VOS_UINT8 *nptr, VOS_UINT16 usLen, OUT VOS_UINT32 *pRtn);
extern PRIVATE VOS_UINT32 auc2ulHex(IN VOS_UINT8 *nptr, VOS_UINT16 usLen, OUT VOS_UINT32 *pRtn);
extern PRIVATE VOS_UINT32 auc2ulOct(IN VOS_UINT8 *nptr, VOS_UINT16 usLen, OUT VOS_UINT32 *pRtn);


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

#endif /* end of Test_AtParseCmd.h */
