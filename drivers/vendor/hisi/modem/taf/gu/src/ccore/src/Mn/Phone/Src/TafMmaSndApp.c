


/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "PsTypeDef.h"
#include "MnComm.h"
#include "TafSdcCtx.h"
#include "TafLog.h"
#include "TafMmaSndApp.h"
#include "MmaMsccInterface.h"
#include "MmaAppLocal.h"
#include "TafStdlib.h"

/* Added by y00307564 for CDMA Iteration 8 2015-2-10 begin */
#include "TafMmaCtx.h"
/* Added by y00307564 for CDMA Iteration 8 2015-2-10 end */

#include "TafMmaComFunc.h"

#include "NasMntn.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_SND_APP_C


/*****************************************************************************
   2 ȫ�ֱ�������ͺ�
****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/
/* Modified by l00301449 for CDMA 1X Iteration 13, 2015-04-17, begin */

VOS_VOID TAF_MMA_SndSysCfgSetCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
)
{
    TAF_MMA_SYS_CFG_CNF_STRU           *pstSndMsg   = VOS_NULL_PTR;

    pstSndMsg = (TAF_MMA_SYS_CFG_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMA,
                                             sizeof(TAF_MMA_SYS_CFG_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndSysCfgSetCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_SYS_CFG_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_SYS_CFG_SET_CNF;
    pstSndMsg->usClientId               = pstCtrl->usClientId;
    pstSndMsg->ucOpid                   = pstCtrl->ucOpId;

    if (TAF_ERR_NO_ERROR != enErrorCause)
    {
        pstSndMsg->enRslt = TAF_MMA_APP_OPER_RESULT_FAILURE;
    }
    else
    {
        pstSndMsg->enRslt = TAF_MMA_APP_OPER_RESULT_SUCCESS;
    }

    pstSndMsg->enErrorCause             = enErrorCause;

    PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    return;
}
/* Modified by l00301449 for CDMA 1X Iteration 13, 2015-04-17, end */

/* Added by c00318887 for AT&T phaseII, 2015-3-12, begin */
/*****************************************************************************
 �� �� ��  : TAF_MMA_SndEonsUcs2Rsp
 ��������  : ����Ϣ�ظ�EONSUCS2��ѯ���
 �������  : pstCtrl                    - ����ģ����Ϣ
             enRslt                     - ��ѯ���
             usErrorCause               - ������
             pstEonsUcs2PlmnName        - ��ѯ����Ľṹ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��12��
    ��    ��   : c00318887
    �޸�����   : �����ɺ���
*****************************************************************************/

VOS_VOID TAF_MMA_SndEonsUcs2Rsp(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause,
    TAF_MMA_EONS_UCS2_PLMN_NAME_STRU   *pstEonsUcs2PlmnName
)
{
    TAF_MMA_EONS_UCS2_CNF_STRU         *pstSndMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstSndMsg = (TAF_MMA_EONS_UCS2_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                        WUEPS_PID_MMA,
                                        sizeof(TAF_MMA_EONS_UCS2_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndEonsUcs2Rsp:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_EONS_UCS2_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MSG_MMA_EONS_UCS2_CNF;
    pstSndMsg->usClientId               = pstCtrl->usClientId;
    pstSndMsg->ucOpId                   = pstCtrl->ucOpId;
    pstSndMsg->enRslt                   = enRslt;
    pstSndMsg->enErrorCause             = enErrorCause;

    if (VOS_NULL_PTR != pstEonsUcs2PlmnName)
    {
        PS_MEM_CPY(&pstSndMsg->stEonsUcs2PlmnName,
                    pstEonsUcs2PlmnName,
                    sizeof(TAF_MMA_EONS_UCS2_PLMN_NAME_STRU));
    }

    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    if (VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndEonsUcs2Rsp:Send Msg Failed");
        return;
    }

    return;

}
/* Added by c00318887 for AT&T phaseII, 2015-3-12, end */

VOS_VOID TAF_MMA_SndPhoneModeSetCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_PH_MODE                         ucPhMode,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
)
{
    TAF_MMA_PHONE_MODE_SET_CNF_STRU    *pstSndMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstSndMsg = (TAF_MMA_PHONE_MODE_SET_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMA,
                                             sizeof(TAF_MMA_PHONE_MODE_SET_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndPhoneModeSetCnf:Alloc Msg Failed");

        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_PHONE_MODE_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_PHONE_MODE_SET_CNF;
    pstSndMsg->usClientId               = pstCtrl->usClientId;
    pstSndMsg->ucOpid                   = pstCtrl->ucOpId;
    pstSndMsg->ucPhMode                 = ucPhMode;
    pstSndMsg->enRslt                   = enRslt;
    pstSndMsg->enErrorCause             = enErrorCause;

    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    if (VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndPhoneModeSetCnf:Send Msg Failed");

        return;
    }

    return;

}



VOS_VOID TAF_MMA_SndAcqBestNetworkCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt,
    MSCC_MMA_ACQ_CNF_STRU               *pstAcqCnfMsg
)
{
    TAF_MMA_ACQ_CNF_STRU               *pstSndMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstSndMsg = (TAF_MMA_ACQ_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                         WUEPS_PID_MMA,
                                         sizeof(TAF_MMA_ACQ_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndAcqBestNetworkCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_ACQ_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_ACQ_BEST_NETWORK_CNF;
    pstSndMsg->usClientId               = pstCtrl->usClientId;
    pstSndMsg->ucOpid                   = pstCtrl->ucOpId;
    pstSndMsg->enRslt                   = enRslt;
    pstSndMsg->stPlmnId.Mcc             = pstAcqCnfMsg->stPlmnId.ulMcc;
    pstSndMsg->stPlmnId.Mnc             = pstAcqCnfMsg->stPlmnId.ulMnc;
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, begin */
    pstSndMsg->ulArfcn                  = pstAcqCnfMsg->ulArfcn;
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, end */

    /* ת�������õ�ǰ��Plmn Priority Class */
    TAF_MMA_ConvertPlmnPriorityClass(pstAcqCnfMsg->enPrioClass, &(pstSndMsg->enPrioClass));

    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    if (VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndAcqBestNetworkCnf:Send Msg Failed");
        return;
    }

    return;

}


VOS_VOID TAF_MMA_SndRegCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt,
    MSCC_MMA_REG_CNF_STRU               *pstRegCnfMsg
)
{
    TAF_MMA_REG_CNF_STRU               *pstSndMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstSndMsg = (TAF_MMA_REG_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                         WUEPS_PID_MMA,
                                         sizeof(TAF_MMA_REG_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndRegCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_REG_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_REG_CNF;
    pstSndMsg->usClientId               = pstCtrl->usClientId;
    pstSndMsg->ucOpid                   = pstCtrl->ucOpId;
    pstSndMsg->enRslt                   = enRslt;
    pstSndMsg->stPlmnId.Mcc             = pstRegCnfMsg->stPlmnId.ulMcc;
    pstSndMsg->stPlmnId.Mnc             = pstRegCnfMsg->stPlmnId.ulMnc;
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, begin */
    pstSndMsg->ulArfcn                  = pstRegCnfMsg->ulArfcn;
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, end */

    /* ת�������õ�ǰ��Plmn Priority Class */
    TAF_MMA_ConvertPlmnPriorityClass(pstRegCnfMsg->enPrioClass, &(pstSndMsg->enPrioClass));
    pstSndMsg->enLmmAttachRegStatus     = pstRegCnfMsg->enLmmAttachClRegStatus;

    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    if (VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndRegCnf:Send Msg Failed");
        return;
    }

    return;

}


VOS_VOID TAF_MMA_SndPowerSaveCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt
)
{
    TAF_MMA_POWER_SAVE_CNF_STRU        *pstSndMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstSndMsg = (TAF_MMA_POWER_SAVE_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                 WUEPS_PID_MMA,
                                                 sizeof(TAF_MMA_POWER_SAVE_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndPowerSaveCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_POWER_SAVE_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_POWER_SAVE_CNF;
    pstSndMsg->usClientId               = pstCtrl->usClientId;
    pstSndMsg->ucOpid                   = pstCtrl->ucOpId;
    pstSndMsg->enRslt                   = enRslt;

    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    if (VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndPowerSaveCnf:Send Msg Failed");
        return;
    }

    return;

}


VOS_VOID TAF_MMA_SndDetachCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enDetachRslt,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
)
{
    TAF_MMA_DETACH_CNF_STRU            *pstDetachCnf = VOS_NULL_PTR;

    /* ������Ϣ��TAF_MMA_DETACH_CNF_STRU */
    pstDetachCnf = (TAF_MMA_DETACH_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           WUEPS_PID_MMA,
                                           sizeof(TAF_MMA_DETACH_CNF_STRU));

    /* �ڴ�����ʧ�ܣ����� */
    if (VOS_NULL_PTR == pstDetachCnf)
    {
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstDetachCnf + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_DETACH_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��������������TAF_MMA_DETACH_CNF_STRU */
    pstDetachCnf->ulSenderPid       = WUEPS_PID_MMA;
    pstDetachCnf->ulReceiverPid     = pstCtrl->ulModuleId;
    pstDetachCnf->ulMsgName         = ID_TAF_MMA_DETACH_CNF;

    pstDetachCnf->usClientId        = pstCtrl->usClientId;
    pstDetachCnf->ucOpid            = pstCtrl->ucOpId;
    pstDetachCnf->enRslt            = enDetachRslt;
    pstDetachCnf->enErrorCause      = enErrorCause;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMA, pstDetachCnf))
    {
        return;
    }

    return;

}

#if (FEATURE_ON == FEATURE_CL_INTERWORK)


VOS_VOID TAF_MMA_SndCmmcaServiceInd(VOS_VOID)
{
    TAF_MMA_SERVICE_STATUS_IND_STRU    *pstSndMsg    = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    /* �����ڴ�  */
    pstSndMsg = (TAF_MMA_SERVICE_STATUS_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(TAF_MMA_SERVICE_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndCmmcaServiceInd: Memory allocation is failure");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstSndMsg) + VOS_MSG_HEAD_LENGTH, 0, sizeof(TAF_MMA_SERVICE_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* fill in header information */
    pstSndMsg->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid        = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid      = WUEPS_PID_CMMCA;
    pstSndMsg->ulLength           = sizeof(TAF_MMA_SERVICE_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* fill in message name */
    pstSndMsg->ulMsgName          = ID_TAF_MMA_SERVICE_STATUS_IND;

    /* fill in clientid and opid */
    pstSndMsg->usClientId         = CMMCA_CLIENT_ID;
    pstSndMsg->ucOpid             = 0x0;

    /* fill in message content */
    TAF_MMA_ConvertServiceStatus(TAF_SDC_GetCsServiceStatus(), &(pstSndMsg->CsSrvSta));
    TAF_MMA_ConvertServiceStatus(TAF_SDC_GetPsServiceStatus(), &(pstSndMsg->PsSrvSta));

    pstSndMsg->ucCsSimValid       = TAF_SDC_GetSimCsRegStatus();
    pstSndMsg->ucPsSimValid       = TAF_SDC_GetSimPsRegStatus();

    /* send message */
    ulRet = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);
    if (VOS_OK != ulRet)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndCmmcaServiceInd: Send message is failure");
    }

    return;
}



VOS_VOID TAF_MMA_SndAcqInd(
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt,
    MSCC_MMA_ACQ_IND_STRU               *pstAcqIndMsg
)
{
    TAF_MMA_ACQ_IND_STRU               *pstSndMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstSndMsg = (TAF_MMA_ACQ_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                         WUEPS_PID_MMA,
                                         sizeof(TAF_MMA_ACQ_IND_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndAcqInd:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_ACQ_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = WUEPS_PID_CMMCA;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_ACQ_IND;
    pstSndMsg->usClientId               = CMMCA_CLIENT_ID;
    pstSndMsg->ucOpid                   = 0;
    pstSndMsg->enRslt                   = enRslt;
    pstSndMsg->stPlmnId.Mcc             = pstAcqIndMsg->stPlmnId.ulMcc;
    pstSndMsg->stPlmnId.Mnc             = pstAcqIndMsg->stPlmnId.ulMnc;
    pstSndMsg->ulArfcn                  = pstAcqIndMsg->ulArfcn;

    /* ת�������õ�ǰ��Plmn Priority Class */
    TAF_MMA_ConvertPlmnPriorityClass(pstAcqIndMsg->enPrioClass, &(pstSndMsg->enPrioClass));

    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    if (VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndAcqInd:Send Msg Failed");
        return;
    }

    return;

}
VOS_VOID TAF_MMA_SndCmmcaSysInfoInd(
    VOS_UINT32                                              ulMcc,
    VOS_UINT32                                              ulMnc,
    VOS_UINT32                                              ulArfcn,
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8             enPrioClass
)
{
    TAF_MMA_SYS_INFO_IND_STRU          *pstSndMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstSndMsg = (TAF_MMA_SYS_INFO_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMA,
                                             sizeof(TAF_MMA_SYS_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndSysInfoInd:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = WUEPS_PID_CMMCA;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_SYS_INFO_IND;
    pstSndMsg->usClientId               = CMMCA_CLIENT_ID;
    pstSndMsg->ucOpid                   = 0;
    pstSndMsg->stPlmnId.Mcc             = ulMcc;
    pstSndMsg->stPlmnId.Mnc             = ulMnc;
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, begin */
    pstSndMsg->ulArfcn                  = ulArfcn;
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, end */

    /* ת�������õ�ǰ��Plmn Priority Class */
    TAF_MMA_ConvertPlmnPriorityClass(enPrioClass, &(pstSndMsg->enPrioClass));

    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    if (VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndSysInfoInd:Send Msg Failed");
        return;
    }

    return;

}
VOS_VOID TAF_MMA_SndSimStatusInd(
    TAF_MMA_USIMM_CARD_TYPE_ENUM_UINT32           enCardType,                    /* ������:SIM��USIM��ROM-SIM  */
    TAF_MMA_CARD_STATUS_ENUM_UINT8                enCardStatus
)
{
    TAF_MMA_SIM_STATUS_IND_STRU        *pstSndMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstSndMsg = (TAF_MMA_SIM_STATUS_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMA,
                                             sizeof(TAF_MMA_SIM_STATUS_IND_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndSimStatusInd:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_SIM_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = WUEPS_PID_CMMCA;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_SIM_STATUS_IND;
    pstSndMsg->usClientId               = CMMCA_CLIENT_ID;
    pstSndMsg->ucOpid                   = 0;
    pstSndMsg->enCardType               = enCardType;
    /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    pstSndMsg->enCardStatus             = enCardStatus;
    /* Modified by h00313353 for iteration 9, 2015-2-6, end */

    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);
    if (VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndSimStatusInd:Send Msg Failed");
        return;
    }

    return;

}

#endif
VOS_VOID TAF_MMA_SndSrvAcqCnf(
    TAF_MMA_SRV_ACQ_RESULT_ENUM_UINT8   enResult
)
{
    TAF_MMA_SRV_ACQ_CNF_STRU           *pstSndMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstSndMsg = (TAF_MMA_SRV_ACQ_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMA,
                                             sizeof(TAF_MMA_SRV_ACQ_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndSrvAcqCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_SRV_ACQ_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = WUEPS_PID_TAF;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_SRV_ACQ_CNF;
    pstSndMsg->enResult                 = enResult;

    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    if (VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndSrvAcqCnf:Send Msg Failed");
        return;
    }

    return;
}



/*lint -restore */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/* Added by m00312079 for CDMA 1X Iteration 6 2014-12-26 begin */
/*****************************************************************************
 �� �� ��  : TAF_MMA_SndCdmaCsqSetCnf
 ��������  : ��AT����ID_TAF_MMA_CDMACSQ_SET_CNF
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��25��
    ��    ��   : m00312079
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MMA_SndCdmaCsqSetCnf(
    TAF_MMA_CTRL_STRU                                      *pstCtrl,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32                     enRslt
)
{
    TAF_MMA_CDMACSQ_SET_CNF_STRU            *pstCdmaCsqCnf   = VOS_NULL_PTR;

    /* ������Ϣ��TAF_MMA_CDMACSQ_SET_CNF_STRU */
    pstCdmaCsqCnf = (TAF_MMA_CDMACSQ_SET_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           WUEPS_PID_MMA,
                                           sizeof(TAF_MMA_CDMACSQ_SET_CNF_STRU));

    /* �ڴ�����ʧ�ܣ����� */
    if (VOS_NULL_PTR == pstCdmaCsqCnf)
    {
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstCdmaCsqCnf + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_CDMACSQ_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��������������TAF_MMA_CDMACSQ_SET_CNF_STRU */
    pstCdmaCsqCnf->ulSenderPid       = WUEPS_PID_MMA;
    pstCdmaCsqCnf->ulReceiverPid     = pstCtrl->ulModuleId;
    pstCdmaCsqCnf->ulMsgName         = ID_TAF_MMA_CDMACSQ_SET_CNF;

    pstCdmaCsqCnf->usClientId        = pstCtrl->usClientId;
    pstCdmaCsqCnf->ucOpId            = pstCtrl->ucOpId;
    pstCdmaCsqCnf->enRslt            = enRslt;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMA, pstCdmaCsqCnf))
    {
        return;
    }

    return;

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SndCdmaCsqInd
 ��������  : ��AT����ID_TAF_MMA_CDMACSQ_IND
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :


 �޸���ʷ      :
  1.��    ��   : 2014��12��25��
    ��    ��   : m00312079
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MMA_SndCdmaCsqInd(VOS_INT8 cCdmaRssi,VOS_INT8 cCdmaEcIo)
{
    TAF_MMA_CDMACSQ_IND_STRU           *pstCdmaCsqInd = VOS_NULL_PTR;

    /* ������Ϣ��TAF_MMA_CDMACSQ_SET_CNF_STRU */
    pstCdmaCsqInd = (TAF_MMA_CDMACSQ_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           WUEPS_PID_MMA,
                                           sizeof(TAF_MMA_CDMACSQ_IND_STRU));

    /* �ڴ�����ʧ�ܣ����� */
    if (VOS_NULL_PTR == pstCdmaCsqInd)
    {
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstCdmaCsqInd + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_CDMACSQ_IND_STRU) - VOS_MSG_HEAD_LENGTH);


    /* ��д��Ϣͷ����Ϣ */
    pstCdmaCsqInd->ulReceiverPid = WUEPS_PID_AT;
    pstCdmaCsqInd->ulMsgName     = ID_TAF_MMA_CDMACSQ_IND;
    pstCdmaCsqInd->usClientId    = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_TAF);
    pstCdmaCsqInd->ucOpid        = MMA_OP_ID_INTERNAL;
    pstCdmaCsqInd->cCdmaRssi     = cCdmaRssi;
    pstCdmaCsqInd->cCdmaEcIo     = cCdmaEcIo;

     /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMA, pstCdmaCsqInd))
    {
        MMA_ERRORLOG("TAF_MMA_SndCdmaCsqInd: Send Msg Error!");
    }

    return;
}

/* Added by m00312079 for CDMA 1X Iteration 6 2014-12-26 end */

/*****************************************************************************
 �� �� ��  : TAF_MMA_SndCFreqLockSetCnf
 ��������  : MMA��AT������Ƶ���õĽ��
 �������  : TAF_MMA_CFREQ_LOCK_SET_REQ_STRU *pstCFreqLockSetReq
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��29��
    ��    ��   : y00307564
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_SndCFreqLockSetCnf(
    TAF_MMA_CFREQ_LOCK_SET_REQ_STRU    *pstCFreqLockSetReq,
    VOS_UINT32                          ulRslt
)
{
    TAF_MMA_CFREQ_LOCK_SET_CNF_STRU    *pstCFreqLockSetCnf    = VOS_NULL_PTR;

    pstCFreqLockSetCnf =
            (TAF_MMA_CFREQ_LOCK_SET_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                        sizeof(TAF_MMA_CFREQ_LOCK_SET_CNF_STRU));
    if (VOS_NULL_PTR == pstCFreqLockSetCnf)
    {
        return VOS_FALSE;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstCFreqLockSetCnf + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_CFREQ_LOCK_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ����Ϣ */
    pstCFreqLockSetCnf->ulReceiverPid          = pstCFreqLockSetReq->ulModuleId;
    pstCFreqLockSetCnf->ulMsgName              = ID_TAF_MMA_CDMA_FREQ_LOCK_SET_CNF;
    pstCFreqLockSetCnf->stCtrl.ulModuleId      = pstCFreqLockSetReq->ulModuleId;
    pstCFreqLockSetCnf->stCtrl.usClientId      = pstCFreqLockSetReq->usClientId;
    pstCFreqLockSetCnf->stCtrl.ucOpId          = pstCFreqLockSetReq->ucOpId;
    pstCFreqLockSetCnf->ulRslt                 = ulRslt;

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstCFreqLockSetCnf);

    return VOS_TRUE;
}

/* Added by x00314862 for CDMA 1X Iteration 6 2014-12-26 begin */
/*****************************************************************************
 �� �� ��  : TAF_MMA_SndCTimeInd
 ��������  : send ctime ind
 �������  :
            pstTimezoneCTime  -- ʱ��ʱ����Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��26��
    ��    ��   : x00314862
    �޸�����   :
*****************************************************************************/
VOS_UINT32 TAF_MMA_SndCTimeInd(
    TAF_MMA_TIME_ZONE_CTIME_STRU       *pstTimezoneCTime
)
{
    TAF_MMA_CTIME_IND_STRU             *pstCTimeInd;

    pstCTimeInd = (TAF_MMA_CTIME_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                             sizeof(TAF_MMA_CTIME_IND_STRU));
    if (VOS_NULL_PTR == pstCTimeInd)
    {
        MMA_ERRORLOG("TAF_MMA_SndCTimeInd: ERROR:ALLOC MEMORY FAIL.");
        return VOS_ERR;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstCTimeInd + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_CTIME_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* fill head message info */
    pstCTimeInd->ulReceiverPid = WUEPS_PID_AT;
    pstCTimeInd->ulMsgName     = ID_TAF_MMA_CTIME_IND;
    pstCTimeInd->usClientId    = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_TAF);
    pstCTimeInd->ucOpid        = MMA_OP_ID_INTERNAL;

    PS_MEM_CPY(&(pstCTimeInd->stTimezoneCTime), pstTimezoneCTime, sizeof(TAF_MMA_TIME_ZONE_CTIME_STRU));

    /* send message */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMA, pstCTimeInd))
    {
        MMA_ERRORLOG("TAF_MMA_SndCTimeInd: Send Msg Error!");
        return VOS_ERR;
    }

    return VOS_OK;
}

VOS_UINT32 TAF_MMA_FillCTimeIndStru(
    NAS_MSCC_PIF_1X_SYS_TIME_STRU      *pstSysTime,
    TAF_MMA_TIME_ZONE_CTIME_STRU       *pstTimezoneCTime
)
{
    TAF_STD_TIME_ZONE_TYPE_STRU         stUniversalTimeandLocalTimeZone;
    VOS_UINT32                          ulHighSystemTime;
    VOS_UINT32                          ulLowSystemTime;
    VOS_UINT32                          ulHighTmp;
    VOS_UINT32                          ulLowTmp;
    VOS_UINT32                          ulRemainder;
    VOS_UINT32                          ulRslt;

    ulHighTmp = 0;
    ulLowTmp  = 0;
    ulHighSystemTime = 0;
    ulLowSystemTime  = 0;
    ulRemainder = 0;

    PS_MEM_SET(&stUniversalTimeandLocalTimeZone, 0X00, sizeof(TAF_STD_TIME_ZONE_TYPE_STRU));

    /*
    SYS_TIME - System time.
    The base station shall set this field to the System Time as of
    four Sync Channel superframes (320 ms) after the end of the
    last superframe containing any part of this  Sync Channel
    Message, minus the pilot PN sequence offset, in units of 80
    ms (see 1.3 of [2]).
    */
    TAF_STD_ConvertSystemTimeToHighLow(pstSysTime->aucSysTime, &ulHighSystemTime, &ulLowSystemTime);

    /*
    LTM_OFF - Offset of local time from System Time.
    The base station shall set this field to the two�s complement
    offset of local time from System Time, in units of 30 minutes.
    The local time of day, in units of 80 ms, as of four Sync
    Channel superframes (320 ms) after the end of the last
    superframe containing any part of this Sync Channel Message,
    minus the pilot PN sequence offset, is equal to SYS_TIME -
    (LP_SEC*12.5) + (LTM_OFF *22500).
     */
    ulRslt = TAF_STD_64Sub32(ulHighSystemTime, ulLowSystemTime,
                   (VOS_UINT32)((pstSysTime->ucLpSec * TAF_MMA_MILLISECOND_FOR_ONE_SECOND) / TAF_MMA_EIGHTY_MILLISECOND_UNIT),
                   &ulHighTmp, &ulLowTmp);
    if (VOS_OK != ulRslt)
    {
        return VOS_ERR;
    }
    /* ��system time��������� */
    ulRslt = VOS_64Multi32(ulHighTmp, ulLowTmp, TAF_MMA_EIGHTY_MILLISECOND_UNIT, &ulHighSystemTime, &ulLowSystemTime);
    if (VOS_OK != ulRslt)
    {
        return VOS_ERR;
    }

    ulRslt = VOS_64Div32(ulHighSystemTime, ulLowSystemTime, TAF_MMA_MILLISECOND_FOR_ONE_SECOND, &ulHighTmp, &ulLowTmp, &ulRemainder);
    if (VOS_OK != ulRslt)
    {
        return VOS_ERR;
    }

    /* �ѵ�ǰϵͳ��ʱ��ת���������� ʱ���� */
    ulRslt = TAF_STD_ConvertTimeFromSecsToTimeZone(ulHighTmp, ulLowTmp, &stUniversalTimeandLocalTimeZone);
    if (VOS_OK != ulRslt)
    {
        return VOS_ERR;
    }

    /* ��ǰ��ϵͳʱ����ڵ���2100��ʱ��Ϊ�Ƿ�ֵ��Ŀǰ���㷨�ݲ�֧�ִ��ڵ���2100��ʱ��ת�� */
    if (stUniversalTimeandLocalTimeZone.usYear >= TAF_STD_TIME_ZONE_MAX_YEAR)
    {
        return VOS_ERR;
    }
    pstTimezoneCTime->ucYear   = (VOS_UINT8)(stUniversalTimeandLocalTimeZone.usYear % 100);
    pstTimezoneCTime->ucMonth  = (VOS_UINT8)stUniversalTimeandLocalTimeZone.usMonth;
    pstTimezoneCTime->ucDay    = (VOS_UINT8)stUniversalTimeandLocalTimeZone.usDay;
    pstTimezoneCTime->ucHour   = (VOS_UINT8)stUniversalTimeandLocalTimeZone.usHour;
    pstTimezoneCTime->ucMinute = (VOS_UINT8)stUniversalTimeandLocalTimeZone.usMinute;
    pstTimezoneCTime->ucSecond = (VOS_UINT8)stUniversalTimeandLocalTimeZone.usSecond;

    /*
    LTM_OFF - Offset of local time from System Time.
    The base station shall set this field to the two�s complement
    offset of local time from System Time, in units of 30 minutes.
    The local time of day, in units of 80 ms, as of four Sync
    Channel superframes (320 ms) after the end of the last
    superframe containing any part of this Sync Channel Message,
    minus the pilot PN sequence offset, is equal to SYS_TIME -
    (LP_SEC*12.5) + (LTM_OFF *22500).
     */
    /* ȫ��UTCƫ������ȡֵ��ΧΪUTC-12:00,�� UTC+14:00,��λ:60���ӣ����ά���ٿƵ�ʱ����Ŀ */
    if (!((pstSysTime->cLtmOff >= TAF_MMA_TIME_ZONE_MIN) && (pstSysTime->cLtmOff <= TAF_MMA_TIME_ZONE_MAX)))
    {
        return VOS_ERR;
    }
    else
    {
        pstTimezoneCTime->cTimeZone = pstSysTime->cLtmOff;
    }

    pstTimezoneCTime->ucDayltSavings = pstSysTime->ucDaylt;

    return VOS_OK;
}
/*****************************************************************************
 �� �� ��  : TAF_MMA_ProcessCSystemTime
 ��������  : Process system time
 �������  : XSD_MMA_1X_SYS_TIME_STRU *pstSysTime

 �������  : ��ta
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��26��
    ��    ��   : x00314862
    �޸�����   :
*****************************************************************************/
VOS_VOID TAF_MMA_ProcessCSystemTime(NAS_MSCC_PIF_1X_SYS_TIME_STRU *pstSysTime)
{
    TAF_MMA_TIME_ZONE_CTIME_STRU        stTimezoneCTime;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl;
    VOS_UINT32                          ulRlst;

    pstCurcRptCtrl  = TAF_SDC_GetCurcRptCtrl();

    /* ^CTIME at command controlled by CURC */
    if (VOS_TRUE != TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg, TAF_SDC_CMD_RPT_CTRL_BY_CURC, TAF_SDC_RPT_CMD_CTIME))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_ProcessCSystemTime: TAF_SDC_CheckRptCmdStatus Failed");
        return;
    }

    /* fill the structure of TimeZoneCTime */
    PS_MEM_SET(&stTimezoneCTime, 0x00, sizeof(TAF_MMA_TIME_ZONE_CTIME_STRU));
    ulRlst = TAF_MMA_FillCTimeIndStru(pstSysTime, &stTimezoneCTime);
    if (VOS_OK != ulRlst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_ProcessCSystemTime: TAF_MMA_FillCTimeIndStru Failed");

        /* ��ȡʱ����Ϣʧ��ʱ����80/01/06,00:00:00,+0,00�ϱ� */
        stTimezoneCTime.ucYear          = 80;
        stTimezoneCTime.ucMonth         = 1;
        stTimezoneCTime.ucDay           = 6;
        stTimezoneCTime.ucHour          = 0;
        stTimezoneCTime.ucMinute        = 0;
        stTimezoneCTime.ucSecond        = 0;
        stTimezoneCTime.cTimeZone       = 0;
        stTimezoneCTime.ucDayltSavings  = 0;
    }

    /* send CTime */
    ulRlst = TAF_MMA_SndCTimeInd(&stTimezoneCTime);
    if (VOS_OK != ulRlst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_ProcessCSystemTime: TAF_MMA_SndCTimeInd Failed");
        return;
    }

    return;
}

/* Added by z00316370 for UTS 2015-5-18 begin */
/*****************************************************************************
 �� �� ��  : TAF_MMA_Snd1xChanSetCnf
 ��������  : MMA��AT����channel���õĽ��
 �������  : TAF_MMA_1XCHAN_SET_REQ_STRU *pstCFreqLockSetReq
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��18��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_Snd1xChanSetCnf(
    TAF_MMA_CFREQ_LOCK_SET_REQ_STRU    *pstCFreqLockSetReq,
    VOS_UINT32                          ulRslt
)
{
    TAF_MMA_CFREQ_LOCK_SET_CNF_STRU    *pstCFreqLockSetCnf    = VOS_NULL_PTR;

    pstCFreqLockSetCnf =
            (TAF_MMA_CFREQ_LOCK_SET_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                        sizeof(TAF_MMA_CFREQ_LOCK_SET_CNF_STRU));
    if (VOS_NULL_PTR == pstCFreqLockSetCnf)
    {
        MMA_ERRORLOG("TAF_MMA_Snd1xChanSetCnf: ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstCFreqLockSetCnf + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_CFREQ_LOCK_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ����Ϣ */
    pstCFreqLockSetCnf->ulReceiverPid          = pstCFreqLockSetReq->ulModuleId;
    pstCFreqLockSetCnf->ulMsgName              = ID_TAF_MMA_1XCHAN_SET_CNF;
    pstCFreqLockSetCnf->stCtrl.ulModuleId      = pstCFreqLockSetReq->ulModuleId;
    pstCFreqLockSetCnf->stCtrl.usClientId      = pstCFreqLockSetReq->usClientId;
    pstCFreqLockSetCnf->stCtrl.ucOpId          = pstCFreqLockSetReq->ucOpId;
    pstCFreqLockSetCnf->ulRslt                 = ulRslt;

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstCFreqLockSetCnf);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SndGetStaQryCnf
 ��������  : ��AT����ID_TAF_MMA_CDMACSQ_SET_CNF
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��22��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MMA_SndGetStaQryCnf(
    TAF_MMA_CTRL_STRU                                      *pstCtrl,
    TAF_MMA_HANDSET_STATE_STRU                             *pstHandsetSta,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32                     enRslt
)
{
    TAF_MMA_STATE_QUERY_CNF_STRU       *pstStateCnf   = VOS_NULL_PTR;

    /* ������Ϣ��TAF_MMA_CDMACSQ_SET_CNF_STRU */
    pstStateCnf = (TAF_MMA_STATE_QUERY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           WUEPS_PID_MMA,
                                           sizeof(TAF_MMA_STATE_QUERY_CNF_STRU));

    /* �ڴ�����ʧ�ܣ����� */
    if (VOS_NULL_PTR == pstStateCnf)
    {
        MMA_ERRORLOG("TAF_MMA_SndGetStaQryCnf: ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstStateCnf + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_STATE_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��������������TAF_MMA_STATE_QUERY_CNF_STRU */
    pstStateCnf->ulSenderPid       = WUEPS_PID_MMA;
    pstStateCnf->ulReceiverPid     = pstCtrl->ulModuleId;
    pstStateCnf->ulMsgName         = ID_TAF_MMA_GETSTA_QUERY_CNF;

    pstStateCnf->stAtAppCtrl.usClientId         = pstCtrl->usClientId;
    pstStateCnf->stAtAppCtrl.ucOpId             = pstCtrl->ucOpId;
    pstStateCnf->ulRslt                         = enRslt;

    if (VOS_NULL_PTR != pstHandsetSta)
    {
        PS_MEM_CPY(&(pstStateCnf->stHandsetSta),
                   pstHandsetSta,
                   sizeof(TAF_MMA_HANDSET_STATE_STRU));
    }

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstStateCnf);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SndCHVerQryCnf
 ��������  : ��AT����ID_TAF_MMA_CDMACSQ_SET_CNF
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��22��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MMA_SndCHVerQryCnf(
    TAF_MMA_CTRL_STRU                                      *pstCtrl,
    TAF_MMA_1X_CAS_P_REV_ENUM_UINT8                         enHighRev,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32                     enRslt
)
{
    TAF_MMA_CHIGHVER_QUERY_CNF_STRU    *pstCHVerCnf   = VOS_NULL_PTR;

    /* ������Ϣ��TAF_MMA_CDMACSQ_SET_CNF_STRU */
    pstCHVerCnf = (TAF_MMA_CHIGHVER_QUERY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           WUEPS_PID_MMA,
                                           sizeof(TAF_MMA_CHIGHVER_QUERY_CNF_STRU));

    /* �ڴ�����ʧ�ܣ����� */
    if (VOS_NULL_PTR == pstCHVerCnf)
    {
        MMA_ERRORLOG("TAF_MMA_SndCHVerQryCnf: ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstCHVerCnf + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_CHIGHVER_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��������������TAF_MMA_CHIGHVER_QUERY_CNF_STRU */
    pstCHVerCnf->ulSenderPid       = WUEPS_PID_MMA;
    pstCHVerCnf->ulReceiverPid     = pstCtrl->ulModuleId;
    pstCHVerCnf->ulMsgName         = ID_TAF_MMA_CHIGHVER_QUERY_CNF;

    pstCHVerCnf->stAtAppCtrl.usClientId        = pstCtrl->usClientId;
    pstCHVerCnf->stAtAppCtrl.ucOpId            = pstCtrl->ucOpId;
    pstCHVerCnf->enHighRev                     = enHighRev;
    pstCHVerCnf->ulRslt                        = enRslt;

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstCHVerCnf);

    return;

}
/* Added by z00316370 for UTS 2015-5-18 end */

/* Added by y00322978 for CDMA Iteration 17, 2015-7-10, begin */
/*****************************************************************************
 �� �� ��  : TAF_MMA_SndQuitCallBackCnf
 ��������  : ֪ͨapp�˳�callbackģʽ�Ľ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��10��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_SndQuitCallBackCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode
)
{

    TAF_MMA_QUIT_CALLBACK_SET_CNF_STRU *pstSndMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstSndMsg = (TAF_MMA_QUIT_CALLBACK_SET_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(TAF_MMA_QUIT_CALLBACK_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstSndMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndQuitCallBackCnf:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(TAF_MMA_QUIT_CALLBACK_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);


    /* ��������������TAF_MMA_CDMACSQ_SET_CNF_STRU */
    pstSndMsg->ulSenderPid       = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverPid     = WUEPS_PID_AT;
    pstSndMsg->ulMsgName         = ID_TAF_MMA_QUIT_CALLBACK_SET_CNF;
    pstSndMsg->enErrorCode       = enErrorCode;

    PS_MEM_CPY(&(pstSndMsg->stCtrl), pstCtrl, sizeof(TAF_MMA_CTRL_STRU));

    /* ����VOS����ԭ�� */
    PS_SEND_MSG( WUEPS_PID_MMA, pstSndMsg );

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SndSetCSidListCnf
 ��������  : set csidlist ��Ϣ ����mma�ķ��ͺ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��13��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_SndSetCSidListCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode
)
{
    TAF_MMA_CSIDLIST_SET_CNF_STRU      *pstSndMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstSndMsg = (TAF_MMA_CSIDLIST_SET_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(TAF_MMA_CSIDLIST_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstSndMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndQuitCallBackCnf:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(TAF_MMA_CSIDLIST_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);


    /* ��������������TAF_MMA_CDMACSQ_SET_CNF_STRU */
    pstSndMsg->ulSenderPid       = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverPid     = WUEPS_PID_AT;
    pstSndMsg->ulMsgName         = ID_TAF_MMA_CSIDLIST_SET_CNF;
    pstSndMsg->enErrorCode       = enErrorCode;

    PS_MEM_CPY(&(pstSndMsg->stCtrl), pstCtrl, sizeof(TAF_MMA_CTRL_STRU));

    /* ����VOS����ԭ�� */
    PS_SEND_MSG( WUEPS_PID_MMA, pstSndMsg );
}
/* Added by y00322978 for CDMA Iteration 17, 2015-7-10, end */

#endif

VOS_VOID TAF_MMA_BuildRssiInd(
    TAF_MMA_RSSI_INFO_IND_STRU         *pstRssiInd
)
{
    TAF_SDC_APPNETWORK_INFO            *pstAppNwInfo              = VOS_NULL_PTR;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enAppSysMode;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl           = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl    = VOS_NULL_PTR;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    /* ���������ϱ����ȫ�ֱ�����ֵ */
    PS_MEM_CPY(pstRssiInd->aucCurcRptCfg, pstCurcRptCtrl->aucRptCfg, TAF_MMA_RPT_CFG_MAX_SIZE);
    PS_MEM_CPY(pstRssiInd->aucUnsolicitedRptCfg, pstUnsolicitedRptCtrl->aucRptCfg, TAF_MMA_RPT_CFG_MAX_SIZE);

    pstAppNwInfo  = TAF_SDC_GetAppNetworkInfo();
    enAppSysMode  = TAF_SDC_GetAppSysMode();

    /*�����ϱ�һ��С���������Ϣ*/
    pstRssiInd->stRssiInfo.ucRssiNum = 1;
    pstRssiInd->stRssiInfo.enRatType              = TAF_SDC_GetAppSysMode();
    pstRssiInd->stRssiInfo.ucCurrentUtranMode     = TAF_SDC_GetAppUtranMode();
    pstRssiInd->stRssiInfo.aRssi[0].ucChannalQual = pstAppNwInfo->stRssiValue.ucChannalQual;

    switch(enAppSysMode)
    {
        case TAF_SDC_SYS_MODE_GSM:
             pstRssiInd->stRssiInfo.aRssi[0].u.stGCellSignInfo.sRssiValue = pstAppNwInfo->stRssiValue.u.st2GCellSignInfo.sRssiValue;

             MMA_GetRssiLevelFromValue(pstAppNwInfo->stRssiValue.u.st2GCellSignInfo.sRssiValue,
                                     &(pstRssiInd->stRssiInfo.aRssi[0].ucRssiValue));

            break;

        case TAF_SDC_SYS_MODE_WCDMA:
             pstRssiInd->stRssiInfo.aRssi[0].u.stWCellSignInfo.sRscpValue = pstAppNwInfo->stRssiValue.u.st3GCellSignInfo.sRscpValue;
             pstRssiInd->stRssiInfo.aRssi[0].u.stWCellSignInfo.sEcioValue = pstAppNwInfo->stRssiValue.u.st3GCellSignInfo.sEcioValue;

             MMA_GetRssiLevelFromValue(pstAppNwInfo->stRssiValue.u.st3GCellSignInfo.sRscpValue,
                                     &(pstRssiInd->stRssiInfo.aRssi[0].ucRssiValue));

            break;

#if (FEATURE_ON == FEATURE_LTE)
        case TAF_SDC_SYS_MODE_LTE:
             pstRssiInd->stRssiInfo.aRssi[0].ucChannalQual                     = TAF_PH_BER_UNKNOWN;
             pstRssiInd->stRssiInfo.aRssi[0].u.stLCellSignInfo.sRssi           = pstAppNwInfo->stRssiValue.u.st4GCellSignInfo.sRssi;
             pstRssiInd->stRssiInfo.aRssi[0].u.stLCellSignInfo.sRsd            = pstAppNwInfo->stRssiValue.u.st4GCellSignInfo.sRsd;
             pstRssiInd->stRssiInfo.aRssi[0].u.stLCellSignInfo.sRsrp           = pstAppNwInfo->stRssiValue.u.st4GCellSignInfo.sRsrp;
             pstRssiInd->stRssiInfo.aRssi[0].u.stLCellSignInfo.sRsrq           = pstAppNwInfo->stRssiValue.u.st4GCellSignInfo.sRsrq;
             pstRssiInd->stRssiInfo.aRssi[0].u.stLCellSignInfo.lSINR           = pstAppNwInfo->stRssiValue.u.st4GCellSignInfo.lSINR;
             pstRssiInd->stRssiInfo.aRssi[0].u.stLCellSignInfo.stCQI.usRI      = pstAppNwInfo->stRssiValue.u.st4GCellSignInfo.stCQI.usRI;
             pstRssiInd->stRssiInfo.aRssi[0].u.stLCellSignInfo.stCQI.ausCQI[0] = pstAppNwInfo->stRssiValue.u.st4GCellSignInfo.stCQI.ausCQI[0];
             pstRssiInd->stRssiInfo.aRssi[0].u.stLCellSignInfo.stCQI.ausCQI[1] = pstAppNwInfo->stRssiValue.u.st4GCellSignInfo.stCQI.ausCQI[1];

             TAF_MMA_GetRssiLevelFromLteRssi(pstAppNwInfo->stRssiValue.u.st4GCellSignInfo.sRssi,
                                           &(pstRssiInd->stRssiInfo.aRssi[0].ucRssiValue));

            break;
#endif

        default:
            MMA_ERRORLOG("TAF_MMA_BuildRssiInd:RAT is INVALID.");
            break;
    }

    return;
}


VOS_VOID TAF_MMA_SndAtRssiInd(VOS_VOID)
{
    TAF_MMA_RSSI_INFO_IND_STRU          *pstRssiInd;

    if (VOS_TRUE != TAF_MMA_IsRssiChangeNeedRpt())
    {
        return;
    }

    pstRssiInd = (TAF_MMA_RSSI_INFO_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                            sizeof(TAF_MMA_RSSI_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstRssiInd)
    {
        MMA_ERRORLOG("TAF_MMA_SndAtRssiInd:ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstRssiInd + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_RSSI_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ����Ϣ */
    pstRssiInd->ulReceiverPid             = WUEPS_PID_AT;
    pstRssiInd->ulMsgName                 = ID_TAF_MMA_RSSI_INFO_IND;
    pstRssiInd->usClientId                = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_TAF);
    pstRssiInd->ucOpId                    = MMA_OP_ID_INTERNAL;

    TAF_MMA_BuildRssiInd(pstRssiInd);

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstRssiInd);

    return;
}
/*lint +e429*/

/* Added by x00314862 for CDMA 1X Iteration 6 2014-12-26 end */


#if (FEATURE_ON == FEATURE_IMS)

VOS_VOID TAF_MMA_SndImsSwitchSetCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enResult,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
)
{
    TAF_MMA_IMS_SWITCH_SET_CNF_STRU    *pstSndMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstSndMsg = (TAF_MMA_IMS_SWITCH_SET_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMA,
                                             sizeof(TAF_MMA_IMS_SWITCH_SET_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndImsSwitchSetCnf:Alloc Msg Failed");

        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0,
               sizeof(TAF_MMA_IMS_SWITCH_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_IMS_SWITCH_SET_CNF;
    pstSndMsg->usClientId               = pstCtrl->usClientId;
    pstSndMsg->ucOpid                   = pstCtrl->ucOpId;
    pstSndMsg->enResult                 = enResult;
    pstSndMsg->enErrorCause             = enErrorCause;

    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);
    if (VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndImsSwitchSetCnf:Send Msg Failed");
    }

    return;
}



VOS_VOID TAF_MMA_SndImsSwitchQryCnf(
    TAF_MMA_CTRL_STRU                          *pstCtrl,
    VOS_UINT8                                   ucImsSwitch
)
{
    TAF_MMA_IMS_SWITCH_QRY_CNF_STRU    *pstSndMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstSndMsg = (TAF_MMA_IMS_SWITCH_QRY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMA,
                                             sizeof(TAF_MMA_IMS_SWITCH_QRY_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndImsSwitchQryCnf:Alloc Msg Failed");

        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0,
               sizeof(TAF_MMA_IMS_SWITCH_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_IMS_SWITCH_QRY_CNF;
    pstSndMsg->usClientId               = pstCtrl->usClientId;
    pstSndMsg->ucOpid                   = pstCtrl->ucOpId;
    pstSndMsg->enImsSwitch              = ucImsSwitch;

    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);
    if (VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndImsSwitchSetCnf:Send Msg Failed");

        return;
    }

    return;
}
#endif


VOS_VOID TAF_MMA_SndVoiceDomainSetCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enResult,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
)
{
    TAF_MMA_VOICE_DOMAIN_SET_CNF_STRU  *pstSndMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstSndMsg = (TAF_MMA_VOICE_DOMAIN_SET_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMA,
                                             sizeof(TAF_MMA_VOICE_DOMAIN_SET_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndVoiceDomainSetCnf:Alloc Msg Failed");

        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0,
               sizeof(TAF_MMA_VOICE_DOMAIN_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_VOICE_DOMAIN_SET_CNF;
    pstSndMsg->usClientId               = pstCtrl->usClientId;
    pstSndMsg->ucOpid                   = pstCtrl->ucOpId;
    pstSndMsg->enResult                 = enResult;
    pstSndMsg->enErrorCause             = enErrorCause;

    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);
    if (VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndVoiceDomainSetCnf:Send Msg Failed");

        return;
    }

    return;
}


VOS_VOID TAF_MMA_SndVoiceDomainQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_VOICE_DOMAIN_ENUM_UINT32    enVoiceDomain
)
{
    TAF_MMA_VOICE_DOMAIN_QRY_CNF_STRU  *pstSndMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstSndMsg = (TAF_MMA_VOICE_DOMAIN_QRY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMA,
                                             sizeof(TAF_MMA_VOICE_DOMAIN_QRY_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndVoiceDomainQryCnf:Alloc Msg Failed");

        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0,
               sizeof(TAF_MMA_VOICE_DOMAIN_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_VOICE_DOMAIN_QRY_CNF;
    pstSndMsg->usClientId               = pstCtrl->usClientId;
    pstSndMsg->ucOpid                   = pstCtrl->ucOpId;
    pstSndMsg->enVoiceDomain            = enVoiceDomain;

    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);
    if (VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndVoiceDomainQryCnf:Send Msg Failed");

        return;
    }

    return;
}



VOS_VOID TAF_MMA_SndCFPlmnSetCnf(
    TAF_MMA_CTRL_STRU                                      *pstCtrl,
    TAF_MMA_APP_CFPLMN_OPER_RESULT_ENUM_UINT32              enRslt
)
{
    TAF_MMA_CFPLMN_SET_CNF_STRU        *pstSndMsg = VOS_NULL_PTR;

    pstSndMsg = (TAF_MMA_CFPLMN_SET_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                               WUEPS_PID_MMA,
                                               sizeof(TAF_MMA_CFPLMN_SET_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndCFPlmnSetCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
               sizeof(TAF_MMA_CFPLMN_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_CFPLMN_SET_CNF;

    PS_MEM_CPY(&pstSndMsg->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));

    pstSndMsg->enRslt                   = enRslt;

    PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);
    return;
}


VOS_VOID TAF_MMA_SndCFPlmnQueryCnf(
    TAF_MMA_CTRL_STRU                                      *pstCtrl,
    TAF_MMA_APP_CFPLMN_OPER_RESULT_ENUM_UINT32              enRslt,
    MSCC_MMA_CFPLMN_QUERY_CNF_STRU                         *pstCFPlmnCnfMsg
)
{
    TAF_MMA_CFPLMN_QUERY_CNF_STRU      *pstSndMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulLoop;

    pstSndMsg = (TAF_MMA_CFPLMN_QUERY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                 WUEPS_PID_MMA,
                                                 sizeof(TAF_MMA_CFPLMN_QUERY_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndCFPlmnQueryCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
               sizeof(TAF_MMA_CFPLMN_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_CFPLMN_QUERY_CNF;

    PS_MEM_CPY(&pstSndMsg->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));

    pstSndMsg->enRslt                   = enRslt;

    if (VOS_NULL_PTR != pstCFPlmnCnfMsg)
    {
        pstSndMsg->usPlmnNum = pstCFPlmnCnfMsg->ucPlmnNum;

        if (pstSndMsg->usPlmnNum > NAS_MSCC_PIF_MAX_CFPLMN_NUM)
        {
            pstSndMsg->usPlmnNum = NAS_MSCC_PIF_MAX_CFPLMN_NUM;
        }

        for (ulLoop = 0; ulLoop < pstSndMsg->usPlmnNum; ulLoop++)
        {
            pstSndMsg->astPlmn[ulLoop].Mcc = pstCFPlmnCnfMsg->astPlmn[ulLoop].ulMcc;
            pstSndMsg->astPlmn[ulLoop].Mnc = pstCFPlmnCnfMsg->astPlmn[ulLoop].ulMnc;

            /* PLMN��ʽת�� */
            MMA_PlmnId2Bcd(&pstSndMsg->astPlmn[ulLoop]);
        }
    }

    PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);
    return;
}
VOS_VOID TAF_MMA_ProcPlmnAutoReselCnf(
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
)
{
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    /* ��ȫ�ֱ���g_stTafMmaCtx.astMmaOperCtx����ID_TAF_MMA_PLMN_AUTO_RESEL_REQ��Ӧ�ļ�¼�� */
    if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_PLMN_AUTO_RESEL_REQ, &ucCtxIndex))
    {
        /*  �ظ�AutoReselSetCnf */
        TAF_MMA_SndPlmnAutoReselCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl), enErrorCause);

        TAF_MMA_ClearOperCtx(ucCtxIndex);
    }

    return;
}

VOS_VOID TAF_MMA_SndPlmnAutoReselCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode
)
{
    TAF_MMA_PLMN_AUTO_RESEL_CNF_STRU   *pstSndMsg = VOS_NULL_PTR;

    pstSndMsg = (TAF_MMA_PLMN_AUTO_RESEL_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                    WUEPS_PID_MMA,
                                                    sizeof(TAF_MMA_PLMN_AUTO_RESEL_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndPlmnAutoReselCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
               sizeof(TAF_MMA_PLMN_AUTO_RESEL_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_PLMN_AUTO_RESEL_CNF;
    PS_MEM_CPY(&pstSndMsg->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));
    pstSndMsg->enErrorCause             = enErrorCode;

    PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);
    return;
}


VOS_VOID TAF_MMA_ProcPlmnSpecialSelCnf(
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
)
{
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    /* ��ȫ�ֱ���g_stTafMmaCtx.astMmaOperCtx����ID_TAF_MMA_PLMN_SPECIAL_SEL_REQ��Ӧ�ļ�¼�� */
    if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_PLMN_SPEC_SEL_REQ, &ucCtxIndex))
    {
        /*  �ظ�plmn special sel CNF */
        TAF_MMA_SndPlmnSpecialSelCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl), enErrorCause);

        TAF_MMA_ClearOperCtx(ucCtxIndex);
    }

    return;
}

VOS_VOID TAF_MMA_SndPlmnSpecialSelCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode
)
{
    TAF_MMA_PLMN_SPECIAL_SEL_CNF_STRU  *pstSndMsg = VOS_NULL_PTR;

    pstSndMsg = (TAF_MMA_PLMN_SPECIAL_SEL_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                               WUEPS_PID_MMA,
                                               sizeof(TAF_MMA_PLMN_SPECIAL_SEL_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndPlmnSpecialSelCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
               sizeof(TAF_MMA_PLMN_SPECIAL_SEL_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_PLMN_SPECIAL_SEL_CNF;
    PS_MEM_CPY(&pstSndMsg->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));
    pstSndMsg->enErrorCause             = enErrorCode;

    PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);
    return;
}

VOS_VOID TAF_MMA_SndPlmnListAbortCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode
)
{
    TAF_MMA_PLMN_LIST_ABORT_CNF_STRU   *pstSndMsg = VOS_NULL_PTR;

    pstSndMsg = (TAF_MMA_PLMN_LIST_ABORT_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                               WUEPS_PID_MMA,
                                               sizeof(TAF_MMA_PLMN_LIST_ABORT_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndPlmnListAbortCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
               sizeof(TAF_MMA_PLMN_LIST_ABORT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulReceiverPid            = WUEPS_PID_AT;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_PLMN_LIST_ABORT_CNF;
    PS_MEM_CPY(&pstSndMsg->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));
    pstSndMsg->enErrorCause             = enErrorCode;

    PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);
    return;
}

VOS_VOID TAF_MMA_ProcPlmnListAbortCnf(
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode
)
{
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    /* ��ȫ�ֱ���g_stTafMmaCtx.astMmaOperCtx����ID_TAF_MMA_PLMN_LIST_ABORT_REQ��Ӧ�ļ�¼�� */
    if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_PLMN_LIST_ABORT_REQ, &ucCtxIndex))
    {
        /*  �ظ�MMA_CFPLMN_CNF */
        TAF_MMA_SndPlmnListAbortCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl), enErrorCode);

        TAF_MMA_ClearOperCtx(ucCtxIndex);

        if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_PLMN_LIST_REQ, &ucCtxIndex))
        {
            TAF_MMA_ClearOperCtx(ucCtxIndex);
            return;
        }
    }

    return;
}


VOS_VOID TAF_MMA_SndLocInfoQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_LOCATION_INFO_QRY_CNF_STRU *pstLocInfoQryCnfMsg
)
{
    TAF_MMA_LOCATION_INFO_QRY_CNF_STRU       *pstSndMsg = VOS_NULL_PTR;

    pstSndMsg = (TAF_MMA_LOCATION_INFO_QRY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                      WUEPS_PID_MMA,
                                                      sizeof(TAF_MMA_LOCATION_INFO_QRY_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndLocInfoQryCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
               sizeof(TAF_MMA_LOCATION_INFO_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_LOCATION_INFO_QRY_CNF;
    PS_MEM_CPY(&pstSndMsg->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));
    pstSndMsg->ulResult                 = pstLocInfoQryCnfMsg->ulResult;
    pstSndMsg->ulMcc                    = pstLocInfoQryCnfMsg->ulMcc;
    pstSndMsg->ulMnc                    = pstLocInfoQryCnfMsg->ulMnc;
    pstSndMsg->usLac                    = pstLocInfoQryCnfMsg->usLac;
    pstSndMsg->ucRac                    = pstLocInfoQryCnfMsg->ucRac;
    pstSndMsg->ucRsv                    = pstLocInfoQryCnfMsg->ucRsv;
    pstSndMsg->ulCellid                 = pstLocInfoQryCnfMsg->ulCellid;

    PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    return;
}

VOS_VOID TAF_MMA_SndPrefPlmnTypeSetCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause,
    MN_PH_PREF_PLMN_TYPE_ENUM_U8        enPrefPlmnType
)
{
    TAF_MMA_PREF_PLMN_TYPE_SET_CNF_STRU          *pstSndMsg = VOS_NULL_PTR;

    pstSndMsg = (TAF_MMA_PREF_PLMN_TYPE_SET_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                       WUEPS_PID_MMA,
                                                       sizeof(TAF_MMA_PREF_PLMN_TYPE_SET_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndPrefPlmnTypeSetCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
               sizeof(TAF_MMA_PREF_PLMN_TYPE_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_PREF_PLMN_TYPE_SET_CNF;

    PS_MEM_CPY(&pstSndMsg->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));

    pstSndMsg->enErrorCause             = enErrorCause;
    pstSndMsg->enPrefPlmnType           = enPrefPlmnType;

    PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    return;
}

VOS_VOID TAF_MMA_SndMtPowrDownCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
)
{
    TAF_MMA_MT_POWER_DOWN_CNF_STRU     *pstSndMsg = VOS_NULL_PTR;

    pstSndMsg = (TAF_MMA_MT_POWER_DOWN_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                 WUEPS_PID_MMA,
                                                 sizeof(TAF_MMA_MT_POWER_DOWN_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndMtPowrDownCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
               sizeof(TAF_MMA_MT_POWER_DOWN_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_MT_POWER_DOWN_CNF;
    pstSndMsg->enErrorCause             = enErrorCause;

    PS_MEM_CPY(&pstSndMsg->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));

    PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    return;
}
/* Added by y00307564 for CDMA Iteration 8 2015-2-5 begin */
/*****************************************************************************
 �� �� ��  : TAF_MMA_SndPrefPlmnQueryCnf
 ��������  : ����prefplmn query cnf��Ϣ��taf
 �������  : TAF_MMA_CTRL_STRU                                          *pstCtrl,
             TAF_MMA_APP_PREF_PLMN_OPER_RESULT_ENUM_UINT32               enRslt
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��05��
    ��    ��   : y00307564
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_SndPrefPlmnSetCnf(
    TAF_MMA_CTRL_STRU                                      *pstCtrl,
    TAF_MMA_APP_PREF_PLMN_OPER_RESULT_ENUM_UINT32           enRslt
)
{
    TAF_MMA_PREF_PLMN_SET_CNF_STRU     *pstPrefPlmnCnf   = VOS_NULL_PTR;

    /* ������Ϣ��TAF_MMA_PREF_PLMN_SET_CNF_STRU */
    pstPrefPlmnCnf = (TAF_MMA_PREF_PLMN_SET_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           WUEPS_PID_MMA,
                                           sizeof(TAF_MMA_PREF_PLMN_SET_CNF_STRU));

    /* �ڴ�����ʧ�ܣ����� */
    if (VOS_NULL_PTR == pstPrefPlmnCnf)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndPrefPlmnSetCnf ERROR: Memory Alloc Error for pstPrefPlmnCnf");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstPrefPlmnCnf + VOS_MSG_HEAD_LENGTH, 0X00,
        sizeof(TAF_MMA_PREF_PLMN_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��������������TAF_MMA_PREF_PLMN_SET_CNF_STRU */
    pstPrefPlmnCnf->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstPrefPlmnCnf->ulSenderPid       = WUEPS_PID_MMA;
    pstPrefPlmnCnf->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstPrefPlmnCnf->ulReceiverPid     = pstCtrl->ulModuleId;
    pstPrefPlmnCnf->ulMsgName         = ID_TAF_MMA_PREF_PLMN_SET_CNF;

    pstPrefPlmnCnf->usClientId        = pstCtrl->usClientId;
    pstPrefPlmnCnf->ucOpId            = pstCtrl->ucOpId;
    pstPrefPlmnCnf->enRslt            = enRslt;

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstPrefPlmnCnf);

    return;
}
/*****************************************************************************
 �� �� ��  : TAF_MMA_SndPrefPlmnQueryCnf
 ��������  : ����prefplmn query cnf��Ϣ��taf
 �������  : TAF_MMA_CTRL_STRU                                      *pstCtrl,
             TAF_MMA_APP_PREF_PLMN_OPER_RESULT_ENUM_UINT32           enRslt,
             MSCC_MMA_PREF_PLMN_QUERY_CNF_STRU                      *pstRcvMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��05��
    ��    ��   : y00307564
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_SndPrefPlmnQueryCnf(
    TAF_MMA_CTRL_STRU                                      *pstCtrl,
    TAF_MMA_APP_PREF_PLMN_OPER_RESULT_ENUM_UINT32           enRslt,
    MSCC_MMA_PREF_PLMN_QUERY_CNF_STRU                      *pstRcvMsg
)
{
    TAF_MMA_PREF_PLMN_QUERY_CNF_STRU                       *pstPrefPlmnCnf      = VOS_NULL_PTR;
    TAF_PH_OPERATOR_NAME_FORMAT_OP_STRU                     stOperName;
    VOS_UINT32                                              i;

    /* �����ڴ�  */
    pstPrefPlmnCnf = (TAF_MMA_PREF_PLMN_QUERY_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(TAF_MMA_PREF_PLMN_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstPrefPlmnCnf)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndPrefPlmnQueryCnf ERROR: Memory Alloc Error for pstPrefPlmnCnf");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstPrefPlmnCnf + VOS_MSG_HEAD_LENGTH, 0,
                           sizeof(TAF_MMA_PREF_PLMN_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ����Ϣ */
    pstPrefPlmnCnf->ulSenderCpuId          = VOS_LOCAL_CPUID;
    pstPrefPlmnCnf->ulSenderPid            = WUEPS_PID_MMA;
    pstPrefPlmnCnf->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstPrefPlmnCnf->ulReceiverPid          = pstCtrl->ulModuleId;
    pstPrefPlmnCnf->ulMsgName              = ID_TAF_MMA_PREF_PLMN_QUERY_CNF;

    /* ��д��Ϣ�� */
    pstPrefPlmnCnf->usClientId             = pstCtrl->usClientId;
    pstPrefPlmnCnf->ucOpId                 = pstCtrl->ucOpId;
    pstPrefPlmnCnf->enRslt                 = enRslt;

    if (VOS_NULL_PTR != pstRcvMsg)
    {
        /* ��д��Ϣ�� */
        pstPrefPlmnCnf->ulFromIndex            = pstRcvMsg->ulFromIndex;
        pstPrefPlmnCnf->ulValidPlmnNum         = pstRcvMsg->ulValidPlmnNum;

        PS_MEM_CPY(&(pstPrefPlmnCnf->stPlmnName), &(pstRcvMsg->stPlmnName), sizeof(TAF_PLMN_NAME_LIST_STRU));

        for (i = 0; i < pstPrefPlmnCnf->stPlmnName.ulPlmnNum; i++ )
        {
            /* ���ں˼�ͨ�����ֻ�ܴ�4K�����Բ��ܻ�ȡ���е����������б�ĳ�������*/
            PS_MEM_SET(&stOperName, 0, sizeof(stOperName));
            stOperName.OperName.PlmnId.Mcc  = pstPrefPlmnCnf->stPlmnName.astPlmnName[i].PlmnId.Mcc;
            stOperName.OperName.PlmnId.Mnc  = pstPrefPlmnCnf->stPlmnName.astPlmnName[i].PlmnId.Mnc;
            stOperName.ListOp               = TAF_PH_OPER_NAME_PLMN2ALPHANUMERICNAME;

            /* ��ȡ��������ĳ����� */
            if (MMA_SUCCESS == Taf_PhoneGetNetworkNameForListPlmn(&stOperName))
            {
                PS_MEM_CPY(pstPrefPlmnCnf->stPlmnName.astPlmnName[i].aucOperatorNameLong,
                           stOperName.OperName.aucOperatorNameLong,
                           TAF_PH_OPER_NAME_LONG);

                PS_MEM_CPY(pstPrefPlmnCnf->stPlmnName.astPlmnName[i].aucOperatorNameShort,
                           stOperName.OperName.aucOperatorNameShort,
                           TAF_PH_OPER_NAME_SHORT);
            }
            else
            {
                pstPrefPlmnCnf->stPlmnName.astPlmnName[i].aucOperatorNameLong[0]  = '\0';
                pstPrefPlmnCnf->stPlmnName.astPlmnName[i].aucOperatorNameShort[0] = '\0';
            }

        }

    }

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstPrefPlmnCnf);

    return;

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SndPrefPlmnTestCnf
 ��������  : ����prefplmn test cnf��Ϣ��taf
 �������  : TAF_MMA_CTRL_STRU                                      *pstCtrl,
             TAF_MMA_APP_PREF_PLMN_OPER_RESULT_ENUM_UINT32           enRslt,
             MSCC_MMA_PREF_PLMN_QUERY_CNF_STRU                      *pstRcvMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��05��
    ��    ��   : y00307564
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_SndPrefPlmnTestCnf(
    TAF_MMA_CTRL_STRU                                      *pstCtrl,
    TAF_MMA_APP_PREF_PLMN_OPER_RESULT_ENUM_UINT32           enRslt,
    MSCC_MMA_PREF_PLMN_QUERY_CNF_STRU                      *pstRcvMsg
)
{
    TAF_MMA_PREF_PLMN_TEST_CNF_STRU    *pstPrefPlmnCnf      = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstPrefPlmnCnf = (TAF_MMA_PREF_PLMN_TEST_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(TAF_MMA_PREF_PLMN_TEST_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstPrefPlmnCnf)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndPrefPlmnTestCnf ERROR: Memory Alloc Error for pstPrefPlmnCnf");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstPrefPlmnCnf + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(TAF_MMA_PREF_PLMN_TEST_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ����Ϣ */
    pstPrefPlmnCnf->ulSenderCpuId          = VOS_LOCAL_CPUID;
    pstPrefPlmnCnf->ulSenderPid            = WUEPS_PID_MMA;
    pstPrefPlmnCnf->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstPrefPlmnCnf->ulReceiverPid          = pstCtrl->ulModuleId;
    pstPrefPlmnCnf->ulMsgName              = ID_TAF_MMA_PREF_PLMN_TEST_CNF;

    /* �����Ϣ�� */
    pstPrefPlmnCnf->usClientId             = pstCtrl->usClientId;
    pstPrefPlmnCnf->ucOpId                 = pstCtrl->ucOpId;
    pstPrefPlmnCnf->enRslt                 = enRslt;

    if (VOS_NULL_PTR != pstRcvMsg)
    {
        /* �����Ϣ�� */
        pstPrefPlmnCnf->usPlmnNum          = pstRcvMsg->usPlmnNum;
    }

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstPrefPlmnCnf);

    return;
}

/* Added by y00307564 for CDMA Iteration 8 2015-2-5 end */


VOS_VOID TAF_MMA_SndAtRegStatus(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId,
    NAS_MSCC_PIF_REG_STATE_ENUM_UINT8   enRegState
)
{
    TAF_SDC_PLMN_ID_STRU               *pstPlmnId     = VOS_NULL_PTR;

    TAF_PH_REG_STATE_STRU               stRegStatus;

    pstPlmnId     = TAF_SDC_GetCurrCampPlmnId();

    PS_MEM_SET(&stRegStatus, 0, sizeof(TAF_PH_REG_STATE_STRU));

    /* ��дCREG/CGREG��Ӧ��OP�� */
    if (NAS_MSCC_PIF_SRVDOMAIN_CS == enCnDomainId)
    {
        stRegStatus.OP_CsRegState = VOS_TRUE;
        stRegStatus.OP_Lac        = VOS_TRUE;
        stRegStatus.OP_CellId     = VOS_TRUE;
        stRegStatus.OP_ucAct      = VOS_TRUE;
        stRegStatus.RegState      = enRegState;
    }
    else if (NAS_MSCC_PIF_SRVDOMAIN_PS == enCnDomainId)
    {
        stRegStatus.OP_PsRegState = VOS_TRUE;
        stRegStatus.OP_Lac        = VOS_TRUE;
        stRegStatus.OP_Rac        = VOS_TRUE;
        stRegStatus.OP_CellId     = VOS_TRUE;
        stRegStatus.OP_ucAct      = VOS_TRUE;
        stRegStatus.ucPsRegState  = enRegState;
    }
    else
    {
        /* ��������Ĳ��ԣ��ͷ��Ѿ�������ڴ�ռ䣬ֱ�ӷ��� */
        return;
    }

    /* פ����Ϣ */
    stRegStatus.ucRac               = TAF_SDC_GetCurrCampRac();
    stRegStatus.CellId.ucCellNum    = 1;
    stRegStatus.CellId.aulCellId[0] = TAF_SDC_GetCurrCampCellId();
    stRegStatus.usLac               = TAF_SDC_GetCurrCampLac();

    PS_MEM_CPY(&stRegStatus.Plmn, pstPlmnId, sizeof(TAF_PLMN_ID_STRU));

    /* ��MMC�ϱ���ϵͳ��ģʽתΪ+CREG/+CGREG�������[ACT]��Э��涨�Ľ��뼼��ֵ */
    NAS_MMA_TransferSysSubMode2ActForAtCmdCreg(TAF_SDC_GetSysSubMode(), &(stRegStatus.ucAct));

    switch (TAF_SDC_GetCampSysMode())
    {
#if (FEATURE_ON == FEATURE_LTE)
        case TAF_SDC_SYS_MODE_LTE:
            stRegStatus.ucRatType = TAF_PH_INFO_LTE_RAT;
            break;
#endif

        case TAF_SDC_SYS_MODE_WCDMA:
            stRegStatus.ucRatType = TAF_PH_INFO_WCDMA_RAT;
            break;

        case TAF_SDC_SYS_MODE_GSM:
            stRegStatus.ucRatType = TAF_PH_INFO_GSM_RAT;
            break;

        default:
            stRegStatus.ucRatType = TAF_PH_INFO_NONE_RAT;
            break;
    }

    if (VOS_TRUE != TAF_MMA_IsRegStatusChangeNeedRpt(&stRegStatus))
    {
        return;
    }

    TAF_MMA_RecordRegStatusReportFlag(enCnDomainId, enRegState);

    TAF_MMA_SndRegStatusInd(&stRegStatus);

    return;
}
/* Added by h00313353 for iteration 9, 2015-2-7, begin */
/*****************************************************************************
 �� �� ��  : TAF_MMA_GetCardInfo
 ��������  : ������Ϣ��Usim��Csim��״̬�Ϳ�����ѡ���ϱ���AT������
 �������  : USIMM_CARDSTATUS_IND_STRU *pStPsUsimStatusInd: ��Ϣ�ṹ��
 �������  : USIMM_CARD_TYPE_ENUM_UINT32 enCardType: ������
             USIMM_CARD_SERVIC_ENUM_UINT32 enCardStatus: ��״̬
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��7��
    ��    ��   : h00313353
    �޸�����   : ��������

*****************************************************************************/
VOS_VOID TAF_MMA_GetCardInfo(
    USIMM_CARDSTATUS_IND_STRU          *pStPsUsimStatusInd,
    USIMM_CARD_TYPE_ENUM_UINT32        *enCardType,
    USIMM_CARD_SERVIC_ENUM_UINT32      *enCardStatus
)
{
    /* ���USIMӦ�ÿ��ã�ȡUSIM״̬ */
    if (USIMM_CARD_SERVIC_AVAILABLE == pStPsUsimStatusInd->stUsimSimInfo.enCardService)
    {

        *enCardStatus    = USIMM_CARD_SERVIC_AVAILABLE;
        *enCardType      = pStPsUsimStatusInd->stUsimSimInfo.enCardType;
    }
    else if (USIMM_CARD_SERVIC_ABSENT != pStPsUsimStatusInd->stUsimSimInfo.enCardService)
    {
        /* ���CSIM���ã�ȡCSIM״̬ */
        if (USIMM_CARD_SERVIC_AVAILABLE == pStPsUsimStatusInd->stCsimUimInfo.enCardService)
        {
            *enCardStatus    = USIMM_CARD_SERVIC_AVAILABLE;
            *enCardType      = pStPsUsimStatusInd->stCsimUimInfo.enCardType;
        }
        else
        {
            /* ���USIM���ǲ����ڣ�ȡUSIM״̬ */
            *enCardStatus    = pStPsUsimStatusInd->stUsimSimInfo.enCardService;
            *enCardType      = pStPsUsimStatusInd->stUsimSimInfo.enCardType;
        }
    }
    else
    {
        /* ���USIM�����ڣ�CSIM���ǲ����ڣ�ȡCSIM״̬ */
        if (USIMM_CARD_SERVIC_ABSENT != pStPsUsimStatusInd->stCsimUimInfo.enCardService)
        {
            *enCardStatus    = pStPsUsimStatusInd->stCsimUimInfo.enCardService;
            *enCardType      = pStPsUsimStatusInd->stCsimUimInfo.enCardType;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SndATUsimmStatusInd
 ��������  : ��AT���Ϳ�״̬��Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��7��
    ��    ��   : h00313353
    �޸�����   : ��������

*****************************************************************************/
VOS_VOID TAF_MMA_SndATUsimmStatusInd(
    USIMM_CARDSTATUS_IND_STRU          *pStPsUsimStatusInd,
    VOS_UINT8                          *pucIMSI
)
{
    AT_MMA_USIM_STATUS_IND_STRU        *pstAtMmaUsimStatusIndMsg;
    USIMM_CARD_TYPE_ENUM_UINT32         enCardType;
    USIMM_CARD_SERVIC_ENUM_UINT32       enCardStatus;

    enCardType      = USIMM_CARD_NOCARD;
    enCardStatus    = USIMM_CARD_SERVIC_ABSENT;

    /* ������Ϣ�ڴ沢��ʼ�� */
    pstAtMmaUsimStatusIndMsg = (AT_MMA_USIM_STATUS_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMA,
                                             sizeof(AT_MMA_USIM_STATUS_IND_STRU));
    if( VOS_NULL_PTR == pstAtMmaUsimStatusIndMsg )
    {
        TAF_LOG(WUEPS_PID_MMA, VOS_NULL, PS_LOG_LEVEL_ERROR, "MMA_PhUsimStatusInd:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstAtMmaUsimStatusIndMsg + VOS_MSG_HEAD_LENGTH,
               0X00,
               sizeof(AT_MMA_USIM_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��ȡ�����ͺͿ�״̬ */
    TAF_MMA_GetCardInfo(pStPsUsimStatusInd, &enCardType, &enCardStatus);

    /* ��д��Ϣ */
    pstAtMmaUsimStatusIndMsg->ulReceiverPid          = WUEPS_PID_AT;
    pstAtMmaUsimStatusIndMsg->ulMsgName              = ID_TAF_MMA_USIM_STATUS_IND;
    pstAtMmaUsimStatusIndMsg->enCardType             = enCardType;
    pstAtMmaUsimStatusIndMsg->enCardStatus           = enCardStatus;
    pstAtMmaUsimStatusIndMsg->enPhyCardType          = pStPsUsimStatusInd->enPhyCardType;
    pstAtMmaUsimStatusIndMsg->ucIMSILen              = PS_MIN(pucIMSI[0], NAS_MAX_IMSI_LENGTH);
    PS_MEM_CPY(pstAtMmaUsimStatusIndMsg->aucIMSI, pucIMSI, pstAtMmaUsimStatusIndMsg->ucIMSILen);

    NAS_TRACE_HIGH("\nTAF_MMA_SndATUsimmStatusInd: CardType: %d , CardStatus: %d , ulSenderPid: %d",
                   enCardType, enCardStatus, pstAtMmaUsimStatusIndMsg->ulSenderPid);

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstAtMmaUsimStatusIndMsg);

    return;
}
/* Added by h00313353 for iteration 9, 2015-2-7, end */

VOS_VOID TAF_MMA_SndPlmnListCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_PLMN_LIST_CNF_PARA_STRU    *pstPlmnListCnfPara
)
{
    TAF_MMA_PLMN_LIST_CNF_STRU         *pstSndMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstSndMsg = (TAF_MMA_PLMN_LIST_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMA,
                                             sizeof(TAF_MMA_PLMN_LIST_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndPlmnListCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_PLMN_LIST_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_PLMN_LIST_CNF;
    pstSndMsg->usClientId               = pstCtrl->usClientId;
    pstSndMsg->ucOpId                   = pstCtrl->ucOpId;
    PS_MEM_CPY(&pstSndMsg->stPlmnListCnfPara, pstPlmnListCnfPara, sizeof(TAF_MMA_PLMN_LIST_CNF_PARA_STRU));

    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    if (VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndSysCfgSetCnf:Send Msg Failed");
        return;
    }

    return;

}


VOS_VOID TAF_MMA_SndCerssiSetCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
)
{
    TAF_MMA_CERSSI_SET_CNF_STRU        *pstSetCerssiCnf   = VOS_NULL_PTR;

    /* ������Ϣ�ڴ�TAF_MMA_CERSSI_SET_CNF_STRU */
    pstSetCerssiCnf = (TAF_MMA_CERSSI_SET_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                     WUEPS_PID_MMA,
                                                     sizeof(TAF_MMA_CERSSI_SET_CNF_STRU));

    /* �ڴ�����ʧ�ܣ����� */
    if (VOS_NULL_PTR == pstSetCerssiCnf)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndCerssiSetCnf ERROR: Memory Alloc Error for pstSetCerssiCnf");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstSetCerssiCnf + VOS_MSG_HEAD_LENGTH, 0X00,
        sizeof(TAF_MMA_CERSSI_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��������������TAF_MMA_CERSSI_SET_CNF_STRU */
    pstSetCerssiCnf->ulSenderCpuId          = VOS_LOCAL_CPUID;
    pstSetCerssiCnf->ulSenderPid            = WUEPS_PID_MMA;
    pstSetCerssiCnf->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstSetCerssiCnf->ulReceiverPid          = pstCtrl->ulModuleId;
    pstSetCerssiCnf->ulMsgName              = ID_TAF_MMA_CERSSI_SET_CNF;

    PS_MEM_CPY(&pstSetCerssiCnf->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));

    pstSetCerssiCnf->enErrorCause           = enErrorCause;

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstSetCerssiCnf);

    return;
}


VOS_VOID TAF_MMA_SndAccessModeQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    MN_MMA_CPAM_RAT_TYPE_ENUM_UINT8     enAccessMode,
    TAF_PH_PLMN_PRIO                    ucPlmnPrio
)
{
    TAF_MMA_ACCESS_MODE_QRY_CNF_STRU  *pstAccessModeCnf = VOS_NULL_PTR;

    /* ������Ϣ��TAF_MMA_DETACH_CNF_STRU */
    pstAccessModeCnf = (TAF_MMA_ACCESS_MODE_QRY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                          WUEPS_PID_MMA,
                                                          sizeof(TAF_MMA_ACCESS_MODE_QRY_CNF_STRU));

    /* �ڴ�����ʧ�ܣ����� */
    if (VOS_NULL_PTR == pstAccessModeCnf)
    {
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstAccessModeCnf + VOS_MSG_HEAD_LENGTH, 0X00,
                 sizeof(TAF_MMA_ACCESS_MODE_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��������������TAF_MMA_ACCESS_MODE_QRY_CNF_STRU */
    pstAccessModeCnf->ulReceiverPid          = pstCtrl->ulModuleId;
    pstAccessModeCnf->ulMsgName              = ID_TAF_MMA_ACCESS_MODE_QRY_CNF;
    pstAccessModeCnf->stCtrl.usClientId      = pstCtrl->usClientId;
    pstAccessModeCnf->stCtrl.ucOpId          = pstCtrl->ucOpId;

    pstAccessModeCnf->enAccessMode           = enAccessMode;
    pstAccessModeCnf->ucPlmnPrio             = ucPlmnPrio;

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstAccessModeCnf);

    return;
}


VOS_VOID TAF_MMA_SndCopsQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_PH_NETWORKNAME_STRU            *pstCopsInfo
)
{
    TAF_MMA_COPS_QRY_CNF_STRU          *pstCopsCnf = VOS_NULL_PTR;

    /* ������Ϣ��TAF_MMA_DETACH_CNF_STRU */
    pstCopsCnf = (TAF_MMA_COPS_QRY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMA,
                                             sizeof(TAF_MMA_COPS_QRY_CNF_STRU));

    /* �ڴ�����ʧ�ܣ����� */
    if (VOS_NULL_PTR == pstCopsCnf)
    {
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstCopsCnf + VOS_MSG_HEAD_LENGTH, 0X00,
                 sizeof(TAF_MMA_COPS_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��������������TAF_MMA_ACCESS_MODE_QRY_CNF_STRU */
    pstCopsCnf->ulReceiverPid          = pstCtrl->ulModuleId;
    pstCopsCnf->ulMsgName              = ID_TAF_MMA_COPS_QRY_CNF;
    pstCopsCnf->usClientId             = pstCtrl->usClientId;
    pstCopsCnf->ucOpId                 = pstCtrl->ucOpId;

    PS_MEM_CPY(&(pstCopsCnf->stCopsInfo), pstCopsInfo, sizeof(TAF_PH_NETWORKNAME_STRU));

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstCopsCnf);

    return;
}


VOS_VOID TAF_MMA_SndRegStateQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_PH_REG_STATE_STRU              *pstRegInfo
)
{
    TAF_MMA_REG_STATE_QRY_CNF_STRU     *pstRegStateQryCnf = VOS_NULL_PTR;

    /* ������Ϣ��TAF_MMA_REG_STATE_QRY_CNF_STRU */
    pstRegStateQryCnf = (TAF_MMA_REG_STATE_QRY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                         WUEPS_PID_MMA,
                                                         sizeof(TAF_MMA_REG_STATE_QRY_CNF_STRU));

    /* �ڴ�����ʧ�ܣ����� */
    if (VOS_NULL_PTR == pstRegStateQryCnf)
    {
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstRegStateQryCnf + VOS_MSG_HEAD_LENGTH, 0X00,
                 sizeof(TAF_MMA_REG_STATE_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��������������TAF_MMA_REG_STATE_QRY_CNF_STRU */
    pstRegStateQryCnf->ulReceiverPid          = pstCtrl->ulModuleId;
    pstRegStateQryCnf->ulMsgName              = ID_TAF_MMA_REG_STATE_QRY_CNF;

    PS_MEM_CPY(&pstRegStateQryCnf->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));
    PS_MEM_CPY(&(pstRegStateQryCnf->stRegInfo), pstRegInfo, sizeof(TAF_PH_REG_STATE_STRU));

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstRegStateQryCnf);

    return;
}



VOS_VOID TAF_MMA_SndSystemInfoQryCnf(
    TAF_MMA_SYSINFO_QRY_REQ_STRU       *pstSysInfoQryReq,
    TAF_PH_SYSINFO_STRU                *pstSysInfo
)
{
    TAF_MMA_SYSINFO_QRY_CNF_STRU       *pstSysInfoCnf = VOS_NULL_PTR;

    TAF_MMA_CTRL_STRU                  *pstCtrl       = VOS_NULL_PTR;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          ulIsConfigCLMode;

    ulIsConfigCLMode = TAF_SDC_IsConfigCLMode();
#endif

    pstCtrl          = &(pstSysInfoQryReq->stCtrl);



    /* ������Ϣ��TAF_MMA_SYSINFO_QRY_CNF_STRU */
    pstSysInfoCnf = (TAF_MMA_SYSINFO_QRY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                      WUEPS_PID_MMA,
                                                      sizeof(TAF_MMA_SYSINFO_QRY_CNF_STRU));

    /* �ڴ�����ʧ�ܣ����� */
    if (VOS_NULL_PTR == pstSysInfoCnf)
    {
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstSysInfoCnf + VOS_MSG_HEAD_LENGTH, 0X00,
                 sizeof(TAF_MMA_SYSINFO_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��������������TAF_MMA_SYSINFO_QRY_CNF_STRU */
    pstSysInfoCnf->ulReceiverPid          = pstCtrl->ulModuleId;
    pstSysInfoCnf->ulMsgName              = ID_TAF_MMA_SYSINFO_QRY_CNF;
    pstSysInfoCnf->usClientId             = pstCtrl->usClientId;
    pstSysInfoCnf->ucOpId                 = pstCtrl->ucOpId;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if ((VOS_TRUE  == ulIsConfigCLMode)
     && (VOS_FALSE == pstSysInfoQryReq->ulSysInfoExFlag))
    {
        pstSysInfoCnf->ucIsSupport        = VOS_FALSE;
    }
    else
    {
        pstSysInfoCnf->ucIsSupport        = VOS_TRUE;
    }
#else
        pstSysInfoCnf->ucIsSupport        = VOS_TRUE;
#endif

    PS_MEM_CPY(&(pstSysInfoCnf->stSysInfo), pstSysInfo, sizeof(TAF_PH_SYSINFO_STRU));


    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstSysInfoCnf);

    return;
}


VOS_VOID TAF_MMA_SndAntennaInfoQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause,
    MN_MMA_ANQUERY_PARA_STRU           *pstAnqueryInfo
)
{
    TAF_MMA_ANTENNA_INFO_QRY_CNF_STRU  *pstAnqueryCnf = VOS_NULL_PTR;

    /* ������Ϣ��TAF_MMA_ANTENNA_INFO_QRY_CNF_STRU */
    pstAnqueryCnf = (TAF_MMA_ANTENNA_INFO_QRY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                        WUEPS_PID_MMA,
                                                        sizeof(TAF_MMA_ANTENNA_INFO_QRY_CNF_STRU));

    /* �ڴ�����ʧ�ܣ����� */
    if (VOS_NULL_PTR == pstAnqueryCnf)
    {
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstAnqueryCnf + VOS_MSG_HEAD_LENGTH, 0X00,
                 sizeof(TAF_MMA_ANTENNA_INFO_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��������������TAF_MMA_ANTENNA_INFO_QRY_CNF_STRU */
    pstAnqueryCnf->ulReceiverPid          = pstCtrl->ulModuleId;
    pstAnqueryCnf->ulMsgName              = ID_TAF_MMA_ANTENNA_INFO_QRY_CNF;
    PS_MEM_CPY(&pstAnqueryCnf->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));

    pstAnqueryCnf->enErrorCause             = enErrorCause;

    PS_MEM_CPY(&(pstAnqueryCnf->stAntennaInfo), pstAnqueryInfo, sizeof(MN_MMA_ANQUERY_PARA_STRU));

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstAnqueryCnf);

    return;
}


VOS_VOID TAF_MMA_SndApHplmnCnf(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause,
    TAF_MMA_HPLMN_WITH_MNC_LEN_STRU    *pstHplmnWithMnc
)
{
    TAF_MMA_HOME_PLMN_QRY_CNF_STRU     *pstHplmnQryCnf = VOS_NULL_PTR;

    /* ������Ϣ��TAF_MMA_HOME_PLMN_QRY_CNF_STRU */
    pstHplmnQryCnf = (TAF_MMA_HOME_PLMN_QRY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                      WUEPS_PID_MMA,
                                                      sizeof(TAF_MMA_HOME_PLMN_QRY_CNF_STRU));

    /* �ڴ�����ʧ�ܣ����� */
    if (VOS_NULL_PTR == pstHplmnQryCnf)
    {
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstHplmnQryCnf + VOS_MSG_HEAD_LENGTH, 0X00,
                 sizeof(TAF_MMA_HOME_PLMN_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��������������TAF_MMA_APHPLMN_QRY_CNF_STRU */
    pstHplmnQryCnf->ulReceiverPid          = WUEPS_PID_AT;
    pstHplmnQryCnf->ulMsgName              = ID_TAF_MMA_HOME_PLMN_QRY_CNF;
    pstHplmnQryCnf->usClientId             = usClientId;
    pstHplmnQryCnf->ucOpId                 = ucOpId;

    pstHplmnQryCnf->enErrorCause             = enErrorCause;

    if (VOS_NULL_PTR != pstHplmnWithMnc)
    {
        PS_MEM_CPY(&(pstHplmnQryCnf->stHplmnWithMncLen), pstHplmnWithMnc, sizeof(TAF_MMA_HPLMN_WITH_MNC_LEN_STRU));
    }

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstHplmnQryCnf);

    return;
}

/* Added by y00322978 for CDMA 1X Iteration 11, 2015-3-28, begin */

/*****************************************************************************
 �� �� ��  : TAF_MMA_SndCsqQryCnf
 ��������  : csq��ѯ��Ϣ�ϱ��ӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��28��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_SndCsqQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_PH_RSSI_STRU                   *pstCsqPara
)
{
    TAF_MMA_CSQ_QRY_CNF_STRU     *pstCsqCnf = VOS_NULL_PTR;

    /* ������Ϣ��TAF_MMA_CSQ_QRY_CNF_STRU */
    pstCsqCnf = (TAF_MMA_CSQ_QRY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           WUEPS_PID_MMA,
                                           sizeof(TAF_MMA_CSQ_QRY_CNF_STRU));

    /* �ڴ�����ʧ�ܣ����� */
    if (VOS_NULL_PTR == pstCsqCnf)
    {
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstCsqCnf + VOS_MSG_HEAD_LENGTH, 0X00,
                 sizeof(TAF_MMA_CSQ_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��������������TAF_MMA_CSQ_QRY_CNF_STRU */
    pstCsqCnf->ulReceiverPid          = pstCtrl->ulModuleId;
    pstCsqCnf->ulMsgName              = ID_TAF_MMA_CSQ_QRY_CNF;
    PS_MEM_CPY(&pstCsqCnf->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));
    pstCsqCnf->enErrorCause           = TAF_ERR_NO_ERROR;

    if (VOS_NULL_PTR != pstCsqPara )
    {
        PS_MEM_CPY(&(pstCsqCnf->stCsq), pstCsqPara, sizeof(TAF_PH_RSSI_STRU));
    }

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstCsqCnf);

    return;

}
/*****************************************************************************
 �� �� ��  : TAF_MMA_SndCsqLvlQryCnf
 ��������  : CSQLVL��ѯ��Ϣ�ϱ��ӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��28��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_SndCsqLvlQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_CSQLVL_PARA_STRU           *pstCsqlvlPara,
    TAF_MMA_CSQLVLEXT_PARA_STRU        *stCsqLvlExtPara,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
)
{
    TAF_MMA_CSQLVL_QRY_CNF_STRU     *pstCsqlvlCnf = VOS_NULL_PTR;

    /* ������Ϣ��TAF_MMA_CSQLVL_QRY_CNF_STRU */
    pstCsqlvlCnf = (TAF_MMA_CSQLVL_QRY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                 WUEPS_PID_MMA,
                                                 sizeof(TAF_MMA_CSQLVL_QRY_CNF_STRU));

    /* �ڴ�����ʧ�ܣ����� */
    if (VOS_NULL_PTR == pstCsqlvlCnf)
    {
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstCsqlvlCnf + VOS_MSG_HEAD_LENGTH, 0X00,
                 sizeof(TAF_MMA_CSQLVL_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��������������TAF_MMA_CSQLVL_QRY_CNF_STRU */
    pstCsqlvlCnf->ulReceiverPid          = pstCtrl->ulModuleId;
    pstCsqlvlCnf->ulMsgName              = ID_TAF_MMA_CSQLVL_QRY_CNF;
    PS_MEM_CPY(&pstCsqlvlCnf->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));

    if ( TAF_ERR_NO_ERROR != enErrorCause)
    {
        pstCsqlvlCnf->enErrorCause= TAF_ERR_GET_CSQLVL_FAIL;

    }
    else
    {
        pstCsqlvlCnf->enErrorCause= TAF_ERR_NO_ERROR;
    }
    PS_MEM_CPY(&(pstCsqlvlCnf->stCsqLvlPara), pstCsqlvlPara, sizeof(TAF_MMA_CSQLVL_PARA_STRU));
    PS_MEM_CPY(&(pstCsqlvlCnf->stCsqLvlExtPara), stCsqLvlExtPara, sizeof(TAF_MMA_CSQLVLEXT_PARA_STRU));

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstCsqlvlCnf);
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SndAutoAttachSetCnf
 ��������  : auto attach set ������ؽӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��30��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_SndAutoAttachSetCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_PARA_SET_RESULT                 ucRslt
)
{
    TAF_MMA_AUTO_ATTACH_SET_CNF_STRU   *pstAutoAttachSetCnf;
    pstAutoAttachSetCnf = (TAF_MMA_AUTO_ATTACH_SET_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                              sizeof(TAF_MMA_AUTO_ATTACH_SET_CNF_STRU));
    if (VOS_NULL_PTR == pstAutoAttachSetCnf)
    {
        MMA_ERRORLOG("TAF_MMA_SndAutoAttachSetCnf: ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstAutoAttachSetCnf + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_AUTO_ATTACH_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ����Ϣ */
    pstAutoAttachSetCnf->ulReceiverPid          = WUEPS_PID_AT;
    pstAutoAttachSetCnf->ulMsgName              = ID_TAF_MMA_AUTO_ATTACH_SET_CNF;
    PS_MEM_CPY(&pstAutoAttachSetCnf->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));
    pstAutoAttachSetCnf->ucResult               = ucRslt;

    PS_SEND_MSG(WUEPS_PID_MMA, pstAutoAttachSetCnf);
    return;

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SndCrpnQryCnf
 ��������  : crpn qry ���ؽ�����ͽӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��30��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_SndCrpnQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_CRPN_QRY_INFO_STRU         *pstMnMmaCrpnQryCnf,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
)
{
    TAF_MMA_CRPN_QRY_CNF_STRU          *pstCrpnQryCnf;
    TAF_MMA_CRPN_QRY_INFO_STRU         *pData;

    pData = pstMnMmaCrpnQryCnf;

    pstCrpnQryCnf = (TAF_MMA_CRPN_QRY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                           sizeof(TAF_MMA_CRPN_QRY_CNF_STRU));
    if (VOS_NULL_PTR == pstCrpnQryCnf)
    {
        MMA_ERRORLOG("TAF_MMA_SndCrpnQryCnf: ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstCrpnQryCnf + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_CRPN_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ����Ϣ */
    pstCrpnQryCnf->ulReceiverPid          = WUEPS_PID_AT;
    pstCrpnQryCnf->ulMsgName              = ID_TAF_MMA_CRPN_QRY_CNF;
    PS_MEM_CPY(&pstCrpnQryCnf->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));
    pstCrpnQryCnf->enErrorCause               = enErrorCause;

    if (VOS_NULL_PTR != pData)
    {
        PS_MEM_CPY(&pstCrpnQryCnf->stCrpnQryInfo, pData, sizeof(TAF_MMA_CRPN_QRY_INFO_STRU));
    }

    PS_SEND_MSG(WUEPS_PID_MMA, pstCrpnQryCnf);
    return;

}
/* Added by y00322978 for CDMA 1X Iteration 11, 2015-3-28, end */


VOS_VOID TAF_MMA_SndBatteryCapacityQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_BATTERYPOWER_STRU          *pstBatteryStatus
)
{
    TAF_MMA_BATTERY_CAPACITY_QRY_CNF_STRU                  *pstCbcQryCnf = VOS_NULL_PTR;

    /* ������Ϣ��TAF_MMA_CBC_QRY_CNF_STRU */
    pstCbcQryCnf = (TAF_MMA_BATTERY_CAPACITY_QRY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                              WUEPS_PID_MMA,
                                              sizeof(TAF_MMA_BATTERY_CAPACITY_QRY_CNF_STRU));

    /* �ڴ�����ʧ�ܣ����� */
    if (VOS_NULL_PTR == pstCbcQryCnf)
    {
        TAF_LOG(WUEPS_PID_MMA, VOS_NULL_PTR, PS_LOG_LEVEL_ERROR,
                "TAF_MMA_SndBatteryCapacityQryCnf: Memory Alloc Error for pstCbcQryCnf!");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstCbcQryCnf + VOS_MSG_HEAD_LENGTH, 0X00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_BATTERY_CAPACITY_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ��������������TAF_MMA_CBC_QRY_CNF_STRU */
    pstCbcQryCnf->ulReceiverPid          = pstCtrl->ulModuleId;
    pstCbcQryCnf->ulMsgName              = ID_TAF_MMA_BATTERY_CAPACITY_QRY_CNF;
    PS_MEM_CPY(&pstCbcQryCnf->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));

    PS_MEM_CPY(&(pstCbcQryCnf->stBatteryStatus), pstBatteryStatus, sizeof(TAF_MMA_BATTERYPOWER_STRU));

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstCbcQryCnf);
}


VOS_VOID TAF_MMA_SndHandShakeQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    VOS_UINT8                          *pPara
)
{
    TAF_MMA_HAND_SHAKE_QRY_CNF_STRU    *pstHsQryCnf = VOS_NULL_PTR;

    /* ������Ϣ��TAF_MMA_HS_QRY_CNF_STRU */
    pstHsQryCnf = (TAF_MMA_HAND_SHAKE_QRY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                            WUEPS_PID_MMA,
                                            sizeof(TAF_MMA_HAND_SHAKE_QRY_CNF_STRU));

    /* �ڴ�����ʧ�ܣ����� */
    if (VOS_NULL_PTR == pstHsQryCnf)
    {
        TAF_LOG(WUEPS_PID_MMA, VOS_NULL_PTR, PS_LOG_LEVEL_ERROR,
                "TAF_MMA_SndHandShakeQryCnf: Memory Alloc Error for pstHsQryCnf!");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstHsQryCnf + VOS_MSG_HEAD_LENGTH, 0X00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_HAND_SHAKE_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ��������������TAF_MMA_HS_QRY_CNF_STRU */
    pstHsQryCnf->ulReceiverPid          = pstCtrl->ulModuleId;
    pstHsQryCnf->ulMsgName              = ID_TAF_MMA_HAND_SHAKE_QRY_CNF;
    PS_MEM_CPY(&pstHsQryCnf->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));

    PS_MEM_CPY(pstHsQryCnf->aucBuf, pPara, (sizeof(VOS_UINT8) * AT_HS_PARA_MAX_LENGTH));

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstHsQryCnf);
}


VOS_VOID TAF_MMA_SndSrvStatusInd(
    TAF_PHONE_CHANGED_SERVICE_STATUS    ucSrvStatus
)
{
    TAF_MMA_SRV_STATUS_IND_STRU        *pstSrvStatus;

    pstSrvStatus = (TAF_MMA_SRV_STATUS_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                             sizeof(TAF_MMA_SRV_STATUS_IND_STRU));
    if (VOS_NULL_PTR == pstSrvStatus)
    {
        MMA_ERRORLOG("TAF_MMA_SndSrvStatusInd: ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstSrvStatus + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_SRV_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ����Ϣ */
    pstSrvStatus->ulReceiverPid = WUEPS_PID_AT;
    pstSrvStatus->ulMsgName     = ID_TAF_MMA_SRV_STATUS_IND;
    pstSrvStatus->usClientId    = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_TAF);
    pstSrvStatus->ucOpid        = MMA_OP_ID_INTERNAL;
    pstSrvStatus->ucSrvStatus   = ucSrvStatus;

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstSrvStatus);

    return;
}


VOS_VOID TAF_MMA_SndRegStatusInd(
    TAF_PH_REG_STATE_STRU              *pstRegState
)
{
    TAF_MMA_REG_STATUS_IND_STRU        *pstRegStatusInd;

    pstRegStatusInd = (TAF_MMA_REG_STATUS_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                                  sizeof(TAF_MMA_REG_STATUS_IND_STRU));
    if (VOS_NULL_PTR == pstRegStatusInd)
    {
        MMA_ERRORLOG("TAF_MMA_SndRegStatusInd: ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstRegStatusInd + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_REG_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ����Ϣ */
    pstRegStatusInd->ulReceiverPid             = WUEPS_PID_AT;
    pstRegStatusInd->ulMsgName                 = ID_TAF_MMA_REG_STATUS_IND;
    pstRegStatusInd->usClientId                = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_TAF);
    pstRegStatusInd->ucOpId                    = MMA_OP_ID_INTERNAL;

    PS_MEM_CPY(&(pstRegStatusInd->stRegStatus), pstRegState, sizeof(TAF_PH_REG_STATE_STRU));

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstRegStatusInd);

    return;
}


VOS_VOID TAF_MMA_SndRegRejInd(
    TAF_PH_REG_REJ_INFO_STRU           *pstRejInfo
)
{
    TAF_MMA_REG_REJ_INFO_IND_STRU      *pstRegRejInd;

    pstRegRejInd = (TAF_MMA_REG_REJ_INFO_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                                 sizeof(TAF_MMA_REG_REJ_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstRegRejInd)
    {
        MMA_ERRORLOG("TAF_MMA_SndRegRejInfoInd: ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstRegRejInd + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_REG_REJ_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ����Ϣ */
    pstRegRejInd->ulReceiverPid             = WUEPS_PID_AT;
    pstRegRejInd->ulMsgName                 = ID_TAF_MMA_REG_REJ_INFO_IND;
    pstRegRejInd->usClientId                = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_TAF);
    pstRegRejInd->ucOpId                    = MMA_OP_ID_INTERNAL;

    PS_MEM_CPY(&(pstRegRejInd->stRegRejInfo), pstRejInfo, sizeof(TAF_PH_REG_REJ_INFO_STRU));

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstRegRejInd);

    return;
}


VOS_VOID TAF_MMA_SndPlmnSelectionInd(
    TAF_MMA_PLMN_SELECTION_INFO_STRU    *pstPlmnSelectInfo
)
{
    TAF_MMA_PLMN_SElECTION_INFO_IND_STRU                   *pstPlmnSelecInd;

    pstPlmnSelecInd = (TAF_MMA_PLMN_SElECTION_INFO_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                                           sizeof(TAF_MMA_PLMN_SElECTION_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstPlmnSelecInd)
    {
        MMA_ERRORLOG("TAF_MMA_SndRegRejInfoInd: ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstPlmnSelecInd + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_PLMN_SElECTION_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ����Ϣ */
    pstPlmnSelecInd->ulReceiverPid             = WUEPS_PID_AT;
    pstPlmnSelecInd->ulMsgName                 = ID_TAF_MMA_PLMN_SELECTION_INFO_IND;
    pstPlmnSelecInd->usClientId                = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_TAF);
    pstPlmnSelecInd->ucOpId                    = MMA_OP_ID_INTERNAL;

    PS_MEM_CPY(&(pstPlmnSelecInd->stPlmnSelectInfo), pstPlmnSelectInfo, sizeof(TAF_MMA_PLMN_SELECTION_INFO_STRU));

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstPlmnSelecInd);

    return;
}


VOS_VOID TAF_MMA_SndCipherQryCnf(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCipherInfo,
    VOS_UINT32                          ulResult
)
{
    TAF_MMA_CIPHER_QRY_CNF_STRU        *pstCipherQryCnf;

    pstCipherQryCnf = (TAF_MMA_CIPHER_QRY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                     WUEPS_PID_MMA,
                                                     sizeof(TAF_MMA_CIPHER_QRY_CNF_STRU));
    if( VOS_NULL_PTR == pstCipherQryCnf )
    {
        MMA_ERRORLOG("TAF_MMA_SndRegRejInfoInd: ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstCipherQryCnf + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(TAF_MMA_CIPHER_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣ */
    pstCipherQryCnf->ulReceiverPid          = WUEPS_PID_AT;
    pstCipherQryCnf->ulMsgName              = ID_TAF_MMA_CIPHER_QRY_CNF;
    pstCipherQryCnf->usClientId             = usClientId;
    pstCipherQryCnf->ucOpId                 = ucOpId;
    pstCipherQryCnf->ucCipherInfo           = ucCipherInfo;
    pstCipherQryCnf->ulResult               = ulResult;

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstCipherQryCnf);
}

/* Added by k902809 for Iteration 11, 2015-3-25, begin */
/*****************************************************************************
Function Name     :   TAF_MMA_SndNetScanCnf
Description       :   Allocate the memory for message.
                      Sends the message to MMA with message ID ID_TAF_MMA_NET_SCAN_CNF
                      Returns AT_FAILURE on failure of senfing message.

Input parameters  :   TAF_MMA_NET_SCAN_CNF_STRU          *pstRcvNetScanCnf
Outout parameters :
Return Value      :   VOS_VOID

Modify History:
    1)  Date      :   2015-03-25
        Author    :   k902809
        Modify content :    Create
*******************************************************************************/
VOS_VOID TAF_MMA_SndNetScanCnf(
    TAF_MMA_NET_SCAN_CNF_STRU          *pstRcvNetScanCnf
)
{
    TAF_MMA_NET_SCAN_CNF_STRU          *pstNetScanCnf = VOS_NULL_PTR;

    pstNetScanCnf = (TAF_MMA_NET_SCAN_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                 WUEPS_PID_MMA,
                                                 sizeof(TAF_MMA_NET_SCAN_CNF_STRU));
    if (VOS_NULL_PTR == pstNetScanCnf)
    {
        MMA_ERRORLOG("TAF_MMA_SendNetScanCnf:ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET( (VOS_UINT8 *)pstNetScanCnf + VOS_MSG_HEAD_LENGTH, 0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_NET_SCAN_CNF_STRU) - VOS_MSG_HEAD_LENGTH) );

    PS_MEM_CPY(pstNetScanCnf, pstRcvNetScanCnf,sizeof(TAF_MMA_NET_SCAN_CNF_STRU));

    pstNetScanCnf->ulSenderPid            = WUEPS_PID_MMA;
    pstNetScanCnf->ulSenderCpuId          = VOS_LOCAL_CPUID;
    pstNetScanCnf->ulReceiverPid          = WUEPS_PID_AT;
    pstNetScanCnf->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstNetScanCnf->ulLength               = sizeof(TAF_MMA_NET_SCAN_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstNetScanCnf->ulMsgName              = ID_TAF_MMA_NET_SCAN_CNF;

    /* Sending message */
    PS_SEND_MSG(WUEPS_PID_MMA, pstNetScanCnf);

    return;
}
/* Added by k902809 for Iteration 11, Iteration 11 2015-3-25, end */



VOS_VOID TAF_MMA_SndAutoAttachQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause,
    VOS_UINT8                           ucAutoAttachFlag
)
{
    TAF_MMA_AUTO_ATTACH_QRY_CNF_STRU         *pstAutoAttachQryCnf = VOS_NULL_PTR;

    /* ������Ϣ��TAF_MMA_AUTOATTACH_QRY_CNF_STRU */
    pstAutoAttachQryCnf = (TAF_MMA_AUTO_ATTACH_QRY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                             WUEPS_PID_MMA,
                                                             sizeof(TAF_MMA_AUTO_ATTACH_QRY_CNF_STRU));

    /* �ڴ�����ʧ�ܣ����� */
    if (VOS_NULL_PTR == pstAutoAttachQryCnf)
    {
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstAutoAttachQryCnf + VOS_MSG_HEAD_LENGTH, 0X00,
                 sizeof(TAF_MMA_AUTO_ATTACH_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��������������TAF_MMA_AUTOATTACH_QRY_CNF_STRU */
    pstAutoAttachQryCnf->ulReceiverPid          = pstCtrl->ulModuleId;
    pstAutoAttachQryCnf->ulMsgName              = ID_TAF_MMA_AUTO_ATTACH_QRY_CNF;
    PS_MEM_CPY(&pstAutoAttachQryCnf->stCtrl, pstCtrl, sizeof(TAF_MMA_CTRL_STRU));

    pstAutoAttachQryCnf->enErrorCause             = enErrorCause;
    pstAutoAttachQryCnf->ucAutoAttachFlag       = ucAutoAttachFlag;

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstAutoAttachQryCnf);

    return;
}

/* Modified by l00301449 for Iteration 13, 2015-04-11, begin */
/*****************************************************************************
 �� �� ��  : TAF_MMA_SndAttachCnf
 ��������  : ����ID_TAF_MMA_ATTACH_CNF��Ϣ
 �������  : TAF_MMA_CTRL_STRU                  *pstCtrl
             TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt
             TAF_PHONE_ERROR                     usErrorCause
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��11��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_SndAttachCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
)
{
    TAF_MMA_ATTACH_CNF_STRU            *pstAttachCnfMsg   = VOS_NULL_PTR;

    pstAttachCnfMsg = (TAF_MMA_ATTACH_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                          WUEPS_PID_MMA,
                                          sizeof(TAF_MMA_ATTACH_CNF_STRU));
    if (VOS_NULL_PTR == pstAttachCnfMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndAttachCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstAttachCnfMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_ATTACH_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstAttachCnfMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstAttachCnfMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstAttachCnfMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstAttachCnfMsg->ulReceiverPid            = pstCtrl->ulModuleId;
    pstAttachCnfMsg->enMsgName                = ID_TAF_MMA_ATTACH_CNF;
    pstAttachCnfMsg->stCtrl.usClientId        = pstCtrl->usClientId;
    pstAttachCnfMsg->stCtrl.ucOpId            = pstCtrl->ucOpId;
    pstAttachCnfMsg->stCtrl.ulModuleId        = pstCtrl->ulModuleId;
    pstAttachCnfMsg->enRslt                   = enRslt;
    pstAttachCnfMsg->enErrorCause             = enErrorCause;

    PS_SEND_MSG(WUEPS_PID_MMA, pstAttachCnfMsg);

    return;

}
/* Modified by l00301449 for Iteration 13, 2015-04-11, end */

/* Added by h00313353 for Iteration 13, 2015-4-17, begin */
/*****************************************************************************
 �� �� ��  : TAF_MMA_SndAttachStatusQryCnf
 ��������  : ����ID_TAF_MMA_ATTACH_CNF��Ϣ
 �������  : TAF_MMA_ATTACH_STATUS_QRY_REQ_STRU *pstRcvMsg,
             TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt,
             TAF_PHONE_ERROR                     usErrorCause,
             TAF_MMA_ATTACH_STATUS_ENUM_UINT8    enCsStatus,
             TAF_MMA_ATTACH_STATUS_ENUM_UINT8    enPsStatus
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��11��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_SndAttachStatusQryCnf(
    TAF_MMA_ATTACH_STATUS_QRY_REQ_STRU *pstRcvMsg,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause,
    TAF_MMA_ATTACH_STATUS_ENUM_UINT8    enCsStatus,
    TAF_MMA_ATTACH_STATUS_ENUM_UINT8    enPsStatus
)
{
    TAF_MMA_ATTACH_STATUS_QRY_CNF_STRU *pstAttachStatusQryCnfMsg    = VOS_NULL_PTR;

    pstAttachStatusQryCnfMsg = (TAF_MMA_ATTACH_STATUS_QRY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                          WUEPS_PID_MMA,
                                          sizeof(TAF_MMA_ATTACH_STATUS_QRY_CNF_STRU));
    if (VOS_NULL_PTR == pstAttachStatusQryCnfMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndAttachStatusQryCnf:Alloc Msg Failed");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstAttachStatusQryCnfMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_ATTACH_STATUS_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstAttachStatusQryCnfMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstAttachStatusQryCnfMsg->ulReceiverPid            = pstRcvMsg->stCtrl.ulModuleId;
    pstAttachStatusQryCnfMsg->enMsgName                = ID_TAF_MMA_ATTACH_STATUS_QRY_CNF;
    pstAttachStatusQryCnfMsg->stCtrl.usClientId        = pstRcvMsg->stCtrl.usClientId;
    pstAttachStatusQryCnfMsg->stCtrl.ucOpId            = pstRcvMsg->stCtrl.ucOpId;
    pstAttachStatusQryCnfMsg->stCtrl.ulModuleId        = pstRcvMsg->stCtrl.ulModuleId;
    pstAttachStatusQryCnfMsg->enRslt                   = enRslt;
    pstAttachStatusQryCnfMsg->enErrorCause             = enErrorCause;
    pstAttachStatusQryCnfMsg->enDomainType             = pstRcvMsg->enDomainType;
    pstAttachStatusQryCnfMsg->enCsStatus               = enCsStatus;
    pstAttachStatusQryCnfMsg->enPsStatus               = enPsStatus;

    PS_SEND_MSG(WUEPS_PID_MMA, pstAttachStatusQryCnfMsg);

    return;

}


TAF_MMA_RAT_TYPE_ENUM_UINT8 TAF_MMA_ConvertMmlRatTypeToTafRatType(
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enMmlRatType
)
{
    switch (enMmlRatType)
    {
        case NAS_MSCC_PIF_NET_RAT_TYPE_GSM:
             return TAF_MMA_RAT_GSM;

        case NAS_MSCC_PIF_NET_RAT_TYPE_WCDMA:
             return TAF_MMA_RAT_WCDMA;

        case NAS_MSCC_PIF_NET_RAT_TYPE_LTE:
             return TAF_MMA_RAT_LTE;

        case NAS_MSCC_PIF_NET_RAT_TYPE_1X:
             return TAF_MMA_RAT_1X;

        case NAS_MSCC_PIF_NET_RAT_TYPE_HRPD:
             return TAF_MMA_RAT_HRPD;

        default:
            TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_ConvertMmlRatTypeToTafRatType:WARNING: The input in invalid");
            return TAF_MMA_RAT_BUTT;
    }
}


VOS_VOID TAF_MMA_SndSrchedPlmnInfoInd(
    MSCC_MMA_SRCHED_PLMN_INFO_IND_STRU *pstSrchedPlmnInfoInd
)
{
    TAF_MMA_SRCHED_PLMN_INFO_IND_STRU  *pstSndMsg      = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT32                          ulRst;

    pstSndMsg = (TAF_MMA_SRCHED_PLMN_INFO_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                         WUEPS_PID_MMA,
                                         sizeof(TAF_MMA_SRCHED_PLMN_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndSrchedPlmnInfoInd:Alloc Msg Failed");
        return;
    }
    PS_MEM_SET( (VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(TAF_MMA_SRCHED_PLMN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ����ϱ��¼� */
    pstSndMsg->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid              = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid            = WUEPS_PID_AT;
    pstSndMsg->ulMsgName                = ID_TAF_MMA_SRCHED_PLMN_INFO_IND;
    pstSndMsg->usClientId               = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_TAF);
    pstSndMsg->ucOpid                   = MMA_OP_ID_INTERNAL;

    pstSndMsg->enRat = TAF_MMA_ConvertMmlRatTypeToTafRatType(pstSrchedPlmnInfoInd->enRat);

    if (MSCC_MMA_MAX_SRCHED_LAI_NUM < pstSrchedPlmnInfoInd->ulLaiNum)
    {
        pstSrchedPlmnInfoInd->ulLaiNum = MSCC_MMA_MAX_SRCHED_LAI_NUM;
    }
    pstSndMsg->ulLaiNum = pstSrchedPlmnInfoInd->ulLaiNum;
    if (TAF_MMA_MAX_SRCHED_LAI_NUM < pstSndMsg->ulLaiNum)
    {
        pstSndMsg->ulLaiNum = TAF_MMA_MAX_SRCHED_LAI_NUM;
    }

    for (i = 0; i < pstSndMsg->ulLaiNum; i++)
    {
        pstSndMsg->astLai[i].stPlmnId.Mcc = pstSrchedPlmnInfoInd->astLai[i].stPlmnId.ulMcc;
        pstSndMsg->astLai[i].stPlmnId.Mnc = pstSrchedPlmnInfoInd->astLai[i].stPlmnId.ulMnc;

        /* ��PLMN IDתΪBCD��ʽ */
        MMA_PlmnId2Bcd(&pstSndMsg->astLai[i].stPlmnId);

        pstSndMsg->astLai[i].usLac        = pstSrchedPlmnInfoInd->astLai[i].usLac;
    }

    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);
    if (VOS_OK != ulRst)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,"TAF_MMA_SndSrchedPlmnInfoInd:Send Msg Failed");
    }
}

/* Added by h00313353 for Iteration 13, 2015-4-17, end */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif



