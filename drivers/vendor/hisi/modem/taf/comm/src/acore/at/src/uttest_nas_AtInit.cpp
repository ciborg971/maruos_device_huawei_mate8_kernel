#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_AtInit.h"

//�����������ã����������ùؼ���ʱ��Ҫ��ǰ׺ testing::
using namespace testing;

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#define    THIS_FILE_ID        PS_FILE_ID_AT_INIT_C
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




class Test_AT_ReadClientConfigNV: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        
        AT_InitCtx();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_ReadClientConfigNV, Test_AT_ReadClientConfigNV_001)
{
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue(VOS_ERR));

    AT_ReadClientConfigNV();

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ReadClientConfigNV, Test_AT_ReadClientConfigNV_002)
{
    VOS_UINT8                           aucAtClientConfig[AT_CLIENT_ID_BUTT];

    PS_MEM_SET(aucAtClientConfig, 0 ,sizeof(aucAtClientConfig));

    aucAtClientConfig[TAF_NV_CLIENT_CFG_PCUI] = 0x04;
    aucAtClientConfig[TAF_NV_CLIENT_CFG_CTRL] = 0x04;
    aucAtClientConfig[TAF_NV_CLIENT_CFG_APP1] = 0x04;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_AT_CLIENT_CONFIG), outBoundP((void *)aucAtClientConfig, AT_CLIENT_ID_BUTT), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    AT_ReadClientConfigNV();

    EXPECT_EQ(MODEM_ID_0, g_astAtClientCtx[AT_CLIENT_TAB_PCUI_INDEX].stClientConfiguration.enModemId);
    EXPECT_EQ(MODEM_ID_0, g_astAtClientCtx[AT_CLIENT_TAB_CTRL_INDEX].stClientConfiguration.enModemId);
    EXPECT_EQ(MODEM_ID_0, g_astAtClientCtx[AT_CLIENT_TAB_APP1_INDEX].stClientConfiguration.enModemId);

    EXPECT_EQ(VOS_TRUE, g_astAtClientCtx[AT_CLIENT_TAB_PCUI_INDEX].stClientConfiguration.ucReportFlg);
    EXPECT_EQ(VOS_TRUE, g_astAtClientCtx[AT_CLIENT_TAB_CTRL_INDEX].stClientConfiguration.ucReportFlg);
    EXPECT_EQ(VOS_TRUE, g_astAtClientCtx[AT_CLIENT_TAB_APP1_INDEX].stClientConfiguration.ucReportFlg);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ReadClientConfigNV, Test_AT_ReadClientConfigNV_003)
{
    VOS_UINT8                           aucAtClientConfig[AT_CLIENT_ID_BUTT];

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    aucAtClientConfig[TAF_NV_CLIENT_CFG_PCUI] = 0x05;
    aucAtClientConfig[TAF_NV_CLIENT_CFG_CTRL] = 0x05;
    aucAtClientConfig[TAF_NV_CLIENT_CFG_APP5] = 0x01;
    aucAtClientConfig[TAF_NV_CLIENT_CFG_APP1] = 0x04;
#endif

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_AT_CLIENT_CONFIG), outBoundP((void *)aucAtClientConfig, AT_CLIENT_ID_BUTT), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    AT_ReadClientConfigNV();

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    EXPECT_EQ(MODEM_ID_1, g_astAtClientCtx[AT_CLIENT_TAB_PCUI_INDEX].stClientConfiguration.enModemId);
    EXPECT_EQ(MODEM_ID_1, g_astAtClientCtx[AT_CLIENT_TAB_CTRL_INDEX].stClientConfiguration.enModemId);
    EXPECT_EQ(MODEM_ID_0, g_astAtClientCtx[AT_CLIENT_TAB_APP1_INDEX].stClientConfiguration.enModemId);
    EXPECT_EQ(MODEM_ID_1, g_astAtClientCtx[AT_CLIENT_TAB_APP5_INDEX].stClientConfiguration.enModemId);
    EXPECT_EQ(VOS_FALSE, g_astAtClientCtx[AT_CLIENT_TAB_APP5_INDEX].stClientConfiguration.ucReportFlg);

#endif
    EXPECT_EQ(VOS_TRUE, g_astAtClientCtx[AT_CLIENT_TAB_PCUI_INDEX].stClientConfiguration.ucReportFlg);
    EXPECT_EQ(VOS_TRUE, g_astAtClientCtx[AT_CLIENT_TAB_CTRL_INDEX].stClientConfiguration.ucReportFlg);
    EXPECT_EQ(VOS_TRUE, g_astAtClientCtx[AT_CLIENT_TAB_APP1_INDEX].stClientConfiguration.ucReportFlg);

    GlobalMockObject::verify();
}


class Test_AT_ReadPlatformNV: public ::testing::Test
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

#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_AT_ReadPlatformNV, Test_AT_ReadPlatformNV_001)
{
    PLATAFORM_RAT_CAPABILITY_STRU       stPlatFormRat;
    AT_MODEM_SPT_RAT_STRU                 *pstAtSptRatList = VOS_NULL_PTR;

    stPlatFormRat.usRatNum = 4;
    stPlatFormRat.aenRatList[0] = PLATFORM_RAT_LTE;
    stPlatFormRat.aenRatList[1] = PLATFORM_RAT_WCDMA;
    stPlatFormRat.aenRatList[2] = PLATFORM_RAT_TDS;
    stPlatFormRat.aenRatList[3] = PLATFORM_RAT_GSM;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq((MODEM_ID_ENUM_UINT16)MODEM_ID_0), eq((VOS_UINT16)en_NV_Item_Platform_RAT_CAP), outBoundP((void *)&stPlatFormRat, (VOS_UINT32)sizeof(stPlatFormRat)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    AT_ReadPlatformNV();

    pstAtSptRatList = AT_GetSptRatFromModemId(MODEM_ID_0);

#if(FEATURE_ON == FEATURE_LTE)
    EXPECT_EQ(VOS_TRUE, pstAtSptRatList->ucPlatformSptLte);
#endif

    EXPECT_EQ(VOS_TRUE, pstAtSptRatList->ucPlatformSptWcdma);
    EXPECT_EQ(VOS_TRUE, pstAtSptRatList->ucPlatformSptGsm);

    GlobalMockObject::verify();
}
#endif





class Test_AT_SendDomainNvimToProto: public ::testing::Test
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


TEST_F(Test_AT_SendDomainNvimToProto, Test_AT_SendDomainNvimToProto_001)
{
    // ��������
    VOS_UINT32                          ulNvimSendDomain;
    AT_CGSMS_SEND_DOMAIN_ENUM_U8        ulRslt;

    // ������ʼ��
    ulNvimSendDomain = AT_NV_SMS_DOMAIN_PS_PREFERRED;

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_SendDomainNvimToProto(ulNvimSendDomain);

    // ִ�м��
    EXPECT_EQ(MN_MSG_SEND_DOMAIN_PS_PREFERRED, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SendDomainNvimToProto, Test_AT_SendDomainNvimToProto_002)
{
    // ��������
    VOS_UINT32                          ulNvimSendDomain;
    AT_CGSMS_SEND_DOMAIN_ENUM_U8        ulRslt;

    // ������ʼ��
    ulNvimSendDomain = AT_NV_SMS_DOMAIN_PS_ONLY;

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_SendDomainNvimToProto(ulNvimSendDomain);

    // ִ�м��
    EXPECT_EQ(MN_MSG_SEND_DOMAIN_PS, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SendDomainNvimToProto, Test_AT_SendDomainNvimToProto_003)
{
    // ��������
    VOS_UINT32                          ulNvimSendDomain;
    AT_CGSMS_SEND_DOMAIN_ENUM_U8        ulRslt;

    // ������ʼ��
    ulNvimSendDomain = AT_NV_SMS_DOMAIN_CS_ONLY;

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_SendDomainNvimToProto(ulNvimSendDomain);

    // ִ�м��
    EXPECT_EQ(MN_MSG_SEND_DOMAIN_CS, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SendDomainNvimToProto, Test_AT_SendDomainNvimToProto_004)
{
    // ��������
    VOS_UINT32                          ulNvimSendDomain;
    AT_CGSMS_SEND_DOMAIN_ENUM_U8        ulRslt;

    // ������ʼ��
    ulNvimSendDomain = AT_NV_SMS_DOMAIN_CS_PREFERRED;

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_SendDomainNvimToProto(ulNvimSendDomain);

    // ִ�м��
    EXPECT_EQ(MN_MSG_SEND_DOMAIN_CS_PREFERRED, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_AT_ReadSmsSendDomainNV: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(NV_GetLength)
            .stubs()
            .will(returnValue((VOS_UINT32)NV_OK));

    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_ReadSmsSendDomainNV, Test_AT_ReadSmsSendDomainNV_001)
{
    // ��������
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_NVIM_SEND_DOMAIN_STRU            stSendDomain;

    // ������ʼ��
    enModemId = MODEM_ID_0;
    stSendDomain.ucActFlg = VOS_TRUE;
    stSendDomain.ucSendDomain = AT_NV_SMS_DOMAIN_CS_PREFERRED;

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), any(), outBoundP((void *)&stSendDomain, (VOS_UINT32)sizeof(stSendDomain)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    // ���ñ��⺯��
    AT_ReadSmsSendDomainNV();

    // ִ�м��
    EXPECT_EQ(VOS_TRUE, g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCgsmsSendDomain.ucActFlg);
    EXPECT_EQ(MN_MSG_SEND_DOMAIN_CS_PREFERRED, g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCgsmsSendDomain.enSendDomain);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_AT_ReadSmsSendDomainNV, Test_AT_ReadSmsSendDomainNV_002)
{
    // ��������
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_NVIM_SEND_DOMAIN_STRU            stSendDomain;

    // ������ʼ��
    enModemId = MODEM_ID_1;
    stSendDomain.ucActFlg = VOS_TRUE;
    stSendDomain.ucSendDomain = AT_NV_SMS_DOMAIN_PS_ONLY;

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), any(), outBoundP((void *)&stSendDomain, (VOS_UINT32)sizeof(stSendDomain)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    // ���ñ��⺯��
    AT_ReadSmsSendDomainNV();

    // ִ�м��
    EXPECT_EQ(VOS_TRUE, g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCgsmsSendDomain.ucActFlg);
    EXPECT_EQ(MN_MSG_SEND_DOMAIN_PS, g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCgsmsSendDomain.enSendDomain);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
#endif


class Test_AT_ReadSmsNV: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(NV_GetLength)
            .stubs()
            .will(returnValue((VOS_UINT32)NV_OK));

        AT_InitCtx();
    }
    void TearDown()
    {

    }
};



TEST_F(Test_AT_ReadSmsNV, Test_AT_ReadSmsNV_001)
{
    AT_NVIM_SEND_DOMAIN_STRU            stSendDomain;
    MN_MSG_ME_STORAGE_PARM_STRU         stMeStorageParm;
    VOS_UINT8                           aucSmsSrvParam[MN_MSG_SRV_PARAM_LEN];
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;
    MN_MSG_NVIM_CLASS0_TAILOR_STRU      stClass0Tailor;
    MODEM_ID_ENUM_UINT16                enModemIdMoker;

    enModemIdMoker = MODEM_ID_0;
    stSendDomain.ucActFlg = VOS_TRUE;
    stSendDomain.ucSendDomain = AT_NV_SMS_DOMAIN_CS_ONLY;

    MOCKER(AT_ReadSmsClosePathNV)
        .expects(exactly(1));

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(enModemIdMoker), eq((VOS_UINT16)en_NV_Item_SMS_SEND_DOMAIN), outBoundP((void *)&stSendDomain, (VOS_UINT32)sizeof(stSendDomain)))
        .will(returnValue((VOS_UINT32)NV_OK));

    enModemIdMoker = MODEM_ID_1;
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(enModemIdMoker), eq((VOS_UINT16)en_NV_Item_SMS_SEND_DOMAIN), outBoundP((void *)&stSendDomain, (VOS_UINT32)sizeof(stSendDomain)))
        .will(returnValue((VOS_UINT32)NV_OK));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_SMS_SEND_DOMAIN), outBoundP((void *)&stSendDomain, (VOS_UINT32)sizeof(stSendDomain)))
        .will(returnValue((VOS_UINT32)NV_OK));
#endif

    stMeStorageParm.enMeStorageStatus = MN_MSG_ME_STORAGE_ENABLE;

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(2))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Sms_Me_Storage_Info), outBoundP((void *)&stMeStorageParm, (VOS_UINT32)sizeof(stSendDomain)))
        .will(returnValue((VOS_UINT32)NV_OK));
#else
   MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Sms_Me_Storage_Info), outBoundP((void *)&stMeStorageParm, (VOS_UINT32)sizeof(stSendDomain)))
        .will(returnValue((VOS_UINT32)NV_OK));
#endif

    aucSmsSrvParam[MN_MSG_SRV_SM_MEM_ENABLE_OFFSET] = VOS_TRUE;
    aucSmsSrvParam[MN_MSG_SRV_RCV_SM_MEM_STORE_OFFSET] = MN_MSG_MEM_STORE_NV;

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(2))
        .with(any(), eq((VOS_UINT16)en_NV_Item_SMS_SERVICE_Para), outBoundP((void *)&aucSmsSrvParam, (VOS_UINT32)sizeof(aucSmsSrvParam)))
        .will(returnValue((VOS_UINT32)NV_OK));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_SMS_SERVICE_Para), outBoundP((void *)&aucSmsSrvParam, (VOS_UINT32)sizeof(aucSmsSrvParam)))
        .will(returnValue((VOS_UINT32)NV_OK));
#endif

    stClass0Tailor.ucActFlg             = MN_MSG_NVIM_ITEM_ACTIVE;
    stClass0Tailor.enClass0Tailor       = MN_MSG_CLASS0_TIM;

    enModemIdMoker = MODEM_ID_0;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(enModemIdMoker), eq((VOS_UINT16)en_NV_Item_SMS_CLASS0_TAILOR), outBoundP((void *)&stClass0Tailor, (VOS_UINT32)sizeof(stClass0Tailor)))
        .will(returnValue((VOS_UINT32)NV_OK));

    AT_ReadSmsNV();

    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstSmsCtx = AT_GetModemSmsCtxAddrFromModemId(enModemId);

        EXPECT_EQ(VOS_TRUE, pstSmsCtx->stCgsmsSendDomain.ucActFlg);
        EXPECT_EQ(MN_MSG_SEND_DOMAIN_CS, pstSmsCtx->stCgsmsSendDomain.enSendDomain);
        EXPECT_EQ(VOS_TRUE, pstSmsCtx->enMsgMeStorageStatus);
        EXPECT_EQ(MN_MSG_MEM_STORE_NV, pstSmsCtx->stCpmsInfo.stRcvPath.enStaRptMemStore);
        EXPECT_EQ(MN_MSG_MEM_STORE_NV, pstSmsCtx->stCpmsInfo.stRcvPath.enSmMemStore);
    }

    EXPECT_EQ(MN_MSG_CLASS0_TIM, g_enClass0Tailor);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ReadSmsNV, Test_AT_ReadSmsNV_002)
{
    AT_NVIM_SEND_DOMAIN_STRU            stSendDomain;
    MN_MSG_ME_STORAGE_PARM_STRU         stMeStorageParm;
    VOS_UINT8                           aucSmsSrvParam[MN_MSG_SRV_PARAM_LEN];
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;
    MN_MSG_NVIM_CLASS0_TAILOR_STRU      stClass0Tailor;
    MODEM_ID_ENUM_UINT16                enModemIdMocker;

    enModemIdMocker = MODEM_ID_0;
    stSendDomain.ucActFlg = VOS_TRUE;
    stSendDomain.ucSendDomain = AT_NV_SMS_DOMAIN_PS_ONLY;

    MOCKER(AT_ReadSmsClosePathNV)
        .expects(exactly(1));

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(enModemIdMocker), eq((VOS_UINT16)en_NV_Item_SMS_SEND_DOMAIN), outBoundP((void *)&stSendDomain, (VOS_UINT32)sizeof(stSendDomain)))
        .will(returnValue((VOS_UINT32)NV_OK));

    enModemIdMocker = MODEM_ID_1;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(enModemIdMocker), eq((VOS_UINT16)en_NV_Item_SMS_SEND_DOMAIN), outBoundP((void *)&stSendDomain, (VOS_UINT32)sizeof(stSendDomain)))
        .will(returnValue((VOS_UINT32)NV_OK));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_SMS_SEND_DOMAIN), outBoundP((void *)&stSendDomain, (VOS_UINT32)sizeof(stSendDomain)))
        .will(returnValue((VOS_UINT32)NV_OK));
#endif

    stMeStorageParm.enMeStorageStatus = MN_MSG_ME_STORAGE_ENABLE;

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(2))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Sms_Me_Storage_Info), outBoundP((void *)&stMeStorageParm, (VOS_UINT32)sizeof(stMeStorageParm)))
        .will(returnValue((VOS_UINT32)NV_OK));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Sms_Me_Storage_Info), outBoundP((void *)&stMeStorageParm, (VOS_UINT32)sizeof(stMeStorageParm)))
        .will(returnValue((VOS_UINT32)NV_OK));
#endif

    aucSmsSrvParam[MN_MSG_SRV_SM_MEM_ENABLE_OFFSET] = VOS_TRUE;
    aucSmsSrvParam[MN_MSG_SRV_RCV_SM_MEM_STORE_OFFSET] = MN_MSG_MEM_STORE_NV;

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(2))
        .with(any(), eq((VOS_UINT16)en_NV_Item_SMS_SERVICE_Para), outBoundP((void *)&aucSmsSrvParam, (VOS_UINT32)sizeof(aucSmsSrvParam)))
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_SMS_SERVICE_Para), outBoundP((void *)&aucSmsSrvParam, (VOS_UINT32)sizeof(aucSmsSrvParam)))
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));
#endif

    stClass0Tailor.ucActFlg             = MN_MSG_NVIM_ITEM_ACTIVE;
    stClass0Tailor.enClass0Tailor       = MN_MSG_CLASS0_TIM;

    enModemIdMocker = MODEM_ID_0;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(enModemIdMocker), eq((VOS_UINT16)en_NV_Item_SMS_CLASS0_TAILOR), outBoundP((void *)&stClass0Tailor, (VOS_UINT32)sizeof(stClass0Tailor)))
        .will(returnValue((VOS_UINT32)NV_OK));

    AT_ReadSmsNV();

    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstSmsCtx = AT_GetModemSmsCtxAddrFromModemId(enModemId);

        EXPECT_EQ(VOS_TRUE, pstSmsCtx->stCgsmsSendDomain.ucActFlg);
        EXPECT_EQ(MN_MSG_SEND_DOMAIN_PS, pstSmsCtx->stCgsmsSendDomain.enSendDomain);
        EXPECT_EQ(VOS_TRUE, pstSmsCtx->enMsgMeStorageStatus);
        EXPECT_EQ(MN_MSG_MEM_STORE_SIM, pstSmsCtx->stCpmsInfo.stRcvPath.enStaRptMemStore);
        EXPECT_EQ(MN_MSG_MEM_STORE_SIM, pstSmsCtx->stCpmsInfo.stRcvPath.enSmMemStore);
    }

    EXPECT_EQ(MN_MSG_CLASS0_TIM, g_enClass0Tailor);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ReadSmsNV, Test_AT_ReadSmsNV_003)
{
    AT_NVIM_SEND_DOMAIN_STRU            stSendDomain;
    MN_MSG_ME_STORAGE_PARM_STRU         stMeStorageParm;
    VOS_UINT8                           aucSmsSrvParam[MN_MSG_SRV_PARAM_LEN];
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;
    MN_MSG_NVIM_CLASS0_TAILOR_STRU      stClass0Tailor;
    MODEM_ID_ENUM_UINT16                enModemIdMocker;

    enModemIdMocker = MODEM_ID_0;
    stSendDomain.ucActFlg = VOS_TRUE;
    stSendDomain.ucSendDomain = AT_NV_SMS_DOMAIN_PS_PREFERRED;

    MOCKER(AT_ReadSmsClosePathNV)
        .expects(exactly(1));

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(enModemIdMocker), eq((VOS_UINT16)en_NV_Item_SMS_SEND_DOMAIN), outBoundP((void *)&stSendDomain, (VOS_UINT32)sizeof(stSendDomain)))
        .will(returnValue((VOS_UINT32)NV_OK));

    enModemIdMocker = MODEM_ID_1;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(enModemIdMocker), eq((VOS_UINT16)en_NV_Item_SMS_SEND_DOMAIN), outBoundP((void *)&stSendDomain, (VOS_UINT32)sizeof(stSendDomain)))
        .will(returnValue((VOS_UINT32)NV_OK));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_SMS_SEND_DOMAIN), outBoundP((void *)&stSendDomain, (VOS_UINT32)sizeof(stSendDomain)))
        .will(returnValue((VOS_UINT32)NV_OK));
#endif

    stMeStorageParm.enMeStorageStatus = MN_MSG_ME_STORAGE_ENABLE;

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(2))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Sms_Me_Storage_Info), outBoundP((void *)&stMeStorageParm, (VOS_UINT32)sizeof(stMeStorageParm)))
        .will(returnValue((VOS_UINT32)NV_OK));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Sms_Me_Storage_Info), outBoundP((void *)&stMeStorageParm, (VOS_UINT32)sizeof(stMeStorageParm)))
        .will(returnValue((VOS_UINT32)NV_OK));
#endif

    aucSmsSrvParam[MN_MSG_SRV_SM_MEM_ENABLE_OFFSET] = VOS_TRUE;
    aucSmsSrvParam[MN_MSG_SRV_RCV_SM_MEM_STORE_OFFSET] = MN_MSG_MEM_STORE_NV;

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(2))
        .with(any(), eq((VOS_UINT16)en_NV_Item_SMS_SERVICE_Para), outBoundP((void *)&aucSmsSrvParam, (VOS_UINT32)sizeof(aucSmsSrvParam)))
        .will(returnValue((VOS_UINT32)NV_OK));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_SMS_SERVICE_Para), outBoundP((void *)&aucSmsSrvParam, (VOS_UINT32)sizeof(aucSmsSrvParam)))
        .will(returnValue((VOS_UINT32)NV_OK));
#endif

    stClass0Tailor.ucActFlg             = MN_MSG_NVIM_ITEM_ACTIVE;
    stClass0Tailor.enClass0Tailor       = MN_MSG_CLASS0_DEF;

    enModemIdMocker = MODEM_ID_0;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(enModemIdMocker), eq((VOS_UINT16)en_NV_Item_SMS_CLASS0_TAILOR), outBoundP((void *)&stClass0Tailor, (VOS_UINT32)sizeof(stClass0Tailor)))
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    AT_ReadSmsNV();

    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstSmsCtx = AT_GetModemSmsCtxAddrFromModemId(enModemId);

        EXPECT_EQ(VOS_TRUE, pstSmsCtx->stCgsmsSendDomain.ucActFlg);
        EXPECT_EQ(MN_MSG_SEND_DOMAIN_PS_PREFERRED, pstSmsCtx->stCgsmsSendDomain.enSendDomain);
        EXPECT_EQ(VOS_TRUE, pstSmsCtx->enMsgMeStorageStatus);
        EXPECT_EQ(MN_MSG_MEM_STORE_NV, pstSmsCtx->stCpmsInfo.stRcvPath.enStaRptMemStore);
        EXPECT_EQ(MN_MSG_MEM_STORE_NV, pstSmsCtx->stCpmsInfo.stRcvPath.enSmMemStore);
    }

    EXPECT_EQ(MN_MSG_CLASS0_DEF, g_enClass0Tailor);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ReadSmsNV, Test_AT_ReadSmsNV_004)
{
    AT_NVIM_SEND_DOMAIN_STRU            stSendDomain;
    MN_MSG_ME_STORAGE_PARM_STRU         stMeStorageParm;
    VOS_UINT8                           aucSmsSrvParam[MN_MSG_SRV_PARAM_LEN];
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;
    MN_MSG_NVIM_CLASS0_TAILOR_STRU      stClass0Tailor;

    MODEM_ID_ENUM_UINT16                enModemIdMocker;

    enModemIdMocker = MODEM_ID_0;

    stSendDomain.ucActFlg = VOS_TRUE;
    stSendDomain.ucSendDomain = AT_NV_SMS_DOMAIN_CS_PREFERRED;
    MOCKER(AT_ReadSmsClosePathNV)
        .expects(exactly(1));

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(enModemIdMocker), eq((VOS_UINT16)en_NV_Item_SMS_SEND_DOMAIN), outBoundP((void *)&stSendDomain))
        .will(returnValue((VOS_UINT32)NV_OK));

    enModemIdMocker = MODEM_ID_1;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(enModemIdMocker), eq((VOS_UINT16)en_NV_Item_SMS_SEND_DOMAIN), outBoundP((void *)&stSendDomain))
        .will(returnValue((VOS_UINT32)NV_OK));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_SMS_SEND_DOMAIN), outBoundP((void *)&stSendDomain))
        .will(returnValue((VOS_UINT32)NV_OK));
#endif

    stMeStorageParm.enMeStorageStatus = MN_MSG_ME_STORAGE_ENABLE;

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(2))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Sms_Me_Storage_Info), outBoundP((void *)&stMeStorageParm))
        .will(returnValue((VOS_UINT32)NV_OK));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Sms_Me_Storage_Info), outBoundP((void *)&stMeStorageParm))
        .will(returnValue((VOS_UINT32)NV_OK));
#endif

    aucSmsSrvParam[MN_MSG_SRV_SM_MEM_ENABLE_OFFSET] = VOS_TRUE;
    aucSmsSrvParam[MN_MSG_SRV_RCV_SM_MEM_STORE_OFFSET] = MN_MSG_MEM_STORE_NV;

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(2))
        .with(any(), eq((VOS_UINT16)en_NV_Item_SMS_SERVICE_Para), outBoundP((void *)&aucSmsSrvParam))
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_SMS_SERVICE_Para), outBoundP((void *)&aucSmsSrvParam))
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));
#endif

    stClass0Tailor.ucActFlg             = MN_MSG_NVIM_ITEM_INACTIVE;
    stClass0Tailor.enClass0Tailor       = MN_MSG_CLASS0_DEF;
    enModemIdMocker = MODEM_ID_0;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(enModemIdMocker), eq((VOS_UINT16)en_NV_Item_SMS_CLASS0_TAILOR), outBoundP((void *)&stClass0Tailor))
        .will(returnValue((VOS_UINT32)NV_OK));

    AT_ReadSmsNV();

    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstSmsCtx = AT_GetModemSmsCtxAddrFromModemId(enModemId);

        EXPECT_EQ(VOS_TRUE, pstSmsCtx->stCgsmsSendDomain.ucActFlg);
        EXPECT_EQ(MN_MSG_SEND_DOMAIN_CS_PREFERRED, pstSmsCtx->stCgsmsSendDomain.enSendDomain);
        EXPECT_EQ(VOS_TRUE, pstSmsCtx->enMsgMeStorageStatus);
        EXPECT_EQ(MN_MSG_MEM_STORE_SIM, pstSmsCtx->stCpmsInfo.stRcvPath.enStaRptMemStore);
        EXPECT_EQ(MN_MSG_MEM_STORE_SIM, pstSmsCtx->stCpmsInfo.stRcvPath.enSmMemStore);
    }

    EXPECT_EQ(MN_MSG_CLASS0_DEF, g_enClass0Tailor);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

class Test_AT_ReadRptNV: public ::testing::Test
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
    }
    void TearDown()
    {

    }
};

#if 0

class Test_AT_ReadPrivateCmdStatusRptNV: public ::testing::Test
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


TEST_F(Test_AT_ReadPrivateCmdStatusRptNV, Test_AT_ReadPrivateCmdStatusRptNV_001)
{
    // ��������
    MODEM_ID_ENUM_UINT16                enModemId;
    NVIM_AT_PRIVATE_CMD_STATUS_RPT_STRU stAtCmdRptCtrl;

    // ������ʼ��
    enModemId                                     = MODEM_ID_0;
    stAtCmdRptCtrl.ucStatus                       = VOS_TRUE;
    stAtCmdRptCtrl.ucAtStatusReportGeneralControl = 1;

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����
    MOCKER(NV_ReadEx)
        .with(any(), any(), outBoundP((void *)&stAtCmdRptCtrl), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    // ���ñ��⺯��
    AT_ReadPrivateCmdStatusRptNV();

    // ִ�м��
    EXPECT_EQ(AT_STATUS_REPORT_GENERAL_CONTROL_NO_REPORT, g_astAtModemCtx[MODEM_ID_0].stCtrlCtx.ucStatusReportGeneralControl);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ReadRptNV, Test_AT_ReadRptNV_001)
{
    // ��������
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_CONTROL_CTX_STRU          *pstCtrlCtx = VOS_NULL_PTR;

    //������ʼ��

    // ��ʼ��ȫ�ֱ���
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstCtrlCtx = AT_GetModemCtrlCtxAddrFromModemId(enModemId);
        pstCtrlCtx->ucStatusReportGeneralControl     = AT_STATUS_REPORT_GENERAL_CONTROL_NO_REPORT;
    }
    g_enAtCCallStateRptStatus           = AT_CMD_RPT_STATUS_DISABLE;

    // MOCKER����;
#if(FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(3))
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(2))
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));
#endif
    // ���ñ��⺯��
    AT_ReadRptNV();

    // ִ�м��
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstCtrlCtx = AT_GetModemCtrlCtxAddrFromModemId(enModemId);
        EXPECT_EQ(AT_STATUS_REPORT_GENERAL_CONTROL_REPORT, pstCtrlCtx->ucStatusReportGeneralControl);
    }
    EXPECT_EQ(AT_CMD_RPT_STATUS_ENABLE, g_enAtCCallStateRptStatus);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ReadRptNV, Test_AT_ReadRptNV_002)
{
    // ��������
    NVIM_AT_PRIVATE_CMD_STATUS_RPT_STRU stAtCmdRptCtrl  = {0};
    AT_NV_CCALLSTATE_RPT_STATUS_STRU    stStatus        = {0};
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_CONTROL_CTX_STRU          *pstCtrlCtx = VOS_NULL_PTR;

    //������ʼ��
    stAtCmdRptCtrl.ucStatus                         = VOS_TRUE;
    stAtCmdRptCtrl.ucAtStatusReportGeneralControl   = 0;
    PS_MEM_SET(&stStatus, 0, sizeof(AT_NV_CCALLSTATE_RPT_STATUS_STRU));
    stStatus.enStatus                               = AT_CMD_RPT_STATUS_ENABLE;

    // ��ʼ��ȫ�ֱ���
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstCtrlCtx = AT_GetModemCtrlCtxAddrFromModemId(enModemId);
        pstCtrlCtx->ucStatusReportGeneralControl     = AT_STATUS_REPORT_GENERAL_CONTROL_NO_REPORT;
    }
    g_enAtCCallStateRptStatus           = AT_CMD_RPT_STATUS_DISABLE;

    // MOCKER����;
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(MODEM_ID_0), eq(en_NV_Item_PRIVATE_CMD_STATUS_RPT),
              outBoundP((void *)&stAtCmdRptCtrl, sizeof(NVIM_AT_PRIVATE_CMD_STATUS_RPT_STRU)),
              eq(sizeof(NVIM_AT_PRIVATE_CMD_STATUS_RPT_STRU)))
        .will(returnValue((VOS_UINT32)NV_OK));

#if(FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(MODEM_ID_1), eq(en_NV_Item_PRIVATE_CMD_STATUS_RPT),
        outBoundP((void *)&stAtCmdRptCtrl, sizeof(NVIM_AT_PRIVATE_CMD_STATUS_RPT_STRU)),
        eq(sizeof(NVIM_AT_PRIVATE_CMD_STATUS_RPT_STRU)))
        .will(returnValue((VOS_UINT32)NV_OK));
#endif

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq(en_NV_Item_CCallState_Rpt_Status),
              outBoundP((void *)&stStatus, sizeof(AT_NV_CCALLSTATE_RPT_STATUS_STRU)),
              eq(sizeof(AT_NV_CCALLSTATE_RPT_STATUS_STRU)))
        .will(returnValue((VOS_UINT32)NV_OK));

    // ���ñ��⺯��
    AT_ReadRptNV();

    // ִ�м��
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstCtrlCtx = AT_GetModemCtrlCtxAddrFromModemId(enModemId);

        EXPECT_EQ(AT_STATUS_REPORT_GENERAL_CONTROL_REPORT, pstCtrlCtx->ucStatusReportGeneralControl);
    }
    EXPECT_EQ(AT_CMD_RPT_STATUS_ENABLE, g_enAtCCallStateRptStatus);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ReadRptNV, Test_AT_ReadRptNV_003)
{
    // ��������
    NVIM_AT_PRIVATE_CMD_STATUS_RPT_STRU stAtCmdRptCtrl  = {0};
    AT_NV_CCALLSTATE_RPT_STATUS_STRU    stStatus        = {0};
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_CONTROL_CTX_STRU          *pstCtrlCtx = VOS_NULL_PTR;

     //������ʼ��
    stAtCmdRptCtrl.ucStatus                         = VOS_TRUE;
    stAtCmdRptCtrl.ucAtStatusReportGeneralControl   = 1;
    PS_MEM_SET(&stStatus, 0, sizeof(AT_NV_CCALLSTATE_RPT_STATUS_STRU));
    stStatus.enStatus                               = AT_CMD_RPT_STATUS_DISABLE;

    // ��ʼ��ȫ�ֱ���
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstCtrlCtx = AT_GetModemCtrlCtxAddrFromModemId(enModemId);

        pstCtrlCtx->ucStatusReportGeneralControl     = AT_STATUS_REPORT_GENERAL_CONTROL_NO_REPORT;
    }
    g_enAtCCallStateRptStatus           = AT_CMD_RPT_STATUS_DISABLE;

    // MOCKER����;
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(MODEM_ID_0), eq(en_NV_Item_PRIVATE_CMD_STATUS_RPT),
              outBoundP((void *)&stAtCmdRptCtrl, sizeof(NVIM_AT_PRIVATE_CMD_STATUS_RPT_STRU)),
              eq(sizeof(NVIM_AT_PRIVATE_CMD_STATUS_RPT_STRU)))
        .will(returnValue((VOS_UINT32)NV_OK));

#if(FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(MODEM_ID_1), eq(en_NV_Item_PRIVATE_CMD_STATUS_RPT),
        outBoundP((void *)&stAtCmdRptCtrl, sizeof(NVIM_AT_PRIVATE_CMD_STATUS_RPT_STRU)),
        eq(sizeof(NVIM_AT_PRIVATE_CMD_STATUS_RPT_STRU)))
        .will(returnValue((VOS_UINT32)NV_OK));
#endif

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq(en_NV_Item_CCallState_Rpt_Status),
              outBoundP((void *)&stStatus, sizeof(AT_NV_CCALLSTATE_RPT_STATUS_STRU)),
              eq(sizeof(AT_NV_CCALLSTATE_RPT_STATUS_STRU)))
        .will(returnValue((VOS_UINT32)NV_OK));

    // ���ñ��⺯��
    AT_ReadRptNV();

    // ִ�м��
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstCtrlCtx = AT_GetModemCtrlCtxAddrFromModemId(enModemId);
        EXPECT_EQ(AT_STATUS_REPORT_GENERAL_CONTROL_NO_REPORT, pstCtrlCtx->ucStatusReportGeneralControl);
    }
    EXPECT_EQ(AT_CMD_RPT_STATUS_DISABLE, g_enAtCCallStateRptStatus);

    GlobalMockObject::verify();
}
#endif


class Test_AT_ReadSystemAppConfigNV: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(NV_GetLength)
            .stubs()
            .will(returnValue((VOS_UINT32)NV_OK));

        AT_InitCtx();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_ReadSystemAppConfigNV, Test_AT_ReadSystemAppConfigNV_001)
{
    // ��������
    VOS_UINT8                            ucSystemAppConfig;
    VOS_UINT8                           *pucSystemAppConfig;

    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    //������ʼ��

    // ��ʼ��ȫ�ֱ���

    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    // ���ñ��⺯��
    AT_ReadSystemAppConfigNV();

    // ִ�м��
    EXPECT_EQ(SYSTEM_APP_MP, *pucSystemAppConfig);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ReadSystemAppConfigNV, Test_AT_ReadSystemAppConfigNV_002)
{
    // ��������
    VOS_UINT8                            ucSystemAppConfig;
    VOS_UINT8                           *pucSystemAppConfig;

    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    ucSystemAppConfig = SYSTEM_APP_ANDROID;
    //������ʼ��

    // ��ʼ��ȫ�ֱ���

    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), eq((VOS_UINT16)en_NV_Item_System_APP_Config), outBoundP((void *)&ucSystemAppConfig))
        .will(returnValue((VOS_UINT32)NV_OK));

    // ���ñ��⺯��
    AT_ReadSystemAppConfigNV();

    // ִ�м��
    EXPECT_EQ(SYSTEM_APP_ANDROID, *pucSystemAppConfig);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ReadSystemAppConfigNV, Test_AT_ReadSystemAppConfigNV_003)
{
    // ��������
    VOS_UINT8                            ucSystemAppConfig;
    VOS_UINT8                           *pucSystemAppConfig;

    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    ucSystemAppConfig = SYSTEM_APP_BUTT;
    //������ʼ��

    // ��ʼ��ȫ�ֱ���

    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), eq((VOS_UINT16)en_NV_Item_System_APP_Config), outBoundP((void *)&ucSystemAppConfig))
        .will(returnValue((VOS_UINT32)NV_OK));

    // ���ñ��⺯��
    AT_ReadSystemAppConfigNV();

    // ִ�м��
    EXPECT_EQ(SYSTEM_APP_MP, *pucSystemAppConfig);

    GlobalMockObject::verify();
}


class Test_AT_ReadRoamCapaNV: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(NV_GetLength)
            .stubs()
            .will(returnValue((VOS_UINT32)NV_OK));

        AT_InitCtx();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_ReadRoamCapaNV, Test_AT_ReadRoamCapaNV_001)
{
    // ��������
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    //������ʼ��

    // ��ʼ��ȫ�ֱ���

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(2))
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));
#endif

    // ���ñ��⺯��
    AT_ReadRoamCapaNV();

    // ִ�м��
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);

        EXPECT_EQ(AT_ROAM_FEATURE_OFF, pstNetCtx->ucRoamFeature);
    }

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ReadRoamCapaNV, Test_AT_ReadRoamCapaNV_002)
{
    // ��������
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    VOS_UINT8                           aucTmp[2];

    //������ʼ��
    aucTmp[0] = AT_ROAM_FEATURE_ON;
    // ��ʼ��ȫ�ֱ���

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(2))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Roam_Capa), outBoundP((void *)aucTmp))
        .will(returnValue((VOS_UINT32)NV_OK));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Roam_Capa), outBoundP((void *)aucTmp))
        .will(returnValue((VOS_UINT32)NV_OK));
#endif

    // ���ñ��⺯��
    AT_ReadRoamCapaNV();

    // ִ�м��
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);

        EXPECT_EQ(AT_ROAM_FEATURE_ON, pstNetCtx->ucRoamFeature);
    }

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ReadRoamCapaNV, Test_AT_ReadRoamCapaNV_003)
{
    // ��������
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    VOS_UINT8                           aucTmp[2];

    //������ʼ��
    aucTmp[0] = 2;
    // ��ʼ��ȫ�ֱ���

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(2))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Roam_Capa), outBoundP((void *)aucTmp))
        .will(returnValue((VOS_UINT32)NV_OK));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Roam_Capa), outBoundP((void *)aucTmp))
        .will(returnValue((VOS_UINT32)NV_OK));
#endif

    // ���ñ��⺯��
    AT_ReadRoamCapaNV();

    // ִ�м��
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);

        EXPECT_EQ(AT_ROAM_FEATURE_OFF, pstNetCtx->ucRoamFeature);
    }

    GlobalMockObject::verify();
}



class Test_AT_ReadAbortCmdParaNV: public ::testing::Test
{
public:

    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(NV_GetLength)
            .stubs()
            .will(returnValue((VOS_UINT32)NV_OK));

        AT_ABORT_CMD_PARA_STRU             *pstCmdPara;

        pstCmdPara = AT_GetAbortCmdPara();

        PS_MEM_SET(pstCmdPara->aucAbortAtCmdStr, 0x00, sizeof(pstCmdPara->aucAbortAtCmdStr));
        PS_MEM_SET(pstCmdPara->aucAbortAtRspStr, 0x00, sizeof(pstCmdPara->aucAbortAtRspStr));
    }

    void TearDown()
    {
        AT_ABORT_CMD_PARA_STRU             *pstCmdPara;

        pstCmdPara = AT_GetAbortCmdPara();

        PS_MEM_SET(pstCmdPara->aucAbortAtCmdStr, 0x00, sizeof(pstCmdPara->aucAbortAtCmdStr));
        PS_MEM_SET(pstCmdPara->aucAbortAtRspStr, 0x00, sizeof(pstCmdPara->aucAbortAtRspStr));
    }
};


TEST_F(Test_AT_ReadAbortCmdParaNV, Test_AT_ReadAbortCmdParaNV_001)
{
    AT_NVIM_ABORT_CMD_PARA_STRU         stTmpNvAbortCmdPara;
    AT_ABORT_CMD_PARA_STRU             *pstCmdPara;

    pstCmdPara = AT_GetAbortCmdPara();

    stTmpNvAbortCmdPara.ucAbortEnableFlg = VOS_FALSE;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), any(), outBoundP((void *)&stTmpNvAbortCmdPara, (VOS_UINT32)sizeof(stTmpNvAbortCmdPara)), eq((VOS_UINT32)sizeof(stTmpNvAbortCmdPara)))
        .will(returnValue((VOS_UINT32)NV_OK));

    AT_ReadAbortCmdParaNV();

    EXPECT_EQ(VOS_FALSE, pstCmdPara->ucAbortEnableFlg);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ReadAbortCmdParaNV, Test_AT_ReadAbortCmdParaNV_002)
{
    AT_ABORT_CMD_PARA_STRU             *pstCmdPara;
    VOS_UINT8                           aucDfltAbortCmd[] = "AT";
    VOS_UINT8                           aucDfltAbortRsp[] = "OK";

    pstCmdPara = AT_GetAbortCmdPara();

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    AT_ReadAbortCmdParaNV();

    EXPECT_EQ(VOS_TRUE, pstCmdPara->ucAbortEnableFlg);
    EXPECT_STREQ((char*)aucDfltAbortCmd, (char*)pstCmdPara->aucAbortAtCmdStr);
    EXPECT_STREQ((char*)aucDfltAbortRsp, (char*)pstCmdPara->aucAbortAtRspStr);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ReadAbortCmdParaNV, Test_AT_ReadAbortCmdParaNV_003)
{
    AT_NVIM_ABORT_CMD_PARA_STRU         stTmpNvAbortCmdPara;
    AT_ABORT_CMD_PARA_STRU             *pstCmdPara;
    VOS_UINT8                           aucDfltAbortCmd[] = "AT";
    VOS_UINT8                           aucDfltAbortRsp[] = "OK";

    pstCmdPara = AT_GetAbortCmdPara();

    stTmpNvAbortCmdPara.ucAbortEnableFlg = VOS_TRUE;

    stTmpNvAbortCmdPara.aucAbortAtCmdStr[0] = 'a';
    stTmpNvAbortCmdPara.aucAbortAtCmdStr[1] = '\n';

    stTmpNvAbortCmdPara.aucAbortAtRspStr[0] = 'O';
    stTmpNvAbortCmdPara.aucAbortAtRspStr[1] = 'K';
    stTmpNvAbortCmdPara.aucAbortAtRspStr[2] = '\n';

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(),any(), outBoundP((void *)&stTmpNvAbortCmdPara, (VOS_UINT32)sizeof(stTmpNvAbortCmdPara)), eq((VOS_UINT32)sizeof(stTmpNvAbortCmdPara)))
        .will(returnValue((VOS_UINT32)NV_OK));

    AT_ReadAbortCmdParaNV();

    EXPECT_EQ(VOS_TRUE, pstCmdPara->ucAbortEnableFlg);
    EXPECT_STREQ((char*)aucDfltAbortCmd, (char*)pstCmdPara->aucAbortAtCmdStr);
    EXPECT_STREQ((char*)aucDfltAbortRsp, (char*)pstCmdPara->aucAbortAtRspStr);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ReadAbortCmdParaNV, Test_AT_ReadAbortCmdParaNV_004)
{
    AT_NVIM_ABORT_CMD_PARA_STRU         stTmpNvAbortCmdPara;
    AT_ABORT_CMD_PARA_STRU             *pstCmdPara;
    VOS_UINT8                           aucDfltAbortCmd[] = "AT";
    VOS_UINT8                           aucDfltAbortRsp[] = "OK";

    pstCmdPara = AT_GetAbortCmdPara();

    stTmpNvAbortCmdPara.ucAbortEnableFlg = VOS_TRUE;

    stTmpNvAbortCmdPara.aucAbortAtCmdStr[0] = 'A';
    stTmpNvAbortCmdPara.aucAbortAtCmdStr[1] = 'T';
    stTmpNvAbortCmdPara.aucAbortAtCmdStr[2] = '\n';

    stTmpNvAbortCmdPara.aucAbortAtRspStr[0] = 'B';
    stTmpNvAbortCmdPara.aucAbortAtRspStr[1] = '\n';

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(),any(), outBoundP((void *)&stTmpNvAbortCmdPara, (VOS_UINT32)sizeof(stTmpNvAbortCmdPara)), eq((VOS_UINT32)sizeof(stTmpNvAbortCmdPara)))
        .will(returnValue((VOS_UINT32)NV_OK));

    AT_ReadAbortCmdParaNV();

    EXPECT_EQ(VOS_TRUE, pstCmdPara->ucAbortEnableFlg);
    EXPECT_STREQ((char*)aucDfltAbortCmd, (char*)pstCmdPara->aucAbortAtCmdStr);
    EXPECT_STREQ((char*)aucDfltAbortRsp, (char*)pstCmdPara->aucAbortAtRspStr);

    GlobalMockObject::verify();
}



TEST_F(Test_AT_ReadAbortCmdParaNV, Test_AT_ReadAbortCmdParaNV_005)
{
    AT_NVIM_ABORT_CMD_PARA_STRU         stTmpNvAbortCmdPara;
    AT_ABORT_CMD_PARA_STRU             *pstCmdPara;
    VOS_UINT8                           aucDfltAbortCmd[] = "AT^BREAK";
    VOS_UINT8                           aucDfltAbortRsp[] = "ABORT";

    pstCmdPara = AT_GetAbortCmdPara();

    stTmpNvAbortCmdPara.ucAbortEnableFlg = VOS_TRUE;

    VOS_StrNCpy((VOS_CHAR *)stTmpNvAbortCmdPara.aucAbortAtCmdStr,
                (VOS_CHAR *)aucDfltAbortCmd,
                AT_MAX_ABORT_CMD_STR_LEN);

    VOS_StrNCpy((VOS_CHAR *)stTmpNvAbortCmdPara.aucAbortAtRspStr,
                (VOS_CHAR *)aucDfltAbortRsp,
                AT_MAX_ABORT_RSP_STR_LEN);

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(),any(), outBoundP((void *)&stTmpNvAbortCmdPara, (VOS_UINT32)sizeof(stTmpNvAbortCmdPara)), eq((VOS_UINT32)sizeof(stTmpNvAbortCmdPara)))
        .will(returnValue((VOS_UINT32)NV_OK));

    AT_ReadAbortCmdParaNV();

    EXPECT_EQ(VOS_TRUE, pstCmdPara->ucAbortEnableFlg);
    EXPECT_STREQ((char*)aucDfltAbortCmd, (char*)pstCmdPara->aucAbortAtCmdStr);
    EXPECT_STREQ((char*)aucDfltAbortRsp, (char*)pstCmdPara->aucAbortAtRspStr);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ReadAbortCmdParaNV, Test_AT_ReadAbortCmdParaNV_006)
{
    AT_NVIM_ABORT_CMD_PARA_STRU         stTmpNvAbortCmdPara;
    AT_ABORT_CMD_PARA_STRU             *pstCmdPara;
    VOS_UINT8                           aucDfltAbortCmd[] = "ANY1";
    VOS_UINT8                           aucDfltAbortRsp[] = "ABORT";

    pstCmdPara = AT_GetAbortCmdPara();

    stTmpNvAbortCmdPara.ucAbortEnableFlg = VOS_TRUE;

    VOS_StrNCpy((VOS_CHAR *)stTmpNvAbortCmdPara.aucAbortAtCmdStr,
                (VOS_CHAR *)aucDfltAbortCmd,
                AT_MAX_ABORT_CMD_STR_LEN);

    VOS_StrNCpy((VOS_CHAR *)stTmpNvAbortCmdPara.aucAbortAtRspStr,
                (VOS_CHAR *)aucDfltAbortRsp,
                AT_MAX_ABORT_RSP_STR_LEN);

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(),any(), outBoundP((void *)&stTmpNvAbortCmdPara, (VOS_UINT32)sizeof(stTmpNvAbortCmdPara)), eq((VOS_UINT32)sizeof(stTmpNvAbortCmdPara)))
        .will(returnValue((VOS_UINT32)NV_OK));

    AT_ReadAbortCmdParaNV();

    EXPECT_EQ(VOS_TRUE, pstCmdPara->ucAbortEnableFlg);
    EXPECT_STREQ((char*)aucDfltAbortCmd, (char*)pstCmdPara->aucAbortAtCmdStr);
    EXPECT_STREQ((char*)aucDfltAbortRsp, (char*)pstCmdPara->aucAbortAtRspStr);
    EXPECT_EQ(VOS_FALSE, pstCmdPara->ucAnyAbortFlg);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ReadAbortCmdParaNV, Test_AT_ReadAbortCmdParaNV_007)
{
    AT_NVIM_ABORT_CMD_PARA_STRU         stTmpNvAbortCmdPara;
    AT_ABORT_CMD_PARA_STRU             *pstCmdPara;
    VOS_UINT8                           aucDfltAbortCmd[] = "ABC";
    VOS_UINT8                           aucDfltAbortRsp[] = "ABORT";

    pstCmdPara = AT_GetAbortCmdPara();

    stTmpNvAbortCmdPara.ucAbortEnableFlg = VOS_TRUE;

    VOS_StrNCpy((VOS_CHAR *)stTmpNvAbortCmdPara.aucAbortAtCmdStr,
                (VOS_CHAR *)aucDfltAbortCmd,
                AT_MAX_ABORT_CMD_STR_LEN);

    VOS_StrNCpy((VOS_CHAR *)stTmpNvAbortCmdPara.aucAbortAtRspStr,
                (VOS_CHAR *)aucDfltAbortRsp,
                AT_MAX_ABORT_RSP_STR_LEN);

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(),any(), outBoundP((void *)&stTmpNvAbortCmdPara, (VOS_UINT32)sizeof(stTmpNvAbortCmdPara)), eq((VOS_UINT32)sizeof(stTmpNvAbortCmdPara)))
        .will(returnValue((VOS_UINT32)NV_OK));

    AT_ReadAbortCmdParaNV();

    EXPECT_EQ(VOS_TRUE, pstCmdPara->ucAbortEnableFlg);
    EXPECT_STREQ((char*)aucDfltAbortCmd, (char*)pstCmdPara->aucAbortAtCmdStr);
    EXPECT_STREQ((char*)aucDfltAbortRsp, (char*)pstCmdPara->aucAbortAtRspStr);
    EXPECT_EQ(VOS_FALSE, pstCmdPara->ucAnyAbortFlg);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ReadAbortCmdParaNV, Test_AT_ReadAbortCmdParaNV_008)
{
    AT_NVIM_ABORT_CMD_PARA_STRU         stTmpNvAbortCmdPara;
    AT_ABORT_CMD_PARA_STRU             *pstCmdPara;
    VOS_UINT8                           aucDfltAbortCmd[] = "ANY";
    VOS_UINT8                           aucDfltAbortRsp[] = "ABORT";

    pstCmdPara = AT_GetAbortCmdPara();

    stTmpNvAbortCmdPara.ucAbortEnableFlg = VOS_TRUE;

    VOS_StrNCpy((VOS_CHAR *)stTmpNvAbortCmdPara.aucAbortAtCmdStr,
                (VOS_CHAR *)aucDfltAbortCmd,
                AT_MAX_ABORT_CMD_STR_LEN);

    VOS_StrNCpy((VOS_CHAR *)stTmpNvAbortCmdPara.aucAbortAtRspStr,
                (VOS_CHAR *)aucDfltAbortRsp,
                AT_MAX_ABORT_RSP_STR_LEN);

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(),any(), outBoundP((void *)&stTmpNvAbortCmdPara, (VOS_UINT32)sizeof(stTmpNvAbortCmdPara)), eq((VOS_UINT32)sizeof(stTmpNvAbortCmdPara)))
        .will(returnValue((VOS_UINT32)NV_OK));

    AT_ReadAbortCmdParaNV();

    EXPECT_EQ(VOS_TRUE, pstCmdPara->ucAbortEnableFlg);
    EXPECT_STREQ((char*)aucDfltAbortCmd, (char*)pstCmdPara->aucAbortAtCmdStr);
    EXPECT_STREQ((char*)aucDfltAbortRsp, (char*)pstCmdPara->aucAbortAtRspStr);
    EXPECT_EQ(VOS_TRUE, pstCmdPara->ucAnyAbortFlg);

    GlobalMockObject::verify();
}





class Test_AT_IsAbortCmdCharValid: public ::testing::Test
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


TEST_F(Test_AT_IsAbortCmdCharValid, Test_AT_IsAbortCmdCharValid_001)
{
    EXPECT_EQ(VOS_FALSE, AT_IsAbortCmdCharValid(VOS_NULL_PTR, 0));

    GlobalMockObject::verify();
}




TEST_F(Test_AT_IsAbortCmdCharValid, Test_AT_IsAbortCmdCharValid_002)
{
    VOS_UINT8                          *pucAbortCmdChar;
    VOS_UINT32                          ulLen;

    pucAbortCmdChar = (VOS_UINT8 *)malloc(sizeof(VOS_UINT8));
    ulLen           = 0;

    EXPECT_EQ(VOS_FALSE, AT_IsAbortCmdCharValid(pucAbortCmdChar, ulLen));

    GlobalMockObject::verify();
}


class Test_AT_ReadSysNV: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(NV_GetLength)
            .stubs()
            .will(returnValue((VOS_UINT32)NV_OK));
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_ReadSysNV,Test_AT_ReadSysNV_001)
{
    VOS_UINT8                           aucTmp[2];
    VOS_UINT16                          usNVId;
    VOS_UINT16                          usModem0;
    VOS_UINT16                          usModem1;

    aucTmp[0] = 1;
    usNVId = en_NV_Item_Roam_Capa;
    usModem0 = MODEM_ID_0;
    usModem1 = MODEM_ID_1;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(usModem0), eq(usNVId), outBoundP((void *)aucTmp,sizeof(aucTmp)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

#if(FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(usModem1), eq(usNVId), outBoundP((void *)aucTmp, sizeof(aucTmp)), any())
        .will(returnValue((VOS_UINT32)NV_OK));
#endif

    MOCKER(AT_ReadSystemAppConfigNV)
        .expects(exactly(1));

    MOCKER(AT_ReadE5NV)
        .expects(exactly(1));


    MOCKER(AT_ReadAbortCmdParaNV)
        .expects(exactly(1));

    AT_ReadSysNV();

    EXPECT_EQ(aucTmp[0], AT_GetModemNetCtxAddrFromClientId(0)->ucRoamFeature);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ReadSysNV,Test_AT_ReadSysNV_002)
{

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(2))
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));
#endif

    MOCKER(AT_ReadSystemAppConfigNV)
        .expects(exactly(1));

    MOCKER(AT_ReadE5NV)
        .expects(exactly(1));


    MOCKER(AT_ReadAbortCmdParaNV)
        .expects(exactly(1));

    AT_ReadSysNV();

    EXPECT_EQ(AT_GetModemNetCtxAddrFromClientId(0)->ucRoamFeature, AT_ROAM_FEATURE_OFF);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ReadSysNV,Test_AT_ReadSysNV_003)
{
    VOS_UINT8                           aucTmp[2];
    VOS_UINT16                          usNVId;
    VOS_UINT16                          usModem0;
    VOS_UINT16                          usModem1;

    aucTmp[0]   = 5;
    usNVId      = en_NV_Item_Roam_Capa;
    usModem0    = MODEM_ID_0;
    usModem1    = MODEM_ID_1;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(usModem0), eq(usNVId), outBoundP((void *)aucTmp, sizeof(aucTmp)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

#if(FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq(usModem1), eq(usNVId), outBoundP((void *)aucTmp, sizeof(aucTmp)), any())
        .will(returnValue((VOS_UINT32)NV_OK));
#endif

    MOCKER(AT_ReadSystemAppConfigNV)
        .expects(exactly(1));

    MOCKER(AT_ReadE5NV)
        .expects(exactly(1));


    MOCKER(AT_ReadAbortCmdParaNV)
        .expects(exactly(1));

    AT_ReadSysNV();

    EXPECT_EQ(AT_ROAM_FEATURE_OFF, AT_GetModemNetCtxAddrFromClientId(0)->ucRoamFeature);

    GlobalMockObject::verify();
}


class Test_AT_ReadCellSignReportCfgNV: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(NV_GetLength)
            .stubs()
            .will(returnValue((VOS_UINT32)NV_OK));

    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_ReadCellSignReportCfgNV, Test_AT_ReadCellSignReportCfgNV_001)
{
    // ��������

    // ������ʼ��

    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);

        pstNetCtx->ucCerssiReportType = AT_CERSSI_REPORT_TYPE_NOT_REPORT;

    }

    // ��ʼ��ȫ�ֱ���;

    // MOCKER����;
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    // ���ñ��⺯��
    AT_ReadCellSignReportCfgNV();

    // ִ�м��
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);

        EXPECT_EQ(AT_CERSSI_REPORT_TYPE_NOT_REPORT, pstNetCtx->ucCerssiReportType);
    }

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ReadCellSignReportCfgNV, Test_AT_ReadCellSignReportCfgNV_002)
{
    // ��������
    NAS_NVIM_CELL_SIGN_REPORT_CFG_STRU  stCellSignReportCfg;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    // ������ʼ��
    stCellSignReportCfg.enSignThreshold = AT_CERSSI_REPORT_TYPE_BUTT;


    // ��ʼ��ȫ�ֱ���;

    // MOCKER����;
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), eq((VOS_UINT16)en_NV_Item_CELL_SIGN_REPORT_CFG), outBoundP((void *)&stCellSignReportCfg), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    // ���ñ��⺯��
    AT_ReadCellSignReportCfgNV();

    // ִ�м��
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);

        EXPECT_EQ(AT_CERSSI_REPORT_TYPE_NOT_REPORT, pstNetCtx->ucCerssiReportType);
    }

    GlobalMockObject::verify();
}


class Test_AT_ReadCsNV: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(NV_GetLength)
            .stubs()
            .will(returnValue((VOS_UINT32)NV_OK));

    }
    void TearDown()
    {
    }
protected:

};


TEST_F(Test_AT_ReadCsNV, Test_AT_ReadCsNV_001)
{
    // ��������
    MODEM_ID_ENUM_UINT16                enModemId;
    TAF_USSD_NVIM_TRANS_MODE_STRU       stUssdTranMode;
    TAF_CCA_TELE_PARA_STRU              stTimeInfo;

    // ������ʼ��
    enModemId                       = MODEM_ID_0;
    stTimeInfo.ucS0TimerLen         = 5;
    stUssdTranMode.ucStatus         = 1;
    stUssdTranMode.ucUssdTransMode  = 1;

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq((MODEM_ID_ENUM_UINT16)MODEM_ID_0), eq((VOS_UINT16)en_NV_Item_CCA_TelePara), outBoundP((void *)&stTimeInfo, (VOS_UINT32)sizeof(stTimeInfo)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(eq((MODEM_ID_ENUM_UINT16)MODEM_ID_1), eq((VOS_UINT16)en_NV_Item_CCA_TelePara), outBoundP((void *)&stTimeInfo, (VOS_UINT32)sizeof(stTimeInfo)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_ReadEx)
        .expects(exactly(2))
        .with(eq((MODEM_ID_ENUM_UINT16)MODEM_ID_0), eq((VOS_UINT16)en_NV_Item_CUST_USSD_MODE), outBoundP((void *)&stUssdTranMode, (VOS_UINT32)sizeof(stUssdTranMode)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_SS_CUSTOMIZE_PARA), any(), any())
        .will(returnValue((VOS_UINT32)NV_OK));
#else
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), any(), outBoundP((void *)&stTimeInfo, (VOS_UINT32)sizeof(stTimeInfo)), any())
        .will(returnValue((VOS_UINT32)NV_OK));
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), any(), outBoundP((void *)&stUssdTranMode, (VOS_UINT32)sizeof(stUssdTranMode)), any())
        .will(returnValue((VOS_UINT32)NV_OK));
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), any(), any(), any())
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));
#endif

    // ���ñ��⺯��
    AT_ReadCsNV();

    // ִ�м��
    EXPECT_EQ(5, g_astAtModemCtx[MODEM_ID_0].stCcCtx.stS0TimeInfo.ucS0TimerLen);
    EXPECT_EQ(1, g_astAtModemCtx[MODEM_ID_0].stSsCtx.usUssdTransMode);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_AT_ValidateWasCategory: public ::testing::Test
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


TEST_F(Test_AT_ValidateWasCategory, Test_AT_ValidateWasCategory_001)
{
    // ��������
    AT_NV_UE_CAPABILITY_STRU            stUeCapability;
    VOS_UINT32                          ulRslt;

    // ������ʼ��
    stUeCapability.ucHSDSCHSupport      = VOS_TRUE;
    stUeCapability.ucHSDSCHPhyCategory  = 0;

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_ValidateWasCategory(&stUeCapability);

    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ValidateWasCategory, Test_AT_ValidateWasCategory_002)
{
    // ��������
    AT_NV_UE_CAPABILITY_STRU            stUeCapability;
    VOS_UINT32                          ulRslt;

    // ������ʼ��
    stUeCapability.ucHSDSCHSupport      = VOS_TRUE;
    stUeCapability.ucHSDSCHPhyCategory  = 2;

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_ValidateWasCategory(&stUeCapability);

    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_AT_ValidateWasCategoryExt: public ::testing::Test
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


TEST_F(Test_AT_ValidateWasCategoryExt, Test_AT_ValidateWasCategoryExt_001)
{
    // ��������
    AT_NV_UE_CAPABILITY_STRU            stUeCapability;
    VOS_UINT32                          ulRslt;

    // ������ʼ��
    stUeCapability.ucHSDSCHSupport          = VOS_TRUE;
    stUeCapability.ucMacEhsSupport          = VOS_TRUE;
    stUeCapability.ucHSDSCHPhyCategoryExt   = 10;

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_ValidateWasCategoryExt(&stUeCapability);

    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ValidateWasCategoryExt, Test_AT_ValidateWasCategoryExt_002)
{
    // ��������
    AT_NV_UE_CAPABILITY_STRU            stUeCapability;
    VOS_UINT32                          ulRslt;

    // ������ʼ��
    stUeCapability.ucHSDSCHSupport          = VOS_TRUE;
    stUeCapability.ucMacEhsSupport          = VOS_TRUE;
    stUeCapability.ucHSDSCHPhyCategoryExt   = 15;

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_ValidateWasCategoryExt(&stUeCapability);

    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_AT_ValidateWasCategoryExt2: public ::testing::Test
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


TEST_F(Test_AT_ValidateWasCategoryExt2, Test_AT_ValidateWasCategoryExt2_001)
{
    // ��������
    AT_NV_UE_CAPABILITY_STRU            stUeCapability;
    VOS_UINT32                          ulRslt;

    // ������ʼ��
    stUeCapability.ucHSDSCHSupport          = VOS_TRUE;
    stUeCapability.ucMacEhsSupport          = VOS_TRUE;
    stUeCapability.ucMultiCellSupport       = VOS_TRUE;
    stUeCapability.ucHSDSCHPhyCategoryExt2  = 20;

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_ValidateWasCategoryExt2(&stUeCapability);

    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ValidateWasCategoryExt2, Test_AT_ValidateWasCategoryExt2_002)
{
    // ��������
    AT_NV_UE_CAPABILITY_STRU            stUeCapability;
    VOS_UINT32                          ulRslt;

    // ������ʼ��
    stUeCapability.ucHSDSCHSupport          = VOS_TRUE;
    stUeCapability.ucMacEhsSupport          = VOS_TRUE;
    stUeCapability.ucMultiCellSupport       = VOS_TRUE;
    stUeCapability.ucHSDSCHPhyCategoryExt2  = 22;

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_ValidateWasCategoryExt2(&stUeCapability);

    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_AT_ValidateWasCategoryExt3: public ::testing::Test
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


TEST_F(Test_AT_ValidateWasCategoryExt3, Test_AT_ValidateWasCategoryExt3_001)
{
    // ��������
    AT_NV_UE_CAPABILITY_STRU            stUeCapability;
    VOS_UINT32                          ulRslt;

    // ������ʼ��
    stUeCapability.ucHSDSCHSupport          = VOS_TRUE;
    stUeCapability.ucMacEhsSupport          = VOS_TRUE;
    stUeCapability.ucMultiCellSupport       = VOS_TRUE;
    stUeCapability.ucDcMimoSupport          = VOS_TRUE;
    stUeCapability.ucHSDSCHPhyCategoryExt3  = 20;

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_ValidateWasCategoryExt3(&stUeCapability);

    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ValidateWasCategoryExt3, Test_AT_ValidateWasCategoryExt3_002)
{
    // ��������
    AT_NV_UE_CAPABILITY_STRU            stUeCapability;
    VOS_UINT32                          ulRslt;

    // ������ʼ��
    stUeCapability.ucHSDSCHSupport          = VOS_TRUE;
    stUeCapability.ucMacEhsSupport          = VOS_TRUE;
    stUeCapability.ucMultiCellSupport       = VOS_TRUE;
    stUeCapability.ucDcMimoSupport          = VOS_TRUE;
    stUeCapability.ucHSDSCHPhyCategoryExt3  = 26;

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_ValidateWasCategoryExt3(&stUeCapability);

    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_AT_GetWasDefaultCategory: public ::testing::Test
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


TEST_F(Test_AT_GetWasDefaultCategory, Test_AT_GetWasDefaultCategory_001)
{
    // ��������
    AT_NV_UE_CAPABILITY_STRU            stUeCapability;
    VOS_UINT8                           ulRslt;

    // ������ʼ��
    stUeCapability.ucAsRelIndicator = PS_PTL_VER_R5;

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_GetWasDefaultCategory(&stUeCapability);

    // ִ�м��
    EXPECT_EQ(AT_RATE_WCDMA_CATEGORY_10, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_GetWasDefaultCategory, Test_AT_GetWasDefaultCategory_002)
{
    // ��������
    AT_NV_UE_CAPABILITY_STRU            stUeCapability;
    VOS_UINT8                           ulRslt;

    // ������ʼ��
    stUeCapability.ucAsRelIndicator = PS_PTL_VER_R6;

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_GetWasDefaultCategory(&stUeCapability);

    // ִ�м��
    EXPECT_EQ(AT_RATE_WCDMA_CATEGORY_10, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_GetWasDefaultCategory, Test_AT_GetWasDefaultCategory_003)
{
    // ��������
    AT_NV_UE_CAPABILITY_STRU            stUeCapability;
    VOS_UINT8                           ulRslt;

    // ������ʼ��
    stUeCapability.ucAsRelIndicator = PS_PTL_VER_R7;

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_GetWasDefaultCategory(&stUeCapability);

    // ִ�м��
    EXPECT_EQ(AT_RATE_WCDMA_CATEGORY_18, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_GetWasDefaultCategory, Test_AT_GetWasDefaultCategory_004)
{
    // ��������
    AT_NV_UE_CAPABILITY_STRU            stUeCapability;
    VOS_UINT8                           ulRslt;

    // ������ʼ��
    stUeCapability.ucAsRelIndicator = PS_PTL_VER_R8;

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_GetWasDefaultCategory(&stUeCapability);

    // ִ�м��
    EXPECT_EQ(AT_RATE_WCDMA_CATEGORY_28, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_AT_CalcWasCategory: public ::testing::Test
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


TEST_F(Test_AT_CalcWasCategory, Test_AT_CalcWasCategory_001)
{
    // ��������
    AT_NV_UE_CAPABILITY_STRU            stUeCapability;
    VOS_UINT8                           ulRslt;

    // ������ʼ��
    PS_MEM_SET(&stUeCapability, 0, sizeof(stUeCapability));

    stUeCapability.ucHSDSCHSupport          = VOS_TRUE;
    stUeCapability.ucMacEhsSupport          = VOS_TRUE;
    stUeCapability.ucMultiCellSupport       = VOS_TRUE;
    stUeCapability.ucDcMimoSupport          = VOS_TRUE;
    stUeCapability.ucHSDSCHPhyCategoryExt3  = 26;

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_CalcWasCategory(&stUeCapability);

    // ִ�м��
    EXPECT_EQ(26, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_CalcWasCategory, Test_AT_CalcWasCategory_002)
{
    // ��������
    AT_NV_UE_CAPABILITY_STRU            stUeCapability;
    VOS_UINT8                           ulRslt;

    // ������ʼ��
    PS_MEM_SET(&stUeCapability, 0, sizeof(stUeCapability));

    stUeCapability.ucHSDSCHSupport          = VOS_TRUE;
    stUeCapability.ucMacEhsSupport          = VOS_TRUE;
    stUeCapability.ucMultiCellSupport       = VOS_TRUE;
    stUeCapability.ucHSDSCHPhyCategoryExt2  = 22;

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_CalcWasCategory(&stUeCapability);

    // ִ�м��
    EXPECT_EQ(22, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

TEST_F(Test_AT_CalcWasCategory, Test_AT_CalcWasCategory_003)
{
    // ��������
    AT_NV_UE_CAPABILITY_STRU            stUeCapability;
    VOS_UINT8                           ulRslt;

    // ������ʼ��
    PS_MEM_SET(&stUeCapability, 0, sizeof(stUeCapability));

    stUeCapability.ucHSDSCHSupport          = VOS_TRUE;
    stUeCapability.ucMacEhsSupport          = VOS_TRUE;
    stUeCapability.ucHSDSCHPhyCategoryExt   = 15;

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_CalcWasCategory(&stUeCapability);

    // ִ�м��
    EXPECT_EQ(15, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_CalcWasCategory, Test_AT_CalcWasCategory_004)
{
    // ��������
    AT_NV_UE_CAPABILITY_STRU            stUeCapability;
    VOS_UINT8                           ulRslt;

    // ������ʼ��
    stUeCapability.ucHSDSCHSupport      = VOS_TRUE;
    stUeCapability.ucHSDSCHPhyCategory  = 2;

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����

    // ���ñ��⺯��
    ulRslt = AT_CalcWasCategory(&stUeCapability);

    // ִ�м��
    EXPECT_EQ(2, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_AT_ReadGasCapabilityNV: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

    }
    void TearDown()
    {
    }
protected:

};


TEST_F(Test_AT_ReadGasCapabilityNV, Test_AT_ReadGasCapabilityNV_001)
{
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    /* ������Ϣ��ں��� */
    AT_ReadGasCapabilityNV();

    /* �����֤*/
    EXPECT_EQ(VOS_FALSE,g_stAtDlRateCategory.ucGasMultislotClass33Flg);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F(Test_AT_ReadGasCapabilityNV, Test_AT_ReadGasCapabilityNV_002)
{
    NVIM_GAS_HIGH_MULTISLOT_CLASS_STRU          stHighMultislotclass;
    VOS_UINT16                                  usGprsMultiSlotClass;
    VOS_UINT16                                  usEgprsMultiSlotClass;
    VOS_UINT16                                  usEgprsFlag;

    usEgprsFlag                                     = VOS_TRUE;
    usGprsMultiSlotClass                            = AT_GAS_GRR_MULTISLOT_CLASS_MAX;
    usEgprsMultiSlotClass                           = AT_GAS_GRR_MULTISLOT_CLASS_MAX;
    stHighMultislotclass.usHighMultislotClassFlg    = VOS_TRUE;
    stHighMultislotclass.usHighMultislotClass       = AT_GAS_HIGH_MULTISLOT_CLASS_0;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(),eq((VOS_UINT16)en_NV_Item_Egprs_Flag),outBoundP((void *)&usEgprsFlag, (VOS_UINT32)sizeof(usEgprsFlag)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(),eq((VOS_UINT16)en_Nv_Item_Gprs_Multi_Slot_Class),outBoundP((void *)&usGprsMultiSlotClass, (VOS_UINT32)sizeof(usGprsMultiSlotClass)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(),eq((VOS_UINT16)en_NV_Item_Egprs_Multi_Slot_Class),outBoundP((void *)&usEgprsMultiSlotClass, (VOS_UINT32)sizeof(usEgprsMultiSlotClass)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(),eq((VOS_UINT16)en_NV_Item_GAS_High_Multislot_Class),outBoundP((void *)&stHighMultislotclass, (VOS_UINT32)sizeof(stHighMultislotclass)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    /* ������Ϣ��ں��� */
    AT_ReadGasCapabilityNV();

    /* �����֤*/
    EXPECT_EQ(VOS_TRUE,g_stAtDlRateCategory.ucGasMultislotClass33Flg);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
TEST_F(Test_AT_ReadGasCapabilityNV, Test_AT_ReadGasCapabilityNV_003)
{
    NVIM_GAS_HIGH_MULTISLOT_CLASS_STRU          stHighMultislotclass;
    VOS_UINT16                                  usGprsMultiSlotClass;
    VOS_UINT16                                  usEgprsMultiSlotClass;
    VOS_UINT16                                  usEgprsFlag;

    usEgprsFlag                                     = VOS_FALSE;
    usGprsMultiSlotClass                            = AT_GAS_GRR_MULTISLOT_CLASS_MAX;
    usEgprsMultiSlotClass                           = AT_GAS_GRR_MULTISLOT_CLASS_MAX;
    stHighMultislotclass.usHighMultislotClassFlg    = VOS_TRUE;
    stHighMultislotclass.usHighMultislotClass       = AT_GAS_HIGH_MULTISLOT_CLASS_0;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(),eq((VOS_UINT16)en_NV_Item_Egprs_Flag),outBoundP((void *)&usEgprsFlag, (VOS_UINT32)sizeof(usEgprsFlag)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(),eq((VOS_UINT16)en_Nv_Item_Gprs_Multi_Slot_Class),outBoundP((void *)&usGprsMultiSlotClass, (VOS_UINT32)sizeof(usGprsMultiSlotClass)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(),eq((VOS_UINT16)en_NV_Item_Egprs_Multi_Slot_Class),outBoundP((void *)&usEgprsMultiSlotClass, (VOS_UINT32)sizeof(usEgprsMultiSlotClass)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(),eq((VOS_UINT16)en_NV_Item_GAS_High_Multislot_Class),outBoundP((void *)&stHighMultislotclass, (VOS_UINT32)sizeof(stHighMultislotclass)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    /* ������Ϣ��ں��� */
    AT_ReadGasCapabilityNV();

    /* �����֤*/
    EXPECT_EQ(VOS_TRUE,g_stAtDlRateCategory.ucGasMultislotClass33Flg);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_IPV6)
class Test_AT_ReadIpv6CapabilityNV: public ::testing::Test
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


TEST_F(Test_AT_ReadIpv6CapabilityNV, Test_AT_ReadIpv6CapabilityNV_001)
{
    // ��������
    AT_NV_IPV6_CAPABILITY_STRU          stNvIpv6Capability;

    // ������ʼ��
    stNvIpv6Capability.ucStatus = VOS_TRUE;
    stNvIpv6Capability.ucIpv6Capablity = AT_IPV6_CAPABILITY_IPV4V6_OVER_ONE_PDP;

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), any(), outBoundP((void *)&stNvIpv6Capability, (VOS_UINT32)sizeof(stNvIpv6Capability)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    // ���ñ��⺯��
    AT_ReadIpv6CapabilityNV();

    // ִ�м��
    EXPECT_EQ(AT_IPV6_CAPABILITY_IPV4V6_OVER_ONE_PDP, AT_GetCommPsCtxAddr()->ucIpv6Capability);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_AT_ReadIpv6BackProcExtCauseNV: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitCtx();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_ReadIpv6BackProcExtCauseNV, Test_AT_ReadIpv6BackProcExtCauseNV_001)
{
    TAF_NV_IPV6_FALLBACK_EXT_CAUSE_STRU  stNvBackProcExtCause;
    AT_COMM_PS_CTX_STRU                *pstCommPsCtx = VOS_NULL_PTR;

    pstCommPsCtx = AT_GetCommPsCtxAddr();

    memset(&stNvBackProcExtCause, 0x00, sizeof(TAF_NV_IPV6_FALLBACK_EXT_CAUSE_STRU));

    stNvBackProcExtCause.ulActiveFlag = VOS_TRUE;
    stNvBackProcExtCause.aucSmCause[0] = 8;
    stNvBackProcExtCause.aucSmCause[1] = 112    ;
    stNvBackProcExtCause.aucSmCause[2] = 7;
    stNvBackProcExtCause.aucSmCause[3] = 113;

    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(),
              eq((VOS_UINT16)en_NV_Item_IPV6_BACKPROC_EXT_CAUSE),
              outBoundP((void *)&stNvBackProcExtCause, sizeof(TAF_NV_IPV6_FALLBACK_EXT_CAUSE_STRU)) ,
              eq((VOS_UINT32)sizeof(TAF_NV_IPV6_FALLBACK_EXT_CAUSE_STRU)))
        .will(returnValue((VOS_UINT32)NV_OK));

    AT_ReadIpv6BackProcExtCauseNV();

    EXPECT_EQ(2, pstCommPsCtx->stIpv6BackProcExtCauseTbl.ulCauseNum);
    EXPECT_EQ(TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 8, pstCommPsCtx->stIpv6BackProcExtCauseTbl.aenPsCause[0]);
    EXPECT_EQ(TAF_PS_CAUSE_SM_NW_SECTION_BEGIN + 112, pstCommPsCtx->stIpv6BackProcExtCauseTbl.aenPsCause[1]);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_ReadIpv6BackProcExtCauseNV, Test_AT_ReadIpv6BackProcExtCauseNV_002)
{
    // ��������
    TAF_NV_IPV6_FALLBACK_EXT_CAUSE_STRU  stNvIpv6BackProcExtCause;
    AT_PS_IPV6_BACKPROC_EXT_CAUSE_STRU *pstPsIpv6BackProcExtCause;

    // ������ʼ��
    memset(&stNvIpv6BackProcExtCause, 0x00, sizeof(TAF_NV_IPV6_FALLBACK_EXT_CAUSE_STRU));
    stNvIpv6BackProcExtCause.ulActiveFlag   = VOS_TRUE;
    stNvIpv6BackProcExtCause.aucSmCause[2]  = 33;

    // ��ʼ��ȫ�ֱ���
    pstPsIpv6BackProcExtCause               = &(AT_GetCommPsCtxAddr()->stIpv6BackProcExtCauseTbl);

    // MOCKER����
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(),
              eq((VOS_UINT16)en_NV_Item_IPV6_BACKPROC_EXT_CAUSE),
              outBoundP((void *)&stNvIpv6BackProcExtCause, sizeof(TAF_NV_IPV6_FALLBACK_EXT_CAUSE_STRU)) ,
              eq((VOS_UINT32)sizeof(TAF_NV_IPV6_FALLBACK_EXT_CAUSE_STRU)))
        .will(returnValue((VOS_UINT32)NV_OK));

    // ���ñ��⺯��
    AT_ReadIpv6BackProcExtCauseNV();

    // ִ�м��
    EXPECT_EQ(pstPsIpv6BackProcExtCause->aenPsCause[0], TAF_PS_CONVERT_SM_CAUSE_TO_PS_CAUSE(stNvIpv6BackProcExtCause.aucSmCause[2]));
    GlobalMockObject::verify();
}
#endif


class Test_AT_ReadPppDialErrCodeNV: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(NV_GetLength)
            .stubs()
            .will(returnValue((VOS_UINT32)NV_OK));

    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_ReadPppDialErrCodeNV, Test_AT_ReadPppDialErrCodeNV_001)
{
    // ��������
    NAS_NV_PPP_DIAL_ERR_CODE_STRU       stPppErrRpt;

    // ������ʼ��
    stPppErrRpt.ucStatus         = VOS_TRUE;
    stPppErrRpt.ucErrCodeRpt     = PPP_DIAL_ERR_CODE_ENABLE;

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), any(), outBoundP((void *)&stPppErrRpt, (VOS_UINT32)sizeof(stPppErrRpt)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    // ���ñ��⺯��
    AT_ReadPppDialErrCodeNV();

    // ִ�м��
    EXPECT_EQ(PPP_DIAL_ERR_CODE_ENABLE, gucPppDialErrCodeRpt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_AT_ReadCregAndCgregCiFourByteRptNV: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        
        MOCKER(NV_GetLength)
            .stubs()
            .will(returnValue((VOS_UINT32)NV_OK));

    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_ReadCregAndCgregCiFourByteRptNV, Test_AT_ReadCregAndCgregCiFourByteRptNV_001)
{
    // ��������
    NAS_NV_CREG_CGREG_CI_FOUR_BYTE_RPT_STRU     stCiFourByteRpt;

    // ������ʼ��
    stCiFourByteRpt.ucStatus     = VOS_TRUE;
    stCiFourByteRpt.ucCiBytesRpt = CREG_CGREG_CI_RPT_FOUR_BYTE;

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), any(), outBoundP((void *)&stCiFourByteRpt, (VOS_UINT32)sizeof(stCiFourByteRpt)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    // ���ñ��⺯��
    AT_ReadCregAndCgregCiFourByteRptNV();

    // ִ�м��
    EXPECT_EQ(CREG_CGREG_CI_RPT_FOUR_BYTE, gucCiRptByte);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_AT_InitDeviceCmd: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

    }
    void TearDown()
    {
    }
protected:

};


TEST_F(Test_AT_InitDeviceCmd, Test_AT_InitDeviceCmd_001)
{
    // ��������
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           aucImei[TAF_PH_IMEI_LEN]     = {0x01, 0x02, 0x03, 0x04, 0x06};

    // ������ʼ��
    enModemId = MODEM_ID_0;

    // ���ȫ�ֱ�����ʼ��
    g_bAtDataLocked         = VOS_TRUE;

    // MOCKER����
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), eq((VOS_UINT16)en_NV_Item_IMEI), outBoundP((void *)&aucImei, TAF_PH_IMEI_LEN))
        .will(returnValue((VOS_UINT32)NV_OK));

    // ���ñ��⺯��
    AT_InitDeviceCmd();

    // ִ�м��
    EXPECT_EQ(VOS_TRUE, g_bAtDataLocked);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_InitDeviceCmd, Test_AT_InitDeviceCmd_002)
{
    // ��������
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           aucImei[TAF_PH_IMEI_LEN]     = {0};

    // ������ʼ��
    enModemId = MODEM_ID_0;

    // ���ȫ�ֱ�����ʼ��
    g_bAtDataLocked         = VOS_TRUE;

    // MOCKER����
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), eq((VOS_UINT16)en_NV_Item_IMEI), outBoundP((void *)&aucImei, TAF_PH_IMEI_LEN))
        .will(returnValue((VOS_UINT32)NV_OK));

    // ���ñ��⺯��
    AT_InitDeviceCmd();

    // ִ�м��
    EXPECT_EQ(VOS_FALSE, g_bAtDataLocked);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_AT_UsbSwitchGwMode: public ::testing::Test
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


TEST_F(Test_AT_UsbSwitchGwMode, Test_AT_UsbSwitchGwMode_001)
{
    // ��������

    // ������ʼ��

    // ���ȫ�ֱ�����ʼ��
    g_stAtAppPdpEntity.enIpv4v6State = AT_PDP_STATE_IDLE;
    g_stAtAppPdpEntity.enIpv4State = AT_PDP_STATE_DEACTING;

    // MOCKER����
    MOCKER(TAF_PS_CallEnd).expects(never());

    // ���ñ��⺯��
    AT_UsbSwitchGwMode();

    // ִ�м��

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_UsbSwitchGwMode, Test_AT_UsbSwitchGwMode_002)
{
    // ��������

    // ������ʼ��

    // ���ȫ�ֱ�����ʼ��
    g_stAtAppPdpEntity.enIpv4State = AT_PDP_STATE_ACTING;
    g_stAtAppPdpEntity.enIpv6State = AT_PDP_STATE_IDLE;
    g_stAtAppPdpEntity.enIpv4v6State = AT_PDP_STATE_IDLE;

    // MOCKER����
    MOCKER(TAF_PS_CallEnd)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    MOCKER(AT_AppSetPdpState)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)TAF_PDP_IPV4), eq((AT_PDP_STATE_ENUM_U8)AT_PDP_STATE_DEACTING));

    // ���ñ��⺯��
    AT_UsbSwitchGwMode();

    // ִ�м��

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_UsbSwitchGwMode, Test_AT_UsbSwitchGwMode_003)
{
    // ��������

    // ������ʼ��

    // ���ȫ�ֱ�����ʼ��
    g_stAtAppPdpEntity.enIpv4State = AT_PDP_STATE_IDLE;
    g_stAtAppPdpEntity.enIpv6State = AT_PDP_STATE_ACTING;
    g_stAtAppPdpEntity.enIpv4v6State = AT_PDP_STATE_IDLE;

    // MOCKER����
    MOCKER(TAF_PS_CallEnd)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    MOCKER(AT_AppSetPdpState)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)TAF_PDP_IPV6), eq((AT_PDP_STATE_ENUM_U8)AT_PDP_STATE_DEACTING));

    // ���ñ��⺯��
    AT_UsbSwitchGwMode();

    // ִ�м��

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_UsbSwitchGwMode, Test_AT_UsbSwitchGwMode_004)
{
    // ��������

    // ������ʼ��

    // ���ȫ�ֱ�����ʼ��
    g_stAtAppPdpEntity.enIpv4State = AT_PDP_STATE_IDLE;
    g_stAtAppPdpEntity.enIpv6State = AT_PDP_STATE_IDLE;
    g_stAtAppPdpEntity.enIpv4v6State = AT_PDP_STATE_ACTING;

    // MOCKER����
    MOCKER(TAF_PS_CallEnd)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    MOCKER(AT_AppSetPdpState)
        .expects(exactly(1))
        .with(eq((VOS_UINT8)TAF_PDP_IPV4V6), eq((AT_PDP_STATE_ENUM_U8)AT_PDP_STATE_DEACTING));

    // ���ñ��⺯��
    AT_UsbSwitchGwMode();

    // ִ�м��

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_AT_InitPort: public ::testing::Test
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


TEST_F(Test_AT_InitPort, Test_AT_InitPort_001)
{
    // ��������

    // ������ʼ��

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����
    MOCKER(BSP_USB_NASSwitchGatewayRegFunc)
        .stubs()
        .will(returnValue(VOS_ERROR));
    MOCKER(BSP_GetHsicEnumStatus)
        .stubs()
        .will(returnValue(VOS_FALSE));

    // ���ñ��⺯��
    AT_InitPort();

    // ִ�м��

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_InitPort, Test_AT_InitPort_002)
{
    // ��������

    // ������ʼ��

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����

    // ���ñ��⺯��
    AT_UsbEnableCB();
    AT_UsbDisableCB();
#if (FEATURE_ON == FEATURE_AT_HSIC)
    AT_HsicEnableCB();
    AT_HsicDisableCB();
#endif

    // ִ�м��

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_AT_InitPara: public ::testing::Test
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


TEST_F(Test_AT_InitPara, Test_AT_InitPara_001)
{
    // ��������
    MODEM_ID_ENUM_UINT16                enModemId;

    // ������ʼ��
    enModemId = MODEM_ID_0;

    // ���ȫ�ֱ�����ʼ��
    g_stAtCommCtx.ucSystemAppConfigAddr = SYSTEM_APP_WEBUI;

    // MOCKER����

    // ���ñ��⺯��
    AT_InitPara();

    // ִ�м��
    EXPECT_EQ(AT_COPS_NUMERIC_TYPE, g_astAtModemCtx[MODEM_ID_0].stNetCtx.ucCopsFormatType);
    EXPECT_EQ(AT_CMEE_ERROR_CODE, gucAtCmeeType);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_InitPara, Test_AT_InitPara_002)
{
    // ��������
    MODEM_ID_ENUM_UINT16                enModemId;

    // ������ʼ��
    enModemId = MODEM_ID_0;

    // ���ȫ�ֱ�����ʼ��
    g_stAtCommCtx.ucSystemAppConfigAddr = SYSTEM_APP_ANDROID;

    // MOCKER����

    // ���ñ��⺯��
    AT_InitPara();

    // ִ�м��
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        EXPECT_EQ(AT_COPS_LONG_ALPH_TYPE, g_astAtModemCtx[enModemId].stNetCtx.ucCopsFormatType);
    }
    EXPECT_EQ(AT_CMEE_ERROR_CONTENT, gucAtCmeeType);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_InitPara, Test_AT_InitPara_003)
{
    // ��������

    // ������ʼ��

    // ���ȫ�ֱ�����ʼ��
    g_stAtCommCtx.ucSystemAppConfigAddr = SYSTEM_APP_BUTT;

    // MOCKER����

    // ���ñ��⺯��
    AT_InitPara();

    // ִ�м��

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_At_PidInit: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(VOS_SmCCreate)
            .stubs()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(NV_ReadEx)
            .stubs()
            .will(returnValue((VOS_UINT32)NV_OK));
        
        MOCKER(NV_GetLength)
            .stubs()
            .will(returnValue((VOS_UINT32)NV_OK));
    }
    void TearDown()
    {
    }
protected:

};

#if (FEATURE_ON == FEATURE_E5)


TEST_F(Test_At_PidInit,AT_E5ComEst����ERROR)
{
    //��������
    enum VOS_INIT_PHASE_DEFINE enPhase;
    TAF_UINT32    ulResult;
    TAF_CCA_TELE_PARA_STRU              stTimeInfo;
    NVIM_AT_PRIVATE_CMD_STATUS_RPT_STRU stAtCmdRptCtrl;
    AT_NVIM_SEND_DOMAIN_STRU            stSendDomain;
    USSD_TRANS_MODE_STRU                stUssdTranMode;
    TAF_UINT8                           aucTmp[2];
    VOS_UINT16                          usReportCregActParaFlg;

    //������ʼ��
    enPhase = VOS_IP_INITIAL;

    stTimeInfo.ucS0TimerLen = 5;

    stAtCmdRptCtrl.ucStatus = VOS_TRUE;
    stAtCmdRptCtrl.ucAtStatusReportGeneralControl = 2;

    stSendDomain.ucActFlg = VOS_TRUE;

    stUssdTranMode.ucStatus = 0;
    stUssdTranMode.ucUssdTransMode = 2;

    aucTmp[0] = 2;

    usReportCregActParaFlg = VOS_TRUE;

    MOCKER(AT_E5ComEst)
        .stubs()
        .will(returnValue(VOS_ERR));

    //���ñ��⺯��
    ulResult = At_PidInit(enPhase);

    //ִ�м��
    EXPECT_EQ(NV_OK, ulResult);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
#endif


#if (FEATURE_ON == FEATURE_NDIS)

TEST_F(Test_At_PidInit,AT_UsbNdisEst����ERROR)
{
    //��������
    enum VOS_INIT_PHASE_DEFINE enPhase;
    TAF_UINT32    ulResult;
    TAF_CCA_TELE_PARA_STRU              stTimeInfo;
    NVIM_AT_PRIVATE_CMD_STATUS_RPT_STRU stAtCmdRptCtrl;
    AT_NVIM_SEND_DOMAIN_STRU            stSendDomain;
    USSD_TRANS_MODE_STRU                stUssdTranMode;
    TAF_UINT8                           aucTmp[2];
    VOS_UINT16                          usReportCregActParaFlg;

    //������ʼ��
    enPhase = VOS_IP_INITIAL;

    stTimeInfo.ucS0TimerLen = 5;

    stAtCmdRptCtrl.ucStatus = VOS_TRUE;
    stAtCmdRptCtrl.ucAtStatusReportGeneralControl = 2;

    stSendDomain.ucActFlg = VOS_TRUE;

    stUssdTranMode.ucStatus = 0;
    stUssdTranMode.ucUssdTransMode = 2;

    aucTmp[0] = 2;

    usReportCregActParaFlg = VOS_TRUE;

    MOCKER(AT_UsbNdisEst)
        .stubs()
        .will(returnValue(VOS_ERR));

    //���ñ��⺯��
    ulResult = At_PidInit(enPhase);

    //ִ�м��
    EXPECT_EQ(VOS_OK, ulResult);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
#endif

TEST_F(Test_At_PidInit,Test_At_PidInit_001)
{
    //��������
    enum VOS_INIT_PHASE_DEFINE enPhase;
    TAF_UINT32    ulResult;
    TAF_CCA_TELE_PARA_STRU              stTimeInfo;
    AT_NVIM_SEND_DOMAIN_STRU            stSendDomain;
    USSD_TRANS_MODE_STRU                stUssdTranMode;
    TAF_UINT8                           aucTmp[2];
    VOS_UINT16                          usReportCregActParaFlg;

    //������ʼ��
    enPhase = VOS_IP_INITIAL;

    stTimeInfo.ucS0TimerLen = 5;

    stSendDomain.ucActFlg = VOS_TRUE;

    stUssdTranMode.ucStatus = 1;
    stUssdTranMode.ucUssdTransMode = AT_USSD_NON_TRAN_MODE;

    aucTmp[0] = 1;

    usReportCregActParaFlg = VOS_TRUE;


    //���ȫ�ֱ�����ʼ��

    //���ñ��⺯��
    ulResult = At_PidInit(enPhase);

    //ִ�м��
    EXPECT_EQ(VOS_OK, ulResult);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}



TEST_F(Test_At_PidInit,Test_At_PidInit_002)
{
    //��������
    enum VOS_INIT_PHASE_DEFINE enPhase;
    TAF_UINT32    ulResult;
    AT_NVIM_SEND_DOMAIN_STRU            stSendDomain;
    USSD_TRANS_MODE_STRU                stUssdTranMode;
    TAF_UINT8                           aucTmp[2];
    VOS_UINT16                          usReportCregActParaFlg;

    //������ʼ��
    enPhase = VOS_IP_INITIAL;

    stSendDomain.ucActFlg = VOS_TRUE;

    stUssdTranMode.ucStatus = 1;
    stUssdTranMode.ucUssdTransMode = 2;

    aucTmp[0] = 2;

    usReportCregActParaFlg = VOS_TRUE;

    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    //���ñ��⺯��
    ulResult = At_PidInit(enPhase);

    //ִ�м��
    EXPECT_EQ(VOS_OK, ulResult);
    EXPECT_EQ(VOS_FALSE, AT_GetModemSmsCtxAddrFromClientId(0)->stCgsmsSendDomain.ucActFlg);
    EXPECT_EQ(AT_USSD_TRAN_MODE, AT_GetModemSsCtxAddrFromClientId(0)->usUssdTransMode);
    EXPECT_EQ(AT_ROAM_FEATURE_OFF, AT_GetModemNetCtxAddrFromClientId(0)->ucRoamFeature);
    EXPECT_EQ(VOS_FALSE, g_usReportCregActParaFlg);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}



TEST_F(Test_At_PidInit,Test_At_PidInit_003)
{
    //��������
    enum VOS_INIT_PHASE_DEFINE enPhase;
    TAF_UINT32    ulResult;
    TAF_CCA_TELE_PARA_STRU              stTimeInfo;
    AT_NVIM_SEND_DOMAIN_STRU            stSendDomain;
    USSD_TRANS_MODE_STRU                stUssdTranMode;
    TAF_UINT8                           aucTmp[2];
    VOS_UINT16                          usReportCregActParaFlg;

    //������ʼ��
    enPhase = VOS_IP_INITIAL;

    stTimeInfo.ucS0TimerLen = 5;

    stSendDomain.ucActFlg = VOS_TRUE;

    stUssdTranMode.ucStatus = 0;
    stUssdTranMode.ucUssdTransMode = 2;

    aucTmp[0] = 2;

    usReportCregActParaFlg = VOS_TRUE;


    //���ñ��⺯��
    ulResult = At_PidInit(enPhase);

    //ִ�м��
    EXPECT_EQ(VOS_OK, ulResult);


    //������ʱ����Ҫ����������λ�ü������
        GlobalMockObject::verify();
}


TEST_F(Test_At_PidInit,Test_At_PidInit_004)
{
    //��������
    enum VOS_INIT_PHASE_DEFINE          enPhase;
    TAF_UINT32                          ulResult;

    //������ʼ��
    enPhase = VOS_IP_BUTT;

    //MOCKER����
    MOCKER(AT_InitCtx).expects(never());

    //���ñ��⺯��
    ulResult = At_PidInit(enPhase);

    //ִ�м��
    EXPECT_EQ(VOS_OK, ulResult);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_AT_HSIC)

TEST_F(Test_At_PidInit, AT_HsicInit����ERROR)
{
    //��������
    enum VOS_INIT_PHASE_DEFINE enPhase;
    TAF_UINT32    ulResult;
    TAF_CCA_TELE_PARA_STRU              stTimeInfo;
    AT_NVIM_SEND_DOMAIN_STRU            stSendDomain;
    USSD_TRANS_MODE_STRU                stUssdTranMode;
    TAF_UINT8                           aucTmp[2];
    VOS_UINT16                          usReportCregActParaFlg;

    //������ʼ��
    enPhase = VOS_IP_INITIAL;

    stTimeInfo.ucS0TimerLen = 5;

    stSendDomain.ucActFlg = VOS_TRUE;

    stUssdTranMode.ucStatus = 0;
    stUssdTranMode.ucUssdTransMode = 2;

    aucTmp[0] = 2;

    usReportCregActParaFlg = VOS_TRUE;

    MOCKER(AT_HsicInit)
        .stubs()
        .will(returnValue(AT_FAILURE));

    //���ñ��⺯��
    ulResult = At_PidInit(enPhase);

    //ִ�м��
    EXPECT_EQ(VOS_OK, ulResult);


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
#endif


class Test_AT_ReadUartCfgNV: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitHsUartStats();
    }
    void TearDown()
    {
        AT_InitHsUartStats();
    }
};


TEST_F(Test_AT_ReadUartCfgNV, Test_AT_ReadUartCfgNV_001)
{
    // ��������

    // ������ʼ��

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    // ���ñ��⺯��
    AT_ReadUartCfgNV();

    // ִ�м��
    EXPECT_EQ(1, g_stAtStatsInfo.stHsUartStats.ucReadNvFailNum);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ReadUartCfgNV, Test_AT_ReadUartCfgNV_002)
{
    // ��������
    TAF_NV_UART_CFG_STRU                stUartNVCfg;
    AT_UART_CTX_STRU                   *pstUartCtx          = VOS_NULL_PTR;

    // ������ʼ��
    memset(&stUartNVCfg, 0x0,sizeof(stUartNVCfg));
    stUartNVCfg.ulBaudRate          = AT_UART_BAUDRATE_115200;
    stUartNVCfg.stFrame.ucFormat    = AT_UART_FORMAT_8DATA_1STOP;
    stUartNVCfg.stFrame.ucParity    = AT_UART_PARITY_SPACE;

    pstUartCtx = AT_GetUartCtxAddr();

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(),any(),outBoundP((void *)&stUartNVCfg, sizeof(stUartNVCfg)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    // ���ñ��⺯��
    AT_ReadUartCfgNV();

    // ִ�м��
    EXPECT_EQ(AT_UART_BAUDRATE_115200, pstUartCtx->stPhyConfig.enBaudRate);
    EXPECT_EQ(AT_UART_FORMAT_8DATA_1STOP, pstUartCtx->stPhyConfig.stFrame.enFormat);
    EXPECT_EQ(AT_UART_PARITY_SPACE, pstUartCtx->stPhyConfig.stFrame.enParity);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ReadUartCfgNV, Test_AT_ReadUartCfgNV_003)
{
    // ��������
    TAF_NV_UART_CFG_STRU                stUartNVCfg;
    AT_UART_CTX_STRU                   *pstUartCtx          = VOS_NULL_PTR;

    // ������ʼ��
    memset(&stUartNVCfg, 0x0,sizeof(stUartNVCfg));
    stUartNVCfg.ulBaudRate          = AT_UART_BAUDRATE_BUTT;
    stUartNVCfg.stFrame.ucFormat    = AT_UART_FORMAT_BUTT;
    stUartNVCfg.stFrame.ucParity    = AT_UART_PARITY_SPACE;

    pstUartCtx = AT_GetUartCtxAddr();

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(),any(),outBoundP((void *)&stUartNVCfg, sizeof(stUartNVCfg)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    // ���ñ��⺯��
    AT_ReadUartCfgNV();

    // ִ�м��
    EXPECT_EQ(AT_UART_BAUDRATE_115200, pstUartCtx->stPhyConfig.enBaudRate);
    EXPECT_EQ(AT_UART_FORMAT_8DATA_1STOP, pstUartCtx->stPhyConfig.stFrame.enFormat);
    EXPECT_EQ(AT_UART_PARITY_SPACE, pstUartCtx->stPhyConfig.stFrame.enParity);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_ReadUartCfgNV, Test_AT_ReadUartCfgNV_004)
{
    // ��������
    TAF_NV_UART_CFG_STRU                stUartNVCfg;
    AT_UART_CTX_STRU                   *pstUartCtx          = VOS_NULL_PTR;

    // ������ʼ��
    memset(&stUartNVCfg, 0x0,sizeof(stUartNVCfg));
    stUartNVCfg.ulBaudRate          = AT_UART_BAUDRATE_115200;
    stUartNVCfg.stFrame.ucFormat    = AT_UART_FORMAT_8DATA_1STOP;
    stUartNVCfg.stFrame.ucParity    = AT_UART_PARITY_BUTT;

    pstUartCtx = AT_GetUartCtxAddr();

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(),any(),outBoundP((void *)&stUartNVCfg, sizeof(stUartNVCfg)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    // ���ñ��⺯��
    AT_ReadUartCfgNV();

    // ִ�м��
    EXPECT_EQ(AT_UART_BAUDRATE_115200, pstUartCtx->stPhyConfig.enBaudRate);
    EXPECT_EQ(AT_UART_FORMAT_8DATA_1STOP, pstUartCtx->stPhyConfig.stFrame.enFormat);
    EXPECT_EQ(AT_UART_PARITY_SPACE, pstUartCtx->stPhyConfig.stFrame.enParity);

    GlobalMockObject::verify();
}


