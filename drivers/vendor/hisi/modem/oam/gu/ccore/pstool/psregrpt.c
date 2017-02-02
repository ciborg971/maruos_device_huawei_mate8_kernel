

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/******************************************************************************
   1 ͷ�ļ�����
******************************************************************************/

#include "stddef.h"
#include "pamom.h"
#include "apminterface.h"
#include "hpaglobalvar.h"
#include "omprivate.h"
#include "sleepflow.h"
#include "PsCommonDef.h"
#include "TtfOamInterface.h"
#include "psregrpt.h"
#include "apmprocess.h"
#include "soc_interface.h"
#include "msp_diag_comm.h"
#if (FEATURE_GUC_BBP_TRIG == FEATURE_ON)
#include "bbp_dbg_trig_interface.h"
#endif
/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/

/*lint -e767 �޸��ˣ�����47350�������ˣ�����51137��ԭ��������Ĵ����ϱ�����*/
#define    THIS_FILE_ID        PS_FILE_ID_PS_REG_RPT_C
/*lint +e767 �޸��ˣ�����47350�������ˣ�����51137��ԭ��������Ĵ����ϱ�����*/




/******************************************************************************
   2 �ⲿ�����ͱ�������
******************************************************************************/

/******************************************************************************
   3 ˽�ж���
******************************************************************************/

/******************************************************************************
   4 ȫ�ֱ�������
******************************************************************************/
PS_REG_RPT_CFG_STRU     g_astPsRegRptCfg[PS_REG_SYS_MODE_BUTT];

PS_REG_RPT_CFG_STRU     g_astPsRegRptTemp[PS_REG_SYS_MODE_BUTT];

PS_REG_REQ_ADDR_STRU    g_astPsRegReqAddr[PS_REG_SYS_MODE_BUTT];

PS_REG_RPT_VALUE_STRU   g_astPsRegRptBuf[PS_REG_RPT_RBUF_NUM];

PS_REG_RPT_IND_MSG      g_stPsRegRptINDMsg;

extern VOS_VOID SLEEP_DMACapRelease(VOS_VOID);

#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
extern VOS_VOID I1_SLEEP_DMACapRelease(VOS_VOID);
#if (3 == MULTI_MODEM_NUMBER)
extern VOS_VOID I2_SLEEP_DMACapRelease(VOS_VOID);
#endif
#endif

VOS_UINT32              g_aulRegCaptureNum[PS_REG_SYS_MODE_BUTT] = {0};

VOS_UINT32              g_aulRegFullNum[PS_REG_SYS_MODE_BUTT] = {0};

VOS_INT32               g_lDMAChanID0;
VOS_INT32               g_lDMAChanID1;
VOS_INT32               g_lDMAChanID2;

VOS_SEM                 g_ulRegTransferSem;

VOS_UINT32              g_ulRptRegInitStatus; /* ץ�Ĵ���ʹ��״̬ */
VOS_UINT32              g_ulRptRegDiffNum;    /* ץ�Ĵ��������ϱ����� */

DMAREG_INFO_STRU        g_stDmaInfo = {0};

DMA_REG_TIME_STRU       g_stDmaTimeInfo = {0};

VOS_UINT32             *g_pstDmaDest[PS_REG_RPT_BUF_NUM][PS_REG_RPT_SEND_FREQUENCY];

BALONG_DMA_CB_S        *g_pstDmaNode[PS_REG_RPT_BUF_NUM][PS_REG_RPT_SEND_FREQUENCY][PS_REG_SYS_MODE_BUTT];

VOS_UINT32              g_ulSendMoud        = PS_REG_RPT_SEND_FREQUENCY;
VOS_UINT32              g_ulSendCount       = 1;

VOS_BOOL                g_bIsOmGetSliceFlag = VOS_FALSE;

PS_REG_RPT_CONTROL_STRU g_PsRegRptContrl;


VOS_UINT32              g_ulChan0IsCapture = VOS_FALSE;
VOS_UINT32              g_ulChan1IsCapture = VOS_FALSE;
VOS_UINT32              g_ulChan2IsCapture = VOS_FALSE;

VOS_UINT32              g_ulPsRegErrCount   = 0;

#if (FEATURE_GUC_BBP_TRIG == FEATURE_ON)
PS_REG_BBPTRIG_CFG_INFO_STRU    g_stPsRegGUCBBPDbgState;

PS_REG_GUCBBP_TRIG_INFO_STRU    g_stPsRegGUCBBPTrigInfo;
#endif

/******************************************************************************
   5 ����ʵ��
******************************************************************************/


VOS_VOID PsRegDmaInfoShow(VOS_VOID)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    /*lint -e534*/
    vos_printf("\r\n DmaRegInfoShow:\r\n The Reg Capture Success Time is    %d", g_stDmaInfo.ulDmaSuccTime);
    vos_printf("\r\n The Dma ISR Success Time is        %d", g_stDmaInfo.ulDmaIsrSuccTime);
    vos_printf("\r\n The Dma ISR Time is                %d", g_stDmaInfo.ulDmaIsrTime);
    vos_printf("\r\n The Dma ISR Err Time is            %d", g_stDmaInfo.ulDmaIsrErrTime);
    vos_printf("\r\n The Dma Head Err Time is           %d", g_stDmaInfo.ulDmaHeadErrTime);
    vos_printf("\r\n The Dma Busy Time is               %d", g_stDmaInfo.ulDmaIdleErrTime);
    vos_printf("\r\n The Dma Start Err Time is          %d", g_stDmaInfo.ulDmaStartErrTime);
    vos_printf("\r\n The Dma Task Run Time is           %d", g_stDmaInfo.ulDmaTaskTime);
    vos_printf("\r\n The Last Dma Isr State is          %d", g_stDmaInfo.ulDmaIntState);
    vos_printf("\r\n The Max Data Isr Time is           %d", g_stDmaTimeInfo.ulIsrMaxTime);
    vos_printf("\r\n The Max Data Capture Time is       %d", g_stDmaTimeInfo.ulMaxTime);
    vos_printf("\r\n The Dma Start  Time is             %d", g_stDmaTimeInfo.ulDmaStartTime);
    vos_printf("\r\n The SmV Max  Time is               %d", g_stDmaTimeInfo.ulSmVMaxTime);
    vos_printf("\r\n The SmP Max  Time is               %d", g_stDmaTimeInfo.ulSmPMaxTime);
    vos_printf("\r\n The SmV To SmP Max Time is         %d", g_stDmaTimeInfo.ulSmVPTime);
    vos_printf("\r\n The Memcpy Max Time is             %d", g_stDmaTimeInfo.ulMemcpyMaxTime);
    vos_printf("\r\n The Socp Send Max Time is          %d", g_stDmaTimeInfo.ulSocpMaxTime);

    vos_printf("\r\n The Dma dest Idle Err Time is       %d", g_stDmaInfo.ulDmaDestIdleErrTime);
    vos_printf("\r\n The Dma dest Busy Err Time is       %d", g_stDmaInfo.ulDmaDestBusyErrTime);
    vos_printf("\r\n The Mem Dma Isr Time is            %d", g_stDmaInfo.ulMemDmaIsrTime);
    vos_printf("\r\n The Mem Dma Start Time is          %d", g_stDmaInfo.ulMemDmaStartTime);
    vos_printf("\r\n The Modem Error Time is          %d", g_stDmaInfo.ulModemErrTime);

    vos_printf("\r\n The Modem Call Diag Api Before     %d", g_stDmaInfo.ulDiagTransReportBeforTime);
    vos_printf("\r\n The Modem Call Diag Api After      %d", g_stDmaInfo.ulDiagTransReportAfterTime);

    vos_printf("\r\ng_PsRegRptContrl.bRptEnableStatus:%d", g_PsRegRptContrl.bRptEnableStatus);
    vos_printf("\r\ng_PsRegRptContrl.aulSendCount[0]WCDMA:%d", g_PsRegRptContrl.aulSendCount[0]);
    vos_printf("\r\ng_PsRegRptContrl.aulSendCount[1]GSM:%d", g_PsRegRptContrl.aulSendCount[1]);
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
    vos_printf("\r\ng_PsRegRptContrl.aulSendCount[2]GSM1:%d", g_PsRegRptContrl.aulSendCount[2]);

#if (3 == MULTI_MODEM_NUMBER)
    vos_printf("\r\ng_PsRegRptContrl.aulSendCount[3]GSM2:%d", g_PsRegRptContrl.aulSendCount[3]);
#endif

#endif
    vos_printf("\r\ng_PsRegRptContrl.ulSendBufIndex[2]:%d", g_PsRegRptContrl.ulSendBufIndex);

    for (i=0;i<PS_REG_RPT_BUF_NUM;i++)
    {
         for (j=0;j<PS_REG_RPT_SEND_FREQUENCY;j++)
         {

            vos_printf("\r\n g_PsRegRptContrl.aulDmaDestWriteStatus is:%d sysmode is:%d",
                        g_PsRegRptContrl.aulDmaDestWriteStatus[i][j],
                        g_PsRegRptContrl.aulDmaDestWriteSysMode[i][j]);
         }
    }

    vos_printf("\r\ng_PsRegRptContrl.aulDmaDestWriteIndex:%d", g_PsRegRptContrl.ulDmaDestWriteIndex);

    for (i=0; i<PS_REG_SYS_MODE_BUTT; i++)
    {
        vos_printf("\r\n g_astPsRegReqAddr[%d].ulCnt = %d", i, g_astPsRegReqAddr[i].ulCnt);
    }
    /*lint +e534*/

    return ;
}


VOS_UINT32 PsRegGetSlice(VOS_VOID)
{
    if(VOS_TRUE == g_bIsOmGetSliceFlag)
    {
        return OM_GetSlice();
    }

    return VOS_OK;
}


VOS_VOID PsRegSendDataSetHead(PS_REG_RPT_IND_CONTENT_HEAD *pstRegRptIndContHead, VOS_UINT32 ulSysMode)
{
    /*���ݲ�ͬģʽ��䷢�ͺͽ���PID*/
    if (PS_REG_SYS_MODE_WCDMA == ulSysMode)
    {
        pstRegRptIndContHead->usModemId     = MODEM_ID_0;
        pstRegRptIndContHead->enRatMode     = PS_REG_RAT_WCDMA;
        pstRegRptIndContHead->usMsgName     = ID_OM_APP_W_REG_IND;


    }
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
    else if (PS_REG_SYS_MODE_GSM1 == ulSysMode)
    {
        pstRegRptIndContHead->usModemId     = MODEM_ID_1;
        pstRegRptIndContHead->enRatMode     = PS_REG_RAT_GSM;
        pstRegRptIndContHead->usMsgName     = ID_OM_APP_G_REG_IND;
    }
#if (3 == MULTI_MODEM_NUMBER)
    else if (PS_REG_SYS_MODE_GSM2 == ulSysMode)
    {
        pstRegRptIndContHead->usModemId     = MODEM_ID_2;
        pstRegRptIndContHead->enRatMode     = PS_REG_RAT_GSM;
        pstRegRptIndContHead->usMsgName     = ID_OM_APP_G_REG_IND;
    }
#endif

#endif
    else
    {
        pstRegRptIndContHead->usModemId     = MODEM_ID_0;
        pstRegRptIndContHead->enRatMode     = PS_REG_RAT_GSM;
        pstRegRptIndContHead->usMsgName     = ID_OM_APP_G_REG_IND;
    }

}
VOS_VOID PsRegPackageSendData(VOS_UINT32 *pulTotalOffset, VOS_UINT32 ulSendBufIndex)
{
    PS_REG_RPT_IND_CONTENT_HEAD        *pstRegRptIndContHead;
    VOS_UINT32                         *pulBitMap;
    VOS_UINT32                         *pstRegRptTemp;
    VOS_UINT32                         *pstPsRegRptValue;
    VOS_UINT32                          ulSendFrequencyLoop; /* �ϱ�֡Ƶ */
    VOS_UINT32                          ulRegRptCntLoop;
    VOS_UINT32                          ulSysMode;
    VOS_UINT32                          ulOffset      = 0;
    VOS_UINT32                          ulBitMapCount = 0;
    VOS_UINT32                          ulBitMapIndex;
    VOS_UINT32                          ulBitShift;
    VOS_UINT32                          ulRegValue;
    VOS_UINT32                          ulRealRptCnt  = 0;
    VOS_INT                             lLockLevel;

    /* ������ϱ�֡ */
    for (ulSendFrequencyLoop=0; ulSendFrequencyLoop<PS_REG_RPT_SEND_FREQUENCY; ulSendFrequencyLoop++)
    {
        if (VOS_TRUE != g_PsRegRptContrl.aulDmaDestWriteStatus[ulSendBufIndex][ulSendFrequencyLoop])
        {
            g_stDmaInfo.ulDmaDestBusyErrTime++;
            continue;
        }

        ulSysMode = PsRegSysModeGet(ulSendBufIndex, ulSendFrequencyLoop);

        /* ȡ��EDMA�������� */
        /*lint -e534*/
        mdrv_memcpy(g_astPsRegRptTemp[ulSysMode].aulRegValue,
                    g_pstDmaDest[ulSendBufIndex][ulSendFrequencyLoop],
                    PsRegNumberGet(ulSysMode) * sizeof(VOS_UINT32));
        /*lint +e534*/

        lLockLevel = VOS_SplIMP();
        g_PsRegRptContrl.aulDmaDestWriteStatus[ulSendBufIndex][ulSendFrequencyLoop] = VOS_FALSE;

        VOS_Splx(lLockLevel);

        /* �ϱ��Ĵ��������ַ */
        pstRegRptTemp = g_astPsRegRptTemp[ulSysMode].aulRegValue;

        /* ƴ��������ʼ��ַ */
        pstRegRptIndContHead = (PS_REG_RPT_IND_CONTENT_HEAD*)(g_stPsRegRptINDMsg.aucValue + ulOffset);

        ulOffset += sizeof(PS_REG_RPT_IND_CONTENT_HEAD);

        /* ����BIT MAP���� */
        ulBitMapCount = (g_astPsRegRptCfg[ulSysMode].ulCnt + 31) / 32;

        /* BitMap��ʼλ�� */
        pulBitMap = (VOS_UINT32*)(g_stPsRegRptINDMsg.aucValue + ulOffset);

        ulOffset += ulBitMapCount * sizeof(VOS_UINT32);

        /* �ϱ��Ĵ���ֵ��ʼλ�� */
        pstPsRegRptValue = (VOS_UINT32*)(g_stPsRegRptINDMsg.aucValue + ulOffset);

        /* ���BITMAP */
        /*lint -e534*/
        VOS_MemSet(pulBitMap, 0, ulBitMapCount * sizeof(VOS_UINT32));
        /*lint +e534*/

        /* �Ĵ��������ϱ�����һ��ʱ���ϱ�һ֡ȫ���� */
        if (0 == (g_PsRegRptContrl.aulSendCount[ulSysMode] % g_ulRptRegDiffNum))
        {
            /* ��ȫ�ϱ�:λͼȫ����1 */
            for (ulRegRptCntLoop = 0; ulRegRptCntLoop < PsRegNumberGet(ulSysMode); ulRegRptCntLoop++)
            {
                ulBitMapIndex             = PS_REG_RPT_GET_BITMAP_NUM(ulRegRptCntLoop);
                ulBitShift                = ulRegRptCntLoop & 0x1f;
                pulBitMap[ulBitMapIndex] |= ( 1U << ulBitShift ) ;
            }

            /* ���������ͻ��� */
            /*lint -e534*/
            mdrv_memcpy(pstPsRegRptValue,
                          pstRegRptTemp,
                          PsRegNumberGet(ulSysMode) * sizeof(VOS_UINT32));

            /* �������Ƚϻ��� */
            mdrv_memcpy(g_astPsRegRptCfg[ulSysMode].aulRegValue,
                        pstRegRptTemp,
                        PsRegNumberGet(ulSysMode) * sizeof(VOS_UINT32));
            /*lint +e534*/

            ulOffset += PsRegNumberGet(ulSysMode) * sizeof(VOS_UINT32);

            g_PsRegRptContrl.aulSendCount[ulSysMode] = 1;

            ulRealRptCnt = PsRegNumberGet(ulSysMode);
        }
        else
        {
            /* �����ϱ� */
            ulRealRptCnt = 0;

            for (ulRegRptCntLoop = 0; ulRegRptCntLoop < PsRegNumberGet(ulSysMode); ulRegRptCntLoop++)
            {
                ulBitMapIndex       = PS_REG_RPT_GET_BITMAP_NUM(ulRegRptCntLoop);
                ulBitShift          = ulRegRptCntLoop & 0x1f;
                ulRegValue          = *(pstRegRptTemp + ulRegRptCntLoop);

                /* ������䶯�Ĵ�����ͬʱ�ѱ䶯λ������λͼ�� */
                if ( g_astPsRegRptCfg[ulSysMode].aulRegValue[ulRegRptCntLoop] != ulRegValue )
                {
                    pstPsRegRptValue[ulRealRptCnt]                           = ulRegValue;
                    g_astPsRegRptCfg[ulSysMode].aulRegValue[ulRegRptCntLoop] = ulRegValue;
                    pulBitMap[ulBitMapIndex]                                |= ( 1U << ulBitShift ) ;
                    ulRealRptCnt++;
                }
            }

            g_PsRegRptContrl.aulSendCount[ulSysMode]++;

            ulOffset += ulRealRptCnt * sizeof(VOS_UINT32);
        }

        pstRegRptIndContHead->usCnt     = (VOS_UINT16)PsRegNumberGet(ulSysMode);
        pstRegRptIndContHead->ulLength  = ulBitMapCount * sizeof(VOS_UINT32) + ulRealRptCnt * sizeof(VOS_UINT32);

        /* ������Ϣͷ */
        PsRegSendDataSetHead(pstRegRptIndContHead, ulSysMode);

    }

    *pulTotalOffset += ulOffset;

    return ;
}

VOS_VOID PsRegTransferTaskEntry(VOS_VOID)
{
    VOS_UINT32                          ulTotalOffset = 0;
    VOS_UINT32                          ulSendBufIndex;
    VOS_UINT32                          ulTime;
    VOS_UINT32                          ulStartTime;
    VOS_UINT32                          ulEndTime;
    VOS_INT                             lLockLevel;
    DIAG_TRANS_IND_STRU                 stDiagTransMsg;

#if (VOS_OS_VER == VOS_WIN32)
    VOS_UINT32                          i;
    for(i=0;i<1;i++)
#else
    for(;;)
#endif
    {
        ulStartTime = PsRegGetSlice();
        if (VOS_OK != VOS_SmP(g_ulRegTransferSem, 0))
        {
            /*lint -e534*/
            LogPrint("PsRegTransferTaskEntry: VOS_SmP Fail.\r\n");
            /*lint +e534*/
            continue;
        }

        ulEndTime = PsRegGetSlice();
        ulTime = ulEndTime - ulStartTime;
        if (ulTime > g_stDmaTimeInfo.ulSmPMaxTime)
        {
            g_stDmaTimeInfo.ulSmPMaxTime = ulTime;
        }

        ulTime = ulEndTime - g_stDmaTimeInfo.ulSmVTime;
        if (ulTime > g_stDmaTimeInfo.ulSmVPTime)
        {
            g_stDmaTimeInfo.ulSmVPTime = ulTime;
        }

        g_stDmaInfo.ulDmaTaskTime++;

        lLockLevel = VOS_SplIMP();
        /* ƹ��д����л� */
        ulSendBufIndex = g_PsRegRptContrl.ulSendBufIndex;
        g_PsRegRptContrl.ulDmaDestWriteIndex = 0;

        if (0 == g_PsRegRptContrl.ulSendBufIndex)
        {
            g_PsRegRptContrl.ulSendBufIndex      = 1;
        }
        else
        {
            g_PsRegRptContrl.ulSendBufIndex      = 0;
        }
        VOS_Splx(lLockLevel);

        ulStartTime = PsRegGetSlice();

        /* �������ݰ�ͷ���� */
        ulTotalOffset = 0;

        /* ����������� */
        PsRegPackageSendData(&ulTotalOffset, ulSendBufIndex);

        ulEndTime = PsRegGetSlice();
        ulTime = ulEndTime - ulStartTime;
        if (ulTime > g_stDmaTimeInfo.ulMemcpyMaxTime)
        {
            g_stDmaTimeInfo.ulMemcpyMaxTime = ulTime;
        }

        /* ��Ϣ���� */
        ulStartTime = PsRegGetSlice();

        stDiagTransMsg.ulModule = DIAG_GEN_MODULE_EX(DIAG_MODEM_0, DIAG_MODE_COMM, DIAG_MSG_TYPE_BBP);
        stDiagTransMsg.ulPid    = WUEPS_PID_REG;
        stDiagTransMsg.ulMsgId  = ID_OM_APP_REG_IND;
        stDiagTransMsg.ulLength = ulTotalOffset;
        stDiagTransMsg.pData    = (VOS_VOID *)&g_stPsRegRptINDMsg;

        g_stDmaInfo.ulDiagTransReportBeforTime++;

        /*lint -e534*/
        (VOS_VOID)DIAG_TransReport_Ex(&stDiagTransMsg);
        /*lint +e534*/

        g_stDmaInfo.ulDiagTransReportAfterTime++;

        ulEndTime = PsRegGetSlice();
        ulTime = ulEndTime - ulStartTime;
        if (ulTime > g_stDmaTimeInfo.ulSocpMaxTime)
        {
            g_stDmaTimeInfo.ulSocpMaxTime = ulTime;
        }

        ulTime = ulEndTime - g_stDmaTimeInfo.ulStartSlice;
        if (ulTime > g_stDmaTimeInfo.ulMaxTime)
        {
            g_stDmaTimeInfo.ulMaxTime = ulTime;
        }

    }
}


VOS_VOID PsRegDmaIsr(VOS_UINT32 ulChannelarg, VOS_UINT32 ulIntState)
{
    VOS_UINT32              ulStartTime;

    g_stDmaInfo.ulDmaIsrTime++;
    g_stDmaInfo.ulDmaIntState = ulIntState;

    if (EDMA_BBP_GRIF == ulChannelarg)
    {
        g_ulChan0IsCapture  = VOS_FALSE;
        SLEEP_DMACapRelease();
    }
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
    else if (EDMA_BBP_DBG == ulChannelarg)
    {
        g_ulChan1IsCapture  = VOS_FALSE;
        I1_SLEEP_DMACapRelease();
    }

#if (3 == MULTI_MODEM_NUMBER)
    else if (EDMA_MEMORY_DSP_6 == ulChannelarg)
    {
        g_ulChan2IsCapture  = VOS_FALSE;
        I2_SLEEP_DMACapRelease();
    }
#endif

#endif
    else
    {
        g_stDmaInfo.ulChan1ArgErrTime++;
    }

    if (BALONG_DMA_INT_DONE == ulIntState)
    {
        ulStartTime = PsRegGetSlice() - g_stDmaTimeInfo.ulStartSlice;

        if (ulStartTime > g_stDmaTimeInfo.ulIsrMaxTime)
        {
            g_stDmaTimeInfo.ulIsrMaxTime = ulStartTime;
        }

        if (g_ulSendCount >= g_ulSendMoud)
        {
            /*lint -e534*/
            VOS_SmV(g_ulRegTransferSem);
            /*lint +e534*/
            g_ulSendCount = 1;
        }
        else
        {
            g_ulSendCount++;
        }

        /*lint -e534*/
        /* VOS_SmV(g_ulRegTransferSem);*/
        /*lint +e534*/

        g_stDmaTimeInfo.ulSmVTime = PsRegGetSlice();
        g_stDmaInfo.ulDmaIsrSuccTime++;

    }
    else
    {
        g_stDmaInfo.ulDmaIsrErrTime++;
    }

    return;
}
VOS_VOID PsRegDmaGetFirstNode(BALONG_DMA_CB_S *psttemp, BALONG_DMA_CB_S *pstDmaNode)
{
    /* g_pstDmaDestTemp = pstDmaNode->des_addr;*/
    /*�õ�һ���ڵ����ͨ����������ƿ���ʼ��ַ*/
    psttemp->lli        = pstDmaNode->lli;
    psttemp->config     = pstDmaNode->config & 0xFFFFFFFE;
    psttemp->src_addr   = pstDmaNode->src_addr;  /*�����ַ*/
    psttemp->des_addr   = pstDmaNode->des_addr;  /*�����ַ*/
    psttemp->cnt0       = pstDmaNode->cnt0;
    psttemp->bindx      = 0;
    psttemp->cindx      = 0;
    psttemp->cnt1       = 0;

/* mask */
/*
    ulRegVal = *(volatile VOS_UINT32 *)0xFF032058;
    ulRegVal &= 0x7FFF;
    *(volatile VOS_UINT32 *)0xFF032058 = ulRegVal;
*/

}


VOS_UINT32 PsRegDmaSetDmaNode(BALONG_DMA_CB_S *psttemp, VOS_UINT32 ulSysMode)
{
    VOS_UINT32                          ulRest = VOS_OK;
    VOS_INT                             lLockLevel;

    switch(g_PsRegRptContrl.ulDmaDestWriteIndex)
    {
        case 0: /* ��һ֡ */
            if (VOS_FALSE != g_PsRegRptContrl.aulDmaDestWriteStatus[g_PsRegRptContrl.ulSendBufIndex][0])
            {
                /* ���� */
                g_stDmaInfo.ulDmaDestIdleErrTime++;
                ulRest = VOS_ERR;
                break;
            }

            /* EDMA������ƿ���ʼ��ַ */
            PsRegDmaGetFirstNode(psttemp, g_pstDmaNode[g_PsRegRptContrl.ulSendBufIndex][0][ulSysMode]);

            lLockLevel = VOS_SplIMP();
            g_PsRegRptContrl.aulDmaDestWriteSysMode[g_PsRegRptContrl.ulSendBufIndex][0] = ulSysMode;
            g_PsRegRptContrl.aulDmaDestWriteStatus[g_PsRegRptContrl.ulSendBufIndex][0] = VOS_TRUE;
            g_PsRegRptContrl.ulDmaDestWriteIndex++;
            VOS_Splx(lLockLevel);

            break;

        case 1:/* �ڶ�֡ */
            if (VOS_FALSE != g_PsRegRptContrl.aulDmaDestWriteStatus[g_PsRegRptContrl.ulSendBufIndex][1])
            {
                /* ���� */
                g_stDmaInfo.ulDmaDestIdleErrTime++;
                ulRest = VOS_ERR;
                break;
            }

            /* EDMA������ƿ���ʼ��ַ */
            PsRegDmaGetFirstNode(psttemp, g_pstDmaNode[g_PsRegRptContrl.ulSendBufIndex][1][ulSysMode]);

            lLockLevel = VOS_SplIMP();
            g_PsRegRptContrl.aulDmaDestWriteSysMode[g_PsRegRptContrl.ulSendBufIndex][1] = ulSysMode;
            g_PsRegRptContrl.aulDmaDestWriteStatus[g_PsRegRptContrl.ulSendBufIndex][1] = VOS_TRUE;
            g_PsRegRptContrl.ulDmaDestWriteIndex++;
            VOS_Splx(lLockLevel);
            break;

        default:/* ����֡ */
            /* EDMA������ƿ���ʼ��ַ */
            if (VOS_FALSE != g_PsRegRptContrl.aulDmaDestWriteStatus[g_PsRegRptContrl.ulSendBufIndex][2])
            {
                /* ���� */
                g_stDmaInfo.ulDmaDestIdleErrTime++;
                ulRest = VOS_ERR;
                break;
            }

            /* EDMA������ƿ���ʼ��ַ */
            PsRegDmaGetFirstNode(psttemp, g_pstDmaNode[g_PsRegRptContrl.ulSendBufIndex][2][ulSysMode]);
            lLockLevel = VOS_SplIMP();
            g_PsRegRptContrl.aulDmaDestWriteSysMode[g_PsRegRptContrl.ulSendBufIndex][2] = ulSysMode;
            g_PsRegRptContrl.aulDmaDestWriteStatus[g_PsRegRptContrl.ulSendBufIndex][2] = VOS_TRUE;
            g_PsRegRptContrl.ulDmaDestWriteIndex = 0;
            VOS_Splx(lLockLevel);
            break;
    }

    return ulRest;

}


VOS_UINT32 PsRegGetDmaCaptureStatus(MODEM_ID_ENUM_UINT16 enModemId)
{
    if (MODEM_ID_0 == enModemId)
    {
        return g_ulChan0IsCapture;
    }
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
    else if (MODEM_ID_1 == enModemId)
    {
        return g_ulChan1IsCapture;
    }

#if (3 == MULTI_MODEM_NUMBER)
    else if (MODEM_ID_2 == enModemId)
    {
        return g_ulChan2IsCapture;
    }
#endif

#endif
    else
    {
        return VOS_FALSE;
    }
}


VOS_VOID PsRegSetDmaCaptureBusy(VOS_INT32 lDMAChanID)
{
    /* ��ֹBBP�µ� */
    if (g_lDMAChanID0 == lDMAChanID)
    {
        g_ulChan0IsCapture  = VOS_TRUE;
    }
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
#if (3 == MULTI_MODEM_NUMBER)
    else if (g_lDMAChanID2 == lDMAChanID)
    {
        g_ulChan2IsCapture  = VOS_TRUE;
    }
#endif
    else
    {
        g_ulChan1IsCapture  = VOS_TRUE;
    }
#endif

    return;
}
VOS_VOID PsRegSetDmaCaptureIdle(VOS_INT32 lDMAChanID)
{
    if (g_lDMAChanID0 == lDMAChanID)
    {
        g_ulChan0IsCapture  = VOS_FALSE;

        SLEEP_DMACapRelease();
    }
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )

#if (3 == MULTI_MODEM_NUMBER)
    if (g_lDMAChanID2 == lDMAChanID)
    {
        g_ulChan2IsCapture  = VOS_FALSE;

        I2_SLEEP_DMACapRelease();
    }

#endif
    else
    {
        g_ulChan1IsCapture  = VOS_FALSE;

        I1_SLEEP_DMACapRelease();
    }
#endif

    return;
}


VOS_VOID PsRegDmaCapture(VOS_UINT32 ulSysMode)
{
    BALONG_DMA_CB_S                    *psttemp;
    VOS_INT32                           lDMAChanID;
    VOS_UINT32                          ulRest;

    if ((PS_REG_SYS_MODE_GSM == ulSysMode)||(PS_REG_SYS_MODE_WCDMA== ulSysMode))
    {
        lDMAChanID = g_lDMAChanID0;
        g_PsRegRptContrl.bEdma0StartStatus = VOS_TRUE;
    }
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
    else if(PS_REG_SYS_MODE_GSM1 == ulSysMode)
    {
        lDMAChanID = g_lDMAChanID1;
        g_PsRegRptContrl.bEdma1StartStatus = VOS_TRUE;
    }
#if (3 == MULTI_MODEM_NUMBER)
    else if(PS_REG_SYS_MODE_GSM2 == ulSysMode)
    {
        lDMAChanID = g_lDMAChanID2;
        g_PsRegRptContrl.bEdma2StartStatus = VOS_TRUE;
    }
#endif
#endif
    else
    {
        g_stDmaInfo.ulModemErrTime++;
        return;
    }

    if (VOS_TRUE != mdrv_edma_chan_is_idle((VOS_UINT32)lDMAChanID))
    {
        g_stDmaInfo.ulDmaIdleErrTime++;
        return;
    }

    /* ��ȡͨ����������ƿ���ʼ��ַ */
    psttemp = mdrv_edma_chan_get_lli_addr((VOS_UINT32)lDMAChanID);

    if (VOS_NULL_PTR == psttemp)
    {
        g_stDmaInfo.ulDmaHeadErrTime++;
        return;
    }

    ulRest = PsRegDmaSetDmaNode(psttemp, ulSysMode);
    if (VOS_OK != ulRest)
    {
        return;
    }

    /* ��DMAͨ��״̬Ϊæ */
    PsRegSetDmaCaptureBusy(lDMAChanID);
    if (mdrv_edma_chan_lli_async_start((VOS_UINT32)lDMAChanID))
    {
        /* ��DMAͨ��״̬Ϊ�� */
        PsRegSetDmaCaptureIdle(lDMAChanID);
        g_stDmaInfo.ulDmaStartErrTime++;
        return ;
    }

    /* ����EDMA���˼Ĵ���ֵ��ȷ�� */
#if 0
    /*��ȡ�Ĵ���*/
    for (ulRest = 0; ulRest < g_astPsRegReqAddr[ulSysMode].ulCnt; ulRest++)
    {
        g_astPsRegRptCfgTemp[ulSysMode].aulRegValue[ulRest] = *((volatile VOS_UINT32*)(g_astPsRegReqAddr[ulSysMode].aulRegAddr[ulRest]));
    }
    g_astPsRegRptCfgTemp[ulSysMode].ulCnt = g_astPsRegReqAddr[ulSysMode].ulCnt;
#endif

    g_stDmaInfo.ulDmaSuccTime++;

    return ;
}
VOS_UINT32 PsRegDmaNodeInit(APP_OM_REG_START_MODE_STRU *pRcvMsg)
{
    BALONG_DMA_CB_S                    *psttemp;
    VOS_UINT32                         *pStDmaDest;
    BALONG_DMA_REQ_E                    enDmaID = EDMA_BBP_GRIF;
    VOS_UINT32                          ulBufNumLoop;        /* Buff���� */
    VOS_UINT32                          ulSendFrequencyLoop; /* �ϱ�֡Ƶ */
    VOS_UINT32                          ulDmaNodeCount;
    VOS_UINT32                          i;

    if ((PS_REG_SYS_MODE_GSM == pRcvMsg->enSysMode)||(PS_REG_SYS_MODE_WCDMA == pRcvMsg->enSysMode))
    {
        enDmaID = EDMA_BBP_GRIF;
    }
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )

#if (3 == MULTI_MODEM_NUMBER)
    else if (PS_REG_SYS_MODE_GSM2 == pRcvMsg->enSysMode)
    {
        enDmaID = EDMA_MEMORY_DSP_6;
    }
#endif
    else
    {
        enDmaID = EDMA_BBP_DBG;
    }
#endif

    for (ulBufNumLoop=0; ulBufNumLoop<PS_REG_RPT_BUF_NUM; ulBufNumLoop++)
    {
        for (ulSendFrequencyLoop = 0; ulSendFrequencyLoop < PS_REG_RPT_SEND_FREQUENCY; ulSendFrequencyLoop++)
        {
            /* �Ĵ���Ŀ����ʼ��ַ */
            pStDmaDest = g_pstDmaDest[ulBufNumLoop][ulSendFrequencyLoop];

            /*�������ڵ�*/
            psttemp   = g_pstDmaNode[ulBufNumLoop][ulSendFrequencyLoop][pRcvMsg->enSysMode];

            ulDmaNodeCount = 1;

            for (i = 0; i < pRcvMsg->ulRegNum; i++)
            {
                /* ����ͷβ���� */
                if ((0 == i)||(i == pRcvMsg->ulRegNum -1))
                {
                    psttemp->lli        = mdrv_edma_set_lli((VOS_UINT32)g_pstDmaNode[ulBufNumLoop][ulSendFrequencyLoop][pRcvMsg->enSysMode] + ulDmaNodeCount * sizeof(BALONG_DMA_CB_S), ((i < pRcvMsg->ulRegNum - 1)?0:1));
                    psttemp->config     = mdrv_edma_set_config(enDmaID, BALONG_DMA_M2M, EDMA_TRANS_WIDTH_32, EDMA_BUR_LEN_16);
                    psttemp->src_addr   = pRcvMsg->aulRegAddr[i];            /* Դ�����ַ */
                    psttemp->des_addr   = (VOS_UINT32)(pStDmaDest + i);      /* Ŀ�������ַ */
                    psttemp->cnt0       = sizeof(VOS_UINT32);
                    psttemp->bindx      = 0;
                    psttemp->cindx      = 0;
                    psttemp->cnt1       = 0;

                    psttemp++;
                    ulDmaNodeCount++;
                    continue;
                }

                /* �����ַ���� */
                if (pRcvMsg->aulRegAddr[i-1] + sizeof(VOS_UINT32) == pRcvMsg->aulRegAddr[i])
                {
                    (psttemp-1)->cnt0       += sizeof(VOS_UINT32);
                }
                else
                {
                    psttemp->lli        = mdrv_edma_set_lli((VOS_UINT32)g_pstDmaNode[ulBufNumLoop][ulSendFrequencyLoop][pRcvMsg->enSysMode] + ulDmaNodeCount * sizeof(BALONG_DMA_CB_S), ((i < pRcvMsg->ulRegNum - 1)?0:1));
                    psttemp->config     = mdrv_edma_set_config(enDmaID, BALONG_DMA_M2M, EDMA_TRANS_WIDTH_32, EDMA_BUR_LEN_16);
                    psttemp->src_addr   = pRcvMsg->aulRegAddr[i];               /* Դ�����ַ */
                    psttemp->des_addr   = (VOS_UINT32)(pStDmaDest + i);         /* Ŀ�������ַ */
                    psttemp->cnt0       = sizeof(VOS_UINT32);
                    psttemp->bindx      = 0;
                    psttemp->cindx      = 0;
                    psttemp->cnt1       = 0;

                    psttemp++;
                    ulDmaNodeCount++;
                }
            }
        }
    }

    return VOS_OK;
}


VOS_UINT32 PsRegDmaUnCacheMemAlloc(VOS_VOID)
{
    VOS_UINT_PTR                        ulAddr;
    VOS_UINT32                          ulBufNumLoop;        /* Buff���� */
    VOS_UINT32                          ulSysModeLoop;       /* Sys Mode���� */
    VOS_UINT32                          ulSendFrequencyLoop; /* �ϱ�֡Ƶ */

    /* [PS_REG_RPT_BUF_NUM][PS_REG_RPT_SEND_FREQUENCY][PS_REG_SYS_MODE_BUTT] */
    /* Buff���� */
    for (ulBufNumLoop=0; ulBufNumLoop<PS_REG_RPT_BUF_NUM; ulBufNumLoop++)
    {
        /* �ϱ�֡Ƶ */
        for (ulSendFrequencyLoop=0; ulSendFrequencyLoop<PS_REG_RPT_SEND_FREQUENCY; ulSendFrequencyLoop++)
        {
            /* DMA Ŀ�Ŀռ� */
            g_pstDmaDest[ulBufNumLoop][ulSendFrequencyLoop] = (VOS_UINT32 *)VOS_UnCacheMemAlloc(PS_REG_RPT_DMA_DEST_BUFFER + 0x100, &ulAddr);

            if (VOS_NULL_PTR == g_pstDmaDest[ulBufNumLoop][ulSendFrequencyLoop])
            {
                /*lint -e534*/
                vos_printf("\r\nPsRegDmaInit: fail to malloc memory for g_pstDmaDest[%d][%d]!\r\n",
                            ulBufNumLoop, ulSendFrequencyLoop);
                /*lint +e534*/
                return VOS_ERR;
            }

            /* Sys Mode���� */
            for (ulSysModeLoop=0; ulSysModeLoop<PS_REG_SYS_MODE_BUTT; ulSysModeLoop++)
            {
                /* DMA���˽ڵ�ռ� */
                g_pstDmaNode[ulBufNumLoop][ulSendFrequencyLoop][ulSysModeLoop] = (BALONG_DMA_CB_S *)VOS_UnCacheMemAlloc(PS_REG_RPT_MAX_NUM * sizeof(BALONG_DMA_CB_S), &ulAddr);

                if (VOS_NULL_PTR == g_pstDmaNode[ulBufNumLoop][ulSendFrequencyLoop][ulSysModeLoop])
                {
                    /*lint -e534*/
                    vos_printf("\r\nPsRegDmaNodeInit: malloc memory fail at g_pstDmaNode[%d][%d][%d]!\r\n",
                                ulBufNumLoop, ulSendFrequencyLoop, ulSysModeLoop);
                    /*lint +e534*/
                    return VOS_ERR;
                }
            }
        }
    }

    return VOS_OK;
  }
VOS_UINT32 PsRegDmaInit(VOS_VOID)
{
    /* Dma �����ڴ����� */
    if(VOS_OK != PsRegDmaUnCacheMemAlloc())
    {
        /*lint -e534*/
        vos_printf("\r\nPsRegDmaInit: alloc memery fail !\r\n");
        /*lint +e534*/
        return VOS_ERR;
    }

    /* ��ʼ��ͨ�� REGDMA_CHANNEL_REQ */
    g_lDMAChanID0 = mdrv_edma_chan_init(EDMA_BBP_GRIF, (channel_isr)PsRegDmaIsr,
                                          EDMA_BBP_GRIF, (BALONG_DMA_INT_DONE | BALONG_DMA_INT_TRANSFER_ERR));
    if (g_lDMAChanID0 < 0)
    {
        /*lint -e534*/
        vos_printf("\r\nPsRegDmaInit: fail to init edma0 channel, phy channel is 0x%x\r\n", g_lDMAChanID0);
        /*lint +e534*/
        return VOS_ERR;
    }

/* ��ǰAustin��GRIF��DEGͨ�����ܸ��ã�������ǰ�Ĵ��������ݲ��� */
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
    /* ��ʼ��ͨ�� REGDMA_CHANNEL_REQ */
    g_lDMAChanID1 = mdrv_edma_chan_init(EDMA_BBP_DBG, (channel_isr)PsRegDmaIsr,
                                          EDMA_BBP_DBG, (BALONG_DMA_INT_DONE | BALONG_DMA_INT_TRANSFER_ERR));
    if (g_lDMAChanID1 < 0)
    {
        /*lint -e534*/
        vos_printf("\r\nPsRegDmaInit: fail to init edma1 channel, phy channel is 0x%x\r\n", g_lDMAChanID1);
        /*lint +e534*/
        return VOS_ERR;
    }

#if (3 == MULTI_MODEM_NUMBER)
    g_lDMAChanID2 = mdrv_edma_chan_init(EDMA_MEMORY_DSP_6, (channel_isr)PsRegDmaIsr,
                                          EDMA_MEMORY_DSP_6, (BALONG_DMA_INT_DONE | BALONG_DMA_INT_TRANSFER_ERR));
    if (g_lDMAChanID2 < 0)
    {
        /*lint -e534*/
        vos_printf("\r\nPsRegDmaInit: fail to init edma2 channel, phy channel is 0x%x\r\n", g_lDMAChanID2);
        /*lint +e534*/
        return VOS_ERR;
    }
#endif

#endif

    return VOS_OK;
}


VOS_VOID PsRegCapture(VOS_UINT32 ulSysMode)
{
    PS_REG_SYS_MODE_ENUM_UINT32         enSysMode;
    PS_REG_RPT_CFG_STRU                *pstPsRegRptCfg;
    VOS_UINT32                          ulTimeStart;
    VOS_UINT32                          ulTimeEnd;
    VOS_UINT32                          ulTime;

    if (VOS_FALSE == g_PsRegRptContrl.bRptEnableStatus)
    {
        return;
    }

    /*���岻ͬ��Ҫ����ת��*/
    enSysMode       = ulSysMode;
    pstPsRegRptCfg  = &g_astPsRegRptCfg[enSysMode];

    /*�жϵ�ǰ����Ĵ����ĸ���*/
    if (0 == pstPsRegRptCfg->ulCnt)
    {
        return;
    }

    ulTimeStart = PsRegGetSlice();
    g_stDmaTimeInfo.ulStartSlice = ulTimeStart;

    PsRegDmaCapture(ulSysMode);

    ulTimeEnd = PsRegGetSlice();
    ulTime = ulTimeEnd - ulTimeStart;
    if (ulTime > g_stDmaTimeInfo.ulDmaStartTime)
    {
        g_stDmaTimeInfo.ulDmaStartTime = ulTime;
    }

    return;
}


VOS_UINT32 PsRegNumberGet(PS_REG_SYS_MODE_ENUM_UINT32 enSysMode)
{
    return g_astPsRegRptCfg[enSysMode].ulCnt;
}


VOS_UINT32 PsRegSysModeGet(VOS_UINT32 ulSendBufIndex, VOS_UINT32 ulSendFrequency)
{
    return g_PsRegRptContrl.aulDmaDestWriteSysMode[ulSendBufIndex][ulSendFrequency];
}


VOS_VOID* PsRegsInfoAddrGet(PS_REG_SYS_MODE_ENUM_UINT32 enSysMode)
{
    return (VOS_VOID*)(g_astPsRegRptCfg[enSysMode].aulRegValue);
}


VOS_UINT32 PsRegInit(VOS_VOID)
{
    OM_BBP_DUMP_ENABLE_STRU             stEnableFlag;
    VOS_UINT32                           ulRet;

    /*lint -e534*/
    VOS_MemSet(&g_stPsRegRptINDMsg,  0, sizeof(g_stPsRegRptINDMsg));
    VOS_MemSet(g_astPsRegRptCfg,        0, sizeof(g_astPsRegRptCfg));
    VOS_MemSet(g_astPsRegRptBuf,        0, sizeof(g_astPsRegRptBuf));

    VOS_MemSet(&g_PsRegRptContrl,        0, sizeof(g_PsRegRptContrl));
    /*lint +e534*/

    g_ulRptRegInitStatus = VOS_FALSE;

    /* ��ȡNV���жϹ����Ƿ��� */
    if (NV_OK != NV_Read(en_NV_Item_BBP_DUMP_ENABLE,
                         (VOS_VOID *)(&stEnableFlag),
                         sizeof(OM_BBP_DUMP_ENABLE_STRU)))
    {
        /*lint -e534*/
        LogPrint("PsRegInit: Read Nv Fail\r\n");
        /*lint +e534*/
        return VOS_ERR;
    }

    /* �ж��Ƿ�����BBP����:ץ�Ĵ�����BBP����ֻ����һ */
    if (VOS_TRUE == stEnableFlag.ulEnable)
    {
        /*lint -e534*/
        LogPrint("PsRegInit: BBP Enable \r\n");
        /*lint +e534*/
        return VOS_OK;
    }

    /* EDMA��ʼ�� */
    ulRet = PsRegDmaInit();
    if (VOS_OK != ulRet)
    {
        /*lint -e534*/
        LogPrint("PsRegInit: Dma Init fail \r\n");
        /*lint +e534*/
        return ulRet;
    }

    g_ulRptRegDiffNum    = PS_REG_RPT_DIFF_NUM; /* �����ϱ�������ʼ�� */
    g_ulRptRegInitStatus = VOS_TRUE;

    return VOS_OK;
}


VOS_VOID PsRegSndOmAppRegModCnf(
    VOS_UINT16                          usTransPrimId,
    VOS_UINT32                          ulResult,
    OM_APP_REG_START_CNF_STRU          *pstOmAppRegCnf)
{
    OM_APP_TRANS_CNF_STRU              *pstAppTransCnf;
    OM_APP_REG_MODE_NUM_STRU           *pstAppModeNum;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          i;
    VOS_UINT32                          ulTotalLen;
    DIAG_TRANS_IND_STRU                 stDiagTransMsg;

    if ((PS_SUCC == ulResult) && (0 != pstOmAppRegCnf->ulSysModeNum))
    {
        /* ��Ҫ�ѹ������óɹ��ļĴ�����ַ���ظ����� */

        /* ��Ϣͷ���� */
        ulDataLen   = offsetof(OM_APP_REG_START_CNF_STRU,aucAddr) +
                      pstOmAppRegCnf->ulSysModeNum * offsetof(OM_APP_REG_MODE_NUM_STRU,aucAddr);

        /* �Ĵ�����ַ���� */
        for (i=0; i<PS_REG_SYS_MODE_BUTT; i++)
        {
            ulDataLen += g_astPsRegReqAddr[i].ulCnt * sizeof(VOS_UINT32);
        }
    }
    else
    {
        ulDataLen  = sizeof(OM_APP_REG_START_CNF_STRU);
    }

    pstAppTransCnf = (OM_APP_TRANS_CNF_STRU *)VOS_MemAlloc(WUEPS_PID_REG, DYNAMIC_MEM_PT,
                                       offsetof(OM_APP_TRANS_CNF_STRU, aucPara[0]) + ulDataLen);
    if (VOS_NULL_PTR == pstAppTransCnf)
    {
        PS_LOG(WUEPS_PID_REG, 0, LOG_LEVEL_ERROR, "Error: Alloc msg ID_OM_APP_REG_ADD_CNF fail!");
        return;
    }

    /* ��һ�ֽ�����β�ĳ��ȣ���λΪByte */
    ulTotalLen = (offsetof(OM_APP_TRANS_CNF_STRU, aucPara[0]) + ulDataLen);

    pstOmAppRegCnf->ulErrCode = ulResult;

    /*lint -e419 -e416 -e534 */
    VOS_MemCpy((VOS_VOID*)pstAppTransCnf->aucPara, (VOS_VOID*)pstOmAppRegCnf, offsetof(OM_APP_REG_START_CNF_STRU,aucAddr));
    /*lint +e419 +e416 +e534 */

    ulDataLen = offsetof(OM_APP_REG_START_CNF_STRU,aucAddr);
    /*����ǰ����ļĴ�����ַ����������������*/
    if ((PS_SUCC == ulResult) && (0 != pstOmAppRegCnf->ulSysModeNum))
    {
        for (i=0; i<PS_REG_SYS_MODE_BUTT; i++)
        {
            pstAppModeNum = (OM_APP_REG_MODE_NUM_STRU*)(pstAppTransCnf->aucPara + ulDataLen);

            if (0 !=g_astPsRegReqAddr[i].ulCnt)
            {
                pstAppModeNum->enSysMode = i;
                pstAppModeNum->ulRegNum  = g_astPsRegReqAddr[i].ulCnt;
                /*lint -e419 -e416 -e534 */
                VOS_MemCpy((VOS_VOID*)pstAppModeNum->aucAddr,
                           (VOS_VOID*)g_astPsRegReqAddr[i].aulRegAddr,
                           pstAppModeNum->ulRegNum * sizeof(VOS_UINT32));
                /*lint +e419 +e416 +e534 */

                ulDataLen += pstAppModeNum->ulRegNum * sizeof(VOS_UINT32) + offsetof(OM_APP_REG_MODE_NUM_STRU,aucAddr);
            }
        }
    }

    stDiagTransMsg.ulModule = DIAG_GEN_MODULE_EX(DIAG_MODEM_0, DIAG_MODE_COMM, DIAG_MSG_TYPE_BBP);
    stDiagTransMsg.ulPid    = WUEPS_PID_REG;
    stDiagTransMsg.ulMsgId  = usTransPrimId;
    stDiagTransMsg.ulLength = ulTotalLen;
    stDiagTransMsg.pData    = (VOS_VOID *)pstAppTransCnf;

    if (VOS_OK != DIAG_TransReport_Ex(&stDiagTransMsg))
    {
        PS_LOG(WUEPS_PID_REG, 0, LOG_LEVEL_ERROR, "Error: Send msg ID_OM_APP_REG_ADD_CNF fail!");
    }
    else
    {
        PS_LOG(WUEPS_PID_REG, 0, LOG_LEVEL_INFO, "Info: Send msg ID_OM_APP_REG_ADD_CNF success!");
    }

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_REG, pstAppTransCnf);
    /*lint +e534*/

    return ;
}
VOS_VOID PsRegRcvAppOmRegDiffSetNumReq(VOS_VOID* pRcvMsg)
{
    OM_APP_REG_START_CNF_STRU           stOmAppRegCnf;
    OM_REG_RPT_DIFF_STRU               *pRegRptDiff;

    (VOS_VOID)VOS_MemSet(&stOmAppRegCnf, 0, sizeof(OM_APP_REG_START_CNF_STRU));

    PsRegDmaInfoShow();

    /* �ظ����߳�ʼֵ */
    stOmAppRegCnf.ulSysModeNum = 0;

    /* ץ�Ĵ���ʹ�� */
    if (VOS_TRUE != g_ulRptRegInitStatus)
    {
        /*lint -e534*/
        LogPrint("\r\nPsRegRcvAppOmRegDiffSetNumReq:Reg not Init!");
        /*lint +e534*/
        PsRegSndOmAppRegModCnf(ID_APP_OM_REG_DIFF_CNF, PS_REG_RPT_NOT_ENABLE, &stOmAppRegCnf);
        return ;
    }

    pRegRptDiff = (OM_REG_RPT_DIFF_STRU*)pRcvMsg;

    g_ulRptRegDiffNum = pRegRptDiff->ulRptDiffNum;

    PsRegSndOmAppRegModCnf(ID_APP_OM_REG_DIFF_CNF, PS_REG_OK, &stOmAppRegCnf);

    return;
}


VOS_VOID PsRegRcvAppOmRegStopReq(VOS_VOID* pRcvMsg)
{
    OM_REG_RPT_STOP_STRU               *pMsg = (OM_REG_RPT_STOP_STRU*)pRcvMsg;
    OM_APP_REG_START_CNF_STRU           stOmAppRegCnf;
    VOS_INT                             lLockLevel;
    VOS_INT                             lRet;

    (VOS_VOID)VOS_MemSet(&stOmAppRegCnf, 0, sizeof(OM_APP_REG_START_CNF_STRU));

    /* �ظ����߳�ʼֵ */
    stOmAppRegCnf.ulSysModeNum = 0;

    /* ץ�Ĵ���ʹ�� */
    if (VOS_TRUE != g_ulRptRegInitStatus)
    {
        /*lint -e534*/
        LogPrint("\r\nPsRegRcvAppOmRegStartReq:Reg not Init!");
        /*lint +e534*/
        PsRegSndOmAppRegModCnf(ID_APP_OM_REG_STOP_CNF, PS_REG_RPT_NOT_ENABLE, &stOmAppRegCnf);
        return;
    }

    /* ������� */
    if (PS_REG_SYS_MODE_BUTT <= pMsg->enSysMode)
    {
        /*lint -e534*/
        LogPrint("\r\nPsRegRcvAppOmRegStartReq:Req mode num err!\r\n");
        /*lint +e534*/
        PsRegSndOmAppRegModCnf(ID_APP_OM_REG_STOP_CNF, PS_REG_MODE_NUM_ERR, &stOmAppRegCnf);
        return ;
    }

    lLockLevel = VOS_SplIMP();
    /*lint -e534*/
    VOS_MemSet(g_astPsRegRptCfg, 0, sizeof(g_astPsRegRptCfg));
    /*lint +e534*/
    VOS_Splx(lLockLevel);

    /*�Ĵ����ϱ������Ѿ����ڹر�״̬�����ӡ��Ϣ*/
    if (VOS_FALSE == g_PsRegRptContrl.bRptEnableStatus)
    {
        /*lint -e534*/
        LogPrint("\r\nPsRegRcvAppOmRegStopReq:RegRptStart Function has been stoped!");
        /*lint +e534*/
        PsRegSndOmAppRegModCnf(ID_APP_OM_REG_STOP_CNF, PS_REG_STOP_ERR, &stOmAppRegCnf);
        return;
    }

    if (VOS_TRUE == g_PsRegRptContrl.bEdma0StartStatus)
    {
        /* ֹͣEDMA0 */
        lRet = mdrv_edma_chan_stop((VOS_UINT32)g_lDMAChanID0);
        if (MDRV_ERROR == lRet)
        {
            /*lint -e534*/
            LogPrint("\r\nPsRegRcvAppOmRegStopReq:Edma0 stop fail!");
            /*lint +e534*/
            PsRegSndOmAppRegModCnf(ID_APP_OM_REG_STOP_CNF, PS_REG_STOP_DAM_FAIL, &stOmAppRegCnf);
            return ;
        }
    }

#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
    if (VOS_TRUE == g_PsRegRptContrl.bEdma1StartStatus)
    {
        lRet = mdrv_edma_chan_stop((VOS_UINT32)g_lDMAChanID1);
        if (MDRV_ERROR == lRet)
        {
            /*lint -e534*/
            LogPrint("\r\nPsRegRcvAppOmRegStopReq:Edma1 stop fail!");
            /*lint +e534*/
            PsRegSndOmAppRegModCnf(ID_APP_OM_REG_STOP_CNF, PS_REG_STOP_DAM_FAIL, &stOmAppRegCnf);
            return ;
        }
    }

#if (3 == MULTI_MODEM_NUMBER)
    if (VOS_TRUE == g_PsRegRptContrl.bEdma2StartStatus)
    {
        lRet = mdrv_edma_chan_stop((VOS_UINT32)g_lDMAChanID2);
        if (MDRV_ERROR == lRet)
        {
            /*lint -e534*/
            LogPrint("\r\nPsRegRcvAppOmRegStopReq:Edma2 stop fail!");
            /*lint +e534*/
            PsRegSndOmAppRegModCnf(ID_APP_OM_REG_STOP_CNF, PS_REG_STOP_DAM_FAIL, &stOmAppRegCnf);
            return ;
        }
    }
#endif
#endif

    /* ����ϱ�����״̬ */
    /*lint -e534*/
    VOS_MemSet(&g_PsRegRptContrl, 0, sizeof(g_PsRegRptContrl));
    /*lint +e534*/

    PsRegSndOmAppRegModCnf(ID_APP_OM_REG_STOP_CNF, PS_REG_OK, &stOmAppRegCnf);

    return;
}


VOS_UINT32 PsRegAddrCheck(PS_REG_SYS_MODE_ENUM_UINT32 enSysMode, VOS_UINT32 ulAddr)
{
    VOS_UINT32                          ulRegBase = 0;
    VOS_UINT32                          ulRegComm = (SOC_BBP_COMM_BASE_ADDR & 0xFFF00000);

    if (PS_REG_SYS_MODE_WCDMA == enSysMode)
    {
        ulRegBase  = (SOC_BBP_WCDMA_BASE_ADDR & 0xFFF00000);
    }
    else if (PS_REG_SYS_MODE_GSM == enSysMode)
    {
        ulRegBase  = (SOC_BBP_GSM_BASE_ADDR & 0xFFFF0000);
    }
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
    else if (PS_REG_SYS_MODE_GSM1 == enSysMode)
    {
        ulRegBase  = (SOC_BBP_GSM1_BASE_ADDR & 0xFFFF0000);
    }

#if (3 == MULTI_MODEM_NUMBER)
    else if (PS_REG_SYS_MODE_GSM2 == enSysMode)
    {
        ulRegBase  = (SOC_BBP_GSM_BASE_ADDR & 0xFFFF0000);
    }
#endif

#endif
    else
    {
        ulRegBase  = 0;
    }

    if (ulRegComm == (ulAddr & 0xFFF00000))
    {
        return VOS_OK;
    }

    if (PS_REG_SYS_MODE_WCDMA == enSysMode)
    {
        if (ulRegBase != (ulAddr & 0xFFF00000))
        {
            g_ulPsRegErrCount++;
            return VOS_ERR;
        }
    }
    else
    {
        if (ulRegBase != (ulAddr & 0xFFFF0000))
        {
            g_ulPsRegErrCount++;
            return VOS_ERR;
        }
    }

    return VOS_OK;
}


VOS_UINT32 PsRegRcvAppMsgCheck(APP_OM_REG_START_MODE_STRU *pRcvMsg)
{
    VOS_UINT32                          ulRegNumLoop;

    /*����ģʽ���*/
    if (PS_REG_SYS_MODE_BUTT <= pRcvMsg->enSysMode)
    {
        /*lint -e534*/
        LogPrint1("PsRegRcvAppMsgCheck:Config system mode is %d wrong!!\r\n",
                (VOS_INT32)pRcvMsg->enSysMode);
        /*lint +e534*/
        return PS_REG_MODE_ERR;
    }

    /*�Ĵ����������*/
    if (0 == pRcvMsg->ulRegNum)
    {
        /*lint -e534*/
        LogPrint("PsRegRcvAppMsgCheck:Regist Number Error:0!");
        /*lint +e534*/
        return PS_REG_NUM_ZERO;
    }

    if ((PS_REG_SYS_MODE_WCDMA == pRcvMsg->enSysMode) && (PS_REG_RPT_MAX_NUM < pRcvMsg->ulRegNum))
    {
        /*lint -e534*/
        LogPrint1("PsRegRcvAppMsgCheck:Reg wcdma Number %d  Error!", (VOS_INT32)pRcvMsg->ulRegNum);
        /*lint +e534*/
        return PS_W_REG_NUM_TOO_LARGE;
    }

    if ((PS_REG_SYS_MODE_GSM == pRcvMsg->enSysMode) && (PS_REG_RPT_G_MAX_NUM < pRcvMsg->ulRegNum))
    {
        /*lint -e534*/
        LogPrint1("PsRegRcvAppMsgCheck:Reg gsm Number %d  Error!", (VOS_INT32)pRcvMsg->ulRegNum);
        /*lint +e534*/
        return PS_G_REG_NUM_TOO_LARGE;
    }

#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
    if ((PS_REG_SYS_MODE_GSM1 == pRcvMsg->enSysMode) && (PS_REG_RPT_G_MAX_NUM < pRcvMsg->ulRegNum))
    {
        /*lint -e534*/
        LogPrint1("PsRegRcvAppMsgCheck:Regist gsm1 Number %d  Error!", (VOS_INT32)pRcvMsg->ulRegNum);
        /*lint +e534*/
        return PS_G1_REG_NUM_TOO_LARGE;
    }

#if (3 == MULTI_MODEM_NUMBER)
    if ((PS_REG_SYS_MODE_GSM2 == pRcvMsg->enSysMode) && (PS_REG_RPT_G_MAX_NUM < pRcvMsg->ulRegNum))
    {
        /*lint -e534*/
        LogPrint1("PsRegRcvAppMsgCheck:Regist gsm2 Number %d  Error!", (VOS_INT32)pRcvMsg->ulRegNum);
        /*lint +e534*/
        return PS_G2_REG_NUM_TOO_LARGE;
    }
#endif

#endif

    /* �����ֽڶ���ĵ�ַ�����ϱ� */
    if (0 != (pRcvMsg->aulRegAddr[0]&HPA_ARM_ALIGNMENT))
    {
        /*lint -e534*/
        LogPrint1("PsRegRcvAppMsgCheck:no align! %d", (VOS_INT32)pRcvMsg->aulRegAddr[0]);
        /*lint +e534*/
        return PS_REG_ALIGN_ERR;
    }

    if (VOS_ERR == PsRegAddrCheck(pRcvMsg->enSysMode, pRcvMsg->aulRegAddr[0]))
    {
        /*lint -e534*/
        LogPrint1("PsRegRcvAppMsgCheck:Invalid Address! %d", (VOS_INT32)pRcvMsg->aulRegAddr[0]);
        /*lint +e534*/
        return PS_REG_ADDR_NOT_MATCH_MODE;
    }

    for (ulRegNumLoop = 1; ulRegNumLoop < pRcvMsg->ulRegNum; ulRegNumLoop++)
    {
        /* �ֽڶ����� */
        /*lint -e661*/
        if (0 != (pRcvMsg->aulRegAddr[ulRegNumLoop]&HPA_ARM_ALIGNMENT))
        {
            /*lint -e534*/
            LogPrint2("PsRegRcvAppMsgCheck:no align! %d %d", (VOS_INT32)pRcvMsg->aulRegAddr[ulRegNumLoop],(VOS_INT32)ulRegNumLoop);
            /*lint +e534*/
            return PS_REG_ALIGN_ERR;
        }

        /* �Ĵ�������򵥼�� */
        if (pRcvMsg->aulRegAddr[ulRegNumLoop - 1] >= pRcvMsg->aulRegAddr[ulRegNumLoop])
        {
            /*lint -e534*/
            LogPrint2("PsRegRcvAppMsgCheck: no order! %d %d", (VOS_INT32)pRcvMsg->aulRegAddr[ulRegNumLoop],(VOS_INT32)ulRegNumLoop);
            /*lint +e534*/
            return PS_REG_QUEUE_ERR;
        }

        if (VOS_ERR == PsRegAddrCheck(pRcvMsg->enSysMode, pRcvMsg->aulRegAddr[ulRegNumLoop]))
        {
            /*lint -e534*/
            LogPrint2("PsRegRcvAppMsgCheck:Invalid Address! %d %d", (VOS_INT32)pRcvMsg->aulRegAddr[ulRegNumLoop],(VOS_INT32)ulRegNumLoop);
            /*lint +e534*/
            return PS_REG_ADDR_NOT_MATCH_MODE;
        }
        /*lint +e661*/
    }

    return VOS_OK;
}
VOS_UINT32 PsRegRcvAppOmRegConfig(VOS_VOID* pMsg)
{
    APP_OM_REG_START_MODE_STRU         *pRcvMsg;
    VOS_UINT32                          ulRest;

    pRcvMsg = (APP_OM_REG_START_MODE_STRU*)pMsg;

    /* ������� */
    ulRest = PsRegRcvAppMsgCheck(pRcvMsg);
    if (VOS_OK != ulRest)
    {
        /*lint -e534*/
        LogPrint("PsRegRcvAppOmRegStartReq:Reg Start Req para err!\r\n");
        /*lint +e534*/
        return ulRest;
    }

    /* DMA�ڵ����� */
    if (VOS_OK != PsRegDmaNodeInit(pRcvMsg))
    {
        /*lint -e534*/
        LogPrint("PsRegRcvAppOmRegStartReq:Edma stop fail!");
        /*lint +e534*/
        return PS_REG_RPT_DMA_INIT_FAIL;
    }

    g_astPsRegRptCfg[pRcvMsg->enSysMode].ulCnt  = pRcvMsg->ulRegNum;

    /* ���湤���·��Ĵ����ϱ���ַ */
    /*lint -e534*/
    VOS_MemCpy(g_astPsRegReqAddr[pRcvMsg->enSysMode].aulRegAddr,
               pRcvMsg->aulRegAddr,
               (pRcvMsg->ulRegNum)*sizeof(VOS_UINT32));/* [false alarm]:Buffer overflow����  */
    /*lint +e534*/

    g_astPsRegReqAddr[pRcvMsg->enSysMode].ulCnt = pRcvMsg->ulRegNum;

    return VOS_OK;

}


VOS_VOID PsRegRcvAppOmRegStartReq(VOS_VOID* pMsg)
{
    APP_OM_REG_START_REQ_STRU          *pRcvMsgHead = (APP_OM_REG_START_REQ_STRU*)pMsg;
    OM_APP_REG_START_CNF_STRU           stOmAppRegCnf;
    APP_OM_REG_START_MODE_STRU         *pRcvMsg;
    VOS_UINT32                          ulMsgLen = 0;
    VOS_UINT32                          ulRest;
    VOS_UINT32                          i;

    (VOS_VOID)VOS_MemSet(&stOmAppRegCnf, 0, sizeof(OM_APP_REG_START_CNF_STRU));

    /* �ظ����߳�ʼֵ */
    stOmAppRegCnf.ulSysModeNum = 0;

    /* ץ�Ĵ���ʹ�� */
    if (VOS_TRUE != g_ulRptRegInitStatus)
    {
        /*lint -e534*/
        LogPrint("\r\nPsRegRcvAppOmRegStartReq:Reg not Init!");
        /*lint +e534*/
        PsRegSndOmAppRegModCnf(ID_APP_OM_REG_START_CNF, PS_REG_RPT_NOT_ENABLE, &stOmAppRegCnf);
        return;
    }

    /* �ж��ϱ�״̬ */
    if (VOS_FALSE != g_PsRegRptContrl.bRptEnableStatus)
    {
        /*lint -e534*/
        LogPrint("\r\nPsRegRcvAppOmRegStartReq:Rpt Status is not Stop!");
        /*lint +e534*/
        PsRegSndOmAppRegModCnf(ID_APP_OM_REG_START_CNF, PS_REG_STOP_ERR, &stOmAppRegCnf);
        return;
    }

    /* ������� */
    if (PS_REG_SYS_MODE_BUTT < pRcvMsgHead->ulSysModeNum)
    {
        /*lint -e534*/
        LogPrint1("\r\nPsRegRcvAppOmRegStartReq:Req mode num err is %d!", (VOS_INT)pRcvMsgHead->ulSysModeNum);
        /*lint +e534*/
        PsRegSndOmAppRegModCnf(ID_APP_OM_REG_START_CNF, PS_REG_MODE_NUM_ERR, &stOmAppRegCnf);
        return;
    }

    /* ��Ϣ���ȼ�� */
    if (sizeof(APP_OM_REG_START_MODE_STRU) > pRcvMsgHead->ulValueLenth)
    {
        /*lint -e534*/
        LogPrint("\r\nPsRegRcvAppOmRegStartReq:Req Msg len err!\r\n");
        /*lint +e534*/
        PsRegSndOmAppRegModCnf(ID_APP_OM_REG_START_CNF, PS_REG_MSG_LEN_ERR, &stOmAppRegCnf);
        return;
    }


    /* ��չ����·������ϱ���ַ */
    /*lint -e534*/
    VOS_MemSet(g_astPsRegReqAddr, 0, sizeof(g_astPsRegReqAddr));
    /*lint +e534*/

    /* �����·����� */
    for (i=0; i< pRcvMsgHead->ulSysModeNum; i++)
    {
        /* ȡ��ÿ����Ϣ */
        pRcvMsg = (APP_OM_REG_START_MODE_STRU*)(pRcvMsgHead->aucValue + ulMsgLen);

        /* ��Ϣ��ƫ�� */
        ulMsgLen += pRcvMsg->ulLenth + sizeof(VOS_UINT32);

        ulRest = PsRegRcvAppOmRegConfig((VOS_VOID*)pRcvMsg);
        if(VOS_OK != ulRest)
        {
            PsRegSndOmAppRegModCnf(ID_APP_OM_REG_START_CNF, ulRest, &stOmAppRegCnf);
            return ;
        }
    }

    /* �ָ��Ĵ����ϱ� */
    g_PsRegRptContrl.bRptEnableStatus = VOS_TRUE;

    /* �����߻ظ���Ϣ */
    stOmAppRegCnf.ulSysModeNum = pRcvMsgHead->ulSysModeNum;
    stOmAppRegCnf.ulWbbpAddr   = (VOS_UINT32)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_WBBP);
    stOmAppRegCnf.ulGbbpAddr   = (VOS_UINT32)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_GBBP);
    PsRegSndOmAppRegModCnf(ID_APP_OM_REG_START_CNF, PS_REG_OK, &stOmAppRegCnf);

    return;
}

#if (FEATURE_GUC_BBP_TRIG == FEATURE_ON)
VOS_VOID PsRegSndGUCBBPDbgRegCnf(
    VOS_UINT16                          usTransPrimId,
    VOS_UINT32                          ulResult,
    VOS_VOID                           *pstOmAppRegCnf)
{
    APP_OM_GUC_REGLIST_CNF_STRU        *pstAppTransCnf;
    VOS_UINT32                          ulTotalLen;
    DIAG_TRANS_IND_STRU                 stDiagTransMsg;

    ulTotalLen = PS_GUCBBP_TRIG_NUM + 2 * sizeof(VOS_UINT32);
    pstAppTransCnf = (APP_OM_GUC_REGLIST_CNF_STRU *)VOS_MemAlloc(WUEPS_PID_REG, DYNAMIC_MEM_PT,
                                      ulTotalLen);
    if (VOS_NULL_PTR == pstAppTransCnf)
    {
        PS_LOG(WUEPS_PID_REG, 0, LOG_LEVEL_ERROR, "Error: Alloc msg ID_APP_OM_REGLIST_CFG_CNF fail!");
        return;
    }

    pstAppTransCnf->ulErrCode = ulResult;
    /*lint -e534 -e419*/
    VOS_MemCpy((VOS_VOID*)pstAppTransCnf->aucAddr, (VOS_VOID*)pstOmAppRegCnf, PS_GUCBBP_TRIG_NUM + sizeof(VOS_UINT32));
    /*lint +e534 +e419*/

    stDiagTransMsg.ulModule = DIAG_GEN_MODULE_EX(DIAG_MODEM_0, DIAG_MODE_COMM, DIAG_MSG_TYPE_BBP);
    stDiagTransMsg.ulPid    = WUEPS_PID_REG;
    stDiagTransMsg.ulMsgId  = usTransPrimId;
    stDiagTransMsg.ulLength = ulTotalLen;
    stDiagTransMsg.pData    = (VOS_VOID *)pstAppTransCnf;

    if (VOS_OK != DIAG_TransReport_Ex(&stDiagTransMsg))
    {
        PS_LOG(WUEPS_PID_REG, 0, LOG_LEVEL_ERROR, "Error: Send msg ID_APP_OM_REGLIST_CFG_CNF fail!");
    }
    else
    {
        PS_LOG(WUEPS_PID_REG, 0, LOG_LEVEL_INFO, "Info: Send msg ID_APP_OM_REGLIST_CFG_CNF success!");
    }

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_REG, pstAppTransCnf);
    /*lint +e534*/

    return ;
}


VOS_VOID  PsRegRcvGUCBBPDbgRegSetReq( MsgBlock *pRcvMsg )
{
    APP_OM_GUC_REGLIST_REQ_STRU        *pRcvMsgHead = (APP_OM_GUC_REGLIST_REQ_STRU*)pRcvMsg;
    APP_OM_GUC_REGLIST_INFO_STRU       *pRegListInfo;
    VOS_UINT32                          ulIndex = 0;
    VOS_UINT32                          ulRegValue;
    VOS_UINT32                          ulRegNum = 0;
    MODEM_ID_ENUM_UINT16                enModemId = MODEM_ID_BUTT;
    PS_REG_BBP_TRIG_MODE_ENUM_UINT16    enMode = PS_REG_BBP_TRIG_MODE_BUTT;
    VOS_UINT32                          ulAddr = 0;
    VOS_UINT32                          ulLen = 0;
    VOS_UINT32                          i,j;
    VOS_UINT32                          ulBBPListBaseAddr = DBG_TRIG_TRACE_ADDR_RAM_ADDR;

    /* ��Ϣ���ȼ�� */
    pRegListInfo = (APP_OM_GUC_REGLIST_INFO_STRU *)pRcvMsgHead->aucValue;

    /* ����reg list�����Ĵ����б� */
    for (ulIndex = 0; ulIndex < pRegListInfo->ulRegNum; ulIndex++)
    {
        ulRegValue  = pRegListInfo->aulRegAddr[ulIndex];

        switch(ulRegValue)
        {
            case PS_GUCBBP_TRIG_HEAD:
                ulIndex++;
                /*lint -e661*/
                ulRegValue  = pRegListInfo->aulRegAddr[ulIndex];
                /*lint +e661*/

                enModemId   = ulRegValue >> 16;
                enMode      = ulRegValue & 0x0000FFFF;

                if ((MODEM_ID_BUTT <= enModemId)
                    || (PS_REG_BBP_TRIG_MODE_BUTT <= enMode))
                {
                    PsRegSndGUCBBPDbgRegCnf(ID_APP_OM_REGLIST_CFG_CNF, PS_REG_REGLIST_ERR, pRcvMsgHead->aucValue);

                    return;
                }

                ulRegNum    = 0;

                g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[enModemId][enMode].ulGUCBBPTrigEnable   = VOS_TRUE;
                break;

            case PS_GUCBBP_TRIG_END:

                if ((MODEM_ID_BUTT <= enModemId)
                    || (PS_REG_BBP_TRIG_MODE_BUTT <= enMode))
                {
                    PsRegSndGUCBBPDbgRegCnf(ID_APP_OM_REGLIST_CFG_CNF, PS_REG_REGLIST_ERR, pRcvMsgHead->aucValue);

                    return;
                }

                g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[enModemId][enMode].ulGUCBBPTrigNumber   = ulRegNum;

                enModemId   = MODEM_ID_BUTT;
                enMode      = PS_REG_BBP_TRIG_MODE_BUTT;

                ulRegNum    = 0xFFFFFFFF;
                break;

            default:
                if ((MODEM_ID_BUTT <= enModemId)
                    || (PS_REG_BBP_TRIG_MODE_BUTT <= enMode)
                    || (0xFFFFFFFF == ulRegNum))
                {
                    PsRegSndGUCBBPDbgRegCnf(ID_APP_OM_REGLIST_CFG_CNF, PS_REG_REGLIST_ERR, pRcvMsgHead->aucValue);

                    return;
                }
                else
                {
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[enModemId][enMode].ulGUCBBPTrigList[ulRegNum] = ulRegValue;
                    ulRegNum++;
                }
                break;
        }

    }

    for (i = 0; i < MODEM_ID_BUTT; i++)
    {
        for (j = 0; j < PS_REG_BBP_TRIG_MODE_BUTT; j++)
        {
            if (VOS_TRUE == g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[i][j].ulGUCBBPTrigEnable)
            {
                /* ����ģʽ�ļĴ�����Ϣ���õ�BBP TRACE RAM�� */
                for (ulRegNum = 0; ulRegNum < g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[i][j].ulGUCBBPTrigNumber; ulRegNum++)
                {
                    HPA_Write32Reg(ulBBPListBaseAddr, g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[i][j].ulGUCBBPTrigList[ulRegNum]);
                    ulBBPListBaseAddr += 4;
                }

                /* ����ģʽ��CFG�Ĵ������ݣ�����GUCģʽ����ַ��Ϣ������ʹ�� */
                ulRegValue  = ((g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[i][j].ulGUCBBPTrigBaseAddr >> 12 ) & 0x000FFF00);
                HPA_Write32Reg(g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[i][j].ulGUCBBPTrigCFGReg, ulRegValue | 0x1);

                /* ����ģʽ��INFO�Ĵ������ݣ�����BBP TRACE RAM����ַ��Ϣ������ʹ�� */
                ulAddr  &= 0x1FF;
                ulLen   = (g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[i][j].ulGUCBBPTrigNumber << 12) & 0x1FF000;

                HPA_Write32Reg(g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[i][j].ulGUCBBPTrigInfoReg, ulAddr | ulLen);

                ulAddr  += (sizeof(VOS_UINT32)*g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[i][j].ulGUCBBPTrigNumber);
            }
        }
    }

    PsRegSndGUCBBPDbgRegCnf(ID_APP_OM_REGLIST_CFG_CNF, PS_REG_OK, pRcvMsgHead->aucValue);

    return;
}
VOS_VOID  PsRegRcvGUCBBPDbgStartReq( MsgBlock *pRcvMsg )
{
    APP_OM_BBPTRIG_CFG_REQ_STRU        *pRcvMsgHead = (APP_OM_BBPTRIG_CFG_REQ_STRU*)pRcvMsg;
    PS_REG_BBPTRIG_CFG_INFO_STRU       *pstInfo;
    VOS_UINT32                          i,j;

    /* ȷ�ϼĴ����б�ģʽ */
    pstInfo = (PS_REG_BBPTRIG_CFG_INFO_STRU *)pRcvMsgHead->aucValue;

    for (i = 0; i < MODEM_ID_BUTT; i++)
    {
        for (j = 0; j < PS_REG_BBP_TRIG_MODE_BUTT; j++)
        {
            g_stPsRegGUCBBPDbgState.aulValue[i][j]  = pstInfo->aulValue[i][j];

            if (VOS_TRUE == g_stPsRegGUCBBPDbgState.aulValue[i][j])
            {
                /* ȷ�ϵ�ǰģʽ���ϵ�̬����ʹ�ܼĴ��������� */
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )

#endif

                HPA_Write32RegMask(g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[i][j].ulGUCBBPTrigCFGReg, 0x10);
            }
        }
    }


    return;
}


VOS_UINT32 PsRegGUCBBPDbgGetState( MODEM_ID_ENUM_UINT16 enModemId, VOS_RATMODE_ENUM_UINT32 enMode )
{
    PS_REG_BBP_TRIG_MODE_ENUM_UINT16    enPsRegType;

    if (enModemId >= MODEM_ID_BUTT || enMode >= VOS_RATMODE_BUTT)
    {
        return VOS_ERR;
    }

    switch (enMode)
    {
        case VOS_RATMODE_GSM:
            enPsRegType = PS_REG_BBP_TRIG_MODE_GSM;
            break;
        case VOS_RATMODE_WCDMA:
            enPsRegType = PS_REG_BBP_TRIG_MODE_WCDMA;
            break;
        case VOS_RATMODE_1X:
        case VOS_RATMODE_HRPD:
            /*��ҪͶƱ*/
            enPsRegType = PS_REG_BBP_TRIG_MODE_CDMA;
            break;
        default:
            return VOS_ERR;
    }

    return g_stPsRegGUCBBPDbgState.aulValue[enModemId][enPsRegType];
}

VOS_VOID PsRegGUCBBPDbgEnable(MODEM_ID_ENUM_UINT16 enModemId, VOS_RATMODE_ENUM_UINT32 enMode)
{
    PS_REG_BBP_TRIG_MODE_ENUM_UINT16    enPsRegType;

    if (enModemId >= MODEM_ID_BUTT || enMode >= VOS_RATMODE_BUTT)
    {
        return;
    }

    switch (enMode)
    {
        case VOS_RATMODE_GSM:
            enPsRegType = PS_REG_BBP_TRIG_MODE_GSM;
            break;
        case VOS_RATMODE_WCDMA:
            enPsRegType = PS_REG_BBP_TRIG_MODE_WCDMA;
            break;
        case VOS_RATMODE_1X:
        case VOS_RATMODE_HRPD:
            /*��ҪͶƱ*/
            enPsRegType = PS_REG_BBP_TRIG_MODE_CDMA;
            break;
        default:
            return;
    }

    if (VOS_TRUE == g_stPsRegGUCBBPDbgState.aulValue[enModemId][enPsRegType])
    {
        return;
    }

    return;
}

VOS_VOID PsRegGUCBBPDbgDisable(MODEM_ID_ENUM_UINT16 enModemId, VOS_RATMODE_ENUM_UINT32 enMode)
{
    PS_REG_BBP_TRIG_MODE_ENUM_UINT16    enPsRegType;

    if (enModemId >= MODEM_ID_BUTT || enMode >= VOS_RATMODE_BUTT)
    {
        return;
    }

    switch (enMode)
    {
        case VOS_RATMODE_GSM:
            enPsRegType = PS_REG_BBP_TRIG_MODE_GSM;
            break;
        case VOS_RATMODE_WCDMA:
            enPsRegType = PS_REG_BBP_TRIG_MODE_WCDMA;
            break;
        case VOS_RATMODE_1X:
        case VOS_RATMODE_HRPD:
            /*��ҪͶƱ*/
            enPsRegType = PS_REG_BBP_TRIG_MODE_CDMA;
            break;
        default:
            return;
    }

    if (VOS_TRUE == g_stPsRegGUCBBPDbgState.aulValue[enModemId][enPsRegType])
    {
        return;
    }

    return;
}
VOS_VOID PsRegGUCBBPInit( VOS_VOID )
{
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_WCDMA].ulGUCBBPTrigEnable      = VOS_FALSE;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_WCDMA].ulGUCBBPTrigNumber      = 0;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_WCDMA].ulGUCBBPTrigCFGReg      = DBG_TRIG_W1_CONFIG1_ADDR;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_WCDMA].ulGUCBBPTrigInfoReg     = DBG_TRIG_W1_CONFIG2_ADDR;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_WCDMA].ulGUCBBPTrigBaseAddr    = SOC_BBP_WCDMA_BASE_ADDR;

    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_WCDMA].ulGUCBBPTrigEnable      = VOS_FALSE;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_WCDMA].ulGUCBBPTrigNumber      = 0;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_WCDMA].ulGUCBBPTrigCFGReg      = DBG_TRIG_W2_CONFIG1_ADDR;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_WCDMA].ulGUCBBPTrigInfoReg     = DBG_TRIG_W2_CONFIG2_ADDR;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_WCDMA].ulGUCBBPTrigBaseAddr    = 0;

    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_GSM].ulGUCBBPTrigEnable        = VOS_FALSE;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_GSM].ulGUCBBPTrigNumber        = 0;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_GSM].ulGUCBBPTrigCFGReg        = DBG_TRIG_G1_CONFIG1_ADDR;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_GSM].ulGUCBBPTrigInfoReg       = DBG_TRIG_G1_CONFIG2_ADDR;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_GSM].ulGUCBBPTrigBaseAddr      = SOC_BBP_GSM0_BASE_ADDR;

    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_GSM].ulGUCBBPTrigEnable        = VOS_FALSE;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_GSM].ulGUCBBPTrigNumber        = 0;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_GSM].ulGUCBBPTrigCFGReg        = DBG_TRIG_G2_CONFIG1_ADDR;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_GSM].ulGUCBBPTrigInfoReg       = DBG_TRIG_G2_CONFIG2_ADDR;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_GSM].ulGUCBBPTrigBaseAddr      = SOC_BBP_GSM1_BASE_ADDR;

    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_CDMA].ulGUCBBPTrigEnable       = VOS_FALSE;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_CDMA].ulGUCBBPTrigNumber       = 0;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_CDMA].ulGUCBBPTrigCFGReg       = DBG_TRIG_C1_CONFIG1_ADDR;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_CDMA].ulGUCBBPTrigInfoReg      = DBG_TRIG_C1_CONFIG2_ADDR;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_CDMA].ulGUCBBPTrigBaseAddr     = SOC_BBP_CDMA_BASE_ADDR;

    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_CDMA].ulGUCBBPTrigEnable       = VOS_FALSE;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_CDMA].ulGUCBBPTrigNumber       = 0;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_CDMA].ulGUCBBPTrigCFGReg       = DBG_TRIG_C2_CONFIG1_ADDR;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_CDMA].ulGUCBBPTrigInfoReg      = DBG_TRIG_C2_CONFIG2_ADDR;
    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_CDMA].ulGUCBBPTrigBaseAddr     = 0;

    return;
}

VOS_VOID PsRegGUCBBPShowTrigInfo(VOS_VOID)
{
    /*lint -e534*/
    vos_printf("\r\nThe DBG_TRIG_W1_CONFIG1_ADDR         is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_WCDMA].ulGUCBBPTrigCFGReg      );
    vos_printf("\r\nThe DBG_TRIG_W1_CONFIG2_ADDR         is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_WCDMA].ulGUCBBPTrigInfoReg     );
    vos_printf("\r\nThe SOC_BBP_WCDMA1_BASE_ADDR         is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_WCDMA].ulGUCBBPTrigBaseAddr    );

    vos_printf("\r\nThe DBG_TRIG_W2_CONFIG1_ADDR         is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_WCDMA].ulGUCBBPTrigCFGReg      );
    vos_printf("\r\nThe DBG_TRIG_W2_CONFIG2_ADDR         is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_WCDMA].ulGUCBBPTrigInfoReg     );
    vos_printf("\r\nThe SOC_BBP_WCDMA2_BASE_ADDR         is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_WCDMA].ulGUCBBPTrigBaseAddr    );

    vos_printf("\r\nThe DBG_TRIG_G1_CONFIG1_ADDR         is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_GSM].ulGUCBBPTrigCFGReg        );
    vos_printf("\r\nThe DBG_TRIG_G1_CONFIG2_ADDR         is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_GSM].ulGUCBBPTrigInfoReg       );
    vos_printf("\r\nThe SOC_BBP_GSM1_BASE_ADDR           is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_GSM].ulGUCBBPTrigBaseAddr      );

    vos_printf("\r\nThe DBG_TRIG_G2_CONFIG1_ADDR         is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_GSM].ulGUCBBPTrigCFGReg        );
    vos_printf("\r\nThe DBG_TRIG_G2_CONFIG2_ADDR         is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_GSM].ulGUCBBPTrigInfoReg       );
    vos_printf("\r\nThe SOC_BBP_GSM2_BASE_ADDR           is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_GSM].ulGUCBBPTrigBaseAddr      );

    vos_printf("\r\nThe DBG_TRIG_C1_CONFIG1_ADDR         is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_CDMA].ulGUCBBPTrigCFGReg       );
    vos_printf("\r\nThe DBG_TRIG_C1_CONFIG2_ADDR         is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_CDMA].ulGUCBBPTrigInfoReg      );
    vos_printf("\r\nThe SOC_BBP_CDMA1_BASE_ADDR          is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_0][PS_REG_BBP_TRIG_MODE_CDMA].ulGUCBBPTrigBaseAddr     );

    vos_printf("\r\nThe DBG_TRIG_C2_CONFIG1_ADDR         is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_CDMA].ulGUCBBPTrigCFGReg       );
    vos_printf("\r\nThe DBG_TRIG_C2_CONFIG2_ADDR         is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_CDMA].ulGUCBBPTrigInfoReg      );
    vos_printf("\r\nThe SOC_BBP_CDMA2_BASE_ADDR          is 0x%x",
                    g_stPsRegGUCBBPTrigInfo.stModeTrigInfo[MODEM_ID_1][PS_REG_BBP_TRIG_MODE_CDMA].ulGUCBBPTrigBaseAddr     );
    /*lint +e534*/
}
#endif


VOS_VOID  Reg_MsgProc(MsgBlock *pRcvMsg)
{
    APP_OM_REG_REQ_MSG_STRU            *pstMsg;

    pstMsg = (APP_OM_REG_REQ_MSG_STRU *)pRcvMsg;

    OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_2, pstMsg->ulSenderPid, WUEPS_PID_REG, pstMsg->ulMsgId);

    switch (pstMsg->ulMsgId)
    {
        case ID_APP_OM_REG_START_REQ:
            Reg_CnfMsgProc(pstMsg, ID_APP_OM_REG_START_REQ);
            PsRegRcvAppOmRegStartReq(pRcvMsg);
            break;

        case ID_APP_OM_REG_DIFF_REQ:
            Reg_CnfMsgProc(pstMsg, ID_APP_OM_REG_DIFF_REQ);
            PsRegRcvAppOmRegDiffSetNumReq(pRcvMsg);
            break;

        case ID_APP_OM_REG_STOP_REQ:
            Reg_CnfMsgProc(pstMsg, ID_APP_OM_REG_STOP_REQ);
            PsRegRcvAppOmRegStopReq(pRcvMsg);
            break;

#if (FEATURE_GUC_BBP_TRIG == FEATURE_ON)
        case ID_APP_OM_REGLIST_CFG_REQ:;
            Reg_CnfMsgProc(pstMsg, ID_APP_OM_REGLIST_CFG_REQ);
            PsRegRcvGUCBBPDbgRegSetReq(pRcvMsg);
            break;

        case ID_APP_OM_BBPTRIG_CFG_REQ:
            Reg_CnfMsgProc(pstMsg, ID_APP_OM_BBPTRIG_CFG_REQ);
            PsRegRcvGUCBBPDbgStartReq(pRcvMsg);
            break;
#endif

        default: /* ��Ч����ϢID */
            PS_LOG2(WUEPS_PID_REG, 0, LOG_LEVEL_WARNING, "not expected msg! ulSenderPid<1>,enMsgName<2>",(VOS_INT32)(pRcvMsg->ulSenderPid),(VOS_INT32)(*((VOS_UINT32 *)((VOS_UINT8 *)(pRcvMsg) + VOS_MSG_HEAD_LENGTH))));
            break;
    }

    OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_2);
}

/******************************************************************************
 Prototype      : Reg_CnfMsgProc
 Description    : �Ĵ���������Ϣ�ظ�������
 Input          : pstRcvMsg - ��Ϣ��
                  ulMsgId - ��ϢID

 Output         : VOID
 Return Value   : VOID

 History        : ---
  1.Date        : 2015-6-19
    Author      : h00300778
    Modification: Created function
******************************************************************************/
VOS_VOID Reg_CnfMsgProc(
    APP_OM_REG_REQ_MSG_STRU            *pstRcvMsg,
    VOS_UINT32                          ulMsgId)
{
    APP_OM_REG_CNF_MSG_STRU            *pstCnfMsg;

    pstCnfMsg = (APP_OM_REG_CNF_MSG_STRU *)VOS_AllocMsg(WUEPS_PID_REG, sizeof(APP_OM_REG_CNF_MSG_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstCnfMsg)
    {
        return;
    }

    /* PC��͸����Ϣ�·��Ĳ���ԭ������ */
    pstCnfMsg->usOriginalId = pstRcvMsg->usOriginalId;
    pstCnfMsg->usTerminalId = pstRcvMsg->usTerminalId;
    pstCnfMsg->ulTimeStamp  = pstRcvMsg->ulTimeStamp;
    pstCnfMsg->ulSN         = pstRcvMsg->ulSN;

    /* �����Ϣ���� */
    pstCnfMsg->ulReceiverPid= MSP_PID_DIAG_APP_AGENT;
    pstCnfMsg->ulMsgId      = ulMsgId;
    pstCnfMsg->ulRslt       = VOS_OK;

    /*lint -e534*/
    VOS_SendMsg(WUEPS_PID_REG, pstCnfMsg);
    /*lint +e534*/

    return;
}


VOS_UINT32 WuepsRegPidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    switch( ip )
    {
        case VOS_IP_LOAD_CONFIG:
            if ( VOS_OK != PsRegInit())
            {
                /*lint -e534*/
                vos_printf("WuepsRegPidInit: PsRegInit fail");
                /*lint +e534*/

                return VOS_ERR;
            }

            if ( VOS_OK != VOS_SmCCreate( "REG", 0, VOS_SEMA4_PRIOR | VOS_SEMA4_INVERSION_SAFE, &g_ulRegTransferSem))
            {
                /*lint -e534*/
                vos_printf("WuepsRegPidInit: creat g_ulRegTransferSem Err");
                /*lint +e534*/

                return VOS_ERR;
            }

#if (FEATURE_GUC_BBP_TRIG == FEATURE_ON)
            PsRegGUCBBPInit();
#endif
            break;

        default:
            break;
    }

    return VOS_OK;
}

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

