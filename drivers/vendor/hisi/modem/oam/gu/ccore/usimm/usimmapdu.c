
#include "product_config.h"

#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)

#include "usimmapdu.h"
#include "usimmdl.h"
#include "usimmt1dl.h"
#include "usimmglobal.h"
#include "UsimPsInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_USIMM_APDUMODULE_C
/*lint +e767*/

VOS_UINT32 USIMM_UiccPinOperationResultProc(
    VOS_UINT8                           ucINS,
    VOS_UINT32                          ulResult)
{
    /* ICC��PIN��������SW״̬��������������DL���Ѿ������ */
    if (USIMM_PHYCARD_TYPE_ICC == USIMM_CCB_GetCardType())
    {
        return ulResult;
    }

    if (  (CMD_INS_VERIFY       == ucINS)
        ||(CMD_INS_DISABLE_PIN  == ucINS)
        ||(CMD_INS_CHANGE_PIN   == ucINS)
        ||(CMD_INS_ENABLE_PIN   == ucINS)
        ||(CMD_INS_UNBLOCK_PIN  == ucINS))
    {
        return USIMM_SW_CMD_REMAINTIME;
    }

    return ulResult;
}
VOS_UINT32 USIMM_CheckSW(
    VOS_UINT8                           ucINS,
    VOS_UINT8                           ucSW1,
    VOS_UINT8                           ucSW2)
{
    USIMM_SWCHECK_ST                   *pstSWCheck;
    VOS_UINT32                          ulLen;
    VOS_UINT32                          i;
    USIMM_SWCHECK_ENUM_UINT16           enResult = USIMM_SW_OTHER_ERROR;

    if (USIMM_PHYCARD_TYPE_ICC == USIMM_CCB_GetCardType())  /*���ݿ������ж�*/
    {
        pstSWCheck = gausSimSWCheck;

        ulLen      = USIMM_SIMSW_MAXNUMBER;
    }
    else
    {
        pstSWCheck = gausUsimSWCheck;

        ulLen      = USIMM_USIMSW_MAXNUMBER;
    }

    for(i=0; i<ulLen; i++)
    {
        if(pstSWCheck[i].ucSW1 != ucSW1)        /*���ж�SW1ƥ��*/
        {
            continue;
        }

        if((0xC0 == (ucSW2&0xF0))&&(0x63 == pstSWCheck[i].ucSW1))
        {
            /* ��DL�㷵�صĽ����״̬�ֻ�Ҫ���PIN����������ж� */
            enResult = (USIMM_SWCHECK_ENUM_UINT16)USIMM_UiccPinOperationResultProc(ucINS, 
                                                                            pstSWCheck[i].enResult);

            break;
        }

        if((0xFF == pstSWCheck[i].ucSW2)||(ucSW2 == pstSWCheck[i].ucSW2))/*����Ҫ�ж�SW2����SW2ƥ��*/
        {
            enResult = pstSWCheck[i].enResult;

            break;
        }
    }

    if (USIMM_SW_OK_WITH_SAT == enResult)    /*SAT��Ҫ���⴦��*/
    {
        USIMM_INFO_LOG("USIMM_CheckSW: There is SAT Data Need Fetch");

        gstUSIMMBaseInfo.enSATState = USIMM_SAT_STATE_NEEDFETCH;

        if (0x00 == ucSW2)           /*����ǰ��ȡ���������256*/
        {
            gstUSIMMBaseInfo.usSATLen = 0x100;
        }
        else
        {
            gstUSIMMBaseInfo.usSATLen = ucSW2;
        }

        enResult = USIMM_SW_OK;
    }

    return (VOS_UINT32)enResult;
}


VOS_UINT8 USIMM_MakeApduCLA(
    VOS_UINT8                           ucChannel,
    VOS_UINT8                           ucINS,
    VOS_UINT8                           ucCLABit,
    USIMM_APDUCMD_ATTRIBUTE_ENUM_UINT8  enAttribute)
{
    VOS_UINT8           ucCLA;
    VOS_UINT8           ucTempChannel;

    if ((CMD_INS_TERMINAL_PROFILE   == ucINS)
        ||(CMD_INS_ENVELOPE         == ucINS)
        ||(CMD_INS_FETCH            == ucINS)
        ||(CMD_INS_TERMINAL_RESPONSE== ucINS))
    {
        return (gstUSIMMBaseInfo.ucCLA | ucCLABit);
    }

    if ( ucChannel <= USIMM_APDU_CHANNEL_4 )
    {
        ucTempChannel = (ucChannel&0x03);
    }
    else
    {
        ucTempChannel = ((ucChannel-4)&0x0F);

        gstUSIMMBaseInfo.ucCLA |= 0x40;
    }

    if ((USIMM_APDUCMD_CSIM == enAttribute)
        &&(CMD_INS_COMPUTE_IP_AUTH == ucINS))
    {
        ucCLA = ucTempChannel|USIMM_APDU_3GPP_CLA;
    }
    else
    {
        ucCLA = ucTempChannel|gstUSIMMBaseInfo.ucCLA;
    }

    if (VOS_NULL != ucCLABit)
    {
        ucCLA = ucCLA|ucCLABit;
    }

    return ucCLA;
}


VOS_UINT8 USIMM_MakeTpduCLA(
    VOS_UINT8                           ucChannel,
    VOS_UINT8                           ucCLA,
    VOS_UINT8                           ucINS)
{
    VOS_UINT8           ucResultCLA;
    VOS_UINT8           ucTempChannel;

    if ((CMD_INS_TERMINAL_PROFILE   == ucINS)
        ||(CMD_INS_ENVELOPE         == ucINS)
        ||(CMD_INS_FETCH            == ucINS)
        ||(CMD_INS_TERMINAL_RESPONSE== ucINS))
    {
        return ucCLA;
    }

    if ( ucChannel <= USIMM_APDU_CHANNEL_4 )
    {
        ucTempChannel = (ucChannel&0x03);
    }
    else
    {
        ucTempChannel = ((ucChannel-4)&0x0F);

        ucCLA = ucCLA | 0x40;
    }

    ucResultCLA = ucTempChannel|ucCLA;

    return ucResultCLA;
}

/*****************************************************************************
�� �� ��  :USIMM_SelectFile_APDU
��������  :����ѡ���ļ�������
�������  :pstApduInfo:      �������
           ulRetryCnt:       ����ִ�д���
�������  :��
�� �� ֵ  :VOS_ERR
           VOS_OK

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_SelectFile_APDU(
    USIMM_APDU_ST                      *pstApduInfo,
    VOS_UINT32                          ulSendCnt
)
{
    VOS_UINT32                          ulResult;

    if(USIMM_SELECT_RETURN_FCP_TEMPLATE == pstApduInfo->aucAPDU[P2])
    {
        /* ���ֳ�����Ϊcase4 */
        pstApduInfo->ulLeValue      = USIMM_LE_MAX_LEN;
    }
    else
    {
        /* case3 */
        pstApduInfo->ulLeValue      = VOS_NULL;
    }

    ulResult = USIMM_DLHandle(pstApduInfo);/*������·�㴦����*/

    if (USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SelectFile_APDU:USIMM_DLHandle error");

        return USIMM_SENDAPDU_FAIL;
    }

    ulResult = USIMM_CheckSW(pstApduInfo->aucAPDU[INS], pstApduInfo->ucSW1, pstApduInfo->ucSW2);

    /* ״̬��ΪWarning��Technical Problem���ٴν���ѡ�ļ����� */
    if ((USIMM_SW_WARNING == ulResult) || (USIMM_SW_TECH_ERROR == ulResult))
    {
        if (1 == ulSendCnt) /*��һ�η���*/
        {
            /*TMO�����������Ӳ�ͬ���������Ի���*/
            if (USIMM_SELECT_RETURN_FCP_TEMPLATE == pstApduInfo->aucAPDU[P2])
            {
                pstApduInfo->aucAPDU[P2] = USIMM_SELECT_ACTIVATE_AID;
            }
            else if (USIMM_SELECT_NO_DATA_RETURNED == pstApduInfo->aucAPDU[P2])
            {
                pstApduInfo->aucAPDU[P2] = USIMM_SELECT_RETURN_FCP_TEMPLATE;
            }
            else
            {
                return USIMM_SENDAPDU_FAIL;
            }

            return USIMM_SENDAPDU_RETRY;
        }
        else
        {
            return USIMM_SENDAPDU_FAIL;
        }
    }

    return USIMM_SENDAPDU_OK;
}

/*****************************************************************************
�� �� ��  :USIMM_Status_APDU
��������  :ͨ��ָ����ͨ����Status�����
�������  :pstApduInfo:      �������
           ulRetryCnt:       ����ִ�д���
�������  :��
�� �� ֵ  :USIMM_SENDAPDU_RESULT_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat
*****************************************************************************/
USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_Status_APDU(
    USIMM_APDU_ST                      *pstApduInfo,
    VOS_UINT32                          ulSendCnt)
{
    VOS_UINT32              ulResult;

    if ((VOS_NULL == pstApduInfo->aucAPDU[P3])
     && (USIMM_STATUS_NO_DATA_RETURNED != pstApduInfo->aucAPDU[P2]))
    {
        pstApduInfo->ulLeValue = 0x100;
    }
    else
    {
        pstApduInfo->ulLeValue = pstApduInfo->aucAPDU[P3];
    }

    ulResult = USIMM_DLHandle(pstApduInfo);   /*������·�㴦����*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_STATUS_APDU: USIMM_DLHandle is Failed");/*��ӡ����*/

        return USIMM_SENDAPDU_FAIL;
    }

    return USIMM_SENDAPDU_OK;
}

/*****************************************************************************
�� �� ��  :USIMM_Manage_Channel_APDU
��������  :ͨ�����������
�������  :pstApduInfo:      �������
           ulRetryCnt:       ����ִ�д���
�������  :��
�� �� ֵ  :USIMM_SENDAPDU_RESULT_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_ManageChannel_APDU(
    USIMM_APDU_ST                      *pstApduInfo,
    VOS_UINT32                          ulSendCnt)
{
    VOS_UINT32              ulResult;

    if (USIMM_MANAGECH_CLOSECH == pstApduInfo->aucAPDU[P1])
    {
        if (USIMM_MANAGECH_ASSIGNED_CARD == pstApduInfo->aucAPDU[P2])
        {
            USIMM_ERROR_LOG("USIMM_Manage_Channel_APDU: pstApduInfo->aucAPDU[P2] is Failed");/*��ӡ����*/

            return USIMM_SENDAPDU_FAIL;
        }
        else
        {
            /* �ڶ�Ӧ���߼�ͨ���Ϸ� �ڴ��߼�ͨ��ʱ:p2Ϊ0���ر��߼�ͨ��ʱ:p2Ϊ��Ӧ�߼�ͨ���� */
            pstApduInfo->aucAPDU[CLA] = pstApduInfo->aucAPDU[CLA] | pstApduInfo->aucAPDU[P2];
        }
    }

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*������·�㴦����*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_Manage_Channel_APDU: USIMM_DLHandle is Failed");/*��ӡ����*/

        return USIMM_SENDAPDU_FAIL;
    }

    return USIMM_SENDAPDU_OK;
}

/*****************************************************************************
�� �� ��  :USIMM_Terminal_Capability_APDU
��������  :terminal capability�����
�������  :pstApduInfo:      �������
           ulRetryCnt:       ����ִ�д���
�������  :��
�� �� ֵ  :USIMM_SENDAPDU_RESULT_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_TerminalCapability_APDU(
    USIMM_APDU_ST                      *pstApduInfo,
    VOS_UINT32                          ulSendCnt)
{
    VOS_UINT32 ulResult;

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*������·�㴦����*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_Terminal_Capability_APDU: USIMM_DLHandle is Failed");/*��ӡ����*/

        return USIMM_SENDAPDU_FAIL;
    }

    return USIMM_SENDAPDU_OK;
}

/*****************************************************************************
�� �� ��  :USIMM_StoreESNMEID_APDU
��������  :����Store ESN MEID����
�������  :pstApduInfo:      �������
           ulRetryCnt:       ����ִ�д���
�������  :��
�� �� ֵ  :USIMM_SENDAPDU_RESULT_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_StoreESNMEID_APDU(
    USIMM_APDU_ST                      *pstApduInfo,
    VOS_UINT32                          ulSendCnt
)
{
    VOS_UINT32              ulResult;

    pstApduInfo->ulLcValue      = USIMM_STORE_ESNMEID_MAX;   /*���������������*/

    pstApduInfo->ulLeValue      = 0x01;                      /*�̶�ֵ*/

    ulResult = USIMM_DLHandle(pstApduInfo);   /*������·�㴦����*/

    if (USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_StoreESNMEID_APDU: USIMM_DLHandle is Failed");/*��ӡ����*/

        return USIMM_SENDAPDU_FAIL;
    }

    return USIMM_SENDAPDU_OK;
}

/*****************************************************************************
�� �� ��  :USIMM_ManageSsdAPDU
��������  :����MANAGE SSD����
�������  :pstApduInfo:      �������
           ulRetryCnt:       ����ִ�д���
�������  :��
�� �� ֵ  :USIMM_SENDAPDU_RESULT_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_ManageSsd_APDU(
    USIMM_APDU_ST                      *pstApduInfo,
    VOS_UINT32                          ulSendCnt)
{
    VOS_UINT32      ulResult;

    ulResult = USIMM_DLHandle(pstApduInfo);   /*������·�㴦����*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_ManageSsdAPDU: USIMM_DLHandle is Failed");/*��ӡ����*/

        return USIMM_SENDAPDU_FAIL;
    }

    return USIMM_SENDAPDU_OK;
}

/*****************************************************************************
�� �� ��  :USIMM_GenerateKeyVpmAPDU
��������  :����Generate Key/VPM����
�������  :pstApduInfo:      �������
           ulRetryCnt:       ����ִ�д���
�������  :��
�� �� ֵ  :USIMM_SENDAPDU_RESULT_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_GenerateKeyVpm_APDU(
    USIMM_APDU_ST                      *pstApduInfo,
    VOS_UINT32                          ulSendCnt)
{
    VOS_UINT32      ulResult;

    ulResult = USIMM_DLHandle(pstApduInfo);   /*������·�㴦����*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_GenerateKeyVpmAPDU: USIMM_DLHandle is Failed");/*��ӡ����*/

        return USIMM_SENDAPDU_FAIL;
    }

    return USIMM_SENDAPDU_OK;
}

/*****************************************************************************
�� �� ��  :USIMM_BSChallengeAPDU
��������  :����Store ESN MEID����
�������  :pstApduInfo:      �������
           ulRetryCnt:       ����ִ�д���
�������  :��
�� �� ֵ  :USIMM_SENDAPDU_RESULT_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_BSChallenge_APDU(
    USIMM_APDU_ST                      *pstApduInfo,
    VOS_UINT32                          ulSendCnt)
{
    VOS_UINT32      ulResult;

    pstApduInfo->ulLeValue    = USIMM_BS_RANDSEED_MAX;

    ulResult = USIMM_DLHandle(pstApduInfo);   /*������·�㴦����*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_BSChallengeAPDU: USIMM_DLHandle is Failed");/*��ӡ����*/

        return USIMM_SENDAPDU_FAIL;
    }

    return USIMM_SENDAPDU_OK;
}

/*****************************************************************************
�� �� ��  :USIMM_SendCase4_APDU
��������  :Search Increace Authentication �����
�������  :pstApduInfo:      �������
           ulRetryCnt:       ����ִ�д���
�������  :��
�� �� ֵ  :USIMM_SENDAPDU_RESULT_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_SendCase4_APDU(
    USIMM_APDU_ST                      *pstApduInfo,
    VOS_UINT32                          ulRetryCnt)
{
    VOS_UINT32                      ulResult;

    /* ���ֳ�����Ϊcase4 */
    pstApduInfo->ulLeValue = USIMM_LE_MAX_LEN;

    ulResult = USIMM_DLHandle(pstApduInfo);   /*������·�㴦����*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_Search_APDU: USIMM_DLHandle is Failed");/*��ӡ����*/

        return USIMM_SENDAPDU_FAIL;
    }

    return USIMM_SENDAPDU_OK;
}

/*****************************************************************************
�� �� ��  :USIMM_SendAndRetry_APDU
��������  :ReadBinary UPDATEBINARY READRECORD UPDATERECORD �����
�������  :pstApduInfo:      �������
           ulRetryCnt:       ����ִ�д���
�������  :��
�� �� ֵ  :USIMM_SENDAPDU_RESULT_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_SendAndRetry_APDU(
    USIMM_APDU_ST                      *pstApduInfo,
    VOS_UINT32                          ulSendCnt)
{
    VOS_UINT32                          ulResult;

    ulResult = USIMM_DLHandle(pstApduInfo);   /*������·�㴦����*/

    if (USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SendAndRetry_APDU: USIMM_DLHandle is Failed");/*��ӡ����*/

        if (1 == ulSendCnt)
        {
            return USIMM_SENDAPDU_RETRY;
        }
        else
        {
            return USIMM_SENDAPDU_FAIL;
        }
    }

    ulResult = USIMM_CheckSW(pstApduInfo->aucAPDU[INS], pstApduInfo->ucSW1, pstApduInfo->ucSW2);

    if ((USIMM_SW_OK != ulResult)&&(1 == ulSendCnt))
    {
        USIMM_ERROR_LOG("USIMM_SendAndRetry_APDU: USIMM_CheckSW is Failed");/*��ӡ����*/

        return USIMM_SENDAPDU_RETRY;
    }

    return USIMM_SENDAPDU_OK;
}

/*****************************************************************************
�� �� ��  :USIMM_SendOneTime_APDU
��������  :VerifyPIN ChangePIN UnblockPIN DeactivateFile ActivateFile �����
�������  :pstApduInfo:      �������
           ulRetryCnt:       ����ִ�д���
�������  :��
�� �� ֵ  :USIMM_SENDAPDU_RESULT_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_SendOneTime_APDU(
    USIMM_APDU_ST                      *pstApduInfo,
    VOS_UINT32                          ulSendCnt)
{
    VOS_UINT32                          ulResult;

    ulResult = USIMM_DLHandle(pstApduInfo);   /*������·�㴦����*/

    if (USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SendOneTime_APDU: USIMM_DLHandle is Failed");/*��ӡ����*/

        return USIMM_SENDAPDU_FAIL;
    }

    return USIMM_SENDAPDU_OK;
}

USIMM_APDU_FUNC_LIST    g_aUSIMMApduFuncTbl[]=
{
    {CMD_INS_SELECT                ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_SelectFile_APDU},
    {CMD_INS_STATUS                ,    USIMM_APDU_3GPP_CLA,    USIMM_APDUCMD_COMMON,   0,  USIMM_Status_APDU},
    {CMD_INS_READ_BINARY           ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_SendAndRetry_APDU},
    {CMD_INS_UPDATE_BINARY         ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_SendAndRetry_APDU},
    {CMD_INS_READ_RECORD           ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_SendAndRetry_APDU},
    {CMD_INS_UPDATE_RECORD         ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_SendAndRetry_APDU},
    {CMD_INS_SEARCH_RECORD         ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_SendCase4_APDU},
    {CMD_INS_INCREASE              ,    USIMM_APDU_3GPP_CLA,    USIMM_APDUCMD_COMMON,   0,  USIMM_SendCase4_APDU},
    {CMD_INS_RETRIEVE_DATA         ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_SET_DATA              ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_VERIFY                ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_SendOneTime_APDU},
    {CMD_INS_CHANGE_PIN            ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_SendOneTime_APDU},
    {CMD_INS_DISABLE_PIN           ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_SendOneTime_APDU},
    {CMD_INS_ENABLE_PIN            ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_SendOneTime_APDU},
    {CMD_INS_UNBLOCK_PIN           ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_SendOneTime_APDU},
    {CMD_INS_DEACTIVATE_FILE       ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_SendOneTime_APDU},
    {CMD_INS_ACTIVATE_FILE         ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_SendOneTime_APDU},
    {CMD_INS_AUTHENTICATE          ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_SendCase4_APDU},
    {CMD_INS_GET_CHALLENGE         ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_TERMINAL_PROFILE      ,    USIMM_APDU_3GPP_CLA,    USIMM_APDUCMD_COMMON,   0,  USIMM_SendOneTime_APDU},
    {CMD_INS_ENVELOPE              ,    USIMM_APDU_3GPP_CLA,    USIMM_APDUCMD_COMMON,   0,  USIMM_SendCase4_APDU},
    {CMD_INS_FETCH                 ,    USIMM_APDU_3GPP_CLA,    USIMM_APDUCMD_COMMON,   0,  USIMM_SendOneTime_APDU},
    {CMD_INS_TERMINAL_RESPONSE     ,    USIMM_APDU_3GPP_CLA,    USIMM_APDUCMD_COMMON,   0,  USIMM_SendOneTime_APDU},
    {CMD_INS_MANAGE_CHANNEL        ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_ManageChannel_APDU},
    {CMD_INS_TERMINAL_CAPABILITY   ,    USIMM_APDU_3GPP_CLA,    USIMM_APDUCMD_COMMON,   0,  USIMM_TerminalCapability_APDU},
    {CMD_INS_MANAGE_SECURE_CHANNEL ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_TRANSACT_DATA         ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_SLEEP                 ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_BASE_STATION_CHALLENGE,    USIMM_APDU_3GPP_CLA,    USIMM_APDUCMD_COMMON,   0,  USIMM_BSChallenge_APDU},
    {CMD_INS_UPDATE_SSD            ,    0,                      USIMM_APDUCMD_UIM,      0,  USIMM_SendOneTime_APDU},
    {CMD_INS_CONFIRM_SSD           ,    0,                      USIMM_APDUCMD_UIM,      0,  USIMM_SendOneTime_APDU},
    {CMD_INS_MANAGE_SSD            ,    USIMM_APDU_3GPP_CLA,    USIMM_APDUCMD_CSIM,     0,  USIMM_ManageSsd_APDU},
    {CMD_INS_GENERATE_KEY          ,    USIMM_APDU_3GPP_CLA,    USIMM_APDUCMD_COMMON,   0,  USIMM_GenerateKeyVpm_APDU},
    {CMD_INS_STORE_ESNMEID         ,    USIMM_APDU_3GPP_CLA,    USIMM_APDUCMD_COMMON,   0,  USIMM_StoreESNMEID_APDU},
    {CMD_INS_LCS_SSAVE_VERIFY      ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_MMS_CFG         ,    0,                      USIMM_APDUCMD_UIM,      0,  VOS_NULL_PTR},
    {CMD_INS_LCS_TLS_GMASTER       ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_LCS_TLS_GVERIFY       ,    0,                      USIMM_APDUCMD_CSIM,     0,  VOS_NULL_PTR},
    {CMD_INS_VANDG_KEYBLOCK        ,    0,                      USIMM_APDUCMD_CSIM,     0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_MMS_DOWNLOAD    ,    0,                      USIMM_APDUCMD_UIM,      0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_3GPD_DOWNLOAD   ,    0,                      USIMM_APDUCMD_UIM,      0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_SUCURE_MODE     ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_FRESH           ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_SKEY_GENERATION ,    0,                      USIMM_APDUCMD_UIM,      0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_GENERIC_KEY     ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_KEY_GENERATION  ,    0,                      USIMM_APDUCMD_UIM,      0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_GENERIC_CFG     ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_DOWNLOAD        ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_BCMCS                 ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_SendOneTime_APDU},
    {CMD_INS_APP_AUTH              ,    0,                      USIMM_APDUCMD_COMMON,   0,  USIMM_SendOneTime_APDU},
    {CMD_INS_UMAC_GENERATION       ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_CONFIRM_KEYS          ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_COMPUTE_IP_AUTH       ,    USIMM_APDU_3GPP_CLA,    USIMM_APDUCMD_CSIM,     0,  USIMM_SendOneTime_APDU},
    {CMD_INS_OTASP_MMD_CFG         ,    0,                      USIMM_APDUCMD_UIM,      0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_MMD_DOWNLOAD    ,    0,                      USIMM_APDUCMD_UIM,      0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_SYSTAG_CFG      ,    0,                      USIMM_APDUCMD_UIM,      0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_COMMIT          ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_VALIDATE        ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_SSPR_CFG        ,    0,                      USIMM_APDUCMD_UIM,      0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_SSPR_DOWNLOAD   ,    0,                      USIMM_APDUCMD_UIM,      0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_SYSTAG_DOWNLOAD ,    0,                      USIMM_APDUCMD_UIM,      0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_OTAPA_REQUEST   ,    0,                      USIMM_APDUCMD_COMMON,   0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_PUZL_CFG        ,    0,                      USIMM_APDUCMD_UIM,      0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_PUZL_DOWNLOAD   ,    0,                      USIMM_APDUCMD_UIM,      0,  VOS_NULL_PTR},
    {CMD_INS_OTASP_3GPD_CFG        ,    0,                      USIMM_APDUCMD_UIM,      0,  VOS_NULL_PTR}
};


VOS_VOID USIMM_MakeAPDUCmdData(
    USIMM_APDU_HEAD_STRU                *pstApduHead,
    USIMM_U8_LVDATA_STRU                *pstApduData,
    USIMM_APDU_RSP_STRU                 *pstRspData)
{
    /*lint -e534*/
    VOS_MemSet(&gstUSIMMAPDU, 0, sizeof(gstUSIMMAPDU));

    if (VOS_NULL_PTR != pstRspData)
    {
        VOS_MemSet(pstRspData, 0, sizeof(USIMM_APDU_RSP_STRU));
    }
    /*lint +e534*/

    /*���APDU����ͷ*/
    gstUSIMMAPDU.aucAPDU[INS]   = pstApduHead->ucINS;

    gstUSIMMAPDU.aucAPDU[P1]    = pstApduHead->ucP1;

    gstUSIMMAPDU.aucAPDU[P2]    = pstApduHead->ucP2;

    /*���������������*/
    if (VOS_NULL_PTR != pstApduData)
    {
        gstUSIMMAPDU.aucAPDU[P3]    = (VOS_UINT8)pstApduData->ulDataLen;

        gstUSIMMAPDU.ulLcValue      = pstApduData->ulDataLen;

        /*lint -e534*/
        VOS_MemCpy(gstUSIMMAPDU.aucSendBuf,
                    pstApduData->pucData,
                    gstUSIMMAPDU.aucAPDU[P3]);
        /*lint +e534*/
    }
    else
    {
        gstUSIMMAPDU.aucAPDU[P3]    = pstApduHead->ucP3;

        gstUSIMMAPDU.ulLcValue      = VOS_NULL;

        gstUSIMMAPDU.ulLeValue      = pstApduHead->ucP3;
    }

    return;
}


VOS_VOID USIMM_AttApduSWCheck(VOS_VOID)
{
    if (VOS_TRUE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulAtt_flg)
    {
        if ((0x6F == gstUSIMMAPDU.ucSW1)&&(0x00 == gstUSIMMAPDU.ucSW2))
        {
            g_ulATTSpecErrSWCnt++;
        }
        else
        {
            g_ulATTSpecErrSWCnt = 0;
        }

        if (g_ulATTSpecErrSWCnt >= 3)                                 /*��������3���ϱ��޿�*/
        {
            USIMM_CCB_SetCardType(USIMM_PHYCARD_TYPE_NOCARD);        /*��ǰ״̬Ϊ�޿�*/
        }
    }

    return;
}


USIMM_SWCHECK_ENUM_UINT32 USIMM_SendAPDUHandle(
    USIMM_APDUCMD_ATTRIBUTE_ENUM_UINT8  enAttribute,
    USIMM_APDU_HEAD_STRU                *pstApduHead,
    USIMM_U8_LVDATA_STRU                *pstApduData,
    USIMM_APDU_RSP_STRU                 *pstRspData)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulSendCnt;
    USIMM_SENDAPDU_RESULT_ENUM_UINT32   enResult = USIMM_SENDAPDU_FAIL;

    if (VOS_NULL_PTR == pstApduHead)
    {
        USIMM_ERROR_LOG("USIMM_SendAPDUHandle: pstApduHead NULL");/*��ӡ����*/

        return USIMM_SW_ERR;
    }

    USIMM_MakeAPDUCmdData(pstApduHead, pstApduData, pstRspData);

    if (VOS_NULL_PTR != pstRspData)
    {
        (VOS_VOID)VOS_MemSet(pstRspData, 0, sizeof(USIMM_APDU_RSP_STRU));
    }
    /*lint +e534*/

    ulSendCnt = 0;

    for (i=0; i<ARRAYSIZE(g_aUSIMMApduFuncTbl);)
    {
        if ((g_aUSIMMApduFuncTbl[i].ucINS       == pstApduHead->ucINS)
            &&(g_aUSIMMApduFuncTbl[i].pProcFun  != VOS_NULL_PTR)
            &&(g_aUSIMMApduFuncTbl[i].enAttribute == enAttribute))
        {
            ulSendCnt++;

            gstUSIMMAPDU.aucAPDU[CLA] = USIMM_MakeApduCLA(pstApduHead->ucChannel,
                                                            pstApduHead->ucINS,
                                                            g_aUSIMMApduFuncTbl[i].ucCLABit,
                                                            g_aUSIMMApduFuncTbl[i].enAttribute);

            enResult = g_aUSIMMApduFuncTbl[i].pProcFun(&gstUSIMMAPDU, ulSendCnt);

            if (USIMM_SENDAPDU_RETRY == enResult)
            {
                USIMM_ERROR_LOG("USIMM_SendAPDUHandle: APDU Need Retry");/*��ӡ����*/

                continue;
            }
            else
            {
                break;
            }
        }

        i++;
    }

    if (USIMM_SENDAPDU_FAIL == enResult)
    {
        USIMM_ERROR_LOG("USIMM_SendAPDUHandle: APDU Send Fail");/*��ӡ����*/

        return USIMM_SW_SENDCMD_ERROR;
    }

    if (VOS_NULL_PTR != pstRspData)
    {
        pstRspData->usRspLen    = (VOS_UINT16)gstUSIMMAPDU.ulRecDataLen;

        pstRspData->ucSW1       = gstUSIMMAPDU.ucSW1;

        pstRspData->ucSW2       = gstUSIMMAPDU.ucSW2;

        pstRspData->ucApduSW1   = gstUSIMMAPDU.ucApduSW1;

        pstRspData->ucApduSW2   = gstUSIMMAPDU.ucApduSW2;

        if (VOS_NULL != gstUSIMMAPDU.ulRecDataLen)
        {
            /*lint -e534*/
            VOS_MemCpy(pstRspData->aucRsp,
                        gstUSIMMAPDU.aucRecvBuf,
                        gstUSIMMAPDU.ulRecDataLen);
            /*lint +e534*/
        }
    }

    USIMM_AttApduSWCheck();

    return USIMM_CheckSW(pstApduHead->ucINS,
                        gstUSIMMAPDU.ucSW1,
                        gstUSIMMAPDU.ucSW2);   /*���ص������Ľ�������ǵ�һ�η��ͽ��*/
}
VOS_UINT32 USIMM_T1SendIFSD_APDU(
    VOS_UINT8                           ucData)
{
    VOS_UINT32      ulResult;

    /*lint -e534*/
    VOS_MemSet(gstUSIMMAPDU.aucAPDU, 0, USIMM_APDU_HEADLEN);

    VOS_MemSet(gstUSIMMAPDU.aucSendBuf, 0, USIMM_APDU_MAXLEN);
    /*lint +e534*/

    /* ��Ҫ����һ���ֽڵ�IFS��С */
    gstUSIMMAPDU.ulLcValue = 0x01;

    gstUSIMMAPDU.ulLeValue = 0x00;

    gstUSIMMAPDU.aucSendBuf[0] = ucData;

    /* ��ǵ�ǰҪ����IFS REQ */
    g_bSendIFSReqFlag = VOS_TRUE;

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*������·�㴦����*/

    g_bSendIFSReqFlag = VOS_FALSE;

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_T1SendIFSD_APDU: USIMM_DLHandle is Failed");/*��ӡ����*/

        return VOS_ERR;
    }

    return VOS_OK;
}


USIMM_SWCHECK_ENUM_UINT32 USIMM_SendTPDUHandle(
    USIMM_TPDU_HEAD_STRU                *pstTpduHead,
    USIMM_U8_LVDATA_STRU                *pstTpduData,
    USIMM_APDU_RSP_STRU                 *pstRspData
)
{
    VOS_UINT32                          ulResult;

    if ((VOS_NULL_PTR == pstTpduHead)||(VOS_NULL_PTR == pstRspData))
    {
        USIMM_ERROR_LOG("USIMM_SendAPDUHandle: pstTpduHead or pstRspData NULL");/*��ӡ����*/

        return USIMM_SW_ERR;
    }

    /*lint -e534*/
    VOS_MemSet(&gstUSIMMAPDU, 0, sizeof(gstUSIMMAPDU));

    VOS_MemSet(pstRspData, 0, sizeof(USIMM_APDU_RSP_STRU));
    /*lint +e534*/

    /*���APDU����ͷ*/
    gstUSIMMAPDU.aucAPDU[CLA]   = USIMM_MakeTpduCLA(pstTpduHead->ucChannel,
                                                    pstTpduHead->ucCLA,
                                                    pstTpduHead->ucINS);    /*������ͨ������*/

    gstUSIMMAPDU.aucAPDU[INS]   = pstTpduHead->ucINS;

    gstUSIMMAPDU.aucAPDU[P1]    = pstTpduHead->ucP1;

    gstUSIMMAPDU.aucAPDU[P2]    = pstTpduHead->ucP2;

    /*���������������*/
    if (VOS_NULL_PTR != pstTpduData)    /*case3, case4*/
    {
        if ((pstTpduData->ulDataLen < pstTpduHead->ucP3)
            ||(pstTpduData->ulDataLen > (pstTpduHead->ucP3 + 1)))
        {
            USIMM_ERROR_LOG("USIMM_SendTPDUHandle: the data len is more");/*��ӡ����*/

            return USIMM_SW_ERR;
        }

        gstUSIMMAPDU.aucAPDU[P3]    = pstTpduHead->ucP3;

        gstUSIMMAPDU.ulLcValue      = pstTpduHead->ucP3;

        /*lint -e534*/
        VOS_MemCpy(gstUSIMMAPDU.aucSendBuf, pstTpduData->pucData, gstUSIMMAPDU.aucAPDU[P3]);
        /*lint +e534*/

        /* case4��������һ�ֽڵ�LE�ֶ� */
        if (pstTpduData->ulDataLen == (pstTpduHead->ucP3 + 1))
        {
            gstUSIMMAPDU.ulLeValue = pstTpduData->pucData[pstTpduData->ulDataLen - 1];
        }
    }
    else                            /*case1 case2*/
    {
        gstUSIMMAPDU.aucAPDU[P3]    = pstTpduHead->ucP3;

        gstUSIMMAPDU.ulLcValue      = VOS_NULL;

        gstUSIMMAPDU.ulLeValue      = pstTpduHead->ucP3;
    }

    if (0 == pstTpduHead->ucChannel)
    {
        ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*������·�㴦����*/
    }
    else
    {
        ulResult = USIMM_CglaDLHandle(&gstUSIMMAPDU);   /*������·�㴦����*/
    }

    if (USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SendTPDUHandle: USIMM_DLHandle Fail");/*��ӡ����*/

        return USIMM_SW_OTHER_ERROR;
    }

    pstRspData->usRspLen = (VOS_UINT16)gstUSIMMAPDU.ulLeValue;

    pstRspData->ucSW1       = gstUSIMMAPDU.ucSW1;

    pstRspData->ucSW2       = gstUSIMMAPDU.ucSW2;

    pstRspData->ucApduSW1   = gstUSIMMAPDU.ucApduSW1;

    pstRspData->ucApduSW2   = gstUSIMMAPDU.ucApduSW2;

    if (VOS_NULL != gstUSIMMAPDU.ulLeValue)
    {
        /*lint -e534*/
        VOS_MemCpy(pstRspData->aucRsp, gstUSIMMAPDU.aucRecvBuf, gstUSIMMAPDU.ulLeValue);
        /*lint +e534*/
    }

    return USIMM_SW_OK;
}
VOS_UINT32 USIMM_DLResetCard(VOS_UINT32 ulResetType, VOS_INT32 *plVoltageSwitchRst)
{
    VOS_INT32                           lSCIResult = VOS_ERR;
    VOS_UINT32                          i;
    NV_USIMM_T1_CTRL_PARA_STRU          stT1CtrlPara;

    if (USIMM_RESET_CARD == ulResetType)
    {
        OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1,
                            WUEPS_PID_USIM,
                            WUEPS_PID_USIM,
                            USIMMDL_DRV_USIMMSCI_RST);

        (VOS_VOID)mdrv_sci_reset(COLD_RESET);

        OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

        if(USIMM_DL_T_MODE_T1 == g_enUSIMMTMode)
        {
            /* ���±��� */
            if(VOS_OK != USIMM_T1DLUpdateParaByATR(g_stUSIMMT1Para.enErrDetectMode,
                                                    g_stUSIMMT1Para.ulIFSC,
                                                    g_stUSIMMT1Para.ulIFSD))
            {
                USIMM_ERROR_LOG("USIMM_DLResetCard: USIMM_T1DLUpdateParaByATR fail!");
                return VOS_ERR;
            }

            /*lint -e534*/
            VOS_MemSet(&stT1CtrlPara, 0, sizeof(stT1CtrlPara));
            /*lint +e534*/

            /* ��NV�� */
            if(VOS_OK != NV_Read(en_NV_Item_Usimm_T1_Ctrl_PARA,
                                &stT1CtrlPara,
                                sizeof(stT1CtrlPara)))
            {
                /* ��ӡ���� */
                USIMM_ERROR_LOG("USIMM_DecideTMode:USIM Read T1 PARA NV error");

                /* NV��ȡʧ�ܣ���ʽ��ֵΪT0 */
                stT1CtrlPara.enTMode = USIMM_DL_T_MODE_T0;
            }

            /* ����IFS����,���߿�UE�������� */
            if(VOS_OK != USIMM_T1SendIFSD_APDU((VOS_UINT8)stT1CtrlPara.ulDefaultIFSD))
            {
                USIMM_ERROR_LOG("USIMM_DLResetCard: USIMM_T1SendIFSD_APDU fail!");
                return VOS_ERR;
            }

            OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1,
                                WUEPS_PID_USIM,
                                WUEPS_PID_USIM,
                                USIMMDL_DRV_USIMMSCI_T1_PRTCL_SWITCH_1);

            if(VOS_OK != mdrv_sci_switch_protocol((PROTOCOL_MODE_E)g_enUSIMMTMode))
            {
                /* ��ά�ɲ���Ϣͳ�� */
                g_stT1StatisticInfo.ulProtocolSwitchFailCnt++;

                USIMM_WARNING_LOG("USIMM_DLResetCard:SET T MODE FAILED");
            }

            OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);
        }
    }
    else
    {
        OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1,
                            WUEPS_PID_USIM,
                            WUEPS_PID_USIM,
                            USIMMDL_DRV_USIMMSCI_CLASS_SWITCH);

        lSCIResult = mdrv_sci_switch_class();

        OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

        *plVoltageSwitchRst = lSCIResult;

        if (USIMM_SCI_SUCCESS == lSCIResult)      /*��ѹ�л��ɹ�����Ҫ�ӳ�*/
        {
            USIMM_NORMAL_LOG("USIMM_DLResetCard: SIM Card Change the Voltage Successful");
        }
        else if (USIMM_SCI_NONEED_CHANGEVCC == lSCIResult)
        {
            USIMM_NORMAL_LOG("USIMM_DLResetCard: Card needn't Change the Voltage");
        }
        else                     /*��ѹ�л�ʧ�ܰ����޿�����*/
        {
            USIMM_CCB_SetCardType(USIMM_PHYCARD_TYPE_NOCARD);

            return VOS_ERR;
        }
    }

    for (i = 0; i < USIMM_GET_SCISTATUS_MAX; i++)        /*ѭ���жϵ�ǰ�Ŀ���λ���*/
    {
        OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1,
                            WUEPS_PID_USIM,
                            WUEPS_PID_USIM,
                            USIMMDL_DRV_USIMMSCI_GET_CARD_STAU);

        lSCIResult = mdrv_sci_get_cardstatus(); /*�����λ�ɹ��򷵻سɹ�*/

        OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

        if (SCI_CARD_STATE_BUSY != lSCIResult)
        {
            break;
        }
#if (VOS_OS_VER != VOS_WIN32)       /* PC Stub */
        HPA_USIMLowPowerLock(WUEPS_PID_USIM);
#endif

        (VOS_VOID)VOS_TaskDelay(20);     /*�ȴ�����������ATR��PPS����*/

#if (VOS_OS_VER != VOS_WIN32)       /* PC Stub */
        HPA_USIMLowPowerUnLock(WUEPS_PID_USIM);
#endif
    }

    if (SCI_CARD_STATE_NOCARD == lSCIResult)
    {
        USIMM_ERROR_LOG("USIMM_DLResetCard: USIMM Could Not Find Any SIM Card!");

        USIMM_CCB_SetCardType(USIMM_PHYCARD_TYPE_NOCARD);

        mdrv_sci_save_recorddata();

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
�� �� ��  : USIMM_TerminateADF
��������  : ѡ�����е�3GPPӦ��
�������  : ��
�������  : ��
�� �� ֵ  : NA
�޶���¼  :
1. ��    ��   : 2015��3��18��
    ��    ��   : zhuli
    �޸�����   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_SendStatusApdu(
    VOS_UINT8                           ucChannelID,
    VOS_UINT8                           ucP1,
    VOS_UINT8                           ucP2,
    VOS_UINT8                           ucP3)
{
    USIMM_APDU_HEAD_STRU                stApduHead;

    stApduHead.ucChannel    = ucChannelID;
    stApduHead.ucINS        = CMD_INS_STATUS;
    stApduHead.ucP1         = ucP1;

    if (USIMM_STATUS_NO_DATA_RETURNED == ucP2)
    {
        stApduHead.ucP2         = USIMM_STATUS_NO_DATA_RETURNED;
        stApduHead.ucP3         = VOS_NULL;
    }
    else
    {
        stApduHead.ucP2         = ucP2;
        stApduHead.ucP3         = ucP3;
    }

    return USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                &stApduHead,
                                VOS_NULL_PTR,
                                VOS_NULL_PTR);
}

/*****************************************************************************
�� �� ��  :USIMM_StatusPollingNeedFcp
��������  :����STATUS����Ҫ�󷵻�FCP
�������  :��
�������  :pstRspData:STATUS����ص�FCP����
�� �� ֵ  :VOS_OK/VOS_ERR

�޶���¼  :
1. ��    ��   : 2015��3��7��
    ��    ��   : h00300778
    �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendStatusPollingApdu(
    USIMM_APDU_RSP_STRU                 *pstRspData)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_CARDAPP_ENUM_UINT32           enAppType;

    enAppType   = USIMM_CCB_GetMainAppType();

    stApduHead.ucChannel    = 0;
    stApduHead.ucINS        = CMD_INS_STATUS;

    stApduHead.ucP1         = USIMM_STATUS_NO_INDICATION;
    stApduHead.ucP2         = USIMM_STATUS_FCP_RETURNED;
    stApduHead.ucP3         = (VOS_UINT8)USIMM_CCB_GetCurFileInfo(enAppType)->usCurDFFcpLen;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    VOS_NULL_PTR,
                                    pstRspData);

    return ulResult;
}

/*****************************************************************************
�� �� ��  :USIMM_SendOpenSpecificChannelCmd
��������  :���ʹ�ָ��CHANNEL ID��MANAGE CHANNEL�����APDU
�������  :ucP2:P2����
�������  :��
�� �� ֵ  :VOS_OK/VOS_ERR

�޶���¼  :
1. ��    ��   : 2015��4��9��
    ��    ��   : h00300778
    �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendCloseChannelApdu(
    VOS_UINT8                           ucP2)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_APDU_RSP_STRU                 stRspData;

    stApduHead.ucChannel    = 0;
    stApduHead.ucINS        = CMD_INS_MANAGE_CHANNEL;
    stApduHead.ucP1         = USIMM_CLOSE_CHANNEL;
    stApduHead.ucP2         = ucP2;
    stApduHead.ucP3         = 0;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    VOS_NULL_PTR,
                                    &stRspData);

    /* �жϷ��ͽ�� */
    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SendCloseChannelApdu:USIMM_SendAPDUHandle error");
    }

    return ulResult;
}


/*****************************************************************************
�� �� ��  :USIMM_OpenChannelApdu
��������  :���߼�ͨ��
�������  :��
�������  :pucChannelID: �����߼�ͨ����
�� �� ֵ  :VOS_ERR
           VOS_OK
�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendOpenChannelApdu(
    VOS_UINT8                          *pucChannelID
)
{
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_APDU_RSP_STRU                 stRspData;
    VOS_UINT8                           ucChannelID;
    VOS_UINT32                          ulResult;

    /* �·�manage���߼�ͨ��,��ͨ����ʱ���ڻ����߼�ͨ���ϣ����P2����Ϊ0,P3������1����������һ���ֽڵ�channelID */
    stApduHead.ucChannel        = USIMM_APDU_BASECHANNEL;
    stApduHead.ucINS            = CMD_INS_MANAGE_CHANNEL;
    stApduHead.ucP1             = USIMM_OPEN_CHANNEL;
    stApduHead.ucP2             = USIMM_MANAGECH_ASSIGNED_CARD;
    stApduHead.ucP3             = 0x01;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    VOS_NULL_PTR,
                                    &stRspData);

    /*�жϼ����*/
    if (USIMM_SW_OK != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_SendOpenChannelApdu: USIMM_SendAPDUHandle Error");

        return ulResult;
    }

    ucChannelID = stRspData.aucRsp[0];

    /* ͨ��ID�����Ϸ���Χ */
    if (USIMM_CHANNEL_NUMBER_MAX <= ucChannelID)
    {
        USIMM_ERROR_LOG("USIMM_SendOpenChannelApdu: Channel ID is not valid.");

        (VOS_VOID)USIMM_SendCloseChannelApdu(ucChannelID);

        return USIMM_SW_ERR;
    }

    *pucChannelID = ucChannelID;

    return USIMM_SW_OK;
}
VOS_UINT32 USIMM_SendUpdateRecordApdu(
    VOS_UINT8                           ucChannelID,
    VOS_UINT8                           ucMode,
    VOS_UINT8                           ucRecordNum,
    VOS_UINT8                          *pucData,
    VOS_UINT8                           ucLen)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stApduData;

    stApduHead.ucChannel    = ucChannelID;
    stApduHead.ucINS        = CMD_INS_UPDATE_RECORD;

    stApduHead.ucP1         = ucRecordNum;
    stApduHead.ucP2         = ucMode;
    stApduHead.ucP3         = ucLen;

    stApduData.ulDataLen    = ucLen;
    stApduData.pucData      = pucData;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    &stApduData,
                                    VOS_NULL_PTR);

    return ulResult;
}


VOS_UINT32 USIMM_SendUpdateBinaryApdu(
    VOS_UINT8                           ucChannelID,
    VOS_UINT16                          usLen,
    VOS_UINT8                          *pucData
)
{
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stApduData;
    VOS_UINT32                          ulResult = USIMM_SW_OK;
    VOS_UINT16                          usUpdateLen;
    VOS_UINT8                           ucP3 = 0;

    stApduHead.ucChannel    = ucChannelID;

    stApduHead.ucINS        = CMD_INS_UPDATE_BINARY;

    for (usUpdateLen=0; usUpdateLen<usLen; usUpdateLen += ucP3)
    {
        if(usLen > (0xFF + usUpdateLen))   /*�жϵ�ǰ��ʣ�����ݳ���*/
        {
            ucP3 = 0xFF;                            /*ʣ�����ݴ���255*/
        }
        else
        {
            ucP3 = (VOS_UINT8)(usLen - usUpdateLen);   /*ʣ�����ݿ���һ�θ������*/
        }

        stApduHead.ucP1         = (VOS_UINT8)((usUpdateLen >> 8) & 0xFF);
        stApduHead.ucP2         = (VOS_UINT8)(usUpdateLen & 0xFF);
        stApduHead.ucP3         = ucP3;

        stApduData.ulDataLen    = ucP3;
        stApduData.pucData      = (pucData + usUpdateLen);

        ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                        &stApduHead,
                                        &stApduData,
                                        VOS_NULL_PTR);

        if (VOS_OK != ulResult)         /*�жϷ��ͽ��*/
        {
            USIMM_ERROR_LOG("USIMM_UpdateTFFile:USIMM_UpdateBinary_APDU error");

            return ulResult;
        }
    }

    return ulResult;
}


VOS_UINT32 USIMM_SendReadRecordApdu(
    VOS_UINT8                           ucChannel,
    VOS_UINT8                           ucTotalNum,
    VOS_UINT8                           ucRecordLen,
    VOS_UINT8                           ucRecordIndex,
    VOS_UINT8                          *pucContent)
{
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_APDU_RSP_STRU                 stRspData;
    VOS_UINT32                          i    = 1;
    VOS_UINT32                          ulTotalNum;

    if (ucTotalNum < ucRecordIndex)
    {
        USIMM_ERROR_LOG("USIMM_SendReadRecordApdu:ucRecordIndex Error");

        return USIMM_SW_ERR;
    }

    stApduHead.ucChannel    = ucChannel;
    stApduHead.ucINS        = CMD_INS_READ_RECORD;
    stApduHead.ucP2         = USIMM_RECORD_ABSOLTE;
    stApduHead.ucP3         = ucRecordLen;

    if(USIMM_READ_ALLRECORD == ucRecordIndex)
    {
        ulTotalNum = ucTotalNum;
    }
    else
    {
        i           = ucRecordIndex;

        ulTotalNum  = ucRecordIndex;
    }

    for(; i<=ulTotalNum; i++)
    {
        stApduHead.ucP1         = (VOS_UINT8)i;

        if(VOS_OK != USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                            &stApduHead,
                                            VOS_NULL_PTR,
                                            &stRspData))/*�жϷ��ͽ��*/
        {
            USIMM_ERROR_LOG("USIMM_ReadLFFile: USIMM_ReadRecord_APDU Error");

            return USIMM_SW_SENDCMD_ERROR;
        }

        /*lint -e534 */
        VOS_MemCpy(pucContent, stRspData.aucRsp, ucRecordLen);
        /*lint +e534 */

        pucContent += ucRecordLen;
    }

    return USIMM_SW_OK;
}
VOS_UINT32 USIMM_SendReadBinaryApdu(
    VOS_UINT8                           ucChannelID,
    VOS_UINT16                          usOffset,
    VOS_UINT16                          usNeedLen,
    VOS_UINT8                           *pucContent)
{
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_APDU_RSP_STRU                 stRspData;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usReadedLen;
    VOS_UINT8                           ucP3 = 0;

    stApduHead.ucChannel    = ucChannelID;
    stApduHead.ucINS        = CMD_INS_READ_BINARY;

    for (usReadedLen=0; usReadedLen<usNeedLen; usReadedLen+=ucP3)
    {
        if ((usNeedLen - usReadedLen) > 0xFF)      /*�����³���*/
        {
            ucP3 = 0xFF;
        }
        else
        {
            ucP3 = (VOS_UINT8)(usNeedLen - usReadedLen);  /*ʣ����³���*/
        }

        stApduHead.ucP1         = (VOS_UINT8)(((usReadedLen+usOffset) >> 8) & 0xFF);
        stApduHead.ucP2         = (VOS_UINT8)((usReadedLen+usOffset) & 0xFF);
        stApduHead.ucP3         = ucP3;

        ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                        &stApduHead,
                                        VOS_NULL_PTR,
                                        &stRspData);

        if(VOS_OK != ulResult)/*�жϸ��·��ͽ��*/
        {
            USIMM_ERROR_LOG("USIMM_SendReadBinaryApdu: USIMM_ReadBinary_APDU Error");

            return ulResult;
        }

        /*lint -e534*/
        VOS_MemCpy(pucContent + usReadedLen, stRspData.aucRsp, ucP3);
        /*lint +e534*/
    }

    return USIMM_SW_OK;
}

/*****************************************************************************
�� �� ��  :USIMM_SendUnblockPinApdu
��������  :����UNBLOCK PIN�����APDU
�������  :enAppType:Ӧ������
           ucPinType:PIN������
           pucPukData:PUK������
           pucPinData:��PIN������
�������  :pstRspData:UNBLOCK PIN����ص�����
�� �� ֵ  :VOS_OK/VOS_ERR

�޶���¼  :
1. ��    ��   : 2015��4��7��
   ��    ��   : h00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendUnblockPinApdu(
    VOS_UINT8                           ucChannelID,
    VOS_UINT8                           ucPinType,
    VOS_UINT8                          *pucPukData,
    VOS_UINT8                          *pucPinData,
    USIMM_APDU_RSP_STRU                *pstRspData)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stPukData;
    USIMM_U8_LVDATA_STRU               *pstPinData = VOS_NULL_PTR;
    VOS_UINT8                           aucPukData[USIMM_PINNUMBER_LEN * 2];
    VOS_UINT8                           ucP3;

    if (VOS_NULL_PTR == pucPukData)
    {
        ucP3        = 0;
        pstPinData  = VOS_NULL_PTR;
    }
    else
    {
        ucP3        = USIMM_PINNUMBER_LEN * 2;
        pstPinData  = &stPukData;

        /*lint -e534 */
        /*���APDU��������*/
        VOS_MemCpy(aucPukData, pucPukData, USIMM_PINNUMBER_LEN);
        VOS_MemCpy(aucPukData + USIMM_PINNUMBER_LEN, pucPinData, USIMM_PINNUMBER_LEN);
        /*lint +e534 */

        stPukData.ulDataLen = ucP3;
        stPukData.pucData   = aucPukData;
    }

    stApduHead.ucChannel    = ucChannelID;
    stApduHead.ucINS        = CMD_INS_UNBLOCK_PIN;
    stApduHead.ucP1         = 0;
    stApduHead.ucP2         = ucPinType;
    stApduHead.ucP3         = ucP3;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    pstPinData,
                                    pstRspData);

    /* �жϷ��ͽ�� */
    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SendUnblockPinApdu:USIMM_SendAPDUHandle error");
    }

    return ulResult;
}

/*****************************************************************************
�� �� ��  :USIMM_SendChangePinApdu
��������  :����CHANGE PIN�����APDU
�������  :enAppType:Ӧ������
           ucPinType:PIN������
           pucData:��PIN������
           pucNewPinData:��PIN������
�������  :pstRspData:CHANGE PIN����ص�����
�� �� ֵ  :VOS_OK/VOS_ERR

�޶���¼  :
1. ��    ��   : 2015��4��7��
   ��    ��   : h00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendChangePinApdu(
    VOS_UINT8                           ucChannelID,
    VOS_UINT8                           ucPinType,
    VOS_UINT8                          *pucPinData,
    VOS_UINT8                          *pucNewPinData,
    USIMM_APDU_RSP_STRU                *pstRspData)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stPinData;
    VOS_UINT8                           aucPinData[USIMM_PINNUMBER_LEN * 2];

    stApduHead.ucChannel    = ucChannelID;
    stApduHead.ucINS        = CMD_INS_CHANGE_PIN;
    stApduHead.ucP1         = 0;
    stApduHead.ucP2         = ucPinType;
    stApduHead.ucP3         = USIMM_PINNUMBER_LEN * 2;

    /*lint -e534 */
    /*���APDU��������*/
    VOS_MemCpy(aucPinData, pucPinData, USIMM_PINNUMBER_LEN);

    VOS_MemCpy(aucPinData + USIMM_PINNUMBER_LEN, pucNewPinData, USIMM_PINNUMBER_LEN);
    /*lint +e534 */

    stPinData.ulDataLen = USIMM_PINNUMBER_LEN * 2;
    stPinData.pucData   = aucPinData;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    &stPinData,
                                    pstRspData);

    /* �жϷ��ͽ�� */
    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SendChangePinApdu:USIMM_SendAPDUHandle error");
    }

    return ulResult;
}

/*****************************************************************************
�� �� ��  :USIMM_SendVerifyPinApdu
��������  :����VERIFY PIN�����APDU
�������  :enAppType:Ӧ������
           ucCmdType:�������Ͳ���
           ucPinType:PIN������
           pucData:PIN�����ݣ�����Ϊ��
�������  :pstRspData:VERIFY PIN����ص�����
�� �� ֵ  :VOS_OK/VOS_ERR

�޶���¼  :
1. ��    ��   : 2015��4��7��
   ��    ��   : h00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendVerifyPinApdu(
    VOS_UINT8                           ucChannelID,
    VOS_UINT8                           ucCmdType,
    VOS_UINT8                           ucPinType,
    VOS_UINT8                          *pucPinData,
    USIMM_APDU_RSP_STRU                *pstRspData)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stPinData;
    USIMM_U8_LVDATA_STRU               *pstPinData;
    VOS_UINT8                           aucPinData[USIMM_PINNUMBER_LEN];
    VOS_UINT8                           ucP3;

    if (VOS_NULL_PTR == pucPinData)
    {
        ucP3 = VOS_NULL;

        pstPinData = VOS_NULL;
    }
    else
    {
        ucP3 = USIMM_PINNUMBER_LEN;

        /*lint -e534*/
        VOS_MemCpy(aucPinData, pucPinData, USIMM_PINNUMBER_LEN);
        /*lint +e534*/

        stPinData.ulDataLen = USIMM_PINNUMBER_LEN;
        stPinData.pucData   = aucPinData;

        pstPinData          = &stPinData;
    }

    stApduHead.ucChannel    = ucChannelID;
    stApduHead.ucINS        = ucCmdType;
    stApduHead.ucP1         = 0;
    stApduHead.ucP2         = ucPinType;
    stApduHead.ucP3         = ucP3;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    pstPinData,
                                    pstRspData);

    /* �жϷ��ͽ�� */
    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SendVerifyPinApdu:USIMM_SendAPDUHandle error");
    }

    return ulResult;
}

/*****************************************************************************
�� �� ��  :USIMM_SendBSChallengeApdu
��������  :����BASE STATION CHALLENGE�����APDU
�������  :enAppType:Ӧ������
           ucP3:P3����
           pucData:���ص�����
�������  :pstRspData:BASE STATION CHALLENGE����ص�����
�� �� ֵ  :VOS_OK/VOS_ERR

�޶���¼  :
1. ��    ��   : 2015��4��7��
   ��    ��   : h00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendBSChallengeApdu(
    VOS_UINT8                           ucChannelID,
    VOS_UINT8                           ucP3,
    VOS_UINT8                          *pucData,
    USIMM_APDU_RSP_STRU                *pstRspData)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stBSChallengeData;

    stApduHead.ucChannel    = ucChannelID;
    stApduHead.ucINS        = CMD_INS_BASE_STATION_CHALLENGE;
    stApduHead.ucP1         = 0;
    stApduHead.ucP2         = 0;
    stApduHead.ucP3         = ucP3;

    stBSChallengeData.ulDataLen    = ucP3;
    stBSChallengeData.pucData      = pucData;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    &stBSChallengeData,
                                    pstRspData);

    /* �жϷ��ͽ�� */
    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SendBSChallengeApdu:USIMM_SendAPDUHandle error");
    }

    return ulResult;
}
VOS_UINT32 USIMM_SendTerminalCapabilityApdu(
    VOS_UINT8                           ucP1,
    VOS_UINT8                           ucP2,
    USIMM_TERMINAL_CAPABILITY_STRU     *pstTerminalCapability)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stApduData;
    USIMM_APDU_RSP_STRU                 stRspData;

    /*lint -e534*/
    VOS_MemSet(&stApduHead, 0, sizeof(USIMM_APDU_HEAD_STRU));
    VOS_MemSet(&stApduData, 0, sizeof(stApduData));
    VOS_MemSet(&stRspData,  0, sizeof(stRspData));
    /*lint +e534*/

    /* ʹ����ͨ�� */
    stApduHead.ucChannel    = USIMM_BASE_CHANNEL_NUM;
    stApduHead.ucP1         = ucP1;
    stApduHead.ucP2         = ucP1;
    stApduHead.ucP3         = (VOS_UINT8)pstTerminalCapability->ulLen;
    stApduHead.ucINS        = CMD_INS_TERMINAL_CAPABILITY;

    stApduData.ulDataLen    = pstTerminalCapability->ulLen;

    stApduData.pucData      = pstTerminalCapability->aucData;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    &stApduData,
                                    &stRspData);

    return ulResult;
}

/*****************************************************************************
�� �� ��  :USIMM_SendGenerateKeyVpmApdu
��������  :����GENERATE KEY VPM �����APDU
�������  :enAppType:Ӧ������
           ucP3:P3����
           pucData:���ص�����
�������  :pstRspData:GENERATE KEY VPM����ص�����
�� �� ֵ  :VOS_OK/VOS_ERR

�޶���¼  :
1. ��    ��   : 2015��4��9��
   ��    ��   : h00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendGenerateKeyVpmApdu(
    VOS_UINT8                           ucChannelID,
    VOS_UINT8                           ucP3,
    VOS_UINT8                          *pucData,
    USIMM_APDU_RSP_STRU                *pstRspData)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stGenerateKeyVpmData;

    stApduHead.ucChannel    = ucChannelID;
    stApduHead.ucINS        = CMD_INS_GENERATE_KEY;
    stApduHead.ucP1         = 0;
    stApduHead.ucP2         = 0;
    stApduHead.ucP3         = ucP3;

    stGenerateKeyVpmData.ulDataLen    = ucP3;
    stGenerateKeyVpmData.pucData      = pucData;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    &stGenerateKeyVpmData,
                                    pstRspData);

    /* �жϷ��ͽ�� */
    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SendGenerateKeyVpmApdu:USIMM_SendAPDUHandle error");
    }

    return ulResult;
}

/*****************************************************************************
�� �� ��  :USIMM_SendUpdateSsdApdu
��������  :����UPDATE SSD�����APDU
�������  :enAppType:Ӧ������
           ucP3:P3����
           pucData:���ص�����
�������  :pstRspData:UPDATE SSD����ص�����
�� �� ֵ  :VOS_OK/VOS_ERR

�޶���¼  :
1. ��    ��   : 2015��4��9��
   ��    ��   : h00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendUpdateSsdApdu(
    VOS_UINT8                           ucP3,
    VOS_UINT8                          *pucData)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stUpdateSsdData;

    stApduHead.ucChannel    = USIMM_APDU_BASECHANNEL;
    stApduHead.ucINS        = CMD_INS_UPDATE_SSD;
    stApduHead.ucP1         = 0;
    stApduHead.ucP2         = 0;
    stApduHead.ucP3         = ucP3;

    stUpdateSsdData.ulDataLen    = ucP3;
    stUpdateSsdData.pucData      = pucData;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_UIM,
                                    &stApduHead,
                                    &stUpdateSsdData,
                                    VOS_NULL_PTR);

    /* �жϷ��ͽ�� */
    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SendUpdateSsdApdu:USIMM_SendAPDUHandle error");
    }

    return ulResult;
}

/*****************************************************************************
�� �� ��  :USIMM_SendConfirmSsdApdu
��������  :����CONFIRM SSD�����APDU
�������  :enAppType:Ӧ������
           ucP3:P3����
           pucData:���ص�����
�������  :pstRspData:UPDATE SSD����ص�����
�� �� ֵ  :VOS_OK/VOS_ERR

�޶���¼  :
1. ��    ��   : 2015��4��9��
   ��    ��   : h00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendConfirmSsdApdu(
    VOS_UINT8                           ucP3,
    VOS_UINT8                          *pucData)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stConfirmData;

    stApduHead.ucChannel    = USIMM_APDU_BASECHANNEL;
    stApduHead.ucINS        = CMD_INS_CONFIRM_SSD;
    stApduHead.ucP1         = 0;
    stApduHead.ucP2         = 0;
    stApduHead.ucP3         = ucP3;

    stConfirmData.ulDataLen = ucP3;
    stConfirmData.pucData   = pucData;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_UIM,
                                    &stApduHead,
                                    &stConfirmData,
                                    VOS_NULL_PTR);

    /* �жϷ��ͽ�� */
    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SendUpdateSsdApdu:USIMM_SendAPDUHandle error");
    }

    return ulResult;
}

/*****************************************************************************
�� �� ��  :USIMM_SendManageSsdApdu
��������  :����MANAGE SSD�����APDU
�������  :enAppType:Ӧ������
           ucP2:P2����
           ucP3:P3����
           pucData:���ص�����
�������  :pstRspData:UPDATE SSD����ص�����
�� �� ֵ  :VOS_OK/VOS_ERR

�޶���¼  :
1. ��    ��   : 2015��4��9��
   ��    ��   : h00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendManageSsdApdu(
    VOS_UINT8                           ucChannelID,
    VOS_UINT8                           ucP2,
    VOS_UINT8                           ucP3,
    VOS_UINT8                          *pucData)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stConfirmData;

    stApduHead.ucChannel    = ucChannelID;
    stApduHead.ucINS        = CMD_INS_MANAGE_SSD;
    stApduHead.ucP1         = 0;
    stApduHead.ucP2         = ucP2;
    stApduHead.ucP3         = ucP3;

    stConfirmData.ulDataLen = ucP3;
    stConfirmData.pucData   = pucData;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_CSIM,
                                    &stApduHead,
                                    &stConfirmData,
                                    VOS_NULL_PTR);

    /* �жϷ��ͽ�� */
    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SendManageSsdApdu:USIMM_SendAPDUHandle error");
    }

    return ulResult;
}

/*****************************************************************************
�� �� ��  :USIMM_SendAuthenticationApdu
��������  :����AUTHENTICAION�����APDU
�������  :enAppType:Ӧ������
           ucP1:P1����
           ucP2:P2����
           ucP3:P3����
           pucData:���ص�����
�������  :pstRspData:STATUS����ص�FCP����
�� �� ֵ  :VOS_OK/VOS_ERR

�޶���¼  :
1. ��    ��   : 2015��3��7��
    ��    ��   : h00300778
    �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendAuthenticationApdu(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT8                           ucP1,
    VOS_UINT8                           ucP2,
    VOS_UINT8                           ucP3,
    VOS_UINT8                          *pucData,
    USIMM_APDU_RSP_STRU                *pstRspData)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stAuthData;
    VOS_UINT32                          ulChannelNo;

    ulChannelNo = USIMM_CCB_GetAppChNO(enAppType);

    if (VOS_NULL_BYTE == ulChannelNo)
    {
        return VOS_ERR;
    }

    stApduHead.ucChannel    = (VOS_UINT8)ulChannelNo;
    stApduHead.ucINS        = CMD_INS_AUTHENTICATE;
    stApduHead.ucP1         = ucP1;
    stApduHead.ucP2         = ucP2;
    stApduHead.ucP3         = ucP3;

    stAuthData.ulDataLen    = ucP3;
    stAuthData.pucData      = pucData;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    &stAuthData,
                                    pstRspData);

    /* �жϷ��ͽ�� */
    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SendAuthenticationApdu:USIMM_SendAPDUHandle error");
    }

    return ulResult;
}
VOS_UINT32 USIMM_SendDeactivateApdu(
    VOS_UINT8                           ucChannelID)
{
    USIMM_APDU_HEAD_STRU                stApduHead;

    stApduHead.ucChannel    = ucChannelID;
    stApduHead.ucINS        = CMD_INS_DEACTIVATE_FILE;
    stApduHead.ucP1         = 0x00;
    stApduHead.ucP2         = 0x00;
    stApduHead.ucP3         = 0x00;

    return USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                &stApduHead,
                                VOS_NULL_PTR,
                                VOS_NULL_PTR);   /*������·�㴦����*/
}
VOS_UINT32 USIMM_SendActivateApdu(
    VOS_UINT8                           ucChannelID)
{
    USIMM_APDU_HEAD_STRU                stApduHead;

    stApduHead.ucChannel    = ucChannelID;

    stApduHead.ucINS        = CMD_INS_ACTIVATE_FILE;
    stApduHead.ucP1         = 0x00;
    stApduHead.ucP2         = 0x00;
    stApduHead.ucP3         = 0x00;

    return USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                &stApduHead,
                                VOS_NULL_PTR,
                                VOS_NULL_PTR);   /*������·�㴦����*/
}
VOS_UINT32 USIMM_SendTermimalProfileDownloadApdu(
    VOS_UINT8                           ucLen,
    VOS_UINT8                          *pucData
)
{
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stApduData;

    /*lint -e534*/
    VOS_MemSet(&stApduHead, 0, sizeof(USIMM_APDU_HEAD_STRU));
    VOS_MemSet(&stApduData, 0, sizeof(stApduData));
    /*lint +e534*/

    /* ʹ����ͨ�� */
    stApduHead.ucChannel    = USIMM_BASE_CHANNEL_NUM;
    stApduHead.ucP1         = 0;
    stApduHead.ucP2         = 0;
    stApduHead.ucP3         = ucLen;
    stApduHead.ucINS        = CMD_INS_TERMINAL_PROFILE;

    stApduData.ulDataLen    = ucLen;

    stApduData.pucData      = pucData;

    return USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                &stApduHead,
                                &stApduData,
                                VOS_NULL_PTR);
}
VOS_UINT32 USIMM_SendStoreESNMEIDApdu(
    UICC_STORE_ESN_MEID_P1_UINT8        enDataType,
    VOS_UINT8                           ucChannelID,
    VOS_UINT8                          *pucData,
    USIMM_APDU_RSP_STRU                *pstRspData
)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stApduData;

    /*lint -e534*/
    VOS_MemSet(&stApduHead, 0, sizeof(USIMM_APDU_HEAD_STRU));
    VOS_MemSet(&stApduData, 0, sizeof(stApduData));
    /*lint +e534*/

    /* ʹ����ͨ�� */
    stApduHead.ucChannel    = ucChannelID;
    stApduHead.ucP1         = enDataType;
    stApduHead.ucP2         = 0;
    stApduHead.ucP3         = USIMM_STORE_ESNMEID_MAX;
    stApduHead.ucINS        = CMD_INS_STORE_ESNMEID;

    stApduData.ulDataLen    = USIMM_STORE_ESNMEID_MAX;

    stApduData.pucData      = pucData;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    &stApduData,
                                    pstRspData);

    return ulResult;

}

/*****************************************************************************
�� �� ��  : USIMM_SendComputIPApdu
��������  : �·�ComputeIP����
�������  : ucLen
            pucData
�������  : ��
�� �� ֵ  : VOS_ERR
           VOS_OK
�޶���¼  :
1. ��    ��   : 2015��06��10��
   ��    ��   : zhuli
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendComputeIPApdu(
    VOS_UINT8                           ucChannelID,
    USIMM_COMPUTEIP_AUTH_ENUM_UINT32	enP1,
    VOS_UINT8                           ucP2,
    USIMM_U8_DATA_STRU                 *pstCmdData,
    USIMM_APDU_RSP_STRU                *pstRspData)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stApduData;

    /*lint -e534*/
    VOS_MemSet(&stApduHead, 0, sizeof(USIMM_APDU_HEAD_STRU));
    VOS_MemSet(&stApduData, 0, sizeof(stApduData));
    /*lint +e534*/

    /* ʹ����ͨ�� */
    stApduHead.ucChannel    = ucChannelID;
    stApduHead.ucP1         = (VOS_UINT8)enP1;
    stApduHead.ucP2         = ucP2;
    stApduHead.ucP3         = pstCmdData->ucDataLen;
    stApduHead.ucINS        = CMD_INS_COMPUTE_IP_AUTH;

    stApduData.ulDataLen    = pstCmdData->ucDataLen;

    stApduData.pucData      = pstCmdData->aucData;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_CSIM,
                                    &stApduHead,
                                    &stApduData,
                                    pstRspData);

    return ulResult;
}

/*****************************************************************************
�� �� ��  : USIMM_SendBCMCSApdu
��������  : �·�BCMCS����
�������  : ucLen
            pucData
�������  : ��
�� �� ֵ  : VOS_ERR
           VOS_OK
�޶���¼  :
1. ��    ��   : 2015��06��10��
   ��    ��   : zhuli
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendBCMCSApdu(
    VOS_UINT8                           ucChannelID,
    USIMM_BCMCS_AUTH_ENUM_UINT32	    enP1,
    USIMM_U8_DATA_STRU                 *pstCmdData,
    USIMM_APDU_RSP_STRU                *pstRspData)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stApduData;

    /*lint -e534*/
    VOS_MemSet(&stApduHead, 0, sizeof(USIMM_APDU_HEAD_STRU));
    VOS_MemSet(&stApduData, 0, sizeof(stApduData));
    /*lint +e534*/

    /* ʹ����ͨ�� */
    stApduHead.ucChannel    = ucChannelID;
    stApduHead.ucP1         = (VOS_UINT8)enP1;
    stApduHead.ucP2         = VOS_NULL;
    stApduHead.ucP3         = pstCmdData->ucDataLen;
    stApduHead.ucINS        = CMD_INS_BCMCS;

    stApduData.ulDataLen    = pstCmdData->ucDataLen;

    stApduData.pucData      = pstCmdData->aucData;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    &stApduData,
                                    pstRspData);

    /*SW��Ҫ�����ж�*/
    if (USIMM_BCMCS_DELETEBAK == enP1)
    {
        if ((0x94 == pstRspData->ucSW1)
           &&(0x02 == pstRspData->ucSW2))
        {
            ulResult = USIMM_SW_INVALID_BAKID;
        }

        if ((0x94 == pstRspData->ucSW1)
           &&(0x04 == pstRspData->ucSW2))
        {
            ulResult = USIMM_SW_INVALID_BCMCSFID;
        }
    }

    return ulResult;
}

/*****************************************************************************
�� �� ��  : USIMM_SendAppAuthApdu
��������  : �·�CDMA APP Auth����
�������  : ucLen
            pucData
�������  : ��
�� �� ֵ  : VOS_ERR
           VOS_OK
�޶���¼  :
1. ��    ��   : 2015��06��10��
   ��    ��   : zhuli
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_SendAppAuthApdu(
    VOS_UINT8                           ucChannelID,
    USIMM_U8_DATA_STRU                 *pstCmdData,
    USIMM_APDU_RSP_STRU                *pstRspData)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_HEAD_STRU                stApduHead;
    USIMM_U8_LVDATA_STRU                stApduData;

    /*lint -e534*/
    VOS_MemSet(&stApduHead, 0, sizeof(USIMM_APDU_HEAD_STRU));
    VOS_MemSet(&stApduData, 0, sizeof(stApduData));
    /*lint +e534*/

    /* ʹ����ͨ�� */
    stApduHead.ucChannel    = ucChannelID;
    stApduHead.ucP1         = VOS_NULL;
    stApduHead.ucP2         = VOS_NULL;
    stApduHead.ucP3         = pstCmdData->ucDataLen;
    stApduHead.ucINS        = CMD_INS_APP_AUTH;

    stApduData.ulDataLen    = pstCmdData->ucDataLen;

    stApduData.pucData      = pstCmdData->aucData;

    ulResult = USIMM_SendAPDUHandle(USIMM_APDUCMD_COMMON,
                                    &stApduHead,
                                    &stApduData,
                                    pstRspData);

    return ulResult;
}

#else

#include "usimmapdu.h"
#include "usimmdl.h"
#include "usimmt1dl.h"
#include "usimmglobal.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_USIMM_APDUMODULE_C
/*lint +e767*/


VOS_UINT32 USIMM_CheckSW(USIMM_APDU_ST *pstUSIMMAPDU)
{
    USIMM_SWCHECK_ST                   *pstSWCheck;
    VOS_UINT32                          ulLen;
    VOS_UINT32                          i;
    VOS_UINT8                           ucSW1;
    VOS_UINT8                           ucSW2;
    USIMM_SWCHECK_ENUM_UINT16           enResult = USIMM_SW_OTHER_ERROR;

    ucSW1 = pstUSIMMAPDU->ucSW1;
    ucSW2 = pstUSIMMAPDU->ucSW2;

    if (USIMM_SIM_CLA == pstUSIMMAPDU->aucAPDU[CLA])  /*���ݿ������ж�*/
    {
        pstSWCheck = gausSimSWCheck;

        ulLen      = USIMM_SIMSW_MAXNUMBER;
    }
    else
    {
        pstSWCheck = gausUsimSWCheck;

        ulLen      = USIMM_USIMSW_MAXNUMBER;
    }

    for(i=0; i<ulLen; i++)
    {
        if(pstSWCheck[i].ucSW1 != ucSW1)        /*���ж�SW1ƥ��*/
        {
            continue;
        }

        if((0xC0 == (ucSW2&0xF0))&&(0x63 == pstSWCheck[i].ucSW1))
        {
            if ((CMD_INS_VERIFY         == pstUSIMMAPDU->aucAPDU[INS])
                ||(CMD_INS_CHANGE_PIN   == pstUSIMMAPDU->aucAPDU[INS])
                ||(CMD_INS_UNBLOCK_PIN  == pstUSIMMAPDU->aucAPDU[INS])
                ||(CMD_INS_DISABLE_PIN  == pstUSIMMAPDU->aucAPDU[INS])
                ||(CMD_INS_ENABLE_PIN   == pstUSIMMAPDU->aucAPDU[INS]))
            {
                enResult = pstSWCheck[i].enResult;
            }
            else
            {
                enResult = USIMM_SW_WARNING;
            }

            break;
        }

        if((0xFF == pstSWCheck[i].ucSW2)||(ucSW2 == pstSWCheck[i].ucSW2))/*����Ҫ�ж�SW2����SW2ƥ��*/
        {
            enResult = pstSWCheck[i].enResult;

            break;
        }
    }

    if (USIMM_SW_OK_WITH_SAT == enResult)    /*SAT��Ҫ���⴦��*/
    {
        USIMM_INFO_LOG("USIMM_CheckSW: There is SAT Data Need Fetch");

        gstUSIMMBaseInfo.enSATState = USIMM_SAT_STATE_NEEDFETCH;

        if (0x00 == ucSW2)           /*����ǰ��ȡ���������256*/
        {
            gstUSIMMBaseInfo.usSATLen = 0x100;
        }
        else
        {
            gstUSIMMBaseInfo.usSATLen = ucSW2;
        }

        enResult = USIMM_SW_OK;
    }

    if (VOS_TRUE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulAtt_flg)
    {
        if ((0x6F == ucSW1)&&(0x00 == ucSW2))
        {
            g_ulATTSpecErrSWCnt++;
        }
        else
        {
            g_ulATTSpecErrSWCnt = 0;
        }

        if (g_ulATTSpecErrSWCnt >= 3)                                 /*��������3���ϱ��޿�*/
        {
            gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType        = USIMM_CARD_NOCARD;        /*��ǰ״̬Ϊ�޿�*/
            gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService     = USIMM_CARD_SERVIC_ABSENT; /*��ǰ״̬Ϊ�޿�*/

            gastUSIMMCardAppInfo[USIMM_UICC_USIM].enStateChange     = USIMM_CARD_STATE_CHANGED;
        }
    }

    return (VOS_UINT32)enResult;
}


VOS_UINT32 USIMM_SelectFileByChannelID_APDU(VOS_UINT8 ucChannelID, USIMM_APDU_ST *pstApduInfo)
{
    VOS_UINT32                          ulResult;

    pstApduInfo->aucAPDU[CLA]   = pstApduInfo->aucAPDU[CLA]|ucChannelID; /*���APDU����ͷ*/

    pstApduInfo->aucAPDU[INS]   = CMD_INS_SELECT;

    pstApduInfo->ulLcValue      = pstApduInfo->aucAPDU[P3];                  /*���������������*/

    if(USIMM_SELECT_RETURN_FCP_TEMPLATE == pstApduInfo->aucAPDU[P2])
    {
        /* ���ֳ�����Ϊcase4 */
        pstApduInfo->ulLeValue      = USIMM_LE_MAX_LEN;
    }
    else
    {
        /* case3 */
        pstApduInfo->ulLeValue      = VOS_NULL;
    }

    ulResult = USIMM_DLHandle(pstApduInfo);/*������·�㴦����*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_SelectFile_APDU:USIMM_DLHandle error");

        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 USIMM_SelectFile_APDU(USIMM_APDU_ST   *pstApduInfo)
{
    return USIMM_SelectFileByChannelID_APDU(0, pstApduInfo);
}


VOS_UINT32 USIMM_ReselectFileAPDU(USIMM_APDU_ST   *pstApduInfo)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulResult;

    for (ulIndex = 0; ulIndex < USIMM_SELECT_MAX_TIME; ulIndex++)
    {
        /* ����FCP�����������������ô�FCP�ķ�ʽ���� */
        if ((USIMM_SELECT_NO_DATA_RETURNED == pstApduInfo->aucAPDU[P2])
            && ((USIMM_SELECT_MAX_TIME - 1) == ulIndex))
        {
            pstApduInfo->aucAPDU[P2] = USIMM_SELECT_RETURN_FCP_TEMPLATE;
        }

        ulResult = USIMM_SelectFile_APDU(pstApduInfo);

        if (VOS_OK != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_ReselectFileAPDU: USIMM_SelectFile_APDU fail.");

            return USIMM_SW_SENDCMD_ERROR;
        }

        ulResult = USIMM_CheckSW(pstApduInfo);

        /* ״̬��ΪWarning��Technical Problem���ٴν���ѡ�ļ����� */
        if ((USIMM_SW_WARNING == ulResult) || (USIMM_SW_TECH_ERROR == ulResult))
        {
            continue;
        }

        break;
    }

    return ulResult;
}


VOS_UINT32 USIMM_StatusByChannelID_APDU(VOS_UINT8 ucChannelID, VOS_UINT8 ucP1,VOS_UINT8 ucP2,VOS_UINT8 ucP3)
{
    VOS_UINT32 ulResult;

    gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA|ucChannelID|0x80; /*���APDU����ͷ*/

    gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_STATUS;

    gstUSIMMAPDU.aucAPDU[P1]  = ucP1;

    gstUSIMMAPDU.aucAPDU[P2]  = ucP2;

    gstUSIMMAPDU.aucAPDU[P3]  = ucP3;

    gstUSIMMAPDU.ulLcValue = 0x00;                              /*���������������*/

    if((ucP3 == 0x00)&&(ucP2 != 0x0C))
    {
        gstUSIMMAPDU.ulLeValue = 0x100;
    }
    else
    {
        gstUSIMMAPDU.ulLeValue = ucP3;
    }


    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*������·�㴦����*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_STATUS_APDU: USIMM_DLHandle is Failed");/*��ӡ����*/

        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 USIMM_Status_APDU(VOS_UINT8 ucP1,VOS_UINT8 ucP2,VOS_UINT8 ucP3)
{
    return USIMM_StatusByChannelID_APDU(0, ucP1, ucP2, ucP3);
}


VOS_UINT32 USIMM_ReadBinary_APDU(VOS_UINT16 usOffset, VOS_UINT8 ucP3)
{
    /* Add by H00300778 for MultiAppSync Begin 2015-05-12 */
    VOS_UINT32                          ulResult;
    VOS_UINT32                          i;

    (VOS_VOID)VOS_MemSet(&gstUSIMMAPDU, 0, sizeof(gstUSIMMAPDU));

    for (i = 0; i < 2; i++)
    {
        gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA; /*���APDU����ͷ*/

        gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_READ_BINARY;

        gstUSIMMAPDU.aucAPDU[P1]  = (VOS_UINT8)((usOffset>>8)&0xFF);

        gstUSIMMAPDU.aucAPDU[P2]  = (VOS_UINT8)(usOffset&0xFF);

        gstUSIMMAPDU.aucAPDU[P3]  = ucP3;

        gstUSIMMAPDU.ulLcValue    = 0x00;           /*���������������*/

        gstUSIMMAPDU.ulLeValue    = ucP3;

        ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*������·�㴦����*/

        if (USIMM_DL_SUCESS != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_Status_APDU: USIMM_DLHandle is Failed");/*��ӡ����*/

            continue;
        }

        ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

        if (USIMM_SW_OK != ulResult)
        {
            continue;
        }
        else
        {
            break;
        }
    }

    /* Add by H00300778 for MultiAppSync End 2015-05-12 */

    return VOS_OK;
}


VOS_UINT32 USIMM_UpdateBinary_APDU(VOS_UINT16 usOffset, VOS_UINT8 ucP3, VOS_UINT8* pucData)
{
    /* Add by H00300778 for MultiAppSync Begin 2015-05-12 */
    VOS_UINT32                          ulResult;
    VOS_UINT32                          i;

    for (i = 0; i < 2; i++)
    {
        /*���APDU����ͷ*/
        gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA;

        gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_UPDATE_BINARY;

        gstUSIMMAPDU.aucAPDU[P1]  = (VOS_UINT8)((usOffset>>0x08)&0xFF);

        gstUSIMMAPDU.aucAPDU[P2]  = (VOS_UINT8)(usOffset&0xFF);

        gstUSIMMAPDU.aucAPDU[P3]  = ucP3;

        /*lint -e534*/
        VOS_MemCpy(gstUSIMMAPDU.aucSendBuf, pucData, ucP3);/*���APDU��������*/
        /*lint +e534*/

        gstUSIMMAPDU.ulLcValue   = ucP3;                  /*���������������*/

        gstUSIMMAPDU.ulLeValue   = 0x00;

        ulResult = USIMM_DLHandle(&gstUSIMMAPDU);/*������·�㴦����*/

        if(USIMM_DL_SUCESS != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_UpdateBinary_APDU: USIMM_DLHandle is Failed");/*��ӡ����*/

            continue;
        }

        ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

        if (USIMM_SW_OK != ulResult)
        {
            continue;
        }
        else
        {
            break;
        }
    }
    /* Add by H00300778 for MultiAppSync End 2015-05-12 */

    return VOS_OK;
}
VOS_UINT32 USIMM_ReadRecord_APDU(VOS_UINT8 ucRecordNum, VOS_UINT8 ucMode, VOS_UINT8 ucLen)
{
    /* Add by H00300778 for MultiAppSync Begin 2015-05-12 */
    VOS_UINT32                          ulResult;
    VOS_UINT32                          i;

    (VOS_VOID)VOS_MemSet(&gstUSIMMAPDU, 0, sizeof(gstUSIMMAPDU));

    for (i = 0; i < 2; i++)
    {
        gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA; /*���APDU����ͷ*/

        gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_READ_RECORD;

        gstUSIMMAPDU.aucAPDU[P1]  = ucRecordNum;

        gstUSIMMAPDU.aucAPDU[P2]  = ucMode;

        gstUSIMMAPDU.aucAPDU[P3]  = ucLen;

        gstUSIMMAPDU.ulLcValue    = 0x00;           /*���������������*/

        gstUSIMMAPDU.ulLeValue    = ucLen;

        ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*������·�㴦����*/

        if (USIMM_DL_SUCESS != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_ReadRecord_APDU: USIMM_DLHandle is Failed");/*��ӡ����*/

            continue;
        }

        ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

        if (USIMM_SW_OK != ulResult)
        {
            continue;
        }
        else
        {
            break;
        }
    }
    /* Add by H00300778 for MultiAppSync End 2015-05-12 */

    return VOS_OK;
}


VOS_UINT32 USIMM_UpdateRecord_APDU(VOS_UINT8 ucRecordNum, VOS_UINT8 ucMode, VOS_UINT8 ucLen, VOS_UINT8* pucData)
{
    /* Add by H00300778 for MultiAppSync Begin 2015-05-12 */
    VOS_UINT32                          ulResult;
    VOS_UINT32                          i;


    for (i = 0; i < 2; i++)
    {
        gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA; /*���APDU����ͷ*/

        gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_UPDATE_RECORD;

        gstUSIMMAPDU.aucAPDU[P1]  = ucRecordNum;

        gstUSIMMAPDU.aucAPDU[P2]  = ucMode;

        gstUSIMMAPDU.aucAPDU[P3]  = ucLen;

        /*lint -e534*/
        VOS_MemCpy(gstUSIMMAPDU.aucSendBuf, pucData, ucLen);/*���APDU��������*/
        /*lint +e534*/

        gstUSIMMAPDU.ulLcValue = ucLen;                              /*���������������*/

        gstUSIMMAPDU.ulLeValue = 0x00;

        ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*������·�㴦����*/

        if(USIMM_DL_SUCESS != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_UpdateRecord_APDU: USIMM_DLHandle is Failed");/*��ӡ����*/

            continue;
        }

        ulResult = USIMM_CheckSW(&gstUSIMMAPDU);

        if (USIMM_SW_OK != ulResult)
        {
            continue;
        }
        else
        {
            break;
        }
    }
    /* Add by H00300778 for MultiAppSync End 2015-05-12 */

    return VOS_OK;
}
VOS_UINT32 USIMM_Search_APDU(VOS_UINT8 ucP1, VOS_UINT8 ucP2, VOS_UINT8 ucP3, VOS_UINT8* pucData)
{
    VOS_UINT32 ulResult;

    gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA; /*���APDU����ͷ*/

    gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_SEARCH_RECORD;

    gstUSIMMAPDU.aucAPDU[P1]  = ucP1;

    gstUSIMMAPDU.aucAPDU[P2]  = ucP2;

    gstUSIMMAPDU.aucAPDU[P3]  = ucP3;

    /*lint -e534*/
    VOS_MemCpy(gstUSIMMAPDU.aucSendBuf, pucData, ucP3);/*���APDU��������*/
    /*lint +e534*/

    gstUSIMMAPDU.ulLcValue = ucP3;                              /*���������������*/

    gstUSIMMAPDU.ulLeValue = 0x00;

    /* ���ֳ�����Ϊcase4 */
    gstUSIMMAPDU.ulLeValue = USIMM_LE_MAX_LEN;

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*������·�㴦����*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_Search_APDU: USIMM_DLHandle is Failed");/*��ӡ����*/

        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 USIMM_Increase_APDU(VOS_UINT8 ucLen, VOS_UINT8* pucData)
{
    VOS_UINT32 ulResult;

    gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA; /*���APDU����ͷ*/

    gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_INCREASE;

    gstUSIMMAPDU.aucAPDU[P1]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P2]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P3]  = ucLen;

    /*lint -e534*/
    VOS_MemCpy(gstUSIMMAPDU.aucSendBuf, pucData, ucLen);/*���APDU��������*/
    /*lint +e534*/

    gstUSIMMAPDU.ulLcValue = ucLen;                              /*���������������*/

    /* ���ֳ�����Ϊcase4 */
    gstUSIMMAPDU.ulLeValue = USIMM_LE_MAX_LEN;

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*������·�㴦����*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_Increase_APDU: USIMM_DLHandle is Failed");/*��ӡ����*/

        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 USIMM_PINVerify_APDU(VOS_UINT8 ucCmdType,VOS_UINT8 ucPINType, VOS_UINT8* pucPINData)
{
    VOS_UINT32 ulResult;
    VOS_UINT8  ucLen;

    if(VOS_NULL_PTR == pucPINData)  /*��ȡ��ǰ��PINʣ�����*/
    {
        ucLen = 0x00;
    }
    else                                                /*У��PIN*/
    {
        ucLen = 0x08;
    }

    gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA; /*���APDU����ͷ*/

    gstUSIMMAPDU.aucAPDU[INS] = ucCmdType;

    gstUSIMMAPDU.aucAPDU[P1]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P2]  = ucPINType;

    gstUSIMMAPDU.aucAPDU[P3]  = ucLen;

    if(8 == ucLen)
    {
        VOS_MemCpy(gstUSIMMAPDU.aucSendBuf, pucPINData, 0x08);/*���APDU��������*/
    }

    gstUSIMMAPDU.ulLcValue = ucLen;                              /*���������������*/

    gstUSIMMAPDU.ulLeValue = 0x00;

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*������·�㴦����*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_PINVerify_APDU: USIMM_DLHandle is Failed");/*��ӡ����*/

        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 USIMM_ChangePIN_APDU(VOS_UINT8 ucPINType, VOS_UINT8* pucOldPIN, VOS_UINT8* pucNewPIN)
{
    VOS_UINT32 ulResult;

    gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA; /*���APDU����ͷ*/

    gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_CHANGE_PIN;

    gstUSIMMAPDU.aucAPDU[P1]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P2]  = ucPINType;

    gstUSIMMAPDU.aucAPDU[P3]  = 0x10;

    /*lint -e534*/
    VOS_MemCpy(&gstUSIMMAPDU.aucSendBuf[0], pucOldPIN, 0x08);/*���APDU��������*/

    VOS_MemCpy(&gstUSIMMAPDU.aucSendBuf[8], pucNewPIN, 0x08);
    /*lint +e534*/

    gstUSIMMAPDU.ulLcValue = 0x10;                              /*���������������*/

    gstUSIMMAPDU.ulLeValue = 0x00;

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*������·�㴦����*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_ChangePIN_APDU: USIMM_DLHandle is Failed");/*��ӡ����*/

        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 USIMM_UnblockPIN_APDU(VOS_UINT8 ucPINType, VOS_UINT8* pucPUKData, VOS_UINT8* pucPINData)
{
    VOS_UINT32 ulResult;
    VOS_UINT8  ucP3;

    if(VOS_NULL_PTR == pucPUKData)
    {
        ucP3 = 0x00;
    }
    else
    {
        ucP3 = 0x10;
    }

    gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA; /*���APDU����ͷ*/

    gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_UNBLOCK_PIN;

    gstUSIMMAPDU.aucAPDU[P1]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P2]  = ucPINType;

    gstUSIMMAPDU.aucAPDU[P3]  = ucP3;

    if(0x00  != ucP3)
    {
        VOS_MemCpy(&gstUSIMMAPDU.aucSendBuf[0], pucPUKData, 0x08);/*���APDU��������*/

        VOS_MemCpy(&gstUSIMMAPDU.aucSendBuf[8], pucPINData, 0x08);
        /*lint +e534*/
    }

    gstUSIMMAPDU.ulLcValue = ucP3;                              /*���������������*/

    gstUSIMMAPDU.ulLeValue = 0;

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*������·�㴦����*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_UnblockPIN_APDU: USIMM_DLHandle is Failed");/*��ӡ����*/

        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 USIMM_DeactivateFile_APDU(VOS_VOID)
{
    VOS_UINT32 ulResult;

    gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA; /*���APDU����ͷ*/

    gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_DEACTIVATE_FILE;

    gstUSIMMAPDU.aucAPDU[P1]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P2]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P3]  = 0x00;

    gstUSIMMAPDU.ulLcValue    = 0x00;                /*���������������*/

    gstUSIMMAPDU.ulLeValue    = 0x00;

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*������·�㴦����*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_DeactivateFile_APDU: USIMM_DLHandle is Failed");/*��ӡ����*/

        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 USIMM_ActivateFile_APDU(VOS_VOID)
{
    VOS_UINT32 ulResult;

    gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA; /*���APDU����ͷ*/

    gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_ACTIVATE_FILE;

    gstUSIMMAPDU.aucAPDU[P1]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P2]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P3]  = 0x00;

    gstUSIMMAPDU.ulLcValue    = 0x00;           /*���������������*/

    gstUSIMMAPDU.ulLeValue    = 0x00;

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*������·�㴦����*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_ActivateFile_APDU: USIMM_DLHandle is Failed");/*��ӡ����*/

        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 USIMM_Authentication_APDU(VOS_UINT8 ucP1, VOS_UINT8 ucMode, VOS_UINT8 *pucData, VOS_UINT32 ulDataLen)
{
    VOS_UINT32                          ulResult;

    /* ������� */
    if (USIMM_APDU_MAXLEN <= ulDataLen)
    {
        USIMM_ERROR_LOG("USIMM_Authentication_APDU: ulDataLen is too big.");

        return VOS_ERR;
    }

    gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA; /*���APDU����ͷ*/

    gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_AUTHENTICATE;

    gstUSIMMAPDU.aucAPDU[P1]  = ucP1;

    gstUSIMMAPDU.aucAPDU[P2]  = ucMode;

    gstUSIMMAPDU.aucAPDU[P3]  = (VOS_UINT8)ulDataLen;

    /*lint -e534*/
    VOS_MemCpy(&gstUSIMMAPDU.aucSendBuf[0], pucData, ulDataLen);/*������������*/
    /*lint +e534*/

    gstUSIMMAPDU.ulLcValue = gstUSIMMAPDU.aucAPDU[P3];      /*���������������*/

    /* ���ֳ�����Ϊcase4 */
    gstUSIMMAPDU.ulLeValue = USIMM_LE_MAX_LEN;

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*������·�㴦����*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_Authentication_APDU: USIMM_DLHandle is Failed");/*��ӡ����*/

        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 USIMM_TermimalProfile_APDU(VOS_UINT8 ucLen, VOS_UINT8* pucData)
{
    VOS_UINT32 ulResult;

    gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA|0x80; /*���APDU����ͷ*/

    gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_TERMINAL_PROFILE;

    gstUSIMMAPDU.aucAPDU[P1]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P2]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P3]  = ucLen;

    /*lint -e534*/
    VOS_MemCpy(&gstUSIMMAPDU.aucSendBuf[0], pucData, ucLen);/*���APDU��������*/
    /*lint +e534*/

    gstUSIMMAPDU.ulLcValue = ucLen;                              /*���������������*/

    gstUSIMMAPDU.ulLeValue = 0x00;

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*������·�㴦����*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_TermimalProfile_APDU: USIMM_DLHandle is Failed");/*��ӡ����*/

        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 USIMM_Envelope_APDU(VOS_UINT8 ucLen, VOS_UINT8* pucData)
{
    VOS_UINT32 ulResult;

    gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA|0x80; /*���APDU����ͷ*/

    gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_ENVELOPE;

    gstUSIMMAPDU.aucAPDU[P1]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P2]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P3]  = ucLen;

    /*lint -e534*/
    VOS_MemCpy(&gstUSIMMAPDU.aucSendBuf[0], pucData, ucLen);/*���APDU��������*/
    /*lint +e534*/

    gstUSIMMAPDU.ulLcValue = ucLen;                              /*���������������*/

    /* ���ֳ�����Ϊcase4 */
    gstUSIMMAPDU.ulLeValue = USIMM_LE_MAX_LEN;

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*������·�㴦����*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_Envelope_APDU: USIMM_DLHandle is Failed");/*��ӡ����*/

        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 USIMM_Fetch_APDU(VOS_UINT8 ucLen)
{
    VOS_UINT32 ulResult;

    gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA|0x80; /*���APDU����ͷ*/

    gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_FETCH;

    gstUSIMMAPDU.aucAPDU[P1]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P2]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P3]  = ucLen;

    gstUSIMMAPDU.ulLcValue = 0x00;                              /*���������������*/

    if(ucLen == 0x00)
    {
        gstUSIMMAPDU.ulLeValue = 0x100;
    }
    else
    {
        gstUSIMMAPDU.ulLeValue = ucLen;
    }

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*������·�㴦����*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_Fetch_APDU: USIMM_DLHandle is Failed");/*��ӡ����*/

        return VOS_ERR;
    }

    return VOS_OK;
}



VOS_UINT32 USIMM_TerminalResponse_APDU(VOS_UINT8 ucLen, VOS_UINT8* pucData)
{
    VOS_UINT32 ulResult;

    gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA|0x80; /*���APDU����ͷ*/

    gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_TERMINAL_RESPONSE;

    gstUSIMMAPDU.aucAPDU[P1]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P2]  = 0x00;

    gstUSIMMAPDU.aucAPDU[P3]  = ucLen;

    /*lint -e534*/
    VOS_MemCpy(&gstUSIMMAPDU.aucSendBuf[0], pucData, ucLen);/*���APDU��������*/
    /*lint +e534*/

    gstUSIMMAPDU.ulLcValue = ucLen;                              /*���������������*/

    gstUSIMMAPDU.ulLeValue = 0x00;

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*������·�㴦����*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_TerminalResponse_APDU: USIMM_DLHandle is Failed");/*��ӡ����*/

        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 USIMM_FormatCsimApdu(USIMM_GACCESS_REQ_STRU *pstMsg,
                                            USIMM_APDU_ST          *pstUsimmApdu)
{
    /* ������ݳ���С�����ֽڣ����ǳ���ĳ��� */
    if(pstMsg->usDataLen < T1_CASE1_APDU_LEN)
    {
        /* ��ӡ���� */
        USIMM_ERROR_LOG("USIMM_FormatCsimApdu: data len is less than 4 bytes");

        return VOS_ERR;
    }

    /* CASE1��CASE2����� */
    if ( (T1_CASE1_APDU_LEN == pstMsg->usDataLen)
        || (pstMsg->usDataLen == sizeof(pstUsimmApdu->aucAPDU)))/*��Lc�ֶ�*/
    {
        USIMM_INFO_LOG("USIMM_FormatCsimApdu: The Command have any Lc Data");

        /* copy apdu */
        /*lint -e534*/
        VOS_MemCpy(pstUsimmApdu->aucAPDU, pstMsg->aucContent, pstMsg->usDataLen);
        /*lint +e534*/

        pstUsimmApdu->ulLcValue = 0;

        pstUsimmApdu->ulLeValue = pstUsimmApdu->aucAPDU[P3];  /*Le�����ݿ���Ϊ0*/

        return VOS_OK;
    }

    /* ���������Ӧ�Ľṹ�� */
    /*lint -e534*/
    VOS_MemCpy(pstUsimmApdu->aucAPDU, pstMsg->aucContent, sizeof(pstUsimmApdu->aucAPDU));
    /*lint +e534*/

    /* �ж�P3�ֽ�ָʾ�Ƿ���ȷ */
    if(pstMsg->usDataLen < (pstUsimmApdu->aucAPDU[P3] + USIMM_APDU_HEADLEN))
    {
        USIMM_ERROR_LOG("USIMM_FormatCsimApdu: LC is wrong");/*��ӡ����*/

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemCpy(pstUsimmApdu->aucSendBuf, (pstMsg->aucContent + USIMM_APDU_HEADLEN), pstUsimmApdu->aucAPDU[P3]);
    /*lint +e534*/

    pstUsimmApdu->ulLcValue = pstUsimmApdu->aucAPDU[P3];

    /* ���ݹ��� */
    if(pstMsg->usDataLen > (USIMM_APDU_HEADLEN + pstUsimmApdu->aucAPDU[P3] + 1))
    {
        USIMM_ERROR_LOG("USIMM_FormatCsimApdu: the data len is more");/*��ӡ����*/

        return VOS_ERR;
    }

    /* case4��������һ�ֽڵ�LE�ֶ� */
    if(pstMsg->usDataLen == (USIMM_APDU_HEADLEN + pstUsimmApdu->aucAPDU[P3] + 1))
    {
        pstUsimmApdu->ulLeValue = pstMsg->aucContent[pstMsg->usDataLen - 1];
    }
    else
    {
        /* case3���� */
        pstUsimmApdu->ulLeValue = 0;
    }

    return VOS_OK;
}
VOS_UINT32 USIMM_FormatIsdbApdu(
    USIMM_ISDB_ACCESS_REQ_STRU         *pstMsg,
    USIMM_APDU_ST                      *pstUsimmApdu)
{
    /* ������ݳ���С�����ֽڣ����ǳ���ĳ��� */
    if(pstMsg->usDataLen < T1_CASE1_APDU_LEN)
    {
        /* ��ӡ���� */
        USIMM_ERROR_LOG("USIMM_FormatIsdbApdu: data len is less than 4 bytes");

        return VOS_ERR;
    }

    /* CASE1��CASE2����� */
    if ( (T1_CASE1_APDU_LEN == pstMsg->usDataLen)
        || (pstMsg->usDataLen == sizeof(pstUsimmApdu->aucAPDU)))/*��Lc�ֶ�*/
    {
        USIMM_INFO_LOG("USIMM_FormatIsdbApdu: The Command have any Lc Data");

        /* copy apdu */
        /*lint -e534*/
        VOS_MemCpy(pstUsimmApdu->aucAPDU, pstMsg->aucContent, pstMsg->usDataLen);
        /*lint +e534*/

        pstUsimmApdu->ulLcValue = 0;

        pstUsimmApdu->ulLeValue = pstUsimmApdu->aucAPDU[P3];  /*Le�����ݿ���Ϊ0*/

        return VOS_OK;
    }

    /* ���������Ӧ�Ľṹ�� */
    /*lint -e420 -e534 */
    VOS_MemCpy(pstUsimmApdu->aucAPDU, pstMsg->aucContent, sizeof(pstUsimmApdu->aucAPDU));
    /*lint +e420 +e534 */

    /* �ж�P3�ֽ�ָʾ�Ƿ���ȷ */
    if(pstMsg->usDataLen < (pstUsimmApdu->aucAPDU[P3] + USIMM_APDU_HEADLEN))
    {
        USIMM_ERROR_LOG("USIMM_FormatIsdbApdu: LC is wrong");/*��ӡ����*/

        return VOS_ERR;
    }

    /*lint -e416 -e534 */
    VOS_MemCpy(pstUsimmApdu->aucSendBuf, (pstMsg->aucContent + USIMM_APDU_HEADLEN), pstUsimmApdu->aucAPDU[P3]);
    /*lint +e416 +e534 */

    pstUsimmApdu->ulLcValue = pstUsimmApdu->aucAPDU[P3];

    /* ���ݹ��� */
    if(pstMsg->usDataLen > (USIMM_APDU_HEADLEN + pstUsimmApdu->aucAPDU[P3] + 1))
    {
        USIMM_ERROR_LOG("USIMM_FormatIsdbApdu: the data len is more");/*��ӡ����*/

        return VOS_ERR;
    }

    /* case4��������һ�ֽڵ�LE�ֶ� */
    if(pstMsg->usDataLen == (USIMM_APDU_HEADLEN + pstUsimmApdu->aucAPDU[P3] + 1))
    {
        pstUsimmApdu->ulLeValue = pstMsg->aucContent[pstMsg->usDataLen - 1];
    }
    else
    {
        /* case3���� */
        pstUsimmApdu->ulLeValue = 0;
    }

    return VOS_OK;
}
VOS_UINT32 USIMM_FormatStandardApdu(VOS_UINT8 *pucData, VOS_UINT16 usLen, USIMM_APDU_ST *pstUsimmApdu)
{
    /* ��Lc�ֶ� */
    if (usLen <= sizeof(pstUsimmApdu->aucAPDU))
    {
        USIMM_INFO_LOG("USIMM_FormatStandardApdu: The Command have any Lc Data");

        /* ��APDUΪcase1ʱ��Le�ֶ�Ϊ0 */
        pstUsimmApdu->aucAPDU[P3] = 0;

        /*lint -e534*/
        VOS_MemCpy(pstUsimmApdu->aucAPDU, pucData, usLen);
        /*lint +e534*/

        pstUsimmApdu->ulLcValue = 0;

        /* Le�����ݿ���Ϊ0 */
        pstUsimmApdu->ulLeValue = pstUsimmApdu->aucAPDU[P3];
    }
    /* ��Lc�ֶ� */
    else if ((usLen > sizeof(pstUsimmApdu->aucAPDU))
             &&(usLen <= (sizeof(pstUsimmApdu->aucAPDU)+USIMM_APDU_MAXLEN)))
    {
        USIMM_INFO_LOG("USIMM_FormatStandardApdu: The Command have Lc Data");

        /* �ж�Lc�ֶ��Ƿ���ȷ */
        if ((sizeof(pstUsimmApdu->aucAPDU) + pucData[P3]) > usLen)
        {
            USIMM_ERROR_LOG("USIMM_FormatStandardApdu: Lc is Error");

            return VOS_ERR;
        }

        /*lint -e534*/
        VOS_MemCpy(pstUsimmApdu->aucAPDU, pucData, sizeof(pstUsimmApdu->aucAPDU));

        /*lint -e416*/
        VOS_MemCpy(pstUsimmApdu->aucSendBuf,
                   pucData+sizeof(pstUsimmApdu->aucAPDU),
                   pstUsimmApdu->aucAPDU[P3]);
        /*lint +e534*/
        /*lint +e416*/
        pstUsimmApdu->ulLcValue = pstUsimmApdu->aucAPDU[P3];

        /* ���ݹ��� */
        if(usLen > (USIMM_APDU_HEADLEN + pstUsimmApdu->aucAPDU[P3] + 1))
        {
            USIMM_ERROR_LOG("USIMM_FormatCsimApdu: the data len is more");/*��ӡ����*/

            return VOS_ERR;
        }

        if(usLen == (USIMM_APDU_HEADLEN + pstUsimmApdu->aucAPDU[P3] + 1))
        {
            /* case4 */
            pstUsimmApdu->ulLeValue = pucData[usLen - 1];
        }
        else
        {
            /* case3 */
            pstUsimmApdu->ulLeValue = 0;
        }
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_FormatStandardApdu: The Command Type is Error");

        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 USIMM_Manage_Channel_APDU(VOS_UINT8 ucP1, VOS_UINT8 ucP2, VOS_UINT8 ucP3)
{
    VOS_UINT32 ulResult;

    /* �ڶ�Ӧ���߼�ͨ���Ϸ� �ڴ��߼�ͨ��ʱ:p2Ϊ0���ر��߼�ͨ��ʱ:p2Ϊ��Ӧ�߼�ͨ���� */
    gstUSIMMAPDU.aucAPDU[CLA] = USIMM_USIM_CLA | ucP2;

    gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_MANAGE_CHANNEL;

    gstUSIMMAPDU.aucAPDU[P1]  = ucP1;

    gstUSIMMAPDU.aucAPDU[P2]  = ucP2;

    gstUSIMMAPDU.aucAPDU[P3]  = ucP3;

    gstUSIMMAPDU.ulLcValue = 0x00;

    gstUSIMMAPDU.ulLeValue = ucP3;

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*������·�㴦����*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_Manage_Channel_APDU: USIMM_DLHandle is Failed");/*��ӡ����*/

        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 USIMM_Terminal_Capability_APDU(VOS_UINT8 ucP1, VOS_UINT8 ucP2, USIMM_TERMINAL_CAPABILITY_STRU *pstTerminalCapability)
{
    VOS_UINT32 ulResult;
    VOS_UINT32 ulLen = 0;

    gstUSIMMAPDU.aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA|0x80; /*���APDU����ͷ*/

    gstUSIMMAPDU.aucAPDU[INS] = CMD_INS_TERMINAL_CAPABILITY;

    gstUSIMMAPDU.aucAPDU[P1]  = ucP1;

    gstUSIMMAPDU.aucAPDU[P2]  = ucP2;

    /*lint -e534*/
    VOS_MemCpy(gstUSIMMAPDU.aucSendBuf, (VOS_UINT8 *)pstTerminalCapability->aucData,
                           pstTerminalCapability->ulLen);/*���APDU��������*/
    /*lint +e534*/

    ulLen = pstTerminalCapability->ulLen;

    gstUSIMMAPDU.aucAPDU[P3]  = (VOS_UINT8)ulLen;

    gstUSIMMAPDU.ulLcValue = ulLen;                  /*���������������*/

    gstUSIMMAPDU.ulLeValue = 0x00;

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*������·�㴦����*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_STATUS_APDU: USIMM_DLHandle is Failed");/*��ӡ����*/

        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 USIMM_T1SendIFSD_APDU(VOS_UINT8 ucData)
{
    VOS_UINT32      ulResult;

    /*lint -e534*/
    VOS_MemSet(gstUSIMMAPDU.aucAPDU, 0, USIMM_APDU_HEADLEN);

    VOS_MemSet(gstUSIMMAPDU.aucSendBuf, 0, USIMM_APDU_MAXLEN);
    /*lint +e534*/

    /* ��Ҫ����һ���ֽڵ�IFS��С */
    gstUSIMMAPDU.ulLcValue = 0x01;

    gstUSIMMAPDU.ulLeValue = 0x00;

    gstUSIMMAPDU.aucSendBuf[0] = ucData;

    /* ��ǵ�ǰҪ����IFS REQ */
    g_bSendIFSReqFlag = VOS_TRUE;

    ulResult = USIMM_DLHandle(&gstUSIMMAPDU);   /*������·�㴦����*/

    g_bSendIFSReqFlag = VOS_FALSE;

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_T1SendIFSD_APDU: USIMM_DLHandle is Failed");/*��ӡ����*/

        return VOS_ERR;
    }

    return VOS_OK;
}


#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)

VOS_UINT32 USIMM_StoreESNMEID_APDU(UICC_STORE_ESN_MEID_P1_UINT8     enDataType,
                                                    VOS_UINT8                   *pucData,
                                                    USIMM_APDU_ST               *pstUSIMMAPDU)
{
    VOS_UINT32      ulResult;

    pstUSIMMAPDU->aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA|0x80; /*���APDU����ͷ*/

    pstUSIMMAPDU->aucAPDU[INS] = CMD_INS_STORE_ESNMEID;

    pstUSIMMAPDU->aucAPDU[P1]  = enDataType;

    pstUSIMMAPDU->aucAPDU[P2]  = 0x00;

    /*lint -e534*/
    VOS_MemCpy(pstUSIMMAPDU->aucSendBuf, pucData, USIMM_STORE_ESNMEID_MAX);/*���APDU��������*/
    /*lint +e534*/

    pstUSIMMAPDU->aucAPDU[P3]  = USIMM_STORE_ESNMEID_MAX;

    pstUSIMMAPDU->ulLcValue = USIMM_STORE_ESNMEID_MAX;   /*���������������*/

    pstUSIMMAPDU->ulLeValue = 0x01;                      /*�̶�ֵ*/

    ulResult = USIMM_DLHandle(pstUSIMMAPDU);   /*������·�㴦����*/

    if (USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_StoreESNMEID_APDU: USIMM_DLHandle is Failed");/*��ӡ����*/

        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 USIMM_UpdateSsdAPDU(VOS_UINT8                    ucLen,
                                            VOS_UINT8                   *pucData,
                                            USIMM_APDU_ST               *pstUSIMMAPDU)
{
    VOS_UINT32      ulResult;

    pstUSIMMAPDU->aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA; /*���APDU����ͷ*/

    pstUSIMMAPDU->aucAPDU[INS] = CMD_INS_UPDATE_SSD;

    pstUSIMMAPDU->aucAPDU[P1]  = 0;

    pstUSIMMAPDU->aucAPDU[P2]  = 0;

    pstUSIMMAPDU->aucAPDU[P3]  = ucLen;

    pstUSIMMAPDU->ulLcValue    = ucLen;           /*���������������*/

    pstUSIMMAPDU->ulLeValue    = 0;

    /*lint -e534*/
    VOS_MemCpy(pstUSIMMAPDU->aucSendBuf, pucData, ucLen);/*���APDU��������*/
    /*lint +e534*/

    ulResult = USIMM_DLHandle(pstUSIMMAPDU);   /*������·�㴦����*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_UpdateSsdAPDU: USIMM_DLHandle is Failed");/*��ӡ����*/

        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 USIMM_ConfirmSsdAPDU(VOS_UINT8                   ucLen,
                                            VOS_UINT8                   *pucData,
                                            USIMM_APDU_ST               *pstUSIMMAPDU)
{
    VOS_UINT32      ulResult;

    pstUSIMMAPDU->aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA; /*���APDU����ͷ*/

    pstUSIMMAPDU->aucAPDU[INS] = CMD_INS_CONFIRM_SSD;

    pstUSIMMAPDU->aucAPDU[P1]  = 0;

    pstUSIMMAPDU->aucAPDU[P2]  = 0;

    pstUSIMMAPDU->aucAPDU[P3]  = ucLen;

    pstUSIMMAPDU->ulLcValue    = ucLen;           /*���������������*/

    pstUSIMMAPDU->ulLeValue    = 0;

    /*lint -e534*/
    VOS_MemCpy(pstUSIMMAPDU->aucSendBuf, pucData, ucLen);/*���APDU��������*/
    /*lint +e534*/

    ulResult = USIMM_DLHandle(pstUSIMMAPDU);   /*������·�㴦����*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_ConfirmSsdAPDU: USIMM_DLHandle is Failed");/*��ӡ����*/

        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 USIMM_ManageSsdAPDU(VOS_UINT8                   ucCmd,
                                            VOS_UINT8                   ucLen,
                                            VOS_UINT8                   *pucData,
                                            USIMM_APDU_ST               *pstUSIMMAPDU)
{
    VOS_UINT32      ulResult;

    pstUSIMMAPDU->aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA|0x80; /*���APDU����ͷ*/

    pstUSIMMAPDU->aucAPDU[INS] = CMD_INS_MANAGE_SSD;

    pstUSIMMAPDU->aucAPDU[P1]  = 0;

    pstUSIMMAPDU->aucAPDU[P2]  = ucCmd;

    pstUSIMMAPDU->aucAPDU[P3]  = ucLen;

    pstUSIMMAPDU->ulLcValue    = ucLen;           /*���������������*/

    pstUSIMMAPDU->ulLeValue    = 0;

    /*lint -e534*/
    VOS_MemCpy(pstUSIMMAPDU->aucSendBuf, pucData, ucLen);/*���APDU��������*/
    /*lint +e534*/

    ulResult = USIMM_DLHandle(pstUSIMMAPDU);   /*������·�㴦����*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_ManageSsdAPDU: USIMM_DLHandle is Failed");/*��ӡ����*/

        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 USIMM_GenerateKeyVpmAPDU(VOS_UINT8                   ucLen,
                                                    VOS_UINT8                   *pucData,
                                                    USIMM_APDU_ST               *pstUSIMMAPDU)
{
    VOS_UINT32      ulResult;

    pstUSIMMAPDU->aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA|0x80; /*���APDU����ͷ*/

    pstUSIMMAPDU->aucAPDU[INS] = CMD_INS_GENERATE_KEY;

    pstUSIMMAPDU->aucAPDU[P1]  = 0;

    pstUSIMMAPDU->aucAPDU[P2]  = 0;

    pstUSIMMAPDU->aucAPDU[P3]  = ucLen;

    pstUSIMMAPDU->ulLcValue    = ucLen;           /*���������������*/

    pstUSIMMAPDU->ulLeValue    = 0;

    /*lint -e534*/
    VOS_MemCpy(pstUSIMMAPDU->aucSendBuf, pucData, ucLen);/*���APDU��������*/
    /*lint +e534*/

    ulResult = USIMM_DLHandle(pstUSIMMAPDU);   /*������·�㴦����*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_GenerateKeyVpmAPDU: USIMM_DLHandle is Failed");/*��ӡ����*/

        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 USIMM_BSChallengeAPDU(VOS_UINT8                  *pucRandSeed,
                                             USIMM_APDU_ST               *pstUSIMMAPDU)
{
    VOS_UINT32      ulResult;

    pstUSIMMAPDU->aucAPDU[CLA] = gstUSIMMBaseInfo.ucCLA|0x80; /*���APDU����ͷ*/

    pstUSIMMAPDU->aucAPDU[INS] = CMD_INS_BASE_STATION_CHALLENGE;

    pstUSIMMAPDU->aucAPDU[P1]  = 0;

    pstUSIMMAPDU->aucAPDU[P2]  = 0;

    pstUSIMMAPDU->aucAPDU[P3]  = USIMM_BS_RANDSEED_MAX;

    pstUSIMMAPDU->ulLcValue    = USIMM_BS_RANDSEED_MAX;           /*���������������*/

    pstUSIMMAPDU->ulLeValue    = USIMM_BS_RANDSEED_MAX;

    /*lint -e534*/
    VOS_MemCpy( pstUSIMMAPDU->aucSendBuf, (VOS_UINT8 *)pucRandSeed,  pstUSIMMAPDU->aucAPDU[P3]);/*���APDU��������*/
    /*lint +e534*/

    ulResult = USIMM_DLHandle(pstUSIMMAPDU);   /*������·�㴦����*/

    if(USIMM_DL_SUCESS != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_BSChallengeAPDU: USIMM_DLHandle is Failed");/*��ӡ����*/

        return VOS_ERR;
    }

    return VOS_OK;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif

