/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMmlLib.c
  �� �� ��   : ����
  ��    ��   : zhoujun 40661
  ��������   : 2011��7��25��
  ����޸�   : 2011��7��25��
  ��������   : MML_CTX�Ķ����ṩ�⺯��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��7��25��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ļ�

****************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "PsLib.h"

#include "PsCommonDef.h"
#include "NasComm.h"
#include "NasMmlCtx.h"
#include "UsimPsInterface.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#include "MmLmmInterface.h"
#endif
#include "NasMmlLib.h"
#include "GmmExt.h"
#include "NasMmcSndLmm.h"

#include "zlib.h"
#include "NVIM_Interface.h"
#include "NasUsimmApi.h"
#include "NasMmlCtx.h"

#include "NasMmcSndOm.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*****************************************************************************
  2 ��������
*****************************************************************************/

#define THIS_FILE_ID PS_FILE_ID_NASMML_LIB_C

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  4 ��������
*****************************************************************************/

/*****************************************************************************
  5 ��������
*****************************************************************************/

/*****************************************************************************
  6 ��������
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
 �� �� ��  : NAS_MML_GetCsServiceExistFlg
 ��������  : ��ȡCS��ҵ��Ĵ������,������ǰCSҵ��ͻ����CSҵ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:CSҵ�����
             VOS_FALSE:CSҵ�񲻴���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��16��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MML_GetCsServiceExistFlg( VOS_VOID )
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;

    pstConnStatus   = NAS_MML_GetConnStatus();

    /* CS���л���ҵ����� */
    if ( VOS_TRUE == pstConnStatus->ucCsServiceBufferFlg)
    {
        return VOS_TRUE;
    }

    /* CS���е�ǰҵ����� */
    if ( VOS_TRUE == pstConnStatus->ucCsServiceConnStatusFlg)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32  NAS_MML_GetPsServiceExistFlg( VOS_VOID )
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus;

    pstConnStatus     = NAS_MML_GetConnStatus();


    /* L�µ��жϹ�����ȫ������LMM�ϱ�����·״̬ */
#if (FEATURE_ON == FEATURE_LTE)
    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        /* PS���е�ǰҵ����� */
        if ( VOS_TRUE == pstConnStatus->ucEpsServiceConnStatusFlg)
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }
#endif

    /* GU�µ��жϹ�������Ҫ����PDP����״̬��RRC��·״̬ */

    /* PS���л���ҵ�����,�˱�־��ʱ���ø���,��Ҫԭ��Ϊ��ǰMMC��������Ҫ�ж�GMM�Ļ���ҵ�� */
    if ( VOS_TRUE == pstConnStatus->ucPsServiceBufferFlg)
    {
        return VOS_TRUE;
    }


    /* GSM�µ�ǰPDP״̬������TBF��·������Ϊ��ǰPS��ҵ����� */
    if ((NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
     && (VOS_TRUE == pstConnStatus->ucPdpStatusFlg)
     && (VOS_TRUE == pstConnStatus->ucPsTbfStatusFlg))
    {
        return VOS_TRUE;
    }

    /* W�µ�ǰPDP״̬����ʱ��PS�������Ӻ�RRC��������Ϊ����PSҵ�� */
    if ((NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
     && (VOS_TRUE == pstConnStatus->ucPdpStatusFlg)
     && (VOS_TRUE == pstConnStatus->ucRrcStatusFlg))
    {
        return VOS_TRUE;
    }

    /* PS�򴥷���TC����ҵ����� */
    if ( VOS_TRUE == pstConnStatus->ucPsTcServiceFlg )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT32 NAS_MML_IsNorthAmericanMcc(
    VOS_UINT32                          ulMcc
)
{
    if ((NAS_MML_PCS1900_MCC_LOW_VALUE == (ulMcc & NAS_MML_MCC_LOW_VALUE_MASK))
     && (NAS_MML_PCS1900_MCC_HIGH_VALUE_RANGE >= (ulMcc & NAS_MML_MCC_THIRD_BYTE_VALUE_MASK)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MML_IsIndianMcc(
    VOS_UINT32                          ulMcc
)
{
    /* 404-406Ϊӡ�ȹ����� */
    if ((NAS_MML_INDIA_MCC_LOW_VALUE == (ulMcc & NAS_MML_MCC_LOW_VALUE_MASK))
     && (NAS_MML_INDIA_MCC_LOW_VALUE_RANGE <= (ulMcc & NAS_MML_MCC_THIRD_BYTE_VALUE_MASK))
     && (NAS_MML_INDIA_MCC_HIGH_VALUE_RANGE >= (ulMcc & NAS_MML_MCC_THIRD_BYTE_VALUE_MASK)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_VOID NAS_MML_SetBitValueToBuffer(
    VOS_UINT8                          *pucDataBuf,
    VOS_UINT32                          ulBitNo,
    VOS_UINT8                           ucValue
)
{
    VOS_UINT32                          ulOffset;
    VOS_UINT8                           ucBit;

    if (0 == ulBitNo)
    {
        return;
    }

    ulOffset = (ulBitNo - 1) / NAS_MML_OCTET_EIGHT_BITS;

    ucBit    = (VOS_UINT8)((ulBitNo - 1)% NAS_MML_OCTET_EIGHT_BITS);

    if (0 != ucValue)
    {
        /*lint -e701 */
        pucDataBuf[ulOffset] |= (VOS_UINT8)(NAS_MML_OCTET_MOVE_ONE_BITS << ucBit);
        /*lint +e701 */
    }
    else
    {
        /*lint -e701 */
        pucDataBuf[ulOffset] &= (~(VOS_UINT8)(NAS_MML_OCTET_MOVE_ONE_BITS << ucBit));
        /*lint +e701 */
    }

    return;
}


VOS_UINT8 NAS_MML_GetBitValueFromBuffer(
    VOS_UINT8                          *pucDataBuf,
    VOS_UINT32                          ulBitNo
)
{
    VOS_UINT32                          ulOffset;
    VOS_UINT8                           ucBit;

    if (0 == ulBitNo)
    {
        return 0;
    }

    ulOffset = (ulBitNo - 1)/ NAS_MML_OCTET_EIGHT_BITS;

    ucBit    = (VOS_UINT8)((ulBitNo - 1) % NAS_MML_OCTET_EIGHT_BITS);

    return (pucDataBuf[ulOffset] >> ucBit)& 0x1;
}


VOS_UINT8 NAS_MML_IsUeSupportImsVoice(VOS_VOID)
{
    VOS_UINT8                                               ucVoiceOnIms;
    NAS_MML_VOICE_DOMAIN_PREFERENCE_ENUM_UINT8              enVoiceDomainPreference;


    enVoiceDomainPreference = NAS_MML_GetVoiceDomainPreference();
    ucVoiceOnIms    = NAS_MML_GetVoiceCallOnImsSupportFlag();

    /* �ܿؿ���δ��ʱ����ΪUE��֧��IMS */
    if (VOS_FALSE == NAS_MML_GetLteImsSupportFlg())
    {
        return VOS_FALSE;
    }

    /* ֧��IMS ������voice domain nv���ò���cs only�򷵻�VOS_TRUE */
    if ((VOS_TRUE == ucVoiceOnIms)
     && (NAS_MML_CS_VOICE_ONLY != enVoiceDomainPreference))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_UINT32 NAS_MML_ComparePlmnMcc(
    VOS_UINT32                          ulSrcMcc,
    VOS_UINT32                          ulDestMcc
)
{
    VOS_UINT32                          ulSrcMccUsaMccFlag;
    VOS_UINT32                          ulDestMccUsaMccFlag;
    VOS_UINT32                          ulSrcMccIndianMccFlag;
    VOS_UINT32                          ulDestMccIndianMccFlag;

    ulSrcMccUsaMccFlag     = NAS_MML_IsNorthAmericanMcc(ulSrcMcc);
    ulDestMccUsaMccFlag    = NAS_MML_IsNorthAmericanMcc(ulDestMcc);
    ulSrcMccIndianMccFlag  = NAS_MML_IsIndianMcc(ulSrcMcc);
    ulDestMccIndianMccFlag = NAS_MML_IsIndianMcc(ulDestMcc);

    if (((VOS_TRUE == ulSrcMccUsaMccFlag)
       && (VOS_TRUE == ulDestMccUsaMccFlag))
      || ((VOS_TRUE == ulSrcMccIndianMccFlag)
       && (VOS_TRUE == ulDestMccIndianMccFlag)))
    {
        return VOS_TRUE;
    }
    else
    {
        if (ulDestMcc != ulSrcMcc)
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}



VOS_UINT32 NAS_MML_ExactlyCompareBcchPlmnwithSimPlmn(
    NAS_MML_PLMN_ID_STRU                *pstBccPlmnId,
    NAS_MML_PLMN_ID_STRU                *pstSimPlmnId
)
{
    VOS_UINT8                           ucBcchMnc3;
    VOS_UINT8                           ucSimMnc3;

    if (pstBccPlmnId->ulMcc == pstSimPlmnId->ulMcc)
    {
        if (pstBccPlmnId->ulMnc == pstSimPlmnId->ulMnc)
        {
            return VOS_TRUE;
        }
        else if ((pstBccPlmnId->ulMnc & NAS_MML_MCC_LOW_VALUE_MASK)
              == (pstSimPlmnId->ulMnc & NAS_MML_MCC_LOW_VALUE_MASK))
        {
            ucBcchMnc3 = (VOS_UINT8)((pstBccPlmnId->ulMnc & NAS_MML_MCC_THIRD_BYTE_VALUE_MASK) >> 16);
            ucSimMnc3  = (VOS_UINT8)((pstSimPlmnId->ulMnc & NAS_MML_MCC_THIRD_BYTE_VALUE_MASK) >> 16);

            /* PLMN ���� NA PCS1900*/
            if ((NAS_MML_PCS1900_MCC_LOW_VALUE == (pstBccPlmnId->ulMcc & NAS_MML_MCC_LOW_VALUE_MASK))
             && (NAS_MML_PCS1900_MCC_HIGH_VALUE_RANGE >= (pstBccPlmnId->ulMcc & NAS_MML_MCC_THIRD_BYTE_VALUE_MASK)))
            {
                if ( ((NAS_MML_PCS1900_MNC_THIRD_BYTE_VALUE_F == ucBcchMnc3)
                 && (NAS_MML_PCS1900_MNC_THIRD_BYTE_VALUE_0 == ucSimMnc3))
                 || ((NAS_MML_PCS1900_MNC_THIRD_BYTE_VALUE_0 == ucBcchMnc3)
                 && (NAS_MML_PCS1900_MNC_THIRD_BYTE_VALUE_F == ucSimMnc3)) )
                {
                    return VOS_TRUE;
                }
            }
        }
        else
        {
        }
    }

    return VOS_FALSE;
}
VOS_UINT32 NAS_MML_CompareBcchPlmnwithSimPlmn(
    NAS_MML_PLMN_ID_STRU                *pstBccPlmnId,
    NAS_MML_PLMN_ID_STRU                *pstSimPlmnId
)
{
    VOS_BOOL                            bCmpRlst;
    VOS_UINT8                           ucBcchMnc3;
    VOS_UINT8                           ucSimMnc3;

    bCmpRlst   = VOS_FALSE;

    /* �����Ҫ��ȷ�Ƚ�MNC*/
    if (VOS_TRUE == NAS_MML_GetPlmnExactlyComparaFlg())
    {
        bCmpRlst = NAS_MML_ExactlyCompareBcchPlmnwithSimPlmn(pstBccPlmnId, pstSimPlmnId);

        return bCmpRlst;
    }

    /* HPLMN Matching Criteria for mobiles which support PCS1900 for NA:
    1) The MS shall compare using all 3 digits the SIM-MCC with the BCCH-MCC.
    If the values do not match, then the HPLMN match fails*/
    if (pstBccPlmnId->ulMcc == pstSimPlmnId->ulMcc)
    {
        /*The MS shall compare using all 3 digits the SIM-MNC with the BCCH-MNC.
          If the values match, then the HPLMN match succeeds*/
        if (pstBccPlmnId->ulMnc == pstSimPlmnId->ulMnc)
        {
            bCmpRlst = VOS_TRUE;
        }
        else if ((pstBccPlmnId->ulMnc & NAS_MML_MCC_LOW_VALUE_MASK)
              == (pstSimPlmnId->ulMnc & NAS_MML_MCC_LOW_VALUE_MASK))
        {
            /* ȡMNC�����λ ,�����λ��0��F����2λMnc��ͬ����ΪPlmn��� */
            ucBcchMnc3 = (VOS_UINT8)((pstBccPlmnId->ulMnc & NAS_MML_MCC_THIRD_BYTE_VALUE_MASK) >> 16);
            ucSimMnc3  = (VOS_UINT8)((pstSimPlmnId->ulMnc & NAS_MML_MCC_THIRD_BYTE_VALUE_MASK) >> 16);

            /* PLMN ���� NA PCS1900*/
            if ((NAS_MML_PCS1900_MCC_LOW_VALUE == (pstBccPlmnId->ulMcc & NAS_MML_MCC_LOW_VALUE_MASK))
             && (NAS_MML_PCS1900_MCC_HIGH_VALUE_RANGE >= (pstBccPlmnId->ulMcc & NAS_MML_MCC_THIRD_BYTE_VALUE_MASK)))
            {
                if ( ((NAS_MML_PCS1900_MNC_THIRD_BYTE_VALUE_F == ucBcchMnc3)
                   && (NAS_MML_PCS1900_MNC_THIRD_BYTE_VALUE_0 == ucSimMnc3))
                  || ((NAS_MML_PCS1900_MNC_THIRD_BYTE_VALUE_0 == ucBcchMnc3)
                   && (NAS_MML_PCS1900_MNC_THIRD_BYTE_VALUE_F == ucSimMnc3)) )
                {
                    bCmpRlst = VOS_TRUE;
                }
            }
            else
            {
                /* The MS shall compare using just the 1st 2 digits of the SIM-MNC
                with the BCCH-MNC. If the values match, then the HPLMN match succeeds,
                otherwise the HPLMN match fails.*/
                if (NAS_MML_LOW_BYTE_INVALID == ucBcchMnc3)
                {
                    bCmpRlst = VOS_TRUE;
                }
            }
        }
        else
        {
        }

    }

    return bCmpRlst;
}


VOS_UINT32 NAS_MML_IsNetRatSupported(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enSpecRat
)
{
    VOS_UINT32                          i;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatList = VOS_NULL_PTR;

    pstRatList = NAS_MML_GetMsPrioRatList();

    /* ָ���Ľ��뼼���Ƿ��ڵ�ǰ�û����õ�RAT�б��� */
    for (i = 0 ; i < pstRatList->ucRatNum; i++)
    {
        if ( (enSpecRat == pstRatList->aucRatPrio[i])
          && (enSpecRat < NAS_MML_NET_RAT_TYPE_BUTT))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
VOS_UINT32 NAS_MML_IsSpecRatInRatList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enSpecRat,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatList
)
{
    VOS_UINT32                          i;

    /* ָ���Ľ��뼼���Ƿ��ڵ�ǰ�û����õ�RAT�б��� */
    for (i = 0 ; i < pstRatList->ucRatNum; i++)
    {
        if ( (enSpecRat == pstRatList->aucRatPrio[i])
          && (enSpecRat < NAS_MML_NET_RAT_TYPE_BUTT))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MML_IsSpec3Gpp2RatInRatList(
    NAS_MML_3GPP2_RAT_TYPE_ENUM_UINT8   enSpec3Gpp2Rat,
    NAS_MML_3GPP2_RAT_PRIO_STRU        *pst3Gpp2RatList
)
{
    VOS_UINT32                          i;

    /* ָ���Ľ��뼼���Ƿ��ڵ�ǰ�û����õ�RAT�б��� */
    for (i = 0 ; i < pst3Gpp2RatList->ucRatNum; i++)
    {
        if ( (enSpec3Gpp2Rat == pst3Gpp2RatList->aucRatPrio[i])
          && (enSpec3Gpp2Rat < NAS_MML_3GPP2_RAT_TYPE_BUTT))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MML_IsPlmnIdValid
 ��������  : �ж�PLMN ID�Ƿ���Ч
 �������  : VOS_VOID
 �� �� ֵ  : VOS_FALSE  : PLMN ID����Чֵ
             VOS_TRUE : PLMN ID����Чֵ
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2011��07��18��
   ��    ��   : zhoujun \40661
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MML_IsPlmnIdValid(
    NAS_MML_PLMN_ID_STRU                *pstPlmnId
)
{
    VOS_UINT32                          ulResult;

    /*
    The coding of this field is the responsibility of each administration but
    BCD coding shall be used. The MNC shall consist of 2 or 3 digits.
    If a network operator decides to use only two digits in the MNC,
    bits 5 to 8 of octet 7 shall be coded as "1111".
    MCC digit 2     MCC digit 1
    MNC digit 3     MCC digit 3
    MNC digit 2     MNC digit 1
    */

    ulResult = VOS_TRUE;

    if ( ((pstPlmnId->ulMcc & NAS_MML_BYTE_MASK) > NAS_MML_MAX_DIGIT_VALUE)
      || (((pstPlmnId->ulMcc >> 8) & NAS_MML_BYTE_MASK) > NAS_MML_MAX_DIGIT_VALUE)
      || (((pstPlmnId->ulMcc >> 16) & NAS_MML_BYTE_MASK) > NAS_MML_MAX_DIGIT_VALUE))
    {
        ulResult = VOS_FALSE;
    }

    if ((((pstPlmnId->ulMnc) & NAS_MML_BYTE_MASK) > NAS_MML_MAX_DIGIT_VALUE)
     || (((pstPlmnId->ulMnc >> 8) & NAS_MML_BYTE_MASK) > NAS_MML_MAX_DIGIT_VALUE))
    {
        ulResult = VOS_FALSE;
    }

    if ((((pstPlmnId->ulMnc >> 16) & NAS_MML_BYTE_MASK) > NAS_MML_MAX_DIGIT_VALUE)
     && (((pstPlmnId->ulMnc >> 16) & NAS_MML_BYTE_MASK) != NAS_MML_LOW_BYTE_INVALID))
    {
        ulResult = VOS_FALSE;
    }

    return ulResult;
}


VOS_UINT32 NAS_MML_IsMccValid(
    VOS_UINT32                          ulMcc
)
{
    VOS_UINT32                          ulResult;

    /*
    The coding of this field is the responsibility of each administration but
    BCD coding shall be used. The MNC shall consist of 2 or 3 digits.
    If a network operator decides to use only two digits in the MNC,
    bits 5 to 8 of octet 7 shall be coded as "1111".
    MCC digit 2     MCC digit 1
    MNC digit 3     MCC digit 3
    MNC digit 2     MNC digit 1
    */

    ulResult = VOS_TRUE;

    if ( ((ulMcc & NAS_MML_BYTE_MASK) > NAS_MML_MAX_DIGIT_VALUE)
      || (((ulMcc >> NAS_MML_OCTET_MOVE_EIGHT_BITS) & NAS_MML_BYTE_MASK)  > NAS_MML_MAX_DIGIT_VALUE)
      || (((ulMcc >> NAS_MML_OCTET_MOVE_SIXTEEN_BITS) & NAS_MML_BYTE_MASK) > NAS_MML_MAX_DIGIT_VALUE)
      || (((ulMcc >> NAS_MML_OCTET_MOVE_TWENTY_FOUR_BITS) & NAS_MML_BYTE_MASK) != NAS_MML_MCC_FOURTH_BYTES_VALID) )
    {
        ulResult = VOS_FALSE;
    }

    return ulResult;
}

VOS_UINT32 NAS_MML_IsBcchPlmnIdInDestSimPlmnList (
    NAS_MML_PLMN_ID_STRU               *pstBcchPlmnId,
    VOS_UINT8                           ucSimPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstSimPlmnIdList
)
{
    VOS_UINT32                          i;

    for ( i = 0; i < ucSimPlmnNum; i++ )
    {
        if ( VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstBcchPlmnId,
                                                            pstSimPlmnIdList+i) )
        {
            return VOS_TRUE;
        }
    }


    return VOS_FALSE;
}




VOS_UINT32 NAS_MML_IsSimPlmnIdInDestBcchPlmnList (
    NAS_MML_PLMN_ID_STRU               *pstSimPlmnId,
    VOS_UINT8                           ucBcchPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstBcchPlmnIdList
)
{
    VOS_UINT32                          i;

    for ( i = 0; i < ucBcchPlmnNum; i++ )
    {
        if ( VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstBcchPlmnIdList + i,
                                                            pstSimPlmnId) )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}




VOS_UINT32 NAS_MML_IsBcchPlmnIdInDestSimPlmnWithRatList (
    NAS_MML_PLMN_ID_STRU               *pstBcchPlmnId,
    VOS_UINT16                          usSimPlmnWithRatNum,
    NAS_MML_SIM_PLMN_WITH_RAT_STRU     *pstSimPlmnWithRatList
)
{
    VOS_UINT32                          i;

    for ( i = 0; i < usSimPlmnWithRatNum; i++ )
    {
        if ( VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstBcchPlmnId,
                                                            &pstSimPlmnWithRatList[i].stPlmnId) )
        {
            return VOS_TRUE;
        }
    }


    return VOS_FALSE;
}



VOS_UINT32 NAS_MML_IsLaiInDestLaiList (
    NAS_MML_LAI_STRU                   *pstLai,
    VOS_UINT32                          ulLaiNum,
    NAS_MML_LAI_STRU                   *pstLaiList
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    VOS_BOOL                            bFlg;

    bFlg = VOS_FALSE;

    for ( i = 0; i < ulLaiNum; i++ )
    {
        if ( VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstLai->stPlmnId),
                                                  &(pstLaiList[i].stPlmnId)) )
        {

            for ( j = 0 ; j < NAS_MML_MAX_LAC_LEN ; j++ )
            {
                if (pstLai->aucLac[j] != pstLaiList[i].aucLac[j])
                {
                    break;
                }
            }

            if (NAS_MML_MAX_LAC_LEN == j)
            {
                bFlg = VOS_TRUE;
                break;
            }
        }
    }


    return (bFlg);
}


VOS_UINT32 NAS_MML_GetLaiIndexInDestLaiList (
    NAS_MML_LAI_STRU                   *pstLai,
    VOS_UINT8                          *pucLaiIdx,
    VOS_UINT8                           ulLaiNum,
    NAS_MML_LAI_STRU                   *pstLaiList
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    VOS_UINT32                          ulFlg;

    ulFlg      = VOS_FALSE;
    *pucLaiIdx = 0;

    for ( i = 0; i < ulLaiNum; i++ )
    {
        if ( VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstLai->stPlmnId),
                                                  &(pstLaiList[i].stPlmnId)) )
        {
            for ( j = 0 ; j < NAS_MML_MAX_LAC_LEN; j++ )
            {
                if (pstLai->aucLac[j] != pstLaiList[i].aucLac[j])
                {
                    break;
                }
            }

            if (NAS_MML_MAX_LAC_LEN == j)
            {
                /* ���ز��ҵ�LAI���б��е�index */
                *pucLaiIdx = (VOS_UINT8)i;
                ulFlg = VOS_TRUE;
                break;
            }
        }
    }


    return (ulFlg);
}

/* Added by g00322017 for CS REG FAIL FORB LA, 2015-9-23, begin */
/*****************************************************************************
 �� �� ��  : NAS_MML_GetLaiIndexInRegFailForbLaList
 ��������  : ��ForbLaList�б��в���ָ��LA���������ȡ��Index������VOS_TRUE����������
             ����VOS_FALSE
 �������  : pstLai: ��Ҫ���ҵ�LAI
             ulLaiNum: �б���LAI�ĸ���
             pstRegFailForbLaList: LAI�б�
 �������  : pucLaiIdx: ���ҵ���LAI��Index
 �� �� ֵ  : VOS_TRUE  : LAI���б���
             VOS_FALSE : LAI�����б���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��9��24��
   ��    ��   : g00322017
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MML_GetLaiIndexInRegFailForbLaList (
    NAS_MML_LAI_STRU                                       *pstLai,
    VOS_UINT8                                              *pucLaiIdx,
    VOS_UINT32                                              ulLaiNum,
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_STRU                 *pstRegFailForbLaList
)
{
    NAS_MML_LAI_STRU                   *pstNasMmlLai = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT32                          ulFlg;

    ulFlg      = VOS_FALSE;
    *pucLaiIdx = 0;

    for ( i = 0; i < ulLaiNum; i++ )
    {
        pstNasMmlLai = &(pstRegFailForbLaList[i].stForbLaWithValidPeriodLai);
        if (VOS_TRUE == NAS_MML_CompareLai(pstLai, pstNasMmlLai))
        {
            /* ���ز��ҵ�LAI���б��е�index */
            *pucLaiIdx = (VOS_UINT8)i;
            ulFlg = VOS_TRUE;
            break;
        }
    }

    return (ulFlg);
}

/*****************************************************************************
 �� �� ��  : NAS_MML_AddCustomizedForbLaToDestLaList
 ��������  : ��tForbLaWithValidPeriod�б���LA,�������pstForbRomLaList�б��У�
             �����pstForbRomLaList�б�����pucForbRoamLaNum���ŵ���

 �������  :
             pucForbRoamLaNum: �б���LAI�ĸ���
             pstForbRomLaList: LAI�б�
 �������  :
             pucForbRoamLaNum: �б���LAI�ĸ���
             pstForbRomLaList: LAI�б�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��9��24��
   ��    ��   : g00322017
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MML_AddCustomizedForbLaToDestLaList(
    VOS_UINT8                          *pucDestLaNum,
    NAS_MML_LAI_STRU                   *pstDestLaList
)
{
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriodList = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                                       *pstLai                       = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstForbLaWithValidPeriodList = NAS_MML_GetForbLaWithValidPeriodList();
    for ( i = 0; i < pstForbLaWithValidPeriodList->ulForbLaWithValidPeriodNum; i++ )
    {
        pstLai = &(pstForbLaWithValidPeriodList->astForbLaWithValidPeriodList[i].stForbLaWithValidPeriodLai);
        if ( (VOS_FALSE == NAS_MML_IsLaiInDestLaiList(pstLai, *pucDestLaNum, pstDestLaList))
          && ( (*pucDestLaNum) < RRC_MAX_FORBLA_NUM) )
        {
            PS_MEM_CPY(&(pstDestLaList[*pucDestLaNum]) ,
                pstLai, sizeof(NAS_MML_LAI_STRU));
            (*pucDestLaNum)++;
        }
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MML_IsInForbLaWithValidPeriodList
 ��������  : �ж�LAI�Ƿ���ForbLaWithValidPeriod�б�
 �������  : NAS_MML_LAI_STRU LAI��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE  : �ڽ�ֹλ������
             VOS_FALSE : ���ڽ�ֹλ������
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2015��09��28��
   ��    ��   : g00322017
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MML_IsInForbLaWithValidPeriodList(
    NAS_MML_LAI_STRU                    *pstLai
)
{
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriod    = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                                       *pstTmpLai                   = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstForbLaWithValidPeriod = NAS_MML_GetForbLaWithValidPeriodList();

    /* LA��"forbidden las for regional" list */
    for (i = 0; i < pstForbLaWithValidPeriod->ulForbLaWithValidPeriodNum; i++)
    {
        pstTmpLai = &(pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].stForbLaWithValidPeriodLai);
        if (VOS_TRUE == NAS_MML_CompareLai(pstLai, pstTmpLai))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/* Added by g00322017 for CS REG FAIL FORB LA, 2015-9-23, end */

/*****************************************************************************
 �� �� ��  : NAS_MML_ComparePlmnIdWithHplmn
 ��������  : �ж�PLMN�Ƿ���HPLMN
 �������  : pstPlmnId:��Ҫ�Ƚϵ�PLMNID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��07��22��
   ��    ��   : zhoujun \40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MML_ComparePlmnIdWithHplmn (
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstEhplmnInfo = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstEhplmnInfo = NAS_MML_GetSimEhplmnList();

    for (i = 0; i < pstEhplmnInfo->ucEhPlmnNum; i++)
    {
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstPlmnId,
                                                           &(pstEhplmnInfo->astEhPlmnInfo[i].stPlmnId)))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MML_ComparePlmnIdWithUplmn (
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
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
        if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnWithRatList(pstPlmnId,
                                                      pstUserPlmnList->ucUserPlmnNum,
                                                      pstUserPlmnList->astUserPlmnInfo))
        {
            return VOS_TRUE;
        }
    }
    else /* ��ʾ(U)SIM���в�����UPLMN��OPLMN��ʹ��PLMN Sel�ļ� */
    {
        pstSelPlmnList = NAS_MML_GetSimSelPlmnList();

        if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstPlmnId,
                                                      pstSelPlmnList->ucSelPlmnNum,
                                                      pstSelPlmnList->astPlmnId))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
VOS_UINT32 NAS_MML_ComparePlmnIdWithOplmn (
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
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
        if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnWithRatList(pstPlmnId,
                                                      pstOperPlmnList->usOperPlmnNum,
                                                      pstOperPlmnList->astOperPlmnInfo))
        {
            return VOS_TRUE;
        }
    }
    else /* ��ʾ(U)SIM���в�����UPLMN��OPLMN��ʹ��PLMN Sel�ļ� */
    {
        pstSelPlmnList = NAS_MML_GetSimSelPlmnList();

        if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstPlmnId,
                                                      pstSelPlmnList->ucSelPlmnNum,
                                                      pstSelPlmnList->astPlmnId))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MML_IsPlmnIdRoamingAllowed(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_ROAM_CFG_INFO_STRU         *pstRoamCfg = VOS_NULL_PTR;
    VOS_UINT32                          ulFlg;

    pstRoamCfg        = NAS_MML_GetRoamCfg();

    /*��HPLMN��ͬ��ֱ�ӷ�������*/
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(pstPlmnId))
    {
        return VOS_TRUE;
    }

    /*�������Կ��عرգ�ֱ�ӷ�������*/
    if (VOS_FALSE == pstRoamCfg->ucRoamFeatureFlg )
    {
        return VOS_TRUE;
    }

    /*��������ʱֱ�ӷ�������*/
    if (NAS_MML_ROAM_NATION_ON_INTERNATION_ON == pstRoamCfg->enRoamCapability)
    {
        return VOS_TRUE;
    }

    /*�����������ʱ,������û��б����������ʾ,����������ʾ���й�������
      ����50506��50599��00101��50501, �Լ�Optus 2G,3G, Vodafone 2G 3G��
      ��������û��б����������ʾ������ע������ε�50501 */
    ulFlg = NAS_MML_IsSimPlmnIdInDestBcchPlmnList( pstPlmnId,
                                            pstRoamCfg->ucNationalRoamNum,
                                            pstRoamCfg->astRoamPlmnIdList );
    if ( (NAS_MML_ROAM_NATION_ON_INTERNATION_OFF == pstRoamCfg->enRoamCapability)
      && (VOS_TRUE                               == ulFlg) )
    {
        return VOS_TRUE;
    }

    /*�������������ʱ���������ε��κ����� */
    ulFlg = NAS_MML_IsSimPlmnIdInDestBcchPlmnList( pstPlmnId,
                                                   pstRoamCfg->ucNotRoamNum,
                                                   pstRoamCfg->astRoamPlmnIdList );
    if ( ( (NAS_MML_ROAM_NATION_OFF_INTERNATION_ON == pstRoamCfg->enRoamCapability)
        || (NAS_MML_ROAM_NATION_OFF_INTERNATION_OFF == pstRoamCfg->enRoamCapability) )
      && (VOS_TRUE == ulFlg) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT32 NAS_MML_GetVoiceNotPreferDisabledPlmnForbiddenTimeSlice(VOS_VOID)
{
    VOS_UINT32                          ulDisabledPlmnInvalidPeriod;
    VOS_UINT32                          ulInvalidTimeSlice;

    ulDisabledPlmnInvalidPeriod = NAS_MML_GetVoiceNotAvailPlmnForbiddenPeriod();
    ulInvalidTimeSlice          = 0;

    if (NAS_MML_MAX_TIME_SLICE == ulDisabledPlmnInvalidPeriod)
    {
        return NAS_MML_MAX_TIME_SLICE;
    }

    ulInvalidTimeSlice = VOS_GetSliceUnit() * (ulDisabledPlmnInvalidPeriod / 1000);
    return ulInvalidTimeSlice;
}


VOS_UINT32 NAS_MML_GetDisabledPlmnRejCause42ForbiddenTimeSlice(VOS_VOID)
{
    VOS_UINT32                          ulInvalidTimeSlice;
    VOS_UINT32                          ulDisabledPlmnForbiddenPeriod;

    ulInvalidTimeSlice          = 0;
    ulDisabledPlmnForbiddenPeriod = 2 * NAS_MML_GetSimHplmnTimerLen();

    ulInvalidTimeSlice = VOS_GetSliceUnit() * (ulDisabledPlmnForbiddenPeriod / 1000);
    return ulInvalidTimeSlice;
}



VOS_UINT32 NAS_MML_IsNeedAddVoiceNotAvailDisabledPlmnInDisabledPlmnWithForbiddenPeriodList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstPlmnWithRat,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegCause,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegCause,
    NAS_MML_ADDITION_UPDATE_RSLT_INFO_ENUM_UINT8            enAdditionUpdatRsltInfo
)
{
    /* ���Э��汾С��r11��������룬����false */
    if (NAS_MML_GetLte3gppRelVersion() < NAS_MML_3GPP_REL_R11)
    {
        return VOS_FALSE;
    }

    /* ���pstPlmnWithRat�Ѿ��ڽ�ֹ���뼼�������б��������账�� */
    if (VOS_TRUE == NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList(pstPlmnWithRat))
    {
        return VOS_FALSE;
    }


    if ((((NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE == enCsRegCause)
       || (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE == enCsRegCause)
       || (NAS_MML_REG_FAIL_CAUSE_CS_DOMAIN_NOT_AVAILABLE == enCsRegCause))
     && (NAS_MML_REG_FAIL_CAUSE_NULL == enPsRegCause))
     || (NAS_MML_ADDITION_UPDATE_RSLT_SMS_ONLY == enAdditionUpdatRsltInfo)
     || (NAS_MML_ADDITION_UPDATE_RSLT_CSFB_NOT_PREFERRED == enAdditionUpdatRsltInfo))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_UINT32 NAS_MML_GetPlmnWithRatIndexInDestDisabledPlmnWithForbiddenPeriodList (
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstSrcPlmnId,
    VOS_UINT32                                              ulDestPlmnNum,
    NAS_MML_DISABLED_PLMN_WITH_FORBIDDEN_PERIOD_STRU       *pstDestPlmnIdList
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulIndex;

    ulIndex = ulDestPlmnNum;

    if (ulIndex > NAS_MML_MAX_DISABLED_RAT_PLMN_NUM)
    {
        ulIndex = NAS_MML_MAX_DISABLED_RAT_PLMN_NUM;
    }

    for ( i = 0; i < ulIndex; i++ )
    {
        if ((VOS_TRUE               == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstSrcPlmnId->stPlmnId), &(pstDestPlmnIdList[i].stPlmnWithRat.stPlmnId)))
         && (pstSrcPlmnId->enRat    == pstDestPlmnIdList[i].stPlmnWithRat.enRat))
        {
            break;
        }
    }

    return i;
}


VOS_VOID NAS_MML_DeleteSpecDisabledPlmnWithValidPeriodInPlmnList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstPlmnWithRat
)
{
    NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU                *pstDisabledPlmnIdWithRatList = VOS_NULL_PTR;
    VOS_UINT32                                              ulIdx;

    pstDisabledPlmnIdWithRatList = NAS_MML_GetDisabledRatPlmnInfo();

    /* ��ȡɾ��plmn�ڽ�ֹ���뼼�������б��� */
    ulIdx = NAS_MML_GetPlmnWithRatIndexInDestDisabledPlmnWithForbiddenPeriodList(pstPlmnWithRat,
                                                 pstDisabledPlmnIdWithRatList->ulDisabledRatPlmnNum,
                                                 pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId);

    /* �ҵ���Ӧ��PlmnId,ɾ�� */
    if (ulIdx < pstDisabledPlmnIdWithRatList->ulDisabledRatPlmnNum)
    {
        if (ulIdx == (pstDisabledPlmnIdWithRatList->ulDisabledRatPlmnNum - 1))
        {
            pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIdx].stPlmnWithRat.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
            pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIdx].stPlmnWithRat.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
            pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIdx].stPlmnWithRat.enRat = NAS_MML_NET_RAT_TYPE_BUTT;
            pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIdx].ulPlmnDisabledForbiddenSlice   = NAS_MML_MAX_TIME_SLICE;
            pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIdx].ulPlmnDisabledBeginSlice = 0;
        }
        else
        {
            PS_MEM_MOVE(pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId + ulIdx,
              (pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId + (ulIdx + 1)),
              (NAS_MML_MAX_DISABLED_RAT_PLMN_NUM - (ulIdx + 1)) * sizeof(NAS_MML_DISABLED_PLMN_WITH_FORBIDDEN_PERIOD_STRU));
        }

        pstDisabledPlmnIdWithRatList->ulDisabledRatPlmnNum--;
    }

    NAS_MMC_LogForbiddenPlmnRelatedInfo();
    return;
}



VOS_UINT32 NAS_MML_DeleteExpireValidPeriodPlmnInDisabledRatPlmnList(VOS_VOID)
{
    NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU                *pstDisabledPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulIndex;
    VOS_UINT32                                              ulIsNeedDeleteDisabledPlmnWithRat;

    pstDisabledPlmnInfo               = NAS_MML_GetDisabledRatPlmnInfo();
    ulIsNeedDeleteDisabledPlmnWithRat = VOS_FALSE;

    for (ulIndex = 0; ulIndex < pstDisabledPlmnInfo->ulDisabledRatPlmnNum;)
    {
        if (VOS_TRUE == NAS_MML_IsNeedDeleteDisabledPlmnWithValidPeriodInPlmnList(&pstDisabledPlmnInfo->astDisabledRatPlmnId[ulIndex]))
        {
            if (ulIndex < pstDisabledPlmnInfo->ulDisabledRatPlmnNum - 1)
            {
                PS_MEM_MOVE(&(pstDisabledPlmnInfo->astDisabledRatPlmnId[ulIndex]),
                            &(pstDisabledPlmnInfo->astDisabledRatPlmnId[ulIndex+1]),
                             (pstDisabledPlmnInfo->ulDisabledRatPlmnNum-ulIndex-1)*sizeof(NAS_MML_DISABLED_PLMN_WITH_FORBIDDEN_PERIOD_STRU));
            }

            (pstDisabledPlmnInfo->ulDisabledRatPlmnNum)--;

            ulIsNeedDeleteDisabledPlmnWithRat = VOS_TRUE;

            NAS_MMC_LogForbiddenPlmnRelatedInfo();

            if (ulIndex > 0 )
            {
                ulIndex--;
            }
            else
            {
                continue;
            }

        }

        ulIndex++;
    }

    /* �����ֹ���뼼�������б��л����ڷ�NV���õ������ֹ����ΪȫF���������������ɾ����ֹ���뼼�������б�ʱ�� */
    for (ulIndex = 0; ulIndex < pstDisabledPlmnInfo->ulDisabledRatPlmnNum; ulIndex++)
    {
        if (NAS_MML_MAX_TIME_SLICE != pstDisabledPlmnInfo->astDisabledRatPlmnId[ulIndex].ulPlmnDisabledForbiddenSlice)
        {
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_DELETE_DISABLED_PLMN_WITH_RAT_TIMER,
                              TI_NAS_MMC_PERIOD_DELETE_DISABLED_PLMN_WITH_RAT_TIMER_LEN);
            break;
        }
    }

    return ulIsNeedDeleteDisabledPlmnWithRat;
}
VOS_UINT32 NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList (
    NAS_MML_PLMN_WITH_RAT_STRU         *pstSrcPlmnId
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulIndex;

    NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU                *pstDisabledPlmnInfo = VOS_NULL_PTR;

    pstDisabledPlmnInfo = NAS_MML_GetDisabledRatPlmnInfo();

    /* ʹ�ý�ֹ���뼼�������б�ǰ���ж����Ƿ��гͷ�ʱ�䵽�����磬�������ɾ�� */
    (VOS_VOID)NAS_MML_DeleteExpireValidPeriodPlmnInDisabledRatPlmnList();

    ulIndex = pstDisabledPlmnInfo->ulDisabledRatPlmnNum;

    if (ulIndex > NAS_MML_MAX_DISABLED_RAT_PLMN_NUM)
    {
        ulIndex = NAS_MML_MAX_DISABLED_RAT_PLMN_NUM;
    }

    for ( i = 0; i < ulIndex; i++ )
    {
        if ((VOS_TRUE               == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstSrcPlmnId->stPlmnId), &(pstDisabledPlmnInfo->astDisabledRatPlmnId[i].stPlmnWithRat.stPlmnId)))
         && (pstSrcPlmnId->enRat    == pstDisabledPlmnInfo->astDisabledRatPlmnId[i].stPlmnWithRat.enRat))
        {
            return VOS_TRUE;
        }
    }


    return VOS_FALSE;
}





VOS_UINT32 NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnRatList (
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstSrcPlmnId,
    VOS_UINT32                                              ulDestPlmnNum,
    NAS_MML_DISABLED_PLMN_WITH_FORBIDDEN_PERIOD_STRU       *pstDestPlmnIdList
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulIndex;

    ulIndex = ulDestPlmnNum;

    if (ulIndex > NAS_MML_MAX_DISABLED_RAT_PLMN_NUM)
    {
        ulIndex = NAS_MML_MAX_DISABLED_RAT_PLMN_NUM;
    }

    for ( i = 0; i < ulIndex; i++ )
    {
        if ((VOS_TRUE               == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstSrcPlmnId->stPlmnId), &(pstDestPlmnIdList[i].stPlmnWithRat.stPlmnId)))
         && (pstSrcPlmnId->enRat    == pstDestPlmnIdList[i].stPlmnWithRat.enRat))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
VOS_UINT32 NAS_MML_IsBcchPlmnIdInLockPlmnList (
    NAS_MML_PLMN_ID_STRU               *pstBcchPlmnId
)
{
    NAS_MML_PLMN_LOCK_CFG_INFO_STRU                        *pstPlmnLockInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList       = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnWithRat;
    VOS_UINT32                                              ulIndex;
    VOS_UINT32                                              ulDisabledPlmnFlg;
    VOS_UINT32                                              ulRatDisabledFlg;

    /* ��ȡ��ǰ���뼼�����ȼ���Ϣ */
    pstPrioRatList          = NAS_MML_GetMsPrioRatList();

    pstPlmnLockInfo         = NAS_MML_GetPlmnLockCfg();

    ulDisabledPlmnFlg       = VOS_TRUE;

    ulRatDisabledFlg        = VOS_TRUE;

    /* E5��̬PLMN ID�ں������� */
    if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstBcchPlmnId,
                                                          pstPlmnLockInfo->ucBlackPlmnLockNum,
                                                          pstPlmnLockInfo->astBlackPlmnId))
    {
        return VOS_TRUE;
    }

    /* ��������뼼����PLMN ID */
    stPlmnWithRat.stPlmnId.ulMcc    = pstBcchPlmnId->ulMcc;
    stPlmnWithRat.stPlmnId.ulMnc    = pstBcchPlmnId->ulMnc;

    /* ����UE֧�ֵĽ��뼼��,���PLMN ID�ڽ�ֹ���뼼���ĺ�����������, ���ҵ�ǰUE
       ֧�ֵĽ��뼼��������ֹ,����Ϊ��PLMN ID�ǽ�ֹ���� */
    for (ulIndex = 0; ulIndex < pstPrioRatList->ucRatNum; ulIndex++)
    {
        stPlmnWithRat.enRat   = pstPrioRatList->aucRatPrio[ulIndex];

        if (VOS_FALSE == NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
        {
            ulDisabledPlmnFlg = VOS_FALSE;
            break;
        }
    }

    /* ��PLMN ID֧�ֵĽ��뼼�����ڽ�ֹRAT��PLMN �б��� */
    if (VOS_TRUE == ulDisabledPlmnFlg)
    {
        return VOS_TRUE;
    }

    for (ulIndex = 0; ulIndex < pstPrioRatList->ucRatNum; ulIndex++)
    {
        stPlmnWithRat.enRat   = pstPrioRatList->aucRatPrio[ulIndex];

        if (VOS_FALSE == NAS_MML_IsRatInForbiddenList(stPlmnWithRat.enRat))
        {
            ulRatDisabledFlg = VOS_FALSE;
            break;
        }
    }

    if (VOS_TRUE == ulRatDisabledFlg)
    {
        return VOS_TRUE;
    }

    /* ����������Ϊ0��ʾδ��������������,E5��̬PLMN ID���ڰ������� */
    if (pstPlmnLockInfo->ucWhitePlmnLockNum > 0)
    {
        if (VOS_FALSE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstBcchPlmnId,
                                                               pstPlmnLockInfo->ucWhitePlmnLockNum,
                                                               pstPlmnLockInfo->astWhitePlmnId))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MML_IsPlmnIdInForbidPlmnList(
    NAS_MML_PLMN_ID_STRU                *pstPlmnId
)
{
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo = VOS_NULL_PTR;
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode;
    VOS_UINT32                          ulRet;

    pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();
    enMsMode          = NAS_MML_GetMsMode();

    /* ��forbid plmn�б��� */
    if(VOS_TRUE == NAS_MML_IsSimPlmnIdInDestBcchPlmnList(pstPlmnId,
                                          pstForbidPlmnInfo->ucForbPlmnNum,
                                          pstForbidPlmnInfo->astForbPlmnIdList))
    {
        return VOS_TRUE;
    }

    /* ��PLMN ID�Ƿ�������������PLMN �б��� */
    if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInLockPlmnList(pstPlmnId))
    {
        return VOS_TRUE;
    }


    /* ����������ʱ */
    if (VOS_FALSE == NAS_MML_IsPlmnIdRoamingAllowed(pstPlmnId))
    {
        return VOS_TRUE;
    }

    ulRet = NAS_MML_IsSimPlmnIdInDestBcchPlmnList(pstPlmnId,
                                              pstForbidPlmnInfo->ucForbGprsPlmnNum,
                                              pstForbidPlmnInfo->astForbGprsPlmnList);

    /* ��forbid plmn for gprs�б��� */
    if ( ( NAS_MML_MS_MODE_PS_ONLY == enMsMode)
      && ( VOS_TRUE == ulRet ))
    {
        return VOS_TRUE;
    }

    /* AģʽʱCS����Чʱ */
    if ( ( VOS_FALSE             == NAS_MML_GetSimCsRegStatus())
      && ( NAS_MML_MS_MODE_PS_CS == enMsMode)
      && ( VOS_TRUE              == ulRet))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT32 NAS_MML_IsRrcConnExist( VOS_VOID )
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat;

    /* ȡ�õ�ǰ�Ľ���ģʽ */
    enCurrRat     = NAS_MML_GetCurrNetRatType();

    /* ȡ�õ�ǰ��������Ϣ */
    pstConnStatus = NAS_MML_GetConnStatus();

    switch ( enCurrRat )
    {
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:

            /* ��ǰģ��L�£������������ӻ����������� */
            if ( (VOS_TRUE == pstConnStatus->ucEpsSigConnStatusFlg)
              || (VOS_TRUE == pstConnStatus->ucEpsServiceConnStatusFlg) )
            {
                return VOS_TRUE;
            }

            /* �����ڷ���FALSE */
            return VOS_FALSE;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:

            /* ��ǰģ��W�£������������ӻ����������� */
            if ( (VOS_TRUE == pstConnStatus->ucRrcStatusFlg)
              || (VOS_TRUE == pstConnStatus->ucPsSigConnStatusFlg)
              || (VOS_TRUE == pstConnStatus->ucCsSigConnStatusFlg) )
            {
                return VOS_TRUE;
            }

            /* �����ڷ���FALSE */
            return VOS_FALSE;

        case NAS_MML_NET_RAT_TYPE_GSM:

            /* ��ǰģ��G�£������������ӻ����������� */
            if ( (VOS_TRUE == pstConnStatus->ucRrcStatusFlg)
              || (VOS_TRUE == pstConnStatus->ucCsSigConnStatusFlg)
              || (VOS_TRUE == pstConnStatus->ucPsTbfStatusFlg) )
            {
                return VOS_TRUE;
            }

            /* �����ڷ���FALSE */
            return VOS_FALSE;

        default:

            /* �޷������Ľ���ģʽ����ӡ�쳣���������Ӳ����ڷ��� */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MML_IsRrcConnExist,WARNING:�޷������Ľ���ģʽ");

            return VOS_FALSE;
    }

}
VOS_UINT32  NAS_MML_IsQuickStartFlg( VOS_VOID )
{
    VOS_UINT8                           ucCardStatus;
    VOS_UINT8                           ucCardType;
    VOS_UINT32                          ulQuickStartFlag;


    ucCardStatus = USIMM_CARD_SERVIC_BUTT;
    ucCardType   = USIMM_CARD_NOCARD;

    if ( USIMM_API_SUCCESS != NAS_USIMMAPI_GetCardType(&ucCardStatus, &ucCardType) )
    {
        return VOS_TRUE;
    }
    if ( USIMM_CARD_ROM_SIM == ucCardType )
    {
        ulQuickStartFlag    = VOS_TRUE;
    }
    else
    {
        ulQuickStartFlag    = VOS_FALSE;
    }

    return ulQuickStartFlag;
}
VOS_UINT32 NAS_MML_IsTmsiValid(VOS_VOID)
{
    VOS_UINT8                          *pucTmsi = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pucTmsi = NAS_MML_GetUeIdTmsi();

    for ( i = 0; i < NAS_MML_MAX_TMSI_LEN; i++ )
    {
        if ( NAS_MML_TMSI_INVALID != pucTmsi[i] )
        {
            return VOS_TRUE;
        }
    }


    return VOS_FALSE;
}


VOS_UINT32 NAS_MML_IsPtmsiValid(VOS_VOID)
{
    VOS_UINT8                          *pucPtmsi = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pucPtmsi = NAS_MML_GetUeIdPtmsi();

    for ( i = 0; i < NAS_MML_MAX_PTMSI_LEN; i++ )
    {
        if ( NAS_MML_PTMSI_INVALID != pucPtmsi[i] )
        {
            return VOS_TRUE;
        }
    }


    return VOS_FALSE;
}


VOS_UINT32  NAS_MML_GetGsmForbidFlg( VOS_VOID )
{
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU *pstMiscellaneousCfg = VOS_NULL_PTR;
    NAS_MML_SIM_TYPE_ENUM_UINT8          enSimType;
    VOS_UINT8                            ucSimPresentStatus;

    /* ���ٿ���ģʽֱ�ӷ��� */
    if ( VOS_TRUE == NAS_MML_IsQuickStartFlg())
    {
        return VOS_FALSE;
    }

    pstMiscellaneousCfg = NAS_MML_GetMiscellaneousCfgInfo();
    enSimType           = NAS_MML_GetSimType();
    ucSimPresentStatus  = NAS_MML_GetSimPresentStatus();

    /* ������ΪUSIM�ҿ���λ */
    if ((NAS_MML_SIM_TYPE_USIM == enSimType)
     && (VOS_TRUE == ucSimPresentStatus))
    {
        /* USIM��NV�ж�ָʾ��ֹGSM����ʱ����Ҫ��¼��GSM�²��ܽ��н��� */
        if (VOS_FALSE == NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_GSM_ACCESS_IN_USIM))
        {
            if ((VOS_FALSE == NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_GSM_SECURITY_CONTEXT))
            && (VOS_TRUE  == pstMiscellaneousCfg->ucNvGsmForbidFlg))
            {
                return VOS_TRUE;
            }
        }
    }

    /* ��NV���޸�ΪW��G��ΪUINT32��, ԭΪUINT16, �� aulSptBand[0]ΪW��BAND, aulSptBand[1]ΪG��BAND */

    if (0 == NAS_MML_GetGsmBandCapability())
    {
        return VOS_TRUE;
    }


    return VOS_FALSE;
}


VOS_VOID  NAS_MML_InitSimPlmnInfo(
    VOS_UINT32                          ulPlmnNum,
    NAS_MML_SIM_PLMN_WITH_RAT_STRU     *pstPlmnInfo
)
{
    VOS_UINT32                          i;

    for ( i = 0 ; i < ulPlmnNum ; i++ )
    {
        pstPlmnInfo[i].usSimRat         = NAS_MML_INVALID_SIM_RAT;
        pstPlmnInfo[i].stPlmnId.ulMcc   = NAS_MML_INVALID_MCC;
        pstPlmnInfo[i].stPlmnId.ulMnc   = NAS_MML_INVALID_MNC;
    }
}


VOS_VOID  NAS_MML_ResumeSimEhplmnList(
    VOS_UINT8                          *pucPlmnNum,
    NAS_MML_SIM_PLMN_WITH_RAT_STRU     *pstPlmnInfo
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulTempPlmnNum;
    NAS_MML_SIM_PLMN_WITH_RAT_STRU      astTempPlmnInfo[NAS_MML_MAX_EHPLMN_NUM];
    VOS_UINT16                          usUeSptRat;

    PS_MEM_SET(astTempPlmnInfo, 0x00, sizeof(astTempPlmnInfo));
#if (FEATURE_ON == FEATURE_LTE)
    usUeSptRat          = NAS_MML_SIM_UE_SUPPORT_RAT_SUPPORT_LTE;
#else
    usUeSptRat          = NAS_MML_SIM_UE_SUPPORT_RAT;
#endif

    /* ��Ҫ���¹�����PLMN WITH RAT��Ϣ��������ʱ������ */
    ulTempPlmnNum = *pucPlmnNum;
    PS_MEM_CPY(astTempPlmnInfo, pstPlmnInfo, sizeof(astTempPlmnInfo));

    /* ��ԴPLMN WITH RAT��Ϣ��� */
    NAS_MML_InitSimPlmnInfo(*pucPlmnNum, pstPlmnInfo);
    *pucPlmnNum = 0;

    /* �����ظ���������ӽ���ԴPLMN WITH RAT �б� */
    for ( i = 0 ; i < ulTempPlmnNum ; i++ )
    {
        /* ��ǰ�����Ѿ���ԭ�е��б����ˣ������  */
        if ( VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnWithRatList(&astTempPlmnInfo[i].stPlmnId,
                                                                      *pucPlmnNum,
                                                                       pstPlmnInfo) )
        {
            continue;
        }

        /* ��ǰ���粻��ԭ�е��б����ˣ��������ԴPLMN WITH RAT �б� */
        pstPlmnInfo[*pucPlmnNum].stPlmnId = astTempPlmnInfo[i].stPlmnId;
        pstPlmnInfo[*pucPlmnNum].usSimRat = usUeSptRat;

        (*pucPlmnNum)++;
    }

    return;
}
VOS_UINT32 NAS_MML_IsUsimStausValid(VOS_VOID)
{
    NAS_MML_SIM_STATUS_STRU            *pstSimStatus    = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_ECALL)
    NAS_MML_CALL_MODE_ENUM_UINT8        enCallMode;

    enCallMode = NAS_MML_GetCallMode();
#endif

    pstSimStatus = NAS_MML_GetSimStatus();

    if ( VOS_FALSE == NAS_MML_GetSimPresentStatus() )
    {
        return VOS_FALSE;
    }

    if (( VOS_FALSE == pstSimStatus->ucSimPsRegStatus)
     && ( VOS_FALSE == pstSimStatus->ucSimCsRegStatus))
    {
        return VOS_FALSE;
    }

    if ((VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
     && (VOS_FALSE == pstSimStatus->ucSimCsRegStatus))
    {
        return VOS_FALSE;
    }

    /* ��ecall onlyģʽCS������attach����PS����Ч����Ϊ����Ч */
    if ((VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
     && (VOS_FALSE == pstSimStatus->ucSimPsRegStatus)
#if (FEATURE_ON == FEATURE_ECALL)
     && (NAS_MML_ECALL_ONLY != enCallMode)
#endif
       )
    {
        return VOS_FALSE;
    }

#if (FEATURE_ON == FEATURE_LTE)

    /* LTE��ģ�����PS����Ч��ʱ��Ҳ��Ϊ��ʱ����Ч */
    if ((VOS_TRUE  == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
     && (VOS_FALSE == pstSimStatus->ucSimPsRegStatus))
    {
        return VOS_FALSE;
    }
#endif
    return VOS_TRUE;

}


VOS_UINT32 NAS_MML_IsMccInDestMccList (
    VOS_UINT32                          ulMcc,
    VOS_UINT32                          ulMccNum,
    VOS_UINT32                         *pulMccList
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulFlg;

    ulFlg = VOS_FALSE;

    for ( i = 0; i < ulMccNum; i++ )
    {
        if ( VOS_TRUE == NAS_MML_ComparePlmnMcc(ulMcc,
                                                  pulMccList[i]) )
        {
            ulFlg = VOS_TRUE;
            break;
        }
    }

    return (ulFlg);
}


/* Added by n00355355 for �����ؽ�, 2015-9-17, begin */

VOS_VOID NAS_MML_GetMmlCsTransactionStatus(
    NAS_MML_CS_TRANSACTION_ENUM_UINT8                        *penAsCsTransactionsStatus
)
{
    /* ���о���CSFB�ı���*/
    if ( NAS_MML_CSFB_SERVICE_STATUS_MT_EXIST == NAS_MML_GetCsfbServiceStatus())
    {
        *penAsCsTransactionsStatus = NAS_MML_CS_TRANSACTION_MT_EXIST;

        return;
    }

    if ( VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
    {
        /* ���ڽ�����*/
        if ( VOS_TRUE == NAS_MML_GetCsEmergencyServiceFlg())
        {
            *penAsCsTransactionsStatus = NAS_MML_CS_TRANSACTION_EMERGENCY_EXIST;
        }
        /* �����ڽ���������ͨ���У�SS,SM��������ͨ����*/
        else
        {
            *penAsCsTransactionsStatus = NAS_MML_CS_TRANSACTION_MO_NORMAL_EXIST;
        }

        return;
    }

    /*������ҵ��*/
    *penAsCsTransactionsStatus = NAS_MML_CS_TRANSACTION_NO_EXIST;

    return;
}

/* Added by n00355355 for �����ؽ�, 2015-9-17, end */



#if (FEATURE_ON == FEATURE_LTE)

VOS_UINT32 NAS_MML_IsPlmnIdInCsDomainUnAvailPlmnList(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_PLMN_ID_STRU               *pstPlmnList = VOS_NULL_PTR;
    NAS_LMM_INFO_STRU                   stLmmInfo;

    PS_MEM_SET(&stLmmInfo, 0x0, sizeof(NAS_LMM_INFO_STRU));


    /* ƽ̨��֧��LTE */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        return VOS_FALSE;
    }

    /* ����LNAS�ṩ�ӿں������ɹ�����VOS_OK */
    if (MMC_LMM_SUCC != Nas_GetLteInfo(NAS_LMM_CS_DOMAIN_UNAVAILABLE_PLMN_LIST, &stLmmInfo))
    {
        return VOS_FALSE;
    }

    /* ���붯̬�ڴ� */
    pstPlmnList = (NAS_MML_PLMN_ID_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC, (MMC_LMM_MAX_PLMN_NUM*sizeof(NAS_MML_PLMN_ID_STRU)));

    /* �������ʧ�ܣ��򷵻� */
    if ( VOS_NULL_PTR == pstPlmnList )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MML_IsPlmnIdInCsDomainUnAvailPlmnList: Dynamic Memory Alloc Error");

        return VOS_FALSE;
    }

    NAS_MMC_ConvertLmmPlmnToGUNasPlmn(stLmmInfo.u.stCsDomainUnAvailPlmnList.ulPlmnNum,
                                      stLmmInfo.u.stCsDomainUnAvailPlmnList.astPlmnId,
                                      pstPlmnList);

    /* ��#18�б��� */
    if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstPlmnId,
                                         (VOS_UINT8)(stLmmInfo.u.stCsDomainUnAvailPlmnList.ulPlmnNum),
                                         pstPlmnList))
    {
        /* �ͷŶ�̬�ڴ� */
        PS_MEM_FREE(WUEPS_PID_MMC, pstPlmnList);

        return VOS_TRUE;
    }

    /* �ͷŶ�̬�ڴ� */
    PS_MEM_FREE(WUEPS_PID_MMC, pstPlmnList);

    return VOS_FALSE;
}



VOS_UINT32 NAS_MML_GetLteRPlmn(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_PLMN_ID_STRU                stRPlmnId;
    NAS_LMM_INFO_STRU                   stLmmInfoStru;

    PS_MEM_SET(&stRPlmnId,     0x00, sizeof(NAS_MML_PLMN_ID_STRU));
    PS_MEM_SET(&stLmmInfoStru, 0x00, sizeof(NAS_LMM_INFO_STRU));

    /* ��ȡLģ��GUTI, ��ȡʧ���򷵻� VOS_FALSE */
    /* ���ƽ̨������֧��lte,���ز�����LTE��RPLMN */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        return VOS_FALSE;
    }

    if (MMC_LMM_SUCC != Nas_GetLteInfo(NAS_LMM_RPLMN, &stLmmInfoStru))
    {
        return VOS_FALSE;
    }

    /* ��GUTI�е�PLMNת��ΪGUNASʹ�õ�PLMN��ʽ */
    NAS_MMC_ConvertLmmPlmnToGUNasFormat(&(stLmmInfoStru.u.stPlmn), &(stRPlmnId));

    /* ����PLMN��Ч�Ҳ��ǽ�ֹ������ֱ�ӷ��� */
    if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&stRPlmnId))
    {
        if (VOS_FALSE == NAS_MML_IsPlmnIdInForbidPlmnList(&stRPlmnId))
        {
            *pstPlmnId = stRPlmnId;

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
VOS_UINT32 NAS_MML_IsTaiInDestTaiList (
    NAS_MML_TAI_STRU                   *pstTai,
    VOS_UINT32                          ulTaiNum,
    NAS_LMM_TAI_STRU                   *pstTaiList
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulIsTaiInTaiListFlg;
    NAS_MML_PLMN_ID_STRU                stPlmnId;
    VOS_UINT32                          ulIsSamePlmn;

    ulIsTaiInTaiListFlg = VOS_FALSE;

    for ( i = 0; i < ulTaiNum; i++ )
    {
        NAS_MMC_ConvertLmmPlmnToGUNasFormat(&pstTaiList[i].stPlmnId, &stPlmnId);

        ulIsSamePlmn = NAS_MML_CompareBcchPlmnwithSimPlmn(&pstTai->stPlmnId, &stPlmnId);

        if ((VOS_TRUE == ulIsSamePlmn)
         && (pstTai->stTac.ucTac == pstTaiList[i].stTac.ucTac)
         && (pstTai->stTac.ucTacCnt == pstTaiList[i].stTac.ucTacCnt))
        {
            ulIsTaiInTaiListFlg = VOS_TRUE;
            break;
        }
    }

    return ulIsTaiInTaiListFlg;
}


VOS_UINT32 NAS_MML_IsSupportLteCapability(VOS_VOID)
{
    VOS_UINT32                          ulIsLteRatSupportFlg;

    ulIsLteRatSupportFlg = NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE);

    if ((VOS_TRUE == NAS_MML_IsLteCapabilityDisabled(NAS_MML_GetLteCapabilityStatus(),NAS_MML_GetDisableLteRoamFlg()))
     || (VOS_FALSE == ulIsLteRatSupportFlg))
    {
        /* L����disable״̬��syscfg���ò�֧��L,����VOS_FALSE*/
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


#endif



VOS_UINT32 NAS_MML_GetGU_CsRPlmn(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_PLMN_ID_STRU                stRPlmnId;
    NAS_MML_LAI_STRU                   *pstLai = VOS_NULL_PTR;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enStatus;

    enStatus = NAS_MML_GetCsUpdateStatus();

    if ((NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED == enStatus)
     || (NAS_MML_LOCATION_UPDATE_STATUS_BUTT == enStatus))
    {
        return VOS_FALSE;
    }

    pstLai = NAS_MML_GetCsLastSuccLai();

    stRPlmnId = pstLai->stPlmnId;

    /* ����PLMN��Ч�Ҳ��ڽ�ֹ�����У����ظ����� */
    if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&stRPlmnId))
    {
        if (VOS_FALSE == NAS_MML_IsPlmnIdInForbidPlmnList(&stRPlmnId))
        {
           *pstPlmnId = stRPlmnId;

           return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
VOS_UINT32 NAS_MML_GetGU_PsRPlmn(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_PLMN_ID_STRU                stRPlmnId;
    NAS_MML_RAI_STRU                   *pstRai = VOS_NULL_PTR;
    NAS_MML_ROUTING_UPDATE_STATUS_ENUM_UINT8    enStatus;

    enStatus = NAS_MML_GetPsUpdateStatus();

    if ((NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED == enStatus)
     || (NAS_MML_ROUTING_UPDATE_STATUS_BUTT == enStatus))
    {
        return VOS_FALSE;
    }

    pstRai  = NAS_MML_GetPsLastSuccRai();

    stRPlmnId = pstRai->stLai.stPlmnId;

    /* ����PLMN��Ч�Ҳ��ڽ�ֹ�����У����ظ����� */
    if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&stRPlmnId))
    {
        if (VOS_FALSE == NAS_MML_IsPlmnIdInForbidPlmnList(&stRPlmnId))
        {
           *pstPlmnId = stRPlmnId;

           return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
VOS_UINT32 NAS_MML_GetGURPlmn(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    if (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
    {
        return NAS_MML_GetGU_PsRPlmn(pstPlmnId);
    }
    else if (NAS_MML_MS_MODE_CS_ONLY == NAS_MML_GetMsMode())
    {
        return NAS_MML_GetGU_CsRPlmn(pstPlmnId);
    }
    else
    {
        /* CS��PSģʽ�£����ж�CS��Rplmn,���ж�PS��Rplmn */
        if (VOS_TRUE == NAS_MML_GetGU_CsRPlmn(pstPlmnId))
        {
            return VOS_TRUE;
        }
        else if (VOS_TRUE == NAS_MML_GetGU_PsRPlmn(pstPlmnId))
        {
            return VOS_TRUE;
        }
        else
        {
            return VOS_FALSE;
        }
    }

}
VOS_UINT32 NAS_MML_GetEfLociPlmn(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_PLMN_ID_STRU                stRPlmnId;
    NAS_MML_RAI_STRU                   *pstRai = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                   *pstLai = VOS_NULL_PTR;
    NAS_MML_ROUTING_UPDATE_STATUS_ENUM_UINT8    enPsStatus;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsStatus;

    pstRai      = NAS_MML_GetPsLastSuccRai();
    pstLai      = NAS_MML_GetCsLastSuccLai();
    enPsStatus  = NAS_MML_GetPsUpdateStatus();
    enCsStatus  = NAS_MML_GetCsUpdateStatus();

    if (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
    {
        if (NAS_MML_ROUTING_UPDATE_STATUS_BUTT == enPsStatus)
        {
            return VOS_FALSE;
        }

        stRPlmnId = pstRai->stLai.stPlmnId;
    }
    else
    {
        if (NAS_MML_LOCATION_UPDATE_STATUS_BUTT == enCsStatus)
        {
            return VOS_FALSE;
        }

        stRPlmnId = pstLai->stPlmnId;
    }

    /* ����PLMN��Ч�Ҳ��ڽ�ֹ�����У����ظ����� */
    if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&stRPlmnId))
    {
        if (VOS_FALSE == NAS_MML_IsPlmnIdInForbidPlmnList(&stRPlmnId))
        {
           *pstPlmnId = stRPlmnId;

           return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
VOS_UINT32 NAS_MML_GetRPlmn(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
#if (FEATURE_ON == FEATURE_LTE)
    if (NAS_MML_NET_RAT_TYPE_LTE == enRat)
    {
        return NAS_MML_GetLteRPlmn(pstPlmnId);
    }
#endif

    return NAS_MML_GetGURPlmn(pstPlmnId);

}


VOS_UINT32 NAS_MML_AddForbPlmn (
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    VOS_UINT32                          ulRlst;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbPlmnInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucForbPlmnNum;
    VOS_UINT32                          ulChgFlag;

    ulChgFlag  = VOS_FALSE;

    ulRlst    = NAS_MML_ComparePlmnIdWithHplmn(pstPlmnId);

    if (VOS_TRUE == ulRlst )
    {
        return ulChgFlag;
    }

    /*���ForbPlmn������Usim���͸�����Ϣ*/
    pstForbPlmnInfo = NAS_MML_GetForbidPlmnInfo();
    ucForbPlmnNum   = pstForbPlmnInfo->ucForbPlmnNum;


    /* ��forbid plmn�б��� */
    ulRlst = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstPlmnId,
                                          pstForbPlmnInfo->ucForbPlmnNum,
                                          pstForbPlmnInfo->astForbPlmnIdList);

    if (VOS_FALSE == ulRlst)
    {
        /* �б�����ʱ��ɾ�����ȱ����Ԫ�� */
        if (( NAS_MML_MAX_FORBPLMN_NUM == ucForbPlmnNum )
         || ((pstForbPlmnInfo->ucUsimForbPlmnNum == ucForbPlmnNum)
          && (0 < ucForbPlmnNum)))
        {
            (VOS_VOID)PS_MEM_MOVE(pstForbPlmnInfo->astForbPlmnIdList,
                        (pstForbPlmnInfo->astForbPlmnIdList + 1),
                        (NAS_MML_MAX_FORBPLMN_NUM -1) * sizeof(NAS_MML_PLMN_ID_STRU));

            ucForbPlmnNum--;
        }

        pstForbPlmnInfo->astForbPlmnIdList[ucForbPlmnNum].ulMcc
                                                       = pstPlmnId->ulMcc;
        pstForbPlmnInfo->astForbPlmnIdList[ucForbPlmnNum].ulMnc
                                                       = pstPlmnId->ulMnc;

        ucForbPlmnNum++;

        pstForbPlmnInfo->ucForbPlmnNum = ucForbPlmnNum;

        ulChgFlag = VOS_TRUE;

    }

    return ulChgFlag;
}
VOS_UINT32 NAS_MML_DelForbPlmn (
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulIdx;
    VOS_UINT32                          ulChgFlag;

    ulChgFlag  = VOS_FALSE;

    pstForbPlmnInfo   = NAS_MML_GetForbidPlmnInfo();

    /* ��forbid plmn�б��� */
    ulIdx = NAS_MML_GetPlmnIdxInList(pstPlmnId,
                    pstForbPlmnInfo->ucForbPlmnNum, pstForbPlmnInfo->astForbPlmnIdList);

    /* �ҵ���Ӧ��PlmnId,ɾ��������ForbPlmn������Usim���͸�����Ϣ*/
    if (ulIdx < pstForbPlmnInfo->ucForbPlmnNum)
    {
        if (ulIdx == (pstForbPlmnInfo->ucForbPlmnNum -1))
        {
            pstForbPlmnInfo->astForbPlmnIdList[ulIdx].ulMcc = NAS_MML_INVALID_MCC;
            pstForbPlmnInfo->astForbPlmnIdList[ulIdx].ulMnc = NAS_MML_INVALID_MNC;
        }
        else
        {
            (VOS_VOID)PS_MEM_MOVE(pstForbPlmnInfo->astForbPlmnIdList + ulIdx,
                 (pstForbPlmnInfo->astForbPlmnIdList + (ulIdx + 1)),
                 (NAS_MML_MAX_FORBPLMN_NUM - (ulIdx + 1)) * sizeof(NAS_MML_PLMN_ID_STRU));
        }

        pstForbPlmnInfo->ucForbPlmnNum --;

        ulChgFlag  = VOS_TRUE;

    }

    return ulChgFlag;
}


VOS_VOID NAS_MML_AddForbGprsPlmn(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbPlmnInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucForbGprsPlmnNum;
    VOS_UINT32                          ulRlst;

    ulRlst = VOS_FALSE;

    /* ���ڻ�ȡ��ֹGPRS PLMN lsit */
    pstForbPlmnInfo = NAS_MML_GetForbidPlmnInfo();

    /* Ts23.122 Ch 3.1 The HPLMN (if the EHPLMN list is not present or is empty)
    or an EHPLMN (if the EHPLMN list is present) shall not be stored
    on the list of "forbidden PLMNs for GPRS service"
    ��ز�������: ts34.123 GCF12.3.2.8 cellA in MCC2/MNC1/LAC1/RAC1(RAI-2, Not HPLMN) */
    ulRlst = NAS_MML_ComparePlmnIdWithHplmn(pstPlmnId);
    if (VOS_TRUE == ulRlst)
    {
        return;
    }

    /* ��PLMN���ڽ�ֹGPRS PLMN lsit�У������ */
    ulRlst = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstPlmnId,
                                            pstForbPlmnInfo->ucForbGprsPlmnNum,
                                            pstForbPlmnInfo->astForbGprsPlmnList);


    if (VOS_TRUE == ulRlst)
    {
        return;
    }

    /* ��ȡ��ֹGPRS PLMN �ĸ��� */
    ucForbGprsPlmnNum   = pstForbPlmnInfo->ucForbGprsPlmnNum;

    /* �б�����ʱ���Ƴ����ȱ����Ԫ�� */
    if ( NAS_MML_MAX_FORBGPRSPLMN_NUM == ucForbGprsPlmnNum )
    {
        (VOS_VOID)PS_MEM_MOVE(&(pstForbPlmnInfo->astForbGprsPlmnList[0]),
                    &(pstForbPlmnInfo->astForbGprsPlmnList[1]),
                     (ucForbGprsPlmnNum-1) * sizeof(NAS_MML_PLMN_ID_STRU));
        ucForbGprsPlmnNum--;
    }

    /* ��ӽ�ֹGPRS PLMN���б����� */
    pstForbPlmnInfo->astForbGprsPlmnList[ucForbGprsPlmnNum].ulMcc
                                                   = pstPlmnId->ulMcc;
    pstForbPlmnInfo->astForbGprsPlmnList[ucForbGprsPlmnNum].ulMnc
                                                   = pstPlmnId->ulMnc;

    /* ���½�ֹGPRS PLMN�ĸ��� */
    ucForbGprsPlmnNum++;
    pstForbPlmnInfo->ucForbGprsPlmnNum = ucForbGprsPlmnNum;

    return;
}
VOS_VOID NAS_MML_DelForbGprsPlmn (
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulIdx;

    pstForbPlmnInfo   = NAS_MML_GetForbidPlmnInfo();

    /* ��forbid plmn for Gprs�б��� */
    ulIdx = NAS_MML_GetPlmnIdxInList(pstPlmnId,
                    pstForbPlmnInfo->ucForbGprsPlmnNum, pstForbPlmnInfo->astForbGprsPlmnList);

    /* �ҵ���Ӧ��PlmnId,ɾ��������ForbPlmn */
    if (ulIdx < pstForbPlmnInfo->ucForbGprsPlmnNum)
    {
        if (ulIdx == (pstForbPlmnInfo->ucForbGprsPlmnNum -1))
        {
            pstForbPlmnInfo->astForbGprsPlmnList[ulIdx].ulMcc = NAS_MML_INVALID_MCC;
            pstForbPlmnInfo->astForbGprsPlmnList[ulIdx].ulMnc = NAS_MML_INVALID_MNC;
        }
        else
        {
            (VOS_VOID)PS_MEM_MOVE(pstForbPlmnInfo->astForbGprsPlmnList + ulIdx,
                 (pstForbPlmnInfo->astForbGprsPlmnList + (ulIdx + 1)),
                 (NAS_MML_MAX_FORBGPRSPLMN_NUM - (ulIdx + 1)) * sizeof(NAS_MML_PLMN_ID_STRU));
        }

        pstForbPlmnInfo->ucForbGprsPlmnNum --;

    }

    return;
}



VOS_VOID NAS_MML_AddForbRoamLa (
    NAS_MML_LAI_STRU                                       *pstLai,
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU               *pstForbRoamLaInfo
)
{
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU                    *pstMiscellaneousCfgInfo = VOS_NULL_PTR;
    VOS_UINT8                                               ucRealMaxForbRoamLaNum;
    VOS_UINT8                                               ucForbRoamLaNum;
    VOS_UINT32                                              ulRlst;

    ulRlst = VOS_FALSE;

    /* ����"Forbidden las for roaming" list�У������ */
    ulRlst = NAS_MML_IsLaiInDestLaiList(pstLai, pstForbRoamLaInfo->ucForbRoamLaNum,
                                        pstForbRoamLaInfo->astForbRomLaList);
    if (VOS_TRUE == ulRlst)
    {
        return;
    }

    /* ���ڻ�ȡNV�б��������ֹLA������Ϣ */
    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();

    /* ���NV�е�����ֹLA������Ϣ��ȡ��Ч������ֹ���� */
    ucRealMaxForbRoamLaNum = NAS_MML_MAX_FORBLA_FOR_ROAM_NUM;
    if (VOS_TRUE == pstMiscellaneousCfgInfo->ucMaxForbRoamLaFlg)
    {
        if (pstMiscellaneousCfgInfo->ucMaxForbRoamLaNum <= NAS_MML_MAX_FORBLA_FOR_ROAM_NUM)
        {
            ucRealMaxForbRoamLaNum = pstMiscellaneousCfgInfo->ucMaxForbRoamLaNum;
        }
    }

    if (0 == ucRealMaxForbRoamLaNum )
    {
        return;
    }

    /* ��ȡ��ǰ�б��еĽ�ֹLA���� */
    ucForbRoamLaNum = pstForbRoamLaInfo->ucForbRoamLaNum;

    /* �б�����ʱ���Ƴ����ȱ����Ԫ�� */
    if (ucRealMaxForbRoamLaNum == ucForbRoamLaNum)
    {
        (VOS_VOID)PS_MEM_MOVE(&(pstForbRoamLaInfo->astForbRomLaList[0]),
                    &(pstForbRoamLaInfo->astForbRomLaList[1]),
                     (ucForbRoamLaNum - 1) * sizeof(NAS_MML_LAI_STRU ) );
        ucForbRoamLaNum--;
    }

    /* ���Forbidden for roaming LA���б����� */
    pstForbRoamLaInfo->astForbRomLaList[ucForbRoamLaNum] = (*pstLai);

    /* ���µ�ǰ�б��еĽ�ֹLA���� */
    ucForbRoamLaNum++;
    pstForbRoamLaInfo->ucForbRoamLaNum = ucForbRoamLaNum;

    return;
}
VOS_VOID NAS_MML_AddForbRegLa (
    NAS_MML_LAI_STRU                   *pstLai
)
{
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbPlmnInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucForbRegLaNum;
    VOS_UINT32                          ulRlst;

    ulRlst = VOS_FALSE;

    /* ���ڻ�ȡ"Forbidden LA for regional provision" list */
    pstForbPlmnInfo = NAS_MML_GetForbidPlmnInfo();

    /* ����"Forbidden LA for regional provision" list������� */
    ulRlst = NAS_MML_IsLaiInDestLaiList(pstLai, pstForbPlmnInfo->ucForbRegLaNum,
                                        pstForbPlmnInfo->astForbRegLaList);
    if (VOS_TRUE == ulRlst)
    {
        return;
    }

    /* ��ȡ��ǰ�б���Forbidden LA�ĸ��� */
    ucForbRegLaNum = pstForbPlmnInfo->ucForbRegLaNum;

    /* �б����������Ƴ����ȱ����Ԫ�� */
    if (NAS_MML_MAX_FORBLA_FOR_REG_NUM == ucForbRegLaNum)
    {
        (VOS_VOID)PS_MEM_MOVE(&(pstForbPlmnInfo->astForbRegLaList[0]),
                    &(pstForbPlmnInfo->astForbRegLaList[1]),
                    (ucForbRegLaNum-1)*sizeof(NAS_MML_LAI_STRU));
        ucForbRegLaNum--;
    }

    /* ���Forbidden LA for regional provision���б����� */
    pstForbPlmnInfo->astForbRegLaList[ucForbRegLaNum] = (*pstLai);

    /* ���µ�ǰ�б��еĽ�ֹLA���� */
    ucForbRegLaNum++;
    pstForbPlmnInfo->ucForbRegLaNum = ucForbRegLaNum;

    return;
}


VOS_UINT32 NAS_MML_DelForbLa (
    NAS_MML_LAI_STRU                   *pstLai,
    /* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, begin */
    NAS_MML_REG_DOMAIN_ENUM_UINT8       enDomain
    /* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, end */
)
{
    /* Added by g00322017 for CS REG FAIL FORB LA, 2015-9-23, begin */
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU             *pstForbLaWithValidPeriodList   = VOS_NULL_PTR;
    /* Added by g00322017 for CS REG FAIL FORB LA, 2015-9-23, end */

    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                        *pstForbPlmnInfo                = VOS_NULL_PTR;
    VOS_UINT32                                              ulRlst;
    VOS_UINT8                                               ucLaiIndex;

    /* Added by g00322017 for CS REG FAIL FORB LA, 2015-9-23, begin */
    VOS_UINT32                                              ulIsLaInForbLaWithValidPeriodList;
    /* Added by g00322017 for CS REG FAIL FORB LA, 2015-9-23, end */

    ulRlst                              = VOS_FALSE;
    ulIsLaInForbLaWithValidPeriodList   = VOS_FALSE;
    /* ���ڻ�ȡ��ֹLA����Ϣ */
    pstForbPlmnInfo = NAS_MML_GetForbidPlmnInfo();

    /* Forbidden LA For Roaming�����ı����Ҫ֪ͨ�����,Ӧ�����ж�Forbidden LA for regional provision�����ж�
       Forbidden las for roaming */

    /* ��"Forbidden LA for regional provision" list �в���Ҫɾ����LAI */
    ulRlst = NAS_MML_GetLaiIndexInDestLaiList(pstLai, &ucLaiIndex,
                                              pstForbPlmnInfo->ucForbRegLaNum,
                                              pstForbPlmnInfo->astForbRegLaList);
    /* ���ҵ�LAI�����ɾ������ */
    if(VOS_TRUE == ulRlst)
    {
        if (ucLaiIndex < (pstForbPlmnInfo->ucForbRegLaNum - 1))
        {
            (VOS_VOID)PS_MEM_MOVE(&(pstForbPlmnInfo->astForbRegLaList[ucLaiIndex]),
                         &(pstForbPlmnInfo->astForbRegLaList[ucLaiIndex + 1]),
                         ((pstForbPlmnInfo->ucForbRegLaNum-ucLaiIndex) - 1) * sizeof(NAS_MML_LAI_STRU));
        }

        /* ɾ��"Forbidden LA for regional provision�󣬸��¸��� */
        pstForbPlmnInfo->ucForbRegLaNum--;
    }

    /* Added by g00322017 for CS REG FAIL FORB LA, 2015-9-23, begin */
    /* Modified by z00359541 for CS REG FAIL FORB LA, 2015-9-28, begin */
    if (NAS_MML_REG_DOMAIN_CS == enDomain)
    {
        pstForbLaWithValidPeriodList = NAS_MML_GetForbLaWithValidPeriodList();
        ulIsLaInForbLaWithValidPeriodList = NAS_MML_GetLaiIndexInRegFailForbLaList(pstLai, &ucLaiIndex,
                                                           pstForbLaWithValidPeriodList->ulForbLaWithValidPeriodNum,
                                                           pstForbLaWithValidPeriodList->astForbLaWithValidPeriodList);
        /* ���ҵ�LAI�����ɾ������ */
        if (VOS_TRUE == ulIsLaInForbLaWithValidPeriodList)
        {
            NAS_MML_DeleteLaFromForbLaWithValidPeriodList(pstForbLaWithValidPeriodList, ucLaiIndex);

            /* ������ʱ�� */
            NAS_MML_StartCustomizedForbLaTimer();
        }
    }
    /* Modified by z00359541 for CS REG FAIL FORB LA, 2015-9-28, end */
    /* Added by g00322017 for CS REG FAIL FORB LA, 2015-9-23, end */

    /* ��"Forbidden las for roaming" list �в���Ҫɾ����LAI */
    ulRlst = NAS_MML_GetLaiIndexInDestLaiList(pstLai, &ucLaiIndex,
                                              pstForbPlmnInfo->ucForbRoamLaNum,
                                              pstForbPlmnInfo->astForbRomLaList);

    /* ���ҵ�LAI�����ɾ������ */
    if (VOS_TRUE == ulRlst)
    {
        /* ɾ��ָ����LAI */
        if (ucLaiIndex < (pstForbPlmnInfo->ucForbRoamLaNum - 1))
        {
            (VOS_VOID)PS_MEM_MOVE(&(pstForbPlmnInfo->astForbRomLaList[ucLaiIndex]),
                         &(pstForbPlmnInfo->astForbRomLaList[ucLaiIndex + 1]),
                         ((pstForbPlmnInfo->ucForbRoamLaNum - ucLaiIndex) - 1) * sizeof(NAS_MML_LAI_STRU));
        }

        /* ɾ��Forbidden LA For Roam��, ���¸��� */
        pstForbPlmnInfo->ucForbRoamLaNum--;
    }
    /* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, begin */
    return (ulRlst | ulIsLaInForbLaWithValidPeriodList);
    /* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, end */
}
VOS_VOID NAS_MML_DelNotAllowRoamPlmnInList(
    VOS_UINT8                          *pucPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstPlmnList
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucPlmnNum;

    ucPlmnNum = *pucPlmnNum;


    i = 0;
    while ( i < ucPlmnNum )
    {
        if (VOS_FALSE == NAS_MML_IsPlmnIdRoamingAllowed(&pstPlmnList[i]))
        {
            if (i < (ucPlmnNum - 1))
            {
                (VOS_VOID)PS_MEM_MOVE(&pstPlmnList[i], &pstPlmnList[i+1],
                            ((ucPlmnNum - i)-1) * sizeof(NAS_MML_PLMN_ID_STRU));
            }

            ucPlmnNum--;

            continue;
        }

        i++;
    }


    *pucPlmnNum = ucPlmnNum;

    return;
}


VOS_UINT32 NAS_MML_DelForbPlmnInList(
    VOS_UINT32                          ulPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pHandlingPlmnList
)
{
    VOS_UINT8                           ucLeftPlmnNum;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo  = VOS_NULL_PTR;

    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode;

    NAS_MML_PLMN_LOCK_CFG_INFO_STRU    *pstPlmnLockCfg     = VOS_NULL_PTR;


    /* ���ڻ�ȡ�ڰ����� */
    pstPlmnLockCfg = NAS_MML_GetPlmnLockCfg();

    enMsMode = NAS_MML_GetMsMode();

    ucLeftPlmnNum     = (VOS_UINT8)ulPlmnNum;
    pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();

    /* ���ڻ�ȡ�ڰ����� */

    /* ɾ�������ں������е����� */
    NAS_MML_DelPlmnsInRefList(&ucLeftPlmnNum, pHandlingPlmnList,
                   pstPlmnLockCfg->ucBlackPlmnLockNum, pstPlmnLockCfg->astBlackPlmnId);

    /* ɾ���������ڰ������е����� */
    if (pstPlmnLockCfg->ucWhitePlmnLockNum != 0)
    {
        NAS_MML_DelPlmnsNotInRefList(&ucLeftPlmnNum, pHandlingPlmnList,
                       pstPlmnLockCfg->ucWhitePlmnLockNum, pstPlmnLockCfg->astWhitePlmnId);
    }

    /* ɾ����ֹ���������,�û�ָ���ѵ�PLMN�ڽ�ֹ�б�ʱ��ע��ɹ�����Ҫ��MMCɾ����PLMN��
    Ϊ�˹��ʱ����ɵ�ɾ�����Ѿ�ע��ɹ������磬���Դ˴�����ɾ����ǰפ�������� */
    NAS_MML_DelEqualPlmnsInForbList(&ucLeftPlmnNum, pHandlingPlmnList,
                                pstForbidPlmnInfo->ucForbPlmnNum, pstForbidPlmnInfo->astForbPlmnIdList);

    /* CS����Ч��PS ONLYʱɾ����ֹGPRS�б��е����� */
    if ((VOS_FALSE == NAS_MML_GetSimCsRegStatus())
     || (NAS_MML_MS_MODE_PS_ONLY == enMsMode))
    {

        /* ɾ����ֹ���������,�û�ָ���ѵ�PLMN�ڽ�ֹ�б�ʱ��ע��ɹ�����Ҫ��MMCɾ����PLMN��
        Ϊ�˹��ʱ����ɵ�ɾ�����Ѿ�ע��ɹ������磬���Դ˴�����ɾ����ǰפ�������� */
        NAS_MML_DelEqualPlmnsInForbList(&ucLeftPlmnNum, pHandlingPlmnList,
                                        pstForbidPlmnInfo->ucForbGprsPlmnNum, pstForbidPlmnInfo->astForbGprsPlmnList);
    }

    /* ���б���ɾ�����������ε����� */
    NAS_MML_DelNotAllowRoamPlmnInList(&ucLeftPlmnNum, pHandlingPlmnList);

    return ucLeftPlmnNum;

}
VOS_UINT32 NAS_MML_DelInvalidPlmnFromList(
    VOS_UINT32                          ulPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstHandlingPlmnList
)
{

    VOS_UINT32                          i;

    /* ɾ�����б��е���Ч���� */


    i = 0;
    while ( i < ulPlmnNum )
    {
        if (VOS_FALSE == NAS_MML_IsPlmnIdValid(pstHandlingPlmnList + i))
        {
            if (i < (ulPlmnNum - 1))
            {
                (VOS_VOID)PS_MEM_MOVE(&pstHandlingPlmnList [i], &pstHandlingPlmnList[i+1],
                            ((ulPlmnNum - i) - 1 ) * sizeof(NAS_MML_PLMN_ID_STRU) );
            }
            ulPlmnNum--;
            continue;
        }

        i++;
    }


    return ulPlmnNum;

}
VOS_VOID NAS_MML_DelPlmnsInRefList(
    VOS_UINT8                          *pHandlingPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pHandlingPlmnList,
    VOS_UINT8                           ucRefPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pRefPlmnList
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucPlmnNum;
    VOS_UINT32                          ulRlst;

    ucPlmnNum = *pHandlingPlmnNum;


    i = 0;
    while ( i < ucPlmnNum )
    {
        ulRlst = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pHandlingPlmnList + i, ucRefPlmnNum, pRefPlmnList);

        if ( VOS_TRUE == ulRlst )
        {
            if (i < (ucPlmnNum - 1))
            {
                (VOS_VOID)PS_MEM_MOVE(&pHandlingPlmnList [i], &pHandlingPlmnList[ i + 1 ],
                            ((ucPlmnNum - i) - 1 ) * sizeof(NAS_MML_PLMN_ID_STRU));
            }
            ucPlmnNum--;
            continue;
        }
        i++;
    }


    *pHandlingPlmnNum = ucPlmnNum;

    return;
}


VOS_VOID NAS_MML_DelPlmnsNotInRefList(
    VOS_UINT8                          *pHandlingPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pHandlingPlmnList,
    VOS_UINT8                           ucRefPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pRefPlmnList
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucPlmnNum;
    VOS_UINT32                          ulRlst;

    ucPlmnNum = *pHandlingPlmnNum;


    i = 0;
    while ( i < ucPlmnNum )
    {
        ulRlst = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pHandlingPlmnList + i, ucRefPlmnNum, pRefPlmnList);

        /* ��������pRefPlmnList�У���ɾ�� */
        if ( VOS_FALSE == ulRlst )
        {
            if (i < (ucPlmnNum - 1))
            {
                (VOS_VOID)PS_MEM_MOVE(&pHandlingPlmnList [i], &pHandlingPlmnList[ i + 1 ],
                            ((ucPlmnNum - i) - 1 ) * sizeof(NAS_MML_PLMN_ID_STRU));
            }

            ucPlmnNum--;
            continue;
        }
        i++;
    }


    *pHandlingPlmnNum = ucPlmnNum;

    return;
}
VOS_UINT32 NAS_MML_GetPlmnIdxInList (
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    VOS_UINT32                          ulPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstPlmnIdList
)
{
    VOS_UINT32                          i;

    for ( i = 0; i < ulPlmnNum; i++ )
    {
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstPlmnId, (pstPlmnIdList + i)))
        {
            break;
        }
    }

    return i;
}


VOS_UINT32 NAS_MML_IsGsmOnlyMode(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatOrder
)
{
    if ( (1                        == pstRatOrder->ucRatNum)
      && (NAS_MML_NET_RAT_TYPE_GSM == pstRatOrder->aucRatPrio[0]) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_UINT32 NAS_MML_IsWcdmaOnlyMode(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatOrder
)
{
    if ( (1                          == pstRatOrder->ucRatNum)
      && (NAS_MML_NET_RAT_TYPE_WCDMA == pstRatOrder->aucRatPrio[0]) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_UINT32 NAS_MML_IsWcdmaPrioGsm(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatOrder
)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT8                           ucWcdmaPrioGsmFlag;

    ucWcdmaPrioGsmFlag = VOS_FALSE;

    for (ulIndex = 0; ulIndex < pstRatOrder->ucRatNum; ulIndex++)
    {
        if (NAS_MML_NET_RAT_TYPE_GSM == pstRatOrder->aucRatPrio[ulIndex])
        {
            ucWcdmaPrioGsmFlag = VOS_FALSE;
            return ucWcdmaPrioGsmFlag;
        }

        if (NAS_MML_NET_RAT_TYPE_WCDMA == pstRatOrder->aucRatPrio[ulIndex])
        {
            ucWcdmaPrioGsmFlag = VOS_TRUE;
            return ucWcdmaPrioGsmFlag;
        }
    }

    return ucWcdmaPrioGsmFlag;
}



VOS_UINT32 NAS_MML_IsLteOnlyMode(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatOrder
)
{
    if ( (1                        == pstRatOrder->ucRatNum)
      && (NAS_MML_NET_RAT_TYPE_LTE == pstRatOrder->aucRatPrio[0]) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_VOID NAS_MML_RemoveRoamPlmnInSrchList(
    VOS_UINT8                          *pucPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstPlmnList
)
{
    VOS_UINT32                          i;

    for ( i = 0; i < *pucPlmnNum; )
    {
        /* ����б��е�PLMN��׼�����Σ��򽫸�PLMN�Ƴ� */
        if ( VOS_FALSE == NAS_MML_IsPlmnIdRoamingAllowed(&pstPlmnList[i]) )
        {
            /* ����������һ��Ԫ�أ����Ƴ� */
            if ( (i + 1) != (*pucPlmnNum) )
            {
                (VOS_VOID)PS_MEM_MOVE(&pstPlmnList[i], &pstPlmnList[i+1],
                            ((*pucPlmnNum - i) - 1)*sizeof(NAS_MML_PLMN_ID_STRU));

            }

            /* ���ܸ�����һ */
            (*pucPlmnNum)--;

            continue;
        }
        i++;
    }

    return;
}
VOS_UINT32 NAS_MMC_IsRoam()
{
    NAS_MML_PLMN_ID_STRU               *pstCurplmn = VOS_NULL_PTR;

    pstCurplmn = NAS_MML_GetCurrCampPlmnId();

    /*��HPLMN��ͬ��ֱ�ӷ�������*/
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(pstCurplmn))
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}
VOS_UINT32 NAS_MML_IsHplmnInEplmnList()
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnList = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstEplmnList = NAS_MML_GetEquPlmnList();

    if (VOS_TRUE == pstEplmnList->ucValidFlg)
    {
        for (i = 0; i < pstEplmnList->ucEquPlmnNum; i++)
        {
            if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(&pstEplmnList->astEquPlmnAddr[i]))
            {
                return VOS_TRUE;
            }
        }
    }
    return VOS_FALSE;
}


VOS_UINT32 NAS_MML_IsCurrCampPlmnInEplmnList(VOS_VOID)
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnList        = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstCurrCampPlmnId   = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstEplmnList              = NAS_MML_GetEquPlmnList();
    pstCurrCampPlmnId         = NAS_MML_GetCurrCampPlmnId();

    if (VOS_TRUE == pstEplmnList->ucValidFlg)
    {
        for (i = 0; i < pstEplmnList->ucEquPlmnNum; i++)
        {
            if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstCurrCampPlmnId, &pstEplmnList->astEquPlmnAddr[i]))
            {
                return VOS_TRUE;
            }
        }
    }
    return VOS_FALSE;
}

/* Added by z00359541 for CS REG FAIL FORB LA, 2015-10-10, begin */
/*****************************************************************************
 �� �� ��  : NAS_MML_IsPlmnInEplmnList
 ��������  : PLMN�Ƿ���EPLMN�б���
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��10��
    ��    ��   : z00359541
    �޸�����   : ����

*****************************************************************************/
VOS_UINT32 NAS_MML_IsPlmnInEplmnList(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId                                   
)
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnList        = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstEplmnList = NAS_MML_GetEquPlmnList();

    if (VOS_TRUE == pstEplmnList->ucValidFlg)
    {
        for (i = 0; i < pstEplmnList->ucEquPlmnNum; i++)
        {
            if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstPlmnId, &pstEplmnList->astEquPlmnAddr[i]))
            {
                return VOS_TRUE;
            }
        }
    }
    return VOS_FALSE;
}
/* Added by z00359541 for CS REG FAIL FORB LA, 2015-10-10, end */

VOS_UINT32 NAS_MML_GetLaiForbType(
    NAS_MML_LAI_STRU                   *pstLai
)
{
    VOS_UINT32                          ulPlmnLaType;
    NAS_MML_PLMN_ID_STRU               *pstPlmnId         = VOS_NULL_PTR;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulRlst;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_LMM_INFO_STRU                   stLmmInfo;
    NAS_MML_TAI_STRU                    stTai;
    VOS_UINT32                          ulForbidFlag;

    VOS_UINT32                          ulForbiddenRegLaFlag;
#endif

    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnWithRat;

    ulPlmnLaType      = NAS_MML_PLMN_FORBID_NULL;
    pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();
    pstPlmnId         = &(pstLai->stPlmnId);


    /* ��forbid plmn�б��� */
    ulRlst = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstPlmnId,
                                          pstForbidPlmnInfo->ucForbPlmnNum,
                                          pstForbidPlmnInfo->astForbPlmnIdList);
    if(VOS_TRUE == ulRlst)
    {
        return NAS_MML_PLMN_FORBID_PLMN;
    }


    /* ���쵱ǰ���뼼����PLMN ID */
    stPlmnWithRat.stPlmnId.ulMcc    = pstLai->stPlmnId.ulMcc;
    stPlmnWithRat.stPlmnId.ulMnc    = pstLai->stPlmnId.ulMnc;
    stPlmnWithRat.enRat             = pstLai->enCampPlmnNetRat;

    /* �жϵ�ǰPLMN�Ƿ��ڽ�ֹRAT��PLMN�б���ͬʱ��ǰ���뼼������ֹ,����Ϊ��ǰPLMNΪ��ֹ���� */
    if (VOS_TRUE == NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
    {
        return NAS_MML_PLMN_FORBID_PLMN;
    }

    /* �ж�PLMN��RAT�ڽ�ֹ���뼼���б��У�����Ϊ��ǰRAT��Ӧ����Ϊ��ֹ���� */
    if (VOS_TRUE == NAS_MML_IsRatInForbiddenList(stPlmnWithRat.enRat))
    {
        return NAS_MML_PLMN_FORBID_PLMN;
    }


    /* ��PLMN ID�Ƿ�������������PLMN �б��� */
    if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInLockPlmnList(pstPlmnId))
    {
        return NAS_MML_PLMN_FORBID_PLMN;
    }

    /* ����������ʱ */
    if (VOS_FALSE == NAS_MML_IsPlmnIdRoamingAllowed(pstPlmnId))
    {
        return NAS_MML_PLMN_FORBID_PLMN;
    }

    /* ��forbid plmn for gprs�б��� */
    ulRlst = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstPlmnId,
                                          pstForbidPlmnInfo->ucForbGprsPlmnNum,
                                          pstForbidPlmnInfo->astForbGprsPlmnList);
    if(VOS_TRUE == ulRlst)
    {
        ulPlmnLaType  |=   NAS_MML_PLMN_FORBID_PLMN_FOR_GPRS;
    }

    /* L��TAI��Ҫ��LAI�л�ȡ���յ�L��ϵͳ��Ϣ�����µ���LAI */
#if (FEATURE_ON == FEATURE_LTE)
    ulForbidFlag         = VOS_FALSE;

    ulForbiddenRegLaFlag = NAS_MML_PLMN_FORBID_NULL;

    stTai.stPlmnId.ulMcc = pstLai->stPlmnId.ulMcc;
    stTai.stPlmnId.ulMnc = pstLai->stPlmnId.ulMnc;
    stTai.stTac.ucTac    = pstLai->aucLac[0];
    stTai.stTac.ucTacCnt = pstLai->aucLac[1];

    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        if ( MMC_LMM_SUCC == Nas_GetLteInfo(NAS_LMM_FORB_TAI_ROAM_LIST, &stLmmInfo) )
        {
            ulForbidFlag = NAS_MML_IsTaiInDestTaiList (&stTai,
                                                        stLmmInfo.u.stForbRoamTaiList.ulTaNum,
                                                        stLmmInfo.u.stForbRoamTaiList.astTa);
        }

        if (VOS_TRUE == ulForbidFlag)
        {
            ulPlmnLaType |= NAS_MML_PLMN_FORBID_PLMN;
        }

        if ( MMC_LMM_SUCC == Nas_GetLteInfo(NAS_LMM_FORB_TAI_RPOS_LIST, &stLmmInfo) )
        {
            ulForbiddenRegLaFlag = NAS_MML_IsTaiInDestTaiList (&stTai,
                                                        stLmmInfo.u.stForbRposTaiList.ulTaNum,
                                                        stLmmInfo.u.stForbRposTaiList.astTa);
        }

        if (VOS_TRUE == ulForbiddenRegLaFlag)
        {
             ulPlmnLaType  |= NAS_MML_PLMN_FORBID_REG_LA;
        }

    }
    else
#endif
    {
        /* �Ƿ��� ForbLA��Ϣ�� */
        /* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, begin */
        ulRlst =  NAS_MML_GetLaiIndexInForbLaWithValidPeriodList(pstLai,
                    &(pstForbidPlmnInfo->stForbLaWithValidPeriod));

        if(NAS_MML_CUSTOMIZE_FORB_LA_MAX_NUM != ulRlst)
        {
             ulPlmnLaType  |=   NAS_MML_PLMN_FORBID_ROAM_LA;
        }
        /* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, end */

        ulRlst =  NAS_MML_IsLaiInDestLaiList(pstLai,
                                            pstForbidPlmnInfo->ucForbRoamLaNum,
                                            pstForbidPlmnInfo->astForbRomLaList);

        if(VOS_TRUE == ulRlst)
        {
             ulPlmnLaType  |=   NAS_MML_PLMN_FORBID_ROAM_LA;
        }

        ulRlst =  NAS_MML_IsLaiInDestLaiList(pstLai,
                                            pstForbidPlmnInfo->ucForbRegLaNum,
                                            pstForbidPlmnInfo->astForbRegLaList);

        if (VOS_TRUE == ulRlst)
        {
             ulPlmnLaType  |=   NAS_MML_PLMN_FORBID_REG_LA;
        }
    }

    return ulPlmnLaType;
}





VOS_UINT32 NAS_MML_IsCampPlmnInfoChanged(
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstOldCampInfo,
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstNewCampInfo
)
{
    VOS_UINT32                          i;

    /* ����Plmn�� lac,rac,cellid��cell��������ϵͳ��ģʽ�Ƿ��б仯 */
    if ((pstOldCampInfo->stLai.stPlmnId.ulMcc  != pstNewCampInfo->stLai.stPlmnId.ulMcc)
     || (pstOldCampInfo->stLai.stPlmnId.ulMnc  != pstNewCampInfo->stLai.stPlmnId.ulMnc)
     || (pstOldCampInfo->ucRac                 != pstNewCampInfo->ucRac)
     || (pstOldCampInfo->enSysSubMode          != pstNewCampInfo->enSysSubMode)

     )
    {
        return VOS_TRUE;
    }

    for ( i = 0 ; i < NAS_MML_MAX_LAC_LEN ; i++ )
    {
        if (pstOldCampInfo->stLai.aucLac[i] != pstNewCampInfo->stLai.aucLac[i])
        {
            return VOS_TRUE;
        }
    }

    if (pstOldCampInfo->stCampCellInfo.ucCellNum != pstNewCampInfo->stCampCellInfo.ucCellNum)
    {
        return VOS_TRUE;
    }

    for ( i = 0 ; i < RRC_NAS_AT_CELL_MAX_NUM ; i++ )
    {
        if (pstOldCampInfo->stCampCellInfo.astCellInfo[i].ulCellId
                    != pstNewCampInfo->stCampCellInfo.astCellInfo[i].ulCellId)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
NAS_MML_RRC_SYS_SUBMODE_ENUM_UINT8 NAS_MML_ConvertGprsSupportIndToSysSubMode(
    VOS_UINT8                           ucGprsSupportInd
)
{
    NAS_MML_RRC_SYS_SUBMODE_ENUM_UINT8  enSysSubMode;

    switch ( ucGprsSupportInd )
    {
        case NAS_MML_GAS_SUBMODE_GSM:
            enSysSubMode = NAS_MML_RRC_SYS_SUBMODE_GSM;
            break;

        case NAS_MML_GAS_SUBMODE_GPRS:
            enSysSubMode = NAS_MML_RRC_SYS_SUBMODE_GPRS;
            break;

        case NAS_MML_GAS_SUBMODE_EDGE:
            enSysSubMode = NAS_MML_RRC_SYS_SUBMODE_EDGE;
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MML_ConvertGasNetModeToMmlNetMode, enSysSubMode invalid");
            enSysSubMode = NAS_MML_RRC_SYS_SUBMODE_NULL;
            break;
    }

    return enSysSubMode;
}


VOS_VOID NAS_MML_SecContext3GTO2G(
    VOS_UINT8                           *pucIk,
    VOS_UINT8                           *pucCk,
    VOS_UINT8                           *pucKc
)
{
    /* ��ʱ���������� for ѭ�� */
    VOS_UINT8       i;

    /* ����������� IK ����ʱ���� */
    VOS_UINT8       aucIk[NAS_MML_UMTS_IK_LEN];

    /* ����������� CK ����ʱ���� */
    VOS_UINT8       aucCk[NAS_MML_UMTS_CK_LEN];

    /* ���� Kc */
    VOS_UINT8       aucKc[NAS_MML_GSM_KC_LEN];

    PS_MEM_SET(aucIk, 0x00, sizeof(aucIk));
    PS_MEM_SET(aucCk, 0x00, sizeof(aucCk));
    PS_MEM_SET(aucKc, 0x00, sizeof(aucKc));

    /* ��� IK */
    PS_MEM_CPY(aucIk, pucIk, NAS_MML_UMTS_IK_LEN);

    /* ��� CK */
    PS_MEM_CPY(aucCk, pucCk, NAS_MML_UMTS_CK_LEN);

    /* ���ù�ʽ���� aucKc */
    /*Kc[GSM] = CK1 xor CK2 xor IK1 xor IK2������CKi �� IKi �ĳ��ȶ�Ϊ 64 bits ��
    CK = CK1 || CK2 ��IK = IK1 || IK2��*/
    for (i = 0; i < NAS_MML_GSM_KC_LEN; i ++)
    {
        aucKc[i] = aucCk[i] ^ aucCk[NAS_MML_GSM_KC_LEN + i];
    }
    for (i = 0; i < NAS_MML_GSM_KC_LEN; i ++)
    {
        aucKc[i] = aucKc[i] ^ aucIk[i];
    }
    for (i = 0; i < NAS_MML_GSM_KC_LEN; i ++)
    {
        aucKc[i] = aucKc[i] ^ aucIk[NAS_MML_GSM_KC_LEN + i];
    }

    /* �� KC д�ص���������� */
    PS_MEM_CPY(pucKc, aucKc, NAS_MML_GSM_KC_LEN);

    return;

}
VOS_VOID NAS_MML_SecContext2GTO3G(
    VOS_UINT8                           *pucIk,
    VOS_UINT8                           *pucCk,
    VOS_UINT8                           *pucKc
)
{
    /* ��ʱ���������� for ѭ�� */
    VOS_UINT8       i;

    /* ���� IK */
    VOS_UINT8       aucIk[NAS_MML_UMTS_IK_LEN];

    /* ���� CK */
    VOS_UINT8       aucCk[NAS_MML_UMTS_CK_LEN];

    /* ����������� KC ����ʱ���� */
    VOS_UINT8       aucKc[NAS_MML_GSM_KC_LEN];

    PS_MEM_SET(aucIk, 0x00, sizeof(aucIk));
    PS_MEM_SET(aucCk, 0x00, sizeof(aucCk));
    PS_MEM_SET(aucKc, 0x00, sizeof(aucKc));

    /* ��� KC */
    PS_MEM_CPY(aucKc, pucKc, NAS_MML_GSM_KC_LEN);

    /* ���ù�ʽ���� IK��CK */
    /* ת��������Կ */
    /* ck=kc||kc(����||Ϊ���ӷ���) */
    PS_MEM_CPY(aucCk, aucKc, NAS_MML_GSM_KC_LEN);
    PS_MEM_CPY((aucCk + NAS_MML_GSM_KC_LEN), aucKc, NAS_MML_GSM_KC_LEN);

    /* ת��һ���Լ����Կ */
    /* ik=Kc1 xor Kc2 || Kc || Kc1 xor Kc2(����||Ϊ���ӷ��š�Kc = Kc1 || Kc2) */
    for (i = 0; i < (NAS_MML_GSM_KC_LEN/2); i++)
    {
        aucIk[i] = aucKc[i] ^ aucKc[(NAS_MML_GSM_KC_LEN/2) + i];
        aucIk[NAS_MML_GSM_KC_LEN + (NAS_MML_GSM_KC_LEN/2) + i] = aucIk[i];
    }
    PS_MEM_CPY((aucIk + (NAS_MML_GSM_KC_LEN/2)), aucKc, NAS_MML_GSM_KC_LEN);

    /* �� IK д�ص���������� */
    PS_MEM_CPY(pucIk, aucIk, NAS_MML_UMTS_IK_LEN);

    /* �� CK д�ص���������� */
    PS_MEM_CPY(pucCk, aucCk, NAS_MML_UMTS_CK_LEN);

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MML_ConvertNasPlmnToLMMFormat
 ��������  : ��MCC��MNC�ֿ��ĸ�ʽת��ΪLMM��3�ֽڸ�ʽPLMN(LAI��ʽ��PLMN)
            (10.5.1.3 Location Area Identification)
             8 7 6 5     4 3 2 1
            Location Area Identification IEI       octet 1
            MCC digit 2     MCC digit 1            octet 2
            MNC digit 3     MCC digit 3            octet 3
            MNC digit 2     MNC digit 1            octet 4

            ����:230,02f (mcc:0x000302,mnc:0x0f0200)  --> 32f020

 �������  : pGUNasPlmn,GU��ʽ��PLMN ID
 �������  : pLMMPlmn:L��ʽ��PLMN ID
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��3��28��
    ��    ��   : likelai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MML_ConvertNasPlmnToLMMFormat(
    MMC_LMM_PLMN_ID_STRU               *pstLMMPlmn,
    NAS_MML_PLMN_ID_STRU               *pstGUNasPlmn
)
{
    pstLMMPlmn->aucPlmnId[0]
      = (VOS_UINT8)(0x0000000F & pstGUNasPlmn->ulMcc);
    pstLMMPlmn->aucPlmnId[0]
     |= (VOS_UINT8)((0x00000F00 & pstGUNasPlmn->ulMcc) >> 4);

    pstLMMPlmn->aucPlmnId[1]
     = (VOS_UINT8)((0x000F0000 & pstGUNasPlmn->ulMcc) >> 16);

    pstLMMPlmn->aucPlmnId[1]
     |= (VOS_UINT8)((0x000F0000 & pstGUNasPlmn->ulMnc) >> 12);

    pstLMMPlmn->aucPlmnId[2]
     = (VOS_UINT8)(0x0000000F & pstGUNasPlmn->ulMnc);
    pstLMMPlmn->aucPlmnId[2]
     |= (VOS_UINT8)((0x00000F00 & pstGUNasPlmn->ulMnc) >> 4);

    return ;

}
#endif


VOS_VOID NAS_MML_SortSpecRatPrioHighest(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enSpecRat,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList
)
{
    VOS_UINT32                          i;

    /* ���򷽷��ǣ���pstPrioRatList�ҵ�ָ���Ľ��뼼���󣬽������pstPrioRatList��ǰ�� */
    for (i = 0; i < pstPrioRatList->ucRatNum; i++)
    {
        if (enSpecRat == pstPrioRatList->aucRatPrio[i])
        {
            (VOS_VOID)PS_MEM_MOVE(&(pstPrioRatList->aucRatPrio[1]),
                        &(pstPrioRatList->aucRatPrio[0]), i);

            pstPrioRatList->aucRatPrio[0] = enSpecRat;

            break;
        }
    }

    return;
}
VOS_VOID NAS_MML_SortSpecRatPrioLowest(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enSpecRat,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList
)
{
    VOS_UINT32                             i;
    VOS_UINT8                              ucRatNumIndex;

    if (pstPrioRatList->ucRatNum <= 1)
    {
        return;
    }

    ucRatNumIndex = pstPrioRatList->ucRatNum - 1;

    /* ���򷽷��ǣ���pstPrioRatList�ҵ�ָ���Ľ��뼼���󣬽������pstPrioRatList����� */
    for (i = 0; i < ucRatNumIndex; i++)
    {
        if (enSpecRat == pstPrioRatList->aucRatPrio[i])
        {
            /*lint -e961*/
            (VOS_VOID)PS_MEM_MOVE(&(pstPrioRatList->aucRatPrio[i]),
                        &(pstPrioRatList->aucRatPrio[i+1]),
                        (pstPrioRatList->ucRatNum-i-1));
            /*lint +e961*/
            pstPrioRatList->aucRatPrio[pstPrioRatList->ucRatNum-1] = enSpecRat;

            break;
        }
    }

    return;
}
VOS_UINT32 NAS_MML_IsPlmnIdForbiddenByWhiteBlackList (
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_PLMN_LOCK_CFG_INFO_STRU    *pstPlmnLockCfg = VOS_NULL_PTR;
    /* ���ڻ�ȡ�ڰ����� */
    pstPlmnLockCfg = NAS_MML_GetPlmnLockCfg();

    if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstPlmnId,
                                                   pstPlmnLockCfg->ucBlackPlmnLockNum,
                                                   pstPlmnLockCfg->astBlackPlmnId))     /* ��PLMN�ں������б��� */
    {
       return VOS_TRUE;
    }

    if (pstPlmnLockCfg->ucWhitePlmnLockNum != 0)
    {

        if (VOS_FALSE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstPlmnId,
                                                        pstPlmnLockCfg->ucWhitePlmnLockNum,
                                                        pstPlmnLockCfg->astWhitePlmnId))     /* ��PLMN���ڰ������б��� */
        {
            return VOS_TRUE;
        }

    }

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_MML_UpdateEpsConnectionStatus(MMC_LMM_CONN_STATE_ENUM_UINT32 enEpsConnState)
{
    /* ����LMM������״̬ */
    switch (enEpsConnState)
    {
        case MMC_LMM_CONN_ESTING:
        case MMC_LMM_CONNECTED_SIG:
            NAS_MML_SetEpsSigConnStatusFlg(VOS_TRUE);
            NAS_MML_SetEpsServiceConnStatusFlg(VOS_FALSE);
            break;

        case MMC_LMM_CONNECTED_DATA:
            NAS_MML_SetEpsServiceConnStatusFlg(VOS_TRUE);
            break;

        case MMC_LMM_CONN_IDLE:
            NAS_MML_SetEpsSigConnStatusFlg(VOS_FALSE);
            NAS_MML_SetEpsServiceConnStatusFlg(VOS_FALSE);
            break;

        default:
            break;
    }

}
VOS_UINT32 NAS_MML_IsCsfbServiceStatusExist(VOS_VOID)
{
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enCsfbServiceStatus;
    VOS_UINT32                                              ulCsfbExistFlag;

    /* Ĭ��CSFB������ */
    ulCsfbExistFlag     = VOS_FALSE;
    enCsfbServiceStatus = NAS_MML_GetCsfbServiceStatus();

    switch ( enCsfbServiceStatus )
    {
        /* CSFB��־������ */
        case NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST :
            ulCsfbExistFlag = VOS_FALSE;
            break;

        /* ����MO�ǽ������е�CC��CSFB��־ */
        case NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_CC_EXIST :
            ulCsfbExistFlag = VOS_TRUE;
            break;

        /* ����MO��SS��CSFB��־ */
        case NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST :
            ulCsfbExistFlag = VOS_TRUE;
            break;

        /* ����MO�����е�CSFB��־ */
        case NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST :
            ulCsfbExistFlag = VOS_TRUE;
            break;

        /* ����MT���е�CSFB��־ */
        case NAS_MML_CSFB_SERVICE_STATUS_MT_EXIST :
            ulCsfbExistFlag = VOS_TRUE;
            break;

        /* CSFB��־������ */
        default:
            ulCsfbExistFlag = VOS_FALSE;
            break;
    }

    return ulCsfbExistFlag;
}
NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8 NAS_MML_GetLteUeOperationMode( VOS_VOID)
{
    NAS_MML_LTE_UE_USAGE_SETTING_ENUM_UINT8                 enLteUeUsageSetting;
    NAS_MML_MS_MODE_ENUM_UINT8                              enMsMode;

    enMsMode            = NAS_MML_GetMsMode();
    enLteUeUsageSetting = NAS_MML_GetLteUeUsageSetting();

    /* PS ONLY��Ϊ�������ģ���ΪPS_2 */
    if ( (NAS_MML_MS_MODE_PS_ONLY                    == enMsMode)
      && (NAS_MML_LTE_UE_USAGE_SETTING_DATA_CENTRIC  == enLteUeUsageSetting) )
    {
        return NAS_MML_LTE_UE_OPERATION_MODE_PS_2;
    }

    /* CS_PS ��Ϊ�������ģ���ΪCS_PS_2 */
    if ( (NAS_MML_MS_MODE_PS_CS                      == enMsMode)
      && (NAS_MML_LTE_UE_USAGE_SETTING_DATA_CENTRIC  == enLteUeUsageSetting) )
    {
        return NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_2;
    }

    /* PS ONLY��Ϊ�������ģ���ΪPS_1 */
    if ( (NAS_MML_MS_MODE_PS_ONLY                    == enMsMode)
      && (NAS_MML_LTE_UE_USAGE_SETTING_VOICE_CENTRIC == enLteUeUsageSetting) )
    {
        return NAS_MML_LTE_UE_OPERATION_MODE_PS_1;
    }

    /* CS_PS ��Ϊ�������ģ���ΪCS_PS_1 */
    if ( (NAS_MML_MS_MODE_PS_CS                      == enMsMode)
      && (NAS_MML_LTE_UE_USAGE_SETTING_VOICE_CENTRIC == enLteUeUsageSetting) )
    {
        return NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1;
    }

    /* �쳣����,PS ONLY����ΪPS_2 */
    if ( NAS_MML_MS_MODE_PS_ONLY                    == enMsMode )
    {
        return NAS_MML_LTE_UE_OPERATION_MODE_PS_2;
    }

    /* CS_PS����ΪCS_PS_2 */
    return NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_2;
}



VOS_UINT32 NAS_MML_IsCsfbMoServiceStatusExist(VOS_VOID)
{
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enCsfbServiceStatus;

    enCsfbServiceStatus = NAS_MML_GetCsfbServiceStatus();

    if ( (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_CC_EXIST == enCsfbServiceStatus)
      || (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == enCsfbServiceStatus)
      || (NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST == enCsfbServiceStatus) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


#endif

VOS_UINT32 NAS_MML_IsEquPlmnInfoChanged(
    NAS_MML_EQUPLMN_INFO_STRU          *pstSrcEquPlmnInfo
)
{
    VOS_UINT32                          i;
    NAS_MML_EQUPLMN_INFO_STRU          *pstDstEquPlmnInfo = VOS_NULL_PTR;

    pstDstEquPlmnInfo   = NAS_MML_GetEquPlmnList();

    /* ��ЧPLMN�ĸ�����ȣ��ҵ�ЧPLMN��ȫ��ͬ����Eplmn��Ϣû�иı� */
    if ( pstSrcEquPlmnInfo->ucEquPlmnNum == pstDstEquPlmnInfo->ucEquPlmnNum )
    {
        for ( i = 0 ; i < pstSrcEquPlmnInfo->ucEquPlmnNum; i++ )
        {
            if ((pstSrcEquPlmnInfo->astEquPlmnAddr[i].ulMcc != pstDstEquPlmnInfo->astEquPlmnAddr[i].ulMcc)
             || (pstSrcEquPlmnInfo->astEquPlmnAddr[i].ulMnc != pstDstEquPlmnInfo->astEquPlmnAddr[i].ulMnc))
            {
                /* ��ЧPLMN�ı䣬���� VOS_TRUE */
                return VOS_TRUE;
            }

        }

        /* ��ЧPLMNû�иı䣬���� VOS_FALSE */
        return VOS_FALSE;
    }

    /* ��ЧPLMN�ĸ������ȣ���ЧPLMN�϶������˸ı䣬���� VOS_TRUE */
    return VOS_TRUE;
}


VOS_VOID NAS_MML_GetMsNetworkCapability(
    NAS_MML_MS_NETWORK_CAPACILITY_STRU  *pstMsNetworkCapbility
)
{
    VOS_INT8                            cVersion;
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability = VOS_NULL_PTR;


#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode;
    VOS_UINT8                           ucIsrSupport;

    enMsMode        = NAS_MML_GetMsMode();
    ucIsrSupport    = NAS_MML_GetIsrSupportFlg();
#endif

    pstMsCapability = NAS_MML_GetMsCapability();
    cVersion        = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_PS);

    pstMsNetworkCapbility->ucNetworkCapabilityLen = NAS_MML_DEFAULT_NETWORKCAPABILITY_LEN;
    PS_MEM_CPY(pstMsNetworkCapbility->aucNetworkCapability, pstMsCapability->stMsNetworkCapability.aucNetworkCapability,
                pstMsNetworkCapbility->ucNetworkCapabilityLen);

    if(PS_PTL_VER_PRE_R99 == cVersion)
    {
        pstMsNetworkCapbility->aucNetworkCapability[0] &= 0xfe;
    }
    else
    {
        pstMsNetworkCapbility->aucNetworkCapability[0] |= 0x01;
    }

    if (PS_PTL_VER_R7 <= cVersion)
    {
        /* ĿǰNV����Network cap��д����Ϊ2,���Э��汾ΪR7��R7֮��,�䳤��Ϊ3 */
        pstMsNetworkCapbility->ucNetworkCapabilityLen++;

        if (pstMsCapability->stMsNetworkCapability.ucNetworkCapabilityLen > 2)
        {
            pstMsNetworkCapbility->aucNetworkCapability[2] = pstMsCapability->stMsNetworkCapability.aucNetworkCapability[2];
        }
        else
        {
            pstMsNetworkCapbility->aucNetworkCapability[2] = 0x0;
        }

#if (FEATURE_ON == FEATURE_LTE)

        /* ���֧��LTE��ģʽΪCS_PSʱ��Ϊ֧��EMM Combined procedures capability */
        if ((VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
         && (NAS_MML_MS_MODE_PS_CS == enMsMode))
        {
            pstMsNetworkCapbility->aucNetworkCapability[2] |= 0x20;
        }
        else
#endif
        {
            pstMsNetworkCapbility->aucNetworkCapability[2] &= 0xDF;
        }
        /* ���֧��LTE,����Ϊ֧��ISR, ISR support��Ӧbit��1 */

#if (FEATURE_ON == FEATURE_LTE)
        if ( (VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
          && (VOS_TRUE == ucIsrSupport))
        {
            pstMsNetworkCapbility->aucNetworkCapability[2] |= 0x10;
        }
        else
#endif
        {
            pstMsNetworkCapbility->aucNetworkCapability[2] &= 0xEF;
        }

    }
}


VOS_VOID NAS_MML_SoftReBoot_WithLineNoAndFileID(
    VOS_UINT32                          ulLineNO,
    VOS_UINT32                          ulFileID,
    NAS_MML_REBOOT_SCENE_ENUM_UINT8     ucRebootScean
)
{
    VOS_UINT32                          ulSlice;
    VOS_UINT32                          ulTaskTcb;
    VOS_UINT32                          ulPid;
    VOS_UINT32                          enFsmId;
    VOS_UINT32                          enFsmTopState;

    ulSlice   = VOS_GetSlice();


#if   (FEATURE_ON == FEATURE_LTE)
    if ( NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        ulPid = PS_PID_MM;
    }
    else
#endif
    {
        /* GAS �� WRR��FID��ͬ */
        ulPid = WUEPS_PID_WRR;
    }

    ulTaskTcb = VOS_GetTCBFromPid(ulPid);

    enFsmTopState = NAS_MMC_GetFsmTopState();
    enFsmId       = NAS_MMC_GetCurrFsmId();
    /* ��λʱ���������TCB��Ϣ */
    mdrv_om_system_error( NAS_REBOOT_MOD_ID_MML | NAS_MML_SAVE_OTHER_FID_TCB_FLAG | (VOS_INT)ucRebootScean
                          | (VOS_INT)(enFsmTopState << 8) | (VOS_INT)(enFsmId << 16),
                      (VOS_INT)ulTaskTcb,
                      (VOS_INT)((ulFileID << 16) | ulLineNO),
                      (VOS_CHAR *)(&ulSlice),
                      sizeof(ulSlice) );
    return;

}
VOS_UINT8 NAS_MML_IsRaiChanged(VOS_VOID)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo;
    NAS_MML_RAI_STRU                   *pstLastSuccRai;
    VOS_UINT32                           i;

    pstCampInfo    = NAS_MML_GetCurrCampPlmnInfo();
    pstLastSuccRai = NAS_MML_GetPsLastSuccRai();

    if ((pstCampInfo->stLai.stPlmnId.ulMcc != pstLastSuccRai->stLai.stPlmnId.ulMcc)
     || (pstCampInfo->stLai.stPlmnId.ulMnc != pstLastSuccRai->stLai.stPlmnId.ulMnc)
     || (pstCampInfo->ucRac != pstLastSuccRai->ucRac))
    {
        return VOS_TRUE;
    }

    for ( i = 0 ; i < NAS_MML_MAX_LAC_LEN ; i++ )
    {
        if (pstCampInfo->stLai.aucLac[i] != pstLastSuccRai->stLai.aucLac[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;

}


VOS_UINT8 NAS_MML_CompareLai(
    NAS_MML_LAI_STRU                    *pstCurLai,
    NAS_MML_LAI_STRU                    *pstOldLai
)
{
    VOS_UINT32                         i;

    if (VOS_FALSE == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstCurLai->stPlmnId), &(pstOldLai->stPlmnId)))
    {
        return VOS_FALSE;
    }

    for ( i = 0 ; i < NAS_MML_MAX_LAC_LEN ; i++ )
    {
        if (pstCurLai->aucLac[i] != pstOldLai->aucLac[i])
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;

}

VOS_UINT32 NAS_MML_IsNetworkRegFailCause(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 usRegFailCause
)
{
    /* ԭ��ֵС��280ʱ�����Ǹ����ཻ����ע��ԭ��ֵ */
    if ( usRegFailCause < NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT )
    {
        return VOS_TRUE;
    }

    /* ԭ��ֵ���ڵ���280ʱ�������û��Զ����ע��ԭ��ֵ */
    return VOS_FALSE;
}



VOS_UINT32 NAS_MML_IsRegFailCauseNotifyLmm(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  usRegFailCause
)
{
    /* ԭ��ֵС��300ʱ����Ҫ��ע����֪ͨ��LMM */
    if ( usRegFailCause < NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE )
    {
        return VOS_TRUE;
    }

    /* ԭ��ֵ���ڵ���300ʱ��*/
    return VOS_FALSE;
}


VOS_UINT32 NAS_MML_UnCompressData(
    VOS_UINT8                          *pucDest,
    VOS_UINT32                         *pulDestLen,
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                         *pulSrcLen
)
{
    VOS_UINT32                          ulRslt;

    /* ��ʽΪ,cmpsSize(32BITs) + data(length=cmpsSize) */

    /* ǰ�ĸ��ֽ�ΪcmpsSize,��ȡcmpsSize */
    PS_MEM_CPY(pulSrcLen, pucSrc, sizeof(VOS_UINT32));
    pucSrc += sizeof(VOS_UINT32);

    /* �ӵ�����ֽڿ�ʼ���ѹ��������� */
    ulRslt  = (VOS_UINT32)_uncompress(pucDest, (unsigned long *)pulDestLen,
                                      pucSrc, *pulSrcLen);
    if (VOS_OK != ulRslt)
    {
        NAS_WARNING_LOG1(WUEPS_PID_MMC,
                         "NAS_MML_UnCompressData: ulRslt",
                         ulRslt);

        return VOS_FALSE;
    }

    /* ����4��cmpsSize�ռ� */
    *pulSrcLen += sizeof(VOS_UINT32);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MML_CompressData(
    VOS_UINT8                          *pucDest,
    VOS_UINT32                         *pulDestLen,
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulSrcLen
)
{
    VOS_UINT32                          ulRslt;

    /*��ʽΪ,cmpsSize(32BITs) + data(length=cmpsSize)*/
    if ((*pulDestLen) < sizeof(VOS_UINT32))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,
                         "NAS_MML_CompressData: ʣ��ռ䲻��");
        return VOS_FALSE;
    }

    /*Ԥ��ǰ�ĸ��ֽڣ��ӵ�����ֽڿ�ʼ���ѹ���������*/
    (*pulDestLen) -= sizeof(VOS_UINT32);

    ulRslt         = (VOS_UINT32)compress(pucDest + sizeof(VOS_UINT32), (unsigned long *)pulDestLen,
                                   pucSrc, ulSrcLen);

    if( VOS_OK != ulRslt )
    {
        NAS_WARNING_LOG1(WUEPS_PID_MMC,
                         "NAS_MML_CompressData: compress", ulRslt);

        return VOS_FALSE;
    }

    /*��Ԥ����ǰ�ĸ��ֽ��ϣ����cmpsSize*/
    PS_MEM_CPY( pucDest, pulDestLen, sizeof(VOS_UINT32));

    /*����4���ֽڳ���*/
    (*pulDestLen) += sizeof(VOS_UINT32);

    return VOS_TRUE;
}




VOS_UINT32 NAS_MML_IsSndOmPcRecurMsgValid(VOS_VOID)
{
    /* ��ǰUE��PC����δ����, ���跢�ͻط���Ϣ */
    if ( VOS_FALSE == NAS_MML_GetOmConnectFlg() )
    {
        return VOS_FALSE;
    }

#ifndef WIN32
    /* ��ǰPC����δʹ��NAS�ط���Ϣ�ķ���, ���跢�ͻط���Ϣ */
    if ( VOS_FALSE == NAS_MML_GetOmPcRecurEnableFlg() )
    {
        return VOS_FALSE;
    }
#endif

    return VOS_TRUE;
}



VOS_VOID NAS_MML_DelEqualPlmnsInForbList(
    VOS_UINT8                          *pEPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pEPlmnList,
    VOS_UINT8                           ucRefPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pRefPlmnList
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucPlmnNum;
    VOS_UINT32                          ulRlst;
    NAS_MML_PLMN_ID_STRU               *pstCurrPlmnId;                          /* PlMN��ʶ */
    NAS_MML_PLMN_ID_STRU               *pstEPlmn;

    pstCurrPlmnId = NAS_MML_GetCurrCampPlmnId();

    ucPlmnNum = *pEPlmnNum;

    for ( i = 0; i < ucPlmnNum;  )
    {
        ulRlst = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pEPlmnList + i, ucRefPlmnNum, pRefPlmnList);

        pstEPlmn = pEPlmnList + i;

        /* ���ڽ�ֹ�б��Ҳ��ǵ�ǰפ������ɾ�� */
        if ((VOS_FALSE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstCurrPlmnId, pstEPlmn))
         && ( VOS_TRUE == ulRlst ))
        {
            if (i < (ucPlmnNum - 1))
            {
                (VOS_VOID)PS_MEM_MOVE(&pEPlmnList [i], &pEPlmnList[ i + 1 ],
                            ((ucPlmnNum - i) - 1 ) * sizeof(NAS_MML_PLMN_ID_STRU));
            }

            ucPlmnNum--;

            if ( i > 0 )
            {
                i--;
            }
            else
            {
                continue;
            }

        }

        i++;
    }

    *pEPlmnNum = ucPlmnNum;

    return;
}



VOS_UINT32 NAS_MML_IsPsBearerExist(VOS_VOID)
{
    NAS_MML_PS_BEARER_CONTEXT_STRU     *pstPsBearerCtx;
    VOS_UINT32                          i;

    pstPsBearerCtx = NAS_MML_GetPsBearerCtx();

    for (i = 0; i < NAS_MML_MAX_PS_BEARER_NUM; i++)
    {
        if (NAS_MML_PS_BEARER_STATE_ACTIVE == pstPsBearerCtx[i].enPsBearerState)
        {
            return VOS_TRUE;
        }
    }
    return VOS_FALSE;
}


VOS_VOID NAS_MML_UpdateAllPsBearIsrFlg(
    NAS_MML_PS_BEARER_ISR_ENUM_UINT8    enPsBearerIsrFlg
)
{
    NAS_MML_PS_BEARER_CONTEXT_STRU     *pstPsBearerCtx;
    VOS_UINT8                           i;

    pstPsBearerCtx = NAS_MML_GetPsBearerCtx();

    for (i = 0; i < NAS_MML_MAX_PS_BEARER_NUM; i++)
    {
        pstPsBearerCtx[i].enPsBearerIsrFlg = enPsBearerIsrFlg;
    }

    return;
}


VOS_UINT32 NAS_MML_IsPsBearerExistBeforeIsrAct(VOS_UINT8 ucNsapi)
{
    NAS_MML_PS_BEARER_CONTEXT_STRU     *pstPsBearerCtx;

    pstPsBearerCtx = NAS_MML_GetPsBearerCtx();

    /* �Ϸ��Լ�飬���ucRabIdȡֵ����Э�鶨��[5,15]��Χ���򲻴���ֱ�ӷ��� */
    if ((ucNsapi < NAS_MML_MIN_NSAPI)
     || (ucNsapi > NAS_MML_MAX_NSAPI))
    {
        return VOS_FALSE;
    }

    if ((NAS_MML_PS_BEARER_STATE_ACTIVE == pstPsBearerCtx[ucNsapi - 5].enPsBearerState)
     && (NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT == pstPsBearerCtx[ucNsapi - 5].enPsBearerIsrFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}
VOS_UINT32 NAS_MML_IsPsBearerAfterIsrActExist(VOS_VOID)
{
    NAS_MML_PS_BEARER_CONTEXT_STRU     *pstPsBearerCtx;
    VOS_UINT8                           i;

    pstPsBearerCtx = NAS_MML_GetPsBearerCtx();

    for (i = 0; i < NAS_MML_MAX_PS_BEARER_NUM; i++)
    {
        if ((NAS_MML_PS_BEARER_STATE_ACTIVE == pstPsBearerCtx[i].enPsBearerState)
         && (NAS_MML_PS_BEARER_EXIST_AFTER_ISR_ACT == pstPsBearerCtx[i].enPsBearerIsrFlg))
        {
            return VOS_TRUE;
        }
    }
    return VOS_FALSE;

}

#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID NAS_MML_ConvertMmlCsfbStatusToLmmCsfbStatus(
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enMmlCsfbStatus,
    MM_LMM_CSFB_SERVICE_TYPE_ENUM_UINT32                   *penLmmCsfbStatus
)
{
    switch ( enMmlCsfbStatus )
    {
        case NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_CC_EXIST :
        case NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST :
            *penLmmCsfbStatus = MM_LMM_CSFB_SERVICE_MO_NORMAL;
            break;

        case NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST :
            *penLmmCsfbStatus = MM_LMM_CSFB_SERVICE_MO_EMERGENCY;
            break;

        case NAS_MML_CSFB_SERVICE_STATUS_MT_EXIST :
            *penLmmCsfbStatus = MM_LMM_CSFB_SERVICE_MT_NORMAL;
            break;

        default:
            *penLmmCsfbStatus = MM_LMM_CSFB_SERVICE_BUTT;
            break;
    }

    return;
}

VOS_UINT32 NAS_MML_GetCsPsMode1EnableLteTimerLen(VOS_VOID)
{
    /* �����ǰפ��plmn��֧��DAM���������б��У��򷵻�T3402��ʱ��ʱ����
       ���򷵻�9220 en_NV_Item_Enable_Lte_Timer_Len NV�������õ�ʱ�� */
    if (VOS_TRUE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
    {
        return NAS_MML_GetT3402Len();
    }

    return NAS_MML_GetCsPsMode13GPPEnableLteTimerLen();
}

#endif

VOS_UINT32 NAS_MML_IsLteCapabilityDisabled(
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapStatus,
    VOS_UINT32                                              ulDisableLteRoamFlg
)
{
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapStatus)
     || (VOS_TRUE == ulDisableLteRoamFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}


VOS_UINT32 NAS_MML_IsNeedAddDamPlmnInDisabledPlmnWithForbiddenPeriodList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstPlmnWithRat
)
{
    NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU                *pstDisabledPlmnIdWithRatList = VOS_NULL_PTR;
    VOS_UINT32                                              ulIndex;
    VOS_UINT32                                              ulIsPlmnSupportDam;

    pstDisabledPlmnIdWithRatList = NAS_MML_GetDisabledRatPlmnInfo();

    /* ���pstPlmnWithRat�Ѿ��ڽ�ֹ���뼼�������б��������账�� */
    if (VOS_TRUE == NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList(pstPlmnWithRat))
    {
        return VOS_FALSE;
    }

    ulIndex = pstDisabledPlmnIdWithRatList->ulDisabledRatPlmnNum;

    /* �б���������VOS_FALSE */
    if (NAS_MML_MAX_DISABLED_RAT_PLMN_NUM == ulIndex)
    {
        return VOS_FALSE;
    }

    ulIsPlmnSupportDam = NAS_MML_IsPlmnSupportDam(&pstPlmnWithRat->stPlmnId);

    /* DAM������Ч����DAM����disable lte����Ҫ��DAM��������ֹ����
       ���������б��У���̬�����ֹ���뼼�������б� */
    if ((VOS_TRUE == NAS_MML_GetAddDamPlmnInDisablePlmnWithRatListFlag())
     && (VOS_TRUE == ulIsPlmnSupportDam))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MML_GetDamDisabledPlmnWithForbiddenPeriodTimeSlice(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnWithRat
)
{
    VOS_UINT32                          ulExpiredTimeSlice;
    VOS_UINT32                          ulIsPlmnSupportDam;

    ulExpiredTimeSlice = 0;

    ulIsPlmnSupportDam = NAS_MML_IsPlmnSupportDam(&pstPlmnWithRat->stPlmnId);

    /* DAM������Ч����DAM����disable lte����Ҫ��DAM��������ֹ����
       ���������б��У�����T3402��ʱ��ʱ�����ض�Ӧ��timeslice */
    if ((VOS_TRUE == NAS_MML_GetAddDamPlmnInDisablePlmnWithRatListFlag())
     && (VOS_TRUE == ulIsPlmnSupportDam))
    {
        ulExpiredTimeSlice = VOS_GetSliceUnit() * (NAS_MML_GetT3402Len()/1000);
    }

    return ulExpiredTimeSlice;
}


VOS_UINT32 NAS_MML_IsNeedDeleteDisabledPlmnWithValidPeriodInPlmnList (
    NAS_MML_DISABLED_PLMN_WITH_FORBIDDEN_PERIOD_STRU       *pstDisabledPlmnIdWithRat
)
{
    VOS_UINT32                          ulCurrTimeSlice;
    VOS_UINT32                          ulDuration;

    ulCurrTimeSlice = VOS_GetSlice();

    /* �����ֹ���뼼��������nv���õĽ�ֹ����ΪȫF���򷵻�VOS_FALSE���趯̬ɾ�� */
    if (NAS_MML_MAX_TIME_SLICE == pstDisabledPlmnIdWithRat->ulPlmnDisabledForbiddenSlice)
    {
        return VOS_FALSE;
    }

    /* �ﵽ��ֹʱ�䣬��ӽ�ֹ���뼼�������б���ɾ��������,��Ϊ���ڷ�ת�������
       ulCurrTimeSliceС��ulPlmnDisabledBeginSliceҲ��Ϊ�ﵽ��ֹʱ�䣬�ӽ�ֹ���뼼�������б���ɾ��������*/
    if (ulCurrTimeSlice < pstDisabledPlmnIdWithRat->ulPlmnDisabledBeginSlice)
    {
        ulDuration = NAS_MML_MAX_TIME_SLICE - pstDisabledPlmnIdWithRat->ulPlmnDisabledBeginSlice + ulCurrTimeSlice + 1;
    }
    else
    {
        ulDuration = ulCurrTimeSlice - pstDisabledPlmnIdWithRat->ulPlmnDisabledBeginSlice;
    }

    if (ulDuration >= pstDisabledPlmnIdWithRat->ulPlmnDisabledForbiddenSlice)
    {
        return VOS_TRUE;
    }


    return VOS_FALSE;
}





VOS_UINT32 NAS_MML_GetFirstAddPlmnIndexInDestDisabledPlmnWithForbiddenPeriodList (
    VOS_UINT32                                              ulDestPlmnNum,
    NAS_MML_DISABLED_PLMN_WITH_FORBIDDEN_PERIOD_STRU       *pstDestPlmnIdList
)
{
    VOS_UINT32                          ulFirstAddPlmnIdIndex;
    VOS_UINT32                          j;
    VOS_UINT32                          ulIndex;

    ulIndex               = ulDestPlmnNum;
    ulFirstAddPlmnIdIndex = NAS_MML_MAX_DISABLED_RAT_PLMN_NUM;

    if (ulIndex > NAS_MML_MAX_DISABLED_RAT_PLMN_NUM)
    {
        ulIndex = NAS_MML_MAX_DISABLED_RAT_PLMN_NUM;
    }

    /* �ҵ�һ���ͷ�ʱ�䲻ΪNAS_MML_MAX_TIME_SLICE������ */
    for (j = 0; j < ulIndex; j++)
    {
        if (pstDestPlmnIdList[j].ulPlmnDisabledForbiddenSlice != NAS_MML_MAX_TIME_SLICE)
        {
            ulFirstAddPlmnIdIndex = j;
            break;
        }
    }

    /* ������ǳͷ�ʱ��ΪNAS_MML_MAX_TIME_SLICE�����磬�򷵻���Чֵ */
    if (NAS_MML_MAX_DISABLED_RAT_PLMN_NUM == ulFirstAddPlmnIdIndex)
    {
        return ulFirstAddPlmnIdIndex;
    }

    /* ����������ҳͷ�ʱ�䲻��ulFirstAddPlmnIdIndex������index */
    for (j = ulFirstAddPlmnIdIndex + 1; j < ulIndex; ++j)
    {
        if ((pstDestPlmnIdList[j].ulPlmnDisabledBeginSlice < pstDestPlmnIdList[ulFirstAddPlmnIdIndex].ulPlmnDisabledBeginSlice)
         && (pstDestPlmnIdList[j].ulPlmnDisabledForbiddenSlice != NAS_MML_MAX_TIME_SLICE))
        {
            ulFirstAddPlmnIdIndex = j;
        }
    }

    return ulFirstAddPlmnIdIndex;
}



VOS_VOID NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstPlmnWithRat,
    VOS_UINT32                                              ulPlmnDisabledInvalidSlice,
    MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32                  enDisableLteReason
)
{
    NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU                *pstDisabledPlmnIdWithRatList = VOS_NULL_PTR;
    VOS_UINT32                                              ulIndex;

    pstDisabledPlmnIdWithRatList = NAS_MML_GetDisabledRatPlmnInfo();

    /* ���pstPlmnWithRat�Ѿ��ڽ�ֹ���뼼�������б�����������ӣ�������begin slice���ͷ�ʱ���ͽ�ֹԭ�� */
    if (VOS_TRUE == NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList(pstPlmnWithRat))
    {
        ulIndex = NAS_MML_GetPlmnWithRatIndexInDestDisabledPlmnWithForbiddenPeriodList(pstPlmnWithRat,
                                                   pstDisabledPlmnIdWithRatList->ulDisabledRatPlmnNum,
                                                   pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId);

        if (ulIndex < NAS_MML_MAX_DISABLED_RAT_PLMN_NUM)
        {
            pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIndex].ulPlmnDisabledForbiddenSlice = ulPlmnDisabledInvalidSlice;
            pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIndex].ulPlmnDisabledBeginSlice     = VOS_GetSlice();
            pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIndex].enDisableLteReason           = enDisableLteReason;
        }
        return;
    }

    /* �б�����,ɾ����������ֹ���뼼�������б��е����� */
    if (NAS_MML_MAX_DISABLED_RAT_PLMN_NUM == pstDisabledPlmnIdWithRatList->ulDisabledRatPlmnNum)
    {
        ulIndex = NAS_MML_GetFirstAddPlmnIndexInDestDisabledPlmnWithForbiddenPeriodList(pstDisabledPlmnIdWithRatList->ulDisabledRatPlmnNum,
                                pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId);

        if (ulIndex < NAS_MML_MAX_DISABLED_RAT_PLMN_NUM)
        {
            pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIndex].stPlmnWithRat.stPlmnId.ulMcc = pstPlmnWithRat->stPlmnId.ulMcc;
            pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIndex].stPlmnWithRat.stPlmnId.ulMnc = pstPlmnWithRat->stPlmnId.ulMnc;
            pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIndex].stPlmnWithRat.enRat          = pstPlmnWithRat->enRat;
            pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIndex].ulPlmnDisabledForbiddenSlice = ulPlmnDisabledInvalidSlice;
            pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIndex].ulPlmnDisabledBeginSlice     = VOS_GetSlice();
            pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIndex].enDisableLteReason           = enDisableLteReason;

            NAS_MMC_LogForbiddenPlmnRelatedInfo();
        }
        return;
    }

    /* ��ǰPLMN���ڳͷ��б����棬�ҵ�ǰ�б�δ��������Ҫ��PLMN���뵽��ֹ���뼼���б����� */
    ulIndex                      = pstDisabledPlmnIdWithRatList->ulDisabledRatPlmnNum;

    pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIndex].stPlmnWithRat.stPlmnId.ulMcc = pstPlmnWithRat->stPlmnId.ulMcc;
    pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIndex].stPlmnWithRat.stPlmnId.ulMnc = pstPlmnWithRat->stPlmnId.ulMnc;
    pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIndex].stPlmnWithRat.enRat          = pstPlmnWithRat->enRat;
    pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIndex].ulPlmnDisabledForbiddenSlice = ulPlmnDisabledInvalidSlice;
    pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIndex].ulPlmnDisabledBeginSlice     = VOS_GetSlice();
    pstDisabledPlmnIdWithRatList->astDisabledRatPlmnId[ulIndex].enDisableLteReason           = enDisableLteReason;
    pstDisabledPlmnIdWithRatList->ulDisabledRatPlmnNum++;

    /* �������ڶ�ʱ���жϼ����ֹ���뼼�������ֹʱ���Ƿ񵽴
        �������Ҫɾ����Ϊ�����粻�ٽ�ֹ������֪ͨ������Чplmn��Ϣ */
    if (NAS_MMC_TIMER_STATUS_RUNING != NAS_MMC_GetTimerStatus(TI_NAS_MMC_PERIOD_DELETE_DISABLED_PLMN_WITH_RAT_TIMER))
    {
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_DELETE_DISABLED_PLMN_WITH_RAT_TIMER,
                            TI_NAS_MMC_PERIOD_DELETE_DISABLED_PLMN_WITH_RAT_TIMER_LEN);
    }


    NAS_MMC_LogForbiddenPlmnRelatedInfo();

    return;
}




VOS_UINT32 NAS_MML_IsImsiHplmnInDamImsiPlmnList(VOS_VOID)
{
    NAS_MML_DAM_IMSI_PLMN_LIST_STRU    *pstDamImsiPlmnList    = VOS_NULL_PTR;
    VOS_UINT8                          *pucImsi               = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stHplmnId;
    VOS_UINT32                          ulIsHplmnInDamImsiPlmnList;

    pstDamImsiPlmnList         = NAS_MML_GetDamImsiPlmnList();
    stHplmnId.ulMcc            = NAS_MML_INVALID_MCC;
    stHplmnId.ulMnc            = NAS_MML_INVALID_MNC;
    ulIsHplmnInDamImsiPlmnList = VOS_FALSE;

    /* ȡ���ֻ�����IMSI����Ϣ */
    pucImsi     = NAS_MML_GetSimImsi();

    /* �ӵ�ǰ��IMSI��ȡ��home plmn */
    stHplmnId                  = NAS_MML_GetImsiHomePlmn(pucImsi);

    /* ���DAM imsi plmn����Ϊ1����mcc��mncΪ0xFF,�������п�,����TRUE */
    if ((1 == pstDamImsiPlmnList->ucPlmnNum)
     && (NAS_MML_INVALID_MCC == pstDamImsiPlmnList->astPlmnId[0].ulMcc)
     && (NAS_MML_INVALID_MNC == pstDamImsiPlmnList->astPlmnId[0].ulMnc))
    {
        ulIsHplmnInDamImsiPlmnList = VOS_TRUE;
    }
    else
    {
        ulIsHplmnInDamImsiPlmnList = NAS_MML_IsSimPlmnIdInDestBcchPlmnList(&stHplmnId,
                                              pstDamImsiPlmnList->ucPlmnNum,
                                              pstDamImsiPlmnList->astPlmnId);
    }

    return ulIsHplmnInDamImsiPlmnList;
}
VOS_UINT32 NAS_MML_IsPlmnSupportDam(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_SUPPORT_DAM_PLMN_INFO_STRU *pstSupportDamPlmnList = VOS_NULL_PTR;
    VOS_UINT32                          ulIsPlmnInDamPlmnList;
    VOS_UINT32                          ulIsHplmnInDamImsiPlmnList;

    pstSupportDamPlmnList      = NAS_MML_GetSupportDamPlmnList();
    ulIsPlmnInDamPlmnList      = VOS_FALSE;
    ulIsHplmnInDamImsiPlmnList = VOS_FALSE;

    ulIsPlmnInDamPlmnList      = NAS_MML_IsSimPlmnIdInDestBcchPlmnList(pstPlmnId,
                                              pstSupportDamPlmnList->ucPlmnNum,
                                              pstSupportDamPlmnList->astPlmnId);

    ulIsHplmnInDamImsiPlmnList = NAS_MML_IsImsiHplmnInDamImsiPlmnList();

    /* IMSI HPLMN��DAM imsi plmn�б��в���פ��������֧��DAM���Ե������б��з���TRUE */
    if ((VOS_TRUE == ulIsPlmnInDamPlmnList)
     && (VOS_TRUE == ulIsHplmnInDamImsiPlmnList))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT8 NAS_MML_IsCsLaiChanged(VOS_VOID)
{
    NAS_MML_LAI_STRU                   *pstCampLai;
    NAS_MML_LAI_STRU                   *pstLastSuccLai;
    VOS_UINT32                          i;

    pstCampLai     = NAS_MML_GetCurrCampLai();
    pstLastSuccLai = NAS_MML_GetCsLastSuccLai();

    if ((pstCampLai->stPlmnId.ulMcc != pstLastSuccLai->stPlmnId.ulMcc)
     || (pstCampLai->stPlmnId.ulMnc != pstLastSuccLai->stPlmnId.ulMnc))
    {
        return VOS_TRUE;
    }

    for ( i = 0 ; i < NAS_MML_MAX_LAC_LEN ; i++ )
    {
        if (pstCampLai->aucLac[i] != pstLastSuccLai->aucLac[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;

}



VOS_UINT32 NAS_MML_IsExistBufferedEmgCall(VOS_VOID)
{
    VOS_UINT8                           ucIsExistEmgCall;

    ucIsExistEmgCall = NAS_MML_GetCsEmergencyServiceFlg();

    if ((VOS_TRUE == NAS_MML_GetCsServiceBufferStatusFlg())
     && (VOS_TRUE == ucIsExistEmgCall))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}




VOS_VOID NAS_MML_GetValidUserCfgEhplmnInfo(
    VOS_UINT8                          *pucImsi,
    VOS_UINT8                          *pucEhplmnListNum,
    NAS_MML_PLMN_ID_STRU               *pstEhPlmnList
)
{
    VOS_UINT32                                  i;
    VOS_UINT32                                  j;
    VOS_UINT32                                  ulUserCfgEhplmnNum;
    NAS_MML_PLMN_ID_STRU                        stHPlmn;
    NAS_MML_USER_CFG_EXT_EHPLMN_INFO_STRU      *pstUserCfgExtEHplmnInfo;

    pstUserCfgExtEHplmnInfo = NAS_MML_GetUserCfgExtEhplmnInfo();
    ulUserCfgEhplmnNum = pstUserCfgExtEHplmnInfo->ulUserCfgEhplmnNum;
    /* ��ֹ�ṹ������Խ�� */
    if ( ulUserCfgEhplmnNum > NAS_MML_MAX_USER_CFG_EXT_EHPLMN_NUM )
    {
        ulUserCfgEhplmnNum = NAS_MML_MAX_USER_CFG_EXT_EHPLMN_NUM;
    }

    /* Ĭ���û����õ�EHplmn�ĸ���Ϊ0�� */
    *pucEhplmnListNum = 0;

    /* �ӵ�ǰ��IMSI��ȡ��home plmn */
    stHPlmn = NAS_MML_GetImsiHomePlmn(pucImsi);


    /* �����ǰ��IMSI�е�Home Plmn��astImsiPlmnList�У���ȡ��ǰ��EHplmn */
    for (j = 0 ; j < ulUserCfgEhplmnNum; j++)
    {
        for ( i = 0 ; i < pstUserCfgExtEHplmnInfo->astUserCfgEhplmnInfo[j].ucImsiPlmnListNum; i++ )
        {
            /* �û����õ�IMSI plmn������BCCH��ʽ�� */
            if ( VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&pstUserCfgExtEHplmnInfo->astUserCfgEhplmnInfo[j].astImsiPlmnList[i],
                                                            &stHPlmn) )
            {
                *pucEhplmnListNum = pstUserCfgExtEHplmnInfo->astUserCfgEhplmnInfo[j].ucEhplmnListNum;

                /* ȡ���û����õ�EHplmn���� */
                PS_MEM_CPY(pstEhPlmnList, pstUserCfgExtEHplmnInfo->astUserCfgEhplmnInfo[j].astEhPlmnList,
                                            sizeof(pstUserCfgExtEHplmnInfo->astUserCfgEhplmnInfo[j].astEhPlmnList) );
                return;
            }
        }
    }


    return ;
}


VOS_UINT32  NAS_MML_GetRrcSimStatus(VOS_VOID)
{
    RRC_NAS_SIM_STATUS_ENUM_UINT32      ulCardStatus;

    /* ������ */
    if ( VOS_TRUE == NAS_MML_GetSimPresentStatus() )
    {
        /* SIM������ */
        if ( NAS_MML_SIM_TYPE_SIM  == NAS_MML_GetSimType())
        {
            ulCardStatus = RRC_NAS_SIM_PRESENT;
        }
        /* USIM������ */
        else
        {
            ulCardStatus = RRC_NAS_USIM_PRESENT;
        }
    }
    /* �������� */
    else
    {
        ulCardStatus = RRC_NAS_UICC_ABSENT;
    }

    return ulCardStatus;
}



VOS_UINT32 NAS_MML_IsBcchPlmnIdWithRatInDestPlmnWithRatList (
    NAS_MML_PLMN_WITH_RAT_STRU         *pstSrcPlmnId,
    VOS_UINT32                          ulDestPlmnNum,
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmnIdList
)
{
    VOS_UINT32                          i;

    for ( i = 0; i < ulDestPlmnNum; i++ )
    {
        if ((VOS_TRUE               == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstSrcPlmnId->stPlmnId), &(pstDestPlmnIdList[i].stPlmnId)))
         && (pstSrcPlmnId->enRat    == pstDestPlmnIdList[i].enRat))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_UINT32 NAS_MML_IsImsiInForbiddenList (VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_MML_PLMN_ID_STRU                stHplmnId;
    NAS_MML_PLMN_ID_STRU                stBlackPlmnId;
    NAS_MML_RAT_FORBIDDEN_LIST_STRU    *pstRatBlackList = VOS_NULL_PTR;
    VOS_UINT8                          *pucImsi         = VOS_NULL_PTR;

    i               = 0;
    pstRatBlackList = NAS_MML_GetRatForbiddenListCfg();

    PS_MEM_SET(&stHplmnId,     0x00, sizeof(stHplmnId));
    PS_MEM_SET(&stBlackPlmnId, 0x00, sizeof(stBlackPlmnId));

    if ( VOS_FALSE == NAS_MML_GetSimPresentStatus() )
    {
        return VOS_FALSE;
    }

    /* ���Ӳ��Կ����������Կ�ʱ���޸ģ�ֱ�ӷ��� */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_FALSE;
    }


    if ( NAS_MML_RAT_FORBIDDEN_LIST_SWITCH_INACTIVE == pstRatBlackList->enSwitchFlag )
    {
        return VOS_FALSE;
    }

    /* ȡ�ñ���ά����IMSI�ĵ�ַ */
    pucImsi    = NAS_MML_GetSimImsi();

    /* �ӵ�ǰ��IMSI��ȡ��home plmn */
    stHplmnId  = NAS_MML_GetImsiHomePlmn(pucImsi);

    /* �ж�IMSI�Ƿ��ڽ�ֹ��IMSI�б��� */
    if (NAS_MML_RAT_FORBIDDEN_LIST_SWITCH_BLACK == pstRatBlackList->enSwitchFlag)
    {
        for (i = 0; i < pstRatBlackList->ucImsiListNum; i++)
        {
            /* ����ں������У���ucIsPlmnIdInPlmnBlackList��ΪTRUE����Ҫ��ֹ��Ӧ��RAT */
            stBlackPlmnId.ulMcc = pstRatBlackList->astImsiList[i].ulMcc;
            stBlackPlmnId.ulMnc = pstRatBlackList->astImsiList[i].ulMnc;

            if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&stBlackPlmnId, &stHplmnId))
            {
                return VOS_TRUE;
            }
        }

        return VOS_FALSE;
    }
    else if (NAS_MML_RAT_FORBIDDEN_LIST_SWITCH_WHITE == pstRatBlackList->enSwitchFlag)
    {
        for (i = 0; i < pstRatBlackList->ucImsiListNum; i++)
        {
            /* ����ڰ������У�ֱ�ӷ���VOS_FALSE(���ں�����) */
            stBlackPlmnId.ulMcc = pstRatBlackList->astImsiList[i].ulMcc;
            stBlackPlmnId.ulMnc = pstRatBlackList->astImsiList[i].ulMnc;

            if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&stBlackPlmnId, &stHplmnId))
            {
                return VOS_FALSE;
            }
        }

        return VOS_TRUE;
    }
    else
    {
    }

    return VOS_FALSE;

}





VOS_UINT32 NAS_MML_IsRatInForbiddenList (
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType
)
{
    VOS_UINT32                          i;
    NAS_MML_RAT_FORBIDDEN_LIST_STRU    *pstRatBlackList = VOS_NULL_PTR;

    i                   = 0;
    pstRatBlackList     = NAS_MML_GetRatForbiddenListCfg();

    /* �������IMSI�������У�����VOS_FALSE */
    if (VOS_FALSE == NAS_MML_GetImsiInForbiddenListFlg())
    {
        return VOS_FALSE;
    }

    /* ����ڽ�ֹIMSI�б��У��ж�RAT�Ƿ��ڽ�ֹ��������ʽ�б��� */
    for (i = 0; i < pstRatBlackList->ucForbidRatNum; i++)
    {
        /* ��������RAT�ڽ�ֹ������ʽ�б����򷵻�VOS_TRUE */
        if (enRatType == pstRatBlackList->aenForbidRatList[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;

}
VOS_UINT32 NAS_MML_IsAllMsRatInForbiddenList (VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList       = VOS_NULL_PTR;
    VOS_UINT32                          i;

    i = 0;

     /* ��ȡ��ǰ���뼼�����ȼ���Ϣ */
    pstPrioRatList  = NAS_MML_GetMsPrioRatList();

    for (i = 0; i < pstPrioRatList->ucRatNum; i++)
    {
        if (VOS_FALSE == NAS_MML_IsRatInForbiddenList(pstPrioRatList->aucRatPrio[i]))
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}



#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 NAS_MML_IsPlatformSupportLte (VOS_VOID)
{
    NAS_MML_PLATFORM_RAT_CAP_STRU              *pstPlatformRatCap;
    VOS_UINT32                                  i;

    /* ��ȡƽ̨���뼼������ */
    pstPlatformRatCap = NAS_MML_GetPlatformRatCap();

    for ( i = 0; i < pstPlatformRatCap->ucRatNum; i++ )
    {
        if (NAS_MML_PLATFORM_RAT_TYPE_LTE == pstPlatformRatCap->aenRatPrio[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
#endif
VOS_UINT32 NAS_MML_IsPlatformSupportUtranFdd (VOS_VOID)
{
    NAS_MML_PLATFORM_RAT_CAP_STRU              *pstPlatformRatCap;
    VOS_UINT32                                  i;

    /* ��ȡƽ̨���뼼������ */
    pstPlatformRatCap = NAS_MML_GetPlatformRatCap();

    for ( i = 0; i < pstPlatformRatCap->ucRatNum; i++ )
    {
        if (NAS_MML_PLATFORM_RAT_TYPE_WCDMA == pstPlatformRatCap->aenRatPrio[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
VOS_UINT32 NAS_MML_IsPlatformSupportUtranTdd (VOS_VOID)
{
    NAS_MML_PLATFORM_RAT_CAP_STRU              *pstPlatformRatCap;
    VOS_UINT32                                  i;

    /* ��ȡƽ̨���뼼������ */
    pstPlatformRatCap = NAS_MML_GetPlatformRatCap();

    for ( i = 0; i < pstPlatformRatCap->ucRatNum; i++ )
    {
        if (NAS_MML_PLATFORM_RAT_TYPE_TD_SCDMA == pstPlatformRatCap->aenRatPrio[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
#endif
VOS_UINT32 NAS_MML_IsDsdsMultiModemMode(VOS_VOID)
{
    /* ���DSDS ����δ�������򷵻�FALSE */
    if (VOS_FALSE == NAS_MML_GetDsdsRfShareFlg() )
    {
        return VOS_FALSE;
    }

    /* �����ǰ���Ƕ࿨ģʽ���򷵻�FALSE */
    if (VOS_FALSE == NAS_MML_GetDsdsMultiModemModeFlg())
    {
        return VOS_FALSE;
    }

    /* DSDS���ܿ��������ҵ�ǰ�Ƕ࿨ģʽ���򷵻�TRUE */
    return VOS_TRUE;
}
VOS_UINT32 NAS_MML_IsPlatformSupportGsm (VOS_VOID)
{
    NAS_MML_PLATFORM_RAT_CAP_STRU              *pstPlatformRatCap;
    VOS_UINT32                                  i;

    /* ��ȡƽ̨���뼼������ */
    pstPlatformRatCap = NAS_MML_GetPlatformRatCap();

    for ( i = 0; i < pstPlatformRatCap->ucRatNum; i++ )
    {
        if (NAS_MML_PLATFORM_RAT_TYPE_GSM == pstPlatformRatCap->aenRatPrio[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
VOS_UINT32 NAS_MML_IsPlatformSupportUtran (VOS_VOID)
{
    if (VOS_TRUE == NAS_MML_IsPlatformSupportUtranFdd())
    {
        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
    if (VOS_TRUE == NAS_MML_IsPlatformSupportUtranTdd())
    {
        return VOS_TRUE;
    }
#endif

    return VOS_FALSE;
}

VOS_UINT32 NAS_MML_IsAcInfoChanged(
    NAS_MML_ACCESS_RESTRICTION_STRU    *pstOldAcRestrictInfo,
    NAS_MML_ACCESS_RESTRICTION_STRU    *pstNewAcRestrictInfo
)
{
    /* ��������ע�ᡢ����Ѱ������������ҵ�����ƽ���ҵ�����Ƿ��б仯 */
    if ((pstOldAcRestrictInfo->ucRestrictPagingRsp        != pstNewAcRestrictInfo->ucRestrictPagingRsp)
     || (pstOldAcRestrictInfo->ucRestrictRegister         != pstNewAcRestrictInfo->ucRestrictRegister)
     || (pstOldAcRestrictInfo->ucRestrictNormalService    != pstNewAcRestrictInfo->ucRestrictNormalService)
     || (pstOldAcRestrictInfo->ucRestrictEmergencyService != pstNewAcRestrictInfo->ucRestrictEmergencyService))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_VOID NAS_MML_Update_Revision_Level(
    VOS_UINT8                          *pucClassMark
)
{
    VOS_INT8                    cVersion;
    VOS_UINT8                   ucRevisionLevel;

    cVersion = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_CS);

    /* R99��ǰ�汾���ϱ� revision level Ϊ GSM PHASE 2*/
    if(PS_PTL_VER_PRE_R99 == cVersion)
    {
        ucRevisionLevel = MM_CLASSMARK_REVISION_LEVEL_GSM_PH2;
    }
    else
    {
        ucRevisionLevel = MM_CLASSMARK_REVISION_LEVEL_R99_OR_LATER;
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* Lʹ��ʱ����R99�Ժ�İ汾*/
    if(NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        ucRevisionLevel = MM_CLASSMARK_REVISION_LEVEL_R99_OR_LATER;
    }
#endif

    *pucClassMark &= 0x9f;
    *pucClassMark |= (VOS_UINT8)(ucRevisionLevel << 5);

    return;
}


VOS_VOID NAS_MML_GetSupportBandNum(
    VOS_UINT32                          ulBand,
    VOS_UINT8                          *pucBandNum
)
{
    /* ucIndicator����������λָʾ */
    VOS_UINT8                           ucIndicator;

    /* ucTotalLen��ʾ��������usBand����bitλ�� */
    VOS_UINT8                           ucTotalLen;

    /* ucBandNum������¼bitֵΪ1�ĸ���������Ϊ�����ķ���ֵ */
    *pucBandNum = 0;
    ucIndicator = 0;
    ucTotalLen  = sizeof(ulBand) * 8;

    /* ͨ��ѭ����λ����ulBand�е�bitֵΪ1���ܸ����������浽ucBandNum�� */
    while (ucIndicator < ucTotalLen)
    {
        if ((ulBand>>ucIndicator) & 0x01)
        {
            (*pucBandNum)++;
        }

        ucIndicator++;
    }

    return;
}


VOS_VOID NAS_MML_Fill_IE_ClassMark2(
    VOS_UINT8                          *pClassMark2
)
{
    GSM_BAND_SET_UN                     unSysCfgSetGsmBand;

    VOS_UINT8                           ucBandNum;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRat;
    NAS_MML_MS_BAND_INFO_STRU          *pstCurrBandInfo = VOS_NULL_PTR;
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability = VOS_NULL_PTR;
    NAS_MML_MS_BAND_INFO_STRU          *pstUserSetBand  = VOS_NULL_PTR;

    pstUserSetBand  = NAS_MML_GetMsSupportBand();
    pstMsCapability = NAS_MML_GetMsCapability();
    pstCurrBandInfo = NAS_MML_GetCurrBandInfo();
    enCurrNetRat    = NAS_MML_GetCurrNetRatType();

    if (pstMsCapability->aucClassmark2[0] != 0)
    {
        pClassMark2[0] = pstMsCapability->aucClassmark2[0];
        pClassMark2[1] = pstMsCapability->aucClassmark2[1];
        pClassMark2[2] = pstMsCapability->aucClassmark2[2];
        pClassMark2[3] = pstMsCapability->aucClassmark2[3];

        NAS_MML_Update_Revision_Level(&pClassMark2[1]);

        /* Ĭ������FCΪ0 */
        pClassMark2[2] &= 0xFE;

        /* ��֧��G�Ͳ���дGSM���� */
        if ( VOS_FALSE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_GSM))
        {
            // W only
            // ES IND => 0, A5/1 => 1, RF power capability => 111
            pClassMark2[1] &= 0xE0;
            pClassMark2[1] |= 0x0F;

            /* PS capability => 0, VBS => 0, VGCS => 0 */
            pClassMark2[2] &= 0xB9;
            /* SoLSA => 0, A5/3 => 0 */
            pClassMark2[3] &= 0xF5;

        }
        else
        {   /* W/G or G only */
            /* ��ȡ��ǰ��С������Ƶ�� */
            unSysCfgSetGsmBand.ulBand = pstCurrBandInfo->unGsmBand.ulBand;
            if ( (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrNetRat)
#if (FEATURE_ON == FEATURE_LTE)
              || (NAS_MML_NET_RAT_TYPE_LTE == enCurrNetRat)
#endif
             )
            {
                unSysCfgSetGsmBand.ulBand = pstUserSetBand->unGsmBand.ulBand;
            }
            /*���ݵ�ǰפ����Ƶ����дRF power capability*/
            if (( VOS_TRUE == unSysCfgSetGsmBand.stBitBand.BandGsm1800)
             || (VOS_TRUE== unSysCfgSetGsmBand.stBitBand.BandGsm1900))
            {
                /*power class 1*/
                pClassMark2[1] &= ~MM_CLASSMARK_RF_POWER_CAP_MASK;
                pClassMark2[1] |= MM_CLASSMARK_RF_POWER_CAP_CLASS1;
            }
            else /* ����Ƶ�� */
            {
                /*power class 4*/
                pClassMark2[1] &= ~MM_CLASSMARK_RF_POWER_CAP_MASK;
                pClassMark2[1] |= MM_CLASSMARK_RF_POWER_CAP_CLASS4;
            }

            /*��ǰ����פ����G��*/
            if (NAS_MML_NET_RAT_TYPE_GSM == enCurrNetRat)
            {

                /* �����900����Ҫ�ж��Ƿ�֧��E900��R900,���֧��FCΪ1��
                   ����ֻ֧��P900��פ��P900����FCΪ0 */
                if ( ( (VOS_TRUE == unSysCfgSetGsmBand.stBitBand.BandGsmE900)
                    || (VOS_TRUE == unSysCfgSetGsmBand.stBitBand.BandGsmR900))
                 || (VOS_TRUE == unSysCfgSetGsmBand.stBitBand.BandGsmP900))
                {
                    if (pstUserSetBand->unGsmBand.ulBand & 0x0030)
                    {
                        pClassMark2[2] |= 0x01;
                    }
                }
            }
            else
            {
                /* ��ȡ�û����õĿ���С����פ����Ƶ�� */
                unSysCfgSetGsmBand.ulBand = pstUserSetBand->unGsmBand.ulBand;

                NAS_MML_GetSupportBandNum(unSysCfgSetGsmBand.ulBand, &ucBandNum);

                /*���֧�ֶ�Ƶ�λ��߲�֧���κ�Ƶ�Σ�����RF power capability => 111*/
                if ( ((ucBandNum > 1)
                     ||(0 == ucBandNum))
                   ||((1 == ucBandNum) && ((VOS_TRUE == unSysCfgSetGsmBand.stBitBand.BandGsmE900)
                   || (VOS_TRUE == unSysCfgSetGsmBand.stBitBand.BandGsmR900))) )
                {
                    pClassMark2[1] |= MM_CLASSMARK_RF_POWER_CAP_MASK;
                }

            }

        }
    }
    return;
}



VOS_UINT32  NAS_MML_IsCsServDomainAvail(
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode
)
{
    /* Aģʽ��CS ONLYģʽʱ����ΪCS����ã�����ģʽ��ΪCS�򲻿��� */
    if ( (NAS_MML_MS_MODE_PS_CS == enMsMode)
      || (NAS_MML_MS_MODE_CS_ONLY == enMsMode) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_VOID NAS_MML_ConvertOamSendPid(
    VOS_UINT32                         *pulConvertedSendPid
)
{
    VOS_UINT32                          ulOrigSendPid;

    ulOrigSendPid = *pulConvertedSendPid;

    if ((I0_WUEPS_PID_USIM == ulOrigSendPid)
     || (I1_WUEPS_PID_USIM == ulOrigSendPid)
     || (I2_WUEPS_PID_USIM == ulOrigSendPid))
    {
        *pulConvertedSendPid = WUEPS_PID_USIM;
        return;
    }

    if ((I0_MAPS_STK_PID == ulOrigSendPid)
     || (I1_MAPS_STK_PID == ulOrigSendPid)
     || (I2_MAPS_STK_PID == ulOrigSendPid))
    {
        *pulConvertedSendPid = MAPS_STK_PID;
        return;
    }

    if ((I0_MAPS_PB_PID == ulOrigSendPid)
     || (I1_MAPS_PB_PID == ulOrigSendPid)
     || (I2_MAPS_PB_PID == ulOrigSendPid))
    {
        *pulConvertedSendPid = MAPS_PB_PID;
        return;
    }

    if ((I0_MAPS_PIH_PID == ulOrigSendPid)
     || (I1_MAPS_PIH_PID == ulOrigSendPid)
     || (I2_MAPS_PIH_PID == ulOrigSendPid))
    {
        *pulConvertedSendPid = MAPS_PIH_PID;
        return;
    }
}

#if (FEATURE_ON == FEATURE_PTM)

VOS_UINT32 NAS_MML_IsErrLogNeedRecord(VOS_UINT16 usLevel)
{
    /* Log���عرգ�����Ҫ�ϱ� */
    if (0 == NAS_MML_GetErrlogCtrlFlag())
    {
        return VOS_FALSE;
    }

    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_FALSE;
    }

    /* ģ��log����usLevel�����û����õ�log�ϱ������usLevel��Ч������Ҫ�ϱ� */
    if ((NAS_MML_GetErrlogAlmLevel() < usLevel)
     || (NAS_ERR_LOG_CTRL_LEVEL_NULL == usLevel))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MML_IsNeedNwSearchInfoRecord(
    VOS_VOID                           *pstMsg
)
{
    MSG_HEADER_STRU                    *pstMsgHeader  = VOS_NULL_PTR;
    NAS_MML_ERRLOG_NW_SEARCH_INFO_STRU *pstNwSrchInfo = VOS_NULL_PTR;
    NAS_MML_REG_STATUS_ENUM_UINT8       ucCsRegState;
    NAS_MML_REG_STATUS_ENUM_UINT8       ucPsRegState;
    VOS_UINT32                          ulIsAsPid;

    pstMsgHeader  = (MSG_HEADER_STRU *)pstMsg;
    ucCsRegState  = NAS_MML_GetCsRegStatus();
    ucPsRegState  = NAS_MML_GetPsRegStatus();
    pstNwSrchInfo = NAS_MML_GetErrLogNwSearchInfoAddr();
    ulIsAsPid     = NAS_MML_IsAsPid(pstMsgHeader->ulSenderPid);

    if (WUEPS_PID_MMC != pstMsgHeader->ulReceiverPid)
    {
        return VOS_FALSE;
    }

    /* ��������ظ��Լ�ֹͣ��������ظ���Ҫ��¼CHR */
    if (((ID_LMM_MMC_PLMN_SRCH_CNF      == pstMsgHeader->ulMsgName)
      || (ID_LMM_MMC_STOP_PLMN_SRCH_CNF == pstMsgHeader->ulMsgName)
      || (RRMM_PLMN_SEARCH_CNF          == pstMsgHeader->ulMsgName)
      || (RRMM_PLMN_SEARCH_STOP_CNF     == pstMsgHeader->ulMsgName))
     && (VOS_TRUE == ulIsAsPid))
    {
        /* �����ǰ��ע��״̬�������������򲻼�¼CHR */
        if (((NAS_MML_REG_REGISTERED_HOME_NETWORK == ucCsRegState)
          || (NAS_MML_REG_REGISTERED_ROAM         == ucCsRegState))
         && ((NAS_MML_REG_REGISTERED_HOME_NETWORK == ucPsRegState)
          || (NAS_MML_REG_REGISTERED_ROAM         == ucPsRegState)))
        {
            return VOS_FALSE;
        }

        /* L�µĿ���ָ���ѣ�����Ҫ��¼CHR */
        if ((PS_PID_MM                   == pstMsgHeader->ulSenderPid)
         && (MMC_LMM_PLMN_SRCH_FAST_SPEC == pstNwSrchInfo->ulSearchType))
        {
            return VOS_FALSE;
        }

        /* GUT�µĿ���ָ���ѣ�����Ҫ��¼CHR */
        if ((VOS_TRUE                    == NAS_MML_IsGutAsPid(pstMsgHeader->ulSenderPid))
         && (RRC_PLMN_SEARCH_SPEC_FAST   == pstNwSrchInfo->ulSearchType))
        {
            return VOS_FALSE;
        }

        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_VOID NAS_MML_RecordNwSearchInfo(
    VOS_VOID                           *pstMsg
)
{
    MSG_HEADER_STRU                            *pstMsgHeader      = VOS_NULL_PTR;
    NAS_MML_ERRLOG_NW_SEARCH_INFO_STRU         *pstNwSrchInfo     = VOS_NULL_PTR;
    LMM_MMC_PLMN_SRCH_CNF_STRU                 *pstLmmSrchCnfMsg  = VOS_NULL_PTR;
    RRMM_PLMN_SEARCH_CNF_STRU                  *pstRrmmSrchCnfMsg = VOS_NULL_PTR;
    NAS_ERR_LOG_OOS_NW_SRCH_PROC_INFO_STRU      stProcInfoEvent;
    VOS_UINT32                                  ulIsLogNeedRecord;
    VOS_UINT32                                  ulLength;
    VOS_UINT32                                  ulResult;
    VOS_UINT16                                  usLevel;
    VOS_UINT8                                   ucCfgActiveFlag;
    VOS_UINT32                                  ulCfgRecordNum;

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel           = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_OOS_NW_SRCH_PROC_INFO);
    ulIsLogNeedRecord = NAS_MML_IsErrLogNeedRecord(usLevel);
    pstNwSrchInfo     = NAS_MML_GetErrLogNwSearchInfoAddr();
    ulCfgRecordNum    = NAS_MML_GetErrLogNwSrchCfgRecordNum();
    ucCfgActiveFlag   = NAS_MML_GetErrLogNwSrchCfgActiveFlag();

    pstMsgHeader      = (MSG_HEADER_STRU *)pstMsg;

    /* 1. ģ���쳣����Ҫ��¼
       2. NV���ò���Ҫ��¼ */
    if ((VOS_FALSE == ulIsLogNeedRecord)
     || (VOS_FALSE == ucCfgActiveFlag))
    {
        return;
    }

    /* �������NV��¼�������������ټ�¼ */
    if (pstNwSrchInfo->ulSearchCount > ulCfgRecordNum)
    {
        return;
    }

    /* �������̼�¼������1 */
    NAS_MML_AddErrLogNwSearchCount();

    ulLength = sizeof(NAS_ERR_LOG_OOS_NW_SRCH_PROC_INFO_STRU);

    /* ��䱾�ؼ�¼��Ϣ */
    PS_MEM_SET(&stProcInfoEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stProcInfoEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_MMC),
                                      NAS_ERR_LOG_ALM_OOS_NW_SRCH_PROC_INFO,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stProcInfoEvent.stPlmnId.ulMcc      = pstNwSrchInfo->stPlmnId.ulMcc;
    stProcInfoEvent.stPlmnId.ulMnc      = pstNwSrchInfo->stPlmnId.ulMnc;
    stProcInfoEvent.enSrchRat           = pstNwSrchInfo->enSrchRat;
    stProcInfoEvent.ucSearchType        = (VOS_UINT8)pstNwSrchInfo->ulSearchType;
    stProcInfoEvent.ulPlmnSrchReqSlice  = pstNwSrchInfo->ulPlmnSrchReqSlice;

    if (ID_LMM_MMC_PLMN_SRCH_CNF == pstMsgHeader->ulMsgName)
    {
        pstLmmSrchCnfMsg  = (LMM_MMC_PLMN_SRCH_CNF_STRU *)pstMsg;
        stProcInfoEvent.ucResult        = (VOS_UINT8)pstLmmSrchCnfMsg->enRlst;
        stProcInfoEvent.ucCoverageType  = (VOS_UINT8)pstLmmSrchCnfMsg->enCoverageType;
    }
    else if (RRMM_PLMN_SEARCH_CNF == pstMsgHeader->ulMsgName)
    {
        pstRrmmSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;
        stProcInfoEvent.ucResult        = (VOS_UINT8)pstRrmmSrchCnfMsg->ulSearchRlt;
        stProcInfoEvent.ucCoverageType  = (VOS_UINT8)pstRrmmSrchCnfMsg->enCoverageType;
    }
    else
    {
        stProcInfoEvent.ucResult        = 0xFF;
        stProcInfoEvent.ucCoverageType  = 0xFF;
    }

    /* ���֮ǰ��¼������������Ϣ */
    pstNwSrchInfo->stPlmnId.ulMcc       = 0;
    pstNwSrchInfo->stPlmnId.ulMnc       = 0;
    pstNwSrchInfo->enSrchRat            = NAS_ERR_LOG_RATMODE_BUTT;
    pstNwSrchInfo->ulSearchType         = 0xFF;
    pstNwSrchInfo->ulPlmnSrchReqSlice   = 0;

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = NAS_MML_PutErrLogRingBuf((VOS_CHAR *)&stProcInfoEvent, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MML_RecordNwSearchInfo(): Push buffer error.");
    }

    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_OOS_NW_SRCH_PROC_INFO,
                           WUEPS_PID_MMC,
                           (VOS_UINT8 *)&stProcInfoEvent,
                           sizeof(stProcInfoEvent));

    return;
}

#endif


VOS_UINT32 NAS_MML_IsGutAsPid(VOS_UINT32 ulPid)
{
    VOS_UINT32                          ulRslt;

    switch (ulPid)
    {
        case UEPS_PID_GAS:
        case WUEPS_PID_WRR:
        case TPS_PID_RRC:
            ulRslt = VOS_TRUE;
            break;

        default:
            ulRslt = VOS_FALSE;
            break;
    }

    return ulRslt;
}


VOS_UINT32 NAS_MML_IsAsPid(VOS_UINT32 ulPid)
{
    VOS_UINT32                          ulRslt;

    switch (ulPid)
    {
        case PS_PID_MM:
        case UEPS_PID_GAS:
        case WUEPS_PID_WRR:
        case TPS_PID_RRC:
            ulRslt = VOS_TRUE;
            break;

        default:
            ulRslt = VOS_FALSE;
            break;
    }

    return ulRslt;
}


VOS_VOID NAS_MML_SaveNwSearchReqInfo(
    VOS_VOID                           *pstMsg
)
{
    MSG_HEADER_STRU                    *pstMsgHeader      = VOS_NULL_PTR;
    MMC_LMM_PLMN_SRCH_REQ_STRU         *pstLmmPlmnSrchReq  = VOS_NULL_PTR;
    RRMM_PLMN_SEARCH_REQ_STRU          *pstRrmmPlmnSrchReq = VOS_NULL_PTR;
    NAS_MML_ERRLOG_NW_SEARCH_INFO_STRU *pstNwSrchInfo      = VOS_NULL_PTR;
    NAS_MML_SIM_FORMAT_PLMN_ID          stSimPlmn;
    VOS_UINT32                          ulReceiverPid;

    pstMsgHeader  = (MSG_HEADER_STRU *)pstMsg;
    pstNwSrchInfo = NAS_MML_GetErrLogNwSearchInfoAddr();

    ulReceiverPid = pstMsgHeader->ulReceiverPid;

    /* LTE���������� */
    if ((ID_MMC_LMM_PLMN_SRCH_REQ == pstMsgHeader->ulMsgName)
     && (PS_PID_MM                == ulReceiverPid))
    {
        PS_MEM_SET(&stSimPlmn, 0x0, sizeof(NAS_MML_SIM_FORMAT_PLMN_ID));

        pstLmmPlmnSrchReq = (MMC_LMM_PLMN_SRCH_REQ_STRU *)pstMsg;

        pstNwSrchInfo->enSrchRat          = NAS_ERR_LOG_RATMODE_LTE;
        pstNwSrchInfo->ulSearchType       = pstLmmPlmnSrchReq->enSrchType;
        pstNwSrchInfo->ulPlmnSrchReqSlice = VOS_GetSlice();

        /* ��ת��ΪSIM��ʽ */
        PS_MEM_CPY(stSimPlmn.aucSimPlmn,
                   pstLmmPlmnSrchReq->stSpecPlmnId.aucPlmnId,
                   MMC_LMM_PLMN_ID_LEN);

        NAS_MML_ConvertSimPlmnToNasPLMN(&stSimPlmn,
                                        (NAS_MML_PLMN_ID_STRU *)&pstNwSrchInfo->stPlmnId);

        return;
    }

    /* GUT���������� */
    if (RRMM_PLMN_SEARCH_REQ == pstMsgHeader->ulMsgName)
    {
        pstRrmmPlmnSrchReq = (RRMM_PLMN_SEARCH_REQ_STRU *)pstMsg;

        pstNwSrchInfo->ulSearchType       = pstRrmmPlmnSrchReq->ulSearchType;
        pstNwSrchInfo->stPlmnId.ulMcc     = pstRrmmPlmnSrchReq->aPlmnIdList[0].ulMcc;
        pstNwSrchInfo->stPlmnId.ulMnc     = pstRrmmPlmnSrchReq->aPlmnIdList[0].ulMnc;
        pstNwSrchInfo->ulPlmnSrchReqSlice = VOS_GetSlice();

        if (UEPS_PID_GAS == ulReceiverPid)
        {
            pstNwSrchInfo->enSrchRat = NAS_ERR_LOG_RATMODE_GSM;
        }
        else if (WUEPS_PID_WRR == ulReceiverPid)
        {
            pstNwSrchInfo->enSrchRat = NAS_ERR_LOG_RATMODE_WCDMA;
        }
        else
        {
            pstNwSrchInfo->enSrchRat = NAS_ERR_LOG_RATMODE_TDS;
        }

        return;

    }
}
VOS_VOID  NAS_MML_ConvertSimPlmnToNasPLMN(
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





VOS_UINT32 NAS_MML_DecodeEmergencyNumList(
    VOS_UINT16                         *pusIndex,
    VOS_UINT8                          *pucRcvMsg,
    VOS_UINT16                          usMsgSize
)
{
    NAS_MML_EMERGENCY_NUM_LIST_STRU    *pstEmergencyNumList = VOS_NULL_PTR;
    VOS_UINT16                          usIndex;
    VOS_UINT8                           ucTotalIeLength;
    VOS_UINT8                           ucParseEmcTotalLength;
    VOS_UINT8                           ucTempLength;
    VOS_UINT8                           ucLength;
    VOS_UINT8                           i;

    usIndex                             = *pusIndex;
    ucTotalIeLength                     = 0;
    ucTempLength                        = 0;
    ucLength                            = 0;
    ucParseEmcTotalLength               = 0;

    pstEmergencyNumList                 = NAS_MML_GetEmergencyNumList();

    pstEmergencyNumList->ucEmergencyNumber = 0;

    /* ����������IE�ĳ��ȣ�����IEI */
    ucTotalIeLength       = pucRcvMsg[usIndex + 1] + 2;

    /* Length of Emergency Number List IE contents */
    ucParseEmcTotalLength = pucRcvMsg[usIndex + 1];

    /* ���ս�������д���ܳ���ֵ�������ᳬ��������Ϣ�ĳ��ȣ�����Ϊ�쳣 */
    if ( ( *pusIndex + ucTotalIeLength) > usMsgSize )
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MML_DecodeEmergencyNumList: IE emergency number length error!!!");

        *pusIndex = usMsgSize;

        /* �����쳣��ֱ�ӷ���END */
        return VOS_FALSE;
    }

    if ( ucParseEmcTotalLength < NAS_MML_MIN_EMERGENCY_NUM_LEN )
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MML_DecodeEmergencyNumList: IE emergency number length < NAS_MML_MIN_EMERGENCY_NUM_LEN error !!!");

        /* ֱ��ָ��������Ľ�������:����һ��IEI���������� */
        *pusIndex = *pusIndex + ucTotalIeLength;

        return VOS_FALSE;
    }

    if ( ucParseEmcTotalLength > NAS_MML_MAX_EMERGENCY_NUM_LEN )
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MML_DecodeEmergencyNumList: IE emergency number length > NAS_MML_MAX_EMERGENCY_NUM_LEN error !!!");

        ucParseEmcTotalLength =  NAS_MML_MAX_EMERGENCY_NUM_LEN;
    }

    /* ָ���һ���������б� */
    usIndex = usIndex + 2;

    while (ucParseEmcTotalLength > ucTempLength)
    {

       ucLength     = pucRcvMsg[usIndex];                                      /* Length of Nst Emergency Number information */

       /*************************************************************************
       *TS 24.007, section 11.4.2
       * -- It is not a syntactical error that a type 4 standard IE specifies in
       * its length indicator a greater length than possible according to the
       * value part specification: extra bits shall be ignored.
       *
       *TS 24.007, section 11.2.1.1.4
       *A type 4 standard information element has format LV or TLV. Its LI precedes
       *the value part, which consists of zero, one, or more octets; if present,
       *its IEI has one octet length and precedes the LI.
       *
       *Hence, this is a type 4 information element.
       **************************************************************************/
        if ( (ucTempLength + 1 + NAS_MML_MIN(ucLength, NAS_MML_MAX_EMERGENCY_NUM_INFO_LEN)) > ucParseEmcTotalLength )
        {
            /* ֱ��ָ��������Ľ�������:����һ��IEI���������� */
            *pusIndex = *pusIndex + ucTotalIeLength;

            return VOS_FALSE;
        }

        /* ������Ч��EMERGENCY Number List����,����Ϊ�����������б���Ч */
        if (ucLength < NAS_MML_MIN_EMERGENCY_NUM_INFO_LEN)
        {
            pstEmergencyNumList->ucEmergencyNumber = 0;
            *pusIndex = *pusIndex + ucTotalIeLength;
            return VOS_FALSE;
        }

        ucTempLength = ucTempLength + ucLength + 1;                             /* �ۼ�����Emergency Number List���ܳ��ȣ����� Length IE */

        if (ucLength > NAS_MML_MAX_EMERGENCY_NUM_INFO_LEN)
        {
            /* usIndexָ����һ������������ */
            usIndex += ucTempLength;

            /* �����Ե���ǰ�������� */
            continue;
        }

        pstEmergencyNumList->ucEmergencyNumber++;
        pstEmergencyNumList->aucEmergencyList[pstEmergencyNumList->ucEmergencyNumber - 1].ucEmcNumLen
            = ucLength - 1;
        pstEmergencyNumList->aucEmergencyList[pstEmergencyNumList->ucEmergencyNumber - 1].ucCategory
            = pucRcvMsg[usIndex + 1] & 0x1F;                                    /* Emergency Service Category Value         */

        /* ƫ�Ƶ� Number digit 1 �ֽ� */
        usIndex = usIndex + 2;

        for (i = 0; i < (ucLength - 1); i++)
        {
            pstEmergencyNumList->aucEmergencyList[pstEmergencyNumList->ucEmergencyNumber - 1].aucEmcNum[i]
                = pucRcvMsg[usIndex];                                        /* Number digit N                           */
            usIndex++;
        }

        /* usIndexָ����һ������������ */

        if (pstEmergencyNumList->ucEmergencyNumber >= NAS_MML_EMERGENCY_NUM_LIST_MAX_RECORDS)
        {
            /* �ﵽ�Դ����������������Ϊ������� */
            *pusIndex = *pusIndex + ucTotalIeLength;

            return VOS_TRUE;
        }

    }

    /* ������ϣ���ָ�����һ���ַ� */
    *pusIndex = *pusIndex + ucTotalIeLength;

    return VOS_TRUE;
}
VOS_UINT32 NAS_MML_IsNvimOplmnAvail(VOS_VOID)
{
    VOS_UINT32                          ulStep;
    NAS_MML_PLMN_ID_STRU                stHPlmn;
    RRC_NAS_SIM_STATUS_ENUM_UINT32      ulCardStatus;
    VOS_UINT8                          *pucImsi             = VOS_NULL_PTR;
    NAS_MML_USER_CFG_OPLMN_INFO_STRU   *pstUserCfgOPlmnInfo = VOS_NULL_PTR;

    PS_MEM_SET(&stHPlmn, 0x00, sizeof(NAS_MML_PLMN_ID_STRU));

    pstUserCfgOPlmnInfo = NAS_MML_GetUserCfgOPlmnInfo();

    /* ���Կ���δ�򿪣���OPLMN����Ϊ0������OPLMN������Ч */
    if ((VOS_FALSE == pstUserCfgOPlmnInfo->ucActiveFlg)
     || (0 == pstUserCfgOPlmnInfo->usOplmnListNum))
    {
        return VOS_FALSE;
    }

    /* �����Ͳ�ΪUSIM���򿨲�����ʱ������OPLMN����Ч */
    ulCardStatus = NAS_MML_GetRrcSimStatus();

    if (RRC_NAS_USIM_PRESENT != ulCardStatus)
    {
        return VOS_FALSE;
    }

    /* IMSI���δʹ�ܣ�����Ҫ��IMSI��� */
    if (VOS_FALSE == pstUserCfgOPlmnInfo->ucImsiCheckFlg)
    {
        return VOS_TRUE;
    }

    /* ȡ�ñ���ά����IMSI�ĵ�ַ */
    pucImsi  = NAS_MML_GetSimImsi();

    /* �ӵ�ǰ��IMSI��ȡ��home plmn */
    stHPlmn  = NAS_MML_GetImsiHomePlmn(pucImsi);

    /* �����ǰIMSI�е�Home Plmn��astImsiPlmnList�У�����OPLMN������Ч */
    for ( ulStep = 0 ; ulStep < pstUserCfgOPlmnInfo->ucImsiPlmnListNum; ulStep++ )
    {
        if ( VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&pstUserCfgOPlmnInfo->astImsiPlmnList[ulStep],
                                                            &stHPlmn) )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_VOID NAS_MML_Fill_IE_TddClassMark3(
    VOS_UINT8                          *pucTddClassMark3
)
{
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability = VOS_NULL_PTR;
    VOS_UINT8                           ucLen;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulRst;
    RRMM_CLASSMARK_CHANGE_IND_STRU     *pstRrmmClassMarkChgInd = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurNetRatType;
    RRC_PLMN_ID_STRU                    stRrmmPlmnId;

    enCurNetRatType        = NAS_MML_GetCurrNetRatType();

    pstRrmmClassMarkChgInd = (RRMM_CLASSMARK_CHANGE_IND_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC, sizeof(RRMM_CLASSMARK_CHANGE_IND_STRU));

    /* ��ǰNV�򿪣������ڴ�ɹ��ҵ�ǰģ����GSM */
    if ( (VOS_TRUE == NAS_MML_GetIsDelFddBandSwitchOnFlg())
      && (VOS_NULL_PTR != pstRrmmClassMarkChgInd)
      && (NAS_MML_NET_RAT_TYPE_GSM != enCurNetRatType) )
    {
        PS_MEM_SET(pstRrmmClassMarkChgInd, 0x00, sizeof(RRMM_CLASSMARK_CHANGE_IND_STRU));

        stRrmmPlmnId.ulMcc = NAS_MML_GetCurrCampPlmnId()->ulMcc;
        stRrmmPlmnId.ulMnc = NAS_MML_GetCurrCampPlmnId()->ulMnc;

        /* ����GAS�ӿڻ�ȡTDD classmark3 */
        ulRst = GASGCOM_GetMsCapability(&stRrmmPlmnId, NAS_GAS_MS_CAP_TYPE_CLASSMARK,
                                                sizeof(RRMM_CLASSMARK_CHANGE_IND_STRU),
                                                (VOS_UINT8*)pstRrmmClassMarkChgInd);

        if ( VOS_TRUE == ulRst )
        {
            pucTddClassMark3[0] = pstRrmmClassMarkChgInd->ucClassmark3TddLen;
            PS_MEM_CPY(&pucTddClassMark3[1], pstRrmmClassMarkChgInd->aucClassmark3Tdd, pucTddClassMark3[0]);

            PS_MEM_FREE(WUEPS_PID_MMC, pstRrmmClassMarkChgInd);
            return;
        }
    }
#endif

    pstMsCapability = NAS_MML_GetMsCapability();

    /* ��0λ��дΪ���� */
    ucLen = pstMsCapability->aucTddClassmark3[0];

    PS_MEM_CPY(&pucTddClassMark3[0], &(pstMsCapability->aucTddClassmark3[0]), ucLen+1);

#if (FEATURE_ON == FEATURE_LTE)
    if ( VOS_NULL_PTR != pstRrmmClassMarkChgInd )
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstRrmmClassMarkChgInd);
    }
#endif

    return;
}
VOS_VOID NAS_MML_Fill_IE_FddClassMark3(
    VOS_UINT8                          *pucFddClassMark3
)
{
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability = VOS_NULL_PTR;
    VOS_UINT8                           ucLen;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulRst;
    RRMM_CLASSMARK_CHANGE_IND_STRU     *pstRrmmClassMarkChgInd = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurNetRatType;
    RRC_PLMN_ID_STRU                    stRrmmPlmnId;

    enCurNetRatType        = NAS_MML_GetCurrNetRatType();

    pstRrmmClassMarkChgInd = (RRMM_CLASSMARK_CHANGE_IND_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC, sizeof(RRMM_CLASSMARK_CHANGE_IND_STRU));

    /* ��ǰNV�򿪣������ڴ�ɹ��ҵ�ǰģ����GSM */
    if ( (VOS_TRUE == NAS_MML_GetIsDelFddBandSwitchOnFlg())
      && (VOS_NULL_PTR != pstRrmmClassMarkChgInd)
      && (NAS_MML_NET_RAT_TYPE_GSM != enCurNetRatType) )
    {
        PS_MEM_SET(pstRrmmClassMarkChgInd, 0x00, sizeof(RRMM_CLASSMARK_CHANGE_IND_STRU));

        stRrmmPlmnId.ulMcc = NAS_MML_GetCurrCampPlmnId()->ulMcc;
        stRrmmPlmnId.ulMnc = NAS_MML_GetCurrCampPlmnId()->ulMnc;

        /* ����GAS�ӿڻ�ȡFDD classmark3 */
        ulRst = GASGCOM_GetMsCapability(&stRrmmPlmnId, NAS_GAS_MS_CAP_TYPE_CLASSMARK,
                                                sizeof(RRMM_CLASSMARK_CHANGE_IND_STRU),
                                                (VOS_UINT8*)pstRrmmClassMarkChgInd);

        if ( VOS_TRUE == ulRst )
        {
            pucFddClassMark3[0] = pstRrmmClassMarkChgInd->ucClassmark3FddLen;
            PS_MEM_CPY(&pucFddClassMark3[1], pstRrmmClassMarkChgInd->aucClassmark3Fdd, pucFddClassMark3[0]);

            PS_MEM_FREE(WUEPS_PID_MMC, pstRrmmClassMarkChgInd);
            return;
        }
    }
#endif

    pstMsCapability = NAS_MML_GetMsCapability();

    /* ��0λ��дΪ���� */
    ucLen = pstMsCapability->aucFddClassmark3[0];

    PS_MEM_CPY(&pucFddClassMark3[0], &(pstMsCapability->aucFddClassmark3[0]), ucLen+1);

#if(FEATURE_ON == FEATURE_LTE)
    if ( VOS_NULL_PTR != pstRrmmClassMarkChgInd )
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstRrmmClassMarkChgInd);
    }
#endif

    return;
}





VOS_VOID NAS_MML_DelEqualPlmnsInDisableRatList(
    VOS_UINT8                                              *pucEPlmnNum,
    NAS_MML_PLMN_ID_STRU                                   *pstEPlmnList,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enSpecRat,
    VOS_UINT32                                              ulDisabledRatPlmnNum,
    NAS_MML_DISABLED_PLMN_WITH_FORBIDDEN_PERIOD_STRU       *pstDisabledRatPlmnIdList
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucPlmnNum;
    VOS_UINT32                          ulRlst;
    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnWithRat;

    ucPlmnNum = *pucEPlmnNum;

    for ( i = 0; i < ucPlmnNum;  )
    {
        /* ��������뼼����PLMN ID */
        stPlmnWithRat.enRat         = enSpecRat;
        stPlmnWithRat.stPlmnId      = pstEPlmnList[i];

        ulRlst = NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnRatList(&stPlmnWithRat,
                                                                  ulDisabledRatPlmnNum,
                                                                  pstDisabledRatPlmnIdList);

        /* ���ڽ�ֹ�б��Ҳ��ǵ�ǰפ������ɾ�� */
        if ( VOS_TRUE == ulRlst )
        {
            if (i < (ucPlmnNum - 1))
            {
                (VOS_VOID)PS_MEM_MOVE(&pstEPlmnList [i], &pstEPlmnList[ i + 1 ],
                            ((ucPlmnNum - i) - 1 ) * sizeof(NAS_MML_PLMN_ID_STRU));
            }

            ucPlmnNum--;

            if ( i > 0 )
            {
                i--;
            }
            else
            {
                continue;
            }

        }

        i++;
    }

    *pucEPlmnNum = ucPlmnNum;

    return;
}


VOS_VOID NAS_MML_DelEqualPlmnNotInAllowLteRoamMccList(
    VOS_UINT8                          *pucEPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstEPlmnList,
    VOS_UINT32                          ulAllowLteRoamMccNum,
    VOS_UINT32                         *pulAllowLteRoamMccList
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucPlmnNum;
    VOS_UINT8                           ucLteRoamFlg;


    ucPlmnNum       = *pucEPlmnNum;
    ucLteRoamFlg    = NAS_MML_GetLteRoamAllowedFlg();

    /* ����LTE��������ʱ����ɾ�� */
    if (VOS_TRUE == ucLteRoamFlg)
    {
        return;
    }

    for ( i = 0; i < ucPlmnNum;  )
    {
            /* EPLMN IDΪ������������,����������,��Ҫɾ�� */
        if (VOS_FALSE == NAS_MML_IsMccInDestMccList(pstEPlmnList[i].ulMcc, ulAllowLteRoamMccNum, pulAllowLteRoamMccList))
        {
            if (i < (ucPlmnNum - 1))
            {
                (VOS_VOID)PS_MEM_MOVE(&pstEPlmnList [i], &pstEPlmnList[ i + 1 ],
                            ((ucPlmnNum - i) - 1 ) * sizeof(NAS_MML_PLMN_ID_STRU));
            }

            ucPlmnNum--;

            if ( i > 0 )
            {
                i--;
            }
            else
            {
                continue;
            }
        }

        i++;
    }

    *pucEPlmnNum = ucPlmnNum;

    return;
}



VOS_VOID NAS_MMC_DelDuplicatedPlmnInPlmnList(
    VOS_UINT8                          *pucPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstPlmnList
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucPlmnNum;


    ucPlmnNum       = *pucPlmnNum;

    /* ��һ��PLMN�϶������ظ���Ĭ�����б��У�ѭ��������1��ʼ */
    for ( i = 1; i < ucPlmnNum;  )
    {
        if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(&(pstPlmnList[i]),
                                               i, pstPlmnList))
        {
            if (i < (ucPlmnNum - 1))
            {
                (VOS_VOID)PS_MEM_MOVE(&pstPlmnList [i], &pstPlmnList[ i + 1 ],
                            ((ucPlmnNum - i) - 1 ) * sizeof(NAS_MML_PLMN_ID_STRU));
            }

            ucPlmnNum--;

            if ( i > 0 )
            {
                i--;
            }
            else
            {
                continue;
            }
        }

        i++;
    }

    *pucPlmnNum = ucPlmnNum;

    return;
}
VOS_VOID NAS_MML_DelForbPlmnInPlmnList(
    VOS_UINT8                          *pucPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstPlmnList
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucPlmnNum;


    ucPlmnNum       = *pucPlmnNum;

    for ( i = 0; i < ucPlmnNum;  )
    {
        if (VOS_TRUE == NAS_MML_IsPlmnIdInForbidPlmnList(&(pstPlmnList[i])))
        {
            if (i < (ucPlmnNum - 1))
            {
                (VOS_VOID)PS_MEM_MOVE(&pstPlmnList [i], &pstPlmnList[ i + 1 ],
                            ((ucPlmnNum - i) - 1 ) * sizeof(NAS_MML_PLMN_ID_STRU));
            }

            ucPlmnNum--;

            if ( i > 0 )
            {
                i--;
            }
            else
            {
                continue;
            }
        }

        i++;
    }

    *pucPlmnNum = ucPlmnNum;

    return;
}


VOS_UINT32 NAS_MML_GetCsOnlyDataServiceSupportFlg(VOS_VOID)
{
    VOS_UINT32                                              ulIsTestCard;
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU                    *pstMiscellaneousCfgInfo = VOS_NULL_PTR;

    /* GCF���Կ�����PSҵ�񴥷�ע������ */
    ulIsTestCard    = NAS_USIMMAPI_IsTestCard();
    if (VOS_TRUE == ulIsTestCard)
    {
        return VOS_TRUE;
    }

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();

    if (VOS_FALSE == pstMiscellaneousCfgInfo->ucCsOnlyDataServiceSupportFlg)
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}
VOS_UINT32 NAS_MML_IsPlmnListSrchRslt(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT32                          enPlmnSrchRslt
)
{

    switch(enRat)
    {
        /* GUʱ��Щ����������б��ѽ�� */
        case NAS_MML_NET_RAT_TYPE_GSM:
        case NAS_MML_NET_RAT_TYPE_WCDMA:

            if ((RRC_PLMN_SEARCH_RLT_LIST           == enPlmnSrchRslt)
             || (RRC_PLMN_SEARCH_RLT_LIST_REJ       == enPlmnSrchRslt)
             || (RRC_PLMN_SEARCH_RLT_LIST_FAIL      == enPlmnSrchRslt)
             || (RRC_PLMN_SEARCH_RLT_LIST_NO_RF     == enPlmnSrchRslt))
            {
                return VOS_TRUE;
            }
            break;

        /* LTEʱ��Щ����������б��ѽ�� */
        case NAS_MML_NET_RAT_TYPE_LTE:

            if ((MMC_LMM_PLMN_SRCH_RLT_LIST_SUCC    == enPlmnSrchRslt)
             || (MMC_LMM_PLMN_SRCH_RLT_LIST_REJ     == enPlmnSrchRslt)
             || (MMC_LMM_PLMN_SRCH_RLT_LIST_NO_RF   == enPlmnSrchRslt))
            {
                return VOS_TRUE;
            }
            break;

        default:

            break;
    }

    return VOS_FALSE;
}
VOS_UINT32 NAS_MML_IsGetGeoPlmnSrchRslt(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT32                          enPlmnSrchRslt
)
{
    switch(enRat)
    {
        /* GU��ʱ��Щ���������GET_GEO��� */
        case NAS_MML_NET_RAT_TYPE_GSM:
        case NAS_MML_NET_RAT_TYPE_WCDMA:

            if ((RRC_PLMN_SEARCH_RLT_GET_GEO_SUCC   == enPlmnSrchRslt)
             || (RRC_PLMN_SEARCH_RLT_GET_GEO_FAIL   == enPlmnSrchRslt)
             || (RRC_PLMN_SEARCH_RLT_GET_GEO_NO_RF  == enPlmnSrchRslt))
            {
                return VOS_TRUE;
            }
            break;

        /* LTEʱ��Щ���������GET_GEO��� */
        case NAS_MML_NET_RAT_TYPE_LTE:

            if ((MMC_LMM_PLMN_SRCH_RLT_GET_GEO_FAIL     == enPlmnSrchRslt)
             || (MMC_LMM_PLMN_SRCH_RLT_GET_GEO_SUCC     == enPlmnSrchRslt)
             || (MMC_LMM_PLMN_SRCH_RLT_GET_GEO_NO_RF    == enPlmnSrchRslt))
            {
                return VOS_TRUE;
            }
            break;

        default:

            break;
    }

    return VOS_FALSE;
}




VOS_UINT32 NAS_MML_IsCampLaiInfoChanged( VOS_VOID )
{
    NAS_MML_LAI_STRU                   *pstOldLai = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                   *pstCurLai = VOS_NULL_PTR;

    pstOldLai   = NAS_MML_GetOldCampLai();
    pstCurLai   = NAS_MML_GetCurrCampLai();

    if ((pstOldLai->stPlmnId.ulMcc != pstCurLai->stPlmnId.ulMcc)
     || (pstOldLai->stPlmnId.ulMnc != pstCurLai->stPlmnId.ulMnc)
     || (pstOldLai->aucLac[0]      != pstCurLai->aucLac[0])
     || (pstOldLai->aucLac[1]      != pstCurLai->aucLac[1]))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}





VOS_UINT8 NAS_MML_IsRoamingRejectNoRetryFlgActived(VOS_UINT8 ucCause)
 {
    NAS_MML_PLMN_ID_STRU                                   *pstCurplmn    = VOS_NULL_PTR;
    VOS_UINT32                                              ulIsRoam;
    NAS_MML_ROAMINGREJECT_NORETYR_CFG_STRU                 *pstNoRetryCfg = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    i               = 0;
    pstCurplmn      = NAS_MML_GetCurrCampPlmnId();
    ulIsRoam        = NAS_MMC_IsRoam();
    pstNoRetryCfg   = NAS_MML_GetRoamingRejectNoRetryCfg();

    /*
    ��������������ʱ���յ�reject 17������
    1. ���ǲ��Կ���
    2. ����nv��,�ܾ�ԭ��ֵ��nv�����У�
    3. ����״̬�ҵ�ǰPLMN����UPLMNҲ����OPLMN��
    */

    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_FALSE;
    }

    if (VOS_FALSE == ulIsRoam)
    {
        return VOS_FALSE;
    }

    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithUplmn(pstCurplmn))
    {
        return VOS_FALSE;
    }

    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithOplmn(pstCurplmn))
    {
        return VOS_FALSE;
    }

    if (0 == pstNoRetryCfg->ucNoRetryRejectCauseNum)
    {
        return VOS_FALSE;
    }

    for (i=0; i<pstNoRetryCfg->ucNoRetryRejectCauseNum; i++)
    {
        if (ucCause == pstNoRetryCfg->aucNoRetryRejectCause[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT8 NAS_MML_IsUeSupportIms(VOS_VOID)
{
    VOS_UINT8                           ucVoiceOnIms;
    VOS_UINT8                           ucSmsOnIms;
    VOS_UINT8                           ucVideoOnIms;
    VOS_UINT8                           ucUssdOnIms;


    /* �ܿؿ���δ��ʱ����ΪUE��֧��IMS */
    if (VOS_FALSE == NAS_MML_GetLteImsSupportFlg())
    {
        return VOS_FALSE;
    }

    /* ����һ��ҵ������֧��ʱ����ΪUE֧��IMS */
    ucVoiceOnIms    = NAS_MML_GetVoiceCallOnImsSupportFlag();
    ucSmsOnIms      = NAS_MML_GetSmsOnImsSupportFlag();
    ucVideoOnIms    = NAS_MML_GetVideoCallOnImsSupportFlag();
    ucUssdOnIms     = NAS_MML_GetUssdOnImsSupportFlag();

    if ( (VOS_TRUE == ucVoiceOnIms)
      || (VOS_TRUE == ucSmsOnIms)
      || (VOS_TRUE == ucVideoOnIms)
      || (VOS_TRUE == ucUssdOnIms) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_UINT8 NAS_MML_GetMoCallSetupFlg(VOS_VOID)
{
    NAS_MML_MO_CALL_STATUS_ENUM_UINT8   enCallStatus;
    VOS_UINT8                           ucRslt;

    enCallStatus    = NAS_MML_GetMoCallStatus();

    switch(enCallStatus)
    {
        case NAS_MML_CSFB_MO_NORMAL_CALL_SETUP_START:
        case NAS_MML_CSFB_MO_EMC_CALL_SETUP_START:
        case NAS_MML_MO_NORMAL_CALL_SETUP_START:
        case NAS_MML_MO_EMC_CALL_SETUP_START:

            ucRslt  = VOS_TRUE;
            break;

        default:

            ucRslt  = VOS_FALSE;
            break;
    }

    return ucRslt;
}


VOS_UINT8 NAS_MML_GetMoSsSetupFlg(VOS_VOID)
{
    NAS_MML_MO_SS_STATUS_ENUM_UINT8     enSsStatus;
    VOS_UINT8                           ucRslt;

    enSsStatus      = NAS_MML_GetMoSsStatus();

    switch(enSsStatus)
    {
        case NAS_MML_CSFB_MO_SS_SETUP_START:
        case NAS_MML_MO_NORMAL_SS_SETUP_START:

            ucRslt  = VOS_TRUE;
            break;

        default:
            ucRslt  = VOS_FALSE;
            break;

    }

    return ucRslt;
}



VOS_UINT8 NAS_MML_GetCmServiceSetupFlg( VOS_VOID )
{

    /* MO����ҵ���־ */
    if (VOS_TRUE == NAS_MML_GetMoCallSetupFlg())
    {
        return VOS_TRUE;
    }

    /* MO SSҵ���־ */
    if (VOS_TRUE == NAS_MML_GetMoSsSetupFlg())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MML_Is3Gpp2Rat(
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8            enRatType
)
{
    if ((NAS_MSCC_PIF_NET_RAT_TYPE_1X == enRatType)
      ||(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD == enRatType))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


#if (FEATURE_ON == FEATURE_LTE)

VOS_UINT32 NAS_MML_IsImsiInLteOos2GPrefPlmnSelCfg(VOS_VOID)
{
    VOS_UINT32                                              i;
    NAS_MML_PLMN_ID_STRU                                    stHplmnId;
    NAS_MML_PLMN_ID_STRU                                    stPlmnId;
    NAS_MML_LTE_OOS_2G_PREF_PLMN_SEL_CFG_STRU              *pstLteOosPlmnSelCfg = VOS_NULL_PTR;
    VOS_UINT8                                              *pucImsi             = VOS_NULL_PTR;

    i                   = 0;
    pstLteOosPlmnSelCfg = NAS_MML_GetLteOos2GPrefPlmnSelCfg();

    PS_MEM_SET(&stHplmnId,0x00, sizeof(stHplmnId));
    PS_MEM_SET(&stPlmnId, 0x00, sizeof(stPlmnId));

    if ( VOS_FALSE == NAS_MML_GetSimPresentStatus() )
    {
        return VOS_FALSE;
    }

    /* ���Ӳ��Կ����������Կ�ʱ���޸ģ�ֱ�ӷ��� */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_FALSE;
    }

    /* ȡ�ñ���ά����IMSI�ĵ�ַ */
    pucImsi   = NAS_MML_GetSimImsi();

    /* �ӵ�ǰ��IMSI��ȡ��home plmn */
    stHplmnId = NAS_MML_GetImsiHomePlmn(pucImsi);

    /* �ж�IMSI�Ƿ���LTE OOSѡ���Ż������б��� */
    for (i = 0; i < pstLteOosPlmnSelCfg->ucImsiListNum; i++)
    {
        stPlmnId.ulMcc = pstLteOosPlmnSelCfg->astImsiList[i].ulMcc;
        stPlmnId.ulMnc = pstLteOosPlmnSelCfg->astImsiList[i].ulMnc;

        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&stPlmnId, &stHplmnId))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MML_IsNeedSortRatPrioForLteOos2GPrefPlmnSel(
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList
)
{
    if ( (VOS_TRUE                      == NAS_MML_IsImsiInLteOos2GPrefPlmnSelCfg())
      && (NAS_MML_MAX_RAT_NUM           == pstPrioRatList->ucRatNum)
      && (NAS_MML_NET_RAT_TYPE_LTE      == pstPrioRatList->aucRatPrio[0])
      && (NAS_MML_NET_RAT_TYPE_WCDMA    == pstPrioRatList->aucRatPrio[1])
      && (NAS_MML_NET_RAT_TYPE_GSM      == pstPrioRatList->aucRatPrio[2]))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MML_IsLastCampedPlmnIdRoam(VOS_VOID)
{
    NAS_MML_PLMN_ID_STRU               *pstLastCampedPlmn = VOS_NULL_PTR;

    pstLastCampedPlmn = NAS_MMC_GetLastCampedPlmnid();

    /* ��HPLMN��ͬ */
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(pstLastCampedPlmn))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
#endif
VOS_UINT32 NAS_MML_IsGULModeConfigured(VOS_VOID)
{
    /* syscfg set not support HRPD and 1X, we consider it's GUL mode */
    VOS_UINT32                          ulSupport1x;
    VOS_UINT32                          ulSupportHrpd;

    ulSupport1x   = NAS_MML_IsSpec3Gpp2RatInRatList(NAS_MML_3GPP2_RAT_TYPE_CDMA1X, NAS_MML_GetMs3Gpp2PrioRatList());
    ulSupportHrpd = NAS_MML_IsSpec3Gpp2RatInRatList(NAS_MML_3GPP2_RAT_TYPE_HRPD, NAS_MML_GetMs3Gpp2PrioRatList());

    if ((VOS_FALSE == ulSupportHrpd)
     && (VOS_FALSE == ulSupport1x))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/* Added by wx270776 for syscfg_sort, 2015-9-6, begin */
/*****************************************************************************
 �� �� ��  : NAS_MML_GetNewRatFromRatList
 ��������  : �ӽ��뼼���б��л�ȡ�µĽ��뼼��
 �������  : *pstOriRatList:    ԭ�ȵĽ��뼼���б��ַ
             *pstNewRatList:    ���ڵĽ��뼼���б��ַ
 �������  : *pstOutputRatList  ����Ľ��뼼���б�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015-09-06
   ��    ��   : wx270776
   �޸�����   : �����ɺ���

****************************************************************************/
VOS_VOID NAS_MML_GetNewRatFromRatList(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstOriRatList,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstNewRatList,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstOutputRatList
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulNum;
    VOS_UINT32                          ulResult;

    /* ��ʼ�� */
    ulNum    = pstNewRatList->ucRatNum;
    ulResult = VOS_FALSE;

    PS_MEM_SET(pstOutputRatList, 0x00, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    for (i = 0; i < ulNum; i++)
    {
        /* �ж�ָ���Ľ��뼼���Ƿ��ڽ��뼼���б��� */
        ulResult = NAS_MML_IsSpecRatInRatList( pstNewRatList->aucRatPrio[i],
                                               pstOriRatList );

        if (VOS_FALSE == ulResult)
        {
            pstOutputRatList->aucRatPrio[pstOutputRatList->ucRatNum] = pstNewRatList->aucRatPrio[i];
           (pstOutputRatList->ucRatNum)++;
        }
    }
}
/* Added by wx270776 for syscfg_sort, 2015-9-6, end */

VOS_UINT8 NAS_MML_GetCsfbMoCallSetupFlg(VOS_VOID)
{
    NAS_MML_MO_CALL_STATUS_ENUM_UINT8   enCallStatus;
    VOS_UINT8                           ucRslt;

    enCallStatus    = NAS_MML_GetMoCallStatus();

    switch (enCallStatus)
    {
        case NAS_MML_CSFB_MO_NORMAL_CALL_SETUP_START:
        case NAS_MML_CSFB_MO_EMC_CALL_SETUP_START:

            ucRslt  = VOS_TRUE;
            break;

        default:

            ucRslt  = VOS_FALSE;
            break;
    }

    return ucRslt;
}


VOS_UINT8 NAS_MML_GetCsfbMoSsSetupFlg(VOS_VOID)
{
    NAS_MML_MO_CALL_STATUS_ENUM_UINT8   enCallStatus;
    VOS_UINT8                           ucRslt;

    enCallStatus    = NAS_MML_GetMoSsStatus();

    switch (enCallStatus)
    {
        case NAS_MML_CSFB_MO_SS_SETUP_START:

            ucRslt  = VOS_TRUE;
            break;

        default:

            ucRslt  = VOS_FALSE;
            break;
    }

    return ucRslt;
}


VOS_VOID NAS_MML_SetCsfbMtPagingTimerStatus(
    NAS_MML_MT_CSFB_PAGING_TIMER_STATUS_ENUM_UINT8  enStatus
)
{
    NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCmSrvStatus.enMtCsfbPagingTimerStatus = enStatus;

    return;
}


NAS_MML_MT_CSFB_PAGING_TIMER_STATUS_ENUM_UINT8 NAS_MML_GetCsfbMtPagingTimerStatus(VOS_VOID)
{
    return (NAS_MML_GetMmlCtx()->stNetworkInfo.stCsDomainInfo.stCmSrvStatus.enMtCsfbPagingTimerStatus);
}

/* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, begin */
/*****************************************************************************
 �� �� ��  :IsCurrRatGUMode
 ��������  :�жϵ�ǰģ�Ƿ�GUģ
 �������  :
 �������  :
 �� �� ֵ  : VOS_TRUE: ��
             VOS_FALSE������
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2015��10��12��
   ��    ��   : z00359541
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MML_IsCurrGURatMode(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enCurrRat;
    
    enCurrRat = NAS_MML_GetCurrNetRatType();
        
    if ((NAS_MML_NET_RAT_TYPE_WCDMA == enCurrRat)
     || (NAS_MML_NET_RAT_TYPE_GSM == enCurrRat))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  :NAS_MML_IsNeedTriggerPLMNSearch
 ��������  :�ж�ɾ��LAI���Ƿ���Ҫ������������
 �������  :
 �������  :
 �� �� ֵ  : VOS_TRUE: ��Ҫ������������
             VOS_FALSE������Ҫ������������
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2015��10��12��
   ��    ��   : z00359541
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MML_IsNeedTriggerPlmnSearchWhenRemoveCustomizedFrobLa(VOS_VOID)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCampPlmnInfo            = VOS_NULL_PTR;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbidPlmnInfo          = VOS_NULL_PTR;
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriod   = VOS_NULL_PTR;
    VOS_UINT32                                              ulRlstLaiInForbidRegLaiList;
    VOS_UINT32                                              i;

    pstForbLaWithValidPeriod            = NAS_MML_GetForbLaWithValidPeriodList();

    /* ��ȡ��ǰפ��PLMN��Ϣ */
    pstCampPlmnInfo                     = NAS_MML_GetCurrCampPlmnInfo();

    /* ��ȡFPLMN��Ϣ*/
    pstForbidPlmnInfo                   = NAS_MML_GetForbidPlmnInfo();

    ulRlstLaiInForbidRegLaiList         = NAS_MML_IsLaiInDestLaiList(&(pstCampPlmnInfo->stLai),
        pstForbidPlmnInfo->ucForbRegLaNum, pstForbidPlmnInfo->astForbRegLaList);

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_IsNeedTriggerPlmnSearchWhenRemoveCustomizedFrobLa");

    /* פ��PLMN�ڽ�ֹFPLMN�б��� */
    if (VOS_TRUE == NAS_MML_IsPlmnIdInForbidPlmnList(&(pstCampPlmnInfo->stLai.stPlmnId)))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_IsNeedTriggerPlmnSearchWhenRemoveCustomizedFrobLa: Cur PLMN in FPLMN, No need search");
        return VOS_FALSE;
    }

    /* פ����LAI�ڽ�ֹLAI�б��� */
    if ((VOS_TRUE == NAS_MML_IsLaiInDestLaiList(&(pstCampPlmnInfo->stLai),
            pstForbidPlmnInfo->ucForbRoamLaNum, pstForbidPlmnInfo->astForbRomLaList)) ||
        (VOS_TRUE == ulRlstLaiInForbidRegLaiList))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_IsNeedTriggerPlmnSearchWhenRemoveCustomizedFrobLa: Cur LA in Forb LA, No need search");
        return VOS_FALSE;
    }

    /* �жϳ�ʱ��LAI�Ƿ��ǵ�ǰפ����LAI */
    for (i = 0; i < pstForbLaWithValidPeriod->ulForbLaWithValidPeriodNum; i++)
    {
        if (0 == NAS_MMC_GetCustomizedForbLaLeftTimeLen(&(pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i])))
        {
            if(VOS_TRUE == NAS_MML_CompareLai(&(pstCampPlmnInfo->stLai),
                &(pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].stForbLaWithValidPeriodLai)))
            {
                NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_IsNeedTriggerPlmnSearchWhenRemoveCustomizedFrobLa: Cur LA will remove from Customized Forb LA, need search");
                return VOS_TRUE;
            }
        }
    }
    
    return VOS_FALSE;
 }

/*****************************************************************************
 �� �� ��  :NAS_MML_StartCustomizedForbLaTimer
 ��������  :����ɾ�����ƽ�ֹLA�б�ʱ��
 �������  :pstForbLaWithValidPeriod
 �������  :
 �� �� ֵ  : VOS_TRUE: ��ʱ������
             VOS_FALSE����ʱ��δ����
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2015��9��23��
   ��    ��   : z00359541
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MML_StartCustomizedForbLaTimer(VOS_VOID)
{
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriod = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulLeftTimeLen;
    VOS_UINT32                                              ulTmpTimeLen;
    
    pstForbLaWithValidPeriod            = NAS_MML_GetForbLaWithValidPeriodList();
    ulLeftTimeLen                       = NAS_MML_MAX_TIME_TICK;

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_StartCustomizedForbLaTimer");

    /* ��ֹLA�б�Ϊ�գ������� */
    if (0 == pstForbLaWithValidPeriod->ulForbLaWithValidPeriodNum)
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_StartCustomizedForbLaTimer: Customized Forb LA is empty");
        return;
    }

    (VOS_VOID)NAS_MMC_StopTimer(TI_NAS_MMC_CUSTOMIZED_FORB_LA_TIMER);

    /* ��ȡ��ǰ�б�����̵�ʣ��ʱ�� */
    for ( i = 0; i < pstForbLaWithValidPeriod->ulForbLaWithValidPeriodNum; i++ )
    {
        ulTmpTimeLen = NAS_MMC_GetCustomizedForbLaLeftTimeLen(&(pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i]));
        
        if (0 == ulTmpTimeLen)
        {
            continue;
        }
        
        ulLeftTimeLen = NAS_MML_MIN(ulLeftTimeLen, ulTmpTimeLen);        
    }

    NAS_NORMAL_LOG2(WUEPS_PID_MMC, "NAS_MML_StartCustomizedForbLaTimer: Get the Customized Forb LA num and next expire timer len: ",
        pstForbLaWithValidPeriod->ulForbLaWithValidPeriodNum, ulLeftTimeLen);

    if (NAS_MML_MAX_TIME_TICK != ulLeftTimeLen)
    {
        /* Modified by z00359541 for CS REG FAIL FORB LA, 2015-11-7, begin */
        /* ������ʱ�� */
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_StartCustomizedForbLaTimer: Start FORB LA timer");
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_CUSTOMIZED_FORB_LA_TIMER,
                            (((ulLeftTimeLen)*NAS_MML_ONE_THOUSAND_MILLISECOND)/NAS_MML_SECOND_TO_TICK));
        /* Modified by z00359541 for CS REG FAIL FORB LA, 2015-11-7, end */
    }

    return;
}

/*****************************************************************************
 �� �� ��  :NAS_MML_GetForbLaWithValidPeriodTimerLen
 ��������  :��ȡ��Ӧʧ��ԭ��ֵ�ĳͷ�ʱ��
 �������  :NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16          enRegFailCause,
            NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_LIST_STRU   *pstForbLaWithValidPeriodCfg
 �������  :
 �� �� ֵ  :��Ӧ��ԭ��ֵ�ĳͷ�ʱ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
1.��    ��   : 2015��9��23��
   ��    ��   : z00359541
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT16 NAS_MML_GetForbLaWithValidPeriodTimerLen(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enRegFailCause,
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_LIST_STRU   *pstForbLaWithValidPeriodCfg
)
{
    VOS_UINT32                                              i;

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_GetForbLaWithValidPeriodTimerLen");

    for (i = 0; i < pstForbLaWithValidPeriodCfg->ulSupportForbLaWithValidPeriodNum; i++)
    {
        if (pstForbLaWithValidPeriodCfg->astForbLaWithValidPeriodCfgList[i].usRegFailCause == enRegFailCause)
        {
            return pstForbLaWithValidPeriodCfg->astForbLaWithValidPeriodCfgList[i].usForbLaValidPeriodLen;
        }
    }

    /* û���ҵ���Ӧƥ��ʱ��������Ϊ0 */
    return 0;
}

/*****************************************************************************
 �� �� ��  :NAS_MML_GetCustomizedForbLaPunishTimeLen
 ��������  :��ȡ��Ӧʧ��ԭ��ֵ��ƹ�һ��Ƶĳͷ�ʱ��
 �������  :NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16          enRegFailCause,
            NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_LIST_STRU   *pstForbLaWithValidPeriodCfg
 �������  :
 �� �� ֵ  :��Ӧ��ԭ��ֵ�ķ�ƹ�һ��Ƶĳͷ�ʱ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��9��23��
   ��    ��   : z00359541
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT16 NAS_MML_GetCustomizedForbLaPunishTimeLen(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enRegFailCause,
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_LIST_STRU   *pstForbLaWithValidPeriodCfg
)
{
    VOS_UINT32                                              i;

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_GetCustomizedForbLaPunishTimeLen");

    for (i = 0; i < pstForbLaWithValidPeriodCfg->ulSupportForbLaWithValidPeriodNum; i++)
    {
        if (pstForbLaWithValidPeriodCfg->astForbLaWithValidPeriodCfgList[i].usRegFailCause == enRegFailCause)
        {
            return pstForbLaWithValidPeriodCfg->astForbLaWithValidPeriodCfgList[i].usPunishTimeLen;
        }
    }

    /* û���ҵ���Ӧƥ��ʱ��������Ϊ0 */
    return 0;
}

/* Added by z00359541 for CS REG FAIL FORB LA, 2015-11-7, begin */
/*****************************************************************************
 �� �� ��  : NAS_MML_IsCustomizedForbLaTimerExpired
 ��������  : �ж϶�ʱ���Ƿ��Ѿ���ʱ�������趨Ϊ1��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32

 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2015��11��7��
   ��    ��   : z00359541
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MML_IsCustomizedForbLaTimerExpired(
    VOS_UINT32                                              ulDuration,
    VOS_UINT32                                              ulPeriod
)
{
    if ((ulDuration >= ulPeriod)
     || ((ulDuration + NAS_MML_CUSTOMIZED_FORB_LA_TIMER_PRECISION) >= ulPeriod))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
/* Added by z00359541 for CS REG FAIL FORB LA, 2015-11-7, end */

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCustomizedForbLaLeftTimeLen
 ��������  : ��ȡ��ֹLA��ʣ��ʱ��
 �������  : pstLaiWithValidPeriod - ��ֹLA��Чʱ���б��е�Ԫ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32

 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2015��9��23��
   ��    ��   : z00359541
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetCustomizedForbLaLeftTimeLen(
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_STRU                 *pstLaWithValidPeriod
)
{
    VOS_UINT32                                              ulCurrTimeTick;
    VOS_UINT32                                              ulDuration;
    /* Modified by z00359541 for CS REG FAIL FORB LA, 2015-11-7, begin */
    VOS_UINT32                                              ulPunishDuration;
    VOS_UINT32                                              ulLeftTimeLen;
    VOS_UINT32                                              ulPunishLeftTimeLen;
    /* Modified by z00359541 for CS REG FAIL FORB LA, 2015-11-7, end */

    ulCurrTimeTick = VOS_GetTick();

    NAS_NORMAL_LOG3(WUEPS_PID_MMC,
        "NAS_MMC_GetCustomizedForbLaLeftTimeLen: Current Tick and Forb La BeginTick, Period",
        ulCurrTimeTick,
        pstLaWithValidPeriod->ulForbLaWithValidPeriodBeginTick,
        pstLaWithValidPeriod->ulForbLaWithValidPeriodTick
        );

    /* ���LAI ��nv���õĽ�ֹ����ΪȫF���򷵻�VOS_FALSE���趯̬ɾ�� */
    if (NAS_MML_MAX_TIME_TICK == pstLaWithValidPeriod->ulForbLaWithValidPeriodTick)
    {
        return NAS_MML_MAX_TIME_TICK;
    }

    ulDuration = ulCurrTimeTick - pstLaWithValidPeriod->ulForbLaWithValidPeriodBeginTick;

    /* Modified by z00359541 for CS REG FAIL FORB LA, 2015-11-7, begin */
    ulPunishDuration = ulCurrTimeTick - pstLaWithValidPeriod->ulForbLaWithValidPeriodPunishBeginTick;

    /* ��ʱ������Ϊ1�룬�뵽��1���ڶ��㳬ʱ */
    if (VOS_TRUE == NAS_MML_IsCustomizedForbLaTimerExpired(ulDuration, pstLaWithValidPeriod->ulForbLaWithValidPeriodTick))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCustomizedForbLaLeftTimeLen: Customized Forb LA timer expired");
        ulLeftTimeLen = 0;
    }
    else
    {
        /* ���㵱ǰʣ���ֹ��Чʱ�� */
        ulLeftTimeLen = pstLaWithValidPeriod->ulForbLaWithValidPeriodTick - ulDuration;
    }

    /* ��ƹ�ҳͷ�ʱ���ѹ� */
    if (VOS_TRUE == NAS_MML_IsCustomizedForbLaTimerExpired(ulPunishDuration,
        pstLaWithValidPeriod->ulForbLaWithValidPeriodPunishDurationTick))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCustomizedForbLaLeftTimeLen: Customized Forb LA punish timer expired");
        ulPunishLeftTimeLen = 0;
    }
    else
    {
        /* ���㵱ǰ�ͷ�ʣ��ʱ�� */
        ulPunishLeftTimeLen =  pstLaWithValidPeriod->ulForbLaWithValidPeriodPunishDurationTick - ulPunishDuration;
    }

    /* ȡ����ʣ��ʱ���е���СֵΪ����ֵ */
    return NAS_MML_MIN(ulLeftTimeLen, ulPunishLeftTimeLen);

    /* Modified by z00359541 for CS REG FAIL FORB LA, 2015-11-7, end */
}

/*****************************************************************************
 �� �� ��  : NAS_MML_CompareLac
 ��������  : �ж�LAC�Ƿ���ͬ
 �������  : pstCurLai
             pstOldLai 
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ��ͬ
             VOS_FALSE: ��ͬ
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2015��9��23��
   ��    ��   : z00359541
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MML_CompareLac(
    NAS_MML_LAI_STRU                                       *pstCurLai,
    NAS_MML_LAI_STRU                                       *pstOldLai
)
{
    VOS_UINT32                         i;

    for ( i = 0 ; i < NAS_MML_MAX_LAC_LEN ; i++ )
    {
        if (pstCurLai->aucLac[i] != pstOldLai->aucLac[i])
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MML_DeleteLaFromForbLaWithValidPeriodList
 ��������  : �ӽ�ֹLA�б���ɾ��ָ��������LA
 �������  : pstForbLaWithValidPeriod
 �������  : pstForbLaWithValidPeriod
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2015��9��23��
   ��    ��   : z00359541
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MML_DeleteLaFromForbLaWithValidPeriodList(
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriod,
    VOS_UINT32                                              ulIndex
)
{

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_DeleteLaFromForbLaWithValidPeriodList");

    /* ɾ��ָ����LAI */
    if (ulIndex < (pstForbLaWithValidPeriod->ulForbLaWithValidPeriodNum - 1))
    {
        (VOS_VOID)PS_MEM_MOVE(&(pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[ulIndex]),
                     &(pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[ulIndex + 1]),
                     ((pstForbLaWithValidPeriod->ulForbLaWithValidPeriodNum- ulIndex) - 1) * sizeof(NAS_MML_FORB_LA_WITH_VALID_PERIOD_STRU));
    }
    
    /* ɾ��LA��, ���¸��� */
    pstForbLaWithValidPeriod->ulForbLaWithValidPeriodNum--;

    /* ��ά�ɲ��ӡ */
    NAS_MMC_LogForbLaWithValidPeriodListInfo();

}

/*****************************************************************************
 �� �� ��  : NAS_MML_IsNeedProtectionBeforeDeleteCustomizedForbLa
 ��������  : �ж��Ƿ���Ҫ���������һ���
 �������  : pstForbLaWithValidPeriod
 �������  : pstForbLaWithValidPeriod
 �� �� ֵ  : 
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2015��9��23��
   ��    ��   : z00359541
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MML_IsNeedProtectionBeforeDeleteCustomizedForbLa(
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriod,
    VOS_UINT32                                              ulIndex
)
{
    NAS_MML_LAI_STRU                                       *pstCurrCampLai      = VOS_NULL_PTR;
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_STRU                 *pstCustomizedForbLa = VOS_NULL_PTR;
    VOS_UINT32                                              ulMatchEplmnFlg;
    VOS_UINT32                                              ulPunishTimeDuration;
    VOS_UINT32                                              ulCsServiceFlg;

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_IsNeedProtectionBeforeDeleteCustomizedForbLa");

    pstCurrCampLai                      = NAS_MML_GetCurrCampLai();
    pstCustomizedForbLa                 = &(pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[ulIndex]);
    ulMatchEplmnFlg                     = NAS_MML_IsPlmnInEplmnList(&(pstCustomizedForbLa->stForbLaWithValidPeriodLai.stPlmnId));
    ulPunishTimeDuration                = VOS_GetTick() - pstCustomizedForbLa->ulForbLaWithValidPeriodPunishBeginTick;
    ulCsServiceFlg                      = NAS_MMC_IsCsNormalService();

    NAS_NORMAL_LOG2(WUEPS_PID_MMC, "NAS_MML_IsNeedProtectionBeforeDeleteCustomizedForbLa: ulCsServiceFlg and ulMatchEplmnFlg",
        ulCsServiceFlg, ulMatchEplmnFlg);

    /* �����һ��ƣ��ͷ�ʱ������Ϊ1�� */
    if ( (VOS_TRUE == ulCsServiceFlg)
      && (VOS_TRUE == ulMatchEplmnFlg)
      && ((ulPunishTimeDuration + NAS_MML_CUSTOMIZED_FORB_LA_TIMER_PRECISION) < pstCustomizedForbLa->ulForbLaWithValidPeriodPunishDurationTick) )
    {
        /* �Ƚϵ�ǰפ��PLMN��Ҫɾ����PLMN�Ƿ���ͬ */
        if (VOS_FALSE == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstCurrCampLai->stPlmnId),
                            &(pstCustomizedForbLa->stForbLaWithValidPeriodLai.stPlmnId)))
        {
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_IsNeedProtectionBeforeDeleteCustomizedForbLa(): In EPLMN list, Start Protection");
            return VOS_TRUE;
        }

        /* �Ƚϵ�ǰפ����LAC��Ҫɾ����LAC�Ƿ���ͬ */
        if (VOS_FALSE == NAS_MML_CompareLac(pstCurrCampLai,
                            &(pstCustomizedForbLa->stForbLaWithValidPeriodLai)))
        {
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_IsNeedProtectionBeforeDeleteCustomizedForbLa(): Same PLMN, Diff LA, Start Protection");
            return VOS_TRUE;
        }
        
        return VOS_FALSE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MML_DeleteExpiredLaFromForbLaWithValidPeriodList
 ��������  : ����ʱ����ʱ��ע��ɹ�ʱ�ӽ�ֹLA�б���ɾ��ָ��LA�Ĵ���
 �������  : pstForbLaWithValidPeriod
 �������  : pstForbLaWithValidPeriod
 �� �� ֵ  : 
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2015��9��23��
   ��    ��   : z00359541
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MML_DeleteExpiredLaFromForbLaWithValidPeriodList(
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriod
)
{
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_LIST_STRU   *pstForbLaWithValidPeriodCfg = VOS_NULL_PTR;
    VOS_UINT16                                              usTimeLen;
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulDeleteFlg;

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_DeleteExpiredLaFromForbLaWithValidPeriodList");

    ulDeleteFlg                         = VOS_FALSE;    
    pstForbLaWithValidPeriodCfg         = NAS_MML_GetForbLaWithValidPeriodCfg();

    /* �ж����б�����һ��LA��ʱ */
    for (i = 0; i < pstForbLaWithValidPeriod->ulForbLaWithValidPeriodNum; i++)
    {
        usTimeLen = NAS_MML_GetForbLaWithValidPeriodTimerLen(pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].enCsRegFailCause,
                                                pstForbLaWithValidPeriodCfg); 
        if (0 == NAS_MMC_GetCustomizedForbLaLeftTimeLen(&(pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i])))
        {
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_DeleteExpiredLaFromForbLaWithValidPeriodList: Got expired LA");

            /* �����һ����Ƿ���Ҫ���� */
            if (VOS_TRUE == NAS_MML_IsNeedProtectionBeforeDeleteCustomizedForbLa(pstForbLaWithValidPeriod, i))
            {        
                /* ���½�ֹLA��Ϣ */
                pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].ulForbLaWithValidPeriodTick                    = NAS_MML_SECOND_TO_TICK * usTimeLen;
                pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].ulForbLaWithValidPeriodBeginTick               = VOS_GetTick();
                NAS_NORMAL_LOG4(WUEPS_PID_MMC,
                    "NAS_MML_DeleteExpiredLaFromForbLaWithValidPeriodList: Ping-Pang protection started, update Forb La info(BeginTick, Period, PunishBeginTick)",
                    i,
                    pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].ulForbLaWithValidPeriodBeginTick,
                    pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].ulForbLaWithValidPeriodTick,
                    pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].ulForbLaWithValidPeriodPunishBeginTick
                    );

                continue;
            }
            
            /* ɾ��ָ����LAI */
            NAS_MML_DeleteLaFromForbLaWithValidPeriodList(pstForbLaWithValidPeriod, i); 

            ulDeleteFlg = VOS_TRUE;
        }
    }

    return ulDeleteFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MML_IsLaiInForbLaWithValidPeriodList
 ��������  : �ж�LAI �Ƿ��ڽ�ֹLA �б���
 �������  : pstForbLai:��Ҫ�жϵ�LAI
 �������  : ��
 �� �� ֵ  : LAI�ڽ�ֹLA�б��е�����������ƥ�䣬�������ֵ
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2015��9��23��
   ��    ��   : z00359541
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MML_GetLaiIndexInForbLaWithValidPeriodList(
    NAS_MML_LAI_STRU                                       *pstCurrCampLai,
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriod
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulIndex;

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_GetLaiIndexInForbLaWithValidPeriodList");

    ulIndex = NAS_MML_MIN(pstForbLaWithValidPeriod->ulForbLaWithValidPeriodNum, NAS_MML_CUSTOMIZE_FORB_LA_MAX_NUM);    

    for ( i = 0; i < ulIndex; i++ )
    {
        /* �Ƚ�LAI */
        if(VOS_TRUE == NAS_MML_CompareLai(pstCurrCampLai,
            &(pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[i].stForbLaWithValidPeriodLai)))
        {
            return i;
        }
    }

    return NAS_MML_CUSTOMIZE_FORB_LA_MAX_NUM;
}

/*****************************************************************************
 �� �� ��  :NAS_MML_AddCsRegFailLaIntoForbLaListWithValidPeriod
 ��������  :�жϵ�ǰCSע��ʧ��ԭ��ֵ�Ƿ�ƥ���ֹLA����
 �������  :CSע��ʧ��ԭ��ֵ
 �������  :
 �� �� ֵ  :FORB LA�Ƿ�仯
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��9��23��
   ��    ��   : z00359541
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MML_AddCsRegFailLaIntoForbLaListWithValidPeriod(
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_STRU        *pstForbLaWithValidPeriodCfgInfo
)
{
    NAS_MML_LAI_STRU                                       *pstCurrCampLai              = VOS_NULL_PTR;
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriod    = VOS_NULL_PTR;
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_STRU                 *pstCustomizedForbLa         = VOS_NULL_PTR;
    VOS_UINT32                                              ulIndex;

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_AddCsRegFailLaIntoForbLaListWithValidPeriod");

    pstCurrCampLai                      = NAS_MML_GetCurrCampLai();
    pstForbLaWithValidPeriod            = NAS_MML_GetForbLaWithValidPeriodList();

    /* �ڽ�ֹLA�б���Ѱ�ҵ�ǰLAIƥ�� */
    ulIndex                             = NAS_MML_GetLaiIndexInForbLaWithValidPeriodList(pstCurrCampLai, pstForbLaWithValidPeriod);

    /* ���pstForbLai�Ѿ��ڽ�ֹLA �б������������ */
    if (NAS_MML_CUSTOMIZE_FORB_LA_MAX_NUM != ulIndex)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MML_AddCsRegFailLaIntoForbLaListWithValidPeriod: LAI already added in Forb LA With Valid Period List");
        return VOS_FALSE;
    }

    /* �б�����,���������ֹLA�б�������LAI */
    if (NAS_MML_CUSTOMIZE_FORB_LA_MAX_NUM <= pstForbLaWithValidPeriod->ulForbLaWithValidPeriodNum)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MML_AddCsRegFailLaIntoForbLaListWithValidPeriod: Could not add  LAI into Forb LA With Valid Period List because it's full");
        return VOS_FALSE;
    }

    /* ��ǰLAI���ڽ�ֹLA�б����棬�ҵ�ǰ�б�δ��������Ҫ��LAI���뵽��ֹLA�б����� */
    ulIndex             = pstForbLaWithValidPeriod->ulForbLaWithValidPeriodNum;
    pstCustomizedForbLa = &(pstForbLaWithValidPeriod->astForbLaWithValidPeriodList[ulIndex]);

    pstCustomizedForbLa->stForbLaWithValidPeriodLai.stPlmnId.ulMcc               = pstCurrCampLai->stPlmnId.ulMcc;
    pstCustomizedForbLa->stForbLaWithValidPeriodLai.stPlmnId.ulMnc               = pstCurrCampLai->stPlmnId.ulMnc;
    pstCustomizedForbLa->stForbLaWithValidPeriodLai.aucLac[0]                    = pstCurrCampLai->aucLac[0];
    pstCustomizedForbLa->stForbLaWithValidPeriodLai.aucLac[1]                    = pstCurrCampLai->aucLac[1];
    pstCustomizedForbLa->stForbLaWithValidPeriodLai.enCampPlmnNetRat             = pstCurrCampLai->enCampPlmnNetRat;
    pstCustomizedForbLa->stForbLaWithValidPeriodLai.ucRac                        = pstCurrCampLai->ucRac;

    NAS_NORMAL_LOG1(WUEPS_PID_MMC, "NAS_MML_AddCsRegFailLaIntoForbLaListWithValidPeriod: Current Tick", VOS_GetTick());    

    /* ���½�ֹLA��Чʱ�� */
    pstCustomizedForbLa->ulForbLaWithValidPeriodTick                             = NAS_MML_SECOND_TO_TICK * (pstForbLaWithValidPeriodCfgInfo->usForbLaValidPeriodLen);
    pstCustomizedForbLa->ulForbLaWithValidPeriodBeginTick                        = VOS_GetTick();

    /* ���·�ƹ�һ��Ƴͷ�ʱ�� */
    pstCustomizedForbLa->ulForbLaWithValidPeriodPunishBeginTick                  = VOS_GetTick();
    pstCustomizedForbLa->ulForbLaWithValidPeriodPunishDurationTick               = NAS_MML_SECOND_TO_TICK * (pstForbLaWithValidPeriodCfgInfo->usPunishTimeLen);
    pstCustomizedForbLa->enCsRegFailCause                                        = pstForbLaWithValidPeriodCfgInfo->usRegFailCause;
    pstForbLaWithValidPeriod->ulForbLaWithValidPeriodNum++;

    /* ��ά�ɲ��ӡ */
    NAS_MMC_LogForbLaWithValidPeriodListInfo();
    
    return VOS_TRUE;
}
/* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, end */

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

