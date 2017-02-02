
#include "product_config.h"
#include "si_pih.h"
#include "UsimPsInterface.h"
#include "apminterface.h"
#include "AtOamInterface.h"
#include "softcrypto.h"
#include "OamXmlComm.h"
#include "csimagent.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID PS_FILE_ID_PIH_PROC_C
/*lint +e767*/

SI_PIH_POLL_TIME_STRU       g_stPIHPollTime[3];

SI_PIH_PROTECT_CTRL_STRU    g_stPIHProtectCtrl;

SI_PIH_CSIM_CTRL_STRU       g_stPIHCSIMCtrlInfo;

/*����Э��ջע��Ŀ�״̬��Ϣ,��ʼ��Ϊ0,����PID��ʼ������ʱ������*/
VOS_UINT32                  g_aulPIHUsimBCPid[SI_PIH_BCPID_REG_MAX] = {0};

/*����Э��ջע���Refresh��״̬��Ϣ,��ʼ��Ϊ0,����PID��ʼ������ʱ������*/
VOS_UINT32                  g_aulPIHRefreshBCPid[SI_PIH_BCPID_REG_MAX] = {0};

SI_PIH_CARDINFO_STRU        g_stPihCardInfo;

SI_PIH_CHANNELAPPINFO_STRU  g_astPIHChannelAppInfo[USIMM_CHANNEL_NUMBER_MAX];

#if (FEATURE_ON == FEATURE_VSIM)
VOS_UINT8                   g_aucVsimAPNData[SI_PIH_VSIMAPN_MAX];

VOS_UINT32                  g_ulTEEShareAddr;

SI_PIH_FWRITE_PARA_STRU     g_stPIHFileWriteGlobal;

#endif  /*(FEATURE_ON == FEATURE_VSIM)*/

SI_PIH_CTRL_INFO_NODE_STRU              g_astPIHCtrlInfoNode[SI_PIH_CTRL_INFO_SIZE];    /* ���PIH������Ϣ�ڵ� */
OM_LIST_S                               g_astPIHCtrlListHeader[SI_PIH_INFO_LIST_BUTT];  /* ���PIH������Ϣ����ͷ */
SI_PIH_CTRL_INFO_NODE_STRU             *g_pstPIHCurrNode = VOS_NULL_PTR;                /* ָ��ǰ������Ϣ�Ľڵ� */


VOS_VOID SI_PIH_InitList(VOS_VOID)
{
    VOS_UINT8                           ucIndex;

    /* ��ʼ������ͷ */
    for (ucIndex = 0; ucIndex < SI_PIH_INFO_LIST_BUTT; ucIndex++)
    {
        /*lint -e717*/
        OM_INIT_LIST_HEAD(&g_astPIHCtrlListHeader[ucIndex]);
        /*lint +e717*/
    }

    /* ���ڵ���ӵ�FREE�б��� */
    /*lint -e534*/
    VOS_MemSet(g_astPIHCtrlInfoNode, 0, sizeof(g_astPIHCtrlInfoNode));
    /*lint +e534*/

    for (ucIndex = 0; ucIndex < SI_PIH_CTRL_INFO_SIZE; ucIndex++)
    {
        om_list_add_tail(&g_astPIHCtrlInfoNode[ucIndex].stListNode,
                         &g_astPIHCtrlListHeader[SI_PIH_INFO_FREE_LIST_ID]);
    }

    g_pstPIHCurrNode = VOS_NULL_PTR;

    return;
}


SI_PIH_CTRL_INFO_NODE_STRU* SI_PIH_GetCtrlNode(
    SI_PIH_INFO_LIST_ENUM_UINT8         enListType
)
{
    OM_LIST_S                          *pstIndexNode;
    SI_PIH_CTRL_INFO_NODE_STRU         *pstCtrlInfo;

    if (enListType >= SI_PIH_INFO_LIST_BUTT)
    {
        return VOS_NULL_PTR;
    }

    pstIndexNode = g_astPIHCtrlListHeader[enListType].next;

    /* û�п��ýڵ� */
    if (pstIndexNode == &g_astPIHCtrlListHeader[enListType])
    {
        return VOS_NULL_PTR;
    }

    om_list_del(pstIndexNode);

    pstCtrlInfo = om_list_entry(pstIndexNode, SI_PIH_CTRL_INFO_NODE_STRU, stListNode);

    return pstCtrlInfo;
}
VOS_VOID SI_PIH_PutCtrlNode(
    SI_PIH_INFO_LIST_ENUM_UINT8         enListType,
    SI_PIH_CTRL_INFO_NODE_STRU         *pstCtrlInfo
)
{
    if ((enListType >= SI_PIH_INFO_LIST_BUTT)
     || (VOS_NULL_PTR == pstCtrlInfo))
    {
        return;
    }

    om_list_add_tail(&(pstCtrlInfo->stListNode), &g_astPIHCtrlListHeader[enListType]);

    return;
}


VOS_VOID SI_PIH_PutCtrlNode_Head(
    SI_PIH_INFO_LIST_ENUM_UINT8         enListType,
    SI_PIH_CTRL_INFO_NODE_STRU         *pstCtrlInfo
)
{
    OM_LIST_S                          *pstListHeader;

    if ((enListType >= SI_PIH_INFO_LIST_BUTT)
     || (VOS_NULL_PTR == pstCtrlInfo))
    {
        return;
    }

    pstListHeader = &g_astPIHCtrlListHeader[enListType];

    __list_add_om(&(pstCtrlInfo->stListNode), pstListHeader, pstListHeader->next);

    return;
}

/*****************************************************************************
�� �� ��  : SI_PIH_ClearChannelInfo
��������  : ���ͨ����Ϣ
�������  :
�������  : ��
�� �� ֵ  : VOS_OK/VOS_ERR

�޶���¼  :
1.��    ��  : 2015��01��30��
  ��    ��  : zhuli
  �޸�����  : �½�����
*****************************************************************************/
VOS_VOID SI_PIH_ClearChannelInfo(VOS_VOID)
{
    VOS_UINT32                          i;

    /*lint  -e534 */
    VOS_MemSet(g_astPIHChannelAppInfo, 0, sizeof(g_astPIHChannelAppInfo));
    /*lint  +e534 */

    for (i = 0; i < USIMM_CHANNEL_NUMBER_MAX; i++)
    {
        g_astPIHChannelAppInfo[i].ulAppType = USIMM_UNLIMIT_APP_BUTT;
    }

    return;
}

/*****************************************************************************
�� �� ��  : SI_PIH_GetAppSession
��������  : ���ͨ����Ϣ
�������  :
�������  : ��
�� �� ֵ  : VOS_OK/VOS_ERR

�޶���¼  :
1.��    ��  : 2015��01��30��
  ��    ��  : zhuli
  �޸�����  : �½�����
*****************************************************************************/

VOS_UINT32 SI_PIH_GetAppBySession(
    VOS_UINT32                          ulSessionID,
    USIMM_CARDAPP_ENUM_UINT32          *penAppType)
{
    VOS_UINT32                          i;

    for (i = 0; i < ARRAYSIZE(g_astPIHChannelAppInfo); i++)
    {
        if (ulSessionID == g_astPIHChannelAppInfo[i].ulSessionID)
        {
            *penAppType = g_astPIHChannelAppInfo[i].ulAppType;

            return VOS_OK;
        }
    }

    PIH_ERROR1_LOG("SI_PIH_ClearAppSession: ulSessionID does not find",
                    (VOS_INT)ulSessionID);

    *penAppType = USIMM_UNLIMIT_APP_BUTT;

    return VOS_ERR;
}

/*****************************************************************************
�� �� ��  : SI_PIH_GetAppSession
��������  : ���ͨ����Ϣ
�������  :
�������  : ��
�� �� ֵ  : VOS_OK/VOS_ERR

�޶���¼  :
1.��    ��  : 2015��01��30��
  ��    ��  : zhuli
  �޸�����  : �½�����
*****************************************************************************/

VOS_UINT32 SI_PIH_GetAppSession(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT32                          *pulSessionID)
{
    VOS_UINT32                          i;

    for (i = 0; i < ARRAYSIZE(g_astPIHChannelAppInfo); i++)
    {
        if (enAppType == g_astPIHChannelAppInfo[i].ulAppType)
        {
            *pulSessionID = g_astPIHChannelAppInfo[i].ulSessionID;

            return VOS_OK;
        }
    }

    PIH_ERROR1_LOG("SI_PIH_ClearAppSession: App does not find",
                    (VOS_INT)enAppType);

    *pulSessionID = VOS_NULL;

    return VOS_ERR;
}

/*****************************************************************************
�� �� ��  : SI_PIH_ClearAppSession
��������  : ���ͨ����Ϣ
�������  :
�������  : ��
�� �� ֵ  : VOS_OK/VOS_ERR

�޶���¼  :
1.��    ��  : 2015��01��30��
  ��    ��  : zhuli
  �޸�����  : �½�����
*****************************************************************************/
VOS_VOID SI_PIH_ClearAppSession(
    VOS_UINT32                          ulSessionID)
{
    VOS_UINT32                          i;

    for (i = 0; i < ARRAYSIZE(g_astPIHChannelAppInfo); i++)
    {
        /*SessionID���ϲ��ҷǻ���Ӧ��*/
        if ((ulSessionID == g_astPIHChannelAppInfo[i].ulSessionID)
            &&(USIMM_CARDAPP_BUTT <= g_astPIHChannelAppInfo[i].ulAppType))
        {
            g_astPIHChannelAppInfo[i].ulAppType     = USIMM_UNLIMIT_APP_BUTT;

            g_astPIHChannelAppInfo[i].ulSessionID   = VOS_NULL;

            break;
        }
    }

    if (i >= USIMM_CHANNEL_NUMBER_MAX)
    {
        PIH_ERROR1_LOG("SI_PIH_ClearAppSession: Session does not find",
                        (VOS_INT)ulSessionID);
    }

    return;
}

/*****************************************************************************
�� �� ��  : SI_PIH_SetAppSession
��������  : ���ͨ����Ϣ
�������  :
�������  : ��
�� �� ֵ  : VOS_OK/VOS_ERR

�޶���¼  :
1.��    ��  : 2015��01��30��
  ��    ��  : zhuli
  �޸�����  : �½�����
*****************************************************************************/
VOS_VOID SI_PIH_SetAppSession(
    USIMM_CARDAPP_ENUM_UINT32           enAppType)
{
    VOS_UINT32                          ulRandNum;
    VOS_UINT32                          i;

    for (i = 0; i < ARRAYSIZE(g_astPIHChannelAppInfo); i++)
    {
        if ((enAppType == g_astPIHChannelAppInfo[i].ulAppType)
            &&(VOS_NULL != g_astPIHChannelAppInfo[i].ulSessionID))
        {
            PIH_ERROR1_LOG("SI_PIH_SetAppSession: App has Alloced Session",
                            (VOS_UINT8)enAppType);

            return;
        }

        if (USIMM_UNLIMIT_APP_BUTT == g_astPIHChannelAppInfo[i].ulAppType)
        {
            break;
        }
    }

    if (i >= USIMM_CHANNEL_NUMBER_MAX)
    {
        PIH_ERROR1_LOG("SI_PIH_SetAppSession: Channel is Full",
                        (VOS_UINT8)enAppType);

        return;
    }

    ulRandNum = VOS_Rand(USIMM_SESSION_ID_MAX);

    if (0 == ulRandNum)
    {
        ulRandNum = SI_PIH_MAKESESSION_ID(USIMM_SESSION_ID_MAX, i);
    }
    else
    {
        ulRandNum = SI_PIH_MAKESESSION_ID(ulRandNum, i);
    }

    g_astPIHChannelAppInfo[i].ulAppType   = enAppType;

    g_astPIHChannelAppInfo[i].ulSessionID = ulRandNum;

    return;
}

/*****************************************************************************
�� �� ��  : SI_PIH_SetChannelInfo
��������  :
�������  :
�������  : ��
�� �� ֵ  : VOS_OK/VOS_ERR

�޶���¼  :
1.��    ��  : 2015��01��30��
  ��    ��  : zhuli
  �޸�����  : �½�����
*****************************************************************************/
VOS_VOID SI_PIH_SaveChannelInfo(
    VOS_UINT32                          ulChannelID,
    VOS_UINT32                          ulSessionID,
    VOS_UINT32                          ulAppType)
{
    if (ulChannelID >= ARRAYSIZE(g_astPIHChannelAppInfo))
    {
        PIH_ERROR1_LOG("SI_PIH_SaveChannelInfo: Wrong Channel ID",
                        (VOS_INT)ulChannelID);

        return;
    }

    g_astPIHChannelAppInfo[ulChannelID].ulAppType   = ulAppType;
    g_astPIHChannelAppInfo[ulChannelID].ulSessionID = ulSessionID;

    return;
}

/*****************************************************************************
�� �� ��  : SI_PIH_SendFdnReqMsg
��������  : PIHģ��FDN������Ϣ���ͺ���
�������  : ulType:��������
            pucPin2:PIN2��
�������  : ��
�� �� ֵ  : VOS_OK/VOS_ERR
���ú���  :
��������  :
�޶���¼  :
1.��    ��  : 2015��01��30��
  ��    ��  : H00300778
  �޸�����  : �½�����
*****************************************************************************/
VOS_UINT32 SI_PIH_SendFdnReqMsg(
    USIMM_FBDN_HANDLE_ENUM_UINT32       ulType,
    VOS_UINT8                           *pucPin2)
{
    USIMM_FDNPROCESS_REQ_STRU          *pstMsg;

    pstMsg = (USIMM_FDNPROCESS_REQ_STRU *)VOS_AllocMsg(MAPS_PIH_PID,
                                                sizeof(USIMM_FDNPROCESS_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        PIH_WARNING_LOG("SI_PIH_SendFdnReqMsg: VOS_AllocMsg is Failed");

        return VOS_ERR;
    }

    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.enMsgName       = USIMM_FBDNPROCESS_REQ;
    pstMsg->stMsgHeader.enAppType       = USIMM_GUTL_APP;
    pstMsg->stMsgHeader.ulSendPara      = SI_PIH_SEND_PAPA(g_pstPIHCurrNode->usClient, g_pstPIHCurrNode->ulEventType);
    pstMsg->enHandleType                = ulType;

    /*lint -e534*/
    VOS_MemCpy(pstMsg->aucPIN, pucPin2, USIMM_PINNUMBER_LEN);
    /*lint +e534*/

    return VOS_SendMsg(MAPS_PIH_PID, pstMsg);
}

/*****************************************************************************
�� �� ��  : SI_PIH_SendDeactiveReqMsg
��������  : PIHģ��SIM��ȥ����������Ϣ���ͺ���
�������  : ��
�������  : ��
�� �� ֵ  : VOS_OK/VOS_ERR
���ú���  :
��������  :
�޶���¼  :
1.��    ��  : 2015��01��31��
  ��    ��  : H00300778
  �޸�����  : �½�����
*****************************************************************************/
VOS_UINT32 SI_PIH_SendDeactiveReqMsg(
    VOS_UINT32                          ulSendPara)
{
    USIMM_DEACTIVECARD_REQ_STRU        *pstMsg;

    pstMsg = (USIMM_DEACTIVECARD_REQ_STRU *)VOS_AllocMsg(MAPS_PIH_PID,
                                                         sizeof(USIMM_DEACTIVECARD_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        PIH_WARNING_LOG("SI_PIH_SendDeactiveReqMsg: VOS_AllocMsg is Failed");

        return VOS_ERR;
    }

    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.enMsgName       = USIMM_DEACTIVECARD_REQ;
    pstMsg->stMsgHeader.enAppType       = USIMM_GUTL_APP;
    pstMsg->stMsgHeader.ulSendPara      = ulSendPara;

    return VOS_SendMsg(MAPS_PIH_PID, pstMsg);
}

/*****************************************************************************
�� �� ��  : SI_PIH_SendProtectResetReqMsg
��������  : PIHģ��SIM�������Ը�λ������Ϣ���ͺ���
�������  : ��
�������  : ��
�� �� ֵ  : VOS_OK/VOS_ERR
���ú���  :
��������  :
�޶���¼  :
1.��    ��  : 2015��01��31��
  ��    ��  : H00300778
  �޸�����  : �½�����
*****************************************************************************/
VOS_UINT32 SI_PIH_SendProtectResetReqMsg(VOS_VOID)
{
    USIMM_PROTECTRESET_REQ_STRU        *pstMsg;

    pstMsg = (USIMM_PROTECTRESET_REQ_STRU *)VOS_AllocMsg(MAPS_PIH_PID,
                                                         sizeof(USIMM_PROTECTRESET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        PIH_WARNING_LOG("SI_PIH_SendProtectResetReqMsg: VOS_AllocMsg is Failed");

        return VOS_ERR;
    }

    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.enMsgName       = USIMM_PROTECTRESET_REQ;
    pstMsg->stMsgHeader.enAppType       = USIMM_GUTL_APP;
    pstMsg->stMsgHeader.ulSendPara      = VOS_NULL;

    return VOS_SendMsg(MAPS_PIH_PID, pstMsg);
}

/*****************************************************************************
�� �� ��  : SI_PIH_SendStatusReqMsg
��������  : PIHģ��SIM����������ѯ������Ϣ���ͺ���
�������  : ��
�������  : ��
�� �� ֵ  : VOS_OK/VOS_ERR
���ú���  :
��������  :
�޶���¼  :
1.��    ��  : 2015��01��31��
  ��    ��  : H00300778
  �޸�����  : �½�����
*****************************************************************************/
VOS_UINT32 SI_PIH_SendStatusReqMsg(
    USIMM_POLL_FCP_ENUM_UINT32          enNeedFcp)
{
    USIMM_STATUSCMD_REQ_STRU           *pstMsg;
    VOS_UINT32                          ulResult;

    pstMsg = (USIMM_STATUSCMD_REQ_STRU *)VOS_AllocMsg(MAPS_PIH_PID,
                                                      sizeof(USIMM_STATUSCMD_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        PIH_WARNING_LOG("SI_PIH_SendStatusReqMsg: VOS_AllocMsg is Failed");

        return VOS_ERR;
    }

    /* �����Ϣ����,APP������GTUL���ͣ�USIMMģ�鲻����APP���ͣ�ֻ�ڻ���ͨ���Ϸ���STATUS���� */
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.enMsgName       = USIMM_STATUSCMD_REQ;
    pstMsg->stMsgHeader.enAppType       = USIMM_UNLIMIT_AUTO;
    pstMsg->stMsgHeader.ulSendPara      = VOS_NULL;
    pstMsg->stFilePath.ulPathLen        = VOS_NULL;

    ulResult = USIMM_IsTestCard();

    if ((USIMM_PHYCARD_TYPE_ICC == g_stPihCardInfo.enPhyCardType)
        ||(VOS_TRUE == ulResult))
    {
        pstMsg->enNeedFcp               = USIMM_POLL_NEED_FCP;
    }
    else
    {
        pstMsg->enNeedFcp               = enNeedFcp;
    }

    return VOS_SendMsg(MAPS_PIH_PID, pstMsg);
}

/*****************************************************************************
�� �� ��  : SI_PIH_SendImsiPollingReqMsg
��������  : PIHģ��SIM����������ѯIMSI������Ϣ���ͺ���
�������  : ��
�������  : ��
�� �� ֵ  : VOS_OK/VOS_ERR
���ú���  :
��������  :
�޶���¼  :
1.��    ��  : 2015��02��04��
  ��    ��  : H00300778
  �޸�����  : �½�����
*****************************************************************************/
VOS_UINT32 SI_PIH_SendImsiPollingReqMsg(VOS_VOID)
{
    USIMM_RACCESS_REQ_STRU             *pstMsg;

    pstMsg = (USIMM_RACCESS_REQ_STRU *)VOS_AllocMsg(MAPS_PIH_PID,
                                                    sizeof(USIMM_RACCESS_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        PIH_WARNING_LOG("SI_PIH_SendImsiPollingReqMsg: VOS_AllocMsg is Failed");

        return VOS_ERR;
    }

    /* ������ݽṹ���Զ�ȡ�������ļ��ķ�ʽ��ȡ6F07�ļ���P1/P2/P3�ֱ�Ϊ0��0��9. �ļ�·��Ϊ�գ���Ĭ��·�������� */
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.enMsgName       = USIMM_RACCESS_REQ;
    pstMsg->stMsgHeader.enAppType       = USIMM_GUTL_APP;
    pstMsg->stMsgHeader.ulSendPara      = VOS_NULL;     /* Ϊ�˺�AT�����������Ҫ��ֵΪ0 */

    pstMsg->enCmdType                   = USIMM_READ_BINARY;
    pstMsg->ucP1                        = VOS_NULL;
    pstMsg->ucP2                        = VOS_NULL;
    pstMsg->ucP3                        = USIMM_EF_IMSI_LEN;
    pstMsg->usEfId                      = EFIMSI;
    pstMsg->usPathLen                   = VOS_NULL;

    return VOS_SendMsg(MAPS_PIH_PID, pstMsg);
}

/*****************************************************************************
�� �� ��  : SI_PIH_CloseChannelReq
��������  : PIHģ��SIM���߼�ͨ���ر�������Ϣ���ͺ���
�������  : ulSessionID:�ỰID
�������  : ��
�� �� ֵ  : VOS_OK/VOS_ERR
���ú���  :
��������  :
�޶���¼  :
1.��    ��  : 2015��02��02��
  ��    ��  : H00300778
  �޸�����  : �½�����
*****************************************************************************/
VOS_UINT32 SI_PIH_CloseChannelReq(
    VOS_UINT32                          ulAppType,
    VOS_UINT32                          ulSessionID)
{
    USIMM_CLOSECHANNEL_REQ_STRU        *pstMsg;

    pstMsg = (USIMM_CLOSECHANNEL_REQ_STRU *)VOS_AllocMsg(MAPS_PIH_PID,
                                                         sizeof(USIMM_CLOSECHANNEL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        PIH_WARNING_LOG("SI_PIH_CloseChannelReq: VOS_AllocMsg is Failed");

        return VOS_ERR;
    }

    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.enMsgName       = USIMM_CLOSECHANNEL_REQ;
    pstMsg->stMsgHeader.enAppType       = ulAppType;

    if (VOS_NULL_PTR == g_pstPIHCurrNode)
    {
        pstMsg->stMsgHeader.ulSendPara  = VOS_NULL;
    }
    else
    {
        pstMsg->stMsgHeader.ulSendPara  = SI_PIH_SEND_PAPA(g_pstPIHCurrNode->usClient, g_pstPIHCurrNode->ulEventType);
    }

    pstMsg->ulSessionID                 = ulSessionID;

    return VOS_SendMsg(MAPS_PIH_PID, pstMsg);
}

/*****************************************************************************
�� �� ��  : SI_PIH_OpenChannelReq
��������  : PIHģ��SIM���߼�ͨ����������Ϣ���ͺ���
�������  : ulAIDLen:AID����
            pucADFName:AID����
�������  : ��
�� �� ֵ  : VOS_OK/VOS_ERR
���ú���  :
��������  :
�޶���¼  :
1.��    ��  : 2015��02��02��
  ��    ��  : H00300778
  �޸�����  : �½�����
*****************************************************************************/
VOS_UINT32 SI_PIH_OpenChannelReq(
    VOS_UINT32                          ulAIDLen,
    VOS_UINT8                           *pucADFName)
{
    USIMM_OPENCHANNEL_REQ_STRU         *pstMsg;

    if (ulAIDLen > (2 * USIMM_AID_LEN_MAX))
    {
        return VOS_ERR;
    }

    pstMsg = (USIMM_OPENCHANNEL_REQ_STRU *)VOS_AllocMsg(MAPS_PIH_PID,
                                                        sizeof(USIMM_OPENCHANNEL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        PIH_WARNING_LOG("SI_PIH_OpenChannelReq: VOS_AllocMsg is Failed");

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemSet(&pstMsg->stChannelInfo, 0, sizeof(USIMM_CHANNEL_INFO_STRU));
    /*lint +e534*/

    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.enMsgName       = USIMM_OPENCHANNEL_REQ;
    pstMsg->stMsgHeader.enAppType       = USIMM_UNLIMIT_AUTO;

    if (VOS_NULL_PTR == g_pstPIHCurrNode)
    {
        pstMsg->stMsgHeader.ulSendPara  = VOS_NULL;
    }
    else
    {
        pstMsg->stMsgHeader.ulSendPara  = SI_PIH_SEND_PAPA(g_pstPIHCurrNode->usClient, g_pstPIHCurrNode->ulEventType);
    }

    pstMsg->stChannelInfo.ulAIDLen      = ulAIDLen;

    /*lint -e534*/
    VOS_MemCpy(pstMsg->stChannelInfo.aucADFName, pucADFName, ulAIDLen);
    /*lint +e534*/

    return VOS_SendMsg(MAPS_PIH_PID, pstMsg);
}

/*****************************************************************************
�� �� ��  : SI_PIH_SendActiveCardReqMsg
��������  : PIHģ��SIM����ʼ����Ϣ���ͺ���
�������  : enMsgName:��ʼ����Ϣ����
�������  : ��
�� �� ֵ  : VOS_OK/VOS_ERR
���ú���  :
��������  :
�޶���¼  :
1.��    ��  : 2015��02��06��
  ��    ��  : H00300778
  �޸�����  : �½�����
*****************************************************************************/
VOS_UINT32 SI_PIH_SendActiveCardReqMsg(
    VOS_UINT32                          ulSendPara
)
{
    NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU   stUSIMMOpenSpeed;
    VOS_UINT32                              ulUsimmOpenSpeed;
    USIMM_ACTIVECARD_REQ_STRU               *pstMsg;

    if(NV_OK != NV_Read(en_NV_Item_FollowOn_OpenSpeed_Flag, &stUSIMMOpenSpeed, sizeof(NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU)))
    {
        ulUsimmOpenSpeed = USIMM_OPENSPEEDDISABLE;
    }
    else
    {
        ulUsimmOpenSpeed = stUSIMMOpenSpeed.ulQuickStartSta;
    }

    if (USIMM_OPENSPEEDENABLE == ulUsimmOpenSpeed)
    {
        PIH_WARNING_LOG("SI_PIH_SendInitCardReqMsg:Open Speed is ON.");

        return VOS_ERR;
    }

    pstMsg = (USIMM_ACTIVECARD_REQ_STRU *)VOS_AllocMsg(MAPS_PIH_PID, sizeof(USIMM_ACTIVECARD_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        PIH_WARNING_LOG("SI_PIH_SendInitCardReqMsg:AllocMsg Failed.");

        return VOS_ERR;
    }

    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.enMsgName       = USIMM_ACTIVECARD_REQ;
    pstMsg->stMsgHeader.enAppType       = USIMM_GUTL_APP;
    pstMsg->stMsgHeader.ulSendPara      = ulSendPara;

    return VOS_SendMsg(MAPS_PIH_PID, pstMsg);
}


VOS_UINT32 SI_PIHSendATMsg(
    SI_PIH_EVENT_INFO_STRU              *pstEvent)
{
#ifndef COMM_ITT
    MN_APP_PIH_AT_CNF_STRU *pstMsg;

    pstMsg = (MN_APP_PIH_AT_CNF_STRU*)VOS_AllocMsg(MAPS_PIH_PID,
                sizeof(MN_APP_PIH_AT_CNF_STRU)-VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        PIH_ERROR_LOG("SI_SimCallback: Alloc Msg Failed!");
        return VOS_ERR;
    }

    pstEvent->ClientId = MN_GetRealClientId(pstEvent->ClientId, MAPS_PIH_PID);

    /*lint -e534*/
    VOS_MemCpy((VOS_VOID *)&pstMsg->stPIHAtEvent, pstEvent, sizeof(SI_PIH_EVENT_INFO_STRU));
    /*lint +e534*/

    pstMsg->ulReceiverPid   = WUEPS_PID_AT;
    pstMsg->ulMsgId         = PIH_AT_EVENT_CNF;

    (VOS_VOID)VOS_SendMsg(MAPS_PIH_PID, pstMsg);
#endif

    return VOS_OK;
}



VOS_UINT32 SI_PIH_HexToAsciiCode(
    VOS_UINT8                           ucSrc,
    VOS_CHAR                            *pcDst)
{
    if (ucSrc <= 0x09)
    {
        *pcDst = (VOS_CHAR)(ucSrc-0x00) + '0';
    }
    else if ((0xa <= ucSrc)&&(ucSrc <= 0xf))
    {
        *pcDst = (VOS_CHAR)(ucSrc-0x0a) + 'A';
    }
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;
}



VOS_UINT32 SI_PIH_AsciiToHexCode(
    VOS_CHAR                            cSrc,
    VOS_UINT8                           *pucDst)
{
    if (( cSrc >= '0') && (cSrc <= '9')) /* the number is 0-9 */
    {
        *pucDst = (VOS_UINT8)(cSrc - '0');
    }
    else if ( (cSrc >= 'a') && (cSrc <= 'f') ) /* the number is 0-9 */
    {
        *pucDst = (VOS_UINT8)(cSrc - 'a') + 0x0a;
    }
    else if ( (cSrc >= 'A') && (cSrc <= 'F') ) /* the number is 0-9 */
    {
        *pucDst = (VOS_UINT8)(cSrc - 'A') + 0x0a;
    }
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 SI_PIH_SendTPDUReq(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT32                          ulSendPara,
    USIMM_FILEPATH_INFO_STRU           *pstFilePath,
    USIMM_TPDU_DATA_STRU               *pstTpduData
)
{
    USIMM_SENDTPDUDATA_REQ_STRU         *pstMsg;

    if (VOS_NULL_PTR == pstTpduData)
    {
        PIH_WARNING_LOG("SI_PIH_SendTPDUReq: Input Para is incorrect.");/*��ӡ����*/

        return VOS_ERR;
    }

    /* �����ڴ� */
    pstMsg = (USIMM_SENDTPDUDATA_REQ_STRU *)VOS_AllocMsg(MAPS_PIH_PID,
                                                    (sizeof(USIMM_SENDTPDUDATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    if (VOS_NULL_PTR == pstMsg)
    {
        PIH_WARNING_LOG("SI_PIH_SendTPDUReq: VOS_AllocMsg is Failed");/*��ӡ����*/

        return VOS_ERR; /*���غ���������Ϣ*/
    }

    /* �����Ϣ���� */
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.enMsgName       = USIMM_SENDTPDUDATA_REQ;
    pstMsg->stMsgHeader.enAppType       = enAppType;
    pstMsg->stMsgHeader.ulSendPara      = ulSendPara;

    /*lint -e534*/
    VOS_MemCpy(&pstMsg->stTPDUData, pstTpduData, sizeof(USIMM_TPDU_DATA_STRU));

    if (VOS_NULL_PTR != pstFilePath)
    {
        VOS_MemCpy(&pstMsg->stFilePath, pstFilePath, sizeof(USIMM_FILEPATH_INFO_STRU));
    }
    else
    {
        VOS_MemSet(&pstMsg->stFilePath, 0, sizeof(USIMM_FILEPATH_INFO_STRU));
    }
    /*lint +e534*/

    return VOS_SendMsg(MAPS_PIH_PID, pstMsg);
}

/*****************************************************************************
�� �� ��  : SI_PIH_PollTimerInit
��������  : PIH��ʱ�����ܳ�ʼ��ʱ��ʼ��������
�������  : ��
�������  : ��
�� �� ֵ  : VOS_OK
���ú���  :
��������  :
�޶���¼  :
1.��    ��  : 2010��07��26��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/
VOS_VOID SI_PIH_PollTimerInit(SI_VOID)
{
    USIMM_FEATURE_CFG_STRU              stUsimmFeatureCfg;

    g_stPIHPollTime[SI_PIH_TIMER_NAME_CHECKSTATUS].ulTimeLen    = SI_PIH_POLL_TIMER_LEN;
    g_stPIHPollTime[SI_PIH_TIMER_NAME_CHECKSTATUS].ulTimerName  = SI_PIH_TIMER_NAME_CHECKSTATUS;
    g_stPIHPollTime[SI_PIH_TIMER_NAME_CHECKSTATUS].enPollState  = SI_PIH_POLLTIMER_ENABLE;

    g_stPIHPollTime[SI_PIH_TIMER_NAME_CALL].ulTimeLen           = SI_PIH_CALL_TIMER_LEN;
    g_stPIHPollTime[SI_PIH_TIMER_NAME_CALL].ulTimerName         = SI_PIH_TIMER_NAME_CALL;
    g_stPIHPollTime[SI_PIH_TIMER_NAME_CALL].enPollState         = SI_PIH_POLLTIMER_DISABLE;

    /* Ĭ�ϲ���ѯ */
    g_stPIHPollTime[SI_PIH_TIMER_NAME_CHECKIMSI].ulTimeLen      = SI_PIH_IMSI_TIMER_LEN;
    g_stPIHPollTime[SI_PIH_TIMER_NAME_CHECKIMSI].ulTimerName    = SI_PIH_TIMER_NAME_CHECKIMSI;
    g_stPIHPollTime[SI_PIH_TIMER_NAME_CHECKIMSI].enPollState    = SI_PIH_POLLTIMER_DISABLE;

    if (VOS_OK != NV_Read(en_NV_Item_Usim_Support_Feature_Config,
                         (VOS_VOID*)&stUsimmFeatureCfg, sizeof(stUsimmFeatureCfg)))
    {
        return;
    }

    if (VOS_TRUE == stUsimmFeatureCfg.unCfg.stFeatureCfg.ulImsiPolling)
    {
        g_stPIHPollTime[SI_PIH_TIMER_NAME_CHECKIMSI].enPollState= SI_PIH_POLLTIMER_ENABLE;
    }

    return;
}

/*****************************************************************************
�� �� ��  : WuepsPIHPidInit
��������  : PIH���ܳ�ʼ��ʱ��ʼ��������
�������  : ��
�������  : ��
�� �� ֵ  : VOS_OK
���ú���  :
��������  :
�޶���¼  :
1.��    ��  : 2010��07��26��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/

VOS_VOID SI_PIH_InitGlobalVar(VOS_VOID)
{
    /*lint -e534*/
    SI_PIH_InitList();

    VOS_MemSet(g_stPIHPollTime,         0, sizeof(g_stPIHPollTime));

    VOS_MemSet(&g_stPIHProtectCtrl,     0, sizeof(g_stPIHProtectCtrl));

    VOS_MemSet(&g_stPIHCSIMCtrlInfo,    0, sizeof(g_stPIHCSIMCtrlInfo));

    SI_PIH_ClearChannelInfo();
    /*lint +e534*/

#if (FEATURE_ON == FEATURE_VSIM)
    /*lint -e534*/
    VOS_MemSet(&g_stPIHFileWriteGlobal, 0, sizeof(g_stPIHFileWriteGlobal));

    VOS_MemSet(g_aucVsimAPNData, 0, sizeof(g_aucVsimAPNData));
    /*lint +e534*/

    SI_PIH_InitTEEShareAddr();
#endif  /*(FEATURE_ON == FEATURE_VSIM)*/

    g_stPIHProtectCtrl.enProtectFun = SI_PIH_PROTECT_ENABLE;

    SI_PIH_PollTimerInit();

    return;
}

/*****************************************************************************
�� �� ��  : WuepsPIHPidInit
��������  : PIH���ܳ�ʼ��ʱ��ʼ��������
�������  : ��
�������  : ��
�� �� ֵ  : VOS_OK
���ú���  :
��������  :
�޶���¼  :
1.��    ��  : 2010��07��26��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/
VOS_UINT32 WuepsPIHPidInit(enum VOS_INIT_PHASE_DEFINE InitPhrase)
{
    switch( InitPhrase )
    {
        case   VOS_IP_LOAD_CONFIG:
            SI_PIH_InitGlobalVar();
            break;

        case   VOS_IP_RESTART:
            /* A�˲���ע�ᣬPCSC��ע����PIH����� */
            /*lint -e534*/
            PIH_RegUsimCardStatusIndMsg(ACPU_PID_PCSC);
            /*lint +e534*/
            break;

        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
�� �� ��  : SI_PIH_MNTNDataHook
��������  : PIH��ά�ɲ����ݹ���
�������  : ulHookMsgName:��������Ϣ����
            ulHookDataLen:���ݳ���
            pucHookData:��������
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :
�޶���¼  :
1.��    ��  : 2013��06��14��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/
VOS_VOID SI_PIH_MNTNDataHook(
    VOS_UINT32                          ulHookMsgName,
    VOS_UINT32                          ulHookDataLen,
    VOS_UINT8                           *pucHookData)
{
    SI_PIH_HOOK_MSG_STRU    *pstMsg;

    pstMsg = (SI_PIH_HOOK_MSG_STRU *)VOS_AllocMsg(MAPS_PIH_PID,
                                                  (sizeof(SI_PIH_HOOK_MSG_STRU) - VOS_MSG_HEAD_LENGTH)+ulHookDataLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        PIH_WARNING_LOG("SI_PIH_MNTNDataHook: Alloc Msg is Failed");

        return;
    }

    pstMsg->ulReceiverPid   = MAPS_PIH_PID;
    pstMsg->ulMsgName       = ulHookMsgName;

    if (VOS_NULL != ulHookDataLen)
    {
        /*lint -e534*/
        VOS_MemCpy(pstMsg->aucContent, pucHookData, ulHookDataLen);
        /*lint +e534*/
    }

    (VOS_VOID)VOS_SendMsg(MAPS_PIH_PID, pstMsg);

    return;
}


VOS_UINT32 SI_PIH_ParaCheck(
    VOS_UINT16                          usClient)
{
    OM_LIST_S                          *pstListHeader;
    OM_LIST_S                          *pstIndexNode;
    OM_LIST_S                          *pstTempNode;
    SI_PIH_CTRL_INFO_NODE_STRU         *pstCtrlNode;

    pstListHeader = &g_astPIHCtrlListHeader[SI_PIH_INFO_USED_LIST_ID];

    om_list_for_each_safe(pstIndexNode, pstTempNode, pstListHeader)
    {
        pstCtrlNode = om_list_entry(pstIndexNode, SI_PIH_CTRL_INFO_NODE_STRU, stListNode);

        /* �ڶ������ҵ���ͬ��ClientId */
        if (usClient == pstCtrlNode->usClient)
        {
            return TAF_ERR_PARA_ERROR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
�� �� ��  : SI_PIH_PollTimerPro
��������  : ����PIH��ʱ����صĿ������޸�ʱ���ȹ���
�������  : pstPIHTimer:��ʱ���ṹ
�������  : ��
�� �� ֵ  : VOS_OK
���ú���  :
��������  :
�޶���¼  :
1.��    ��  : 2010��07��26��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/
VOS_VOID SI_PIH_PollTimerPro(
    SI_PIH_POLL_TIME_STRU               *pstPIHTimer)
{
    VOS_UINT32 ulResult = VOS_OK;

    if(pstPIHTimer->stTimer != VOS_NULL_PTR)        /*��ʱ���������У���Ҫ��ֹͣ*/
    {
        PIH_NORMAL_LOG("SI_PIH_PollTimerPro: Need Stop Timer First.");

        if(SI_PIH_TIMER_NAME_CHECKSTATUS == pstPIHTimer->ulTimerName)
        {
            ulResult = SI_PIH_POLL_32K_TIMER_STOP(&pstPIHTimer->stTimer);
        }
        else
        {
            ulResult = VOS_StopRelTimer(&pstPIHTimer->stTimer);
        }
    }

    if(pstPIHTimer->enPollState == SI_PIH_POLLTIMER_ENABLE) /*��ʱ����Ҫ����*/
    {
        PIH_NORMAL_LOG("SI_PIH_PollTimerPro: Need Start Timer First.");

        if (SI_PIH_TIMER_NAME_CHECKSTATUS == pstPIHTimer->ulTimerName)
        {
            ulResult = SI_PIH_POLL_32K_TIMER_START(&pstPIHTimer->stTimer, pstPIHTimer->ulTimeLen, pstPIHTimer->ulTimerName);
        }
        else
        {
            ulResult = SI_PIH_POLL_TIMER_START(&pstPIHTimer->stTimer, pstPIHTimer->ulTimeLen, pstPIHTimer->ulTimerName);
        }
    }

    if(ulResult != VOS_OK)
    {
        PIH_ERROR1_LOG("SI_PIH_PollTimerPro: Handle Timer Name %d Error.", (VOS_INT32)pstPIHTimer->ulTimerName);
    }

    return;
}

/*****************************************************************************
�� �� ��  :
��������  :
�������  : ��
�������  : ��
�� �� ֵ  : VOS_UINT32 ����ִ�н��
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2010��08��20��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/
VOS_UINT32 SI_PIH_EventCallBack(
    SI_PIH_EVENT_INFO_STRU              *pstEvent)
{
    if (VOS_NULL_PTR != g_pstPIHCurrNode)
    {
        pstEvent->ClientId  = g_pstPIHCurrNode->usClient;
        pstEvent->EventType = g_pstPIHCurrNode->ulEventType;
        pstEvent->OpId      = g_pstPIHCurrNode->ucOpID;

        /*lint -e534*/
        VOS_MemSet(g_pstPIHCurrNode, 0, sizeof(SI_PIH_CTRL_INFO_NODE_STRU));
        /*lint +e534*/

        SI_PIH_PutCtrlNode(SI_PIH_INFO_FREE_LIST_ID, g_pstPIHCurrNode);

        g_pstPIHCurrNode = VOS_NULL_PTR;
    }

    return SI_PIHSendATMsg(pstEvent);
}


VOS_VOID SI_PIH_SendPCSCCnfMsg(
    VOS_UINT32                          ulCmdType,
    VOS_UINT32                          ulResult,
    VOS_UINT32                          ulLen,
    VOS_UINT8                           *pucContent)
{
    SI_PIH_PCSC_CNF_STRU  *pstMsg;

    pstMsg = (SI_PIH_PCSC_CNF_STRU *)VOS_AllocMsg(MAPS_PIH_PID,
                    ((sizeof(SI_PIH_PCSC_CNF_STRU) - VOS_MSG_HEAD_LENGTH) - 4) + ulLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        PIH_ERROR_LOG("SI_PIH_SendPCSCCnfMsg: VOS_AllocMsg is Failed");

        return;
    }

    pstMsg->ulReceiverPid = ACPU_PID_PCSC;
    pstMsg->ulMsgName     = SI_PIH_PCSC_DATA_CNF;
    pstMsg->ulResult      = ulResult;
    pstMsg->ulCmdType     = ulCmdType;
    pstMsg->ulRspLen      = ulLen;

    if (VOS_NULL_PTR != pucContent)
    {
        /*lint -e534*/
        VOS_MemCpy(pstMsg->aucContent, pucContent, ulLen);
        /*lint +e534*/
    }

    if(VOS_OK != VOS_SendMsg(MAPS_PIH_PID, pstMsg))
    {
        PIH_ERROR_LOG("SI_PIH_SendPCSCCnfMsg: VOS_SendMsg is Failed");
    }

    return;
}


VOS_VOID SI_PIH_EventReportError(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    VOS_UINT32                          ulSimError,
    VOS_UINT32                          ulMsgName,
    VOS_UINT32                          ulEventType)
{
    SI_PIH_EVENT_INFO_STRU   stEvent;

    /*������*/
    stEvent.ClientId    = ClientId;
    stEvent.OpId        = OpId;
    stEvent.PIHError    = ulSimError;
    stEvent.EventType   = ulEventType;

    /*����ظ�*/
    if(SI_PIH_PCSC_DATA_REQ == ulMsgName)
    {
        SI_PIH_SendPCSCCnfMsg(ulEventType, ulSimError, 0, VOS_NULL_PTR);
    }
    else
    {
        /*lint -e534*/
        SI_PIHSendATMsg(&stEvent);
        /*lint +e534*/
    }

    return ;
}


VOS_UINT32  SI_PIH_FdnBdnStateReport(
    VOS_UINT32                          ulState,
    VOS_UINT32                          SimError,
    VOS_UINT32                          ulCmdType)
{
    SI_PIH_EVENT_INFO_STRU  Event;

    (VOS_VOID)VOS_MemSet(&Event, 0, sizeof(SI_PIH_EVENT_INFO_STRU));

    /*������*/
    Event.PIHError                    = SimError;
    Event.PIHEvent.FDNCnf.FdnCmd      = ulCmdType;
    Event.PIHEvent.FDNCnf.FdnState    = ulState;

    /*����ظ�*/
    return SI_PIH_EventCallBack(&Event);
}


VOS_VOID SI_PIH_PCSCDataCnf(
    VOS_UINT32                          ulCmdType,
    VOS_UINT32                          ulResult,
    VOS_UINT32                          ulLen,
    VOS_UINT8                           *pucContent)
{
    SI_PIH_SendPCSCCnfMsg(ulCmdType, ulResult, ulLen, pucContent);

    if (VOS_NULL_PTR != g_pstPIHCurrNode)
    {
        /*lint -e534*/
        VOS_MemSet(g_pstPIHCurrNode, 0, sizeof(SI_PIH_CTRL_INFO_NODE_STRU));
        /*lint +e534*/

        SI_PIH_PutCtrlNode(SI_PIH_INFO_FREE_LIST_ID, g_pstPIHCurrNode);

        g_pstPIHCurrNode = VOS_NULL_PTR;
    }

    return;
}


VOS_UINT32 SI_PIH_PCSCApduCheck(
    VOS_UINT32                          *pulLen,
    VOS_UINT8                           *pucApdu,
    VOS_UINT32                          *pulRspLen,
    VOS_UINT8                           *pucRsp)
{
    VOS_UINT32  ulResult        = VOS_OK;
    VOS_UINT8   aucAid[5]       = {0xA0, 0x00, 0x00, 0x00, 0x87};
    VOS_UINT8   aucSelectAid[7] = {0x00, 0xA4, 0x08, 0x04, 0x02, 0x7F, 0xFF};

    ulResult = (VOS_UINT32)VOS_MemCmp(pucApdu + 5, aucAid, sizeof(aucAid));

    if ((VOS_OK == ulResult) && (CMD_INS_SELECT == pucApdu[INS]))
    {
        /*lint -e534*/
        VOS_MemCpy(pucApdu, aucSelectAid, sizeof(aucSelectAid));
        /*lint +e534*/

        *pulLen = sizeof(aucSelectAid);

        ulResult = VOS_OK;
    }
    else if((CMD_INS_SELECT == pucApdu[INS])&&(0x04 == pucApdu[P1]))
    {
        *pulRspLen = 2;

        /* ������UICC����ICC���ж� */
        if (USIMM_PHYCARD_TYPE_UICC == g_stPihCardInfo.enPhyCardType)
        {
            pucRsp[0] = 0x6A;    /* ������ */
            pucRsp[1] = 0x82;
        }
        else
        {
            pucRsp[0] = 0x6B;
            pucRsp[1] = 0x00;
        }

        ulResult = VOS_ERR;
    }
    else if((CMD_INS_SELECT != pucApdu[INS])        && (CMD_INS_STATUS != pucApdu[INS])
         && (CMD_INS_READ_BINARY != pucApdu[INS])   && (CMD_INS_UPDATE_BINARY != pucApdu[INS])
         && (CMD_INS_READ_RECORD != pucApdu[INS])   && (CMD_INS_UPDATE_RECORD != pucApdu[INS])
         && (CMD_INS_SEARCH_RECORD != pucApdu[INS]) && (CMD_INS_DEACTIVATE_FILE != pucApdu[INS])
         && (CMD_INS_ACTIVATE_FILE != pucApdu[INS]) && (CMD_INS_AUTHENTICATE != pucApdu[INS])
         && (CMD_INS_GET_CHALLENGE != pucApdu[INS]) && (CMD_INS_ENVELOPE != pucApdu[INS])
         && (CMD_INS_FETCH != pucApdu[INS])         && (CMD_INS_TERMINAL_RESPONSE != pucApdu[INS])
         && (CMD_INS_GET_RESPONSE != pucApdu[INS])  && (CMD_INS_VERIFY != pucApdu[INS])
         && (CMD_INS_CHANGE_PIN != pucApdu[INS])    && (CMD_INS_DISABLE_PIN != pucApdu[INS])
         && (CMD_INS_ENABLE_PIN != pucApdu[INS])    && (CMD_INS_UNBLOCK_PIN != pucApdu[INS]))
    {
        *pulRspLen = 2;

        pucRsp[0] = 0x6F;    /* TECH PROBLEM */
        pucRsp[1] = 0x00;

        ulResult = VOS_ERR;
    }
    else
    {
        ulResult = VOS_OK;
    }

    return ulResult;
}

/*****************************************************************************
�� �� ��  :
��������  :
�������  : ��
�������  : ��
�� �� ֵ  : VOS_UINT32 ����ִ�н��
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2010��08��20��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/
VOS_UINT32 SI_PIH_GAccessReqProc(
    SI_PIH_GACCESS_REQ_STRU             *pstMsg)
{
    SI_PIH_EVENT_INFO_STRU          stEvent;
    VOS_UINT32                      ulResult;
    VOS_UINT8                       aucData[2] = {0};
    VOS_UINT32                      ulRspLen;
    USIMM_TPDU_DATA_STRU            stTpduData;

    /*lint -e534*/
    VOS_MemSet(&stTpduData, 0, sizeof(stTpduData));
    (VOS_VOID)VOS_MemSet(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));
    /*lint +e534*/

    if(pstMsg->aucData[1] == 0xC0)
    {
        stEvent.PIHError = TAF_ERR_NO_ERROR;

        if(pstMsg->aucData[4] > g_stPIHCSIMCtrlInfo.usRspLen)
        {
            stEvent.PIHEvent.GAccessCnf.Len = 0;

            stEvent.PIHEvent.GAccessCnf.SW1 = 0x67;
            stEvent.PIHEvent.GAccessCnf.SW2 = 0x00;
        }
        else
        {
            if (0 == pstMsg->aucData[4])
            {
                stEvent.PIHEvent.GAccessCnf.Len = g_stPIHCSIMCtrlInfo.usRspLen;
                /*lint -e534*/
                VOS_MemCpy(stEvent.PIHEvent.GAccessCnf.Command, g_stPIHCSIMCtrlInfo.aucRspCotent, g_stPIHCSIMCtrlInfo.usRspLen);
                /*lint +e534*/
            }
            else
            {
                stEvent.PIHEvent.GAccessCnf.Len = pstMsg->aucData[4];
                /*lint -e534*/
                VOS_MemCpy(stEvent.PIHEvent.GAccessCnf.Command, g_stPIHCSIMCtrlInfo.aucRspCotent, pstMsg->aucData[4]);
                /*lint +e534*/
            }
            stEvent.PIHEvent.GAccessCnf.SW1 = 0x90;
            stEvent.PIHEvent.GAccessCnf.SW2 = 0x00;
        }

        return SI_PIH_EventCallBack(&stEvent);
    }
    else
    {
        ulResult = SI_PIH_PCSCApduCheck(&pstMsg->ulDataLen, pstMsg->aucData, &ulRspLen, aucData);

        if(VOS_OK != ulResult)
        {
            stEvent.PIHError = TAF_ERR_CMD_TYPE_ERROR;

            return SI_PIH_EventCallBack(&stEvent);
        }

        if (pstMsg->ulDataLen <= USIMM_TPDU_HEAD_LEN)
        {
            /*lint -e534*/
            VOS_MemCpy(stTpduData.aucTPDUHead, pstMsg->aucData, pstMsg->ulDataLen);
            /*lint +e534*/
        }
        else
        {
            /*lint -e534*/
            VOS_MemCpy(stTpduData.aucTPDUHead, pstMsg->aucData, USIMM_TPDU_HEAD_LEN);

            stTpduData.usDataLen = (VOS_UINT16)(pstMsg->ulDataLen-USIMM_TPDU_HEAD_LEN);

            VOS_MemCpy(stTpduData.aucData, &pstMsg->aucData[USIMM_TPDU_HEAD_LEN], pstMsg->ulDataLen-USIMM_TPDU_HEAD_LEN);
            /*lint +e534*/
        }

        ulResult = SI_PIH_SendTPDUReq(USIMM_UNLIMIT_AUTO,
                                      SI_PIH_SEND_PAPA(g_pstPIHCurrNode->usClient, g_pstPIHCurrNode->ulEventType),
                                      &g_stPIHCSIMCtrlInfo.stFilePath,
                                      &stTpduData);

        if(ulResult != VOS_OK)
        {
            stEvent.PIHError = TAF_ERR_USIM_SIM_CARD_NOTEXIST;

            return SI_PIH_EventCallBack(&stEvent);
        }
    }

    return VOS_OK;
}


VOS_UINT32 SI_PIH_IsdbAccessReqProc(
    SI_PIH_ISDB_ACCESS_REQ_STRU         *pstMsg)
{
    SI_PIH_EVENT_INFO_STRU              stEvent;
    VOS_UINT32                          ulResult;
    USIMM_TPDU_DATA_STRU                stTpduData;

    /*lint -e534*/
    VOS_MemSet(&stTpduData, 0, sizeof(stTpduData));
    (VOS_VOID)VOS_MemSet(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));
    /*lint +e534*/

    if (pstMsg->ulDataLen <= USIMM_TPDU_HEAD_LEN)
    {
        /*lint -e534*/
        VOS_MemCpy(stTpduData.aucTPDUHead, pstMsg->aucData, pstMsg->ulDataLen);
        /*lint +e534*/
    }
    else
    {
        /*lint -e534*/
        VOS_MemCpy(stTpduData.aucTPDUHead, pstMsg->aucData, USIMM_TPDU_HEAD_LEN);

        stTpduData.usDataLen = (VOS_UINT16)(pstMsg->ulDataLen-USIMM_TPDU_HEAD_LEN);

        VOS_MemCpy(stTpduData.aucData, &pstMsg->aucData[USIMM_TPDU_HEAD_LEN], pstMsg->ulDataLen-USIMM_TPDU_HEAD_LEN);
        /*lint +e534*/
    }

    ulResult = SI_PIH_SendTPDUReq(USIMM_UNLIMIT_AUTO,
                                  SI_PIH_SEND_PAPA(g_pstPIHCurrNode->usClient, g_pstPIHCurrNode->ulEventType),
                                  VOS_NULL_PTR,
                                  &stTpduData);

    if (VOS_OK != ulResult)
    {
        stEvent.PIHError = TAF_ERR_SIM_FAIL;

        return SI_PIH_EventCallBack(&stEvent);
    }

    return VOS_OK;
}



VOS_UINT32 SI_PIH_GetNFCConfigFlag(VOS_VOID)
{
    USIMM_FEATURE_CFG_STRU              stUsimmFeatureCfg;

    /*lint -e534*/
    VOS_MemSet(stUsimmFeatureCfg.unCfg.aulValue ,
                VOS_FALSE,
                sizeof(stUsimmFeatureCfg.unCfg.aulValue));
    /*lint +e534*/

    if (VOS_OK != NV_Read(en_NV_Item_Usim_Support_Feature_Config,
                         (VOS_VOID*)&stUsimmFeatureCfg,
                         sizeof(stUsimmFeatureCfg)))
    {
        return VOS_FALSE;
    }

    return stUsimmFeatureCfg.unCfg.stFeatureCfg.ulNFCFlg;
}


VOS_UINT32 SI_PIH_CchoSetReqProc(
    SI_PIH_CCHO_SET_REQ_STRU            *pstMsg)
{
    SI_PIH_EVENT_INFO_STRU              stEvent;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulNFCFlg;

    (VOS_VOID)VOS_MemSet(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));

    ulNFCFlg = SI_PIH_GetNFCConfigFlag();

    if (VOS_TRUE != ulNFCFlg)
    {
        stEvent.PIHError = TAF_ERR_ERROR;

        return SI_PIH_EventCallBack(&stEvent);
    }

    ulResult = SI_PIH_OpenChannelReq(pstMsg->ulAIDLen, pstMsg->aucADFName);

    if (USIMM_API_SUCCESS != ulResult)
    {
        stEvent.PIHError = TAF_ERR_SIM_FAIL;

        return SI_PIH_EventCallBack(&stEvent);
    }

    return VOS_OK;
}


VOS_UINT32 SI_PIH_CchcSetReqProc(
    SI_PIH_CCHC_SET_REQ_STRU            *pstMsg)
{
    SI_PIH_EVENT_INFO_STRU              stEvent;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulAppType;
    VOS_UINT32                          ulNFCFlg;

    (VOS_VOID)VOS_MemSet(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));

    ulNFCFlg = SI_PIH_GetNFCConfigFlag();

    if (VOS_TRUE != ulNFCFlg)
    {
        stEvent.PIHError = TAF_ERR_ERROR;

        return SI_PIH_EventCallBack(&stEvent);
    }

    ulResult = SI_PIH_GetAppBySession(pstMsg->ulSessionID, &ulAppType);

    if (VOS_OK == ulResult)
    {
        SI_PIH_ClearAppSession(pstMsg->ulSessionID);

        ulResult = SI_PIH_CloseChannelReq(ulAppType, pstMsg->ulSessionID);
    }

    if (USIMM_API_SUCCESS != ulResult)
    {
        stEvent.PIHError = TAF_ERR_SIM_FAIL;

        return SI_PIH_EventCallBack(&stEvent);
    }

    return VOS_OK;

}


VOS_UINT32 SI_PIH_CglaSetReqProc(
    SI_PIH_CGLA_REQ_STRU                *pstMsg)
{
    SI_PIH_EVENT_INFO_STRU              stEvent;
    VOS_UINT32                          ulResult;
    USIMM_TPDU_DATA_STRU                stTpduData;
    VOS_UINT32                          ulNFCFlg;
    USIMM_CARDAPP_ENUM_UINT32           enAppType;

    (VOS_VOID)VOS_MemSet(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));

    ulNFCFlg = SI_PIH_GetNFCConfigFlag();

    if (VOS_TRUE != ulNFCFlg)
    {
        stEvent.PIHError = TAF_ERR_ERROR;

        return SI_PIH_EventCallBack(&stEvent);
    }

    /*lint -e534*/
    VOS_MemSet(&stTpduData, 0, sizeof(stTpduData));
    /*lint +e534*/

    if (pstMsg->ulDataLen <= USIMM_TPDU_HEAD_LEN)
    {
        /*lint -e534*/
        VOS_MemCpy(stTpduData.aucTPDUHead, pstMsg->aucData, pstMsg->ulDataLen);
        /*lint +e534*/
    }
    else
    {
        /*lint -e534*/
        VOS_MemCpy(stTpduData.aucTPDUHead, pstMsg->aucData, USIMM_TPDU_HEAD_LEN);

        stTpduData.usDataLen = (VOS_UINT16)(pstMsg->ulDataLen-USIMM_TPDU_HEAD_LEN);

        VOS_MemCpy(stTpduData.aucData,
                    &pstMsg->aucData[USIMM_TPDU_HEAD_LEN],
                    pstMsg->ulDataLen-USIMM_TPDU_HEAD_LEN);
    }

    if (VOS_OK != SI_PIH_GetAppBySession(pstMsg->ulSessionID, &enAppType))
    {
        stEvent.PIHError = TAF_ERR_PARA_ERROR;

        return SI_PIH_EventCallBack(&stEvent);
    }

#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)
    ulResult = SI_PIH_SendTPDUReq(enAppType,
                                  SI_PIH_SEND_PAPA(g_pstPIHCurrNode->usClient, g_pstPIHCurrNode->ulEventType),
                                  VOS_NULL_PTR,
                                  &stTpduData);
#else
    ulResult = SI_PIH_SendTPDUReq(pstMsg->ulSessionID,
                                  SI_PIH_SEND_PAPA(g_pstPIHCurrNode->usClient, g_pstPIHCurrNode->ulEventType),
                                  VOS_NULL_PTR,
                                  &stTpduData);
#endif

    if (VOS_OK != ulResult)
    {
        stEvent.PIHError = TAF_ERR_SIM_FAIL;

        return SI_PIH_EventCallBack(&stEvent);
    }

    return VOS_OK;
}
VOS_UINT32 SI_PIH_ATRQryReqProc(VOS_VOID)
{
    SI_PIH_EVENT_INFO_STRU              stEvent;
    VOS_UINT32                          ulATRLen = 0;
    VOS_UINT8                           aucATRData[SI_ATR_MAX_LEN] = {0};
    VOS_INT32                           lResult;
    SCI_ATRINFO_S                       stSCIATRInfo;

    /*lint -e534*/
    (VOS_VOID)VOS_MemSet(&stEvent,      0, sizeof(stEvent));
    (VOS_VOID)VOS_MemSet(&stSCIATRInfo, 0, sizeof(stSCIATRInfo));
    /*lint +e534*/

    lResult = (VOS_INT32)mdrv_sci_get_atr((VOS_ULONG*)&ulATRLen,
                                           aucATRData,
                                           &stSCIATRInfo);

    if ((VOS_OK != lResult)||(ulATRLen > SI_ATR_MAX_LEN))
    {
        PIH_ERROR1_LOG("SI_PIH_ATRQryReqProc: Get ATR fail.", (VOS_INT32)ulATRLen);

        stEvent.PIHError = TAF_ERR_SIM_FAIL;
    }
    else
    {
        stEvent.PIHError = TAF_ERR_NO_ERROR;

        /* Add by H00300778 for MultiAppSync Begin 2015-05-12 */
        stEvent.PIHEvent.stATRQryCnf.ulLen = ulATRLen + stSCIATRInfo.tckLen;
        /* Add by H00300778 for MultiAppSync End 2015-05-12 */

        /*lint -e534*/
        (VOS_VOID)VOS_MemCpy(stEvent.PIHEvent.stATRQryCnf.aucCommand,
                             aucATRData,
                             sizeof(stEvent.PIHEvent.stATRQryCnf.aucCommand));
        /*lint +e534*/
    }

    return SI_PIH_EventCallBack(&stEvent);
}


VOS_VOID SI_PIH_PCSC_PowerOn(
    SI_PIH_PCSC_REQ_STRU                *pstMsg)
{
    VOS_INT32                           lSCIResult;
    VOS_UINT32                          ulATRLen = 0;
    VOS_UINT8                           aucATR[USIMM_ATR_MAX_LEN];
    SCI_ATRINFO_S                       stSCIATRInfo;

    /*lint -e534*/
    (VOS_VOID)VOS_MemSet(&stSCIATRInfo, 0, sizeof(stSCIATRInfo));
    /*lint +e534*/

    lSCIResult = (VOS_INT32)mdrv_sci_get_atr((VOS_ULONG*)&ulATRLen,
                                              aucATR,
                                              &stSCIATRInfo);

    if (USIMM_SCI_SUCCESS != lSCIResult)
    {
        SI_PIH_PCSCDataCnf(pstMsg->ulCmdType,
                            (VOS_UINT32)lSCIResult,
                            VOS_NULL,
                            VOS_NULL_PTR);
    }
    else
    {
        /* Add by H00300778 for MultiAppSync Begin 2015-05-12 */
        SI_PIH_PCSCDataCnf(pstMsg->ulCmdType,
                            (VOS_UINT32)lSCIResult,
                            (ulATRLen + stSCIATRInfo.tckLen),
                            aucATR);
        /* Add by H00300778 for MultiAppSync End 2015-05-12 */
    }

    return;
}


VOS_VOID SI_PIH_PCSC_PowerOff(
    SI_PIH_PCSC_REQ_STRU                *pstMsg)
{
    SI_PIH_PCSCDataCnf(pstMsg->ulCmdType, VOS_OK, 0, VOS_NULL_PTR);

    return;
}


VOS_VOID SI_PIH_PCSC_SimQuiry(
    SI_PIH_PCSC_REQ_STRU                *pstMsg)
{
    VOS_UINT8       ucCardStatus;

    if (USIMM_PHYCARD_TYPE_NOCARD == g_stPihCardInfo.enPhyCardType)
    {
        ucCardStatus = SI_PIH_PCSC_SIM_ABSENT;
    }
    else
    {
        ucCardStatus = SI_PIH_PCSC_SIM_PRESENT;
    }

    SI_PIH_PCSCDataCnf(pstMsg->ulCmdType,
                        VOS_OK,
                        sizeof(VOS_UINT8),
                        &ucCardStatus);

    return;
}


VOS_VOID SI_PIH_PCSC_GetATR(
    SI_PIH_PCSC_REQ_STRU                *pstMsg)
{
    VOS_INT32                           lSCIResult;
    VOS_UINT32                          ulATRLen = 0;
    VOS_UINT8                           aucATR[USIMM_ATR_MAX_LEN];
    SCI_ATRINFO_S                       stSCIATRInfo;

    /*lint -e534*/
    (VOS_VOID)VOS_MemSet(&stSCIATRInfo, 0, sizeof(stSCIATRInfo));
    /*lint +e534*/

    lSCIResult = (VOS_INT32)mdrv_sci_get_atr((VOS_ULONG*)&ulATRLen,
                                              aucATR,
                                              &stSCIATRInfo);

    if (USIMM_SCI_SUCCESS != lSCIResult)
    {
        SI_PIH_PCSCDataCnf(pstMsg->ulCmdType,
                            (VOS_UINT32)lSCIResult,
                            VOS_NULL,
                            VOS_NULL_PTR);
    }
    else
    {
        /* Add by H00300778 for MultiAppSync Begin 2015-05-12 */
        SI_PIH_PCSCDataCnf(pstMsg->ulCmdType,
                           (VOS_UINT32)lSCIResult,
                           (ulATRLen + stSCIATRInfo.tckLen),
                           aucATR);
        /* Add by H00300778 for MultiAppSync End 2015-05-12 */
    }

    return;
}


VOS_VOID SI_PIH_PCSC_GetPara(
    SI_PIH_PCSC_REQ_STRU                *pstMsg)
{
    VOS_UINT8  aucSimPara[5];

    /*lint -e534*/
    mdrv_sci_get_parameter(aucSimPara);
    /*lint +e534*/

    SI_PIH_PCSCDataCnf(pstMsg->ulCmdType, VOS_OK, sizeof(aucSimPara), aucSimPara);

    return;
}


VOS_VOID SI_PIH_PCSC_GetClkFreq(
    SI_PIH_PCSC_REQ_STRU                *pstMsg)
{
    VOS_UINT8   aucSimClkFreq[16];
    VOS_UINT32  ulLen = 0;
    VOS_UINT32  ulResult;

    ulResult = mdrv_sci_get_clkfreq((VOS_ULONG*)&ulLen, aucSimClkFreq);

    SI_PIH_PCSCDataCnf(pstMsg->ulCmdType, ulResult, ulLen, aucSimClkFreq);

    return;
}


VOS_VOID SI_PIH_PCSC_GetBaudRate(
    SI_PIH_PCSC_REQ_STRU                *pstMsg)
{
    VOS_UINT8   aucSimBaudRate[16];
    VOS_UINT32  ulLen = 0;
    VOS_UINT32  ulResult;

    ulResult = mdrv_sci_get_baudrate((VOS_ULONG*)&ulLen, aucSimBaudRate);

    SI_PIH_PCSCDataCnf(pstMsg->ulCmdType, ulResult, ulLen, aucSimBaudRate);

    return;
}



VOS_VOID SI_PIH_PCSC_ApduCmd(
    SI_PIH_PCSC_REQ_STRU                *pstMsg)
{
    VOS_UINT32                          ulResult = VOS_ERR;
    VOS_UINT32                          ulLen = 0;
    VOS_UINT8                           aucContent[260]={0};/* ������SW״̬�� */
    USIMM_TPDU_DATA_STRU                stTpduData;
    USIMM_FILEPATH_INFO_STRU            stFilePath;

    /*lint -e534*/
    VOS_MemSet(&stTpduData, 0, sizeof(stTpduData));
    VOS_MemSet(&stFilePath, 0, sizeof(stFilePath));
    /*lint +e534*/

    ulResult = SI_PIH_PCSCApduCheck(&pstMsg->ulCmdLen,
                                    pstMsg->aucAPDU,
                                    &ulLen,
                                    aucContent);

    if(ulResult != VOS_OK)
    {
        SI_PIH_PCSCDataCnf(pstMsg->ulCmdType, VOS_OK, ulLen, aucContent);

        return;
    }

    /* ���ڻ����Get Response���ݣ�������һ��ִ�е��Ƕ�Ӧ��Case4 APDU��ֱ�ӻظ� */
    if ((0xC0 == pstMsg->aucAPDU[1]) && (0 != g_stPIHCSIMCtrlInfo.usRspLen))
    {
        /*lint -e534*/
        VOS_MemCpy(aucContent,
                    g_stPIHCSIMCtrlInfo.aucRspCotent,
                    g_stPIHCSIMCtrlInfo.usRspLen);
        /*lint +e534*/

        ulLen = ((pstMsg->aucAPDU[4] < g_stPIHCSIMCtrlInfo.usRspLen)?
                            pstMsg->aucAPDU[4] :g_stPIHCSIMCtrlInfo.usRspLen) + 2;

        aucContent[ulLen-2] = 0x90;    /* ������ǰ��SW�ֽ�������β */

        aucContent[ulLen-1] = 0x00;

        SI_PIH_PCSCDataCnf(pstMsg->ulCmdType, ulResult, ulLen, aucContent);

        return;
    }

    if (pstMsg->ulCmdLen <= USIMM_TPDU_HEAD_LEN)
    {
        /*lint -e534*/
        VOS_MemCpy(stTpduData.aucTPDUHead, pstMsg->aucAPDU, pstMsg->ulCmdLen);
        /*lint +e534*/
    }
    else
    {
        /*lint -e534*/
        VOS_MemCpy(stTpduData.aucTPDUHead, pstMsg->aucAPDU, USIMM_TPDU_HEAD_LEN);

        stTpduData.usDataLen = (VOS_UINT16)(pstMsg->ulCmdLen-USIMM_TPDU_HEAD_LEN);

        VOS_MemCpy(stTpduData.aucData, &pstMsg->aucAPDU[USIMM_TPDU_HEAD_LEN], pstMsg->ulCmdLen-USIMM_TPDU_HEAD_LEN);
        /*lint +e534*/
    }

    ulResult = SI_PIH_SendTPDUReq(USIMM_UNLIMIT_AUTO,
                                  SI_PIH_SEND_PAPA(g_pstPIHCurrNode->usClient, g_pstPIHCurrNode->ulEventType),
                                  &g_stPIHCSIMCtrlInfo.stFilePath,
                                  &stTpduData);

    if(ulResult != VOS_OK)
    {
        PIH_ERROR_LOG("SI_PIH_PCSC_ApduCmd: The Command Send is Error");

        SI_PIH_PCSCDataCnf(pstMsg->ulCmdType, VOS_ERR, 0, VOS_NULL_PTR);
    }

    return;
}
static const PUSIMPCSCPROC  af_PIH_PCSCProc[] =
{
    SI_PIH_PCSC_PowerOn,
    SI_PIH_PCSC_PowerOff,
    SI_PIH_PCSC_SimQuiry,
    SI_PIH_PCSC_ApduCmd,
    SI_PIH_PCSC_GetATR,
    SI_PIH_PCSC_GetPara,
    SI_PIH_PCSC_GetClkFreq,
    SI_PIH_PCSC_GetBaudRate
};

VOS_UINT32 SI_PIH_PCSCCmdHandle(
    SI_PIH_PCSC_REQ_STRU                *pstMsg)
{
    if (pstMsg->ulCmdType >= SI_PIH_PCSC_CMD_BUTT)
    {
        return VOS_ERR;
    }

    af_PIH_PCSCProc[pstMsg->ulCmdType](pstMsg);

    return VOS_OK;
}

/*****************************************************************************
�� �� ��  : SI_PIH_HVSSTQueryHandle
��������  : AT/APP HVSST Query��������
�������  : pMsg ��Ϣ����
�������  : ��
�� �� ֵ  : VOS_UINT32 ����ִ�н��
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2013��03��20��
  ��    ��  : zhuli
  �޸�����  : Create
2.��    ��  : 2014��10��9��
  ��    ��  : zhuli
  �޸�����  : �������ɲ�ƷҪ�󣬸ýӿڲ��ܺ����
*****************************************************************************/
VOS_UINT32 SI_PIH_HVSSTQueryHandle(
    SI_PIH_MSG_HEADER_STRU              *pMsg
)
{
    SI_PIH_EVENT_INFO_STRU  stEvent;
    VOS_BOOL                bVSimState;

    /*lint -e534*/
    VOS_MemSet(&stEvent, 0, sizeof(stEvent));
    /*lint +e534*/

    stEvent.PIHError = TAF_ERR_NO_ERROR;  /*��ѯ����Ĭ�Ϸ���OK*/

    bVSimState = USIMM_VsimIsActive();

    /*vSIM״̬���*/
    if (VOS_TRUE == bVSimState)
    {
        stEvent.PIHEvent.HVSSTQueryCnf.enVSimState = SI_PIH_SIM_ENABLE;
    }
    else
    {
        stEvent.PIHEvent.HVSSTQueryCnf.enVSimState = SI_PIH_SIM_DISABLE;
    }

    /*ֻҪ�����޿�������Ϊ����*/
    if (USIMM_PHYCARD_TYPE_NOCARD == g_stPihCardInfo.enPhyCardType)
    {
        stEvent.PIHEvent.HVSSTQueryCnf.enCardUse   = SI_PIH_CARD_NOUSE;
    }
    else
    {
        stEvent.PIHEvent.HVSSTQueryCnf.enCardUse   = SI_PIH_CARD_USE;
    }

    /*����ظ�*/
    return SI_PIH_EventCallBack(&stEvent);
}

/*****************************************************************************
�� �� ��  : SI_PIH_HVSSTStateCheck
��������  : �ж��Ƿ���Ҫ���м����ȥ���������״̬���
�������  : bIsHandleVSim  �������Ƿ������⿨
            enIsActiveCard �����ȥ�������
            pstEvent       ���ظ�ATģ����¼�
�������  : ��
�� �� ֵ  : VOS_TRUE : ��Ҫ�����ȥ�������
            VOS_FALSE: ����Ҫ�����ȥ�������
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2013��03��20��
  ��    ��  : zhuli
  �޸�����  : Create
2.��    ��  : 2014��10��9��
  ��    ��  : zhuli
  �޸�����  : �������ɲ�ƷҪ�󣬸ýӿڲ��ܺ����
*****************************************************************************/
VOS_BOOL SI_PIH_HVSSTStateCheck(
    SI_PIH_HVSST_REQ_STRU               *pMsg,
    SI_PIH_EVENT_INFO_STRU              *pstEvent
)
{
    SI_PIH_HVSST_HANDLE_STATE_ENUM_UINT8    enValue = 0;
    VOS_BOOL                                bVsimState;

    if(SI_PIH_SIM_ENABLE == pMsg->stHvSSTData.enSIMSet)
    {
        PIH_NORMAL_LOG("SI_PIH_HVSSTStateCheck: Active Card:");

        PIH_SET_BIT(enValue, BIT_ACTIVECARD);
    }

    /*�жϵ�ǰ�Ĳ������Ƿ�vSIM��*/
    if(pMsg->stHvSSTData.ucIndex != SI_PIH_SIM_REAL_SIM1)
    {
        PIH_NORMAL_LOG("SI_PIH_HVSSTStateCheck: Handle VSIM Card:");

        PIH_SET_BIT(enValue, BIT_HANDLEVSIM);
    }

    bVsimState = USIMM_VsimIsActive();

    if(VOS_TRUE == bVsimState)
    {
        PIH_NORMAL_LOG("SI_PIH_HVSSTStateCheck: Vsim is Active");

        PIH_SET_BIT(enValue, BIT_VSIMSTATE);
    }

    if (USIMM_PHYCARD_TYPE_NOCARD != g_stPihCardInfo.enPhyCardType)
    {
        PIH_NORMAL1_LOG("SI_PIH_HVSSTStateCheck: Card is Active %d",
                            (VOS_INT)g_stPihCardInfo.enPhyCardType);

        PIH_SET_BIT(enValue, BIT_CURCARDOK);
    }

    PIH_NORMAL1_LOG("SI_PIH_HVSSTStateCheck: HVSST Bit Map is :",
                            (VOS_INT32)enValue);

    /*����Ҫ�����ķ��أ�������ȷ�ظ�*/
    if((SI_PIH_HVSST_DEACTIVE_RSIM_AGAIN        == enValue)
        ||(SI_PIH_HVSST_DEACTIVE_VSIM_AGAIN     == enValue)
        ||(SI_PIH_HVSST_ACTIVE_VSIM_AGAIN2      == enValue))
    {
        pstEvent->PIHError = TAF_ERR_NO_ERROR;

        return VOS_FALSE;
    }
    /*��Ҫ�����ķ���*/
    if((SI_PIH_HVSST_DEACTIVE_RSIM     == enValue)
        ||(SI_PIH_HVSST_DEACTIVE_VSIM       == enValue)
        ||(SI_PIH_HVSST_ACTIVE_RSIM         == enValue)
        ||(SI_PIH_HVSST_ACTIVE_VSIM         == enValue)
        ||(SI_PIH_HVSST_ACTIVE_VSIM_AGAIN   == enValue)
        ||(SI_PIH_HVSST_ACTIVE_RSIM_AGAIN2  == enValue))
    {
        return VOS_TRUE;
    }

    pstEvent->PIHError = TAF_ERR_PARA_ERROR;

    PIH_WARNING_LOG("SI_PIH_HVSSTStateCheck: Not able to Process Command");

    return VOS_FALSE;
}

/*****************************************************************************
�� �� ��  : SI_PIH_HVSSTQueryHandle
��������  : AT/APP HVSST Set��������
�������  : pMsg ��Ϣ����
�������  : ��
�� �� ֵ  : VOS_UINT32 ����ִ�н��
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2013��03��20��
  ��    ��  : zhuli
  �޸�����  : Create
2.��    ��  : 2014��10��9��
  ��    ��  : zhuli
  �޸�����  : �������ɲ�ƷҪ�󣬸ýӿڲ��ܺ����
*****************************************************************************/
VOS_UINT32 SI_PIH_HVSSTSetHandle(
    SI_PIH_HVSST_REQ_STRU               *pMsg
)
{
    SI_PIH_EVENT_INFO_STRU              stEvent;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          i;
    SI_PIH_SIM_STATE_ENUM_UINT8         enVSIMSet;
    VOS_UINT8                           ucCardState;

    /*lint -e534*/
    VOS_MemSet(&stEvent, 0, sizeof(stEvent));
    /*lint +e534*/

    stEvent.PIHError = TAF_ERR_NO_ERROR; /* �ȸ�ֵ�ɹ� */

    ulResult = SI_PIH_HVSSTStateCheck(pMsg, &stEvent);

    /* �жϵ�ǰ״̬�Ƿ���Ҫ���п����� */
    if (VOS_FALSE == ulResult)
    {
        PIH_NORMAL_LOG("SI_PIH_HVSSTSetHandle: No need handle this msg");

        return SI_PIH_EventCallBack(&stEvent);
    }

    /*��Ҫ��״̬��¼��NV��*/
    if(SI_PIH_SIM_ENABLE == pMsg->stHvSSTData.enSIMSet) /*ʹ��SIM ��*/
    {
        if(pMsg->stHvSSTData.ucIndex == SI_PIH_SIM_REAL_SIM1)   /*Ӳ��*/
        {
            enVSIMSet = SI_PIH_SIM_DISABLE;
        }
        else
        {
            enVSIMSet = SI_PIH_SIM_ENABLE;
        }

        if(NV_OK != NV_WritePart(en_NV_Item_VSIM_SUPPORT_FLAG, 0, &enVSIMSet, sizeof(VOS_UINT8)))
        {
            stEvent.PIHError = TAF_ERR_CAPABILITY_ERROR;

            return SI_PIH_EventCallBack(&stEvent);
        }
    }

    /*������ʼ����USIMM�ӿ�*/
    if(SI_PIH_SIM_ENABLE == pMsg->stHvSSTData.enSIMSet)
    {
        PIH_NORMAL_LOG("SI_PIH_HVSSTSetHandle: Active SIM Card");

        if(USIMM_API_SUCCESS != SI_PIH_SendActiveCardReqMsg(SI_PIH_SEND_PAPA(g_pstPIHCurrNode->usClient, g_pstPIHCurrNode->ulEventType)))
        {
            stEvent.PIHError = TAF_ERR_ERROR;  /*��ֵʧ��*/

            PIH_WARNING_LOG("SI_PIH_HVSSTSetHandle: USIMM_ActiveCardReq Return Error");

            return SI_PIH_EventCallBack(&stEvent);
        }

        if(pMsg->stHvSSTData.ucIndex == SI_PIH_SIM_REAL_SIM1)
        {
            g_stPIHProtectCtrl.enProtectFun = SI_PIH_PROTECT_ENABLE;    /*����Ӳ�����´򿪱����Ը�λ����*/
        }
    }
    else
    {
        PIH_NORMAL_LOG("SI_PIH_HVSSTSetHandle: Deactive SIM Card");

        if(USIMM_API_SUCCESS != SI_PIH_SendDeactiveReqMsg(SI_PIH_SEND_PAPA(g_pstPIHCurrNode->usClient, g_pstPIHCurrNode->ulEventType)))
        {
            stEvent.PIHError = TAF_ERR_ERROR;  /*��ֵʧ��*/

            PIH_WARNING_LOG("SI_PIH_HVSSTSetHandle: USIMM_DeactiveCardReq Return Error");

            return SI_PIH_EventCallBack(&stEvent);
        }

#if (VOS_OS_VER != VOS_WIN32)       /* PC Stub */
        HPA_USIMLowPowerLock(MAPS_PIH_PID);
#endif

        for(i=0; i<SI_PIH_GETCARDSTATUS_MAX; i++)
        {
            /*��ȡ��ǰSIM����״̬*/
            (VOS_VOID)USIMM_GetCardTypeByAppType(&ucCardState, VOS_NULL_PTR, USIMM_GUTL_APP);

            /*����ǰ���Ѿ�ȥ���֪ͨAP�������*/
            if (USIMM_CARD_SERVIC_ABSENT == ucCardState)
            {
                break;
            }

            (VOS_VOID)VOS_TaskDelay(SI_PIH_TASKDELAY_TIMER_LEN);
        }

#if (VOS_OS_VER != VOS_WIN32)       /* PC Stub */
        HPA_USIMLowPowerUnLock(MAPS_PIH_PID);
#endif

        if (i >= SI_PIH_GETCARDSTATUS_MAX)
        {
            stEvent.PIHError = TAF_ERR_TIME_OUT;
        }

        (VOS_VOID)SI_PIH_EventCallBack(&stEvent);
    }

    PIH_NORMAL_LOG("SI_PIH_HVSSTSetHandle: Wait USIMM Return Msg");

    return VOS_OK;
}

/*****************************************************************************
�� �� ��  : SI_PIH_SciCfgSetHandle
��������  : AT/APP SCICFG Set��������
�������  : pMsg ��Ϣ����
�������  : ��
�� �� ֵ  : VOS_UINT32 ����ִ�н��
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2014��10��9��
  ��    ��  : zhuli
  �޸�����  : �������ɲ�ƷҪ������
*****************************************************************************/
VOS_UINT32 SI_PIH_SciCfgSetHandle(
    SI_PIH_SCICFG_SET_REQ_STRU          *pstMsg
)
{
    SI_PIH_EVENT_INFO_STRU              stEvent;
    VOS_UINT32                          ulResult = VOS_ERR;

    /*lint -e534*/
    VOS_MemSet(&stEvent, 0, sizeof(stEvent));
    /*lint +e534*/

    /*����ǰ��δȥ���֪ͨAP�������*/
    if (USIMM_PHYCARD_TYPE_NOCARD != g_stPihCardInfo.enPhyCardType)
    {
        PIH_ERROR_LOG("SI_PIH_SciCfgSetHandle: card is running");

        stEvent.PIHError    = TAF_ERR_SIM_BUSY;
    }
    else
    {
        /*���������ӿ�*/
        /*lint -e732*/
        ulResult = mdrv_sci_slot_switch((SCI_SLOT)pstMsg->enCard0Slot,
                                        (SCI_SLOT)pstMsg->enCard1Slot,
                                        (SCI_SLOT)pstMsg->enCard2Slot);
        /*lint +e732*/

        if (VOS_OK == ulResult)
        {
            stEvent.PIHError    = TAF_ERR_NO_ERROR;
        }
        else
        {
            PIH_ERROR1_LOG("SI_PIH_SciCfgSetHandle: DRV API Return %d",
                            (VOS_INT32)ulResult);

            stEvent.PIHError    = TAF_ERR_SIM_BUSY;
        }
    }

    PIH_INFO_LOG("SI_PIH_SciCfgSetHandle: Return Event");

    return SI_PIH_EventCallBack(&stEvent);
}

/*****************************************************************************
�� �� ��  : SI_PIH_SciCfgQueryHandle
��������  : AT/APP SCICFG Query��������
�������  : pMsg ��Ϣ����
�������  : ��
�� �� ֵ  : VOS_UINT32 ����ִ�н��
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2014��10��9��
  ��    ��  : zhuli
  �޸�����  : �������ɲ�ƷҪ������
*****************************************************************************/
VOS_UINT32 SI_PIH_SciCfgQueryHandle(
    SI_PIH_MSG_HEADER_STRU              *pstMsg
)
{
    SI_PIH_EVENT_INFO_STRU              stEvent;
    VOS_UINT32                          ulResult = VOS_ERR;

    /*lint -e534*/
    VOS_MemSet(&stEvent, 0, sizeof(stEvent));
    /*lint +e534*/

    /*���������ӿ�*/
    /*lint -e732*/
    ulResult = mdrv_sci_get_slot_state((SCI_SLOT *)&stEvent.PIHEvent.SciCfgCnf.enCard0Slot,
                                       (SCI_SLOT *)&stEvent.PIHEvent.SciCfgCnf.enCard1Slot,
                                       (SCI_SLOT *)&stEvent.PIHEvent.SciCfgCnf.enCard2Slot);
    /*lint +e732*/

    if (VOS_OK == ulResult)
    {
        stEvent.PIHError    = TAF_ERR_NO_ERROR;
    }
    else
    {
        PIH_ERROR1_LOG("SI_PIH_SciCfgQueryHandle: DRV API Return %d",
                        (VOS_INT32)ulResult);

        stEvent.PIHError    = TAF_ERR_SIM_BUSY;
    }

    PIH_INFO_LOG("SI_PIH_SciCfgQueryHandle: Return Event");

    return SI_PIH_EventCallBack(&stEvent);
}

/*****************************************************************************
�� �� ��  : SI_PIH_ActiveSimCnfProc
��������  :
�������  : pstMsg
�������  : ��
�� �� ֵ  : VOS_UINT32 ����ִ�н��
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2010��08��20��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/
VOS_VOID SI_PIH_ActiveSimCnfProc(
    USIMM_SINGLECMD_CNF_STRU            *pMsg)
{
    SI_PIH_EVENT_INFO_STRU  stEvent;

    (VOS_VOID)VOS_MemSet(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));

    if (VOS_OK == pMsg->stCmdResult.ulResult)
    {
        stEvent.PIHError = TAF_ERR_NO_ERROR;
    }
    else
    {
        stEvent.PIHError = TAF_ERR_SIM_FAIL;
    }

    (VOS_VOID)SI_PIH_EventCallBack(&stEvent);

    return;
}


VOS_VOID SI_PIH_BcdNumToAsciiNum(
    VOS_UINT8                           *pucAsciiNum,
    VOS_UINT8                           *pucBcdNum,
    VOS_UINT8                           ucBcdNumLen)
{
    VOS_UINT8       ucTmp;
    VOS_UINT8       ucFirstNumber;
    VOS_UINT8       ucSecondNumber;

    for (ucTmp = 0; ucTmp < ucBcdNumLen; ucTmp++)
    {
        ucFirstNumber = (VOS_UINT8)((*(pucBcdNum + ucTmp)) & 0x0f);             /*low four bits*/
        ucSecondNumber = (VOS_UINT8)(((*(pucBcdNum + ucTmp)) >> 4) & 0x0f);   /*high four bits*/
        if (ucFirstNumber <= 9)
        {
            *pucAsciiNum = ucFirstNumber + 0x30;
            pucAsciiNum++;
        }
        else if (0xa == ucFirstNumber)            /* the key is '*' */
        {
            *pucAsciiNum = 0x2a;
            pucAsciiNum++;
        }
        else if (0xb == ucFirstNumber)            /* the key is '#' */
        {
            *pucAsciiNum = 0x23;
            pucAsciiNum++;
        }
        else                                     /* the key is 'a','b'or 'c' */
        {
            *pucAsciiNum = ucFirstNumber + 0x57;
            pucAsciiNum++;
        }

        /* the following proceed the second number */
        if (0xf == ucSecondNumber)
        {
            break;
        }
        if (ucSecondNumber <= 9)
        {
            *pucAsciiNum = ucSecondNumber + 0x30;
            pucAsciiNum++;
        }
        else if (0xa == ucSecondNumber)            /* the key is '*' */
        {
            *pucAsciiNum = 0x2a;
            pucAsciiNum++;
        }
        else if (0xb == ucSecondNumber)            /* the key is '#' */
        {
            *pucAsciiNum = 0x23;
            pucAsciiNum++;
        }
        else                                     /* the key is 'a','b'or 'c' */
        {
            *pucAsciiNum = ucSecondNumber + 0x57;
            pucAsciiNum++;
        }
    }

    *pucAsciiNum = '\0';

    return;
}
VOS_UINT32 SI_PIH_ImsiBcd2Ascii(
    VOS_UINT8                           ucLen,
    VOS_UINT8                           *pucNum,
    VOS_UINT8                           *pucAsciiStr)
{
    VOS_UINT32  ulI     = 0;
    VOS_UINT8   ucTmp   = 0;

    /*��Ч���ж�*/
    if ( (VOS_NULL_PTR == pucNum)
       ||(VOS_NULL_PTR == pucAsciiStr)
       ||(           0 == ucLen )
       )
    {
        PIH_WARNING_LOG("SI_PIH_ImsiBcd2Ascii():WARNING:NULL PTR");
        return VOS_ERR;
    }

    /*�����ƶ��û�ʶ����*/
    /*��մ���ַ����Ļ�����*/
    for ( ulI = 0; ulI < (VOS_UINT32)ucLen; ulI++ )
    {
        pucAsciiStr[ulI] = 0;
    }

    ucTmp = (*pucNum >> 4) & 0x0f;

    /*ȡ����һλ*/
    SI_PIH_BcdNumToAsciiNum(pucAsciiStr, &ucTmp, 1);

    /*����Bcd��Ascii��ת��*/
    SI_PIH_BcdNumToAsciiNum(pucAsciiStr + 1, pucNum + 1, (ucLen - 1)/2);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : SI_PIH_ChangeNum
 ��������  : ����Э��ƻ�ԭ��ֵ
 �������  : ulSrcValude  -- BCD�볤��
             ulCodeMode   -- BCD���ŵ�λ��

 �������  : ��
 �� �� ֵ  : VOS_UINT32 -����Э�黹ԭ����ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��28��
    ��    ��   :
    �޸�����   : Create
*****************************************************************************/
VOS_UINT32 SI_PIH_ChangeNum(VOS_UINT32 ulSrcValude, VOS_UINT32 ulCodeMode)
{
    VOS_UINT32                          ulTempl   = 0;
    VOS_UINT32                          ulDstValue = 0;

    if (ulCodeMode >= 3)
    {
        ulTempl = ulSrcValude / 100;        /*��λ*/
        if (ulTempl + 1 <= 9)
        {
            ulDstValue += (ulTempl + 1) * 100;
        }
    }

    if (ulCodeMode >= 2)
    {
        ulTempl = (ulSrcValude / 10)  % 10; /*ʮλ*/
        if ( ulTempl+1 <= 9)
        {
            ulDstValue += (ulTempl+1 ) * 10;
        }
    }

    if (ulCodeMode >= 1)
    {
        ulTempl = ulSrcValude % 10;         /*��λ*/
        if (ulTempl +1 <= 9)
        {
            ulDstValue += ulTempl +1;
        }
    }

    return ulDstValue;
}
VOS_UINT32 SI_PIH_CImsiBcd2Ascii(
    VOS_UINT8                           *pucCIMSI,
    VOS_UINT8                           *pucStrCIMSI)
{
    VOS_UINT32                          ulMCC     = 0; /* ���Ҵ��� */
    VOS_UINT32                          ulMNC     = 0; /* ������� */
    VOS_UINT32                          ulMSIN_A  = 0; /* �ƶ��û���ݵ�0 - 3λ*/
    VOS_UINT32                          ulMSIN_B  = 0; /* �ƶ��û���ݵ�4 - 10λ*/
    VOS_UINT32                          ulMSIN_B1 = 0; /* �ƶ��û���ݵ�4 - 6λ*/
    VOS_UINT32                          ulMSIN_B2 = 0; /* �ƶ��û���ݵ�7λ*/
    VOS_UINT32                          ulMSIN_B3 = 0; /* �ƶ��û���ݵ�8 - 10λ*/

    if ((VOS_NULL_PTR == pucCIMSI) || (VOS_NULL_PTR == pucStrCIMSI))
    {
        return VOS_ERR;
    }
/*
    6F22��ʽ��
    00 AA AA BB BB BB CC 80 DD DD

    00����CLASS=0
    AA AA����MINǰ3λ����
    BB BB BB����MIN��7λ����
    CC����MNC����
    80����IMSI_M_PROGRAMMED=1��IMSI_M_ADD_NUM=0

    DD DD����MCC����
    ����CDMA2000Э����6F22�ĸ�ʽ����1���ֽں͵�7���ֽڶ��ø㶨���������Ǳ�־λ�����á�

    ����AA AA����
    1����MIN��ǰ3λΪ�������ݣ��ָ��3����λ�����ֱ�����ΪD1��D2��D3
    2����������NUM = D1 * 100 + D2 * 10 + D3 - 111����D1��D2��D3�г���0������10���㣩
    3����NUMת��Ϊ2�ֽ�С�˸�ʽ16���ƣ�λ��������ǰ����0����AA AA�������

    ����BB BB BB����
    1����MIN��4-6λΪ���ݣ�����AA AA�ļ��㲽��1��2���NUM����NUMת��Ϊ10bit��2���ƣ�������0��
    2����MIN��7λ����ȡ���������ձ�׼10����ת2���Ƶļ��㷽���������4bit��2���ƣ�������0��(�����������0������10����)
    3����MIN��8-10λΪ���ݣ�����AA AA�ļ��㲽��1��2���NUM����NUMת��Ϊ10bit��2���ƣ�������0��
    4����ǰ3���ļ�������Ĺ�24bit��2������ƴ������ת����3�ֽ�С�˸�ʽ16��������BB BB BB�������

    ����CC����
    1����MNC�ָ��2����λ�����ֱ�����ΪD1��D2
    2����������NUM = D1 * 10 + D2 - 11����D1��D2�г���0������10���㣩
    3����NUMת��Ϊ1�ֽ�16���ơ�CC�������

    ����DD DD����
    1����MCCΪ���ݣ�����AA AA�ļ��㷽���������2�ֽ�С�˸�ʽ16���ƣ���ΪDD DD

    ���ӣ�
    ��֪IMSI�ţ�460036591141482
    ��IMSI�У�
    MCC��460
    MNC��03
    MIN��6591141482

    ����AA AA
    MINǰ3λ659��NUM = 6 * 100 + 5 * 10 + 9 - 111 = 548 ת����2�ֽ�С�˸�ʽ16����Ϊ��24 02

    ����BB BB BB
    MIN��4-6λ114��NUM = 1 * 100 + 1 * 10 + 4 - 111 = 3 ת����10bit��2����Ϊ��0000000011
    MIN��7λ1��ת��Ϊ4bit��2����Ϊ��0001
    MIN��8-10λ482��NUM = 4 * 100 + 8 * 10 + 2 - 111 = 371 ת����10bit��2����Ϊ��0101110011
    24bit��2������Ϊ��000000001100010101110011��ת����3�ֽ�С�˸�ʽ16����Ϊ��73 C5 00

    ����CC
    MNCΪ03��NUM = 10 * 10 + 3 - 11 = 92��ת����1�ֽ�16����Ϊ5C

    ����DD DD
    MCCΪ460��NUM = 4 * 100 + 6 * 10 + 10 - 111 = 359 ת����2�ֽ�С�˸�ʽ16����Ϊ��67 01

    ���˵õ�6F22�ļ�����ӦΪ
    00 24 02 73 C5 00 5C 80 67 01
    460036591141482
*/
    ulMCC     = pucCIMSI[8];
    ulMCC     = 0x0000FFFF & ( ulMCC | (pucCIMSI[9] << 8));
    ulMCC     = SI_PIH_ChangeNum(ulMCC,3);       /* ���Ҵ��� */

    ulMNC     = pucCIMSI[6];
    ulMNC     = SI_PIH_ChangeNum(ulMNC,2);       /* ������� */

    ulMSIN_A  = pucCIMSI[1];
    ulMSIN_A  = 0x0000FFFF & ( ulMSIN_A | (pucCIMSI[2] << 8));
    ulMSIN_A  = SI_PIH_ChangeNum(ulMSIN_A, 3);   /* �ƶ��û���ݵ�0 - 3λ*/

    ulMSIN_B  = pucCIMSI[3];
    ulMSIN_B  = 0x0000FFFF & (ulMSIN_B | (pucCIMSI[4] << 8));
    ulMSIN_B  = 0x00FFFFFF & (ulMSIN_B | (pucCIMSI[5] << 16));

    ulMSIN_B1 = ulMSIN_B >> 14;
    ulMSIN_B1 = SI_PIH_ChangeNum(ulMSIN_B1, 3); /* �ƶ��û���ݵ�4 - 6λ */

    ulMSIN_B2 = (ulMSIN_B & 0x3c00)>>10;         /* �ƶ��û���ݵ�7λ */
    ulMSIN_B2 = ulMSIN_B2 % 10;

    ulMSIN_B3 = ulMSIN_B & 0x3FF;
    ulMSIN_B3 = SI_PIH_ChangeNum(ulMSIN_B3, 3);  /* �ƶ��û���ݵ�8 - 10λ */

#if (VOS_WIN32 == VOS_OS_VER)
    sprintf((VOS_CHAR*)pucStrCIMSI,      "%03d", ulMCC);
    sprintf((VOS_CHAR*)pucStrCIMSI + 3,  "%02d", ulMNC);
    sprintf((VOS_CHAR*)pucStrCIMSI + 5,  "%03d", ulMSIN_A);
    sprintf((VOS_CHAR*)pucStrCIMSI + 8,  "%03d", ulMSIN_B1);
    sprintf((VOS_CHAR*)pucStrCIMSI + 11, "%d",   ulMSIN_B2);
    sprintf((VOS_CHAR*)pucStrCIMSI + 12, "%03d", ulMSIN_B3);
#else
    (VOS_VOID)VOS_sprintf((VOS_CHAR*)pucStrCIMSI,      "%03d", ulMCC);
    (VOS_VOID)VOS_sprintf((VOS_CHAR*)pucStrCIMSI + 3,  "%02d", ulMNC);
    (VOS_VOID)VOS_sprintf((VOS_CHAR*)pucStrCIMSI + 5,  "%03d", ulMSIN_A);
    (VOS_VOID)VOS_sprintf((VOS_CHAR*)pucStrCIMSI + 8,  "%03d", ulMSIN_B1);
    (VOS_VOID)VOS_sprintf((VOS_CHAR*)pucStrCIMSI + 11, "%d",   ulMSIN_B2);
    (VOS_VOID)VOS_sprintf((VOS_CHAR*)pucStrCIMSI + 12, "%03d", ulMSIN_B3);
#endif

    return VOS_OK;
}

#if (FEATURE_ON == FEATURE_VSIM)


VOS_VOID SI_PIH_DecodeImsiHPLMN(
    VOS_UINT8                           *pucImsi,
    VOS_UINT8                           ucMNCLen,
    SI_PIH_CARD_CONTENT_STRU            *pstCardCont)
{
    /* ��IMSIת��ΪASCII�� */
    (VOS_VOID)SI_PIH_ImsiBcd2Ascii((VOS_UINT8)(pucImsi[0]*2), &pucImsi[1], pstCardCont->aucImsi);

    /* ���HPLMN */
    pstCardCont->astPlmn[0].ulMCC |= (pucImsi[1] & 0xF0) >> 0x04;
    pstCardCont->astPlmn[0].ulMCC |= (pucImsi[2] & 0x0F) << 0x08;
    pstCardCont->astPlmn[0].ulMCC |= (pucImsi[2] & 0xF0) << 0x0c;
    pstCardCont->astPlmn[0].ulMNC |= (pucImsi[3] & 0x0F);
    pstCardCont->astPlmn[0].ulMNC |= (pucImsi[3] & 0xF0) << 0x04;

    if (SI_PIH_MNC_TWO_BYTES_LEN == ucMNCLen)
    {
        pstCardCont->astPlmn[0].ulMNC |= (0x0f) << 0x10;
    }
    else
    {
        pstCardCont->astPlmn[0].ulMNC |= (pucImsi[4] & 0x0f) << 0x10;
    }

    pstCardCont->usPlmnNum++;

    return;
}


VOS_VOID SI_PIH_DecodeEHPLMN(
    VOS_UINT8                           *pucData,
    VOS_UINT32                          ulDateLen,
    SI_PIH_CARD_CONTENT_STRU            *pstCardCont)
{
    VOS_UINT32                          ulEHplmnNum;
    VOS_UINT32                          ulIndex;

    /* ��ȡ�Ŀ��ļ����Ȳ��Ϸ���ֱ�ӷ���VOS_FALSE */
    if ((ulDateLen < SI_PIH_EHPLMN_BYTE_NUM)
     || (0 != (ulDateLen % SI_PIH_EHPLMN_BYTE_NUM)))
    {
        PIH_ERROR1_LOG("SI_PIH_DecodeEHPLMN: the EFEHPLMN file is incorrect.", (VOS_INT32)ulDateLen);
        return ;
    }

    ulEHplmnNum = ulDateLen/SI_PIH_EHPLMN_BYTE_NUM;

    /* ����HPLMN�Ѿ�ռ��һ����Ԫ��������Ҫ���м�1���� */
    if (ulEHplmnNum > (SI_PIH_HPLMN_MAX_NUM - 1))
    {
        ulEHplmnNum = (SI_PIH_HPLMN_MAX_NUM - 1);
    }

    for (ulIndex = 1; ulIndex <= ulEHplmnNum; ulIndex++)
    {
        pstCardCont->astPlmn[ulIndex].ulMCC |= (pucData[0] & 0x0F);
        pstCardCont->astPlmn[ulIndex].ulMCC |= (pucData[0] & 0xF0) << 0x04;
        pstCardCont->astPlmn[ulIndex].ulMCC |= (pucData[1] & 0x0F) << 0x10;

        pstCardCont->astPlmn[ulIndex].ulMNC |= (pucData[1] & 0xF0) << 0x0C;
        pstCardCont->astPlmn[ulIndex].ulMNC |= (pucData[2] & 0x0F);
        pstCardCont->astPlmn[ulIndex].ulMNC |= (pucData[2] & 0xF0) << 0x04;

        pucData += SI_PIH_EHPLMN_BYTE_NUM;
    }

    pstCardCont->usPlmnNum += (VOS_UINT16)ulEHplmnNum;

    return;
}


VOS_BOOL SI_PIH_GetEHPlmnNVState(VOS_VOID)
{
    VOS_UINT16                          usEHPlmnSupportFlg;

    /* ��ȡEHPLMN�Ƿ�ʹ�ܵ�NV�� */
    if (NV_OK != NV_Read(en_NV_Item_Standard_EHplmn_Support_Flg,
                         &usEHPlmnSupportFlg,
                         sizeof(VOS_UINT16)))
    {
        PIH_ERROR_LOG("SI_PIHGetEHPlmnNVState: NV_Read EHplmn_Support fail.");
        return VOS_FALSE;
    }

    /* EHPLMN��֧�� */
    if (VOS_TRUE != usEHPlmnSupportFlg)
    {
        PIH_WARNING_LOG("SI_PIHGetEHPlmnNVState: EHplmn not Support.");
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT8 SI_PIH_GetMncLen(
    VOS_UINT8                           *pucAdContent,
    VOS_UINT32                          ulFileSize)
{
    VOS_UINT8                           ucHplmnMncLen;

    ucHplmnMncLen = SI_PIH_MNC_TWO_BYTES_LEN;

    /* �ļ���С��С����Ĭ��MNCΪ2�ֽڳ��� */
    if(USIMM_EF_AD_MIN_LEN >= ulFileSize)
    {
        return ucHplmnMncLen;
    }

    /* �ж�MNC����,MNC����Ϊ2λ��3λ */
    if ((SI_PIH_MNC_TWO_BYTES_LEN == (pucAdContent[SI_PIH_AD_MNC_LEN_POS] & 0x0F))
        || (SI_PIH_MNC_THREE_BYTES_LEN == (pucAdContent[SI_PIH_AD_MNC_LEN_POS] & 0x0F)))
    {
        ucHplmnMncLen = pucAdContent[SI_PIH_AD_MNC_LEN_POS] & 0x0F;
    }

    return ucHplmnMncLen;
}


VOS_VOID SI_PIH_GetRSimContent(
    SI_PIH_CARD_CONTENT_STRU            *pstCardCont)
{
    VOS_UINT8                           aucImsi[USIMM_EF_IMSI_LEN] = {0};
    VOS_UINT32                          ulDataLen;
    VOS_UINT8                          *pucData;
    VOS_UINT8                           ucHplmnMncLen;

    pstCardCont->ucIndex   = SI_PIH_SIM_REAL_SIM1;
    pstCardCont->ucCardCap = PIH_BIT_N(USIMM_CARD_SIM) | PIH_BIT_N(USIMM_CARD_USIM);

    /* ����VSIM���Ѿ�����������д�����ֶ� */
    if (VOS_TRUE == USIMM_VsimIsActive())
    {
        PIH_WARNING_LOG("SI_PIH_GetRSimContent: vSIM is Active.");
        return;
    }


    /* �����ͳ�����Ҫ�ķ�Χ����������ǿ��ٿ������޿�Ӧ��ֱ�ӷ��� */
    if (g_stPihCardInfo.enGUTLCardType  > USIMM_CARD_USIM)
    {
        PIH_WARNING_LOG("SI_PIH_GetRSimContent: Card type is Error.");
        return;
    }

/*lint -e701*/
    pstCardCont->ucCardType = (VOS_UINT8)PIH_BIT_N(g_stPihCardInfo.enGUTLCardType);
/*lint +e701*/

    /*  ��ȡIMSI���� */
    if (USIMM_API_SUCCESS != USIMM_GetCardIMSI(aucImsi))
    {
        PIH_ERROR_LOG("SI_PIH_GetRSimContent: USIMM_GetCardIMSI fail.");
        return;
    }

    /* �ж�IMSI�����Ƿ�Ϸ� */
    if (SI_PIH_IMSI_MAX_LEN < aucImsi[0])
    {
        PIH_ERROR1_LOG("SI_PIH_GetRSimContent: IMSI length is error.", aucImsi[0]);
        return;
    }

    /* ��AD�ļ��У���ȡHPLMN MNC���� */
    if (USIMM_API_SUCCESS != USIMM_GetCachedFile(USIMM_USIM_EFAD_STR,
                                                &ulDataLen,
                                                &pucData,
                                                USIMM_GUTL_APP))
    {
        PIH_ERROR_LOG("SI_PIH_GetRSimContent: USIMM_GetCachedFile fail.");
        return;
    }

    ucHplmnMncLen = SI_PIH_GetMncLen(pucData, ulDataLen);

    SI_PIH_DecodeImsiHPLMN(aucImsi, ucHplmnMncLen, pstCardCont);

    if (USIMM_CARD_SIM == g_stPihCardInfo.enGUTLCardType)
    {
        PIH_NORMAL_LOG("SI_PIH_GetRSimContent: SIM Card do not need read EHPLMN.");
        return;
    }

    if(VOS_FALSE == SI_PIH_GetEHPlmnNVState())
    {
        PIH_NORMAL_LOG("SI_PIH_GetRSimContent: SI_PIHGetEHPlmnNVState not support.");
        return;
    }

    /* �ж�EHPLMN�����Ƿ�֧�� */
    if (PS_USIM_SERVICE_AVAILIABLE != USIMM_IsServiceAvailable(USIM_SVR_EHPLMN))
    {
        PIH_WARNING_LOG("SI_PIH_GetRSimContent: EHplmn's SST not Support.");
        return;
    }

    /* �ӻ������ж���EHPLMN�ļ����� */
    if (USIMM_API_SUCCESS != USIMM_GetCachedFile(USIMM_USIM_EFEHPLMNPI_STR,
                                                &ulDataLen,
                                                &pucData,
                                                USIMM_GUTL_APP))
    {
        PIH_WARNING_LOG("SI_PIH_GetRSimContent: EHplmn not in SIM.");
        return;
    }

    SI_PIH_DecodeEHPLMN(pucData, ulDataLen, pstCardCont);

    return ;
}
VOS_UINT8* SI_PIH_GetVSimFileContent(
    OAM_XML_NODE_STRU                   *pstXmlNode,
    VOS_CHAR                            *pcEFName,
    VOS_UINT32                          *pulDataLen)
{
    VOS_UINT8           *pucContent;
    VOS_UINT32          ulDataLen;
    OAM_XML_NODE_STRU   *pstXMLNopde;

    pstXMLNopde = OAM_XML_GetChildNodeByAttributeValue(pstXmlNode, pcEFName);

    if(VOS_NULL_PTR == pstXMLNopde)
    {
        PIH_WARNING_LOG("SI_PIH_GetVSimFileContent: OAM_XML_GetChildNodeByAttributeValue failed!");

        return VOS_NULL_PTR;
    }

    if((VOS_NULL == pstXMLNopde->ulValueLength)
        ||(VOS_NULL_PTR == pstXMLNopde->pcNodeValue))
    {
        PIH_WARNING_LOG("SI_PIH_GetVSimFileContent: File Content is NULL.");

        return VOS_NULL_PTR;
    }

    pucContent = (VOS_UINT8*)VOS_MemAlloc(MAPS_PIH_PID,
                                        DYNAMIC_MEM_PT,
                                        pstXMLNopde->ulValueLength);

    if(VOS_NULL_PTR == pucContent)
    {
        PIH_WARNING_LOG("SI_PIH_GetVSimFileContent: VOS_MemAlloc is NULL!");

        return VOS_NULL_PTR;
    }

    /*���������ַ�*/
    if(VOS_OK != OAM_XML_GetIntArray(pstXMLNopde->pcNodeValue,
                                    pstXMLNopde->ulValueLength,
                                    pucContent,
                                    &ulDataLen))
    {
        PIH_WARNING_LOG("SI_PIH_GetVSimFileContent: OAM_XML_GetIntArray is Failed!");

        (VOS_VOID)VOS_MemFree(MAPS_PIH_PID, pucContent);

        return VOS_NULL_PTR;
    }

    *pulDataLen = ulDataLen;

    return pucContent;
}
VOS_UINT32 SI_PIH_GetUsimUstState(
    VOS_UINT8                           *pucUst,
    VOS_UINT32                          ulUstLen,
    VOS_UINT32                          ulBitNo)
{
    VOS_UINT32          ulResult;

    ulResult = USIMM_GetBitFromBuf(pucUst, ulBitNo, ulUstLen);

    if(USIMM_BITNOFOUNE == ulResult)
    {
        PIH_WARNING_LOG("SI_PIH_GetUsimUstState: The Service is Out of File");

        return PS_USIM_SERVICE_NOT_AVAILIABLE;
    }

    return ulResult;
}


VOS_UINT32 SI_PIH_DecodeVSimFile(
    VOS_UINT8                           *pucXMLData,
    SI_PIH_CARD_CONTENT_STRU            *pstCardCont)
{
    OAM_XML_CTX_STRU                    stXmlCtx;
    OAM_XML_NODE_STRU                  *pstXmlNode;    /*���ڵ�*/
    VOS_UINT8                          *pucData;
    USIMM_PHYCARD_TYPE_ENUM_UINT32      enCardType;     /*��ǰ������*/
    VOS_UINT32                          ulDataLen;
    VOS_UINT8                           ucHplmnMncLen;

    /*����xml�ļ�*/
    /*lint -e534*/
    VOS_MemSet(&stXmlCtx, 0x00, sizeof(stXmlCtx));
    /*lint +e534*/

    /* ����XML������������,����XML�ṹ�� */
    if (OAM_XML_RESULT_SUCCEED != OAM_XML_InitXMLCtx(&stXmlCtx))
    {
        PIH_WARNING_LOG("SI_PIHDecodeVSimFile: Xml initialization failed!");

        return VOS_ERR;
    }

    pstXmlNode = OAM_XML_BuildXMLTree((VOS_CHAR*)pucXMLData, &stXmlCtx);

    if (VOS_NULL_PTR == pstXmlNode)
    {
        PIH_WARNING_LOG("SI_PIHDecodeVSimFile: Build xml tree failed!");

        (VOS_VOID)OAM_XML_ClearXMLCtx(&stXmlCtx);

        return VOS_ERR;
    }

    /*�����ļ����ڵ�*/
    if(VOS_OK != USIMM_DecodeVsimRoot(pstXmlNode, &enCardType, VOS_NULL_PTR))
    {
        PIH_WARNING_LOG("SI_PIHDecodeVSimFile: USIMM_DecodeVsimRoot failed!");

        (VOS_VOID)OAM_XML_ClearXMLCtx(&stXmlCtx);

        return VOS_ERR;
    }

/*lint -e701*/
    pstCardCont->ucCardType = (VOS_UINT8)PIH_BIT_N(enCardType);
/*lint +e701*/

    /*��ѯEFAD*/
    pucData = SI_PIH_GetVSimFileContent(pstXmlNode, "EFAD", &ulDataLen);

    if(VOS_NULL_PTR == pucData)
    {
        PIH_WARNING_LOG("SI_PIHDecodeVSimFile: Find EFAD failed!");

        (VOS_VOID)OAM_XML_ClearXMLCtx(&stXmlCtx); /*���XML*/

        return VOS_ERR;
    }

    /* ��ȡMNC���� */
    ucHplmnMncLen = SI_PIH_GetMncLen(pucData, ulDataLen);

    /*lint -e534*/
    (VOS_VOID)VOS_MemFree(MAPS_PIH_PID, pucData);     /*�ͷ�EFAD ���ڴ�*/
    /*lint +e534*/

    /*��ѯ EFIMSI*/
    pucData = SI_PIH_GetVSimFileContent(pstXmlNode, "EFIMSI", &ulDataLen);

    if(VOS_NULL_PTR == pucData)
    {
        PIH_WARNING_LOG("SI_PIHDecodeVSimFile: find EFIMSI failed!");

        (VOS_VOID)OAM_XML_ClearXMLCtx(&stXmlCtx);     /*���XML*/

        return VOS_ERR;
    }

    /* EFIMSI �ļ����ȴ��� */
    if ((USIMM_EF_IMSI_LEN != ulDataLen)&&(SI_PIH_IMSI_MAX_LEN < pucData[0]))
    {
        PIH_WARNING_LOG("SI_PIHDecodeVSimFile: EF IMSI Len Error!");

        (VOS_VOID)OAM_XML_ClearXMLCtx(&stXmlCtx);     /*���XML*/

        (VOS_VOID)VOS_MemFree(MAPS_PIH_PID, pucData); /*�ͷ�EFIMSI ���ڴ�*/

        return VOS_ERR;
    }

    /*���� IMSI*/
    SI_PIH_DecodeImsiHPLMN(pucData, ucHplmnMncLen, pstCardCont);

    /*lint -e534*/
    (VOS_VOID)VOS_MemFree(MAPS_PIH_PID, pucData);     /*�ͷ�EFIMSI ���ڴ�*/
    /*lint +e534*/

    if (USIMM_PHYCARD_TYPE_ICC == enCardType)
    {
        PIH_NORMAL_LOG("SI_PIHDecodeVSimFile: SIM Card do not need read EHPLMN.");

        (VOS_VOID)OAM_XML_ClearXMLCtx(&stXmlCtx);     /*���XML*/

        return VOS_OK;
    }

    /*��� EHPLMN�Ƿ�֧��*/
    if(VOS_FALSE == SI_PIH_GetEHPlmnNVState())
    {
        PIH_NORMAL_LOG("SI_PIHDecodeVSimFile: SI_PIH_GetEHPlmnNVState return not support.");

        (VOS_VOID)OAM_XML_ClearXMLCtx(&stXmlCtx);     /*���XML*/

        return VOS_OK;
    }

    /*��ѯ EFUST*/
    pucData = SI_PIH_GetVSimFileContent(pstXmlNode, "EFUST", &ulDataLen);

    if(VOS_NULL_PTR == pucData)
    {
        PIH_WARNING_LOG("SI_PIHDecodeVSimFile: Find EF UST failed!");

        (VOS_VOID)OAM_XML_ClearXMLCtx(&stXmlCtx);

        return VOS_ERR;
    }

    /*��ѯ EFUST ����״̬*/
    if(PS_USIM_SERVICE_NOT_AVAILIABLE ==
                SI_PIH_GetUsimUstState(pucData, ulDataLen, USIM_SVR_EHPLMN))
    {
        PIH_WARNING_LOG("SI_PIHDecodeVSimFile: Find EF UST failed!");

        (VOS_VOID)OAM_XML_ClearXMLCtx(&stXmlCtx);     /*���XML*/

        (VOS_VOID)VOS_MemFree(MAPS_PIH_PID, pucData); /*�ͷ�EF UST ���ڴ�*/

        return VOS_OK;
    }

    /*lint -e534*/
    (VOS_VOID)VOS_MemFree(MAPS_PIH_PID, pucData);     /*�ͷ�EF UST ���ڴ�*/
    /*lint +e534*/

    /*��ѯ EF EHPLMN */
    pucData = SI_PIH_GetVSimFileContent(pstXmlNode, "EFEHPLMN", &ulDataLen);

    if(VOS_NULL_PTR == pucData)
    {
        PIH_WARNING_LOG("SI_PIHDecodeVSimFile: Find EF EHPLMN failed!");

        (VOS_VOID)OAM_XML_ClearXMLCtx(&stXmlCtx);

        return VOS_OK;
    }

    SI_PIH_DecodeEHPLMN(pucData, ulDataLen, pstCardCont);

    (VOS_VOID)OAM_XML_ClearXMLCtx(&stXmlCtx);    /*���XML*/

    /*lint -e534*/
    (VOS_VOID)VOS_MemFree(MAPS_PIH_PID, pucData);/*�ͷ�EF EHPLMN ���ڴ�*/
    /*lint +e534*/

    return VOS_OK;
}
VOS_VOID SI_PIH_GetVSimContent(
    SI_PIH_CARD_CONTENT_STRU            *pstCardCont)
{
    VOS_UINT8                           *pucXMLData;

    pstCardCont->ucIndex   = SI_PIH_SIM_VIRT_SIM1;
    pstCardCont->ucCardCap = PIH_BIT_N(USIMM_PHYCARD_TYPE_ICC) | PIH_BIT_N(USIMM_PHYCARD_TYPE_UICC);

    /* �ж����⿨�Ƿ���� */
    pucXMLData = USIMM_ReadVsimFile(MAPS_PIH_PID);

    if(VOS_NULL_PTR == pucXMLData)
    {
        PIH_WARNING_LOG("SI_PIH_GetVSimContent: USIMM_ReadVsimFile is failed.");
        return;
    }

    if(VOS_OK != SI_PIH_DecodeVSimFile(pucXMLData, pstCardCont))
    {
        PIH_WARNING_LOG("SI_PIH_GetVSimContent: SI_PIH_DecodeVSimFile is failed.");
    }

    /* pucXMLData�ڴ���USIMM_ReadVsimFile���䣬��Ҫ�����ͷŲ��� */
    /*lint -e534*/
    (VOS_VOID)VOS_MemFree(MAPS_PIH_PID, pucXMLData);
    /*lint +e534*/

    return;
}


VOS_UINT32 SI_PIH_HvsDHSetHandle(
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                           *pucData)
{
    NVIM_VSIM_HVSDH_NV_STRU             stDhNv;
    SI_PIH_EVENT_INFO_STRU              stEvent;
    VOS_UINT32                          ulResult;

    (VOS_VOID)VOS_MemSet(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));

    stEvent.PIHError = TAF_ERR_ERROR;

    /* ��NV���ж�����Կ��Ϣ */
    ulResult = NV_Read(en_NV_Item_VSIM_HVSDH_INFO, &stDhNv, sizeof(stDhNv));

    if (NV_OK != ulResult)
    {
        PIH_ERROR1_LOG("SI_PIH_HvsDHSetReq: NV_Read fail.", (VOS_INT32)ulResult);

        return SI_PIH_EventCallBack(&stEvent);
    }

    /*lint -e534*/
    VOS_MemCpy(stDhNv.stSPublicKey.aucKey, pucData, ulDataLen);
    /*lint +e534*/

    stDhNv.stSPublicKey.ulKeyLen = ulDataLen;

    /* ����������Կд��NV���� */
    ulResult = NV_Write(en_NV_Item_VSIM_HVSDH_INFO, &stDhNv, sizeof(stDhNv));

    if (NV_OK != ulResult)
    {
        PIH_ERROR1_LOG("SI_PIH_HvsDHSetReq: NV_Write fail.", (VOS_INT32)ulResult);

        return SI_PIH_EventCallBack(&stEvent);
    }

    stEvent.PIHError = TAF_ERR_NO_ERROR;

    return SI_PIH_EventCallBack(&stEvent);
}


VOS_UINT32 SI_PIH_HvsDHQueryHandle(VOS_VOID)
{
    NVIM_VSIM_HVSDH_NV_STRU             stDhNv;
    SI_PIH_EVENT_INFO_STRU              stEvent;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucPubKey[VSIM_DH_PUBIIC_KEY] = {0};
    DH_KEY                              stDhKey;

    /*lint -e534*/
    VOS_MemSet(&stDhKey, 0, sizeof(stDhKey));
    (VOS_VOID)VOS_MemSet(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));
    /*lint +e534*/

    stEvent.PIHError = TAF_ERR_ERROR;

    /* ��NV����ȡ����Կ��Ϣ */
    ulResult = NV_Read(en_NV_Item_VSIM_HVSDH_INFO, &stDhNv, sizeof(stDhNv));

    if (NV_OK != ulResult)
    {
        PIH_ERROR1_LOG("SI_PIH_HvsDHQryReq: NV_Read fail.", (VOS_INT32)ulResult);

        return SI_PIH_EventCallBack(&stEvent);
    }

    /* ���絥�����ԿΪ�գ������DH�ӿ�������Կ */
    if ((VOS_NULL == stDhNv.stCPrivateKey.ulKeyLen)
        ||(VSIM_DH_PRIVATE_KEY < stDhNv.stCPrivateKey.ulKeyLen)
        ||(VOS_NULL == stDhNv.stCPublicKey.ulKeyLen)
        ||(VSIM_DH_PUBIIC_KEY < stDhNv.stCPublicKey.ulKeyLen))
    {
        /* ��ʼ����Կ���� */
        DH_FillFixParams(&stDhKey);

        /* ����modem��Կ��˽Կ */
        ulResult = (VOS_UINT32)DH_GeneratePublicValue(aucPubKey,
                                                    VSIM_DH_PRIVATE_KEY,
                                                    &stDhKey);

        if (VOS_OK != ulResult)
        {
            PIH_ERROR1_LOG("SI_PIH_HvsDHQryReq: DH_GeneratePublicValue fail.",
                                                    (VOS_INT32)ulResult);

            return SI_PIH_EventCallBack(&stEvent);
        }

        /*lint -e534*/
        VOS_MemCpy(stDhNv.stCPublicKey.aucKey, aucPubKey, VSIM_DH_PUBIIC_KEY);
        /*lint +e534*/

        stDhNv.stCPublicKey.ulKeyLen = VSIM_DH_PUBIIC_KEY;

        /*lint -e534*/
        VOS_MemCpy(stDhNv.stCPrivateKey.aucKey,
                    stDhKey.privateValue,
                    VSIM_DH_PRIVATE_KEY);
        /*lint +e534*/

        stDhNv.stCPrivateKey.ulKeyLen = VSIM_DH_PRIVATE_KEY;

        /* ���������Կд��NV���� */
        ulResult = NV_Write(en_NV_Item_VSIM_HVSDH_INFO, &stDhNv, sizeof(stDhNv));

        if (NV_OK != ulResult)
        {
            PIH_ERROR1_LOG("SI_PIH_HvsDHQryReq: NV_Write fail.", (VOS_INT32)ulResult);

            return SI_PIH_EventCallBack(&stEvent);
        }
    }

    /* �������㷨����ظ���Ϣ�� */
    stEvent.PIHEvent.HvsDHCnf.enAlgorithm = stDhNv.enAlgorithm;

    /* ��������๫Կ */
    /*lint -e534*/
    VOS_MemCpy(&stEvent.PIHEvent.HvsDHCnf.stCkey, &stDhNv.stCPublicKey,
                    sizeof(stEvent.PIHEvent.HvsDHCnf.stCkey));

    /* ������������Կ */
    VOS_MemCpy(&stEvent.PIHEvent.HvsDHCnf.stSkey, &stDhNv.stSPublicKey,
                    sizeof(stEvent.PIHEvent.HvsDHCnf.stSkey));
    /*lint +e534*/

    stEvent.PIHError = TAF_ERR_NO_ERROR;

    return SI_PIH_EventCallBack(&stEvent);
}


VOS_UINT32 SI_PIH_HvsContQueryHandle(VOS_VOID)
{
    SI_PIH_EVENT_INFO_STRU              stEvent;

    /*lint -e534*/
    VOS_MemSet(&stEvent, 0, sizeof(stEvent));
    /*lint +e534*/

    /* ����Ӳ�������� */
    SI_PIH_GetRSimContent(&stEvent.PIHEvent.HvsContCnf.astSimCard[SI_PIH_RSIM]);

    /* ������������ */
    SI_PIH_GetVSimContent(&stEvent.PIHEvent.HvsContCnf.astSimCard[SI_PIH_VSIM]);

    stEvent.PIHError = TAF_ERR_NO_ERROR;

    return SI_PIH_EventCallBack(&stEvent);
}


VOS_VOID SI_PIH_ReDhNegotiateIndProc(VOS_VOID)
{
    SI_PIH_EVENT_INFO_STRU              stEvent;

    /*lint -e534*/
    VOS_MemSet(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));
    /*lint +e534*/

    stEvent.ClientId  = MN_CLIENT_ALL;/*�����ֵ*/
    stEvent.EventType = SI_PIH_EVENT_HVRDH_IND;
    stEvent.PIHError  = TAF_ERR_NO_ERROR;

    stEvent.PIHEvent.HvrdhInd.ulReDhFlag = VOS_TRUE;

    (VOS_VOID)SI_PIHSendATMsg(&stEvent);

    return;
}
VOS_UINT32 SI_PIH_FwriteParaCheck(
    SI_PIH_FILE_WRITE_REQ_STRU          *pstMsg)
{
    /* ������� */
    if(SI_PIH_FILE_START_INDEX == pstMsg->ucIndex)  /*д���һ��*/
    {
        PIH_NORMAL_LOG("SI_PIH_FwriteParaCheck: Clear the Global Para.");

        if(VOS_NULL_PTR != g_stPIHFileWriteGlobal.fpFile)
        {
            PIH_NORMAL_LOG("SI_PIH_FwriteParaCheck: The File is not Close.");

            (VOS_VOID)USIMM_File_Close(g_stPIHFileWriteGlobal.fpFile);
        }

        /*lint -e534*/
        (VOS_VOID)VOS_MemSet(&g_stPIHFileWriteGlobal,
                            0,
                            sizeof(g_stPIHFileWriteGlobal));
        /*lint +e534*/
    }
    else if(pstMsg->ucIndex > SI_PIH_FILE_START_INDEX)  /*д��ǵ�һ��*/
    {
        if(g_stPIHFileWriteGlobal.usRefNum != pstMsg->ucRef)
        {
           PIH_ERROR_LOG("SI_PIH_FwriteParaCheck: usRefNum is not same.");
           return VOS_ERR;
        }

        if((g_stPIHFileWriteGlobal.usIndex+1) != pstMsg->ucIndex)
        {
           PIH_ERROR_LOG("SI_PIH_FwriteParaCheck: Index is Error.");
           return VOS_ERR;
        }

        if(g_stPIHFileWriteGlobal.usTotalNum != pstMsg->ucTotalNum)
        {
           PIH_ERROR_LOG("SI_PIH_FwriteParaCheck: usTotalNum is not same.");
           return VOS_ERR;
        }
    }
    else    /*make pclint pass*/
    {
        PIH_ERROR_LOG("SI_PIH_FwriteParaCheck: Code Run Error.");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 SI_PIH_ATFileWriteHandle(
    SI_PIH_FILE_WRITE_REQ_STRU          *pstMsg)
{
    SI_PIH_EVENT_INFO_STRU              stEvent;
    VOS_INT32                          ulResult;

    (VOS_VOID)VOS_MemSet(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));

    /* ��ȡNV���ж�vsim�Ƿ���ʹ�� */
    if((VOS_TRUE == USIMM_VsimIsActive())
      &&(USIMM_CARD_SERVIC_ABSENT != g_stPihCardInfo.enGUTLSvcStatus))
    {
        PIH_ERROR_LOG("SI_PIH_FileWriteProc: vSIM File is using.");

        stEvent.PIHError = TAF_ERR_SIM_BUSY;

        return SI_PIH_EventCallBack(&stEvent);
    }

    stEvent.PIHError = TAF_ERR_PARA_ERROR;

    if(VOS_OK != SI_PIH_FwriteParaCheck(pstMsg))    /*chenck gobal para*/
    {
        PIH_ERROR_LOG("SI_PIH_FileWriteProc: SI_PIH_FwriteParaCheck is Failed.");

        return SI_PIH_EventCallBack(&stEvent);
    }

    /* �ж��Ƿ���Ҫ���ļ� */
    if(VOS_NULL_PTR == g_stPIHFileWriteGlobal.fpFile)
    {
        /* ������ǵ�һ�����ش��� */
        if(SI_PIH_FILE_START_INDEX != pstMsg->ucIndex)
        {
            PIH_ERROR_LOG("SI_PIH_FileWriteProc: it is not first packages.");

            return SI_PIH_EventCallBack(&stEvent);
        }

        /* ��Ŀ¼�������򴴽� */
        if (VOS_OK != mdrv_file_access(VSIM_XML_DIR_PATH, 0))
        {
            (VOS_VOID)USIMM_Mkdir(VSIM_XML_DIR_PATH);
        }

        (VOS_VOID)mdrv_file_remove(VSIM_XML_FILE_PATH);

        (VOS_VOID)mdrv_file_remove(VSIM_XML_TEMP_PATH);

        g_stPIHFileWriteGlobal.fpFile = USIMM_File_Open(VSIM_XML_TEMP_PATH,
                                                        USIMM_FILE_OPEN_MODE_ADD_W);

        if (VOS_NULL_PTR == g_stPIHFileWriteGlobal.fpFile)
        {
            stEvent.PIHError = TAF_ERR_NULL_PTR;

            PIH_ERROR_LOG("SI_PIH_FileWriteProc: XML Temp file open is Failed.");

            return SI_PIH_EventCallBack(&stEvent);
        }

        /* ����ȫ�ֱ��� */
        g_stPIHFileWriteGlobal.usRefNum = pstMsg->ucRef;
        g_stPIHFileWriteGlobal.usTotalNum = pstMsg->ucTotalNum;
    }

    ulResult = USIMM_File_Write(pstMsg->aucFileData,
                                pstMsg->ulFileDataLen,
                                VSIM_FILE_WRITE_COUNT,
                                g_stPIHFileWriteGlobal.fpFile);

    stEvent.PIHError = TAF_ERR_ERROR;

    if (VSIM_FILE_WRITE_COUNT != ulResult)
    {
        PIH_ERROR_LOG("SI_PIH_FileWriteProc: XML Temp file Write is Failed.");

        return SI_PIH_EventCallBack(&stEvent);
    }

    g_stPIHFileWriteGlobal.usIndex  = pstMsg->ucIndex;

    /* �������һ�� */
    if(pstMsg->ucIndex == pstMsg->ucTotalNum)
    {
        if (VOS_OK != USIMM_File_Close(g_stPIHFileWriteGlobal.fpFile) )
        {
            PIH_ERROR_LOG("SI_PIH_FileWriteProc: XML Temp file Close is Failed.");

            return SI_PIH_EventCallBack(&stEvent);
        }

        /*lint -e534*/
        (VOS_VOID)VOS_MemSet(&g_stPIHFileWriteGlobal,
                                0,
                                sizeof(g_stPIHFileWriteGlobal));
        /*lint +e534*/

        (VOS_VOID)USIMM_File_Rename(VSIM_XML_TEMP_PATH, VSIM_XML_FILE_PATH);
    }

    stEvent.PIHError = TAF_ERR_NO_ERROR;

    return SI_PIH_EventCallBack(&stEvent);
}

/*****************************************************************************
�� �� ��  :SI_PIH_HukEncode
��������  :ʵ�����ݵ�HUK+AES����
�������  :��
�������  :��
�� �� ֵ  :VOS_UINT32
���ú���  :
�޶���¼  :
1. ��    ��   : 2014��10��09��
   ��    ��   : zhuli
   �޸�����   : Create
*****************************************************************************/
VOS_UINT32 SI_PIH_HukEncode(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          ulSrcLen,
    VOS_UINT8                           *pucDst,
    VOS_UINT32                          *pulDstLen
)
{
    VOS_UINT8           auckey[SI_PIH_HUK_LEN];
    VOS_INT32           lDstLen;

    if (MDRV_OK != mdrv_efuse_read_huk(auckey, sizeof(auckey)))
    {
        PIH_ERROR_LOG("SI_PIH_HukEncode: Read HUK Fail");

        return VOS_ERR;
    }

    lDstLen = AESEncryptS(pucSrc, (VOS_INT)ulSrcLen, auckey, SI_PIH_HUK_BITS, pucDst, VSIM_DH_AGREE_KEY);

    if (VOS_NULL == lDstLen)
    {
        PIH_ERROR_LOG("SI_PIH_HukEncode: AESEncrypt Fail");

        return VOS_ERR;
    }

    *pulDstLen = (VOS_UINT32)lDstLen;

    return VOS_OK;
}

/*****************************************************************************
�� �� ��  :SI_PIH_HvteeDataCheck
��������  :ʵ��Share Memory ���ݵļ��
�������  :��
�������  :��
�� �� ֵ  :SI_PIH_HVTEE_ERROR_ENUM_UINT32
���ú���  :
�޶���¼  :
1. ��    ��   : 2014��10��09��
   ��    ��   : zhuli
   �޸�����   : Create
*****************************************************************************/
SI_PIH_HVTEE_ERROR_ENUM_UINT32 SI_PIH_HvteeDataCheck(
    SI_PIH_HVTEE_DATAFLAG_ENUM_UINT32   enFlag,
    VOS_UINT32                          ulMaxLen,
    VOS_UINT8                          *pucData
)
{
    SI_PIH_HVTEE_SHAREHEAD_STRU     *pstDataHead = VOS_NULL;
    VOS_UINT32                      ulEndFlag = 0;

    if (VOS_NULL_PTR == pucData)    /*�ж�ADDR�ķ�Χ*/
    {
        PIH_ERROR_LOG("SI_PIH_HvteeDataCheck: ADDR is Error.");

        return SI_PIH_HVTEE_ADDR_ERROR;
    }

    pstDataHead = (SI_PIH_HVTEE_SHAREHEAD_STRU *)pucData;

    if (pstDataHead->enFlag != enFlag)
    {
        PIH_ERROR_LOG("SI_PIH_HvteeDataCheck: StartFlag is Error.");

        return SI_PIH_HVTEE_HEAD_ERROR;
    }

    if (pstDataHead->ulDataLen > ulMaxLen)
    {
        PIH_ERROR_LOG("SI_PIH_HvteeDataCheck: LEN is Error.");

        return SI_PIH_HVTEE_LEN_ERROR;
    }

    (VOS_VOID)VOS_MemCpy(&ulEndFlag, &pucData[sizeof(SI_PIH_HVTEE_SHAREHEAD_STRU)+pstDataHead->ulDataLen],sizeof(VOS_UINT32));

    if (SI_PIH_SMEM_ENDFLAG != ulEndFlag)
    {
        PIH_ERROR_LOG("SI_PIH_HvteeDataCheck: End Flag is Error.");

        return SI_PIH_HVTEE_END_ERROR;
    }

    return SI_PIH_HVTEE_NOERROR;
}

/*****************************************************************************
�� �� ��  :SI_PIH_HvteeApnHandle
��������  :ʵ��APN���Ʋ���д��
�������  :��
�������  :��
�� �� ֵ  :VOS_OK
���ú���  :
�޶���¼  :
1. ��    ��   : 2014��10��09��
   ��    ��   : zhuli
   �޸�����   : Create
*****************************************************************************/
VOS_UINT32 SI_PIH_HvteeApnHandle(VOS_VOID)
{
    SI_PIH_HVTEE_ERROR_ENUM_UINT32  enResult;
    VOS_UINT8                       *pucAPNData;
    SI_PIH_HVTEE_SHAREHEAD_STRU     *pstDataHead;

    enResult = SI_PIH_HvteeDataCheck((SI_PIH_HVTEE_DATAFLAG_ENUM_UINT32)SI_PIH_HVTEE_APNSET,
                                        SI_PIH_APNSET_SMEM_LEN,
                                        (VOS_UINT8 *)SI_PIH_APNSET_SMEM_ADDR);
    /*lint -save -e438*/
    if (SI_PIH_HVTEE_NOERROR != enResult)
    {
        PIH_ERROR_LOG("SI_PIH_HvteeApnHandle: SI_PIH_HvteeDataCheck is Error.");

        return enResult;
    }

    pstDataHead = (SI_PIH_HVTEE_SHAREHEAD_STRU*)SI_PIH_APNSET_SMEM_ADDR;

    if (VOS_OK != VOS_TaskLock())
    {
        PIH_WARNING_LOG("SI_PIH_HvteeApnHandle: VOS_TaskLock Error");

        return SI_PIH_HVTEE_DATA_ERROR;
    }

    (VOS_VOID)VOS_MemSet(g_aucVsimAPNData, VOS_NULL, sizeof(g_aucVsimAPNData));

    if (VOS_NULL == pstDataHead->ulDataLen)
    {
        pucAPNData = VOS_NULL_PTR;
    }
    else
    {
        pucAPNData = (VOS_UINT8*)(SI_PIH_APNSET_SMEM_ADDR+sizeof(SI_PIH_HVTEE_SHAREHEAD_STRU));

        if (pucAPNData[pstDataHead->ulDataLen-1] != '\0')
        {
            (VOS_VOID)VOS_TaskUnlock();

            return SI_PIH_HVTEE_LEN_ERROR;
        }

        /*����APN����,�ַ�������*/
        (VOS_VOID)VOS_MemCpy(g_aucVsimAPNData, pucAPNData, pstDataHead->ulDataLen);
    }

    (VOS_VOID)VOS_TaskUnlock();

    SI_PIH_MNTNDataHook(SI_PIH_HVTEE_DATA_HOOK,
                        sizeof(SI_PIH_HVTEE_SHAREHEAD_STRU)+pstDataHead->ulDataLen,
                        (VOS_UINT8*)pstDataHead);

    return SI_PIH_HVTEE_NOERROR;
    /*lint -restore*/
}

/*****************************************************************************
�� �� ��  :SI_PIH_HvteeDHHandle
��������  :ʵ��VSIM�ļ���д��
�������  :��
�������  :��
�� �� ֵ  :VOS_OK
���ú���  :
�޶���¼  :
1. ��    ��   : 2014��10��09��
   ��    ��   : zhuli
   �޸�����   : Create
*****************************************************************************/
VOS_UINT32 SI_PIH_HvteeDHHandle(VOS_VOID)
{
    NVIM_VSIM_HVSDH_NV_STRU             stNVDHKey;
    SI_PIH_HVTEEDHPARA_STRU             *pstDHParaData;
    SI_PIH_HVTEE_ERROR_ENUM_UINT32      enResult;

    if (NV_OK != NV_Read(en_NV_Item_VSIM_HVSDH_INFO, &stNVDHKey, sizeof(NVIM_VSIM_HVSDH_NV_STRU)))
    {
        USIMM_ERROR_LOG("SI_PIH_HvteeDHHandle: NV Read Key is Failed");

        return SI_PIH_HVTEE_DATA_ERROR;
    }

    enResult = SI_PIH_HvteeDataCheck((SI_PIH_HVTEE_DATAFLAG_ENUM_UINT32)SI_PIH_HVTEE_DHSET,
                                    SI_PIH_DHPARASET_SMEM_LEN,
                                    (VOS_UINT8 *)SI_PIH_DHPARASET_SMEM_ADDR);

    if (SI_PIH_HVTEE_NOERROR != enResult)
    {
        PIH_ERROR_LOG("SI_PIH_HvteeApnHandle: SI_PIH_HvteeDataCheck is Error.");

        return enResult;
    }

    pstDHParaData = (SI_PIH_HVTEEDHPARA_STRU*)(SI_PIH_DHPARASET_SMEM_ADDR+sizeof(SI_PIH_HVTEE_SHAREHEAD_STRU));

    if ((VOS_NULL != pstDHParaData->ulSPublicKeyLen)
        &&(pstDHParaData->ulSPublicKeyLen <= VSIM_KEYLEN_MAX))
    {
        stNVDHKey.stSPublicKey.ulKeyLen = pstDHParaData->ulSPublicKeyLen;

        (VOS_VOID)VOS_MemCpy(stNVDHKey.stSPublicKey.aucKey,
                    pstDHParaData->aucSPublicKey,
                    pstDHParaData->ulSPublicKeyLen);
    }

    if ((VOS_NULL != pstDHParaData->ulCPublicKeyLen)
        &&(pstDHParaData->ulCPublicKeyLen <= VSIM_KEYLEN_MAX))
    {
        stNVDHKey.stCPublicKey.ulKeyLen = pstDHParaData->ulCPublicKeyLen;

        (VOS_VOID)VOS_MemCpy(stNVDHKey.stCPublicKey.aucKey,
                    pstDHParaData->aucCPublicKey,
                    pstDHParaData->ulCPublicKeyLen);
    }

    if ((VOS_NULL != pstDHParaData->ulCPrivateKeyLen)
        &&(pstDHParaData->ulCPrivateKeyLen <= VSIM_KEYLEN_MAX))
    {
        stNVDHKey.stCPrivateKey.ulKeyLen = pstDHParaData->ulCPrivateKeyLen;

        if (VOS_OK != SI_PIH_HukEncode(pstDHParaData->aucCPrivateKey,
                                        pstDHParaData->ulCPrivateKeyLen,
                                        stNVDHKey.stCPrivateKey.aucKey,
                                        &stNVDHKey.stCPrivateKey.ulKeyLen))
        {
            PIH_ERROR_LOG("SI_PIH_HvteeApnHandle: SI_PIH_HukEncode is Error.");

            return SI_PIH_HVTEE_ENCODE_ERROR;
        }
    }

    if (NV_OK != NV_Write(en_NV_Item_VSIM_HVSDH_INFO, &stNVDHKey, sizeof(NVIM_VSIM_HVSDH_NV_STRU)))
    {
        USIMM_ERROR_LOG("SI_PIH_HvteeDHHandle: NV Write Key is Failed");

        return SI_PIH_HVTEE_DATA_ERROR;
    }

    if ((VOS_NULL != pstDHParaData->ulParaPLen)||(VOS_NULL != pstDHParaData->ulParaGLen))
    {
        DH_ChangeDHParas(pstDHParaData->ulParaPLen,
                        pstDHParaData->aucParaPKey,
                        pstDHParaData->ulParaGLen,
                        pstDHParaData->aucParaGKey);
    }

    SI_PIH_MNTNDataHook(SI_PIH_HVTEE_DATA_HOOK, sizeof(SI_PIH_HVTEEDHPARA_STRU), (VOS_UINT8*)pstDHParaData);

    return SI_PIH_HVTEE_NOERROR;
}


VOS_UINT32 SI_PIH_HvteeVSIMHandle(VOS_VOID)
{
    SI_PIH_HVTEE_ERROR_ENUM_UINT32      enResult;
    VOS_UINT8                           *pucVsimData;
    SI_PIH_HVTEE_SHAREHEAD_STRU         *pstDataHead;

    enResult = SI_PIH_HvteeDataCheck((SI_PIH_HVTEE_DATAFLAG_ENUM_UINT32)SI_PIH_HVTEE_VSIMDATA,
                                    SI_PIH_VSIM_SMEM_LEN,
                                    (VOS_UINT8 *)SI_PIH_VSIM_SMEM_ADDR);

    if (SI_PIH_HVTEE_NOERROR != enResult)
    {
        PIH_ERROR_LOG("SI_PIH_HvteeApnHandle: SI_PIH_HvteeDataCheck is Error.");

        return enResult;
    }

    pstDataHead = (SI_PIH_HVTEE_SHAREHEAD_STRU *)SI_PIH_VSIM_SMEM_ADDR;

    pucVsimData = (VOS_UINT8 *)(SI_PIH_VSIM_SMEM_ADDR+sizeof(SI_PIH_HVTEE_SHAREHEAD_STRU));

    USIMM_SaveHvteeVsimData(pstDataHead->ulDataLen, pucVsimData);

    if (VOS_NULL != pstDataHead->ulDataLen)
    {
        SI_PIH_MNTNDataHook(SI_PIH_HVTEE_DATA_HOOK, sizeof(SI_PIH_HVTEE_SHAREHEAD_STRU)+pstDataHead->ulDataLen, (VOS_UINT8*)pstDataHead);
    }

    return SI_PIH_HVTEE_NOERROR;
}


VOS_UINT32 SI_PIH_HvteeSetHandle(
    SI_PIH_HVTEE_SET_REQ_STRU           *pstMsg
)
{
    VOS_UINT32                          ulAPNResult = VOS_OK;
    VOS_UINT32                          ulDHResult = VOS_OK;
    VOS_UINT32                          ulVSIMResult = VOS_OK;
    SI_PIH_EVENT_INFO_STRU              stEvent;

    /*lint -e534*/
    VOS_MemSet(&stEvent, 0, sizeof(stEvent));
    /*lint +e534*/

    if (VOS_NULL_PTR == g_ulTEEShareAddr)
    {
        stEvent.PIHError = TAF_ERR_NOT_READY;

        return SI_PIH_EventCallBack(&stEvent);
    }

    if (VOS_TRUE == pstMsg->stHvtee.bAPNFlag)
    {
        ulAPNResult = SI_PIH_HvteeApnHandle();
    }

    if (VOS_TRUE == pstMsg->stHvtee.bDHParaFlag)
    {
        ulDHResult = SI_PIH_HvteeDHHandle();
    }

    if (VOS_TRUE == pstMsg->stHvtee.bVSIMDataFlag)
    {
        ulVSIMResult = SI_PIH_HvteeVSIMHandle();
    }

    stEvent.PIHEvent.HVTEECnf.ulAPNResult   = ulAPNResult;
    stEvent.PIHEvent.HVTEECnf.ulDHResult    = ulDHResult;
    stEvent.PIHEvent.HVTEECnf.ulVSIMResult  = ulVSIMResult;

    if ((VOS_OK == ulAPNResult)&&(VOS_OK == ulDHResult)&&(VOS_OK == ulVSIMResult))
    {
        stEvent.PIHError = TAF_ERR_NO_ERROR;
    }
    else
    {
        stEvent.PIHError = TAF_ERR_UNSPECIFIED_ERROR;
    }

    return SI_PIH_EventCallBack(&stEvent);
}

/*****************************************************************************
�� �� ��  :SI_PIH_HvteeSetHandle
��������  :ʵ��VSIM��Ӳ��״̬��ѯ
�������  :pstMsg  -- HVTEE����
�������  :��
�� �� ֵ  :VOS_OK
���ú���  :
�޶���¼  :
1. ��    ��   : 2014��10��09��
   ��    ��   : zhuli
   �޸�����   : Create
*****************************************************************************/
VOS_UINT32 SI_PIH_HvCheckCardHandle(
    SI_PIH_HVCHECKCARD_REQ_STRU         *pstMsg
)
{
    SI_PIH_EVENT_INFO_STRU              stEvent;
    VOS_INT32                           lSCIResult = VOS_ERR;
    VOS_UINT32                          i;

    /*lint -e534*/
    VOS_MemSet(&stEvent, 0, sizeof(stEvent));
    /*lint +e534*/

    if (VOS_FALSE == USIMM_VsimIsActive())
    {
        stEvent.PIHError = TAF_ERR_SIM_BUSY;

        PIH_ERROR_LOG("SI_PIH_HvCheckCardHandle: Deactive Card Error");

        return SI_PIH_EventCallBack(&stEvent);
    }

    (VOS_VOID)mdrv_sci_reset(COLD_RESET);

#if (VOS_OS_VER != VOS_WIN32)       /* PC Stub */
    HPA_USIMLowPowerLock(MAPS_PIH_PID);
#endif

    for(i=0; i<SI_PIH_GETCARDSTATUS_MAX; i++)
    {
        lSCIResult = mdrv_sci_get_cardstatus(); /*�����λ�ɹ��򷵻سɹ�*/

        if (SCI_CARD_STATE_BUSY != lSCIResult)
        {
            break;
        }

        (VOS_VOID)VOS_TaskDelay(SI_PIH_TASKDELAY_TIMER_LEN);
    }

#if (VOS_OS_VER != VOS_WIN32)       /* PC Stub */
    HPA_USIMLowPowerUnLock(MAPS_PIH_PID);
#endif

    stEvent.PIHError = TAF_ERR_NO_ERROR;

    if (SCI_CARD_STATE_READY == lSCIResult)
    {
        stEvent.PIHEvent.HvCheckCardCnf.enData = SI_PIH_HVCHECKCARD_CARDIN;
    }
    else
    {
        stEvent.PIHEvent.HvCheckCardCnf.enData = SI_PIH_HVCHECKCARD_ABSENT;
    }

    for(i=0; i<SI_PIH_GETCARDSTATUS_MAX; i++)
    {
        if(VOS_OK == mdrv_sci_deact())
        {
            break;
        }

        PIH_ERROR_LOG("SI_PIH_HvCheckCardHandle: Deactive Card Error");
    }

    return SI_PIH_EventCallBack(&stEvent);
}

/*****************************************************************************
�� �� ��  :SI_PIH_InitTEEShareAddr
��������  :ʵ��VSIM��TEE�����ַ��ѯ
�������  :��
�������  :��
�� �� ֵ  :VOS_OK
���ú���  :
�޶���¼  :
1. ��    ��   : 2014��10��09��
   ��    ��   : zhuli
   �޸�����   : Create
*****************************************************************************/
VOS_VOID SI_PIH_InitTEEShareAddr(VOS_VOID)
{
    BSP_DDR_SECT_QUERY_S        stSectQuery;
    BSP_DDR_SECT_INFO_S         stSectInfo;

    (VOS_VOID)VOS_MemSet(&stSectQuery, 0, sizeof(stSectQuery));

    (VOS_VOID)VOS_MemSet(&stSectInfo, 0, sizeof(stSectInfo));

    g_ulTEEShareAddr = VOS_NULL_PTR;

    stSectQuery.enSectType = BSP_DDR_SECT_TYPE_ECS_TEE;

    if (MDRV_OK == mdrv_get_fix_ddr_addr(&stSectQuery, &stSectInfo))
    {
        g_ulTEEShareAddr = (VOS_UINT32)stSectInfo.pSectPhysAddr;
    }

    return ;
}

#endif  /*(FEATURE_ON == FEATURE_VSIM)*/

#if (FEATURE_ON == FEATURE_IMS)

VOS_VOID SI_PIH_GetEFIDFromPath(
    USIMM_FILEPATH_INFO_STRU           *pstFilePath,
    VOS_UINT16                         *pusEFID
)
{
    VOS_UINT8                           ucTemp;
    VOS_UINT32                          i;

    *pusEFID = VOS_NULL;

    for (i = 1; i <= 4; i++)
    {
        if (VOS_ERR == SI_PIH_AsciiToHexCode(pstFilePath->acPath[pstFilePath->ulPathLen - i], &ucTemp))
        {
            return;
        }

        /*lint -e701*/
        *pusEFID += (VOS_UINT16)((VOS_UINT16)ucTemp << ((i - 1) * 4));
        /*lint +e701*/
    }

    return ;
}


VOS_UINT32 SI_PIH_GetFileReq(
    VOS_UINT32                          ulSendPara,
    SI_PIH_GETFILE_INFO_STRU           *pstGetFileInfo
)
{
    USIMM_READFILE_REQ_STRU            *pstMsg;

    pstMsg = (USIMM_READFILE_REQ_STRU *)VOS_AllocMsg(MAPS_PIH_PID,
                                                sizeof(USIMM_READFILE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_ERR; /*���غ���������Ϣ*/
    }

    /*�����Ϣ����*/
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulSendPara      = ulSendPara;
    pstMsg->stMsgHeader.enMsgName       = USIMM_READFILE_REQ;
    pstMsg->stMsgHeader.enAppType       = pstGetFileInfo->enAppType;
    pstMsg->ucRecordNum                 = pstGetFileInfo->ucRecordNum;

    pstMsg->stFilePath.ulPathLen        = (VOS_UINT32)VOS_StrLen(USIMM_USIM_STR);

    /*lint -e534*/
    VOS_MemCpy(pstMsg->stFilePath.acPath, USIMM_USIM_STR, pstMsg->stFilePath.ulPathLen);

    SI_PIH_HexToAsciiCode((VOS_UINT8)((pstGetFileInfo->usEfId >> 12) & 0x0F), &pstMsg->stFilePath.acPath[pstMsg->stFilePath.ulPathLen]);
    SI_PIH_HexToAsciiCode((VOS_UINT8)((pstGetFileInfo->usEfId >> 8) & 0x0F), &pstMsg->stFilePath.acPath[pstMsg->stFilePath.ulPathLen + 1]);
    SI_PIH_HexToAsciiCode((VOS_UINT8)((pstGetFileInfo->usEfId >> 4) & 0x0F), &pstMsg->stFilePath.acPath[pstMsg->stFilePath.ulPathLen + 2]);
    SI_PIH_HexToAsciiCode((VOS_UINT8)((pstGetFileInfo->usEfId) & 0x0F), &pstMsg->stFilePath.acPath[pstMsg->stFilePath.ulPathLen + 3]);
    /*lint +e534*/

    pstMsg->stFilePath.ulPathLen += 4;

    return VOS_SendMsg(MAPS_PIH_PID, pstMsg);
}


VOS_UINT32 SI_PIH_SetFileReq(
    SI_PIH_SETFILE_INFO_STRU            *pstSetFileInfo)
{
    USIMM_UPDATEFILE_REQ_STRU          *pstMsg;

    pstMsg = (USIMM_UPDATEFILE_REQ_STRU *)VOS_AllocMsg(MAPS_PIH_PID,
                                                sizeof(USIMM_UPDATEFILE_REQ_STRU) - VOS_MSG_HEAD_LENGTH + pstSetFileInfo->ulEfLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_ERR; /*���غ���������Ϣ*/
    }

    /*�����Ϣ����*/
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulSendPara      = SI_PIH_SEND_PAPA(g_pstPIHCurrNode->usClient, g_pstPIHCurrNode->ulEventType);
    pstMsg->stMsgHeader.enMsgName       = USIMM_UPDATEFILE_REQ;
    pstMsg->stMsgHeader.enAppType       = pstSetFileInfo->enAppType;
    pstMsg->ucRecordNum                 = pstSetFileInfo->ucRecordNum;
    pstMsg->usDataLen                   = (VOS_UINT16)pstSetFileInfo->ulEfLen;

    /*lint -e534*/
    VOS_MemCpy(pstMsg->aucContent, pstSetFileInfo->pucEfContent, pstSetFileInfo->ulEfLen);

    pstMsg->stFilePath.ulPathLen        = (VOS_UINT32)VOS_StrLen(USIMM_USIM_STR);

    VOS_MemCpy(pstMsg->stFilePath.acPath, USIMM_USIM_STR, pstMsg->stFilePath.ulPathLen);

    SI_PIH_HexToAsciiCode((VOS_UINT8)((pstSetFileInfo->usEfId >> 12) & 0x0F), &pstMsg->stFilePath.acPath[pstMsg->stFilePath.ulPathLen]);
    SI_PIH_HexToAsciiCode((VOS_UINT8)((pstSetFileInfo->usEfId >> 8) & 0x0F), &pstMsg->stFilePath.acPath[pstMsg->stFilePath.ulPathLen + 1]);
    SI_PIH_HexToAsciiCode((VOS_UINT8)((pstSetFileInfo->usEfId >> 4) & 0x0F), &pstMsg->stFilePath.acPath[pstMsg->stFilePath.ulPathLen + 2]);
    SI_PIH_HexToAsciiCode((VOS_UINT8)((pstSetFileInfo->usEfId) & 0x0F), &pstMsg->stFilePath.acPath[pstMsg->stFilePath.ulPathLen + 3]);
    /*lint +e534*/

    pstMsg->stFilePath.ulPathLen += 4;

    return VOS_SendMsg(MAPS_PIH_PID, pstMsg);
}


VOS_UINT32 SI_PIH_UiccAuthHandle(
    SI_PIH_UICCAUTH_REQ_STRU            *pstMsg)
{
    USIMM_CARDAPP_ENUM_UINT32          enAppType;
    USIMM_AUTHENTICATION_REQ_STRU      *pstUsimMsg;

    if (SI_PIH_UICCAPP_USIM == pstMsg->stAuthData.enAppType)
    {
        enAppType           = USIMM_GUTL_APP;
    }
    else if (SI_PIH_UICCAPP_ISIM == pstMsg->stAuthData.enAppType)
    {
        enAppType           = USIMM_IMS_APP;
    }
    else
    {
        return USIMM_API_WRONG_PARA;
    }

    pstUsimMsg = (USIMM_AUTHENTICATION_REQ_STRU *)VOS_AllocMsg(MAPS_PIH_PID, sizeof(USIMM_AUTHENTICATION_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstUsimMsg)
    {
        PIH_NORMAL_LOG("SI_PIH_UiccAuthHandle: Alloc Auth Msg Fail");

        return USIMM_API_FAILED;
    }

    /* ����Ȩ��Ϣͷ */
    pstUsimMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstUsimMsg->stMsgHeader.enMsgName       = USIMM_AUTHENTICATION_REQ;
    pstUsimMsg->stMsgHeader.enAppType       = enAppType;
    pstUsimMsg->stMsgHeader.ulSendPara      = SI_PIH_SEND_PAPA(g_pstPIHCurrNode->usClient, g_pstPIHCurrNode->ulEventType);

    if (SI_PIH_UICCAUTH_AKA == pstMsg->stAuthData.enAuthType)
    {
        if (SI_PIH_UICCAPP_USIM == pstMsg->stAuthData.enAppType)
        {
            pstUsimMsg->enAuthType = USIMM_3G_AUTH;
        }
        else
        {
            pstUsimMsg->enAuthType = USIMM_IMS_AUTH;
        }

        /*lint -e534*/
        pstUsimMsg->uAuth.st3GAuth.stRand.ucDataLen = (VOS_UINT8)pstMsg->stAuthData.uAuthData.stAka.ulRandLen;
        VOS_MemCpy(pstUsimMsg->uAuth.st3GAuth.stRand.aucData,
                   pstMsg->stAuthData.uAuthData.stAka.aucRand,
                   pstUsimMsg->uAuth.st3GAuth.stRand.ucDataLen);

        pstUsimMsg->uAuth.st3GAuth.stAutn.ucDataLen = (VOS_UINT8)pstMsg->stAuthData.uAuthData.stAka.ulAuthLen;
        VOS_MemCpy(pstUsimMsg->uAuth.st3GAuth.stAutn.aucData,
                   pstMsg->stAuthData.uAuthData.stAka.aucAuth,
                   pstUsimMsg->uAuth.st3GAuth.stAutn.ucDataLen);
        /*lint +e534*/
    }

    if (SI_PIH_UICCAUTH_GBA == pstMsg->stAuthData.enAuthType)
    {
        pstUsimMsg->enAuthType  = USIMM_GBA_AUTH;

        /*lint -e534*/
        pstUsimMsg->uAuth.stGbaAuth.stRand.ucDataLen = (VOS_UINT8)pstMsg->stAuthData.uAuthData.stAka.ulRandLen;
        VOS_MemCpy(pstUsimMsg->uAuth.stGbaAuth.stRand.aucData,
                   pstMsg->stAuthData.uAuthData.stAka.aucRand,
                   pstUsimMsg->uAuth.stGbaAuth.stRand.ucDataLen);

        pstUsimMsg->uAuth.stGbaAuth.stAutn.ucDataLen = (VOS_UINT8)pstMsg->stAuthData.uAuthData.stAka.ulAuthLen;
        VOS_MemCpy(pstUsimMsg->uAuth.stGbaAuth.stAutn.aucData,
                   pstMsg->stAuthData.uAuthData.stAka.aucAuth,
                   pstUsimMsg->uAuth.stGbaAuth.stAutn.ucDataLen);
        /*lint +e534*/
    }

    if (SI_PIH_UICCAUTH_NAF == pstMsg->stAuthData.enAuthType)
    {
        pstUsimMsg->enAuthType  = USIMM_NAF_AUTH;

        /*lint -e534*/
        pstUsimMsg->uAuth.stNafAuth.stNafID.ucDataLen   = (VOS_UINT8)pstMsg->stAuthData.uAuthData.stKsNAF.ulNAFIDLen;
        VOS_MemCpy(pstUsimMsg->uAuth.stNafAuth.stNafID.aucData,
                   pstMsg->stAuthData.uAuthData.stKsNAF.aucNAFID,
                   pstUsimMsg->uAuth.stNafAuth.stNafID.ucDataLen);

        pstUsimMsg->uAuth.stNafAuth.stImpi.ucDataLen    = (VOS_UINT8)pstMsg->stAuthData.uAuthData.stKsNAF.ulIMPILen;
        VOS_MemCpy(pstUsimMsg->uAuth.stNafAuth.stImpi.aucData,
                   pstMsg->stAuthData.uAuthData.stKsNAF.aucIMPI,
                   pstUsimMsg->uAuth.stNafAuth.stImpi.ucDataLen);
        /*lint +e534*/
    }

    return VOS_SendMsg(MAPS_PIH_PID, pstUsimMsg);
}
VOS_UINT32 SI_PIH_AccessFileHandle(
    SI_PIH_ACCESSFILE_REQ_STRU          *pstMsg)
{
    SI_PIH_SETFILE_INFO_STRU            stSetFileInfo;
    SI_PIH_GETFILE_INFO_STRU            stGetFileInfo;

    if (SI_PIH_UICCAPP_USIM == pstMsg->stCmdData.enAppType)
    {
        stGetFileInfo.enAppType = USIMM_GUTL_APP;
        stSetFileInfo.enAppType = USIMM_GUTL_APP;
    }
    else if (SI_PIH_UICCAPP_ISIM == pstMsg->stCmdData.enAppType)
    {
        stGetFileInfo.enAppType = USIMM_IMS_APP;
        stSetFileInfo.enAppType = USIMM_IMS_APP;
    }
    else
    {
        return VOS_ERR;
    }

    if (SI_PIH_ACCESS_READ == pstMsg->stCmdData.enCmdType)
    {
        stGetFileInfo.usEfId        = pstMsg->stCmdData.usEfId;
        stGetFileInfo.ucRecordNum   = pstMsg->stCmdData.ucRecordNum;

        return SI_PIH_GetFileReq(SI_PIH_SEND_PAPA(g_pstPIHCurrNode->usClient, g_pstPIHCurrNode->ulEventType),
                                &stGetFileInfo);
    }
    else
    {
        stSetFileInfo.usEfId        = pstMsg->stCmdData.usEfId;
        stSetFileInfo.ucRecordNum   = pstMsg->stCmdData.ucRecordNum;
        stSetFileInfo.ulEfLen       = pstMsg->stCmdData.ulDataLen;
        stSetFileInfo.pucEfContent  = pstMsg->stCmdData.aucCommand;

        return SI_PIH_SetFileReq(&stSetFileInfo);
    }
}

/*****************************************************************************
�� �� ��  : SI_PIH_AuthCnfProc
��������  : Authentication cnf ��Ϣ������
�������  : pstMsg:Authenctication cnf ��Ϣ
�������  : ��
�� �� ֵ  : ��
History     :
1.��    ��  : 2014��03��20��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/
VOS_VOID SI_PIH_AuthCnfProc(
    USIMM_AUTHENTICATION_CNF_STRU       *pstMsg)
{
    SI_PIH_EVENT_INFO_STRU              stEvent;

    /*lint -e534*/
    VOS_MemSet(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));
    /*lint +e534*/

    if (USIMM_GUTL_APP == pstMsg->stCmdResult.enApptype)
    {
        stEvent.PIHEvent.UiccAuthCnf.enAppType = SI_PIH_UICCAPP_USIM;
    }
    else if (USIMM_IMS_APP == pstMsg->stCmdResult.enApptype)
    {
        stEvent.PIHEvent.UiccAuthCnf.enAppType = SI_PIH_UICCAPP_ISIM;
    }
    else
    {
        stEvent.PIHError = TAF_ERR_ERROR;
    }

    if (USIMM_3G_AUTH == pstMsg->enAuthType)
    {
        stEvent.PIHEvent.UiccAuthCnf.enAuthType = SI_PIH_UICCAUTH_AKA;

        /*lint -e534*/
        VOS_MemCpy(stEvent.PIHEvent.UiccAuthCnf.stAkaData.aucAuthRes, pstMsg->uCnfData.stTELECnf.aucAuthRes, sizeof(pstMsg->uCnfData.stTELECnf.aucAuthRes));
        VOS_MemCpy(stEvent.PIHEvent.UiccAuthCnf.stAkaData.aucAuts, pstMsg->uCnfData.stTELECnf.aucAuts, sizeof(pstMsg->uCnfData.stTELECnf.aucAuts));
        VOS_MemCpy(stEvent.PIHEvent.UiccAuthCnf.stAkaData.aucCK, pstMsg->uCnfData.stTELECnf.aucCK, sizeof(pstMsg->uCnfData.stTELECnf.aucCK));
        VOS_MemCpy(stEvent.PIHEvent.UiccAuthCnf.stAkaData.aucIK, pstMsg->uCnfData.stTELECnf.aucIK, sizeof(pstMsg->uCnfData.stTELECnf.aucIK));
        /*lint +e534*/
    }
    else if (USIMM_IMS_AUTH == pstMsg->enAuthType)
    {
        stEvent.PIHEvent.UiccAuthCnf.enAuthType = SI_PIH_UICCAUTH_AKA;

        /*lint -e534*/
        VOS_MemCpy(stEvent.PIHEvent.UiccAuthCnf.stAkaData.aucAuthRes, pstMsg->uCnfData.stIMSCnf.aucAuthRes, sizeof(pstMsg->uCnfData.stIMSCnf.aucAuthRes));
        VOS_MemCpy(stEvent.PIHEvent.UiccAuthCnf.stAkaData.aucAuts, pstMsg->uCnfData.stIMSCnf.aucAuts, sizeof(pstMsg->uCnfData.stIMSCnf.aucAuts));
        VOS_MemCpy(stEvent.PIHEvent.UiccAuthCnf.stAkaData.aucCK, pstMsg->uCnfData.stIMSCnf.aucCK, sizeof(pstMsg->uCnfData.stIMSCnf.aucCK));
        VOS_MemCpy(stEvent.PIHEvent.UiccAuthCnf.stAkaData.aucIK, pstMsg->uCnfData.stIMSCnf.aucIK, sizeof(pstMsg->uCnfData.stIMSCnf.aucIK));
        /*lint +e534*/
    }
    else if (USIMM_GBA_AUTH == pstMsg->enAuthType)
    {
        stEvent.PIHEvent.UiccAuthCnf.enAuthType = SI_PIH_UICCAUTH_GBA;

        /*lint -e534*/
        VOS_MemCpy(stEvent.PIHEvent.UiccAuthCnf.stAkaData.aucAuthRes, pstMsg->uCnfData.stIMSCnf.aucAuthRes, sizeof(pstMsg->uCnfData.stIMSCnf.aucAuthRes));
        /*lint +e534*/
    }
    else if (USIMM_NAF_AUTH == pstMsg->enAuthType)
    {
        stEvent.PIHEvent.UiccAuthCnf.enAuthType = SI_PIH_UICCAUTH_NAF;

        /*lint -e534*/
        VOS_MemCpy(stEvent.PIHEvent.UiccAuthCnf.stNAFData.aucKs_ext_NAF, pstMsg->uCnfData.stIMSCnf.aucKs_ext_NAF, pstMsg->uCnfData.stIMSCnf.aucKs_ext_NAF[0]+1);
        /*lint +e534*/
    }
    else
    {
        stEvent.PIHError = TAF_ERR_ERROR;
    }

    if ((USIMM_AUTH_UMTS_SUCCESS == pstMsg->enResult)
        ||(USIMM_AUTH_IMS_SUCCESS == pstMsg->enResult)
        ||(USIMM_AUTH_GSM_SUCCESS == pstMsg->enResult))
    {
        stEvent.PIHError = TAF_ERR_NO_ERROR;
        stEvent.PIHEvent.UiccAuthCnf.enStatus = SI_PIH_AUTH_SUCCESS;
    }
    else if(USIMM_AUTH_SYNC_FAILURE == pstMsg->enResult)
    {
        stEvent.PIHError = TAF_ERR_NO_ERROR;
        stEvent.PIHEvent.UiccAuthCnf.enStatus = SI_PIH_AUTH_SYNC;
    }
    else if(USIMM_AUTH_MAC_FAILURE == pstMsg->enResult)
    {
        stEvent.PIHError = TAF_ERR_NO_ERROR;
        stEvent.PIHEvent.UiccAuthCnf.enStatus = SI_PIH_AUTH_FAIL;
    }
    else
    {
        stEvent.PIHError = TAF_ERR_ERROR;
    }

    /*lint -e534*/
    (VOS_VOID)SI_PIH_EventCallBack(&stEvent);
    /*lint +e534*/

    return;
}


VOS_VOID SI_PIH_SetFileCnfProc(
    USIMM_UPDATEFILE_CNF_STRU           *pstMsg)
{
    SI_PIH_EVENT_INFO_STRU              stEvent;
    VOS_UINT16                          usEFID;

    SI_PIH_GetEFIDFromPath(&pstMsg->stFilePath, &usEFID);

    /*lint -e534*/
    VOS_MemSet(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));
    /*lint +e534*/

    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        stEvent.PIHError = TAF_ERR_NO_ERROR;
    }
    else
    {
        stEvent.PIHError = TAF_ERR_CME_OPT_NOT_SUPPORTED;
    }

    stEvent.PIHEvent.UiccAcsFileCnf.enCmdType   = SI_PIH_ACCESS_WRITE;
    stEvent.PIHEvent.UiccAcsFileCnf.ulResult    = pstMsg->stCmdResult.ulResult;
    stEvent.PIHEvent.UiccAcsFileCnf.usEfId      = usEFID;
    stEvent.PIHEvent.UiccAcsFileCnf.ucRecordNum = pstMsg->ucRecordNum;

    /*lint -e534*/
    (VOS_VOID)SI_PIH_EventCallBack(&stEvent);
    /*lint +e534*/

    return;
}

#endif  /*(FEATURE_ON == FEATURE_VSIM)*/

VOS_VOID SI_PIH_GetFileCnfProc(
    USIMM_READFILE_CNF_STRU             *pstMsg)
{
    SI_PIH_EVENT_INFO_STRU              stEvent;
    VOS_UINT32                          ulRest;
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT16                          usEFID;
#endif

    /*lint -e534*/
    VOS_MemSet(&stEvent, 0, sizeof(stEvent));
    /*lint +e534*/

    if (SI_PIH_EVENT_CIMI_QRY_CNF == SI_PIH_EVENT_TYPE(pstMsg->stCmdResult.ulSendPara))
    {
        /* ����δ�ɹ� */
        stEvent.PIHError = pstMsg->stCmdResult.ulErrorCode;

        if(USIMM_IMSI_MAX_LEN < pstMsg->aucEf[0])
        {
            stEvent.PIHError = TAF_ERR_ERROR;
        }

        if (TAF_ERR_NO_ERROR == stEvent.PIHError)
        {
            /* �ַ�ת������ */
            ulRest = SI_PIH_ImsiBcd2Ascii((VOS_UINT8)(pstMsg->aucEf[0] * 2),
                                          &pstMsg->aucEf[1],
                                          stEvent.PIHEvent.stImsi.aucImsi);

            stEvent.PIHError = ulRest;
        }

        (VOS_VOID)SI_PIH_EventCallBack(&stEvent);

        return;
    }

    if (SI_PIH_EVENT_CCIMI_QRY_CNF == SI_PIH_EVENT_TYPE(pstMsg->stCmdResult.ulSendPara))
    {
        /* ����δ�ɹ� */
        stEvent.PIHError = pstMsg->stCmdResult.ulErrorCode;

        /* �ַ�ת������ */
        if (TAF_ERR_NO_ERROR == stEvent.PIHError)
        {
            /* �ַ�ת������ */
            ulRest = SI_PIH_CImsiBcd2Ascii(&pstMsg->aucEf[0],
                                           stEvent.PIHEvent.stImsi.aucImsi);
            stEvent.PIHError = ulRest;
        }

        (VOS_VOID)SI_PIH_EventCallBack(&stEvent);

        return;
    }

#if (FEATURE_ON == FEATURE_IMS)
    SI_PIH_GetEFIDFromPath(&pstMsg->stFilePath, &usEFID);

    /*lint -e534*/
    VOS_MemSet(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));
    /*lint +e534*/

    stEvent.PIHEvent.UiccAcsFileCnf.enCmdType   = SI_PIH_ACCESS_READ;
    stEvent.PIHEvent.UiccAcsFileCnf.ulResult    = pstMsg->stCmdResult.ulResult;
    stEvent.PIHEvent.UiccAcsFileCnf.usEfId      = usEFID;
    stEvent.PIHEvent.UiccAcsFileCnf.ucRecordNum = pstMsg->ucRecordNum;

    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        stEvent.PIHEvent.UiccAcsFileCnf.ulDataLen = (pstMsg->usEfLen > USIMM_T0_APDU_MAX_LEN)?(USIMM_T0_APDU_MAX_LEN):pstMsg->usEfLen;

        stEvent.PIHError = TAF_ERR_NO_ERROR;

        /*lint -e534*/
        VOS_MemCpy(stEvent.PIHEvent.UiccAcsFileCnf.aucCommand, pstMsg->aucEf, stEvent.PIHEvent.UiccAcsFileCnf.ulDataLen);
        /*lint +e534*/
    }
    else
    {
        stEvent.PIHError = TAF_ERR_CME_OPT_NOT_SUPPORTED;
    }

    /*lint -e534*/
    (VOS_VOID)SI_PIH_EventCallBack(&stEvent);
    /*lint +e534*/
#endif

    return;
}

/*****************************************************************************
�� �� ��  : SI_PIH_CardTypeQueryHandle
��������  : AT/APP��������
�������  : ��
�������  : ��
�� �� ֵ  : VOS_UINT32 ����ִ�н��
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2014��06��04��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/
VOS_UINT32 SI_PIH_CardTypeQueryHandle(
    SI_PIH_MSG_HEADER_STRU              *pMsg)
{
    SI_PIH_EVENT_INFO_STRU              stEvent;
#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)
    VOS_UINT32                          ulCardMode;
    VOS_BOOL                            bHasCModule;
    VOS_BOOL                            bHasGModule;
#endif

    /*lint -e534*/
    VOS_MemSet(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));
    /*lint +e534*/

#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)
    if (USIMM_API_SUCCESS == USIMM_GetCardCGType(&ulCardMode, &bHasCModule, &bHasGModule))
    {
        stEvent.PIHEvent.CardTypeCnf.ucHasCModule = (VOS_UINT8)bHasCModule;

        stEvent.PIHEvent.CardTypeCnf.ucHasGModule = (VOS_UINT8)bHasGModule;

        if (USIMM_PHYCARD_TYPE_ICC == ulCardMode)
        {
            stEvent.PIHEvent.CardTypeCnf.ucMode = SI_PIH_CARD_ICC_TYPE;
        }
        else if (USIMM_PHYCARD_TYPE_UICC == ulCardMode)
        {
            stEvent.PIHEvent.CardTypeCnf.ucMode = SI_PIH_CARD_UICC_TYPE;
        }
        else
        {
            stEvent.PIHEvent.CardTypeCnf.ucMode = SI_PIH_CARD_NON_TYPE;
        }

        stEvent.PIHError = TAF_ERR_NO_ERROR;
    }
#else
    if (USIMM_API_SUCCESS == USIMM_GetCardCGType(&stEvent.PIHEvent.CardTypeCnf.ucMode,
                                                &stEvent.PIHEvent.CardTypeCnf.ucHasCModule,
                                                &stEvent.PIHEvent.CardTypeCnf.ucHasGModule))
    {
        stEvent.PIHError = TAF_ERR_NO_ERROR;
    }
#endif
    else
    {
        stEvent.PIHError = TAF_ERR_PARA_ERROR;
    }

    /*����ظ�*/
    return SI_PIH_EventCallBack(&stEvent);
}
VOS_UINT32 SI_PIH_CrsmSetHandle(
    SI_PIH_MSG_HEADER_STRU              *pstMsg)
{
    SI_PIH_CRSM_SET_REQ_STRU           *pstCrsmMsg;
    USIMM_RACCESS_REQ_STRU             *pstRAccessMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLength;

    /* ��ʼ�� */
    ulMsgLength     = 0;

    /* ������� */
    if (VOS_NULL_PTR == pstMsg)
    {
        PIH_ERROR_LOG("SI_PIH_CrsmSetHandle: pstMsg Is NULL.");

        return USIMM_API_WRONG_PARA;
    }

    /* ������Ϣ�ڴ沢��ʼ�� */
    ulMsgLength = sizeof(USIMM_RACCESS_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstRAccessMsg = (USIMM_RACCESS_REQ_STRU*)VOS_AllocMsg(MAPS_PIH_PID, ulMsgLength);

    if (VOS_NULL_PTR == pstRAccessMsg)
    {
        PIH_ERROR_LOG("SI_PIH_CrsmSetHandle: Allocate Msg Failed.");

        return USIMM_API_FAILED;
    }

    /* ��д��Ϣͷ */
    pstRAccessMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstRAccessMsg->stMsgHeader.enMsgName       = USIMM_RACCESS_REQ;
    pstRAccessMsg->stMsgHeader.enAppType       = USIMM_UNLIMIT_AUTO;

    if (VOS_NULL_PTR == g_pstPIHCurrNode)
    {
        pstRAccessMsg->stMsgHeader.ulSendPara  = VOS_NULL;
    }
    else
    {
        pstRAccessMsg->stMsgHeader.ulSendPara  = SI_PIH_SEND_PAPA(g_pstPIHCurrNode->usClient, g_pstPIHCurrNode->ulEventType);
    }

    pstCrsmMsg = (SI_PIH_CRSM_SET_REQ_STRU*)pstMsg;

    /* ��д��Ϣ�� */
    pstRAccessMsg->enCmdType                   = pstCrsmMsg->stMsgContent.enCmdType;
    pstRAccessMsg->ucP1                        = pstCrsmMsg->stMsgContent.ucP1;
    pstRAccessMsg->ucP2                        = pstCrsmMsg->stMsgContent.ucP2;
    pstRAccessMsg->ucP3                        = pstCrsmMsg->stMsgContent.ucP3;
    pstRAccessMsg->usEfId                      = pstCrsmMsg->stMsgContent.usEfId;

    /* �����ļ�·�� */
    pstRAccessMsg->usPathLen                   = ((pstCrsmMsg->stMsgContent.usPathLen > USIMM_MAX_PATH_LEN)?\
                                                   USIMM_MAX_PATH_LEN:pstCrsmMsg->stMsgContent.usPathLen);

    /* �ļ�·��������U16Ϊ��λ�ģ�·�������ĳ���Ҫ��2 */
    (VOS_VOID)VOS_MemCpy(pstRAccessMsg->ausPath,
                        pstCrsmMsg->stMsgContent.ausPath,
                        (pstRAccessMsg->usPathLen) * sizeof(VOS_UINT16));

    /* ����P3��������<DATA>�ֶ� */
    (VOS_VOID)VOS_MemCpy(pstRAccessMsg->aucContent,
                        pstCrsmMsg->stMsgContent.aucContent,
                        pstCrsmMsg->stMsgContent.ucP3);

    /* ����VOS����ԭ�� */
    return VOS_SendMsg(MAPS_PIH_PID, pstRAccessMsg);
}
VOS_UINT32 SI_PIH_CrlaSetHandle(
    SI_PIH_MSG_HEADER_STRU              *pMsg)
{
    SI_PIH_CRLA_SET_REQ_STRU           *pstCrlaMsg;
    USIMM_RACCESS_REQ_STRU             *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLength;
    USIMM_CARDAPP_ENUM_UINT32           enAppType;

    /* ��ʼ�� */
    ulMsgLength     = 0;
    pstCrlaMsg      = (SI_PIH_CRLA_SET_REQ_STRU*)pMsg;

    /* ������� */
    if (VOS_NULL_PTR == pstCrlaMsg)
    {
        PIH_ERROR_LOG("SI_PIH_CrlaSetHandle: psCrlaMsg Is NULL.");

        return USIMM_API_WRONG_PARA;
    }

    /* ��ΪICC����Ĭ�ϲ�����ͨ�� */
    if (USIMM_PHYCARD_TYPE_ICC == g_stPihCardInfo.enPhyCardType)
    {
        enAppType = USIMM_UNLIMIT_AUTO;
    }
    /* UICC��ͨ��SessionID������Ӧ������ */
    else
    {
        if (VOS_OK != SI_PIH_GetAppBySession(pstCrlaMsg->stMsgContent.ulSessionID,
                                             &enAppType))
        {
            PIH_ERROR_LOG("SI_PIH_CrlaSetHandle: ulSessionID Is Incorret.");

            return USIMM_API_WRONG_PARA;
        }
    }

    /* ������Ϣ�ڴ沢��ʼ�� */
    ulMsgLength = sizeof(USIMM_RACCESS_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg = (USIMM_RACCESS_REQ_STRU*)VOS_AllocMsg(MAPS_PIH_PID, ulMsgLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        PIH_ERROR_LOG("SI_PIH_CrlaSetHandle: Allocate Msg Failed.");

        return USIMM_API_FAILED;
    }

    /* ��д��Ϣͷ */
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.enMsgName       = USIMM_RACCESS_REQ;
    pstMsg->stMsgHeader.enAppType       = enAppType;

    if (VOS_NULL_PTR == g_pstPIHCurrNode)
    {
        pstMsg->stMsgHeader.ulSendPara  = VOS_NULL;
    }
    else
    {
        pstMsg->stMsgHeader.ulSendPara  = SI_PIH_SEND_PAPA(g_pstPIHCurrNode->usClient, g_pstPIHCurrNode->ulEventType);
    }

    /* ��д��Ϣ�� */
    pstMsg->enCmdType                   = pstCrlaMsg->stMsgContent.enCmdType;
    pstMsg->ucP1                        = pstCrlaMsg->stMsgContent.ucP1;
    pstMsg->ucP2                        = pstCrlaMsg->stMsgContent.ucP2;
    pstMsg->ucP3                        = pstCrlaMsg->stMsgContent.ucP3;
    pstMsg->usEfId                      = pstCrlaMsg->stMsgContent.usEfId;

    /* �����ļ�·�� */
    pstMsg->usPathLen                   = ((pstCrlaMsg->stMsgContent.usPathLen > USIMM_MAX_PATH_LEN)?\
                                          USIMM_MAX_PATH_LEN:pstCrlaMsg->stMsgContent.usPathLen);

    /* �ļ�·��������U16Ϊ��λ�ģ�·�������ĳ���Ҫ��2 */
    (VOS_VOID)VOS_MemCpy(pstMsg->ausPath,
                        pstCrlaMsg->stMsgContent.ausPath,
                        (pstMsg->usPathLen) * sizeof(VOS_UINT16));

    /* ����P3��������<DATA>�ֶ� */
    (VOS_VOID)VOS_MemCpy(pstMsg->aucContent,
                        pstCrlaMsg->stMsgContent.aucContent,
                        pstCrlaMsg->stMsgContent.ucP3);

    /* ����VOS����ԭ�� */
    return VOS_SendMsg(MAPS_PIH_PID, pstMsg);
}
VOS_UINT32 SI_PIH_CardSessionQueryHandle(
    SI_PIH_MSG_HEADER_STRU              *pstMsg)
{
    SI_PIH_EVENT_INFO_STRU              stEvent = {0};
    VOS_UINT32                          i;

    /* ����δ�ɹ� */
    stEvent.PIHError = VOS_OK;

    for (i = 0; i < USIMM_CARDAPP_BUTT; i++)
    {
        (VOS_VOID)SI_PIH_GetAppSession(i, &stEvent.PIHEvent.aulSessionID[i]);
    }

    return SI_PIH_EventCallBack(&stEvent);
}
VOS_UINT32 SI_PIH_IMSICheckPinSatus(VOS_UINT32 ulCardStatus)
{
    VOS_UINT32                         ulErrorCode;

    switch (ulCardStatus)
    {
        case USIMM_CARD_SERVIC_AVAILABLE:
            ulErrorCode = TAF_ERR_NO_ERROR;
            break;

        case USIMM_CARD_SERVIC_SIM_PIN:
            ulErrorCode = TAF_ERR_NEED_PIN1;
            break;

        case USIMM_CARD_SERVIC_SIM_PUK:
            ulErrorCode = TAF_ERR_NEED_PUK1;
            break;

        case USIMM_CARD_SERVIC_UNAVAILABLE:
            ulErrorCode = TAF_ERR_USIM_SIM_INVALIDATION;
            break;

        case USIMM_CARD_SERVIC_ABSENT:
            ulErrorCode = TAF_ERR_ERROR;
            break;

        default:
            ulErrorCode = TAF_ERR_UNSPECIFIED_ERROR;
            break;
    }

    return ulErrorCode;
}


VOS_UINT32 SI_PIH_CIMIQueryHandle(
    SI_PIH_MSG_HEADER_STRU              *pstMsg)
{
    SI_PIH_EVENT_INFO_STRU              stEvent     = {0};
    USIMM_READFILE_REQ_STRU            *pstReadMsg;
#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)
    VOS_UINT32                          ulCardMode  = USIMM_PHYCARD_TYPE_BUTT;
    VOS_BOOL                            bHasCModule = VOS_FALSE;
    VOS_BOOL                            bHasGModule = VOS_FALSE;

    /* ��ȡ����ǰ״̬ */
    if (USIMM_CARD_SERVIC_ABSENT == g_stPihCardInfo.enGUTLSvcStatus)
    {
        (VOS_VOID)USIMM_GetCardCGType(&ulCardMode, &bHasCModule, &bHasGModule);

        if (VOS_FALSE == bHasGModule)
        {
            PIH_WARNING_LOG("SI_PIH_CIMIQueryHandle: Card Status err");

            /* �ظ�AT */
            stEvent.PIHError = TAF_ERR_ERROR;

            (VOS_VOID)SI_PIH_EventCallBack(&stEvent);

            return VOS_OK;
        }
    }
    else
    {
        stEvent.PIHError = SI_PIH_IMSICheckPinSatus(g_stPihCardInfo.enGUTLSvcStatus);

        if (TAF_ERR_NO_ERROR != stEvent.PIHError)
        {
            PIH_WARNING_LOG("SI_PIH_CIMIQueryHandle: Card Status Wrong");

            /* �ظ�AT */
            (VOS_VOID)SI_PIH_EventCallBack(&stEvent);

            return VOS_OK;
        }
    }
#else
    stEvent.PIHError = SI_PIH_IMSICheckPinSatus(g_stPihCardInfo.enGUTLSvcStatus);

    if (TAF_ERR_NO_ERROR != stEvent.PIHError)
    {
        PIH_WARNING_LOG("SI_PIH_CIMIQueryHandle: Card Status Wrong");

        /* �ظ�AT */
        (VOS_VOID)SI_PIH_EventCallBack(&stEvent);

        return VOS_OK;
    }
#endif

    pstReadMsg = (USIMM_READFILE_REQ_STRU*)VOS_AllocMsg(MAPS_PIH_PID,
                                                        sizeof(USIMM_READFILE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstReadMsg)
    {
        PIH_WARNING_LOG("SI_PIH_CIMIQueryHandle: VOS_AllocMsg is Failed");

        return VOS_ERR;
    }

    /* ��ΪICC����Ĭ�ϲ�����ͨ�� */
    if (USIMM_PHYCARD_TYPE_ICC == g_stPihCardInfo.enPhyCardType)
    {
        pstReadMsg->stMsgHeader.enAppType       = USIMM_UNLIMIT_AUTO;

        pstReadMsg->stFilePath.ulPathLen        = VOS_StrLen(USIMM_GSM_EFIMSI_STR);

        (VOS_VOID)VOS_MemCpy(pstReadMsg->stFilePath.acPath,
                             USIMM_GSM_EFIMSI_STR,
                             pstReadMsg->stFilePath.ulPathLen);
    }
    else
    {
        pstReadMsg->stMsgHeader.enAppType       = USIMM_GUTL_APP;

        pstReadMsg->stFilePath.ulPathLen        = VOS_StrLen(USIMM_USIM_EFIMSI_STR);

        (VOS_VOID)VOS_MemCpy(pstReadMsg->stFilePath.acPath,
                             USIMM_USIM_EFIMSI_STR,
                             pstReadMsg->stFilePath.ulPathLen);
    }

    /* ������ݽṹ���Զ�ȡ�������ļ��ķ�ʽ��ȡ6F07�ļ���P1/P2/P3�ֱ�Ϊ0��0��9. �ļ�·��Ϊ�գ���Ĭ��·�������� */
    pstReadMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstReadMsg->stMsgHeader.enMsgName       = USIMM_READFILE_REQ;

    pstReadMsg->stMsgHeader.ulSendPara      = SI_PIH_SEND_PAPA(g_pstPIHCurrNode->usClient, g_pstPIHCurrNode->ulEventType);
    pstReadMsg->bNeedReadCache              = VOS_FALSE;
    pstReadMsg->ucRecordNum                 = 0;

    return VOS_SendMsg(MAPS_PIH_PID, pstReadMsg);

}


VOS_UINT32 SI_PIH_CCIMIQueryHandle(
    SI_PIH_MSG_HEADER_STRU              *pstMsg)
{
    USIMM_READFILE_REQ_STRU            *pstReadMsg;

    pstReadMsg = (USIMM_READFILE_REQ_STRU*)VOS_AllocMsg(MAPS_PIH_PID,
                                                        sizeof(USIMM_READFILE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstReadMsg)
    {
        PIH_WARNING_LOG("SI_PIH_CCIMIQueryHandle: VOS_AllocMsg is Failed");

        return VOS_ERR;
    }

    /* ��ΪICC����Ĭ�ϲ�����ͨ�� */
    if (USIMM_PHYCARD_TYPE_ICC == g_stPihCardInfo.enPhyCardType)
    {
        pstReadMsg->stMsgHeader.enAppType       = USIMM_UNLIMIT_AUTO;

        pstReadMsg->stFilePath.ulPathLen        = VOS_StrLen(USIMM_CDMA_EFIMSIM_STR);

        (VOS_VOID)VOS_MemCpy(pstReadMsg->stFilePath.acPath,
                         USIMM_CDMA_EFIMSIM_STR,
                         pstReadMsg->stFilePath.ulPathLen);
    }
    else
    {
        pstReadMsg->stMsgHeader.enAppType       = USIMM_CDMA_APP;

        pstReadMsg->stFilePath.ulPathLen        = VOS_StrLen(USIMM_CSIM_EFIMSIM_STR);

        (VOS_VOID)VOS_MemCpy(pstReadMsg->stFilePath.acPath,
                         USIMM_CSIM_EFIMSIM_STR,
                         pstReadMsg->stFilePath.ulPathLen);
    }

    /* ������ݽṹ���Զ�ȡ�������ļ��ķ�ʽ��ȡ6F07�ļ���P1/P2/P3�ֱ�Ϊ0��0��9. �ļ�·��Ϊ�գ���Ĭ��·�������� */
    pstReadMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstReadMsg->stMsgHeader.enMsgName       = USIMM_READFILE_REQ;

    pstReadMsg->stMsgHeader.ulSendPara      = SI_PIH_SEND_PAPA(g_pstPIHCurrNode->usClient, g_pstPIHCurrNode->ulEventType);
    pstReadMsg->bNeedReadCache              = VOS_FALSE;
    pstReadMsg->ucRecordNum                 = 0;

    return VOS_SendMsg(MAPS_PIH_PID, pstReadMsg);

}

VOS_UINT32  SI_PIH_MsgSyncProc(
    PS_SI_MSG_STRU                      *pMsg
)
{
    VOS_UINT32                          ulResult = VOS_OK;

    switch(pMsg->ulMsgName)
    {
        case SI_PIH_BDN_QUERY_REQ:
            USIMM_BdnQuery(&ulResult);
            ulResult = SI_PIH_FdnBdnStateReport(ulResult, TAF_ERR_NO_ERROR, SI_PIH_FDN_BDN_QUERY);
            break;

        case SI_PIH_FDN_QUERY_REQ:
            USIMM_FdnQuery(&ulResult);
            ulResult = SI_PIH_FdnBdnStateReport(ulResult, TAF_ERR_NO_ERROR, SI_PIH_FDN_BDN_QUERY);
            break;

        case SI_PIH_CARD_ATR_QRY_REQ:
            PIH_NORMAL_LOG("SI_PIH_MsgSyncProc:NORMAL:SI_PIH_CARD_ATR_QRY_REQ.");
            ulResult = SI_PIH_ATRQryReqProc();
            break;

        case SI_PIH_HVSST_QUERY_REQ:
            PIH_NORMAL_LOG("SI_PIH_MsgSyncProc:NORMAL:SI_PIH_HVSST_QUERY_REQ.");
            ulResult = SI_PIH_HVSSTQueryHandle((SI_PIH_MSG_HEADER_STRU *)pMsg);
            break;

        case SI_PIH_SCICFG_SET_REQ:
            PIH_NORMAL_LOG("SI_PIH_MsgSyncProc:NORMAL:SI_PIH_SCICFG_SET_REQ.");
            ulResult = SI_PIH_SciCfgSetHandle((SI_PIH_SCICFG_SET_REQ_STRU *)pMsg);
            break;

        case SI_PIH_SCICFG_QUERY_REQ:
            PIH_NORMAL_LOG("SI_PIH_MsgSyncProc:NORMAL:SI_PIH_SCICFG_QUERY_REQ.");
            ulResult = SI_PIH_SciCfgQueryHandle((SI_PIH_MSG_HEADER_STRU *)pMsg);
            break;

#if (FEATURE_VSIM == FEATURE_ON)
        case SI_PIH_HVSDH_SET_REQ:
            PIH_NORMAL_LOG("SI_PIH_MsgSyncProc:NORMAL:SI_PIH_HVSDH_SET_REQ.");
            ulResult = SI_PIH_HvsDHSetHandle(((SI_PIH_HVSDH_SET_REQ_STRU*)pMsg)->ulDataLen, ((SI_PIH_HVSDH_SET_REQ_STRU*)pMsg)->aucData);
            break;

        case SI_PIH_HVSDH_QRY_REQ:
            PIH_NORMAL_LOG("SI_PIH_MsgSyncProc:NORMAL:SI_PIH_HVSDH_QRY_REQ.");
            ulResult = SI_PIH_HvsDHQueryHandle();
            break;

        case SI_PIH_HVSCONT_QRY_REQ:
            PIH_NORMAL_LOG("SI_PIH_MsgSyncProc:NORMAL:SI_PIH_HVSCONT_QRY_REQ.");
            ulResult = SI_PIH_HvsContQueryHandle();
            break;

        case SI_PIH_FILE_WRITE_REQ:
            PIH_NORMAL_LOG("SI_PIH_MsgSyncProc:NORMAL:SI_PIH_FILE_WRITE_REQ.");
            ulResult = SI_PIH_ATFileWriteHandle((SI_PIH_FILE_WRITE_REQ_STRU *)pMsg);
            break;

        case SI_PIH_HVTEE_SET_REQ:
            PIH_NORMAL_LOG("SI_SIM_AppMsgProc:NORMAL:SI_PIH_HVTEE_SET_REQ.");
            ulResult = SI_PIH_HvteeSetHandle((SI_PIH_HVTEE_SET_REQ_STRU *)pMsg);
            break;

        case SI_PIH_HVCHECKCARD_REQ:
            PIH_NORMAL_LOG("SI_PIH_MsgSyncProc:NORMAL:SI_PIH_HVCHECKCARD_REQ.");
            ulResult = SI_PIH_HvCheckCardHandle((SI_PIH_HVCHECKCARD_REQ_STRU *)pMsg);
            break;
#endif

        case SI_PIH_CARDTYPE_QUERY_REQ:
            PIH_NORMAL_LOG("SI_PIH_MsgSyncProc:NORMAL:SI_PIH_CARDTYPE_QUERY_REQ.");
            ulResult = SI_PIH_CardTypeQueryHandle((SI_PIH_MSG_HEADER_STRU *)pMsg);
            break;

        case SI_PIH_SESSION_QRY_REQ:
            PIH_NORMAL_LOG("SI_SIM_AppMsgProc:NORMAL:SI_PIH_SESSION_QRY_REQ.");
            ulResult = SI_PIH_CardSessionQueryHandle((SI_PIH_MSG_HEADER_STRU *)pMsg);
            break;

        default:
            ulResult = VOS_ERR;
            break;
    };

    return ulResult;
}


VOS_UINT32  SI_PIH_MsgAsyncProc(
    PS_SI_MSG_STRU                      *pMsg
)
{
    VOS_UINT32                          ulResult = VOS_OK;

    switch(pMsg->ulMsgName)
    {
        case SI_PIH_FDN_ENABLE_REQ: /* USIMM_FBDNPROCESS_REQ->USIMM_FBDNPROCESS_CNF->SI_PIH_EVENT_FDN_CNF */
            PIH_NORMAL_LOG("SI_PIH_MsgAsyncProc:NORMAL:FDN_ENABLE_REQ.");
            ulResult = SI_PIH_SendFdnReqMsg(USIMM_FDN_ACTIVE, ((SI_PIH_FDN_ENABLE_REQ_STRU*)pMsg)->aucPIN2);
            break;

        case SI_PIH_FDN_DISALBE_REQ: /* USIMM_FBDNPROCESS_REQ->USIMM_FBDNPROCESS_CNF->SI_PIH_EVENT_FDN_CNF */
            PIH_NORMAL_LOG("SI_PIH_MsgAsyncProc:NORMAL:FDN_DISALBE_REQ.");
            ulResult = SI_PIH_SendFdnReqMsg(USIMM_FDN_DEACTIVE, ((SI_PIH_FDN_ENABLE_REQ_STRU*)pMsg)->aucPIN2);
            break;

        case SI_PIH_GACCESS_REQ: /* USIMM_SENDTPDUDATA_REQ->USIMM_SENDTPDUDATA_CNF->SI_PIH_EVENT_GENERIC_ACCESS_CNF*/
            PIH_NORMAL_LOG("SI_PIH_MsgAsyncProc:NORMAL:SI_PIH_GACCESS_REQ.");
            ulResult = SI_PIH_GAccessReqProc((SI_PIH_GACCESS_REQ_STRU *)pMsg);
            break;

        case SI_PIH_PCSC_DATA_REQ: /* USIMM_SENDTPDUDATA_REQ->USIMM_SENDTPDUDATA_CNF */
            PIH_NORMAL_LOG("SI_PIH_MsgAsyncProc:NORMAL:SI_PIH_PCSC_REQ.");
            ulResult = SI_PIH_PCSCCmdHandle((SI_PIH_PCSC_REQ_STRU *)pMsg);
            break;

        case SI_PIH_ISDB_ACCESS_REQ: /* USIMM_SENDTPDUDATA_REQ->USIMM_SENDTPDUDATA_CNF->SI_PIH_EVENT_ISDB_ACCESS_CNF */
            PIH_NORMAL_LOG("SI_PIH_MsgAsyncProc:NORMAL:SI_PIH_ISDB_ACCESS_REQ.");
            ulResult = SI_PIH_IsdbAccessReqProc((SI_PIH_ISDB_ACCESS_REQ_STRU *)pMsg);
            break;

        case SI_PIH_CCHO_SET_REQ: /* USIMM_OPENCHANNEL_REQ->USIMM_OPENCHANNEL_CNF->SI_PIH_EVENT_CCHO_SET_CNF */
            PIH_NORMAL_LOG("SI_PIH_MsgAsyncProc:NORMAL:SI_PIH_CCHO_SET_REQ.");
            ulResult = SI_PIH_CchoSetReqProc((SI_PIH_CCHO_SET_REQ_STRU *)pMsg);
            break;

        case SI_PIH_CCHC_SET_REQ: /* USIMM_CLOSECHANNEL_REQ->USIMM_CLOSECHANNEL_CNF->SI_PIH_EVENT_CCHC_SET_CNF */
            PIH_NORMAL_LOG("SI_SIM_AppMsgProc:NORMAL:SI_PIH_CCHC_SET_REQ.");
            ulResult = SI_PIH_CchcSetReqProc((SI_PIH_CCHC_SET_REQ_STRU *)pMsg);
            break;

        case SI_PIH_CGLA_SET_REQ: /* USIMM_SENDTPDUDATA_REQ->USIMM_SENDTPDUDATA_CNF->SI_PIH_EVENT_CGLA_SET_CNF */
            PIH_NORMAL_LOG("SI_PIH_MsgAsyncProc:NORMAL:SI_PIH_CGLA_SET_REQ.");
            ulResult = SI_PIH_CglaSetReqProc((SI_PIH_CGLA_REQ_STRU *)pMsg);
            break;

        case SI_PIH_HVSST_SET_REQ: /* USIMM_ACTIVECARD_REQ->USIMM_ACTIVECARD_CNF->SI_PIH_EVENT_HVSST_SET_CNF */
            PIH_NORMAL_LOG("SI_PIH_MsgAsyncProc:NORMAL:SI_PIH_HVSST_SET_REQ.");
            ulResult = SI_PIH_HVSSTSetHandle((SI_PIH_HVSST_REQ_STRU *)pMsg);
            break;

#if (FEATURE_ON == FEATURE_IMS)
        case SI_PIH_UICCAUTH_REQ: /* USIMM_AUTHENTICATION_REQ->USIMM_AUTHENTICATION_CNF->SI_PIH_EVENT_UICCAUTH_CNF */
            PIH_NORMAL_LOG("SI_PIH_MsgAsyncProc:NORMAL:SI_PIH_UICCAUTH_REQ.");
            ulResult = SI_PIH_UiccAuthHandle((SI_PIH_UICCAUTH_REQ_STRU *)pMsg);
            break;

        case SI_PIH_URSM_REQ: /* USIMM_UPDATEFILE_REQ,USIMM_READFILE_REQ->USIMM_UPDATEFILE_CNF,USIMM_READFILE_CNF->SI_PIH_EVENT_URSM_CNF */
            PIH_NORMAL_LOG("SI_PIH_MsgAsyncProc:NORMAL:SI_PIH_URSM_REQ.");
            ulResult = SI_PIH_AccessFileHandle((SI_PIH_ACCESSFILE_REQ_STRU *)pMsg);
            break;
#endif
        case SI_PIH_CRSM_SET_REQ:
            PIH_NORMAL_LOG("SI_SIM_AppMsgProc:NORMAL:SI_PIH_CRSM_SET_REQ.");
            ulResult = SI_PIH_CrsmSetHandle((SI_PIH_MSG_HEADER_STRU *)pMsg);
            break;

        case SI_PIH_CRLA_SET_REQ:
            PIH_NORMAL_LOG("SI_SIM_AppMsgProc:NORMAL:SI_PIH_CRLA_SET_REQ.");
            ulResult = SI_PIH_CrlaSetHandle((SI_PIH_MSG_HEADER_STRU *)pMsg);
            break;

        case SI_PIH_CIMI_QRY_REQ:
            PIH_NORMAL_LOG("SI_SIM_AppMsgProc:NORMAL:SI_PIH_CIMI_QRY_REQ.");
            ulResult = SI_PIH_CIMIQueryHandle((SI_PIH_MSG_HEADER_STRU *)pMsg);
            break;

        case SI_PIH_CCIMI_QRY_REQ:
            PIH_NORMAL_LOG("SI_SIM_AppMsgProc:NORMAL:SI_PIH_CCIMI_QRY_REQ.");
            ulResult = SI_PIH_CCIMIQueryHandle((SI_PIH_MSG_HEADER_STRU *)pMsg);
            break;

        default:
            PIH_WARNING_LOG("SI_PIH_MsgAsyncProc:WARNING:DEFAULT Unkown Msg.");
            ulResult = VOS_ERR;
            break;
    }

    return ulResult;
}
VOS_UINT32  SI_PIH_MsgProc(
    PS_SI_MSG_STRU                      *pMsg
)
{
    VOS_UINT32                          ulResult;
    SI_PIH_MSG_HEADER_STRU             *pstMsg;

    pstMsg = (SI_PIH_MSG_HEADER_STRU*)pMsg;

    /*������Ϣ�����¼����ֱ�ӷ���*/
    if ((SI_PIH_USIMREG_PID_HOOK        == pMsg->ulMsgName)
        ||(SI_PIH_REFRESHREG_PID_HOOK   == pMsg->ulMsgName)
        ||(SI_PIH_ISIMREG_PID_HOOK      == pMsg->ulMsgName)
        ||(SI_PIH_HVTEE_DATA_HOOK       == pMsg->ulMsgName))
    {
        return VOS_OK;
    }

    /* �жϵ�ǰ��ClientId�Ƿ��Ѿ��ڶ����� */
    ulResult = SI_PIH_ParaCheck(pstMsg->usClient);

    if(VOS_OK != ulResult)
    {
        PIH_WARNING1_LOG("SI_PIH_MsgProc:WARNING:EventType:", (VOS_INT32)pstMsg->ulEventType);

        SI_PIH_EventReportError(pstMsg->usClient,
                                pstMsg->ucOpID,
                                ulResult,
                                pMsg->ulMsgName,
                                pstMsg->ulEventType);

        return ulResult;
    }

    g_pstPIHCurrNode = SI_PIH_GetCtrlNode(SI_PIH_INFO_FREE_LIST_ID);

    if (VOS_NULL_PTR == g_pstPIHCurrNode)
    {
        PIH_WARNING1_LOG("SI_PIH_MsgProc:WARNING:EventType:", (VOS_INT32)pstMsg->ulEventType);

        SI_PIH_EventReportError(pstMsg->usClient,
                                pstMsg->ucOpID,
                                TAF_ERR_SIM_BUSY,
                                pMsg->ulMsgName,
                                pstMsg->ulEventType);

        return TAF_ERR_SIM_BUSY;
    }

    /*����ִ����Ϣ����ز����������ٺ����Ļظ�ʱ����*/
    g_pstPIHCurrNode->usClient    = pstMsg->usClient;
    g_pstPIHCurrNode->ucOpID      = pstMsg->ucOpID;
    g_pstPIHCurrNode->enCmdType   = pstMsg->ulMsgName;
    g_pstPIHCurrNode->ulEventType = pstMsg->ulEventType;

    /* �ȴ���ͬ����Ϣ */
    ulResult = SI_PIH_MsgSyncProc(pMsg);

    /* �ж���Ϣ�Ƿ��Ѿ������� */
    if (VOS_NULL_PTR != g_pstPIHCurrNode)
    {
        /* �ٴ����첽��Ϣ */
        ulResult = SI_PIH_MsgAsyncProc(pMsg);
    }

    if (VOS_NULL_PTR != g_pstPIHCurrNode)
    {
        if(USIMM_API_SUCCESS != ulResult)
        {
            PIH_WARNING1_LOG("SI_PIH_MsgProc:WARNING:EventType:",
                                            (VOS_INT32)pstMsg->ulEventType);

            SI_PIH_EventReportError(g_pstPIHCurrNode->usClient,
                                    g_pstPIHCurrNode->ucOpID,
                                    TAF_ERR_UNSPECIFIED_ERROR,
                                    pMsg->ulMsgName,
                                    pstMsg->ulEventType);

            /*lint -e534*/
            VOS_MemSet(g_pstPIHCurrNode, 0, sizeof(SI_PIH_CTRL_INFO_NODE_STRU));
            /*lint +e534*/

            /* ����ǰ�ڵ㱣���ڶ����� */
            SI_PIH_PutCtrlNode(SI_PIH_INFO_FREE_LIST_ID, g_pstPIHCurrNode);
        }
        else
        {
            /* ����ǰ�ڵ㱣���ڶ����� */
            SI_PIH_PutCtrlNode(SI_PIH_INFO_USED_LIST_ID, g_pstPIHCurrNode);
        }

        g_pstPIHCurrNode = VOS_NULL_PTR;
    }

    return ulResult;
}


VOS_VOID SI_PIH_CardUsimStatusInd(
    USIMM_CARDSTATUS_IND_STRU           *pstMsg)
{

    USIMM_CARDSTATUS_IND_STRU          *pstUsimMsg;
    VOS_UINT32                          ulRegPid;
    VOS_UINT32                          i;

    SI_PIH_MNTNDataHook(SI_PIH_USIMREG_PID_HOOK,
                        sizeof(g_aulPIHUsimBCPid),
                        (VOS_UINT8*)g_aulPIHUsimBCPid);

    /* ѭ�����͸�PID�ϱ���״̬ */
    for (i = 0; i < SI_PIH_BCPID_REG_MAX; i++)
    {
        if (VOS_NULL == g_aulPIHUsimBCPid[i])
        {
            continue;
        }

        ulRegPid = g_aulPIHUsimBCPid[i];

        pstUsimMsg = (USIMM_CARDSTATUS_IND_STRU *)VOS_AllocMsg(MAPS_PIH_PID,
                                                               sizeof(USIMM_CARDSTATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

        if (VOS_NULL_PTR == pstUsimMsg)
        {
            PIH_ERROR_LOG("SI_PIH_CardStatusInd: VOS_AllocMsg is Failed");

            return;
        }

        pstUsimMsg->ulReceiverPid               = ulRegPid;
        pstUsimMsg->ulMsgName                   = USIMM_CARDSTATUS_IND;    /* ������Ϣ���� */
        pstUsimMsg->enPhyCardType               = pstMsg->enPhyCardType;
        pstUsimMsg->stUsimSimInfo.enCardType    = pstMsg->stUsimSimInfo.enCardType;
        pstUsimMsg->stUsimSimInfo.enCardService = pstMsg->stUsimSimInfo.enCardService;
        pstUsimMsg->stCsimUimInfo.enCardType    = pstMsg->stCsimUimInfo.enCardType;
        pstUsimMsg->stCsimUimInfo.enCardService = pstMsg->stCsimUimInfo.enCardService;
        pstUsimMsg->stIsimInfo.enCardType       = pstMsg->stIsimInfo.enCardType;
        pstUsimMsg->stIsimInfo.enCardService    = pstMsg->stIsimInfo.enCardService;

        (VOS_VOID)VOS_SendMsg(pstUsimMsg->ulSenderPid, pstUsimMsg);
    }

    return;
}

/*****************************************************************************
�� �� ��  : SI_PIH_SendMsg2DSPSingle
��������  : PIH���͸�GDSP�Ĺ��ʽ�����Ϣ
�������  : ��
�������  : ��
�� �� ֵ  : VOS_OK
���ú���  :
��������  :
�޶���¼  :
1.��    ��  : 2010��07��26��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/
VOS_VOID SI_PIH_SendMsg2DSPSingle(
    SI_PIH_DSP_LIMIT_ENUM_UINT16        enLimit)
{
    SI_PIH_DSP_LIMIT_STRU   *pMsg;

    pMsg = (SI_PIH_DSP_LIMIT_STRU*)VOS_AllocMsg(WUEPS_PID_USIM,
                                        sizeof(SI_PIH_DSP_LIMIT_STRU)-VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR == pMsg)
    {
        PIH_ERROR_LOG("SI_PIH_SendMsg2DSP: VOS_AllocMsg is Failed");/*��ӡ����*/

        return; /*���غ���������Ϣ*/
    }

#if defined (INSTANCE_1)
    pMsg->ulReceiverPid = I1_DSP_PID_GPHY;
#elif defined (INSTANCE_2)
    pMsg->ulReceiverPid = I2_DSP_PID_GPHY;
#else
    pMsg->ulReceiverPid = I0_DSP_PID_GPHY;
#endif
    pMsg->ulLength      = 2*sizeof(VOS_UINT16);
    pMsg->usMsgName     = SI_PIH_DSP_POWER_LIMIT;
    pMsg->enLimit       = enLimit;

    (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pMsg);

    PIH_WARNING_LOG("SI_PIH_SendMsg2DSP: Send the Limit Power Msg");/*������ӡ�澯*/

    return;
}

/*****************************************************************************
�� �� ��  : SI_PIH_SendMsg2DSPAll
��������  : PIH���͸�GDSP�Ĺ��ʽ�����Ϣ
�������  : ��
�������  : ��
�� �� ֵ  : VOS_OK
���ú���  :
��������  :
�޶���¼  :
1.��    ��  : 2010��07��26��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/
VOS_VOID SI_PIH_SendMsg2DSPAll(
    SI_PIH_DSP_LIMIT_ENUM_UINT16        enLimit)
{
    SI_PIH_DSP_LIMIT_STRU   *pMsg;
    MODEM_ID_ENUM_UINT16    i;

    for (i = 0; i < MODEM_ID_BUTT; i++)
    {
        pMsg = (SI_PIH_DSP_LIMIT_STRU*)VOS_AllocMsg(WUEPS_PID_USIM,
                                        sizeof(SI_PIH_DSP_LIMIT_STRU)-VOS_MSG_HEAD_LENGTH);

        if (VOS_NULL_PTR == pMsg)
        {
            PIH_ERROR_LOG("SI_PIH_SendMsg2DSP: VOS_AllocMsg is Failed");/*��ӡ����*/

            return; /*���غ���������Ϣ*/
        }

        if (MODEM_ID_0 == i)
        {
            pMsg->ulReceiverPid = I0_DSP_PID_GPHY;
        }
#if  (FEATURE_MULTI_MODEM == FEATURE_ON)
        else    /*Ŀǰ��ֻ������GDSP*/
        {
            pMsg->ulReceiverPid = I1_DSP_PID_GPHY;
        }
#endif

        pMsg->ulLength      = 2*sizeof(VOS_UINT16);
        pMsg->usMsgName     = SI_PIH_DSP_POWER_LIMIT;
        pMsg->enLimit       = enLimit;

        (VOS_VOID)VOS_SendMsg(WUEPS_PID_USIM, pMsg);

        PIH_WARNING_LOG("SI_PIH_SendMsg2DSP: Send the Limit Power Msg");/*������ӡ�澯*/
    }

    return;
}

/*****************************************************************************
�� �� ��  : SI_PIH_SendMsg2DSP
��������  : PIH���͸�GDSP�Ĺ��ʽ�����Ϣ
�������  : ��
�������  : ��
�� �� ֵ  : VOS_OK
���ú���  :
��������  :
�޶���¼  :
1.��    ��  : 2010��07��26��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/
VOS_VOID SI_PIH_SendMsg2DSP(
    SI_PIH_DSP_LIMIT_ENUM_UINT16        enLimit)
{
    if (VOS_TRUE != USIMM_IsSvlte())
    {
        SI_PIH_SendMsg2DSPSingle(enLimit);
    }
    else             /*SVLTE NV ��Multi Modem�򿪵�ʱ�������*/
    {
        SI_PIH_SendMsg2DSPAll(enLimit);
    }

    return;
}
VOS_UINT32 SI_PIH_ProtectReset(SI_VOID)
{
    /* �Ѿ��������Ͳ�Ҫ������SIM�� */
#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)
    if (VOS_FALSE == USIMM_CCB_IsCardExist())
    {
        PIH_WARNING_LOG("SI_PIH_ProtectReset: SIM already removed, no need Protect Reset.");

        return SI_PIH_NO_NEED_REPORT;
    }
#else
    USIMM_CARD_SERVIC_ENUM_UINT32       ulCardStatus = USIMM_CARD_SERVIC_ABSENT;

    /*lint -e534*/
    USIMM_GetCardType(g_stPihCardInfo.enGUTLCardType, &ulCardStatus);
    /*lint +e534*/

    /* �Ѿ��������Ͳ�Ҫ������SIM�� */
    if (USIMM_CARD_SERVIC_ABSENT == ulCardStatus)
    {
        PIH_WARNING_LOG("SI_PIH_ProtectReset: SIM already removed, no need Protect Reset.");

        return SI_PIH_NO_NEED_REPORT;
    }
#endif  /*(FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)*/

    PIH_WARNING_LOG("SI_PIH_ProtectReset: Start the Protect Reset.");

    (VOS_VOID)SI_PIH_POLL_32K_TIMER_STOP(&g_stPIHPollTime[SI_PIH_TIMER_NAME_CHECKSTATUS].stTimer);/*ֹͣ���ܿ����Ķ�ʱ��*/

    (VOS_VOID)VOS_StopRelTimer(&g_stPIHPollTime[SI_PIH_TIMER_NAME_CHECKIMSI].stTimer);

    (VOS_VOID)VOS_StopRelTimer(&g_stPIHPollTime[SI_PIH_TIMER_NAME_CALL].stTimer);

    if(g_stPIHProtectCtrl.enProtectFun == SI_PIH_PROTECT_DISABLE)  /*��ǰ���ܹر�*/
    {
        g_stPIHProtectCtrl.enProtectState = SI_PIH_PROTECT_OFF;     /*�������������ٽ��б�����λ��*/

        PIH_WARNING_LOG("SI_PIH_ProtectReset: No Need the Protect Reset.");

        return SI_PIH_NEED_REPORT;                                  /*��ǰ��Ҫ�ϱ���״̬*/
    }

    g_stPIHProtectCtrl.enProtectState = SI_PIH_PROTECT_RUNING;      /*���ĵ�ǰ�����Ը�λ��״̬*/

    PIH_WARNING_LOG("SI_PIH_ProtectReset: Need Send the Prower Limit Msg.");

    SI_PIH_SendMsg2DSP(SI_PIH_DSP_POWER_LIMIT_ON);


    /* �·���λ���� */
    if (VOS_OK != SI_PIH_SendProtectResetReqMsg())
    {
        PIH_WARNING_LOG("SI_PIH_ProtectReset: SI_PIH_SendProtectResetReqMsg return Error.");

        return SI_PIH_NEED_REPORT;
    }

    PIH_WARNING_LOG("SI_PIH_ProtectReset: End the Protect Reset.");

    return SI_PIH_NO_NEED_REPORT;
}
VOS_VOID SI_PIH_CardStateIndProc(
    USIMM_CARDSTATUS_IND_STRU           *pstMsg)
{
    /* GUTL/CDMA/IMS��һ���з����������ʱ��,GUTL��״̬��������ROM SIM */
    if ((USIMM_CARD_SERVIC_AVAILABLE == pstMsg->stUsimSimInfo.enCardService)
     && (USIMM_CARD_ROM_SIM          != pstMsg->stUsimSimInfo.enCardType))
    {
        PIH_NORMAL_LOG("SI_PIH_CardStateIndProc: The GUTL State is USIMM_CARD_SERVIC_AVAILABLE");

        if (VOS_FALSE == USIMM_VsimIsActive())    /*vSIM���ܹر�*/
        {
            g_stPIHProtectCtrl.enProtectFun = SI_PIH_PROTECT_ENABLE;    /*�����Ը�λ�����ܿ���*/

            g_stPIHProtectCtrl.enProtectState = SI_PIH_PROTECT_ON;      /*������ر�������*/

            SI_PIH_PollTimerPro(&g_stPIHPollTime[SI_PIH_TIMER_NAME_CHECKSTATUS]);/*������ѯ��״̬��ʱ��*/

            SI_PIH_PollTimerPro(&g_stPIHPollTime[SI_PIH_TIMER_NAME_CHECKIMSI]); /*������ѯIMSI��ʱ��*/

            SI_PIH_PollTimerPro(&g_stPIHPollTime[SI_PIH_TIMER_NAME_CALL]);
        }
    }
    else if (USIMM_CARD_SERVIC_AVAILABLE == pstMsg->stCsimUimInfo.enCardService)
    {
        PIH_NORMAL_LOG("SI_PIH_CardStateIndProc: The CDMA State is USIMM_CARD_SERVIC_AVAILABLE");

        if (VOS_FALSE == USIMM_VsimIsActive())    /*vSIM���ܹر�*/
        {
            g_stPIHProtectCtrl.enProtectFun = SI_PIH_PROTECT_ENABLE;    /*�����Ը�λ�����ܿ���*/

            g_stPIHProtectCtrl.enProtectState = SI_PIH_PROTECT_ON;      /*������ر�������*/

            SI_PIH_PollTimerPro(&g_stPIHPollTime[SI_PIH_TIMER_NAME_CHECKSTATUS]);/*������ѯ��״̬��ʱ��*/

            SI_PIH_PollTimerPro(&g_stPIHPollTime[SI_PIH_TIMER_NAME_CALL]);
        }
    }
    else                                                                /*������״̬*/
    {
        /*lint -e534*/
        (VOS_VOID)VOS_StopRelTimer(&g_stPIHPollTime[SI_PIH_TIMER_NAME_CHECKIMSI].stTimer);
        (VOS_VOID)VOS_StopRelTimer(&g_stPIHPollTime[SI_PIH_TIMER_NAME_CALL].stTimer);
        /*lint +e534*/

        if(pstMsg->stUsimSimInfo.enCardService == USIMM_CARD_SERVIC_ABSENT)     /*��״̬�޿�*/
        {
            g_stPIHProtectCtrl.enProtectFun = SI_PIH_PROTECT_DISABLE;

            /*ֹͣ���ܿ����Ķ�ʱ��*/
            /*lint -e534*/
            (VOS_VOID)SI_PIH_POLL_32K_TIMER_STOP(&g_stPIHPollTime[SI_PIH_TIMER_NAME_CHECKSTATUS].stTimer);
            /*lint +e534*/
        }
        else
        {
            /*������ѯ��״̬��ʱ��*/
            SI_PIH_PollTimerPro(&g_stPIHPollTime[SI_PIH_TIMER_NAME_CHECKSTATUS]);
        }

        PIH_NORMAL_LOG("SI_PIH_CardStateIndProc: The Card State is Other");
    }

    SI_PIH_CardUsimStatusInd(pstMsg);

    /* �޿�����Ҫ���ͨ��״̬��Ϣ */
    if (USIMM_PHYCARD_TYPE_NOCARD == pstMsg->enPhyCardType)
    {
        SI_PIH_ClearChannelInfo();
    }
#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)
    else
    {
        if (USIMM_CARD_SERVIC_AVAILABLE == pstMsg->stUsimSimInfo.enCardService)
        {
            SI_PIH_SetAppSession(USIMM_GUTL_APP);
        }

        if (USIMM_CARD_SERVIC_AVAILABLE == pstMsg->stCsimUimInfo.enCardService)
        {
            SI_PIH_SetAppSession(USIMM_CDMA_APP);
        }

        if (USIMM_CARD_SERVIC_AVAILABLE == pstMsg->stIsimInfo.enCardService)
        {
            SI_PIH_SetAppSession(USIMM_IMS_APP);
        }
    }
#endif

    g_stPihCardInfo.enPhyCardType   = pstMsg->enPhyCardType;
    g_stPihCardInfo.enGUTLCardType  = pstMsg->stUsimSimInfo.enCardType;
    g_stPihCardInfo.enGUTLSvcStatus = pstMsg->stUsimSimInfo.enCardService;
    g_stPihCardInfo.enCDMACardType  = pstMsg->stCsimUimInfo.enCardType;
    g_stPihCardInfo.enCDMASvcStatus = pstMsg->stCsimUimInfo.enCardService;

    return;
}
VOS_VOID SI_PIH_RAccessCnfFromAT(
    USIMM_RACCESS_CNF_STRU              *pstRAccessCnf)
{
    SI_PIH_EVENT_INFO_STRU              stEvent;

    /*lint -e534*/
    VOS_MemSet(&stEvent, 0, sizeof(stEvent));
    /*lint +e534*/

    /* ����δ�ɹ� */
    stEvent.PIHError                    =   pstRAccessCnf->stCmdResult.ulResult;
    stEvent.PIHEvent.RAccessCnf.ucSW1   =   pstRAccessCnf->ucSW1;
    stEvent.PIHEvent.RAccessCnf.ucSW2   =   pstRAccessCnf->ucSW2;
    stEvent.PIHEvent.RAccessCnf.usLen   =   pstRAccessCnf->usLen;

    (VOS_VOID)VOS_MemCpy(stEvent.PIHEvent.RAccessCnf.aucContent,
                           pstRAccessCnf->aucContent,
                           sizeof(stEvent.PIHEvent.RAccessCnf.aucContent));

    (VOS_VOID)SI_PIH_EventCallBack(&stEvent);

    return;
}
VOS_UINT32 SI_PIH_ImsiPollingCnfProc(
    USIMM_RACCESS_CNF_STRU              *pstRAccessCnf)
{
    VOS_UINT32                          ulResult;
    USIMM_CARD_SERVIC_ENUM_UINT32       ulCardStatus;
    VOS_UINT8                           aucImsi[USIMM_EF_IMSI_LEN];

    /* ������AT���������Ҫ����AT�������������� */
    if (VOS_NULL != pstRAccessCnf->stCmdResult.ulSendPara)
    {
        return VOS_ERR;
    }

    ulCardStatus = USIMM_CARD_SERVIC_AVAILABLE;

    /* ��ȡ����ǰ״̬ */
    /*lint -e534*/
    USIMM_GetCardType(g_stPihCardInfo.enGUTLCardType, &ulCardStatus);
    /*lint +e534*/

    if (USIMM_CARD_SERVIC_AVAILABLE != ulCardStatus)
    {
        PIH_WARNING_LOG("SI_PIH_GAccessProc: Card Status Wrong");

        return VOS_OK;
    }

    ulResult = pstRAccessCnf->stCmdResult.ulErrorCode;

    if(USIMM_SW_OK == pstRAccessCnf->stCmdResult.ulErrorCode)
    {
        /* ���ڴ��л�ȡ��ǰIMSI */
        if(USIMM_API_SUCCESS != USIMM_GetCardIMSI(aucImsi))
        {
            PIH_WARNING_LOG("SI_PIH_GAccessProc: read IMSI error");

            return VOS_OK;
        }

        /* �ڴ���IMSI�ź�USIM����IMSI�����ݲ�ƥ��*/
        if(VOS_OK != VOS_MemCmp(aucImsi, pstRAccessCnf->aucContent, sizeof(aucImsi)))
        {
            PIH_WARNING_LOG("SI_PIH_GAccessProc: The IMSI is Not Same");

            ulResult = USIMM_SW_SENDCMD_ERROR;
        }
    }

    /* ��ȡʧ�� */
    if(  (USIMM_SW_OK != ulResult)
        &&(USIMM_SW_SECURITY_ERROR != ulResult))
    {
        PIH_WARNING_LOG("SI_PIH_GAccessProc: The Msg is Error, Need Protect Reset");

        if(g_stPIHProtectCtrl.enProtectState == SI_PIH_PROTECT_RUNING)
        {
            PIH_WARNING_LOG("SI_PIH_GAccessProc: The Protect is Running, No Need Protect Reset");

            return VOS_OK;
        }

        /*���ִ�����Ҫ��������*/
        ulResult = SI_PIH_ProtectReset();

        if(SI_PIH_NEED_REPORT == ulResult)
        {
            PIH_WARNING_LOG("SI_PIH_GAccessProc: Need Deactive Card");

            /*lint -e534*/
            SI_PIH_SendDeactiveReqMsg(0);
            /*lint +e534*/
        }
    }
    else
    {
        /* ����Timer */
        SI_PIH_PollTimerPro(&g_stPIHPollTime[SI_PIH_TIMER_NAME_CHECKIMSI]);
    }

    return VOS_OK;
}
VOS_VOID SI_PIH_ProtectResetCnfProc(
    USIMM_SINGLECMD_CNF_STRU            *pstMsg)
{
    USIMM_CARD_SERVIC_ENUM_UINT32       ulCardStatus = USIMM_CARD_SERVIC_BUTT;

    /* ֪ͨDSP�ָ����书�� */
    SI_PIH_SendMsg2DSP(SI_PIH_DSP_POWER_LIMIT_OFF);

    if (VOS_OK != pstMsg->stCmdResult.ulResult)    /*��ѯ״̬OK�� ������ʱ��*/
    {
        PIH_WARNING_LOG("SI_PIH_StatusProc: The Msg is Other Error");

        g_stPIHProtectCtrl.enProtectFun = SI_PIH_PROTECT_DISABLE;   /*���ù��ܹرգ����ϱ���״̬��ʱ��������*/

        return;
    }

    /* �����Ը�λ�ɹ������ȫ�ֱ���״̬ */
    g_stPIHProtectCtrl.enProtectState = SI_PIH_PROTECT_ON;

    /*lint -e534*/
    USIMM_GetCardType(g_stPihCardInfo.enGUTLCardType, &ulCardStatus);
    /*lint +e534*/

    if (USIMM_CARD_SERVIC_AVAILABLE == ulCardStatus)
    {
        SI_PIH_PollTimerPro(&g_stPIHPollTime[SI_PIH_TIMER_NAME_CHECKSTATUS]);/*������ѯ��״̬��ʱ��*/

        SI_PIH_PollTimerPro(&g_stPIHPollTime[SI_PIH_TIMER_NAME_CHECKIMSI]); /*������ѯIMSI��ʱ��*/

        SI_PIH_PollTimerPro(&g_stPIHPollTime[SI_PIH_TIMER_NAME_CALL]);
    }

#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)
    /*lint -e534*/
    USIMM_GetCardType(g_stPihCardInfo.enCDMACardType, &ulCardStatus);
    /*lint +e534*/

    if (USIMM_CARD_SERVIC_AVAILABLE == ulCardStatus)
    {
        SI_PIH_PollTimerPro(&g_stPIHPollTime[SI_PIH_TIMER_NAME_CHECKSTATUS]);/*������ѯ��״̬��ʱ��*/

        SI_PIH_PollTimerPro(&g_stPIHPollTime[SI_PIH_TIMER_NAME_CALL]);
    }
#endif

    return;
}

/*****************************************************************************
�� �� ��  : SI_PIH_StatusProc
��������  : ��ѯ��״̬��Ϣ�Ϳ���λ����ظ��ϱ�
�������  : pstStatusCnf: ��Ϣ����
�������  : ��
�� �� ֵ  :
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2010��07��26��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/
VOS_VOID SI_PIH_StatusCnfProc(
    USIMM_SINGLECMD_CNF_STRU            *pstMsg)
{
    VOS_UINT32 ulResult;

    if (pstMsg->stCmdResult.ulResult == VOS_OK)    /*��ѯ״̬OK�� ������ʱ��*/
    {
        PIH_NORMAL_LOG("SI_PIH_StatusProc: The Msg is OK");

        SI_PIH_PollTimerPro(&g_stPIHPollTime[SI_PIH_TIMER_NAME_CHECKSTATUS]);   /*������ʱ��������һ���ڹ���*/

        SI_PIH_PollTimerPro(&g_stPIHPollTime[SI_PIH_TIMER_NAME_CALL]);
    }
    else if (pstMsg->stCmdResult.ulResult == USIMM_SW_OTHER_ERROR)     /*��ǰ�����������󣬲��ٽ�����������*/
    {
        PIH_WARNING_LOG("SI_PIH_StatusProc: The Msg is Other Error");

        g_stPIHProtectCtrl.enProtectFun = SI_PIH_PROTECT_DISABLE;   /*���ù��ܹرգ����ϱ���״̬��ʱ��������*/

        /*lint -e534*/
        SI_PIH_SendDeactiveReqMsg(0);              /*ȥ���ǰ�Ŀ�*/
        /*lint +e534*/
    }
    else
    {
        PIH_WARNING_LOG("SI_PIH_StatusProc: The Msg is Error, Need Protect Reset");

        if(g_stPIHProtectCtrl.enProtectState == SI_PIH_PROTECT_RUNING)
        {
            PIH_WARNING_LOG("SI_PIH_StatusProc: The Protect is Running, No Need Protect Reset");

            return;
        }

        ulResult = SI_PIH_ProtectReset();              /*���ִ�����Ҫ��������*/

        if(ulResult == SI_PIH_NEED_REPORT)
        {
            PIH_WARNING_LOG("SI_PIH_StatusProc: Need Deactive Card");

            /*lint -e534*/
            SI_PIH_SendDeactiveReqMsg(0);
            /*lint +e534*/
        }
    }

    return;
}

/*****************************************************************************
�� �� ��  : SI_PIH_GAccessCnfProc
��������  :
�������  : pstMsg
�������  : ��
�� �� ֵ  : VOS_UINT32 ����ִ�н��
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2010��08��20��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/
VOS_VOID SI_PIH_PCSCCnfProc(
    USIMM_SENDTPDUDATA_CNF_STRU         *pstMsg)
{
    VOS_UINT8               aucContent[260];
    VOS_UINT32              ulDataLen;

    if(pstMsg->stCmdResult.ulResult == USIMM_SW_ERR)
    {
        SI_PIH_PCSCDataCnf(g_pstPIHCurrNode->ulEventType,
                            pstMsg->stCmdResult.ulResult,
                            0,
                            VOS_NULL_PTR);

        return;
    }

    (VOS_VOID)VOS_MemCpy(&g_stPIHCSIMCtrlInfo.stFilePath,
                         &pstMsg->stFilePath,
                         sizeof(USIMM_FILEPATH_INFO_STRU));

    if((pstMsg->stRspData.aucInputCmd[INS] == 0xA4)
        ||(pstMsg->stRspData.aucInputCmd[INS] == 0x88)
        ||(pstMsg->stRspData.aucInputCmd[INS] == 0x32)
        ||(pstMsg->stRspData.aucInputCmd[INS] == 0xA2))
    {
        g_stPIHCSIMCtrlInfo.usRspLen = (VOS_UINT16)pstMsg->stRspData.ulDataLen;

        ulDataLen = 2;

        if (pstMsg->stRspData.ulDataLen != 0)
        {
            /*lint -e534*/
            VOS_MemCpy(g_stPIHCSIMCtrlInfo.aucRspCotent,
                        pstMsg->stRspData.aucRspData,
                        pstMsg->stRspData.ulDataLen);
            /*lint +e534*/

            aucContent[1] = (VOS_UINT8)pstMsg->stRspData.ulDataLen;

            if (USIMM_PHYCARD_TYPE_ICC == g_stPihCardInfo.enPhyCardType)
            {
                aucContent[0] = 0x9F;
            }
            else
            {
                aucContent[0] = 0x61;
            }
        }
        else
        {
            aucContent[0] = pstMsg->stRspData.ucSW1;
            aucContent[1] = pstMsg->stRspData.ucSW2;
        }
    }
    else
    {
        g_stPIHCSIMCtrlInfo.usRspLen = 0;

        ulDataLen = pstMsg->stRspData.ulDataLen;

        /*lint -e534*/
        VOS_MemCpy(aucContent, pstMsg->stRspData.aucRspData, pstMsg->stRspData.ulDataLen);
        /*lint +e534*/

        aucContent[ulDataLen]   = pstMsg->stRspData.ucSW1;
        aucContent[ulDataLen+1] = pstMsg->stRspData.ucSW2;

        ulDataLen += 2;
    }

    SI_PIH_PCSCDataCnf(g_pstPIHCurrNode->ulEventType,
                        pstMsg->stCmdResult.ulResult,
                        ulDataLen,
                        aucContent);

    return;
}

/*****************************************************************************
�� �� ��  : SI_PIH_GAccessCnfProc
��������  :
�������  : pstMsg
�������  : ��
�� �� ֵ  : VOS_UINT32 ����ִ�н��
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2010��08��20��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/
VOS_VOID SI_PIH_GAccessCnfProc(
    USIMM_SENDTPDUDATA_CNF_STRU         *pstMsg)
{
    SI_PIH_EVENT_INFO_STRU              stEvent;

    (VOS_VOID)VOS_MemSet(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));

    if(USIMM_SW_ERR == pstMsg->stCmdResult.ulResult)
    {
        stEvent.PIHError = TAF_ERR_PARA_ERROR;

        /*lint -e534*/
        (VOS_VOID)SI_PIH_EventCallBack(&stEvent);
        /*lint +e534*/

        return;
    }

    stEvent.PIHError    = VOS_OK;       /*��֤���Դ�ӡ���*/

    (VOS_VOID)VOS_MemCpy(&g_stPIHCSIMCtrlInfo.stFilePath,
                         &pstMsg->stFilePath,
                         sizeof(USIMM_FILEPATH_INFO_STRU));

    if((pstMsg->stRspData.aucInputCmd[INS] == 0xA4)
        ||(pstMsg->stRspData.aucInputCmd[INS] == 0x88)
        ||(pstMsg->stRspData.aucInputCmd[INS] == 0x32)
        ||(pstMsg->stRspData.aucInputCmd[INS] == 0xA2))
    {
        g_stPIHCSIMCtrlInfo.usRspLen = (VOS_UINT16)pstMsg->stRspData.ulDataLen;

        stEvent.PIHEvent.GAccessCnf.Len = 0;

        if(pstMsg->stRspData.ulDataLen != 0)
        {
            /*lint -e534*/
            VOS_MemCpy(g_stPIHCSIMCtrlInfo.aucRspCotent,
                        pstMsg->stRspData.aucRspData,
                        pstMsg->stRspData.ulDataLen);
            /*lint +e534*/

            stEvent.PIHEvent.GAccessCnf.SW2 = (VOS_UINT8)pstMsg->stRspData.ulDataLen;

            if (USIMM_PHYCARD_TYPE_ICC == g_stPihCardInfo.enPhyCardType)
            {
                stEvent.PIHEvent.GAccessCnf.SW1 = 0x9F;
            }
            else
            {
                stEvent.PIHEvent.GAccessCnf.SW1 = 0x61;
            }
        }
        else
        {
            stEvent.PIHEvent.GAccessCnf.SW1 = pstMsg->stRspData.ucSW1;
            stEvent.PIHEvent.GAccessCnf.SW2 = pstMsg->stRspData.ucSW2;
        }
    }
    else
    {
        g_stPIHCSIMCtrlInfo.usRspLen = 0;

        stEvent.PIHEvent.GAccessCnf.SW1 = pstMsg->stRspData.ucSW1;
        stEvent.PIHEvent.GAccessCnf.SW2 = pstMsg->stRspData.ucSW2;
        stEvent.PIHEvent.GAccessCnf.Len = (VOS_UINT16)pstMsg->stRspData.ulDataLen;

        /*lint -e534*/
        VOS_MemCpy(stEvent.PIHEvent.GAccessCnf.Command,
                        pstMsg->stRspData.aucRspData,
                        pstMsg->stRspData.ulDataLen);
        /*lint +e534*/
    }

    /*lint -e534*/
    (VOS_VOID)SI_PIH_EventCallBack(&stEvent);
    /*lint +e534*/

    return;
}
VOS_VOID SI_PIH_IsdbAccessCnfProc(
    USIMM_SENDTPDUDATA_CNF_STRU         *pstMsg)
{
    SI_PIH_EVENT_INFO_STRU              stEvent;

    (VOS_VOID)VOS_MemSet(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));

    /* APDU��ʽ���Ϸ� */
    if (USIMM_SW_ERR == pstMsg->stCmdResult.ulResult)
    {
        stEvent.PIHError = TAF_ERR_PARA_ERROR;
    }
    else
    {
        stEvent.PIHError                        =   TAF_ERR_NO_ERROR;
        stEvent.PIHEvent.IsdbAccessCnf.ucSW1    =   pstMsg->stRspData.ucSW1;
        stEvent.PIHEvent.IsdbAccessCnf.ucSW2    =   pstMsg->stRspData.ucSW2;
        stEvent.PIHEvent.IsdbAccessCnf.usLen    =   (VOS_UINT16)pstMsg->stRspData.ulDataLen;

        (VOS_VOID)VOS_MemCpy(stEvent.PIHEvent.IsdbAccessCnf.aucCommand,
                    pstMsg->stRspData.aucRspData,
                    pstMsg->stRspData.ulDataLen);
    }

    /*lint -e534*/
    (VOS_VOID)SI_PIH_EventCallBack(&stEvent);
    /*lint +e534*/

    return;
}
VOS_VOID SI_PIH_OpenChannelCnfProc(
    USIMM_OPENCHANNEL_CNF_STRU          *pstMsg)
{
    SI_PIH_EVENT_INFO_STRU              stEvent;

    (VOS_VOID)VOS_MemSet(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));

    /* ����δ�ɹ� */
    stEvent.PIHError                        =   pstMsg->stCmdResult.ulResult;
    stEvent.PIHEvent.ulSessionID            =   pstMsg->ulSessionID;

    /*lint -e534*/
    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)
        SI_PIH_SetAppSession(pstMsg->stCmdResult.enApptype);

        SI_PIH_GetAppSession(pstMsg->stCmdResult.enApptype,
                            &stEvent.PIHEvent.ulSessionID);
#else
        SI_PIH_SaveChannelInfo(pstMsg->ucChannelID,
                                pstMsg->ulSessionID,
                                pstMsg->stCmdResult.enApptype);
#endif
    }

    (VOS_VOID)SI_PIH_EventCallBack(&stEvent);
    /*lint +e534*/

    return;
}
VOS_VOID SI_PIH_CloseChannelCnfProc(
    USIMM_CLOSECHANNEL_CNF_STRU         *pstMsg)
{
    SI_PIH_EVENT_INFO_STRU              stEvent;

    (VOS_VOID)VOS_MemSet(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));

    stEvent.PIHError = pstMsg->stCmdResult.ulResult;

    /*lint -e534*/
    (VOS_VOID)SI_PIH_EventCallBack(&stEvent);
    /*lint +e534*/

    return;
}


VOS_VOID SI_PIH_AccessChannelCnfProc(
    USIMM_SENDTPDUDATA_CNF_STRU         *pstMsg)
{
    SI_PIH_EVENT_INFO_STRU              stEvent;

    (VOS_VOID)VOS_MemSet(&stEvent, 0, sizeof(SI_PIH_EVENT_INFO_STRU));

    /* APDU��ʽ���Ϸ� */
    if (VOS_OK != pstMsg->stCmdResult.ulResult)
    {
        stEvent.PIHError = TAF_ERR_ERROR;
    }
    else
    {
        stEvent.PIHError                       =  TAF_ERR_NO_ERROR;
        stEvent.PIHEvent.stCglaCmdCnf.ucSW1    =  pstMsg->stRspData.ucSW1;
        stEvent.PIHEvent.stCglaCmdCnf.ucSW2    =  pstMsg->stRspData.ucSW2;
        stEvent.PIHEvent.stCglaCmdCnf.usLen    =  (VOS_UINT16)pstMsg->stRspData.ulDataLen;

        /*lint -e534*/
        (VOS_VOID)VOS_MemCpy(stEvent.PIHEvent.stCglaCmdCnf.aucCommand,
                   pstMsg->stRspData.aucRspData,
                   pstMsg->stRspData.ulDataLen);
        /*lint +e534*/
    }

    /*lint -e534*/
    (VOS_VOID)SI_PIH_EventCallBack(&stEvent);
    /*lint +e534*/

    return;
}
VOS_VOID SI_PIH_RefreshIndProc(
    USIMM_STKREFRESH_IND_STRU           *pstMsg)
{
    USIMM_STKREFRESH_IND_STRU           *pstUsimMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRegPid;
    VOS_UINT32                          i;

    PIH_NORMAL_LOG("SI_PIH_RefreshIndProc: Need Report Refresh.");

    SI_PIH_MNTNDataHook(SI_PIH_REFRESHREG_PID_HOOK, sizeof(g_aulPIHRefreshBCPid), (VOS_UINT8*)g_aulPIHRefreshBCPid);

    /* ѭ�����͸�PID�ϱ���״̬ */
    for (i = 0; i < SI_PIH_BCPID_REG_MAX; i++)
    {
        if (VOS_NULL == g_aulPIHRefreshBCPid[i])
        {
            continue;
        }

        ulRegPid = g_aulPIHRefreshBCPid[i];

        pstUsimMsg = (USIMM_STKREFRESH_IND_STRU *)VOS_AllocMsg(MAPS_PIH_PID, pstMsg->stIndHdr.ulLength);

        if (VOS_NULL_PTR == pstUsimMsg)
        {
            PIH_ERROR_LOG("SI_PIH_RefreshIndProc: VOS_AllocMsg is Failed");

            return;
        }

        /*lint -e534*/
        (VOS_VOID)VOS_MemCpy((VOS_UINT8*)pstUsimMsg + VOS_MSG_HEAD_LENGTH,
                   (VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                   pstMsg->stIndHdr.ulLength);
        /*lint +e534*/

        pstUsimMsg->stIndHdr.ulReceiverPid  = ulRegPid;

        (VOS_VOID)VOS_SendMsg(MAPS_PIH_PID, pstUsimMsg);
    }

    return;
}

/*****************************************************************************
�� �� ��  : SI_PIH_CardTimeOutProc
��������  : Card Time Out IND��Ϣ������
�������  : ��
�������  : ��
�� �� ֵ  : ��
History     :
1.��    ��  : 2015��07��28��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/

VOS_VOID SI_PIH_CardTimeOutProc(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)
    if (SI_PIH_PROTECT_RUNING == g_stPIHProtectCtrl.enProtectState)
    {
        PIH_WARNING_LOG("SI_PIH_CardTimeOutProc: Protect Reset is ON.");
        return;
    }

    if (SI_PIH_NO_NEED_REPORT != SI_PIH_ProtectReset())
    {
        PIH_WARNING_LOG("SI_PIH_CardTimeOutProc: no need Protect Reset.");
    }
#endif

    return;
}


VOS_UINT32 SI_PIH_UsimIndMsgProc(
    PS_SI_MSG_STRU                      *pstMsg)
{
    switch(pstMsg->ulMsgName)
    {
        case USIMM_CARDSTATUS_IND:
            SI_PIH_CardStateIndProc((USIMM_CARDSTATUS_IND_STRU *)pstMsg);
            return VOS_OK;

        case USIMM_STATUSCMD_CNF:
            SI_PIH_StatusCnfProc((USIMM_SINGLECMD_CNF_STRU*)pstMsg);
            return VOS_OK;

        case USIMM_PROTECTRESET_CNF:
            SI_PIH_ProtectResetCnfProc((USIMM_SINGLECMD_CNF_STRU*)pstMsg);
            return VOS_OK;

        case USIMM_STKREFRESH_IND:
            SI_PIH_RefreshIndProc((USIMM_STKREFRESH_IND_STRU *)pstMsg);
            return VOS_OK;

        case USIMM_RACCESS_CNF:
            return SI_PIH_ImsiPollingCnfProc((USIMM_RACCESS_CNF_STRU*)pstMsg);

#if (FEATURE_VSIM == FEATURE_ON)
        case USIMM_VSIM_RDH_IND:
            SI_PIH_ReDhNegotiateIndProc();
            return VOS_OK;
#endif

        case USIMM_CARDTIMEOUT_IND:
            SI_PIH_CardTimeOutProc();
            return VOS_OK;

        default:
            break;
    };

    return VOS_ERR;
}


VOS_UINT32 SI_PIH_UsimCnfMsgProc(
    PS_SI_MSG_STRU                      *pMsg)
{
    USIMM_FDNPROCESS_CNF_STRU          *pstFDNCnf;
    USIMM_SENDTPDUDATA_CNF_STRU        *pstSendTpduCnf;
    USIMM_CMDHEADER_CNF_STRU           *pstHeaderCnf;
    VOS_UINT32                          ulResult = VOS_OK;
    VOS_UINT32                          ulRet = VOS_OK;

    g_pstPIHCurrNode = SI_PIH_GetCtrlNode(SI_PIH_INFO_USED_LIST_ID);

    if (VOS_NULL_PTR == g_pstPIHCurrNode)
    {
        PIH_ERROR_LOG("SI_PIH_UsimCnfMsgProc:g_pstPIHCurrNode is VOS_NULL_PTR.");

        return VOS_ERR;
    }

    pstHeaderCnf = (USIMM_CMDHEADER_CNF_STRU*)pMsg;

    /* �ж���Ϣ�Ƿ���ȷ */
    if (pstHeaderCnf->ulSendPara != SI_PIH_SEND_PAPA(g_pstPIHCurrNode->usClient, g_pstPIHCurrNode->ulEventType))
    {
        PIH_ERROR1_LOG("SI_PIH_UsimCnfMsgProc:ulSendPara is incorrect.", (VOS_INT32)pstHeaderCnf->ulSendPara);
        PIH_ERROR1_LOG("SI_PIH_UsimCnfMsgProc:usClient is incorrect.",   (VOS_INT32)g_pstPIHCurrNode->usClient);
        PIH_ERROR1_LOG("SI_PIH_UsimCnfMsgProc:ulEventType is incorrect.",(VOS_INT32)g_pstPIHCurrNode->ulEventType);

        return VOS_ERR;
    }

    switch(pMsg->ulMsgName)
    {
        case USIMM_FBDNPROCESS_CNF:

            pstFDNCnf = (USIMM_FDNPROCESS_CNF_STRU *)pMsg;

            if(VOS_OK == pstFDNCnf->stCmdResult.ulResult)
            {
                PIH_NORMAL_LOG("SI_PIH_UsimCnfMsgProc:NORMAL: FDN CNF OK.");
                ulRet = SI_PIH_FdnBdnStateReport(pstFDNCnf->enFDNState, TAF_ERR_NO_ERROR, g_pstPIHCurrNode->enCmdType);
            }
            else if (USIMM_SIM_PUK2_REQUIRED == pstFDNCnf->stCmdResult.ulResult)
            {
                PIH_WARNING_LOG("SI_PIH_UsimCnfMsgProc:NORMAL: FDN CNF PUK2 REQUIRED.");
                ulRet = SI_PIH_FdnBdnStateReport(pstFDNCnf->enFDNState, TAF_ERR_NEED_PUK2, g_pstPIHCurrNode->enCmdType);
            }
            else if (USIMM_INCORRECT_PASSWORD == pstFDNCnf->stCmdResult.ulResult)
            {
                PIH_WARNING_LOG("SI_PIH_UsimCnfMsgProc:NORMAL: FDN CNF INCORRECT PASSWORD.");
                ulRet = SI_PIH_FdnBdnStateReport(pstFDNCnf->enFDNState, TAF_ERR_SIM_INCORRECT_PASSWORD, g_pstPIHCurrNode->enCmdType);
            }
            else
            {
                PIH_WARNING_LOG("SI_PIH_UsimCnfMsgProc:NORMAL: FDN CNF ERROR.");
                ulRet = SI_PIH_FdnBdnStateReport(pstFDNCnf->enFDNState, TAF_ERR_SIM_FAIL, g_pstPIHCurrNode->enCmdType);
            }

            if (VOS_OK != ulRet)
            {
                PIH_INFO_LOG("SI_PIH_UsimCnfMsgProc:Fdn Report fail");
            }

            break;

        case USIMM_OPENCHANNEL_CNF:
            SI_PIH_OpenChannelCnfProc((USIMM_OPENCHANNEL_CNF_STRU *)pMsg);
            break;

        case USIMM_CLOSECHANNEL_CNF:
            SI_PIH_CloseChannelCnfProc((USIMM_CLOSECHANNEL_CNF_STRU *)pMsg);
            break;

        case USIMM_SENDTPDUDATA_CNF:
            pstSendTpduCnf = (USIMM_SENDTPDUDATA_CNF_STRU *)pMsg;

            if (SI_PIH_EVENT_GENERIC_ACCESS_CNF == SI_PIH_EVENT_TYPE(pstSendTpduCnf->stCmdResult.ulSendPara))
            {
                if(SI_PIH_PCSC_DATA_REQ == g_pstPIHCurrNode->enCmdType)
                {
                    SI_PIH_PCSCCnfProc(pstSendTpduCnf);
                }
                else
                {
                    SI_PIH_GAccessCnfProc(pstSendTpduCnf);
                }
            }
            else if (SI_PIH_EVENT_ISDB_ACCESS_CNF == SI_PIH_EVENT_TYPE(pstSendTpduCnf->stCmdResult.ulSendPara))
            {
                SI_PIH_IsdbAccessCnfProc(pstSendTpduCnf);
            }
            else if (SI_PIH_EVENT_CGLA_SET_CNF == SI_PIH_EVENT_TYPE(pstSendTpduCnf->stCmdResult.ulSendPara))
            {
                SI_PIH_AccessChannelCnfProc(pstSendTpduCnf);
            }
            else
            {
                PIH_WARNING_LOG("SI_PIH_UsimCnfMsgProc:USIMM_SENDTPDUDATA_CNF Unknow SendPara");
            }
            break;

        case USIMM_ACTIVECARD_CNF:
            SI_PIH_ActiveSimCnfProc((USIMM_SINGLECMD_CNF_STRU *)pMsg);
            break;

#if (FEATURE_ON == FEATURE_IMS)
        case USIMM_AUTHENTICATION_CNF:
            SI_PIH_AuthCnfProc((USIMM_AUTHENTICATION_CNF_STRU *)pMsg);
            break;

        case USIMM_UPDATEFILE_CNF:
            SI_PIH_SetFileCnfProc((USIMM_UPDATEFILE_CNF_STRU *)pMsg);
            break;
#endif

        case USIMM_READFILE_CNF:
            SI_PIH_GetFileCnfProc((USIMM_READFILE_CNF_STRU *)pMsg);
            break;

        case USIMM_RACCESS_CNF:
            SI_PIH_RAccessCnfFromAT((USIMM_RACCESS_CNF_STRU*)pMsg);
            break;

        default:
            PIH_WARNING_LOG("SI_PIH_UsimCnfMsgProc:WARNING:Default Unknow Msg");
            ulResult = VOS_ERR;
            break;
    }

    /* ����g_pstPIHCurrNode��Ϊ������Ҫ������ʹ�ö��е�ͷ�� */
    if (VOS_NULL_PTR != g_pstPIHCurrNode)
    {
        SI_PIH_PutCtrlNode_Head(SI_PIH_INFO_USED_LIST_ID, g_pstPIHCurrNode);

        g_pstPIHCurrNode = VOS_NULL_PTR;
    }

    return ulResult;
}


VOS_UINT32 SI_PIH_UsimMsgProc(
    PS_SI_MSG_STRU                      *pMsg)
{
    VOS_UINT32                          ulResult;

    /* �ȴ��������ϱ�����Ϣ */
    if (VOS_OK == SI_PIH_UsimIndMsgProc(pMsg))
    {
        /* �����Ϣ�Ѿ������˾�ֱ�ӷ��� */
        return VOS_OK;
    }

    /* �ڴ���ظ���Ϣ */
    ulResult = SI_PIH_UsimCnfMsgProc(pMsg);

    return ulResult;
}
VOS_UINT32 SI_PIH_TimerMsgProc(
    REL_TIMER_MSG                       *pstMsg)
{
    VOS_UINT32                          ulResult = VOS_OK;

    if(g_stPIHProtectCtrl.enProtectState == SI_PIH_PROTECT_RUNING)
    {
        PIH_WARNING_LOG("SI_PIH_TimerMsgProc:Default Protect Running Discard Timer Msg");
        return ulResult;
    }

    switch(pstMsg->ulName)
    {
        case SI_PIH_TIMER_NAME_CHECKSTATUS:
        case SI_PIH_TIMER_NAME_CALL:
            ulResult = SI_PIH_SendStatusReqMsg(g_stPIHPollTime[pstMsg->ulName].enPollData);
            break;

        case SI_PIH_TIMER_NAME_CHECKIMSI:
            ulResult = SI_PIH_SendImsiPollingReqMsg();
            break;

        default:
            PIH_WARNING_LOG("SI_PIH_TimerMsgProc:Default Unknow Timer Msg");
            break;
    }

    return ulResult;
}
VOS_VOID SI_PIH_PidMsgProc(
    PS_SI_MSG_STRU                      *pMsg )
{
    VOS_UINT32 ulResult = VOS_ERR;

    OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_2,
                       pMsg->ulSenderPid,
                       MAPS_PIH_PID,
                       pMsg->ulMsgName);

    switch(pMsg->ulSenderPid)
    {
        case ACPU_PID_PCSC:
        case MAPS_PIH_PID:
        case WUEPS_PID_AT:
            ulResult = SI_PIH_MsgProc(pMsg);
            break;

        case WUEPS_PID_USIM:
            ulResult = SI_PIH_UsimMsgProc(pMsg);
            break;

        case VOS_PID_TIMER:
            ulResult = SI_PIH_TimerMsgProc((REL_TIMER_MSG*)pMsg);
            break;

        default:
            PIH_WARNING_LOG("SI_PIH_PidMsgProc:Default Unknow PID Msg");
            break;
    }

    if(ulResult == VOS_ERR)
    {
        PIH_ERROR_LOG("SI_PIH_PidMsgProc: The Msg Handle Error.");
    }

    OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_2);

    return;
}

/*****************************************************************************
�� �� ��  : WuepsSIFidInit
��������  : SI����ĳ�ʼ������
�������  : ip ��ʼ������
�������  : ��
�� �� ֵ  : VOS_UINT32����ʾ����ִ�н��
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2012��12��28��
  ��    ��  : zhuli
  �޸�����  : Create
*****************************************************************************/
VOS_UINT32 WuepsSIFidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32          ulRslt;

    switch( ip )
    {
        case VOS_IP_LOAD_CONFIG:
        {
            /* PB ģ��PID ע�� */
            ulRslt = VOS_RegisterPIDInfo(MAPS_PB_PID,
                                        (Init_Fun_Type)WuepsPBPidInit,
                                        (Msg_Fun_Type)SI_PB_PidMsgProc);
            if ( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            /* PIH ģ��PID ע�� */
            ulRslt = VOS_RegisterPIDInfo(MAPS_PIH_PID,
                                        (Init_Fun_Type)WuepsPIHPidInit,
                                        (Msg_Fun_Type)SI_PIH_PidMsgProc);
            if ( VOS_OK != ulRslt)
            {
                return VOS_ERR;
            }

            /* STK ģ��PID ע�� */
            ulRslt = VOS_RegisterPIDInfo(MAPS_STK_PID,
                                        (Init_Fun_Type)WuepsSTKPidInit,
                                        (Msg_Fun_Type)SI_STK_PidMsgProc);
            if ( VOS_OK != ulRslt)
            {
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterMsgTaskPrio(MAPS_SI_FID, VOS_PRIORITY_M5);

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
#endif /* __cpluscplus */
#endif /* __cpluscplus */



