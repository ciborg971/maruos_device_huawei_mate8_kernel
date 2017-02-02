

#ifndef __TEST_ATEXTENDPRIVATECMD_H__
#define __TEST_ATEXTENDPRIVATECMD_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "AtParse.h"
#include "ATCmdProc.h"
//#include "Taf_Tafm_Remote.h"
#include "AtInputProc.h"

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

extern VOS_UINT32 AT_GetPortInfoIndex(VOS_UINT8   ucPortType, VOS_UINT8 *pucIndex);
extern VOS_UINT32 AT_QryDloadVerPara( VOS_UINT8 ucIndex );
extern VOS_UINT32 At_RegisterExPrivateCmdTable(VOS_VOID);
extern VOS_UINT32  AT_SetDissdCmd(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetSdrebootCmd(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestApRptPortSelectPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_TestCgauthPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestChdataPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_TestCmlckPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestCpnnPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestGpioPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestImsichgPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestIpv6capPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestOplPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestPnnPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestRsfrPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestRsfwPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestRstriggerPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestSetPort(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestStgiPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestStgrPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestStsfPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestSyscfg(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestSyscfgEx(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestUsbSwitchPara(VOS_UINT8 ucIndex);
extern VOS_VOID  AT_InitPort(VOS_VOID);
extern VOS_VOID Test_AT_InitMuxClientTab(VOS_VOID);

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

#endif /* end of Test_AtExtendPrivateCmd.h */
