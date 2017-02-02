


#ifndef __NAS_MSCC_MLPL_MSPL_API_H__
#define __NAS_MSCC_MLPL_MSPL_API_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "NasMsccMlplMsplParse.h"
#include "NasMsccCtx.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define NAS_MSCC_BYTES_IN_HRPD_SUBNET                       (16)

#define NAS_MSCC_MLPL_WILDCARD_MCC                          (0x0FFF)

#define NAS_MSCC_MLPL_WILDCARD_MNC                          (0x0FFF)

#define NAS_MSCC_NAS_STYLE_WILDCARD_MNC                     (0x0F0F0F)

#define NAS_MSCC_MLPL_WILDCARD_NID_START                    (0xFFFF)

#define NAS_MSCC_INVALID_MSPL_INDEX                         (0xFF)

#define NAS_MSCC_INVALID_MSPL_REC_ID                        (0xFF)

#define NAS_MSCC_MAX_PREF_PLMN_NUM                          (NAS_MSCC_PIF_MAX_EHPLMN_NUM \
                                                             + NAS_MSCC_PIF_MAX_USERPLMN_NUM \
                                                             + NAS_MSCC_PIF_MAX_OPERPLMN_NUM)

#define NAS_MSCC_BIT_LEN_ONE_BYTE                           (8)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
   ����3gpp����5�ֿ��ܵ�ƥ�伶����ϣ��������ȼ�����Ϊ:
   MCC_MNC_LOC > MCC_LOC > LOC > MCC_MNC > MCC

   ����3gpp2 1x�����ܵ�ƥ�伶��������3gpp��ͬ

   ����3ggp2 HRPD���������粻��MNC�����п��ܵ�ƥ�伶����Ϻ�����Ϊ:
   MCC_LOC > LOC > MCC
*****************************************************************************/

enum NAS_MSCC_MLPL_MATCH_LEVEL_ENUM
{
    NAS_MSCC_MLPL_MATCH_LVL_NOT_MATCH   = 0x00,     /* Not match */
    NAS_MSCC_MLPL_MATCH_LVL_MCC         = 0x01,     /* MCC match */
    NAS_MSCC_MLPL_MATCH_LVL_MNC         = 0x02,     /* MNC match, ������ֻƥ��MNC�������MNC��Ҫ��MCC���*/
    NAS_MSCC_MLPL_MATCH_LVL_MCC_MNC     = 0x03,     /* MCC MNC match��ΪMCC 0x01��MNC 0x02����� */
    NAS_MSCC_MLPL_MATCH_LVL_LOC         = 0x04,     /* LOC match */
    NAS_MSCC_MLPL_MATCH_LVL_MCC_LOC     = 0x05,     /* MCC LOC match��ΪMCC 0x01��LOC 0x04����� */
    NAS_MSCC_MLPL_MATCH_LVL_MCC_MNC_LOC = 0x07,     /* MCC MNC LOC match��ΪMCC 0x01��MNC 0x02��LOC 0x05����� */
    NAS_MSCC_MLPL_MATCH_LVL_BUTT        = 0xFF
};
typedef VOS_UINT8 NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8;

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
    NAS_MSCC_MSPL_HIGHER_PRI_SRCH_TIME_ENUM_UINT8           enPriSrchTime;
    VOS_UINT8                                               aucRsv[3];
    VOS_UINT32                                              usMilliSec;
}NAS_MSPL_PRI_SRCH_TIME_MAP_MINUTE_STRU;


typedef struct
{
    VOS_UINT32                                              ulMcc;  /* NAS��ʽ��MCC������461: 0x00010604 */
    VOS_UINT8                                               ucIsMccValid;
    VOS_UINT8                                               ucSubNetMask;
    VOS_UINT8                                               aucRsv[2];
    VOS_UINT8                                               aucSectorId[NAS_MSCC_BYTES_IN_HRPD_SUBNET];
    NAS_MSCC_SYS_PRI_CLASS_ENUM_UINT8                       enPriClassCdma2000Hrpd;
    NAS_MSCC_SYS_PRI_CLASS_ENUM_UINT8                       enPriClassCdma2000Ai;
    VOS_UINT8                                               aucRsv1[2];
}NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU;
typedef struct
{
    VOS_RATMODE_ENUM_UINT32                                 enSysRat;
    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmnId;   /* NAS��ʽ��MCC��MNC������461 03: 0x00010604, 0x000f0300 */
    NAS_MSCC_SYS_PRI_CLASS_ENUM_UINT8                       enPriClass;
    VOS_UINT8                                               aucRsv[3];
}NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU;
typedef struct
{
    VOS_UINT32                                              ulMcc;  /* NAS��ʽ��MCC������461: 0x00010604 */
    VOS_UINT32                                              ulMnc;  /* NAS��ʽ��MNC������03 : 0x000f0300 */
    VOS_UINT16                                              usSid;
    VOS_UINT16                                              usNid;
    NAS_MSCC_SYS_PRI_CLASS_ENUM_UINT8                       enPriClassCdma2000Ai;
    NAS_MSCC_SYS_PRI_CLASS_ENUM_UINT8                       enPriClassCdma20001x;
    VOS_UINT8                                               ucIsMccValid;
    VOS_UINT8                                               ucIsMncValid;
}NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU;


typedef struct
{
    NAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM_UINT8                  enSysType;
    NAS_MSCC_MSPL_SYS_PRI_CLASS_ENUM_UINT8                  enPriClass;
    VOS_UINT8                                               aucRsv[2];
}NAS_MSCC_MSPL_SYS_INFO_STRU;


typedef struct
{
    VOS_UINT8                                               ucSysCount;
    VOS_UINT8                                               aucRsv[3];
    NAS_MSCC_MSPL_SYS_INFO_STRU                             astSysList[NAS_MSCC_MAX_NUM_MSPL_REC];
}NAS_MSCC_MSPL_SYS_LIST_INFO_STRU;


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

/* Public interface for other files start */
VOS_UINT8 NAS_MSCC_GetHigherPriMsplSysListThan3gpp(
    NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU               *pstIn3gppInfo,
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                       *pstOutSysList
);

VOS_UINT8 NAS_MSCC_GetHigherPriMsplSysListThan1x(
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                 *pstIn1xInfo,
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                       *pstOutSysList
);

VOS_UINT8 NAS_MSCC_GetHigherPriMsplSysListThanHrpd(
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstInHrpdInfo,
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                       *pstOutSysList
);

VOS_UINT32 NAS_MSCC_GetHigherPriMsplSysListThanHrpdBy1xLoc(
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                 *pstIn1xInfo,
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstInHrpdInfo,
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                       *pstOutSysList
);

VOS_UINT8 NAS_MSCC_GetMsplSysListBy1xLoc(
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                 *pstIn1xInfo,
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                       *pstOutSysList
);

VOS_UINT8 NAS_MSCC_GetCurr3gppSysBsrTimerLen(
    NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU               *pstIn3gppInfo,
    VOS_UINT32                                             *pusOutBsrTimerLenMilliSec
);

VOS_UINT8 NAS_MSCC_GetCurr1xSysBsrTimerLen(
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                 *pstIn1xInfo,
    VOS_UINT32                                             *pusOutBsrTimerLenMilliSec
);

VOS_UINT8 NAS_MSCC_GetCurrHrpdSysBsrTimerLen(
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstInHrpdInfo,
    VOS_UINT32                                             *pusOutBsrTimerLenMilliSec
);

VOS_UINT32 NAS_MSCC_GetCurrHrpdSysBsrTimerLenBy1xLoc(
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                 *pstIn1xInfo,
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstInHrpdInfo,
    VOS_UINT32                                             *pusOutBsrTimerLenMilliSec
);

NAS_MSCC_PARSE_MSPL_RSLT_ENUM_UINT32 NAS_MSCC_ParseMsplFile(
    VOS_UINT8                          *pucMsplBuff,
    VOS_UINT16                          usBuffSize
);

NAS_MSCC_PARSE_MLPL_RSLT_ENUM_UINT32 NAS_MSCC_ParseMlplFile(
    VOS_UINT8                          *pucMlplBuff,
    VOS_UINT16                          usBuffSize
);
/* Public interface for other files end */


/* Internal interface use in this file start */
VOS_UINT8 NAS_MSCC_GetMsplIndexBy3gppSys(
    NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU               *pstIn3gppInfo,
    NAS_MSCC_MLPL_STRU                                     *pstInMlplInfo,
    VOS_UINT8                                              *pucOutMsplIndex,
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                     *penOutMatchLvl
);

VOS_UINT8 NAS_MSCC_GetMsplIndexBy1xSys(
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                 *pstIn1xInfo,
    NAS_MSCC_MLPL_STRU                                     *pstInMlplInfo,
    VOS_UINT8                                              *pucOutMsplIndex,
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                     *penOutMatchLvl
);

VOS_UINT8 NAS_MSCC_GetMsplIndexByHrpdSys(
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstInHrpdInfo,
    NAS_MSCC_MLPL_STRU                                     *pstInMlplInfo,
    VOS_UINT8                                              *pucOutMsplIndex,
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                     *penOutMatchLvl
);

NAS_MSCC_MSPL_ID_STRU* NAS_MSCC_GetMsplTableByMsplIndex(
    NAS_MSCC_MSPL_STRU                                     *pstInMsplInfo,
    VOS_UINT8                                               ucInMsplIndex
);

VOS_VOID NAS_MSCC_Compare3gppSysWithMlplRec(
    NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU               *pstIn3gppInfo,
    NAS_MSCC_MLPL_RECORD_STRU                              *pstInMlplRec,
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                     *penOutMatchLvl
);

VOS_VOID NAS_MSCC_Compare1xSysWithMlplRec(
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                 *pstIn1xInfo,
    NAS_MSCC_MLPL_RECORD_STRU                              *pstInMlplRec,
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                     *penOutMatchLvl
);

VOS_VOID NAS_MSCC_CompareHrpdSysWithMlplRec(
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstInHrpdInfo,
    NAS_MSCC_MLPL_RECORD_STRU                              *pstInMlplRec,
    NAS_MSCC_MLPL_MATCH_LVL_ENUM_UINT8                     *penOutMatchLvl
);

VOS_UINT8 NAS_MSCC_Is3gppSysWithLocTagMatched(
    NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU               *pst3gppInfo,
    NAS_MSCC_MLPL_RECORD_STRU                              *pstMlplRec
);

VOS_UINT8  NAS_MSCC_Is1xSysWithLocTagMatched(
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                 *pst1xInfo,
    NAS_MSCC_MLPL_RECORD_STRU                              *pstMlplRec
);

VOS_UINT8  NAS_MSCC_IsHrpdSysWithLocTagMatched(
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstInHrpdInfo,
    NAS_MSCC_MLPL_RECORD_STRU                              *pstMlplRec
);

VOS_UINT8 NAS_MSCC_Get3gppMatchedMsplRecIndex(
    NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU               *pstIn3gppInfo,
    NAS_MSCC_MSPL_ID_STRU                                  *pstInMsplTable,
    VOS_UINT8                                              *pucOutMsplRecId
);

VOS_UINT8 NAS_MSCC_Get1xMatchedMsplRecIndex(
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                 *pstIn1xInfo,
    NAS_MSCC_MSPL_ID_STRU                                  *pstInMsplTable,
    VOS_UINT8                                              *pucOutMsplRecId
);

VOS_UINT8 NAS_MSCC_GetHrpdMatchedMsplRecIndex(
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstInHrpdInfo,
    NAS_MSCC_MSPL_ID_STRU                                  *pstInMsplTable,
    VOS_UINT8                                              *pucOutMsplRecId
);

VOS_UINT8 NAS_MSCC_Is3gppSysWithMsplRecMatched(
    NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU               *pst3gppInfo,
    NAS_MSCC_MSPL_REC_STRU                                 *pstMsplRec
);

VOS_UINT8 NAS_MSCC_Is1xSysWithMsplRecMatched(
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                 *pstIn1xInfo,
    NAS_MSCC_MSPL_REC_STRU                                 *pstMsplRec
);

VOS_UINT8 NAS_MSCC_IsHrpdSysWithMsplRecMatched(
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstHrpdInfo,
    NAS_MSCC_MSPL_REC_STRU                                 *pstMsplRec
);

VOS_VOID NAS_MSCC_GetHigherSysListThanSpecRecIndexSys(
    NAS_MSCC_MSPL_ID_STRU                                  *pstInMsplTable,
    VOS_UINT8                                               ucInCurrMsplRecId,
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                       *pstOutSysList
);

VOS_UINT8 NAS_MSCC_IsSysPlmnInLocTagPlmnRange(
    NAS_MSCC_PIF_PLMN_ID_STRU                              *pstSysPlmn,
    VOS_UINT8                                              *aucPlmnStart,
    VOS_UINT8                                               ucPlmnRange
);

VOS_UINT8 NAS_MSCC_IsSysSubnetIdWithLocTagMatched(
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU               *pstHrpdInfo,
    NAS_MSCC_MLPL_SYS_LOC_TAG_CDMA2000_HRPD_STRU           *pstLocTagHrpd
);

VOS_UINT8 NAS_MSCC_Is1xMncWithMlplMncMatched(
    VOS_UINT32                                              ul1xMnc,
    VOS_UINT16                                              usMlplMnc
);

VOS_UINT8 NAS_MSCC_IsMlplMsplSysTypeSupportLte(
    NAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM_UINT8                  enSysType
);

VOS_VOID NAS_MSCC_GeneratePrefPlmnList(
    NAS_MSCC_PIF_SIM_PLMN_WITH_RAT_STRU                     *pstOutPlmnList,
    VOS_UINT16                                              *pusOutPlmnCnt
);

VOS_UINT32 NAS_MSCC_ConvertMlplMccToNasStyleMcc(
    VOS_UINT16                          usMlplMcc
);

VOS_UINT32 NAS_MSCC_ConvertMlplMncToNasStyleMnc(
    VOS_UINT16                          usMlplMnc
);
/* Internal interface use in this file end */
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

#endif /* end of NasMsccMlplMsplApi.h */


