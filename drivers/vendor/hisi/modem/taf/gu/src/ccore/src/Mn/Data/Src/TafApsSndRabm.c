
/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafApsSndRabm.c��
  �� �� ��   : ����
  ��    ��   : S62952
  ��������   : 2011��12��14��
  ����޸�   :
  ��������   : ���͸�RABM����Ϣ���ͺ���
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2011��12��14��
    ��    ��   : S62952
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "Taf_Aps.h"
#include "TafLog.h"
#include "TafApsSndRabm.h"



#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_SNDRABM_C

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
 �� �� ��  : TAF_APS_SndRabmSetTransModeMsg
 ��������  : ����RABM_APS_SET_TRANSMODE_MSG_TYPE��Ϣ��RABM
 �������  : ucNsapi                    - NSAPI
             enTransMode                - ����ģʽ(ABM/ADM)
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��27��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndRabmSetTransModeMsg(
    VOS_UINT8                           ucNsapi,
    RABM_TRANS_MODE_ENUM                enTransMode
)
{
    RABM_APS_SET_TRANSMODE_MSG         *pstRabmSetTransModeMsg;

    /* ������Ϣ */
    pstRabmSetTransModeMsg = (RABM_APS_SET_TRANSMODE_MSG*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                        WUEPS_PID_TAF,
                                        sizeof(RABM_APS_SET_TRANSMODE_MSG));
    if (VOS_NULL_PTR == pstRabmSetTransModeMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_APS_SndRabmSetTransMode: Memory alloc failed.");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstRabmSetTransModeMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(RABM_APS_SET_TRANSMODE_MSG) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstRabmSetTransModeMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstRabmSetTransModeMsg->ulReceiverPid   = WUEPS_PID_RABM;
    pstRabmSetTransModeMsg->usMsgType       = RABM_APS_SET_TRANSMODE_MSG_TYPE;

    /* ��д��Ϣ���� */
    pstRabmSetTransModeMsg->RabmApsSetTransMode.ucNsapi   = ucNsapi;
    pstRabmSetTransModeMsg->RabmApsSetTransMode.TransMode = enTransMode;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstRabmSetTransModeMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "MN_APS_PackEsmPdpOptModify: Send message failed.");
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





