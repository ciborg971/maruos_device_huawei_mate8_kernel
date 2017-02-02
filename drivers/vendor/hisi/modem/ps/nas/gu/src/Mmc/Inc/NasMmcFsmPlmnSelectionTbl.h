/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMmcFsmPLmnSelectionTbl.h
  �� �� ��   : ����
  ��    ��   : sunxibo /46746
  ��������   : 2011��07��04��
  ����޸�   :
  ��������   : NasMmcFsmPLmnSelectionTbl.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��07��04��
    ��    ��   : sunxibo /46746
    �޸�����   : Added for V7R1 phase II

******************************************************************************/
#ifndef _NAS_MMC_FSM_PLMN_SELECTION_TBL_H_
#define _NAS_MMC_FSM_PLMN_SELECTION_TBL_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#include  "vos.h"
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
extern NAS_STA_STRU                                         g_astNasMmcPlmnSelectionStaTbl[];

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define NAS_MMC_GetPlmnSelectionStaTbl()                    (g_astNasMmcPlmnSelectionStaTbl)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


enum NAS_MMC_PLMN_SELECTION_STA_ENUM
{
    /* �Զ�����״̬���ȴ���Ϣ״̬ */
    NAS_MMC_PLMN_SELECTION_STA_INIT                         =0,

    /*  �ȴ�Wģ�ϱ�������� */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_PLMN_SEARCH_CNF     =1,

    /*  �ȴ�Gģ�ϱ�������� */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_PLMN_SEARCH_CNF     =2,

    /*  �ȴ�Lģ�ϱ�������� */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF     =3,

    /*  �ȴ�Wģ�ϱ������� */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF         =4,

    /*  �ȴ�Gģ�ϱ������� */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SUSPEND_CNF         =5,

    /*  �ȴ�Lģ�ϱ������� */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SUSPEND_CNF         =6,

    /*  �ȴ�Wģ�ϱ�ֹͣ������� */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF       =7,

    /*  �ȴ�Gģ�ϱ�ֹͣ������� */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_PLMN_STOP_CNF       =8,

    /*  �ȴ�Lģ�ϱ�ֹͣ������� */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_STOP_CNF       =9,

    /*  �ȴ�Wģ�ϱ�ϵͳ��Ϣ*/
    NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SYSINFO_IND         =10,

    /*  �ȴ�Gģ�ϱ�ϵͳ��Ϣ*/
    NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SYSINFO_IND         =11,

    /*  �ȴ�Lģ�ϱ�ϵͳ��Ϣ*/
    NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SYSINFO_IND         =12,

    /*  �ȴ�CS+PS���ע����*/
    NAS_MMC_PLMN_SELECTION_STA_WAIT_CSPS_REG_IND            =13,

    /*  �ȴ�EPS���ע���� */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND             =14,

    /*  �ȴ�GU�����ͷ� */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_RRC_CONN_REL_IND        =15,

    /*  �ȴ�EPS��������ͷŽ�� */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND        =16,


    /*  CS/PS mode 1�ػ�Lģ�ȴ�Wģ�ϱ������� */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_CSPSMODE1_RECAMP_LTE        =17,

    /*  CS/PS mode 1�ػ�Lģ�ȴ�Gģ�ϱ������� */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SUSPEND_CNF_CSPSMODE1_RECAMP_LTE        =18,

    /*  CS/PS mode 1�ػ�Lģ�ȴ�Lģ�ϱ�������� */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF_CSPSMODE1_RECAMP_LTE    =19,

    /*  CS/PS mode 1�ػ�Lģ�ȴ�Lģ�ϱ�ֹͣ������� */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_STOP_CNF_CSPSMODE1_RECAMP_LTE      =20,

    /*  CS/PS mode 1�ػ�Lģ�ȴ�Lģ�ϱ�ϵͳ��Ϣ */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SYSINFO_IND_CSPSMODE1_RECAMP_LTE        =21,

    /*  CS/PS mode 1�ػ�Lģ�ȴ�EPS���ע���� */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND_CSPSMODE1_RECAMP_LTE            =22,

    /*  CS/PS mode 1�ػ�Lģ�ȴ�EPS�����ͷ� */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REL_IND_CSPSMODE1_RECAMP_LTE            =23,

    /*  �ȴ�MSCC��ע������ */
    NAS_MMC_PLMN_SELECTION_STA_WAIT_MSCC_REG_REQ                                 =24,

    NAS_MMC_PLMN_SELECTION_STA_BUTT
};
typedef VOS_UINT32  NAS_MMC_PLMN_SELECTION_STA_ENUM_U32;


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
VOS_UINT32 NAS_MMC_GetPlmnSelectionStaTblSize(VOS_VOID);

NAS_FSM_DESC_STRU * NAS_MMC_GetPlmnSelectionFsmDescAddr(VOS_VOID);


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

#endif /* end of NasMmcFsmPLmnSelectionTbl.h */
