/******************************************************************************

                  ��Ȩ���� (C), 2013-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMmaSndOm.c
  �� �� ��   : ����
  ��    ��   : y00322978
  ��������   : 2015-07-16
  ����޸�   :
  ��������   : MMAģ�鷢�͵�om����Ϣ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015-07-16
    ��    ��   : y00322978
    �޸�����   : �����ļ�

******************************************************************************/




/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "TafMmaSndOm.h"
#include "TafMmaComFunc.h"
#include "TafSdcCtx.h"
#include "MmaAppLocal.h"
/* Added by y00322978 for CDMA Iteration 17, 2015-8-4, begin */
#include "msp_diag_comm.h"
#include "TafMmaProcNvim.h"
/* Added by y00322978 for CDMA Iteration 17, 2015-8-4, end */
#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

#define    THIS_FILE_ID                 PS_FILE_ID_TAF_MMA_SND_OM_C


/*****************************************************************************
   2 ȫ�ֱ�������ͺ�
****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/
/* Added by y00322978 for CDMA Iteration 17, 2015-7-10, begin */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
 �� �� ��  : TAF_MMA_SndOmCdmaSysInfoCnf
 ��������  : �ظ�om��ά�ɲ���Ϣ����ѯcdma��Ϣ
 �������  : NAS_OM_MMA_CDMA_STATUS_REPORT_RESRLT_ENUM_UINT32        enRlst ��ѯ���
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��10��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_SndOmCdmaStatusReportCnf(
    NAS_OM_MMA_CDMA_STATUS_REPORT_RESRLT_ENUM_UINT32        enRlst,
    OM_NAS_MMA_CDMA_STATUS_INFO_REPORT_REQ_STRU            *pstMsg
)
{
    NAS_OM_MMA_CDMA_STATUS_INFO_REPORT_CNF_STRU        *pstSndMsg;

    pstSndMsg = (NAS_OM_MMA_CDMA_STATUS_INFO_REPORT_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                         WUEPS_PID_MMA,
                                         sizeof(NAS_OM_MMA_CDMA_STATUS_INFO_REPORT_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        return ;
    }

    PS_MEM_SET( (VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(NAS_OM_MMA_CDMA_STATUS_INFO_REPORT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulSn                     = pstMsg->ulSn;
    pstSndMsg->ulTimeStamp              = pstMsg->ulTimeStamp;
    pstSndMsg->usOriginalId             = pstMsg->usOriginalId;
    pstSndMsg->usTerminalId             = pstMsg->usTerminalId;

    pstSndMsg->ulReceiverPid            = MSP_PID_DIAG_APP_AGENT;
    pstSndMsg->ulMsgId                  = ID_NAS_OM_MMA_CDMA_STATUS_INFO_REPORT_CNF;
    pstSndMsg->enResult                 = enRlst;

    PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SndOmCdmaStatusInfoReportInd
 ��������  : cdma sys info �ϱ���om
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��10��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_SndOmCdmaStatusInfoReportInd( VOS_VOID )
{
    NAS_OM_MMA_CDMA_STATUS_COMMON_INFO_STRU             stCdmaCommInfo;
    NAS_OM_MMA_1X_SYS_INFO_STRU                         st1xSysInfo;
    NAS_OM_MMA_HRPD_SYS_INFO_STRU                       stHrpdSysInfo;
    NAS_OM_MMA_CDMA_STATUS_INFO_REPORT_IND_STRU        *pstStatusInfoInd;
    DIAG_TRANS_IND_STRU                                 stIndMsg;

    pstStatusInfoInd = (NAS_OM_MMA_CDMA_STATUS_INFO_REPORT_IND_STRU*)PS_MEM_ALLOC(
                                         WUEPS_PID_MMA,
                                         sizeof(NAS_OM_MMA_CDMA_STATUS_INFO_REPORT_IND_STRU));
    if (VOS_NULL_PTR == pstStatusInfoInd)
    {
        return ;
    }

    /*��ʼ������*/
    PS_MEM_SET(pstStatusInfoInd, 0X00, sizeof(NAS_OM_MMA_CDMA_STATUS_INFO_REPORT_IND_STRU));
    TAF_MMA_InitSndOmCdma1xSysInfo(&st1xSysInfo);
    TAF_MMA_InitSndOmCdmaCommSysInfo(&stCdmaCommInfo);
    TAF_MMA_InitSndOmCdmaHrpdSysInfo(&stHrpdSysInfo);

    TAF_MMA_ReadMeidFromNvim();
    TAF_MMA_ReadEsnFromNvim();

    TAF_MMA_QryCdmaStatusInfo(&stCdmaCommInfo, &st1xSysInfo, &stHrpdSysInfo);

    pstStatusInfoInd->usToolsId                = 0;
    pstStatusInfoInd->usPrimId                 = ID_NAS_OM_MMA_CDMA_STATUS_INFO_REPORT_IND;

    PS_MEM_CPY(&(pstStatusInfoInd->stCdmaCommInfo), &stCdmaCommInfo, sizeof(stCdmaCommInfo));
    PS_MEM_CPY(&(pstStatusInfoInd->st1xSysInfo), &st1xSysInfo, sizeof(st1xSysInfo));
    PS_MEM_CPY(&(pstStatusInfoInd->stHrpdSysInfo), &stHrpdSysInfo, sizeof(stHrpdSysInfo));

    stIndMsg.ulPid = WUEPS_PID_MMA;
    stIndMsg.ulLength = sizeof(NAS_OM_MMA_CDMA_STATUS_INFO_REPORT_IND_STRU);
    stIndMsg.ulModule = DIAG_GEN_MODULE(VOS_GetModemIDFromPid(WUEPS_PID_MMA), DIAG_MODE_COMM);
    stIndMsg.ulMsgId = ID_NAS_OM_MMA_CDMA_STATUS_INFO_REPORT_IND;
    stIndMsg.pData = (VOS_VOID*)pstStatusInfoInd;

    DIAG_TransReport(&stIndMsg);

    PS_MEM_FREE(WUEPS_PID_MMA, pstStatusInfoInd);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_InitCdmaCommSysInfo
 ��������  : ��ʼ��mma�ϱ�om��cdma common info
 �������  : NAS_OM_MMA_CDMA_STATUS_COMMON_INFO_STRU             stCdmaCommInfo;
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��16��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_InitSndOmCdmaCommSysInfo(
    NAS_OM_MMA_CDMA_STATUS_COMMON_INFO_STRU            *pstCdmaCommInfo
)
{
    PS_MEM_SET(pstCdmaCommInfo, 0x00, sizeof(NAS_OM_MMA_CDMA_STATUS_COMMON_INFO_STRU));
    pstCdmaCommInfo->enPhoneMode = NAS_OM_MMA_PHONE_MODE_BUTT;
    pstCdmaCommInfo->enSysMode = NAS_OM_MMA_SYS_MODE_BUTT;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_InitCdma!xSysInfo
 ��������  : ��ʼ��mma�ϱ�om��1x sysinfo
 �������  : NAS_OM_MMA_1X_SYS_INFO_STRU                         st1xSysInfo;
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��16��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_InitSndOmCdma1xSysInfo(
    NAS_OM_MMA_1X_SYS_INFO_STRU        *pst1xSysInfo
)
{
    PS_MEM_SET(pst1xSysInfo, 0x00, sizeof(NAS_OM_MMA_1X_SYS_INFO_STRU));

    pst1xSysInfo->lSid                  = MMA_INVALID_SID;
    pst1xSysInfo->lNid                  = MMA_INVALID_NID;
    pst1xSysInfo->ulMcc                 = (VOS_UINT32)MMA_INVALID_MCC;
    pst1xSysInfo->usMnc                 = (VOS_UINT16)MMA_INVALID_MNC;
    pst1xSysInfo->en1xCallState         = NAS_OM_1X_CALL_STATE_IDLE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_InitCdmaHrpdSysInfo
 ��������  : ��ʼ��mma�ϱ�om HRPD SYS INFO
 �������  : NAS_OM_MMA_HRPD_SYS_INFO_STRU      *pstHrpdSysInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��16��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_InitSndOmCdmaHrpdSysInfo(
    NAS_OM_MMA_HRPD_SYS_INFO_STRU      *pstHrpdSysInfo
)
{
    PS_MEM_SET(pstHrpdSysInfo, 0x0, sizeof(TAF_SDC_HRPD_SYS_INFO_STRU));

    pstHrpdSysInfo->enSessionStatus     = NAS_OM_MMA_HRPD_SESSION_STATUS_CLOSE;
    pstHrpdSysInfo->ulMcc               = (VOS_UINT32)MMA_INVALID_MCC;
    pstHrpdSysInfo->enSysSubMode        = NAS_OM_MMA_SYS_SUBMODE_BUTT;
}
#endif
/* Added by y00322978 for CDMA Iteration 17, 2015-7-10, end */


/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif



