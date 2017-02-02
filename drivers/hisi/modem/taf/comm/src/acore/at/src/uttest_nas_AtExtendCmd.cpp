#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_AtExtendCmd.h"

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

class Test_At_TestCpolPara: public ::testing::Test
{
public:
    VOS_UINT8       ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stElement;
    VOS_UINT8                           szCmdName[32];

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                       = 0;

        VOS_StrCpy((VOS_CHAR*)szCmdName,"+cpol");
        g_stParseContext[ucIndex].pstCmdElement = &stElement;
        stElement.pszCmdName                    = szCmdName;

        gucAtParaIndex                = 0;
        gastAtParaList[0].usParaLen   = 0;
        gastAtParaList[0].ulParaValue = 0;
        gastAtParaList[1].usParaLen   = 0;
        gastAtParaList[1].ulParaValue = 0;
        AT_GetModemSsCtxAddrFromClientId(ucIndex)->ucSalsType                 = 0;
        g_stATParseCmd.ucCmdOptType   = AT_CMD_OPT_BUTT;
        AT_GetModemNetCtxAddrFromClientId(ucIndex)->ucRoamFeature              = AT_ROAM_FEATURE_OFF;
    }

    void TearDown()
    {
        ucIndex                       = 0;
        gucAtParaIndex                = 0;
        gastAtParaList[0].usParaLen   = 0;
        gastAtParaList[0].ulParaValue = 0;
        gastAtParaList[1].usParaLen   = 0;
        gastAtParaList[1].ulParaValue = 0;
        AT_GetModemSsCtxAddrFromClientId(ucIndex)->ucSalsType                 = 0;
        g_stATParseCmd.ucCmdOptType   = AT_CMD_OPT_BUTT;
        AT_GetModemNetCtxAddrFromClientId(ucIndex)->ucRoamFeature              = AT_ROAM_FEATURE_OFF;
    }
};

TEST_F(Test_At_TestCpolPara,Test_At_TestCpolPara_001)
{
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .will(returnValue(TAF_FAILURE));

    EXPECT_EQ(AT_ERROR, At_TestCpolPara(ucIndex));

    GlobalMockObject::verify();
}

TEST_F(Test_At_TestCpolPara,Test_At_TestCpolPara_002)
{
    MOCKER(MN_FillAndSndAppReqMsg)
        .stubs()
        .will(returnValue(TAF_SUCCESS));

    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, At_TestCpolPara(ucIndex));

    GlobalMockObject::verify();
}


class Test_At_TestCgeqnegPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        gastAtClientTab[0].CmdCurrentOpt = AT_CMD_INVALID;
    }
    void TearDown()
    {

    }
};


TEST_F(Test_At_TestCgeqnegPara,Test_At_TestCgeqnegPara_001)
{
    // ��������

    //������ʼ��

    gastAtClientTab[0].CmdCurrentOpt = AT_CMD_INVALID;


    // MOCKER����;
    MOCKER(TAF_PS_GetPdpContextState)
           .stubs()
           .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(At_StartTimer)
           .stubs()
           .will(returnValue((VOS_UINT32)AT_SUCCESS));

    // ���ñ��⺯��
    At_TestCgeqnegPara(0);

    // ִ�м��
    EXPECT_EQ(AT_CMD_CGEQNEG_TEST, gastAtClientTab[0].CmdCurrentOpt);

    GlobalMockObject::verify();
}

