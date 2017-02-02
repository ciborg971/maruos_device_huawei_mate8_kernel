

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "MnMsgInclude.h"
#include "TafCbaProcUsim.h"

#include "Taf_Common.h"

#include "NasUsimmApi.h"

#include "MnMsgSmCommProc.h"

/* Added by h00313353 for iteration 9, 2015-3-9, begin */
#include "TafSdcCtx.h"
/* Added by h00313353 for iteration 9, 2015-3-9, end */

#include "MnMsgSendSpm.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


#define    THIS_FILE_ID        PS_FILE_ID_MNMSG_USIM_PROC_C

/*****************************************************************************
  2 ��������
*****************************************************************************/
enum MN_MSG_STUB_CFG_VALUE_ENUM
{
    MN_MSG_STUB_CFG_VALUE_RESET = 0,
    MN_MSG_STUB_CFG_VALUE_SET   = 1
};
typedef VOS_UINT8 MN_MSG_STUB_CFG_VALUE_ENUM_U8;


/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucListSetRec;                           /*�б�ʱ,USIM���صļ�¼����*/
    VOS_UINT8                           ucListSuccRec;                          /*�б�ʱ,USIM����д��ɹ��ļ�¼����*/
    VOS_UINT8                           ucDeleteSetRec;                         /*ɾ������ʱ,USIM���صļ�¼����*/
    VOS_UINT8                           ucDeleteSuccRec;                        /*ɾ������ʱ,USIM����д��ɹ��ļ�¼����*/
    VOS_UINT8                           ucDeleteStaRptSetRec;                   /*ɾ������״̬����ʱ,USIM���صļ�¼����*/
    VOS_UINT8                           ucDeleteStaRptSuccRec;                  /*ɾ������״̬����ʱ,USIM����д��ɹ��ļ�¼����*/
    VOS_UINT8                           ucDeleteSrvParmSetRec;                  /*ɾ�����Ų����ļ�EFSMSP,USIM���صļ�¼����*/
    VOS_UINT8                           ucDeleteSrvParmSuccRec;                 /*ɾ�����Ų����ļ�EFSMSP,USIM����д��ɹ��ļ�¼����*/
}MN_MSG_USIM_RETURN_REC_STRU;

/*****************************************************************************
  4 ��������
*****************************************************************************/
LOCAL MN_MSG_USIM_RETURN_REC_STRU      f_stMsgUsimReturnRec;
LOCAL VOS_UINT8                        f_ucMsgCurrSmRec;
VOS_UINT8                              g_ucSetEfSmsFail = 0;
LOCAL TAF_MSG_FDN_INFO_STRU            f_stMsgFdnInfo;
#if ( VOS_WIN32 == VOS_OS_VER )
VOS_UINT8                              g_ucSetEfSmsCapacity = 0;
VOS_UINT8                              g_ucSetEfSmsNoResponse = 0;
#endif

/*lint -save -e958 */


/*****************************************************************************
  5 ����ʵ��
*****************************************************************************/

VOS_VOID MSG_PrintUsimReturnRecStru(
    MN_MSG_USIM_RETURN_REC_STRU        *pstUsimReturnRec
)
{
    MN_INFO_LOG1("MSG_PrintUsimReturnRecStru: ucListSetRec ", (VOS_INT32)pstUsimReturnRec->ucListSetRec);
    MN_INFO_LOG1("MSG_PrintUsimReturnRecStru: ucListSuccRec ", (VOS_INT32)pstUsimReturnRec->ucListSuccRec);
    MN_INFO_LOG1("MSG_PrintUsimReturnRecStru: ucDeleteSetRec ", (VOS_INT32)pstUsimReturnRec->ucDeleteSetRec);
    MN_INFO_LOG1("MSG_PrintUsimReturnRecStru: ucDeleteSuccRec ", (VOS_INT32)pstUsimReturnRec->ucDeleteSuccRec);
    MN_INFO_LOG1("MSG_PrintUsimReturnRecStru: ucDeleteStaRptSetRec ", (VOS_INT32)pstUsimReturnRec->ucDeleteStaRptSetRec);
    MN_INFO_LOG1("MSG_PrintUsimReturnRecStru: ucDeleteStaRptSuccRec ", (VOS_INT32)pstUsimReturnRec->ucDeleteStaRptSuccRec);
    MN_INFO_LOG1("MSG_PrintUsimReturnRecStru: ucDeleteSrvParmSetRec ", (VOS_INT32)pstUsimReturnRec->ucDeleteSrvParmSetRec);
    MN_INFO_LOG1("MSG_PrintUsimReturnRecStru: ucDeleteSrvParmSuccRec ", (VOS_INT32)pstUsimReturnRec->ucDeleteSrvParmSuccRec);
}


VOS_VOID MN_MSG_Usim_Stub(
    VOS_UINT32                          ulDestTskId,
    VOS_UINT16                          usEfId,
    VOS_UINT32                          ulResult,
    VOS_UINT8                           ucRecordNum
)
{
    USIMM_UPDATEFILE_CNF_STRU          *pUsimSetFileRsp;
    VOS_CHAR                           *pucFilePathStr = VOS_NULL_PTR;
    /* Added by h00313353 for iteration 9, 2015-2-17, begin */
    VOS_UINT32                          ulPathLength;

    ulPathLength    = 0;

    if (VOS_OK != USIMM_ChangeDefFileToPath(usEfId, &pucFilePathStr))
    {
        return;
    }

    /* �ļ�·�����ȱ��� */
    ulPathLength = VOS_StrLen(pucFilePathStr);
    if (0 == ulPathLength)
    {
        return;
    }
    /* Added by h00313353 for iteration 9, 2015-2-17, end */

    pUsimSetFileRsp = (USIMM_UPDATEFILE_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_USIM, sizeof(USIMM_UPDATEFILE_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR == pUsimSetFileRsp)
    {
        return;
    }

    pUsimSetFileRsp->stCmdResult.enMsgName          = USIMM_UPDATEFILE_CNF;
    pUsimSetFileRsp->stCmdResult.ulReceiverPid      = ulDestTskId;
    pUsimSetFileRsp->stCmdResult.ulReceiverCpuId    = VOS_LOCAL_CPUID;       /* ������Ϣ����                             */

    pUsimSetFileRsp->stCmdResult.ulResult           = ulResult;                                             /* ��ȡ�ļ��Ľ��                           */
    pUsimSetFileRsp->stCmdResult.ulErrorCode        = USIMM_SW_MEMORY_ERROR;
    /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    pUsimSetFileRsp->stFilePath.ulPathLen           = ulPathLength;
    PS_MEM_CPY(pUsimSetFileRsp->stFilePath.acPath, pucFilePathStr, pUsimSetFileRsp->stFilePath.ulPathLen + 1);
    /* Modified by h00313353 for iteration 9, 2015-2-6, end */
    pUsimSetFileRsp->ucRecordNum                    = ucRecordNum;                                          /* linear fixed��cycle fixed����EF��¼��    */

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_USIM, pUsimSetFileRsp))
    {
        NAS_WARNING_LOG(WUEPS_PID_USIM, "MN_MSG_Usim_Stub():WARNING:SEND MSG FIAL");
    }
}


VOS_VOID MSG_SmssFileContentToMem(
    VOS_UINT8                           *pucEf,
    VOS_UINT16                          usEfLen
)
{
    MN_MSG_SMSS_INFO_STRU               stSmssInfo;

    stSmssInfo.ucLastUsedTpMr = *(pucEf);
    if (MN_MSG_SIM_MEM_FULL_SET == *(pucEf + 1))
    {
        stSmssInfo.enMemCapExcNotFlag = MN_MSG_MEM_FULL_SET;
    }
    else
    {
        stSmssInfo.enMemCapExcNotFlag = MN_MSG_MEM_FULL_UNSET;
    }
    MN_MSG_UpdateSmssInfo(VOS_TRUE, &stSmssInfo, usEfLen);

    return;
}

/*****************************************************************************
 �� �� ��  : MSG_UpdateMemSmStatus
 ��������  : дUSIM��ʧ�ܺ�,��Ҫ���ڴ��еĶ���״̬�ָ�Ϊԭ����״̬,�ú�����Ҫ����
 Read,List,Modify Sm�Ȳ���
 �������  : ucRecIndex   -  ��Ҫ���µ�����λ��
             ucStatus     - ��Ҫ�����ڴ��е�״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��15��
    ��    ��   : �ܾ� 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
LOCAL VOS_VOID MSG_UpdateMemSmStatus(
    VOS_UINT8                           ucRecIndex,
    VOS_UINT8                           ucStatus
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];

    PS_MEM_SET(aucSmContent,(VOS_CHAR)0XFF,MN_MSG_EFSMS_LEN);
    ulRet = MN_MSG_ReadSmsInfo(MN_MSG_MEM_STORE_SIM,ucRecIndex,aucSmContent);
    if (MN_ERR_NO_ERROR == ulRet)
    {
        aucSmContent[0] = ucStatus;
        MN_MSG_UpdateEachMemSmInfo(ucRecIndex,aucSmContent,MN_MSG_EFSMS_LEN);
    }
}


LOCAL VOS_VOID MSG_ProcEfSmssGetFileRsp(
    VOS_VOID                            *pMsg
)
{
    /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    USIMM_READFILE_CNF_STRU            *pUsimGetFileRsp;
    /* Modified by h00313353 for iteration 9, 2015-2-6, end */
    MN_MSG_USIM_POWER_STATE_ENUM_U8     enPowerState;
    MN_MSG_SMSS_INFO_STRU               stSmssInfo;

    pUsimGetFileRsp = (USIMM_READFILE_CNF_STRU *) pMsg;
    PS_MEM_SET(&stSmssInfo,0X00,sizeof(stSmssInfo));
    MN_MSG_GetUsimPowerState(&enPowerState);

    MN_INFO_LOG1("MSG_ProcEfSmssGetFileRsp: enPowerState is ", enPowerState);
    if (MN_MSG_USIM_POWER_WAIT_EFSMSS == enPowerState)
    {
        MN_MSG_StopTimer(MN_MSG_TID_WAIT_GET_EF_RSP);
        if (VOS_OK == (pUsimGetFileRsp->stCmdResult.ulResult))
        {
            MSG_SmssFileContentToMem(pUsimGetFileRsp->aucEf, pUsimGetFileRsp->usEfLen);
        }
        else
        {
            MN_WARN_LOG("MSG_ProcEfSmssGetFileRsp:the Rsp of Usim is Failed");
        }

        /*��ȡEFSMSP�ļ�������*/
        /* Modified by h00313353 for iteration 9, 2015-3-9, begin */
        if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
        {
            MN_MSG_GetUsimParmReq(USIMM_USIM_EFSMSP_ID);
        }
        else
        {
            MN_MSG_GetUsimParmReq(USIMM_TELE_EFSMSP_ID);
        }
        /* Modified by h00313353 for iteration 9, 2015-3-9, end */
    }
    else
    {
        MN_WARN_LOG("MSG_ProcEfSmssGetFileRsp:Invalid State");
    }
}
LOCAL VOS_VOID MSG_ProcEfSmspGetFileRsp(
    VOS_VOID                            *pMsg
)
{
    USIMM_READFILE_CNF_STRU            *pUsimGetFileRsp;
    MN_MSG_USIM_POWER_STATE_ENUM_U8     enPowerState;

    pUsimGetFileRsp = (USIMM_READFILE_CNF_STRU *) pMsg;
    MN_MSG_GetUsimPowerState(&enPowerState);
    MN_INFO_LOG1("MSG_ProcEfSmspGetFileRsp: enPowerState is ", enPowerState);
    MN_INFO_LOG1("MSG_ProcEfSmspGetFileRsp: pUsimGetFileRsp->ulResult is ", (long)pUsimGetFileRsp->stCmdResult.ulResult);
    if (MN_MSG_USIM_POWER_WAIT_EFSMSP == enPowerState)
    {
        MN_MSG_StopTimer(MN_MSG_TID_WAIT_GET_EF_RSP);
        if (VOS_OK == pUsimGetFileRsp->stCmdResult.ulResult)
        {
            MN_MSG_UpdateTotalSmspInfo(VOS_TRUE,
                                       pUsimGetFileRsp->ucTotalNum,               /*�ļ��д洢��¼�ĸ������� 1��ʼΪ��¼������ */
                                       (VOS_UINT8)pUsimGetFileRsp->usEfLen,
                                       pUsimGetFileRsp->aucEf);
        }
        else
        {
            MN_WARN_LOG("MSG_ProcEfSmssGetFileRsp:the Rsp of Usim is Failed");
        }
        MN_MSG_SmspInitFinish(MN_CLIENT_ALL);
        /* Modified by h00313353 for iteration 9, 2015-3-9, begin */
        if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
        {
            MN_MSG_GetUsimParmReq(USIMM_USIM_EFSMS_ID);
        }
        else
        {
            MN_MSG_GetUsimParmReq(USIMM_TELE_EFSMS_ID);
        }
        /* Modified by h00313353 for iteration 9, 2015-3-9, end */
    }
    else
    {
        MN_WARN_LOG("MSG_ProcEfSmspGetFileRsp:Invalid State");
    }
    MN_INFO_LOG("MSG_ProcEfSmspGetFileRsp: step out of function.");
}
LOCAL VOS_VOID MSG_ProcEfSmsGetFileRsp(
    VOS_VOID                            *pMsg
)
{
    /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    USIMM_READFILE_CNF_STRU            *pUsimGetFileRsp;
    /* Modified by h00313353 for iteration 9, 2015-2-6, end */
    MN_MSG_USIM_POWER_STATE_ENUM_U8     enPowerState;
    MN_MSG_USIM_EFUST_INFO_STRU         stUstInfo;
    VOS_UINT32                          ulRet;
    /* Added by h00313353 for iteration 9, 2015-3-9, begin */
    VOS_UINT32                          ulFileId;

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId    = USIMM_USIM_EFSMS_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMS_ID;
    }
    /* Added by h00313353 for iteration 9, 2015-3-9, end */

    pUsimGetFileRsp = (USIMM_READFILE_CNF_STRU *) pMsg;
    PS_MEM_SET(&stUstInfo,0X00,sizeof(stUstInfo));
    MN_MSG_GetUsimPowerState(&enPowerState);
    MN_INFO_LOG1("MSG_ProcEfSmsGetFileRsp: enPowerState is ", enPowerState);
    if (MN_MSG_USIM_POWER_WAIT_EFSMS == enPowerState)
    {
        MN_MSG_StopTimer(MN_MSG_TID_WAIT_GET_EF_RSP);
        if (VOS_OK == (pUsimGetFileRsp->stCmdResult.ulResult))
        {
            MN_MSG_UpdateEachMemSmInfo(f_ucMsgCurrSmRec - 1,
                                       pUsimGetFileRsp->aucEf,
                                       MN_MSG_EFSMS_LEN);
        }
        else
        {
            MN_WARN_LOG("MSG_ProcEfSmsGetFileRsp:the Rsp of Usim is Failed");
        }
/* ���USIM׮�ļ�����: �����EFSMS�ļ���¼������ʵ������ļ�¼���� */
#ifndef __PS_WIN32_RECUR__
        /*������ж���δ��ȡ��,��ȡ��һ����¼,�����ȡ�ļ�EFSMSR������*/
        if (f_ucMsgCurrSmRec < MN_MSG_GetSmCapacity(MN_MSG_MEM_STORE_SIM))
        {
            f_ucMsgCurrSmRec++;
            /* Modified by h00313353 for iteration 9, 2015-3-9, begin */
            ulRet = MN_MSG_SndUsimGetFileReq((VOS_UINT16)ulFileId,f_ucMsgCurrSmRec);
            /* Modified by h00313353 for iteration 9, 2015-3-9, end */
            if (USIMM_API_SUCCESS == ulRet)
            {
                return;
            }
        }
        else
#endif
        {
            f_ucMsgCurrSmRec = 1;
        }
        /* Modified by h00313353 for iteration 9, 2015-3-9, begin */
        if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
        {
            MN_MSG_GetUsimParmReq(USIMM_USIM_EFSMSR_ID);
        }
        else
        {
            MN_MSG_GetUsimParmReq(USIMM_TELE_EFSMSR_ID);
        }
        /* Modified by h00313353 for iteration 9, 2015-3-9, end */
    }
    else
    {
        MN_WARN_LOG("MSG_ProcEfSmsGetFileRsp:Invalid State");
    }
}


LOCAL VOS_VOID MSG_ProcEfSmsrGetFileRsp(
    VOS_VOID                            *pMsg
)
{
    /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    USIMM_READFILE_CNF_STRU            *pUsimGetFileRsp;
    /* Modified by h00313353 for iteration 9, 2015-2-6, end */
    MN_MSG_USIM_POWER_STATE_ENUM_U8     enPowerState;

    pUsimGetFileRsp = (USIMM_READFILE_CNF_STRU *) pMsg;
    MN_MSG_GetUsimPowerState(&enPowerState);
    MN_INFO_LOG1("MSG_ProcEfSmsrGetFileRsp: enPowerState is ", enPowerState);
    if (MN_MSG_USIM_POWER_WAIT_EFSMSR == enPowerState)
    {
        MN_MSG_StopTimer(MN_MSG_TID_WAIT_GET_EF_RSP);
        if (VOS_OK == (pUsimGetFileRsp->stCmdResult.ulResult))
        {
            MN_MSG_UpdateTotalSmsrInfo(VOS_TRUE,
                                       pUsimGetFileRsp->ucTotalNum,               /*�ļ��д洢��¼�ĸ������� 1��ʼΪ��¼������ */
                                       pUsimGetFileRsp->usEfLen,
                                       pUsimGetFileRsp->aucEf);
        }
        else
        {
            MN_WARN_LOG("MSG_ProcEfSmsrGetFileRsp:the Rsp of Usim is Failed");
        }
        /* Modified by h00313353 for iteration 9, 2015-3-9, begin */
        MN_MSG_GetUsimParmReq(USIMM_DEF_FILEID_BUTT);
        /* Modified by h00313353 for iteration 9, 2015-3-9, end */
    }
    else
    {
        MN_WARN_LOG("MSG_ProcEfSmsrGetFileRsp:Invalid State");
    }
}
LOCAL VOS_VOID  MSG_ReadSaveUsimMsgRsp(
    VOS_VOID                            *pMsg,
    MN_CLIENT_ID_T                      clientId
)
{
    USIMM_UPDATEFILE_CNF_STRU           *pUsimSetFileRsp;
    VOS_UINT8                           ucRecIndex;
    MN_OPERATION_ID_T                   bcOpId;

    pUsimSetFileRsp = (USIMM_UPDATEFILE_CNF_STRU *) pMsg;
    if (VOS_OK == (pUsimSetFileRsp->stCmdResult.ulResult))
    {
        /*�㲥�ϱ�USIM�ж����ѷ����˸ı�*/
        bcOpId = MN_MSG_GetBCopId();
        MN_MSG_ReportSmChanged(clientId,bcOpId,VOS_TRUE,MN_MSG_MEM_STORE_SIM);
    }
    else
    {
        ucRecIndex = pUsimSetFileRsp->ucRecordNum - 1;
        /*���޸ĵ��Ѷ����Żָ���δ�����ŵ�״̬*/
        MSG_UpdateMemSmStatus(ucRecIndex,EF_SMS_STATUS_MT_TO_BE_READ);
        MN_WARN_LOG("MSG_ReadSaveUsimMsgRsp:Usim Returns Error");
    }
}


LOCAL VOS_VOID MSG_ListSaveUsimMsgRsp(
    VOS_VOID                            *pMsg,
    MN_CLIENT_ID_T                      clientId
)
{
    USIMM_UPDATEFILE_CNF_STRU          *pUsimSetFileRsp;
    VOS_UINT8                           ucRecIndex;
    VOS_UINT8                           ucSetUsimRec;
    MN_OPERATION_ID_T                   bcOpId;

    pUsimSetFileRsp = (USIMM_UPDATEFILE_CNF_STRU *) pMsg;
    f_stMsgUsimReturnRec.ucListSetRec++;
    if (VOS_OK == (pUsimSetFileRsp->stCmdResult.ulResult))
    {
        f_stMsgUsimReturnRec.ucListSuccRec++;
    }
    else
    {
        ucRecIndex = pUsimSetFileRsp->ucRecordNum - 1;
        /*���޸ĵ��Ѷ����Żָ���δ�����ŵ�״̬*/
        MSG_UpdateMemSmStatus(ucRecIndex,EF_SMS_STATUS_MT_TO_BE_READ);
        MN_WARN_LOG("MSG_ListSaveUsimMsgRsp:USIM Returns Error");
    }

    ucSetUsimRec = MN_MSG_GetUsimRec(MN_MSG_SET_USIM_LIST);
    /*LISTʱ,��������USIM�ļ�¼��������*/
    if (f_stMsgUsimReturnRec.ucListSetRec == ucSetUsimRec)
    {
        if (f_stMsgUsimReturnRec.ucListSuccRec > 0)
        {
            /*�㲥�ϱ�USIM�ж����ѷ����˸ı�*/
            bcOpId = MN_MSG_GetBCopId();
            MN_MSG_ReportSmChanged(clientId,bcOpId,VOS_TRUE,MN_MSG_MEM_STORE_SIM);
        }
        f_stMsgUsimReturnRec.ucListSuccRec = 0;
        f_stMsgUsimReturnRec.ucListSetRec = 0;
        MN_MSG_SetUsimRec(MN_MSG_SET_USIM_LIST,0);
    }
}
LOCAL VOS_VOID MSG_WriteSaveUsimMsgRsp(
    VOS_VOID                            *pMsg,
    const MN_MSG_USIM_INFO_STRU         *pstSmaUsimInfo
)
{
    /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    USIMM_UPDATEFILE_CNF_STRU          *pUsimSetFileRsp;
    /* Modified by h00313353 for iteration 9, 2015-2-6, end */
    VOS_UINT8                           ucRecIndex;
    MN_MSG_WRITE_EVT_INFO_STRU          stWriteEvt;
    VOS_UINT8                           ucStatus;
    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
    MN_OPERATION_ID_T                   bcOpId;
    VOS_UINT32                          ulRslt;

    ucStatus = 0;


    PS_MEM_SET(&stWriteEvt,0X00,sizeof(stWriteEvt));
    pUsimSetFileRsp = (USIMM_UPDATEFILE_CNF_STRU *) pMsg;
    ucRecIndex = pUsimSetFileRsp->ucRecordNum - 1;
    stWriteEvt.enMemStroe = MN_MSG_MEM_STORE_SIM;
    stWriteEvt.ulIndex = ucRecIndex;
    ulRslt = MN_MSG_GetStatus(MN_MSG_MEM_STORE_SIM,ucRecIndex,&ucStatus);
    if (MN_ERR_NO_ERROR != ulRslt)
    {
        MN_WARN_LOG("MSG_WriteSaveUsimMsgRsp:MN_MSG_GetStatus Returns Error");
    }
    MN_MSG_GetAppStatus(ucStatus, &stWriteEvt.enStatus);
    if (VOS_OK == (pUsimSetFileRsp->stCmdResult.ulResult))
    {
        /*�ϱ�д�ļ��ɹ�*/
        stWriteEvt.bSuccess = VOS_TRUE;
        stWriteEvt.ulFailCause = MN_ERR_NO_ERROR;
        MN_MSG_ReportWriteEvent(pstSmaUsimInfo->clientId,pstSmaUsimInfo->opId,&stWriteEvt,MN_MSG_EVT_WRITE);
        /*�㲥�ϱ�USIM�еĶ��ŷ����˱仯*/
        bcOpId = MN_MSG_GetBCopId();
        MN_MSG_ReportSmChanged(pstSmaUsimInfo->clientId,bcOpId,VOS_TRUE,MN_MSG_MEM_STORE_SIM);
    }
    else
    {
        MN_MSG_RecoverOrgSm(ucRecIndex%MN_MSG_MAX_ORG_REC_NUM,aucSmContent);
        MN_MSG_UpdateEachMemSmInfo(ucRecIndex,aucSmContent,MN_MSG_EFSMS_LEN);
        /*�ϱ�д�ļ�ʧ��*/
        stWriteEvt.bSuccess = VOS_FALSE;
        if (USIMM_SW_MEMORY_ERROR == (pUsimSetFileRsp->stCmdResult.ulErrorCode))
        {
            stWriteEvt.ulFailCause = MN_ERR_CLASS_SMS_USIM_MEM_ERROR;
        }
        else
        {
            stWriteEvt.ulFailCause = MN_ERR_CLASS_SMS_UPDATE_USIM;
        }
        MN_MSG_ReportWriteEvent(pstSmaUsimInfo->clientId,pstSmaUsimInfo->opId,&stWriteEvt,MN_MSG_EVT_WRITE);
        MN_WARN_LOG("MSG_WriteSaveUsimMsgRsp:Usim Returns Error");
    }
}
LOCAL VOS_VOID MSG_DeleteSaveUsimMsgRsp(
    VOS_VOID                            *pMsg,
    const MN_MSG_USIM_INFO_STRU         *pstSmaUsimInfo
)
{
    USIMM_UPDATEFILE_CNF_STRU          *pUsimSetFileRsp;
    VOS_UINT8                           ucRecIndex;
    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
    VOS_UINT8                           ucSetUsimRec;
    VOS_BOOL                            bReportFlag;
    VOS_BOOL                            bDeleteAll;
    VOS_UINT32                          ulDeleteCount;
    VOS_UINT32                          ulRet;
    MN_MSG_DELETE_EVT_INFO_STRU         stDeleteInfo;
    MN_OPERATION_ID_T                   bcOpId;


    ulDeleteCount = 0;


    pUsimSetFileRsp = (USIMM_UPDATEFILE_CNF_STRU *) pMsg;
    ucRecIndex = pUsimSetFileRsp->ucRecordNum - 1;
    PS_MEM_SET(&stDeleteInfo,0X00,sizeof(stDeleteInfo));

    stDeleteInfo.enDeleteType = pstSmaUsimInfo->enDeleteType;
    stDeleteInfo.enMemStore = MN_MSG_MEM_STORE_SIM;
    stDeleteInfo.ulIndex = ucRecIndex;
    if (MN_MSG_DELETE_SINGLE == pstSmaUsimInfo->enDeleteType)
    {
        if (VOS_OK == (pUsimSetFileRsp->stCmdResult.ulResult))
        {
            stDeleteInfo.bSuccess = VOS_TRUE;
            stDeleteInfo.ulFailCause = MN_ERR_NO_ERROR;
            MN_MSG_ReportDeleteEvent(pstSmaUsimInfo->clientId,
                                      pstSmaUsimInfo->opId,
                                      &stDeleteInfo,
                                      MN_MSG_EVT_DELETE);
            /*�㲥�ϱ�USIM�ж��ŷ����˸ı�*/
            bcOpId = MN_MSG_GetBCopId();
            MN_MSG_ReportSmChanged(pstSmaUsimInfo->clientId,bcOpId,VOS_TRUE,MN_MSG_MEM_STORE_SIM);
            /*�鿴�Ƿ���Ҫ֪ͨ��������ڴ�*/
            MN_MSG_StartMemNotification();
        }
        else
        {
            MN_MSG_RecoverOrgSm(ucRecIndex%MN_MSG_MAX_ORG_REC_NUM,aucSmContent);
            MN_MSG_UpdateEachMemSmInfo(ucRecIndex,aucSmContent,MN_MSG_EFSMS_LEN);
            stDeleteInfo.bSuccess = VOS_FALSE;
            stDeleteInfo.ulFailCause = MN_ERR_CLASS_SMS_UPDATE_USIM;
            MN_MSG_ReportDeleteEvent(pstSmaUsimInfo->clientId,
                                     pstSmaUsimInfo->opId,
                                     &stDeleteInfo,
                                     MN_MSG_EVT_DELETE);
        }
    }
    else
    {
        f_stMsgUsimReturnRec.ucDeleteSetRec++;
        if (VOS_OK == (pUsimSetFileRsp->stCmdResult.ulResult))
        {
            f_stMsgUsimReturnRec.ucDeleteSuccRec++;
            /*�鿴�Ƿ���Ҫ֪ͨ��������ڴ�*/
            MN_MSG_StartMemNotification();
        }
        else
        {
            /*��ԭԭ���Ķ�������*/
            MN_MSG_RecoverOrgSm(ucRecIndex%MN_MSG_MAX_ORG_REC_NUM,aucSmContent);
            MN_MSG_UpdateEachMemSmInfo(ucRecIndex,aucSmContent,MN_MSG_EFSMS_LEN);
        }
        ucSetUsimRec = MN_MSG_GetUsimRec(MN_MSG_SET_USIM_DELETE);
        if (ucSetUsimRec == f_stMsgUsimReturnRec.ucDeleteSetRec)
        {
            MN_MSG_SetUsimRec(MN_MSG_SET_USIM_DELETE,0);
            /*��ȡ��ǰ�Ƿ����ϱ�ɾ�����ŵĽ��*/
            bReportFlag = MN_MSG_GetDeleteReportFlag(MN_MSG_SET_USIM_DELETE);
            if (ucSetUsimRec == f_stMsgUsimReturnRec.ucDeleteSuccRec)
            {
                /*ɾ������Ѿ��ϱ�,���ϱ�USIM�ж��ŷ����˸ı�*/
                if (VOS_TRUE == bReportFlag)
                {
                    /*�㲥�ϱ�USIM�ж��ŷ����˸ı�*/
                    bcOpId = MN_MSG_GetBCopId();
                    MN_MSG_ReportSmChanged(pstSmaUsimInfo->clientId,bcOpId,VOS_TRUE,MN_MSG_MEM_STORE_SIM);
                }
                else
                {
                    /*����δ��ȫ��ɾ�����,����Ҫɾ��*/
                    ulRet = MN_MSG_DeleteMultiSm(pstSmaUsimInfo->clientId,
                                                 pstSmaUsimInfo->opId,
                                                 MN_MSG_MEM_STORE_SIM,
                                                 pstSmaUsimInfo->enDeleteType,
                                                 &bDeleteAll,
                                                 &ulDeleteCount);
                    if (MN_ERR_NO_ERROR != ulRet)
                    {
                        /*ɾ��ʧ��*/
                        stDeleteInfo.bSuccess = VOS_FALSE;
                        stDeleteInfo.ulFailCause = MN_ERR_CLASS_SMS_UPDATE_USIM;
                        MN_MSG_ReportDeleteEvent(pstSmaUsimInfo->clientId,
                                                 pstSmaUsimInfo->opId,
                                                 &stDeleteInfo,
                                                 MN_MSG_EVT_DELETE);

                        /*�������µ�ɾ��*/
                        if (0 == ulDeleteCount)
                        {
                            /*�㲥�ϱ�USIM�ж��ŷ����˸ı�*/
                            bcOpId = MN_MSG_GetBCopId();
                            MN_MSG_ReportSmChanged(pstSmaUsimInfo->clientId,bcOpId,VOS_TRUE,MN_MSG_MEM_STORE_SIM);
                        }
                    }
                    else if (0 == ulDeleteCount) /*�����Ѿ���ȫɾ��*/
                    {
                       /*����ȫ��ɾ�����,�ϱ�ɾ���ɹ�*/
                       stDeleteInfo.bSuccess = VOS_TRUE;
                       stDeleteInfo.ulFailCause = MN_ERR_NO_ERROR;
                       MN_MSG_ReportDeleteEvent(pstSmaUsimInfo->clientId,
                                                pstSmaUsimInfo->opId,
                                                &stDeleteInfo,
                                                MN_MSG_EVT_DELETE);
                       /*�㲥�ϱ�USIM�ж��ŷ����˸ı�*/
                       bcOpId = MN_MSG_GetBCopId();
                       MN_MSG_ReportSmChanged(pstSmaUsimInfo->clientId,bcOpId,VOS_TRUE,MN_MSG_MEM_STORE_SIM);
                    }
                    else
                    {
                    }
                }
            }
            else /*�ж���ɾ��ʧ��,�ϱ�ɾ������ʧ��*/
            {
                if (VOS_FALSE == bReportFlag)
                {
                    stDeleteInfo.bSuccess = VOS_FALSE;
                    stDeleteInfo.ulFailCause = MN_ERR_CLASS_SMS_UPDATE_USIM;
                    MN_MSG_ReportDeleteEvent(pstSmaUsimInfo->clientId,
                                             pstSmaUsimInfo->opId,
                                             &stDeleteInfo,
                                             MN_MSG_EVT_DELETE);
                    MN_MSG_SetUsimRec(MN_MSG_SET_USIM_DELETE_BEGIN,0);
                    MN_MSG_SetDeleteReportFlag(MN_MSG_SET_USIM_DELETE,VOS_TRUE);
                }
                if (f_stMsgUsimReturnRec.ucDeleteSuccRec > 0)
                {
                    /*�㲥�ϱ�USIM�ж��ŷ����˸ı�*/
                    bcOpId = MN_MSG_GetBCopId();
                    MN_MSG_ReportSmChanged(pstSmaUsimInfo->clientId,bcOpId,VOS_TRUE,MN_MSG_MEM_STORE_SIM);
                }
            }
            f_stMsgUsimReturnRec.ucDeleteSetRec = 0;
            f_stMsgUsimReturnRec.ucDeleteSuccRec = 0;
        }
    }
}


LOCAL VOS_VOID MSG_ModifySaveUsimMsgRsp(
    VOS_VOID                            *pMsg,
    const MN_MSG_USIM_INFO_STRU         *pstSmaUsimInfo
)
{
    /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    USIMM_UPDATEFILE_CNF_STRU          *pUsimSetFileRsp;
    /* Modified by h00313353 for iteration 9, 2015-2-6, end */
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
    VOS_UINT8                           ucRecIndex;
    MN_MSG_MODIFY_STATUS_EVT_INFO_STRU  stModifyStatusEvt;
    MN_MSG_STATUS_TYPE_ENUM_U8          enStatus;
    MN_OPERATION_ID_T                   bcOpId;

    pUsimSetFileRsp = (USIMM_UPDATEFILE_CNF_STRU *) pMsg;
    PS_MEM_SET(aucSmContent,(VOS_CHAR)0XFF,MN_MSG_EFSMS_LEN);
    PS_MEM_SET(&stModifyStatusEvt,0X00,sizeof(stModifyStatusEvt));
    ucRecIndex = pUsimSetFileRsp->ucRecordNum - 1;
    ulRet = MN_MSG_ReadSmsInfo(MN_MSG_MEM_STORE_SIM,ucRecIndex,aucSmContent);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return;
    }
    MN_MSG_GetAppStatus(aucSmContent[0],&enStatus);
    stModifyStatusEvt.enMemStore = MN_MSG_MEM_STORE_SIM;
    stModifyStatusEvt.ulIndex = pstSmaUsimInfo->ucRecIndex;
    stModifyStatusEvt.enStatus = enStatus;
    if (VOS_OK == (pUsimSetFileRsp->stCmdResult.ulResult))
    {
        stModifyStatusEvt.bSuccess = VOS_TRUE;
        stModifyStatusEvt.ulFailCause = MN_ERR_NO_ERROR;
         /*�ϱ��޸ĳɹ�*/
        MN_MSG_ReportModifyEvent(pstSmaUsimInfo->clientId,
                                 pstSmaUsimInfo->opId,
                                 &stModifyStatusEvt,
                                 MN_MSG_EVT_MODIFY_STATUS);
        /*�㲥�ϱ�USIM�ж����ѷ����˸ı�*/
        bcOpId = MN_MSG_GetBCopId();
        MN_MSG_ReportSmChanged(pstSmaUsimInfo->clientId,bcOpId,VOS_TRUE,MN_MSG_MEM_STORE_SIM);
    }
    else
    {
        MN_MSG_RecoverOrgSm(ucRecIndex%MN_MSG_MAX_ORG_REC_NUM,aucSmContent);
        MN_MSG_UpdateEachMemSmInfo(ucRecIndex,aucSmContent,MN_MSG_EFSMS_LEN);
        /*�ϱ��޸�ʧ��*/
        stModifyStatusEvt.bSuccess = VOS_FALSE;
        if (USIMM_SW_MEMORY_ERROR == (pUsimSetFileRsp->stCmdResult.ulErrorCode))
        {
            stModifyStatusEvt.ulFailCause = MN_ERR_CLASS_SMS_USIM_MEM_ERROR;
        }
        else
        {
            stModifyStatusEvt.ulFailCause = MN_ERR_CLASS_SMS_UPDATE_USIM;
        }
        MN_SendClientEvent(pstSmaUsimInfo->clientId,
                           MN_CALLBACK_MSG,
                           MN_MSG_EVT_MODIFY_STATUS,
                           (VOS_VOID *)&stModifyStatusEvt);
        MN_WARN_LOG("MSG_ModifySaveUsimMsgRsp:Usim Returns Error");
    }
}
LOCAL VOS_VOID MSG_RcvSaveUsimMsgRsp(
    VOS_VOID                            *pMsg,
    const MN_MSG_USIM_INFO_STRU         *pstSmaUsimInfo
)
{
    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
    /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    USIMM_UPDATEFILE_CNF_STRU          *pUsimSetFileRsp;
    /* Modified by h00313353 for iteration 9, 2015-2-6, end */
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucRecIndex;
    MN_MSG_BCD_ADDR_STRU                stScAddr;
    MN_MSG_RAW_TS_DATA_STRU             stRawData;
    VOS_UINT8                           ucStatus;
    MN_OPERATION_ID_T                   bcopId;
    MN_MSG_DELIVER_EVT_INFO_STRU        stDeliverEvt;
    MN_MSG_CONFIG_PARM_STRU             stCfgParm;
    MN_CLIENT_ID_T                      clientId;
    MN_MSG_WRITE_EFSMS_CAUSE_ENUM_U32   enEfsmsCause;

    clientId = pstSmaUsimInfo->clientId;
    pUsimSetFileRsp = (USIMM_UPDATEFILE_CNF_STRU *) pMsg;
    ucRecIndex   = pUsimSetFileRsp->ucRecordNum - 1;
    PS_MEM_SET(aucSmContent,(VOS_CHAR)0xFF,MN_MSG_EFSMS_LEN);
    PS_MEM_SET(&stCfgParm,0X00,sizeof(stCfgParm));

    PS_MEM_SET(&stRawData, 0x00, sizeof(stRawData));

    if (VOS_OK == (pUsimSetFileRsp->stCmdResult.ulResult))
    {
        MN_MSG_Internal_SendRpt(VOS_TRUE,0,0);
        ulRet = MN_MSG_ReadSmsInfo(MN_MSG_MEM_STORE_SIM,ucRecIndex,aucSmContent);

        if ((MN_ERR_NO_ERROR == ulRet)
         && (EF_SMS_STATUS_MT_TO_BE_READ == (aucSmContent[0] & 0x03)))
        {
            ulRet = MN_MSG_ParseEFSmContent(aucSmContent,&stScAddr,&stRawData,&ucStatus);
            if (MN_ERR_NO_ERROR != ulRet)
            {
                MN_WARN_LOG("MSG_RcvSaveUsimMsgRsp: MN_MSG_ParseEFSmContent ErrCode ");
            }
            /*�㲥�ϱ��յ�һ���¶���*/
            bcopId = MN_MSG_GetBCopId();
            stCfgParm.enRcvSmAct = MN_MSG_RCVMSG_ACT_STORE;
            stCfgParm.enSmMemStore = MN_MSG_MEM_STORE_SIM;
            MSG_BuildDeliverEvtParm(&stCfgParm,&stScAddr,&stRawData,&stDeliverEvt);
            stDeliverEvt.ulInex = pstSmaUsimInfo->ucRecIndex;
            MN_MSG_ReportRcvMsgEvent(bcopId,&stDeliverEvt);
            bcopId = MN_MSG_GetBCopId();
            MN_MSG_ReportSmChanged(clientId,bcopId,VOS_TRUE,MN_MSG_MEM_STORE_SIM);
        }
        else
        {
            MN_WARN_LOG("MSG_RcvSaveUsimMsgRsp,Not Find Proper Sm");
        }
    }
    else
    {
        MSG_UpdateMemSmStatus(ucRecIndex,EF_SMS_STATUS_FREE_SPACE);
        MN_WARN_LOG("MSG_RcvSaveUsimMsgRsp,Usim Returns Error");

        if (USIMM_SW_MEMORY_ERROR == (pUsimSetFileRsp->stCmdResult.ulErrorCode))
        {
            enEfsmsCause = MN_MSG_WRITE_EFSMS_CAUSE_MEM_PROBLEM;
            MN_MSG_UpdateSmsInfo(VOS_TRUE, 0);
        }
        else
        {
            enEfsmsCause = MN_MSG_WRITE_EFSMS_CAUSE_UNSEPCIFIC;
        }

        MN_MSG_FailToWriteEfsms(MN_MSG_MEM_STORE_SIM, enEfsmsCause);
    }
}


LOCAL VOS_VOID  MSG_SendSaveUsimMsgRsp(
    VOS_VOID                            *pMsg,
    MN_CLIENT_ID_T                      clientId
)
{
    /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    USIMM_UPDATEFILE_CNF_STRU          *pUsimSetFileRsp;
    /* Modified by h00313353 for iteration 9, 2015-2-6, end */
    VOS_UINT8                           ucRecIndex;
    MN_OPERATION_ID_T                   bcOpId;

    pUsimSetFileRsp = (USIMM_UPDATEFILE_CNF_STRU *) pMsg;
    ucRecIndex   = pUsimSetFileRsp->ucRecordNum - 1;

    if (VOS_OK == (pUsimSetFileRsp->stCmdResult.ulResult))
    {
        /*�㲥�ϱ�USIM�ж��ŷ����˸ı�*/
        bcOpId = MN_MSG_GetBCopId();
        MN_MSG_ReportSmChanged(clientId,bcOpId,VOS_TRUE,MN_MSG_MEM_STORE_SIM);
    }
    else
    {
        /*�����ڴ��и������ŵ�״̬,��Ϊ�ն���*/
        MSG_UpdateMemSmStatus(ucRecIndex,EF_SMS_STATUS_FREE_SPACE);
        /*���¸ö��ŵĴ洢����Ϊ���洢*/
        MN_MSG_UpdateMoSaveInfo(MN_MSG_MEM_STORE_NONE,0);
        MN_WARN_LOG("MSG_RcvSaveUsimMsgRsp,Usim Returns Error");
    }
}
LOCAL VOS_VOID MSG_RcvMoRptSaveUsimMsgRsp(
    VOS_VOID                            *pMsg,
    MN_CLIENT_ID_T                      clientId
)
{
    /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    USIMM_UPDATEFILE_CNF_STRU           *pUsimSetFileRsp;
    /* Modified by h00313353 for iteration 9, 2015-2-6, end */
    VOS_UINT8                           ucRecIndex;
    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
    MN_OPERATION_ID_T                   bcOpId;

    pUsimSetFileRsp = (USIMM_UPDATEFILE_CNF_STRU *) pMsg;
    PS_MEM_SET(aucSmContent,(VOS_CHAR)0XFF,MN_MSG_EFSMS_LEN);

    if (VOS_OK == (pUsimSetFileRsp->stCmdResult.ulResult))
    {
        /*�㲥�ϱ�USIM�ж����ѷ����˸ı�*/
        bcOpId = MN_MSG_GetBCopId();
        MN_MSG_ReportSmChanged(clientId,bcOpId,VOS_TRUE,MN_MSG_MEM_STORE_SIM);
    }
    else
    {
        ucRecIndex   = pUsimSetFileRsp->ucRecordNum - 1;
        /*��ԭ�ڴ��и������Ķ���*/
        MN_MSG_RecoverOrgSm(ucRecIndex%MN_MSG_MAX_ORG_REC_NUM,aucSmContent);
        MN_MSG_UpdateEachMemSmInfo(ucRecIndex,aucSmContent,MN_MSG_EFSMS_LEN);
        MN_WARN_LOG("MSG_RcvMoRptSaveUsimMsgRsp:Usim returns Error");
    }
}


LOCAL VOS_VOID MSG_WriteEfSmspUsimRsp(
    VOS_VOID                            *pMsg,
    const MN_MSG_USIM_INFO_STRU         *pstSmaUsimInfo
)
{
    /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    USIMM_UPDATEFILE_CNF_STRU          *pUsimSetFileRsp;
    /* Modified by h00313353 for iteration 9, 2015-2-6, end */
    VOS_UINT8                           ucRecIndex;
    MN_MSG_SRV_PARM_EVT_INFO_STRU       stSrvParmEvt;
    VOS_UINT32                          ulRet;
    MN_MSG_SRV_PARAM_STRU                stSrvParm;
    MN_MSG_USIM_EFSMSP_DTL_INFO_STRU    stOrgSrvParm;
    MN_OPERATION_ID_T                   bcopId;

    PS_MEM_SET(&stSrvParmEvt,0X00,sizeof(stSrvParmEvt));
    PS_MEM_SET(&stSrvParm,0X00,sizeof(stSrvParm));
    PS_MEM_SET(&stOrgSrvParm,0X00,sizeof(stOrgSrvParm));
    pUsimSetFileRsp = (USIMM_UPDATEFILE_CNF_STRU *) pMsg;
    ucRecIndex = pUsimSetFileRsp->ucRecordNum - 1;
    ulRet = MN_MSG_ReadSmspInfo(MN_MSG_MEM_STORE_SIM,ucRecIndex,&stSrvParm);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return;
    }
    stSrvParmEvt.operType = MN_MSG_OPER_SET;
    stSrvParmEvt.ulIndex = ucRecIndex;
    PS_MEM_CPY(&stSrvParmEvt.stSrvParm,&stSrvParm,sizeof(stSrvParmEvt.stSrvParm));
    bcopId = MN_MSG_GetBCopId();

    if (VOS_OK == (pUsimSetFileRsp->stCmdResult.ulResult))
    {
        /*�ϱ����óɹ�*/
        stSrvParmEvt.bSuccess = VOS_TRUE;
        stSrvParmEvt.ulFailCause = MN_ERR_NO_ERROR;
        MN_MSG_ReportSrvParmEvent(pstSmaUsimInfo->clientId,
                                   pstSmaUsimInfo->opId,
                                   &stSrvParmEvt,
                                   MN_MSG_EVT_WRITE_SRV_PARM);

        /*�㲥�ϱ�USIM�еĶ��Ų����ѷ����˸ı�*/
        MN_MSG_ReportSrvParmChanged(pstSmaUsimInfo->clientId,bcopId,MN_MSG_MEM_STORE_SIM);
    }
    else
    {
        /*�ָ��ڴ���ԭ��������*/
        MN_MSG_RecoverOrgSrvParm(ucRecIndex,&stOrgSrvParm);
        MN_MSG_UpdateEachMemSmspInfo(ucRecIndex,stOrgSrvParm.bUsed,&(stOrgSrvParm.stParm));
        /*�ϱ�����ʧ��*/
        stSrvParmEvt.bSuccess = VOS_FALSE;
        stSrvParmEvt.ulFailCause = MN_ERR_CLASS_SMS_UPDATE_USIM;
        MN_MSG_ReportSrvParmEvent(pstSmaUsimInfo->clientId,
                                   pstSmaUsimInfo->opId,
                                   &stSrvParmEvt,
                                   MN_MSG_EVT_WRITE_SRV_PARM);
        MN_WARN_LOG("MSG_WriteEfSmspUsimRsp:Usim Returns Error" );
    }
}


LOCAL VOS_VOID MSG_DeleteEfSmspUsimRsp(
    VOS_VOID                            *pMsg,
    const MN_MSG_USIM_INFO_STRU         *pstSmaUsimInfo
)
{
    /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    USIMM_UPDATEFILE_CNF_STRU          *pUsimSetFileRsp;
    /* Modified by h00313353 for iteration 9, 2015-2-6, end */
    VOS_UINT8                           ucRecIndex;
    MN_MSG_USIM_EFSMSP_DTL_INFO_STRU    stOrgSrvParm;
    VOS_UINT8                           ucSetUsimRec;
    MN_MSG_DELETE_EVT_INFO_STRU         stDeleteInfo;
    VOS_BOOL                            bReportFlag;
    MN_OPERATION_ID_T                   bcopId;

    pUsimSetFileRsp = (USIMM_UPDATEFILE_CNF_STRU *) pMsg;
    ucRecIndex = pUsimSetFileRsp->ucRecordNum - 1;
    PS_MEM_SET(&stOrgSrvParm,0X00,sizeof(stOrgSrvParm));
    PS_MEM_SET(&stDeleteInfo,0X00,sizeof(stDeleteInfo));

    stDeleteInfo.enDeleteType = pstSmaUsimInfo->enDeleteType;
    stDeleteInfo.enMemStore = MN_MSG_MEM_STORE_SIM;
    stDeleteInfo.ulIndex = ucRecIndex;
    bcopId = MN_MSG_GetBCopId();
    if (MN_MSG_DELETE_SINGLE == pstSmaUsimInfo->enDeleteType)
    {
        if (VOS_OK == (pUsimSetFileRsp->stCmdResult.ulResult))
        {
            /*�ϱ�ɾ���ɹ�*/
            stDeleteInfo.bSuccess = VOS_TRUE;
            stDeleteInfo.ulFailCause = MN_ERR_NO_ERROR;
            MN_MSG_ReportDeleteEvent(pstSmaUsimInfo->clientId,
                                     pstSmaUsimInfo->opId,
                                     &stDeleteInfo,
                                      MN_MSG_EVT_DELETE_SRV_PARM);
            /*�ϱ�USIM�Ķ��Ų��������˱仯*/
            MN_MSG_ReportSrvParmChanged(pstSmaUsimInfo->clientId,bcopId,MN_MSG_MEM_STORE_SIM);
        }
        else
        {
            /*�ָ��ڴ���ԭ��������*/
            MN_MSG_RecoverOrgSrvParm(ucRecIndex,&stOrgSrvParm);
            MN_MSG_UpdateEachMemSmspInfo(ucRecIndex,
                                         stOrgSrvParm.bUsed,
                                         &(stOrgSrvParm.stParm));

            /*�ϱ�ɾ��ʧ��*/
            stDeleteInfo.bSuccess = VOS_FALSE;
            stDeleteInfo.ulFailCause = MN_ERR_CLASS_SMS_UPDATE_USIM;
            MN_MSG_ReportDeleteEvent(pstSmaUsimInfo->clientId,
                                     pstSmaUsimInfo->opId,
                                     &stDeleteInfo,
                                     MN_MSG_EVT_DELETE_SRV_PARM);
        }
    }
    else
    {
        f_stMsgUsimReturnRec.ucDeleteSrvParmSetRec++;
        if (VOS_OK == (pUsimSetFileRsp->stCmdResult.ulResult))
        {
            f_stMsgUsimReturnRec.ucDeleteSrvParmSuccRec++;
        }
        else
        {
            /*�ָ��ڴ���ԭ��������*/
            MN_MSG_RecoverOrgSrvParm(ucRecIndex,&stOrgSrvParm);
            MN_MSG_UpdateEachMemSmspInfo(ucRecIndex,
                                         stOrgSrvParm.bUsed,
                                         &(stOrgSrvParm.stParm));
        }

        ucSetUsimRec = MN_MSG_GetUsimRec(MN_MSG_SET_USIM_DELETE_EFSMSP);
        if (ucSetUsimRec == f_stMsgUsimReturnRec.ucDeleteSrvParmSetRec)
        {
            MN_MSG_SetUsimRec(MN_MSG_SET_USIM_DELETE_EFSMSP,0);
            bReportFlag = MN_MSG_GetDeleteReportFlag(MN_MSG_SET_USIM_DELETE_EFSMSP);
            if (VOS_FALSE == bReportFlag)
            {
                if (ucSetUsimRec == f_stMsgUsimReturnRec.ucDeleteSrvParmSuccRec)
                {
                    /*�ϱ�ɾ���ɹ�*/
                    stDeleteInfo.bSuccess = VOS_TRUE;
                    stDeleteInfo.ulFailCause = MN_ERR_NO_ERROR;
                }
                else
                {
                    /*�ϱ�ɾ��ʧ��*/
                    stDeleteInfo.bSuccess = VOS_FALSE;
                    stDeleteInfo.ulFailCause = MN_ERR_CLASS_SMS_UPDATE_USIM;
                }
                MN_MSG_ReportDeleteEvent(pstSmaUsimInfo->clientId,
                                         pstSmaUsimInfo->opId,
                                         &stDeleteInfo,
                                         MN_MSG_EVT_DELETE_SRV_PARM);
            }
            /*�ϱ�USIM�Ķ��Ų��������˱仯*/
            if (f_stMsgUsimReturnRec.ucDeleteSrvParmSuccRec > 0)
            {
                MN_MSG_ReportSrvParmChanged(pstSmaUsimInfo->clientId,bcopId,MN_MSG_MEM_STORE_SIM);
            }
            f_stMsgUsimReturnRec.ucDeleteSrvParmSetRec = 0;
            f_stMsgUsimReturnRec.ucDeleteSrvParmSuccRec = 0;
        }
    }
}


LOCAL VOS_VOID  MSG_DeleteStaRptSaveUsimMsgRsp(
    VOS_VOID                            *pMsg,
    const MN_MSG_USIM_INFO_STRU         *pstSmaUsimInfo
)
{
    /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    USIMM_UPDATEFILE_CNF_STRU          *pUsimSetFileRsp;
    /* Modified by h00313353 for iteration 9, 2015-2-6, end */
    VOS_UINT8                           ucRecIndex;
    VOS_UINT8                           aucSmsrContent[MN_MSG_EFSMSR_LEN];
    VOS_UINT8                           ucSetUsimRec;
    VOS_BOOL                            bDeleteAll;
    VOS_UINT8                           ucDeleteCount;
    VOS_UINT32                          ulRet;
    VOS_BOOL                            bReportFlag;
    MN_MSG_DELETE_EVT_INFO_STRU         stDeleteInfo;

    pUsimSetFileRsp = (USIMM_UPDATEFILE_CNF_STRU *) pMsg;
    ucRecIndex = pUsimSetFileRsp->ucRecordNum - 1;
    PS_MEM_SET(&stDeleteInfo,0X00,sizeof(stDeleteInfo));

    stDeleteInfo.enDeleteType = pstSmaUsimInfo->enDeleteType;
    stDeleteInfo.enMemStore = MN_MSG_MEM_STORE_SIM;
    stDeleteInfo.ulIndex = ucRecIndex;
    if (MN_MSG_DELETE_SINGLE == pstSmaUsimInfo->enDeleteType)
    {
        if (VOS_OK == (pUsimSetFileRsp->stCmdResult.ulResult))
        {
            stDeleteInfo.bSuccess = VOS_TRUE;
            stDeleteInfo.ulFailCause = MN_ERR_NO_ERROR;
            MN_MSG_ReportDeleteEvent(pstSmaUsimInfo->clientId,
                                     pstSmaUsimInfo->opId,
                                     &stDeleteInfo,
                                     MN_MSG_EVT_DELETE_STARPT);
        }
        else
        {
            MN_MSG_RecoverOrgSmsr(ucRecIndex%MN_MSG_MAX_ORG_REC_NUM,aucSmsrContent);
            MN_MSG_UpdateEachMemSmsrInfo(ucRecIndex,aucSmsrContent,MN_MSG_EFSMSR_LEN);
            stDeleteInfo.bSuccess = VOS_FALSE;
            stDeleteInfo.ulFailCause = MN_ERR_CLASS_SMS_UPDATE_USIM;
            MN_MSG_ReportDeleteEvent(pstSmaUsimInfo->clientId,
                                     pstSmaUsimInfo->opId,
                                     &stDeleteInfo,
                                     MN_MSG_EVT_DELETE_STARPT);
        }
    }
    else
    {
        f_stMsgUsimReturnRec.ucDeleteStaRptSetRec++;
        if (VOS_OK == (pUsimSetFileRsp->stCmdResult.ulResult))
        {
            f_stMsgUsimReturnRec.ucDeleteStaRptSuccRec++;
        }
        else
        {
            /*��ԭԭ���Ķ���״̬��������*/
            MN_MSG_RecoverOrgSmsr(ucRecIndex%MN_MSG_MAX_ORG_REC_NUM,aucSmsrContent);
            MN_MSG_UpdateEachMemSmsrInfo(ucRecIndex,aucSmsrContent,MN_MSG_EFSMSR_LEN);
        }
        ucSetUsimRec = MN_MSG_GetUsimRec(MN_MSG_SET_USIM_DELETE_STARPT);
        if (ucSetUsimRec == f_stMsgUsimReturnRec.ucDeleteStaRptSetRec)
        {
            MN_MSG_SetUsimRec(MN_MSG_SET_USIM_DELETE_STARPT,0);
            bReportFlag = MN_MSG_GetDeleteReportFlag(MN_MSG_SET_USIM_DELETE_STARPT);
            if (ucSetUsimRec == f_stMsgUsimReturnRec.ucDeleteStaRptSuccRec)
            {
                /*ɾ�����δ���ϱ�*/
                if (VOS_FALSE == bReportFlag)
                {
                    /*����״̬����δ��ȫ��ɾ�����,����Ҫɾ��*/
                    ulRet = MN_MSG_DeleteMultiStaRpt(pstSmaUsimInfo->clientId,
                                                     pstSmaUsimInfo->opId,
                                                     MN_MSG_MEM_STORE_SIM,
                                                     &bDeleteAll,
                                                     &ucDeleteCount);
                    if (MN_ERR_NO_ERROR != ulRet)
                    {
                        /*ɾ��ʧ��*/
                        stDeleteInfo.bSuccess = VOS_FALSE;
                        stDeleteInfo.ulFailCause = ulRet;
                        MN_MSG_ReportDeleteEvent(pstSmaUsimInfo->clientId,
                                                 pstSmaUsimInfo->opId,
                                                 &stDeleteInfo,
                                                 MN_MSG_EVT_DELETE_STARPT);
                    }
                    else
                    {
                        if (0 == ucDeleteCount) /*�����Ѿ���ȫɾ��*/
                        {
                           /*����ȫ��ɾ�����,�ϱ�ɾ���ɹ�*/
                            stDeleteInfo.bSuccess = VOS_TRUE;
                            stDeleteInfo.ulFailCause = MN_ERR_NO_ERROR;
                            MN_MSG_ReportDeleteEvent(pstSmaUsimInfo->clientId,
                                                     pstSmaUsimInfo->opId,
                                                     &stDeleteInfo,
                                                     MN_MSG_EVT_DELETE_STARPT);
                        }
                    }
                }
            }
            else /*�ж���ɾ��ʧ��,�ϱ�ɾ������ʧ��*/
            {
                if (VOS_FALSE == bReportFlag)
                {
                    stDeleteInfo.bSuccess = VOS_FALSE;
                    stDeleteInfo.ulFailCause = MN_ERR_CLASS_SMS_UPDATE_USIM;
                    MN_MSG_ReportDeleteEvent(pstSmaUsimInfo->clientId,
                                             pstSmaUsimInfo->opId,
                                             &stDeleteInfo,
                                             MN_MSG_EVT_DELETE_STARPT);
                    MN_MSG_SetDeleteReportFlag(MN_MSG_SET_USIM_DELETE_STARPT,VOS_TRUE);
                    MN_MSG_SetUsimRec(MN_MSG_SET_USIM_DELETE_STARPT_BEGIN,0);
                }
            }
            f_stMsgUsimReturnRec.ucDeleteStaRptSetRec = 0;
            f_stMsgUsimReturnRec.ucDeleteStaRptSuccRec = 0;
        }
    }
}
LOCAL VOS_VOID MSG_SetEfSmssUsimRsp(
    VOS_VOID                            *pMsg
)
{
    /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    USIMM_UPDATEFILE_CNF_STRU           *pUsimSetFileRsp;
    /* Modified by h00313353 for iteration 9, 2015-2-6, end */

    pUsimSetFileRsp = (USIMM_UPDATEFILE_CNF_STRU  *)pMsg;
    if (VOS_OK != (pUsimSetFileRsp->stCmdResult.ulResult))
    {
        MN_WARN_LOG1("MSG_SetEfSmssUsimRsp:Usim Returns Err, ErrCode ",(long)pUsimSetFileRsp->stCmdResult.ulResult);
    }
}

/*****************************************************************************
 �� �� ��  : MN_MSG_InitParm
 ��������  : ����ʱ��Ҫ��ʼ����ǰ����USIM�ļ�¼��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��15��
    ��    ��   : �ܾ� 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MN_MSG_InitParm(VOS_VOID)
{
    /*��ʼ������USIM�ļ�¼��*/
    PS_MEM_SET(&f_stMsgUsimReturnRec,0X00,sizeof(f_stMsgUsimReturnRec));
}

/*****************************************************************************
 �� �� ��  : MN_MSG_GetSmCurrRecFromUsim
 ��������  : ��ȡ��ǰ��USIMȡ���ŵļ�¼��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��15��
    ��    ��   : �ܾ� 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8  MN_MSG_GetSmCurrRecFromUsim(VOS_VOID)
{
    MN_INFO_LOG1("MN_MSG_GetSmCurrRecFromUsim: f_ucMsgCurrSmRec", (VOS_INT32)f_ucMsgCurrSmRec);
    return f_ucMsgCurrSmRec;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_SetSmCurrRecFromUsim
 ��������  : ���õ�ǰ��USIMȡ���ŵļ�¼��
 �������  : ucCurrRec  - ��Ҫ���õļ�¼��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��15��
    ��    ��   : �ܾ� 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  MN_MSG_SetSmCurrRecFromUsim(
    VOS_UINT8                           ucCurrRec
)
{
    f_ucMsgCurrSmRec = ucCurrRec;
}


VOS_UINT32  MN_MSG_SndUsimGetFileReq(
    VOS_UINT16                          usEfId,
    VOS_UINT8                           ucRecNum
)
{
    VOS_UINT32                          ulRet;
    /* Modified by h00313353 for iteration 9, 2015-2-3, begin */
    NAS_USIMM_GETFILE_INFO_STRU         stGetFileInfo;

    PS_MEM_SET(&stGetFileInfo, 0x00, sizeof(stGetFileInfo));
    /* Modified by h00313353 for iteration 9, 2015-2-3, end */

    /*����USIM�ĺ�����ȡָ���ļ���ָ����¼�ŵ�����*/
    /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
    TAF_COMM_BUILD_USIM_GET_FILE_INFO(&stGetFileInfo, USIMM_GUTL_APP, usEfId, ucRecNum);
    /* Modified by h00313353 for iteration 9, 2015-2-4, end */

    ulRet = NAS_USIMMAPI_GetFileReq(WUEPS_PID_TAF, 0, &stGetFileInfo);


    if (USIMM_API_SUCCESS != ulRet)
    {
        return ulRet;
    }

    /*����USIM�Ľӿڷ��سɹ�,������Ӧ��״̬*/
    switch (usEfId)
    {
        /* Modified by h00313353 for iteration 9, 2015-3-9, begin */
        case USIMM_USIM_EFSMSS_ID:
        case USIMM_TELE_EFSMSS_ID:
        /* Modified by h00313353 for iteration 9, 2015-3-9, end */
            MN_MSG_UpdateUsimStateInfo(MN_MSG_USIM_POWER_WAIT_EFSMSS);
            break;
        /* Modified by h00313353 for iteration 9, 2015-3-9, begin */
        case USIMM_USIM_EFSMSP_ID:
        case USIMM_TELE_EFSMSP_ID:
        /* Modified by h00313353 for iteration 9, 2015-3-9, end */
            MN_MSG_UpdateUsimStateInfo(MN_MSG_USIM_POWER_WAIT_EFSMSP);
            break;
        /* Modified by h00313353 for iteration 9, 2015-3-9, begin */
        case USIMM_USIM_EFSMS_ID:
        case USIMM_TELE_EFSMS_ID:
        /* Modified by h00313353 for iteration 9, 2015-3-9, end */
            MN_MSG_UpdateUsimStateInfo(MN_MSG_USIM_POWER_WAIT_EFSMS);
            break;
        /* Modified by h00313353 for iteration 9, 2015-3-9, begin */
        case USIMM_USIM_EFSMSR_ID:
        case USIMM_TELE_EFSMSR_ID:
        /* Modified by h00313353 for iteration 9, 2015-3-9, end */
            MN_MSG_UpdateUsimStateInfo(MN_MSG_USIM_POWER_WAIT_EFSMSR);
            break;
        default:
            MN_WARN_LOG1("MN_MSG_SndUsimGetFileReq:Invalid EFID ",usEfId);
            return USIMM_API_WRONG_PARA;
    }

    /*���سɹ�,������ʱ��*/
    MN_MSG_StartTimer(MN_MSG_TID_WAIT_GET_EF_RSP,0);

    return ulRet;
}
VOS_UINT32  MN_MSG_SndUsimGetMaxRecReq(
    VOS_UINT16                          usEfId
)
{
    VOS_UINT32                          ulRet;

    /*����USIM�ĺ�����ȡ�ļ�EFSMS�ļ�¼��*/
    ulRet = NAS_USIMMAPI_MaxEFRecordNumReq(WUEPS_PID_TAF, USIMM_GUTL_APP, usEfId);

    /*���سɹ�,������ʱ��������״̬*/
    if (USIMM_API_SUCCESS == ulRet)
    {
        MN_MSG_UpdateUsimStateInfo(MN_MSG_USIM_POWER_WAIT_EFSMSREC);
        MN_MSG_StartTimer(MN_MSG_TID_WAIT_GET_EF_RSP,0);
    }
    return ulRet;
}


VOS_VOID  MN_MSG_RcvUsimGetMaxRecRsp(
    VOS_VOID                            *pMsg
)
{
    /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    USIMM_QUERYFILE_CNF_STRU           *pUsimGetMaxNumMsg;
    /* Modified by h00313353 for iteration 9, 2015-2-6, end */
    MN_MSG_USIM_POWER_STATE_ENUM_U8     enPowerState;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulTotalRec = 0;
    /* Added by h00313353 for iteration 9, 2015-2-10, begin */
    VOS_UINT32                          ulFileId;
    /* Added by h00313353 for iteration 9, 2015-2-10, end */

    pUsimGetMaxNumMsg = (USIMM_QUERYFILE_CNF_STRU*) pMsg;
    /* Added by h00313353 for iteration 9, 2015-2-10, begin */
    ulFileId = 0;
    if (VOS_OK != USIMM_ChangePathToDefFileID(USIMM_GUTL_APP, pUsimGetMaxNumMsg->stFilePath.ulPathLen, pUsimGetMaxNumMsg->stFilePath.acPath, &ulFileId))
    {
        return;
    }
    /* Added by h00313353 for iteration 9, 2015-2-10, end */

    MN_MSG_GetUsimPowerState(&enPowerState);
    if (MN_MSG_USIM_POWER_WAIT_EFSMSREC == enPowerState)
    {
        MN_MSG_StopTimer(MN_MSG_TID_WAIT_GET_EF_RSP);
        if ((VOS_OK == (pUsimGetMaxNumMsg->stCmdResult.ulResult))
         /* Modified by h00313353 for iteration 9, 2015-2-11, begin */
         && ((USIMM_USIM_EFSMS_ID == ulFileId)
         || (USIMM_TELE_EFSMS_ID == ulFileId))) /* EF_SMS_SMS_ID */
         /* Modified by h00313353 for iteration 9, 2015-2-11, end */
        {
#if ( VOS_WIN32 == VOS_OS_VER )
            if (0 != g_ucSetEfSmsCapacity)
            {
                ulTotalRec = g_ucSetEfSmsCapacity;
            }
            else
            {
                ulTotalRec = pUsimGetMaxNumMsg->ucRecordNum;
            }
#else
            ulTotalRec = pUsimGetMaxNumMsg->ucRecordNum;
#endif
            if (ulTotalRec > 0)
            {
                MN_MSG_UpdateSmsInfo(VOS_TRUE, (VOS_UINT8)ulTotalRec);
            }
        }
        else
        {
            MN_WARN_LOG("MN_MSG_RcvSmsGetRec:the Rsp of Usim is Failed");
        }

        if (ulTotalRec > 0)
        {
            /*����һ��һ���Ķ�ȡ,�ӵ�һ����ʼ����,��ȡ�ɹ���ȵ�USIM�Ļظ�*/
            f_ucMsgCurrSmRec = 1;
            /* Modified by h00313353 for iteration 9, 2015-3-9, begin */
            ulRet = MN_MSG_SndUsimGetFileReq((VOS_UINT16)ulFileId,f_ucMsgCurrSmRec);
            /* Modified by h00313353 for iteration 9, 2015-3-9, end */
            if (USIMM_API_SUCCESS == ulRet)
            {
                return;
            }
        }
        /* Modified by h00313353 for iteration 9, 2015-3-9, begin */
        if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
        {
            MN_MSG_GetUsimParmReq(USIMM_USIM_EFSMSR_ID);
        }
        else
        {
            MN_MSG_GetUsimParmReq(USIMM_TELE_EFSMSR_ID);
        }
        /* Modified by h00313353 for iteration 9, 2015-3-9, end */
    }
    else
    {
        MN_WARN_LOG("MN_MSG_RcvSmsGetRec:Invalid State");
    }
}


VOS_VOID  MN_MSG_RcvUsimGetFileRsp(
    VOS_VOID                           *pMsg
)
{
    USIMM_READFILE_CNF_STRU            *pstUsimGetFileRsp;
    VOS_UINT32                          ulEfId;

    pstUsimGetFileRsp = (USIMM_READFILE_CNF_STRU *)pMsg;
    /* Added by h00313353 for iteration 9, 2015-2-5, begin */
    if (VOS_OK != USIMM_ChangePathToDefFileID(USIMM_GUTL_APP, pstUsimGetFileRsp->stFilePath.ulPathLen, pstUsimGetFileRsp->stFilePath.acPath, &ulEfId))
    {
        return;
    }
    /* Added by h00313353 for iteration 9, 2015-2-5, end */

    switch (ulEfId)
    {
        /* Modified by h00313353 for iteration 9, 2015-2-11, begin */
        case USIMM_USIM_EFSMSS_ID: /* EF_SMS_SMSS_ID */
        case USIMM_TELE_EFSMSS_ID:
            MSG_ProcEfSmssGetFileRsp(pMsg);
            break;
        case USIMM_USIM_EFSMSP_ID: /* EF_SMS_SMSP_ID */
        case USIMM_TELE_EFSMSP_ID:
            MSG_ProcEfSmspGetFileRsp(pMsg);
            break;
        case USIMM_USIM_EFSMS_ID: /* EF_SMS_SMS_ID */
        case USIMM_TELE_EFSMS_ID:
            MSG_ProcEfSmsGetFileRsp(pMsg);
            break;
        case USIMM_USIM_EFSMSR_ID: /* EF_SMS_SMSR_ID */
        case USIMM_TELE_EFSMSR_ID:
            MSG_ProcEfSmsrGetFileRsp(pMsg);
            break;
#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

        case USIMM_USIM_EFCBMI_ID: /* TAF_CBA_EF_CBMI_ID */
		case USIMM_GSM_EFCBMI_ID:
        case USIMM_USIM_EFCBMIR_ID: /* TAF_CBA_EF_CBMIR_ID */
		case USIMM_GSM_EFCBMIR_ID:
        case USIMM_USIM_EFCBMID_ID: /* TAF_CBA_EF_CBMID_ID */
		case USIMM_GSM_EFCBMID_ID:
            TAF_CBA_MsgProc((struct MsgCB*)pMsg);
            break;

#endif
        /* Modified by h00313353 for iteration 9, 2015-2-11, end */
        default:
            MN_INFO_LOG("MN_MSG_RcvUsimGetFileRsp:Rcv Invalid EFID");
            break;

    }
}
VOS_UINT32 MN_MSG_SndUsimSetFileReq(
    VOS_UINT16                          usEfId,
    VOS_UINT8                           *pucEf,
    VOS_UINT8                           ucEfLen,
    VOS_UINT8                           ucRecNum
)
{
    /* Modified by h00313353 for iteration 9, 2015-2-3, begin */
    NAS_USIMM_UPDATEFILE_INFO_STRU      stSetFileInfo;

    PS_MEM_SET(&stSetFileInfo, 0x00, sizeof(stSetFileInfo));
    /* Modified by h00313353 for iteration 9, 2015-2-3, end */

    if (VOS_FALSE == MN_MSG_IsUsimFileExist(usEfId))
    {
        MN_WARN_LOG("MN_MSG_SndUsimSetFileReq: File is inavailable.");
        return USIMM_API_FAILED;
    }

    if (MN_MSG_STUB_CFG_VALUE_SET == g_ucSetEfSmsFail)
    {
        MN_MSG_Usim_Stub(WUEPS_PID_TAF, usEfId, VOS_ERR, ucRecNum);
        return USIMM_API_SUCCESS;
    }
    else
    {

        #ifdef __PS_WIN32_RECUR__
        return USIMM_API_SUCCESS;
        #else
        TAF_COMM_BUILD_USIM_SET_FILE_INFO(&stSetFileInfo,
                                        /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
                                        USIMM_GUTL_APP,
                                        /* Modified by h00313353 for iteration 9, 2015-2-4, end */
                                        usEfId,
                                        ucRecNum,
                                        ucEfLen,
                                        pucEf);

        return NAS_USIMMAPI_SetFileReq(WUEPS_PID_TAF, 0, &stSetFileInfo);
        #endif
    }
}


VOS_UINT32 MN_MSG_EnvelopRspRpAckWithTpdu(
    /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    SI_STK_ENVELOPEDWON_CNF_STRU       *pstEnvelope
    /* Modified by h00313353 for iteration 9, 2015-2-6, end */
)
{
    MN_MSG_RP_ACK_STRU                  stRpAck;
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo;
    MN_MSG_DELIVER_RPT_ACK_STRU         *pstDeliverRptAck;
    MN_MSG_TP_PID_TYPE_ENUM_U8          enPid;
    MN_MSG_DCS_CODE_STRU                stDcs;
    MN_MSG_RAW_TS_DATA_STRU             *pstRawData;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucSendLen;
    VOS_UINT8                           *pucSendData;
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32  enMsgSignallingType;

    PS_MEM_SET(&stRpAck, 0, sizeof(MN_MSG_RP_ACK_STRU));
    PS_MEM_SET(&stDcs, 0, sizeof(MN_MSG_DCS_CODE_STRU));

    /*1. RP-ACK��Ϣ��TPDU����ԭʼ���ݽṹ�ڴ�����*/
    pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_MSG_TS_DATA_INFO_STRU));
    if (VOS_NULL_PTR == pstTsDataInfo)
    {
        MN_WARN_LOG("MN_MSG_EnvelopRspRpAckWithTpdu: Fail to alloc memory.");
        return MN_ERR_NOMEM;
    }

    /*2. RP-ACK��Ϣ��TPDU����ԭʼ���ݽṹ��д*/
    PS_MEM_SET(pstTsDataInfo, 0x00, sizeof(MN_MSG_TS_DATA_INFO_STRU));
    pstTsDataInfo->enTpduType = MN_MSG_TPDU_DELIVER_RPT_ACK;
    pstDeliverRptAck = &pstTsDataInfo->u.stDeliverRptAck;
    pstDeliverRptAck->ucParaInd = MN_MSG_TP_PID_MASK | MN_MSG_TP_DCS_MASK | MN_MSG_TP_UDL_MASK;
    MN_MSG_GetMtTpPidAndDcs(&enPid, &stDcs);
    pstDeliverRptAck->enPid = enPid;
    PS_MEM_CPY(&pstDeliverRptAck->stDcs, &stDcs, sizeof(stDcs));
    pstDeliverRptAck->bUserDataHeaderInd = VOS_FALSE;
    /* Modified by h00313353 for iteration 9, 2015-2-13, begin */
    pstDeliverRptAck->stUserData.ulLen = pstEnvelope->stCnfData.ulRspDataLen;
    /* Modified by h00313353 for iteration 9, 2015-2-13, end */
    PS_MEM_CPY(pstDeliverRptAck->stUserData.aucOrgData,
               /* Modified by h00313353 for iteration 9, 2015-2-13, begin */
               pstEnvelope->stCnfData.aucRspData,
               pstEnvelope->stCnfData.ulRspDataLen);
               /* Modified by h00313353 for iteration 9, 2015-2-13, end */

    /*3. RP-ACK��Ϣ��TPDU�����ڴ�����*/
    pstRawData = (MN_MSG_RAW_TS_DATA_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_MSG_RAW_TS_DATA_STRU));
    if (VOS_NULL_PTR == pstRawData)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstTsDataInfo);
        MN_WARN_LOG("MN_MSG_EnvelopRspRpAckWithTpdu: Fail to alloc memory.");
        return MN_ERR_NOMEM;
    }

    /*4. RP-ACK��Ϣ��TPDU���룬���뺯�����ú�TPDUԭʼ���ݽṹ�Ѿ�����Ҫ���Դ˴��ͷŸ��ڴ�*/
    ulRet = MN_MSG_Encode(pstTsDataInfo, pstRawData);
    PS_MEM_FREE(WUEPS_PID_TAF, pstTsDataInfo);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstRawData);
        MN_NORM_LOG("MN_MSG_EnvelopRspRpAckWithTpdu: Fail to MN_MSG_Encode.");
        return MN_ERR_CLASS_SMS_INVALID_TPDU;
    }

    /*5. RP-ACK��Ϣ��TPDU���볤���쳣�˳�*/
    if (pstRawData->ulLen > MN_MSG_MAX_TPDU_LEN)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstRawData);
        MN_NORM_LOG("MN_MSG_EnvelopRspRpAckWithTpdu: TPDU length is overflow.");
        return MN_ERR_CLASS_SMS_INVALID_TPDU;
    }

    /*6. RP-ACK��Ϣ��RP-ACKԭʼ������д��TPDU�����Ϣ��д��ɺ�TPDU�������ݽṹ�Ѿ�����Ҫ���Դ˴��ͷŸ��ڴ�*/
    PS_MEM_SET(&stRpAck,0x00,sizeof(stRpAck));
    stRpAck.ucRpUserDataLen = (VOS_UINT8)pstRawData->ulLen;
    PS_MEM_CPY(stRpAck.aucRpUserData, pstRawData->aucData, pstRawData->ulLen);
    PS_MEM_FREE(WUEPS_PID_TAF, pstRawData);
    stRpAck.ucRpMsgType = MN_MSG_RP_MTI_UP_RP_ACK;
    stRpAck.bRpUserDataExist = VOS_TRUE;
    stRpAck.ucRpUserDataIei = MN_MSG_RP_USER_DATA_IEI;

    /*7. RP-ACK��Ϣ��RP-ACK���ݱ����ڴ����뼰����*/
    pucSendData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_TAF, MN_MSG_MAX_LEN);
    if (VOS_NULL_PTR == pucSendData)
    {
        MN_WARN_LOG("MN_MSG_EnvelopRspRpAckWithTpdu: Fail to alloc memory.");
        return MN_ERR_NOMEM;
    }
    MN_MSG_EncodeRpAck(&stRpAck, pucSendData,&ucSendLen);

    enMsgSignallingType = MN_MSG_GetMtRouteStackType();
    
    /*8. RP-ACK��Ϣ��RP-ACK��Ϣ����*/
    ulRet = MN_MSG_SendSmsRpReportReq(pucSendData,ucSendLen, enMsgSignallingType);    
    if (VOS_OK != ulRet)
    {
        MN_WARN_LOG("MN_MSG_EnvelopRspRpAckWithTpdu: Send Msg Failed");
    }

    PS_MEM_FREE(WUEPS_PID_TAF, pucSendData);
    return MN_ERR_NO_ERROR;
}


VOS_UINT32 MN_MSG_EnvelopRspRpErrorWithTpdu(
    /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    SI_STK_ENVELOPEDWON_CNF_STRU       *pstEnvelope
    /* Modified by h00313353 for iteration 9, 2015-2-6, end */
)
{
    MN_MSG_RP_ERR_STRU                  stRpErr;
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo;
    MN_MSG_DELIVER_RPT_ERR_STRU         *pstDeliverRptErr;
    MN_MSG_TP_PID_TYPE_ENUM_U8          enPid;
    MN_MSG_DCS_CODE_STRU                stDcs;
    MN_MSG_RAW_TS_DATA_STRU             *pstRawData;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucSendLen;
    VOS_UINT8                           *pucSendData;
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType;

    PS_MEM_SET(&stRpErr, 0, sizeof(MN_MSG_RP_ERR_STRU));
    PS_MEM_SET(&stDcs, 0, sizeof(MN_MSG_DCS_CODE_STRU));

    /*1. RP-ERROR��Ϣ��TPDU����ԭʼ���ݽṹ�ڴ�����*/
    pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_MSG_TS_DATA_INFO_STRU));
    if (VOS_NULL_PTR == pstTsDataInfo)
    {
        MN_WARN_LOG("MN_MSG_EnvelopRspRpErrorWithTpdu: Fail to alloc memory.");
        return MN_ERR_NOMEM;
    }

    /*2. RP-ERROR��Ϣ��TPDU����ԭʼ���ݽṹ��д*/
    PS_MEM_SET(pstTsDataInfo, 0x00, sizeof(MN_MSG_TS_DATA_INFO_STRU));
    pstTsDataInfo->enTpduType       = MN_MSG_TPDU_DELIVER_RPT_ERR;
    pstDeliverRptErr                = &pstTsDataInfo->u.stDeliverRptErr;
    pstDeliverRptErr->enFailCause   = MN_MSG_TP_CAUSE_SIM_DATA_DOWNLOAD_ERR;
    pstDeliverRptErr->ucParaInd     = MN_MSG_TP_PID_MASK | MN_MSG_TP_DCS_MASK | MN_MSG_TP_UDL_MASK;
    MN_MSG_GetMtTpPidAndDcs(&enPid, &stDcs);
    pstDeliverRptErr->enPid = enPid;
    PS_MEM_CPY(&pstDeliverRptErr->stDcs, &stDcs, sizeof(stDcs));
    pstDeliverRptErr->bUserDataHeaderInd    = VOS_FALSE;
    /* Modified by h00313353 for iteration 9, 2015-2-13, begin */
    pstDeliverRptErr->stUserData.ulLen      = pstEnvelope->stCnfData.ulRspDataLen;
    PS_MEM_CPY(pstDeliverRptErr->stUserData.aucOrgData,
               pstEnvelope->stCnfData.aucRspData,
               pstEnvelope->stCnfData.ulRspDataLen);
    /* Modified by h00313353 for iteration 9, 2015-2-13, end */

    /*3. RP-ERROR��Ϣ��TPDU�����ڴ�����*/
    pstRawData = (MN_MSG_RAW_TS_DATA_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_MSG_RAW_TS_DATA_STRU));
    if (VOS_NULL_PTR == pstRawData)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstTsDataInfo);
        MN_WARN_LOG("MN_MSG_EnvelopRspRpErrorWithTpdu: Fail to alloc memory.");
        return MN_ERR_NOMEM;
    }

    /*4. RP-ERROR��Ϣ��TPDU���룬���뺯�����ú�TPDUԭʼ���ݽṹ�Ѿ�����Ҫ���Դ˴��ͷŸ��ڴ�*/
    ulRet = MN_MSG_Encode(pstTsDataInfo, pstRawData);
    PS_MEM_FREE(WUEPS_PID_TAF, pstTsDataInfo);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstRawData);
        MN_NORM_LOG("MN_MSG_EnvelopRspRpErrorWithTpdu: Fail to MN_MSG_Encode.");
        return MN_ERR_CLASS_SMS_INVALID_TPDU;
    }

    /*5. RP-ERROR��Ϣ��TPDU���볤���쳣�˳�*/
    if (pstRawData->ulLen > MN_MSG_MAX_TPDU_LEN)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstRawData);
        MN_NORM_LOG("MN_MSG_EnvelopRspRpErrorWithTpdu: TPDU length is overflow.");
        return MN_ERR_CLASS_SMS_INVALID_TPDU;
    }

    /*6. RP-ERROR��Ϣ��RP-ERRORԭʼ������д��TPDU�����Ϣ��д��ɺ�TPDU�������ݽṹ�Ѿ�����Ҫ���Դ˴��ͷŸ��ڴ�*/
    PS_MEM_SET(&stRpErr,0x00,sizeof(stRpErr));
    stRpErr.ucRpUserDataLen  = (VOS_UINT8)pstRawData->ulLen;
    PS_MEM_CPY(stRpErr.aucRpUserData, pstRawData->aucData, pstRawData->ulLen);
    PS_MEM_FREE(WUEPS_PID_TAF, pstRawData);
    stRpErr.ucRpMsgType      = MN_MSG_RP_MTI_UP_RP_ERR;
    stRpErr.bRpUserDataExist = VOS_TRUE;
    stRpErr.ucRpUserDataIei  = MN_MSG_RP_USER_DATA_IEI;
    stRpErr.ucRpCauseLen = 1;
    stRpErr.stRpCause.bDiagnosticsExist = VOS_FALSE;
    stRpErr.stRpCause.enRpCause = MN_MSG_RP_CAUSE_PROTOCOL_ERR_UNSPECIFIED;

    /*7. RP-ERROR��Ϣ��RP-ACK���ݱ����ڴ����뼰����*/
    pucSendData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_TAF, MN_MSG_MAX_LEN);
    if (VOS_NULL_PTR == pucSendData)
    {
        MN_WARN_LOG("MN_MSG_EnvelopRspRpErrorWithTpdu: Fail to alloc memory.");
        return MN_ERR_NOMEM;
    }
    MN_MSG_EncodeRpErr(&stRpErr, pucSendData,&ucSendLen);

    NAS_EventReport(WUEPS_PID_TAF, 
                    NAS_OM_EVENT_SMS_MT_FAIL, 
                    &(stRpErr.stRpCause.enRpCause), 
                    sizeof(MN_MSG_RP_CAUSE_ENUM_U8));

    enMsgSignallingType = MN_MSG_GetMtRouteStackType();
    
    /*8. RP-ERROR��Ϣ��RP-ERROR��Ϣ����*/
    ulRet = MN_MSG_SendSmsRpReportReq(pucSendData,ucSendLen, enMsgSignallingType);

    if (VOS_OK != ulRet)
    {
        MN_WARN_LOG("MN_MSG_EnvelopRspRpErrorWithTpdu: Send Msg Failed");
    }

    PS_MEM_FREE(WUEPS_PID_TAF, pucSendData);
    return MN_ERR_NO_ERROR;
}


VOS_VOID  MN_MSG_RcvUsimEnvelopRsp(
    /* Modified by h00313353 for iteration 9, 2015-2-13, begin */
    SI_STK_ENVELOPEDWON_CNF_STRU       *pstEnvelope
    /* Modified by h00313353 for iteration 9, 2015-2-13, end */
)
{
    VOS_UINT32                          ulRet;

    /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    if (VOS_OK == (pstEnvelope->stCmdResult.ulResult))
    /* Modified by h00313353 for iteration 9, 2015-2-6, end */
    {
        /*(U)SIM�����ص�TP-UDLΪ0ʱ���ظ������RP-ACK��Ϣ����TPDU*/
        /* Modified by h00313353 for iteration 9, 2015-2-13, begin */
        if (0 == pstEnvelope->stCnfData.ulRspDataLen)
        /* Modified by h00313353 for iteration 9, 2015-2-13, end */
        {
            MN_MSG_Internal_SendRpt(VOS_TRUE, 0, 0);
            return;
        }

        /*(U)SIM�����ص�TP-UDL��Ϊ0ʱ���ظ������RP-ACK��Ϣ��TPDU*/
        ulRet = MN_MSG_EnvelopRspRpAckWithTpdu(pstEnvelope);
    }
    else
    {
        /*(U)SIM�����صĴ���ԭ��ֵΪ��æʱ���ظ������RP-ERROR��Ϣ����TPDU��TP-FCSΪ0xd4*/
        /* Modified by h00313353 for iteration 9, 2015-2-13, begin */
        if (USIMM_SW_CARD_BUSY == (pstEnvelope->stCmdResult.ulErrorNO))
        /* Modified by h00313353 for iteration 9, 2015-2-13, end */
        {
            MN_MSG_Internal_SendRpt(VOS_FALSE,
                                    MN_MSG_RP_CAUSE_PROTOCOL_ERR_UNSPECIFIED,
                                    MN_MSG_TP_CAUSE_SAT_BUSY);
            return;
        }

        /*(U)SIM�����ص�TP-UDLΪ0ʱ���ظ������RP-ERROR��Ϣ����TPDU��TP-FCSΪ0xd5*/
        /* Modified by h00313353 for iteration 9, 2015-2-13, begin */
        if (0 == pstEnvelope->stCnfData.ulRspDataLen)
        /* Modified by h00313353 for iteration 9, 2015-2-13, end */
        {
            MN_MSG_Internal_SendRpt(VOS_FALSE,
                                    MN_MSG_RP_CAUSE_PROTOCOL_ERR_UNSPECIFIED,
                                    MN_MSG_TP_CAUSE_SIM_DATA_DOWNLOAD_ERR);
            return;
        }

        /*(U)SIM�����ص�TP-UDL��Ϊ0ʱ���ظ������RP-ERROR��Ϣ��TPDU��TP-FCSΪ0xd5*/
        ulRet = MN_MSG_EnvelopRspRpErrorWithTpdu(pstEnvelope);

    }

    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_MSG_Internal_SendRpt(VOS_FALSE,
                                MN_MSG_RP_CAUSE_PROTOCOL_ERR_UNSPECIFIED,
                                MN_MSG_TP_CAUSE_ERR_IN_MS);
    }

}
VOS_VOID  MN_MSG_RcvUsimRefreshInd(
    VOS_VOID                            *pMsg
)
{
    USIMM_STKREFRESH_IND_STRU           *pstRefreshInd;

    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    VOS_UINT32                          ulRequireRefresh;
    /* Added by h00313353 for iteration 9, 2015-3-9, begin */
    VOS_UINT32                          aulFileId[4];

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        aulFileId[0]    = USIMM_USIM_EFSMSS_ID;
        aulFileId[1]    = USIMM_USIM_EFSMS_ID;
        aulFileId[2]    = USIMM_USIM_EFSMSP_ID;
        aulFileId[3]    = USIMM_USIM_EFSMSR_ID;
    }
    else
    {
        aulFileId[0]    = USIMM_TELE_EFSMSS_ID;
        aulFileId[1]    = USIMM_TELE_EFSMS_ID;
        aulFileId[2]    = USIMM_TELE_EFSMSP_ID;
        aulFileId[3]    = USIMM_TELE_EFSMSR_ID;
    }
    /* Added by h00313353 for iteration 9, 2015-3-9, end */

    pstRefreshInd = (USIMM_STKREFRESH_IND_STRU *)pMsg;

    if ((USIMM_REFRESH_FILE_LIST != pstRefreshInd->enRefreshType)
     && (USIMM_REFRESH_3G_SESSION_RESET != pstRefreshInd->enRefreshType)
     && (USIMM_REFRESH_ALL_FILE != pstRefreshInd->enRefreshType))
    {
        return;
    }

    /* 3G SESSION RESET�������ļ��������͵�REFRESH�¼�Ҫ���ض�����USIM�ļ� */
    if ((USIMM_REFRESH_3G_SESSION_RESET == pstRefreshInd->enRefreshType )
     || (USIMM_REFRESH_ALL_FILE == pstRefreshInd->enRefreshType))
    {

        MN_MSG_SetSmsFileRefreshFlag(USIMM_USIM_EFSMSS_ID, VOS_TRUE);
        MN_MSG_SetSmsFileRefreshFlag(USIMM_USIM_EFSMS_ID, VOS_TRUE);
        MN_MSG_SetSmsFileRefreshFlag(USIMM_USIM_EFSMSP_ID, VOS_TRUE);
        MN_MSG_SetSmsFileRefreshFlag(USIMM_USIM_EFSMSR_ID, VOS_TRUE);

        MN_MSG_CfgDataInit(MNPH_USIM_STATUS_AVILABLE);

        return;
    }

    /* ָ���ļ��б����͵�REFRESHҪ���ض��б��д��ڵ�USIM�ļ� */
    ulRequireRefresh = TAF_GetSpecificFileListRefreshFileInfo((VOS_UINT16)aulFileId[0], pstRefreshInd, &enAppType);
    if (VOS_TRUE == ulRequireRefresh)
    {
        MN_MSG_SetSmsFileRefreshFlag(USIMM_USIM_EFSMSS_ID, VOS_TRUE);
    }

    ulRequireRefresh = TAF_GetSpecificFileListRefreshFileInfo((VOS_UINT16)aulFileId[1], pstRefreshInd, &enAppType);
    if (VOS_TRUE == ulRequireRefresh)
    {
        MN_MSG_SetSmsFileRefreshFlag(USIMM_USIM_EFSMS_ID, VOS_TRUE);
    }

    ulRequireRefresh = TAF_GetSpecificFileListRefreshFileInfo((VOS_UINT16)aulFileId[2], pstRefreshInd, &enAppType);
    if (VOS_TRUE == ulRequireRefresh)
    {
        MN_MSG_SetSmsFileRefreshFlag(USIMM_USIM_EFSMSP_ID, VOS_TRUE);
    }

    ulRequireRefresh = TAF_GetSpecificFileListRefreshFileInfo((VOS_UINT16)aulFileId[3], pstRefreshInd, &enAppType);
    if (VOS_TRUE == ulRequireRefresh)
    {
        MN_MSG_SetSmsFileRefreshFlag(USIMM_USIM_EFSMSR_ID, VOS_TRUE);
    }

    MN_MSG_CfgDataInit(MNPH_USIM_STATUS_AVILABLE);

    return;
}
VOS_VOID  MN_MSG_RcvUsimSetFileRsp(
    VOS_VOID                            *pMsg
)
{
    MN_MSG_USIM_INFO_STRU               SmaUsimInfo;
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulRet;
    /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    USIMM_UPDATEFILE_CNF_STRU          *pUsimSetFileRsp;
    /* Modified by h00313353 for iteration 9, 2015-2-6, end */
    VOS_UINT8                           ucRecIndex;
    VOS_UINT32                          ulEfId;

    pUsimSetFileRsp = (USIMM_UPDATEFILE_CNF_STRU *) pMsg;

    /* Added by h00313353 for iteration 9, 2015-2-5, begin */
    if (VOS_OK != USIMM_ChangePathToDefFileID(USIMM_GUTL_APP, pUsimSetFileRsp->stFilePath.ulPathLen, pUsimSetFileRsp->stFilePath.acPath, &ulEfId))
    {
        return;
    }
    /* Added by h00313353 for iteration 9, 2015-2-5, end */

    PS_MEM_SET(&SmaUsimInfo, 0, sizeof(SmaUsimInfo));

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    ulRet = TAF_CBA_ProcUsimSetFileRsp(pUsimSetFileRsp);
    if ( VOS_OK == ulRet )
    {
        MN_INFO_LOG1("MN_MSG_RcvUsimSetFileRsp,CB Files ", (VOS_UINT16)ulEfId);
        return;
    }

#endif

    ucRecIndex = pUsimSetFileRsp->ucRecordNum;
    MN_NORM_LOG1("MN_MSG_RcvUsimSetFileRsp: pUsimSetFileRsp->usEfId ", (VOS_UINT16)ulEfId);
    MN_NORM_LOG1("MN_MSG_RcvUsimSetFileRsp: pUsimSetFileRsp->ulResult ", (long)pUsimSetFileRsp->stCmdResult.ulResult);
    MN_NORM_LOG1("MN_MSG_RcvUsimSetFileRsp: pUsimSetFileRsp->ucRecordNum ", pUsimSetFileRsp->ucRecordNum);
    MSG_PrintUsimReturnRecStru(&f_stMsgUsimReturnRec);
    if (MN_MSG_USIM_DEF_REC != pUsimSetFileRsp->ucRecordNum)
    {
        ucRecIndex = pUsimSetFileRsp->ucRecordNum - 1;
    }

    ulRet = MN_MSG_FindNodeByUsimResult(ucRecIndex,
                                        (VOS_UINT16)ulEfId,
                                        &SmaUsimInfo,
                                        &ulIndex);

    if (VOS_ERR == ulRet)
    {
        MN_WARN_LOG1("MN_MSG_RcvUsimSetFileRsp,Not matched USIM Node, EFID ", (VOS_UINT16)ulEfId);
        return;
    }
    MN_NORM_LOG1("MN_MSG_RcvUsimSetFileRsp: SmaUsimInfo.clientId ", SmaUsimInfo.clientId);
    MN_NORM_LOG1("MN_MSG_RcvUsimSetFileRsp: SmaUsimInfo.opId ", SmaUsimInfo.opId);
    MN_NORM_LOG1("MN_MSG_RcvUsimSetFileRsp: SmaUsimInfo.ucRecIndex ", SmaUsimInfo.ucRecIndex);
    MN_NORM_LOG1("MN_MSG_RcvUsimSetFileRsp: SmaUsimInfo.usEfId ", (VOS_UINT16)ulEfId);
    MN_NORM_LOG1("MN_MSG_RcvUsimSetFileRsp: SmaUsimInfo.enDeleteType ", SmaUsimInfo.enDeleteType);
    MN_NORM_LOG1("MN_MSG_RcvUsimSetFileRsp: SmaUsimInfo.enSmaUsimAction ", SmaUsimInfo.enSmaUsimAction);
#if ( VOS_WIN32 == VOS_OS_VER )
    if (0 != g_ucSetEfSmsNoResponse)
    {
        if ((MN_MSG_USIM_WRITE == SmaUsimInfo.enSmaUsimAction)
        || (MN_MSG_USIM_RCVNEWMSG == SmaUsimInfo.enSmaUsimAction))
       {
           MN_WARN_LOG1("MN_MSG_RcvUsimSetFileRsp,Not matched USIM Node, EFID ",(VOS_UINT16)ulEfId);
           MN_MSG_DestroyUsimNode(ulIndex);
           return;
       }
    }
#endif

    switch (SmaUsimInfo.enSmaUsimAction)
    {
        case MN_MSG_USIM_READ:
            MSG_ReadSaveUsimMsgRsp(pMsg,SmaUsimInfo.clientId);
            break;
        case MN_MSG_USIM_LIST:
            MSG_ListSaveUsimMsgRsp(pMsg,SmaUsimInfo.clientId);
            break;
        case MN_MSG_USIM_WRITE:
            MSG_WriteSaveUsimMsgRsp(pMsg,&SmaUsimInfo);
            break;
        case MN_MSG_USIM_DELETE:
            MSG_DeleteSaveUsimMsgRsp(pMsg,&SmaUsimInfo);
            break;
        case MN_MSG_USIM_MODIFYSTATUS:
            MSG_ModifySaveUsimMsgRsp(pMsg,&SmaUsimInfo);
            break;
        case MN_MSG_USIM_RCVNEWMSG:
        case MN_MSG_USIM_RCVSTARPT:
            MSG_RcvSaveUsimMsgRsp(pMsg, &SmaUsimInfo);
            break;
        case MN_MSG_USIM_SEND:
            MSG_SendSaveUsimMsgRsp(pMsg,SmaUsimInfo.clientId);
            break;
        case MN_MSG_USIM_RCVMORPT:
            MSG_RcvMoRptSaveUsimMsgRsp(pMsg,SmaUsimInfo.clientId);
            break;
        case MN_MSG_USIM_WRITE_EFSMSP:
            MSG_WriteEfSmspUsimRsp(pMsg,&SmaUsimInfo);
            break;
        case MN_MSG_USIM_DELETE_EFSMSP:
            MSG_DeleteEfSmspUsimRsp(pMsg,&SmaUsimInfo);
            break;
        case MN_MSG_USIM_DELETE_STARPT:
            MSG_DeleteStaRptSaveUsimMsgRsp(pMsg,&SmaUsimInfo);
            break;
        case MN_MSG_USIM_SET_EFSMSS:
            MSG_SetEfSmssUsimRsp(pMsg);
            break;
        default:
            MN_WARN_LOG1("MN_MSG_RcvUsimSetFileRsp,Invalid Action, Action ",SmaUsimInfo.enSmaUsimAction);
            break;

    }

    MN_MSG_DestroyUsimNode(ulIndex);
}


VOS_VOID MN_MSG_RcvUsimMoControlRsp(
    /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    SI_STK_ENVELOPEDWON_CNF_STRU       *pstEnvelope
    /* Modified by h00313353 for iteration 9, 2015-2-6, end */
)
{
    MN_MSG_MO_ENTITY_STRU               stMoEntity;
    MN_MSG_RETRY_INFO_STRU              stRetryInfo;
    MN_MSG_SENDMSG_EVT_INFO_STRU        stSendMsgEvt;
    VOS_UINT32                          ulRet;
    VOS_BOOL                            bBufferEntity;
    VOS_UINT32                          ulIndex;
    NAS_OM_SMS_MO_REPORT_STRU           stSmsMoReportPara;

    MN_MSG_StopTimer(MN_MGS_ID_WAIT_MO_SMS_CTRL_CHECK);

    PS_MEM_SET(&stMoEntity, 0, sizeof(stMoEntity));
    PS_MEM_SET(&stRetryInfo, 0, sizeof(stRetryInfo));

    ulRet = MN_MSG_GetSpecificStatusMoEntity(MN_MSG_MO_STATE_WAIT_SMS_CTRL_RSP,
                                             &bBufferEntity,
                                             &ulIndex,
                                             &stMoEntity);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MN_MSG_RcvUsimMoControlRsp: invalid status");
        return;
    }

/*
    ��ȡ���ؽ��USIM�Ĳ�������
    if ����������SMS-PP data download
        if UICC���ؽ����"90 00"(����USIM���ز�ͬ�Ľ��ֵ)
            ����UICC���صĽ������Rp-ACK��TP-UD,ͬʱDCS��PIDӦ�ñ��ֲ���
            ���ú���MN_MSG_Internal_SendRpt����Rp-ACK��Ϣ������
        else if UICC���ؽ����"93 00"
            ���ú���MN_MSG_Internal_SendRpt����Rp-Error��Ϣ������,ͬʱTP-FCS��ֵӦ��Ϊ"SIM Application Toolkit Busy"
        else if UICC���ؽ����"6F XX"
            TP-FCS��ֵӦ��Ϊ"UICC data download error",ͬʱDCS��PIDӦ�ñ��ֲ���
            ���ú���MN_MSG_Internal_SendRpt����Rp-Error��Ϣ������
        else if UICC���صĽ����"62 XX"��"63 XX"
            ����UICC���صĽ������Rp-ERROR��TP-UD,ͬʱDCS��PIDӦ�ñ��ֲ���,TP-FCS��ֵӦ��Ϊ"SIM data download error"
            ���ú���MN_MSG_Internal_SendRpt����Rp-Error��Ϣ������
        else
            ���ú���MN_MSG_Internal_SendRpt����Rp-Error��Ϣ������

*/
    ulRet = MN_MSG_UpdateMoEntityAccordingToMoSmsCtrl(pstEnvelope, &stMoEntity);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG1("MN_MSG_RcvUsimMoControlRsp : MN_MSG_UpdateMoEntityAccordingToMoSmsCtrl ", (VOS_INT32)ulRet);
        MN_SendClientResponse(stMoEntity.clientId,
                              stMoEntity.opId,
                              ulRet);

        MN_MNTN_RecordSmsMoFailure(ulRet);

#if (FEATURE_ON == FEATURE_PTM)
        /* ��¼���ŷ����쳣log */
        MN_MSG_FailErrRecord(ulRet);
#endif

        /* SMS MO FAIL�¼��ϱ� */
        stSmsMoReportPara.ucSmsMr = stMoEntity.ucMr;
        stSmsMoReportPara.ulCause = ulRet;
        
        NAS_EventReport(WUEPS_PID_TAF, NAS_OM_EVENT_SMS_MO_FAIL,
                        &stSmsMoReportPara, sizeof(stSmsMoReportPara));

        MN_MSG_DestroyMoInfo();

        /* ֪ͨSPM����� */
        TAF_MSG_SendSpmMsgCheckResultInd(stMoEntity.clientId, stMoEntity.opId,TAF_MSG_ERROR_CTRL_CHECK_FAIL);
    }
    else
    {
        MN_SendClientResponse(stMoEntity.clientId, stMoEntity.opId, MN_ERR_NO_ERROR);

        MN_MSG_UpdateSmaMoState(MN_MSG_MO_STATE_WAIT_REPORT_IND);

        MN_MSG_GetRetryInfo(&stRetryInfo);

        /* �����ط�����>0 ����Ҫ���������ط�����*/
        if (stRetryInfo.ulRetryPeriod > 0)
        {
            MN_MSG_StartTimer(MN_MSG_ID_WAIT_RETRY_PERIOD,0);
        }

        /*�㲥�ϱ������ѱ�����*/
        PS_MEM_SET(&stSendMsgEvt,0X00,sizeof(stSendMsgEvt));
        stSendMsgEvt.enTpduType = stMoEntity.enTpduType;
        MN_MSG_ReportSentEvent(stMoEntity.clientId, stMoEntity.opId,&stSendMsgEvt,MN_MSG_EVT_MSG_SENT);
    }

    return ;
}

/* MN_MSG_ProcUsimFdnInd */

VOS_VOID MN_MSG_ProcFdnCnf(struct MsgCB * pstMsg)
{
    MN_MSG_MO_ENTITY_STRU               stMoEntity;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulIndex;
    VOS_BOOL                            bCheckMoCtrl;
    VOS_BOOL                            bBufferEntity;
    PB_FDN_CHECK_CNF_STRU              *pstCheckCnf;
    NAS_OM_SMS_MO_REPORT_STRU           stSmsMoReportPara;

    PS_MEM_SET(&stMoEntity, 0, sizeof(stMoEntity));

    /* ��ȡ�ȴ�FDN�������MOʵ��򻺴� */
    ulRet = MN_MSG_GetSpecificStatusMoEntity(MN_MSG_MO_STATE_WAIT_FDN_CHECK_RSP,
                                             &bBufferEntity,
                                             &ulIndex,
                                             &stMoEntity);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MN_MSG_ProcFdnCnf: discard FDN RESPONSE.");
        return;
    }

    pstCheckCnf = (PB_FDN_CHECK_CNF_STRU *)pstMsg;

    /* ĿǰFDN�Ļظ���Ϣͬʱ��CALL��MSGģ��,��Ҫ������ͬclient ID����Ϣ */
    if (stMoEntity.clientId != (pstCheckCnf->ulSendPara & 0x0000FFFF))
    {
        MN_INFO_LOG("MN_MSG_ProcFdnCnf: not same client ID,discard FDN RESPONSE.");
        return;
    }

    MN_MSG_StopTimer(MN_MGS_ID_WAIT_FDN_CHECK);

    /* FDN�����Ϊ��ͨ�����ܾ����ŷ�������ͬʱ�ͷŶ��ŷ���ʵ�� */
    if (PB_FDN_CHECK_SUCC != pstCheckCnf->enResult)
    {
        MN_WARN_LOG("MN_MSG_ProcFdnCnf: Fail to pass FDN check.");
        if (PB_FDN_CHECK_NUM1_FAIL == pstCheckCnf->enResult)
        {
            MN_SendClientResponse(stMoEntity.clientId,
                                  stMoEntity.opId,
                                  MN_ERR_CLASS_FDN_CHECK_SC_FAILURE);

            MN_MNTN_RecordSmsMoFailure(ulRet);
    
#if (FEATURE_ON == FEATURE_PTM)
            /* ��¼���ŷ����쳣log */
            MN_MSG_FailErrRecord(MN_ERR_CLASS_FDN_CHECK_SC_FAILURE);
#endif
    
            /* SMS MO FAIL�¼��ϱ� */
            stSmsMoReportPara.ucSmsMr = stMoEntity.ucMr;
            stSmsMoReportPara.ulCause = MN_ERR_CLASS_FDN_CHECK_SC_FAILURE;
            
            NAS_EventReport(WUEPS_PID_TAF, NAS_OM_EVENT_SMS_MO_FAIL,
                            &stSmsMoReportPara, sizeof(stSmsMoReportPara));
            
        }
        else
        {
            MN_SendClientResponse(stMoEntity.clientId,
                                  stMoEntity.opId,
                                  MN_ERR_CLASS_FDN_CHECK_DN_FAILURE);
                                  
            MN_MNTN_RecordSmsMoFailure(MN_ERR_CLASS_FDN_CHECK_DN_FAILURE);
    
#if (FEATURE_ON == FEATURE_PTM)
            /* ��¼���ŷ����쳣log */
            MN_MSG_FailErrRecord(MN_ERR_CLASS_FDN_CHECK_DN_FAILURE);
#endif
    
            /* SMS MO FAIL�¼��ϱ� */
            stSmsMoReportPara.ucSmsMr = stMoEntity.ucMr;
            stSmsMoReportPara.ulCause = MN_ERR_CLASS_FDN_CHECK_DN_FAILURE;
            
            NAS_EventReport(WUEPS_PID_TAF, NAS_OM_EVENT_SMS_MO_FAIL,
                            &stSmsMoReportPara, sizeof(stSmsMoReportPara));
        }

        /* ���ٵȴ�FDN�������MOʵ��򻺴� */
        MN_MSG_DestroySpecificMoEntity(bBufferEntity, ulIndex);

        /* ֪ͨSPM����� */
        TAF_MSG_SendSpmMsgCheckResultInd(stMoEntity.clientId, stMoEntity.opId,TAF_MSG_ERROR_FDN_CHECK_FAIL);

        return;
    }

    /* MO SMS CONTROL ����:  */
    ulRet = MN_MSG_CheckMoSmsCtrl(&stMoEntity, &bCheckMoCtrl);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MN_MSG_ProcFdnCnf: Fail to MSG_CheckMoSmsCtrl.");
        MN_SendClientResponse(stMoEntity.clientId,
                              stMoEntity.opId,
                              ulRet);
                              
        MN_MNTN_RecordSmsMoFailure(ulRet);

#if (FEATURE_ON == FEATURE_PTM)
        /* ��¼���ŷ����쳣log */
        MN_MSG_FailErrRecord(ulRet);
#endif

        /* SMS MO FAIL�¼��ϱ� */
        stSmsMoReportPara.ucSmsMr = stMoEntity.ucMr;
        stSmsMoReportPara.ulCause = ulRet;
        
        NAS_EventReport(WUEPS_PID_TAF, NAS_OM_EVENT_SMS_MO_FAIL,
                        &stSmsMoReportPara, sizeof(stSmsMoReportPara));

        /* ���ٵȴ�FDN�������MOʵ��򻺴� */
        MN_MSG_DestroySpecificMoEntity(bBufferEntity, ulIndex);
        return;
    }

    /* Ҫ����MO SMS CONTROL: ������ʱ���ȴ�USIM�ļ���� */
    if (VOS_TRUE == bCheckMoCtrl)
    {
        ulRet = MN_MSG_ProcMoCtrl(stMoEntity.clientId,
                                  stMoEntity.opId,
                                  stMoEntity.aucRpDataInfo);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_WARN_LOG("MN_MSG_ProcFdnCnf: Fail to MN_MSG_ProcMoCtrl.");
            MN_SendClientResponse(stMoEntity.clientId,
                                  stMoEntity.opId,
                                  ulRet);

            MN_MNTN_RecordSmsMoFailure(ulRet);
    
#if (FEATURE_ON == FEATURE_PTM)
            /* ��¼���ŷ����쳣log */
            MN_MSG_FailErrRecord(ulRet);
#endif
    
            /* SMS MO FAIL�¼��ϱ� */
            stSmsMoReportPara.ucSmsMr = stMoEntity.ucMr;
            stSmsMoReportPara.ulCause = ulRet;
            
            NAS_EventReport(WUEPS_PID_TAF, NAS_OM_EVENT_SMS_MO_FAIL,
                            &stSmsMoReportPara, sizeof(stSmsMoReportPara));

            /* ���ٵȴ�FDN�������MOʵ��򻺴� */
            MN_MSG_DestroySpecificMoEntity(bBufferEntity, ulIndex);
            return;
        }

        /* ��������Ͷ��ŵ�����ʵ��򻺴棬������״̬��MN_MSG_MO_STATE_WAIT_FDN_CHECK_RSP
           ������ʱ���ȴ�USIM�ļ���� */
        MN_MSG_StartTimer(MN_MGS_ID_WAIT_MO_SMS_CTRL_CHECK, 0);
        MN_MSG_UpdateSpecificMoEntityStatus(bBufferEntity, ulIndex, MN_MSG_MO_STATE_WAIT_SMS_CTRL_RSP);

        return;
    }

    /* ������ʵ���ǰ������ʵ��������̬�����Ͷ�Ϣ��SMS */
    /* FDN��CALL CONTROL�����Ϊͨ�������ͺ�������CC */
    if (VOS_OK == MN_MSG_SendMsgAvailable(bBufferEntity,
                                          ulIndex,
                                          &stMoEntity))
    {
        MN_MSG_SendMsgToSms(&stMoEntity);
    }

    return;

}


VOS_VOID MN_MSG_GetFdnMeCfg(VOS_VOID)
{
    if (NV_OK != NV_Read(en_NV_Item_FDN_Info,
                         &f_stMsgFdnInfo.stFdnConfig,
                         sizeof(TAF_FDN_CONFIG_STRU)))
    {
        f_stMsgFdnInfo.stFdnConfig.enMeStatus        = TAF_FDN_CHECK_FEATURE_OFF;
    }

    return;
}


VOS_UINT32 MN_MSG_CheckFdn(
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity,
    VOS_BOOL                           *pbCheckFdn
)
{
    VOS_BOOL                            bBufferEntity;
    VOS_UINT32                          ulIndex;
    MN_MSG_MO_ENTITY_STRU               stMoEntity;
    VOS_UINT32                          ulRet;

    VOS_UINT32                          ulFdnStatus;

    ulFdnStatus = 0;
    *pbCheckFdn = VOS_FALSE;

    /* �Ѿ����FDN��飬ֱ�ӷ��� */
    if (pstMoEntity->enSmaMoState > MN_MSG_MO_STATE_WAIT_FDN_CHECK_RSP)
    {
        return MN_ERR_NO_ERROR;
    }

    /* STK�û������ҵ����FDNҵ���� */
    if (OAM_CLIENT_ID_STK == pstMoEntity->clientId)
    {
        return MN_ERR_NO_ERROR;
    }

    /* MEû������FDN��鹦�ܣ�ֱ�ӷ���ҵ����ͨ�� */
    if (TAF_FDN_CHECK_FEATURE_ON != f_stMsgFdnInfo.stFdnConfig.enMeStatus)
    {
        return MN_ERR_NO_ERROR;
    }

    /*
    ����(U)SIM����FDN״̬ȷ���Ƿ���FDN���
       0 ȥʹ��: ����FDN���
       1 ʹ��:   ��FDN���
    */
    NAS_USIMMAPI_FdnQuery(&ulFdnStatus);

    if (USIMM_FDNSTATUS_ON == ulFdnStatus)
    {
        *pbCheckFdn = VOS_TRUE;
    }

    /* �����ǰ�Ѿ��ж�����MN_MSG_MO_STATE_WAIT_FDN_CHECK_RSP ״̬��ܾ��¶��� */
    ulRet = MN_MSG_GetSpecificStatusMoEntity(MN_MSG_MO_STATE_WAIT_FDN_CHECK_RSP,
                                             &bBufferEntity,
                                             &ulIndex,
                                             &stMoEntity);
    if (MN_ERR_NO_ERROR == ulRet)
    {
        return MN_ERR_CLASS_SMS_MOSTATE;
    }

    return MN_ERR_NO_ERROR;
}
VOS_VOID MN_MSG_DispatchUsimMsg(struct MsgCB * pstMsg)
{
    switch (((MSG_HEADER_STRU *)pstMsg)->ulMsgName)
    {
        case USIMM_READFILE_CNF:
            MN_MSG_RcvUsimGetFileRsp((VOS_VOID*)pstMsg);
            break;
        case USIMM_UPDATEFILE_CNF:
            MN_MSG_RcvUsimSetFileRsp((VOS_VOID*)pstMsg);
            break;
        case USIMM_QUERYFILE_CNF:
            MN_MSG_RcvUsimGetMaxRecRsp((VOS_VOID*)pstMsg);
            break;
        /* Deleted USIMM_STKENVELOPE_CNF */
        /* Deleted USIMM_STKREFRESH_IND */

        case SI_PB_EVENT_FDNCHECK_CNF:
            /* FDN��������� */
            MN_MSG_ProcFdnCnf(pstMsg);
            break;

        default:
            MN_WARN_LOG("MN_ProcUsimMsg:Rcv Invalid Msg Type");
            break;
    }

    return;
}
VOS_UINT32 MN_MSG_SendMsgAvailable(
    VOS_BOOL                                bBufferEntity,
    VOS_UINT32                              ulIndex,
    MN_MSG_MO_ENTITY_STRU                  *pstMoEntity
)
{
    MN_MSG_MO_ENTITY_STRU               stMoEntity;

    if (VOS_TRUE != bBufferEntity)
    {
        return VOS_OK;
    }

    PS_MEM_SET(&stMoEntity, 0, sizeof(stMoEntity));

    MN_MSG_GetMoEntity(&stMoEntity);
    if (MN_MSG_MO_STATE_NULL == stMoEntity.enSmaMoState)
    {
        MN_MSG_CreateMoInfo(pstMoEntity);
        return VOS_OK;
    }

    return VOS_ERR;
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

