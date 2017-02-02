
#include "pamom.h"
#include "ombbplog.h"
#include "omprivate.h"
#include "msp_diag_comm.h"
#include "NVIM_Interface.h"
#include "ScInterface.h"
#include "DspInterface.h"
#include "ombbpmaster.h"
#include "omerrorlog.h"
#include "PamOamSpecTaskDef.h"
#include "DrvNvInterface.h"
#include "errorlog.h"
#include "NasNvInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID PS_FILE_ID_PAM_OM_C
/*lint +e767*/

/* wait for the feedback of modem id quereying */
VOS_SEM                                 g_ulPamVosQuereyModemIdSem = VOS_NULL;
VOS_SEM                                 g_ulPamVosQuereyModemIdProtectionSem = VOS_NULL;

/* the result of modem ID */
MODEM_ID_ENUM_UINT16                    g_usPamVosQuereyModemIdResult = MODEM_ID_BUTT;

/* ��¼�յ���Ϣ��Ϣ��buffer����ǰ���� */
OM_RECORD_BUF_STRU g_astRecordInfo[VOS_EXC_DUMP_MEM_NUM_BUTT];

VOS_UINT32                              g_ulCcpuOmFilterFlag;

#if (VOS_WIN32 == VOS_OS_VER)
VOS_UINT32 OM_GetSlice(VOS_VOID)
{
    return VOS_GetTick();
}
#endif
VOS_VOID OM_WriteDspNv(MsgBlock* pMsg)
{
    VOS_UINT32                  usIndex;
    VOS_UINT16                  usCount;
    VOS_UINT16                  usNvId;
    VOS_UINT16                  usNvLen;
    VOS_UINT32                  ulResult;
    DSP_WRITE_NV_STRU           *pstWriteNVMsg;
    DSP_WRITE_NV_CONTEXT_STRU   *pstWrteNvContext;
    VOS_UINT8                   *pucNvData;
    MODEM_ID_ENUM_UINT16        enModemID;

    enModemID = VOS_GetModemIDFromPid(pMsg->ulSenderPid); /*���DCXOȷ��˫���ٵ���*/

    pstWriteNVMsg = (DSP_WRITE_NV_STRU *)pMsg;

    usCount = pstWriteNVMsg->usCount;

    pstWrteNvContext = (DSP_WRITE_NV_CONTEXT_STRU *)(pstWriteNVMsg->aucNVData);

    for ( usIndex = 0; usIndex < usCount; usIndex++ )
    {
        usNvId = pstWrteNvContext->usNvId;

        usNvLen = pstWrteNvContext->usNvLen;

        pucNvData = pstWrteNvContext->aucNVData;

        ulResult = NV_WriteEx(enModemID, usNvId, pucNvData, (VOS_UINT32)usNvLen);

        if ( NV_OK != ulResult )
        {
            PS_LOG2(CCPU_PID_PAM_OM, 0, PS_PRINT_ERROR,
                "OM_WriteDspNv:NV_Write, NV id: ErrCode :", (VOS_INT32)usNvId, (VOS_INT32)ulResult);

            return;
        }

        pstWrteNvContext = (DSP_WRITE_NV_CONTEXT_STRU *)(pstWrteNvContext->aucNVData + usNvLen);
    }

    return;
}

VOS_VOID OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_ENUM_UINT32 enNumber)
{
    VOS_UINT32 *pulBuf;

    if(VOS_EXC_DUMP_MEM_NUM_BUTT <= enNumber)
    {
        return;
    }

    if(VOS_NULL_PTR == g_astRecordInfo[enNumber].pucBuf)
    {
        return;
    }

    if(0 == g_astRecordInfo[enNumber].ulLen)
    {
        return;
    }

    /* ��start���Ѿ�����˼�¼endslice�ĳ��ȣ���˴˴������ĸ��ֽ���дendslice��ֵ */
    pulBuf = (VOS_UINT32*)(g_astRecordInfo[enNumber].pucBuf + g_astRecordInfo[enNumber].ulLen - sizeof(VOS_UINT32));

    *pulBuf = VOS_GetSlice();

    return;
}

VOS_VOID OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_ENUM_UINT32 enNumber, VOS_UINT32 ulSendPid, VOS_UINT32 ulRcvPid, VOS_UINT32 ulMsgName)
{
    OM_RECORD_INFO_STRU     stRecordInfo;

    if(VOS_EXC_DUMP_MEM_NUM_BUTT <= enNumber)
    {
       return;
    }

    if(VOS_NULL_PTR == g_astRecordInfo[enNumber].pucBuf)
    {
       return;
    }

    g_astRecordInfo[enNumber].ulLen %= VOS_TASK_DUMP_INFO_SIZE;

    stRecordInfo.usSendPid      = (VOS_UINT16)ulSendPid;
    stRecordInfo.usRcvPid       = (VOS_UINT16)ulRcvPid;
    stRecordInfo.ulMsgName      = ulMsgName;
    stRecordInfo.ulSliceStart   = VOS_GetSlice();
    stRecordInfo.ulSliceEnd     = 0;

    /*lint -e534*/
    VOS_MemCpy((g_astRecordInfo[enNumber].pucBuf + g_astRecordInfo[enNumber].ulLen),
              &stRecordInfo, sizeof(OM_RECORD_INFO_STRU));
    /*lint +e534*/

    g_astRecordInfo[enNumber].ulLen += sizeof(OM_RECORD_INFO_STRU);

    return;
}



VOS_VOID OM_RecordMemInit(VOS_VOID)
{
   VOS_UINT32 i;

   /*lint -e534*/
   VOS_MemSet(g_astRecordInfo, 0, sizeof(g_astRecordInfo));
   /*lint +e534*/

   /* ����ÿ��ģ���¼��ν�ɲ���Ϣ�Ŀռ� */
   for(i = 0; i < VOS_EXC_DUMP_MEM_NUM_BUTT; i++)
   {
      g_astRecordInfo[i].pucBuf = (VOS_UINT8*)VOS_ExcDumpMemAlloc(i);

      if(VOS_NULL_PTR == g_astRecordInfo[i].pucBuf)
      {
          return;
      }
   }

   return;
}
VOS_UINT32 OM_GetLogPath(VOS_CHAR *pucBuf, VOS_CHAR *pucOldPath, VOS_CHAR *pucUnitaryPath)
{
    NV_PRODUCT_TYPE_FOR_LOG_DIRECTORY   stLogDir;
    VOS_UINT32                          ulRslt;

    /*lint -e534*/
    VOS_MemSet(&stLogDir, 0, sizeof(stLogDir));
    /*lint +e534*/

    ulRslt = NV_Read(en_NV_Item_ProductTypeForLogDirectory, &stLogDir, sizeof(stLogDir));
    if (VOS_OK != ulRslt)
    {
        /* ��NVʧ��,ֱ�ӷ��� */
        return VOS_ERR;
    }

    /*0:MBB V3R3 stick/E5,etc.; 1:V3R3 M2M & V7R2; 2:V9R1 phone; 3:K3V3&V8R1;*/
    if ((1 == stLogDir.usProductType) || (3 == stLogDir.usProductType))
    {
        /*lint -e534*/
        VOS_StrCpy(pucBuf, pucUnitaryPath);
        /*lint +e534*/
    }
    else
    {
        /*lint -e534*/
        VOS_StrCpy(pucBuf, pucOldPath);
        /*lint +e534*/
    }

    return VOS_OK;
}


VOS_VOID PAMOM_DspMsgProc(MsgBlock* pMsg)
{
    VOS_UINT16         usPrimId;
    DSP_ERROR_LOG_STRU *pstMsg;

    usPrimId = *(VOS_UINT16 *)(pMsg->aucValue);

    if (OM_RECORD_DSP_ERRORLOG == usPrimId)
    {
        pstMsg  = (DSP_ERROR_LOG_STRU *)pMsg;

        if(pstMsg->ulTotalLength > OM_ERRORLOG_DSP_LEN_MAX)
        {
            return;
        }

        /*lint -e534*/
        (VOS_VOID)MNTN_RecordErrorLog(pstMsg->ulErrNo, &pstMsg->ulTotalLength, pstMsg->ulTotalLength);
        /*lint +e534*/
    }
    else if ( OM_DSP_DCXO_UPDATE_NV_DATA == usPrimId )
    {
        /*lint -e534*/
        Print(" Start DCXO NV UPDATE!\n");
        /*lint +e534*/

        OM_WriteDspNv(pMsg);
    }
    else
    {
        /* Make  Pclint happy */
        /* blank */
    }

    return;
}


MODEM_ID_ENUM_UINT16 PAMOM_QuereyModemIdFromPid(VOS_UINT32 ulPid)
{
    PAM_VOS_QUEREY_MODEM_ID_STRU    *pstMsg;
    MODEM_ID_ENUM_UINT16             usModemId;

    if ( VOS_NULL == g_ulPamVosQuereyModemIdSem )
    {
        /*lint -e534*/
        Print("PAMOM_QuereyModemIdFromPid: Don't call in init state.\r\n");
        /*lint +e534*/

        return MODEM_ID_BUTT;
    }

    if ( VOS_OK != VOS_SmP(g_ulPamVosQuereyModemIdProtectionSem, 0) )
    {
        return MODEM_ID_BUTT;
    }

    pstMsg = (PAM_VOS_QUEREY_MODEM_ID_STRU *)VOS_AllocMsg(CCPU_PID_PAM_OM,
                            sizeof(PAM_VOS_QUEREY_MODEM_ID_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ������Ϣʧ�� */
    if (VOS_NULL_PTR == pstMsg)
    {
        if ( VOS_OK != VOS_SmV(g_ulPamVosQuereyModemIdProtectionSem) )
        {
            /*blank */
        }

        return MODEM_ID_BUTT;
    }

    pstMsg->ulReceiverPid  = ACPU_PID_PAM_OM;
    pstMsg->usPrimId       = PAM_VOS_QUEREY_MODEM_ID_REQ;
    pstMsg->usModemID      = MODEM_ID_BUTT;
    pstMsg->ulPid          = ulPid;

    (VOS_VOID)VOS_SendMsg(CCPU_PID_PAM_OM, pstMsg);

    if ( VOS_OK != VOS_SmP(g_ulPamVosQuereyModemIdSem, 1000) )
    {
        if ( VOS_OK != VOS_SmV(g_ulPamVosQuereyModemIdProtectionSem) )
        {
            /*blank */
        }

        return MODEM_ID_BUTT;
    }

    usModemId = g_usPamVosQuereyModemIdResult;

    g_usPamVosQuereyModemIdResult = MODEM_ID_BUTT;

    if ( VOS_OK != VOS_SmV(g_ulPamVosQuereyModemIdProtectionSem) )
    {
        /*blank */
    }

    return usModemId;
}


VOS_VOID PAMOM_QueryModemIdMsgProc(MsgBlock* pMsg)
{
    PAM_VOS_QUEREY_MODEM_ID_STRU    *pstMsg;
    PAM_VOS_QUEREY_MODEM_ID_STRU    *pstCnfMsg;
    MODEM_ID_ENUM_UINT16             usModemId;

    pstMsg = (PAM_VOS_QUEREY_MODEM_ID_STRU *)pMsg;

    if (PAM_VOS_QUEREY_MODEM_ID_REQ == pstMsg->usPrimId)
    {
        usModemId = VOS_GetModemIDFromPid(pstMsg->ulPid);

        pstCnfMsg = (PAM_VOS_QUEREY_MODEM_ID_STRU *)VOS_AllocMsg(CCPU_PID_PAM_OM,
                            sizeof(PAM_VOS_QUEREY_MODEM_ID_STRU) - VOS_MSG_HEAD_LENGTH);

        /* ������Ϣʧ�� */
        if (VOS_NULL_PTR == pstCnfMsg)
        {
            return;
        }

        pstCnfMsg->ulReceiverPid  = ACPU_PID_PAM_OM;
        pstCnfMsg->usPrimId       = PAM_VOS_QUEREY_MODEM_ID_CNF;
        pstCnfMsg->usModemID      = usModemId;
        pstCnfMsg->ulPid          = pstMsg->ulPid;

        (VOS_VOID)VOS_SendMsg(CCPU_PID_PAM_OM, pstCnfMsg);
    }
    else if (PAM_VOS_QUEREY_MODEM_ID_CNF == pstMsg->usPrimId)
    {
        g_usPamVosQuereyModemIdResult = pstMsg->usModemID;

        if ( VOS_OK != VOS_SmV(g_ulPamVosQuereyModemIdSem) )
        {
            g_usPamVosQuereyModemIdResult = MODEM_ID_BUTT;
        }
    }
    else
    {
        /* blank */
    }

    return;
}


VOS_VOID PAMOM_CcpuQueryDumpCnfMsgProc(MsgBlock* pMsg)
{
    VOS_UINT16                  usPrimId;

    /* ����Ϣǰ�����ֽ���ȡ��ԭ��ID */
    usPrimId = *(VOS_UINT16*)(pMsg->aucValue);

    if (BBP_QUERY_DUMP_INFO_CNF == usPrimId)
    {
        Om_BbpDumpAddrQueryMsgProc(pMsg);
    }

    return;
}
 VOS_VOID PAMOM_CcpuAcpuPamMsgProc(MsgBlock* pMsg)
 {
    VOS_UINT16                          usPrimId;

    usPrimId = *(VOS_UINT16 *)(pMsg->aucValue);

    if (BBP_QUERY_DUMP_INFO_CNF == usPrimId)
    {
        PAMOM_CcpuQueryDumpCnfMsgProc(pMsg);
    }
    else if (PAM_VOS_QUEREY_MODEM_ID_REQ == usPrimId)
    {
        PAMOM_QueryModemIdMsgProc(pMsg);
    }
    else if (PAM_VOS_QUEREY_MODEM_ID_CNF == usPrimId)
    {
        PAMOM_QueryModemIdMsgProc(pMsg);
    }
    else
    {
        /* blank */
    }

    return;
}
VOS_VOID PAMOM_MsgProc(MsgBlock* pMsg)
{
    if ((DSP_PID_WPHY == pMsg->ulSenderPid)
        || (I0_DSP_PID_GPHY == pMsg->ulSenderPid)
        || (I1_DSP_PID_GPHY == pMsg->ulSenderPid))
    {
        PAMOM_DspMsgProc(pMsg);

        return;
    }

    /* �յ���ѯDRV Dump�ظ���Ϣ */
    if (ACPU_PID_PAM_OM == pMsg->ulSenderPid)
    {
        PAMOM_CcpuAcpuPamMsgProc(pMsg);

        return;
    }

    if (MSP_PID_DIAG_APP_AGENT == pMsg->ulSenderPid)
    {
        Om_CcpuBbpLogConfigMsgProc(pMsg);
    }

    return;
}
VOS_UINT32 PAMOM_PidLoadConfigInit(VOS_VOID)
{
    NAS_NV_SMS_FILTER_CFG_STRU          stSmsFilterCfg;

    /* ����������ź��� */
    if (VOS_OK != VOS_SmBCreate("VQMI", 0, VOS_SEMA4_FIFO, &g_ulPamVosQuereyModemIdSem))
    {
        return VOS_ERR;
    }

    if (VOS_OK != VOS_SmBCreate("VQMP", 1, VOS_SEMA4_FIFO, &g_ulPamVosQuereyModemIdProtectionSem))
    {
        return VOS_ERR;
    }

    if(VOS_OK != OM_BbpMasterInit())
    {
        return VOS_ERR;
    }

    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                           en_NV_Item_Sms_Log_Filter_Cfg,
                          &stSmsFilterCfg,
                           sizeof(NAS_NV_SMS_FILTER_CFG_STRU)))
    {
        stSmsFilterCfg.ucSmsFilterEnableFlg = VOS_FALSE;
    }

    if (VOS_FALSE != stSmsFilterCfg.ucSmsFilterEnableFlg)
    {
        stSmsFilterCfg.ucSmsFilterEnableFlg = VOS_TRUE;
    }

    g_ulCcpuOmFilterFlag = stSmsFilterCfg.ucSmsFilterEnableFlg;

    return VOS_OK;
}
VOS_UINT32 PAMOM_PidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    switch( ip )
    {
        case VOS_IP_LOAD_CONFIG:
            return PAMOM_PidLoadConfigInit();

        case VOS_IP_INITIAL:
            return Om_BbpDumpEdmaInit();

            /* ��ȡ��ɫ��״̬��NAS����ʱ���г�ͻ */
        case VOS_IP_RESTART:
            DRV_LED_STATE_FUNREG(OM_RuningPsStateCheckCb);

            /* ������Ϣ��ѯDUMP��Ϣ */
            if (BBP_DUMP_OK != Om_SendQueryDumpMsg())
            {
                /*lint -e534*/
                LogPrint("PAMOM_PidInit:Send Query Dump info fail!\r\n");
                /*lint +e534*/
            }

            break;

        default:
            break;
    }

    return VOS_OK;
}


VOS_UINT32 PAMOM_FID_Init(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32                          ulRslt;

    switch( ip )
    {
        case VOS_IP_LOAD_CONFIG:
        {
            ulRslt = VOS_RegisterPIDInfo(CCPU_PID_PAM_OM,
                                        (Init_Fun_Type)PAMOM_PidInit,
                                        (Msg_Fun_Type)PAMOM_MsgProc);
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterPIDInfo(WUEPS_PID_AGING,
                                        (Init_Fun_Type)WuepsAgingPidInit,
                                        (Msg_Fun_Type)Aging_MsgProc);
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterPIDInfo(WUEPS_PID_REG,
                                        (Init_Fun_Type)WuepsRegPidInit,
                                        (Msg_Fun_Type)Reg_MsgProc);
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterMsgTaskPrio(CCPU_FID_PAM_OM, VOS_PRIORITY_M5);
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

#if ( VOS_WIN32 != VOS_OS_VER )
            ulRslt = VOS_RegisterSelfTaskPrio(CCPU_FID_PAM_OM,
                                              (VOS_TASK_ENTRY_TYPE)Om_BbpDbgSelfTask,
                                              COMM_BBPDBG_SELFTASK_PRIO, OM_BBP_DBG_TASK_STACK_SIZE);
            if ( VOS_NULL_BYTE == ulRslt )
            {
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterSelfTaskPrio(CCPU_FID_PAM_OM,
                                              (VOS_TASK_ENTRY_TYPE)PsRegTransferTaskEntry,
                                              COMM_NOSIG_TASK_PRIO, OM_BBP_DBG_TASK_STACK_SIZE);
            if ( VOS_NULL_BYTE == ulRslt )
            {
                PS_LOG(CCPU_FID_PAM_OM, 0, PS_PRINT_ERROR,
                    "PAMOM_FID_Init:PsRegTransferTaskEntry failure !\n");

                return VOS_ERR;
            }
#endif

            break;
        }

        default:
            break;
    }
    return VOS_OK;
}



VOS_UINT VOS_ICCError_CB(VOS_UINT ulChanID, VOS_UINT ulEvent, VOS_VOID* pParam)
{
    /*lint -e534*/
    LogPrint2("VOS_ICCError_CB: The Error ICC Channel is %d, and Error Event is %d",
                    (VOS_INT32)ulChanID, (VOS_INT32)ulEvent);
    /*lint +e534*/

    return VOS_OK;
}


VOS_UINT32 VOS_ICC_Init(VOS_VOID)
{
   OM_ICC_UDI_CTRL_STRU                astCCPUICCCtrlTable;

    /*��ʼ�� ICCͨ��*/
    /*lint -e534*/
    VOS_MemSet((&astCCPUICCCtrlTable), 0, sizeof(astCCPUICCCtrlTable));
    /*lint +e534*/

    astCCPUICCCtrlTable.pstICCAttr = (ICC_CHAN_ATTR_S*)VOS_MemAlloc(CCPU_PID_PAM_OM,
                                                              STATIC_MEM_PT,
                                                              sizeof(ICC_CHAN_ATTR_S));
    if(VOS_NULL_PTR == astCCPUICCCtrlTable.pstICCAttr)
    {
        return VOS_ERR;
    }

    astCCPUICCCtrlTable.enICCId               = UDI_ICC_GUOM4;
    astCCPUICCCtrlTable.pstICCAttr->read_cb   = V_ICC_OSAMsg_CB;

    astCCPUICCCtrlTable.pstICCAttr->u32Priority    = OM_ICC_CHANNEL_PRIORITY;  /* ͳһʹ��������ȼ� */
    astCCPUICCCtrlTable.pstICCAttr->u32TimeOut     = OM_ICC_HANDSHAKE_TIME_MAX;
    astCCPUICCCtrlTable.pstICCAttr->u32FIFOInSize  = OSA_ICC_BUFFER_SIZE;
    astCCPUICCCtrlTable.pstICCAttr->u32FIFOOutSize = OSA_ICC_BUFFER_SIZE;
    astCCPUICCCtrlTable.pstICCAttr->enChanMode     = ICC_CHAN_MODE_PACKET;
    astCCPUICCCtrlTable.pstICCAttr->event_cb       = VOS_ICCError_CB;
    astCCPUICCCtrlTable.pstICCAttr->write_cb       = VOS_NULL_PTR;

    if (VOS_ERROR == DRV_ICC_OPEN(astCCPUICCCtrlTable.enICCId, astCCPUICCCtrlTable.pstICCAttr))
    {
        /* ��ʧ��ʱ��¼��ǰICCͨ����Ϣ */
        VOS_ProtectionReboot(OM_APP_ICC_INIT_ERROR, THIS_FILE_ID, __LINE__, VOS_NULL_PTR,0);
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_VOID OM_OSAEvent(VOS_VOID *pData, VOS_UINT32 ulLength)
{
    DIAG_EVENT_IND_STRU                 stEventInd;

    stEventInd.ulModule = DIAG_GEN_MODULE(DIAG_MODEM_0, DIAG_MODE_COMM);
    stEventInd.ulPid    = CCPU_PID_PAM_OM;
    stEventInd.ulEventId= OAM_EVENT_TIMER;
    stEventInd.ulLength = ulLength;
    stEventInd.pData    = pData;

    /*lint -e534*/
    (VOS_VOID)DIAG_EventReport(&stEventInd);
    /*lint +e534*/

    return;
}

#if (FEATURE_ON == FEATURE_HIFI_USE_ICC)
/*****************************************************************************
 Function   : VOS_Hifi_ICC_Init
 Description: the init of the ICC channel of Hifi
 Input      : None
 Return     : ok or error
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_Hifi_ICC_Init(VOS_VOID)
{
   OM_ICC_UDI_CTRL_STRU                astCCPUICCCtrlTable;

    /*��ʼ�� ICCͨ��*/
    /*lint -e534*/
    VOS_MemSet((&astCCPUICCCtrlTable), 0, sizeof(astCCPUICCCtrlTable));
    /*lint +e534*/

    astCCPUICCCtrlTable.pstICCAttr = (ICC_CHAN_ATTR_S*)VOS_MemAlloc(CCPU_PID_PAM_OM,
                                                              STATIC_MEM_PT,
                                                              sizeof(ICC_CHAN_ATTR_S));
    if(VOS_NULL_PTR == astCCPUICCCtrlTable.pstICCAttr)
    {
        return VOS_ERR;
    }

    astCCPUICCCtrlTable.enICCId               = UDI_ICC_CCPU_HIFI_VOS_NORMAL_MSG;
    astCCPUICCCtrlTable.pstICCAttr->read_cb   = V_ICC_OSAHifiMsg_CB;

    astCCPUICCCtrlTable.pstICCAttr->u32Priority    = OM_ICC_CHANNEL_PRIORITY;  /* ͳһʹ��������ȼ� */
    astCCPUICCCtrlTable.pstICCAttr->u32TimeOut     = OM_ICC_HANDSHAKE_TIME_MAX;
    astCCPUICCCtrlTable.pstICCAttr->u32FIFOInSize  = OSA_ICC_BUFFER_SIZE;
    astCCPUICCCtrlTable.pstICCAttr->u32FIFOOutSize = OSA_ICC_BUFFER_SIZE;
    astCCPUICCCtrlTable.pstICCAttr->enChanMode     = ICC_CHAN_MODE_PACKET;
    astCCPUICCCtrlTable.pstICCAttr->event_cb       = VOS_ICCError_CB;
    astCCPUICCCtrlTable.pstICCAttr->write_cb       = VOS_NULL_PTR;

    if (VOS_ERROR == DRV_ICC_OPEN(astCCPUICCCtrlTable.enICCId, astCCPUICCCtrlTable.pstICCAttr))
    {
        /* ��ʧ��ʱ��¼��ǰICCͨ����Ϣ */
        VOS_ProtectionReboot(OM_APP_ICC_INIT_ERROR, THIS_FILE_ID, __LINE__, VOS_NULL_PTR,0);
        return VOS_ERR;
    }

    return VOS_OK;
}
#endif

/*****************************************************************************
 �� �� ��  : PAM_OM_LayerMsgFilter
 ��������  : ����PAM�е�������Ϣ
 �������  : const VOID *pMsg:��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:
                ����VOS_TRUE:  ��ʾ����Ϣ��Ҫ���й���
                ����VOS_FALSE: ��ʾ����Ϣ������й���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��28��
    ��    ��   : zhuli
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 PAM_OM_LayerMsgFilter(
    const VOS_VOID                      *pMsg
)
{
    OM_FILTER_MSG_HEAD_STRU             *pstMsgHead;

    if (VOS_FALSE == g_ulCcpuOmFilterFlag)
    {
        return VOS_FALSE;
    }

    pstMsgHead = (OM_FILTER_MSG_HEAD_STRU*)pMsg;

    /* SIM��Ϣ���� */
    if (((I0_WUEPS_PID_USIM <= pstMsgHead->ulSenderPid)&&(I0_MAPS_PB_PID >= pstMsgHead->ulSenderPid))
        ||((I1_WUEPS_PID_USIM <= pstMsgHead->ulSenderPid)&&(I1_MAPS_PB_PID >= pstMsgHead->ulSenderPid))
        ||((I2_WUEPS_PID_USIM <= pstMsgHead->ulSenderPid)&&(I2_MAPS_PB_PID >= pstMsgHead->ulSenderPid))
       )
    {
        return VOS_TRUE;
    }

    if (((I0_WUEPS_PID_USIM <= pstMsgHead->ulReceiverPid)&&(I0_MAPS_PB_PID >= pstMsgHead->ulReceiverPid))
        ||((I1_WUEPS_PID_USIM <= pstMsgHead->ulReceiverPid)&&(I1_MAPS_PB_PID >= pstMsgHead->ulReceiverPid))
        ||((I2_WUEPS_PID_USIM <= pstMsgHead->ulReceiverPid)&&(I2_MAPS_PB_PID >= pstMsgHead->ulReceiverPid))
       )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

