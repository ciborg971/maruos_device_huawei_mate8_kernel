#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_nas_CsdUpLink.h"


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

#if 0

#if( FEATURE_ON == FEATURE_CSD )

class Test_CSD_UL_ProcMsg: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        CSD_InitCtx();

        PS_MEM_SET(&stCallStateInd, 0x00, sizeof(AT_CSD_CALL_STATE_TYPE_IND_STRU));

        /* ��д��Ϣͷ */
        stCallStateInd.ulSenderPid     = WUEPS_PID_AT;
        stCallStateInd.ulReceiverCpuId = VOS_LOCAL_CPUID;
        stCallStateInd.ulReceiverPid   = ACPU_PID_CSD;
        stCallStateInd.enMsgId         = ID_AT_CSD_CALL_STATE_IND;
    }
    void TearDown()
    {
    }

protected:

    AT_CSD_CALL_STATE_TYPE_IND_STRU stCallStateInd;

};
TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_RcvAtMsg_001 )
{
    /* ������������ */
    stCallStateInd.enMsgId      = ID_AT_CSD_MSG_ID_ENUM_BUTT;

    /* �������� */
    MOCKER(CSD_UL_RcvAtCallStateInd)
          .expects(never());

    /* ���Ժ������� */
    CSD_UL_ProcMsg((struct MsgCB *)(&stCallStateInd));

    /* ƥ��ִ�н�� */

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();


}

TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_ProcMsg_001 )
{
    /* ������������ */
    MsgBlock* pMsg;

    pMsg            = VOS_NULL_PTR;

    /* �������� */
    MOCKER(CSD_UL_RcvAtMsg)
          .expects(never());

    /* ���Ժ������� */
    CSD_UL_ProcMsg(pMsg);

    /* ƥ��ִ�н�� */

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();


}

TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_ProcMsg_002 )
{
    /* ������������ */
    stCallStateInd.ulSenderPid      = ACPU_PID_CSD;

    /* �������� */
    MOCKER(CSD_UL_RcvAtMsg)
          .expects(never());

    /* ���Ժ������� */
    CSD_UL_ProcMsg((MsgBlock *)(&stCallStateInd));

    /* ƥ��ִ�н�� */

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_RcvAtCallStateInd_001 )
{
    /* ������������ */
    stCallStateInd.enCallState      = AT_CSD_CALL_STATE_BUTT;

    /* �������� */
    MOCKER(CSD_UL_RcvAtCallStateOn)
          .expects(never());

    MOCKER(CSD_UL_RcvAtCallStateOff)
          .expects(never());

    /* ���Ժ������� */
    CSD_UL_ProcMsg((MsgBlock *)(&stCallStateInd));

    /* ƥ��ִ�н�� */

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}

TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_RcvAtCallStateOn_001 )
{
    IMM_ZC_HEAD_STRU                    *pstULQueue;


    /* ������������ */
    stCallStateInd.enCallState           = AT_CSD_CALL_STATE_ON;

    /* �������� */
    pstULQueue                           = (IMM_ZC_HEAD_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                        sizeof(IMM_ZC_HEAD_STRU));

    MOCKER(V_MemAlloc)
          .will(returnValue(pstULQueue));

    MOCKER(CSD_UL_RcvAtCallStateOff)
          .expects(never());

    /* ���Ժ������� */
    CSD_UL_ProcMsg((MsgBlock *)(&stCallStateInd));

    /* ƥ��ִ�н�� */
    EXPECT_EQ(pstULQueue, CSD_UL_GetQueue());
    EXPECT_EQ(AT_CSD_CALL_STATE_ON, CSD_GetCallState());

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();


}


TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_RcvAtCallStateOff_001 )
{
    IMM_ZC_HEAD_STRU                    *pstULQueue;

    pstULQueue                           =(IMM_ZC_HEAD_STRU *) PS_MEM_ALLOC(ACPU_PID_CSD,
                                                        sizeof(IMM_ZC_HEAD_STRU));
    /* ������������ */
    stCallStateInd.enCallState           = AT_CSD_CALL_STATE_OFF;

    /* �������� */
    PS_MEM_SET(pstULQueue, 0x00, sizeof(IMM_ZC_HEAD_STRU));

    CSD_UL_SetQueue(pstULQueue);

    MOCKER(CSD_UL_RcvAtCallStateOn)
          .expects(never());

    /* ���Ժ������� */
    CSD_UL_ProcMsg((MsgBlock *)(&stCallStateInd));

    /* ƥ��ִ�н�� */
    EXPECT_EQ(VOS_NULL_PTR, CSD_UL_GetQueue());
    EXPECT_EQ(CSD_DEFAULT_TX_SLICE, CSD_GetLastTxSlice());
    EXPECT_EQ(AT_CSD_CALL_STATE_OFF, CSD_GetCallState());

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();


}


TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_RcvAtCallStateOff_002 )
{
    /* ������������ */
    stCallStateInd.enCallState      = AT_CSD_CALL_STATE_OFF;

    /* �������� */
    MOCKER(CSD_UL_RcvAtCallStateOn)
          .expects(never());

    /* ���Ժ������� */
    CSD_UL_ProcMsg((MsgBlock *)(&stCallStateInd));

    /* ƥ��ִ�н�� */
    EXPECT_EQ(VOS_NULL_PTR, CSD_UL_GetQueue());
    EXPECT_EQ(CSD_DEFAULT_TX_SLICE, CSD_GetLastTxSlice());
    EXPECT_EQ(AT_CSD_CALL_STATE_OFF, CSD_GetCallState());


    CSD_UL_ProcMsg((MsgBlock *)(&stCallStateInd));


    EXPECT_EQ(VOS_NULL_PTR, CSD_UL_GetQueue());
    EXPECT_EQ(CSD_DEFAULT_TX_SLICE, CSD_GetLastTxSlice());
    EXPECT_EQ(AT_CSD_CALL_STATE_OFF, CSD_GetCallState());


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();


}

TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_RcvAtCallStateOff_003 )
{
    IMM_ZC_HEAD_STRU                   *pstULQueue;

    /* ������������ */
    stCallStateInd.enCallState          = AT_CSD_CALL_STATE_OFF;

    /* �������� */
    pstULQueue                          = (IMM_ZC_HEAD_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                      sizeof(IMM_ZC_HEAD_STRU));

    PS_MEM_SET(pstULQueue, 0x00, sizeof(IMM_ZC_HEAD_STRU));

    IMM_ZcQueueHeadInit(pstULQueue);

    pstULQueue->qlen                   = 1;


    CSD_UL_SetQueue(pstULQueue);

    MOCKER(CSD_UL_RcvAtCallStateOn)
          .expects(never());

    /* ���Ժ������� */
    CSD_UL_ProcMsg((MsgBlock *)(&stCallStateInd));

    EXPECT_EQ(VOS_NULL_PTR, CSD_UL_GetQueue());


}
TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_FreeQueue_001 )
{
    IMM_ZC_HEAD_STRU                    *pstULQueue;
    IMM_ZC_STRU                         *pstZcData;
    IMM_ZC_STRU                         *pstCmpZcData;

    pstULQueue                           = (IMM_ZC_HEAD_STRU *) PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                        sizeof(IMM_ZC_HEAD_STRU));

    pstZcData                             = (IMM_ZC_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                        sizeof(IMM_ZC_STRU));

    pstCmpZcData                             = (IMM_ZC_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                        sizeof(IMM_ZC_STRU));

    /* ������������ */
    stCallStateInd.enCallState           = AT_CSD_CALL_STATE_OFF;

    /* �������� */
    PS_MEM_SET(pstZcData, 0x00, sizeof(IMM_ZC_STRU));
    PS_MEM_SET(pstCmpZcData, 0x00, sizeof(IMM_ZC_STRU));
    PS_MEM_SET(pstULQueue, 0x00, sizeof(IMM_ZC_HEAD_STRU));

    IMM_ZcQueueHeadInit(pstULQueue);

    CSD_UL_SetQueue(pstULQueue);

    CSD_UL_InsertQueueTail(CSD_UL_GetQueue(),pstZcData);

    EXPECT_EQ(0x01, CSD_UL_GetQueue()->qlen);

    MOCKER(CSD_UL_RcvAtCallStateOn)
          .expects(never());

    MOCKER(kfree_skb)
        .with(mirror(pstCmpZcData, sizeof(IMM_ZC_STRU)));

    MOCKER(V_MemFree)
        .expects(exactly(1));

    /* ���Ժ������� */
    CSD_UL_ProcMsg((MsgBlock *)(&stCallStateInd));

    /* ƥ��ִ�н�� */
    EXPECT_EQ(VOS_NULL_PTR, CSD_UL_GetQueue());
    EXPECT_EQ(CSD_DEFAULT_TX_SLICE, CSD_GetLastTxSlice());
    EXPECT_EQ(AT_CSD_CALL_STATE_OFF, CSD_GetCallState());

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();


}

TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_FreeQueue_002 )
{
    IMM_ZC_HEAD_STRU                         *pstULQueue;

    pstULQueue                           = (IMM_ZC_HEAD_STRU *) PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                        sizeof(IMM_ZC_HEAD_STRU));

    /* ������������ */
    stCallStateInd.enCallState           = AT_CSD_CALL_STATE_OFF;

    /* �������� */
    PS_MEM_SET(pstULQueue, 0x00, sizeof(IMM_ZC_HEAD_STRU));

    IMM_ZcQueueHeadInit(pstULQueue);

    pstULQueue->qlen                   = 0x01;

    CSD_UL_SetQueue(pstULQueue);

    EXPECT_EQ(0x01, CSD_UL_GetQueue()->qlen);

    MOCKER(CSD_UL_RcvAtCallStateOn)
          .expects(never());

    MOCKER(kfree_skb)
          .expects(never());

    MOCKER(V_MemFree)
          .expects(exactly(1));

    /* ���Ժ������� */
    CSD_UL_ProcMsg((MsgBlock *)(&stCallStateInd));

    /* ƥ��ִ�н�� */
    EXPECT_EQ(VOS_NULL_PTR, CSD_UL_GetQueue());
    EXPECT_EQ(CSD_DEFAULT_TX_SLICE, CSD_GetLastTxSlice());
    EXPECT_EQ(AT_CSD_CALL_STATE_OFF, CSD_GetCallState());

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();


}

TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_FreeQueue_003 )
{
    IMM_ZC_HEAD_STRU                   *pstULQueue;
    IMM_ZC_STRU                        *pstZcData;
    IMM_ZC_STRU                         *pstCmpZcData;


    pstULQueue                          = (IMM_ZC_HEAD_STRU *) PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                         sizeof(IMM_ZC_HEAD_STRU));

    pstZcData                           = (IMM_ZC_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                         sizeof(IMM_ZC_STRU));
    pstCmpZcData                             = (IMM_ZC_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                        sizeof(IMM_ZC_STRU));

    /* ������������ */
    stCallStateInd.enCallState          = AT_CSD_CALL_STATE_OFF;

    /* �������� */
    PS_MEM_SET(pstCmpZcData, 0x00, sizeof(IMM_ZC_STRU));
    PS_MEM_SET(pstZcData, 0x00, sizeof(IMM_ZC_STRU));
    PS_MEM_SET(pstULQueue, 0x00, sizeof(IMM_ZC_HEAD_STRU));

    IMM_ZcQueueHeadInit(pstULQueue);

    CSD_UL_SetQueue(pstULQueue);

    CSD_UL_InsertQueueTail(CSD_UL_GetQueue(),pstZcData);

    EXPECT_EQ(0x01, CSD_UL_GetQueue()->qlen);

    MOCKER(CSD_UL_RcvAtCallStateOn)
        .expects(never());

    MOCKER(kfree_skb)
        .with(mirror(pstCmpZcData, sizeof(IMM_ZC_STRU)));
#if (FEATURE_IMM_MEM_DEBUG)
    MOCKER(skb_queue_tail_debug)
        .will(returnValue(VOS_NULL_PTR));
#else
    MOCKER(skb_queue_tail)
        .will(returnValue(VOS_NULL_PTR));
#endif

    MOCKER(V_MemFree)
        .expects(exactly(1));

    /* ���Ժ������� */
    CSD_UL_ProcMsg((MsgBlock *)(&stCallStateInd));

    /* ƥ��ִ�н�� */
    EXPECT_EQ(VOS_NULL_PTR, CSD_UL_GetQueue());
    EXPECT_EQ(CSD_DEFAULT_TX_SLICE, CSD_GetLastTxSlice());
    EXPECT_EQ(AT_CSD_CALL_STATE_OFF, CSD_GetCallState());

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_InitQueue_001 )
{
    /* ������������ */
    stCallStateInd.enCallState          = AT_CSD_CALL_STATE_ON;

    /* �������� */
    MOCKER(CSD_UL_RcvAtCallStateOff)
          .expects(never());

    MOCKER(V_MemAlloc)
           .will(returnValue(VOS_NULL_PTR));

    /* ���Ժ������� */
    CSD_UL_ProcMsg((MsgBlock *)(&stCallStateInd));

    /* ƥ��ִ�н�� */
    EXPECT_EQ(VOS_NULL_PTR, CSD_UL_GetQueue());
    EXPECT_EQ(AT_CSD_CALL_STATE_OFF, CSD_GetCallState());

}

TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_InitQueue_002 )
{
    IMM_ZC_HEAD_STRU                         *pstULQueue;

    /* ������������ */
    stCallStateInd.enCallState          = AT_CSD_CALL_STATE_ON;

    /* �������� */

    pstULQueue                          = (IMM_ZC_HEAD_STRU *) PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                        sizeof(IMM_ZC_HEAD_STRU));
    PS_MEM_SET(pstULQueue, 0x00, sizeof(IMM_ZC_HEAD_STRU));

    IMM_ZcQueueHeadInit(pstULQueue);

    CSD_UL_SetQueue(pstULQueue);

    MOCKER(CSD_UL_RcvAtCallStateOff)
      .expects(never());

    /* ���Ժ������� */
    CSD_UL_ProcMsg((MsgBlock *)(&stCallStateInd));

    /* ƥ��ִ�н�� */
    EXPECT_EQ(pstULQueue, CSD_UL_GetQueue());
    EXPECT_EQ(AT_CSD_CALL_STATE_ON, CSD_GetCallState());

}


TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_InsertQueue_001 )
{
    IMM_ZC_STRU                        *pstZcData;

    /* ������������ */
    pstZcData                           = (IMM_ZC_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                sizeof(IMM_ZC_STRU));
    PS_MEM_SET(pstZcData, 0x00, sizeof(IMM_ZC_STRU));

    pstZcData->data                     = (VOS_UINT8 *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                    4);
    pstZcData->len                      = 4;

    /* �������� */
    MOCKER(kfree_skb)
        .with(mirror(pstZcData, sizeof(IMM_ZC_STRU)));

    /* ���Ժ������� */
    CSD_UL_SendData(pstZcData);

    /* ƥ��ִ�н�� */
    EXPECT_EQ(VOS_NULL_PTR, CSD_UL_GetQueue());
    EXPECT_EQ(AT_CSD_CALL_STATE_OFF, CSD_GetCallState());

}


TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_InsertQueue_003 )
{
    IMM_ZC_STRU                        *pstZcData;
    IMM_ZC_HEAD_STRU                   *pstULQueue;

    /* ������������ */
    pstZcData                           = (IMM_ZC_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                sizeof(IMM_ZC_STRU));

    pstULQueue                          = (IMM_ZC_HEAD_STRU *) PS_MEM_ALLOC(ACPU_PID_CSD,
                                                        sizeof(IMM_ZC_HEAD_STRU));

    PS_MEM_SET(pstULQueue, 0x00, sizeof(IMM_ZC_HEAD_STRU));
    PS_MEM_SET(pstZcData, 0x00, sizeof(IMM_ZC_STRU));

    pstZcData->data                     = (VOS_UINT8 *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                    4);
    pstZcData->len                      = 4;

    /* �������� */
    IMM_ZcQueueHeadInit(pstULQueue);

    CSD_UL_SetQueue(pstULQueue);
    CSD_SetCallState(AT_CSD_CALL_STATE_ON);

    MOCKER(VOS_SmV)
        .with(eq(CSD_GetUpLinkDataSem()))
        .expects(exactly(1));

    /* ���Ժ������� */
    CSD_UL_SendData(pstZcData);

    /* ƥ��ִ�н�� */
    EXPECT_EQ(pstULQueue, CSD_UL_GetQueue());
    EXPECT_EQ(1, CSD_UL_GetQueue()->qlen);
    EXPECT_EQ(AT_CSD_CALL_STATE_ON, CSD_GetCallState());

}



TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_ProcDataTask_001 )
{
    /* ������������ */

    /* �������� */
    MOCKER(VOS_SmP)
          .expects(exactly(1))
          .will(returnValue(VOS_ERR));


    MOCKER(CSD_UL_CalcIsrSlice)
          .expects(never());

    MOCKER(CSD_UL_SendDataToDICC)
          .expects(never());

    /* ���Ժ������� */
    CSD_UL_ProcDataTask();

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}
TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_ProcDataTask_002 )
{
    /* ������������ */

    /* �������� */
    MOCKER(VOS_SmP)
          .expects(exactly(1))
          .will(returnValue(VOS_OK));


    MOCKER(CSD_UL_CalcIsrSlice)
          .expects(never());

    MOCKER(CSD_UL_SendDataToDICC)
          .expects(never());

    CSD_SetCallState(AT_CSD_CALL_STATE_OFF);

    /* ���Ժ������� */
    CSD_UL_ProcDataTask();

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();


}
TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_ProcDataTask_003 )
{
    /* ������������ */

    /* �������� */
    MOCKER(VOS_SmP)
          .expects(exactly(1))
          .will(returnValue(VOS_OK));

    MOCKER(VOS_GetSlice)
          .will(returnObjectList(CSD_MAX_SLICE_CNT - 100, CSD_MAX_SLICE_CNT - 400));

    MOCKER(VOS_TaskDelay)
          .with(eq(CSD_UL_TASK_DELAY_TIME));

    MOCKER(CSD_UL_SendDataToDICC)
          .expects(exactly(1));

    CSD_SetCallState(AT_CSD_CALL_STATE_ON);

    /* ���Ժ������� */
    CSD_UL_ProcDataTask();

    /* ƥ��ִ�н�� */

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();


}


TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_SendData_001 )
{
    IMM_ZC_HEAD_STRU                   *pstULQueue;

    /* ������������ */
    pstULQueue                          = (IMM_ZC_HEAD_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                      sizeof(IMM_ZC_HEAD_STRU));

    PS_MEM_SET(pstULQueue, 0x00, sizeof(IMM_ZC_HEAD_STRU));

    /* �������� */
    IMM_ZcQueueHeadInit(pstULQueue);

    CSD_UL_SetQueue(pstULQueue);

    EXPECT_EQ(0x00, CSD_UL_GetQueue()->qlen);

    MOCKER(CSD_UL_InsertQueue)
          .expects(never());

    /* ���Ժ������� */
    CSD_UL_SendData(VOS_NULL_PTR);


    /* ƥ��ִ�н�� */
    EXPECT_EQ(0x00, CSD_UL_GetQueue()->qlen);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();


}

TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_SendData_002 )
{
    IMM_ZC_STRU                        *pstZcData;
    IMM_ZC_HEAD_STRU                   *pstULQueue;

    /* ������������ */
    pstZcData                           = (IMM_ZC_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                      sizeof(IMM_ZC_STRU));

    pstULQueue                          = (IMM_ZC_HEAD_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                      sizeof(IMM_ZC_HEAD_STRU));

    PS_MEM_SET(pstULQueue, 0x00, sizeof(IMM_ZC_HEAD_STRU));
    PS_MEM_SET(pstZcData, 0x00, sizeof(IMM_ZC_STRU));

    pstZcData->data                     = VOS_NULL_PTR;
    pstZcData->len                      = 4;

    /* �������� */
    IMM_ZcQueueHeadInit(pstULQueue);

    CSD_UL_SetQueue(pstULQueue);

    EXPECT_EQ(0x00, CSD_UL_GetQueue()->qlen);

    MOCKER(CSD_UL_InsertQueue)
          .expects(never());

    /* ���Ժ������� */
    CSD_UL_SendData(pstZcData);

    /* ƥ��ִ�н�� */
    EXPECT_EQ(0x00, CSD_UL_GetQueue()->qlen);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();


}

TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_SendData_003 )
{
    IMM_ZC_STRU                        *pstZcData;
    IMM_ZC_HEAD_STRU                        *pstULQueue;

    /* ������������ */
    pstZcData                           = (IMM_ZC_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                      sizeof(IMM_ZC_STRU));

    pstULQueue                          = (IMM_ZC_HEAD_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                      sizeof(IMM_ZC_HEAD_STRU));

    PS_MEM_SET(pstULQueue, 0x00, sizeof(IMM_ZC_HEAD_STRU));
    PS_MEM_SET(pstZcData, 0x00, sizeof(IMM_ZC_STRU));

    pstZcData->data                     = (VOS_UINT8 *)PS_MEM_ALLOC(ACPU_PID_CSD, 4);;
    pstZcData->len                      = 0;

    /* �������� */
    IMM_ZcQueueHeadInit(pstULQueue);

    CSD_UL_SetQueue(pstULQueue);

    EXPECT_EQ(0x00, CSD_UL_GetQueue()->qlen);

    MOCKER(CSD_UL_InsertQueue)
          .expects(never());

    /* ���Ժ������� */
    CSD_UL_SendData(pstZcData);


    /* ƥ��ִ�н�� */
    EXPECT_EQ(0x00, CSD_UL_GetQueue()->qlen);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();


}


TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_SendDataToDICC_001 )
{

    IMM_ZC_HEAD_STRU                    *pstULQueue;
    IMM_ZC_STRU                         *pstZcData;

    /* ������������ */
    pstULQueue                           = (IMM_ZC_HEAD_STRU *) PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                        sizeof(IMM_ZC_HEAD_STRU));

    pstZcData                             = (IMM_ZC_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                        sizeof(IMM_ZC_STRU));

    /* �������� */
    PS_MEM_SET(pstZcData, 0x00, sizeof(IMM_ZC_STRU));
    PS_MEM_SET(pstULQueue, 0x00, sizeof(IMM_ZC_HEAD_STRU));

    IMM_ZcQueueHeadInit(pstULQueue);

    CSD_UL_SetQueue(pstULQueue);

    CSD_UL_InsertQueueTail(CSD_UL_GetQueue(), pstZcData);

    EXPECT_EQ(0x01, CSD_UL_GetQueue()->qlen);

    MOCKER(VOS_SmP)
          .expects(exactly(1))
          .will(returnValue(VOS_OK));

    MOCKER(VOS_GetSlice)
          .will(returnValue(CSD_MAX_SLICE_CNT - 400));

    MOCKER(VOS_TaskDelay)
          .expects(never());

    MOCKER(DICC_GetChannelNodeCnt)
          .will(returnObjectList(0,1));

    MOCKER(DICC_TriggerChanDataTx)
           .expects(exactly(2));

    CSD_SetCallState(AT_CSD_CALL_STATE_ON);

    /* ���Ժ������� */
    CSD_UL_ProcDataTask();

    /* ƥ��ִ�н�� */

    //������ʱ����Ҫ����������λ�ü������
    EXPECT_EQ(0x00, CSD_UL_GetQueue()->qlen);
    GlobalMockObject::verify();


}


TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_SendDataToDICC_002 )
{
    IMM_ZC_HEAD_STRU                    *pstULQueue;
    IMM_ZC_STRU                         *pstZcData;

    /* ������������ */
    pstULQueue                           = (IMM_ZC_HEAD_STRU *) PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                        sizeof(IMM_ZC_HEAD_STRU));

    pstZcData                             = (IMM_ZC_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                        sizeof(IMM_ZC_STRU));

    /* �������� */
    PS_MEM_SET(pstZcData, 0x00, sizeof(IMM_ZC_STRU));
    PS_MEM_SET(pstULQueue, 0x00, sizeof(IMM_ZC_HEAD_STRU));

    IMM_ZcQueueHeadInit(pstULQueue);

    CSD_UL_SetQueue(pstULQueue);

    CSD_UL_InsertQueueTail(CSD_UL_GetQueue(), pstZcData);

    EXPECT_EQ(0x01, CSD_UL_GetQueue()->qlen);

    MOCKER(VOS_SmP)
          .expects(exactly(1))
          .will(returnValue(VOS_OK));

    MOCKER(VOS_GetSlice)
          .will(returnValue(CSD_MAX_SLICE_CNT - 400));

    MOCKER(VOS_TaskDelay)
          .expects(never());

    MOCKER(DICC_GetChannelNodeCnt)
          .expects(exactly(1))
          .will(returnValue(1));

    MOCKER(DICC_InsertChannelDataAction)
          .expects(exactly(1))
          .will(returnValue(DICC_ERR_BUTT));

    MOCKER(IMM_MemFree_Debug)
          .expects(exactly(1));

    MOCKER(DICC_TriggerChanDataTx)
           .expects(exactly(1));

    CSD_SetCallState(AT_CSD_CALL_STATE_ON);

    /* ���Ժ������� */
    CSD_UL_ProcDataTask();

    /* ƥ��ִ�н�� */

    //������ʱ����Ҫ����������λ�ü������
    EXPECT_EQ(0x00, CSD_UL_GetQueue()->qlen);
    GlobalMockObject::verify();


}


TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_SendDataToDICC_003 )
{
    IMM_ZC_HEAD_STRU                    *pstULQueue;
    IMM_ZC_STRU                         *pstZcData;

    /* ������������ */
    pstULQueue                           = (IMM_ZC_HEAD_STRU *) PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                        sizeof(IMM_ZC_HEAD_STRU));

    pstZcData                             = (IMM_ZC_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                        sizeof(IMM_ZC_STRU));

    /* �������� */
    PS_MEM_SET(pstZcData, 0x00, sizeof(IMM_ZC_STRU));
    PS_MEM_SET(pstULQueue, 0x00, sizeof(IMM_ZC_HEAD_STRU));

    IMM_ZcQueueHeadInit(pstULQueue);

    CSD_UL_SetQueue(pstULQueue);

    CSD_UL_InsertQueueTail(CSD_UL_GetQueue(), pstZcData);

    EXPECT_EQ(0x01, CSD_UL_GetQueue()->qlen);

    MOCKER(VOS_SmP)
          .expects(exactly(1))
          .will(returnValue(VOS_OK));

    MOCKER(VOS_GetSlice)
          .will(returnValue(CSD_MAX_SLICE_CNT - 400));

    MOCKER(VOS_TaskDelay)
          .expects(never());

    MOCKER(DICC_GetChannelNodeCnt)
          .will(returnValue(1));

    MOCKER(DICC_InsertChannelDataAction)
          .will(returnValue(DICC_OK));

    MOCKER(DICC_TriggerChanDataTx)
           .expects(exactly(1));

    CSD_SetCallState(AT_CSD_CALL_STATE_ON);

    /* ���Ժ������� */
    CSD_UL_ProcDataTask();

    /* ƥ��ִ�н�� */

    //������ʱ����Ҫ����������λ�ü������
    EXPECT_EQ(0x00, CSD_UL_GetQueue()->qlen);
    GlobalMockObject::verify();


}

TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_SendDataToDICC_004 )
{
    IMM_ZC_HEAD_STRU                    *pstULQueue;
    IMM_ZC_STRU                         *pstZcData;

    /* ������������ */
    pstULQueue                           = (IMM_ZC_HEAD_STRU *) PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                        sizeof(IMM_ZC_HEAD_STRU));

    pstZcData                             = (IMM_ZC_STRU *)PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                        sizeof(IMM_ZC_STRU));

    /* �������� */
    PS_MEM_SET(pstZcData, 0x00, sizeof(IMM_ZC_STRU));
    PS_MEM_SET(pstULQueue, 0x00, sizeof(IMM_ZC_HEAD_STRU));

    IMM_ZcQueueHeadInit(pstULQueue);

    CSD_UL_SetQueue(pstULQueue);

    CSD_UL_InsertQueueTail(CSD_UL_GetQueue(), pstZcData);

    EXPECT_EQ(0x01, CSD_UL_GetQueue()->qlen);

    MOCKER(VOS_SmP)
          .expects(exactly(1))
          .will(returnValue(VOS_OK));

    MOCKER(VOS_GetSlice)
          .will(returnValue(CSD_MAX_SLICE_CNT - 400));

    MOCKER(VOS_TaskDelay)
          .expects(never());

    MOCKER(DICC_GetChannelNodeCnt)
          .expects(exactly(1))
          .will(returnValue(1));

    MOCKER(DICC_InsertChannelDataAction)
          .expects(exactly(1))
          .will(returnValue(DICC_OK));

    MOCKER(DICC_TriggerChanDataTx)
           .expects(exactly(1))
           .will(returnValue(DICC_ERR_BUTT));

    CSD_SetCallState(AT_CSD_CALL_STATE_ON);

    /* ���Ժ������� */
    CSD_UL_ProcDataTask();

    /* ƥ��ִ�н�� */

    //������ʱ����Ҫ����������λ�ü������
    EXPECT_EQ(0x00, CSD_UL_GetQueue()->qlen);
    GlobalMockObject::verify();


}

TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_SendDataToDICC_005 )
{
    IMM_ZC_HEAD_STRU                         *pstULQueue;

    /* ������������ */
    pstULQueue                           = (IMM_ZC_HEAD_STRU *) PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                        sizeof(IMM_ZC_HEAD_STRU));

    /* �������� */
    PS_MEM_SET(pstULQueue, 0x00, sizeof(IMM_ZC_HEAD_STRU));

    IMM_ZcQueueHeadInit(pstULQueue);

    CSD_UL_SetQueue(pstULQueue);


    EXPECT_EQ(0x00, CSD_UL_GetQueue()->qlen);

    MOCKER(VOS_SmP)
          .expects(exactly(1))
          .will(returnValue(VOS_OK));

    MOCKER(VOS_GetSlice)
          .will(returnValue(CSD_MAX_SLICE_CNT - 400));

    MOCKER(VOS_TaskDelay)
          .expects(never());

    MOCKER(DICC_GetChannelNodeCnt)
          .will(returnValue(1));


    MOCKER(DICC_InsertChannelDataAction)
          .expects(never());

    MOCKER(DICC_TriggerChanDataTx)
           .expects(never());

    CSD_SetCallState(AT_CSD_CALL_STATE_ON);

    /* ���Ժ������� */
    CSD_UL_ProcDataTask();

    /* ƥ��ִ�н�� */

    //������ʱ����Ҫ����������λ�ü������
    EXPECT_EQ(0x00, CSD_UL_GetQueue()->qlen);
    GlobalMockObject::verify();

}

TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_SendDataToDICC_006 )
{
    IMM_ZC_HEAD_STRU                         *pstULQueue;

    /* ������������ */
    pstULQueue                           = (IMM_ZC_HEAD_STRU *) PS_MEM_ALLOC(ACPU_PID_CSD,
                                                                        sizeof(IMM_ZC_HEAD_STRU));

    /* �������� */
    PS_MEM_SET(pstULQueue, 0x00, sizeof(IMM_ZC_HEAD_STRU));

    IMM_ZcQueueHeadInit(pstULQueue);

    CSD_UL_SetQueue(pstULQueue);


    EXPECT_EQ(0x00, CSD_UL_GetQueue()->qlen);

    MOCKER(VOS_SmP)
          .expects(exactly(1))
          .will(returnValue(VOS_OK));

    MOCKER(VOS_GetSlice)
          .will(returnValue(CSD_MAX_SLICE_CNT - 400));

    MOCKER(VOS_TaskDelay)
          .expects(never());

    MOCKER(DICC_GetChannelNodeCnt)
          .will(returnValue(DICC_INVALID_VALUE));


    MOCKER(DICC_InsertChannelDataAction)
          .expects(never());

    MOCKER(DICC_TriggerChanDataTx)
           .expects(never());

    CSD_SetCallState(AT_CSD_CALL_STATE_ON);

    /* ���Ժ������� */
    CSD_UL_ProcDataTask();

    /* ƥ��ִ�н�� */

    //������ʱ����Ҫ����������λ�ü������
    EXPECT_EQ(0x00, CSD_UL_GetQueue()->qlen);
    GlobalMockObject::verify();

}


TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_CalcIsrSlice_001 )
{

    VOS_UINT32  ulRslt;

    /* ������������ */

    /* �������� */
    MOCKER(VOS_GetSlice)
          .will(returnValue(CSD_MAX_SLICE_CNT - 600));

    MOCKER(CSD_GetLastTxSlice)
          .will(returnValue(CSD_MAX_SLICE_CNT - 400));


    /* ���Ժ������� */


    ulRslt = CSD_UL_CalcIsrSlice();

    /* ƥ��ִ�н�� */
    EXPECT_EQ(CSD_MAX_SLICE_CNT - 200 , ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST_F( Test_CSD_UL_ProcMsg, TEST_CSD_UL_CalcIsrSlice_002 )
{
    VOS_UINT32  ulRslt;

    /* ������������ */

    /* �������� */
    MOCKER(VOS_GetSlice)
          .will(returnValue(CSD_MAX_SLICE_CNT - 200));

    MOCKER(CSD_GetLastTxSlice)
          .will(returnValue(CSD_MAX_SLICE_CNT - 400));


    /* ���Ժ������� */


    ulRslt = CSD_UL_CalcIsrSlice();

    /* ƥ��ִ�н�� */
    EXPECT_EQ(200 , ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}

#endif

#endif
