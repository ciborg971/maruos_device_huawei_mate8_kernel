

#ifndef __TEST_ATDEVICECMD_H__
#define __TEST_ATDEVICECMD_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "AtParse.h"
#include "ATCmdProc.h"
#include "AtDeviceCmd.h"
#include "AtCheckFunc.h"
#include "mdrv.h"
#include "AtCmdMsgProc.h"
#include "AtInputProc.h"
#include "phyoaminterface.h"

#if(FEATURE_ON == FEATURE_LTE)
#include "LNvCommon.h"
#include "msp_nvim.h"
#endif

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
#define    THIS_FILE_ID        PS_FILE_ID_AT_DEVICECMD_C


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

extern VOS_UINT32 AT_CheckSetPortRight(
           VOS_UINT8                           aucOldRewindPortStyle[],
           VOS_UINT8                           aucNewRewindPortStyle[]
       );
extern VOS_UINT32 AT_CloseDiagPort(VOS_VOID);
extern VOS_UINT32 AT_ExistSpecificPort(VOS_UINT8 ucPortType);
extern VOS_UINT32 AT_ExistSpecificPortChange(
           VOS_UINT8                           ucPortType,
           VOS_UINT8                           aucOldRewindPortStyle[],
           VOS_UINT8                           aucNewRewindPortStyle[]
       );
extern VOS_VOID AT_GetSpecificPort(
           VOS_UINT8                           ucPortType,
           VOS_UINT8                           aucRewindPortStyle[],
           VOS_UINT32                         *pulPortPos,
           VOS_UINT32                         *pulPortNum
       );
extern  VOS_VOID AT_GetTseLrfLoadDspInfo(
           AT_TSELRF_PATH_ENUM_UINT32          enPath,
           VOS_BOOL                           *pbLoadDsp,
           DRV_AGENT_TSELRF_SET_REQ_STRU      *pstTseLrf
       );
extern VOS_UINT32 AT_OpenDiagPort(VOS_VOID);
extern VOS_UINT32 AT_QryCmdlenPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryHsspt(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryTbatPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryTseLrfPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryWiwepPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_RegisterDeviceCmdTable(VOS_VOID);
extern VOS_UINT32 AT_SDParamErrCode();
extern VOS_UINT32 AT_SetCmdlenPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetExbandInfoPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetExbandTestInfoPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetHsspt(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetPstandbyPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetTbatPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetTmodeAutoPowerOff(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetTseLrfPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetWiwepPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_TestFdacPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestHsicCmdPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestSsidPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_TestTmodePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestWifiPaRangePara (VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestWikeyPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_TestWiwepPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_UpdateMacPara(
           VOS_UINT8                           aucMac[],
           VOS_UINT16                          usMacLength
       );
extern VOS_UINT32 AT_WriteWiWep(
           VOS_UINT32                          ulIndex,
           VOS_UINT8                           aucWiWep[],
           VOS_UINT16                          usWiWepLen,
           AT_WIFI_SEC_STRU                   *pstWifiSecInfo
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

#endif /* end of Test_AtDeviceCmd.h */
