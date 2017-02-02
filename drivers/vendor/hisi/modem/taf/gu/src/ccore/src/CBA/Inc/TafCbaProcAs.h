

#ifndef __TAFCBAPROCAS_H__
#define __TAFCBAPROCAS_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "TafCbaCtx.h"
#include  "TafCbsInterface.h"
#include  "TafCbaMntn.h"
#include  "mnmsgcbencdec.h"


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

/* CBS Data��0���ֽ� */
#define TAF_CBA_CB_W_NUM_OF_PAGES_POS                       (0x01)
#define TAF_CBA_MAX_CB_PAGE_LEN                             (83)
#define TAF_CBA_MAX_CB_HEADER_LEN                           (6)

#define TAF_CBA_PADDING_OCTET                               (0xff)
#define TAF_CBA_INVALID_INDEX                               (0xffff)

/* Serial Number�е�Message Code λ������� */
#define TAF_CBA_BIT_MASK_MSG_CODE                           (0x3FF0)

/* Serial Number�е�GS λ������� */
#define TAF_CBA_BIT_MASK_GS                                 (0xC000)

/* Serial Number�е�Update Number λ������� */
#define TAF_CBA_BIT_MASK_UPDATE_NUMBER                      (0x000F)
#define CB_UPDATE_NUMBER_MAX_CHANGE                         (0x0008)
#define CB_MAX_UPDATE_NUMBER                                (0x000F)


#define TAF_CBA_BuildCbsMsgId(ucHigh, ucLow)                ((VOS_UINT16)((ucHigh << 8) | (ucLow)))

#define TAF_CBA_BuildCbsSN(ucHigh, ucLow)                   ((VOS_UINT16)((ucHigh << 8) | (ucLow)))

#define TAF_CBA_BuildGsmCbsPageBitmap(ucPageIndex)          ((VOS_UINT16)(1 << (ucPageIndex - 1)))

#define TAF_CBA_BuildGsCode(usSn)                           ((VOS_UINT8)((usSn >> 14) & 0x03))

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


enum TAF_CBA_GS_CODE_ENUM
{
    TAF_CBA_GS_CODE_HIGH_PRIORITY_CELL_WIDE    = 0x00,                                 /*CBS��Ϣ��С������Ч*/
    TAF_CBA_GS_CODE_PLMN_WIDE                  = 0x01,                                 /*CBS��Ϣ��PLMN����Ч*/
    TAF_CBA_GS_CODE_SERVICE_AREA_WIDE          = 0x02,                                 /*CBS��Ϣ��SA����Ч*/
    TAF_CBA_GS_CODE_LOW_PRIORITY_CELL_WIDE     = 0x03,                                 /*CBS��Ϣ��С������Ч*/

    TAF_CBA_GS_CODE_BUTT
};
typedef VOS_UINT8 TAF_CBA_GS_CODE_ENUM_UINT8;

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
    VOS_UINT8                           aucCbsData[TAF_CBA_MAX_CBDATA_LEN];
    VOS_UINT8                           ucCbsDataLen;
}TAF_CBA_CB_W_AIR_DATA_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

VOS_VOID TAF_CBA_ProcGasMsg(
    struct MsgCB                       *pstMsg
);


VOS_VOID TAF_CBA_ProcWrrMsg(
    struct MsgCB                       *pstMsg
);


VOS_VOID TAF_CBA_ProcBmcMsg(
    struct MsgCB                       *pstMsg
);


#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID TAF_CBA_ProcLrrcMsg(
    struct MsgCB                       *pstMsg
);
#endif  /* (FEATURE_ON == FEATURE_LTE) */

VOS_VOID TAF_CBA_RcvAsCbsCfgCnf(
    BMC_CBS_CFG_CNF_STRU             *pstCfgCnf
);


VOS_VOID TAF_CBA_RcvGasCbsDataInd(
    GAS_CBS_DATA_IND_STRU               *pstGasDataInd
);


VOS_VOID TAF_CBA_RcvBmcCbsDataInd(
    BMC_CBS_DATA_IND_STRU              *pstBmcDataInd
);

VOS_VOID TAF_CBA_RcvLrrcCbsDataInd(
    LRRC_CBS_DATA_IND_STRU             *pstBmcDataInd
);

VOS_VOID TAF_CBA_RcvAsGsStatusChangeInd(
    RR_CBS_GS_STATUS_CHANGE_IND_STRU   *pstGsChangeInd
);


VOS_UINT8 TAF_CBA_GetGsmCbsPageLen(
    GAS_CBS_PAGE_DATA_STRU             *pstCbPageData
);

TAF_CBA_NET_RAT_TYPE_ENUM_UINT8 TAF_CBA_GetRatTypeBySenderPid(
    VOS_UINT32                          ulSenderPid
);

VOS_UINT32  TAF_CBA_IsCbsEnable(VOS_VOID);


VOS_UINT32  TAF_CBA_IsCbsMsgIdValid(
    VOS_UINT16                          usMsgId
);


VOS_UINT16  TAF_CBA_GetEarliestCbsRecordInx(VOS_VOID);

VOS_UINT32 TAF_CBA_GetCbsRecordInxByMsgIdCode(
    TAF_CBA_RECORD_STRU                *pstRecord,
    VOS_UINT32                         *pulIndex
);

VOS_UINT32 TAF_CBA_IsDupBmcCbsRecord(
    TAF_CBA_RECORD_STRU                *pstRecord
);


VOS_VOID TAF_CBA_BuildBmcCbsRecord(
    BMC_CBS_DATA_IND_STRU              *pstBmcDataInd,
    TAF_CBA_RECORD_STRU                *pstNewRecord
);


VOS_VOID TAF_CBA_SaveBmcCbsRecord (
    TAF_CBA_RECORD_STRU                *pstRecord
);

VOS_UINT32 TAF_CBA_IsDupGsmCbsRecord(
    TAF_CBA_RECORD_STRU                *pstRecord
);


VOS_VOID TAF_CBA_BuildGsmCbsRecord(
    MN_MSG_CBGSMPAGE_STRU              *pstGsmPage,
    TAF_CBS_NETWORK_INFO_STRU        *pstCampPlmnInfo,
    TAF_CBA_RECORD_STRU                *pstNewRecord
);

VOS_VOID TAF_CBA_AppendCbsRecord(
    TAF_CBA_RECORD_STRU                *pstNewRecord
);

VOS_VOID TAF_CBA_SaveGsmCbsRecord(
    TAF_CBA_RECORD_STRU                *pstNewRecord
);

VOS_UINT32 TAF_CBA_ProcRcvCbMsg(
    VOS_UINT8                           ucPageNum,
    MN_MSG_CBRAW_TS_DATA_STRU          *pstPageData
);


VOS_UINT32 TAF_CBA_IsNeedDownloadToUsim(
    VOS_UINT16                          usMsgId
);


VOS_UINT32 TAF_CBA_IsMsgIdInCbmid(
    VOS_UINT16                          usMsgId,
    TAF_CBA_CBMI_DOWNLOAD_LIST_STRU    *pstCbmidList
);

VOS_VOID TAF_CBA_ReportRcvCbsData(
    VOS_UINT8                           ucPageNum,
    MN_MSG_CBRAW_TS_DATA_STRU          *pstPageData
);

#if (FEATURE_ON == FEATURE_ETWS)
VOS_UINT32 TAF_CBA_GetCbsDupDetcTimeLen(
    TAF_CBA_PLMN_ID_STRU                                   *pstPlmn,
    VOS_UINT16                                              usMsgId
);
#endif

VOS_UINT32 TAF_CBA_IsNeedDupDetectCbs(
    VOS_UINT16                          usMsgID
);

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

#endif /* end of TafCbaProcAs.h */
