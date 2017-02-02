#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_AtCmdPacketProc.h"

//�����������ã����������ùؼ���ʱ��Ҫ��ǰ׺ testing::
using namespace testing;

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_AT_CMD_PACKET_PROC_C


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

AT_PAR_CMD_ELEMENT_STRU             gstDhcpCmdInfo = {AT_CMD_DHCP,
    At_SetDhcpPara, AT_SET_PARA_TIME, At_QryDhcpPara, AT_QRY_PARA_TIME, AT_TestDhcpPara, AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^DHCP", (VOS_UINT8*)"(1-11)"};

AT_PAR_CMD_ELEMENT_STRU             gstDhcpV6CmdInfo = {AT_CMD_DHCPV6,
    AT_SetDhcpv6Para,       AT_NOT_SET_TIME,  AT_QryDhcpv6Para,          AT_NOT_SET_TIME,    AT_TestDhcpv6Para, AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,       CMD_TBL_LIMITED_NULL,
    (VOS_UINT8*)"^DHCPV6",      (VOS_UINT8*)"(1-11)"};


#if (FEATURE_ON == FEATURE_AT_HSIC)

class Test_AT_SetChdataPara: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;

    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmBCreate)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(NV_ReadEx)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        MOCKER(NV_GetLength)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        AT_PS_DATA_CHANL_CFG_STRU  stTmpCfg;
        At_PidInit(VOS_IP_INITIAL);
        ucIndex = AT_CLIENT_TAB_HSIC1_INDEX;

        pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

        stTmpCfg.ulUsed        = VOS_FALSE;
        stTmpCfg.ulRmNetId     = UDI_INVAL_DEV_ID;
        stTmpCfg.ulRmNetActFlg = VOS_FALSE;

        pstModemPsCtx->astChannelCfg[1] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[2] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[3] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[4] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[5] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[6] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[7] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[8] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[9] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[10] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[11] = stTmpCfg;
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_SetChdataPara,Test_AT_SetChdataPara_001)
{
    /*��������*/
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/
    ulRet                               = TAF_FAILURE;

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_READ_CMD;
    gastAtClientTab[ucIndex].UserType   = AT_HSIC3_USER;
    gucAtParaIndex                      = 2;
    gastAtParaList[0].usParaLen         = 0;
    gastAtParaList[0].ulParaValue       = 0;
    gastAtParaList[1].usParaLen         = 1;
    gastAtParaList[1].ulParaValue       = 1;

    /*������׮*/

    /*���ñ��⺯�� */
    ulRet = AT_SetChdataPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRet);

    GlobalMockObject::verify();
}



TEST_F(Test_AT_SetChdataPara,Test_AT_SetChdataPara_002)
{
    /*��������*/
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/
    ulRet                               = TAF_FAILURE;

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gastAtClientTab[ucIndex].UserType   = AT_HSIC3_USER;
    gucAtParaIndex                      = 3;
    gastAtParaList[0].usParaLen         = 0;
    gastAtParaList[0].ulParaValue       = 0;
    gastAtParaList[1].usParaLen         = 1;
    gastAtParaList[1].ulParaValue       = 1;

    /*������׮*/

    /*���ñ��⺯�� */
    ulRet = AT_SetChdataPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetChdataPara,Test_AT_SetChdataPara_003)
{
    /*��������*/
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/
    ulRet                               = TAF_FAILURE;

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gastAtClientTab[ucIndex].UserType   = AT_USBCOM_USER;
    gucAtParaIndex                      = 2;
    gastAtParaList[0].usParaLen         = 1;
    gastAtParaList[0].ulParaValue       = 1;
    gastAtParaList[1].usParaLen         = 1;
    gastAtParaList[1].ulParaValue       = 1;

    /*������׮*/
    MOCKER(AT_CheckHsicUser)
        .expects(exactly(1))
        .will(returnValue(VOS_FALSE));

    /*���ñ��⺯�� */
    ulRet = AT_SetChdataPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetChdataPara,Test_AT_SetChdataPara_004)
{
    /*��������*/
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/
    ulRet                               = TAF_FAILURE;

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gastAtClientTab[ucIndex].UserType   = AT_HSIC3_USER;
    gucAtParaIndex                      = 2;
    gastAtParaList[0].usParaLen         = 0;
    gastAtParaList[0].ulParaValue       = 0;
    gastAtParaList[1].usParaLen         = 1;
    gastAtParaList[1].ulParaValue       = 1;
    pstModemPsCtx->astChannelCfg[2].ulUsed          = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[2].ulRmNetId       = UDI_ACM_HSIC_ACM3_ID;

    /*������׮*/

    /*���ñ��⺯�� */
    ulRet = AT_SetChdataPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetChdataPara,Test_AT_SetChdataPara_005)
{
    /*��������*/
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/
    ulRet                               = TAF_FAILURE;

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gastAtClientTab[ucIndex].UserType   = AT_HSIC3_USER;
    gucAtParaIndex                      = 2;
    gastAtParaList[0].usParaLen         = 1;
    gastAtParaList[0].ulParaValue       = 2;
    gastAtParaList[1].usParaLen         = 0;
    gastAtParaList[1].ulParaValue       = 0;
    pstModemPsCtx->astChannelCfg[2].ulUsed          = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[2].ulRmNetId       = UDI_ACM_HSIC_ACM3_ID;

    /*������׮*/

    /*���ñ��⺯�� */
    ulRet = AT_SetChdataPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(VOS_FALSE,     pstModemPsCtx->astChannelCfg[2].ulUsed);
    EXPECT_EQ(UDI_INVAL_DEV_ID, pstModemPsCtx->astChannelCfg[2].ulRmNetId);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetChdataPara,Test_AT_SetChdataPara_006)
{
    /*��������*/
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/
    ulRet                               = TAF_FAILURE;

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gastAtClientTab[ucIndex].UserType   = AT_HSIC1_USER;
    gucAtParaIndex                      = 2;
    gastAtParaList[0].usParaLen         = 1;
    gastAtParaList[0].ulParaValue       = 1;
    gastAtParaList[1].usParaLen         = 1;
    gastAtParaList[1].ulParaValue       = 2;
    pstModemPsCtx->astChannelCfg[2].ulUsed          = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[2].ulRmNetId       = UDI_ACM_HSIC_ACM3_ID;

    /*������׮*/
    MOCKER(mdrv_misc_support_check)
        .expects(exactly(1))
        .will(returnValue(BSP_MODULE_UNSUPPORT));

    /*���ñ��⺯�� */
    ulRet = AT_SetChdataPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_ERROR, ulRet);
    EXPECT_EQ(VOS_FALSE,     pstModemPsCtx->astChannelCfg[1].ulUsed);
    EXPECT_EQ(UDI_INVAL_DEV_ID, pstModemPsCtx->astChannelCfg[1].ulRmNetId);

    GlobalMockObject::verify();
}



TEST_F(Test_AT_SetChdataPara,Test_AT_SetChdataPara_007)
{
    /*��������*/
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/
    ulRet                               = TAF_FAILURE;

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gastAtClientTab[ucIndex].UserType   = AT_HSIC1_USER;
    gucAtParaIndex                      = 2;
    gastAtParaList[0].usParaLen         = 1;
    gastAtParaList[0].ulParaValue       = 1;
    gastAtParaList[1].usParaLen         = 1;
    gastAtParaList[1].ulParaValue       = 1;

    /*������׮*/
    MOCKER(mdrv_misc_support_check)
        .expects(exactly(1))
        .will(returnValue(BSP_MODULE_UNSUPPORT));
    /*���ñ��⺯�� */
    ulRet = AT_SetChdataPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(VOS_TRUE, pstModemPsCtx->astChannelCfg[1].ulUsed);
    EXPECT_EQ(UDI_ACM_HSIC_ACM1_ID, pstModemPsCtx->astChannelCfg[1].ulRmNetId);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetChdataPara,Test_AT_SetChdataPara_008)
{
    /*��������*/
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/
    ulRet                               = TAF_FAILURE;

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gastAtClientTab[ucIndex].UserType   = AT_HSIC1_USER;
    gucAtParaIndex                      = 2;
    gastAtParaList[0].usParaLen         = 1;
    gastAtParaList[0].ulParaValue       = 1;
    gastAtParaList[1].usParaLen         = 1;
    gastAtParaList[1].ulParaValue       = 3;

    /*������׮*/
    MOCKER(mdrv_misc_support_check)
        .expects(exactly(1))
        .will(returnValue(BSP_MODULE_UNSUPPORT));
    /*���ñ��⺯�� */
    ulRet = AT_SetChdataPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(VOS_TRUE, pstModemPsCtx->astChannelCfg[1].ulUsed);
    EXPECT_EQ(UDI_ACM_HSIC_ACM5_ID, pstModemPsCtx->astChannelCfg[1].ulRmNetId);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetChdataPara,Test_AT_SetChdataPara_009)
{
    /*��������*/
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/
    ulRet                               = TAF_FAILURE;

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gastAtClientTab[ucIndex].UserType   = AT_HSIC3_USER;
    gucAtParaIndex                      = 2;
    gastAtParaList[0].usParaLen         = 1;
    gastAtParaList[0].ulParaValue       = 2;
    gastAtParaList[1].usParaLen         = 0;
    gastAtParaList[1].ulParaValue       = 0;
    pstModemPsCtx->astChannelCfg[2].ulUsed          = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[2].ulRmNetId       = UDI_ACM_HSIC_ACM3_ID;
    pstModemPsCtx->astChannelCfg[2].ulRmNetActFlg   = VOS_TRUE;

    /*������׮*/

    /*���ñ��⺯�� */
    ulRet = AT_SetChdataPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_ERROR, ulRet);
    EXPECT_EQ(VOS_TRUE,             pstModemPsCtx->astChannelCfg[2].ulUsed);
    EXPECT_EQ(UDI_ACM_HSIC_ACM3_ID, pstModemPsCtx->astChannelCfg[2].ulRmNetId);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetChdataPara,Test_AT_SetChdataPara_010)
{
    /*��������*/
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/
    ulRet                               = TAF_FAILURE;

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gastAtClientTab[ucIndex].UserType   = AT_HSIC1_USER;
    gucAtParaIndex                      = 2;
    gastAtParaList[0].usParaLen         = 1;
    gastAtParaList[0].ulParaValue       = 1;
    gastAtParaList[1].usParaLen         = 1;
    gastAtParaList[1].ulParaValue       = 1;

    /*������׮*/
    MOCKER(mdrv_misc_support_check)
        .expects(exactly(1))
        .will(returnValue(BSP_MODULE_SUPPORT));
    /*���ñ��⺯�� */
    ulRet = AT_SetChdataPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(VOS_TRUE, pstModemPsCtx->astChannelCfg[1].ulUsed);
    EXPECT_EQ(UDI_NCM_HSIC_NCM0_ID, pstModemPsCtx->astChannelCfg[1].ulRmNetId);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetChdataPara,Test_AT_SetChdataPara_011)
{
    /*��������*/
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/
    ulRet                               = TAF_FAILURE;

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gastAtClientTab[ucIndex].UserType   = AT_HSIC1_USER;
    gucAtParaIndex                      = 2;
    gastAtParaList[0].usParaLen         = 1;
    gastAtParaList[0].ulParaValue       = 1;
    gastAtParaList[1].usParaLen         = 1;
    gastAtParaList[1].ulParaValue       = 2;

    /*������׮*/
    MOCKER(mdrv_misc_support_check)
        .expects(exactly(1))
        .will(returnValue(BSP_MODULE_SUPPORT));
    /*���ñ��⺯�� */
    ulRet = AT_SetChdataPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(VOS_TRUE, pstModemPsCtx->astChannelCfg[1].ulUsed);
    EXPECT_EQ(UDI_NCM_HSIC_NCM1_ID, pstModemPsCtx->astChannelCfg[1].ulRmNetId);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetChdataPara,Test_AT_SetChdataPara_012)
{
    /*��������*/
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/
    ulRet                               = TAF_FAILURE;

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gastAtClientTab[ucIndex].UserType   = AT_HSIC1_USER;
    gucAtParaIndex                      = 2;
    gastAtParaList[0].usParaLen         = 1;
    gastAtParaList[0].ulParaValue       = 1;
    gastAtParaList[1].usParaLen         = 1;
    gastAtParaList[1].ulParaValue       = 3;

    /*������׮*/
    MOCKER(mdrv_misc_support_check)
        .expects(exactly(1))
        .will(returnValue(BSP_MODULE_SUPPORT));
    /*���ñ��⺯�� */
    ulRet = AT_SetChdataPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(VOS_TRUE, pstModemPsCtx->astChannelCfg[1].ulUsed);
    EXPECT_EQ(UDI_NCM_HSIC_NCM2_ID, pstModemPsCtx->astChannelCfg[1].ulRmNetId);

    GlobalMockObject::verify();
}

class Test_AT_QryChdataPara: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmBCreate)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(NV_ReadEx)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        MOCKER(NV_GetLength)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        At_PidInit(VOS_IP_INITIAL);
        ucIndex = AT_CLIENT_TAB_HSIC1_INDEX;

        pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

        stCmdInfo.ulCmdIndex        = AT_CMD_CHDATA;
        stCmdInfo.pfnSetProc        = AT_SetChdataPara;
        stCmdInfo.ulSetTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnQryProc        = AT_QryChdataPara;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.pfnTestProc       = VOS_NULL_PTR;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^CHDATA";
        stCmdInfo.pszParam          = (VOS_UINT8*)"(1-11),(1-3)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
        gastAtClientTab[ucIndex].UserType       = AT_HSIC3_USER;

    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_QryChdataPara,Test_AT_QryChdataPara_001)
{
    /*��������*/
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/
    ulRet           = TAF_FAILURE;

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_TEST_CMD;

    /*������׮*/

    /*���ñ��⺯�� */
    ulRet = AT_QryChdataPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_QryChdataPara,Test_AT_QryChdataPara_002)
{
    /*��������*/
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/
    ulRet           = TAF_FAILURE;

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_READ_CMD;
    pstModemPsCtx->astChannelCfg[1].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[2].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[3].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[4].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[5].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[6].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[7].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[8].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[9].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[10].ulUsed         = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[11].ulUsed         = VOS_FALSE;

    /*������׮*/

    /*���ñ��⺯�� */
    ulRet = AT_QryChdataPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(0, gstAtSendData.usBufLen);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_QryChdataPara,Test_AT_QryChdataPara_003)
{
    /*��������*/
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcExpactedStr;

    /*���ر�����ʼ��*/
    ulRet           = TAF_FAILURE;
    pcExpactedStr   = "^CHDATA: 1,2\r\n^CHDATA: 2,3\r\n^CHDATA: 11,1";

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_READ_CMD;
    pstModemPsCtx->astChannelCfg[1].ulUsed          = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[1].ulRmNetId       = UDI_ACM_HSIC_ACM3_ID;
    pstModemPsCtx->astChannelCfg[2].ulUsed          = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[2].ulRmNetId       = UDI_ACM_HSIC_ACM5_ID;
    pstModemPsCtx->astChannelCfg[3].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[4].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[5].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[6].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[7].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[8].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[9].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[10].ulUsed         = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[11].ulUsed         = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[11].ulRmNetId      = UDI_ACM_HSIC_ACM1_ID;

    /*������׮*/

    /*���ñ��⺯�� */
    ulRet = AT_QryChdataPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(VOS_StrLen(pcExpactedStr), gstAtSendData.usBufLen);
    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_QryChdataPara,Test_AT_QryChdataPara_004)
{
    /*��������*/
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/
    ulRet           = TAF_FAILURE;

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_READ_CMD;
    gastAtClientTab[ucIndex].UserType   = AT_COM_USER;

    /*������׮*/
    MOCKER(AT_CheckHsicUser)
        .expects(exactly(1))
        .will(returnValue(VOS_FALSE));

    /*���ñ��⺯�� */
    ulRet = AT_QryChdataPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_QryChdataPara,Test_AT_QryChdataPara_005)
{
    /*��������*/
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcExpactedStr;

    /*���ر�����ʼ��*/
    ulRet           = TAF_FAILURE;
    pcExpactedStr   = "^CHDATA: 1,2\r\n^CHDATA: 2,3\r\n^CHDATA: 11,1";

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_READ_CMD;
    pstModemPsCtx->astChannelCfg[1].ulUsed          = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[1].ulRmNetId       = UDI_NCM_HSIC_NCM1_ID;
    pstModemPsCtx->astChannelCfg[2].ulUsed          = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[2].ulRmNetId       = UDI_NCM_HSIC_NCM2_ID;
    pstModemPsCtx->astChannelCfg[3].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[4].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[5].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[6].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[7].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[8].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[9].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[10].ulUsed         = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[11].ulUsed         = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[11].ulRmNetId      = UDI_NCM_HSIC_NCM0_ID;

    /*������׮*/

    /*���ñ��⺯�� */
    ulRet = AT_QryChdataPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(VOS_StrLen(pcExpactedStr), gstAtSendData.usBufLen);
    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}



TEST_F(Test_AT_QryChdataPara,Test_AT_QryChdataPara_006)
{
    /*��������*/
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcExpactedStr;

    /*���ر�����ʼ��*/
    ulRet           = TAF_FAILURE;
    pcExpactedStr   = "^CHDATA: 1,2\r\n^CHDATA: 2,3\r\n^CHDATA: 11,1";

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_READ_CMD;
    pstModemPsCtx->astChannelCfg[1].ulUsed          = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[1].ulRmNetId       = UDI_NCM_NDIS_ID;

    /*������׮*/

    /*���ñ��⺯�� */
    ulRet = AT_QryChdataPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}

class Test_AT_TestChdataPara: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    VOS_UINT8                          *pucSystemAppConfig;

    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitPort();
        ucIndex                     = AT_CLIENT_TAB_APP_INDEX;
        pucSystemAppConfig          = AT_GetSystemAppConfigAddr();
        *pucSystemAppConfig         = SYSTEM_APP_ANDROID;

        stCmdInfo.ulCmdIndex        = AT_CMD_CHDATA;
        stCmdInfo.pfnSetProc        = AT_SetChdataPara;
        stCmdInfo.ulSetTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnQryProc        = AT_QryChdataPara;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.pfnTestProc       = VOS_NULL_PTR;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^CHDATA";
        stCmdInfo.pszParam          = (VOS_UINT8*)"(1-31),(1-5)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
        gastAtClientTab[ucIndex].UserType       = AT_APP_USER;

    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_TestChdataPara,Test_AT_TestChdataPara_001)
{
    /*��������*/
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_TEST_CMD;

    /*������׮*/
    MOCKER(AT_CheckHsicUser).stubs().will(returnValue(VOS_FALSE));

    /*���ñ��⺯�� */
    ulRet = AT_TestChdataPara(AT_CLIENT_TAB_PCUI_INDEX);

    /* �����֤*/
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_TestChdataPara,Test_AT_TestChdataPara_002)
{
    /*��������*/
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcExpactedStr;

    /*���ر�����ʼ��*/
#if (FEATURE_ON == FEATURE_LTE)
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    pcExpactedStr   = "^CHDATA: (1-31),(1-5)";
#else
    pcExpactedStr   = "^CHDATA: (1-31),(1-3)";
#endif
#else
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    pcExpactedStr   = "^CHDATA: (1-11),(1-5)";
#else
    pcExpactedStr   = "^CHDATA: (1-11),(1-3)";
#endif
#endif

    /*���ر�����ʼ��*/

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_TEST_CMD;

    /*������׮*/

    /*���ñ��⺯�� */
    ulRet = AT_TestChdataPara(AT_CLIENT_TAB_APP_INDEX);

    /* �����֤*/
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(VOS_StrLen(pcExpactedStr), gstAtSendData.usBufLen);
    EXPECT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}
#endif
class Test_At_SetDhcpPara: public ::testing::Test
{
public:
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;
    AT_PS_CALL_ENTITY_STRU             *pstPsCallEntity;

    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmP)
            .stubs()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(VOS_SmV)
            .stubs()
            .will(returnValue((VOS_UINT32)VOS_OK));

        ucCid                           = 1;
        ucIndex                         = AT_CLIENT_TAB_APP_INDEX;
        g_stATParseCmd.ucCmdOptType     = AT_CMD_OPT_SET_PARA_CMD;
        PS_MEM_SET(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName            = (VOS_UINT8*)"^DHCP";
        stCmdInfo.pszParam              = (VOS_UINT8 *)"(1,11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;

        gastAtClientTab[ucIndex].UserType   = AT_HSIC4_USER;
        gastAtParaList[0].usParaLen         = 1;
        gastAtParaList[0].aucPara[0]        = ucCid;
        gastAtParaList[0].ulParaValue       = ucCid;
        gucAtParaIndex                      = 1;

        AT_InitCtx();
        pstPsCallEntity = AT_PS_GetCallEntity(ucIndex, 0);
        pstPsCallEntity->enIpv4State    = AT_PDP_STATE_ACTED;
        pstPsCallEntity->ucIpv4Cid      = 1;

        pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);
        pstModemPsCtx->aucCidToIndexTbl[ucCid]   = 0;

    }

    void TearDown()
    {

    }
};

TEST_F(Test_At_SetDhcpPara, Test_At_SetDhcpPara_001)
{
    // ��������
    VOS_UINT32                          ulRslt;

    // ������ʼ��
    ucIndex                                 = AT_CLIENT_TAB_APP_INDEX;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    gastAtClientTab[ucIndex].UserType       = AT_HSIC1_USER;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = At_SetDhcpPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_At_SetDhcpPara, Test_At_SetDhcpPara_002)
{
    // ��������
    VOS_UINT32                          ulRslt;

    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    ucIndex                             = AT_CLIENT_TAB_NDIS_INDEX;

    g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = At_SetDhcpPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_At_SetDhcpPara, Test_At_SetDhcpPara_003)
{
    // ��������
    VOS_UINT32                          ulRslt;
    // ������ʼ��
    ucIndex                                 = AT_CLIENT_TAB_APP_INDEX;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    gastAtClientTab[ucIndex].UserType       = AT_HSIC3_USER;

    // ��ʼ��ȫ�ֱ���
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_CMD_NO_PARA;

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = At_SetDhcpPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_At_SetDhcpPara, Test_At_SetDhcpPara_004)
{
    // ��������
    VOS_UINT32                          ulRslt;
    // ������ʼ��
    ucIndex                                 = AT_CLIENT_TAB_APP_INDEX;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    gastAtClientTab[ucIndex].UserType       = AT_HSIC2_USER;

    // ��ʼ��ȫ�ֱ���
    gucAtParaIndex                      = 2;

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = At_SetDhcpPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_At_SetDhcpPara, Test_At_SetDhcpPara_005)
{
    // ��������
    VOS_UINT32                          ulRslt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    pstPsCallEntity->enIpv4State    = AT_PDP_STATE_DEACTING;

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = At_SetDhcpPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_ERROR, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_At_SetDhcpPara, Test_At_SetDhcpPara_006)
{
    // ��������
    VOS_UINT32                          ulRslt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(AT_GetDisplayRate)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));

    // ���ñ��⺯��
    ulRslt = At_SetDhcpPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_At_SetDhcpPara, Test_At_SetDhcpPara_007)
{
    // ��������
    VOS_UINT32                          ulRslt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    gastAtParaList[0].ulParaValue        = ucCid + 1;

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = At_SetDhcpPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_ERROR, ulRslt);
    GlobalMockObject::verify();
}



class Test_At_QryDhcpPara_AppUser: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmBCreate)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(NV_ReadEx)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        MOCKER(NV_GetLength)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        At_PidInit(VOS_IP_INITIAL);

        g_stParseContext[AT_CLIENT_TAB_PCUI_INDEX].pstCmdElement = &gstDhcpCmdInfo;
    }
    void TearDown()
    {

    }
//protected:
    //VOS_UINT8                   ucIndex;
};


TEST_F(Test_At_QryDhcpPara_AppUser, Test_At_QryDhcpPara_AppUser_001)
{
    //��������

    g_stAtAppPdpEntity.enIpv4State = AT_PDP_STATE_IDLE;

    g_stAtAppPdpEntity.enIpv6State = AT_PDP_STATE_IDLE;

    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_WEBUI;

    /* ��ѯAT^DHCP? */
    EXPECT_EQ(AT_ERROR, At_QryDhcpPara(AT_CLIENT_TAB_PCUI_INDEX));

    /* �ϱ���� */

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_QryDhcpPara_AppUser, Test_At_QryDhcpPara_AppUser_002)
{
    VOS_UINT32                          ulResult;
    VOS_CHAR                            acAtSndCode[100];

    /*���ر�����ʼ��*/
    PS_MEM_SET(acAtSndCode, 0 ,100);

    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_WEBUI;
    g_stAtAppPdpEntity.enIpv4State = AT_PDP_STATE_ACTED;
    g_stAtAppPdpEntity.enIpv4v6State = AT_PDP_STATE_IDLE;
    g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4Addr = 0xC0A83D41;
    g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4GateWay = 0xC0A83D42;
    g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4NetMask = 0xFFFFFF00;

    gastAtClientTab[AT_CLIENT_TAB_PCUI_INDEX].UserType = AT_USBCOM_USER;

    MOCKER(AT_GetDisplayRate)
        .stubs()
        .will(returnValue(VOS_ERR));

    //MOCKER(At_sprintf).expects(exactly(9));

    /* ��ѯAT^DHCP? */
    ulResult = At_QryDhcpPara(AT_CLIENT_TAB_PCUI_INDEX);

    PS_MEM_CPY(acAtSndCode, (char *)pgucAtSndCodeAddr, VOS_StrLen((VOS_CHAR *)pgucAtSndCodeAddr));

    EXPECT_EQ(AT_OK, ulResult);

    /* �ϱ���� */

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
TEST_F(Test_At_QryDhcpPara_AppUser, Test_At_QryDhcpPara_AppUser_003)
{
    VOS_UINT32                          ulResult;

    VOS_UINT32                          ulSpeed = 14400000;

    TAF_AGENT_SYS_MODE_STRU             stSysMode = {0};
	/* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
    stSysMode.enRatType     = TAF_MMA_RAT_WCDMA;
	/* Modified by h00313353 for Iteration 13, 2015-4-10, end */
    stSysMode.enSysSubMode  = TAF_SYS_SUBMODE_WCDMA;

    gastAtClientTab[AT_CLIENT_TAB_PCUI_INDEX].UserType = AT_USBCOM_USER;

    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_WEBUI;
    g_stAtAppPdpEntity.enIpv4State = AT_PDP_STATE_ACTED;
    g_stAtAppPdpEntity.enIpv4v6State = AT_PDP_STATE_IDLE;
    g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4Addr = 0xC0A83D41;
    g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4GateWay = 0xC0A83D42;
    g_stAtAppPdpEntity.stIpv4Dhcp.ulIpv4NetMask = 0xFFFFFF00;

    MOCKER(TAF_AGENT_GetSysMode)
        .stubs()
        .with(any(), outBoundP(&stSysMode))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_GetDisplayRate)
        .expects(exactly(1))
        .with(any(), outBoundP((VOS_UINT32 *)&ulSpeed, (VOS_UINT32)sizeof(ulSpeed)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    //MOCKER(At_sprintf).expects(exactly(9));

    /* ��ѯAT^DHCP? */
    ulResult = At_QryDhcpPara(AT_CLIENT_TAB_PCUI_INDEX);

    EXPECT_EQ(AT_OK, ulResult);

    /* �ϱ���� */

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
//#endif


class Test_At_QryDhcpPara_NdisUser: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmBCreate)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(NV_ReadEx)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        MOCKER(NV_GetLength)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        MOCKER(VOS_SmP)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(VOS_SmV)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        At_PidInit(VOS_IP_INITIAL);
        ucIndex = 0;
        g_stParseContext[ucIndex].pstCmdElement = &gstDhcpCmdInfo;
    }
    void TearDown()
    {

    }
protected:
    VOS_UINT8                   ucIndex;
};


TEST_F(Test_At_QryDhcpPara_NdisUser, Test_At_QryDhcpPara_NdisUser_001)
{
    //��������

    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_MP;

    g_stAtNdisDhcpPara.enIpv4State = AT_PDP_STATE_DEACTING;

    g_stAtNdisDhcpPara.enIpv6State = AT_PDP_STATE_IDLE;

    /* ��ѯAT^DHCP? */
    EXPECT_EQ(AT_ERROR, At_QryDhcpPara(AT_CLIENT_TAB_PCUI_INDEX));

    /* �ϱ���� */

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_QryDhcpPara_NdisUser, Test_At_QryDhcpPara_NdisUser_002)
{
    VOS_UINT32                          ulResult;
    VOS_CHAR                           *pcExpactedStr;

    /*���ر�����ʼ��*/
    pcExpactedStr   = "^DHCP: 413DA8C0,FFFFFF,423DA8C0,423DA8C0,0,0,81920000,81920000";

    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_MP;
    g_stAtNdisDhcpPara.enIpv4State = AT_PDP_STATE_ACTED;
    g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4Addr = 0xC0A83D41;
    g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4GateWay = 0xC0A83D42;
    g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4NetMask = 0xFFFFFF00;

    gastAtClientTab[AT_CLIENT_TAB_PCUI_INDEX].UserType = AT_USBCOM_USER;

    MOCKER(AT_GetDisplayRate)
        .stubs()
        .will(returnValue(VOS_ERR));

    //MOCKER(At_sprintf).expects(exactly(9));

    /* ��ѯAT^DHCP? */
    ulResult = At_QryDhcpPara(AT_CLIENT_TAB_PCUI_INDEX);

    EXPECT_EQ(AT_OK, ulResult);

    /* �ϱ���� */
    //ASSERT_STREQ(pcExpactedStr, (char *)pgucAtSndCodeAddr);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
TEST_F(Test_At_QryDhcpPara_NdisUser, Test_At_QryDhcpPara_NdisUser_003)
{
    VOS_UINT32                          ulResult;
    VOS_CHAR                           *pcExpactedStr;

    /*���ر�����ʼ��*/
    pcExpactedStr   = "^DHCP: 413DA8C0,FFFFFF,423DA8C0,423DA8C0,0,0,14400000,14400000";

    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_MP;
    g_stAtNdisDhcpPara.enIpv4State = AT_PDP_STATE_ACTED;
    g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4Addr = 0xC0A83D41;
    g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4GateWay = 0xC0A83D42;
    g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4NetMask = 0xFFFFFF00;

    gastAtClientTab[AT_CLIENT_TAB_PCUI_INDEX].UserType = AT_USBCOM_USER;

    //MOCKER(At_sprintf).expects(exactly(9));

    /* ��ѯAT^DHCP? */
    ulResult = At_QryDhcpPara(AT_CLIENT_TAB_PCUI_INDEX);

    EXPECT_EQ(AT_OK, ulResult);

    /* �ϱ���� */
    //EXPECT_STREQ(pcExpactedStr, (char *)pgucAtSndCodeAddr);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
class Test_AT_TestDhcpPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = AT_CLIENT_TAB_APP_INDEX;
        memset(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^DHCP";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(1,11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }

    void TearDown()
    {
    }

    VOS_UINT8                   ucIndex;
    AT_PAR_CMD_ELEMENT_STRU     stCmdInfo;
};

TEST_F(Test_AT_TestDhcpPara, Test_AT_TestDhcpPara_001)
{
    // ��������

    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    gastAtClientTab[ucIndex].UserType   = AT_HSIC4_USER;

    // MOCKER����

    // ���ñ��⺯��
    AT_TestDhcpPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen("^DHCP: (1-11)"));
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_IPV6)


class Test_At_SetDhcpv6Para: public ::testing::Test
{
public:
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;
    AT_PS_CALL_ENTITY_STRU             *pstPsCallEntity;

    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmP)
            .stubs()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(VOS_SmV)
            .stubs()
            .will(returnValue((VOS_UINT32)VOS_OK));

        ucCid                           = 1;
        ucIndex                         = AT_CLIENT_TAB_APP_INDEX;
        g_stATParseCmd.ucCmdOptType     = AT_CMD_OPT_SET_PARA_CMD;
        PS_MEM_SET(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName            = (VOS_UINT8*)"^DHCP";
        stCmdInfo.pszParam              = (VOS_UINT8 *)"(1,11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;

        gastAtClientTab[ucIndex].UserType   = AT_HSIC4_USER;
        gastAtParaList[0].usParaLen         = 1;
        gastAtParaList[0].aucPara[0]        = ucCid;
        gastAtParaList[0].ulParaValue       = ucCid;
        gucAtParaIndex                      = 1;

        AT_InitCtx();
        pstPsCallEntity = AT_PS_GetCallEntity(ucIndex, 0);
        pstPsCallEntity->enIpv6State    = AT_PDP_STATE_ACTED;
        pstPsCallEntity->ucIpv6Cid      = 1;

        pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);
        pstModemPsCtx->aucCidToIndexTbl[ucCid]   = 0;

    }

    void TearDown()
    {

    }
};

TEST_F(Test_At_SetDhcpv6Para, Test_At_SetDhcpv6Para_001)
{
    // ��������
    VOS_UINT32                          ulRslt;

    // ������ʼ��
    ucIndex                                 = AT_CLIENT_TAB_APP_INDEX;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    gastAtClientTab[ucIndex].UserType       = AT_HSIC1_USER;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_SetDhcpv6Para(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_At_SetDhcpv6Para, Test_At_SetDhcpv6Para_002)
{
    // ��������
    VOS_UINT32                          ulRslt;

    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    ucIndex                             = AT_CLIENT_TAB_NDIS_INDEX;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_SetDhcpv6Para(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_At_SetDhcpv6Para, Test_At_SetDhcpv6Para_003)
{
    // ��������
    VOS_UINT32                          ulRslt;

    // ������ʼ��
    ucIndex                                 = AT_CLIENT_TAB_APP_INDEX;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    gastAtClientTab[ucIndex].UserType       = AT_HSIC3_USER;

    // ��ʼ��ȫ�ֱ���
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_CMD_NO_PARA;

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_SetDhcpv6Para(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_At_SetDhcpv6Para, Test_At_SetDhcpv6Para_004)
{
    // ��������
    VOS_UINT32                          ulRslt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    gucAtParaIndex                          = 2;
    ucIndex                                 = AT_CLIENT_TAB_APP_INDEX;
    g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    gastAtClientTab[ucIndex].UserType       = AT_HSIC2_USER;

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_SetDhcpv6Para(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_At_SetDhcpv6Para, Test_At_SetDhcpv6Para_005)
{
    // ��������
    VOS_UINT32                          ulRslt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    pstPsCallEntity->enIpv6State    = AT_PDP_STATE_DEACTING;

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_SetDhcpv6Para(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_ERROR, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_At_SetDhcpv6Para, Test_At_SetDhcpv6Para_006)
{
    // ��������
    VOS_UINT32                          ulRslt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(AT_GetDisplayRate)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    // ���ñ��⺯��
    ulRslt = AT_SetDhcpv6Para(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRslt);
    GlobalMockObject::verify();
}


TEST_F(Test_At_SetDhcpv6Para, Test_At_SetDhcpv6Para_007)
{
    // ��������
    VOS_UINT32                          ulRslt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    gastAtParaList[0].ulParaValue        = ucCid + 1;

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_SetDhcpv6Para(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_ERROR, ulRslt);
    GlobalMockObject::verify();
}


class Test_AT_CheckIpv6Capability: public ::testing::Test
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

TEST_F(Test_AT_CheckIpv6Capability, Test_AT_CheckIpv6Capability_001)
{
    // ��������
    VOS_UINT32                          ulRslt;

    // ������ʼ��
    AT_GetCommPsCtxAddr()->ucIpv6Capability = AT_IPV6_CAPABILITY_IPV4_ONLY;
    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_CheckIpv6Capability(AT_PDP_IPV6);

    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRslt);
    GlobalMockObject::verify();
}

TEST_F(Test_AT_CheckIpv6Capability, Test_AT_CheckIpv6Capability_002)
{
    // ��������
    VOS_UINT32                          ulRslt;

    // ������ʼ��
    AT_GetCommPsCtxAddr()->ucIpv6Capability = AT_IPV6_CAPABILITY_IPV6_ONLY;
    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_CheckIpv6Capability(AT_PDP_IPV4);

    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRslt);
    GlobalMockObject::verify();
}


class Test_At_QryDhcpV6Para_AppUser: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        //PS_MEM_SET(&gstAtSendData, 0 , sizeof(gstAtSendData));
    }
    void TearDown()
    {

    }
protected:
    VOS_UINT8                   ucIndex;
};


TEST_F(Test_At_QryDhcpV6Para_AppUser, Test_At_QryDhcpV6Para_AppUser_001)
{
    //��������

    g_stAtAppPdpEntity.enIpv4State = AT_PDP_STATE_IDLE;

    g_stAtAppPdpEntity.enIpv6State = AT_PDP_STATE_IDLE;

    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_WEBUI;

    /* ��ѯAT^DHCP? */
    EXPECT_EQ(AT_ERROR, AT_QryDhcpv6Para(AT_CLIENT_TAB_PCUI_INDEX));

    /* �ϱ���� */

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_QryDhcpV6Para_AppUser, Test_At_QryDhcpV6Para_AppUser_002)
{
    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_WEBUI;

    PS_MEM_SET(&g_stAtAppPdpEntity, 0 ,sizeof(g_stAtAppPdpEntity));
    g_stAtAppPdpEntity.enIpv6State = AT_PDP_STATE_ACTED;

    gastAtClientTab[AT_CLIENT_TAB_PCUI_INDEX].UserType = AT_USBCOM_USER;

    MOCKER(AT_GetDisplayRate)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    g_stParseContext[AT_CLIENT_TAB_PCUI_INDEX].pstCmdElement = &gstDhcpV6CmdInfo;

    AT_QryDhcpv6Para(AT_CLIENT_TAB_PCUI_INDEX);

    /* �ϱ���� */
    EXPECT_STREQ("^DHCPV6: ::,::,::,::,::,::,81920000,81920000", (char *)pgucAtSndCodeAddr);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
TEST_F(Test_At_QryDhcpV6Para_AppUser, Test_At_QryDhcpV6Para_AppUser_003)
{
    VOS_UINT32                          ulSpeed = 14400000;
    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_WEBUI;

    PS_MEM_SET(&g_stAtAppPdpEntity, 0 ,sizeof(g_stAtAppPdpEntity));
    g_stAtAppPdpEntity.enIpv6State = AT_PDP_STATE_ACTED;

    gastAtClientTab[AT_CLIENT_TAB_PCUI_INDEX].UserType = AT_USBCOM_USER;

    MOCKER(AT_GetDisplayRate)
        .expects(exactly(1))
        .with(any(), outBoundP(&ulSpeed))
        .will(returnValue((VOS_UINT32)VOS_OK));

    g_stParseContext[AT_CLIENT_TAB_PCUI_INDEX].pstCmdElement = &gstDhcpV6CmdInfo;

    AT_QryDhcpv6Para(AT_CLIENT_TAB_PCUI_INDEX);

    /* �ϱ���� */
    EXPECT_STREQ("^DHCPV6: ::,::,::,::,::,::,14400000,14400000", (char *)pgucAtSndCodeAddr);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
class Test_At_QryDhcpV6Para_NdisUser: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmBCreate)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(NV_ReadEx)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        MOCKER(NV_GetLength)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        At_PidInit(VOS_IP_INITIAL);
       // ucIndex = AT_CLIENT_TAB_APP_INDEX;
        ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
        g_stParseContext[ucIndex].pstCmdElement = &gstDhcpV6CmdInfo;

    }
    void TearDown()
    {

    }
protected:
    VOS_UINT8                   ucIndex;
};


TEST_F(Test_At_QryDhcpV6Para_NdisUser, Test_At_QryDhcpV6Para_NdisUser_001)
{
    //��������

    memset(&g_stAtNdisDhcpPara,0,sizeof(g_stAtNdisDhcpPara));

    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_MP;
    g_stAtNdisDhcpPara.enIpv6State = AT_PDP_STATE_DEACTING;
    //g_stAtNdisDhcpPara.stIpv6Dhcp.ulIpvAddr = 0xC0A83D41;
    //g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4GateWay = 0xC0A83D42;
    //g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4NetMask = 0xFFFFFF00;

    gastAtClientTab[AT_CLIENT_TAB_PCUI_INDEX].UserType = AT_USBCOM_USER;

    /* ��ѯAT^DHCPV6? */
    EXPECT_EQ(AT_ERROR, AT_QryDhcpv6Para(AT_CLIENT_TAB_PCUI_INDEX));

    /* �ϱ���� */

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_QryDhcpV6Para_NdisUser, Test_At_QryDhcpV6Para_NdisUser_002)
{
    VOS_UINT32                          ulResult;
    VOS_CHAR                           *pcExpactedStr;

    /*���ر�����ʼ��*/
    pcExpactedStr   = "^DHCPV6: ::,::,::,::,::,::,81920000,81920000";

    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_MP;
    g_stAtNdisDhcpPara.enIpv6State = AT_PDP_STATE_ACTED;
    //g_stAtNdisDhcpPara.stIpv6Dhcp.ulIpvAddr = 0xC0A83D41;
    //g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4GateWay = 0xC0A83D42;
    //g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4NetMask = 0xFFFFFF00;

    gastAtClientTab[AT_CLIENT_TAB_PCUI_INDEX].UserType = AT_USBCOM_USER;

    MOCKER(AT_GetDisplayRate)
        .stubs()
        .will(returnValue(VOS_ERR));

    /* ��ѯAT^DHCP? */
    ulResult = AT_QryDhcpv6Para(AT_CLIENT_TAB_PCUI_INDEX);

    EXPECT_EQ(AT_OK, ulResult);

    /* �ϱ���� */
    ASSERT_STREQ(pcExpactedStr, (char *)pgucAtSndCodeAddr);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
TEST_F(Test_At_QryDhcpV6Para_NdisUser, Test_At_QryDhcpV6Para_NdisUser_003)
{
    VOS_UINT32                          ulResult;
    VOS_CHAR                           *pcExpactedStr;
    TAF_AGENT_SYS_MODE_STRU             stSysMode;

    memset(&g_stAtNdisDhcpPara,0,sizeof(g_stAtNdisDhcpPara));

    /*���ر�����ʼ��*/
    pcExpactedStr   = "^DHCPV6: ::,::,::,::,::,::,384000,384000";

    PS_MEM_SET(&stSysMode, 0, sizeof(TAF_AGENT_SYS_MODE_STRU));

	/* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
    stSysMode.enRatType     = TAF_MMA_RAT_WCDMA;
	/* Modified by h00313353 for Iteration 13, 2015-4-10, end */
    stSysMode.enSysSubMode  = TAF_SYS_SUBMODE_WCDMA;

    AT_GetCommCtxAddr()->ucSystemAppConfigAddr = SYSTEM_APP_MP;
    g_stAtNdisDhcpPara.enIpv6State = AT_PDP_STATE_ACTED;
    g_stDialConnectDisplayRate.ucWcdmaConnectRate = 3;
    //g_stAtNdisDhcpPara.stIpv6Dhcp.ulIpvAddr = 0xC0A83D41;
    //g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4GateWay = 0xC0A83D42;
    //g_stAtNdisDhcpPara.stIpv4Dhcp.ulIpv4NetMask = 0xFFFFFF00;

    gastAtClientTab[AT_CLIENT_TAB_PCUI_INDEX].UserType = AT_USBCOM_USER;

    MOCKER(TAF_AGENT_GetSysMode)
        .stubs()
        .with(eq((VOS_UINT16)AT_CLIENT_TAB_PCUI_INDEX), outBoundP((TAF_AGENT_SYS_MODE_STRU *)&stSysMode, sizeof(stSysMode)))
        .will(returnValue((VOS_UINT32)VOS_OK));

    /* ��ѯAT^DHCP? */
    ulResult = AT_QryDhcpv6Para(AT_CLIENT_TAB_PCUI_INDEX);

    EXPECT_EQ(AT_OK, ulResult);

    /* �ϱ���� */
    ASSERT_STREQ(pcExpactedStr, (char *)pgucAtSndCodeAddr);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
class Test_AT_TestDhcpv6Para: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = AT_CLIENT_TAB_APP_INDEX;
        memset(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^DHCPV6";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(1,11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }

    void TearDown()
    {
    }

    VOS_UINT8                   ucIndex;
    AT_PAR_CMD_ELEMENT_STRU     stCmdInfo;
};

TEST_F(Test_AT_TestDhcpv6Para, Test_AT_TestDhcpv6Para_001)
{
    // ��������

    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    gastAtClientTab[ucIndex].UserType   = AT_HSIC4_USER;

    // MOCKER����

    // ���ñ��⺯��
    AT_TestDhcpv6Para(ucIndex);

    // ִ�м��
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen("^DHCPV6: (1-11)"));
    GlobalMockObject::verify();
}


class Test_AT_SetApRaInfoPara: public ::testing::Test
{
public:

    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           cid;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = AT_CLIENT_TAB_APP_INDEX;
        cid                         = 1;
        PS_MEM_SET(gastAtParaList, 0x00, (sizeof(AT_PARSE_PARA_TYPE_STRU) * AT_MAX_PARA_NUMBER));
        AT_AppComEst();
        AT_InitCtx();

        AT_PS_AllocCallEntity(ucIndex, &ucCallId);
        AT_PS_AssignCallIdToCid(ucIndex, cid, ucCallId);

        pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);
        pstCallEntity->stUserInfo.enPortIndex   = AT_CLIENT_TAB_APP_INDEX;
        pstCallEntity->stUserInfo.enUserIndex   = AT_CLIENT_TAB_APP_INDEX;
        pstCallEntity->stUserInfo.ucUsrType     = AT_APP_USER;
        pstCallEntity->stUserInfo.ucUsrCid      = cid;
        pstCallEntity->enIpv6State              = AT_PDP_STATE_ACTED;
        pstCallEntity->ucIpv6Cid                = cid;

        g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
        gucAtParaIndex              = 1;

        PS_MEM_SET(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^APRAINFO";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(1-11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }

    void TearDown()
    {
        AT_PS_FreeCallIdToCid(ucIndex, 1);
        AT_PS_FreeCallEntity(ucIndex, ucCallId);
    }
};

TEST_F(Test_AT_SetApRaInfoPara, Test_AT_SetApRaInfoPara_001)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = AT_SetApRaInfoPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRelt);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetApRaInfoPara, Test_AT_SetApRaInfoPara_002)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    gucAtParaIndex = 2;

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = AT_SetApRaInfoPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRelt);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetApRaInfoPara, Test_AT_SetApRaInfoPara_003)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    gastAtParaList[0].ulParaValue   = cid;
    AT_PS_FreeCallIdToCid(ucIndex, 1);
    AT_PS_FreeCallEntity(ucIndex, ucCallId);

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = AT_SetApRaInfoPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_ERROR, ulRelt);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetApRaInfoPara, Test_AT_SetApRaInfoPara_004)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    gastAtParaList[0].ulParaValue   = cid;
    pstCallEntity->enIpv6State      = AT_PDP_STATE_ACTING;


    // MOCKER����

    // ���ñ��⺯��
    ulRelt = AT_SetApRaInfoPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_ERROR, ulRelt);
    GlobalMockObject::verify();
}



TEST_F(Test_AT_SetApRaInfoPara, Test_AT_SetApRaInfoPara_005)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    gastAtParaList[0].ulParaValue   = cid;
    pstCallEntity->stIpv6RaInfo.bitOpMtuSize            = VOS_FALSE;
    pstCallEntity->stIpv6RaInfo.bitOpPrefixAddr         = VOS_FALSE;
    pstCallEntity->stIpv6RaInfo.bitOpPreferredLifetime  = VOS_FALSE;
    pstCallEntity->stIpv6RaInfo.bitOpValidLifetime      = VOS_FALSE;

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = AT_SetApRaInfoPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRelt);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetApRaInfoPara, Test_AT_SetApRaInfoPara_006)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    gastAtParaList[0].ulParaValue   = cid;
    pstCallEntity->stIpv6RaInfo.bitOpMtuSize            = VOS_TRUE;
    pstCallEntity->stIpv6RaInfo.bitOpPrefixAddr         = VOS_TRUE;
    pstCallEntity->stIpv6RaInfo.bitOpPreferredLifetime  = VOS_TRUE;
    pstCallEntity->stIpv6RaInfo.bitOpValidLifetime      = VOS_TRUE;

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = AT_SetApRaInfoPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRelt);
    GlobalMockObject::verify();
}



class Test_AT_QryApRaInfoPara: public ::testing::Test
{
public:

    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           cid;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    AT_IPV6_RA_INFO_STRU               *pstAppRaInfoAddr;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex = AT_CLIENT_TAB_APP_INDEX;
        cid     = 1;
        PS_MEM_SET(gastAtParaList, 0x00, (sizeof(AT_PARSE_PARA_TYPE_STRU) * AT_MAX_PARA_NUMBER));
        AT_AppComEst();
        AT_InitCtx();
        pstAppRaInfoAddr               = AT_APP_GetRaInfoAddr();
        pstAppPdpEntity                = AT_APP_GetPdpEntInfoAddr();

        pstAppPdpEntity->enIpv6State   = AT_PDP_STATE_ACTED;
        pstAppPdpEntity->enIpv4v6State = AT_PDP_STATE_ACTED;

        PS_MEM_SET(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^APRAINFO";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(1-11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }

    void TearDown()
    {
    }
};

TEST_F(Test_AT_QryApRaInfoPara, Test_AT_QryApRaInfoPara_001)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    pstAppPdpEntity->enIpv6State    = AT_PDP_STATE_IDLE;
    pstAppPdpEntity->enIpv4v6State  = AT_PDP_STATE_IDLE;

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = AT_QryApRaInfoPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_ERROR, ulRelt);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_QryApRaInfoPara, Test_AT_QryApRaInfoPara_002)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    pstAppRaInfoAddr->bitOpMtuSize            = VOS_FALSE;
    pstAppRaInfoAddr->bitOpPrefixAddr         = VOS_FALSE;
    pstAppRaInfoAddr->bitOpPreferredLifetime  = VOS_FALSE;
    pstAppRaInfoAddr->bitOpValidLifetime      = VOS_FALSE;

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = AT_QryApRaInfoPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRelt);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_QryApRaInfoPara, Test_AT_QryApRaInfoPara_003)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    pstAppRaInfoAddr->bitOpMtuSize            = VOS_TRUE;
    pstAppRaInfoAddr->bitOpPrefixAddr         = VOS_TRUE;
    pstAppRaInfoAddr->bitOpPreferredLifetime  = VOS_TRUE;
    pstAppRaInfoAddr->bitOpValidLifetime      = VOS_TRUE;

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = AT_QryApRaInfoPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRelt);
    GlobalMockObject::verify();
}


class Test_AT_TestApRaInfoPara: public ::testing::Test
{
public:

    VOS_UINT8                           ucIndex;
    VOS_UINT8                           cid;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex = AT_CLIENT_TAB_APP_INDEX;
        cid     = 1;
        PS_MEM_SET(gastAtParaList, 0x00, (sizeof(AT_PARSE_PARA_TYPE_STRU) * AT_MAX_PARA_NUMBER));
        AT_AppComEst();
        AT_InitCtx();

        PS_MEM_SET(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^APRAINFO";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(1-11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }

    void TearDown()
    {
    }
};

TEST_F(Test_AT_TestApRaInfoPara, Test_AT_TestApRaInfoPara_001)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = AT_TestApRaInfoPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRelt);
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen("^APRAINFO: (1-11)"));
    GlobalMockObject::verify();
}


class Test_AT_SetApLanAddrPara: public ::testing::Test
{
public:

    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           cid;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = AT_CLIENT_TAB_APP_INDEX;
        cid                         = 1;
        PS_MEM_SET(gastAtParaList, 0x00, (sizeof(AT_PARSE_PARA_TYPE_STRU) * AT_MAX_PARA_NUMBER));
        AT_AppComEst();
        AT_InitCtx();

        AT_PS_AllocCallEntity(ucIndex, &ucCallId);
        AT_PS_AssignCallIdToCid(ucIndex, cid, ucCallId);

        pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);
        pstCallEntity->stUserInfo.enPortIndex   = AT_CLIENT_TAB_APP_INDEX;
        pstCallEntity->stUserInfo.enUserIndex   = AT_CLIENT_TAB_APP_INDEX;
        pstCallEntity->stUserInfo.ucUsrType     = AT_APP_USER;
        pstCallEntity->stUserInfo.ucUsrCid      = cid;
        pstCallEntity->enIpv6State              = AT_PDP_STATE_ACTED;
        pstCallEntity->ucIpv6Cid                = cid;

        g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
        gucAtParaIndex              = 1;

        PS_MEM_SET(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^APLANADDR";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(1-11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }

    void TearDown()
    {
        AT_PS_FreeCallIdToCid(ucIndex, 1);
        AT_PS_FreeCallEntity(ucIndex, ucCallId);
    }
};

TEST_F(Test_AT_SetApLanAddrPara, Test_AT_SetApLanAddrPara_001)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = AT_SetApLanAddrPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRelt);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetApLanAddrPara, Test_AT_SetApLanAddrPara_002)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    gucAtParaIndex = 2;

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = AT_SetApLanAddrPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRelt);
    GlobalMockObject::verify();
}



TEST_F(Test_AT_SetApLanAddrPara, Test_AT_SetApLanAddrPara_003)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    gastAtParaList[0].ulParaValue   = cid;
    AT_PS_FreeCallIdToCid(ucIndex, 1);
    AT_PS_FreeCallEntity(ucIndex, ucCallId);

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = AT_SetApLanAddrPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_ERROR, ulRelt);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetApLanAddrPara, Test_AT_SetApLanAddrPara_004)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    gastAtParaList[0].ulParaValue   = cid;
    pstCallEntity->enIpv6State      = AT_PDP_STATE_ACTING;

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = AT_SetApLanAddrPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_ERROR, ulRelt);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetApLanAddrPara, Test_AT_SetApLanAddrPara_005)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    gastAtParaList[0].ulParaValue            = cid;
    pstCallEntity->stIpv6RaInfo.bitOpLanAddr = VOS_FALSE;

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = AT_SetApLanAddrPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRelt);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetApLanAddrPara, Test_AT_SetApLanAddrPara_006)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    gastAtParaList[0].ulParaValue            = cid;
    pstCallEntity->stIpv6RaInfo.bitOpLanAddr = VOS_TRUE;

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = AT_SetApLanAddrPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRelt);

    GlobalMockObject::verify();
}



class Test_AT_QryApLanAddrPara: public ::testing::Test
{
public:

    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           cid;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    AT_IPV6_RA_INFO_STRU               *pstAppRaInfoAddr;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex = AT_CLIENT_TAB_APP_INDEX;
        cid     = 1;
        PS_MEM_SET(gastAtParaList, 0x00, (sizeof(AT_PARSE_PARA_TYPE_STRU) * AT_MAX_PARA_NUMBER));
        AT_AppComEst();
        AT_InitCtx();
        pstAppRaInfoAddr               = AT_APP_GetRaInfoAddr();
        pstAppPdpEntity                = AT_APP_GetPdpEntInfoAddr();

        pstAppPdpEntity->enIpv6State   = AT_PDP_STATE_ACTED;
        pstAppPdpEntity->enIpv4v6State = AT_PDP_STATE_ACTED;

        PS_MEM_SET(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^APLANADDR";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(1-11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
        gastAtClientTab[ucIndex].UserType       = AT_APP_USER;
    }

    void TearDown()
    {
    }
};

TEST_F(Test_AT_QryApLanAddrPara, Test_AT_QryApLanAddrPara_001)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    pstAppPdpEntity->enIpv6State    = AT_PDP_STATE_IDLE;
    pstAppPdpEntity->enIpv4v6State  = AT_PDP_STATE_IDLE;

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = AT_QryApLanAddrPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_ERROR, ulRelt);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_QryApLanAddrPara, Test_AT_QryApLanAddrPara_002)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    pstAppRaInfoAddr->bitOpLanAddr = VOS_FALSE;

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = AT_QryApLanAddrPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRelt);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_QryApLanAddrPara, Test_AT_QryApLanAddrPara_003)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    pstAppRaInfoAddr->bitOpLanAddr = VOS_TRUE;
    // MOCKER����

    // ���ñ��⺯��
    ulRelt = AT_QryApLanAddrPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRelt);
    GlobalMockObject::verify();
}


class Test_AT_TestApLanAddrPara: public ::testing::Test
{
public:

    VOS_UINT8                           ucIndex;
    VOS_UINT8                           cid;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex = AT_CLIENT_TAB_APP_INDEX;
        cid     = 1;
        PS_MEM_SET(gastAtParaList, 0x00, (sizeof(AT_PARSE_PARA_TYPE_STRU) * AT_MAX_PARA_NUMBER));
        AT_AppComEst();
        AT_InitCtx();

        PS_MEM_SET(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^APLANADDR";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(1-11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }

    void TearDown()
    {
    }
};

TEST_F(Test_AT_TestApLanAddrPara, Test_AT_TestApLanAddrPara_001)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = AT_TestApLanAddrPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRelt);
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen("^APLANADDR: (1-11)"));
    GlobalMockObject::verify();
}

class Test_At_SetApConnStPara: public ::testing::Test
{
public:

    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           cid;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity;
    AT_COMM_PS_CTX_STRU                *pstCommPsCtx;
    VOS_UINT8                           ucIpv6Capability;
    VOS_CHAR                           *pcExpactedStr;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = AT_CLIENT_TAB_APP_INDEX;
        cid                         = 1;
        PS_MEM_SET(gastAtParaList, 0x00, (sizeof(AT_PARSE_PARA_TYPE_STRU) * AT_MAX_PARA_NUMBER));
        AT_AppComEst();
        AT_InitCtx();

        pstCommPsCtx = AT_GetCommPsCtxAddr();
        ucIpv6Capability = pstCommPsCtx->ucIpv6Capability;

        AT_PS_AllocCallEntity(ucIndex, &ucCallId);
        AT_PS_AssignCallIdToCid(ucIndex, cid, ucCallId);

        pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);
        pstCallEntity->stUserInfo.enPortIndex   = AT_CLIENT_TAB_APP_INDEX;
        pstCallEntity->stUserInfo.enUserIndex   = AT_CLIENT_TAB_APP_INDEX;
        pstCallEntity->stUserInfo.ucUsrType     = AT_APP_USER;
        pstCallEntity->stUserInfo.ucUsrCid      = cid;
        pstCallEntity->enIpv6State              = AT_PDP_STATE_ACTED;
        pstCallEntity->ucIpv6Cid                = cid;

        g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
        gucAtParaIndex              = 1;

        PS_MEM_SET(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^APCONNST";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(1-11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }

    void TearDown()
    {
        pstCommPsCtx->ucIpv6Capability = ucIpv6Capability;
        AT_PS_FreeCallIdToCid(ucIndex, 1);
        AT_PS_FreeCallEntity(ucIndex, ucCallId);
    }
};

TEST_F(Test_At_SetApConnStPara, Test_At_SetApConnStPara_001)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = At_SetApConnStPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRelt);
    GlobalMockObject::verify();
}


TEST_F(Test_At_SetApConnStPara, Test_At_SetApConnStPara_002)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    gucAtParaIndex = 2;

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = At_SetApConnStPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRelt);
    GlobalMockObject::verify();
}


TEST_F(Test_At_SetApConnStPara, Test_At_SetApConnStPara_003)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    gastAtParaList[0].ulParaValue   = cid;
    AT_PS_FreeCallIdToCid(ucIndex, 1);
    AT_PS_FreeCallEntity(ucIndex, ucCallId);

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = At_SetApConnStPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_ERROR, ulRelt);
    GlobalMockObject::verify();
}


TEST_F(Test_At_SetApConnStPara, Test_At_SetApConnStPara_004)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��
    pcExpactedStr   = "^APCONNST: 0,\"IPV4\"";

    // ��ʼ��ȫ�ֱ���
    gastAtParaList[0].ulParaValue  = cid;
    pstCommPsCtx->ucIpv6Capability = AT_IPV6_CAPABILITY_IPV4_ONLY;
    pstCallEntity->enIpv4State     = AT_PDP_STATE_ACTING;

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = At_SetApConnStPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRelt);
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen("^APCONNST: 0,\"IPV4\""));
    EXPECT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}


TEST_F(Test_At_SetApConnStPara, Test_At_SetApConnStPara_005)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��
    pcExpactedStr   = "^APCONNST: 2,\"IPV6\"";

    // ��ʼ��ȫ�ֱ���
    gastAtParaList[0].ulParaValue  = cid;
    pstCommPsCtx->ucIpv6Capability = AT_IPV6_CAPABILITY_IPV6_ONLY;
    pstCallEntity->enIpv6State     = AT_PDP_STATE_IDLE;

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = At_SetApConnStPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRelt);
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen("^APCONNST: 2,\"IPV6\""));
    EXPECT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}


TEST_F(Test_At_SetApConnStPara, Test_At_SetApConnStPara_006)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��
    pcExpactedStr   = "^APCONNST: 1,\"IPV4\",1,\"IPV6\"";

    // ��ʼ��ȫ�ֱ���
    gastAtParaList[0].ulParaValue  = cid;
    pstCommPsCtx->ucIpv6Capability = AT_IPV6_CAPABILITY_IPV4V6_OVER_TWO_PDP;
    pstCallEntity->enIpv4State     = AT_PDP_STATE_ACTED;
    pstCallEntity->enIpv6State     = AT_PDP_STATE_ACTED;

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = At_SetApConnStPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRelt);
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen("^APCONNST: 1,\"IPV4\",1,\"IPV6\""));
    EXPECT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}



TEST_F(Test_At_SetApConnStPara, Test_At_SetApConnStPara_007)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��
    pcExpactedStr   = "^APCONNST: 2,\"IPV4\",1,\"IPV6\"";

    // ��ʼ��ȫ�ֱ���
    gastAtParaList[0].ulParaValue  = cid;
    pstCommPsCtx->ucIpv6Capability = AT_IPV6_CAPABILITY_IPV4V6_OVER_ONE_PDP;
    pstCallEntity->enIpv4State     = AT_PDP_STATE_BUTT;
    pstCallEntity->enIpv6State     = AT_PDP_STATE_DEACTING;

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = At_SetApConnStPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRelt);
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen("^APCONNST: 2,\"IPV4\",1,\"IPV6\""));
    EXPECT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}



TEST_F(Test_At_SetApConnStPara, Test_At_SetApConnStPara_008)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    gastAtParaList[0].ulParaValue  = cid;
    pstCommPsCtx->ucIpv6Capability = 0;
    pstCallEntity->enIpv4State     = AT_PDP_STATE_ACTING;

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = At_SetApConnStPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRelt);
    EXPECT_EQ(gstAtSendData.usBufLen, 0);
    GlobalMockObject::verify();
}

class Test_At_QryApConnStPara: public ::testing::Test
{
public:

    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           cid;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex = AT_CLIENT_TAB_APP_INDEX;
        cid     = 1;
        PS_MEM_SET(gastAtParaList, 0x00, (sizeof(AT_PARSE_PARA_TYPE_STRU) * AT_MAX_PARA_NUMBER));
        AT_AppComEst();
        AT_InitCtx();
        pstAppPdpEntity                = AT_APP_GetPdpEntInfoAddr();

        PS_MEM_SET(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^APCONNST";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(1-11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }

    void TearDown()
    {
    }
};


TEST_F(Test_At_QryApConnStPara, Test_At_QryApConnStPara_001)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    pstAppPdpEntity->enIpv4State     = AT_PDP_STATE_ACTING;

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = At_QryApConnStPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRelt);
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen("^APCONNST: 0"));
    GlobalMockObject::verify();
}


TEST_F(Test_At_QryApConnStPara, Test_At_QryApConnStPara_002)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    pstAppPdpEntity->enIpv4State = AT_PDP_STATE_IDLE;

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = At_QryApConnStPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRelt);
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen("^APCONNST: 2"));
    GlobalMockObject::verify();
}



TEST_F(Test_At_QryApConnStPara, Test_At_QryApConnStPara_003)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    pstAppPdpEntity->enIpv4State     = AT_PDP_STATE_ACTED;

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = At_QryApConnStPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRelt);
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen("^APCONNST: 1"));
    GlobalMockObject::verify();
}



class Test_AT_TestApConnStPara: public ::testing::Test
{
public:

    VOS_UINT8                           ucIndex;
    VOS_UINT8                           cid;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex = AT_CLIENT_TAB_APP_INDEX;
        cid     = 1;
        PS_MEM_SET(gastAtParaList, 0x00, (sizeof(AT_PARSE_PARA_TYPE_STRU) * AT_MAX_PARA_NUMBER));
        AT_AppComEst();
        AT_InitCtx();

        PS_MEM_SET(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^APCONNST";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(1-11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }

    void TearDown()
    {
    }
};

TEST_F(Test_AT_TestApConnStPara, Test_AT_TestApConnStPara_001)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = AT_TestApConnStPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRelt);
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen("^APCONNST: (1-11)"));
    GlobalMockObject::verify();
}
#endif

class Test_AT_SetChdataPara_App: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;

    void SetUp()
    {
        UT_STUB_INIT();
        AT_PS_DATA_CHANL_CFG_STRU  stTmpCfg;
        ucIndex                = AT_CLIENT_TAB_APP_INDEX;

        pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

        stTmpCfg.ulUsed        = VOS_FALSE;
        stTmpCfg.ulRmNetId     = UDI_INVAL_DEV_ID;
        stTmpCfg.ulRmNetActFlg = VOS_FALSE;

        pstModemPsCtx->astChannelCfg[1] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[2] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[3] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[4] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[5] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[6] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[7] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[8] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[9] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[10] = stTmpCfg;
        pstModemPsCtx->astChannelCfg[11] = stTmpCfg;
    }
    void TearDown()
    {
        AT_CleanAtChdataCfg(ucIndex, 1);
    }
};


TEST_F(Test_AT_SetChdataPara_App,Test_AT_SetChdataPara_App_001)
{
    /*��������*/
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/
    ulRet                               = TAF_FAILURE;

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex                      = 2;
    gastAtParaList[0].usParaLen         = 1;
    gastAtParaList[0].ulParaValue       = 2;
    gastAtParaList[1].usParaLen         = 0;
    gastAtParaList[1].ulParaValue       = 0;
    pstModemPsCtx->astChannelCfg[2].ulUsed          = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[2].ulRmNetId       = RNIC_RM_NET_ID_0;

    /*������׮*/

    /*���ñ��⺯�� */
    ulRet = AT_SetChdataPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(VOS_FALSE,     pstModemPsCtx->astChannelCfg[2].ulUsed);
    EXPECT_EQ(UDI_INVAL_DEV_ID, pstModemPsCtx->astChannelCfg[2].ulRmNetId);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetChdataPara_App,Test_AT_SetChdataPara_App_002)
{
    /*��������*/
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/
    ulRet                               = TAF_FAILURE;

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex                      = 2;
    gastAtParaList[0].usParaLen         = 1;
    gastAtParaList[0].ulParaValue       = 1;
    gastAtParaList[1].usParaLen         = 1;
    gastAtParaList[1].ulParaValue       = 2;
    pstModemPsCtx->astChannelCfg[2].ulUsed          = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[2].ulRmNetId       = RNIC_RM_NET_ID_1;

    /*������׮*/

    /*���ñ��⺯�� */
    ulRet = AT_SetChdataPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_ERROR, ulRet);
    EXPECT_EQ(VOS_FALSE,     pstModemPsCtx->astChannelCfg[1].ulUsed);
    EXPECT_EQ(UDI_INVAL_DEV_ID, pstModemPsCtx->astChannelCfg[1].ulRmNetId);

    GlobalMockObject::verify();
}



TEST_F(Test_AT_SetChdataPara_App,Test_AT_SetChdataPara_App_003)
{
    /*��������*/
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/
    ulRet                               = TAF_FAILURE;

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex                      = 2;
    gastAtParaList[0].usParaLen         = 1;
    gastAtParaList[0].ulParaValue       = 1;
    gastAtParaList[1].usParaLen         = 1;
    gastAtParaList[1].ulParaValue       = 1;

    /*������׮*/

    /*���ñ��⺯�� */
    ulRet = AT_SetChdataPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(VOS_TRUE, pstModemPsCtx->astChannelCfg[1].ulUsed);
    EXPECT_EQ(RNIC_RM_NET_ID_0, pstModemPsCtx->astChannelCfg[1].ulRmNetId);

    GlobalMockObject::verify();
}



TEST_F(Test_AT_SetChdataPara_App,Test_AT_SetChdataPara_App_004)
{
    /*��������*/
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/
    ulRet                               = TAF_FAILURE;

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex                      = 2;
    gastAtParaList[0].usParaLen         = 1;
    gastAtParaList[0].ulParaValue       = 1;
    gastAtParaList[1].usParaLen         = 1;
    gastAtParaList[1].ulParaValue       = 5;

    /*������׮*/

    /*���ñ��⺯�� */
    ulRet = AT_SetChdataPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_ERROR, ulRet);
    EXPECT_EQ(VOS_FALSE, pstModemPsCtx->astChannelCfg[1].ulUsed);
    EXPECT_EQ(UDI_INVAL_DEV_ID, pstModemPsCtx->astChannelCfg[1].ulRmNetId);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetChdataPara_App,Test_AT_SetChdataPara_App_005)
{
    /*��������*/
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/
    ulRet                               = TAF_FAILURE;

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex                      = 2;
    gastAtParaList[0].usParaLen         = 1;
    gastAtParaList[0].ulParaValue       = 2;
    gastAtParaList[1].usParaLen         = 0;
    gastAtParaList[1].ulParaValue       = 0;
    pstModemPsCtx->astChannelCfg[2].ulUsed          = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[2].ulRmNetId       = RNIC_RM_NET_ID_1;
    pstModemPsCtx->astChannelCfg[2].ulRmNetActFlg   = VOS_TRUE;

    /*������׮*/

    /*���ñ��⺯�� */
    ulRet = AT_SetChdataPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_ERROR, ulRet);
    EXPECT_EQ(VOS_TRUE,         pstModemPsCtx->astChannelCfg[2].ulUsed);
    EXPECT_EQ(RNIC_RM_NET_ID_1, pstModemPsCtx->astChannelCfg[2].ulRmNetId);

    GlobalMockObject::verify();
}


class Test_AT_QryChdataPara_App: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    AT_MODEM_PS_CTX_STRU               *pstModemPsCtx;
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmBCreate)
            .defaults()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(NV_ReadEx)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        MOCKER(NV_GetLength)
            .defaults()
            .will(returnValue((VOS_UINT32)NV_OK));

        At_PidInit(VOS_IP_INITIAL);
        ucIndex                     = AT_CLIENT_TAB_APP_INDEX;

        pstModemPsCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

        stCmdInfo.ulCmdIndex        = AT_CMD_CHDATA;
        stCmdInfo.pfnSetProc        = AT_SetChdataPara;
        stCmdInfo.ulSetTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnQryProc        = AT_QryChdataPara;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.pfnTestProc       = VOS_NULL_PTR;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^CHDATA";
        stCmdInfo.pszParam          = (VOS_UINT8*)"(1-11),(1-5)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
        gastAtClientTab[ucIndex].UserType       = AT_APP_USER;

    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_QryChdataPara_App,Test_AT_QryChdataPara_App_001)
{
    /*��������*/
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcExpactedStr;

    /*���ر�����ʼ��*/
    ulRet           = TAF_FAILURE;
    pcExpactedStr   = "^CHDATA: 1,2\r\n^CHDATA: 2,3\r\n^CHDATA: 11,1";

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_READ_CMD;
    pstModemPsCtx->astChannelCfg[1].ulUsed          = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[1].ulRmNetId       = RNIC_RM_NET_ID_1;
    pstModemPsCtx->astChannelCfg[2].ulUsed          = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[2].ulRmNetId       = RNIC_RM_NET_ID_2;
    pstModemPsCtx->astChannelCfg[3].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[4].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[5].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[6].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[7].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[8].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[9].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[10].ulUsed         = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[11].ulUsed         = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[11].ulRmNetId      = RNIC_RM_NET_ID_0;

    /*������׮*/

    /*���ñ��⺯�� */
    ulRet = AT_QryChdataPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(VOS_StrLen(pcExpactedStr), gstAtSendData.usBufLen);
    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);
    GlobalMockObject::verify();
}



TEST_F(Test_AT_QryChdataPara_App,Test_AT_QryChdataPara_App_002)
{
    /*��������*/
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/
    ulRet           = TAF_FAILURE;

    /*ȫ�ֱ�����ʼ��*/
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_READ_CMD;
    pstModemPsCtx->astChannelCfg[1].ulUsed          = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[1].ulRmNetId       = RNIC_RMNET_ID_BUTT;
    pstModemPsCtx->astChannelCfg[2].ulUsed          = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[2].ulRmNetId       = RNIC_RM_NET_ID_2;
    pstModemPsCtx->astChannelCfg[3].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[4].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[5].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[6].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[7].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[8].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[9].ulUsed          = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[10].ulUsed         = VOS_FALSE;
    pstModemPsCtx->astChannelCfg[11].ulUsed         = VOS_TRUE;
    pstModemPsCtx->astChannelCfg[11].ulRmNetId      = RNIC_RM_NET_ID_0;

    /*������׮*/

    /*���ñ��⺯�� */
    ulRet = AT_QryChdataPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}



class Test_At_SetApThroughputPara: public ::testing::Test
{
public:

    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           cid;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = AT_CLIENT_TAB_APP_INDEX;
        cid                         = 1;
        PS_MEM_SET(gastAtParaList, 0x00, (sizeof(AT_PARSE_PARA_TYPE_STRU) * AT_MAX_PARA_NUMBER));
        AT_AppComEst();
        AT_InitCtx();

        pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

        pstPsModemCtx->astChannelCfg[cid].ulRmNetId = RNIC_RM_NET_ID_2;

        g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
        gucAtParaIndex              = 1;

        PS_MEM_SET(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^APTHROUGHPUT";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(1-11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
        gastAtParaList[0].ulParaValue           = 1;
    }

    void TearDown()
    {
        AT_PS_FreeCallIdToCid(ucIndex, 1);
        AT_PS_FreeCallEntity(ucIndex, ucCallId);
    }
};

TEST_F(Test_At_SetApThroughputPara, Test_At_SetApThroughputPara_001)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = At_SetApThroughputPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRelt);
    GlobalMockObject::verify();
}


TEST_F(Test_At_SetApThroughputPara, Test_At_SetApThroughputPara_002)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    gucAtParaIndex = 2;

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = At_SetApThroughputPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRelt);
    GlobalMockObject::verify();
}


TEST_F(Test_At_SetApThroughputPara, Test_At_SetApThroughputPara_003)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    pstPsModemCtx->astChannelCfg[cid].ulRmNetId = RNIC_RMNET_ID_BUTT;

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = At_SetApThroughputPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_ERROR, ulRelt);
    GlobalMockObject::verify();
}


TEST_F(Test_At_SetApThroughputPara, Test_At_SetApThroughputPara_004)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue((MsgBlock *)VOS_NULL_PTR));

    // ���ñ��⺯��
    ulRelt = At_SetApThroughputPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_ERROR, ulRelt);
    GlobalMockObject::verify();
}


TEST_F(Test_At_SetApThroughputPara, Test_At_SetApThroughputPara_005)
{
    // ��������
    VOS_UINT32                          ulRelt;
    AT_RNIC_DSFLOW_IND_STRU             stMsg;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue((MsgBlock *)&stMsg));

    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    // ���ñ��⺯��
    ulRelt = At_SetApThroughputPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_ERROR, ulRelt);
    GlobalMockObject::verify();
}


TEST_F(Test_At_SetApThroughputPara, Test_At_SetApThroughputPara_006)
{
    // ��������
    VOS_UINT32                          ulRelt;
    AT_RNIC_DSFLOW_IND_STRU             stMsg;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue((MsgBlock *)&stMsg));

    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // ���ñ��⺯��
    ulRelt = At_SetApThroughputPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRelt);
    GlobalMockObject::verify();
}



class Test_At_QryApThroughputPara: public ::testing::Test
{
public:

    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           cid;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = AT_CLIENT_TAB_APP_INDEX;
        cid                         = 1;
        PS_MEM_SET(gastAtParaList, 0x00, (sizeof(AT_PARSE_PARA_TYPE_STRU) * AT_MAX_PARA_NUMBER));
        AT_AppComEst();
        AT_InitCtx();

        pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

        pstPsModemCtx->astChannelCfg[cid].ulRmNetId = RNIC_RM_NET_ID_2;

        g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
        gucAtParaIndex              = 1;

        PS_MEM_SET(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^APTHROUGHPUT";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(1-11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
        gastAtParaList[0].ulParaValue           = 1;
    }

    void TearDown()
    {
        AT_PS_FreeCallIdToCid(ucIndex, 1);
        AT_PS_FreeCallEntity(ucIndex, ucCallId);
    }
};


TEST_F(Test_At_QryApThroughputPara, Test_At_QryApThroughputPara_001)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue((MsgBlock *)VOS_NULL_PTR));

    // ���ñ��⺯��
    ulRelt = At_QryApThroughputPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_ERROR, ulRelt);
    GlobalMockObject::verify();
}


TEST_F(Test_At_QryApThroughputPara, Test_At_QryApThroughputPara_002)
{
    // ��������
    VOS_UINT32                          ulRelt;
    AT_RNIC_DSFLOW_IND_STRU             stMsg;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue((MsgBlock *)&stMsg));

    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    // ���ñ��⺯��
    ulRelt = At_QryApThroughputPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_ERROR, ulRelt);
    GlobalMockObject::verify();
}


TEST_F(Test_At_QryApThroughputPara, Test_At_QryApThroughputPara_003)
{
    // ��������
    VOS_UINT32                          ulRelt;
    AT_RNIC_DSFLOW_IND_STRU             stMsg;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(V_AllocMsg)
        .expects(exactly(1))
        .will(returnValue((MsgBlock *)&stMsg));

    MOCKER(Ps_SendMsg)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // ���ñ��⺯��
    ulRelt = At_QryApThroughputPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_WAIT_ASYNC_RETURN, ulRelt);
    GlobalMockObject::verify();
}



class Test_AT_TestApThroughputPara: public ::testing::Test
{
public:

    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           cid;
    AT_PAR_CMD_ELEMENT_STRU             stCmdInfo;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = AT_CLIENT_TAB_APP_INDEX;
        cid                         = 1;
        PS_MEM_SET(gastAtParaList, 0x00, (sizeof(AT_PARSE_PARA_TYPE_STRU) * AT_MAX_PARA_NUMBER));
        AT_AppComEst();
        AT_InitCtx();

        pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

        pstPsModemCtx->astChannelCfg[cid].ulRmNetId = RNIC_RM_NET_ID_2;

        g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
        gucAtParaIndex              = 1;

        PS_MEM_SET(&stCmdInfo, 0x00, sizeof(AT_PAR_CMD_ELEMENT_STRU));
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^APTHROUGHPUT";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(1-11)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
        gastAtParaList[0].ulParaValue           = 1;
    }

    void TearDown()
    {
        AT_PS_FreeCallIdToCid(ucIndex, 1);
        AT_PS_FreeCallEntity(ucIndex, ucCallId);
    }
};

TEST_F(Test_AT_TestApThroughputPara, Test_AT_TestApThroughputPara_001)
{
    // ��������
    VOS_UINT32                          ulRelt;
    // ������ʼ��

    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = AT_TestApThroughputPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRelt);
    EXPECT_EQ(gstAtSendData.usBufLen, VOS_StrLen("^APTHROUGHPUT: (1-11)"));
    GlobalMockObject::verify();
}
