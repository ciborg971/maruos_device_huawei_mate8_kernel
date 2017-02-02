

#include <msp_errno.h>
#include <osm.h>
#include <gen_msg.h>
#include <ftm.h>
#include "LMspLPhyInterface.h"
#include "ftm_ct.h"
#include "TPsTMspInterface.h"

/*lint -e767*/
#define    THIS_FILE_ID        MSP_FILE_ID_FTM_LTE_NONSIGNAL_BT_C
/*lint -e767*/

/*lint --e{830,539,525,550}*/

/*****************************************************************************
 �� �� ��  : at_ftm_ssync_store
 ��������  : �������
 �������  : ucStoreType �������� 
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
/*lint -save -e655 -e732 -e958*/
static VOID at_ftm_ssync_store(VOS_UINT8 ucStoreType, FTM_SET_SSYNC_REQ_STRU* pstReq)
{
    static FTM_SET_SSYNC_REQ_STRU stReq = { 0 };    
    FTM_SYN_INFO_STRU* pstFtmSynInfo    = ftm_GetSynMainInfo();
    
    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {       
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_SSYNC_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else 
    {
        pstFtmSynInfo->ulCurCmdStepsFlag |= CT_S_STEPS_DONE_SSYNC;
        pstFtmSynInfo->ulCurCmdStepsFlag |= CT_S_STEPS_DONE_SSYNC_CNF;
    }
    
    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_ssync_setcnf
 ��������  : ����ID_MSG_FTM_SET_SSYNC_CNF
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_ssync_setcnf(VOS_UINT32 ulErrCode)
{  
    FTM_SET_SSYNC_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_SSYNC_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_SSYNC_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_ssync_read
 ��������  : ID_MSG_FTM_RD_SSYNC_REQ ������
 �������  : pParam FTM_RD_SSYNC_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_ssync_read(VOID* pParam)
{ 
    FTM_SYN_INFO_STRU* pstFtmSynInfo = ftm_GetSynMainInfo();
    FTM_RD_SSYNC_CNF_STRU stRdCnf    = { 0 };

    stRdCnf.ulStatus = pstFtmSynInfo->stSsyncRdCnf.ulStatus;
    stRdCnf.ulErrCode = ERR_MSP_SUCCESS;
           
    return ftm_comm_send(ID_MSG_FTM_RD_SSYNC_CNF, (VOS_UINT32)&stRdCnf, 
        sizeof(FTM_RD_SSYNC_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_ssync_set
 ��������  : ID_MSG_FTM_SET_SSYNC_REQ ������
             ��DSP����OM_PHY_SYN_SSYNC_SET_REQԭ��
 �������  : pParam FTM_SET_SSYNC_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_ssync_set(VOS_VOID* pParam)
{ 
    FTM_SET_SSYNC_REQ_STRU* pstFtmReq        = (FTM_SET_SSYNC_REQ_STRU*)pParam;
    OM_PHY_SYN_SSYNC_SET_REQ_STRU stReqToDsp = { 0 };
    FTM_SYN_INFO_STRU* pstFtmSynInfo         = ftm_GetSynMainInfo();
    MSP_PS_SET_SFN_SYNC_REQ_STRU stReqToPsSync = {0};
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();
    FCHAN_MODE_ENUM fchanMode = pstFtmFastCtInfo->enCurMode;    

    pstFtmSynInfo->stSsyncRdCnf.ulStatus =  0;
  
    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if((ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
        || (!ftm_CheckSynCmdSteps(CT_S_STEPS_DONE_TMODE_7_REQ)))
    {
        return at_ftm_ssync_setcnf(ERR_MSP_UE_MODE_ERR);
    }
	if (EN_FCHAN_MODE_TD_SCDMA == fchanMode)
    {
        HAL_SDMLOG("-----[%s]:send data to ps \n", __FUNCTION__);

        stReqToPsSync.cellID = pstFtmSynInfo->stFtmSparaInfo.usValue;
		stReqToPsSync.freq = pstFtmReq->usdlChannel;/*usdlChannel = usulChannel*/
		stReqToPsSync.MsgId = ID_T_MSP_PS_SFN_SYNC_REQ;

	    if(ERR_MSP_SUCCESS != atFTMSendVosMsg(TPS_PID_MAC, &stReqToPsSync, sizeof(stReqToPsSync) ))
		{
			HAL_SDMLOG("[%s] send data to ps fail\n", __FUNCTION__);
		       return at_ftm_ssync_setcnf(ERR_MSP_UNKNOWN);
		}	
  
	    at_ftm_ssync_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);      
        return ERR_MSP_WAIT_ASYNC;       
    }
    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId     = OM_PHY_SYN_SSYNC_SET_REQ;
    stReqToDsp.usMode      = pstFtmReq->usMode;
    stReqToDsp.usBand      = pstFtmReq->usBand;
	stReqToDsp.usUlchannel = pstFtmReq->usulChannel;
    stReqToDsp.usDlchannel = pstFtmReq->usdlChannel;

    if(ERR_MSP_SUCCESS != ftm_mailbox_ltebt_write(&stReqToDsp, sizeof(OM_PHY_SYN_SSYNC_SET_REQ_STRU)))
    {
        return at_ftm_ssync_setcnf(ERR_MSP_UNKNOWN);
    }

    at_ftm_ssync_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);      
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_ssync_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_ssync_timeout(VOS_VOID)
{
    return at_ftm_ssync_setcnf(ERR_MSP_TIME_OUT);
}
/*****************************************************************************
 �� �� ��  : at_ftm_ssync_pscnf
 ��������  : PSԭ��ID_T_PS_MSP_SFN_SYNC_CNF������
 �������  : pParam PS_MSP_SFN_SYNC_CNFָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_ssync_pscnf(VOS_VOID* pParam)
{
    PS_MSP_SFN_SYNC_CNF* pPsCnf = (PS_MSP_SFN_SYNC_CNF*)pParam;
    FTM_SYN_INFO_STRU* pstFtmSynInfo = ftm_GetSynMainInfo();
	
    HAL_SDMLOG("-----ENTER:at_ftm_ssync_pscnf  \n");
	
    at_ftm_ssync_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);/*��sync_done ��־ */

    pstFtmSynInfo->stSsyncRdCnf.ulStatus = pPsCnf->ulresult;
    return at_ftm_ssync_setcnf(ERR_MSP_SUCCESS);
}



/*****************************************************************************
 �� �� ��  : at_ftm_ssync_dspcnf
 ��������  : DSPԭ��PHY_OM_SYN_SSYNC_SET_CNF������
 �������  : pParam PHY_OM_SYN_SSYNC_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_ssync_dspcnf(VOS_VOID* pParam)
{
    
    at_ftm_ssync_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_ssync_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_ssync_dspind
 ��������  : DSPԭ��PHY_OM_SYN_SSYNC_IND������
             ��DSP�����ϱ�����Ϣ����ȫ�ֻ�����
 �������  : pParam PHY_OM_SYN_SSYNC_RPT_IND_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_ssync_dspind(VOS_VOID* pParam)
{
    PHY_OM_SYN_SSYNC_RPT_IND_STRU* pstSsyncInd = (PHY_OM_SYN_SSYNC_RPT_IND_STRU*)pParam; 
    FTM_SYN_INFO_STRU* pstFtmSynInfo           = ftm_GetSynMainInfo();
    
    pstFtmSynInfo->ulCurCmdStepsFlag |= CT_S_STEPS_DONE_SSYNC_IND; /* �����ѳɹ��ϱ���־ */
	pstFtmSynInfo->stSsyncRdCnf.ulStatus = pstSsyncInd->ulStatus;
            
    return ERR_MSP_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxbw_store
 ��������  : �������
 �������  : ucStoreType �������� 
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_stxbw_store(VOS_UINT8 ucStoreType, FTM_SET_STXBW_REQ_STRU* pstReq)
{
    static FTM_SET_STXBW_REQ_STRU stReq = { 0 };    
    FTM_SYN_INFO_STRU* pstFtmSynInfo    = ftm_GetSynMainInfo();
    
    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {       
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_STXBW_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else 
    {
        pstFtmSynInfo->ulCurCmdStepsFlag |= CT_S_STEPS_DONE_STXBW;
        pstFtmSynInfo->stStxbwRdCnf.ulBandwide = stReq.ulBandwide;
    }
    
    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxbw_setcnf
 ��������  : ����ID_MSG_FTM_SET_STXBW_CNF
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_stxbw_setcnf(VOS_UINT32 ulErrCode)
{  
    FTM_SET_STXBW_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_STXBW_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_STXBW_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxbw_read
 ��������  : ID_MSG_FTM_RD_STXBW_REQ ������
 �������  : pParam FTM_RD_STXBW_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_stxbw_read(VOID* pParam)
{ 
    FTM_SYN_INFO_STRU* pstFtmSynInfo = ftm_GetSynMainInfo();
    FTM_RD_STXBW_CNF_STRU stRdCnf    = { 0 };

    stRdCnf.ulErrCode  = ERR_MSP_SUCCESS;
    stRdCnf.ulBandwide = pstFtmSynInfo->stStxbwRdCnf.ulBandwide;   
           
    return ftm_comm_send(ID_MSG_FTM_RD_STXBW_CNF, (VOS_UINT32)&stRdCnf, 
        sizeof(FTM_RD_STXBW_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxbw_set
 ��������  : ID_MSG_FTM_SET_STXBW_REQ ������
             ��DSP����OM_PHY_SYN_STXBW_SET_REQԭ��
 �������  : pParam FTM_SET_STXBW_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_stxbw_set(VOS_VOID* pParam)
{ 
    FTM_SET_STXBW_REQ_STRU* pstFtmReq        = (FTM_SET_STXBW_REQ_STRU*)pParam;
    OM_PHY_SYN_STXBW_SET_REQ_STRU stReqToDsp = { 0 };
    
    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if((ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
        || (!ftm_CheckSynCmdSteps(CT_S_STEPS_DONE_TMODE_7_REQ)))
    {
        return at_ftm_stxbw_setcnf(ERR_MSP_UE_MODE_ERR);
    }
    
    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId    = OM_PHY_SYN_STXBW_SET_REQ;
    stReqToDsp.usBandwide = (VOS_UINT16)pstFtmReq->ulBandwide;

    if(ERR_MSP_SUCCESS != ftm_mailbox_ltebt_write(&stReqToDsp, sizeof(OM_PHY_SYN_STXBW_SET_REQ_STRU)))
    {
        return at_ftm_stxbw_setcnf(ERR_MSP_UNKNOWN);
    }

    at_ftm_stxbw_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);      
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxbw_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_stxbw_timeout(VOS_VOID)
{
    return at_ftm_stxbw_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxbw_dspcnf
 ��������  : DSPԭ��PHY_OM_SYN_STXBW_SET_CNF������
 �������  : pParam PHY_OM_SYN_STXBW_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_stxbw_dspcnf(VOS_VOID* pParam)
{
    
    at_ftm_stxbw_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_stxbw_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxchan_store
 ��������  : �������
 �������  : ucStoreType �������� 
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_stxchan_store(VOS_UINT8 ucStoreType, FTM_SET_STXCHAN_REQ_STRU* pstReq)
{
    static FTM_SET_STXCHAN_REQ_STRU stReq = { 0 };    
    FTM_SYN_INFO_STRU* pstFtmSynInfo      = ftm_GetSynMainInfo();
    
    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {       
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_STXCHAN_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else 
    {
        pstFtmSynInfo->ulCurCmdStepsFlag          |= CT_S_STEPS_DONE_STXCHAN;
        pstFtmSynInfo->stStxchanRdCnf.ulStxChannel = stReq.ulStxChannel;
    }
    
    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxchan_setcnf
 ��������  : ����ID_MSG_FTM_SET_STXCHAN_CNF
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_stxchan_setcnf(VOS_UINT32 ulErrCode)
{  
    FTM_SET_STXCHAN_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_STXCHAN_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_STXCHAN_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxchan_read
 ��������  : ID_MSG_FTM_RD_STXCHAN_REQ ������
 �������  : pParam FTM_RD_STXCHAN_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_stxchan_read(VOID* pParam)
{ 
    FTM_SYN_INFO_STRU* pstFtmSynInfo   = ftm_GetSynMainInfo();
    FTM_RD_STXCHAN_CNF_STRU stRdCnf    = { 0 };

    stRdCnf.ulErrCode    = ERR_MSP_SUCCESS;
    stRdCnf.ulStxChannel = pstFtmSynInfo->stStxchanRdCnf.ulStxChannel;   
           
    return ftm_comm_send(ID_MSG_FTM_RD_STXCHAN_CNF, (VOS_UINT32)&stRdCnf, 
        sizeof(FTM_RD_STXCHAN_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxchan_set
 ��������  : ID_MSG_FTM_SET_STXCHAN_REQ ������
             ��DSP����OM_PHY_SYN_STXCHAN_SET_REQԭ��
 �������  : pParam FTM_SET_STXCHAN_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_stxchan_set(VOS_VOID* pParam)
{ 
    FTM_SET_STXCHAN_REQ_STRU* pstFtmReq        = (FTM_SET_STXCHAN_REQ_STRU*)pParam;
    OM_PHY_SYN_STXCHAN_SET_REQ_STRU stReqToDsp = { 0 };
    
    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if((ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
        || (!ftm_CheckSynCmdSteps(CT_S_STEPS_DONE_TMODE_7_REQ)))
    {
        return at_ftm_stxchan_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    if(!ftm_CheckSynCmdSteps(CT_S_STEPS_DONE_SSYNC))
    {
        return at_ftm_stxchan_setcnf(ERR_MSP_INVALID_PARAMETER);
    }
    
    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId     = OM_PHY_SYN_STXCHAN_SET_REQ;
    stReqToDsp.usUlchannel = (VOS_UINT16)pstFtmReq->ulStxChannel;

    if(ERR_MSP_SUCCESS != ftm_mailbox_ltebt_write(&stReqToDsp, sizeof(OM_PHY_SYN_STXCHAN_SET_REQ_STRU)))
    {
        return at_ftm_stxchan_setcnf(ERR_MSP_UNKNOWN);
    }

    at_ftm_stxchan_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);      
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxchan_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_stxchan_timeout(VOS_VOID)
{
    return at_ftm_stxchan_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxchan_dspcnf
 ��������  : DSPԭ��PHY_OM_SYN_STXCHAN_SET_CNF������
 �������  : pParam PHY_OM_SYN_STXCHAN_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_stxchan_dspcnf(VOS_VOID* pParam)
{
    
    at_ftm_stxchan_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_stxchan_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_ssubframe_store
 ��������  : �������
 �������  : ucStoreType �������� 
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_ssubframe_store(VOS_UINT8 ucStoreType, FTM_SET_SSUBFRAME_REQ_STRU* pstReq)
{
    static FTM_SET_SSUBFRAME_REQ_STRU stReq = { 0 };    
    FTM_SYN_INFO_STRU* pstFtmSynInfo        = ftm_GetSynMainInfo();
    
    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {       
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_SSUBFRAME_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else 
    {
        pstFtmSynInfo->ulCurCmdStepsFlag                 |= CT_S_STEPS_DONE_SSUBFRAME;
        pstFtmSynInfo->stSsubframeRdCnf.usSubFrameAssign  = stReq.usSubFrameAssign;
		pstFtmSynInfo->stSsubframeRdCnf.usSubFramePattern = stReq.usSubFramePattern;
    }
    
    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_ssubframe_setcnf
 ��������  : ����ID_MSG_FTM_SET_SSUBFRAME_CNF
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_ssubframe_setcnf(VOS_UINT32 ulErrCode)
{  
    FTM_SET_SSUBFRAME_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_SSUBFRAME_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_SSUBFRAME_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_ssubframe_read
 ��������  : ID_MSG_FTM_RD_SSUBFRAME_REQ ������
 �������  : pParam FTM_RD_SSUBFRAME_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_ssubframe_read(VOID* pParam)
{ 
    FTM_SYN_INFO_STRU* pstFtmSynInfo     = ftm_GetSynMainInfo();
    FTM_RD_SSUBFRAME_CNF_STRU stRdCnf    = { 0 };

    stRdCnf.ulErrCode         = ERR_MSP_SUCCESS;
    stRdCnf.usSubFrameAssign  = pstFtmSynInfo->stSsubframeRdCnf.usSubFrameAssign;
    stRdCnf.usSubFramePattern = pstFtmSynInfo->stSsubframeRdCnf.usSubFramePattern;
           
    return ftm_comm_send(ID_MSG_FTM_RD_SSUBFRAME_CNF, (VOS_UINT32)&stRdCnf, 
        sizeof(FTM_RD_SSUBFRAME_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_ssubframe_set
 ��������  : ID_MSG_FTM_SET_SSUBFRAME_REQ ������
             ��DSP����OM_PHY_SYN_SSUBFRAME_SET_REQԭ��
 �������  : pParam FTM_SET_SSUBFRAME_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_ssubframe_set(VOS_VOID* pParam)
{ 
    FTM_SET_SSUBFRAME_REQ_STRU* pstFtmReq        = (FTM_SET_SSUBFRAME_REQ_STRU*)pParam;
    OM_PHY_SYN_SSUBFRAME_SET_REQ_STRU stReqToDsp = { 0 };
    
    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if((ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
        || (!ftm_CheckSynCmdSteps(CT_S_STEPS_DONE_TMODE_7_REQ)))
    {
        return at_ftm_ssubframe_setcnf(ERR_MSP_UE_MODE_ERR);
    }
    
    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId           = OM_PHY_SYN_SSUBFRAME_SET_REQ;
    stReqToDsp.usSubFrameAssign  = pstFtmReq->usSubFrameAssign;
	stReqToDsp.usSubFramePattern = pstFtmReq->usSubFramePattern;

    if(ERR_MSP_SUCCESS != ftm_mailbox_ltebt_write(&stReqToDsp, sizeof(OM_PHY_SYN_SSUBFRAME_SET_REQ_STRU)))
    {
        return at_ftm_ssubframe_setcnf(ERR_MSP_UNKNOWN);
    }

    at_ftm_ssubframe_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);      
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_ssubframe_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_ssubframe_timeout(VOS_VOID)
{
    return at_ftm_ssubframe_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_ssubframe_dspcnf
 ��������  : DSPԭ��PHY_OM_SYN_SSUBFRAME_SET_CNF������
 �������  : pParam PHY_OM_SYN_SSUBFRAME_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_ssubframe_dspcnf(VOS_VOID* pParam)
{
    
    at_ftm_ssubframe_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_ssubframe_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_spara_store
 ��������  : �������
 �������  : ucStoreType �������� 
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_spara_store(VOS_UINT8 ucStoreType, FTM_SET_SPARA_REQ_STRU* pstReq)
{
    static FTM_SET_SPARA_REQ_STRU stReq = { 0 };    
    FTM_SYN_INFO_STRU* pstFtmSynInfo    = ftm_GetSynMainInfo();
    
    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {       
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_SPARA_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else 
    {
       pstFtmSynInfo->ulCurCmdStepsFlag |= CT_S_STEPS_DONE_SPARA;

       /* ������ֲ����ԭ��, ���Ǵ˶δ���ʵ����Щ���� */
	   if(pstFtmSynInfo->stSparaRdCnf.ulTypeNum >=32)
	   {
           pstFtmSynInfo->stSparaRdCnf.ulTypeNum = 0;
	   }
       pstFtmSynInfo->stSparaRdCnf.stSpara[pstFtmSynInfo->stSparaRdCnf.ulTypeNum].usType  = stReq.usType;
       pstFtmSynInfo->stSparaRdCnf.stSpara[pstFtmSynInfo->stSparaRdCnf.ulTypeNum].usValue = stReq.usValue;       
	   pstFtmSynInfo->stSparaRdCnf.ulTypeNum++;
    }
    
    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_spara_setcnf
 ��������  : ����ID_MSG_FTM_SET_SPARA_CNF
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_spara_setcnf(VOS_UINT32 ulErrCode)
{  
    FTM_SET_SPARA_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_SPARA_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_SPARA_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_spara_read
 ��������  : ID_MSG_FTM_RD_SPARA_REQ ������
 �������  : pParam FTM_RD_SPARA_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_spara_read(VOID* pParam)
{ 
    VOS_UINT32 i = 0;
    FTM_SYN_INFO_STRU* pstFtmSynInfo    = ftm_GetSynMainInfo();
    FTM_RD_SPARA_CNF_TOTAL_STRU stRdCnf = { 0 };

    /* ������ֲ����ԭ��, ���Ǵ˶δ���ʵ����Щ���� */
    stRdCnf.ulErrCode = ERR_MSP_SUCCESS;
    stRdCnf.ulTypeNum = pstFtmSynInfo->stSparaRdCnf.ulTypeNum;

    for(i=0; i<stRdCnf.ulTypeNum; i++)
    {
        stRdCnf.stSpara[i].usType  = pstFtmSynInfo->stSparaRdCnf.stSpara[i].usType;
        stRdCnf.stSpara[i].usValue = pstFtmSynInfo->stSparaRdCnf.stSpara[i].usValue;
    }
           
    return ftm_comm_send(ID_MSG_FTM_RD_SPARA_CNF, (VOS_UINT32)&stRdCnf, 
        sizeof(FTM_RD_SPARA_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_spara_set
 ��������  : ID_MSG_FTM_SET_SPARA_REQ ������
             ��DSP����OM_PHY_SYN_SPARA_SET_REQԭ��
 �������  : pParam FTM_SET_SPARA_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_spara_set(VOS_VOID* pParam)
{ 
    FTM_SET_SPARA_REQ_STRU* pstFtmReq        = (FTM_SET_SPARA_REQ_STRU*)pParam;
    OM_PHY_SYN_SPARA_SET_REQ_STRU stReqToDsp = { 0 };
    FTM_SYN_INFO_STRU* pstFtmSynInfo         = ftm_GetSynMainInfo();
	FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();
    FCHAN_MODE_ENUM fchanMode = pstFtmFastCtInfo->enCurMode;

    
    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if((ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
        || (!ftm_CheckSynCmdSteps(CT_S_STEPS_DONE_TMODE_7_REQ)))
    {
        return at_ftm_spara_setcnf(ERR_MSP_UE_MODE_ERR);
    }
	if (EN_FCHAN_MODE_TD_SCDMA == fchanMode)
    {
        HAL_SDMLOG("-----[%s]:save type=%d,value=%d \n", __FUNCTION__,pstFtmReq->usType,pstFtmReq->usValue);
        /*bt tds nosig ����cellID, ֱ�ӷ��سɹ�*/
        pstFtmSynInfo->stFtmSparaInfo.usType = pstFtmReq->usType;
        pstFtmSynInfo->stFtmSparaInfo.usValue = pstFtmReq->usValue;
	  return at_ftm_spara_setcnf(ERR_MSP_SUCCESS);
    }
    
    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId = OM_PHY_SYN_SPARA_SET_REQ;
    stReqToDsp.usType  = pstFtmReq->usType;
    stReqToDsp.usValue = pstFtmReq->usValue;

    if(ERR_MSP_SUCCESS != ftm_mailbox_ltebt_write(&stReqToDsp, sizeof(OM_PHY_SYN_SPARA_SET_REQ_STRU)))
    {
        return at_ftm_spara_setcnf(ERR_MSP_UNKNOWN);
    }

    at_ftm_spara_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);      
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_spara_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_spara_timeout(VOS_VOID)
{
    return at_ftm_spara_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_spara_dspcnf
 ��������  : DSPԭ��PHY_OM_SYN_SPARA_SET_CNF������
 �������  : pParam PHY_OM_SYN_SPARA_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_spara_dspcnf(VOS_VOID* pParam)
{
    
    at_ftm_spara_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_spara_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_ssegnum_store
 ��������  : �������
 �������  : ucStoreType �������� 
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_ssegnum_store(VOS_UINT8 ucStoreType, FTM_SET_SSEGNUM_REQ_STRU* pstReq)
{
    static FTM_SET_SSEGNUM_REQ_STRU stReq = { 0 };    
    FTM_SYN_INFO_STRU* pstFtmSynInfo      = ftm_GetSynMainInfo();
    
    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {       
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_SSEGNUM_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else 
    {
       pstFtmSynInfo->ulCurCmdStepsFlag      |= CT_S_STEPS_DONE_SSEGNUM;
       pstFtmSynInfo->stSsegnumRdCnf.usSegNum = stReq.usSegNum;
    }
    
    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_ssegnum_setcnf
 ��������  : ����ID_MSG_FTM_SET_SSEGNUM_CNF
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_ssegnum_setcnf(VOS_UINT32 ulErrCode)
{  
    FTM_SET_SSEGNUM_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_SSEGNUM_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_SSEGNUM_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_ssegnum_read
 ��������  : ID_MSG_FTM_RD_SSEGNUM_REQ ������
 �������  : pParam FTM_RD_SSEGNUM_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_ssegnum_read(VOID* pParam)
{ 
    FTM_SYN_INFO_STRU* pstFtmSynInfo   = ftm_GetSynMainInfo();
    FTM_RD_SSEGNUM_CNF_STRU stRdCnf    = { 0 };

    stRdCnf.ulErrCode = ERR_MSP_SUCCESS;
    stRdCnf.usSegNum  = pstFtmSynInfo->stSsegnumRdCnf.usSegNum;  
           
    return ftm_comm_send(ID_MSG_FTM_RD_SSEGNUM_CNF, (VOS_UINT32)&stRdCnf, 
        sizeof(FTM_RD_SSEGNUM_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_ssegnum_set
 ��������  : ID_MSG_FTM_SET_SSEGNUM_REQ ������
             ��DSP����OM_PHY_SYN_SSEGNUM_SET_REQԭ��
 �������  : pParam FTM_SET_SSEGNUM_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_ssegnum_set(VOS_VOID* pParam)
{ 
    FTM_SET_SSEGNUM_REQ_STRU* pstFtmReq        = (FTM_SET_SSEGNUM_REQ_STRU*)pParam;
    OM_PHY_SYN_SSEGNUM_SET_REQ_STRU stReqToDsp = { 0 };
    
    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if((ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
        || (!ftm_CheckSynCmdSteps(CT_S_STEPS_DONE_TMODE_7_REQ)))
    {
        return at_ftm_ssegnum_setcnf(ERR_MSP_UE_MODE_ERR);
    }
    
    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId  = OM_PHY_SYN_SSEGNUM_SET_REQ;
    stReqToDsp.usSegNum = (VOS_UINT16)pstFtmReq->usSegNum;

    if(ERR_MSP_SUCCESS != ftm_mailbox_ltebt_write(&stReqToDsp, sizeof(OM_PHY_SYN_SSEGNUM_SET_REQ_STRU)))
    {
        return at_ftm_ssegnum_setcnf(ERR_MSP_UNKNOWN);
    }

    at_ftm_ssegnum_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);      
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_ssegnum_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_ssegnum_timeout(VOS_VOID)
{
    return at_ftm_ssegnum_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_ssegnum_dspcnf
 ��������  : DSPԭ��PHY_OM_SYN_SSEGNUM_SET_CNF������
 �������  : pParam PHY_OM_SYN_SSEGNUM_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_ssegnum_dspcnf(VOS_VOID* pParam)
{
    
    at_ftm_ssegnum_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_ssegnum_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxmodus_store
 ��������  : �������
 �������  : ucStoreType �������� 
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_stxmodus_store(VOS_UINT8 ucStoreType, FTM_SET_STXMODUS_REQ_STRU* pstReq)
{
    static FTM_SET_STXMODUS_REQ_STRU stReq = { 0 };    
    FTM_SYN_INFO_STRU* pstFtmSynInfo       = ftm_GetSynMainInfo();
    
    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {       
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_STXMODUS_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else 
    {
       pstFtmSynInfo->ulCurCmdStepsFlag               |= CT_S_STEPS_DONE_STXMODUS;
       pstFtmSynInfo->stStxmodusRdCnf.usmodulution_num = stReq.usmodulution_num;
	   (VOS_VOID)MSP_MEMCPY(pstFtmSynInfo->stStxmodusRdCnf.usmodulation_list, stReq.usmodulation_list, sizeof(stReq.usmodulation_list));
    }
    
    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxmodus_setcnf
 ��������  : ����ID_MSG_FTM_SET_STXMODUS_CNF
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_stxmodus_setcnf(VOS_UINT32 ulErrCode)
{  
    FTM_SET_STXMODUS_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_STXMODUS_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_STXMODUS_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxmodus_read
 ��������  : ID_MSG_FTM_RD_STXMODUS_REQ ������
 �������  : pParam FTM_RD_STXMODUS_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_stxmodus_read(VOID* pParam)
{ 
    FTM_SYN_INFO_STRU* pstFtmSynInfo    = ftm_GetSynMainInfo();
    FTM_RD_STXMODUS_CNF_STRU stRdCnf    = { 0 };

    stRdCnf.ulErrCode        = ERR_MSP_SUCCESS;
    stRdCnf.usmodulution_num = pstFtmSynInfo->stStxmodusRdCnf.usmodulution_num;
	(VOS_VOID)MSP_MEMCPY(stRdCnf.usmodulation_list, pstFtmSynInfo->stStxmodusRdCnf.usmodulation_list, sizeof(stRdCnf.usmodulation_list));
           
    return ftm_comm_send(ID_MSG_FTM_RD_STXMODUS_CNF, (VOS_UINT32)&stRdCnf, 
        sizeof(FTM_RD_STXMODUS_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxmodus_set
 ��������  : ID_MSG_FTM_SET_STXMODUS_REQ ������
             ��DSP����OM_PHY_SYN_STXMODUS_SET_REQԭ��
 �������  : pParam FTM_SET_STXMODUS_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_stxmodus_set(VOS_VOID* pParam)
{ 
    FTM_SET_STXMODUS_REQ_STRU* pstFtmReq        = (FTM_SET_STXMODUS_REQ_STRU*)pParam;
    OM_PHY_SYN_STXMODUS_SET_REQ_STRU stReqToDsp = { 0 };
    
    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if((ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
        || (!ftm_CheckSynCmdSteps(CT_S_STEPS_DONE_TMODE_7_REQ)))
    {
        return at_ftm_stxmodus_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    if(!ftm_CheckSynCmdSteps(CT_S_STEPS_DONE_SSYNC))
    {
        return at_ftm_stxmodus_setcnf(ERR_MSP_INVALID_PARAMETER);
    }
    
    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId          = OM_PHY_SYN_STXMODUS_SET_REQ;
    stReqToDsp.usModulution_num = (VOS_UINT16)pstFtmReq->usmodulution_num;
    (VOS_VOID)MSP_MEMCPY(stReqToDsp.usModulation_list, pstFtmReq->usmodulation_list, sizeof(stReqToDsp.usModulation_list));

    if(ERR_MSP_SUCCESS != ftm_mailbox_ltebt_write(&stReqToDsp, sizeof(OM_PHY_SYN_STXMODUS_SET_REQ_STRU)))
    {
        return at_ftm_stxmodus_setcnf(ERR_MSP_UNKNOWN);
    }

    at_ftm_stxmodus_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);      
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxmodus_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_stxmodus_timeout(VOS_VOID)
{
    return at_ftm_stxmodus_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxmodus_dspcnf
 ��������  : DSPԭ��PHY_OM_SYN_STXMODUS_SET_CNF������
 �������  : pParam PHY_OM_SYN_STXMODUS_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_stxmodus_dspcnf(VOS_VOID* pParam)
{
    
    at_ftm_stxmodus_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_stxmodus_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxrbnums_store
 ��������  : �������
 �������  : ucStoreType �������� 
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_stxrbnums_store(VOS_UINT8 ucStoreType, FTM_SET_STXRBNUMS_REQ_STRU* pstReq)
{
    static FTM_SET_STXRBNUMS_REQ_STRU stReq = { 0 };    
    FTM_SYN_INFO_STRU* pstFtmSynInfo        = ftm_GetSynMainInfo();
    
    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {       
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_STXRBNUMS_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else 
    {
        pstFtmSynInfo->ulCurCmdStepsFlag        |= CT_S_STEPS_DONE_STXRBNUMS;
        pstFtmSynInfo->stStxrbnumsRdCnf.usrb_num = stReq.usrb_num;
        (VOS_VOID)MSP_MEMCPY(pstFtmSynInfo->stStxrbnumsRdCnf.usrb_list, stReq.usrb_list, sizeof(stReq.usrb_list));
    }
    
    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxrbnums_setcnf
 ��������  : ����ID_MSG_FTM_SET_STXRBNUMS_CNF
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_stxrbnums_setcnf(VOS_UINT32 ulErrCode)
{  
    FTM_SET_STXRBNUMS_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_STXRBNUMS_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_STXRBNUMS_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxrbnums_read
 ��������  : ID_MSG_FTM_RD_STXRBNUMS_REQ ������
 �������  : pParam FTM_RD_STXRBNUMS_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_stxrbnums_read(VOID* pParam)
{ 
    FTM_SYN_INFO_STRU* pstFtmSynInfo     = ftm_GetSynMainInfo();
    FTM_RD_STXRBNUMS_CNF_STRU stRdCnf    = { 0 };

    stRdCnf.ulErrCode = ERR_MSP_SUCCESS;
    stRdCnf.usrb_num  = pstFtmSynInfo->stStxrbnumsRdCnf.usrb_num;
    (VOS_VOID)MSP_MEMCPY(stRdCnf.usrb_list, pstFtmSynInfo->stStxrbnumsRdCnf.usrb_list, sizeof(stRdCnf.usrb_list));
           
    return ftm_comm_send(ID_MSG_FTM_RD_STXRBNUMS_CNF, (VOS_UINT32)&stRdCnf, 
        sizeof(FTM_RD_STXRBNUMS_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxrbnums_set
 ��������  : ID_MSG_FTM_SET_STXRBNUMS_REQ ������
             ��DSP����OM_PHY_SYN_STXRBNUMS_SET_REQԭ��
 �������  : pParam FTM_SET_STXRBNUMS_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_stxrbnums_set(VOS_VOID* pParam)
{ 
    FTM_SET_STXRBNUMS_REQ_STRU* pstFtmReq        = (FTM_SET_STXRBNUMS_REQ_STRU*)pParam;
    OM_PHY_SYN_STXRBNUMS_SET_REQ_STRU stReqToDsp = { 0 };
    
    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if((ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
        || (!ftm_CheckSynCmdSteps(CT_S_STEPS_DONE_TMODE_7_REQ)))
    {
        return at_ftm_stxrbnums_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    /* ������� */
    if(!ftm_CheckSynCmdSteps(CT_S_STEPS_DONE_SSYNC))
    {
        return at_ftm_stxrbnums_setcnf(ERR_MSP_INVALID_PARAMETER);
    }
    
    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId   = OM_PHY_SYN_STXRBNUMS_SET_REQ;
    stReqToDsp.usRb_num  = (VOS_UINT16)pstFtmReq->usrb_num;
    (VOS_VOID)MSP_MEMCPY(stReqToDsp.usrb_list, pstFtmReq->usrb_list, sizeof(stReqToDsp.usrb_list));

    if(ERR_MSP_SUCCESS != ftm_mailbox_ltebt_write(&stReqToDsp, sizeof(OM_PHY_SYN_STXRBNUMS_SET_REQ_STRU)))
    {
        return at_ftm_stxrbnums_setcnf(ERR_MSP_UNKNOWN);
    }

    at_ftm_stxrbnums_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);      
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxrbnums_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_stxrbnums_timeout(VOS_VOID)
{
    return at_ftm_stxrbnums_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxrbnums_dspcnf
 ��������  : DSPԭ��PHY_OM_SYN_STXRBNUMS_SET_CNF������
 �������  : pParam PHY_OM_SYN_STXRBNUMS_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_stxrbnums_dspcnf(VOS_VOID* pParam)
{
    
    at_ftm_stxrbnums_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_stxrbnums_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxrbposs_store
 ��������  : �������
 �������  : ucStoreType �������� 
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_stxrbposs_store(VOS_UINT8 ucStoreType, FTM_SET_STXRBPOSS_REQ_STRU* pstReq)
{
    static FTM_SET_STXRBPOSS_REQ_STRU stReq = { 0 };    
    FTM_SYN_INFO_STRU* pstFtmSynInfo        = ftm_GetSynMainInfo();
    
    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {       
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_STXRBPOSS_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else 
    {
        pstFtmSynInfo->ulCurCmdStepsFlag           |= CT_S_STEPS_DONE_STXRBPOSS;
        pstFtmSynInfo->stStxrbpossRdCnf.usrbpos_num = stReq.usrbpos_num;
		(VOS_VOID)MSP_MEMCPY(pstFtmSynInfo->stStxrbpossRdCnf.usrbpos_list, stReq.usrbpos_list, sizeof(stReq.usrbpos_list));
    }
    
    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxrbposs_setcnf
 ��������  : ����ID_MSG_FTM_SET_STXRBPOSS_CNF
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_stxrbposs_setcnf(VOS_UINT32 ulErrCode)
{  
    FTM_SET_STXRBPOSS_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_STXRBPOSS_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_STXRBPOSS_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxrbposs_read
 ��������  : ID_MSG_FTM_RD_STXRBPOSS_REQ ������
 �������  : pParam FTM_RD_STXRBPOSS_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_stxrbposs_read(VOID* pParam)
{ 
    FTM_SYN_INFO_STRU* pstFtmSynInfo     = ftm_GetSynMainInfo();
    FTM_RD_STXRBPOSS_CNF_STRU stRdCnf    = { 0 };

    stRdCnf.ulErrCode   = ERR_MSP_SUCCESS;
    stRdCnf.usrbpos_num = pstFtmSynInfo->stStxrbpossRdCnf.usrbpos_num;
	(VOS_VOID)MSP_MEMCPY(stRdCnf.usrbpos_list, pstFtmSynInfo->stStxrbpossRdCnf.usrbpos_list, sizeof(stRdCnf.usrbpos_list));
           
    return ftm_comm_send(ID_MSG_FTM_RD_STXRBPOSS_CNF, (VOS_UINT32)&stRdCnf, 
        sizeof(FTM_RD_STXRBPOSS_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxrbposs_set
 ��������  : ID_MSG_FTM_SET_STXRBPOSS_REQ ������
             ��DSP����OM_PHY_SYN_STXRBPOSS_SET_REQԭ��
 �������  : pParam FTM_SET_STXRBPOSS_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_stxrbposs_set(VOS_VOID* pParam)
{ 
    FTM_SET_STXRBPOSS_REQ_STRU* pstFtmReq        = (FTM_SET_STXRBPOSS_REQ_STRU*)pParam;
    OM_PHY_SYN_STXRBPOSS_SET_REQ_STRU stReqToDsp = { 0 };
    
    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if((ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
        || (!ftm_CheckSynCmdSteps(CT_S_STEPS_DONE_TMODE_7_REQ)))
    {
        return at_ftm_stxrbposs_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    /* ������� */
    if(!ftm_CheckSynCmdSteps(CT_S_STEPS_DONE_SSYNC))
    {
        return at_ftm_stxrbposs_setcnf(ERR_MSP_INVALID_PARAMETER);
    }
    
    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId     = OM_PHY_SYN_STXRBPOSS_SET_REQ;
    stReqToDsp.usRbpos_num = (VOS_UINT16)pstFtmReq->usrbpos_num;
    (VOS_VOID)MSP_MEMCPY(stReqToDsp.usrbpos_list, pstFtmReq->usrbpos_list, sizeof(stReqToDsp.usrbpos_list));
    if(ERR_MSP_SUCCESS != ftm_mailbox_ltebt_write(&stReqToDsp, sizeof(OM_PHY_SYN_STXRBPOSS_SET_REQ_STRU)))
    {
        return at_ftm_stxrbposs_setcnf(ERR_MSP_UNKNOWN);
    }

    at_ftm_stxrbposs_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);      
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxrbposs_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_stxrbposs_timeout(VOS_VOID)
{
    return at_ftm_stxrbposs_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxrbposs_dspcnf
 ��������  : DSPԭ��PHY_OM_SYN_STXRBPOSS_SET_CNF������
 �������  : pParam PHY_OM_SYN_STXRBPOSS_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_stxrbposs_dspcnf(VOS_VOID* pParam)
{
    
    at_ftm_stxrbposs_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_stxrbposs_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxpows_store
 ��������  : �������
 �������  : ucStoreType �������� 
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_stxpows_store(VOS_UINT8 ucStoreType, FTM_SET_STXPOWS_REQ_STRU* pstReq)
{
    static FTM_SET_STXPOWS_REQ_STRU stReq = { 0 };    
    FTM_SYN_INFO_STRU* pstFtmSynInfo      = ftm_GetSynMainInfo();
    
    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {       
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_STXPOWS_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else 
    {
        pstFtmSynInfo->ulCurCmdStepsFlag         |= CT_S_STEPS_DONE_STXPOWS;
        pstFtmSynInfo->stStxpowsRdCnf.uspower_num = stReq.uspower_num;
		(VOS_VOID)MSP_MEMCPY(pstFtmSynInfo->stStxpowsRdCnf.uspower_list, stReq.uspower_list, sizeof(stReq.uspower_list));
    }
    
    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxpows_setcnf
 ��������  : ����ID_MSG_FTM_SET_STXPOWS_CNF
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_stxpows_setcnf(VOS_UINT32 ulErrCode)
{  
    FTM_SET_STXPOWS_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_STXPOWS_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_STXPOWS_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxpows_read
 ��������  : ID_MSG_FTM_RD_STXPOWS_REQ ������
 �������  : pParam FTM_RD_STXPOWS_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_stxpows_read(VOID* pParam)
{ 
    FTM_SYN_INFO_STRU* pstFtmSynInfo   = ftm_GetSynMainInfo();
    FTM_RD_STXPOWS_CNF_STRU stRdCnf    = { 0 };

    stRdCnf.ulErrCode   = ERR_MSP_SUCCESS;
    stRdCnf.uspower_num = pstFtmSynInfo->stStxpowsRdCnf.uspower_num;
    (VOS_VOID)MSP_MEMCPY(stRdCnf.uspower_list, pstFtmSynInfo->stStxpowsRdCnf.uspower_list, sizeof(stRdCnf.uspower_list));
           
    return ftm_comm_send(ID_MSG_FTM_RD_STXPOWS_CNF, (VOS_UINT32)&stRdCnf, 
        sizeof(FTM_RD_STXPOWS_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxpows_set
 ��������  : ID_MSG_FTM_SET_STXPOWS_REQ ������
             ��DSP����OM_PHY_SYN_STXPOWS_SET_REQԭ��
 �������  : pParam FTM_SET_STXPOWS_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_stxpows_set(VOS_VOID* pParam)
{ 
    FTM_SET_STXPOWS_REQ_STRU* pstFtmReq        = (FTM_SET_STXPOWS_REQ_STRU*)pParam;
    OM_PHY_SYN_STXPOWS_SET_REQ_STRU stReqToDsp = { 0 };
    
    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if((ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
        || (!ftm_CheckSynCmdSteps(CT_S_STEPS_DONE_TMODE_7_REQ)))
    {
        return at_ftm_stxpows_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    /* ������� */
    if(!ftm_CheckSynCmdSteps(CT_S_STEPS_DONE_SSYNC))
    {
        return at_ftm_stxpows_setcnf(ERR_MSP_INVALID_PARAMETER);
    }
    
    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId   = OM_PHY_SYN_STXPOWS_SET_REQ;
    stReqToDsp.ulPow_num = (VOS_UINT16)pstFtmReq->uspower_num;
    (VOS_VOID)MSP_MEMCPY(stReqToDsp.slPow_list, pstFtmReq->uspower_list, sizeof(stReqToDsp.slPow_list));

    if(ERR_MSP_SUCCESS != ftm_mailbox_ltebt_write(&stReqToDsp, sizeof(OM_PHY_SYN_STXPOWS_SET_REQ_STRU)))
    {
        return at_ftm_stxpows_setcnf(ERR_MSP_UNKNOWN);
    }

    at_ftm_stxpows_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);      
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxpows_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_stxpows_timeout(VOS_VOID)
{
    return at_ftm_stxpows_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxpows_dspcnf
 ��������  : DSPԭ��PHY_OM_SYN_STXPOWS_SET_CNF������
 �������  : pParam PHY_OM_SYN_STXPOWS_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_stxpows_dspcnf(VOS_VOID* pParam)
{
    
    at_ftm_stxpows_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_stxpows_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxchantypes_store
 ��������  : �������
 �������  : ucStoreType �������� 
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_stxchantypes_store(VOS_UINT8 ucStoreType, FTM_SET_STXCHANTYPES_REQ_STRU* pstReq)
{
    static FTM_SET_STXCHANTYPES_REQ_STRU stReq = { 0 };    
    FTM_SYN_INFO_STRU* pstFtmSynInfo           = ftm_GetSynMainInfo();
    
    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {       
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_STXCHANTYPES_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else 
    {
        pstFtmSynInfo->ulCurCmdStepsFlag             |= CT_S_STEPS_DONE_STXCHANTYPES;
        pstFtmSynInfo->stStxchantypesRdCnf.ustype_num = stReq.ustype_num;
		(VOS_VOID)MSP_MEMCPY(pstFtmSynInfo->stStxchantypesRdCnf.ustype_list, stReq.ustype_list, sizeof(stReq.ustype_list));
    }
    
    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxchantypes_setcnf
 ��������  : ����ID_MSG_FTM_SET_STXCHANTYPES_CNF
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_stxchantypes_setcnf(VOS_UINT32 ulErrCode)
{  
    FTM_SET_STXCHANTYPES_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_STXCHANTYPES_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_STXCHANTYPES_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxchantypes_read
 ��������  : ID_MSG_FTM_RD_STXCHANTYPES_REQ ������
 �������  : pParam FTM_RD_STXCHANTYPES_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_stxchantypes_read(VOID* pParam)
{ 
    FTM_SYN_INFO_STRU* pstFtmSynInfo        = ftm_GetSynMainInfo();
    FTM_RD_STXCHANTYPES_CNF_STRU stRdCnf    = { 0 };

    stRdCnf.ulErrCode  = ERR_MSP_SUCCESS;
    stRdCnf.ustype_num = pstFtmSynInfo->stStxchantypesRdCnf.ustype_num;
	(VOS_VOID)MSP_MEMCPY(stRdCnf.ustype_list, pstFtmSynInfo->stStxchantypesRdCnf.ustype_list, sizeof(stRdCnf.ustype_list));
           
    return ftm_comm_send(ID_MSG_FTM_RD_STXCHANTYPES_CNF, (VOS_UINT32)&stRdCnf, 
        sizeof(FTM_RD_STXCHANTYPES_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxchantypes_set
 ��������  : ID_MSG_FTM_SET_STXCHANTYPES_REQ ������
             ��DSP����OM_PHY_SYN_STXCHANTYPES_SET_REQԭ��
 �������  : pParam FTM_SET_STXCHANTYPES_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_stxchantypes_set(VOS_VOID* pParam)
{ 
    FTM_SET_STXCHANTYPES_REQ_STRU* pstFtmReq        = (FTM_SET_STXCHANTYPES_REQ_STRU*)pParam;
    OM_PHY_SYN_STXCHANTYPES_SET_REQ_STRU stReqToDsp = { 0 };
    
    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if((ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
        || (!ftm_CheckSynCmdSteps(CT_S_STEPS_DONE_TMODE_7_REQ)))
    {
        return at_ftm_stxchantypes_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    /* ������� */
    if(!ftm_CheckSynCmdSteps(CT_S_STEPS_DONE_SSYNC))
    {
        return at_ftm_stxchantypes_setcnf(ERR_MSP_INVALID_PARAMETER);
    }
    
    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId    = OM_PHY_SYN_STXCHANTYPES_SET_REQ;
    stReqToDsp.usType_num = (VOS_UINT16)pstFtmReq->ustype_num;
    (VOS_VOID)MSP_MEMCPY(stReqToDsp.usType_list, pstFtmReq->ustype_list, sizeof(stReqToDsp.usType_list));

    if(ERR_MSP_SUCCESS != ftm_mailbox_ltebt_write(&stReqToDsp, sizeof(OM_PHY_SYN_STXCHANTYPES_SET_REQ_STRU)))
    {
        return at_ftm_stxchantypes_setcnf(ERR_MSP_UNKNOWN);
    }

    at_ftm_stxchantypes_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);      
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxchantypes_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_stxchantypes_timeout(VOS_VOID)
{
    return at_ftm_stxchantypes_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_stxchantypes_dspcnf
 ��������  : DSPԭ��PHY_OM_SYN_STXCHANTYPES_SET_CNF������
 �������  : pParam PHY_OM_SYN_STXCHANTYPES_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_stxchantypes_dspcnf(VOS_VOID* pParam)
{
    
    at_ftm_stxchantypes_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_stxchantypes_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_sseglen_store
 ��������  : �������
 �������  : ucStoreType �������� 
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_sseglen_store(VOS_UINT8 ucStoreType, FTM_SET_SSEGLEN_REQ_STRU* pstReq)
{
    static FTM_SET_SSEGLEN_REQ_STRU stReq = { 0 };    
    FTM_SYN_INFO_STRU* pstFtmSynInfo      = ftm_GetSynMainInfo();
    
    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {       
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_SSEGLEN_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else 
    {        
        pstFtmSynInfo->ulCurCmdStepsFlag           |= CT_S_STEPS_DONE_SSEGLEN;
        pstFtmSynInfo->stSseglenRdCnf.ussegment_len = stReq.ussegment_len;
    }
    
    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_sseglen_setcnf
 ��������  : ����ID_MSG_FTM_SET_SSEGLEN_CNF
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_sseglen_setcnf(VOS_UINT32 ulErrCode)
{  
    FTM_SET_SSEGLEN_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_SSEGLEN_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_SSEGLEN_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_sseglen_read
 ��������  : ID_MSG_FTM_RD_SSEGLEN_REQ ������
 �������  : pParam FTM_RD_SSEGLEN_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_sseglen_read(VOID* pParam)
{ 
    FTM_SYN_INFO_STRU* pstFtmSynInfo   = ftm_GetSynMainInfo();
    FTM_RD_SSEGLEN_CNF_STRU stRdCnf    = { 0 };

    stRdCnf.ulErrCode     = ERR_MSP_SUCCESS;
    stRdCnf.ussegment_len = pstFtmSynInfo->stSseglenRdCnf.ussegment_len;
           
    return ftm_comm_send(ID_MSG_FTM_RD_SSEGLEN_CNF, (VOS_UINT32)&stRdCnf, 
        sizeof(FTM_RD_SSEGLEN_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_sseglen_set
 ��������  : ID_MSG_FTM_SET_SSEGLEN_REQ ������
             ��DSP����OM_PHY_SYN_SSEGLEN_SET_REQԭ��
 �������  : pParam FTM_SET_SSEGLEN_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_sseglen_set(VOS_VOID* pParam)
{ 
    FTM_SET_SSEGLEN_REQ_STRU* pstFtmReq        = (FTM_SET_SSEGLEN_REQ_STRU*)pParam;
    OM_PHY_SYN_SSEGLEN_SET_REQ_STRU stReqToDsp = { 0 };
    
    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if((ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
        || (!ftm_CheckSynCmdSteps(CT_S_STEPS_DONE_TMODE_7_REQ)))
    {
        return at_ftm_sseglen_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    /* ������� */
    if(!ftm_CheckSynCmdSteps(CT_S_STEPS_DONE_SSYNC))
    {
        return at_ftm_sseglen_setcnf(ERR_MSP_INVALID_PARAMETER);
    }
    
    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId       = OM_PHY_SYN_SSEGLEN_SET_REQ;
    stReqToDsp.usSegment_Len = (VOS_UINT16)pstFtmReq->ussegment_len;

    if(ERR_MSP_SUCCESS != ftm_mailbox_ltebt_write(&stReqToDsp, sizeof(OM_PHY_SYN_SSEGLEN_SET_REQ_STRU)))
    {
        return at_ftm_sseglen_setcnf(ERR_MSP_UNKNOWN);
    }

    at_ftm_sseglen_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);      
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_sseglen_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_sseglen_timeout(VOS_VOID)
{
    return at_ftm_sseglen_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_sseglen_dspcnf
 ��������  : DSPԭ��PHY_OM_SYN_SSEGLEN_SET_CNF������
 �������  : pParam PHY_OM_SYN_SSEGLEN_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_sseglen_dspcnf(VOS_VOID* pParam)
{
    
    at_ftm_sseglen_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_sseglen_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_srxset_store
 ��������  : �������
 �������  : ucStoreType �������� 
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_srxset_store(VOS_UINT8 ucStoreType, FTM_SET_SRXSET_REQ_STRU* pstReq)
{
    static FTM_SET_SRXSET_REQ_STRU stReq = { 0 };    
    FTM_SYN_INFO_STRU* pstFtmSynInfo     = ftm_GetSynMainInfo();
    
    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {       
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_SRXSET_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else 
    {        
        pstFtmSynInfo->ulCurCmdStepsFlag     |= CT_S_STEPS_DONE_SRXSET;
        pstFtmSynInfo->stSrxsetRdCnf.usSwitch = stReq.usSwitch;
	    pstFtmSynInfo->stSrxsetRdCnf.sPower   = stReq.sPower;
	    pstFtmSynInfo->stSrxsetRdCnf.usRBNum  = stReq.usRBNum;
	    pstFtmSynInfo->stSrxsetRdCnf.usRBPos  = stReq.usRBPos;
	    pstFtmSynInfo->stSrxsetRdCnf.usMod    = stReq.usMod;
    }
    
    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_srxset_setcnf
 ��������  : ����ID_MSG_FTM_SET_SRXSET_CNF
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_srxset_setcnf(VOS_UINT32 ulErrCode)
{  
    FTM_SET_SRXSET_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_SRXSET_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_SRXSET_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_srxset_read
 ��������  : ID_MSG_FTM_RD_SRXSET_REQ ������
 �������  : pParam FTM_RD_SRXSET_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_srxset_read(VOID* pParam)
{ 
    FTM_SYN_INFO_STRU* pstFtmSynInfo  = ftm_GetSynMainInfo();
    FTM_RD_SRXSET_CNF_STRU stRdCnf    = { 0 };

    stRdCnf.ulErrCode = ERR_MSP_SUCCESS;
    stRdCnf.usSwitch  = pstFtmSynInfo->stSrxsetRdCnf.usSwitch;
	stRdCnf.sPower    = pstFtmSynInfo->stSrxsetRdCnf.sPower;
	stRdCnf.usRBNum   = pstFtmSynInfo->stSrxsetRdCnf.usRBNum;
	stRdCnf.usRBPos   = pstFtmSynInfo->stSrxsetRdCnf.usRBPos;
	stRdCnf.usMod     = pstFtmSynInfo->stSrxsetRdCnf.usMod;
           
    return ftm_comm_send(ID_MSG_FTM_RD_SRXSET_CNF, (VOS_UINT32)&stRdCnf, 
        sizeof(FTM_RD_SRXSET_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_srxset_set
 ��������  : ID_MSG_FTM_SET_SRXSET_REQ ������
             ��DSP����OM_PHY_SYN_SRXSET_SET_REQԭ��
 �������  : pParam FTM_SET_SRXSET_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_srxset_set(VOS_VOID* pParam)
{ 
    FTM_SET_SRXSET_REQ_STRU* pstFtmReq        = (FTM_SET_SRXSET_REQ_STRU*)pParam;
    OM_PHY_SYN_SRXSET_SET_REQ_STRU stReqToDsp = { 0 };
    
    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if((ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
        || (!ftm_CheckSynCmdSteps(CT_S_STEPS_DONE_TMODE_7_REQ)))
    {
        return at_ftm_srxset_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    /* ������� */
    if(!ftm_CheckSynCmdSteps(CT_S_STEPS_DONE_SSYNC))
    {
        return at_ftm_srxset_setcnf(ERR_MSP_INVALID_PARAMETER);
    }
    
    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId  = OM_PHY_SYN_SRXSET_SET_REQ;
    stReqToDsp.usSwitch = (VOS_UINT16)pstFtmReq->usSwitch;
	stReqToDsp.sPower   = (VOS_INT16)pstFtmReq->sPower;
	stReqToDsp.usRBNum  = (VOS_UINT16)pstFtmReq->usRBNum;
	stReqToDsp.usRBPos  = (VOS_UINT16)pstFtmReq->usRBPos;
	stReqToDsp.usMod    = (VOS_UINT16)pstFtmReq->usMod;

    if(ERR_MSP_SUCCESS != ftm_mailbox_ltebt_write(&stReqToDsp, sizeof(OM_PHY_SYN_SRXSET_SET_REQ_STRU)))
    {
        return at_ftm_srxset_setcnf(ERR_MSP_UNKNOWN);
    }

    at_ftm_srxset_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);      
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_srxset_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_srxset_timeout(VOS_VOID)
{
    return at_ftm_srxset_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_srxset_dspcnf
 ��������  : DSPԭ��PHY_OM_SYN_SRXSET_SET_CNF������
 �������  : pParam PHY_OM_SYN_SRXSET_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_srxset_dspcnf(VOS_VOID* pParam)
{
    
    at_ftm_srxset_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_srxset_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_srxsubfra_store
 ��������  : �������
 �������  : ucStoreType �������� 
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_srxsubfra_store(VOS_UINT8 ucStoreType, FTM_SET_SRXSUBFRA_REQ_STRU* pstReq)
{
    static FTM_SET_SRXSUBFRA_REQ_STRU stReq = { 0 };    
    FTM_SYN_INFO_STRU* pstFtmSynInfo        = ftm_GetSynMainInfo();
    
    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {       
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_SRXSUBFRA_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else 
    {        
        pstFtmSynInfo->ulCurCmdStepsFlag             |= CT_S_STEPS_DONE_SRXSUBFRA;
		pstFtmSynInfo->stSrxsubfraRdCnf.ussubFrameNum = stReq.ussubFrameNum;
    }
    
    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_srxsubfra_setcnf
 ��������  : ����ID_MSG_FTM_SET_SRXSUBFRA_CNF
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_srxsubfra_setcnf(VOS_UINT32 ulErrCode)
{  
    FTM_SET_SRXSUBFRA_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_SRXSUBFRA_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_SRXSUBFRA_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_srxsubfra_read
 ��������  : ID_MSG_FTM_RD_SRXSUBFRA_REQ ������
 �������  : pParam FTM_RD_SRXSUBFRA_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_srxsubfra_read(VOID* pParam)
{ 
    FTM_SYN_INFO_STRU* pstFtmSynInfo     = ftm_GetSynMainInfo();
    FTM_RD_SRXSUBFRA_CNF_STRU stRdCnf    = { 0 };

    stRdCnf.ulErrCode	  = ERR_MSP_SUCCESS;
    stRdCnf.ussubFrameNum = pstFtmSynInfo->stSrxsubfraRdCnf.ussubFrameNum;
           
    return ftm_comm_send(ID_MSG_FTM_RD_SRXSUBFRA_CNF, (VOS_UINT32)&stRdCnf, 
        sizeof(FTM_RD_SRXSUBFRA_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_srxsubfra_set
 ��������  : ID_MSG_FTM_SET_SRXSUBFRA_REQ ������
             ��DSP����OM_PHY_SYN_SRXSUBFRA_SET_REQԭ��
 �������  : pParam FTM_SET_SRXSUBFRA_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_srxsubfra_set(VOS_VOID* pParam)
{ 
    FTM_SET_SRXSUBFRA_REQ_STRU* pstFtmReq        = (FTM_SET_SRXSUBFRA_REQ_STRU*)pParam;
    OM_PHY_SYN_SRXSUBFRA_SET_REQ_STRU stReqToDsp = { 0 };
    
	FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();
	FCHAN_MODE_ENUM fchanMode = pstFtmFastCtInfo->enCurMode;
    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if((ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
        || (!ftm_CheckSynCmdSteps(CT_S_STEPS_DONE_TMODE_7_REQ)))
    {
        return at_ftm_srxsubfra_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    /* ������� */
    if(!ftm_CheckSynCmdSteps(CT_S_STEPS_DONE_SSYNC))
    {
        return at_ftm_srxsubfra_setcnf(ERR_MSP_INVALID_PARAMETER);
    }
    
    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId       = OM_PHY_SYN_SRXSUBFRA_SET_REQ;
    stReqToDsp.usSubFrameNum = (VOS_UINT16)pstFtmReq->ussubFrameNum;

    if(ERR_MSP_SUCCESS != ftm_mailbox_bt_write(fchanMode,&stReqToDsp, sizeof(OM_PHY_SYN_SRXSUBFRA_SET_REQ_STRU)))
    {
        return at_ftm_srxsubfra_setcnf(ERR_MSP_UNKNOWN);
    }

    at_ftm_srxsubfra_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);      
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_srxsubfra_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_srxsubfra_timeout(VOS_VOID)
{
    return at_ftm_srxsubfra_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_srxsubfra_dspcnf
 ��������  : DSPԭ��PHY_OM_SYN_SRXSUBFRA_SET_CNF������
 �������  : pParam PHY_OM_SYN_SRXSUBFRA_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_srxsubfra_dspcnf(VOS_VOID* pParam)
{
    
    at_ftm_srxsubfra_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_srxsubfra_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_srxmeas_read
 ��������  : ID_MSG_FTM_RD_SRXBLER_REQ ������
 �������  : pParam FTM_RD_SRXBLER_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_srxmeas_read(VOID* pParam)
{ 

    FTM_SYN_INFO_STRU* pstFtmSynInfo   = ftm_GetSynMainInfo();
    FTM_RD_SRXBLER_CNF_STRU stRdCnf    = { {0}, };

    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if((ftm_GetNoneSig()!=FTM_NONESIG_RTT_OPEN) || (!ftm_CheckSynCmdSteps(CT_S_STEPS_DONE_TMODE_7_REQ)))
    {
        stRdCnf.ulErrCode = ERR_MSP_UE_MODE_ERR;
        
        return ftm_comm_send(ID_MSG_FTM_RD_SRXBLER_CNF, (VOS_UINT32)&stRdCnf,
            sizeof(FTM_RD_SRXBLER_CNF_STRU));
    }       

    /*�ж��Ƿ����AT^SSTART AT^SSYNC�����յ�PHY_OM_SYN_SRXBLER_RD_CNF */
    if(((pstFtmSynInfo->ulCurCmdStepsFlag&CT_S_STEPS_DONE_SSTART) == CT_S_STEPS_DONE_SSTART)
        && ((pstFtmSynInfo->ulCurCmdStepsFlag&CT_S_STEPS_DONE_SSYNC) == CT_S_STEPS_DONE_SSYNC)
        && ((pstFtmSynInfo->ulCurCmdStepsFlag&CT_S_STEPS_DONE_SRXBLER_IND) == CT_S_STEPS_DONE_SRXBLER_IND))
	{
        stRdCnf.usbler[0]    = pstFtmSynInfo->stSrxblerRdCnf.usbler[0];
        stRdCnf.usSnr[0]     = pstFtmSynInfo->stSrxblerRdCnf.usSnr[0];
        stRdCnf.usbler[1]    = pstFtmSynInfo->stSrxblerRdCnf.usbler[1];
        stRdCnf.usSnr[1]     = pstFtmSynInfo->stSrxblerRdCnf.usSnr[1];
        stRdCnf.ulErrCode = ERR_MSP_SUCCESS;

    }else
    {
        stRdCnf.ulErrCode = ERR_MSP_INVALID_PARAMETER;
    }

    return ftm_comm_send(ID_MSG_FTM_RD_SRXBLER_CNF, (VOS_UINT32)&stRdCnf,
            sizeof(FTM_RD_SRXBLER_CNF_STRU));
}

//TDS BER RD
VOS_UINT32 at_ftm_strxmeas_read(VOS_VOID* pParam)
{ 
    FTM_SYN_INFO_STRU* pstFtmSynInfo   = ftm_GetSynMainInfo();
 //   FTM_RD_SRXBLER_CNF_STRU stRdCnf    = { 0 };

    FTM_RD_STRXBER_CNF_STRU stBerRdCnf = {0};
	
    HAL_SDMLOG("-----ENTER:[%s] \n", __FUNCTION__);

    /* �ж��Ƿ��ڷ�����ģʽ�� */
        if((ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
        || (!ftm_CheckSynCmdSteps(CT_S_STEPS_DONE_TMODE_7_REQ)))
    {
        
	 HAL_SDMLOG("-----[%s]:GetNoneSig fail \n", __FUNCTION__);
        stBerRdCnf.ulErrCode = ERR_MSP_UE_MODE_ERR;       
        return ftm_comm_send(ID_MSG_FTM_RD_SRXBLER_CNF, (VOS_UINT32)&stBerRdCnf,
            sizeof(FTM_RD_STRXBER_CNF_STRU));
    }       
    
    /*�ж��Ƿ����AT^SSTART AT^SSYNC�����յ�PHY_OM_SYN_SRXBLER_RD_CNF */
    if(((pstFtmSynInfo->ulCurCmdStepsFlag&CT_S_STEPS_DONE_SSTART) == CT_S_STEPS_DONE_SSTART)
        && ((pstFtmSynInfo->ulCurCmdStepsFlag&CT_S_STEPS_DONE_SSYNC) == CT_S_STEPS_DONE_SSYNC)
        && ((pstFtmSynInfo->ulCurCmdStepsFlag&CT_S_STEPS_DONE_STRXBER_IND) == CT_S_STEPS_DONE_STRXBER_IND))
    {
        stBerRdCnf.ulbersum = pstFtmSynInfo->stStrxBerRdCnf.ulbersum;
        stBerRdCnf.ulberErr = pstFtmSynInfo->stStrxBerRdCnf.ulberErr;
        stBerRdCnf.ulErrCode = ERR_MSP_SUCCESS;

    }
    else
    {
        HAL_SDMLOG("-----[%s]:Stepsflag is %d \n", __FUNCTION__,pstFtmSynInfo->ulCurCmdStepsFlag);
        stBerRdCnf.ulErrCode = ERR_MSP_INVALID_PARAMETER;
    }

   /*  ��ȡBER������ */
    pstFtmSynInfo->stStrxBerRdCnf.ulberErr = 0;
    pstFtmSynInfo->stStrxBerRdCnf.ulbersum = 0;
    pstFtmSynInfo->stStrxBerRdCnf.ulErrCode = 0;
   /* �ظ���A �� */
    return ftm_comm_send(ID_MSG_FTM_RD_STRXBER_CNF, (VOS_UINT32)&stBerRdCnf,
         sizeof(FTM_RD_STRXBER_CNF_STRU));

}

/*****************************************************************************
 �� �� ��  : at_ftm_srxmeas_dspind
 ��������  : DSPԭ��PHY_OM_SYN_SRXBLER_RD_CNF������
 �������  : pParam PHY_OM_SYN_SRXMEAS_RPT_IND_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_srxmeas_dspind(VOS_VOID* pParam)
{
    PHY_OM_SYN_SRXMEAS_RPT_IND_STRU* pDspInd = (PHY_OM_SYN_SRXMEAS_RPT_IND_STRU*)pParam; 
    FTM_SYN_INFO_STRU* pstFtmSynInfo         = ftm_GetSynMainInfo();

    pstFtmSynInfo->ulCurCmdStepsFlag    |= CT_S_STEPS_DONE_SRXBLER_IND; 
	pstFtmSynInfo->stSrxblerRdCnf.usbler[0] = (VOS_UINT16)pDspInd->ulBler[0];
	pstFtmSynInfo->stSrxblerRdCnf.usSnr[0]  = pDspInd->sSnr[0];
    pstFtmSynInfo->stSrxblerRdCnf.usbler[1] = (VOS_UINT16)pDspInd->ulBler[1];
	pstFtmSynInfo->stSrxblerRdCnf.usSnr[1]  = pDspInd->sSnr[1];
            
    return ERR_MSP_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : at_ftm_strxmeas_dspind
 ��������  : DSPԭ��PHY_OM_SYN_SRXBLER_RD_CNF������
 �������  : pParam PHY_OM_SYN_SRXMEAS_RPT_IND_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_strxmeas_dspind(VOS_VOID* pParam)
{
    FTM_SYN_INFO_STRU* pstFtmSynInfo         = ftm_GetSynMainInfo();
    PHY_OM_SYN_SRXMEAS_TDS_RPT_IND_STRU* pTDspInd = (PHY_OM_SYN_SRXMEAS_TDS_RPT_IND_STRU*)pParam;
	
    HAL_SDMLOG("-----TDS 1 param_addr=%p , dspind=%08x,sum=%d,err=%d\n", pParam,pTDspInd->ulMsgId,pTDspInd->ulBersum,pTDspInd->ulBerErr);
		   
	   
	   /* BT TDS �������۲��ۼƶ�ʱ�ϱ���ֵ  */
    pstFtmSynInfo->ulCurCmdStepsFlag    |= CT_S_STEPS_DONE_STRXBER_IND; 
	pstFtmSynInfo->stStrxBerRdCnf.ulbersum+= pTDspInd->ulBersum;
	pstFtmSynInfo->stStrxBerRdCnf.ulberErr+= pTDspInd->ulBerErr;
    HAL_SDMLOG("-----TDS 3 dspind sum=%d,err=%d\n", pstFtmSynInfo->stStrxBerRdCnf.ulbersum,pstFtmSynInfo->stStrxBerRdCnf.ulberErr);
    return ERR_MSP_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : at_ftm_sstart_store
 ��������  : �������
 �������  : ucStoreType �������� 
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_sstart_store(VOS_UINT8 ucStoreType, FTM_SET_SSTART_REQ_STRU* pstReq)
{
    static FTM_SET_SSTART_REQ_STRU stReq = { 0 };    
    FTM_SYN_INFO_STRU* pstFtmSynInfo     = ftm_GetSynMainInfo();
    
    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {       
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_SSTART_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else 
    {
        pstFtmSynInfo->ulCurCmdStepsFlag     |= CT_S_STEPS_DONE_SSTART;
        pstFtmSynInfo->stSstartRdCnf.usType   = stReq.usType;
        pstFtmSynInfo->stSstartRdCnf.usStatus = 0;
    }
    
    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_sstart_setcnf
 ��������  : ����ID_MSG_FTM_SET_SSTART_CNF
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_sstart_setcnf(VOS_UINT32 ulErrCode)
{  
    FTM_SET_SSTART_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_SSTART_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_SSTART_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_sstart_read
 ��������  : ID_MSG_FTM_RD_SSTART_REQ ������
 �������  : pParam FTM_RD_SSTART_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_sstart_read(VOID* pParam)
{ 
    FTM_SYN_INFO_STRU* pstFtmSynInfo  = ftm_GetSynMainInfo();
    FTM_RD_SSTART_CNF_STRU stRdCnf    = { 0 };

    if(!ftm_CheckSynCmdSteps(CT_S_STEPS_DONE_SSTART_CNF))
    {
        stRdCnf.ulErrCode = ERR_MSP_SUCCESS;
        stRdCnf.usType    = pstFtmSynInfo->stSstartRdCnf.usType;
        stRdCnf.usStatus  = 1;
    }
    else
    {
        stRdCnf.ulErrCode = ERR_MSP_SUCCESS;
        stRdCnf.usType    = pstFtmSynInfo->stSstartRdCnf.usType;
        stRdCnf.usStatus  = pstFtmSynInfo->stSstartRdCnf.usStatus;
    }
           
    return ftm_comm_send(ID_MSG_FTM_RD_SSTART_CNF, (VOS_UINT32)&stRdCnf, 
        sizeof(FTM_RD_SSTART_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_sstart_set
 ��������  : ID_MSG_FTM_SET_SSTART_REQ ������
             ��DSP����OM_PHY_SYN_SSTART_SET_REQԭ��
 �������  : pParam FTM_SET_SSTART_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_sstart_set(VOS_VOID* pParam)
{ 
    FTM_SET_SSTART_REQ_STRU* pstFtmReq        = (FTM_SET_SSTART_REQ_STRU*)pParam;
    OM_PHY_SYN_SSTART_SET_REQ_STRU stReqToDsp = { 0 };
	FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();
	FCHAN_MODE_ENUM fchanMode = pstFtmFastCtInfo->enCurMode;
    
    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if((ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
        || (!ftm_CheckSynCmdSteps(CT_S_STEPS_DONE_TMODE_7_REQ)))
    {
        return at_ftm_sstart_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    /* ������� */
    if(!ftm_CheckSynCmdSteps(CT_S_STEPS_DONE_SSYNC))
    {
        return at_ftm_sstart_setcnf(ERR_MSP_INVALID_PARAMETER);
    }
    
    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId = OM_PHY_SYN_SSTART_SET_REQ;
    stReqToDsp.usType  = (VOS_UINT16)pstFtmReq->usType;

    if(ERR_MSP_SUCCESS != ftm_mailbox_bt_write(fchanMode,&stReqToDsp, sizeof(OM_PHY_SYN_SSTART_SET_REQ_STRU)))
    {
        return at_ftm_sstart_setcnf(ERR_MSP_UNKNOWN);
    }

    at_ftm_sstart_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);      
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_sstart_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_sstart_timeout(VOS_VOID)
{
    return at_ftm_sstart_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_sstart_dspcnf
 ��������  : DSPԭ��PHY_OM_SYN_SSTART_SET_CNF������
 �������  : pParam PHY_OM_SYN_SSTART_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_sstart_dspcnf(VOS_VOID* pParam)
{
    FTM_SYN_INFO_STRU* pstFtmSynInfo        = ftm_GetSynMainInfo();
	FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();
    FCHAN_MODE_ENUM fchanMode = pstFtmFastCtInfo->enCurMode;
    
    at_ftm_sstart_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    pstFtmSynInfo->ulCurCmdStepsFlag |= CT_S_STEPS_DONE_SSTART_CNF;

    /* ��������в�����������ղ������ֵ */
    if((pstFtmSynInfo->stSstartRdCnf.usType == 1)
        || (pstFtmSynInfo->stSstartRdCnf.usType == 3))
    {
        if(EN_FCHAN_MODE_TD_SCDMA == fchanMode)
        {
            /* TDS */
            pstFtmSynInfo->stStrxBerRdCnf.ulbersum = 0;
	     pstFtmSynInfo->stStrxBerRdCnf.ulberErr = 0;
            pstFtmSynInfo->ulCurCmdStepsFlag     &= (~CT_S_STEPS_DONE_STRXBER_IND);	
	     HAL_SDMLOG("-----START1: ber sum=%d,err=%d\n", pstFtmSynInfo->stStrxBerRdCnf.ulbersum,pstFtmSynInfo->stStrxBerRdCnf.ulberErr);
			
        } 
        else
        {
		    pstFtmSynInfo->stSrxblerRdCnf.usbler[0] = 0;
    	    pstFtmSynInfo->stSrxblerRdCnf.usSnr[0]  = 0;
            pstFtmSynInfo->stSrxblerRdCnf.usbler[1] = 0;
    	    pstFtmSynInfo->stSrxblerRdCnf.usSnr[1]  = 0;
    	    pstFtmSynInfo->ulCurCmdStepsFlag     &= (~CT_S_STEPS_DONE_SRXBLER_IND);		    
	}
    }

#ifdef MSP_PLATFORM_VUD
			hal_dra_SigGiveSem();
#endif

    return at_ftm_sstart_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_sstop_store
 ��������  : �������
 �������  : ucStoreType �������� 
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_sstop_store(VOS_UINT8 ucStoreType, FTM_SET_SSTOP_REQ_STRU* pstReq)
{
    static FTM_SET_SSTOP_REQ_STRU stReq = { 0 };    
    FTM_SYN_INFO_STRU* pstFtmSynInfo    = ftm_GetSynMainInfo();
    
    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {       
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_SSTOP_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else 
    {
       pstFtmSynInfo->ulCurCmdStepsFlag |= CT_S_STEPS_DONE_SSTOP;
    }
    
    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_sstop_setcnf
 ��������  : ����ID_MSG_FTM_SET_SSTOP_CNF
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_sstop_setcnf(VOS_UINT32 ulErrCode)
{  
    FTM_SET_SSTOP_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_SSTOP_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_SSTOP_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_sstop_set
 ��������  : ID_MSG_FTM_SET_SSTOP_REQ ������
             ��DSP����OM_PHY_SYN_SSTOP_SET_REQԭ��
 �������  : pParam FTM_SET_SSTOP_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_sstop_set(VOS_VOID* pParam)
{ 
    FTM_SET_SSTOP_REQ_STRU* pstFtmReq        = (FTM_SET_SSTOP_REQ_STRU*)pParam;
    OM_PHY_SYN_SSTOP_SET_REQ_STRU stReqToDsp = { 0 };
    MSP_PS_SSTOP_REQ_STRU stReqToPsStop ={0};
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();
    FCHAN_MODE_ENUM fchanMode = pstFtmFastCtInfo->enCurMode;
    
    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if((ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
        || (!ftm_CheckSynCmdSteps(CT_S_STEPS_DONE_TMODE_7_REQ)))
    {
        return at_ftm_sstop_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    if(0 == pstFtmReq->usType)
    {
        /* ���з���ֹͣ ֪ͨPS */
#if (FEATURE_UE_MODE_TDS == FEATURE_ON)
		HAL_SDMLOG("-----[%s]:send data to PS \n", __FUNCTION__);
		stReqToPsStop.MsgId=ID_T_MSP_PS_STOP_REQ;
		stReqToPsStop.ulType=0;

	   	if(ERR_MSP_SUCCESS != atFTMSendVosMsg(TPS_PID_MAC,  &stReqToPsStop, sizeof(stReqToPsStop) ))
		{
			HAL_SDMLOG("[%s] send data to ps fail\n", __FUNCTION__);
			return at_ftm_sstop_setcnf(ERR_MSP_UNKNOWN);
		}

		at_ftm_sstop_store(FTM_F_CT_STORE_REQ_GLOBAL,pstFtmReq);
	       return at_ftm_sstop_setcnf(ERR_MSP_SUCCESS);
#else
           return at_ftm_sstop_setcnf(ERR_MSP_INVALID_OP);
#endif
    }
    else if(1 == pstFtmReq->usType)
    {
    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId = OM_PHY_SYN_SSTOP_SET_REQ;
    stReqToDsp.usType  = (VOS_UINT16)pstFtmReq->usType;

	    if(ERR_MSP_SUCCESS != ftm_mailbox_bt_write(fchanMode,&stReqToDsp, sizeof(OM_PHY_SYN_SSTOP_SET_REQ_STRU)))
    {
        return at_ftm_sstop_setcnf(ERR_MSP_UNKNOWN);
    }

    at_ftm_sstop_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);      
    return ERR_MSP_WAIT_ASYNC;
    }
    else
    {	    
	    HAL_SDMLOG("-----[%s]:invalid parameter \n", __FUNCTION__);
	    return at_ftm_sstop_setcnf(ERR_MSP_INVALID_PARAMETER);
    }
}

/*****************************************************************************
 �� �� ��  : at_ftm_sstop_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_sstop_timeout(VOS_VOID)
{
    return at_ftm_sstop_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_sstop_dspcnf
 ��������  : DSPԭ��PHY_OM_SYN_SSTOP_SET_CNF������
 �������  : pParam PHY_OM_SYN_SSTOP_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_sstop_dspcnf(VOS_VOID* pParam)
{
    
    at_ftm_sstop_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_sstop_setcnf(ERR_MSP_SUCCESS);
}


/*****************************************************************************
 �� �� ��  : at_ftm_stcfgdpch_store
 ��������  : �������
 �������  : ucStoreType �������� 
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_stcfgdpch_store(VOS_UINT8 ucStoreType, FTM_SET_SSTOP_REQ_STRU* pstReq)
{
    static FTM_SET_SSTOP_REQ_STRU stReq = { 0 };    
    FTM_SYN_INFO_STRU* pstFtmSynInfo    = ftm_GetSynMainInfo();

	HAL_SDMLOG("-----[%s]:storeType = %d \n", __FUNCTION__,ucStoreType);
    
    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {       
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_SSTOP_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else 
    {
       pstFtmSynInfo->ulCurCmdStepsFlag |= CT_S_STEPS_DONE_STCFGDPCH;
    }
    
    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_stcfgdpch_setcnf
 ��������  : ����ID_MSG_FTM_SET_STCFGDPCH_CNF
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_stcfgdpch_setcnf(VOS_UINT32 ulErrCode)
{  
    FTM_SET_STCFGDPCH_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_STCFGDPCH_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_STCFGDPCH_CNF_STRU));
}


/*****************************************************************************
 �� �� ��  : at_ftm_stcfgdpch_set
 ��������  : ID_T_MSP_PS_DPCH_REQ ������
 �������  : pParam FTM_SET_STCFGDPCH_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_stcfgdpch_set(VOS_VOID* pParam)
{ 
    FTM_SET_STCFGDPCH_REQ_STRU* pstFtmReq        = (FTM_SET_STCFGDPCH_REQ_STRU*)pParam;
    MSP_PS_DPCH_REQ_STRU stReqToPsDpch = {0};

    
    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if((ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
        || (!ftm_CheckSynCmdSteps(CT_S_STEPS_DONE_TMODE_7_REQ)))
    {
        
		HAL_SDMLOG("-----[%s]:GetNoneSig fail \n", __FUNCTION__);
        return at_ftm_stcfgdpch_setcnf(ERR_MSP_UE_MODE_ERR);
    }


    stReqToPsDpch.ulTransType = pstFtmReq->ulTransType;
    stReqToPsDpch.MsgId = ID_T_MSP_PS_DPCH_REQ;
    stReqToPsDpch.ulTpcStep = pstFtmReq->usTPCStepSize;
	HAL_SDMLOG("at^stcfgdpch send data to PS : type=%d msgID=%d, TPC size=%d\n",
	  	stReqToPsDpch.ulTransType,stReqToPsDpch.MsgId, stReqToPsDpch.ulTpcStep);
	if(ERR_MSP_SUCCESS != atFTMSendVosMsg(TPS_PID_MAC,  &stReqToPsDpch, sizeof(stReqToPsDpch) ))
	{
		HAL_SDMLOG("[%s] send data to ps fail  AGAIN\n", __FUNCTION__);
		return at_ftm_stcfgdpch_setcnf(ERR_MSP_UNKNOWN);
	}

	at_ftm_stcfgdpch_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL); 
	
	return at_ftm_stcfgdpch_setcnf(ERR_MSP_SUCCESS);

}


#if 0

/*****************************************************************************
 �� �� ��  : at_ftm_stcfgdpch_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
extern VOS_UINT32 at_ftm_stcfgdpch_timeout(VOS_VOID)
{
    HAL_SDMLOG("-----ENTER :[%s] \n", __FUNCTION__);
    return at_ftm_stcfgdpch_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_stcfgdpch_pscnf
 ��������  : PSԭ�ﴦ����
 �������  : pParam ָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
extern VOS_UINT32 at_ftm_stcfgdpch_pscnf(VOS_VOID* pParam)
{
    PS_MSP_DPCH_CNF* pPsCnf = (PS_MSP_DPCH_CNF*)pParam; 

	HAL_SDMLOG("-----ENTER :[%s] \n", __FUNCTION__);
    
    at_ftm_stcfgdpch_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_stcfgdpch_setcnf(ERR_MSP_SUCCESS);
    
}

#endif

/*****************************************************************************
 �� �� ��  : at_ftm_fpow_store
 ��������  : �������
 �������  : ucStoreType �������� 
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_fpow_store(VOS_UINT8 ucStoreType, FTM_FPOW_REQ_STRU* pstReq)
{
    static FTM_FPOW_REQ_STRU stReq = { 0 };    
    FTM_SYN_INFO_STRU* pstFtmSynInfo    = ftm_GetSynMainInfo();

	HAL_SDMLOG("-----[%s]:storeType = %d \n", __FUNCTION__,ucStoreType);
    
    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {       
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_FPOW_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else 
    {
       /* ��ȷ��--����power ��Ҫ������ȫ����Ϣ��    */
       pstFtmSynInfo->ulCurCmdStepsFlag |= CT_S_STEPS_DONE_FPOW;
    }
    
    return ;


}

/*****************************************************************************
 �� �� ��  : at_ftm_fpow_setcnf
 ��������  : ����ID_MSG_FTM_FPOW_CNF
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_fpow_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_FPOW_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_FPOW_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_FPOW_CNF_STRU));
    
}

/*****************************************************************************
 �� �� ��  : at_ftm_fpow_set
 ��������  : ID_MSG_FTM_FPOW_REQ ������
             ��DSP����OM_PHY_BT_FPOW_SET_REQԭ��
 �������  : pParam FTM_FPOW_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fpow_set(VOS_VOID* pParam)
{
	FTM_FPOW_REQ_STRU* pstFtmReq = (FTM_FPOW_REQ_STRU*)pParam;
	OM_PHY_SYN_FPOW_SET_REQ_STRU stReqToDsp = { 0 };

	
	HAL_SDMLOG("-----enter:[%s] \n", __FUNCTION__);

	/* �ж��Ƿ��ڷ�����ģʽ�� */
    if((ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
        || (!ftm_CheckSynCmdSteps(CT_S_STEPS_DONE_TMODE_7_REQ)))
    {
        
		HAL_SDMLOG("-----[%s]:GetNoneSig fail\n", __FUNCTION__);
        return at_ftm_sstop_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    /*  */
	if((pstFtmReq->sPower)<(-60)||(pstFtmReq->sPower)>24)
	{
	    HAL_SDMLOG("-----[%s]:INVALID_PARAMETER \n", __FUNCTION__);
	    return at_ftm_fpow_setcnf(ERR_MSP_INVALID_PARAMETER);
	}

    stReqToDsp.ulMsgId = OM_PHY_BT_FPOW_SET_REQ; /*ID ����*/
	stReqToDsp.usPower = pstFtmReq->sPower;
	HAL_SDMLOG("-----[%s]:send data to DSP \n", __FUNCTION__);
	if(ERR_MSP_SUCCESS != ftm_mailbox_tdsbt_write(&stReqToDsp, sizeof(OM_PHY_SYN_FPOW_SET_REQ_STRU)))
    {
        HAL_SDMLOG("-----[%s]:send data to dsp fail \n", __FUNCTION__);
        return at_ftm_fpow_setcnf(ERR_MSP_UNKNOWN);
    }

    at_ftm_fpow_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);      
    return ERR_MSP_WAIT_ASYNC;
	
}


/*****************************************************************************
 �� �� ��  : at_ftm_fpow_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fpow_timeout(VOS_VOID)
{
    HAL_SDMLOG("-----ENTER :[%s] \n", __FUNCTION__);
    return at_ftm_fpow_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fpow_dspcnf
 ��������  : DSPԭ�ﴦ����
 �������  : pParam PHY_OM_SYN_FPOW_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fpow_dspcnf(VOS_VOID* pParam)
{

	HAL_SDMLOG("-----ENTER :[%s] \n", __FUNCTION__);
    
    at_ftm_sstop_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_sstop_setcnf(ERR_MSP_SUCCESS);
    
}
/*lint -restore*/

