


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasCommBuffer.h"
#include    "LPsOm.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASCOMMBUFFER_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASCOMMBUFFER_C
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
/* ESM������ */
VOS_UINT8                               g_aucEsmBuff[NAS_COMM_BUFF_ESM_MAX_ITEM_NUM][NAS_COMM_BUFF_ESM_ITEM_MAX_SIZE + NAS_COMM_BUFF_ITEM_RESERVED_LEN];

/* EMM������ */
VOS_UINT8                               g_aucEmmBuff[NAS_COMM_BUFF_EMM_MAX_ITEM_NUM][NAS_COMM_BUFF_EMM_ITEM_MAX_SIZE + NAS_COMM_BUFF_ITEM_RESERVED_LEN];

/* �������ͱ� */
NAS_COMM_BUFFER_TYPE_TABLE_ITEM_STRU    g_astNasBuffTypeTable[] =
{
    {NAS_COMM_BUFF_TYPE_ESM,  NAS_COMM_BUFF_ESM_MAX_ITEM_NUM, {0},&g_aucEsmBuff[0][0], NAS_COMM_BUFF_ESM_ITEM_MAX_SIZE},
    {NAS_COMM_BUFF_TYPE_EMM,  NAS_COMM_BUFF_EMM_MAX_ITEM_NUM, {0},&g_aucEmmBuff[0][0],NAS_COMM_BUFF_EMM_ITEM_MAX_SIZE}
};

/* ���������Ʊ� */
NAS_COMM_BUFFER_CTRL_BLOCK_STRU         g_astNasBuffCtrlBlockTable[NAS_COMM_BUFF_NUM];

/*****************************************************************************
  3 Function
*****************************************************************************/
/*lint -e826*/
/*****************************************************************************
 Function Name   : NAS_COMM_CheckBuff
 Description     : �ж��û������ͷŵĵ�ַ�Ƿ�Ϸ�
 Input           : pucBuffItemAddr-----------�����¼�׵�ַ
                   ulMaxBuffItemLen----------�����¼��󳤶�
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-1-28  Draft Enact
    2.lihong00150010      2010-4-22  Modify

*****************************************************************************/
/*lint -e961*/
VOS_UINT32  NAS_COMM_CheckBuff
(
    VOS_UINT8                          *pucBuffItemAddr,
    VOS_UINT32                          ulMaxBuffItemLen
)
{
    NAS_COMM_BUFFER_ITEM_HEAD_STRU     *pstNasBuffItemHead = (NAS_COMM_BUFFER_ITEM_HEAD_STRU*)pucBuffItemAddr;
    VOS_UINT32                         *pulNasBuffItemTail = VOS_NULL_PTR;

    /* �жϻ����¼ͷ������ʶ�Ƿ���ȷ */
    if (pstNasBuffItemHead->ulProtCrc != NAS_COMM_BUFF_PROT_CRC)
    {
        NAS_COMM_LOG_WARN("NAS_COMM_CheckBuff:WARN:Buffer head protect flag is modified!");
        TLPS_PRINT2LAYER_WARNING(NAS_COMM_CheckBuff_ENUM, LNAS_FUNCTION_LABEL1);
        return NAS_COMM_BUFF_CHECK_FAIL;
    }

    /* ���㻺���¼β��ַ */
    pulNasBuffItemTail = (VOS_UINT32*)( pucBuffItemAddr +
                                        NAS_COMM_BUFF_ITEM_RESERVED_HEAD_LEN +
                                        ulMaxBuffItemLen);

    /* �жϻ����¼β������ʶ�Ƿ���ȷ */
    if (*pulNasBuffItemTail != NAS_COMM_BUFF_PROT_CRC)
    {
        NAS_COMM_LOG_WARN("NAS_COMM_CheckBuff:WARN:Buffer tail protect flag is modified!");
        TLPS_PRINT2LAYER_WARNING(NAS_COMM_CheckBuff_ENUM, LNAS_FUNCTION_LABEL2);
        return NAS_COMM_BUFF_CHECK_FAIL;
    }

    return NAS_COMM_BUFF_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_COMM_InitBuffItem
 Description     : ��ʼ�������¼
 Input           : pucBuffItemAddr-----------�����¼�׵�ַ
                   ulMaxBuffItemLen----------�����¼��󳤶�
 Output          :
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-1-28  Draft Enact
    2.lihong00150010      2010-4-24  Modify

*****************************************************************************/
VOS_VOID  NAS_COMM_InitBuffItem
(
    VOS_UINT8                          *pucBuffItemAddr,
    VOS_UINT32                          ulMaxBuffItemLen
)
{
    NAS_COMM_BUFFER_ITEM_HEAD_STRU     *pstNasBuffItemHead = (NAS_COMM_BUFFER_ITEM_HEAD_STRU*)pucBuffItemAddr;
    VOS_UINT32                         *pulNasBuffItemTail = VOS_NULL_PTR;

    /* ��ʶ��¼δ���� */
    pstNasBuffItemHead->ucUsedTag = NAS_COMM_BUFF_ITEM_UNUSED;

    /* ��ֵ�����¼ͷ������ʶ */
    pstNasBuffItemHead->ulProtCrc = NAS_COMM_BUFF_PROT_CRC;

    /* ���㻺���¼β��ַ */
    pulNasBuffItemTail = (VOS_UINT32*)( pucBuffItemAddr +
                                        NAS_COMM_BUFF_ITEM_RESERVED_HEAD_LEN +
                                        ulMaxBuffItemLen);

    /* ��ֵ�����¼β������ʶ */
    *pulNasBuffItemTail = NAS_COMM_BUFF_PROT_CRC;
}

/*****************************************************************************
 Function Name   : NAS_COMM_ClearBuffItem
 Description     : ��������¼
 Input           : pucBuffItemAddr-----------�����¼�׵�ַ
                   ulMaxBuffItemLen----------�����¼��󳤶�
 Output          :
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-4-22  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_COMM_ClearBuffItem
(
    VOS_UINT8                          *pucBuffItemAddr,
    VOS_UINT32                          ulMaxBuffItemLen
)
{
    NAS_COMM_BUFFER_ITEM_HEAD_STRU     *pstNasBuffItemHead = (NAS_COMM_BUFFER_ITEM_HEAD_STRU *)pucBuffItemAddr;

    /* ��ʶ��¼δ���� */
    pstNasBuffItemHead->ucUsedTag = NAS_COMM_BUFF_ITEM_UNUSED;

    /* ��������¼���� */
    /*lint -e960*/
    NAS_COMM_MEM_SET(   (pucBuffItemAddr + NAS_COMM_BUFF_ITEM_RESERVED_HEAD_LEN),
                        NAS_COMM_NULL,
                        ulMaxBuffItemLen);
    /*lint +e960*/
}


/*****************************************************************************
 Function Name   : NAS_COMM_QueryBuffTypeTableItem
 Description     : ���һ������ͱ��¼
 Input           : enNasBuffType----------------NAS��������
                   pulIndex---------------------�������ͱ��¼������ָ��
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-4-21  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_COMM_QueryBuffTypeTableItem
(
    NAS_COMM_BUFF_TYPE_ENUM_UINT8       enNasBuffType,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                              ulCnt                   = NAS_COMM_NULL;
    NAS_COMM_BUFFER_TYPE_TABLE_ITEM_STRU   *pstBufferTypeTable      = NAS_GetBufferTypeTable();

    /* �������������pstBuff��ͬ�ļ�¼ */
    for (ulCnt = NAS_COMM_NULL; ulCnt < NAS_COMM_BUFF_NUM; ulCnt++)
    {
        /*lint -e960*/
        if (enNasBuffType == pstBufferTypeTable[ulCnt].enNasBufferType)
        {
            break;
        }
        /*lint +e960*/
    }

    if (ulCnt < NAS_COMM_BUFF_NUM)
    {
        *pulIndex = ulCnt;
        return NAS_COMM_BUFF_SUCCESS;
    }

    return NAS_COMM_BUFF_QUERY_TYPE_TABLE_FAIL;
}

/*****************************************************************************
 Function Name   : NAS_COMM_InitBuff
 Description     : ��ʼ��������
 Input           : enNasBuffType----------------NAS��������
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-1-28  Draft Enact
    2.lihong00150010      2010-4-22  Modify

*****************************************************************************/
VOS_VOID  NAS_COMM_InitBuff
(
    NAS_COMM_BUFF_TYPE_ENUM_UINT8            enNasBuffType
)
{
    VOS_UINT32                              ulCnt                   = NAS_COMM_NULL;
    VOS_UINT32                              ulBuffTypeTabItemIndex  = NAS_COMM_NULL;
    VOS_UINT8                               ucMaxBuffItemNum        = NAS_COMM_NULL;
    VOS_UINT32                              ulMaxBuffItemLen        = NAS_COMM_NULL;
    NAS_COMM_BUFFER_TYPE_TABLE_ITEM_STRU   *pstBufferTypeTableItem  = VOS_NULL_PTR;
    VOS_UINT8                              *pucBuffItemAddr         = VOS_NULL_PTR;
    NAS_COMM_BUFFER_CTRL_BLOCK_STRU        *pstBuffCtrlBlock        = VOS_NULL_PTR;

    /* �жϻ��������Ƿ�Ϸ� */
    if (NAS_COMM_BUFF_QUERY_TYPE_TABLE_FAIL ==
            NAS_COMM_QueryBuffTypeTableItem(enNasBuffType, &ulBuffTypeTabItemIndex))
    {
        NAS_COMM_LOG_WARN("NAS_COMM_InitBuff:WARN:Buffer is invalid!");
        TLPS_PRINT2LAYER_WARNING(NAS_COMM_InitBuff_ENUM, LNAS_FUNCTION_LABEL1);
        return ;
    }

    /* ��ȡ�������ͱ��¼ */
    pstBufferTypeTableItem  = NAS_GetBufferTypeTableItem(ulBuffTypeTabItemIndex);

    ucMaxBuffItemNum        = pstBufferTypeTableItem->ucMaxBuffItemNum;
    ulMaxBuffItemLen        = pstBufferTypeTableItem->ulMaxBuffItemLen;

    /* ��ȡ������ƿ� */
    pstBuffCtrlBlock    = NAS_GetBufferCtrlBlock(ulBuffTypeTabItemIndex);

    /* ������������ƿ� */
    /*lint -e960*/
    NAS_COMM_MEM_SET(   pstBuffCtrlBlock,
                        NAS_COMM_NULL,
                        sizeof(NAS_COMM_BUFFER_CTRL_BLOCK_STRU));

    /* ����������ռ� */
    NAS_COMM_MEM_SET(   pstBufferTypeTableItem->pucBuff,
                        NAS_COMM_NULL,
                        ucMaxBuffItemNum * (ulMaxBuffItemLen + NAS_COMM_BUFF_ITEM_RESERVED_LEN));
    /*lint +e960*/
    /* ��ֵ���ü�¼����Ϊ0 */
    pstBuffCtrlBlock->ucUsedNum     = NAS_COMM_NULL;

    /* ��ֵ���洢��¼���� */
    pstBuffCtrlBlock->ucMaxNum      = ucMaxBuffItemNum;

    /* ��ֵ�洢��¼��󳤶� */
    pstBuffCtrlBlock->ulMaxItemLen  = ulMaxBuffItemLen;

    /* ������ȥ���Ϊ�ѳ�ʼ�� */
    pstBuffCtrlBlock->enState = NAS_COMM_BUFF_STATE_INITED;

    for (ulCnt = NAS_COMM_NULL; ulCnt < pstBuffCtrlBlock->ucMaxNum; ulCnt++)
    {
        /* ���㵱ǰ�����¼�׵�ַ */
        pucBuffItemAddr = pstBufferTypeTableItem->pucBuff
                                + (ulCnt * (ulMaxBuffItemLen + NAS_COMM_BUFF_ITEM_RESERVED_LEN));

        /* ��ʼ�������¼ */
        NAS_COMM_InitBuffItem(pucBuffItemAddr, ulMaxBuffItemLen);
    }
}

/*****************************************************************************
 Function Name   : NAS_COMM_AllocBuffItem
 Description     : �����µĻ����¼
 Input           : enNasBuffType------------NAS��������
                   ulAllocLen---------------�������ռ��С
 Return          : VOS_VOID*

 History         :
    1.lihong00150010      2010-1-28  Draft Enact
    2.lihong00150010      2010-4-22  Modify

*****************************************************************************/
VOS_VOID*  NAS_COMM_AllocBuffItem
(
    NAS_COMM_BUFF_TYPE_ENUM_UINT8       enNasBuffType,
    VOS_UINT32                          ulAllocLen
)
{
    VOS_UINT32                              ulCnt                   = NAS_COMM_NULL;
    VOS_UINT32                              ulBuffTypeTabItemIndex  = NAS_COMM_NULL;
    VOS_UINT8                               ucMaxBuffItemNum        = NAS_COMM_NULL;
    VOS_UINT32                              ulMaxBuffItemLen        = NAS_COMM_NULL;
    NAS_COMM_BUFFER_TYPE_TABLE_ITEM_STRU   *pstBufferTypeTableItem  = VOS_NULL_PTR;
    NAS_COMM_BUFFER_CTRL_BLOCK_STRU        *pstBuffCtrlBlock        = VOS_NULL_PTR;
    VOS_UINT8                              *pucBuffItemAddr         = VOS_NULL_PTR;
    NAS_COMM_BUFFER_ITEM_HEAD_STRU         *pstNasBuffItemHead      = VOS_NULL_PTR;

    /* �жϻ��������Ƿ�Ϸ� */
    if (NAS_COMM_BUFF_QUERY_TYPE_TABLE_FAIL ==
            NAS_COMM_QueryBuffTypeTableItem(enNasBuffType, &ulBuffTypeTabItemIndex))
    {
        NAS_COMM_LOG_WARN("NAS_COMM_AllocBuffItem:WARN:Buffer is invalid!");
        TLPS_PRINT2LAYER_WARNING(NAS_COMM_AllocBuffItem_ENUM, LNAS_FUNCTION_LABEL1);
        return VOS_NULL_PTR;
    }

    /* ��ȡ�������ͱ��¼ */
    pstBufferTypeTableItem  = NAS_GetBufferTypeTableItem(ulBuffTypeTabItemIndex);

    ucMaxBuffItemNum        = pstBufferTypeTableItem->ucMaxBuffItemNum;
    ulMaxBuffItemLen        = pstBufferTypeTableItem->ulMaxBuffItemLen;

    /* ��ȡ������ƿ� */
    pstBuffCtrlBlock    = NAS_GetBufferCtrlBlock(ulBuffTypeTabItemIndex);

    /* �жϻ������Ƿ��ѳ�ʼ�� */
    if (pstBuffCtrlBlock->enState != NAS_COMM_BUFF_STATE_INITED)
    {
        NAS_COMM_LOG_WARN("NAS_COMM_AllocBuffItem:WARN:The buffer is not initialized!");
        TLPS_PRINT2LAYER_WARNING(NAS_COMM_AllocBuffItem_ENUM, LNAS_FUNCTION_LABEL2);
        return VOS_NULL_PTR;
    }

    /* �ж��û�����Ŀռ��С�Ƿ񳬳��˻����¼����󳤶� */
    if (ulAllocLen > ulMaxBuffItemLen)
    {
        NAS_COMM_LOG_WARN("NAS_COMM_AllocBuffItem:WARN:The request of alloc space is too big!");
        TLPS_PRINT2LAYER_WARNING(NAS_COMM_AllocBuffItem_ENUM, LNAS_FUNCTION_LABEL3);
        return VOS_NULL_PTR;
    }

    /* �жϻ������Ƿ����� */
    if (pstBuffCtrlBlock->ucUsedNum >= ucMaxBuffItemNum)
    {
        NAS_COMM_LOG_WARN("NAS_COMM_AllocBuffItem:WARN:Insufficent resources!");
        TLPS_PRINT2LAYER_WARNING(NAS_COMM_AllocBuffItem_ENUM, LNAS_FUNCTION_LABEL4);
        return VOS_NULL_PTR;
    }

    /* ������δʹ�õĻ���ռ䣬������û� */
    for (ulCnt = NAS_COMM_NULL; ulCnt < ucMaxBuffItemNum; ulCnt++)
    {
        /* ���㻺���¼�׵�ַ */
        pucBuffItemAddr = pstBufferTypeTableItem->pucBuff
                                + (ulCnt * (ulMaxBuffItemLen + NAS_COMM_BUFF_ITEM_RESERVED_LEN));

        pstNasBuffItemHead = (NAS_COMM_BUFFER_ITEM_HEAD_STRU *)pucBuffItemAddr;
        if (NAS_COMM_BUFF_ITEM_UNUSED == pstNasBuffItemHead->ucUsedTag)
        {
            /* �ѷ����¼����1 */
            pstBuffCtrlBlock->ucUsedNum++;

            /* ��ʶ��¼�ѷ��� */
            pstNasBuffItemHead->ucUsedTag = NAS_COMM_BUFF_ITEM_USED;

            return (VOS_VOID*)(pucBuffItemAddr + NAS_COMM_BUFF_ITEM_RESERVED_HEAD_LEN);
        }
    }

    return VOS_NULL_PTR;
}

/*****************************************************************************
 Function Name   : NAS_COMM_FreeBuffItem
 Description     : �ͷŻ����¼
 Input           : enNasBuffType----------------NAS��������
                   pBufferItemAddr--------------�����¼��ַ
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-04-21  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_COMM_FreeBuffItem
(
    NAS_COMM_BUFF_TYPE_ENUM_UINT8       enNasBuffType,
    const VOS_VOID                     *pBufferItemStorageAddr
)
{
    VOS_UINT32                              ulCnt                   = NAS_COMM_NULL;
    VOS_UINT32                              ulBuffTypeTabItemIndex  = NAS_COMM_NULL;
    VOS_UINT8                               ucMaxBuffItemNum        = NAS_COMM_NULL;
    VOS_UINT32                              ulMaxBuffItemLen        = NAS_COMM_NULL;
    NAS_COMM_BUFFER_TYPE_TABLE_ITEM_STRU   *pstBufferTypeTableItem  = VOS_NULL_PTR;
    NAS_COMM_BUFFER_CTRL_BLOCK_STRU        *pstBuffCtrlBlock        = VOS_NULL_PTR;
    VOS_UINT8                              *pucBuffItemAddr         = VOS_NULL_PTR;
    NAS_COMM_BUFFER_ITEM_HEAD_STRU         *pstNasBuffItemHead      = VOS_NULL_PTR;

    /* �жϻ��������Ƿ�Ϸ� */
    if (NAS_COMM_BUFF_QUERY_TYPE_TABLE_FAIL ==
            NAS_COMM_QueryBuffTypeTableItem(enNasBuffType, &ulBuffTypeTabItemIndex))
    {
        NAS_COMM_LOG_WARN("NAS_COMM_FreeBuffItem:WARN:Buffer is invalid!");
        TLPS_PRINT2LAYER_WARNING(NAS_COMM_FreeBuffItem_ENUM, LNAS_FUNCTION_LABEL1);
        return NAS_COMM_BUFF_FREE_FAIL;
    }

    /* �ж��û������ͷŵĵ�ַ�Ƿ�Ϊ�� */
    if (pBufferItemStorageAddr == VOS_NULL_PTR)
    {
        NAS_COMM_LOG_WARN("NAS_COMM_FreeBuffItem:WARN:Input para pBufferItemStorageAddr is null!");
        TLPS_PRINT2LAYER_WARNING(NAS_COMM_FreeBuffItem_ENUM, LNAS_FUNCTION_LABEL2);
        return NAS_COMM_BUFF_FREE_FAIL;
    }

    /* ��ȡ�������ͱ��¼ */
    pstBufferTypeTableItem  = NAS_GetBufferTypeTableItem(ulBuffTypeTabItemIndex);

    ucMaxBuffItemNum        = pstBufferTypeTableItem->ucMaxBuffItemNum;
    ulMaxBuffItemLen        = pstBufferTypeTableItem->ulMaxBuffItemLen;

    /* ��ȡ������ƿ� */
    pstBuffCtrlBlock    = NAS_GetBufferCtrlBlock(ulBuffTypeTabItemIndex);

    /* �жϻ������Ƿ��ѳ�ʼ�� */
    if (pstBuffCtrlBlock->enState != NAS_COMM_BUFF_STATE_INITED)
    {
        NAS_COMM_LOG_WARN("NAS_COMM_FreeBuffItem:WARN:The buffer is not initialized!");
        TLPS_PRINT2LAYER_WARNING(NAS_COMM_FreeBuffItem_ENUM, LNAS_FUNCTION_LABEL3);
        return NAS_COMM_BUFF_FREE_FAIL;
    }

    /* ��ȡ�����¼�׵�ַ */
    pstNasBuffItemHead = (NAS_COMM_BUFFER_ITEM_HEAD_STRU *)
                         ((VOS_UINT8 *)pBufferItemStorageAddr - NAS_COMM_BUFF_ITEM_RESERVED_HEAD_LEN);

    /* �ж��û������ͷŵĵ�ַ�Ƿ�Ϸ� */
    if (NAS_COMM_BUFF_SUCCESS != NAS_COMM_CheckBuff((VOS_UINT8*)pstNasBuffItemHead, ulMaxBuffItemLen))
    {
        NAS_COMM_LOG_WARN("NAS_COMM_FreeBuffItem:WARN:NAS_COMM_CheckBuff failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_COMM_FreeBuffItem_ENUM, LNAS_FUNCTION_LABEL4);
        return NAS_COMM_BUFF_FREE_FAIL;
    }

    for (ulCnt = NAS_COMM_NULL; ulCnt < ucMaxBuffItemNum; ulCnt++)
    {
        /* ���㵱ǰ�����¼�׵�ַ */
        pucBuffItemAddr = pstBufferTypeTableItem->pucBuff
                                + (ulCnt * (ulMaxBuffItemLen + NAS_COMM_BUFF_ITEM_RESERVED_LEN));

        /* �жϵ�ǰ�����¼�Ƿ�Ϊ�û������ͷŵĻ����¼ */
        /*lint -e960*/
        if ((VOS_UINT8*)pstNasBuffItemHead == pucBuffItemAddr)
        {
            break;
        }
        /*lint +e960*/
    }

    if (ulCnt >= ucMaxBuffItemNum)
    {
        NAS_COMM_LOG_WARN("NAS_COMM_FreeBuffItem:WARN: The input pointer address is not in buffer list!");
        TLPS_PRINT2LAYER_WARNING(NAS_COMM_FreeBuffItem_ENUM, LNAS_FUNCTION_LABEL5);
        return NAS_COMM_BUFF_FREE_FAIL;
    }

    if ((pstNasBuffItemHead->ucUsedTag == NAS_COMM_BUFF_ITEM_USED))
    {
        /* �ѷ����¼����1 */
        pstBuffCtrlBlock->ucUsedNum--;

        /* ��ʼ�������¼ */
        NAS_COMM_ClearBuffItem((VOS_UINT8 *)pstNasBuffItemHead, ulMaxBuffItemLen);
    }

    return NAS_COMM_BUFF_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_COMM_ClearBuff
 Description     : ��ջ�����
 Input           : enNasBuffType----------------NAS��������
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-4-24  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_COMM_ClearBuff
(
    NAS_COMM_BUFF_TYPE_ENUM_UINT8       enNasBuffType
)
{
    VOS_UINT32                              ulCnt                   = NAS_COMM_NULL;
    VOS_UINT32                              ulBuffTypeTabItemIndex  = NAS_COMM_NULL;
    VOS_UINT32                              ulMaxBuffItemLen        = NAS_COMM_NULL;
    NAS_COMM_BUFFER_TYPE_TABLE_ITEM_STRU   *pstBufferTypeTableItem  = VOS_NULL_PTR;
    VOS_UINT8                              *pucBuffItemAddr         = VOS_NULL_PTR;
    NAS_COMM_BUFFER_CTRL_BLOCK_STRU        *pstBuffCtrlBlock        = VOS_NULL_PTR;

    /* �жϻ��������Ƿ�Ϸ� */
    if (NAS_COMM_BUFF_QUERY_TYPE_TABLE_FAIL ==
            NAS_COMM_QueryBuffTypeTableItem(enNasBuffType, &ulBuffTypeTabItemIndex))
    {
        NAS_COMM_LOG_WARN("NAS_COMM_ClearBuff:WARN:Buffer is invalid!");
        TLPS_PRINT2LAYER_WARNING(NAS_COMM_ClearBuff_ENUM, LNAS_FUNCTION_LABEL1);
        return ;
    }

    /* ��ȡ�������ͱ��¼ */
    pstBufferTypeTableItem  = NAS_GetBufferTypeTableItem(ulBuffTypeTabItemIndex);

    ulMaxBuffItemLen        = pstBufferTypeTableItem->ulMaxBuffItemLen;

    /* ��ȡ������ƿ� */
    pstBuffCtrlBlock        = NAS_GetBufferCtrlBlock(ulBuffTypeTabItemIndex);

    /* ��ֵ���ü�¼����Ϊ0 */
    pstBuffCtrlBlock->ucUsedNum = NAS_COMM_NULL;

    for (ulCnt = NAS_COMM_NULL; ulCnt < pstBuffCtrlBlock->ucMaxNum; ulCnt++)
    {
        /* ���㵱ǰ�����¼�׵�ַ */
        pucBuffItemAddr = pstBufferTypeTableItem->pucBuff
                                + (ulCnt * (ulMaxBuffItemLen + NAS_COMM_BUFF_ITEM_RESERVED_LEN));

        /* ��������¼ */
        NAS_COMM_ClearBuffItem(pucBuffItemAddr, ulMaxBuffItemLen);
    }
}
/*lint +e826*/
/*lint +e961*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of NasCommBuffer.c */
