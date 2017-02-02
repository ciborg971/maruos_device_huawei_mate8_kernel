
#ifndef _NAS_MMC_FSM_INTER_SYS_CCO_TBL_H_
#define _NAS_MMC_FSM_INTER_SYS_CCO_TBL_H_

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
extern NAS_STA_STRU                                     g_astNasMmcInterSysCcoStaTbl[];


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define NAS_MMC_GetInterSysCcoStaTbl()                          (g_astNasMmcInterSysCcoStaTbl)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : NAS_MMC_INTER_SYS_CCO_STA_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ״̬��InterSysCco��״̬ö�ٶ���
*****************************************************************************/
enum NAS_MMC_INTER_SYS_CCO_STA_ENUM
{
    /*Cell change order״̬����ʼ��״̬*/
    NAS_MMC_INTER_SYS_CCO_STA_INIT                                          =0,

    /*Cell change order���� �ȴ�MM����ظ�*/
    NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP                           =1,

    /*Cell change order״̬�� �ȴ������Ļָ�ָʾ*/
    NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_RESUME_IND                            =2,

    /*Cell change order״̬�� �ȴ�MM�ָ��ظ�*/
    NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP                            =3,

    /*Cell change order״̬�� �ȴ�WASϵͳ��Ϣ*/
    NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND                          =4,

    /*Cell change order״̬�� �ȴ�GASϵͳ��Ϣ*/
    NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND                          =5,

#if (FEATURE_ON == FEATURE_LTE)
    /*Cell change order״̬�� �ȴ�Lϵͳ��Ϣ*/
    NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND                          =6,
#endif

    /*Cell change order״̬�� �ȴ��������*/
    NAS_MMC_INTER_SYS_CCO_STA_WAIT_EST_IND                                  =7,

    /*Cell change order״̬�� �ȴ�����ʱ�����Ĺ���ָʾ*/
    NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_SUSPEND_IND_FALLBACK                  =8,

    /*Cell change order״̬�� �ȴ�����ʱMM�Ĺ���ظ�*/
    NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP_FALLBACK                  =9,

    /*Cell change order״̬�� �ȴ�����ʱ�����Ļָ�ָʾ*/
    NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_RESUME_IND_FALLBACK                   =10,

    /*Cell change order״̬�� �ȴ�����ʱMM�Ļָ��ظ�*/
    NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP_FALLBACK                   =11,

    /*Cell change order״̬�� �ȴ�����ʱWASϵͳ��Ϣ*/
    NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND_FALLBACK                 =12,

    /*Cell change order״̬�� �ȴ�����ʱGASϵͳ��Ϣ*/
    NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND_FALLBACK                 =13,

#if (FEATURE_ON == FEATURE_LTE)
    /*Cell change order״̬�� �ȴ�����ʱLϵͳ��Ϣ*/
    NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND_FALLBACK                 =14,
#endif

    NAS_MMC_INTER_SYS_CCO_STA_BUTT
};

typedef VOS_UINT32  NAS_MMC_INTER_SYS_CCO_STA_ENUM_UINT32;


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
VOS_UINT32 NAS_MMC_GetInterSysCcoStaTblSize( VOS_VOID  );

NAS_FSM_DESC_STRU * NAS_MMC_GetInterSysCcoFsmDescAddr(VOS_VOID);

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

#endif /* end of NasMmcInterSysCcoFsmTbl.h */



