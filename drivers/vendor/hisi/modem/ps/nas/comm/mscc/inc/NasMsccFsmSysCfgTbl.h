
#ifndef _NAS_MSCC_FSM_SYS_CFG_TBL_H_
#define _NAS_MSCC_FSM_SYS_CFG_TBL_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#include  "vos.h"
#include  "PsTypeDef.h"
#include  "NasFsm.h"
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

extern NAS_STA_STRU                            g_astNasMsccSysCfgStaTbl[];


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define NAS_MSCC_GetSysCfgStaTbl()                   (g_astNasMsccSysCfgStaTbl)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


enum NAS_MSCC_SYS_CFG_STA_ENUM
{
    /* System config Init State */
    NAS_MSCC_SYSCFG_STA_INIT,

    /* Waiting for power save confirmation from XSD */
    NAS_MSCC_SYSCFG_STA_WAIT_XSD_POWER_SAVE_CNF,

    /* Waiting for power save confirmation from HSD */
    NAS_MSCC_SYSCFG_STA_WAIT_HSD_POWER_SAVE_CNF,

    /* Waiting for power save confirmation from MMC */
    NAS_MSCC_SYSCFG_STA_WAIT_MMC_POWER_SAVE_CNF,

    /* Waiting for system config confirmation from XSD */
    NAS_MSCC_SYSCFG_STA_WAIT_XSD_SYS_CFG_CNF,

    /* Waiting for system config confirmation from HSD */
    NAS_MSCC_SYSCFG_STA_WAIT_HSD_SYS_CFG_CNF,

    /* Waiting for system config confirmation from MMC */
    NAS_MSCC_SYSCFG_STA_WAIT_MMC_SYS_CFG_CNF,

    /* Invalid state */
    NAS_MSCC_SSYSCFG_STA_BUTT
};
typedef VOS_UINT32  NAS_MSCC_SYSCFG_STA_ENUM_UINT32;

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
VOS_UINT32 NAS_MSCC_GetSysCfgStaTblSize(VOS_VOID);

NAS_FSM_DESC_STRU * NAS_MSCC_GetSysCfgFsmDescAddr(VOS_VOID);

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

#endif /* end of NasMsccFsmSysCfgTbl.h */


