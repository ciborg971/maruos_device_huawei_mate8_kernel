

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasLmmPubMInclude.h"
#include    "NasMmlMsgProc.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASMMPUBMINTRAMSG_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASMMPUBMINTRAMSG_C
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



/*****************************************************************************
 Function Name  : NAS_LMM_GetSendIntraMsgBuffAddr
 Discription    : ��ȡ�����ڲ���Ϣ�ĵ�ַ
                  �����ڲ���Ϣ�Ĺ���Ϊ:
                    1.�����ڲ���Ϣ��ַ,
                    2.����ڲ���Ϣ����
                    3.�����ڲ���Ϣ
 Input          : ��Ϣ����:�ó��Ⱥ���ͬDOPRA������Ϣʱ�ĳ��ȣ���������
                    ��Ϣͷ VOS_MSG_HEADER�ĳ���
 Output         : None
 Return         : ��Ϣ��ַ��NasMmIntraMsgBlock ָ������
 History:
*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
NasMmIntraMsgBlock * NAS_LMM_GetSendIntraMsgBuffAddr( VOS_UINT32 ulBuffSize )
{
    VOS_UINT16                          usQueHeaderPos;
    VOS_UINT16                          usQueTailPos;
    NAS_LMM_INTRA_MSG_QUEUE_STRU        *pstMsgQue;
    VOS_UINT8                          *pucMsgBuff;

    NAS_LMM_INTRA_MSG_STRU  *pstIntraMsgHeader = NAS_LMM_NULL_PTR;

    if ( (0 == ulBuffSize) || (NAS_EMM_INTRA_MSG_MAX_SIZE < ulBuffSize ) )
    {
        /* ��ӡ������Ϣ */
        NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_GetSendIntraMsgBuffAddr, Size error, ", ulBuffSize);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_GetSendIntraMsgBuffAddr_ENUM
,LNAS_ERROR,ulBuffSize);

        return NAS_LMM_NULL_PTR;
    }

    /* ��ȡ���е�ַ */
    pstMsgQue      = NAS_LMM_GetMmIntrMsgQueueAddr();


    /* ��ͷ��βλ�� */
    usQueHeaderPos = pstMsgQue->usHeader % NAS_LMM_INTRA_MSG_MAX_NUM;
    usQueTailPos   = pstMsgQue->usTail % NAS_LMM_INTRA_MSG_MAX_NUM;

    /* ��֤�Ƿ������,��������+1, Ԥ��һ�����пռ䲻�ܷ���, �п��ܸ���Ϣ���ڴ��� */
    if ( ((usQueTailPos + 1 + 1) % NAS_LMM_INTRA_MSG_MAX_NUM) != usQueHeaderPos )
    {
        pucMsgBuff = pstMsgQue->aucMsgBuff[(usQueTailPos) % NAS_LMM_INTRA_MSG_MAX_NUM];

        /* ������Ļ�������0 */
        NAS_LMM_MEM_SET(pucMsgBuff, 0, NAS_EMM_INTRA_MSG_MAX_SIZE);


        pstIntraMsgHeader                = (NAS_LMM_INTRA_MSG_STRU *)pucMsgBuff;

        /* ��д�ڲ���Ϣ��Ϣͷ�еĳ����� */
        pstIntraMsgHeader->ulLength      = ulBuffSize;

        return (NasMmIntraMsgBlock *)pucMsgBuff;
    }
    else
    {
        /* ��ӡ������Ϣ */
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_GetSendIntraMsgBuffAddr, Queue full!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_GetSendIntraMsgBuffAddr_ENUM
,LNAS_FUNCTION_LABEL1);

        return NAS_LMM_NULL_PTR;
    }
}


/*****************************************************************************
 Function Name  : NAS_EMM_SendIntraMsg
 Discription    : �����ڲ���Ϣ����
                  ʹ�÷���:��������Ϣ��(RRC_MAIN_GetSendIntraMsgBuffAddr),
                           ���ص�ַ,���ݵ�ַ��д��Ϣ����,Ȼ����øú���
                   �ú�����ʵ����:ʹǰ�����ڲ���Ϣ����������Ϣ��,�����Ϣ
                   ���Ĳ�����Ч;
 Input          : pucIntraMsg   :ָ���ڲ���Ϣ��ָ��
 Output         : None
 Return         : �ɹ� ʧ��
 History:
*****************************************************************************/
VOS_UINT32 NAS_LMM_MMSendIntraMsg(  VOS_VOID          **pucIntraMsg )/*lint -e818*/
{

    if ( NAS_LMM_NULL_PTR == pucIntraMsg )
    {
        /* ��ӡ������Ϣ */
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_SendIntraMsg, IntraMsg Null Pointer.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_MMSendIntraMsg_ENUM
,LNAS_NULL_PTR);

        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }


    /* ��Ϣ����� */
    NAS_LMM_MAIN_EnQueue();

    return  NAS_EMM_SUCC;
}/*lint +e818*/

/*****************************************************************************
 Function Name  : NAS_LMM_MAIN_EnQueue
 Discription    : ��Ϣ�����,
                  ����OM�Ĺ��Ӻ�������OM�и��ٳ���;
                  ֻ��PUBģ��ʹ�ã�����ģ������Ҫ���Լ���װ
 Input          : None
 Output         : None
 Return         :

 History:
      1. hanlufeng 41410  2008-02-25  ��ֲ����
*****************************************************************************/
VOS_VOID    NAS_LMM_MAIN_EnQueue(VOS_VOID)
{
    NAS_LMM_INTRA_MSG_QUEUE_STRU            *pstMsgQue;

    /* ��ȡ���е�ַ */
    pstMsgQue         = NAS_LMM_GetMmIntrMsgQueueAddr();


    /* ����OM�Ĺ��Ӻ�������OM�и��ٳ��� */


    /* ѭ�����еĶ�βָ����һ��λ�� */
    pstMsgQue->usTail = (pstMsgQue->usTail + 1) % NAS_LMM_INTRA_MSG_MAX_NUM;

    return;
}


/*****************************************************************************
 Function Name  : NAS_LMM_GetIntraMsgFromQueue
 Discription    : ��PUBLIC������������Ϣ��,���ż���Ƿ����ڲ���Ϣ������,
                  �����,��ָ����һ����������ڲ���Ϣ,ͬʱ������Ϣ����,
                  ��:����Ϣ������Ϣ�����б�ɾ��,�������ĸ���Ϣ�Ƿ��ѱ�
                  ��ȷ����;
                  ������Ϣ�޷�����ǰ״̬����,��MM����������Ϣ�������;
                  ������Ϣ������̳���,������Ϣ�����д�,����Ϣ���в�����;
 Input          : None
 Output         : None
 Return         : NULL: ��ʾû���ڲ���Ϣ������
                  ����: ָ���������ڲ���Ϣ
 History:
*****************************************************************************/
VOS_UINT8 * NAS_LMM_GetIntraMsgFromQueue( VOS_VOID  )
{
    VOS_UINT16                          usQueHeaderPos;
    VOS_UINT16                          usQueTailPos;
    VOS_UINT8                          *pucMsg     = NAS_LMM_NULL_PTR;
    NAS_LMM_INTRA_MSG_QUEUE_STRU        *pstMsgQue  = NAS_LMM_NULL_PTR;

    /* ��ȡ���е�ַ */
    pstMsgQue      = NAS_LMM_GetMmIntrMsgQueueAddr();

    /* ��ͷ��βλ�� */
    usQueHeaderPos = pstMsgQue->usHeader % NAS_LMM_INTRA_MSG_MAX_NUM;
    usQueTailPos   = pstMsgQue->usTail % NAS_LMM_INTRA_MSG_MAX_NUM;

    /* ����Ϊ�� */
    if ( usQueHeaderPos == usQueTailPos )
    {
        return NAS_LMM_NULL_PTR;
    }

    /* ��Ϣ��ַ */
    pucMsg = (pstMsgQue->aucMsgBuff)[usQueHeaderPos];

    /* ��Ϣ������ */
    NAS_LMM_DeQueue();

    return pucMsg;
}

/*****************************************************************************
 Function Name  : NAS_LMM_DeQueue
 Discription    : ��Ϣ������
 Input          : None
 Output         : None
 Return         :

 History:
*****************************************************************************/
VOS_VOID NAS_LMM_DeQueue(VOS_VOID)
{
    NAS_LMM_INTRA_MSG_QUEUE_STRU *pstMsgQue = NAS_LMM_NULL_PTR;


    /* ��ȡ���е�ַ */
    pstMsgQue           = NAS_LMM_GetMmIntrMsgQueueAddr();

    pstMsgQue->usHeader = (pstMsgQue->usHeader + 1) % NAS_LMM_INTRA_MSG_MAX_NUM;

    return;
}
MsgBlock *  NAS_LMM_GetLmmMmcMsgBuf( VOS_UINT32 ulBuffSize )
{
    MsgBlock                           *pstLmmMmcIntraMsg = VOS_NULL_PTR;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_GetLmmMmcMsgBuf entered.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_GetLmmMmcMsgBuf_ENUM
,LNAS_ENTRY);

/* PC�����£�����Dopra��Ϣ����*/
#if(VOS_WIN32 == VOS_OS_VER)

    pstLmmMmcIntraMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(ulBuffSize);

/* ���廷���£�����MMC�ڲ���Ϣ*/
#else
    pstLmmMmcIntraMsg = (VOS_VOID *)NAS_MML_GetIntMsgSendBuf(ulBuffSize);

#endif

    return pstLmmMmcIntraMsg;
}


VOS_VOID  NAS_LMM_SendLmmMmcMsg( const VOS_VOID *pstLmmMmcMsg )
{
    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_SendLmmMmcMsg entered.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_SendLmmMmcMsg_ENUM
,LNAS_ENTRY);

/* PC�����£�����Dopra��Ϣ����*/
#if(VOS_WIN32 == VOS_OS_VER)

    NAS_LMM_SEND_MSG(pstLmmMmcMsg);
/*PC REPLAY MODIFY BY LEILI BEGIN*/
/* ���廷���£�����MMC�ڲ���Ϣ����*/
#else
    #ifndef __PS_WIN32_RECUR__
    /* lihong00150010 volte phaseiii begin */
    NAS_LMM_PUBM_PrintSendMsg((const PS_MSG_HEADER_STRU *)pstLmmMmcMsg,NAS_COMM_GET_MM_PRINT_BUF());
    /* lihong00150010 volte phaseiii end */

    NAS_MML_SndInternalMsg((VOS_VOID *)pstLmmMmcMsg);
    #else
    NAS_LMM_SEND_MSG(pstLmmMmcMsg);
    #endif

#endif
/*PC REPLAY MODIFY BY LEILI END*/
}
/*lint +e961*/
/*lint +e960*/
/*****************************************************************************
 Function Name  :
 Discription    :
 Input          :
 Output         : None
 Return         : None
 History:
      1.  Name+ID  yyyy-mm-dd  Draft Enact
*****************************************************************************/




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ��ϵͳ+ģ��+�ļ���.c */
