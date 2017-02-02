
#include "Tcinclude.h"
#include "psprimitive.h"
#include "pscfg.h"

#include "NasComm.h"
#include "NasMmlCtx.h"

#include "NasUtranCtrlInterface.h"
#include "NasWphyInterface.h"
#include "NasMmcSndMscc.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TC_C

TC_GLOBAL_CTRL_STRU               g_TcInfo;                                             /* TCȫ�ֿ�����Ϣ                           */


/***********************************************************************
 *  MODULE   : Tc_SndMmTestReq
 *  FUNCTION : ��MM����TEST��Ϣ
 *  INPUT    : VOS_UINT8 ucMode      ģʽ��Ϣ
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   ��־��      2004.05.24   �¹�����
 ************************************************************************/
VOS_VOID Tc_SndMmTestReq(VOS_UINT8 ucMode)
{
    TCMM_TEST_REQ_STRU         *pTestReq= VOS_NULL_PTR;                                         /* ����ԭ������ָ��                         */

    pTestReq = (TCMM_TEST_REQ_STRU*)PS_ALLOC_MSG(WUEPS_PID_TC, sizeof(TCMM_TEST_REQ_STRU)
                                                               - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pTestReq )
    {                                                                                   /* �ڴ�����ʧ��                             */
        return;                                                                         /* ����                                     */
    }

    pTestReq->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pTestReq->MsgHeader.ulReceiverPid = WUEPS_PID_MM;
    pTestReq->MsgHeader.ulMsgName        = TCMM_TEST_REQ;                               /* ��Ϣ����                                 */

    pTestReq->ulMode = ucMode;                                                          /* ����ģʽ                                 */

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pTestReq))
    {
        NAS_WARNING_LOG(WUEPS_PID_TC, "Tc_SndMmTestReq():WARNING:SEND MSG FIAL");
    }

    return;
}

/***********************************************************************
 *  MODULE   : Tc_SndGmmTestReq
 *  FUNCTION : ��GMM����TEST��Ϣ
 *  INPUT    : VOS_UINT8 ucMode      ģʽ��Ϣ
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   ��־��      2004.05.24   �¹�����
 ************************************************************************/
VOS_VOID Tc_SndGmmTestReq(VOS_UINT8 ucMode)
{
    TCGMM_TEST_REQ_STRU         *pTestReq= VOS_NULL_PTR;                                        /* ����ԭ������ָ��                         */

    pTestReq = (TCGMM_TEST_REQ_STRU*)PS_ALLOC_MSG(WUEPS_PID_TC, sizeof(TCGMM_TEST_REQ_STRU)
                                                               - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pTestReq )
    {                                                                                   /* �ڴ�����ʧ��                             */
        return;                                                                         /* ����                                     */
    }

    pTestReq->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pTestReq->MsgHeader.ulReceiverPid = WUEPS_PID_GMM;
    pTestReq->MsgHeader.ulMsgName        = TCGMM_TEST_REQ;                              /* ��Ϣ����                                 */

    pTestReq->ulMode = ucMode;                                                          /* ����ģʽ                                 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pTestReq))
    {
        NAS_WARNING_LOG(WUEPS_PID_TC, "Tc_SndGmmTestReq():WARNING:SEND MSG FIAL");
    }

    return;
}

/***********************************************************************
 *  MODULE   : Tc_SndSmTestReq
 *  FUNCTION : ��SM����TEST��Ϣ
 *  INPUT    : VOS_UINT8 ucMode      ģʽ��Ϣ
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   ��־��      2004.05.24   �¹�����
      2.  ��³��   2005-04-25   for A32D01738
 ************************************************************************/
VOS_VOID Tc_SndSmTestReq(VOS_UINT8 ucMode)
{
    TCSM_TEST_REQ_STRU         *pTestReq= VOS_NULL_PTR;                                         /* ����ԭ������ָ��                         */

    pTestReq = (TCSM_TEST_REQ_STRU*)PS_ALLOC_MSG(WUEPS_PID_TC, sizeof(TCSM_TEST_REQ_STRU)
                                                               - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pTestReq )
    {                                                                                   /* �ڴ�����ʧ��                             */
        return;                                                                         /* ����                                     */
    }

    pTestReq->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pTestReq->MsgHeader.ulReceiverPid = WUEPS_PID_SM;
    pTestReq->MsgHeader.ulMsgName        = TCSM_TEST_REQ;                               /* ��Ϣ����                                 */

    pTestReq->ulMode = ucMode;                                                          /* ����ģʽ                                 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pTestReq))
    {
        NAS_WARNING_LOG(WUEPS_PID_TC, "Tc_SndSmTestReq():WARNING:SEND MSG FIAL");
    }
    return;
}

/***********************************************************************
 *  MODULE   : Tc_SndSmsTestReq
 *  FUNCTION : ��SMS����TEST��Ϣ
 *  INPUT    : VOS_UINT8 ucMode      ģʽ��Ϣ
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   ��־��      2004.05.24   �¹�����
      2.  ��³��   2005-04-25   for A32D01738
 ************************************************************************/
VOS_VOID Tc_SndSmsTestReq(VOS_UINT8 ucMode)
{
    TCSMS_TEST_REQ_STRU         *pTestReq= VOS_NULL_PTR;                                        /* ����ԭ������ָ��                         */

    pTestReq = (TCSMS_TEST_REQ_STRU*)PS_ALLOC_MSG(WUEPS_PID_TC, sizeof(TCSMS_TEST_REQ_STRU)
                                                               - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pTestReq )
    {                                                                                   /* �ڴ�����ʧ��                             */
        return;                                                                         /* ����                                     */
    }

    pTestReq->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pTestReq->MsgHeader.ulReceiverPid = WUEPS_PID_SMS;
    pTestReq->MsgHeader.ulMsgName        = TCSMS_TEST_REQ;                              /* ��Ϣ����                                 */

    pTestReq->ulMode = ucMode;                                                          /* ����ģʽ                                 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pTestReq))
    {
        NAS_WARNING_LOG(WUEPS_PID_TC, "Tc_SndSmsTestReq():WARNING:SEND MSG FIAL");
    }
    return;
}

/***********************************************************************
 *  MODULE   : Tc_SndSsTestReq
 *  FUNCTION : ��Ss����TEST��Ϣ
 *  INPUT    : VOS_UINT8 ucMode      ģʽ��Ϣ
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   ��־��      2004.05.24   �¹�����
 ************************************************************************/
VOS_VOID Tc_SndSsTestReq(VOS_UINT8 ucMode)
{
    TCSS_TEST_REQ_STRU         *pTestReq= VOS_NULL_PTR;                                         /* ����ԭ������ָ��                         */

    pTestReq = (TCSS_TEST_REQ_STRU*)PS_ALLOC_MSG(WUEPS_PID_TC, sizeof(TCSS_TEST_REQ_STRU)
                                                               - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pTestReq )
    {                                                                                   /* �ڴ�����ʧ��                             */
        return;                                                                         /* ����                                     */
    }

    pTestReq->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pTestReq->MsgHeader.ulReceiverPid = WUEPS_PID_SS;
    pTestReq->MsgHeader.ulMsgName        = TCSS_TEST_REQ;                               /* ��Ϣ����                                 */

    pTestReq->ulMode = ucMode;                                                          /* ����ģʽ                                 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pTestReq))
    {
        NAS_WARNING_LOG(WUEPS_PID_TC, "Tc_SndSsTestReq():WARNING:SEND MSG FIAL");
    }
    return;
}

/***********************************************************************
 *  MODULE   : Tc_SndCcTestReq
 *  FUNCTION : ��Cc����TEST��Ϣ
 *  INPUT    : VOS_UINT8 ucMode      ģʽ��Ϣ
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   ��־��      2004.05.24   �¹�����
 ************************************************************************/
VOS_VOID Tc_SndCcTestReq(VOS_UINT8 ucMode)
{
    TCCC_TEST_REQ_STRU         *pTestReq= VOS_NULL_PTR;                                         /* ����ԭ������ָ��                         */

    pTestReq = (TCCC_TEST_REQ_STRU*)PS_ALLOC_MSG(WUEPS_PID_TC, sizeof(TCCC_TEST_REQ_STRU)
                                                               - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pTestReq )
    {                                                                                   /* �ڴ�����ʧ��                             */
        return;                                                                         /* ����                                     */
    }

    pTestReq->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pTestReq->MsgHeader.ulReceiverPid = WUEPS_PID_CC;
    pTestReq->MsgHeader.ulMsgName        = TCCC_TEST_REQ;                               /* ��Ϣ����                                 */

    pTestReq->ulMode = ucMode;                                                          /* ����ģʽ                                 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pTestReq))
    {
        NAS_WARNING_LOG(WUEPS_PID_TC, "Tc_SndCcTestReq():WARNING:SEND MSG FIAL");
    }
    return;
}

/***********************************************************************
 *  MODULE   : Tc_SndRabmTestReq
 *  FUNCTION : ��RABM����TEST��Ϣ
 *  INPUT    : VOS_UINT8 ucMode      ģʽ��Ϣ
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   ��־��      2004.05.24   �¹�����
 ************************************************************************/
VOS_VOID Tc_SndRabmTestReq(VOS_UINT8 ucMode)
{
    TCRABM_TEST_REQ_STRU         *pTestReq= VOS_NULL_PTR;                                       /* ����ԭ������ָ��                         */

    pTestReq = (TCRABM_TEST_REQ_STRU*)PS_ALLOC_MSG(WUEPS_PID_TC, sizeof(TCRABM_TEST_REQ_STRU)
                                                               - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pTestReq )
    {                                                                                   /* �ڴ�����ʧ��                             */
        return;                                                                         /* ����                                     */
    }

    pTestReq->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pTestReq->MsgHeader.ulReceiverPid = WUEPS_PID_RABM;
    pTestReq->MsgHeader.ulMsgName        = TCRABM_TEST_REQ;                             /* ��Ϣ����                                 */

    pTestReq->ulMode = ucMode;                                                          /* ����ģʽ                                 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pTestReq))
    {
        NAS_WARNING_LOG(WUEPS_PID_TC, "Tc_SndRabmTestReq():WARNING:SEND MSG FIAL");
    }
    return;
}
VOS_VOID Tc_SndRabmTestLoopReq(VOS_UINT8 ucMode)
{
    VOS_UINT8                       k;                                                      /* ����ѭ������                             */
    TCRABM_TEST_LOOP_REQ_STRU   *pTestReq= VOS_NULL_PTR;                                        /* ����ԭ������ָ��                         */

    pTestReq = (TCRABM_TEST_LOOP_REQ_STRU*)PS_ALLOC_MSG(
                WUEPS_PID_TC, sizeof(TCRABM_TEST_LOOP_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pTestReq )
    {                                                                                   /* �ڴ�����ʧ��                             */
        return;                                                                         /* ����                                     */
    }



    PS_MEM_SET((VOS_INT8*)pTestReq + VOS_MSG_HEAD_LENGTH,0,
                     sizeof(TCRABM_TEST_LOOP_REQ_STRU) - VOS_MSG_HEAD_LENGTH);



    pTestReq->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pTestReq->MsgHeader.ulReceiverPid = WUEPS_PID_RABM;
    pTestReq->MsgHeader.ulMsgName        = TCRABM_TEST_LOOP_REQ;                        /* ��Ϣ����                                 */

    pTestReq->ulMode = ucMode;                                                          /* ����ģʽ                                 */
    if(TC_LOOP_CLOSE == ucMode)
    {                                                                                   /* ���ģʽ�Ǳջ�                           */
        pTestReq->ulRBNum = g_TcInfo.TcModeInfo.ucLbNum;                                /* ֪ͨLBʵ��ĸ���                         */

        pTestReq->ucTestLoopMode = g_TcInfo.TcModeInfo.ucTcMode;

        for(k = 0;k < g_TcInfo.TcModeInfo.ucLbNum;k++)
        {                                                                               /* ����ÿ��LBʵ�����                       */
            pTestReq->aLBIdList[k].ulRBID
                = g_TcInfo.TcModeInfo.aLBList[k].ucRBID;                                /* ����LB��RB ID��Ϣ                        */
            pTestReq->aLBIdList[k].ulUpRlcSduSize
                = g_TcInfo.TcModeInfo.aLBList[k].usUpRlcSduSize;                        /* ����LB������RLC SIZE��Ϣ                 */
        }
    }

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pTestReq))
    {
        NAS_WARNING_LOG(WUEPS_PID_TC, "Tc_SndRabmTestLoopReq():WARNING:SEND MSG FIAL");
    }
    return;
}

/***********************************************************************
 *  MODULE   : Tc_SndDataReq
 *  FUNCTION : ��MM��GMM���ͻظ��������Ӧ��Ϣ��
 *  INPUT    : VOS_UINT8  ucMsgType    ��Ϣ����
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   ��־��      2004.05.25   �¹�����
 ************************************************************************/
VOS_VOID Tc_SndDataReq(VOS_UINT8 ucMsgType)
{
    TCMM_DATA_REQ_STRU          *pMmDataReq= VOS_NULL_PTR;                                      /* ����ԭ������ָ��                         */
    TCGMM_DATA_REQ_STRU         *pGmmDataReq= VOS_NULL_PTR;                                     /* ����ԭ������ָ��                         */

    if( TC_CN_DOMAIN_CS == g_TcInfo.ucCnDomain )
    {                                                                                   /* �ж���Ϣ����CN��CS��                     */
        pMmDataReq = (TCMM_DATA_REQ_STRU*)PS_ALLOC_MSG(
                      WUEPS_PID_TC, sizeof(TCMM_DATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
        if( VOS_NULL_PTR == pMmDataReq )
        {                                                                               /* �ڴ�����ʧ��                             */
            return;                                                                     /* ����                                     */
        }

        pMmDataReq->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
        pMmDataReq->MsgHeader.ulReceiverPid = WUEPS_PID_MM;
        pMmDataReq->MsgHeader.ulMsgName        = TCMM_DATA_REQ;                         /* ��Ϣ����                                 */


        pMmDataReq->SendTcMsg.ulTcMsgSize = TC_CMPMSG_SIZE;                             /* ������Ϣ����                             */
        pMmDataReq->SendTcMsg.aucTcMsg[0] = 0x0F;                                       /* ����PD                                   */
        pMmDataReq->SendTcMsg.aucTcMsg[1] = ucMsgType;                                  /* ������Ϣ����                             */

        g_TcInfo.ucMsgType = TC_MSG_INVALID;                                            /* ������ڴ������Ϣ                       */

        if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pMmDataReq))
        {
            NAS_WARNING_LOG(WUEPS_PID_TC, "Tc_SndGmmTestReq():WARNING:SEND MSG FIAL");
        }
    }
    else
    {                                                                                   /* �ж���Ϣ����CN��PS��                     */
        pGmmDataReq = (TCGMM_DATA_REQ_STRU*)PS_ALLOC_MSG(
                       WUEPS_PID_TC, sizeof(TCGMM_DATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
        if( VOS_NULL_PTR == pGmmDataReq )
        {                                                                               /* �ڴ�����ʧ��                             */
            return;                                                                     /* ����                                     */
        }

        pGmmDataReq->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
        pGmmDataReq->MsgHeader.ulReceiverPid = WUEPS_PID_GMM;
        pGmmDataReq->MsgHeader.ulMsgName        = TCGMM_DATA_REQ;                       /* ��Ϣ����                                 */

        pGmmDataReq->SendTcMsg.ulTcMsgSize = TC_CMPMSG_SIZE;                            /* ������Ϣ����                             */
        pGmmDataReq->SendTcMsg.aucTcMsg[0] = 0x0F;                                      /* ����PD                                   */
        pGmmDataReq->SendTcMsg.aucTcMsg[1] = ucMsgType;                                 /* ������Ϣ����                             */

        g_TcInfo.ucMsgType = TC_MSG_INVALID;                                            /* ������ڴ������Ϣ                       */

        if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pGmmDataReq))
        {
            NAS_WARNING_LOG(WUEPS_PID_TC, "Tc_SndGmmTestReq():WARNING:SEND MSG FIAL");
        }
    }
    return;
}



VOS_VOID Tc_SndRrcfTestControlMsg(VOS_UINT32 ulMode)
{
    TC_RRCF_TEST_CONTROL_MSG    *pTestControlMsg;
    VOS_UINT32                   ulLength;

    ulLength        = sizeof(TC_RRCF_TEST_CONTROL_MSG) - VOS_MSG_HEAD_LENGTH;
    pTestControlMsg = (TC_RRCF_TEST_CONTROL_MSG *)PS_ALLOC_MSG( WUEPS_PID_RABM, ulLength );
    if ( VOS_NULL_PTR == pTestControlMsg )
    {
        /*��ӡ������Ϣ---������Ϣ��ʧ��:*/
        PS_NAS_LOG(WUEPS_PID_TC, 0, PS_LOG_LEVEL_ERROR, "Tc_SndRrcfTestControlMsg:ERROR:Allocates a message packet for TC_RRCF_TEST_CONTROL_MSG msg FAIL!");
        return;
    }

    /*��д��Ϣͷ:*/
    pTestControlMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pTestControlMsg->ulSenderPid     = WUEPS_PID_TC;
    pTestControlMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pTestControlMsg->ulReceiverPid   = WUEPS_PID_WRR;
    pTestControlMsg->ulLength        = ulLength;

    /*��д��Ϣ��:*/
    pTestControlMsg->ulMsgName       = TC_RRCF_TEST_CONTROL;
    pTestControlMsg->ulMode          = ulMode;

    /*���͸���Ϣ:*/
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_RABM, pTestControlMsg ) )
    {
        /*��ӡ������Ϣ---������Ϣʧ��:*/
        PS_NAS_LOG(WUEPS_PID_TC, 0, PS_LOG_LEVEL_WARNING, "Tc_SndRrcfTestControlMsg:WARNING:Send TC_RRCF_TEST_CONTROL_MSG Msg Fail!");
    }

    return;
}



/* Deleted by wx270776 for OM�ں�, 2015-7-16, begin */
//RFAģ�鱻OMɾ�����˶δ��벻�����ã���ɾ��
#if 0

VOS_VOID Tc_SndRfaTestControlMsg(VOS_UINT32 ulMsgName)
{
    TC_RFA_CONTROL_MSG          *pTestControlMsg;
    TC_RFA_ACT_REQ_MSG          *pTcRfaActReq;
    TC_RFA_DEACT_REQ_MSG        *pTcRfaDeactReq;
    VOS_UINT32                   ulLength;

    ulLength        = sizeof(TC_RFA_CONTROL_MSG) - VOS_MSG_HEAD_LENGTH;
    pTestControlMsg = (TC_RFA_CONTROL_MSG *)PS_ALLOC_MSG( WUEPS_PID_TC, ulLength );
    if ( VOS_NULL_PTR == pTestControlMsg )
    {
        /*��ӡ������Ϣ---������Ϣ��ʧ��:*/
        PS_NAS_LOG(WUEPS_PID_TC, 0, PS_LOG_LEVEL_ERROR, "Tc_SndRfaTestControlMsg:ERROR:Allocates a message packet for TC_RFA_CONTROL_MSG msg FAIL!");
        return;
    }

    if ( ID_TC_RFA_ACT_REQ == ulMsgName )
    {
        pTcRfaActReq = (TC_RFA_ACT_REQ_MSG *)pTestControlMsg;

        /*��д��Ϣͷ:*/
        pTcRfaActReq->ulSenderCpuId   = VOS_LOCAL_CPUID;
        pTcRfaActReq->ulSenderPid     = WUEPS_PID_TC;
        pTcRfaActReq->ulReceiverCpuId = VOS_LOCAL_CPUID;
        pTcRfaActReq->ulReceiverPid   = WUEPS_PID_RFA;
        pTcRfaActReq->ulLength        = ulLength;

        /*��д��Ϣ��:*/
        pTcRfaActReq->ulMsgName       = ulMsgName;
    }
    else
    {
        pTcRfaDeactReq = (TC_RFA_DEACT_REQ_MSG *)pTestControlMsg;

        /*��д��Ϣͷ:*/
        pTcRfaDeactReq->ulSenderCpuId   = VOS_LOCAL_CPUID;
        pTcRfaDeactReq->ulSenderPid     = WUEPS_PID_TC;
        pTcRfaDeactReq->ulReceiverCpuId = VOS_LOCAL_CPUID;
        pTcRfaDeactReq->ulReceiverPid   = WUEPS_PID_RFA;
        pTcRfaDeactReq->ulLength        = ulLength;

        /*��д��Ϣ��:*/
        pTcRfaDeactReq->ulMsgName       = ulMsgName;
    }

    /*���͸���Ϣ:*/
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_TC, pTestControlMsg ) )
    {
        /*��ӡ������Ϣ---������Ϣʧ��:*/
        PS_NAS_LOG(WUEPS_PID_TC, 0, PS_LOG_LEVEL_WARNING, "Tc_SndRfaTestControlMsg:WARNING:Send TC_RFA_CONTROL_MSG Msg Fail!");
    }

    return;
}
#endif
/* Deleted by wx270776 for OM�ں�, 2015-7-16, end */


VOS_VOID Tc_SndMtaResetStoredPosInfoInd(TC_UE_POS_TECH_ENUM_UINT8 enUePosTech)
{
    TCMTA_RESET_UE_POS_STORED_INFO_STRU         *pstResetInd;

    /* ������Ϣ�ڴ� */
    pstResetInd = (TCMTA_RESET_UE_POS_STORED_INFO_STRU*)PS_ALLOC_MSG(WUEPS_PID_TC, sizeof(TCMTA_RESET_UE_POS_STORED_INFO_STRU)
                                                               - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pstResetInd )
    {
        return;
    }

    pstResetInd->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstResetInd->stMsgHeader.ulReceiverPid   = UEPS_PID_MTA;
    pstResetInd->stMsgHeader.ulMsgName       = TCMTA_RESET_UE_POS_STORED_INFO_IND;

    pstResetInd->enUePosTech                 = enUePosTech;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pstResetInd))
    {
        /*��ӡ������Ϣ---������Ϣʧ��:*/
        PS_NAS_LOG(WUEPS_PID_TC, 0, PS_LOG_LEVEL_WARNING, "Tc_SndMtaResetStoredPosInfoInd:WARNING:Send TCMTA_RESET_UE_POS_STORED_INFO_IND Msg Fail!");
    }

    return;
}


/***********************************************************************
 *  MODULE   : Tc_RcvRabmTestCnf
 *  FUNCTION : �յ�RABM����Ӧ������RAB��Ϣ�����������Ӧ��Ϣ��
 *  INPUT    : VOS_VOID     *pMsg           �յ���RABMԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   ��־��      2004.05.24   �¹�����
      2.   ��־��      2004.11.23   �޸ķ���ȥ����cmp��Ϣ��ʱ�����ڷ���DataReq��ǰ
 ************************************************************************/
VOS_VOID Tc_RcvRabmTestCnf(VOS_VOID *pMsg)
{
    VOS_UINT8                     k;                                                        /* ����ѭ������                             */
    TCRABM_TEST_CNF_STRU      *pRabmTestCnf;                                            /* �յ�����Ϣ                               */

    VOS_UINT16                    usRbCnt;
    pRabmTestCnf = (TCRABM_TEST_CNF_STRU *) pMsg;
    g_TcInfo.TcRabInfo.ulRabCnt = pRabmTestCnf->ulRabCnt;                               /* ����Ŀǰ��RAB����                        */

    for(k = 0;k < (VOS_UINT8)g_TcInfo.TcRabInfo.ulRabCnt;k++)
    {                                                                                   /* �����Ѿ�������RAB����                    */
        g_TcInfo.TcRabInfo.aRabInfo[k].ulRabId      =
            pRabmTestCnf->aRabInfo[k].ulRabId;                                          /* ��ÿ��RAB ID���и�ֵ                     */
        g_TcInfo.TcRabInfo.aRabInfo[k].ulCnDomainId =
            pRabmTestCnf->aRabInfo[k].ulCnDomainId;                                     /* ��ÿ��RAB��������CN���и�ֵ              */
        /*g_TcInfo.TcRabInfo.aRabInfo[k].ulRbId       =     */
        /*    pRabmTestCnf->aRabInfo[k].ulRbId;             */                              /* ����RAB�е�RB ID                         */
        usRbCnt = (VOS_UINT16)g_TcInfo.TcRabInfo.aRabInfo[k].ulRbCnt;
        g_TcInfo.TcRabInfo.aRabInfo[k].aulRbId[usRbCnt] =
             pRabmTestCnf->aRabInfo[k].ulRbId;
        (g_TcInfo.TcRabInfo.aRabInfo[k].ulRbCnt)++;
    }
    if(TC_RRC_CONN_STATUS_PRESENT == g_TcInfo.ucRrcConnStatus)
    {                                                                                   /* �ж�RRC�����Ƿ����                      */
        switch(g_TcInfo.ucTcState)
        {                                                                               /* ���ݵ�ǰ��״̬���зַ�                   */
        case TC_OPEN_TEST_LOOP:
        case TC_CLOSE_TEST_LOOP:
/* 2004.11.23 del end */
            /*Tc_SndDataReq(TC_DEACT_RB_TEST_MODE_CMP);*/                                   /* ����ȥ������Ϣ                           */
            g_TcInfo.ucTcState = TC_NORMAL_MODE;                                        /* ״̬Ǩ��NORMAL                           */
/* 2004.11.23 del end */
            break;
        case TC_NORMAL_MODE:
            Tc_SndDataReq(TC_ACT_RB_TEST_MODE_CMP);                                     /* ���ͼ�����Ϣ                             */
            g_TcInfo.ucTcState = TC_OPEN_TEST_LOOP;                                     /* ״̬Ǩ��OPEN                             */
            break;
        default:
            break;
        }
    }
    else
    {                                                                                   /* RRC���Ӳ�����                            */
        g_TcInfo.ucTcState = TC_NORMAL_MODE;                                            /* ״̬Ǩ��NORMAL                           */
    }
    return;
}


VOS_VOID Tc_RcvRabmTestLoopCnf()
{
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8             enCurrUtranMode;

    switch(g_TcInfo.ucMsgType)
    {                                                                                   /* ���ݵ�ǰ��״̬���зַ�                   */
    case TC_CLOSE_UE_TEST_LOOP:
        Tc_SndDataReq(TC_CLOSE_UE_TEST_LOOP_CMP);                                       /* ���ͱջ���Ӧ��Ϣ                         */
        g_TcInfo.ucTcState = TC_CLOSE_TEST_LOOP;                                        /* ״̬Ǩ��CLOSE                            */

        enCurrUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();
        if ((VOS_FALSE == g_TcInfo.ucSndWphyCloseLoopNtfLable)
         && (NAS_UTRANCTRL_UTRAN_MODE_FDD == enCurrUtranMode))
        {
            /* ����DSP������W��֪ͨWPHY���뻷�� */
            NAS_TC_SndWphyCloseLoopNtf();
            g_TcInfo.ucSndWphyCloseLoopNtfLable = VOS_TRUE;
        }

        /* ����: WCDMA PS���ؽ��� */
        if (TC_CN_DOMAIN_PS == g_TcInfo.ucCnDomain)
        {
            NAS_MMC_SndMsccDataTranAttri(NAS_MSCC_PIF_DATATRAN_ATTRI_PDP_ACT);
        }
        break;
    case TC_OPEN_UE_TEST_LOOP:
        Tc_SndDataReq(TC_OPEN_UE_TEST_LOOP_CMP);                                        /* ���Ϳ�����Ӧ��Ϣ                         */
        g_TcInfo.ucTcState = TC_OPEN_TEST_LOOP;                                         /* ״̬Ǩ��OPEN                             */

        if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
        {
            /* ����DSP������W��֪ͨWPHY�˳����� */
            NAS_TC_SndWphyOpenLoopNtf();
            g_TcInfo.ucSndWphyCloseLoopNtfLable = VOS_FALSE;
        }

        /* ����: WCDMA PS�����ͷ� */
        if (TC_CN_DOMAIN_PS == g_TcInfo.ucCnDomain)
        {
            NAS_MMC_SndMsccDataTranAttri(NAS_MSCC_PIF_DATATRAN_ATTRI_PDP_DEACT);
        }
        break;
    default:
        break;
    }
    return;
}

/***********************************************************************
 *  MODULE   : Tc_RcvRabmRabInd
 *  FUNCTION : �յ�RABM�ϱ���RAB��Ϣ���洢���ж��Ƿ�������ʹ�õ�RAB��
 *  INPUT    : VOS_VOID     *pMsg           �յ���RABMԭ��ͷָ��
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
      1.   ��־��      2004.05.24   �¹�����
      1.   ��־��      2004.11.24   ʹ���˽ṹ�帳ֵ���,��Ϊ�Խṹ��ĳ�Աֱ�Ӹ�ֵ
 ************************************************************************/
VOS_VOID Tc_RcvRabmRabInd(VOS_VOID *pMsg)
{
    TCRABM_RAB_IND_STRU                 *pRabmInd;                                      /* �յ�����Ϣ                               */
    VOS_UINT8                               i,j;                                            /* ����ѭ������                             */
    VOS_UINT16     usRbCnt = 0,usRabCnt = 0,usRbLoop = 0;

    pRabmInd = (TCRABM_RAB_IND_STRU *) pMsg;                                            /* �ṹ��ָ������ת��                       */
    if( TC_RAB_SETUP == pRabmInd->ulRabChangeType )
    {                                                                                   /* �ж�RAB���޸�ģʽ                        */
        for( i = 0; i < (VOS_UINT8)g_TcInfo.TcRabInfo.ulRabCnt; i++ )
        {                                                                               /* �ڵ�ǰ�Ѿ��洢��rab��Ϣ�н�������        */
            if((g_TcInfo.TcRabInfo.aRabInfo[i].ulRabId
                          == pRabmInd->RabInfo.ulRabId)&&
               (g_TcInfo.TcRabInfo.aRabInfo[i].ulCnDomainId
                          == pRabmInd->RabInfo.ulCnDomainId))
            {                                                                           /* ���RAB ID�Ѿ�������                     */
                break;                                                                  /* ������                                   */
            }
        }
        if( i == (VOS_UINT8)g_TcInfo.TcRabInfo.ulRabCnt )
        {                                                                               /* ���û���ҵ���ͬ��rab                    */
            g_TcInfo.TcRabInfo.aRabInfo[(VOS_UINT8)g_TcInfo.TcRabInfo.ulRabCnt].ulRabId =
                pRabmInd->RabInfo.ulRabId;                                              /* ��ÿ��RAB ID���и�ֵ                     */
            g_TcInfo.TcRabInfo.aRabInfo[(VOS_UINT8)g_TcInfo.TcRabInfo.ulRabCnt].ulCnDomainId =
                pRabmInd->RabInfo.ulCnDomainId;                                         /* ��ÿ��RAB��������CN���и�ֵ              */
            usRabCnt = (VOS_UINT16)g_TcInfo.TcRabInfo.ulRabCnt;
                g_TcInfo.TcRabInfo.aRabInfo[usRabCnt].aulRbId[0] =
                    pRabmInd->RabInfo.ulRbId;
                g_TcInfo.TcRabInfo.aRabInfo[usRabCnt].ulRbCnt = 1;
            g_TcInfo.TcRabInfo.ulRabCnt ++;                                             /* ����Ŀǰ��RAB����                        */
        }
        else
        {
            usRabCnt = i;
            usRbCnt = (VOS_UINT16)g_TcInfo.TcRabInfo.aRabInfo[usRabCnt].ulRbCnt;

            if (  (usRabCnt < (TC_RABM_MAX_RAB_SETUP))
                &&(usRbCnt < RRC_NAS_MAX_RB_PER_RAB))
            {
                g_TcInfo.TcRabInfo.aRabInfo[usRabCnt].aulRbId[usRbCnt] =
                    pRabmInd->RabInfo.ulRbId;
                (g_TcInfo.TcRabInfo.aRabInfo[usRabCnt].ulRbCnt)++;
            }
            else
            {
                PS_NAS_LOG2(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvRabmRabInd:WARNING:overflow ulRabCnt ,ulRbCnt :" ,usRabCnt, usRbCnt);
            }
        }
    }
    else
    {                                                                                   /* �ͷ�RAB��Ϣ                              */
        for( i = 0; i < (VOS_UINT8)g_TcInfo.TcRabInfo.ulRabCnt; i++ )
        {                                                                               /* ����rab�洢��Ϣ                          */
            if((g_TcInfo.TcRabInfo.aRabInfo[i].ulRabId == pRabmInd->RabInfo.ulRabId)&&
              (g_TcInfo.TcRabInfo.aRabInfo[i].ulCnDomainId
                                  == pRabmInd->RabInfo.ulCnDomainId))
            {                                                                           /* �ҵ���RAB ID��λ��                       */
                for( j = i ; j < ((VOS_UINT8)g_TcInfo.TcRabInfo.ulRabCnt - 1) ; j++ )
                {                                                                       /* ɾ����RAB                                */
                    g_TcInfo.TcRabInfo.aRabInfo[j].ulCnDomainId =
                        g_TcInfo.TcRabInfo.aRabInfo[j+1].ulCnDomainId;
                    g_TcInfo.TcRabInfo.aRabInfo[j].ulRabId      =
                        g_TcInfo.TcRabInfo.aRabInfo[j+1].ulRabId;
                    #if 0
                    g_TcInfo.TcRabInfo.aRabInfo[j].ulRbId       =
                        g_TcInfo.TcRabInfo.aRabInfo[j+1].ulRbId;
                    #else
                    g_TcInfo.TcRabInfo.aRabInfo[j].ulRbCnt =
                        g_TcInfo.TcRabInfo.aRabInfo[j+1].ulRbCnt;
                    if (g_TcInfo.TcRabInfo.aRabInfo[j].ulRbCnt < RRC_NAS_MAX_RB_PER_RAB)
                    {
                        for(usRbLoop = 0;usRbLoop < g_TcInfo.TcRabInfo.aRabInfo[j+1].ulRbCnt;usRbLoop++)
                        {
                            g_TcInfo.TcRabInfo.aRabInfo[j].aulRbId[usRbLoop] =
                                g_TcInfo.TcRabInfo.aRabInfo[j + 1].aulRbId[usRbLoop];
                        }
                    }
                    else
                    {
                        PS_NAS_LOG2(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvRabmRabInd:WARNING:overflow ulRabCnt ,ulRbCnt :" ,j + 1, (VOS_INT32)g_TcInfo.TcRabInfo.aRabInfo[j].ulRbCnt);
                    }
                    #endif
                }
                g_TcInfo.TcRabInfo.ulRabCnt --;                                         /* ����Ŀǰ��RAB����                        */
                break;
            }
        }
        if(0 == g_TcInfo.TcRabInfo.ulRabCnt)
        {                                                                               /* ����Ѿ�û��rb����                       */
            switch(g_TcInfo.ucTcState)
            {                                                                           /* ���ݵ�ǰ��״̬�ж�                       */
            case TC_OPEN_TEST_LOOP:
                if(TC_CLOSE_UE_TEST_LOOP == g_TcInfo.ucMsgType)
                {                                                                       /* ������ڴ���ջ���Ϣ                     */
                    g_TcInfo.ucMsgType = TC_MSG_INVALID;                                /* ������ڴ������Ϣ                       */
                    Tc_SndRabmTestLoopReq(TC_LOOP_OPEN);                                /* ֪ͨRABMȥ��������                       */
                }
                break;
            case TC_CLOSE_TEST_LOOP:
                if(TC_OPEN_UE_TEST_LOOP != g_TcInfo.ucMsgType)
                {                                                                       /* ������ڴ���ȥ������Ϣ����������֪ͨ *
                                                                                         * RABM��������                             */
                    Tc_SndRabmTestLoopReq(TC_LOOP_OPEN);                                /* ֪ͨRABMȥ��������                       */
                }
                break;
            default:
                break;
            }
        }
    }
    return;
}
VOS_VOID  Tc_SndRlcTcModeInfo(VOS_UINT8 ucTcFlag, VOS_UINT8 ucTcMode)
{
    TC_RLC_TEST_IND_STRU    *pTcRlcTestInd;
    VOS_UINT32              ulLength;

    ulLength = sizeof(TC_RLC_TEST_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pTcRlcTestInd = (TC_RLC_TEST_IND_STRU *)PS_ALLOC_MSG( WUEPS_PID_TC, ulLength );
    if ( VOS_NULL_PTR == pTcRlcTestInd )
    {
        /*��ӡ������Ϣ---������Ϣ��ʧ��:*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_ERROR, "Tc_SndRlcTcModeInfo:ERROR:Allocates a message packet for TC_RLC_TEST_IND_STRU msg FAIL!");
        return;
    }

    pTcRlcTestInd->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pTcRlcTestInd->ulSenderPid     = WUEPS_PID_TC;
    pTcRlcTestInd->ulReceiverCpuId = VOS_LOCAL_CPUID;

    pTcRlcTestInd->ulReceiverPid   = WUEPS_PID_RLC;

    pTcRlcTestInd->ulLength        = ulLength;
    pTcRlcTestInd->enMsgName       = ID_TC_RLC_TEST_IND;

    if ( TC_LOOP_CLOSE == ucTcFlag )
    {
        if ( TC_MODE_1 == ucTcMode )
        {
            pTcRlcTestInd->enTcMode = TEST_LOOP_MODE1;
        }
        else if ( TC_MODE_2 == ucTcMode )
        {
            pTcRlcTestInd->enTcMode = TEST_LOOP_MODE2;
        }
        else
        {
            pTcRlcTestInd->enTcMode = TEST_LOOP_BUTT;
        }
    }
    else
    {
        pTcRlcTestInd->enTcMode = TEST_LOOP_NULL;
    }

    if ( VOS_OK != NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_TC, (struct MsgCB **)&pTcRlcTestInd) )
    {
        /*��ӡ������Ϣ---������Ϣʧ��:*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_SndRlcTcModeInfo:ERROR:Snd TC_RLC_TEST_IND_STRU msg FAIL!");
    }

    return;
}



VOS_VOID Tc_RcvCloseLoop(VOS_UINT8 * pRcvTcMsg)
{
    VOS_UINT8       i,k;                                                                    /* ����ѭ������                             */
    VOS_UINT8       ucFindFlg = WUEPS_FALSE;                                                /* ����״̬����                             */
    VOS_UINT16      usRlcsize = 0;                                                          /* �����м����                             */
    VOS_UINT16      usRbLoop = 0;
    VOS_UINT8                           ucLbNum;
    VOS_UINT8                           ucRabCnt;
    VOS_UINT8                           ucRbCnt;

    if(TC_MSG_INVALID != g_TcInfo.ucMsgType)
    {                                                                                   /* û�����ڴ���������Ϣ                     */
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvCloseLoop:WARNING:TC_MSG_INVALID != g_TcInfo.ucMsgType ");
        return;
    }
    if( 0 == g_TcInfo.TcRabInfo.ulRabCnt )
    {                                                                                   /* ��ǰ�����ڿ��õ�rab                      */
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvCloseLoop:WARNING:0 == g_TcInfo.TcRabInfo.ulRabCnt");
        return;
    }


    switch(g_TcInfo.ucTcState)
    {                                                                                   /* ���ݵ�ǰ��״̬���зַ�                   */
    case TC_OPEN_TEST_LOOP:
        g_TcInfo.ucMsgType = TC_CLOSE_UE_TEST_LOOP;                                     /* ��¼���ڴ������Ϣ����                   */
        g_TcInfo.TcModeInfo.ucTcMode = pRcvTcMsg[2];                                    /* ����ģʽ��Ϣ                             */

        /*TC��RLC����TC����������ģʽ��Ϣ:*/
        Tc_SndRlcTcModeInfo(TC_LOOP_CLOSE, g_TcInfo.TcModeInfo.ucTcMode);

        g_TcInfo.TcModeInfo.ucLbNum = 0;                                                /* ��ʼ��LBʵ�������0                      */
        if(TC_MODE_1 == g_TcInfo.TcModeInfo.ucTcMode)
        {                                                                               /* �ж�ģʽ�Ƿ���1                          */
            ucLbNum = NAS_COMM_MIN(pRcvTcMsg[3], TC_LB_MAX_RBNUM);
            for( i = 0 ; i < ucLbNum ; i++ )
            {                                                                           /* ��LB��Ϣ�ĳ�����ѭ��                     */
                if((( i + 1 ) % 3) == 0 )
                {                                                                       /* ÿ3���ֽ�һ����λ���д洢                */
                    g_TcInfo.TcModeInfo.aLBList[g_TcInfo.TcModeInfo.ucLbNum].ucRBID
                                                              = pRcvTcMsg[4+i]&(0x1F);  /* ����RB ID                                */
                    usRlcsize = pRcvTcMsg[2+i];                                         /* �洢RLC SIZE�ĸ�8λ��                    */
                    usRlcsize = ((usRlcsize << 8)&0xFF00) | pRcvTcMsg[3+i];             /* ��8λ������λ���洢��8λ����             */
                    g_TcInfo.TcModeInfo.aLBList[g_TcInfo.TcModeInfo.ucLbNum].
                        usUpRlcSduSize = usRlcsize;                                     /* ȡ��RLC SIZE����ֵ                       */
                    g_TcInfo.TcModeInfo.ucLbNum++;                                      /* LBʵ��ĸ�������                         */
                }
            }
            for( i = 0; i < g_TcInfo.TcModeInfo.ucLbNum; i++ )
            {                                                                           /* ���LB�е�RB ID�Ƿ����                  */
                ucFindFlg = WUEPS_FALSE;                                                /* �����ڻ���CN��һ��                     */
                ucRabCnt = NAS_COMM_MIN(((VOS_UINT8)g_TcInfo.TcRabInfo.ulRabCnt), TC_RABM_MAX_RAB_SETUP);
                for(k = 0; k < ucRabCnt; k++ )
                {                                                                       /* �ڵ�ǰ���ڵ�RAB�в���                    */
                    ucRbCnt = NAS_COMM_MIN(((VOS_UINT8)g_TcInfo.TcRabInfo.aRabInfo[k].ulRbCnt), RRC_NAS_MAX_RB_PER_RAB);
                    for(usRbLoop = 0;usRbLoop < ucRbCnt;usRbLoop++)
                    {
                        if(g_TcInfo.TcModeInfo.aLBList[i].ucRBID ==
                                (VOS_UINT8)g_TcInfo.TcRabInfo.aRabInfo[k].aulRbId[usRbLoop])
                        {                                                                   /* LBʵ�����RB ID�Ƿ����Ѿ�������RAB�У��� *
                                                                                             * ��RAB��CN����g_TcInfo.ucCnDomainһ��     */
                            ucFindFlg = WUEPS_TRUE;                                         /* ������һ��                               */
                            break;
                        }
                    }
                }
                if(WUEPS_FALSE == ucFindFlg)
                {                                                                       /* LBʵ���е�RB�����ڻ����뵱ǰ���Ե���ͬ */
                    PS_NAS_LOG1(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING,
                            "Tc_RcvCloseLoop:WARNING: Can't find match RbId!", g_TcInfo.TcModeInfo.aLBList[i].ucRBID);
                }
            }
            Tc_SndRabmTestLoopReq(TC_LOOP_CLOSE);                                       /* ֪ͨRABM�ջ�����                         */
        }
        else
        {                                                                               /* ģʽ����1                                */
            Tc_SndRabmTestLoopReq(TC_LOOP_CLOSE);
        }

        /* ֪ͨMTC����״̬ */
        NAS_TC_SndMtcStatusInfoInd(MTC_NAS_TC_START);
        break;
    case TC_CLOSE_TEST_LOOP:
        Tc_SndDataReq(TC_CLOSE_UE_TEST_LOOP_CMP);                                       /* ���Ϳ�����Ӧ��Ϣ                         */
        break;
    default:
        break;
    }
}

/***********************************************************************
 *  MODULE   : Tc_RcvOpenLoop
 *  FUNCTION : �ж��Ƿ������ػ����ԣ�����LB����
 *  INPUT    : VOS_UINT8
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_VOID
 *  NOTE     :
 *  HISTORY  :
 1.�� ־ ��     s2004.05.24   �¹�����
 2.��    ��   : 2015��6��9��
   ��    ��   : wx270776
   �޸�����   : TAS����: ֪ͨMTC����״̬

 ************************************************************************/
VOS_VOID Tc_RcvOpenLoop()
{
    if(TC_MSG_INVALID != g_TcInfo.ucMsgType)
    {                                                                                   /* û�����ڴ���������Ϣ                     */
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvOpenLoop:WARNING:TC_MSG_INVALID != g_TcInfo.ucMsgType");
        return;
    }
    if( 0 == g_TcInfo.TcRabInfo.ulRabCnt )
    {                                                                                   /* ��ǰ�����ڿ��õ�rab                      */
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvOpenLoop:WARNING:0 == g_TcInfo.TcRabInfo.ulRabCnt");
        return;
    }
    PS_NAS_MEM_SET(&g_TcInfo.TcModeInfo,0,sizeof(TC_MODE_INFO_STRU));                      /* ��ʼ���ڴ�                               */
    switch(g_TcInfo.ucTcState)
    {                                                                                   /* ���ݵ�ǰ��״̬���зַ�                   */
    case TC_CLOSE_TEST_LOOP:
        g_TcInfo.ucMsgType = TC_OPEN_UE_TEST_LOOP;                                      /* ��¼���ڴ������Ϣ����                   */

        /*TC��RLC����TC����ֹͣ��Ϣ:*/
        Tc_SndRlcTcModeInfo(TC_LOOP_OPEN, 0);
        Tc_SndRabmTestLoopReq(TC_LOOP_OPEN);                                            /* ֪ͨRABMȥ��������                       */

        /* ֪ͨMTC����״̬ */
        NAS_TC_SndMtcStatusInfoInd(MTC_NAS_TC_STOP);
        break;

    case TC_NORMAL_MODE:
    case TC_OPEN_TEST_LOOP:
        Tc_SndDataReq(TC_OPEN_UE_TEST_LOOP_CMP);                                        /* ���ͼ�����Ӧ��Ϣ                         */

        break;

    default:
        break;
    }
    return;
}
VOS_VOID Tc_RcvActRbTest()
{
    if(TC_MSG_INVALID != g_TcInfo.ucMsgType)
    {                                                                                   /* û�����ڴ���������Ϣ                     */
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvActRbTest:WARNING:TC_MSG_INVALID != g_TcInfo.ucMsgType");
        return;
    }
    switch(g_TcInfo.ucTcState)
    {                                                                                   /* ���ݵ�ǰ��״̬���зַ�                   */
    case TC_NORMAL_MODE:
        g_TcInfo.ucMsgType = TC_ACT_RB_TEST_MODE;                                       /* ��¼���ڴ������Ϣ����                   */

        /* Deleted by wx270776 for OM�ں�, 2015-7-16, begin */
        //Tc_SndRfaTestControlMsg(ID_TC_RFA_ACT_REQ);
        /* Deleted by wx270776 for OM�ں�, 2015-7-16, end */

        if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
        {
            /* ����DSP������W��֪ͨWPHY���뻷�� */
            NAS_TC_SndWphyCloseLoopNtf();
            g_TcInfo.ucSndWphyCloseLoopNtfLable = VOS_TRUE;
        }

        Tc_SndRabmTestReq(TC_RB_TEST_ACTIVE);                                           /* ֪ͨRABM����                             */
        Tc_SndMmTestReq(TC_RB_TEST_ACTIVE);                                             /* ֪ͨMM����                               */
        Tc_SndGmmTestReq(TC_RB_TEST_ACTIVE);                                            /* ֪ͨGMM����                              */
        g_TcInfo.ucRrcConnStatus = TC_RRC_CONN_STATUS_PRESENT;                          /* RRC���Ӵ��ڵı�־λ��λ                  */

        /* ֪ͨMTC����״̬ */
        NAS_TC_SndMtcStatusInfoInd(MTC_NAS_TC_START);
        break;

    case TC_OPEN_TEST_LOOP:
    case TC_CLOSE_TEST_LOOP:
        Tc_SndDataReq(TC_ACT_RB_TEST_MODE_CMP);                                         /* ���ͼ�����Ӧ��Ϣ                         */
        break;

    default:
        break;
    }
    return;
}


VOS_VOID Tc_RcvDeactRbTest()
{
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8             enCurrUtranMode;

    if(TC_MSG_INVALID != g_TcInfo.ucMsgType)
    {                                                                                   /* û�����ڴ���������Ϣ                     */
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvDeactRbTest:WARNING:TC_MSG_INVALID != g_TcInfo.ucMsgType");
        return;
    }
    switch(g_TcInfo.ucTcState)
    {                                                                                   /* ���ݵ�ǰ��״̬���зַ�                   */
    case TC_OPEN_TEST_LOOP:
    case TC_CLOSE_TEST_LOOP:
        g_TcInfo.ucMsgType = TC_DEACT_RB_TEST_MODE;                                     /* ��¼���ڴ������Ϣ����                   */

        /* Deleted by wx270776 for OM�ں�, 2015-7-16, begin */
        //Tc_SndRfaTestControlMsg(ID_TC_RFA_DEACT_REQ);
        /* Deleted by wx270776 for OM�ں�, 2015-7-16, end */

        enCurrUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();
        if ((VOS_TRUE == g_TcInfo.ucSndWphyCloseLoopNtfLable)
         && (NAS_UTRANCTRL_UTRAN_MODE_FDD == enCurrUtranMode))
        {
            /* ����DSP������W��֪ͨWPHY�˳����� */
            NAS_TC_SndWphyOpenLoopNtf();
            g_TcInfo.ucSndWphyCloseLoopNtfLable = VOS_FALSE;
        }

        Tc_SndDataReq(TC_DEACT_RB_TEST_MODE_CMP);                                       /* ����ȥ������Ӧ��Ϣ                       */
        Tc_SndRabmTestReq(TC_RB_TEST_DEACTIVE);                                         /* ֪ͨRABMȥ����                           */
        Tc_SndMmTestReq(TC_RB_TEST_DEACTIVE);                                           /* ֪ͨMMȥ����                             */
        Tc_SndGmmTestReq(TC_RB_TEST_DEACTIVE);                                          /* ֪ͨGMMȥ����                            */

        /* ֪ͨMTC����״̬ */
        NAS_TC_SndMtcStatusInfoInd(MTC_NAS_TC_STOP);
        break;

    case TC_NORMAL_MODE:
        Tc_SndDataReq(TC_DEACT_RB_TEST_MODE_CMP);                                       /* ����ȥ������Ӧ��Ϣ                       */
        break;

    default:
        break;
    }
    return;
}


VOS_VOID Tc_RcvResetUePosStoredInfo(VOS_UINT8 * pRcvTcMsg)
{
    TC_UE_POS_TECH_ENUM_UINT8           enUePosTech;

    /* ��ȡenUePosTech */
    enUePosTech = pRcvTcMsg[2];

    switch (enUePosTech)
    {
        case TC_UE_POS_TECH_AGPS:
        case TC_UE_POS_TECH_AGNSS:
            /* ��MTA�������ָʾ */
            Tc_SndMtaResetStoredPosInfoInd(enUePosTech);
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvResetUePosStoredInfo:WARNING:Abnormal Msg!");
            break;
    }

    return;
}


VOS_UINT32  Tc_GetMsgSize( VOS_UINT16 usMsgId )
{
    VOS_UINT32  ulMsgSize;

    switch ( usMsgId )
    {
        case TC_CLOSE_TCH_LOOP_REQ:
            ulMsgSize = sizeof(TC_CLOSE_TCH_LOOP_REQ_STRU);
            break;
        case TC_OPEN_TCH_LOOP_REQ:
            ulMsgSize = sizeof(TC_OPEN_TCH_LOOP_REQ_STRU);
            break;
        case TC_TEST_INTERFACE_REQ:
            ulMsgSize = sizeof(TC_TEST_INTERFACE_REQ_STRU);
            break;
        case TC_TEST_MODE_W_TO_G_IND:
            ulMsgSize = sizeof(TC_TEST_MODE_W_TO_G_IND_STRU);
            break;
        default:
            ulMsgSize = 0;
            break;
    }

    return ulMsgSize;
}




VOS_INT32  Tc_SndPhyMsg( VOS_UINT16 usMsgId, VOS_UCHAR *pucStru )
{
    VOS_UINT32      ulMsgSize;
    VOS_UCHAR       *pMsg;
    MSG_CB          *pTmpMsg;

    ulMsgSize = Tc_GetMsgSize( usMsgId );
    if ( 0 == ulMsgSize )
    {
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_SndPhyMsg:WARNING:usMsgId is Abnormal!");
        return VOS_ERR;
    }

    /*������Ϣ��:*/
    pMsg = ( VOS_UCHAR * )PS_ALLOC_MSG( WUEPS_PID_TC, ulMsgSize );
    if ( VOS_NULL_PTR == pMsg )
    {
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_ERROR, "Tc_SndPhyMsg:ERROR:Alloc msg Error!");
        return VOS_ERR;
    }

    /*��д��Ϣͷ:*/
    pTmpMsg                     = (MSG_CB *)pMsg;
    pTmpMsg->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pTmpMsg->ulSenderPid        = WUEPS_PID_TC;
    pTmpMsg->ulReceiverCpuId    = VOS_LOCAL_CPUID;

    pTmpMsg->ulReceiverPid      = DSP_PID_GPHY;

    pTmpMsg->ulLength           = ulMsgSize;
    /*��д��Ϣ��:*/
    PS_NAS_MEM_CPY( pMsg + VOS_MSG_HEAD_LENGTH, pucStru, ulMsgSize );

    /*������Ϣ:*/
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_TC, pMsg ) )
    {
        return VOS_ERR;
    }
    else
    {
        return VOS_OK;
    }

}



VOS_UINT16 Tc_ParseTchLoopType( VOS_UINT8 ucSubChannel )
{
    VOS_UINT8 ucTag = (ucSubChannel & 0x3E) >> 1;

    if ( 0x0 == ucTag )
    {
        return TC_TCH_LOOP_TYPE_A;
    }
    else if ( 0x01 == ucTag )
    {
        return TC_TCH_LOOP_TYPE_B;
    }
    else if ( ( ucTag >= 0x02 ) && ( ucTag <= 0x03 ) )
    {
        return TC_TCH_LOOP_TYPE_C;
    }
    else if ( ( ucTag >= 0x04 ) && ( ucTag <= 0x07 ) )
    {
        return TC_TCH_LOOP_TYPE_D;
    }
    else if ( ( ucTag >= 0x08 ) && ( ucTag <= 0x0B ) )
    {
        return TC_TCH_LOOP_TYPE_E;
    }
    else if ( ( ucTag >= 0x0C ) && ( ucTag <= 0x0F ) )
    {
        return TC_TCH_LOOP_TYPE_F;
    }
    else if ( ( ucTag >= 0x1C ) && ( ucTag <= 0x1F ) )
    {
        return TC_TCH_LOOP_TYPE_I;
    }
    else
    {
        return TC_TCH_LOOP_TYPE_ABNORMAL;
    }
}




VOS_UINT16 Tc_ParseTchChannelType( VOS_UINT8 ucSubChannel )
{
    VOS_UINT16  usChannelType = (VOS_UINT16)ucSubChannel & 0x1;

    return usChannelType;
}




VOS_UINT16 Tc_ParseTestDevice( VOS_UINT8 ucTestDeviceIE )
{
    VOS_UINT16   usTestDevice = (VOS_UINT16)(ucTestDeviceIE & 0x07);

    usTestDevice &= 0x00FF;

    if (     (TC_TEST_DEVICE_0 != usTestDevice)
          && (TC_TEST_DEVICE_1 != usTestDevice)
          && (TC_TEST_DEVICE_2 != usTestDevice)
          && (TC_TEST_DEVICE_3 != usTestDevice) )
    {
        usTestDevice = TC_TEST_DEVICE_ABNORMAL;
    }
    return usTestDevice;
}




VOS_VOID Tc_SndOpenLoopAck(VOS_UINT8 ucAckInfo)
{
    TCMM_DATA_REQ_STRU          *pMmDataReq = VOS_NULL_PTR;                         /* ����ԭ������ָ�� */


    pMmDataReq = (TCMM_DATA_REQ_STRU*)PS_ALLOC_MSG(
                  WUEPS_PID_TC, sizeof(TCMM_DATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pMmDataReq )
    {                                                                                   /* �ڴ�����ʧ��                             */
        return;                                                                         /* ����                                     */
    }

    pMmDataReq->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pMmDataReq->MsgHeader.ulReceiverPid    = WUEPS_PID_MM;
    pMmDataReq->MsgHeader.ulLength         = sizeof( TCMM_DATA_REQ_STRU ) - VOS_MSG_HEAD_LENGTH;
    pMmDataReq->MsgHeader.ulMsgName        = TCMM_DATA_REQ;                         /* ��Ϣ����         */

    pMmDataReq->SendTcMsg.ulTcMsgSize = 3;                                          /* ������Ϣ����     */
    pMmDataReq->SendTcMsg.aucTcMsg[0] = 0x0F;                                       /* ����PD           */
    pMmDataReq->SendTcMsg.aucTcMsg[1] = TC_OPEN_LOOP_CMD;                           /* ������Ϣ����     */
    pMmDataReq->SendTcMsg.aucTcMsg[2] = ucAckInfo;                                  /* ��дAcknowledge Info */

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pMmDataReq))
    {
        NAS_WARNING_LOG(WUEPS_PID_TC, "Tc_SndOpenLoopAck():WARNING:SEND MSG FIAL");
    }

    return;
}




VOS_VOID Tc_RcvPhyCloseTchLoopCnf(TC_CLOSE_TCH_LOOP_CNF_STRU *pCloseTchLoopCnf)
{
    if ( (TC_NORMAL_MODE == g_TcInfo.ucTcState)
         && (TC_CLOSE_TCH_LOOP_CMD == g_TcInfo.ucMsgType) )
    {
        /*�л�TC״̬:*/
        g_TcInfo.ucTcState = TC_GSM_CLOSE_TCH_LOOP;

        /*���ͼ�����Ӧ��Ϣ:*/
        Tc_SndDataReq(TC_CLOSE_TCH_LOOP_ACK);
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvPhyCloseTchLoopCnf:WARNING:Abnormal Msg!");
    }
}




VOS_VOID Tc_RcvPhyOpenTchLoopCnf(TC_OPEN_TCH_LOOP_CNF_STRU *pOpenTchLoopCnf)
{
    VOS_UINT8      ucAckInfo;

    if ( (TC_GSM_CLOSE_TCH_LOOP == g_TcInfo.ucTcState)
         && (TC_OPEN_LOOP_CMD == g_TcInfo.ucMsgType) )
    {
        if ( TC_TCH_LOOP_TYPE_C == g_TcInfo.usTchLoopType )
        {
            /*�Ѵ������յ���OPEN_LOOP_CMD��Ϣ�����һ��������"1"��Ȼ��ط�������*/
            ucAckInfo = (VOS_UINT8)(pOpenTchLoopCnf->usAckInfo | 0x1);
            Tc_SndOpenLoopAck(ucAckInfo);
        }

        /*�л�TC״̬:*/
        g_TcInfo.ucTcState = TC_NORMAL_MODE;

        /*����Ϣ��־:*/
        g_TcInfo.ucMsgType = TC_MSG_INVALID;
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvPhyOpenTchLoopCnf:WARNING:Abnormal Msg!");
    }
}
VOS_VOID Tc_RcvPhyTestInterfaceCnf(TC_TEST_INTERFACE_CNF_STRU *pTestInterfaceCnf)
{
    if ( (TC_GSM_CLOSE_TCH_LOOP == g_TcInfo.ucTcState)
         && (TC_TEST_INTERFACE == g_TcInfo.ucMsgType) )
    {
        /*����Ϣ��־:*/
        g_TcInfo.ucMsgType = TC_MSG_INVALID;
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvPhyTestInterfaceCnf:WARNING:Abnormal Msg!");
    }
}
VOS_VOID Tc_RcvCloseTchLoopCmd(VOS_UCHAR *pRcvTcMsg)
{
    TC_CLOSE_TCH_LOOP_REQ_STRU  TcCloseTchLoopReq;

    if(TC_MSG_INVALID != g_TcInfo.ucMsgType)
    {                                                                      /*û�����ڴ���������Ϣ*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvCloseTchLoopCmd:WARNING:TC_MSG_INVALID != g_TcInfo.ucMsgType");
        return;
    }

    switch(g_TcInfo.ucTcState)
    {                                                                      /*���ݵ�ǰ��״̬���зַ�*/
        case TC_NORMAL_MODE:
            g_TcInfo.ucMsgType = TC_CLOSE_TCH_LOOP_CMD;                    /*��¼���ڴ������Ϣ����*/

            /*������ģ�鷢������������Ϣ:*/
            Tc_SndMmTestReq(TC_RB_TEST_ACTIVE);                            /*֪ͨMM����(2G��3G�еĴ���һ�£���Ҳʹ�ú�TC_RB_TEST_ACTIVE)*/
            Tc_SndGmmTestReq(TC_RB_TEST_ACTIVE);                           /*֪ͨGMM����*/

            /*����TCH ��������:*/
            g_TcInfo.usTchLoopType = Tc_ParseTchLoopType(pRcvTcMsg[2]);

            /*������㷢��ָʾ:*/
            TcCloseTchLoopReq.usMsgID       = TC_CLOSE_TCH_LOOP_REQ;
            TcCloseTchLoopReq.usTchLoopType = g_TcInfo.usTchLoopType;                           /*����GSM��TCH�Ļ�·����*/
            TcCloseTchLoopReq.usSubChan     = Tc_ParseTchChannelType(pRcvTcMsg[2]);             /*����GSM��TCH��Channel����*/
            if ( VOS_OK != Tc_SndPhyMsg(TC_CLOSE_TCH_LOOP_REQ, (VOS_UCHAR *)(&TcCloseTchLoopReq)) )
            {
                g_TcInfo.ucMsgType = TC_MSG_INVALID;
            }

            /* ֪ͨMTC����״̬ */
            NAS_TC_SndMtcStatusInfoInd(MTC_NAS_TC_START);
            break;

        case TC_GSM_CLOSE_TCH_LOOP:
            PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvCloseTchLoopCmd:WARNING:Ignore this Msg!");
            break;

        default:
            PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_ERROR, "Tc_RcvCloseTchLoopCmd:ERROR:g_TcInfo.ucTcState ERROR!");
            break;
    }
    return;
}
VOS_VOID Tc_RcvOpenLoopCmd(VOS_UCHAR *pRcvTcMsg)
{
    TC_OPEN_TCH_LOOP_REQ_STRU   TcOpenTchLoopReq;

    if(TC_MSG_INVALID != g_TcInfo.ucMsgType)
    {                                                                      /*û�����ڴ���������Ϣ*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvOpenLoopCmd:WARNING:TC_MSG_INVALID != g_TcInfo.ucMsgType");
        return;
    }

    switch(g_TcInfo.ucTcState)
    {                                                                      /*���ݵ�ǰ��״̬���зַ�*/
        case TC_GSM_CLOSE_TCH_LOOP:
            g_TcInfo.ucMsgType = TC_OPEN_LOOP_CMD;                         /*��¼���ڴ������Ϣ����*/

            /*������ģ�鷢�ͽ���������Ϣ:*/
            Tc_SndMmTestReq(TC_RB_TEST_DEACTIVE);                          /*֪ͨMM����*/
            Tc_SndGmmTestReq(TC_RB_TEST_DEACTIVE);                         /*֪ͨGMM����*/

            /*������㷢��ָʾ:*/
            TcOpenTchLoopReq.usMsgID   = TC_OPEN_TCH_LOOP_REQ;
            TcOpenTchLoopReq.usAckInfo = (VOS_UINT16)(pRcvTcMsg[2]);
            if ( VOS_OK != Tc_SndPhyMsg(TC_OPEN_TCH_LOOP_REQ, (VOS_UCHAR *)(&TcOpenTchLoopReq)) )
            {
                g_TcInfo.ucMsgType = TC_MSG_INVALID;
            }

            /* ֪ͨMTC����״̬ */
            NAS_TC_SndMtcStatusInfoInd(MTC_NAS_TC_STOP);
            break;

        case TC_NORMAL_MODE:
            PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvOpenLoopCmd:WARNING:Ignore this Msg!");
            break;

        default:
            break;
    }

    return;
}




VOS_VOID Tc_RcvTestInterface(VOS_UCHAR *pRcvTcMsg)
{
    TC_TEST_INTERFACE_REQ_STRU      TcTestInterfaceReq;

    if(TC_MSG_INVALID != g_TcInfo.ucMsgType)
    {                                                                      /*û�����ڴ���������Ϣ*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvTestInterface:WARNING:TC_MSG_INVALID != g_TcInfo.ucMsgType");
        return;
    }

    switch(g_TcInfo.ucTcState)
    {                                                                      /*���ݵ�ǰ��״̬���зַ�*/
        case TC_GSM_CLOSE_TCH_LOOP:
            g_TcInfo.ucMsgType = TC_TEST_INTERFACE;                        /*��¼���ڴ������Ϣ����*/

            /*������㷢��ָʾ:*/
            TcTestInterfaceReq.usMsgID      = TC_TEST_INTERFACE_REQ;
            TcTestInterfaceReq.usTestDevice = Tc_ParseTestDevice(pRcvTcMsg[2]);
            if ( VOS_OK != Tc_SndPhyMsg(TC_TEST_INTERFACE_REQ, (VOS_UCHAR *)(&TcTestInterfaceReq)) )
            {
                g_TcInfo.ucMsgType = TC_MSG_INVALID;
            }
            break;
        case TC_NORMAL_MODE:
            PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvTestInterface:WARNING:Ignore this Msg!");
            break;
        default:
            break;
    }
    return;
}




VOS_VOID  Tc_RcvHpaMsgHandle(struct MsgCB *pMsg)
{
    VOS_UINT16      usMsgId;

    usMsgId = *((VOS_UINT16 *)(pMsg->aucValue));

    switch (usMsgId)
    {
        case TC_CLOSE_TCH_LOOP_CNF:
            Tc_RcvPhyCloseTchLoopCnf( &(((TC_CLOSE_TCH_LOOP_CNF_MSG *)pMsg)->TcCloseTchLoopCnf) );
            break;
        case TC_OPEN_TCH_LOOP_CNF:
            Tc_RcvPhyOpenTchLoopCnf( &(((TC_OPEN_TCH_LOOP_CNF_MSG *)pMsg)->TcOpenTchLoopCnf) );
            break;
        case TC_TEST_INTERFACE_CNF:
            Tc_RcvPhyTestInterfaceCnf( &(((TC_TEST_INTERFACE_CNF_MSG *)pMsg)->TcTestInterfaceCnf) );
            break;
        default:
            break;
    }

    return;
}


VOS_UINT32  Tc_SndGrmGtmSetupReq(VOS_UCHAR *pMsg)
{
    GRM_GTM_SETUP_REQ_MSG   *pSetupReqMsg;
    VOS_UINT32               ulMsgLength;

    /*GRM_GTM_SETUP_REQ_MSG ����Ϣ����*/
    ulMsgLength = sizeof(GRM_GTM_SETUP_REQ_MSG) - VOS_MSG_HEAD_LENGTH;

    /*������Ϣ��*/
    pSetupReqMsg = (GRM_GTM_SETUP_REQ_MSG *)PS_ALLOC_MSG(WUEPS_PID_TC, ulMsgLength);
    if ( VOS_NULL_PTR == pSetupReqMsg )
    {
        /*��ӡ������Ϣ---������Ϣ��ʧ��*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_ERROR, "Tc_SndGrmGtmSetupReq:ERROR:Alloc msg Fail!");
        return VOS_ERR;
    }
    /*��д��Ϣͷ*/
    pSetupReqMsg->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pSetupReqMsg->ulSenderPid       = WUEPS_PID_TC;
    pSetupReqMsg->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pSetupReqMsg->ulReceiverPid     = UEPS_PID_GRM;
    pSetupReqMsg->ulLength          = ulMsgLength;

    /*��д��Ϣ����*/
    pSetupReqMsg->usMsgType         = ID_GRM_GTM_SETUP_REQ;
    pSetupReqMsg->usTransId         = 0;

    pSetupReqMsg->stGLSetupReq.ucPduDescript1 = pMsg[2];    /*��һ��PDU Descript�ֽ�*/
    pSetupReqMsg->stGLSetupReq.ucPduDescript2 = pMsg[3];    /*�ڶ���PDU Descript�ֽ�*/
    pSetupReqMsg->stGLSetupReq.ucModeFlag     = pMsg[4];    /*Mode Flag�ֽ�*/
    pSetupReqMsg->stGLSetupReq.Rsv            = 0;          /*Ϊ�����ֽڶ���������Reserved�ֽ�*/

    /*���͸���Ϣ*/
    if ( VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pSetupReqMsg) )
    {
        /*��ӡ������Ϣ---������Ϣʧ��:*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_SndGrmGtmSetupReq:WARNING:SEND GRM_GTM_SETUP_REQ msg FAIL!");
        return VOS_ERR;
    }
    else
    {
        /*��ӡ������Ϣ---��������Ϣ:*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Tc_SndGrmGtmSetupReq:NORMAL:SEND GRM_GTM_SETUP_REQ Msg Success.");

        /*��¼�µ�ǰ����״̬*/
        g_TcInfo.ucMsgType = TC_GPRS_TEST_MODE_CMD;
        return VOS_OK;
    }
}
VOS_VOID  Tc_SndGrmGtmRelRsp(VOS_VOID)
{
    GRM_GTM_REL_RSP_MSG     *pRelRspMsg;
    VOS_UINT32               ulMsgLength;

    /*GRM_GTM_REL_RSP_MSG ����Ϣ����*/
    ulMsgLength = sizeof(GRM_GTM_REL_RSP_MSG) - VOS_MSG_HEAD_LENGTH;

    /*������Ϣ��*/
    pRelRspMsg = (GRM_GTM_REL_RSP_MSG *)PS_ALLOC_MSG(WUEPS_PID_TC, ulMsgLength);
    if ( VOS_NULL_PTR == pRelRspMsg )
    {
        /*��ӡ������Ϣ---������Ϣ��ʧ��*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_ERROR, "Tc_SndGrmGtmRelRsp:ERROR:Alloc msg Fail!");
        return;
    }

    /*��д��Ϣͷ*/
    pRelRspMsg->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pRelRspMsg->ulSenderPid       = WUEPS_PID_TC;
    pRelRspMsg->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pRelRspMsg->ulReceiverPid     = UEPS_PID_GRM;
    pRelRspMsg->ulLength          = ulMsgLength;

    /*��д��Ϣ����*/
    pRelRspMsg->usMsgType         = ID_GRM_GTM_REL_RSP;
    pRelRspMsg->usTransId         = 0;

    /*���͸���Ϣ*/
    if ( VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pRelRspMsg) )
    {
        /*��ӡ������Ϣ---������Ϣʧ��:*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_SndGrmGtmRelRsp:WARNING:SEND GRM_GTM_REL_RSP msg FAIL!");
    }
    else
    {
        /*��ӡ������Ϣ---��������Ϣ:*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Tc_SndGrmGtmRelRsp:NORMAL:SEND GRM_GTM_REL_RSP Msg Success.");
    }

    return;

}



VOS_VOID  Tc_RcvGrmGtmSetupCnf(VOS_UCHAR *pMsg)
{
    TC_GTM_SETUP_CNF_MSG *pSetupCnfMsg;

    pSetupCnfMsg = (TC_GTM_SETUP_CNF_MSG *)pMsg;

    if ( (TC_NORMAL_MODE == g_TcInfo.ucTcState)
         && (TC_GPRS_TEST_MODE_CMD == g_TcInfo.ucMsgType) )
    {
        if ( GTM_STATUS_SETUP_OK == pSetupCnfMsg->usTransId )
        {
            /*�л�״̬:*/
            g_TcInfo.ucTcState = TC_GPRS_CLOSE_TCH_LOOP;
            g_TcInfo.ucMsgType = TC_MSG_INVALID;

            /* ����: GPRS���ؽ��� */
            NAS_MMC_SndMsccDataTranAttri(NAS_MSCC_PIF_DATATRAN_ATTRI_PDP_ACT);
        }
        else   /*ʧ��*/
        {
            /*��ӡ������Ϣ---GPRS���ؽ���ʧ��:*/
            PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvGrmGtmSetupCnf:WARNING:GPRS TC setup FAIL!");

            g_TcInfo.ucMsgType = TC_MSG_INVALID;

            /*������ģ�鷢�ͽ���������Ϣ:*/
            Tc_SndMmTestReq(TC_RB_TEST_DEACTIVE);                          /*֪ͨMM����*/
            Tc_SndGmmTestReq(TC_RB_TEST_DEACTIVE);                         /*֪ͨGMM����*/
            Tc_SndCcTestReq(TC_RB_TEST_DEACTIVE);                          /*֪ͨCC����*/
            Tc_SndSmTestReq(TC_RB_TEST_DEACTIVE);                          /*֪ͨSM����*/
            Tc_SndSmsTestReq(TC_RB_TEST_DEACTIVE);                         /*֪ͨSMS����*/
            Tc_SndSsTestReq(TC_RB_TEST_DEACTIVE);                          /*֪ͨSS����*/
        }
    }
    else
    {
        /*��ӡ������Ϣ---�����˲����߼�����Ϣ:*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvGrmGtmSetupCnf:WARNING:RECEIVE An Illogic Msg!");
    }

    return;
}





VOS_VOID  Tc_RcvGrmGtmRelInd(VOS_VOID)
{
    if(TC_MSG_INVALID != g_TcInfo.ucMsgType)
    {
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvGrmGtmRelInd:WARNING:TC_MSG_INVALID != g_TcInfo.ucMsgType");
        return;
    }

    if ( TC_GPRS_CLOSE_TCH_LOOP == g_TcInfo.ucTcState )
    {
        /*��GRM�����ͷŻ�����Ӧ��Ϣ*/
        Tc_SndGrmGtmRelRsp();

        /*������ģ�鷢�ͽ���������Ϣ:*/
        Tc_SndMmTestReq(TC_RB_TEST_DEACTIVE);                          /*֪ͨMM����*/
        Tc_SndGmmTestReq(TC_RB_TEST_DEACTIVE);                         /*֪ͨGMM����*/
        Tc_SndCcTestReq(TC_RB_TEST_DEACTIVE);                          /*֪ͨCC����*/
        Tc_SndSmTestReq(TC_RB_TEST_DEACTIVE);                          /*֪ͨSM����*/
        Tc_SndSmsTestReq(TC_RB_TEST_DEACTIVE);                         /*֪ͨSMS����*/
        Tc_SndSsTestReq(TC_RB_TEST_DEACTIVE);                          /*֪ͨSS����*/

        /*�л�״̬*/
        g_TcInfo.ucTcState = TC_NORMAL_MODE;

        /* ����: GPRS�����ͷ� */
        NAS_MMC_SndMsccDataTranAttri(NAS_MSCC_PIF_DATATRAN_ATTRI_PDP_DEACT);
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvGrmGtmRelInd:WARNING:Illogic State when receive TC_GTM_REL_IND Msg!");
    }

    return;
}





VOS_VOID  Tc_RcvGrmMsgHandle(struct MsgCB *pMsg)
{
    GPRS_LOOP_NO_CONTENT_MSG    *pRcvMsg;

    pRcvMsg = (GPRS_LOOP_NO_CONTENT_MSG *)pMsg;
    switch ( pRcvMsg->usMsgType )
    {
        case ID_TC_GTM_SETUP_CNF :
            Tc_RcvGrmGtmSetupCnf((VOS_UCHAR *)pMsg);
            break;
        case ID_TC_GTM_REL_IND :
            Tc_RcvGrmGtmRelInd();
            break;
        case ID_GTM_TC_SRB_SETUP_CNF:
            Tc_RcvGrmGtmEgprsSetupCnf((VOS_UCHAR *)pMsg);
            break;
        case ID_GTM_TC_SRB_REL_IND:
            Tc_RcvGrmGtmEgprsRelInd();
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvGrmMsgHandle:WARNING:Msg type Error!");
            break;
    }

    return;
}




VOS_VOID  Tc_RcvGprsTestModeCmd(VOS_UCHAR *pRcvTcMsg)
{
    VOS_UINT32      ulResult;

    if(TC_MSG_INVALID != g_TcInfo.ucMsgType)
    {
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvGprsTestModeCmd:WARNING:TC_MSG_INVALID != g_TcInfo.ucMsgType");
        return;
    }

    switch(g_TcInfo.ucTcState)
    {
        case TC_NORMAL_MODE:
            /*��GRM���ͽ�������������Ϣ*/
            ulResult = Tc_SndGrmGtmSetupReq(pRcvTcMsg);
            if ( VOS_OK == ulResult )
            {
                /*������ģ�鷢������������Ϣ:*/
                Tc_SndMmTestReq(TC_RB_TEST_ACTIVE);                            /*֪ͨMM����(2G��3G�еĴ���һ�£���Ҳʹ�ú�TC_RB_TEST_ACTIVE)*/
                Tc_SndGmmTestReq(TC_RB_TEST_ACTIVE);                           /*֪ͨGMM����*/
                Tc_SndCcTestReq(TC_RB_TEST_ACTIVE);                            /*֪ͨCC����*/
                Tc_SndSmTestReq(TC_RB_TEST_ACTIVE);                            /*֪ͨSM����*/
                Tc_SndSmsTestReq(TC_RB_TEST_ACTIVE);                           /*֪ͨSMS����*/
                Tc_SndSsTestReq(TC_RB_TEST_ACTIVE);                            /*֪ͨSS����*/
            }
            break;
        case TC_GPRS_CLOSE_TCH_LOOP:
            PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvGprsTestModeCmd:WARNING:Ignore this Msg!");
            break;
        default:
            break;
    }

    return;
}




VOS_UINT32  Tc_SndGrmGtmEgprsSetupReq(
    VOS_UINT8                           ucModeFlg

)
{
    TC_GTM_SRB_SETUP_REQ_MSG     *pSetupReqMsg;
    VOS_UINT32                       ulMsgLength;

    /*ID_TC_GTM_SRB_SETUP_REQ ����Ϣ����*/
    ulMsgLength = sizeof(TC_GTM_SRB_SETUP_REQ_MSG) - VOS_MSG_HEAD_LENGTH;

    /*������Ϣ��*/
    pSetupReqMsg = (TC_GTM_SRB_SETUP_REQ_MSG *)PS_ALLOC_MSG(WUEPS_PID_TC, ulMsgLength);
    if ( VOS_NULL_PTR == pSetupReqMsg )
    {
        /*��ӡ������Ϣ---������Ϣ��ʧ��*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_ERROR, "Tc_SndGrmGtmEgprsSetupReq:ERROR:Alloc msg Fail!");
        return VOS_ERR;
    }
    /*��д��Ϣͷ*/
    pSetupReqMsg->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pSetupReqMsg->ulSenderPid       = WUEPS_PID_TC;
    pSetupReqMsg->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pSetupReqMsg->ulReceiverPid     = UEPS_PID_GRM;
    pSetupReqMsg->ulLength          = ulMsgLength;

    /*��д��Ϣ����*/
    pSetupReqMsg->usMsgType         = ID_TC_GTM_SRB_SETUP_REQ;
    pSetupReqMsg->usModeFlg         = ucModeFlg;

    /*���͸���Ϣ*/
    if ( VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pSetupReqMsg) )
    {
        /*��ӡ������Ϣ---������Ϣʧ��:*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_SndGrmGtmEgprsSetupReq:WARNING:SEND TC_GTM_SRB_SETUP_REQ_MSG msg FAIL!");
        return VOS_ERR;
    }
    else
    {
        /*��ӡ������Ϣ---��������Ϣ:*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Tc_SndGrmGtmEgprsSetupReq:NORMAL:SEND TC_GTM_SRB_SETUP_REQ_MSG Msg Success.");

        /*��¼�µ�ǰ����״̬*/
        g_TcInfo.ucMsgType = TC_EGPRS_START_RADIO_BLOCK_LOOPBACK_CMD;
        return VOS_OK;
    }
}
VOS_VOID  Tc_SndGrmGtmEgprsRelRsp(VOS_VOID)
{
    TC_GTM_SRB_REL_RSP_MSG     *pRelRspMsg;
    VOS_UINT32                     ulMsgLength;

    /*TC_GTM_SRB_REL_RSP_MSG ����Ϣ����*/
    ulMsgLength = sizeof(TC_GTM_SRB_REL_RSP_MSG) - VOS_MSG_HEAD_LENGTH;

    /*������Ϣ��*/
    pRelRspMsg = (TC_GTM_SRB_REL_RSP_MSG *)PS_ALLOC_MSG(WUEPS_PID_TC, ulMsgLength);
    if ( VOS_NULL_PTR == pRelRspMsg )
    {
        /*��ӡ������Ϣ---������Ϣ��ʧ��*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_ERROR, "Tc_SndGrmGtmEgprsRelRsp:ERROR:Alloc msg Fail!");
        return;
    }

    /*��д��Ϣͷ*/
    pRelRspMsg->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pRelRspMsg->ulSenderPid       = WUEPS_PID_TC;
    pRelRspMsg->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pRelRspMsg->ulReceiverPid     = UEPS_PID_GRM;
    pRelRspMsg->ulLength          = ulMsgLength;

    /*��д��Ϣ����*/
    pRelRspMsg->usMsgType         = ID_TC_GTM_SRB_REL_RSP;
    pRelRspMsg->usTransId         = 0;

    /*���͸���Ϣ*/
    if ( VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pRelRspMsg) )
    {
        /*��ӡ������Ϣ---������Ϣʧ��:*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_SndGrmGtmEgprsRelRsp:WARNING:SEND ID_TC_GTM_SRB_REL_RSP msg FAIL!");
    }
    else
    {
        /*��ӡ������Ϣ---��������Ϣ:*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Tc_SndGrmGtmEgprsRelRsp:NORMAL:SEND ID_TC_GTM_SRB_REL_RSP Msg Success.");
    }

    return;
}




VOS_VOID  Tc_RcvGrmGtmEgprsSetupCnf(VOS_UCHAR *pMsg)
{
    GTM_TC_SRB_SETUP_CNF_MSG *pSetupCnfMsg;

    pSetupCnfMsg = (GTM_TC_SRB_SETUP_CNF_MSG *)pMsg;

    if ( (TC_NORMAL_MODE == g_TcInfo.ucTcState)
         && (TC_EGPRS_START_RADIO_BLOCK_LOOPBACK_CMD == g_TcInfo.ucMsgType) )
    {
        if ( GTM_STATUS_SETUP_OK == pSetupCnfMsg->usTransId )
        {
            /*�л�״̬:*/
            g_TcInfo.ucTcState = TC_EGPRS_CLOSE_TCH_LOOP;
            g_TcInfo.ucMsgType = TC_MSG_INVALID;

            /* ����: EGPRS���ؽ��� */
            NAS_MMC_SndMsccDataTranAttri(NAS_MSCC_PIF_DATATRAN_ATTRI_PDP_ACT);
        }
        else   /*ʧ��*/
        {
            /*��ӡ������Ϣ---EGPRS���ؽ���ʧ��:*/
            PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvGrmGtmEgprsSetupCnf:WARNING:EGPRS TC setup FAIL!");

            g_TcInfo.ucMsgType = TC_MSG_INVALID;

            /*������ģ�鷢�ͽ���������Ϣ:*/
            Tc_SndMmTestReq(TC_RB_TEST_DEACTIVE);                          /*֪ͨMM����*/
            Tc_SndGmmTestReq(TC_RB_TEST_DEACTIVE);                         /*֪ͨGMM����*/
            Tc_SndCcTestReq(TC_RB_TEST_DEACTIVE);                          /*֪ͨCC����*/
            Tc_SndSmTestReq(TC_RB_TEST_DEACTIVE);                          /*֪ͨSM����*/
            Tc_SndSmsTestReq(TC_RB_TEST_DEACTIVE);                         /*֪ͨSMS����*/
            Tc_SndSsTestReq(TC_RB_TEST_DEACTIVE);                          /*֪ͨSS����*/
        }
    }
    else
    {
        /*��ӡ������Ϣ---�����˲����߼�����Ϣ:*/
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvGrmGtmEgprsSetupCnf:WARNING:RECEIVE An Illogic Msg!");
    }

    return;
}




VOS_VOID  Tc_RcvGrmGtmEgprsRelInd(VOS_VOID)
{
    if(TC_MSG_INVALID != g_TcInfo.ucMsgType)
    {
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvGrmGtmEgprsRelInd:WARNING:TC_MSG_INVALID != g_TcInfo.ucMsgType");
        return;
    }

    if ( TC_EGPRS_CLOSE_TCH_LOOP == g_TcInfo.ucTcState )
    {
        /*��GRM�����ͷ�EGPRS�����ͷ���Ӧ��Ϣ*/
        Tc_SndGrmGtmEgprsRelRsp();

        /*������ģ�鷢�ͽ���������Ϣ:*/
        Tc_SndMmTestReq(TC_RB_TEST_DEACTIVE);                          /*֪ͨMM����*/
        Tc_SndGmmTestReq(TC_RB_TEST_DEACTIVE);                         /*֪ͨGMM����*/
        Tc_SndCcTestReq(TC_RB_TEST_DEACTIVE);                          /*֪ͨCC����*/
        Tc_SndSmTestReq(TC_RB_TEST_DEACTIVE);                          /*֪ͨSM����*/
        Tc_SndSmsTestReq(TC_RB_TEST_DEACTIVE);                         /*֪ͨSMS����*/
        Tc_SndSsTestReq(TC_RB_TEST_DEACTIVE);                          /*֪ͨSS����*/

        /*�л�״̬*/
        g_TcInfo.ucTcState = TC_NORMAL_MODE;

        /* ����: EGPRS�����ͷ� */
        NAS_MMC_SndMsccDataTranAttri(NAS_MSCC_PIF_DATATRAN_ATTRI_PDP_DEACT);
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvGrmGtmEgprsRelInd:WARNING:Illogic State when receive ID_GTM_TC_SRB_REL_IND Msg!");
    }

    return;
}


VOS_VOID  Tc_RcvEgprsLoopBackCmd(
    VOS_UINT8                           ucModeFlg
)
{
    VOS_UINT32      ulResult;

    if(TC_MSG_INVALID != g_TcInfo.ucMsgType)
    {
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvEgprsLoopBackCmd:WARNING:TC_MSG_INVALID != g_TcInfo.ucMsgType");
        return;
    }

    switch(g_TcInfo.ucTcState)
    {
        case TC_NORMAL_MODE:
            /*��GRM���ͽ���EGPRS����������Ϣ*/
            ulResult = Tc_SndGrmGtmEgprsSetupReq(ucModeFlg);
            if ( VOS_OK == ulResult )
            {
                /*������ģ�鷢������������Ϣ:*/
                Tc_SndMmTestReq(TC_RB_TEST_ACTIVE);                            /*֪ͨMM����(2G��3G�еĴ���һ�£���Ҳʹ�ú�TC_RB_TEST_ACTIVE)*/
                Tc_SndGmmTestReq(TC_RB_TEST_ACTIVE);                           /*֪ͨGMM����*/
                Tc_SndCcTestReq(TC_RB_TEST_ACTIVE);                            /*֪ͨCC����*/
                Tc_SndSmTestReq(TC_RB_TEST_ACTIVE);                            /*֪ͨSM����*/
                Tc_SndSmsTestReq(TC_RB_TEST_ACTIVE);                           /*֪ͨSMS����*/
                Tc_SndSsTestReq(TC_RB_TEST_ACTIVE);                            /*֪ͨSS����*/
            }
            break;
        case TC_EGPRS_CLOSE_TCH_LOOP:
            PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvEgprsLoopBackCmd:WARNING:Ignore this Msg!");
            break;
        default:
            break;
    }

    return;
}



VOS_VOID Tc_RcvMmDataInd(VOS_VOID *pMsg)
{
    TCMM_DATA_IND_STRU         *pRcvMsg;                                                /* �յ�����Ϣ                               */
    VOS_UINT8                      *pRcvTcMsg;                                              /* ԭ���г��ص�Tc�տ���Ϣ                   */
    VOS_UINT8                      ucMsgType;                                               /* �տ���Ϣ������                           */

    pRcvMsg = (TCMM_DATA_IND_STRU *)(pMsg);                                             /* �ṹ������ת��                           */
    /* added by gaoming for A32D00546 begin */

    if( 2 > pRcvMsg->RcvTcMsg.ulTcMsgSize )
    {                                                                                   /* ��Ϣ����                                 */
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvMmDataInd:WARNING:2 > pRcvMsg->RcvTcMsg.ulTcMsgSize");
        return;
    }
    if(( 0x0F != ( pRcvMsg->RcvTcMsg.aucTcMsg[0] & 0x0F)) &&
       ( 0    != ( pRcvMsg->RcvTcMsg.aucTcMsg[0] & 0xF0)))
    {                                                                                   /* PDΪf��SIΪ0�����Էַ�����               */
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvMmDataInd:WARNING:( 0x0F != ( pRcvMsg->RcvTcMsg.aucTcMsg[0] & 0x0F)) &&( 0    != ( pRcvMsg->RcvTcMsg.aucTcMsg[0] & 0xF0))");
        return;
    }
     /* added by gaoming for A32D00546 end */
    pRcvTcMsg = pRcvMsg->RcvTcMsg.aucTcMsg;                                             /* ȡ����Ϣ���ݵ�ַ                         */
    ucMsgType = pRcvTcMsg[1];                                                           /* ȡ�ÿտ���Ϣ������                       */
    g_TcInfo.ucCnDomain = TC_CN_DOMAIN_CS;                                              /* ��¼��Ϣ��CS�����ϴ���                   */
    switch(ucMsgType)
    {                                                                                   /* ������Ϣ���ͽ��зַ�                     */
    case TC_CLOSE_UE_TEST_LOOP:
        Tc_RcvCloseLoop(pRcvTcMsg);                                                     /* ����TC_CLOSE_UE_TEST_LOOP��Ϣ            */
        break;
    case TC_OPEN_UE_TEST_LOOP:
        Tc_RcvOpenLoop();                                                               /* ����TC_OPEN_UE_TEST_LOOP��Ϣ             */
        break;
    case TC_ACT_RB_TEST_MODE:
        Tc_RcvActRbTest();                                                              /* ����TC_ACT_RB_TEST_MODE��Ϣ              */
        break;
    case TC_DEACT_RB_TEST_MODE:
        Tc_RcvDeactRbTest();                                                            /* ����TC_DEACT_RB_TEST_MODE��Ϣ            */
        break;
    case TC_RESET_UE_POS_STORED_INFO:
        Tc_RcvResetUePosStoredInfo(pRcvTcMsg);
        break;
    case TC_CLOSE_TCH_LOOP_CMD:
        Tc_RcvCloseTchLoopCmd(pRcvTcMsg);
        break;
    case TC_OPEN_LOOP_CMD:
        Tc_RcvOpenLoopCmd(pRcvTcMsg);
        break;
    case TC_TEST_INTERFACE:
        Tc_RcvTestInterface(pRcvTcMsg);
        break;
    default:
        break;
    }
    return;
}


VOS_VOID Tc_RcvGmmDataInd(VOS_VOID *pMsg)
{
    TCGMM_DATA_IND_STRU                *pRcvMsg;                                                /* �յ�����Ϣ                               */
    VOS_UINT8                          *pRcvTcMsg;                                              /* ԭ���г��ص�Tc�տ���Ϣ                   */
    VOS_UINT8                           ucMsgType;                                               /* �տ���Ϣ������                           */
    VOS_UINT8                           ucModeFlg;

    pRcvMsg = (TCGMM_DATA_IND_STRU *)(pMsg);                                             /* �ṹ������ת��                           */
   /* added by gaoming for A32D00546 begin */
    if( 2 > pRcvMsg->RcvTcMsg.ulTcMsgSize )
    {                                                                                   /* ��Ϣ����                                 */
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvGmmDataInd:WARNING:2 > pRcvMsg->RcvTcMsg.ulTcMsgSize");
        return;
    }
    if(( 0x0F != ( pRcvMsg->RcvTcMsg.aucTcMsg[0] & 0x0F)) &&
       ( 0    != ( pRcvMsg->RcvTcMsg.aucTcMsg[0] & 0xF0)))
    {                                                                                   /* PDΪf��SIΪ0�����Էַ�����               */
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_RcvGmmDataInd:WARNING:( 0x0F != ( pRcvMsg->RcvTcMsg.aucTcMsg[0] & 0x0F)) &&( 0    != ( pRcvMsg->RcvTcMsg.aucTcMsg[0] & 0xF0))");
        return;
    }

    /* added by gaoming for A32D00546 end */
    pRcvTcMsg = pRcvMsg->RcvTcMsg.aucTcMsg;                                             /* ȡ����Ϣ���ݵ�ַ                         */
    ucMsgType = pRcvTcMsg[1];                                                           /* ȡ�ÿտ���Ϣ������                       */
    g_TcInfo.ucCnDomain = TC_CN_DOMAIN_PS;                                              /* ��¼��Ϣ��PS�����ϴ���                   */
    switch(ucMsgType)
    {                                                                                   /* ������Ϣ���ͽ��зַ�                     */
    case TC_CLOSE_UE_TEST_LOOP:
        Tc_RcvCloseLoop(pRcvTcMsg);                                                     /* ����TC_CLOSE_UE_TEST_LOOP��Ϣ            */
        break;
    case TC_OPEN_UE_TEST_LOOP:
        Tc_RcvOpenLoop();                                                               /* ����TC_OPEN_UE_TEST_LOOP��Ϣ             */
        break;
    case TC_ACT_RB_TEST_MODE:
        Tc_RcvActRbTest();                                                              /* ����TC_ACT_RB_TEST_MODE��Ϣ              */
        break;
    case TC_DEACT_RB_TEST_MODE:
        Tc_RcvDeactRbTest();                                                            /* ����TC_DEACT_RB_TEST_MODE��Ϣ            */
        break;
    case TC_RESET_UE_POS_STORED_INFO:
        Tc_RcvResetUePosStoredInfo(pRcvTcMsg);
        break;
    case TC_GPRS_TEST_MODE_CMD:
        Tc_RcvGprsTestModeCmd(pRcvTcMsg);
        break;
    case TC_EGPRS_START_RADIO_BLOCK_LOOPBACK_CMD:
        ucModeFlg = pRcvTcMsg[2];
        Tc_RcvEgprsLoopBackCmd(ucModeFlg);
        break;
    default:
        break;
    }
    return;
}


VOS_VOID Tc_TaskInit()
{
    PS_NAS_MEM_SET(&g_TcInfo,0,sizeof(TC_GLOBAL_CTRL_STRU));                               /* ��ʼ��ȫ�ֱ���                           */

    g_TcInfo.ucMsgType     = TC_MSG_INVALID;
    g_TcInfo.usTchLoopType = TC_TCH_LOOP_TYPE_ABNORMAL;

}
VOS_VOID Tc_TaskEntry (struct MsgCB * pRcvMsg)
{
    MSG_HEADER_STRU*        pMsgHeader;

    if ( VOS_NULL_PTR == pRcvMsg )
    {
        PS_NAS_LOG(WUEPS_PID_TC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Tc_TaskEntry:WARNING:The Entry Pointer is NULL!");
        return;
    }

    if ( DSP_PID_GPHY == pRcvMsg->ulSenderPid )
    {
        Tc_RcvHpaMsgHandle(pRcvMsg);
        return;
    }

    if ( UEPS_PID_GRM == pRcvMsg->ulSenderPid )
    {
        Tc_RcvGrmMsgHandle(pRcvMsg);
        return;
    }

    pMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;

    switch( pMsgHeader->ulMsgName )
    {                                                                       /* ��MM��Ϣ���зַ�                         */
    case TCMM_DATA_IND:
        Tc_RcvMmDataInd(pRcvMsg);                                           /* ��Ϣ�ַ�����                             */
        break;

    case TCGMM_DATA_IND:
        Tc_RcvGmmDataInd(pRcvMsg);                                          /* ��Ϣ�ַ�����                             */
        break;

    case TCMM_RR_REL_IND:
        NAS_TC_RcvMmRelInd(pRcvMsg);
        break;

    case TCGMM_RR_REL_IND:
        NAS_TC_RcvGmmRelInd(pRcvMsg);
        break;

    case TCRABM_TEST_CNF:
        Tc_RcvRabmTestCnf(pRcvMsg);                                         /* ��Ϣ�ַ�����                             */
        break;

    case TCRABM_TEST_LOOP_CNF:
        Tc_RcvRabmTestLoopCnf();                                            /* RABM��Ϣ�ַ�����                         */
        break;

    case TCRABM_RAB_IND:
        Tc_RcvRabmRabInd(pRcvMsg);                                          /* RABM��Ϣ�ַ�����                         */
        break;

    case TCGMM_HANDOVER_IND:
        NAS_TC_RcvGmmHandoverInd(pRcvMsg);
        break;

    default:
        break;
    }
}

/******************************************************************************
 * �������� �� WuepsTcPidInit
 * �������� �� WUEPS TC PID�ĳ�ʼ������
 * ����˵�� �� ��
 * ��    ע ��
 * �� �� ֵ �� VOS_UINT32 ��ʼ�������
 *             0  : �ɹ�
 *             ��0: ʧ��
 *
 * �����ʷ ��
 *           No.  ����      ���                                    ��   ��
 *           1    ��־��    �½�                                   2005.02.24
 *****************************************************************************/
VOS_UINT32 WuepsTcPidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    switch( ip )
    {
    case VOS_IP_LOAD_CONFIG:
        Tc_TaskInit();                                                      /* TC TASK��ʼ��                            */
        break;
    case VOS_IP_FARMALLOC:
    case VOS_IP_INITIAL:
    case VOS_IP_ENROLLMENT:
    case VOS_IP_LOAD_DATA:
    case VOS_IP_FETCH_DATA:
    case VOS_IP_STARTUP:
    case VOS_IP_RIVAL:
    case VOS_IP_KICKOFF:
    case VOS_IP_STANDBY:
    case VOS_IP_BROADCAST_STATE:
    case VOS_IP_RESTART:
    case VOS_IP_BUTT:
        break;
    default:
        break;
    }

    return VOS_OK;
}


/*****************************************************************************
Function            : Tc_GetState()
Description         : �˽ӿ��ṩTC��ǰ״̬
Calls               : VOS_VOID
Called By           :
Input               : VOS_VOID
Output              : VOS_VOID
Return Value        : TC_NORMAL_MODE                TC��ͨ��״̬����ʱRB����û�м���
                      TC_OPEN_TEST_LOOP             TC�Ŀ���״̬����ʱRB�����Ѿ����
                                                    �ػ����Ի�û�н���
                      TC_CLOSE_TEST_LOOP            TC�ıջ�״̬����ʱRB�����Ѿ����
                                                    �ػ��������ڽ���
                      TC_ABNORMAL_STATE             TC״̬�쳣
Others              :
*****************************************************************************/
VOS_UINT32  Tc_GetState(VOS_VOID)
{
    if ( g_TcInfo.ucTcState <= TC_CLOSE_TEST_LOOP )
    {
        return g_TcInfo.ucTcState;
    }
    else
    {
        return TC_ABNORMAL_STATE;
    }

}



VOS_UINT32  Tc_GetMode(VOS_VOID)
{
    return g_TcInfo.TcModeInfo.ucTcMode;
}




VOS_VOID NAS_TC_RcvMmRelInd(
    struct MsgCB                       *pstMsg
)
{
    /* ���RRC���Ӵ��ڱ�־�Ѳ����ڣ���ʾ���յ���REL IND����ֱ�ӷ��� */
    if (TC_RRC_CONN_STATUS_ABSENT == g_TcInfo.ucRrcConnStatus)
    {
        return;
    }

    /* ���RRC���Ӵ��ڱ�־ */
    g_TcInfo.ucRrcConnStatus = TC_RRC_CONN_STATUS_ABSENT;

    /* ���ݵ�ǰ��״̬���зַ� */
    switch(g_TcInfo.ucTcState)
    {
        case TC_NORMAL_MODE:
          /* ��״̬���յ�MMC_REL_IND,����������W2G����
             (W2Gʱ��RABM�յ�suspend IND�������Tc_TaskInit��TC��ʼ��)��
             ��״̬�µĴ���������״̬һ�£�����break */
        case TC_OPEN_TEST_LOOP:
        case TC_CLOSE_TEST_LOOP:
            if(TC_DEACT_RB_TEST_MODE != g_TcInfo.ucMsgType)
            {                                                                   /* ������ڴ���ȥ������Ϣ����������֪ͨ *
                                                                                 * NAS����TASKȥ����                        */
                Tc_SndRabmTestReq(TC_RB_TEST_DEACTIVE);                         /* ֪ͨRABMȥ����                           */
                Tc_SndMmTestReq(TC_RB_TEST_DEACTIVE);                           /* ֪ͨMMȥ����                             */
                Tc_SndGmmTestReq(TC_RB_TEST_DEACTIVE);                          /* ֪ͨGMMȥ����                            */
            }

            /* ֪ͨMTC���ز���ֹͣ */
            NAS_TC_SndMtcStatusInfoInd(MTC_NAS_TC_STOP);
            break;

        case TC_GSM_CLOSE_TCH_LOOP:
        case TC_GPRS_CLOSE_TCH_LOOP:
            /* ֪ͨMTC���ز���ֹͣ */
            NAS_TC_SndMtcStatusInfoInd(MTC_NAS_TC_STOP);
            break;

        default:
            break;
    }

    g_TcInfo.ucMsgType = TC_MSG_INVALID;                                        /* ������ڴ������Ϣ����                   */
    return;
}


VOS_VOID NAS_TC_RcvGmmRelInd(
    struct MsgCB                       *pstMsg
)
{
    /* ���RRC���Ӵ��ڱ�־�Ѳ����ڣ���ʾ���յ���REL IND����ֱ�ӷ��� */
    if(TC_RRC_CONN_STATUS_ABSENT == g_TcInfo.ucRrcConnStatus)
    {
        return;
    }

    /* �����CS����, ������PS�����ͷ� */
    if (TC_CN_DOMAIN_CS == g_TcInfo.ucCnDomain)
    {
        return;
    }

    /* ���RRC���Ӵ��ڱ�־ */
    g_TcInfo.ucRrcConnStatus = TC_RRC_CONN_STATUS_ABSENT;

    /* ���ݵ�ǰ��״̬���зַ� */
    switch(g_TcInfo.ucTcState)
    {
        case TC_NORMAL_MODE:
          /* ��״̬���յ�MMC_REL_IND,����������W2G����
             (W2Gʱ��RABM�յ�suspend IND�������Tc_TaskInit��TC��ʼ��)��
             ��״̬�µĴ���������״̬һ�£�����break */
        case TC_OPEN_TEST_LOOP:
        case TC_CLOSE_TEST_LOOP:
            if(TC_DEACT_RB_TEST_MODE != g_TcInfo.ucMsgType)
            {                                                                   /* ������ڴ���ȥ������Ϣ����������֪ͨ *
                                                                                 * NAS����TASKȥ����                        */
                Tc_SndRabmTestReq(TC_RB_TEST_DEACTIVE);                         /* ֪ͨRABMȥ����                           */
                Tc_SndMmTestReq(TC_RB_TEST_DEACTIVE);                           /* ֪ͨMMȥ����                             */
                Tc_SndGmmTestReq(TC_RB_TEST_DEACTIVE);                          /* ֪ͨGMMȥ����                            */
            }

            /* ֪ͨMTC���ز���ֹͣ */
            NAS_TC_SndMtcStatusInfoInd(MTC_NAS_TC_STOP);
            break;

        case TC_GSM_CLOSE_TCH_LOOP:
        case TC_GPRS_CLOSE_TCH_LOOP:
            /* ֪ͨMTC���ز���ֹͣ */
            NAS_TC_SndMtcStatusInfoInd(MTC_NAS_TC_STOP);
            break;

        default:
            break;
    }

    g_TcInfo.ucMsgType = TC_MSG_INVALID;                                        /* ������ڴ������Ϣ����                   */
    return;
}


VOS_VOID NAS_TC_RcvGmmHandoverInd(
    struct MsgCB                       *pstMsg
)
{
    TCGMM_HANDOVER_IND_STRU            *pstHandoverMsg = VOS_NULL_PTR;
    TC_TEST_MODE_W_TO_G_IND_STRU        stTcTestModeWToGInd;

    pstHandoverMsg = (TCGMM_HANDOVER_IND_STRU*)pstMsg;

    if (NAS_MML_NET_RAT_TYPE_GSM == pstHandoverMsg->enNetRat)
    {
        /* ������㷢��ָʾ: */
        stTcTestModeWToGInd.usMsgID = TC_TEST_MODE_W_TO_G_IND;

        if ( VOS_OK != Tc_SndPhyMsg(TC_TEST_MODE_W_TO_G_IND, (VOS_UCHAR *)(&stTcTestModeWToGInd)) )
        {
            NAS_WARNING_LOG(WUEPS_PID_TC, "NAS_TC_RcvGmmHandoverInd:ERROR:Send TC_TEST_MODE_W_TO_G_IND fail!");
        }
    }
    /* ����DSP�����л���W��֪ͨWPHY���뻷�� */
    else if ((NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
          && (NAS_MML_NET_RAT_TYPE_WCDMA == pstHandoverMsg->enNetRat))
    {
        NAS_TC_SndWphyCloseLoopNtf();
    }
    else
    {

    }
    return;
}



VOS_VOID NAS_TC_SndWphyCloseLoopNtf(VOS_VOID)
{
    VOS_UINT32                          ulLength;
    TC_WPHY_CLOSE_LOOP_NTF_STRU        *pstMsg;

    /* ����TC_WPHY_CLOSE_LOOP_NTF_STRU��Ϣ */
    ulLength    = sizeof(TC_WPHY_CLOSE_LOOP_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg      = (TC_WPHY_CLOSE_LOOP_NTF_STRU *)PS_ALLOC_MSG(WUEPS_PID_TC, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_WARNING_LOG(WUEPS_PID_TC, "NAS_TC_SndWphyCloseLoopNtf, Alloc Message Fail");

        return;
    }

    PS_MEM_SET(pstMsg,0x00,sizeof(TC_WPHY_CLOSE_LOOP_NTF_STRU));

    /* ��д��Ϣͷ */
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_TC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = DSP_PID_WPHY;
    pstMsg->ulLength        = ulLength;

    /* ��д��Ϣ�� */
    pstMsg->usMsgId         = ID_TC_WPHY_CLOSE_LOOP_NTF;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pstMsg))
    {
        NAS_WARNING_LOG(WUEPS_PID_TC, "NAS_TC_SndWphyCloseLoopNtf, Send Message Fail");

        return;
    }

    return;
}
VOS_VOID NAS_TC_SndWphyOpenLoopNtf(VOS_VOID)
{
    VOS_UINT32                          ulLength;
    TC_WPHY_OPEN_LOOP_NTF_STRU         *pstMsg;

    /* ����TC_WPHY_CLOSE_LOOP_NTF_STRU��Ϣ */
    ulLength    = sizeof(TC_WPHY_OPEN_LOOP_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg      = (TC_WPHY_OPEN_LOOP_NTF_STRU *)PS_ALLOC_MSG(WUEPS_PID_TC, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_WARNING_LOG(WUEPS_PID_TC, "NAS_TC_SndWphyCloseLoopNtf, Alloc Message Fail");

        return;
    }

    PS_MEM_SET(pstMsg,0x00,sizeof(TC_WPHY_OPEN_LOOP_NTF_STRU));

    /* ��д��Ϣͷ */
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_TC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = DSP_PID_WPHY;
    pstMsg->ulLength        = ulLength;

    /* ��д��Ϣ�� */
    pstMsg->usMsgId         = ID_TC_WPHY_OPEN_LOOP_NTF;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pstMsg))
    {
        NAS_WARNING_LOG(WUEPS_PID_TC, "NAS_TC_SndWphyCloseLoopNtf, Send Message Fail");

        return;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_TC_SndMtcStatusInfoInd
 ��������  : ��MTC������Ϣ֪ͨTC���ز���״̬��Ϣ
 �������  : MTC_NAS_TC_STATUS_ENUM_UINT16    enTcStatus  TC����״̬
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��5��5��
   ��    ��   : wx270776
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_TC_SndMtcStatusInfoInd(
    MTC_NAS_TC_STATUS_ENUM_UINT16       enTcStatus
)
{

    VOS_UINT32                          ulMsgLength;
    NAS_MTC_TC_STATUS_INFO_IND_STRU    *pstNasSndMtcMsg = VOS_NULL_PTR;

    /* ����MTC_NAS_TC_STATUS_INFO_IND_STRU��Ϣ */
    ulMsgLength      = sizeof(NAS_MTC_TC_STATUS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstNasSndMtcMsg  = (NAS_MTC_TC_STATUS_INFO_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_TC, ulMsgLength);

    if (VOS_NULL_PTR == pstNasSndMtcMsg)
    {
        NAS_WARNING_LOG(WUEPS_PID_TC, "NAS_TC_SndMtcStatusInfoInd, Alloc Message Fail");
        return;
    }

    PS_MEM_SET(pstNasSndMtcMsg, 0x00, sizeof(NAS_MTC_TC_STATUS_INFO_IND_STRU));

    /* ��д��Ϣͷ */
    pstNasSndMtcMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstNasSndMtcMsg->ulSenderPid      = WUEPS_PID_TC;
    pstNasSndMtcMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstNasSndMtcMsg->ulReceiverPid    = UEPS_PID_MTC;
    pstNasSndMtcMsg->ulLength         = ulMsgLength;

    /* ��д��Ϣ�� */
    pstNasSndMtcMsg->ulMsgName        = ID_NAS_MTC_TC_STATUS_INFO_IND;
    pstNasSndMtcMsg->enRatMode        = NAS_TC_GetNetRatMode();
    pstNasSndMtcMsg->enTcStatus       = enTcStatus;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TC, pstNasSndMtcMsg))
    {
        NAS_WARNING_LOG(WUEPS_PID_TC, "NAS_TC_SndMtcStatusInfoInd, Send Message Fail");
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_TC_GetNetRatMode
 ��������  : ��ȡ��ǰ���뼼��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : MTC_NAS_RAT_MODE_ENUM_UINT16  ֪ͨMTC��ǰ���뼼��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��5��5��
   ��    ��   : wx270776
   �޸�����   : �����ɺ���

*****************************************************************************/
MTC_NAS_RAT_MODE_ENUM_UINT16 NAS_TC_GetNetRatMode(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurNetRat;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurUtrMod;
    MTC_NAS_RAT_MODE_ENUM_UINT16        enSndMtcNetRatMode;

    enCurNetRat                       = NAS_MML_GetCurrNetRatType();
    enCurUtrMod                       = NAS_UTRANCTRL_GetCurrUtranMode();
    enSndMtcNetRatMode                = MTC_NAS_RAT_MODE_BUTT;

    if (NAS_MML_NET_RAT_TYPE_GSM == enCurNetRat)
    {
        enSndMtcNetRatMode = MTC_NAS_RAT_MODE_GSM;
    }
    else if ( (NAS_MML_NET_RAT_TYPE_WCDMA   == enCurNetRat)
           && (NAS_UTRANCTRL_UTRAN_MODE_FDD == enCurUtrMod) )
    {
        enSndMtcNetRatMode = MTC_NAS_RAT_MODE_WCDMA;
    }
    else if ( (NAS_MML_NET_RAT_TYPE_WCDMA   == enCurNetRat)
           && (NAS_UTRANCTRL_UTRAN_MODE_TDD == enCurUtrMod) )
    {
        enSndMtcNetRatMode = MTC_NAS_RAT_MODE_TDSCDMA;
    }
    else if ( (NAS_MML_NET_RAT_TYPE_LTE     == enCurNetRat)
           && (NAS_UTRANCTRL_UTRAN_MODE_FDD == enCurUtrMod) )
    {
        enSndMtcNetRatMode = MTC_NAS_RAT_MODE_LTE;
    }
    else if ( (NAS_MML_NET_RAT_TYPE_LTE     == enCurNetRat)
           && (NAS_UTRANCTRL_UTRAN_MODE_TDD == enCurUtrMod) )
    {
        enSndMtcNetRatMode = MTC_NAS_RAT_MODE_CDMA;
    }
    else
    {
        enSndMtcNetRatMode = MTC_NAS_RAT_MODE_BUTT;
    }

    return enSndMtcNetRatMode;
}


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
