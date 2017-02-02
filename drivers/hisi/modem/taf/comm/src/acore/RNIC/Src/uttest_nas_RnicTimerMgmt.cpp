#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_nas_RnicTimerMgmt.h"


//�����������ã����������ùؼ���ʱ��Ҫ��ǰ׺ testing::
using namespace testing;

//˵��: ����������gtest+�������׺Ͳ����������ֲ�����Ϊ��
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

class Test_RNIC_InitAllTimers: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx     = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);       
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx     = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);       
    }
};


TEST_F(Test_RNIC_InitAllTimers, Test_RNIC_InitAllTimers_001)
{
    RNIC_TIMER_CTX_STRU                 astTimerCtx[RNIC_MAX_TIMER_NUM];   /* RNIC��ǰ�������еĶ�ʱ����Դ */
    VOS_UINT32                          i;

    RNIC_InitAllTimers(astTimerCtx);

    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        EXPECT_EQ(VOS_NULL_PTR, astTimerCtx[i].hTimer);
        EXPECT_EQ(TI_RNIC_TIMER_BUTT, astTimerCtx[i].enTimerId);
        EXPECT_EQ(RNIC_TIMER_STATUS_STOP, astTimerCtx[i].enTimerStatus);

    }
}
class Test_RNIC_StartTimer: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx     = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);       
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx     = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);       
    }

};


TEST_F(Test_RNIC_StartTimer, Test_RNIC_StartTimer_001)
{
    VOS_UINT32                          i;
    RNIC_TIMER_CTX_STRU                *pstRnicTimerCtx;

    pstRnicTimerCtx   =  RNIC_GetTimerAddr();
    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        pstRnicTimerCtx[i].enTimerStatus = RNIC_TIMER_STATUS_RUNING;
    }

    RNIC_StartTimer(TI_RNIC_DSFLOW_STATS_0, TI_RNIC_DSFLOW_STATS_LEN);

    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        EXPECT_NE(TI_RNIC_DSFLOW_STATS_0, pstRnicTimerCtx[i].enTimerId);
    }
}


TEST_F(Test_RNIC_StartTimer, Test_RNIC_StartTimer_002)
{
    VOS_UINT32                          i;
    RNIC_TIMER_CTX_STRU                 *pstRnicTimerCtx;

    pstRnicTimerCtx   =  RNIC_GetTimerAddr();
    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        pstRnicTimerCtx[i].enTimerStatus = RNIC_TIMER_STATUS_STOP;
    }

    MOCKER(V_StartRelTimer)
        .stubs()
        .will(returnValue(VOS_ERR));


    RNIC_StartTimer(TI_RNIC_DSFLOW_STATS_0, TI_RNIC_DSFLOW_STATS_LEN + VOS_TIMER_MAX_LENGTH);

    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        EXPECT_EQ(RNIC_TIMER_STATUS_STOP, pstRnicTimerCtx[i].enTimerStatus);
    }

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}



TEST_F(Test_RNIC_StartTimer, Test_RNIC_StartTimer_003)
{

    VOS_UINT32                          i;
    RNIC_TIMER_CTX_STRU                 *pstRnicTimerCtx;

    pstRnicTimerCtx   =  RNIC_GetTimerAddr();
    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        pstRnicTimerCtx[i].enTimerStatus = RNIC_TIMER_STATUS_STOP;
    }

    MOCKER(V_StartRelTimer)
        .stubs()
        .with(any(),eq(ACPU_PID_RNIC),eq(TI_RNIC_DEMAND_DIAL_DISCONNECT_LEN),any(),any(),any())
        .will(returnValue(VOS_OK));

    RNIC_StartTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT, TI_RNIC_DEMAND_DIAL_DISCONNECT_LEN);

    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, pstRnicTimerCtx[0].enTimerStatus);
    EXPECT_EQ(TI_RNIC_DEMAND_DIAL_DISCONNECT, pstRnicTimerCtx[0].enTimerId);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}



TEST_F(Test_RNIC_StartTimer, Test_RNIC_StartTimer_004)
{
    VOS_UINT32                          i;
    RNIC_TIMER_CTX_STRU                 *pstRnicTimerCtx;

    pstRnicTimerCtx   =  RNIC_GetTimerAddr();
    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        pstRnicTimerCtx[i].enTimerStatus = RNIC_TIMER_STATUS_STOP;
    }

    pstRnicTimerCtx[1].enTimerStatus = RNIC_TIMER_STATUS_RUNING;
    pstRnicTimerCtx[1].enTimerId     = TI_RNIC_DEMAND_DIAL_DISCONNECT;

    MOCKER(V_StartRelTimer)
        .expects(never());

    RNIC_StartTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT, TI_RNIC_DEMAND_DIAL_DISCONNECT_LEN);

    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, pstRnicTimerCtx[1].enTimerStatus);
    EXPECT_EQ(TI_RNIC_DEMAND_DIAL_DISCONNECT, pstRnicTimerCtx[1].enTimerId);


    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_RNIC_StopTimer: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx     = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);       
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx     = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);       
    }

};


TEST_F(Test_RNIC_StopTimer, Test_RNIC_StopTimer_001)
{
    VOS_UINT32                          i;
    RNIC_TIMER_CTX_STRU                 *pstRnicTimerCtx;

    pstRnicTimerCtx   =  RNIC_GetTimerAddr();
    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        pstRnicTimerCtx[i].enTimerStatus = RNIC_TIMER_STATUS_STOP;
    }

    RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT);

    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        EXPECT_EQ(RNIC_TIMER_STATUS_STOP, pstRnicTimerCtx[i].enTimerStatus);
    }

}


TEST_F(Test_RNIC_StopTimer, Test_RNIC_StopTimer_002)
{
    VOS_UINT32                          i;
    RNIC_TIMER_CTX_STRU                 *pstRnicTimerCtx;
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId;

    enTimerId = TI_RNIC_DEMAND_DIAL_DISCONNECT;

    pstRnicTimerCtx   =  RNIC_GetTimerAddr();
    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        pstRnicTimerCtx[i].enTimerStatus = RNIC_TIMER_STATUS_STOP;
    }

    pstRnicTimerCtx[2].hTimer        = (HTIMER)(&enTimerId);
    pstRnicTimerCtx[2].enTimerStatus = RNIC_TIMER_STATUS_RUNING;
    pstRnicTimerCtx[2].enTimerId     = TI_RNIC_DEMAND_DIAL_DISCONNECT;

    RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT);

    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        EXPECT_EQ(RNIC_TIMER_STATUS_STOP, pstRnicTimerCtx[i].enTimerStatus);
    }
}


class Test_RNIC_StopAllTimer: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx     = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);       
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx     = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);       
    }

};



TEST_F(Test_RNIC_StopAllTimer, Test_RNIC_StopAllTimer_001)
{
    VOS_UINT32                          i;
    RNIC_TIMER_CTX_STRU                 *pstRnicTimerCtx;

    pstRnicTimerCtx   =  RNIC_GetTimerAddr();
    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        pstRnicTimerCtx[i].enTimerStatus = RNIC_TIMER_STATUS_RUNING;
    }

    RNIC_StopAllTimer();

    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        EXPECT_EQ(RNIC_TIMER_STATUS_STOP, pstRnicTimerCtx[i].enTimerStatus);
    }

}


class Test_RNIC_GetTimerStatus: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
        RNIC_CTX_STRU                  *pstRnicCtx     = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);       
    }
    void TearDown()
    {
        RNIC_CTX_STRU                  *pstRnicCtx     = VOS_NULL_PTR;

        pstRnicCtx  = RNIC_GetRnicCtxAddr();

        RNIC_InitCtx(pstRnicCtx);       
    }

};


TEST_F(Test_RNIC_GetTimerStatus, Test_RNIC_GetTimerStatus_001)
{
    VOS_UINT32                          i;
    RNIC_TIMER_CTX_STRU                 *pstRnicTimerCtx;

    pstRnicTimerCtx   =  RNIC_GetTimerAddr();
    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        pstRnicTimerCtx[i].enTimerStatus = RNIC_TIMER_STATUS_STOP;
    }

    EXPECT_EQ(RNIC_TIMER_STATUS_STOP, RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_DISCONNECT));
}



TEST_F(Test_RNIC_GetTimerStatus, Test_RNIC_GetTimerStatus_002)
{
    VOS_UINT32                          i;
    RNIC_TIMER_CTX_STRU                 *pstRnicTimerCtx;

    pstRnicTimerCtx   =  RNIC_GetTimerAddr();
    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        pstRnicTimerCtx[i].enTimerStatus = RNIC_TIMER_STATUS_STOP;
    }

    pstRnicTimerCtx[0].enTimerStatus = RNIC_TIMER_STATUS_RUNING;
    pstRnicTimerCtx[0].enTimerId     = TI_RNIC_DEMAND_DIAL_DISCONNECT;

    MOCKER(V_GetRelTmRemainTime)
        .stubs()
        .will(returnValue(VOS_ERR));

    MOCKER(RNIC_StopTimer)
        .expects(exactly(1));

    EXPECT_EQ(RNIC_TIMER_STATUS_STOP, RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_DISCONNECT));
}



TEST_F(Test_RNIC_GetTimerStatus, Test_RNIC_GetTimerStatus_003)
{
    VOS_UINT32                          i;
    RNIC_TIMER_CTX_STRU                 *pstRnicTimerCtx;

    pstRnicTimerCtx   =  RNIC_GetTimerAddr();
    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        pstRnicTimerCtx[i].enTimerStatus = RNIC_TIMER_STATUS_STOP;
    }

    pstRnicTimerCtx[0].enTimerStatus = RNIC_TIMER_STATUS_RUNING;
    pstRnicTimerCtx[0].enTimerId     = TI_RNIC_DEMAND_DIAL_DISCONNECT;

    MOCKER(V_GetRelTmRemainTime)
        .stubs()
        .will(returnValue(VOS_OK));

    MOCKER(RNIC_StopTimer)
        .expects(never());

    EXPECT_EQ(RNIC_TIMER_STATUS_RUNING, RNIC_GetTimerStatus(TI_RNIC_DEMAND_DIAL_DISCONNECT));


}

#endif
