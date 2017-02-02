/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsFsmCdataDiscingTbl.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2014年10月14日
  最近修改   :
  功能描述   : TafApsFsmCdataDiscingTbl.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月14日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAFAPSFSMCDATADISCINGTBL_H__
#define __TAFAPSFSMCDATADISCINGTBL_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "TafFsm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
extern TAF_STA_STRU                             g_astTafApsCdataDiscingStaTbl[];
#define TAF_APS_GetCdataDiscingStaTbl()       (g_astTafApsCdataDiscingStaTbl)

#endif
/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum TAF_APS_CDATA_DISCING_SUBSTA_ENUM
{
    TAF_APS_CDATA_DISCING_SUBSTA_INIT                            = 0x00,        /* CDATA DISCING状态机的初始状态 */
    TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_DISC_CNF               = 0x01,        /* APS已经向HSM模块发起了断开请求，等待HSM的响应 */
    TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_HANGUP_DATA_CALL_CNF   = 0x02,        /* APS已经向XCC模块发起了断开请求，等待XCC的响应 */
    /* Added by y00314741 for CDMA Iteration 15, 2015-5-8, begin */
    TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF    = 0x03,        /* APS已经向EHSM模块发起了断开请求，等待EHSM的响应 */
    TAF_APS_CDATA_DISCING_SUBSTA_SUSPEND                         = 0x04,        /* CDATA DISCING状态机的挂起状态 */
    /* Added by y00314741 for CDMA Iteration 15, 2015-5-8, end */
    TAF_APS_CDATA_DISCING_SUBSTA_BUTT                            = 0xFF
} ;
typedef VOS_UINT32 TAF_APS_CDATA_DISCING_SUBSTA_ENUM_UINT32;


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_UINT32 TAF_APS_GetCdataDiscingStaTblSize( VOS_VOID );

TAF_FSM_DESC_STRU * TAF_APS_GetCdataDiscingFsmDescAddr( VOS_VOID );

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

#endif /* end of TafApsFsmCdataDiscingTbl.h */
