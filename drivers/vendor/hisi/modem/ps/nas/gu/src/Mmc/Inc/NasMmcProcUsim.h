

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#ifndef __NASMMCPROCUSIM_H__
#define __NASMMCPROCUSIM_H__


#include "NasMmlCtx.h"
#include "UsimPsInterface.h"
/* Added by x00314862 for CDMA Iteration 9 2015-2-5 begin */
#include "TafAppMma.h"
/* Added by x00314862 for CDMA Iteration 9 2015-2-5 end */




#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/

/* STK���� Network Search Mode Change Event ��غ궨�� */
#define MMC_STK_NET_SCH_MODE_MANUAL                         (0)
#define MMC_STK_NET_SCH_MODE_AUTO                           (1)

#define NAS_MMC_USIM_PSLOCI_LAC_POSITION_BEG                (10)                  /* ��Ϣ�б�ɾ����RAI��LAC���ֽڵ�ȡֵ       */
#define NAS_MMC_USIM_PSLOCI_LAC_POSITION_END                (11)

#define NAS_MMC_USIM_FILE_CONTENT_INVALID                   (0xFF)

#define NAS_MMC_PERI_HPLMN_ATTEMP_STEP_SIZE                 (6)                 /* ����HPLMN��������6����λ��λ���� */
#define NAS_MMC_MAX_PERI_HPLMN_ATTEMP_TIME_LEN              (480)               /* ����HPLMN�������8Сʱ */

#define NAS_MMC_MNC_LENGTH_INDICATOR_POSITION               (4)                 /* ָʾMNC���ȵ��ֽ���EF�ļ��е�λ�� */
#define NAS_MMC_MNC_LENGTH_TWO_BYTES_IN_IMSI                (2)                 /* MNC��IMSI�еĳ�����2 */
#define NAS_MMC_MNC_LENGTH_THREE_BYTES_IN_IMSI              (3)                 /* MNC��IMSI�еĳ�����3 */

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
    USIMM_CMDHEADER_CNF_STRU            stCmdResult;
    USIMM_FILEPATH_INFO_STRU            stFilePath;
    VOS_UINT16                          usRsv;
    VOS_UINT16                          usEfLen;
    VOS_UINT8                           ucRecordNum;
    VOS_UINT8                           ucTotalNum;
    VOS_UINT8                           ucSW1;
    VOS_UINT8                           ucSW2;
    VOS_UINT8                           aucEf[255];
}PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU;


/* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, begin */
typedef struct
{
    VOS_UINT16                          usEfNum;        /* ���µ��ļ��ĸ��� */
    VOS_UINT8                           aucRsv[2];      /* Ԥ������ */
    USIM_REFRESH_FILE_STRU              astRefreshFile[USIMM_MAX_REFRESH_FILE_NUM];
}NAS_MMC_USIMM_REFRESH_FILE_CONTENT_STRU;
/* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, end */

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_VOID  NAS_MMC_ConverPlmnInfoFromSim(
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulPlmnNum,
    NAS_MML_SIM_PLMN_WITH_RAT_STRU     *pstPlmnWithRat
);
VOS_VOID  NAS_MMC_ConvertSimPlmnToNasPLMN(
    NAS_MML_SIM_FORMAT_PLMN_ID          *pstSimPlmn,
    NAS_MML_PLMN_ID_STRU                *pstNasPlmn
);
VOS_VOID  NAS_MMC_ConvertNasPlmnToSimFormat(
    NAS_MML_PLMN_ID_STRU               *pstGUNasPlmn,
    NAS_MML_SIM_FORMAT_PLMN_ID         *pstSimPlmn
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU                   *pstMsg
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_CS_CKIK_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU                   *pstMsg
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_CS_KC_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU                   *pstMsg
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_CS_LOC_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU                   *pstMsg
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_EHPLMNPI_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU                   *pstMsg
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_EHPLMN_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_FORBIDDEN_PLMN_LIST_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
);
VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_HPLMN_PERI_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_HPLMN_SEL_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_LRPLMNSI_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_MNC_LENGTH_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_OPLMN_SEL_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_PLMN_SEL_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU           *pstMsg
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_PS_KC_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_PS_KEY_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU           *pstMsg
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_PS_LOC_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_UPLMN_SEL_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_ACTINGHPLMN_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
);

VOS_VOID NAS_MMC_SaveOperatorPlmnInfo(
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                          *pucData
);

VOS_VOID   NAS_MMC_SndUsimReadFileReq( VOS_VOID );

VOS_VOID NAS_MMC_SndUsimUpdateForbPlmnReq(VOS_VOID);

VOS_VOID  NAS_MMC_UpdateCsSecutityInfoFromUsimFile(
    VOS_UINT8                          *pucCsSecutityInfo
);

VOS_VOID  NAS_MMC_UpdateLaiFormCsLociFile(
    VOS_UINT8                          *pucCsLociFileContent
);

VOS_VOID  NAS_MMC_UpdatePsSecutityInfoFromUsimFile(
    VOS_UINT8                          *pucPsSecutityInfo
);

VOS_VOID  NAS_MMC_UpdatePtmsiFormPsLociFile(
    VOS_UINT8                          *pucPsLociFileContent
);

VOS_VOID  NAS_MMC_UpdatePtmsiSignatureFormPsLociFile(
    VOS_UINT8                          *pucPsLociFileContent
);

VOS_VOID  NAS_MMC_UpdateRaiFormPsLociFile(
    VOS_UINT8                          *pucPsLociFileContent
);

VOS_VOID  NAS_MMC_UpdateSimInfoFromCsLociFile(
    VOS_UINT8                          *pucCsLociFileContent
);

VOS_VOID  NAS_MMC_UpdateSimInfoFromPsLociFile(
    VOS_UINT8                          *pucPsLociFileContent
);

VOS_VOID  NAS_MMC_UpdateTmsiFormCsLociFile(
    VOS_UINT8                          *pucCsLociFileContent
);

TAF_PH_PLMN_SEL_MODE NAS_MMC_ConvertSrchModeToStkSrchMode(
   VOS_UINT8                            ucReselMode
);


VOS_VOID NAS_MMC_SndStkSearchModeChgEvt(
    VOS_UINT8                           ucReselMode
);

VOS_UINT32 NAS_MMC_IsNeedSndStkSearchModeChgEvt(VOS_VOID);

VOS_VOID  NAS_MMC_UpdateOPlmnInfoFromNvim(
    VOS_UINT8                          *pucOPlmnData,
    VOS_UINT16                          usOPlmnNum
);

/* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, Begin */
VOS_UINT8  NAS_MMC_GetUsimAllRefreshFileNumber(VOS_VOID);
VOS_UINT16  NAS_MMC_GetUsimAllRefreshFileId(VOS_UINT8 ucIndex);

VOS_VOID NAS_MMC_BuildRefreshFileList(
    USIMM_STKREFRESH_IND_STRU                   *pstUsimRefreshInd,
    NAS_MMC_USIMM_REFRESH_FILE_CONTENT_STRU     *pstRefreshFile
);

/* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, end */


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

