#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_AtMntn.h"


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



class Test_AT_MNTN_TraceCmdResult: public ::testing::Test
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

TEST_F(Test_AT_MNTN_TraceCmdResult, Test_AT_MNTN_TraceCmdResult_01)
{
    const char          cWarning[] = "At_HookResult:ERROR:Alloc Mem Fail.";
    TAF_UINT8 ucIndex = 0;
    TAF_UINT8          aucCmdString[] = "at+cimi";
    TAF_UINT8 *pData = VOS_NULL_PTR;
    TAF_UINT16 usLen;

    //MOCKER(DIAG_LogReport)
    //    .with(any(), any(), any(), any(), any(), mirror(cWarning,strlen(cWarning) + 1));

    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((void *)VOS_NULL_PTR));

    MOCKER(DIAG_TraceReport)
        .expects(never())
        .will(returnValue((VOS_UINT32)VOS_OK));

    pData = aucCmdString;
    usLen = sizeof(aucCmdString);

    AT_MNTN_TraceCmdResult(ucIndex, pData, usLen);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_MNTN_TraceCmdResult, Test_AT_MNTN_TraceCmdResult_02)
{
    TAF_UINT8 ucIndex = 0;
    TAF_UINT8          aucCmdString[] = "at+cimi";
    TAF_UINT8 *pData = VOS_NULL_PTR;
    TAF_UINT16 usLen;

    MOCKER(DIAG_TraceReport)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    pData = aucCmdString;
    usLen = sizeof(aucCmdString);

    AT_MNTN_TraceCmdResult(ucIndex, pData, usLen);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_AT_MNTN_TraceCmdBuffer: public ::testing::Test
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

TEST_F(Test_AT_MNTN_TraceCmdBuffer, Test_AT_MNTN_TraceCmdBuffer_01)
{
    const char          cWarning[] = "AT_MNTN_TraceCmdBuffer:ERROR:Alloc Mem Fail.";
    TAF_UINT8 ucIndex = 0;
    TAF_UINT8          aucCmdString[] = "at+cimi";
    TAF_UINT8 *pData = VOS_NULL_PTR;
    TAF_UINT16 usLen;

    MOCKER(DIAG_LogReport)
        .stubs()
        .with(any(), any(), any(), any(), any(), mirror(cWarning,strlen(cWarning) + 1));

    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((void *)VOS_NULL_PTR));

    MOCKER(DIAG_TraceReport)
        .expects(never())
        .will(returnValue((VOS_UINT32)VOS_OK));

    pData = aucCmdString;
    usLen = sizeof(aucCmdString);

    AT_MNTN_TraceCmdBuffer(ucIndex, pData, usLen);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_MNTN_TraceCmdBuffer, Test_AT_MNTN_TraceCmdBuffer_02)
{
    TAF_UINT8 ucIndex = 0;
    TAF_UINT8          aucCmdString[] = "at+cimi";
    TAF_UINT8 *pData = VOS_NULL_PTR;
    TAF_UINT16 usLen;

    MOCKER(DIAG_TraceReport)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    pData = aucCmdString;
    usLen = sizeof(aucCmdString);

    AT_MNTN_TraceCmdBuffer(ucIndex, pData, usLen);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_AT_ShowResetStatsInfo: public ::testing::Test
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


TEST_F(Test_AT_ShowResetStatsInfo, Test_AT_ShowResetStatsInfo_001)
{
    //��������

    //������ʼ��

    //���ȫ�ֱ�����ʼ��

    //MOCKER����

    //���ñ��⺯��
    AT_ShowResetStatsInfo();

    //ִ�м��

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_AT_Help: public ::testing::Test
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


TEST_F(Test_AT_Help, Test_AT_Help_001)
{
    // ��������

    // ������ʼ��

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    AT_Help();

    // ִ�м��

    GlobalMockObject::verify();
}


class Test_AT_ShowPsEntityInfo: public ::testing::Test
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


TEST_F(Test_AT_ShowPsEntityInfo, Test_AT_ShowPsEntityInfo_001)
{
    // ��������

    // ������ʼ��

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    AT_ShowPsEntityInfo(0);

    // ִ�м��

    GlobalMockObject::verify();
}


class Test_AT_InitHsUartStats: public ::testing::Test
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


TEST_F(Test_AT_InitHsUartStats, Test_AT_InitHsUartStats_001)
{
    g_stAtStatsInfo.stHsUartStats.ucReadNvFailNum = 1;
    AT_InitHsUartStats();

    EXPECT_EQ(0, g_stAtStatsInfo.stHsUartStats.ucReadNvFailNum);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_AT_ShowHsUartNvStats: public ::testing::Test
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


TEST_F(Test_AT_ShowHsUartNvStats, Test_AT_ShowHsUartNvStats_001)
{
    AT_ShowHsUartNvStats();

    GlobalMockObject::verify();
}


class Test_AT_ShowHsUartIoctlStats: public ::testing::Test
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


TEST_F(Test_AT_ShowHsUartIoctlStats, Test_AT_ShowHsUartIoctlStats_001)
{
    AT_ShowHsUartIoctlStats();
    GlobalMockObject::verify();
}


class Test_AT_ShowHsUartDataStats: public ::testing::Test
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


TEST_F(Test_AT_ShowHsUartDataStats, Test_AT_ShowHsUartDataStats_001)
{
    AT_ShowHsUartDataStats();

    GlobalMockObject::verify();
}


class Test_AT_ShowHsUartConfigInfo: public ::testing::Test
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


TEST_F(Test_AT_ShowHsUartConfigInfo, Test_AT_ShowHsUartConfigInfo_001)
{
    // ��������
    AT_UART_LINE_CTRL_STRU             *pstLineCtrl = VOS_NULL_PTR;
    AT_UART_FLOW_CTRL_STRU             *pstFlowCtrl = VOS_NULL_PTR;
    AT_UART_RI_CFG_STRU                *pstUartRiCfgInfo = VOS_NULL_PTR;
    AT_UART_PHY_CFG_STRU               *pstUartPhyCfgInfo = VOS_NULL_PTR;
    AT_UART_FORMAT_PARAM_STRU          *pstFormatParam = VOS_NULL_PTR;

    // ������ʼ��
    pstLineCtrl       = AT_GetUartLineCtrlInfo();
    memset(pstLineCtrl, 0, sizeof(AT_UART_LINE_CTRL_STRU));
    pstFlowCtrl       = AT_GetUartFlowCtrlInfo();
    memset(pstFlowCtrl, 0, sizeof(AT_UART_FLOW_CTRL_STRU));
    pstUartRiCfgInfo  = AT_GetUartRiCfgInfo();
    memset(pstUartRiCfgInfo, 0, sizeof(AT_UART_RI_CFG_STRU));
    pstUartPhyCfgInfo = AT_GetUartPhyCfgInfo();
    memset(pstUartPhyCfgInfo, 0, sizeof(AT_UART_PHY_CFG_STRU));
    pstFormatParam    = AT_HSUART_GetFormatParam(pstUartPhyCfgInfo->stFrame.enFormat);
    memset(pstFormatParam, 0, sizeof(AT_UART_FORMAT_PARAM_STRU));

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    AT_ShowHsUartConfigInfo();

    // ִ�м��

    GlobalMockObject::verify();
}


class Test_AT_InitModemStats: public ::testing::Test
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


TEST_F(Test_AT_InitModemStats, Test_AT_InitModemStats_001)
{
    // ��������

    // ������ʼ��

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    AT_InitModemStats();

    // ִ�м��

    GlobalMockObject::verify();
}


class Test_AT_ShowModemDataStats: public ::testing::Test
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


TEST_F(Test_AT_ShowModemDataStats, Test_AT_ShowModemDataStats_001)
{
    // ��������

    // ������ʼ��

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    AT_ShowModemDataStats();

    // ִ�м��

    GlobalMockObject::verify();
}


class Test_AT_MNTN_TraceEvent: public ::testing::Test
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


TEST_F(Test_AT_MNTN_TraceEvent, Test_AT_MNTN_TraceEvent_001)
{
    // ��������
    AT_MNTN_MSC_STRU                    stMntnMsc;

    // ������ʼ��

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(DIAG_TraceReport)
        .stubs()
        .will(returnValue(VOS_ERR));

    // ���ñ��⺯��
    AT_MNTN_TraceEvent(&stMntnMsc);

    // ִ�м��

    GlobalMockObject::verify();
}

