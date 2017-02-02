#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_AtCmdFtmProc.h"

//�����������ã����������ùؼ���ʱ��Ҫ��ǰ׺ testing::
using namespace testing;

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_AT_CMD_FTM_PROC_C


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

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

AT_PAR_CMD_ELEMENT_STRU             gstLogPortCmdInfo = {AT_CMD_LOGPORT,
                                                        At_SetLogPortPara,       AT_NOT_SET_TIME,  At_QryLogPortPara,   AT_NOT_SET_TIME,    At_CmdTestProcOK,    AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,        AT_NOT_SET_TIME,
                                                        AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
                                                        (VOS_UINT8*)"^LOGPORT",  VOS_NULL_PTR};


class Test_At_SetLogPortPara: public ::testing::Test
{
public:

    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitPort();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_At_SetLogPortPara,Test_At_SetLogPortPara_001)
{
    /*��������*/
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    /*���ر�����ʼ��*/
    ucIndex = AT_CLIENT_ID_APP1;

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_READ_CMD;

    /*������׮*/

    /*���ñ��⺯�� */
    ulRet = At_SetLogPortPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_At_SetLogPortPara,Test_At_SetLogPortPara_002)
{
    /*��������*/
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    /*���ر�����ʼ��*/
    ucIndex = AT_CLIENT_ID_APP1;

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 0;

    /*������׮*/

    /*���ñ��⺯�� */
    ulRet = At_SetLogPortPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_At_SetLogPortPara,Test_At_SetLogPortPara_003)
{
    /*��������*/
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    /*���ر�����ʼ��*/
    ucIndex = AT_CLIENT_ID_APP1;
    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 1;
    gastAtParaList[0].ulParaValue = 0;

    /*������׮*/
    MOCKER(PPM_LogPortSwitch)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    /*���ñ��⺯�� */
    ulRet = At_SetLogPortPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();
}



TEST_F(Test_At_SetLogPortPara,Test_At_SetLogPortPara_004)
{
    /*��������*/
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    /*���ر�����ʼ��*/
    ucIndex = AT_CLIENT_ID_APP1;

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 1;
    gastAtParaList[0].ulParaValue = 1;

    /*������׮*/
    MOCKER(PPM_LogPortSwitch)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    /*���ñ��⺯�� */
    ulRet = At_SetLogPortPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_At_SetLogPortPara,Test_At_SetLogPortPara_005)
{
    /*��������*/
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    /*���ر�����ʼ��*/
    ucIndex = AT_CLIENT_ID_APP1;

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 1;
    gastAtParaList[0].ulParaValue = 0;

    /*������׮*/
    MOCKER(PPM_LogPortSwitch)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    /*���ñ��⺯�� */
    ulRet = At_SetLogPortPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}


class Test_At_QryLogPortPara: public ::testing::Test
{
public:

    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitPort();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_At_QryLogPortPara,Test_At_QryLogPortPara_001)
{
    /*��������*/
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulOmLogPort;
    VOS_CHAR                           *pcExpactedStr;

    /*���ر�����ʼ��*/
    pcExpactedStr   = "^LOGPORT: 0";
    ucIndex = AT_CLIENT_ID_APP1;
    g_stParseContext[ucIndex].pstCmdElement = &gstLogPortCmdInfo;
    ulOmLogPort = COMM_LOG_PORT_USB;

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_READ_CMD;

    /*������׮*/
    MOCKER(PPM_QueryLogPort)
        .expects(exactly(1))
        .with(outBoundP((VOS_UINT32 *)&ulOmLogPort, sizeof(ulOmLogPort)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    /*���ñ��⺯�� */
    ulRet = At_QryLogPortPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_OK, ulRet);
    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}


TEST_F(Test_At_QryLogPortPara,Test_At_QryLogPortPara_002)
{
    /*��������*/
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulOmLogPort;
    VOS_CHAR                           *pcExpactedStr;

    /*���ر�����ʼ��*/
    pcExpactedStr   = "^LOGPORT: 1";
    ucIndex = AT_CLIENT_ID_APP1;
    g_stParseContext[ucIndex].pstCmdElement = &gstLogPortCmdInfo;
    ulOmLogPort = COMM_LOG_PORT_VCOM;

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_READ_CMD;

    /*������׮*/
    MOCKER(PPM_QueryLogPort)
        .stubs()
        .with(outBoundP((VOS_UINT32 *)&ulOmLogPort, sizeof(ulOmLogPort)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    /*���ñ��⺯�� */
    ulRet = At_QryLogPortPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_OK, ulRet);
    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}


TEST_F(Test_At_QryLogPortPara,Test_At_QryLogPortPara_003)
{
    /*��������*/
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    VOS_CHAR                           *pcExpactedStr;

    /*���ر�����ʼ��*/
    pcExpactedStr   = "^LOGPORT: 0";
    ucIndex = AT_CLIENT_ID_APP1;
    g_stParseContext[ucIndex].pstCmdElement = &gstLogPortCmdInfo;

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_READ_CMD;

    /*������׮*/
    MOCKER(PPM_QueryLogPort)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    /*���ñ��⺯�� */
    ulRet = At_QryLogPortPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}


class Test_At_SetDpdtTestFlagPara: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                                = 0;
        gastAtClientTab[ucIndex].usClientId    = 0;
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;
        g_stATParseCmd.ucCmdOptType            = AT_CMD_OPT_BUTT;

    }

    void TearDown()
    {
        gastAtClientTab[ucIndex].usClientId    = 0;
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;
        g_stATParseCmd.ucCmdOptType            = AT_CMD_OPT_BUTT;

        gucAtParaIndex                         = 0;
    }
};


TEST_F(Test_At_SetDpdtTestFlagPara, Test_At_SetDpdtTestFlagPara_001)
{
    /* �������� */
    VOS_UINT32                          ulRst;

    /* ������ʼ�� */
    gucAtParaIndex                = 3;

    /* ������׮ */

    /* ���ñ��⺯�� */
    ulRst = At_SetDpdtTestFlagPara(ucIndex);

    /* �����֤ */
    ASSERT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRst);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
TEST_F(Test_At_SetDpdtTestFlagPara, Test_At_SetDpdtTestFlagPara_002)
{
    /* �������� */
    VOS_UINT32                          ulRst;
    AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU   stAtCmd;

    /* ������ʼ�� */
    gucAtParaIndex                = 2;
    gastAtParaList[0].ulParaValue = 0;
    gastAtParaList[1].ulParaValue = 1;

    PS_MEM_SET(&stAtCmd, 0, sizeof(AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU));
    stAtCmd.enRatMode = (AT_MTA_CMD_RATMODE_ENUM_UINT8)gastAtParaList[0].ulParaValue;
    stAtCmd.ucFlag    = gastAtParaList[1].ulParaValue;

    /* ������׮ */
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)ID_AT_MTA_SET_DPDTTEST_FLAG_REQ), mirror((void *)&stAtCmd, sizeof(stAtCmd)), any(), any())
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    /* ���ñ��⺯�� */
    ulRst = At_SetDpdtTestFlagPara(ucIndex);

    /* �����֤ */
    ASSERT_EQ(AT_ERROR, ulRst);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
TEST_F(Test_At_SetDpdtTestFlagPara, Test_At_SetDpdtTestFlagPara_003)
{
    /* �������� */
    VOS_UINT32                          ulRst;
    AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU   stAtCmd;

    /* ������ʼ�� */
    gucAtParaIndex                = 2;
    gastAtParaList[0].ulParaValue = 0;
    gastAtParaList[1].ulParaValue = 1;

    PS_MEM_SET(&stAtCmd, 0, sizeof(AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU));
    stAtCmd.enRatMode = (AT_MTA_CMD_RATMODE_ENUM_UINT8)gastAtParaList[0].ulParaValue;
    stAtCmd.ucFlag    = gastAtParaList[1].ulParaValue;

    /* ������׮ */
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)ID_AT_MTA_SET_DPDTTEST_FLAG_REQ), mirror((void *)&stAtCmd, sizeof(stAtCmd)), any(), any())
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    /* ���ñ��⺯�� */
    ulRst = At_SetDpdtTestFlagPara(ucIndex);

    /* �����֤ */
    ASSERT_EQ(AT_WAIT_ASYNC_RETURN, ulRst);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
class Test_At_SetDpdtPara: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                                = 0;
        gastAtClientTab[ucIndex].usClientId    = 0;
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;
        g_stATParseCmd.ucCmdOptType            = AT_CMD_OPT_BUTT;

    }

    void TearDown()
    {
        gastAtClientTab[ucIndex].usClientId    = 0;
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;
        g_stATParseCmd.ucCmdOptType            = AT_CMD_OPT_BUTT;

        gucAtParaIndex                         = 0;
    }
};


TEST_F(Test_At_SetDpdtPara, Test_At_SetDpdtPara_001)
{
    /* �������� */
    VOS_UINT32                          ulRst;

    /* ������ʼ�� */
    gucAtParaIndex                = 3;

    /* ������׮ */

    /* ���ñ��⺯�� */
    ulRst = At_SetDpdtPara(ucIndex);

    /* �����֤ */
    ASSERT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRst);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
TEST_F(Test_At_SetDpdtPara, Test_At_SetDpdtPara_002)
{
    /* �������� */
    VOS_UINT32                          ulRst;
    AT_MTA_SET_DPDT_VALUE_REQ_STRU      stAtCmd;

    /* ������ʼ�� */
    gucAtParaIndex                = 2;
    gastAtParaList[0].ulParaValue = 1;
    gastAtParaList[1].ulParaValue = 1;

    PS_MEM_SET(&stAtCmd, 0, sizeof(AT_MTA_SET_DPDT_VALUE_REQ_STRU));
    stAtCmd.enRatMode   = (AT_MTA_CMD_RATMODE_ENUM_UINT8)gastAtParaList[0].ulParaValue;
    stAtCmd.ulDpdtValue = gastAtParaList[1].ulParaValue;


    /* ������׮ */
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)ID_AT_MTA_SET_DPDT_VALUE_REQ), mirror((void *)&stAtCmd, sizeof(stAtCmd)), any(), any())
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    /* ���ñ��⺯�� */
    ulRst = At_SetDpdtPara(ucIndex);

    /* �����֤ */
    ASSERT_EQ(AT_ERROR, ulRst);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
TEST_F(Test_At_SetDpdtPara, Test_At_SetDpdtPara_003)
{
    /* �������� */
    VOS_UINT32                          ulRst;
    AT_MTA_SET_DPDT_VALUE_REQ_STRU      stAtCmd;

    /* ������ʼ�� */
    gucAtParaIndex                = 2;
    gastAtParaList[0].ulParaValue = 1;
    gastAtParaList[1].ulParaValue = 1;

    PS_MEM_SET(&stAtCmd, 0, sizeof(AT_MTA_SET_DPDT_VALUE_REQ_STRU));
    stAtCmd.enRatMode   = (AT_MTA_CMD_RATMODE_ENUM_UINT8)gastAtParaList[0].ulParaValue;
    stAtCmd.ulDpdtValue = gastAtParaList[1].ulParaValue;

    /* ������׮ */
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)ID_AT_MTA_SET_DPDT_VALUE_REQ), mirror((void *)&stAtCmd, sizeof(stAtCmd)), any(), any())
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    /* ���ñ��⺯�� */
    ulRst = At_SetDpdtPara(ucIndex);

    /* �����֤ */
    ASSERT_EQ(AT_WAIT_ASYNC_RETURN, ulRst);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
class Test_At_SetQryDpdtPara: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                                = 0;
        gastAtClientTab[ucIndex].usClientId    = 0;
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;
        g_stATParseCmd.ucCmdOptType            = AT_CMD_OPT_BUTT;

    }

    void TearDown()
    {
        gastAtClientTab[ucIndex].usClientId    = 0;
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;
        g_stATParseCmd.ucCmdOptType            = AT_CMD_OPT_BUTT;

        gucAtParaIndex                         = 0;
    }
};


TEST_F(Test_At_SetQryDpdtPara, Test_At_SetQryDpdtPara_001)
{
    /* �������� */
    VOS_UINT32                          ulRst;

    /* ������ʼ�� */
    gucAtParaIndex                = 2;

    /* ������׮ */

    /* ���ñ��⺯�� */
    ulRst = At_SetQryDpdtPara(ucIndex);

    /* �����֤ */
    ASSERT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRst);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
TEST_F(Test_At_SetQryDpdtPara, Test_At_SetQryDpdtPara_002)
{
    /* �������� */
    VOS_UINT32                          ulRst;
    AT_MTA_QRY_DPDT_VALUE_REQ_STRU      stAtCmd;

    /* ������ʼ�� */
    gucAtParaIndex                = 1;
    gastAtParaList[0].ulParaValue = 0;

    PS_MEM_SET(&stAtCmd, 0, sizeof(AT_MTA_QRY_DPDT_VALUE_REQ_STRU));
    stAtCmd.enRatMode = (AT_MTA_CMD_RATMODE_ENUM_UINT8)gastAtParaList[0].ulParaValue;

    /* ������׮ */
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)ID_AT_MTA_QRY_DPDT_VALUE_REQ), mirror((void *)&stAtCmd, sizeof(stAtCmd)), any(), any())
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    /* ���ñ��⺯�� */
    ulRst = At_SetQryDpdtPara(ucIndex);

    /* �����֤ */
    ASSERT_EQ(AT_ERROR, ulRst);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
TEST_F(Test_At_SetQryDpdtPara, Test_At_SetQryDpdtPara_003)
{
    /* �������� */
    VOS_UINT32                          ulRst;
    AT_MTA_QRY_DPDT_VALUE_REQ_STRU      stAtCmd;

    /* ������ʼ�� */
    gucAtParaIndex                = 1;
    gastAtParaList[0].ulParaValue = 2;

    PS_MEM_SET(&stAtCmd, 0, sizeof(AT_MTA_QRY_DPDT_VALUE_REQ_STRU));
    stAtCmd.enRatMode = (AT_MTA_CMD_RATMODE_ENUM_UINT8)gastAtParaList[0].ulParaValue;

    /* ������׮ */
    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)ID_AT_MTA_QRY_DPDT_VALUE_REQ), mirror((void *)&stAtCmd, sizeof(stAtCmd)), any(), any())
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    /* ���ñ��⺯�� */
    ulRst = At_SetQryDpdtPara(ucIndex);

    /* �����֤ */
    ASSERT_EQ(AT_WAIT_ASYNC_RETURN, ulRst);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
class Test_AT_RcvMtaSetDpdtTestFlagCnf: public ::testing::Test
{
public:
    AT_MTA_MSG_STRU                     *pRcvMsg;
    MTA_AT_SET_DPDTTEST_FLAG_CNF_STRU   *pstSetCnf;
    VOS_UINT8                            ucIndex;

    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(V_StopRelTimer)
            .stubs()
            .will(returnValue((VOS_UINT32)VOS_OK));
        
        ucIndex = 0;

        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));

        /* ����������Ϣ */
        pRcvMsg = (AT_MTA_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(AT_MTA_MSG_STRU) + sizeof(MTA_AT_SET_DPDTTEST_FLAG_CNF_STRU) - 4);

        if (VOS_NULL_PTR == pRcvMsg)
        {
            return;
        }
        pRcvMsg->stAppCtrl.usClientId = 0;
        pstSetCnf = (MTA_AT_SET_DPDTTEST_FLAG_CNF_STRU *)(pRcvMsg->aucContent);

        PS_MEM_SET(pRcvMsg, 0, sizeof(AT_MTA_MSG_STRU));
        PS_MEM_SET(pstSetCnf, 0, sizeof(MTA_AT_SET_DPDTTEST_FLAG_CNF_STRU));

    }

    void TearDown()
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));

        /* �ͷ���Ϣ�ڴ� */
        if (VOS_NULL_PTR != pRcvMsg)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pRcvMsg);
        }
    }
};


TEST_F(Test_AT_RcvMtaSetDpdtTestFlagCnf, Test_AT_RcvMtaSetDpdtTestFlagCnf_001)
{
    // ��������
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;

    /* ������ʼ�� */
    usClientId = 0;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex, sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    // ���ñ��⺯��
    ulRst = AT_RcvMtaSetDpdtTestFlagCnf((VOS_VOID*)pRcvMsg);
    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRst);
    GlobalMockObject::verify();
}
TEST_F(Test_AT_RcvMtaSetDpdtTestFlagCnf, Test_AT_RcvMtaSetDpdtTestFlagCnf_002)
{
    // ��������
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucIndexTemp;

    /* ������ʼ�� */
    usClientId  = 0;
    ucIndexTemp = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndexTemp, sizeof(ucIndexTemp)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    // ���ñ��⺯��
    ulRst = AT_RcvMtaSetDpdtTestFlagCnf((VOS_VOID*)pRcvMsg);
    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRst);
    GlobalMockObject::verify();
}
TEST_F(Test_AT_RcvMtaSetDpdtTestFlagCnf, Test_AT_RcvMtaSetDpdtTestFlagCnf_003)
{
    // ��������
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;

    /* ������ʼ�� */
    usClientId = 0;

    // ��ʼ��ȫ�ֱ���
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

    // MOCKER����
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex, sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    // ���ñ��⺯��
    ulRst = AT_RcvMtaSetDpdtTestFlagCnf((VOS_VOID*)pRcvMsg);
    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRst);
    GlobalMockObject::verify();
}
TEST_F(Test_AT_RcvMtaSetDpdtTestFlagCnf, Test_AT_RcvMtaSetDpdtTestFlagCnf_004)
{
    // ��������
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;

    /* ������ʼ�� */
    usClientId = 0;
    pstSetCnf->enResult = MTA_AT_RESULT_ERROR;

    // ��ʼ��ȫ�ֱ���
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DPDTTEST_SET;

    // MOCKER����
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex, sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .stubs();
    
    // ���ñ��⺯��
    ulRst = AT_RcvMtaSetDpdtTestFlagCnf((VOS_VOID*)pRcvMsg);
    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRst);
    EXPECT_EQ(0,gstAtSendData.usBufLen);
    EXPECT_EQ(g_stParseContext[ucIndex].ucClientStatus,AT_FW_CLIENT_STATUS_READY);
    EXPECT_EQ(gastAtClientTab[ucIndex].CmdCurrentOpt, AT_CMD_CURRENT_OPT_BUTT);
    EXPECT_EQ(gastAtClientTab[ucIndex].opId, 0);
    GlobalMockObject::verify();
}
TEST_F(Test_AT_RcvMtaSetDpdtTestFlagCnf, Test_AT_RcvMtaSetDpdtTestFlagCnf_005)
{
    // ��������
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;

    /* ������ʼ�� */
    usClientId = 0;
    pstSetCnf->enResult = MTA_AT_RESULT_NO_ERROR;

    // ��ʼ��ȫ�ֱ���
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DPDTTEST_SET;

    // MOCKER����
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex, sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .stubs();

    // ���ñ��⺯��
    ulRst = AT_RcvMtaSetDpdtTestFlagCnf((VOS_VOID*)pRcvMsg);
    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRst);
    EXPECT_EQ(g_stParseContext[ucIndex].ucClientStatus,AT_FW_CLIENT_STATUS_READY);
    EXPECT_EQ(gastAtClientTab[ucIndex].CmdCurrentOpt, AT_CMD_CURRENT_OPT_BUTT);
    EXPECT_EQ(gastAtClientTab[ucIndex].opId, 0);
    GlobalMockObject::verify();
}
class Test_AT_RcvMtaSetDpdtValueCnf: public ::testing::Test
{
public:
    AT_MTA_MSG_STRU                     *pRcvMsg;
    MTA_AT_SET_DPDT_VALUE_CNF_STRU      *pstSetCnf;
    VOS_UINT8                            ucIndex;

    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(V_StopRelTimer)
            .stubs()
            .will(returnValue((VOS_UINT32)VOS_OK));

        ucIndex = 0;

        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));

        /* ����������Ϣ */
        pRcvMsg = (AT_MTA_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(AT_MTA_MSG_STRU) + sizeof(MTA_AT_SET_DPDT_VALUE_CNF_STRU) - 4);

        if (VOS_NULL_PTR == pRcvMsg)
        {
            return;
        }
        pRcvMsg->stAppCtrl.usClientId = 0;
        pstSetCnf = (MTA_AT_SET_DPDT_VALUE_CNF_STRU *)(pRcvMsg->aucContent);

        PS_MEM_SET(pRcvMsg, 0, sizeof(AT_MTA_MSG_STRU));
        PS_MEM_SET(pstSetCnf, 0, sizeof(MTA_AT_SET_DPDT_VALUE_CNF_STRU));

    }

    void TearDown()
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));

        /* �ͷ���Ϣ�ڴ� */
        if (VOS_NULL_PTR != pRcvMsg)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pRcvMsg);
        }
    }
};


TEST_F(Test_AT_RcvMtaSetDpdtValueCnf, Test_AT_RcvMtaSetDpdtValueCnf_001)
{
    // ��������
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;

    /* ������ʼ�� */
    usClientId = 0;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex))
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    // ���ñ��⺯��
    ulRst = AT_RcvMtaSetDpdtValueCnf((VOS_VOID*)pRcvMsg);
    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRst);
    GlobalMockObject::verify();
}
TEST_F(Test_AT_RcvMtaSetDpdtValueCnf, Test_AT_RcvMtaSetDpdtValueCnf_002)
{
    // ��������
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucIndexTemp;

    /* ������ʼ�� */
    usClientId  = 0;
    ucIndexTemp = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndexTemp))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    // ���ñ��⺯��
    ulRst = AT_RcvMtaSetDpdtValueCnf((VOS_VOID*)pRcvMsg);
    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRst);
    GlobalMockObject::verify();
}
TEST_F(Test_AT_RcvMtaSetDpdtValueCnf, Test_AT_RcvMtaSetDpdtValueCnf_003)
{
    // ��������
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;

    /* ������ʼ�� */
    usClientId = 0;

    // ��ʼ��ȫ�ֱ���
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

    // MOCKER����
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    // ���ñ��⺯��
    ulRst = AT_RcvMtaSetDpdtValueCnf((VOS_VOID*)pRcvMsg);
    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRst);
    GlobalMockObject::verify();
}
TEST_F(Test_AT_RcvMtaSetDpdtValueCnf, Test_AT_RcvMtaSetDpdtValueCnf_004)
{
    // ��������
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;

    /* ������ʼ�� */
    usClientId = 0;
    pstSetCnf->enResult = MTA_AT_RESULT_ERROR;

    // ��ʼ��ȫ�ֱ���
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DPDT_SET;

    // MOCKER����
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .stubs();

    // ���ñ��⺯��
    ulRst = AT_RcvMtaSetDpdtValueCnf((VOS_VOID*)pRcvMsg);
    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRst);
    EXPECT_EQ(0,gstAtSendData.usBufLen);
    EXPECT_EQ(g_stParseContext[ucIndex].ucClientStatus,AT_FW_CLIENT_STATUS_READY);
    EXPECT_EQ(gastAtClientTab[ucIndex].CmdCurrentOpt, AT_CMD_CURRENT_OPT_BUTT);
    EXPECT_EQ(gastAtClientTab[ucIndex].opId, 0);
    GlobalMockObject::verify();
}
TEST_F(Test_AT_RcvMtaSetDpdtValueCnf, Test_AT_RcvMtaSetDpdtValueCnf_005)
{
    // ��������
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;

    /* ������ʼ�� */
    usClientId = 0;
    pstSetCnf->enResult = MTA_AT_RESULT_NO_ERROR;

    // ��ʼ��ȫ�ֱ���
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DPDT_SET;

    // MOCKER����
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .stubs();

    // ���ñ��⺯��
    ulRst = AT_RcvMtaSetDpdtValueCnf((VOS_VOID*)pRcvMsg);
    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRst);
    EXPECT_EQ(g_stParseContext[ucIndex].ucClientStatus,AT_FW_CLIENT_STATUS_READY);
    EXPECT_EQ(gastAtClientTab[ucIndex].CmdCurrentOpt, AT_CMD_CURRENT_OPT_BUTT);
    EXPECT_EQ(gastAtClientTab[ucIndex].opId, 0);
    GlobalMockObject::verify();
}
class Test_AT_RcvMtaQryDpdtValueCnf: public ::testing::Test
{
public:
    AT_MTA_MSG_STRU                     *pRcvMsg;
    MTA_AT_QRY_DPDT_VALUE_CNF_STRU      *pstQryCnf;
    VOS_UINT8                            ucIndex;

    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(V_StopRelTimer)
            .stubs()
            .will(returnValue((VOS_UINT32)VOS_OK));
    
        ucIndex = 0;

        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));

        /* ����������Ϣ */
        pRcvMsg = (AT_MTA_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(AT_MTA_MSG_STRU) + sizeof(MTA_AT_QRY_DPDT_VALUE_CNF_STRU) - 4);

        if (VOS_NULL_PTR == pRcvMsg)
        {
            return;
        }
        pRcvMsg->stAppCtrl.usClientId = 0;
        pstQryCnf = (MTA_AT_QRY_DPDT_VALUE_CNF_STRU *)(pRcvMsg->aucContent);

        PS_MEM_SET(pRcvMsg, 0, sizeof(AT_MTA_MSG_STRU));
        PS_MEM_SET(pstQryCnf, 0, sizeof(MTA_AT_QRY_DPDT_VALUE_CNF_STRU));

    }

    void TearDown()
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));

        /* �ͷ���Ϣ�ڴ� */
        if (VOS_NULL_PTR != pRcvMsg)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pRcvMsg);
        }
    }
};


TEST_F(Test_AT_RcvMtaQryDpdtValueCnf, Test_AT_RcvMtaQryDpdtValueCnf_001)
{
    // ��������
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;

    /* ������ʼ�� */
    usClientId = 0;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex))
        .will(returnValue((TAF_UINT32)AT_FAILURE));

    // ���ñ��⺯��
    ulRst = AT_RcvMtaQryDpdtValueCnf((VOS_VOID*)pRcvMsg);
    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRst);
    GlobalMockObject::verify();
}
TEST_F(Test_AT_RcvMtaQryDpdtValueCnf, Test_AT_RcvMtaQryDpdtValueCnf_002)
{
    // ��������
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucIndexTemp;

    /* ������ʼ�� */
    usClientId  = 0;
    ucIndexTemp = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndexTemp))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    // ���ñ��⺯��
    ulRst = AT_RcvMtaQryDpdtValueCnf((VOS_VOID*)pRcvMsg);
    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRst);
    GlobalMockObject::verify();
}
TEST_F(Test_AT_RcvMtaQryDpdtValueCnf, Test_AT_RcvMtaQryDpdtValueCnf_003)
{
    // ��������
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;

    /* ������ʼ�� */
    usClientId = 0;

    // ��ʼ��ȫ�ֱ���
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

    // MOCKER����
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    // ���ñ��⺯��
    ulRst = AT_RcvMtaQryDpdtValueCnf((VOS_VOID*)pRcvMsg);
    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRst);
    GlobalMockObject::verify();
}
TEST_F(Test_AT_RcvMtaQryDpdtValueCnf, Test_AT_RcvMtaQryDpdtValueCnf_004)
{
    // ��������
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;

    /* ������ʼ�� */
    usClientId = 0;
    pstQryCnf->enResult = MTA_AT_RESULT_ERROR;
    pstQryCnf->ulDpdtValue = 0x100;

    // ��ʼ��ȫ�ֱ���
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DPDTQRY_SET;

    // MOCKER����
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .stubs();

    // ���ñ��⺯��
    ulRst = AT_RcvMtaQryDpdtValueCnf((VOS_VOID*)pRcvMsg);
    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRst);
    EXPECT_EQ(0,gstAtSendData.usBufLen);
    EXPECT_EQ(g_stParseContext[ucIndex].ucClientStatus,AT_FW_CLIENT_STATUS_READY);
    EXPECT_EQ(gastAtClientTab[ucIndex].CmdCurrentOpt, AT_CMD_CURRENT_OPT_BUTT);
    EXPECT_EQ(gastAtClientTab[ucIndex].opId, 0);
    GlobalMockObject::verify();
}
TEST_F(Test_AT_RcvMtaQryDpdtValueCnf, Test_AT_RcvMtaQryDpdtValueCnf_005)
{
    // ��������
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;
    char                                acExpectedResult[] = "^DPDTQRY: 256";

    /* ������ʼ�� */
    usClientId = 0;
    pstQryCnf->enResult = MTA_AT_RESULT_NO_ERROR;
    pstQryCnf->ulDpdtValue = 0x100;


    // ��ʼ��ȫ�ֱ���
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DPDTQRY_SET;

    // MOCKER����
    MOCKER(At_ClientIdToUserId)
        .stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex, sizeof(ucIndex)))
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    MOCKER(At_FormatResultData)
        .stubs();

    // ���ñ��⺯��
    ulRst = AT_RcvMtaQryDpdtValueCnf((VOS_VOID*)pRcvMsg);
    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRst);
    ASSERT_STREQ(acExpectedResult , (char *)pgucAtSndCodeAddr);
    EXPECT_EQ(g_stParseContext[ucIndex].ucClientStatus,AT_FW_CLIENT_STATUS_READY);
    EXPECT_EQ(gastAtClientTab[ucIndex].CmdCurrentOpt, AT_CMD_CURRENT_OPT_BUTT);
    EXPECT_EQ(gastAtClientTab[ucIndex].opId, 0);
    GlobalMockObject::verify();
}
class Test_At_SetJamDetectPara: public ::testing::Test
{
public:
    TAF_UINT8                           ucIndex;

    void SetUp()
    {
		UT_STUB_INIT();

        ucIndex                                = 0;
        gastAtClientTab[ucIndex].usClientId    = 0;
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;
        g_stATParseCmd.ucCmdOptType            = AT_CMD_OPT_BUTT;

    }

    void TearDown()
    {
        gastAtClientTab[ucIndex].usClientId    = 0;
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;
        g_stATParseCmd.ucCmdOptType            = AT_CMD_OPT_BUTT;

        gucAtParaIndex                         = 0;
    }
};


TEST_F(Test_At_SetJamDetectPara, Test_At_SetJamDetectPara_001)
{
    /* �������� */
    VOS_UINT32                          ulRst;

    /* ������ʼ�� */
    gucAtParaIndex                = 5;

    /* ������׮ */

    /* ���ñ��⺯�� */
    ulRst = At_SetJamDetectPara(ucIndex);

    /* �����֤ */
    ASSERT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRst);

    //������ʱ����Ҫ����������λ�ü������
	GlobalMockObject::verify();
}
TEST_F(Test_At_SetJamDetectPara, Test_At_SetJamDetectPara_002)
{
    /* �������� */
    VOS_UINT32                          ulRst;
    AT_MTA_SET_JAM_DETECT_REQ_STRU      stAtCmd;

    /* ������ʼ�� */
    gucAtParaIndex                = 4;
    gastAtParaList[0].ulParaValue = 1;
    gastAtParaList[1].ulParaValue = 2;
    gastAtParaList[2].usParaLen   = 1;
    gastAtParaList[2].ulParaValue = 10;
    gastAtParaList[3].usParaLen   = 1;
    gastAtParaList[3].ulParaValue = 100;

    PS_MEM_SET(&stAtCmd, 0, sizeof(AT_MTA_SET_JAM_DETECT_REQ_STRU));
    stAtCmd.ucFlag      = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    stAtCmd.ucMethod    = (VOS_UINT8)gastAtParaList[1].ulParaValue;
    stAtCmd.ucThreshold = (VOS_UINT8)gastAtParaList[2].ulParaValue;
    stAtCmd.ucFreqNum   = (VOS_UINT8)gastAtParaList[3].ulParaValue;

    /* ������׮ */
	MOCKER(NV_ReadEx)
		.stubs()
		.will(returnValue((VOS_UINT32)NV_OK));

	MOCKER(NV_WriteEx)
		.stubs()
		.will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq((VOS_UINT16)ID_AT_MTA_SET_JAM_DETECT_REQ), mirror((void *)&stAtCmd, sizeof(stAtCmd)), any(), any())
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    /* ���ñ��⺯�� */
    ulRst = At_SetJamDetectPara(ucIndex);

    /* �����֤ */
    ASSERT_EQ(AT_ERROR, ulRst);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
TEST_F(Test_At_SetJamDetectPara, Test_At_SetJamDetectPara_003)
{
    /* �������� */
    VOS_UINT32                          ulRst;
    AT_MTA_SET_JAM_DETECT_REQ_STRU      stAtCmd;

    /* ������ʼ�� */
    gucAtParaIndex                = 4;
    gastAtParaList[0].ulParaValue = 1;
    gastAtParaList[1].ulParaValue = 2;
    gastAtParaList[2].usParaLen   = 1;
    gastAtParaList[2].ulParaValue = 10;
    gastAtParaList[3].usParaLen   = 1;
    gastAtParaList[3].ulParaValue = 100;

    PS_MEM_SET(&stAtCmd, 0, sizeof(AT_MTA_SET_JAM_DETECT_REQ_STRU));
    stAtCmd.ucFlag      = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    stAtCmd.ucMethod    = (VOS_UINT8)gastAtParaList[1].ulParaValue;
    stAtCmd.ucThreshold = (VOS_UINT8)gastAtParaList[2].ulParaValue;
    stAtCmd.ucFreqNum   = (VOS_UINT8)gastAtParaList[3].ulParaValue;

    /* ������׮ */
	MOCKER(NV_ReadEx)
		.stubs()
		.will(returnValue((VOS_UINT32)NV_OK));

	MOCKER(NV_WriteEx)
		.stubs()
		.will(returnValue((VOS_UINT32)NV_OK));

	MOCKER(AT_FillAndSndAppReqMsg)
		.expects(exactly(1))
		.with(any(), any(), eq((VOS_UINT16)ID_AT_MTA_SET_JAM_DETECT_REQ), mirror((void *)&stAtCmd, sizeof(stAtCmd)), any(), any())
		.will(returnValue((VOS_UINT32)TAF_SUCCESS));

    /* ���ñ��⺯�� */
    ulRst = At_SetJamDetectPara(ucIndex);

    /* �����֤ */
    ASSERT_EQ(AT_WAIT_ASYNC_RETURN, ulRst);

    //������ʱ����Ҫ����������λ�ü������
	GlobalMockObject::verify();
}
TEST_F(Test_At_SetJamDetectPara, Test_At_SetJamDetectPara_004)
{
    /* �������� */
    VOS_UINT32                          ulRst;
    AT_MTA_SET_JAM_DETECT_REQ_STRU      stAtCmd;

    /* ������ʼ�� */
    gucAtParaIndex                = 4;
    gastAtParaList[0].ulParaValue = 1;
    gastAtParaList[1].ulParaValue = 2;
    gastAtParaList[2].usParaLen   = 0;
    gastAtParaList[2].ulParaValue = 10;
    gastAtParaList[3].usParaLen   = 0;
    gastAtParaList[3].ulParaValue = 100;

    PS_MEM_SET(&stAtCmd, 0, sizeof(AT_MTA_SET_JAM_DETECT_REQ_STRU));
    stAtCmd.ucFlag      = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    stAtCmd.ucMethod    = (VOS_UINT8)gastAtParaList[1].ulParaValue;
    stAtCmd.ucThreshold = AT_JAM_DETECT_DEFAULT_THRESHOLD;
    stAtCmd.ucFreqNum   = AT_JAM_DETECT_DEFAULT_FREQ_NUM;

    /* ������׮ */
	MOCKER(NV_ReadEx)
		.stubs()
		.will(returnValue((VOS_UINT32)NV_OK));

	MOCKER(NV_WriteEx)
		.stubs()
		.will(returnValue((VOS_UINT32)NV_OK));

	MOCKER(AT_FillAndSndAppReqMsg)
		.expects(exactly(1))
		.with(any(), any(), eq((VOS_UINT16)ID_AT_MTA_SET_JAM_DETECT_REQ), mirror((void *)&stAtCmd, sizeof(stAtCmd)), any(), any())
		.will(returnValue((VOS_UINT32)TAF_SUCCESS));

    /* ���ñ��⺯�� */
    ulRst = At_SetJamDetectPara(ucIndex);

    /* �����֤ */
    ASSERT_EQ(AT_WAIT_ASYNC_RETURN, ulRst);

    //������ʱ����Ҫ����������λ�ü������
	GlobalMockObject::verify();
}
TEST_F(Test_At_SetJamDetectPara, Test_At_SetJamDetectPara_005)
{
    /* �������� */
    VOS_UINT32                          ulRst;
    AT_MTA_SET_JAM_DETECT_REQ_STRU      stAtCmd;

    /* ������ʼ�� */
    gucAtParaIndex                = 4;
    gastAtParaList[0].ulParaValue = 1;
    gastAtParaList[1].ulParaValue = 2;
    gastAtParaList[2].usParaLen   = 1;
    gastAtParaList[2].ulParaValue = 10;
    gastAtParaList[3].usParaLen   = 1;
    gastAtParaList[3].ulParaValue = 100;

    PS_MEM_SET(&stAtCmd, 0, sizeof(AT_MTA_SET_JAM_DETECT_REQ_STRU));
    stAtCmd.ucFlag      = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    stAtCmd.ucMethod    = (VOS_UINT8)gastAtParaList[1].ulParaValue;
    stAtCmd.ucThreshold = (VOS_UINT8)gastAtParaList[2].ulParaValue;
    stAtCmd.ucFreqNum   = (VOS_UINT8)gastAtParaList[3].ulParaValue;

    /* ������׮ */
	MOCKER(NV_ReadEx)
		.stubs()
		.will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_WriteEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(0));

    /* ���ñ��⺯�� */
    ulRst = At_SetJamDetectPara(ucIndex);

    /* �����֤ */
    ASSERT_EQ(AT_ERROR, ulRst);

    //������ʱ����Ҫ����������λ�ü������
	GlobalMockObject::verify();
}
TEST_F(Test_At_SetJamDetectPara, Test_At_SetJamDetectPara_006)
{
    /* �������� */
    VOS_UINT32                          ulRst;
    AT_MTA_SET_JAM_DETECT_REQ_STRU      stAtCmd;

    /* ������ʼ�� */
    gucAtParaIndex                = 4;
    gastAtParaList[0].ulParaValue = 1;
    gastAtParaList[1].ulParaValue = 2;
    gastAtParaList[2].usParaLen   = 1;
    gastAtParaList[2].ulParaValue = 10;
    gastAtParaList[3].usParaLen   = 1;
    gastAtParaList[3].ulParaValue = 100;

    PS_MEM_SET(&stAtCmd, 0, sizeof(AT_MTA_SET_JAM_DETECT_REQ_STRU));
    stAtCmd.ucFlag      = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    stAtCmd.ucMethod    = (VOS_UINT8)gastAtParaList[1].ulParaValue;
    stAtCmd.ucThreshold = (VOS_UINT8)gastAtParaList[2].ulParaValue;
    stAtCmd.ucFreqNum   = (VOS_UINT8)gastAtParaList[3].ulParaValue;

    /* ������׮ */
    MOCKER(NV_ReadEx)
		.stubs()
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(0));

    /* ���ñ��⺯�� */
    ulRst = At_SetJamDetectPara(ucIndex);

    /* �����֤ */
    ASSERT_EQ(AT_ERROR, ulRst);

    //������ʱ����Ҫ����������λ�ü������
	GlobalMockObject::verify();
}
class Test_At_QryJamDetectPara: public ::testing::Test
{
public:
    TAF_UINT8                           ucIndex;

    void SetUp()
    {
		UT_STUB_INIT();

        ucIndex                                = 0;
        gastAtClientTab[ucIndex].usClientId    = 0;
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;
        g_stATParseCmd.ucCmdOptType            = AT_CMD_OPT_BUTT;

    }

    void TearDown()
    {
        gastAtClientTab[ucIndex].usClientId    = 0;
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;
        g_stATParseCmd.ucCmdOptType            = AT_CMD_OPT_BUTT;

        gucAtParaIndex                         = 0;
    }
};


TEST_F(Test_At_QryJamDetectPara, Test_At_QryJamDetectPara_001)
{
    /* �������� */
    VOS_UINT32                          ulRst;

    /* ������ʼ�� */

    /* ������׮ */

    /* ���ñ��⺯�� */
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    ulRst = At_QryJamDetectPara(ucIndex);

    /* �����֤ */
    ASSERT_EQ(AT_ERROR, ulRst);

    //������ʱ����Ҫ����������λ�ü������
	GlobalMockObject::verify();
}
TEST_F(Test_At_QryJamDetectPara, Test_At_QryJamDetectPara_002)
{
    /* �������� */
    VOS_UINT32                          ulRst;
    NV_NAS_JAM_DETECT_CFG_STRU          stNvJamDetect;
    char                                acExpectedResult[] = "^JDETEX: 1,2,20,100";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_JDETEX,
                                                        At_SetJamDetectPara,   AT_SET_PARA_TIME,
                                                        At_QryJamDetectPara,   AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR, AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,   AT_NOT_SET_TIME,
                                                        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_NO_LIMITED,
                                                        (VOS_UINT8*)"^JDETEX",  VOS_NULL_PTR};

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    /* ������ʼ�� */
    PS_MEM_SET(&stNvJamDetect, 0x0, sizeof(stNvJamDetect));
    stNvJamDetect.ucMode       = 1;
    stNvJamDetect.ucMethod     = 2;
    stNvJamDetect.ucThreshold  = 20;
    stNvJamDetect.ucFreqNum    = 100;

    /* ������׮ */

    /* ���ñ��⺯�� */
    MOCKER(NV_ReadEx)
		.expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_JAM_DETECT_CFG), outBoundP((void *)&stNvJamDetect, (VOS_UINT32)sizeof(NV_NAS_JAM_DETECT_CFG_STRU)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    ulRst = At_QryJamDetectPara(ucIndex);

    /* �����֤ */
    ASSERT_EQ(AT_OK, ulRst);
    ASSERT_STREQ(acExpectedResult , (char *)pgucAtSndCodeAddr);

    //������ʱ����Ҫ����������λ�ü������
	GlobalMockObject::verify();
}
class Test_AT_RcvMtaSetJamDetectCnf: public ::testing::Test
{
public:
    AT_MTA_MSG_STRU                     *pRcvMsg;
    MTA_AT_SET_JAM_DETECT_CNF_STRU      *pstSetCnf;
    VOS_UINT8                            ucIndex;

    void SetUp()
    {
		UT_STUB_INIT();

		MOCKER(V_StopRelTimer)
			.stubs()
			.will(returnValue((VOS_UINT32)VOS_OK));

        ucIndex = 0;

        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));

        /* ����������Ϣ */
        pRcvMsg = (AT_MTA_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(AT_MTA_MSG_STRU) + sizeof(MTA_AT_SET_JAM_DETECT_CNF_STRU) - 4);

        if (VOS_NULL_PTR == pRcvMsg)
        {
            return;
        }
        pRcvMsg->stAppCtrl.usClientId = 0;
        pstSetCnf = (MTA_AT_SET_JAM_DETECT_CNF_STRU *)(pRcvMsg->aucContent);

        PS_MEM_SET(pRcvMsg, 0, sizeof(AT_MTA_MSG_STRU));
        PS_MEM_SET(pstSetCnf, 0, sizeof(MTA_AT_SET_JAM_DETECT_CNF_STRU));

    }

    void TearDown()
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));

        /* �ͷ���Ϣ�ڴ� */
        if (VOS_NULL_PTR != pRcvMsg)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pRcvMsg);
        }
    }
};


TEST_F(Test_AT_RcvMtaSetJamDetectCnf, Test_AT_RcvMtaSetJamDetectCnf_001)
{
    // ��������
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;

    /* ������ʼ�� */
    usClientId = 0;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
	MOCKER(At_ClientIdToUserId)
		.stubs()
		.with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex))
		.will(returnValue((TAF_UINT32)AT_FAILURE));

    // ���ñ��⺯��
    ulRst = AT_RcvMtaSetJamDetectCnf((VOS_VOID*)pRcvMsg);
    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRst);
	GlobalMockObject::verify();
}
TEST_F(Test_AT_RcvMtaSetJamDetectCnf, Test_AT_RcvMtaSetJamDetectCnf_002)
{
    // ��������
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucIndexTemp;

    /* ������ʼ�� */
    usClientId  = 0;
    ucIndexTemp = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
	MOCKER(At_ClientIdToUserId)
		.stubs()
		.with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndexTemp))
		.will(returnValue((TAF_UINT32)AT_SUCCESS));

    // ���ñ��⺯��
    ulRst = AT_RcvMtaSetJamDetectCnf((VOS_VOID*)pRcvMsg);
    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRst);
	GlobalMockObject::verify();
}
TEST_F(Test_AT_RcvMtaSetJamDetectCnf, Test_AT_RcvMtaSetJamDetectCnf_003)
{
    // ��������
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;

    /* ������ʼ�� */
    usClientId = 0;

    // ��ʼ��ȫ�ֱ���
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

    // MOCKER����
	MOCKER(At_ClientIdToUserId)
		.stubs()
		.with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex))
		.will(returnValue((TAF_UINT32)AT_SUCCESS));

    // ���ñ��⺯��
    ulRst = AT_RcvMtaSetJamDetectCnf((VOS_VOID*)pRcvMsg);
    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRst);
	GlobalMockObject::verify();
}
TEST_F(Test_AT_RcvMtaSetJamDetectCnf, Test_AT_RcvMtaSetJamDetectCnf_004)
{
    // ��������
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;

    /* ������ʼ�� */
    usClientId = 0;
    pstSetCnf->enResult = MTA_AT_RESULT_ERROR;

    // ��ʼ��ȫ�ֱ���
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_JDETEX_SET;

    // MOCKER����
	MOCKER(At_ClientIdToUserId)
		.stubs()
		.with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex))
		.will(returnValue((TAF_UINT32)AT_SUCCESS));

	MOCKER(At_FormatResultData)
		.stubs();

    // ���ñ��⺯��
    ulRst = AT_RcvMtaSetJamDetectCnf((VOS_VOID*)pRcvMsg);
    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRst);
    EXPECT_EQ(0,gstAtSendData.usBufLen);
    EXPECT_EQ(g_stParseContext[ucIndex].ucClientStatus,AT_FW_CLIENT_STATUS_READY);
    EXPECT_EQ(gastAtClientTab[ucIndex].CmdCurrentOpt, AT_CMD_CURRENT_OPT_BUTT);
    EXPECT_EQ(gastAtClientTab[ucIndex].opId, 0);
	GlobalMockObject::verify();
}
TEST_F(Test_AT_RcvMtaSetJamDetectCnf, Test_AT_RcvMtaSetJamDetectCnf_005)
{
    // ��������
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;

    /* ������ʼ�� */
    usClientId = 0;
    pstSetCnf->enResult = MTA_AT_RESULT_NO_ERROR;

    // ��ʼ��ȫ�ֱ���
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_JDETEX_SET;

    // MOCKER����
	MOCKER(At_ClientIdToUserId)
		.stubs()
		.with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex))
		.will(returnValue((TAF_UINT32)AT_SUCCESS));

	MOCKER(At_FormatResultData)
		.stubs();

    // ���ñ��⺯��
    ulRst = AT_RcvMtaSetJamDetectCnf((VOS_VOID*)pRcvMsg);
    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRst);
    EXPECT_EQ(g_stParseContext[ucIndex].ucClientStatus,AT_FW_CLIENT_STATUS_READY);
    EXPECT_EQ(gastAtClientTab[ucIndex].CmdCurrentOpt, AT_CMD_CURRENT_OPT_BUTT);
    EXPECT_EQ(gastAtClientTab[ucIndex].opId, 0);
	GlobalMockObject::verify();
}
class Test_AT_RcvMtaJamDetectInd: public ::testing::Test
{
public:
    AT_MTA_MSG_STRU                     *pRcvMsg;
    MTA_AT_JAM_DETECT_IND_STRU          *pstJamInd;
    VOS_UINT8                            ucIndex;

    void SetUp()
    {
		UT_STUB_INIT();

		MOCKER(V_StopRelTimer)
			.stubs()
			.will(returnValue((VOS_UINT32)VOS_OK));

        ucIndex = 0;

        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));

        /* ����������Ϣ */
        pRcvMsg = (AT_MTA_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(AT_MTA_MSG_STRU) + sizeof(MTA_AT_JAM_DETECT_IND_STRU) - 4);

        if (VOS_NULL_PTR == pRcvMsg)
        {
            return;
        }
        pRcvMsg->stAppCtrl.usClientId = 0;
        pstJamInd = (MTA_AT_JAM_DETECT_IND_STRU *)(pRcvMsg->aucContent);

        PS_MEM_SET(pRcvMsg, 0, sizeof(AT_MTA_MSG_STRU));
        PS_MEM_SET(pstJamInd, 0, sizeof(MTA_AT_JAM_DETECT_IND_STRU));

    }

    void TearDown()
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

        gstAtSendData.usBufLen = 0;
        PS_MEM_SET(gstAtSendData.aucBuffer, 0, sizeof(gstAtSendData.aucBuffer));

        /* �ͷ���Ϣ�ڴ� */
        if (VOS_NULL_PTR != pRcvMsg)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pRcvMsg);
        }
    }
};


TEST_F(Test_AT_RcvMtaJamDetectInd, Test_AT_RcvMtaJamDetectInd_001)
{
    // ��������
    VOS_UINT32                          ulRst;
    VOS_UINT16                          usClientId;

    /* ������ʼ�� */
    usClientId = 0;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
	MOCKER(At_ClientIdToUserId)
		.stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex, sizeof(ucIndex)))
		.will(returnValue((TAF_UINT32)AT_FAILURE));

    // ���ñ��⺯��
    ulRst = AT_RcvMtaJamDetectInd((VOS_VOID*)pRcvMsg);
    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRst);
	GlobalMockObject::verify();
}
TEST_F(Test_AT_RcvMtaJamDetectInd, Test_AT_RcvMtaJamDetectInd_002)
{
    // ��������
    VOS_UINT32                          ulRst;
    VOS_CHAR                           *pcExpectStr;

    /* ������ʼ�� */
    pcExpectStr = "\r\n^JDET: JAMMED\r\n";

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    pstJamInd->enJamResult = MTA_AT_JAM_RESULT_JAM_DISCOVERED;
/*
	MOCKER(At_ClientIdToUserId)
		.stubs()
        .with(eq(usClientId),outBoundP((VOS_UINT8 *)&ucIndex, sizeof(ucIndex)))
		.will(returnValue((TAF_UINT32)AT_SUCCESS));*/


	MOCKER(At_ClientIdToUserId)
		.stubs()
		.will(returnValue((VOS_UINT32)AT_SUCCESS));

	MOCKER(At_FormatResultData)
		.stubs();
    // ���ñ��⺯��
    ulRst = AT_RcvMtaJamDetectInd((VOS_VOID*)pRcvMsg);
    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRst);
    ASSERT_STREQ((VOS_CHAR *)pgucAtSndCodeAddr, pcExpectStr);
	GlobalMockObject::verify();
}


TEST_F(Test_AT_RcvMtaJamDetectInd, Test_AT_RcvMtaJamDetectInd_003)
{
    // ��������
    VOS_UINT32                          ulRst;
    VOS_CHAR                           *pcExpectStr;

    /* ������ʼ�� */
    pcExpectStr = "\r\n^JDET: DETECTING\r\n";

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    pstJamInd->enJamResult = MTA_AT_JAM_RESULT_JAM_DISAPPEARED;

	MOCKER(At_ClientIdToUserId)
		.stubs()
		.will(returnValue((VOS_UINT32)AT_SUCCESS));


    // ���ñ��⺯��
    ulRst = AT_RcvMtaJamDetectInd((VOS_VOID*)pRcvMsg);
    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRst);
    ASSERT_STREQ((VOS_CHAR *)pgucAtSndCodeAddr, pcExpectStr);
	GlobalMockObject::verify();
}

