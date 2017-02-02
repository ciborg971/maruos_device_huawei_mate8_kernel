

#ifndef __TAFAPSFSMMSMODIFYINGTBL_H__
#define __TAFAPSFSMMSMODIFYINGTBL_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "TafFsm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
extern TAF_STA_STRU                             g_astTafApsMsModifyingStaTbl[];
#define TAF_APS_GetMsModifyingStaTbl()          (g_astTafApsMsModifyingStaTbl)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum TAF_APS_MS_MODIFYING_SUBSTA_ENUM
{
    TAF_APS_MS_MODIFYING_SUBSTA_INIT,                                           /* MS MODIFYIN״̬���ĳ�ʼ״̬ */
    TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND,                                        /* MS MODIFYIN״̬���Ĺ���״̬ */
    TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF,                             /* APS��SM������PDP�޸����󣬵ȴ�SM��Ӧ */
    TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND,                     /* APS��SM������PDP�޸����󣬵ȴ�SM��Ӧʱ������ */
    TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP,                          /* APS��SNDCP�����޸�SNDCPָʾ���ȴ�SNDCP��Ӧ */
    TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND,                  /* APS��SNDCP�����޸�SNDCPָʾ���ȴ�SNDCP��Ӧʱ������ */
#if (FEATURE_ON == FEATURE_LTE)
    TAF_APS_MS_MODIFYING_SUBSTA_WAIT_L4A_MODIFY_CNF,                            /* APS��L4A������PDP�޸����󣬵ȴ�L4A��Ӧ */
    TAF_APS_MS_MODIFYING_SUBSTA_WAIT_L4A_MODIFY_CNF_SUSPEND,                    /* APS��L4A������PDP�޸����󣬵ȴ�L4A��Ӧʱ������ */
#endif
    TAF_APS_MS_MODIFYING_SUBSTA_BUTT
} ;
typedef VOS_UINT32 TAF_APS_MS_MODIFYING_SUBSTA_ENUM_UINT32;


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
VOS_UINT32 TAF_APS_GetMsModifyingStaTblSize( VOS_VOID );
TAF_FSM_DESC_STRU * TAF_APS_GetMsModifyingFsmDescAddr( VOS_VOID );




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

#endif /* end of TafApsFsmMsModifying.h */
