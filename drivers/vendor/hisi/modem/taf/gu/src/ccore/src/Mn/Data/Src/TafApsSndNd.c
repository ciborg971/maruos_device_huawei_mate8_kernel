
/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafApsSndNd.c��
  �� �� ��   : ����
  ��    ��   : A00165503
  ��������   : 2011��12��31��
  ����޸�   :
  ��������   : MMC����ND Client����Ϣ�Ĵ���
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2011��12��31��
    ��    ��   : A00165503
    �޸�����   : �����ļ�

******************************************************************************/
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "PsLib.h"

#include "PsCommonDef.h"
#include "PsTypeDef.h"

#include "TafLog.h"
#include "Taf_Aps.h"

#include "ApsNdInterface.h"
#include "TafApsSndNd.h"



#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_SND_ND_C

/******************************************************************************
   2 �ⲿ������������
******************************************************************************/


/******************************************************************************
   3 ˽�ж���
******************************************************************************/


/******************************************************************************
   4 ȫ�ֱ�������
*****************************************************************************/


/******************************************************************************
   5 ����ʵ��
******************************************************************************/

/*****************************************************************************
 �� �� ��  : TAF_APS_SndNdPdpActInd
 ��������  : ��ND Client����ID_APS_NDCLIENT_PDP_ACT_IND��Ϣ
 �������  : ucRabId                    - RAB ID
             pucIpv6Addr                - IPv6��ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��31��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndNdPdpActInd(
    VOS_UINT8                           ucRabId,
    VOS_UINT8                          *pucIpv6Addr
)
{
    APS_NDCLIENT_PDP_ACT_IND           *pstNdPdpActInd;

    /* ������Ϣ */
    pstNdPdpActInd = (APS_NDCLIENT_PDP_ACT_IND*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_TAF,
                            sizeof(APS_NDCLIENT_PDP_ACT_IND));
    if (VOS_NULL_PTR == pstNdPdpActInd)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndNdPdpActInd: Memory alloc failed.");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstNdPdpActInd + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(APS_NDCLIENT_PDP_ACT_IND) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstNdPdpActInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstNdPdpActInd->ulReceiverPid   = UEPS_PID_NDCLIENT;
    pstNdPdpActInd->ulMsgId         = ID_APS_NDCLIENT_PDP_ACT_IND;

    /* ��д��Ϣ���� */
    pstNdPdpActInd->ucRabId         = ucRabId;
    PS_MEM_CPY(pstNdPdpActInd->aucIpv6InterfacId,
               pucIpv6Addr + (TAF_IPV6_ADDR_LEN - APS_NDCLIENT_IPV6_IFID_LENGTH),
               APS_NDCLIENT_IPV6_IFID_LENGTH);

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstNdPdpActInd))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndNdPdpActInd: Send message failed.");
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndNdPdpDeactInd
 ��������  : ��ND Client����ID_APS_NDCLIENT_PDP_DEACT_IND��Ϣ
 �������  : ucRabId                    - RAB ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��31��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndNdPdpDeactInd(
    VOS_UINT8                           ucRabId
)
{
    APS_NDCLIENT_PDP_DEACT_IND         *pstNdPdpDeactInd;

    /* ������Ϣ */
    pstNdPdpDeactInd = (APS_NDCLIENT_PDP_DEACT_IND*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_TAF,
                            sizeof(APS_NDCLIENT_PDP_DEACT_IND));
    if (VOS_NULL_PTR == pstNdPdpDeactInd)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndNdPdpDeactInd: Memory alloc failed.");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstNdPdpDeactInd + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(APS_NDCLIENT_PDP_DEACT_IND) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstNdPdpDeactInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstNdPdpDeactInd->ulReceiverPid   = UEPS_PID_NDCLIENT;
    pstNdPdpDeactInd->ulMsgId         = ID_APS_NDCLIENT_PDP_DEACT_IND;

    /* ��д��Ϣ���� */
    pstNdPdpDeactInd->ucRabId         = ucRabId;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstNdPdpDeactInd))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndNdPdpDeactInd: Send message failed.");
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndNdRelInd
 ��������  : ��ND Client����ID_APS_NDCLIENT_REL_IND��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��31��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndNdRelInd(VOS_VOID)
{
    APS_NDCLIENT_REL_IND_STRU          *pstNdRelInd;

    /* ������Ϣ */
    pstNdRelInd = (APS_NDCLIENT_REL_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_TAF,
                            sizeof(APS_NDCLIENT_REL_IND_STRU));
    if (VOS_NULL_PTR == pstNdRelInd)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndNdRelInd: Memory alloc failed.");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstNdRelInd + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(APS_NDCLIENT_REL_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstNdRelInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstNdRelInd->ulReceiverPid   = UEPS_PID_NDCLIENT;
    pstNdRelInd->ulMsgId         = ID_APS_NDCLIENT_REL_IND;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstNdRelInd))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndNdRelInd: Send message failed.");
        return;
    }

    return;
}

/*lint +e958*/



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



