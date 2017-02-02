

#ifndef __TAFCBAPROCUSIM_H__
#define __TAFCBAPROCUSIM_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "TafCbaCtx.h"
#include  "TafCbsInterface.h"
#include  "MnMsgApi.h"
#include  "UsimPsInterface.h"
#include  "NasUsimmApi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))


/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define  TAF_CBA_CBMI_UNIT_LEN                              (2)
#define  TAF_CBA_CBMIR_UNIT_LEN                             (4)

#define  TAF_CBA_EF_MSGID_PADDING                           (0xffff)


/* ͳһʹ��USIM�ṩ���ļ�IDö��,��������ʵ���ļ�ID */


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


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

typedef struct
{
    VOS_UINT16                          usMsgIdFrom;                            /*Cell broadcast message id value range from  */
    VOS_UINT16                          usMsgIdTo;                              /*Cell broadcast message id value range to    */
}TAF_CBA_USIM_CBMIR_STRU;

typedef struct
{
    VOS_UINT8                          ucTafCbaCbmiFlag;
    VOS_UINT8                          ucTafCbaCbmirFlag;
    VOS_UINT8                          ucTafCbaCbmidFlag;
}TAF_CBA_FILE_NEED_REFRESH_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

extern VOS_UINT32 TAF_CBA_IsNeedActAsCbs(VOS_VOID);

extern VOS_VOID TAF_CBA_SndAsActiveCbsReq(
    TAF_CBS_CFG_ENUM_UINT32      enCfgFlg
);

VOS_VOID TAF_CBA_RcvUsimGetEfCbmiRsp(
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_CBA_RcvUsimGetEfCbmirRsp(
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_CBA_RcvUsimGetEfCbmidRsp(
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_CBA_ParseUsimFileEfCbmiData(
    VOS_UINT8                           ucEfCbmiExistFlg,
    VOS_UINT8                          *pucEf,
    VOS_UINT16                          usEfLen
);

VOS_VOID TAF_CBA_ParseUsimFileEfCbmirData(
    VOS_UINT8                           ucEfCbmirExistFlg,
    VOS_UINT8                          *pucEf,
    VOS_UINT16                          usEfLen
);

VOS_VOID TAF_CBA_ParseUsimFileEfCbmidData(
    VOS_UINT8                           ucEfCbmidExistFlg,
    VOS_UINT8                          *pucEf,
    VOS_UINT16                          usEfLen
);

VOS_UINT16 TAF_CBA_CountCbmiNum(
    VOS_UINT16                         *pusCbmi,
    VOS_UINT32                          ulLength
);

VOS_UINT16 TAF_CBA_CountCbmirNum(
    VOS_UINT16                         *pusCbmir,
    VOS_UINT32                          ulLength
);

VOS_VOID TAF_CBA_BuildUsimEfCbmiContent(
    VOS_UINT16                         *pusMsgId
);

VOS_VOID TAF_CBA_BuildUsimEfCbmirContent(
    TAF_CBA_USIM_CBMIR_STRU            *pstMsgRange
);

VOS_VOID TAF_CBA_UpdateUsimFileEfCbmiReq(VOS_VOID);

VOS_VOID TAF_CBA_UpdateUsimFileEfCbmirReq(VOS_VOID);

VOS_VOID  TAF_CBA_UpdateUsimFile(VOS_VOID);

/* Modified by h00313353 for iteration 9, 2015-2-6, begin */
VOS_UINT32  TAF_CBA_ProcUsimSetFileRsp(
    USIMM_UPDATEFILE_CNF_STRU           *pstSetFileRsp
);
/* Modified by h00313353 for iteration 9, 2015-2-6, end */

VOS_VOID TAF_CBA_ReadSpecificFileListRefreshFile(
    VOS_UINT32                          ulFileId,
    NAS_USIMM_SERVICES_TYPE_ENUM_UINT32 ulUsimmService,
    USIMM_STKREFRESH_IND_STRU          *pstRefreshInd
);


VOS_VOID TAF_CBA_ParseSpecUsimFileData (
    VOS_UINT16                          usFileId,
    VOS_UINT8                           ucFileExistFlg,
    VOS_UINT8                          *pucEf,
    VOS_UINT16                          ulEfLen
);



VOS_VOID TAF_CBA_SndUsimCbMsg(
    VOS_UINT32                          ulSendPID,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_CBRAW_TS_DATA_STRU          *pstCbMsg
);

VOS_VOID TAF_CBA_ReadUsimFile(
    VOS_UINT32                          ulFileId,
    NAS_USIMM_SERVICES_TYPE_ENUM_UINT32 ulUsimmService
);

VOS_VOID TAF_CBA_ApplyUsimInfo(VOS_VOID);
/* Modified by h00313353 for iteration 9, 2015-2-6, begin */
VOS_VOID TAF_CBA_ProcRefreshInd(USIMM_STKREFRESH_IND_STRU *pstRefreshInd);
/* Modified by h00313353 for iteration 9, 2015-2-6, end */


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

#endif /* end of TafCbaProcUsim.h */
