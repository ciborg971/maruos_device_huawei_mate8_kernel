

#ifndef __DIAG_API_H__
#define __DIAG_API_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile                            
*****************************************************************************/
#include  "vos.h" 
#include  "msp_diag.h"
#pragma pack(4)

/*****************************************************************************
  2 macro
*****************************************************************************/

/* diag初始化成功且HSO连接上 */
#define  DIAG_IS_CONN_ON            ((g_ulDiagCfgInfo & (DIAG_CFG_INIT | DIAG_CFG_CONN )) == (DIAG_CFG_INIT | DIAG_CFG_CONN ))

/* 允许LT 空口上报 */
#define  DIAG_IS_LT_AIR_ON          ((g_ulDiagCfgInfo & (DIAG_CFG_INIT | DIAG_CFG_CONN | DIAG_CFG_LT_AIR)) == (DIAG_CFG_INIT | DIAG_CFG_CONN | DIAG_CFG_LT_AIR))

/* 允许GU 空口上报 */
#define  DIAG_IS_GU_AIR_ON          ((g_ulDiagCfgInfo & (DIAG_CFG_INIT | DIAG_CFG_CONN | DIAG_CFG_GU_AIR)) == (DIAG_CFG_INIT | DIAG_CFG_CONN | DIAG_CFG_GU_AIR))

/* 允许事件上报 */
#define  DIAG_IS_EVENT_ON           ((g_ulDiagCfgInfo & (DIAG_CFG_INIT | DIAG_CFG_CONN | DIAG_CFG_EVT)) == (DIAG_CFG_INIT | DIAG_CFG_CONN | DIAG_CFG_EVT))


#define DIAG_GET_MODEM_ID(id)               (id >> 24)
#define DIAG_GET_MODE_ID(id)                ((id & 0x000F0000)>>16)
#define DIAG_GET_PRINTF_LEVEL(id)           ((id & 0x0000F000)>>12)
#define DIAG_GET_GROUP_ID(id)               ((id & 0x00000F00)>>8)
#define DIAG_GET_MODULE_ID(id)              ( id & 0x00000FFF)

/* 日志类型定义*/
#define DIAG_CMD_LOG_CATETORY_PRINT_ID              (1<<15)
#define DIAG_CMD_LOG_CATETORY_EVENT_ID              (1<<14)
#define DIAG_CMD_LOG_CATETORY_AIR_ID                (1<<13)
#define DIAG_CMD_LOG_CATETORY_LAYER_ID              (1<<12)
#define DIAG_CMD_LOG_CATETORY_MSG_ID                (1<<10)
#define DIAG_CMD_LOG_CATETORY_USERPLANE_ID          (1<<9)

/*****************************************************************************
  3 Massage Declare 
*****************************************************************************/


/*****************************************************************************
  4 Enum 
*****************************************************************************/


/*****************************************************************************
   5 STRUCT 
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulPrintNum;
    VOS_UINT32 ulAirNum;
    VOS_UINT32 ulVoLTENum;
    VOS_UINT32 ulLayerNum;
    VOS_UINT32 ulUserNum;
    VOS_UINT32 ulEventNum;
    VOS_UINT32 ulTransNum;
} DIAG_LOG_PKT_NUM_ACC_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern VOS_UINT32 g_ulTransId;
extern DIAG_LOG_PKT_NUM_ACC_STRU g_DiagLogPktNum;

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_CHAR * diag_GetFileNameFromPath(VOS_CHAR* pcFileName);


/*****************************************************************************
  9 OTHERS
*****************************************************************************/

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

#endif /* end of diag_api.h */

