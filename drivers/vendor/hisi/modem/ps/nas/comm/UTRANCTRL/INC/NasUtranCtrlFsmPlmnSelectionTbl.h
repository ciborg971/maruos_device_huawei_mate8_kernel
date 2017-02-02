
#ifndef _NAS_UTRANCTRL_FSM_PLMN_SELECTION_TBL_H_
#define _NAS_UTRANCTRL_FSM_PLMN_SELECTION_TBL_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#include  "vos.h"
#include  "PsTypeDef.h"
#include  "NasFsm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  1 ȫ�ֱ�������
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)

extern NAS_STA_STRU                            g_astNasUtranCtrlPlmnSelectionStaTbl[];


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define NAS_UTRANCTRL_GetPlmnSelectionStaTbl()                   (g_astNasUtranCtrlPlmnSelectionStaTbl)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


enum NAS_UTRANCTRL_PLMN_SELECTION_STA_ENUM
{
    NAS_UTRANCTRL_PLMN_SELECTION_STA_INIT,                                      /* ����״̬����ʼ��״̬ */

    NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF_SEARCH_TD,          /* ����״̬���ȴ�WASֹͣ�����ظ���ȥTD������״̬ */

    NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_PLMN_STOP_CNF_SEARCH_W,            /* ����״̬���ȴ�TDRRCֹͣ�����غ�ȥW��������״̬ */

    NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF,                      /* ����״̬���ȴ�WAS����ظ�״̬ */

    NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF,                    /* ����״̬���ȴ�TDRRC����ظ�״̬ */

    NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_SEARCH_CNF,                  /* ����״̬���ȴ�WAS�����ظ�״̬ */

    NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_PLMN_SEARCH_CNF,                /* ����״̬���ȴ�TDRRC�����ظ�״̬ */

    NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF,                    /* ����״̬���ȴ�WASֹͣ�����ظ�״̬ */

    NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_PLMN_STOP_CNF,                     /* ����״̬���ȴ�TDRRCֹͣ�����ظ�״̬ */

    NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_BACK_TD,              /* ����״̬���ȴ��ص�TDʱWAS�Ĺ���ظ�״̬ */

    NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF_BACK_W,                /* ����״̬���ȴ��ص�WʱTDRRC�Ĺ���ظ�״̬ */

    NAS_UTRANCTRL_PLMN_SELECTION_STA_BUTT
};
typedef VOS_UINT32  NAS_UTRANCTRL_PLMN_SELECTION_STA_ENUM_UINT32;

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

VOS_UINT32 NAS_UTRANCTRL_GetPlmnSelectionStaTblSize( VOS_VOID  );


NAS_FSM_DESC_STRU * NAS_UTRANCTRL_GetPlmnSelectionFsmDescAddr(VOS_VOID);
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

#endif /* end of NAS_UTRANCTRLMainFsmTbl.h */
