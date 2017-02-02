/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : ImsaProcMsccMsg.c
  Description     : ��C�ļ�ʵ��MSCC��Ϣ�����MSCC��Ϣ����
  History           :
     1.sunbing 49683      2013-06-19  Draft Enact
     2.zhaochen 00308719  2015-02-02  Modify for MSCC Interface

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "PsTypeDef.h"
#include "ImsaProcMsccMsg.h"
#include "ImsaEntity.h"
#include "ImsaPublic.h"
#include "ImsaServiceManagement.h"
#include "ImsaImsAdaption.h"
#include "ImsaMain.h"
#include "ImsaImsApi.h"
#include "ImsaProcSpmMsg.h"
#include "ImsaConnManagement.h"


/*lint -e767*/
#define    THIS_FILE_ID       PS_FILE_ID_IMSAPROCMSCCMSG_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/


/*****************************************************************************
  3 Function
*****************************************************************************/

/*lint -e961*/
/*****************************************************************************
 Function Name  : IMSA_ProcMsccMsg()
 Description    : MSCC��Ϣ������
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-21  Draft Enact
      2.zhaochen 00308719  2015-02-02  Modify for MSCC Interface
*****************************************************************************/
VOS_VOID IMSA_ProcMsccMsg(const VOS_VOID *pRcvMsg )
{
    /* ������Ϣͷָ��*/
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;

    /* ��ȡ��Ϣͷָ��*/
    pHeader = (PS_MSG_HEADER_STRU *) pRcvMsg;

    switch(pHeader->ulMsgName)
    {
        case ID_MSCC_IMSA_START_REQ:
            IMSA_ProcMsccMsgStartReq();
            break;

        case ID_MSCC_IMSA_STOP_REQ:
            IMSA_ProcMsccMsgStopReq(pRcvMsg);
            break;

        case ID_MSCC_IMSA_DEREG_REQ:
            IMSA_ProcMsccMsgDeregReq();
            break;

        case ID_MSCC_IMSA_SERVICE_CHANGE_IND:
            IMSA_ProcMsccMsgServiceChangeInd(pRcvMsg);
            break;

        case ID_MSCC_IMSA_CAMP_INFO_CHANGE_IND:
            IMSA_ProcMsccMsgCampInfoChangeInd(pRcvMsg);
            break;
        case ID_MSCC_IMSA_VOICE_DOMAIN_CHANGE_IND:
            IMSA_ProcMsccMsgVoiceDomainChangeInd(pRcvMsg);
            break;
        default:
            break;
    }
}

/*****************************************************************************
 Function Name  : IMSA_ProcMsccMsgStartReq()
 Description    : MSCC������Ϣ������
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-21  Draft Enact
      2.zhaochen 00308719  2015-02-02  Modify for MSCC Interface
*****************************************************************************/
VOS_VOID IMSA_ProcMsccMsgStartReq(VOS_VOID  )
{
    IMSA_CONTROL_MANAGER_STRU  *pstControlManager;
    static VOS_UINT8            ucD2ImsTaskStart = 0;

    pstControlManager = IMSA_GetControlManagerAddress();

    if(ucD2ImsTaskStart == 0)
    {
        /*��ʼ��D2Э��ջ*/
        (VOS_VOID)IMSA_ImsInit();

        ucD2ImsTaskStart ++;
    }

    /*�жϿ���״̬������ѿ�������ظ������ɹ�*/
    if(pstControlManager->enImsaStatus == IMSA_STATUS_STARTED)
    {
        IMSA_SndMsccMsgStartCnf();
        return;
    }

    /*�Ѵ��ڿ�������״̬������*/
    if(pstControlManager->enImsaStatus == IMSA_STATUS_STARTING)
    {
        IMSA_WARN_LOG("IMSA_ProcMsccMsgStartReq: Status is Starting!");
        TLPS_PRINT2LAYER_WARNING(IMSA_ProcMsccMsgStartReq_ENUM, IMSA_PRINT_STATUS_STARTING);
        return;
    }

    IMSA_StopTimer(&pstControlManager->stProtectTimer);

    /*��ʼ��*/

    /*��ȡNV*/
    IMSA_ReadImsaNV();

    /*֪ͨIMS������ת״̬*/
    pstControlManager->enImsaStatus = IMSA_STATUS_STARTING;

    IMSA_SndImsMsgStartReq();

    IMSA_StartTimer(&pstControlManager->stProtectTimer);

    /*����λ�����ȡ����Ϣ*/
    if(pstControlManager->enImsaIsimStatus == IMSA_ISIM_STATUS_AVAILABLE)
    {
        IMSA_INFO_LOG("IMSA_ProcMsccMsgStartReq: ISIM is available!");
        TLPS_PRINT2LAYER_INFO(IMSA_ProcMsccMsgStartReq_ENUM, 2);
        IMSA_ReadIsimFile();
    }
}

/*****************************************************************************
 Function Name  : IMSA_SndMsccMsgStartCnf()
 Description    : ��MSCC���Ϳ����ظ���Ϣ
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-26  Draft Enact
      2.zhaochen 00308719  2015-02-02  Modify for MSCC Interface
*****************************************************************************/
VOS_VOID IMSA_SndMsccMsgStartCnf(VOS_VOID  )
{
    IMSA_MSCC_START_CNF_STRU           *pstImsaMsccStartCnf;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstImsaMsccStartCnf = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_MSCC_START_CNF_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstImsaMsccStartCnf)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SndMsccMsgStartCnf:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndMsccMsgStartCnf_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET( IMSA_GET_MSG_ENTITY(pstImsaMsccStartCnf), 0, IMSA_GET_MSG_LENGTH(pstImsaMsccStartCnf));

    /*��д��Ϣͷ*/
    IMSA_WRITE_MSCC_MSG_HEAD(pstImsaMsccStartCnf, ID_IMSA_MSCC_START_CNF);

    /*������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstImsaMsccStartCnf);
}




/*****************************************************************************
 Function Name  : IMSA_ProcMsccMsgStopReq()
 Description    : MSCC�ػ���Ϣ������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-21  Draft Enact
      2.zhaochen 00308719  2015-02-02  Modify for MSCC Interface
*****************************************************************************/
VOS_VOID IMSA_ProcMsccMsgStopReq
(
    const VOS_VOID                     *pRcvMsg
)
{
    IMSA_CONTROL_MANAGER_STRU *pstControlManager;

    MSCC_IMSA_STOP_REQ_STRU            *pstMsccImsaStopReq = VOS_NULL_PTR;

    pstMsccImsaStopReq = (MSCC_IMSA_STOP_REQ_STRU*) pRcvMsg;
    IMSA_INFO_LOG("IMSA_ProcMsccMsgStopReq: enter!");
    TLPS_PRINT2LAYER_INFO(IMSA_ProcMsccMsgStopReq_ENUM, LNAS_ENTRY);

    pstControlManager = IMSA_GetControlManagerAddress();

    /* SRVCC�쳣(����ػ���DEREG REQ��״̬Ǩ��CONN+REG)���建�� */
    IMSA_SrvccAbormalClearBuff(IMSA_SRVCC_ABNORMAL_STOP_REQ);

    /*�ж�״̬������ѹػ�����ظ��ػ��ɹ�*/
    if(pstControlManager->enImsaStatus == IMSA_STATUS_NULL)
    {
        IMSA_SndMsccMsgStopCnf();
        return;
    }

    /*�Ѵ��ڹػ�״̬������*/
    if(pstControlManager->enImsaStatus == IMSA_STATUS_STOPING)
    {
        IMSA_WARN_LOG("IMSA_ProcMsccMsgStopReq: Status is Stoping!");
        TLPS_PRINT2LAYER_WARNING(IMSA_ProcMsccMsgStopReq_ENUM, IMSA_PRINT_STATUS_STOPING);
        return;
    }

    /*ֹͣ���ػ�������ʱ��*/
    IMSA_StopTimer(&pstControlManager->stProtectTimer);
    /* ��¼�ػ��������͡�����ػ�����������ims��̬�رգ�����Ҫ���յ�IMS�ػ�������ͷ����г��� */
    pstControlManager->enStopType = pstMsccImsaStopReq->enStopType;

    /*֪ͨIMS�ػ���ת״̬*/
    pstControlManager->enImsaStatus = IMSA_STATUS_STOPING;

    /*�ػ��󣬿���λʱ����Ҫ����״̬��Ϊ��Ч����Ϊ�����п���Ч�ĳ�������Ҫ�ػ������״̬*/
    if(pstControlManager->enImsaIsimStatus != IMSA_ISIM_STATUS_ABSENT)
    {
        pstControlManager->enImsaIsimStatus = IMSA_ISIM_STATUS_AVAILABLE;
    }

    IMSA_SndImsMsgStopReq();

    /*�������ػ�������ʱ��*/
    IMSA_StartTimer(&pstControlManager->stProtectTimer);
}

/*****************************************************************************
 Function Name  : IMSA_SndMsccMsgStopCnf()
 Description    : ��MSCC���Ϳ����ظ���Ϣ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-21  Draft Enact
      2.zhaochen 00308719  2015-02-02  Modify for MSCC Interface
*****************************************************************************/
VOS_VOID IMSA_SndMsccMsgStopCnf(VOS_VOID  )
{
    IMSA_MSCC_STOP_CNF_STRU           *pstImsaMsccStopCnf;

    IMSA_INFO_LOG("IMSA_SndMsccMsgStopCnf:enter!");
    TLPS_PRINT2LAYER_INFO(IMSA_SndMsccMsgStopCnf_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstImsaMsccStopCnf = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_MSCC_STOP_CNF_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstImsaMsccStopCnf)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SndMsccMsgStopCnf:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndMsccMsgStopCnf_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET( IMSA_GET_MSG_ENTITY(pstImsaMsccStopCnf), 0, IMSA_GET_MSG_LENGTH(pstImsaMsccStopCnf));

    /*��д��Ϣͷ*/
    IMSA_WRITE_MSCC_MSG_HEAD(pstImsaMsccStopCnf, ID_IMSA_MSCC_STOP_CNF);

    /*������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstImsaMsccStopCnf);
}



/*****************************************************************************
 Function Name  : IMSA_ProcMsccMsgDeregReq()
 Description    : MSCCȥע����Ϣ������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-21  Draft Enact
      2.zhaochen 00308719  2015-02-02  Modify for MSCC Interface
*****************************************************************************/
VOS_VOID IMSA_ProcMsccMsgDeregReq(VOS_VOID )
{
    /* SRVCC�쳣(����ػ���DEREG REQ��״̬Ǩ��CONN+REG)���建�� */
    IMSA_SrvccAbormalClearBuff(IMSA_SRVCC_ABNORMAL_DEREG_REQ);

    IMSA_SRV_ProcDeregReq(IMSA_SRV_DEREG_CAUSE_MSCC_DEREG_REQ);

    return ;
}

/*****************************************************************************
 Function Name  : IMSA_ProcMsccMsgDeregReq()
 Description    : MSCC SERVICE CHANGE IND��Ϣ������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-21  Draft Enact
      2.zhaochen 00308719  2015-02-02  Modify for MSCC Interface
*****************************************************************************/
VOS_VOID IMSA_ProcMsccMsgServiceChangeInd
(
    const VOS_VOID                     *pRcvMsg
)
{
    IMSA_SRV_ProcServiceChangeInd((MSCC_IMSA_SERVICE_CHANGE_IND_STRU*)pRcvMsg);

    return ;
}


VOS_VOID IMSA_ProcMsccMsgCampInfoChangeInd
(
    const VOS_VOID                     *pRcvMsg
)
{
    IMSA_SRV_ProcCampInfoChangeInd((MSCC_IMSA_CAMP_INFO_CHANGE_IND_STRU*)pRcvMsg);

    return ;
}


/*****************************************************************************
 Function Name  : IMSA_SndMsccMsgDeregCnf()
 Description    : ��MSCC����ȥע��ظ���Ϣ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-26  Draft Enact
      2.zhaochen 00308719  2015-02-02  Modify for MSCC Interface
*****************************************************************************/
VOS_VOID IMSA_SndMsccMsgDeregCnf(VOS_VOID )
{
    IMSA_MSCC_DEREGISTER_CNF_STRU           *pstImsaMsccDeregCnf;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstImsaMsccDeregCnf = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_MSCC_DEREGISTER_CNF_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstImsaMsccDeregCnf)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SndMsccMsgDeregCnf:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndMsccMsgDeregCnf_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET( IMSA_GET_MSG_ENTITY(pstImsaMsccDeregCnf), 0, IMSA_GET_MSG_LENGTH(pstImsaMsccDeregCnf));

    /*��д��Ϣͷ*/
    IMSA_WRITE_MSCC_MSG_HEAD(pstImsaMsccDeregCnf, ID_IMSA_MSCC_DEREG_CNF);

    /*������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstImsaMsccDeregCnf);
}

VOS_VOID IMSA_ProcMsccMsgVoiceDomainChangeInd
(
    const VOS_VOID                     *pRcvMsg
)
{
    IMSA_SRV_ProcVoiceDomainChangeInd((MSCC_IMSA_VOICE_DOMAIN_CHANGE_IND_STRU*)pRcvMsg);

    return ;
}

/*****************************************************************************
 Function Name  : IMSA_ProcImsMsgStartOrStopCnf()
 Description    : ����IMS�������߹ػ����
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-24  Draft Enact
      2.zhaochen 00308719  2015-02-02  Modify for MSCC Interface
*****************************************************************************/
VOS_VOID IMSA_ProcImsMsgStartOrStopCnf(VOS_VOID)
{
    IMSA_CONTROL_MANAGER_STRU          *pstControlManager;
    IMSA_NORMAL_CONN_STRU              *pstNormalConn      = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                 *pstEmcConn         = VOS_NULL_PTR;
    VOS_UINT8                           ucOpid             = IMSA_NULL;
    VOS_UINT32                          ulLoop             = IMSA_NULL;

    IMSA_NORM_LOG("IMSA_ProcImsMsgStartOrStopCnf: Enter!");
    TLPS_PRINT2LAYER_ERROR(IMSA_ProcImsMsgStartOrStopCnf_ENUM, LNAS_ENTRY);

    pstControlManager = IMSA_GetControlManagerAddress();

    /*ֹͣ���ػ�������ʱ��*/
    IMSA_StopTimer(&pstControlManager->stProtectTimer);

    /*�ػ�����*/
    if(pstControlManager->enImsaStatus == IMSA_STATUS_STOPING)
    {
        /* �����IMS��̬�ر����͵Ĺػ������ͷ����� */
        if (pstControlManager->enStopType == MSCC_IMSA_STOP_TYPE_IMS_SWITCH_OFF)
        {
            pstEmcConn      = IMSA_CONN_GetEmcConnAddr();
            if (IMSA_CONN_STATUS_IDLE != pstEmcConn->enImsaConnStatus)
            {
                /* ����APS�ͷ����� */
                IMSA_WARN_LOG("IMSA_ProcImsMsgStartOrStopCnf:releasing emc conn!");
                TLPS_PRINT2LAYER_INFO(IMSA_ProcImsMsgStartOrStopCnf_ENUM, IMSA_EMERGENCY);
                /* �����CONNING̬���������ͷ����ڽ�����������غ��Ѿ������������� */
                if (IMSA_CONN_STATUS_CONNING == pstEmcConn->enImsaConnStatus)
                {
                    /* ����OPID���洢 */
                    IMSA_CONN_AssignOpid(IMSA_CONN_TYPE_EMC, &ucOpid);
                    if (VOS_OK != TAF_PS_CallEnd(   PS_PID_IMSA, IMSA_CLIENT_ID, ucOpid,
                                                    pstEmcConn->stSelSdfPara.ucCid))
                    {
                        IMSA_WARN_LOG("IMSA_ProcImsMsgStartOrStopCnf:EMC,conninig,CallEnd failed!");
                        TLPS_PRINT2LAYER_ERROR1(IMSA_ProcImsMsgStartOrStopCnf_ENUM, IMSA_CALL_API_ERROR, 1);
                    }
                }

                else
                {
                    /* ����OPID���洢 */
                    IMSA_CONN_AssignOpid(IMSA_CONN_TYPE_EMC, &ucOpid);

                    if (VOS_OK != TAF_PS_CallEnd(   PS_PID_IMSA, IMSA_CLIENT_ID, ucOpid,
                                                    (VOS_UINT8)pstEmcConn->stSipSignalPdp.ucCid))
                    {
                        IMSA_WARN_LOG("IMSA_ProcImsMsgStartOrStopCnf:IMS Swtich off,conn,CallEnd failed!");
                        TLPS_PRINT2LAYER_ERROR1(IMSA_ProcImsMsgStartOrStopCnf_ENUM, IMSA_CALL_API_ERROR, 2);
                    }
                    IMSA_CONN_SndCdsSetImsBearerReq();
                }
            }
            pstNormalConn      = IMSA_CONN_GetNormalConnAddr();
            if (IMSA_CONN_STATUS_IDLE != pstNormalConn->enImsaConnStatus)
            {
                /* ����APS�ͷ����� */
                IMSA_WARN_LOG("IMSA_ProcImsMsgStartOrStopCnf:releasing normal conn!");
                TLPS_PRINT2LAYER_INFO(IMSA_ProcImsMsgStartOrStopCnf_ENUM, IMSA_NORMAL);
                /* �����CONNING̬���������ͷ����ڽ�����������غ��Ѿ������������� */
                if (IMSA_CONN_STATUS_CONNING == pstNormalConn->enImsaConnStatus)
                {
                    /* ����OPID���洢 */
                    IMSA_CONN_AssignOpid(IMSA_CONN_TYPE_NORMAL, &ucOpid);

                    if (VOS_OK != TAF_PS_CallEnd(   PS_PID_IMSA, IMSA_CLIENT_ID, ucOpid,
                                                    pstNormalConn->stSelSdfPara.ucCid))
                    {
                        IMSA_WARN_LOG("IMSA_ProcImsMsgStartOrStopCnf:IMS Swtich off,normal,conninig,CallEnd failed!");
                        TLPS_PRINT2LAYER_ERROR1(IMSA_ProcImsMsgStartOrStopCnf_ENUM, IMSA_CALL_API_ERROR, 3);
                    }
                }

                if (0 == pstNormalConn->ulSipSignalPdpNum)
                {
                    IMSA_WARN_LOG("IMSA_ProcImsMsgStartOrStopCnf:IMS Swtich off,normal,conning,no active pdp!");
                    TLPS_PRINT2LAYER_ERROR(IMSA_ProcImsMsgStartOrStopCnf_ENUM, IMSA_NO_ACTIVE_PDP);
                }
                else
                {
                    /* ��������˶�����أ���Ҫ����ͷ� */
                    for (ulLoop = 0 ; ulLoop < pstNormalConn->ulSipSignalPdpNum ; ulLoop ++)
                    {
                        /* ����OPID���洢 */
                        IMSA_CONN_AssignOpid(IMSA_CONN_TYPE_NORMAL, &ucOpid);
                        if (VOS_OK != TAF_PS_CallEnd(   PS_PID_IMSA, IMSA_CLIENT_ID, ucOpid,
                                                    pstNormalConn->astSipSignalPdpArray[ulLoop].ucCid))
                        {
                            IMSA_WARN_LOG("IMSA_ProcImsMsgStartOrStopCnf:IMS Swtich off,normal,CallEnd failed!");
                            TLPS_PRINT2LAYER_ERROR1(IMSA_ProcImsMsgStartOrStopCnf_ENUM, IMSA_CALL_API_ERROR, 4);
                        }
                    }
                    IMSA_CONN_SndCdsSetImsBearerReq();
               }
            }
        }
        /*�����Դ*/
        IMSA_ClearResource();

        /*����ȴ�����״̬*/
        pstControlManager->enImsaStatus = IMSA_STATUS_NULL;

        IMSA_SndMsccMsgStopCnf();
    }
    else if(pstControlManager->enImsaStatus == IMSA_STATUS_STARTING)
    {
        /*���뿪��״̬*/
        pstControlManager->enImsaStatus = IMSA_STATUS_STARTED;

        IMSA_SndMsccMsgStartCnf();

        /* ��IMS����UE���� */
        IMSA_ConfigUeCapabilityInfo2Ims();

        if ((IMSA_OP_TRUE == pstControlManager->stImsaCommonInfo.stImsaUeId.bitOpImpi)
            && (IMSA_OP_TRUE == pstControlManager->stImsaCommonInfo.stImsaUeId.bitOpTImpu)
            && (IMSA_OP_TRUE == pstControlManager->stImsaCommonInfo.bitOpHomeNetDomainName))
        {
            /* config account info to ims */
            IMSA_ConfigAccoutInfo2Ims(IMSA_REG_TYPE_NORMAL);

            /* config account info to ims */
            IMSA_ConfigAccoutInfo2Ims(IMSA_REG_TYPE_EMC);
        }

        /* set imei */
        IMSA_ConfigImei2Ims();

        /* set retry time */
        IMSA_ConfigTimerLength2Ims();

        IMSA_ConfigSipPort2Ims();

        /* ��IMS����SIP��Ϣ */
        IMSA_ConfigSipInfo2Ims();

        IMSA_ConfigVoipInfo2Ims();

        IMSA_ConfigCodeInfo2Ims();

        IMSA_ConfigSsConfInfo2Ims();

        IMSA_ConfigSecurityInfo2Ims();

        IMSA_ConfigMediaParmInfo2Ims();
    }
    else
    {
        IMSA_WARN_LOG("IMSA_ProcImsMsgStartOrStopCnf: err stat!");
        TLPS_PRINT2LAYER_WARNING(IMSA_ProcImsMsgStartOrStopCnf_ENUM, IMSA_STATE_ERROR);
    }


}
 VOS_VOID IMSA_SndMsccMsgImsVoiceCapNotify
 (
    MSCC_IMSA_IMS_VOICE_CAP_ENUM_UINT8   enImsVoiceCap,
    VOS_UINT32                          ucIsExistPersistentBearer
 )
 {
     IMSA_MSCC_IMS_VOICE_CAP_NOTIFY_STRU     *pstImsaMsccImsVoiceCap;

     /*����ռ䲢��������Ƿ�ɹ�*/
     pstImsaMsccImsVoiceCap = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_MSCC_IMS_VOICE_CAP_NOTIFY_STRU));

     /*����Ƿ����ɹ�*/
     if (VOS_NULL_PTR == pstImsaMsccImsVoiceCap)
     {
         /*��ӡ�쳣��Ϣ*/
         IMSA_ERR_LOG("IMSA_SndMsccMsgImsVoiceCapNotify:ERROR:Alloc Msg fail!");
         TLPS_PRINT2LAYER_ERROR(IMSA_SndMsccMsgImsVoiceCapNotify_ENUM, LNAS_NULL_PTR);
         return ;
     }

     /*���*/
     IMSA_MEM_SET( IMSA_GET_MSG_ENTITY(pstImsaMsccImsVoiceCap), 0, IMSA_GET_MSG_LENGTH(pstImsaMsccImsVoiceCap));

     /*��д��Ϣͷ*/
     IMSA_WRITE_MSCC_MSG_HEAD(pstImsaMsccImsVoiceCap, ID_IMSA_MSCC_IMS_VOICE_CAP_NOTIFY);


     pstImsaMsccImsVoiceCap->enImsVoiceCap = enImsVoiceCap;

    pstImsaMsccImsVoiceCap->ucIsExistPersistentBearer = (VOS_UINT8)ucIsExistPersistentBearer;

    /*������Ϣ���ͺ��� */
     IMSA_SND_MSG(pstImsaMsccImsVoiceCap);
 }
/*lint +e961*/


#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ImsaProcMmaMsg.c */



