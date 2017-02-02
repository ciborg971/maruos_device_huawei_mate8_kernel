
#ifndef _NAS_MMC_FSM_INTER_SYS_CELLRESEL_TBL_H_
#define _NAS_MMC_FSM_INTER_SYS_CELLRESEL_TBL_H_

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
extern NAS_STA_STRU                            g_astNasMmcInterSysCellReselStaTbl[];



/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define NAS_MMC_GetInterSysCellReselStaTbl()                      (g_astNasMmcInterSysCellReselStaTbl)



/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : NAS_MMC_INTER_SYS_CELLRESEL_STA_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ״̬��InterSysCellResel��״̬ö�ٶ���
*****************************************************************************/
enum NAS_MMC_INTER_SYS_CELLRESEL_STA_ENUM
{
    /* ����㷢�����ϵͳ��ѡ�����еĳ�ʼ��״̬*/
    NAS_MMC_INTER_SYS_CELLRESEL_STA_INIT                                     =0,

    /* ����㷢�����ϵͳ��ѡ�����еȴ�MM�Ĺ��� */
    NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_SUSPEND_RSP                      =1,

    /* ����㷢�����ϵͳ��ѡ�����еȴ������Ļָ� */
    NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND                       =2,

    /* ����㷢�����ϵͳ��ѡ�����еȴ�MM�Ļָ� */
    NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP                       =3,

    /* ����㷢�����ϵͳ��ѡ�����еȴ�WASϵͳ��Ϣ */
    NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND                     =4,

    /* ����㷢�����ϵͳ��ѡ�����еȴ�GASϵͳ��Ϣ */
    NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SYSINFO_IND                     =5,

#if (FEATURE_ON == FEATURE_LTE)
    /* ����㷢�����ϵͳ��ѡ�����еȴ�Lϵͳ��Ϣ */
    NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SYSINFO_IND                     =6,
    NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SUSPEND_REL_CNF                 =7,
#endif

    NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SUSPEND_REL_CNF                 =8,

    NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SUSPEND_REL_CNF                 =9,

    NAS_MMC_INTER_SYS_CELLRESEL_BUTT
};

typedef VOS_UINT32  NAS_MMC_INTER_SYS_CELLRESEL_STA_ENUM_UINT32;


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
VOS_UINT32 NAS_MMC_GetInterSysCellReselStaTblSize( VOS_VOID  );

NAS_FSM_DESC_STRU * NAS_MMC_GetInterSysCellReselFsmDescAddr(VOS_VOID);



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

#endif /* end of NasMmcInterSysCellReselFsmTbl.h */




