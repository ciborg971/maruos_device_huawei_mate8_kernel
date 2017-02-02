

#ifndef __TAF_APS_FSM_DEACTIVATING_TBL_H__
#define __TAF_APS_FSM_DEACTIVATING_TBL_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "TafFsm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
extern TAF_STA_STRU                             g_astTafApsMsDeactivatingStaTbl[];
#define TAF_APS_GetMsDeactivatingStaTbl()       (g_astTafApsMsDeactivatingStaTbl)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum TAF_APS_MS_DEACTIVATING_SUBSTA_ENUM
{
    TAF_APS_MS_DEACTIVATING_SUBSTA_INIT,                                        /* MS DEACTIVATING״̬���ĳ�ʼ״̬ */
    TAF_APS_MS_DEACTIVATING_SUBSTA_SUSPEND,                                     /* MS DEACTIVATING״̬���Ĺ���״̬ */
    TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF,                      /* APS��SM������PDPȥ�������󣬵ȴ�SM��Ӧ */
    TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF_SUSPEND,              /* APS��SM������PDPȥ�������󣬵ȴ�SM��Ӧʱ������ */
    TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF,                   /* APS��SNDCP����ȥ����SNDCP���󣬵ȴ�SNDCP��Ӧ */
    TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF_SUSPEND,           /* APS��SNDCP����ȥ����SNDCP���󣬵ȴ�SNDCP��Ӧʱ������ */
#if (FEATURE_ON == FEATURE_LTE)
    TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_L4A_DEACTIVATE_CNF,                     /* APS��L4A������PDP�������󣬵ȴ�L4A��Ӧ */
    TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_L4A_DEACTIVATE_CNF_SUSPEND,             /* APS��ESM������PDPȥ�������󣬵ȴ�ESM��Ӧʱ���� */
#endif
    TAF_APS_MS_DEACTIVATING_SUBSTA_BUTT
} ;
typedef VOS_UINT32 TAF_APS_MS_DEACTIVATING_SUBSTA_ENUM_UINT32;




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
VOS_UINT32 TAF_APS_GetMsDeactivatingStaTblSize( VOS_VOID );
TAF_FSM_DESC_STRU * TAF_APS_GetMsDeactivatingFsmDescAddr( VOS_VOID );









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

#endif /* end of TafApsFsmDeactivating.h */
