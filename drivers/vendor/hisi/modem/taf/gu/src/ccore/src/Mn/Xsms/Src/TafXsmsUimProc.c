/******************************************************************************

                  ��Ȩ���� (C), 2001-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXsmsUimProc.c
  �� �� ��   : ����
  ��    ��   : h00300778
  ��������   : 2014��10��31��
  ��������   : 1X SMS(Short Message Service)������USIMM��������Ϣ��������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafXsmsUimProc.h"
#include "TafXsmsCtx.h"
#include "TafXsmsTimer.h"
#include "TafXsmsSndAt.h"
#include "TafXsmsMtFsmMain.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XSMS_UIM_PROC_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
TAF_XSMS_INIT_CTRL_INFO_STRU   g_stTafXsmsInitCtrlInfo;

TAF_XSMS_CTRL_INFO_STRU        g_stTafXsmsReqCtrlInfo;

TAF_XSMS_FILETABLE_STRU         g_stTafXsmsFileTable[] =
{
    {TAF_XSMS_EFSMS_FILEID,     USIMM_CDMA_EFSMS_ID,    USIMM_CSIM_EFSMS_ID},
    {TAF_XSMS_EFSMSS_FILEID,    USIMM_CDMA_EFSMSS_ID,   USIMM_CSIM_EFSMSS_ID},
    {TAF_XSMS_EFIMSIT_FILEID,   USIMM_CDMA_EFIMSIM_ID,  USIMM_CSIM_EFIMSIM_ID}
};

/*****************************************************************************
  3 ��������
*****************************************************************************/


VOS_VOID TAF_XSMS_ChangeFileID(TAF_XSMS_FILEID_ENUM_ENUM_UINT32   enFileID,
                                            USIMM_DEF_FILEID_ENUM_UINT32       *penDefID)
{
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfoAddr;

    pstInitCtrlInfoAddr = TAF_XSMS_GetInitCtrlInfoAddr();

    if (USIMM_CARD_UIM == pstInitCtrlInfoAddr->enCardType)
    {
        *penDefID = g_stTafXsmsFileTable[enFileID].enUIMID;
    }
    else
    {
        *penDefID = g_stTafXsmsFileTable[enFileID].enCSIMID;
    }

    return;
}


VOS_UINT32 TAF_XSMS_GetFileReq(USIMM_DEF_FILEID_ENUM_UINT32   enFileID,
                                        VOS_UINT32                    ulSendPara,
                                        VOS_UINT8                      ucIndex)
{
    USIMM_READFILE_REQ_STRU     *pstMsg;
    VOS_CHAR                    *pcFilePath;

    if (VOS_ERR == USIMM_ChangeDefFileToPath(enFileID, &pcFilePath))
    {
        return VOS_ERR; /*���غ���������Ϣ*/
    }

    pstMsg = (USIMM_READFILE_REQ_STRU *)VOS_AllocMsg(UEPS_PID_XSMS,
                                                sizeof(USIMM_READFILE_REQ_STRU)-VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR == pstMsg)
    {
        return VOS_ERR; /*���غ���������Ϣ*/
    }

    /*�����Ϣ����*/
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulSendPara      = ulSendPara;
    pstMsg->stMsgHeader.enMsgName       = USIMM_READFILE_REQ;
    pstMsg->stMsgHeader.enAppType       = USIMM_CDMA_APP;
    pstMsg->ucRecordNum                 = ucIndex;

    pstMsg->stFilePath.ulPathLen    = VOS_StrLen(pcFilePath);

    PS_MEM_CPY(pstMsg->stFilePath.acPath, pcFilePath, pstMsg->stFilePath.ulPathLen);

    return VOS_SendMsg(UEPS_PID_XSMS, pstMsg);
}
VOS_UINT32 TAF_XSMS_SetFileReq(TAF_XSMS_FILEID_ENUM_ENUM_UINT32 enXSMSID,
                                        VOS_UINT32                      ulSendPara,
                                        TAF_XSMS_SETFILE_INFO_STRU      *pstFileInfo)
{
    USIMM_UPDATEFILE_REQ_STRU       *pstMsg;
    VOS_CHAR                        *pcFilePath;
    USIMM_DEF_FILEID_ENUM_UINT32    enFileID;

    TAF_XSMS_ChangeFileID(enXSMSID, &enFileID);

    if (VOS_ERR == USIMM_ChangeDefFileToPath(enFileID, &pcFilePath))
    {
        return VOS_ERR; /*���غ���������Ϣ*/
    }

    pstMsg = (USIMM_UPDATEFILE_REQ_STRU *)VOS_AllocMsg(UEPS_PID_XSMS,
                                                sizeof(USIMM_UPDATEFILE_REQ_STRU)-VOS_MSG_HEAD_LENGTH+pstFileInfo->usEfLen);

    if(VOS_NULL_PTR == pstMsg)
    {
        return VOS_ERR; /*���غ���������Ϣ*/
    }

    /*�����Ϣ����*/
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulSendPara      = ulSendPara;
    pstMsg->stMsgHeader.enMsgName       = USIMM_UPDATEFILE_REQ;
    pstMsg->stMsgHeader.enAppType       = USIMM_CDMA_APP;
    pstMsg->ucRecordNum                 = pstFileInfo->ucRecordNum;
    pstMsg->usDataLen                   = pstFileInfo->usEfLen;

    PS_MEM_CPY(pstMsg->aucContent, pstFileInfo->pucEfContent, pstFileInfo->usEfLen);

    pstMsg->stFilePath.ulPathLen        = VOS_StrLen(pcFilePath);

    PS_MEM_CPY(pstMsg->stFilePath.acPath, pcFilePath, pstMsg->stFilePath.ulPathLen);

    return VOS_SendMsg(UEPS_PID_XSMS, pstMsg);
}

/*****************************************************************************
 �� �� ��  :SI_PB_QueryFileReq
 ��������  :�ҵ�EFSMS������Ŀ
 �������  :��
 �������  :pucIndex:�ҵ��Ŀ��м�¼
 �� �� ֵ  : VOS_OK:�ҵ����м�¼
             VOS_ERR:δ�ҵ����м�¼
 ���ú���  :��

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/

VOS_UINT32 TAF_XSMS_QueryFileReq(TAF_XSMS_FILEID_ENUM_ENUM_UINT32 enXSMSID)
{
    USIMM_QUERYFILE_REQ_STRU        *pstMsg;
    VOS_CHAR                        *pcFilePath;
    USIMM_DEF_FILEID_ENUM_UINT32    enFileID;

    TAF_XSMS_ChangeFileID(enXSMSID, &enFileID);

    if (VOS_ERR == USIMM_ChangeDefFileToPath(enFileID, &pcFilePath))
    {
        return VOS_ERR; /*���غ���������Ϣ*/
    }

    pstMsg = (USIMM_QUERYFILE_REQ_STRU *)VOS_AllocMsg(UEPS_PID_XSMS,
                                                    sizeof(USIMM_QUERYFILE_REQ_STRU)-VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR == pstMsg)
    {
        return VOS_ERR; /*���غ���������Ϣ*/
    }

    /*�����Ϣ����*/
    pstMsg->stMsgHeader.enAppType       = USIMM_CDMA_APP;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.enMsgName       = USIMM_QUERYFILE_REQ;
    pstMsg->stMsgHeader.ulSendPara      = 0;

    pstMsg->stFilePath.ulPathLen        = VOS_StrLen(pcFilePath);

    PS_MEM_CPY(pstMsg->stFilePath.acPath, pcFilePath, pstMsg->stFilePath.ulPathLen);

    return VOS_SendMsg(MAPS_PB_PID, pstMsg);
}

/*****************************************************************************
 �� �� ��  :TAF_XSMS_FindFreeIndex
 ��������  :�ҵ�EFSMS������Ŀ
 �������  :��
 �������  :pucIndex:�ҵ��Ŀ��м�¼
 �� �� ֵ  : VOS_OK:�ҵ����м�¼
             VOS_ERR:δ�ҵ����м�¼
 ���ú���  :��

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_FindFreeIndex(VOS_UINT8 *pucIndex)
{
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfoAddr;
    VOS_UINT8                           i;

    pstInitCtrlInfoAddr = TAF_XSMS_GetInitCtrlInfoAddr();

    /* ���ݵ�ǰ����������ѯ�ռ�¼ */
    for (i = 1; i <= pstInitCtrlInfoAddr->ucMaxRecord; i++)
    {
        if (TAF_XSMS_EFSMS_STATUS_FREE == TAF_XSMS_GetBitFromBuf(pstInitCtrlInfoAddr->aucFreeIndex, i))
        {
            break;
        }
    }

    /* ����ȫ�� */
    if (i > pstInitCtrlInfoAddr->ucMaxRecord)
    {
        return VOS_ERR;
    }

    *pucIndex = i;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  :TAF_XSMS_GetBitFromBuf
 ��������  :���������趨Bitλ��ֵ
 �������  :ucDataBuf:   ��������
            ulBitNo:     Bit��,��1��ʼ
            ulValue:     ��Ҫ���õ�ֵ,0��1
 �������  :��
 �� �� ֵ  : 1:��Ч��0:��Ч
 ���ú���  :��

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_SetBitToBuf(VOS_UINT8 *pucDataBuf, VOS_UINT32 ulBitNo,VOS_UINT32 ulValue)
{
    VOS_UINT32                          ulOffset;
    VOS_UINT8                           ucBit;

    ulOffset = (ulBitNo - 1)/ 8;

    ucBit    = (VOS_UINT8)((ulBitNo - 1)%8);

    if (VOS_NULL != ulValue)
    {
        /*lint -e701 */
        pucDataBuf[ulOffset] |= (VOS_UINT8)(0x1<<ucBit);
        /*lint +e701 */
    }
    else
    {
        /*lint -e701 */
        pucDataBuf[ulOffset] &= (~(VOS_UINT8)(0x1<<ucBit));
        /*lint +e701 */
    }

    return;
}

/*****************************************************************************
 �� �� ��  :TAF_XSMS_GetBitFromBuf
 ��������  :�������л�ȡָ��Bitλ��ֵ��
 �������  :ucDataBuf:   ��������
           ulBitNo:     Bit�ţ���1��ʼ
 �������  :��
 �� �� ֵ  : 1:��Ч��0:��Ч
 ���ú���  :��

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_GetBitFromBuf(VOS_UINT8 *pucDataBuf, VOS_UINT32 ulBitNo)
{
    VOS_UINT32                          ulOffset;
    VOS_UINT8                           ucBit;

    ulOffset = (ulBitNo - 1)/ 8;

    ucBit    = (VOS_UINT8)((ulBitNo - 1)%8);

    return (pucDataBuf[ulOffset]>>ucBit)&0x1;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_AtSmsDeleteReq
 ��������  : AT�����ɾ������
 �������  : ucLen:��¼����
             ucIndex:��¼��������1��ʼ
 �������  : ��
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_AtSmsDeleteReq(VOS_UINT8 ucIndex)
{
    TAF_XSMS_SETFILE_INFO_STRU          stSetFileReq;
    VOS_UINT8                           aucData[TAF_XSMS_RECORD_LEN_MAX];
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfoAddr;

    pstInitCtrlInfoAddr = TAF_XSMS_GetInitCtrlInfoAddr();

    /* ɾ����������һ���ֽ�ΪFREE״̬���ڶ����ֽڱ�ʾ���ȣ�����ȫΪFF */
    VOS_MemSet(aucData, (VOS_CHAR)0xFF, sizeof(aucData));

    aucData[0] = TAF_XSMS_UIM_MSG_STATUS_FREE;
    aucData[1] = VOS_NULL;

    /* ���д�ļ�����ṹ */
    stSetFileReq.ucRecordNum  = ucIndex;
    stSetFileReq.usEfLen      = pstInitCtrlInfoAddr->ucRecordLen;
    stSetFileReq.pucEfContent = aucData;

    /* ͸������ָʾ�Ǵ�AT�������� */
    return TAF_XSMS_SetFileReq(TAF_XSMS_EFSMS_FILEID, TAF_XSMS_UIM_REQ_TYPE_AT, &stSetFileReq);
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_MsgIdUpdataReq
 ��������  : MO�����и���MESSAGE ID�Ĵ���
 �������  : pucMsgId:Ҫд���MESSAGE ID������
 �������  : ��
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_MsgIdUpdataReq(VOS_UINT8 *pucMsgId)
{
    TAF_XSMS_SETFILE_INFO_STRU          stSetFileReq;

    /* ���д�ļ�����ṹ */
    stSetFileReq.ucRecordNum  = 0;
    stSetFileReq.usEfLen      = 2;
    stSetFileReq.pucEfContent = pucMsgId;

    /* ͸������ָʾ�Ǵ�MO�������� */
    return TAF_XSMS_SetFileReq(TAF_XSMS_EFSMSS_FILEID, TAF_XSMS_UIM_REQ_TYPE_MO, &stSetFileReq);
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_AtSmsWriteReq
 ��������  : AT�����д������
 �������  : ucLen:��¼����
             pucData:Ҫд�������
             ucIndex:��¼��������1��ʼ
 �������  : ��
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_AtSmsWriteReq(VOS_UINT8 ucLen, VOS_UINT8 *pucData, VOS_UINT8 ucIndex)
{
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfoAddr;
    TAF_XSMS_SETFILE_INFO_STRU         stSetFileReq;
    VOS_UINT8                           aucData[TAF_XSMS_RECORD_LEN_MAX];

    pstInitCtrlInfoAddr = TAF_XSMS_GetInitCtrlInfoAddr();

    /* δʹ�õ� */
    VOS_MemSet(aucData, (VOS_CHAR)0xFF, sizeof(aucData));

    PS_MEM_CPY(aucData, pucData, ucLen);

    /* ���д�ļ�����ṹ */
    stSetFileReq.ucRecordNum  = ucIndex;
    stSetFileReq.usEfLen      = pstInitCtrlInfoAddr->ucRecordLen;
    stSetFileReq.pucEfContent = aucData;

    /* ͸������ָʾ�Ǵ�AT�������� */
    return TAF_XSMS_SetFileReq(TAF_XSMS_EFSMS_FILEID, TAF_XSMS_UIM_REQ_TYPE_AT, &stSetFileReq);
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_PrlWriteReq
 ��������  : MT������PRL�ļ���������
 �������  : ucLen:��¼����
             pucPrl:PRL�ļ�����
             ucIndex:��¼��������1��ʼ
 �������  : ��
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_PrlWriteReq(VOS_UINT8 ucLen, VOS_UINT8 *pucPrl, VOS_UINT8 ucIndex)
{
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfoAddr;
    TAF_XSMS_SETFILE_INFO_STRU          stSetFileReq;
    VOS_UINT8                           aucData[TAF_XSMS_RECORD_LEN_MAX];

    pstInitCtrlInfoAddr = TAF_XSMS_GetInitCtrlInfoAddr();

    VOS_MemSet(aucData, (VOS_CHAR)0xFF, sizeof(aucData));

    PS_MEM_CPY(aucData, pucPrl, ucLen);

    /* ���д�ļ�����ṹ */
    stSetFileReq.ucRecordNum  = ucIndex;
    stSetFileReq.usEfLen      = pstInitCtrlInfoAddr->ucRecordLen;
    stSetFileReq.pucEfContent = aucData;

    /* ͸������ָʾ�Ǵ�MT������������ */
    return TAF_XSMS_SetFileReq(TAF_XSMS_EFSMS_FILEID, TAF_XSMS_UIM_REQ_TYPE_MT, &stSetFileReq);
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_CommonFileWriteReq
 ��������  : MT�������ļ���������
 �������  : ucLen:��¼����
             pucData:PRL�ļ�����
             ucIndex:��¼��������1��ʼ
 �������  : ��
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_CommonFileWriteReq(VOS_UINT8 ucLen, VOS_UINT8 *pucData, VOS_UINT8 ucIndex)
{
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfoAddr;
    TAF_XSMS_SETFILE_INFO_STRU          stSetFileReq;
    VOS_UINT8                           aucData[TAF_XSMS_RECORD_LEN_MAX];

    pstInitCtrlInfoAddr = TAF_XSMS_GetInitCtrlInfoAddr();

    VOS_MemSet(aucData, (VOS_CHAR)0xFF, sizeof(aucData));

    aucData[0] = TAF_XSMS_STATUS_REC_UNREAD;
    aucData[1] = ucLen;

    PS_MEM_CPY(aucData + 2, pucData, ucLen);

    /* ���д�ļ�����ṹ */
    stSetFileReq.ucRecordNum  = ucIndex;
    stSetFileReq.usEfLen      = pstInitCtrlInfoAddr->ucRecordLen;
    stSetFileReq.pucEfContent = aucData;

    /* ͸������ָʾ�Ǵ�MT������������ */
    return TAF_XSMS_SetFileReq(TAF_XSMS_EFSMS_FILEID, TAF_XSMS_UIM_REQ_TYPE_MT, &stSetFileReq);
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_PrlReadReq
 ��������  : MT������PRL�ļ���ȡ����
 �������  : ucIndex:��¼��������1��ʼ
 �������  : ��
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_PrlReadReq(VOS_UINT8 ucIndex)
{
    USIMM_DEF_FILEID_ENUM_UINT32    enDefID;

    TAF_XSMS_ChangeFileID(TAF_XSMS_EFSMS_FILEID, &enDefID);

    /* ͸������ָʾ�Ǵ�MT������������ */
    return TAF_XSMS_GetFileReq(enDefID, TAF_XSMS_UIM_REQ_TYPE_MT, ucIndex);
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_InitFileReadReq
 ��������  : ��ʼ���������ļ���ȡ����
 �������  : ucIndex:��¼��������¼�ļ���1��ʼ��͸���ļ���0��ʼ
             usFileId:�ļ�ID
 �������  : ��
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_InitFileReadReq(VOS_UINT8 ucIndex, VOS_UINT32 enFileId)
{
    USIMM_DEF_FILEID_ENUM_UINT32    enDefID;

    TAF_XSMS_ChangeFileID(enFileId, &enDefID);

    /* ͸������ָʾ�Ǵӳ�ʼ�������������� */
    return TAF_XSMS_GetFileReq(enDefID, TAF_XSMS_UIM_REQ_TYPE_INIT, ucIndex);
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_PihStatusIndProc
 ��������  : ��״̬�����Ϣ
 �������  : pstMsg:��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_PihStatusIndProc(USIMM_CARDSTATUS_IND_STRU *pstMsg)
{
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfoAddr;

    pstInitCtrlInfoAddr = TAF_XSMS_GetInitCtrlInfoAddr();

    /* �յ��޿�״̬��ֹͣ��ʼ�� */
    if (USIMM_CARD_SERVIC_ABSENT == pstMsg->stCsimUimInfo.enCardService)
    {
        TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_INIT_PROTECT);
        /*VOS_MemSet(pstInitCtrlInfoAddr, 0, sizeof(TAF_XSMS_INIT_CTRL_INFO_STRU));*/
        TAF_XSMS_MsgInitInd(pstInitCtrlInfoAddr->ucMaxRecord);

        return;
    }

    /* ��ʼ��δ���������յ����������ʱ��ʼ��ʼ��������״̬ʱ��ճ�ʼ��״̬ */
    if (TAF_XSMS_INIT_STATUS_NOT_INIT == pstInitCtrlInfoAddr->enSmsInitState)
    {
        /* ����UIM��Ҳ����CSIM��ʱ����Ҫ��ʼ�� */
        if ((USIMM_CARD_UIM != pstMsg->stCsimUimInfo.enCardType)
            && (USIMM_CARD_CSIM != pstMsg->stCsimUimInfo.enCardType))
        {
            return;
        }

        /* ���濨���� */
        pstInitCtrlInfoAddr->enCardType = pstMsg->stCsimUimInfo.enCardType;

        if (USIMM_CARD_SERVIC_AVAILABLE == pstMsg->stCsimUimInfo.enCardService)
        {
            /* ������ʱ�� */
            TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_INIT_PROTECT, TI_TAF_XSMS_TIMER_USIMM_INIT_LEN);

            pstInitCtrlInfoAddr->stCurrInitFile.usCurrFile  = TAF_XSMS_EFIMSIT_FILEID;

            (VOS_VOID)TAF_XSMS_InitFileReadReq(0, TAF_XSMS_EFIMSIT_FILEID);
        }
        else
        {
            VOS_MemSet(pstInitCtrlInfoAddr, 0, sizeof(TAF_XSMS_INIT_CTRL_INFO_STRU));
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_PihMsgProc
 ��������  : PIH��Ϣ������
 �������  : pstMsg:��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_PihMsgProc(TAF_XSMS_UIM_MSG_STRU *pstMsg)
{
    switch (pstMsg->ulMsgName)
    {
        /* ��״̬�����Ϣ */
        case USIMM_CARDSTATUS_IND:
            TAF_XSMS_PihStatusIndProc((USIMM_CARDSTATUS_IND_STRU *)pstMsg);
            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_InitUsimmMaxRecordRspMsgProc
 ��������  : ��ʼ�����̻�ȡ6F3C�ļ�����¼������ظ��Ĵ�����
 �������  : pstMsg:��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_InitUsimmMaxRecordRspMsgProc(USIMM_QUERYFILE_CNF_STRU *pstMsg)
{
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfoAddr;

    /* ��ȡ�ļ�����¼�������ٳ��� */
    if (VOS_OK != pstMsg->stCmdResult.ulResult)
    {
        TAF_XSMS_WARNING_LOG("TAF_XSMS_InitUsimmMaxRecordRspMsgProc:Get Max Record Err");

        return;
    }

    pstInitCtrlInfoAddr = TAF_XSMS_GetInitCtrlInfoAddr();

    /* ��¼EFSMS�ļ�¼���ͼ�¼���� */
    pstInitCtrlInfoAddr->ucMaxRecord = pstMsg->ucRecordNum;
    pstInitCtrlInfoAddr->ucRecordLen = pstMsg->ucRecordLen;

    /* ��¼��ǰEFSMS��ȡ�ļ�¼�����ļ�ID */
    pstInitCtrlInfoAddr->stCurrInitFile.usCurrFile  = TAF_XSMS_EFSMS_FILEID;
    pstInitCtrlInfoAddr->stCurrInitFile.ucCurrIndex = 1;

    /* ��ȡEFSMS��¼��������ʱ�� */
    TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_INIT_PROTECT, TI_TAF_XSMS_TIMER_USIMM_INIT_LEN);
    (VOS_VOID)TAF_XSMS_InitFileReadReq(pstInitCtrlInfoAddr->stCurrInitFile.ucCurrIndex, TAF_XSMS_EFSMS_FILEID);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_InitEfsmsFileMsgProc
 ��������  : ��ʼ�����̶�ȡ6F3C�ļ�����ظ�������
 �������  : pstMsg:��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_InitEfsmsFileMsgProc(USIMM_READFILE_CNF_STRU *pstMsg)
{
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfoAddr;

    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_INIT_PROTECT);

    pstInitCtrlInfoAddr = TAF_XSMS_GetInitCtrlInfoAddr();

    /* ��ȡ�ɹ�ʱ���ݵ�һ���ֽڵ�״̬�������ֱ�����Ϊ��ʹ�ú�δʹ�� */
    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        if (TAF_XSMS_UIM_MSG_STATUS_FREE == pstMsg->aucEf[0])
        {
            TAF_XSMS_SetBitToBuf(pstInitCtrlInfoAddr->aucFreeIndex,
                                 pstMsg->ucRecordNum,
                                 TAF_XSMS_EFSMS_STATUS_FREE);
        }
        else
        {
            TAF_XSMS_SetBitToBuf(pstInitCtrlInfoAddr->aucFreeIndex,
                                 pstMsg->ucRecordNum,
                                 TAF_XSMS_EFSMS_STATUS_USED);
        }
    }
    /* ��ȡʧ��ʱ����Ϊ��ʹ�ã���¼�Ų���ʹ��USIMM���ص�INDEX��Ҫ��XSMSȫ�ֱ��������INDEX */
    else
    {
        TAF_XSMS_SetBitToBuf(pstInitCtrlInfoAddr->aucFreeIndex,
                             pstInitCtrlInfoAddr->stCurrInitFile.ucCurrIndex,
                             TAF_XSMS_EFSMS_STATUS_USED);
    }

    /* ��¼��ǰEFSMS��ȡ�ļ�¼�����ļ�ID */
    pstInitCtrlInfoAddr->stCurrInitFile.usCurrFile  = TAF_XSMS_EFSMS_FILEID;
    pstInitCtrlInfoAddr->stCurrInitFile.ucCurrIndex++;

    /* �������ֵ��������¼������ʼ������ɣ��ϱ�AT */
    if (pstInitCtrlInfoAddr->stCurrInitFile.ucCurrIndex > pstInitCtrlInfoAddr->ucMaxRecord)
    {
        TAF_XSMS_MsgInitInd(pstInitCtrlInfoAddr->ucMaxRecord);
        pstInitCtrlInfoAddr->enSmsInitState = TAF_XSMS_INIT_STATUS_FINISH;
    }
    else
    {
        /* ��ȡEFSMS��¼��������ʱ�� */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_INIT_PROTECT, TI_TAF_XSMS_TIMER_USIMM_INIT_LEN);
        (VOS_VOID)TAF_XSMS_InitFileReadReq(pstInitCtrlInfoAddr->stCurrInitFile.ucCurrIndex, TAF_XSMS_EFSMS_FILEID);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_InitTimeOutMsgProc
 ��������  : ��ʼ�����̶�ȡ�ļ�����ʱ������
 �������  : pstMsg:��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_InitTimeOutMsgProc(VOS_VOID)
{
    VOS_UINT32                          ulRslt = VOS_ERR;
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfoAddr;

    pstInitCtrlInfoAddr = TAF_XSMS_GetInitCtrlInfoAddr();

    if (TAF_XSMS_EFSMS_FILEID == pstInitCtrlInfoAddr->stCurrInitFile.usCurrFile)
    {
        TAF_XSMS_WARNING_LOG("TAF_XSMS_InitTimeOutMsgProc:Read EFSMS Time Out");

        /* ��ȡ��ʱ���˼�¼����Ϊ��ʹ�� */
        TAF_XSMS_SetBitToBuf(pstInitCtrlInfoAddr->aucFreeIndex,
                             pstInitCtrlInfoAddr->stCurrInitFile.ucCurrIndex,
                             TAF_XSMS_EFSMS_STATUS_USED);

        pstInitCtrlInfoAddr->stCurrInitFile.ucCurrIndex++;

        /* ������ȡ��һ����¼���������ֵ��������¼������ʼ������ɣ��ϱ�AT */
        if (pstInitCtrlInfoAddr->stCurrInitFile.ucCurrIndex > pstInitCtrlInfoAddr->ucMaxRecord)
        {
            TAF_XSMS_MsgInitInd(pstInitCtrlInfoAddr->ucMaxRecord);
            pstInitCtrlInfoAddr->enSmsInitState = TAF_XSMS_INIT_STATUS_FINISH;

            return;
        }
        else
        {
            /* ��ȡEFSMS��¼ */
            ulRslt = TAF_XSMS_InitFileReadReq(pstInitCtrlInfoAddr->stCurrInitFile.ucCurrIndex, TAF_XSMS_EFSMS_FILEID);
        }
    }
    /* ��ȡIMSI��ʱ����ȡ��һ���ļ�EFSMSS */
    else if (TAF_XSMS_EFIMSIT_FILEID == pstInitCtrlInfoAddr->stCurrInitFile.usCurrFile)
    {
        TAF_XSMS_WARNING_LOG("TAF_XSMS_InitTimeOutMsgProc:Read EFIMSI Time Out");

        pstInitCtrlInfoAddr->stCurrInitFile.usCurrFile  = TAF_XSMS_EFSMSS_FILEID;
        pstInitCtrlInfoAddr->stCurrInitFile.ucCurrIndex = VOS_NULL;

        /* ��ȡEFSMSS��¼ */
        ulRslt = TAF_XSMS_InitFileReadReq(pstInitCtrlInfoAddr->stCurrInitFile.ucCurrIndex, TAF_XSMS_EFSMSS_FILEID);
    }
    /* ��ȡEFSMSS��ʱ��MESSAGE ID����Ϊ0����ȡ��һ���ļ�EFSMS */
    else if (TAF_XSMS_EFSMSS_FILEID == pstInitCtrlInfoAddr->stCurrInitFile.usCurrFile)
    {
        TAF_XSMS_WARNING_LOG("TAF_XSMS_InitTimeOutMsgProc:Read EFSMSS Time Out");

        pstInitCtrlInfoAddr->usMessageId                = VOS_NULL;
        pstInitCtrlInfoAddr->stCurrInitFile.usCurrFile  = TAF_XSMS_EFSMS_FILEID;
        pstInitCtrlInfoAddr->stCurrInitFile.ucCurrIndex = VOS_NULL;

        /* ��ȡEFSMS��¼������¼������������ʱ�� */
        TAF_XSMS_QueryFileReq(TAF_XSMS_EFSMS_FILEID);
    }
    else
    {
        /* do nothing make pclint happy */
        return;
    }

    /* ������ʱ�� */
    if (VOS_OK == ulRslt)
    {
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_INIT_PROTECT, TI_TAF_XSMS_TIMER_USIMM_INIT_LEN);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_InitUsimmGetFileRspMsgProc
 ��������  : ��ʼ�����̶�ȡ�ļ�����ظ�������
 �������  : pstMsg:��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_InitUsimmGetFileRspMsgProc(USIMM_READFILE_CNF_STRU *pstMsg)
{
    VOS_UINT32                          ulRslt = VOS_ERR;
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfoAddr;
    VOS_UINT16                          usMessageId;
    VOS_UINT8                          *pucTmp;
    VOS_UINT32                          ulEFID;

    pstInitCtrlInfoAddr = TAF_XSMS_GetInitCtrlInfoAddr();

    USIMM_ChangePathToDefFileID(USIMM_CDMA_APP, pstMsg->stFilePath.ulPathLen, pstMsg->stFilePath.acPath, &ulEFID);

    switch (ulEFID)
    {
        /* ��ȡIMSI�ɹ����ȡEFSMSS�ļ� */
        case USIMM_CDMA_EFIMSIM_ID:
        case USIMM_CSIM_EFIMSIM_ID:
            TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_INIT_PROTECT);

            pucTmp = pstMsg->aucEf;

            if (VOS_OK == pstMsg->stCmdResult.ulResult)
            {
                PS_MEM_CPY(pstInitCtrlInfoAddr->aucImsi, (VOS_UINT8*)(VOS_UINT32)pucTmp, TAF_XSMS_IMSI_LEN_MAX);
            }

            /* ��¼��ǰ��ȡ���ļ�IDΪEFSMSS */
            pstInitCtrlInfoAddr->stCurrInitFile.usCurrFile  = TAF_XSMS_EFSMSS_FILEID;

            ulRslt = TAF_XSMS_InitFileReadReq(0, TAF_XSMS_EFSMSS_FILEID);

            break;

        /* ��ȡSMSS�ɹ����ȡEFSMS�ļ�������¼�� */
        case USIMM_CDMA_EFSMSS_ID:
        case USIMM_CSIM_EFSMSS_ID:
            TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_INIT_PROTECT);

            if (VOS_OK == pstMsg->stCmdResult.ulResult)
            {
                /* �����ֽ��������ֽ���ת�� */
                usMessageId = pstMsg->aucEf[0] << 8;
                usMessageId += pstMsg->aucEf[1];
                pstInitCtrlInfoAddr->usMessageId = usMessageId;

                /* ��¼��ǰ��ȡ���ļ�IDΪEFSMS */
                pstInitCtrlInfoAddr->stCurrInitFile.usCurrFile  = TAF_XSMS_EFSMS_FILEID;
                pstInitCtrlInfoAddr->stCurrInitFile.ucCurrIndex = VOS_NULL;
            }

            /* ��ȡ����¼��������������ʱ�� */
            TAF_XSMS_QueryFileReq(TAF_XSMS_EFSMS_FILEID);

            break;

        case USIMM_CSIM_EFSMS_ID:
        case USIMM_CDMA_EFSMS_ID:
            /* �ں�����������������ʱ�� */
            TAF_XSMS_InitEfsmsFileMsgProc(pstMsg);
            break;

        default:
            break;
    }

    if (VOS_OK == ulRslt)
    {
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_INIT_PROTECT, TI_TAF_XSMS_TIMER_USIMM_INIT_LEN);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_MtGetFileRspMsgProc
 ��������  : MT���̶�ȡ�ļ�����ظ�������
 �������  : pstMsg:��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_MtGetFileRspMsgProc(USIMM_READFILE_CNF_STRU *pstMsg)
{
    VOS_UINT32              ulEFID;

    USIMM_ChangePathToDefFileID(USIMM_CDMA_APP, pstMsg->stFilePath.ulPathLen, pstMsg->stFilePath.acPath, &ulEFID);

    /* MT������ֻ����6F3C */
    if ((USIMM_CDMA_EFSMS_ID == ulEFID)||(USIMM_CSIM_EFSMS_ID == ulEFID))
    {
        TAF_XSMS_MtFsmMainProc((MsgBlock *)pstMsg);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_UsimmGetFileRspMsgProc
 ��������  : XSMSģ���ȡ�ļ�����ظ�������
 �������  : pstMsg:��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_UsimmGetFileRspMsgProc(USIMM_READFILE_CNF_STRU *pstMsg)
{
    /* ֻ���ڳ�ʼ����MT�����в��ж�ȡ�ļ��Ĳ��� */
    switch (pstMsg->stCmdResult.ulSendPara)
    {
        case TAF_XSMS_UIM_REQ_TYPE_INIT:
            TAF_XSMS_InitUsimmGetFileRspMsgProc(pstMsg);
            break;

        case TAF_XSMS_UIM_REQ_TYPE_MT:
            TAF_XSMS_MtGetFileRspMsgProc(pstMsg);
            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_AtSetFileRspMsgProc
 ��������  : AT�����·�д�ļ�����ظ�������
 �������  : pstMsg:��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_AtSetFileRspMsgProc(USIMM_UPDATEFILE_CNF_STRU *pstMsg)
{
    TAF_XSMS_CTRL_INFO_STRU            *pstCtrlInfoAddr;
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfoAddr;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulEFDefID;

    USIMM_ChangePathToDefFileID(USIMM_CDMA_APP, pstMsg->stFilePath.ulPathLen, pstMsg->stFilePath.acPath, &ulEFDefID);

    /* AT�����д�ļ�����ֻ��6F3C */
    if ((USIMM_CDMA_EFSMS_ID != ulEFDefID)&&(USIMM_CSIM_EFSMS_ID != ulEFDefID))
    {
        TAF_XSMS_WARNING_LOG("TAF_XSMS_AtSetFileRspMsgProc:Rcv Msg EF not 6F3C");

        return;
    }

    pstCtrlInfoAddr     = TAF_XSMS_GetReqCtrlInfoAddr();
    pstInitCtrlInfoAddr = TAF_XSMS_GetInitCtrlInfoAddr();

    if (TAF_XSMS_APP_MSG_TYPE_WRITE_REQ == pstCtrlInfoAddr->enAppMsgType)
    {
        /* �ϱ�ATд���¼����������������ж�Ӧ��BIT����Ϊ��ʹ�� */
        if (VOS_OK == pstMsg->stCmdResult.ulResult)
        {
            ucIndex = pstMsg->ucRecordNum;

            TAF_XSMS_SetBitToBuf(pstInitCtrlInfoAddr->aucFreeIndex, ucIndex, TAF_XSMS_EFSMS_STATUS_USED);

            /* AT�ϱ�����ֵ����1��ʼ��AT�Ĵ��������1 */
            TAF_XSMS_MsgWriteCnf(pstCtrlInfoAddr->usClient, pstCtrlInfoAddr->ucOpID, VOS_OK, ucIndex);
        }
        else
        {
            TAF_XSMS_WARNING_LOG("TAF_XSMS_AtSetFileRspMsgProc: Write SMS Fail");

            TAF_XSMS_MsgWriteCnf(pstCtrlInfoAddr->usClient, pstCtrlInfoAddr->ucOpID, VOS_ERR, 0);
        }
    }
    else if (TAF_XSMS_APP_MSG_TYPE_DELETE_REQ == pstCtrlInfoAddr->enAppMsgType)
    {
        /* �ϱ�ATɾ����¼����������������ж�Ӧ��BIT��� */
        if (VOS_OK == pstMsg->stCmdResult.ulResult)
        {
            ucIndex = pstMsg->ucRecordNum;
            TAF_XSMS_SetBitToBuf(pstInitCtrlInfoAddr->aucFreeIndex, ucIndex, TAF_XSMS_EFSMS_STATUS_FREE);
            TAF_XSMS_MsgDeleteCnf(pstCtrlInfoAddr->usClient, pstCtrlInfoAddr->ucOpID, VOS_OK);
        }
        else
        {
            TAF_XSMS_WARNING_LOG("TAF_XSMS_AtSetFileRspMsgProc: Delete SMS Fail");

            TAF_XSMS_MsgDeleteCnf(pstCtrlInfoAddr->usClient, pstCtrlInfoAddr->ucOpID, VOS_ERR);
        }
    }
    else
    {
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_MtSetFileRspMsgProc
 ��������  : MT����д�ļ�����ظ�������
 �������  : pstMsg:��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_MtSetFileRspMsgProc(USIMM_UPDATEFILE_CNF_STRU *pstMsg)
{
    VOS_UINT32                          ulEFDefID;

    USIMM_ChangePathToDefFileID(USIMM_CDMA_APP, pstMsg->stFilePath.ulPathLen, pstMsg->stFilePath.acPath, &ulEFDefID);

    /* MT������ֻ��PRL�ļ����� */
    if ((USIMM_CDMA_EFSMS_ID == ulEFDefID)||(USIMM_CSIM_EFSMS_ID == ulEFDefID))
    {
        TAF_XSMS_MtFsmMainProc((MsgBlock *)pstMsg);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_UsimmSetFileRspMsgProc
 ��������  : USIMMд�ļ�����ظ���Ϣ������
 �������  : pstMsg:��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_UsimmSetFileRspMsgProc(USIMM_UPDATEFILE_CNF_STRU *pstMsg)
{
    /* ֻ��AT�����MO/MT�����в��и����ļ��Ĳ��� */
    switch (pstMsg->stCmdResult.ulSendPara)
    {
        case TAF_XSMS_UIM_REQ_TYPE_AT:
            TAF_XSMS_AtSetFileRspMsgProc(pstMsg);
            break;

        /* MO����ĿǰֻдMessageID�������Ƿ�ɹ������ù� */
        case TAF_XSMS_UIM_REQ_TYPE_MO:
            /* do nothing, make pclint happy */
            break;

        case TAF_XSMS_UIM_REQ_TYPE_MT:
            TAF_XSMS_MtSetFileRspMsgProc(pstMsg);
            break;

        default:

            break;
    }

    return;

}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_UsimmMsgProc
 ��������  : USIMM��Ϣ������
 �������  : pstMsg:��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_UsimmMsgProc(TAF_XSMS_UIM_MSG_STRU *pstMsg)
{
    switch (pstMsg->ulMsgName)
    {
        /* ��ȡ�ļ�����CNF */
        case USIMM_READFILE_CNF:
            TAF_XSMS_UsimmGetFileRspMsgProc((USIMM_READFILE_CNF_STRU *)pstMsg);
            break;
        /* �����ļ�����CNF */
        case USIMM_UPDATEFILE_CNF:
            TAF_XSMS_UsimmSetFileRspMsgProc((USIMM_UPDATEFILE_CNF_STRU *)pstMsg);
            break;
        /* ��ȡ�ļ�����¼������CNF */
        case USIMM_QUERYFILE_CNF:
            TAF_XSMS_InitUsimmMaxRecordRspMsgProc((USIMM_QUERYFILE_CNF_STRU *)pstMsg);
            break;

        default:
            break;
    }

    return;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

