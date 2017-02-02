
#ifndef _NAS_MMC_FSM_GET_GEO_TBL_H_
#define _NAS_MMC_FSM_GET_GEO_TBL_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#include  "vos.h"
#include  "NasFsm.h"
#include  "NasMmcFsmGetGeo.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  1 ȫ�ֱ�������
*****************************************************************************/
extern NAS_STA_STRU                     g_astNasMmcGetGeoStaTbl[];


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define NAS_MMC_GetGetGeoStaTbl()       g_astNasMmcGetGeoStaTbl


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


enum NAS_MMC_GET_GEO_STA_ENUM
{
    NAS_MMC_GET_GEO_STA_INIT,

    NAS_MMC_GET_GEO_STA_WAIT_CSS_BAND_SCAN_CNF,
    NAS_MMC_GET_GEO_STA_WAIT_CSS_STOP_BAND_SCAN_CNF,

    NAS_MMC_GET_GEO_STA_WAIT_GAS_PLMN_SEARCH_CNF,
    NAS_MMC_GET_GEO_STA_WAIT_WAS_PLMN_SEARCH_CNF,

    NAS_MMC_GET_GEO_STA_WAIT_GAS_STOP_PLMN_SEARCH_CNF,
    NAS_MMC_GET_GEO_STA_WAIT_WAS_STOP_PLMN_SEARCH_CNF,

    NAS_MMC_GET_GEO_STA_WAIT_GAS_SUSPEND_CNF,
    NAS_MMC_GET_GEO_STA_WAIT_WAS_SUSPEND_CNF,

    NAS_MMC_GET_GEO_STA_WAIT_LMM_PLMN_SEARCH_CNF,
    NAS_MMC_GET_GEO_STA_WAIT_LMM_STOP_PLMN_SEARCH_CNF,
    NAS_MMC_GET_GEO_STA_WAIT_LMM_SUSPEND_CNF,

    NAS_MMC_GET_GEO_STA_BUTT
};

typedef VOS_UINT32  NAS_MMC_GET_GEO_STA_ENUM_UINT32;


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
extern VOS_UINT32 NAS_MMC_GetGeoStaTblSize(VOS_VOID);

extern NAS_FSM_DESC_STRU * NAS_MMC_GetGeoFsmDescAddr(VOS_VOID);


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


