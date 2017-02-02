

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "PsTypeDef.h"
#include "NasMmlCtx.h"
#include "NasMmlLib.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcSndLmm.h"
#include "NasMmcSndMm.h"
#include "NasMmSublayerDef.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "NasMmcSndMscc.h"
#include "NasMmcSndOm.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcCtx.h"
#include "NasMmcComFunc.h"
#include "NasMmcPlmnSelectionStrategy.h"
#include "NasMmcSndAps.h"
#include "NasMmcSndCds.h"
#include "NasMmcProcUsim.h"
#include "Nasrrcinterface.h"

#include "NasUtranCtrlInterface.h"
#include "NasMmcProcRegRslt.h"

#include "MsccMmcInterface.h"

#include "NasUsimmApi.h"
#include "NasMmcFsmMainTbl.h"
/* added by wx270776 for OM�ں�, 2015-08-21, begin */
#include "OmApi.h"
/* added by wx270776 for OM�ں�, 2014-08-21, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e(767)*/
#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_COM_FUNC_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*lint -save -e958 */

VOS_UINT32 NAS_MMC_IsNeedSndEplmn( VOS_VOID )
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnInfo  = VOS_NULL_PTR;
    VOS_UINT32                                              ulEplmnValidFlg;
    VOS_UINT32                                              ulRegFlag;

    VOS_UINT8                                               ucAsAnyCampOn;

    /* �޿�ʱ�����뷢�͵�Ч Plmn */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus())
    {
        return VOS_FALSE;
    }

    /*  ��ǰפ�����磬��Rplmnʱ�������� Eplmn������㣬�������㶪�� */
    pstEplmnInfo = NAS_MML_GetEquPlmnList();


    /* ��ǰ��EPlmn��֪ͨ�����,����RAU��������ATTACH,LAUʱ����Ҫɾ��Eplmn��24008:4.7.3.2.5
    if the attach attempt counter is smaller than 5 and, additionally,
    the update status is different from U1 UPDATED or the stored LAI is different
    from the one of the current serving cell, then the mobile station shall delete
    any LAI, TMSI, ciphering key sequence number stored in the SIM/USIM
    and list of equivalent PLMNs */
    if ( 0 == pstEplmnInfo->ucEquPlmnNum)
    {
        /* û��EPlmnʱ����֪ͨ����㵱ǰפ�������� */
        return VOS_TRUE;
    }

    if (VOS_FALSE == NAS_MML_CompareBcchPlmnwithSimPlmn(NAS_MML_GetCurrCampPlmnId(), &(pstEplmnInfo->astEquPlmnAddr[0])))
    {
        return VOS_FALSE;
    }

    ulEplmnValidFlg   = NAS_MML_GetEplmnValidFlg();
    ulRegFlag         = NAS_MMC_GetUserSpecPlmnRegisterStatus();

    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        /* �ֶ�����ģʽ�ж�eplmn�б��Ƿ���Ч����Ч�򷵻� */
        if ((VOS_FALSE == ulRegFlag)
         || (VOS_FALSE == ulEplmnValidFlg))
        {
            return VOS_FALSE;
        }
    }

    ucAsAnyCampOn = NAS_MMC_GetAsAnyCampOn();

    /* �����3GPP2����ע�ᣬ��ǰLΪ����פ������������ע�� */
    if ((NAS_MMC_REG_CONTROL_BY_3GPP_MMC != NAS_MMC_GetRegCtrl())
     && (VOS_TRUE == ucAsAnyCampOn))
    {
        return VOS_FALSE;
    }


    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_GetLaiForbTypeManualSelMode(
    NAS_MML_LAI_STRU                   *pstLai
)
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnInfo  = VOS_NULL_PTR;
    VOS_UINT32                          ulRlst;
    VOS_UINT32                          ulRegFlag;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          aulComparedMcc[NAS_MML_ROAM_ENABLED_MAX_MCC_NUMBER];

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;
#endif
    VOS_UINT32                          ulEplmnValidFlg;

    /* �ֶ�ģʽ��ǰPlmn����Eplmn�������û�ָ�����粻ͬʱ,��ֹע�� */
    pstEplmnInfo = NAS_MML_GetEquPlmnList();

    ulRlst = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(&(pstLai->stPlmnId),
                                            pstEplmnInfo->ucEquPlmnNum,
                                            pstEplmnInfo->astEquPlmnAddr);

    ulRegFlag = NAS_MMC_GetUserSpecPlmnRegisterStatus();
    ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

    pstUserSpecPlmn = NAS_MMC_GetUserSpecPlmnId();

    /* LTE��ֹ��������ʱ����ǰ�û�ָ��������ʱ��������Ӧ����forbidden���� */
#if (FEATURE_ON == FEATURE_LTE)
    enRatType = NAS_MML_GetCurrNetRatType();

    if ((VOS_FALSE == NAS_MML_GetLteRoamAllowedFlg())
     && (NAS_MML_NET_RAT_TYPE_LTE == enRatType))
     {
        /* ��ȡ��Ӫ�̶��Ƶ�MCC�б� */
        NAS_MML_GetRoamEnabledMccList(aulComparedMcc);

        /* ��ǰפ��PLMN IDΪ������������ */
        if (VOS_FALSE == NAS_MML_IsMccInDestMccList(pstUserSpecPlmn->stPlmnId.ulMcc, NAS_MML_ROAM_ENABLED_MAX_MCC_NUMBER, aulComparedMcc))
        {
            return NAS_MML_PLMN_FORBID_PLMN;
        }
     }
#endif

    if ((VOS_TRUE== NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstLai->stPlmnId), &(pstUserSpecPlmn->stPlmnId)))
     || ((VOS_TRUE == ulRegFlag)
      && (VOS_TRUE == ulRlst)
      && (VOS_TRUE == ulEplmnValidFlg)))
    {
        return   NAS_MML_GetLaiForbType(pstLai);
    }
    else
    {
        return NAS_MML_PLMN_FORBID_PLMN;
    }

}


VOS_UINT32 NAS_MMC_GetLaiForbTypeAutoSelMode(
    NAS_MML_LAI_STRU                   *pstLai
)
{

    return NAS_MML_GetLaiForbType(pstLai);


}
VOS_UINT32 NAS_MMC_GetCurrentLaiForbbidenType(VOS_VOID)
{
    NAS_MML_LAI_STRU                                       *pstCurrentLai = VOS_NULL_PTR;
    VOS_UINT32                                              ulPlmnLaType;
    NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8                  enPlmnSelMode;
    NAS_MML_SIM_STATUS_STRU                                *pstSimStatus    = VOS_NULL_PTR;

    pstSimStatus = NAS_MML_GetSimStatus();

    /* ��USIM������SIM����Чʱ������Ҫ�ж�FORBIDDEN��־��ֱ�ӷ��� */
    if ( VOS_FALSE == NAS_MML_GetSimPresentStatus() )
    {
        return NAS_MML_PLMN_FORBID_NULL;
    }

    if (( VOS_FALSE == pstSimStatus->ucSimPsRegStatus)
     && ( VOS_FALSE == pstSimStatus->ucSimCsRegStatus))
    {
        return NAS_MML_PLMN_FORBID_NULL;
    }

    enPlmnSelMode = NAS_MMC_GetPlmnSelectionMode();

    pstCurrentLai  = NAS_MML_GetCurrCampLai();

    /* ����ʱ��ǰפ��������Ϣ��Ĭ����Чֵ�������жϽ�ֹ���� */
    if (VOS_FALSE == NAS_MML_IsPlmnIdValid(&pstCurrentLai->stPlmnId))
    {
        return NAS_MML_PLMN_FORBID_NULL;
    }

    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == enPlmnSelMode)
    {
        ulPlmnLaType =  NAS_MMC_GetLaiForbTypeManualSelMode(pstCurrentLai);
    }
    /*�Զ�ģʽ�½�ֹ��Ϣ��ȡ*/
    else
    {
        ulPlmnLaType = NAS_MMC_GetLaiForbTypeAutoSelMode(pstCurrentLai);
    }

    /*���ؽ�ֹ��Ϣ*/
    return ulPlmnLaType;
}


VOS_UINT32 NAS_MMC_GetHPlmnSpecDomainAccessCapa(
    NAS_MMC_REG_DOMAIN_ENUM_UINT8       enRegCnDomain
)
{
    NAS_MMC_PLMN_REG_REJ_CTX_STRU      *pstRegRejCtx       = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstCurrPlmn        = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                   *pstCurrLai         = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;
    VOS_UINT8                           ucCurrCampRac;
    NAS_MMC_REG_DOMAIN_ENUM_UINT8       enDomain;

    if ((NAS_MMC_REG_DOMAIN_CS != enRegCnDomain)
     && (NAS_MMC_REG_DOMAIN_PS != enRegCnDomain)
#if   (FEATURE_ON == FEATURE_LTE)
     && (NAS_MMC_REG_DOMAIN_EPS !=  enRegCnDomain)
#endif
     )
    {
        return VOS_TRUE;
    }

    /* ��ȡ��ǰפ����PLMN */
    pstCurrPlmn = NAS_MML_GetCurrCampPlmnId();

    /* ��ǰפ��PLMN����HPLMN�б��У���ֱ�ӷ��� */
    if (VOS_FALSE ==  NAS_MML_ComparePlmnIdWithHplmn(pstCurrPlmn))
    {
         return VOS_TRUE;
    }

    /* ��ȡHPLMNע�ᱻ�ܵ��б� */
    pstRegRejCtx       = NAS_MMC_GetPlmnRegRejInfo();

    /* ��ǰפ��PLMN��HPLMNע�ᱻ���б��У���ֱ�ӷ��� */
    ulIndex = NAS_MMC_GetPlmnIndexInRegInfoList(pstCurrPlmn,
                             pstRegRejCtx->ucPlmnRegInfoNum, pstRegRejCtx->astPlmnRegInfoList);

    if (NAS_MML_INVALID_INDEX == ulIndex)
    {
        return VOS_TRUE;
    }

    /* ��ȡ��ǰפ����LAI */
    pstCurrLai = NAS_MML_GetCurrCampLai();

    NAS_MMC_GetHplmnRejDomainInfo(&enDomain);

    if (enDomain & enRegCnDomain)
    {
        if (NAS_MMC_REG_DOMAIN_CS == enRegCnDomain)
        {
            if ( (pstRegRejCtx->astPlmnRegInfoList[ulIndex].aucLac[0] == pstCurrLai->aucLac[0])
              && (pstRegRejCtx->astPlmnRegInfoList[ulIndex].aucLac[1] == pstCurrLai->aucLac[1]) )
            {
                return VOS_FALSE;
            }
        }
        else
        {
           ucCurrCampRac = NAS_MML_GetCurrCampRac();
           if ( (pstRegRejCtx->astPlmnRegInfoList[ulIndex].aucLac[0] == pstCurrLai->aucLac[0])
             && (pstRegRejCtx->astPlmnRegInfoList[ulIndex].aucLac[1] == pstCurrLai->aucLac[1])
             && (pstRegRejCtx->astPlmnRegInfoList[ulIndex].ucRac == ucCurrCampRac) )
           {
               return VOS_FALSE;
           }
        }
    }
    return VOS_TRUE;
}
VOS_UINT32  NAS_MMC_GetPlmnIndexInRegInfoList(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    VOS_UINT32                          ulRegPlmnListNum,
    NAS_MMC_PLMN_REG_INFO_STRU         *pstPlmnRegList
)
{
    VOS_UINT32                          i;

    for ( i = 0; i < ulRegPlmnListNum; i++ )
    {
        /* pstPlmnRegList�洢���� BCCH�е�ֵ��pstPlmnId����ʱ���е� Plmn */
        if ( VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstPlmnRegList[i].stPlmnId), pstPlmnId) )
        {
            break;
        }
    }

    if (i < ulRegPlmnListNum)
    {
        return i;
    }
    else
    {
        return NAS_MML_INVALID_INDEX;
    }
}
VOS_UINT32  NAS_MMC_GetOptMask_WasSysinfo(
    RRMM_SYS_INFO_IND_STRU             *pstRrMmSysInfoInd
)
{
    VOS_UINT32                          ulBitMask;

    ulBitMask = 0;

    /* ����ϵͳ��Ϣ�����ݣ����Maskֵ */
    if (VOS_TRUE == pstRrMmSysInfoInd->bitOpPlmnId)
    {
        ulBitMask |= RRC_NAS_SYS_MSK_PLMN;
    }

    if (VOS_TRUE == pstRrMmSysInfoInd->bitOpCsDrx)
    {
        ulBitMask |= RRC_NAS_SYS_MSK_CS_DRX;
    }

    if (VOS_TRUE == pstRrMmSysInfoInd->bitOpPsDrx)
    {
        ulBitMask |= RRC_NAS_SYS_MSK_PS_DRX;
    }

    if ((0< pstRrMmSysInfoInd->ucCsInfoSize)
     || (0< pstRrMmSysInfoInd->ucPsInfoSize))
    {
        ulBitMask |= RRC_NAS_SYS_MSK_CSPS_INFO;
    }

    return ulBitMask;
}

/* ɾ��NAS_MMC_ConvertUserSpecAccessMode2MmlRat����*/




TAF_SYS_SUBMODE_ENUM_UINT8 NAS_MMC_CovertMmlSysSubModeToMsccSysSubMode(
    NAS_MML_RRC_SYS_SUBMODE_ENUM_UINT8  enSysSubMode
)
{
    VOS_UINT32                          i;

    VOS_UINT8                           aucSysSubModeMapTable[NAS_MML_MAX_SYS_SUBMODE_NUM][2] =
    {
        {NAS_MML_RRC_SYS_SUBMODE_NULL,        TAF_SYS_SUBMODE_NONE       },
        {NAS_MML_RRC_SYS_SUBMODE_GSM,         TAF_SYS_SUBMODE_GSM        },
        {NAS_MML_RRC_SYS_SUBMODE_GPRS,        TAF_SYS_SUBMODE_GPRS       },
        {NAS_MML_RRC_SYS_SUBMODE_EDGE,        TAF_SYS_SUBMODE_EDGE       },
        {NAS_MML_RRC_SYS_SUBMODE_WCDMA,       TAF_SYS_SUBMODE_WCDMA      },
        {NAS_MML_RRC_SYS_SUBMODE_HSDPA,       TAF_SYS_SUBMODE_HSDPA      },
        {NAS_MML_RRC_SYS_SUBMODE_HSUPA,       TAF_SYS_SUBMODE_HSUPA      },
        {NAS_MML_RRC_SYS_SUBMODE_HSDPA_HSUPA, TAF_SYS_SUBMODE_HSDPA_HSUPA},
        {NAS_MML_RRC_SYS_SUBMODE_LTE,         TAF_SYS_SUBMODE_LTE        },
    };

    for (i = 0; i < NAS_MML_MAX_SYS_SUBMODE_NUM; i++)
    {
        if (enSysSubMode == aucSysSubModeMapTable[i][0])
        {
            return aucSysSubModeMapTable[i][1];
        }
    }

    return TAF_SYS_SUBMODE_BUTT;
}


VOS_UINT32 NAS_MMC_IsHplmnTimerLenValid( VOS_VOID )
{
    NAS_MML_BG_SEARCH_CFG_INFO_STRU    *pstBgSearchCfg = VOS_NULL_PTR;

    pstBgSearchCfg = NAS_MML_GetBgSearchCfg();

    /* H3G��������(VPLMN�·��״���HPLMNʱ��NV������)��*/
    if (VOS_TRUE == pstBgSearchCfg->stNonFirstHplmnTimerPeriod.ucNvimActiveFlg)
    {
        /* HPLMN��ʱ����ʱ���Ӵ�NV��en_NV_Item_SearchHplmnTtimerValue�л�ȡ��
           NV��ֵ����0ʱ��HPLMN��ʱ��ʱ����Ч */
        if (pstBgSearchCfg->stNonFirstHplmnTimerPeriod.ulNonFirstHplmnTimerLen != 0)
        {
            return VOS_TRUE;
        }
    }
    else
    {
        /* HPLMN��ʱ����ʱ����USIM�ļ�EFHPPLMN (0x6F31 Higher Priority PLMN search period)
           �л�ȡ�����ļ���ֵ����0ʱ��HPLMN��ʱ��ʱ����Ч */
        if (NAS_MML_GetSimHplmnTimerLen() != 0)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_UINT32 NAS_MMC_IsHighPrioPlmnSearchVaild( VOS_VOID )
{
    /* �ֶ�ģʽ�·�����Ч */
    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        return VOS_FALSE;
    }

    if (VOS_FALSE == NAS_MML_IsUsimStausValid())
    {
        return VOS_FALSE;
    }

    /* HPLMN TIMER LEN��ʱ��ʱ����Ч */
    if ( VOS_FALSE == NAS_MMC_IsHplmnTimerLenValid() )
    {
        return VOS_FALSE;
    }

    /* ������Ч */
    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_IsCampOnHPlmn(VOS_VOID)
{
    NAS_MML_PLMN_ID_STRU               *pstCurrCampPlmnId = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnList      = VOS_NULL_PTR;
    VOS_UINT32                          i;

    /* ȡ�õ�ǰפ����PLMN ID */
    pstCurrCampPlmnId = NAS_MML_GetCurrCampPlmnId();

    /* ��HPLMN��ͬ��������פ��HPLMN�� */
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(pstCurrCampPlmnId))
    {
        return VOS_TRUE;
    }

    pstEplmnList  = NAS_MML_GetEquPlmnList();

    /* �����ǰ������EPLMN��1����ͬ,��ʾ�洢��EPLMN�ǵ�ǰ�����EPLMN,��ʱ���ñȽ�EPLMN�� */
    if (VOS_FALSE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstCurrCampPlmnId,
                                                       &pstEplmnList->astEquPlmnAddr[0]))
    {
        return VOS_FALSE;
    }

    /* EPLMN�Ǵ������±�1��ʼ��ŵģ������±�0��ŵ���RPLMN */
    for ( i = 1; i < pstEplmnList->ucEquPlmnNum; i++ )
    {
        if (VOS_FALSE == NAS_MML_ComparePlmnMcc(pstCurrCampPlmnId->ulMcc, pstEplmnList->astEquPlmnAddr[i].ulMcc))
        {
            continue;
        }

        /* ���HOME PLMN��EPLMN�У��Һ͵�ǰפ����PLMN��MCC��ͬ��
           ��Ϊ��ǰ�Ѿ���HOME PLMN�� */
        if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(&pstEplmnList->astEquPlmnAddr[i]))
        {
            return VOS_TRUE;
        }
    }


    return VOS_FALSE;
}


VOS_UINT32 NAS_MMC_IsCampOnHighestPrioPlmn(VOS_VOID)
{
    NAS_MML_BG_SEARCH_CFG_INFO_STRU                        *pstBgSearchCfg           = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                                   *pstCurrCampPlmnId        = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEplmnList             = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stHighestPrioPlmnInfo;
    NAS_MML_AIS_ROAMING_CFG_STRU                           *pstRoamingCfg            = VOS_NULL_PTR;
    VOS_UINT32                                              ulIsCampOnHPlmn;
    NAS_MMC_HPLMN_SEARCH_REGARDLESS_MCC_CTX_STRU           *pstBgSearchRegardlessMccCtx = VOS_NULL_PTR;

    pstCurrCampPlmnId           = NAS_MML_GetCurrCampPlmnId();
    pstPlmnSelectionListInfo    = NAS_MMC_GetHighPrioPlmnList();
    pstBgSearchCfg              = NAS_MML_GetBgSearchCfg();
    pstEplmnList                = NAS_MML_GetEquPlmnList();

    pstBgSearchRegardlessMccCtx = NAS_MML_GetBgSearchRegardlessMccCtx();

    PS_MEM_SET(&stHighestPrioPlmnInfo,0x00, sizeof(stHighestPrioPlmnInfo));


    /* �����ǰ������Ч���򷵻�δפ����������ȼ������ϣ�����ģ�����󣬵�ǰפ��������
       ����ЧPLMNID */
    if ( VOS_FALSE == NAS_MML_IsPlmnIdValid(pstCurrCampPlmnId) )
    {
        return VOS_FALSE;
    }

    pstRoamingCfg  = NAS_MML_GetAisRoamingCfg();
    if ( VOS_TRUE == NAS_MMC_IsAisRoamingEffect())
    {
        /* �ж��Ƿ�פ���������PLMN��,�����Ѿ�����Ӫ��ȷ��,
        AIS��TOT����������֮�䲻������ΪEPLMN��С��֮��Ҳ��������Ϊ������ϵ
        */
        return NAS_MML_IsBcchPlmnIdInDestSimPlmnList(NAS_MML_GetCurrCampPlmnId(),
            1, &(pstRoamingCfg->stHighPrioPlmnId));
    }



    ulIsCampOnHPlmn = NAS_MMC_IsCampOnHPlmn();
    /* �����ǰ��פ����(E)HPLMN��, ��Ϊפ����������ȼ������� */
    if (VOS_TRUE == ulIsCampOnHPlmn)
    {
        return VOS_TRUE;
    }


    if (VOS_FALSE == NAS_MMC_IsCampOnHPlmn())
    {
        /* Vplmn��Hplmn��ͬ������ʱ,����ص�Hplmn�Ķ������Կ��ش�ʱ */
        if (VOS_TRUE == pstBgSearchCfg->ucSpecialRoamFlg)
        {
            return VOS_FALSE;
        }

        /* AT&T BG�Ѳ����ǹ����붨�ƿ��ش򿪣���VPLMN�������ڶ����б��� */
        if (VOS_TRUE == NAS_MML_IsMccInDestMccList(pstCurrCampPlmnId->ulMcc, pstBgSearchRegardlessMccCtx->ucCustomMccNum, pstBgSearchRegardlessMccCtx->aulCostumMccList))
        {
            return VOS_FALSE;
        }
    }

    /* �Ӹ����ȼ��б��л�ȡ�͵�ǰפ��������ͬ�������������ȼ����� */
    if (VOS_FALSE == NAS_MMC_GetHighestPrioPlmnInHighPrioPlmnList(pstPlmnSelectionListInfo,
                                                          &stHighestPrioPlmnInfo))
    {
        /* û����ͬ������ĸ����ȼ����磬��Ϊ�Ѿ�פ����������ȼ����磬����vos_true,��������hplmn��ʱ��*/
        return VOS_TRUE;
    }

    /* �Ƚ�VPLMN�͸����ȼ��������ȼ��Ƿ���ͬ����ͬ����Ϊ�Ѿ�פ����������ȼ����� */
    if (VOS_TRUE == NAS_MMC_CompareVPlmnPrioWithHighPrioPlmn(pstCurrCampPlmnId,
                                                             NAS_MML_GetCurrNetRatType(),
                                                             pstEplmnList,
                                                             &stHighestPrioPlmnInfo ))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MMC_IsNeedStartHPlmnTimer(VOS_VOID)
{
    NAS_MML_BG_SEARCH_CFG_INFO_STRU    *pstBgSearchCfg           = VOS_NULL_PTR;


    /* �жϵ�ǰ�����ȼ������Ƿ���Ч���ֶ�ģʽ��SIM������λ��CS��PS������Ч
       ��HPLMN��ʱ��ʱ��Ϊ0ʱ����Ϊ��ǰ��������HPLMN��ʱ����������и����ȼ����� */
    if (VOS_FALSE == NAS_MMC_IsHighPrioPlmnSearchVaild())
    {
        return VOS_FALSE;
    }

    /* Ϊ�˱��ⷴ�����ø����ȼ������Ĵ�����10s�����Գ��Զ�ʱ�������ڼ䲻����HPLMN��ʱ�� */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH))
    {
        return VOS_FALSE;
    }

    /* ���HPLMN�Ѿ������У���������,on plmn���յ�psע������csע���������ж��Ƿ���Ҫ����hplmn��ʱ�������ܴ����������е���� */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_HPLMN_TIMER))
    {
        return VOS_FALSE;
    }

    pstBgSearchCfg            = NAS_MML_GetBgSearchCfg();

    /* ����Ѿ�פ����������ȼ����� */
    if (VOS_TRUE == NAS_MMC_IsCampOnHighestPrioPlmn())
    {
        /* �����ǿ��Hplmn����,���綨�����Կ��ش�: ����Hplmn Timer��ʱ��,
           ֻҪû��פ����home PLMN��,Ҳ��Ҫ�����˶�ʱ��,��һ������2Min,��������T Min����*/
        if ((VOS_FALSE == NAS_MMC_IsCampOnHPlmn())
         && (VOS_TRUE == pstBgSearchCfg->ucEnhancedHplmnSrchFlg))
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }

    return VOS_TRUE;
}





VOS_VOID NAS_MMC_ConvertRrcPlmnList2SearchedPlmnListInfo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat,
    RRC_PLMN_ID_LIST_STRU                                  *pstPlmnIdList,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    VOS_UINT32                          i;

    pstSearchedPlmnListInfo->enRatType = enRat;

    /* ѭ��pstPlmnIdList�е�ÿһ��������PLMN ID,��ֵ��pstIntraPlmnSearchInfo */
    for (i = 0; ((i < pstPlmnIdList->ulHighPlmnNum) && (i < NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM)); i++)
    {
        pstSearchedPlmnListInfo->astHighPlmnList[i].ulMcc         = pstPlmnIdList->aHighPlmnList[i].stPlmnId.ulMcc;
        pstSearchedPlmnListInfo->astHighPlmnList[i].ulMnc         = pstPlmnIdList->aHighPlmnList[i].stPlmnId.ulMnc;
    }
    pstSearchedPlmnListInfo->ulHighPlmnNum = i;

    /* ѭ��pstPlmnIdList�е�ÿһ��������PLMN ID,��PLMN ID��������ֵ��pstIntraPlmnSearchInfo */
    for (i = 0; ((i < pstPlmnIdList->ulLowPlmnNum) && (i < NAS_MMC_INTRA_MAX_LOW_QUALITY_PLMN_NUM)); i++)
    {
        pstSearchedPlmnListInfo->astLowPlmnList[i].stPlmnId.ulMcc = pstPlmnIdList->aLowPlmnList[i].PlmnId.stPlmnId.ulMcc;
        pstSearchedPlmnListInfo->astLowPlmnList[i].stPlmnId.ulMnc = pstPlmnIdList->aLowPlmnList[i].PlmnId.stPlmnId.ulMnc;
        pstSearchedPlmnListInfo->astLowPlmnList[i].lRscp          = pstPlmnIdList->aLowPlmnList[i].lRscp;
    }
    pstSearchedPlmnListInfo->ulLowPlmnNum = i;

    return;
}


VOS_VOID NAS_MMC_ConvertRrcBgPlmnSearchRslt2SearchedPlmnListInfo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat,
    RRMM_BG_PLMN_SEARCH_CNF_ST                             *pstBgSearchRslt,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulTotalNum;

    /* ���õ�ǰ����BG�ѵĽ��뼼�� */
    pstSearchedPlmnListInfo->enRatType = enRat;

    /* ѭ��pstBgPlmnIdList�е�ÿһ��PLMN ID, ��ֵ��pstIntraPlmnSearchInfo */
    ulTotalNum                             = pstBgSearchRslt->ucPlmnNum;
    pstSearchedPlmnListInfo->ulHighPlmnNum = pstBgSearchRslt->ucPlmnNum;

    if (pstSearchedPlmnListInfo->ulHighPlmnNum > NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM)
    {
        pstSearchedPlmnListInfo->ulHighPlmnNum = NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM;
        ulTotalNum                             = NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM;
    }

    pstSearchedPlmnListInfo->ulLowPlmnNum  = 0x0;

    for ( i = 0 ; i < ulTotalNum; i++ )
    {
        pstSearchedPlmnListInfo->astHighPlmnList[i].ulMcc = pstBgSearchRslt->astPlmnId[i].stPlmnId.ulMcc;
        pstSearchedPlmnListInfo->astHighPlmnList[i].ulMnc = pstBgSearchRslt->astPlmnId[i].stPlmnId.ulMnc;
    }


    return;
}

#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID NAS_MMC_ConvertLmmPlmnList2SearchedPlmnListInfo(
    MMC_LMM_PLMN_ID_LIST_STRU                              *pstLMMPlmnList,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_ID_STRU                stPlmn;
    VOS_UINT32                          i;
    NAS_MML_SIM_FORMAT_PLMN_ID          stSimPlmn;

    PS_MEM_SET(&stSimPlmn, 0, sizeof(NAS_MML_SIM_FORMAT_PLMN_ID));
    pstSearchedPlmnListInfo->enRatType = NAS_MML_NET_RAT_TYPE_LTE;

    /* ѭ��pstLMMPlmnList�е�ÿһ��������PLMN ID,��ֵ��pstIntraPlmnSearchInfo */
    for (i = 0; ((i < pstLMMPlmnList->ulHighPlmnNum) && (i < NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM)); i++)
    {
        /* ��ת��ΪSIM��ʽ */
        PS_MEM_CPY(stSimPlmn.aucSimPlmn, pstLMMPlmnList->astHighPlmnWithRatList[i].aucPlmnId, MMC_LMM_PLMN_ID_LEN);

        NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmn, &stPlmn);

        pstSearchedPlmnListInfo->astHighPlmnList[i]         = stPlmn;
    }

    pstSearchedPlmnListInfo->ulHighPlmnNum = i;

    /* ѭ��pstLMMPlmnList�е�ÿһ��������PLMN ID,��PLMN ID��������ֵ��pstIntraPlmnSearchInfo */
    for (i = 0; ((i < pstLMMPlmnList->ulLowPlmnNum) && (i < NAS_MMC_INTRA_MAX_LOW_QUALITY_PLMN_NUM)); i++)
    {
        /* ��ת��ΪSIM��ʽ */
        PS_MEM_CPY(stSimPlmn.aucSimPlmn, pstLMMPlmnList->astLowPlmnWithRatList[i].stPlmnIdWithRat.aucPlmnId, MMC_LMM_PLMN_ID_LEN);

        NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmn, &stPlmn);

        pstSearchedPlmnListInfo->astLowPlmnList[i].lRscp    = pstLMMPlmnList->astLowPlmnWithRatList[i].lRscp;


        pstSearchedPlmnListInfo->astLowPlmnList[i].stPlmnId = stPlmn;
    }
    pstSearchedPlmnListInfo->ulLowPlmnNum = i;

    return;
}


VOS_VOID NAS_MMC_ConvertLmmBgPlmnSearchRslt2SearchedPlmnListInfo(
    LMM_MMC_BG_PLMN_SEARCH_CNF_STRU                        *pstLmmPlmnList,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo,
     NAS_MML_NET_RAT_TYPE_ENUM_UINT8                        enRatType
)
{
    VOS_UINT32                          ulIndex;
    MMC_LMM_PLMN_ID_STRU                stLmmPlmn;
    NAS_MML_PLMN_ID_STRU                stGUNasPlmn;
    VOS_UINT32                          ulTotalNum;

    pstSearchedPlmnListInfo->enRatType     = enRatType;

    ulTotalNum                             = pstLmmPlmnList->ulPlmnNum;
    pstSearchedPlmnListInfo->ulHighPlmnNum = pstLmmPlmnList->ulPlmnNum;

    if (pstSearchedPlmnListInfo->ulHighPlmnNum > NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM)
    {
        pstSearchedPlmnListInfo->ulHighPlmnNum = NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM;
        ulTotalNum                             = NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM;
    }

    pstSearchedPlmnListInfo->ulLowPlmnNum  = 0x0;

    for ( ulIndex = 0; ulIndex < ulTotalNum; ulIndex++ )
    {
        pstSearchedPlmnListInfo->enRatType = pstLmmPlmnList->astPlmnIdWithRatList[ulIndex].enPlmnRat;
        PS_MEM_CPY(stLmmPlmn.aucPlmnId, pstLmmPlmnList->astPlmnIdWithRatList[ulIndex].aucPlmnId, MMC_LMM_PLMN_ID_LEN);
        NAS_MMC_ConvertLmmPlmnToGUNasFormat(&stLmmPlmn, &stGUNasPlmn);
        pstSearchedPlmnListInfo->astHighPlmnList[ulIndex].ulMcc = stGUNasPlmn.ulMcc;
        pstSearchedPlmnListInfo->astHighPlmnList[ulIndex].ulMnc = stGUNasPlmn.ulMnc;
    }

    return;
}
#endif


VOS_UINT32 NAS_MMC_IsPlmnWithRatInPlmnList (
    NAS_MML_PLMN_ID_STRU                                   *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    VOS_UINT32                                              ulPlmnNum
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    if (ulPlmnNum > pstPlmnSelectionListInfo->usSearchPlmnNum)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MML_IsPlmnWithRatInPlmnList: Plmn Num Overflow!");
        return VOS_FALSE;
    }

    /* ����Ӧ���뼼����PLMN ID �Ƿ����б��� */
    for (i = 0; i < ulPlmnNum; i++)
    {
        for (j = 0; j < pstPlmnSelectionListInfo->astPlmnSelectionList[i].ucRatNum; j++)
        {
            if ((VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstPlmnId,
                                                                 &(pstPlmnSelectionListInfo->astPlmnSelectionList[i].stPlmnId)))
             && (enRat == pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j].enRatType))
            {
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}
VOS_VOID NAS_MMC_ConvertPlmnId2NasFormat(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    VOS_UINT8                           ucPlmnMncNum
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           aucTmp[4];
    VOS_UINT32                          ulMcc;
    VOS_UINT32                          ulMnc;

    PS_MEM_SET(aucTmp, 0, sizeof(aucTmp));
    ulMcc = 0;
    ulMnc = 0;

    ulMcc            = pstPlmnId->ulMcc;
    pstPlmnId->ulMcc = 0;

    for ( i = 0 ; i < 3 ; i++ )
    {
        aucTmp[i]     = ulMcc & 0x0f;
        ulMcc         >>=  4;
    }

    pstPlmnId->ulMcc  =  aucTmp[2]
                     |((VOS_UINT32)aucTmp[1] << 8)
                     |((VOS_UINT32)aucTmp[0] << 16);

    /*����MNCǰ����ձ���*/
    PS_MEM_SET(aucTmp, 0, sizeof(aucTmp));

    ulMnc           = pstPlmnId->ulMnc;
    pstPlmnId->ulMnc  = 0;

    for ( i = 0 ; i < 3 ; i++ )
    {
        aucTmp[i]     = ulMnc & 0x0f;
        ulMnc         >>=  4;
    }

    if(NAS_MML_MNC_LENGTH_TWO_BYTES_IN_IMSI == ucPlmnMncNum)
    {
        pstPlmnId->ulMnc =  aucTmp[1]
                         |((VOS_UINT32)aucTmp[0] << 8)
                         |0x0f0000;
    }
    else
    {
        pstPlmnId->ulMnc =   aucTmp[2]
                     |((VOS_UINT32)aucTmp[1] << 8)
                     |((VOS_UINT32)aucTmp[0] << 16);
    }

    return;
}
VOS_VOID NAS_MMC_UpdateDplmnNplmnInfo(
    NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU                 *pstNvimCfgDPlmnNPlmnInfo
)
{
    VOS_UINT32                                              ulStep;
    NAS_MML_PLMN_ID_STRU                                    stTempPlmn;
    NAS_MML_SIM_FORMAT_PLMN_ID                              stNvimPlmn;
    VOS_UINT16                                              usSimRat;
    NAS_MMC_REG_DOMAIN_ENUM_UINT8                           enRegDomain;
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;

    /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-20, begin */
    NAS_MMC_DPLMN_NPLMN_SETTING_TYPE_ENUM_UINT8             enType;
    /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-20, end */

    pstDPlmnNPlmnCfgInfo     = NAS_MMC_GetDPlmnNPlmnCfgInfo();
    enRegDomain              = NAS_MMC_REG_DOMAIN_BUTT;
    PS_MEM_SET(&stTempPlmn, 0, sizeof(stTempPlmn));
    PS_MEM_SET(&stNvimPlmn, 0, sizeof(stNvimPlmn));

    /* ��NV�е�DPLMN���浽�ڴ���,��Ҫ��ֹ����Խ�� */
    if ( pstNvimCfgDPlmnNPlmnInfo->usDplmnListNum > NAS_MMC_MAX_CFG_DPLMN_NUM )
    {
        pstNvimCfgDPlmnNPlmnInfo->usDplmnListNum = NAS_MMC_MAX_CFG_DPLMN_NUM;
    }

    for ( ulStep = 0; ulStep < pstNvimCfgDPlmnNPlmnInfo->usDplmnListNum; ulStep++ )
    {
        /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-20, begin */
        PS_MEM_CPY(stNvimPlmn.aucSimPlmn,
            pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList + (ulStep * (NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN)), NAS_MML_SIM_PLMN_ID_LEN);

        /* ת��PLMN IDΪMMC�ڲ��ĸ�ʽ���洢 */
        NAS_MMC_ConvertSimPlmnToNasPLMN(&stNvimPlmn, &stTempPlmn);


        /* �洢PLMN��Ӧ��RAT */
        usSimRat    = (VOS_UINT16)(pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + NAS_MML_PLMN_WITH_RAT_FIRST_RAT_OFFSET] << NAS_MML_OCTET_MOVE_EIGHT_BITS)
                                | pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + NAS_MML_PLMN_WITH_RAT_SECOND_RAT_OFFSET];

        enRegDomain = (VOS_UINT8)(pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + NAS_MML_PLMN_WITH_RAT_UNIT_LEN]);

        enType      = (VOS_UINT8)(pstNvimCfgDPlmnNPlmnInfo->aucDPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + NAS_MMC_DPLMN_NPLMN_NV_PRESETING_FLAG_INDEX]);
        /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-20, end */

        /* ������Ҫ��ӵ�DPLMN�Ѿ����ڣ�����Ҫ�ظ���� */
        if (VOS_TRUE == NAS_MMC_IsPlmnIdWithSimRatInSimPlmnWithRegDomainList(&stTempPlmn, usSimRat, pstDPlmnNPlmnCfgInfo->usDplmnListNum, pstDPlmnNPlmnCfgInfo->astDPlmnList))
        {
            continue;
        }

        if ((VOS_TRUE == NAS_MML_IsPlmnIdValid(&stTempPlmn))
         && (NAS_MML_INVALID_SIM_RAT != usSimRat))
        {
            pstDPlmnNPlmnCfgInfo->astDPlmnList[pstDPlmnNPlmnCfgInfo->usDplmnListNum].stSimPlmnWithRat.stPlmnId = stTempPlmn;
            pstDPlmnNPlmnCfgInfo->astDPlmnList[pstDPlmnNPlmnCfgInfo->usDplmnListNum].stSimPlmnWithRat.usSimRat = usSimRat;
            pstDPlmnNPlmnCfgInfo->astDPlmnList[pstDPlmnNPlmnCfgInfo->usDplmnListNum].enRegDomain               = enRegDomain;

            /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-20, begin */
            pstDPlmnNPlmnCfgInfo->astDPlmnList[pstDPlmnNPlmnCfgInfo->usDplmnListNum].enType                    = enType;
            /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-20, end */

            pstDPlmnNPlmnCfgInfo->usDplmnListNum++;
        }
    }

    /* ��NV�е�NPLMN���浽�ڴ���,��Ҫ��ֹ����Խ�� */
    if ( pstNvimCfgDPlmnNPlmnInfo->usNplmnListNum > NAS_MMC_MAX_CFG_NPLMN_NUM )
    {
        pstNvimCfgDPlmnNPlmnInfo->usNplmnListNum = NAS_MMC_MAX_CFG_NPLMN_NUM;
    }

    for ( ulStep = 0; ulStep < pstNvimCfgDPlmnNPlmnInfo->usNplmnListNum; ulStep++ )
    {
        /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-20, begin */
        PS_MEM_CPY(stNvimPlmn.aucSimPlmn, pstNvimCfgDPlmnNPlmnInfo->aucNPlmnList + (ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN), NAS_MML_SIM_PLMN_ID_LEN);

        /* ת��PLMN IDΪMMC�ڲ��ĸ�ʽ���洢 */
        NAS_MMC_ConvertSimPlmnToNasPLMN(&stNvimPlmn, &stTempPlmn);


        /* �洢PLMN��Ӧ��RAT */
        usSimRat = (VOS_UINT16)(pstNvimCfgDPlmnNPlmnInfo->aucNPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + NAS_MML_PLMN_WITH_RAT_FIRST_RAT_OFFSET] << NAS_MML_OCTET_MOVE_EIGHT_BITS)
                     | pstNvimCfgDPlmnNPlmnInfo->aucNPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + NAS_MML_PLMN_WITH_RAT_SECOND_RAT_OFFSET];

        enRegDomain = (VOS_UINT8)(pstNvimCfgDPlmnNPlmnInfo->aucNPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + NAS_MML_PLMN_WITH_RAT_UNIT_LEN]);

        enType      = (VOS_UINT8)(pstNvimCfgDPlmnNPlmnInfo->aucNPlmnList[(ulStep * NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN) + NAS_MMC_DPLMN_NPLMN_NV_PRESETING_FLAG_INDEX]);
        /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-20, end */

        /* ������Ҫ��ӵ�NPLMN�Ѿ����ڣ�����Ҫ�ظ���� */
        if (VOS_TRUE == NAS_MMC_IsPlmnIdWithSimRatInSimPlmnWithRegDomainList(&stTempPlmn, usSimRat, pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList))
        {
            continue;
        }

        if ((VOS_TRUE == NAS_MML_IsPlmnIdValid(&stTempPlmn))
         && (NAS_MML_INVALID_SIM_RAT != usSimRat))
        {
            pstDPlmnNPlmnCfgInfo->astNPlmnList[pstDPlmnNPlmnCfgInfo->usNplmnListNum].stSimPlmnWithRat.stPlmnId = stTempPlmn;
            pstDPlmnNPlmnCfgInfo->astNPlmnList[pstDPlmnNPlmnCfgInfo->usNplmnListNum].stSimPlmnWithRat.usSimRat = usSimRat;
            pstDPlmnNPlmnCfgInfo->astNPlmnList[pstDPlmnNPlmnCfgInfo->usNplmnListNum].enRegDomain = enRegDomain;

            /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-20, begin */
            pstDPlmnNPlmnCfgInfo->astNPlmnList[pstDPlmnNPlmnCfgInfo->usNplmnListNum].enType                    = enType;
            /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-20, end */

            pstDPlmnNPlmnCfgInfo->usNplmnListNum++;
        }
    }

    return;
}


VOS_VOID NAS_MMC_UpdateDPlmnNPlmnFlagInfo(
    NAS_MMC_NVIM_CFG_DPLMN_NPLMN_FLAG_STRU                 *pstNvimCfgDPlmnNPlmnFlagInfo
)
{

    VOS_UINT32                                              ulStep;
    NAS_MML_PLMN_ID_STRU                                    stTempPlmn;
    NAS_MML_SIM_FORMAT_PLMN_ID                              stNvimPlmn;
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;

    pstDPlmnNPlmnCfgInfo     = NAS_MMC_GetDPlmnNPlmnCfgInfo();
    PS_MEM_SET(&stTempPlmn, 0, sizeof(stTempPlmn));
    PS_MEM_SET(&stNvimPlmn, 0, sizeof(stNvimPlmn));

    /* ��NV�е�CMCC HPLMN���浽�ڴ���,��Ҫ��ֹ����Խ�� */
    if ( pstNvimCfgDPlmnNPlmnFlagInfo->ucCMCCHplmnNum > NAS_MMC_MAX_CFG_HPLMN_NUM )
    {
        pstNvimCfgDPlmnNPlmnFlagInfo->ucCMCCHplmnNum = NAS_MMC_MAX_CFG_HPLMN_NUM;
    }

    for ( ulStep = 0; ulStep < pstNvimCfgDPlmnNPlmnFlagInfo->ucCMCCHplmnNum; ulStep++ )
    {
        PS_MEM_CPY(stNvimPlmn.aucSimPlmn,
            pstNvimCfgDPlmnNPlmnFlagInfo->aucCMCCHplmnList+ (ulStep * NAS_MML_SIM_PLMN_ID_LEN), NAS_MML_SIM_PLMN_ID_LEN);

        /* ת��PLMN IDΪMMC�ڲ��ĸ�ʽ���洢 */
        NAS_MMC_ConvertSimPlmnToNasPLMN(&stNvimPlmn, &stTempPlmn);

        if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&stTempPlmn))
        {
            pstDPlmnNPlmnCfgInfo->astCMCCHplmnList[pstDPlmnNPlmnCfgInfo->ucCMCCHplmnNum] = stTempPlmn;
            pstDPlmnNPlmnCfgInfo->ucCMCCHplmnNum++;
        }
    }

    /* ��NV�е�UNICOM HPLMN���浽�ڴ���,��Ҫ��ֹ����Խ�� */
    if ( pstNvimCfgDPlmnNPlmnFlagInfo->ucUNICOMHplmnNum > NAS_MMC_MAX_CFG_HPLMN_NUM )
    {
        pstNvimCfgDPlmnNPlmnFlagInfo->ucUNICOMHplmnNum = NAS_MMC_MAX_CFG_HPLMN_NUM;
    }

    for ( ulStep = 0; ulStep < pstNvimCfgDPlmnNPlmnFlagInfo->ucUNICOMHplmnNum; ulStep++ )
    {
        PS_MEM_CPY(stNvimPlmn.aucSimPlmn,
            pstNvimCfgDPlmnNPlmnFlagInfo->aucUNICOMHplmnList+ (ulStep * NAS_MML_SIM_PLMN_ID_LEN), NAS_MML_SIM_PLMN_ID_LEN);

        /* ת��PLMN IDΪMMC�ڲ��ĸ�ʽ���洢 */
        NAS_MMC_ConvertSimPlmnToNasPLMN(&stNvimPlmn, &stTempPlmn);

        if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&stTempPlmn))
        {
            pstDPlmnNPlmnCfgInfo->astUNICOMHplmnList[pstDPlmnNPlmnCfgInfo->ucUNICOMHplmnNum] = stTempPlmn;
            pstDPlmnNPlmnCfgInfo->ucUNICOMHplmnNum++;
        }
    }

    /* ��NV�е�CT HPLMN���浽�ڴ���,��Ҫ��ֹ����Խ�� */
    if ( pstNvimCfgDPlmnNPlmnFlagInfo->ucCTHplmnNum> NAS_MMC_MAX_CFG_HPLMN_NUM )
    {
        pstNvimCfgDPlmnNPlmnFlagInfo->ucCTHplmnNum = NAS_MMC_MAX_CFG_HPLMN_NUM;
    }

    for ( ulStep = 0; ulStep < pstNvimCfgDPlmnNPlmnFlagInfo->ucCTHplmnNum; ulStep++ )
    {
        PS_MEM_CPY(stNvimPlmn.aucSimPlmn,
            pstNvimCfgDPlmnNPlmnFlagInfo->aucCTHplmnList+ (ulStep * NAS_MML_SIM_PLMN_ID_LEN), NAS_MML_SIM_PLMN_ID_LEN);

        /* ת��PLMN IDΪMMC�ڲ��ĸ�ʽ���洢 */
        NAS_MMC_ConvertSimPlmnToNasPLMN(&stNvimPlmn, &stTempPlmn);

        if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&stTempPlmn))
        {
            pstDPlmnNPlmnCfgInfo->astCTHplmnList[pstDPlmnNPlmnCfgInfo->ucCTHplmnNum] = stTempPlmn;
            pstDPlmnNPlmnCfgInfo->ucCTHplmnNum++;
        }
    }
}



VOS_VOID  NAS_MMC_DelDuplicatedPlmnWithRatInPlmnList (
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    /* ɾ���ظ���PLMN */
    for (i = 0; i < NAS_MML_MIN(pstPlmnSelectionListInfo->usSearchPlmnNum, NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST); )
    {
        for (j = 0; j < pstPlmnSelectionListInfo->astPlmnSelectionList[i].ucRatNum; )
        {
            if (VOS_TRUE == NAS_MMC_IsPlmnWithRatInPlmnList(&(pstPlmnSelectionListInfo->astPlmnSelectionList[i].stPlmnId),
                                                            pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j].enRatType,
                                                            pstPlmnSelectionListInfo,
                                                            i))
            {
                /* ɾ����Ӧ��RAT */
                /*lint -e961*/
                (VOS_VOID)PS_MEM_MOVE(&(pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j]),
                            &(pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j + 1]),
                            ((pstPlmnSelectionListInfo->astPlmnSelectionList[i]).ucRatNum - j - 1) * sizeof(NAS_MMC_PLMN_RAT_INFO_STRU));
                /*lint +e961*/

                pstPlmnSelectionListInfo->astPlmnSelectionList[i].ucRatNum--;

            }
            else
            {
                j++;
            }
        }

        /* ���뼼������Ϊ0ʱ��ɾ����Ӧ��PLMN ID */
        if (0 == pstPlmnSelectionListInfo->astPlmnSelectionList[i].ucRatNum)
        {
            /*lint -e961*/
            (VOS_VOID)PS_MEM_MOVE(&(pstPlmnSelectionListInfo->astPlmnSelectionList[i]),
                        &(pstPlmnSelectionListInfo->astPlmnSelectionList[i + 1]),
                        (pstPlmnSelectionListInfo->usSearchPlmnNum - i - 1) * sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));
            /*lint +e961*/
            pstPlmnSelectionListInfo->usSearchPlmnNum--;
        }
        else
        {
            i++;
        }
    }
}
VOS_UINT32 NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId,
    VOS_UINT32                          ulEventType
)
{
    if ( ( NAS_MMC_FSM_PLMN_SELECTION == enFsmId )
      && ( ulEventType == NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ )))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}


VOS_UINT32 NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch(VOS_VOID)
{
    NAS_MML_LAI_STRU                                       *pstCurrentLai     = VOS_NULL_PTR;
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU               *pstForbRoamLaInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                                   *pstForbGprsPlmn   = VOS_NULL_PTR;
    NAS_MMC_FSM_EXTRA_CTX_UNION                            *punParentFsmCtx   = VOS_NULL_PTR;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enParentFsmId;
    VOS_UINT32                                              ulPlmnLaType;
    VOS_UINT32                                              ulRlst;

    ulPlmnLaType      = NAS_MML_PLMN_FORBID_NULL;
    pstCurrentLai     = NAS_MML_GetCurrCampLai();
    enParentFsmId     = NAS_MMC_GetParentFsmId();
    punParentFsmCtx   = NAS_MMC_GetParentFsmCtx();

    /* �����ǰ״̬����PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION == NAS_MMC_GetCurrFsmId())
    {
        pstForbRoamLaInfo = NAS_MMC_GetForbRoamLaInfo_PlmnSelection();
        pstForbGprsPlmn   = NAS_MMC_GetForbPlmnForGrpsInfo_PlmnSelection();
    }

    /* ��ǰ��״̬����ѡ��״̬�����ҵ�ǰ�ĸ�״̬�������������ݴ��ڣ���ȡ��״̬����ؽ�ֹ��Ϣ */
    else if ( (NAS_MMC_FSM_PLMN_SELECTION == enParentFsmId)
           && (VOS_NULL_PTR               != punParentFsmCtx) )
    {
        pstForbRoamLaInfo = &(punParentFsmCtx->stPlmnSelectionCtx.stForbRoamLaInfo);
        pstForbGprsPlmn   = &(punParentFsmCtx->stPlmnSelectionCtx.stForbGprsPlmn);
    }
    else
    {
        /* ��ǰ��״̬������ѡ��״̬�������ߵ�ǰ�ĸ�״̬��������������Ϊ�գ�ֱ���쳣���� */
        return ulPlmnLaType;
    }

    /* �Ƿ��� ForbLA��Ϣ�� */
    ulRlst =  NAS_MML_IsLaiInDestLaiList(pstCurrentLai,
                                        pstForbRoamLaInfo->ucForbRoamLaNum,
                                        pstForbRoamLaInfo->astForbRomLaList);

    if(VOS_TRUE == ulRlst)
    {
         ulPlmnLaType  |=   NAS_MML_PLMN_FORBID_ROAM_LA;
    }


    /* ��forbid plmn for gprs�б��� */
    ulRlst = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(NAS_MML_GetCurrCampPlmnId(),
                                                   1,
                                                   pstForbGprsPlmn);
    if(VOS_TRUE == ulRlst)
    {
        ulPlmnLaType  |=   NAS_MML_PLMN_FORBID_PLMN_FOR_GPRS;
    }

    return ulPlmnLaType;
}
VOS_UINT32 NAS_MMC_IsSpecTypePlmnIdInDestPlmnList (
    NAS_MML_PLMN_ID_STRU               *pstSpecPlmnId,
    NAS_MMC_PLMN_TYPE_ENUM_UINT8        enSpecPlmnType,
    VOS_UINT8                           ucPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstPlmnIdList
)
{
    /* ��ָ����PLMN����ΪH/U/O,��ʹ��Sim���͵�PLMN���жϵ�ǰPLMNID�Ƿ���
        �����б��� */
    if ( (NAS_MMC_PLMN_TYPE_HPLMN  == enSpecPlmnType)
      || (NAS_MMC_PLMN_TYPE_UPLMN  == enSpecPlmnType)
      || (NAS_MMC_PLMN_TYPE_OPLMN  == enSpecPlmnType) )
    {
        if ( VOS_TRUE == NAS_MML_IsSimPlmnIdInDestBcchPlmnList(pstSpecPlmnId,
                                                               ucPlmnNum,
                                                               pstPlmnIdList) )
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }

    /* ��ָ����PLMN���Ͳ�ΪH/U/O,��ʹ��BCCH���͵�PLMN���жϵ�ǰPLMNID�Ƿ���
        �����б��� */
    if ( VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstSpecPlmnId,
                                                           ucPlmnNum,
                                                           pstPlmnIdList) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}





VOS_VOID NAS_MMC_UpdateCsPsRestriction_WasInfo(
    RRMM_SYS_INFO_IND_STRU             *pstWrrSysInfo,
    NAS_MML_NETWORK_INFO_STRU          *pstNetWorkInfo
)
{
    /* ���õ�ǰ��Cs����ע��ı任��ʶ */
    pstNetWorkInfo->stCsDomainInfo.ulCsRegisterBarToUnBarFlag   = VOS_FALSE;
    /* ���õ�ǰ��Ps����ע��ı任��ʶ */
    pstNetWorkInfo->stPsDomainInfo.ulPsRegisterBarToUnBarFlag   = VOS_FALSE;

    if (VOS_FALSE == pstWrrSysInfo->stCsRestriction.enRestrictRegister)
    {
        if (VOS_TRUE == pstNetWorkInfo->stCsDomainInfo.stCsAcRestriction.ucRestrictRegister)
        {
            /* ���õ�ǰ��Cs����ע��ı任��ʶ */
            pstNetWorkInfo->stCsDomainInfo.ulCsRegisterBarToUnBarFlag   = VOS_TRUE;
        }
    }

    if (VOS_FALSE == pstWrrSysInfo->stPsRestriction.enRestrictRegister)
    {
        if (VOS_TRUE == pstNetWorkInfo->stPsDomainInfo.stPsAcRestriction.ucRestrictRegister)
        {
            /* ���õ�ǰ��Ps����ע��ı任��ʶ */
            pstNetWorkInfo->stPsDomainInfo.ulPsRegisterBarToUnBarFlag   = VOS_TRUE;
        }
    }

    /* ����CS����������Ϣ */
    NAS_MML_SetCsRestrictRegisterFlg(pstWrrSysInfo->stCsRestriction.enRestrictRegister);
    NAS_MML_SetCsRestrictPagingFlg(pstWrrSysInfo->stCsRestriction.enRestrictPagingRsp);
    NAS_MML_SetCsRestrictNormalServiceFlg(pstWrrSysInfo->stCsRestriction.enRestrictNormalService);
    NAS_MML_SetCsRestrictEmergencyServiceFlg(pstWrrSysInfo->stCsRestriction.enRestrictEmergencyService);


    /* ����PS����������Ϣ */
    NAS_MML_SetPsRestrictRegisterFlg(pstWrrSysInfo->stPsRestriction.enRestrictRegister);
    NAS_MML_SetPsRestrictPagingFlg(pstWrrSysInfo->stPsRestriction.enRestrictPagingRsp);
    NAS_MML_SetPsRestrictNormalServiceFlg(pstWrrSysInfo->stPsRestriction.enRestrictNormalService);
    NAS_MML_SetPsRestrictEmergencyServiceFlg(pstWrrSysInfo->stPsRestriction.enRestrictEmergencyService);

    return;
}







VOS_VOID NAS_MMC_UpdateCsPsRestriction_GasSysInfo(
    GRRMM_SYS_INFO_IND_ST              *pstGrrSysInfo,
    NAS_MML_NETWORK_INFO_STRU          *pstNetWorkInfo
)
{
    /* GSM���޷�������,ȫ�ֱ�����λ�� */
    pstNetWorkInfo->stCsDomainInfo.ulCsRegisterBarToUnBarFlag = VOS_FALSE;
    pstNetWorkInfo->stPsDomainInfo.ulPsRegisterBarToUnBarFlag = VOS_FALSE;

    /* ����CS/PS �Ƿ�����ע��ı�־ */
    switch (pstGrrSysInfo->unAcInfo.ucRestrictType)
    {
        case RRC_NAS_ACCESS_RESTRICTION_ALL_SERVICE:
            {
                /* ����CS����������Ϣ */
                NAS_MML_SetCsRestrictRegisterFlg(VOS_TRUE);
                NAS_MML_SetCsRestrictPagingFlg(VOS_TRUE);
                NAS_MML_SetCsRestrictNormalServiceFlg(VOS_TRUE);
                NAS_MML_SetCsRestrictEmergencyServiceFlg(VOS_TRUE);

                /* ����PS����������Ϣ */
                NAS_MML_SetPsRestrictRegisterFlg(VOS_TRUE);
                NAS_MML_SetPsRestrictPagingFlg(VOS_TRUE);
                NAS_MML_SetPsRestrictNormalServiceFlg(VOS_TRUE);
            }
            break;
        case RRC_NAS_ACCESS_NO_RESTRICTION:
            {
                if (VOS_TRUE == pstNetWorkInfo->stCsDomainInfo.stCsAcRestriction.ucRestrictRegister)
                {
                    /* ���õ�ǰ��Cs����ע��ı任��ʶ */
                    pstNetWorkInfo->stCsDomainInfo.ulCsRegisterBarToUnBarFlag   = VOS_TRUE;
                }


                if (VOS_TRUE == pstNetWorkInfo->stPsDomainInfo.stPsAcRestriction.ucRestrictRegister)
                {
                    /* ���õ�ǰ��Ps����ע��ı任��ʶ */
                    pstNetWorkInfo->stPsDomainInfo.ulPsRegisterBarToUnBarFlag   = VOS_TRUE;
                }

                /* ����CS����������Ϣ */
                NAS_MML_SetCsRestrictRegisterFlg(VOS_FALSE);
                NAS_MML_SetCsRestrictPagingFlg(VOS_FALSE);
                NAS_MML_SetCsRestrictNormalServiceFlg(VOS_FALSE);
                NAS_MML_SetCsRestrictEmergencyServiceFlg(VOS_FALSE);

                /* ����PS����������Ϣ */
                NAS_MML_SetPsRestrictRegisterFlg(VOS_FALSE);
                NAS_MML_SetPsRestrictPagingFlg(VOS_FALSE);
                NAS_MML_SetPsRestrictNormalServiceFlg(VOS_FALSE);
            }
            break;

        case RRC_NAS_ACCESS_RESTRICTION_NORMAL_SERVICE:
            {
                /* ����CS����������Ϣ */
                NAS_MML_SetCsRestrictRegisterFlg(VOS_TRUE);
                NAS_MML_SetCsRestrictPagingFlg(VOS_TRUE);
                NAS_MML_SetCsRestrictNormalServiceFlg(VOS_TRUE);
                NAS_MML_SetCsRestrictEmergencyServiceFlg(VOS_FALSE);

                /* ����PS����������Ϣ */
                NAS_MML_SetPsRestrictRegisterFlg(VOS_TRUE);
                NAS_MML_SetPsRestrictPagingFlg(VOS_TRUE);
                NAS_MML_SetPsRestrictNormalServiceFlg(VOS_TRUE);
            }
            break;

        case RRC_NAS_ACCESS_RESTRICTION_EMERGENCY_SERVICE:
            {
                /* ����CS����������Ϣ */
                NAS_MML_SetCsRestrictRegisterFlg(VOS_FALSE);
                NAS_MML_SetCsRestrictPagingFlg(VOS_FALSE);
                NAS_MML_SetCsRestrictNormalServiceFlg(VOS_FALSE);
                NAS_MML_SetCsRestrictEmergencyServiceFlg(VOS_TRUE);

                /* ����PS����������Ϣ */
                NAS_MML_SetPsRestrictRegisterFlg(VOS_FALSE);
                NAS_MML_SetPsRestrictPagingFlg(VOS_FALSE);
                NAS_MML_SetPsRestrictNormalServiceFlg(VOS_FALSE);
            }
            break;

        default:
            break;

    }

    /* PS�޽���ҵ�񣬸�ֵʼ�ղ����� */
    NAS_MML_SetPsRestrictEmergencyServiceFlg(VOS_FALSE);

    /* USIM����ֹGSM����ʱ��Ҳ��Ҫ����CS/PS �Ƿ�����ע��ı�־ */
    if (VOS_TRUE == NAS_MML_GetGsmForbidFlg())
    {
        /* ���õ�ǰ��Cs����ע��ı任��ʶ */
        pstNetWorkInfo->stCsDomainInfo.ulCsRegisterBarToUnBarFlag   = VOS_FALSE;

        /* ���õ�ǰ��Ps����ע��ı任��ʶ */
        pstNetWorkInfo->stPsDomainInfo.ulPsRegisterBarToUnBarFlag   = VOS_FALSE;

        /* ����CS����������Ϣ */
        NAS_MML_SetCsRestrictRegisterFlg(VOS_TRUE);
        NAS_MML_SetCsRestrictPagingFlg(VOS_TRUE);
        NAS_MML_SetCsRestrictNormalServiceFlg(VOS_TRUE);

        /* ����PS����������Ϣ */
        NAS_MML_SetPsRestrictRegisterFlg(VOS_TRUE);
        NAS_MML_SetPsRestrictPagingFlg(VOS_TRUE);
        NAS_MML_SetPsRestrictNormalServiceFlg(VOS_TRUE);
        NAS_MML_SetPsRestrictEmergencyServiceFlg(VOS_FALSE);

    }


    return;
}


VOS_VOID NAS_MMC_UpdateCsPsRestriction_AcChangeInd(
    RRMM_W_AC_INFO_CHANGE_IND_STRU     *pstWAcChangeInd,
    NAS_MML_NETWORK_INFO_STRU          *pstNetWorkInfo
)
{

    /* ���õ�ǰ��Cs����ע��ı任��ʶ */
    pstNetWorkInfo->stCsDomainInfo.ulCsRegisterBarToUnBarFlag   = VOS_FALSE;

    /* ���õ�ǰ��Ps����ע��ı任��ʶ */
    pstNetWorkInfo->stPsDomainInfo.ulPsRegisterBarToUnBarFlag   = VOS_FALSE;

    if (VOS_FALSE == pstWAcChangeInd->stCsRestriction.enRestrictRegister)
    {
        if (VOS_TRUE == pstNetWorkInfo->stCsDomainInfo.stCsAcRestriction.ucRestrictRegister)
        {
            /* ���õ�ǰ��Cs����ע��ı任��ʶ */
            pstNetWorkInfo->stCsDomainInfo.ulCsRegisterBarToUnBarFlag   = VOS_TRUE;
        }
    }

    if (VOS_FALSE == pstWAcChangeInd->stPsRestriction.enRestrictRegister)
    {
        if (VOS_TRUE == pstNetWorkInfo->stPsDomainInfo.stPsAcRestriction.ucRestrictRegister)
        {
            /* ���õ�ǰ��Ps����ע��ı任��ʶ */
            pstNetWorkInfo->stPsDomainInfo.ulPsRegisterBarToUnBarFlag   = VOS_TRUE;
        }
    }

    /* ����CS����������Ϣ */
    NAS_MML_SetCsRestrictRegisterFlg(pstWAcChangeInd->stCsRestriction.enRestrictRegister);
    NAS_MML_SetCsRestrictPagingFlg(pstWAcChangeInd->stCsRestriction.enRestrictPagingRsp);
    NAS_MML_SetCsRestrictNormalServiceFlg(pstWAcChangeInd->stCsRestriction.enRestrictNormalService);
    NAS_MML_SetCsRestrictEmergencyServiceFlg(pstWAcChangeInd->stCsRestriction.enRestrictEmergencyService);

    /* ����PS����������Ϣ */
    NAS_MML_SetPsRestrictRegisterFlg(pstWAcChangeInd->stPsRestriction.enRestrictRegister);
    NAS_MML_SetPsRestrictPagingFlg(pstWAcChangeInd->stPsRestriction.enRestrictPagingRsp);
    NAS_MML_SetPsRestrictNormalServiceFlg(pstWAcChangeInd->stPsRestriction.enRestrictNormalService);
    NAS_MML_SetPsRestrictEmergencyServiceFlg(pstWAcChangeInd->stPsRestriction.enRestrictEmergencyService);

    return;
}


VOS_VOID NAS_MMC_ConvertRrcRatToNasFormat(
    RRC_NAS_RAT_TYPE_ENUM_UINT32        ulRrcRat,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    *penRat
)
{
    switch (ulRrcRat)
    {
        case RRC_NAS_RAT_WCDMA_FDD:

            *penRat = NAS_MML_NET_RAT_TYPE_WCDMA;
            break;

        case RRC_NAS_RAT_GSM:

            *penRat = NAS_MML_NET_RAT_TYPE_GSM;
            break;

        case RRC_NAS_RAT_LTE:

            *penRat = NAS_MML_NET_RAT_TYPE_LTE;
            break;

        default:

            /* �쳣��ӡ */
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ConvertRrcRatToNasFormat,Unexpected Rrc rat!");
            *penRat = NAS_MML_NET_RAT_TYPE_BUTT;
            break;
    }

    return;
}
VOS_VOID NAS_MMC_ConvertNasRatToRrcFormat(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNasRat,
    RRC_NAS_RAT_TYPE_ENUM_UINT32       *penRrcRat
)
{
    switch (enNasRat)
    {
        case NAS_MML_NET_RAT_TYPE_GSM:
            *penRrcRat = RRC_NAS_RAT_GSM;
            break;

        case NAS_MML_NET_RAT_TYPE_WCDMA:
            *penRrcRat = RRC_NAS_RAT_WCDMA_FDD;
            break;

        case NAS_MML_NET_RAT_TYPE_LTE:
            *penRrcRat = RRC_NAS_RAT_LTE;
            break;

        default:

            /* �쳣��ӡ */
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ConvertRrcRatToNasFormat,Unexpected Nas rat!");

            *penRrcRat = RRC_NAS_RAT_TYPE_BUTT;

            break;
    }

    return;
}
VOS_VOID   NAS_MMC_ConvertRrcCoverTypeToNasFormat(
    RRC_NAS_COVERAGE_TYPE_ENUM_UINT32   enRrcCoverType,
    NAS_MMC_COVERAGE_TYPE_ENUM_UINT8   *penCoverType
)
{
    switch (enRrcCoverType)
    {
        case RRC_NAS_COVERAGE_TYPE_NONE:

            *penCoverType = NAS_MMC_COVERAGE_TYPE_NONE;
            break;

        case RRC_NAS_COVERAGE_TYPE_LOW:

            *penCoverType = NAS_MMC_COVERAGE_TYPE_LOW;
            break;

        case RRC_NAS_COVERAGE_TYPE_HIGH:

            *penCoverType = NAS_MMC_COVERAGE_TYPE_HIGH;
            break;

        default:

            /* �쳣��ӡ */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ConvertRrcCoverTypeToNasFormat,Unexpected Rrc coverage type!");
            *penCoverType = NAS_MMC_COVERAGE_TYPE_BUTT;
            break;
    }

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID   NAS_MMC_ConvertLmmCoverTypeToNasFormat(
    MMC_LMM_COVERAGE_TYPE_ENUM_UINT32   enLmmCoverType,
    NAS_MMC_COVERAGE_TYPE_ENUM_UINT8   *penCoverType
)
{
    switch (enLmmCoverType)
    {
        case MMC_LMM_COVERAGE_TYPE_NONE:

            *penCoverType = NAS_MMC_COVERAGE_TYPE_NONE;
            break;

        case MMC_LMM_COVERAGE_TYPE_LOW:

            *penCoverType = NAS_MMC_COVERAGE_TYPE_LOW;
            break;

        case MMC_LMM_COVERAGE_TYPE_HIGH:

            *penCoverType = NAS_MMC_COVERAGE_TYPE_HIGH;
            break;

        default:

            /* �쳣��ӡ */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ConvertLmmCoverTypeToNasFormat,Unexpected Rrc coverage type!");
            *penCoverType = NAS_MMC_COVERAGE_TYPE_BUTT;
            break;
    }

    return;
}
#endif



#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_MMC_ConvertLmmRatToRrcFormat(
    MMC_LMM_RAT_TYPE_ENUM_UINT8         ucLmmRat,
    RRC_NAS_RAT_TYPE_ENUM_UINT32       *penRat
)
{
    switch (ucLmmRat)
    {
        case MMC_LMM_RAT_WCDMA_FDD:
            *penRat = RRC_NAS_RAT_WCDMA_FDD;
            break;

        case MMC_LMM_RAT_GSM:
            *penRat = RRC_NAS_RAT_GSM;
            break;

        case MMC_LMM_RAT_LTE:
            *penRat = RRC_NAS_RAT_LTE;
            break;

        default:

            /* �쳣��ӡ */
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ConvertLmmRatToRrcFormat,Unexpected Rrc rat!");
            *penRat = RRC_NAS_RAT_TYPE_BUTT;
            break;
    }

    return;
}

#endif
NAS_MML_NET_MODE_ENUM_UINT8 NAS_MMC_ConvertGasNetModeToMmlNetMode(
    GRRMM_NW_OP_MODE_ENUM_UINT8         enGasNetMode
)
{
    NAS_MML_NET_MODE_ENUM_UINT8         enMmlNetMode;

    switch ( enGasNetMode )
    {
        case GRRMM_NW_OP_MODE_I:
            enMmlNetMode = NAS_MML_NET_MODE_I;
            break;

        case GRRMM_NW_OP_MODE_II:
            enMmlNetMode = NAS_MML_NET_MODE_II;
            break;

        case GRRMM_NW_OP_MODE_III:
            enMmlNetMode = NAS_MML_NET_MODE_III;
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ConvertGasNetModeToMmlNetMode, net mode invalid");
            enMmlNetMode = NAS_MML_NET_MODE_BUTT;
            break;
    }

    return enMmlNetMode;
}



VOS_UINT32 NAS_MMC_IsOptItemVaild_WasSysInfo(
    RRMM_SYS_INFO_IND_STRU             *pstWrrSysInfo
)
{
    if ((0 == pstWrrSysInfo->ucCnCommonSize)
     && (0 == pstWrrSysInfo->ucCsInfoSize)
     && (0 == pstWrrSysInfo->ucPsInfoSize)
     && (0 == pstWrrSysInfo->bitOpPlmnId)
     && (0 == pstWrrSysInfo->bitOpCsDrx)
     && (0 == pstWrrSysInfo->bitOpPsDrx))
    {
        return VOS_FALSE;
    }

    if ((RRC_NAS_MAX_SIZE_NAS_GSM_MAP < pstWrrSysInfo->ucCnCommonSize)
     || (RRC_NAS_MAX_SIZE_NAS_GSM_MAP < pstWrrSysInfo->ucCsInfoSize)
     || (RRC_NAS_MAX_SIZE_NAS_GSM_MAP < pstWrrSysInfo->ucPsInfoSize))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_IsNeedEnableUtran_AnyCellSearch (VOS_VOID)
{
    /* ������Anycell����״̬��ʱ���ҵ�ǰUtran��Disable�ˣ���Re-Enable Utran */

    if (NAS_MMC_FSM_ANYCELL_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        return VOS_FALSE;
    }

    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE != NAS_MML_GetUtranForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_IsNeedDisableUtran_RcvGasSysInfo (VOS_VOID)
{
    /* ���Utran�ڽ�ֹ���뼼���б����Ҵ�ʱUtranΪEnable״̬�����յ�Gas��ϵͳ��Ϣ��Disable Utran */
    if (VOS_FALSE == NAS_MML_IsRatInForbiddenList(NAS_MML_NET_RAT_TYPE_WCDMA))
    {
        return VOS_FALSE;
    }

    if (NAS_MML_RAT_CAPABILITY_STATUS_REENABLE != NAS_MML_GetUtranForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
VOS_VOID NAS_MMC_UpdateUtranCapabilityStatus_AnyCellSearch_Init (VOS_VOID)
{
    if (VOS_TRUE == NAS_MMC_IsNeedEnableUtran_AnyCellSearch())
    {
        NAS_MML_SetUtranForbiddenStatusFlg(NAS_MML_RAT_CAPABILITY_STATUS_REENABLE);
        NAS_MMC_SndAsRatCapabilityStatusChangeInfo();
    }
}


VOS_VOID NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus (VOS_VOID)
{

    if (VOS_TRUE == NAS_MMC_IsNeedDisableUtran_RcvGasSysInfo())
    {
        NAS_MML_SetUtranForbiddenStatusFlg(NAS_MML_RAT_CAPABILITY_STATUS_DISABLE);
        NAS_MMC_SndAsRatCapabilityStatusChangeInfo();
    }

}



VOS_VOID NAS_MMC_UpdateOperNameInfo(
    RRC_PLMN_ID_STRU                   *pstPlmnId
)
{
    NAS_MML_OPERATOR_NAME_INFO_STRU    *pstOperNameInfo = VOS_NULL_PTR;

    /* ���µ�ǰפ��������Ϣ */
    pstOperNameInfo = NAS_MML_GetOperatorNameInfo();

    /* �������ĳ����������뵱ǰפ����PLMN ID��ͬ�����ȫ�ֱ��� */
    if ((pstOperNameInfo->stOperatorPlmnId.ulMcc != pstPlmnId->ulMcc)
     || (pstOperNameInfo->stOperatorPlmnId.ulMnc != pstPlmnId->ulMnc))
    {
        /* ���aucOperatorNameShort��aucOperatorNameLong */
        PS_MEM_SET(pstOperNameInfo, 0x00, sizeof(NAS_MML_OPERATOR_NAME_INFO_STRU));
        pstOperNameInfo->stOperatorPlmnId.ulMcc = pstPlmnId->ulMcc;
        pstOperNameInfo->stOperatorPlmnId.ulMnc = pstPlmnId->ulMnc;
    }

    return;
}
VOS_VOID NAS_MMC_UpdateNetworkInfo_GasSysInfo(
    struct MsgCB                       *pstMsg
)
{
    GRRMM_SYS_INFO_IND_ST              *pstGrrSysInfo       = VOS_NULL_PTR;
    NAS_MML_NETWORK_3GPP_REL_STRU      *pst3GPPRelVersion   = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCurrCampPlmnInfo = VOS_NULL_PTR;
    NAS_MML_MS_BAND_INFO_STRU          *pstBandInfo         = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                   *pstOldCampLai       = VOS_NULL_PTR;


    NAS_MML_NETWORK_INFO_STRU          *pstNetWorkInfo      = VOS_NULL_PTR;

    pstNetWorkInfo  =  NAS_MML_GetNetworkInfo();

    pstGrrSysInfo     = (GRRMM_SYS_INFO_IND_ST *)pstMsg;
    pst3GPPRelVersion = NAS_MML_GetNetwork3GppRel();

    pst3GPPRelVersion->enNetSgsnRel = pstGrrSysInfo->ucSgsnRelease;
    pst3GPPRelVersion->enNetMscRel  = pstGrrSysInfo->ucMsrRelease;

    pstCurrCampPlmnInfo = NAS_MML_GetCurrCampPlmnInfo();

    pstOldCampLai       = NAS_MML_GetOldCampLai();

    /* �����ϴ�פ����LAI��Ϣ,Ȼ�����沽����µ�ǰפ��LAI��Ϣ */
    if (VOS_FALSE == NAS_MMC_IsInValidCampPlmn())
    {
        PS_MEM_CPY(pstOldCampLai, &(pstCurrCampPlmnInfo->stLai), sizeof(NAS_MML_LAI_STRU));
    }

    /* ��ǰucGprsSupportIndΪGsmʱ������ǰ��֧��GPRS���޷���PS����Ϣ�л�ȡ����ģʽ */
    if (NAS_MML_GAS_SUBMODE_GSM == pstGrrSysInfo->ucGprsSupportInd)
    {
        /* ���õ�ǰ����ģʽΪ��ЧNAS_MML_NET_MODE_BUTT */
        pstCurrCampPlmnInfo->enNetworkMode = NAS_MML_NET_MODE_BUTT;

        pstCurrCampPlmnInfo->ucRac = NAS_MML_RAC_INVALID;
    }
    else
    {
        /* ��������ģʽ ��ֻ����PS����Ϣ��Ч������£�����ģʽ����Ч */
        if (GRRMM_NW_OP_MODE_INVALID != pstGrrSysInfo->ucNetworkOperationMode)
        {
            pstCurrCampPlmnInfo->enNetworkMode =
                NAS_MMC_ConvertGasNetModeToMmlNetMode(pstGrrSysInfo->ucNetworkOperationMode);
        }

        pstCurrCampPlmnInfo->ucRac                = pstGrrSysInfo->ucRac;
    }

    /* ����GAS�ϱ���GPRS֧��ָʾ��ת��Ϊ��Ӧ��ϵͳ��ģʽ */
    pstCurrCampPlmnInfo->enSysSubMode = NAS_MML_ConvertGprsSupportIndToSysSubMode(pstGrrSysInfo->ucGprsSupportInd);

    /* ������·����Ӫ��������Ϣ */
    NAS_MMC_UpdateOperNameInfo(&(pstGrrSysInfo->PlmnId));

    /* ���µ�ǰפ��������Ϣ */
    pstCurrCampPlmnInfo->stLai.stPlmnId.ulMcc = pstGrrSysInfo->PlmnId.ulMcc;
    pstCurrCampPlmnInfo->stLai.stPlmnId.ulMnc = pstGrrSysInfo->PlmnId.ulMnc;

    pstCurrCampPlmnInfo->stLai.enCampPlmnNetRat = NAS_MML_NET_RAT_TYPE_GSM;

    /* ���µ�ǰפ�������LAC��RAC��Ϣ */
    pstCurrCampPlmnInfo->stLai.aucLac[0]      = (VOS_UINT8)((pstGrrSysInfo->usLac & 0xFF00) >> 8);
    pstCurrCampPlmnInfo->stLai.aucLac[1]      = (VOS_UINT8)(pstGrrSysInfo->usLac & 0x00FF);


    /* ��С���л�ȡGPRS֧����Ϣ */
    pstNetWorkInfo->stPsDomainInfo.ucPsSupportFlg = pstGrrSysInfo->ucGprsSupportInd;

    /* ����cell Info */
    pstCurrCampPlmnInfo->stCampCellInfo.ucCellNum = 1;
    pstCurrCampPlmnInfo->stCampCellInfo.astCellInfo[0].ulCellId = pstGrrSysInfo->usCellId;

    NAS_MML_SetCurrCampArfcn(0x0);

    /* ���µ�ǰ��ϵͳGsmBand��Ϣ��W,L פ�� BandΪ0 */
    pstBandInfo = NAS_MML_GetCurrBandInfo();
    pstBandInfo->unWcdmaBand.ulBand      = 0;
    pstBandInfo->unGsmBand.ulBand        = pstGrrSysInfo->unGsmBand.ulBand;
#if (FEATURE_ON == FEATURE_LTE)
    pstBandInfo->stLteBand.aulLteBand[0] = 0;
    pstBandInfo->stLteBand.aulLteBand[1] = 0;
#endif

    /* ���µ�ǰ����� CS/PS��ķ������������ */
    NAS_MMC_UpdateCsPsRestriction_GasSysInfo(pstGrrSysInfo, NAS_MML_GetNetworkInfo());
    OM_DelDrxTimerWakeSrc(VOS_GetModemIDFromPid(WUEPS_PID_MMC));
    NAS_MMC_SndDrxTimerInfo(VOS_FALSE);
    return;
}
VOS_VOID NAS_MMC_UpdateNetworkInfo_WasSysInfo(
    struct MsgCB                       *pstMsg
)
{
    RRMM_SYS_INFO_IND_STRU             *pstWrrSysInfo   = VOS_NULL_PTR;
    NAS_MML_NETWORK_INFO_STRU          *pstNetWorkInfo  = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                   *pstOldCampLai   = VOS_NULL_PTR;

    pstWrrSysInfo = (RRMM_SYS_INFO_IND_STRU*)pstMsg;

    if (VOS_FALSE == NAS_MMC_IsOptItemVaild_WasSysInfo(pstWrrSysInfo))
    {
        return;
    }

    pstNetWorkInfo  =  NAS_MML_GetNetworkInfo();

    pstOldCampLai       = NAS_MML_GetOldCampLai();

    /* �����ϴ�פ����LAI��Ϣ,Ȼ�����沽����µ�ǰפ��LAI��Ϣ */
    if (VOS_FALSE == NAS_MMC_IsInValidCampPlmn())
    {
        PS_MEM_CPY(pstOldCampLai, &(pstNetWorkInfo->stCampPlmnInfo.stLai), sizeof(NAS_MML_LAI_STRU));
    }

    if (VOS_TRUE == pstWrrSysInfo->bitOpPlmnId)
    {
        /* ������·����Ӫ��������Ϣ */
        NAS_MMC_UpdateOperNameInfo(&(pstWrrSysInfo->PlmnId));

        /* ���µ�ǰפ���������Ϣ */
        pstNetWorkInfo->stCampPlmnInfo.stLai.stPlmnId.ulMcc   = pstWrrSysInfo->PlmnId.ulMcc;
        pstNetWorkInfo->stCampPlmnInfo.stLai.stPlmnId.ulMnc   = pstWrrSysInfo->PlmnId.ulMnc;

        pstNetWorkInfo->stCampPlmnInfo.stLai.enCampPlmnNetRat = NAS_MML_NET_RAT_TYPE_WCDMA;
    }

    /* ��ȡ LAC, aucCnCommonInfo[0]����Lac, aucCnCommonInfo[1]���� Lac Continued Byte*/
    if (0 != pstWrrSysInfo->ucCnCommonSize)
    {
        pstNetWorkInfo->stCampPlmnInfo.stLai.aucLac[0] = pstWrrSysInfo->aucCnCommonInfo[0];
        pstNetWorkInfo->stCampPlmnInfo.stLai.aucLac[1] = pstWrrSysInfo->aucCnCommonInfo[1];
    }

    /* ���� rac��Ϣ��PS��֧����Ϣ */
    if (0 == pstWrrSysInfo->ucPsInfoSize)
    {
        if (RRC_NAS_SYS_INFO_TYPE_SYS == pstWrrSysInfo->enSysInfoType)
        {
            pstNetWorkInfo->stPsDomainInfo.ucPsSupportFlg = VOS_FALSE;

            pstNetWorkInfo->stCampPlmnInfo.ucRac = NAS_MML_RAC_INVALID;
        }
    }
    else
    {
        pstNetWorkInfo->stPsDomainInfo.ucPsSupportFlg = VOS_TRUE;
        pstNetWorkInfo->stCampPlmnInfo.ucRac = pstWrrSysInfo->aucPsInfo[0];
    }

    if (VOS_TRUE == pstWrrSysInfo->bitOpCellId)
    {
        /* ����С��ID */
        pstNetWorkInfo->stCampPlmnInfo.stCampCellInfo.astCellInfo[0].ulCellId = pstWrrSysInfo->ulCellId;
        pstNetWorkInfo->stCampPlmnInfo.stCampCellInfo.ucCellNum               = 1;
    }

    /* ��������ģʽ :aucPsInfo[1]��Bit1ָʾ����ģʽ */
    if ( 0 == (pstWrrSysInfo->aucPsInfo[1] & NAS_MML_NET_MODE_BIT_MASK_WAS_SYS_INFO) )
    {
        /* ����Ϊ����ģʽI ,NAS_MML_NET_MODE_I */
        pstNetWorkInfo->stCampPlmnInfo.enNetworkMode = NAS_MML_NET_MODE_I;
    }
    else
    {
        /* ����Ϊ����ģʽII ,NAS_MML_NET_MODE_II */
        pstNetWorkInfo->stCampPlmnInfo.enNetworkMode = NAS_MML_NET_MODE_II;
    }

    /* ����Sysinfo����ģʽ */
    pstNetWorkInfo->stCampPlmnInfo.enSysSubMode = pstWrrSysInfo->enSysSubMode;

    NAS_MML_SetCurrCampArfcn(0x0);

    /* ���µ�ǰ�� W Band ϵͳ��Ϣ��G��Lפ�� BandΪ0 */
    pstNetWorkInfo->stBandInfo.unWcdmaBand.ulBand      = pstWrrSysInfo->unWcdmaBand.ulBand;
    pstNetWorkInfo->stBandInfo.unGsmBand.ulBand        = 0;
#if (FEATURE_ON == FEATURE_LTE)
    pstNetWorkInfo->stBandInfo.stLteBand.aulLteBand[0] = 0;
    pstNetWorkInfo->stBandInfo.stLteBand.aulLteBand[1] = 0;
#endif

    /* ����CsPS ���Ƿ�����ע��ı�־��unBar��־λ */

    NAS_MMC_UpdateCsPsRestriction_WasInfo(pstWrrSysInfo, pstNetWorkInfo);

    OM_DelDrxTimerWakeSrc(VOS_GetModemIDFromPid(WUEPS_PID_MMC));
    NAS_MMC_SndDrxTimerInfo(VOS_FALSE);
    return;
}


#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID NAS_MMC_UpdateSuitPlmnList_LmmSysInfo(
    MMC_LMM_SYS_INFO_STRU              *pstLteSysInfo
)
{
    NAS_MML_PLMN_ID_STRU                stPlmnId;
    MMC_LMM_PLMN_ID_STRU               *pstLmmPlmnId = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucSuitTotalPlmnNum;
    NAS_MML_SUIT_PLMN_LIST_STRU        *pstSuitPlmnList = VOS_NULL_PTR;

    pstSuitPlmnList    = NAS_MML_GetSuitPlmnList();
    ucSuitTotalPlmnNum = (VOS_UINT8)pstLteSysInfo->stSpecPlmnIdList.ulSuitPlmnNum;

    if (ucSuitTotalPlmnNum > MMC_LMM_MAX_SRCH_PLMN_NUM)
    {
        ucSuitTotalPlmnNum = MMC_LMM_MAX_SRCH_PLMN_NUM;
    }

    for (ucIndex = 0; ucIndex < ucSuitTotalPlmnNum; ucIndex++)
    {
        pstLmmPlmnId = &(pstLteSysInfo->stSpecPlmnIdList.astSuitPlmnList[ucIndex]);

        /* ���湲��������Ϣ��������ǰפ������ */
        NAS_MMC_ConvertLmmPlmnToGUNasFormat(pstLmmPlmnId, &stPlmnId);

        PS_MEM_CPY(&pstSuitPlmnList->astSuitPlmnList[ucIndex], &stPlmnId, sizeof(pstSuitPlmnList->astSuitPlmnList[ucIndex]));
    }

    pstSuitPlmnList->ucSuitPlmnNum = ucSuitTotalPlmnNum;

    return;
}



VOS_VOID NAS_MMC_UpdateNetworkInfo_LmmSysInfo(
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SYS_INFO_IND_STRU          *pstLmmSysInfoMsg    = VOS_NULL_PTR;
    MMC_LMM_PLMN_ID_STRU               *pstLmmPlmnId        = VOS_NULL_PTR;
    NAS_MML_MS_BAND_INFO_STRU          *pstBandInfo         = VOS_NULL_PTR;
    NAS_MML_CAMP_CELL_INFO_STRU        *pstCampCell         = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstCurrPlmnId       = VOS_NULL_PTR;
    NAS_MML_OPERATOR_NAME_INFO_STRU    *pstOperNameInfo     = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCurCampInfo      = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stPlmnId;


    pstLmmSysInfoMsg  = (LMM_MMC_SYS_INFO_IND_STRU*)pstMsg;

    pstLmmPlmnId = &(pstLmmSysInfoMsg->stLteSysInfo.stSpecPlmnIdList.astSuitPlmnList[0]);

    /* ����PLMN ID��Ϣ����ǰ����Ϣ�� */
    NAS_MMC_ConvertLmmPlmnToGUNasFormat(pstLmmPlmnId, &stPlmnId);

    pstCurCampInfo                       = NAS_MML_GetCurrCampPlmnInfo();
    NAS_MML_InitRssiValue(&(pstCurCampInfo->stCampCellInfo));

    /* ��L�º��������������Ϣ */
    NAS_MML_ClearCsPsRestrictionAll();

    /* ����פ����Ϣ */
    pstOperNameInfo = NAS_MML_GetOperatorNameInfo();
    pstCurrPlmnId   = NAS_MML_GetCurrCampPlmnId();

    /* �������ĳ����������뵱ǰפ����PLMN ID��ͬ�����ȫ�ֱ��� */
    if ((pstCurrPlmnId->ulMcc != stPlmnId.ulMcc)
     || (pstCurrPlmnId->ulMnc != stPlmnId.ulMnc))
    {
        /* ���aucOperatorNameShort��aucOperatorNameLong */
        PS_MEM_SET(pstOperNameInfo, 0x00, sizeof(NAS_MML_OPERATOR_NAME_INFO_STRU));
        pstOperNameInfo->stOperatorPlmnId.ulMcc = stPlmnId.ulMcc;
        pstOperNameInfo->stOperatorPlmnId.ulMnc = stPlmnId.ulMnc;
        pstCurrPlmnId->ulMcc                    = stPlmnId.ulMcc;
        pstCurrPlmnId->ulMnc                    = stPlmnId.ulMnc;
    }

    /* ����cell Info */
    pstCampCell     = NAS_MML_GetCampCellInfo();

    /* ����С��ID */
    pstCampCell->ucCellNum               = 1;
    pstCampCell->astCellInfo[0].ulCellId = pstLmmSysInfoMsg->stLteSysInfo.ulCellId;

    NAS_MML_SetCurrCampArfcn(pstLmmSysInfoMsg->stLteSysInfo.ulArfcn);

    /* ���µ�ǰ��ϵͳGsmBand��Ϣ��W,L פ�� BandΪ0 */
    pstBandInfo = NAS_MML_GetCurrBandInfo();
    pstBandInfo->unWcdmaBand.ulBand      = 0;
    pstBandInfo->unGsmBand.ulBand        = 0;
    pstBandInfo->stLteBand.aulLteBand[0] = pstLmmSysInfoMsg->stLteSysInfo.stLteBand.aulLteBand[0];
    pstBandInfo->stLteBand.aulLteBand[1] = pstLmmSysInfoMsg->stLteSysInfo.stLteBand.aulLteBand[1];

    /* ��ȡ��ǰפ����������Ϣ */
    pstCurCampInfo->enNetworkMode        = NAS_MML_NET_MODE_INVALID;

    pstCurCampInfo->enSysSubMode         = NAS_MML_RRC_SYS_SUBMODE_LTE;

    pstCurCampInfo->stLai.aucLac[0]      = pstLmmSysInfoMsg->stLteSysInfo.stTac.ucTac;
    pstCurCampInfo->stLai.aucLac[1]      = pstLmmSysInfoMsg->stLteSysInfo.stTac.ucTacCnt;
    pstCurCampInfo->ucRac                = NAS_MML_RAC_INVALID;

    pstCurCampInfo->enLmmAccessType      = pstLmmSysInfoMsg->stLteSysInfo.enAccessType;


    pstCurCampInfo->stLai.enCampPlmnNetRat = NAS_MML_NET_RAT_TYPE_LTE;

    OM_DelDrxTimerWakeSrc(VOS_GetModemIDFromPid(WUEPS_PID_MMC));
    NAS_MMC_SndDrxTimerInfo(VOS_FALSE);

    NAS_MMC_UpdateSuitPlmnList_LmmSysInfo(&pstLmmSysInfoMsg->stLteSysInfo);

    return;
}
#endif


VOS_VOID NAS_MMC_GetDomainRegStatusInRegInfoList(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurNetRatType,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 *penCsCause,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 *penPsCause
)
{
    NAS_MMC_PLMN_REG_REJ_CTX_STRU      *pstPlmnRegRejInfo = VOS_NULL_PTR;
    NAS_MMC_PLMN_REG_INFO_STRU         *pstPlmnRegList    = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;

    pstPlmnRegRejInfo = NAS_MMC_GetPlmnRegRejInfo();

    /* ��ȡע��ԭ���б��ָ�� */
    pstPlmnRegList = pstPlmnRegRejInfo->astPlmnRegInfoList;

    /* �жϵ�ǰ�����Ƿ�����ע���б��� */
    ulIndex = NAS_MMC_GetPlmnIndexInRegInfoList(pstPlmnId,
                            pstPlmnRegRejInfo->ucPlmnRegInfoNum, pstPlmnRegList);

    /* ��ǰ������ע���б��У�ȡ�ö�Ӧ���뼼����CS/PS���ע���� */
    if ((ulIndex < pstPlmnRegRejInfo->ucPlmnRegInfoNum)
     && (ulIndex < NAS_MMC_MAX_REG_PLMN_INFO_NUM))
    {
        switch ( enCurNetRatType )
        {

        #if (FEATURE_ON == FEATURE_LTE)

            case NAS_MML_NET_RAT_TYPE_LTE :
                *penCsCause = pstPlmnRegRejInfo->astPlmnRegInfoList[ulIndex].enLCsRegStatus;
                *penPsCause = pstPlmnRegRejInfo->astPlmnRegInfoList[ulIndex].enLPsRegStatus;
                return;
        #endif

            case NAS_MML_NET_RAT_TYPE_WCDMA:
                *penCsCause = pstPlmnRegRejInfo->astPlmnRegInfoList[ulIndex].enWCsRegStatus;
                *penPsCause = pstPlmnRegRejInfo->astPlmnRegInfoList[ulIndex].enWPsRegStatus;
                return;

            case NAS_MML_NET_RAT_TYPE_GSM :
                *penCsCause = pstPlmnRegRejInfo->astPlmnRegInfoList[ulIndex].enGCsRegStatus;
                *penPsCause = pstPlmnRegRejInfo->astPlmnRegInfoList[ulIndex].enGPsRegStatus;
                return;

            default:
                NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetDomainResultInfoInRegInfoList: NETRAT TYPE INVALID ");
                return;
        }
    }

    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetDomainResultInfoInRegInfoList: can't find the plmn id ");

    return;

}
VOS_UINT32  NAS_MMC_IsPlmnRegInfoAllSucc(
    NAS_MMC_PLMN_REG_INFO_STRU         *pstPlmnRegList
)
{
	/* G��CS���Ƿ�ע��ʧ�ܹ�����ʧ�ܣ��򷵻�VOS_FASLE */
	if ( NAS_MML_REG_FAIL_CAUSE_NULL != pstPlmnRegList->enGCsRegStatus )
	{
	    return VOS_FALSE;
	}

	/* G��PS���Ƿ�ע��ʧ�ܹ�����ʧ�ܣ��򷵻�VOS_FASLE */
	if ( NAS_MML_REG_FAIL_CAUSE_NULL != pstPlmnRegList->enGPsRegStatus )
	{
	    return VOS_FALSE;
	}

	/* W��CS���Ƿ�ע��ʧ�ܹ�����ʧ�ܣ��򷵻�VOS_FASLE */

	if ( NAS_MML_REG_FAIL_CAUSE_NULL != pstPlmnRegList->enWCsRegStatus )
	{
	    return VOS_FALSE;
	}
	/* W��PS���Ƿ�ע��ʧ�ܹ�����ʧ�ܣ��򷵻�VOS_FASLE */
	if ( NAS_MML_REG_FAIL_CAUSE_NULL != pstPlmnRegList->enWPsRegStatus )
	{
	    return VOS_FALSE;
	}

#if (FEATURE_ON == FEATURE_LTE)

	/* L��CS���Ƿ�ע��ʧ�ܹ�����ʧ�ܣ��򷵻�VOS_FASLE */
	if ( NAS_MML_REG_FAIL_CAUSE_NULL != pstPlmnRegList->enLCsRegStatus )
	{
	    return VOS_FALSE;
	}

	/* L��PS���Ƿ�ע��ʧ�ܹ�����ʧ�ܣ��򷵻�VOS_FASLEs */
	if ( NAS_MML_REG_FAIL_CAUSE_NULL != pstPlmnRegList->enLPsRegStatus )
	{
	    return VOS_FALSE;
	}
#endif

	/* ������ΪNAS_MML_REG_FAIL_CAUSE_NULL,����Ϊ������ע��ɹ� */
	return VOS_TRUE;

}
VOS_VOID NAS_MMC_NotifyModeChange(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8             enRatType,
    VOS_UINT8                                   ucSimPsRegStatus
)
{
    NAS_MMC_SRV_STA_CHNG_INFO_STRU             *pstLastSrvStaInfo;

    pstLastSrvStaInfo = NAS_MMC_GetSrvStaChngInfo();

    /* ����ģʽ�����仯ʱ��֪ͨAPS��CDS������Ϊ��Чʱ��֪ͨAPS��CDS */
    if ( ( enRatType != pstLastSrvStaInfo->enRatType )
      || ( ( ucSimPsRegStatus != pstLastSrvStaInfo->ucSimPsRegStatus )
        && ( VOS_FALSE == ucSimPsRegStatus )) )
    {
        NAS_MMC_SndApsServiceStatusInd(enRatType, ucSimPsRegStatus);
        NAS_MMC_SndCdsModeChangeInd(enRatType);

        pstLastSrvStaInfo->enRatType          = enRatType;
        pstLastSrvStaInfo->ucSimPsRegStatus   = ucSimPsRegStatus;
    }

    return;
}


VOS_UINT32 NAS_MMC_IsPlmnAllowedInManualMode(
    NAS_MML_PLMN_ID_STRU                                   *pstPlmnId
)
{
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstUserSpecPlmnId = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEplmnInfo      = VOS_NULL_PTR;
    VOS_UINT32                                              ulRlst;
    VOS_UINT32                                              ulEplmnValidFlg;

    pstUserSpecPlmnId = NAS_MMC_GetUserSpecPlmnId();
    pstEplmnInfo      = NAS_MML_GetEquPlmnList();

    /* �ֶ�ѡ��ģʽ��LTE���������û�ָ����������ͬ */
    if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstPlmnId, &(pstUserSpecPlmnId->stPlmnId)))
    {
        return VOS_TRUE;
    }

    /* �ж��ֶ�ѡ��ģʽ��LTE�������ǲ����û�ָ���������EPLMN */
    ulRlst = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstPlmnId,
                                            pstEplmnInfo->ucEquPlmnNum,
                                            pstEplmnInfo->astEquPlmnAddr);

    ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

    /* �ֶ�ѡ��ģʽʱ���û�ָ����������ע�ᣬ��LTE���������û�ָ���������EPLMN*/
    if ((VOS_TRUE == NAS_MMC_GetUserSpecPlmnRegisterStatus())
     && (VOS_TRUE == ulRlst)
     && (VOS_TRUE == ulEplmnValidFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_LTE)

VOS_UINT32 NAS_MMC_IsNeedDisableLte_SysCfg(
    NAS_MMCMMC_SysCfg_RSLT_STRU        *pstSyscfgRsltMsg
)
{
    VOS_UINT8                                               ucSimPsRegStatus;
    VOS_UINT8                                               ucSimCsRegStatus;
    VOS_UINT32                                              ulRatForbiddenFlg;

    ulRatForbiddenFlg   = NAS_MML_IsRatInForbiddenList(NAS_MML_NET_RAT_TYPE_LTE);

    /* ����Э�����������������������£���Ҫdisable LTE��
    (1)SYSCFG���õ�ǰ���뼼��ΪLW,LG,LWG
    (2)PS����Ч����PS������attach��SIM��
    (3)CS����Ч��CS����ע�� */

    ucSimPsRegStatus    = NAS_MML_GetSimPsRegStatus();
    ucSimCsRegStatus    = NAS_MML_GetSimCsRegStatus();

    /* ��������ʱ����Ҫdisable LTE */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus() )
    {
        return VOS_FALSE;
    }

    /* ƽ̨��֧��LTEʱ����Ҫdisable LTE */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        return VOS_FALSE;
    }

    /* ����Ѿ�disable ����Ҫ��disable LTE */
    if (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
    {
        return VOS_FALSE;
    }

    /* LTE ONLY���������ֹLTE�����������Ҫ��ֹ */
    if ((VOS_FALSE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
     && (VOS_TRUE == ulRatForbiddenFlg))
    {
        return VOS_TRUE;
    }

    /* ��L��ģ��ΪSIM����ֱ��disable Lģ */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {
        return VOS_TRUE;
    }

    /* CS������ע���CS����Ч */
    if ((VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
     || (VOS_FALSE == ucSimCsRegStatus))
    {
        return VOS_FALSE;
    }

    /* PS����Ч������PS����attach */

    if (((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
       || (VOS_TRUE == pstSyscfgRsltMsg->ulIsNeedAttachPs))
     && (VOS_TRUE == ucSimPsRegStatus))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_IsNeedEnableLte_SysCfg(
    NAS_MMCMMC_SysCfg_RSLT_STRU        *pstSyscfgRsltMsg
)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;

    /* ����������������MMC��Ҫ����enable LTE��
    (1)����disable LTE�ı��Ϊ��
    (2)����ģʽ����֧��LTE ONLY */

    /* ��ȡLTE��ʹ��״̬ */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    /* ���֮ǰδdisable LTE,Ҳ����Ҫenable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* ��ǰ����ģʽΪL only,��Ҫenable LTE */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_TRUE;
    }


    /* �ж�ATTACH PS�Ƿ���Ҫ����ENABLE LTE */
    if ((VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
     && (VOS_TRUE == pstSyscfgRsltMsg->ulIsNeedAttachPs))
    {
        if (VOS_TRUE == NAS_MMC_IsNeedEnableLte_AttachPs())
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MMC_IsNeedDisableLte_ModeChange(VOS_VOID)
{
    VOS_UINT8                                               ucSimPsRegStatus;
    VOS_UINT8                                               ucSimCsRegStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    /* ����Э�����������������������£���Ҫdisable LTE��
    (1)��ǰ���뼼��ΪLW,LG,LWG
    (2)PS����Ч��SIM��
    (3)CS+PS */

    ucSimPsRegStatus    = NAS_MML_GetSimPsRegStatus();
    ucSimCsRegStatus    = NAS_MML_GetSimCsRegStatus();
    enSimType           = NAS_MML_GetSimType();

    /* ��������ʱ����Ҫdisable LTE */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus() )
    {
        return VOS_FALSE;
    }

    /* ƽ̨��֧��LTEʱ����Ҫdisable LTE */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        return VOS_FALSE;
    }

    /* ����Ѿ�disable ����Ҫ��disable LTE */
    if (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
    {
        return VOS_FALSE;
    }

    /* LTE��ģ,����disable */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    if (NAS_MML_SIM_TYPE_SIM == enSimType)
    {
        return VOS_TRUE;
    }

    /* CS����Ч */
    if (VOS_FALSE == ucSimCsRegStatus)
    {
        return VOS_FALSE;
    }

    /* MSģʽ��CS+PS */
    if (NAS_MML_MS_MODE_PS_CS != NAS_MML_GetMsMode())
    {
        return VOS_FALSE;
    }

    /* PS����Ч */
    if (VOS_TRUE == ucSimPsRegStatus)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_IsNeedEnableLte_ModeChange(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
    VOS_UINT8                                               ucCsAllowAttachFlg;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    /* ����������������MMC��Ҫ����enable LTE��
    (1)����disable LTE�ı��Ϊ��
    (2)MSģʽ����֧��PS ONLY��CS������ע��
    (3)PS����Ч����USIM�� */

    /* ��ȡLTE��ʹ��״̬ */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
    ucCsAllowAttachFlg     = NAS_MML_GetCsAttachAllowFlg();
    enSimType              = NAS_MML_GetSimType();

    /* �������ʱ�Ѿ�����en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config�����ý�ֹ��LTE���򷵻�VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }

    /* ���֮ǰδdisable LTE,Ҳ����Ҫenable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* SIM�������Ҳ�ΪL��ģ����Ҫenable LTE */
    if ((VOS_TRUE               != NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
     && (NAS_MML_SIM_TYPE_SIM   == enSimType))
    {
        return VOS_FALSE;
    }

    /* PS����Ч */
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return VOS_FALSE;
    }


    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
    {
        return VOS_FALSE;
    }

    /* ��ǰMSģʽΪPS only,��Ҫenable LTE */
    if ((NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
     && (VOS_FALSE == ucCsAllowAttachFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MMC_IsNeedDisableLte_DetachPs(VOS_VOID)
{
    NAS_MMC_DETACH_REQ_CTX_STRU                            *pstDetachReqCtx = VOS_NULL_PTR;
    VOS_UINT8                                               ucSimCsRegStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    /* ����Э��3GPP 24.301����,5.5.2.2.2 UE initiated detach procedure completion for EPS services only
    The UE in CS/PS mode 1 or CS/PS mode 2 of operation shall set the update status
    to U2 NOT UPDATED, disable E UTRAN and select GERAN or UTRAN access technology
    and enter the EMM-NULL state.

    ��ʵ����⿴�����������������£���Ҫdisable LTE��
    (1)��ǰ���뼼��ΪLW,LG,LWG
    (2)PS��������ע���SIM��
    (3)CS����Ч��CS����ע�� */

    ucSimCsRegStatus    = NAS_MML_GetSimCsRegStatus();
    enSimType           = NAS_MML_GetSimType();

    /* ��������ʱ����Ҫdisable LTE */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus() )
    {
        return VOS_FALSE;
    }

    /* ƽ̨��֧��LTEʱ����Ҫdisable LTE */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        return VOS_FALSE;
    }

    /* ����Ѿ�disable ����Ҫ��disable LTE */
    if (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
    {
        return VOS_FALSE;
    }

    /* disable ��enable lte�����ж�syscfg�Ƿ�֧��L */

    /* LTE��ģ */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    if (NAS_MML_SIM_TYPE_SIM == enSimType)
    {
        return VOS_TRUE;
    }

    /* PSû�н���Detach */
    if (VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
    {
        return VOS_FALSE;
    }


    /* CS������ע���CS����Ч */
    if ((VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
     || (VOS_FALSE == ucSimCsRegStatus))
    {
        return VOS_FALSE;
    }

    pstDetachReqCtx = NAS_MMC_GetDetachReqCtxAddr();

    if (VOS_FALSE == NAS_MMC_IsDetachReqestDisableLte(pstDetachReqCtx->enDetachType,
                                                      pstDetachReqCtx->enDetachReason))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_IsNeedEnableLte_DetachPs(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
    VOS_UINT8                                               ucCsAttachAllowFlg;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;           /* SIM������,USIM��SIM��*/

    /* ����������������MMC��Ҫ����enable LTE��
    (1)����disable LTE�ı��Ϊ��
    (2)CS����Ч��CS��������ע�� */

    /* ��ȡLTE��ʹ��״̬ */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
    ucCsAttachAllowFlg     = NAS_MML_GetCsAttachAllowFlg();

    /* �������ʱ�Ѿ�����en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config�����ý�ֹ��LTE���򷵻�VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }


    /* ���֮ǰδdisable LTE,Ҳ����Ҫenable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* SIM�������Ҳ�ΪL��ģ����Ҫenable LTE */
    enSimType = NAS_MML_GetSimType();
    if ((VOS_TRUE               != NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
     && (NAS_MML_SIM_TYPE_SIM   == enSimType))
    {
        return VOS_FALSE;
    }

    /* CS����Ч��CS��������ע�ᣬ��ҪEnable Lte */
    if ((VOS_FALSE == NAS_MML_GetSimCsRegStatus())
     || (VOS_FALSE == ucCsAttachAllowFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT32 NAS_MMC_IsNeedEnableLte_AttachPs(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    /* ����������������MMC��Ҫ����enable LTE��
    (1)����disable LTE�ı��Ϊ��
    (2)PS����Ч
    (3)USIM�� */

    /* ��ȡLTE��ʹ��״̬ */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    /* �������ʱ�Ѿ�����en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config�����ý�ֹ��LTE���򷵻�VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }


    /* ���֮ǰδdisable LTE,Ҳ����Ҫenable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* SIM�������Ҳ�ΪL��ģ����Ҫenable LTE */
    enSimType = NAS_MML_GetSimType();
    if ((VOS_TRUE               != NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
     && (NAS_MML_SIM_TYPE_SIM   == enSimType))
    {
        return VOS_FALSE;
    }

    /* PS����Ч */
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return VOS_FALSE;
    }

    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_IsNeedDisableLte_AttachCs(VOS_VOID)
{
    VOS_UINT8                                               ucSimPsRegStatus;
    VOS_UINT8                                               ucSimCsRegStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    /* ����Э�����������������������£���Ҫdisable LTE��
    (1)SYSCFG���õ�ǰ���뼼��ΪLW,LG,LWG
    (2)PS����Ч��PS������ע���SIM��
    (3)CS����Ч��ģʽΪCS+PS */

    ucSimPsRegStatus    = NAS_MML_GetSimPsRegStatus();
    ucSimCsRegStatus    = NAS_MML_GetSimCsRegStatus();
    enSimType           = NAS_MML_GetSimType();

    /* ��������ʱ����Ҫdisable LTE */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus() )
    {
        return VOS_FALSE;
    }

    /* ƽ̨��֧��LTEʱ����Ҫdisable LTE */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        return VOS_FALSE;
    }

    /* ����Ѿ�disable ����Ҫ��disable LTE */
    if (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
    {
        return VOS_FALSE;
    }

    /* LTE��ģ������disable lte */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    if (NAS_MML_SIM_TYPE_SIM == enSimType)
    {
        return VOS_TRUE;
    }

    /* CS����Ч */
    if (VOS_FALSE == ucSimCsRegStatus)
    {
        return VOS_FALSE;
    }

    /* PS����Ч������PS����attach */
    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (VOS_TRUE == ucSimPsRegStatus))
    {
        return VOS_FALSE;
    }


    if (NAS_MML_MS_MODE_PS_CS != NAS_MML_GetMsMode())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_IsNeedEnableLte_DetachCs(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    /* ����������������MMC��Ҫ����enable LTE��
    (1)����disable LTE�ı��Ϊ��
    (2)֧��LTE
    (3) USIM */

    /* ��ȡLTE��ʹ��״̬ */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
    enSimType              = NAS_MML_GetSimType();

    /* �������ʱ�Ѿ�����en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config�����ý�ֹ��LTE���򷵻�VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }


    /* ���֮ǰδdisable LTE,Ҳ����Ҫenable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* SIM�������Ҳ�ΪL��ģ����Ҫenable LTE */
    if ((VOS_TRUE               != NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
     && (NAS_MML_SIM_TYPE_SIM   == enSimType))
    {
        return VOS_FALSE;
    }


    /* disable ��enable lte�����ж�syscfg�Ƿ�֧��L */

    /* CSû�н���Detach */
    if (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
    {
        return VOS_FALSE;
    }

    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_IsNeedDisableLte_AttachCsPs(VOS_VOID)
{
    VOS_UINT8                                               ucSimPsRegStatus;
    VOS_UINT8                                               ucSimCsRegStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    /* ����Э�����������������������£���Ҫdisable LTE��
    (1)SYSCFG���õ�ǰ���뼼��ΪLW,LG,LWG
    (2)PS����Ч��SIM��
    (3)CS����Ч */

    ucSimPsRegStatus    = NAS_MML_GetSimPsRegStatus();
    ucSimCsRegStatus    = NAS_MML_GetSimCsRegStatus();
    enSimType              = NAS_MML_GetSimType();

    /* ��������ʱ����Ҫdisable LTE */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus() )
    {
        return VOS_FALSE;
    }

    /* ƽ̨��֧��LTEʱ����Ҫdisable LTE */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        return VOS_FALSE;
    }

    /* ����Ѿ�disable ����Ҫ��disable LTE */
    if (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
    {
        return VOS_FALSE;
    }

    /* LTE��ģ */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    if (NAS_MML_SIM_TYPE_SIM == enSimType)
    {
        return VOS_TRUE;
    }

    /* CS����Ч */
    if (VOS_FALSE == ucSimCsRegStatus)
    {
        return VOS_FALSE;
    }

    /* PS����Ч */
    if (VOS_TRUE == ucSimPsRegStatus)
    {
        return VOS_FALSE;
    }


    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_IsNeedEnableLte_AttachCsPs(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    /* ����������������MMC��Ҫ����enable LTE��
    (1)����disable LTE�ı��Ϊ��
    (2)PS����Ч */

    /* ��ȡLTE��ʹ��״̬ */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    /* �������ʱ�Ѿ�����en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config�����ý�ֹ��LTE���򷵻�VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }

    /* ���֮ǰδdisable LTE,Ҳ����Ҫenable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* SIM�������Ҳ�ΪL��ģ����Ҫenable LTE */
    enSimType = NAS_MML_GetSimType();
    if ((VOS_TRUE               != NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
     && (NAS_MML_SIM_TYPE_SIM   == enSimType))
    {
        return VOS_FALSE;
    }

    /* disable ��enable lte�����ж�syscfg�Ƿ�֧��L */

    /* PS����Ч */
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_IsNeedDisableLte_DetachCsPs(VOS_VOID)
{
    /* �ó�������ҪDisable lte, ����Ԥ��������չʹ�� */
    return VOS_FALSE;
}
VOS_UINT32 NAS_MMC_IsNeedEnableLte_DetachCsPs(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;           /* SIM������,USIM��SIM��*/

    /* ����������������MMC��Ҫ����enable LTE��
    (1)����disable LTE�ı��Ϊ��
    (2)֧��LTE */

    /* ��ȡLTE��ʹ��״̬ */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    /* �������ʱ�Ѿ�����en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config�����ý�ֹ��LTE���򷵻�VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }


    /* ���֮ǰδdisable LTE,Ҳ����Ҫenable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* disable ��enable lte�����ж�syscfg�Ƿ�֧��L */

    /* SIM�������Ҳ�ΪL��ģ����Ҫenable LTE */
    enSimType = NAS_MML_GetSimType();
    if ((VOS_TRUE               != NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
     && (NAS_MML_SIM_TYPE_SIM   == enSimType))
    {
        return VOS_FALSE;
    }

    /* CSû�н���Detach */
    if (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_IsNeedDisableLteRoam(
    VOS_UINT32                          ulMcc
)
{
    VOS_UINT32                          aulComparedMcc[NAS_MML_ROAM_ENABLED_MAX_MCC_NUMBER];

    VOS_UINT32                          ulPlatformSuppLteFlg;

    ulPlatformSuppLteFlg = NAS_MML_IsPlatformSupportLte();


    /* MCC��Чʱ�򣬲���ҪDISABLE LTE */
    if ( VOS_FALSE == NAS_MML_IsMccValid(ulMcc) )
    {
        return VOS_FALSE;
    }

    /* ��ֹLTE��������ʱ */
    if ((VOS_FALSE == NAS_MML_GetLteRoamAllowedFlg())
     && (VOS_TRUE == ulPlatformSuppLteFlg))
    {
        /* ��ȡ��Ӫ�̶��Ƶ�MCC�б� */
        NAS_MML_GetRoamEnabledMccList(aulComparedMcc);

        /* ��ǰפ��PLMN IDΪ������������ */
        if (VOS_FALSE == NAS_MML_IsMccInDestMccList(ulMcc, NAS_MML_ROAM_ENABLED_MAX_MCC_NUMBER, aulComparedMcc))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MMC_IsNeedEnableLteRoam(
    VOS_UINT32                          ulMcc
)
{
    VOS_UINT32                          ulDisableLte;
    VOS_UINT32                          aulComparedMcc[NAS_MML_ROAM_ENABLED_MAX_MCC_NUMBER];

    /* ��ȡ�Ƿ���Ҫdisable LTE���α�� */
    ulDisableLte  = NAS_MML_GetDisableLteRoamFlg();


    /* MCC��Чʱ�򣬲���ҪDISABLE LTE */
    if ( VOS_FALSE == NAS_MML_IsMccValid(ulMcc) )
    {
        return VOS_FALSE;
    }

    /* �������ʱ�Ѿ�����en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config�����ý�ֹ��LTE���򷵻�VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }

    /* ��ֹLTE��������ʱ */
    if (VOS_FALSE == NAS_MML_GetLteRoamAllowedFlg())
    {
        /* ��ȡ��Ӫ�̶��Ƶ�MCC�б� */
        NAS_MML_GetRoamEnabledMccList(aulComparedMcc);

        /* ��ǰפ��PLMN IDΪ�������粢���Ѿ�disable LTE */
        if ((VOS_TRUE == NAS_MML_IsMccInDestMccList(ulMcc, NAS_MML_ROAM_ENABLED_MAX_MCC_NUMBER, aulComparedMcc))
         && (VOS_TRUE == ulDisableLte))
        {
           return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MMC_IsNeedEnableLte_ImsSwitchOnOrNotCsOnly(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;           /* SIM������,USIM��SIM��*/

    /* ����������������MMC��Ҫ����enable LTE��
    (1)NVû�����ý�ֹLTEģ
    (2)�Ѿ�Disable LTE
    (3)USIM��,����SIM��L��ģ
    (4)PS����Ч,������ע��
    (5)Disable LTE��ԭ��ֵΪLTE��voice unavailable
    (6)UE֧��IMS
    (7)voice domain��Ϊcs only

    ����ط���DS�ĵ���ͬ����Ϊ��ʱ�޷�֪��֮ǰ��LTE����ע��ɹ����µ�Disable LTE
    ����������ʧ��5�ε��µ�Disable LTE
    ����LTE������ע��������ʧ�ܵ����������ط�Ҳ��Enable LTE�����������LTE����Ȼʧ�ܣ���Disable LTE */

    /* ��ȡLTE��ʹ��״̬ */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    /* �������ʱ�Ѿ�����en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config�����ý�ֹ��LTE���򷵻�VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }


    /* ���֮ǰδdisable LTE,Ҳ����Ҫenable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* UE��֧��ims */
    if (VOS_FALSE == NAS_MML_IsUeSupportIms())
    {
        return VOS_FALSE;
    }

    /* voice domainΪcs only */
    if (NAS_MML_CS_VOICE_ONLY == NAS_MML_GetVoiceDomainPreference())
    {
        return VOS_FALSE;
    }

    /* SIM�������Ҳ�ΪL��ģ����Ҫenable LTE */
    enSimType = NAS_MML_GetSimType();
    if ((VOS_TRUE               != NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
     && (NAS_MML_SIM_TYPE_SIM   == enSimType))
    {
        return VOS_FALSE;
    }

    /* PS����Ч */
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return VOS_FALSE;
    }

    /* PS��������ע�� */
    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        return VOS_FALSE;
    }

    /* Disable LTE��ԭ��ֵΪLTE������������ */
    if (MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE == NAS_MML_GetDisableLteReason())
    {
       return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT32 NAS_MMC_IsCampLteNormalService(VOS_VOID)
{
    /* ��ǰ���뼼������LTE */
    if ( NAS_MML_NET_RAT_TYPE_LTE != NAS_MML_GetCurrNetRatType() )
    {
        return VOS_FALSE;
    }

    /* ��ǰNASΪδפ��״̬ */
    if (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == NAS_MMC_GetSpecPlmnSearchState())
    {
        return VOS_FALSE;
    }

    /* ��ǰ���ڷ���������״̬ */
    if (VOS_FALSE == NAS_MMC_IsNormalServiceStatus())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
VOS_UINT32  NAS_MMC_IsReCampLteLimitedService( VOS_VOID )
{
    /* ��ǰ���뼼������LTE */
    if ( NAS_MML_NET_RAT_TYPE_LTE != NAS_MML_GetCurrNetRatType() )
    {
        return VOS_FALSE;
    }

    /* ��ǰNASΪδפ��״̬ */
    if (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == NAS_MMC_GetSpecPlmnSearchState())
    {
        return VOS_FALSE;
    }

    /* ����ǿ���Ч���µ���Ҫdisable lte����,����Ҫ��LTE�� */
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return VOS_FALSE;
    }

    /* �����PS��detach���µ���Ҫdisable lte����,����Ҫ��LTE�� */
    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


#endif

/* Deleted by n00355355 for User_Exp_Improve, 2015-9-21, begin */
/* NAS_MMC_GetMmlCsTransactionStatu�����Ƶ�NAS MML LIB ��*/
/* Deleted by n00355355 for User_Exp_Improve, 2015-9-21, end */


VOS_VOID NAS_MMC_SortPlmnSearchListSpecRatPrioLowest(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enSpecRatType,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    /* �б��б����PLMN���� */
    VOS_UINT16                          usSearchPlmnNum;
    usSearchPlmnNum  = pstPlmnSelectionListInfo->usSearchPlmnNum;

    for( i = 0; i < usSearchPlmnNum; i++ )
    {
        for ( j = 0; j < pstPlmnSelectionListInfo->astPlmnSelectionList[i].ucRatNum; j++ )
        {
            /* ����ǰPLMN�б����������˳� */
            if ( NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST <= pstPlmnSelectionListInfo->usSearchPlmnNum )
            {
                return;
            }

            if ( enSpecRatType == pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j].enRatType )
            {

                /* ����һ�ݵ�ǰ�����������Ϣ�����е������б�ĺ��� */
                PS_MEM_CPY(&(pstPlmnSelectionListInfo->astPlmnSelectionList[pstPlmnSelectionListInfo->usSearchPlmnNum]),
                           &(pstPlmnSelectionListInfo->astPlmnSelectionList[i]),
                           sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));

                /* �����һ������Ľ��뼼����������Ϊ1�����ҽ��뼼������Ϊ�û���Ҫ���õĽ��뼼�� */
                pstPlmnSelectionListInfo->astPlmnSelectionList[pstPlmnSelectionListInfo->usSearchPlmnNum].ucRatNum = 1;
                pstPlmnSelectionListInfo->astPlmnSelectionList[pstPlmnSelectionListInfo->usSearchPlmnNum].astPlmnRatInfo[0].enRatType = enSpecRatType;

                pstPlmnSelectionListInfo->astPlmnSelectionList[pstPlmnSelectionListInfo->usSearchPlmnNum].astPlmnRatInfo[0].enNetStatus
                    = pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j].enNetStatus;
                pstPlmnSelectionListInfo->astPlmnSelectionList[pstPlmnSelectionListInfo->usSearchPlmnNum].astPlmnRatInfo[0].enQuality
                    = pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j].enQuality;
                pstPlmnSelectionListInfo->astPlmnSelectionList[pstPlmnSelectionListInfo->usSearchPlmnNum].astPlmnRatInfo[0].lRscp
                    = pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j].lRscp;
                pstPlmnSelectionListInfo->astPlmnSelectionList[pstPlmnSelectionListInfo->usSearchPlmnNum].astPlmnRatInfo[0].ucReserve
                    = 0;

                /* ѡ�������б��е��������������1�� */
                pstPlmnSelectionListInfo->usSearchPlmnNum++;

                /* ����ǰ����������Ҫ�ƶ��Ľ��뼼������Ϊ��Чֵ������ǰ����Ľ��뼼���������һ����
                       ����Ҫ������Ľ��뼼���Ƶ�ǰ��ȥ */
                pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j].enRatType = NAS_MML_NET_RAT_TYPE_BUTT;
                if ( (NAS_MML_MAX_RAT_NUM - 1) > j  )
                {
                    /*lint -e961*/
                    (VOS_VOID)PS_MEM_MOVE(&(pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j]),
                            &(pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j + 1] ),
                            (NAS_MML_MAX_RAT_NUM - j - 1) * sizeof(NAS_MMC_PLMN_RAT_INFO_STRU));
                    /*lint +e961*/
                }

                /* ��ǰ��������Ľ��뼼������һ�� */
                pstPlmnSelectionListInfo->astPlmnSelectionList[i].ucRatNum--;


                /* �ҵ���ָ�����뼼�������磬���˳�����ѭ����������һ������ */
                break;

            }
        }
    }

    /* ������н��뼼������Ϊ0������ */
    for ( i = 0; i < usSearchPlmnNum;  )
    {
        /* ����ǰ���������Ľ��뼼������Ϊ0������ɾ����PLMN���� */
        if( 0 == pstPlmnSelectionListInfo->astPlmnSelectionList[i].ucRatNum )
        {
            if (i < (NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST - 1))
            {
                /*lint -e961*/
                (VOS_VOID)PS_MEM_MOVE(&(pstPlmnSelectionListInfo->astPlmnSelectionList[i]),
                        &(pstPlmnSelectionListInfo->astPlmnSelectionList[i + 1] ),
                        (NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST - i - 1) * sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));
                /*lint +e961*/
            }

            /* ѡ�������б��е��������������1�� */
            pstPlmnSelectionListInfo->usSearchPlmnNum--;

            /* ��Ҫ�жϴ�����뼼��Ϊ0�������������һ�� */
            usSearchPlmnNum--;
            continue;
        }

        i++;
    }
}


VOS_UINT32 NAS_MMC_IsRejectedBySpecCause(
    NAS_MMC_REG_DOMAIN_ENUM_UINT8       enDomain,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause
)
{
    NAS_MMC_PLMN_REG_REJ_CTX_STRU      *pstPlmnRegRejInfo = VOS_NULL_PTR;
    VOS_UINT8                           i;

    pstPlmnRegRejInfo = NAS_MMC_GetPlmnRegRejInfo();

    for (i = 0; i < pstPlmnRegRejInfo->ucPlmnRegInfoNum; i++)
    {
        if (NAS_MMC_REG_DOMAIN_PS == enDomain)
        {
            if ((enCause == pstPlmnRegRejInfo->astPlmnRegInfoList[i].enGPsRegStatus)
             || (enCause == pstPlmnRegRejInfo->astPlmnRegInfoList[i].enWPsRegStatus)
#if (FEATURE_ON == FEATURE_LTE)
             || (enCause == pstPlmnRegRejInfo->astPlmnRegInfoList[i].enLPsRegStatus)
#endif
             )
            {
                return VOS_TRUE;
            }
        }

        if (NAS_MMC_REG_DOMAIN_CS == enDomain)
        {
            if ((enCause == pstPlmnRegRejInfo->astPlmnRegInfoList[i].enGCsRegStatus)
             || (enCause == pstPlmnRegRejInfo->astPlmnRegInfoList[i].enWCsRegStatus)
#if (FEATURE_ON == FEATURE_LTE)
             || (enCause == pstPlmnRegRejInfo->astPlmnRegInfoList[i].enLCsRegStatus)
#endif
             )
            {
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsAisRoamingEffect
 ��������  : �ж�AIS�������ι����Ƿ���Ч
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ч
             VOS_FALSE:����Ч
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��5��17��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsAisRoamingEffect( VOS_VOID )
{
    /******************************************************************
    1.���ĵ�ֻʵ���Զ�ģʽ��������TOT�����硣
    2��ֻҪ���ض��򿪣���ֻ���AIS SIM��������TOT���硣
    3��������ֻ�ڿ����ͱ����ѹ����������á�
    4�������ѹ��̱�SYSCFG���û��б��ѡ����Ʒ������û���ѡ�Ȼ����������ĳ�����ϣ���������������ʵʱ����TOT����Ĵ���״̬����Ҫ�ȵ��´α����ѲŻ���TOT��
    *******************************************************************/
    NAS_MML_AIS_ROAMING_CFG_STRU        *pstAisRoamingCfg;


    pstAisRoamingCfg        = NAS_MML_GetAisRoamingCfg();

    /* NVIM�й��ܲ���Чʱ,ֱ�ӷ��ع��ܲ���Ч */
    if ( VOS_FALSE == pstAisRoamingCfg->ucEnableFlg )
    {
        return VOS_FALSE;
    }

    /* ��ǰ��AIS��SIM�� */
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn((NAS_MML_PLMN_ID_STRU*)&(pstAisRoamingCfg->stSimHPlmnId)))
    {
        return VOS_TRUE;
    }

    /* �����������VOS_FALSE */
    return VOS_FALSE;
}



VOS_VOID NAS_MMC_UpdateUserSpecPlmnRegisterStatusWhenRegFail(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enRegFailCause
)
{
    /* �Զ�ģʽ�²���Ҫ���¸�ȫ�ֱ��� */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        return;
    }

    if ( (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW  == enRegFailCause)
      || (NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW  == enRegFailCause))
    {
        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_FALSE);
    }
}
VOS_VOID NAS_MMC_UpdateUserSpecPlmnRegisterStatus(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause
)
{
    /* �Զ�ģʽ�²���Ҫ���¸�ȫ�ֱ��� */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        return;
    }

    if (NAS_MML_REG_FAIL_CAUSE_NULL == enCause)
    {
        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);
    }
    else
    {
        NAS_MMC_UpdateUserSpecPlmnRegisterStatusWhenRegFail(enCause);
    }

}
VOS_VOID  NAS_MMC_UpdateEhplmnRat_WithEhplmnRatList(
    NAS_MML_PLMN_ID_STRU                stPlmnId,
    VOS_UINT16                         *pusRatForOneEhplmnItem,
    VOS_UINT32                         *pulPlmnNum,
    NAS_MML_SIM_PLMN_WITH_RAT_STRU     *pstPlmnWithRatInfo
)
{
    NAS_MML_SIM_HPLMN_WITH_RAT_INFO_STRU        *pstHplmnWithRatList= VOS_NULL_PTR;
    VOS_UINT32                                   i;
    VOS_UINT32                                   ulEqual;
    VOS_UINT16                                   usRatInUsim;
    VOS_UINT16                                   usUeSptRat;

#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
    {
        usUeSptRat          = NAS_MML_SIM_UE_SUPPORT_RAT_SUPPORT_LTE;
    }
    else
    {
        usUeSptRat          = NAS_MML_SIM_UE_SUPPORT_RAT;
    }
#else
    usUeSptRat          = NAS_MML_SIM_UE_SUPPORT_RAT;
#endif

    pstHplmnWithRatList = NAS_MML_GetSimHplmnWithRatList();
    ulEqual             = VOS_FALSE;

    /* ��ȡSIM����Ϣ */
    for (i = 0; i < pstHplmnWithRatList->ucHPlmnWithRatNum; i++)
    {
        ulEqual = NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstHplmnWithRatList->astHPlmnWithRatInfo[i].stPlmnId),
                                                     &stPlmnId);
        if (VOS_TRUE == ulEqual )
        {
            usRatInUsim = pstHplmnWithRatList->astHPlmnWithRatInfo[i].usSimRat;

            if (NAS_MML_SIM_NO_RAT == ( usRatInUsim & (NAS_MML_SIM_ALL_RAT_SUPPORT_LTE)))
            {
                usRatInUsim = usUeSptRat;
            }
            else
            {
                usRatInUsim &= usUeSptRat;
            }

            if (NAS_MML_SIM_NO_RAT != ((~*pusRatForOneEhplmnItem) & usRatInUsim))
            {
                /*����Sim���д��ڵ�ʣ��Ľ��뼼������ʱȫ�ֱ�������*/
                pstPlmnWithRatInfo[*pulPlmnNum].usSimRat = ((~*pusRatForOneEhplmnItem) & usRatInUsim);

                pstPlmnWithRatInfo[*pulPlmnNum].stPlmnId.ulMcc = stPlmnId.ulMcc;

                pstPlmnWithRatInfo[*pulPlmnNum].stPlmnId.ulMnc = stPlmnId.ulMnc;

                (*pulPlmnNum)++;

                (*pusRatForOneEhplmnItem) |= usRatInUsim;
            }

            if ((*pulPlmnNum >= NAS_MML_MAX_EHPLMN_NUM)
             || (usUeSptRat == (*pusRatForOneEhplmnItem & usUeSptRat)))
            {
                /*  ��ǰPlmn�����������������������н��뼼������ӣ� �˳��������� */
                break;
            }
        }
    }

}


VOS_VOID  NAS_MMC_UpdateEhplmnRat_WithNvPrioHplmnAct(VOS_VOID)
{
    NAS_MML_PRIO_HPLMNACT_CFG_STRU              *pstNvPrioHPlmnActCfg;
    NAS_MML_SIM_EHPLMN_INFO_STRU                *pstEHPlmnInfo = VOS_NULL_PTR;
    NAS_MML_SIM_PLMN_WITH_RAT_STRU              *pstTmpPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                                   k;
    VOS_UINT32                                   i;
    VOS_UINT32                                   ulPlmnNum;
    VOS_UINT16                                   usRatForOneEhplmnItem;
    VOS_UINT16                                   usRatNeedToAdd;
    VOS_UINT16                                   usUeSptRat;

    pstNvPrioHPlmnActCfg = NAS_MML_GetPrioHplmnActCfg();

    /* ��ȡSIM����EHPLMN��Ϣ*/
    pstEHPlmnInfo       = NAS_MML_GetSimEhplmnList();

    ulPlmnNum = 0;

#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
    {
        usUeSptRat          = NAS_MML_SIM_UE_SUPPORT_RAT_SUPPORT_LTE;
    }
    else
    {
        usUeSptRat          = NAS_MML_SIM_UE_SUPPORT_RAT;
    }
#else
    usUeSptRat          = NAS_MML_SIM_UE_SUPPORT_RAT;
#endif

    pstTmpPlmnInfo  = (NAS_MML_SIM_PLMN_WITH_RAT_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC, NAS_MML_MAX_EHPLMN_NUM * sizeof(NAS_MML_SIM_PLMN_WITH_RAT_STRU));

    if ( VOS_NULL_PTR == pstTmpPlmnInfo )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdateEhplmnRat: Alloc Mem Failed ");
        return;
    }

    NAS_MML_InitSimPlmnInfo(NAS_MML_MAX_EHPLMN_NUM, pstTmpPlmnInfo);

    /*����NVֵ��EHPLMN�Ľ��뼼������*/
    for ( k = 0; k < pstEHPlmnInfo->ucEhPlmnNum; k++ )
    {
        usRatForOneEhplmnItem = 0;

        /* ��NV�����õ�HPLMNAct��Ϊ������ȼ���ֱ����� */
        if (ulPlmnNum < NAS_MML_MAX_EHPLMN_NUM)
        {
            pstTmpPlmnInfo[ulPlmnNum].usSimRat = pstNvPrioHPlmnActCfg->usPrioHplmnAct;

            pstTmpPlmnInfo[ulPlmnNum].stPlmnId.ulMcc = pstEHPlmnInfo->astEhPlmnInfo[k].stPlmnId.ulMcc;

            pstTmpPlmnInfo[ulPlmnNum].stPlmnId.ulMnc = pstEHPlmnInfo->astEhPlmnInfo[k].stPlmnId.ulMnc;

            ulPlmnNum++;

            usRatForOneEhplmnItem = pstNvPrioHPlmnActCfg->usPrioHplmnAct;

        }

        /* EHPLMN������Ѵﵽ���������˳� */
        if(ulPlmnNum >= NAS_MML_MAX_EHPLMN_NUM)
        {
            break;
        }

        /* ���н��뼼������ӣ� �˳��������� */
        if (usUeSptRat == (usRatForOneEhplmnItem & usUeSptRat))
        {
            continue;
        }

        /* ��ȡSIM����Ϣ */
        NAS_MMC_UpdateEhplmnRat_WithEhplmnRatList(pstEHPlmnInfo->astEhPlmnInfo[k].stPlmnId,
                                                  &usRatForOneEhplmnItem,
                                                  &ulPlmnNum,
                                                  pstTmpPlmnInfo);

        /* ȷ��ʣ��� Ҫ��ӵ�RAT */
        usRatNeedToAdd = ( (~usRatForOneEhplmnItem) & usUeSptRat);

        if ((NAS_MML_SIM_NO_RAT != usRatNeedToAdd)
         && (ulPlmnNum  < NAS_MML_MAX_EHPLMN_NUM))
        {
             /* ��NV�кͿ��е�HplmnAct�����ж�Ӧ��RAT,��Ҫ������н��뼼��;
                ������Ӳ��� RAT,���ʣ���RAT
             */
            pstTmpPlmnInfo[ulPlmnNum].usSimRat       = usRatNeedToAdd;

            pstTmpPlmnInfo[ulPlmnNum].stPlmnId.ulMcc = pstEHPlmnInfo->astEhPlmnInfo[k].stPlmnId.ulMcc;

            pstTmpPlmnInfo[ulPlmnNum].stPlmnId.ulMnc = pstEHPlmnInfo->astEhPlmnInfo[k].stPlmnId.ulMnc;

            ulPlmnNum++;
        }

    }

    /* ����Hplmn�ĸ�����Rat�б� */
    pstEHPlmnInfo->ucEhPlmnNum = (VOS_UINT8)ulPlmnNum;
    for (i = 0; i < ulPlmnNum; i++)
    {
        pstEHPlmnInfo->astEhPlmnInfo[i].stPlmnId.ulMcc = pstTmpPlmnInfo[i].stPlmnId.ulMcc;
        pstEHPlmnInfo->astEhPlmnInfo[i].stPlmnId.ulMnc = pstTmpPlmnInfo[i].stPlmnId.ulMnc;
        pstEHPlmnInfo->astEhPlmnInfo[i].usSimRat       = pstTmpPlmnInfo[i].usSimRat;
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pstTmpPlmnInfo);
    return;
}
VOS_VOID  NAS_MMC_UpdateEhplmnRat_WithOrigSimHplmnAct(VOS_VOID)
{
    NAS_MML_SIM_EHPLMN_INFO_STRU                           *pstEHPlmnInfo = VOS_NULL_PTR;
    NAS_MML_SIM_PLMN_WITH_RAT_STRU                         *pstTmpPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                                              k;
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulPlmnNum;
    VOS_UINT16                                              usRatForOneEhplmnItem;
    VOS_UINT16                                              usRatNeedToAdd;
    VOS_UINT16                                              usUeSptRat;

    /* ��ȡSIM����EHPLMN��Ϣ*/
    pstEHPlmnInfo       = NAS_MML_GetSimEhplmnList();

#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
    {
        usUeSptRat          = NAS_MML_SIM_UE_SUPPORT_RAT_SUPPORT_LTE;
    }
    else
    {
        usUeSptRat          = NAS_MML_SIM_UE_SUPPORT_RAT;
    }
#else
    usUeSptRat          = NAS_MML_SIM_UE_SUPPORT_RAT;
#endif

    /* HPLMNĬ���� ���ģʽ��֧�ֵ�,HPLMNWithRat�еĽ���ģʽ����
    ��Ҫ���µ�ǰPLMN�Ľ������ȼ�,�����ǰHPLMNWithRat֧������ģʽ,
    �򲻽����޸�,�����ǰHPLMNWithRat֧�ֵ�ģ��2��ģʽ,����Ҫ����HplmnWithACt,ȷ�����µĽ��뼼�����ȼ�ָʾ,
    ֧�� ��ģʽ ����ǰ��,����ģʽ�ķ��ں���;
    ��HplmnWithActָʾ: W -> L ��������Ҫ��3�� Hplmn: W->L->G ;����ָʾ W,�����ΪW->LG
    */
    ulPlmnNum = 0;

    pstTmpPlmnInfo  = (NAS_MML_SIM_PLMN_WITH_RAT_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC, NAS_MML_MAX_EHPLMN_NUM * sizeof(NAS_MML_SIM_PLMN_WITH_RAT_STRU));
    if ( VOS_NULL_PTR == pstTmpPlmnInfo )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdateEhplmnRat: Alloc Mem Failed ");
        return;
    }

    NAS_MML_InitSimPlmnInfo(NAS_MML_MAX_EHPLMN_NUM, pstTmpPlmnInfo);

    for ( k = 0; k < pstEHPlmnInfo->ucEhPlmnNum; k++ )
    {
        usRatForOneEhplmnItem = 0;

        /* ��SIM���ļ�0x6F62�л�ȡ��ӦPLMN��RAT */

        NAS_MMC_UpdateEhplmnRat_WithEhplmnRatList(pstEHPlmnInfo->astEhPlmnInfo[k].stPlmnId,
                                                  &usRatForOneEhplmnItem,
                                                  &ulPlmnNum,
                                                  pstTmpPlmnInfo);

        /* ȷ��ʣ��� Ҫ��ӵ�RAT */
        usRatNeedToAdd = ( (~usRatForOneEhplmnItem) & usUeSptRat);

        if ((NAS_MML_SIM_NO_RAT != usRatNeedToAdd)
         && (ulPlmnNum  < NAS_MML_MAX_EHPLMN_NUM))
        {
             /* ����û���ҵ���Ӧ��RAT,��Ҫ������н��뼼��;
                ������Ӳ��� RAT,���ʣ���RAT
             */
            pstTmpPlmnInfo[ulPlmnNum].usSimRat       = usRatNeedToAdd;

            pstTmpPlmnInfo[ulPlmnNum].stPlmnId.ulMcc = pstEHPlmnInfo->astEhPlmnInfo[k].stPlmnId.ulMcc;

            pstTmpPlmnInfo[ulPlmnNum].stPlmnId.ulMnc = pstEHPlmnInfo->astEhPlmnInfo[k].stPlmnId.ulMnc;

            ulPlmnNum++;
        }

    }

    /* ����Hplmn�ĸ�����Rat�б� */
    pstEHPlmnInfo->ucEhPlmnNum = (VOS_UINT8)ulPlmnNum;
    for (i =0;i< ulPlmnNum;i++)
    {
        pstEHPlmnInfo->astEhPlmnInfo[i].stPlmnId.ulMcc = pstTmpPlmnInfo[i].stPlmnId.ulMcc;
        pstEHPlmnInfo->astEhPlmnInfo[i].stPlmnId.ulMnc = pstTmpPlmnInfo[i].stPlmnId.ulMnc;
        pstEHPlmnInfo->astEhPlmnInfo[i].usSimRat       = pstTmpPlmnInfo[i].usSimRat;
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pstTmpPlmnInfo);
}
VOS_VOID  NAS_MMC_UpdateEhplmnRat(VOS_VOID)
{

    NAS_MML_PRIO_HPLMNACT_CFG_STRU     *pstPrioHPlmnActCfg;

    pstPrioHPlmnActCfg = NAS_MML_GetPrioHplmnActCfg();

    if ((VOS_TRUE == pstPrioHPlmnActCfg->ucActiveFlg)
     && (NAS_MML_SIM_NO_RAT != pstPrioHPlmnActCfg->usPrioHplmnAct))
    {
        /*����NV���Ƶ�HPLMN��������Sim���е�HPLMNACt����HPLMN�Ľ��뼼��*/
        NAS_MMC_UpdateEhplmnRat_WithNvPrioHplmnAct();
    }
    else
    {
        /* ����ԭʼ��SIM���е�HPLMN������򲹳�EHPLMN�Ľ��뼼��*/
        NAS_MMC_UpdateEhplmnRat_WithOrigSimHplmnAct();
    }
    return;
}
VOS_VOID  NAS_MMC_UpdateHomePlmn(
    VOS_UINT8                           *pucIMSI
)
{
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstEHPlmnInfo = VOS_NULL_PTR;

    VOS_UINT8                           ucUsimMncLenth;
    VOS_UINT8                           ucExactlyComparaFlag;

    ucUsimMncLenth       = NAS_MML_GetUsimMncLen();
    ucExactlyComparaFlag = NAS_MML_GetPlmnExactlyComparaFlg();

    pstEHPlmnInfo   = NAS_MML_GetSimEhplmnList();

    pstEHPlmnInfo->ucEhPlmnNum = 1;

    PS_MEM_SET(&pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId, 0, sizeof(NAS_MML_PLMN_ID_STRU));
    pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMcc |= (pucIMSI[1] & NAS_MML_OCTET_HIGH_FOUR_BITS) >> NAS_MML_OCTET_MOVE_FOUR_BITS;
    pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMcc |= (pucIMSI[2] & NAS_MML_OCTET_LOW_FOUR_BITS) << NAS_MML_OCTET_MOVE_EIGHT_BITS;
    pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMcc |= (pucIMSI[2] & NAS_MML_OCTET_HIGH_FOUR_BITS) << NAS_MML_OCTET_MOVE_TWELVE_BITS;
    pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMnc |= (pucIMSI[3] & NAS_MML_OCTET_LOW_FOUR_BITS);
    pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMnc |= (pucIMSI[3] & NAS_MML_OCTET_HIGH_FOUR_BITS) << NAS_MML_OCTET_MOVE_FOUR_BITS;

    if ((NAS_MMC_MNC_LENGTH_TWO_BYTES_IN_IMSI == ucUsimMncLenth)
     && (VOS_TRUE == ucExactlyComparaFlag))
    {
        pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMnc |= (NAS_MML_LOW_BYTE_INVALID) << NAS_MML_OCTET_MOVE_SIXTEEN_BITS;
    }
    else
    {
        pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMnc |= (pucIMSI[4] & NAS_MML_OCTET_LOW_FOUR_BITS) << NAS_MML_OCTET_MOVE_SIXTEEN_BITS;
    }

    /* ����PLMN ID��ͬ�ıȽϣ�ĩλΪ0����F��������Ѿ����µıȽϺ�����
      ����:NAS_MMC_CompareBcchPlmnwithSimPlmn����Ҫ�������PLMN ID������
      ���ƶ��������⴦����Ҫ����,���2λMNC��HPLMN��Hplmn�б���,
      �ƶ�MCC=460,MNC=02��07�й��ƶ������⴦��
    */
    if (( 0x000604 == pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMcc )
     && ( (0x200   == (pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMnc & 0xFFFF ) )
       || (0x700   == (pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMnc & 0xFFFF))))
    {
        pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMnc &= 0xFF0000;
    }
}

VOS_VOID NAS_MMC_DelLowPrioEHPlmn(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU  *pstReportList
)
{
    NAS_MML_SIM_EHPLMN_INFO_STRU           *pstEHPlmnList;
    VOS_UINT32                              i,j;
    VOS_UINT8                               ucHighPrioPlmn;
    VOS_UINT16                              usSearchPlmnNum;
    NAS_MML_PLMN_ID_STRU                    stHighPrioPlmnId;

    pstEHPlmnList   = NAS_MML_GetSimEhplmnList();
    ucHighPrioPlmn  = VOS_TRUE;
    usSearchPlmnNum = pstReportList->usSearchPlmnNum;

    stHighPrioPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stHighPrioPlmnId.ulMnc = NAS_MML_INVALID_MNC;

    for ( i = 0 ; i < pstEHPlmnList->ucEhPlmnNum ; i++ )
    {
        for ( j = 0 ; j < pstReportList->usSearchPlmnNum ; j++ )
        {
            /* ���ҵ���ǰ���ȼ���ߵ�EHPLMN��list�д��� */
            if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&pstReportList->astPlmnSelectionList[j].stPlmnId,
                                                               &pstEHPlmnList->astEhPlmnInfo[i].stPlmnId))
            {
                /* ������������ȼ���EHPLMN */
                if ( VOS_TRUE == ucHighPrioPlmn )
                {
                    ucHighPrioPlmn         = VOS_FALSE;
                    stHighPrioPlmnId.ulMcc = pstEHPlmnList->astEhPlmnInfo[i].stPlmnId.ulMcc;
                    stHighPrioPlmnId.ulMnc = pstEHPlmnList->astEhPlmnInfo[i].stPlmnId.ulMnc;
                    continue;
                }

                if (VOS_FALSE == NAS_MML_CompareBcchPlmnwithSimPlmn(&stHighPrioPlmnId,
                                                               &pstEHPlmnList->astEhPlmnInfo[i].stPlmnId))
                {
                    /* ɾ��������PLMN */
                    /*lint -e961*/
                    (VOS_VOID)PS_MEM_MOVE(&(pstReportList->astPlmnSelectionList[j]),
                                &(pstReportList->astPlmnSelectionList[j + 1]),
                                ((pstReportList->usSearchPlmnNum- j - 1) * sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU)));
                    /*lint +e961*/
                    usSearchPlmnNum--;
                }
            }
        }
    }

    pstReportList->usSearchPlmnNum = usSearchPlmnNum;
}




#if (FEATURE_ON == FEATURE_LTE)


VOS_VOID  NAS_MMC_RcvGuSysInfoIndSetLteRoamAbility(
    VOS_UINT32                                              ulSysInfoMcc,
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus
)
{    /* �Ƿ���Ҫ��ֹLTE���� */
    if (VOS_TRUE == NAS_MMC_IsNeedDisableLteRoam(ulSysInfoMcc))
    {
        /* �Ѿ�֪ͨdisable LTE����Ҫ��֪ͨ�� */
        if ((VOS_FALSE == NAS_MML_GetDisableLteRoamFlg())
         && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLCapabilityStatus))
        {
            if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE != NAS_MML_GetLteForbiddenStatusFlg())
            {
                NAS_MMC_SndDisableLteNotify(MMC_LMM_DISABLE_LTE_REASON_LTE_ROAMING_NOT_ALLOWED);

                /* ��¼disable lteʱפ����������Ϣ */
                NAS_MMC_SetDisabledLtePlmnId(NAS_MML_GetCurrCampPlmnId());
            }

        }

        /* ����disable LTE������� */
        NAS_MML_SetDisableLteRoamFlg(VOS_TRUE);

        if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
        {
            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_IMSI_IN_FORBIDDEN_LIST);
        }
        else
        {
            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_ROAMING_NOT_ALLOWED);
        }
        return;
    }

    /* �Ƿ���Ҫ����LTE���� */
    if (VOS_TRUE == NAS_MMC_IsNeedEnableLteRoam(ulSysInfoMcc))
    {
        /* ��ǰLTE�����ָ����û���ΪĬ��ֵ */
        if ((NAS_MML_LTE_CAPABILITY_STATUS_BUTT == enLCapabilityStatus)
         || (NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS == enLCapabilityStatus))
        {
            NAS_MMC_SndEnableLteNotify();
            NAS_MMC_ClearDisabledLtePlmnId();
            NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
        }

        if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
        }

        /* ����disable LTE������� */
        NAS_MML_SetDisableLteRoamFlg(VOS_FALSE);
    }
    return;

}
#endif

VOS_UINT32 NAS_MMC_IsInterNationalRoamingSearchRPLMN(
    VOS_UINT32                          ulMcc
)
{
    VOS_UINT32                          *aulComparedMcc ;

    aulComparedMcc = NAS_MML_GetNationalMCCList();

    if( VOS_TRUE == NAS_MML_GetRoamRplmnSearchFlg() )
    {
        if (VOS_TRUE == NAS_MML_IsMccInDestMccList(ulMcc, NAS_MML_MAX_NATIONAL_MCC_NUM, aulComparedMcc))
        {
           return VOS_FALSE;
        }
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

#if (FEATURE_ON == FEATURE_LTE)


VOS_UINT32 NAS_MCC_IsNeedDisableLteWBand(
    VOS_UINT32                         ulBand
)
{
    /*��Ҫ��NV���� */
    if (VOS_TRUE == NAS_MML_GetDisableLTEOnBandFlg())
    {
        /* ��ǰפ��Ƶ��ΪBAND9 */
        if (NAS_MMC_WCDMA_BAND_IX == ulBand)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;

}


VOS_VOID  NAS_MMC_RcvGuSysInfoIndSetLteAbility(
    struct MsgCB                       *pstMsg,
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus
)
{
    MSG_HEADER_STRU                    *MsgHeader      = VOS_NULL_PTR;
    RRMM_SYS_INFO_IND_STRU             *pstWrrSysinfo  = VOS_NULL_PTR;
    GRRMM_SYS_INFO_IND_ST              *pstGasSysInfo  = VOS_NULL_PTR;
    VOS_UINT32                          ulSysInfoMcc;
    VOS_UINT32                          ulBand;
    VOS_UINT32                          ucDisableLTEOnBandFlg;

    ulSysInfoMcc            = NAS_MML_INVALID_MCC;
    ulBand                  = 0;
    ucDisableLTEOnBandFlg   = VOS_FALSE;

    MsgHeader = (MSG_HEADER_STRU*)pstMsg;

    if( RRMM_SYS_INFO_IND == MsgHeader->ulMsgName )
    {
        /*3g��ϵͳ��Ϣ����,��ȡMCC��BAND��Ϣ*/
        pstWrrSysinfo = (RRMM_SYS_INFO_IND_STRU*)pstMsg;

        if (VOS_TRUE == pstWrrSysinfo->bitOpPlmnId)
        {
            ulSysInfoMcc = pstWrrSysinfo->PlmnId.ulMcc;
        }
        ulBand = pstWrrSysinfo->unWcdmaBand.ulBand;
    }
    else if( GRRMM_SYS_INFO_IND == MsgHeader->ulMsgName)
    {
        /*2g��ϵͳ��Ϣ����,��ȡMCC��BAND��Ϣ*/
        pstGasSysInfo = (GRRMM_SYS_INFO_IND_ST*)pstMsg;
        ulSysInfoMcc = pstGasSysInfo->PlmnId.ulMcc;
        ulBand = pstGasSysInfo->unGsmBand.ulBand;
    }
    else
    {
        return;
    }

    ucDisableLTEOnBandFlg = NAS_MCC_IsNeedDisableLteWBand(ulBand);

    /* �Ƿ���Ҫ��ֹLTE���� */
    if ( (VOS_TRUE == NAS_MMC_IsNeedDisableLteRoam(ulSysInfoMcc))
      || (VOS_TRUE == ucDisableLTEOnBandFlg) )
    {
        /* �Ѿ�֪ͨdisable LTE����Ҫ��֪ͨ�� */
        if ((VOS_FALSE == NAS_MML_GetDisableLteRoamFlg())
         && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLCapabilityStatus))
        {
            NAS_MMC_SndDisableLteNotify(MMC_LMM_DISABLE_LTE_REASON_LTE_ROAMING_NOT_ALLOWED);

            /* ��¼disable lteʱפ����������Ϣ */
            NAS_MMC_SetDisabledLtePlmnId(NAS_MML_GetCurrCampPlmnId());
        }

        /* ����disable LTE������� */
        NAS_MML_SetDisableLteRoamFlg(VOS_TRUE);

        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_ROAMING_NOT_ALLOWED);
        return;
    }

    /* �Ƿ���Ҫ����LTE���� */
    if ( (VOS_TRUE  == NAS_MMC_IsNeedEnableLteRoam(ulSysInfoMcc))
      && (VOS_FALSE == ucDisableLTEOnBandFlg) )
    {
        /* ��ǰLTE�����ָ����û���ΪĬ��ֵ */
        if ((NAS_MML_LTE_CAPABILITY_STATUS_BUTT == enLCapabilityStatus)
         || (NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS == enLCapabilityStatus))
        {
            NAS_MMC_SndEnableLteNotify();
            NAS_MMC_ClearDisabledLtePlmnId();
            NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
        }

        if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
        }

        /* ����disable LTE������� */
        NAS_MML_SetDisableLteRoamFlg(VOS_FALSE);
    }
    return;

}

#endif
VOS_VOID NAS_MMC_DelHplmnInFplmn(VOS_VOID)
{
    VOS_INT8                            i;
    VOS_UINT8                           ucForbPlmnNum;
    VOS_UINT32                          ulHplmnInFplmnFlg;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo;

    pstForbidPlmnInfo           = NAS_MML_GetForbidPlmnInfo();

    ucForbPlmnNum               = pstForbidPlmnInfo->ucForbPlmnNum;
    ulHplmnInFplmnFlg           = VOS_FALSE;

    for (i = 0; i < ucForbPlmnNum; i++)
    {
        /* ���hplmn��fplmn�б�����ɾ��fplmnȫ�ֱ����еļ�¼,�����޷�����hplmn��ע�� */
        if ((VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(&(pstForbidPlmnInfo->astForbPlmnIdList[i]))))
        {
            if ( i < (ucForbPlmnNum - 1) )
            {
                (VOS_VOID)PS_MEM_MOVE(&pstForbidPlmnInfo->astForbPlmnIdList[i],
                            &pstForbidPlmnInfo->astForbPlmnIdList[i+1],
                            ((ucForbPlmnNum - i) - 1) * sizeof(NAS_MML_PLMN_ID_STRU ) );
            }
            ucForbPlmnNum--;
            i--;
            ulHplmnInFplmnFlg = VOS_TRUE;
        }
    }

    pstForbidPlmnInfo->ucForbPlmnNum = ucForbPlmnNum;

    if (VOS_TRUE == ulHplmnInFplmnFlg)
    {
        /* ���HPLMN������FPLMN����Ϊ���ļ����Ϸ�,��FPLMN��ɾ��HPLMN��¼ */
        NAS_MMC_SndUsimUpdateForbPlmnReq();
    }

}

#if (FEATURE_ON == FEATURE_LTE)


VOS_VOID NAS_MMC_ConvertLmmPlmnIdListToGUFormat_PlmnList(
    MMC_LMM_PLMN_ID_LIST_STRU          *pstSrcPlmnIdList,
    RRC_PLMN_ID_LIST_STRU              *pstDestPlmnIdList
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    NAS_MML_PLMN_ID_STRU                stPlmn;
    MMC_LMM_PLMN_ID_STRU                stLmmPlmn;
    RRC_NAS_RAT_TYPE_ENUM_UINT32        ulRrcRat;

    ulRrcRat = RRC_NAS_RAT_TYPE_BUTT;

    /* ��ת�������������б� */
    if (pstSrcPlmnIdList->ulLowPlmnNum > RRC_MAX_LOW_PLMN_NUM)
    {
        pstSrcPlmnIdList->ulLowPlmnNum = RRC_MAX_LOW_PLMN_NUM;
    }

    pstDestPlmnIdList->ulLowPlmnNum = pstSrcPlmnIdList->ulLowPlmnNum;

    for ( i = 0; i < pstSrcPlmnIdList->ulLowPlmnNum; i++)
    {
        /* ��L��ʽ��PLMN �б�ת����GU��ʽ��*/
        for ( j = 0; j < MMC_LMM_PLMN_ID_LEN; j++)
        {
            stLmmPlmn.aucPlmnId[j] = pstSrcPlmnIdList->astLowPlmnWithRatList[i].stPlmnIdWithRat.aucPlmnId[j];
        }
        NAS_MMC_ConvertLmmPlmnToGUNasFormat(&stLmmPlmn,
                                            &stPlmn);
        pstDestPlmnIdList->aLowPlmnList[i].PlmnId.stPlmnId.ulMcc = stPlmn.ulMcc;

        pstDestPlmnIdList->aLowPlmnList[i].PlmnId.stPlmnId.ulMnc = stPlmn.ulMnc;

        NAS_MMC_ConvertLmmRatToRrcFormat(pstSrcPlmnIdList->astLowPlmnWithRatList[i].stPlmnIdWithRat.enPlmnRat, &ulRrcRat);

        pstDestPlmnIdList->aLowPlmnList[i].PlmnId.ulRat = ulRrcRat;

        pstDestPlmnIdList->aLowPlmnList[i].lRscp =
                                pstSrcPlmnIdList->astLowPlmnWithRatList[i].lRscp;
    }

    /* ת�������������б� */
    if (pstSrcPlmnIdList->ulHighPlmnNum > RRC_MAX_HIGH_PLMN_NUM)
    {
        pstSrcPlmnIdList->ulHighPlmnNum = RRC_MAX_HIGH_PLMN_NUM;
    }

    pstDestPlmnIdList->ulHighPlmnNum = pstSrcPlmnIdList->ulHighPlmnNum;

    for ( i=0; i < pstSrcPlmnIdList->ulHighPlmnNum; i++)
    {
        /* ��L��ʽ��PLMN �б�ת����GU��ʽ��*/
        for ( j = 0; j < MMC_LMM_PLMN_ID_LEN; j++)
        {
            stLmmPlmn.aucPlmnId[j] = pstSrcPlmnIdList->astHighPlmnWithRatList[i].aucPlmnId[j];
        }

        NAS_MMC_ConvertLmmPlmnToGUNasFormat(&stLmmPlmn,
                                            &stPlmn);

        pstDestPlmnIdList->aHighPlmnList[i].stPlmnId.ulMcc = stPlmn.ulMcc;

        pstDestPlmnIdList->aHighPlmnList[i].stPlmnId.ulMnc = stPlmn.ulMnc;

        NAS_MMC_ConvertLmmRatToRrcFormat(pstSrcPlmnIdList->astHighPlmnWithRatList[i].enPlmnRat, &ulRrcRat);

        pstDestPlmnIdList->aHighPlmnList[i].ulRat = ulRrcRat;

    }
    return;
}


VOS_UINT32 NAS_MMC_IsNeedRelPsConnEnableLteTimerExpired(VOS_VOID)
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus  = VOS_NULL_PTR;
    NAS_MML_GMM_PROC_INFO_STRU         *pstGmmProcInfo = VOS_NULL_PTR;

    /* ȡ�õ�ǰ��������Ϣ */
    pstConnStatus    = NAS_MML_GetConnStatus();
    pstGmmProcInfo   = NAS_MML_GetGmmProcInfo();

    /* ������rrc���ӣ�����false����Ҫ�����ͷ����� */
    if (VOS_FALSE == NAS_MML_IsRrcConnExist())
    {
        return VOS_FALSE;
    }

    /* �������csҵ�񣬷���false����Ҫ�����ͷ����� */
    if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
    {
        return VOS_FALSE;
    }

    /* �������cs��������lau���̣�����false����Ҫ�����ͷ����� */
    if (VOS_TRUE == pstConnStatus->ucCsSigConnStatusFlg)
    {
        return VOS_FALSE;
    }

    /* ���gmm��ע�����̣�����false������Ҫ�����ͷ����� */
    if ((NAS_MML_GMM_PROC_TYPE_INVALID != pstGmmProcInfo->enGmmProcType)
     && (NAS_MML_GMM_PROC_FLAG_START == pstGmmProcInfo->enGmmProcFlag))
    {
        return VOS_FALSE;
    }

    /* sm�ڽ���pdp���ȥ���modify���̣�����false������Ҫ�����ͷ����� */
    if (NAS_MML_SM_PROC_FLAG_START == NAS_MML_GetSmProcFlag())
    {
        return VOS_FALSE;
    }

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

VOS_UINT32 NAS_MMC_IsDisableLteNeedLocalReleaseEpsConn(VOS_VOID)
{
    NAS_MML_ADDITION_UPDATE_RSLT_INFO_ENUM_UINT8            enAdditionUpdateRslt;
    VOS_UINT32                                              ulCsDomainUnAvailFlg;
    MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32                  enDisableLteReason;

    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegCause;
    VOS_UINT32                                              ulAttempCounter;

    /* Attempt Counter ��ʼ��Ϊ0 */
    ulAttempCounter = 0;

    enPsRegCause = NAS_MML_REG_FAIL_CAUSE_NULL;
    enCsRegCause = NAS_MML_REG_FAIL_CAUSE_NULL;

    enAdditionUpdateRslt = NAS_MML_GetAdditionUpdateRslt();
    ulCsDomainUnAvailFlg = VOS_FALSE;
    enDisableLteReason   = NAS_MML_GetDisableLteReason();

    /* disable LTE������ԭ����IMS VOICE��������Ҫ֪ͨL�ͷ�����*/
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS  != NAS_MML_GetLteCapabilityStatus())
     || (MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE != enDisableLteReason))
    {
        return VOS_FALSE;
    }


    NAS_MMC_GetDomainRegStatusInRegInfoList( NAS_MML_GetCurrCampPlmnId(),
                                             NAS_MML_NET_RAT_TYPE_LTE,
                                             &enCsRegCause,
                                             &enPsRegCause );

    /* ��ȡL�µĳ��Դ���*/
    ulAttempCounter = NAS_MMC_GetRegRsltAttemptCounter(NAS_MMC_GetRegRsltType());

    /* EPS only �ɹ���#16,#17,#22��Ҫdisable lteʱ�����ͷ�����*/
    if ((NAS_MML_REG_FAIL_CAUSE_NULL == enPsRegCause)
     && (NAS_MML_MAX_PS_REG_FAIL_CNT <= ulAttempCounter))
    {
        if (NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE == enCsRegCause)
        {
            return NAS_MMC_IsNeedDisableL_RegFailCause16AttmptCntMaxTimes();
        }

        if (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE == enCsRegCause)
        {
            return NAS_MMC_IsNeedDisableL_RegFailCause17AttmptCntMaxTimes();
        }

        if (NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION == enCsRegCause)
        {
            return NAS_MMC_IsNeedDisableL_RegFailCause22AttmptCntMaxTimes();
        }

        return VOS_TRUE;
    }

    /*�Ƿ���#18�б���*/
    ulCsDomainUnAvailFlg = NAS_MML_IsPlmnIdInCsDomainUnAvailPlmnList(NAS_MML_GetCurrCampPlmnId());

    /* ��#18�б��У�SMS ONLY ,CSFB NOT PREFERRED��Ҫ֪ͨL�ͷ�����*/
    if ((VOS_TRUE == NAS_MMC_IsNeedDisableL_CombinedRegSuccAdditionUpdateRslt(enAdditionUpdateRslt))
     || (VOS_TRUE == ulCsDomainUnAvailFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


#endif


VOS_UINT32 NAS_MMC_IsPlmnMccSameWithRplmn(
    VOS_UINT32                          ulMcc
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRPlmnCfg  = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stRPlmnId;
    VOS_UINT32                          i;

    PS_MEM_SET(&stRPlmnId, 0, sizeof(stRPlmnId));
    i = 0;

    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    /* ��ȡRPLMN������Ϣ */
    pstRPlmnCfg = NAS_MML_GetRplmnCfg();

    /* ������֧�ֽ��뼼����rplmn��mcc�Ƚ�,��Ϊ��rplmn���Կ���ʱ��gul��rplmn���ܻ᲻ͬ,
       �����rplmn���Թرգ���ֻ����ǰ���뼼��rplmn mcc�Ƚϣ���Ϊ��ʹ�ǵ�rplmn������Ҳ����gu��rplmn��lte�²�ͬ�ĳ���*/
    if (VOS_FALSE == pstRPlmnCfg->ucMultiRATRplmnFlg)
    {
        if (VOS_FALSE == NAS_MMC_GetRPlmn_PlmnSelectionStrategy(NAS_MML_GetLastRplmnRat(), &stRPlmnId))
        {
            /* rplmn�����ڷ���false*/
            return VOS_FALSE;
        }

        if (VOS_TRUE == NAS_MML_ComparePlmnMcc(ulMcc, stRPlmnId.ulMcc))
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }

    /* ��rplmn���Կ��� */
    for (i = 0; i < pstPrioRatList->ucRatNum; i++)
    {
        if (VOS_FALSE == NAS_MMC_GetRPlmn_PlmnSelectionStrategy(pstPrioRatList->aucRatPrio[i], &stRPlmnId))
        {
            continue;
        }

        if (VOS_TRUE == NAS_MML_ComparePlmnMcc(ulMcc, stRPlmnId.ulMcc))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MMC_IsPlmnMccSameWithHplmn(
    VOS_UINT32                          ulMcc
)
{
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstEHPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                          i;

    /* ��ȡEHPLMN */
    pstEHPlmnInfo = NAS_MML_GetSimEhplmnList();

    for (i = 0; i < pstEHPlmnInfo->ucEhPlmnNum; i++)
    {
        if (VOS_TRUE == NAS_MML_ComparePlmnMcc(ulMcc,
                             pstEHPlmnInfo->astEhPlmnInfo[i].stPlmnId.ulMcc))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
VOS_VOID  NAS_MMC_GetMccListInRrcPlmnIdList(
    VOS_UINT32                         *pulMccNum,
    VOS_UINT32                         *pulMccList,
    RRC_PLMN_ID_LIST_STRU              *pstRrcPlmnIdList
)
{
    VOS_UINT32                          i;

    *pulMccNum = 0;

    if (pstRrcPlmnIdList->ulHighPlmnNum > RRC_MAX_HIGH_PLMN_NUM)
    {
        pstRrcPlmnIdList->ulHighPlmnNum = RRC_MAX_HIGH_PLMN_NUM;
    }

    /* �������������� */
    for (i = 0; i < pstRrcPlmnIdList->ulHighPlmnNum; i++)
    {
        /*lint -e961*/
        pulMccList[(*pulMccNum)++]= pstRrcPlmnIdList->aHighPlmnList[i].stPlmnId.ulMcc;
        /*lint +e961*/
    }

    if (pstRrcPlmnIdList->ulLowPlmnNum > RRC_MAX_LOW_PLMN_NUM)
    {
        pstRrcPlmnIdList->ulLowPlmnNum = RRC_MAX_LOW_PLMN_NUM;
    }

    /* �������������� */
    for (i = 0; i < pstRrcPlmnIdList->ulLowPlmnNum; i++)
    {
        /*lint -e961*/
        pulMccList[(*pulMccNum)++] = pstRrcPlmnIdList->aLowPlmnList[i].PlmnId.stPlmnId.ulMcc;
        /*lint +e961*/

    }
}


VOS_VOID  NAS_MMC_DelPlmnSelectionRatInfoInPlmnWithRatList (
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmn,
    VOS_UINT32                                              ulPlmnNum,
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstPlmnIdList
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           j;

    /* ���б��в���ָ����PLMN�Ľ��뼼�� */
    for (i = 0; i < ulPlmnNum; i++)
    {
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstPlmnIdList[i].stPlmnId),
                                                            &(pstPlmn->stPlmnId)))
        {
            j = 0;

            while ( j < (pstPlmn->ucRatNum) )
            {
                if (pstPlmnIdList[i].enRat == pstPlmn->astPlmnRatInfo[j].enRatType)
                {
                    if (j < (pstPlmn->ucRatNum - 1))
                    {

                        /*lint -e961*/
                        (VOS_VOID)PS_MEM_MOVE(&(pstPlmn->astPlmnRatInfo[j]),
                                    &(pstPlmn->astPlmnRatInfo[j + 1]),
                                    (NAS_MML_MAX_RAT_NUM - j - 1) * sizeof(NAS_MMC_PLMN_RAT_INFO_STRU));
                        /*lint +e961*/
                    }

                    (pstPlmn->ucRatNum)--;

                    continue;
                }

                j++;
            }
        }
    }

    return;
}


#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID  NAS_MMC_SndEnableLteNotify(VOS_VOID)
{
    /* ��WAS/GAS����enable LTE֪ͨ��Ϣ */
    NAS_MMC_SndAsLteCapabilityStatus(WUEPS_PID_WRR, RRC_NAS_LTE_CAPABILITY_STATUS_REENABLE);
    NAS_MMC_SndAsLteCapabilityStatus(UEPS_PID_GAS, RRC_NAS_LTE_CAPABILITY_STATUS_REENABLE);

    /* ��LMM����enable LTE��Ϣ */
    NAS_MMC_SndLmmEnableLteNotify();
    return;
}


VOS_VOID  NAS_MMC_SndDisableLteNotify(
    MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32                  enDisableLteReason
)
{
    /* ��WAS/GAS����disable LTE֪ͨ��Ϣ */
    NAS_MMC_SndAsLteCapabilityStatus(WUEPS_PID_WRR, RRC_NAS_LTE_CAPABILITY_STATUS_DISABLE);
    NAS_MMC_SndAsLteCapabilityStatus(UEPS_PID_GAS, RRC_NAS_LTE_CAPABILITY_STATUS_DISABLE);

    /* ��LMM����disable LTE��Ϣ */
    NAS_MMC_SndLmmDisableLteNotify(enDisableLteReason);
    return;
}

#endif


VOS_VOID  NAS_MMC_DelPlmnSelectionRatInfoInDisabledPlmnWithForbiddenPeriodList (
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmn,
    VOS_UINT32                                              ulPlmnNum,
    NAS_MML_DISABLED_PLMN_WITH_FORBIDDEN_PERIOD_STRU       *pstPlmnIdList
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           j;
    VOS_UINT32                          ulIndex;

    ulIndex = ulPlmnNum;

    if (ulIndex > NAS_MML_MAX_DISABLED_RAT_PLMN_NUM)
    {
        ulIndex = NAS_MML_MAX_DISABLED_RAT_PLMN_NUM;
    }

    /* ���б��в���ָ����PLMN�Ľ��뼼�� */
    for (i = 0; i < ulIndex; i++)
    {
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstPlmnIdList[i].stPlmnWithRat.stPlmnId),
                                                            &(pstPlmn->stPlmnId)))
        {
            j = 0;

            while ( j < (pstPlmn->ucRatNum) )
            {
                if (pstPlmnIdList[i].stPlmnWithRat.enRat == pstPlmn->astPlmnRatInfo[j].enRatType)
                {
                    if (j < (pstPlmn->ucRatNum - 1))
                    {

                        /*lint -e961*/
                        (VOS_VOID)PS_MEM_MOVE(&(pstPlmn->astPlmnRatInfo[j]),
                                    &(pstPlmn->astPlmnRatInfo[j + 1]),
                                    (NAS_MML_MAX_RAT_NUM - j - 1) * sizeof(NAS_MMC_PLMN_RAT_INFO_STRU));
                        /*lint +e961*/
                    }

                    (pstPlmn->ucRatNum)--;

                    continue;
                }

                j++;
            }
        }
    }

    return;
}
VOS_VOID  NAS_MMC_DeleteForbiddenRatInPlmnSeleInfo (
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU *pstPlmn
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    NAS_MML_RAT_FORBIDDEN_LIST_STRU    *pstRatBlackList = VOS_NULL_PTR;

    i               = 0;
    j               = 0;
    pstRatBlackList = NAS_MML_GetRatForbiddenListCfg();

    /* ���IMSI���ں������У��򷵻� */
    if (VOS_FALSE == NAS_MML_GetImsiInForbiddenListFlg())
    {
        return;
    }

    /* ���IMSI�ں������У���Ҫ�������б��н�NV�����ý�ֹ��RAT��ɾ�� */
    for (i = 0; i < pstRatBlackList->ucForbidRatNum; i++)
    {
        j = 0;
        while ( j < NAS_MML_MIN((pstPlmn->ucRatNum),NAS_MML_MAX_RAT_NUM) )
        {
            if (pstRatBlackList->aenForbidRatList[i] == pstPlmn->astPlmnRatInfo[j].enRatType)
            {
                if ( (j + 1) < (pstPlmn->ucRatNum) )
                {
                    /*lint -e961*/
                    (VOS_VOID)PS_MEM_MOVE(&(pstPlmn->astPlmnRatInfo[j]),
                                &(pstPlmn->astPlmnRatInfo[j + 1]),
                                (NAS_MML_MAX_RAT_NUM - j - 1) * sizeof(NAS_MMC_PLMN_RAT_INFO_STRU));
                    /*lint +e961*/
                }

                (pstPlmn->ucRatNum)--;

                continue;
            }

            j++;
        }
    }

    return;
}


VOS_VOID NAS_MMC_AddPlmnListIntoSimEhplmnInfo(
    VOS_UINT32                          ulPlmnListNum,
    NAS_MML_PLMN_ID_STRU               *pstPlmnList,
    NAS_MMC_PLMN_TYPE_ENUM_UINT8        enSpecPlmnType,
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstEhplmnInfo
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           ucTempSimEhplmnListNum;
    NAS_MML_PLMN_ID_STRU                astTempEhplmnList[NAS_MML_MAX_EHPLMN_NUM];

    /* ��SIM�е�EHplmn������ʱ��EHplmn LIST���棬���ں�����бȽϵ�ǰ�����Ƿ���EHPLMN LIST ���� */
    for ( i = 0 ; i < pstEhplmnInfo->ucEhPlmnNum; i++ )
    {
        astTempEhplmnList[i] = pstEhplmnInfo->astEhPlmnInfo[i].stPlmnId;
    }
    ucTempSimEhplmnListNum = pstEhplmnInfo->ucEhPlmnNum;

    for ( i = 0 ; i < ulPlmnListNum; i++ )
    {
        /* �����ǰ��SIM Ehplmn LIST�������������������� */
        if ( NAS_MML_MAX_EHPLMN_NUM <= pstEhplmnInfo->ucEhPlmnNum )
        {
            return;
        }

        /* �����ǰ��������SIM Ehplmn LIST���棬����� */
        if ( VOS_TRUE == NAS_MMC_IsSpecTypePlmnIdInDestPlmnList( &pstPlmnList[i],
                                                                 enSpecPlmnType,
                                                                 ucTempSimEhplmnListNum,
                                                                 astTempEhplmnList) )
        {
            continue;
        }

        /* ��PLMN ID���뵽SIM Ehplmn LIST���� */
        pstEhplmnInfo->astEhPlmnInfo[pstEhplmnInfo->ucEhPlmnNum].stPlmnId = pstPlmnList[i];
        pstEhplmnInfo->ucEhPlmnNum++;

        /* ��PLMN ID���뵽��ʱ��SIM Ehplmn LIST���� */
        astTempEhplmnList[ucTempSimEhplmnListNum] = pstPlmnList[i];
        ucTempSimEhplmnListNum++;
    }

    return ;
}
VOS_UINT32  NAS_MMC_IsCurrentWcdmaMode(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    enRatType       = NAS_MML_GetCurrNetRatType();

    if ((NAS_UTRANCTRL_UTRAN_MODE_FDD   == NAS_UTRANCTRL_GetCurrUtranMode())
     && (NAS_MML_NET_RAT_TYPE_WCDMA     == enRatType))
    {
        return VOS_TRUE;
    }

    /* �����������VOS_FALSE */
    return VOS_FALSE;
}
VOS_UINT32  NAS_MMC_IsCurrentTdscdmaMode(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    enRatType       = NAS_MML_GetCurrNetRatType();

    if ((NAS_UTRANCTRL_UTRAN_MODE_TDD   == NAS_UTRANCTRL_GetCurrUtranMode())
     && (NAS_MML_NET_RAT_TYPE_WCDMA     == enRatType))
    {
        return VOS_TRUE;
    }

    /* �����������VOS_FALSE */
    return VOS_FALSE;
}
VOS_UINT32 NAS_MMC_IsNetRatSupportedTdscdma(VOS_VOID)
{
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode;

    enUtranMode  = NAS_UTRANCTRL_GetCurrUtranMode();

    if ((VOS_TRUE                     == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_WCDMA))
     && (NAS_UTRANCTRL_UTRAN_MODE_TDD == enUtranMode))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


#if (FEATURE_ON == FEATURE_LTE)


VOS_UINT32  NAS_MMC_IsEpsEmergencyAttachType(
    MMC_LMM_ATTACH_TYPE_ENUM_UINT32     ulReqType
)
{
    if (MMC_LMM_ATT_TYPE_EPS_EMERGENCY == ulReqType)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_VOID  NAS_MMC_DelForbInfo_LmmAttRsltSucc(
    MMC_LMM_LAI_STRU                   *pstLmmLai,
    VOS_UINT32                          ulEpsEmergencyAttachFlag
)
{
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbPlmnInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstPlmn         = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                    stForbLai;

    /* ���ڻ�ȡ��ֹLA����Ϣ */
    pstForbPlmnInfo     = NAS_MML_GetForbidPlmnInfo();
    pstPlmn             = NAS_MML_GetCurrCampPlmnId();
    PS_MEM_SET(&stForbLai, 0, sizeof(NAS_MML_LAI_STRU));

    /* �����ڽ���PDN���ӣ��Ҳ���Ϊ�������ص�attach,ע��ɹ�ֱ��ɾ����ֹPLMN��Ϣ,����Ҫ�ж��Ƿ�Ϊָ������,���֮ǰPS���CS��ע��
       �ӵ���ֹ�б�,ֻ����ָ������ʱ�Żᷢ��CS/PS��ע��,ע��ɹ������ֱ��ɾ����ֹ��Ϣ */
    if ((VOS_FALSE == NAS_MML_GetEmcPdpStatusFlg())
     && (VOS_FALSE == ulEpsEmergencyAttachFlag))
    {
        if (VOS_TRUE ==  NAS_MML_DelForbPlmn(pstPlmn))
        {
            NAS_MMC_SndUsimUpdateForbPlmnReq();
        }

        NAS_MML_DelForbGprsPlmn(pstPlmn);
    }

    /* pstLmmLaiΪ��Чֵʱ������Ҫɾ��ForbLai */
    if (VOS_NULL_PTR == pstLmmLai)
    {
        return;
    }

    /* ��LMM��LAת����NAS��LA */
    NAS_MMC_ConvertLmmPlmnToGUNasFormat(&(pstLmmLai->stPlmnId), &(stForbLai.stPlmnId));
    stForbLai.aucLac[0]   = pstLmmLai->stLac.ucLac;
    stForbLai.aucLac[1]   = pstLmmLai->stLac.ucLacCnt;

    /* ���뼼��ΪLʱ��LAI��ATTACH_IND��Ϣ�д���LAI�������õ�ǰפ����LAI */
    /* Modified by z00359541 for CS REG FAIL FORB LA, 2015-9-23, begin */
    (VOS_VOID)NAS_MML_DelForbLa(&stForbLai, NAS_MML_REG_DOMAIN_CS);
    /* Modified by z00359541 for CS REG FAIL FORB LA, 2015-9-23, end */

    /* ��ֹForbidden LA Ϊ�գ���ֹͣ Forbidden LA TImer */
    if ( ( 0 == pstForbPlmnInfo->ucForbRegLaNum )
      && ( 0 == pstForbPlmnInfo->ucForbRoamLaNum ) )
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_FORBID_LA_TIMER);
    }

}


VOS_UINT32 NAS_MMC_IsLmmAttachCnfTriggerPlmnSrch(
    LMM_MMC_ATTACH_CNF_STRU            *pstLmmAttachCnf
)
{
    if ( NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER) )
    {
        return VOS_FALSE;
    }

    /* ��ǰ�Ѿ�����������������Ҫ�������� */
    if ( VOS_TRUE == NAS_MMC_IsNormalServiceStatus() )
    {
        return VOS_FALSE;
    }

    /* ��ǰ���뼼����֧��W/G������Ҫ���� */
    if ( VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()) )
    {
        return VOS_FALSE;
    }

    switch ( pstLmmAttachCnf->ulAttachRslt)
    {
        /* ���Դ������� */
        case MMC_LMM_ATT_RSLT_FAILURE :
        case MMC_LMM_ATT_RSLT_FORBID_PLMN :
        case MMC_LMM_ATT_RSLT_FORBID_PLMN_FOR_GPRS :
        case MMC_LMM_ATT_RSLT_FORBID_TA_FOR_ROAMING :
        case MMC_LMM_ATT_RSLT_FORBID_TA_FOR_RPOS :

            return VOS_TRUE;

        default:
            return VOS_FALSE;
    }

}

#endif


VOS_VOID  NAS_MMC_DelForbInfo_GuRegRsltSucc(
    NAS_MMC_REG_DOMAIN_ENUM_UINT8       enDomain
)
{
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbPlmnInfo = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                   *pstLai          = VOS_NULL_PTR;

    /* ���ڻ�ȡ��ֹLA����Ϣ */
    pstForbPlmnInfo     = NAS_MML_GetForbidPlmnInfo();
    pstLai              = NAS_MML_GetCurrCampLai();

    /* ע��ɹ�ֱ��ɾ����ֹPLMN��Ϣ,����Ҫ�ж��Ƿ�Ϊָ������,���֮ǰPS���CS��ע��
       �ӵ���ֹ�б�,ֻ����ָ������ʱ�Żᷢ��CS/PS��ע��,ע��ɹ������ֱ��ɾ����ֹ��Ϣ */
    if (VOS_TRUE ==  NAS_MML_DelForbPlmn(&(pstLai->stPlmnId)))
    {
        NAS_MMC_SndUsimUpdateForbPlmnReq();
    }

    if (NAS_MMC_REG_DOMAIN_CS != enDomain)
    {
        NAS_MML_DelForbGprsPlmn(&(pstLai->stPlmnId));
    }

    /* ��ȡCS PS��ע��ԭ��ֵ */

    /* ���һ�����Ѿ���#12��13��#15�ܣ���һ����ע��ɹ���Ҫɾ��ForbLai */


    /* Modified by z00359541 for CS REG FAIL FORB LA, 2015-9-23, begin */
    if (VOS_TRUE == NAS_MML_DelForbLa(pstLai, enDomain))
    /* Modified by z00359541 for CS REG FAIL FORB LA, 2015-9-23, end */
    {
        NAS_MMC_SndRrMmCellSelReq(RRC_NAS_FORBLA_CHANGE);
    }

    /* ��ֹForbidden LA Ϊ�գ���ֹͣ Forbidden LA TImer */
    if ( ( 0 == pstForbPlmnInfo->ucForbRegLaNum )
      && ( 0 == pstForbPlmnInfo->ucForbRoamLaNum ) )
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_FORBID_LA_TIMER);
    }
}


#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32  NAS_MMC_GetLteInfo(
    NAS_LMM_INFO_TYPE_ENUM_UINT32       ulInfoType,
    NAS_LMM_INFO_STRU                  *pstLmmInfo
)
{
    /* ƽ̨��֧��LTE */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        return VOS_FALSE;
    }

    /* ����LNAS�ṩ�ӿں������ɹ�����VOS_OK */
    if (MMC_LMM_SUCC == Nas_GetLteInfo(ulInfoType, pstLmmInfo))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
#endif


VOS_VOID  NAS_MMC_ChangeCsRegState(
    NAS_MML_REG_STATUS_ENUM_UINT8       ucCsRegState
)
{
    NAS_MML_REG_STATUS_ENUM_UINT8       ucOldRegState;

    ucOldRegState = NAS_MML_GetCsRegStatus();

    /*normal ע��״̬�������ϱ�*/
    if ((ucCsRegState == ucOldRegState)
     && (NAS_MML_REG_REGISTERED_HOME_NETWORK != ucCsRegState)
     && (NAS_MML_REG_REGISTERED_ROAM != ucCsRegState))
    {
        return;
    }

    NAS_MMC_ErrLogRecordCsOosCause(ucOldRegState, ucCsRegState);
    NAS_MMC_ErrLogClrNwSearchCount(ucOldRegState, ucCsRegState);

    /* ����CSע��״̬ */
    NAS_MML_SetCsRegStatus(ucCsRegState);

    /* �ϱ�ע��״̬�����ı� */
    NAS_MMC_SndMsccRegStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS, ucCsRegState);

    return;
}
VOS_VOID  NAS_MMC_ChangePsRegState(
    NAS_MML_REG_STATUS_ENUM_UINT8       ucPsRegState
)
{
    NAS_MML_REG_STATUS_ENUM_UINT8       ucOldRegState;

    ucOldRegState = NAS_MML_GetPsRegStatus();

    /*normal ע��״̬�������ϱ�*/
    if((ucPsRegState == ucOldRegState)
    && (NAS_MML_REG_REGISTERED_HOME_NETWORK != ucPsRegState)
    && (NAS_MML_REG_REGISTERED_ROAM != ucPsRegState))
    {
        return;
    }

    NAS_MMC_ErrLogRecordPsOosCause(ucOldRegState, ucPsRegState);
    NAS_MMC_ErrLogClrNwSearchCount(ucOldRegState, ucPsRegState);

    /* Deleted by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin */
    /*ѡ����Anycell����ʱ���ϱ�LTE��ע��״̬*/
    /* Deleted by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, end */

    /* ����PSע��״̬ */
    NAS_MML_SetPsRegStatus(ucPsRegState);

    /* �ϱ�ע��״̬�����ı� */
    NAS_MMC_SndMsccRegStatusInd(NAS_MSCC_PIF_SRVDOMAIN_PS, ucPsRegState);

    return;
}


VOS_VOID  NAS_MMC_UpdateRegStateSpecPlmnSearch(VOS_VOID)
{
    /* ����޿�ע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus())
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

        return;
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* ����CSFBҵ�񲻸���CSPSע��״̬ */
    if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
    {
        return;
    }
#endif

    /* ���CS����Ч����CSע��״̬ΪNAS_MML_REG_REGISTERED_DENIED */
    if (VOS_FALSE == NAS_MML_GetSimCsRegStatus())
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
    }
    /* ���CS������ע�����CSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    else if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }
    else
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    }

    /* ���PS����Ч����PSע��״̬ΪNAS_MML_REG_REGISTERED_DENIED */
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    }
    /* ���PS������ע�����PSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    else if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }
    else
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    }

    return;
}


VOS_VOID  NAS_MMC_UpdateRegStateAnyCellSearchSucc(VOS_VOID)
{
    NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8                  enSelectionMode;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstUserSpecPlmnId = VOS_NULL_PTR;
    VOS_UINT32                                              ulForbPlmnFlag;
    VOS_UINT8                                               ucUpdateRegStaFlg;
#if   (FEATURE_ON == FEATURE_LTE)
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbidPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulRet;
    VOS_UINT32                                              ulLteOnlyFlg;
#endif

    ucUpdateRegStaFlg = VOS_FALSE;

    /* ��ʱ����������,һ��Ҫ����ע��״̬ */
    if (NAS_MMC_TIMER_STATUS_STOP == NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER))
    {
        ucUpdateRegStaFlg = VOS_TRUE;
    }
    else
    {
        enSelectionMode   = NAS_MMC_GetPlmnSelectionMode();
        pstUserSpecPlmnId = NAS_MMC_GetUserSpecPlmnId();
        ulForbPlmnFlag    = NAS_MML_IsPlmnIdInForbidPlmnList( &(pstUserSpecPlmnId->stPlmnId) );

        /* ��ǰΪ�ֶ�ģʽ���û�ָ���������ڽ�ֹ�����б�����Ҫ����ע��״̬ */
        if ((NAS_MMC_PLMN_SELECTION_MODE_MANUAL == enSelectionMode)
         && (VOS_TRUE                           == ulForbPlmnFlag))
        {
            ucUpdateRegStaFlg = VOS_TRUE;
        }

#if   (FEATURE_ON == FEATURE_LTE)
        ulLteOnlyFlg        = NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList());
        pstForbidPlmnInfo   = NAS_MML_GetForbidPlmnInfo();

        ulRet = NAS_MML_IsSimPlmnIdInDestBcchPlmnList(&(pstUserSpecPlmnId->stPlmnId),
                                                  pstForbidPlmnInfo->ucForbGprsPlmnNum,
                                                  pstForbidPlmnInfo->astForbGprsPlmnList);

        /* LTE ONLY�ֶ�ģʽ���û�ָ���������ڽ�ֹGPRS�б���,��Ҫ����ע��״̬ */
        if ((NAS_MMC_PLMN_SELECTION_MODE_MANUAL == enSelectionMode)
         && (VOS_TRUE == ulLteOnlyFlg)
         && (VOS_TRUE == ulRet))
        {
            ucUpdateRegStaFlg = VOS_TRUE;
        }
#endif
    }

    if (VOS_FALSE == ucUpdateRegStaFlg)
    {
        return;
    }

    /* ����޿�ע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus())
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

        return;
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* ����CSFBҵ�񲻸���CSPSע��״̬ */
    if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
    {
        return;
    }
#endif

    /* ���CS����Ч����CSע��״̬ΪNAS_MML_REG_REGISTERED_DENIED */
    if (VOS_FALSE == NAS_MML_GetSimCsRegStatus())
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
    }
    /* ����CSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    else
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }

    /* ���PS����Ч����PSע��״̬ΪNAS_MML_REG_REGISTERED_DENIED */
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    }
    /* ����PSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    else
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }

    return;
}
VOS_VOID  NAS_MMC_UpdateCsRegStateCsRegSucc(VOS_VOID)
{
    VOS_UINT8                           ucHplmnInEplmnDisplayHomeFlg;
    VOS_UINT32                          ulIsHplmnInEplmnList;

    ucHplmnInEplmnDisplayHomeFlg = NAS_MML_GetHplmnInEplmnDisplayHomeFlg();
    ulIsHplmnInEplmnList         = NAS_MML_IsHplmnInEplmnList();

    if ((VOS_FALSE == NAS_MMC_IsRoam())
     || ((VOS_TRUE == ucHplmnInEplmnDisplayHomeFlg)
      && (VOS_TRUE == ulIsHplmnInEplmnList)))
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_HOME_NETWORK);
    }
    else
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_ROAM);
    }


    return;
}


VOS_VOID  NAS_MMC_UpdatePsRegStatePsRegSucc(VOS_VOID)
{
    VOS_UINT8                           ucHplmnInEplmnDisplayHomeFlg;
    VOS_UINT32                          ulIsHplmnInEplmnList;

    ucHplmnInEplmnDisplayHomeFlg = NAS_MML_GetHplmnInEplmnDisplayHomeFlg();
    ulIsHplmnInEplmnList         = NAS_MML_IsHplmnInEplmnList();

    if ((VOS_FALSE == NAS_MMC_IsRoam())
     || ((VOS_TRUE == ucHplmnInEplmnDisplayHomeFlg)
      && (VOS_TRUE == ulIsHplmnInEplmnList)))
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_HOME_NETWORK);
    }
    else
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_ROAM);
    }

    return;
}

/*lint -save -e958 */

VOS_VOID NAS_MMC_ConvertToMsccSrvStatus(
    NAS_MMC_SERVICE_ENUM_UINT8          enMmcServiceState,
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32  *penMsccServiceState
)
{
    switch(enMmcServiceState)
    {
        case NAS_MMC_NO_SERVICE:
            *penMsccServiceState = NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE;
            break;
        case NAS_MMC_NORMAL_SERVICE:
            *penMsccServiceState = NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE;
            break;
        case NAS_MMC_LIMITED_SERVICE:
            *penMsccServiceState = NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE;
            break;
        case NAS_MMC_LIMITED_SERVICE_REGION:
            *penMsccServiceState = NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE_REGION;
            break;
        default:
            *penMsccServiceState = NAS_MSCC_PIF_SERVICE_STATUS_BUTT;
            break;
    }

    return;
}
/*lint -restore */

/*lint -save -e958 */

VOS_VOID  NAS_MMC_ChangeServiceState(
    VOS_UINT32                          ulCnDomainId,
    NAS_MMC_SERVICE_ENUM_UINT8          enServiceState
)
{

    NAS_MMC_SERVICE_INFO_CTX_STRU      *pstServiceInfo      = VOS_NULL_PTR;
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32  enMsccServiceState;



    /* Deleted by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin */
    /*ѡ����Anycell����ʱ���ϱ�LTE�ķ���״̬*/
    /* Deleted by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, end */


    pstServiceInfo =  NAS_MMC_GetServiceInfo();

    switch (ulCnDomainId)
    {
        case NAS_MSCC_PIF_SRVDOMAIN_CS:
            /* ��������ʱ������֪ͨMMA����״̬��MMA��Ҫ����������ʱ����stAppNetworkInfo
               ���������ǰ�Ѿ�����Ҫ���µ�ע��״̬����Ҫ������ */
            if ((enServiceState == pstServiceInfo->enCsCurrService)
             && (NAS_MMC_NORMAL_SERVICE != enServiceState))
            {
                return;
            }
            /* ����CS����״̬ */
            NAS_MMC_SetCsServiceStatus(enServiceState);
            break;

        case NAS_MSCC_PIF_SRVDOMAIN_PS:

            /* ��������ʱ������֪ͨMMA����״̬��MMA��Ҫ����������ʱ����stAppNetworkInfo
               ���������ǰ�Ѿ�����Ҫ���µ�ע��״̬����Ҫ������ */
            if ((enServiceState == pstServiceInfo->enPsCurrService)
             && (NAS_MMC_NORMAL_SERVICE != enServiceState))
            {
                return;
            }
            /* ����PS����״̬ */
            NAS_MMC_SetPsServiceStatus(enServiceState);
            break;

        case NAS_MSCC_PIF_SRVDOMAIN_CS_PS:
        case NAS_MSCC_PIF_SRVDOMAIN_NOT_REG_PLMN_SEARCHING:

            /* ��������ʱ������֪ͨMMA����״̬��MMA��Ҫ����������ʱ����stAppNetworkInfo
               ���������ǰ�Ѿ�����Ҫ���µ�ע��״̬����Ҫ������ */
            if ((enServiceState == pstServiceInfo->enPsCurrService)
             && (enServiceState == pstServiceInfo->enCsCurrService)
             && (NAS_MMC_NORMAL_SERVICE != enServiceState))
            {
                return;
            }

            /* ����CS����״̬ */
            NAS_MMC_SetCsServiceStatus(enServiceState);

            /* ����PS����״̬ */
            NAS_MMC_SetPsServiceStatus(enServiceState);
            break;

        default:

            NAS_ERROR_LOG(WUEPS_PID_MMC,"NAS_MMC_ChangeServiceState: domain Type Error");
            return;
    }

    NAS_MMC_ConvertToMsccSrvStatus(enServiceState, &enMsccServiceState);

    NAS_MMC_SndMsccServiceStatusInd(ulCnDomainId,  enMsccServiceState);

    return;
}
/*lint -restore */


VOS_VOID  NAS_MMC_UpdateServiceState_RegSucc(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  ulCnDomainId,
    NAS_MMC_SERVICE_ENUM_UINT8          enServiceState
)
{
    NAS_NORMAL_LOG2(WUEPS_PID_MMC,"NAS_MMC_UpdateServiceState_RegSucc entered ulCnDomainId: enServiceState:", ulCnDomainId, enServiceState);

    if (NAS_MSCC_PIF_SRVDOMAIN_PS == ulCnDomainId)
    {
        NAS_MMC_UpdatePsRegStatePsRegSucc();
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, enServiceState);
    }
    else if (NAS_MSCC_PIF_SRVDOMAIN_CS == ulCnDomainId)
    {
        NAS_MMC_UpdateCsRegStateCsRegSucc();
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, enServiceState);
    }
    else if (NAS_MSCC_PIF_SRVDOMAIN_CS_PS == ulCnDomainId)
    {
        NAS_MMC_UpdateCsRegStateCsRegSucc();
        NAS_MMC_UpdatePsRegStatePsRegSucc();
        
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, enServiceState);
    }    
    else 
    {
        /* nothing */
    }    
}



VOS_VOID  NAS_MMC_UpdateServiceStateSpecPlmnSearch(VOS_VOID)
{
    NAS_MMC_SERVICE_ENUM_UINT8          enPsServiceStatus;
    NAS_MMC_SERVICE_ENUM_UINT8          enCsServiceStatus;

    enCsServiceStatus = NAS_MMC_GetCsServiceStatus();
    enPsServiceStatus = NAS_MMC_GetPsServiceStatus();

#if (FEATURE_ON == FEATURE_LTE)
     /* ����CSFBҵ�񲻸���CSPS����״̬ */
     if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
     {
         return;
     }
#endif

     /* �ж�פ�������MCC��MNC��Ч */
    if (VOS_TRUE == NAS_MMC_IsInValidCampPlmn())
    {
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
        return;
    }

    /* �������������Ϊ���Ʒ���;�������治��-���ж�CS������attach��� */
    if( NAS_MMC_NORMAL_SERVICE == enCsServiceStatus)
    {
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS ,NAS_MMC_LIMITED_SERVICE);
    }

    if( NAS_MMC_NORMAL_SERVICE == enPsServiceStatus)
    {
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS,NAS_MMC_LIMITED_SERVICE);
    }

    return;
}
NAS_MML_MS_MODE_ENUM_UINT8  NAS_MMC_ConvertMsccMsModeToMmlMsMode(
    NAS_MSCC_PIF_MS_MODE_ENUM_UINT32    enMsccMsMode
)
{
    NAS_MML_MS_MODE_ENUM_UINT8          enMmlMsMode;

    /* ��ʼ��ΪNAS_MML_MS_MODE_BUTT */
    enMmlMsMode = NAS_MML_MS_MODE_BUTT;

    switch (enMsccMsMode)
    {
        case NAS_MSCC_PIF_MS_MODE_A:

            enMmlMsMode = NAS_MML_MS_MODE_PS_CS;
            break;

        case NAS_MSCC_PIF_MS_MODE_CG:

            enMmlMsMode = NAS_MML_MS_MODE_PS_ONLY;
            break;

        case NAS_MSCC_PIF_MS_MODE_CC:

            enMmlMsMode = NAS_MML_MS_MODE_CS_ONLY;
            break;

        default:

            NAS_ERROR_LOG(WUEPS_PID_MMC,"NAS_MML_ConvertMsccMsModeToMmlMsMode: Ms Mode Type Error");
    }

    return enMmlMsMode;

}
NAS_MMC_CS_DOMAIN_CAPA_CHANGE_TYPE_ENUM_UINT8  NAS_MMC_GetCsDomainCapaChangeType(
    NAS_MML_MS_MODE_ENUM_UINT8          enOldMsMode,
    NAS_MML_MS_MODE_ENUM_UINT8          enNewMsMode
)
{
    VOS_UINT32                          ulOldCsAvailFlg;
    VOS_UINT32                          ulNewCsAvailFlg;

    ulOldCsAvailFlg = NAS_MML_IsCsServDomainAvail(enOldMsMode);
    ulNewCsAvailFlg = NAS_MML_IsCsServDomainAvail(enNewMsMode);

    /* �ɵ�CS���������µ���ͬʱ���ޱ仯 */
    if (ulOldCsAvailFlg == ulNewCsAvailFlg)
    {
        return NAS_MMC_CS_DOMAIN_CAPA_NO_CHANGE;
    }

    /* �ɵ�CS���������ã��µ�CS������������ */
    if ( (VOS_TRUE  == ulOldCsAvailFlg)
      && (VOS_FALSE == ulNewCsAvailFlg) )
    {
        return NAS_MMC_CS_DOMAIN_CAPA_AVAIL_TO_UNAVAIL;
    }

    /* �ɵ�CS�����������ã��µ�CS���������� */
    return NAS_MMC_CS_DOMAIN_CAPA_UNAVAIL_TO_AVAIL;

}


VOS_VOID NAS_MMC_DelForbPlmnFromAsSrchedPlmnList(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    *pstSrchedPlmn
)
{
    VOS_UINT32                                              ulPlmnCnt;
    VOS_UINT32                                              ulRatCnt;

    /* ɾ����ֹ��PLMN��Ϣ */
    for (ulRatCnt = 0; ulRatCnt < NAS_MML_MAX_RAT_NUM; ulRatCnt++)
    {
        for (ulPlmnCnt = 0; ulPlmnCnt < pstSrchedPlmn[ulRatCnt].ulHighPlmnNum; )
        {
            if (VOS_TRUE == NAS_MML_IsPlmnIdInForbidPlmnList(&(pstSrchedPlmn[ulRatCnt].astHighPlmnList[ulPlmnCnt])))
            {
                (VOS_VOID)PS_MEM_MOVE(&(pstSrchedPlmn[ulRatCnt].astHighPlmnList[ulPlmnCnt]),
                    &(pstSrchedPlmn[ulRatCnt].astHighPlmnList[ulPlmnCnt + 1]),
                    (pstSrchedPlmn[ulRatCnt].ulHighPlmnNum - (ulPlmnCnt + 1)) * sizeof(NAS_MML_PLMN_ID_STRU));

                pstSrchedPlmn[ulRatCnt].ulHighPlmnNum--;
            }
            else
            {
                ulPlmnCnt++;
            }
        }

        for (ulPlmnCnt = 0; ulPlmnCnt < pstSrchedPlmn[ulRatCnt].ulLowPlmnNum; )
        {
            if (VOS_TRUE == NAS_MML_IsPlmnIdInForbidPlmnList(&(pstSrchedPlmn[ulRatCnt].astLowPlmnList[ulPlmnCnt].stPlmnId)))
            {
                (VOS_VOID)PS_MEM_MOVE(&(pstSrchedPlmn[ulRatCnt].astLowPlmnList[ulPlmnCnt]),
                    &(pstSrchedPlmn[ulRatCnt].astLowPlmnList[ulPlmnCnt + 1]),
                    (pstSrchedPlmn[ulRatCnt].ulLowPlmnNum - (ulPlmnCnt + 1)) * sizeof(NAS_MMC_LOW_PLMN_INFO_STRU));

                pstSrchedPlmn[ulRatCnt].ulLowPlmnNum--;
            }
            else
            {
                ulPlmnCnt++;
            }
        }
    }

}
VOS_VOID NAS_MMC_DelNotUserSpecPlmnFromSrchedPlmnList(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSrchedPlmn
)
{
    VOS_UINT32                                              ulPlmnCnt;
    VOS_UINT32                                              ulRatCnt;
    VOS_UINT32                                              ulEplmnValidFlg;
    NAS_MML_EQUPLMN_INFO_STRU                              *pEplmnAddr  = VOS_NULL_PTR;

    pEplmnAddr = NAS_MML_GetEquPlmnList();
    ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL != NAS_MMC_GetPlmnSelectionMode())
    {
        return;
    }

    /* �ֶ�����ģʽ��,ɾ�����û�ָ����PLMN��Ϣ */
    for (ulRatCnt = 0; ulRatCnt < NAS_MML_MAX_RAT_NUM; ulRatCnt++)
    {
        if ((VOS_TRUE != NAS_MMC_GetUserSpecPlmnRegisterStatus())
         || (VOS_TRUE != ulEplmnValidFlg))
        {
            /* EPLMN��Ч�������Ŀǰ������ */
            pstSrchedPlmn[ulRatCnt].ulHighPlmnNum = 0;

            /* EPLMN��Ч�������Ŀǰ������ */
            pstSrchedPlmn[ulRatCnt].ulLowPlmnNum  = 0;

            continue;
        }

        for (ulPlmnCnt = 0; ulPlmnCnt < pstSrchedPlmn[ulRatCnt].ulHighPlmnNum; )
        {
            if (VOS_FALSE == NAS_MML_IsSimPlmnIdInDestBcchPlmnList(&(pstSrchedPlmn[ulRatCnt].astHighPlmnList[ulPlmnCnt]),
                                        pEplmnAddr->ucEquPlmnNum,
                                        pEplmnAddr->astEquPlmnAddr))
            {
                (VOS_VOID)PS_MEM_MOVE(&(pstSrchedPlmn[ulRatCnt].astHighPlmnList[ulPlmnCnt]),
                    &(pstSrchedPlmn[ulRatCnt].astHighPlmnList[ulPlmnCnt + 1]),
                    (pstSrchedPlmn[ulRatCnt].ulHighPlmnNum - (ulPlmnCnt + 1)) * sizeof(NAS_MML_PLMN_ID_STRU));

                pstSrchedPlmn[ulRatCnt].ulHighPlmnNum--;
            }
            else
            {
                ulPlmnCnt++;
            }
        }

        for (ulPlmnCnt = 0; ulPlmnCnt < pstSrchedPlmn[ulRatCnt].ulLowPlmnNum; )
        {
            if (VOS_FALSE == NAS_MML_IsSimPlmnIdInDestBcchPlmnList(&(pstSrchedPlmn[ulRatCnt].astLowPlmnList[ulPlmnCnt].stPlmnId),
                                        pEplmnAddr->ucEquPlmnNum,
                                        pEplmnAddr->astEquPlmnAddr))
            {
                (VOS_VOID)PS_MEM_MOVE(&(pstSrchedPlmn[ulRatCnt].astLowPlmnList[ulPlmnCnt]),
                    &(pstSrchedPlmn[ulRatCnt].astLowPlmnList[ulPlmnCnt + 1]),
                    (pstSrchedPlmn[ulRatCnt].ulLowPlmnNum - (ulPlmnCnt + 1)) * sizeof(NAS_MMC_LOW_PLMN_INFO_STRU));

                pstSrchedPlmn[ulRatCnt].ulLowPlmnNum--;
            }
            else
            {
                ulPlmnCnt++;
            }
        }
    }
}
VOS_VOID NAS_MMC_InitSearchedPlmnListInfo(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstListInfo
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT32                                              k;

    if (VOS_NULL_PTR == pstListInfo)
    {
        return;
    }

    for ( i = 0; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        pstListInfo[i].enRatType        = NAS_MML_NET_RAT_TYPE_BUTT;
        pstListInfo[i].ulHighPlmnNum    = 0;
        pstListInfo[i].ulLowPlmnNum     = 0;
        pstListInfo[i].enCoverType      = NAS_MMC_COVERAGE_TYPE_BUTT;

        /* �����ȼ��б� */
        for ( j = 0; j < NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM; j++ )
        {
            pstListInfo[i].astHighPlmnList[j].ulMcc = NAS_MML_INVALID_MCC;
            pstListInfo[i].astHighPlmnList[j].ulMnc = NAS_MML_INVALID_MNC;
        }

        /* �����ȼ��б� */
        for ( k = 0; k < NAS_MMC_INTRA_MAX_LOW_QUALITY_PLMN_NUM; k++)
        {
            pstListInfo[i].astLowPlmnList[k].stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
            pstListInfo[i].astLowPlmnList[k].stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
            pstListInfo[i].astLowPlmnList[k].lRscp          = NAS_MML_UTRA_RSCP_UNVALID;
        }
    }
}
VOS_VOID NAS_MMC_UpdateSearchedPlmnListInfo(
    RRC_PLMN_ID_LIST_STRU                                  *pstRrcList,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstListInfo
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatPrioList   = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    if ((VOS_NULL_PTR == pstRrcList)
     || (VOS_NULL_PTR == pstListInfo))
    {
        return;
    }

    /* ��ȡ���ȼ��б� */
    pstRatPrioList      = NAS_MML_GetMsPrioRatList();

    /* ��ʼ���ϱ��Ľ��뼼���б� */
    for (i =0; i< pstRatPrioList->ucRatNum; i++)
    {
        pstListInfo[i].enRatType        = pstRatPrioList->aucRatPrio[i];
        pstListInfo[i].ulHighPlmnNum    = 0;
        pstListInfo[i].ulLowPlmnNum     = 0;
    }

    /* ����������б���������Ӧ���뼼�����б� */
    for (i =0; i< pstRrcList->ulHighPlmnNum; i++)
    {
        for (j=0; j< pstRatPrioList->ucRatNum;j++)
        {
            /* ת��RRC��ʽ�Ľ��뼼�� */
            NAS_MMC_ConvertRrcRatToNasFormat(pstRrcList->aHighPlmnList[i].ulRat, &enRat);

            if ( enRat == pstListInfo[j].enRatType)
            {
                pstListInfo[j].astHighPlmnList[pstListInfo[j].ulHighPlmnNum].ulMcc
                       = pstRrcList->aHighPlmnList[i].stPlmnId.ulMcc;

                pstListInfo[j].astHighPlmnList[pstListInfo[j].ulHighPlmnNum].ulMnc
                       = pstRrcList->aHighPlmnList[i].stPlmnId.ulMnc;

                pstListInfo[j].ulHighPlmnNum ++;
            }
        }
    }

    /* ����������б���������Ӧ���뼼�����б� */
    for (i =0 ;i< pstRrcList->ulLowPlmnNum; i++)
    {
        for (j=0; j< pstRatPrioList->ucRatNum;j++)
        {
            /* ת��RRC��ʽ�Ľ��뼼�� */
            NAS_MMC_ConvertRrcRatToNasFormat(pstRrcList->aLowPlmnList[i].PlmnId.ulRat, &enRat);

            if ( enRat == pstListInfo[j].enRatType)
            {
                pstListInfo[j].astLowPlmnList[pstListInfo[j].ulLowPlmnNum].stPlmnId.ulMcc
                       = pstRrcList->aLowPlmnList[i].PlmnId.stPlmnId.ulMcc;

                pstListInfo[j].astLowPlmnList[pstListInfo[j].ulLowPlmnNum].stPlmnId.ulMnc
                       = pstRrcList->aLowPlmnList[i].PlmnId.stPlmnId.ulMnc;

                pstListInfo[j].astLowPlmnList[pstListInfo[j].ulLowPlmnNum].lRscp
                       = pstRrcList->aLowPlmnList[i].lRscp;

                pstListInfo[j].ulLowPlmnNum ++;
            }
        }
    }
}


VOS_VOID NAS_MMC_BuildEquPlmnInfo(
     NAS_MML_EQUPLMN_INFO_STRU         *pstOutEplmnInfo
)
{
    VOS_UINT32                                              ulLoop;
    VOS_UINT8                                               ucSndEplmnNum;
    NAS_MML_PLMN_ID_STRU                                   *pstCurrPlmnId = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnWithRat;
    MSCC_MMC_PLMN_ID_STRU                                   astEquPlmnAddr[NAS_MSCC_PIF_MAX_EQUPLMN_NUM];

    PS_MEM_SET(astEquPlmnAddr, 0, sizeof(astEquPlmnAddr));

    /* ��ȡ��ǰפ��������͵�Чplmn  */
    pstCurrPlmnId = NAS_MML_GetCurrCampPlmnId();
    ucSndEplmnNum = 0;
    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(stPlmnWithRat));

    /* EPLMN����ʱ */
    if (pstOutEplmnInfo->ucEquPlmnNum > 0)
    {
        for (ulLoop = 0; ulLoop < pstOutEplmnInfo->ucEquPlmnNum; ulLoop++)
        {
            if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(&(pstOutEplmnInfo->astEquPlmnAddr[ulLoop]),
                                               (VOS_UINT8)ucSndEplmnNum, astEquPlmnAddr))
            {
                continue;
            }

            if (VOS_TRUE == NAS_MML_IsPlmnIdInForbidPlmnList(&(pstOutEplmnInfo->astEquPlmnAddr[ulLoop])))
            {
                continue;
            }

            /* ��������뼼����PLMN ID */
            stPlmnWithRat.enRat         = NAS_MML_GetCurrNetRatType();
            stPlmnWithRat.stPlmnId      = pstOutEplmnInfo->astEquPlmnAddr[ulLoop];

            /* �жϵ�ЧPLMN�Ƿ��ڽ�ֹ���뼼����PLMN�б���,������򲻽���PLMN ID����RRC */
            if (VOS_TRUE == NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
            {
                continue;
            }

            astEquPlmnAddr[ucSndEplmnNum].ulMcc = pstOutEplmnInfo->astEquPlmnAddr[ulLoop].ulMcc;
            astEquPlmnAddr[ucSndEplmnNum].ulMnc = pstOutEplmnInfo->astEquPlmnAddr[ulLoop].ulMnc;

            ucSndEplmnNum++;
        }
    }
    /*Eplmn������ʱ��ֻ��ӵ�ǰ����*/
    else
    {
        if (VOS_FALSE == NAS_MML_IsPlmnIdInForbidPlmnList(pstCurrPlmnId))
        {
            astEquPlmnAddr[ucSndEplmnNum].ulMcc = pstCurrPlmnId->ulMcc;
            astEquPlmnAddr[ucSndEplmnNum].ulMnc = pstCurrPlmnId->ulMnc;

            ucSndEplmnNum++;
        }
    }


    pstOutEplmnInfo->ucEquPlmnNum = ucSndEplmnNum;
    PS_MEM_CPY(pstOutEplmnInfo->astEquPlmnAddr, astEquPlmnAddr, sizeof(pstOutEplmnInfo->astEquPlmnAddr));

    return;
}
VOS_UINT32 NAS_MMC_IsExistAvailPlmnInSearchedPlmnList(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pastIntraPlmnSrchInfo
)
{
    VOS_UINT32                                              ulRatCnt;

    if (VOS_NULL_PTR == pastIntraPlmnSrchInfo)
    {
        return VOS_FALSE;
    }

    /* �п�������,��Ҫ�������� */
    for (ulRatCnt = 0; ulRatCnt < NAS_MML_MAX_RAT_NUM; ulRatCnt++)
    {
        if ((0 != pastIntraPlmnSrchInfo[ulRatCnt].ulHighPlmnNum)
         || (0 != pastIntraPlmnSrchInfo[ulRatCnt].ulLowPlmnNum))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


#if (FEATURE_ON == FEATURE_PTM)
VOS_VOID NAS_MMC_CsRegErrRecord(MMMMC_CS_REG_RESULT_IND_STRU *pstCsRegRstInd)
{
    NAS_ERR_LOG_CS_REG_RESULT_EVENT_STRU                    stCsRegRstEvent;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulRegFailFlag;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_CS_REG_FAIL);
    ulIsLogRecord = NAS_MML_IsErrLogNeedRecord(usLevel);

    /* �ж϶�Ӧ���쳣ԭ��ֵ�Ƿ���Ҫ��¼ */
    ulRegFailFlag = NAS_MML_RegFailCauseNeedRecord(pstCsRegRstInd->enRegFailCause);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if ((VOS_FALSE == ulIsLogRecord)
     || (VOS_FALSE == ulRegFailFlag))
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_CS_REG_RESULT_EVENT_STRU);

    /* ���CSע��ʧ���쳣��Ϣ */
    PS_MEM_SET(&stCsRegRstEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stCsRegRstEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_MMC),
                                      NAS_ERR_LOG_ALM_CS_REG_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stCsRegRstEvent.ulLuResult        = pstCsRegRstInd->enLuResult;
    stCsRegRstEvent.enNetType         = pstCsRegRstInd->enNetType;
    stCsRegRstEvent.ucIsComBined      = pstCsRegRstInd->ucIsComBined;
    stCsRegRstEvent.usRegFailCause    = pstCsRegRstInd->enRegFailCause;
    stCsRegRstEvent.ulServiceStatus   = pstCsRegRstInd->ulServiceStatus;
    stCsRegRstEvent.ulCsUpdateStatus  = pstCsRegRstInd->ulCsUpdateStatus;
    stCsRegRstEvent.ulLuAttemptCnt    = pstCsRegRstInd->ulLuAttemptCnt;

    PS_MEM_CPY(&stCsRegRstEvent.stOldLai, &pstCsRegRstInd->stOldLai, sizeof(MM_LAI_STRU));

    NAS_MNTN_OutputPositionInfo(&stCsRegRstEvent.stPositionInfo);

    /* Added by g00322017 for SEARCH_NW_CHR_OPT, 2015-8-17, begin */
    stCsRegRstEvent.ucRegFailOriginalCause = NAS_MML_GetOriginalRejectCause(stCsRegRstEvent.usRegFailCause);
    /* Added by g00322017 for SEARCH_NW_CHR_OPT, 2015-8-17, end */
    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = NAS_MML_PutErrLogRingBuf((VOS_CHAR *)&stCsRegRstEvent, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_CsRegErrRecord(): Push buffer error.");
    }

    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_CS_REG_FAIL,
                           WUEPS_PID_MMC,
                           (VOS_UINT8 *)&stCsRegRstEvent,
                           sizeof(stCsRegRstEvent));

    return;
}


VOS_VOID NAS_MMC_PsRegErrRecord(GMMMMC_PS_REG_RESULT_IND_STRU *pstPsRegRstInd)
{
    NAS_ERR_LOG_PS_REG_RESULT_EVENT_STRU                    stPsRegRstEvent;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulRegFailFlag;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_PS_REG_FAIL);
    ulIsLogRecord = NAS_MML_IsErrLogNeedRecord(usLevel);

    /* �ж϶�Ӧ���쳣ԭ��ֵ�Ƿ���Ҫ��¼ */
    ulRegFailFlag = NAS_MML_RegFailCauseNeedRecord(pstPsRegRstInd->enRegFailCause);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if ((VOS_FALSE == ulIsLogRecord)
     || (VOS_FALSE == ulRegFailFlag))
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_PS_REG_RESULT_EVENT_STRU);

    /* ���PSע��ʧ���쳣��Ϣ */
    PS_MEM_SET(&stPsRegRstEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stPsRegRstEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_MMC),
                                      NAS_ERR_LOG_ALM_PS_REG_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stPsRegRstEvent.enGmmActionType   = pstPsRegRstInd->enGmmActionType;
    stPsRegRstEvent.ulActionResult    = pstPsRegRstInd->enActionResult;
    stPsRegRstEvent.enReqDomain       = pstPsRegRstInd->enReqDomain;
    stPsRegRstEvent.enRsltDomain      = pstPsRegRstInd->enRsltDomain;
    stPsRegRstEvent.usRegFailCause    = pstPsRegRstInd->enRegFailCause;
    stPsRegRstEvent.enNetType         = pstPsRegRstInd->enNetType;
    stPsRegRstEvent.ulRegCounter      = pstPsRegRstInd->ulRegCounter;
    stPsRegRstEvent.ulServiceStatus   = pstPsRegRstInd->ulServiceStatus;

    NAS_MNTN_OutputPositionInfo(&stPsRegRstEvent.stPositionInfo);
    /* Added by g00322017 for SEARCH_NW_CHR_OPT, 2015-8-17, begin */
    stPsRegRstEvent.ucRegFailOriginalCause = NAS_MML_GetOriginalRejectCause(stPsRegRstEvent.usRegFailCause);
    /* Added by g00322017 for SEARCH_NW_CHR_OPT, 2015-8-17, end */
    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = NAS_MML_PutErrLogRingBuf((VOS_CHAR *)&stPsRegRstEvent, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_PsRegErrRecord(): Push buffer error.");
    }

    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_PS_REG_FAIL,
                           WUEPS_PID_MMC,
                           (VOS_UINT8 *)&stPsRegRstEvent,
                           sizeof(stPsRegRstEvent));
    return;
}


VOS_VOID NAS_MMC_PsServiceRegErrRecord(
    GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU                 *pstServiceRsltInd
)
{
    NAS_ERR_LOG_PS_SRV_REG_RESULT_EVENT_STRU                stPsSrvRegRstEvent;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulRegFailFlag;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_PS_SRV_REG_FAIL);
    ulIsLogRecord = NAS_MML_IsErrLogNeedRecord(usLevel);

    /* �ж϶�Ӧ���쳣ԭ��ֵ�Ƿ���Ҫ��¼ */
    ulRegFailFlag = NAS_MML_RegFailCauseNeedRecord(pstServiceRsltInd->enRegFailCause);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if ((VOS_FALSE == ulIsLogRecord)
     || (VOS_FALSE == ulRegFailFlag))
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_PS_SRV_REG_RESULT_EVENT_STRU);

    /* ���PSע��ʧ���쳣��Ϣ */
    PS_MEM_SET(&stPsSrvRegRstEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stPsSrvRegRstEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_MMC),
                                      NAS_ERR_LOG_ALM_PS_SRV_REG_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stPsSrvRegRstEvent.enActionResult = pstServiceRsltInd->enActionResult;
    stPsSrvRegRstEvent.enRegFailCause = pstServiceRsltInd->enRegFailCause;
    stPsSrvRegRstEvent.ulServiceSts   = pstServiceRsltInd->ulServiceSts;

    NAS_MNTN_OutputPositionInfo(&stPsSrvRegRstEvent.stPositionInfo);

    /* Added by g00322017 for SEARCH_NW_CHR_OPT, 2015-8-17, begin */
    stPsSrvRegRstEvent.ucRegFailOriginalCause = NAS_MML_GetOriginalRejectCause(stPsSrvRegRstEvent.enRegFailCause);
    /* Added by g00322017 for SEARCH_NW_CHR_OPT, 2015-8-17, end */

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = NAS_MML_PutErrLogRingBuf((VOS_CHAR *)&stPsSrvRegRstEvent, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_PsServiceRegErrRecord(): Push buffer error.");
    }

    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_PS_SRV_REG_FAIL,
                           WUEPS_PID_MMC,
                           (VOS_UINT8 *)&stPsSrvRegRstEvent,
                           sizeof(stPsSrvRegRstEvent));
    return;
}

/* Added by zwx247453 for CHR optimize, 2015-3-13 Begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_CmServiceRejErrRecord
 ��������  : ��¼Cm Service �����쳣�¼�
 �������  : VOS_UINT32                              ulCause,
             VOS_UINT32                              ulServiceStatus
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��13��
    ��    ��   : zwx247453
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_CmServiceRejErrRecord(
    VOS_UINT32                                              ulCause,
    VOS_UINT32                                              ulServiceStatus
)
{
    NAS_ERR_LOG_CM_SRV_REJ_IND_EVENT_STRU                   stCmSrvRejIndEvent;
    VOS_UINT32                                              ulIsLogNeedRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel           = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_CM_SRV_REJ_IND);
    ulIsLogNeedRecord = NAS_MML_IsErrLogNeedRecord(usLevel);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogNeedRecord)
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_CM_SRV_REJ_IND_EVENT_STRU);

    /* ���Cm���񱻾��쳣��Ϣ */
    PS_MEM_SET(&stCmSrvRejIndEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stCmSrvRejIndEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_MMC),
                                      NAS_ERR_LOG_ALM_CM_SRV_REJ_IND,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stCmSrvRejIndEvent.ulCause         = ulCause;
    stCmSrvRejIndEvent.ulServiceStatus = ulServiceStatus;

    NAS_MNTN_OutputPositionInfo(&stCmSrvRejIndEvent.stPositionInfo);
    /* Added by g00322017 for SEARCH_NW_CHR_OPT, 2015-8-17, begin */
    stCmSrvRejIndEvent.ucOriginalCause = NAS_MML_GetOriginalRejectCause(stCmSrvRejIndEvent.ulCause);
    /* Added by g00322017 for SEARCH_NW_CHR_OPT, 2015-8-17, end */

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = NAS_MML_PutErrLogRingBuf((VOS_CHAR *)&stCmSrvRejIndEvent, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_CmServiceRejErrRecord(): Push buffer error.");
    }

    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_CM_SRV_REJ_IND,
                           WUEPS_PID_MMC,
                           (VOS_UINT8 *)&stCmSrvRejIndEvent,
                           sizeof(stCmSrvRejIndEvent));

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_MoDetachIndRecord
 ��������  : ��¼MO Detachָʾ�¼�
 ��������  : ��¼����Detachָʾ�¼�
 �������  : VOS_UINT32                              ulDetachType
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��13��
    ��    ��   : zwx247453
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_MoDetachIndRecord(
    VOS_UINT32                              ulDetachType
)
{
    NAS_ERR_LOG_MO_DETACH_IND_EVENT_STRU                    stMoDetachIndEvent;
    VOS_UINT32                                              ulIsLogNeedRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel           = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_MO_DETACH_IND);
    ulIsLogNeedRecord = NAS_MML_IsErrLogNeedRecord(usLevel);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogNeedRecord)
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_MO_DETACH_IND_EVENT_STRU);

    /* ��䱾��DETACH�쳣��Ϣ */
    PS_MEM_SET(&stMoDetachIndEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stMoDetachIndEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_MMC),
                                      NAS_ERR_LOG_ALM_MO_DETACH_IND,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    NAS_MNTN_OutputPositionInfo(&stMoDetachIndEvent.stPositionInfo);

    stMoDetachIndEvent.enDetachType         = ulDetachType;

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = NAS_MML_PutErrLogRingBuf((VOS_CHAR *)&stMoDetachIndEvent, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_MoDetachIndRecord(): Push buffer error.");
    }

    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_MO_DETACH_IND,
                           WUEPS_PID_MMC,
                           (VOS_UINT8 *)&stMoDetachIndEvent,
                           sizeof(stMoDetachIndEvent));

    return;
}
/* Added by zwx247453 for CHR optimize, 2015-3-13 End */

#endif
VOS_VOID NAS_MMC_ErrLogRecordCsOosCause(
    NAS_MML_REG_STATUS_ENUM_UINT8        enOldCsRegStatus,
    NAS_MML_REG_STATUS_ENUM_UINT8        enNewCsRegStatus
)
{
    NAS_ERR_LOG_OOS_EVENT_ENUM_UINT32    enOosEvent;
    NAS_ERR_LOG_OOS_CAUSE_ENUM_UINT32    enOosCause;

    /* �з����޷��������£���¼�޷����ԭ�� */
    if (((NAS_MML_REG_REGISTERED_HOME_NETWORK == enOldCsRegStatus)
      || (NAS_MML_REG_REGISTERED_ROAM         == enOldCsRegStatus))
     && ((NAS_MML_REG_REGISTERED_HOME_NETWORK != enNewCsRegStatus)
      && (NAS_MML_REG_REGISTERED_ROAM         != enNewCsRegStatus)))
    {
        enOosEvent = NAS_MML_GetErrLogOosEvent();
        enOosCause = NAS_MNTN_ConvertOosEventToOosCause(enOosEvent);

        NAS_MML_SetErrLogCsOosCause(enOosCause);
    }

    return;
}
VOS_VOID NAS_MMC_ErrLogRecordPsOosCause(
    NAS_MML_REG_STATUS_ENUM_UINT8        enOldPsRegStatus,
    NAS_MML_REG_STATUS_ENUM_UINT8        enNewPsRegStatus
)
{
    NAS_ERR_LOG_OOS_EVENT_ENUM_UINT32    enOosEvent;
    NAS_ERR_LOG_OOS_CAUSE_ENUM_UINT32    enOosCause;

    /* �з����޷��������£���¼�޷����ԭ�� */
    if (((NAS_MML_REG_REGISTERED_HOME_NETWORK == enOldPsRegStatus)
      || (NAS_MML_REG_REGISTERED_ROAM         == enOldPsRegStatus))
     && ((NAS_MML_REG_REGISTERED_HOME_NETWORK != enNewPsRegStatus)
      && (NAS_MML_REG_REGISTERED_ROAM         != enNewPsRegStatus)))
    {
        enOosEvent = NAS_MML_GetErrLogOosEvent();
        enOosCause = NAS_MNTN_ConvertOosEventToOosCause(enOosEvent);

        NAS_MML_SetErrLogPsOosCause(enOosCause);
    }

    return;
}
VOS_VOID NAS_MMC_ErrLogClrNwSearchCount(
    NAS_MML_REG_STATUS_ENUM_UINT8        enOldRegStatus,
    NAS_MML_REG_STATUS_ENUM_UINT8        enNewRegStatus
)
{
    /* �޷����з��������£����������¼�Ĵ��� */
    if (((NAS_MML_REG_REGISTERED_HOME_NETWORK != enOldRegStatus)
      && (NAS_MML_REG_REGISTERED_ROAM         != enOldRegStatus))
     && ((NAS_MML_REG_REGISTERED_HOME_NETWORK == enNewRegStatus)
      || (NAS_MML_REG_REGISTERED_ROAM         == enNewRegStatus)))
    {
        NAS_MML_ClrErrLogNwSearchCount();
    }

    return;
}
VOS_VOID NAS_MMC_RecordOosEvent(
    NAS_ERR_LOG_OOS_EVENT_ENUM_UINT32    enOosEvent
)
{
    NAS_MML_SetErrLogOosEvent(enOosEvent);

    return;
}


VOS_VOID NAS_MMC_RecordOosEventForPlmnSearchScene(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32    enPlmnSearchScene
)
{
    switch (enPlmnSearchScene)
    {
        case NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE:
            NAS_MML_SetErrLogOosEvent(NAS_ERR_LOG_OOS_EVENT_DISABLE_LTE);
            break;

        case NAS_MMC_PLMN_SEARCH_SCENE_ENABLE_LTE_PLMN_SEARCH:
            NAS_MML_SetErrLogOosEvent(NAS_ERR_LOG_OOS_EVENT_ENABLE_LTE);
            break;

        default:
            break;
    }

    return;
}


VOS_VOID NAS_MMC_RecordOosEventForDetachReason(
    NAS_MSCC_PIF_DETACH_REASON_ENUM_UINT32  enDetachReason
)
{
    switch (enDetachReason)
    {
        case NAS_MSCC_PIF_DETACH_REASON_USER_DETACH:
            NAS_MML_SetErrLogOosEvent(NAS_ERR_LOG_OOS_EVENT_USER_DETACH);
            break;

        case NAS_MSCC_PIF_DETACH_REASON_RAT_OR_BAND_DETACH:
        case NAS_MSCC_PIF_DETACH_REASON_SRV_DOMAIN_DETACH:
            NAS_MML_SetErrLogOosEvent(NAS_ERR_LOG_OOS_EVENT_USER_SYSCFG);
            break;

        default:
            break;
    }

    return;

}

/* ������ȡNAS�������Ϣ���� */

VOS_VOID MM_GetNasInfo(MM_INFO_ST *pMmInfo)
{
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmn;
    NAS_MML_LAI_STRU                                       *pstLai;
    NAS_MML_PLMN_ID_STRU                                   *pstCurPlmnAddr;
    VOS_UINT32                                              i;
    PLMN_INFO_LIST_ST                                      *pstPlmnList;
    MM_INFO_ST                                             *pstMmInfo;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbidPlmnInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnWithRat;

    NAS_MML_PLMN_WITH_RAT_STRU                             *pstUserSpecPlmnId = VOS_NULL_PTR;
    VOS_UINT32                                              ulEplmnValidFlg;
    VOS_UINT32                                              ulRegFlag;

    VOS_UINT32                                              ulIsPlmnIdInDestPlmnWithRatList;
    VOS_UINT32                                              ulIsPlmnIdInForbidPlmnList;

    /* Added by g00322017 for CS REG FAIL FORB LA, 2015-9-23, begin */
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriodList =VOS_NULL_PTR;
    /* Added by g00322017 for CS REG FAIL FORB LA, 2015-9-23, end */


    pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();
    pstEquPlmn        = NAS_MML_GetEquPlmnList();
    pstMmInfo         = (MM_INFO_ST *)pMmInfo;
    pstPlmnList       = &(pstMmInfo->stPlmnInfo);


    pstCurPlmnAddr    = NAS_MML_GetCurrCampPlmnId();
    pstLai            = NAS_MML_GetCurrCampLai();

    pstPlmnList->stEplmnInfo.ulPlmnIdNum  = 0;
    pstPlmnList->stEplmnInfo.bitOpCurPlmn = VOS_FALSE;
    pstUserSpecPlmnId                     = NAS_MMC_GetUserSpecPlmnId();
    ulEplmnValidFlg                       = NAS_MML_GetEplmnValidFlg();
    ulRegFlag                             = NAS_MMC_GetUserSpecPlmnRegisterStatus();

    /*��ȡ��ֹ�б�*/
    pstPlmnList->ulForbLaNum = pstForbidPlmnInfo->ucForbRoamLaNum;

    for (i = 0; i < pstPlmnList->ulForbLaNum; i++)
    {
        pstPlmnList->aForbLaList[i].PlmnId.ulMcc = pstForbidPlmnInfo->astForbRomLaList[i].stPlmnId.ulMcc;
        pstPlmnList->aForbLaList[i].PlmnId.ulMnc = pstForbidPlmnInfo->astForbRomLaList[i].stPlmnId.ulMnc;

        pstPlmnList->aForbLaList[i].ulForbLac    = (VOS_UINT32)pstForbidPlmnInfo->astForbRomLaList[i].aucLac[1]
                                                   |(VOS_UINT32)((VOS_UINT32)pstForbidPlmnInfo->astForbRomLaList[i].aucLac[0]<<8);
    }

    /* Added by g00322017 for CS REG FAIL FORB LA, 2015-9-23, begin */
    pstForbLaWithValidPeriodList = NAS_MML_GetForbLaWithValidPeriodList();
    for ( i = 0; i < pstForbLaWithValidPeriodList->ulForbLaWithValidPeriodNum; i++ )
    {
        pstLai = &(pstForbLaWithValidPeriodList->astForbLaWithValidPeriodList[i].stForbLaWithValidPeriodLai);
        if ( (VOS_FALSE == NAS_MML_IsLaiInDestLaiList(pstLai, pstForbidPlmnInfo->ucForbRoamLaNum, pstForbidPlmnInfo->astForbRomLaList))
          && ( pstPlmnList->ulForbLaNum < RRC_MAX_FORBLA_NUM) )
        {
            pstPlmnList->aForbLaList[pstPlmnList->ulForbLaNum].PlmnId.ulMcc   =
                        pstLai->stPlmnId.ulMcc;
            pstPlmnList->aForbLaList[pstPlmnList->ulForbLaNum].PlmnId.ulMnc   =
                        pstLai->stPlmnId.ulMnc;
            pstPlmnList->aForbLaList[pstPlmnList->ulForbLaNum].ulForbLac      =
                        ((VOS_UINT32)((pstLai->aucLac[0]) << 8 ) | (VOS_UINT32)((pstLai->aucLac[1])));
            (pstPlmnList->ulForbLaNum)++;
        }
    }
    /* Added by g00322017 for CS REG FAIL FORB LA, 2015-9-23, end */


    /*��ȡusim��״̬*/
    if (VOS_FALSE == NAS_MML_IsUsimStausValid())
    {                                                                           /* SIM��������                              */
        pstMmInfo->stSimInfo.ulSimStatus = RRC_NAS_UICC_ABSENT;                                      /* �趨SIM��״̬                            */
    }
    else
    {                                                                           /* SIM������                                */
        if (NAS_MML_SIM_TYPE_SIM  == NAS_MML_GetSimType())
        {
            pstMmInfo->stSimInfo.ulSimStatus = RRC_NAS_SIM_PRESENT;
        }
        else
        {
            pstMmInfo->stSimInfo.ulSimStatus = RRC_NAS_USIM_PRESENT;                                     /* �趨SIM��״̬                            */
        }

        pstMmInfo->ucUeOperMode = NAS_MML_GetUeOperMode();
    }

    pMmInfo->stCurPlmnId.ulMcc = pstCurPlmnAddr->ulMcc;
    pMmInfo->stCurPlmnId.ulMnc = pstCurPlmnAddr->ulMnc;

    pMmInfo->usCurLac          = (VOS_UINT16)pstLai->aucLac[1]
                                 |(VOS_UINT16)((VOS_UINT16)pstLai->aucLac[0]<<8);

    pMmInfo->ucCurRac          = NAS_MML_GetCurrCampRac();

    pstPlmnList->stEplmnInfo.stCurCampedPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    pstPlmnList->stEplmnInfo.stCurCampedPlmnId.ulMnc = NAS_MML_INVALID_MNC;

    stPlmnWithRat.enRat         = NAS_MML_NET_RAT_TYPE_GSM;

    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        stPlmnWithRat.stPlmnId = pstUserSpecPlmnId->stPlmnId;
    }
    else
    {
        stPlmnWithRat.stPlmnId = *pstCurPlmnAddr;
    }

    ulIsPlmnIdInDestPlmnWithRatList = NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat);

    ulIsPlmnIdInForbidPlmnList = NAS_MML_IsPlmnIdInForbidPlmnList(&stPlmnWithRat.stPlmnId);

    if ((VOS_FALSE == ulIsPlmnIdInDestPlmnWithRatList)
     && (VOS_FALSE == ulIsPlmnIdInForbidPlmnList))
    {
        pstPlmnList->stEplmnInfo.bitOpCurPlmn = VOS_TRUE;
        pMmInfo->stPlmnInfo.stEplmnInfo.stCurCampedPlmnId.ulMcc = stPlmnWithRat.stPlmnId.ulMcc;
        pMmInfo->stPlmnInfo.stEplmnInfo.stCurCampedPlmnId.ulMnc = stPlmnWithRat.stPlmnId.ulMnc;
    }

    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        /* �ж�eplmn�б��Ƿ���Ч,��Ч�򷵻� */
        if ((VOS_FALSE == ulRegFlag)
         || (VOS_FALSE == ulEplmnValidFlg))
        {
            pstPlmnList->stEplmnInfo.ulPlmnIdNum  = 0;
            return;
        }
    }

    /* ��ȡ��ЧPLMN�б�,����ǰ���粻��Eplmn��,����ǰ���緵�ظ������ */
    for (i = 0; i < pstEquPlmn->ucEquPlmnNum; i++)
    {
        /* ��������뼼����PLMN ID */
        stPlmnWithRat.enRat         = NAS_MML_NET_RAT_TYPE_GSM;
        stPlmnWithRat.stPlmnId      = pstEquPlmn->astEquPlmnAddr[i];

        /* �жϵ�ЧPLMN�Ƿ��ڽ�ֹ���뼼����PLMN�б���,������򲻽���PLMN ID����RRC */
        if (VOS_TRUE == NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
        {
            continue;
        }

        if (VOS_TRUE == NAS_MML_IsPlmnIdInForbidPlmnList(&(pstEquPlmn->astEquPlmnAddr[i])))
        {
            continue;
        }

        pstPlmnList->stEplmnInfo.aPlmnIdList[pstPlmnList->stEplmnInfo.ulPlmnIdNum].ulMcc = pstEquPlmn->astEquPlmnAddr[i].ulMcc;
        pstPlmnList->stEplmnInfo.aPlmnIdList[pstPlmnList->stEplmnInfo.ulPlmnIdNum].ulMnc = pstEquPlmn->astEquPlmnAddr[i].ulMnc;
        pstPlmnList->stEplmnInfo.ulPlmnIdNum++;
    }



    return;
}
VOS_UINT32 NAS_MMC_IsCsPsBothRegSucc(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetRatType
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsRegCause;
    NAS_MMC_SERVICE_ENUM_UINT8          enPsServiceStatus;
    NAS_MMC_SERVICE_ENUM_UINT8          enCsServiceStatus;


    enPsRegCause            = NAS_MML_REG_FAIL_CAUSE_NULL;
    enCsRegCause            = NAS_MML_REG_FAIL_CAUSE_NULL;

    enCsServiceStatus = NAS_MMC_GetCsServiceStatus();
    enPsServiceStatus = NAS_MMC_GetPsServiceStatus();


    /* ��ȡ֮ǰע��ʧ�ܵ�ԭ��ֵ */
    NAS_MMC_GetDomainRegStatusInRegInfoList(NAS_MML_GetCurrCampPlmnId(),
                                            enNetRatType,
                                            &enCsRegCause,
                                            &enPsRegCause);


    if ((NAS_MMC_NORMAL_SERVICE == enCsServiceStatus)
     && (NAS_MMC_NORMAL_SERVICE == enPsServiceStatus)
     && (NAS_MML_REG_FAIL_CAUSE_NULL == enCsRegCause)
     && (NAS_MML_REG_FAIL_CAUSE_NULL == enPsRegCause))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail(VOS_VOID)
{
    VOS_UINT32                                              ulIsNeedDisableL;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegCause;
    NAS_MMC_SERVICE_ENUM_UINT8                              enPsServiceStatus;

    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnWithRat;

    VOS_UINT32                                              ulIsNeedAddVoiceNotAvailPlmnFlag;

    NAS_MMC_REG_RSLT_CTX_STRU                              *pstRegRsltCtx = VOS_NULL_PTR;

    pstRegRsltCtx   = NAS_MMC_GetRegRsltCtxAddr();

    enPsRegCause            = NAS_MML_REG_FAIL_CAUSE_NULL;
    enCsRegCause            = NAS_MML_REG_FAIL_CAUSE_NULL;

    /* ����Ѿ�disable ����Ҫ��disable LTE */
    if (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
    {
        return VOS_FALSE;
    }


    /* ֮ǰ��L�½��й�δTAU��ATTACH��ҵ������ */
    if ( NAS_MML_NET_RAT_TYPE_LTE != NAS_MML_GetCurrNetRatType() )
    {
        return VOS_FALSE;
    }
    enPsServiceStatus = NAS_MMC_GetPsServiceStatus();

    PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(), sizeof(stPlmnWithRat.stPlmnId));
    stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

    /* ��ȡ֮ǰע��ʧ�ܵ�ԭ��ֵ */
    NAS_MMC_GetDomainRegStatusInRegInfoList(NAS_MML_GetCurrCampPlmnId(),
                                            NAS_MML_NET_RAT_TYPE_LTE,
                                            &enCsRegCause,
                                            &enPsRegCause);

    /* CS+EPS ���ɹ� */
    if (VOS_TRUE == NAS_MMC_IsCsPsBothRegSucc(NAS_MML_NET_RAT_TYPE_LTE))
    {
        ulIsNeedDisableL = NAS_MMC_IsNeedDisableL_CombinedRegRsltSucc();

        if (VOS_TRUE == ulIsNeedDisableL)
        {
            if (VOS_TRUE == NAS_MML_IsNeedAddVoiceNotAvailDisabledPlmnInDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat, NAS_MML_REG_FAIL_CAUSE_NULL, NAS_MML_REG_FAIL_CAUSE_NULL, NAS_MML_GetAdditionUpdateRslt()))
            {
                NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                              NAS_MML_GetVoiceNotPreferDisabledPlmnForbiddenTimeSlice(),
                                                              MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
            }
        }

        return ulIsNeedDisableL;
    }

    if ((NAS_MMC_NORMAL_SERVICE == enPsServiceStatus)
     && (NAS_MML_REG_FAIL_CAUSE_NULL == enPsRegCause))
    {

        /* EPS����ע��ɹ� */
        if (VOS_TRUE == pstRegRsltCtx->ucIsLteRegTypeEpsOnly)
        {
            ulIsNeedDisableL = NAS_MMC_IsNeedDisableL_EpsOnlyRegSucc();

            return ulIsNeedDisableL;
        }

        /* EPS ONLY�ɹ�,CS����18,CS����16,17,22,other cause,EPS���Դ����ﵽ5�� */
        if (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR != enCsRegCause)
        {
            ulIsNeedDisableL = NAS_MMC_IsNeedDisableL_CombinedRegRsltOnlyEpsSucc(enCsRegCause);

            if ((NAS_MML_MAX_PS_REG_FAIL_CNT == NAS_MMC_GetRegRsltAttemptCounter(NAS_MMC_GetRegRsltType()))
              && (VOS_TRUE == ulIsNeedDisableL))
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER, NAS_MML_GetCsPsMode1EnableLteTimerLen());

                if (VOS_TRUE == NAS_MML_IsNeedAddDamPlmnInDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
                {
                    NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                                  NAS_MML_GetDamDisabledPlmnWithForbiddenPeriodTimeSlice(&stPlmnWithRat),
                                                                  MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
                }

            }

            ulIsNeedAddVoiceNotAvailPlmnFlag = NAS_MML_IsNeedAddVoiceNotAvailDisabledPlmnInDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat, enCsRegCause, enPsRegCause, NAS_MML_GetAdditionUpdateRslt());

            if ((VOS_TRUE == ulIsNeedDisableL)
             && (VOS_TRUE == ulIsNeedAddVoiceNotAvailPlmnFlag))
            {
                NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                              NAS_MML_GetVoiceNotPreferDisabledPlmnForbiddenTimeSlice(),
                                                              MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
            }
            return ulIsNeedDisableL;
        }
    }

    return VOS_FALSE;
}

#endif
VOS_UINT32 NAS_MMC_GetWaitGasPlmnSearchCnfTimerLen(
    VOS_UINT32                          ulUserSpecSearchFlg
)
{
    /* ��DSDS�汾ģʽ���ҷ��û�ָ����ʱ��ȡ����ʱ����ʱ�� */
    if ( (VOS_TRUE == NAS_MML_IsDsdsMultiModemMode())
      && (VOS_FALSE == ulUserSpecSearchFlg) )
    {
        return TI_NAS_MMC_DSDS_SCEAN_WAIT_GAS_PLMN_SEARCH_CNF_LEN;
    }

    return TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF_LEN;
}
VOS_VOID NAS_MMC_RegisterRrmResourceNtf(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNasRat,
    RRM_PS_TASK_TYPE_ENUM_UINT16        enRrmTaskType
)
{
#if (FEATURE_ON == FEATURE_DSDS)
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_RATMODE_ENUM_UINT32             enRrmRat;

    enRrmRat = NAS_MMC_ConvertRatToRrmPsRat(enNasRat);

    /* ��ȡmodem id */
    enModemId = VOS_GetModemIDFromPid(WUEPS_PID_MMC);

    /* �����ǰNVδ����DSDS,����RRM����ע�� */
    if ( VOS_FALSE == NAS_MML_GetDsdsRfShareFlg() )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RegisterRrmResourceNtf: DSDS RF SHARE FLG IS VOS_FALSE!!!");
        return;
    }

    /* ����ע����Ϣ */
    if((VOS_RATMODE_BUTT     != enRrmRat)
    && (MODEM_ID_BUTT        != enModemId))
    {
        NAS_MMC_SndRrmRegisterInd(enModemId,
                                  enRrmTaskType,
                                  enRrmRat);
    }

#endif

    NAS_INFO_LOG2(WUEPS_PID_MMC, "NAS_MMC_RegisterRrmResourceNtf : enNasRat, enRrmTaskType", enNasRat, enRrmTaskType);

    return;
}
VOS_VOID NAS_MMC_DeregisterRrmResourceNtf(
    VOS_RATMODE_ENUM_UINT32             enRrmRat,
    RRM_PS_TASK_TYPE_ENUM_UINT16        enRrmTaskType
)
{
#if (FEATURE_ON == FEATURE_DSDS)
    MODEM_ID_ENUM_UINT16                usModemId;

    /* ȡ�õ�ǰMODEM��ID��Ϣ  */
    usModemId = VOS_GetModemIDFromPid(WUEPS_PID_MMC);

    /* �����ǰNVδ����DSDS,����RRM����ȥע�� */
    if ( VOS_FALSE == NAS_MML_GetDsdsRfShareFlg() )
    {
        return;
    }

    /* ��RRM���͵�ȥע����Ϣ */
    if((VOS_RATMODE_BUTT     != enRrmRat)
    && (MODEM_ID_BUTT        != usModemId))
    {
        NAS_MMC_SndRrmDeRegisterInd(usModemId,
                                    enRrmTaskType,
                                    enRrmRat);
    }
#endif

    NAS_INFO_LOG2(WUEPS_PID_MMC, "NAS_MMC_DeregisterRrmResourceNtf : enRrmRat, enRrmTaskType", enRrmRat, enRrmTaskType);

    return;
}
VOS_VOID NAS_MMC_DeregisterRrmResourceNtfAllRat(
    RRM_PS_TASK_TYPE_ENUM_UINT16        enRrmTaskType
)
{
    VOS_UINT32                          i;
    NAS_MML_PLATFORM_RAT_CAP_STRU      *pstPlatformRatCap  = VOS_NULL_PTR;

    pstPlatformRatCap = NAS_MML_GetPlatformRatCap();

    /* LTE�Ƿ���ƽ̨���뼼�������б��� */
    for (i = 0 ; i < pstPlatformRatCap->ucRatNum; i++)
    {
        if (NAS_MML_PLATFORM_RAT_TYPE_GSM == pstPlatformRatCap->aenRatPrio[i])
        {
            /* ���ݱ���ģʽ������RRM����ȥע����Ϣ */
            NAS_MMC_DeregisterRrmResourceNtf(VOS_RATMODE_GSM, enRrmTaskType);
        }
#if (FEATURE_ON == FEATURE_LTE)
        else if (NAS_MML_PLATFORM_RAT_TYPE_LTE == pstPlatformRatCap->aenRatPrio[i])
        {
            /* ���ݱ���ģʽ������RRM����ȥע����Ϣ */
            NAS_MMC_DeregisterRrmResourceNtf(VOS_RATMODE_LTE, enRrmTaskType);
        }
#endif
        else if (NAS_MML_PLATFORM_RAT_TYPE_WCDMA == pstPlatformRatCap->aenRatPrio[i])
        {
            /* ���ݱ���ģʽ������RRM����ȥע����Ϣ */
            NAS_MMC_DeregisterRrmResourceNtf(VOS_RATMODE_WCDMA, enRrmTaskType);
        }
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
        else if (NAS_MML_PLATFORM_RAT_TYPE_TD_SCDMA == pstPlatformRatCap->aenRatPrio[i])
        {
            /* ���ݱ���ģʽ������RRM����ע�ᡢȥע����Ϣ */
            NAS_MMC_DeregisterRrmResourceNtf(VOS_RATMODE_TDS, enRrmTaskType);\
        }
#endif
        else
        {
            ;
        }
    }

    return;
}
VOS_RATMODE_ENUM_UINT32 NAS_MMC_ConvertRatToRrmPsRat(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enMmcRat
)
{
    VOS_RATMODE_ENUM_UINT32             enRrmPsRat;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode;

    /*��ȡTD����WCDMA*/
    enUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();

    if (NAS_MML_NET_RAT_TYPE_GSM == enMmcRat)
    {
        enRrmPsRat = VOS_RATMODE_GSM;
    }
    else if ((NAS_MML_NET_RAT_TYPE_WCDMA   == enMmcRat)
          && (NAS_UTRANCTRL_UTRAN_MODE_FDD == enUtranMode))
    {
        enRrmPsRat = VOS_RATMODE_WCDMA;
    }
    else if ((NAS_MML_NET_RAT_TYPE_WCDMA   == enMmcRat)
          && (NAS_UTRANCTRL_UTRAN_MODE_TDD == enUtranMode))
    {
        enRrmPsRat = VOS_RATMODE_TDS;
    }
#if (FEATURE_ON == FEATURE_LTE)
    else if (NAS_MML_NET_RAT_TYPE_LTE == enMmcRat)
    {
        enRrmPsRat = VOS_RATMODE_LTE;
    }
#endif
    else
    {
        enRrmPsRat = VOS_RATMODE_BUTT;
    }

    return enRrmPsRat;
}
VOS_UINT32 NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer_CsfbEnd( VOS_VOID )
{
    VOS_UINT32                                              ulIsRrcConnExist;
    VOS_UINT32                                              ulIsNeedStartHighPrioRatHPlmnTimer;

    ulIsRrcConnExist                    = NAS_MML_IsRrcConnExist();
    ulIsNeedStartHighPrioRatHPlmnTimer  = NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer();

    /* ҵ�񲻴��ڣ�����RRC���Ӳ����ڣ������ȼ�RAT��HPLMN��ʱ����NV�� */
    if ((VOS_FALSE  == NAS_MML_GetCmServiceSetupFlg())
     && (VOS_FALSE  == ulIsRrcConnExist)
     && (VOS_TRUE   == ulIsNeedStartHighPrioRatHPlmnTimer))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT32 NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPlmnRatList       = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCurrCampPlmnInfo  = VOS_NULL_PTR;

    if (VOS_FALSE == NAS_MMC_IsHighPrioRatHplmnSearchVaild())
    {
        return VOS_FALSE;
    }

    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER))
    {
        return VOS_FALSE;
    }

    /* ��ȡMML�б���ĵ�ǰMS֧�ֵĽ���ģʽ�ͽ������ȼ� */
    pstPlmnRatList = NAS_MML_GetMsPrioRatList();

    pstCurrCampPlmnInfo = NAS_MML_GetCurrCampPlmnInfo();

    if (VOS_FALSE == NAS_MML_ComparePlmnIdWithHplmn(&pstCurrCampPlmnInfo->stLai.stPlmnId))
    {
        return VOS_FALSE;
    }

    /* פ����HPLMN��������ȼ��Ľ��뼼�� */
    if (pstPlmnRatList->aucRatPrio[0] == pstCurrCampPlmnInfo->stLai.enCampPlmnNetRat)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_IsHighPrioRatHplmnSearchVaild( VOS_VOID )
{
    NAS_MML_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU       *pstHighRatHplmnTimerCfg = VOS_NULL_PTR;

    pstHighRatHplmnTimerCfg = NAS_MML_GetHighPrioRatHplmnTimerCfg();

    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_FALSE;
    }

    if (VOS_FALSE == NAS_MML_GetHighPrioRatHplmnTimerActiveFlg())
    {
        return VOS_FALSE;
    }

    /* �ֶ�ģʽ�·�����Ч */
    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        return VOS_FALSE;
    }

    if (VOS_FALSE == NAS_MML_IsUsimStausValid())
    {
        return VOS_FALSE;
    }

    /* HPLMN TIMER LEN��ʱ��ʱ����Ч */
    if ((0 != pstHighRatHplmnTimerCfg->ulFirstSearchTimeLen)
     && (0 != pstHighRatHplmnTimerCfg->ulNonFirstSearchTimeLen)
     && (0 != pstHighRatHplmnTimerCfg->ulRetrySearchTimeLen))
    {
        /* ������Ч */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT32 NAS_MMC_IsCampOnHighestPrioRatHplmn(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPlmnRatList       = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCurrCampPlmnInfo  = VOS_NULL_PTR;

    /* ��ȡMML�б���ĵ�ǰMS֧�ֵĽ���ģʽ�ͽ������ȼ� */
    pstPlmnRatList = NAS_MML_GetMsPrioRatList();

    pstCurrCampPlmnInfo = NAS_MML_GetCurrCampPlmnInfo();

    /* �����ǰ������Ч���򷵻�δפ����������ȼ������ϣ�����ģ�����󣬵�ǰפ��������
       ����ЧPLMNID */
    if ( VOS_FALSE == NAS_MML_IsPlmnIdValid(&pstCurrCampPlmnInfo->stLai.stPlmnId) )
    {
        return VOS_FALSE;
    }

    if (VOS_FALSE == NAS_MML_ComparePlmnIdWithHplmn(&pstCurrCampPlmnInfo->stLai.stPlmnId))
    {
        return VOS_FALSE;
    }

    /* פ����HPLMN�Ƿ�������ȼ��Ľ��뼼�� */
    if (pstPlmnRatList->aucRatPrio[0] != pstCurrCampPlmnInfo->stLai.enCampPlmnNetRat)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
VOS_VOID NAS_MMC_UpdateHighPrioRatHPlmnTimerTdCount(VOS_VOID)
{
    VOS_UINT8                                               ucCurrHighRatHplmnTdCount;
    VOS_UINT8                                               ucHighRatHplmnTdThreshold;

    if (VOS_FALSE == NAS_MMC_IsCurrentTdscdmaMode())
    {
        return;
    }

    ucCurrHighRatHplmnTdCount = NAS_MMC_GetTdHighRatSearchCount();
    ucHighRatHplmnTdThreshold = NAS_MML_GetHighPrioRatHplmnTimerTdThreshold();

    if (ucCurrHighRatHplmnTdCount >= ucHighRatHplmnTdThreshold)
    {
        NAS_MMC_InitTdHighRatSearchCount();
    }

    NAS_MMC_AddTdHighRatSearchCount();

    return;

}


NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8 NAS_MMC_GetPlmnPrioClass(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    if (VOS_FALSE == NAS_MML_IsPlmnIdValid(pstPlmnId))
    {
        return NAS_MSCC_PIF_PLMN_PRIORITY_BUTT;
    }

    /* ��HPLMN��ͬ������NAS_MSCC_PIF_PLMN_PRIORITY_HOME */
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(pstPlmnId))
    {
        return NAS_MSCC_PIF_PLMN_PRIORITY_HOME;
    }

    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithUplmn(pstPlmnId))
    {
        if (VOS_FALSE == NAS_MML_Get3GPP2UplmnNotPrefFlg())
        {
            return NAS_MSCC_PIF_PLMN_PRIORITY_PREF;
        }
    }

    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithOplmn(pstPlmnId))
    {
        return NAS_MSCC_PIF_PLMN_PRIORITY_PREF;
    }

    return NAS_MSCC_PIF_PLMN_PRIORITY_ANY;
}
VOS_UINT32 NAS_MMC_ComParePlmnPrioClass(
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8                  enSrcPrioClass,
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8                  enDestPrioClass
)
{
    /* ���enSrcPrioClass�Ѿ���������ȼ���ֱ�ӷ���VOS_TRUE */
    if (NAS_MSCC_PIF_PLMN_PRIORITY_HOME == enSrcPrioClass)
    {
        return VOS_TRUE;
    }
    else if (NAS_MSCC_PIF_PLMN_PRIORITY_PREF == enSrcPrioClass)
    {
        /* ���enSrcPrioClass��NAS_MSCC_PIF_PLMN_PRIORITY_PREF������enDestPrioClassΪ������ȼ�ʱ����VOS_FALSE */
        if (NAS_MSCC_PIF_PLMN_PRIORITY_HOME == enDestPrioClass)
        {
            return VOS_FALSE;
        }
        else
        {
            return VOS_TRUE;
        }
    }
    else
    {
        /* ���enSrcPrioClass��NAS_MSCC_PIF_PLMN_PRIORITY_ANY������enDestPrioClassΪ��ͬ���ȼ�ʱ����VOS_TRUE */
        if (NAS_MSCC_PIF_PLMN_PRIORITY_ANY == enDestPrioClass)
        {
            return VOS_TRUE;
        }
        else
        {
            return VOS_FALSE;
        }
    }
}
VOS_UINT32 NAS_MMC_IsSuccRegInSpecCellInfo(
    MSCC_MMC_REG_CELL_INFO_STRU         *pstCellInfo
)
{
    VOS_UINT32                          i;
    NAS_MML_CAMP_CELL_INFO_STRU        *pstCampCell         = VOS_NULL_PTR;

    /* ���뼼����ͬ������VOS_FALSE */
    if (pstCellInfo->ucRat != NAS_MML_GetCurrNetRatType())
    {
        return VOS_FALSE;
    }

    /* Ƶ�㲻ͬ������VOS_FALSE */
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, begin */
    if (pstCellInfo->ulArfcn != NAS_MML_GetCurrCampArfcn())
    {
        return VOS_FALSE;
    }
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, end */

    /* ������Ϣ��PLMN���ڶ����뵱ǰפ����ͬ������VOS_FALSE */
    if (pstCellInfo->ucPlmnNum > 0)
    {
        if (VOS_FALSE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(NAS_MML_GetCurrCampPlmnId(),
                                                  pstCellInfo->ucPlmnNum,
                                                  pstCellInfo->astPlmnId))
        {
            return VOS_FALSE;
        }
    }

    /* ������Ϣ��û��Я��С��ID������VOS_TRUE */
    if (0 == pstCellInfo->ucCellNum)
    {
        return VOS_TRUE;
    }

    pstCampCell     = NAS_MML_GetCampCellInfo();

    /* ������Ϣ��CELL ID���ڶ����뵱ǰפ����ͬ������VOS_TRUE */
    for (i = 0; i < pstCellInfo->ucCellNum; i++)
    {
        if (pstCellInfo->ausCellId[i] == pstCampCell->astCellInfo[0].ulCellId)
        {
            return VOS_TRUE;
        }
    }

    /* ������Ϣ��CELL ID���ڶ����뵱ǰפ����ͬ������VOS_FALSE */
    return VOS_FALSE;
}


NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32 NAS_MMC_GetPlmnSearchSceneMsccRegReq(
    MSCC_MMC_REG_REQ_STRU               *pstRegReq
)
{
    /* �����ڲ�������Ϣ���������������߼� */
    if (VOS_TRUE == pstRegReq->bitOpCellInfo)
    {
        return NAS_MMC_PLMN_SEARCH_SCENE_REG_NCELL;
    }
    /* ����ָ�����ȼ���ע�� */
    else if (VOS_TRUE == pstRegReq->bitOpPrioClass)
    {
        /* ����ָ�����ȼ�ΪHPLMN��ע�� */
        if (NAS_MSCC_PIF_PLMN_PRIORITY_HOME == pstRegReq->enPrioClass)
        {
            return NAS_MMC_PLMN_SEARCH_SCENE_REG_HPLMN;
        }
        /* ����ָ�����ȼ�ΪPREF��ע�� */
        else if (NAS_MSCC_PIF_PLMN_PRIORITY_PREF == pstRegReq->enPrioClass)
        {
            return NAS_MMC_PLMN_SEARCH_SCENE_REG_PREF_PLMN;
        }
        else
        {
            return NAS_MMC_PLMN_SEARCH_SCENE_REG_ANY_PLMN;
        }
    }
    /* �쳣������NAS_MMC_PLMN_SEARCH_SCENE_REG_ANY_PLMN���� */
    else
    {
        return NAS_MMC_PLMN_SEARCH_SCENE_REG_ANY_PLMN;
    }
}
VOS_VOID   NAS_MMC_Convert3GPP2RatType(
    NAS_MSCC_PIF_3GPP2_RAT_TYPE_ENUM_UINT8   enMSCC3GPP2RatType,
    NAS_MML_3GPP2_RAT_TYPE_ENUM_UINT8  *penMML3GPP2RatType
)
{
    switch (enMSCC3GPP2RatType)
    {
        case NAS_MSCC_PIF_3GPP2_RAT_TYPE_CDMA1X:

            *penMML3GPP2RatType = NAS_MML_3GPP2_RAT_TYPE_CDMA1X;
            break;

        case NAS_MSCC_PIF_3GPP2_RAT_TYPE_HRPD:

            *penMML3GPP2RatType = NAS_MML_3GPP2_RAT_TYPE_HRPD;
            break;

        case NAS_MSCC_PIF_3GPP2_RAT_TYPE_BUTT:
            *penMML3GPP2RatType = NAS_MML_3GPP2_RAT_TYPE_BUTT;
            break;

        default:

            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ConvertRrcCoverTypeToNasFormat TYPE ERROR!!!");
            *penMML3GPP2RatType = NAS_MML_3GPP2_RAT_TYPE_BUTT;
            break;
    }

    return;
}



VOS_UINT32  NAS_MMC_IsSorTriggerAdditionalLau(VOS_VOID)
{
    NAS_MML_SOR_ADDITIONAL_LAU_STRU                        *pstAdditionalLau    = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCampInfo         = VOS_NULL_PTR;


    pstAdditionalLau    = NAS_MML_GetSorAdditionalLauCtx();
    pstCampInfo         = NAS_MML_GetCurrCampPlmnInfo();

    if ( VOS_FALSE == pstAdditionalLau->ucAdditionalLauFlag )
    {
        return VOS_FALSE;
    }

    /* ��ǿ�ж�LAI�Ƿ�ı� */
    if ( VOS_FALSE == NAS_MML_CompareLai(&(pstAdditionalLau->stLai),&(pstCampInfo->stLai)) )
    {
        return VOS_FALSE;
    }

    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        return VOS_FALSE;
    }

    /* ���򷵻���Ҫ����ADDITIONAL LAU */
    return VOS_TRUE;
}


VOS_VOID NAS_MMC_SndMsccCurrServiceRelatedInfo(VOS_VOID)
{
    MSCC_MMC_SCELL_MEAS_REPORT_TYPE_UN   unMeasReportType;
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32  enMsccServiceState;

    PS_MEM_SET(((VOS_UINT8*)&unMeasReportType), 0, sizeof(MSCC_MMC_SCELL_MEAS_REPORT_TYPE_UN));

    unMeasReportType.ucMeasReportType |= NAS_MSCC_PIF_SCELL_MEAS_TYPE_RXLEV;

    /* �ϱ���ǰ��ϵͳ��Ϣ����MSCC������Ϣͬ�� */
    NAS_MMC_SndMsccSysInfo();

    /* �ϱ�CAMP ON��Ϣ */
    if (NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    }
    else
    {
        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    }

    /* �ϱ�����״̬ */
    NAS_MMC_ConvertToMsccSrvStatus(NAS_MMC_GetCsServiceStatus(), &enMsccServiceState);
    NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS,  enMsccServiceState);

    NAS_MMC_ConvertToMsccSrvStatus(NAS_MMC_GetPsServiceStatus(), &enMsccServiceState);
    NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_PS,  enMsccServiceState);

    /* �ϱ�ע��״̬ */
    NAS_MMC_SndMsccRegStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MML_GetCsRegStatus());
    NAS_MMC_SndMsccRegStatusInd(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MML_GetPsRegStatus());

    /* �ϱ�RSSI */
    NAS_MMC_SndMsccRssiInd(&unMeasReportType);

    return;
}


/* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-18, begin */


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetIndexOfFirstSelfLearningTypeElement
 ��������  : ��ȡ DplmnList �����һ��������Ԥ�����͵�plmn���±�
 �������  :
             pulDestPlmnNum    - DPLMN/NPLMN list����
             pstDestPlmnIdList - DPLMN/NPLMN listָ��
 �������  : ��
 �� �� ֵ  : ulIndex -- �����±�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��5��18��
   ��    ��   : c00318887
   �޸�����   : for DPlmn���ݺ����Ƚ���HPLMN
*****************************************************************************/
VOS_UINT32  NAS_MMC_GetIndexOfFirstSelfLearningTypeElement(
    VOS_UINT16                                             *pulFirstPosition,
    VOS_UINT16                                              ulDestPlmnNum,
    NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU                  *pstDestPlmnIdList
)
{
    VOS_UINT32                    ulLoop  = 0;

    for (ulLoop = 0; ulLoop < ulDestPlmnNum; ulLoop++)
    {
        if (NAS_MMC_DPLMN_NPLMN_SELF_LEARING_TYPE == pstDestPlmnIdList[ulLoop].enType)
        {
            break;
        }
    }

    /* ����ѧϰ���� */
    if (ulLoop < ulDestPlmnNum)
    {
        *pulFirstPosition = (VOS_UINT16)ulLoop;
        return VOS_TRUE;
    }

    /* û����ѧϰ���� ����û�� */
    if (NAS_MMC_MAX_CFG_DPLMN_NUM - 1 >= ulDestPlmnNum)
    {
        *pulFirstPosition = ulDestPlmnNum;
        return VOS_TRUE;
    }

    /* û����ѧϰ����, ������  */
    *pulFirstPosition = NAS_MMC_MAX_CFG_DPLMN_NUM;
    return VOS_FALSE;
}
/* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-21, end */


VOS_VOID  NAS_MMC_UpdateDPlmnNPlmnList(
    NAS_MML_PLMN_ID_STRU                   *pstCurrPlmn,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetType,
    NAS_MMC_REG_DOMAIN_ENUM_UINT8       enRegDomain,
    VOS_UINT16                                             *pulDestPlmnNum,
    NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU                  *pstDestPlmnIdList
)
 {
    VOS_UINT32                                              i;
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    VOS_UINT16                                              usSimRat;

    /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-21, begin */
    VOS_UINT16                                              usIndex;
    /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-21, end */

    pstDPlmnNPlmnCfgInfo  = NAS_MMC_GetDPlmnNPlmnCfgInfo();
    usSimRat              = NAS_MML_INVALID_SIM_RAT;

    if (VOS_TRUE != pstDPlmnNPlmnCfgInfo->ucActiveFlg)
    {
        return;
    }

    /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-25, begin */
    if (NAS_MMC_MAX_CFG_DPLMN_NUM < *pulDestPlmnNum )
    {
        return;
    }
    /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-25, end */

    usSimRat = NAS_MMC_ConvertNetRatToSimRat(enNetType);

    for (i = 0; i < *pulDestPlmnNum; i++)
    {
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstCurrPlmn, &(pstDestPlmnIdList[i].stSimPlmnWithRat.stPlmnId)))
        {
            /* ���PLMN��ͬ��RATҲ��ͬ�򲻸��� */
            if ((usSimRat & pstDestPlmnIdList[i].stSimPlmnWithRat.usSimRat) == usSimRat)
            {
                return;
            }
            /*���PLMN��ͬ��RAT��ͬ */
            else
            {
                /* ����ѧϰ����,�������RAT */
                /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-21, begin */
                if (NAS_MMC_DPLMN_NPLMN_SELF_LEARING_TYPE == pstDestPlmnIdList[i].enType)
                {
                    pstDestPlmnIdList[i].stSimPlmnWithRat.usSimRat = usSimRat | pstDestPlmnIdList[i].stSimPlmnWithRat.usSimRat;
                    return;
                }
                /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-21, end */
            }
        }
    }

    /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-21, begin */
    if (VOS_FALSE == NAS_MMC_GetIndexOfFirstSelfLearningTypeElement(&usIndex, *pulDestPlmnNum, pstDestPlmnIdList))
    {
        return;
    }

    /* ����¼�¼ */
    if (*pulDestPlmnNum < NAS_MMC_MAX_CFG_DPLMN_NUM )
    {
        (VOS_VOID)PS_MEM_MOVE(&pstDestPlmnIdList[usIndex + 1], &pstDestPlmnIdList[usIndex],
                               (*pulDestPlmnNum - usIndex) * sizeof(NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU));

        pstDestPlmnIdList[usIndex].stSimPlmnWithRat.stPlmnId.ulMcc    = pstCurrPlmn->ulMcc;
        pstDestPlmnIdList[usIndex].stSimPlmnWithRat.stPlmnId.ulMnc    = pstCurrPlmn->ulMnc;
        pstDestPlmnIdList[usIndex].stSimPlmnWithRat.usSimRat          = usSimRat;
        pstDestPlmnIdList[usIndex].enRegDomain                        = enRegDomain;
        pstDestPlmnIdList[usIndex].enType                             = NAS_MMC_DPLMN_NPLMN_SELF_LEARING_TYPE;
        (*pulDestPlmnNum)++;
    }
    else
    {
        (VOS_VOID)PS_MEM_MOVE(&pstDestPlmnIdList[usIndex + 1], &pstDestPlmnIdList[usIndex],
                               (NAS_MMC_MAX_CFG_DPLMN_NUM - usIndex - 1) * sizeof(NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU));

        pstDestPlmnIdList[usIndex].stSimPlmnWithRat.stPlmnId.ulMcc    = pstCurrPlmn->ulMcc;
        pstDestPlmnIdList[usIndex].stSimPlmnWithRat.stPlmnId.ulMnc    = pstCurrPlmn->ulMnc;
        pstDestPlmnIdList[usIndex].stSimPlmnWithRat.usSimRat          = usSimRat;
        pstDestPlmnIdList[usIndex].enRegDomain                        = enRegDomain;
        pstDestPlmnIdList[usIndex].enType                             = NAS_MMC_DPLMN_NPLMN_SELF_LEARING_TYPE;
    }
    /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-21, end */

    return;
}

VOS_VOID  NAS_MMC_DeleteDPlmnNPlmnList(
    NAS_MML_PLMN_ID_STRU                   *pstCurrPlmn,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetType,
    NAS_MMC_REG_DOMAIN_ENUM_UINT8       enRegDomain,
    VOS_UINT16                                             *pulDestPlmnNum,
    NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU                  *pstDestPlmnIdList
)
{
    VOS_UINT32                                              i;
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    VOS_UINT16                                              usSimRat;
    VOS_UINT16                                              usTmpSimRat;

    pstDPlmnNPlmnCfgInfo     = NAS_MMC_GetDPlmnNPlmnCfgInfo();
    usSimRat                 = NAS_MML_INVALID_SIM_RAT;
    usTmpSimRat              = NAS_MML_INVALID_SIM_RAT;

    usSimRat = NAS_MMC_ConvertNetRatToSimRat(enNetType);

    if (VOS_TRUE != pstDPlmnNPlmnCfgInfo->ucActiveFlg)
    {
        return;
    }

    for (i = 0; i < *pulDestPlmnNum;)
    {
        if ( (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstCurrPlmn, &(pstDestPlmnIdList[i].stSimPlmnWithRat.stPlmnId)))
            /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-21, begin */
          && (NAS_MMC_DPLMN_NPLMN_SELF_LEARING_TYPE == pstDestPlmnIdList[i].enType)
            /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-21, end */
           )
        {
            usTmpSimRat = pstDestPlmnIdList[i].stSimPlmnWithRat.usSimRat & ~usSimRat;

            /*���PLMN��ͬ��RATҲ��ȫ��ͬ��ɾ��������¼*/
            if(usSimRat == pstDestPlmnIdList[i].stSimPlmnWithRat.usSimRat)
            {
                if (i < NAS_MMC_MAX_CFG_DPLMN_NUM - 1)
                {
                    (VOS_VOID)PS_MEM_MOVE(&pstDestPlmnIdList[i], &pstDestPlmnIdList[ i + 1 ],
                            ((*pulDestPlmnNum - i) - 1 ) * sizeof(NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU));
                }

                (*pulDestPlmnNum)--;

                if ( i > 0 )
                {
                    i--;
                }
                else
                {
                    continue;
                }
            }
            /*���PLMN��ͬ��RAT����RAT������һ����ɾ��������ʽ*/
            else if((usSimRat & pstDestPlmnIdList[i].stSimPlmnWithRat.usSimRat) == usSimRat)
            {
                pstDestPlmnIdList[i].stSimPlmnWithRat.usSimRat = usTmpSimRat;
            }
            else
            {

            }

        }

        i++;
    }
    return;
}

VOS_UINT16  NAS_MMC_ConvertNetRatToSimRat(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enPlmnNetRat
)
{
    VOS_UINT16                          usSimRat;

    usSimRat = NAS_MML_INVALID_SIM_RAT;

    if (NAS_MML_NET_RAT_TYPE_LTE == enPlmnNetRat)
    {
        usSimRat = NAS_MML_SIM_RAT_E_UTRN;
    }
    else if (NAS_MML_NET_RAT_TYPE_WCDMA == enPlmnNetRat)
    {
        usSimRat = NAS_MML_SIM_RAT_UTRN;
    }
    else if (NAS_MML_NET_RAT_TYPE_GSM == enPlmnNetRat)
    {
        usSimRat = NAS_MML_SIM_RAT_GSM;
    }
    else
    {
        usSimRat = NAS_MML_INVALID_SIM_RAT;
    }

    return usSimRat;

}


VOS_UINT32 NAS_MMC_IsBcchPlmnIdWithRatInDestSimPlmnList (
    NAS_MML_PLMN_WITH_RAT_STRU         *pstBcchPlmnIdWithRat,
    VOS_UINT16                          usSimPlmnWithRatNum,
    NAS_MML_SIM_PLMN_WITH_RAT_STRU     *pstSimPlmnWithRatList
)
{
    VOS_UINT32                          i;
    VOS_UINT16                          usBcchPlmnSimRat;

    usBcchPlmnSimRat = NAS_MMC_ConvertNetRatToSimRat(pstBcchPlmnIdWithRat->enRat);

    for ( i = 0; i < usSimPlmnWithRatNum; i++ )
    {
        if ( (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&pstBcchPlmnIdWithRat->stPlmnId,
                                                            &pstSimPlmnWithRatList[i].stPlmnId))
          && (usBcchPlmnSimRat == (pstSimPlmnWithRatList[i].usSimRat & usBcchPlmnSimRat)))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MMC_ComparePlmnIdWithRatWithUplmn (
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnIdWithRat
)
{
    NAS_MML_SIM_USERPLMN_INFO_STRU     *pstUserPlmnList = VOS_NULL_PTR;
    NAS_MML_SIM_OPERPLMN_INFO_STRU     *pstOperPlmnList = VOS_NULL_PTR;
    NAS_MML_SIM_SELPLMN_INFO_STRU      *pstSelPlmnList  = VOS_NULL_PTR;

    /* ��ȡUOPLMN */
    pstUserPlmnList = NAS_MML_GetSimUserPlmnList();
    pstOperPlmnList = NAS_MML_GetSimOperPlmnList();

    /* UPLMN������Ϊ0����OPLMN������Ϊ0 */
    if ((pstUserPlmnList->ucUserPlmnNum > 0)
     || (pstOperPlmnList->usOperPlmnNum > 0))
    {
        if (VOS_TRUE == NAS_MMC_IsBcchPlmnIdWithRatInDestSimPlmnList(pstPlmnIdWithRat,
                                                      pstUserPlmnList->ucUserPlmnNum,
                                                      pstUserPlmnList->astUserPlmnInfo))
        {
            return VOS_TRUE;
        }
    }
    else /* ��ʾ(U)SIM���в�����UPLMN��OPLMN��ʹ��PLMN Sel�ļ� */
    {
        pstSelPlmnList = NAS_MML_GetSimSelPlmnList();

        if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(&pstPlmnIdWithRat->stPlmnId,
                                                      pstSelPlmnList->ucSelPlmnNum,
                                                      pstSelPlmnList->astPlmnId))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
VOS_UINT32 NAS_MMC_ComparePlmnIdWithRatWithOplmn (
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnIdWithRat
)
{
    NAS_MML_SIM_USERPLMN_INFO_STRU     *pstUserPlmnList = VOS_NULL_PTR;
    NAS_MML_SIM_OPERPLMN_INFO_STRU     *pstOperPlmnList = VOS_NULL_PTR;
    NAS_MML_SIM_SELPLMN_INFO_STRU      *pstSelPlmnList  = VOS_NULL_PTR;

    /* ��ȡUOPLMN */
    pstUserPlmnList = NAS_MML_GetSimUserPlmnList();
    pstOperPlmnList = NAS_MML_GetSimOperPlmnList();

    /* UPLMN������Ϊ0����OPLMN������Ϊ0 */
    if ((pstUserPlmnList->ucUserPlmnNum > 0)
     || (pstOperPlmnList->usOperPlmnNum > 0))
    {
        if (VOS_TRUE == NAS_MMC_IsBcchPlmnIdWithRatInDestSimPlmnList(pstPlmnIdWithRat,
                                                      pstOperPlmnList->usOperPlmnNum,
                                                      pstOperPlmnList->astOperPlmnInfo))
        {
            return VOS_TRUE;
        }
    }
    else /* ��ʾ(U)SIM���в�����UPLMN��OPLMN��ʹ��PLMN Sel�ļ� */
    {
        pstSelPlmnList = NAS_MML_GetSimSelPlmnList();

        if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(&pstPlmnIdWithRat->stPlmnId,
                                                      pstSelPlmnList->ucSelPlmnNum,
                                                      pstSelPlmnList->astPlmnId))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
VOS_UINT32 NAS_MMC_IsPlmnIdWithSimRatInSimPlmnWithRegDomainList(
    NAS_MML_PLMN_ID_STRU                                   *pstPlmnId,
    VOS_UINT16                                              usSimRat,
    VOS_UINT32                                              ulDestPlmnNum,
    NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU                  *pstDestPlmnIdList
)
{
    VOS_UINT32                          i;

    for (i = 0; i < ulDestPlmnNum; i++)
    {
        if ((VOS_TRUE  == NAS_MML_CompareBcchPlmnwithSimPlmn(pstPlmnId, &(pstDestPlmnIdList[i].stSimPlmnWithRat.stPlmnId)))
         && ((usSimRat & pstDestPlmnIdList[i].stSimPlmnWithRat.usSimRat)  == usSimRat))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

NAS_MML_NET_RAT_TYPE_ENUM_UINT8  NAS_MMC_ConvertSimRatToNetRat(
    VOS_UINT16                          usSimRat
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatPrio = VOS_NULL_PTR;
    VOS_UINT16                          usConvertedSimRat;
    VOS_UINT32                          i;

    pstRatPrio = NAS_MML_GetMsPrioRatList();

    for (i = 0; i < pstRatPrio->ucRatNum; i++)
    {
        usConvertedSimRat = NAS_MMC_ConvertNetRatToSimRat(pstRatPrio->aucRatPrio[i]);

        if (usConvertedSimRat == (usConvertedSimRat & usSimRat))
        {
            return pstRatPrio->aucRatPrio[i];
        }
    }

    return NAS_MML_NET_RAT_TYPE_BUTT;
}


VOS_UINT32 NAS_MMC_IsPlmnIdWithRatInSimPlmnWithRegDomainList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstSrcPlmnId,
    VOS_UINT32                                              ulDestPlmnNum,
    NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU                  *pstDestPlmnIdList
)
{
    VOS_UINT32                          i;
    VOS_UINT16                          usSrcPlmnSimRat;

    for ( i = 0; i < ulDestPlmnNum; i++ )
    {
        usSrcPlmnSimRat = NAS_MMC_ConvertNetRatToSimRat(pstSrcPlmnId->enRat);

        if ((VOS_TRUE  == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstSrcPlmnId->stPlmnId), &(pstDestPlmnIdList[i].stSimPlmnWithRat.stPlmnId)))
         && (usSrcPlmnSimRat == (usSrcPlmnSimRat & pstDestPlmnIdList[i].stSimPlmnWithRat.usSimRat)))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}







VOS_UINT32 NAS_MMC_IsEnableLteTriggerPlmnSearch_ImsSwitchOnOrNotCsOnly(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;

    pstPrioRatList      = NAS_MML_GetMsPrioRatList();
    enFsmId             = NAS_MMC_GetCurrFsmId();

    /* ��߽��뼼�����ȼ�����LTE������Ҫ���� */
    if ((NAS_MML_NET_RAT_TYPE_LTE != pstPrioRatList->aucRatPrio[0]))
    {
        return VOS_FALSE;
    }

    /* ���CSҵ����ڲ���Ҫ���� */
    if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
    {
        return VOS_FALSE;
    }

    /* ON PLMN״̬��ʱ��Ҫ���� */
    if ((NAS_MMC_L1_STA_ON_PLMN == NAS_MMC_GetFsmTopState())
     && (NAS_MMC_FSM_L1_MAIN == enFsmId))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/* Added by y00307564 for CDMA Iteration 8 2015-3-3 begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_IsPlmnValid
 ��������  : �ж�PLMN�Ƿ���Ч
 �������  : NAS_MSCC_PIF_PLMN_ID_STRU          *pstPlmnId
 �������  : ��
 �� �� ֵ  : VOS_FALSE/VOS_TRUE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2015��03��03��
   ��    ��   : y00307564
   �޸�����   : Iteration 8����
*****************************************************************************/
VOS_BOOL NAS_MMC_IsPlmnValid(
    NAS_MSCC_PIF_PLMN_ID_STRU          *pstPlmnId
)
{
    VOS_UINT32                          i;

    for (i=0; i<3; i++)
    {
        if ((((pstPlmnId->ulMcc >> (i*4)) & 0x0F) > 9)
         || ((((pstPlmnId->ulMnc >> (i*4)) & 0x0F) > 9) && (i != 2 ))
         || ((((pstPlmnId->ulMnc >> (i*4)) & 0x0F) > 9) && (((pstPlmnId->ulMnc >> (i*4)) & 0x0F) != 0x0F)))
        {
            /* PLMN ID?? */
            return VOS_FALSE;
        }
    }
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_PlmnId2Bcd
 ��������  : ��PLMNת��ΪBCD��
 �������  : NAS_MSCC_PIF_PLMN_ID_STRU          *pstPlmnId
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2015��03��03��
   ��    ��   : y00307564
   �޸�����   : Iteration 8����
*****************************************************************************/
VOS_VOID NAS_MMC_PlmnId2Bcd(
    NAS_MSCC_PIF_PLMN_ID_STRU          *pstPlmnId
)
{
    VOS_UINT8                           ucI;
    VOS_UINT32                          ulTmp;
    VOS_UINT8                           aucTmp[4];

    ulTmp            = pstPlmnId->ulMcc;
    pstPlmnId->ulMcc = 0;
    for (ucI = 0 ;ucI < 3; ucI++)
    {
        aucTmp[ucI]     = ulTmp & 0x0f;
        ulTmp         >>=  8;
    }
    pstPlmnId->ulMcc = ((VOS_UINT32)aucTmp[0] << 8)
                      |((VOS_UINT32)aucTmp[1] << 4)
                      | aucTmp[2];

    ulTmp            = pstPlmnId->ulMnc;
    pstPlmnId->ulMnc = 0;
    for (ucI = 0; ucI < 3; ucI++)
    {
        aucTmp[ucI]     = ulTmp & 0x0f;
        ulTmp         >>=  8;
    }

    if (0xf == aucTmp[2])
    {
        pstPlmnId->ulMnc = ((VOS_UINT32)aucTmp[0] << 4)
                          |((VOS_UINT32)aucTmp[1] )
                          |0xf00;
    }
    else
    {
        pstPlmnId->ulMnc = ((VOS_UINT32)aucTmp[0] << 8)
                          |((VOS_UINT32)aucTmp[1] << 4)
                          | aucTmp[2];
    }
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_PlmnId2Bcd
 ��������  : ��PLMNת��ΪNasStyle��ʽ����
 �������  : NAS_MSCC_PIF_PLMN_ID_STRU          *pstPlmnId
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2015��03��03��
   ��    ��   : y00307564
   �޸�����   : Iteration 8����
*****************************************************************************/
VOS_VOID NAS_MMC_PlmnId2NasStyle(NAS_MSCC_PIF_PLMN_ID_STRU *pstPlmnId)
{
    VOS_UINT8   ucI;
    VOS_UINT8   aucTmp[4];
    VOS_UINT32  ulTmp;

    ulTmp           = pstPlmnId->ulMcc;
    pstPlmnId->ulMcc  = 0;
    for (ucI = 0; ucI < 3; ucI++)
    {
        aucTmp[ucI]     = ulTmp & 0x0f;
        ulTmp         >>=  4;
    }
    pstPlmnId->ulMcc  =  aucTmp[2]
                     |((VOS_UINT32)aucTmp[1] << 8)
                     |((VOS_UINT32)aucTmp[0] << 16);

    ulTmp           = pstPlmnId->ulMnc;
    pstPlmnId->ulMnc  = 0;
    for (ucI = 0; ucI < 3; ucI++)
    {
        aucTmp[ucI]     = ulTmp & 0x0f;
        ulTmp         >>=  4;
    }

    if (0xf == aucTmp[2])
    {
        pstPlmnId->ulMnc =  aucTmp[1]
                         |((VOS_UINT32)aucTmp[0] << 8)
                         |0x0f0000;
    }
    else
    {
        pstPlmnId->ulMnc =   aucTmp[2]
                     |((VOS_UINT32)aucTmp[1] << 8)
                     |((VOS_UINT32)aucTmp[0] << 16);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetUpdateFileForPrefPlmn
 ��������  : ����Pref PLMN�Ĳ���,ȷ����ǰҪ���µ��ļ�
 �������  : ��Ҫ���µ�USIM�ļ�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��03��03��
   ��    ��   : y00307564
   �޸�����   : Iteration 8����
*****************************************************************************/
VOS_UINT16 NAS_MMC_GetUpdateFileForPrefPlmn(
    NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8                       enPrefPLMNType
)
{
    VOS_UINT16                          usUpdateFile;
    NAS_MML_SIM_TYPE_ENUM_UINT8         enSimType;

    enSimType       = NAS_MML_GetSimType();
    usUpdateFile    = 0;

    if (NAS_MSCC_UPLMN_INFO == enPrefPLMNType)
    {
        if (NAS_MML_SIM_TYPE_USIM == enSimType)
        {/* 3G USIM */
            usUpdateFile = USIMM_USIM_EFPLMNWACT_ID;
        }
        else if (NAS_MML_SIM_TYPE_SIM == enSimType)
        {/* 2G SIM */
            usUpdateFile = USIMM_GSM_EFPLMNWACT_ID;
        }
        else
        {
            usUpdateFile = USIMM_DEF_FILEID_BUTT;
        }
    }
    else if (NAS_MSCC_PLMNSEL_INFO == enPrefPLMNType)
    {
        usUpdateFile = USIMM_GSM_EFPLMNSEL_ID;
    }
    else if (NAS_MSCC_OPLMN_INFO == enPrefPLMNType)
    {
        if (NAS_MML_SIM_TYPE_USIM == enSimType)
        {/* 3G USIM */
            usUpdateFile = USIMM_USIM_EFOPLMNWACT_ID;
        }
        else if (NAS_MML_SIM_TYPE_SIM == enSimType)
        {/* 2G SIM */
            usUpdateFile = USIMM_GSM_EFOPLMNWACT_ID;
        }
        else
        {
            usUpdateFile = USIMM_DEF_FILEID_BUTT;
        }
    }
    else
    {
        if (NAS_MML_SIM_TYPE_USIM == enSimType)
        {/* 3G USIM */
            usUpdateFile = USIMM_USIM_EFHPLMNwACT_ID;
        }
        else if (NAS_MML_SIM_TYPE_SIM == enSimType)
        {/* 2G SIM */
            usUpdateFile = USIMM_GSM_EFHPLMNACT_ID;
        }
        else
        {
            usUpdateFile = USIMM_DEF_FILEID_BUTT;
        }
    }

    return usUpdateFile;
}
/* Added by y00307564 for CDMA Iteration 8 2015-3-3 end */

VOS_UINT32 NAS_MMC_GetWaitAsResumeIndTimerLen(VOS_VOID)
{
    if (VOS_TRUE == NAS_MML_IsDsdsMultiModemMode())
    {
        return TI_NAS_MMC_DSDS_WAIT_AS_RESUME_IND_LEN;
    }

    return TI_NAS_MMC_WAIT_AS_RESUME_IND_LEN;
}


VOS_UINT32 NAS_MMC_GetWaitGUTAsRedirResumeIndTimerLen(VOS_VOID)
{
    if (VOS_TRUE == NAS_MML_IsDsdsMultiModemMode())
    {
        return TI_NAS_MMC_DSDS_INTER_SYS_GU_REDIR_WAIT_AS_RESUME_IND_LEN;
    }

    return TI_NAS_MMC_INTER_SYS_GU_REDIR_WAIT_AS_RESUME_IND_LEN;
}


VOS_UINT32 NAS_MMC_GetWaitAsOosResumeIndTimerLen(VOS_VOID)
{
    if (VOS_TRUE == NAS_MML_IsDsdsMultiModemMode())
    {
        return TI_NAS_MMC_DSDS_INTER_SYS_OOS_WAIT_AS_RESUME_IND_LEN;
    }

    return TI_NAS_MMC_INTER_SYS_OOS_WAIT_AS_RESUME_IND_LEN;
}




#if (FEATURE_ON == FEATURE_LTE)

VOS_UINT32 NAS_MMC_IsDetachReqestDisableLte(
    NAS_MMC_DETACH_TYPE_ENUM_UINT32     enDetachType,
    NAS_MMC_DETACH_REASON_ENUM_UINT32   enDetachReason
)
{
    if (((NAS_MSCC_PIF_DETACH_REASON_USER_DETACH       == enDetachReason)
      || (NAS_MSCC_PIF_DETACH_REASON_SRV_DOMAIN_DETACH == enDetachReason))
     && (NAS_MSCC_PIF_DETACH_TYPE_GPRS            == enDetachType))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
#endif



VOS_VOID NAS_MMC_ConvertMsccHighPrioPlmnListToMmcPlmnListInfo(
    NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU              *pstHighPrioPlmnInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstMmcPlmnListInfo
)
{
    VOS_UINT32                          i;

    if (VOS_NULL_PTR == pstHighPrioPlmnInfo)
    {
        return;
    }

    pstMmcPlmnListInfo[0].enRatType     = pstHighPrioPlmnInfo->enRat;
    pstMmcPlmnListInfo[0].enCoverType   = NAS_MMC_COVERAGE_TYPE_HIGH;

    pstMmcPlmnListInfo[0].ulHighPlmnNum = pstHighPrioPlmnInfo->ucHighPlmnNum;
    if (pstMmcPlmnListInfo[0].ulHighPlmnNum > NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM)
    {
        pstMmcPlmnListInfo[0].ulHighPlmnNum = NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM;
    }

    for (i = 0; i < (pstMmcPlmnListInfo[0].ulHighPlmnNum); i++)
    {
        pstMmcPlmnListInfo[0].astHighPlmnList[i].ulMcc = pstHighPrioPlmnInfo->astHighPlmnID[i].ulMcc;

        pstMmcPlmnListInfo[0].astHighPlmnList[i].ulMnc = pstHighPrioPlmnInfo->astHighPlmnID[i].ulMnc;
    }

    pstMmcPlmnListInfo[0].ulLowPlmnNum  = pstHighPrioPlmnInfo->ucLowPlmnNum;
    if (pstMmcPlmnListInfo[0].ulLowPlmnNum > NAS_MMC_INTRA_MAX_LOW_QUALITY_PLMN_NUM)
    {
        pstMmcPlmnListInfo[0].ulHighPlmnNum = NAS_MMC_INTRA_MAX_LOW_QUALITY_PLMN_NUM;
    }

    for (i = 0; i < (pstMmcPlmnListInfo[0].ulLowPlmnNum); i++)
    {
        pstMmcPlmnListInfo[0].astLowPlmnList[i].stPlmnId.ulMcc = pstHighPrioPlmnInfo->astLowPlmnID[i].ulMcc;

        pstMmcPlmnListInfo[0].astLowPlmnList[i].stPlmnId.ulMnc = pstHighPrioPlmnInfo->astLowPlmnID[i].ulMnc;
    }

    return;
}


NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32 NAS_MMC_GetPlmnSearchSceneMsccPlmnSrchReq(
    MSCC_MMC_PLMN_SEARCH_REQ_STRU      *pstPlmnSrchReq
)
{
    if (NAS_MSCC_PIF_ACQ_REASON_POWER_UP == pstPlmnSrchReq->enAcqReason)
    {
        return NAS_MMC_PLMN_SEARCH_SCENE_SWITCH_ON;
    }

    if (NAS_MSCC_PIF_ACQ_REASON_HIGH_PRIORITY == pstPlmnSrchReq->enAcqReason)
    {
        return NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_LTE_PLMN_SEARCH;
    }

    if (NAS_MSCC_PIF_ACQ_REASON_OTHER == pstPlmnSrchReq->enAcqReason)
    {
        return NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST;
    }

    return NAS_MMC_PLMN_SEARCH_SCENE_BUTT;
}




VOS_VOID   NAS_MMC_ConvertMsccRatTypeToMml3GPP2RatType(
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enMsccRatType,
    NAS_MML_3GPP2_RAT_TYPE_ENUM_UINT8                      *penMml3GPP2RatType
)
{
    switch (enMsccRatType)
    {
        case NAS_MSCC_PIF_NET_RAT_TYPE_1X:

            *penMml3GPP2RatType = NAS_MML_3GPP2_RAT_TYPE_CDMA1X;
            break;

        case NAS_MSCC_PIF_NET_RAT_TYPE_HRPD:

            *penMml3GPP2RatType = NAS_MML_3GPP2_RAT_TYPE_HRPD;
            break;

        default:

            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ConvertMsccRatTypeToMml3GPP2RatType TYPE ERROR!!!");
            *penMml3GPP2RatType = NAS_MML_3GPP2_RAT_TYPE_BUTT;
            break;
    }

    return;
}



VOS_UINT32  NAS_MMC_IsRatPrioChangeTriggerPlmnSrch(
    NAS_MSCC_PIF_RAT_PRIO_STRU         *pstOldRatList,
    NAS_MSCC_PIF_RAT_PRIO_STRU         *pstNewRatList
)
{
    VOS_UINT32                               ulCurrRatIndex;                         /* ��ǰ���뼼�������ȼ����б��index,0��ߣ�2��� */
    VOS_UINT8                                ucNewRatNum;                            /* �������뼼������  */
    VOS_UINT8                                ucOldRatNum;                            /* ԭ�н��뼼������  */
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8    *pstNewRatPrio = VOS_NULL_PTR;           /* �����������ȼ����б� index��ʾ���ȼ�����,0��ߣ�2��� */
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8    *pstOldRatPrio = VOS_NULL_PTR;           /* ԭ�н������ȼ����б� index��ʾ���ȼ�����,0��ߣ�2��� */
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8          enCurrRat;
    VOS_UINT8                                ucOldRatIndex;
    VOS_UINT8                                ucNewRatIndex;


    /* ȡ�������������ȸ��� */
    ucNewRatNum        = pstNewRatList->ucRatNum;

    /* ȡ�������������ȼ��б� */
    pstNewRatPrio      = pstNewRatList->aucRatPrio;


    /* ȡ�õ�ǰ�Ľ���ģʽ */
    enCurrRat          = NAS_MML_GetCurrNetRatType();

    /* ȡ��ԭ�еĽ������ȸ��� */
    ucOldRatNum        = pstOldRatList->ucRatNum;

    /* ȡ��ԭ�еĽ������ȼ��б� */
    pstOldRatPrio      = pstOldRatList->aucRatPrio;

    if ( (0 == ucNewRatNum)
      || (0 == ucOldRatNum) )
    {
        return VOS_FALSE;
    }

    /* ��ǰ���뼼�����µ����ȼ��б����index, 0��ߣ�2���  */
    ulCurrRatIndex = NAS_MML_GetRatIndexInPrioRatList(enCurrRat, pstNewRatList);

    /* ��ǰ���뼼�����µ����ȼ��б���û�У�����true */
    if (NAS_MML_INVALID_INDEX == ulCurrRatIndex)
    {
        return VOS_TRUE;
    }

    /* ��������:1��SysSet�������˽��뼼�� */
    /*          2�������Ľ��뼼�����ȼ����ڵ�ǰפ�����뼼�� */
    for (ucNewRatIndex = 0; ucNewRatIndex < ucNewRatNum; ucNewRatIndex++)
    {
        for (ucOldRatIndex = 0; ucOldRatIndex < ucOldRatNum; ucOldRatIndex++)
        {
            if (pstNewRatPrio[ucNewRatIndex] == pstOldRatPrio[ucOldRatIndex])
            {
                /* SysSet��ĳ�����뼼���ڵ�ǰ���뼼���� */
                break;
            }
        }

        /* ��ԭ�н��뼼���б��У������ڣ���ʾ��������  */
        if (ucOldRatIndex == ucOldRatNum)
        {
            /* ���ж��������뼼���ڽ��뼼���б�������� �Ƿ�С�� ��ǰ���뼼���ڽ��뼼���б�������� */
            if ((VOS_UINT32)ucNewRatIndex < ulCurrRatIndex)
            {
                return VOS_TRUE;
            }
        }

    }


    /* Ĭ�ϲ���Ҫ���и����ȼ��б����� */
    return VOS_FALSE;
}


/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-26, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_StartPlmnSearchPhaseOneTotalTimer
 ��������  : ��������������һ�׶�������ʱ����ƶ�ʱ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_TRUE: TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER �����ɹ�
             VOS_FALSE: TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��26��
    ��    ��   : c00318887
    �޸�����   : �½�

*****************************************************************************/
VOS_UINT32 NAS_MMC_StartPlmnSearchPhaseOneTotalTimer(VOS_VOID)
{
    NAS_MML_AVAIL_TIMER_CFG_STRU                 *pstAvailTimerCfg        = VOS_NULL_PTR;
    NAS_MMC_HISTORY_SEARCH_INFO_STRU             *pstHistoryinfo          = VOS_NULL_PTR;
    VOS_UINT32                                    ulNormalCount;
    VOS_UINT32                                    ulPhaseOneTotalTimeLen;  

    pstAvailTimerCfg                            = NAS_MML_GetAvailTimerCfg();
    ulNormalCount                               = NAS_MMC_GetCurNormalAvailableTimerCount_L1Main();
    ulPhaseOneTotalTimeLen                      = NAS_MML_GetPlmnSearchPhaseOneTotalTimerLen();
    pstHistoryinfo                              = NAS_MMC_GetHistorySearchInfo();

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_StartPlmnSearchPhaseOneTotalTimer entered.");

    /* ����Ѿ��������ڶ��׶Σ������� */
    if (ulNormalCount >= pstAvailTimerCfg->ulFirstSearchTimeCount)
    {
        NAS_WARNING_LOG1(WUEPS_PID_MMC, "NAS_MMC_StartPlmnSearchPhaseOneTotalTimer WANRING: ue is in plmn search phaseII", ulNormalCount);
    
        return VOS_FALSE;
    }

    /* no rf �������� */
    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_StartPlmnSearchPhaseOneTotalTimer:WARNING: no rf");
    
        return VOS_FALSE;
    }

    /* nv����û��������Control��ʱ�� */
    if (VOS_FALSE == NAS_MML_GetPlmnSearchPhaseOneTotalTimerActiveFlag())
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_StartPlmnSearchPhaseOneTotalTimer:WARNING: nv not active");
    
        return VOS_FALSE;
    }
    
    /* histroy ������һ�׶���ʱ�� С�� HISTORY ʱ���������� */
    if ( (VOS_TRUE == pstHistoryinfo->ucActiveFlg)
      && (ulPhaseOneTotalTimeLen < pstHistoryinfo->ulFirstTimerLen))
    {
        NAS_WARNING_LOG2(WUEPS_PID_MMC, "NAS_MMC_StartPlmnSearchPhaseOneTotalTimer:WARNING: PhaseOneTotalTimeLen, historyFirstTimerLen", 
                        ulPhaseOneTotalTimeLen, pstHistoryinfo->ulFirstTimerLen);
    
        return VOS_FALSE;
    }
   
    if (VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER,
                                       ulPhaseOneTotalTimeLen * NAS_MML_ONE_THOUSAND_MILLISECOND))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_StartPlmnSearchPhaseOneTotalTimer START SUCC.");
        return VOS_TRUE;
    }
    
    NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_StartPlmnSearchPhaseOneTotalTimer:info: START TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER IS FALSE");

    return VOS_FALSE;
}
/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-26, end */

NAS_ERR_LOG_RATMODE_ENUM_UINT8 NAS_MMC_ConvertRatTypeFromNasMsccToNasErr (
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8 msccRatType
)
{
    NAS_ERR_LOG_RATMODE_ENUM_UINT8 errRatType;
    switch (msccRatType)
    {
        case NAS_MSCC_PIF_NET_RAT_TYPE_GSM:           /* GSM���뼼�� */
            errRatType = NAS_ERR_LOG_RATMODE_GSM;
            break;
        case NAS_MSCC_PIF_NET_RAT_TYPE_WCDMA:         /* WCDMA���뼼�� */
            errRatType = NAS_ERR_LOG_RATMODE_WCDMA;
            break;
        case NAS_MSCC_PIF_NET_RAT_TYPE_LTE:           /* LTE���뼼�� */
            errRatType = NAS_ERR_LOG_RATMODE_LTE;
            break;
        default:
            NAS_TRACE_HIGH("NAS_MMC_ConvertRatTypeFromNasMsccToNasErr: Convert rat(%d) to BUTT", msccRatType);
            errRatType = NAS_ERR_LOG_RATMODE_BUTT;
            break;
    }

    return errRatType;
}
#if (FEATURE_ON == FEATURE_PTM)
VOS_VOID NAS_MMC_RecordFftSrchMccInfo( VOS_VOID )
{
    NAS_MML_ERRLOG_FFT_SRCH_INFO_STRU          *pstGeoSrchInfo = VOS_NULL_PTR;
    NAS_ERR_LOG_FFT_SRCH_MCC_PROC_INFO_STRU     stProcInfoEvent;
    VOS_UINT32                                  ulIsLogNeedRecord;
    VOS_UINT32                                  ulLength;
    VOS_UINT32                                  ulResult;
    VOS_UINT16                                  usLevel;

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel             = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_FFT_SRCH_MCC_INFO);
    ulIsLogNeedRecord   = NAS_MML_IsErrLogNeedRecord(usLevel);

    /* NV���ò���Ҫ��¼ */
    if (VOS_FALSE == ulIsLogNeedRecord)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RecordFftSrchMccInfo,ERROR:log nv disable or low level");
        return;
    }

    NAS_TRACE_HIGH("NAS_MMC_RecordFftSrchMccInfo(): recording ");

    ulLength = sizeof(NAS_ERR_LOG_FFT_SRCH_MCC_PROC_INFO_STRU);

    /* ��䱾�ؼ�¼��Ϣ */
    PS_MEM_SET(&stProcInfoEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stProcInfoEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_MMC),
                                      NAS_ERR_LOG_ALM_FFT_SRCH_MCC_INFO,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    pstGeoSrchInfo = NAS_MML_GetErrLogFftSrchInfoAddr();
    stProcInfoEvent.ulSrchStartSlice  = pstGeoSrchInfo->ulSrchStartSlice;
    stProcInfoEvent.ulSrchFinishSlice = pstGeoSrchInfo->ulSrchFinishSlice;

    /* ת��GetGeo������MCC������ɹ�����ʧ�ܣ��Լ�ʧ�ܵ�ԭ�� */
    if (NAS_MMC_GET_GEO_SUCCESS == pstGeoSrchInfo->ucSrchRslt)
    {
        stProcInfoEvent.ucSrchRslt  = VOS_TRUE;
        stProcInfoEvent.ucFailCause = 0;

        /* ת��MCC�Ľ��뼼����ʽ */
        stProcInfoEvent.enMccRatType = NAS_MMC_ConvertRatTypeFromNasMsccToNasErr(pstGeoSrchInfo->enMccRatType);

    }
    else
    {
        stProcInfoEvent.ucSrchRslt   = VOS_FALSE;
        stProcInfoEvent.ucFailCause  = pstGeoSrchInfo->ucSrchRslt;

        /* δ�ҵ�MCC����ʼ����ǰ��ʽΪĬ��ֵ */
        stProcInfoEvent.enMccRatType = NAS_ERR_LOG_RATMODE_BUTT;
    }


    /* ��¼CSS Multi Band Scan�Ľ�� */
    stProcInfoEvent.stMultiBandScanInfo.ucResult                = (VOS_UINT8)pstGeoSrchInfo->stCssBandScanInfo.enResult;
    stProcInfoEvent.stMultiBandScanInfo.ulBandScanStartSlice    = pstGeoSrchInfo->stCssBandScanInfo.ulBandScanStartSlice;
    stProcInfoEvent.stMultiBandScanInfo.ulBandScanFinishSlice   = pstGeoSrchInfo->stCssBandScanInfo.ulBandScanFinishSlice;
    stProcInfoEvent.stMultiBandScanInfo.ucGsmCoverageType       = (VOS_UINT8)pstGeoSrchInfo->stCssBandScanInfo.enGsmCoverageType;
    stProcInfoEvent.stMultiBandScanInfo.ucLteCoverageType       = (VOS_UINT8)pstGeoSrchInfo->stCssBandScanInfo.enLteCoverageType;
    stProcInfoEvent.stMultiBandScanInfo.ucUmtsFddCoverageType   = (VOS_UINT8)pstGeoSrchInfo->stCssBandScanInfo.enUmtsFddCoverageType;

    /* ��յ�FFT����MCCȫ�ֱ�����Ϣ */
    NAS_MML_InitErrLogFftSrchInfo();

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = NAS_MML_PutErrLogRingBuf((VOS_CHAR *)&stProcInfoEvent, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RecordFftSrchMccInfo(): Push buffer error.");
    }

    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_FFT_SRCH_MCC_INFO,
                           WUEPS_PID_MMC,
                           (VOS_UINT8 *)&stProcInfoEvent,
                           sizeof(stProcInfoEvent));

    return;
}
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



