/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: APMProcess.c                                                    */
/*                                                                           */
/*    Author: Jiang KaiBo                                                    */
/*            Xu Cheng                                                       */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2008-02                                                             */
/*                                                                           */
/* Description: process data of APM mailbox                                  */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date:                                                                  */
/*    Author:                                                                */
/*    Modification: Create this file                                         */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include "hpacomm.h"
#include "omprivate.h"
#include "rfa.h"
#include "apminterface.h"
#include "apmprocess.h"
#include "PhyNvInterface.h"
#include "bbp_gsm_interface.h"
#include "bbp_comm_interface.h"
#include "msp_diag_comm.h"

#ifdef __LDF_FUNCTION__
#include "HifiDumpInterface.h"
#include "WasOmInterface.h"
#endif

#include "sleepflow.h"

#if (RAT_MODE != RAT_GU)
#include "product_config.h"
#include "psregrpt.h"
#endif

/* Macro of log */
#define    THIS_FILE_ID        PS_FILE_ID_APM_PROCESS_C


#define     APM_WAITING_LOOP_TIMES      (50)

#define     HPA_DDR_FREQ_TRACK_NUM      (50)

/* ����PHY�ļ���״̬ */
VOS_UINT32                      g_aulShpaActiveState[MODEM_ID_BUTT][VOS_RATMODE_BUTT];

/* Record current RAT mdoe. 2G or 3G */
VOS_UINT32                      g_aulShpaCurSysId[MODEM_ID_BUTT];

/* A semaphor. Get it when succeed to load DSP. */
VOS_SEM                         g_aulShpaLoadPhySemaphor[MODEM_ID_BUTT];

/* A semaphor. Get it when succeed to Active DSP. */
VOS_SEM                         g_aulShpaActivePhySemaphor[MODEM_ID_BUTT];

/* A semaphor. Get it when save data to file. */
VOS_SEM                         g_ulLdfSavingSemaphor;

/* DSP Config info Data */
DSP_CONFIG_CTRL_STRU            g_astDspConfigCtrl[MODEM_ID_BUTT];

/*ϵͳʹ�õĵ�ַ*/
PLATFORM_SYSADDR_STRU           g_stSysAddr;

/* CCPU DDRʹ��ͨ�� */
VOS_INT                         g_lCcpuDDRFreqId = 0;

NV_DDR_ADJUST_ENABLE_STRU       g_stDDRAdjustCFG;

typedef struct
{
    VOS_UINT32                  ulDDRValue;
    VOS_UINT32                  ulSlice;
} HPA_DDR_FREQ_INFO_STRU;

typedef struct
{
    MODEM_ID_ENUM_UINT16                enModem;
    DUALMODEM_SCENE_TYPE_ENUM_UINT16    enSceneType;
    HPA_DDR_FREQ_INFO_STRU              stDDRInfo;
} HPA_DDR_FREQ_DEBUGINFO_STRU;


/*��¼��ͬģ��ĵ�ǰͶƱ��ֵ*/
HPA_DDR_FREQ_INFO_STRU          g_stHpaDDRDfsInfo[MODEM_ID_BUTT][DUALMODEM_SCENCE_BUTT];
VOS_UINT32                      g_ulHpaDDRDfsDebugTrack = 0;
HPA_DDR_FREQ_DEBUGINFO_STRU     g_stHpaDDRDfsDebugInfo[HPA_DDR_FREQ_TRACK_NUM];

#ifndef MIN
#define MIN(a, b)       ((a) < (b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b)       ((a) > (b) ? (a) : (b))
#endif

VOS_UINT_PTR                        g_ulPamBbpCommBaseAddr;

VOS_UINT_PTR                        g_ulPamBbpCommOnBaseAddr;

VOS_UINT_PTR                        g_ulPamBbpGsm0BaseAddr;

VOS_UINT_PTR                        g_ulPamBbpGsm0OnBaseAddr;

VOS_UINT_PTR                        g_ulPamBbpGsm1BaseAddr;

VOS_UINT_PTR                        g_ulPamBbpGsm1OnBaseAddr;

VOS_UINT_PTR                        g_ulPamBbpWcdmaBaseAddr;

VOS_UINT_PTR                        g_ulPamBbpWcdmaOnBaseAddr;

VOS_UINT_PTR                        g_ulPamBbpCdmaBaseAddr;

VOS_UINT_PTR                        g_ulPamBbpCdmaOnBaseAddr;

#if (FEATURE_GUC_BBP_TRIG == FEATURE_ON)
VOS_UINT_PTR                        g_ulPamBbpDgbTrigBaseAddr;
#endif

#ifdef  __LDF_FUNCTION__

/*****************************************************************************
 Function   : SHPA_Ldf_Hifi_Saving
 Description: Save Load HIFI Fail reason
 Input      :
 Return     : void
 Other      :
 *****************************************************************************/
VOS_UINT32 SHPA_Ldf_Hifi_Saving(VOS_VOID)
{
    return VOS_OK;
}
#endif


VOS_UINT32 GHPA_GetRealFN(MODEM_ID_ENUM_UINT16 enModemID)
{
    VOS_UINT16  usFnLow  = 0;
    VOS_UINT16  usFnHigh = 0;
    VOS_UINT32  ulFnReal = 0;
    VOS_UINT32  ulRegValue = 0;

    if (MODEM_ID_BUTT <= enModemID)
    {
        return ulFnReal;
    }

    ulRegValue = HPA_Read32Reg(g_aulGUCBBPRegAddr[GTC_FN][enModemID][VOS_RATMODE_GSM]);

    /* ��֡�ŵ�ַ�ж�ȡ֡�ŵĵ�λ�͸�λ */
    usFnLow  = ((VOS_UINT16)ulRegValue) & 0x07FF;           /*��11������Ч*/
    usFnHigh = ((VOS_UINT16)(ulRegValue >> 16)) & 0x07FF;   /*��11������Ч*/

    /* ���ݹ�ʽ����֡�� */
    ulFnReal = usFnLow + (usFnHigh * 26 * 51);

    return ulFnReal;
}

/*****************************************************************************
 Function   : SHPA_ReadWTxPower
 Description: ����Was�����ȡ�Ĵ���������Ƶ��˴���ȡ���з��书�ʼĴ���
 Input      : ��
 Return     : �Ĵ���ֵ
 Other      : ������Ҫ��˺�����OM�ṩ
 *****************************************************************************/
VOS_UINT32 SHPA_ReadWTxPower( VOS_VOID)
{
#ifndef FEATURE_DSP2ARM
    return HPA_Read32Reg(W_BBP_SLOT_0_UL_TX_POWER_REG);
#endif
    return 0;
}


VOS_VOID APM_ReportEvent(VOS_UINT ulEventData)
{
    DIAG_EVENT_IND_STRU                 stEventInd;

    stEventInd.ulModule = DIAG_GEN_MODULE(DIAG_MODEM_0, DIAG_MODE_COMM);
    stEventInd.ulPid    = UEPS_PID_SHPA;
    stEventInd.ulEventId= VOS_NULL;
    stEventInd.ulLength = sizeof(ulEventData);
    stEventInd.pData    = (VOS_VOID *)(&ulEventData);

    /*lint -e534*/
    (VOS_VOID)DIAG_EventReport(&stEventInd);
    /*lint +e534*/

    return;
}


VOS_UINT32 SHPA_ActiveDSP(VOS_RATMODE_ENUM_UINT32 enRatMode, MODEM_ID_ENUM_UINT16 enModemId)
{
    UPHY_OAM_ACTIVE_UPHY_REQ_STRU      *pstMsg;

    /* Add for L Only version */
    if (PROTOCOL_TYPE_LTE_ONLY == VOS_GetProtocolType())
    {
        return VOS_OK;
    }

    if((MODEM_ID_BUTT <= enModemId)||(VOS_RATMODE_LTE == enRatMode)||(VOS_RATMODE_TDS == enRatMode))
    {
        PS_LOG(UEPS_PID_SHPA, 0, PS_PRINT_ERROR,"SHPA_ActiveDSP: Para Err");
        return VOS_ERR;
    }

    /*lint -e662 -e661*/

    /* �Ѿ�����PHY�������ټ��� */
    if (VOS_TRUE == g_aulShpaActiveState[enModemId][enRatMode])
    {
        /*lint -e534*/
        LogPrint1("SHPA_ActiveDSP: Modem %d Has Actived !\r\n", enModemId);
        /*lint +e534*/

        return VOS_OK;
    }

    /*lint -e534*/
    LogPrint1("SHPA_ActiveDSP: Modem %d Active Start !\r\n", enModemId);
    /*lint +e534*/

    g_astDspConfigCtrl[enModemId].ulDSPActiveSlice = OM_GetSlice();

    if (MODEM_ID_1 == enModemId)
    {
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
        I1_SLEEP_VoteLock(enRatMode);

        I1_SLEEP_PowerUp(enRatMode);
#endif
    }
    else if (MODEM_ID_2 == enModemId)
    {
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
#if ( 3 == MULTI_MODEM_NUMBER )
        I2_SLEEP_VoteLock(enRatMode);

        I2_SLEEP_PowerUp(enRatMode);
#endif
#endif
    }
    else
    {
        SLEEP_VoteLock(enRatMode);

        SLEEP_PowerUp(enRatMode);
    }

    /* ����DSP����Ϣ��PID��SHPA*/
    pstMsg = (UPHY_OAM_ACTIVE_UPHY_REQ_STRU*)VOS_AllocMsg(UEPS_PID_SHPA, sizeof(UPHY_OAM_ACTIVE_UPHY_REQ_STRU)- VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)  /*�˴�ʧ�ܻḴλ����˲���Ҫ��¼����*/
    {
        PS_LOG(UEPS_PID_SHPA, 0, PS_PRINT_ERROR,"SHPA_ActiveDSP: VOS_AllocMsg Err");
        return VOS_ERR;
    }

    if (MODEM_ID_1 == enModemId)
    {
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
        pstMsg->ulReceiverPid   = I1_DSP_PID_APM;
#endif
    }
    else if (MODEM_ID_2 == enModemId)
    {
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
#if ( 3 == MULTI_MODEM_NUMBER )
        pstMsg->ulReceiverPid   = I2_DSP_PID_APM;
#endif
#endif
    }
    else
    {
        pstMsg->ulReceiverPid   = I0_DSP_PID_APM;
    }

    pstMsg->enMsgId         = ID_OAM_UPHY_ACTIVE_UPHY_REQ;
    pstMsg->enModem         = enModemId;
    pstMsg->enRatTpye       = enRatMode;

    if(VOS_ERR == VOS_SendMsg(UEPS_PID_SHPA, pstMsg))
    {
        PS_LOG(UEPS_PID_SHPA, 0, PS_PRINT_ERROR,"SHPA_ActiveDSP: VOS_SendMsg Err");
        return VOS_ERR;
    }

    g_astDspConfigCtrl[enModemId].enActiveState = APM_SENDED_MSG;

    g_astDspConfigCtrl[enModemId].ulActiveSmPResult
                = VOS_SmP(g_aulShpaActivePhySemaphor[enModemId], SHPA_TMR_LOAD_PHY_INTERVAL);

    if( VOS_OK != g_astDspConfigCtrl[enModemId].ulActiveSmPResult)
    {
        PS_LOG1(UEPS_PID_SHPA, 0, PS_PRINT_ERROR,"SHPA_ActiveDSP: Modem %d g_ulShpaActivePhySemaphor Timeout!\r\n", enModemId);

        g_astDspConfigCtrl[enModemId].enErrorCode = DSP_ACTIVE_TIME_OUT;

        VOS_ProtectionReboot(OAM_PROTECTION_DSP_Init, VOS_FILE_ID, __LINE__, (VOS_CHAR *)(g_astDspConfigCtrl), sizeof(g_astDspConfigCtrl));

        return VOS_ERR;
    }

    if(UPHY_OAM_RSLT_SUCC != g_astDspConfigCtrl[enModemId].ulActiveResult)
    {
        PS_LOG1(UEPS_PID_SHPA, 0, PS_PRINT_ERROR,"SHPA_ActiveDSP: Modem %d Active FAIL!\r\n", enModemId);

        VOS_ProtectionReboot(OAM_PROTECTION_DSP_Init, VOS_FILE_ID, __LINE__, (VOS_CHAR *)(g_astDspConfigCtrl), sizeof(g_astDspConfigCtrl));

        return VOS_ERR;
    }

    /* �Ѿ����� */
    g_aulShpaActiveState[enModemId][enRatMode] = VOS_TRUE;

    /*lint +e662 +e661 -e534*/

    LogPrint1("SHPA_ActiveDSP: Modem %d Active end !\r\n", enModemId);
    /*lint +e534*/

    return VOS_OK;
}


VOS_UINT16 SHPA_LoadPhy( PHY_OAM_SET_WORK_MODE_REQ_STRU stSetWorkMode )
{
    PHY_OAM_SET_WORK_MODE_REQ_STRU      *pstSetWorkModeReq;

    g_astDspConfigCtrl[stSetWorkMode.enModem].ulDSPLoadSlice = OM_GetSlice();

    pstSetWorkModeReq = (PHY_OAM_SET_WORK_MODE_REQ_STRU *)VOS_AllocMsg(UEPS_PID_SHPA, sizeof(PHY_OAM_SET_WORK_MODE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSetWorkModeReq)
    {
        /*lint -e534*/
        LogPrint("SHPA_LoadPhy: VOS_AllocMsg Fail!\r\n");
        /*lint +e534*/
        return VOS_FALSE;
    }

    pstSetWorkModeReq->enMsgId          = stSetWorkMode.enMsgId;

    pstSetWorkModeReq->ulReceiverPid    = stSetWorkMode.ulReceiverPid;
    pstSetWorkModeReq->enModem          = stSetWorkMode.enModem;
    pstSetWorkModeReq->enMasterMode     = stSetWorkMode.enMasterMode;
    pstSetWorkModeReq->enSlaveMode      = stSetWorkMode.enSlaveMode;
    pstSetWorkModeReq->enBusinessType   = stSetWorkMode.enBusinessType;
    pstSetWorkModeReq->enPhyInitFlag    = stSetWorkMode.enPhyInitFlag;
    pstSetWorkModeReq->enNvUpdateFlag   = stSetWorkMode.enNvUpdateFlag;

    if (VOS_OK != VOS_SendMsg(UEPS_PID_SHPA, pstSetWorkModeReq))
    {
        /*lint -e534*/
        LogPrint("SHPA_LoadPhy:Waring: VOS_SendMsg Error!\r\n");
        /*lint +e534*/
        return VOS_FALSE;
    }

    /*lint -e662 -e661*/
    g_astDspConfigCtrl[stSetWorkMode.enModem].enLoadState = APM_SENDED_MSG;

    g_astDspConfigCtrl[stSetWorkMode.enModem].ulLoadSmPResult
                    = VOS_SmP(g_aulShpaLoadPhySemaphor[stSetWorkMode.enModem],SHPA_TMR_LOAD_PHY_INTERVAL);

    if( VOS_OK !=  g_astDspConfigCtrl[stSetWorkMode.enModem].ulLoadSmPResult)
    {
        /*lint -e534*/
        LogPrint1("SHPA_LoadPhy:Waring: Modem %d g_aulShpaLoadPhySemaphor Timeout!\r\n", stSetWorkMode.enModem);
        /*lint +e534*/

        g_astDspConfigCtrl[stSetWorkMode.enModem].enErrorCode = CPHY_DSP_LOAD_TIMEOUT;

        APM_ReportEvent(g_astDspConfigCtrl[stSetWorkMode.enModem].enErrorCode);

        VOS_ProtectionReboot(OAM_PROTECTION_LOAD_DSP, THIS_FILE_ID, __LINE__, VOS_NULL_PTR, 0);

        return VOS_FALSE;
    }

    if(UPHY_OAM_RSLT_SUCC != g_astDspConfigCtrl[stSetWorkMode.enModem].ulLoadResult)
    {
        PS_LOG1( UEPS_PID_SHPA, 0, PS_PRINT_WARNING, "SHPA_LoadPhy:Modem %d Load DSP Failed, Reboot it!", stSetWorkMode.enModem);

        /*lint -e534*/
        LogPrint1("Load DSP Failed, g_ulShpaLoadPhyStatusis %d\r\n",(VOS_INT)g_astDspConfigCtrl[stSetWorkMode.enModem].ulLoadResult);
        /*lint +e534*/

        VOS_ProtectionReboot(OAM_PROTECTION_LOAD_DSP, THIS_FILE_ID, __LINE__, VOS_NULL_PTR, 0);

        return VOS_FALSE;
    }
    /*lint +e662 +e661*/

    /*lint -e534*/
    LogPrint1("SHPA_LoadPhy: Modme %d Load OK !\r\n", stSetWorkMode.enModem);
    /*lint +e534*/

    return VOS_TRUE;
}

/*****************************************************************************
 Function   :APM_InitSystemAddr
 Description:Read the Dsp Nv Data
 Input      :VOS_VOID
 Return     :VOS_ERR/VOS_OK
 Other      :
 *****************************************************************************/
VOS_UINT32 APM_InitSystemAddr(VOS_VOID)
{
    BSP_AXI_SECT_INFO_S                 stAXIInfo;

    /*lint -e534*/
    VOS_MemSet(&g_stSysAddr, 0, sizeof(g_stSysAddr));
    /*lint +e534*/

    g_stSysAddr.ulAHBBaseAddr       = (VOS_UINT_PTR)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_AHB);

    if(0 == g_stSysAddr.ulAHBBaseAddr)
    {
        /*lint -e534*/
        LogPrint("APM_InitSystemAddr: BSP_IP_TYPE_AHB Addr Get Error!\r\n");
        /*lint +e534*/
        return VOS_ERR;
    }

    g_stSysAddr.ulWBBPBaseAddr      = (VOS_UINT_PTR)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_WBBP);

    if(0 == g_stSysAddr.ulWBBPBaseAddr)
    {
        /*lint -e534*/
        LogPrint("APM_InitSystemAddr: BSP_IP_TYPE_WBBP Addr Get Error!\r\n");
        /*lint +e534*/
        return VOS_ERR;
    }

    g_stSysAddr.ulWBBPDRXBaseAddr   = (VOS_UINT_PTR)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_WBBP_DRX);

    if(0 == g_stSysAddr.ulWBBPDRXBaseAddr)
    {
        /*lint -e534*/
        LogPrint("APM_InitSystemAddr: BSP_IP_TYPE_WBBP_DRX Addr Get Error!\r\n");
        /*lint +e534*/
        return VOS_ERR;
    }

    g_stSysAddr.ulGBBPBaseAddr      = (VOS_UINT_PTR)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_GBBP);

    if(0 == g_stSysAddr.ulGBBPBaseAddr)
    {
        /*lint -e534*/
        LogPrint("APM_InitSystemAddr: BSP_IP_TYPE_GBBP Addr Get Error!\r\n");
        /*lint +e534*/
        return VOS_ERR;
    }

    g_stSysAddr.ulGBBPDRXBaseAddr   = (VOS_UINT_PTR)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_GBBP_DRX);

    if(0 == g_stSysAddr.ulGBBPDRXBaseAddr)
    {
        /*lint -e534*/
        LogPrint("APM_InitSystemAddr: BSP_IP_TYPE_GBBP_DRX Addr Get Error!\r\n");
        /*lint +e534*/
        return VOS_ERR;
    }

    g_stSysAddr.ulGBBP1BaseAddr      = (VOS_UINT_PTR)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_GBBP1);

    g_stSysAddr.ulGBBP1DRXBaseAddr   = (VOS_UINT_PTR)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_GBBP1_DRX);

    /*ֻ��˫���汾�Ŷ��ڴ˵�ַ�жϣ������汾��V3R3���ж�����ʹ�õ���ķ���ֵ*/
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
    if(0 == g_stSysAddr.ulGBBP1BaseAddr)
    {
        /*lint -e534*/
        LogPrint("APM_InitSystemAddr: BSP_IP_TYPE_GBBP1 Addr Get Error!\r\n");
        /*lint +e534*/
        return VOS_ERR;
    }

    if(0 == g_stSysAddr.ulGBBP1DRXBaseAddr)
    {
        /*lint -e534*/
        LogPrint("APM_InitSystemAddr: BSP_IP_TYPE_GBBP1_DRX Addr Get Error!\r\n");
        /*lint +e534*/
        return VOS_ERR;
    }
#endif

    g_stSysAddr.ulSYSCTRLBaseAddr   = (VOS_UINT_PTR)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_SYSCTRL);

    if(0 == g_stSysAddr.ulSYSCTRLBaseAddr)
    {
        /*lint -e534*/
        LogPrint("APM_InitSystemAddr: BSP_IP_TYPE_SYSCTRL Addr Get Error!\r\n");
        /*lint +e534*/
        return VOS_ERR;
    }

    g_stSysAddr.ulBBPCommBaseAddr   = (VOS_UINT_PTR)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_BBP_COMM);

    g_stSysAddr.ulBBPCommOnBaseAddr = (VOS_UINT_PTR)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_BBP_COMM_ON);

    if(0 == g_stSysAddr.ulBBPCommBaseAddr)
    {
        /*lint -e534*/
        LogPrint("APM_InitSystemAddr: BSP_IP_TYPE_BBP_COMM Addr Get Error!\r\n");
        /*lint +e534*/
        return VOS_ERR;
    }

    if(0 == g_stSysAddr.ulBBPCommOnBaseAddr)
    {
        /*lint -e534*/
        LogPrint("APM_InitSystemAddr: BSP_IP_TYPE_BBP_COMM_ON Addr Get Error!\r\n");
        /*lint +e534*/
        return VOS_ERR;
    }

    g_stSysAddr.ulCDMABBPBaseAddr      = (VOS_UINT_PTR)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_BBP_CDMA);

    g_stSysAddr.ulCDMABBPDRXBaseAddr   = (VOS_UINT_PTR)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_BBP_CDMA_ON);
#if  (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if(0 == g_stSysAddr.ulCDMABBPBaseAddr)
    {
        /*lint -e534*/
        LogPrint("APM_InitSystemAddr: BSP_IP_TYPE_BBP_CDMA Addr Get Error!\r\n");
        /*lint +e534*/
        return VOS_ERR;
    }

    if(0 == g_stSysAddr.ulCDMABBPDRXBaseAddr)
    {
        /*lint -e534*/
        LogPrint("APM_InitSystemAddr: BSP_IP_TYPE_BBP_CDMA_ON Addr Get Error!\r\n");
        /*lint +e534*/
        return VOS_ERR;
    }
#endif


    if(VOS_OK != mdrv_get_fix_axi_addr(BSP_AXI_SECT_TYPE_HIFI, &stAXIInfo))
    {
        /*lint -e534*/
        LogPrint("APM_InitSystemAddr: BSP_AXI_SECT_TYPE_HIFI Addr Get Error!\r\n");
        /*lint +e534*/
        return VOS_ERR;
    }

    g_stSysAddr.ulHIFIAXIBaseAddr   = (VOS_UINT_PTR)stAXIInfo.pSectVirtAddr; /*�ϲ������ַ*/

    if(VOS_OK != mdrv_get_fix_axi_addr(BSP_AXI_SECT_TYPE_TEMPERATURE, &stAXIInfo))
    {
        /*lint -e534*/
        LogPrint("APM_InitSystemAddr: BSP_AXI_SECT_TYPE_TEMPERATURE Addr Get Error!\r\n");
        /*lint +e534*/
        return VOS_ERR;
    }

    g_stSysAddr.ulDSPTempBaseAddr   = (VOS_UINT_PTR)stAXIInfo.pSectVirtAddr; /*�ϲ������ַ*/

#ifdef FEATURE_DSP2ARM
    UCOM_SetTemparatureAddr(g_stSysAddr.ulDSPTempBaseAddr);
#endif

#ifdef FEATURE_DSP2ARM
    /*���DSP������Ϣ�ĸ���*/
    if ( VOS_OK != mdrv_dsp_update_shareinfo(UCOM_GetDspShareMemAddr()) )
    {
        PS_LOG( UEPS_PID_SHPA, 0, PS_PRINT_ERROR," SHPA_AcitiveDSP:Write DSP Config Info Failed.");

        VOS_ProtectionReboot(OAM_PROTECTION_DSP_SHARE, VOS_FILE_ID, __LINE__, (VOS_CHAR *)(g_astDspConfigCtrl), sizeof(g_astDspConfigCtrl));

        return VOS_ERR;
    }
#endif

    g_ulPamBbpCommBaseAddr      = g_stSysAddr.ulBBPCommBaseAddr;

    g_ulPamBbpCommOnBaseAddr    = g_stSysAddr.ulBBPCommOnBaseAddr;

    g_ulPamBbpGsm0BaseAddr      = g_stSysAddr.ulGBBPBaseAddr;

    g_ulPamBbpGsm0OnBaseAddr    = g_stSysAddr.ulGBBPDRXBaseAddr;

    g_ulPamBbpGsm1BaseAddr      = g_stSysAddr.ulGBBP1BaseAddr;

    g_ulPamBbpGsm1OnBaseAddr    = g_stSysAddr.ulGBBP1DRXBaseAddr;

    g_ulPamBbpWcdmaBaseAddr     = g_stSysAddr.ulWBBPBaseAddr;

    g_ulPamBbpWcdmaOnBaseAddr   = g_stSysAddr.ulWBBPDRXBaseAddr;

    g_ulPamBbpCdmaBaseAddr      = g_stSysAddr.ulCDMABBPBaseAddr;

    g_ulPamBbpCdmaOnBaseAddr    = g_stSysAddr.ulCDMABBPDRXBaseAddr;

#if (FEATURE_GUC_BBP_TRIG == FEATURE_ON)
    g_ulPamBbpDgbTrigBaseAddr   = g_stSysAddr.ulBBPCommBaseAddr & 0xff000000;
#endif

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : HPA_DspAcitveCnf
 ��������  : Handle the DSP Active Cnf Msg
 �������  : PHY_OAM_MSG_STRU *pstRcvMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   :
    ��    ��   :
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID HPA_DspAcitveCnf(PHY_OAM_MSG_STRU *pstMsg)
{
    UPHY_OAM_ACTIVE_UPHY_CNF_STRU   *pstDspMsg;

    pstDspMsg = (UPHY_OAM_ACTIVE_UPHY_CNF_STRU *)pstMsg;

    if(MODEM_ID_BUTT <= pstDspMsg->enModem)
    {
        PS_LOG(UEPS_PID_SHPA, 0, PS_PRINT_ERROR,"HPA_DspAcitveCnf: the Msg Modem ID is Error");

        VOS_ProtectionReboot(OAM_PROTECTION_DSP_Init, VOS_FILE_ID, __LINE__, (VOS_CHAR *)(&pstDspMsg), sizeof(UPHY_OAM_ACTIVE_UPHY_CNF_STRU));

        return;
    }

    g_astDspConfigCtrl[pstDspMsg->enModem].ulDSPActCnfSlice = OM_GetSlice();

    g_astDspConfigCtrl[pstDspMsg->enModem].enActiveState = APM_RECEIVED_MSG;

    g_astDspConfigCtrl[pstDspMsg->enModem].ulActiveResult= pstDspMsg->enRslt;

    /*lint -e534*/
    VOS_SmV(g_aulShpaActivePhySemaphor[pstDspMsg->enModem]);
    /*lint +e534*/

    return;
}


/*****************************************************************************
 �� �� ��  : HPA_DspLoadCnf
 ��������  : Handle the DSP Load Cnf Msg
 �������  : PHY_OAM_MSG_STRU *pstRcvMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   :
    ��    ��   :
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID HPA_DspLoadCnf(PHY_OAM_MSG_STRU *pstMsg)
{
    PHY_OAM_SET_WORK_MODE_CNF_STRU      *pstDspMsg;

    pstDspMsg = (PHY_OAM_SET_WORK_MODE_CNF_STRU *)pstMsg;

    if(MODEM_ID_BUTT <= pstDspMsg->enModem)
    {
        PS_LOG(UEPS_PID_SHPA, 0, PS_PRINT_ERROR,"HPA_DspLoadCnf: the Msg Modem ID is Error");

        VOS_ProtectionReboot(OAM_PROTECTION_DSP_Init, VOS_FILE_ID, __LINE__, (VOS_CHAR *)(&pstDspMsg), sizeof(PHY_OAM_LOAD_PHY_CNF_STRU));

        return;
    }

    g_astDspConfigCtrl[pstDspMsg->enModem].ulDSPLoadCnfSlice = OM_GetSlice();

    g_astDspConfigCtrl[pstDspMsg->enModem].enLoadState   = APM_RECEIVED_MSG;

    g_astDspConfigCtrl[pstDspMsg->enModem].ulLoadResult = pstDspMsg->enRslt;

    /*lint -e534*/
    VOS_SmV(g_aulShpaLoadPhySemaphor[pstDspMsg->enModem]);
    /*lint +e534*/

    return;
}


VOS_VOID HPA_ApmMsgPIDProc(MsgBlock *pstRcvMsg)
{
#ifdef FEATURE_DSP2ARM
    PHY_OAM_MSG_STRU              *pstMsg;

    pstMsg = (PHY_OAM_MSG_STRU *)pstRcvMsg;

    switch(pstMsg->usMsgId)
    {
        case ID_PHY_OAM_SET_WORK_MODE_CNF:
            HPA_DspLoadCnf(pstMsg);
            break;

        case ID_UPHY_OAM_ACTIVE_UPHY_CNF:
            HPA_DspAcitveCnf(pstMsg);
            break;

        default:
            break;
    }

#endif
    return;
}

/*****************************************************************************
 Function   : APM_InitAPMGlobal
 Description: Init one memory control block
 Input      : VOS_MemCtrlBlock -- address of control block
            : ulBlockLength -- length
            : ulTotalBlockNumber -- number
            : ulAddress -- the start of address
 Return     : void
 Other      :
 *****************************************************************************/

VOS_VOID APM_InitAPMGlobal(VOS_VOID)
{
    VOS_UINT32  i;

    for(i=0; i<MODEM_ID_BUTT; i++)
    {
        g_aulShpaCurSysId[i] = VOS_RATMODE_BUTT;
    }

    /*lint -e534*/
    VOS_MemSet(g_astDspConfigCtrl, 0, sizeof(g_astDspConfigCtrl));

    VOS_MemSet(g_aulShpaActiveState, 0, sizeof(g_aulShpaActiveState));
    /*lint +e534*/

    return;
}


VOS_UINT32 DualModem_DDRQosUpdate(MODEM_ID_ENUM_UINT16 enModem, DUALMODEM_SCENE_TYPE_ENUM_UINT16 enSceneType,  VOS_UINT32 ulValue)
{
    VOS_INT                             lIntLevel;
    VOS_UINT32                          ulDDRFreqModem0 = 0;
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
    VOS_UINT32                          ulDDRFreqModem1 = 0;
#endif
    VOS_UINT32                          ulDrxFreqModem0 = 0;
    VOS_UINT32                          ulCcpuDDRFreq   = 0;

    lIntLevel = VOS_SplIMP();

    /*��¼��Ƶ�켣��ά�ɲ���Ϣ*/
    g_stHpaDDRDfsDebugInfo[g_ulHpaDDRDfsDebugTrack].enModem     = enModem;
    g_stHpaDDRDfsDebugInfo[g_ulHpaDDRDfsDebugTrack].enSceneType = enSceneType;
    g_stHpaDDRDfsDebugInfo[g_ulHpaDDRDfsDebugTrack].stDDRInfo.ulDDRValue    = ulValue;
    g_stHpaDDRDfsDebugInfo[g_ulHpaDDRDfsDebugTrack].stDDRInfo.ulSlice       = OM_GetSlice();
    g_ulHpaDDRDfsDebugTrack++;

    if (HPA_DDR_FREQ_TRACK_NUM == g_ulHpaDDRDfsDebugTrack)
    {
        g_ulHpaDDRDfsDebugTrack = 0;
    }

    if ((MODEM_ID_BUTT <= enModem) || (DUALMODEM_SCENCE_BUTT <= enSceneType))
    {
        VOS_Splx(lIntLevel);

        return VOS_ERR;
    }

    /*��¼��ģʽͶƱ��Ϣ*/
    g_stHpaDDRDfsInfo[enModem][enSceneType].ulDDRValue  = ulValue;
    g_stHpaDDRDfsInfo[enModem][enSceneType].ulSlice     = OM_GetSlice();

    /*�ռ�����Ƶ�ʣ���ǰֻ��עPHY/APS/GUDRX��ͶƱ������δ����ο�*/
    ulCcpuDDRFreq   = MAX(g_stHpaDDRDfsInfo[MODEM_ID_0][DUALMODEM_SCENCE_GSM].ulDDRValue, g_stHpaDDRDfsInfo[MODEM_ID_0][DUALMODEM_SCENCE_WCDMA].ulDDRValue);
    ulDrxFreqModem0 = MAX(ulCcpuDDRFreq, g_stHpaDDRDfsInfo[MODEM_ID_0][DUALMODEM_SCENCE_GUDRX].ulDDRValue);
    ulDDRFreqModem0 = MAX(ulDrxFreqModem0, g_stHpaDDRDfsInfo[MODEM_ID_0][DUALMODEM_SCENCE_APS].ulDDRValue);
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
    /*�ռ�����Ƶ�ʣ���ǰֻ��עPHY��GUDRX������δ����ο�*/
    ulDDRFreqModem1 = MAX(g_stHpaDDRDfsInfo[MODEM_ID_1][DUALMODEM_SCENCE_GSM].ulDDRValue, g_stHpaDDRDfsInfo[MODEM_ID_1][DUALMODEM_SCENCE_GUDRX].ulDDRValue);
    ulCcpuDDRFreq   = MAX(ulDDRFreqModem0, ulDDRFreqModem1);
#else
    ulCcpuDDRFreq   = ulDDRFreqModem0;
#endif

    VOS_Splx(lIntLevel);

#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
    /*�����������MODEM����Ҫ��Ƶ��������ʵֵ����ͶƱ*/
    if (ulDDRFreqModem0 == 0 || ulDDRFreqModem1 == 0)
    {
        (VOS_VOID)mdrv_pm_dfs_qos_update((VOS_INT32)DFS_QOS_ID_DDR_MINFREQ_E, g_lCcpuDDRFreqId, ulCcpuDDRFreq);
    }
    else    /*�������MODEM����DDR��Ƶ��������Ҫ���DDRƵ��һ��*/
    {
        /*�жϵ�ǰ�汾�Ƿ����DDR�ᵵ��Ƶ����*/
        if (VOS_TRUE == g_stDDRAdjustCFG.bEnable)
        {
            /* ����MIN FREQ��Ƶ���ԵĴ���Ҫ�󣬽�����DDRƵ�ʼ�1�󣬵������Ҫ��DDR���һ����λ���� */
            ulCcpuDDRFreq += 1;
        }

        (VOS_VOID)mdrv_pm_dfs_qos_update((VOS_INT32)DFS_QOS_ID_DDR_MINFREQ_E, g_lCcpuDDRFreqId, ulCcpuDDRFreq);
    }
#else
    (VOS_VOID)mdrv_pm_dfs_qos_update((VOS_INT32)DFS_QOS_ID_DDR_MINFREQ_E, g_lCcpuDDRFreqId, ulCcpuDDRFreq);
#endif

    return VOS_OK;
}

/*****************************************************************************
 Function   : APM_PIDInit
 Description: Init one memory control block
 Input      : VOS_MemCtrlBlock -- address of control block
            : ulBlockLength -- length
            : ulTotalBlockNumber -- number
            : ulAddress -- the start of address
 Return     : void
 Other      :
 *****************************************************************************/
VOS_UINT32 APM_PIDInit( enum VOS_INIT_PHASE_DEFINE ip )
{
    VOS_UINT32          i;

    switch ( ip )
    {
        case VOS_IP_INITIAL:
            APM_InitAPMGlobal();

#ifndef FEATURE_DSP2ARM
            HPA_Write32Reg(ZSP_SLEEP_TYPE_ADDR, ZSP_SLEEP_INIT | ZSP_SLEEP_NORMAL);
#endif

            for(i=0; i<MODEM_ID_BUTT; i++)
            {
                if ( VOS_OK != VOS_SmCCreate( "sem4", 0, VOS_SEMA4_FIFO,
                                            &g_aulShpaLoadPhySemaphor[i]) )
                {
                    PS_LOG(  UEPS_PID_SHPA, 0, PS_PRINT_WARNING, "APM_PIDInit: Create Semaphore<sem4> Error!!!");
                    return VOS_ERR;
                }

                if ( VOS_OK != VOS_SmCCreate( "sem5", 0, VOS_SEMA4_FIFO,
                                            &g_aulShpaActivePhySemaphor[i]) )
                {
                    PS_LOG(  UEPS_PID_SHPA, 0, PS_PRINT_WARNING, "APM_PIDInit: Create Semaphore<sem5> Error!!!");
                    return VOS_ERR;
                }
            }

            if ( VOS_OK != VOS_SmCCreate( "Ldf", 1, VOS_SEMA4_FIFO,
                                            &g_ulLdfSavingSemaphor) )
            {
                PS_LOG(  UEPS_PID_SHPA, 0, PS_PRINT_WARNING, "APM_PIDInit: Create Semaphore<Ldf> Error!!!");
                return VOS_ERR;
            }

            /*����CCPU DDR��Ƶͨ��*/
            (VOS_VOID)mdrv_pm_dfs_qos_get((VOS_INT32)DFS_QOS_ID_DDR_MINFREQ_E, 0, &g_lCcpuDDRFreqId);

            /* ��ȡDDR��Ƶ������Ϣ */
            if(NV_OK != NV_Read(en_NV_Item_DDR_ADJUST_CFG, &g_stDDRAdjustCFG, sizeof(NV_DDR_ADJUST_ENABLE_STRU)))
            {
                /*lint -e534*/
                LogPrint("APM_PIDInit: Read en_NV_Item_DDR_ADJUST_CFG Fail.\r\n");
                /*lint +e534*/
                return VOS_ERR;
            }

            break;

        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 Function   : HPA_ShowSystemAddr
 Description: Show memory Addr Inof
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID HPA_ShowSystemAddr(VOS_VOID)
{
    /*lint -e534*/
    vos_printf("\r\nThe AHBBaseAddr         is 0x%x",g_stSysAddr.ulAHBBaseAddr      );
    vos_printf("\r\nThe WBBPBaseAddr        is 0x%x",g_stSysAddr.ulWBBPBaseAddr     );
    vos_printf("\r\nThe WBBPDRXBaseAddr     is 0x%x",g_stSysAddr.ulWBBPDRXBaseAddr  );
    vos_printf("\r\nThe GBBPBaseAddr        is 0x%x",g_stSysAddr.ulGBBPBaseAddr     );
    vos_printf("\r\nThe GBBPDRXBaseAddr     is 0x%x",g_stSysAddr.ulGBBPDRXBaseAddr  );
    vos_printf("\r\nThe GBBP1BaseAddr       is 0x%x",g_stSysAddr.ulGBBP1BaseAddr    );
    vos_printf("\r\nThe GBBP1DRXBaseAddr    is 0x%x",g_stSysAddr.ulGBBP1DRXBaseAddr );
    vos_printf("\r\nThe SYSCTRLBaseAddr     is 0x%x",g_stSysAddr.ulSYSCTRLBaseAddr  );
    vos_printf("\r\nThe HIFIAXIBaseAddr     is 0x%x",g_stSysAddr.ulHIFIAXIBaseAddr  );
    vos_printf("\r\nThe DSPTempBaseAddr     is 0x%x",g_stSysAddr.ulDSPTempBaseAddr  );
    vos_printf("\r\nThe ulBBPCommBaseAddr   is 0x%x",g_stSysAddr.ulBBPCommBaseAddr  );
    vos_printf("\r\nThe ulBBPCommOnBaseAddr is 0x%x",g_stSysAddr.ulBBPCommOnBaseAddr);
    vos_printf("\r\nThe ulCDMABBPBaseAddr   is 0x%x",g_stSysAddr.ulCDMABBPBaseAddr  );
    vos_printf("\r\nThe ulCDMABBPDRXBaseAddris 0x%x",g_stSysAddr.ulCDMABBPDRXBaseAddr);
    /*lint +e534*/

    return ;
}


VOS_VOID HPA_ShowDDRFreqInfo(VOS_VOID)
{
    VOS_INT                             lIntLevel;

    lIntLevel = VOS_SplIMP();

    /*��ǰ��ģʽͶƱ���*/
    /*lint -e534*/
    vos_printf("\r\nThe GHPY0   DDR:     is %d Slice is %d",g_stHpaDDRDfsInfo[MODEM_ID_0][DUALMODEM_SCENCE_GSM].ulDDRValue, g_stHpaDDRDfsInfo[MODEM_ID_0][DUALMODEM_SCENCE_GSM].ulSlice);
    vos_printf("\r\nThe WPHY0   DDR:     is %d Slice is %d",g_stHpaDDRDfsInfo[MODEM_ID_0][DUALMODEM_SCENCE_WCDMA].ulDDRValue, g_stHpaDDRDfsInfo[MODEM_ID_0][DUALMODEM_SCENCE_WCDMA].ulSlice);
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
    vos_printf("\r\nThe GPHY1   DDR:     is %d Slice is %d",g_stHpaDDRDfsInfo[MODEM_ID_1][DUALMODEM_SCENCE_GSM].ulDDRValue, g_stHpaDDRDfsInfo[MODEM_ID_1][DUALMODEM_SCENCE_GSM].ulSlice);
#endif
    vos_printf("\r\nThe APS     DDR:     is %d Slice is %d",g_stHpaDDRDfsInfo[MODEM_ID_0][DUALMODEM_SCENCE_APS].ulDDRValue, g_stHpaDDRDfsInfo[MODEM_ID_0][DUALMODEM_SCENCE_APS].ulSlice);
    vos_printf("\r\nThe GUDRX   DDR:     is %d Slice is %d",g_stHpaDDRDfsInfo[MODEM_ID_0][DUALMODEM_SCENCE_GUDRX].ulDDRValue, g_stHpaDDRDfsInfo[MODEM_ID_0][DUALMODEM_SCENCE_GUDRX].ulSlice);
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
    vos_printf("\r\nThe GUDRX1  DDR:     is %d Slice is %d",g_stHpaDDRDfsInfo[MODEM_ID_1][DUALMODEM_SCENCE_GUDRX].ulDDRValue, g_stHpaDDRDfsInfo[MODEM_ID_1][DUALMODEM_SCENCE_GUDRX].ulSlice);
#endif
    vos_printf("\r\n========================================");
    /*lint +e534*/

    VOS_Splx(lIntLevel);

    return;
}
VOS_VOID HPA_ShowDDRFreqTrack(VOS_VOID)
{
    VOS_INT                             lIntLevel;
    VOS_UINT32                          i;

    lIntLevel = VOS_SplIMP();

    /*��ǰ��ģʽͶƱ���*/
    HPA_ShowDDRFreqInfo();

    for (i=0; i<HPA_DDR_FREQ_TRACK_NUM; i++)
    {
        /*lint -e534*/
        vos_printf("\r\nThe DDR Trace Log: Modem %d Type %d Freq %d Slice %d",g_stHpaDDRDfsDebugInfo[i].enModem, g_stHpaDDRDfsDebugInfo[i].enSceneType, g_stHpaDDRDfsDebugInfo[i].stDDRInfo.ulDDRValue, g_stHpaDDRDfsDebugInfo[i].stDDRInfo.ulSlice);
        /*lint +e534*/
    }

    VOS_Splx(lIntLevel);

    return;
}



#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



