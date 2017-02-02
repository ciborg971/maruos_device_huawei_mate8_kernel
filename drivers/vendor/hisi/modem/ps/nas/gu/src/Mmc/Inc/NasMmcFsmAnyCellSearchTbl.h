
#ifndef _NAS_MMC_FSM_ANYCELL_SEARCH_TBL_H_
#define _NAS_MMC_FSM_ANYCELL_SEARCH_TBL_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
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
extern NAS_STA_STRU                                   g_astNasMmcAnyCellSearchStaTbl[];


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define NAS_MMC_GetAnyCellSearchStaTbl()              (g_astNasMmcAnyCellSearchStaTbl)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


enum NAS_MMC_ANYCELL_SEARCH_STA_ENUM
{
    NAS_MMC_ANYCELL_SEARCH_STA_INIT                                             = 0,

    /* �ȴ�Wģ�ϱ�������� */
    NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_PLMN_SEARCH_CNF                         = 1,

    /* �ȴ�Gģ�ϱ�������� */
    NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_PLMN_SEARCH_CNF                         = 2,

    /* �ȴ�Lģ�ϱ�������� */
    NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_PLMN_SEARCH_CNF                         = 3,

    /* �ȴ�Wģ�ϱ������� */
    NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_SUSPEND_CNF                             = 4,

    /* �ȴ�Gģ�ϱ������� */
    NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_SUSPEND_CNF                             = 5,

    /* �ȴ�Lģ�ϱ������� */
    NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_SUSPEND_CNF                             = 6,

    /* �ȴ�Wģ�ϱ�ֹͣ������� */
    NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_PLMN_STOP_CNF                           = 7,

    /* �ȴ�Gģ�ϱ�ֹͣ������� */
    NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_PLMN_STOP_CNF                           = 8,

    /* �ȴ�Lģ�ϱ�ֹͣ������� */
    NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_PLMN_STOP_CNF                           = 9,


    /* ANYCELL�����ɹ���ȴ�Wģ�ϱ�ϵͳ��Ϣ */
    NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_SYSINFO_IND                             = 10,

    /* ANYCELL�����ɹ���ȴ�Gģ�ϱ�ϵͳ��Ϣ */
    NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_SYSINFO_IND                             = 11,

    /* ANYCELL�����ɹ���ȴ�Lģ�ϱ�ϵͳ��Ϣ */
    NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_SYSINFO_IND                             = 12,
    
    NAS_MMC_ANYCELL_SEARCH_STA_BUTT

};
typedef VOS_UINT32  NAS_MMC_ANYCELL_SEARCH_STA_ENUM_UINT32;



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
VOS_UINT32 NAS_MMC_GetAnyCellSearchStaTblSize(VOS_VOID);

NAS_FSM_DESC_STRU * NAS_MMC_GetAnyCellSearchFsmDescAddr(VOS_VOID);


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

#endif /* end of NasMmcFsmAnyCellSearchTbl.h */
