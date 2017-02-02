/******************************************************************************

            Copyright 2014, Huawei Technologies Co. Ltd.

 ******************************************************************************
File Name       :   NasMsccFsmSwitchOnTbl.h
Author          :   m270891
Version         :
Date            :   2015-1-30
Description     :   Contains FSM tables and act tables for SwitchOn
Function list   :
History         :
    1) Date :
       Author:
       Modification:
******************************************************************************/
#ifndef _NAS_MSCC_FSM_SWITCH_ON_TBL_H_
#define _NAS_MSCC_FSM_SWITCH_ON_TBL_H_

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

extern NAS_STA_STRU                            g_astNasMsccSwitchOnStaTbl[];


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define NAS_MSCC_GetSwitchOnStaTbl()                   (g_astNasMsccSwitchOnStaTbl)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


enum NAS_MSCC_SWITCH_ON_STA_ENUM
{
    /* Switch On Init State */
    NAS_MSCC_SWITCHON_STA_INIT,

#if (FEATURE_IMS == FEATURE_ON)
    /* Waiting for Start confirmation from IMSA */
    NAS_MSCC_SWITCHON_STA_WAIT_IMSA_START_CNF,
#endif
    /* Waiting for Start confirmation from MMC */
    NAS_MSCC_SWITCHON_STA_WAIT_MMC_START_CNF,

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* Waiting for start confirmation from XSD */
    NAS_MSCC_SWITCHON_STA_WAIT_XSD_START_CNF,
    /* Waiting for start confirmation from HSD */
    NAS_MSCC_SWITCHON_STA_WAIT_HSD_START_CNF,
#endif

    NAS_MSCC_SWITCHON_STA_WAIT_CARD_READ_CNF,

    NAS_MSCC_SWITCHON_STA_BUTT
};
typedef VOS_UINT32  NAS_MSCC_SWITCH_ON_STA_ENUM_UINT32;

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
VOS_UINT32 NAS_MSCC_GetSwitchOnStaTblSize(VOS_VOID);

NAS_FSM_DESC_STRU * NAS_MSCC_GetSwitchOnFsmDescAddr(VOS_VOID);

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


