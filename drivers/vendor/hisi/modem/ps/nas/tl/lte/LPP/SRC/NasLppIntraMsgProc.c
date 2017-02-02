/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasLppIntraMsgProc.c
  �� �� ��   : ����
  ��    ��   : XiaoJun
  ��������   : 2015��7��30��
  ����޸�   :
  ��������   : LPP ģ����ڲ���Ϣ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��7��30��
    ��    ��   : XiaoJun
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
#include  "vos.h"
#include  "NasLppPublic.h"
#include  "NasLppSendMsg.h"

#if (FEATURE_LPP == FEATURE_ON)
extern LPP_UPLINK_MSG_BUF_STRU*  NAS_LPP_GetLppMsgUpBuffByOpId
(
    VOS_UINT32              ulLmmLppOpId
);
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#define    THIS_FILE_ID            PS_FILE_ID_NASLPPINTRAMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLPPINTRAMSGPROC_C


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


/*****************************************************************************
 Function Name   : NAS_LPP_RcvIntraDataCnf
 Description     : �����ڲ�data cnf��Ϣ
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_RcvIntraDataCnf( NAS_LPP_INTRA_DATA_CNF_STRU *pRcvMsg)
{
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity;
    VOS_UINT8 ucSessionIndex,ucSessionTransIndx;
    NAS_LPP_SUB_STATE_ENUM_UINT32 enSubState;
    LPP_UPLINK_MSG_BUF_STRU  *pstUplinkMsgBuff = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_RcvIntraDataCnf enter!");

    /*ֹͣ���е�session������*/
    if (NAS_LPP_CONN_MANAGE_FAIL == pRcvMsg->enRslt)
    {
        NAS_LPP_ReleaseAllSession();
        return;
    }

    ucSessionIndex = NAS_LPP_SearchSessionIndx(pRcvMsg->stLppMsgIdentity.ulSessionId);

    pstUplinkMsgBuff = NAS_LPP_GetLppMsgUpBuffByOpId(pRcvMsg->ulOpId);
    if(NAS_LPP_NULL_PTR == pstUplinkMsgBuff)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_AckDataCnfSuccHandle: No buffer!");
        return;
    }


    /*����������Ӧ��SESSION��TRANSACTION*/
    pstTransEntity = NAS_LPP_SearchTransEntity(pRcvMsg->stLppMsgIdentity.ulSessionId,
                                               &(pRcvMsg->stLppMsgIdentity.stTransId),
                                               &ucSessionTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransEntity)
    {
        /* ����Ѿ��������������������ˣ����յ���������ʱ�ᷢ������LPP ACK��Ϣ�����ʱ���յ�DATA CNFʱ�Ҳ���TRANSACTION */
        NAS_LPP_RelUpMsgBuffer(&pstUplinkMsgBuff);
        NAS_LPP_NORM_LOG("NAS_LPP_RcvIntraDataCnf: Null!");
        return;
    }

    /*������������TRANSACTIONȡ��ǰ��״̬��״̬��ȷ���Ƿ���Ҫִ�е���Ϣ:������ǣ��˳�*/
    if (NAS_LPP_SUCCESS != NAS_LPP_TransFsmCheck(pstTransEntity->enLppMainState,
                                                 pstTransEntity->enLppSubState,
                                                 (PS_MSG_HEADER_STRU *)pRcvMsg) )
    {
        NAS_LPP_ERR_LOG2("intra data msg not match fsm, Main State,SubState",
                          pstTransEntity->enLppMainState,
                          pstTransEntity->enLppSubState);
        return;
    }

    /*�����transaction���ڵȴ�����LPP ACK(������LPP ABORT /LPP ERROR)������ɵ�״̬*/
    if ( LPP_SS_WAIT_INTRA_DATA_CNF_OF_UP_LPP_ACK == pstTransEntity->enLppSubState )
    {
        NAS_LPP_AbortAndErrorProcess(ucSessionIndex,
                                     ucSessionTransIndx,
                                     &(pRcvMsg->stLppMsgIdentity.stTransId));
        return;
    }

    /*������transaction��*/
    if (NAS_LPP_SUCCESS != pRcvMsg->enRslt)
    {
        NAS_LPP_ReleaseTransEntity(ucSessionIndex, ucSessionTransIndx);
    }

    /*upbuffer������2��LPPMSG: LPP ACK +  up lpp msg;������������϶�ֻ��һ��LPP ACK�ڷ��ͣ�û��������Ϣ*/
/*
    else if ( (PS_TRUE == pstTransEntity->ucTransEndFlag)&&(NAS_LPP_AIR_MSG_UP_LPP_ACK == pstTransEntity->enLastUpMsgId))
    {
        NAS_LPP_ReleaseTransEntity(ucSessionIndex, ucSessionTransIndx);
    }
    else if (  NAS_LPP_UPLINK_MSG_TYPE_ACK == pstUplinkMsgBuff->stLppMsgIdentity.enUplinkMsgType)
    {
        if ((PS_TRUE != pstTransEntity->ucTransEndFlag))
        {
           NAS_LPP_RelUpMsgBuffer(&pstUplinkMsgBuff);
        }
        else
        {

        }

    }
*/
    else if (PS_TRUE == pstTransEntity->ucTransEndFlag)
    {
        if (NAS_LPP_AIR_MSG_UP_LPP_ACK == pstTransEntity->enLastUpMsgId)/*upbuffer������2��LPPMSG: LPP ACK +  up lpp msg;������������϶�ֻ��һ��LPP ACK�ڷ��ͣ�û��������Ϣ*/
        {

            NAS_LPP_ReleaseTransEntity(ucSessionIndex, ucSessionTransIndx);
            return;

        }
        else if(  NAS_LPP_UPLINK_MSG_TYPE_ACK == pstUplinkMsgBuff->stLppMsgIdentity.enUplinkMsgType)
        {
            NAS_LPP_RelUpMsgBuffer(&pstUplinkMsgBuff);
            return;
        }
        else
        {
        }

    }
    else
    {
        if (  NAS_LPP_UPLINK_MSG_TYPE_ACK == pstUplinkMsgBuff->stLppMsgIdentity.enUplinkMsgType)
        {
            NAS_LPP_RelUpMsgBuffer(&pstUplinkMsgBuff);
            return;
        }
        else
        {

        }

    }

    /*�ɹ�������:ת��״̬���������ȴ�ACK�Ķ�ʱ��*/
    enSubState = NAS_LPP_GetWaitAckSubState( pstTransEntity->enLastUpMsgId, pstTransEntity->enLppMainState);
    NAS_LPP_INFO_LOG2("NAS_LPP_RcvIntraDataCnf: MainState, SubState", pstTransEntity->enLppMainState, enSubState);
    NAS_LPP_ChangeTransFsmState(ucSessionIndex, ucSessionTransIndx, pstTransEntity->enLppMainState, enSubState );

}

/*****************************************************************************
 Function Name   : NAS_LPP_LppMsgDistr
 Description     : LPPģ���LPPģ���Լ������ڲ���Ϣ�Ĵ�����ں���
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_LppMsgDistr( VOS_VOID *pRcvMsg )
{
    NAS_LPP_INTRA_MSG_STRU *pstIntraMsg = NAS_LPP_NULL_PTR;

    NAS_LPP_WARN_LOG("NAS_LPP_LppMsgDistr enter!");

    pstIntraMsg = (NAS_LPP_INTRA_MSG_STRU*)pRcvMsg;

    /*������Ϣ����������Ӧ����Ϣ������*/
    switch ( pstIntraMsg->ulMsgId )
    {
        case ID_NAS_LPP_INTRA_DATA_CNF :
            NAS_LPP_RcvIntraDataCnf((NAS_LPP_INTRA_DATA_CNF_STRU *)pstIntraMsg);
            break;
        /*
        case # :

            break;*/
        default:
            break;
    }

    return;
}









#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

