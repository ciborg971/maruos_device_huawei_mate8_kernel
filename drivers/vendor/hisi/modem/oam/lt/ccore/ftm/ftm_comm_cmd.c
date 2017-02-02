

#include <msp_errno.h>
#include <osm.h>
#include <gen_msg.h>
#include <ftm.h>
#include "LMspLPhyInterface.h"
#include "ftm_ct.h"
/*lint -save -e537*/
#include <AppRrcInterface.h>
#include "TafAppMma.h"
/*lint -restore*/
#include "Tds_ps_at.h"
#include "TPsTMspInterface.h" 

/*lint -save -e767*/
#define    THIS_FILE_ID        MSP_FILE_ID_FTM_COMM_CMD_C
/*lint -restore*/

/*****************************************************************************
 �� �� ��  : at_ftm_ltcommcmd_set
 ��������  : ID_MSG_FTM_SET_LTCOMMCMD_REQ ������
             ����LTEƵ���л�
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_ltcommcmd_set(VOS_VOID* pParam)
{
	/*lint -save -e813 -e550 */
    FTM_SET_LTCOMMCMD_CNF_STRU  stCnf = { 0 };
    FTM_SET_LTCOMMCMD_REQ_STRU* pstFtmReq   = (FTM_SET_LTCOMMCMD_REQ_STRU*)pParam;
    FTM_PHY_COMM_CMD_SET_REQ_STRU *pstReqToDsp = NULL;

    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
	VOS_UINT32 ulLen = 0;

    (VOS_VOID)VOS_MemSet(&ftm_GetMainInfo()->stRdLtCommCmdCnf, 0, sizeof(FTM_RD_LTCOMMCMD_CNF_STRU) + pstFtmReq->ulDataLen);
    ftm_GetMainInfo()->stRdLtCommCmdCnf.ulErrCode = ERR_MSP_SUCCESS;

    ulLen = (sizeof(FTM_PHY_COMM_CMD_SET_REQ_STRU)+MAX_COMM_CMD_LEN);
    pstReqToDsp = (FTM_PHY_COMM_CMD_SET_REQ_STRU *)VOS_MemAlloc(WUEPS_PID_AT, DYNAMIC_MEM_PT, ulLen);
    if (pstReqToDsp == VOS_NULL) {
        (VOS_VOID)vos_printf("[%s]failed to malloc\n",__FUNCTION__);
        return ERR_MSP_FAILURE;
    }
    pstReqToDsp->ulMsgId   = OM_PHY_COMM_CMD_SET_REQ;
    pstReqToDsp->ulDataLen = pstFtmReq->ulDataLen;
    (VOS_VOID)VOS_MemCpy(pstReqToDsp->cData, pstFtmReq->cData, pstReqToDsp->ulDataLen);  

    switch(pstFtmReq->ulCmdDest)
    {
        case EN_LTCOMMCMD_DEST_LDSP_CT:
            ulRet = ftm_mailbox_ltect_write((void *)pstReqToDsp, ulLen);
            break;

        case EN_LTCOMMCMD_DEST_LDSP_BT:
            ulRet = ftm_mailbox_ltebt_write((void *)pstReqToDsp, ulLen);
            break;

        case EN_LTCOMMCMD_DEST_TDSP_CT:
            ulRet = ftm_mailbox_tdsct_write((void *)pstReqToDsp, ulLen);
            break;

        case EN_LTCOMMCMD_DEST_TDSP_BT:
            ulRet = ftm_mailbox_tdsbt_write((void *)pstReqToDsp, ulLen);
            break;

        default:
            ulRet = ERR_MSP_FAILURE;
    }
 
    (VOS_VOID)VOS_MemFree(WUEPS_PID_AT, pstReqToDsp);
    if (ERR_MSP_SUCCESS != ulRet)
    {
        stCnf.ulErrCode = ERR_MSP_UNKNOWN;
        stCnf.ulDataLen = 0;
        
        return ftm_comm_send(ID_MSG_FTM_SET_LTCOMMCMD_CNF,
            (VOS_UINT32)&stCnf, sizeof(FTM_SET_LTCOMMCMD_CNF_STRU));
    }  
    return ERR_MSP_WAIT_ASYNC;
    /*lint -restore*/
}

/*****************************************************************************
 �� �� ��  : at_ftm_ltcommcmd_read
 ��������  : ID_MSG_FTM_RD_LTCOMMCMD_REQ ������
 �������  : ��
 �������  : ��s
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_ltcommcmd_read(VOS_VOID* pParam)
{
    FTM_RD_LTCOMMCMD_CNF_STRU* pstFtmCnf = (FTM_RD_LTCOMMCMD_CNF_STRU *)&ftm_GetMainInfo()->stRdLtCommCmdCnf;

    return ftm_comm_send(ID_MSG_FTM_RD_LTCOMMCMD_CNF, (VOS_UINT32)pstFtmCnf, sizeof(FTM_RD_LTCOMMCMD_CNF_STRU) + pstFtmCnf->ulDataLen);
}

/*****************************************************************************
 �� �� ��  : at_ftm_ltcommcmd_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_ltcommcmd_timeout(VOS_VOID)
{
	/*lint -save -e813 -e550 */
	FTM_SET_LTCOMMCMD_CNF_STRU  stCnf = { 0 };
	
    stCnf.ulErrCode = ERR_MSP_TIME_OUT;
    stCnf.ulDataLen = 0;
        
   return ftm_comm_send(ID_MSG_FTM_SET_LTCOMMCMD_CNF,
            (VOS_UINT32)&stCnf, sizeof(FTM_SET_LTCOMMCMD_CNF_STRU));
    /*lint -restore*/
}

/*****************************************************************************
 �� �� ��  : at_ftm_ltcommcmd_dspcnf
 ��������  : DSPԭ��PHY_OM_COMM_CMD_SET_CNF������
 �������  : pParam PHY_OM_COMM_CMD_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_ltcommcmd_dspcnf(VOS_VOID* pParam)
{
    PHY_FTM_COMM_CMD_SET_CNF_STRU* pDspCnf = (PHY_FTM_COMM_CMD_SET_CNF_STRU*)pParam;
	/*lint -save -e813*/
    FTM_SET_LTCOMMCMD_CNF_STRU    *pstSetLtCommCmdCnf  = NULL;
	/*lint -restore*/
    VOS_UINT32 ulRet = 0;

    pstSetLtCommCmdCnf = (FTM_SET_LTCOMMCMD_CNF_STRU *)VOS_MemAlloc(WUEPS_PID_AT, DYNAMIC_MEM_PT, 
        sizeof(FTM_SET_LTCOMMCMD_CNF_STRU) + pDspCnf->ulDataLen);

    if (pstSetLtCommCmdCnf == VOS_NULL){
        (VOS_VOID)vos_printf("[%s]failed to malloc\n",__FUNCTION__);
        return ERR_MSP_FAILURE;
    }
    pstSetLtCommCmdCnf->ulErrCode = ERR_MSP_SUCCESS;
    pstSetLtCommCmdCnf->ulDataLen = pDspCnf->ulDataLen;
    (VOS_VOID)VOS_MemCpy(pstSetLtCommCmdCnf->cData, pDspCnf->cData, pstSetLtCommCmdCnf->ulDataLen);    

    ulRet = ftm_comm_send(ID_MSG_FTM_SET_LTCOMMCMD_CNF,
        (VOS_UINT32)pstSetLtCommCmdCnf, 
        sizeof(FTM_SET_LTCOMMCMD_CNF_STRU) + pstSetLtCommCmdCnf->ulDataLen);
    (VOS_VOID)VOS_MemFree(WUEPS_PID_AT, pstSetLtCommCmdCnf);
    return ulRet;
    
}

/*****************************************************************************
 �� �� ��  : at_ftm_ltcommcmd_dspind
 ��������  : DSPԭ��PHY_OM_COMM_CMD_IND������
 �������  : pParam PHY_OM_COMM_CMD_IND_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_ltcommcmd_dspind(VOS_VOID* pParam)
{
    PHY_FTM_COMM_CMD_IND_STRU* pDspInd    = (PHY_FTM_COMM_CMD_IND_STRU*)pParam;
    FTM_RD_LTCOMMCMD_CNF_STRU* pstFtmCnf = (FTM_RD_LTCOMMCMD_CNF_STRU *)&ftm_GetMainInfo()->stRdLtCommCmdCnf;

    (VOS_VOID)VOS_MemSet(pstFtmCnf, 0, sizeof(FTM_RD_LTCOMMCMD_CNF_STRU) + pDspInd->ulDataLen);
    pstFtmCnf->ulErrCode = ERR_MSP_SUCCESS;
    pstFtmCnf->ulDataLen = pDspInd->ulDataLen;
    (VOS_VOID)VOS_MemCpy(pstFtmCnf->cData, pDspInd->cData, pstFtmCnf->ulDataLen);

    return ERR_MSP_SUCCESS;
}

