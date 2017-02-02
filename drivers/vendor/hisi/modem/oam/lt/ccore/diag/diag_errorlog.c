/******************************************************************************

    Copyright(C)2014,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : diag_errorlog.c
  Description     : ��ֲomerrorlog����
  History         :
     1.cuijunqiang       2015-7-10     Draft Enact
     2.
******************************************************************************/
#include "vos.h"
#include "product_config.h"
#include "omerrorlog.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define    THIS_FILE_ID        MSP_FILE_ID_DIAG_ERRORLOG_C


#if (FEATURE_ON == FEATURE_PTM)
/* ���ڱ�������Err LOG ע��ص�����ָ�� */
OM_REGISTER_PROJECT_CTX_STRU            g_astFTMCallBackFuncCtx[]={
                                        {OM_ERR_LOG_MOUDLE_ID_IMS,  VOS_NULL_PTR},
                                        {OM_ERR_LOG_MOUDLE_ID_IMSA, VOS_NULL_PTR},
                                       };
#endif

VOS_VOID OmOpenCCPULog(VOS_UINT32 ulFlag);

/******************************************************************************
������  ��OM_RegisterGetData
����������OM Ccpu���ո�����ϱ�����ģʽ���ݵ�APP�ص�����ע��ӿ�
���������enModuleProjectCallback���ص��齨��ţ��̶�ΪOM_VOLTE_MOUDLE_PROJECT
          pFuncProjectCallbak    ���ص�����ָ��
���������NA
����ֵ  ��VOS_UINT32
�޸���ʷ��
1.  ����    ��2014��1��2��
����    ��
�޸����ݣ������ɺ���
˵��:
    1������ģʽ�����ϱ�����֪ͨ����������ṹ��APP_OM_CTRL_STATUS_STRU��Data��ȥOMHead��ulMsgModuleID����������
    2������ģʽ�����ϱ���Ϣ֪ͨ�������Data�����������OmHeard��OMPayload

2.c00326366         2015-7-10  ��ģOM�ں���ֲ

*****************************************************************************/
VOS_UINT32 OM_RegisterGetData(OM_ERR_LOG_MOUDLE_ID_ENUM_UINT32 enProjectModule, pFuncOMGetData pFuncProjectCallback)
{
#if (FEATURE_ON == FEATURE_PTM)
    VOS_UINT32                          ulIndex;

    if (VOS_NULL_PTR == enProjectModule)
    {
        vos_printf("OM_RegisterGetData:ModuleID is %d, func name is null.\r\n", enProjectModule);
        return OM_APP_MSG_MODULE_ID_ERR;
    }

    for (ulIndex=0; ulIndex<(sizeof(g_astFTMCallBackFuncCtx) / sizeof(g_astFTMCallBackFuncCtx[0])); ulIndex++)
    {
        if (g_astFTMCallBackFuncCtx[ulIndex].enProjectModule == enProjectModule)
        {
            break;
        }
    }

    if( (sizeof(g_astFTMCallBackFuncCtx) / sizeof(g_astFTMCallBackFuncCtx[0])) <= ulIndex )
    {
        vos_printf("OM_RegisterGetData:ModuleID is error %d\r\n", enProjectModule);
        return OM_APP_MSG_MODULE_ID_ERR;
    }

    if (VOS_NULL_PTR == g_astFTMCallBackFuncCtx[ulIndex].pSendUlAtFunc)
    {
        g_astFTMCallBackFuncCtx[ulIndex].pSendUlAtFunc = pFuncProjectCallback;
        return VOS_OK;
    }

    vos_printf("OM_RegisterGetData:callback Func is Registed,ModuleID is %d\r\n", enProjectModule);
    return VOS_ERR;
#else

    return VOS_OK;

#endif
}

/******************************************************************************
������  ��OM_GetData
����������OM Ccpu���ո�����ϱ�����ģʽ����
���������enProjectModule    ���齨���
          pData              ����������
          ulLen              ���������ݳ���
���������NA
����ֵ  ��VOS_OK/VOS_ERR
�޸���ʷ��
1.  ����    ��2014��1��2��
����    ��
�޸����ݣ������ɺ���
˵����pData��OMHeader��MsgType��ʼ���൱�ڵ������Ԥ������Header���֣�����Header���ֵ�SN�ֶ���COMM��д

2.c00326366         2015-7-10  ��ģOM�ں���ֲ

*****************************************************************************/
VOS_UINT32 OM_GetData(OM_ERR_LOG_MOUDLE_ID_ENUM_UINT32 enProjectModule, VOS_VOID *pData, VOS_UINT32 ulLen)
{
#if (FEATURE_ON == FEATURE_PTM)
    OM_ALARM_MSG_HEAD_STRU             *pstOmHead;
    OM_FTM_REPROT_IND_STRU             *pstOmFtmReportInd;
    VOS_UINT32                          ulAddr;
    VOS_UINT32                          ulIndex;

    for (ulIndex=0; ulIndex<(sizeof(g_astFTMCallBackFuncCtx) / sizeof(g_astFTMCallBackFuncCtx[0])); ulIndex++)
    {
        /* �ϱ���Ϣʱ����������û��ע����ص��������Ͳ�����������Ϣ */
        if ( (g_astFTMCallBackFuncCtx[ulIndex].enProjectModule == enProjectModule)
             && (g_astFTMCallBackFuncCtx[ulIndex].pSendUlAtFunc  != VOS_NULL_PTR) )
        {
            break;
        }
    }

    if ((sizeof(g_astFTMCallBackFuncCtx) / sizeof(g_astFTMCallBackFuncCtx[0])) <= ulIndex)
    {
        vos_printf("OM_GetData:ModuleID is error %d\r\n", enProjectModule);
        return OM_APP_MSG_MODULE_ID_ERR;
    }

    if ((VOS_NULL_PTR == pData) || ((sizeof(OM_ALARM_MSG_HEAD_STRU) + sizeof(OM_FTM_HEADER_STRU)) > ulLen))
    {
        vos_printf("\r\n OM_GetData: Module ID is %d, Send data is NULL or len is error:%d\n", enProjectModule, ulLen);
        return OM_APP_MSG_LENGTH_ERR;
    }

    /* ����ģʽ�����Ϣ�ϱ���OM */
    pstOmFtmReportInd  = (OM_FTM_REPROT_IND_STRU*)VOS_AllocMsg(MSP_PID_DIAG_AGENT, (ulLen + sizeof(VOS_UINT32)));

    if (VOS_NULL_PTR == pstOmFtmReportInd)
    {
        vos_printf("OM_GetData:Module ID is %d, malloc msg is fail\r\n", enProjectModule);
        return OM_APP_OMCCPU_ALLOC_MSG_ERR;
    }

    pstOmFtmReportInd->ulReceiverPid = MSP_PID_DIAG_APP_AGENT;
    pstOmHead = (OM_ALARM_MSG_HEAD_STRU*)pData;

    /* ��ϢTYPE���ж�*/
    if (OM_ERR_LOG_MSG_FTM_REPORT == pstOmHead->ulMsgType)
    {
        pstOmFtmReportInd->ulMsgName     = ID_OM_FTM_REPROT_IND;
    }
    else if (OM_ERR_LOG_MSG_FTM_CNF == pstOmHead->ulMsgType)
    {
        pstOmFtmReportInd->ulMsgName     = ID_OM_FTM_REQUIRE_CNF;
    }
    else if (OM_ERR_LOG_MSG_ERR_REPORT == pstOmHead->ulMsgType) 
    {
        pstOmFtmReportInd->ulMsgName     = ID_OM_ERR_LOG_REPORT_CNF;
    } 
    else
    {
        vos_printf("OM_GetData:Module ID is %d, Msg Type is Err %d\r\n",
                         enProjectModule, pstOmHead->ulMsgType);

        /*lint -e534*/
        VOS_FreeMsg(MSP_PID_DIAG_AGENT, pstOmFtmReportInd);
        /*lint +e534*/

        return OM_APP_MSG_TYPE_ERR;
    }

    /* make pclint happy  begin */
    ulAddr = (VOS_UINT32)(&pstOmFtmReportInd->ulMsgType);
    /*lint -e534*/
    VOS_MemCpy((VOS_VOID *)ulAddr, (VOS_VOID*)pData, ulLen);
    /*lint +e534*/
    /* make pclint happy  end */

    (VOS_VOID)VOS_SendMsg(MSP_PID_DIAG_AGENT, pstOmFtmReportInd);
#endif

    return OM_APP_MSG_OK;
}


#if (FEATURE_ON == FEATURE_PTM)

#define OM_CCPU_ERRLOG_RCV          (0x01 << 7)
#define OM_CCPU_ERRLOG_PRINT        (0x01 << 8)

VOS_UINT32 g_ulOmCcpuDbgFlag = VOS_FALSE;

/* CCPU ���� DEBUG ��Ϣ */
#define OM_CCPU_DEBUG_TRACE(pucData, ulDataLen, ulSwitch) \
if(VOS_FALSE != (g_ulOmCcpuDbgFlag&ulSwitch)) \
{ \
    VOS_UINT32 ulOmDbgIndex; \
    vos_printf("\n%s, Data Len: = %d\n", __FUNCTION__, ulDataLen); \
    for (ulOmDbgIndex = 0 ; ulOmDbgIndex < ulDataLen; ulOmDbgIndex++) \
    { \
        vos_printf("%02x ", *((VOS_UINT8*)pucData + ulOmDbgIndex)); \
    } \
    vos_printf("\r\n"); \
}


/* ����ErrLog ��ӡ */
#define OM_CCPU_ERR_LOG(string) \
    if(VOS_FALSE != (g_ulOmCcpuDbgFlag & OM_CCPU_ERRLOG_PRINT)) \
    {\
        vos_printf("%s.\r\n",string);\
    }

#define OM_CCPU_ERR_LOG1(string, para1) \
    if(VOS_FALSE != (g_ulOmCcpuDbgFlag & OM_CCPU_ERRLOG_PRINT)) \
    {\
        vos_printf("%s %d.\r\n", string, para1);\
    }

#define OM_CCPU_ERR_LOG2(string, para1, para2) \
    if(VOS_FALSE != (g_ulOmCcpuDbgFlag & OM_CCPU_ERRLOG_PRINT)) \
    {\
        vos_printf("%s %d, %d.\r\n", string, para1, para2);\
    }


extern VOS_UINT32 OM_ErrLogMsgProc(MsgBlock* pMsg);
VOS_VOID OmOpenCCPULog(VOS_UINT32 ulFlag)
{
    g_ulOmCcpuDbgFlag = ulFlag;

    return;
}

/******************************************************************************
������  ��OM_ErrLogMsgProc
����������OM Ccpu���ո�����ϱ�����ģʽ����
���������pMsg    ���յ�����ErrLog����ģʽ����

���������NA
����ֵ  ��VOS_VOID
�޸���ʷ��
1.  ����    ��2014��1��2��
����    ��
�޸����ݣ������ɺ���
*****************************************************************************/
VOS_UINT32 OM_ErrLogMsgProc(MsgBlock* pMsg)
{
    OM_FTM_REQUIRE_STRU                *pstOmFTMMsg;
    OM_FTM_CTRL_IND_STRU               *pstOmFtmCtrlInd; /* ����ģʽ������Ϣ:���ش򿪣��²������ϱ� */
    APP_OM_FTM_REQ_STRU                *pstAppOmFtmReq;  /* ����ģʽ������Ϣ:����һ�Σ��²��ϱ�һ�� */
    APP_OM_CTRL_STATUS_STRU             stAppOmCtrlStatus = {};
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulResult;

    pstOmFTMMsg = (OM_FTM_REQUIRE_STRU*)pMsg;
    switch( pstOmFTMMsg->ulMsgName )
    {
        case ID_OM_FTM_CTRL_IND:
        {
            pstOmFtmCtrlInd = (OM_FTM_CTRL_IND_STRU*)pMsg;

            /* ����ģʽ�����ϱ���� */
            stAppOmCtrlStatus.stOmHeader.ulMsgType = OM_ERR_LOG_MSG_ON_OFF;
            stAppOmCtrlStatus.stOmHeader.ulMsgLen  = sizeof(VOS_UINT32) + sizeof(VOS_UINT16) + 2*sizeof(VOS_UINT8); /* �ýṹ�峤�� */
            stAppOmCtrlStatus.usModemID            = pstOmFTMMsg->usModemID;
            stAppOmCtrlStatus.ucAlmStatus          = pstOmFtmCtrlInd->ucActionFlag;

            /*lint -e40 -e534*/
            OM_CCPU_DEBUG_TRACE(((VOS_UINT8*)&stAppOmCtrlStatus), sizeof(stAppOmCtrlStatus), OM_CCPU_ERRLOG_RCV);
            /*lint +e40 +e534*/

            for (ulIndex=0; ulIndex<(sizeof(g_astFTMCallBackFuncCtx) / sizeof(g_astFTMCallBackFuncCtx[0])); ulIndex++)
            {
                if (VOS_NULL_PTR == g_astFTMCallBackFuncCtx[ulIndex].pSendUlAtFunc)
                {
                    continue;
                }

                stAppOmCtrlStatus.ulMsgModuleID = g_astFTMCallBackFuncCtx[ulIndex].enProjectModule;
                ulResult = g_astFTMCallBackFuncCtx[ulIndex].pSendUlAtFunc(stAppOmCtrlStatus.ulMsgModuleID,
                                                                        (VOS_VOID *)&stAppOmCtrlStatus,
                                                                        sizeof(stAppOmCtrlStatus));
                if (VOS_OK != ulResult)
                {
                    /*lint -e534*/
                    OM_CCPU_ERR_LOG2("OM_ErrLogMsgProc:Module ID is %d, return value fail: %d\r\n",
                                 stAppOmCtrlStatus.ulMsgModuleID, ulResult);
                    /*lint +e534*/
                }
            }

            break;
        }

        case ID_OM_FTM_REQUIRE_IND:
        {
            pstAppOmFtmReq = (APP_OM_FTM_REQ_STRU*)pstOmFTMMsg->aucContent;

            /*lint -e40 -e534*/
            OM_CCPU_DEBUG_TRACE((VOS_UINT8*)pstAppOmFtmReq,
                                (sizeof(APP_OM_FTM_REQ_STRU) - 4*sizeof(VOS_UINT8) + pstAppOmFtmReq->ulProjectLength),
                                OM_CCPU_ERRLOG_RCV);
            /*lint +e40 +e534*/

            /* ����ģʽ�����ϱ���� */
            for (ulIndex=0; ulIndex<(sizeof(g_astFTMCallBackFuncCtx) / sizeof(g_astFTMCallBackFuncCtx[0])); ulIndex++)
            {
                if (g_astFTMCallBackFuncCtx[ulIndex].enProjectModule != pstAppOmFtmReq->ulMsgModuleID)
                {
                    continue;
                }

                if (VOS_NULL_PTR == g_astFTMCallBackFuncCtx[ulIndex].pSendUlAtFunc)
                {
                    continue;
                }

                ulResult = g_astFTMCallBackFuncCtx[ulIndex].pSendUlAtFunc(pstAppOmFtmReq->ulMsgModuleID,
                                                                          (VOS_VOID *)pstAppOmFtmReq,
                                                                          (sizeof(APP_OM_FTM_REQ_STRU) + pstAppOmFtmReq->ulProjectLength - sizeof(VOS_UINT32)));

                if (VOS_OK != ulResult)
                {
                    /*lint -e534*/
                    OM_CCPU_ERR_LOG2("OM_ErrLogMsgProc:Module ID is %d, return value fail: %d\r\n",
                                 pstAppOmFtmReq->ulMsgModuleID, ulResult);
                }
            }
            break;
        }

        case ID_OM_ERR_LOG_CTRL_IND:
        {
            OM_ERROR_LOG_CTRL_IND_STRU *pstOmErrCtrlInd = (OM_ERROR_LOG_CTRL_IND_STRU *)pMsg;

            stAppOmCtrlStatus.stOmHeader.ulMsgType = OM_ERR_LOG_MSG_ON_OFF;
            stAppOmCtrlStatus.stOmHeader.ulMsgLen  = sizeof(VOS_UINT32) + sizeof(VOS_UINT16) + 2*sizeof(VOS_UINT8); /* �ýṹ�峤�� */
            stAppOmCtrlStatus.ulMsgModuleID        = OM_APP_SWITCH_MSG_ID_ERR_LOG;  /* �μ�Kirin����Errlog���϶�λ&����ģʽ��չ����-ƽ̨�ӿ�˵�����������ҵ��ӿ� */
            stAppOmCtrlStatus.usModemID            = pstOmErrCtrlInd->usModemID;
            stAppOmCtrlStatus.ucAlmStatus          = pstOmErrCtrlInd->ucAlmStatus;
            stAppOmCtrlStatus.ucAlmLevel           = pstOmErrCtrlInd->ucAlmLevel;

            /*lint -e40*/
            OM_CCPU_DEBUG_TRACE(((VOS_UINT8*)&stAppOmCtrlStatus), sizeof(stAppOmCtrlStatus), OM_CCPU_ERRLOG_RCV);
            /*lint +e40*/

            for (ulIndex=0; ulIndex<(sizeof(g_astFTMCallBackFuncCtx) / sizeof(g_astFTMCallBackFuncCtx[0])); ulIndex++)
            {
                if (VOS_NULL_PTR == g_astFTMCallBackFuncCtx[ulIndex].pSendUlAtFunc)
                {
                    continue;
                }

                ulResult = g_astFTMCallBackFuncCtx[ulIndex].pSendUlAtFunc(stAppOmCtrlStatus.ulMsgModuleID,
                                                                                    (VOS_VOID *)&stAppOmCtrlStatus,
                                                                                    sizeof(stAppOmCtrlStatus));
                if (VOS_OK != ulResult){
                    OM_CCPU_ERR_LOG2("OM_ErrLogMsgProc:Module ID is %d, return value fail: %d\r\n",
                                             stAppOmCtrlStatus.ulMsgModuleID, ulResult);
                }
            }
            break;
        }

        /* һ���ϱ� */
        case ID_OM_ERR_LOG_REPORT_REQ:
        {
            APP_OM_REQ_ERR_LOG_STRU pstAppOmErrReq;
            OM_ERR_LOG_REPORT_REQ_STRU *p       = (OM_ERR_LOG_REPORT_REQ_STRU *)pMsg;
            pstAppOmErrReq.stOmHeader.ulMsgType = OM_ERR_LOG_MSG_SET_ERR_REPORT;
            pstAppOmErrReq.stOmHeader.ulMsgLen  = sizeof(VOS_UINT32) + 2* sizeof(VOS_UINT16);
            pstAppOmErrReq.ulMsgModuleID        = 0x01000000; /* �μ�Kirin����Errlog���϶�λ&����ģʽ��չ����-ƽ̨�ӿ�˵�����������ҵ��ӿ� */
            pstAppOmErrReq.usModemID            = p->usModemID;

            OM_CCPU_DEBUG_TRACE(((VOS_UINT8*)&pstAppOmErrReq), sizeof(pstAppOmErrReq), OM_CCPU_ERRLOG_RCV);

            for (ulIndex=0; ulIndex<(sizeof(g_astFTMCallBackFuncCtx) / sizeof(g_astFTMCallBackFuncCtx[0])); ulIndex++)
            {
                if (VOS_NULL_PTR == g_astFTMCallBackFuncCtx[ulIndex].pSendUlAtFunc)
                {
                    continue;
                }

                ulResult = g_astFTMCallBackFuncCtx[ulIndex].pSendUlAtFunc(pstAppOmErrReq.ulMsgModuleID,
                                                                        (VOS_VOID *)&pstAppOmErrReq,
                                                                        sizeof(pstAppOmErrReq));

                if (VOS_OK != ulResult){
                    OM_CCPU_ERR_LOG2("OM_ErrLogMsgProc:Module ID is %d, return value fail: %d\r\n",
                                 pstAppOmErrReq.ulMsgModuleID, ulResult);
                }
            }
            break;
        }

        default:
            /*lint -e534*/
            OM_CCPU_ERR_LOG1("OM_ErrLogMsgProc:msg name is err %d\r\n", pstOmFTMMsg->ulMsgName);
            /*lint +e534*/
            break;
    }

    return VOS_OK;
}

#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


