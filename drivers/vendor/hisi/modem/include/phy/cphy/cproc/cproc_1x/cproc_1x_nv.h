/**

                   Huawei Technologies Sweden AB (C), 2001-2011,

 ******************************************************************************
 * @file
 *
 * @author  F73150
 * @version
 * @date    2015/03/03 15:20(+0100)
 * @copyright Huawei Technologies Sweden AB
******************************************************************************/

/*****************************************************************************
  1 Other files included
*****************************************************************************/
#ifndef INCLUSION_GUARD_CPROC_1X_NV_H
#define INCLUSION_GUARD_CPROC_1X_NV_H

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */
#include "PhyNvDefine.h"
#include "CasNvInterface.h"
#include "uphy_type_define.h"

/*****************************************************************************
  2 Macro definitions
*****************************************************************************/
/*NV context, include all struct*/
#define CPROC_1X_GetNvContextAddress()       ( pstCproc1xNvContext )

/*Nxm switch data address, include n2m and n3m*/
#define CPROC_1X_GetNxmSwitchAddress()       ( &(CPROC_1X_GetNvContextAddress())->stCproc1xNxmSwitch )

/*Filter coef data address */
#define CPROC_1X_GetFilterCoefAddress()      ( &(CPROC_1X_GetNvContextAddress())->stCproc1xFilterCoef )

/*n2m config value, read from nv table*/
#define CPROC_1X_GetN2mHuaweiConfigValue()   ( (CPROC_1X_GetNxmSwitchAddress())->ucN2mHuaweiConfigValue )

/*n3m config value, read from nv table*/
#define CPROC_1X_GetN3mHuaweiConfigValue()   ( (CPROC_1X_GetNxmSwitchAddress())->ucN3mHuaweiConfigValue )
/*****************************************************************************
  3 Enumeration declaration
*****************************************************************************/

/*****************************************************************************
  4 Message Header declaration
*****************************************************************************/

/*****************************************************************************
  5 Message declarations
*****************************************************************************/

/*****************************************************************************
  6 STRUCT declarations
*****************************************************************************/

typedef struct CPROC_1X_NV_TABLE_STRU
{
    UCOM_NV_CDMA_1X_CPROC_GENERAL_STRU stGeneral;
    UCOM_NV_SINGLE_XO_DEFINE_STRU      stXoDefine;
}CPROC_1X_NV_TABLE_STRU;

typedef struct CPROC_1X_NV_CONTEXT_STRU
{
    CPROC_1X_NVIM_FILTER_COEF_STRU stCproc1xFilterCoef;
    CPROC_1X_NVIM_NXM_SWITCH_STRU stCproc1xNxmSwitch;
}CPROC_1X_NV_CONTEXT_STRU;
/*****************************************************************************
  7 UNION declarations
*****************************************************************************/

/*****************************************************************************
  8 OTHER declarations
*****************************************************************************/

/*****************************************************************************
  9 Global variables
*****************************************************************************/

/*****************************************************************************
  10 Function declarations
*****************************************************************************/
/*nv context pointer*/
extern CPROC_1X_NV_CONTEXT_STRU *pstCproc1xNvContext;

CPROC_1X_NV_TABLE_STRU* pstGetCproc1xNvAddress(PHY_VOID);
PHY_VOID CPROC_1X_GetFilterCoefFromNvTable( PHY_VOID );
PHY_VOID CPROC_1X_ReadNvTable( PHY_VOID );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* INCLUSION_GUARD_CPROC_1X_NV_H */
