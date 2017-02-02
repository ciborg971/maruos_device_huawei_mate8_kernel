/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��      : Om.c
  �� �� ��      : ����
  ��    ��      : ����47350
  ��������      : 2008��5��3��
  ����޸�      :
  ��������      : ��C�ļ�������OMģ���ʵ��
  �����б�      :
  �޸���ʷ      :
  1.��    ��    : 2008��5��3��
    ��    ��    : ����47350
    �޸�����    : �����ļ�

******************************************************************************/
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "NVIM_Interface.h"
#include "UsimPsInterface.h"
#include "apminterface.h"
#include "spysystem.h"
#include "wasphycomminterface.h"
#include "PhyGasInterface.h"
#include "PhyGrmInterface.h"
#include "PhyGasComm.h"
#include "PhyCodecInterface.h"
#include "TafOamInterface.h"
#include "hpamailboxdef.h"
#include "DspInterface.h"
#include "NasNvInterface.h"
#include "cbtrl.h"
#include "PhyNvDefine.h"
#include "omprivate.h"
#include "pamom.h"

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

#include "csdr1xcm.h"
#include "cproc1xcm.h"
#include "cproc1x.h"
#include "cascbtinterface.h"
#include "cttfcbtinterface.h"
#include "cdma_timing_drv.h"
#include "cproc_1x_ccbt.h"

#endif


#if (RAT_MODE != RAT_GU)
#include "msp_nvim.h"
#include "product_config.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif


/*lint -e767 �޸��ˣ�����47350�������ˣ�����46160��ԭ�������LOG���������Ҫ*/
#define    THIS_FILE_ID        PS_FILE_ID_CBT_FUNC_C
/*lint +e767 �޸��ˣ�����47350�������ˣ�lixiao��*/

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
extern VOS_UINT16                       g_usCBadFrames;
extern VOS_UINT16                       g_usListModeCurrentMode;
extern VOS_UINT32                       g_ulOmNosigEnable;
extern VOS_UINT32                       g_ulListmodeEnable;
extern CBT_LISI_MODE_CTRL_STRU          g_stListmodeCtrl;

/*����У׼ͨ����·��״̬�������Ƿ��������ͨ��*/
VOS_UINT32                              g_ulCbtSwitchOnOff = CBT_STATE_IDLE;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*����cdma�����жϳ����״̬*/
VOS_UINT32                              g_ulCbtCdmaRegisterInterface = VOS_FALSE;

extern VOS_VOID   HPA_10msOffsetCdmaIsr(CDMA_TIME pstCdmaSysTime, VOS_VOID *pvParam);

#endif

VOS_RATMODE_ENUM_UINT32                 g_ulCBTMasterModeBackup = VOS_RATMODE_BUTT;

VOS_RATMODE_ENUM_UINT32                 g_ulOMMasterModeBackup  = VOS_RATMODE_BUTT;


VOS_UINT32 CBT_SysCtrlCmd(VOS_UINT16 usClientId, VOS_UINT32 ulMode, MODEM_ID_ENUM_UINT16 enModemID)
{
    MN_APP_PHONE_MODE_SET_REQ_STRU * pstMsg;

    if (MODEM_ID_BUTT <= enModemID)
    {
        PS_LOG(CCPU_PID_CBT, 0, PS_PRINT_ERROR, "OM_SysCtrlCmd: Modem ID Error!");

        return VOS_ERR;
    }

    pstMsg = (MN_APP_PHONE_MODE_SET_REQ_STRU*)VOS_AllocMsg(CCPU_PID_CBT,
            sizeof(MN_APP_PHONE_MODE_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        PS_LOG(CCPU_PID_CBT, 0, PS_PRINT_ERROR, "OM_SysCtrlCmd: VOS_AllocMsg failed!");

        return VOS_ERR;
    }

    if (MODEM_ID_1 == enModemID)
    {
        pstMsg->ulReceiverPid      = I1_WUEPS_PID_MMA;
    }

    else
    {
        pstMsg->ulReceiverPid      = I0_WUEPS_PID_MMA;
    }

    pstMsg->ulMsgId            = OAM_MMA_PHONE_MODE_SET_REQ;

    /* ������Ϣ��NAS����ϵͳ���� */
    pstMsg->usClientId         = usClientId;
    pstMsg->opID               = 0;
    pstMsg->stPhOpMode.CmdType = TAF_PH_CMD_SET;
    pstMsg->stPhOpMode.PhMode  = (VOS_UINT8)ulMode;
    pstMsg->stPhOpMode.PhReset = TAF_PH_OP_MODE_UNRESET;

    return VOS_SendMsg(CCPU_PID_CBT, pstMsg);
}
VOS_UINT32 CBT_SetFTM(CBT_UNIFORM_MSG_STRU * pstPcToCbtMsg,
                                           VOS_UINT16 usReturnPrimId)
{
    /* ����У׼��INDͨ���ϱ� */
    if (VOS_OK != CBT_SysCtrlCmd((VOS_UINT16)OAM_CLIENT_ID_CBT,
                                *((VOS_UINT32*)pstPcToCbtMsg->aucPara),
                                (MODEM_ID_ENUM_UINT16)(pstPcToCbtMsg->stMsgHeader.stModemSsid.ucModem)))
    {
        CBT_SendResultChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, (VOS_UINT32)VOS_ERR);

        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 CBT_ActivePhyMsgProc(CBT_UNIFORM_MSG_STRU * pstPcToCbtMsg, VOS_UINT16 usReturnPrimId)
{
    OM_ACTIVE_PHY_STRU                 *pstActiveMsg;
    VOS_RATMODE_ENUM_UINT32             enRatMode;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulResult;

    enModemId = pstPcToCbtMsg->stMsgHeader.stModemSsid.ucModem;

    pstActiveMsg = (OM_ACTIVE_PHY_STRU*)pstPcToCbtMsg->aucPara;

    /* ���߲ඨ���뵥��಻һ�� */
    if(LMT_RAT_WCDMA == pstActiveMsg->usSysMode)
    {
        enRatMode = VOS_RATMODE_WCDMA;
    }
    else if(LMT_RAT_GSM == pstActiveMsg->usSysMode)
    {
        enRatMode = VOS_RATMODE_GSM;
    }
    else
    {
        CBT_SendResultChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, (VOS_UINT32)VOS_ERR);

        return VOS_ERR;
    }

    ulResult = SHPA_ActiveDSP(enRatMode, enModemId);

    CBT_SendResultChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, ulResult);

    return ulResult;
}
VOS_UINT32 CBT_LoadLmtMsgProc(CBT_UNIFORM_MSG_STRU * pstPcToCbtMsg, VOS_UINT16 usReturnPrimId)
{
    OM_LMT_MSG_STRU                    *pstLmtMsg;
    OM_SW_VER_FLAG_STRU                 stCustomVersion;
    MODEM_ID_ENUM_UINT16                enModemID;
    PHY_OAM_SET_WORK_MODE_REQ_STRU      stSetWorkModeReq;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulSlaveReceiverPid  = VOS_PID_BUTT;
    VOS_RATMODE_ENUM_UINT32             enMasterMode;
    VOS_RATMODE_ENUM_UINT32             enSlaveMode;
    UPHY_OAM_BUSINESS_TYPE_ENUM_UINT16  enBusiness      = UPHY_OAM_BUSINESS_TYPE_BUTT;
    UPHY_OAM_BOOL_ENUM_UINT16           enPhyInitFlag   = UPHY_OAM_INVALID;
    UCOM_NV_TRI_MODE_ENABLE_STRU        stRfSwitchFlag;

    enModemID = pstPcToCbtMsg->stMsgHeader.stModemSsid.ucModem;

    if (MODEM_ID_BUTT <= enModemID)
    {
        CBT_SendResultChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, (VOS_UINT32)VOS_ERR);

        return VOS_ERR;
    }

    pstLmtMsg = (OM_LMT_MSG_STRU*)(pstPcToCbtMsg->aucPara);

    stSetWorkModeReq.ulLength   = (VOS_UINT32)sizeof(PHY_OAM_SET_WORK_MODE_REQ_STRU) - (VOS_UINT32)VOS_MSG_HEAD_LENGTH;

    /* make Coverity happy begin */
    stSetWorkModeReq.ulSenderCpuId     = (VOS_UINT32)0;
    stSetWorkModeReq.ulSenderPid       = (VOS_UINT32)0;
    stSetWorkModeReq.ulReceiverCpuId   = (VOS_UINT32)0;
    stSetWorkModeReq.sRsv              = (VOS_UINT16)0;
    /* make Coverity happy end */

    /* ��ȡȫ��ͨʹ�����Կ����� */
    if(NV_OK != NV_Read(en_NV_Item_TRI_MODE_ENABLE, &stRfSwitchFlag, sizeof(UCOM_NV_TRI_MODE_ENABLE_STRU)))
    {
        stRfSwitchFlag.uhwEnable    = VOS_FALSE;
    }

    if ( VOS_TRUE == stRfSwitchFlag.uhwEnable )
    {
        SLEEP_ActivateHw(VOS_RATMODE_WCDMA);
        SLEEP_ActivateHw(VOS_RATMODE_GSM);
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        SLEEP_ActivateHw(VOS_RATMODE_1X);
#endif
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
        I1_SLEEP_ActivateHw(VOS_RATMODE_GSM);
#endif
    }

    /* ͨ�����������·��ļ���Ҫ�󣬹�������������Ϣ�����ڼ����������Ҫ������ģ
       ������һ����Ϣ��������Ҫ��������������ͬ��������Ϣ���� */
    if (LMT_RAT_WCDMA == pstLmtMsg->usSysMode)
    {
        ulReceiverPid       = DSP_PID_WPHY;
        if (VOS_RATMODE_GSM == g_ulCBTMasterModeBackup)
        {
            ulSlaveReceiverPid  = I0_DSP_PID_GPHY;
        }
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        else if (VOS_RATMODE_1X == g_ulCBTMasterModeBackup)
        {
            ulSlaveReceiverPid  = CPROC_PID_1X_CM;
        }
#endif
        else
        {
            ulSlaveReceiverPid  = VOS_PID_BUTT;
        }
        enMasterMode        = VOS_RATMODE_WCDMA;
        enSlaveMode         = g_ulCBTMasterModeBackup;

        g_ulCBTMasterModeBackup = VOS_RATMODE_WCDMA;
    }
    else if (LMT_RAT_GSM == pstLmtMsg->usSysMode)
    {
        /* ���ڸ���ֻ��Gģ������Ҫ����W��ģ */
        if (MODEM_ID_1 == enModemID)
        {
            ulReceiverPid       = I1_DSP_PID_GPHY;
            ulSlaveReceiverPid  = VOS_PID_BUTT;
            enMasterMode        = VOS_RATMODE_GSM;
            enSlaveMode         = VOS_RATMODE_WCDMA;
        }
        else
        {
            ulReceiverPid       = I0_DSP_PID_GPHY;
            if (VOS_RATMODE_WCDMA == g_ulCBTMasterModeBackup)
            {
                ulSlaveReceiverPid  = DSP_PID_WPHY;
            }
        #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
            else if (VOS_RATMODE_1X == g_ulCBTMasterModeBackup)
            {
                ulSlaveReceiverPid  = CPROC_PID_1X_CM;
            }
        #endif
            else
            {
                ulSlaveReceiverPid  = VOS_PID_BUTT;
            }
            enMasterMode        = VOS_RATMODE_GSM;
            enSlaveMode         = g_ulCBTMasterModeBackup;
        }

        g_ulCBTMasterModeBackup = VOS_RATMODE_GSM;
    }
    else if (LMT_RAT_CDMA == pstLmtMsg->usSysMode)
    {
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        ulReceiverPid       = CPROC_PID_1X_CM;
        if (VOS_RATMODE_WCDMA == g_ulCBTMasterModeBackup)
        {
            ulSlaveReceiverPid  = DSP_PID_WPHY;
        }
        else if (VOS_RATMODE_GSM == g_ulCBTMasterModeBackup)
        {
            ulSlaveReceiverPid  = DSP_PID_GPHY;
        }
        else
        {
            ulSlaveReceiverPid  = VOS_PID_BUTT;
        }
        enMasterMode        = VOS_RATMODE_1X;
        enSlaveMode         = g_ulCBTMasterModeBackup;

        g_ulCBTMasterModeBackup = VOS_RATMODE_1X;
#else
        CBT_SendResultChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, (VOS_UINT32)VOS_ERR);

        return VOS_ERR;
#endif
    }
    else if (VOS_NULL_WORD == pstLmtMsg->usSysMode) /*���������״̬��ˢ��NV����*/
    {
        if (MODEM_ID_1 == enModemID)
        {
            stSetWorkModeReq.ulReceiverPid  = I1_DSP_PID_APM;
        }
        else
        {
            stSetWorkModeReq.ulReceiverPid  = I0_DSP_PID_APM;
        }

        stSetWorkModeReq.enMsgId           = ID_OAM_PHY_SET_WORK_MODE_REQ;
        stSetWorkModeReq.enModem           = enModemID;
        stSetWorkModeReq.enMasterMode      = VOS_RATMODE_BUTT;
        stSetWorkModeReq.enSlaveMode       = VOS_RATMODE_BUTT;
        stSetWorkModeReq.enBusinessType    = UPHY_OAM_BUSINESS_TYPE_CT;
        stSetWorkModeReq.enPhyInitFlag     = UPHY_OAM_INVALID;
        stSetWorkModeReq.enNvUpdateFlag    = pstLmtMsg->ucNvEnable;

        if (VOS_TRUE != SHPA_LoadPhy(stSetWorkModeReq))
        {
            CBT_SendResultChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, (VOS_UINT32)VOS_ERR);

            return VOS_ERR;
        }

        CBT_SendResultChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, (VOS_UINT32)VOS_OK);

        return VOS_OK;
    }
    else
    {
        CBT_SendResultChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, (VOS_UINT32)VOS_ERR);

        return VOS_ERR;
    }

    if (VOS_NULL_WORD != pstLmtMsg->usSysMode)
    {
        /* �ж�CT���Ƿ�����BT */
        if (VOS_FALSE == pstLmtMsg->ucFtmMode)
        {
            g_ulOmNosigEnable   = VOS_FALSE;

            enBusiness          = UPHY_OAM_BUSINESS_TYPE_CT;
        }
        else
        {
            /* �ж��Ƿ�Ϊ��Ƭ�汾 */
            if ( VOS_OK != NV_Read(en_NV_Item_SW_VERSION_FLAG, &stCustomVersion, sizeof(stCustomVersion)) )
            {
                stCustomVersion.ulNvSwVerFlag = VOS_TRUE;
            }

            /* ���ulCustomVersion == VOS_TRUE��ʾ������Ƭ�汾����ֱ�ӷ��أ����߲�֧�ַ����� */
            if ( VOS_TRUE == stCustomVersion.ulNvSwVerFlag)
            {
                CBT_SendResultChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, (VOS_UINT32)VOS_ERR);

                return VOS_ERR;
            }

            /* ��ʼ����������ƽṹ */
            OM_NoSigCtrlInit();
            CBT_ListModeCtrlInit();

            g_ulOmNosigEnable       = MAIL_BOX_PROTECTWORD_SND;
            g_usListModeCurrentMode = (LMT_RAT_WCDMA == pstLmtMsg->usSysMode)?
                                        VOS_RATMODE_WCDMA : VOS_RATMODE_GSM;

            enBusiness          = UPHY_OAM_BUSINESS_TYPE_NO_SIG_BT;
        }

        g_ulListmodeEnable = VOS_FALSE;
        enPhyInitFlag   = UPHY_OAM_VALID;
    }

    /*����������ģ��Ϣ�������ش�ģ�����*/
    if (MODEM_ID_1 != enModemID)
    {
        if (VOS_PID_BUTT != ulSlaveReceiverPid)
        {
            stSetWorkModeReq.enMsgId           = ID_OAM_PHY_SET_WORK_MODE_REQ;
            stSetWorkModeReq.ulReceiverPid     = ulSlaveReceiverPid;
            stSetWorkModeReq.enModem           = enModemID;
            stSetWorkModeReq.enMasterMode      = enMasterMode;
            stSetWorkModeReq.enSlaveMode       = enSlaveMode;
            stSetWorkModeReq.enBusinessType    = enBusiness;
            stSetWorkModeReq.enPhyInitFlag     = enPhyInitFlag;
            stSetWorkModeReq.enNvUpdateFlag    = UPHY_OAM_INVALID;

            if (VOS_TRUE != SHPA_LoadPhy(stSetWorkModeReq))
            {
                CBT_SendResultChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, (VOS_UINT32)VOS_ERR);

                return VOS_ERR;
            }
        }
    }

    /*������ģ��Ϣ����������ģ�����*/
    stSetWorkModeReq.enMsgId           = ID_OAM_PHY_SET_WORK_MODE_REQ;
    stSetWorkModeReq.ulReceiverPid     = ulReceiverPid;
    stSetWorkModeReq.enModem           = enModemID;
    stSetWorkModeReq.enMasterMode      = enMasterMode;
    stSetWorkModeReq.enSlaveMode       = enSlaveMode;
    stSetWorkModeReq.enBusinessType    = enBusiness;
    stSetWorkModeReq.enPhyInitFlag     = enPhyInitFlag;
    stSetWorkModeReq.enNvUpdateFlag    = pstLmtMsg->ucNvEnable;

    if (VOS_TRUE != SHPA_LoadPhy(stSetWorkModeReq))
    {
        CBT_SendResultChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, (VOS_UINT32)VOS_ERR);

        return VOS_ERR;
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if ((LMT_RAT_CDMA == pstLmtMsg->usSysMode)
     && (VOS_TRUE == pstLmtMsg->ucFtmMode))
    {
        if (VOS_FALSE == g_ulCbtCdmaRegisterInterface)
        {
            /*lint -e534*/
            CDMA_RequestTimeEvent(CDMA_TIMING_RTT_1X, CDMA_TIMING_PERIOD_10_00_MS_1X, 0, HPA_10msOffsetCdmaIsr, VOS_NULL_PTR);
            /*lint +e534*/

            g_ulCbtCdmaRegisterInterface = VOS_TRUE;
        }

        g_ulOmNosigEnable           = MAIL_BOX_PROTECTWORD_SND;
        g_usListModeCurrentMode     = VOS_RATMODE_1X;
    }
#endif

    CBT_SendResultChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, (VOS_UINT32)VOS_OK);

    return VOS_OK;
}


VOS_UINT32 CBT_EstablishProc(CBT_UNIFORM_MSG_STRU * pstPcToCbtMsg,
                                           VOS_UINT16 usReturnPrimId)
{
    g_ulCbtSwitchOnOff = (VOS_UINT32)OM_STATE_ACTIVE;

    return VOS_OK;
}


VOS_UINT32 CBT_ReleaseProc(CBT_UNIFORM_MSG_STRU * pstPcToCbtMsg,
                                           VOS_UINT16 usReturnPrimId)
{
    g_ulCbtSwitchOnOff = OM_STATE_IDLE;

    return VOS_OK;
}


VOS_UINT32 CBT_QueryModemNumReq(CBT_UNIFORM_MSG_STRU * pstPcToCbtMsg,
                                            VOS_UINT16 usReturnPrimId)
{
    VOS_UINT32                          ulModemNum;

#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
    ulModemNum = (VOS_UINT32)MODEM_ID_BUTT;
#else
    ulModemNum = (VOS_UINT32)(MODEM_ID_0 + 1);
#endif

    CBT_SendResultChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, (VOS_UINT32)ulModemNum);

    return VOS_OK;
}


VOS_UINT32 CBT_QueryMisc(CBT_UNIFORM_MSG_STRU * pstPcToCbtMsg, VOS_UINT16 usReturnPrimId)
{
    CBT_UNIFORM_MSG_STRU            *pstCbtToPcMsg;
    OM_APP_PA_ATTRIBUTE_STRU        *pstPaAttribute;
    VOS_UINT16                      *pusData;
    VOS_UINT32                       ulTotalSize;
    VOS_UINT16                       usQueryType = 0;
    VOS_UINT32                       ulIndex;
    VOS_UINT32                       ulNum;
    VOS_INT16                        sTempValue = 0;
    VOS_UINT16                       usVoltValue = 0;
    VOS_INT                          lStatus = 0;
    VOS_INT32                        lResult = VOS_OK;
    VOS_UINT32                       ulResult;
    MODEM_ID_ENUM_UINT16             enModemID;
    HKADC_TEMP_PROTECT_E             enTempType;

    /*ָ���ѯ���������ָ��*/
    pusData = (VOS_UINT16*)(pstPcToCbtMsg->aucPara);

    /*��ȡ��ѯ���͵ĸ���*/
    ulNum = pstPcToCbtMsg->ulMsgLength / sizeof(usQueryType);
    /*�������ݰ����ܳ��ȣ��μ�OM_APP_PA_ATTRIBUTE_STRU*/
    ulTotalSize = (CBT_MSG_HEAD_EX_LENGTH + sizeof(VOS_UINT32))
                              + (ulNum*sizeof(OM_PA_ITEM_STRU));
    pstCbtToPcMsg = (CBT_UNIFORM_MSG_STRU *)VOS_MemAlloc(CCPU_PID_CBT,
                                          DYNAMIC_MEM_PT, ulTotalSize);
    if (VOS_NULL_PTR == pstCbtToPcMsg)
    {
        CBT_SendResultChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, (VOS_UINT32)VOS_ERR);

        return VOS_ERR;
    }

    enModemID = pstPcToCbtMsg->stMsgHeader.stModemSsid.ucModem;

    pstPaAttribute = (OM_APP_PA_ATTRIBUTE_STRU *)(pstCbtToPcMsg->aucPara);
    usQueryType = *pusData;

    /*���õ���ӿڣ���ȡPA����*/
    for (ulIndex = 0; ulIndex < ulNum; ulIndex++)
    {
        usQueryType = *pusData;
        switch (usQueryType)
        {
        case OM_W_PA_TEMP:
        case OM_G_PA_TEMP:
            if(MODEM_ID_0 == enModemID)
            {
                enTempType = HKADC_TEMP_PA0;
            }
            else
            {
                enTempType = HKADC_TEMP_PA1;
            }

            lResult = mdrv_hkadc_get_temp(enTempType, VOS_NULL_PTR, &sTempValue, HKADC_CONV_DELAY);
            lStatus = sTempValue;
            break;

        case OM_W_HKADC:
        case OM_G_HKADC:
            if(MODEM_ID_0 == enModemID)
            {
                enTempType = HKADC_TEMP_PA0;
            }
            else
            {
                enTempType = HKADC_TEMP_PA1;
            }

            lResult = mdrv_hkadc_get_temp(enTempType, &usVoltValue, VOS_NULL_PTR, HKADC_CONV_DELAY);
            lStatus = (VOS_INT)usVoltValue;
            break;

        case OM_BATTER_VOLT:
            if(BSP_MODULE_SUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_CHARGE)) /*���õ���ӿ��жϵ���Ƿ�֧��*/
            {
                lResult = mdrv_hkadc_get_bat_volt((VOS_INT*)&lStatus);
            }
            else
            {
                lResult = VOS_OK;
            }
            break;

        case OM_DCXO_TEMP:
            if(MODEM_ID_0 == enModemID)
            {
                enTempType = HKADC_TEMP_XO0;
            }
            else
            {
                enTempType = HKADC_TEMP_XO1;
            }

            lResult = mdrv_hkadc_get_temp(enTempType, VOS_NULL_PTR, &sTempValue, HKADC_CONV_DELAY);
            lStatus = sTempValue;
            break;

        case OM_DCXO_TEMP_LT:
            if(MODEM_ID_0 == enModemID)
            {
                enTempType = HKADC_TEMP_XO0_LOW;
            }
            else
            {
                enTempType = HKADC_TEMP_XO1_LOW;
            }

            lResult = mdrv_hkadc_get_temp(enTempType, VOS_NULL_PTR, &sTempValue, HKADC_CONV_DELAY);
            lStatus = sTempValue;
            break;

        default:
            lResult = VOS_ERR;
            break;
        }

        /*��ѯʧ��*/
        if (VOS_OK != lResult)
        {
            /*Just for PcLint*/
            ulResult = (VOS_UINT32)lResult;
            ulResult <<= 16;
            ulResult |= usQueryType;
            /*lint -e534*/
            VOS_MemFree(CCPU_PID_CBT, pstCbtToPcMsg);
            /*lint +e534*/
            CBT_SendResultChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, ulResult);

            return VOS_ERR;
        }

        /*��д��ѯ�Ľ��*/
        pstPaAttribute->aPaItem[ulIndex].usQueryType  = usQueryType;/* [false alarm]:Buffer overflow����  */
        pstPaAttribute->aPaItem[ulIndex].sQueryResult = (VOS_INT16)lStatus;/* [false alarm]:Buffer overflow����  */
        pusData++;
    }

    /*Assign the length field.*/
    pstCbtToPcMsg->ulMsgLength = (VOS_UINT32)(ulTotalSize - CBT_MSG_HEAD_EX_LENGTH);
    pstPaAttribute->ulResult = VOS_OK;

    CBT_SendContentChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, pstCbtToPcMsg);
    /*lint -e534*/
    VOS_MemFree(CCPU_PID_CBT, pstCbtToPcMsg);
    /*lint +e534*/
    return VOS_OK;
}
VOS_UINT32 CBT_QueryPaTempByPhyChan(CBT_UNIFORM_MSG_STRU * pstPcToCbtMsg, VOS_UINT16 usReturnPrimId)
{
    CBT_UNIFORM_MSG_STRU            *pstCbtToPcMsg;
    OM_APP_PA_ATTRIBUTE_STRU        *pstPaAttribute;
    VOS_UINT16                      *pusData;
    VOS_UINT32                       ulTotalSize;
    VOS_UINT16                       usChannelNo = 0;
    VOS_UINT32                       ulIndex;
    VOS_UINT32                       ulNum;
    VOS_INT16                        sTempValue = 0;
    VOS_INT32                        lResult = VOS_OK;
    VOS_UINT32                       ulResult;

    /*ָ���ѯ���������ָ��*/
    pusData = (VOS_UINT16 *)(pstPcToCbtMsg->aucPara);
    /*��ȡ��ѯ���͵ĸ���*/
    ulNum = pstPcToCbtMsg->ulMsgLength / sizeof(usChannelNo);
    /*�������ݰ����ܳ��ȣ��μ�OM_APP_PA_ATTRIBUTE_STRU*/
    ulTotalSize = (CBT_MSG_HEAD_EX_LENGTH + sizeof(VOS_UINT32))
                              + (ulNum * sizeof(OM_PA_ITEM_STRU));
    pstCbtToPcMsg = (CBT_UNIFORM_MSG_STRU *)VOS_MemAlloc(CCPU_PID_CBT,
                                          DYNAMIC_MEM_PT, ulTotalSize);

    if (VOS_NULL_PTR == pstCbtToPcMsg)
    {
        CBT_SendResultChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, (VOS_UINT32)VOS_ERR);
        return  VOS_ERR;
    }

    pstPaAttribute = (OM_APP_PA_ATTRIBUTE_STRU *)(pstCbtToPcMsg->aucPara);
    usChannelNo = *pusData;

    /*���õ���ӿڣ���ȡPA����*/
    for (ulIndex = 0; ulIndex < ulNum; ulIndex++)
    {
        usChannelNo = *pusData;
        lResult = mdrv_hkadc_get_phy_temp(usChannelNo, VOS_NULL_PTR, &sTempValue, HKADC_CONV_DELAY);
        /*��ѯʧ��*/
        if (VOS_OK != lResult)
        {
            ulResult = (VOS_UINT32)lResult;
            ulResult <<= 16;
            ulResult |= usChannelNo;
            /*lint -e534*/
            VOS_MemFree(CCPU_PID_CBT, pstCbtToPcMsg);
            /*lint +e534*/
            CBT_SendResultChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, ulResult);
            return VOS_ERR;
        }
        /*��д��ѯ�Ľ��*/
        pstPaAttribute->aPaItem[ulIndex].usQueryType  = usChannelNo;/* [false alarm]:Buffer overflow����  */
        pstPaAttribute->aPaItem[ulIndex].sQueryResult = (VOS_INT16)sTempValue;/* [false alarm]:Buffer overflow����  */
        pusData++;
    }
    /*Assign the length field.*/
    pstPaAttribute->ulResult = VOS_OK;
    pstCbtToPcMsg->ulMsgLength = (VOS_UINT16)(ulTotalSize - CBT_MSG_HEAD_EX_LENGTH);

    CBT_SendContentChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, pstCbtToPcMsg);

    /*lint -e534*/
    VOS_MemFree(CCPU_PID_CBT, pstCbtToPcMsg);
    /*lint -e534*/

    return VOS_OK;
}
VOS_UINT32 CBT_SendAT2RttAgent(CBT_UNIFORM_MSG_STRU * pstPcToCbtMsg, VOS_UINT16 usReturnPrimId, RTTAgentFunc pfunRttAgent)
{
    CBT_SEND_COMM_MSG_STRU             *pstMsg;
    VOS_UINT32                          ulLength;
    VOS_UINT32                          ulRet;

    ulLength = pstPcToCbtMsg->ulMsgLength;

    pstMsg = (CBT_SEND_COMM_MSG_STRU *)VOS_AllocMsg(CCPU_PID_CBT, ulLength + CBT_MSG_ID_COMP_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        CBT_SendResultChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, VOS_ERR);
        return VOS_ERR;
    }

    pstMsg->ulReceiverPid = TLPHY_PID_RTTAGENT;

    pstMsg->usMsgId     = pstPcToCbtMsg->usMsgId;
    /*lint -e534*/
    VOS_MemCpy(&pstMsg->usCompMode, (VOS_UINT8 *)&pstPcToCbtMsg->stCompMode, sizeof(VOS_UINT16));
    VOS_MemCpy(pstMsg->aucPara, (VOS_UINT8*)(pstPcToCbtMsg->aucPara), ulLength);
    /*lint +e534*/

    ulRet = pfunRttAgent(pstMsg);
    /*pfunRttAgent �����·����ڴ������pstMsg*/
    /*lint -e534*/
    VOS_FreeMsg(CCPU_PID_CBT, pstMsg);
    /*lint +e534*/
    if (VOS_OK != ulRet)
    {
        return VOS_ERR;
    }

    return VOS_OK;

}



#if (RAT_MODE != RAT_GU)
VOS_UINT32 CBT_ATTMode(CBT_UNIFORM_MSG_STRU * pstPcToCbtMsg, VOS_UINT16 usReturnPrimId)
{
    return CBT_SendAT2RttAgent(pstPcToCbtMsg, usReturnPrimId, RTTAGENT_TmodeSet);
}

VOS_UINT32 CBT_ATBandSW(CBT_UNIFORM_MSG_STRU * pstPcToCbtMsg, VOS_UINT16 usReturnPrimId)
{
    return CBT_SendAT2RttAgent(pstPcToCbtMsg, usReturnPrimId, RTTAGENT_BandSWSetNoCardSig);
}

VOS_UINT32 CBT_ATFChan(CBT_UNIFORM_MSG_STRU * pstPcToCbtMsg, VOS_UINT16 usReturnPrimId)
{
    VOS_UINT8                           usMode;

    usMode = pstPcToCbtMsg->stCompMode.ucMode;

    if (CBT_MODE_TDS == usMode)
    {
        return CBT_SendAT2RttAgent(pstPcToCbtMsg, usReturnPrimId, RTTAGENT_FchanTDSSet);
    }
    else
    {
        return CBT_SendAT2RttAgent(pstPcToCbtMsg, usReturnPrimId, RTTAGENT_FchanLTESet);
    }
}

VOS_UINT32 CBT_SwitchRfAnt(CBT_UNIFORM_MSG_STRU * pstPcToCbtMsg, VOS_UINT16 usReturnPrimId)
{
    CBT_LT_SWITCH_RF_ANT_STRU          *pstContextMsg;

    pstContextMsg = (CBT_LT_SWITCH_RF_ANT_STRU *)pstPcToCbtMsg->aucPara;

    if (VOS_OK != mdrv_fem_ioctrl(CFG_RFFE_SET_PIN_NO_NV, pstContextMsg->usGpioNo, 0, pstContextMsg->usGpioLevel))
    {
        CBT_SendResultChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, VOS_ERR);
        return VOS_ERR;
    }

    CBT_SendResultChannel(pstPcToCbtMsg->stMsgHeader.stModemSsid, pstPcToCbtMsg->stCompMode, usReturnPrimId, VOS_OK);
    return VOS_OK;
}


#endif



/*Global map table used to find the function according the PrimId.*/
CBT_MSG_FUN_STRU g_astCbtMsgFunTbl[] =
{
    {CBT_LoadLmtMsgProc,           APP_OM_HANDLE_LMT_REQ,             OM_APP_HANDLE_LMT_CNF},
    {CBT_ActivePhyMsgProc,         APP_OM_ACTIVE_PHY_REQ,             OM_APP_ACTIVE_PHY_CNF},
    {CBT_SetFTM,                   APP_OM_SET_FTM_REQ,                OM_APP_SET_FTM_CNF},
    {CBT_EstablishProc,            APP_OM_ESTABLISH_REQ,              OM_APP_ESTABLISH_CNF},
    {CBT_ReleaseProc,              APP_OM_RELEASE_REQ,                OM_APP_RELEASE_CNF},
    {CBT_QueryModemNumReq,         APP_OM_QUERY_MODEM_NUM_REQ,        OM_APP_QUERY_MODEM_NUM_CNF},
    {CBT_QueryMisc,                APP_OM_PA_ATTRIBUTE_REQ,           OM_APP_PA_ATTRIBUTE_IND},
    {CBT_QueryPaTempByPhyChan,     APP_OM_PA_TEMP_PHY_CHAN_REQ,       OM_APP_PA_TEMP_PHY_CHAN_IND},



#if (RAT_MODE != RAT_GU)
    {CBT_ATTMode,                  APP_OM_AT_TMODE_REQ,               OM_APP_AT_TMODE_CNF},
    {CBT_ATBandSW,                 APP_OM_AT_BANDSW_REQ,              OM_APP_AT_BANDSW_CNF},
    {CBT_ATFChan,                  APP_OM_AT_FCHAN_REQ,               OM_APP_AT_FCHAN_CNF},
    {CBT_SwitchRfAnt,              APP_OM_SWITCH_RF_ANT_REQ,          OM_APP_SWITCH_RF_ANT_CNF},
#endif


};
VOS_VOID CBT_QueryMsgProc(CBT_UNIFORM_MSG_STRU * pRspPacket)
{
    VOS_UINT32               ulIndex;
    VOS_UINT32               ulTotalNum;
    VOS_UINT16               usPrimId;
    VOS_UINT16               usReturnPrimId;
    VOS_UINT32               ulResult = VOS_ERR;

    ulTotalNum = sizeof(g_astCbtMsgFunTbl)/sizeof(CBT_MSG_FUN_STRU);
    usPrimId = pRspPacket->usMsgId;
    /*Search the corresponding function and return PrimId*/
    for (ulIndex = 0; ulIndex < ulTotalNum; ulIndex++)
    {
        if (usPrimId == (VOS_UINT16)(g_astCbtMsgFunTbl[ulIndex].ulPrimId))
        {
            usReturnPrimId = (VOS_UINT16)(g_astCbtMsgFunTbl[ulIndex].ulReturnPrimId);
            ulResult = g_astCbtMsgFunTbl[ulIndex].pfCbtFun(pRspPacket, usReturnPrimId);
            break;
        }
    }

    /*Can't find the function handles the usPrimId.*/
    if (ulIndex == ulTotalNum)
    {
        CBT_SendResultChannel(pRspPacket->stMsgHeader.stModemSsid, pRspPacket->stCompMode, usPrimId, ulResult);
    }

    return;
}

VOS_UINT32 CBT_ComposeSendMsg(CBT_UNIFORM_MSG_STRU * pstUniformMsg, VOS_UINT32 ulReceiverPid)
{
    VOS_UINT32                          ulLength;
    CBT_SEND_COMM_MSG_STRU             *pstMsg;

    ulLength = pstUniformMsg->ulMsgLength;

    pstMsg = (CBT_SEND_COMM_MSG_STRU *)VOS_AllocMsg(CCPU_PID_CBT, ulLength + CBT_MSG_ID_COMP_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_ERR;
    }

    pstMsg->ulReceiverPid = ulReceiverPid;

    pstMsg->usMsgId = pstUniformMsg->usMsgId;

    /*lint -e534*/
    VOS_MemCpy(&pstMsg->usCompMode, &pstUniformMsg->stCompMode, sizeof(VOS_UINT16));
    VOS_MemCpy(pstMsg->aucPara, pstUniformMsg->aucPara, ulLength);

    VOS_SendMsg(CCPU_PID_CBT, pstMsg);
    /*lint +e534*/

    return VOS_OK;
}


VOS_VOID CBT_PsMsgProc(CBT_UNIFORM_MSG_STRU * pstUniformMsg)
{
    VOS_UINT32                          ulReceivePid;
    VOS_UINT8                           ucMode;

    ucMode = pstUniformMsg->stCompMode.ucMode;

    if (CBT_MODE_TDS == ucMode)
    {
        ulReceivePid = TPS_PID_MAC;
    }
    else
    {
        return;
    }

    (VOS_VOID)CBT_ComposeSendMsg(pstUniformMsg, ulReceivePid);

    return;
}

VOS_VOID CBT_RfMsgProc(CBT_UNIFORM_MSG_STRU * pRspPacket)
{
    VOS_UINT32                          ulReceivePid;
    VOS_UINT8                           ucMode;

    ucMode = pRspPacket->stCompMode.ucMode;

    if ((CBT_MODE_LTE == ucMode) || (CBT_MODE_TDS == ucMode))
    {
        ulReceivePid = TLPHY_PID_RTTAGENT;
    }

    else if (CBT_MODE_CDMA == ucMode)
    {
        ulReceivePid = DSP_PID_PROCSTUB;
    }

    else if (CBT_MODE_UMTS == ucMode)
    {
        ulReceivePid = DSP_PID_WPHY;
    }

    else
    {
        if (MODEM_ID_1 == pRspPacket->stMsgHeader.stModemSsid.ucModem)
        {
            ulReceivePid = I1_DSP_PID_GPHY;   /*���͸���1��PID*/
        }
        else
        {
            ulReceivePid = I0_DSP_PID_GPHY;   /*���͸���0��PID*/
        }
    }

    (VOS_VOID)CBT_ComposeSendMsg(pRspPacket, ulReceivePid);

    return;
}


VOS_VOID CBT_NoSigMsgProc(CBT_UNIFORM_MSG_STRU * pRspPacket)
{
    MsgBlock                           *pstMsg;
    VOS_UINT32                          usLength;

    usLength = pRspPacket->ulMsgLength;

    pstMsg = VOS_AllocMsg(CCPU_PID_CBT, usLength + CBT_MSG_HEAD_EX_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->ulReceiverPid = WUEPS_PID_NOSIG;

    /*lint -e534*/
    VOS_MemCpy((VOS_UINT8*)(pstMsg->aucValue), (VOS_UINT8*)pRspPacket, usLength + CBT_MSG_HEAD_EX_LENGTH);
    /*lint +e534*/

    (VOS_VOID)VOS_SendMsg(CCPU_PID_CBT, pstMsg);

    return;
}

VOS_VOID CBT_MMAMsgProc(MsgBlock* pMsg)
{
    MN_APP_PHONE_EVENT_INFO_STRU     *pstEvent;
    VOS_UINT16                        usPrimId;

    CBT_MODEM_SSID_STRU               stModemSsid;
    CBT_COMPONENT_MODE_STRU           stCompMode;

    usPrimId = *(VOS_UINT16*)(pMsg->aucValue);

    /*lint -e534*/
    VOS_MemSet(&stModemSsid, 0, sizeof(CBT_MODEM_SSID_STRU));
    VOS_MemSet(&stCompMode, 0, sizeof(CBT_COMPONENT_MODE_STRU));
    /*lint +e534*/

    if(TAF_OAM_PHONE_EVENT_IND != usPrimId)
    {
        CBT_SendResultChannel(stModemSsid, stCompMode, OM_APP_SET_FTM_CNF, VOS_ERR);
        return;
    }

    pstEvent  = (MN_APP_PHONE_EVENT_INFO_STRU *)pMsg;
    if(OAM_CLIENT_ID_CBT != pstEvent->stPhoneEvent.ClientId)
    {
        CBT_SendResultChannel(stModemSsid, stCompMode, OM_APP_SET_FTM_CNF, VOS_ERR);
        return;
    }

    stModemSsid.ucModem = (VOS_UINT8)VOS_GetModemIDFromPid(pMsg->ulSenderPid);
    stModemSsid.ucSsid  = CBT_SSID_MODEM_CPU;

    stCompMode.ucCompID = CBT_COMP_FUNC;

    CBT_SendResultChannel(stModemSsid, stCompMode, OM_APP_SET_FTM_CNF, pstEvent->stPhoneEvent.PhoneError);
}

VOS_UINT8 CBT_CompModeToSsId(VOS_UINT8 ucCompMode)
{
    VOS_UINT8 ucSsid = CBT_SSID_GU_DSP;

    switch(ucCompMode)
    {
        case CBT_MODE_LTE:
            ucSsid = CBT_SSID_LTE_DSP;
            break;
        case CBT_MODE_TDS:
            ucSsid = CBT_SSID_TDS_DSP;
            break;
        case CBT_MODE_GSM:
        case CBT_MODE_UMTS:
            ucSsid = CBT_SSID_GU_DSP;
            break;
        case CBT_MODE_CDMA:
            ucSsid = CBT_SSID_X_DSP;
            break;
        default:
            break;
    }

    return ucSsid;
}


VOS_VOID CBT_GutlcPsMsgProc(MsgBlock* pMsg)
{
    VOS_UINT8                           ucModemStru;
    VOS_UINT32                          ulTotalSize;
    VOS_UINT32                          ulMsgConetextLength;

    CBT_RCV_TRANS_MSG_STRU             *pstPs2CbtRsp = VOS_NULL_PTR;
    CBT_UNIFORM_MSG_STRU               *pstCbtToAppMsg = VOS_NULL_PTR;

    ulMsgConetextLength = pMsg->ulLength - 2*sizeof(VOS_UINT16);

    pstPs2CbtRsp = (CBT_RCV_TRANS_MSG_STRU *)((VOS_UINT8*)(pMsg->aucValue));

    /*Transfrom PHY msg to Standard Message format*/
    ulTotalSize = CBT_MSG_HEAD_EX_LENGTH + (ulMsgConetextLength - CBT_MSG_ID_COMP_LENGTH);
    pstCbtToAppMsg = (CBT_UNIFORM_MSG_STRU *)VOS_MemAlloc(CCPU_PID_CBT,
                                      DYNAMIC_MEM_PT, ulTotalSize);

    if(VOS_NULL_PTR == pstCbtToAppMsg)
    {
        return;
    }

    CBT_ResetMsgHead(pstCbtToAppMsg);

    ucModemStru = (VOS_UINT8)CBT_MODEM_SSID_COMBINE(VOS_GetModemIDFromPid(pMsg->ulSenderPid), \
                                CBT_CompModeToSsId(CBT_GET_COMPMODE_MODE(pstPs2CbtRsp->usCompMode)));
    (VOS_VOID)VOS_MemCpy(&pstCbtToAppMsg->stMsgHeader.stModemSsid, &ucModemStru, sizeof(ucModemStru));

    pstCbtToAppMsg->usMsgId             = pstPs2CbtRsp->usMsgId;

    /*lint -e534*/
    VOS_MemCpy(&pstCbtToAppMsg->stCompMode, &pstPs2CbtRsp->usCompMode, sizeof(VOS_UINT16));
    /*lint +e534*/

    /*MsgId(Rsv) has been assigned, so need to sub*/
    pstCbtToAppMsg->ulMsgLength = ulMsgConetextLength - CBT_MSG_ID_COMP_LENGTH;

    /*lint -e534*/
    VOS_MemCpy(pstCbtToAppMsg->aucPara, pstPs2CbtRsp->aucPara, pstCbtToAppMsg->ulMsgLength);
    CBT_SendData(pstCbtToAppMsg, (VOS_UINT16)(pstCbtToAppMsg->ulMsgLength + CBT_MSG_HEAD_EX_LENGTH));
    VOS_MemFree(CCPU_PID_CBT, pstCbtToAppMsg);
    /*lint +e534*/
}

VOS_VOID CBT_TraceConfirm(MsgBlock* pMsg)
{
    VOS_UINT16                          usPrimId;
    VOS_UINT16                          usPrimIdLen;
    CBT_HOOK_MSG_STRU                  *pstHookMsg;
    MPH_CELL_SB_IND_STRU               *pstSbInd;

    pstHookMsg = (CBT_HOOK_MSG_STRU *)pMsg->aucValue;
    usPrimId   = pstHookMsg->usPrimId;

    if (usPrimId == g_stListmodeCtrl.usRecvPrimId)
    {
        /*�Ƿ��ϱ���Ϣ*/
        if (g_stListmodeCtrl.usEnableReport)
        {
            usPrimIdLen = sizeof(usPrimId);
            /*lint -e534*/
            CBT_GreenChannel(g_stListmodeCtrl.stModemSsid, g_stListmodeCtrl.stCompMode, usPrimId, \
                                (VOS_UINT8 *)(&pstHookMsg->usReserve), (VOS_UINT16)(pMsg->ulLength - usPrimIdLen));
            /*lint +e534*/
        }

        if (ID_MPH_CELL_SB_IND == usPrimId)
        {
            pstSbInd = (MPH_CELL_SB_IND_STRU *)pMsg;
            if (0 != pstSbInd->usErrCode)
            {
                (VOS_VOID)LogPrint1("CBT_ListmodeTransProc: SB Ind Error code: %d\r\n", pstSbInd->usErrCode);
                return;
            }
        }

        /*lint -e534*/
        VOS_SmV(g_stListmodeCtrl.ulCbtSyncSem);
        /*lint +e534*/
    }
    return;
}
VOS_VOID CBT_GeBer(MsgBlock* pMsg)
{
    /*lint -e813*/
    CBT_LIST_MODE_BER_IND_STRU              stBerDataInd;
    /*lint +e813*/
    GPHY_VOICE_RX_DATA_IND_STRU            *pstGsmBerInfo;

    if (g_stListmodeCtrl.usCurReportFrameNum < g_stListmodeCtrl.usReportFrameNum)
    {
        pstGsmBerInfo = (GPHY_VOICE_RX_DATA_IND_STRU *)pMsg;

        stBerDataInd.usTotalFrameNum = g_stListmodeCtrl.usReportFrameNum;
        stBerDataInd.usCurFrameNum   = g_stListmodeCtrl.usCurReportFrameNum;
        stBerDataInd.usBand          = (VOS_UINT16)g_stListmodeCtrl.ulBand;
        stBerDataInd.usRxChan        = g_stListmodeCtrl.usRxChan;
        stBerDataInd.usCrcData       = (0==pstGsmBerInfo->enBfi)? 1 : 0; /* Ϊ�˺�wcdma��crc����һ�£���һ��ת��*/

        g_stListmodeCtrl.usCurReportFrameNum++;

        stBerDataInd.ulDataLen = GPHY_VOICE_DATA_LEN * sizeof(VOS_UINT16) - 1;

        (VOS_VOID)VOS_MemCpy(stBerDataInd.aucData, pstGsmBerInfo->puhwData, stBerDataInd.ulDataLen);

        stBerDataInd.ulMsgLength = sizeof(stBerDataInd) - CBT_MSG_HEAD_EX_LENGTH;
        CBT_SendContentChannel(g_stListmodeCtrl.stModemSsid, g_stListmodeCtrl.stCompMode, OM_APP_LISTMODE_BT_BER_IND, (CBT_UNIFORM_MSG_STRU *)&stBerDataInd);
    }
    return;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID CBT_SendCSyncStatus(MsgBlock *pMsg)
{
    VOS_UINT16                              usFrameIndex;
    VOS_UINT16                              usFrameCount;
    CSDR_CPROC_1X_FER_MEAS_REPORT_IND_STRU *pstFrameMeasReport;

    pstFrameMeasReport = (CSDR_CPROC_1X_FER_MEAS_REPORT_IND_STRU *)pMsg;
    /*����ͳ��FCH�ŵ���֡��*/
    if (CSDR_1X_TRUE != pstFrameMeasReport->enFchPowerMeasFlag)
    {
        return ;
    }

    usFrameCount = pstFrameMeasReport->stFchPowerMeas.uhwNumFrames;
    for (usFrameIndex=0; usFrameIndex < usFrameCount; usFrameIndex++)
    {
        if (CSDR_1X_FALSE == pstFrameMeasReport->stFchPowerMeas.aenGoodFrame[usFrameIndex])
        {
            /*lint -e534*/
            /* ����ʧ�� ����Ϣ�����ظ�PC ������*/
            CBT_GreenChannel(g_stListmodeCtrl.stModemSsid, g_stListmodeCtrl.stCompMode, pstFrameMeasReport->enMsgId, \
                                (VOS_UINT8 *)(&pstFrameMeasReport->uhwOpId), (VOS_UINT16)(pMsg->ulLength - sizeof(VOS_UINT16)));
            /*lint +e534*/

            /* �ٽ����Ҳ���� */
            CBT_SendResultChannel(g_stListmodeCtrl.stModemSsid, g_stListmodeCtrl.stCompMode, OM_APP_NON_SIG_BT_C_SYNC_CNF, (VOS_UINT32)CBT_C_SYNC_STATUS_OUT_OF_SYNC);
            return;
        }
    }

    CBT_SendResultChannel(g_stListmodeCtrl.stModemSsid, g_stListmodeCtrl.stCompMode, OM_APP_NON_SIG_BT_C_SYNC_CNF, (VOS_UINT32)CBT_C_SYNC_STATUS_SYNC);
    return;
}
VOS_VOID CBT_CFrameMsg(MsgBlock *pMsg)
{
    VOS_UINT16                              usFrameIndex;
    VOS_UINT16                              usFrameCount;
    CBT_C_FER_DATA_CNF_STRU                 stCFerDataCnf;
    CSDR_CPROC_1X_FER_MEAS_REPORT_IND_STRU *pstFrameMeasReport;

    if (g_stListmodeCtrl.usCurFrameNum < g_stListmodeCtrl.usTotalFrameNum)
    {
        pstFrameMeasReport = (CSDR_CPROC_1X_FER_MEAS_REPORT_IND_STRU *)pMsg;

        /*����ͳ��FCH�ŵ���֡��*/
        if (CSDR_1X_TRUE != pstFrameMeasReport->enFchPowerMeasFlag)
        {
            return ;
        }

        usFrameCount = pstFrameMeasReport->stFchPowerMeas.uhwNumFrames;
        for (usFrameIndex=0; usFrameIndex < usFrameCount; usFrameIndex++)
        {
            if (CSDR_1X_TRUE != pstFrameMeasReport->stFchPowerMeas.aenGoodFrame[usFrameIndex])
            {
                g_usCBadFrames++;
            }
        }
        g_stListmodeCtrl.usCurFrameNum += usFrameCount;
    }

    else if (0 != g_stListmodeCtrl.usTotalFrameNum)
    {
        stCFerDataCnf.usTotalFrameNum = g_stListmodeCtrl.usCurFrameNum;
        stCFerDataCnf.usBadFrameNum   = g_usCBadFrames;

        stCFerDataCnf.ulErrorCode = VOS_OK;
        stCFerDataCnf.ulMsgLength = sizeof(CBT_C_FER_DATA_CNF_STRU) - CBT_MSG_HEAD_EX_LENGTH;

        CBT_SendContentChannel(g_stListmodeCtrl.stModemSsid, g_stListmodeCtrl.stCompMode, OM_APP_NON_SIG_BT_C_FER_CNF, (CBT_UNIFORM_MSG_STRU *)&stCFerDataCnf);

        g_stListmodeCtrl.usCurFrameNum   = 0;
        g_stListmodeCtrl.usTotalFrameNum = 0;
    }
    else
    {
        /* for pclint */
    }
}

VOS_VOID  CBT_RcvLacSyncSendSetTimingReq(MsgBlock* pMsg)
{
    CAS_CPROC_1X_SET_TIMING_REQ_STRU        *pstSetTimingReq;

    pstSetTimingReq = (CAS_CPROC_1X_SET_TIMING_REQ_STRU *)VOS_AllocMsg(CCPU_PID_CBT,
                       sizeof(CAS_CPROC_1X_SET_TIMING_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSetTimingReq)
    {
        (VOS_VOID)LogPrint("CBT_SendSetTimingReq: fail to allocate message");
        return;
    }

    if (VOS_OK != CAS_1X_MAIN_CbtParseSyncInd(pMsg, pstSetTimingReq))
    {
        CBT_SendResultChannel(g_stListmodeCtrl.stModemSsid, g_stListmodeCtrl.stCompMode, CTTF_1X_FLAC_GetSyncIndMsgId(), (VOS_UINT32)VOS_ERR);
        return;
    }

    pstSetTimingReq->ulReceiverPid    = CPROC_PID_1X_CM;
    /* �����Ϣ */
    pstSetTimingReq->enMsgId          = ID_CAS_CPROC_1X_SET_TIMING_REQ;
    pstSetTimingReq->usOpId           = 0;

    /* ������Ϣ */
    (VOS_VOID)VOS_SendMsg(CCPU_PID_CBT, pstSetTimingReq);

    return;
}

#endif


VOS_VOID CBT_ListmodeTransProc(MsgBlock* pMsg)
{
    VOS_UINT16                              usPrimId;

    CBT_GE_DL_STATUS_STRU                   stGeDlStatus;

    MPH_CS_DEDICATED_MEAS_IND_STRU         *pstMphMeasInd;
    MPHP_EGPRS_CHANNEL_QUALITY_REPORT_ST   *stMphpEgrsReport;
    CBT_HOOK_MSG_STRU                      *pstHookMsg;

    pstHookMsg = (CBT_HOOK_MSG_STRU *)pMsg->aucValue;
    usPrimId   = pstHookMsg->usPrimId;

    /*������յ�W��ͬ����ʧ����Ϣ, ��¼��ȫ�ֱ�����*/
    if ( ID_PHY_RRC_SYNC_IND == usPrimId)
    {
        g_stListmodeCtrl.usWSyncStatus = OM_W_SYNC_STATUS_SYNC;
    }
    if ( ID_PHY_RRC_OUT_OF_SYNC_IND == usPrimId)
    {
        g_stListmodeCtrl.usWSyncStatus = OM_W_SYNC_STATUS_OUT_OF_SYNC;
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (ID_CPROC_CCBT_1X_SET_POWER_CNF == usPrimId)
    {
        CBT_SendResultChannel(g_stListmodeCtrl.stModemSsid, g_stListmodeCtrl.stCompMode, OM_APP_BT_C_TX_SET_POWER_CNF, *(VOS_UINT32 *)pstHookMsg->aucPara);
        return;
    }
#endif

    CBT_TraceConfirm(pMsg);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    if (CTTF_1X_FLAC_GetSyncIndMsgId() == usPrimId)
    {
        CBT_RcvLacSyncSendSetTimingReq(pMsg);
        return;
    }

    /*CDMA Frame */
    if (ID_CSDR_CPROC_1X_FER_MEAS_REPORT_IND == usPrimId)
    {
        if (VOS_TRUE == g_stListmodeCtrl.usCReportFlag)
        {
            CBT_SendCSyncStatus(pMsg);

            g_stListmodeCtrl.usCReportFlag = VOS_FALSE;
        }

        CBT_CFrameMsg(pMsg);
        return;
    }

#endif

    /*GSM Ber Report */
    if (ID_GPHY_VOICE_RX_DATA_IND == usPrimId)
    {
        CBT_GeBer(pMsg);
        return;
    }

    /*������յ�GSM/EDGE�ź������Ļظ���Ϣ*/
    if ((ID_MPH_CS_DEDICATED_MEAS_IND == usPrimId)
     && (VOS_TRUE == g_stListmodeCtrl.usGeReportFlag))
    {
        pstMphMeasInd = (MPH_CS_DEDICATED_MEAS_IND_STRU *)pMsg;

        stGeDlStatus.usBerValue[0] = pstMphMeasInd->usMeanBep;
        stGeDlStatus.usBerValue[1] = pstMphMeasInd->usCvBep;
        stGeDlStatus.ulMsgLength   = (VOS_UINT32)(sizeof(stGeDlStatus)- CBT_MSG_HEAD_EX_LENGTH);
        g_stListmodeCtrl.usGeReportFlag = VOS_FALSE;
        CBT_SendContentChannel(g_stListmodeCtrl.stModemSsid, g_stListmodeCtrl.stCompMode, OM_APP_GE_DL_STATUS_CNF, (CBT_UNIFORM_MSG_STRU *)(&stGeDlStatus));

        return;
    }

    if ((ID_MPHP_EGPRS_CHANNEL_QUALITY_REPORT == usPrimId)
     && (VOS_TRUE == g_stListmodeCtrl.usGeReportFlag))
    {
        stMphpEgrsReport = (MPHP_EGPRS_CHANNEL_QUALITY_REPORT_ST *)pMsg;

        stGeDlStatus.usBerValue[0] = stMphpEgrsReport->usMeanBep8Psk;
        stGeDlStatus.usBerValue[1] = stMphpEgrsReport->usCVBep8Psk;
        stGeDlStatus.ulMsgLength   = (VOS_UINT32)(sizeof(stGeDlStatus)- CBT_MSG_HEAD_EX_LENGTH);

        /*ֻ�ϱ�һ�� */
        g_stListmodeCtrl.usGeReportFlag = VOS_FALSE;
        CBT_SendContentChannel(g_stListmodeCtrl.stModemSsid, g_stListmodeCtrl.stCompMode, OM_APP_GE_DL_STATUS_CNF, (CBT_UNIFORM_MSG_STRU *)(&stGeDlStatus));

        return;
    }

    return;
}
VOS_VOID CBT_MsgProc(MsgBlock* pMsg)
{
    VOS_UINT16                          usPrimId;
    VOS_UINT8                           ucComponentID;
    CBT_UNIFORM_MSG_STRU               *pstAppMsg = VOS_NULL_PTR;

    /*send messages to Hids*/
    DIAG_TraceReport((VOS_VOID *)pMsg);

    /*�������Թ��߲����Ϣ*/
    if (PC_PID_TOOL == pMsg->ulSenderPid)
    {
        pstAppMsg = (CBT_UNIFORM_MSG_STRU *)pMsg->aucValue;

        ucComponentID = pstAppMsg->stCompMode.ucCompID;

        switch ( ucComponentID )
        {
            case CBT_COMP_FUNC:
                CBT_QueryMsgProc(pstAppMsg);
                break;

            case CBT_COMP_NOSIG:
                CBT_NoSigMsgProc(pstAppMsg);
                break;

            case CBT_COMP_PHY:
                CBT_RfMsgProc(pstAppMsg);
                break;

            case CBT_COMP_PS:
                CBT_PsMsgProc(pstAppMsg);
                break;

            default:
                CBT_SendResultChannel(pstAppMsg->stMsgHeader.stModemSsid, pstAppMsg->stCompMode, pstAppMsg->usMsgId, VOS_ERR);
                break;
        }
    }
    /*��������MMA����Ϣ*/
    else if((I0_WUEPS_PID_MMA == pMsg->ulSenderPid)
     || (I1_WUEPS_PID_MMA == pMsg->ulSenderPid))
    {
        CBT_MMAMsgProc(pMsg);
    }

    else
    {
        usPrimId = *((VOS_UINT16*)pMsg->aucValue);

        /*����0x5001Ϊ͸����Ϣ������Ϣ͸����PC��*/
        if (OM_TRANS_PRIMID == usPrimId)
        {
            CBT_GutlcPsMsgProc(pMsg);
        }
        else
        {
            CBT_ListmodeTransProc(pMsg);
        }
    }

    return;
}


VOS_UINT32 CBTFidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32 ulRslt;

    switch( ip )
    {
        case VOS_IP_LOAD_CONFIG:
        {

            ulRslt = VOS_RegisterPIDInfo(CCPU_PID_CBT,
                                        (Init_Fun_Type)VOS_NULL_PTR,
                                        (Msg_Fun_Type)CBT_MsgProc);
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterMsgTaskPrio(CCPU_FID_CBT, VOS_PRIORITY_M5);
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            break;
        }

        default:
            break;
    }
    return VOS_OK;
}

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif
