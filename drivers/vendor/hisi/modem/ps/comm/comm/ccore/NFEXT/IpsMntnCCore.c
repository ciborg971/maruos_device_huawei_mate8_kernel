/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : IpsMntnCCore.c
  �� �� ��   : ����
  ��    ��   : caikai
  ��������   : 2013��7��22��
  ����޸�   :
  ��������   : IPS MNTNģ��ʵ��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��7��22��
    ��    ��   : caikai
    �޸�����   : �����ļ�

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "IpsMntnCCore.h"

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e534*/
#define    THIS_FILE_ID        PS_FILE_ID_IPS_MNTN_CCORE_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
IPS_MNTN_CCORE_TRACE_CONFIG_REQ_STRU          g_stIpsCcoreTraceMsgCfg;     /*TCP/IPЭ��ջ��ά�ɲ�������Ϣ*/
IPS_MNTN_CCORE_INFO_ENTITY                    g_stIpsCcoreMntnInfoEntity;  /*TCP/IPЭ��ջ��ά�ɲ�ʵ��*/

/* �����������ϱ����ڴ� */
VOS_UINT8                                     g_aucIpsCCoreInfo[IPS_CCORE_INFO_LEN] = {0};

TCPIP_LOG_HOOK_FUNC stLogHook           = {IPS_MNTN_CCORE_TCPIP_FixlenLogOutput, IPS_MNTN_CCORE_TCPIP_VarlenLogOutput};
gpfTCPIPInfoOutput  pFnInfoHook         = IPS_MNTN_CCORE_PrintInfoCB;
gpfTCPIPDebugOutput pFnDebugHook        = IPS_MNTN_CCORE_PrintInfoCB;

IPS_MNTN_CCORE_HOOK_MASK_OPS_STRU             g_stIpsCcoreHookMaskOpt[] =
{
    {
        IPS_MNTN_CCORE_IPV4_CAPTRURE_UP_MASK,
        IP_PP4_HOOK_INPUT_ALL_PKT,
        0,
        IPS_MNTN_CCORE_IpLayerUpCapCB,
        (pfRegHook)TCPIP_IP_PP4_Intermediate_Hook_Register,
        (pfUnRegHook)TCPIP_IP_PP4_Intermediate_Hook_UnRegister
    },
    {
        IPS_MNTN_CCORE_IPV4_CAPTRURE_DOWN_MASK,
        IP_PP4_HOOK_OUTPUT_ALL_PKT,
        0,
        IPS_MNTN_CCORE_IpLayerDownCapCB,
        (pfRegHook)TCPIP_IP_PP4_Intermediate_Hook_Register,
        (pfUnRegHook)TCPIP_IP_PP4_Intermediate_Hook_UnRegister
    },
    {
        IPS_MNTN_CCORE_IPV6_CAPTRURE_UP_MASK,
        PP_INPUT_TYPE,
        0,
        IPS_MNTN_CCORE_IpLayerUpCapCB,
        (pfRegHook)TCPIP_IP_PP6_Intermediate_Hook_Register,
        VOS_NULL_PTR
    },
    {
        IPS_MNTN_CCORE_IPV6_CAPTRURE_DOWN_MASK,
        PP_IFOUTPUT_TYPE,
        0,
        IPS_MNTN_CCORE_IpLayerDownCapCB,
        (pfRegHook)TCPIP_IP_PP6_Intermediate_Hook_Register,
        VOS_NULL_PTR
    },
};

VOS_UINT32 g_ulCurrMask = 0; /* ��ǰHook���� */

extern VOS_UINT32 RTOSCK_AdapterInit(VOS_VOID);
extern VOS_UINT32 VISP_InitTCPIPStack(VOS_VOID);

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */

VOS_VOID IPS_MNTN_CCORE_TransMsg
(
    VOS_UINT8                                       *pucTransMsg,
    VOS_UINT32                                       ulTransMsgContentLen,
    TTF_MNTN_MSG_TYPE_ENUM_UINT16                    enMsgName
)
{
    DIAG_TRANS_IND_STRU        *pstTransData;
    MODEM_ID_ENUM_UINT16        enModemId;

    pstTransData                = (DIAG_TRANS_IND_STRU *)pucTransMsg;

    enModemId                   = VOS_GetModemIDFromPid(UEPS_PID_IPS_CCORE);

    /* �����Ϣ */
    pstTransData->ulPid         = UEPS_PID_IPS_CCORE;
    pstTransData->ulMsgId       = enMsgName;
    pstTransData->ulModule      = DIAG_GEN_MODULE(enModemId, DIAG_MODE_COMM);
    pstTransData->ulLength      = ulTransMsgContentLen;
    pstTransData->pData         = pucTransMsg + IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN;

    if ( VOS_OK != DIAG_TransReport((DIAG_TRANS_IND_STRU *)pucTransMsg) )
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_CCORE_TransMsg, ERROR, Call DIAG_TransReport fail!");
    }

    return;
}
VOS_VOID IPS_MNTN_CCORE_SndCfgCnf2Om
(
    VOS_UINT16      usPrimId,
    VOS_UINT16      usTransMsgContentLen,
    VOS_VOID       *pTransMsgContent
)
{
    MsgBlock                *pSendMsg;

    /*���䲢��д��Ϣ*/
    pSendMsg = VOS_AllocMsg(UEPS_PID_IPS_CCORE, usTransMsgContentLen - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pSendMsg)
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                                "Error: IPS_MNTN_CCORE_SndCfgCnf2Om, ERROR, Call VOS_AllocMsg fail!");
        return;
    }

    mdrv_memcpy(pSendMsg, pTransMsgContent, usTransMsgContentLen);

    if ( VOS_OK != VOS_SendMsg(UEPS_PID_IPS_CCORE, pSendMsg) )
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                                "Error: IPS_MNTN_CCORE_SndCfgCnf2Om, ERROR, Call VOS_SendMsg fail!");
    }

    return;
}
VOS_UINT32 IPS_MNTN_CCORE_ChkMntnInfoIsStart(VOS_VOID)
{
    /*�ж϶�ʱ���Ƿ�����*/
    if(IPS_MNTN_CCORE_INFO_REPORT_START == g_stIpsCcoreMntnInfoEntity.enIpsMntnFlag)
    {
        return PS_TRUE;
    }
    else if(IPS_MNTN_CCORE_INFO_REPORT_STOP == g_stIpsCcoreMntnInfoEntity.enIpsMntnFlag)
    {
        return PS_FALSE;
    }
    else
    {
        return PS_FALSE;
    }
}
VOS_UINT32 IPS_MNTN_CCORE_StartRelTimer
(
    HTIMER                         *phTm,
    VOS_PID                         Pid,
    VOS_UINT32                      ulLength,
    VOS_UINT32                      ulName,
    VOS_UINT32                      ulParam,
    VOS_UINT8                       ucMode,
    VOS_TIMER_PRECISION_ENUM_UINT32 enPrecision
)
{
    VOS_UINT32      ulErrCode;

    /*=============*/   /*��ʱ���Ѿ�����������������*/
    if (VOS_NULL_PTR != *phTm)
    {
        ulErrCode = VOS_RestartRelTimer(phTm);

        if ( VOS_OK != ulErrCode )
        {
            TTF_LOG1(UEPS_PID_IPS_CCORE, PS_SUBMOD_NULL, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_CCORE_StartRelTimer, ERROR, Call VOS_RestartRelTimer fail!\
                ulErrCode:<1>", (VOS_INT32)ulErrCode);
            return PS_FAIL;
        }
    }
    /*=============*/   /*��ʱ��δ��������������ʱ��*/
    else
    {
        ulErrCode = VOS_StartRelTimer(phTm, Pid, ulLength, ulName, ulParam, ucMode, enPrecision);

        if ( VOS_OK != ulErrCode )
        {
            TTF_LOG1(UEPS_PID_IPS_CCORE, PS_SUBMOD_NULL, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_CCORE_StartRelTimer, ERROR, Call VOS_StartRelTimer fail!\
                 ulErrCode:<1>", (VOS_INT32)ulErrCode);
            return PS_FAIL;
        }
    }

    return PS_SUCC;
}


VOS_VOID IPS_MNTN_CCORE_StopMntnInfoTimer(VOS_VOID)
{
    VOS_UINT32  ulErrCode;
    /*�ж϶�ʱ��ָ���Ƿ�Ϊ��*/
    if ( VOS_NULL_PTR != g_stIpsCcoreMntnInfoEntity.hIpsMntnTimer )
    {
        /*�����Ϊ�գ���ֹͣ��ʱ��*/
        ulErrCode = VOS_StopRelTimer(&g_stIpsCcoreMntnInfoEntity.hIpsMntnTimer);

        if ( VOS_OK != ulErrCode )
        {
            g_stIpsCcoreMntnInfoEntity.hIpsMntnTimer = VOS_NULL_PTR;

            TTF_LOG1(UEPS_PID_IPS_CCORE, PS_SUBMOD_NULL, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_CCORE_StopMntnInfoTimer, ERROR, Call VOS_StopRelTimer \
                fail! ulErrCode:<1>", (VOS_INT32)ulErrCode);
        }
    }
}


VOS_UINT32 IPS_MNTN_CCORE_GetPktLenByTraceCfg
(
    IPS_MNTN_CCORE_TRACE_CONFIG_STRU     *pstTraceCfg,
    VOS_UINT16                            usPktLen,
    VOS_UINT32                           *pulDataLen
)
{
    *pulDataLen    =   0;

    /*�ж϶�ʱ���Ƿ�����*/
    switch ( pstTraceCfg->ulChoice )
    {
        case IPS_MNTN_CCORE_TRACE_NULL_CHOSEN:
            return PS_FALSE;
        case IPS_MNTN_CCORE_TRACE_MSG_HEADER_CHOSEN:
            break;
        case IPS_MNTN_CCORE_TRACE_CONFIGURABLE_LEN_CHOSEN:
            *pulDataLen = TTF_MIN(pstTraceCfg->ulTraceDataLen, usPktLen);
            break;
        case IPS_MNTN_CCORE_TRACE_WHOLE_DATA_LEN_CHOSEN:
            *pulDataLen = usPktLen;
            break;
        default:
            return PS_FALSE;
    }

    return PS_TRUE;
}
VOS_VOID IPS_MNTN_CCORE_BridgePktInfo
(
    VOS_UINT8                                   *pucSrcPort,
    VOS_UINT8                                   *pucDestPort,
    VOS_UINT8                                   *pucPktData,
    VOS_UINT16                                   usPktLen,
    TTF_MNTN_MSG_TYPE_ENUM_UINT16                usType
)
{
    VOS_UINT8                                *pucTraceData;
    IPS_MNTN_CCORE_TRACE_CONFIG_STRU         *pstTraceCfg;
    IPS_MNTN_CCORE_BRIDGE_PKT_INFO_STRU      *pstTraceMsg;
    VOS_UINT32                                ulTransDataLen;
    VOS_UINT32                                ulDataLen;
    VOS_UINT32                                ulRst;

    ulTransDataLen  =   0;
    ulDataLen       =   0;

    if ( VOS_NULL_PTR == pucPktData )
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_CCORE_BridgePktInfo, ERROR, paucPktData is NULL ");
        return;
    }

    /*������Ϣ����ѡ���Ӧ������Ϣ*/
    if(ID_IPS_CCORE_TRACE_BRIDGE_DATA_INFO == usType)
    {
        pstTraceCfg = &(g_stIpsCcoreTraceMsgCfg.stBridgeTraceCfg);
    }
    else
    {
        /*��ӡ������Ϣ,��Ϣ���Ͳ�ƥ��*/
        TTF_LOG( UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_CCORE_BridgePktInfo : ERROR : usType is not Expectes!" );
        return;
    }

    /*������Ϣ������Ϣ����ȡ������ĳ���*/
    ulRst = IPS_MNTN_CCORE_GetPktLenByTraceCfg(pstTraceCfg, usPktLen, &ulDataLen);
    if(PS_FALSE == ulRst)
    {
        /*������ñ���*/
        return;
    }

    ulDataLen           = PS_MIN(IPS_MNTN_CCORE_TRACE_MAX_BYTE_LEN, ulDataLen);
    ulTransDataLen      = (IPS_CCORE_BRIDGE_PKT_INFO_OFFSET_LEN + ulDataLen);

    pucTraceData        = PS_MEM_ALLOC(UEPS_PID_IPS_CCORE, ulTransDataLen + IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN);
    if (VOS_NULL_PTR == pucTraceData)
    {
        /*��ӡ������Ϣ,�����ڴ�ʧ��*/
        TTF_LOG( UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_CCORE_BridgePktInfo : ERROR : alloc mem failed!" );

        return;
    }

    /*����͸����Ϣ*/
    pstTraceMsg             = (IPS_MNTN_CCORE_BRIDGE_PKT_INFO_STRU *)(pucTraceData + IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN);
    pstTraceMsg->usLen      = usPktLen;
    pstTraceMsg->usPrimId   = usType;
    PS_MEM_CPY(pstTraceMsg->aucSrcPort, pucSrcPort, IPS_CCORE_END_NAME);
    PS_MEM_CPY(pstTraceMsg->aucDestPort, pucDestPort, IPS_CCORE_END_NAME);

    /*lint -e669 */
    PS_MEM_CPY(pstTraceMsg->aucData, pucPktData, ulDataLen);
    /*lint +e669 */

    IPS_MNTN_CCORE_TransMsg(pucTraceData, ulTransDataLen, usType);

    PS_MEM_FREE(UEPS_PID_IPS_CCORE, pucTraceData);
}

/*****************************************************************************
 �� �� ��  : IPS_MNTN_CCORE_BridgePktInfoCB
 ��������  : ����������ת���Ļص�����
 �������  : pstIpsMntnCapturePara  �ص����������ṹ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��1��
    ��    ��   : caikai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_BridgePktInfoCB
(
    IPS_MNTN_CCORE_CAPTURE_PARA_STRU *pstIpsMntnCapturePara
)
{
    VOS_UINT8                                   *pucSrcPort;
    VOS_UINT8                                   *pucDestPort;
    VOS_UINT8                                   *pucPktData;
    VOS_UINT16                                   usPktLen;

    if ( VOS_NULL_PTR == pstIpsMntnCapturePara )
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_CCORE_BridgePktInfoCB, ERROR, pstIpsMntnCapturePara is NULL ");
        return;
    }

    pucSrcPort      = pstIpsMntnCapturePara->paucSrcPort;
    pucDestPort     = pstIpsMntnCapturePara->paucDestPort;
    pucPktData      = pstIpsMntnCapturePara->pucData;
    usPktLen        = pstIpsMntnCapturePara->usLen;

    IPS_MNTN_CCORE_BridgePktInfo(pucSrcPort, pucDestPort, pucPktData, usPktLen, ID_IPS_CCORE_TRACE_BRIDGE_DATA_INFO);

    return;
}


VOS_VOID IPS_MNTN_CCORE_CtrlPktInfo
(
    VOS_UINT8                                     *pucNetIfName,
    VOS_UINT8                                     *pucPktData,
    VOS_UINT16                                     usPktLen,
    TTF_MNTN_MSG_TYPE_ENUM_UINT16                  usType
)
{
    VOS_UINT8                                *pucTraceData;
    IPS_MNTN_CCORE_PKT_INFO_STRU             *pstTraceMsg;
    VOS_UINT32                                ulTransDataLen;
    VOS_UINT32                                ulDataLen;

    ulTransDataLen  =   0;
    ulDataLen       =   0;

    if ( VOS_NULL_PTR == pucPktData )
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_CCORE_CtrlPktInfo, ERROR, pucPktData is NULL ");
        return;
    }

    ulDataLen           = PS_MIN(IPS_MNTN_CCORE_TRACE_MAX_BYTE_LEN, usPktLen);
    ulTransDataLen      = (IPS_CCORE_PKT_INFO_OFFSET_LEN + ulDataLen);

    pucTraceData        = PS_MEM_ALLOC(UEPS_PID_IPS_CCORE, ulTransDataLen + IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN);
    if (VOS_NULL_PTR == pucTraceData)
    {
        /*��ӡ������Ϣ,�����ڴ�ʧ��*/
        TTF_LOG( UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_CCORE_CtrlPktInfo : ERROR : alloc mem failed!" );

        return;
    }

    /*����͸����Ϣ*/
    pstTraceMsg             = (IPS_MNTN_CCORE_PKT_INFO_STRU *)(pucTraceData + IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN);
    pstTraceMsg->usLen      = usPktLen;
    pstTraceMsg->usPrimId   = usType;
    PS_MEM_CPY(pstTraceMsg->aucNetIfName, pucNetIfName, IPS_CCORE_IFNAMSIZ);
    /*lint -e669 */
    PS_MEM_CPY(pstTraceMsg->aucData, pucPktData, ulDataLen);
    /*lint +e669 */

    IPS_MNTN_CCORE_TransMsg(pucTraceData, ulTransDataLen, usType);

    PS_MEM_FREE(UEPS_PID_IPS_CCORE, pucTraceData);
}

/*****************************************************************************
 �� �� ��  : IPS_MNTN_CCORE_ArpRecvPktInfoCB
 ��������  : ����TCP/IPЭ��ջ���յ�ARP���Ʊ��Ļص�����
 �������  : pstIpsMntnCapturePara  �ص����������ṹ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��1��
    ��    ��   : caikai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_ArpRecvPktInfoCB
(
    IPS_MNTN_CCORE_CAPTURE_PARA_STRU *pstIpsMntnCapturePara
)
{
    VOS_UINT8                                    *pucNetIfName;
    VOS_UINT8                                    *pucPktData;
    VOS_UINT16                                    usPktLen;

    if ( VOS_NULL_PTR == pstIpsMntnCapturePara )
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_CCORE_ArpRecvPktInfoCB, ERROR, pstIpsMntnCapturePara is NULL ");
        return;
    }

    pucNetIfName    = pstIpsMntnCapturePara->paucNetIfName;
    pucPktData      = pstIpsMntnCapturePara->pucData;
    usPktLen        = pstIpsMntnCapturePara->usLen;

    IPS_MNTN_CCORE_CtrlPktInfo(pucNetIfName, pucPktData, usPktLen, ID_IPS_CCORE_TRACE_RECV_ARP_PKT);

    return;
}

/*****************************************************************************
 �� �� ��  : IPS_MNTN_CCORE_ArpSendPktInfoCB
 ��������  : ����TCP/IPЭ��ջ���͵�ARP���Ʊ��Ļص�����
 �������  : pstIpsMntnCapturePara  �ص����������ṹ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��1��
    ��    ��   : caikai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_ArpSendPktInfoCB
(
    IPS_MNTN_CCORE_CAPTURE_PARA_STRU *pstIpsMntnCapturePara
)
{
    VOS_UINT8                                    *pucNetIfName;
    VOS_UINT8                                    *pucPktData;
    VOS_UINT16                                    usPktLen;

    if ( VOS_NULL_PTR == pstIpsMntnCapturePara )
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_CCORE_ArpSendPktInfoCB, ERROR, pstIpsMntnCapturePara is NULL ");
        return;
    }

    pucNetIfName    = pstIpsMntnCapturePara->paucNetIfName;
    pucPktData      = pstIpsMntnCapturePara->pucData;
    usPktLen        = pstIpsMntnCapturePara->usLen;

    IPS_MNTN_CCORE_CtrlPktInfo(pucNetIfName, pucPktData, usPktLen, ID_IPS_CCORE_TRACE_SEND_ARP_PKT);

    return;
}

/*****************************************************************************
 �� �� ��  : IPS_MNTN_CCORE_DhcpcRecvPktInfoCB
 ��������  : ����TCP/IPЭ��ջ���յ�DHCP���Ʊ��Ļص�����
 �������  : pstIpsMntnCapturePara  �ص����������ṹ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��1��
    ��    ��   : caikai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_DhcpcRecvPktInfoCB
(
    IPS_MNTN_CCORE_CAPTURE_PARA_STRU *pstIpsMntnCapturePara
)
{
    VOS_UINT8                                    *pucNetIfName;
    VOS_UINT8                                    *pucPktData;
    VOS_UINT16                                    usPktLen;

    if ( VOS_NULL_PTR == pstIpsMntnCapturePara )
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_CCORE_DhcpcRecvPktInfoCB, ERROR, pstIpsMntnCapturePara is NULL ");
        return;
    }

    pucNetIfName    = pstIpsMntnCapturePara->paucNetIfName;
    pucPktData      = pstIpsMntnCapturePara->pucData;
    usPktLen        = pstIpsMntnCapturePara->usLen;

    IPS_MNTN_CCORE_CtrlPktInfo(pucNetIfName, pucPktData, usPktLen, ID_IPS_CCORE_TRACE_RECV_DHCPC_PKT);

    return;
}

/*****************************************************************************
 �� �� ��  : IPS_MNTN_CCORE_DhcpcSendPktInfoCB
 ��������  : ����TCP/IPЭ��ջ���͵�DHCP���Ʊ��Ļص�����
 �������  : pstIpsMntnCapturePara  �ص����������ṹ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��1��
    ��    ��   : caikai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_DhcpcSendPktInfoCB
(
    IPS_MNTN_CCORE_CAPTURE_PARA_STRU *pstIpsMntnCapturePara
)
{
    VOS_UINT8                                    *pucNetIfName;
    VOS_UINT8                                    *pucPktData;
    VOS_UINT16                                    usPktLen;

    if ( VOS_NULL_PTR == pstIpsMntnCapturePara )
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_CCORE_DhcpcSendPktInfoCB, ERROR, pstIpsMntnCapturePara is NULL ");
        return;
    }

    pucNetIfName    = pstIpsMntnCapturePara->paucNetIfName;
    pucPktData      = pstIpsMntnCapturePara->pucData;
    usPktLen        = pstIpsMntnCapturePara->usLen;

    IPS_MNTN_CCORE_CtrlPktInfo(pucNetIfName, pucPktData, usPktLen, ID_IPS_CCORE_TRACE_SEND_DHCPC_PKT);

    return;
}

/*****************************************************************************
 �� �� ��  : IPS_MNTN_CCORE_DhcpsRecvktInfoCB
 ��������  : ����TCP/IPЭ��ջ���յ�DHCPS���Ʊ��Ļص�����
 �������  : pstIpsMntnCapturePara  �ص����������ṹ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��1��
    ��    ��   : caikai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_DhcpsRecvPktInfoCB
(
    IPS_MNTN_CCORE_CAPTURE_PARA_STRU *pstIpsMntnCapturePara
)
{
    VOS_UINT8                                    *pucNetIfName;
    VOS_UINT8                                    *pucPktData;
    VOS_UINT16                                    usPktLen;

    if ( VOS_NULL_PTR == pstIpsMntnCapturePara )
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_CCORE_DhcpsRecvktInfoCB, ERROR, pstIpsMntnCapturePara is NULL ");
        return;
    }

    pucNetIfName    = pstIpsMntnCapturePara->paucNetIfName;
    pucPktData      = pstIpsMntnCapturePara->pucData;
    usPktLen        = pstIpsMntnCapturePara->usLen;

    IPS_MNTN_CCORE_CtrlPktInfo(pucNetIfName, pucPktData, usPktLen, ID_IPS_CCORE_TRACE_RECV_DHCPS_PKT);

    return;
}

/*****************************************************************************
 �� �� ��  : IPS_MNTN_CCORE_DhcpsSendPktInfoCB
 ��������  : ����TCP/IPЭ��ջ���͵�DHCPS���Ʊ��Ļص�����
 �������  : pstIpsMntnCapturePara  �ص����������ṹ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��1��
    ��    ��   : caikai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_DhcpsSendPktInfoCB
(
    IPS_MNTN_CCORE_CAPTURE_PARA_STRU *pstIpsMntnCapturePara
)
{
    VOS_UINT8                                    *pucNetIfName;
    VOS_UINT8                                    *pucPktData;
    VOS_UINT16                                    usPktLen;

    if ( VOS_NULL_PTR == pstIpsMntnCapturePara )
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_CCORE_DhcpsSendPktInfoCB, ERROR, pstIpsMntnCapturePara is NULL ");
        return;
    }

    pucNetIfName    = pstIpsMntnCapturePara->paucNetIfName;
    pucPktData      = pstIpsMntnCapturePara->pucData;
    usPktLen        = pstIpsMntnCapturePara->usLen;

    IPS_MNTN_CCORE_CtrlPktInfo(pucNetIfName, pucPktData, usPktLen, ID_IPS_CCORE_TRACE_SEND_DHCPS_PKT);

    return;
}


VOS_VOID IPS_MNTN_CCORE_AppCmdInfo
(
    VOS_UINT8                                    *pucData,
    VOS_UINT16                                    usCmdLen,
    TTF_MNTN_MSG_TYPE_ENUM_UINT16                 usType
)
{
    VOS_UINT8                                *pucTraceData;
    IPS_MNTN_CCORE_APP_CMD_INFO_STRU         *pstTraceMsg;
    VOS_UINT32                                ulTransDataLen;
    VOS_UINT32                                ulDataLen;

    ulTransDataLen  =   0;
    ulDataLen       =   0;

    if ( VOS_NULL_PTR == pucData )
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_CCORE_AppCmdInfo, ERROR, pucData is NULL ");
        return;
    }

    ulDataLen           = PS_MIN(IPS_CCORE_APP_CMD_INFO_LEN, usCmdLen);
    ulTransDataLen      = (IPS_CCORE_APP_CMD_INFO_OFFSET_LEN + ulDataLen);

    pucTraceData        = PS_MEM_ALLOC(UEPS_PID_IPS_CCORE, ulTransDataLen + IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN);
    if (VOS_NULL_PTR == pucTraceData)
    {
        /*��ӡ������Ϣ,�����ڴ�ʧ��*/
        TTF_LOG( UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_CCORE_AppCmdInfo : ERROR : alloc mem failed!" );

        return;
    }

    /*����͸����Ϣ*/
    pstTraceMsg             = (IPS_MNTN_CCORE_APP_CMD_INFO_STRU *)(pucTraceData + IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN);
    pstTraceMsg->usLen      = usCmdLen;
    pstTraceMsg->usPrimId   = usType;
    /*lint -e669 */
    PS_MEM_CPY(pstTraceMsg->aucData, pucData, ulDataLen);
    /*lint +e669 */

    IPS_MNTN_CCORE_TransMsg(pucTraceData, ulTransDataLen, usType);

    PS_MEM_FREE(UEPS_PID_IPS_CCORE, pucTraceData);
}

/*****************************************************************************
 �� �� ��  : IPS_MNTN_CCORE_AppCmdInfoCB
 ��������  : ����APP��������ص�����
 �������  : pstIpsMntnCapturePara  �ص����������ṹ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��1��
    ��    ��   : caikai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_AppCmdInfoCB
(
    IPS_MNTN_CCORE_CAPTURE_PARA_STRU *pstIpsMntnCapturePara
)
{
    VOS_UINT8                              *pucData;
    VOS_UINT16                              usCmdLen;

    if ( VOS_NULL_PTR == pstIpsMntnCapturePara )
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_CCORE_AppCmdInfoCB, ERROR, pstIpsMntnCapturePara is NULL ");
        return;
    }

    pucData         = pstIpsMntnCapturePara->pucData;
    usCmdLen        = pstIpsMntnCapturePara->usLen;

    IPS_MNTN_CCORE_AppCmdInfo(pucData, usCmdLen, ID_IPS_CCORE_TRACE_APP_CMD);

    return;
}


/*****************************************************************************
 �� �� ��  : IPS_MNTN_CCORE_PrintInfoCB
 ��������  : �ṩ��VISP�����ά�ɲ���Ϣ�ص��ӿ�
 �������  : VOS_UINT8                              *pucData;
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��1��
    ��    ��   : caikai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_PrintInfoCB
(
    VOS_CHAR                               *pucData
)
{
    VOS_UINT16                              usCmdLen;

    if ( VOS_NULL_PTR == pucData )
    {
        return;
    }

    usCmdLen        = (VOS_UINT16)VOS_StrLen(pucData);

    IPS_MNTN_CCORE_AppCmdInfo((VOS_UINT8 *)pucData, usCmdLen, ID_IPS_CCORE_TRACE_APP_CMD);

    return;
}


VOID IPS_MNTN_CCORE_TCPIP_FixlenLogOutput(ULONG ulLogCode, ULONG ulLogLevel, ULONG ulLogType, VOID *ucMessage,
                        ULONG ulPara1, ULONG ulPara2, ULONG ulPara3, ULONG ulPara4)
{
    VOS_CHAR                    aucInfoPrint[IPS_CCORE_APP_CMD_INFO_LEN];
    VOS_UINT32                  ulPos;

    if ( VOS_NULL_PTR == ucMessage )
    {
        return;
    }

    /* ucMessage���ܹ��� */
    if ((IPS_CCORE_APP_CMD_INFO_LEN >> 1) < VOS_StrLen((VOS_CHAR *)ucMessage))
    {
        return;
    }

    memset(aucInfoPrint, 0, IPS_CCORE_APP_CMD_INFO_LEN);

    switch (ulLogType) {
        case LOG_TYPE_CFG:
        case LOG_TYPE_WARNING:
        case LOG_TYPE_RUN:
            VOS_sprintf((char *)aucInfoPrint, "LogCode:%d,type:%d,level:%d | ",
                                    ulLogCode, ulLogType, ulLogLevel);

            ulPos = VOS_StrLen((VOS_CHAR *)aucInfoPrint);
            VOS_sprintf((char *)&aucInfoPrint[ulPos], (VOS_CHAR *)ucMessage,
                                    ulPara1, ulPara2, ulPara3, ulPara4);
            break;

        default:
            return;
    }

    IPS_MNTN_CCORE_PrintInfoCB(aucInfoPrint);

    return;
}
VOID IPS_MNTN_CCORE_TCPIP_VarlenLogOutput(ULONG ulLogCode, ULONG ulLogLevel,
                        ULONG ulLogType, VOID* pcFormat, VOID* pData)
{
    VOS_CHAR                    aucInfoPrint[IPS_CCORE_APP_CMD_INFO_LEN];
    VOS_UINT32                  ulPos;

    if (( VOS_NULL_PTR == pcFormat ) || ( VOS_NULL_PTR == pData ))
    {
        return;
    }

    /* ucMessage���ܹ��� */
    if ((IPS_CCORE_APP_CMD_INFO_LEN >> 1) < (VOS_StrLen((VOS_CHAR *)pcFormat) + VOS_StrLen((VOS_CHAR *)pData)))
    {
        return;
    }

    memset(aucInfoPrint, 0, IPS_CCORE_APP_CMD_INFO_LEN);

    switch (ulLogType) {
        case LOG_TYPE_CFG:
        case LOG_TYPE_WARNING:
        case LOG_TYPE_RUN:
            VOS_sprintf((char *)aucInfoPrint, "LogCode:%d,type:%d,level:%d | ",
                                    ulLogCode, ulLogType, ulLogLevel);
            ulPos = VOS_StrLen((VOS_CHAR *)aucInfoPrint);
            VOS_sprintf((char *)&aucInfoPrint[ulPos], (VOS_CHAR *)pcFormat, (VOS_CHAR *)pData);
            break;

        default:
            return;
    }

    IPS_MNTN_CCORE_PrintInfoCB(aucInfoPrint);

    return;
}
PS_BOOL_ENUM_UINT8  IPS_MNTN_CCORE_BridgeTraceCfgChkParam(IPS_MNTN_CCORE_TRACE_CONFIG_REQ_STRU *pRcvMsg)
{
    if ( (IPS_MNTN_CCORE_TRACE_NULL_CHOSEN !=pRcvMsg->stBridgeTraceCfg.ulChoice)
        && (IPS_MNTN_CCORE_TRACE_MSG_HEADER_CHOSEN !=pRcvMsg->stBridgeTraceCfg.ulChoice)
        && (IPS_MNTN_CCORE_TRACE_CONFIGURABLE_LEN_CHOSEN !=pRcvMsg->stBridgeTraceCfg.ulChoice)
        && (IPS_MNTN_CCORE_TRACE_WHOLE_DATA_LEN_CHOSEN !=pRcvMsg->stBridgeTraceCfg.ulChoice) )
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}


PS_BOOL_ENUM_UINT8  IPS_MNTN_CCORE_TraceCfgChkParam(IPS_MNTN_CCORE_TRACE_CONFIG_REQ_STRU *pRcvMsg)
{
    if ( (IPS_MNTN_CCORE_TRACE_NULL_CHOSEN != pRcvMsg->stInputTraceCfg.ulChoice)
        && (IPS_MNTN_CCORE_TRACE_MSG_HEADER_CHOSEN != pRcvMsg->stInputTraceCfg.ulChoice)
        && (IPS_MNTN_CCORE_TRACE_CONFIGURABLE_LEN_CHOSEN != pRcvMsg->stInputTraceCfg.ulChoice)
        && (IPS_MNTN_CCORE_TRACE_WHOLE_DATA_LEN_CHOSEN != pRcvMsg->stInputTraceCfg.ulChoice) )
    {
        return PS_FALSE;
    }

    if ( (IPS_MNTN_CCORE_TRACE_NULL_CHOSEN != pRcvMsg->stOutputTraceCfg.ulChoice)
        && (IPS_MNTN_CCORE_TRACE_MSG_HEADER_CHOSEN != pRcvMsg->stOutputTraceCfg.ulChoice)
        && (IPS_MNTN_CCORE_TRACE_CONFIGURABLE_LEN_CHOSEN != pRcvMsg->stOutputTraceCfg.ulChoice)
        && (IPS_MNTN_CCORE_TRACE_WHOLE_DATA_LEN_CHOSEN != pRcvMsg->stOutputTraceCfg.ulChoice) )
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}


PS_BOOL_ENUM_UINT8  IPS_MNTN_CCORE_TraceAdvancedCfgChkParam(IPS_MNTN_CCORE_TRACE_CONFIG_REQ_STRU *pRcvMsg)
{
    /*TCP/IPЭ��ջ���Ĺ������ò������*/
    if(PS_FALSE == IPS_MNTN_CCORE_TraceCfgChkParam(pRcvMsg))
    {
        return PS_FALSE;
    }

    /*������ת���Ĺ������ò������*/
    if(PS_FALSE == IPS_MNTN_CCORE_BridgeTraceCfgChkParam(pRcvMsg))
    {
        return  PS_FALSE;
    }

    return PS_TRUE;

}


VOS_VOID IPS_MNTN_CCORE_OutputRouteIpv4Info(VOS_UINT8 *pucData, VOS_UINT16 usType)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulWaitList;
    VOS_UINT32                          ulRtNumReturn;
    VOS_UINT32                          ulLen;
    VOS_UINT8                          *pucTransMsg;
    VOS_UINT16                          usPrimId = ID_IPS_CCORE_TRACE_MNTN_INFO;

    /* �򿪻�ȡ·�ɱ����waitlist��� */
    ulRet = TCPIP_OpenFibTable((UINTPTR *)&ulWaitList);
    if ( FIB4_OK != ulRet )
    {
        TTF_LOG1(UEPS_PID_IPS_CCORE, 0, PS_PRINT_ERROR,
                "VISP, OpenFibTable Failed!!!", (VOS_INT32)ulRet);
        return;
    }

    ulRtNumReturn   =   0;
    pucTransMsg     =   pucData + IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN;

    ulRet = TCPIP_GetFibEntry(ulWaitList,
        IPS_MNTN_CCORE_MAX_IPV4_ROUTE_ITEM,
        (TCPIP_RT4_ENTRY_S *)(pucTransMsg + IPS_MNTN_CCORE_BASE_INFO_OFFSET_LEN),
        (ULONG *)&ulRtNumReturn);
    if ( FIB4_OK != ulRet )
    {
        TTF_LOG1(UEPS_PID_IPS_CCORE, 0, PS_PRINT_ERROR,
                "VISP, GetFibEntry Failed!!!", (VOS_INT32)ulWaitList);

        TCPIP_CloseFibTable(ulWaitList);

        return;
    }

    if ( ulRtNumReturn > IPS_MNTN_CCORE_MAX_IPV4_ROUTE_ITEM )
    {
        TTF_LOG1(UEPS_PID_IPS_CCORE, 0, PS_PRINT_ERROR,
                "VISP, Get Route Item Too Large!!!", (VOS_INT32)ulRtNumReturn);
        ulRtNumReturn = IPS_MNTN_CCORE_MAX_IPV4_ROUTE_ITEM;
    }

    TCPIP_CloseFibTable(ulWaitList);

    /* �������� */
    PS_MEM_CPY(pucTransMsg, &usPrimId, sizeof(usPrimId));

    /* SDT���߽���ʱ���Ͳ���4�ֽ� */
    pucTransMsg += sizeof(VOS_UINT32);

    /* �������� */
    PS_MEM_CPY(pucTransMsg, &usType, sizeof(usType));

    /* SDT���߽���ʱ���Ͳ���4�ֽ� */
    pucTransMsg += sizeof(VOS_UINT32);

    /* ���볤�� */
    ulLen = sizeof(TCPIP_RT4_ENTRY_S) * ulRtNumReturn;
    PS_MEM_CPY(pucTransMsg, &ulLen, sizeof(ulLen));

    IPS_MNTN_CCORE_TransMsg(pucData,
        ulLen + IPS_MNTN_CCORE_BASE_INFO_OFFSET_LEN, ID_IPS_CCORE_TRACE_MNTN_INFO);

    return;
}


VOS_VOID IPS_MNTN_CCORE_OutputUdpInfo(VOS_UINT8 *pucData, VOS_UINT16 usType)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulWaitList;
    VOS_UINT32                          ulLen;
    VOS_UINT8                          *pucTransMsg;
    VOS_UINT16                          usPrimId = ID_IPS_CCORE_TRACE_MNTN_INFO;

    ulRet = TCPIP_OpenUdpNetInfo((UINTPTR *)&ulWaitList);
    if ( VOS_OK != ulRet )
    {
        TTF_LOG1(UEPS_PID_IPS_CCORE, 0, PS_PRINT_ERROR,
                "VISP, OpenUdpNetInfo Failed!!!", (VOS_INT32)ulRet);
        return;
    }

    pucTransMsg     =   pucData + IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN;

    /* �������� */
    PS_MEM_CPY(pucTransMsg, &usPrimId, sizeof(usPrimId));

    /* SDT���߽���ʱ���Ͳ���4�ֽ� */
    pucTransMsg += sizeof(VOS_UINT32);

    /* �������� */
    PS_MEM_CPY(pucTransMsg, &usType, sizeof(usType));

    /* SDT���߽���ʱ���Ͳ���4�ֽ� */
    pucTransMsg += sizeof(VOS_UINT32);

    /* ���볤�� */
    ulLen = sizeof(TCPIP_UDPNETINFO_S);
    PS_MEM_CPY(pucTransMsg, &ulLen, sizeof(ulLen));
    pucTransMsg += sizeof(VOS_UINT32);

    ulRet = TCPIP_GetUdpNetInfo(ulWaitList, (TCPIP_UDPNETINFO_S *)pucTransMsg);
    if ( VOS_OK != ulRet )
    {
        TTF_LOG1(UEPS_PID_IPS_CCORE, 0, PS_PRINT_ERROR,
                "VISP, GetUdpNetInfo Failed!!!", (VOS_INT32)ulRet);

        (VOS_VOID)TCPIP_CloseUdpNetInfo(ulWaitList);
        return;
    }

    (VOS_VOID)TCPIP_CloseUdpNetInfo(ulWaitList);

    IPS_MNTN_CCORE_TransMsg(pucData,
        ulLen + IPS_MNTN_CCORE_BASE_INFO_OFFSET_LEN, ID_IPS_CCORE_TRACE_MNTN_INFO);

    return;
}
VOS_VOID IPS_MNTN_CCORE_OutputTcpInfo(VOS_UINT8 *pucData, VOS_UINT16 usType)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulWaitList;
    VOS_UINT32                          ulLen;
    VOS_UINT8                          *pucTransMsg;
    VOS_UINT16                          usPrimId = ID_IPS_CCORE_TRACE_MNTN_INFO;

    ulRet = TCPIP_OpenTcpNetInfo((UINTPTR *)&ulWaitList);
    if ( VOS_OK != ulRet )
    {
        TTF_LOG1(UEPS_PID_IPS_CCORE, 0, PS_PRINT_ERROR,
                "VISP, OpenTcpNetInfo Failed!!!", (VOS_INT32)ulRet);
        return;
    }

    pucTransMsg     =   pucData + IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN;

    /* �������� */
    PS_MEM_CPY(pucTransMsg, &usPrimId, sizeof(usPrimId));

    /* SDT���߽���ʱ���Ͳ���4�ֽ� */
    pucTransMsg += sizeof(VOS_UINT32);

    /* �������� */
    PS_MEM_CPY(pucTransMsg, &usType, sizeof(usType));

    /* SDT���߽���ʱ���Ͳ���4�ֽ� */
    pucTransMsg += sizeof(VOS_UINT32);

    /* ���볤�� */
    ulLen = sizeof(TCPIP_TCPNETINFO_S);
    PS_MEM_CPY(pucTransMsg, &ulLen, sizeof(ulLen));
    pucTransMsg += sizeof(ulLen);

    ulRet = TCPIP_GetTcpNetInfo(ulWaitList, (TCPIP_TCPNETINFO_S *)pucTransMsg);
    if ( TCP_FILTOK != ulRet )
    {
        TTF_LOG1(UEPS_PID_IPS_CCORE, 0, PS_PRINT_ERROR,
                "VISP, GetTcpNetInfo Failed!!!", (VOS_INT32)ulRet);

        TCPIP_CloseTcpNetInfo(ulWaitList);
        return;
    }

    TCPIP_CloseTcpNetInfo(ulWaitList);

    IPS_MNTN_CCORE_TransMsg(pucData,
        ulLen + IPS_MNTN_CCORE_BASE_INFO_OFFSET_LEN, ID_IPS_CCORE_TRACE_MNTN_INFO);

    return;
}
VOS_VOID IPS_MNTN_CCORE_OutputNetIfInfo(VOS_UINT8 *pucData, VOS_UINT16 usType)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulWaitList;
    VOS_UINT32                          ulLen;
    VOS_UINT8                          *pucTransMsg;
    VOS_UINT16                          usPrimId = ID_IPS_CCORE_TRACE_MNTN_INFO;

    ulRet = TCPIP_OpenIfConfigEntry((UINTPTR *)&ulWaitList);
    if ( VRP_IFNET_NOERR != ulRet )
    {
        TTF_LOG1(UEPS_PID_IPS_CCORE, 0, PS_PRINT_ERROR,
                "VISP, OpenIfConfigEntry Failed!!!", (VOS_INT32)ulRet);
        return;
    }

    pucTransMsg     =   pucData + IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN;

    /* �������� */
    PS_MEM_CPY(pucTransMsg, &usPrimId, sizeof(usPrimId));

    /* SDT���߽���ʱ���Ͳ���4�ֽ� */
    pucTransMsg += sizeof(VOS_UINT32);

    /* �������� */
    PS_MEM_CPY(pucTransMsg, &usPrimId, sizeof(usPrimId));

    /* SDT���߽���ʱ���Ͳ���4�ֽ� */
    pucTransMsg += sizeof(VOS_UINT32);

    /* �������� */
    PS_MEM_CPY(pucTransMsg, &usType, sizeof(usType));

    /* SDT���߽���ʱ���Ͳ���4�ֽ� */
    pucTransMsg += sizeof(VOS_UINT32);

    /* ���볤�� */
    ulLen = sizeof(TCPIP_IFNET_S);
    PS_MEM_CPY(pucTransMsg, &ulLen, sizeof(ulLen));
    pucTransMsg += sizeof(ulLen);

    ulRet = TCPIP_GetIfConfigEntry(ulWaitList, (TCPIP_IFNET_S *)pucTransMsg);
    if ( VRP_IFNET_NOERR != ulRet )
    {
        TTF_LOG1(UEPS_PID_IPS_CCORE, 0, PS_PRINT_ERROR,
                "VISP, GetIfConfigEntry Failed!!!", (VOS_INT32)ulRet);

        TCPIP_CloseIfConfigEntry(ulWaitList);
        return;
    }

    TCPIP_CloseIfConfigEntry(ulWaitList);

    IPS_MNTN_CCORE_TransMsg(pucData,
        ulLen + IPS_MNTN_CCORE_BASE_INFO_OFFSET_LEN, ID_IPS_CCORE_TRACE_MNTN_INFO);

    return;
}
VOS_VOID IPS_MNTN_CCORE_OutputIpv4AddrInfo(VOS_UINT8 *pucData, VOS_UINT16 usType)
{
    VOS_UINT32                          ulWaitlist;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulIfIndex;
    VOS_UINT32                          ulLen;
    VOS_UINT32                          ulIndex;
    TCPIP_IPIFADDR_S                    stAddrInfo;
    VOS_UINT8                          *pucTransMsg;
    VOS_UINT8                          *pucDataHead;
    IMS_NIC_ENTITY_STRU                *pstImsNicEntity;
    VOS_UINT16                          usPrimId = ID_IPS_CCORE_TRACE_MNTN_INFO;

    pstImsNicEntity = IMS_NIC_GET_ENTITY_STRU(IMS_NIC_MODEM_ID_0);

    ulIfIndex       = pstImsNicEntity->ulIfIndex;
    PS_MEM_SET(&stAddrInfo, 0, sizeof(stAddrInfo));

    ulRet = TCPIP_OpenAddrTable((UINTPTR *)&ulWaitlist, ulIfIndex);
    if ( ERR_AM4_OK != ulRet )
    {
        TTF_LOG1(UEPS_PID_IPS_CCORE, 0, PS_PRINT_ERROR,
                "VISP, OpenAddrTable Failed!!!", (VOS_INT32)ulRet);
        return;
    }

    pucTransMsg     =   pucData + IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN + IPS_MNTN_CCORE_BASE_INFO_OFFSET_LEN;
    pucDataHead     =   pucData + IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN;

    ulRet = TCPIP_GetAddrTable(ulWaitlist, &stAddrInfo, ulIfIndex);
    if ( ERR_AM4_OK != ulRet )
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                "VISP, GetAddrTable Failed!!!");

        TCPIP_CloseAddrTable(ulWaitlist);
        return;
    }

    ulIndex = 0;
    while ( (ERR_AM4_END != ulRet) && (ulIndex < IPS_MNTN_CCORE_MAX_IPV4_ADDR_NUM) )
    {
        PS_MEM_CPY(pucTransMsg, &stAddrInfo, sizeof(stAddrInfo));
        ulRet = TCPIP_GetAddrTable(ulWaitlist, &stAddrInfo, ulIfIndex);
        ulIndex++;
    }

    TCPIP_CloseAddrTable(ulWaitlist);

    /* �������� */
    PS_MEM_CPY(pucDataHead, &usPrimId, sizeof(usPrimId));

    /* SDT���߽���ʱ���Ͳ���4�ֽ� */
    pucDataHead += sizeof(VOS_UINT32);

    /* �������� */
    PS_MEM_CPY(pucDataHead, &usType, sizeof(usType));

    /* SDT���߽���ʱ���Ͳ���4�ֽ� */
    pucDataHead += sizeof(VOS_UINT32);

    /* ���볤�� */
    ulLen = ulIndex * sizeof(stAddrInfo);
    PS_MEM_CPY(pucDataHead, &ulLen, sizeof(ulLen));

    IPS_MNTN_CCORE_TransMsg(pucData,
        ulLen + IPS_MNTN_CCORE_BASE_INFO_OFFSET_LEN, ID_IPS_CCORE_TRACE_MNTN_INFO);

    return;
}
VOS_VOID IPS_MNTN_CCORE_IpsMntnInfoTimeoutProc(VOS_VOID)
{
    VOS_UINT8                          *pucTraceData;

    g_stIpsCcoreMntnInfoEntity.enIpsMntnFlag = IPS_MNTN_CCORE_INFO_REPORT_STOP;

    /* Ϊģ��ʵ��ָ���ڴ� */
    pucTraceData    = g_aucIpsCCoreInfo;

    /* �������������Ϣ */
    IPS_MNTN_CCORE_OutputNetIfInfo(pucTraceData, ID_IPS_MNTN_CCORE_NETIF_INFO);

    /* ���TCP����״̬��Ϣ */
    IPS_MNTN_CCORE_OutputTcpInfo(pucTraceData, ID_IPS_MNTN_CCORE_TCP_INFO);

    /* ���UDP����״̬��Ϣ */
    IPS_MNTN_CCORE_OutputUdpInfo(pucTraceData, ID_IPS_MNTN_CCORE_UDP_INFO);

    /* ���IPV4·�ɱ���Ϣ */
    IPS_MNTN_CCORE_OutputRouteIpv4Info(pucTraceData, ID_IPS_MNTN_CCORE_IPV4_ROUTE_INFO);

    /* ���IPV4��ַ����Ϣ */
    IPS_MNTN_CCORE_OutputIpv4AddrInfo(pucTraceData, ID_IPS_MNTN_CCORE_IPV4_ADDR_INFO);

    /* ���IMS��������ͳ����Ϣ */
    IPS_MNTN_CCORE_OutputImsNicStatsInfo(pucTraceData, ID_IPS_MNTN_CCORE_IMS_NIC_INFO);

    /*������ά�ɲⶨʱ��*/
    if (PS_SUCC != IPS_MNTN_CCORE_StartRelTimer(&(g_stIpsCcoreMntnInfoEntity.hIpsMntnTimer), UEPS_PID_IPS_CCORE,
                    g_stIpsCcoreMntnInfoEntity.ulIpsMntnTimerLen, IPS_MNTN_CCORE_INFO_TIMER, 0,
                    VOS_RELTIMER_NOLOOP, VOS_TIMER_NO_PRECISION))
    {
        /*������ʱ��ʧ�ܣ���ֹͣ��ʱ����ע����ģ��*/
        IPS_MNTN_CCORE_StopMntnInfoTimer();
        g_stIpsCcoreMntnInfoEntity.enIpsMntnFlag = IPS_MNTN_CCORE_INFO_REPORT_STOP;
    }
    else
    {
        g_stIpsCcoreMntnInfoEntity.enIpsMntnFlag = IPS_MNTN_CCORE_INFO_REPORT_START;
    }

    return;
}
VOS_VOID IPS_MNTN_CCORE_PktInfo
(
    VOS_UINT8                                    *pucPktData,
    VOS_UINT16                                    usPktLen,
    TTF_MNTN_MSG_TYPE_ENUM_UINT16                 usType
)
{
    VOS_UINT8                          *pucTraceData;
    IPS_MNTN_CCORE_TRACE_CONFIG_STRU   *pstTraceCfg;
    IPS_MNTN_CCORE_PKT_INFO_STRU       *pstTraceMsg;
    VOS_UINT32                          ulTransDataLen;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulRst;


    /* ��ָ�����ⲿ�Ѿ��жϹ� */
    ulTransDataLen  =   0;
    ulDataLen       =   0;

    /*������Ϣ����ѡ���Ӧ������Ϣ*/
    if(ID_IPS_CCORE_TRACE_INPUT_DATA_INFO == usType)
    {
        pstTraceCfg = &(g_stIpsCcoreTraceMsgCfg.stInputTraceCfg);
    }
    else if(ID_IPS_CCORE_TRACE_OUTPUT_DATA_INFO == usType)
    {
        pstTraceCfg = &(g_stIpsCcoreTraceMsgCfg.stOutputTraceCfg);
    }
    else
    {
        /*��ӡ������Ϣ,��Ϣ���Ͳ�ƥ��*/
        TTF_LOG( UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_CCORE_PktInfo : ERROR : usType is not Expectes!" );
        return;
    }

    /*������Ϣ������Ϣ����ȡ������ĳ���*/
    ulRst = IPS_MNTN_CCORE_GetPktLenByTraceCfg(pstTraceCfg, usPktLen, &ulDataLen);
    if(PS_FALSE == ulRst)
    {
        /*������ñ���*/
        return;
    }

    ulDataLen           = PS_MIN(IPS_MNTN_CCORE_TRACE_MAX_BYTE_LEN, ulDataLen);
    ulTransDataLen      = IPS_CCORE_PKT_INFO_OFFSET_LEN + IMS_NIC_ETH_HDR_SIZE + ulDataLen;

    pucTraceData        = PS_MEM_ALLOC(UEPS_PID_IPS_CCORE, ulTransDataLen + IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN);
    if (VOS_NULL_PTR == pucTraceData)
    {
        /*��ӡ������Ϣ,�����ڴ�ʧ��*/
        TTF_LOG( UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_CCORE_PktInfo : ERROR : alloc mem failed!" );

        return;
    }

    /*����͸����Ϣ*/
    pstTraceMsg             = (IPS_MNTN_CCORE_PKT_INFO_STRU *)(pucTraceData + IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN);
    pstTraceMsg->usLen      = usPktLen + IMS_NIC_ETH_HDR_SIZE;
    pstTraceMsg->usPrimId   = usType;
    PS_MEM_CPY(pstTraceMsg->aucNetIfName, IMS_NIC_GET_NIC_NAME, IPS_CCORE_IFNAMSIZ);

    /*lint -e416 */
    ulRst = MBUF_CopyDataFromMBufToBuffer((MBUF_S *)pucPktData, 0, ulDataLen,
        (pstTraceMsg->aucData + IMS_NIC_ETH_HDR_SIZE));
    /*lint +e416 */

    if ( VOS_OK != ulRst )
    {
        /*��ӡ������Ϣ,��MBUF��������ʧ��*/
        TTF_LOG1(UEPS_PID_IPS_CCORE, 0, PS_PRINT_ERROR,
                "IPS, CopyDataFromMBufToBuffer failed!", (VOS_INT32)ulRst);

        PS_MEM_FREE(UEPS_PID_IPS_CCORE, pucTraceData);

        return;
    }

    IPS_MNTN_CCORE_TransMsg(pucTraceData, ulTransDataLen, usType);

    PS_MEM_FREE(UEPS_PID_IPS_CCORE, pucTraceData);

    return;
}


VOS_UINT32 IPS_MNTN_CCORE_IpLayerUpCapCB(MBUF_S *pMBuf)
{
    VOS_UINT16                          usPktLen;

    if ( VOS_NULL_PTR == pMBuf )
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "Link layer capture input data is NULL!!!");
        return PS_FAIL;
    }

    usPktLen        = (VOS_UINT16)pMBuf->ulTotalDataLength;

    IPS_MNTN_CCORE_PktInfo((VOS_UINT8 *)pMBuf, usPktLen, ID_IPS_CCORE_TRACE_INPUT_DATA_INFO);

    return PS_SUCC;
}


VOS_UINT32 IPS_MNTN_CCORE_IpLayerDownCapCB(MBUF_S *pMBuf)
{
    VOS_UINT16                          usPktLen;


    if ( VOS_NULL_PTR == pMBuf )
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "Link layer capture output data is NULL!!!");
        return PS_FAIL;
    }

    usPktLen        = (VOS_UINT16)pMBuf->ulTotalDataLength;

    IPS_MNTN_CCORE_PktInfo((VOS_UINT8 *)pMBuf, usPktLen, ID_IPS_CCORE_TRACE_OUTPUT_DATA_INFO);

    return PS_SUCC;
}


VOS_VOID IPS_MNTN_CCORE_UnregHooks(VOS_UINT32 ulMask)
{
    VOS_UINT32                          ulIndex;


    for ( ulIndex = 0; ulIndex < IPS_ARRAY_SIZE(g_stIpsCcoreHookMaskOpt); ulIndex++ )
    {
        if ( (g_stIpsCcoreHookMaskOpt[ulIndex].ulMask
            == (ulMask & g_stIpsCcoreHookMaskOpt[ulIndex].ulMask))
            && (VOS_NULL_PTR != g_stIpsCcoreHookMaskOpt[ulIndex].pfUnRegHookFunc) )
        {
            /*ж�ع��Ӻ���*/
            (VOS_VOID)g_stIpsCcoreHookMaskOpt[ulIndex].pfUnRegHookFunc(g_stIpsCcoreHookMaskOpt[ulIndex].ulType,
                g_stIpsCcoreHookMaskOpt[ulIndex].pfHookCbFunc);

            /* ������Ӧ������λ */
            g_ulCurrMask &= ~g_stIpsCcoreHookMaskOpt[ulIndex].ulMask;
        }
    }

    return;
}


VOS_UINT32 IPS_MNTN_CCORE_RegHooks(VOS_UINT32 ulMask)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulIndex;


    for ( ulIndex = 0; ulIndex < IPS_ARRAY_SIZE(g_stIpsCcoreHookMaskOpt); ulIndex++ )
    {
        if ( (g_stIpsCcoreHookMaskOpt[ulIndex].ulMask
            != (ulMask & g_stIpsCcoreHookMaskOpt[ulIndex].ulMask))
            || (VOS_NULL_PTR == g_stIpsCcoreHookMaskOpt[ulIndex].pfRegHookFunc) )
        {
            continue;
        }

        /* �Ѿ�ע����Ĳ����ظ�ע�� */
        if ( 0 == (g_stIpsCcoreHookMaskOpt[ulIndex].ulMask & g_ulCurrMask) )
        {
            /*ע����Ӧ�Ĺ��Ӻ���*/
            ulRet = g_stIpsCcoreHookMaskOpt[ulIndex].pfRegHookFunc(g_stIpsCcoreHookMaskOpt[ulIndex].ulType,
                g_stIpsCcoreHookMaskOpt[ulIndex].ulPriority, g_stIpsCcoreHookMaskOpt[ulIndex].pfHookCbFunc);
            if ( PS_SUCC != ulRet )
            {
                TTF_LOG1(UEPS_PID_IPS_CCORE, PS_SUBMOD_NULL, PS_PRINT_ERROR,
                    "Reg Fail!!!ulErrCode:<1>", (VOS_INT32)ulRet);

                /*����һ��ע��ʧ����ж�ص�ǰ�����Ѿ�ע���ϵĹ��Ӻ���*/
                IPS_MNTN_CCORE_UnregHooks(g_ulCurrMask);
                return ulRet;
            }

            g_ulCurrMask |= g_stIpsCcoreHookMaskOpt[ulIndex].ulMask;
        }
    }

    return PS_SUCC;
}
VOS_UINT32 IPS_MNTN_CCORE_ReRegHooks(VOS_UINT32 ulMask)
{
    VOS_UINT32                          ulRet;


    /*����ע��ǰ��ж�ص�ǰ���еĹ��Ӻ���*/
    if ( 0 != g_ulCurrMask )
    {
        IPS_MNTN_CCORE_UnregHooks(g_ulCurrMask);
    }

    ulRet = IPS_MNTN_CCORE_RegHooks(ulMask);

    return ulRet;
}
PS_BOOL_ENUM_UINT8 IPS_MNTN_CCORE_SetCallbackFunc(IPS_MNTN_CCORE_TRACE_CONFIG_REQ_STRU *pstTraceCfgReq)
{
    VOS_UINT32                          ulMask = 0;
    VOS_UINT32                          ulRet;


    if ( (pstTraceCfgReq->stBridgeTraceCfg.ulChoice > IPS_MNTN_CCORE_TRACE_NULL_CHOSEN)
        && (pstTraceCfgReq->stBridgeTraceCfg.ulChoice <= IPS_MNTN_CCORE_TRACE_WHOLE_DATA_LEN_CHOSEN) )
    {
        ulMask |= IPS_MNTN_CCORE_IPV4_CAPTRURE_UP_MASK;
        ulMask |= IPS_MNTN_CCORE_IPV4_CAPTRURE_DOWN_MASK;
        ulMask |= IPS_MNTN_CCORE_IPV6_CAPTRURE_UP_MASK;
        ulMask |= IPS_MNTN_CCORE_IPV6_CAPTRURE_DOWN_MASK;
    }
    else
    {
        if ( (pstTraceCfgReq->stInputTraceCfg.ulChoice > IPS_MNTN_CCORE_TRACE_NULL_CHOSEN)
            && (pstTraceCfgReq->stInputTraceCfg.ulChoice <= IPS_MNTN_CCORE_TRACE_WHOLE_DATA_LEN_CHOSEN) )
        {
            ulMask |= IPS_MNTN_CCORE_IPV4_CAPTRURE_UP_MASK;
            ulMask |= IPS_MNTN_CCORE_IPV6_CAPTRURE_UP_MASK;
        }

        if ( (pstTraceCfgReq->stOutputTraceCfg.ulChoice > IPS_MNTN_CCORE_TRACE_NULL_CHOSEN)
            && (pstTraceCfgReq->stOutputTraceCfg.ulChoice <= IPS_MNTN_CCORE_TRACE_WHOLE_DATA_LEN_CHOSEN) )
        {
            ulMask |= IPS_MNTN_CCORE_IPV4_CAPTRURE_DOWN_MASK;
            ulMask |= IPS_MNTN_CCORE_IPV6_CAPTRURE_DOWN_MASK;
        }
    }

    ulRet = IPS_MNTN_CCORE_ReRegHooks(ulMask);
    if ( PS_SUCC != ulRet )
    {
        TTF_LOG1(UEPS_PID_IPS_CCORE, PS_SUBMOD_NULL, PS_PRINT_ERROR,
            "RegHooks Fail!!!ulErrCode:<1>", (VOS_INT32)ulRet);
        return PS_FALSE;
    }

    return PS_TRUE;
}



VOS_VOID IPS_MNTN_CCORE_TraceAdvancedCfgReq(VOS_VOID *pMsg)
{
    PS_BOOL_ENUM_UINT8                            enResult;

    OM_IPS_CCORE_ADVANCED_TRACE_CONFIG_REQ_STRU   *pRcvMsg;
    IPS_CCORE_OM_ADVANCED_TRACE_CONFIG_CNF_STRU   stIpsCcoreTraceCfgCnf;

    pRcvMsg = (OM_IPS_CCORE_ADVANCED_TRACE_CONFIG_REQ_STRU *)pMsg;

    /* Fill DIAG trans msg header */
    stIpsCcoreTraceCfgCnf.stDiagHdr.ulSenderCpuId   = VOS_LOCAL_CPUID;
    stIpsCcoreTraceCfgCnf.stDiagHdr.ulSenderPid     = UEPS_PID_IPS_CCORE;
    stIpsCcoreTraceCfgCnf.stDiagHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    stIpsCcoreTraceCfgCnf.stDiagHdr.ulReceiverPid   = MSP_PID_DIAG_APP_AGENT ;   /* ��Ӧ����Ϣ���͸�DIAG����DIAG��͸������Ĵ��������͸�HIDS����*/
    stIpsCcoreTraceCfgCnf.stDiagHdr.ulLength = sizeof(IPS_CCORE_OM_ADVANCED_TRACE_CONFIG_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    stIpsCcoreTraceCfgCnf.stDiagHdr.ulMsgId = ID_IPS_CCORE_OM_ADVANCED_TRACE_CONFIG_CNF;

    /* DIAG͸�������е��ض���Ϣ*/
    stIpsCcoreTraceCfgCnf.stDiagHdr.usOriginalId  = pRcvMsg->stDiagHdr.usOriginalId;
    stIpsCcoreTraceCfgCnf.stDiagHdr.usTerminalId  = pRcvMsg->stDiagHdr.usTerminalId;
    stIpsCcoreTraceCfgCnf.stDiagHdr.ulTimeStamp   = pRcvMsg->stDiagHdr.ulTimeStamp;
    stIpsCcoreTraceCfgCnf.stDiagHdr.ulSN          = pRcvMsg->stDiagHdr.ulSN;

    /*������ò����Ƿ�Ϸ�*/
    enResult = IPS_MNTN_CCORE_TraceAdvancedCfgChkParam(&(pRcvMsg->stIpsCcoreCfgReq));

    if ( PS_FALSE == enResult )
    {
        /*���������ⲻ�Ϸ�����OM�ظ�����ʧ��*/
        stIpsCcoreTraceCfgCnf.stIpsCcoreCfgCnf.enRslt = PS_FAIL;

        IPS_MNTN_CCORE_SndCfgCnf2Om(ID_IPS_CCORE_OM_ADVANCED_TRACE_CONFIG_CNF,
            sizeof(stIpsCcoreTraceCfgCnf),&stIpsCcoreTraceCfgCnf);

        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "Warning: IPS_MNTN_CCORE_TraceAdvancedCfgReq check fail");

        return;
    }

    enResult = IPS_MNTN_CCORE_SetCallbackFunc(&(pRcvMsg->stIpsCcoreCfgReq));
    if( PS_FALSE == enResult )
    {
        /*���������ⲻ�Ϸ�����OM�ظ�����ʧ��*/
        stIpsCcoreTraceCfgCnf.stIpsCcoreCfgCnf.enRslt = PS_FAIL;

        IPS_MNTN_CCORE_SndCfgCnf2Om(ID_IPS_CCORE_OM_ADVANCED_TRACE_CONFIG_CNF,
            sizeof(stIpsCcoreTraceCfgCnf),&stIpsCcoreTraceCfgCnf);

        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
            "Warning: IPS_MNTN_CCORE_SetCallbackFunc fail");

        return;
    }

    /*�������ò���*/
    mdrv_memcpy(&g_stIpsCcoreTraceMsgCfg, &(pRcvMsg->stIpsCcoreCfgReq), sizeof(IPS_MNTN_CCORE_TRACE_CONFIG_REQ_STRU));

    if (WTTF_TRACE_MSG_YES == g_stIpsCcoreTraceMsgCfg.stVispLogConfig.enVISPLogOutConfig)
    {
        (VOS_VOID)TCPIP_SetLogType(1,1,1);

        (VOS_VOID)TCPIP_SetLogLevel(g_stIpsCcoreTraceMsgCfg.stVispLogConfig.enVISPRunLogLevelConfig);

        /* SOCKET */
        (VOS_VOID)TCPIP_DebugSockAll();

        /* TCP */
        (VOS_VOID)TCPIP_DebugTCPAll();

        /* UDP */
        (VOS_VOID)TCPIP_DebugUDPAll();

        /* ICMP */
        (VOS_VOID)TCPIP_SetIcmpDebugFlag(1);

        /* PP4 */
        (VOS_VOID)TCPIP_SetPP4DebugFlag(1,0,0,0,1,1);

        /* TCP6 */
        (VOS_VOID)TCP6_DebugSwitch(1);

        /* UDP6 */
        (VOS_VOID)UDP6_DebugSwitch(1);

        /* ICMP6 */
        (VOS_VOID)ICMP6_DebugSwitch(1);

        /* PP6 */
        (VOS_VOID)TCPIP_SetPP6DebugFlag(1,1);

        /* IPSEC */
        (VOS_VOID)TCPIP_IPSEC_SetDebug(1,2);
    }
    else
    {
        /* SOCKET */
        (VOS_VOID)TCPIP_NoDebugSockAll();

        /* TCP */
        (VOS_VOID)TCPIP_NoDebugTCPAll();

        /* UDP */
        (VOS_VOID)TCPIP_NoDebugUDPAll();

        /* ICMP */
        (VOS_VOID)TCPIP_SetIcmpDebugFlag(0);

        /* PP4 */
        (VOS_VOID)TCPIP_SetPP4DebugFlag(0,0,0,0,0,0);

        /* TCP6 */
        (VOS_VOID)TCP6_DebugSwitch(0);

        /* UDP6 */
        (VOS_VOID)UDP6_DebugSwitch(0);

        /* ICMP6 */
        (VOS_VOID)ICMP6_DebugSwitch(0);

        /* PP6 */
        (VOS_VOID)TCPIP_SetPP6DebugFlag(0,0);

        /* IPSEC */
        (VOS_VOID)TCPIP_IPSEC_SetDebug(0,0);

        (VOS_VOID)TCPIP_SetLogType(0,0,0);
    }

    /*��OM�ظ����óɹ�*/
    stIpsCcoreTraceCfgCnf.stIpsCcoreCfgCnf.enRslt = PS_SUCC;

    IPS_MNTN_CCORE_SndCfgCnf2Om(ID_IPS_CCORE_OM_ADVANCED_TRACE_CONFIG_CNF,
            sizeof(stIpsCcoreTraceCfgCnf),&stIpsCcoreTraceCfgCnf);

    return;
}


VOS_UINT32 IPS_MNTN_CCORE_RcvIpsMntnInfoCfgReq(VOS_VOID *pMsg)
{
    OM_IPS_CCORE_MNTN_INFO_CONFIG_REQ_STRU  *pRcvMsg;
    IPS_CCORE_OM_MNTN_INFO_CONFIG_CNF_STRU  stIpsCcoreMntnCfgCnf;
    IPS_MNTN_CCORE_RESULT_TYPE_ENUM_UINT32  enResult;
    VOS_UINT32                              ulIpsMntnTimerLen;

    pRcvMsg = (OM_IPS_CCORE_MNTN_INFO_CONFIG_REQ_STRU *)pMsg;

    enResult            = IPS_MNTN_CCORE_RESULT_OK;

    /*��������TCP/IPЭ��ջ������Ϣ*/
    if( IPS_MNTN_CCORE_INFO_REPORT_START == pRcvMsg->stIpsCcoreMntnCfgReq.enCommand )
    {
        /*��Ⲷ��TCP/IPЭ��ջ������Ϣ�����Ƿ���������*/
        if(PS_FALSE == IPS_MNTN_CCORE_ChkMntnInfoIsStart())
        {
            /*���ö�ʱ��ʱ����Ĭ��Ϊ1000����*/
            ulIpsMntnTimerLen = 1000 * pRcvMsg->stIpsCcoreMntnCfgReq.usTimeLen;

            if (PS_SUCC != IPS_MNTN_CCORE_StartRelTimer(&(g_stIpsCcoreMntnInfoEntity.hIpsMntnTimer), UEPS_PID_IPS_CCORE,
                    ulIpsMntnTimerLen, IPS_MNTN_CCORE_INFO_TIMER, 0,
                    VOS_RELTIMER_NOLOOP, VOS_TIMER_NO_PRECISION))
            {
                /*������ʱ��ʧ�ܣ���ֹͣ��ʱ����ע����ģ��*/
                IPS_MNTN_CCORE_StopMntnInfoTimer();
                enResult = IPS_MNTN_CCORE_RESULT_START_TIMER_FAIL;

                g_stIpsCcoreMntnInfoEntity.enIpsMntnFlag = IPS_MNTN_CCORE_INFO_REPORT_STOP;
            }
            else
            {
                g_stIpsCcoreMntnInfoEntity.ulIpsMntnTimerLen = ulIpsMntnTimerLen;
                g_stIpsCcoreMntnInfoEntity.enIpsMntnFlag     = IPS_MNTN_CCORE_INFO_REPORT_START;
            }
        }
    }
    /*ֹͣ����TCP/IPЭ��ջ������Ϣ*/
    else if( IPS_MNTN_CCORE_INFO_REPORT_STOP == pRcvMsg->stIpsCcoreMntnCfgReq.enCommand )
    {
        /*��Ⲷ��TCP/IPЭ��ջ������Ϣ�����Ƿ���������*/
        if(PS_TRUE == IPS_MNTN_CCORE_ChkMntnInfoIsStart())
        {
            /*�����ģ������������ֹͣ��ʱ����ע����ģ��*/
            IPS_MNTN_CCORE_StopMntnInfoTimer();

            g_stIpsCcoreMntnInfoEntity.enIpsMntnFlag = IPS_MNTN_CCORE_INFO_REPORT_STOP;
        }
    }
    /*================*/    /*OM ����Ĳ�����Ч*/
    else
    {
        enResult = IPS_MNTN_CCORE_RESULT_INPUT_PARAM_ERR;
    }

    /* Fill DIAG trans msg header */
    stIpsCcoreMntnCfgCnf.stDiagHdr.ulSenderCpuId    = VOS_LOCAL_CPUID;
    stIpsCcoreMntnCfgCnf.stDiagHdr.ulSenderPid      = UEPS_PID_IPS_CCORE;
    stIpsCcoreMntnCfgCnf.stDiagHdr.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    stIpsCcoreMntnCfgCnf.stDiagHdr.ulReceiverPid    = MSP_PID_DIAG_APP_AGENT ;   /* ��Ӧ����Ϣ���͸�DIAG����DIAG��͸������Ĵ��������͸�HIDS����*/
    stIpsCcoreMntnCfgCnf.stDiagHdr.ulLength         = sizeof(IPS_CCORE_OM_MNTN_INFO_CONFIG_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    stIpsCcoreMntnCfgCnf.stDiagHdr.ulMsgId          = ID_IPS_CCORE_OM_MNTN_INFO_CONFIG_CNF;

    /* DIAG͸�������е��ض���Ϣ*/
    stIpsCcoreMntnCfgCnf.stDiagHdr.usOriginalId     = pRcvMsg->stDiagHdr.usOriginalId;
    stIpsCcoreMntnCfgCnf.stDiagHdr.usTerminalId     = pRcvMsg->stDiagHdr.usTerminalId;
    stIpsCcoreMntnCfgCnf.stDiagHdr.ulTimeStamp      = pRcvMsg->stDiagHdr.ulTimeStamp;
    stIpsCcoreMntnCfgCnf.stDiagHdr.ulSN             = pRcvMsg->stDiagHdr.ulSN;

    /* ���ȷ����Ϣ */
    stIpsCcoreMntnCfgCnf.stIpsCcoreMntnCfgCnf.enCommand = pRcvMsg->stIpsCcoreMntnCfgReq.enCommand;
    stIpsCcoreMntnCfgCnf.stIpsCcoreMntnCfgCnf.enRslt    = enResult;

    /* ����OM͸����Ϣ */
    IPS_MNTN_CCORE_SndCfgCnf2Om(ID_IPS_CCORE_OM_MNTN_INFO_CONFIG_CNF,
            sizeof(stIpsCcoreMntnCfgCnf),&stIpsCcoreMntnCfgCnf);

    return PS_SUCC;
}

/*****************************************************************************
 �� �� ��  : IPS_MNTN_CCORE_OutputImsNicStatsInfo
 ��������  : �������������������ͳ����Ϣ
 �������  : pucData    -- �����ڴ�
             usType     -- ��ά�ɲ���Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��16��
    ��    ��   : caikai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID IPS_MNTN_CCORE_OutputImsNicStatsInfo
(
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usType
)
{
    VOS_UINT32                          ulDataLen;
    VOS_UINT8                          *pucTransMsg;
    VOS_UINT32                          ulResult;

    ulDataLen       =   0;
    pucTransMsg     =   pucData + sizeof(VOS_UINT32);

    /* �������� */
    PS_MEM_CPY(pucData, &usType, sizeof(usType));

    /* SDT���߽���ʱ���Ͳ���4�ֽ� */
    pucData += sizeof(VOS_UINT32);

    /* ��ȡIMS����������ͳ����Ϣ */
    ulResult    = IMS_NIC_GetMntnInfo((pucTransMsg + IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN), &ulDataLen, usType);

    if ((IMS_NIC_SUCC != ulResult) || (0 == ulDataLen) || (ulDataLen > IPS_MNTN_CCORE_INFO_LEN))
    {
        TTF_LOG1(UEPS_PID_IPS_CCORE, 0, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_CCORE_OutputImsNicStatsInfo : ERROR : IMS_NIC_GetMntnInfo  Failed! ulDataLen =%d\n", (long)ulDataLen);
        return;
    }

    IPS_MNTN_CCORE_TransMsg(pucData, ulDataLen + sizeof(VOS_UINT32), usType);

    return;
}
VOS_VOID IPS_MNTN_CCORE_RcvOmMsgProc(VOS_VOID *pMsg)
{
    VOS_UINT32          usMsgId;

    usMsgId = (VOS_UINT16)(*((VOS_UINT32 *)((VOS_UINT8 *)(pMsg) + VOS_MSG_HEAD_LENGTH)));

    switch ( usMsgId )
    {
        case ID_OM_IPS_CCORE_ADVANCED_TRACE_CONFIG_REQ:
            IPS_MNTN_CCORE_TraceAdvancedCfgReq(pMsg);
            break;

        case ID_OM_IPS_CCORE_MNTN_INFO_CONFIG_REQ:
            IPS_MNTN_CCORE_RcvIpsMntnInfoCfgReq(pMsg);
            break;

        default:
            TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_CCORE_RcvOmMsgProc : ERROR : Receive Unkown Type Message !" );
            break;
    }
    return;
}


VOS_VOID IPS_MNTN_CCORE_RcvTimerExpireMsgProc(REL_TIMER_MSG *pTimerMsg)
{
    switch ( pTimerMsg->ulName)
    {
        case IPS_MNTN_CCORE_INFO_TIMER:
            IPS_MNTN_CCORE_IpsMntnInfoTimeoutProc();
            break;

        default:
            TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_CCORE_RcvTimerExpireMsgProc : ERROR : Receive Unkown Type Message !" );
            break;
    }

    return;
}


VOS_VOID IPS_MNTN_CCORE_MsgProc( struct MsgCB * pMsg )
{
    if(VOS_NULL_PTR == pMsg)
    {
        TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_CCORE_MsgProc : ERROR : Message NULL !" );
        return;
    }

    switch( pMsg->ulSenderPid )
    {
        case MSP_PID_DIAG_APP_AGENT: /* ����AT����Ϣ���� */
            IPS_MNTN_CCORE_RcvOmMsgProc( (VOS_VOID *)pMsg );
            break;

        case VOS_PID_TIMER:
            IPS_MNTN_CCORE_RcvTimerExpireMsgProc((REL_TIMER_MSG *)pMsg);
            break;

        default:
            break;
    }

    return;
}
VOS_UINT32 IPS_MNTN_CCORE_FidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    VOS_UINT32  ulReturnCode;


    switch( ip )
    {
    case    VOS_IP_LOAD_CONFIG:
        ulReturnCode = RTOSCK_AdapterInit();
        if ( VOS_OK != ulReturnCode )
        {
            TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_CCORE_FidInit RTOSCK_AdapterInit Failed! \n");
            return VOS_ERR;
        }

        ulReturnCode = VISP_InitTCPIPStack();
        if ( VOS_OK != ulReturnCode )
        {
            TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_CCORE_FidInit VISP_InitTCPIPStack Failed! \n");
            return VOS_ERR;
        }

        /* ��ʼ��IMS�������� */
        ulReturnCode        = IMS_NIC_InitAll();
        if ( IMS_NIC_SUCC != ulReturnCode )
        {
            TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_CCORE_FidInit IMS_NIC_Init Failed! \n");
            return VOS_ERR;
        }

        /* PIDΪWUEPS_PID_IPS_MNTN_CCORE*/
        ulReturnCode = VOS_RegisterPIDInfo(UEPS_PID_IPS_CCORE,
                                    VOS_NULL_PTR,
                                    (Msg_Fun_Type)IPS_MNTN_CCORE_MsgProc);
        if( VOS_OK != ulReturnCode )
        {
            TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                    "IPS, IPS_MNTN_CCORE_FidInit VOS_RegisterPIDInfo Failed" );
            return VOS_ERR;
        }

        /* FIDΪWUEPS_PID_IPS_MNTN*/
        ulReturnCode = VOS_RegisterMsgTaskPrio(UEPS_FID_IPS_CCORE, VOS_PRIORITY_M4);
        if( VOS_OK != ulReturnCode )
        {
            TTF_LOG(UEPS_PID_IPS_CCORE, DIAG_MODE_COMM, PS_PRINT_ERROR,
                    "IPS, IPS_MNTN_CCORE_FidInit VOS_RegisterTaskPrio Failed" );
            return VOS_ERR;
        }

        break;

    case   VOS_IP_FARMALLOC:
    case   VOS_IP_INITIAL:
    case   VOS_IP_ENROLLMENT:
    case   VOS_IP_LOAD_DATA:
    case   VOS_IP_FETCH_DATA:
    case   VOS_IP_STARTUP:
    case   VOS_IP_RIVAL:
    case   VOS_IP_KICKOFF:
    case   VOS_IP_STANDBY:
    case   VOS_IP_BROADCAST_STATE:
    case   VOS_IP_RESTART:
        break;

    default:
        break;
    }

    return VOS_OK;
} /* ISP_MNTN_CCORE_FidInit */

#else /*FEATURE_ON == FEATURE_IMS*/

VOS_UINT32 IPS_MNTN_CCORE_FidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    switch( ip )
    {
    case    VOS_IP_LOAD_CONFIG:

        break;

    case   VOS_IP_FARMALLOC:
    case   VOS_IP_INITIAL:
    case   VOS_IP_ENROLLMENT:
    case   VOS_IP_LOAD_DATA:
    case   VOS_IP_FETCH_DATA:
    case   VOS_IP_STARTUP:
    case   VOS_IP_RIVAL:
    case   VOS_IP_KICKOFF:
    case   VOS_IP_STANDBY:
    case   VOS_IP_BROADCAST_STATE:
    case   VOS_IP_RESTART:
        break;

    default:
        break;
    }

    return VOS_OK;
} /* ISP_MNTN_CCORE_FidInit */
/*lint -restore */
/*lint +e534*/

#endif  /*FEATURE_ON == FEATURE_IMS*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif




