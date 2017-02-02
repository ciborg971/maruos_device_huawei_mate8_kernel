

#include <msp_errno.h>
#include <osm.h>
#include <gen_msg.h>
#include <ftm.h>
#include "LMspLPhyInterface.h"
#include "ftm_ct.h"
#include "stdint.h"
/*lint -e767*/
#define    THIS_FILE_ID        MSP_FILE_ID_FTM_LTE_QUICK_CT_C
/*lint -e767*/

/*lint --e{830,539,525,420,550}*/

/* �ӵ���鵽��PAֵ */
VOS_UINT32 g_ulFtmCmTms = 0;

VOS_UINT32 g_ulFtmBspFail=0;
VOS_UINT32 g_ulFtmDspFail=0;

/*****************************************************************************
 �� �� ��  : at_ftm_fblk_store
 ��������  : �������
 �������  : ucStoreType ��������
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
/*lint -save -e655 -e732 -e958*/
static VOID at_ftm_fblk_store(VOS_UINT8 ucStoreType, FTM_SET_F_FBLK_REQ_STRU* pstReq)
{
    static FTM_SET_F_FBLK_REQ_STRU stReq = {0};
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_F_FBLK_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else
    {
        pstFtmFastCtInfo->ulCurCmdStepsFlag |= CT_F_STEPS_DONE_FBLK;
        pstFtmFastCtInfo->ulBlocking= stReq.ulBlocking;
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fblk_setcnf
 ��������  : �������
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_fblk_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_F_FBLK_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_F_SET_FBLK_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_F_FBLK_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fblk_read
 ��������  : ID_MSG_FTM_F_RD_FBLK_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fblk_read(VOS_VOID* pParam)
{
    FTM_RD_F_FBLK_CNF_STRU stRdCnf = { 0 };

    stRdCnf.ulErrCode = ERR_MSP_SUCCESS;
    stRdCnf.ulBlocking= ftm_GetFastCTMainInfo()->ulBlocking;

     return ftm_comm_send(ID_MSG_FTM_F_RD_FBLK_CNF, (VOS_UINT32)&stRdCnf, sizeof(FTM_RD_F_FBLK_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fblk_set
 ��������  : ID_MSG_FTM_F_SET_FBLK_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fblk_set(VOS_VOID* pParam)
{
    FTM_SET_F_FBLK_REQ_STRU* pstFtmReq      = (FTM_SET_F_FBLK_REQ_STRU*)pParam;
    OM_PHY_CT_F_BLK_SET_REQ_STRU stReqToDsp = { 0 };

    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if(ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        return at_ftm_fblk_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId     = OM_PHY_CT_F_FBLK_SET_REQ;
    stReqToDsp.usIsBLKMode = (VOS_UINT16)pstFtmReq->ulBlocking;
    if(ERR_MSP_SUCCESS != ftm_mailbox_ltect_write(&stReqToDsp, sizeof(OM_PHY_CT_F_BLK_SET_REQ_STRU)))
    {
        return at_ftm_fblk_setcnf(ERR_MSP_UNKNOWN);
    }

    at_ftm_fblk_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fblk_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fblk_timeout(VOS_VOID)
{
    return at_ftm_fblk_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fblk_dspcnf
 ��������  : DSPԭ��PHY_OM_CT_F_FBLK_SET_CNF������
 �������  : pParam PHY_OM_CT_F_BLK_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fblk_dspcnf(VOS_VOID* pParam)
{

    at_ftm_fblk_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_fblk_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fchans_store
 ��������  : �������
 �������  : ucStoreType ��������
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_fchans_store(VOS_UINT8 ucStoreType, FTM_SET_F_FCHANS_REQ_STRU* pstReq)
{
    static FTM_SET_F_FCHANS_REQ_STRU stReq = {0};
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_F_FCHANS_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else
    {
        pstFtmFastCtInfo->ulCurCmdStepsFlag |= CT_F_STEPS_DONE_FCHANS;
        pstFtmFastCtInfo->usCurUlListNum = stReq.usULFreqNum;
        pstFtmFastCtInfo->usCurDlListNum = stReq.usDLFreqNum;
        (VOS_VOID)MSP_MEMCPY(pstFtmFastCtInfo->ausCurUlFreqInfo, stReq.usULFreqList, sizeof(pstFtmFastCtInfo->ausCurUlFreqInfo));
        (VOS_VOID)MSP_MEMCPY(pstFtmFastCtInfo->ausCurDlFreqInfo, stReq.usDLFreqList, sizeof(pstFtmFastCtInfo->ausCurDlFreqInfo));
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fchans_setcnf
 ��������  : �������
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_fchans_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_F_FCHANS_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_F_SET_FCHANS_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_F_FCHANS_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fchans_read
 ��������  : ID_MSG_FTM_F_RD_FCHANS_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fchans_read(VOS_VOID* pParam)
{
    FTM_RD_F_FCHANS_CNF_STRU stRdCnf = { 0 };
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    stRdCnf.ulErrCode   = ERR_MSP_SUCCESS;
    stRdCnf.usULFreqNum = pstFtmFastCtInfo->usCurUlListNum;
    stRdCnf.usDLFreqNum = pstFtmFastCtInfo->usCurDlListNum;

    (VOS_VOID)MSP_MEMCPY(stRdCnf.usULFreqList, pstFtmFastCtInfo->ausCurUlFreqInfo, sizeof(stRdCnf.usULFreqList));
    (VOS_VOID)MSP_MEMCPY(stRdCnf.usDLFreqList, pstFtmFastCtInfo->ausCurDlFreqInfo, sizeof(stRdCnf.usDLFreqList));

    return ftm_comm_send(ID_MSG_FTM_F_RD_FCHANS_CNF, (VOS_UINT32)&stRdCnf, sizeof(FTM_RD_F_FCHANS_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fchans_set
 ��������  : ID_MSG_FTM_F_SET_FCHANS_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fchans_set(VOS_VOID* pParam)
{
    VOS_UINT16 usTmp                              = 0;
    FTM_SET_F_FCHANS_REQ_STRU* pstFtmReq     = (FTM_SET_F_FCHANS_REQ_STRU*)pParam;
    OM_PHY_CT_F_FREQ_SET_REQ_STRU stReqToDsp = { 0 };
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();
    FCHAN_MODE_ENUM fchanMode = pstFtmFastCtInfo->enCurMode;
    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if(ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        return at_ftm_fchans_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    /* �жϲ����Ƿ���ȷ */
    if ((pstFtmReq->usULFreqNum > CT_F_FREQ_UL_LIST_MAX_NUM)
        || (pstFtmReq->usDLFreqNum > CT_F_FREQ_DL_LIST_MAX_NUM))
    {
        return at_ftm_fchans_setcnf(ERR_MSP_INVALID_PARAMETER);
    }

    if((pstFtmReq->usULFreqNum>0) && (pstFtmReq->usDLFreqNum>0)
       && (pstFtmReq->usULFreqNum != pstFtmReq->usDLFreqNum ))
    {
        return at_ftm_fchans_setcnf(ERR_MSP_INVALID_PARAMETER);
    }

    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId     = OM_PHY_CT_F_FREQ_SET_REQ;
    stReqToDsp.ulMode      = fchanMode;
    stReqToDsp.usUlListNum = pstFtmReq->usULFreqNum;
    stReqToDsp.usDlListNum = pstFtmReq->usDLFreqNum;

    /* �ŵ���ת����Ƶ����Ϣ */
    for(usTmp=0; usTmp<stReqToDsp.usUlListNum; usTmp++)
    {
        stReqToDsp.ausUlFreqInfo[usTmp] = at_ftm_get_freq(fchanMode, pstFtmReq->usULFreqList[usTmp]);
    }

    for(usTmp=0; usTmp<stReqToDsp.usDlListNum; usTmp++)
    {
        stReqToDsp.ausDlFreqInfo[usTmp] = at_ftm_get_freq(fchanMode, pstFtmReq->usDLFreqList[usTmp]);
    }
    
    if(ERR_MSP_SUCCESS != ftm_mailbox_ct_write(fchanMode, &stReqToDsp, sizeof(OM_PHY_CT_F_FREQ_SET_REQ_STRU)))
    {
        return at_ftm_fchans_setcnf(ERR_MSP_UNKNOWN);
    }
    at_ftm_fchans_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fchans_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fchans_timeout(VOS_VOID)
{
    return at_ftm_fchans_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fchans_dspcnf
 ��������  : DSPԭ��PHY_OM_CT_F_FREQ_SET_CNF������
 �������  : pParam PHY_OM_CT_F_FREQ_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fchans_dspcnf(VOS_VOID* pParam)
{

    at_ftm_fchans_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_fchans_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fsegment_store
 ��������  : �������
 �������  : ucStoreType ��������
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_fsegment_store(VOS_UINT8 ucStoreType, FTM_SET_F_FSEGMENT_REQ_STRU* pstReq)
{
    static FTM_SET_F_FSEGMENT_REQ_STRU stReq    = {0};
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_F_FSEGMENT_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else
    {
        pstFtmFastCtInfo->ulCurCmdStepsFlag |= CT_F_STEPS_DONE_FSEGMENT;
        pstFtmFastCtInfo->usCurSegmentLen    = stReq.usSegmentLen;
        pstFtmFastCtInfo->usCurMeasOffset    = stReq.usMeasOffset;
        pstFtmFastCtInfo->usCurMeasLen       = stReq.usMeasLen;
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fsegment_setcnf
 ��������  : �������
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_fsegment_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_F_FSEGMENT_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_F_SET_FSEGMENT_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_F_FSEGMENT_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fsegment_read
 ��������  : ID_MSG_FTM_F_RD_FSEGMENT_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fsegment_read(VOS_VOID* pParam)
{
    FTM_RD_F_FSEGMENT_CNF_STRU stRdCnf = { 0 };
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    stRdCnf.ulErrCode    = ERR_MSP_SUCCESS;
    stRdCnf.usSegmentLen = pstFtmFastCtInfo->usCurSegmentLen;
    stRdCnf.usMeasOffset = pstFtmFastCtInfo->usCurMeasOffset;
    stRdCnf.usMeasLen    = pstFtmFastCtInfo->usCurMeasLen;

    return ftm_comm_send(ID_MSG_FTM_F_RD_FSEGMENT_CNF, (VOS_UINT32)&stRdCnf, sizeof(FTM_RD_F_FSEGMENT_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fsegment_set
 ��������  : ID_MSG_FTM_F_SET_FSEGMENT_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fsegment_set(VOS_VOID* pParam)
{
    FTM_SET_F_FSEGMENT_REQ_STRU* pstFtmReq      = (FTM_SET_F_FSEGMENT_REQ_STRU*)pParam;
    OM_PHY_CT_F_SEGMENT_SET_REQ_STRU stReqToDsp = { 0 };
    FCHAN_MODE_ENUM fchanMode = ftm_GetFastCTMainInfo()->enCurMode;
    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if(ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        return at_ftm_fsegment_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    /* �жϲ����Ƿ���ȷ */

    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId   = OM_PHY_CT_F_SEGMENT_SET_REQ;
    stReqToDsp.usSegment = pstFtmReq->usSegmentLen;
    stReqToDsp.measOffset= pstFtmReq->usMeasOffset;
    stReqToDsp.measLen   = pstFtmReq->usMeasLen;
    if(ERR_MSP_SUCCESS != ftm_mailbox_ct_write(fchanMode, &stReqToDsp, sizeof(OM_PHY_CT_F_SEGMENT_SET_REQ_STRU)))
    {
        return at_ftm_fsegment_setcnf(ERR_MSP_UNKNOWN);
    }
    at_ftm_fsegment_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fsegment_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fsegment_timeout(VOS_VOID)
{
    return at_ftm_fsegment_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fsegment_dspcnf
 ��������  : DSPԭ��PHY_OM_CT_F_SEGMENT_SET_CNF������
 �������  : pParam PHY_OM_CT_F_SEGMENT_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fsegment_dspcnf(VOS_VOID* pParam)
{

    at_ftm_fsegment_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_fsegment_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fpows_store
 ��������  : �������
 �������  : ucStoreType ��������
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_fpows_store(VOS_UINT8 ucStoreType, FTM_SET_F_FPOWS_REQ_STRU* pstReq)
{
    static FTM_SET_F_FPOWS_REQ_STRU stReq       = {0};
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_F_FPOWS_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else
    {
        pstFtmFastCtInfo->ulCurCmdStepsFlag |= CT_F_STEPS_DONE_FPOWS;
        pstFtmFastCtInfo->usCurTxPowerNum    = stReq.usTxPowerNum;
        (VOS_VOID)MSP_MEMCPY(pstFtmFastCtInfo->asCurTxPowerList, stReq.asTxPower,sizeof(pstFtmFastCtInfo->asCurTxPowerList));
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fpows_setcnf
 ��������  : �������
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_fpows_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_F_FPOWS_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_F_SET_FPOWS_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_F_FPOWS_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fpows_read
 ��������  : ID_MSG_FTM_F_RD_FPOWS_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fpows_read(VOS_VOID* pParam)
{
    FTM_RD_F_FPOWS_CNF_STRU stRdCnf             = { 0 };
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    stRdCnf.ulErrCode    = ERR_MSP_SUCCESS;
    stRdCnf.usTxPowerNum = pstFtmFastCtInfo->usCurTxPowerNum;
    (VOS_VOID)MSP_MEMCPY(stRdCnf.asTxPower, pstFtmFastCtInfo->asCurTxPowerList, sizeof(stRdCnf.asTxPower));

    return ftm_comm_send(ID_MSG_FTM_F_RD_FPOWS_CNF, (VOS_UINT32)&stRdCnf, sizeof(FTM_RD_F_FPOWS_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fpows_set
 ��������  : ID_MSG_FTM_F_SET_FPOWS_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fpows_set(VOS_VOID* pParam)
{
    FTM_SET_F_FPOWS_REQ_STRU* pstFtmReq         = (FTM_SET_F_FPOWS_REQ_STRU*)pParam;
    OM_PHY_CT_F_TXPOW_SET_REQ_STRU stReqToDsp   = { 0 };

    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if(ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        return at_ftm_fpows_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    /* �жϲ����Ƿ���ȷ */

    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId      = OM_PHY_CT_F_TXPOW_SET_REQ;
    stReqToDsp.usTxPowerNum = pstFtmReq->usTxPowerNum;
    (VOS_VOID)MSP_MEMCPY(stReqToDsp.ausTxPower, pstFtmReq->asTxPower, sizeof(stReqToDsp.ausTxPower));
    if(ERR_MSP_SUCCESS != ftm_mailbox_ltect_write(&stReqToDsp, sizeof(OM_PHY_CT_F_TXPOW_SET_REQ_STRU)))
    {
        return at_ftm_fpows_setcnf(ERR_MSP_UNKNOWN);
    }

    at_ftm_fpows_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fpows_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fpows_timeout(VOS_VOID)
{
    return at_ftm_fpows_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fpows_dspcnf
 ��������  : DSPԭ��PHY_OM_CT_F_TXPOW_SET_CNF������
 �������  : pParam PHY_OM_CT_F_TXPOW_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fpows_dspcnf(VOS_VOID* pParam)
{

    at_ftm_fpows_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_fpows_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fpas_store
 ��������  : �������
 �������  : ucStoreType ��������
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_fpas_store(VOS_UINT8 ucStoreType, FTM_SET_F_FPAS_REQ_STRU* pstReq)
{
    static FTM_SET_F_FPAS_REQ_STRU stReq        = {0};
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_F_FPAS_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else
    {
        pstFtmFastCtInfo->ulCurCmdStepsFlag |= CT_F_STEPS_DONE_FPAS;
        pstFtmFastCtInfo->usCurPaLevelNum    = stReq.usPaLevelNum;
        (VOS_VOID)MSP_MEMCPY(pstFtmFastCtInfo->aucCurPaLevelList, stReq.aucPaLevelList, sizeof(pstFtmFastCtInfo->aucCurPaLevelList));
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fpas_setcnf
 ��������  : �������
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_fpas_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_F_FPAS_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_F_SET_FPAS_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_F_FPAS_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fpas_read
 ��������  : ID_MSG_FTM_F_RD_FPAS_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fpas_read(VOS_VOID* pParam)
{
    FTM_RD_F_FPAS_CNF_STRU stRdCnf = { 0 };
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    stRdCnf.ulErrCode    = ERR_MSP_SUCCESS;
    stRdCnf.usPaLevelNum = pstFtmFastCtInfo->usCurPaLevelNum;
    (VOS_VOID)MSP_MEMCPY(stRdCnf.aucPaLevelList,  pstFtmFastCtInfo->aucCurPaLevelList, sizeof(stRdCnf.aucPaLevelList));

    return ftm_comm_send(ID_MSG_FTM_F_RD_FPAS_CNF, (VOS_UINT32)&stRdCnf, sizeof(FTM_RD_F_FPAS_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fpas_set
 ��������  : ID_MSG_FTM_F_SET_FPAS_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fpas_set(VOS_VOID* pParam)
{
    FTM_SET_F_FPAS_REQ_STRU* pstFtmReq          = (FTM_SET_F_FPAS_REQ_STRU*)pParam;
    OM_PHY_CT_F_PA_SET_REQ_STRU stReqToDsp      = { 0 };
    FCHAN_MODE_ENUM fchanMode = ftm_GetFastCTMainInfo()->enCurMode;
    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if(ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        return at_ftm_fpas_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    /* �жϲ����Ƿ���ȷ */

    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId    = OM_PHY_CT_F_PA_SET_REQ;
    stReqToDsp.usLevelNum = pstFtmReq->usPaLevelNum;
    (VOS_VOID)MSP_MEMCPY(stReqToDsp.aucLvlList, pstFtmReq->aucPaLevelList, sizeof(stReqToDsp.aucLvlList));
    if(ERR_MSP_SUCCESS != ftm_mailbox_ct_write(fchanMode, &stReqToDsp, sizeof(OM_PHY_CT_F_PA_SET_REQ_STRU)))
    {
        return at_ftm_fpas_setcnf(ERR_MSP_UNKNOWN);
    }
    at_ftm_fpas_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fpas_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fpas_timeout(VOS_VOID)
{
    return at_ftm_fpas_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fpas_dspcnf
 ��������  : DSPԭ��PHY_OM_CT_F_PA_SET_CNF������
 �������  : pParam PHY_OM_CT_F_PA_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fpas_dspcnf(VOS_VOID* pParam)
{

    at_ftm_fpas_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_fpas_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_flnas_store
 ��������  : �������
 �������  : ucStoreType ��������
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_flnas_store(VOS_UINT8 ucStoreType, FTM_SET_F_AAGC_REQ_STRU* pstReq)
{
    static FTM_SET_F_AAGC_REQ_STRU stReq        = {0};
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_F_AAGC_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else
    {
        pstFtmFastCtInfo->ulCurCmdStepsFlag |= CT_F_STEPS_DONE_FLNAS;
        pstFtmFastCtInfo->usCurAagcNum       = stReq.usAagcNum;
        (VOS_VOID)MSP_MEMCPY(pstFtmFastCtInfo->aucCurAagcList, stReq.aucAAGCValue, sizeof(pstFtmFastCtInfo->aucCurAagcList));
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_flnas_setcnf
 ��������  : �������
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_flnas_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_F_AAGC_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_F_SET_FLNAS_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_F_AAGC_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_flnas_read
 ��������  : ID_MSG_FTM_F_RD_FLNAS_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_flnas_read(VOS_VOID* pParam)
{
    FTM_RD_F_AAGC_CNF_STRU stRdCnf = { 0 };
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    stRdCnf.ulErrCode = ERR_MSP_SUCCESS;
    stRdCnf.usAagcNum = pstFtmFastCtInfo->usCurAagcNum;
    (VOS_VOID)MSP_MEMCPY(stRdCnf.aucAAGCValue, pstFtmFastCtInfo->aucCurAagcList, sizeof(stRdCnf.aucAAGCValue));

    return ftm_comm_send(ID_MSG_FTM_F_RD_FLNAS_CNF, (VOS_UINT32)&stRdCnf, sizeof(FTM_RD_F_AAGC_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_flnas_set
 ��������  : ID_MSG_FTM_F_SET_FLNAS_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_flnas_set(VOS_VOID* pParam)
{
    FTM_SET_F_AAGC_REQ_STRU* pstFtmReq          = (FTM_SET_F_AAGC_REQ_STRU*)pParam;
    OM_PHY_CT_F_AAGC_SET_REQ_STRU stReqToDsp    = { 0 };
    FCHAN_MODE_ENUM fchanMode = ftm_GetFastCTMainInfo()->enCurMode;
    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if(ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        return at_ftm_flnas_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    /* �жϲ����Ƿ���ȷ */

    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId   = OM_PHY_CT_F_AAGC_SET_REQ;
    stReqToDsp.usAagcNum = pstFtmReq->usAagcNum;
    (VOS_VOID)MSP_MEMCPY(stReqToDsp.aucAAGCValue, pstFtmReq->aucAAGCValue, sizeof(stReqToDsp.aucAAGCValue));
    if(ERR_MSP_SUCCESS != ftm_mailbox_ct_write(fchanMode, &stReqToDsp, sizeof(OM_PHY_CT_F_AAGC_SET_REQ_STRU)))
    {
        return at_ftm_flnas_setcnf(ERR_MSP_UNKNOWN);
    }
    at_ftm_flnas_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_flnas_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_flnas_timeout(VOS_VOID)
{
    return at_ftm_flnas_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_flnas_dspcnf
 ��������  : DSPԭ��PHY_OM_CT_F_AAGC_SET_CNF������
 �������  : pParam PHY_OM_CT_F_AAGC_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_flnas_dspcnf(VOS_VOID* pParam)
{

    at_ftm_flnas_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_flnas_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fpdms_store
 ��������  : �������
 �������  : ucStoreType ��������
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_fpdms_store(VOS_UINT8 ucStoreType, FTM_SET_F_FPDMS_REQ_STRU* pstReq)
{
    static FTM_SET_F_FPDMS_REQ_STRU stReq    = {0};
    FTM_CT_F_MANAGE_INFO_STRU *pstFCtMainInfo = ftm_GetFastCTMainInfo();

    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if ((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_F_FPDMS_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else
    {
        pstFCtMainInfo->ulCurCmdStepsFlag |= CT_F_STEPS_DONE_FPDMS;
        pstFCtMainInfo->ulFpdmsSw          = stReq.ulSwitch;
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fpdms_setcnf
 ��������  : �������
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_fpdms_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_F_FPDMS_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_FPDMS_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_F_FPDMS_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fpdms_read
 ��������  : ID_MSG_FTM_RD_FPDMS_RD ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fpdms_read(VOS_VOID* pParam)
{
    FTM_RD_F_FPDMS_CNF_STRU stRdCnf          = { 0 };
    FTM_CT_F_MANAGE_INFO_STRU *stFCtMainInfo = ftm_GetFastCTMainInfo();

    stRdCnf.ulErrCode = ERR_MSP_SUCCESS;
    stRdCnf.ulSwitch  = stFCtMainInfo->ulFpdmsSw;

    return ftm_comm_send(ID_MSG_FTM_RD_FPDMS_CNF, (VOS_UINT32)&stRdCnf, sizeof(FTM_RD_F_FPDMS_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fpdms_set
 ��������  : ID_MSG_FTM_F_SET_FPDMS_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fpdms_set(VOS_VOID* pParam)
{
    FTM_SET_F_FPDMS_REQ_STRU* pstFtmReq       = (FTM_SET_F_FPDMS_REQ_STRU*)pParam;
    OM_PHY_CT_F_FPDMS_SET_REQ_STRU stReqToDsp = { 0 };

    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if (ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        return at_ftm_fpdms_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId    = OM_PHY_CT_F_FPDMS_REQ;
    stReqToDsp.ulIsEnable = pstFtmReq->ulSwitch;
    if(ERR_MSP_SUCCESS != ftm_mailbox_ltect_write(&stReqToDsp, sizeof(OM_PHY_CT_F_FPDMS_SET_REQ_STRU)))
    {
        return at_ftm_fpdms_setcnf(ERR_MSP_UNKNOWN);
    }

    at_ftm_fpdms_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fpdms_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fpdms_timeout(VOS_VOID)
{
    return at_ftm_fpdms_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fpdms_dspcnf
 ��������  : DSPԭ��PHY_OM_CT_F_FPDMS_CNF������
 �������  : pParam PHY_OM_CT_F_FPDMS_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fpdms_dspcnf(VOS_VOID* pParam)
{

    at_ftm_fpdms_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_fpdms_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_ftxwave_store
 ��������  : �������
 �������  : ucStoreType ��������
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_ftxwave_store(VOS_UINT8 ucStoreType, FTM_SET_F_FTXWAVE_REQ_STRU* pstReq)
{
    static FTM_SET_F_FTXWAVE_REQ_STRU stReq  = {0};
    FTM_CT_F_MANAGE_INFO_STRU *pstFCtMainInfo = ftm_GetFastCTMainInfo();

    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if ((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_F_FTXWAVE_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else
    {
        pstFCtMainInfo->ulCurCmdStepsFlag |= CT_F_STEPS_DONE_FTXWAVE;
        pstFCtMainInfo->ucCurWaveType      = (VOS_UINT8)stReq.usWaveType;
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_ftxwave_setcnf
 ��������  : �������
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_ftxwave_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_F_FTXWAVE_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_F_SET_FTXWAVE_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_F_FTXWAVE_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_ftxwave_read
 ��������  : ID_MSG_FTM_F_RD_FTXWAVE_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_ftxwave_read(VOS_VOID* pParam)
{
    FTM_RD_F_FTXWAVE_CNF_STRU stRdCnf         = { 0 };
    FTM_CT_F_MANAGE_INFO_STRU *pstFCtMainInfo = ftm_GetFastCTMainInfo();

    stRdCnf.ulErrCode  = ERR_MSP_SUCCESS;
    stRdCnf.usWaveType = pstFCtMainInfo->ucCurWaveType;

    return ftm_comm_send(ID_MSG_FTM_F_RD_FTXWAVE_CNF, (VOS_UINT32)&stRdCnf, sizeof(FTM_RD_F_FTXWAVE_CNF_STRU));
}
static VOS_UINT8 ftxwave_is_para_correct(VOS_INT16 wave)
{
    /*lint -e685*/
	/*lint -e568*/
	if (((wave >= 0) && (wave <= 6))||(wave == 11))
	/*lint +e568*/
	/*lint +e685*/	
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*****************************************************************************
 �� �� ��  : at_ftm_ftxwave_set
 ��������  : ID_MSG_FTM_F_SET_FTXWAVE_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_ftxwave_set(VOS_VOID* pParam)
{
    FTM_SET_F_FTXWAVE_REQ_STRU* pstFtmReq      = (FTM_SET_F_FTXWAVE_REQ_STRU*)pParam;
    OM_PHY_CT_F_TXWAVE_SET_REQ_STRU stReqToDsp = { 0 };
    FCHAN_MODE_ENUM fchanMode = ftm_GetFastCTMainInfo()->enCurMode;
    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if (ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        return at_ftm_ftxwave_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId    = OM_PHY_CT_F_TXWAVE_SET_REQ;
    stReqToDsp.usWaveType = pstFtmReq->usWaveType;
	/*lint -save -e713*/
    if(FALSE == ftxwave_is_para_correct(stReqToDsp.usWaveType))
	/*lint -restore*/	
    {
        return at_ftm_ftxwave_setcnf(ERR_MSP_INVALID_PARAMETER);
    }
    if(ERR_MSP_SUCCESS != ftm_mailbox_ct_write(fchanMode, &stReqToDsp, sizeof(OM_PHY_CT_F_TXWAVE_SET_REQ_STRU)))
    {
        return at_ftm_ftxwave_setcnf(ERR_MSP_UNKNOWN);
    }

    at_ftm_ftxwave_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_ftxwave_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_ftxwave_timeout(VOS_VOID)
{
    return at_ftm_ftxwave_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_ftxwave_dspcnf
 ��������  : DSPԭ��PHY_OM_CT_F_TXWAVE_SET_CNF������
 �������  : pParam PHY_OM_CT_F_TXWAVE_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_ftxwave_dspcnf(VOS_VOID* pParam)
{

    at_ftm_ftxwave_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_ftxwave_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fstart_store
 ��������  : �������
 �������  : ucStoreType ��������
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_fstart_store(VOS_UINT8 ucStoreType, FTM_SET_F_TRIGGER_REQ_STRU* pstReq)
{
    static FTM_SET_F_TRIGGER_REQ_STRU stReq     = {0};
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_F_TRIGGER_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else
    {
         pstFtmFastCtInfo->ulCurCmdStepsFlag |= CT_F_STEPS_DONE_FSTART;
         pstFtmFastCtInfo->ucCurTriggerType   = stReq.ucType;
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fstart_setcnf
 ��������  : �������
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_fstart_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_F_TRIGGER_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_F_SET_FSTART_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_F_TRIGGER_CNF_STRU));
}

/**********************************************************************************

��������1:

    ������ʹ����AT^FCHANS�·��ɹ�֮��
    ����ͨ����У׼��AT^FPOWS��AT^FPAS��AT^FSEGMENT�����·��ɹ�֮��
    ����ͨ����У׼��AT^FLNAS��AT^FSEGMENT�����·��ɹ�֮��

��������2:

    MSP��AT^FCHANS���ж�����Ӧ�����£�

    a)�����AT^FCHANS�����������ŵ���û�����������ŵ���У׼��������ֻ����0����1��2ʱ���ش���
    b)�����AT^FCHANS�����������ŵ���û�����������ŵ�����У׼����0��1��2ʱ�����ش���
    c)�����AT^FCHANSͬʱ����������/�����ŵ�;У׼�������ǿ�����0��1��2��

У׼����:

    0   ����ͨ��У׼
    1   ����ͨ��У׼������Ĭ��Ϊ˫ͨ����
    2   ����/����ͨ��ͬʱУ׼������Ĭ��Ϊ˫ͨ����

***********************************************************************************/
static VOS_BOOL at_ftm_fstart_setparaIsCorrect(FTM_SET_F_TRIGGER_REQ_STRU* pstFtmReq)
{
    VOS_UINT8 bRet = TRUE;
	FTM_CT_F_CMD_STEPS_FLAG_ENUM_UINT32 ulStepFlag = 0;

    if ( START_TRIGGER_TYPE_TX == pstFtmReq->ucType)
    {
        /* 0x1E ���� CT_F_STEPS_DONE_FCHANS | CT_F_STEPS_DONE_FSEGMENT |CT_F_STEPS_DONE_FPOWS |CT_F_STEPS_DONE_FPAS */
        ulStepFlag = CT_F_STEPS_DONE_FSEGMENT |CT_F_STEPS_DONE_FCHANS|CT_F_STEPS_DONE_FPAS;
        if (ftm_CheckCmdSteps(ulStepFlag) == FALSE)
        {
            bRet = FALSE;
        }

    }
    else if( START_TRIGGER_TYPE_RX == pstFtmReq->ucType)
    {
        /* 0x3E ���� CT_F_STEPS_DONE_FCHANS | CT_F_STEPS_DONE_FSEGMENT |CT_F_STEPS_DONE_FPOWS |CT_F_STEPS_DONE_FPAS|CT_F_STEPS_DONE_FLNAS */
        /* Added by daizhicheng without CT_F_STEPS_DONE_FPOWS*/
        ulStepFlag = CT_F_STEPS_DONE_FSEGMENT |CT_F_STEPS_DONE_FCHANS|CT_F_STEPS_DONE_FPAS | CT_F_STEPS_DONE_FLNAS;
        if (ftm_CheckCmdSteps(ulStepFlag) == FALSE)
        {
            bRet = FALSE;
        }
    }
    else if( START_TRIGGER_TYPE_TXRX == pstFtmReq->ucType)
    {
        /* 0x3E ���� CT_F_STEPS_DONE_FCHANS | CT_F_STEPS_DONE_FSEGMENT |CT_F_STEPS_DONE_FPOWS |CT_F_STEPS_DONE_FPAS|CT_F_STEPS_DONE_FLNAS */
        /* Added by daizhicheng without CT_F_STEPS_DONE_FPOWS*/
        ulStepFlag = CT_F_STEPS_DONE_FSEGMENT |CT_F_STEPS_DONE_FCHANS|CT_F_STEPS_DONE_FPAS | CT_F_STEPS_DONE_FLNAS;
        if (ftm_CheckCmdSteps(ulStepFlag) == FALSE)
        {
            bRet = FALSE;
        }
    }
    else if(START_TRIGGER_TYPE_MAXTX == pstFtmReq->ucType)
	{
	    ulStepFlag = CT_F_STEPS_DONE_FTXWAVE|CT_F_STEPS_DONE_FSEGMENT
			        |CT_F_STEPS_DONE_FCHANS  |CT_F_STEPS_DONE_FPAS;
	    if(ftm_CheckCmdSteps(ulStepFlag) == FALSE)
	    {
	        bRet = FALSE;
	    }

	}
    else
    {
        /* �Ƿ�У׼���� */
        bRet = FALSE;
    }

    return bRet;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fstart_set
 ��������  : ID_MSG_FTM_F_SET_FSTART_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fstart_set(VOS_VOID* pParam)
{
    FTM_SET_F_TRIGGER_REQ_STRU* pstFtmReq       = (FTM_SET_F_TRIGGER_REQ_STRU*)pParam;
    OM_PHY_CT_F_TRIGGER_SET_REQ_STRU stReqToDsp = { 0 };
    FCHAN_MODE_ENUM fchanMode = ftm_GetFastCTMainInfo()->enCurMode;
    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if(ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        return at_ftm_fstart_setcnf(ERR_MSP_UE_MODE_ERR);
    }
#if (1)
    /* �жϲ����Ƿ���ȷ */
    if(at_ftm_fstart_setparaIsCorrect(pstFtmReq) == FALSE)
    {
        return at_ftm_fstart_setcnf(ERR_MSP_INVALID_PARAMETER);
    }
#endif
    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId = OM_PHY_CT_F_TRIGGER_SET_REQ;
    stReqToDsp.ucType  = pstFtmReq->ucType;
    if(ERR_MSP_SUCCESS != ftm_mailbox_ct_write(fchanMode, &stReqToDsp, sizeof(OM_PHY_CT_F_TRIGGER_SET_REQ_STRU)))
    {
        return at_ftm_fstart_setcnf(ERR_MSP_UNKNOWN);
    }
    at_ftm_fstart_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fstart_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fstart_timeout(VOS_VOID)
{
    return at_ftm_fstart_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fstart_dspcnf
 ��������  : DSPԭ��PHY_OM_CT_F_TRIGGER_SET_CNF������
 �������  : pParam PHY_OM_CT_F_TRIGGER_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fstart_dspcnf(VOS_VOID* pParam)
{

    at_ftm_fstart_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_fstart_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fstart_readcnf
 ��������  : �������
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_fstart_readcnf(VOS_UINT8 ucType, VOS_UINT8 ucStatus, VOS_UINT32 ulErrCode)
{
    FTM_RD_F_TRIGGER_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;
    stCnf.ucType    = ucType;
    stCnf.ucStatus  = ucStatus;

    return ftm_comm_send(ID_MSG_FTM_F_RD_FSTART_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_RD_F_TRIGGER_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fstart_readtimeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fstart_read_timeout(VOS_VOID)
{
    return at_ftm_fstart_readcnf(0, 0, ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fstart_read
 ��������  : ID_MSG_FTM_F_RD_FSTART_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fstart_read(VOS_VOID* pParam)
{
    OM_PHY_CT_F_TRIGGER_RD_REQ_STRU stReqToDsp  = { 0 };
    FCHAN_MODE_ENUM fchanMode = ftm_GetFastCTMainInfo()->enCurMode;
    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if(ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        return at_ftm_fstart_readcnf(0, 0, ERR_MSP_UE_MODE_ERR);
    }
    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId = OM_PHY_CT_F_TRIGGER_RD_REQ;
    if(ERR_MSP_SUCCESS != ftm_mailbox_ct_write(fchanMode, &stReqToDsp, sizeof(OM_PHY_CT_F_TRIGGER_RD_REQ_STRU)))
    {
        return at_ftm_fstart_readcnf(0, 0, ERR_MSP_UNKNOWN);
    }
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fstart_readdspcnf
 ��������  : DSPԭ��PHY_OM_CT_F_TRIGGER_RD_CNF������
 �������  : pParam PHY_OM_CT_F_TRIGGER_RD_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fstart_read_dspcnf(VOS_VOID* pParam)
{
    PHY_OM_CT_F_TRIGGER_RD_CNF_STRU* pDspCnf = (PHY_OM_CT_F_TRIGGER_RD_CNF_STRU*)pParam;

    return at_ftm_fstart_readcnf(pDspCnf->ucType, pDspCnf->ucStatus, ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_frssis_set
 ��������  : ID_MSG_FTM_F_SET_FPAS_REQ ������
             �ж�DSP�Ƿ������ϱ��������������ϱ��򽫿���ȫ�ֻ��沢��������أ�δ�ϱ��򷵻ش�����Ϣ
 �������  : pParam FTM_SET_F_FRSSIS_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_frssis_set(VOS_VOID* pParam)
{
    VOS_BOOL bFreqExist = FALSE;
    VOS_UINT16 usTmp       = 0;

    FTM_SET_F_FRSSIS_CNF_STRU stCnf             = { 0 };
    FTM_SET_F_FRSSIS_REQ_STRU* pstFtmReq        = (FTM_SET_F_FRSSIS_REQ_STRU*)(pParam);
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if(ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        stCnf.ulErrCode = ERR_MSP_UE_MODE_ERR;

        return ftm_comm_send(ID_MSG_FTM_F_SET_FRSSIS_CNF,
            (VOS_UINT32)&stCnf, sizeof(FTM_SET_F_FRSSIS_CNF_STRU));
    }

    /* �жϲ����Ƿ���ȷ */
    if(ftm_CheckCmdSteps(CT_F_STEPS_DONE_FRSSIS_IND) != TRUE )
    {
        stCnf.ulErrCode = ERR_MSP_INVALID_PARAMETER;

        return ftm_comm_send(ID_MSG_FTM_F_SET_FRSSIS_CNF,
            (VOS_UINT32)&stCnf, sizeof(FTM_SET_F_FRSSIS_CNF_STRU));
    }

    /* �ж������е��Ƿ�������û������õ������ŵ������� */
    for(usTmp = 0 ; usTmp < pstFtmFastCtInfo->usCurDlListNum ; usTmp ++)
    {
        if (pstFtmFastCtInfo->ausCurDlFreqInfo[usTmp] == pstFtmReq->usDLFreq)
        {
            bFreqExist = TRUE;
            break; /* �ҵ���һ��ƥ��������ŵ��žͷ��� */
        }
    }

    if(bFreqExist == FALSE)
    {
       stCnf.ulErrCode = ERR_MSP_NOT_SET_CHAN;

       return ftm_comm_send(ID_MSG_FTM_F_SET_FRSSIS_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_F_FRSSIS_CNF_STRU));
    }

    /* ����ȫ�ֱ����еĽ�������������Ӧ�ṹ�������� */
    stCnf.ulErrCode    = ERR_MSP_SUCCESS;
    /*Modify by daizhicheng for using at^flnas channel number */
    //stCnf.usRSSIPowNum = pstFtmFastCtInfo->usCurTxPowerNum;
    stCnf.usRSSIPowNum = pstFtmFastCtInfo->usCurAagcNum;
    (VOS_VOID)MSP_MEMCPY(stCnf.ausRxANT1RSSI, pstFtmFastCtInfo->ausRxANT1RSSI[usTmp], sizeof(stCnf.ausRxANT1RSSI));
    (VOS_VOID)MSP_MEMCPY(stCnf.ausRxANT2RSSI, pstFtmFastCtInfo->ausRxANT2RSSI[usTmp], sizeof(stCnf.ausRxANT2RSSI));

    return ftm_comm_send(ID_MSG_FTM_F_SET_FRSSIS_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_F_FRSSIS_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_frssis_dspind
 ��������  : DSPԭ��PHY_OM_CT_F_MEAS_RSSI_IND������
             ����DSP�����ϱ���RSSI����ֵ:���������������ȫ�ֻ�����
             ���������󣬸���Ϣ�����ϱ�һ��,����Ƶ��������ͬʱ�ϱ�
 �������  : pParam PHY_OM_CT_F_MEAS_RSSI_IND_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_frssis_dspind(VOS_VOID* pParam)
{
    VOS_UINT16 usTmpi = 0;
    VOS_UINT16 usTmpj = 0;
    CT_F_ANT_RSSI_STRU* pstRSSI = NULL;

    PHY_OM_CT_F_MEAS_RSSI_IND_STRU* pstRttRssi  = (PHY_OM_CT_F_MEAS_RSSI_IND_STRU*)pParam;
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    HAL_SDMLOG("\n ENTER at_ftm_frssis_dspind, Addr: 0x%x, ulMsgId: 0x%x \n", (VOS_UINT32)pstRttRssi, pstRttRssi->ulMsgId);

    pstFtmFastCtInfo->ulCurCmdStepsFlag |= CT_F_STEPS_DONE_FRSSIS_IND;

    for(usTmpi = 0 ; usTmpi < FREQ_MAX_NUM ; usTmpi ++)
    {
        for(usTmpj = 0 ; usTmpj < POW_MAX_NUM ; usTmpj ++)
        {
            pstRSSI = &(pstRttRssi->astRxANTRSSI[usTmpi][usTmpj]);

            /* ǿ�Ƹ���֮ǰ������ȫ�ֽṹ�е�RSSI����ֵ */
            pstFtmFastCtInfo->ausRxANT1RSSI[usTmpi][usTmpj] = (VOS_UINT16)(pstRSSI->sRxANT1RSSI);
            pstFtmFastCtInfo->ausRxANT2RSSI[usTmpi][usTmpj] = (VOS_UINT16)(pstRSSI->sRxANT2RSSI);
        }
    }

    return ERR_MSP_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcmtms_read
 ��������  : ID_MSG_FTM_F_RD_FCMTMS_REQ ������
             ��ȫ�ֻ����ж�ȡ�¶�ֵ�б�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fcmtms_read(VOS_VOID* pParam)
{
    FTM_RD_F_FCMTMS_CNF_STRU stRdCnf            = { 0 };
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    stRdCnf.ulErrCode  = ERR_MSP_SUCCESS;
    stRdCnf.usCmtmsNum = pstFtmFastCtInfo->usCmtmsNum;
    (VOS_VOID)MSP_MEMCPY(stRdCnf.ausCmtms, pstFtmFastCtInfo->ausCmtms, sizeof(stRdCnf.ausCmtms));

    return ftm_comm_send(ID_MSG_FTM_F_RD_FCMTMS_CNF, (VOS_UINT32)&stRdCnf, sizeof(FTM_RD_F_FCMTMS_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcmtms_dspind
 ��������  : DSPԭ��PHY_OM_CT_F_MEAS_CMTMS_IND������
             ���¶�ֵ�б��浽ȫ�ֻ�����
 �������  : pParam PHY_OM_CT_F_MEAS_CMTMS_IND_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fcmtms_dspind(VOS_VOID* pParam)
{
    PHY_OM_CT_F_MEAS_CMTMS_IND_STRU* pDspInd  = (PHY_OM_CT_F_MEAS_CMTMS_IND_STRU*)pParam;
    FTM_CT_F_MANAGE_INFO_STRU *pstFCtMainInfo = ftm_GetFastCTMainInfo();

    pstFCtMainInfo->ulCurCmdStepsFlag |= CT_F_STEPS_DONE_FCMTMS_IND; /* �����ѳɹ��ϱ���־ */
	pstFCtMainInfo->usCmtmsNum         = pDspInd->usCmtmsNum;
	(VOS_VOID)MSP_MEMCPY(pstFCtMainInfo->ausCmtms, pDspInd->ausCmtms, sizeof(pstFCtMainInfo->ausCmtms));

    return ERR_MSP_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fmaxpower_store
 ��������  : �������
 �������  : ucStoreType ��������
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_fmaxpower_store(VOS_UINT8 ucStoreType, FTM_SET_F_FMAXPOWER_REQ_STRU* pstReq)
{
    static FTM_SET_F_FMAXPOWER_REQ_STRU stReq   = {0};
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_F_FMAXPOWER_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else
    {
        pstFtmFastCtInfo->ulCurCmdStepsFlag         |= CT_F_STEPS_DONE_FMAXPOWER;
        pstFtmFastCtInfo->ulFmaxpower_usPaLevelNum   = stReq.usPaLevelNum;
		pstFtmFastCtInfo->ulFmaxpower_usPaReduceGain = stReq.usPaReduceGain;
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fmaxpower_setcnf
 ��������  : ����ID_MSG_FTM_F_SET_FMAXPOWER_CNF
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_fmaxpower_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_F_FMAXPOWER_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_F_SET_FMAXPOWER_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_F_FMAXPOWER_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fmaxpower_read
 ��������  : ID_MSG_FTM_F_RD_FMAXPOWER_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fmaxpower_read(VOS_VOID* pParam)
{
    FTM_RD_F_FMAXPOWER_CNF_STRU stRdCnf         = { 0 };
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    stRdCnf.ulErrCode      = ERR_MSP_SUCCESS;
    stRdCnf.usPaLevelNum   = (VOS_UINT16)pstFtmFastCtInfo->ulFmaxpower_usPaLevelNum;
	stRdCnf.usPaReduceGain = (VOS_UINT16)pstFtmFastCtInfo->ulFmaxpower_usPaReduceGain;

    return ftm_comm_send(ID_MSG_FTM_F_RD_FMAXPOWER_CNF, (VOS_UINT32)&stRdCnf, sizeof(FTM_RD_F_FMAXPOWER_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fmaxpower_set
 ��������  : ID_MSG_FTM_F_SET_FPAPOWER_REQ ������
             ��DSP����OM_PHY_CT_F_MAX_POWER_SET_REQԭ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fmaxpower_set(VOS_VOID* pParam)
{
    FTM_SET_F_FMAXPOWER_REQ_STRU* pstFtmReq       = (FTM_SET_F_FMAXPOWER_REQ_STRU*)pParam;
    OM_PHY_CT_F_MAX_POWER_SET_REQ_STRU stReqToDsp = { 0 };

    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if(ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        return at_ftm_fmaxpower_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId        = OM_PHY_CT_F_MAX_POWER_SET_REQ;
    stReqToDsp.usPaLevelNum   = pstFtmReq->usPaLevelNum;
    stReqToDsp.usPaReduceGain = pstFtmReq->usPaReduceGain;
    if(ERR_MSP_SUCCESS != ftm_mailbox_ltect_write(&stReqToDsp, sizeof(OM_PHY_CT_F_MAX_POWER_SET_REQ_STRU)))
    {
        return at_ftm_fmaxpower_setcnf(ERR_MSP_UNKNOWN);
    }

    at_ftm_fmaxpower_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fmaxpower_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fmaxpower_timeout(VOS_VOID)
{
    return at_ftm_fmaxpower_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fmaxpower_dspcnf
 ��������  : DSPԭ��PHY_OM_CT_F_MAX_POWER_SET_CNF������
 �������  : pParam PHY_OM_CT_F_MAX_POWER_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fmaxpower_dspcnf(VOS_VOID* pParam)
{

    at_ftm_fmaxpower_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_fmaxpower_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fpapower_store
 ��������  : �������
 �������  : ucStoreType ��������
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_fpapower_store(VOS_UINT8 ucStoreType, FTM_SET_F_FPAPOWER_REQ_STRU* pstReq)
{
    static FTM_SET_F_FPAPOWER_REQ_STRU stReq    = {0};
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_F_FPAPOWER_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else
    {
        pstFtmFastCtInfo->ulCurCmdStepsFlag      |= CT_F_STEPS_DONE_FPAPOWER;
        pstFtmFastCtInfo->ulFpapower_usPaLeverNum = stReq.usPaLeverNum;
        (VOS_VOID)MSP_MEMCPY(pstFtmFastCtInfo->usFpapower_list, stReq.usMaxPowerList, sizeof(pstFtmFastCtInfo->usFpapower_list));
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fpapower_setcnf
 ��������  : ����ID_MSG_FTM_F_SET_FPAPOWER_CNF
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_fpapower_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_F_FPAPOWER_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_F_SET_FPAPOWER_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_F_FPAPOWER_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fpapower_read
 ��������  : ID_MSG_FTM_F_RD_FPAPOWER_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fpapower_read(VOS_VOID* pParam)
{
    FTM_RD_F_FPAPOWER_CNF_STRU stRdCnf          = { 0 };
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    stRdCnf.ulErrCode    = ERR_MSP_SUCCESS;
    stRdCnf.usPaLeverNum = (VOS_UINT16)(pstFtmFastCtInfo->ulFpapower_usPaLeverNum);
    (VOS_VOID)MSP_MEMCPY(stRdCnf.usMaxPowerList, pstFtmFastCtInfo->usFpapower_list, sizeof(stRdCnf.usMaxPowerList));

    return ftm_comm_send(ID_MSG_FTM_F_RD_FPAPOWER_CNF, (VOS_UINT32)&stRdCnf, sizeof(FTM_RD_F_FPAPOWER_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fpapower_set
 ��������  : ID_MSG_FTM_F_SET_FPAPOWER_REQ ������
             ��DSP����OM_PHY_CT_F_PA_POWER_SET_REQԭ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fpapower_set(VOS_VOID* pParam)
{
    FTM_SET_F_FPAPOWER_REQ_STRU* pstFtmReq       = (FTM_SET_F_FPAPOWER_REQ_STRU*)pParam;
    OM_PHY_CT_F_PA_POWER_SET_REQ_STRU stReqToDsp = { 0 };

    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if(ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        return at_ftm_fpapower_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId      = OM_PHY_CT_F_PA_POWER_SET_REQ;
    stReqToDsp.usPaLevelNum = pstFtmReq->usPaLeverNum;
    (VOS_VOID)MSP_MEMCPY(stReqToDsp.asMaxPwrList, pstFtmReq->usMaxPowerList, sizeof(stReqToDsp.asMaxPwrList));
    if(ERR_MSP_SUCCESS != ftm_mailbox_ltect_write(&stReqToDsp, sizeof(OM_PHY_CT_F_PA_POWER_SET_REQ_STRU)))
    {
        return at_ftm_fpapower_setcnf(ERR_MSP_UNKNOWN);
    }

    at_ftm_fpapower_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fpapower_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fpapower_timeout(VOS_VOID)
{
    return at_ftm_fpapower_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fpapower_dspcnf
 ��������  : DSPԭ��PHY_OM_CT_F_PA_POWER_SET_CNF������
 �������  : pParam PHY_OM_CT_F_PA_POWER_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fpapower_dspcnf(VOS_VOID* pParam)
{

    at_ftm_fpapower_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_fpapower_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcaliip2s_store
 ��������  : �������
 �������  : ucStoreType ��������
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_fcaliip2s_store(VOS_UINT8 ucStoreType, FTM_SET_FCALIIP2S_REQ_STRU* pstReq)
{
    static FTM_SET_FCALIIP2S_REQ_STRU stReq     = { 0 };
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_FCALIIP2S_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else
    {
        (VOS_VOID)MSP_MEMCPY(&pstFtmFastCtInfo->stFCaliIp2sSetReq, &stReq, sizeof(FTM_SET_FCALIIP2S_REQ_STRU));

        /* ���ò�ѯ��Ϣ  */
        (VOS_VOID)MSP_MEMSET(&pstFtmFastCtInfo->stFCaliIp2sRdCnf, 0, sizeof(pstFtmFastCtInfo->stFCaliIp2sRdCnf));
        pstFtmFastCtInfo->stFCaliIp2sRdCnf.ulErrCode = ERR_MSP_SUCCESS;
        pstFtmFastCtInfo->stFCaliIp2sRdCnf.usStatus  = FTM_STATUS_EXECUTING;
        pstFtmFastCtInfo->stFCaliIp2sRdCnf.usChanNum = pstFtmFastCtInfo->stFCaliIp2sSetReq.usChanNum;
        (VOS_VOID)MSP_MEMCPY(pstFtmFastCtInfo->stFCaliIp2sRdCnf.usChan, pstFtmFastCtInfo->stFCaliIp2sSetReq.usChan,
            sizeof(pstFtmFastCtInfo->stFCaliIp2sSetReq.usChan));
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcaldip2s_setcnf
 ��������  : ����ID_MSG_FTM_SET_FCALIIP2S_CNF
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_fcaliip2s_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_FCALIIP2S_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_FCALIIP2S_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_FCALIIP2S_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcaliip2s_read
 ��������  : ID_MSG_FTM_RD_FCALIIP2S_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fcaliip2s_read(VOS_VOID* pParam)
{
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    return ftm_comm_send(ID_MSG_FTM_RD_FCALIIP2S_CNF, (VOS_UINT32)&pstFtmFastCtInfo->stFCaliIp2sRdCnf,
        sizeof(FTM_RD_FCALIIP2S_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcaliip2s_set
 ��������  : ID_MSG_FTM_SET_FCALIIP2S_REQ ������
             ��DSP����OM_PHY_CT_F_CALIIP2_SET_REQԭ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fcaliip2s_set(VOS_VOID* pParam)
{
    VOS_UINT32 i = 0;
    FTM_SET_FCALIIP2S_REQ_STRU* pstFtmReq       = (FTM_SET_FCALIIP2S_REQ_STRU*)pParam;
    OM_PHY_CT_F_CALIIP2_SET_REQ_STRU stReqToDsp = { 0 };

    FCHAN_MODE_ENUM fchanMode = ftm_GetFastCTMainInfo()->enCurMode;

    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if(ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        return at_ftm_fcaliip2s_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    /* �жϲ����Ƿ���Ч */
    if(pstFtmReq->usChanNum > FTM_CALIIP2_MAX_CHAN_NUM)
    {
        return at_ftm_fcaliip2s_setcnf(ERR_MSP_INVALID_PARAMETER);
    }

    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId   = OM_PHY_CT_F_CALIIP2_SET_REQ;
    stReqToDsp.usChanNum = pstFtmReq->usChanNum;
    for(i=0; i<pstFtmReq->usChanNum; i++)
    {
        stReqToDsp.usChan[i] = at_ftm_get_freq(fchanMode, pstFtmReq->usChan[i]);
    }

     /* ��ԭ��ֻ���͵�LTE���䣬����fchanMode */
    if(ERR_MSP_SUCCESS != ftm_mailbox_ltect_write(&stReqToDsp, sizeof(OM_PHY_CT_F_CALIIP2_SET_REQ_STRU)))
    {
        return at_ftm_fcaliip2s_setcnf(ERR_MSP_UNKNOWN);
    }

    at_ftm_fcaliip2s_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcaliip2s_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fcaliip2s_timeout(VOS_VOID)
{
    return at_ftm_fcaliip2s_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcaliip2s_dspcnf
 ��������  : DSPԭ��PHY_OM_CT_F_CALIIP2_SET_CNF������
 �������  : pParam PHY_OM_CT_F_CALIIP2_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fcaliip2s_dspcnf(VOS_VOID* pParam)
{

    at_ftm_fcaliip2s_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_fcaliip2s_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcaliip2s_dspind
 ��������  : DSPԭ��PHY_OM_CT_F_CALIIP2_IND������
             ��DSP�����ϱ�����Ϣ����ȫ�ֻ�����
 �������  : pParam PHY_OM_CT_F_CALIIP2_IND_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fcaliip2s_dspind(VOS_VOID* pParam)
{
    PHY_OM_CT_F_CALIIP2_IND_STRU* pstCaliIp2Ind = (PHY_OM_CT_F_CALIIP2_IND_STRU*)pParam;
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    pstFtmFastCtInfo->stFCaliIp2sRdCnf.ulErrCode = ERR_MSP_SUCCESS;
    pstFtmFastCtInfo->stFCaliIp2sRdCnf.usStatus  = FTM_STATUS_EXECUTED;
    pstFtmFastCtInfo->stFCaliIp2sRdCnf.usChanNum = pstCaliIp2Ind->usChanNum;
    (VOS_VOID)MSP_MEMCPY(pstFtmFastCtInfo->stFCaliIp2sRdCnf.usMain_I_DivOff, pstCaliIp2Ind->usMain_I_DivOff, sizeof(pstCaliIp2Ind->usMain_I_DivOff));
    (VOS_VOID)MSP_MEMCPY(pstFtmFastCtInfo->stFCaliIp2sRdCnf.usMain_Q_DivOff, pstCaliIp2Ind->usMain_Q_DivOff, sizeof(pstCaliIp2Ind->usMain_Q_DivOff));
    (VOS_VOID)MSP_MEMCPY(pstFtmFastCtInfo->stFCaliIp2sRdCnf.usMain_I_DivOn,  pstCaliIp2Ind->usMain_I_DivOn,  sizeof(pstCaliIp2Ind->usMain_I_DivOn));
    (VOS_VOID)MSP_MEMCPY(pstFtmFastCtInfo->stFCaliIp2sRdCnf.usMain_Q_DivOn,  pstCaliIp2Ind->usMain_Q_DivOn,  sizeof(pstCaliIp2Ind->usMain_Q_DivOn));
    (VOS_VOID)MSP_MEMCPY(pstFtmFastCtInfo->stFCaliIp2sRdCnf.usDiv_I,         pstCaliIp2Ind->usDiv_I,         sizeof(pstCaliIp2Ind->usDiv_I));
    (VOS_VOID)MSP_MEMCPY(pstFtmFastCtInfo->stFCaliIp2sRdCnf.usDiv_Q,         pstCaliIp2Ind->usDiv_Q,         sizeof(pstCaliIp2Ind->usDiv_Q));

    return ERR_MSP_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcalidcocs_store
 ��������  : �������
 �������  : ucStoreType ��������
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_fcalidcocs_store(VOS_UINT8 ucStoreType, FTM_SET_FCALIDCOCS_REQ_STRU* pstReq)
{
    static FTM_SET_FCALIDCOCS_REQ_STRU stReq    = {0};
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_FCALIDCOCS_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else
    {
        (VOS_VOID)MSP_MEMCPY(&pstFtmFastCtInfo->stFCaliDcocsSetReq, &stReq, sizeof(FTM_SET_FCALIDCOCS_REQ_STRU));

        /* ���ò�ѯ��Ϣ  */
        (VOS_VOID)MSP_MEMSET(&pstFtmFastCtInfo->stFCaliDcocsRdCnf, 0, sizeof(pstFtmFastCtInfo->stFCaliDcocsRdCnf));
        pstFtmFastCtInfo->stFCaliDcocsRdCnf.ulErrCode = ERR_MSP_SUCCESS;
        pstFtmFastCtInfo->stFCaliDcocsRdCnf.usStatus  = FTM_STATUS_EXECUTING;
        pstFtmFastCtInfo->stFCaliDcocsRdCnf.usChannel = pstFtmFastCtInfo->stFCaliDcocsSetReq.usChannel;
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcalidcocs_setcnf
 ��������  : ����ID_MSG_FTM_SET_FCALIDCOCS_CNF
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_fcalidcocs_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_FCALIDCOCS_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_FCALIDCOCS_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_FCALIDCOCS_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcalidcocs_read
 ��������  : ID_MSG_FTM_RD_FCALIDCOCS_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fcalidcocs_read(VOS_VOID* pParam)
{
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    return ftm_comm_send(ID_MSG_FTM_RD_FCALIDCOCS_CNF, (VOS_UINT32)&pstFtmFastCtInfo->stFCaliDcocsRdCnf,
        sizeof(FTM_RD_FCALIDCOCS_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcalidcocs_set
 ��������  : ID_MSG_FTM_SET_FCALIDCOCS_REQ ������
             ��DSP����OM_PHY_CT_F_CALIDCOCS_SET_REQԭ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fcalidcocs_set(VOS_VOID* pParam)
{
    FTM_SET_FCALIDCOCS_REQ_STRU* pstFtmReq       = (FTM_SET_FCALIDCOCS_REQ_STRU*)pParam;
    OM_PHY_CT_F_CALIDCOCS_SET_REQ_STRU stReqToDsp= { 0 };

    FCHAN_MODE_ENUM fchanMode = ftm_GetFastCTMainInfo()->enCurMode;

    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if(ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        return at_ftm_fcalidcocs_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId   = OM_PHY_CT_F_CALIDCOCS_SET_REQ;
    stReqToDsp.usChannel = at_ftm_get_freq(fchanMode,pstFtmReq->usChannel);

    /* ��ԭ��ֻ���͵�LTE���䣬����fchanMode */
    if(ERR_MSP_SUCCESS != ftm_mailbox_ltect_write(&stReqToDsp, sizeof(OM_PHY_CT_F_CALIDCOCS_SET_REQ_STRU)))
    {
        return at_ftm_fcalidcocs_setcnf(ERR_MSP_UNKNOWN);
    }

    at_ftm_fcalidcocs_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcalidcocs_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fcalidcocs_timeout(VOS_VOID)
{
    return at_ftm_fcalidcocs_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcalidcocs_dspcnf
 ��������  : DSPԭ��PHY_OM_CT_F_CALIDCOCS_SET_CNF������
 �������  : pParam PHY_OM_CT_F_CALIDCOCS_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fcalidcocs_dspcnf(VOS_VOID* pParam)
{

    at_ftm_fcalidcocs_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_fcalidcocs_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcalidcocs_dspind
 ��������  : DSPԭ��PHY_OM_CT_F_CALIDCOCS_IND������
             ��DSP�����ϱ�����Ϣ����ȫ�ֻ�����
 �������  : pParam PHY_OM_CT_F_CALIDCOCS_IND_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fcalidcocs_dspind(VOS_VOID* pParam)
{
    PHY_OM_CT_F_CALIDCOCS_IND_STRU* pstCaliDcocsInd = (PHY_OM_CT_F_CALIDCOCS_IND_STRU*)pParam;
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo     = ftm_GetFastCTMainInfo();

    pstFtmFastCtInfo->stFCaliDcocsRdCnf.ulErrCode = ERR_MSP_SUCCESS;
    pstFtmFastCtInfo->stFCaliDcocsRdCnf.usStatus  = FTM_STATUS_EXECUTED;

    (VOS_VOID)MSP_MEMCPY(pstFtmFastCtInfo->stFCaliDcocsRdCnf.usBLK_ANT1_I, pstCaliDcocsInd->usBLK_ANT1_I, sizeof(pstCaliDcocsInd->usBLK_ANT1_I));
    (VOS_VOID)MSP_MEMCPY(pstFtmFastCtInfo->stFCaliDcocsRdCnf.usBLK_ANT1_Q, pstCaliDcocsInd->usBLK_ANT1_Q, sizeof(pstCaliDcocsInd->usBLK_ANT1_Q));
    (VOS_VOID)MSP_MEMCPY(pstFtmFastCtInfo->stFCaliDcocsRdCnf.usNOBLK_ANT1_I, pstCaliDcocsInd->usNOBLK_ANT1_I, sizeof(pstCaliDcocsInd->usNOBLK_ANT1_I));
    (VOS_VOID)MSP_MEMCPY(pstFtmFastCtInfo->stFCaliDcocsRdCnf.usNOBLK_ANT1_Q, pstCaliDcocsInd->usNOBLK_ANT1_Q, sizeof(pstCaliDcocsInd->usNOBLK_ANT1_Q));

    (VOS_VOID)MSP_MEMCPY(pstFtmFastCtInfo->stFCaliDcocsRdCnf.usBLK_ANT2_I, pstCaliDcocsInd->usBLK_ANT2_I, sizeof(pstCaliDcocsInd->usBLK_ANT2_I));
    (VOS_VOID)MSP_MEMCPY(pstFtmFastCtInfo->stFCaliDcocsRdCnf.usBLK_ANT2_Q, pstCaliDcocsInd->usBLK_ANT2_Q, sizeof(pstCaliDcocsInd->usBLK_ANT2_Q));
    (VOS_VOID)MSP_MEMCPY(pstFtmFastCtInfo->stFCaliDcocsRdCnf.usNOBLK_ANT2_I, pstCaliDcocsInd->usNOBLK_ANT2_I, sizeof(pstCaliDcocsInd->usNOBLK_ANT2_I));
    (VOS_VOID)MSP_MEMCPY(pstFtmFastCtInfo->stFCaliDcocsRdCnf.usNOBLK_ANT2_Q, pstCaliDcocsInd->usNOBLK_ANT2_Q, sizeof(pstCaliDcocsInd->usNOBLK_ANT2_Q));

    return ERR_MSP_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcaliip2smrf_store
 ��������  : �������
 �������  : ucStoreType ��������
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_fcaliip2sMrf_store(VOS_UINT8 ucStoreType, FTM_SET_FCALIIP2SMRF_REQ_STRU* pstReq)
{
    VOS_UINT32 i =0;
    static FTM_SET_FCALIIP2SMRF_REQ_STRU stReq     = { 0 };
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_FCALIIP2SMRF_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else
    {
        (VOS_VOID)MSP_MEMCPY(&pstFtmFastCtInfo->stFCaliIp2sMrfSetReq, &stReq, sizeof(FTM_SET_FCALIIP2SMRF_REQ_STRU));

        /* ���ò�ѯ��Ϣ  */
        (VOS_VOID)MSP_MEMSET(&pstFtmFastCtInfo->stFCaliIp2sMrfRdCnf, 0, sizeof(pstFtmFastCtInfo->stFCaliIp2sMrfRdCnf));
        pstFtmFastCtInfo->stFCaliIp2sMrfRdCnf.ulErrCode = ERR_MSP_SUCCESS;
        pstFtmFastCtInfo->stFCaliIp2sMrfRdCnf.usStatus  = FTM_STATUS_EXECUTING;
        pstFtmFastCtInfo->stFCaliIp2sMrfRdCnf.usChanNum = pstFtmFastCtInfo->stFCaliIp2sMrfSetReq.usChanNum;
        for(i=0; i<pstFtmFastCtInfo->stFCaliIp2sMrfRdCnf.usChanNum; i++)
        {
            pstFtmFastCtInfo->stFCaliIp2sMrfRdCnf.usChan[i] = pstFtmFastCtInfo->stFCaliIp2sMrfSetReq.usChan[i];
        }
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcaldip2sMrf_setcnf
 ��������  : ����ID_MSG_FTM_SET_FCALIIP2SMRF_CNF
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_fcaliip2sMrf_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_FCALIIP2SMRF_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_FCALIIP2SMRF_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_FCALIIP2SMRF_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcaliip2sMrf_read
 ��������  : ID_MSG_FTM_RD_FCALIIP2SMRF_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fcaliip2sMrf_read(VOS_VOID* pParam)
{
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    return ftm_comm_send(ID_MSG_FTM_RD_FCALIIP2SMRF_CNF, (VOS_UINT32)&pstFtmFastCtInfo->stFCaliIp2sMrfRdCnf,
        sizeof(FTM_RD_FCALIIP2SMRF_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcaliip2sMrf_set
 ��������  : ID_MSG_FTM_SET_FCALIIP2SMRF_REQ ������
             ��DSP����OM_PHY_CT_F_CALIIP2_MULTIF_SET_REQԭ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fcaliip2sMrf_set(VOS_VOID* pParam)
{
    VOS_UINT32 i = 0;
    FTM_SET_FCALIIP2SMRF_REQ_STRU* pstFtmReq       = (FTM_SET_FCALIIP2SMRF_REQ_STRU*)pParam;
    OM_PHY_CT_F_CALIIP2_SET_MUTIRF_REQ_STRU stReqToDsp = { 0 };
    

    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if(ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        return at_ftm_fcaliip2sMrf_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    /* ����ԭ�ﵽDSP */
	/*lint -save -e553 */
#if (FEATURE_LPHY_RFIC_HI6362 == FEATURE_ON)
	stReqToDsp.ulMsgId    = OM_PHY_CT_F_CALIIP2_SET_MUTIRF_REQ;
    stReqToDsp.usFreqNum  = pstFtmReq->usChanNum;
    stReqToDsp.usBand     = pstFtmReq->usBand;
    stReqToDsp.usRfid     = pstFtmReq->usRfid;
 	/*lint -restore*/   
    for(i=0; i<stReqToDsp.usFreqNum; i++)
    {
        stReqToDsp.usFreq[i] = at_ftm_get_freq(EN_FCHAN_MODE_FDD_LTE,pstFtmReq->usChan[i]);
    }
#else
    stReqToDsp.ulMsgId    = OM_PHY_CT_F_CALIIP2_SET_MUTIRF_REQ;
    stReqToDsp.usChanNum  = pstFtmReq->usChanNum;
    for(i=0; i<stReqToDsp.usChanNum; i++)
    {
        stReqToDsp.usChan[i] = at_ftm_get_freq(EN_FCHAN_MODE_FDD_LTE,pstFtmReq->usChan[i]);
    }
#endif
    if(ERR_MSP_SUCCESS != ftm_mailbox_ltect_write(&stReqToDsp, sizeof(OM_PHY_CT_F_CALIIP2_SET_MUTIRF_REQ_STRU)))
    {
        return at_ftm_fcaliip2sMrf_setcnf(ERR_MSP_UNKNOWN);
    }

    at_ftm_fcaliip2sMrf_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcaliip2sMrf_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fcaliip2sMrf_timeout(VOS_VOID)
{
    return at_ftm_fcaliip2sMrf_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcaliip2sMrf_dspcnf
 ��������  : DSPԭ��PHY_OM_CT_F_CALIIP2_SET_MUTIRF_CNF������
 �������  : pParam PHY_OM_CT_F_CALIIP2_SET_MUTIRF_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fcaliip2sMrf_dspcnf(VOS_VOID* pParam)
{

    at_ftm_fcaliip2sMrf_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_fcaliip2sMrf_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcaliip2sMrf_dspind
 ��������  : DSPԭ��PHY_OM_CT_F_CALIIP2_MUTIRF_IND������
             ��DSP�����ϱ�����Ϣ����ȫ�ֻ�����
 �������  : pParam PHY_OM_CT_F_CALIIP2_MUTIRF_IND_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fcaliip2sMrf_dspind(VOS_VOID* pParam)
{
    PHY_OM_CT_F_CALIIP2_MUTIRF_IND_STRU* pstCaliIp2Ind = (PHY_OM_CT_F_CALIIP2_MUTIRF_IND_STRU*)pParam;
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    pstFtmFastCtInfo->stFCaliIp2sMrfRdCnf.ulErrCode = ERR_MSP_SUCCESS;
    pstFtmFastCtInfo->stFCaliIp2sMrfRdCnf.usStatus  = FTM_STATUS_EXECUTED;
    pstFtmFastCtInfo->stFCaliIp2sMrfRdCnf.usChanNum = pstCaliIp2Ind->usChanNum;
    (VOS_VOID)MSP_MEMCPY(pstFtmFastCtInfo->stFCaliIp2sMrfRdCnf.astIp2CalRst, pstCaliIp2Ind->astIp2CalRst, sizeof(pstCaliIp2Ind->astIp2CalRst));

    return ERR_MSP_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcalidcocsMrf_store
 ��������  : �������
 �������  : ucStoreType ��������
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_fcalidcocsMrf_store(VOS_UINT8 ucStoreType, FTM_SET_FCALIDCOCSMRF_REQ_STRU* pstReq)
{
    static FTM_SET_FCALIDCOCSMRF_REQ_STRU stReq    = {0};
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_FCALIDCOCSMRF_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else
    {
        (VOS_VOID)MSP_MEMCPY(&pstFtmFastCtInfo->stFCaliDcocsMrfSetReq, &stReq, sizeof(FTM_SET_FCALIDCOCSMRF_REQ_STRU));

        /* ���ò�ѯ��Ϣ  */
        (VOS_VOID)MSP_MEMSET(&pstFtmFastCtInfo->stFCaliDcocsMrfRdCnf, 0, sizeof(pstFtmFastCtInfo->stFCaliDcocsRdCnf));
        pstFtmFastCtInfo->stFCaliDcocsMrfRdCnf.ulErrCode = ERR_MSP_SUCCESS;
        pstFtmFastCtInfo->stFCaliDcocsMrfRdCnf.usStatus  = FTM_STATUS_EXECUTING;
        pstFtmFastCtInfo->stFCaliDcocsMrfRdCnf.usChannel = stReq.usChannel;
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcalidcocsMrf_setcnf
 ��������  : ����ID_MSG_FTM_SET_FCALIDCOCSMRF_CNF
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_fcalidcocsMrf_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_FCALIDCOCSMRF_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_FCALIDCOCSMRF_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_FCALIDCOCSMRF_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcalidcocsMrf_read
 ��������  : ID_MSG_FTM_RD_FCALIDCOCSMRF_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fcalidcocsMrf_read(VOS_VOID* pParam)
{
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    return ftm_comm_send(ID_MSG_FTM_RD_FCALIDCOCSMRF_CNF, (VOS_UINT32)&pstFtmFastCtInfo->stFCaliDcocsMrfRdCnf,
        sizeof(FTM_RD_FCALIDCOCSMRF_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcalidcocsMrf_set
 ��������  : ID_MSG_FTM_SET_FCALIDCOCSMRF_REQ ������
             ��DSP����OM_PHY_CT_F_CALIDCOCS_SET_MUTIRF_REQԭ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fcalidcocsMrf_set(VOS_VOID* pParam)
{
    FTM_SET_FCALIDCOCSMRF_REQ_STRU* pstFtmReq       = (FTM_SET_FCALIDCOCSMRF_REQ_STRU*)pParam;
    OM_PHY_CT_F_CALIDCOCS_SET_MUTIRF_REQ_STRU stReqToDsp= { 0 };

    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if(ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        return at_ftm_fcalidcocsMrf_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId   = OM_PHY_CT_F_CALIDCOCS_SET_MUTIRF_REQ;
	/*lint -save -e553 */	
#if (FEATURE_LPHY_RFIC_HI6362 == FEATURE_ON)
	stReqToDsp.usFreq = at_ftm_get_freq(EN_FCHAN_MODE_FDD_LTE, pstFtmReq->usChannel);
    stReqToDsp.usBand = pstFtmReq->usBand;
    stReqToDsp.usRfid = pstFtmReq->usRfid;
#else
    stReqToDsp.usChannel = at_ftm_get_freq(EN_FCHAN_MODE_FDD_LTE, pstFtmReq->usChannel);
#endif
	/*lint -restore*/
    if(ERR_MSP_SUCCESS != ftm_mailbox_ltect_write(&stReqToDsp, sizeof(OM_PHY_CT_F_CALIDCOCS_SET_MUTIRF_REQ_STRU)))
    {
        return at_ftm_fcalidcocsMrf_setcnf(ERR_MSP_UNKNOWN);
    }

    at_ftm_fcalidcocsMrf_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcalidcocsMrf_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fcalidcocsMrf_timeout(VOS_VOID)
{
    return at_ftm_fcalidcocsMrf_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcalidcocsMrf_dspcnf
 ��������  : DSPԭ��PHY_OM_CT_F_CALIDCOCS_SET_MUTIRF_CNF������
 �������  : pParam PHY_OM_CT_F_CALIDCOCS_SET_MUTIRF_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fcalidcocsMrf_dspcnf(VOS_VOID* pParam)
{

    at_ftm_fcalidcocsMrf_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_fcalidcocsMrf_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcalidcocsMrf_dspind
 ��������  : DSPԭ��PHY_OM_CT_F_CALIDCOCS_MUTIRF_IND������
             ��DSP�����ϱ�����Ϣ����ȫ�ֻ�����
 �������  : pParam PHY_OM_CT_F_CALIDCOCS_MUTIRF_IND_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fcalidcocsMrf_dspind(VOS_VOID* pParam)
{
    PHY_OM_CT_F_CALIDCOCS_MUTIRF_IND_STRU* pstCaliDcocsInd = (PHY_OM_CT_F_CALIDCOCS_MUTIRF_IND_STRU*)pParam;
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo     = ftm_GetFastCTMainInfo();

    pstFtmFastCtInfo->stFCaliDcocsMrfRdCnf.ulErrCode = ERR_MSP_SUCCESS;
    pstFtmFastCtInfo->stFCaliDcocsMrfRdCnf.usStatus  = FTM_STATUS_EXECUTED;
    pstFtmFastCtInfo->stFCaliDcocsMrfRdCnf.usChannel = pstCaliDcocsInd->usChanNum;
    /*lint -save -e419*/
    (VOS_VOID)MSP_MEMCPY(pstFtmFastCtInfo->stFCaliDcocsMrfRdCnf.astDcocCalRst, pstCaliDcocsInd->astDcocCalRst, sizeof(pstCaliDcocsInd->astDcocCalRst));
    /*lint -restore*/
    return ERR_MSP_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fgainstates_store
 ��������  : �������
 �������  : ucStoreType ��������
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_fgainstates_store(VOS_UINT8 ucStoreType, FTM_SET_FGAINSTATES_REQ_STRU* pstReq)
{
    static FTM_SET_FGAINSTATES_REQ_STRU stReq   = {0};
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_FGAINSTATES_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else
    {
        (VOS_VOID)MSP_MEMCPY(&pstFtmFastCtInfo->stFGainStatesSetReq, &stReq, sizeof(FTM_SET_FGAINSTATES_REQ_STRU));
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fgainstates_setcnf
 ��������  : ����ID_MSG_FTM_SET_FGAINSTATES_CNF
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_fgainstates_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_FGAINSTATES_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_FGAINSTATES_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_FGAINSTATES_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fgainstates_read
 ��������  : ID_MSG_FTM_RD_FGAINSTATES_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fgainstates_read(VOS_VOID* pParam)
{
    FTM_RD_FGAINSTATES_CNF_STRU stRdCnf         = { 0 };
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    stRdCnf.ulErrCode      = ERR_MSP_SUCCESS;
    stRdCnf.usGainStateNum = pstFtmFastCtInfo->stFGainStatesSetReq.usGainStateNum;
    (VOS_VOID)MSP_MEMCPY(stRdCnf.usGainState, pstFtmFastCtInfo->stFGainStatesSetReq.usGainState, sizeof(stRdCnf.usGainState));

    return ftm_comm_send(ID_MSG_FTM_RD_FGAINSTATES_CNF, (VOS_UINT32)&stRdCnf, sizeof(FTM_RD_FGAINSTATES_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fgainstates_set
 ��������  : ID_MSG_FTM_SET_FGAINSTATES_REQ ������
             ��DSP����OM_PHY_CT_F_GAINSTATE_SET_REQԭ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fgainstates_set(VOS_VOID* pParam)
{
    FTM_SET_FGAINSTATES_REQ_STRU* pstFtmReq       = (FTM_SET_FGAINSTATES_REQ_STRU*)pParam;
    OM_PHY_CT_F_GAINSTATE_SET_REQ_STRU stReqToDsp = { 0 };
    FCHAN_MODE_ENUM fchanMode = ftm_GetFastCTMainInfo()->enCurMode;
    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if(ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        return at_ftm_fgainstates_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    /* �жϲ����Ƿ���Ч */
	/*lint -save -e553 */
#if (FEATURE_LPHY_RFIC_HI6362 == FEATURE_ON)
	if(pstFtmReq->usGainStateNum > FTM_GAINSTATE_MAX_NUM_HI6362)
    {
         return at_ftm_fgainstates_setcnf(ERR_MSP_INVALID_PARAMETER);
    }
	/*lint -restore*/
    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId        = OM_PHY_CT_F_GAINSTATE_SET_REQ;
    stReqToDsp.usGainStateNum = pstFtmReq->usGainStateNum;
    
    if((pstFtmReq->usGainStateNum >= TX_POW_MAX_NUM) || (pstFtmReq->usGainStateNum >= FTM_GAINSTATE_MAX_NUM_HI6362))
    {
        (VOS_VOID)vos_printf("at_ftm_fgainstates_set failed %d.\n", pstFtmReq->usGainStateNum);
        return ERR_MSP_FAILURE;
    }
    
    MSP_MEMCPY(stReqToDsp.ausGainState, pstFtmReq->usGainState, (pstFtmReq->usGainStateNum * sizeof(VOS_UINT16)));
#else
    if(pstFtmReq->usGainStateNum > FTM_GAINSTATE_MAX_NUM)
    {
         return at_ftm_fgainstates_setcnf(ERR_MSP_INVALID_PARAMETER);
    }

    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId        = OM_PHY_CT_F_GAINSTATE_SET_REQ;
    stReqToDsp.usGainStateNum = pstFtmReq->usGainStateNum;
    (VOS_VOID)MSP_MEMCPY(stReqToDsp.usGainState, pstFtmReq->usGainState, sizeof(stReqToDsp.usGainState));
#endif
    if(ERR_MSP_SUCCESS != ftm_mailbox_ct_write(fchanMode, &stReqToDsp, sizeof(OM_PHY_CT_F_GAINSTATE_SET_REQ_STRU)))
    {
        return at_ftm_fgainstates_setcnf(ERR_MSP_UNKNOWN);
    }
    at_ftm_fgainstates_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fgainstates_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fgainstates_timeout(VOS_VOID)
{
    return at_ftm_fgainstates_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fgainstates_dspcnf
 ��������  : DSPԭ��PHY_OM_CT_F_GAINSTATE_SET_CNF������
 �������  : pParam PHY_OM_CT_F_GAINSTATE_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fgainstates_dspcnf(VOS_VOID* pParam)
{

    at_ftm_fgainstates_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_fgainstates_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fdbbatts_store
 ��������  : �������
 �������  : ucStoreType ��������
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_fdbbatts_store(VOS_UINT8 ucStoreType, FTM_SET_FDBBATTS_REQ_STRU* pstReq)
{
    static FTM_SET_FDBBATTS_REQ_STRU stReq      = { 0 };
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_FDBBATTS_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else
    {
        (VOS_VOID)MSP_MEMCPY(&pstFtmFastCtInfo->stFDbbAttSetReq, &stReq, sizeof(FTM_SET_FDBBATTS_REQ_STRU));
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fdbbatts_setcnf
 ��������  : ����ID_MSG_FTM_SET_FDBBATTS_CNF
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_fdbbatts_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_FDBBATTS_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_FDBBATTS_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_FDBBATTS_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fdbbatts_read
 ��������  : ID_MSG_FTM_RD_FDBBATTS_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fdbbatts_read(VOS_VOID* pParam)
{
    FTM_RD_FDBBATTS_CNF_STRU stRdCnf            = { 0 };
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();
	/*lint -save -e553 */
    stRdCnf.ulErrCode   = ERR_MSP_SUCCESS;
#if (FEATURE_LPHY_RFIC_HI6362 == FEATURE_ON)
	stRdCnf.usDbbAttNum = pstFtmFastCtInfo->stFDbbAttSetReq.usDbbCodeNum;
    MSP_MEMCPY((void *)(intptr_t)(stRdCnf.usDbbAtt), (const void *)(intptr_t)(pstFtmFastCtInfo->stFDbbAttSetReq.usDbbCode), sizeof(stRdCnf.usDbbAtt));
#else
    stRdCnf.usDbbAttNum = pstFtmFastCtInfo->stFDbbAttSetReq.usDbbAttNum;
    (VOS_VOID)MSP_MEMCPY(stRdCnf.usDbbAtt, pstFtmFastCtInfo->stFDbbAttSetReq.usDbbAtt, sizeof(stRdCnf.usDbbAtt));
#endif
	/*lint -restore*/
    return ftm_comm_send(ID_MSG_FTM_RD_FDBBATTS_CNF, (VOS_UINT32)&stRdCnf, sizeof(FTM_RD_FDBBATTS_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fdbbatts_set
 ��������  : ID_MSG_FTM_SET_FDBBATTS_REQ ������
             ��DSP����OM_PHY_CT_F_DBBATT_SET_REQԭ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fdbbatts_set(VOS_VOID* pParam)
{
    FTM_SET_FDBBATTS_REQ_STRU* pstFtmReq         = (FTM_SET_FDBBATTS_REQ_STRU*)pParam;
    OM_PHY_CT_F_DBBATT_SET_REQ_STRU stReqToDsp   = { 0 };
    FCHAN_MODE_ENUM fchanMode = ftm_GetFastCTMainInfo()->enCurMode;
    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if(ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        return at_ftm_fdbbatts_setcnf(ERR_MSP_UE_MODE_ERR);
    }
	/*lint -save -e553 */
    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId     = OM_PHY_CT_F_DBBATT_SET_REQ;
#if (FEATURE_LPHY_RFIC_HI6362 == FEATURE_ON)
	stReqToDsp.usDbbCodeNum = pstFtmReq->usDbbCodeNum;
    MSP_MEMCPY((void *)(intptr_t)(stReqToDsp.usDbbCode), (const void *)(intptr_t)(pstFtmReq->usDbbCode), sizeof(stReqToDsp.usDbbCode));
	/*lint -restore*/
#else
    stReqToDsp.usDbbAttNum = pstFtmReq->usDbbAttNum;
    (VOS_VOID)MSP_MEMCPY(stReqToDsp.usDbbAtt, pstFtmReq->usDbbAtt, sizeof(stReqToDsp.usDbbAtt));
#endif
    if(ERR_MSP_SUCCESS != ftm_mailbox_ct_write(fchanMode, &stReqToDsp, sizeof(OM_PHY_CT_F_DBBATT_SET_REQ_STRU)))
    {
        return at_ftm_fdbbatts_setcnf(ERR_MSP_UNKNOWN);
    }
    at_ftm_fdbbatts_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fdbbatts_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fdbbatts_timeout(VOS_VOID)
{
    return at_ftm_fdbbatts_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fdbbatts_dspcnf
 ��������  : DSPԭ��PHY_OM_CT_F_DBBATT_SET_CNF������
 �������  : pParam PHY_OM_CT_F_DBBATT_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fdbbatts_dspcnf(VOS_VOID* pParam)
{

    at_ftm_fdbbatts_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_fdbbatts_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fbbatts_store
 ��������  : �������
 �������  : ucStoreType ��������
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_fbbatts_store(VOS_UINT8 ucStoreType, FTM_SET_FBBATTS_REQ_STRU* pstReq)
{
    static FTM_SET_FBBATTS_REQ_STRU stReq    = {0};
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_FBBATTS_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else
    {
        (VOS_VOID)MSP_MEMCPY(&pstFtmFastCtInfo->stFBbAttSetReq, &stReq, sizeof(FTM_SET_FBBATTS_REQ_STRU));
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fbbatts_setcnf
 ��������  : ����ID_MSG_FTM_SET_FBBATTS_CNF
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_fbbatts_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_FBBATTS_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_FBBATTS_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_FBBATTS_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fbbatts_read
 ��������  : ID_MSG_FTM_RD_FBBATTS_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fbbatts_read(VOS_VOID* pParam)
{
    FTM_RD_FBBATTS_CNF_STRU stRdCnf             = { 0 };
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    stRdCnf.ulErrCode  = ERR_MSP_SUCCESS;
    stRdCnf.usBbAttNum = pstFtmFastCtInfo->stFBbAttSetReq.usBbAttNum;
    (VOS_VOID)MSP_MEMCPY(stRdCnf.usBbAtt, pstFtmFastCtInfo->stFBbAttSetReq.usBbAtt, sizeof(stRdCnf.usBbAtt));

    return ftm_comm_send(ID_MSG_FTM_RD_FBBATTS_CNF, (VOS_UINT32)&stRdCnf, sizeof(FTM_RD_FBBATTS_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fbbatts_set
 ��������  : ID_MSG_FTM_SET_FBBATTS_REQ ������
             ��DSP����OM_PHY_CT_F_BBATT_SET_REQԭ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fbbatts_set(VOS_VOID* pParam)
{
    FTM_SET_FBBATTS_REQ_STRU* pstFtmReq          = (FTM_SET_FBBATTS_REQ_STRU*)pParam;
    OM_PHY_CT_F_BBATT_SET_REQ_STRU stReqToDsp    = { 0 };
    FCHAN_MODE_ENUM fchanMode = ftm_GetFastCTMainInfo()->enCurMode;
    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if(ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        return at_ftm_fbbatts_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId    = OM_PHY_CT_F_BBATT_SET_REQ;
    stReqToDsp.usBbAttNum = pstFtmReq->usBbAttNum;
    (VOS_VOID)MSP_MEMCPY(stReqToDsp.usBbAtt, pstFtmReq->usBbAtt, sizeof(stReqToDsp.usBbAtt));
    if(ERR_MSP_SUCCESS != ftm_mailbox_ct_write(fchanMode, &stReqToDsp, sizeof(OM_PHY_CT_F_BBATT_SET_REQ_STRU)))
    {
        return at_ftm_fbbatts_setcnf(ERR_MSP_UNKNOWN);
    }
    at_ftm_fbbatts_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fbbatts_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fbbatts_timeout(VOS_VOID)
{
    return at_ftm_fbbatts_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fbbatts_dspcnf
 ��������  : DSPԭ��PHY_OM_CT_F_BBATT_SET_CNF������
 �������  : pParam PHY_OM_CT_F_BBATT_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fbbatts_dspcnf(VOS_VOID* pParam)
{

    at_ftm_fbbatts_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_fbbatts_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcalitxiqs_store
 ��������  : �������
 �������  : ucStoreType ��������
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_fcalitxiqs_store(VOS_UINT8 ucStoreType, FTM_SET_FCALITXIQS_REQ_STRU* pstReq)
{
    static FTM_SET_FCALITXIQS_REQ_STRU stReq    = { 0 };
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_FCALITXIQS_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else
    {
         (VOS_VOID)MSP_MEMCPY(&pstFtmFastCtInfo->stFCaliTxiqSetReq, &stReq, sizeof(FTM_SET_FCALITXIQS_REQ_STRU));

         /* ���ò�ѯ��Ϣ  */
         (VOS_VOID)MSP_MEMSET(&pstFtmFastCtInfo->stFCaliTxiqRdCnf, 0, sizeof(pstFtmFastCtInfo->stFCaliTxiqRdCnf));
         pstFtmFastCtInfo->stFCaliTxiqRdCnf.ulErrCode = ERR_MSP_SUCCESS;
         pstFtmFastCtInfo->stFCaliTxiqRdCnf.usStatus  = FTM_STATUS_EXECUTING;
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcalitxiqs_setcnf
 ��������  : ����ID_MSG_FTM_SET_FCALITXIQS_CNF
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_fcalitxiqs_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_FCALITXIQS_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_FCALITXIQS_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_FCALITXIQS_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcalitxiqs_read
 ��������  : ID_MSG_FTM_RD_FCALITXIQS_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fcalitxiqs_read(VOS_VOID* pParam)
{
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    return ftm_comm_send(ID_MSG_FTM_RD_FCALITXIQS_CNF, (VOS_UINT32)&pstFtmFastCtInfo->stFCaliTxiqRdCnf,
        sizeof(FTM_RD_FCALITXIQS_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcalitxiqs_set
 ��������  : ID_MSG_FTM_SET_FCALITXIQS_REQ ������
             ��DSP����OM_PHY_CT_F_CALITXIQ_SET_REQԭ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fcalitxiqs_set(VOS_VOID* pParam)
{
    FTM_SET_FCALITXIQS_REQ_STRU* pstFtmReq      = (FTM_SET_FCALITXIQS_REQ_STRU*)pParam;
	OM_PHY_CT_F_TXIQ_SET_REQ_STRU stReqToDsp	= { 0 };	
	FCHAN_MODE_ENUM fchanMode = ftm_GetFastCTMainInfo()->enCurMode;

    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if(ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        return at_ftm_fcalitxiqs_setcnf(ERR_MSP_UE_MODE_ERR);
    }
	/*lint -save -e553 */
    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId   = OM_PHY_CT_F_CALITXIQ_SET_REQ;
#if (FEATURE_LPHY_RFIC_HI6362 == FEATURE_ON)
	stReqToDsp.usFreq    = at_ftm_get_freq(fchanMode, pstFtmReq->usChannel);
    stReqToDsp.usBand    = pstFtmReq->usBand;
    stReqToDsp.usRfid    = pstFtmReq->usRfid;
#else
    stReqToDsp.usChannel = at_ftm_get_freq(fchanMode, pstFtmReq->usChannel);
#endif
	/*lint -restore*/
    /*AT^FCALITXIQSֻ���͵�LTE���� */
    if(ERR_MSP_SUCCESS != ftm_mailbox_ltect_write( &stReqToDsp, sizeof(OM_PHY_CT_F_TXIQ_SET_REQ_STRU)))
    {
        return at_ftm_fcalitxiqs_setcnf(ERR_MSP_UNKNOWN);
    }

    at_ftm_fcalitxiqs_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcalitxiqs_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fcalitxiqs_timeout(VOS_VOID)
{
    return at_ftm_fcalitxiqs_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcalitxiqs_dspcnf
 ��������  : DSPԭ��PHY_OM_CT_F_CALITXIQ_SET_CNF������
 �������  : pParam PHY_OM_CT_F_TXIQ_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fcalitxiqs_dspcnf(VOS_VOID* pParam)
{

    at_ftm_fcalitxiqs_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_fcalitxiqs_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcalitxiqs_dspind
 ��������  : DSPԭ��PHY_OM_CT_F_CALITXIQ_IND������
             ��DSP�����ϱ�����Ϣ����ȫ�ֻ�����
 �������  : pParam PHY_OM_CT_F_TXIQ_IND_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fcalitxiqs_dspind(VOS_VOID* pParam)
{
    PHY_OM_CT_F_TXIQ_IND_STRU* pstCaliTxiqInd   = (PHY_OM_CT_F_TXIQ_IND_STRU*)pParam;
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    pstFtmFastCtInfo->stFCaliTxiqRdCnf.ulErrCode   = ERR_MSP_SUCCESS;
    pstFtmFastCtInfo->stFCaliTxiqRdCnf.usStatus    = FTM_STATUS_EXECUTED;
    pstFtmFastCtInfo->stFCaliTxiqRdCnf.usAmplitude = pstCaliTxiqInd->usAmplitude;
    pstFtmFastCtInfo->stFCaliTxiqRdCnf.usPhase     = pstCaliTxiqInd->usPhase;
    pstFtmFastCtInfo->stFCaliTxiqRdCnf.usDCI       = pstCaliTxiqInd->usDCI;
    pstFtmFastCtInfo->stFCaliTxiqRdCnf.usDCQ       = pstCaliTxiqInd->usDCQ;

    return ERR_MSP_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fipstart_store
 ��������  : �������
 �������  : ucStoreType ��������
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static VOID at_ftm_fipstart_store(VOS_UINT8 ucStoreType, FTM_SET_F_FIPSTART_REQ_STRU * pstReq)
{
    static FTM_SET_F_FIPSTART_REQ_STRU stReq    = { 0 };
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_F_FIPSTART_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else
    {
        pstFtmFastCtInfo->ulCurCmdStepsFlag |= CT_F_STEPS_DONE_FIPSTART;
        pstFtmFastCtInfo->ulChannel          = stReq.ulChannel;
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fipstart_setcnf
 ��������  : ����ID_MSG_FTM_F_SET_FIPSTART_CNF
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
static VOS_UINT32 at_ftm_fipstart_setcnf(VOS_UINT32 ulIp2Value1, VOS_UINT32 ulIp2Value2,  VOS_UINT32 ulErrCode)
{
    FTM_SET_F_FIPSTART_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode   = ulErrCode;
    stCnf.ulIp2Value1 = ulIp2Value1;
    stCnf.ulIp2Value2 = ulIp2Value2;

    return ftm_comm_send(ID_MSG_FTM_F_SET_FIPSTART_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_F_FIPSTART_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fipstart_set
 ��������  : ID_MSG_FTM_F_SET_FIPSTART_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fipstart_set(VOS_VOID* pParam)
{
    FTM_SET_F_FIPSTART_REQ_STRU* pstFtmReq      = (FTM_SET_F_FIPSTART_REQ_STRU*)pParam;
    OM_PHY_CT_F_IP2START_REQ_STRU stReqToDsp    = { 0 };

    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if(ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        return at_ftm_fipstart_setcnf(0, 0, ERR_MSP_UE_MODE_ERR);
    }

    /* ����ԭ�ﵽDSP */
	/*lint -save -e734*/
    stReqToDsp.ulMsgId = OM_PHY_CT_F_FIPSTART_SET_REQ;
    stReqToDsp.usBand  = pstFtmReq->ulChannel;
	/*lint -restore*/
    if(ERR_MSP_SUCCESS != ftm_mailbox_ltect_write(&stReqToDsp, sizeof(OM_PHY_CT_F_IP2START_REQ_STRU)))
    {
        return at_ftm_fipstart_setcnf(0, 0, ERR_MSP_UNKNOWN);
    }

    at_ftm_fipstart_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fipstart_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fipstart_timeout(VOS_VOID)
{
    return at_ftm_fipstart_setcnf(0, 0, ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fipstart_dspind
 ��������  : DSPԭ��PHY_OM_CT_F_MEAS_IP2_IND������
 �������  : pParam PHY_OM_CT_F_MEAS_IP2_IND_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fipstart_dspind(VOS_VOID* pParam)
{
    PHY_OM_CT_F_MEAS_IP2_IND_STRU* pDspInd = (PHY_OM_CT_F_MEAS_IP2_IND_STRU*)pParam;

    at_ftm_fipstart_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_fipstart_setcnf(pDspInd->ulIP2Value1 , pDspInd->ulIP2Value1,  ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcalpddcs_setcnf
 ��������  : �������
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
PRIVATE VOS_UINT32 at_ftm_fcalpddcs_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_F_FCALPDDCS_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_F_SET_FCALPDDCS_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_F_FCALPDDCS_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcalpddcs_store
 ��������  : �������
 �������  : ucStoreType ��������
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
PRIVATE VOID at_ftm_fcalpddcs_store(VOS_UINT8 ucStoreType, FTM_SET_F_FCALPDDCS_REQ_STRU* pstReq)
{
    static FTM_SET_F_FCALPDDCS_REQ_STRU stReq     = { 0 };
	FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo  = ftm_GetFastCTMainInfo();

    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_F_FCALPDDCS_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else
    {
        (VOS_VOID)MSP_MEMCPY(&pstFtmFastCtInfo->stFCalPDDCSSetReq, &stReq, sizeof(FTM_SET_F_FCALPDDCS_REQ_STRU));

        /* ���ò�ѯ��Ϣ  */
        (VOS_VOID)MSP_MEMSET(&pstFtmFastCtInfo->stFCalPDDCSRdCnf, 0, sizeof(pstFtmFastCtInfo->stFCalPDDCSRdCnf));
        pstFtmFastCtInfo->stFCalPDDCSRdCnf.ulErrCode = ERR_MSP_SUCCESS;
	    pstFtmFastCtInfo->stFCalPDDCSRdCnf.usStatus  = FTM_CALPDDCS_EXECUTING;///??
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcalpddcs_set
 ��������  : ID_MSG_FTM_F_SET_FCALPDDCS_REQ ������
                          ��DSP����OM_PHY_CT_F_BBATT_SET_REQԭ��
 �������  : pParam FTM_SET_F_FCALPDDCS_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fcalpddcs_set(VOID* pParam)
{
    FTM_SET_F_FCALPDDCS_REQ_STRU* pstFtmReq      = (FTM_SET_F_FCALPDDCS_REQ_STRU*)pParam;
    OM_PHY_CT_F_PD_AUTOCAL_REQ_STRU stReqToDsp    = { 0 };
	FCHAN_MODE_ENUM fchanMode = ftm_GetFastCTMainInfo()->enCurMode;

    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if(ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        return at_ftm_fcalpddcs_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId = OM_PHY_CT_F_PD_AUTO_CAL_REQ;/* ??  ԭ���ȷ��*/
    stReqToDsp.ulPdAutoFlg = pstFtmReq->ulPdAutoFlg;
    if(ERR_MSP_SUCCESS != ftm_mailbox_ct_write(fchanMode, &stReqToDsp, sizeof(OM_PHY_CT_F_PD_AUTOCAL_REQ_STRU)))
    {
        HAL_SDMLOG("[%s]:send data to dsp fail \n", __FUNCTION__);
        return at_ftm_fcalpddcs_setcnf(ERR_MSP_UNKNOWN);
    }

    at_ftm_fcalpddcs_store(FTM_F_CT_STORE_REQ_TEMP, pstFtmReq);
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcalpddcs_dspind
 ��������  : DSPԭ��PHY_OM_CT_F_MEAS_PDDCS_IND������
             ����DSP�����ϱ���PDDC����ֵ:���������������ȫ�ֻ�����
 �������  : pParam PHY_OM_CT_F_MEAS_PDDCS_IND_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fcalpddcs_dspind(VOID* pParam)
{
    PHY_OM_CT_F_PD_AUTO_IND_STRU* pstCalPDDCInd = (PHY_OM_CT_F_PD_AUTO_IND_STRU*)pParam;
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    HAL_SDMLOG("[%s]:msgID =%d \n", __FUNCTION__,pstCalPDDCInd->ulMsgId);
    pstFtmFastCtInfo->stFCalPDDCSRdCnf.ulErrCode = ERR_MSP_SUCCESS;
    pstFtmFastCtInfo->stFCalPDDCSRdCnf.usStatus  = FTM_CALPDDCS_EXECUTED;
    pstFtmFastCtInfo->stFCalPDDCSRdCnf.usDacCfg = pstCalPDDCInd->usDacCfg;
    pstFtmFastCtInfo->stFCalPDDCSRdCnf.usVgaCfg = pstCalPDDCInd->usVgaCfg;
    return ERR_MSP_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcalpddcs_read
 ��������  : ID_MSG_FTM_F_RD_FCALPDDCS_REQ ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fcalpddcs_read(VOS_VOID* pParam)
{
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    return ftm_comm_send(ID_MSG_FTM_F_RD_FCALPDDCS_CNF, (VOS_UINT32)&pstFtmFastCtInfo->stFCalPDDCSRdCnf,
        sizeof(FTM_RD_F_FCALPDDCS_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcalpddcs_dspcnf
 ��������  : DSPԭ��PHY_OM_CT_F_FCALPDDCS_SET_CNF������
 �������  : NULL
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fcalpddcs_dspcnf(VOS_VOID* pParam)
{
    at_ftm_fcalpddcs_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);

    return at_ftm_fcalpddcs_setcnf(ERR_MSP_SUCCESS);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fcalpddcs_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fcalpddcs_timeout(VOS_VOID)
{
    return at_ftm_fcalpddcs_setcnf(ERR_MSP_TIME_OUT);
}


/*****************************************************************************
 �� �� ��  : at_ftm_fpdpows_store
 ��������  : �������
 �������  : ucStoreType ��������
               FTM_F_CT_STORE_REQ_TEMP �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������
               FTM_F_CT_STORE_REQ_GLOBAL �յ�LRTTȷ��ԭ������������װ����ѯ
             pstReq  ����
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
PRIVATE VOID at_ftm_fpdpows_store(VOS_UINT8 ucStoreType, FTM_SET_F_FPDPOWS_REQ_STRU* pstReq)
{
    static FTM_SET_F_FPDPOWS_REQ_STRU stReq    = {0};
    FTM_CT_F_MANAGE_INFO_STRU *pstFCtMainInfo = ftm_GetFastCTMainInfo();

    /* �յ�װ����������ָ�δ�յ�LRTTȷ��ԭ�ֻ�������*/
    if ((FTM_F_CT_STORE_REQ_TEMP==ucStoreType) && (NULL != pstReq))
    {
        (VOS_VOID)MSP_MEMCPY(&stReq, pstReq, sizeof(FTM_SET_F_FPDPOWS_REQ_STRU));
    }
    /* �յ�LRTTȷ��ԭ������������װ����ѯ */
    else
    {
        pstFCtMainInfo->stFpdpowsSetReq  = stReq;
		pstFCtMainInfo->ulCurCmdStepsFlag |= CT_F_STEPS_DONE_FPDPOWS; /*�Ǳ��*/
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fpdpows_setcnf
 ��������  : �������
 �������  : ulErrCode ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
PRIVATE VOS_UINT32 at_ftm_fpdpows_setcnf(VOS_UINT32 ulErrCode)
{
    FTM_SET_F_FPDPOWS_CNF_STRU stCnf = { 0 };

    stCnf.ulErrCode = ulErrCode;

    return ftm_comm_send(ID_MSG_FTM_SET_FPDPOWS_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_F_FPDPOWS_CNF_STRU));
}

/*****************************************************************************
 �� �� ��  : at_ftm_fpdpows_read
 ��������  : ID_MSG_FTM_RD_FPDPOWS_RD ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
#if 0
EXTERN U32_T at_ftm_fpdpows_read()
{
    FTM_RD_F_FPDPOWS_CNF_STRU stRdCnf          = { 0 };
    FTM_CT_F_MANAGE_INFO_STRU *stFCtMainInfo = ftm_GetFastCTMainInfo();

    stRdCnf.ulErrCode = ERR_MSP_SUCCESS;
    stRdCnf.ulSwitch  = stFCtMainInfo->ulFpdpowsSw;

    return ftm_comm_send(ID_MSG_FTM_RD_FPDPOWS_CNF, (U32_T)&stRdCnf, sizeof(FTM_RD_F_FPDPOWS_CNF_STRU));
}
#endif
/*****************************************************************************
 �� �� ��  : at_ftm_fpdpows_set
 ��������  : ID_MSG_FTM_F_SET_FPDPOWS_REQ ������
 �������  : FTM_SET_F_FPDPOWS_REQ_STRUָ�룬���濪��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fpdpows_set(VOID* pParam)
{
    FTM_SET_F_FPDPOWS_REQ_STRU*  stFtmReq        = (FTM_SET_F_FPDPOWS_REQ_STRU*)pParam;
    OM_PHY_CT_F_PD_REQ_STRU stReqToDsp = { 0 };
	FCHAN_MODE_ENUM fchanMode = ftm_GetFastCTMainInfo()->enCurMode;//��Ҫ��LTE

    /* �ж��Ƿ��ڷ�����ģʽ�� */
    if (ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
    {
        return at_ftm_fpdpows_setcnf(ERR_MSP_UE_MODE_ERR);
    }

    /* ����ԭ�ﵽDSP */
    stReqToDsp.ulMsgId    = OM_PHY_CT_F_PD_CAL_REQ;
    stReqToDsp.ulPdEnbFlg = stFtmReq->ulPdEnbFlg;
	stReqToDsp.usDacCfg = stFtmReq->usDacCfg;
	stReqToDsp.usVgaCfg = stFtmReq->usVgaCfg;

	HAL_SDMLOG("[%s]:ready send data to dsp  \n", __FUNCTION__);
	if(ERR_MSP_SUCCESS != ftm_mailbox_ct_write(fchanMode, &stReqToDsp, sizeof(OM_PHY_CT_F_PD_REQ_STRU)))
		{
			HAL_SDMLOG("[%s]:send data to dsp fail \n", __FUNCTION__);
			return at_ftm_fpdpows_setcnf(ERR_MSP_UNKNOWN);
		}

    at_ftm_fpdpows_store(FTM_F_CT_STORE_REQ_TEMP, stFtmReq);
    return ERR_MSP_WAIT_ASYNC;
}

/*****************************************************************************
 �� �� ��  : at_ftm_fpdpows_timeout
 ��������  : ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fpdpows_timeout(VOS_VOID)
{
    HAL_SDMLOG("[%s]: FPDDPOWS set to dsp timeout\n", __FUNCTION__);
    return at_ftm_fpdpows_setcnf(ERR_MSP_TIME_OUT);
}

/*****************************************************************************
 �� �� ��  : at_ftm_fpdpows_dspcnf
 ��������  : DSPԭ��PHY_OM_CT_F_FPDPOWS_CNF������
 �������  : pParam PHY_OM_CT_F_FPDPOWS_SET_CNF_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fpdpows_dspcnf(VOID* pParam)
{

    at_ftm_fpdpows_store(FTM_F_CT_STORE_REQ_GLOBAL, NULL);
    HAL_SDMLOG("[%s]: FPDDPOWS set to dsp CNF\n", __FUNCTION__);
    return at_ftm_fpdpows_setcnf(ERR_MSP_SUCCESS);
}

VOS_UINT32 at_ftm_fpdpows_dspind(VOID* pParam)
{
    PHY_OM_CT_F_PD_IND_STRU* pstfpdpowsInd = (PHY_OM_CT_F_PD_IND_STRU*)pParam;
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();
	VOS_UINT16 usTmpi = 0;
    VOS_UINT16 usTmpj = 0;
    VOS_UINT16 usTmpValue = 0;

    HAL_SDMLOG("ENTER at_ftm_fpdpows_dspind \n");
    (VOS_VOID)vos_printf("xxxxxxxxxxxxxxat_ftm_fpdpows_dspind");

    pstFtmFastCtInfo->ulCurCmdStepsFlag |= CT_F_STEPS_DONE_FPDPOWS;

	for(usTmpi = 0 ; usTmpi < FREQ_MAX_NUM ; usTmpi ++)
    {
        for(usTmpj = 0 ; usTmpj < POW_MAX_NUM ; usTmpj ++)
        {
            usTmpValue = pstfpdpowsInd->ausFreqVota[usTmpi][usTmpj];

            /* ǿ�Ƹ���֮ǰ������ȫ�ֽṹ�е�PDDC����ֵ */
            pstFtmFastCtInfo->stFQPDDCRESRdCnf.ausPDDCValue[usTmpi][usTmpj] = usTmpValue;

            (VOS_VOID)vos_printf("%d ",usTmpValue);
        }

        (VOS_VOID)vos_printf("\n ");
    }

 //   pstFtmFastCtInfo->ulErrCode = ERR_MSP_SUCCESS;
    return ERR_MSP_SUCCESS;
}


/*****************************************************************************
 �� �� ��  : at_ftm_fqpddcres_set
 ��������  : ID_MSG_FTM_F_SET_FQPDDCRES_REQ ������
             ����ȫ�ֻ��沢��������أ��ϱ�������ж��Ƿ�ɹ�����װ���ж�״̬
 �������  : pParam FTM_SET_F_FQPDDCRES_REQ_STRUָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_MSP_SUCCESS, ���򷵻��������
*****************************************************************************/
VOS_UINT32 at_ftm_fqpddcres_set(VOID* pParam)
{
    VOS_BOOL bFreqExist = FALSE;
    VOS_UINT16 usTmp       = 0;

    FTM_SET_FQPDDCRES_CNF_STRU stCnf             = { {0}, };
    FTM_SET_FQPDDCRES_REQ_STRU* pstFtmReq        = (FTM_SET_FQPDDCRES_REQ_STRU*)(pParam);
    FTM_CT_F_MANAGE_INFO_STRU* pstFtmFastCtInfo = ftm_GetFastCTMainInfo();

    /* �ж��Ƿ��ڷ�����ģʽ�� */
    #if 0
    if((ftm_GetNoneSig() != FTM_NONESIG_RTT_OPEN)
		||(!ftm_CheckSynCmdSteps(CT_F_STEPS_DONE_FPDPOWS|CT_F_STEPS_DONE_FSTART)))
    {
        stCnf.ulErrCode = ERR_MSP_UE_MODE_ERR;
        HAL_SDMLOG("%s:NONSIG is not ok OR FPDPOWS and FSTART is not ok\n",__FUNCTION__);
        return ftm_comm_send(ID_MSG_FTM_F_SET_FQPDDCRES_CNF,
            (VOS_UINT32)&stCnf, sizeof(FTM_SET_FQPDDCRES_CNF_STRU));
    }
    #endif

    HAL_SDMLOG("ENTER at_ftm_fqpddcres_set \n");
    /* �ж������е��Ƿ�������û������õ������ŵ������� */
    for(usTmp = 0 ; usTmp < pstFtmFastCtInfo->usCurUlListNum ; usTmp ++)
    {
        if (pstFtmFastCtInfo->ausCurUlFreqInfo[usTmp] == pstFtmReq->ulChannel)
        {
            bFreqExist = TRUE;
            break; /* �ҵ���һ��ƥ��������ŵ��žͷ��� */
        }
    }

    if(bFreqExist == FALSE)
    {
       stCnf.ulErrCode = ERR_MSP_NOT_SET_CHAN;

       return ftm_comm_send(ID_MSG_FTM_F_SET_FQPDDCRES_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_FQPDDCRES_CNF_STRU));
    }

    /* ����ȫ�ֱ����еĽ�������������Ӧ�ṹ�������� */
    stCnf.ulErrCode    = ERR_MSP_SUCCESS;
    (VOS_VOID)MSP_MEMCPY(stCnf.ausPDDCValue, pstFtmFastCtInfo->stFQPDDCRESRdCnf.ausPDDCValue[usTmp], sizeof(stCnf.ausPDDCValue));

    return ftm_comm_send(ID_MSG_FTM_F_SET_FQPDDCRES_CNF,
        (VOS_UINT32)&stCnf, sizeof(FTM_SET_FQPDDCRES_CNF_STRU));
}
/*lint -restore*/






