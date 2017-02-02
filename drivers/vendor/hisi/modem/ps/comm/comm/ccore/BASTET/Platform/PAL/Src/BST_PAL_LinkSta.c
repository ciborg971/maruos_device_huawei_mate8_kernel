/******************************************************************************

                  ��Ȩ���� (C), 2014, ��Ϊ�������޹�˾
*******************************************************************************
  �� �� ��   : BST_PAL_LinkSta.c
  �� �� ��   : ����
  ��    ��   : 
  ��������   : 
  ����޸�   :
  ��������   : 
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 
    ��    ��   : 
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_PAL_Net.h"
#include "BST_DRV_LinkSta.h"
#include "BastetRrcInterface.h"
#include "BastetWrrcinterface.h"
#include "BastetTrrcInterface.h"
#include "BastetGasInterface.h"
#include "Nasrrcinterface.h"
#include "TLPsBastetInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_PAL_LINK_STA_C
/*lint +e767*/
/******************************************************************************
   2 �궨��
******************************************************************************/

/******************************************************************************
   3 ˽�ж���
******************************************************************************/

/*****************************************************************************
  4 ��������
*****************************************************************************/
/* ��ͬMODEM����ͬ��ʽ�������ź����� */
extern BST_UINT32          BST_DRV_LsItf_InWriteNetStrength(
    const BST_UINT32        ulModemId,
    const BST_UINT32        ulRatMode,
    const BST_UINT32        ulCellId,
    const BST_INT16         sRscp,
    const BST_INT16         sEcio );

/* ע���ѯ�������Խӿ� */
extern BST_ERR_ENUM_UINT8  BST_DRV_LsItf_InRegInquireFun(
    const BST_UINT32        ulModemId,
    const BST_UINT32        ulRatMode,
    BST_VOID               *pfReadTrsInfo,
    BST_VOID               *pfReadQueInfo );
/******************************************************************************
   5 ȫ�ֱ�������
******************************************************************************/

/******************************************************************************
   6 ����ʵ��
******************************************************************************/

/* ��BST_SYS_MsgProcʹ�� */

BST_VOID BST_PAL_LsItf_ExtRegInquireFunc(
    const BST_UINT32    ulPid, 
    BST_VOID           *pfGetTrsFun,
    BST_VOID           *pfGetQueFun)
{
    BST_UINT32                          ulModemId;
    BST_UINT32                          ulRatMode;

    /* ���ݷ��͵�PID���жϳ�MODEM_ID, �Լ�RAT */
    ulModemId           = BST_MODEM_MAX;
    ulRatMode           = BST_DRV_LS_RAT_INVALID_SN;
    switch( ulPid )
    {
        case PS_PID_RLC_UL:
            ulModemId = BST_MODEM_ID_1;
            ulRatMode = BST_DRV_LS_RAT_LTE_SN;
            break;

        case WUEPS_PID_RLC:
            ulModemId = BST_MODEM_ID_1;
            ulRatMode = BST_DRV_LS_RAT_WCDMA_SN;
            break;

        case TPS_PID_RLC:
            ulModemId = BST_MODEM_ID_1;
            ulRatMode = BST_DRV_LS_RAT_TDSCDMA_SN;
            break;

        case I0_UEPS_PID_SN:
            ulModemId = BST_MODEM_ID_1;
            ulRatMode = BST_DRV_LS_RAT_GSM_SN;
            break;
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
        case I1_UEPS_PID_SN:
            ulModemId = BST_MODEM_ID_2;
            ulRatMode = BST_DRV_LS_RAT_GSM_SN;
            break;
#if ( 3 == MULTI_MODEM_NUMBER )
        case I2_UEPS_PID_SN:
            ulModemId = BST_MODEM_ID_3;
            ulRatMode = BST_DRV_LS_RAT_GSM_SN;
            break;
#endif
#endif
        default:
            break;
    }

    BST_DRV_LsItf_InRegInquireFun(
        ulModemId, ulRatMode, pfGetTrsFun, pfGetQueFun );
}
BST_VOID BST_PAL_LsSendWRrcRegCB( BST_VOID )
{
    BST_WRRC_REG_NET_CB_STRU           *pstSndMsg;
    BST_UINT32                          ulRslt;

    /* �����ڴ�  */
    pstSndMsg = (BST_WRRC_REG_NET_CB_STRU *)PS_ALLOC_MSG(UEPS_PID_BASTET,
                                               sizeof(BST_WRRC_REG_NET_CB_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( BST_NULL_PTR == pstSndMsg )
    {
        /* �ڴ�����ʧ�� */
        BST_DBG_LOG("BST_PAL_LsSendWRrcRegCB:ERROR: Memory Alloc Error for pstMsg");
        return;
    }

    PS_MEM_SET( (VOS_CHAR*)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0x00,
                (sizeof(BST_WRRC_REG_NET_CB_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��ز��� */
    pstSndMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_WRR;
    pstSndMsg->stMsgHeader.ulLength          = sizeof(BST_WRRC_REG_NET_CB_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSndMsg->stMsgHeader.ulMsgName         = ID_WRRC_BASTET_NET_QUAL_CB;

    pstSndMsg->ulModemId      = BST_MODEM_ID_1;
    pstSndMsg->ulRatMode      = BST_AS_RAT_WCDMA;
    pstSndMsg->pfRcvCb        = BST_DRV_LsItf_InWriteNetStrength;

    /* ����VOS����ԭ�� */
    ulRslt = PS_SEND_MSG(UEPS_PID_BASTET, pstSndMsg);
    if ( VOS_OK != ulRslt )
    {
        BST_DBG_LOG("BST_PAL_LsSendWRrcRegCB:ERROR:PS_SEND_MSG ");
        return;
    }
}



BST_VOID BST_PAL_LsSendModemGasRegCB( BST_MODEM_ID_ENUM_UINT32 enModemId )
{
    BST_GAS_REG_NET_CB_STRU           *pstSndMsg;
    BST_UINT32                         ulRslt;
    BST_UINT32                         ulReceiverPid;

    if(BST_MODEM_ID_1 == enModemId)
    {
        ulReceiverPid                  = I0_UEPS_PID_GAS;
    }
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
    else if(BST_MODEM_ID_2 == enModemId)
    {
        ulReceiverPid                  = I1_UEPS_PID_GAS;
    }
#if ( 3 == MULTI_MODEM_NUMBER )
    else if(BST_MODEM_ID_3 == enModemId)
    {
        ulReceiverPid                  = I2_UEPS_PID_GAS;
    }
#endif
#endif
    else
    {
        BST_RLS_LOG1("BST_PAL_LsSendModemGasRegCB:ERROR: invalid modemid:%d",enModemId);
        return;
    }

    /* �����ڴ�  */
    pstSndMsg = (BST_GAS_REG_NET_CB_STRU *)PS_ALLOC_MSG(UEPS_PID_BASTET,
                                               sizeof(BST_GAS_REG_NET_CB_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( BST_NULL_PTR == pstSndMsg )
    {
        /* �ڴ�����ʧ�� */
        BST_DBG_LOG("BST_PAL_LsSendModem0GasRegCB:ERROR: Memory Alloc Error for pstMsg");
        return;
    }

    PS_MEM_SET( (VOS_CHAR*)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0x00,
                (sizeof(BST_GAS_REG_NET_CB_STRU) - VOS_MSG_HEAD_LENGTH));


    /* ��д��ز��� */
    pstSndMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->stMsgHeader.ulReceiverPid     = ulReceiverPid;
    pstSndMsg->stMsgHeader.ulLength          = sizeof(BST_GAS_REG_NET_CB_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSndMsg->stMsgHeader.ulMsgName         = ID_GAS_BASTET_NET_QUAL_CB;

    pstSndMsg->ulModemId      = enModemId;
    pstSndMsg->ulRatMode      = BST_AS_RAT_GPRS;
    pstSndMsg->pfRcvCb        = BST_DRV_LsItf_InWriteNetStrength;

    /* ����VOS����ԭ�� */
    ulRslt = PS_SEND_MSG(UEPS_PID_BASTET, pstSndMsg);
    if ( VOS_OK != ulRslt )
    {
        BST_DBG_LOG("BST_PAL_LsSendModem0GasRegCB:ERROR:PS_SEND_MSG ");
        return;
    }
}


BST_UINT32 BST_PAL_LsGetLRlcBuffSize( BST_UINT32 *pulBufferSize, BST_UINT32 *pulBandWidth )
{
    if( ( BST_NULL_PTR == pulBufferSize ) || ( BST_NULL_PTR == pulBandWidth ) )
    {
        return BST_ERR_INVALID_PTR;
    }

    LRLC_UlGetBufferSize( pulBufferSize );
    *pulBandWidth                       = BST_DRV_INVALID_BAND_WIDTH;

    return BST_TRUE;
}



BST_UINT32 BST_PAL_LsGetTRlcBuffSize( BST_UINT32 *pulBufferSize, BST_UINT32 *pulBandWidth )
{
    if( ( BST_NULL_PTR == pulBufferSize ) || ( BST_NULL_PTR == pulBandWidth ) )
    {
        return BST_ERR_INVALID_PTR;
    }

    TRLC_UlGetBufferSize( pulBufferSize );
    *pulBandWidth                       = BST_DRV_INVALID_BAND_WIDTH;

    return BST_TRUE;
}


BST_VOID BST_PAL_LsInit( BST_VOID )
{
    BST_MODEM_ID_ENUM_UINT32            enModemIndex;

    BST_RLS_LOG("BST_PAL_LsInit");

    /* bastetģ����WCDMA/GSM����㷢���ź�����ע��ص���Ϣ */
    BST_PAL_LsSendWRrcRegCB();
    for( enModemIndex = BST_MODEM_ID_1; enModemIndex < BST_MODEM_MAX; enModemIndex++)
    {
        BST_PAL_LsSendModemGasRegCB( enModemIndex );
    }
    return;
}
BST_VOID BST_PAL_LsRegCb( BST_DRV_LS_INS_STRU *pstLsIns )
{
    BST_ASSERT_NULL( pstLsIns );
    /*��ʼ��ʱ����TDS��LTE�Ľӿں���������Ӧ�ĺ���ָ��*/
    pstLsIns->apfReadQueInfo[BST_MODEM_ID_1][BST_DRV_LS_RAT_LTE_SN]
                                        = BST_PAL_LsGetLRlcBuffSize;
    pstLsIns->apfReadTrsInfo[BST_MODEM_ID_1][BST_DRV_LS_RAT_LTE_SN]
                                        = LRLC_UlGetRetxRatio;

    pstLsIns->apfReadQueInfo[BST_MODEM_ID_1][BST_DRV_LS_RAT_TDSCDMA_SN]
                                        = BST_PAL_LsGetTRlcBuffSize;
    pstLsIns->apfReadTrsInfo[BST_MODEM_ID_1][BST_DRV_LS_RAT_TDSCDMA_SN]
                                        = TRLC_UlGetRetxRatio;
}
