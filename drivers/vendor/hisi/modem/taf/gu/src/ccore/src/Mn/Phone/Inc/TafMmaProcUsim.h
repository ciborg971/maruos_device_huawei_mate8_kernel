
#ifndef _TAF_MMA_PROC_USIM_H
#define _TAF_MMA_PROC_USIM_H

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "TafSdcCtx.h"
#include "MmaAppLocal.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* Deleted by h00313353 for iteration 9, 2015-3-10, begin */

/* Deleted by h00313353 for iteration 9, 2015-3-10, end */
/* Added by y00322978 for CDMA 1X Iteration 17, 2015-8-22, begin */
#define TAF_MMA_EFRUIMID_OCTET_LEN_EIGHT                   (8)
#define TAF_MMA_EFRUIMID_OCTET_LEN_FIVE                    (5)
/* Added by y00322978 for CDMA 1X Iteration 17, 2015-8-22, end */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum  TAF_MMA_READ_SIM_FILES_CNF_ENUM
{
    TAF_MMA_READ_USIM_FILE_FLG_NULL                         = 0x0,
    TAF_MMA_READ_USIM_PNN_FILE_ID_FLG                       = 0x1,
    TAF_MMA_READ_SIM_PNN_FILE_ID_FLG                        = 0x2,
    TAF_MMA_READ_USIM_OPL_FILE_ID_FLG                       = 0x4,
    TAF_MMA_READ_SIM_OPL_FILE_ID_FLG                        = 0x8,
    TAF_MMA_READ_USIM_SPN_FILE_ID_FLG                       = 0x10,
    TAF_MMA_READ_SIM_SPN_FILE_ID_FLG                        = 0x20,
    TAF_MMA_READ_CPHS_FILE_ID_FLG                           = 0x40,
    TAF_MMA_READ_SIM_SPDI_FILE_ID_FLG                       = 0x80,
    TAF_MMA_READ_USIM_SPDI_FILE_ID_FLG                      = 0x100,
    TAF_MMA_READ_CUSTOM_SRV_PROFILE_FILE_ID_FLG             = 0x200,
    TAF_MMA_READ_USIM_FILE_CNF_BUTT
};

typedef VOS_UINT32 TAF_MMA_READ_SIM_FILES_CNF_ENUM_UINT32;

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
#if (FEATURE_ON == FEATURE_ECALL)

VOS_VOID TAF_MMA_UpdateCallMode( VOS_VOID );

#endif

VOS_VOID    TAF_MMA_SetWaitSimFilesCnfFlg(
    TAF_MMA_READ_SIM_FILES_CNF_ENUM_UINT32                  enSimFileCnfFlg
);

TAF_MMA_READ_SIM_FILES_CNF_ENUM_UINT32  TAF_MMA_GetWaitSimFilesCnfFlg(VOS_VOID);
VOS_VOID  TAF_MMA_ClearAllWaitSimFilesCnfFlg(VOS_VOID);
VOS_VOID  TAF_MMA_ReadSimCphsOperNameFile(VOS_VOID);

VOS_VOID TAF_MMA_ReadSpnFile(VOS_VOID);

VOS_UINT32 TAF_MMA_UsimGetFileRspPreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_MMA_ReadOplFile(VOS_VOID);
VOS_VOID TAF_MMA_ReadPnnFile(VOS_VOID);
VOS_VOID TAF_MMA_ReadSpdiFile(VOS_VOID);
VOS_UINT32 TAF_MMA_SendUsimFileReq(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT16                          usEfId
);
VOS_VOID  TAF_MMA_ClearWaitSimFilesCnfFlg(
    USIMM_DEF_FILEID_ENUM_UINT32        usEfId
);
VOS_VOID TAF_MMA_ReadCustomerServiceProfileFile_SwitchOn(VOS_VOID);

VOS_VOID   TAF_MMA_ReadCphsFileCnf(
    USIMM_READFILE_CNF_STRU            *pUsimTafMsg
);
VOS_VOID TAF_MMA_UsimRefreshIndFileListChangedMsgProc(USIMM_STKREFRESH_IND_STRU *pUsimTafMsg);
VOS_VOID TAF_MMA_ReadIccIdFileCnf(VOS_VOID);
VOS_VOID TAF_MMA_ReadSpdiFileCnf(
    USIMM_READFILE_CNF_STRU            *pUsimTafMsg,
    USIMM_DEF_FILEID_ENUM_UINT32        enFileID
);
VOS_VOID TAF_MMA_ReadPnnFileCnf(
    USIMM_READFILE_CNF_STRU            *pUsimTafMsg,
    USIMM_DEF_FILEID_ENUM_UINT32        enFileID
);
VOS_VOID TAF_MMA_ReadOplFileCnf(
    USIMM_READFILE_CNF_STRU            *pUsimTafMsg,
    USIMM_DEF_FILEID_ENUM_UINT32        enFileID
);

VOS_VOID MMA_ReadSpnFileCnf(
    TAF_PH_USIM_SPN_CNF_STRU           *pMsg,
    USIMM_DEF_FILEID_ENUM_UINT32        enFileID
);

VOS_VOID TAF_MMA_RcvCustomerServiceProfileFile(
    VOS_UINT32                          ulRslt,
    VOS_UINT16                          usEfLen,
    VOS_UINT8                          *pucEf
);

VOS_VOID TAF_MMA_USIMRefreshFileProc(
    VOS_UINT16                          usEfId,
    VOS_UINT16                          usEfLen,
    VOS_UINT8                          *pucEf
);


/* Added by y00322978 for CDMA 1X Iteration 17, 2015-8-22, begin */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_MMA_RcvUsimmReadUimidFile(
    USIMM_READFILE_CNF_STRU            *pstUsimmReadCnfMsg
);
#endif
/* Added by y00322978 for CDMA 1X Iteration 17, 2015-8-22, end */

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


