/******************************************************************************

                  ��Ȩ���� (C), 2001-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXsmsSndAt.c
  �� �� ��   : ����
  ��    ��   : h00300778
  ��������   : 2014��10��31��
  ��������   : 1X SMS(Short Message Service) ��AT�Ļظ�������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafXsmsSndAt.h"
#include "TafXsmsUimProc.h"
#include "TafXsmsCtx.h"
#include "MnClient.h"
#include "TafXpdsXsmsInterface.h"



#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XSMS_SND_AT_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 �� �� ��  : TAF_XSMS_MsgInitInd
 ��������  : 1XSMS��AT�Ķ��ų�ʼ�����ָʾ�ϱ�����
 �������  : ulTotalNum:���ŵ��ܼ�¼��
 �������  : ��
 �� �� ֵ  : VOS_OK -- ���ͳɹ�
             VOS_ERR -- ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��1��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_MsgInitInd(VOS_UINT32 ulTotalNum)
{
    TAF_XSMS_APP_AT_EVENT_INFO_STRU     stEvent;

    /* �����Ϣ�ṹ���㲥�ϱ� */
    stEvent.usClientId = MN_CLIENT_ALL;
    stEvent.ucOpId     = 0;
    stEvent.ulError    = VOS_OK;

    stEvent.XSmsEvent.stInitInd.ulTotalNum = ulTotalNum;

    return TAF_XSMS_SmsEventCallBack(TAF_XSMS_APP_MSG_TYPE_INIT_IND, &stEvent);
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_MsgSubmitCnf
 ��������  : 1XSMS��AT�Ķ��ŷ��ͽ���ظ�����
 �������  : usClientId:Client ID
             ucOpId:Op Id
             ulRslt:���ŵķ��ͽ��
 �������  : ��
 �� �� ֵ  : VOS_OK -- ���ͳɹ�
             VOS_ERR -- ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��1��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_MsgSubmitCnf(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT32                          ulRslt
)
{
    TAF_XSMS_APP_AT_EVENT_INFO_STRU     stEvent;

    /* �����Ϣ�ṹ */
    stEvent.usClientId = usClientId;
    stEvent.ucOpId     = ucOpId;
    stEvent.ulError    = ulRslt;

    return TAF_XSMS_SmsEventCallBack(TAF_XSMS_APP_MSG_TYPE_SEND_CNF, &stEvent);
}
VOS_UINT32 TAF_XSMS_SetAPFullCnf(VOS_UINT16 usClientId, VOS_UINT8 ucOpId, VOS_UINT32 ulRslt)
{
    TAF_XSMS_APP_AT_EVENT_INFO_STRU     stEvent;

    PS_MEM_SET(&stEvent, 0, sizeof(TAF_XSMS_APP_AT_EVENT_INFO_STRU));

    /* �����Ϣ�ṹ */
    stEvent.usClientId = usClientId;
    stEvent.ucOpId     = ucOpId;
    stEvent.ulError    = ulRslt;

    return TAF_XSMS_SmsEventCallBack(TAF_XSMS_APP_MSG_TYPE_UIM_MEM_FULL_CNF, &stEvent);
}


/*****************************************************************************
 �� �� ��  : TAF_XSMS_MsgWriteCnf
 ��������  : 1XSMS��AT�Ķ���д�����ظ�����
 �������  : usClientId:Client ID
             ucOpId:Op Id
             ulRslt:д������Ľ��
             ulIndex:д��ļ�¼������
 �������  : ��
 �� �� ֵ  : VOS_OK -- ���ͳɹ�
             VOS_ERR -- ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��1��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_MsgWriteCnf(VOS_UINT16 usClientId,  VOS_UINT8 ucOpId, VOS_UINT32 ulRslt, VOS_UINT32 ulIndex)
{
    TAF_XSMS_APP_AT_EVENT_INFO_STRU     stEvent;
    TAF_XSMS_CTRL_INFO_STRU            *pstAddr;

    pstAddr = TAF_XSMS_GetReqCtrlInfoAddr();

    /* ����API�ӿڣ����ȫ�ֱ��� */
    PS_MEM_SET(pstAddr, 0, sizeof(TAF_XSMS_CTRL_INFO_STRU));

    /* �����Ϣ�ṹ */
    stEvent.usClientId = usClientId;
    stEvent.ucOpId     = ucOpId;
    stEvent.ulError    = ulRslt;

    stEvent.XSmsEvent.stWriteCnf.ulIndex = ulIndex;

    return TAF_XSMS_SmsEventCallBack(TAF_XSMS_APP_MSG_TYPE_WRITE_CNF, &stEvent);
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_MsgDeleteCnf
 ��������  : 1XSMS��AT�Ķ���ɾ������ظ�����
 �������  : usClientId:Client ID
             ucOpId:Op Id
             ulRslt:ɾ�������Ľ��
 �������  : ��
 �� �� ֵ  : VOS_OK -- ���ͳɹ�
             VOS_ERR -- ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��1��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_MsgDeleteCnf(VOS_UINT16 usClientId, VOS_UINT8 ucOpId, VOS_UINT32 ulRslt)
{
    TAF_XSMS_APP_AT_EVENT_INFO_STRU     stEvent;
    TAF_XSMS_CTRL_INFO_STRU            *pstAddr;

    pstAddr = TAF_XSMS_GetReqCtrlInfoAddr();

    /* ����API�ӿڣ����ȫ�ֱ��� */
    PS_MEM_SET(pstAddr, 0, sizeof(TAF_XSMS_CTRL_INFO_STRU));

    /* �����Ϣ�ṹ */
    stEvent.usClientId = usClientId;
    stEvent.ucOpId     = ucOpId;
    stEvent.ulError    = ulRslt;

    return TAF_XSMS_SmsEventCallBack(TAF_XSMS_APP_MSG_TYPE_DELETE_CNF, &stEvent);
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_MsgSubmitFailInd
 ��������  : 1XSMS��AT�Ķ��ŷ��ͳɹ�ָʾ�ϱ�����
 �������  : ulMr:MESSAGE ID
 �������  : ��
 �� �� ֵ  : VOS_OK -- ���ͳɹ�
             VOS_ERR -- ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��1��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_MsgSubmitSuccInd(VOS_UINT32 ulMr)
{
    TAF_XSMS_APP_AT_EVENT_INFO_STRU     stEvent;
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;

    pstMoRec = TAF_XSMS_MoGetRecAddr();
    if ((TAF_XSMS_STK_SEND_XSMS == pstMoRec->enOrigPid)
     && (VOS_FALSE == pstMoRec->usIsStkUserAck))
    {
        /* �oSTK�ϱ����ųɹ� */
        return TAF_XSMS_SendStkRsltInd(VOS_TRUE, 0);
    }
    else if ((VOS_TRUE == pstMoRec->usIsStkUserAck)
          || (TAF_XSMS_XPDS_SEND_XSMS == pstMoRec->enOrigPid) )
    {
        /* ���ڶ�USER ACK��Ϣ���ϱ� */
        return VOS_OK;
    }
    else
    {
        /* �����Ϣ�ṹ���㲥�ϱ� */
        stEvent.usClientId = MN_CLIENT_ALL;
        stEvent.ucOpId     = 0;
        stEvent.ulError    = VOS_OK;

        stEvent.XSmsEvent.stSndSuccInd.ulMr = ulMr;

        return TAF_XSMS_SmsEventCallBack(TAF_XSMS_APP_MSG_TYPE_SEND_SUCC_IND, &stEvent);
    }
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_MsgSubmitFailInd
 ��������  : 1XSMS��AT�Ķ��ŷ���ʧ��ָʾ�ϱ�����
 �������  : ulCourceCode:����ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_OK -- ���ͳɹ�
             VOS_ERR -- ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��1��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_MsgSubmitFailInd(VOS_UINT32 ulCourceCode)
{
    TAF_XSMS_APP_AT_EVENT_INFO_STRU     stEvent;
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    if ((TAF_XSMS_STK_SEND_XSMS == pstMoRec->enOrigPid)
    &&  (VOS_FALSE == pstMoRec->usIsStkUserAck))
    {
        /* �oSTK�ϱ����ŷ���ʧ�� */
        return TAF_XSMS_SendStkRsltInd(VOS_FALSE, ulCourceCode);
    }
    else if ((TAF_XSMS_STK_SEND_XSMS == pstMoRec->enOrigPid)
        &&   (VOS_TRUE == pstMoRec->usIsStkUserAck))
    {
        /* ���ڶ�USER ACK��Ϣ���ϱ� */
        return VOS_OK;
    }
    else if (TAF_XSMS_XPDS_SEND_XSMS == pstMoRec->enOrigPid)
    {
        /* ���ڶ�MTA��Ϣ���ϱ� */
        return VOS_OK;
    }
    else
    {
        /* �����Ϣ�ṹ���㲥�ϱ� */
        stEvent.usClientId = MN_CLIENT_ALL;
        stEvent.ucOpId     = 0;
        stEvent.ulError    = VOS_OK;

        stEvent.XSmsEvent.stSndFailInd.ulCourseCode = ulCourceCode;

        return TAF_XSMS_SmsEventCallBack(TAF_XSMS_APP_MSG_TYPE_SEND_FAIL_IND, &stEvent);
    }
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_MsgUimFullInd
 ��������  : 1XSMS��AT��UIM����ָʾ�ϱ�����
 �������  : pstDeliveryMsg:�յ��Ķ��Ż����״̬�ϱ�
 �������  : ��
 �� �� ֵ  : VOS_OK -- ���ͳɹ�
             VOS_ERR -- ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��1��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_MsgDeliveryInd(TAF_XSMS_MESSAGE_STRU *pstDeliveryMsg)
{
    TAF_XSMS_APP_AT_EVENT_INFO_STRU     stEvent;

    /* �����Ϣ�ṹ���㲥�ϱ� */
    stEvent.usClientId = MN_CLIENT_ALL;
    stEvent.ucOpId     = 0;
    stEvent.ulError    = VOS_OK;

    TAF_XSMS_TranslatePlusToNum(&pstDeliveryMsg->stAddr);

    PS_MEM_CPY(&stEvent.XSmsEvent.stRcvInd.stRcvMsg, pstDeliveryMsg, sizeof(TAF_XSMS_MESSAGE_STRU));

    return TAF_XSMS_SmsEventCallBack(TAF_XSMS_APP_MSG_TYPE_RCV_IND, &stEvent);
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_MsgUimFullInd
 ��������  : 1XSMS��AT��UIM����ָʾ�ϱ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_OK -- ���ͳɹ�
             VOS_ERR -- ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��1��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_MsgUimFullInd(VOS_VOID)
{
    TAF_XSMS_APP_AT_EVENT_INFO_STRU     stEvent;

    /* �����Ϣ�ṹ���㲥�ϱ� */
    stEvent.usClientId = MN_CLIENT_ALL;
    stEvent.ucOpId     = 0;
    stEvent.ulError    = VOS_OK;

    return TAF_XSMS_SmsEventCallBack(TAF_XSMS_APP_MSG_TYPE_UIM_FULL_IND, &stEvent);
}


/*****************************************************************************
 �� �� ��  : TAF_XSMS_MsgEventCallBack
 ��������  : 1XSMS��AT����Ϣ���ͺ���
 �������  : enEventType:�¼�����
 �������  : pstEvent:�¼�����
 �� �� ֵ  : VOS_OK -- ���ͳɹ�
             VOS_ERR -- ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��1��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_SmsEventCallBack(
    TAF_XSMS_APP_MSG_TYPE_ENUM_UINT32   enEventType,
    TAF_XSMS_APP_AT_EVENT_INFO_STRU    *pstEvent)
{
    TAF_XSMS_APP_AT_CNF_STRU          *pstMsg;

    pstMsg = (TAF_XSMS_APP_AT_CNF_STRU *)VOS_AllocMsg(UEPS_PID_XSMS,
                                                       sizeof(TAF_XSMS_APP_AT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_ERR;
    }

    pstEvent->usClientId = MN_GetRealClientId(pstEvent->usClientId, UEPS_PID_XSMS);

    PS_MEM_CPY((VOS_VOID*)&pstMsg->stXsmsAtEvent, pstEvent, sizeof(TAF_XSMS_APP_AT_EVENT_INFO_STRU));

    pstMsg->enEventType   = enEventType;
    pstMsg->ulReceiverPid = WUEPS_PID_AT;

    return VOS_SendMsg(UEPS_PID_XSMS, pstMsg);
}



VOS_UINT32 TAF_XSMS_SendStkRsltInd(
    VOS_UINT32                          ulSendRslt,
    VOS_UINT32                          ulCauseCode
)
{
    XSMS_STK_SEND_SMS_RSLT_IND_STRU    *pstSendRslt;

    pstSendRslt = (XSMS_STK_SEND_SMS_RSLT_IND_STRU*)VOS_AllocMsg(UEPS_PID_XSMS,
                                 sizeof(XSMS_STK_SEND_SMS_RSLT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSendRslt->ulReceiverPid = MAPS_STK_PID;

    pstSendRslt->enMsgId       = ID_XSMS_STK_SEND_SMS_RSLT_IND;
    pstSendRslt->ulIsUserAck   = VOS_FALSE;
    pstSendRslt->ulSendSucc    = ulSendRslt;
    pstSendRslt->ulCauseCode   = ulCauseCode;

    return VOS_SendMsg(UEPS_PID_XSMS, pstSendRslt);
}



VOS_VOID TAF_XSMS_StkMsgSubmitCnf(VOS_UINT32 ulRet)
{
    XSMS_STK_SEND_SMS_CNF_STRU    *pstSendCnf;

    pstSendCnf = (XSMS_STK_SEND_SMS_CNF_STRU*)VOS_AllocMsg(UEPS_PID_XSMS,
                                 sizeof(XSMS_STK_SEND_SMS_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSendCnf->ulReceiverPid = MAPS_STK_PID;

    pstSendCnf->enMsgId       = ID_XSMS_STK_SEND_SMS_CNF;
    pstSendCnf->ulIsUserAck   = VOS_FALSE;
    pstSendCnf->ulRet         = ulRet;

    VOS_SendMsg(UEPS_PID_XSMS, pstSendCnf);

}


VOS_VOID TAF_XSMS_SendStkCATPTMsg(
    VOS_UINT32                          ulLen,
    VOS_UINT8                          *pucTpdu,
    TAF_XSMS_MESSAGE_STRU              *pst1XSms
)
{
    XSMS_STK_RCV_SMS_IND_STRU          *pstCatptMsg;

    pstCatptMsg = (XSMS_STK_RCV_SMS_IND_STRU*)VOS_AllocMsg(UEPS_PID_XSMS,
                                 sizeof(XSMS_STK_RCV_SMS_IND_STRU) + ulLen - 4 - VOS_MSG_HEAD_LENGTH);

    pstCatptMsg->ulReceiverPid = MAPS_STK_PID;

    pstCatptMsg->enMsgId       = ID_XSMS_STK_RCV_SMS_IND;
    pstCatptMsg->ulTpduLen     = ulLen;

    PS_MEM_CPY(pstCatptMsg->aucTpduData , pucTpdu, ulLen);
    PS_MEM_CPY(&pstCatptMsg->st1XSms, pst1XSms, sizeof(TAF_XSMS_MESSAGE_STRU));

    VOS_SendMsg(UEPS_PID_XSMS, pstCatptMsg);

}


VOS_VOID TAF_XSMS_SendXpdsGpsSms(
    TAF_XSMS_ADDR_STRU                 *pstXsmsAddr,
    VOS_UINT32                          ulLen,
    VOS_UINT8                          *pucData
)
{
    TAF_XSMS_XPDS_REV_IND_STRU         *pstRcvInd;
    /* 4�ǽṹ�����еĳ��� */
    pstRcvInd    = (TAF_XSMS_XPDS_REV_IND_STRU*)VOS_AllocMsg(UEPS_PID_XSMS,
                      sizeof(TAF_XSMS_XPDS_REV_IND_STRU) + ulLen - 4 - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstRcvInd)
    {
        return;
    }

    pstRcvInd->ulReceiverPid = UEPS_PID_XPDS;

    pstRcvInd->enMsgName     = ID_XSMS_XPDS_RCV_IND;
    pstRcvInd->usDataLen     = (VOS_UINT16)ulLen;

    PS_MEM_CPY(pstRcvInd->aucData, pucData, ulLen);
    PS_MEM_CPY(&pstRcvInd->stXsmsAddr, pstXsmsAddr, sizeof(TAF_XSMS_ADDR_STRU));

    (VOS_VOID)VOS_SendMsg(UEPS_PID_XSMS, pstRcvInd);

    return;

}



/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



