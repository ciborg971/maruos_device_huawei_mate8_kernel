
#ifndef _NAS_RABM_MSG_PROC_H_
#define _NAS_RABM_MSG_PROC_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define NAS_RABM_GetWProFuncTblAddr()               (&g_stNasRabmWProcFuncTbl)
#define NAS_RABM_GetGProFuncTblAddr()               (&g_stNasRabmGProcFuncTbl)
#if (FEATURE_ON == FEATURE_LTE)
#define NAS_RABM_GetLProFuncTblAddr()               (&g_stNasRabmLProcFuncTbl)
#endif

#define NAS_RABM_GetDataSuspendFlg()                (g_bNasRabmDataSuspendFlg)
#define NAS_RABM_SetDataSuspendFlg()                (g_bNasRabmDataSuspendFlg = VOS_TRUE)
#define NAS_RABM_ClearDataSuspendFlg()              (g_bNasRabmDataSuspendFlg = VOS_FALSE)

#define NAS_RABM_GetSysModeChgTblSize()             ((sizeof(g_astRabmSysModeChgTbl) / sizeof(NAS_RABM_SYS_CHG_TBL_STRU)))
#define NAS_RABM_GetSysModeChgTblAddr(ulIndex)      (&g_astRabmSysModeChgTbl[ulIndex])
#define NAS_RABM_GetSysModeChgTblOldMode(ulIndex)   (NAS_RABM_GetSysModeChgTblAddr(ulIndex)->enOldMode)
#define NAS_RABM_GetSysModeChgTblNewMode(ulIndex)   (NAS_RABM_GetSysModeChgTblAddr(ulIndex)->enNewMode)
#define NAS_RABM_GetSysModeChgTblProcFunc(ulIndex)  (NAS_RABM_GetSysModeChgTblAddr(ulIndex)->pSysModeChgProcFunc)

#define NAS_RABM_GetGPsEntAddr(ucEntId)             (&gastRabm2GEntity[ucEntId])
#define NAS_RABM_GetGPsEntState(ucEntId)            (NAS_RABM_GetGPsEntAddr(ucEntId)->State)

#define NAS_RABM_GetWPsEntAddr(ucEntId)             (&g_aRabmPsEnt[ucEntId])
#define NAS_RABM_GetWPsEntState(ucEntId)            (NAS_RABM_GetWPsEntAddr(ucEntId)->ucState)
#define NAS_RABM_GetWPsEntDlData(ucEntId)           (NAS_RABM_GetWPsEntAddr(ucEntId)->DlDataSave)
#define NAS_RABM_GetWPsEntUlData(ucEntId)           (NAS_RABM_GetWPsEntAddr(ucEntId)->UlDataSave)
#define NAS_RABM_GetWPsEntRabReestFlg(ucEntId)      (NAS_RABM_GetWPsEntAddr(ucEntId)->ucReEstFlg)
#define NAS_RABM_SetWPsEntRabReestFlg(ucEntId)      (NAS_RABM_GetWPsEntAddr(ucEntId)->ucReEstFlg = VOS_TRUE)
#define NAS_RABM_ClearWPsEntRabReestFlg(ucEntId)    (NAS_RABM_GetWPsEntAddr(ucEntId)->ucReEstFlg = VOS_FALSE)

#define NAS_RABM_GetCsEntAddr(ucEntId)              (&g_aRabmCsEnt[ucEntId])

#define NAS_RABM_GetRabRsestTimerFlg()              (g_ucReestTimerFlg)
#define NAS_RABM_SetRabRsestTimerFlg()              (g_ucReestTimerFlg = VOS_TRUE)
#define NAS_RABM_ClearRabRsestTimerFlg()            (g_ucReestTimerFlg = VOS_FALSE)

#define NAS_RABM_GetRauT1Flg()                      (gRabmRAT1Switch)
#define NAS_RABM_SetRauT1Flg()                      (gRabmRAT1Switch = RABM_ROUTING_AREA_UPDATE_T1_ON)
#define NAS_RABM_ClearRauT1Flg()                    (gRabmRAT1Switch = RABM_ROUTING_AREA_UPDATE_T1_OFF)

#define NAS_RABM_GetW2GT3Flg()                      (gRabm3GTo2GT3Switch)
#define NAS_RABM_SetW2GT3Flg()                      (gRabm3GTo2GT3Switch = RABM_3G_TO_2G_T3_ON)
#define NAS_RABM_ClearW2GT3Flg()                    (gRabm3GTo2GT3Switch = RABM_3G_TO_2G_T3_OFF)

#define NAS_RABM_ClearSiMapEnt()                    PS_MEM_SET(g_aucSiMapEnt, (VOS_CHAR)0xFF, sizeof(g_aucSiMapEnt))

#define NAS_RABM_GetG2WDataResumeFlg()              (gRabm2GTo3GDataResume)
#define NAS_RABM_ClearG2WDataResumeFlg()            (gRabm2GTo3GDataResume = VOS_FALSE)

#if (FEATURE_ON == FEATURE_LTE)
#define NAS_RABM_GetL2GFlg()                        (g_ulNasRabmL2GFlg)
#define NAS_RABM_SetL2GFlg()                        (g_ulNasRabmL2GFlg = VOS_TRUE)
#define NAS_RABM_ClearL2GFlg()                      (g_ulNasRabmL2GFlg = VOS_FALSE)
#endif

#define NAS_RABM_GET_RAB_PENDING_TMR_LEN()          (g_ulNasRabmRabPendingTmrLen)
#define NAS_RABM_SET_RAB_PENDING_TMR_LEN(ulTmrLen)  (g_ulNasRabmRabPendingTmrLen = (ulTmrLen))


/*****************************************************************************
  3 ö�ٶ���
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

/*****************************************************************************
 �� �� ��  : NAS_RABM_ProcSysModeChgInd
 ��������  : WCDMAϵͳģʽ����ϵͳģʽ�ı�ָʾ
 �������  : enOldSysMode   - RABM�ɵ�ϵͳģʽ
             enNewSysMode   - RABM�µ�ϵͳģʽ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_ProcSysModeChgInd(
    GMM_RABM_NET_RAT_ENUM_UINT32        enOldSysMode,
    GMM_RABM_NET_RAT_ENUM_UINT32        enNewSysMode
);


/*****************************************************************************
 �� �� ��  : NAS_RABM_WProcSysModeChgToGprs
 ��������  : ����Wģ�л���Gģ��RABMʵ��״̬ת��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_WProcSysModeChangeToGprs(VOS_VOID);


/*****************************************************************************
 �� �� ��  : NAS_RABM_WProcSysModeChgToLte
 ��������  : ����Wģ�л���Lģ��RABMʵ��״̬ת��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_WProcSysModeChangeToLte(VOS_VOID);


/*****************************************************************************
 �� �� ��  : NAS_RABM_WProcDataSuspendInd
 ��������  : WCDMAϵͳģʽ�´������ָʾ
 �������  : bRatChangeFlg  - ��ϵͳ�л���־
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_WProcDataSuspendInd(
    VOS_BOOL                            bRatChangeFlg
);


VOS_VOID NAS_RABM_WProcDataResumeInd(
    VOS_UINT8                           ucRebuildRabFlag
);


/*****************************************************************************
 �� �� ��  : NAS_RABM_GProcSysModeChgToWcdma
 ��������  : ����Gģ�л���Wģ��RABMʵ��״̬ת��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_GProcSysModeChangeToWcdma(VOS_VOID);


/*****************************************************************************
 �� �� ��  : NAS_RABM_GProcSysModeChgToLte
 ��������  : ����Gģ�л���Lģ��RABMʵ��״̬ת��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_GProcSysModeChangeToLte(VOS_VOID);


/*****************************************************************************
 �� �� ��  : NAS_RABM_GProcDataSuspendInd
 ��������  : GPRSϵͳģʽ�´������ָʾ
 �������  : bRatChangeFlg  - ��ϵͳ�л���־
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_GProcDataSuspendInd(
    VOS_BOOL                            bRatChangeFlg
);



VOS_VOID NAS_RABM_GProcDataResumeInd(
    VOS_UINT8                           ucRebuildRabFlag
);


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_RABM_LProcSysModeChgToGprs
 ��������  : ����Wģ�л���Gģ��RABMʵ��״̬ת��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_LProcSysModeChangeToWcdma(VOS_VOID);


/*****************************************************************************
 �� �� ��  : NAS_RABM_LProcSysModeChgToLte
 ��������  :
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_LProcSysModeChangeToGprs(VOS_VOID);


/*****************************************************************************
 �� �� ��  : NAS_RABM_LProcDataSuspendInd
 ��������  : LTEϵͳģʽ�´������ָʾ
 �������  : bRatChangeFlg  - ��ϵͳ�л���־
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_LProcDataSuspendInd(
    VOS_BOOL                            bRatChangeFlg
);



VOS_VOID NAS_RABM_LProcDataResumeInd(
    VOS_UINT8                           ucRebuildRabFlag
);



/*****************************************************************************
 �� �� ��  : NAS_RABM_LProcCommMsg
 ��������  : LTEģʽ�´���WRR����Ϣ
 �������  : struct MsgCB                       *pMsg
 �������  : VOS_VOID
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_LProcCommMsg(
    struct MsgCB                       *pMsg
);

#endif


/*****************************************************************************
 �� �� ��  : NAS_RABM_InitWProcFuncTbl
 ��������  : ��ʼ��WCDMA�������б�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_InitWProcFuncTbl(VOS_VOID);


/*****************************************************************************
 �� �� ��  : NAS_RABM_InitGProcFuncTbl
 ��������  : ��ʼ��GPRS�������б�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_InitGProcFuncTbl(VOS_VOID);


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_RABM_InitLProcFuncTbl
 ��������  : ��ʼ��LTE�������б�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_InitLProcFuncTbl(VOS_VOID);
#endif


VOS_VOID NAS_RABM_InitProcFuncTbl(VOS_VOID);


/*****************************************************************************
 �� �� ��  : NAS_RABM_ClearRabInfo
 ��������  : ���ָ��ʵ��ID��WģRAB��Ϣ
 �������  : ucEntId    - ʵ��ID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_ClearRabInfo(
    VOS_UINT8                           ucEntId
);


/*****************************************************************************
 �� �� ��  : NAS_RABM_ClearRabmWPsEnt
 ��������  : ���ָ��ʵ��ID��WģPS��ʵ����Ϣ
 �������  : VOS_UINT8                           ucEntId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_ClearRabmWPsEnt(
    VOS_UINT8                           ucEntId
);


/*****************************************************************************
 �� �� ��  : NAS_RABM_ClearRabmGPsEnt
 ��������  : ���ָ��ʵ��ID��GģPS��ʵ����Ϣ
 �������  : VOS_UINT8                           ucEntId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_ClearRabmGPsEnt(
    VOS_UINT8                           ucEntId
);


/*****************************************************************************
 �� �� ��  : NAS_RABM_ClearRabmCsEnt
 ��������  : ���ָ��CS��ʵ����Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_ClearRabmCsEnt(VOS_VOID);


/*****************************************************************************
 �� �� ��  : NAS_RABM_ClearRabReestFlg
 ��������  : ֹͣRAB�ؽ���ʱ��, ���RAB�ؽ���־
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_ClearRabReestFlg(VOS_VOID);


/*****************************************************************************
 �� �� ��  : NAS_RABM_StopGprsRaT1Timer
 ��������  : ֹͣrout.area.update.T1��ʱ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_StopGprsRaT1Timer(VOS_VOID);


/*****************************************************************************
 �� �� ��  : NAS_RABM_Stop3GTo2GT3Timer
 ��������  : �ر�Rabm.sys.3To2.T3��ʱ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_Stop3GTo2GT3Timer(VOS_VOID);


/*****************************************************************************
 �� �� ��  : NAS_RABM_UpdateWPsEntFromGPsEnt
 ��������  : PS��ʵ����Ϣת��, G->W
 �������  : VOS_UINT8                           ucEntId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_UpdateWPsEntFromGPsEnt(
    VOS_UINT8                           ucEntId
);


/*****************************************************************************
 �� �� ��  : NAS_RABM_UpdateGPsEntFromWPsEnt
 ��������  : PS��ʵ����Ϣת��, W->G
 �������  : VOS_UINT8                           ucEntId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_UpdateGPsEntFromWPsEnt(
    VOS_UINT8                           ucEntId
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

#endif

