


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasLmmPubMInclude.h"
#include    "NasCommBuffer.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASMMPUBMMSGBUF_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASMMPUBMMSGBUF_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/


/*****************************************************************************
  3 Function
*****************************************************************************/


VOS_UINT32  NAS_LMM_ExistMsgInFsmQue(NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId,
                                 VOS_UINT32                 ulPriLevel)
{
    NAS_LMM_FSM_MSG_BUF_STRU             *pstFsmMsgBuffAddr = NAS_LMM_NULL_PTR;
    VOS_UINT8                           ucMsgCont = NAS_EMM_MSG_BUF_EMPTY;
    VOS_UINT32                          ulRsltExistMsgInQue = NAS_LMM_FAIL;


    /* ��ȡ���� FSM Buffer�ĵ�ַ */
    pstFsmMsgBuffAddr                   = NAS_LMM_GetFsmBufAddr( enParalFsmId );
    if(NAS_LMM_NULL_PTR                  == pstFsmMsgBuffAddr)
    {
        NAS_LMM_PUBM_LOG_WARN(           "NAS_LMM_ExistMsgInFsmQue, Get pstFsmMsgBuffAddr Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_ExistMsgInFsmQue_ENUM
,LNAS_NULL_PTR);
        return  NAS_LMM_FAIL;

    }
    if (NAS_LMM_STORE_HIGH_PRIO_MSG == ulPriLevel)
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_ExistMsgInFsmQue: HIGH PRIO QUE!");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_ExistMsgInFsmQue_ENUM
,LNAS_FUNCTION_LABEL1);
        ucMsgCont                       = pstFsmMsgBuffAddr->ucHighPrioCnt;
    }
    else if (NAS_LMM_STORE_LOW_PRIO_MSG == ulPriLevel)
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_ExistMsgInFsmQue: LOW PRIO QUE!");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_ExistMsgInFsmQue_ENUM
,LNAS_FUNCTION_LABEL2);
        ucMsgCont                       = pstFsmMsgBuffAddr->ucLowPrioCnt;
    }
    else
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_ExistMsgInFsmQue: OTHER PRIO QUE!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_ExistMsgInFsmQue_ENUM
,LNAS_FUNCTION_LABEL3);
    }

    if (NAS_EMM_MSG_BUF_EMPTY != ucMsgCont)
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_ExistMsgInFsmQue: EXIST MSG IN QUE!");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_ExistMsgInFsmQue_ENUM
,LNAS_FUNCTION_LABEL4);
        ulRsltExistMsgInQue = NAS_LMM_SUCC;
    }

    return ulRsltExistMsgInQue;
}
/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_LMM_RemoveMsgFromFsmQue(
    NAS_LMM_FSM_MSG_BUF_STRU*            pstFsmMsgBuffAddr,
    VOS_UINT32                          ulMsgType,
    VOS_UINT32                          ulPriLevel)

{
    VOS_UINT8                           ucCnt;
    NAS_LMM_BUFF_MSG_STRU*              pstMsgQue         = NAS_LMM_NULL_PTR;
    VOS_BOOL                            bRsltRemoveMsgFromQue = VOS_FALSE;


    /* �������  */

    if(NAS_LMM_NULL_PTR                  == pstFsmMsgBuffAddr)
    {
        NAS_LMM_PUBM_LOG_WARN(           "NAS_LMM_RemoveMsgFromFsmQue, Get pstFsmMsgBuffAddr Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_RemoveMsgFromFsmQue_ENUM
,LNAS_NULL_PTR);
        return;

    }
    if( (NAS_LMM_STORE_HIGH_PRIO_MSG != ulPriLevel) &&
        (NAS_LMM_STORE_LOW_PRIO_MSG  != ulPriLevel))
    {
        NAS_LMM_PUBM_LOG1_WARN(           "NAS_LMM_RemoveMsgFromFsmQue, PRIO Fail!",ulPriLevel);
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_RemoveMsgFromFsmQue_ENUM
,LNAS_FAIL);
        return;

    }
    /* �ڸ����ȼ��͵����ȼ��в���ulMsgType��������У���Ҫ�ͷ�  */

    pstMsgQue                           = pstFsmMsgBuffAddr->astHighPrioBufQue;
    ucCnt                               = pstFsmMsgBuffAddr->ucHighPrioCnt;
    bRsltRemoveMsgFromQue               = NAS_LMM_RemoveMsgFromQue( pstMsgQue,
                                                                ucCnt,
                                                                ulMsgType);
    /*��Ϣ�ɹ��ͷţ�����MSG COUNT */
    if( bRsltRemoveMsgFromQue )
    {
        pstFsmMsgBuffAddr->ucHighPrioCnt-=1;
    }

    /*�����ȼ� */
    pstMsgQue                           = pstFsmMsgBuffAddr->astLowPrioBufQue;
    ucCnt                               = pstFsmMsgBuffAddr->ucLowPrioCnt;

    bRsltRemoveMsgFromQue               = NAS_LMM_RemoveMsgFromQue( pstMsgQue,
                                                                ucCnt,
                                                                ulMsgType);

    /*��Ϣ�ɹ��ͷţ�����MSG COUNT */
    if( bRsltRemoveMsgFromQue )
    {
        pstFsmMsgBuffAddr->ucLowPrioCnt-=1;
    }

    return;
}
VOS_BOOL  NAS_LMM_RemoveMsgFromQue(
    NAS_LMM_BUFF_MSG_STRU*              pstMsgQue ,
    VOS_UINT8                           ucCnt,
    VOS_UINT32                          ulMsgType
                                           )
{
    VOS_UINT8                           ucMoveCnt;
    VOS_UINT32                          ulBufMsgType;
    VOS_UINT8                           ucSearchCnt = 0;
    VOS_BOOL                            bFlag = VOS_FALSE;
    NAS_LMM_BUFF_MSG_STRU*              pstBufMsg =  NAS_LMM_NULL_PTR;
    VOS_UINT32                          ulRslt;

    /*�������  */

    if(NAS_LMM_NULL_PTR                  == pstMsgQue)
    {
        NAS_LMM_PUBM_LOG_WARN(           "NAS_LMM_RemoveMsgFromQue, pstMsgQue == NAS_LMM_NULL_PTR");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_RemoveMsgFromQue_ENUM
,LNAS_NULL_PTR);
        return(VOS_FALSE);

    }
    /*��Queue�в���ulMsgType  */
    for(ucSearchCnt = 0 ; (ucSearchCnt < ucCnt) && (ucSearchCnt < NAS_EMM_BUF_MSG_MAX_NUM);
        ucSearchCnt++ )
    {
        pstBufMsg    = (pstMsgQue+ucSearchCnt);
        ulBufMsgType = pstBufMsg->ulEvtType;

        /* �ж���Ϣ�Ƿ��Ѵ��� */
        if( ulBufMsgType                == ulMsgType )
        {
            bFlag = VOS_TRUE;
            break;
        }
    }

    /* �����Ϣ����*/
    if(bFlag)
    {
        /*�ͷ��Ѵ��ڵ���Ϣ */
        if((pstBufMsg != NAS_LMM_NULL_PTR) &&
           (pstBufMsg->pBuffMsg != NAS_LMM_NULL_PTR) )
        {
            ulRslt = NAS_COMM_FreeBuffItem( NAS_COMM_BUFF_TYPE_EMM, pstBufMsg->pBuffMsg );

            if (NAS_COMM_BUFF_SUCCESS != ulRslt)
            {
                NAS_LMM_PUBM_LOG_WARN("NAS_LMM_RemoveMsgFromQue, Memory Free is not succ");
                TLPS_PRINT2LAYER_WARNING(NAS_LMM_RemoveMsgFromQue_ENUM
,LNAS_FAIL);

            }
        }

        /*�Ѻ������Ϣǰ��  */

        /* �����Ϣ������� */

        if(ucSearchCnt < (ucCnt-1) )
        {
            for(ucMoveCnt = ucSearchCnt; (ucMoveCnt < (ucCnt-1)) && (ucMoveCnt < (NAS_EMM_BUF_MSG_MAX_NUM-1));
                ucMoveCnt++ )
            {
                pstMsgQue[ucMoveCnt].pBuffMsg
                                            = pstMsgQue[ucMoveCnt+1].pBuffMsg;
                pstMsgQue[ucMoveCnt].ulEvtType
                                            = pstMsgQue[ucMoveCnt+1].ulEvtType;
            }
        }

        pstMsgQue[ucCnt-1].pBuffMsg = NAS_LMM_NULL_PTR;
        pstMsgQue[ucCnt-1].ulEvtType= 0;

        return(VOS_TRUE);
    }

    return(VOS_FALSE);
}
VOS_VOID  NAS_LMM_BufMsgQueFree( VOS_VOID )
{
    /* ��ǰֻ�����ͷ�EMM��MMC�ĸߵ����ȼ�������Ժ��õ�������Que�������ȼ���
    ** ��Ҫ��Ӷ�Ӧ����Դ�Ĵ��� */

    NAS_LMM_PUBM_LOG_NORM( "NAS_LMM_BufMsgQueFree" );
    TLPS_PRINT2LAYER_WARNING(NAS_LMM_BufMsgQueFree_ENUM
,LNAS_ENTRY);

    NAS_LMM_ClearBufMsgQue( NAS_LMM_PARALLEL_FSM_EMM , NAS_LMM_STORE_HIGH_PRIO_MSG );
    NAS_LMM_ClearBufMsgQue( NAS_LMM_PARALLEL_FSM_EMM , NAS_LMM_STORE_LOW_PRIO_MSG );
    /*NAS_LMM_ClearBufMsgQue( NAS_LMM_PARALLEL_FSM_MMC , NAS_LMM_STORE_HIGH_PRIO_MSG );
    NAS_LMM_ClearBufMsgQue( NAS_LMM_PARALLEL_FSM_MMC , NAS_LMM_STORE_LOW_PRIO_MSG );*/
    NAS_LMM_ClearBufMsgQue( NAS_LMM_PARALLEL_FSM_SECU , NAS_LMM_STORE_HIGH_PRIO_MSG );
    NAS_LMM_ClearBufMsgQue( NAS_LMM_PARALLEL_FSM_SECU , NAS_LMM_STORE_LOW_PRIO_MSG );
}



VOS_UINT32  NAS_LMM_BufMsgInQue(
    NAS_LMM_FSM_MSG_BUF_STRU*            pstFsmAddr,
    VOS_UINT32                          ulPriLevel)

{
    VOS_UINT32                          ulRslt = NAS_LMM_FAIL;
    VOS_UINT8                           *pucCnt = NAS_LMM_NULL_PTR;

    /* ��μ����� */
    /* ��ӡ������Ϣ */

    if ( (ulPriLevel < NAS_LMM_STORE_HIGH_PRIO_MSG ) ||
         (ulPriLevel > NAS_LMM_STORE_LOW_PRIO_MSG ))
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_BufMsgInQue, error: ... ",ulPriLevel);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_BufMsgInQue_ENUM
,LNAS_FUNCTION_LABEL1,ulPriLevel);
        return NAS_LMM_FAIL;
    }

    if(NAS_LMM_NULL_PTR == pstFsmAddr)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_BufMsgInQue, error: NAS_LMM_NULL_PTR == pstFsmAddr ");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_BufMsgInQue_ENUM
,LNAS_FUNCTION_LABEL2);
        return NAS_LMM_FAIL;
    }

    /* �������ȼ�����Queue����Ϣ */
    if( NAS_LMM_STORE_HIGH_PRIO_MSG      == ulPriLevel )
    {
        pucCnt                           = &(pstFsmAddr->ucHighPrioCnt);
    }
    else if( NAS_LMM_STORE_LOW_PRIO_MSG  == ulPriLevel )
    {
        pucCnt                           = &(pstFsmAddr->ucLowPrioCnt);
    }
    else
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_BufMsgInQue: OTHER PRIO QUE ");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_BufMsgInQue_ENUM
,LNAS_FUNCTION_LABEL3);
    }

    /* ����Count��ֵ */
    if( NAS_LMM_NULL_PTR                 != pucCnt )
    {
        *pucCnt                          += 1;
        if( *pucCnt                      <= NAS_EMM_BUF_MSG_MAX_NUM )
        {
            ulRslt                      = NAS_LMM_SUCC;
        }
        else
        {
            NAS_LMM_PUBM_LOG_NORM("NAS_LMM_BufMsgInQue: QUE is overflow ");
            TLPS_PRINT2LAYER_INFO(NAS_LMM_BufMsgInQue_ENUM
,LNAS_FUNCTION_LABEL4);
        }

    }

    return( ulRslt );
}



NAS_LMM_BUFF_MSG_STRU * NAS_LMM_GetStoreBufMsgAddr(
                NAS_LMM_FSM_MSG_BUF_STRU*        pstFsmAddr,
                VOS_UINT32                      ulPriLevel)
{
    NAS_LMM_BUFF_MSG_STRU               *pstMsgBuffAddr = NAS_LMM_NULL_PTR;
    VOS_UINT8                           ucCnt;

    /* ��μ����� */
    /* ��ӡ������Ϣ */
    if ( (ulPriLevel < NAS_LMM_STORE_HIGH_PRIO_MSG ) ||
         (ulPriLevel > NAS_LMM_STORE_LOW_PRIO_MSG ))
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_GetStoreBufMsgAddr, error: ... ",ulPriLevel);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_GetStoreBufMsgAddr_ENUM
,LNAS_FUNCTION_LABEL1,ulPriLevel);
        return NAS_LMM_NULL_PTR;
    }

    if(NAS_LMM_NULL_PTR == pstFsmAddr)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_GetStoreBufMsgAddr, error: NAS_LMM_NULL_PTR == pstFsmAddr ");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_GetStoreBufMsgAddr_ENUM
,LNAS_FUNCTION_LABEL2);
        return NAS_LMM_NULL_PTR;
    }

    /* �������ȼ���û���Buffer�ĵ�ַ*/

    if( NAS_LMM_STORE_HIGH_PRIO_MSG == ulPriLevel )
    {
        ucCnt = pstFsmAddr->ucHighPrioCnt;
        if(ucCnt < NAS_EMM_BUF_MSG_MAX_NUM)
        {
            pstMsgBuffAddr = (pstFsmAddr->astHighPrioBufQue+ucCnt);
        }
    }
    else if( NAS_LMM_STORE_LOW_PRIO_MSG == ulPriLevel )
    {
        ucCnt = pstFsmAddr->ucLowPrioCnt;
        if(ucCnt < NAS_EMM_BUF_MSG_MAX_NUM)
        {
            pstMsgBuffAddr = (pstFsmAddr->astLowPrioBufQue+ucCnt);
        }
    }
    else
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_GetStoreBufMsgAddr: OTHER QUE ADDR");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_GetStoreBufMsgAddr_ENUM
,LNAS_FUNCTION_LABEL3);
    }
    return( pstMsgBuffAddr );
}
NAS_LMM_FSM_MSG_BUF_STRU* NAS_LMM_GetFsmBufAddr( NAS_LMM_PARALLEL_FSM_ENUM_UINT16
                                                          enParalFsmId )
{
    if(enParalFsmId >= NAS_LMM_PARALLEL_FSM_BUTT)
    {
        NAS_LMM_PUBM_LOG1_ERR( "NAS_LMM_GetFsmBufAddr: Error enParalFsmId:",enParalFsmId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_GetFsmBufAddr_ENUM
                            ,LNAS_FUNCTION_LABEL1,enParalFsmId);
        return(NAS_LMM_NULL_PTR);
    }
    else
    {
        return(NAS_LMM_GetFsmBufQueueAddr(enParalFsmId));
    }
}



VOS_UINT32  NAS_LMM_StoreMsgToQue(
                NAS_LMM_PARALLEL_FSM_ENUM_UINT16   enParalFsmId,
                VOS_UINT32                        ulBufPriLevel,
                VOS_UINT32                        ulMsgType,
                const VOS_VOID                    *pMsg )
{
    VOS_UINT32                          ulLength;
    VOS_UINT8                          *pucMsgBuff          = NAS_LMM_NULL_PTR;
    NAS_LMM_BUFF_MSG_STRU              *pstBuffer           = NAS_LMM_NULL_PTR;
    NAS_LMM_FSM_MSG_BUF_STRU            *pstFsmMsgBuffAddr   = NAS_LMM_NULL_PTR;
    VOS_UINT32                          ulRslt;

    /* ��ڼ�� ��Ϊ�˱����ڴ�й©����ǰֻ֧��EMM,�����Ҫ֧��MMC�������޸�������������,
    ** �����ڶ�Ӧ��ģ����Ҫ�����Ӧ�Ĵ���;������������ȼ��Ļ��棬Ҳ��֧��;*/
    if ( enParalFsmId != NAS_LMM_PARALLEL_FSM_EMM )
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_StoreMsgToQue, FsmId error, FsmId:", enParalFsmId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_StoreMsgToQue_ENUM
,LNAS_FUNCTION_LABEL1,enParalFsmId);
        return  NAS_LMM_ERR_CODE_ARRAY_OVERFLOW;
    }

    if ( NAS_LMM_NULL_PTR == pMsg )
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_StoreMsgToQue, Msg is NULL!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_StoreMsgToQue_ENUM
,LNAS_FUNCTION_LABEL2);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }
    if( (NAS_LMM_STORE_HIGH_PRIO_MSG != ulBufPriLevel) &&
        (NAS_LMM_STORE_LOW_PRIO_MSG  != ulBufPriLevel))
    {
        NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_StoreMsgToQue, Prio err!",ulBufPriLevel);
        TLPS_PRINT2LAYER_WARNING1(NAS_LMM_StoreMsgToQue_ENUM
,LNAS_FUNCTION_LABEL3,ulBufPriLevel);
        return  NAS_LMM_ERR_CODE_PARA_INVALID;
    }

    /* ��ȡ����Buffer�ĵ�ַ */
    pstFsmMsgBuffAddr                   = NAS_LMM_GetFsmBufAddr( enParalFsmId );
    if(NAS_LMM_NULL_PTR                  == pstFsmMsgBuffAddr)
    {
        NAS_LMM_PUBM_LOG_WARN(           "NAS_LMM_StoreMsgToQue, Get pstFsmMsgBuffAddr Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_StoreMsgToQue_ENUM
,LNAS_FUNCTION_LABEL4);
        return  NAS_LMM_ERR_CODE_PTR_NULL;

    }

    /*�����Ϣ���ڣ���ȥ����Ϣ */
    NAS_LMM_RemoveMsgFromFsmQue( pstFsmMsgBuffAddr, ulMsgType, ulBufPriLevel );


    pstBuffer = NAS_LMM_GetStoreBufMsgAddr( pstFsmMsgBuffAddr, ulBufPriLevel );
    if(NAS_LMM_NULL_PTR                  == pstBuffer)
    {
        NAS_LMM_PUBM_LOG_WARN(           "NAS_LMM_StoreMsgToQue, GetStoreBufMsgAddr Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_StoreMsgToQue_ENUM
,LNAS_FUNCTION_LABEL5);
        return  NAS_LMM_ERR_CODE_PTR_NULL;

    }

    /* ��ȡ��Ϣ����  */
    ulLength  = ((NAS_LMM_MSG_HEADER_STRU *)pMsg)->ulLength
                            + NAS_EMM_PUB_VOS_MSG_HEADER_LEN;

    /* ��̬���仺��ռ� */
    pucMsgBuff                          = NAS_COMM_AllocBuffItem(NAS_COMM_BUFF_TYPE_EMM, ulLength);
    if(NAS_LMM_NULL_PTR                  == pucMsgBuff )
    {
        NAS_LMM_PUBM_LOG_WARN(           "NAS_LMM_StoreMsgToQue, Msg Allocate Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_StoreMsgToQue_ENUM
,LNAS_FUNCTION_LABEL6);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /* ����Ҫ�������Ϣ���������뵽�ĵ�ַ�� */
    NAS_LMM_MEM_CPY( pucMsgBuff, pMsg, ulLength );

    /* ��Ϣ��� */
    pstBuffer->pBuffMsg                 = (VOS_VOID*)(pucMsgBuff);
    pstBuffer->ulEvtType                = ulMsgType;
    ulRslt                              = NAS_LMM_BufMsgInQue( pstFsmMsgBuffAddr,ulBufPriLevel );

    if( NAS_LMM_FAIL                     == ulRslt)
    {
        NAS_LMM_PUBM_LOG_WARN(           "NAS_LMM_StoreMsgToQue, In Queue Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_StoreMsgToQue_ENUM
,LNAS_FUNCTION_LABEL7);
        ulRslt = NAS_COMM_FreeBuffItem(NAS_COMM_BUFF_TYPE_EMM, pucMsgBuff);

        if (NAS_COMM_BUFF_SUCCESS != ulRslt)
        {
            NAS_LMM_PUBM_LOG_WARN("NAS_LMM_StoreMsgToQue, Memory Free is not succ");
            TLPS_PRINT2LAYER_WARNING(NAS_LMM_StoreMsgToQue_ENUM
,LNAS_FUNCTION_LABEL8);
        }

        pstBuffer->pBuffMsg             = NAS_LMM_NULL_PTR;
        pstBuffer->ulEvtType            = 0;
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    return  NAS_LMM_SUCC;
}



VOS_UINT32 NAS_LMM_OutMsgFromQue( NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId,
                                        VOS_UINT32         ulBufPriLevel,
                                        NAS_LMM_BUFF_MSG_STRU   *pstGetMsg)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           *pucMsgCnt          = NAS_LMM_NULL_PTR;
    NAS_LMM_BUFF_MSG_STRU               *pstBuffer          = NAS_LMM_NULL_PTR;
    NAS_LMM_FSM_MSG_BUF_STRU             *pstFsmMsgBuffAddr  = NAS_LMM_NULL_PTR;
    VOS_UINT32                          ulRslt              = NAS_LMM_NOT_TRAVEL_BUFFER_MSG;


    /* �������*/
    if (enParalFsmId != NAS_LMM_PARALLEL_FSM_EMM )
    {
        NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_OutMsgFromQue: FsmId error, FsmId:", enParalFsmId);
        TLPS_PRINT2LAYER_WARNING1(NAS_LMM_OutMsgFromQue_ENUM
,LNAS_FUNCTION_LABEL1,enParalFsmId);
        return ulRslt;
    }

    if (NAS_LMM_NULL_PTR == pstGetMsg)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_OutMsgFromQue: pstGetMsg is null");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_OutMsgFromQue_ENUM
,LNAS_FUNCTION_LABEL2);
        return ulRslt;
    }

    /* ��ȡ����FSM Buffer�ĵ�ַ */

    pstFsmMsgBuffAddr                   = NAS_LMM_GetFsmBufAddr( enParalFsmId );
    if(NAS_LMM_NULL_PTR                  == pstFsmMsgBuffAddr)
    {
        NAS_LMM_PUBM_LOG_WARN(           "NAS_LMM_OutMsgFromQue, Get pstFsmMsgBuffAddr Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_OutMsgFromQue_ENUM
,LNAS_FUNCTION_LABEL3);
        return  ulRslt;

    }

    /* �������ȼ�ȡ��ز���*/

    if (NAS_LMM_STORE_HIGH_PRIO_MSG == ulBufPriLevel)
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_OutMsgFromQue: high prio buff");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_OutMsgFromQue_ENUM
,LNAS_FUNCTION_LABEL4);
        pstBuffer = pstFsmMsgBuffAddr->astHighPrioBufQue;
        pucMsgCnt = &(pstFsmMsgBuffAddr->ucHighPrioCnt);

    }
    else if (NAS_LMM_STORE_LOW_PRIO_MSG == ulBufPriLevel)
    {

        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_OutMsgFromQue: low prio buff");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_OutMsgFromQue_ENUM
,LNAS_FUNCTION_LABEL5);
        pstBuffer = pstFsmMsgBuffAddr->astLowPrioBufQue;
        pucMsgCnt = &(pstFsmMsgBuffAddr->ucLowPrioCnt);
    }
    else
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_OutMsgFromQue is entered");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_OutMsgFromQue_ENUM
,LNAS_FUNCTION_LABEL6);
        return ulRslt;
    }


    /* ����������Ϣ���� */

    if ((*pucMsgCnt > 0) && (*pucMsgCnt <= NAS_EMM_BUF_MSG_MAX_NUM))
    {
        NAS_LMM_PUBM_LOG1_NORM("NAS_LMM_OutMsgFromQue: ucMsgCnt valid, *pucMsgCnt = ",*pucMsgCnt);
        TLPS_PRINT2LAYER_INFO1(NAS_LMM_OutMsgFromQue_ENUM
,LNAS_FUNCTION_LABEL7,*pucMsgCnt);

        /* ����һ�����ͳ��� */
        pstGetMsg->ulEvtType = pstBuffer[0].ulEvtType;
        pstGetMsg->pBuffMsg = pstBuffer[0].pBuffMsg;

        /* ���������ǰ�� */
        for (ulLoop = 1; ulLoop < *pucMsgCnt; ulLoop++)
        {
            pstBuffer[ulLoop - 1].pBuffMsg  = pstBuffer[ulLoop].pBuffMsg;
            pstBuffer[ulLoop - 1].ulEvtType = pstBuffer[ulLoop].ulEvtType;
        }

        /* ����Ϣ����ָ���ÿ� */
        pstBuffer[*pucMsgCnt - 1].pBuffMsg = VOS_NULL_PTR;
        pstBuffer[*pucMsgCnt - 1].ulEvtType = 0;

        /* ��Ŀ-1 */
        (*pucMsgCnt) --;

        ulRslt = NAS_LMM_TRAVEL_BUFFER_MSG;

    }
    else
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_OutMsgFromQue: *pucMsgCnt is invalid");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_OutMsgFromQue_ENUM
,LNAS_FUNCTION_LABEL8);
    }

    return ulRslt;
}


VOS_VOID    NAS_LMM_ClearBufMsgQue(
                NAS_LMM_PARALLEL_FSM_ENUM_UINT16     enParalFsmId,
                VOS_UINT32                          ulBufPriLevel)
{

    NAS_LMM_FSM_MSG_BUF_STRU             *pstFsmMsgBuffAddr  = NAS_LMM_NULL_PTR;
    NAS_LMM_BUFF_MSG_STRU               *pstBuffer          = NAS_LMM_NULL_PTR;
    NAS_LMM_BUFF_MSG_STRU               *pstQueMsg          = NAS_LMM_NULL_PTR;
    VOS_UINT8                           *pucCnt             = NAS_LMM_NULL_PTR;
    VOS_UINT8                           ucFreeCnt;
    VOS_UINT32                          ulRslt;

    /* ��ȡ����FSM Buffer�ĵ�ַ */
    pstFsmMsgBuffAddr                   = NAS_LMM_GetFsmBufAddr( enParalFsmId );
    if(NAS_LMM_NULL_PTR                  == pstFsmMsgBuffAddr)
    {
        NAS_LMM_PUBM_LOG_WARN(           "NAS_LMM_ClearBufMsgQue, Get pstFsmMsgBuffAddr Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_ClearBufMsgQue_ENUM
,LNAS_NULL_PTR);
        return;

    }

    /* �������ȼ�ȡ��Ϣ  */
    if (NAS_LMM_STORE_HIGH_PRIO_MSG      == ulBufPriLevel)
    {
        pucCnt                           = &(pstFsmMsgBuffAddr->ucHighPrioCnt);
        pstQueMsg                        = pstFsmMsgBuffAddr->astHighPrioBufQue;
    }
    else if (NAS_LMM_STORE_LOW_PRIO_MSG      == ulBufPriLevel)
    {
        pucCnt                           = &(pstFsmMsgBuffAddr->ucLowPrioCnt );
        pstQueMsg                        = pstFsmMsgBuffAddr->astLowPrioBufQue;
    }
    else
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_ClearBufMsgQue: OTHER QUE");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_ClearBufMsgQue_ENUM
,LNAS_FUNCTION_LABEL1);
    }

    /* �ͷ���Ϣ*/
    if ( (pucCnt != NAS_LMM_NULL_PTR) && (pstQueMsg != NAS_LMM_NULL_PTR) )
    {
        for(ucFreeCnt = 0 ; (ucFreeCnt < *pucCnt) && (ucFreeCnt < NAS_EMM_BUF_MSG_MAX_NUM) ; ucFreeCnt++)
        {
            pstBuffer                   = pstQueMsg[ucFreeCnt].pBuffMsg;
            ulRslt = NAS_COMM_FreeBuffItem(NAS_COMM_BUFF_TYPE_EMM, pstBuffer);

            if (NAS_COMM_BUFF_SUCCESS != ulRslt)
            {
                NAS_LMM_PUBM_LOG_WARN("NAS_LMM_ClearBufMsgQue, Memory Free is not succ");
                TLPS_PRINT2LAYER_WARNING(NAS_LMM_ClearBufMsgQue_ENUM
,LNAS_FUNCTION_LABEL2);
            }

            /* ����ֵ   */
            pstQueMsg[ucFreeCnt].pBuffMsg
                                        = NAS_LMM_NULL_PTR;
            pstQueMsg[ucFreeCnt].ulEvtType
                                        = 0;

            NAS_LMM_PUBM_LOG3_NORM(       "NAS_LMM_ClearBufMsgQue: Free Msg: enParalFsmId:,ulBufPriLevel,*pucCnt",
                                          enParalFsmId,ulBufPriLevel,*pucCnt);
            TLPS_PRINT2LAYER_INFO1(NAS_LMM_ClearBufMsgQue_ENUM
,LNAS_FUNCTION_LABEL3,
                                          enParalFsmId);
            TLPS_PRINT2LAYER_INFO2(NAS_LMM_ClearBufMsgQue_ENUM
,LNAS_FUNCTION_LABEL4,
                                          ulBufPriLevel,*pucCnt);

        }

        *pucCnt                         = 0;
    }

    return;
}
/*lint +e961*/
/*lint +e960*/


VOS_VOID  NAS_EMM_InitBufMsgQue( VOS_VOID )
{
    VOS_UINT32                          ulCont;
    NAS_LMM_FSM_MSG_BUF_STRU             *pstEmmFsmMsgBuf;

    NAS_LMM_PUBM_LOG_NORM(
    "NAS_EMM_InitBufMsgQue              START INIT...");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_InitBufMsgQue_ENUM
,LNAS_BEGIN);

    /* ��ǰ״̬��ʼ�� */
    /* ������Ϣ���г�ʼ�� */
    pstEmmFsmMsgBuf                     = NAS_LMM_GetFsmBufQueueAddr(NAS_LMM_PARALLEL_FSM_EMM);
    pstEmmFsmMsgBuf->ucHighPrioCnt      = NAS_EMM_MSG_BUF_EMPTY;
    pstEmmFsmMsgBuf->ucMidPrioCnt       = NAS_EMM_MSG_BUF_EMPTY;
    pstEmmFsmMsgBuf->ucLowPrioCnt       = NAS_EMM_MSG_BUF_EMPTY;
    for ( ulCont = 0; ulCont < NAS_EMM_BUF_MSG_MAX_NUM; ulCont++ )
    {
        pstEmmFsmMsgBuf->astHighPrioBufQue[ulCont].pBuffMsg = NAS_LMM_NULL_PTR;
        pstEmmFsmMsgBuf->astMidPrioBufQue[ulCont].pBuffMsg = NAS_LMM_NULL_PTR;
        pstEmmFsmMsgBuf->astLowPrioBufQue[ulCont].pBuffMsg = NAS_LMM_NULL_PTR;
    }

}



VOS_VOID  NAS_EMMC_InitBufMsgQue( VOS_VOID )
{

}

/*****************************************************************************
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

/* end of ��ϵͳ+ģ��+�ļ���.c */
