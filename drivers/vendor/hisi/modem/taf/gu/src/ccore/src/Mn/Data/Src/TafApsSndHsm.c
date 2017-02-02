/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafApsSndHsm.c
  �� �� ��   : ����
  ��    ��   : y00314741
  ��������   : 2015��02��04��
  ����޸�   :
  ��������   : TAF APSģ�鷢����Ϣ��HSM�ĺ���ʵ���ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��02��04��
    ��    ��   : y00314741
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#include "PsCommonDef.h"
#include "PsTypeDef.h"
#include "TafLog.h"
#include "Taf_Aps.h"
#include "MnApsComm.h"
#include "TafApsSndHsm.h"

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "hsm_aps_pif.h"
#include "TafApsProcEpdszid.h"
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_SND_HSM_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
 �� �� ��  : TAF_APS_SndHsmOrigReq
 ��������  : ����ID_APS_HSM_ORIG_REQ��Ϣ
 �������  : VOS_UINT8                    ucPdpId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndHsmOrigReq(
    VOS_UINT8                           ucPdpId
)
{
    APS_HSM_ORIG_REQ_STRU              *pstOrigReq   = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity = VOS_NULL_PTR;

    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    pstOrigReq = (APS_HSM_ORIG_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_HSM_ORIG_REQ_STRU));

    if (VOS_NULL_PTR == pstOrigReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndHsmOrigDataCallReq: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstOrigReq + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_HSM_ORIG_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д���� */
    pstOrigReq->ulReceiverPid           = UEPS_PID_HSM;
    pstOrigReq->enMsgId                 = ID_APS_HSM_ORIG_REQ;
    pstOrigReq->usOpId                  = 0;
    pstOrigReq->ucCallId                = pstPdpEntity->stCdataInfo.ucCallId;

    PS_SEND_MSG(WUEPS_PID_TAF, pstOrigReq);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndHsmDiscReq
 ��������  : ����ID_APS_HSM_DISC_REQ��Ϣ
 �������  : VOS_UINT8                    ucPdpId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndHsmDiscReq(
    VOS_UINT8                           ucPdpId
)
{
    APS_HSM_DISC_REQ_STRU              *pstDiscReq   = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity = VOS_NULL_PTR;

    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    pstDiscReq = (APS_HSM_DISC_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_HSM_DISC_REQ_STRU));

    if (VOS_NULL_PTR == pstDiscReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndHsmDiscReq: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstDiscReq + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_HSM_DISC_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д���� */
    pstDiscReq->ulReceiverPid           = UEPS_PID_HSM;
    pstDiscReq->enMsgId                 = ID_APS_HSM_DISC_REQ;
    pstDiscReq->usOpId                  = 0;
    pstDiscReq->ucCallId                = pstPdpEntity->stCdataInfo.ucCallId;

    PS_SEND_MSG(WUEPS_PID_TAF, pstDiscReq);

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_SndHsmConnectRsp
 ��������  : ����ID_APS_HSM_CONNECT_RSP��Ϣ
 �������  : VOS_UINT8                           ucPdpId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndHsmConnectRsp(
    VOS_UINT8                           ucCallId
)
{
    APS_HSM_CONNECT_RSP_STRU           *pstConnectRsp = VOS_NULL_PTR;

    pstConnectRsp = (APS_HSM_CONNECT_RSP_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_HSM_CONNECT_RSP_STRU));

    if (VOS_NULL_PTR == pstConnectRsp)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndHsmConnectRsp: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstConnectRsp + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_HSM_CONNECT_RSP_STRU) - VOS_MSG_HEAD_LENGTH);

    pstConnectRsp->ulReceiverPid        = UEPS_PID_HSM;
    pstConnectRsp->enMsgId              = ID_APS_HSM_CONNECT_RSP;
    pstConnectRsp->usOpId               = 0;
    pstConnectRsp->ucCallId             = ucCallId;

    PS_SEND_MSG(WUEPS_PID_TAF, pstConnectRsp);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndHs1XHrpdHandOffReq
 ��������  : ����ID_APS_HSM_1X_TO_HRPD_HANDOFF_REQ��Ϣ
 �������  : VOS_UINT8                    ucPdpId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndHsm1XToHrpdHandOffReq(
    VOS_UINT8                           ucPdpId
)
{
    APS_HSM_1X_TO_HRPD_HANDOFF_REQ_STRU     *pstHandOffReq = VOS_NULL_PTR;
    TAF_APS_CDATA_EPDSZID_CTX_STRU          *pstEpdszidCtx = VOS_NULL_PTR;

    pstEpdszidCtx = TAF_APS_GetEpdszidCtx();

    pstHandOffReq = (APS_HSM_1X_TO_HRPD_HANDOFF_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_HSM_1X_TO_HRPD_HANDOFF_REQ_STRU));

    if (VOS_NULL_PTR == pstHandOffReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndHsm1XToHrpdHandOffReq: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstHandOffReq + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_HSM_1X_TO_HRPD_HANDOFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д���� */
    pstHandOffReq->ulReceiverPid           = UEPS_PID_HSM;
    pstHandOffReq->enMsgId                 = ID_APS_HSM_1X_TO_HRPD_HANDOFF_REQ;
    pstHandOffReq->usOpId                  = 0;
    pstHandOffReq->usSid                   = pstEpdszidCtx->stCurrEpdszid.usSid;
    pstHandOffReq->usNid                   = pstEpdszidCtx->stCurrEpdszid.usNid;
    pstHandOffReq->ucPktZoneId             = pstEpdszidCtx->stCurrEpdszid.ucPzid;

    PS_SEND_MSG(WUEPS_PID_TAF, pstHandOffReq);

    return;
}

#endif


/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
