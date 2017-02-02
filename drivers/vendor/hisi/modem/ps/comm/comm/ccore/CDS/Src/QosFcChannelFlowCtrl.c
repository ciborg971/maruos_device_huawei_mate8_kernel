


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#include "CDS.h"
#include "QosFcCommon.h"
#include "QosFcChannelFlowCtrl.h"
#include "QosFcOm.h"
#include "FcCdsInterface.h"
#include "CdsMsgProc.h"


/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_QOS_FC_CHANNEL_FLOWCTRL_C
/*lint +e767*/




/*****************************************************************************
  2 �ⲿ��������
*****************************************************************************/

/******************************************************************************
   3 ˽�ж���
******************************************************************************/

/******************************************************************************
   4 ȫ�ֱ�������
******************************************************************************/
QOS_FC_CHANNEL_ENTITY_STRU g_stQosFcChannelEntity[FC_MAX_RAB_NUM];

/******************************************************************************
   5 ����ʵ��
******************************************************************************/

VOS_VOID QosFcChannelInit(VOS_VOID)
{
    VOS_UINT32 i=0;
    for(i = 0; i < FC_MAX_RAB_NUM; i++)
    {
        g_stQosFcChannelEntity[i].ucRabId = FC_INVALID_RABID;
        g_stQosFcChannelEntity[i].enQci = QCI_TYPE_BUTT;
        g_stQosFcChannelEntity[i].enChannelState = QOS_FC_CHANNEL_STATE_BUTT;
    }

    return;
}


VOS_VOID QosFc_SendStopChannel2AFC(VOS_UINT32 ulIndex)
{
    CDS_FC_STOP_CHANNEL_IND_STRU    *pstStopChannelInd;
    QOS_FC_CHANNEL_ENTITY_STRU      *pstQosFcChannelEntity;
    MODEM_ID_ENUM_UINT16             enModemId;

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter QosFc_SendStopChannel2AFC ");
    CDS_PRINT_ERROR(QosFc_SendStopChannel2AFC_ENUM, CDS_FUNCTION_ENTER);

    if(FC_MAX_RAB_NUM <= ulIndex)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"QosFc_SendStopChannel2AFC : Error Index: ",ulIndex);
        CDS_PRINT_ERROR1(QosFc_SendStopChannel2AFC_ENUM, CDS_FC_CH_INDEX_INVALID,ulIndex);
        return;
    }

    pstQosFcChannelEntity = &g_stQosFcChannelEntity[ulIndex];
    if(QosFc_IsInValidRabId(FC_MASK_RABID & pstQosFcChannelEntity->ucRabId))
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"QosFc_SendStopChannel2AFC : Error RabId: ",pstQosFcChannelEntity->ucRabId);
        CDS_PRINT_ERROR1(QosFc_SendStopChannel2AFC_ENUM, CDS_RAB_ID_INVALID,pstQosFcChannelEntity->ucRabId);
        return ;
    }

    enModemId = pstQosFcChannelEntity->ucRabId >> FC_MODEMID_SHIFT;
    if(MODEM_ID_BUTT <= enModemId)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"QosFc_SendStopChannel2AFC : Error ModemId:", enModemId);
        CDS_PRINT_ERROR1(QosFc_SendStopChannel2AFC_ENUM, CDS_MODEM_ID_INVALID,enModemId);
        return;
    }

    /*����OSA��Ϣ�ڴ�*/
    pstStopChannelInd = (VOS_VOID *)PS_ALLOC_MSG_ALL_CHECK(UEPS_PID_CDS, sizeof(CDS_FC_STOP_CHANNEL_IND_STRU));
    if (VOS_NULL_PTR == pstStopChannelInd)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"QosFc_SendStopChannel2AFC : Error to Alloc Msg Mem");
        CDS_PRINT_ERROR(QosFc_SendStopChannel2AFC_ENUM, CDS_ALLOC_MSG_FAIL);
        return ;
    }

    /*��д��Ϣ����*/
    CDS_CFG_MSG_HDR(pstStopChannelInd, ACPU_PID_FC);
    pstStopChannelInd->enMsgName = ID_CDS_FC_STOP_CHANNEL_IND;
    pstStopChannelInd->ucRabId = FC_MASK_RABID & pstQosFcChannelEntity->ucRabId;
    pstStopChannelInd->enModemId = enModemId;

    /*������Ϣ*/
    if (VOS_OK != PS_SND_MSG_ALL_CHECK(UEPS_PID_CDS, pstStopChannelInd))
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"QosFc_SendStopChannel2AFC : Send Msg Fail");
        CDS_PRINT_ERROR(QosFc_SendStopChannel2AFC_ENUM, CDS_SEND_MSG_FAIL);
        return;
    }

    FC_DBG_CHANNEL_FC_STAT(enModemId, (FC_MASK_RABID & pstQosFcChannelEntity->ucRabId), 1);
    CDS_WARNING_LOG1(UEPS_PID_CDS,"QosFc_SendStopChannel2AFC: Send Stop Msg Succ:", pstQosFcChannelEntity->ucRabId);
    CDS_PRINT_ERROR(QosFc_SendStopChannel2AFC_ENUM, CDS_FUNCTION_LEAVE);

    return;
}
VOS_VOID QosFc_SendStartChannel2AFC(VOS_UINT32 ulIndex)
{
    CDS_FC_START_CHANNEL_IND_STRU   *pstStartChannelInd;
    QOS_FC_CHANNEL_ENTITY_STRU      *pstQosFcChannelEntity;
    MODEM_ID_ENUM_UINT16             enModemId;

    CDS_INFO_LOG(UEPS_PID_CDS,"Enter QosFc_SendStartChannel2AFC ");
    CDS_PRINT_INFO(QosFc_SendStartChannel2AFC_ENUM, CDS_FUNCTION_ENTER);

    if(FC_MAX_RAB_NUM <= ulIndex)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"QosFc_SendStartChannel2AFC : Error Index: ",ulIndex);
        CDS_PRINT_ERROR1(QosFc_SendStartChannel2AFC_ENUM, CDS_FC_CH_INDEX_INVALID,ulIndex);
        return;
    }

    pstQosFcChannelEntity = &g_stQosFcChannelEntity[ulIndex];
    if(QosFc_IsInValidRabId(FC_MASK_RABID & pstQosFcChannelEntity->ucRabId))
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"QosFc_SendStartChannel2AFC : Error RabId: ",pstQosFcChannelEntity->ucRabId);
        CDS_PRINT_ERROR1(QosFc_SendStartChannel2AFC_ENUM, CDS_RAB_ID_INVALID,pstQosFcChannelEntity->ucRabId);
        return;
    }

    enModemId = pstQosFcChannelEntity->ucRabId >> FC_MODEMID_SHIFT;
    if(MODEM_ID_BUTT <= enModemId)
    {
        CDS_ERROR_LOG1(UEPS_PID_CDS,"QosFc_SendStartChannel2AFC : Error ModemId:", enModemId);
        CDS_PRINT_ERROR1(QosFc_SendStartChannel2AFC_ENUM, CDS_MODEM_ID_INVALID,enModemId);
        return;
    }

    /*����OSA��Ϣ�ڴ�*/
    pstStartChannelInd = (VOS_VOID *)PS_ALLOC_MSG_ALL_CHECK(UEPS_PID_CDS, sizeof(CDS_FC_START_CHANNEL_IND_STRU));
    if (VOS_NULL_PTR == pstStartChannelInd)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"QosFc_SendStartChannel2AFC : Error to Alloc Msg Mem");
        CDS_PRINT_ERROR(QosFc_SendStartChannel2AFC_ENUM, CDS_ALLOC_MSG_FAIL);
        return ;
    }

    /*��д��Ϣ����*/
    CDS_CFG_MSG_HDR(pstStartChannelInd, ACPU_PID_FC);
    pstStartChannelInd->enMsgName = ID_CDS_FC_START_CHANNEL_IND;
    pstStartChannelInd->ucRabId = FC_MASK_RABID & pstQosFcChannelEntity->ucRabId;
    pstStartChannelInd->enModemId = enModemId;

    /*������Ϣ*/
    if (VOS_OK != PS_SND_MSG_ALL_CHECK(UEPS_PID_CDS, pstStartChannelInd))
    {
        CDS_ERROR_LOG(UEPS_PID_CDS,"QosFc_SendStartChannel2AFC : Send Msg Fail");
        CDS_PRINT_ERROR(QosFc_SendStartChannel2AFC_ENUM, CDS_SEND_MSG_FAIL);
        return;
    }

    FC_DBG_CHANNEL_RESUME_STAT(enModemId, (FC_MASK_RABID & pstQosFcChannelEntity->ucRabId), 1);
    CDS_WARNING_LOG1(UEPS_PID_CDS,"QosFc_SendStartChannel2AFC: Send Start Msg Succ:", pstQosFcChannelEntity->ucRabId);
    CDS_PRINT_INFO1(QosFc_SendStartChannel2AFC_ENUM, CDS_FUNCTION_LEAVE,pstQosFcChannelEntity->ucRabId);

    return;
}
VOS_VOID QosFc_ChannelControl(VOS_UINT8 ucRabId)
{
    VOS_UINT32  i;

    for(i = 0; i < FC_MAX_RAB_NUM; i++)
    {
        if(ucRabId == g_stQosFcChannelEntity[i].ucRabId)
        {
            /* �ҵ���Ӧͨ��λ�� */
            break;
        }
    }
    if(FC_MAX_RAB_NUM == i)
    {
        /* ������ */
        CDS_ERROR_LOG1(UEPS_PID_CDS, "QosFc_ChannelControl : Not find the channel: ", ucRabId);
        CDS_PRINT_ERROR1(QosFc_ChannelControl_ENUM, CDS_RAB_ID_INVALID,ucRabId);
        return;
    }

    if(QOS_FC_CHANNEL_STATE_FLOWCTRL != g_stQosFcChannelEntity[i].enChannelState)
    {
        CDS_WARNING_LOG2(UEPS_PID_CDS, "QosFc_ChannelControl : RabId: Pre State:", ucRabId, g_stQosFcChannelEntity[i].enChannelState );
        CDS_PRINT_WARNING2(QosFc_ChannelControl_ENUM, CDS_FC_CH_PRE_STATE, ucRabId, g_stQosFcChannelEntity[i].enChannelState);
        /* ��ͨ��Ϊ����״̬ */
        g_stQosFcChannelEntity[i].enChannelState = QOS_FC_CHANNEL_STATE_FLOWCTRL;

        QosFc_SendStopChannel2AFC(i);
    }

    return;
}
VOS_VOID QosFc_ChannelRestore(VOS_UINT8 ucRabId)
{
    VOS_UINT32  i;

    for(i = 0; i < FC_MAX_RAB_NUM; i++)
    {
        if(ucRabId == g_stQosFcChannelEntity[i].ucRabId)
        {
            /* �ҵ���Ӧͨ��λ�� */
            break;
        }
    }
    if(FC_MAX_RAB_NUM == i)
    {
        /* ������ */
        CDS_ERROR_LOG1(UEPS_PID_CDS, "QosFc_ChannelRestore : Not find the channel: ", ucRabId);
        CDS_PRINT_ERROR1(QosFc_ChannelRestore_ENUM, CDS_RAB_ID_INVALID,ucRabId);
        return;
    }

    if(QOS_FC_CHANNEL_STATE_NORMAL != g_stQosFcChannelEntity[i].enChannelState)
    {
        CDS_WARNING_LOG2(UEPS_PID_CDS, "QosFc_ChannelRestore : RabId: Pre State:", ucRabId, g_stQosFcChannelEntity[i].enChannelState );
        CDS_PRINT_WARNING2(QosFc_ChannelRestore_ENUM, CDS_FC_CH_PRE_STATE, ucRabId, g_stQosFcChannelEntity[i].enChannelState);
        /* �ָ�ͨ������ */
        g_stQosFcChannelEntity[i].enChannelState = QOS_FC_CHANNEL_STATE_NORMAL;

        QosFc_SendStartChannel2AFC(i);
    }

    return;
}
VOS_VOID QosFc_UpdateChannelQos(VOS_UINT8 ucRabId, QCI_TYPE_ENUM_UINT8 enQci)
{
    VOS_UINT32  i,j;

    for(i = 0; i < FC_MAX_RAB_NUM; i++)
    {
        if((ucRabId == g_stQosFcChannelEntity[i].ucRabId)
            ||(FC_INVALID_RABID == g_stQosFcChannelEntity[i].ucRabId))
        {
            /* �ҵ���Ӧͨ��λ�� */
            break;
        }
    }

    if(FC_MAX_RAB_NUM == i)
    {
        /* ������ */
        CDS_ERROR_LOG(UEPS_PID_CDS, "QosFc_UpdateChannelQos : too many channel created!");
        CDS_PRINT_ERROR(QosFc_UpdateChannelQos_ENUM, CDS_RAB_ID_INVALID);
        return;
    }

    if(QCI_TYPE_BUTT != enQci)
    {
        if(FC_INVALID_RABID == g_stQosFcChannelEntity[i].ucRabId)
        {
            /* �½�ͨ�� */
            g_stQosFcChannelEntity[i].ucRabId = ucRabId;
            g_stQosFcChannelEntity[i].enQci = enQci;
            g_stQosFcChannelEntity[i].enChannelState = QOS_FC_CHANNEL_STATE_NORMAL;
            CDS_WARNING_LOG2(UEPS_PID_CDS, "QosFc_UpdateChannelQos : Create Channel: Qci:", ucRabId, enQci);
            CDS_PRINT_WARNING2(QosFc_UpdateChannelQos_ENUM, CDS_FC_CH_CREATE_QCI, ucRabId, enQci);
        }
        else
        {
            CDS_WARNING_LOG3(UEPS_PID_CDS, "QosFc_UpdateChannelQos : Update Channel: Qci: -> :", ucRabId, g_stQosFcChannelEntity[i].enQci, enQci);
            CDS_PRINT_WARNING2(QosFc_UpdateChannelQos_ENUM, CDS_FC_CH_UPDATE_QCI, g_stQosFcChannelEntity[i].enQci, enQci);
            /* ����QCI */
            g_stQosFcChannelEntity[i].enQci = enQci;
        }

        /* ��A������ģ�鷢��Ϣ����ͨ��QCI */
        /* ����AT����ͨ��QCI���˴�������Ϣ */
    }
    else
    {
        /* ��A������ģ�鷢��Ϣɾ��ͨ�� */
        /* ����AT���𣬴˴�������Ϣ */

        /* ͨ��ɾ��ʱ�ָ�ͨ��״̬��������� */
        QosFc_ChannelRestore(ucRabId);

        CDS_WARNING_LOG2(UEPS_PID_CDS, "QosFc_UpdateChannelQos : Delete Channel: Qci:", g_stQosFcChannelEntity[i].ucRabId, g_stQosFcChannelEntity[i].enQci);
        CDS_PRINT_WARNING2(QosFc_UpdateChannelQos_ENUM, CDS_FC_CH_DELETE_QCI, g_stQosFcChannelEntity[i].ucRabId, g_stQosFcChannelEntity[i].enQci);

        /* ɾ��ͨ�� */
        for(j = i; j < FC_MAX_RAB_NUM-1; j++)
        {
            if(FC_INVALID_RABID == g_stQosFcChannelEntity[j+1].ucRabId)
            {
                break;
            }
            (VOS_VOID)VOS_MemCpy(&g_stQosFcChannelEntity[j], &g_stQosFcChannelEntity[j+1], sizeof(QOS_FC_CHANNEL_ENTITY_STRU));
        }

        g_stQosFcChannelEntity[j].ucRabId = FC_INVALID_RABID;
        g_stQosFcChannelEntity[j].enQci = QCI_TYPE_BUTT;
        g_stQosFcChannelEntity[j].enChannelState = QOS_FC_CHANNEL_STATE_BUTT;

    }

    return;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



