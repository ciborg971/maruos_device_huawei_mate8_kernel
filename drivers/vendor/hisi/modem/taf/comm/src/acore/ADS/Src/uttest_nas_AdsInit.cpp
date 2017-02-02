#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_nas_AdsInit.h"

//�����������ã����������ùؼ���ʱ��Ҫ��ǰ׺ testing::
using namespace testing;


//˵��������������gtest+�������׺Ͳ����������ֲ�����Ϊ��
//      ������ú�gtest��ͬ�Ĺؼ��֣����ⲻ��Ҫ���鷳
//      gtest�ṩ EXPECT �� ASSERT ����,���庬����Կ���Ƭ�����׺궼��һһ��Ӧ�ģ�������EXPECTΪ��

//1���ȶԲ������� EXPECT_TRUE��EXPECT_FALSE/ASSERT_TRUE
//2���Ƚ����� EXPECT_EQ EXPECT_NE
//3���Ƚ��ַ��� EXPECT_STREQ
//4������ʧ�������Ϣ ADD_FAILUREd
//5�����óɹ���ʧ�� SUCCEED FAIL
//6���Զ����ʽ EXPECT_PRED_FORMAT3
//7�����������������TRUE EXPECT_PRED1
//8�������ͱȽ� EXPECT_FLOAT_EQ EXPECT_PRED_FORMAT2 ASSERT_PRED_FORMAT2
//9�����ͼ�� StaticAssertTypeEq
//10������3�ֲ��Լ����¼�
//11����ȡ������������ test_case_name()
//12���Ƚ��쳣 EXPECT_THROW
//13���ṹ�����ͱȽ�ASSERT_SAME_DATA ASSERT_SAME_MEMORY

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define TTF_L1_CACHE_SHIFT              (5)
#define TTF_L1_CACHE_BYTES              (1 << TTF_L1_CACHE_SHIFT)
#define TTF_SMP_CACHE_BYTES             (TTF_L1_CACHE_BYTES)
#define TTF_DATA_ALIGN(X)               (((X) + (TTF_SMP_CACHE_BYTES - 1)) & \
                                            ~(TTF_SMP_CACHE_BYTES - 1))



unsigned char *UT_skb_tail_pointer(const struct sk_buff *skb)
{
    return skb->tail;
}


void UT_skb_insert(struct sk_buff *newsk,
                      struct sk_buff *prev, struct sk_buff *next,
                      struct sk_buff_head *list)
{
    newsk->next = next;
    newsk->prev = prev;
    next->prev  = prev->next = newsk;
    list->qlen++;
}

void UT_skb_queue_before(struct sk_buff_head *list,
                                struct sk_buff *next,
                                struct sk_buff *newsk)
{
    UT_skb_insert(newsk, next->prev, next, list);
}

void UT_skb_queue_tail(struct sk_buff_head *list,
                            struct sk_buff *newsk)
{
    UT_skb_queue_before(list, (struct sk_buff *)list, newsk);
}

void UT_skb_unlink(struct sk_buff *skb, struct sk_buff_head *list)
{
    struct sk_buff *next, *prev;

    list->qlen--;
    next        = skb->next;
    prev        = skb->prev;
    skb->next  = skb->prev = NULL;
    next->prev = prev;
    prev->next = next;
}

struct sk_buff *UT_skb_peek(struct sk_buff_head *list_)
{
    struct sk_buff *list = ((struct sk_buff *)list_)->next;
    if (list == (struct sk_buff *)list_)
        list = NULL;
    return list;
}

void UT_kfree_skb(struct sk_buff *skb)
{
    if (NULL == skb)
    {
        return;
    }

    if (MEM_TYPE_SYS_DEFINED == skb->private_mem.enType)
    {
         free(skb->head);
    }
    else if(MEM_TYPE_USER_DEFINED == skb->private_mem.enType)
    {
        ;
    }

    free(skb);
    skb = NULL;
}

void UT_skb_reserve_debug(unsigned short usFileID, unsigned short usLineNum,
                               struct sk_buff *skb, int len)
{
    skb->data += len;
    skb->tail += len;
}

struct sk_buff *UT_skb_peek_tail(struct sk_buff_head *list_)
{
    struct sk_buff *list = ((struct sk_buff *)list_)->prev;
    if (list == (struct sk_buff *)list_)
        list = NULL;
    return list;
}
struct sk_buff *UT_skb_dequeue_tail(struct sk_buff_head *list)
{
    struct sk_buff *skb = UT_skb_peek_tail(list);
    if (skb)
        UT_skb_unlink(skb, list);
    return skb;
}


void UT_copy_skb_header(struct sk_buff *st_new, const struct sk_buff *old)
{
        st_new->dev        = old->dev;
        st_new->transport_header   = old->transport_header;
        st_new->network_header = old->network_header;
        st_new->mac_header     = old->mac_header;
#ifdef CONFIG_XFRM
        st_new->sp         = secpath_get(old->sp);
#endif
        memcpy(st_new->cb, old->cb, sizeof(old->cb));
        st_new->local_df       = old->local_df;
        st_new->pkt_type       = old->pkt_type;
        st_new->ip_summed      = old->ip_summed;
        st_new->priority       = old->priority;
#if defined(CONFIG_IP_VS) || defined(CONFIG_IP_VS_MODULE)
        st_new->ipvs_property  = old->ipvs_property;
#endif
        st_new->protocol       = old->protocol;
#if defined(CONFIG_NETFILTER_XT_TARGET_TRACE) || \
        defined(CONFIG_NETFILTER_XT_TARGET_TRACE_MODULE)
        st_new->nf_trace       = old->nf_trace;
#endif
#ifdef CONFIG_NET_SCHED
        st_new->tc_index       = old->tc_index;
#ifdef CONFIG_NET_CLS_ACT
        st_new->tc_verd        = old->tc_verd;
#endif
#endif
        /* HI_MODIFY begin */
        st_new->private_mem.enType = old->private_mem.enType;
        st_new->private_mem.pMem = old->private_mem.pMem;
        st_new->private_mem.usApp = old->private_mem.usApp;

}

IMM_MEM_STRU *UT_IMM_MemAlloc_Debug(unsigned short usFileID, unsigned short usLineNum,
                        unsigned char ucPoolId, unsigned short usLen)
{
	IMM_MEM_STRU *pstImmMem;

    if (usLen > 0x7ffdefff)
    {
        return NULL;
    }

	pstImmMem = (IMM_MEM_STRU *)malloc(sizeof(IMM_MEM_STRU));

	pstImmMem->pstMemBlk = (unsigned char *)malloc(usLen);

	return pstImmMem;
}

IMM_ZC_STRU *UT_IMM_ZcStaticAlloc_Debug(unsigned short usFileID, unsigned short usLineNum, unsigned int ulLen)
{

#if (FEATURE_OFF == FEATURE_SKB_EXP)
    IMM_ZC_STRU    *pstImmZc;
    unsigned char  *pucData;
    unsigned int    ulAllignlen;

    ulAllignlen = ulLen;

    pstImmZc = (IMM_ZC_STRU*)malloc(sizeof(IMM_ZC_STRU));
    if(VOS_NULL_PTR == pstImmZc)
    {
        return VOS_NULL_PTR;
    }
    pucData = (unsigned char*)malloc(((ulLen +31)&(~31)) + 64  +288 );
    if(VOS_NULL_PTR == pucData)
    {
        free(pstImmZc);
        return VOS_NULL_PTR;
    }

    memset(pstImmZc, 0x0, sizeof(IMM_ZC_STRU));

    pstImmZc->head               = pucData;
    pstImmZc->len                = ulLen;
    pstImmZc->data               = pucData + 64;
    pstImmZc->tail               = pstImmZc->data;
    ulLen                       = (ulAllignlen +31)&(~31);
    pstImmZc->end                = pstImmZc->data + ulLen;
    pstImmZc->private_mem.enType = MEM_TYPE_SYS_DEFINED;
    pstImmZc->private_mem.pMem   = (void*)pstImmZc;
    return pstImmZc;

#else

    IMM_ZC_STRU    *pstImmZc;
    unsigned char * pucData;
    IMM_MEM_STRU * pstImmMem;


    pstImmZc = (IMM_ZC_STRU*)malloc(sizeof(IMM_ZC_STRU));
    if(VOS_NULL_PTR == pstImmZc)
    {
        return VOS_NULL_PTR;
    }

    pstImmMem = UT_IMM_MemAlloc_Debug(usFileID,usLineNum,IMM_MEM_POOL_ID_SHARE
,ulLen + 64 + 14 +288);

    if(VOS_NULL_PTR == pstImmMem)
    {
        free(pstImmZc);
        return VOS_NULL_PTR;
    }

    pucData = pstImmMem->pstMemBlk;
    memset(pstImmZc, 0x0, sizeof(IMM_ZC_STRU));

    pstImmZc->head               = pucData;
    pstImmZc->data               = pucData + 64 + 14;
    pstImmZc->len                = ulLen;
    pstImmZc->tail               = pucData + ulLen;
    pstImmZc->end                = pstImmZc->tail;
    pstImmZc->private_mem.enType = MEM_TYPE_USER_DEFINED;
    pstImmZc->private_mem.pMem   = (void*)pstImmMem;
    return pstImmZc;
#endif
}


IMM_ZC_STRU * UT_IMM_ZcDataTransformImmZc_Debug(unsigned short usFileID,
            unsigned short usLineNum,
            const unsigned char *pucData,
            unsigned long ulLen,
            const void *pstTtfMem)
{
    IMM_ZC_STRU                        *pstZc;

    if (ulLen > 0x7ffdefff)
    {
        return NULL;
    }
    pstZc = (IMM_ZC_STRU *)malloc(ulLen);

    if(VOS_NULL_PTR == pstZc)
    {
        return VOS_NULL_PTR;
    }

    pstZc->len = ulLen;

    return pstZc;
}


unsigned char *UT_IMM_ZcPut_Debug(unsigned short usFileID, unsigned short usLineNum,
struct sk_buff *skb, unsigned int len)
{
    unsigned char *tmp = UT_skb_tail_pointer(skb);

    skb->tail += len;
    skb->len  += len;

    return tmp;
}


unsigned char *UT_IMM_ZcPull_Debug(unsigned short usFileID, unsigned short usLineNum,
struct sk_buff *skb, unsigned int len)
{
    unsigned char *tmp = UT_skb_tail_pointer(skb);

    skb->data += len;
    skb->len  += len;

    return tmp;
}


void UT_IMM_ZcQueueHeadInit_Debug(unsigned short usFileID, unsigned short
usLineNum, struct sk_buff_head *list)
{
    list->prev = list->next = (struct sk_buff *)list;
    list->qlen = 0;

    return;
}


unsigned int UT_IMM_ZcQueueLen_Debug(unsigned short usFileID, unsigned short usLineNum,
    struct sk_buff_head *list_)
{
    return list_->qlen;
}

void UT_IMM_ZcQueueTail_Debug(unsigned short usFileID, unsigned short usLineNum,
struct sk_buff_head *list, struct sk_buff *newsk)
{
    UT_skb_queue_tail(list, newsk);
}


struct sk_buff * UT_IMM_ZcDequeueHead_Debug(unsigned short usFileID, unsigned
short usLineNum, struct sk_buff_head *list)
{
    struct sk_buff *skb = UT_skb_peek(list);
    if (skb)
        UT_skb_unlink(skb, list);
    return skb;
}

void UT_IMM_ZcHeadFree(struct sk_buff *skb)
{
    skb->head = VOS_NULL_PTR;
    UT_kfree_skb(skb);
}

IMM_MEM_STRU *UT_IMM_ZcMapToImmMem_Debug(unsigned short usFileID,
            unsigned short usLineNum, IMM_ZC_STRU *pstImmZc)
{
    if (pstImmZc->len > 0x7ffdefff)
    {
        return NULL;
    }
    return (IMM_MEM_STRU *)malloc(pstImmZc->len);
}


void UT_IMM_ZcReserve_Debug(unsigned short usFileID, unsigned short usLineNum,
struct sk_buff *skb, int len)
{
    skb->data += len;
    skb->tail += len;
}


IMM_ZC_STRU *UT_IMM_ZcStaticCopy_Debug(unsigned short usFileID, unsigned short
usLineNum, struct sk_buff *skb)
{

    IMM_ZC_STRU    *pstImmZc;
    int             headerlen;
    unsigned int    size;
    IMM_MEM_STRU   *pstImmMem;
    unsigned char  *pucData;

    if(VOS_NULL_PTR == skb)
    {
       return VOS_NULL_PTR;
    }

    headerlen = skb->data - skb->head;

        /*
        Allocate the copy buffer
        */
    pstImmZc = (IMM_ZC_STRU*)malloc(sizeof(IMM_ZC_STRU));
    if(VOS_NULL_PTR == pstImmZc)
    {
       return VOS_NULL_PTR;
    }
    size = TTF_DATA_ALIGN((skb->end - skb->head));

    pstImmMem = UT_IMM_MemAlloc_Debug(0,0,IMM_MEM_POOL_ID_SHARE,(size + 264));

    if(VOS_NULL_PTR == pstImmMem)
    {
        free(pstImmZc);
        return VOS_NULL_PTR;
    }

    pucData = pstImmMem->pstMemBlk;


    memset(pstImmZc, 0x0, sizeof(IMM_ZC_STRU));

    pstImmZc->head     = pucData;
    pstImmZc->data     = pstImmZc->head;
    pstImmZc->tail     = pstImmZc->head;
    pstImmZc->end      = pstImmZc->head + size;


    IMM_ZcReserve(pstImmZc, headerlen);
    IMM_ZcPut(pstImmZc, skb->len);

    memcpy(pstImmZc->data, skb->data, skb->len);

    UT_copy_skb_header(pstImmZc, skb);


    pstImmZc->private_mem.enType    = MEM_TYPE_USER_DEFINED;
    pstImmZc->private_mem.usApp     = skb->private_mem.usApp;
    pstImmZc->private_mem.pMem      = (void*)pstImmMem;
    return pstImmZc;

}

struct sk_buff *UT_IMM_ZcDequeueTail_Debug(unsigned short usFileID, unsigned short usLineNum, struct sk_buff_head *list)
{
    struct sk_buff *result;

    result = UT_skb_dequeue_tail(list);

    return result;
}


unsigned int UT_phys_to_virt(unsigned int ulData)
{
    return ulData;
}

unsigned int UT_virt_to_phys(unsigned int ulData)
{
    return ulData;
}

void UT_IMM_STUB_INIT(void)
{
    MOCKER(kfree_skb)
        .defaults()
        .will(invoke(UT_kfree_skb));
    MOCKER(IMM_ZcStaticAlloc_Debug)
        .defaults()
        .will(invoke(UT_IMM_ZcStaticAlloc_Debug));
    MOCKER(IMM_ZcDataTransformImmZc_Debug)
        .defaults()
        .will(invoke(UT_IMM_ZcDataTransformImmZc_Debug));
    MOCKER(IMM_ZcPut_Debug)
        .defaults()
        .will(invoke(UT_IMM_ZcPut_Debug));
    MOCKER(IMM_ZcPull_Debug)
        .defaults()
        .will(invoke(UT_IMM_ZcPull_Debug));
    MOCKER(IMM_ZcQueueHeadInit_Debug)
        .defaults()
        .will(invoke(UT_IMM_ZcQueueHeadInit_Debug));
    MOCKER(IMM_ZcQueueLen_Debug)
        .defaults()
        .will(invoke(UT_IMM_ZcQueueLen_Debug));
    MOCKER(IMM_ZcQueueTail_Debug)
        .defaults()
        .will(invoke(UT_IMM_ZcQueueTail_Debug));
    MOCKER(IMM_ZcDequeueHead_Debug)
        .defaults()
        .will(invoke(UT_IMM_ZcDequeueHead_Debug));
    MOCKER(IMM_ZcHeadFree)
        .defaults()
        .will(invoke(UT_IMM_ZcHeadFree));
    MOCKER(IMM_ZcMapToImmMem_Debug)
        .defaults()
        .will(invoke(UT_IMM_ZcMapToImmMem_Debug));
    MOCKER(IMM_ZcReserve_Debug)
        .defaults()
        .will(invoke(UT_IMM_ZcReserve_Debug));
    MOCKER(IMM_ZcStaticCopy_Debug)
        .defaults()
        .will(invoke(UT_IMM_ZcStaticCopy_Debug));
    MOCKER(IMM_ZcDequeueTail_Debug)
        .defaults()
        .will(invoke(UT_IMM_ZcDequeueTail_Debug));

    MOCKER(V_StartRelTimer)
        .defaults()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(NV_ReadEx)
        .defaults()
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(VOS_GetSlice)
        .defaults()
        .will(returnValue((VOS_UINT32)0xffffffff));
    MOCKER(phys_to_virt)
        .defaults()
        .will(invoke(UT_phys_to_virt));
    MOCKER(virt_to_phys)
        .defaults()
        .will(invoke(UT_virt_to_phys));
}


#ifdef __cplusplus
#if __cplusplus
        }
#endif
#endif


class Test_ADS_UL_FidInit: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
		UT_IMM_STUB_INIT();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_ADS_UL_FidInit,Test_ADS_UL_FidInit_001)
{
    VOS_UINT32                          ulRslt;

    /* ����PID��ʼ�� */
    MOCKER(VOS_RegisterPIDInfo)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)ACPU_PID_ADS_UL), eq((Init_Fun_Type)ADS_UL_PidInit), eq((Msg_Fun_Type)ADS_UL_ProcMsg))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(VOS_RegisterMsgTaskEntry)
        .expects(exactly(1))
        .with(eq(ACPU_FID_ADS_UL), eq((VOS_VOIDFUNCPTR)ADS_UL_FidTask))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(VOS_RegisterTaskPrio)
        .expects(exactly(1))
        .with(eq(ACPU_FID_ADS_UL), eq((VOS_UINT32)ADS_UL_TASK_PRIORITY))
        .will(returnValue((VOS_UINT32)VOS_OK));


    ulRslt = ADS_UL_FidInit(VOS_IP_LOAD_CONFIG);

    EXPECT_EQ(VOS_OK, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
TEST_F(Test_ADS_UL_FidInit,Test_ADS_UL_FidInit_002)
{
    VOS_UINT32                          ulRslt;

    /* ����PID��ʼ�� */
    MOCKER(VOS_RegisterPIDInfo)
        .expects(exactly(1))
        .with(eq((VOS_UINT32)ACPU_PID_ADS_UL), eq((Init_Fun_Type)ADS_UL_PidInit), eq((Msg_Fun_Type)ADS_UL_ProcMsg))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    ulRslt = ADS_UL_FidInit(VOS_IP_LOAD_CONFIG);

    EXPECT_EQ(VOS_ERR, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
class Test_ADS_UL_PidInit: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
		UT_IMM_STUB_INIT();
        g_stAdsStats.stResetStatsinfo.ulULCreateBinarySemFailNum = 0;
        g_stAdsStats.stResetStatsinfo.ulDLCreateBinarySemFailNum = 0;

        MOCKER(V_StartRelTimer)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(NV_ReadEx)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

    }
    void TearDown()
    {
        g_stAdsStats.stResetStatsinfo.ulULCreateBinarySemFailNum = 0;
        g_stAdsStats.stResetStatsinfo.ulDLCreateBinarySemFailNum = 0;
    }
};


TEST_F(Test_ADS_UL_PidInit,Test_ADS_UL_PidInit_001)
{
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_DL_CTX_STRU                    *pAdsDlCtx;
    ADS_TIMER_CTX_STRU                 *pAdsTiCtx;
	ADS_STATS_INFO_CTX_STRU            *pAdsStatsInfoCtx;
    VOS_UINT32                          i;
    VOS_UINT32                          ulInstancLoop;

    ADS_UL_PidInit(VOS_IP_LOAD_CONFIG);

    for (ulInstancLoop = 0 ; ulInstancLoop < ADS_INSTANCE_MAX_NUM; ulInstancLoop++)
    {
        pAdsDlCtx        = ADS_GetDlCtx(ulInstancLoop);
        pAdsUlCtx		 = ADS_GetUlCtx(ulInstancLoop);
        pAdsTiCtx		 = ADS_GetTiCtx();
        pAdsStatsInfoCtx = ADS_GetStatsInfoCtx(ulInstancLoop);

        /* ��ʼ�����е���Ϣ */

        /* Ĭ���������������� */
        EXPECT_EQ(VOS_TRUE, pAdsUlCtx->ucModemSndPermitFlg);

#if(FEATURE_OFF == FEATURE_SKB_EXP)
        EXPECT_EQ(512, pAdsUlCtx->ulUlMaxQueueLength);
#endif

        /* Ĭ�ϴӵ�һ�����п�ʼ���� */
        EXPECT_EQ(0, pAdsUlCtx->ucAdsUlCurIndex);

        for (i = 0; i < ADS_RAB_ID_MAX + 1; i++)
        {
            EXPECT_EQ(VOS_NULL_PTR,         pAdsUlCtx->astAdsUlQueue[i].pstAdsUlLink);
            EXPECT_EQ(VOS_FALSE,            pAdsUlCtx->astAdsUlQueue[i].ucIsQueueValid);
            EXPECT_EQ(ADS_QCI_TYPE_BUTT, pAdsUlCtx->astAdsUlQueue[i].enPrio);
            EXPECT_EQ(0,                    pAdsUlCtx->astAdsUlQueue[i].usRecordNum);
            EXPECT_EQ(VOS_TRUE,             pAdsUlCtx->astAdsUlQueue[i].ucRabSndPermitFlg);
        }

        EXPECT_EQ(0, pAdsStatsInfoCtx->stULDataStats.ulULCurDataRate);
        EXPECT_EQ(0, pAdsStatsInfoCtx->stULDataStats.ulULPeriodSndBytes);
        EXPECT_EQ(0, pAdsStatsInfoCtx->stDLDataStats.ulDLCurDataRate);
        EXPECT_EQ(0, pAdsStatsInfoCtx->stDLDataStats.ulDLPeriodRcvBytes);

        /* ��ʼ�����е�RAB��Ϣ */
        for (i = 0; i < ADS_RAB_NUM_MAX; i++)
        {
            EXPECT_EQ(ADS_RAB_ID_INVALID, pAdsDlCtx->astAdsDlRabInfo[i].ucRabId);
            EXPECT_EQ(VOS_NULL_PTR, pAdsDlCtx->astAdsDlRabInfo[i].pRcvDlDataFunc);
        }

        /* ��ʱ����ʼ�������飺 */
        for (i = 0; i < ADS_MAX_TIMER_NUM; i++)
        {
            EXPECT_EQ(VOS_NULL_PTR, pAdsTiCtx[i].hTimer);
            EXPECT_EQ(ADS_TIMER_STATUS_STOP, pAdsTiCtx[i].enTimerStatus);
        }
    }

    EXPECT_EQ(ADS_INSTANCE_INDEX_0, g_stAdsCtx.ucAdsCurInstanceIndex);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
TEST_F(Test_ADS_UL_PidInit,Test_ADS_UL_PidInit_002)
{
    MOCKER(ADS_InitUlCtx)
        .expects(never());

    ADS_UL_PidInit(VOS_IP_BUTT);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_UL_PidInit,Test_ADS_UL_PidInit_003)
{
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_DL_CTX_STRU                    *pAdsDlCtx;
    ADS_TIMER_CTX_STRU                 *pAdsTiCtx;
	ADS_STATS_INFO_CTX_STRU            *pAdsStatsInfoCtx;
    VOS_UINT32                          i;
    VOS_UINT32                          ulInstancLoop;

    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue(NV_ID_NOT_EXIST));

    ADS_UL_PidInit(VOS_IP_LOAD_CONFIG);

    for (ulInstancLoop = 0 ; ulInstancLoop < ADS_INSTANCE_MAX_NUM; ulInstancLoop++)
    {
        pAdsDlCtx        = ADS_GetDlCtx(ulInstancLoop);
        pAdsUlCtx		 = ADS_GetUlCtx(ulInstancLoop);
        pAdsTiCtx		 = ADS_GetTiCtx();
        pAdsStatsInfoCtx = ADS_GetStatsInfoCtx(ulInstancLoop);

        /* ��ʼ�����е���Ϣ */

        /* Ĭ���������������� */
        EXPECT_EQ(VOS_TRUE, pAdsUlCtx->ucModemSndPermitFlg);

        /* Ĭ�ϴӵ�һ�����п�ʼ���� */
        EXPECT_EQ(0, pAdsUlCtx->ucAdsUlCurIndex);

#if(FEATURE_OFF == FEATURE_SKB_EXP)
        EXPECT_EQ(512, pAdsUlCtx->ulUlMaxQueueLength);
#endif

        for (i = 0; i < ADS_RAB_ID_MAX + 1; i++)
        {
            EXPECT_EQ(VOS_NULL_PTR,         pAdsUlCtx->astAdsUlQueue[i].pstAdsUlLink);
            EXPECT_EQ(VOS_FALSE,            pAdsUlCtx->astAdsUlQueue[i].ucIsQueueValid);
            EXPECT_EQ(ADS_QCI_TYPE_BUTT, pAdsUlCtx->astAdsUlQueue[i].enPrio);
            EXPECT_EQ(0,                    pAdsUlCtx->astAdsUlQueue[i].usRecordNum);
            EXPECT_EQ(VOS_TRUE,             pAdsUlCtx->astAdsUlQueue[i].ucRabSndPermitFlg);
        }

        EXPECT_EQ(0, pAdsStatsInfoCtx->stULDataStats.ulULCurDataRate);
        EXPECT_EQ(0, pAdsStatsInfoCtx->stULDataStats.ulULPeriodSndBytes);
        EXPECT_EQ(0, pAdsStatsInfoCtx->stDLDataStats.ulDLCurDataRate);
        EXPECT_EQ(0, pAdsStatsInfoCtx->stDLDataStats.ulDLPeriodRcvBytes);

        /* ��ʼ�����е�RAB��Ϣ */
        for (i = 0; i < ADS_RAB_NUM_MAX; i++)
        {
            EXPECT_EQ(ADS_RAB_ID_INVALID, pAdsDlCtx->astAdsDlRabInfo[i].ucRabId);
            EXPECT_EQ(VOS_NULL_PTR, pAdsDlCtx->astAdsDlRabInfo[i].pRcvDlDataFunc);
        }

        /* ��ʱ����ʼ�������飺 */
        for (i = 0; i < ADS_MAX_TIMER_NUM; i++)
        {
            EXPECT_EQ(VOS_NULL_PTR, pAdsTiCtx[i].hTimer);
            EXPECT_EQ(ADS_TIMER_STATUS_STOP, pAdsTiCtx[i].enTimerStatus);
        }
    }

    EXPECT_EQ(ADS_INSTANCE_INDEX_0, g_stAdsCtx.ucAdsCurInstanceIndex);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
TEST_F(Test_ADS_UL_PidInit,Test_ADS_UL_PidInit_004)
{
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_DL_CTX_STRU                    *pAdsDlCtx;
    ADS_TIMER_CTX_STRU                 *pAdsTiCtx;
    ADS_STATS_INFO_CTX_STRU            *pAdsStatsInfoCtx;
    VOS_UINT32                          i;
    VOS_UINT32                          ulInstancLoop;


    /* ׮���� */
    MOCKER(VOS_SmBCreate)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    ADS_UL_PidInit(VOS_IP_LOAD_CONFIG);

    for (ulInstancLoop = 0 ; ulInstancLoop < ADS_INSTANCE_MAX_NUM; ulInstancLoop++)
    {
        pAdsDlCtx        = ADS_GetDlCtx(ulInstancLoop);
        pAdsUlCtx		 = ADS_GetUlCtx(ulInstancLoop);
        pAdsTiCtx		 = ADS_GetTiCtx();
        pAdsStatsInfoCtx = ADS_GetStatsInfoCtx(ulInstancLoop);

        /* ��ʼ�����е���Ϣ */

        /* Ĭ���������������� */
        EXPECT_EQ(VOS_TRUE, pAdsUlCtx->ucModemSndPermitFlg);

#if(FEATURE_OFF == FEATURE_SKB_EXP)
        EXPECT_EQ(512, pAdsUlCtx->ulUlMaxQueueLength);
#endif

        /* Ĭ�ϴӵ�һ�����п�ʼ���� */
        EXPECT_EQ(0, pAdsUlCtx->ucAdsUlCurIndex);

        for (i = 0; i < ADS_RAB_ID_MAX + 1; i++)
        {
            EXPECT_EQ(VOS_NULL_PTR,         pAdsUlCtx->astAdsUlQueue[i].pstAdsUlLink);
            EXPECT_EQ(VOS_FALSE,            pAdsUlCtx->astAdsUlQueue[i].ucIsQueueValid);
            EXPECT_EQ(ADS_QCI_TYPE_BUTT, pAdsUlCtx->astAdsUlQueue[i].enPrio);
            EXPECT_EQ(0,                    pAdsUlCtx->astAdsUlQueue[i].usRecordNum);
            EXPECT_EQ(VOS_TRUE,             pAdsUlCtx->astAdsUlQueue[i].ucRabSndPermitFlg);
        }

        EXPECT_EQ(0, pAdsStatsInfoCtx->stULDataStats.ulULCurDataRate);
        EXPECT_EQ(0, pAdsStatsInfoCtx->stULDataStats.ulULPeriodSndBytes);
        EXPECT_EQ(0, pAdsStatsInfoCtx->stDLDataStats.ulDLCurDataRate);
        EXPECT_EQ(0, pAdsStatsInfoCtx->stDLDataStats.ulDLPeriodRcvBytes);

        /* ��ʼ�����е�RAB��Ϣ */
        for (i = 0; i < ADS_RAB_NUM_MAX; i++)
        {
            EXPECT_EQ(ADS_RAB_ID_INVALID, pAdsDlCtx->astAdsDlRabInfo[i].ucRabId);
            EXPECT_EQ(VOS_NULL_PTR, pAdsDlCtx->astAdsDlRabInfo[i].pRcvDlDataFunc);
        }

        /* ��ʱ����ʼ�������飺 */
        for (i = 0; i < ADS_MAX_TIMER_NUM; i++)
        {
            EXPECT_EQ(VOS_NULL_PTR, pAdsTiCtx[i].hTimer);
            EXPECT_EQ(ADS_TIMER_STATUS_STOP, pAdsTiCtx[i].enTimerStatus);
        }
    }

    EXPECT_EQ(ADS_INSTANCE_INDEX_0, g_stAdsCtx.ucAdsCurInstanceIndex);
    EXPECT_EQ(1, g_stAdsStats.stResetStatsinfo.ulULCreateBinarySemFailNum);
    EXPECT_EQ(0, g_stAdsStats.stResetStatsinfo.ulDLCreateBinarySemFailNum);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_UL_PidInit,Test_ADS_UL_PidInit_005)
{
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_DL_CTX_STRU                    *pAdsDlCtx;
    ADS_TIMER_CTX_STRU                 *pAdsTiCtx;
    ADS_STATS_INFO_CTX_STRU            *pAdsStatsInfoCtx;
    VOS_UINT32                          i;
    VOS_UINT32                          ulInstancLoop;


    /* ׮���� */
    MOCKER(VOS_SmBCreate)
        .expects(exactly(2))
        .will(returnObjectList((VOS_UINT32)VOS_OK, (VOS_UINT32)VOS_ERR));

    ADS_UL_PidInit(VOS_IP_LOAD_CONFIG);

    for (ulInstancLoop = 0 ; ulInstancLoop < ADS_INSTANCE_MAX_NUM; ulInstancLoop++)
    {
        pAdsDlCtx        = ADS_GetDlCtx(ulInstancLoop);
        pAdsUlCtx		 = ADS_GetUlCtx(ulInstancLoop);
        pAdsTiCtx		 = ADS_GetTiCtx();
        pAdsStatsInfoCtx = ADS_GetStatsInfoCtx(ulInstancLoop);

        /* ��ʼ�����е���Ϣ */

        /* Ĭ���������������� */
        EXPECT_EQ(VOS_TRUE, pAdsUlCtx->ucModemSndPermitFlg);

#if(FEATURE_OFF == FEATURE_SKB_EXP)
        EXPECT_EQ(512, pAdsUlCtx->ulUlMaxQueueLength);
#endif

        /* Ĭ�ϴӵ�һ�����п�ʼ���� */
        EXPECT_EQ(0, pAdsUlCtx->ucAdsUlCurIndex);

        for (i = 0; i < ADS_RAB_ID_MAX + 1; i++)
        {
            EXPECT_EQ(VOS_NULL_PTR,         pAdsUlCtx->astAdsUlQueue[i].pstAdsUlLink);
            EXPECT_EQ(VOS_FALSE,            pAdsUlCtx->astAdsUlQueue[i].ucIsQueueValid);
            EXPECT_EQ(ADS_QCI_TYPE_BUTT, pAdsUlCtx->astAdsUlQueue[i].enPrio);
            EXPECT_EQ(0,                    pAdsUlCtx->astAdsUlQueue[i].usRecordNum);
            EXPECT_EQ(VOS_TRUE,             pAdsUlCtx->astAdsUlQueue[i].ucRabSndPermitFlg);
        }

        EXPECT_EQ(0, pAdsStatsInfoCtx->stULDataStats.ulULCurDataRate);
        EXPECT_EQ(0, pAdsStatsInfoCtx->stULDataStats.ulULPeriodSndBytes);
        EXPECT_EQ(0, pAdsStatsInfoCtx->stDLDataStats.ulDLCurDataRate);
        EXPECT_EQ(0, pAdsStatsInfoCtx->stDLDataStats.ulDLPeriodRcvBytes);

        /* ��ʼ�����е�RAB��Ϣ */
        for (i = 0; i < ADS_RAB_NUM_MAX; i++)
        {
            EXPECT_EQ(ADS_RAB_ID_INVALID, pAdsDlCtx->astAdsDlRabInfo[i].ucRabId);
            EXPECT_EQ(VOS_NULL_PTR, pAdsDlCtx->astAdsDlRabInfo[i].pRcvDlDataFunc);
        }

        /* ��ʱ����ʼ�������飺 */
        for (i = 0; i < ADS_MAX_TIMER_NUM; i++)
        {
            EXPECT_EQ(VOS_NULL_PTR, pAdsTiCtx[i].hTimer);
            EXPECT_EQ(ADS_TIMER_STATUS_STOP, pAdsTiCtx[i].enTimerStatus);
        }
    }

    EXPECT_EQ(ADS_INSTANCE_INDEX_0, g_stAdsCtx.ucAdsCurInstanceIndex);
    EXPECT_EQ(0, g_stAdsStats.stResetStatsinfo.ulULCreateBinarySemFailNum);
    EXPECT_EQ(1, g_stAdsStats.stResetStatsinfo.ulDLCreateBinarySemFailNum);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_ADS_DL_PidInit: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
		UT_IMM_STUB_INIT();

        MOCKER(V_StartRelTimer)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(NV_ReadEx)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        ADS_InitCtx();
    }
    void TearDown()
    {

    }
};

#if (FEATURE_OFF == FEATURE_SKB_EXP)

TEST_F(Test_ADS_DL_PidInit,Test_ADS_DL_PidInit_001)
{

    VOS_UINT                            ulIpfAd0Num;
    VOS_UINT                            ulIpfAd1Num;

    ulIpfAd0Num = 63;
    ulIpfAd1Num = 63;

    MOCKER(mdrv_ipf_get_dlad_num)
        .stubs()
        .with(outBoundP((VOS_UINT *)&ulIpfAd0Num, sizeof(VOS_UINT)), outBoundP((VOS_UINT *)&ulIpfAd1Num, sizeof(VOS_UINT)))
        .will(returnValue(IPF_SUCCESS));

    MOCKER(mdrv_ipf_config_dlad)
        .expects(exactly(1))
        .with(eq(IPF_AD_0), eq(ulIpfAd0Num))
        .will(returnValue(IPF_SUCCESS));

    MOCKER(mdrv_ipf_config_dlad)
        .expects(exactly(1))
        .with(eq(IPF_AD_1), eq(ulIpfAd1Num))
        .will(returnValue(IPF_SUCCESS));

    ADS_DL_PidInit(VOS_IP_LOAD_CONFIG);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
#endif

TEST_F(Test_ADS_DL_PidInit,Test_ADS_DL_PidInit_002)
{
    MOCKER(ADS_InitDlCtx)
        .expects(never());

    ADS_DL_PidInit(VOS_IP_BUTT);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_ADS_DL_FidInit: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
		UT_IMM_STUB_INIT();

    }
    void TearDown()
    {

    }
};


TEST_F(Test_ADS_DL_FidInit,Test_ADS_DL_FidInit_001)
{
    VOS_UINT32                          ulRslt;

    /* ����PID��ʼ�� */
    MOCKER(VOS_RegisterPIDInfo)
        .expects(exactly(1))
        .with(any(), eq((Init_Fun_Type)ADS_DL_PidInit), eq((Msg_Fun_Type)ADS_DL_ProcMsg))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(VOS_RegisterMsgTaskEntry)
        .expects(exactly(1))
        .with(eq(ACPU_FID_ADS_DL), eq((VOS_VOIDFUNCPTR)ADS_DL_FidTask))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(VOS_RegisterMsgTaskPrio)
        .expects(exactly(1))
        .with(eq(ACPU_FID_ADS_DL), eq(VOS_PRIORITY_P6))
        .will(returnValue((VOS_UINT32)VOS_OK));

#if (FEATURE_OFF == FEATURE_SKB_EXP)
    MOCKER(mdrv_ipf_register_ops)
        .expects(exactly(1))
        .will(returnValue(IPF_SUCCESS));
#endif

    ulRslt = ADS_DL_FidInit(VOS_IP_LOAD_CONFIG);

    EXPECT_EQ(VOS_OK, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
TEST_F(Test_ADS_DL_FidInit,Test_ADS_DL_FidInit_002)
{
    VOS_UINT32                          ulRslt;

    /* ����PID��ʼ�� */
    MOCKER(VOS_RegisterPIDInfo)
        .expects(exactly(1))
        .with(any(), eq((Init_Fun_Type)ADS_DL_PidInit), eq((Msg_Fun_Type)ADS_DL_ProcMsg))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    ulRslt = ADS_DL_FidInit(VOS_IP_LOAD_CONFIG);

    EXPECT_EQ(VOS_ERR, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
#if (FEATURE_OFF == FEATURE_SKB_EXP)
TEST_F(Test_ADS_DL_FidInit,Test_ADS_DL_FidInit_003)
{
    VOS_UINT32                          ulRslt;

    /* ����PID��ʼ�� */
    MOCKER(VOS_RegisterPIDInfo)
        .expects(exactly(1))
        .with(any(), eq((Init_Fun_Type)ADS_DL_PidInit), eq((Msg_Fun_Type)ADS_DL_ProcMsg))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(VOS_RegisterMsgTaskEntry)
        .expects(exactly(1))
        .with(eq(ACPU_FID_ADS_DL), eq((VOS_VOIDFUNCPTR)ADS_DL_FidTask))
        .will(returnValue((VOS_UINT32)VOS_OK));


    MOCKER(mdrv_ipf_register_ops)
        .expects(exactly(1))
        .will(returnValue(IPF_ERROR));

    ulRslt = ADS_DL_FidInit(VOS_IP_LOAD_CONFIG);

    EXPECT_EQ(VOS_ERR, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
#endif
class Test_ADS_DL_FidTask: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
		UT_IMM_STUB_INIT();

        MOCKER(V_StartRelTimer)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(NV_ReadEx)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        ADS_InitCtx();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_ADS_DL_FidTask, Test_ADS_DL_FidTask_001)
{
    VOS_UINT32                          ulEvent;

    ulEvent = ADS_DL_EVENT_IPF_RD_INT;

    MOCKER(ADS_DL_ProcIpfResult).expects(exactly(1));

    MOCKER(VOS_GetCurrentTaskID)
        .stubs()
        .will(returnValue(0));

    MOCKER(VOS_CreateEvent)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(VOS_EventRead)
        .stubs()
        .with(any(), any(), any(), outBoundP((VOS_UINT32 *)&ulEvent, sizeof(ulEvent)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    ADS_DL_FidTask(0,0,0,0);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_FidTask, Test_ADS_DL_FidTask_002)
{
    VOS_UINT32                          ulEvent;

    ulEvent = ADS_DL_EVENT_IPF_ADQ_EMPTY_INT;

#if (FEATURE_OFF == FEATURE_SKB_EXP)
    MOCKER(ADS_DL_ProcIpfAdqEmtpyEvent).expects(exactly(1));
#endif

    MOCKER(VOS_GetCurrentTaskID)
        .stubs()
        .will(returnValue(0));

    MOCKER(VOS_CreateEvent)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(VOS_EventRead)
        .stubs()
        .with(any(), any(), any(), outBoundP((VOS_UINT32 *)&ulEvent, sizeof(ulEvent)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    ADS_DL_FidTask(0,0,0,0);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_ADS_DL_CCpuResetCallback: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
		UT_IMM_STUB_INIT();

        MOCKER(V_StartRelTimer)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(NV_ReadEx)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));
    }
    void TearDown()
    {
    }
};


TEST_F(Test_ADS_DL_CCpuResetCallback, Test_ADS_DL_CCpuResetCallback_001)
{
    VOS_UINT32                          ulRst;

    /* ������ʼ�� */

    /* ׮���� */

    MOCKER(VOS_EventWrite)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue((MsgCB *)VOS_NULL_PTR));

    /* �������� */

    /* ������ں��� */
    ulRst = ADS_DL_CCpuResetCallback(MDRV_RESET_CB_BEFORE, 0);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(VOS_ERROR, ulRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST_F(Test_ADS_DL_CCpuResetCallback, Test_ADS_DL_CCpuResetCallback_002)
{
    VOS_UINT32                          ulRst;

    /* ������ʼ�� */

    /* ׮���� */
    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    MOCKER(VOS_EventWrite)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    /* �������� */

    /* ������ں��� */
    ulRst = ADS_DL_CCpuResetCallback(MDRV_RESET_CB_BEFORE, 0);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(VOS_ERROR, ulRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST_F(Test_ADS_DL_CCpuResetCallback, Test_ADS_DL_CCpuResetCallback_003)
{
    VOS_UINT32                          ulRst;

    /* ������ʼ�� */

    /* ׮���� */
    MOCKER(VOS_SmP)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    MOCKER(VOS_EventWrite)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    /* �������� */

    /* ������ں��� */
    ulRst = ADS_DL_CCpuResetCallback(MDRV_RESET_CB_BEFORE, 0);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(VOS_ERROR, ulRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}



TEST_F(Test_ADS_DL_CCpuResetCallback, Test_ADS_DL_CCpuResetCallback_004)
{
    VOS_UINT32                          ulRst;

    /* ������ʼ�� */

    /* ׮���� */
    MOCKER(VOS_SmP)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(VOS_EventWrite)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    /* �������� */

    /* ������ں��� */
    ulRst = ADS_DL_CCpuResetCallback(MDRV_RESET_CB_BEFORE, 0);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(VOS_OK, ulRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST_F(Test_ADS_DL_CCpuResetCallback, Test_ADS_DL_CCpuResetCallback_005)
{
    VOS_UINT32                          ulRst;

    /* ������ʼ�� */

    /* ׮���� */
    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue((MsgCB *)VOS_NULL_PTR));

    /* �������� */

    /* ������ں��� */
    ulRst = ADS_DL_CCpuResetCallback(MDRV_RESET_CB_AFTER, 0);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(VOS_ERROR, ulRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}



TEST_F(Test_ADS_DL_CCpuResetCallback, Test_ADS_DL_CCpuResetCallback_006)
{
    VOS_UINT32                          ulRst;

    /* ������ʼ�� */

    /* ׮���� */
    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    /* �������� */

    /* ������ں��� */
    ulRst = ADS_DL_CCpuResetCallback(MDRV_RESET_CB_AFTER, 0);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(VOS_ERROR, ulRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}



TEST_F(Test_ADS_DL_CCpuResetCallback, Test_ADS_DL_CCpuResetCallback_007)
{
    VOS_UINT32                          ulRst;

    /* ������ʼ�� */

    /* ׮���� */

    /* �������� */

    /* ������ں��� */
    ulRst = ADS_DL_CCpuResetCallback(MDRV_RESET_CB_AFTER, 0);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(VOS_OK, ulRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST_F(Test_ADS_DL_CCpuResetCallback, Test_ADS_DL_CCpuResetCallback_008)
{
    VOS_UINT32                          ulRst;

    /* ������ʼ�� */

    /* ׮���� */

    /* �������� */

    /* ������ں��� */
    ulRst = ADS_DL_CCpuResetCallback(MDRV_RESET_CB_INVALID, 0);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(VOS_ERROR, ulRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


class Test_ADS_UL_CCpuResetCallback: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
		UT_IMM_STUB_INIT();
    }
    void TearDown()
    {
    }
};


TEST_F(Test_ADS_UL_CCpuResetCallback, Test_ADS_UL_CCpuResetCallback_001)
{
    VOS_UINT32                          ulRst;

    /* ������ʼ�� */

    /* ׮���� */
    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue((MsgCB *)VOS_NULL_PTR));

    /* �������� */

    /* ������ں��� */
    ulRst = ADS_UL_CCpuResetCallback(MDRV_RESET_CB_BEFORE, 0);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(VOS_ERROR, ulRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST_F(Test_ADS_UL_CCpuResetCallback, Test_ADS_UL_CCpuResetCallback_002)
{
    VOS_UINT32                          ulRst;

    /* ������ʼ�� */

    /* ׮���� */
    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    /* �������� */

    /* ������ں��� */
    ulRst = ADS_UL_CCpuResetCallback(MDRV_RESET_CB_BEFORE, 0);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(VOS_ERROR, ulRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST_F(Test_ADS_UL_CCpuResetCallback, Test_ADS_UL_CCpuResetCallback_003)
{
    VOS_UINT32                          ulRst;

    /* ������ʼ�� */

    /* ׮���� */
    MOCKER(VOS_SmP)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    /* �������� */

    /* ������ں��� */
    ulRst = ADS_UL_CCpuResetCallback(MDRV_RESET_CB_BEFORE, 0);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(VOS_ERROR, ulRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}



TEST_F(Test_ADS_UL_CCpuResetCallback, Test_ADS_UL_CCpuResetCallback_004)
{
    VOS_UINT32                          ulRst;

    /* ������ʼ�� */

    /* ׮���� */
    MOCKER(VOS_SmP)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    /* �������� */

    /* ������ں��� */
    ulRst = ADS_UL_CCpuResetCallback(MDRV_RESET_CB_BEFORE, 0);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(VOS_OK, ulRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST_F(Test_ADS_UL_CCpuResetCallback, Test_ADS_UL_CCpuResetCallback_005)
{
    VOS_UINT32                          ulRst;

    /* ������ʼ�� */

    /* ׮���� */

    /* �������� */

    /* ������ں��� */
    ulRst = ADS_UL_CCpuResetCallback(MDRV_RESET_CB_AFTER, 0);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(VOS_OK, ulRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST_F(Test_ADS_UL_CCpuResetCallback, Test_ADS_UL_CCpuResetCallback_006)
{
    VOS_UINT32                          ulRst;

    /* ������ʼ�� */

    /* ׮���� */

    /* �������� */

    /* ������ں��� */
    ulRst = ADS_UL_CCpuResetCallback(MDRV_RESET_CB_INVALID, 0);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(VOS_ERROR, ulRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}

