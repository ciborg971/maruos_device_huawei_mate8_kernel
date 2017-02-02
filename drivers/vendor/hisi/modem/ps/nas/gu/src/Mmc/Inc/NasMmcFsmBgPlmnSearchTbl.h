
#ifndef _NAS_MMC_FSM_BG_PLMN_SEARCH_TBL_H_
#define _NAS_MMC_FSM_BG_PLMN_SEARCH_TBL_H_

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
extern NAS_STA_STRU                                         g_astNasMmcFsmBgPlmnSearchStaTbl[];

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define NAS_MMC_GetBgPlmnSearchStaTbl()                     (g_astNasMmcFsmBgPlmnSearchStaTbl)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


enum NAS_MMC_BG_PLMN_SEARCH_STA_ENUM
{
    /* �����ȼ�����״̬���ȴ���Ϣ״̬ */
    NAS_MMC_BG_PLMN_SEARCH_STA_INIT                                  =0,

    /*  �ȴ�Wģ�ϱ�BG������� */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_BG_PLMN_SEARCH_CNF           =1,

    /*  �ȴ�Gģ�ϱ�BG������� */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_BG_PLMN_SEARCH_CNF           =2,

    /*  �ȴ�Wģ�ϱ������� */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_SUSPEND_CNF                  =3,

    /*  �ȴ�Gģ�ϱ������� */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_SUSPEND_CNF                  =4,

    /*  �ȴ�Wģ�ϱ�ֹͣBG������� */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_BG_PLMN_STOP_CNF             =5,

    /*  �ȴ�Gģ�ϱ�ֹͣBG������� */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_BG_PLMN_STOP_CNF             =6,

    /*  �ȴ�Wģ�ϱ�ֹͣ����ָ��������� */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_FAST_PLMN_STOP_CNF           =7,

    /*  �ȴ�Gģ�ϱ�ֹͣ����ָ��������� */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_FAST_PLMN_STOP_CNF           =8,

    /*  �ȴ�Wģ�ϱ�����ָ��������� */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_PLMN_FAST_SEARCH_CNF         =9,

    /*  �ȴ�Gģ�ϱ�����ָ��������� */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_PLMN_FAST_SEARCH_CNF         =10,

    /*  �ȴ�Wģ�ϱ�ϵͳ��Ϣ*/
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_SYSINFO_IND                  =11,

    /*  �ȴ�Gģ�ϱ�ϵͳ��Ϣ*/
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_SYSINFO_IND                  =12,

    /*  �ȴ�CS+PS���ע����*/
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_CSPS_REG_IND                     =13,

    /*  �ȴ�GU�����ͷ� */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_RRC_CONN_REL_IND                 =14,

    /*  ��VPLMNʱ�ȴ�Wģ�ϱ������� */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_SUSPEND_CNF_RECAMP_VPLMN     =15,

    /*  ��VPLMNʱ�ȴ�Gģ�ϱ������� */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_SUSPEND_CNF_RECAMP_VPLMN     =16,

    /*  ��VPLMNʱ�ȴ�Wģ�ϱ�ָ��������� */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_PLMN_SEARCH_CNF_RECAMP_VPLMN =17,

    /*  ��VPLMNʱ�ȴ�Gģ�ϱ�ָ��������� */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_PLMN_SEARCH_CNF_RECAMP_VPLMN =18,

    /*  ��VPLMNʱ�ȴ�Wģ�ϱ�ָֹͣ��������� */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_PLMN_STOP_CNF_RECAMP_VPLMN   =19,

    /*  ��VPLMNʱ�ȴ�Gģ�ϱ�ָֹͣ��������� */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_PLMN_STOP_CNF_RECAMP_VPLMN   =20,

    /*  ��VPLMNʱ�ȴ�Wģ�ϱ�ϵͳ��Ϣ*/
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_SYSINFO_IND_RECAMP_VPLMN     =21,

    /*  ��VPLMNʱ�ȴ�Gģ�ϱ�ϵͳ��Ϣ*/
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_SYSINFO_IND_RECAMP_VPLMN     =22,

    /* �ȴ�Lģ�ϱ������� */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_SUSPEND_CNF                  =23,

    /* �ȴ�Lģ�ϱ�ϵͳ��Ϣ��� */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_SYSINFO_IND                  =24,

    /* �ȴ�epsע���� */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_REG_IND                      =25,

    /* �ȴ�Lģ�����ͷŽ�� */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_CONN_REL_IND                 =26,

    /* ��VPLMNʱ�ȴ�Lģ�ϱ�������� */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_PLMN_SEARCH_CNF_RECAMP_VPLMN =27,

    /* ��VPLMNʱ�ȴ�Lģ�ϱ������� */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_SUSPEND_CNF_RECAMP_VPLMN     =28,

    /* ��VPLMNʱ�ȴ�Lģ�ϱ�ֹͣ������� */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_PLMN_STOP_CNF_RECAMP_VPLMN   =29,

    /* ��VPLMNʱ�ȴ�Lģ�ϱ�ϵͳ��Ϣ��� */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_SYSINFO_IND_RECAMP_VPLMN     =30,

    /* �ȴ�Lģ�ϱ�BG������� */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_BG_PLMN_SEARCH_CNF           =31,

    /*  �ȴ�Lģ�ϱ�ֹͣBG������� */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_BG_PLMN_STOP_CNF             =32,

    /*  �ȴ�Lģ�ϱ�����ָ��������� */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_PLMN_FAST_SEARCH_CNF         =33,

    /*  �ȴ�Lģ�ϱ�ֹͣ����ָ��������� */
    NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_FAST_PLMN_STOP_CNF           =34,

    NAS_MMC_BG_PLMN_SEARCH_STA_BUTT
};
typedef VOS_UINT32  NAS_MMC_BG_PLMN_SEARCH_STA_ENUM_U32;


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
VOS_UINT32 NAS_MMC_GetBgPlmnSearchStaTblSize(VOS_VOID);

NAS_FSM_DESC_STRU * NAS_MMC_GetBgPlmnSearchFsmDescAddr(VOS_VOID);


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
