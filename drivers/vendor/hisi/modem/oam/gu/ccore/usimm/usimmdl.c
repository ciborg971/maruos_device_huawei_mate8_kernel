
#include "product_config.h"

#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)

#include "usimmdl.h"
#include "usimmt1dl.h"
#include "v_iddef.h"
#include "usimmglobal.h"
#include "msp_diag_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_USIMM_DLMODULE_C
/*lint +e767*/


VOS_VOID USIMM_DLJudgeCmdCase(
    USIMM_APDU_ST                       *pstAPDUData)
{
        /* �жϵ�ǰ�Ŀ��������� */
    if (0 == pstAPDUData->ulLcValue)
    {
        if (0 == pstAPDUData->ulLeValue) /* Lc,Le�������� */
        {
            gstUSIMMDLControl.enCMDCase = USIMM_CMD_CASE1;
        }
        else                            /* Lc������,Le���� */
        {
            gstUSIMMDLControl.enCMDCase = USIMM_CMD_CASE2;
        }
    }
    else
    {
        if (0 == pstAPDUData->ulLeValue) /* Lc����,Le������ */
        {
            gstUSIMMDLControl.enCMDCase = USIMM_CMD_CASE3;
        }
        else                            /* Lc,Le������ */
        {
            gstUSIMMDLControl.enCMDCase = USIMM_CMD_CASE4;
        }
    }

    return;
}
VOS_VOID USIMM_SciDataHook(VOS_UINT32 ulLength, VOS_UINT8 *pucData)
{
    MsgBlock                           *pMsg;

#ifdef USIMM_DEBUG_PEINT
    VOS_UINT32   i;

    /*lint -e534*/
    vos_printf("\r\nSciDataHook Length is :%d\r\n",ulLength);
    /*lint +e534*/

    for(i = 0;i<ulLength; i++)
    {
        /*lint -e534*/
        vos_printf("%02x,", pucData[i]);
        /*lint +e534*/
    }

    /*lint -e534*/
    vos_printf("\r\nend\n");
    /*lint +e534*/
#endif

    USIMM_LogDataSave(pucData, (VOS_UINT8)ulLength);

    USIMM_ExcLogDataSave(pucData, (VOS_UINT8)ulLength);

    pMsg = (MsgBlock*)VOS_AllocMsg(WUEPS_PID_USIM, ulLength);

    if(VOS_NULL_PTR == pMsg)
    {
        USIMM_WARNING_LOG("USIMM_SciDataHook:WARNING:alloc msg failed\n");

        return;
    }

    pMsg->ulReceiverPid   = WUEPS_PID_USIM;

    pMsg->ulLength        = ulLength;

    /*lint -e534*/
    VOS_MemCpy(pMsg->aucValue, pucData, ulLength);
    /*lint +e534*/

    DIAG_TraceReport((VOS_VOID *)(pMsg));

    /*lint -e534*/
    (VOS_VOID)VOS_FreeMsg(WUEPS_PID_USIM, pMsg);
    /*lint +e534*/

    return;
}


VOS_VOID USIMM_DLStateStar(
    USIMM_APDU_ST                       *pstAPDUData)
{
    USIMM_DLJudgeCmdCase(pstAPDUData);

    /*��������ͷ����ʼ�����ֵ*/
    gstUSIMMDLControl.ulSendDataLen = sizeof(pstAPDUData->aucAPDU);

    gstUSIMMDLControl.ulRecDataLen  = sizeof(pstAPDUData->ucACK);

    gstUSIMMDLControl.enDLError     = USIMMDL_NOERROR;

    gstUSIMMDLControl.enDLState     = USIMMDL_STATE_SENDAPDU;

    return;
}
VOS_INT32 USIMM_DLSendDataOneByOne(
    VOS_UINT8                           ucINS,
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                           *pucData)
{
    VOS_UINT32                  i;
    VOS_UINT8                   ucRecData = 0;
    VOS_UINT8                   ucSendData;
    VOS_INT32                   lSCIResult;
    VOS_UINT32                  ulRemainLen = ulDataLen;
    USIMMDL_STATE_ENUM_UINT32   enSendState = USIMMDL_STATE_SENDDATA;

    for(i=0; i<ulDataLen; )
    {
        if(enSendState == USIMMDL_STATE_SENDDATA)
        {
            ucSendData = pucData[i];

            OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1,
                                WUEPS_PID_USIM,
                                WUEPS_PID_USIM,
                                USIMMDL_DRV_USIMMSCI_SND_DATA1);

            lSCIResult = mdrv_sci_send_data(sizeof(VOS_UINT8), &ucSendData);

            OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

            if(USIMM_SCI_SUCCESS != lSCIResult)      /*����һ���ֽ�*/
            {
                USIMM_ERROR_LOG("USIMM_DLSendDataOneByOne: USIMMSCISendData Error");

                return VOS_ERR;
            }

            ulRemainLen = ((ulDataLen - i) - 1);

            if(ulRemainLen == 0x00) /*���ֽڷ��͵����һ���ֽڲ��ý���INS*/
            {
                return VOS_OK;
            }
        }


        OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1,
                            WUEPS_PID_USIM,
                            WUEPS_PID_USIM,
                            USIMMDL_DRV_USIMMSCI_RCV1);

        lSCIResult = mdrv_sci_recv(sizeof(VOS_UINT8), &ucRecData);

        OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

        if(USIMM_SCI_SUCCESS != lSCIResult)  /*���չ����ֽ�*/
        {
            USIMM_ERROR_LOG("USIMM_DLSendDataOneByOne: USIMMSCIReceived Error");

            return VOS_ERR;
        }

        if(ucRecData == ucINS)  /*����ֽں�INS��ȣ�����Ҫ��ʣ���ֽ�һ���Է���*/
        {

            OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1,
                                WUEPS_PID_USIM,
                                WUEPS_PID_USIM,
                                USIMMDL_DRV_USIMMSCI_SND_DATA2);

            lSCIResult = mdrv_sci_send_data(ulRemainLen, &pucData[i+1]);

            OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

            return ((USIMM_SCI_SUCCESS == lSCIResult)?VOS_OK:VOS_ERR);
        }
        else if(ucRecData == 0x60)
        {
            USIMM_WARNING_LOG("USIMM_DLSendDataOneByOne: Receive NULL Byte");

            enSendState = USIMMDL_STATE_WAITACK;
        }
        else
        {
            enSendState = USIMMDL_STATE_SENDDATA;

            i++;
        }
    }

    return VOS_OK;
}


VOS_UINT32 USIMM_DLIdle(
    USIMM_APDU_ST                       *pstAPDUData)
{
    USIMM_ERROR_LOG("USIMM_DLIdle: Usimm DL Run into Error State");

    gstUSIMMDLControl.enDLError = USIMMDL_STATE_ERROR;

    return VOS_ERR;
}


VOS_UINT32 USIMM_DLSendAPDU(
    USIMM_APDU_ST                       *pstAPDUData)
{
    VOS_INT32                           lSCIResult;
    VOS_UINT8                          *pucSendData;

    OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1,
                        WUEPS_PID_USIM,
                        WUEPS_PID_USIM,
                        USIMMDL_DRV_USIMMSCI_SND_DATA3);

    if (VOS_FALSE == gstUSIMMDLControl.bSendRep)
    {
        pucSendData = pstAPDUData->aucAPDU;
    }
    else
    {
        pucSendData = pstAPDUData->aucGetRepAPDU;
    }

    lSCIResult = mdrv_sci_send_data(gstUSIMMDLControl.ulSendDataLen, pucSendData);

    OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

    USIMM_SciDataHook(gstUSIMMDLControl.ulSendDataLen, pucSendData);

    if (USIMM_SCI_SUCCESS == lSCIResult)             /*�������ݷ��ͳɹ�*/
    {
        gstUSIMMDLControl.enDLState = USIMMDL_STATE_WAITACK;
    }
    else                                /*�����ʧ��*/
    {
        USIMM_ERROR_LOG("USIMM_DLSendAPDU: USIMMSCISendData APDU Error");

        gstUSIMMDLControl.enDLError = USIMMDL_SCISENDAPDU_ERROR;
    }

    gstUSIMMDLControl.ulSendAPDUTime++;

    return ((USIMM_SCI_SUCCESS == lSCIResult)?VOS_OK:VOS_ERR);/* [false alarm]: ����Fortify ���� */
}
VOS_UINT32 USIMM_DLSendData(
    USIMM_APDU_ST                       *pstAPDUData)
{
    VOS_INT32                           lSCIResult;
    VOS_UINT8                           aucSendBuf[USIMM_APDU_MAXLEN];

    if(pstAPDUData->ucACK == pstAPDUData->aucAPDU[INS])/*һ���Է���*/
    {
        OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1,
                            WUEPS_PID_USIM,
                            WUEPS_PID_USIM,
                            USIMMDL_DRV_USIMMSCI_SND_DATA4);

        lSCIResult = mdrv_sci_send_data(gstUSIMMDLControl.ulSendDataLen, pstAPDUData->aucSendBuf);

        OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);
    }
    else if(pstAPDUData->ucACK == (VOS_UINT8)(~pstAPDUData->aucAPDU[INS]))/*��һ����*/
    {
        lSCIResult = USIMM_DLSendDataOneByOne(pstAPDUData->aucAPDU[INS],
                                            gstUSIMMDLControl.ulSendDataLen,
                                            pstAPDUData->aucSendBuf);
    }
    else                                                                                    /*ACK���ݴ���*/
    {
        USIMM_ERROR_LOG("USIMM_DLSendData: The INS is Wrong");/*��ӡ����*/

        gstUSIMMDLControl.enDLError = USIMMDL_SCIRECEIVEACK_ERROR;

        return VOS_ERR;
    }

    if ((USIMM_PINCMD_VERIFY == pstAPDUData->aucAPDU[INS])
        || (USIMM_PINCMD_CHANGE == pstAPDUData->aucAPDU[INS])
        || (USIMM_PINCMD_DISABLE == pstAPDUData->aucAPDU[INS])
        || (USIMM_PINCMD_ENABLE == pstAPDUData->aucAPDU[INS])
        || (USIMM_PINCMD_UNBLOCK == pstAPDUData->aucAPDU[INS]))
    {
        /*lint -e534*/
        VOS_MemSet(aucSendBuf, (VOS_CHAR)0xFF, sizeof(aucSendBuf));
        /*lint +e534*/
        USIMM_SciDataHook(gstUSIMMDLControl.ulSendDataLen, aucSendBuf);
    }
    else
    {
        USIMM_SciDataHook(gstUSIMMDLControl.ulSendDataLen, pstAPDUData->aucSendBuf);
    }

    if(USIMM_SCI_SUCCESS == lSCIResult)     /*�������ݷ��ͳɹ�*/
    {
        gstUSIMMDLControl.ulRecDataLen = 1; /*����SW1,����60�ĳ�������SW1,SW2�ֿ�����*/

        gstUSIMMDLControl.enDLState    = USIMMDL_STATE_WAITACK;/*�շ�ת���ʱ����Ҫ�Ƚ���ACK*/
    }
    else                                /*�����ʧ��*/
    {
        USIMM_ERROR_LOG("USIMM_DLSendData: SCI Send Data Error");

        gstUSIMMDLControl.enDLError = USIMMDL_SCISENDLC_ERROR;
    }

    return ((USIMM_SCI_SUCCESS == lSCIResult)?VOS_OK:VOS_ERR);/* [false alarm]: ����Fortify ���� */
}
VOS_UINT32 USIMM_DLReceiveACK(
    USIMM_APDU_ST                       *pstAPDUData)
{
    VOS_UINT8                           aucRecData[2] = {0};
    VOS_INT32                           lSCIesult;
    VOS_UINT8                           ucINS;

    OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1,
                        WUEPS_PID_USIM,
                        WUEPS_PID_USIM,
                        USIMMDL_DRV_USIMMSCI_RCV2);

    lSCIesult = mdrv_sci_recv(1, aucRecData);

    OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

    if(VOS_OK != lSCIesult)/*���մ���*/
    {
        USIMM_ERROR_LOG("USIMM_DLReceiveACK: USIMMSCIReceived ACK Error");

        gstUSIMMDLControl.enDLError = USIMMDL_SCIRECEIVEACK_ERROR;

        return VOS_ERR;
    }

    if(aucRecData[0] == 0x60)   /*����0x60�ֽڣ�״̬�����ٽ��˺�����ACK*/
    {
        USIMM_WARNING_LOG("USIMM_DLReceiveACK:receive 0x60 byte");

        USIMM_SciDataHook(1, aucRecData);    /*���ճɹ�*/

        return VOS_OK;
    }
    else if(((aucRecData[0]&0xF0) == 0x60)||((aucRecData[0]&0xF0) == 0x90))/*����ΪSW1�ֽ�*/
    {
        gstUSIMMDLControl.enDLState    = USIMMDL_STATE_WAITSW;     /*׼������SW2�ֽ�*/

        gstUSIMMDLControl.ulRecDataLen = 1;

        pstAPDUData->ucSW1             = aucRecData[0];
    }
    else                                    /*����ΪACK����*/
    {
        USIMM_SciDataHook(gstUSIMMDLControl.ulRecDataLen, aucRecData);    /*���ճɹ�*/

        pstAPDUData->ucACK = aucRecData[0];

        if (USIMM_CMD_CASE1 == gstUSIMMDLControl.enCMDCase) /*׼������SW */
        {
            if (VOS_FALSE == gstUSIMMDLControl.bSendRep)
            {
                ucINS = pstAPDUData->aucAPDU[INS];
            }
            else
            {
                ucINS = pstAPDUData->aucGetRepAPDU[INS];
            }

            if (pstAPDUData->ucACK == ucINS)
            {
                USIMM_INFO_LOG("USIMM_DLReceiveACK: Case 1 To Case 2 Command, Receive Data");

                gstUSIMMDLControl.enCMDCase    = USIMM_CMD_CASE2;

                gstUSIMMDLControl.ulRecDataLen = USIMM_APDU_MAXLEN;

                pstAPDUData->ulLeValue         = USIMM_APDU_MAXLEN;

                gstUSIMMDLControl.enDLState    = USIMMDL_STATE_WAITDATA;
            }
            else    /*��ǰ�ֽڲ�ʶ�𣬳��Խ���2�ֽ�������ΪSW*/
            {
                USIMM_INFO_LOG("USIMM_DLReceiveACK: Case 1 Command, Receive SW");

                gstUSIMMDLControl.ulRecDataLen = 2; /*׼������SW1,SW2*/

                gstUSIMMDLControl.enDLState    = USIMMDL_STATE_WAITSW;
            }
        }
        else if (USIMM_CMD_CASE2 == gstUSIMMDLControl.enCMDCase)/*��Ҫ������������Le*/
        {
            USIMM_INFO_LOG("USIMM_DLReceiveACK: Case 2 Command, Receive Cmd Data");

            gstUSIMMDLControl.ulRecDataLen = pstAPDUData->ulLeValue;

            gstUSIMMDLControl.enDLState    = USIMMDL_STATE_WAITDATA;
        }
        else if (USIMM_CMD_CASE3 == gstUSIMMDLControl.enCMDCase)/*��Ҫ������������Lc*/
        {
            USIMM_INFO_LOG("USIMM_DLReceiveACK: Case 3 Command, Send Command Data");

            gstUSIMMDLControl.ulSendDataLen  = pstAPDUData->ulLcValue;

            gstUSIMMDLControl.enDLState      = USIMMDL_STATE_SENDDATA;
        }
        else
        {
            USIMM_ERROR_LOG("USIMM_DLReceiveACK: Case 4 Command, Can Not Handler");

            gstUSIMMDLControl.enDLError = USIMMDL_STATE_ERROR;

            return VOS_ERR;
        }
    }

    return VOS_OK;
}

VOS_UINT32 USIMM_DLReceiveData(
    USIMM_APDU_ST                       *pstAPDUData)
{
    VOS_INT32                           lSCIResult;
    VOS_UINT8                           aucRecData[256] = {0};

    OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1,
                        WUEPS_PID_USIM,
                        WUEPS_PID_USIM,
                        USIMMDL_DRV_USIMMSCI_RCV3);

    lSCIResult = mdrv_sci_recv(gstUSIMMDLControl.ulRecDataLen, aucRecData);

    OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

    if(USIMM_SCI_SUCCESS == lSCIResult)                           /*���ճɹ�׼������SW�ֽ�*/
    {
        USIMM_SciDataHook(gstUSIMMDLControl.ulRecDataLen, aucRecData);

        if((pstAPDUData->ulRecDataLen+gstUSIMMDLControl.ulRecDataLen) > sizeof(pstAPDUData->aucRecvBuf))   /*��λ�ȡ�������Ѿ����������ش��󣬲�֧�ָ����*/
        {
            USIMM_WARNING_LOG("USIMM_GetResponse_APDU: The Receive Data Too long to the aucRecvBuf");
        }
        else
        {
            /*lint -e534*/
            VOS_MemCpy(pstAPDUData->aucRecvBuf+pstAPDUData->ulRecDataLen, aucRecData, gstUSIMMDLControl.ulRecDataLen);   /*��λ�ȡ��������Ҫ�����ھֲ�������*/
            /*lint +e534*/

            pstAPDUData->ulRecDataLen += gstUSIMMDLControl.ulRecDataLen;                         /*��¼�ܹ���������ݳ���*/
        }
#if (VOS_WIN32 == VOS_OS_VER)
        gstUSIMMDLControl.enDLState    = USIMMDL_STATE_WAITSW;

        gstUSIMMDLControl.ulRecDataLen = 2;         /*����ȫ����SW1,SW2*/
#else
         /*������һ�������ֽڣ����п��ܻظ�����60,������SW*/
        gstUSIMMDLControl.enDLState    = USIMMDL_STATE_WAITACK;
        gstUSIMMDLControl.ulRecDataLen = 1;
#endif
    }
    else                                            /*����ʧ��*/
    {
        USIMM_ERROR_LOG("USIMM_DLReceiveData: USIMMSCIReceived Data Error");

        gstUSIMMDLControl.enDLError = USIMMDL_SCIRECEIVELE_ERROR;
    }

    return ((USIMM_SCI_SUCCESS == lSCIResult)?VOS_OK:VOS_ERR);/* [false alarm]: ����Fortify ���� */
}


VOS_UINT32 USIMM_DLReceiveSW(
    USIMM_APDU_ST                       *pstAPDUData)
{
    VOS_INT32                           lSCIResult;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucRecData[2] = {0};

    OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1,
                        WUEPS_PID_USIM,
                        WUEPS_PID_USIM,
                        USIMMDL_DRV_USIMMSCI_RCV4);

    lSCIResult = mdrv_sci_recv(gstUSIMMDLControl.ulRecDataLen, aucRecData);

    OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

    if(USIMM_SCI_SUCCESS == lSCIResult)                      /*���ճɹ�*/
    {
        if (1 == gstUSIMMDLControl.ulRecDataLen) /*��ǰ���յ�SW2*/
        {
            pstAPDUData->ucSW2 = aucRecData[0];
        }
        else
        {
            pstAPDUData->ucSW1 = aucRecData[0];    /*����SW����*/

            pstAPDUData->ucSW2 = aucRecData[1];
        }

        if (1 == gstUSIMMDLControl.ulSendAPDUTime)   /*�����һ�η��ͷ���SW����*/
        {
            pstAPDUData->ucApduSW1 = pstAPDUData->ucSW1;

            pstAPDUData->ucApduSW2 = pstAPDUData->ucSW2;
        }

        gstUSIMMDLControl.enDLError = USIMMDL_NOERROR;

        USIMM_SciDataHook(2, &pstAPDUData->ucSW1);
    }
    else                                        /*����ʧ��*/
    {
        USIMM_ERROR_LOG("USIMM_DLReceiveSW: USIMMSCIReceived SW Error");

        gstUSIMMDLControl.enDLError = USIMMDL_SCIRECEIVESW_ERROR;

        return VOS_ERR;
    }

    ulResult = USIMM_CheckSW(pstAPDUData->aucAPDU[INS], pstAPDUData->ucSW1, pstAPDUData->ucSW2);

    if (USIMM_SW_P3_ERROR == ulResult)   /*����P3�ֽڴ��󣬸ı�֮�����½����µ�DL���̷���*/
    {
        USIMM_WARNING_LOG("USIMM_DLReceiveSW:Receive 6C or 67 Byte,Resend APDU Command");

        gstUSIMMDLControl.ulP3ErrorTime++;

        if (USIMM_P3ERROR_MAXTIME <= gstUSIMMDLControl.ulP3ErrorTime)
        {
            USIMM_WARNING_LOG("USIMM_DLReceiveSW:Receive 6C or 67 Byte Too Many");

            gstUSIMMDLControl.enDLState = USIMMDL_STATE_IDLE;

            return VOS_OK;
        }

        if ((VOS_TRUE == gstUSIMMDLControl.bSendRep)&&(CMD_INS_GET_RESPONSE == pstAPDUData->aucGetRepAPDU[INS]))
        {
            if (pstAPDUData->ucSW2 == pstAPDUData->aucGetRepAPDU[P3])
            {
                USIMM_WARNING_LOG("USIMM_DLReceiveSW:Receive 6C or 67 Byte Again");

                gstUSIMMDLControl.enDLState = USIMMDL_STATE_IDLE;

                return VOS_OK;
            }
            else
            {
                pstAPDUData->ulLeValue  = pstAPDUData->ucSW2;/*���Ķ�Ӧ��Le�ĳ���*/

                pstAPDUData->aucGetRepAPDU[P3]= pstAPDUData->ucSW2;/*����P3�ֽڵĴ���*/
            }
        }
        else
        {
            if (CMD_INS_STATUS == pstAPDUData->aucAPDU[INS])/*STATUS������Ҫ���¶�Ӧ��ȫ�ֱ�������*/
            {
                pstAPDUData->ulLeValue  = pstAPDUData->ucSW2;/*���Ķ�Ӧ��Le�ĳ���*/
            }
            else
            {
                if (pstAPDUData->ulLcValue != 0)
                {
                    pstAPDUData->ulLcValue  = pstAPDUData->ucSW2;/*���Ķ�Ӧ��Lc�ĳ���*/
                }
                else
                {
                    pstAPDUData->ulLeValue  = pstAPDUData->ucSW2;/*���Ķ�Ӧ��Le�ĳ���*/
                }
            }

            pstAPDUData->aucAPDU[P3]= pstAPDUData->ucSW2;/*����P3�ֽڵĴ���*/
        }

        USIMM_DLStateStar(pstAPDUData);              /*���¿�ʼDL��ĳ�ʼ��*/

        return VOS_OK;
    }

    if (USIMM_SW_OK_WITH_RESOPNSE == ulResult)
    {
        gstUSIMMDLControl.enDLState = USIMMDL_STATE_GETRESPONSE;

        return VOS_OK;
    }

    /* �ο�7816-4 8.6.1 */
    if ((USIMM_SW_WARNING == ulResult)&&(VOS_FALSE == gstUSIMMDLControl.bSendRep))
    {
        gstUSIMMDLControl.enDLState = USIMMDL_STATE_GETRESPONSE;
    }
    else
    {
        gstUSIMMDLControl.enDLState = USIMMDL_STATE_IDLE;
    }

    return VOS_OK;
}
VOS_UINT32 USIMM_DLGetResponse(
    USIMM_APDU_ST                       *pstAPDUData)
{
    if (USIMM_PHYCARD_TYPE_ICC == USIMM_CCB_GetCardType())
    {
        pstAPDUData->aucGetRepAPDU[CLA]   = gstUSIMMBaseInfo.ucCLA;
    }
    else
    {
        pstAPDUData->aucGetRepAPDU[CLA]   = gstUSIMMBaseInfo.ucCLA|(pstAPDUData->aucAPDU[CLA]&0x6F);
    }

    pstAPDUData->aucGetRepAPDU[INS]   = CMD_INS_GET_RESPONSE;

    pstAPDUData->aucGetRepAPDU[P1]    = 0x00;

    pstAPDUData->aucGetRepAPDU[P2]    = 0x00;

    if((0x61 == pstAPDUData->ucSW1)||(0x9F == pstAPDUData->ucSW1))
    {
        pstAPDUData->aucGetRepAPDU[P3] = pstAPDUData->ucSW2; /*������һ������״̬��61XX��SW2��ֵ*/

        if(0x00 == pstAPDUData->aucGetRepAPDU[P3])
        {
            pstAPDUData->ulLeValue  = 0x100;
        }
        else
        {
            pstAPDUData->ulLeValue  = pstAPDUData->aucGetRepAPDU[P3];
        }
    }
    else
    {
        pstAPDUData->aucGetRepAPDU[P3]= 0x00;             /*�����62����63*/

        pstAPDUData->ulLeValue  = 0x00;
    }

    pstAPDUData->ulLcValue      = 0x00;

    pstAPDUData->ucSW1          = 0x00;

    pstAPDUData->ucSW2          = 0x00;

    pstAPDUData->ucACK          = 0x00;

    gstUSIMMDLControl.bSendRep  = VOS_TRUE;

    USIMM_DLStateStar(pstAPDUData);

    return VOS_OK;
}


static USIMMDL_FUNC_STATUS gastUSIMMDLProc[] =
{
    {USIMMDL_STATE_IDLE,        USIMM_DLIdle},
    {USIMMDL_STATE_SENDAPDU,    USIMM_DLSendAPDU},
    {USIMMDL_STATE_SENDDATA,    USIMM_DLSendData},
    {USIMMDL_STATE_WAITACK,     USIMM_DLReceiveACK},
    {USIMMDL_STATE_WAITDATA,    USIMM_DLReceiveData},
    {USIMMDL_STATE_WAITSW,      USIMM_DLReceiveSW},
    {USIMMDL_STATE_GETRESPONSE, USIMM_DLGetResponse}
};

VOS_UINT32 USIMM_T0DLHandle(USIMM_APDU_ST* pstAPDUData)
{
    VOS_UINT32  ulResult = 0;           /* ������� */
    VOS_UINT32  i;

    if (USIMMDL_STATE_IDLE != gstUSIMMDLControl.enDLState)
    {
        USIMM_WARNING_LOG("USIMM_T0DLHandle: DL State is Wrong");/* ��ӡ���� */
    }

    USIMM_ExcLogDataBK();

    pstAPDUData->ulRecDataLen  = 0;     /*���ڶ�ν������ݣ����DL�㿪ʼ��ʱ���������*/

    /*lint -e534*/
    VOS_MemSet(&gstUSIMMDLControl, 0, sizeof(gstUSIMMDLControl));   /* ��ʼ����ǰ״̬ */

    VOS_MemSet(pstAPDUData->aucGetRepAPDU, 0, USIMM_APDU_HEADLEN);
    /*lint +e534*/

    USIMM_DLStateStar(pstAPDUData);

    if(USIMM_CMD_CASE4 == gstUSIMMDLControl.enCMDCase)
    {
        /* T=0Э�飬û��case4���������ͨ��case3+case2ʵ�ֵ�case4 */
        gstUSIMMDLControl.enCMDCase = USIMM_CMD_CASE3;

        pstAPDUData->ulLeValue = 0;
    }

    for(i=0; i<(sizeof(gastUSIMMDLProc)/sizeof(USIMMDL_FUNC_STATUS)); i++)
    {
        if(gstUSIMMDLControl.enDLState == gastUSIMMDLProc[i].enStateId)
        {
            ulResult = gastUSIMMDLProc[i].pProcFun(pstAPDUData);

            /*�����ִ���������DL���̺��˳�*/
            if((VOS_OK != ulResult)||(USIMMDL_STATE_IDLE == gstUSIMMDLControl.enDLState))
            {
                break;
            }

            i = 0;
        }
    }

    gstUSIMMDLControl.enDLState = USIMMDL_STATE_IDLE;

    /*���ݴ�����Ϣ���غ����������*/
    if(USIMMDL_NOERROR == gstUSIMMDLControl.enDLError)
    {
        USIMM_INFO_LOG("USIMM_T0DLHandle:DL Complete the Step Right");

        ulResult = USIMM_DL_SUCESS;

        USIMM_ExcLogDataRE();
    }
    else if(gstUSIMMDLControl.enDLError > USIMMDL_SCISENDLC_ERROR)
    {
        USIMM_ERROR_LOG("USIMM_T0DLHandle:DL Complete the Step With Receive Data Error");

        ulResult = USIMM_DL_RECEIVE_ERROR;
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_T0DLHandle:DL Complete the Step With Send Data Error");

        ulResult = USIMM_DL_SEND_ERROR;
    }

    gstUSIMMDLControl.enDLState = USIMMDL_STATE_IDLE;   /*DL���̽���*/

    return ulResult;
}


VOS_UINT32 USIMM_DLHandle(
    USIMM_APDU_ST                       *pstAPDUData)
{
    VOS_UINT32                          ulResult;           /* ������� */

    if (USIMM_DL_T_MODE_T0 == g_enUSIMMTMode)
    {
        /* ��ǰ֧��T=0 */
        ulResult = USIMM_T0DLHandle(pstAPDUData);
    }
    else if (USIMM_DL_T_MODE_T1 == g_enUSIMMTMode)
    {
        /* ��ǰ֧��T=1 */
        ulResult = USIMM_T1DLHandle(pstAPDUData);
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_DLHandle: USIMM T mode is BUTT");

        ulResult = VOS_ERR;
    }

    return ulResult;
}
VOS_UINT32 USIMM_DLCglaReceiveSW(
    USIMM_APDU_ST                       *pstAPDUData)
{
    VOS_INT32                           lSCIResult;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucRecData[2] = {0};

    OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1,
                        WUEPS_PID_USIM,
                        WUEPS_PID_USIM,
                        USIMMDL_DRV_USIMMSCI_RCV4);

    lSCIResult = mdrv_sci_recv(gstUSIMMDLControl.ulRecDataLen, aucRecData);

    OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

    if(USIMM_SCI_SUCCESS == lSCIResult)                      /*���ճɹ�*/
    {
        if(1 == gstUSIMMDLControl.ulRecDataLen) /*��ǰ���յ�SW2*/
        {
            pstAPDUData->ucSW2 = aucRecData[0];
        }
        else
        {
            pstAPDUData->ucSW1 = aucRecData[0];    /*����SW����*/

            pstAPDUData->ucSW2 = aucRecData[1];
        }

        gstUSIMMDLControl.enDLError = USIMMDL_NOERROR;

        USIMM_SciDataHook(2, &pstAPDUData->ucSW1);
    }
    else                                        /*����ʧ��*/
    {
        USIMM_ERROR_LOG("USIMM_DLCglaReceiveSW: USIMMSCIReceived SW Error");

        gstUSIMMDLControl.enDLError = USIMMDL_SCIRECEIVESW_ERROR;

        return VOS_ERR;
    }

    ulResult = USIMM_CheckSW(pstAPDUData->aucAPDU[INS], pstAPDUData->ucSW1, pstAPDUData->ucSW2);

    /* �����һ�η��ͷ���SW���ݺ�Resultֵ */
    if (1 == gstUSIMMDLControl.ulSendAPDUTime)
    {
        pstAPDUData->ucApduSW1 = pstAPDUData->ucSW1;
        pstAPDUData->ucApduSW2 = pstAPDUData->ucSW2;
        pstAPDUData->ucResult  = (VOS_UINT8)ulResult;
    }

    /* ���Ʋ����з���INS=0x09����Ҫֱ�ӷ��� */
    if((USIMM_SW_P3_ERROR == ulResult)&&(0x09 != pstAPDUData->aucAPDU[INS]))   /*����P3�ֽڴ��󣬸ı�֮�����½����µ�DL���̷���*/
    {
        USIMM_WARNING_LOG("USIMM_DLCglaReceiveSW:Receive 6C or 67 Byte,Resend APDU Command");

        gstUSIMMDLControl.ulP3ErrorTime ++;

        if (USIMM_P3ERROR_MAXTIME <= gstUSIMMDLControl.ulP3ErrorTime)
        {
            USIMM_WARNING_LOG("USIMM_DLCglaReceiveSW:Receive 6C or 67 Byte Too Many");

            gstUSIMMDLControl.enDLState = USIMMDL_STATE_IDLE;

            return VOS_OK;
        }

        if ((VOS_TRUE == gstUSIMMDLControl.bSendRep)&&(CMD_INS_GET_RESPONSE == pstAPDUData->aucGetRepAPDU[INS]))
        {
            if (pstAPDUData->ucSW2 == pstAPDUData->aucGetRepAPDU[P3])
            {
                USIMM_WARNING_LOG("USIMM_DLCglaReceiveSW:Receive 6C or 67 Byte Again");

                gstUSIMMDLControl.enDLState = USIMMDL_STATE_IDLE;

                return VOS_OK;
            }
            else
            {
                pstAPDUData->ulLeValue  = pstAPDUData->ucSW2;/*���Ķ�Ӧ��Le�ĳ���*/

                pstAPDUData->aucGetRepAPDU[P3]= pstAPDUData->ucSW2;/*����P3�ֽڵĴ���*/
            }
        }
        else
        {
            if (pstAPDUData->ucSW2 == pstAPDUData->aucAPDU[P3])
            {
                USIMM_WARNING_LOG("USIMM_DLCglaReceiveSW:Receive 6C or 67 Byte Again");

                gstUSIMMDLControl.enDLState = USIMMDL_STATE_IDLE;

                return VOS_OK;
            }

            if (CMD_INS_STATUS == pstAPDUData->aucAPDU[INS])/*STATUS������Ҫ���¶�Ӧ��ȫ�ֱ�������*/
            {
                pstAPDUData->ulLeValue  = pstAPDUData->ucSW2;/*���Ķ�Ӧ��Le�ĳ���*/
            }
            else
            {
                if (pstAPDUData->ulLcValue != 0)
                {
                    pstAPDUData->ulLcValue  = pstAPDUData->ucSW2;/*���Ķ�Ӧ��Lc�ĳ���*/
                }
                else
                {
                    pstAPDUData->ulLeValue  = pstAPDUData->ucSW2;/*���Ķ�Ӧ��Le�ĳ���*/
                }
            }

            pstAPDUData->aucAPDU[P3]= pstAPDUData->ucSW2;/*����P3�ֽڵĴ���*/
        }

        USIMM_DLStateStar(pstAPDUData);              /*���¿�ʼDL��ĳ�ʼ��*/

        return VOS_OK;
    }

    if(USIMM_SW_OK_WITH_RESOPNSE == ulResult)
    {
        gstUSIMMDLControl.enDLState = USIMMDL_STATE_GETRESPONSE;

        return VOS_OK;
    }

    gstUSIMMDLControl.enDLState = USIMMDL_STATE_IDLE;

    /* �ο�7816-4 8.6.1 */
    if ((USIMM_SW_WARNING == ulResult)
    &&(VOS_FALSE == gstUSIMMDLControl.bSendRep)
	&&(VOS_TRUE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulCglaGetRsp))
    {
        gstUSIMMDLControl.enDLState = USIMMDL_STATE_GETRESPONSE;
    }

    return VOS_OK;
}


VOS_UINT32 USIMM_DLCglaGetResponse(
    USIMM_APDU_ST                       *pstAPDUData)
{
    VOS_UINT32                      ulTempLen;

    if (USIMM_SIM_CLA != pstAPDUData->aucAPDU[CLA])
    {
        /* ����102.221Э��,GET RESPONSE��INS�ֶ�֧��'0X' or '4X' or '6X' */
        pstAPDUData->aucGetRepAPDU[CLA] = pstAPDUData->aucAPDU[CLA] & 0x6F;
    }
    else
    {
        pstAPDUData->aucGetRepAPDU[CLA] = USIMM_SIM_CLA;
    }

    pstAPDUData->aucGetRepAPDU[INS]   = CMD_INS_GET_RESPONSE;

    pstAPDUData->aucGetRepAPDU[P1]    = 0x00;

    pstAPDUData->aucGetRepAPDU[P2]    = 0x00;

    if((0x61 == pstAPDUData->ucSW1)||(0x9F == pstAPDUData->ucSW1))
    {
        pstAPDUData->aucGetRepAPDU[P3] = pstAPDUData->ucSW2; /*������һ������״̬��61XX��SW2��ֵ*/

        if (0x00 == pstAPDUData->aucGetRepAPDU[P3])
        {
            ulTempLen = 0x100;
        }
        else
        {
            ulTempLen = pstAPDUData->aucGetRepAPDU[P3];
        }

        if ((pstAPDUData->ulRecDataLen + ulTempLen) > USIMM_APDU_MAXLEN)
        {
            gstUSIMMDLControl.enDLState = USIMMDL_STATE_IDLE;

            return VOS_OK;
        }

        pstAPDUData->ulLeValue  = ulTempLen;
    }
    else
    {
        pstAPDUData->aucGetRepAPDU[P3]= 0x00;             /*�����62����63*/

        pstAPDUData->ulLeValue  = 0x00;
    }

    pstAPDUData->ulLcValue      = 0x00;

    pstAPDUData->ucSW1          = 0x00;

    pstAPDUData->ucSW2          = 0x00;

    pstAPDUData->ucACK          = 0x00;

    gstUSIMMDLControl.bSendRep  = VOS_TRUE;

    USIMM_DLStateStar(pstAPDUData);

    return VOS_OK;
}
static USIMMDL_FUNC_STATUS gastUSIMMCglaDLProc[] =
{
    {USIMMDL_STATE_IDLE,        USIMM_DLIdle},
    {USIMMDL_STATE_SENDAPDU,    USIMM_DLSendAPDU},
    {USIMMDL_STATE_SENDDATA,    USIMM_DLSendData},
    {USIMMDL_STATE_WAITACK,     USIMM_DLReceiveACK},
    {USIMMDL_STATE_WAITDATA,    USIMM_DLReceiveData},
    {USIMMDL_STATE_WAITSW,      USIMM_DLCglaReceiveSW},
    {USIMMDL_STATE_GETRESPONSE, USIMM_DLCglaGetResponse}
};

VOS_UINT32 USIMM_T0CglaDLHandle(
    USIMM_APDU_ST                       *pstAPDUData)
{
    VOS_UINT32  ulResult = 0;           /* ������� */
    VOS_UINT32  i;

    if(USIMMDL_STATE_IDLE != gstUSIMMDLControl.enDLState)
    {
        USIMM_WARNING_LOG("USIMM_T0CglaDLHandle: DL State is Wrong");/* ��ӡ���� */

        gstUSIMMDLControl.enDLState = USIMMDL_STATE_IDLE;/* ��ʼ����ǰ״̬ */
    }

    pstAPDUData->ulRecDataLen  = 0;     /*���ڶ�ν������ݣ����DL�㿪ʼ��ʱ���������*/

    /*lint -e534*/
    VOS_MemSet(&gstUSIMMDLControl, 0, sizeof(gstUSIMMDLControl));   /* ��ʼ����ǰ״̬ */

    VOS_MemSet(pstAPDUData->aucGetRepAPDU, 0, USIMM_APDU_HEADLEN);
    /*lint +e534*/

    USIMM_DLStateStar(pstAPDUData);

    if(USIMM_CMD_CASE4 == gstUSIMMDLControl.enCMDCase)
    {
        /* T=0Э�飬û��case4���������ͨ��case3+case2ʵ�ֵ�case4 */
        gstUSIMMDLControl.enCMDCase = USIMM_CMD_CASE3;

        pstAPDUData->ulLeValue = 0;
    }

    for(i=0; i<(sizeof(gastUSIMMCglaDLProc)/sizeof(USIMMDL_FUNC_STATUS)); i++)
    {
        if(gstUSIMMDLControl.enDLState == gastUSIMMCglaDLProc[i].enStateId)
        {
            ulResult = gastUSIMMCglaDLProc[i].pProcFun(pstAPDUData);

            /*�����ִ���������DL���̺��˳�*/
            if((VOS_OK != ulResult)||(USIMMDL_STATE_IDLE == gstUSIMMDLControl.enDLState))
            {
                break;
            }

            i = 0;
        }
    }

    gstUSIMMDLControl.enDLState = USIMMDL_STATE_IDLE;

    /*���ݴ�����Ϣ���غ����������*/
    if(USIMMDL_NOERROR == gstUSIMMDLControl.enDLError)
    {
        USIMM_INFO_LOG("USIMM_T0CglaDLHandle:DL Complete the Step Right");

        ulResult = USIMM_DL_SUCESS;
    }
    else if(gstUSIMMDLControl.enDLError > USIMMDL_SCISENDLC_ERROR)
    {
        USIMM_ERROR_LOG("USIMM_T0CglaDLHandle:DL Complete the Step With Receive Data Error");

        ulResult = USIMM_DL_RECEIVE_ERROR;
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_T0CglaDLHandle:DL Complete the Step With Send Data Error");

        ulResult = USIMM_DL_SEND_ERROR;
    }

    gstUSIMMDLControl.enDLState = USIMMDL_STATE_IDLE;   /*DL���̽���*/

    return ulResult;
}
VOS_UINT32 USIMM_CglaDLHandle(
    USIMM_APDU_ST                       *pstAPDUData)
{

    VOS_UINT32  ulResult = 0;           /* ������� */

    if(USIMM_DL_T_MODE_T0 == g_enUSIMMTMode)
    {
        /* ��ǰ֧��T=0 */
        ulResult = USIMM_T0CglaDLHandle(pstAPDUData);
    }
    else if(USIMM_DL_T_MODE_T1 == g_enUSIMMTMode)
    {
        /* ��ǰ֧��T=1 */
        ulResult = USIMM_T1DLHandle(pstAPDUData);
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_CglaDLHandle: USIMM T mode is BUTT");

        ulResult = VOS_ERR;
    }

    return ulResult;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#else

#include "usimmdl.h"
#include "usimmt1dl.h"
#include "usimmbase.h"
#include "v_iddef.h"
#include "usimmglobal.h"
#include "msp_diag_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_USIMM_DLMODULE_C
/*lint +e767*/


VOS_VOID USIMM_DLJudgeCmdCase(USIMM_APDU_ST* pstAPDUData)
{
        /* �жϵ�ǰ�Ŀ��������� */
    if(0 == pstAPDUData->ulLcValue)
    {
        if(0 == pstAPDUData->ulLeValue) /* Lc,Le�������� */
        {
            gstUSIMMDLControl.enCMDCase = USIMM_CMD_CASE1;
        }
        else                            /* Lc������,Le���� */
        {
            gstUSIMMDLControl.enCMDCase = USIMM_CMD_CASE2;
        }
    }
    else
    {
        if(0 == pstAPDUData->ulLeValue) /* Lc����,Le������ */
        {
            gstUSIMMDLControl.enCMDCase = USIMM_CMD_CASE3;
        }
        else                            /* Lc,Le������ */
        {
            gstUSIMMDLControl.enCMDCase = USIMM_CMD_CASE4;
        }
    }

    return;
}
VOS_UINT32 USIMM_DLResetCard(VOS_UINT32 ulResetType, VOS_INT32 *plVoltageSwitchRst)
{
    VOS_INT32                           lSCIResult = VOS_ERR;
    VOS_UINT32                          i;
    NV_USIMM_T1_CTRL_PARA_STRU          stT1CtrlPara;

    if (USIMM_RESET_CARD == ulResetType)
    {
        OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_RST);
        /*lint -e534*/
        mdrv_sci_reset(COLD_RESET);
        /*lint +e534*/
        OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

        if(USIMM_DL_T_MODE_T1 == g_enUSIMMTMode)
        {
            /* ���±��� */
            if(VOS_OK != USIMM_T1DLUpdateParaByATR(g_stUSIMMT1Para.enErrDetectMode, g_stUSIMMT1Para.ulIFSC, g_stUSIMMT1Para.ulIFSD))
            {
                USIMM_ERROR_LOG("USIMM_DLResetCard: USIMM_T1DLUpdateParaByATR fail!");
                return VOS_ERR;
            }

            /*lint -e534*/
            VOS_MemSet(&stT1CtrlPara, 0, sizeof(stT1CtrlPara));
            /*lint +e534*/

            /* ��NV�� */
            if(VOS_OK != NV_Read(en_NV_Item_Usimm_T1_Ctrl_PARA, &stT1CtrlPara, sizeof(stT1CtrlPara)))
            {
                /* ��ӡ���� */
                USIMM_ERROR_LOG("USIMM_DecideTMode:USIM Read T1 PARA NV error");

                /* NV��ȡʧ�ܣ���ʽ��ֵΪT0 */
                stT1CtrlPara.enTMode = USIMM_DL_T_MODE_T0;
            }

            /* ����IFS����,���߿�UE�������� */
            if(VOS_OK != USIMM_T1SendIFSD_APDU((VOS_UINT8)stT1CtrlPara.ulDefaultIFSD))
            {
                USIMM_ERROR_LOG("USIMM_DLResetCard: USIMM_T1SendIFSD_APDU fail!");
                return VOS_ERR;
            }

            OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_T1_PRTCL_SWITCH_1);
            if(VOS_OK != mdrv_sci_switch_protocol((PROTOCOL_MODE_E)g_enUSIMMTMode))
            {
                /* ��ά�ɲ���Ϣͳ�� */
                g_stT1StatisticInfo.ulProtocolSwitchFailCnt++;

                USIMM_WARNING_LOG("USIMM_DLResetCard:SET T MODE FAILED");
            }
            OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);
        }
    }
    else
    {
        OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_CLASS_SWITCH);
        lSCIResult = mdrv_sci_switch_class();
        OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

        *plVoltageSwitchRst = lSCIResult;

        if (USIMM_SCI_SUCCESS == lSCIResult)      /*��ѹ�л��ɹ�����Ҫ�ӳ�*/
        {
            USIMM_NORMAL_LOG("USIMM_DLResetCard: SIM Card Change the Voltage Successful");
        }
        else if (USIMM_SCI_NONEED_CHANGEVCC == lSCIResult)
        {
            USIMM_NORMAL_LOG("USIMM_DLResetCard: Card needn't Change the Voltage");
        }
        else                     /*��ѹ�л�ʧ�ܰ����޿�����*/
        {
            gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType = USIMM_CARD_NOCARD;

            return VOS_ERR;
        }
    }

    for (i = 0; i < USIMM_GET_SCISTATUS_MAX; i++)        /*ѭ���жϵ�ǰ�Ŀ���λ���*/
    {
        OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_GET_CARD_STAU);
        lSCIResult = mdrv_sci_get_cardstatus(); /*�����λ�ɹ��򷵻سɹ�*/
        OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

        if (SCI_CARD_STATE_BUSY != lSCIResult)
        {
            break;
        }
#if (VOS_OS_VER != VOS_WIN32)       /* PC Stub */
        HPA_USIMLowPowerLock(WUEPS_PID_USIM);
#endif
        /*lint -e534*/
        VOS_TaskDelay(20);     /*�ȴ�����������ATR��PPS����*/
        /*lint +e534*/

#if (VOS_OS_VER != VOS_WIN32)       /* PC Stub */
        HPA_USIMLowPowerUnLock(WUEPS_PID_USIM);
#endif
    }

    if (SCI_CARD_STATE_NOCARD == lSCIResult)
    {
        USIMM_ERROR_LOG("USIMM_DLResetCard: USIMM Could Not Find Any SIM Card!");

        gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType = USIMM_CARD_NOCARD;

        mdrv_sci_save_recorddata();

        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_VOID USIMM_SciDataHook(VOS_UINT32 ulLength, VOS_UINT8 *pucData)
{
    MsgBlock                           *pMsg;

#ifdef USIMM_DEBUG_PEINT
    VOS_UINT32   i;

    /* lint -e534 */
    vos_printf("\r\nSciDataHook Length is :%d\r\n",ulLength);
    /* lint +e534 */

    for(i = 0;i<ulLength; i++)
    {
        /* lint -e534 */
        vos_printf("0x%02x,",pucData[i]);
        /* lint +e534 */
    }

    /* lint -e534 */
    vos_printf("\r\nend\n");
    /* lint +e534 */
#endif

    USIMM_LogDataSave(pucData, (VOS_UINT8)ulLength);

    USIMM_ExcLogDataSave(pucData, (VOS_UINT8)ulLength);

    pMsg = (MsgBlock*)VOS_AllocMsg(WUEPS_PID_USIM, ulLength);

    if(VOS_NULL_PTR == pMsg)
    {
        USIMM_WARNING_LOG("USIMM_SciDataHook:WARNING:alloc msg failed\n");

        return;
    }

    pMsg->ulReceiverPid   = WUEPS_PID_USIM;

    pMsg->ulLength        = ulLength;

    /*lint -e534*/
    VOS_MemCpy(pMsg->aucValue, pucData, ulLength);
    /*lint +e534*/

    DIAG_TraceReport((VOS_VOID *)(pMsg));

    /*lint -e534*/
    VOS_FreeMsg(WUEPS_PID_USIM, pMsg);
    /*lint +e534*/

    return;
}


VOS_VOID USIMM_DLStateStar(USIMM_APDU_ST* pstAPDUData)
{
    USIMM_DLJudgeCmdCase(pstAPDUData);

    /*��������ͷ����ʼ�����ֵ*/
    gstUSIMMDLControl.ulSendDataLen = sizeof(pstAPDUData->aucAPDU);

    gstUSIMMDLControl.ulRecDataLen  = sizeof(pstAPDUData->ucACK);

    gstUSIMMDLControl.enDLError     = USIMMDL_NOERROR;

    gstUSIMMDLControl.enDLState     = USIMMDL_STATE_SENDAPDU;

    return;
}
VOS_INT32 USIMM_DLSendDataOneByOne(VOS_UINT8 ucINS,VOS_UINT32 ulDataLen, VOS_UINT8* pucData)
{
    VOS_UINT32                  i;
    VOS_UINT8                   ucRecData = {0};
    VOS_UINT8                   ucSendData;
    VOS_INT32                   lSCIResult;
    VOS_UINT32                  ulRemainLen = ulDataLen;
    USIMMDL_STATE_ENUM_UINT32   enSendState = USIMMDL_STATE_SENDDATA;

    for(i=0; i<ulDataLen; )
    {
        if(enSendState == USIMMDL_STATE_SENDDATA)
        {
            ucSendData = pucData[i];

            OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_SND_DATA1);
            lSCIResult = mdrv_sci_send_data(sizeof(VOS_UINT8), &ucSendData);
            OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

            if(USIMM_SCI_SUCCESS != lSCIResult)      /*����һ���ֽ�*/
            {
                USIMM_ERROR_LOG("USIMM_DLSendDataOneByOne: USIMMSCISendData Error");

                return VOS_ERR;
            }

            ulRemainLen = ((ulDataLen - i) - 1);

            if(ulRemainLen == 0x00) /*���ֽڷ��͵����һ���ֽڲ��ý���INS*/
            {
                return VOS_OK;
            }
        }


        OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_RCV1);
        lSCIResult = mdrv_sci_recv(sizeof(VOS_UINT8), &ucRecData);
        OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

        if(USIMM_SCI_SUCCESS != lSCIResult)  /*���չ����ֽ�*/
        {
            USIMM_ERROR_LOG("USIMM_DLSendDataOneByOne: USIMMSCIReceived Error");

            return VOS_ERR;
        }

        if(ucRecData == ucINS)  /*����ֽں�INS��ȣ�����Ҫ��ʣ���ֽ�һ���Է���*/
        {

            OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_SND_DATA2);
            lSCIResult = mdrv_sci_send_data(ulRemainLen, &pucData[i+1]);
            OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

            return ((USIMM_SCI_SUCCESS == lSCIResult)?VOS_OK:VOS_ERR);
        }
        else if(ucRecData == 0x60)
        {
            USIMM_WARNING_LOG("USIMM_DLSendDataOneByOne: Receive NULL Byte");

            enSendState = USIMMDL_STATE_WAITACK;
        }
        else
        {
            enSendState = USIMMDL_STATE_SENDDATA;

            i++;
        }
    }

    return VOS_OK;
}


VOS_UINT32 USIMM_DLIdle(USIMM_APDU_ST *pstAPDUData)
{
    USIMM_ERROR_LOG("USIMM_DLIdle: Usimm DL Run into Error State");

    gstUSIMMDLControl.enDLError = USIMMDL_STATE_ERROR;

    return VOS_ERR;
}


VOS_UINT32 USIMM_DLSendAPDU(USIMM_APDU_ST *pstAPDUData)
{
    VOS_INT32                           lSCIResult;
    VOS_UINT8                          *pucSendData;

    OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_SND_DATA3);

    if (VOS_FALSE == gstUSIMMDLControl.bSendRep)
    {
        pucSendData = pstAPDUData->aucAPDU;
    }
    else
    {
        pucSendData = pstAPDUData->aucGetRepAPDU;
    }

    lSCIResult = mdrv_sci_send_data(gstUSIMMDLControl.ulSendDataLen, pucSendData);

    OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

    USIMM_SciDataHook(gstUSIMMDLControl.ulSendDataLen, pucSendData);

    if (USIMM_SCI_SUCCESS == lSCIResult)             /*�������ݷ��ͳɹ�*/
    {
        gstUSIMMDLControl.enDLState = USIMMDL_STATE_WAITACK;
    }
    else                                /*�����ʧ��*/
    {
        USIMM_ERROR_LOG("USIMM_DLSendAPDU: USIMMSCISendData APDU Error");

        gstUSIMMDLControl.enDLError = USIMMDL_SCISENDAPDU_ERROR;
    }

    gstUSIMMDLControl.ulSendAPDUTime++;

    return ((USIMM_SCI_SUCCESS == lSCIResult)?VOS_OK:VOS_ERR);/* [false alarm]: ����Fortify ���� */
}
VOS_UINT32 USIMM_DLSendData(USIMM_APDU_ST *pstAPDUData)
{
    VOS_INT32                           lSCIResult;
    VOS_UINT8                           aucSendBuf[USIMM_APDU_MAXLEN];

    if(pstAPDUData->ucACK == pstAPDUData->aucAPDU[INS])/*һ���Է���*/
    {
        OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_SND_DATA4);
        lSCIResult = mdrv_sci_send_data(gstUSIMMDLControl.ulSendDataLen, pstAPDUData->aucSendBuf);
        OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);
    }
    else if(pstAPDUData->ucACK == (VOS_UINT8)(~pstAPDUData->aucAPDU[INS]))/*��һ����*/
    {
        lSCIResult = USIMM_DLSendDataOneByOne(pstAPDUData->aucAPDU[INS],
                                            gstUSIMMDLControl.ulSendDataLen,
                                            pstAPDUData->aucSendBuf);
    }
    else                                                                                    /*ACK���ݴ���*/
    {
        USIMM_ERROR_LOG("USIMM_DLSendData: The INS is Wrong");/*��ӡ����*/

        gstUSIMMDLControl.enDLError = USIMMDL_SCIRECEIVEACK_ERROR;

        return VOS_ERR;
    }

    if ((USIMM_PINCMD_VERIFY == pstAPDUData->aucAPDU[INS])
        || (USIMM_PINCMD_CHANGE == pstAPDUData->aucAPDU[INS])
        || (USIMM_PINCMD_DISABLE == pstAPDUData->aucAPDU[INS])
        || (USIMM_PINCMD_ENABLE == pstAPDUData->aucAPDU[INS])
        || (USIMM_PINCMD_UNBLOCK == pstAPDUData->aucAPDU[INS]))
    {
        /*lint -e534*/
        VOS_MemSet(aucSendBuf, (VOS_CHAR)0xFF, sizeof(aucSendBuf));
        /*lint +e534*/
        USIMM_SciDataHook(gstUSIMMDLControl.ulSendDataLen, aucSendBuf);
    }
    else
    {
        USIMM_SciDataHook(gstUSIMMDLControl.ulSendDataLen, pstAPDUData->aucSendBuf);
    }

    if(USIMM_SCI_SUCCESS == lSCIResult)     /*�������ݷ��ͳɹ�*/
    {
        gstUSIMMDLControl.ulRecDataLen = 1; /*����SW1,����60�ĳ�������SW1,SW2�ֿ�����*/

        gstUSIMMDLControl.enDLState    = USIMMDL_STATE_WAITACK;/*�շ�ת���ʱ����Ҫ�Ƚ���ACK*/
    }
    else                                /*�����ʧ��*/
    {
        USIMM_ERROR_LOG("USIMM_DLSendData: SCI Send Data Error");

        gstUSIMMDLControl.enDLError = USIMMDL_SCISENDLC_ERROR;
    }

    return ((USIMM_SCI_SUCCESS == lSCIResult)?VOS_OK:VOS_ERR);/* [false alarm]: ����Fortify ���� */
}
VOS_UINT32 USIMM_DLReceiveACK(USIMM_APDU_ST *pstAPDUData)
{
    VOS_UINT8                           aucRecData[2] = {0};
    VOS_INT32                           lSCIesult;
    VOS_UINT8                           ucINS;

    OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_RCV2);
    lSCIesult = mdrv_sci_recv(1, aucRecData);
    OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

    if(VOS_OK != lSCIesult)/*���մ���*/
    {
        USIMM_ERROR_LOG("USIMM_DLReceiveACK: USIMMSCIReceived ACK Error");

        gstUSIMMDLControl.enDLError = USIMMDL_SCIRECEIVEACK_ERROR;

        return VOS_ERR;
    }

    if(aucRecData[0] == 0x60)   /*����0x60�ֽڣ�״̬�����ٽ��˺�����ACK*/
    {
        USIMM_WARNING_LOG("USIMM_DLReceiveACK:receive 0x60 byte");

        USIMM_SciDataHook(1, aucRecData);    /*���ճɹ�*/

        return VOS_OK;
    }
    else if(((aucRecData[0]&0xF0) == 0x60)||((aucRecData[0]&0xF0) == 0x90))/*����ΪSW1�ֽ�*/
    {
        gstUSIMMDLControl.enDLState    = USIMMDL_STATE_WAITSW;     /*׼������SW2�ֽ�*/

        gstUSIMMDLControl.ulRecDataLen = 1;

        pstAPDUData->ucSW1             = aucRecData[0];
    }
    else                                    /*����ΪACK����*/
    {
        USIMM_SciDataHook(gstUSIMMDLControl.ulRecDataLen, aucRecData);    /*���ճɹ�*/

        pstAPDUData->ucACK = aucRecData[0];

        if(USIMM_CMD_CASE1 == gstUSIMMDLControl.enCMDCase) /*׼������SW */
        {
            if (VOS_FALSE == gstUSIMMDLControl.bSendRep)
            {
                ucINS = pstAPDUData->aucAPDU[INS];
            }
            else
            {
                ucINS = pstAPDUData->aucGetRepAPDU[INS];
            }

            if (pstAPDUData->ucACK == ucINS)
            {
                USIMM_INFO_LOG("USIMM_DLReceiveACK: Case 1 To Case 2 Command, Receive Data");

                gstUSIMMDLControl.enCMDCase    = USIMM_CMD_CASE2;

                gstUSIMMDLControl.ulRecDataLen = USIMM_APDU_MAXLEN;

                pstAPDUData->ulLeValue         = USIMM_APDU_MAXLEN;

                gstUSIMMDLControl.enDLState    = USIMMDL_STATE_WAITDATA;
            }
            else    /*��ǰ�ֽڲ�ʶ�𣬳��Խ���2�ֽ�������ΪSW*/
            {
                USIMM_INFO_LOG("USIMM_DLReceiveACK: Case 1 Command, Receive SW");

                gstUSIMMDLControl.ulRecDataLen = 2; /*׼������SW1,SW2*/

                gstUSIMMDLControl.enDLState    = USIMMDL_STATE_WAITSW;
            }
        }
        else if(USIMM_CMD_CASE2 == gstUSIMMDLControl.enCMDCase)/*��Ҫ������������Le*/
        {
            USIMM_INFO_LOG("USIMM_DLReceiveACK: Case 2 Command, Receive Cmd Data");

            gstUSIMMDLControl.ulRecDataLen = pstAPDUData->ulLeValue;

            gstUSIMMDLControl.enDLState    = USIMMDL_STATE_WAITDATA;
        }
        else if(USIMM_CMD_CASE3 == gstUSIMMDLControl.enCMDCase)/*��Ҫ������������Lc*/
        {
            USIMM_INFO_LOG("USIMM_DLReceiveACK: Case 3 Command, Send Command Data");

            gstUSIMMDLControl.ulSendDataLen  = pstAPDUData->ulLcValue;

            gstUSIMMDLControl.enDLState      = USIMMDL_STATE_SENDDATA;
        }
        else
        {
            USIMM_ERROR_LOG("USIMM_DLReceiveACK: Case 4 Command, Can Not Handler");

            gstUSIMMDLControl.enDLError = USIMMDL_STATE_ERROR;

            return VOS_ERR;
        }
    }

    return VOS_OK;
}

VOS_UINT32 USIMM_DLReceiveData(USIMM_APDU_ST *pstAPDUData)
{
    VOS_INT32                           lSCIResult;
    VOS_UINT8                           aucRecData[256] = {0};

    OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_RCV3);
    lSCIResult = mdrv_sci_recv(gstUSIMMDLControl.ulRecDataLen, aucRecData);
    OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

    if(USIMM_SCI_SUCCESS == lSCIResult)                           /*���ճɹ�׼������SW�ֽ�*/
    {
        USIMM_SciDataHook(gstUSIMMDLControl.ulRecDataLen, aucRecData);

        if((pstAPDUData->ulRecDataLen+gstUSIMMDLControl.ulRecDataLen) > sizeof(pstAPDUData->aucRecvBuf))   /*��λ�ȡ�������Ѿ����������ش��󣬲�֧�ָ����*/
        {
            USIMM_WARNING_LOG("USIMM_GetResponse_APDU: The Receive Data Too long to the aucRecvBuf");
        }
        else
        {
            /*lint -e534*/
            VOS_MemCpy(pstAPDUData->aucRecvBuf+pstAPDUData->ulRecDataLen, aucRecData, gstUSIMMDLControl.ulRecDataLen);   /*��λ�ȡ��������Ҫ�����ھֲ�������*/
            /*lint +e534*/

            pstAPDUData->ulRecDataLen += gstUSIMMDLControl.ulRecDataLen;                         /*��¼�ܹ���������ݳ���*/
        }
#if (VOS_WIN32 == VOS_OS_VER)
        gstUSIMMDLControl.enDLState    = USIMMDL_STATE_WAITSW;

        gstUSIMMDLControl.ulRecDataLen = 2;         /*����ȫ����SW1,SW2*/
#else
         /*������һ�������ֽڣ����п��ܻظ�����60,������SW*/
        gstUSIMMDLControl.enDLState    = USIMMDL_STATE_WAITACK;
        gstUSIMMDLControl.ulRecDataLen = 1;
#endif
    }
    else                                            /*����ʧ��*/
    {
        USIMM_ERROR_LOG("USIMM_DLReceiveData: USIMMSCIReceived Data Error");

        gstUSIMMDLControl.enDLError = USIMMDL_SCIRECEIVELE_ERROR;
    }

    return ((USIMM_SCI_SUCCESS == lSCIResult)?VOS_OK:VOS_ERR);/* [false alarm]: ����Fortify ���� */
}


VOS_UINT32 USIMM_DLReceiveSW(USIMM_APDU_ST *pstAPDUData)
{
    VOS_INT32                           lSCIResult;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucRecData[2] = {0};

    OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_RCV4);
    lSCIResult = mdrv_sci_recv(gstUSIMMDLControl.ulRecDataLen, aucRecData);
    OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

    if(USIMM_SCI_SUCCESS == lSCIResult)                      /*���ճɹ�*/
    {
        if (1 == gstUSIMMDLControl.ulRecDataLen) /*��ǰ���յ�SW2*/
        {
            pstAPDUData->ucSW2 = aucRecData[0];
        }
        else
        {
            pstAPDUData->ucSW1 = aucRecData[0];    /*����SW����*/

            pstAPDUData->ucSW2 = aucRecData[1];
        }

        if (1 == gstUSIMMDLControl.ulSendAPDUTime)   /*�����һ�η��ͷ���SW����*/
        {
            pstAPDUData->ucApduSW1 = pstAPDUData->ucSW1;

            pstAPDUData->ucApduSW2 = pstAPDUData->ucSW2;
        }

        gstUSIMMDLControl.enDLError = USIMMDL_NOERROR;

        USIMM_SciDataHook(2, &pstAPDUData->ucSW1);
    }
    else                                        /*����ʧ��*/
    {
        USIMM_ERROR_LOG("USIMM_DLReceiveSW: USIMMSCIReceived SW Error");

        gstUSIMMDLControl.enDLError = USIMMDL_SCIRECEIVESW_ERROR;

        return VOS_ERR;
    }

    ulResult = USIMM_CheckSW(pstAPDUData);

    if (USIMM_SW_P3_ERROR == ulResult)   /*����P3�ֽڴ��󣬸ı�֮�����½����µ�DL���̷���*/
    {
        USIMM_WARNING_LOG("USIMM_DLReceiveSW:Receive 6C or 67 Byte,Resend APDU Command");

        if ((VOS_TRUE == gstUSIMMDLControl.bSendRep)&&(CMD_INS_GET_RESPONSE == pstAPDUData->aucGetRepAPDU[INS]))
        {
            pstAPDUData->ulLeValue  = pstAPDUData->ucSW2;/*���Ķ�Ӧ��Le�ĳ���*/

            pstAPDUData->aucGetRepAPDU[P3]= pstAPDUData->ucSW2;/*����P3�ֽڵĴ���*/
        }
        else
        {
            if (CMD_INS_STATUS == pstAPDUData->aucAPDU[INS])/*STATUS������Ҫ���¶�Ӧ��ȫ�ֱ�������*/
            {
                pstAPDUData->ulLeValue  = pstAPDUData->ucSW2;/*���Ķ�Ӧ��Le�ĳ���*/
            }
            else
            {
                if (pstAPDUData->ulLcValue != 0)
                {
                    pstAPDUData->ulLcValue  = pstAPDUData->ucSW2;/*���Ķ�Ӧ��Lc�ĳ���*/
                }
                else
                {
                    pstAPDUData->ulLeValue  = pstAPDUData->ucSW2;/*���Ķ�Ӧ��Le�ĳ���*/
                }
            }

            pstAPDUData->aucAPDU[P3]= pstAPDUData->ucSW2;/*����P3�ֽڵĴ���*/
        }

        USIMM_DLStateStar(pstAPDUData);              /*���¿�ʼDL��ĳ�ʼ��*/

        return VOS_OK;
    }

    if (USIMM_SW_OK_WITH_RESOPNSE == ulResult)
    {
        gstUSIMMDLControl.enDLState = USIMMDL_STATE_GETRESPONSE;

        return VOS_OK;
    }

    /* �ο�7816-4 8.6.1 */
    if ((USIMM_SW_WARNING == ulResult)&&(VOS_FALSE == gstUSIMMDLControl.bSendRep))
    {
        gstUSIMMDLControl.enDLState = USIMMDL_STATE_GETRESPONSE;
    }
    else
    {
        gstUSIMMDLControl.enDLState = USIMMDL_STATE_IDLE;
    }

    return VOS_OK;
}
VOS_UINT32 USIMM_DLGetResponse(USIMM_APDU_ST* pstAPDUData)
{
    if (0x80 == pstAPDUData->aucAPDU[CLA])       /* Envelope Command ��Ҫ��ȡ��Ӧֵ */
    {
        pstAPDUData->aucGetRepAPDU[CLA]   = 0x00;
    }
    else
    {
        pstAPDUData->aucGetRepAPDU[CLA]   = pstAPDUData->aucAPDU[CLA];
    }

    pstAPDUData->aucGetRepAPDU[INS]   = CMD_INS_GET_RESPONSE;

    pstAPDUData->aucGetRepAPDU[P1]    = 0x00;

    pstAPDUData->aucGetRepAPDU[P2]    = 0x00;

    if((0x61 == pstAPDUData->ucSW1)||(0x9F == pstAPDUData->ucSW1))
    {
        pstAPDUData->aucGetRepAPDU[P3] = pstAPDUData->ucSW2; /*������һ������״̬��61XX��SW2��ֵ*/

        if(0x00 == pstAPDUData->aucGetRepAPDU[P3])
        {
            pstAPDUData->ulLeValue  = 0x100;
        }
        else
        {
            pstAPDUData->ulLeValue  = pstAPDUData->aucGetRepAPDU[P3];
        }
    }
    else
    {
        pstAPDUData->aucGetRepAPDU[P3]= 0x00;             /*�����62����63*/

        pstAPDUData->ulLeValue  = 0x00;
    }

    pstAPDUData->ulLcValue      = 0x00;

    pstAPDUData->ucSW1          = 0x00;

    pstAPDUData->ucSW2          = 0x00;

    pstAPDUData->ucACK          = 0x00;

    gstUSIMMDLControl.bSendRep  = VOS_TRUE;

    USIMM_DLStateStar(pstAPDUData);

    return VOS_OK;
}
static USIMMDL_FUNC_STATUS gastUSIMMDLProc[] =
{
    {USIMMDL_STATE_IDLE,        USIMM_DLIdle},
    {USIMMDL_STATE_SENDAPDU,    USIMM_DLSendAPDU},
    {USIMMDL_STATE_SENDDATA,    USIMM_DLSendData},
    {USIMMDL_STATE_WAITACK,     USIMM_DLReceiveACK},
    {USIMMDL_STATE_WAITDATA,    USIMM_DLReceiveData},
    {USIMMDL_STATE_WAITSW,      USIMM_DLReceiveSW},
    {USIMMDL_STATE_GETRESPONSE, USIMM_DLGetResponse}
};

VOS_UINT32 USIMM_T0DLHandle(USIMM_APDU_ST* pstAPDUData)
{
    VOS_UINT32  ulResult = 0;           /* ������� */
    VOS_UINT32  i;

    if(USIMMDL_STATE_IDLE != gstUSIMMDLControl.enDLState)
    {
        USIMM_WARNING_LOG("USIMM_T0DLHandle: DL State is Wrong");/* ��ӡ���� */
    }

    USIMM_ExcLogDataBK();

    pstAPDUData->ulRecDataLen  = 0;     /*���ڶ�ν������ݣ����DL�㿪ʼ��ʱ���������*/

    /*lint -e534*/
    VOS_MemSet(&gstUSIMMDLControl, 0, sizeof(gstUSIMMDLControl));   /* ��ʼ����ǰ״̬ */

    VOS_MemSet(pstAPDUData->aucGetRepAPDU, 0, USIMM_APDU_HEADLEN);
    /*lint +e534*/

    USIMM_DLStateStar(pstAPDUData);

    if(USIMM_CMD_CASE4 == gstUSIMMDLControl.enCMDCase)
    {
        /* T=0Э�飬û��case4���������ͨ��case3+case2ʵ�ֵ�case4 */
        gstUSIMMDLControl.enCMDCase = USIMM_CMD_CASE3;

        pstAPDUData->ulLeValue = 0;
    }

    for(i=0; i<(sizeof(gastUSIMMDLProc)/sizeof(USIMMDL_FUNC_STATUS)); i++)
    {
        if(gstUSIMMDLControl.enDLState == gastUSIMMDLProc[i].enStateId)
        {
            ulResult = gastUSIMMDLProc[i].pProcFun(pstAPDUData);

            /*�����ִ���������DL���̺��˳�*/
            if((VOS_OK != ulResult)||(USIMMDL_STATE_IDLE == gstUSIMMDLControl.enDLState))
            {
                break;
            }

            i = 0;
        }
    }

    gstUSIMMDLControl.enDLState = USIMMDL_STATE_IDLE;

    /*���ݴ�����Ϣ���غ����������*/
    if(USIMMDL_NOERROR == gstUSIMMDLControl.enDLError)
    {
        USIMM_INFO_LOG("USIMM_T0DLHandle:DL Complete the Step Right");

        ulResult = USIMM_DL_SUCESS;

        USIMM_ExcLogDataRE();
    }
    else if(gstUSIMMDLControl.enDLError > USIMMDL_SCISENDLC_ERROR)
    {
        USIMM_ERROR_LOG("USIMM_T0DLHandle:DL Complete the Step With Receive Data Error");

        ulResult = USIMM_DL_RECEIVE_ERROR;
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_T0DLHandle:DL Complete the Step With Send Data Error");

        ulResult = USIMM_DL_SEND_ERROR;
    }

    gstUSIMMDLControl.enDLState = USIMMDL_STATE_IDLE;   /*DL���̽���*/

    return ulResult;
}


VOS_UINT32 USIMM_DLHandle(USIMM_APDU_ST* pstAPDUData)
{
    VOS_UINT32      ulResult;           /* ������� */

    if(USIMM_DL_T_MODE_T0 == g_enUSIMMTMode)
    {
        /* ��ǰ֧��T=0 */
        ulResult = USIMM_T0DLHandle(pstAPDUData);
    }
    else if(USIMM_DL_T_MODE_T1 == g_enUSIMMTMode)
    {
        /* ��ǰ֧��T=1 */
        ulResult = USIMM_T1DLHandle(pstAPDUData);
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_DLHandle: USIMM T mode is BUTT");

        ulResult = VOS_ERR;
    }

    return ulResult;
}
VOS_UINT32 USIMM_DLCglaReceiveSW(USIMM_APDU_ST *pstAPDUData)
{
    VOS_INT32                           lSCIResult;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucRecData[2] = {0};

    OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_RCV4);
    lSCIResult = mdrv_sci_recv(gstUSIMMDLControl.ulRecDataLen, aucRecData);
    OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

    if(USIMM_SCI_SUCCESS == lSCIResult)                      /*���ճɹ�*/
    {
        if(1 == gstUSIMMDLControl.ulRecDataLen) /*��ǰ���յ�SW2*/
        {
            pstAPDUData->ucSW2 = aucRecData[0];
        }
        else
        {
            pstAPDUData->ucSW1 = aucRecData[0];    /*����SW����*/

            pstAPDUData->ucSW2 = aucRecData[1];
        }

        gstUSIMMDLControl.enDLError = USIMMDL_NOERROR;

        USIMM_SciDataHook(2, &pstAPDUData->ucSW1);
    }
    else                                        /*����ʧ��*/
    {
        USIMM_ERROR_LOG("USIMM_DLCglaReceiveSW: USIMMSCIReceived SW Error");

        gstUSIMMDLControl.enDLError = USIMMDL_SCIRECEIVESW_ERROR;

        return VOS_ERR;
    }

    ulResult = USIMM_CheckSW(pstAPDUData);

    /* �����һ�η��ͷ���SW���ݺ�Resultֵ */
    if (1 == gstUSIMMDLControl.ulSendAPDUTime)
    {
        pstAPDUData->ucApduSW1 = pstAPDUData->ucSW1;
        pstAPDUData->ucApduSW2 = pstAPDUData->ucSW2;
        pstAPDUData->ucResult  = (VOS_UINT8)ulResult;
    }

    /* ���Ʋ����з���INS=0x09����Ҫֱ�ӷ��� */
    if((USIMM_SW_P3_ERROR == ulResult)&&(0x09 != pstAPDUData->aucAPDU[INS]))   /*����P3�ֽڴ��󣬸ı�֮�����½����µ�DL���̷���*/
    {
        USIMM_WARNING_LOG("USIMM_DLCglaReceiveSW:Receive 6C or 67 Byte,Resend APDU Command");

        if ((VOS_TRUE == gstUSIMMDLControl.bSendRep)&&(CMD_INS_GET_RESPONSE == pstAPDUData->aucGetRepAPDU[INS]))
        {
            pstAPDUData->ulLeValue  = pstAPDUData->ucSW2;/*���Ķ�Ӧ��Le�ĳ���*/

            pstAPDUData->aucGetRepAPDU[P3]= pstAPDUData->ucSW2;/*����P3�ֽڵĴ���*/
        }
        else
        {
            if (CMD_INS_STATUS == pstAPDUData->aucAPDU[INS])/*STATUS������Ҫ���¶�Ӧ��ȫ�ֱ�������*/
            {
                pstAPDUData->ulLeValue  = pstAPDUData->ucSW2;/*���Ķ�Ӧ��Le�ĳ���*/
            }
            else
            {
                if (pstAPDUData->ulLcValue != 0)
                {
                    pstAPDUData->ulLcValue  = pstAPDUData->ucSW2;/*���Ķ�Ӧ��Lc�ĳ���*/
                }
                else
                {
                    pstAPDUData->ulLeValue  = pstAPDUData->ucSW2;/*���Ķ�Ӧ��Le�ĳ���*/
                }
            }

            pstAPDUData->aucAPDU[P3]= pstAPDUData->ucSW2;/*����P3�ֽڵĴ���*/
        }

        USIMM_DLStateStar(pstAPDUData);              /*���¿�ʼDL��ĳ�ʼ��*/

        return VOS_OK;
    }

    if(USIMM_SW_OK_WITH_RESOPNSE == ulResult)
    {
        gstUSIMMDLControl.enDLState = USIMMDL_STATE_GETRESPONSE;

        return VOS_OK;
    }

    gstUSIMMDLControl.enDLState = USIMMDL_STATE_IDLE;

    /* �ο�7816-4 8.6.1 */
    if ((USIMM_SW_WARNING == ulResult)
      &&(VOS_FALSE == gstUSIMMDLControl.bSendRep)
	  &&(VOS_TRUE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulCglaGetRsp))
    {
        gstUSIMMDLControl.enDLState = USIMMDL_STATE_GETRESPONSE;
    }

    return VOS_OK;
}


VOS_UINT32 USIMM_DLCglaGetResponse(USIMM_APDU_ST* pstAPDUData)
{
    VOS_UINT32                      ulTempLen;

    if (USIMM_SIM_CLA != pstAPDUData->aucAPDU[CLA])
    {
        /* ����102.221Э��,GET RESPONSE��INS�ֶ�֧��'0X' or '4X' or '6X' */
        pstAPDUData->aucGetRepAPDU[CLA] = pstAPDUData->aucAPDU[CLA] & 0x6F;
    }
    else
    {
        pstAPDUData->aucGetRepAPDU[CLA] = USIMM_SIM_CLA;
    }

    pstAPDUData->aucGetRepAPDU[INS]   = CMD_INS_GET_RESPONSE;

    pstAPDUData->aucGetRepAPDU[P1]    = 0x00;

    pstAPDUData->aucGetRepAPDU[P2]    = 0x00;

    if((0x61 == pstAPDUData->ucSW1)||(0x9F == pstAPDUData->ucSW1))
    {
        pstAPDUData->aucGetRepAPDU[P3] = pstAPDUData->ucSW2; /*������һ������״̬��61XX��SW2��ֵ*/

        if(0x00 == pstAPDUData->aucGetRepAPDU[P3])
        {
            ulTempLen = 0x100;
        }
        else
        {
            ulTempLen = pstAPDUData->aucGetRepAPDU[P3];
        }

        if ((pstAPDUData->ulRecDataLen + ulTempLen) > USIMM_APDU_MAXLEN)
        {
            gstUSIMMDLControl.enDLState = USIMMDL_STATE_IDLE;

            return VOS_OK;
        }

        pstAPDUData->ulLeValue  = ulTempLen;
    }
    else
    {
        pstAPDUData->aucGetRepAPDU[P3]= 0x00;             /*�����62����63*/

        pstAPDUData->ulLeValue  = 0x00;
    }

    pstAPDUData->ulLcValue      = 0x00;

    pstAPDUData->ucSW1          = 0x00;

    pstAPDUData->ucSW2          = 0x00;

    pstAPDUData->ucACK          = 0x00;

    gstUSIMMDLControl.bSendRep  = VOS_TRUE;

    USIMM_DLStateStar(pstAPDUData);

    return VOS_OK;
}
static USIMMDL_FUNC_STATUS gastUSIMMCglaDLProc[] =
{
    {USIMMDL_STATE_IDLE,        USIMM_DLIdle},
    {USIMMDL_STATE_SENDAPDU,    USIMM_DLSendAPDU},
    {USIMMDL_STATE_SENDDATA,    USIMM_DLSendData},
    {USIMMDL_STATE_WAITACK,     USIMM_DLReceiveACK},
    {USIMMDL_STATE_WAITDATA,    USIMM_DLReceiveData},
    {USIMMDL_STATE_WAITSW,      USIMM_DLCglaReceiveSW},
    {USIMMDL_STATE_GETRESPONSE, USIMM_DLCglaGetResponse}
};

VOS_UINT32 USIMM_T0CglaDLHandle(USIMM_APDU_ST* pstAPDUData)
{
    VOS_UINT32  ulResult = 0;           /* ������� */
    VOS_UINT32  i;

    if(USIMMDL_STATE_IDLE != gstUSIMMDLControl.enDLState)
    {
        USIMM_WARNING_LOG("USIMM_T0CglaDLHandle: DL State is Wrong");/* ��ӡ���� */

        gstUSIMMDLControl.enDLState = USIMMDL_STATE_IDLE;/* ��ʼ����ǰ״̬ */
    }

    pstAPDUData->ulRecDataLen  = 0;     /*���ڶ�ν������ݣ����DL�㿪ʼ��ʱ���������*/

    /*lint -e534*/
    VOS_MemSet(&gstUSIMMDLControl, 0, sizeof(gstUSIMMDLControl));   /* ��ʼ����ǰ״̬ */

    VOS_MemSet(pstAPDUData->aucGetRepAPDU, 0, USIMM_APDU_HEADLEN);
    /*lint +e534*/

    USIMM_DLStateStar(pstAPDUData);

    if(USIMM_CMD_CASE4 == gstUSIMMDLControl.enCMDCase)
    {
        /* T=0Э�飬û��case4���������ͨ��case3+case2ʵ�ֵ�case4 */
        gstUSIMMDLControl.enCMDCase = USIMM_CMD_CASE3;

        pstAPDUData->ulLeValue = 0;
    }

    for(i=0; i<(sizeof(gastUSIMMCglaDLProc)/sizeof(USIMMDL_FUNC_STATUS)); i++)
    {
        if(gstUSIMMDLControl.enDLState == gastUSIMMCglaDLProc[i].enStateId)
        {
            ulResult = gastUSIMMCglaDLProc[i].pProcFun(pstAPDUData);

            /*�����ִ���������DL���̺��˳�*/
            if((VOS_OK != ulResult)||(USIMMDL_STATE_IDLE == gstUSIMMDLControl.enDLState))
            {
                break;
            }

            i = 0;
        }
    }

    gstUSIMMDLControl.enDLState = USIMMDL_STATE_IDLE;

    /*���ݴ�����Ϣ���غ����������*/
    if(USIMMDL_NOERROR == gstUSIMMDLControl.enDLError)
    {
        USIMM_INFO_LOG("USIMM_T0CglaDLHandle:DL Complete the Step Right");

        ulResult = USIMM_DL_SUCESS;
    }
    else if(gstUSIMMDLControl.enDLError > USIMMDL_SCISENDLC_ERROR)
    {
        USIMM_ERROR_LOG("USIMM_T0CglaDLHandle:DL Complete the Step With Receive Data Error");

        ulResult = USIMM_DL_RECEIVE_ERROR;
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_T0CglaDLHandle:DL Complete the Step With Send Data Error");

        ulResult = USIMM_DL_SEND_ERROR;
    }

    gstUSIMMDLControl.enDLState = USIMMDL_STATE_IDLE;   /*DL���̽���*/

    return ulResult;
}
VOS_UINT32 USIMM_CglaDLHandle(USIMM_APDU_ST* pstAPDUData)
{

    VOS_UINT32  ulResult = 0;           /* ������� */

    if(USIMM_DL_T_MODE_T0 == g_enUSIMMTMode)
    {
        /* ��ǰ֧��T=0 */
        ulResult = USIMM_T0CglaDLHandle(pstAPDUData);
    }
    else if(USIMM_DL_T_MODE_T1 == g_enUSIMMTMode)
    {
        /* ��ǰ֧��T=1 */
        ulResult = USIMM_T1DLHandle(pstAPDUData);
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_CglaDLHandle: USIMM T mode is BUTT");

        ulResult = VOS_ERR;
    }

    return ulResult;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* #if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT) */


