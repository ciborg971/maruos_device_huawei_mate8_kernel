#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_AtCtx.h"

//�����������ã����������ùؼ���ʱ��Ҫ��ǰ׺ testing::
using namespace testing;

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#define    THIS_FILE_ID                 PS_FILE_ID_AT_CTX_C

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


class Test_AT_InitPlatformRatList: public ::testing::Test
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


TEST_F(Test_AT_InitPlatformRatList,Test_AT_InitPlatformRatList_001)
{
    //��������
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_CTX_STRU                  *pstAtModemCtx;
    VOS_UINT8                           ucPlatformSptGsm;
    VOS_UINT8                           ucPlatformSptWcdma;
    VOS_UINT8                           ucPlatformSptLte;

    // ������ʼ��
    ucPlatformSptGsm    = VOS_TRUE;
    ucPlatformSptWcdma  = VOS_FALSE;
    ucPlatformSptLte    = VOS_FALSE;

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����;

    // ���ñ��⺯��

    // ִ�м��
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstAtModemCtx = AT_GetModemCtxAddr(enModemId);

        //ִ�м��
        EXPECT_EQ(ucPlatformSptGsm, pstAtModemCtx->stPlatformRatList.ucPlatformSptGsm);
        EXPECT_EQ(ucPlatformSptWcdma, pstAtModemCtx->stPlatformRatList.ucPlatformSptWcdma);
        EXPECT_EQ(ucPlatformSptLte, pstAtModemCtx->stPlatformRatList.ucPlatformSptLte);
    }

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_AT_InitUsimStatus: public ::testing::Test
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


TEST_F(Test_AT_InitUsimStatus,Test_AT_InitUsimStatus_001)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_CTX_STRU                  *pstAtModemCtx;

    // ������ʼ��

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����;

    // ���ñ��⺯��

    // ִ�м��
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstAtModemCtx = AT_GetModemCtxAddr(enModemId);

        //ִ�м��
        EXPECT_EQ(USIMM_CARD_SERVIC_BUTT, pstAtModemCtx->stAtUsimInfoCtx.enCardStatus);
        EXPECT_EQ(USIMM_CARD_TYPE_BUTT, pstAtModemCtx->stAtUsimInfoCtx.enCardType);
    }

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_AT_InitModemSmsCtx: public ::testing::Test
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


TEST_F(Test_AT_InitModemSmsCtx, Test_AT_InitModemSmsCtx_001)
{
    // ��������
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_CTX_STRU                  *pstAtModemCtx;
    MN_MSG_VALID_PERIOD_ENUM_U8         enValidPeriod;                          /*TP Validity Period Format*/
    VOS_UINT8                           ucOtherTime;

    // ������ʼ��
    enValidPeriod   = MN_MSG_VALID_PERIOD_RELATIVE;
    ucOtherTime     = AT_CSMP_SUBMIT_VP_DEFAULT_VALUE;

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����;

    // ���ñ��⺯��

    // ִ�м��
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstAtModemCtx = AT_GetModemCtxAddr(enModemId);

        EXPECT_EQ(AT_CMGF_MSG_FORMAT_PDU, pstAtModemCtx->stSmsCtx.enCmgfMsgFormat);
        EXPECT_EQ(AT_CSDH_NOT_SHOW_TYPE, pstAtModemCtx->stSmsCtx.ucCsdhType);
        EXPECT_EQ(VOS_FALSE ,pstAtModemCtx->stSmsCtx.ucParaCmsr);
        EXPECT_EQ(VOS_FALSE ,pstAtModemCtx->stSmsCtx.ucSmsAutoReply);
        EXPECT_EQ(MN_MSG_CSMS_MSG_VERSION_PHASE2_PLUS ,pstAtModemCtx->stSmsCtx.enCsmsMsgVersion);
        EXPECT_EQ(MN_MSG_ME_STORAGE_DISABLE ,pstAtModemCtx->stSmsCtx.enMsgMeStorageStatus);
        EXPECT_EQ(AT_CNMI_MODE_BUFFER_TYPE ,pstAtModemCtx->stSmsCtx.stCnmiType.CnmiModeType);
        EXPECT_EQ(MN_MSG_SEND_DOMAIN_CS_PREFERRED ,pstAtModemCtx->stSmsCtx.stCgsmsSendDomain.enSendDomain);
        EXPECT_EQ(MN_MSG_MEM_STORE_SIM ,pstAtModemCtx->stSmsCtx.stCpmsInfo.enMemSendorWrite);
        EXPECT_EQ(MN_MSG_RCVMSG_ACT_STORE ,pstAtModemCtx->stSmsCtx.stCpmsInfo.stRcvPath.enRcvSmAct);
        EXPECT_EQ(enValidPeriod, pstAtModemCtx->stSmsCtx.stCscaCsmpInfo.stVp.enValidPeriod);
        EXPECT_EQ(ucOtherTime, pstAtModemCtx->stSmsCtx.stCscaCsmpInfo.stVp.u.ucOtherTime);
    }

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
class Test_AT_InitModemCcCtx: public ::testing::Test
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


TEST_F(Test_AT_InitModemCcCtx, Test_AT_InitModemCcCtx_001)
{
    // ��������
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;

    // ������ʼ��

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����;

    // ���ñ��⺯��

    // ִ�м��
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstCcCtx = AT_GetModemCcCtxAddrFromModemId(enModemId);

        EXPECT_EQ(VOS_FALSE, pstCcCtx->ulCurIsExistCallFlag);
        EXPECT_EQ(TAF_CS_CAUSE_SUCCESS, pstCcCtx->enCsErrCause);
    }

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

class Test_AT_InitModemSsCtx: public ::testing::Test
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


TEST_F(Test_AT_InitModemSsCtx, Test_AT_InitModemSsCtx_001)
{
    // ��������
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    // ������ʼ��

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����;

    // ���ñ��⺯��

    // ִ�м��
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstSsCtx = AT_GetModemSsCtxAddrFromModemId(enModemId);

        EXPECT_EQ(AT_USSD_TRAN_MODE ,pstSsCtx->usUssdTransMode);
        EXPECT_EQ(MN_CALL_MODE_SINGLE , pstSsCtx->enCModType);
        EXPECT_EQ(AT_SALS_DISABLE_TYPE , pstSsCtx->ucSalsType);
        EXPECT_EQ(AT_CLIP_DISABLE_TYPE , pstSsCtx->ucClipType);
        EXPECT_EQ(AT_CLIR_AS_SUBSCRIPT , pstSsCtx->ucClirType);
        EXPECT_EQ(AT_COLP_DISABLE_TYPE , pstSsCtx->ucColpType);
        EXPECT_EQ(AT_CRC_DISABLE_TYPE , pstSsCtx->ucCrcType);
        EXPECT_EQ(AT_CCWA_DISABLE_TYPE , pstSsCtx->ucCcwaType);

        EXPECT_EQ(MN_CALL_CSD_SPD_64K_MULTI , pstSsCtx->stCbstDataCfg.enSpeed);
        EXPECT_EQ(MN_CALL_CSD_NAME_SYNC_UDI , pstSsCtx->stCbstDataCfg.enName);
        EXPECT_EQ(MN_CALL_CSD_CE_T , pstSsCtx->stCbstDataCfg.enConnElem);
    }

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_AT_InitModemNetCtx: public ::testing::Test
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


TEST_F(Test_AT_InitModemNetCtx, Test_AT_InitModemNetCtx_001)
{
    // ��������
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    // ������ʼ��

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����;

    // ���ñ��⺯��

    // ִ�м��
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);

        EXPECT_EQ(AT_CERSSI_REPORT_TYPE_5DB_CHANGE_REPORT, pstNetCtx->ucCerssiReportType);
        EXPECT_EQ(AT_CREG_RESULT_CODE_NOT_REPORT_TYPE, pstNetCtx->ucCregType);
        EXPECT_EQ(AT_CGREG_RESULT_CODE_NOT_REPORT_TYPE, pstNetCtx->ucCgregType);

        EXPECT_EQ(AT_COPS_LONG_ALPH_TYPE, pstNetCtx->ucCopsFormatType);
        EXPECT_EQ(MN_PH_PREF_PLMN_UPLMN, pstNetCtx->enPrefPlmnType);
        EXPECT_EQ(AT_COPS_NUMERIC_TYPE, pstNetCtx->ucCpolFormatType);
        EXPECT_EQ(AT_ROAM_FEATURE_OFF, pstNetCtx->ucRoamFeature);
        EXPECT_EQ(0, pstNetCtx->ucSpnType);
        EXPECT_EQ(AT_CMD_ANTENNA_LEVEL_0, pstNetCtx->enCalculateAntennaLevel);

#if(FEATURE_ON == FEATURE_LTE)
        EXPECT_EQ(AT_CEREG_RESULT_CODE_NOT_REPORT_TYPE, pstNetCtx->ucCeregType);
#endif

    }

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_AT_InitModemAgpsCtx: public ::testing::Test
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


TEST_F(Test_AT_InitModemAgpsCtx, Test_AT_InitModemAgpsCtx_001)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MODEM_AGPS_CTX_STRU             *pstAgpsCtx;

    // ������ʼ��

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����;

    // ���ñ��⺯��

    // ִ�м��
    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstAgpsCtx = AT_GetModemAgpsCtxAddrFromModemId(enModemId);

        //ִ�м��
        EXPECT_EQ(AT_CPOSR_DISABLE, pstAgpsCtx->enCposrReport);
        EXPECT_EQ(AT_XCPOSR_DISABLE, pstAgpsCtx->enXcposrReport);
    }

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_AT_InitClientConfiguration: public ::testing::Test
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


TEST_F(Test_AT_InitClientConfiguration, Test_AT_InitClientConfiguration_001)
{
    //��������

    //������ʼ��

    //MOCKER����

    //���ñ��⺯��
    AT_InitClientConfiguration();

    //ִ�м��
    EXPECT_EQ(VOS_TRUE, g_astAtClientCtx[AT_CLIENT_TAB_APP1_INDEX].stClientConfiguration.ucReportFlg);
    EXPECT_EQ(MODEM_ID_0, g_astAtClientCtx[AT_CLIENT_TAB_APP1_INDEX].stClientConfiguration.enModemId);
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    EXPECT_EQ(VOS_TRUE, g_astAtClientCtx[AT_CLIENT_TAB_APP5_INDEX].stClientConfiguration.ucReportFlg);
    EXPECT_EQ(MODEM_ID_0, g_astAtClientCtx[AT_CLIENT_TAB_APP5_INDEX].stClientConfiguration.enModemId);
#endif
    EXPECT_EQ(VOS_TRUE, g_astAtClientCtx[AT_CLIENT_TAB_PCUI_INDEX].stClientConfiguration.ucReportFlg);
    EXPECT_EQ(MODEM_ID_0, g_astAtClientCtx[AT_CLIENT_TAB_PCUI_INDEX].stClientConfiguration.enModemId);
    EXPECT_EQ(VOS_TRUE, g_astAtClientCtx[AT_CLIENT_TAB_CTRL_INDEX].stClientConfiguration.ucReportFlg);
    EXPECT_EQ(MODEM_ID_0, g_astAtClientCtx[AT_CLIENT_TAB_CTRL_INDEX].stClientConfiguration.enModemId);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_AT_IsModemSupportRat: public ::testing::Test
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
        At_PidInit(VOS_IP_INITIAL);
    }
};


TEST(Test_AT_IsModemSupportRat,Test_AT_IsModemSupportRat_001)
{
    //��������
    MODEM_ID_ENUM_UINT16                enModemId;
	/* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enRat;
	/* Modified by h00313353 for Iteration 13, 2015-4-10, end */
    VOS_UINT8                           ucRst;

    //������ʼ��
    enModemId = MODEM_ID_0;
	/* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
    enRat = TAF_MMA_RAT_LTE;
	/* Modified by h00313353 for Iteration 13, 2015-4-10, end */

    //MOCKER����

    //���ñ��⺯��
    ucRst = AT_IsModemSupportRat(enModemId, enRat);

    //ִ�м��
    EXPECT_EQ(VOS_FALSE, ucRst);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST(Test_AT_IsModemSupportRat,Test_AT_IsModemSupportRat_002)
{
    //��������
    MODEM_ID_ENUM_UINT16                enModemId;
	/* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enRat;
	/* Modified by h00313353 for Iteration 13, 2015-4-10, end */
    VOS_UINT8                           ucRst;

    //������ʼ��
    enModemId = MODEM_ID_0;
	/* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
    enRat = TAF_MMA_RAT_WCDMA;
	/* Modified by h00313353 for Iteration 13, 2015-4-10, end */

    //MOCKER����

    //���ñ��⺯��
    ucRst = AT_IsModemSupportRat(enModemId, enRat);

    //ִ�м��
    EXPECT_EQ(VOS_FALSE, ucRst);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST(Test_AT_IsModemSupportRat,Test_AT_IsModemSupportRat_003)
{
    //��������
    MODEM_ID_ENUM_UINT16                enModemId;
	/* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enRat;
	/* Modified by h00313353 for Iteration 13, 2015-4-10, end */
    VOS_UINT8                           ucRst;

    //������ʼ��
    enModemId = MODEM_ID_0;
	/* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
    enRat = TAF_MMA_RAT_GSM;
	/* Modified by h00313353 for Iteration 13, 2015-4-10, end */

    //MOCKER����

    //���ñ��⺯��
    ucRst = AT_IsModemSupportRat(enModemId, enRat);

    //ִ�м��
    EXPECT_EQ(VOS_TRUE, ucRst);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST(Test_AT_IsModemSupportRat,Test_AT_IsModemSupportRat_004)
{
    //��������
    MODEM_ID_ENUM_UINT16                enModemId;
	/* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enRat;
	/* Modified by h00313353 for Iteration 13, 2015-4-10, end */
    VOS_UINT8                           ucRst;

    //������ʼ��
    enModemId = MODEM_ID_0;
	/* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
    enRat = TAF_MMA_RAT_BUTT;
	/* Modified by h00313353 for Iteration 13, 2015-4-10, end */

    //MOCKER����

    //���ñ��⺯��
    ucRst = AT_IsModemSupportRat(enModemId, enRat);

    //ִ�м��
    EXPECT_EQ(VOS_FALSE, ucRst);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_AT_GetModemIdFromClient: public ::testing::Test
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


TEST_F(Test_AT_GetModemIdFromClient, Test_AT_GetModemIdFromClient_001)
{
    //��������
    AT_CLIENT_TAB_INDEX_UINT8           enClientIndex;
    MODEM_ID_ENUM_UINT16                enModemId;
    UINT8                               ucRslt;

    //������ʼ��
    enClientIndex = AT_CLIENT_BUTT;
    enModemId = MODEM_ID_0;

    //MOCKER����

    //���ñ��⺯��
    ucRslt = AT_GetModemIdFromClient(enClientIndex, &enModemId);

    //ִ�м��
    EXPECT_EQ(VOS_ERR, ucRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_GetModemIdFromClient, Test_AT_GetModemIdFromClient_002)
{
    //��������
    AT_CLIENT_TAB_INDEX_UINT8           enClientIndex;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;
    UINT8                               ucRslt;

    //������ʼ��
    enClientIndex = AT_CLIENT_TAB_APP1_INDEX;
    enModemId = MODEM_ID_0;

    pstAtClientCtx = AT_GetClientCtxAddr(enClientIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_0;

    //MOCKER����

    //���ñ��⺯��
    ucRslt = AT_GetModemIdFromClient(enClientIndex, &enModemId);

    //ִ�м��
    EXPECT_EQ(MODEM_ID_0, enModemId);
    EXPECT_EQ(VOS_OK, ucRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_AT_GetModemIdFromClient, Test_AT_GetModemIdFromClient_003)
{
    //��������
    AT_CLIENT_TAB_INDEX_UINT8           enClientIndex;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;
    UINT8                               ucRslt;

    //������ʼ��
    enClientIndex = AT_CLIENT_TAB_APP5_INDEX;
    enModemId = MODEM_ID_0;

    pstAtClientCtx = AT_GetClientCtxAddr(enClientIndex);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_1;

    //MOCKER����

    //���ñ��⺯��
    ucRslt = AT_GetModemIdFromClient(enClientIndex, &enModemId);

    //ִ�м��
    EXPECT_EQ(MODEM_ID_1, enModemId);
    EXPECT_EQ(VOS_OK, ucRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
#endif


class Test_AT_GetDestPid: public ::testing::Test
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


TEST_F(Test_AT_GetDestPid, Test_AT_GetDestPid_001)
{
    //��������
    MN_CLIENT_ID_T                      usClientId;
    VOS_UINT32                          ulRcvPid;
    UINT8                               ucRslt;
    MODEM_ID_ENUM_UINT16                enModemId;

    //������ʼ��
    usClientId = AT_CLIENT_ID_APP;
    ulRcvPid = I0_WUEPS_PID_TAF;
    enModemId = MODEM_ID_0;

    //MOCKER����
    MOCKER(AT_GetModemIdFromClient)
        .stubs()
        .with(eq(usClientId), outBoundP(&enModemId))
        .will(returnValue((VOS_UINT32)VOS_OK));

    //���ñ��⺯��
    ucRslt = AT_GetDestPid(usClientId, ulRcvPid);

    //ִ�м��
    EXPECT_EQ(I0_WUEPS_PID_TAF, ucRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_AT_GetDestPid, Test_AT_GetDestPid_002)
{
    //��������
    MN_CLIENT_ID_T                      usClientId;
    VOS_UINT32                          ulRcvPid;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    //������ʼ��
    usClientId = AT_CLIENT_ID_APP;
    enModemId  = MODEM_ID_0;
    ulRcvPid   = I0_WUEPS_PID_TAF;

    pstAtClientCtx = AT_GetClientCtxAddr((AT_CLIENT_TAB_INDEX_UINT8)usClientId);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_0;

    //MOCKER����

    //���ñ��⺯��
    ulRslt = AT_GetDestPid(usClientId, ulRcvPid);

    //ִ�м��
    EXPECT_EQ(I0_WUEPS_PID_TAF, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_GetDestPid, Test_AT_GetDestPid_003)
{
    //��������
    MN_CLIENT_ID_T                      usClientId;
    VOS_UINT32                          ulRcvPid;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    //������ʼ��
    usClientId = AT_CLIENT_ID_APP5;
    enModemId  = MODEM_ID_0;
    ulRcvPid   = I0_WUEPS_PID_TAF;

    pstAtClientCtx = AT_GetClientCtxAddr((AT_CLIENT_TAB_INDEX_UINT8)usClientId);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_1;

    //MOCKER����

    //���ñ��⺯��
    ulRslt = AT_GetDestPid(usClientId, ulRcvPid);

    //ִ�м��
    EXPECT_EQ(I1_WUEPS_PID_TAF, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_GetDestPid, Test_AT_GetDestPid_004)
{
    //��������
    VOS_UINT32                          i;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRcvPid;
    MN_CLIENT_ID_T                      usClientId;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    //������ʼ��
    i = 0;
    ulRcvPid   = I0_WUEPS_PID_SS;
    enModemId  = MODEM_ID_0;
    usClientId = AT_CLIENT_ID_APP6;

    pstAtClientCtx = AT_GetClientCtxAddr((AT_CLIENT_TAB_INDEX_UINT8)usClientId);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_1;

    //MOCKER����

    //���ñ��⺯��
    ulRslt = AT_GetDestPid(usClientId, ulRcvPid);

    //ִ�м��
    EXPECT_EQ(I1_WUEPS_PID_SS, ulRslt);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

#endif


class Test_AT_GetSsCustomizePara: public ::testing::Test
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


TEST_F(Test_AT_GetSsCustomizePara, Test_AT_GetSsCustomizePara_001)
{
    // ��������
    VOS_UINT32                          ulRet;

    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    g_stAtSsCustomizePara.ucStatus  = VOS_FALSE;

    // MOCKER����

    // ���ñ��⺯��
    ulRet = AT_GetSsCustomizePara(AT_SS_CUSTOMIZE_CCWA_QUERY);

    // ִ�м��
    EXPECT_EQ(VOS_FALSE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_GetSsCustomizePara, Test_AT_GetSsCustomizePara_002)
{
    // ��������
    VOS_UINT32                          ulRet;

    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    g_stAtSsCustomizePara.ucStatus          = VOS_TRUE;
    g_stAtSsCustomizePara.ucSsCmdCustomize  = 0x01;

    // MOCKER����

    // ���ñ��⺯��
    ulRet = AT_GetSsCustomizePara(AT_SS_CUSTOMIZE_CCWA_QUERY);

    // ִ�м��
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_GetSsCustomizePara, Test_AT_GetSsCustomizePara_003)
{
    // ��������
    VOS_UINT32                          ulRet;

    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    g_stAtSsCustomizePara.ucStatus          = VOS_TRUE;
    g_stAtSsCustomizePara.ucSsCmdCustomize  = 0x10;

    // MOCKER����

    // ���ñ��⺯��
    ulRet = AT_GetSsCustomizePara(AT_SS_CUSTOMIZE_CCWA_QUERY);

    // ִ�м��
    EXPECT_EQ(VOS_FALSE, ulRet);

    GlobalMockObject::verify();
}


class Test_AT_InitResetCtx: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        g_stAtStatsInfo.stCCpuResetStatsInfo.ulCreateBinarySemFailNum = 0;
    }
    void TearDown()
    {
        g_stAtStatsInfo.stCCpuResetStatsInfo.ulCreateBinarySemFailNum = 0;
    }
};


TEST_F(Test_AT_InitResetCtx, Test_AT_InitResetCtx_001)
{
    //��������

    //������ʼ��

    //MOCKER����
    MOCKER(VOS_SmBCreate)
        .stubs()
        .will(returnValue(VOS_ERR));

    //���ñ��⺯��
    AT_InitResetCtx();

    //ִ�м��
    EXPECT_EQ(VOS_FALSE, g_stAtStatsInfo.stCCpuResetStatsInfo.ulSemInitFlg);
    EXPECT_EQ(1, g_stAtStatsInfo.stCCpuResetStatsInfo.ulCreateBinarySemFailNum);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_AT_PORT_BUFF_CFG: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        AT_InitPortBuffCfg();
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_PORT_BUFF_CFG, Test_AT_PORT_BUFF_CFG_001)
{
    AT_COMM_CTX_STRU                   *pstCommCtx = VOS_NULL_PTR;
    TAF_NV_PORT_BUFF_CFG_STRU           stSmsBuffCfg;

    stSmsBuffCfg.ucEnableFlg = AT_PORT_BUFF_BUTT;
    pstCommCtx = AT_GetCommCtxAddr();

    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(),any(),outBoundP((void *)&stSmsBuffCfg),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    AT_ReadPortBuffCfgNV();

    EXPECT_EQ(AT_PORT_BUFF_DISABLE,pstCommCtx->stPortBuffCfg.enSmsBuffCfg);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PORT_BUFF_CFG, Test_AT_PORT_BUFF_CFG_002)
{
    AT_COMM_CTX_STRU                   *pstCommCtx = VOS_NULL_PTR;
    TAF_NV_PORT_BUFF_CFG_STRU           stSmsBuffCfg;

    PS_MEM_SET(&stSmsBuffCfg, 0, sizeof(TAF_NV_PORT_BUFF_CFG_STRU));

    stSmsBuffCfg.ucEnableFlg = AT_PORT_BUFF_ENABLE;
    pstCommCtx = AT_GetCommCtxAddr();

    MOCKER(NV_ReadEx)
        .stubs()
        .with(eq((MODEM_ID_ENUM_UINT16)MODEM_ID_0), eq((VOS_UINT16)en_NV_Item_PORT_BUFF_CFG), outBoundP((void *)&stSmsBuffCfg), eq((VOS_UINT32)sizeof(stSmsBuffCfg)))
        .will(returnValue((VOS_UINT32)NV_OK));

    AT_ReadPortBuffCfgNV();

    EXPECT_EQ(AT_PORT_BUFF_ENABLE, pstCommCtx->stPortBuffCfg.enSmsBuffCfg);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PORT_BUFF_CFG, Test_AT_PORT_BUFF_CFG_003)
{
    AT_COMM_CTX_STRU                   *pstCommCtx = VOS_NULL_PTR;

    pstCommCtx = AT_GetCommCtxAddr();

    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    AT_ReadPortBuffCfgNV();

    EXPECT_EQ(AT_PORT_BUFF_DISABLE,pstCommCtx->stPortBuffCfg.enSmsBuffCfg);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PORT_BUFF_CFG, Test_AT_PORT_BUFF_CFG_004)
{
    AT_COMM_CTX_STRU                   *pstCommCtx = VOS_NULL_PTR;
    TAF_NV_PORT_BUFF_CFG_STRU           stSmsBuffCfg;

    stSmsBuffCfg.ucEnableFlg = AT_PORT_BUFF_ENABLE;
    pstCommCtx = AT_GetCommCtxAddr();

    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(),any(),outBoundP((void *)&stSmsBuffCfg),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    AT_ReadPortBuffCfgNV();
    EXPECT_EQ(AT_PORT_BUFF_ENABLE, AT_GetPortBuffCfg());

    EXPECT_EQ(AT_PORT_BUFF_ENABLE,pstCommCtx->stPortBuffCfg.enSmsBuffCfg);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PORT_BUFF_CFG, Test_AT_PORT_BUFF_CFG_005)
{
    VOS_UINT16                      usClientId;

    usClientId = AT_MAX_CLIENT_NUM;

    AT_AddUsedClientId2Tab(usClientId);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PORT_BUFF_CFG, Test_AT_PORT_BUFF_CFG_006)
{
    VOS_UINT16                      usClientId;

    usClientId = AT_CLIENT_ID_APP;

    AT_AddUsedClientId2Tab(usClientId);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PORT_BUFF_CFG, Test_AT_PORT_BUFF_CFG_007)
{
    VOS_UINT16                      usClientId;

    usClientId = AT_MAX_APP_CLIENT_ID;

    AT_AddUsedClientId2Tab(usClientId);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PORT_BUFF_CFG, Test_AT_PORT_BUFF_CFG_008)
{
    VOS_UINT16                          usClientId;
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg = VOS_NULL_PTR;

    usClientId = AT_CLIENT_ID_PCUI;
    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    pstPortBuffCfg->ucNum = AT_MAX_CLIENT_NUM + 1;

    AT_AddUsedClientId2Tab(usClientId);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PORT_BUFF_CFG, Test_AT_PORT_BUFF_CFG_009)
{
    VOS_UINT16                          usClientId;
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg = VOS_NULL_PTR;

    usClientId = AT_CLIENT_ID_PCUI;
    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    pstPortBuffCfg->ucNum = 1;
    pstPortBuffCfg->ulUsedClientID[0] = AT_CLIENT_ID_PCUI;

    AT_AddUsedClientId2Tab(usClientId);

    EXPECT_EQ(1, pstPortBuffCfg->ucNum);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PORT_BUFF_CFG, Test_AT_PORT_BUFF_CFG_010)
{
    VOS_UINT16                          usClientId;
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg = VOS_NULL_PTR;

    usClientId = AT_CLIENT_ID_CTRL;
    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    pstPortBuffCfg->ucNum = 1;
    pstPortBuffCfg->ulUsedClientID[0] = AT_CLIENT_ID_PCUI;

    AT_AddUsedClientId2Tab(usClientId);

    EXPECT_EQ(2, pstPortBuffCfg->ucNum);
    EXPECT_EQ(AT_CLIENT_ID_CTRL, pstPortBuffCfg->ulUsedClientID[1]);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PORT_BUFF_CFG, Test_AT_PORT_BUFF_CFG_011)
{
    VOS_UINT16                          usClientId;
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg = VOS_NULL_PTR;

    usClientId = AT_CLIENT_ID_CTRL;
    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    pstPortBuffCfg->ucNum = AT_MAX_CLIENT_NUM + 1;
    pstPortBuffCfg->ulUsedClientID[0] = AT_CLIENT_ID_PCUI;

    AT_RmUsedClientIdFromTab(usClientId);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PORT_BUFF_CFG, Test_AT_PORT_BUFF_CFG_012)
{
    VOS_UINT16                          usClientId;
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg = VOS_NULL_PTR;

    usClientId = AT_CLIENT_ID_PCUI;
    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    pstPortBuffCfg->ucNum = 1;
    pstPortBuffCfg->ulUsedClientID[0] = AT_CLIENT_ID_PCUI;

    AT_RmUsedClientIdFromTab(usClientId);

    EXPECT_EQ(0,pstPortBuffCfg->ucNum);
    EXPECT_EQ(0xFFFFFFFF,pstPortBuffCfg->ulUsedClientID[0]);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PORT_BUFF_CFG, Test_AT_PORT_BUFF_CFG_013)
{
    VOS_UINT16                          usClientId;
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg = VOS_NULL_PTR;

    usClientId = AT_CLIENT_ID_CTRL;
    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    pstPortBuffCfg->ucNum = 1;
    pstPortBuffCfg->ulUsedClientID[0] = AT_CLIENT_ID_PCUI;

    AT_RmUsedClientIdFromTab(usClientId);

    EXPECT_EQ(1,pstPortBuffCfg->ucNum);
    EXPECT_EQ(AT_CLIENT_ID_PCUI,pstPortBuffCfg->ulUsedClientID[0]);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_PORT_BUFF_CFG, Test_AT_PORT_BUFF_CFG_014)
{
    VOS_UINT16                          usClientId;
    AT_PORT_BUFF_CFG_STRU              *pstPortBuffCfg = VOS_NULL_PTR;

    usClientId = AT_CLIENT_ID_CTRL;
    pstPortBuffCfg = AT_GetPortBuffCfgInfo();

    pstPortBuffCfg->ucNum = 1;
    pstPortBuffCfg->ulUsedClientID[0] = AT_CLIENT_ID_PCUI;

    for (usClientId = 0; usClientId < AT_MAX_CLIENT_NUM; usClientId++)
    {
        AT_AddUsedClientId2Tab(usClientId);
    }

    EXPECT_EQ(AT_CLIENT_ID_PCUI,pstPortBuffCfg->ulUsedClientID[0]);
    EXPECT_EQ(AT_CLIENT_ID_CTRL,pstPortBuffCfg->ulUsedClientID[1]);
    EXPECT_EQ(AT_CLIENT_ID_MODEM,pstPortBuffCfg->ulUsedClientID[2]);
    EXPECT_EQ(AT_CLIENT_ID_NDIS,pstPortBuffCfg->ulUsedClientID[3]);
    EXPECT_EQ(AT_CLIENT_ID_UART,pstPortBuffCfg->ulUsedClientID[4]);

    for (usClientId = 0; usClientId < AT_MAX_CLIENT_NUM; usClientId++)
    {
        AT_RmUsedClientIdFromTab(usClientId);
    }

    EXPECT_EQ(0,pstPortBuffCfg->ucNum);
    EXPECT_EQ(0xFFFFFFFF,pstPortBuffCfg->ulUsedClientID[0]);

    GlobalMockObject::verify();
}
