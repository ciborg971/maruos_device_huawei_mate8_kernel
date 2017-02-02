

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "TafCbaProcAt.h"
#include  "TafCbsInterface.h"
#include  "TafCbaComFunc.h"
#include  "TafCbaProcUsim.h"

#include  "TafLog.h"
#include  "MnErrorCode.h"
#include  "MnMsgApi.h"
#include  "TafClientApi.h"
#include  "MnComm.h"
#include  "MnMsgSmCommProc.h"
#include  "TafTypeDef.h"
#include  "TafCbaProcNvim.h"
#include  "TafCbaMntn.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_CBA_PROC_AT_C

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

extern MN_MSG_EVENT_INFO_STRU           f_stMsgEventInfo;

/*lint -save -e958 */

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


VOS_VOID TAF_CBA_SndAtRcvCbmMsg(
    const MN_MSG_CBRAW_TS_DATA_STRU    *pstTpduData
)
{
    MN_MSG_CB_DELIVER_EVT_INFO_STRU    *pstCbDeliver;
    MN_OPERATION_ID_T                   ucOpId;

    /* �㲥�ϱ���һ��CBS */
    ucOpId = MN_MSG_GetBCopId();

    PS_MEM_SET(&f_stMsgEventInfo,0x00,sizeof(f_stMsgEventInfo));

    f_stMsgEventInfo.opId           = ucOpId;
    f_stMsgEventInfo.clientId       = MN_CLIENT_ALL;
    pstCbDeliver                    = &(f_stMsgEventInfo.u.stCbsDeliverInfo);
    pstCbDeliver->bSuccess          = VOS_TRUE;
    pstCbDeliver->ulFailCause       = MN_ERR_NO_ERROR;
    PS_MEM_CPY(&pstCbDeliver->stCbRawData,pstTpduData,sizeof(MN_MSG_CBRAW_TS_DATA_STRU));

    MN_SendClientEvent(MN_CLIENT_ALL,
                       MN_CALLBACK_MSG,
                       MN_MSG_EVT_DELIVER_CBM,
                       &f_stMsgEventInfo);

}
VOS_VOID  TAF_CBA_SndAtGetAllCbMidsRslt(
    const MN_MSG_EVENT_PARM_STRU       *pstEventParm
)
{
    MN_MSG_CBMIDS_GET_EVT_INFO_STRU    *pstCbsCbMids;

    PS_MEM_SET(&f_stMsgEventInfo, 0x00, sizeof(f_stMsgEventInfo));

    f_stMsgEventInfo.opId   = pstEventParm->opId;
    pstCbsCbMids            = (MN_MSG_CBMIDS_GET_EVT_INFO_STRU *)&f_stMsgEventInfo.u.stCbsCbMids;

    if (MN_ERR_NO_ERROR != pstEventParm->ulFailCause)
    {
        pstCbsCbMids->bSuccess    = VOS_FALSE;
        pstCbsCbMids->ulFailCause = pstEventParm->ulFailCause;
    }
    else
    {
        pstCbsCbMids->bSuccess    = VOS_TRUE;
    }

    TAF_CBA_GetActiveMids(&(pstCbsCbMids->stCbMidr));

    MN_SendClientEvent(pstEventParm->clientId,
                       MN_CALLBACK_MSG,
                       MN_MSG_EVT_GET_CBTYPE,
                       &f_stMsgEventInfo);
}


VOS_VOID  TAF_CBA_SndAtModifyCbMidsRlst(
    const MN_MSG_EVENT_PARM_STRU       *pstEventParm,
    VOS_UINT32                          ulEventType
)
{
    MN_MSG_CBMIDS_CHANGE_EVT_INFO_STRU *pstCbMidsInfo;

    PS_MEM_SET(&f_stMsgEventInfo, 0X00, sizeof(f_stMsgEventInfo));

    f_stMsgEventInfo.opId   = pstEventParm->opId;
    pstCbMidsInfo           = (MN_MSG_CBMIDS_CHANGE_EVT_INFO_STRU *)&f_stMsgEventInfo.u.stCbsChangeInfo;

    if (MN_ERR_NO_ERROR != pstEventParm->ulFailCause)
    {
        pstCbMidsInfo->bSuccess    = VOS_FALSE;
        pstCbMidsInfo->ulFailCause = pstEventParm->ulFailCause;
    }
    else
    {
        pstCbMidsInfo->bSuccess    = VOS_TRUE;
    }

    MN_SendClientEvent(pstEventParm->clientId,
                       MN_CALLBACK_MSG,
                       ulEventType,
                       &f_stMsgEventInfo);

}


#if (FEATURE_ON == FEATURE_ETWS)


VOS_VOID  TAF_CBA_SndAtEtwsPrimNtfMsg(
    RR_CBS_ETWS_PRIMARY_NOTIFY_IND_STRU                    *pstPrimNtfMsg
)
{
    TAF_CBA_ETWS_PRIM_NTF_EVT_INFO_STRU                    *pstPrimNtfEvt;

    PS_MEM_SET(&f_stMsgEventInfo, 0X00, sizeof(f_stMsgEventInfo));

    /* �㲥�ϱ� */
    f_stMsgEventInfo.opId       = MN_MSG_GetBCopId();
    f_stMsgEventInfo.clientId   = MN_CLIENT_ALL;
    pstPrimNtfEvt               = &f_stMsgEventInfo.u.stEtwsPrimNtf;

    pstPrimNtfEvt->stPlmn.ulMcc = pstPrimNtfMsg->stCurrNetworkInfo.stCurPlmn.ulMcc;
    pstPrimNtfEvt->stPlmn.ulMnc = pstPrimNtfMsg->stCurrNetworkInfo.stCurPlmn.ulMnc;
    pstPrimNtfEvt->usWarnType   = pstPrimNtfMsg->usWarnType;
    pstPrimNtfEvt->usMsgId      = pstPrimNtfMsg->usMessageId;
    pstPrimNtfEvt->usSN         = pstPrimNtfMsg->usSerialNumber;

    /* ��Ȩ���ĿǰĬ��Ϊδͨ����Ȩ */
    pstPrimNtfEvt->enAuthRslt   = TAF_CBA_ETWS_PRIM_NTF_AUTH_FAILED;

    MN_SendClientEvent(MN_CLIENT_ALL,
                       MN_CALLBACK_MSG,
                       MN_MSG_EVT_DELIVER_ETWS_PRIM_NOTIFY,
                       &f_stMsgEventInfo);

}

#endif /* (FEATURE_ON == FEATURE_ETWS) */


/*****************************************************************************
 �� �� ��  : TAF_CBA_InitEventParm
 ��������  : ��ʼ����Ϣ�ϱ��¼��Ļ�������
 �������  : clientId    : ����������Client��ID
             opId        : Operation ID, ��ʶ���β���
 �������  : pstEventParm: ��Ϣ�ϱ��¼��Ļ�������
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��25��
    ��    ��   : ��ӳ�� 62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_CBA_InitEventParm(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_EVENT_PARM_STRU             *pstEventParm
)
{
    pstEventParm->clientId      = clientId;
    pstEventParm->opId          = opId;
    pstEventParm->ulFailCause   = MN_ERR_NO_ERROR;
}


VOS_VOID TAF_CBA_RcvAtGetAllCbMids(
    MN_CLIENT_ID_T                     clientId,
    MN_OPERATION_ID_T                  opId
)
{
    MN_MSG_EVENT_PARM_STRU             stEventParm;

    MN_SendClientResponse(clientId, opId, MN_ERR_NO_ERROR);

    TAF_CBA_InitEventParm(clientId, opId, &stEventParm);

    TAF_CBA_SndAtGetAllCbMidsRslt(&stEventParm);

    return;
}


VOS_VOID  TAF_CBA_RcvAtAddCbMids(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstAddCbMidsList
)
{
    VOS_UINT32                          ulRet;
    MN_MSG_EVENT_PARM_STRU              stEventParm;


    /* AT���ù�����MID�б�MSG ID��Ҫ����ΪС��MSG ID
       �ŵ�usMsgIdFrom��,���MSG ID�ŵ�usMsgIdTo�� */
    TAF_CBA_SortCbmiRangeList(pstAddCbMidsList);

    MN_SendClientResponse(clientId, opId, MN_ERR_NO_ERROR);

    TAF_CBA_InitEventParm(clientId, opId, &stEventParm);


    /* ���ظ���MSG IDҲ�������� */

    /* ����ǰ��CBMIDR�б���µ��ڴ��� */
    ulRet = TAF_CBA_AddCbMiRangeListToActiveList(pstAddCbMidsList);
    if (VOS_OK != ulRet)
    {
        stEventParm.ulFailCause = MN_ERR_CLASS_CBS_TOO_CBMIDS;
        TAF_CBA_SndAtModifyCbMidsRlst(&stEventParm, MN_MSG_EVT_ADD_CBMIDS);
        return;
    }

    /* ����NV���USIM�ļ��Լ�������Ϣ */
    TAF_CBA_RcvAtModifyMsgIds();

    /* ֱ���ڴ˴��ϱ�,����Ҫ�ȴ������ظ���CNF��Ϣ,�˴������ֿ���,
           1.�����ظ���CNFʧ�ܺ�,�޷��ָ��ڴ�
           2.���͸�USIM�޸��ļ��Ľӿ�,USIM�ļ�����ʧ�ܺ�Ҳ�������κδ��� */
    stEventParm.ulFailCause = MN_ERR_NO_ERROR;
    TAF_CBA_SndAtModifyCbMidsRlst(&stEventParm, MN_MSG_EVT_ADD_CBMIDS);
}


VOS_VOID TAF_CBA_RcvAtDelCbMids(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstDelCbMids
)
{
    VOS_UINT32                          ulRet;
    MN_MSG_EVENT_PARM_STRU              stEventParm;


    MN_SendClientResponse(clientId, opId, MN_ERR_NO_ERROR);

    TAF_CBA_InitEventParm(clientId, opId, &stEventParm);

    /* �ȶ�range list���� */
    TAF_CBA_SortCbmiRangeList(pstDelCbMids);

    /* ���ڴ���ɾ��CBMIDS,����ڴ���û����ֱ�ӷ���, ������USIM��NIVM�Լ�AS */
    ulRet = TAF_CBA_DelCbMiRangeListFromActiveList(pstDelCbMids);
    if ( VOS_FALSE == ulRet )
    {
        stEventParm.ulFailCause = MN_ERR_NO_ERROR;
        TAF_CBA_SndAtModifyCbMidsRlst(&stEventParm, MN_MSG_EVT_DELETE_CBMIDS);
        return;
    }

    /* ɾ�����ڼ����б��е���ʷ��¼�� */
    TAF_CBA_DelRecordByActiveList();

    /* ����NV���USIM�ļ��Լ�������Ϣ */
    TAF_CBA_RcvAtModifyMsgIds();

    /* ֱ���ڴ˴��ϱ�,����Ҫ�ȴ������ظ���CNF��Ϣ,�˴������ֿ���,
           1.�������ظ���CNFʧ�ܺ�,�޷��ظ��ڴ�
           2.���͸�USIM�޸��ļ��Ľӿ�,USIM�ļ�����ʧ�ܺ�Ҳ�������κδ��� */
    stEventParm.ulFailCause = MN_ERR_NO_ERROR;
    TAF_CBA_SndAtModifyCbMidsRlst(&stEventParm, MN_MSG_EVT_DELETE_CBMIDS);
}



VOS_VOID TAF_CBA_RcvAtEmptyCbMids(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId
)
{
    VOS_UINT32                          ulRet;
    MN_MSG_EVENT_PARM_STRU              stEventParm;


    MN_SendClientResponse(clientId, opId, MN_ERR_NO_ERROR);

    TAF_CBA_InitEventParm(clientId, opId, &stEventParm);

    /* ���ж�CBMI RANGE LIST�Ƿ���Ϊ�� */
    ulRet = TAF_CBA_IsCbmiRangeListEmpty();
    if (VOS_TRUE == ulRet)
    {
       stEventParm.ulFailCause = MN_ERR_NO_ERROR;
       TAF_CBA_SndAtModifyCbMidsRlst(&stEventParm, MN_MSG_EVT_DELETE_ALL_CBMIDS);
       return;
    }

    /* ����ڴ���CBMI RANGE LIST */
    TAF_CBA_InitCbmiRangeList();

    /* ���CBS��Ϣ��ʷ��¼�� */
    TAF_CBA_InitRecordList();

    /* ����NV���USIM�ļ��Լ�������Ϣ */
    TAF_CBA_RcvAtModifyMsgIds();

    /* ֱ���ڴ˴��ϱ�,����Ҫ�ȴ������ظ���CNF��Ϣ,�˴������ֿ���,
           1.�������ظ���CNFʧ�ܺ�,�޷��ظ��ڴ�
           2.���͸�USIM�޸��ļ��Ľӿ�,USIM�ļ�����ʧ�ܺ�Ҳ�������κδ��� */
    stEventParm.ulFailCause = MN_ERR_NO_ERROR;
    TAF_CBA_SndAtModifyCbMidsRlst(&stEventParm, MN_MSG_EVT_DELETE_ALL_CBMIDS);

}


VOS_VOID TAF_CBA_ProcAtMsg(
    struct MsgCB                       *pstMsg
)
{
    MN_APP_REQ_MSG_STRU                *pstAppMsg;

    pstAppMsg = (MN_APP_REQ_MSG_STRU*)pstMsg;

    switch(pstAppMsg->usMsgName)
    {
        case MN_MSG_MSGTYPE_GET_ALLCBMIDS:
            TAF_CBA_RcvAtGetAllCbMids(pstAppMsg->clientId,
                                      pstAppMsg->opId);
            break;

        case MN_MSG_MSGTYPE_ADD_CBMIDS:
            TAF_CBA_RcvAtAddCbMids(pstAppMsg->clientId,
                                   pstAppMsg->opId,
                                  (TAF_CBA_CBMI_RANGE_LIST_STRU *)pstAppMsg->aucContent);
            break;
        case MN_MSG_MSGTYPE_DELETE_CBMIDS:
            TAF_CBA_RcvAtDelCbMids(pstAppMsg->clientId,
                                   pstAppMsg->opId,
                                  (TAF_CBA_CBMI_RANGE_LIST_STRU *)pstAppMsg->aucContent);
            break;

        case MN_MSG_MSGTYPE_EMPTY_CBMIDS:
            TAF_CBA_RcvAtEmptyCbMids(pstAppMsg->clientId,pstAppMsg->opId);
            break;

        default:
            break;
    }
}


VOS_VOID TAF_CBA_UpdateAsCbsActiveState(VOS_VOID)
{
    VOS_UINT32                          ulIsActiveListEmpty;

    /* ��ǰ�꿪��δ�򿪻�CBSδ����,��ֱ�ӷ���  */
    if ( VOS_FALSE == TAF_CBA_IsNeedActAsCbs())
    {
        return;
    }

    /* ���ݼ����б��Ƿ�Ϊ��, ���������ȥ����AS��CBS���� */
    ulIsActiveListEmpty = TAF_CBA_IsCbsActiveListEmpty();

    if (VOS_TRUE == ulIsActiveListEmpty)
    {
        TAF_CBA_SndAsActiveCbsReq(TAF_CBS_CFG_DEACTIVE);
    }
    else
    {
        TAF_CBA_SndAsActiveCbsReq(TAF_CBS_CFG_ACTIVE);
    }
}


VOS_VOID TAF_CBA_RcvAtModifyMsgIds(VOS_VOID)
{
    /* ����NV���е�MSGID �б� */
    TAF_CBA_WriteCbmiRangeListNvim();

    /* ����USIM�е�MSGID �ļ� */
    TAF_CBA_UpdateUsimFile();

    /* ���ݵ�ǰ�ļ����б��������������CBS ���� */
    TAF_CBA_UpdateAsCbsActiveState();

    /* ��ά�ɲ���Ϣ */
    TAF_CBA_SndOmCbmiDownloadListInfo();

    /* ��ά�ɲ���Ϣ */
    TAF_CBA_SndOmCbmiRangeList();

    return;
}
VOS_VOID TAF_CBA_GetActiveMids(
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstActiveCbMids
)
{
    VOS_INT32                           ulCbmidRangeInx;
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstCbmiRangeList;
    VOS_UINT16                          usCbmiRangNum;

    PS_MEM_SET(pstActiveCbMids, 0, sizeof(TAF_CBA_CBMI_RANGE_LIST_STRU));

    pstCbmiRangeList = TAF_CBA_GetCbMiRangeList();
    usCbmiRangNum    = TAF_CBA_GetCbmiRangNum();

    if (usCbmiRangNum >= TAF_CBA_MAX_CBMID_RANGE_NUM)
    {
        usCbmiRangNum = TAF_CBA_MAX_CBMID_RANGE_NUM;
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_GetActiveMids: usCbmiRangNum ERROR!");
    }

    for ( ulCbmidRangeInx = 0; ulCbmidRangeInx < usCbmiRangNum; ulCbmidRangeInx++ )
    {
        /* ����ϢID��״̬��Ϊ�������Թ� */
        if ( TAF_CBA_CBMI_RANGE_RCV_MODE_ACCEPT != (pstCbmiRangeList->astCbmiRangeInfo[ulCbmidRangeInx].enRcvMode) )
        {
            continue;
        }

        /* �������CBS��ϢID���Ƶ���������� */
        PS_MEM_CPY(&(pstActiveCbMids->astCbmiRangeInfo[pstActiveCbMids->usCbmirNum]),
                   &(pstCbmiRangeList->astCbmiRangeInfo[ulCbmidRangeInx]),
                   sizeof(pstActiveCbMids->astCbmiRangeInfo[pstActiveCbMids->usCbmirNum]));

        pstActiveCbMids->usCbmirNum++;
    }

    return;
}

/*lint -restore */


#endif /* ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS)) */




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
