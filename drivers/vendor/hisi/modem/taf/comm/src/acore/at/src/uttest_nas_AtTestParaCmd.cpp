#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_AtTestParaCmd.h"


#define    THIS_FILE_ID                 PS_FILE_ID_AT_TESTPARACMD_C

//�����������ã����������ùؼ���ʱ��Ҫ��ǰ׺ testing::
using namespace testing;

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


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


class Test_At_TestCgpaddr: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex = 0;

    }
    void TearDown()
    {

    }
protected:
    VOS_UINT8                   ucIndex;
};



TEST_F(Test_At_TestCgpaddr, Test_At_TestCgpaddr_002)
{
    /*��������*/
    VOS_UINT32                          ulRst = 0;

    /* ȫ�ֱ�����ֵ */
    gastAtClientTab[ucIndex].usClientId = 0;
    gucAtParaIndex                  = 1;
    gastAtParaList[0].usParaLen     = 2;

    /* ׮���� */
    MOCKER(TAF_PS_SndMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));


    /* ������Ϣ��ں��� */
    ulRst = At_TestCgpaddr(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();

}

TEST_F(Test_At_TestCgpaddr, Test_At_TestCgpaddr_003)
{
    /*��������*/
    VOS_UINT32                          ulRst = 0;

    /* ȫ�ֱ�����ֵ */
    gastAtClientTab[ucIndex].usClientId = 0;
    gucAtParaIndex                  = 1;
    gastAtParaList[0].usParaLen     = 2;

    /* ׮���� */
    MOCKER(TAF_PS_SndMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));


    /* ������Ϣ��ں��� */
    ulRst = At_TestCgpaddr(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_ERROR, ulRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();

}


class Test_AT_TestCposrPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = AT_CLIENT_TAB_MODEM_INDEX;

        stCmdInfo.ulCmdIndex        = AT_CMD_CPOSR;
        stCmdInfo.pfnSetProc        = AT_SetCposrPara;
        stCmdInfo.ulSetTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnQryProc        = AT_QryCposrPara;
        stCmdInfo.ulQryTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnTestProc       = AT_TestCposrPara;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"+CPOSR";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(0,1)";

        PS_MEM_SET(g_stParseContext, 0, sizeof(AT_PARSE_CONTEXT_STRU)*AT_MAX_CLIENT_NUM);

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;

    }

    void TearDown()
    {
    }

    VOS_UINT8                   ucIndex;
    AT_PAR_CMD_ELEMENT_STRU     stCmdInfo;
};


TEST_F(Test_AT_TestCposrPara, Test_AT_TestCposrPara_001)
{
    // ��������
    VOS_UINT32                          ulRet;

    // ������ʼ��

    // ��ʼ��ȫ�ֱ���;

    // MOCKER����;
    MOCKER(AT_IsApPort)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    // ���ñ��⺯��
    ulRet = AT_TestCposrPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen("+CPOSR: (0,1)"));

    GlobalMockObject::verify();
}


TEST_F(Test_AT_TestCposrPara, Test_AT_TestCposrPara_002)
{
    // ��������
    VOS_UINT32                          ulRet;

    // ������ʼ��

    // ��ʼ��ȫ�ֱ���;

    // MOCKER����;
    MOCKER(AT_IsApPort)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    // ���ñ��⺯��
    ulRet = AT_TestCposrPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}


class Test_AT_TestCbgPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = AT_CLIENT_TAB_APP_INDEX;

        stCmdInfo.ulCmdIndex        = AT_CMD_CBG;
        stCmdInfo.pfnSetProc        = AT_SetCbgPara;
        stCmdInfo.ulSetTimeOut      = AT_SET_PARA_TIME;
        stCmdInfo.pfnQryProc        = AT_QryCbgPara;
        stCmdInfo.ulQryTimeOut      = AT_QRY_PARA_TIME;
        stCmdInfo.pfnTestProc       = AT_TestCbgPara;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^CBG";
        stCmdInfo.pszParam          = (VOS_UINT8*)"(0,1)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }

    void TearDown()
    {

    }

    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
};


TEST_F(Test_AT_TestCbgPara, Test_AT_TestCbgPara_001)
{
    // ��������
    VOS_UINT32                          ulRslt;
    VOS_CHAR                           *pStr = "^CBG: (0,1)";

    // ������ʼ��

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_TestCbgPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRslt);
    ASSERT_STREQ(pStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen("^CBG: (0,1)"));

    GlobalMockObject::verify();
}


class Test_AT_TestCnmaPara: public ::testing::Test
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


TEST_F(Test_AT_TestCnmaPara,Test_AT_TestCnmaPara_001)
{
    // ��������
    TAF_UINT8                           ucIndex = 0;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+CNMA: (0-2)";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement;

    AT_SMS_CMD_TAB_STRU                 stSmsElement = {AT_CMD_CNMA,
                                                        At_SetCnmaPara, AT_SMS_SET_PARA_TIME,
                                                        AT_TestCnmaPara, AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,        AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"+CNMA",  TAF_NULL_PTR, (TAF_UINT8*)"(0-2),(0-65535)"};

    // ������ʼ��

    // ���ȫ�ֱ�����ʼ��
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.enCmgfMsgFormat        = AT_CMGF_MSG_FORMAT_PDU;
    stCmdElement.pszCmdName                                     = stSmsElement.pszCmdName;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_TestCnmaPara(ucIndex);

    // ִ�м��
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_AT_TestCnmaPara,Test_AT_TestCnmaPara_002)
{
    // ��������
    TAF_UINT8                           ucIndex = 0;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+CNMA: (0-2)";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement;

    AT_SMS_CMD_TAB_STRU                 stSmsElement = {AT_CMD_CNMA,
                                                        At_SetCnmaPara, AT_SMS_SET_PARA_TIME,
                                                        AT_TestCnmaPara, AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,        AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"+CNMA",  TAF_NULL_PTR, (TAF_UINT8*)"(0-2),(0-65535)"};

    // ������ʼ��

    // ���ȫ�ֱ�����ʼ��
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.enCmgfMsgFormat        = AT_CMGF_MSG_FORMAT_PDU;
    stCmdElement.pszCmdName                                     = stSmsElement.pszCmdName;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_TestCnmaPara(ucIndex);

    // ִ�м��
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
#endif


class Test_AT_TestCpmsPara: public ::testing::Test
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


TEST_F(Test_AT_TestCpmsPara,Test_AT_TestCpmsPara_001)
{
    // ��������
    TAF_UINT8                           ucIndex = 0;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+CPMS: (\"SM\"),(\"SM\"),(\"SM\")";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_CPMS,
                                                        At_SetCpmsPara,     AT_SET_PARA_TIME,
                                                        At_QryCpmsPara,     AT_QRY_PARA_TIME,
                                                        AT_TestCpmsPara,    AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"+CPMS",    (VOS_UINT8*)"(\"SM\"),(\"SM\"),(\"SM\")"};

    // ������ʼ��

    // ���ȫ�ֱ�����ʼ��
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.enMsgMeStorageStatus   = MN_MSG_ME_STORAGE_DISABLE;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_TestCpmsPara(ucIndex);

    // ִ�м��
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_AT_TestCpmsPara,Test_AT_TestCpmsPara_002)
{
    // ��������
    TAF_UINT8                           ucIndex = 0;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+CPMS: (\"SM\"),(\"SM\"),(\"SM\")";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_CPMS,
        At_SetCpmsPara,     AT_SET_PARA_TIME,
        At_QryCpmsPara,     AT_QRY_PARA_TIME,
        AT_TestCpmsPara,    AT_NOT_SET_TIME,
        VOS_NULL_PTR,       AT_NOT_SET_TIME,
        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
        (VOS_UINT8*)"+CPMS",    (VOS_UINT8*)"(\"SM\"),(\"SM\"),(\"SM\")"};

    // ������ʼ��

    // ���ȫ�ֱ�����ʼ��
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.enMsgMeStorageStatus   = MN_MSG_ME_STORAGE_DISABLE;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_TestCpmsPara(ucIndex);

    // ִ�м��
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
#endif
#if 0

class Test_AT_TestMemStatusPara: public ::testing::Test
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


TEST_F(Test_AT_TestMemStatusPara,Test_AT_TestMemStatusPara_001)
{
    // ��������
    TAF_UINT8                           ucIndex = 0;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "^CSASM: (0,1)";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_CSASM,
                                                        AT_SetMemStatusPara,    AT_SET_PARA_TIME,
                                                        VOS_NULL_PTR,           AT_NOT_SET_TIME,
                                                        AT_TestMemStatusPara,   AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,           AT_NOT_SET_TIME,
                                                        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
                                                        (TAF_UINT8*)"^CSASM",  (TAF_UINT8*)"(0,1)"};

    // ������ʼ��

    // ���ȫ�ֱ�����ʼ��
    gastAtClientTab[ucIndex].UserType                           = AT_APP_USER;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_TestMemStatusPara(ucIndex);

    // ִ�м��
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
#endif

class Test_AT_TestApRptPortSelectPara: public ::testing::Test
{
public:
    VOS_UINT8                          *pucSystemAppConfig;

    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitPort();
        pucSystemAppConfig          = AT_GetSystemAppConfigAddr();
        *pucSystemAppConfig         = SYSTEM_APP_ANDROID;

    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_TestApRptPortSelectPara,Test_AT_TestApRptPortSelectPara_001)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_APP_INDEX;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "^APRPTPORTSEL: (0-FFFFFFFF), (0-FFFFFFFF)";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_APRPTPORTSEL,
                                                        AT_SetApRptPortSelectPara,  AT_NOT_SET_TIME,
                                                        AT_QryApRptPortSelectPara,  AT_NOT_SET_TIME,
                                                        AT_TestApRptPortSelectPara, AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,   AT_NOT_SET_TIME,
                                                        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
                                                        (VOS_UINT8*)"^APRPTPORTSEL",    (VOS_UINT8*)"(0-FFFFFFFF), (0-FFFFFFFF)"};

    // ������ʼ��

    // ���ȫ�ֱ�����ʼ��
    gastAtClientTab[ucIndex].UserType                           = AT_APP_USER;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_TestApRptPortSelectPara(ucIndex);

    // ִ�м��
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_AT_TestUsbSwitchPara: public ::testing::Test
{
public:
    VOS_UINT8                          *pucSystemAppConfig;

    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitPort();
        pucSystemAppConfig  = AT_GetSystemAppConfigAddr();
        *pucSystemAppConfig = SYSTEM_APP_ANDROID;
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_TestUsbSwitchPara,Test_AT_TestUsbSwitchPara_001)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_MODEM_INDEX;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+USBSWITCH: (1,2)";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_USBSWITCH,
                                                        At_SetUsbSwitchPara,    AT_NOT_SET_TIME,
                                                        At_QryUsbSwitchPara,    AT_NOT_SET_TIME,
                                                        AT_TestUsbSwitchPara,   AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,   AT_NOT_SET_TIME,
                                                        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
                                                        (VOS_UINT8*)"+USBSWITCH",    (VOS_UINT8*)"(1,2)"};

    // ������ʼ��

    // ���ȫ�ֱ�����ʼ��
    gastAtClientTab[ucIndex].UserType                           = AT_APP_USER;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_TestUsbSwitchPara(ucIndex);

    // ִ�м��
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

class Test_AT_TestApSimStPara: public ::testing::Test
{
public:
    VOS_UINT8                          *pucSystemAppConfig;

    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitPort();
        pucSystemAppConfig = AT_GetSystemAppConfigAddr();
        *pucSystemAppConfig = SYSTEM_APP_ANDROID;

    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_TestApSimStPara,Test_AT_TestApSimStPara_001)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_MODEM_INDEX;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "^APSIMST: (0,1)";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_APSIMST,
                                                        AT_SetApSimStPara,      AT_SET_PARA_TIME,
                                                        VOS_NULL_PTR,           AT_NOT_SET_TIME,
                                                        AT_TestApSimStPara,     AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,   AT_NOT_SET_TIME,
                                                        AT_ERROR, CMD_TBL_PIN_IS_LOCKED,
                                                        (VOS_UINT8*)"^APSIMST",    (VOS_UINT8*)"(0,1)"};

    // ������ʼ��

    // ���ȫ�ֱ�����ʼ��
    gastAtClientTab[ucIndex].UserType                           = AT_APP_USER;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_TestApSimStPara(ucIndex);

    // ִ�м��
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    EXPECT_EQ(AT_OK, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}



class Test_At_TestCgdcont: public ::testing::Test
{
public:
    VOS_UINT8                          *pucSystemAppConfig;

    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitPort();
        pucSystemAppConfig = AT_GetSystemAppConfigAddr();
        *pucSystemAppConfig = SYSTEM_APP_ANDROID;

    }
    void TearDown()
    {

    }
};


TEST_F(Test_At_TestCgdcont,Test_At_TestCgdcont_001)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_MODEM_INDEX;
    VOS_UINT32                          ulRslt;

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement =     {AT_CMD_CGDCONT,
        AT_SetCgdcontPara, AT_SET_PARA_TIME, AT_QryCgdcontPara, AT_QRY_PARA_TIME, At_TestCgdcont, AT_NOT_SET_TIME,
        VOS_NULL_PTR,        AT_NOT_SET_TIME,
        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
        (VOS_UINT8*)"+CGDCONT",     (VOS_UINT8*)CGDCONT_CMD_PARA_STRING};

    // ������ʼ��

    // ���ȫ�ֱ�����ʼ��
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = At_TestCgdcont(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_TestCgdcont,Test_At_TestCgdcont_002)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_MODEM_INDEX;
    VOS_UINT32                          ulRslt;

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement =     {AT_CMD_CGDCONT,
        AT_SetCgdcontPara, AT_SET_PARA_TIME, AT_QryCgdcontPara, AT_QRY_PARA_TIME, At_TestCgdcont, AT_NOT_SET_TIME,
        VOS_NULL_PTR,        AT_NOT_SET_TIME,
        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
        (VOS_UINT8*)"+CGDCONT",     (VOS_UINT8*)CGDCONT_CMD_PARA_STRING};

    // ������ʼ��

    // ���ȫ�ֱ�����ʼ��
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;
    AT_GetCommPsCtxAddr()->ucIpv6Capability = AT_IPV6_CAPABILITY_IPV4V6_OVER_TWO_PDP;

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = At_TestCgdcont(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_At_TestCgansExtPara: public ::testing::Test
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


TEST_F(Test_At_TestCgansExtPara,Test_At_TestCgansExtPara_001)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "^CGANS: (0,1)";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement =     {AT_CMD_CGANS_EXT,
        AT_SetCgansPara,    AT_SET_PARA_TIME, VOS_NULL_PTR,      AT_NOT_SET_TIME,   At_TestCgansExtPara,   AT_NOT_SET_TIME,
        VOS_NULL_PTR,        AT_NOT_SET_TIME,
        AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
        (VOS_UINT8*)"^CGANS",       (VOS_UINT8*)CGANS_EXT_CMD_PARA_STRING};

    // ������ʼ��

    // ���ȫ�ֱ�����ʼ��
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = At_TestCgansExtPara(ucIndex);

    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_AT_TestRefclkfreqPara: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;

    void SetUp()
    {
        UT_STUB_INIT();
        stCmdInfo.ulCmdIndex        = AT_CMD_REFCLKFREQ;
        stCmdInfo.pfnSetProc        = AT_SetRefclkfreqPara;
        stCmdInfo.ulSetTimeOut      = AT_SET_PARA_TIME;
        stCmdInfo.pfnQryProc        = AT_QryRefclkfreqPara;
        stCmdInfo.ulTestTimeOut     = AT_QRY_PARA_TIME;
        stCmdInfo.pfnTestProc       = AT_TestRefclkfreqPara;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.pfnAbortProc      = VOS_NULL_PTR;
        stCmdInfo.ulAbortTimeOut    = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_ERROR;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^REFCLKFREQ";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(0,1)";

        AT_ResetClientTab();

        ucIndex         = AT_CLIENT_TAB_APP_INDEX;

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
        g_stAtCommCtx.ucSystemAppConfigAddr     = SYSTEM_APP_ANDROID;
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_TestRefclkfreqPara, Test_AT_TestRefclkfreqPara_001)
{
    // ��������
    VOS_UINT32                          ulRet;

    // ������ʼ��
    ucIndex         = AT_CLIENT_TAB_PCUI_INDEX;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    ulRet = AT_TestRefclkfreqPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_TestRefclkfreqPara, Test_AT_TestRefclkfreqPara_002)
{
    // ��������
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcExpectStr = VOS_NULL_PTR;

    // ������ʼ��
    pcExpectStr     = "^REFCLKFREQ: (0,1)";

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    ulRet = AT_TestRefclkfreqPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_STREQ((VOS_CHAR*)pgucAtSndCodeAddr, pcExpectStr);

    GlobalMockObject::verify();
}



class Test_At_TestCgeqos: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitCtx();
    }
    void TearDown()
    {
        AT_InitCtx();
    }
};

TEST_F(Test_At_TestCgeqos, Test_At_TestCgeqos_001)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+CGEQOS: (1-31),(0-9),(0-262144),(0-262144),(0-262144),(0-262144)";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement =     {AT_CMD_CGEQOS,
    atSetCgeqosPara, AT_SET_PARA_TIME, atQryCgeqosPara,   AT_QRY_PARA_TIME,  At_TestCgeqos,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CGEQOS",    (VOS_UINT8*)"(1-31),(0-9),(0-262144),(0-262144),(0-262144),(0-262144)"};

    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = At_TestCgeqos(ucIndex);

    // ִ�м��
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}


class Test_At_TestCgeqosrdp: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitCtx();
    }
    void TearDown()
    {
        AT_InitCtx();
    }
};

TEST_F(Test_At_TestCgeqosrdp, Test_At_TestCgeqosrdp_001)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+CGEQOSRDP: (1-31)";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement =     {AT_CMD_CGEQOSRDP,
    atSetCgeqosrdpPara, AT_SET_PARA_TIME, VOS_NULL_PTR,   AT_NOT_SET_TIME,  At_TestCgeqosrdp,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CGEQOSRDP",    (VOS_UINT8*)"(1-31)"};

    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = At_TestCgeqosrdp(ucIndex);

    // ִ�м��
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}



class Test_At_TestCgcontrdp: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitCtx();
    }
    void TearDown()
    {
        AT_InitCtx();
    }
};

TEST_F(Test_At_TestCgcontrdp, Test_At_TestCgcontrdp_001)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+CGCONTRDP: (1-31)";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement =     {AT_CMD_CGCONTRDP,
    atSetCgcontrdpPara, AT_SET_PARA_TIME, VOS_NULL_PTR,   AT_NOT_SET_TIME,  At_TestCgcontrdp,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CGCONTRDP",    (VOS_UINT8*)"(1-31)"};

    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = At_TestCgcontrdp(ucIndex);

    // ִ�м��
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}



class Test_At_TestCgscontrdp: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitCtx();
    }
    void TearDown()
    {
        AT_InitCtx();
    }
};

TEST_F(Test_At_TestCgscontrdp, Test_At_TestCgscontrdp_001)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+CGSCONTRDP: (1-31)";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement =     {AT_CMD_CGSCONTRDP,
    atSetCgscontrdpPara, AT_SET_PARA_TIME, VOS_NULL_PTR,   AT_NOT_SET_TIME,  At_TestCgscontrdp,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CGSCONTRDP",    (VOS_UINT8*)"(1-31)"};

    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = At_TestCgscontrdp(ucIndex);

    // ִ�м��
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}



class Test_At_TestCgtftrdp: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitCtx();
    }
    void TearDown()
    {
        AT_InitCtx();
    }
};

TEST_F(Test_At_TestCgtftrdp, Test_At_TestCgtftrdp_001)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+CGTFTRDP: (1-31)";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement =     {AT_CMD_CGTFTRDP,
    atSetCgtftrdpPara, AT_SET_PARA_TIME, VOS_NULL_PTR,    AT_NOT_SET_TIME,  At_TestCgtftrdp,       AT_NOT_SET_TIME,
    VOS_NULL_PTR,        AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"+CGTFTRDP",    (VOS_UINT8*)"(1-31)"};

    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = At_TestCgtftrdp(ucIndex);

    // ִ�м��
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_IMS)

class Test_AT_TestCiregPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitCtx();
    }
    void TearDown()
    {
        AT_InitCtx();
    }
};

TEST_F(Test_AT_TestCiregPara, Test_AT_TestCiregPara_001)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+CIREG: (0-2)";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement =     {AT_CMD_CIREG,
        AT_SetCiregPara,     AT_SET_PARA_TIME,   AT_QryCiregPara,       AT_QRY_PARA_TIME,   AT_TestCiregPara,   AT_NOT_SET_TIME,
        VOS_NULL_PTR,        AT_NOT_SET_TIME,
        AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_NO_LIMITED,
        (VOS_UINT8 *)"+CIREG",   (VOS_UINT8 *)"(0-2)"};

    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_TestCiregPara(ucIndex);

    // ִ�м��
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}


class Test_AT_TestCirepPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitCtx();
    }
    void TearDown()
    {
        AT_InitCtx();
    }
};

TEST_F(Test_AT_TestCirepPara, Test_AT_TestCirepPara_001)
{
    // ��������
    TAF_UINT8                           ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                            acExpectedStr[] = "+CIREP: (0,1)";

    AT_PAR_CMD_ELEMENT_STRU             stCmdElement =     {AT_CMD_CIREP,
        AT_SetCirepPara,     AT_SET_PARA_TIME,   AT_QryCirepPara,       AT_QRY_PARA_TIME,   AT_TestCirepPara,   AT_NOT_SET_TIME,
        VOS_NULL_PTR,        AT_NOT_SET_TIME,
        AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_NO_LIMITED,
        (VOS_UINT8 *)"+CIREP",   (VOS_UINT8 *)"(0,1)"};

    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    g_stParseContext[ucIndex].pstCmdElement = &stCmdElement;

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_TestCirepPara(ucIndex);

    // ִ�м��
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}

#endif
