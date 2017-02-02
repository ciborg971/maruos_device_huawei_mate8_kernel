

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "PsTypeDef.h"
#include "NasMmSublayerDef.h"
#include "NasMmcProcUsim.h"
#include "NasMmcFsmSwitchOn.h"
#include "GmmExt.h"
#include "NasMmcCtx.h"
#include "NasMmlCtx.h"
#include "NasComm.h"
#include "NasMmlLib.h"
#include "siappstk.h"
#include "NasMmcComFunc.h"

#include "NasUsimmApi.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMCPROCUSIM_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, begin */
/* MMC �յ�USIMM_REFRESH_ALL_FILE��refresh��Ϣʱ��ֻ���¸����������ļ�
   ��6F7E����ע��ʱ��TMSI������ע��ʧ��  */
VOS_UINT16 g_astNasUsimAllRefreshFileID[] =
{
    USIMM_USIM_EFEHPLMN_ID,
    USIMM_USIM_EFHPLMNwACT_ID,
    USIMM_USIM_EFPLMNWACT_ID,
    USIMM_USIM_EFOPLMNWACT_ID,
    USIMM_USIM_EFFPLMN_ID
};

VOS_UINT16 g_astNasGsmAllRefreshFileID[] =
{
    USIMM_GSM_EFHPLMNACT_ID,
    USIMM_GSM_EFPLMNWACT_ID,
    USIMM_GSM_EFOPLMNWACT_ID,
    USIMM_GSM_EFPLMNSEL_ID,
    USIMM_GSM_EFFPLMN_ID
};

/* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, end */


/*lint -save -e958 */


VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_HPLMN_SEL_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
)
{
    NAS_MML_SIM_PLMN_WITH_RAT_STRU                         *pstHPlmnWithRatList = VOS_NULL_PTR;
    NAS_MML_SIM_HPLMN_WITH_RAT_INFO_STRU                   *pstHplmnWithRatInfo = VOS_NULL_PTR;
    VOS_UINT8                                               ucHplmnWithRat ;

    if ( VOS_OK == pstMsg->stCmdResult.ulResult )
    {
        /* ��ȡȫ�ֱ����ĵ�ַ */
        pstHplmnWithRatInfo = NAS_MML_GetSimHplmnWithRatList();
        pstHPlmnWithRatList = pstHplmnWithRatInfo->astHPlmnWithRatInfo;

        /* ��ʼ��ȫ�ֱ����е�HPLMN��Ϣ��Ȼ���SIM�ж�ȡ��PLMN ID��RAT�洢��ȫ�ֱ����� */
        NAS_MML_InitSimHPlmnWithRatInfo(pstHplmnWithRatInfo);

        ucHplmnWithRat = (VOS_UINT8)(pstMsg->usEfLen / NAS_MML_PLMN_WITH_RAT_UNIT_LEN);
        if ( ucHplmnWithRat > NAS_MML_MAX_HPLMN_WITH_RAT_NUM )
        {
            ucHplmnWithRat = NAS_MML_MAX_HPLMN_WITH_RAT_NUM;
        }

        /* ��USIM�б����PLMN��Ϣת��Ϊ�ڴ��е���Ϣ */
        NAS_MMC_ConverPlmnInfoFromSim(pstMsg->aucEf, ucHplmnWithRat, pstHPlmnWithRatList);

        /* ����PLMN�ĸ��� */
        pstHplmnWithRatInfo->ucHPlmnWithRatNum = ucHplmnWithRat;
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_HPLMN_SEL_FILE_ID:ERROR: Read SIM/USIM Mandatory File Error:");
    }

    return;
}


VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_FORBIDDEN_PLMN_LIST_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
)
{
    VOS_UINT8                           ucFplmnNum;
    VOS_UINT32                          ulTempData;
    VOS_UINT8                           ucTempNum;                              /* �洢׼MMC��forbidden PlMN��������ʱ����  */
    VOS_UINT32                          i;

    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo  = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstForbPlmnIdList  = VOS_NULL_PTR;

    if ( VOS_OK == pstMsg->stCmdResult.ulResult )
    {
        /* ��ȡ����SIM���н�ֹ��PLMN��ȫ�ֱ�����Ϣ */
        pstForbidPlmnInfo   = NAS_MML_GetForbidPlmnInfo();
        pstForbPlmnIdList   = pstForbidPlmnInfo->astForbPlmnIdList;

        if (( NAS_MML_SIM_FILE_LEN_VALID == ( pstMsg->usEfLen % NAS_MML_SIM_PLMN_ID_LEN)))
        {                                                                           /* ���ȺϷ�                                 */
            ucFplmnNum = (VOS_UINT8)(pstMsg->usEfLen / NAS_MML_SIM_PLMN_ID_LEN);

            /* ��MMLȫ�ֱ�����SIM��forbidden PLMN����   */
            pstForbidPlmnInfo->ucUsimForbPlmnNum = ucFplmnNum;

            if ( ucFplmnNum <= NAS_MML_MAX_FORBPLMN_NUM )
            {
                ucTempNum = ucFplmnNum;
            }
            else
            {
                ucTempNum = NAS_MML_MAX_FORBPLMN_NUM;
            }

            ucFplmnNum = 0;

            for (i = 0; i < ucTempNum; i++)
            {
                if ( (NAS_MMC_USIM_FILE_CONTENT_INVALID == pstMsg->aucEf[(i * NAS_MML_SIM_PLMN_ID_LEN)])
                  && (NAS_MMC_USIM_FILE_CONTENT_INVALID == pstMsg->aucEf[(i * NAS_MML_SIM_PLMN_ID_LEN) + 1])
                  && (NAS_MMC_USIM_FILE_CONTENT_INVALID == pstMsg->aucEf[(i * NAS_MML_SIM_PLMN_ID_LEN) + 2]) )
                {                                                                   /* ���ݷǷ�                                 */
                    continue;
                }

                /* ��ȫ�ֱ����е�PLMN��Ϣ��Ϊ0 */
                PS_MEM_SET(&(pstForbPlmnIdList[ucFplmnNum]), NAS_MML_PLMN_ID_ZERO, sizeof(NAS_MML_PLMN_ID_STRU));

                    /*
                       PLMN BCD ���� ��ʽ

                       MCC digit 2,  MCC digit 1, ----OCTET 1
                       MNC digit 3,  MCC digit 3, ----OCTET 2
                       MNC digit 2,  MNC digit 1, ----OCTET 3
                    */
                /* ��ȡSIM���еĹ��Һ� */
                ulTempData = NAS_MML_OCTET_LOW_FOUR_BITS & pstMsg->aucEf[i * NAS_MML_SIM_PLMN_ID_LEN];
                pstForbPlmnIdList[ucFplmnNum].ulMcc = ulTempData;

                ulTempData = (NAS_MML_OCTET_HIGH_FOUR_BITS & pstMsg->aucEf[i * NAS_MML_SIM_PLMN_ID_LEN]) >> NAS_MML_OCTET_MOVE_FOUR_BITS;
                pstForbPlmnIdList[ucFplmnNum].ulMcc |= (ulTempData << NAS_MML_OCTET_MOVE_EIGHT_BITS);

                ulTempData = NAS_MML_OCTET_LOW_FOUR_BITS & pstMsg->aucEf[(i * NAS_MML_SIM_PLMN_ID_LEN) + 1];
                pstForbPlmnIdList[ucFplmnNum].ulMcc |= (ulTempData << NAS_MML_OCTET_MOVE_SIXTEEN_BITS);

                /* ��ȡSIM���е������ */
                ulTempData = (NAS_MML_OCTET_HIGH_FOUR_BITS & pstMsg->aucEf[(i * NAS_MML_SIM_PLMN_ID_LEN) + 1]) >> NAS_MML_OCTET_MOVE_FOUR_BITS;
                pstForbPlmnIdList[ucFplmnNum].ulMnc |= (ulTempData << NAS_MML_OCTET_MOVE_SIXTEEN_BITS);

                ulTempData = NAS_MML_OCTET_LOW_FOUR_BITS & pstMsg->aucEf[(i * NAS_MML_SIM_PLMN_ID_LEN) + 2];
                pstForbPlmnIdList[ucFplmnNum].ulMnc |= ulTempData;

                ulTempData = (NAS_MML_OCTET_HIGH_FOUR_BITS & pstMsg->aucEf[(i * NAS_MML_SIM_PLMN_ID_LEN) + 2]) >> NAS_MML_OCTET_MOVE_FOUR_BITS;
                pstForbPlmnIdList[ucFplmnNum].ulMnc |= (ulTempData << NAS_MML_OCTET_MOVE_EIGHT_BITS);
                ucFplmnNum++;
            }

            /* ��ʼ��MMC��forbidden PLMN�ĸ��� */
            pstForbidPlmnInfo->ucForbPlmnNum = ucFplmnNum;
        }
        else
        {                                                                           /* ���ȷǷ�                                 */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_FORBIDDEN_PLMN_LIST_FILE_ID:ERROR: The length of USIM_READ_FILE_CNF is invalid.");
        }
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_FORBIDDEN_PLMN_LIST_FILE_ID:ERROR: Read SIM/USIM Mandatory File Error:");
    }

    return;
}


VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_UPLMN_SEL_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
)
{
    VOS_UINT8                           ucUplmnNum;

    NAS_MML_SIM_USERPLMN_INFO_STRU     *pstUserPlmnInfo = VOS_NULL_PTR;
    NAS_MML_SIM_PLMN_WITH_RAT_STRU     *pstUplmnAddr    = VOS_NULL_PTR;

    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        ucUplmnNum = (VOS_UINT8)(pstMsg->usEfLen / NAS_MML_PLMN_WITH_RAT_UNIT_LEN);

        if ( ucUplmnNum > NAS_MML_MAX_USERPLMN_NUM )
        {
            ucUplmnNum  = NAS_MML_MAX_USERPLMN_NUM;
        }

        /* ��ȡȫ�ֱ����ĵ�ַ */
        pstUserPlmnInfo = NAS_MML_GetSimUserPlmnList();
        pstUplmnAddr    = pstUserPlmnInfo->astUserPlmnInfo;

        /* ��ʼ��ȫ�ֱ����е�UPLMN��Ϣ��Ȼ���SIM�ж�ȡ��PLMN ID��RAT�洢��ȫ�ֱ����� */
        NAS_MML_InitSimUserPlmnInfo(pstUserPlmnInfo);

        /* ��USIM�б����PLMN��Ϣת��Ϊ�ڴ��е���Ϣ */
        NAS_MMC_ConverPlmnInfoFromSim(pstMsg->aucEf, ucUplmnNum, pstUplmnAddr);

        /* ����UPLMN�ĸ��� */
        pstUserPlmnInfo->ucUserPlmnNum = ucUplmnNum;
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_FORBIDDEN_PLMN_LIST_FILE_ID:ERROR: Read SIM/USIM Mandatory File Error:");
    }

    return;
}


VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_OPLMN_SEL_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usOplmnNum;
    NAS_MML_SIM_OPERPLMN_INFO_STRU     *pstOperPlmnInfo = VOS_NULL_PTR;
    NAS_MML_SIM_PLMN_WITH_RAT_STRU     *pstOplmnAddr    = VOS_NULL_PTR;

    ulRet                               = VOS_TRUE;

    ulRet = NAS_MML_IsNvimOplmnAvail();

    /* ����û����õ�OPLMN��Ч����Ҫ��NV�е�OPLMN�б��浽MMLȫ�ֱ����� */
    if (ulRet == VOS_TRUE)
    {
        return;
    }
    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        usOplmnNum = (VOS_UINT16)(pstMsg->usEfLen / NAS_MML_PLMN_WITH_RAT_UNIT_LEN);

        if ( usOplmnNum > NAS_MML_MAX_OPERPLMN_NUM )
        {
            usOplmnNum = NAS_MML_MAX_OPERPLMN_NUM;
        }

        /* ��ȡȫ�ֱ����ĵ�ַ */
        pstOperPlmnInfo = NAS_MML_GetSimOperPlmnList();
        pstOplmnAddr    = pstOperPlmnInfo->astOperPlmnInfo;

        /* ��ʼ��ȫ�ֱ����е�OPLMN��Ϣ��Ȼ���SIM�ж�ȡ��PLMN ID��RAT�洢��ȫ�ֱ����� */
        NAS_MML_InitSimOperPlmnInfo(pstOperPlmnInfo);

        /* ��USIM�б����PLMN��Ϣת��Ϊ�ڴ��е���Ϣ */
        NAS_MMC_ConverPlmnInfoFromSim(pstMsg->aucEf, usOplmnNum, pstOplmnAddr);

        /* ����OPLMN�ĸ��� */
        pstOperPlmnInfo->usOperPlmnNum = usOplmnNum;
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_OPLMN_SEL_FILE_ID:ERROR: Read SIM/USIM Mandatory File Error:");
    }

    return;
}


VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_LRPLMNSI_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
)
{
    NAS_MML_LAST_RPLMN_SEL_IND_ENUM_UINT8                  *penPLMNSelInd = VOS_NULL_PTR;
    NAS_MML_SIM_EHPLMN_INFO_STRU                           *pstEHPlmnInfo = VOS_NULL_PTR;

    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        pstEHPlmnInfo   = NAS_MML_GetSimEhplmnList();
        penPLMNSelInd   = &(pstEHPlmnInfo->enPLMNSelInd);

        *penPLMNSelInd  = NAS_MML_LRPLMN_SELECTION_IND_INVALID;

        if ( (NAS_MML_LRPLMNSI_SIM_FILE_LEN == pstMsg->usEfLen)
          && (NAS_MML_LRPLMN_SELECTION_IND_VALID == pstMsg->aucEf[0]) )
        {
            *penPLMNSelInd = NAS_MML_LRPLMN_SELECTION_IND_VALID;
        }
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_LRPLMNSI_FILE_ID:ERROR: Read SIM/USIM Mandatory File Error:");
    }

    return;

}

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_EHPLMNPI_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
)
{
    NAS_MML_SIM_EHPLMN_INFO_STRU                           *pstEHPlmnInfo       = VOS_NULL_PTR;
    NAS_MML_EHPLMN_PRESENT_IND_ENUM_UINT8                  *penEHplmnPresentInd = VOS_NULL_PTR;

    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        /* ȡ��ȫ�ֱ�����ַ */
        pstEHPlmnInfo                       = NAS_MML_GetSimEhplmnList();
        penEHplmnPresentInd                 = &(pstEHPlmnInfo->enEHplmnPresentInd);

        if ( NAS_MML_EHPLMNPI_SIM_FILE_LEN == pstMsg->usEfLen )
        {
            *penEHplmnPresentInd        = pstMsg->aucEf[0];
        }
        else
        {
            *penEHplmnPresentInd        = NAS_MML_EHPLMN_PRESENT_IND_NO_PREF;
        }
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_EHPLMNPI_FILE_ID:ERROR: Read SIM/USIM Mandatory File Error:");
    }

    return;


}
VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_EHPLMN_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
)
{
    NAS_MML_PLMN_ID_STRU                stPlmn;
    VOS_UINT32                          ulEHplmnNum;
    VOS_UINT32                          i;
    NAS_MML_SIM_FORMAT_PLMN_ID          stSimPlmn;

    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstSimEHPlmnInfo = VOS_NULL_PTR;

    NAS_MML_SIM_EHPLMN_INFO_STRU        stTempSimEHPlmnInfo;

    VOS_UINT8                           ucUserCfgEhplmnListNum;
    NAS_MML_PLMN_ID_STRU                astUserCfgEhPlmnList[NAS_MML_MAX_USER_CFG_EHPLMN_NUM];

    VOS_UINT8                           ucSimEhplmnListNum;
    NAS_MML_PLMN_ID_STRU                astSimEhPlmnList[NAS_MML_MAX_EHPLMN_NUM];

    PS_MEM_SET(&stPlmn, 0, sizeof(NAS_MML_PLMN_ID_STRU));
    PS_MEM_SET(&stSimPlmn, 0, sizeof(NAS_MML_SIM_FORMAT_PLMN_ID));
    PS_MEM_SET(&stTempSimEHPlmnInfo, 0, sizeof(NAS_MML_SIM_EHPLMN_INFO_STRU));

    ucSimEhplmnListNum                  = 0;
    PS_MEM_SET(astUserCfgEhPlmnList, (VOS_UINT)0X00, sizeof(astUserCfgEhPlmnList));

    ucUserCfgEhplmnListNum              = 0;
    PS_MEM_SET(astSimEhPlmnList, (VOS_UINT)0X00, sizeof(astSimEhPlmnList));

    pstSimEHPlmnInfo = NAS_MML_GetSimEhplmnList();

    /* �����ǰΪACTING-HPLMN���򲻸��� */
    if ( NAS_MML_HPLMN_TYPE_ACTING_HPLMN == NAS_MML_GetHPlmnType())
    {
        return;
    }

    /* �����ļ�ʧ�� */
    if (VOS_OK != pstMsg->stCmdResult.ulResult)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_EHPLMN_FILE_ID:ERROR: Read SIM/USIM Mandatory File Error:");
        return;
    }

    /* ��ȡ�Ŀ��ļ����Ȳ��Ϸ���ֱ�ӷ���VOS_FALSE */
    if ((pstMsg->usEfLen < NAS_MML_SIM_PLMN_ID_LEN)
     || (NAS_MML_SIM_FILE_LEN_VALID != (pstMsg->usEfLen % NAS_MML_SIM_PLMN_ID_LEN)))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_EHPLMN_FILE_ID:WARNING: The length of USIM_READ_FILE_CNF is invalid.");
        return;
    }

    ulEHplmnNum = (VOS_UINT32) (pstMsg->usEfLen / NAS_MML_SIM_PLMN_ID_LEN);

    if (ulEHplmnNum > NAS_MML_MAX_EHPLMN_NUM)
    {
        ulEHplmnNum = NAS_MML_MAX_EHPLMN_NUM;
    }


    /* ��ʼ��EHPLMN��Ϣ��Ȼ���SIM�ж�ȡ��PLMN ID��RAT�洢��ȫ�ֱ����� */
    NAS_MML_InitSimEhPlmnInfo(&stTempSimEHPlmnInfo);

    /* ȡ���û�NV�����õ�EHplmn��Ϣ���û����õ�EHplmn��Ϣ����SIM���е�EHPLMN */
    NAS_MML_GetValidUserCfgEhplmnInfo( NAS_MML_GetSimImsi(),
                                       &ucUserCfgEhplmnListNum,
                                       astUserCfgEhPlmnList );

    /* ���û�NV�����õ�EHplmn��Ϣ���뵽SIM�е�EHPLMN��Ϣ�� */
    NAS_MMC_AddPlmnListIntoSimEhplmnInfo( ucUserCfgEhplmnListNum,
                                          astUserCfgEhPlmnList,
                                          NAS_MMC_PLMN_TYPE_HPLMN,
                                          &stTempSimEHPlmnInfo);


    /* ��USIM�б����PLMN��Ϣת��Ϊ�ڴ��е���Ϣ */
    for ( i = 0; i < ulEHplmnNum; i++ )
    {
        PS_MEM_CPY(stSimPlmn.aucSimPlmn, pstMsg->aucEf + (NAS_MML_SIM_PLMN_ID_LEN * i), NAS_MML_SIM_PLMN_ID_LEN);
        NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmn, &stPlmn);

        if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&stPlmn))
        {
            astSimEhPlmnList[ucSimEhplmnListNum] = stPlmn;
            ucSimEhplmnListNum++;
        }
    }

    NAS_MMC_AddPlmnListIntoSimEhplmnInfo( ucSimEhplmnListNum,
                                          astSimEhPlmnList,
                                          NAS_MMC_PLMN_TYPE_HPLMN,
                                          &stTempSimEHPlmnInfo);


    /* NV�����õĺͿ��ļ��е�EHplmn���ܸ���Ϊ0������ʹ��IMSI�е�HOME PLMN */
    if ( 0 == stTempSimEHPlmnInfo.ucEhPlmnNum)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_EHPLMN_FILE_ID:WARNING: VALID EHplmn number is zero.");

        /* ���µ�ǰHPLMN������ */
        NAS_MML_SetHPlmnType(NAS_MML_HPLMN_TYPE_HPLMN);

        NAS_MMC_UpdateHomePlmn( NAS_MML_GetSimImsi() );

        return;
    }


    /* ���µ�ǰHPLMN������ */
    NAS_MML_SetHPlmnType(NAS_MML_HPLMN_TYPE_EHPLMN);

    /* NV�����õĺͿ��ļ��е�EHplmn���ܸ�����Ϊ0������������Ч��EHplmn��Ϣ
       ���µ��ڴ���ȥ */
    pstSimEHPlmnInfo->ucEhPlmnNum = stTempSimEHPlmnInfo.ucEhPlmnNum;

    PS_MEM_CPY(pstSimEHPlmnInfo->astEhPlmnInfo,
               stTempSimEHPlmnInfo.astEhPlmnInfo,
               sizeof(pstSimEHPlmnInfo->astEhPlmnInfo));

    return;
}
VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_HPLMN_PERI_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
)
{
    NAS_MML_BG_SEARCH_CFG_INFO_STRU    *pstBgSearchCfg = VOS_NULL_PTR;

    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        pstBgSearchCfg = NAS_MML_GetBgSearchCfg();

        if (NAS_MML_HPLMN_PERI_FILE_LEN == pstMsg->usEfLen)
        {
            /*Э��23.011�涨������������Ϊ8Сʱ������Э��31.102��
              �������ĸ�ֵΪ16����������˵���ֵ���ڵ���30ʱ��ʹ��Ĭ
              ��ֵ60min
              31.102�涨��6F31����ļ��ĵ�һ���ֽڱ�ʾʱ������λΪ6����
            */
            if ( pstMsg->aucEf[0] > (NAS_MMC_MAX_PERI_HPLMN_ATTEMP_TIME_LEN/NAS_MMC_PERI_HPLMN_ATTEMP_STEP_SIZE) )
            {
                /* orange����:����Ӫ�̶���ʱ����SIM���е�ֵ����Чֵʱ��
                   ��NV�л�ȡ��Ĭ��ֵ��18���� */
                if (VOS_TRUE == pstBgSearchCfg->stDefaultMaxHplmnTimerPeriod.ucNvimActiveFlg)
                {
                    /* Orang����:  ��Ӫ�̶���ֵ*60��*1000���� */
                    NAS_MML_SetSimHplmnTimerLen(pstBgSearchCfg->stDefaultMaxHplmnTimerPeriod.ulDefaultMaxHplmnLen);
                }
                else
                {
                    /* Ĭ��ֵΪ60����*60��*1000���� */
                    NAS_MML_SetSimHplmnTimerLen(NAS_MML_SIXTY_MINUTE * NAS_MML_SIXTY_SECOND * NAS_MML_ONE_THOUSAND_MILLISECOND);
                }
            }
            else
            {
                /* SIM��ȡֵ*6����*60��*1000���� */
                NAS_MML_SetSimHplmnTimerLen(pstMsg->aucEf[0] * NAS_MMC_PERI_HPLMN_ATTEMP_STEP_SIZE * NAS_MML_SIXTY_SECOND * NAS_MML_ONE_THOUSAND_MILLISECOND);
            }
        }
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_HPLMN_PERI_FILE_ID:ERROR: Read SIM/USIM Mandatory File Error:");
    }

    return;
}
VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_MNC_LENGTH_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
)
{
    VOS_UINT8                           ucExactlyComparaFlag;

    ucExactlyComparaFlag = NAS_MML_GetPlmnExactlyComparaFlg();

    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        /* 31.102,4.2.18�½ڣ�SIM���ļ����Ȳ�С��3 */
        if ( pstMsg->usEfLen < 3 )
        {
            PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mmc_RcvAgentUsimReadFileCnf:WARNING: The length of USIM_READ_FILE_CNF(MNC length) is invalid.");
        }
        else if ( 3 == pstMsg->usEfLen )
        {
            /* 31.102,4.2.18�½ڣ�SIM���ļ��ĵ�һ���ֽڱ�ʾOperation mode */
            NAS_MML_SetUeOperMode(pstMsg->aucEf[0]);
        }
        else
        {
            /* 31.102,4.2.18�½ڣ�SIM���ļ��ĵ�һ���ֽڱ�ʾOperation mode */
            NAS_MML_SetUeOperMode(pstMsg->aucEf[0]);
            if (( NAS_MMC_MNC_LENGTH_TWO_BYTES_IN_IMSI == (pstMsg->aucEf[NAS_MMC_MNC_LENGTH_INDICATOR_POSITION-1] & NAS_MML_OCTET_LOW_FOUR_BITS) )
            || ( NAS_MMC_MNC_LENGTH_THREE_BYTES_IN_IMSI == (pstMsg->aucEf[NAS_MMC_MNC_LENGTH_INDICATOR_POSITION-1] & NAS_MML_OCTET_LOW_FOUR_BITS) ))
            {
                if (VOS_TRUE == ucExactlyComparaFlag)
                {
                    NAS_MML_SetUsimMncLen(pstMsg->aucEf[NAS_MMC_MNC_LENGTH_INDICATOR_POSITION-1] & NAS_MML_OCTET_LOW_FOUR_BITS);
                }
            }
            else
            {
                PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mmc_RcvAgentUsimReadFileCnf:WARNING: The value of USIM_READ_FILE_CNF(MNC length) is invalid.");
            }
        }
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_MNC_LENGTH_FILE_ID:ERROR: Read SIM/USIM Mandatory File Error:");
    }

    return;
}
VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_CS_LOC_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
)
{
    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        if (NAS_MML_CS_LOCI_SIM_FILE_LEN == pstMsg->usEfLen)
        {
            NAS_MMC_UpdateSimInfoFromCsLociFile(pstMsg->aucEf);
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_CS_LOC_FILE_ID:WARNING: The length of USIM_READ_FILE_CNF(CS location info) is invalid.");
        }
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_CS_LOC_FILE_ID:ERROR: Read SIM/USIM Mandatory File Error:");
    }

    return;
}


VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_CS_CKIK_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
)
{
    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        if ( NAS_MML_CS_KEY_USIM_FILE_LEN == pstMsg->usEfLen)
        {
            NAS_MMC_UpdateCsSecutityInfoFromUsimFile(pstMsg->aucEf);
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_CS_CKIK_FILE_ID:WARNING: The length of USIM_READ_FILE_CNF(CS CK and IK) is invalid.");
        }
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_CS_CKIK_FILE_ID:ERROR: Read SIM/USIM Mandatory File Error:");
    }

    return;
}


VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_CS_KC_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
)
{
    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        if ( NAS_MML_CS_KC_SIM_FILE_LEN == pstMsg->usEfLen )
        {
            NAS_MMC_UpdateCsSecutityInfoFromUsimFile(pstMsg->aucEf);
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "Mmc_RcvAgentUsimReadFileCnf:WARNING: The length of USIM_READ_FILE_CNF(CS KC) is invalid.");
        }
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "Mmc_RcvAgentUsimReadFileCnf:ERROR: Read SIM/USIM Mandatory File Error:");
    }

    return;
}


VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_PS_KEY_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU           *pstMsg
)
{
    if (VOS_OK == pstMsg->stCmdResult.ulResult)

    {
        if ( NAS_MML_PS_KEY_USIM_FILE_LEN == pstMsg->usEfLen )
        {
            NAS_MMC_UpdatePsSecutityInfoFromUsimFile(pstMsg->aucEf);
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_PS_KEY_FILE_ID:WARNING: The length of USIM_READ_FILE_CNF(PS key) is invalid.");
        }
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_PS_KEY_FILE_ID:ERROR: Read SIM/USIM Mandatory File Error:");
    }

    return;
}


VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_PS_KC_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
)
{
    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        if ( NAS_MML_PS_KC_SIM_FILE_LEN == pstMsg->usEfLen )
        {
            NAS_MMC_UpdatePsSecutityInfoFromUsimFile(pstMsg->aucEf);
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_PS_KC_FILE_ID:WARNING: The length of USIM_READ_FILE_CNF(PS KC) is invalid.");
        }
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_PS_KC_FILE_ID:ERROR: Read SIM/USIM Mandatory File Error:");
    }

    return;
}


VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_PS_LOC_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
)
{
    VOS_UINT8                           aucPsLocInfo[NAS_MML_PS_LOCI_SIM_FILE_LEN];

    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        if ( NAS_MML_PS_LOCI_SIM_FILE_LEN == pstMsg->usEfLen )
        {
            PS_MEM_SET(aucPsLocInfo, (VOS_CHAR)0xFF, NAS_MML_PS_LOCI_SIM_FILE_LEN);

            PS_MEM_CPY(aucPsLocInfo, pstMsg->aucEf, pstMsg->usEfLen );

            /*����MML��GMMȫ�ֱ������������*/
            NAS_MMC_UpdateSimInfoFromPsLociFile(aucPsLocInfo);
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_PS_LOC_FILE_ID:WARNING: The length of USIM_READ_FILE_CNF(PS location info) is invalid.");
        }
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_PS_LOC_FILE_ID:ERROR: Read SIM/USIM Mandatory File Error:");
    }

    return;
}




VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_PLMN_SEL_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU           *pstMsg
)
{
    VOS_UINT8                           ucPlmnSetNum;
    VOS_UINT32                          i;
    NAS_MML_SIM_FORMAT_PLMN_ID          stSimPlmn;

    NAS_MML_SIM_SELPLMN_INFO_STRU      *pstSelPlmnInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstPlmnSelList = VOS_NULL_PTR;

    PS_MEM_SET(&stSimPlmn, 0, sizeof(NAS_MML_SIM_FORMAT_PLMN_ID));

    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        ucPlmnSetNum   = (VOS_UINT8)(pstMsg->usEfLen / NAS_MML_SIM_PLMN_ID_LEN);
        if ( ucPlmnSetNum > NAS_MML_MAX_SELPLMN_NUM )
        {
            ucPlmnSetNum = NAS_MML_MAX_SELPLMN_NUM;
        }

        pstSelPlmnInfo = NAS_MML_GetSimSelPlmnList();
        pstPlmnSelList = pstSelPlmnInfo->astPlmnId;

        /* ��ʼ��ȫ�ֱ����е�UPLMN��Ϣ��Ȼ���SIM�ж�ȡ��PLMN ID�洢��ȫ�ֱ����� */
        NAS_MML_InitSimSelPlmnInfo(pstSelPlmnInfo);

        for ( i = 0; i < ucPlmnSetNum; i++ )
        {
            PS_MEM_CPY(stSimPlmn.aucSimPlmn, pstMsg->aucEf + (NAS_MML_SIM_PLMN_ID_LEN * i), NAS_MML_SIM_PLMN_ID_LEN);

            NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmn, &pstPlmnSelList[i]);
        }

        /* ����SELPLMN�ĸ��� */
        pstSelPlmnInfo->ucSelPlmnNum = ucPlmnSetNum;
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_PLMN_SEL_FILE_ID:ERROR: Read SIM/USIM Mandatory File Error:");
    }

    return;
}
VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_ACTINGHPLMN_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU                   *pstMsg
)
{
    NAS_MML_PLMN_ID_STRU                stPlmn;
    NAS_MML_SIM_FORMAT_PLMN_ID          stSimPlmn;
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstEHPlmnInfo   = VOS_NULL_PTR;
    NAS_MML_SIM_MS_IDENTITY_STRU       *pstMsIdentity   = VOS_NULL_PTR;

    PS_MEM_SET(&stPlmn, 0, sizeof(NAS_MML_PLMN_ID_STRU));
    PS_MEM_SET(&stSimPlmn, 0, sizeof(NAS_MML_SIM_FORMAT_PLMN_ID));

    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        if (pstMsg->usEfLen >= NAS_MML_SIM_PLMN_ID_LEN)
        {
            PS_MEM_CPY(stSimPlmn.aucSimPlmn, pstMsg->aucEf, NAS_MML_SIM_PLMN_ID_LEN);
            NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmn, &stPlmn);

            if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&stPlmn))
            {
                pstEHPlmnInfo = NAS_MML_GetSimEhplmnList();

                /* ��ʼ��ȫ�ֱ����е�EHPLMN��Ϣ */
                NAS_MML_InitSimEhPlmnInfo(pstEHPlmnInfo);

                pstEHPlmnInfo->ucEhPlmnNum                  = 1;
                pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId    = stPlmn;

                /* ���µ�ǰHPLMN������ */
                NAS_MML_SetHPlmnType(NAS_MML_HPLMN_TYPE_ACTING_HPLMN);

                return;
            }
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_ACTINGHPLMN_FILE_ID:WARNING: The length of USIM_READ_FILE_CNF is invalid.");
        }
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAgentUsimReadFileCnf_ACTINGHPLMN_FILE_ID:ERROR: Read SIM/USIM Mandatory File Error:");
    }

    pstMsIdentity = NAS_MML_GetSimMsIdentity();

    /* ACTING-HPLMN��ȡʧ�ܻ���Ч����Ҫ��HPLMN����ΪIMSI�е�HPLMN */
    NAS_MMC_UpdateHomePlmn(pstMsIdentity->aucImsi);

    /* ���µ�ǰHPLMN������ */
    NAS_MML_SetHPlmnType(NAS_MML_HPLMN_TYPE_HPLMN);

    return;

}

VOS_VOID  NAS_MMC_RcvAgentUsimReadFileCnf(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU           *pstMsg
)
{
    USIMM_DEF_FILEID_ENUM_UINT32        enEfId;

    if (VOS_OK != USIMM_ChangePathToDefFileID(USIMM_GUTL_APP, pstMsg->stFilePath.ulPathLen, pstMsg->stFilePath.acPath, &enEfId))
    {
        return;
    }

    switch ( enEfId )
    {
        /* Modified by h00313353 for iteration 9, 2015-2-11, begin */
        case USIMM_USIM_EFHPLMNwACT_ID:
        case USIMM_GSM_EFHPLMNACT_ID:
        /* Modified by h00313353 for iteration 9, 2015-2-11, end */
            NAS_MMC_RcvAgentUsimReadFileCnf_HPLMN_SEL_FILE_ID(pstMsg);
            break;

        /* Modified by h00313353 for iteration 9, 2015-2-11, begin */
        case USIMM_USIM_EFFPLMN_ID:
        case USIMM_GSM_EFFPLMN_ID:
        /* Modified by h00313353 for iteration 9, 2015-2-11, end */
            NAS_MMC_RcvAgentUsimReadFileCnf_FORBIDDEN_PLMN_LIST_FILE_ID(pstMsg);
            break;

        /* Modified by h00313353 for iteration 9, 2015-2-11, begin */
        case USIMM_USIM_EFPLMNWACT_ID:
        case USIMM_GSM_EFPLMNWACT_ID:
        /* Modified by h00313353 for iteration 9, 2015-2-11, end */
            NAS_MMC_RcvAgentUsimReadFileCnf_UPLMN_SEL_FILE_ID(pstMsg);
            break;

        /* Modified by h00313353 for iteration 9, 2015-2-11, begin */
        case USIMM_USIM_EFOPLMNWACT_ID:
        case USIMM_GSM_EFOPLMNWACT_ID:
        /* Modified by h00313353 for iteration 9, 2015-2-11, end */
            NAS_MMC_RcvAgentUsimReadFileCnf_OPLMN_SEL_FILE_ID(pstMsg);
            break;

        /* Modified by h00313353 for iteration 9, 2015-2-11, begin */
        case USIMM_USIM_EFHPPLMN_ID:
        case USIMM_GSM_EFHPLMN_ID:
        /* Modified by h00313353 for iteration 9, 2015-2-11, end */
            NAS_MMC_RcvAgentUsimReadFileCnf_HPLMN_PERI_FILE_ID(pstMsg);
            break;

        /* Modified by h00313353 for iteration 9, 2015-2-11, begin */
        case USIMM_USIM_EFAD_ID:
        case USIMM_GSM_EFAD_ID:
        /* Modified by h00313353 for iteration 9, 2015-2-11, end */
            NAS_MMC_RcvAgentUsimReadFileCnf_MNC_LENGTH_FILE_ID(pstMsg);
            break;

        /* Modified by h00313353 for iteration 9, 2015-2-11, begin */
        case USIMM_USIM_EFLOCI_ID:
        case USIMM_GSM_EFLOCI_ID:
        /* Modified by h00313353 for iteration 9, 2015-2-11, end */
            NAS_MMC_RcvAgentUsimReadFileCnf_CS_LOC_FILE_ID(pstMsg);
            break;

        /* Modified by h00313353 for iteration 9, 2015-2-11, begin */
        case USIMM_USIM_EFKEYS_ID:
        /* Modified by h00313353 for iteration 9, 2015-2-11, end */
            NAS_MMC_RcvAgentUsimReadFileCnf_CS_CKIK_FILE_ID(pstMsg);
            break;

        /* ���Ӷ�SIM���е�cskc�ļ���ȡ */
        /* Modified by h00313353 for iteration 9, 2015-2-11, begin */
        case USIMM_GSM_EFKC_ID:
        /* Modified by h00313353 for iteration 9, 2015-2-11, end */
            NAS_MMC_RcvAgentUsimReadFileCnf_CS_KC_FILE_ID(pstMsg);
            break;

        /* Modified by h00313353 for iteration 9, 2015-2-11, begin */
        case USIMM_USIM_EFKEYSPS_ID:
        /* Modified by h00313353 for iteration 9, 2015-2-11, end */
            NAS_MMC_RcvAgentUsimReadFileCnf_PS_KEY_FILE_ID(pstMsg);
            break;

        /* ���Ӷ�SIM���е�PSkc�ļ���ȡ���� */
        /* Modified by h00313353 for iteration 9, 2015-2-11, begin */
        case USIMM_GSM_EFKCGPRS_ID:
        /* Modified by h00313353 for iteration 9, 2015-2-11, end */
            NAS_MMC_RcvAgentUsimReadFileCnf_PS_KC_FILE_ID(pstMsg);
            break;

        /* Modified by h00313353 for iteration 9, 2015-2-11, begin */
        case USIMM_USIM_EFPSLOCI_ID:
        case USIMM_GSM_EFLOCIGPRS_ID:
        /* Modified by h00313353 for iteration 9, 2015-2-11, end */
            NAS_MMC_RcvAgentUsimReadFileCnf_PS_LOC_FILE_ID(pstMsg);
            break;

        /* ���Ӷ�SIM���е�cskc�ļ���ȡ */
        /* Modified by h00313353 for iteration 9, 2015-2-11, begin */
        case USIMM_GSM_EFPLMNSEL_ID:
        /* Modified by h00313353 for iteration 9, 2015-2-11, end */
            NAS_MMC_RcvAgentUsimReadFileCnf_PLMN_SEL_FILE_ID(pstMsg);
            break;

        /* Modified by h00313353 for iteration 9, 2015-2-11, begin */
        case USIMM_USIM_EFEHPLMN_ID:
        /* Modified by h00313353 for iteration 9, 2015-2-11, end */
            NAS_MMC_RcvAgentUsimReadFileCnf_EHPLMN_FILE_ID(pstMsg);
            break;

        /* Modified by h00313353 for iteration 9, 2015-2-11, begin */
        case USIMM_ATTGSM_EFACTINGHPLMN_ID:
        case USIMM_ATTUSIM_EFACTINGHPLMN_ID:
        /* Modified by h00313353 for iteration 9, 2015-2-11, end */

            NAS_MMC_RcvAgentUsimReadFileCnf_ACTINGHPLMN_FILE_ID(pstMsg);
            break;

        /* Modified by h00313353 for iteration 9, 2015-2-11, begin */
        case USIMM_USIM_EFEHPLMNPI_ID:
        /* Modified by h00313353 for iteration 9, 2015-2-11, end */
            NAS_MMC_RcvAgentUsimReadFileCnf_EHPLMNPI_FILE_ID(pstMsg);
            break;

        /* Modified by h00313353 for iteration 9, 2015-2-11, begin */
        case USIMM_USIM_EFLRPLMNSI_ID:
        /* Modified by h00313353 for iteration 9, 2015-2-11, end */
            NAS_MMC_RcvAgentUsimReadFileCnf_LRPLMNSI_FILE_ID(pstMsg);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "Mmc_RcvAgentUsimReadFileCnf:WARNING: File Id Abnormal");
            break;
    }

    return ;

}



VOS_VOID  NAS_MMC_UpdatePtmsiFormPsLociFile(
    VOS_UINT8                          *pucPsLociFileContent
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           ucInvalidCnt;
    NAS_MML_SIM_MS_IDENTITY_STRU       *pstMsIdentity;

    NAS_MML_SIM_FORMAT_PLMN_ID          stSimPlmnId;
    NAS_MML_PLMN_ID_STRU                stPlmnId;
    VOS_UINT8                           ucCurrPos;
    VOS_UINT32                          ulValidPtmsiFlag;

    PS_MEM_SET(&stSimPlmnId, 0, sizeof(NAS_MML_SIM_FORMAT_PLMN_ID));
    PS_MEM_SET(&stPlmnId, 0, sizeof(NAS_MML_PLMN_ID_STRU));

    /* Ĭ��PTMSI��Ч */
    ulValidPtmsiFlag    = VOS_TRUE;

    ucInvalidCnt        = 0;
    pstMsIdentity       = NAS_MML_GetSimMsIdentity();

    /* λ������Ч,��PTMSI�����ݿ϶�����Ч��,ֱ�ӷ��� */
    if ( (NAS_MML_LAC_LOW_BYTE_INVALID == pucPsLociFileContent[NAS_MMC_USIM_PSLOCI_LAC_POSITION_BEG])
      && ( (NAS_MML_LAC_LOW_BYTE_INVALID == pucPsLociFileContent[NAS_MMC_USIM_PSLOCI_LAC_POSITION_END])
        || (NAS_MML_LAC_HIGH_BYTE_INVALID == pucPsLociFileContent[NAS_MMC_USIM_PSLOCI_LAC_POSITION_END])))
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdatePtmsiFormPsLociFile:invalid LAC FFFF OR FFFE");


        /* ����ֱ��RETURN,����Ҫ��ʾ�ĸ��µ�ǰ��PTMSIΪ��Чֵ��Ʃ��NV�еı����
          ����Ч�ģ����ļ��е�����Ч�ģ���������ȡ��Ϊ׼ */
        ulValidPtmsiFlag = VOS_FALSE;
    }


    /* λ����������Ϊȫ0������ΪRAI��Ч,��PTMSI�����ݿ϶�����Ч�� TS24008:10.5.1.3 */
    if ( (NAS_MML_LAC_INVALID_SPECAL_IN_SIM == pucPsLociFileContent[NAS_MMC_USIM_PSLOCI_LAC_POSITION_BEG])
      && (NAS_MML_LAC_INVALID_SPECAL_IN_SIM == pucPsLociFileContent[NAS_MMC_USIM_PSLOCI_LAC_POSITION_END]) )
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdatePtmsiFormPsLociFile:invalid LAC,ALL ZEROS");

        ulValidPtmsiFlag = VOS_FALSE;
    }

    /* ȡ��SIM���е�PLMN ID��Ϣ�������ж�PLMN�Ƿ���Ч */
    ucCurrPos           = NAS_MML_RAI_POS_EFPSLOCI_FILE;

    /* �洢PLMN ID */
    PS_MEM_CPY(stSimPlmnId.aucSimPlmn,
               pucPsLociFileContent + ucCurrPos,
               NAS_MML_SIM_PLMN_ID_LEN);

    NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmnId, &stPlmnId);

    /* PLMN ID��Ч���򲻸���PTMSI */
    if ( VOS_FALSE == NAS_MML_IsPlmnIdValid(&stPlmnId) )
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdatePtmsiFormPsLociFile:invalid PLMN ID");

        ulValidPtmsiFlag = VOS_FALSE;
    }

    /* ��ȡPTMSI������ */
    for (i = 0; i < NAS_MML_MAX_PTMSI_LEN; i++)
    {
        if (NAS_MML_PTMSI_INVALID == pucPsLociFileContent[i])
        {
            ucInvalidCnt++;
        }
    }

    /* PTMSI��Чʱ����Ҫ����,����PTMSI��ʼ�������Ϊ��Чֵ */
    if ( NAS_MML_MAX_PTMSI_LEN == ucInvalidCnt )
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdatePtmsiFormPsLociFile:invalid PTMSI");


        /* ����ֱ��RETURN,����Ҫ��ʾ�ĸ��µ�ǰ��PTMSIΪ��Чֵ��Ʃ��NV�еı����
          ����Ч�ģ����ļ��е�����Ч�ģ���������ȡ��Ϊ׼ */
        ulValidPtmsiFlag = VOS_FALSE;
    }


    /* ��PTMSI��Ч������ʾ����PTMSIΪ��Чֵ */
    if ( VOS_FALSE == ulValidPtmsiFlag )
    {
        for ( i = 0 ; i < NAS_MML_MAX_PTMSI_LEN ; i++ )
        {
            pstMsIdentity->aucPtmsi[i] = NAS_MML_PTMSI_INVALID;
        }

        return;
    }

    for (i = 0; i < NAS_MML_MAX_PTMSI_LEN; i++)
    {
        pstMsIdentity->aucPtmsi[i]  = pucPsLociFileContent[i];
    }
}
VOS_VOID  NAS_MMC_UpdatePtmsiSignatureFormPsLociFile(
    VOS_UINT8                          *pucPsLociFileContent
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           ucInvalidCnt;
    NAS_MML_SIM_MS_IDENTITY_STRU       *pstMsIdentity;

    ucInvalidCnt        = 0;
    pstMsIdentity       = NAS_MML_GetSimMsIdentity();

    for (i = NAS_MML_PTMSI_SIGNATRUE_POS_EFPSLOCI_FILE; i < (NAS_MML_PTMSI_SIGNATRUE_POS_EFPSLOCI_FILE + NAS_MML_MAX_PTMSI_SIGNATURE_LEN); i++)
    {
        if (NAS_MML_PTMSI_SIGNATURE_INVALID == pucPsLociFileContent[i])
        {
            ucInvalidCnt++;
        }
    }

    /* PTMSI Signature��Чʱ����Ҫ����,����PTMSI Signature��ʼ�������Ϊ��Чֵ */
    if (NAS_MML_MAX_PTMSI_SIGNATURE_LEN == ucInvalidCnt)
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdatePtmsiSignatureFormPsLociFile:invalid PTMSISignature");


        /* ����PTMSI Signature����Ϊ��Чֵ */
        for ( i = 0 ; i < NAS_MML_MAX_PTMSI_SIGNATURE_LEN ; i++ )
        {
            pstMsIdentity->aucPtmsiSignature[i] = NAS_MML_PTMSI_SIGNATURE_INVALID;
        }

        return;
    }

    for (i = 0; i < NAS_MML_MAX_PTMSI_SIGNATURE_LEN; i++)
    {
        pstMsIdentity->aucPtmsiSignature[i] = pucPsLociFileContent[i + NAS_MML_PTMSI_SIGNATRUE_POS_EFPSLOCI_FILE];
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateRaiFormPsLociFile
 ��������  : ����PSLOCI�ļ������ݸ���RAI������
 �������  : pucPsLociFileContent:USIM��EFPSLOCI������
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��12��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateRaiFormPsLociFile(
    VOS_UINT8                          *pucPsLociFileContent
)
{
    VOS_UINT32                          i;
    NAS_MML_SIM_FORMAT_PLMN_ID          stSimPlmnId;
    NAS_MML_PS_DOMAIN_INFO_STRU        *pstPsDomainInfo;
    VOS_UINT8                           ucCurrPos;

    PS_MEM_SET(&stSimPlmnId, 0, sizeof(NAS_MML_SIM_FORMAT_PLMN_ID));

    ucCurrPos           = NAS_MML_RAI_POS_EFPSLOCI_FILE;
    pstPsDomainInfo     = NAS_MML_GetPsDomainInfo();

    /* �洢PLMN ID */
    PS_MEM_CPY(stSimPlmnId.aucSimPlmn,
               pucPsLociFileContent + ucCurrPos,
               NAS_MML_SIM_PLMN_ID_LEN);

    NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmnId,
                                    &(pstPsDomainInfo->stLastSuccRai.stLai.stPlmnId));

    /* �洢LAC  */
    ucCurrPos += NAS_MML_SIM_PLMN_ID_LEN;
    for ( i = 0 ; i < NAS_MML_MAX_LAC_LEN ; i++ )
    {
        pstPsDomainInfo->stLastSuccRai.stLai.aucLac[i] = pucPsLociFileContent[ucCurrPos + i];
    }

    if ((NAS_MML_LAC_INVALID_SPECAL_IN_SIM == pstPsDomainInfo->stLastSuccRai.stLai.aucLac[0])
     && (NAS_MML_LAC_INVALID_SPECAL_IN_SIM == pstPsDomainInfo->stLastSuccRai.stLai.aucLac[1]))
    {
        pstPsDomainInfo->stLastSuccRai.stLai.aucLac[0] = NAS_MML_LAC_LOW_BYTE_INVALID;
        pstPsDomainInfo->stLastSuccRai.stLai.aucLac[1] = NAS_MML_LAC_HIGH_BYTE_INVALID;
    }

    /* ���sim���е�������0xFFFF,����ΪLAIΪ0xFEFF */
    if ((NAS_MML_LAC_LOW_BYTE_INVALID == pstPsDomainInfo->stLastSuccRai.stLai.aucLac[0])
     && (NAS_MML_LAC_LOW_BYTE_INVALID == pstPsDomainInfo->stLastSuccRai.stLai.aucLac[1]))
    {
        pstPsDomainInfo->stLastSuccRai.stLai.aucLac[0] = NAS_MML_LAC_LOW_BYTE_INVALID;
        pstPsDomainInfo->stLastSuccRai.stLai.aucLac[1] = NAS_MML_LAC_HIGH_BYTE_INVALID;
    }

    ucCurrPos += NAS_MML_MAX_LAC_LEN;

    /* �洢RAC */
    pstPsDomainInfo->stLastSuccRai.ucRac    = pucPsLociFileContent[ucCurrPos];
}


VOS_VOID  NAS_MMC_UpdateSimInfoFromPsLociFile(
    VOS_UINT8                          *pucPsLociFileContent
)
{
    NAS_MML_SIM_STATUS_STRU            *pstSimStatus;
    VOS_UINT8                           ucUpdateStatus;

    pstSimStatus    = NAS_MML_GetSimStatus();

    /*

    Identifier: '6F73'  Structure: transparent  Mandatory
    SFI: '0C'
    File size: 14 bytes Update activity: high
    Access Conditions:
        READ    PIN
        UPDATE  PIN
        DEACTIVATE  ADM
        ACTIVATE    ADM

    Bytes   Description M/O Length
    1 to 4  P-TMSI  M   4 bytes
    5 to 7  P-TMSI signature value  M   3 bytes
    8 to13  RAI M   6 bytes
    14  Routing Area update status  M   1 byte

    */

    NAS_MML_UpdateSimPsLociFileContent(pucPsLociFileContent);


    /* ����PTMSI������ */
    NAS_MMC_UpdatePtmsiFormPsLociFile(pucPsLociFileContent);

    /* ����PTMSI SIGNATURE������ */
    NAS_MMC_UpdatePtmsiSignatureFormPsLociFile(pucPsLociFileContent);

    /* ����RAI������ */
    NAS_MMC_UpdateRaiFormPsLociFile(pucPsLociFileContent);

    /* ����GPRS��״̬ */
    ucUpdateStatus = pucPsLociFileContent[NAS_MML_PS_LOCI_SIM_FILE_LEN - 1];
    ucUpdateStatus = (ucUpdateStatus) & NAS_MML_UPDATE_STATUS_MASK_IN_SIM;

    if (ucUpdateStatus > NAS_MML_ROUTING_UPDATE_STATUS_BUTT )
    {
        ucUpdateStatus = NAS_MML_ROUTING_UPDATE_STATUS_BUTT;
    }
    pstSimStatus->enPsUpdateStatus  = ucUpdateStatus;
}


VOS_VOID  NAS_MMC_UpdatePsSecutityInfoFromUsimFile(
    VOS_UINT8                          *pucPsSecutityInfo
)
{
    NAS_MML_SIM_STATUS_STRU            *pstSimStatus;
    NAS_MML_SIM_PS_SECURITY_INFO_STRU  *pstPsSecurityInfo;

    pstSimStatus            = NAS_MML_GetSimStatus();
    pstPsSecurityInfo       = NAS_MML_GetSimPsSecurity();

    /* �洢PS security key */
    if (NAS_MML_SIM_TYPE_USIM == pstSimStatus->enSimType )
    {
        /*
        Identifier: '6F09'  Structure: transparent  Mandatory
        SFI: '08'
        File size: 33 bytes Update activity: high
        Access Conditions:
            READ    PIN
            UPDATE  PIN
            DEACTIVATE  ADM
            ACTIVATE    ADM

        Bytes   Description M/O Length
        1   Key set identifier KSIPS  M   1 byte
        2 to 17 Ciphering key CKPS    M   16 bytes
        18 to 33    Integrity key IKPS    M   16 bytes

        */

        /* �洢CKSN */
        pstPsSecurityInfo->ucCKSN   = (pucPsSecutityInfo[0] & NAS_MML_CKSN_INVALID);

        PS_MEM_CPY(pstPsSecurityInfo->aucUmtsCk,
                   &pucPsSecutityInfo[NAS_MML_CK_POS_EFKEY_FILE],
                   NAS_MML_UMTS_CK_LEN);

        PS_MEM_CPY(pstPsSecurityInfo->aucUmtsIk,
                   &pucPsSecutityInfo[NAS_MML_CK_POS_EFKEY_FILE + NAS_MML_UMTS_CK_LEN],
                   NAS_MML_UMTS_IK_LEN);

        NAS_MML_SecContext3GTO2G(pstPsSecurityInfo->aucUmtsIk,
                                 pstPsSecurityInfo->aucUmtsCk,
                                 pstPsSecurityInfo->aucGsmKc);
    }
    else
    {
        /*
        Identifier: '6F52'  Structure: transparent  Mandatory
        File size: 9 bytes  Update activity: high
        Bytes   Description M/O Length
        1 to 8  Ciphering key KcGPRS    M   8 bytes
        9   Ciphering key sequence number n M   1 byte
        */

        pstPsSecurityInfo->ucCKSN   = (pucPsSecutityInfo[NAS_MML_GSM_KC_LEN] & NAS_MML_CKSN_INVALID);

        PS_MEM_CPY(pstPsSecurityInfo->aucGsmKc,
                   pucPsSecutityInfo,
                   NAS_MML_GSM_KC_LEN);

        NAS_MML_SecContext2GTO3G(pstPsSecurityInfo->aucUmtsIk,
                                 pstPsSecurityInfo->aucUmtsCk,
                                 pstPsSecurityInfo->aucGsmKc);
    }
}



VOS_VOID  NAS_MMC_UpdateTmsiFormCsLociFile(
    VOS_UINT8                          *pucCsLociFileContent
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           ucInvalidCnt;
    NAS_MML_SIM_MS_IDENTITY_STRU       *pstMsIdentity;

    NAS_MML_SIM_FORMAT_PLMN_ID          stSimPlmnId;
    NAS_MML_PLMN_ID_STRU                stPlmnId;
    VOS_UINT8                          *pucLaiPos;

    VOS_UINT32                          ulValidTmsiFlag;

    PS_MEM_SET(&stSimPlmnId, 0, sizeof(NAS_MML_SIM_FORMAT_PLMN_ID));
    PS_MEM_SET(&stPlmnId, 0, sizeof(NAS_MML_PLMN_ID_STRU));

    /* Ĭ��TMSI��Ч */
    ulValidTmsiFlag    = VOS_TRUE;

    ucInvalidCnt        = 0;
    pstMsIdentity       = NAS_MML_GetSimMsIdentity();

    /* λ������Ч,��TMSI�����ݿ϶�����Ч��,ֱ�ӷ��� */
    /* �ο�31.102, 4.2.17�½�, ��������Ӧλ�õ��ֽں��� */
    if ( ( NAS_MML_LAC_LOW_BYTE_INVALID == pucCsLociFileContent[7] )
      && ( (NAS_MML_LAC_LOW_BYTE_INVALID == pucCsLociFileContent[8])
        || (NAS_MML_LAC_HIGH_BYTE_INVALID == pucCsLociFileContent[8])))
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdateTmsiFormCsLociFile:invalid LAC");


        /* ����ֱ��RETURN,����Ҫ��ʾ�ĸ��µ�ǰ��PTMSIΪ��Чֵ��Ʃ��NV�еı����
          ����Ч�ģ����ļ��е�����Ч�ģ���������ȡ��Ϊ׼ */
        ulValidTmsiFlag = VOS_FALSE;
    }


     /* λ����������Ϊȫ0������ΪRAI��Ч,��PTMSI�����ݿ϶�����Ч�� TS24008:10.5.1.3 */
    if ( (NAS_MML_LAC_INVALID_SPECAL_IN_SIM == pucCsLociFileContent[7])
      && (NAS_MML_LAC_INVALID_SPECAL_IN_SIM == pucCsLociFileContent[8]) )
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdatePtmsiFormPsLociFile:invalid LAC,ALL ZEROS");


        /* ����ֱ��RETURN,����Ҫ��ʾ�ĸ��µ�ǰ��TMSIΪ��Чֵ��Ʃ��NV�еı����
          ����Ч�ģ����ļ��е�����Ч�ģ���������ȡ��Ϊ׼ */
        ulValidTmsiFlag = VOS_FALSE;
    }

    /* ȡ��SIM���е�PLMN ID��Ϣ�������ж�PLMN�Ƿ���Ч */
    pucLaiPos             = pucCsLociFileContent +  NAS_MML_LAI_POS_EFLOCI_FILE;

    /* �洢PLMN ID */
    PS_MEM_CPY(stSimPlmnId.aucSimPlmn,
               pucLaiPos,
               NAS_MML_SIM_PLMN_ID_LEN);

    NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmnId, &stPlmnId);

    /* PLMN ID��Ч���򲻸���TMSI */
    if ( VOS_FALSE == NAS_MML_IsPlmnIdValid(&stPlmnId) )
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdateTmsiFormCsLociFile:invalid PLMN ID");


        /* ����ֱ��RETURN,����Ҫ��ʾ�ĸ��µ�ǰ��TMSIΪ��Чֵ��Ʃ��NV�еı����
          ����Ч�ģ����ļ��е�����Ч�ģ���������ȡ��Ϊ׼ */
        ulValidTmsiFlag = VOS_FALSE;
    }

    for (i = 0; i < NAS_MML_MAX_TMSI_LEN; i++)
    {
        if (NAS_MML_TMSI_INVALID == pucCsLociFileContent[i])
        {
            ucInvalidCnt++;
        }
    }

    if ( NAS_MML_MAX_TMSI_LEN == ucInvalidCnt )
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdateTmsiFormCsLociFile:invalid TMSI");

        /* ����ֱ��RETURN,����Ҫ��ʾ�ĸ��µ�ǰ��TMSIΪ��Чֵ��Ʃ��NV�еı����
          ����Ч�ģ����ļ��е�����Ч�ģ���������ȡ��Ϊ׼ */
        ulValidTmsiFlag = VOS_FALSE;
    }


    /* ��TMSI��Ч������ʽ����TMSIΪ��Чֵ */
    if ( VOS_FALSE == ulValidTmsiFlag )
    {
        for ( i = 0 ; i < NAS_MML_MAX_TMSI_LEN ; i++ )
        {
            pstMsIdentity->aucTmsi[i] = NAS_MML_TMSI_INVALID;
        }

        return;
    }

    for (i = 0; i < NAS_MML_MAX_TMSI_LEN; i++ )
    {
        pstMsIdentity->aucTmsi[i] = pucCsLociFileContent[i];
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateLaiFormCsLociFile
 ��������  : ����LOCI�ļ������ݸ���LAI������
 �������  : pucCsLociFileContent:USIM��EFLOCI������
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��12��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateLaiFormCsLociFile(
    VOS_UINT8                          *pucCsLociFileContent
)
{
    NAS_MML_SIM_FORMAT_PLMN_ID          stSimPlmnId;
    NAS_MML_CS_DOMAIN_INFO_STRU        *pstCsDomainInfo = VOS_NULL_PTR;
    VOS_UINT8                          *pucLaiPos = VOS_NULL_PTR;
    VOS_UINT32                          i;

    PS_MEM_SET(&stSimPlmnId, 0, sizeof(NAS_MML_SIM_FORMAT_PLMN_ID));

    pstCsDomainInfo       = NAS_MML_GetCsDomainInfo();
    pucLaiPos             = pucCsLociFileContent +  NAS_MML_LAI_POS_EFLOCI_FILE;

    /* �洢PLMN ID */
    PS_MEM_CPY(stSimPlmnId.aucSimPlmn,
               pucLaiPos,
               NAS_MML_SIM_PLMN_ID_LEN);

    NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmnId,
                                    &(pstCsDomainInfo->stLastSuccLai.stPlmnId));


    /* �洢LAI */
    for ( i = 0 ; i < NAS_MML_MAX_LAC_LEN ; i++ )
    {
        pstCsDomainInfo->stLastSuccLai.aucLac[i] = *(pucLaiPos + NAS_MML_SIM_PLMN_ID_LEN + i);
    }

    if ((NAS_MML_LAC_INVALID_SPECAL_IN_SIM == pstCsDomainInfo->stLastSuccLai.aucLac[0])
     && (NAS_MML_LAC_INVALID_SPECAL_IN_SIM == pstCsDomainInfo->stLastSuccLai.aucLac[1]))
    {
        pstCsDomainInfo->stLastSuccLai.aucLac[0] = NAS_MML_LAC_LOW_BYTE_INVALID;
        pstCsDomainInfo->stLastSuccLai.aucLac[1] = NAS_MML_LAC_HIGH_BYTE_INVALID;
    }

    /* ���sim���е�������0xFFFF,����ΪLAIΪ0xFEFF */
    if ((NAS_MML_LAC_LOW_BYTE_INVALID == pstCsDomainInfo->stLastSuccLai.aucLac[0])
     && (NAS_MML_LAC_LOW_BYTE_INVALID == pstCsDomainInfo->stLastSuccLai.aucLac[1]))
    {
        pstCsDomainInfo->stLastSuccLai.aucLac[0] = NAS_MML_LAC_LOW_BYTE_INVALID;
        pstCsDomainInfo->stLastSuccLai.aucLac[1] = NAS_MML_LAC_HIGH_BYTE_INVALID;
    }
}
VOS_VOID  NAS_MMC_UpdateSimInfoFromCsLociFile(
    VOS_UINT8                          *pucCsLociFileContent
)
{
    NAS_MML_SIM_STATUS_STRU            *pstSimStatus = VOS_NULL_PTR;
    VOS_UINT8                           ucUpdateStatus;

    pstSimStatus    = NAS_MML_GetSimStatus();

    /*
    Identifier: '6F7E'  Structure: transparent  Mandatory
    SFI: '0B'
    File size: 11 bytes Update activity: high
    Access Conditions:
        READ    PIN
        UPDATE  PIN
        DEACTIVATE  ADM
        ACTIVATE    ADM

    Bytes   Description M/O Length
    1 to 4  TMSI    M   4 bytes
    5 to 9  LAI M   5 bytes
    10  RFU M   1 byte
    11  Location update status  M   1 byte
    */

    NAS_MML_UpdateSimCsLociFileContent(pucCsLociFileContent);

    /* ����PTMSI������ */
    NAS_MMC_UpdateTmsiFormCsLociFile(pucCsLociFileContent);

    /* ����LAI������ */
    NAS_MMC_UpdateLaiFormCsLociFile(pucCsLociFileContent);

    /* ����CS���״̬ */
    ucUpdateStatus = pucCsLociFileContent[NAS_MML_CS_LOCI_SIM_FILE_LEN - 1];
    ucUpdateStatus = (ucUpdateStatus) & NAS_MML_UPDATE_STATUS_MASK_IN_SIM;

    if (ucUpdateStatus > NAS_MML_LOCATION_UPDATE_STATUS_BUTT)
    {
        ucUpdateStatus = NAS_MML_LOCATION_UPDATE_STATUS_BUTT;
    }

    pstSimStatus->enCsUpdateStatus  = ucUpdateStatus;
}
VOS_VOID  NAS_MMC_UpdateCsSecutityInfoFromUsimFile(
    VOS_UINT8                          *pucCsSecutityInfo
)
{
    NAS_MML_SIM_STATUS_STRU            *pstSimStatus;
    NAS_MML_SIM_CS_SECURITY_INFO_STRU  *pstCsSecurityInfo;

    pstSimStatus            = NAS_MML_GetSimStatus();
    pstCsSecurityInfo       = NAS_MML_GetSimCsSecurity();

    /* �洢CS security key */
    if (NAS_MML_SIM_TYPE_USIM == pstSimStatus->enSimType )
    {
        /*
        Identifier: '6F08'  Structure: transparent  Mandatory
        SFI: '08'
        File size: 33 bytes Update activity: high
        Access Conditions:
            READ    PIN
            UPDATE  PIN
            DEACTIVATE  ADM
            ACTIVATE    ADM

        Bytes   Description M/O Length
        1   Key set identifier KSI  M   1 byte
        2 to 17 Ciphering key CK    M   16 bytes
        18 to 33    Integrity key IK    M   16 bytes
        */
        /* �洢CKSN */
        pstCsSecurityInfo->ucCKSN   = (pucCsSecutityInfo[0] & NAS_MML_CKSN_INVALID);

        PS_MEM_CPY(pstCsSecurityInfo->aucUmtsCk,
                   &pucCsSecutityInfo[NAS_MML_CK_POS_EFKEY_FILE],
                   NAS_MML_UMTS_CK_LEN);

        PS_MEM_CPY(pstCsSecurityInfo->aucUmtsIk,
                   &pucCsSecutityInfo[NAS_MML_CK_POS_EFKEY_FILE + NAS_MML_UMTS_CK_LEN],
                   NAS_MML_UMTS_IK_LEN);

        NAS_MML_SecContext3GTO2G(pstCsSecurityInfo->aucUmtsIk,
                                 pstCsSecurityInfo->aucUmtsCk,
                                 pstCsSecurityInfo->aucGsmKc);
    }
    else
    {
        /*

        Identifier: '6F20'  Structure: transparent  Mandatory
        File size: 9 bytes  Update activity: high
        Access Conditions:
            READ    CHV1
            UPDATE  CHV1
            INVALIDATE  ADM
            REHABILITATE    ADM

        Bytes   Description M/O Length
        1 to 8  Ciphering key Kc    M   8 bytes
        9   Ciphering key sequence number n M   1 byte

        */

        pstCsSecurityInfo->ucCKSN   = (pucCsSecutityInfo[NAS_MML_GSM_KC_LEN] & NAS_MML_CKSN_INVALID);

        PS_MEM_CPY(pstCsSecurityInfo->aucGsmKc,
                   pucCsSecutityInfo,
                   NAS_MML_GSM_KC_LEN);

        NAS_MML_SecContext2GTO3G(pstCsSecurityInfo->aucUmtsIk,
                                 pstCsSecurityInfo->aucUmtsCk,
                                 pstCsSecurityInfo->aucGsmKc);
    }
}

/* Added by h00313353 for iteration 9, 2015-2-17, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_ReadUsimmPlmn
 ��������  : �����ȡUSIM�ļ���������USIMģ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��2��6��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_ReadUsimmPlmn(
    NAS_USIMM_GETFILE_INFO_STRU        *pstGetFileInfo
)
{
    VOS_UINT16                          usFileId;

    PS_MEM_SET(pstGetFileInfo, 0x00, sizeof(NAS_USIMM_GETFILE_INFO_STRU));
    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {/* 3G USIM */
        usFileId = USIMM_USIM_EFFPLMN_ID;
    }
    else
    {/* 2G SIM */
        usFileId = USIMM_GSM_EFFPLMN_ID;
    }

    /* ��ȡPLMN */
    NAS_COMM_BUILD_USIM_GET_FILE_INFO(pstGetFileInfo,
                                    USIMM_GUTL_APP,
                                    usFileId,
                                    0);

    (VOS_VOID)NAS_USIMMAPI_GetFileReq(WUEPS_PID_MMC, 0, pstGetFileInfo);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ReadUsimmEfad
 ��������  : �����ȡUSIM�ļ���������USIMģ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��2��6��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_ReadUsimmEfad(
    NAS_USIMM_GETFILE_INFO_STRU        *pstGetFileInfo
)
{
    VOS_UINT16                          usFileId;

    PS_MEM_SET(pstGetFileInfo, 0x00, sizeof(NAS_USIMM_GETFILE_INFO_STRU));

    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {/* 3G USIM */
        usFileId = USIMM_USIM_EFAD_ID;
    }
    else
    {/* 2G SIM */
        usFileId = USIMM_GSM_EFAD_ID;
    }

    /* ��ȡEFAD */
    NAS_COMM_BUILD_USIM_GET_FILE_INFO(pstGetFileInfo,
                                    USIMM_GUTL_APP,
                                    usFileId,
                                    0);

    (VOS_VOID)NAS_USIMMAPI_GetFileReq(WUEPS_PID_MMC, 0, pstGetFileInfo);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ReadUsimmUplmn
 ��������  : �����ȡUSIM�ļ���������USIMģ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��2��6��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_ReadUsimmUplmn(
    NAS_USIMM_GETFILE_INFO_STRU        *pstGetFileInfo
)
{
    VOS_UINT16                          usFileId;

    PS_MEM_SET(pstGetFileInfo, 0x00, sizeof(NAS_USIMM_GETFILE_INFO_STRU));

    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {/* 3G USIM */
        usFileId = USIMM_USIM_EFPLMNWACT_ID;
    }
    else
    {/* 2G SIM */
        usFileId = USIMM_GSM_EFPLMNWACT_ID;
    }

    /* ��ȡUPLMN */
    NAS_COMM_BUILD_USIM_GET_FILE_INFO(pstGetFileInfo,
                                    USIMM_GUTL_APP,
                                    usFileId,
                                    0);

    (VOS_VOID)NAS_USIMMAPI_GetFileReq(WUEPS_PID_MMC, 0, pstGetFileInfo);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ReadUsimmOplmn
 ��������  : �����ȡUSIM�ļ���������USIMģ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��2��6��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_ReadUsimmOplmn(
    NAS_USIMM_GETFILE_INFO_STRU        *pstGetFileInfo
)
{
    VOS_UINT16                          usFileId;

    PS_MEM_SET(pstGetFileInfo, 0x00, sizeof(NAS_USIMM_GETFILE_INFO_STRU));

    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {/* 3G USIM */
        usFileId = USIMM_USIM_EFOPLMNWACT_ID;
    }
    else
    {/* 2G SIM */
        usFileId = USIMM_GSM_EFOPLMNWACT_ID;
    }

    /* ��ȡOPLMN */
    NAS_COMM_BUILD_USIM_GET_FILE_INFO(pstGetFileInfo,
                                    USIMM_GUTL_APP,
                                    usFileId,
                                    0);

    (VOS_VOID)NAS_USIMMAPI_GetFileReq(WUEPS_PID_MMC, 0, pstGetFileInfo);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ReadUsimmHplmn
 ��������  : �����ȡUSIM�ļ���������USIMģ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��2��6��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_ReadUsimmHplmn(
    NAS_USIMM_GETFILE_INFO_STRU        *pstGetFileInfo
)
{
    VOS_UINT16                          usFileId;

    PS_MEM_SET(pstGetFileInfo, 0x00, sizeof(NAS_USIMM_GETFILE_INFO_STRU));

    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {/* 3G USIM */
        usFileId = USIMM_USIM_EFHPLMNwACT_ID;
    }
    else
    {/* 2G SIM */
        usFileId = USIMM_GSM_EFHPLMNACT_ID;
    }

    /* ��ȡHPLMN */
    NAS_COMM_BUILD_USIM_GET_FILE_INFO(pstGetFileInfo,
                                    USIMM_GUTL_APP,
                                    usFileId,
                                    0);

    (VOS_VOID)NAS_USIMMAPI_GetFileReq(WUEPS_PID_MMC, 0, pstGetFileInfo);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ReadUsimmLoci
 ��������  : �����ȡUSIM�ļ���������USIMģ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��2��6��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_ReadUsimmCSLoci(
    NAS_USIMM_GETFILE_INFO_STRU        *pstGetFileInfo
)
{
    VOS_UINT16                          usFileId;

    PS_MEM_SET(pstGetFileInfo, 0x00, sizeof(NAS_USIMM_GETFILE_INFO_STRU));

    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {/* 3G USIM */
        usFileId = USIMM_USIM_EFLOCI_ID;
    }
    else
    {/* 2G SIM */
        usFileId = USIMM_GSM_EFLOCI_ID;
    }

    /* ��ȡCS LOCI*/
    NAS_COMM_BUILD_USIM_GET_FILE_INFO(pstGetFileInfo,
                                    USIMM_GUTL_APP,
                                    usFileId,
                                    0);

    (VOS_VOID)NAS_USIMMAPI_GetFileReq(WUEPS_PID_MMC, 0, pstGetFileInfo);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ReadUsimmAtt
 ��������  : �����ȡUSIM�ļ���������USIMģ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��2��6��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_ReadUsimmAtt(
    NAS_USIMM_GETFILE_INFO_STRU        *pstGetFileInfo
)
{
    VOS_UINT16                          usFileId;

    PS_MEM_SET(pstGetFileInfo, 0x00, sizeof(NAS_USIMM_GETFILE_INFO_STRU));

    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {/* 3G USIM */
        usFileId = USIMM_ATTUSIM_EFACTINGHPLMN_ID;
    }
    else
    {/* 2G SIM */
        usFileId = USIMM_ATTGSM_EFACTINGHPLMN_ID;
    }

    /* ��ȡATT */
    NAS_COMM_BUILD_USIM_GET_FILE_INFO(pstGetFileInfo,
                                    USIMM_GUTL_APP,
                                    usFileId,
                                    0);

    (VOS_VOID)NAS_USIMMAPI_GetFileReq(WUEPS_PID_MMC, 0, pstGetFileInfo);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ReadUsimmEhplmn
 ��������  : �����ȡUSIM�ļ���������USIMģ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��2��6��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_ReadUsimmEhplmn(
    NAS_USIMM_GETFILE_INFO_STRU        *pstGetFileInfo
)
{
    PS_MEM_SET(pstGetFileInfo, 0x00, sizeof(NAS_USIMM_GETFILE_INFO_STRU));

    /* ��ȡEHPLMN */
    NAS_COMM_BUILD_USIM_GET_FILE_INFO(pstGetFileInfo,
                                    USIMM_GUTL_APP,
                                    USIMM_USIM_EFEHPLMN_ID,
                                    0);

    (VOS_VOID)NAS_USIMMAPI_GetFileReq(WUEPS_PID_MMC, 0, pstGetFileInfo);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ReadUsimmEhplmnpi
 ��������  : �����ȡUSIM�ļ���������USIMģ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��2��6��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_ReadUsimmEhplmnpi(
    NAS_USIMM_GETFILE_INFO_STRU        *pstGetFileInfo
)
{
    PS_MEM_SET(pstGetFileInfo, 0x00, sizeof(NAS_USIMM_GETFILE_INFO_STRU));

    /* ��ȡEHPLMNPI */
    NAS_COMM_BUILD_USIM_GET_FILE_INFO(pstGetFileInfo,
                                    USIMM_GUTL_APP,
                                    USIMM_USIM_EFEHPLMNPI_ID,
                                    0);

    (VOS_VOID)NAS_USIMMAPI_GetFileReq(WUEPS_PID_MMC, 0, pstGetFileInfo);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ReadUsimmLrplmnsi
 ��������  : �����ȡUSIM�ļ���������USIMģ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��2��6��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_ReadUsimmLrplmnsi(
    NAS_USIMM_GETFILE_INFO_STRU        *pstGetFileInfo
)
{
    PS_MEM_SET(pstGetFileInfo, 0x00, sizeof(NAS_USIMM_GETFILE_INFO_STRU));

    /* ��ȡLRPLMNSI */
    NAS_COMM_BUILD_USIM_GET_FILE_INFO(pstGetFileInfo,
                                    USIMM_GUTL_APP,
                                    USIMM_USIM_EFLRPLMNSI_ID,
                                    0);

    (VOS_VOID)NAS_USIMMAPI_GetFileReq(WUEPS_PID_MMC, 0, pstGetFileInfo);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ReadUsimmHpplmn
 ��������  : �����ȡUSIM�ļ���������USIMģ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��2��6��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_ReadUsimmHpplmn(
    NAS_USIMM_GETFILE_INFO_STRU        *pstGetFileInfo
)
{
    VOS_UINT16                          usFileId;

    PS_MEM_SET(pstGetFileInfo, 0x00, sizeof(NAS_USIMM_GETFILE_INFO_STRU));

    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {/* 3G USIM */
        usFileId = USIMM_USIM_EFHPPLMN_ID;
    }
    else
    {/* 2G SIM */
        usFileId = USIMM_GSM_EFHPLMN_ID;
    }

    /* ��ȡHPPLMN */
    NAS_COMM_BUILD_USIM_GET_FILE_INFO(pstGetFileInfo,
                                    USIMM_GUTL_APP,
                                    usFileId,
                                    0);

    (VOS_VOID)NAS_USIMMAPI_GetFileReq(WUEPS_PID_MMC, 0, pstGetFileInfo);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ReadUsimmFile
 ��������  : �����ȡUSIM�ļ���������USIMģ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��2��6��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_ReadUsimmFile(
    NAS_USIMM_GETFILE_INFO_STRU        *pstGetFileInfo,
    VOS_UINT16                          usFileId
)
{
    PS_MEM_SET(pstGetFileInfo, 0x00, sizeof(NAS_USIMM_GETFILE_INFO_STRU));

    /* ��ȡ usFileId��Ӧ�ļ� */
    NAS_COMM_BUILD_USIM_GET_FILE_INFO(pstGetFileInfo,
                                    USIMM_GUTL_APP,
                                    usFileId,
                                    0);

    (VOS_VOID)NAS_USIMMAPI_GetFileReq(WUEPS_PID_MMC, 0, pstGetFileInfo);
}

/* Added by h00313353 for iteration 9, 2015-2-17, end */



VOS_VOID   NAS_MMC_SndUsimReadFileReq( VOS_VOID )
{
    VOS_UINT32                          ulRet;
    NAS_MML_SIM_STATUS_STRU            *pstSimStatus = VOS_NULL_PTR;
    NAS_MML_HPLMN_CFG_INFO_STRU        *pstHplmnCfgInfo = VOS_NULL_PTR;

    VOS_UINT32                          ulNvOplmnAvail = VOS_FALSE;

    /* Added by h00313353 for iteration 9, 2015-2-4, begin */
    NAS_USIMM_GETFILE_INFO_STRU         stGetFileInfo;

    /* Added by h00313353 for iteration 9, 2015-2-4, end */

    pstHplmnCfgInfo = NAS_MML_GetHplmnCfg();

    pstSimStatus    = NAS_MML_GetSimStatus();

    NAS_MMC_ReadUsimmPlmn(&stGetFileInfo);

    NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_FORBIDDEN_PLMN_LIST_FILE_ID_FLG);

    NAS_MMC_ReadUsimmEfad(&stGetFileInfo);

    NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_MNC_LENGTH_FILE_ID_FLG);

    ulRet = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_UPLMN_SEL_WACT);

    if (PS_USIM_SERVICE_AVAILIABLE == ulRet)
    {
        NAS_MMC_ReadUsimmUplmn(&stGetFileInfo);

        NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_UPLMN_SEL_FILE_ID_FLG);
    }

    ulRet = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_OPLMN_SEL_WACT);

    ulNvOplmnAvail = NAS_MML_IsNvimOplmnAvail();
    if ((PS_USIM_SERVICE_AVAILIABLE == ulRet)
     && (VOS_FALSE == ulNvOplmnAvail))
    {
        NAS_MMC_ReadUsimmOplmn(&stGetFileInfo);

        NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_OPLMN_SEL_FILE_ID_FLG);
    }

    ulRet = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_HPLMN_WACT);

    if (PS_USIM_SERVICE_AVAILIABLE == ulRet)
    {
        NAS_MMC_ReadUsimmHplmn(&stGetFileInfo);

        NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_HPLMN_SEL_FILE_ID_FLG);
    }

    NAS_MMC_ReadUsimmCSLoci(&stGetFileInfo);

    NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_CS_LOC_FILE_ID_FLG);

    /* ACTING-HPLMN���Կ��ش�ʱ��Ҫ��ȡACTING-HPLMN�������ȡEHPLMN */
    if (VOS_TRUE == pstHplmnCfgInfo->ucActingHPlmnSupportFlg)
    {
        NAS_MMC_ReadUsimmAtt(&stGetFileInfo);

        NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_ACTING_HPLMN_FILE_ID_FLG);
    }
    else
    {
        /* EHPLMN���Կ��ش�ʱ����Ҫ��ȡ */
        ulRet = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_EHPLMN);

        if ( (VOS_TRUE == pstHplmnCfgInfo->ucEhplmnSupportFlg)
          && (PS_USIM_SERVICE_AVAILIABLE == ulRet))
        {
            NAS_MMC_ReadUsimmEhplmn(&stGetFileInfo);

            NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_EHPLMN_FILE_ID_FLG);
        }
    }

    ulRet = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_EHPLMN_IND);

    if (PS_USIM_SERVICE_AVAILIABLE == ulRet)
    {
        NAS_MMC_ReadUsimmEhplmnpi(&stGetFileInfo);

        NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_EHPLMNPI_FILE_ID_FLG);
    }

    ulRet = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_RPLMN_LACT);

    if (PS_USIM_SERVICE_AVAILIABLE == ulRet)
    {
        NAS_MMC_ReadUsimmLrplmnsi(&stGetFileInfo);

        NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_LRPLMNSI_FILE_ID_FLG);
    }

    NAS_MMC_ReadUsimmHpplmn(&stGetFileInfo);

    NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_HPLMN_PERI_FILE_ID_FLG);

    if ( NAS_MML_SIM_TYPE_SIM == pstSimStatus->enSimType)
    {
        /* ��ȡPS LOCI */
        NAS_MMC_ReadUsimmFile(&stGetFileInfo, USIMM_GSM_EFLOCIGPRS_ID);  /* NAS_MML_READ_SIM_PS_LOC_FILE_ID */

        NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_PS_LOC_FILE_ID_FLG);

        /* ��ȡCS KC */
        NAS_MMC_ReadUsimmFile(&stGetFileInfo, USIMM_GSM_EFKC_ID);

        NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_CS_KC_FILE_ID_FLG);

        /* ��ȡPS KC */
        NAS_MMC_ReadUsimmFile(&stGetFileInfo, USIMM_GSM_EFKCGPRS_ID);

        NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_PS_KC_FILE_ID_FLG);

        ulRet = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_PLMN_SELECTOR);

        if (PS_USIM_SERVICE_AVAILIABLE == ulRet)
        {
            /* SIM�������UPLMN��OPLMN */
            NAS_MMC_ReadUsimmFile(&stGetFileInfo, USIMM_GSM_EFPLMNSEL_ID);

            NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_PLMN_SEL_FILE_ID_FLG);
        }
    }
    else
    {
        /* ��ȡPS LOCI */
        NAS_MMC_ReadUsimmFile(&stGetFileInfo, USIMM_USIM_EFPSLOCI_ID);

        NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_PS_LOC_FILE_ID_FLG);

        /* ��ȡCS CK IK */
        NAS_MMC_ReadUsimmFile(&stGetFileInfo, USIMM_USIM_EFKEYS_ID);

        NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_CS_CKIK_FILE_ID_FLG);

        /* ��ȡPS KEY */
        NAS_MMC_ReadUsimmFile(&stGetFileInfo, USIMM_USIM_EFKEYSPS_ID);

        NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_PS_KEY_FILE_ID_FLG);
    }
}





VOS_VOID NAS_MMC_SndUsimUpdateForbPlmnReq(VOS_VOID)
{
    VOS_UINT8                          *pucFileContent = VOS_NULL_PTR;          /* ָ��File���ݵ�ָ��                       */
    VOS_UINT8                           ucForbPlmnNum;                          /* MMC forbidden PLMN�ĸ���                 */
    VOS_UINT8                           ucUsimForbPlmnNum;                      /* MMC forbidden PLMN�ĸ���                 */
    VOS_UINT8                           i;                                      /* ѭ�����Ʊ���                             */
    VOS_UINT8                           ucDif;                                  /* MMC��SIM��forbidden PLMN����֮��         */
    VOS_UINT8                           ucSetUsimPlmnNum;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo = VOS_NULL_PTR;
    /* Modified by h00313353 for iteration 9, 2015-2-3, begin */
    NAS_USIMM_UPDATEFILE_INFO_STRU      stSetFileInfo;
    VOS_UINT16                          usFileId;

    usFileId = USIMM_DEF_FILEID_BUTT;
    PS_MEM_SET(&stSetFileInfo, 0x00, sizeof(stSetFileInfo));
    /* Modified by h00313353 for iteration 9, 2015-2-3, end */

    pstForbidPlmnInfo           = NAS_MML_GetForbidPlmnInfo();
    ucForbPlmnNum               = pstForbidPlmnInfo->ucForbPlmnNum;
    ucUsimForbPlmnNum           = pstForbidPlmnInfo->ucUsimForbPlmnNum;
    ucSetUsimPlmnNum            = pstForbidPlmnInfo->ucUsimForbPlmnNum;

    pucFileContent = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_MMC, ucUsimForbPlmnNum * 3);

    if (VOS_NULL_PTR == pucFileContent)
    {
        PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_MMC_SndUsimUpdateForbPlmnReq:ERROR: Memory Alloc Error for pMsg");

        return;
    }

    PS_MEM_SET(pucFileContent, 0, ucUsimForbPlmnNum * 3);

    /* ��MMC�ڲ���forbidden PLMNת��ΪSIM�еĸ�ʽ */
    if (ucForbPlmnNum >= ucUsimForbPlmnNum)
    {
        /* MMC forbidden PLMN�ĸ���>=SIM�еĸ���    */
        ucDif = ucForbPlmnNum - ucUsimForbPlmnNum;

        /* ��MMC�����µ�ucUsimForbPlmnNum��forbidden PLMNת��ΪSIM�еĸ�ʽ */
        /* �μ�3GPP 31.102, 4.2.16�½ڣ�����SIM���ļ���ʽ������*/
        for (i=0; i < ucUsimForbPlmnNum; i++)
        {
            *(pucFileContent + (i*3))
              = (VOS_UINT8)(0x0000000F & pstForbidPlmnInfo->astForbPlmnIdList[ucDif + i].ulMcc);

            *(pucFileContent + (i*3))
             |= (VOS_UINT8)((0x00000F00 & pstForbidPlmnInfo->astForbPlmnIdList[ucDif + i].ulMcc) >> 4);

            *(pucFileContent + (i*3) + 1)
             = (VOS_UINT8)((0x000F0000 & pstForbidPlmnInfo->astForbPlmnIdList[ucDif + i].ulMcc) >> 16);

            *(pucFileContent + (i*3) + 1)
             |= (VOS_UINT8)((0x000F0000 & pstForbidPlmnInfo->astForbPlmnIdList[ucDif + i].ulMnc) >> 12);

            *(pucFileContent + (i*3) + 2)
             = (VOS_UINT8)(0x0000000F & pstForbidPlmnInfo->astForbPlmnIdList[ucDif + i].ulMnc);

            *(pucFileContent + (i*3) + 2)
             |= (VOS_UINT8)((0x00000F00 & pstForbidPlmnInfo->astForbPlmnIdList[ucDif + i].ulMnc) >> 4);
        }
    }
    else
    {
        /* MMC forbidden PLMN�ĸ���С��SIM�еĸ��� */
        if (NAS_MML_MAX_FORBPLMN_NUM > ucUsimForbPlmnNum)
        {
            ucDif = ucUsimForbPlmnNum - ucForbPlmnNum;
        }
        else
        {
            ucDif = NAS_MML_MAX_FORBPLMN_NUM - ucForbPlmnNum;

            /* ������USIM�ڳ���UE֧�ַ�Χ��FPLMN */
            ucSetUsimPlmnNum = NAS_MML_MAX_FORBPLMN_NUM;
        }

        /* ��MMC��forbidden PLMNת��ΪSIM�еĸ�ʽ */
        /* �μ�3GPP 31.102, 4.2.16�½ڣ�����SIM���ļ���ʽ������ */
        for (i=0; i < ucForbPlmnNum; i++)
        {
            *(pucFileContent + (i*3))
              = (VOS_UINT8)(0x0000000F & pstForbidPlmnInfo->astForbPlmnIdList[i].ulMcc);

            *(pucFileContent + (i*3))
             |= (VOS_UINT8)((0x00000F00 & pstForbidPlmnInfo->astForbPlmnIdList[i].ulMcc) >> NAS_MML_OCTET_MOVE_FOUR_BITS);

            *(pucFileContent + (i*3) + 1)
             = (VOS_UINT8)((0x000F0000 & pstForbidPlmnInfo->astForbPlmnIdList[i].ulMcc) >> NAS_MML_OCTET_MOVE_SIXTEEN_BITS);
            *(pucFileContent + (i*3) + 1)
             |= (VOS_UINT8)((0x000F0000 & pstForbidPlmnInfo->astForbPlmnIdList[i].ulMnc) >> NAS_MML_OCTET_MOVE_TWELVE_BITS);

            *(pucFileContent + (i*3) + 2)
             = (VOS_UINT8)(0x0000000F & pstForbidPlmnInfo->astForbPlmnIdList[i].ulMnc);

            *(pucFileContent + (i*3) + 2)
             |= (VOS_UINT8)((0x00000F00 & pstForbidPlmnInfo->astForbPlmnIdList[i].ulMnc) >> NAS_MML_OCTET_MOVE_FOUR_BITS);
        }

        /* ʣ��ռ���oxFF����  */
        PS_MEM_SET((pucFileContent + (ucForbPlmnNum*3)), (VOS_CHAR)0xFF, (ucDif*3));

    }

    /* Added by h00313353 for iteration 9, 2015-2-4, begin */
    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {/* 3G USIM */
        usFileId = USIMM_USIM_EFFPLMN_ID;
    }
    else
    {/* 2G SIM */
        usFileId = USIMM_GSM_EFFPLMN_ID;
    }
    /* Added by h00313353 for iteration 9, 2015-2-4, end */

    NAS_COMM_BUILD_USIM_SET_FILE_INFO(&stSetFileInfo,
                                    /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
                                    USIMM_GUTL_APP,
                                    usFileId,
                                    /* Modified by h00313353 for iteration 9, 2015-2-4, end */
                                    0,
                                    (VOS_UINT8)(ucSetUsimPlmnNum*NAS_MML_SIM_FORMAT_PLMN_LEN),
                                    pucFileContent);

    (VOS_VOID)NAS_USIMMAPI_SetFileReq(WUEPS_PID_MMC, 0, &stSetFileInfo);


    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_FPLMN_LIST,
                    pucFileContent, (i*3));

    /* �ͷſռ�  */
    PS_MEM_FREE(WUEPS_PID_MMC, pucFileContent);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertSimPlmnToNasPLMN
 ��������  : ��SIM���е�3�ֽڸ�ʽPLMNת��ΪMCC��MNC�ֿ��ĸ�ʽ
 �������  : aucEFplmn[3]
 �������  : ��
 �� �� ֵ  :MMC_PLMN_ID_STRU
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2010��1��21��
   ��    ��   : likelai
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��7��13��
   ��    ��   : zhoujun 40661
   �޸�����   : SIM�����ݸ��µ�MML��
*****************************************************************************/
VOS_VOID  NAS_MMC_ConvertSimPlmnToNasPLMN(
    NAS_MML_SIM_FORMAT_PLMN_ID          *pstSimPlmn,
    NAS_MML_PLMN_ID_STRU                *pstNasPlmn
)
{

    VOS_UINT32                          ulTempData;
    NAS_MML_PLMN_ID_STRU                stPlmn;

    /*
       PLMN BCD ���� ��ʽ

       MCC digit 2,  MCC digit 1, ----OCTET 1
       MNC digit 3,  MCC digit 3, ----OCTET 2
       MNC digit 2,  MNC digit 1, ----OCTET 3
    */
    ulTempData = NAS_MML_OCTET_LOW_FOUR_BITS & (pstSimPlmn->aucSimPlmn[0]);
    stPlmn.ulMcc = ulTempData;
    ulTempData = (NAS_MML_OCTET_HIGH_FOUR_BITS & (pstSimPlmn->aucSimPlmn[0])) >> NAS_MML_OCTET_MOVE_FOUR_BITS;
    stPlmn.ulMcc |= ulTempData << NAS_MML_OCTET_MOVE_EIGHT_BITS;

    ulTempData = NAS_MML_OCTET_LOW_FOUR_BITS & (pstSimPlmn->aucSimPlmn[1]);
    stPlmn.ulMcc |= ulTempData << NAS_MML_OCTET_MOVE_SIXTEEN_BITS;
    ulTempData = (NAS_MML_OCTET_HIGH_FOUR_BITS & (pstSimPlmn->aucSimPlmn[1])) >> NAS_MML_OCTET_MOVE_FOUR_BITS;

    stPlmn.ulMnc = ulTempData << NAS_MML_OCTET_MOVE_SIXTEEN_BITS;
    ulTempData = NAS_MML_OCTET_LOW_FOUR_BITS & (pstSimPlmn->aucSimPlmn[2]);
    stPlmn.ulMnc |= ulTempData;
    ulTempData = (NAS_MML_OCTET_HIGH_FOUR_BITS & (pstSimPlmn->aucSimPlmn[2])) >> NAS_MML_OCTET_MOVE_FOUR_BITS;
    stPlmn.ulMnc |= ulTempData << NAS_MML_OCTET_MOVE_EIGHT_BITS;

    *pstNasPlmn = stPlmn;


    return ;

}


VOS_VOID  NAS_MMC_ConvertNasPlmnToSimFormat(
    NAS_MML_PLMN_ID_STRU               *pstGUNasPlmn,
    NAS_MML_SIM_FORMAT_PLMN_ID         *pstSimPlmn
)
{
    pstSimPlmn->aucSimPlmn[0]
      = (VOS_UINT8)(0x0000000F & pstGUNasPlmn->ulMcc);
    pstSimPlmn->aucSimPlmn[0]
     |= (VOS_UINT8)((0x00000F00 & pstGUNasPlmn->ulMcc) >> 4);

    pstSimPlmn->aucSimPlmn[1]
     = (VOS_UINT8)((0x000F0000 & pstGUNasPlmn->ulMcc) >> 16);

    pstSimPlmn->aucSimPlmn[1]
     |= (VOS_UINT8)((0x000F0000 & pstGUNasPlmn->ulMnc) >> 12);

    pstSimPlmn->aucSimPlmn[2]
     = (VOS_UINT8)(0x0000000F & pstGUNasPlmn->ulMnc);
    pstSimPlmn->aucSimPlmn[2]
     |= (VOS_UINT8)((0x00000F00 & pstGUNasPlmn->ulMnc) >> 4);

    return;

}



VOS_VOID  NAS_MMC_ConverPlmnInfoFromSim(
    VOS_UINT8                          *pucUsimFileData,
    VOS_UINT32                          ulPlmnNum,
    NAS_MML_SIM_PLMN_WITH_RAT_STRU     *pstPlmnWithRat
)
{
    VOS_UINT32                          i;
    NAS_MML_PLMN_ID_STRU                stTempPlmn;
    NAS_MML_SIM_FORMAT_PLMN_ID          stSimPlmn;
    VOS_UINT16                          usTempData;

    PS_MEM_SET(&stTempPlmn, 0, sizeof(NAS_MML_PLMN_ID_STRU));
    PS_MEM_SET(&stSimPlmn, 0, sizeof(NAS_MML_SIM_FORMAT_PLMN_ID));
    
    for ( i = 0; i < ulPlmnNum; i++ )
    {
        /*
            31102
            1 to 3 PLMN (highest priority) M 3 bytes st
            4 to 5 PLMN Access Technology Identifier M 2 bytes
        */

        PS_MEM_CPY(stSimPlmn.aucSimPlmn, pucUsimFileData + (i * NAS_MML_PLMN_WITH_RAT_UNIT_LEN), NAS_MML_SIM_PLMN_ID_LEN);

        /* ת��PLMN IDΪMMC�ڲ��ĸ�ʽ���洢 */
        NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmn, &stTempPlmn);
        pstPlmnWithRat[i].stPlmnId = stTempPlmn;

        /* �洢PLMN��Ӧ��RAT */
        usTempData = (VOS_UINT16)(pucUsimFileData[(i * NAS_MML_PLMN_WITH_RAT_UNIT_LEN) + NAS_MML_PLMN_WITH_RAT_FIRST_RAT_OFFSET] << NAS_MML_OCTET_MOVE_EIGHT_BITS)
                                | pucUsimFileData[(i * NAS_MML_PLMN_WITH_RAT_UNIT_LEN) + NAS_MML_PLMN_WITH_RAT_SECOND_RAT_OFFSET];
        pstPlmnWithRat[i].usSimRat = usTempData;

    }
}



VOS_UINT32 NAS_MMC_IsNeedSndStkSearchModeChgEvt(VOS_VOID)
{
    if (VOS_TRUE == NAS_MML_GetSvlteSupportFlag())
    {
       if (VOS_TRUE == NAS_MML_IsCsServDomainAvail(NAS_MML_GetMsMode()))
       {
           return VOS_TRUE;
       }
       return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }

}




TAF_PH_PLMN_SEL_MODE NAS_MMC_ConvertSrchModeToStkSrchMode(
                                         VOS_UINT8 ucReselMode
                                         )
{
    switch (ucReselMode)
    {
        case NAS_MMC_PLMN_SELECTION_MODE_AUTO:
             return TAF_PH_PLMN_SEL_MODE_AUTO;

        case NAS_MMC_PLMN_SELECTION_MODE_MANUAL:
             return TAF_PH_PLMN_SEL_MODE_MANUAL;

        default:
            PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MMC_ConvertSrchModeToStkSrchMode: The input is invalid");
            return TAF_PH_PLMN_SEL_MODE_BUTT;
    }
}



VOS_VOID NAS_MMC_SndStkSearchModeChgEvt(
    VOS_UINT8                           ucReselMode
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulMsgLength;
    NAS_STK_SRCHMODE_CHG_EVENT_STRU    *pstSearchModeChgEvent = VOS_NULL_PTR;

    ulMsgLength    = sizeof(NAS_STK_SRCHMODE_CHG_EVENT_STRU);

    pstSearchModeChgEvent = (NAS_STK_SRCHMODE_CHG_EVENT_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                           (ulMsgLength - VOS_MSG_HEAD_LENGTH));
    if (VOS_NULL_PTR == pstSearchModeChgEvent)
    {
        PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MMC_SndStkSearchModeChgEvt: Alloc Msg Fail!");
        return;
    }

    PS_MEM_SET(&(pstSearchModeChgEvent->stSrchModeChgEvent), 0, sizeof(NAS_STK_SRCHMODE_CHG_EVENT_INFO_STRU));

    pstSearchModeChgEvent->ulReceiverPid = NAS_GetOamReceivePid(MAPS_STK_PID);
    pstSearchModeChgEvent->ulMsgId       = ID_NAS_STK_NET_SRCH_MODE_CHG_EVENT;

    pstSearchModeChgEvent->stSrchModeChgEvent.ucSrchMode = NAS_MMC_ConvertSrchModeToStkSrchMode(ucReselMode);

    ulRet = PS_SEND_MSG(WUEPS_PID_MMC, pstSearchModeChgEvent);
    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MMC_SndStkSearchModeChgEvt: Send Msg Fail!");
        return;
    }

    NAS_EventReport(WUEPS_PID_MMC,
                    NAS_OM_EVENT_STK_NETWORK_SEARCH_MODE_CHANGE_EVENT,
                    (VOS_VOID *)&ucReselMode,
                    NAS_OM_EVENT_STK_NETWORK_SEARCH_MODE_CHANGE_LEN);


    return;
}


VOS_VOID  NAS_MMC_UpdateOPlmnInfoFromNvim(
    VOS_UINT8                         *pucOPlmnData,
    VOS_UINT16                         usOPlmnNum
)
{
    NAS_MML_SIM_OPERPLMN_INFO_STRU     *pstOperPlmnInfo = VOS_NULL_PTR;
    NAS_MML_SIM_PLMN_WITH_RAT_STRU     *pstOplmnAddr    = VOS_NULL_PTR;

    /* ��ȡȫ�ֱ����ĵ�ַ */
    pstOperPlmnInfo = NAS_MML_GetSimOperPlmnList();
    pstOplmnAddr    = pstOperPlmnInfo->astOperPlmnInfo;

    /* ��ʼ��ȫ�ֱ����е�OPLMN��Ϣ��Ȼ���SIM�ж�ȡ��PLMN ID��RAT�洢��ȫ�ֱ����� */
    NAS_MML_InitSimOperPlmnInfo(pstOperPlmnInfo);

    /* ��NV�б�����û����õ�OPLMN��Ϣת��Ϊ�ڴ��е���Ϣ */
    NAS_MMC_ConverPlmnInfoFromSim(pucOPlmnData, usOPlmnNum, pstOplmnAddr);

    /* ����OPLMN�ĸ��� */
    pstOperPlmnInfo->usOperPlmnNum = usOPlmnNum;

    return;
}



/* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, Begin */

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetUsimAllRefreshFileNumber
 ��������  : ��ȡg_astNasUsimAllRefreshFileID����Ԫ����Ŀ����󲻳���USIMM_MAX_REFRESH_FILE_NUM
 �������  : ��
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��05��05��
   ��    ��   : c00318887
   �޸�����   : �����ɺ���
2.��    ��   : 2015��07��30��
  ��    ��   : c00318887
  �޸�����   : ���ӿڱ仯��������������USIM��sim��
*****************************************************************************/
VOS_UINT8  NAS_MMC_GetUsimAllRefreshFileNumber(VOS_VOID)
{
    VOS_UINT8                   ucNumber;
    NAS_MML_SIM_TYPE_ENUM_UINT8 ucSimType = NAS_MML_GetSimType();

    /* Modified by  for c00318887 for file refresh��Ҫ����������, 2015-7-30, begin */
    if (NAS_MML_SIM_TYPE_USIM == ucSimType)
    {
        ucNumber = sizeof(g_astNasUsimAllRefreshFileID)/sizeof(g_astNasUsimAllRefreshFileID[0]);
    }
    else if (NAS_MML_SIM_TYPE_SIM == ucSimType)
    {
        ucNumber = sizeof(g_astNasGsmAllRefreshFileID)/sizeof(g_astNasGsmAllRefreshFileID[0]);
    }
    else
    {
        ucNumber = 0;
    }
    /* Modified by  for c00318887 for file refresh��Ҫ����������, 2015-7-30, end */

    return ucNumber;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetUsimRefreshFileNumber
 ��������  : ��ȡg_astNasUsimAllRefreshFileID����Ԫ���е�file id
 �������  : ucIndex---�����±�
 �������  : file id
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��05��05��
   ��    ��   : c00318887
   �޸�����   : �����ɺ���
2.��    ��   : 2015��07��30��
  ��    ��   : c00318887
  �޸�����   : ���ӿڱ仯��������������USIM��sim��
*****************************************************************************/
VOS_UINT16  NAS_MMC_GetUsimAllRefreshFileId(VOS_UINT8 ucIndex)
{
    NAS_MML_SIM_TYPE_ENUM_UINT8 ucSimType = NAS_MML_GetSimType();

    /* Modified by  for c00318887 for file refresh��Ҫ����������, 2015-7-30, begin */
    if (NAS_MML_SIM_TYPE_USIM == ucSimType)
    {
        if (NAS_MMC_GetUsimAllRefreshFileNumber() <= ucIndex)
        {
            return USIMM_DEF_FILEID_BUTT;
        }

        return g_astNasUsimAllRefreshFileID[ucIndex];
    }
    else if (NAS_MML_SIM_TYPE_SIM == ucSimType)
    {
        if (NAS_MMC_GetUsimAllRefreshFileNumber() <= ucIndex)
        {
            return USIMM_DEF_FILEID_BUTT;
        }

        return g_astNasGsmAllRefreshFileID[ucIndex];
    }
    else
    {
        return USIMM_DEF_FILEID_BUTT;
    }
    /* Modified by  for c00318887 for file refresh��Ҫ����������, 2015-7-30, end */
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_BuildRefreshFileList
 ��������  : �����ȼ������ļ�����ʱ���������ļ��ṹ
 �������  : pstUsimRefreshInd  --- USIM ���ļ�������Ϣ
 �������  : pstRefreshFile     --- ͳ��ʵ�ʸ��µ��ļ��б�͸���
 �� �� ֵ  : ��
             
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��04��28��
   ��    ��   : c00318887
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��07��30��
   ��    ��   : c00318887
   �޸�����   : ���ӿڱ仯��������������USIM��sim��

*****************************************************************************/
VOS_VOID NAS_MMC_BuildRefreshFileList(
    USIMM_STKREFRESH_IND_STRU                  *pstUsimRefreshInd,
    NAS_MMC_USIMM_REFRESH_FILE_CONTENT_STRU    *pstRefreshFile
)
{
    VOS_UINT32      ulLoop;
    VOS_UINT16      usFileId;
    VOS_UINT16      usNumber;
    VOS_UINT16      usIndex;
    
    /* file list ����ʱ��copy ��Ϣ���EF ID */
    if (USIMM_REFRESH_FILE_LIST == pstUsimRefreshInd->enRefreshType)
    {
        pstRefreshFile->usEfNum = pstUsimRefreshInd->usEfNum;
        
        if (USIMM_MAX_REFRESH_FILE_NUM < pstRefreshFile->usEfNum)
        {
            pstRefreshFile->usEfNum = USIMM_MAX_REFRESH_FILE_NUM;
        }

        
        for (ulLoop = 0; ulLoop < pstRefreshFile->usEfNum; ulLoop++)
        {
            PS_MEM_CPY(&pstRefreshFile->astRefreshFile[ulLoop], &pstUsimRefreshInd->astEfId[ulLoop], sizeof(USIM_REFRESH_FILE_STRU)); 
        }

        return;
        
    }

    /* Modified by  for c00318887 for file refresh��Ҫ����������, 2015-7-30, begin */
    /* ALL FILE ����ʱ����ΪFILE ID ���ܴ��������ȼ��������ļ������Ҹ��ݿ����ͷֿ��� */  
    usNumber = NAS_MMC_GetUsimAllRefreshFileNumber();
    usIndex  = 0;
    
    for (ulLoop = 0; ulLoop < usNumber; ulLoop++)
    {
        usFileId = NAS_MMC_GetUsimAllRefreshFileId((VOS_UINT8)ulLoop);

        if (USIMM_DEF_FILEID_BUTT == usFileId)
        {
            continue;
        }

        pstRefreshFile->astRefreshFile[usIndex].usFileId     = usFileId;
        pstRefreshFile->astRefreshFile[usIndex].enAppType    = USIMM_GUTL_APP; 
        
        pstRefreshFile->astRefreshFile[usIndex].usPathLen    = 0;
        PS_MEM_SET(pstRefreshFile->astRefreshFile[usIndex].aucPath, 0x0, sizeof(pstRefreshFile->astRefreshFile[usIndex].aucPath));
    
        usIndex++;
    }
    
    pstRefreshFile->usEfNum = usIndex;
    /* Modified by  for c00318887 for file refresh��Ҫ����������, 2015-7-30, end */
}
/* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, end */


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


