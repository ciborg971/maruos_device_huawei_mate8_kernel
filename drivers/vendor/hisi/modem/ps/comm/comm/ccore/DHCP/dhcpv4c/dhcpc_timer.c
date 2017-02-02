#include "dhcp_inc.h"
#include "dhcpc_def.h"
#include "dhcpc_comp.h"
#include "dhcpc_dbg.h"

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_DHCPC_TIMER_C
/*lint +e767*/

/* ʱ��ڵ�Ĺ�ϣ��������ɾ����ʱ�����ϵĽڵ�ʱ�ܹ����ٶ�λ���ڵ㣬�ڵ��ϣֵͨ��teidc����õ� */
DHCPC_TIMER_LIST_HEAD_S *g_pstDHCPTimerHashList = NULL;
/* �뼶��ʱ������ */
/* DHCPC_TIMER_NODE_S *g_pstDHCPTimerSecondList = NULL; */
DHCPC_TIMER_NODE_S g_pstDHCPTimerSecondList[DHCPC_SECOND_TIMER_LEN] = {0};
/* Сʱ��ʱ������ */
/* DHCPC_TIMER_NODE_S *g_pstDHCPTimerHourList = NULL; */
DHCPC_TIMER_NODE_S g_pstDHCPTimerHourList[DHCPC_HOUR_TIMER_LEN] = {0};

/* �뼶��ʱ��������ĵ�ǰλ�� */
ULONG g_ulDHCPCTimerSecondPos = 0;
/* Сʱ��ʱ��������ĵ�ǰλ�� */
ULONG g_ulDHCPCTimerHourPos = 0;

/* Сʱ��ʱ��������Ӵ������ */
ULONG g_ulDHCPCTimerHourSecNum = 0;

/* �뼶��ʱ��id */
RELTMR_T g_ulDHCPCSecondTimerId = 0;
/* Сʱ��ʱ��id */
RELTMR_T g_ulDHCPCHourTimerId = 0;

/* �뼶��ʱ����Сʱ��ʱ�������Ͻڵ���� */
ULONG g_ulDHCPCTimerListNodeNum[DHCPC_LIST_TYPE_MAX] = {0};

/* ��ȡ�뼶���ĵ�ǰλ�� */
ULONG DHCPC_getCurTimerSecondPos()
{
    return g_ulDHCPCTimerSecondPos;
}

/* ʹ�뼶���ĵ�ǰλ�ü�1 */
ULONG DHCPC_incCurTimerSecondPos()
{
    g_ulDHCPCTimerSecondPos++;
    g_ulDHCPCTimerSecondPos = g_ulDHCPCTimerSecondPos%DHCPC_SECOND_TIMER_LEN;
    return g_ulDHCPCTimerSecondPos;
}

/* ��ȡСʱ���ĵ�ǰλ�� */
ULONG DHCPC_getCurTimerHourPos()
{
    return g_ulDHCPCTimerHourPos;
}

/* ʹСʱ���ĵ�ǰλ�ü�1 */
ULONG DHCPC_incCurTimerHourPos()
{
    g_ulDHCPCTimerHourPos++;
    g_ulDHCPCTimerHourPos = g_ulDHCPCTimerHourPos%DHCPC_HOUR_TIMER_LEN;
    return g_ulDHCPCTimerHourPos;
}

/* ��ȡСʱ���ĳ�ʱ���� */
ULONG DHCPC_getCurTimerHourSec()
{
    return g_ulDHCPCTimerHourSecNum;
}

/* ʹСʱ���ĳ�ʱ������1 */
VOID DHCPC_incCurTimerHourSec()
{
    g_ulDHCPCTimerHourSecNum++;
    g_ulDHCPCTimerHourSecNum = g_ulDHCPCTimerHourSecNum%DHCPC_SECONDS_PER_HOUR;
    return;
}
ULONG DHCPC_InitTimerList()
{
    ULONG ulMemSize;

    /* Ϊʱ��ڵ��ϣ�����ͷ�����ڴ沢��ʼ�� */
    ulMemSize= sizeof(DHCPC_TIMER_LIST_HEAD_S) * DHCPC_CTRLBLK_HASH_TABLE_SIZE;
    g_pstDHCPTimerHashList = (DHCPC_TIMER_LIST_HEAD_S *)DHCP_Malloc(DHCPC_HANDLE, ulMemSize);
    if (NULL == g_pstDHCPTimerHashList)
    {
        VOS_Assert(0);
        return VOS_ERR;
    }
    DHCP_MemZero(g_pstDHCPTimerHashList, ulMemSize);

    /* Ϊʱ��ڵ��뼶�����ͷ�����ڴ沢��ʼ�� */
    /* ulMemSize= sizeof(DHCPC_TIMER_NODE_S) * DHCPC_SECOND_TIMER_LEN;
    g_pstDHCPTimerSecondList = (DHCPC_TIMER_NODE_S *)DHCP_Malloc(DHCPC_HANDLE, ulMemSize);
    if (NULL == g_pstDHCPTimerSecondList)
    {
        DHCP_Free(DHCPC_HANDLE, g_pstDHCPTimerHashList);
        VOS_Assert(0);
        return VOS_ERR;
    } */
    DHCP_MemZero(g_pstDHCPTimerSecondList, ulMemSize);

    /* Ϊʱ��ڵ�Сʱ�����ͷ�����ڴ沢��ʼ�� */
    /* ulMemSize= sizeof(DHCPC_TIMER_NODE_S) * DHCPC_HOUR_TIMER_LEN;
    g_pstDHCPTimerHourList = (DHCPC_TIMER_NODE_S *)DHCP_Malloc(DHCPC_HANDLE, ulMemSize);
    if (NULL == g_pstDHCPTimerHourList)
    {
        DHCP_Free(DHCPC_HANDLE, g_pstDHCPTimerHashList);
        DHCP_Free(DHCPC_HANDLE, g_pstDHCPTimerSecondList);
        VOS_Assert(0);
        return VOS_ERR;
    } */
    DHCP_MemZero(g_pstDHCPTimerHourList, ulMemSize);

    return VOS_OK;
}

ULONG DHCPC_IsTimNodeExist(UCHAR ucIpType, ULONG ulTeidc)
{
    ULONG ulHashKey = DHCPC_GET_HASHKEY(ulTeidc);
    DHCPC_TIMER_NODE_S *pstCurrNode = NULL;

    pstCurrNode = g_pstDHCPTimerHashList[ulHashKey].pstNextNode;

    while(NULL != pstCurrNode)
    {
        if ((pstCurrNode->ulTeidc == ulTeidc)
            && (pstCurrNode->ucIpType == ucIpType))
        {
            return VOS_OK;
        }

        pstCurrNode = pstCurrNode->pstHashNextNode;
    }

    return VOS_ERR;
}



VOID DHCPC_CreateDhcpcTimerNode(DHCPC_TIMER_NODE_S **ppstDHCPTimerNode)
{
    DHCPC_TIMER_NODE_S *pstDHCPTimerNode = NULL;

    if (NULL == ppstDHCPTimerNode)
    {
        VOS_Assert(0);
        return;
    }

    pstDHCPTimerNode = (DHCPC_TIMER_NODE_S *)DHCP_Malloc(DHCPC_HANDLE, sizeof(DHCPC_TIMER_NODE_S));
    if (NULL == pstDHCPTimerNode)
    {
        VOS_Assert(0);
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_MALLOC_ERR_FOR_TIMER_NODE);
        *ppstDHCPTimerNode = NULL;
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "malloc Timer Node memory failed!");
        return;
    }
    DHCP_MemZero(pstDHCPTimerNode, sizeof(DHCPC_TIMER_NODE_S));

    *ppstDHCPTimerNode = pstDHCPTimerNode;

    return;
}


VOID DHCPC_putTimerNodeToHashList(DHCPC_TIMER_LIST_HEAD_S *pstHashList,
                                    DHCPC_TIMER_NODE_S *pstTimerNode)
{
    ULONG ulHashKey = DHCPC_GET_HASHKEY(pstTimerNode->ulTeidc);

    pstTimerNode->pstHashNextNode = pstHashList[ulHashKey].pstNextNode;

    pstHashList[ulHashKey].pstNextNode = pstTimerNode;

    return;
}


VOID DHCPC_putTimerNodeToTimerList(DHCPC_TIMER_NODE_S *pstTimerList,
                                    DHCPC_TIMER_NODE_S *pstTimerNode, ULONG ulTimerPos)
{
    DHCPC_TIMER_NODE_S *pstHeadNode = &(pstTimerList[ulTimerPos]);

    /* �嵽�׽ڵ�λ�� */
    pstTimerNode->pstPrevNode = pstHeadNode;
    pstTimerNode->pstNextNode = pstHeadNode->pstNextNode;

    if (NULL != pstHeadNode->pstNextNode)
    {
        pstHeadNode->pstNextNode->pstPrevNode = pstTimerNode;
    }

    pstHeadNode->pstNextNode = pstTimerNode;

    return;
}
VOID DHCPC_putIntoTimerList(DHCPC_TIMER_NODE_S *pstTimerNode, ULONG ulTimerInterval)
{
    ULONG ulTempSeconds = 0;
    ULONG ulInsTimerPos = 0;
    ULONG ulTempHours = 0;

    /* ����Сʱ��ʱ�� */
    if (ulTimerInterval >= DHCPC_SECONDS_PER_HOUR)
    {
        /* ��Ҫ����Сʱ��ʱ���Ѿ���ȥ��ʱ�� */
        ulTempSeconds = (ulTimerInterval + DHCPC_getCurTimerHourSec());
        pstTimerNode->usSecondField = (USHORT)(ulTempSeconds % DHCPC_SECONDS_PER_HOUR);

        ulTempHours = ulTempSeconds / DHCPC_SECONDS_PER_HOUR;
        pstTimerNode->ulCircleNum = ulTempHours / DHCPC_HOUR_TIMER_LEN; /* ��Լ��������0��ʾ����һ���� */
        pstTimerNode->ucListType = DHCPC_LIST_TYPE_HOUR;
        ulInsTimerPos = DHCPC_GET_HOUR_INSPOS(ulTempHours);
        DHCPC_putTimerNodeToTimerList(g_pstDHCPTimerHourList, pstTimerNode, ulInsTimerPos);
        g_ulDHCPCTimerListNodeNum[DHCPC_LIST_TYPE_HOUR]++;

        DHCPC_DebugPrint(PTM_LOG_DEBUG, "put Timer Node into Hour-Timer List "
                        "ulTeidc=%08x, ulTimerInterval=%u, ulSecondField=%u, "
                        "ulCurHourPos=%u, ulInsHourPos=%u!",
                        pstTimerNode->ulTeidc, ulTimerInterval, pstTimerNode->usSecondField,
                        DHCPC_getCurTimerHourPos(), ulInsTimerPos);
        return;
    }

    /* �����뼶��ʱ�� */
    pstTimerNode->usSecondField = 0;
    pstTimerNode->ucListType = DHCPC_LIST_TYPE_SECOND;
    ulInsTimerPos = DHCPC_GET_SECOND_INSPOS(ulTimerInterval * DHCPC_MILLSECONDS_PER_SECOND / DHCPC_SECOND_TIMER_INTERVAL);
    DHCPC_putTimerNodeToTimerList(g_pstDHCPTimerSecondList, pstTimerNode, ulInsTimerPos);
    g_ulDHCPCTimerListNodeNum[DHCPC_LIST_TYPE_SECOND]++;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "put Timer Node into Second-Timer List "
                    "ulTeidc=%08x, ulTimerInterval=%u, ulSecondField=%u, "
                    "ulCurSecPos=%u, ulInsSecPos=%u!",
                    pstTimerNode->ulTeidc, ulTimerInterval, 0,
                    DHCPC_getCurTimerSecondPos(), ulInsTimerPos);

    return;
}


ULONG DHCPC_StartTimer(UCHAR ucIpType, ULONG ulTeidc, UCHAR ucEvent, ULONG ulTimerInterval, DHCPC_TIMER_CALLBACK pCallBackFun)
{
    DHCPC_TIMER_NODE_S *pstTimerNode = NULL;

    /* �Ϸ���У�� */
    if ((0 == ulTeidc) || (0 == ulTimerInterval))
    {
        VOS_Assert(0 != ulTeidc);
        VOS_Assert(0 != ulTimerInterval);
        return VOS_ERR;
    }

    /* �����ڴ棬����ʱ������ڵ� */
    DHCPC_CreateDhcpcTimerNode(&pstTimerNode);
    if (NULL == pstTimerNode)
    {
        return VOS_ERR;
    }

    /* Ϊʱ������ڵ㸳ֵ */
    pstTimerNode->ulTeidc = ulTeidc;
    pstTimerNode->ucIpType = ucIpType;
    pstTimerNode->ucEvent = ucEvent;
    pstTimerNode->pCallBackFun = pCallBackFun;

    /* �����ϣ�� */
    DHCPC_putTimerNodeToHashList(g_pstDHCPTimerHashList, pstTimerNode);

    /* ���붨ʱ�� */
    DHCPC_putIntoTimerList(pstTimerNode, ulTimerInterval);

    return VOS_OK;
}
ULONG DHCPC_DeleteNodeFromHashList(UCHAR ucIpType, ULONG ulTeidc, UCHAR ucEvent, DHCPC_TIMER_NODE_S **ppstTimerNode)
{
    ULONG ulHashKey = DHCPC_GET_HASHKEY(ulTeidc);
    DHCPC_TIMER_NODE_S *pstPrevNode = NULL;
    DHCPC_TIMER_NODE_S *pstCurrNode = NULL;

    *ppstTimerNode = NULL;

    pstPrevNode = g_pstDHCPTimerHashList[ulHashKey].pstNextNode;
    pstCurrNode = pstPrevNode;

    /* ���һ���ڵ㶼û�У���Ȼ�ǲ���ʧ�� */
    if (NULL == pstPrevNode)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_NO_NODE_IN_HASH_LIST);
        return VOS_ERR;
    }

    while(NULL != pstCurrNode)
    {
        if ((pstCurrNode->ulTeidc == ulTeidc)
            && (pstCurrNode->ucIpType == ucIpType)
            && (pstCurrNode->ucEvent == ucEvent))
        {
            /* �ӹ�ϣ����ժ�� */
            /* ��ͷ������� */
            if (pstPrevNode == pstCurrNode)
            {
                g_pstDHCPTimerHashList[ulHashKey].pstNextNode = pstCurrNode->pstHashNextNode;
            }
            else
            {
                pstPrevNode->pstHashNextNode = pstCurrNode->pstHashNextNode;
            }

            pstCurrNode->pstHashNextNode = NULL;
            *ppstTimerNode = pstCurrNode;
            return VOS_OK;
        }

        /* �ı�ѭ������ */
        pstPrevNode = pstCurrNode;
        pstCurrNode = pstCurrNode->pstHashNextNode;
    }

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_NODE_NOT_IN_HASH_LIST);
    return VOS_ERR;
}


ULONG DHCPC_CutTimerNodeFromTimerList(DHCPC_TIMER_NODE_S *pstTimerNode)
{
    if (NULL == pstTimerNode)
    {
        VOS_ASSERT(0);
        return VOS_ERR;
    }

    /* ������ͷ��㣬�����ͷ��㣬�����쳣 */
    if (NULL == pstTimerNode->pstPrevNode)
    {
        VOS_Assert(0);
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_FIND_NODE_CANNOT_BE_HEAD);
        return VOS_ERR;
    }

    pstTimerNode->pstPrevNode->pstNextNode = pstTimerNode->pstNextNode;

    if (NULL != pstTimerNode->pstNextNode)
    {
        pstTimerNode->pstNextNode->pstPrevNode = pstTimerNode->pstPrevNode;
    }

    g_ulDHCPCTimerListNodeNum[pstTimerNode->ucListType]--;

    pstTimerNode->pstPrevNode = NULL;
    pstTimerNode->pstNextNode = NULL;

#if 0
    DHCP_Free(DHCPC_HANDLE, pstTimerNode);
#endif

    return VOS_OK;
}
ULONG DHCPC_StopTimer(UCHAR ucIpType, ULONG ulTeidc, UCHAR ucEvent)
{
    DHCPC_TIMER_NODE_S *pstTimerNode = NULL;

    /* �Ϸ���У�� */
    if (0 == ulTeidc)
    {
        VOS_Assert(0 != ulTeidc);
        return VOS_ERR;
    }

    /* ����ʱ��ڵ㣬����ʱ��ڵ��ϣ����ɾ�� */
    (VOID)DHCPC_DeleteNodeFromHashList(ucIpType, ulTeidc, ucEvent, &pstTimerNode);
    if (NULL == pstTimerNode)
    {
        return VOS_ERR;
    }

    /* ��ʱ�����ժ�����ﵽɾ����ʱ��Ŀ�� */
    (VOID)DHCPC_CutTimerNodeFromTimerList(pstTimerNode);

    pstTimerNode = NULL;

    return VOS_OK;
}
VOID DHCPC_HourListTimerOut(VOID *pvArg)
{
    ULONG ulCurIndex = 0;
    ULONG ulInsTimerPos = 0;
    DHCPC_TIMER_NODE_S *pstTempNode = NULL;
    DHCPC_TIMER_NODE_S *pstTimerNode = NULL;

    DHCPC_incCurTimerHourSec();

    if (0 < DHCPC_getCurTimerHourSec())
    {
        return;
    }

    /* ��Сʱ�ڵ�����ǰ������1������ȡֵ */
    ulCurIndex = DHCPC_incCurTimerHourPos();

    pstTimerNode = g_pstDHCPTimerHourList[ulCurIndex].pstNextNode;

    while (NULL != pstTimerNode)
    {
        /* ��һ���ڵ㲻��Ϊ�� */
        if (NULL == pstTimerNode->pstPrevNode)
        {
            VOS_Assert(0);
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SECONDNODE_CANNOT_BE_HEAD);
            break;
        }

        /* ��һ���ڵ����һ���ڵ�����Ǳ��ڵ� */
        if (pstTimerNode != pstTimerNode->pstPrevNode->pstNextNode)
        {
            VOS_Assert(0);
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SECONDLIST_LINK_ERROR);
            break;
        }

        /* ������һ�ڵ� */
        pstTempNode = pstTimerNode->pstNextNode;

        /* �Ѿ����ڵ���� */
        if (0 == pstTimerNode->ulCircleNum)
        {
            /* �ȴ�Сʱ������ժ�� */
            pstTimerNode->pstPrevNode->pstNextNode = pstTimerNode->pstNextNode;
            if (NULL != pstTimerNode->pstNextNode)
            {
                pstTimerNode->pstNextNode->pstPrevNode = pstTimerNode->pstPrevNode;
            }
            /* ���ڵ��Сʱ����ת�Ƶ��뼶���� */
            ulInsTimerPos = DHCPC_GET_SECOND_INSPOS(pstTimerNode->usSecondField * DHCPC_MILLSECONDS_PER_SECOND / DHCPC_SECOND_TIMER_INTERVAL);
            pstTimerNode->usSecondField = 0;   /* ת���뼶����󣬸�ֵ��Ҫ���� */
            pstTimerNode->ucListType = DHCPC_LIST_TYPE_SECOND;
            DHCPC_putTimerNodeToTimerList(g_pstDHCPTimerSecondList, pstTimerNode, ulInsTimerPos);
            g_ulDHCPCTimerListNodeNum[DHCPC_LIST_TYPE_HOUR]--;
            g_ulDHCPCTimerListNodeNum[DHCPC_LIST_TYPE_SECOND]++;
            pstTimerNode = pstTempNode;
            continue;
        }

        /* ��Լʱ������31���������·ݼ�1 */
        pstTimerNode->ulCircleNum--;

        pstTimerNode = pstTempNode;
    }

    return;
}
VOID DHCPC_DealBusAndDelFromTimerList(DHCPC_TIMER_NODE_S *pstTimerNode)
{
    ULONG ulTeidc = pstTimerNode->ulTeidc;
    UCHAR ucIpType = pstTimerNode->ucIpType;
    UCHAR ucEvent = pstTimerNode->ucEvent;
    DHCPC_TIMER_CALLBACK pCallBackFun = pstTimerNode->pCallBackFun;

    /* ��������ɾ���ýڵ� */
    (VOID)DHCPC_CutTimerNodeFromTimerList(pstTimerNode);

    /* ִ�лص�����������ҵ���� */
    (VOID)pCallBackFun(ucIpType, ulTeidc, ucEvent);

    return;
}


ULONG DHCPC_DeleteNodeFromHashListByNode(DHCPC_TIMER_NODE_S *pstTimerNode, DHCPC_TIMER_NODE_S **ppstTimerNode)
{
    DHCPC_TIMER_NODE_S *pstPrevNode = NULL;
    DHCPC_TIMER_NODE_S *pstCurrNode = NULL;

    ULONG ulHashKey = DHCPC_GET_HASHKEY(pstTimerNode->ulTeidc);

    *ppstTimerNode = NULL;

    pstPrevNode = g_pstDHCPTimerHashList[ulHashKey].pstNextNode;
    pstCurrNode = pstPrevNode;

    /* ���һ���ڵ㶼û�У���Ȼ�ǲ���ʧ�� */
    if (NULL == pstPrevNode)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_NO_NODE_IN_HASH_LIST);
        return VOS_ERR;
    }

    while(NULL != pstCurrNode)
    {
        if (pstCurrNode == pstTimerNode)
        {
            /* �ӹ�ϣ����ժ�� */
            /* ��ͷ������� */
            if (pstPrevNode == pstCurrNode)
            {
                g_pstDHCPTimerHashList[ulHashKey].pstNextNode = pstCurrNode->pstHashNextNode;
            }
            else
            {
                pstPrevNode->pstHashNextNode = pstCurrNode->pstHashNextNode;
            }

            pstCurrNode->pstHashNextNode = NULL;
            *ppstTimerNode = pstCurrNode;
            return VOS_OK;
        }

        /* �ı�ѭ������ */
        pstPrevNode = pstCurrNode;
        pstCurrNode = pstCurrNode->pstHashNextNode;
    }

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_NODE_NOT_IN_HASH_LIST);
    return VOS_ERR;
}


VOID DHCPC_ProcSecondListTimerOut()
{
    ULONG ulCurIndex = 0;
    DHCPC_TIMER_NODE_S *pstTempNode = NULL;
    DHCPC_TIMER_NODE_S *pstTimerNode = NULL;
    DHCPC_TIMER_NODE_S *pstHashNode = NULL;

    /* ���뼶�ڵ�����ǰ������1������ȡֵ */
    ulCurIndex = DHCPC_incCurTimerSecondPos();

    pstTimerNode = g_pstDHCPTimerSecondList[ulCurIndex].pstNextNode;

    while (NULL != pstTimerNode)
    {
        /* ��һ���ڵ㲻��Ϊ�� */
        if (NULL == pstTimerNode->pstPrevNode)
        {
            VOS_Assert(0);
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_HOURNODE_CANNOT_BE_HEAD);
            break;
        }

        /* ��һ���ڵ����һ���ڵ�����Ǳ��ڵ� */
        if (pstTimerNode != pstTimerNode->pstPrevNode->pstNextNode)
        {
            VOS_Assert(0);
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_HOURLIST_LINK_ERROR);
            break;
        }

        /* �뼶��ʱ����ʱ�䲻Ϊ0ʱ��˵���������е����⣬������¼ */
        if (0 != pstTimerNode->usSecondField)
        {
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SECOND_FIELD_VALUE_ERROR);
        }

        /* ������һ�ڵ� */
        pstTempNode = pstTimerNode->pstNextNode;

        pstHashNode = NULL;
        /* �ӹ�ϣ������ɾ�� */
        (VOID)DHCPC_DeleteNodeFromHashListByNode(pstTimerNode, &pstHashNode);
        if (NULL == pstHashNode)
        {
            VOS_Assert(0);
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_TIMER_UP_FIND_HASH_ERROR);
        }

        /* ����ҵ���� */
        DHCPC_DealBusAndDelFromTimerList(pstTimerNode);
        pstTimerNode = pstTempNode;
    }

    return;
}
VOID DHCPC_SecondListTimerOut(VOID *pvArg)
{

    /* �����뼶���� */
    DHCPC_ProcSecondListTimerOut();

    return;
}


