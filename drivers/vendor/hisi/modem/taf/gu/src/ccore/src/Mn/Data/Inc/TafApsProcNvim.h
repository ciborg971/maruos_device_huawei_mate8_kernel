

#ifndef __TAFAPSPROCNVIM_H__
#define __TAFAPSPROCNVIM_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "TafApsCtx.h"


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

VOS_VOID  TAF_APS_ReadDsFlowInfoFromNv(
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsFlowCtx
);
VOS_VOID  TAF_APS_ClearDsFlowInfoInNv( VOS_VOID );
VOS_VOID  TAF_APS_SaveDsFlowInfoToNv( VOS_VOID );

VOS_VOID TAF_APS_ReadPdpActLimitFlgFromNv(VOS_VOID);

VOS_VOID TAF_APS_ReadDsflowRateConfigFromNv(TAF_APS_SWITCH_DDR_RATE_INFO_STRU *pstSwitchDdrInfo);

VOS_VOID TAF_APS_Recorrect_ProfileNum(
    TAF_NV_DFS_DSFLOW_RATE_CONFIG_STRU     *pstDfsProfile,
    VOS_UINT32                              ulProfileNum);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_APS_Read1xPktDataInactivityTimeLenFromNv(VOS_VOID);

/* Added by y00314741 for  CDMA Iteration 17, 2015-7-15, begin */
VOS_VOID TAF_APS_ReadEvdoPktDataInactivityTimeLenFromNv(VOS_VOID);
/* Added by y00314741 for  CDMA Iteration 17, 2015-7-15, end */
VOS_VOID TAF_APS_Read1xDataSoCfgNvim(VOS_VOID);
#endif

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID TAF_APS_ReadPdnTeardownPolicyNV(VOS_VOID);
#endif



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

#endif /* end of TafApsProcNvim.h */
