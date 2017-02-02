

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "Ps.h"

#include "Taf_Common.h"
#include "Taf_Ssa_EncodeDef.h"
#include "TafStdlib.h"
#include "TafMmiEncode.h"
#include "mnmsgcbencdec.h"
#include "MnErrorCode.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_SSA_ENCODE_C



/*lint -save -e958 */

/*****************************************************************************
 Prototype      : SSA_EncodeRegisterSSReq
 Description    : ��MS�����RegisterSS������facility���ݽ��б���
 Input          : *pSrc--����ǰ�����ݽṹ
 Output         : *pucContent--�������ִ�   *pucCodeLen--�ִ��ĳ���
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_EncodeRegisterSSReq(VOS_UINT8   *pucContent, VOS_UINT8  *pucCodeLen, TAF_SS_REGISTERSS_REQ_STRU *pSrc)
{
    VOS_UINT8           ucTmpLen = 0;              /*��¼ÿ��������ı��볤��,��ʼֵΪ0*/
    VOS_UINT8           ucOffset = 0;
    VOS_UINT32          ulRslt;

    gpucSsEncodeEndLocation = pucContent + MAX_FACILITY_LEN;

    /*�Բ�����ss-Code���б���, ����ʧ���򷵻�*/
    ulRslt = SSA_EncodeSsCode(pucContent + ucOffset, &ucTmpLen, &(pSrc->SsCode), EXPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeRegisterSSReq:WARNING:SSA_EncodeSsCode encode failure");
        return ulRslt;
    }
    /*����ƫ��ֵ*/
    ucOffset = ucOffset + ucTmpLen;

    /*����в�����basicService���������Ӧ������ı���, ����ʧ���򷵻�*/
    if (pSrc->OP_BsService)
    {
        ulRslt = SSA_EncodeBasicService(pucContent + ucOffset, &ucTmpLen, &(pSrc->BsService), EXPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeRegisterSSReq:WARNING:SSA_EncodeBasicService encode failure");
            return ulRslt;
        }
        /*����ƫ��ֵ*/
        ucOffset = ucOffset + ucTmpLen;
    }

    /*����в�����forwardedToNumber���SSA_EncodeForwardedToNumber������Ӧ������ı��? ����ʧ���򷵻�*/
    if (pSrc->OP_FwdToNum)
    {
        ulRslt = SSA_EncodeForwardedToNumber(pucContent + ucOffset, &ucTmpLen, pSrc->NumType, pSrc->aucFwdToNum, IMPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeRegisterSSReq:WARNING:SSA_EncodeForwardedToNumber encode failure");
            return ulRslt;
        }
        /*IMPLICITģʽ�£���ͷ�����з�װ*/
        ulRslt = SSA_PackTL(0x84, pucContent + ucOffset , &ucTmpLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeRegisterSSReq:WARNING:FwdToNum: Tag Length encode failure");
            return ulRslt;
        }
        /*����ƫ��ֵ*/
        ucOffset = ucOffset + ucTmpLen;
    }

    /*����в�����forwardedToSubaddress���������Ӧ������ı���, ����ʧ���򷵻�*/
    if (pSrc->OP_FwdToAddr)
    {
        ulRslt = SSA_EncodeForwardedToSubaddress(pucContent + ucOffset, &ucTmpLen, pSrc->SubAddrType, pSrc->aucFwdToSubAddr, IMPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeRegisterSSReq:WARNING:SSA_EncodeForwardedToSubaddress encode failure");
            return ulRslt;
        }
        /*IMPLICITģʽ�£���ͷ�����з�װ*/
        ulRslt = SSA_PackTL(0x86, pucContent + ucOffset , &ucTmpLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeRegisterSSReq:WARNING:FwdToAddr: Tag Length encode encode failure");
            return ulRslt;
        }
        /*����ƫ��ֵ*/
        ucOffset = ucOffset + ucTmpLen;
    }

    /*����в�����noReplyConditionTime���������Ӧ������ı���, ����ʧ���򷵻�*/
    if (pSrc->OP_NoRepCondTime)
    {
        ulRslt = SSA_EncodeNoRepCondTime(pucContent + ucOffset, &ucTmpLen, (VOS_INT)pSrc->NoRepCondTime, IMPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeRegisterSSReq:WARNING:SSA_EncodeNoRepCondTime encode failure");
            return ulRslt;
        }
        /*IMPLICITģʽ�£���ͷ�����з�װ*/
        ulRslt = SSA_PackTL(0x85, pucContent + ucOffset , &ucTmpLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeRegisterSSReq:WARNING:NoRepCondTime: Tag Length encode encode failure");
            return ulRslt;
        }
        /*����ƫ��ֵ*/
        ucOffset = ucOffset + ucTmpLen;
    }


    /*����в�����defaultPriority���������Ӧ������ı���, ����ʧ���򷵻�*/
    if (pSrc->OP_DefaultPrio)
    {
        ulRslt = SSA_EncodeDefaultPriority(pucContent + ucOffset, &ucTmpLen, (VOS_INT)pSrc->DefaultPrio, IMPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeRegisterSSReq:WARNING:WARNING:SSA_EncodeDefaultPriority encode failure");
            return ulRslt;
        }
        /*IMPLICITģʽ�£���ͷ�����з�װ*/
        ulRslt = SSA_PackTL(0x87, pucContent + ucOffset , &ucTmpLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeRegisterSSReq:WARNING:DefaultPrio: Tag Length encode encode failure");
            return ulRslt;
        }
        /*����ƫ��ֵ*/
        ucOffset = ucOffset + ucTmpLen;
    }

    /*����в�����nbrUser���������Ӧ������ı���, ����ʧ���򷵻�*/
    if (pSrc->OP_NbrUser)
    {
        ulRslt = SSA_EncodeNbrUser(pucContent + ucOffset, &ucTmpLen, (VOS_INT)pSrc->NbrUser, IMPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeRegisterSSReq:WARNING:SSA_EncodeNbrUser encode failure");
            return ulRslt;
        }
        /*IMPLICITģʽ�£���ͷ�����з�װ*/
        ulRslt = SSA_PackTL(0x88, pucContent + ucOffset , &ucTmpLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeRegisterSSReq:WARNING:NbrUser: Tag Length encode encode failure");
            return ulRslt;
        }
        /*����ƫ��ֵ*/
        ucOffset = ucOffset + ucTmpLen;
    }

    /*����в�����longFTN-Supported���������Ӧ������ı���, ����ʧ���򷵻�*/
    if (pSrc->OP_LongFTN_Supported)
    {
        /*ʹ��EXPLICITģʽ����ͷ�����з�װ��NULL����û���κ�����,ֻ��T��L,û��V*/
        ulRslt = SSA_EncodeNullType(0x89, pucContent + ucOffset , &ucTmpLen, EXPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeRegisterSSReq:WARNING:SSA_EncodeNullType encode failure");
            return ulRslt;
        }
        /*����ƫ��ֵ*/
        ucOffset = ucOffset + ucTmpLen;
    }


    /*���������ִ�����*/
    *pucCodeLen = ucOffset;
    /*���������Ľṹ��ͷ����װ*/
    ulRslt = SSA_PackTL(0x30 , pucContent, pucCodeLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeRegisterSSReq:WARNING:RegisterSSReq: Tag Length encode encode failure");
        return ulRslt;
    }

    return SSA_SUCCESS;

}

/*****************************************************************************
 Prototype      : SSA_EncodeEraseSSReq
 Description    : ��MS�����EraseSS������facility���ݽ��б���
 Input          : *pSrc--����ǰ�����ݽṹ
 Output         : *pucContent--�������ִ�   *pucCodeLen--�ִ��ĳ���
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_EncodeEraseSSReq(VOS_UINT8   *pucContent, VOS_UINT8  *pucCodeLen, TAF_SS_ERASESS_REQ_STRU *pSrc)
{
    VOS_UINT8           ucTmpLen = 0;              /*��¼ÿ��������ı��볤��,��ʼֵΪ0*/
    VOS_UINT8           ucOffset = 0;
    VOS_UINT32          ulRslt;

    gpucSsEncodeEndLocation = pucContent + MAX_FACILITY_LEN;

    /*�Բ�����ss-Code���б���*/
    ulRslt = SSA_EncodeSsCode(pucContent + ucOffset, &ucTmpLen, &(pSrc->SsCode), EXPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeEraseSSReq:WARNING:SSA_EncodeSsCode encode failure");
        return ulRslt;
    }
    /*����ƫ��ֵ*/
    ucOffset = ucOffset + ucTmpLen;

    /*����в�����basicService���������Ӧ������ı���*/
    if (pSrc->OP_BsService)
    {
        ulRslt = SSA_EncodeBasicService(pucContent + ucOffset, &ucTmpLen, &(pSrc->BsService), EXPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeEraseSSReq:WARNING:SSA_EncodeBasicService encode failure");
            return ulRslt;
        }
        /*����ƫ��ֵ*/
        ucOffset = ucOffset + ucTmpLen;
    }

    /*����в�����longFTN-Supported���������Ӧ������ı���*/
    if (pSrc->OP_LongFTN_Supported)
    {
        /*ʹ��EXPLICITģʽ����ͷ�����з�װ��NULL����û���κ�����*/
        ulRslt = SSA_EncodeNullType(0x84, pucContent + ucOffset , &ucTmpLen, EXPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeEraseSSReq:WARNING:SSA_EncodeNullType encode failure");
            return ulRslt;
        }
        /*����ƫ��ֵ*/
        ucOffset = ucOffset + ucTmpLen;
    }

    /*���������ִ�����*/
    *pucCodeLen = ucOffset;
    /*���������Ľṹ��ͷ����װ*/
    ulRslt = SSA_PackTL(0x30 , pucContent, pucCodeLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeEraseSSReq:WARNING:EraseSSReq: Tag Length encode encode failure");
        return ulRslt;
    }

    return SSA_SUCCESS;

}

/*****************************************************************************
 Prototype      : SSA_EncodeActivateSSReq
 Description    : ��MS�����ActivateSS������facility���ݽ��б���
 Input          : *pSrc--����ǰ�����ݽṹ
 Output         : *pucContent--�������ִ�   *pucCodeLen--�ִ��ĳ���
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_EncodeActivateSSReq(VOS_UINT8   *pucContent, VOS_UINT8  *pucCodeLen, TAF_SS_ACTIVATESS_REQ_STRU *pSrc)
{
    VOS_UINT32          ulRslt;

    /*ActivateSS�����Ĳ�����EraseSS������ͬ*/
    ulRslt = SSA_EncodeEraseSSReq(pucContent, pucCodeLen, pSrc);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeActivateSSReq:WARNING:encode ActivateSS failure");
    }

    return ulRslt;

}

/*****************************************************************************
 Prototype      : SSA_EncodeDeativateSSReq
 Description    : ��MS�����DeactivateSS������facility���ݽ��б���
 Input          : *pSrc--����ǰ�����ݽṹ
 Output         : *pucContent--�������ִ�   *pucCodeLen--�ִ��ĳ���
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_EncodeDeactivateSSReq(VOS_UINT8   *pucContent, VOS_UINT8  *pucCodeLen, TAF_SS_DEACTIVATESS_REQ_STRU *pSrc)
{
    VOS_UINT32          ulRslt;

    /*DeactivateSS�����Ĳ�����EraseSS������ͬ*/
    ulRslt = SSA_EncodeEraseSSReq(pucContent, pucCodeLen, pSrc);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeDeactivateSSReq:WARNING:encode DeactivateSS failure");
    }

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_EncodeInterrogateSsReq
 Description    : ��MS�����InterrogateSS������facility���ݽ��б���
 Input          : *pSrc--����ǰ�����ݽṹ
 Output         : *pucContent--�������ִ�   *pucCodeLen--�ִ��ĳ���
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_EncodeInterrogateSsReq(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, TAF_SS_INTERROGATESS_REQ_STRU *pSrc)
{
    VOS_UINT32          ulRslt;

    /*InterrogateSS�����Ĳ�����EraseSS������ͬ*/
    ulRslt = SSA_EncodeEraseSSReq(pucContent, pucCodeLen, pSrc);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeInterrogateSsReq:WARNING:encode InterrogateSS failure");
    }

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_EncodeRegPwdReq
 Description    : ��MS�����RegisterPassword������facility���ݽ��б���
 Input          : *pSrc--����ǰ�����ݽṹ
 Output         : *pucContent--�������ִ�   *pucCodeLen--�ִ��ĳ���
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_EncodeRegPwdReq(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, TAF_SS_REGPWD_REQ_STRU *pSrc)
{
    VOS_UINT8           ucTmpLen = 0;          /*��¼ÿ��������ı��볤��,��ʼֵΪ0*/
    VOS_UINT8           ucOffset = 0;
    VOS_UINT32          ulRslt;

    gpucSsEncodeEndLocation = pucContent + MAX_FACILITY_LEN;

    /*�Բ�����ss-Code���б���*/
    ulRslt = SSA_EncodeSsCode(pucContent + ucOffset, &ucTmpLen, &(pSrc->SsCode), EXPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeRegPwdReq:WARNING:SSA_EncodeSsCode encode failure");
        return ulRslt;
    }
    /*����ƫ��ֵ*/
    ucOffset = ucOffset + ucTmpLen;

    /*���������ִ�����*/
    *pucCodeLen = ucOffset;

    return SSA_SUCCESS;
}

/*****************************************************************************
 Prototype      : SSA_EncodeGetPwdRsp
 Description    : ��MS�����GetPassword������facility���ݽ��б���
 Input          : *pSrc--����ǰ�����ݽṹ
 Output         : *pucContent--�������ִ�   *pucCodeLen--�ִ��ĳ���
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_EncodeGetPwdRsp(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, TAF_SS_GETPWD_RSP_STRU *pSrc)
{
    VOS_UINT8           ucTmpLen = 0;              /*��¼ÿ��������ı��볤��,��ʼֵΪ0*/
    VOS_UINT8           ucOffset = 0;
    VOS_UINT32          ulRslt;

    gpucSsEncodeEndLocation = pucContent + MAX_FACILITY_LEN;

    /*�Բ�����currentPassword(NumericString����)���б���*/
    ulRslt = SSA_EncodeNumericString(pucContent + ucOffset, &ucTmpLen, pSrc->aucPwdStr, TAF_SS_MAX_PASSWORD_LEN, EXPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeGetPwdRsp:WARNING:SSA_EncodeNumericString encode failure");
        return ulRslt;
    }
    /*����ƫ��ֵ*/
    ucOffset = ucOffset + ucTmpLen;

    /*���������ִ�����*/
    *pucCodeLen = ucOffset;

    return SSA_SUCCESS;

}


VOS_UINT32  SSA_EncodeProcessUntructuredSSReq(
    VOS_UINT8                          *pucContent,
    VOS_UINT8                          *pucCodeLen,
    VOS_UINT8                           ucTi
)
{
    /*��¼ÿ��������ı��볤��,��ʼֵΪ0*/
    VOS_UINT8                           ucTmpLen;
    VOS_UINT8                           ucOffset;
    VOS_UINT32                          ulRslt;
    MN_MSG_CBDCS_CODE_STRU              stDcsInfo;

    ucTmpLen                = 0;
    ucOffset                = 0;
    gpucSsEncodeEndLocation = pucContent + MAX_FACILITY_LEN;

    /*�Բ�����ussd-DataCodingScheme���б���*/
    ulRslt = SSA_EncodeUssdDataCodingScheme(pucContent + ucOffset,
                                            &ucTmpLen,
                                            &gastSsaStatetable[ucTi].DatacodingScheme,
                                            EXPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*����ƫ��ֵ*/
    ucOffset = ucOffset + ucTmpLen;

    /*
    ��APP���ִ����ݱ��뷽��,���б���,����GSM02.90���������ƶ�̨����Ĳ����У���D
    CS�����趨Ϊ "Language Unspecified"��"Default alphabet"������GSM03.38�����
    ��ΪOXOF��������Ϊ0000 1111��
    */
    PS_MEM_SET(&stDcsInfo, 0, sizeof(stDcsInfo));
    ulRslt = MN_MSG_DecodeCbsDcs(gastSsaStatetable[ucTi].DatacodingScheme,
                                 gastSsaStatetable[ucTi].pstUssdBuf->aucUssdStr,
                                 gastSsaStatetable[ucTi].pstUssdBuf->usCnt,
                                 &stDcsInfo);
    if (MN_ERR_NO_ERROR != ulRslt)
    {
        stDcsInfo.enMsgCoding = MN_MSG_MSG_CODING_7_BIT;
    }

    if (MN_MSG_MSG_CODING_7_BIT == stDcsInfo.enMsgCoding)
    {
        if(AT_USSD_NON_TRAN_MODE == SSA_GetUssdTransMode())
        {
            ulRslt = TAF_MmiEncodeUssdMessage(gastSsaStatetable[ucTi].pstUssdBuf);
            if (VOS_FALSE == ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_EncodeProcessUntructuredSSReq:WARNING:SSA_EncodeUssdMessage encode failure");
                return SSA_PARA_ERROR;
            }
        }
        else
        {
            ulRslt = TAF_STD_AsciiNum2HexString(gastSsaStatetable[ucTi].pstUssdBuf->aucUssdStr,
                                               &(gastSsaStatetable[ucTi].pstUssdBuf->usCnt));

            if (VOS_FALSE == ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_EncodeProcessUntructuredSSReq:WARNING:SSA_AsciiNum2HexString encode failure");
                return SSA_PARA_ERROR;
            }
        }
    }
    else
    {
        if (gastSsaStatetable[ucTi].pstUssdBuf->usCnt > TAF_SS_MAX_USS_CHAR)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeProcessUntructuredSSReq:WARNING:String too Long failure");
            return SSA_PARA_ERROR;
        }
    }

    /*�Բ�����ussd-String���б���*/
    ulRslt = SSA_EncodeUssdString(pucContent + ucOffset, &ucTmpLen, gastSsaStatetable[ucTi].pstUssdBuf, EXPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeProcessUntructuredSSReq:WARNING:SSA_EncodeUssdString encode failure");
        return ulRslt;
    }

    /*����ƫ��ֵ*/
    ucOffset = ucOffset + ucTmpLen;

    /*����в�����alertingPattern���������Ӧ������ı���*/
    if (gastSsaStatetable[ucTi].OP_AlertingPattern)
    {
        ulRslt = SSA_EncodeAlertingPattern(pucContent + ucOffset, &ucTmpLen, &(gastSsaStatetable[ucTi].AlertingPattern), EXPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeProcessUntructuredSSReq:WARNING:SSA_EncodeAlertingPattern encode failure");
            return ulRslt;
        }

        /*����ƫ��ֵ*/
        ucOffset = ucOffset + ucTmpLen;
    }

    /*����в�����msisdn���������Ӧ������ı���*/
    if (gastSsaStatetable[ucTi].OP_Msisdn)
    {
        ulRslt = SSA_EncodeMsisdn(pucContent + ucOffset, &ucTmpLen, gastSsaStatetable[ucTi].aucMsisdn, IMPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeProcessUntructuredSSReq:WARNING:SSA_EncodeMsisdn encode failure");
            return ulRslt;
        }

        /*��Ϊ��IMPLICITģʽ����ͷ�����з�װ*/
        ulRslt = SSA_PackTL(0x80, pucContent + ucOffset, &ucTmpLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeProcessUntructuredSSReq:WARNING:Msisdn: Tag Length encode failure");
            return ulRslt;
        }

        /*����ƫ��ֵ*/
        ucOffset = ucOffset + ucTmpLen;
    }

    /*���������ִ�����*/
    *pucCodeLen = ucOffset;
    /*���������Ľṹ��ͷ����װ*/
    ulRslt = SSA_PackTL(0x30 , pucContent, pucCodeLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeProcessUntructuredSSReq:WARNING:ProcessUntructuredSS: Tag Length encode failure");
        return ulRslt;
    }
    return SSA_SUCCESS;
}

/*****************************************************************************
 Prototype      : SSA_EncodeUssData
 Description    : ��MS�����ProcessUntructuredSS������facility���ݽ��б���
 Input          : *pSrc--����ǰ�����ݽṹ
 Output         : *pucContent--�������ִ�   *pucCodeLen--�ִ��ĳ���
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2007-01-22
    Author      : ---
    Modification: Created function for A32D08448
*****************************************************************************/
VOS_UINT32  SSA_EncodeUssData(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, TAF_SS_PROCESS_USSDATA_REQ_STRU *pSrc)
{
    VOS_UINT8           ucTmpLen = 0;          /*��¼ÿ��������ı��볤��,��ʼֵΪ0*/
    VOS_UINT8           ucOffset = 0;
    VOS_UINT32          ulRslt;

    gpucSsEncodeEndLocation = pucContent + MAX_FACILITY_LEN;

    /*�Բ�����ussd-DataCodingScheme���б���*/
    ulRslt = SSA_EncodeIa5String(pucContent + ucOffset, &ucTmpLen, pSrc->aucUserData, pSrc->ucCnt, IMPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*��Ϊ��IMPLICITģʽ����ͷ�����з�װ*/
    ulRslt = SSA_PackTL(IA5STRING_TAG, pucContent + ucOffset, &ucTmpLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeProcessUntructuredSSReq:WARNING:Msisdn: Tag Length encode failure");
        return ulRslt;
    }
    /*����ƫ��ֵ*/
    ucOffset = ucOffset + ucTmpLen;

    /*���������ִ�����*/
    *pucCodeLen = ucOffset;


    return SSA_SUCCESS;
}
VOS_UINT32  SSA_EncodeUntructuredSSRsp(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, TAF_SS_USS_RSP_STRU *pSrc)
{
    VOS_UINT8                           ucTmpLen = 0;              /*��¼ÿ��������ı��볤��,��ʼֵΪ0*/
    VOS_UINT8                           ucOffset = 0;
    VOS_UINT32                          ulRslt;
    MN_MSG_CBDCS_CODE_STRU              stDcsInfo;

    gpucSsEncodeEndLocation = pucContent + MAX_FACILITY_LEN;

    /*�Բ�����ussd-DataCodingScheme���б���*/
    ulRslt = SSA_EncodeUssdDataCodingScheme(pucContent + ucOffset, &ucTmpLen, &(pSrc->DataCodeScheme), EXPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeUntructuredSSRsp:WARNING:SSA_EncodeUssdDataCodingScheme encode failure");
        return ulRslt;
    }
    /*����ƫ��ֵ*/
    ucOffset = ucOffset + ucTmpLen;

    /*�Բ�����ussd-String���б���*/
    /*
    ��APP���ִ����ݱ��뷽��,���б���,����GSM02.90���������ƶ�̨����Ĳ����У���D
    CS�����趨Ϊ "Language Unspecified"��"Default alphabet"������GSM03.38�����
    ��ΪOXOF��������Ϊ0000 1111��
    */
    PS_MEM_SET(&stDcsInfo, 0, sizeof(stDcsInfo));
    ulRslt = MN_MSG_DecodeCbsDcs(pSrc->DataCodeScheme,
                                 pSrc->UssdStr.aucUssdStr,
                                 pSrc->UssdStr.usCnt,
                                &stDcsInfo);
    if (MN_ERR_NO_ERROR != ulRslt)
    {
        stDcsInfo.enMsgCoding = MN_MSG_MSG_CODING_7_BIT;
    }

    if (MN_MSG_MSG_CODING_7_BIT == stDcsInfo.enMsgCoding)
    {
        if (AT_USSD_NON_TRAN_MODE == SSA_GetUssdTransMode())
        {
            ulRslt = TAF_MmiEncodeUssdMessage(&(pSrc->UssdStr));

            if (VOS_FALSE == ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_EncodeUntructuredSSRsp:WARNING:SSA_EncodeUssdMessage encode failure");
                return SSA_PARA_ERROR;
            }
        }
        else
        {
            ulRslt = TAF_STD_AsciiNum2HexString(pSrc->UssdStr.aucUssdStr, &(pSrc->UssdStr.usCnt));

            if (VOS_FALSE == ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_EncodeUntructuredSSRsp:WARNING:SSA_AsciiNum2HexString encode failure");
                return SSA_PARA_ERROR;
            }
        }
    }

    ulRslt = SSA_EncodeUssdString(pucContent + ucOffset, &ucTmpLen, &(pSrc->UssdStr), EXPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeUntructuredSSRsp:WARNING:SSA_EncodeUssdString encode failure");
        return ulRslt;
    }

    /*����ƫ��ֵ*/
    ucOffset = ucOffset + ucTmpLen;

     /*���������ִ�����*/
    *pucCodeLen = ucOffset;
    /*���������Ľṹ��ͷ����װ*/
    ulRslt = SSA_PackTL(0x30 , pucContent, pucCodeLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeUntructuredSSRsp:WARNING:UntructuredSSRsp: Tag Length encode failure");
        return ulRslt;
    }

    return SSA_SUCCESS;

}


/*****************************************************************************
 Prototype      : SSA_EncodeEraseCCEntryReq
 Description    : ��MS�����EraseCCEntry������facility���ݽ��б���
 Input          : *pSrc--����ǰ�����ݽṹ
 Output         : *pucContent--�������ִ�   *pucCodeLen--�ִ��ĳ���
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_EncodeEraseCCEntryReq(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, TAF_SS_ERASECC_ENTRY_REQ_STRU  *pSrc)
{
    VOS_UINT8           ucTmpLen = 0;              /*��¼ÿ��������ı��볤��,��ʼֵΪ0*/
    VOS_UINT8           ucOffset = 0;
    VOS_UINT32          ulRslt;

    gpucSsEncodeEndLocation = pucContent + MAX_FACILITY_LEN;

    /*�Բ�����ss-Code���б���*/
    ulRslt = SSA_EncodeSsCode(pucContent + ucOffset, &ucTmpLen, &(pSrc->SsCode), IMPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeEraseCCEntryReq:WARNING:SSA_EncodeSsCode encode failure");
        return ulRslt;
    }
    /*��Ϊ��IMPLICITģʽ����ͷ�����з�װ*/
    ulRslt = SSA_PackTL(0x80 , pucContent + ucOffset, &ucTmpLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeEraseCCEntryReq:WARNING:SsCode: Tag Length encode failure");
        return ulRslt;
    }

    /*����ƫ��ֵ*/
    ucOffset = ucOffset + ucTmpLen;

    /*����в�����ccbs-Indexs���������Ӧ������ı���*/
    if (pSrc->OP_CcbsIndex)
    {
        ulRslt = SSA_EncodeCcbsIndex(pucContent + ucOffset, &ucTmpLen, pSrc->CcbsIndex, IMPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeEraseCCEntryReq:WARNING:SSA_EncodeCcbsIndex encode failure");
            return ulRslt;
        }
        /*��Ϊ��IMPLICITģʽ����ͷ�����з�װ*/
        ulRslt = SSA_PackTL(0x81 , pucContent + ucOffset, &ucTmpLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeEraseCCEntryReq:WARNING:CcbsIndex: Tag Length encode failure");
            return ulRslt;
        }

        /*����ƫ��ֵ*/
        ucOffset = ucOffset + ucTmpLen;
    }

    /*���������ִ�����*/
    *pucCodeLen = ucOffset;
    /*���������Ľṹ��ͷ����װ*/
    ulRslt = SSA_PackTL(0x30 , pucContent, pucCodeLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeEraseCCEntryReq:WARNING:EraseCCEntry: Tag Length encode failure");
        return ulRslt;
    }

    return SSA_SUCCESS;

}

#if 0
/*****************************************************************************
 Prototype      : SSA_EncodeUnstructuredSSDataReq
 Description    : ��MS�����Process-UnstructuredSSData������facility���ݽ��б���
 Input          : *pSrc--����ǰ�����ݽṹ
 Output         : *pucContent--�������ִ�   *pucCodeLen--�ִ��ĳ���
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_EncodeProcessUSSDataReq(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, TAF_SS_PROCESS_USSDATA_REQ_STRU  *pSrc)
{
    VOS_UINT32          ulRslt;

    gpucSsEncodeEndLocation = pucContent + MAX_FACILITY_LEN;

    if (pSrc->ucCnt > TAF_SS_MAX_NUM_OF_USERDATA)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeProcessUSSDataReq:WARNING:StrLen too Long");
        return SSA_PARA_ERROR;
    }

    /*������ss-UserData(IA5String����)����*/
    ulRslt = SSA_EncodeIA5String(pucContent, pucCodeLen, pSrc->aucUserData, pSrc->ucCnt, EXPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeEraseCCEntryReq:WARNING:SSA_EncodeCcbsIndex encode failure");
        return ulRslt;
    }
    return SSA_SUCCESS;
}
#endif

/*****************************************************************************
 Prototype      : SSA_EncodeBasicService
 Description    : ����basicservice�ı��룬�μ�24.080 Annex A��ASN.1����
 Input          : *pSrc--����ǰ�����ݽṹ, ucTagMode -- ��ǩģʽ,EXPLICIT_MODE����IMPLICIT_MODE
 Output         : *pucContent--�������ִ�   *pucCodeLen--�ִ��ĳ���
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_EncodeBasicService(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, TAF_SS_BASIC_SERVICE_STRU  *pstSrc, TAG_MODE ucTagMode)
{
    VOS_UINT32      ulRslt;

    /*���ȳ�ʼ��Ϊ0*/
    *pucCodeLen = 0;

    switch (pstSrc->BsType)
    {
        /*bearerService����*/
        case TAF_SS_BEARER_SERVICE:
            ulRslt = SSA_EncodeBearerService(pucContent, pucCodeLen, &(pstSrc->BsServiceCode), IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_EncodeBasicService:WARNING:SSA_EncodeBearerService encode failure");
                return ulRslt;
            }
            ulRslt = SSA_PackTL(0x82, pucContent, pucCodeLen);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_EncodeBasicService:WARNING:bearerService Tag Length encode failure");
                return ulRslt;
            }

            break;

        /*teleservice����*/
        case TAF_SS_TELE_SERVICE:
            ulRslt = SSA_EncodeTeleService(pucContent, pucCodeLen, &(pstSrc->BsServiceCode), IMPLICIT_MODE);
            if (ulRslt != SSA_SUCCESS)
            {
                SSA_LOG(WARNING_PRINT, "SSA_EncodeBasicService:WARNING:SSA_EncodeTeleService encode failure");
                return ulRslt;
            }
            ulRslt = SSA_PackTL(0x83, pucContent, pucCodeLen);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_EncodeBasicService:WARNING:teleservice Tag Length encode failure");
                return ulRslt;
            }
            break;
        default:
            /*�����쳣����*/
            SSA_LOG(WARNING_PRINT, "SSA_EncodeBasicService:WARNING:Parameter Error!");
            return SSA_PARA_ERROR;
    }

    return SSA_SUCCESS;
}

/*****************************************************************************
 Prototype      : SSA_EncodeForwardedToNumber
 Description    : ����forwardedToNumber�ı��룬�μ�24.080 Annex A��ASN.1����
 Input          : *pSrc--����ǰ�����ݽṹ, ucTagMode -- ��ǩģʽ,EXPLICIT_MODE����IMPLICIT_MODE
 Output         : *pucContent--�������ִ�   *pucCodeLen--�ִ��ĳ���
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_EncodeForwardedToNumber(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, VOS_UINT8 ucNumType, VOS_UINT8 *pucFwdNum, TAG_MODE ucTagMode)
{
    VOS_UINT8       ucAscIItrLen;
    VOS_UINT8       ucBcdStrLen;
    VOS_UINT32      ulRslt;
    VOS_UINT8       aucStr[TAF_SS_MAX_ENCODE_FWD_TO_NUM_LEN];

    /*��ȡASCII���ַ����ĳ���*/
    ucAscIItrLen = (VOS_UINT8)VOS_StrLen((VOS_CHAR *)pucFwdNum);
    if (ucAscIItrLen > (TAF_SS_MAX_FORWARDED_TO_NUM_LEN - 1))
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeForwardedToNumber:WARNING: String too Long");
        return SSA_PARA_ERROR;
    }

    /*��numtype �� number ͳһ�ŵ�һ���ַ�����*/
    aucStr[0] = ucNumType;
    ulRslt = SSA_AsciiNumToBcdNum(pucFwdNum, ucAscIItrLen, aucStr + 1, &ucBcdStrLen, &(aucStr[0])); /*<==A32D10708*/
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeForwardedToNumber:WARNING: value is too large");
        return ulRslt;
    }

    /*�ַ�����BER����*/
    ulRslt = SSA_EncodeString(pucContent, pucCodeLen, aucStr, ucBcdStrLen + 1, ucTagMode);

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_EncodeForwardedToSubaddress
 Description    : ����forwardedToSubaddress�ı��룬�μ�24.080 Annex A��ASN.1����
 Input          : *pSrc--����ǰ�����ݽṹ, ucTagMode -- ��ǩģʽ,EXPLICIT_MODE����IMPLICIT_MODE
 Output         : *pucContent--�������ִ�   *pucCodeLen--�ִ��ĳ���
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_EncodeForwardedToSubaddress(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, VOS_UINT8 ucSubAddrType, VOS_UINT8  *paucFwdToSubAddr, TAG_MODE ucTagMode)
{
    VOS_UINT32      ulRslt;
    VOS_UINT8       ucStrLen;
    VOS_UINT8       aucStr[TAF_SS_MAX_ENCODE_FWD_TO_SUBADDR_LEN];

    /*����ַ���ͺ��ӵ�ַ���ִ��ϲ���һ���ַ�����*/
    ucStrLen = (VOS_UINT8)VOS_StrLen((VOS_CHAR *)paucFwdToSubAddr);
    if (ucStrLen > (TAF_SS_MAX_ENCODE_FWD_TO_SUBADDR_LEN - 1))
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeForwardedToSubaddress:WARNING: String too Long");
        return SSA_PARA_ERROR;
    }

    aucStr[0] = ucSubAddrType;
    PS_MEM_CPY(aucStr + 1, paucFwdToSubAddr, ucStrLen);

    /*�ַ�������*/
    ulRslt = SSA_EncodeString(pucContent, pucCodeLen, aucStr, ucStrLen + 1, ucTagMode);

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_EncodeUssdString
 Description    : �������ussd-String�μ�24.080��Annex A��ASN.1������
 Input          : *pSrc--����ǰ�����ݽṹ, ucTagMode -- ��ǩģʽ,EXPLICIT_MODE����IMPLICIT_MODE
 Output         : *pucContent--�������ִ�   *pucCodeLen--�ִ��ĳ���
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_EncodeUssdString(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, TAF_SS_USSD_STRING_STRU  *pSrc, TAG_MODE ucTagMode)
{
    VOS_UINT32   ulRslt;

    /*�ַ�������*/
    ulRslt = SSA_EncodeString(pucContent, pucCodeLen, pSrc->aucUssdStr, (VOS_UINT8)pSrc->usCnt, ucTagMode);

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_EncodeMsisdn
 Description    : �������msisdn�μ�24.080��Annex A��ASN.1������
 Input          : *pSrc--����ǰ�����ݽṹ, ucTagMode -- ��ǩģʽ,EXPLICIT_MODE����IMPLICIT_MODE
 Output         : *pucContent--�������ִ�   *pucCodeLen--�ִ��ĳ���
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_EncodeMsisdn(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, VOS_UINT8  *pucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT32   ulRslt;
    VOS_UINT8    ucStrLen;

    /*��ȡASCII���ַ����ĳ���*/
    ucStrLen = (VOS_UINT8)VOS_StrLen((VOS_CHAR *)pucSrc);
    if (ucStrLen > TAF_SS_MAX_MSISDN_LEN)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeMsisdn:WARNING: String too Long");
        return SSA_PARA_ERROR;
    }


    /*�ַ�������*/
    ulRslt = SSA_EncodeString(pucContent, pucCodeLen, pucSrc, ucStrLen, ucTagMode);

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_EncodeErrorCode
 Description    : �������Problem code��TLV,�μ�24.080�� Table 3.3������
 Input          : ucProblemCode -- problem Code��ֵ
 Output         : *pucContent -- �������ִ�,*pucCodeLen�������ִ�����
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID SSA_EncodeErrorCode(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, VOS_UINT16 usErrCode)
{
    VOS_UINT8    ucTmp[3];

    /*T��L��V��ֵ*/
    ucTmp[0] = ERROR_CODE_TAG;
    ucTmp[1] = 1;
    /*�ṩ��APP�Ĵ��������ֵ��ƫ��,��˻ظ�����������Ҫ������ඨ���ֵ*/
    if (usErrCode > TAF_SS_ERRCODE_OFFSET)
    {
        ucTmp[2] = (VOS_UINT8)(usErrCode - TAF_SS_ERRCODE_OFFSET);
    }

    /*�ڴ���λ����*/
    (VOS_VOID)memmove(pucContent + 3, pucContent, *pucCodeLen);
    (VOS_VOID)memcpy(pucContent, ucTmp, 3);
    *pucCodeLen += 3;
}


 /*****************************************************************************
 Prototype      : SSA_EncodeProblemCode
 Description    : �������Problem code��TLV,�μ�24.080�� Table 3.3������
 Input          : ucProblemCode -- problem Code��ֵ
 Output         : *pucContent -- �������ִ�,*pucCodeLen�������ִ�����
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID SSA_EncodeProblemCode(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, VOS_UINT8 ucProblemCode)
{
    VOS_UINT8    ucTmp[3];

    /*T��L��V��ֵ*/
    /*ProblemCode�ĸ�4λ������problem tag,��4λ�����˾���tag�µĴ�����*/
    ucTmp[0] = 0x80 + (ucProblemCode >> 4);
    ucTmp[1] = 1;
    ucTmp[2] = ucProblemCode & 0x0f;

    /*�ڴ���λ����*/
    (VOS_VOID)memmove(pucContent + 3, pucContent, *pucCodeLen);
    (VOS_VOID)memcpy(pucContent, ucTmp, 3);
    *pucCodeLen += 3;
}

 /*****************************************************************************
 Prototype      : SSA_EncodeOperationCode
 Description    : �������Operation code��TLV,�μ�24.080�� Table 3.3������
 Input          : ucOpCode--Operation Code��ֵ
 Output         : *pucContent--�������ִ�,*pucCodeLen�������ִ�����
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID SSA_EncodeOperationCode(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, VOS_UINT8 ucOpCode)
{
    VOS_UINT8    ucTmp[3];

    /*T��L��V��ֵ*/
    ucTmp[0] = OPERATION_CODE_TAG;
    ucTmp[1] = 1;
    ucTmp[2] = ucOpCode;

    /*�ڴ���λ����*/
    (VOS_VOID)memmove(pucContent + 3, pucContent, *pucCodeLen);
    (VOS_VOID)memcpy(pucContent, ucTmp, 3);
    *pucCodeLen += 3;
}

 /*****************************************************************************
 Prototype      : SSA_EncodeSequenceTag
 Description    : �������Sequence Tag��TL,�μ�24.080�� Table 3.3������
 Input          : *pucCodeLen--����ǰ���ִ�����
 Output         : *pucContent--�������ִ�,*pucCodeLen�������ִ�����
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID SSA_EncodeSequenceTag(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen)
{
    VOS_UINT8    ucTmp[3];

    /*T��L��V��ֵ*/
    ucTmp[0] = TAG_SS_OF_SEQUENCE;
    ucTmp[1] = *pucCodeLen;

    /*�ڴ���λ����*/
    (VOS_VOID)memmove(pucContent + 2, pucContent, *pucCodeLen);
    (VOS_VOID)memcpy(pucContent, ucTmp, 2);
    *pucCodeLen += 2;
}

/*****************************************************************************
 Prototype      : SSA_EncodeInvokeId
 Description    : �������Invoke Id��TLV,�μ�24.080��Table 3.3������
 Input          : ucInvokeId -- INVOKE ID��ֵ
 Output         : *pucContent--�������ִ�,*pucCodeLen�������ִ�����
 Return Value   : ��
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID SSA_EncodeInvokeId(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, VOS_UINT8 ucInvokeId)
{
    VOS_UINT8    ucTmp[3];

    /*T��L��V��ֵ*/
    ucTmp[0] = INVOKE_ID_TAG;
    ucTmp[1] = 1;
    ucTmp[2] = ucInvokeId;

    /*�ڴ���λ����*/
    (VOS_VOID)memmove(pucContent + 3, pucContent, *pucCodeLen);
    (VOS_VOID)memcpy(pucContent, ucTmp, 3);
    *pucCodeLen += 3;
}

/*****************************************************************************
 Prototype      : SSA_EncodeComponentType
 Description    : �������Component Type��TL,�μ�24.080��Table 3.3������
 Input          : ucComponentTag -- component type��ǩֵ
 Output         : *pucContent--�������ִ�,*pucCodeLen�������ִ�����
 Return Value   : ��
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID SSA_EncodeComponentType(VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, VOS_UINT8 ucComponentTag)
{
    VOS_UINT8    ucTmp[5];
    VOS_UINT8    ucheaderLen;

    /*T��L��ֵ*/
    ucTmp[0] = ucComponentTag;

    SSA_EncodeLength(*pucCodeLen, ucTmp + 1, &ucheaderLen);
    ucheaderLen ++;


    /*�ڴ���λ����*/
    (VOS_VOID)memmove(pucContent + ucheaderLen, pucContent, *pucCodeLen);
    (VOS_VOID)memcpy(pucContent, ucTmp, ucheaderLen);
    *pucCodeLen += ucheaderLen;

}

VOS_UINT32 SSA_AsciiNumToBcdNum(VOS_UINT8 *pucAsciiNum, VOS_UINT8 ucAsciiNumLen, VOS_UINT8 *pucBcdNum,
                                VOS_UINT8 *pucBcdNumLen, VOS_UINT8 *pucNewNumType)
{
    VOS_UINT32     i, k;
    VOS_UINT8     *pucTemp, ucNewAsciiNumLen;

    pucTemp = pucBcdNum;
    ucNewAsciiNumLen = ucAsciiNumLen;

    /*==>A32D10708*/
    if ('+' == *(pucAsciiNum))
    {
        /*remove the 1st character:'+' from the input number string*/
        (VOS_VOID)PS_MEM_MOVE(pucAsciiNum, pucAsciiNum + 1, ucNewAsciiNumLen - 1);
        ucNewAsciiNumLen--;

        /*change the number type to "international number"+"E.164"*/
        *pucNewNumType = SSA_NUM_TYPE_INT_E164;
    }
    /*<==A32D10708*/

    for (i = 0; i < ucNewAsciiNumLen; i++)
    {
        k = i % 2;

        /*ASCII NUMber  is  '0'~'9'*/
        if ((*(pucAsciiNum + i) >= 0x30) && (*(pucAsciiNum + i) <= 0x39))
        {
            if(k == 0)
            {
                *(pucTemp + (i/2)) = *(pucAsciiNum + i) - 0x30;
            }
            else
            {
                *(pucTemp + (i/2)) = (VOS_UINT8)(((VOS_UINT8)(*(pucAsciiNum + i) - 0x30) << 4) | *(pucTemp + (i/2)));
            }
        }
        else if('*' == *(pucAsciiNum + i))   /* the key is '*' */
        {
            if(k == 0)
            {
                *(pucTemp + (i/2)) = 0xa;
            }
            else
            {
                *(pucTemp + (i/2)) = (0xa << 4) | *(pucTemp + (i/2));
            }
        }
        else if('#' == *(pucAsciiNum + i))   /* the key is '#' */
        {
            if(k == 0)
            {
                *(pucTemp + (i/2)) = 0xb;
            }
            else
            {
                *(pucTemp + (i/2)) = (0xb << 4) | *(pucTemp + (i/2));
            }
        }
        else
        {
            TAF_PRINT( TAF_SSA, WARNING_PRINT, "SSA_AsciiNumToBcdNum:  The key is invalid" );
            return SSA_PARA_ERROR;
        }
    }

    *pucBcdNumLen = ucNewAsciiNumLen/2;

    if((ucNewAsciiNumLen % 2) == 1)
    {
        *(pucTemp + (ucNewAsciiNumLen / 2)) = 0xf0 | *(pucTemp + (ucNewAsciiNumLen / 2));
        (*pucBcdNumLen)++;
    }
    return SSA_SUCCESS;
}


/*****************************************************************************
*  Prototype       : SSA_Put7bits
*  Description     : ��������ֽڽ���7bit����
*  Input           : ulBitAddress  --- ��7Ϊ������bit���ĳ���ֵ
*                    ucChar        --- ������ֽ�
*  Output          : pucEncodedMsg --- ָ��7bit����ת����Ķ���Ϣ�ַ�����ָ��
*  Return Value    : SMT_FALSE     --- ʧ��
*                    SMT_TRUE      --- �ɹ�
*  Calls           :
*  Called By       : Smt_EncodeMessage
*
*  History         :
*  1. Date         : 2005-10-13
*     Author       : ۬����
*     Modification : Created function
*****************************************************************************/
VOS_UINT8 SSA_Put7bits( VOS_UINT8  *pucEncodedMsg,
                         VOS_UINT32  ulBitAddress,
                         VOS_UINT8   ucChar )
{
    VOS_UINT32    ulAddress;    /*����ֽڵ�ַ*/
    VOS_UINT32    ulOffset;     /*���λƫ��*/

    /*�������ĺϷ���*/
    if ( ucChar >= 128 )
    {
        return SSA_FAILURE;
    }

    /*������ֽڵ�ַ��λƫ��*/
    ulAddress = ulBitAddress / 8;
    ulOffset  = ulBitAddress % 8;

    /*����Ҫ������ַ��ֳ������֣��ֱ��������ڵ������ֽ�*/
    /*����һ���ֵ����ݱ���*/
    /*lint -e701*/
    pucEncodedMsg[ulAddress] |= (VOS_UINT8)( ucChar << ulOffset );
    /*lint +e701*/

    /*���λƫ��С��2����û�еڶ����ֵ����ݣ�ֱ�ӷ���*/
    if ( ulOffset < 2 )
    {
        return SSA_SUCCESS;
    }

    /*���ڶ����ֵ����ݱ���*/
    pucEncodedMsg[ulAddress + 1] |= ( ucChar >> ( 8 - ulOffset ) );

    return SSA_SUCCESS;
}



/*****************************************************************************
 Prototype      : SSA_Pack_TL
 Description    : ��װͷ����T����TL������Basetype.c�ļ��е�pack����
 Input          : ucTag--����ǰTag��ֵ,
 Output         : *pucContent--�������ִ�    *pucLen--�����ĳ���
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/

VOS_UINT32  SSA_PackTL(VOS_UINT8  ucTag,  VOS_UINT8   *pucContent,  VOS_UINT8 *pucCodeLen)
{
    VOS_UINT8    aucTmppool[5];
    VOS_UINT8    ucheaderLen;

    /*�ж�pucContent�Ƿ�ĵ�ַ�Ƿ��ںϷ��ķ�Χ��*/
    if (pucContent > gpucSsEncodeEndLocation)
    {
        SSA_LOG(WARNING_PRINT, "SSA_PackTL:WARNING:pucContent beyond mark");
        return SSA_PARA_ERROR;
    }

    /*�����ǰ��û�н����κεĲ����ı���,��������Ϊ0*/
    if (0 == *pucCodeLen)
    {
        *pucContent = ucTag;
        *(pucContent + 1) = 0;
        *pucCodeLen = 2;
        return SSA_SUCCESS;
    }


    aucTmppool[0] = ucTag;
    /*�Գ��Ƚ��б���*/
    SSA_EncodeLength(*pucCodeLen, aucTmppool + 1, &ucheaderLen);
    ucheaderLen ++;

    /*�ж�ucheaderLen�ĳ����Ƿ�С��4(��ǰ����̳���),С��4Ϊ����*/
    if (ucheaderLen > 4)
    {
        SSA_LOG(WARNING_PRINT, "SSA_PackTL:WARNING:Length is Wrong");
        return SSA_PARA_ERROR;
    }

    /*�Ե�ǰ�ִ�������λ(ΪTLԤ�����ռ�)�Ϳ���*/
    (VOS_VOID)VOS_MemMove(pucContent + ucheaderLen, pucContent, *pucCodeLen);
    PS_MEM_CPY(pucContent, aucTmppool, ucheaderLen);

    /*��ǰ�Ѿ�������ִ�����*/
    *pucCodeLen = ucheaderLen + *pucCodeLen;

    return SSA_SUCCESS;

}


/*****************************************************************************
 Prototype      : Encode_NumericString
 Description    : ����ͨ���ַ��������NumericString���͵�BER������ִ�
 Input          : *pucSrc--����ǰ���ַ���  ucSrcLen--�ַ�������
 Output         : *pcodeContent--�������ִ�   *pucCodeLen--�������ִ�����
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_EncodeNumericString(VOS_UINT8 *pucCodeContent, VOS_UINT8 *pucCodeLen, VOS_UINT8 *pucSrc, VOS_UINT8 ucSrcLen, TAG_MODE ucTagMode)
{
    VOS_UINT32      ulRslt;

    /*������Ӧ�Ľ��뺯��*/
    ulRslt = SSA_EncodeOtherString(NUMERICSTRING_TAG, pucCodeContent, pucCodeLen, pucSrc, ucSrcLen, ucTagMode);

    return ulRslt;
}


#if 0
/*****************************************************************************
 Prototype      : Encode_IA5String
 Description    : ����ͨ���ַ��������IA5String���͵�BER������ִ�
 Input          : *pucSrc--����ǰ���ַ���  ucSrcLen--�ַ�������
 Output         : *pcodeContent--�������ִ�   *pucCodeLen--�������ִ�����
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_EncodeIA5String(VOS_UINT8 *pucCodeContent, VOS_UINT8 *pucCodeLen, VOS_UINT8 *pucSrc, VOS_UINT8 ucSrcLen, TAG_MODE ucTagMode)
{
    VOS_UINT32      ulRslt;

    /*������Ӧ�Ľ��뺯��*/
    ulRslt = SSA_EncodeOtherString(IA5STRING_TAG, pucCodeContent, pucCodeLen, pucSrc, ucSrcLen, ucTagMode);

    return ulRslt;
}
#endif

/*****************************************************************************
 Prototype      : Encode_INT
 Description    : ��������ֵ���б���
 Input          : lSrc--����ǰ������ֵ, lMaxNum -- ������ֵ�����ֵ
 Output         : *pucContent--�������ִ�   *pucCodeLen--������ִ��ĳ���
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_EncodeInt(VOS_UINT8 *pucCodeContent, VOS_UINT8 *pucCodeLen, VOS_INT iSrc, VOS_INT iMaxNum, VOS_INT iMiniNum, TAG_MODE ucTagMode)
{
    VOS_UINT8   j = 0 , k = 0 ;
    VOS_UINT8   auctmpbuffer[sizeof(VOS_INT)];
    VOS_INT     Tmpvalue, Tmpint;
    VOS_UINT32  ulRslt;

    /*�ж�����������Ƿ񳬹����޶��ķ�Χ*/
    if ((iSrc > iMaxNum)||(iSrc < iMiniNum))
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeInt:WARNING: value is beyond range");
        return SSA_PARA_ERROR;
    }

    /*�жϵ�ǰ��ַ��û��Խ��*/
    if (pucCodeContent > gpucSsEncodeEndLocation)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeString:WARNING: beyond mark");
        return SSA_PARA_ERROR;
    }

    /*lint -e961*/
    /*���������������ֽڴ���*/
    Tmpvalue = iSrc;
    if (iSrc > 0)
    {
        while (Tmpvalue > 255)
        {
            auctmpbuffer[k++] = (VOS_UINT8)(Tmpvalue & 0x00ff);
            Tmpvalue = (VOS_UINT)Tmpvalue >> 8;
        }
        auctmpbuffer[k++] = (VOS_UINT8)(Tmpvalue & 0x00ff);
    }
    else
    {
        Tmpint = Tmpvalue;
        while (Tmpint < -255)
        {
            auctmpbuffer[k++] = (VOS_UINT8)(Tmpint & 0x00ff);
            Tmpint = (VOS_UINT)Tmpint >> 8;
        }
        auctmpbuffer[k++] = (VOS_UINT8)(Tmpint & 0x00ff);
    }


    if (Tmpvalue >= 0)
    {
        /*���bit��ֵΪ1ʱ,��֮ǰ�ټ�һ���ֽ�,���ֽڵ�ֵΪ0*/
        if ( (auctmpbuffer[k-1] & 0x80) == 0x80 )
        {
            auctmpbuffer[k++] = 0x00;
        }
    }
    else
    {
        if ( (auctmpbuffer[k-1] & 0x80) == 0x00 )
        {
            auctmpbuffer[k++] = 0xff;
        }
    }

    while (k > 0)
    {
        pucCodeContent[j++] = auctmpbuffer[k-1] ;
        k--;
    }
    /* pucCodeContent[j++] = auctmpbuffer[0]; */

    *pucCodeLen = j;
    /*lint +e961*/
    /*�����explicit mode��ǩ���룬��T��L���з�װ*/
    if (EXPLICIT_MODE == ucTagMode)
    {
        ulRslt = SSA_PackTL(INTEGER_TAG, pucCodeContent, pucCodeLen);
        if (ulRslt != SSA_SUCCESS)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeString:WARNING: Int:Tag Length Encode Error!");
            return ulRslt;
        }
    }

    return SSA_SUCCESS;
}

/*****************************************************************************
 Prototype      : Encode_String
 Description    : ���ַ��������Octet String���͵��ִ�
 Input          : *pSrc--����ǰ���ִ�   ucSrcLen--����ǰ���ַ�������
 Output         : *pContent--�������ִ�   *pucCodeLen--�������ִ�����
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_EncodeString(VOS_UINT8 *pucCodeContent, VOS_UINT8 *pucCodeLen, VOS_UINT8 *pucSrc, VOS_UINT8 ucSrcLen, TAG_MODE ucTagMode)
{
    VOS_UINT32  ulRslt;

    /*�жϵ�ǰ��ַ��û��Խ��*/
    if (pucCodeContent > gpucSsEncodeEndLocation)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeString:WARNING: beyond mark");
        return SSA_PARA_ERROR;
    }

    /*L��V��ֵ*/
    *pucCodeLen = ucSrcLen;
    PS_MEM_CPY(pucCodeContent, pucSrc, ucSrcLen);

    /*�����explicit mode��ǩ���룬��T��L���з�װ*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        ulRslt = SSA_PackTL(OCTETSTRING_TAG, pucCodeContent, pucCodeLen);
        if (ulRslt != SSA_SUCCESS)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeString:WARNING: Int:Tag Length Encode Error!");
            return ulRslt;
        }
    }
    return SSA_SUCCESS;
}




/*****************************************************************************
 Prototype      : Encode_Length
 Description    : ��֪TLV��L�ĳ��ȣ��������BER����
 Input          : ucSrcLen--����ǰ�ĳ���
 Output         : *pucCodeLen--�����ĳ��ȣ� *pucContent--�������ִ�
 Return Value   : ��
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID  SSA_EncodeLength(VOS_UINT8 ucSrcLen, VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen)
{
    /*����ֻ���������ֱ��뷽ʽ������ȷ���ȵı��뷽ʽû�в���*/
    /*�������ȷ������ʽ�Ķ̸�ʽ�����봦��*/
    if (ucSrcLen < 128)
    {
        /*L��V��ֵ*/
        *pucCodeLen = 1;
        *pucContent = ucSrcLen;
        return;
    }
    /*�������ȷ������ʽ�ĳ���ʽ,���봦��*/
    else
    {
        /*L��V��ֵ*/
        *pucCodeLen = 2;
        *pucContent = 0x81;
        *(pucContent + 1) = ucSrcLen;
        return;
    }

    /* return SSA_FAILURE; */

}


VOS_UINT32  SSA_EncodeOtherString(VOS_UINT8 ucTagNum, VOS_UINT8 *pucCodeContent, VOS_UINT8 *pucCodeLen, VOS_UINT8 *pSrc, VOS_UINT8 ucSrcLen, TAG_MODE ucTagMode)
{
    VOS_UINT32  ulRslt;

    /*�����ַ�������*/
    ulRslt = SSA_EncodeString(pucCodeContent, pucCodeLen, pSrc, ucSrcLen, IMPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeOtherString():WARNING:SSA_EncodeString Error!");
    }

    /*�����explicit mode��ǩ���룬��T��L���з�װ*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        ulRslt = SSA_PackTL(ucTagNum, pucCodeContent, pucCodeLen);
        if (ulRslt != SSA_SUCCESS)
        {
            SSA_LOG(WARNING_PRINT, "SSA_EncodeString:WARNING: Int:Tag Length Encode Error!");
            return ulRslt;
        }

    }

    return SSA_SUCCESS;
}

/*****************************************************************************
 Prototype      : Encode_NullType
 Description    : ��Encode_NullType����BER����
 Input          : ucTag--Tag��ֵ
 Output         : *pcodeContent--�������ִ�   *pucCodeLen--�������ִ�����
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_EncodeNullType(VOS_UINT8 ucTag, VOS_UINT8 *pucContent, VOS_UINT8 *pucCodeLen, TAG_MODE ucTagMode)
{
    /*�жϵ�ǰ��ַ��û��Խ��*/
    if (pucContent > gpucSsEncodeEndLocation)
    {
        SSA_LOG(WARNING_PRINT, "SSA_EncodeNullType:WARNING: beyond mark");
        return SSA_PARA_ERROR;
    }

    if (ucTagMode == IMPLICIT_MODE)
    {
        *pucCodeLen = 0;
    }
    else
    {
        *pucCodeLen = 2;
        *pucContent = ucTag;
        *(pucContent+1) = 0;
    }
    return SSA_SUCCESS;
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
