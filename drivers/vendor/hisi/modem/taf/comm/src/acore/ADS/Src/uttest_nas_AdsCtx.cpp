#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_nas_AdsCtx.h"

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

VOS_VOID TEST_ADS_Set_QueuePriNv(VOS_UINT8 ucIndex)
{
    ADS_UL_CTX_STRU                    *pstAdsUlCtx = VOS_NULL_PTR;

    pstAdsUlCtx = ADS_GetUlCtx(ucIndex);

    pstAdsUlCtx->stQueuePriNv.ulStatus = VOS_TRUE;
    pstAdsUlCtx->stQueuePriNv.ausPriWeightedNum[0] = 9;
    pstAdsUlCtx->stQueuePriNv.ausPriWeightedNum[1] = 8;
    pstAdsUlCtx->stQueuePriNv.ausPriWeightedNum[2] = 7;
    pstAdsUlCtx->stQueuePriNv.ausPriWeightedNum[3] = 6;
    pstAdsUlCtx->stQueuePriNv.ausPriWeightedNum[4] = 5;
    pstAdsUlCtx->stQueuePriNv.ausPriWeightedNum[5] = 4;
    pstAdsUlCtx->stQueuePriNv.ausPriWeightedNum[6] = 3;
    pstAdsUlCtx->stQueuePriNv.ausPriWeightedNum[7] = 2;
    pstAdsUlCtx->stQueuePriNv.ausPriWeightedNum[8] = 1;

}



class Test_ADS_UL_CreateQueue: public ::testing::Test
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

        PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

        /* ����ID_APS_ADS_PDP_STATUS_IND��Ϣ */
        stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
        stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
        stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

        stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
        stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI3_GBR;
        stPdpStatusInd.enModemId     = MODEM_ID_0;
        stPdpStatusInd.ucRabId       = 0x05;
        stPdpStatusInd.enPdpType     = ADS_PDP_PPP;

        PS_MEM_SET(&stPdpStatusInd2, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

        /* ����ID_APS_ADS_PDP_STATUS_IND��Ϣ */
        stPdpStatusInd2.ulSenderPid   = WUEPS_PID_TAF;
        stPdpStatusInd2.ulReceiverPid = ACPU_PID_ADS_UL;
        stPdpStatusInd2.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

        stPdpStatusInd2.enPdpStatus   = ADS_PDP_STATUS_ACT;
        stPdpStatusInd2.enQciType     = ADS_QCI_TYPE_QCI1_GBR;
        stPdpStatusInd2.enModemId      = MODEM_ID_0;
        stPdpStatusInd2.ucRabId       = 0x08;
        stPdpStatusInd2.enPdpType     = ADS_PDP_PPP;

        /* ����ID_APS_ADS_PDP_STATUS_IND��Ϣ */
        stPdpStatusInd3.ulSenderPid   = WUEPS_PID_TAF;
        stPdpStatusInd3.ulReceiverPid = ACPU_PID_ADS_UL;
        stPdpStatusInd3.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

        stPdpStatusInd3.enPdpStatus   = ADS_PDP_STATUS_ACT;
        stPdpStatusInd3.enQciType     = ADS_QCI_TYPE_QCI5_NONGBR;
        stPdpStatusInd3.enModemId     = MODEM_ID_0;
        stPdpStatusInd3.ucRabId       = 0x07;
        stPdpStatusInd3.enPdpType     = ADS_PDP_PPP;

        /* ����ID_APS_ADS_PDP_STATUS_IND��Ϣ */
        stPdpStatusInd4.ulSenderPid   = WUEPS_PID_TAF;
        stPdpStatusInd4.ulReceiverPid = ACPU_PID_ADS_UL;
        stPdpStatusInd4.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

        stPdpStatusInd4.enPdpStatus   = ADS_PDP_STATUS_ACT;
        stPdpStatusInd4.enQciType     = ADS_QCI_TYPE_QCI4_GBR;
        stPdpStatusInd4.enModemId     = MODEM_ID_0;
        stPdpStatusInd4.ucRabId       = 0x05;
        stPdpStatusInd4.enPdpType     = ADS_PDP_PPP;

        /* ����ID_APS_ADS_PDP_STATUS_IND��Ϣ */
        stPdpStatusInd5.ulSenderPid   = WUEPS_PID_TAF;
        stPdpStatusInd5.ulReceiverPid = ACPU_PID_ADS_UL;
        stPdpStatusInd5.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

        stPdpStatusInd5.enPdpStatus   = ADS_PDP_STATUS_ACT;
        stPdpStatusInd5.enQciType     = ADS_QCI_TYPE_QCI2_GBR;
        stPdpStatusInd5.enModemId     = MODEM_ID_0;
        stPdpStatusInd5.ucRabId       = 0x05;
        stPdpStatusInd5.enPdpType     = ADS_PDP_PPP;

        ADS_InitCtx();

        TEST_ADS_Set_QueuePriNv(ADS_INSTANCE_INDEX_0);
#if(FEATURE_ON == FEATURE_MULTI_MODEM)
        TEST_ADS_Set_QueuePriNv(ADS_INSTANCE_INDEX_1);
#endif

    }
    void TearDown()
    {
    }

protected:

    IMM_ZC_HEAD_STRU                    stULQueue;
    IMM_ZC_HEAD_STRU                    stULQueue2;
    ADS_PDP_STATUS_IND_STRU             stPdpStatusInd;
    ADS_PDP_STATUS_IND_STRU             stPdpStatusInd2;
    ADS_PDP_STATUS_IND_STRU             stPdpStatusInd3;
    ADS_PDP_STATUS_IND_STRU             stPdpStatusInd4;
    ADS_PDP_STATUS_IND_STRU             stPdpStatusInd5;
};
TEST_F(Test_ADS_UL_CreateQueue,Test_ADS_UL_CreateQueue_001)
{
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_STATS_INFO_CTX_STRU            *pAdsStatsInfoCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;

    pAdsStatsInfoCtx = ADS_GetStatsInfoCtx(ADS_INSTANCE_INDEX_0);

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    /* �������� */
    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((VOS_VOID *)&stULQueue));

    /* ���Ժ������� */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* ƥ��ִ�н�� */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].enPrio, ADS_QCI_TYPE_QCI3_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].ucIsQueueValid, VOS_TRUE);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].pstAdsUlLink, &stULQueue);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_DSFLOW_STATS);

    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, enTimerStatus);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
TEST_F(Test_ADS_UL_CreateQueue,Test_ADS_UL_CreateQueue_002)
{
    ADS_UL_CTX_STRU                    *pAdsUlCtx;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    /* �������� */
    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((VOS_VOID *)(&stULQueue)));

    /* ���Ժ������� */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd4));

    /* ƥ��ִ�н�� */
    /* ƥ��ִ�н�� */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].enPrio, ADS_QCI_TYPE_QCI3_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].ucIsQueueValid, VOS_TRUE);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].pstAdsUlLink, &stULQueue);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}



TEST_F(Test_ADS_UL_CreateQueue,Test_ADS_UL_CreateQueue_003)
{
    ADS_UL_CTX_STRU                    *pAdsUlCtx;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    /* �������� */
    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((VOS_VOID *)(&stULQueue)));

    /* ���Ժ������� */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd5));

    /* ƥ��ִ�н�� */
    /* ƥ��ִ�н�� */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].enPrio, ADS_QCI_TYPE_QCI2_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].ucIsQueueValid, VOS_TRUE);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].pstAdsUlLink, &stULQueue);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}
#if 0

TEST_F(Test_ADS_UL_CreateQueue,Test_ADS_UL_CreateQueue_004)
{
    ADS_UL_CTX_STRU                    *pAdsUlCtx;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd2));

    /* ƥ��ִ�н�� */
    //EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 0x05);
    //EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].ucIsQueueValid, VOS_TRUE);
    //EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 0);

    //EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x08);
    //EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[8].ucIsQueueValid, VOS_TRUE);
    //EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[8].pstAdsUlLink->qlen, 0);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}
TEST_F(Test_ADS_UL_CreateQueue,Test_ADS_UL_CreateQueue_005)
{
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    VOS_UINT32                          i;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* ����ID_APS_ADS_PDP_STATUS_IND��Ϣ */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.ucRabId       = 0x05;

    /* ��������� */
    for (i = 0; i < ADS_RAB_NUM_MAX; i++)
    {
        stPdpStatusInd.ucRabId       = 5 + i;
        stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI1_GBR + (i % ADS_QCI_TYPE_BUTT);

        ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));
    }

    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 14);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[2] , 6);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[3] , 15);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[4] , 7);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[5] , 8);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[6] , 9);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[7] , 10);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[8] , 11);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[9] , 12);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[10], 13);

    stPdpStatusInd.ucRabId       = 0x09;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI3_GBR;

    /* ����RabIdΪ6�Ķ��� */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* ƥ��ִ�н�� */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[5] , 9);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[6] , 8);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].enPrio, ADS_QCI_TYPE_QCI1_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].enPrio, ADS_QCI_TYPE_QCI2_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[7].enPrio, ADS_QCI_TYPE_QCI3_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[8].enPrio, ADS_QCI_TYPE_QCI4_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[9].enPrio, ADS_QCI_TYPE_QCI3_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[10].enPrio, ADS_QCI_TYPE_QCI6_NONGBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[11].enPrio, ADS_QCI_TYPE_QCI7_NONGBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[12].enPrio, ADS_QCI_TYPE_QCI8_NONGBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[13].enPrio, ADS_QCI_TYPE_QCI9_NONGBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[14].enPrio, ADS_QCI_TYPE_QCI1_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[15].enPrio, ADS_QCI_TYPE_QCI2_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[9].pstAdsUlLink->qlen, 0);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
#endif


TEST_F(Test_ADS_UL_CreateQueue,Test_ADS_UL_CreateQueue_006)
{
    ADS_UL_CTX_STRU                    *pAdsUlCtx;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    /* ������� */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* �ڴ�����ʧ�� */
    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((void *)VOS_NULL_PTR));

    /* ����RabIdΪ6�Ķ��� */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd2));

    /* ƥ��ִ�н�� */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 0);

    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 0);
    EXPECT_EQ(VOS_NULL_PTR, pAdsUlCtx->astAdsUlQueue[8].pstAdsUlLink);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

#if(FEATURE_ON == FEATURE_MULTI_MODEM)


TEST_F(Test_ADS_UL_CreateQueue,Test_ADS_UL_CreateQueue_011)
{
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_STATS_INFO_CTX_STRU            *pAdsStatsInfoCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;

    pAdsStatsInfoCtx = ADS_GetStatsInfoCtx(ADS_INSTANCE_INDEX_1);

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    /* �������� */
    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((VOS_VOID *)(&stULQueue)));

    /* ���Ժ������� */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;

    stPdpStatusInd.enModemId = MODEM_ID_1;
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* ƥ��ִ�н�� */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].enPrio, ADS_QCI_TYPE_QCI3_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].ucIsQueueValid, VOS_TRUE);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].pstAdsUlLink, &stULQueue);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_DSFLOW_STATS_1);

    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, enTimerStatus);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
TEST_F(Test_ADS_UL_CreateQueue,Test_ADS_UL_CreateQueue_012)
{
    ADS_UL_CTX_STRU                    *pAdsUlCtx;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    /* �������� */
    MOCKER(V_MemAlloc).stubs()
          .will(returnValue((VOS_VOID *)(&stULQueue)));

    /* ���Ժ������� */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.enModemId = MODEM_ID_1;

    stPdpStatusInd4.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd4.enModemId = MODEM_ID_1;
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd4));

    /* ƥ��ִ�н�� */
    /* ƥ��ִ�н�� */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].enPrio, ADS_QCI_TYPE_QCI3_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].ucIsQueueValid, VOS_TRUE);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].pstAdsUlLink, &stULQueue);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}



TEST_F(Test_ADS_UL_CreateQueue,Test_ADS_UL_CreateQueue_013)
{
    ADS_UL_CTX_STRU                    *pAdsUlCtx;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    /* �������� */
    MOCKER(V_MemAlloc).stubs()
          .will(returnValue((VOS_VOID *)(&stULQueue)));

    /* ���Ժ������� */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.enModemId = MODEM_ID_1;

    stPdpStatusInd5.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd5.enModemId = MODEM_ID_1;
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd5));

    /* ƥ��ִ�н�� */
    /* ƥ��ִ�н�� */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x05);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].enPrio, ADS_QCI_TYPE_QCI2_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].ucIsQueueValid, VOS_TRUE);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[0x05].pstAdsUlLink, &stULQueue);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}
#if 0

TEST_F(Test_ADS_UL_CreateQueue,Test_ADS_UL_CreateQueue_014)
{
    ADS_UL_CTX_STRU                    *pAdsUlCtx;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.enModemId = MODEM_ID_1;

    stPdpStatusInd2.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd2.enModemId = MODEM_ID_1;
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd2));

    /* ƥ��ִ�н�� */
    //EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 0x05);
    //EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].ucIsQueueValid, VOS_TRUE);
    //EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 0);

    //EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0x08);
    //EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[8].ucIsQueueValid, VOS_TRUE);
    //EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[8].pstAdsUlLink->qlen, 0);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}
TEST_F(Test_ADS_UL_CreateQueue,Test_ADS_UL_CreateQueue_015)
{
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    VOS_UINT32                          i;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* ����ID_APS_ADS_PDP_STATUS_IND��Ϣ */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.ucRabId       = 0x05;

    /* ��������� */
    for (i = 0; i < ADS_RAB_NUM_MAX; i++)
    {
        stPdpStatusInd.ucRabId       = 5 + i;
        stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI1_GBR + (i % ADS_QCI_TYPE_BUTT);


        stPdpStatusInd.enModemId = MODEM_ID_1;

        ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));
    }

    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 14);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[2] , 6);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[3] , 15);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[4] , 7);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[5] , 8);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[6] , 9);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[7] , 10);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[8] , 11);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[9] , 12);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[10], 13);

    stPdpStatusInd.ucRabId       = 0x09;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI3_GBR;

    /* ����RabIdΪ6�Ķ��� */
    stPdpStatusInd.enModemId = MODEM_ID_1;
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* ƥ��ִ�н�� */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[5] , 9);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[6] , 8);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].enPrio, ADS_QCI_TYPE_QCI1_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].enPrio, ADS_QCI_TYPE_QCI2_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[7].enPrio, ADS_QCI_TYPE_QCI3_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[8].enPrio, ADS_QCI_TYPE_QCI4_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[9].enPrio, ADS_QCI_TYPE_QCI3_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[10].enPrio, ADS_QCI_TYPE_QCI6_NONGBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[11].enPrio, ADS_QCI_TYPE_QCI7_NONGBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[12].enPrio, ADS_QCI_TYPE_QCI8_NONGBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[13].enPrio, ADS_QCI_TYPE_QCI9_NONGBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[14].enPrio, ADS_QCI_TYPE_QCI1_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[15].enPrio, ADS_QCI_TYPE_QCI2_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[9].pstAdsUlLink->qlen, 0);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
#endif


TEST_F(Test_ADS_UL_CreateQueue,Test_ADS_UL_CreateQueue_016)
{
    ADS_UL_CTX_STRU                    *pAdsUlCtx;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    /* ������� */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;

    stPdpStatusInd.enModemId = MODEM_ID_1;
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* �ڴ�����ʧ�� */
    MOCKER(V_MemAlloc)
        .expects(exactly(1))
        .will(returnValue((void *)VOS_NULL_PTR));

    /* ����RabIdΪ6�Ķ��� */
    stPdpStatusInd2.ulSenderPid   = I1_WUEPS_PID_TAF;

    stPdpStatusInd2.enModemId = MODEM_ID_1;
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd2));

    /* ƥ��ִ�н�� */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 0);

    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 0);
    EXPECT_EQ(VOS_NULL_PTR, pAdsUlCtx->astAdsUlQueue[8].pstAdsUlLink);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

#endif


class Test_ADS_UL_DestroyQueue: public ::testing::Test
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

        MOCKER(VOS_GetSlice)
            .defaults()
            .will(returnValue((VOS_INT64)0xffffffff));

        PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

        /* ����ID_APS_ADS_PDP_STATUS_IND��Ϣ */
        stPdpStatusInd.ulSenderPid                          = WUEPS_PID_TAF;
        stPdpStatusInd.ulReceiverPid                        = ACPU_PID_ADS_UL;
        stPdpStatusInd.enMsgId                              = ID_APS_ADS_PDP_STATUS_IND;

        stPdpStatusInd.enPdpStatus                          = ADS_PDP_STATUS_DEACT;
        stPdpStatusInd.ucRabId                              = 0x05;

        pstULQueue                                          = (IMM_ZC_HEAD_STRU *)PS_MEM_ALLOC(ACPU_PID_ADS_UL,
                                                                         sizeof(IMM_ZC_HEAD_STRU));

        ADS_InitCtx();
        IMM_ZcQueueHeadInit(pstULQueue);

        /*�Ѽ���0x05*/

        TEST_ADS_Set_QueuePriNv(ADS_INSTANCE_INDEX_0);
#if(FEATURE_ON == FEATURE_MULTI_MODEM)
        TEST_ADS_Set_QueuePriNv(ADS_INSTANCE_INDEX_1);
#endif

    }
    void TearDown()
    {
        UT_STUB_INIT();
        UT_IMM_STUB_INIT();

        ADS_InitCtx();

        GlobalMockObject::verify();
    }

protected:

    IMM_ZC_HEAD_STRU                    *pstULQueue;
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
};


TEST_F(Test_ADS_UL_DestroyQueue,Test_ADS_UL_DestroyQueue_001)
{
    /* ������������ */
    stPdpStatusInd.ucRabId                              = 0x06;
    ADS_UL_CTX_STRU                    *pstAdsUlCtx = VOS_NULL_PTR;

    pstAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    pstAdsUlCtx->aucPrioIndex[0] = 5;
    pstAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink = pstULQueue;
    pstAdsUlCtx->astAdsUlQueue[5].enPrio       = ADS_QCI_TYPE_QCI2_GBR;
    pstAdsUlCtx->astAdsUlQueue[5].ucIsQueueValid = VOS_TRUE;

    /* �������� */
    MOCKER(V_MemAlloc).stubs()
          .will(returnValue((VOS_VOID *)(pstULQueue)));

    /* ���Ժ������� */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* ƥ��ִ�н�� */
    EXPECT_EQ(pstAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pstAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink, pstULQueue);
    EXPECT_EQ(pstAdsUlCtx->astAdsUlQueue[5].enPrio, ADS_QCI_TYPE_QCI2_GBR);
    EXPECT_EQ(pstAdsUlCtx->astAdsUlQueue[5].ucIsQueueValid, VOS_TRUE);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}



TEST_F(Test_ADS_UL_DestroyQueue,Test_ADS_UL_DestroyQueue_002)
{
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;
    ADS_STATS_INFO_CTX_STRU            *pAdsStatsInfoCtx;
    ADS_UL_CTX_STRU                    *pstAdsUlCtx = VOS_NULL_PTR;

    pstAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    pAdsStatsInfoCtx = ADS_GetStatsInfoCtx(ADS_INSTANCE_INDEX_0);

    pstAdsUlCtx->aucPrioIndex[0] = 5;
    pstAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink = pstULQueue;
    pstAdsUlCtx->astAdsUlQueue[5].enPrio       = ADS_QCI_TYPE_QCI2_GBR;

    /* ������������ */

    /* �������� */

    /* ���Ժ������� */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* ƥ��ִ�н�� */
    EXPECT_EQ(pstAdsUlCtx->aucPrioIndex[0] , 0);
    EXPECT_EQ(pstAdsUlCtx->astAdsUlQueue[5].enPrio , ADS_QCI_TYPE_BUTT);
    EXPECT_EQ(VOS_NULL_PTR, pstAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_DSFLOW_STATS);

    EXPECT_EQ(ADS_TIMER_STATUS_STOP, enTimerStatus);
    EXPECT_EQ(0, pAdsStatsInfoCtx->stULDataStats.ulULPeriodSndBytes);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST_F(Test_ADS_UL_DestroyQueue,Test_ADS_UL_DestroyQueue_003)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;

    pAdsUlCtx    = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* ����ID_APS_ADS_PDP_STATUS_IND��Ϣ */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI2_GBR;
    stPdpStatusInd.ucRabId       = 0x05;

    /* ����RabIdΪ5�Ķ��� */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* �������� */
    ucRabId = 5;

    /* ����RabId5��5�����ݰ� */
    for (i = 0; i < 5; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* ƥ��ִ�н�� */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].enPrio , ADS_QCI_TYPE_QCI2_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].ucIsQueueValid, VOS_TRUE);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 5);

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_DEACT;
    stPdpStatusInd.ucRabId       = 0x05;

    /* ����RabIdΪ5�Ķ��� */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].ucIsQueueValid, VOS_FALSE);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].enPrio , ADS_QCI_TYPE_BUTT);
    EXPECT_EQ(VOS_NULL_PTR, pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}



TEST_F(Test_ADS_UL_DestroyQueue,Test_ADS_UL_DestroyQueue_004)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;
    ADS_STATS_INFO_CTX_STRU            *pAdsStatsInfoCtx;

    pAdsStatsInfoCtx = ADS_GetStatsInfoCtx(ADS_INSTANCE_INDEX_0);

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    MOCKER(V_StartRelTimer)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* ����ID_APS_ADS_PDP_STATUS_IND��Ϣ */
    stPdpStatusInd.ulSenderPid   = WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI4_GBR;
    stPdpStatusInd.ucRabId       = 0x05;

    /* ����RabIdΪ5�Ķ��� */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI1_GBR;
    stPdpStatusInd.ucRabId       = 0x06;

    /* ����RabIdΪ6�Ķ��� */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI2_GBR;
    stPdpStatusInd.ucRabId       = 0x07;

    /* ����RabIdΪ7�Ķ��� */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* �������� */
    ucRabId = 5;

    /* ����RabId5��5�����ݰ� */
    for (i = 0; i < 5; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* ƥ��ִ�н�� */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 6);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 5);

    pAdsStatsInfoCtx->stULDataStats.ulULPeriodSndBytes = 10;

    /* ����RabIdΪ6�Ķ��� */
    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_DEACT;
    stPdpStatusInd.ucRabId       = 0x06;

    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 7);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].ucIsQueueValid, VOS_FALSE);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].enPrio , ADS_QCI_TYPE_BUTT);
    EXPECT_EQ(VOS_NULL_PTR, pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_DSFLOW_STATS);

    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, enTimerStatus);
    EXPECT_EQ(10, pAdsStatsInfoCtx->stULDataStats.ulULPeriodSndBytes);

    /* ����RabIdΪ8�Ķ��� */
    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI3_GBR;
    stPdpStatusInd.ucRabId       = 0x08;

    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 7);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 8);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[2] , 5);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
TEST_F(Test_ADS_UL_DestroyQueue,Test_ADS_UL_DestroyQueue_005)
{
    ADS_UL_CTX_STRU                    *pAdsUlCtx;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_0);

    pAdsUlCtx->aucPrioIndex[0] = 5;
    /* ��������ڣ����Ƕ���Ϊ�� */
    pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink = VOS_NULL_PTR;
    pAdsUlCtx->astAdsUlQueue[5].enPrio       = ADS_QCI_TYPE_QCI2_GBR;
    pAdsUlCtx->astAdsUlQueue[5].ucIsQueueValid = VOS_TRUE;

    /* ���Ժ������� */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));


    /* ƥ��ִ�н�� */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0);
    EXPECT_EQ(VOS_NULL_PTR, pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
#if(FEATURE_ON == FEATURE_MULTI_MODEM)
TEST_F(Test_ADS_UL_DestroyQueue,Test_ADS_UL_DestroyQueue_011)
{
    /* ������������ */
    stPdpStatusInd.ucRabId                              = 0x06;
    ADS_UL_CTX_STRU                    *pstAdsUlCtx = VOS_NULL_PTR;

    pstAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    pstAdsUlCtx->aucPrioIndex[0] = 5;
    pstAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink = pstULQueue;
    pstAdsUlCtx->astAdsUlQueue[5].enPrio       = ADS_QCI_TYPE_QCI2_GBR;
    pstAdsUlCtx->astAdsUlQueue[5].ucIsQueueValid = VOS_TRUE;

    /* �������� */
    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((VOS_VOID *)(pstULQueue)));

    /* ���Ժ������� */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;

    stPdpStatusInd.enModemId = MODEM_ID_1;
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* ƥ��ִ�н�� */
    EXPECT_EQ(pstAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pstAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink, pstULQueue);
    EXPECT_EQ(pstAdsUlCtx->astAdsUlQueue[5].enPrio, ADS_QCI_TYPE_QCI2_GBR);
    EXPECT_EQ(pstAdsUlCtx->astAdsUlQueue[5].ucIsQueueValid, VOS_TRUE);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}



TEST_F(Test_ADS_UL_DestroyQueue,Test_ADS_UL_DestroyQueue_012)
{
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;
    ADS_STATS_INFO_CTX_STRU            *pAdsStatsInfoCtx;
    ADS_UL_CTX_STRU                    *pstAdsUlCtx = VOS_NULL_PTR;

    pstAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    pAdsStatsInfoCtx = ADS_GetStatsInfoCtx(ADS_INSTANCE_INDEX_1);

    pstAdsUlCtx->aucPrioIndex[0] = 5;
    pstAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink = pstULQueue;
    pstAdsUlCtx->astAdsUlQueue[5].enPrio       = ADS_QCI_TYPE_QCI2_GBR;

    /* ������������ */

    /* �������� */

    /* ���Ժ������� */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;

    stPdpStatusInd.enModemId = MODEM_ID_1;
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* ƥ��ִ�н�� */
    EXPECT_EQ(pstAdsUlCtx->aucPrioIndex[0] , 0);
    EXPECT_EQ(pstAdsUlCtx->astAdsUlQueue[5].enPrio , ADS_QCI_TYPE_BUTT);
    EXPECT_EQ(VOS_NULL_PTR, pstAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_DSFLOW_STATS);

    EXPECT_EQ(ADS_TIMER_STATUS_STOP, enTimerStatus);
    EXPECT_EQ(0, pAdsStatsInfoCtx->stULDataStats.ulULPeriodSndBytes);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST_F(Test_ADS_UL_DestroyQueue,Test_ADS_UL_DestroyQueue_013)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;

    pAdsUlCtx    = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* ����ID_APS_ADS_PDP_STATUS_IND��Ϣ */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI2_GBR;
    stPdpStatusInd.ucRabId       = 0x05;

    /* ����RabIdΪ5�Ķ��� */

    stPdpStatusInd.enModemId = MODEM_ID_1;
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* �������� */
    ucRabId = 0x45;

    /* ����RabId5��5�����ݰ� */
    for (i = 0; i < 5; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* ƥ��ִ�н�� */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 5);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].enPrio , ADS_QCI_TYPE_QCI2_GBR);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].ucIsQueueValid, VOS_TRUE);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 5);

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_DEACT;
    stPdpStatusInd.ucRabId       = 0x05;

    /* ����RabIdΪ5�Ķ��� */
    stPdpStatusInd.enModemId = MODEM_ID_1;
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].ucIsQueueValid, VOS_FALSE);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].enPrio , ADS_QCI_TYPE_BUTT);
    EXPECT_EQ(VOS_NULL_PTR, pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}



TEST_F(Test_ADS_UL_DestroyQueue,Test_ADS_UL_DestroyQueue_014)
{
    ADS_PDP_STATUS_IND_STRU          stPdpStatusInd;
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstData;
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pAdsUlCtx;
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;
    ADS_STATS_INFO_CTX_STRU            *pAdsStatsInfoCtx;

    pAdsStatsInfoCtx = ADS_GetStatsInfoCtx(ADS_INSTANCE_INDEX_1);

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    PS_MEM_SET(&stPdpStatusInd, 0x00, sizeof(ADS_PDP_STATUS_IND_STRU));

    /* ����ID_APS_ADS_PDP_STATUS_IND��Ϣ */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;
    stPdpStatusInd.ulReceiverPid = ACPU_PID_ADS_UL;
    stPdpStatusInd.enMsgId       = ID_APS_ADS_PDP_STATUS_IND;

    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI4_GBR;
    stPdpStatusInd.ucRabId       = 0x05;

    /* ����RabIdΪ5�Ķ��� */
    stPdpStatusInd.enModemId = MODEM_ID_1;
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI1_GBR;
    stPdpStatusInd.ucRabId       = 0x06;

    /* ����RabIdΪ6�Ķ��� */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI2_GBR;
    stPdpStatusInd.ucRabId       = 0x07;

    /* ����RabIdΪ7�Ķ��� */
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    /* �������� */
    ucRabId = 0x45;

    /* ����RabId5��5�����ݰ� */
    for (i = 0; i < 5; i++)
    {
        pstData = IMM_ZcStaticAlloc(10);

        ADS_UL_SendPacket(pstData, ucRabId);
    }

    /* ƥ��ִ�н�� */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 6);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink->qlen, 5);

    pAdsStatsInfoCtx->stULDataStats.ulULPeriodSndBytes = 10;

    /* ����RabIdΪ6�Ķ��� */
    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_DEACT;
    stPdpStatusInd.ucRabId       = 0x06;

    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 7);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].ucIsQueueValid, VOS_FALSE);
    EXPECT_EQ(pAdsUlCtx->astAdsUlQueue[6].enPrio , ADS_QCI_TYPE_BUTT);
    EXPECT_EQ(VOS_NULL_PTR, pAdsUlCtx->astAdsUlQueue[6].pstAdsUlLink);

    enTimerStatus = ADS_GetTimerStatus(ACPU_PID_ADS_UL, TI_ADS_DSFLOW_STATS_1);

    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, enTimerStatus);
    EXPECT_EQ(10, pAdsStatsInfoCtx->stULDataStats.ulULPeriodSndBytes);

    /* ����RabIdΪ8�Ķ��� */
    stPdpStatusInd.enPdpStatus   = ADS_PDP_STATUS_ACT;
    stPdpStatusInd.enQciType     = ADS_QCI_TYPE_QCI3_GBR;
    stPdpStatusInd.ucRabId       = 0x08;

    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));

    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 7);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[1] , 8);
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[2] , 5);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
TEST_F(Test_ADS_UL_DestroyQueue,Test_ADS_UL_DestroyQueue_015)
{
    ADS_UL_CTX_STRU                    *pAdsUlCtx;

    pAdsUlCtx = ADS_GetUlCtx(ADS_INSTANCE_INDEX_1);

    pAdsUlCtx->aucPrioIndex[0] = 5;
    /* ��������ڣ����Ƕ���Ϊ�� */
    pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink = VOS_NULL_PTR;
    pAdsUlCtx->astAdsUlQueue[5].enPrio       = ADS_QCI_TYPE_QCI2_GBR;
    pAdsUlCtx->astAdsUlQueue[5].ucIsQueueValid = VOS_TRUE;

    /* ���Ժ������� */
    stPdpStatusInd.ulSenderPid   = I1_WUEPS_PID_TAF;

    stPdpStatusInd.enModemId = MODEM_ID_1;
    ADS_UL_ProcMsg((struct MsgCB *)(&stPdpStatusInd));


    /* ƥ��ִ�н�� */
    EXPECT_EQ(pAdsUlCtx->aucPrioIndex[0] , 0);
    EXPECT_EQ(VOS_NULL_PTR, pAdsUlCtx->astAdsUlQueue[5].pstAdsUlLink);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
#endif
class Test_ADS_UL_SetProtectTmrLen: public ::testing::Test
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


TEST_F(Test_ADS_UL_SetProtectTmrLen,Test_ADS_UL_SetProtectTmrLen_001)
{
    ADS_IPF_CTX_STRU                    *pAdsIpfCtx;

    pAdsIpfCtx = ADS_GET_IPF_CTX_PTR();

    ADS_UL_SetProtectTmrLen(10);

    EXPECT_EQ(10, pAdsIpfCtx->ulProtectTmrLen);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

