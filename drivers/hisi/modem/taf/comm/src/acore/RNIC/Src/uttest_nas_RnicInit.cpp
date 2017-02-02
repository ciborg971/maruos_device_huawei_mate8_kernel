/*****************************************************************************
1 ͷ�ļ�����
*****************************************************************************/
#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_nas_RnicInit.h"


//�����������ã����������ùؼ���ʱ��Ҫ��ǰ׺ testing::
using namespace testing;

#if 0
/*****************************************************************************
2 ����ʵ��
*****************************************************************************/


class Test_RNIC_PidInit: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
    }
    void TearDown()
    {
    }
};


TEST_F(Test_RNIC_PidInit, Test_RNIC_PidInit_001)
{
    VOS_UINT32                          ulRst;
    VOS_INIT_PHASE_DEFINE               enPhase;
    RNIC_CTX_STRU                      *pstRnicCtx;

    /* ������ʼ�� */
    enPhase = VOS_IP_LOAD_CONFIG;

    /* ׮���� */

    /* �������� */

    /* ������ں��� */
    ulRst = RNIC_PidInit(enPhase);

    /* ��ȡ��� */
    pstRnicCtx = RNIC_GetRnicCtxAddr();

    /* ����ƥ�� */
    EXPECT_EQ(VOS_OK, ulRst);
    EXPECT_EQ(AT_RNIC_DIAL_MODE_MANUAL, pstRnicCtx->stDialMode.enDialMode);
    EXPECT_EQ(RNIC_DIAL_DEMA_IDLE_TIME, pstRnicCtx->stDialMode.ulIdleTime);
    EXPECT_EQ(TI_RNIC_DSFLOW_STATS_0, pstRnicCtx->astSpecCtx[0].enTiDsFlowStats);
    EXPECT_EQ(TI_RNIC_DSFLOW_STATS_1, pstRnicCtx->astSpecCtx[1].enTiDsFlowStats);
    EXPECT_EQ(TI_RNIC_DSFLOW_STATS_2, pstRnicCtx->astSpecCtx[2].enTiDsFlowStats);
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    EXPECT_EQ(MODEM_ID_1, pstRnicCtx->astSpecCtx[3].enModemId);
#endif
    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
    
}


TEST_F(Test_RNIC_PidInit, Test_RNIC_PidInit_002)
{
    VOS_UINT32                          ulRst;
    VOS_INIT_PHASE_DEFINE               enPhase;

    /* ������ʼ�� */
    enPhase = VOS_IP_FARMALLOC;

    /* ׮���� */
    MOCKER(RNIC_GetRnicCtxAddr)
        .expects(never());
    
    MOCKER(RNIC_InitCtx)
        .expects(never());

    /* �������� */

    /* ������ں��� */
    ulRst = RNIC_PidInit(enPhase);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(VOS_OK, ulRst);

    enPhase = VOS_IP_BUTT;
    ulRst = RNIC_PidInit(enPhase);
    EXPECT_EQ(VOS_OK, ulRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST_F(Test_RNIC_PidInit, Test_RNIC_PidInit_003)
{
    VOS_UINT32                          ulRst;
    VOS_INIT_PHASE_DEFINE               enPhase;
    RNIC_CTX_STRU                      *pstRnicCtx;

    /* ������ʼ�� */
    enPhase = VOS_IP_LOAD_CONFIG;

    /* ׮���� */
    MOCKER(VOS_SmBCreate)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));

    /* �������� */

    /* ������ں��� */
    ulRst = RNIC_PidInit(enPhase);

    /* ��ȡ��� */
    pstRnicCtx = RNIC_GetRnicCtxAddr();

    /* ����ƥ�� */
    EXPECT_EQ(VOS_OK, ulRst);
    EXPECT_EQ(AT_RNIC_DIAL_MODE_MANUAL, pstRnicCtx->stDialMode.enDialMode);
    EXPECT_EQ(RNIC_DIAL_DEMA_IDLE_TIME, pstRnicCtx->stDialMode.ulIdleTime);
    EXPECT_EQ(TI_RNIC_DSFLOW_STATS_0, pstRnicCtx->astSpecCtx[0].enTiDsFlowStats);
    EXPECT_EQ(TI_RNIC_DSFLOW_STATS_1, pstRnicCtx->astSpecCtx[1].enTiDsFlowStats);
    EXPECT_EQ(TI_RNIC_DSFLOW_STATS_2, pstRnicCtx->astSpecCtx[2].enTiDsFlowStats);
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    EXPECT_EQ(MODEM_ID_1, pstRnicCtx->astSpecCtx[3].enModemId);
#endif
    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_RNIC_FidInit: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
    }
    void TearDown()
    {
    }
};


TEST_F(Test_RNIC_FidInit, Test_RNIC_FidInit_001)
{
    VOS_UINT32                          ulRst;
    VOS_INIT_PHASE_DEFINE               enPhase;

    /* ������ʼ�� */
    enPhase = VOS_IP_LOAD_CONFIG;

    /* ׮���� */
    MOCKER(VOS_RegisterPIDInfo)
        .expects(exactly(1))
        .with(eq(ACPU_PID_RNIC), eq((VOS_UINT_PTR)RNIC_PidInit), eq((VOS_UINT_PTR)RNIC_ProcMsg))
        .will(returnValue(VOS_OK));

    MOCKER(VOS_RegisterMsgTaskPrio)
        .expects(exactly(1))
        .with(eq(ACPU_FID_RNIC), eq(VOS_PRIORITY_P6))
        .will(returnValue(VOS_OK));

    /* �������� */

    /* ������ں��� */
    ulRst = RNIC_FidInit(enPhase);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(VOS_OK, ulRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST_F(Test_RNIC_FidInit, Test_RNIC_FidInit_002)
{
    VOS_UINT32                          ulRst;
    VOS_INIT_PHASE_DEFINE               enPhase;

    /* ������ʼ�� */
    enPhase = VOS_IP_LOAD_CONFIG;

    /* ׮���� */
    MOCKER(VOS_RegisterPIDInfo)
        .expects(exactly(1))
        .with(eq(ACPU_PID_RNIC), eq((VOS_UINT_PTR)RNIC_PidInit), eq((VOS_UINT_PTR)RNIC_ProcMsg))
        .will(returnValue(VOS_ERR));

    /* �������� */

    /* ������ں��� */
    ulRst = RNIC_FidInit(enPhase);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(VOS_ERR, ulRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST_F(Test_RNIC_FidInit, Test_RNIC_FidInit_003)
{
    VOS_UINT32                          ulRst;
    VOS_INIT_PHASE_DEFINE               enPhase;

    /* ������ʼ�� */
    enPhase = VOS_IP_LOAD_CONFIG;

    /* ׮���� */
    MOCKER(VOS_RegisterPIDInfo)
        .expects(exactly(1))
        .with(eq(ACPU_PID_RNIC), eq((VOS_UINT_PTR)RNIC_PidInit), eq((VOS_UINT_PTR)RNIC_ProcMsg))
        .will(returnValue(VOS_OK));

    MOCKER(VOS_RegisterMsgTaskPrio)
        .expects(exactly(1))
        .with(eq(ACPU_FID_RNIC), eq(VOS_PRIORITY_P6))
        .will(returnValue(VOS_ERR));

    /* �������� */

    /* ������ں��� */
    ulRst = RNIC_FidInit(enPhase);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(VOS_ERR, ulRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST_F(Test_RNIC_FidInit, Test_RNIC_FidInit_004)
{
    VOS_UINT32                          ulRst;
    VOS_INIT_PHASE_DEFINE               enPhase;

    /* ������ʼ�� */
    enPhase = VOS_IP_FARMALLOC;

    /* ׮���� */
    MOCKER(VOS_RegisterPIDInfo)
        .expects(never());
    
    /* �������� */

    /* ������ں��� */
    ulRst = RNIC_FidInit(enPhase);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(VOS_OK, ulRst);

    enPhase = VOS_IP_BUTT;
    ulRst = RNIC_FidInit(enPhase);
    EXPECT_EQ(VOS_OK, ulRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


class Test_RNIC_CCpuResetCallback: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();
    }
    void TearDown()
    {
    }
};


TEST_F(Test_RNIC_CCpuResetCallback, Test_RNIC_CCpuResetCallback_001)
{
    VOS_UINT32                          ulRst;

    /* ������ʼ�� */

    /* ׮���� */
    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue(VOS_NULL_PTR));

    /* �������� */

    /* ������ں��� */
    ulRst = RNIC_CCpuResetCallback(MDRV_RESET_CB_BEFORE, 0);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(VOS_ERROR, ulRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
    
}


TEST_F(Test_RNIC_CCpuResetCallback, Test_RNIC_CCpuResetCallback_002)
{
    VOS_UINT32                          ulRst;

    /* ������ʼ�� */

    /* ׮���� */
    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));

    /* �������� */

    /* ������ں��� */
    ulRst = RNIC_CCpuResetCallback(MDRV_RESET_CB_BEFORE, 0);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(VOS_ERROR, ulRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
    
}


TEST_F(Test_RNIC_CCpuResetCallback, Test_RNIC_CCpuResetCallback_003)
{
    VOS_UINT32                          ulRst;

    /* ������ʼ�� */

    /* ׮���� */
    MOCKER(VOS_SmP)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));

    /* �������� */

    /* ������ں��� */
    ulRst = RNIC_CCpuResetCallback(MDRV_RESET_CB_BEFORE, 0);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(VOS_ERROR, ulRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
    
}



TEST_F(Test_RNIC_CCpuResetCallback, Test_RNIC_CCpuResetCallback_004)
{
    VOS_UINT32                          ulRst;

    /* ������ʼ�� */

    /* ׮���� */
    MOCKER(VOS_SmP)
        .expects(exactly(1))
        .will(returnValue(VOS_OK));

    /* �������� */

    /* ������ں��� */
    ulRst = RNIC_CCpuResetCallback(MDRV_RESET_CB_BEFORE, 0);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(VOS_OK, ulRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
    
}


TEST_F(Test_RNIC_CCpuResetCallback, Test_RNIC_CCpuResetCallback_005)
{
    VOS_UINT32                          ulRst;

    /* ������ʼ�� */

    /* ׮���� */

    /* �������� */

    /* ������ں��� */
    ulRst = RNIC_CCpuResetCallback(MDRV_RESET_CB_AFTER, 0);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(VOS_OK, ulRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
    
}


TEST_F(Test_RNIC_CCpuResetCallback, Test_RNIC_CCpuResetCallback_006)
{
    VOS_UINT32                          ulRst;

    /* ������ʼ�� */

    /* ׮���� */

    /* �������� */

    /* ������ں��� */
    ulRst = RNIC_CCpuResetCallback(MDRV_RESET_CB_INVALID, 0);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(VOS_ERROR, ulRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
    
}

#endif
