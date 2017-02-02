
#include <osm.h>
#include <gen_msg.h>
#include <ftm.h>
#include <ftm_ct.h>
/*lint -save -e537*/
#include <msp_errno.h>
/*lint -restore*/
#include <msp_drx.h>
#include "ftm_mntn.h"
/*lint -save -e767*/
#define    THIS_FILE_ID        MSP_FILE_ID_FTM_MAILBOX_PROC_C
/*lint -restore*/
/* �������ݿɶ�֪ͨ�ź���������ص����� */
VOS_SEM g_mailbox_readsem = 0; 

/*lint --e{830,539,525}*/

/*****************************************************************************
 �� �� ��  : ftm_mailbox_msgproc
 ��������  : �������ݶ�ȡ
 �������  : enMbxType ������������
 �������  : ��
 �� �� ֵ  : 0�����ݣ�����0Ϊ�������ݳ���
*****************************************************************************/
VOS_UINT32 ftm_mailbox_msgproc(MAILBOX_SERVICE_TYPE_E enMbxType)
{
    VOS_UINT32 ulRet      = 0;
    VOS_UINT32 ulMsgSize  = 0;
    VOS_VOID* pMailBoxMsg = NULL;
    MsgBlock* pMsgBlock   = NULL;
    VOS_UINT32 ret = ERR_MSP_UNKNOWN;

    /* ��ȡ��Ϣ���� */
    ulMsgSize = BSP_MailBox_ComMsgSize(enMbxType);
    if(ulMsgSize == 0 )
    {
        return ulMsgSize;
    }

    pMailBoxMsg = VOS_MemAlloc(MSP_SYS_FTM_PID, ((DYNAMIC_MEM_PT)), ulMsgSize);
    if(NULL == pMailBoxMsg)
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] VOS_MemAlloc failed.\n", __FUNCTION__, __LINE__, VOS_GetSlice());
        return 0;
    }

    /* ��ȡ�������� */
    ulRet = BSP_MailBox_ComMsgRead(enMbxType, pMailBoxMsg, ulMsgSize, EN_MAILBOX_SLEEP_WAKEUP);
    if(ulRet != VOS_OK)
    {
        (VOS_VOID)VOS_MemFree(MSP_SYS_FTM_PID, pMailBoxMsg);
        return 0;
    }

    /* ������Ϣ��MSP_SYS_FTM_PID���� */
    pMsgBlock = (MsgBlock*)VOS_AllocMsg(MSP_SYS_FTM_PID, sizeof(OS_MSG_STRU));
    if (!pMsgBlock) {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]VOS_MemAlloc failed\n",__FUNCTION__,__LINE__,VOS_GetSlice());
        return 0;
    }

    OS_MSG_STRU* pMsg = (OS_MSG_STRU*)pMsgBlock->aucValue;

    pMsgBlock->ulReceiverPid = MSP_SYS_FTM_PID;
    pMsgBlock->ulSenderPid   = MSP_SYS_FTM_PID;
    pMsg->ulMsgId  = ID_MSG_L1A_CT_IND;
    pMsg->ulParam1 = pMailBoxMsg;
    pMsg->ulParam2 = ulMsgSize;

    (VOS_VOID)ftm_mntn_mb2ftm_save(pMsg->ulMsgId, (VOS_UINT8 *)pMailBoxMsg, ulMsgSize);
    ftm_mntn_datahook(MSP_LDSP_PID, MSP_SYS_FTM_PID, ulMsgSize, (VOS_UINT8 *)pMailBoxMsg);   
    
    ret = VOS_SendMsg(MSP_SYS_FTM_PID, pMsgBlock);
    if (ret != VOS_OK){
        (VOS_VOID)ftm_mntn_printf("[%s line%d,slice %d]send msg to MSP_SYS_FTM_PID FAILED \n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return 0;
    }

    return ulMsgSize;
}

/*****************************************************************************
 �� �� ��  : ftm_mailbox_taskproc
 ��������  : �����������Դ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOS_VOID ftm_mailbox_taskproc(VOS_UINT32 ulPara0,
                              VOS_UINT32 ulPara1,
                              VOS_UINT32 ulPara2,
                              VOS_UINT32 ulPara3)
{
	/*lint -save -e716*/
	while(1)
	/*lint -restore*/
    {
        if(VOS_ERR == VOS_SmP(g_mailbox_readsem, 0))
        {
            (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d] VOS_Smp failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        }

		/*vote for lock*/
		drx_msp_fid_vote_lock(DRX_FTM_MAILBOX_VOTE);
       /* LTE CT ԭ�� */
        if(ftm_mailbox_msgproc(EN_MAILBOX_SERVICE_LTE_CT) > 0)
        {
            continue;
        }

      /* LTE BT ԭ�� */
        if(ftm_mailbox_msgproc(EN_MAILBOX_SERVICE_LTE_BT) > 0)
        {
            continue;
        }

        /* TDS CT ԭ�� */
        if(ftm_mailbox_msgproc(EN_MAILBOX_SERVICE_TDS_CT) > 0)
        {
            continue;
        }

        /* TDS BT ԭ�� */
        if(ftm_mailbox_msgproc(EN_MAILBOX_SERVICE_TDS_BT) > 0)
        {
            continue;
        }
		/*vote for lock*/
		drx_msp_fid_vote_unlock(DRX_FTM_MAILBOX_VOTE);
    }

}

/*****************************************************************************
 �� �� ��  : ftm_mailbox_ltect_cb
 ��������  : LTE CT�������ݵ��׻ص�
 �������  : enIntType �����ж�����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOS_VOID ftm_mailbox_ltect_cb(MAILBOX_INT_TYPE_E enIntType)
{
    (VOS_VOID)VOS_SmV(g_mailbox_readsem);

    return;
}

/*****************************************************************************
 �� �� ��  : ftm_mailbox_ltebt_cb
 ��������  : LTE BT�������ݵ��׻ص�
 �������  : enIntType �����ж�����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOS_VOID ftm_mailbox_ltebt_cb(MAILBOX_INT_TYPE_E enIntType)
{
    (VOS_VOID)VOS_SmV(g_mailbox_readsem);

    return;
}

/*****************************************************************************
 �� �� ��  : ftm_mailbox_tdsct_cb
 ��������  : TDS CT�������ݵ��׻ص�
 �������  : enIntType �����ж�����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOS_VOID ftm_mailbox_tdsct_cb(MAILBOX_INT_TYPE_E enIntType)
{
    (VOS_VOID)VOS_SmV(g_mailbox_readsem);

    return;
}

/*****************************************************************************
 �� �� ��  : ftm_mailbox_tdsbt_cb
 ��������  : TDS BT�������ݵ��׻ص�
 �������  : enIntType �����ж�����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOS_VOID ftm_mailbox_tdsbt_cb(MAILBOX_INT_TYPE_E enIntType)
{
    (VOS_VOID)VOS_SmV(g_mailbox_readsem);

    return;
}

/*****************************************************************************
 �� �� ��  : ftm_mailbox_ltect_write
 ��������  : дLTE CT�������ݵ�����
 �������  : param ԭ������
             ulLen ԭ�ﳤ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOS_UINT32 ftm_mailbox_ltect_write(VOS_VOID* param,VOS_UINT32 ulLen)
{
    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
    ulRet = BSP_MailBox_ComMsgWrite(EN_MAILBOX_SERVICE_LTE_CT, param, ulLen, EN_MAILBOX_SLEEP_WAKEUP);
    if(ulRet != VOS_OK)
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]send lte ct to dsp fail\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        ulRet = ERR_MSP_FAILURE;
    }
    FTM_MNTN_FTM2RTT_MSG(*((VOS_UINT*)param))
   
    (VOS_VOID)ftm_mntn_ftm2mb_save((VOS_UINT8 *)param, ulLen);
    (VOS_VOID)ftm_mntn_datahook(MSP_SYS_FTM_PID, MSP_LDSP_PID, ulLen, (VOS_UINT8 *)param);
    
    return ulRet;
}

/*****************************************************************************
 �� �� ��  : ftm_mailbox_ltebt_write
 ��������  : дLTE bT�������ݵ�����
 �������  : param ԭ������
             ulLen ԭ�ﳤ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOS_UINT32 ftm_mailbox_ltebt_write(VOS_VOID* param,VOS_UINT32 ulLen)
{
    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;

    ulRet = BSP_MailBox_ComMsgWrite(EN_MAILBOX_SERVICE_LTE_BT, param, ulLen, EN_MAILBOX_SLEEP_WAKEUP);
    if(ulRet != VOS_OK)
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]send lte ct to dsp fail\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        ulRet = ERR_MSP_FAILURE;
    }
    FTM_MNTN_FTM2RTT_MSG(*((VOS_UINT*)param))
    (VOS_VOID)ftm_mntn_ftm2mb_save((VOS_UINT8 *)param, ulLen);
    ftm_mntn_datahook(MSP_SYS_FTM_PID, MSP_LDSP_PID, ulLen, (VOS_UINT8 *)param);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : ftm_mailbox_tdsct_write
 ��������  : дTDS CT�������ݵ�����
 �������  : param ԭ������
             ulLen ԭ�ﳤ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOS_UINT32 ftm_mailbox_tdsct_write(VOS_VOID* param,VOS_UINT32 ulLen)
{
    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;

    ulRet = BSP_MailBox_ComMsgWrite(EN_MAILBOX_SERVICE_TDS_CT, param, ulLen, EN_MAILBOX_SLEEP_WAKEUP);
    if(ulRet != VOS_OK)
    {
        
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]send tds ct to dsp fail\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        ulRet = ERR_MSP_FAILURE;
    }
    FTM_MNTN_FTM2RTT_MSG(*((VOS_UINT*)param))

    (VOS_VOID)ftm_mntn_ftm2mb_save((VOS_UINT8 *)param, ulLen);
    ftm_mntn_datahook(MSP_SYS_FTM_PID, MSP_LDSP_PID, ulLen, (VOS_UINT8 *)param);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : ftm_mailbox_tdsbt_write
 ��������  : дLTE BT�������ݵ�����
 �������  : param ԭ������
             ulLen ԭ�ﳤ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOS_UINT32 ftm_mailbox_tdsbt_write(VOS_VOID* param,VOS_UINT32 ulLen)
{
    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;

    ulRet = BSP_MailBox_ComMsgWrite(EN_MAILBOX_SERVICE_TDS_BT, param, ulLen, EN_MAILBOX_SLEEP_WAKEUP);
    if(ulRet != VOS_OK)
    {
        
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]send tds bt to dsp fail\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        ulRet = ERR_MSP_FAILURE;
    }
    FTM_MNTN_FTM2RTT_MSG(*((VOS_UINT*)param))

    (VOS_VOID)ftm_mntn_ftm2mb_save((VOS_UINT8 *)param, ulLen);
    ftm_mntn_datahook(MSP_SYS_FTM_PID, MSP_LDSP_PID, ulLen, (VOS_UINT8 *)param);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : ftm_mailbox_ltect_write
 ��������  : дLTE CT�������ݵ�����
 �������  : param ԭ������
             ulLen ԭ�ﳤ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOS_UINT32 ftm_mailbox_ct_write(VOS_UINT32 mode, VOS_VOID* param,VOS_UINT32 ulLen)
{
    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;

    if(EN_FCHAN_MODE_TD_SCDMA == mode)
    {
        ulRet = ftm_mailbox_tdsct_write(param, ulLen);
    }
    else
    {
        ulRet = ftm_mailbox_ltect_write(param, ulLen);
    }

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : ftm_mailbox_bt_write
 ��������  : дLTE BT�������ݵ�����
 �������  : param ԭ������
             ulLen ԭ�ﳤ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOS_UINT32 ftm_mailbox_bt_write(VOS_UINT32 mode, VOS_VOID* param,VOS_UINT32 ulLen)
{
    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;

    if(EN_FCHAN_MODE_TD_SCDMA == mode)
    {
        ulRet = ftm_mailbox_tdsbt_write(param, ulLen);
    }
    else
    {
        ulRet = ftm_mailbox_ltebt_write(param, ulLen);
    }

    return ulRet;
}


/*****************************************************************************
 �� �� ��  : ftm_mailbox_init
 ��������  : FTMģ�����������ʼ��
 �������  : param ԭ������
             ulLen ԭ�ﳤ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOS_UINT32 ftm_mailbox_init(VOS_VOID)
{
    if(VOS_OK != VOS_SmBCreate( "ftm_mailbox_taskproc", 0, VOS_SEMA4_FIFO, &g_mailbox_readsem))
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]VOS_SmBCreate failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return ERR_MSP_FAILURE;
    }

    if(VOS_OK != BSP_MailBox_ComNotifyReg(EN_MAILBOX_SERVICE_LTE_CT, ftm_mailbox_ltect_cb))
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]BSP_MailBox_ComNotifyReg EN_MAILBOX_SERVICE_LTE_CT failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return ERR_MSP_FAILURE;
    }

    if(VOS_OK != BSP_MailBox_ComNotifyReg(EN_MAILBOX_SERVICE_LTE_BT, ftm_mailbox_ltebt_cb))
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]BSP_MailBox_ComNotifyReg EN_MAILBOX_SERVICE_LTE_BT failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return ERR_MSP_FAILURE;
    }

    if(VOS_OK != BSP_MailBox_ComNotifyReg(EN_MAILBOX_SERVICE_TDS_CT, ftm_mailbox_tdsct_cb))
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]BSP_MailBox_ComNotifyReg EN_MAILBOX_SERVICE_TDS_CT failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return ERR_MSP_FAILURE;
    }

    if(VOS_OK != BSP_MailBox_ComNotifyReg(EN_MAILBOX_SERVICE_TDS_BT, ftm_mailbox_tdsbt_cb))
    {
        (VOS_VOID)ftm_mntn_printf("[%s line%d, slice%d]BSP_MailBox_ComNotifyReg EN_MAILBOX_SERVICE_TDS_BT failed\n", __FUNCTION__, __LINE__,VOS_GetSlice());
        return ERR_MSP_FAILURE;
    }

    return ERR_MSP_SUCCESS;
}

