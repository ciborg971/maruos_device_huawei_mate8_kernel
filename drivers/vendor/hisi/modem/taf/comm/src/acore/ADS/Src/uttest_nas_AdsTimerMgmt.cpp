#include "gtest.h"
#include "llt_mockcpp.h"

#include "uttest_nas_AdsTimerMgmt.h"

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



#if (FEATURE_OFF == FEATURE_SKB_EXP)            

class Test_ADS_DL_StartAdqEmptyTimer: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        ADS_InitTiCtx();       
    }
    void TearDown()
    {
    }

};


TEST_F(Test_ADS_DL_StartAdqEmptyTimer, Test_ADS_DL_StartAdqEmptyTimer_001)
{
    VOS_UINT32                          i;
    ADS_TIMER_CTX_STRU                 *pstAdsTimerCtx;

    pstAdsTimerCtx   =  ADS_GetTiCtx();
    for ( i = 0 ; i < ADS_MAX_TIMER_NUM ; i++ )
    {
        pstAdsTimerCtx[i].enTimerStatus = ADS_TIMER_STATUS_RUNNING;
    }

    MOCKER(V_StartCallBackRelTimer)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));
	
    ADS_DL_StartAdqEmptyTimer();

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_ADS_DL_StartAdqEmptyTimer, Test_ADS_DL_StartAdqEmptyTimer_002)
{
    MOCKER(V_StartCallBackRelTimer)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    ADS_DL_StartAdqEmptyTimer();

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
#endif


class Test_ADS_StartTimer: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        ADS_InitTiCtx();       
    }
    void TearDown()
    {
    }

};


TEST_F(Test_ADS_StartTimer, Test_ADS_StartTimer_001)
{
    VOS_UINT32                          i;
    ADS_TIMER_CTX_STRU                 *pstAdsTimerCtx;

    pstAdsTimerCtx   =  ADS_GetTiCtx();
    for ( i = 0 ; i < ADS_MAX_TIMER_NUM ; i++ )
    {
        pstAdsTimerCtx[i].enTimerStatus = ADS_TIMER_STATUS_RUNNING;
    }

    ADS_StartTimer(ACPU_PID_ADS_UL,TI_ADS_UL_SEND, TI_ADS_UL_SEND_LEN);

}


TEST_F(Test_ADS_StartTimer, Test_ADS_StartTimer_002)
{
    VOS_UINT32                          i;
    ADS_TIMER_CTX_STRU                 *pstAdsTimerCtx;

    pstAdsTimerCtx   =  ADS_GetTiCtx();
    for ( i = 0 ; i < ADS_MAX_TIMER_NUM ; i++ )
    {
        pstAdsTimerCtx[i].enTimerStatus = ADS_TIMER_STATUS_STOP;
    }

    MOCKER(V_StartRelTimer)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));


    ADS_StartTimer(ACPU_PID_ADS_UL,TI_ADS_UL_SEND, TI_ADS_UL_SEND_LEN + VOS_TIMER_MAX_LENGTH);

    for ( i = 0 ; i < ADS_MAX_TIMER_NUM ; i++ )
    {
        EXPECT_EQ(ADS_TIMER_STATUS_STOP, pstAdsTimerCtx[i].enTimerStatus);
    }

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}



TEST_F(Test_ADS_StartTimer, Test_ADS_StartTimer_003)
{

    VOS_UINT32                          i;
    ADS_TIMER_CTX_STRU                 *pstAdsTimerCtx;

    pstAdsTimerCtx   =  ADS_GetTiCtx();
    for ( i = 0 ; i < ADS_MAX_TIMER_NUM ; i++ )
    {
        pstAdsTimerCtx[i].enTimerStatus = ADS_TIMER_STATUS_STOP;
    }

    MOCKER(V_StartRelTimer)
        .stubs()
        .with(any(),eq(ACPU_PID_ADS_UL),eq((VOS_UINT32)TI_ADS_UL_SEND_LEN))
        .will(returnValue((VOS_UINT32)VOS_OK));

    ADS_StartTimer(ACPU_PID_ADS_UL,TI_ADS_UL_SEND, TI_ADS_UL_SEND_LEN);

    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, pstAdsTimerCtx[0].enTimerStatus);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}



TEST_F(Test_ADS_StartTimer, Test_ADS_StartTimer_004)
{
    VOS_UINT32                          i;
    ADS_TIMER_CTX_STRU                 *pstAdsTimerCtx;

    pstAdsTimerCtx   =  ADS_GetTiCtx();
    for ( i = 0 ; i < ADS_MAX_TIMER_NUM ; i++ )
    {
        pstAdsTimerCtx[i].enTimerStatus = ADS_TIMER_STATUS_STOP;
    }

    pstAdsTimerCtx[TI_ADS_UL_SEND].enTimerStatus = ADS_TIMER_STATUS_RUNNING;

    MOCKER(V_StartRelTimer)
        .expects(never());

    ADS_StartTimer(ACPU_PID_ADS_UL,TI_ADS_UL_SEND, TI_ADS_UL_SEND_LEN);

    EXPECT_EQ(ADS_TIMER_STATUS_RUNNING, pstAdsTimerCtx[TI_ADS_UL_SEND].enTimerStatus);


    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}




TEST_F(Test_ADS_StartTimer, Test_ADS_StartTimer_005)
{
    VOS_UINT32                          i;
    ADS_TIMER_CTX_STRU                 *pstAdsTimerCtx;

    pstAdsTimerCtx   =  ADS_GetTiCtx();
    for ( i = 0 ; i < ADS_MAX_TIMER_NUM ; i++ )
    {
        pstAdsTimerCtx[i].enTimerStatus = ADS_TIMER_STATUS_STOP;
    }

    MOCKER(V_StartRelTimer)
        .expects(never());

    ADS_StartTimer(ACPU_PID_ADS_UL,TI_ADS_UL_SEND, 0);

    EXPECT_EQ(ADS_TIMER_STATUS_STOP, pstAdsTimerCtx[1].enTimerStatus);


    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

class Test_ADS_StopTimer: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        ADS_InitTiCtx();           
    }
    void TearDown()
    {
    }

};


TEST_F(Test_ADS_StopTimer, Test_ADS_StopTimer_001)
{
    VOS_UINT32                          i;
    ADS_TIMER_CTX_STRU                 *pstAdsTimerCtx;

    pstAdsTimerCtx   =  ADS_GetTiCtx();
    for ( i = 0 ; i < ADS_MAX_TIMER_NUM ; i++ )
    {
        pstAdsTimerCtx[i].enTimerStatus = ADS_TIMER_STATUS_STOP;
    }

    ADS_StopTimer(ACPU_PID_ADS_UL, TI_ADS_UL_SEND, ADS_TIMER_STOP_CAUSE_USER);

    for ( i = 0 ; i < ADS_MAX_TIMER_NUM ; i++ )
    {
        EXPECT_EQ(ADS_TIMER_STATUS_STOP, pstAdsTimerCtx[i].enTimerStatus);
    }

}


TEST_F(Test_ADS_StopTimer, Test_ADS_StopTimer_002)
{
    VOS_UINT32                          i;
    ADS_TIMER_CTX_STRU                 *pstAdsTimerCtx;
    HTIMER                              hTimer;
    ADS_TIMER_ID_ENUM_UINT32            enTimerId;

    enTimerId = TI_ADS_UL_SEND;

    pstAdsTimerCtx   =  ADS_GetTiCtx();
    for ( i = 0 ; i < ADS_MAX_TIMER_NUM ; i++ )
    {
        pstAdsTimerCtx[i].enTimerStatus = ADS_TIMER_STATUS_STOP;
    }

    pstAdsTimerCtx[TI_ADS_UL_SEND].hTimer        = (HTIMER)(&enTimerId);
    pstAdsTimerCtx[TI_ADS_UL_SEND].enTimerStatus = ADS_TIMER_STATUS_RUNNING;

    MOCKER(V_StopRelTimer)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    ADS_StopTimer(ACPU_PID_ADS_UL, TI_ADS_UL_SEND, ADS_TIMER_STOP_CAUSE_USER);

    for ( i = 0 ; i < ADS_MAX_TIMER_NUM ; i++ )
    {
        EXPECT_EQ(ADS_TIMER_STATUS_STOP, pstAdsTimerCtx[i].enTimerStatus);
    }
}


class Test_ADS_GetTimerStatus: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        ADS_InitTiCtx();      
    }
    void TearDown()
    {
    }

};


TEST_F(Test_ADS_GetTimerStatus, Test_ADS_GetTimerStatus_001)
{
    VOS_UINT32                          i;
    ADS_TIMER_CTX_STRU                 *pstAdsTiCtx;

    pstAdsTiCtx   =  ADS_GetTiCtx();

    pstAdsTiCtx[0].enTimerStatus = ADS_TIMER_STATUS_STOP;

    EXPECT_EQ(ADS_TIMER_STATUS_STOP, ADS_GetTimerStatus(ACPU_PID_ADS_UL,TI_ADS_UL_SEND));
}

