/******************************************************************************

            Copyright 2014, Huawei Technologies Co. Ltd.

 ******************************************************************************
File Name       :   NasMsccFsmSysAcqTbl.h
Author          :   m00312079
Version         :
Date            :   2015-4-3
Description     :   Contains FSM tables and act tables for SystemAcq
Function list   :
History         :
    1) Date :
       Author:
       Modification:
******************************************************************************/
#ifndef _NAS_MSCC_FSM_SYS_ACQ_TBL_H_
#define _NAS_MSCC_FSM_SYS_ACQ_TBL_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#include  "vos.h"
#include  "PsTypeDef.h"
#include  "NasFsm.h"
#include  "ImsaMsccInterface.h"
#include  "MsccMmcInterface.h"
#include  "MmaMsccInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  1 ȫ�ֱ�������
*****************************************************************************/

extern NAS_STA_STRU                            g_astNasMsccSysAcqStaTbl[];


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define NAS_MSCC_GetSysAcqStaTbl()                   (g_astNasMsccSysAcqStaTbl)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/****************************************************************************
Structure name    :   NAS_MSCC_SYSACQ_STA_ENUM
Description       :   Information of all states in System Acquire FSM
Modify History:
    1)  Date    :   2015-4-3
        Author  :   m00312079
        Modify content :    Create
****************************************************************************/
enum NAS_MSCC_SYSACQ_STA_ENUM
{
    NAS_MSCC_SYSACQ_STA_INIT,

    NAS_MSCC_SYSACQ_STA_WAIT_HSD_ACQUIRE_CNF,

    NAS_MSCC_SYSACQ_STA_WAIT_HSD_POWER_SAVE_CNF,

    NAS_MSCC_SYSACQ_STA_WAIT_MMC_PLMN_SEARCH_CNF,

    NAS_MSCC_SYSACQ_STA_WAIT_MMC_POWER_SAVE_CNF,

    NAS_MSCC_SYSACQ_STA_WAIT_INIT_LOC_INFO_IND,

    NAS_MSCC_SYSACQ_STA_BUTT
};
typedef VOS_UINT32  NAS_MSCC_SYSACQ_STA_ENUM_UINT32;

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
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32 NAS_MSCC_GetSysAcqStaTblSize(VOS_VOID);

NAS_FSM_DESC_STRU * NAS_MSCC_GetSysAcqFsmDescAddr(VOS_VOID);
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

#endif /* end of NasMsccFsmSwitchOnTbl.h */



