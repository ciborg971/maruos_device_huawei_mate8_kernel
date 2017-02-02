/******************************************************************************

                  ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasSndUsimm.c
  �� �� ��   : ����
  ��    ��   : h00313353
  ��������   : 2015��01��26��
  ����޸�   :
  ��������   : ����USIMM�ӿڵ�����ԭ����USIMM�ӿڷ�����Ϣ
               ��Ϊֱ����USIMMģ�鷢����Ϣ
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��01��26��
    ��    ��   : h00313353
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  ͷ�ļ�����
*****************************************************************************/
#include "NasMntn.h"
#include "NasUsimmApiMntn.h"
#include "NasSndUsimm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID PS_FILE_ID_NAS_SNDUSIMM_C

/*****************************************************************************
  ��������
*****************************************************************************/


/*****************************************************************************
  ��������
*****************************************************************************/
NAS_USIMM_SVLTE_TYPE_ENUM_UINT8         g_enSvlteSupportFlg = NAS_USIMM_SVLTE_TYPE_BUTT;

/*****************************************************************************
  ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  :NAS_SNDUSIMM_SetSvlteSupportFlag
 ��������  :����svlte�Ƿ�֧�ֱ�ʶ
 �������  :enSvlteSupportFlag - svlte�Ƿ�֧�ֵ�ֵ
 �������  :��
 �� �� ֵ  :��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1. ��    ��   : 2015��01��26��
    ��    ��   : h00313353
    �޸�����   : Create
*****************************************************************************/
VOS_VOID NAS_SNDUSIMM_SetSvlteSupportFlag(
    NAS_USIMM_SVLTE_TYPE_ENUM_UINT8     enSvlteSupportFlag
)
{
    g_enSvlteSupportFlg = enSvlteSupportFlag;

    return;
}

/*****************************************************************************
 �� �� ��  :NAS_SNDUSIMM_ReadSvlteSupportFlagNvim
 ��������  :��ȡsvlte�Ƿ�֧��nv
 �������  :��
 �������  :��
 �� �� ֵ  :��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1. ��    ��   : 2015��01��26��
     ��    ��   : h00313353
     �޸�����   : Create
*****************************************************************************/
VOS_VOID NAS_SNDUSIMM_ReadSvlteSupportFlagNvim(
    VOS_VOID
)
{
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    SVLTE_SUPPORT_FLAG_STRU             stSvlteSupportFlag;

    PS_MEM_SET(&stSvlteSupportFlag, 0x00, sizeof(stSvlteSupportFlag));

    /* ��NVʧ�� */
    if (NV_OK != NV_Read(en_NV_Item_SVLTE_FLAG,
                         &stSvlteSupportFlag,
                         sizeof(SVLTE_SUPPORT_FLAG_STRU)))
    {
        return;
    }

    if (VOS_TRUE == stSvlteSupportFlag.ucSvlteSupportFlag)
    {
        NAS_SNDUSIMM_SetSvlteSupportFlag(NAS_USIMM_SVLTE_TYPE_SUPPORT);

        return;
    }

    NAS_SNDUSIMM_SetSvlteSupportFlag(NAS_USIMM_SVLTE_TYPE_NOT_SUPPORT);
#endif

    NAS_INFO_LOG(WUEPS_PID_MMA, "NAS_SNDUSIMM_ReadSvlteSupportFlagNvim is Called.");

    return;
}

/*****************************************************************************
 �� �� ��  :NAS_SNDUSIMM_GetSvlteSupportFlag
 ��������  :��ȡsvlte�Ƿ�֧�ֱ�ʶ
 �������  :��
 �������  :��
 �� �� ֵ  :svlte�����Ƿ�֧�ֵ�ȡֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1. ��    ��   : 2015��01��26��
    ��    ��   : h00313353
    �޸�����   : Create
*****************************************************************************/
NAS_USIMM_SVLTE_TYPE_ENUM_UINT8 NAS_SNDUSIMM_GetSvlteSupportFlag(
    VOS_VOID
)
{
    return g_enSvlteSupportFlg;
}

/*****************************************************************************
 �� �� ��  :NAS_SNDUSIMM_IsSvlteSupported
 ��������  :��ȡ�Ƿ�֧��svlte����
 �������  :��
 �������  :��
 �� �� ֵ  :VOS_TRUE:֧��svlte
            VOS_FALSE:��֧��svlte
 ���ú���  :
 ��������  :
 �޸���ʷ       :
  1. ��    ��   : 2015��01��26��
     ��    ��   : h00313353
     �޸�����   : Create
*****************************************************************************/
VOS_UINT32 NAS_SNDUSIMM_IsSvlteSupported(
    VOS_VOID
)
{
    if (NAS_USIMM_SVLTE_TYPE_BUTT == NAS_SNDUSIMM_GetSvlteSupportFlag())
    {
        NAS_SNDUSIMM_ReadSvlteSupportFlagNvim();
    }

    if (NAS_USIMM_SVLTE_TYPE_SUPPORT == NAS_SNDUSIMM_GetSvlteSupportFlag())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_UINT32 NAS_SNDUSIMM_IsCdmaPid(
    VOS_UINT32                          ulSenderPid
)
{
    if (UEPS_PID_XSD == ulSenderPid)
    {
        return VOS_TRUE;
    }

    if (UEPS_PID_XREG == ulSenderPid)
    {
        return VOS_TRUE;
    }

    if (UEPS_PID_XCC == ulSenderPid)
    {
        return VOS_TRUE;
    }

    if (UEPS_PID_HSD == ulSenderPid)
    {
        return VOS_TRUE;
    }

    if (UEPS_PID_HSM == ulSenderPid)
    {
        return VOS_TRUE;
    }

    if (UEPS_PID_EHSM == ulSenderPid)
    {
        return VOS_TRUE;
    }

    if (UEPS_PID_HLU == ulSenderPid)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_UINT32 NAS_SNDUSIMM_IsModem0SupportC(VOS_VOID)
{
    PLATAFORM_RAT_CAPABILITY_STRU       stModem0PlatRat;
    VOS_UINT16                          i;

    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_Platform_RAT_CAP, &stModem0PlatRat,
                              sizeof(PLATAFORM_RAT_CAPABILITY_STRU)))
    {
        NAS_TRACE_HIGH("NAS_SNDUSIMM_IsModem0SupportC read NV en_NV_Item_Platform_RAT_CAP failed!\r\n");
        return VOS_FALSE;
    }

    for (i = 0; i < stModem0PlatRat.usRatNum; i++)
    {
        if (PLATFORM_RAT_1X == stModem0PlatRat.aenRatList[i])
        {
            return VOS_TRUE;
        }

        if (PLATFORM_RAT_HRPD == stModem0PlatRat.aenRatList[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
#endif


VOS_UINT32 NAS_SNDUSIMM_GetReceiverPid(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulModem0ReceiverID,
    VOS_UINT32                          ulModem1ReceiverID,
    VOS_UINT32                          ulModem2ReceiverID
)
{
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = 0;

    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        /* ���֧��Svlte������Modem0��Ӧ��ReceiverPid */
        return ulModem0ReceiverID;
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == NAS_SNDUSIMM_IsCdmaPid(ulSenderPid))
    {
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
        if (VOS_TRUE == NAS_SNDUSIMM_IsModem0SupportC())
        {
            return ulModem0ReceiverID;
        }
        else
        {
            return ulModem1ReceiverID;
        }
#else
        return ulModem0ReceiverID;
#endif
    }
#endif

    /* �����֧�֣�����SenderPid��ȡModemId */
    enModemId = VOS_GetModemIDFromPid(ulSenderPid);

    if (MODEM_ID_0 == enModemId)
    {
        return ulModem0ReceiverID;
    }

    if (MODEM_ID_1 == enModemId)
    {
        return ulModem1ReceiverID;
    }

    if (MODEM_ID_2 == enModemId)
    {
        return ulModem2ReceiverID;
    }

    return RECEIVERID_NOT_FOUND;
}

/*****************************************************************************
�� �� ��  :NAS_SndUsimmSetFileReq
��������  :�����ļ�������
�������  :ulSenderPid:���ͷ�Pid
           ulSendPara:͸������
           pstSetFileInfo:�ĵ�������Ϣ
�������  :��
�� �� ֵ  :USIMM_API_SUCCESS
           USIMM_API_WRONG_PARA
           USIMM_API_ALLOCMEM_FAILED
           USIMM_API_SENDMSG_FAILED
���ú���  :
��������  :
�޶���¼  :
1. ��    ��   : 2015��01��26��
   ��    ��   : h00313353
   �޸�����   : Create
*****************************************************************************/
VOS_UINT32 NAS_SndUsimmUpdateFileReq(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulSendPara,
    NAS_USIMM_UPDATEFILE_DATA_STRU     *pstSetFileInfo
)
{
    USIMM_UPDATEFILE_REQ_STRU          *pstMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_CHAR                           *pucFilePathStr  = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLength;
    VOS_UINT32                          ulPathLength;

    /* ��ʼ�� */
    ulReceiverPid   = 0;
    ulMsgLength     = 0;
    ulPathLength    = 0;

    /* ������� */
    if (VOS_NULL_PTR == pstSetFileInfo)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmUpdateFileReq: pstSetFileInfo Is NULL.");

        return USIMM_API_WRONG_PARA;
    }

    if ((pstSetFileInfo->ulEfLen > MAX_FILE_LENGTH)
        || (pstSetFileInfo->ulEfLen < MIN_FILE_LENGTH))
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmUpdateFileReq: File Length Not In [1,65535].");

        return USIMM_API_WRONG_PARA;
    }

    /* ��ȡReceiverPid */
    ulReceiverPid = NAS_SNDUSIMM_GetReceiverPid(ulSenderPid,
                                                I0_WUEPS_PID_USIM,
                                                I1_WUEPS_PID_USIM,
                                                I2_WUEPS_PID_USIM);
    if (RECEIVERID_NOT_FOUND == ulReceiverPid)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmUpdateFileReq: Get ReceiverPid Failed.");

        return USIMM_API_WRONG_PARA;
    }

    /* �ļ�Idת�ļ�·�� */
    if (VOS_OK != USIMM_ChangeDefFileToPath(pstSetFileInfo->usEfId, &pucFilePathStr))
    {
        return USIMM_API_WRONG_PARA;
    }

    /* �ļ�·�����ȱ��� */
    ulPathLength = VOS_StrLen(pucFilePathStr);
    if (0 == ulPathLength)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmUpdateFileReq: File Path Str Error.");

        return USIMM_API_WRONG_PARA;
    }


    /* ������Ϣ�ڴ沢��ʼ�� */
    ulMsgLength = (sizeof(USIMM_UPDATEFILE_REQ_STRU) - VOS_MSG_HEAD_LENGTH)
                + (pstSetFileInfo->ulEfLen - NAS_USIMM_UPDATEFILE_STRU_ARRAY_LENGTH * sizeof(VOS_UINT8));
    pstMsg = (USIMM_UPDATEFILE_REQ_STRU *)PS_ALLOC_MSG(ulSenderPid, ulMsgLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmUpdateFileReq: Allocate Msg Failed.");

        return USIMM_API_FAILED;
    }

    PS_MEM_SET(pstMsg, 0x00, ulMsgLength);

    /* ��д��Ϣͷ */
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = ulSenderPid;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = ulReceiverPid;
    pstMsg->stMsgHeader.ulLength        = ulMsgLength;
    pstMsg->stMsgHeader.enMsgName       = USIMM_UPDATEFILE_REQ;
    pstMsg->stMsgHeader.enAppType       = pstSetFileInfo->enAppType;
    pstMsg->stMsgHeader.ulSendPara      = ulSendPara;

    /* ��д��Ϣ�� */
    pstMsg->stFilePath.ulPathLen        = ulPathLength;
    PS_MEM_CPY(pstMsg->stFilePath.acPath, pucFilePathStr, pstMsg->stFilePath.ulPathLen + 1);
    pstMsg->usDataLen                   = (VOS_UINT16)pstSetFileInfo->ulEfLen;
    pstMsg->ucRecordNum                 = pstSetFileInfo->ucRecordNum;
    PS_MEM_CPY(pstMsg->aucContent, pstSetFileInfo->pucEfContent, pstSetFileInfo->ulEfLen);

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(ulSenderPid, pstMsg);

    return USIMM_API_SUCCESS;
}

/*****************************************************************************
�� �� ��  :NAS_SndUsimmGetFileReq
��������  :��ȡ�ļ�������
�������  :ulSenderPid:���ͷ�Pid
           ulSendPara:͸������
           pstSetFileInfo:��Ҫ��ȡ���ĵ���Ϣ
�������  :��
�� �� ֵ  :USIMM_API_SUCCESS
           USIMM_API_WRONG_PARA
           USIMM_API_ALLOCMEM_FAILED
           USIMM_API_SENDMSG_FAILED
���ú���  :
��������  :
�޶���¼  :
1. ��    ��   : 2015��01��26��
   ��    ��   : h00313353
   �޸�����   : Create
*****************************************************************************/
VOS_UINT32 NAS_SndUsimmReadFileReq(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulSendPara,
    NAS_USIMM_GETFILE_DATA_STRU        *pstGetFileInfo
)
{
    USIMM_READFILE_REQ_STRU            *pstMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_CHAR                           *pucFilePathStr  = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLength;
    VOS_UINT32                          ulPathLength;

    /* ��ʼ�� */
    ulReceiverPid   = 0;
    ulMsgLength     = 0;
    ulPathLength    = 0;

    /* ������� */
    if (VOS_NULL_PTR == pstGetFileInfo)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmGetAppFileReq: pstGetFileInfo Is NULL.");

        return USIMM_API_WRONG_PARA;
    }

    /* ��ȡReceiverPid */
    ulReceiverPid = NAS_SNDUSIMM_GetReceiverPid(ulSenderPid,
                                                I0_WUEPS_PID_USIM,
                                                I1_WUEPS_PID_USIM,
                                                I2_WUEPS_PID_USIM);
    if (RECEIVERID_NOT_FOUND == ulReceiverPid)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmGetAppFileReq: Get ReceiverPid Failed.");

        return USIMM_API_WRONG_PARA;
    }

    /* �ļ�Idת�ļ�·�� */
    if (VOS_OK != USIMM_ChangeDefFileToPath(pstGetFileInfo->usEfId, &pucFilePathStr))
    {
        return USIMM_API_WRONG_PARA;
    }

    /* �ļ�·�����ȱ��� */
    ulPathLength = VOS_StrLen(pucFilePathStr);
    if (0 == ulPathLength)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmUpdateFileReq: File Path Str Error.");

        return USIMM_API_WRONG_PARA;
    }

    /* ������Ϣ�ڴ沢��ʼ�� */
    ulMsgLength = sizeof(USIMM_READFILE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg = (USIMM_READFILE_REQ_STRU *)PS_ALLOC_MSG(ulSenderPid, ulMsgLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmGetAppFileReq: Allocate Msg Failed.");

        return USIMM_API_FAILED;
    }

    PS_MEM_SET(pstMsg, 0x00, ulMsgLength);

    /* ��д��Ϣͷ */
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = ulSenderPid;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = ulReceiverPid;
    pstMsg->stMsgHeader.ulLength        = ulMsgLength;
    pstMsg->stMsgHeader.enMsgName       = USIMM_READFILE_REQ;
    pstMsg->stMsgHeader.enAppType       = pstGetFileInfo->enAppType;
    pstMsg->stMsgHeader.ulSendPara      = ulSendPara;

    /* ��д��Ϣ�� */
    pstMsg->stFilePath.ulPathLen        = ulPathLength;
    pstMsg->bNeedReadCache              = VOS_TRUE;
    pstMsg->ucRecordNum                 = pstGetFileInfo->ucRecordNum;
    PS_MEM_CPY(pstMsg->stFilePath.acPath, pucFilePathStr, pstMsg->stFilePath.ulPathLen + 1);

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(ulSenderPid, pstMsg);

    return USIMM_API_SUCCESS;
}

/*****************************************************************************
�� �� ��  :NAS_SndUsimmAuthReq
��������  :��Ȩ������
�������  :ulSenderPid:���ͷ�Pid
           enAppType:Ӧ������
           pucAutn:��Ȩ����
�������  :��
�� �� ֵ  :USIMM_API_SUCCESS
           USIMM_API_WRONG_PARA
           USIMM_API_ALLOCMEM_FAILED
           USIMM_API_SENDMSG_FAILED
���ú���  :
��������  :
�޶���¼  :
1. ��    ��   : 2015��01��26��
   ��    ��   : h00313353
   �޸�����   : Create
*****************************************************************************/
VOS_UINT32 NAS_SndUsimmAuthReq(
    VOS_UINT32                          ulSenderPid,
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    NAS_USIMM_AUTH_DATA_STRU           *pstAuth,
    VOS_UINT8                           ucOpId
)
{
    USIMM_AUTHENTICATION_REQ_STRU      *pstMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulMsgLength;

    /* ��ʼ�� */
    ulReceiverPid   = 0;
    ulMsgLength     = 0;

    /* ������� */
    if (VOS_NULL_PTR == pstAuth)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmAuthReq: pstAuth Is NULL.");

        return USIMM_API_WRONG_PARA;
    }

    /* ��ȡReceiverPid */
    ulReceiverPid = NAS_SNDUSIMM_GetReceiverPid(ulSenderPid,
                                                I0_WUEPS_PID_USIM,
                                                I1_WUEPS_PID_USIM,
                                                I2_WUEPS_PID_USIM);
    if (RECEIVERID_NOT_FOUND == ulReceiverPid)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmAuthReq: Get ReceiverPid Failed.");

        return USIMM_API_WRONG_PARA;
    }

    /* ������Ϣ�ڴ沢��ʼ�� */
    ulMsgLength = sizeof(USIMM_AUTHENTICATION_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg = (USIMM_AUTHENTICATION_REQ_STRU *)PS_ALLOC_MSG(ulSenderPid, ulMsgLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmAuthReq: Allocate Msg Failed");

        return USIMM_API_FAILED;
    }

    PS_MEM_SET(pstMsg, 0x00, ulMsgLength);

    /* ��д��Ϣͷ */
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = ulSenderPid;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = ulReceiverPid;
    pstMsg->stMsgHeader.ulLength        = ulMsgLength;

    pstMsg->stMsgHeader.enMsgName       = USIMM_AUTHENTICATION_REQ;
    pstMsg->stMsgHeader.ulSendPara      = ucOpId;
    pstMsg->stMsgHeader.enAppType       = enAppType;

    /* ��д��Ϣ�� */

    pstMsg->enAuthType                  = pstAuth->enAuthType;
    PS_MEM_CPY(&(pstMsg->uAuth), &(pstAuth->unAuthPara), sizeof(pstAuth->unAuthPara));

    /* ����VOS����ԭ�� */
    PS_SEND_URGENT_MSG(ulSenderPid, pstMsg);

    return USIMM_API_SUCCESS;
}

/*****************************************************************************
�� �� ��  :NAS_SndUsimmPinReq
��������  :PIN������
�������  :ulSenderPid:������ID
           ucCmdType:��������
           ucPINType:PIN����
           pucOldPIN:PIN������
           pucNewPIN:��PIN������
�������  :��
�� �� ֵ  :USIMM_API_SUCCESS
           USIMM_API_WRONG_PARA
           USIMM_API_ALLOCMEM_FAILED
           USIMM_API_SENDMSG_FAILED
���ú���  :
��������  :
�޶���¼  :
1. ��    ��   : 2015��01��26��
   ��    ��   : h00313353
   �޸�����   : Create
*****************************************************************************/
VOS_UINT32 NAS_SndUsimmPinReq(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT8                           ucCmdType,
    VOS_UINT8                           ucPINType,
    VOS_UINT8                          *pucOldPIN,
    VOS_UINT8                          *pucNewPIN
)
{
    USIMM_PINHANDLE_REQ_STRU           *pstMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    VOS_UINT32                          ulMsgLength;

    /* ��ʼ�� */
    ulReceiverPid   = 0;
    enAppType       = USIMM_GUTL_APP;
    ulMsgLength     = 0;

    /* ������� */
    if (VOS_NULL_PTR == pucOldPIN)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmPinReq: pucOldPIN Is NULL.");

        return USIMM_API_WRONG_PARA;
    }

    /* ��ȡReceiverPid */
    ulReceiverPid = NAS_SNDUSIMM_GetReceiverPid(ulSenderPid,
                                                I0_WUEPS_PID_USIM,
                                                I1_WUEPS_PID_USIM,
                                                I2_WUEPS_PID_USIM);
    if (RECEIVERID_NOT_FOUND == ulReceiverPid)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmPinReq: Get ReceiverPid Failed.");

        return USIMM_API_WRONG_PARA;
    }

    /* ������Ϣ�ڴ沢��ʼ�� */
    ulMsgLength = sizeof(USIMM_PINHANDLE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg = (USIMM_PINHANDLE_REQ_STRU *)PS_ALLOC_MSG(ulSenderPid, ulMsgLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmPinReq: Allocate Msg Failed.");

        return USIMM_API_FAILED;
    }

    PS_MEM_SET(pstMsg, 0x00, ulMsgLength);

    /* ��д��Ϣͷ */
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = ulSenderPid;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = ulReceiverPid;
    pstMsg->stMsgHeader.ulLength        = ulMsgLength;

    pstMsg->stMsgHeader.enMsgName       = USIMM_PINHANDLE_REQ;
    pstMsg->stMsgHeader.enAppType       = enAppType;
    pstMsg->stMsgHeader.ulSendPara      = 0;            /* Ԥ������ */

    /* ��д��Ϣ�� */
    pstMsg->enCmdType                   = ucCmdType;
    pstMsg->enPINType                   = ucPINType;
    PS_MEM_CPY(pstMsg->aucOldPIN, pucOldPIN, USIMM_PINNUMBER_LEN);

    if (VOS_NULL_PTR != pucNewPIN)
    {
        PS_MEM_CPY(pstMsg->aucNewPIN, pucNewPIN, USIMM_PINNUMBER_LEN);
    }

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(ulSenderPid, pstMsg);

    return USIMM_API_SUCCESS;
}

/*****************************************************************************
�� �� ��  :NAS_SndUsimmFdnNumCheckReq
��������  :�ṩ��NAS����FDN�������API
�������  :ulPid������FDN�����������Pid
           ulClientId:����ʶ��TAF Pid�µĸ�ҵ��ģ��
�������  :��
�� �� ֵ  : 0:��Ч��1:��Ч
�޶���¼  :
1. ��    ��   : 2015��01��26��
   ��    ��   : h00313353
   �޸�����   : Create
*****************************************************************************/
VOS_UINT32 NAS_SndUsimmFdnNumCheckReq(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulContextIndex,
    VOS_UINT32                          ulSendPara,
    SI_PB_FDN_NUM_STRU                 *pstFdnInfo
)
{
    SI_PB_FDN_CHECK_REQ_STRU           *pstMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulMsgLength;

    /* ��ʼ�� */
    ulReceiverPid   = 0;
    ulMsgLength     = 0;

    /* ������� */
    if (VOS_NULL_PTR == pstFdnInfo)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmFdnNumCheckReq: pstFdnInfo Is NULL.");

        return USIMM_API_WRONG_PARA;
    }

    /* ��ȡReceiverPid */
    ulReceiverPid = NAS_SNDUSIMM_GetReceiverPid(ulSenderPid,
                                                I0_MAPS_PB_PID,
                                                I1_MAPS_PB_PID,
                                                I2_MAPS_PB_PID);
    if (RECEIVERID_NOT_FOUND == ulReceiverPid)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmFdnNumCheckReq: Get ReceiverPid Failed.");

        return USIMM_API_WRONG_PARA;
    }

    /* ������Ϣ�ڴ沢��ʼ�� */
    ulMsgLength = sizeof(SI_PB_FDN_CHECK_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg = (SI_PB_FDN_CHECK_REQ_STRU *)PS_ALLOC_MSG(ulSenderPid, ulMsgLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmFdnNumCheckReq: Allocate Msg Failed.");

        return USIMM_API_FAILED;
    }

    PS_MEM_SET(pstMsg, 0x00, ulMsgLength);

    /* ��д��Ϣͷ */
    pstMsg->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid         = ulSenderPid;
    pstMsg->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid       = ulReceiverPid;
    pstMsg->ulLength            = ulMsgLength;

    /* ��д��Ϣ�� */
    pstMsg->ulMsgName           = SI_PB_FDN_CHECK_REQ;
    pstMsg->enAppType           = USIMM_GUTL_APP;
    pstMsg->ulSendPara          = ulSendPara;
    pstMsg->ulContextIndex      = ulContextIndex;
    PS_MEM_CPY(&(pstMsg->stFDNNum), pstFdnInfo, sizeof(SI_PB_FDN_NUM_STRU));

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(ulSenderPid, pstMsg);

    return USIMM_API_SUCCESS;
}

/*****************************************************************************
�� �� ��  :NAS_SndUsimmQueryFileReq
��������  :��ȡ�ļ�����¼����
�������  :ulSenderPid:������Pid
           usEfId:�ļ�ID
�������  :��
�� �� ֵ  :USIMM_API_SUCCESS
           USIMM_API_WRONG_PARA
           USIMM_API_ALLOCMEM_FAILED
           USIMM_API_SENDMSG_FAILED
���ú���  :
��������  :
�޶���¼  :
1. ��    ��   : 2015��01��26��
   ��    ��   : h00313353
   �޸�����   : Create
*****************************************************************************/
VOS_UINT32 NAS_SndUsimmQueryFileReq(
    VOS_UINT32                          ulSenderPid,
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT16                          usEFid
)
{
    USIMM_QUERYFILE_REQ_STRU           *pstMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;
    VOS_CHAR                           *pucFilePathStr  = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLength;
    VOS_UINT32                          ulPathLength;

    /* ��ʼ�� */
    ulReceiverPid   = 0;
    ulMsgLength     = 0;
    ulPathLength    = 0;

    /* ��ȡReceiverPid */
    ulReceiverPid = NAS_SNDUSIMM_GetReceiverPid(ulSenderPid,
                                                I0_WUEPS_PID_USIM,
                                                I1_WUEPS_PID_USIM,
                                                I2_WUEPS_PID_USIM);
    if (RECEIVERID_NOT_FOUND == ulReceiverPid)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmQueryFileReq: Get ReceiverPid Failed.");

        return USIMM_API_WRONG_PARA;
    }

    /* �ļ�Idת�ļ�·�� */
    if (VOS_OK != USIMM_ChangeDefFileToPath(usEFid, &pucFilePathStr))
    {
        return USIMM_API_WRONG_PARA;
    }

    /* �ļ�·�����ȱ��� */
    ulPathLength = VOS_StrLen(pucFilePathStr);
    if (0 == ulPathLength)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmUpdateFileReq: File Path Str Error.");

        return USIMM_API_WRONG_PARA;
    }

    /* ������Ϣ�ڴ沢��ʼ�� */
    ulMsgLength = sizeof(USIMM_QUERYFILE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg = (USIMM_QUERYFILE_REQ_STRU *)PS_ALLOC_MSG(ulSenderPid, ulMsgLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmQueryFileReq: Allocate Msg Failed.");

        return USIMM_API_FAILED;
    }

    PS_MEM_SET(pstMsg, 0x00, ulMsgLength);

    /* ��д��Ϣͷ */
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = ulSenderPid;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = ulReceiverPid;
    pstMsg->stMsgHeader.ulLength        = ulMsgLength;

    pstMsg->stMsgHeader.enMsgName       = USIMM_QUERYFILE_REQ;
    pstMsg->stMsgHeader.enAppType       = enAppType;
    pstMsg->stMsgHeader.ulSendPara      = 0;                /* Ԥ������ */

    /* ��д��Ϣ�� */
    pstMsg->stFilePath.ulPathLen        = ulPathLength;
    PS_MEM_CPY(pstMsg->stFilePath.acPath, pucFilePathStr, pstMsg->stFilePath.ulPathLen + 1);

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(ulSenderPid, pstMsg);

    return USIMM_API_SUCCESS;
}

/*****************************************************************************
�� �� ��  :NAS_SndUsimmDeactiveCardReq
��������  :SIM��ȥ��������
�������  :ulSenderPid:������Pid
�������  :��
�� �� ֵ  :VOS_TRUE
           VOS_FALSE
���ú���  :
��������  :
�޶���¼  :
1. ��    ��   : 2015��01��26��
   ��    ��   : h00313353
   �޸�����   : Create
*****************************************************************************/
VOS_UINT32 NAS_SndUsimmDeactiveCardReq(
    VOS_UINT32                          ulSenderPid
)
{
    USIMM_DEACTIVECARD_REQ_STRU        *pstMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLength;

    /* ��ʼ�� */
    ulMsgLength     = 0;

    /* ������Ϣ�ڴ沢��ʼ�� */
    ulMsgLength = sizeof(USIMM_DEACTIVECARD_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg = (USIMM_DEACTIVECARD_REQ_STRU *)PS_ALLOC_MSG(ulSenderPid, ulMsgLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmDeactiveCardReq: Allocate Msg Failed.");

        return USIMM_API_FAILED;
    }

    PS_MEM_SET(pstMsg, 0x00, ulMsgLength);

    /* ��д��Ϣͷ */
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = ulSenderPid;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulLength        = ulMsgLength;

    pstMsg->stMsgHeader.enMsgName       = USIMM_DEACTIVECARD_REQ;
    pstMsg->stMsgHeader.enAppType       = USIMM_GUTL_APP;
    pstMsg->stMsgHeader.ulSendPara      = 0;                /* Ԥ������ */

    /* ����VOS����ԭ�� */
    PS_SEND_URGENT_MSG(ulSenderPid, pstMsg);

    return USIMM_API_SUCCESS;
}

/*****************************************************************************
�� �� ��  :NAS_SndUsimmEcallNumberQry
��������  :�ṩ��NAS��ȡECALL(FDN/SDN)�������API
�������  :ulSenderPid������FDN�����������Pid
           enStorage:�洢������
           ucListLen:NASҪ��ȡ�ĺ����б�
           pucList:�б�����
�������  :��
�� �� ֵ  : 0:��Ч��1:��Ч
���ú���  :
��������  :
�޶���¼  :
1. ��    ��   : 2015��01��26��
   ��    ��   : h00313353
   �޸�����   : Create
*****************************************************************************/
VOS_UINT32 NAS_SndUsimmEcallNumberQry(
    VOS_UINT32                          ulSenderPid,
    SI_PB_STORAGE_ENUM_UINT32           enStorage,
    VOS_UINT8                           ucListLen,
    VOS_UINT8                          *pucList
)
{
    SI_PB_ECALLQRY_REQ_STRU            *pstMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLength;

    /* ��ʼ�� */
    ulMsgLength     = 0;

    /* ������� */
    if (VOS_NULL_PTR == pucList)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmEcallNumberQry: pucList Is NULL.");

        return USIMM_API_WRONG_PARA;
    }

    /* ������Ϣ�ڴ沢��ʼ�� */
    ulMsgLength = (sizeof(SI_PB_ECALLQRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH)
                    + (ucListLen - NAS_SI_PB_ECALLQRY_REQ_STRU_ARRAY_LENGTH * sizeof(VOS_UINT8));
    pstMsg = (SI_PB_ECALLQRY_REQ_STRU *)PS_ALLOC_MSG(ulSenderPid, ulMsgLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmEcallNumberQry: Allocate Msg Failed.");

        return USIMM_API_FAILED;
    }

    PS_MEM_SET(pstMsg, 0x00, ulMsgLength);

    /* ��д��Ϣͷ */
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = ulSenderPid;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = MAPS_PB_PID;
    pstMsg->ulLength        = ulMsgLength;

    /* ��д��Ϣ�� */
    pstMsg->ulMsgName       = SI_PB_ECALL_QRY_REQ;
    pstMsg->enAppType       = USIMM_GUTL_APP;
    pstMsg->enStorage       = enStorage;
    pstMsg->ucListLen       = ucListLen;
    PS_MEM_CPY(pstMsg->aucList, pucList, ucListLen);

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(ulSenderPid, pstMsg);

    return USIMM_API_SUCCESS;
}

/*****************************************************************************
�� �� ��  :NAS_SndUsimmEnvelopeDownloadReq
��������  :STK����ENVELOP���غ���,Э��ջTAFʹ��
�������  :ulSenderPid:������Pid
           ulSendPara:͸������
           pstENStru:Envelope����
�������  :��
�� �� ֵ  :SI_UINT32 ����ִ�н��
���ú���  :
��������  :
�޶���¼  :
1. ��    ��   : 2015��01��26��
   ��    ��   : h00313353
   �޸�����   : Create
*****************************************************************************/
VOS_UINT32 NAS_SndUsimmEnvelopeDownloadReq(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulSendPara,
    SI_STK_ENVELOPE_STRU               *pstENStru
)
{
    SI_STK_ENVELOPEDOWN_REQ_STRU       *pstMsg          = VOS_NULL_PTR;
    VOS_UINT8                           aucEvent[MAX_VALUE_OF_ONE_BYTE + 1];
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulMsgLength;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulOffSet;
    VOS_UINT32                          ulRslt;


    /* ��ʼ�� */
    ulReceiverPid   = 0;
    ulMsgLength     = 0;
    ulDataLen       = 0;
    ulOffSet        = 0;
    ulRslt          = 0;
    PS_MEM_SET(aucEvent, 0x00, sizeof(aucEvent));

    /* ������� */
    if (VOS_NULL_PTR == pstENStru)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmEnvelopeDownloadReq: pstENStru Is NULL.");

        return USIMM_API_WRONG_PARA;
    }

    /* ��ȡReceiverPid */
    ulReceiverPid = NAS_SNDUSIMM_GetReceiverPid(ulSenderPid,
                                                I0_MAPS_STK_PID,
                                                I1_MAPS_STK_PID,
                                                I2_MAPS_STK_PID);
    if (RECEIVERID_NOT_FOUND == ulReceiverPid)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmEnvelopeDownloadReq: Get ReceiverPid Failed.");

        return USIMM_API_WRONG_PARA;
    }

    /* Envelope ���ͼ�� */
    if ((SI_STK_ENVELOPE_MENUSEL == pstENStru->enEnvelopeType)
        || (SI_STK_PROCMD == pstENStru->enEnvelopeType))
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmEnvelopeDownloadReq: The Input EnvelopeType Is Error");

        return USIMM_API_FAILED;
    }

    /* �������±����ŵ������� */
    ulRslt = SI_STK_EnvelopeData_Code(pstENStru, &ulDataLen, aucEvent, &ulOffSet);

    NAS_LogStkApiEnvelopReqCode(ulRslt, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, aucEvent, ulDataLen, ulOffSet);

    if (VOS_ERR == ulRslt)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmEnvelopeDownloadReq: The SI_STK_EnvelopeData_Code Is Error");

        return USIMM_API_FAILED;
    }

    /* �����ⲿAPI��� */
    if (ulDataLen > SI_STK_DATA_MAX_LEN)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmEnvelopeDownloadReq: The SI_STK_EnvelopeData_Code ulDataLen > 256");

        return USIMM_API_FAILED;
    }

    /* ������Ϣ�ڴ沢��ʼ�� */
    ulMsgLength = sizeof(SI_STK_ENVELOPEDOWN_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg = (SI_STK_ENVELOPEDOWN_REQ_STRU *)PS_ALLOC_MSG(ulSenderPid, ulMsgLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmEnvelopeDownloadReq: Allocate Msg Failed.");

        return USIMM_API_FAILED;
    }

    PS_MEM_SET(pstMsg, 0x00, ulMsgLength);

    /* ��д��Ϣͷ */
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = ulReceiverPid;            /* USIMM Ҫ�����ϢSenderPid = ReceiverPid*/
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = ulReceiverPid;
    pstMsg->stMsgHeader.ulLength        = ulMsgLength;

    pstMsg->stMsgHeader.enMsgName       = SI_STK_ENVELOPEDWON_REQ;
    pstMsg->stMsgHeader.ulSendPara      = ulSendPara;
    pstMsg->stMsgHeader.ucOpID          = VOS_NULL;
    pstMsg->stMsgHeader.usATClient      = VOS_NULL;

    /* ��д��Ϣ�� */
    pstMsg->bTransFlag                  = NAS_SI_STK_ENVELOPEDOWN_ENCODE;
    pstMsg->enEnvelopeType              = pstENStru->enEnvelopeType;
    pstMsg->stEnvelopeData.ulDataLen    = ulDataLen;
    PS_MEM_CPY(pstMsg->stEnvelopeData.aucData, &aucEvent[ulOffSet], ulDataLen);

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(ulSenderPid, pstMsg);

    return USIMM_API_SUCCESS;
}

/*****************************************************************************
�� �� ��  :NAS_SndUsimmRestrictedAccessReq
��������  :
�������  :ulSenderPid:������Pid
           ulSendPara:͸������
           pstENStru:Envelope����
�������  :��
�� �� ֵ  :SI_UINT32 ����ִ�н��
���ú���  :
��������  :
�޶���¼  :
1. ��    ��   : 2015��01��26��
   ��    ��   : h00313353
   �޸�����   : Create
*****************************************************************************/
VOS_UINT32 NAS_SndUsimmRestrictedAccessReq(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulSendPara,
    USIMM_RACCESS_REQ_STRU             *pstData
)
{
    USIMM_RACCESS_REQ_STRU             *pstMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLength;

    /* ��ʼ�� */
    ulMsgLength     = 0;

    /* ������� */
    if (VOS_NULL_PTR == pstData)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmRestrictedAccessReq: pstENStru Is NULL.");

        return USIMM_API_WRONG_PARA;
    }

    /* ������Ϣ�ڴ沢��ʼ�� */
    ulMsgLength = sizeof(USIMM_RACCESS_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg = (USIMM_RACCESS_REQ_STRU *)PS_ALLOC_MSG(ulSenderPid, ulMsgLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmRestrictedAccessReq: Allocate Msg Failed.");

        return USIMM_API_FAILED;
    }

    PS_MEM_SET(pstMsg, 0x00, ulMsgLength);

    /* ��д��Ϣͷ */
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = ulSenderPid;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulLength        = ulMsgLength;

    pstMsg->stMsgHeader.enMsgName       = USIMM_RACCESS_REQ;
    pstMsg->stMsgHeader.ulSendPara      = ulSendPara;
    pstMsg->stMsgHeader.enAppType       = USIMM_GUTL_APP;

    /* ��д��Ϣ�� */
    pstMsg->enCmdType                   = pstData->enCmdType;
    pstMsg->ucP1                        = pstData->ucP1;
    pstMsg->ucP2                        = pstData->ucP2;
    pstMsg->ucP3                        = pstData->ucP3;
    pstMsg->usEfId                      = pstData->usEfId;

    /* �����ļ�·�� */
    pstMsg->usPathLen                   = ((pstData->usPathLen > USIMM_MAX_PATH_LEN)?\
                                          USIMM_MAX_PATH_LEN:pstData->usPathLen);

    /* �ļ�·��������U16Ϊ��λ�ģ�·�������ĳ���Ҫ��2 */
    PS_MEM_CPY(pstMsg->ausPath, pstData->ausPath, (pstMsg->usPathLen) * sizeof(VOS_UINT16));

    /* ����P3��������<DATA>�ֶ� */
    PS_MEM_CPY(pstMsg->aucContent, pstData->aucContent, pstData->ucP3);

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(ulSenderPid, pstMsg);

    return USIMM_API_SUCCESS;
}

/*****************************************************************************
�� �� ��  :NAS_SndUsimmRestrictedAccessReq
��������  :
�������  :ulSenderPid:������Pid
           ulSendPara:͸������
           pstENStru:Envelope����
�������  :��
�� �� ֵ  :SI_UINT32 ����ִ�н��
���ú���  :
��������  :
�޶���¼  :
1. ��    ��   : 2015��01��26��
   ��    ��   : h00313353
   �޸�����   : Create
*****************************************************************************/
VOS_UINT32 NAS_SndUsimmRefreshReq(
    VOS_UINT32                          ulSenderPid,
    USIMM_STK_COMMAND_DETAILS_STRU     *pstCMDDetail,
    USIMM_RESET_INFO_STRU              *pstRstInfo
)
{
    USIMM_STKREFRESH_REQ_STRU          *pstMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLength;

    /* ��ʼ�� */
    ulMsgLength     = 0;

    /* ������� */
    if (VOS_NULL_PTR == pstCMDDetail)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmRefreshReq: pstCMDDetail Is NULL.");

        return USIMM_API_WRONG_PARA;
    }

    if (VOS_NULL_PTR == pstRstInfo)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmRefreshReq: pstRstInfo Is NULL.");

        return USIMM_API_WRONG_PARA;
    }

    /* ������Ϣ�ڴ沢��ʼ�� */
    ulMsgLength = sizeof(USIMM_STKREFRESH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg = (USIMM_STKREFRESH_REQ_STRU *)PS_ALLOC_MSG(ulSenderPid, ulMsgLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(ulSenderPid, "NAS_SndUsimmRefreshReq: Allocate Msg Failed.");

        return USIMM_API_FAILED;
    }

    PS_MEM_SET(pstMsg, 0x00, ulMsgLength);

    /* ��д��Ϣͷ */
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = ulSenderPid;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulLength        = ulMsgLength;

    pstMsg->stMsgHeader.enMsgName       = USIMM_STKREFRESH_REQ;
    pstMsg->stMsgHeader.ulSendPara      = 0;
    pstMsg->stMsgHeader.enAppType       = USIMM_GUTL_APP;

    /* ��д��Ϣ�� */
    pstMsg->ulCommandNum                = pstCMDDetail->ucCommandNum;
    pstMsg->ulCommandType               = pstCMDDetail->ucCommandType;
    pstMsg->enRefreshType               = pstCMDDetail->ucCommandQua;

    if (USIMM_AID_LEN_MAX < pstRstInfo->usAidLen)
    {
        pstMsg->ulAidLen = USIMM_AID_LEN_MAX;
    }
    else
    {
        pstMsg->ulAidLen = pstRstInfo->usAidLen;
    }

    if (VOS_NULL != pstMsg->ulAidLen)
    {
        (VOS_VOID)VOS_MemCpy(pstMsg->aucAid, pstRstInfo->aucAid, pstMsg->ulAidLen);
    }

    pstMsg->usLen = pstRstInfo->usFileListLen;

    if (VOS_NULL != pstRstInfo->usFileListLen)
    {
        PS_MEM_CPY(pstMsg->aucFileList, pstRstInfo->aucFileList, pstRstInfo->usFileListLen);
    }

    /* ����VOS����ԭ�� */
    PS_SEND_MSG(ulSenderPid, pstMsg);

    return USIMM_API_SUCCESS;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

