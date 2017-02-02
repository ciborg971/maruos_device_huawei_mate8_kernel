/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : Test_AtExtendCmd.h
  �� �� ��   : ����
  ��    ��   : 
  ��������   : 2012��5��17��
  ����޸�   :
  ��������   : Test_AtExtendCmd.cpp ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��5��17��
    ��    ��   : 
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __TEST_ATEXTENDCMD_H__
#define __TEST_ATEXTENDCMD_H__

/*****************************************************************************
  1 ����ͷ�ļ�����                            
*****************************************************************************/
#include "AtParse.h"
#include "ATCmdProc.h"
#include "Taf_Tafm_Remote.h"



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

extern VOS_UINT32 At_RegisterExCmdTable(VOS_VOID);
extern VOS_UINT32 At_TestCcfcPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_TestCcwaPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_TestCgansPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_TestCgdataPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_TestCgdnsPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_TestCgeqnegPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_TestCgeqreqPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_TestClckPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestCnmaPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_TestCopsPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_TestCpasPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestCpbrPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestCpbsPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestCpmsPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_TestCpolPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_TestCpwdPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestCscbPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_TestCusdPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_TestCuus1Para(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_TestVtsPara(VOS_UINT8 ucIndex);



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

#endif /* end of Test_AtExtendCmd.h */
