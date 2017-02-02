/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MnCallFacilityDecode.c
  �� �� ��   : ����
  ��    ��   : ���� 49431
  ��������   : 2007��9��20��
  ����޸�   : 2007��9��20��
  ��������   : ʵ��CS������ص�API�ӿں���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ļ�
******************************************************************************/
/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "Taf_Ssa_DecodeDef.h"
#include "MnCallFacilityDecode.h"
#include "MnComm.h"
#include "NasCcIe.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
  2 ��������
*****************************************************************************/


/*****************************************************************************
  3���Ͷ���
*****************************************************************************/


/*****************************************************************************
  4 �궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_MNCALL_FACILITY_DECODE_C

/*lint -e961*/

#define MN_CALL_DecodeEctCallState(pucDest, pucSrc, TagMode)\
            SSA_DecodeEnum(pucDest, pucSrc, TagMode)

#define MN_CALL_DecodeMultiCallInd(pucDest, pucSrc, TagMode)\
            SSA_DecodeEnum(pucDest, pucSrc, TagMode)
#define MN_CALL_DecodeCallOnHoldInd(pucDest, pucSrc, TagMode)\
            SSA_DecodeEnum(pucDest, pucSrc, TagMode)


#define MN_CALL_DecodeCugIndex(value, content, tagmode)\
            SSA_DecodeInt(value, 32767, content, tagmode)

#define MN_CALL_DecodePartyNumber(NumType, aucNumer, ppucSrc, TagMode) \
            SSA_DecodeForwardedToNumber(NumType, aucNumer, ppucSrc, TagMode)

#define MN_CALL_DecodePartyNumberSubAddr(pucSubAddrType, pucSubAddr, ppucSrc, ucTagMode)\
            SSA_DecodeForwardedToSubaddress(pucSubAddrType, pucSubAddr, ppucSrc, ucTagMode)

#define MN_CALL_DecodePresentationAllowedAddr(pDest, ppucSrc, ucTagMode, pucEndLocation)\
            MN_CALL_DecodePresentationAddress(pDest, ppucSrc, ucTagMode, pucEndLocation)

#define MN_CALL_DecodePresentationRestrictedAddr(pDest, ppucSrc, ucTagMode, pucEndLocation)\
            MN_CALL_DecodePresentationAddress(pDest, ppucSrc, ucTagMode, pucEndLocation)

#define MN_CALL_DecodeNamePresentationRestricted(pDest, ppucSrc, ucTagMode)\
            MN_CALL_DecodeNamePresentation(pDest, ppucSrc, ucTagMode)

#define MN_CALL_DecodeNamePresentationAllowed(pDest, ppucSrc, ucTagMode)\
            MN_CALL_DecodeNamePresentation(pDest, ppucSrc, ucTagMode)


/*lint +e961*/

extern VOS_UINT32 SSA_DecodeSsNull(VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode);
/*****************************************************************************
  5 ��������
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  6 ����ʵ��
*****************************************************************************/

LOCAL VOS_UINT32 MN_CALL_DecodePresentationAddress(
    MN_CALL_PRESENTATION_ADDR_STRU      *pstDest,
    VOS_UINT8                           **ppucSrc,
    TAG_MODE                            ucTagMode,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt = VOS_OK;

    /*���TAG_MODEΪEXPLICITģʽ*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L,ȷ������λ��*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (VOS_OK != ulRslt)
        {
            MN_WARN_LOG("MN_CALL_DecodePresentationAddress:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (VOS_OK != ulRslt)
        {
            MN_WARN_LOG("MN_CALL_DecodePresentationAddress:WARNING: Length Value Error");
            return ulRslt;
        }
    }


    /*�Ա�ǩ���н��룬����TLV�е�T��L,ȷ������λ��*/
    ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
    if (VOS_OK != ulRslt)
    {
        MN_WARN_LOG("MN_CALL_DecodePresentationAddress:WARNING: Tag Value Wrong");
        return ulRslt;
    }

    ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
    if (VOS_OK != ulRslt)
    {
        MN_WARN_LOG("MN_CALL_DecodePresentationAddress:WARNING: Length Value Error");
        return ulRslt;
    }

    /*�ж��Ƿ���PartyNumber�������Tagֵ:0x84*/
    if ((0 == gSsTagValue.iNumber)&&(CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass))
    {
         /*����PartyNumber���������ʧ���򷵻�*/
         ulRslt = MN_CALL_DecodePartyNumber(&(pstDest->NumType), pstDest->aucPartyNumber, ppucSrc, IMPLICIT_MODE);
         if (VOS_OK != ulRslt)
         {
             MN_WARN_LOG("MN_CALL_DecodePresentationAddress:WARNING: PartyNumber Decode Failure");
             return ulRslt;
         }
     }
     else
     {
         MN_WARN_LOG("MN_CALL_DecodePresentationAddress:WARNING: PartyNumber Tag Value Err");
         return VOS_ERR;
     }

    /* ��ѡ�ӵ�ַ������,���سɹ� */
     if (pucEndLocation <= *ppucSrc)
     {
         return ulRslt;
     }

     /*�Ա�ǩ���н��룬����TLV�е�T��L,ȷ������λ��*/
     ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
     if (VOS_OK != ulRslt)
     {
         MN_WARN_LOG("MN_CALL_DecodePresentationAddress:WARNING: Tag Value Wrong");
         return ulRslt;
     }

     ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
     if (VOS_OK != ulRslt)
     {
         MN_WARN_LOG("MN_CALL_DecodePresentationAddress:WARNING: Length Value Error");
         return ulRslt;
     }
     /*�ж��Ƿ���partyNumberSubaddress�������Tagֵ:0x84*/
     if ((1 == gSsTagValue.iNumber)&&(CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass))
     {
         /*����partyNumberSubaddress���������ʧ���򷵻�*/
         ulRslt = MN_CALL_DecodePartyNumberSubAddr(&(pstDest->NumType), pstDest->aucPartyNumber, ppucSrc, IMPLICIT_MODE);
         if (VOS_OK != ulRslt)
         {
             MN_WARN_LOG("MN_CALL_DecodePresentationAddress:WARNING: partyNumberSubaddress Decode Failure");
             return ulRslt;
         }
     }
     else
     {
         MN_WARN_LOG("MN_CALL_DecodePresentationAddress:WARNING: partyNumberSubaddress Tag Value Err");
         return VOS_ERR;
     }

     return ulRslt;

}

/*****************************************************************************
 Prototype      : MN_CALL_DecodeNamePresentation
 Description    : ��������namePresentationAllowed��namePresentationRestricted����,���Ͷ���μ�24.080,��¼
 Input          : **ppucSrc--����ǰ���ִ�, ucTagMode -- ��ǩģʽ
 Output         : *pDest--������ִ�
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2006-01-21
    Author      : ---
    Modification: Created function
*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_DecodeNamePresentation(
    MN_CALL_NAME_PRESENTATION_STRU      *pstDest,
    VOS_UINT8                           **ppucSrc,
    TAG_MODE                            ucTagMode
)
{
    VOS_UINT32                          ulRslt = VOS_OK;
    VOS_UINT8                           ucStrLen;

    /*���TAG_MODEΪEXPLICITģʽ*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L,ȷ������λ��*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (VOS_OK != ulRslt)
        {
            MN_WARN_LOG("MN_CALL_DecodeNamePresentation:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (VOS_OK != ulRslt)
        {
            MN_WARN_LOG("MN_CALL_DecodeNamePresentation:WARNING: Length Value Error");
            return ulRslt;
        }
    }

    /*���������dataCodingScheme*/
    ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
    if (VOS_OK != ulRslt)
    {
        MN_WARN_LOG("MN_CALL_DecodeNamePresentation:WARNING: Tag Value Wrong");
        return ulRslt;
    }
    ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
    if (VOS_OK != ulRslt)
    {
        MN_WARN_LOG("MN_CALL_DecodeNamePresentation:WARNING: Length Value Error");
        return ulRslt;
    }


    if((0 == gSsTagValue.iNumber)&&(CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass))
    {
        gulCurStrMaxLen = 1;
        ulRslt = SSA_DecodeString(&(pstDest->DataCodingScheme), &ucStrLen, ppucSrc, IMPLICIT_MODE);
        if (VOS_OK != ulRslt)
        {
            MN_WARN_LOG("MN_CALL_DecodeNamePresentation:WARNING: dataCodingScheme Decode Failure");
            return ulRslt;
        }
    }
    else
    {
        MN_WARN_LOG("MN_CALL_DecodePresentationAddress:WARNING: dataCodingScheme Tag Value Err");
        return VOS_ERR;
    }


    /*���������lengthInCharacters*/
    ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
    if (VOS_OK != ulRslt)
    {
        MN_WARN_LOG( "MN_CALL_DecodeNamePresentation:WARNING: Tag Value Wrong");
        return ulRslt;
    }
    ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
    if (VOS_OK != ulRslt)
    {
        MN_WARN_LOG( "MN_CALL_DecodeNamePresentation:WARNING: Length Value Error");
        return ulRslt;
    }
    if((1 == gSsTagValue.iNumber)&&(CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass))
    {
        gulCurStrMaxLen = 1;
        ulRslt = SSA_DecodeInt(&(pstDest->LengthInCharacters), 32767, ppucSrc, IMPLICIT_MODE);
        if (VOS_OK != ulRslt)
        {
            MN_WARN_LOG( "MN_CALL_DecodeNamePresentation:WARNING: lengthInCharacters Decode Failure");
            return ulRslt;
        }
    }
    else
    {
        MN_WARN_LOG( "MN_CALL_DecodePresentationAddress:WARNING: lengthInCharacters Tag Value Err");
        return VOS_ERR;
    }

    /*���������nameString*/
    ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
    if (VOS_OK != ulRslt)
    {
        MN_WARN_LOG( "MN_CALL_DecodeNamePresentation:WARNING: Tag Value Wrong");
        return ulRslt;
    }
    ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
    if (VOS_OK != ulRslt)
    {
        MN_WARN_LOG( "MN_CALL_DecodeNamePresentation:WARNING: Length Value Error");
        return ulRslt;
    }
    if((2 == gSsTagValue.iNumber)&&(CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass))
    {
        gulCurStrMaxLen = 161;
        ulRslt = SSA_DecodeString(pstDest->NameString, &ucStrLen, ppucSrc, IMPLICIT_MODE);
        if (VOS_OK != ulRslt)
        {
            MN_WARN_LOG( "MN_CALL_DecodeNamePresentation:WARNING: SSA_DecodeString Decode Failure");
            return ulRslt;
        }
    }
    else
    {
        MN_WARN_LOG( "MN_CALL_DecodePresentationAddress:WARNING: lengthInCharacters Tag Value Err");
        return VOS_ERR;
    }

    return ulRslt;
}

/*****************************************************************************
 Prototype      : MN_CALL_DecodeEctIndicator
 Description    : ��������ss-Notification����,���Ͷ���μ�24.080,��¼
 Input          : **ppucSrc--����ǰ���ִ�, ucTagMode -- ��ǩģʽ
 Output         : *pucDest--������ִ�
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2006-01-21
    Author      : ---
    Modification: Created function
*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_DecodeSsNotification(
    VOS_UINT8                           *pucDest,
    VOS_UINT8                           **ppucSrc,
    TAG_MODE                            ucTagMode
)
{
    VOS_UINT8                           ucStrLen;

    /* ���룬���ؽ��뺯���Ĳ������ */
    gulCurStrMaxLen = 1;
    return  SSA_DecodeString(pucDest, &ucStrLen, ppucSrc, ucTagMode);

}
LOCAL VOS_UINT32 MN_CALL_DecodeEctIndicator(
    MN_CALL_ECT_INDICATOR_STRU          *pstDest,
    VOS_UINT8                           **ppucSrc,
    TAG_MODE                            ucTagMode
)
{
    VOS_UINT8                           *pucEndLocation;
    VOS_UINT32                          ulRslt = VOS_OK;

    /*���TAG_MODEΪEXPLICITģʽ*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L,ȷ������λ��*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (VOS_OK != ulRslt)
        {
            MN_WARN_LOG( "MN_CALL_DecodeEctIndicator:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (VOS_OK != ulRslt)
        {
            MN_WARN_LOG( "MN_CALL_DecodeEctIndicator:WARNING: Length Value Error");
            return ulRslt;
        }
    }

    /*�ִ�������ĵ�ַ*/
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*��ect-CallState���н���*/
    /*����TLV�е�T��L,ȷ������λ��*/
    ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
    if (VOS_OK != ulRslt)
    {
        MN_WARN_LOG( "MN_CALL_DecodeEctIndicator:WARNING: Tag Value Wrong");
        return ulRslt;
    }
    ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
    if (VOS_OK != ulRslt)
    {
        MN_WARN_LOG( "MN_CALL_DecodeEctIndicator:WARNING: Length Value Error");
        return ulRslt;
    }

    /*�жϱ�ǩֵ����ȷ��*/
    if ((0 == gSsTagValue.iNumber)&&(CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass))
    {
        /*����ect-CallState������,�������ʧ��,�򷵻�*/
        ulRslt = MN_CALL_DecodeEctCallState(&(pstDest->EctCallState), ppucSrc, IMPLICIT_MODE);
        if (VOS_OK != ulRslt)
        {
            MN_WARN_LOG( "MN_CALL_DecodeEctIndicator:WARNING: ect-CallState decode Failure");
            return ulRslt;
        }
    }
    else
    {
        /*��ǩֵ����ect-CallState�ı�ǩֵ,ʧ�ܷ���*/
        MN_WARN_LOG( "MN_CALL_DecodeEctIndicator:WARNING: ect-CallState TagNumber is Error");
        return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
    }

    /*�ж��Ƿ��в�����rdn,�еĻ�����,û������*/
    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L,ȷ������λ��*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (VOS_OK != ulRslt)
        {
            MN_WARN_LOG( "MN_CALL_DecodeEctIndicator:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (VOS_OK != ulRslt)
        {
            MN_WARN_LOG( "MN_CALL_DecodeEctIndicator:WARNING: Length Value Error");
            return ulRslt;
        }

        /*�ж��Ƿ���rdn�������Tagֵ:0x81,choice����*/
        if ((1 == gSsTagValue.iNumber)&&(CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)&&(*ppucSrc < pucEndLocation))
        {
            /*����rdn������,����ʧ���򷵻�*/
            /*�Ա�ǩ���н��룬����TLV�е�T��L*/
            ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeEctIndicator:WARNING: Tag Value Wrong");
                return ulRslt;
            }
            ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeEctIndicator:WARNING: Length Value Error");
                return ulRslt;
            }

            switch(gSsTagValue.iNumber)
            {
            /*������presentationAllowedAddress*/
            case 0x00:
                ulRslt = MN_CALL_DecodePresentationAllowedAddr(&(pstDest->PresentationAllowedAddr),
                                                            ppucSrc,
                                                            IMPLICIT_MODE,
                                                            pucEndLocation);
                if (VOS_OK != ulRslt)
                {
                    MN_WARN_LOG( "MN_CALL_DecodeEctIndicator:WARNING: presentationAllowedAddress decode Failure");
                    return ulRslt;
                }
                pstDest->OP_PresentationAllowedAddr= 1;
                break;
            /*������presentationRestricted*/
            case 0x01:
                ulRslt = SSA_DecodeSsNull(ppucSrc, (VOS_UINT8)IMPLICIT_MODE);
                if (VOS_OK != ulRslt)
                {
                    MN_WARN_LOG( "MN_CALL_DecodeEctIndicator:WARNING: presentationRestricted decode Failure");
                    return ulRslt;
                }
                pstDest->OP_PresentationRestricted= 1;
                break;
            /*������numberNotAvailableDueToInterworking*/
            case 0x02:
                ulRslt = SSA_DecodeSsNull(ppucSrc, (VOS_UINT8)IMPLICIT_MODE);
                if (VOS_OK != ulRslt)
                {
                    MN_WARN_LOG( "MN_CALL_DecodeEctIndicator:WARNING: numberNotAvailableDueToInterworking decode Failure");
                    return ulRslt;
                }
                pstDest->OP_NumNotAvailableDueToInterworking= 1;
                break;
            /*������presentationRestrictedAddress*/
            case 0x03:
                ulRslt = MN_CALL_DecodePresentationRestrictedAddr(&(pstDest->PresentationRestrictedAddr),
                                                     ppucSrc,
                                                     IMPLICIT_MODE,
                                                     pucEndLocation);
                if (VOS_OK != ulRslt)
                {
                    MN_WARN_LOG( "MN_CALL_DecodeEctIndicator:WARNING: presentationRestrictedAddress decode Failure");
                    return ulRslt;
                }
                pstDest->OP_PresentationRestrictedAddr= 1;
                break;
            default:
                MN_WARN_LOG( "MN_CALL_DecodeEctIndicator:WARNING: Tag Value Error");
                break;
            }

        }
        else
        {
            return ulRslt;
        }
    }

    /*�жϵ�ǰָ���λ�ú��Ƿ�ͱ�ǩ����һ��*/
    if (pucEndLocation != *ppucSrc)
    {
        MN_WARN_LOG( "MN_CALL_DecodeEctIndicator:WARNING: Length Value not equal with actual length");
        return VOS_ERR;
    }

    return ulRslt;
}
LOCAL VOS_UINT32 MN_CALL_DecodeNameIndicator(
    MN_CALL_NAME_INDICATOR_STRU         *pstDest,
    VOS_UINT8                           **ppucSrc,
    TAG_MODE                            ucTagMode
)
{
    VOS_UINT8       *pucEndLocation;
    VOS_UINT32       ulRslt = VOS_OK;

    /*���TAG_MODEΪEXPLICITģʽ*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L,ȷ������λ��*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (VOS_OK != ulRslt)
        {
            MN_WARN_LOG( "MN_CALL_DecodeNameIndicator:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (VOS_OK != ulRslt)
        {
            MN_WARN_LOG( "MN_CALL_DecodeNameIndicator:WARNING: Length Value Error");
            return ulRslt;
        }
    }

    /*�ִ�������ĵ�ַ*/
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*��callingName���н���*/
    /*����TLV�е�T��L,ȷ������λ��*/
    ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
    if (VOS_OK != ulRslt)
    {
        MN_WARN_LOG( "MN_CALL_DecodeNameIndicator:WARNING: Tag Value Wrong");
        return ulRslt;
    }
    ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
    if (VOS_OK != ulRslt)
    {
        MN_WARN_LOG( "MN_CALL_DecodeNameIndicator:WARNING: Length Value Error");
        return ulRslt;
    }

    /*�жϱ�ǩֵ����ȷ��*/
    if ((0 == gSsTagValue.iNumber)&&(CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass))
    {
        /*����callingName������,����ʧ���򷵻�*/
        /*�Ա�ǩ���н��룬����TLV�е�T��L*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (VOS_OK != ulRslt)
        {
            MN_WARN_LOG( "MN_CALL_DecodeNameIndicator:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (VOS_OK != ulRslt)
        {
            MN_WARN_LOG( "SSA_DecodeCallBarringFeature:WARNING: Length Value Error");
            return ulRslt;
        }

        switch(gSsTagValue.iNumber)
        {
        /*������namePresentationAllowed*/
        case 0x00:
            ulRslt = MN_CALL_DecodeNamePresentationAllowed(&(pstDest->NamePresentationAllowed),
                                                 ppucSrc,
                                                 IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNameIndicator:WARNING: namePresentationAllowed decode failure");
                return ulRslt;
            }
            pstDest->OP_NamePresentationAllowed= 1;
            break;
        /*������presentationRestricted*/
        case 0x01:
            ulRslt = SSA_DecodeSsNull(ppucSrc, (VOS_UINT8)IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNameIndicator:WARNING: presentationRestricted decode failure");
                return ulRslt;
            }
            pstDest->OP_RresentationRestricted= 1;
            break;
        /*������nameUnavailable*/
        case 0x02:
            ulRslt = SSA_DecodeSsNull(ppucSrc, (VOS_UINT8)IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNameIndicator:WARNING: nameUnavailable decode failure");
                return ulRslt;
            }
            pstDest->OP_NameUnAvailable= 1;
            break;
        /*������namePresentationRestricted*/
        case 0x03:
            ulRslt = MN_CALL_DecodeNamePresentationRestricted(&(pstDest->NamePresentationRestricted),
                                                 ppucSrc,
                                                 IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNameIndicator:WARNING: namePresentationRestricted decode failure");
                return ulRslt;
            }
            pstDest->OP_NamePresentationRestricted= 1;
            break;
        default:
            MN_WARN_LOG( "MN_CALL_DecodeNameIndicator:WARNING: Tag Value Error");
            break;
        }

    }
    else
    {
        return ulRslt;
    }

    /*�жϵ�ǰָ���λ�ú��Ƿ�ͱ�ǩ����һ��*/
    if (pucEndLocation != *ppucSrc)
    {
        MN_WARN_LOG( "MN_CALL_DecodeNameIndicator:WARNING: Length Value not equal with actual length");
        return VOS_ERR;
    }

    return ulRslt;
}
VOS_UINT32 MN_CALL_DecodeNotifySsSsCode(
    MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*�жϱ�ǩ���ͺͱ�ǩֵ�����жϽ���λ��*/
        if ((0x01 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*����ss-Code������,�������ʧ��,�򷵻�*/
            ulRslt = SSA_DecodeSsCode(&(pstDest->SsCode), ppucSrc, IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNotifySsSsCode:WARNING: ss-Code decode Failure");
                return ulRslt;
            }
            pstDest->OP_SsCode = 1;
        }
        else
        {
            /*������ss-Code��*/
            *ppucSrc           = pucCurLocation;
            pstDest->OP_SsCode = 0;
        }
    }
    else
    {
        pstDest->OP_SsCode = 0;
        ulRslt             = SSA_SUCCESS;
    }

    return ulRslt;
}


VOS_UINT32 MN_CALL_DecodeNotifySsSsStatus(
    MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt = SSA_SUCCESS;
    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*�жϱ�ǩ���ͺͱ�ǩֵ�����жϽ���λ��*/
        if ((0x04 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*����ss-Status������,�������ʧ��,�򷵻�*/
            ulRslt = SSA_DecodeSsStatus(&(pstDest->SsStatus),
                                        ppucSrc, IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNotifySsSsStatus:WARNING: ss-Status decode Failure");
                return ulRslt;
            }
            pstDest->OP_SsStatus = 1;
        }
        else
        {
            /*������ss-Status��*/
            pstDest->OP_SsStatus = 0;
            *ppucSrc             = pucCurLocation;
        }

    }
    else
    {
        pstDest->OP_SsStatus = 0;
        ulRslt               = SSA_SUCCESS;
    }

    return ulRslt;
}


VOS_UINT32 MN_CALL_DecodeNotifySsSsNotification(
    MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*�жϱ�ǩ���ͺͱ�ǩֵ�����жϽ���λ��*/
        if ((0x05 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*����ss-Notification������,�������ʧ��,�򷵻�*/
            ulRslt = MN_CALL_DecodeSsNotification(&(pstDest->SsNotification),
                                                  ppucSrc, IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNotifySsSsNotification:WARNING: ss-Notification Failure");
                return ulRslt;
            }
            pstDest->OP_SsNotification = 1;
        }
        else
        {
            /*������ss-Notification��*/
            pstDest->OP_SsNotification = 0;
            *ppucSrc                   = pucCurLocation;
        }
    }
    else
    {
        pstDest->OP_SsNotification = 0;
        ulRslt                     = SSA_SUCCESS;
    }

    return ulRslt;
}


VOS_UINT32 MN_CALL_DecodeNotifySsCallWaitingInd(
    MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*�жϱ�ǩ���ͺͱ�ǩֵ�����жϽ���λ��*/
        if ((0x0e == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc <= pucEndLocation))
        {
            /*����callIsWaiting-Indicator������,�������ʧ��,�򷵻�*/
            ulRslt = SSA_DecodeSsNull(ppucSrc, (VOS_UINT8)IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNotifySsCallWaitingInd:WARNING: callIsWaiting-Indicator decode Failure");
                return ulRslt;
            }
            pstDest->OP_CallWaitingInd = 1;
        }
        else
        {
            /*������callOnHold-Indicator��*/
            pstDest->OP_CallWaitingInd = 0;
            *ppucSrc                   = pucCurLocation;
        }
    }
    else
    {
        pstDest->OP_CallWaitingInd = 0;
        ulRslt                     = SSA_SUCCESS;
    }

    return ulRslt;
}


VOS_UINT32 MN_CALL_DecodeNotifySsCallOnHoldInd(
    MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*�жϱ�ǩ���ͺͱ�ǩֵ�����жϽ���λ��*/
        if ((0x0f == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*����callOnHold-Indicator������,�������ʧ��,�򷵻�*/
            ulRslt = MN_CALL_DecodeCallOnHoldInd(&(pstDest->CallOnHoldIndicator),
                                                 ppucSrc, IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNotifySsCallOnHoldInd:WARNING: callOnHold-Indicator decode Failure");
                return ulRslt;
            }
            pstDest->OP_CallOnHoldInd = 1;
        }
        else
        {
            /*������callOnHold-Indicator��*/
            pstDest->OP_CallOnHoldInd = 0;
            *ppucSrc                  = pucCurLocation;
        }

    }
    else
    {
        pstDest->OP_CallOnHoldInd = 0;
        ulRslt                    = SSA_SUCCESS;
    }

    return ulRslt;
}


VOS_UINT32 MN_CALL_DecodeNotifySsMptyIndicator(
    MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;
    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*�жϱ�ǩ���ͺͱ�ǩֵ�����жϽ���λ��*/
        if ((0x10 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc <= pucEndLocation))
        {
            /*����mpty-Indicator������,�������ʧ��,�򷵻�*/
            ulRslt = SSA_DecodeSsNull(ppucSrc, (VOS_UINT8)IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNotifySsMptyIndicator:WARNING: mpty-Indicator decode Failure");
                return ulRslt;
            }
            pstDest->OP_MptyIndicator = 1;
        }
        else
        {
            /*������mpty-Indicator��*/
            pstDest->OP_MptyIndicator = 0;
            *ppucSrc                  = pucCurLocation;
        }
    }
    else
    {
        pstDest->OP_MptyIndicator = 0;
        ulRslt                    = SSA_SUCCESS;
    }

    return ulRslt;
}


VOS_UINT32 MN_CALL_DecodeNotifySsCugIndex(
    MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32       ulRslt = SSA_SUCCESS;
    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*�жϱ�ǩ���ͺͱ�ǩֵ�����жϽ���λ��*/
        if ((0x11 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*����cug-Index������,�������ʧ��,�򷵻�*/
            ulRslt = MN_CALL_DecodeCugIndex(&(pstDest->CugIndex),
                                            ppucSrc, IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNotifySsCugIndex:WARNING: cug-Index Failure");
                return ulRslt;
            }
            pstDest->OP_CugIndex = 1;
        }
        else
        {
            /*������cug-Index��*/
            pstDest->OP_CugIndex = 0;
            *ppucSrc             = pucCurLocation;
        }
    }
    else
    {
        pstDest->OP_CugIndex = 0;
        ulRslt               = SSA_SUCCESS;
    }

    return ulRslt;
}


VOS_UINT32 MN_CALL_DecodeNotifySsClirSuppressionRej(
    MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*�жϱ�ǩ���ͺͱ�ǩֵ�����жϽ���λ��*/
        if ((0x12 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc <= pucEndLocation))
        {
            /*����clirSuppressionRejected������,�������ʧ��,�򷵻�*/
            ulRslt = SSA_DecodeSsNull(ppucSrc, (VOS_UINT8)IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNotifySsClirSuppressionRej:WARNING: clirSuppressionRejected decode Failure");
                return ulRslt;
            }
            pstDest->OP_ClirSuppressionRej = 1;
        }
        else
        {
            /*������clirSuppressionRejected��*/
            pstDest->OP_ClirSuppressionRej = 0;
            *ppucSrc                       = pucCurLocation;
        }

    }
    else
    {
        pstDest->OP_ClirSuppressionRej = 0;
        ulRslt                         = SSA_SUCCESS;
    }

    return ulRslt;
}


VOS_UINT32 MN_CALL_DecodeNotifySsEctIndicator(
    MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;
    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*�жϱ�ǩ���ͺͱ�ǩֵ�����жϽ���λ��*/
        if ((0x13 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*����ect-Indicator������,�������ʧ��,�򷵻�*/
            ulRslt = MN_CALL_DecodeEctIndicator(&(pstDest->EctIndicator),
                                                ppucSrc, IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNotifySsEctIndicator:WARNING: ect-Indicator Failure");
                return ulRslt;
            }
            pstDest->OP_EctIndicator = 1;
        }
        else
        {
            /*������ect-Indicator��*/
            pstDest->OP_EctIndicator = 0;
            *ppucSrc                 = pucCurLocation;
        }
    }
    else
    {
        pstDest->OP_EctIndicator = 0;
        ulRslt                   = SSA_SUCCESS;
    }

    return ulRslt;
}


VOS_UINT32 MN_CALL_DecodeNotifySsNameIndicator(
    MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*�жϱ�ǩ���ͺͱ�ǩֵ�����жϽ���λ��*/
        if ((0x14 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*����nameIndicator������,�������ʧ��,�򷵻�*/
            ulRslt = MN_CALL_DecodeNameIndicator(&(pstDest->NameIndicator),
                                                 ppucSrc, IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNotifySsNameIndicator:WARNING: nameIndicator Failure");
                return ulRslt;
            }
            pstDest->OP_NameIndicator = 1;
        }
        else
        {
            /*������nameIndicator��*/
            pstDest->OP_NameIndicator = 0;
            *ppucSrc                  = pucCurLocation;
        }

    }
    else
    {
        pstDest->OP_NameIndicator = 0;
        ulRslt                    = SSA_SUCCESS;
    }

    return ulRslt;
}


VOS_UINT32 MN_CALL_DecodeNotifySsCcbsFeature(
    MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*�жϱ�ǩ���ͺͱ�ǩֵ�����жϽ���λ��*/
        if ((0x15 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*����ccbs-Feature������,�������ʧ��,�򷵻�*/
            ulRslt = SSA_DecodeCcbsFeature(&(pstDest->CcbsFeature),
                                           ppucSrc, IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNotifySsCcbsFeature:WARNING: ccbs-Feature decode Failure");
                return ulRslt;
            }
            pstDest->OP_CcbsFeature = 1;
        }
        else
        {
            /*������ccbs-Feature��*/
            pstDest->OP_CcbsFeature = 0;
            *ppucSrc                = pucCurLocation;
        }
    }
    else
    {
        pstDest->OP_CcbsFeature = 0;
        ulRslt                  = SSA_SUCCESS;
    }

    return ulRslt;
}


VOS_UINT32 MN_CALL_DecodeNotifySsAlertingPattern(
    MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*�жϱ�ǩ���ͺͱ�ǩֵ�����жϽ���λ��*/
        if ((0x16 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*����alertingPattern������,�������ʧ��,�򷵻�*/
            ulRslt = SSA_DecodeAlertingPattern(&(pstDest->AlertingPattern),
                                               ppucSrc, IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNotifySsAlertingPattern:WARNING: alertingPattern decode Failure");
                return ulRslt;
            }
            pstDest->OP_AlertingPattern = 1;
        }
        else
        {
            /*������alertingPattern��*/
            pstDest->OP_AlertingPattern = 0;
            *ppucSrc                    = pucCurLocation;
        }

    }
    else
    {
        pstDest->OP_AlertingPattern = 0;
        ulRslt                      = SSA_SUCCESS;
    }

    return ulRslt;
}


VOS_UINT32 MN_CALL_DecodeNotifySsMultiCallInd(
    MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32       ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*�жϱ�ǩ���ͺͱ�ǩֵ�����жϽ���λ��*/
        if ((0x17 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*����multicall-Indicator������,�������ʧ��,�򷵻�*/
            ulRslt = MN_CALL_DecodeMultiCallInd(&(pstDest->MulticallIndicator),
                                                ppucSrc, IMPLICIT_MODE);
            if (VOS_OK != ulRslt)
            {
                MN_WARN_LOG( "MN_CALL_DecodeNotifySsMultiCallInd:WARNING: multicall-Indicator decode Failure");
                return ulRslt;
            }
            pstDest->OP_MulticallInd = 1;
        }
        else
        {
            /*���һ����������ǩֵ������Ϊ�����������������������Ϊ����*/
            MN_WARN_LOG( "MN_CALL_DecodeNotifySsMultiCallInd:WARNING: multicall-Indicator Tag Number Error");
            return TAF_SS_REJ_MISTYPED_COMPONENT;

        }
    }
    else
    {
        pstDest->OP_MulticallInd = 0;
        ulRslt                   = SSA_SUCCESS;
    }

    return ulRslt;
}

LOCAL VOS_UINT32 MN_CALL_DecodeNotifySs(
    MN_CALL_SS_NOTIFYSS_ARG_STRU        *pstDest,
    VOS_UINT8                           **ppucSrc
)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           *pucEndLocation;
    VOS_UINT8                           *pucCurLocation;

    *((VOS_UINT32 *)pstDest) = 0;

    /*����TLV�е�T��L,ȷ������λ��*/
    ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*�ִ�������ĵ�ַ*/
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*��ǽ���ָ�뵱ǰλ��*/
    pucCurLocation = *ppucSrc;

    /*�������SsCode*/
    ulRslt = MN_CALL_DecodeNotifySsSsCode(pstDest, ppucSrc,
                                          pucCurLocation, pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*��ǽ���ָ�뵱ǰλ��*/
    pucCurLocation = *ppucSrc;

    /*�������ss-Status*/
    ulRslt = MN_CALL_DecodeNotifySsSsStatus(pstDest, ppucSrc,
                                            pucCurLocation,pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*��ǽ���ָ�뵱ǰλ��*/
    pucCurLocation = *ppucSrc;

    /*�������ss-Notification*/
    ulRslt = MN_CALL_DecodeNotifySsSsNotification(pstDest, ppucSrc,
                                                  pucCurLocation, pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*��ǽ���ָ�뵱ǰλ��*/
    pucCurLocation = *ppucSrc;

    /*�������callIsWaiting-Indicator*/
    ulRslt = MN_CALL_DecodeNotifySsCallWaitingInd(pstDest, ppucSrc,
                                                  pucCurLocation, pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*��ǽ���ָ�뵱ǰλ��*/
    pucCurLocation = *ppucSrc;

    /*�������callOnHold-Indicator*/
    ulRslt = MN_CALL_DecodeNotifySsCallOnHoldInd(pstDest, ppucSrc,
                                                 pucCurLocation, pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*��ǽ���ָ�뵱ǰλ��*/
    pucCurLocation = *ppucSrc;

    /*�������mpty-Indicator*/
    ulRslt = MN_CALL_DecodeNotifySsMptyIndicator(pstDest, ppucSrc,
                                                 pucCurLocation, pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*��ǽ���ָ�뵱ǰλ��*/
    pucCurLocation = *ppucSrc;

    /*�������cug-Index*/
    ulRslt = MN_CALL_DecodeNotifySsCugIndex(pstDest, ppucSrc,
                                            pucCurLocation, pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*��ǽ���ָ�뵱ǰλ��*/
    pucCurLocation = *ppucSrc;

    /*�������clirSuppressionRejected*/
    ulRslt = MN_CALL_DecodeNotifySsClirSuppressionRej(pstDest, ppucSrc,
                                                      pucCurLocation, pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*��ǽ���ָ�뵱ǰλ��*/
    pucCurLocation = *ppucSrc;

    /*�������ect-Indicator*/
    ulRslt = MN_CALL_DecodeNotifySsEctIndicator(pstDest, ppucSrc,
                                                pucCurLocation, pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*��ǽ���ָ�뵱ǰλ��*/
    pucCurLocation = *ppucSrc;

    /*�������nameIndicator*/
    ulRslt = MN_CALL_DecodeNotifySsNameIndicator(pstDest, ppucSrc,
                                                 pucCurLocation, pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*��ǽ���ָ�뵱ǰλ��*/
    pucCurLocation = *ppucSrc;

    /*�������ccbs-Feature*/
    ulRslt = MN_CALL_DecodeNotifySsCcbsFeature(pstDest, ppucSrc,
                                               pucCurLocation, pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*��ǽ���ָ�뵱ǰλ��*/
    pucCurLocation = *ppucSrc;

    /*�������alertingPattern*/
    ulRslt = MN_CALL_DecodeNotifySsAlertingPattern(pstDest,ppucSrc,
                                                   pucCurLocation, pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*��ǽ���ָ�뵱ǰλ��*/
    pucCurLocation = *ppucSrc;

    /*�������multicall-Indicator*/
    ulRslt = MN_CALL_DecodeNotifySsMultiCallInd(pstDest, ppucSrc,
                                                pucCurLocation, pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    return ulRslt;
}

/*****************************************************************************
 Prototype      : MN_CALL_SsInvokeArgDecode()
 Description    : ���������Ϣ����
 Input          : ucOpCode - ������
                  pucSrc   - �����������
 Output         : punArg   - �����Ļ���ָ��
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-19
    Author      : cjh
    Modification: Created function
*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_SsInvokeArgDecode(
    VOS_UINT8                           ucOpCode,
    VOS_UINT8                           *pucSrc,
    MN_CALL_SS_COMPONENT_ARG_UNION      *punArg
)
{
    switch(ucOpCode)
    {
    case MN_CALL_SS_NOTIFYSS_OPERATION:
        return MN_CALL_DecodeNotifySs(&punArg->notifySsArg, &pucSrc);

    default:
        return VOS_ERR;
    }
}

#if 0
LOCAL VOS_UINT32 CALL_SsResultArgEncode(
    VOS_UINT8                            ucOpCode,
    const MN_CALL_SS_COMPONENT_ARG_UNION *punArg,
    VOS_UINT8                            *pucDest
)
{
    return 0;
}
#endif

/*****************************************************************************
 Prototype      : MN_CALL_SsResultArgDecode()
 Description    : ���������Ϣ����
 Input          : ucOpCode - ������
                  pucSrc   - �����������
 Output         : punArg   - �����Ļ���ָ��
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-19
    Author      : cjh
    Modification: Created function
*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_SsResultArgDecode(
    VOS_UINT8                           ucOpCode,
    VOS_UINT8                           *pucSrc,
    MN_CALL_SS_COMPONENT_ARG_UNION      *punArg
)
{
    return VOS_ERR;
}

#if 0
/*****************************************************************************
 Prototype      : MN_CALL_SsErrorArgDecode()
 Description    : ��������Ϣ����
 Input          : ucErrorCode - ��Ҫ�����component������
                  punArg      - Component���ֵ�����
 Output         : pucDest     - �����Ļ���ָ��
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-19
    Author      : cjh
    Modification: Created function
*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_SsErrorArgDecode(
    VOS_UINT8                            ucErrorCode,
    const MN_CALL_SS_COMPONENT_ARG_UNION *punArg,
    VOS_UINT8                            *pucDest
)
{
    return 0;
}
#endif

/*****************************************************************************
 Prototype      : MN_CALL_SsErrorArgDecode()
 Description    : ��������Ϣ����
 Input          : pucSrc      - ��Ҫ���������
                  ucErrorCode - ������
 Output         : punArg      - �����Ļ���ָ��
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-19
    Author      : cjh
    Modification: Created function
*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_SsErrorArgDecode(
    VOS_UINT8                           ucErrorCode,
    VOS_UINT8                           *pucSrc,
    MN_CALL_SS_COMPONENT_ARG_UNION      *punArg
)
{
    return VOS_ERR;
}



/*****************************************************************************
 Prototype      : MN_CALL_SsComponentDecode
 Description    : Component���ֽ���
 Input          : pucSrc - ������ִ�
 Output         : punComponent - Component���ֵĽ���

 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-19
    Author      : cjh
    Modification: Created function
*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_SsComponentDecode(
    VOS_UINT8                           *pucSrc,
    MN_CALL_SS_COMPONENT_UNION          *punComponent
)
{
    punComponent->ucCompType = pucSrc[0];

    switch(punComponent->ucCompType)
    {
    case MN_CALL_SS_INVOKE_TYPE_TAG:
        punComponent->invokeComp.ucInvokeId = pucSrc[4];
        if (pucSrc[5] == MN_CALL_SS_LINKED_ID_TAG)
        {
            punComponent->invokeComp.bitOpLinkId = 1;
            punComponent->invokeComp.ucLinkId = pucSrc[7];
            punComponent->invokeComp.ucOperateCode = pucSrc[10];
            if (MN_CALL_SsInvokeArgDecode(punComponent->invokeComp.ucOperateCode,
                                      &pucSrc[11],
                                      &punComponent->invokeComp.unArg) == VOS_OK)
            {
                punComponent->invokeComp.bitOpArg = 1;
            }
        }
        else
        {
            punComponent->invokeComp.bitOpLinkId = 0;
            punComponent->invokeComp.ucOperateCode = pucSrc[7];
            if (MN_CALL_SsInvokeArgDecode(punComponent->invokeComp.ucOperateCode,
                                      &pucSrc[8],
                                      &punComponent->invokeComp.unArg) == VOS_OK)
            {
                punComponent->invokeComp.bitOpArg = 1;
            }
            else
            {
                punComponent->invokeComp.bitOpArg = 0;
            }
        }
        break;

    case MN_CALL_SS_RETURN_RESULT_TYPE_TAG:
        punComponent->resultComp.ucInvokeId = pucSrc[4];
        if (pucSrc[1] > 8)
        {
            /* Omitted if the Return Result component
            does not include any parameters. - 24.080*/
            punComponent->resultComp.bitOpSequence = 1;
            punComponent->resultComp.bitOpOperateCode = 1;
            punComponent->resultComp.ucSequenceTag = pucSrc[5];
            punComponent->resultComp.ucOperateCode = pucSrc[9];
            if (MN_CALL_SsResultArgDecode(punComponent->resultComp.ucOperateCode,
                                     &pucSrc[10],
                                     &punComponent->resultComp.unArg) == VOS_OK)
            {
                punComponent->resultComp.bitOpArg = 1;
            }
            else
            {
                punComponent->resultComp.bitOpArg = 0;
            }
        }
        else
        {
            punComponent->resultComp.bitOpArg = 0;
            punComponent->resultComp.bitOpSequence = 0;
            punComponent->resultComp.bitOpOperateCode = 0;
        }
        break;

    case MN_CALL_SS_RETURN_ERROR_TYPE_TAG:
        punComponent->errorComp.ucInvokeId = pucSrc[4];
        punComponent->errorComp.ucErrorCode = pucSrc[7];
        if (pucSrc[1] > 6)
        {
            if (MN_CALL_SsErrorArgDecode(punComponent->errorComp.ucErrorCode,
                                    &pucSrc[8],
                                    &punComponent->errorComp.unArg) == VOS_OK)
            {
                punComponent->errorComp.bitOpArg = 1;
            }
            else
            {
                punComponent->errorComp.bitOpArg = 0;
            }
        }
        else
        {
            punComponent->errorComp.bitOpArg = 0;
        }
        break;

    case MN_CALL_SS_REJECT_TYPE_TAG:
        punComponent->rejectComp.ucInvokeId = pucSrc[4];
        punComponent->rejectComp.ucProblemCode = pucSrc[7];
        break;

    default:
        return VOS_ERR;
    }

    return VOS_OK;

}

/*****************************************************************************
 Prototype      : MN_CALL_FacilityDecode()
 Description    : Facility��Ϣ����
 Input          : ulMsgPointer   ������Ϣ��ָ��
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-19
    Author      : cjh
    Modification: Created function
*****************************************************************************/
VOS_UINT32 MN_CALL_FacilityDecode(
    const NAS_CC_IE_FACILITY_STRU       *pstFacility,
    MN_CALL_SS_COMPONENT_UNION          *punComponent
)
{
    VOS_UINT8                           aucFacility[NAS_CC_MAX_FACILITY_LEN];

    PS_MEM_SET(aucFacility, 0x00, sizeof(aucFacility));

    /* �˴�Ϊ�˹�ܸ澯�����ں��������ʱ�򣬲�����û�����Ƴ�const  */
    PS_MEM_CPY(aucFacility, pstFacility->aucFacility, NAS_CC_MAX_FACILITY_LEN);

    if(0 == pstFacility->LastOctOffset)
    /* if (0 == NAS_IE_GET_BLOCK_SIZE(pstFacility, aucFacility)) */
    {
        MN_ERR_LOG ( "MN_CALL_FacilityDecode:  IE length is 0!\n" );
        return VOS_ERR;
    }

    if (VOS_OK != MN_CALL_SsComponentDecode(aucFacility, punComponent))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif



