#include "gtest/gtest.h"
#include "llt_mockcpp.h"


#include "uttest_AtDeviceCmd.h"
//�����������ã����������ùؼ���ʱ��Ҫ��ǰ׺ testing::
using namespace testing;

#define    THIS_FILE_ID                 PS_FILE_ID_AT_DEVICECMD_C

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


AT_PAR_CMD_ELEMENT_STRU             gstHssptCmdInfo = {AT_CMD_HSSPT,
    AT_SetHsspt  ,       AT_NOT_SET_TIME,    AT_QryHsspt,         AT_NOT_SET_TIME,   VOS_NULL_PTR ,    AT_NOT_SET_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS,    CMD_TBL_PIN_IS_LOCKED,
    (VOS_UINT8*)"^HSSPT",    (VOS_UINT8*)"(0,1,2,6)"};




class Test_AT_SetHsspt: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        g_stParseContext[0].pstCmdElement = &gstHssptCmdInfo;
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_SetHsspt, Test_AT_SetHsspt_001)
{
    /*��������*/
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_BUTT;

    /*������׮*/

    /*���ñ��⺯�� */
    ulRet = AT_SetHsspt(0);

    /* �����֤*/
    EXPECT_EQ(AT_DPAUPA_ERROR, ulRet);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_SetHsspt, Test_AT_SetHsspt_002)
{
    /*��������*/
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;

    gucAtParaIndex = 2;

    /*������׮*/

    /*���ñ��⺯�� */
    ulRet = AT_SetHsspt(0);

    /* �����֤*/
    EXPECT_EQ(AT_DPAUPA_ERROR, ulRet);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_SetHsspt, Test_AT_SetHsspt_003)
{
    /*��������*/
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;

    gucAtParaIndex = 1;

    g_bAtDataLocked = VOS_TRUE;

    /*������׮*/

    /*���ñ��⺯�� */
    ulRet = AT_SetHsspt(0);

    /* �����֤*/
    EXPECT_EQ(AT_DATA_UNLOCK_ERROR, ulRet);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_SetHsspt, Test_AT_SetHsspt_004)
{
    /*��������*/
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;

    gucAtParaIndex = 1;

    g_bAtDataLocked = VOS_FALSE;

    gastAtParaList[0].ulParaValue = 0;

    /*������׮*/
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_WriteEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    /*���ñ��⺯�� */
    ulRet = AT_SetHsspt(0);

    /* �����֤*/
    EXPECT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_SetHsspt, Test_AT_SetHsspt_005)
{
    /*��������*/
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;

    gucAtParaIndex = 1;

    g_bAtDataLocked = VOS_FALSE;

    gastAtParaList[0].ulParaValue = 1;

    /*������׮*/
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_WriteEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    /*���ñ��⺯�� */
    ulRet = AT_SetHsspt(0);

    /* �����֤*/
    EXPECT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_SetHsspt, Test_AT_SetHsspt_006)
{
    /*��������*/
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;

    gucAtParaIndex = 1;

    g_bAtDataLocked = VOS_FALSE;

    gastAtParaList[0].ulParaValue = 2;

    /*������׮*/
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_WriteEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    /*���ñ��⺯�� */
    ulRet = AT_SetHsspt(0);

    /* �����֤*/
    EXPECT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_SetHsspt, Test_AT_SetHsspt_007)
{
    /*��������*/
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;

    gucAtParaIndex = 1;

    g_bAtDataLocked = VOS_FALSE;

    gastAtParaList[0].ulParaValue = 2;

    /*������׮*/
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_WriteEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    /*���ñ��⺯�� */
    ulRet = AT_SetHsspt(0);

    /* �����֤*/
    EXPECT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();
}
class Test_AT_QryHsspt: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        g_stParseContext[0].pstCmdElement = &gstHssptCmdInfo;
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_QryHsspt, Test_AT_QryHsspt_001)
{
    /*��������*/
    VOS_UINT32                          ulRet;
    AT_NVIM_UE_CAPA_STRU                stUECapa;
    VOS_CHAR                           *pcExpactedStr = "^HSSPT:0";

    /*���ر�����ʼ��*/
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    stUECapa.ulHspaStatus = VOS_TRUE;
    stUECapa.enEDCHSupport    = VOS_FALSE;
    stUECapa.enHSDSCHSupport  = VOS_FALSE;

    /*������׮*/
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_WAS_RadioAccess_Capa_New), outBoundP((void *)&stUECapa, sizeof(stUECapa)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    /*���ñ��⺯�� */
    ulRet = AT_QryHsspt(0);

    /* �����֤*/
    EXPECT_EQ(AT_OK, ulRet);

    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_QryHsspt, Test_AT_QryHsspt_002)
{
    /*��������*/
    VOS_UINT32                          ulRet;
    AT_NVIM_UE_CAPA_STRU                stUECapa;
    VOS_CHAR                           *pcExpactedStr = "^HSSPT:1";

    /*���ر�����ʼ��*/
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    stUECapa.ulHspaStatus = VOS_TRUE;
    stUECapa.enEDCHSupport    = VOS_FALSE;
    stUECapa.enHSDSCHSupport  = VOS_TRUE;

    /*������׮*/
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_WAS_RadioAccess_Capa_New), outBoundP((void *)&stUECapa, sizeof(stUECapa)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    /*���ñ��⺯�� */
    ulRet = AT_QryHsspt(0);

    /* �����֤*/
    EXPECT_EQ(AT_OK, ulRet);

    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_QryHsspt, Test_AT_QryHsspt_003)
{
    /*��������*/
    VOS_UINT32                          ulRet;
    AT_NVIM_UE_CAPA_STRU                stUECapa;
    VOS_CHAR                           *pcExpactedStr = "^HSSPT:2";

    /*���ر�����ʼ��*/
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    stUECapa.ulHspaStatus = VOS_TRUE;
    stUECapa.enAsRelIndicator = AT_PTL_VER_ENUM_R6;
    stUECapa.enEDCHSupport    = VOS_TRUE;
    stUECapa.enHSDSCHSupport  = VOS_TRUE;

    /*������׮*/
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_WAS_RadioAccess_Capa_New), outBoundP((void *)&stUECapa, sizeof(stUECapa)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    /*���ñ��⺯�� */
    ulRet = AT_QryHsspt(0);

    /* �����֤*/
    EXPECT_EQ(AT_OK, ulRet);

    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_QryHsspt, Test_AT_QryHsspt_004)
{
    /*��������*/
    VOS_UINT32                          ulRet;
    AT_NVIM_UE_CAPA_STRU                stUECapa;
    VOS_CHAR                           *pcExpactedStr = "^HSSPT:6";

    /*���ر�����ʼ��*/
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;

    stUECapa.ulHspaStatus = VOS_TRUE;
    stUECapa.enAsRelIndicator = AT_PTL_VER_ENUM_R7;
    stUECapa.enEDCHSupport    = VOS_TRUE;
    stUECapa.enHSDSCHSupport  = VOS_TRUE;

    /*������׮*/
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_WAS_RadioAccess_Capa_New), outBoundP((void *)&stUECapa, sizeof(stUECapa)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    /*���ñ��⺯�� */
    ulRet = AT_QryHsspt(0);

    /* �����֤*/
    EXPECT_EQ(AT_OK, ulRet);

    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}
class Test_AT_ExistSpecificPort: public ::testing::Test
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


TEST_F(Test_AT_ExistSpecificPort, Test_AT_ExistSpecificPort_001)
{
    /*��������*/
    AT_DYNAMIC_PID_TYPE_STRU            stStubDynamicPidType;
    VOS_UINT8                           ucPortType = AT_DEV_DIAG;
    VOS_UINT8   aucFirstPortStyle[]     = {0xA1, 0XA2};   /* �豸�л�ǰ�˿���̬ */
    VOS_UINT8   aucRewindPortStyle[]    = {0x10,0x05,0x16,0x13,0x12, 0x0A,0x03,0x14,0x15, 0xA1,0xA2, 0x00};  /* �豸�л���˿���̬ */
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/

    /*������׮*/
    PS_MEM_SET(&stStubDynamicPidType, 0X00, sizeof(stStubDynamicPidType));
    PS_MEM_CPY(stStubDynamicPidType.aucFirstPortStyle, aucFirstPortStyle, sizeof(aucFirstPortStyle));
    PS_MEM_CPY(stStubDynamicPidType.aucRewindPortStyle, aucRewindPortStyle, sizeof(aucRewindPortStyle));
    stStubDynamicPidType.ulNvStatus = VOS_TRUE;
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), eq((VOS_UINT16)en_NV_Item_Huawei_Dynamic_PID_Type), outBoundP((void *)&stStubDynamicPidType, sizeof(stStubDynamicPidType)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    /*���ñ��⺯�� */
    ulRet = AT_ExistSpecificPort(ucPortType);

    /* �����֤*/
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_ExistSpecificPort, Test_AT_ExistSpecificPort_002)
{
    /*��������*/
    AT_DYNAMIC_PID_TYPE_STRU            stStubDynamicPidType;
    VOS_UINT8                           ucPortType = AT_DEV_DIAG;
    VOS_UINT8   aucFirstPortStyle[]     = {0xA1, 0XA2};   /* �豸�л�ǰ�˿���̬ */
    VOS_UINT8   aucRewindPortStyle[]    = {0x10,0x05,0x16,0x13,0x12, 0x0A,0x14,0x15, 0xA1,0xA2, 0x00};  /* �豸�л���˿���̬ */
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/

    /*������׮*/
    PS_MEM_SET(&stStubDynamicPidType, 0X00, sizeof(stStubDynamicPidType));
    PS_MEM_CPY(stStubDynamicPidType.aucFirstPortStyle, aucFirstPortStyle, sizeof(aucFirstPortStyle));
    PS_MEM_CPY(stStubDynamicPidType.aucRewindPortStyle, aucRewindPortStyle, sizeof(aucRewindPortStyle));
    stStubDynamicPidType.ulNvStatus = VOS_TRUE;
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Huawei_Dynamic_PID_Type), outBoundP((void *)&stStubDynamicPidType, sizeof(stStubDynamicPidType)),any())
        .will(returnValue((VOS_UINT32)NV_OK));

    /*���ñ��⺯�� */
    ulRet = AT_ExistSpecificPort(ucPortType);

    /* �����֤*/
    EXPECT_EQ(VOS_FALSE, ulRet);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_ExistSpecificPort, Test_AT_ExistSpecificPort_003)
{
    /*��������*/
    AT_DYNAMIC_PID_TYPE_STRU            stStubDynamicPidType;
    VOS_UINT8                           ucPortType = AT_DEV_DIAG;
    VOS_UINT8   aucFirstPortStyle[]     = {0xA1, 0XA2};   /* �豸�л�ǰ�˿���̬ */
    VOS_UINT8   aucRewindPortStyle[]    = {0x10,0x05,0x16,0x13,0x12, 0x0A,0x14,0x15, 0xA1,0xA2, 0x00};  /* �豸�л���˿���̬ */
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/

    /*������׮*/
    PS_MEM_SET(&stStubDynamicPidType, 0X00, sizeof(stStubDynamicPidType));
    PS_MEM_CPY(stStubDynamicPidType.aucFirstPortStyle, aucFirstPortStyle, sizeof(aucFirstPortStyle));
    PS_MEM_CPY(stStubDynamicPidType.aucRewindPortStyle, aucRewindPortStyle, sizeof(aucRewindPortStyle));
    stStubDynamicPidType.ulNvStatus = VOS_TRUE;
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Huawei_Dynamic_PID_Type), outBoundP((void *)&stStubDynamicPidType, sizeof(stStubDynamicPidType)),any())
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    /*���ñ��⺯�� */
    ulRet = AT_ExistSpecificPort(ucPortType);

    /* �����֤*/
    EXPECT_EQ(VOS_FALSE, ulRet);

    GlobalMockObject::verify();
}
class Test_AT_ExistSpecificPortChange: public ::testing::Test
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


TEST_F(Test_AT_ExistSpecificPortChange, AT_ExistSpecificPortChange_001)
{
    /*��������*/
    VOS_UINT8                           ucPortType = AT_DEV_DIAG;
    VOS_UINT8                           aucOldRewindPortStyle[AT_SETPORT_PARA_MAX_LEN] = {0};
    VOS_UINT8                           aucNewRewindPortStyle[AT_SETPORT_PARA_MAX_LEN] = {0};
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/
    g_enATE5RightFlag = AT_E5_RIGHT_FLAG_YES;

    aucOldRewindPortStyle[0] = AT_DEV_DIAG;
    aucOldRewindPortStyle[1] = AT_DEV_PCUI;
    aucNewRewindPortStyle[0] = AT_DEV_PCUI;

    /*������׮*/

    /*���ñ��⺯�� */
    ulRet = AT_ExistSpecificPortChange(ucPortType, aucOldRewindPortStyle, aucNewRewindPortStyle);

    /* �����֤*/
    EXPECT_EQ(VOS_TRUE, ulRet);

    GlobalMockObject::verify();
}
class Test_AT_CloseDiagPort: public ::testing::Test
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


TEST_F(Test_AT_CloseDiagPort, Test_AT_CloseDiagPort_001)
{
    /*��������*/
    AT_DYNAMIC_PID_TYPE_STRU            stDynamicPidType;
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/
    g_enATE5RightFlag = AT_E5_RIGHT_FLAG_YES;

    stDynamicPidType.ulNvStatus = VOS_TRUE;
    stDynamicPidType.aucRewindPortStyle[0] = AT_DEV_DIAG;
    stDynamicPidType.aucRewindPortStyle[1] = AT_DEV_CDROM;

    /*������׮*/
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Huawei_Dynamic_PID_Type), outBoundP((void *)&stDynamicPidType, sizeof(stDynamicPidType)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_WriteEx)
        .expects(never());

    /*���ñ��⺯�� */
    ulRet = AT_CloseDiagPort();

    /* �����֤*/
    EXPECT_EQ(AT_OK, ulRet);
    GlobalMockObject::verify();
}
class Test_AT_OpenDiagPort: public ::testing::Test
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


TEST_F(Test_AT_OpenDiagPort, Test_AT_OpenDiagPort_001)
{
    /*��������*/
    AT_DYNAMIC_PID_TYPE_STRU            stDynamicPidType;
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/
    g_enATE5RightFlag = AT_E5_RIGHT_FLAG_NO;

    stDynamicPidType.ulNvStatus = VOS_TRUE;
    stDynamicPidType.aucRewindPortStyle[0] = AT_DEV_PCUI;
    stDynamicPidType.aucRewindPortStyle[1] = AT_DEV_CDROM;

    /*������׮*/
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Huawei_Dynamic_PID_Type), outBoundP((void *)&stDynamicPidType, sizeof(stDynamicPidType)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_WriteEx)
        .expects(never());

    /*���ñ��⺯�� */
    ulRet = AT_OpenDiagPort();

    /* �����֤*/
    EXPECT_EQ(AT_OK, ulRet);
    GlobalMockObject::verify();
}
TEST_F(Test_AT_CloseDiagPort, Test_AT_CloseDiagPort_002)
{
    /*��������*/
    AT_DYNAMIC_PID_TYPE_STRU            stDynamicPidType;
    VOS_UINT32                          ulRet;

    /*���ر�����ʼ��*/
    g_enATE5RightFlag = AT_E5_RIGHT_FLAG_YES;

    stDynamicPidType.ulNvStatus = VOS_TRUE;
    stDynamicPidType.aucRewindPortStyle[0] = AT_DEV_DIAG;
    stDynamicPidType.aucRewindPortStyle[1] = AT_DEV_SD;

    /*������׮*/
    MOCKER(NV_ReadEx)
        .expects(exactly(1))
        .with(any(), eq((VOS_UINT16)en_NV_Item_Huawei_Dynamic_PID_Type), outBoundP((void *)&stDynamicPidType, sizeof(stDynamicPidType)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_WriteEx)
        .expects(never());

    /*���ñ��⺯�� */
    ulRet = AT_CloseDiagPort();

    /* �����֤*/
    EXPECT_EQ(AT_OK, ulRet);
    GlobalMockObject::verify();
}
class Test_AT_GetSimLockStatus: public ::testing::Test
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


TEST_F(Test_AT_GetSimLockStatus, Test_AT_GetSimLockStatus_001)
{
    /*��������*/
    VOS_UINT32                                  ulRet;
    VOS_UINT8                                   ucIndex;

    /*���ر�����ʼ��*/
    ucIndex = 0;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CURRENT_OPT_BUTT;
    g_stParseContext[ucIndex].ucClientStatus = 0;

    /*������׮*/
    MOCKER(Taf_ParaQuery)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    MOCKER(At_StartTimer)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    /*���ñ��⺯�� */
    ulRet = AT_GetSimLockStatus(ucIndex);

    /* �����֤*/
    EXPECT_EQ(VOS_OK, ulRet);
    EXPECT_EQ(AT_CMD_SIMLOCKSTATUS_READ, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(AT_FW_CLIENT_STATUS_PEND, g_stParseContext[ucIndex].ucClientStatus);
    GlobalMockObject::verify();
}

#if(FEATURE_ON == FEATURE_WIFI)
class Test_AT_TestWifiPaRangePara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex = 0;
        stCmdInfo.ulCmdIndex        = AT_CMD_WIINFO;
        stCmdInfo.pfnSetProc        = AT_SetWifiPaRangePara;
        stCmdInfo.ulSetTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnQryProc        = AT_QryWifiPaRangePara;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.pfnTestProc       = AT_TestWifiPaRangePara;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^WIPARANGE";
        stCmdInfo.pszParam          = (VOS_UINT8*)"(@gainmode)";

        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }
    void TearDown()
    {

    }
protected:
    VOS_UINT8                   ucIndex;
    AT_PAR_CMD_ELEMENT_STRU     stCmdInfo;
};
#if 0

TEST_F(Test_AT_TestWifiPaRangePara, Test_AT_TestWifiPaRangePara_001)
{
    /*��������*/
    VOS_UINT32                          ulRst = 0;
    VOS_CHAR                           *pcExpactedStr;

    /* ��ʼ������ */
    pcExpactedStr = "^WIPARANGE:h";

    /* ȫ�ֱ�����ֵ */

    /* ׮���� */
    MOCKER(wifi_get_pa_mode)
        .stubs()
        .will(returnValue(AT_WIFI_MODE_ONLY_PA));

    /* ������Ϣ��ں��� */
    ulRst = AT_TestWifiPaRangePara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_OK, ulRst);
    EXPECT_EQ(VOS_StrLen(pcExpactedStr), gstAtSendData.usBufLen);
    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();

}
TEST_F(Test_AT_TestWifiPaRangePara, Test_AT_TestWifiPaRangePara_002)
{
    /*��������*/
    VOS_UINT32                          ulRst = 0;
    VOS_CHAR                           *pcExpactedStr;

    /* ��ʼ������ */
    pcExpactedStr = "^WIPARANGE:l";

    /* ȫ�ֱ�����ֵ */

    /* ׮���� */
    MOCKER(wifi_get_pa_mode)
        .stubs()
        .will(returnValue(AT_WIFI_MODE_ONLY_NOPA));

    /* ������Ϣ��ں��� */
    ulRst = AT_TestWifiPaRangePara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_OK, ulRst);
    EXPECT_EQ(VOS_StrLen(pcExpactedStr), gstAtSendData.usBufLen);
    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();

}
TEST_F(Test_AT_TestWifiPaRangePara, Test_AT_TestWifiPaRangePara_003)
{
    /*��������*/
    VOS_UINT32                          ulRst = 0;
    VOS_CHAR                           *pcExpactedStr;

    /* ��ʼ������ */
    pcExpactedStr = "^WIPARANGE:h,l";

    /* ȫ�ֱ�����ֵ */

    /* ׮���� */
    MOCKER(wifi_get_pa_mode)
        .stubs()
        .will(returnValue(AT_WIFI_MODE_PA_NOPA));

    /* ������Ϣ��ں��� */
    ulRst = AT_TestWifiPaRangePara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_OK, ulRst);
    EXPECT_EQ(VOS_StrLen(pcExpactedStr), gstAtSendData.usBufLen);
    ASSERT_STREQ(pcExpactedStr, (TAF_CHAR *)pgucAtSndCodeAddr);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();

}
#endif
TEST_F(Test_AT_TestWifiPaRangePara, Test_AT_TestWifiPaRangePara_004)
{
    /*��������*/
    VOS_UINT32                          ulRst = 0;

    /* ȫ�ֱ�����ֵ */

    /* ׮���� */
    MOCKER(wifi_get_pa_mode)
        .stubs()
        .will(returnValue(-1));

    /* ������Ϣ��ں��� */
    ulRst = AT_TestWifiPaRangePara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_ERROR, ulRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();

}

#endif

AT_PAR_CMD_ELEMENT_STRU     gstWiwepCmdInfo = {AT_CMD_WIWEP,
    AT_SetWiwepPara,        AT_SET_PARA_TIME,   AT_QryWiwepPara,  AT_QRY_PARA_TIME,  AT_TestWiwepPara, AT_SET_PARA_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_LIMITED_NULL,
    (TAF_UINT8*)"^WIWEP",    (VOS_UINT8 *)"(0-3),(@wifikey)"};

AT_PAR_CMD_ELEMENT_STRU     gstTbatCmdInfo = {AT_CMD_TBAT,
    AT_SetTbatPara,     AT_SET_PARA_TIME,   AT_QryTbatPara,  AT_QRY_PARA_TIME,  VOS_NULL_PTR, AT_SET_PARA_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"^TBAT",    (VOS_UINT8 *)"(1),(0,1),(0-65535),(0-65535)"};

AT_PAR_CMD_ELEMENT_STRU     gstCmdLenCmdInfo = {AT_CMD_CMDLEN,
    AT_SetCmdlenPara,        AT_SET_PARA_TIME,   AT_QryCmdlenPara,  AT_QRY_PARA_TIME,  At_CmdTestProcOK, AT_SET_PARA_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"^CMDLEN",    (VOS_UINT8 *)"(0-65535),(0-65535)"};

AT_PAR_CMD_ELEMENT_STRU     gstTseLrfCmdInfo = {AT_CMD_TSELRF,
    AT_SetTseLrfPara,        AT_SET_PARA_TIME,   AT_QryTseLrfPara,  AT_QRY_PARA_TIME,  VOS_NULL_PTR, AT_SET_PARA_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"^TSELRF",    (VOS_UINT8 *)"(1,2,3,7)"};

AT_PAR_CMD_ELEMENT_STRU     gstPstandbyCmdInfo = {AT_CMD_PSTANDBY,
    AT_SetPstandbyPara,     AT_SET_PARA_TIME,   VOS_NULL_PTR,  AT_QRY_PARA_TIME,  VOS_NULL_PTR, AT_SET_PARA_TIME,
    VOS_NULL_PTR,   AT_NOT_SET_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"^PSTANDBY",    (VOS_UINT8 *)"(0-65535),(0-65535)"};

/*AT_PAR_CMD_ELEMENT_STRU     gstCmdLenCmdInfo = {AT_CMD_CMDLEN,
    AT_SetCmdlenPara,        AT_SET_PARA_TIME,   AT_QryCmdlenPara,  AT_QRY_PARA_TIME,  At_CmdTestProcOK, AT_SET_PARA_TIME,
    AT_CME_INCORRECT_PARAMETERS, CMD_TBL_PIN_IS_LOCKED,
    (TAF_UINT8*)"^CMDLEN",    (VOS_UINT8 *)"(0-65535),(0-65535)"};*/

#if 0

class Test_AT_QryTbatPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        g_stParseContext[0].pstCmdElement = &gstTbatCmdInfo;

    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_QryTbatPara, Test_AT_QryTbatPara_001)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;
    char                                  *paucExpectedStr = "^TBAT:1";
    VOS_UINT32                             usExpectedStrLen;

    /*���ر�����ʼ��*/
    ucIndex = 0;

    /*���ñ��⺯�� */
    ulRet = AT_QryTbatPara(ucIndex);

    /* �����֤*/
    usExpectedStrLen = (VOS_UINT16)strlen((VOS_CHAR *)paucExpectedStr);
    ASSERT_EQ(usExpectedStrLen, gstAtSendData.usBufLen);
    ASSERT_EQ(AT_OK, ulRet);
    ASSERT_STREQ(paucExpectedStr, (char *)pgucAtSndCodeAddr);
}
#endif

class Test_AT_QryWiwepPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();

        g_stParseContext[0].pstCmdElement = &gstWiwepCmdInfo;
    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_QryWiwepPara, Test_AT_QryWiwepPara_001)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;
    TAF_AT_MULTI_WIFI_SEC_STRU             stWifiSecInfo;
    VOS_UINT8                              aucwlKeys1[] = "1234";
    VOS_UINT8                              aucwlKeys2[] = "12345";
    VOS_UINT8                              aucwlKeys3[] = "12346";
    VOS_UINT8                              aucwlKeys4[] = "12347";
    char                                  *paucExpectedStr = "^WIWEP:4\r\n^WIWEP:0,1234,0\r\n^WIWEP:1,12345,0\r\n^WIWEP:2,12346,0\r\n^WIWEP:3,12347,0\r\n";
    VOS_UINT32                             usExpectedStrLen;

    /*���ر�����ʼ��*/
    ucIndex = 0;
    g_bAtDataLocked = VOS_FALSE;

    PS_MEM_SET(&stWifiSecInfo, 0x00, sizeof(stWifiSecInfo));
    PS_MEM_CPY(stWifiSecInfo.aucWifiWepKey1, aucwlKeys1, sizeof(aucwlKeys1));
    PS_MEM_CPY(stWifiSecInfo.aucWifiWepKey2, aucwlKeys2, sizeof(aucwlKeys2));
    PS_MEM_CPY(stWifiSecInfo.aucWifiWepKey3, aucwlKeys3, sizeof(aucwlKeys3));
    PS_MEM_CPY(stWifiSecInfo.aucWifiWepKey4, aucwlKeys4, sizeof(aucwlKeys4));
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), eq((VOS_UINT16)en_NV_Item_MULTI_WIFI_KEY), outBoundP((void *)&stWifiSecInfo, sizeof(stWifiSecInfo)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    /*���ñ��⺯�� */
    ulRet = AT_QryWiwepPara(ucIndex);

    // ִ�м��
    usExpectedStrLen = (VOS_UINT16)strlen((VOS_CHAR *)paucExpectedStr) - strlen("\r\n");
    ASSERT_EQ(usExpectedStrLen, gstAtSendData.usBufLen);
    ASSERT_EQ(AT_OK, ulRet);
    ASSERT_STREQ(paucExpectedStr, (char *)pgucAtSndCodeAddr);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
TEST_F(Test_AT_QryWiwepPara, Test_AT_QryWiwepPara_002)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    /*���ر�����ʼ��*/
    ucIndex = 0;
    g_bAtDataLocked = VOS_FALSE;

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    /*�����ڴ�ʧ��*/
    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((void *)VOS_NULL_PTR));

    /*���ñ��⺯�� */
    ulRet = AT_QryWiwepPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}
TEST_F(Test_AT_QryWiwepPara, Test_AT_QryWiwepPara_003)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    /*���ر�����ʼ��*/
    ucIndex = 0;
    g_bAtDataLocked = VOS_FALSE;

    /*NV���ȡ����ʧ��*/
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));


    /*���ñ��⺯�� */
    ulRet = AT_QryWiwepPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}


#if (FEATURE_ON != FEATURE_LTE)
class Test_AT_SetTbatPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        g_stParseContext[0].pstCmdElement = &gstTbatCmdInfo;

    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_SetTbatPara, Test_AT_SetTbatPara_001)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;

    gucAtParaIndex = 2;

    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 1;

    gastAtParaList[1].usParaLen = 1;
    gastAtParaList[1].ulParaValue = 0;

    /*���ر�����ʼ��*/
    ucIndex = 0;

    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq(DRV_AGENT_HKADC_GET_REQ), any(), any(), any())
        .will(returnValue(TAF_SUCCESS));

    /*���ñ��⺯�� */
    ulRet = AT_SetTbatPara(ucIndex);

    /* �����֤*/
    ASSERT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetTbatPara, Test_AT_SetTbatPara_002)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;

    gucAtParaIndex = 2;

    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 1;

    gastAtParaList[1].usParaLen = 1;
    gastAtParaList[1].ulParaValue = 0;

    /*���ر�����ʼ��*/
    ucIndex = 0;

    MOCKER(AT_FillAndSndAppReqMsg)
        .expects(exactly(1))
        .with(any(), any(), eq(DRV_AGENT_HKADC_GET_REQ), any(), any(), any())
        .will(returnValue(TAF_FAILURE));

    /*���ñ��⺯�� */
    ulRet = AT_SetTbatPara(ucIndex);

    /* �����֤*/
    ASSERT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetTbatPara, Test_AT_SetTbatPara_003)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;
    VOS_INT                                TbatHkadc;
    VOS_UINT16                             usExpectedStrLen;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;

    gucAtParaIndex = 4;

    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 1;

    gastAtParaList[1].usParaLen = 1;
    gastAtParaList[1].ulParaValue = 1;

    gastAtParaList[2].usParaLen = 4;
    gastAtParaList[2].ulParaValue = 3700;

    gastAtParaList[3].usParaLen = 4;
    gastAtParaList[3].ulParaValue = 4200;

    /*���ر�����ʼ��*/
    ucIndex = 0;

    /*���ñ��⺯�� */
    ulRet = AT_SetTbatPara(ucIndex);

    /* �����֤*/
    ASSERT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetTbatPara, Test_AT_SetTbatPara_004)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;
    VOS_INT                                TbatHkadc;
    VOS_UINT16                             usExpectedStrLen;
    const char                             cWarning[] = "AT_SetTbatPara: Fail to write NV en_NV_Item_BATTERY_ADC.";

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;

    gucAtParaIndex = 4;

    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 1;

    gastAtParaList[1].usParaLen = 1;
    gastAtParaList[1].ulParaValue = 1;

    gastAtParaList[2].usParaLen = 4;
    gastAtParaList[2].ulParaValue = 3700;

    gastAtParaList[3].usParaLen = 4;
    gastAtParaList[3].ulParaValue = 4200;

    /*���ر�����ʼ��*/
    ucIndex = 0;

    /*NV���ȡ����ʧ��*/
    MOCKER(NV_WriteEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    /* дNV��ʧ�ܵĸ澯��Ϣ */
    MOCKER(DIAG_LogReport)
        .stubs()
        .with(any(), any(), any(), any(), any(), mirror(cWarning,strlen(cWarning) + 1));

    /*���ñ��⺯�� */
    ulRet = AT_SetTbatPara(ucIndex);

    /* �����֤*/
    ASSERT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}
#if 0

TEST_F(Test_AT_SetTbatPara, Test_AT_SetTbatPara_004)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    /*���ر�����ʼ��*/
    ucIndex = 0;
    gastAtParaList[0].ulParaValue = AT_TBAT_BATTERY_ANALOG_VOLTAGE;

    /*���ñ��⺯�� */
    ulRet = AT_SetTbatPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRet);
    GlobalMockObject::verify();
}
#endif

TEST_F(Test_AT_SetTbatPara, Test_AT_SetTbatPara_006)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;

    /*���ñ��⺯�� */
    ulRet = AT_SetTbatPara(ucIndex);

    /* �����֤*/
    ASSERT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRet);

    GlobalMockObject::verify();

}


TEST_F(Test_AT_SetTbatPara, Test_AT_SetTbatPara_007)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gastAtParaList[0].usParaLen = 0;
    gastAtParaList[0].ulParaValue = 1;
    gastAtParaList[1].usParaLen = 1;
    gastAtParaList[1].ulParaValue = 1;

    /*���ñ��⺯�� */
    ulRet = AT_SetTbatPara(ucIndex);

    /* �����֤*/
    ASSERT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRet);

    GlobalMockObject::verify();

}


TEST_F(Test_AT_SetTbatPara, Test_AT_SetTbatPara_008)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 1;
    gastAtParaList[1].usParaLen = 0;
    gastAtParaList[1].ulParaValue = 1;

    /*���ñ��⺯�� */
    ulRet = AT_SetTbatPara(ucIndex);

    /* �����֤*/
    ASSERT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRet);

    GlobalMockObject::verify();

}


TEST_F(Test_AT_SetTbatPara, Test_AT_SetTbatPara_009)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 1;
    gastAtParaList[1].usParaLen = 1;
    gastAtParaList[1].ulParaValue = 0;

    gucAtParaIndex = 3;

    /*���ñ��⺯�� */
    ulRet = AT_SetTbatPara(ucIndex);

    /* �����֤*/
    ASSERT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRet);

    GlobalMockObject::verify();

}


TEST_F(Test_AT_SetTbatPara, Test_AT_SetTbatPara_010)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 1;
    gastAtParaList[1].usParaLen = 1;
    gastAtParaList[1].ulParaValue = 1;

    gucAtParaIndex = 3;

    /*���ñ��⺯�� */
    ulRet = AT_SetTbatPara(ucIndex);

    /* �����֤*/
    ASSERT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRet);

    GlobalMockObject::verify();

}


TEST_F(Test_AT_SetTbatPara, Test_AT_SetTbatPara_011)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 1;
    gastAtParaList[1].usParaLen = 1;
    gastAtParaList[1].ulParaValue = 1;
    gastAtParaList[2].usParaLen = 0;
    gastAtParaList[3].usParaLen = 4;
    gastAtParaList[3].ulParaValue = 4200;

    gucAtParaIndex = 4;

    /*���ñ��⺯�� */
    ulRet = AT_SetTbatPara(ucIndex);

    /* �����֤*/
    ASSERT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRet);

    GlobalMockObject::verify();

}


TEST_F(Test_AT_SetTbatPara, Test_AT_SetTbatPara_012)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 1;
    gastAtParaList[1].usParaLen = 1;
    gastAtParaList[1].ulParaValue = 1;
    gastAtParaList[2].usParaLen = 4;
    gastAtParaList[2].ulParaValue = 3700;
    gastAtParaList[3].usParaLen = 0;

    gucAtParaIndex = 4;

    /*���ñ��⺯�� */
    ulRet = AT_SetTbatPara(ucIndex);

    /* �����֤*/
    ASSERT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRet);

    GlobalMockObject::verify();

}
#endif

class Test_AT_SetWiwepPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        g_stParseContext[0].pstCmdElement = &gstWiwepCmdInfo;

    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_SetWiwepPara, Test_AT_SetWiwepPara_001)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT8                              aucWifiKey[] = "12345";
    VOS_UINT32                             ulRet;

    /*���ر�����ʼ��*/
    ucIndex = 0;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 0;
    gastAtParaList[1].usParaLen = strlen((VOS_CHAR *)aucWifiKey);
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[2].ulParaValue = 0;
    PS_MEM_CPY(gastAtParaList[1].aucPara, aucWifiKey, gastAtParaList[1].usParaLen);

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_WriteEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    g_bAtDataLocked = VOS_FALSE;

    /*���ñ��⺯�� */
    ulRet = AT_SetWiwepPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_OK, ulRet);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetWiwepPara, Test_AT_SetWiwepPara_002)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT8                              aucWifiKey[] = "12345";
    VOS_UINT32                             ulRet;

    /*���ر�����ʼ��*/
    ucIndex = 0;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 0;
    gastAtParaList[1].usParaLen = strlen((VOS_CHAR *)aucWifiKey);
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[2].ulParaValue = 0;
    PS_MEM_CPY(gastAtParaList[1].aucPara, aucWifiKey, gastAtParaList[1].usParaLen);

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    g_bAtDataLocked = VOS_FALSE;

    /*�����ڴ�ʧ��*/
    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((void *)VOS_NULL_PTR));

    /*���ñ��⺯�� */
    ulRet = AT_SetWiwepPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}
TEST_F(Test_AT_SetWiwepPara, Test_AT_SetWiwepPara_003)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT8                              aucWifiKey[] = "12345";
    VOS_UINT32                             ulRet;

    /*���ر�����ʼ��*/
    ucIndex = 0;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 0;
    gastAtParaList[1].usParaLen = strlen((VOS_CHAR *)aucWifiKey);
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[2].ulParaValue = 0;
    PS_MEM_CPY(gastAtParaList[1].aucPara, aucWifiKey, gastAtParaList[1].usParaLen);

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    /*NV���ȡ����ʧ��*/
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    g_bAtDataLocked = VOS_FALSE;

    /*���ñ��⺯�� */
    ulRet = AT_SetWiwepPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}
TEST_F(Test_AT_SetWiwepPara, Test_AT_SetWiwepPara_004)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT8                              aucWifiKey[] = "12345";
    VOS_UINT32                             ulRet;

    /*���ر�����ʼ��*/
    ucIndex = 0;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 0;
    gastAtParaList[1].usParaLen = strlen((VOS_CHAR *)aucWifiKey);
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[2].ulParaValue = 0;
    PS_MEM_CPY(gastAtParaList[1].aucPara, aucWifiKey, gastAtParaList[1].usParaLen);

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    /*NV���ȡ����ʧ��*/
    MOCKER(NV_ReadEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_WriteEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_ID_NOT_EXIST));

    g_bAtDataLocked = VOS_FALSE;


    /*���ñ��⺯�� */
    ulRet = AT_SetWiwepPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}
TEST_F(Test_AT_SetWiwepPara, Test_AT_SetWiwepPara_005)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT8                              aucWifiKey[] = "12345";
    VOS_UINT32                             ulRet;

    /*���ر�����ʼ��*/
    ucIndex = 0;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 0;
    gastAtParaList[1].usParaLen = strlen((VOS_CHAR *)aucWifiKey);
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[2].ulParaValue = 0;
    PS_MEM_CPY(gastAtParaList[1].aucPara, aucWifiKey, gastAtParaList[1].usParaLen);

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    g_bAtDataLocked = VOS_FALSE;

    /*���ñ��⺯�� */
    ulRet = AT_SetWiwepPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetWiwepPara, Test_AT_SetWiwepPara_006)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT8                              aucWifiKey[] = "12345";
    VOS_UINT32                             ulRet;

    /*���ر�����ʼ��*/
    ucIndex = 0;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 4;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 0;
    gastAtParaList[1].usParaLen = strlen((VOS_CHAR *)aucWifiKey);
    gastAtParaList[2].usParaLen = 0;
    gastAtParaList[2].ulParaValue = 0;
    PS_MEM_CPY(gastAtParaList[1].aucPara, aucWifiKey, gastAtParaList[1].usParaLen);

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    g_bAtDataLocked = VOS_FALSE;

    /*���ñ��⺯�� */
    ulRet = AT_SetWiwepPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetWiwepPara, Test_AT_SetWiwepPara_007)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT8                              aucWifiKey[] = "12345";
    VOS_UINT32                             ulRet;

    /*���ر�����ʼ��*/
    ucIndex = 0;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 3;
    gastAtParaList[0].usParaLen = 0;
    gastAtParaList[0].ulParaValue = 0;
    gastAtParaList[1].usParaLen = strlen((VOS_CHAR *)aucWifiKey);
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[2].ulParaValue = 0;
    PS_MEM_CPY(gastAtParaList[1].aucPara, aucWifiKey, gastAtParaList[1].usParaLen);

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    g_bAtDataLocked = VOS_FALSE;

    /*���ñ��⺯�� */
    ulRet = AT_SetWiwepPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetWiwepPara, Test_AT_SetWiwepPara_008)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT8                              aucWifiKey[] = "12345";
    VOS_UINT32                             ulRet;

    /*���ر�����ʼ��*/
    ucIndex = 0;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 3;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 0;
    gastAtParaList[1].usParaLen = 0;
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[2].ulParaValue = 0;
    PS_MEM_CPY(gastAtParaList[1].aucPara, aucWifiKey, gastAtParaList[1].usParaLen);

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    g_bAtDataLocked = VOS_FALSE;

    /*���ñ��⺯�� */
    ulRet = AT_SetWiwepPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetWiwepPara, Test_AT_SetWiwepPara_009)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT8                              aucWifiKey[] = "12345";
    VOS_UINT32                             ulRet;

    /*���ر�����ʼ��*/
    ucIndex = 0;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 3;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 0;
    gastAtParaList[1].usParaLen = AT_NV_WLKEY_LEN + 1;
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[2].ulParaValue = 0;

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    g_bAtDataLocked = VOS_FALSE;

    /*���ñ��⺯�� */
    ulRet = AT_SetWiwepPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetWiwepPara, Test_AT_SetWiwepPara_010)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT8                              aucWifiKey[] = "12345";
    VOS_UINT32                             ulRet;

    /*���ر�����ʼ��*/
    ucIndex = 0;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 0;
    gastAtParaList[1].usParaLen = AT_NV_WLKEY_LEN + 1;
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[2].ulParaValue = 0;

    g_bAtDataLocked = VOS_FALSE;

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    /*���ñ��⺯�� */
    ulRet = AT_SetWiwepPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetWiwepPara, Test_AT_SetWiwepPara_011)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT8                              aucWifiKey[] = "12345";
    VOS_UINT32                             ulRet;

    /*���ر�����ʼ��*/
    ucIndex = 0;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 0;
    gastAtParaList[0].ulParaValue = 0;
    gastAtParaList[1].usParaLen = AT_NV_WLKEY_LEN + 1;
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[2].ulParaValue = 0;

    g_bAtDataLocked = VOS_FALSE;

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    /*���ñ��⺯�� */
    ulRet = AT_SetWiwepPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetWiwepPara, Test_AT_SetWiwepPara_012)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT8                              aucWifiKey[] = "12345";
    VOS_UINT32                             ulRet;

    /*���ر�����ʼ��*/
    ucIndex = 0;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 0;
    gastAtParaList[0].ulParaValue = 0;
    gastAtParaList[1].usParaLen = AT_NV_WLKEY_LEN + 1;
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[2].ulParaValue = 0;

    g_bAtDataLocked = VOS_FALSE;

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    /*���ñ��⺯�� */
    ulRet = AT_SetWiwepPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}

TEST_F(Test_AT_SetWiwepPara, Test_AT_SetWiwepPara_013)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT8                              aucWifiKey[] = "12345";
    VOS_UINT32                             ulRet;

    /*���ر�����ʼ��*/
    ucIndex = 0;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 0;
    gastAtParaList[1].usParaLen = 0;
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[2].ulParaValue = 0;

    g_bAtDataLocked = VOS_FALSE;

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    /*���ñ��⺯�� */
    ulRet = AT_SetWiwepPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_ERROR, ulRet);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetWiwepPara, Test_AT_SetWiwepPara_014)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT8                              aucWifiKey1[] = "12345";
    VOS_UINT8                              aucWifiKey[] = "12345";
    VOS_UINT32                             ulRet;
    TAF_AT_MULTI_WIFI_SEC_STRU             stWifiSecInfo;

    /*���ر�����ʼ��*/
    ucIndex = 0;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 3;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = 0;
    gastAtParaList[1].usParaLen = 5 ;
    gastAtParaList[2].usParaLen = 1;
    gastAtParaList[2].ulParaValue = 0;

    g_bAtDataLocked = VOS_FALSE;

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    PS_MEM_CPY(stWifiSecInfo.aucWifiWepKey1, aucWifiKey1, sizeof(aucWifiKey1));
    MOCKER(NV_ReadEx)
        .stubs()
        .with(any(), eq((VOS_UINT16)en_NV_Item_MULTI_WIFI_KEY), outBoundP((void *)&stWifiSecInfo,sizeof(stWifiSecInfo)), any())
        .will(returnValue((VOS_UINT32)NV_OK));

    MOCKER(NV_WriteEx)
        .stubs()
        .will(returnValue((VOS_UINT32)NV_OK));

    /*���ñ��⺯�� */
    ulRet = AT_SetWiwepPara(ucIndex);

    /* �����֤*/
    EXPECT_EQ(AT_OK, ulRet);
    GlobalMockObject::verify();
}


class Test_AT_TestWiwepPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        g_stParseContext[0].pstCmdElement = &gstWiwepCmdInfo;

    }
    void TearDown()
    {

    }
};


TEST_F(Test_AT_TestWiwepPara, Test_AT_TestWiwepPara_001)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;
    char                                  *paucExpectedStr = "^WIWEP:16";
    VOS_UINT32                             usExpectedStrLen;

    /*���ر�����ʼ��*/
    ucIndex = 0;

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .will(returnValue(BSP_MODULE_SUPPORT));

    /*���ñ��⺯�� */
    ulRet = AT_TestWiwepPara(ucIndex);

    /* �����֤*/
    usExpectedStrLen = (VOS_UINT16)strlen((VOS_CHAR *)paucExpectedStr);
    ASSERT_EQ(usExpectedStrLen, gstAtSendData.usBufLen);
    ASSERT_EQ(AT_OK, ulRet);
    ASSERT_STREQ(paucExpectedStr, (char *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}

class Test_AT_GetTseLrfLoadDspInfo: public ::testing::Test
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


TEST_F(Test_AT_GetTseLrfLoadDspInfo, Test_AT_GetTseLrfLoadDspInfo_001)
{
    AT_TSELRF_PATH_ENUM_UINT32          enPath;
    VOS_BOOL                            bLoadDsp;
    DRV_AGENT_TSELRF_SET_REQ_STRU       stTseLrf;

    enPath = AT_TSELRF_PATH_GSM;
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_GSM;
    g_stAtDevCmdCtrl.bDspLoadFlag    = VOS_TRUE;

    stTseLrf.ucLoadDspMode     = VOS_RATMODE_GSM;
    stTseLrf.ucDeviceRatMode   = AT_RAT_MODE_GSM;
    bLoadDsp                   = VOS_TRUE;

    AT_GetTseLrfLoadDspInfo(enPath, &bLoadDsp, &stTseLrf);

    EXPECT_EQ(VOS_FALSE, bLoadDsp);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_GetTseLrfLoadDspInfo, Test_AT_GetTseLrfLoadDspInfo_002)
{
    AT_TSELRF_PATH_ENUM_UINT32          enPath;
    VOS_BOOL                            bLoadDsp;
    DRV_AGENT_TSELRF_SET_REQ_STRU       stTseLrf;

    enPath = AT_TSELRF_PATH_GSM;
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_GSM;
    g_stAtDevCmdCtrl.bDspLoadFlag    = VOS_FALSE;

    stTseLrf.ucLoadDspMode     = VOS_RATMODE_GSM;
    stTseLrf.ucDeviceRatMode   = AT_RAT_MODE_GSM;
    bLoadDsp                   = VOS_TRUE;

    AT_GetTseLrfLoadDspInfo(enPath, &bLoadDsp, &stTseLrf);

    EXPECT_EQ(VOS_TRUE, bLoadDsp);
    EXPECT_EQ(VOS_RATMODE_GSM, stTseLrf.ucLoadDspMode);
    EXPECT_EQ(AT_RAT_MODE_GSM, stTseLrf.ucDeviceRatMode);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_GetTseLrfLoadDspInfo, Test_AT_GetTseLrfLoadDspInfo_003)
{
    AT_TSELRF_PATH_ENUM_UINT32          enPath;
    VOS_BOOL                            bLoadDsp;
    DRV_AGENT_TSELRF_SET_REQ_STRU       stTseLrf;

    enPath = AT_TSELRF_PATH_GSM;
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_WCDMA;
    g_stAtDevCmdCtrl.bDspLoadFlag    = VOS_FALSE;

    stTseLrf.ucLoadDspMode     = VOS_RATMODE_GSM;
    stTseLrf.ucDeviceRatMode   = AT_RAT_MODE_GSM;
    bLoadDsp                   = VOS_TRUE;

    AT_GetTseLrfLoadDspInfo(enPath, &bLoadDsp, &stTseLrf);

    EXPECT_EQ(VOS_TRUE, bLoadDsp);
    EXPECT_EQ(VOS_RATMODE_GSM, stTseLrf.ucLoadDspMode);
    EXPECT_EQ(AT_RAT_MODE_GSM, stTseLrf.ucDeviceRatMode);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_GetTseLrfLoadDspInfo, Test_AT_GetTseLrfLoadDspInfo_004)
{
    AT_TSELRF_PATH_ENUM_UINT32          enPath;
    VOS_BOOL                            bLoadDsp;
    DRV_AGENT_TSELRF_SET_REQ_STRU       stTseLrf;

    enPath = AT_TSELRF_PATH_WCDMA_PRI;
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_WCDMA;
    g_stAtDevCmdCtrl.bDspLoadFlag    = VOS_TRUE;

    stTseLrf.ucLoadDspMode     = VOS_RATMODE_WCDMA;
    stTseLrf.ucDeviceRatMode   = AT_RAT_MODE_WCDMA;
    bLoadDsp                   = VOS_TRUE;

    AT_GetTseLrfLoadDspInfo(enPath, &bLoadDsp, &stTseLrf);

    EXPECT_EQ(VOS_FALSE, bLoadDsp);
    GlobalMockObject::verify();
}


TEST_F(Test_AT_GetTseLrfLoadDspInfo, Test_AT_GetTseLrfLoadDspInfo_005)
{
    AT_TSELRF_PATH_ENUM_UINT32          enPath;
    VOS_BOOL                            bLoadDsp;
    DRV_AGENT_TSELRF_SET_REQ_STRU       stTseLrf;

    enPath = AT_TSELRF_PATH_WCDMA_PRI;
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_AWS;
    g_stAtDevCmdCtrl.bDspLoadFlag    = VOS_TRUE;

    stTseLrf.ucLoadDspMode     = VOS_RATMODE_WCDMA;
    stTseLrf.ucDeviceRatMode   = AT_RAT_MODE_WCDMA;
    bLoadDsp                   = VOS_FALSE;

    AT_GetTseLrfLoadDspInfo(enPath, &bLoadDsp, &stTseLrf);

    EXPECT_EQ(VOS_FALSE, bLoadDsp);
    EXPECT_EQ(VOS_RATMODE_WCDMA, stTseLrf.ucLoadDspMode);
    EXPECT_EQ(AT_RAT_MODE_WCDMA, stTseLrf.ucDeviceRatMode);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_GetTseLrfLoadDspInfo, Test_AT_GetTseLrfLoadDspInfo_006)
{
    AT_TSELRF_PATH_ENUM_UINT32          enPath;
    VOS_BOOL                            bLoadDsp;
    DRV_AGENT_TSELRF_SET_REQ_STRU       stTseLrf;

    enPath = AT_TSELRF_PATH_WCDMA_PRI;
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_WCDMA;
    g_stAtDevCmdCtrl.bDspLoadFlag    = VOS_FALSE;

    stTseLrf.ucLoadDspMode     = VOS_RATMODE_WCDMA;
    stTseLrf.ucDeviceRatMode   = AT_RAT_MODE_WCDMA;
    bLoadDsp                   = VOS_FALSE;

    AT_GetTseLrfLoadDspInfo(enPath, &bLoadDsp, &stTseLrf);

    EXPECT_EQ(VOS_TRUE, bLoadDsp);
    EXPECT_EQ(VOS_RATMODE_WCDMA, stTseLrf.ucLoadDspMode);
    EXPECT_EQ(AT_RAT_MODE_WCDMA, stTseLrf.ucDeviceRatMode);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_GetTseLrfLoadDspInfo, Test_AT_GetTseLrfLoadDspInfo_007)
{
    AT_TSELRF_PATH_ENUM_UINT32          enPath;
    VOS_BOOL                            bLoadDsp;
    DRV_AGENT_TSELRF_SET_REQ_STRU       stTseLrf;

    enPath = AT_TSELRF_PATH_WCDMA_PRI;
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_GSM;
    g_stAtDevCmdCtrl.bDspLoadFlag    = VOS_TRUE;

    stTseLrf.ucLoadDspMode     = VOS_RATMODE_WCDMA;
    stTseLrf.ucDeviceRatMode   = AT_RAT_MODE_WCDMA;
    bLoadDsp                   = VOS_FALSE;

    AT_GetTseLrfLoadDspInfo(enPath, &bLoadDsp, &stTseLrf);

    EXPECT_EQ(VOS_TRUE, bLoadDsp);
    EXPECT_EQ(VOS_RATMODE_WCDMA, stTseLrf.ucLoadDspMode);
    EXPECT_EQ(AT_RAT_MODE_WCDMA, stTseLrf.ucDeviceRatMode);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_GetTseLrfLoadDspInfo, Test_AT_GetTseLrfLoadDspInfo_008)
{
    AT_TSELRF_PATH_ENUM_UINT32          enPath;
    VOS_BOOL                            bLoadDsp;
    DRV_AGENT_TSELRF_SET_REQ_STRU       stTseLrf;
    const char                          cWarning[] = "AT_GetTseLrfLoadDspInfo: enPath only support GSM or WCDMA primary.";

    enPath = AT_TSELRF_PATH_BUTT;
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_GSM;
    g_stAtDevCmdCtrl.bDspLoadFlag    = VOS_TRUE;

    stTseLrf.ucLoadDspMode     = VOS_RATMODE_WCDMA;
    stTseLrf.ucDeviceRatMode   = AT_RAT_MODE_WCDMA;
    bLoadDsp                   = VOS_FALSE;

    AT_GetTseLrfLoadDspInfo(enPath, &bLoadDsp, &stTseLrf);

    EXPECT_EQ(VOS_FALSE, bLoadDsp);

    GlobalMockObject::verify();
}

class Test_AT_QryCmdlenPara: public ::testing::Test
{
public:

    void SetUp()
    {
        UT_STUB_INIT();
        g_stParseContext[0].pstCmdElement = &gstCmdLenCmdInfo;
    }
    void TearDown()
    {
    }
};


TEST_F(Test_AT_QryCmdlenPara, Test_AT_QryCmdlenPara_001)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;
    char                                  *paucExpectedStr = "^CMDLEN:1598,5000";
    VOS_UINT32                             usExpectedStrLen;

    ucIndex = 0;

    ulRet = AT_QryCmdlenPara(ucIndex);

    usExpectedStrLen = (VOS_UINT16)strlen((VOS_CHAR *)paucExpectedStr);

    ASSERT_EQ(usExpectedStrLen, gstAtSendData.usBufLen);
    ASSERT_EQ(AT_OK, ulRet);
    ASSERT_STREQ(paucExpectedStr, (char *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}
class Test_AT_SetTseLrfPara: public ::testing::Test
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


TEST_F(Test_AT_SetTseLrfPara, Test_AT_SetTseLrfPara_001)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;

    ulRet = AT_SetTseLrfPara(ucIndex);

    ASSERT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}

#if (FEATURE_ON != FEATURE_LTE)
TEST_F(Test_AT_SetTseLrfPara, Test_AT_SetTseLrfPara_002)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 1;
    gastAtParaList[0].usParaLen = 0;

    ulRet = AT_SetTseLrfPara(ucIndex);

    ASSERT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_SetTseLrfPara, Test_AT_SetTseLrfPara_003)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 1;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = AT_TSELRF_PATH_WIFI;

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .with(eq((BSP_MODULE_TYPE_E)BSP_MODULE_TYPE_WIFI))
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    MOCKER(wifi_get_status)
        .stubs()
        .will(returnValue((int)VOS_FALSE));

    ulRet = AT_SetTseLrfPara(ucIndex);

    ASSERT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_SetTseLrfPara, Test_AT_SetTseLrfPara_004)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 2;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = AT_TSELRF_PATH_WCDMA_PRI;

    ulRet = AT_SetTseLrfPara(ucIndex);

    ASSERT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_SetTseLrfPara, Test_AT_SetTseLrfPara_005)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 1;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = AT_TSELRF_PATH_WIFI;

    MOCKER(wifi_get_status)
        .expects(exactly(1))
        .will(returnValue((int)VOS_TRUE));

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .with(eq((BSP_MODULE_TYPE_E)BSP_MODULE_TYPE_WIFI))
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_SUPPORT));

    MOCKER(wifi_get_status)
        .expects(exactly(1))
        .will(returnValue((int)VOS_TRUE));

    ulRet = AT_SetTseLrfPara(ucIndex);

    ASSERT_EQ(AT_OK, ulRet);
    ASSERT_EQ(AT_RAT_MODE_WIFI, g_stAtDevCmdCtrl.ucDeviceRatMode);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_SetTseLrfPara, Test_AT_SetTseLrfPara_006)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 1;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = AT_TSELRF_PATH_WIFI;

    MOCKER(mdrv_misc_support_check)
        .stubs()
        .with(eq((BSP_MODULE_TYPE_E)BSP_MODULE_TYPE_WIFI))
        .will(returnValue((BSP_MODULE_SUPPORT_E)BSP_MODULE_UNSUPPORT));

    ulRet = AT_SetTseLrfPara(ucIndex);

    ASSERT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}
#endif
TEST_F(Test_AT_SetTseLrfPara, Test_AT_SetTseLrfPara_007)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 1;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = AT_TSELRF_PATH_WCDMA_DIV;

    g_stAtDevCmdCtrl.ucCurrentTMode = AT_TMODE_NORMAL;

    ulRet = AT_SetTseLrfPara(ucIndex);

    ASSERT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_SetTseLrfPara, Test_AT_SetTseLrfPara_008)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;
    VOS_UINT8                              ucPriOrDiv;

    ucIndex = 0;
    ucPriOrDiv = AT_RX_DIV_ON;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 1;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = AT_TSELRF_PATH_WCDMA_DIV;

    g_stAtDevCmdCtrl.ucCurrentTMode = AT_TMODE_FTM;
    g_stAtDevCmdCtrl.ucRxOnOff      = 0;

    ulRet = AT_SetTseLrfPara(ucIndex);

    ASSERT_EQ(AT_OK, ulRet);
    ASSERT_EQ(ucPriOrDiv, g_stAtDevCmdCtrl.ucPriOrDiv);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_SetTseLrfPara, Test_AT_SetTseLrfPara_009)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 1;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = AT_TSELRF_PATH_WCDMA_DIV;

    g_stAtDevCmdCtrl.ucCurrentTMode = AT_TMODE_FTM;
    g_stAtDevCmdCtrl.ucRxOnOff      = DRV_AGENT_DSP_RF_SWITCH_ON;

    MOCKER(At_SendRfCfgAntSelToHPA)
        .stubs()
        .will(returnValue((VOS_UINT32)AT_FAILURE));

    ulRet = AT_SetTseLrfPara(ucIndex);

    ASSERT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_SetTseLrfPara, Test_AT_SetTseLrfPara_010)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 1;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = AT_TSELRF_PATH_WCDMA_DIV;

    g_stAtDevCmdCtrl.ucCurrentTMode = AT_TMODE_FTM;
    g_stAtDevCmdCtrl.ucRxOnOff      = DRV_AGENT_DSP_RF_SWITCH_ON;

    MOCKER(At_SendRfCfgAntSelToHPA)
        .stubs()
        .will(returnValue((VOS_UINT32)AT_SUCCESS));

    ulRet = AT_SetTseLrfPara(ucIndex);

    ASSERT_EQ(ucIndex, g_stAtDevCmdCtrl.ucIndex);
    ASSERT_EQ(AT_CMD_TSELRF_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);
    ASSERT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_SetTseLrfPara, Test_AT_SetTseLrfPara_011)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;
    VOS_BOOL                               bLoadDsp;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 1;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = AT_TSELRF_PATH_WCDMA_PRI;

    g_stAtDevCmdCtrl.ucCurrentTMode = AT_TMODE_FTM;
    g_stAtDevCmdCtrl.ucRxOnOff      = DRV_AGENT_DSP_RF_SWITCH_ON;

    bLoadDsp = VOS_TRUE;

    MOCKER(AT_GetTseLrfLoadDspInfo)
        .expects(exactly(1))
        .with(eq((AT_TSELRF_PATH_ENUM_UINT32)AT_TSELRF_PATH_WCDMA_PRI), outBoundP((VOS_BOOL *)&bLoadDsp, (VOS_UINT32)sizeof(bLoadDsp)), any());

    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    ulRet = AT_SetTseLrfPara(ucIndex);

    ASSERT_EQ(AT_CMD_TSELRF_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);
    ASSERT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_SetTseLrfPara, Test_AT_SetTseLrfPara_012)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;
    VOS_BOOL                               bLoadDsp;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 1;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = AT_TSELRF_PATH_WCDMA_PRI;

    g_stAtDevCmdCtrl.ucCurrentTMode = AT_TMODE_FTM;
    g_stAtDevCmdCtrl.ucRxOnOff      = DRV_AGENT_DSP_RF_SWITCH_ON;

    bLoadDsp = VOS_TRUE;

    MOCKER(AT_GetTseLrfLoadDspInfo)
        .stubs()
        .with(any(), outBoundP((VOS_BOOL *)&bLoadDsp, (VOS_UINT32)sizeof(bLoadDsp)), any());

    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    ulRet = AT_SetTseLrfPara(ucIndex);

    ASSERT_EQ(AT_CMD_TSELRF_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);
    ASSERT_EQ(AT_WAIT_ASYNC_RETURN, ulRet);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_SetTseLrfPara, Test_AT_SetTseLrfPara_013)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;
    VOS_BOOL                               bLoadDsp;

    ucIndex = 0;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtParaIndex = 1;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[0].ulParaValue = AT_TSELRF_PATH_WCDMA_PRI;

    g_stAtDevCmdCtrl.ucCurrentTMode = AT_TMODE_FTM;
    g_stAtDevCmdCtrl.ucRxOnOff      = DRV_AGENT_DSP_RF_SWITCH_ON;

    bLoadDsp = VOS_FALSE;

    MOCKER(AT_GetTseLrfLoadDspInfo)
        .stubs()
        .with(any(), outBoundP((VOS_BOOL *)&bLoadDsp, (VOS_UINT32)sizeof(bLoadDsp)), any());
    
    MOCKER(AT_FillAndSndAppReqMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    ulRet = AT_SetTseLrfPara(ucIndex);

    ASSERT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();
}

#if(FEATURE_LTE != FEATURE_ON)
class Test_AT_QryTseLrfPara: public ::testing::Test
{
public:

    void SetUp()
    {
        UT_STUB_INIT();
        g_stParseContext[0].pstCmdElement = &gstTseLrfCmdInfo;
    }
    void TearDown()
    {
    }
};


TEST_F(Test_AT_QryTseLrfPara, Test_AT_QryTseLrfPara_001)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;
    char                                  *paucExpectedStr = "^TSELRF:4\r\n^TSELRF:1\r\n^TSELRF:2\r\n^TSELRF:3\r\n^TSELRF:7";
    VOS_UINT32                             usExpectedStrLen;

    ucIndex = 0;
    ulRet = AT_QryTseLrfPara(ucIndex);

    usExpectedStrLen = (VOS_UINT16)strlen((VOS_CHAR *)paucExpectedStr);

    ASSERT_EQ(usExpectedStrLen, gstAtSendData.usBufLen);
    ASSERT_EQ(AT_OK, ulRet);
    ASSERT_STREQ(paucExpectedStr, (char *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}

#endif
#if 0
class Test_AT_SetCmdlenPara: public ::testing::Test
{
public:

    void SetUp()
    {
        UT_STUB_INIT();
        g_stParseContext[0].pstCmdElement = &gstCmdLenCmdInfo;
    }
    void TearDown()
    {
    }
};


TEST_F(Test_AT_SetCmdlenPara, Test_AT_SetCmdlenPara_001)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gastAtParaList[0].usParaLen = 3;
    gastAtParaList[0].ulParaValue = 1000;
    gastAtParaList[1].usParaLen = 3;
    gastAtParaList[1].ulParaValue =3000;

    ucIndex = 0;

    ulRet = AT_SetCmdlenPara(ucIndex);

    ASSERT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_SetCmdlenPara, Test_AT_SetCmdlenPara_002)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;
    gastAtParaList[0].usParaLen = 3;
    gastAtParaList[0].ulParaValue = 1000;
    gastAtParaList[1].usParaLen = 3;
    gastAtParaList[1].ulParaValue =3000;

    ucIndex = 0;

    ulRet = AT_SetCmdlenPara(ucIndex);

    ASSERT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRet);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_SetCmdlenPara, Test_AT_SetCmdlenPara_003)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gastAtParaList[0].usParaLen = 0;
    gastAtParaList[0].ulParaValue = 1000;
    gastAtParaList[1].usParaLen = 3;
    gastAtParaList[1].ulParaValue =3000;

    ucIndex = 0;
    ulRet = AT_SetCmdlenPara(ucIndex);

    ASSERT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRet);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_SetCmdlenPara, Test_AT_SetCmdlenPara_004)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gastAtParaList[0].usParaLen = 3;
    gastAtParaList[0].ulParaValue = 1000;
    gastAtParaList[1].usParaLen = 0;
    gastAtParaList[1].ulParaValue =3000;

    ucIndex = 0;
    ulRet = AT_SetCmdlenPara(ucIndex);

    ASSERT_EQ(AT_CME_INCORRECT_PARAMETERS, ulRet);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_SetCmdlenPara, Test_AT_SetCmdlenPara_005)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gastAtParaList[0].usParaLen = 3;
    gastAtParaList[0].ulParaValue = 1600;
    gastAtParaList[1].usParaLen = 3;
    gastAtParaList[1].ulParaValue =3000;

    ucIndex = 0;
    ulRet = AT_SetCmdlenPara(ucIndex);

    ASSERT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}
class Test_AT_SetTmodeAutoPowerOff: public ::testing::Test
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

#if (FEATURE_ON == FEATURE_E5)

TEST_F(Test_AT_SetTmodeAutoPowerOff, Test_AT_SetTmodeAutoPowerOff_001)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;
    TAF_PH_OP_MODE_STRU    stPhModeSet;

    ucIndex = 0;

    stPhModeSet.CmdType = TAF_PH_CMD_SET;
    stPhModeSet.PhMode  = TAF_PH_MODE_POWEROFF;
    MOCKER(Taf_DefPhMode)
        .stubs()
        .with(any(), any(), mirror(&stPhModeSet, sizeof(stPhModeSet)))
        .will(returnValue(AT_SUCCESS));

    ulRet = AT_SetTmodeAutoPowerOff(ucIndex);

    ASSERT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();
}
TEST_F(Test_AT_SetTmodeAutoPowerOff, Test_AT_SetTmodeAutoPowerOff_002)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;
    TAF_PH_OP_MODE_STRU    stPhModeSet;

    ucIndex = 0;

    stPhModeSet.CmdType = TAF_PH_CMD_SET;
    stPhModeSet.PhMode  = TAF_PH_MODE_POWEROFF;
    MOCKER(Taf_DefPhMode)
        .stubs()
        .with(any(), any(), mirror(&stPhModeSet, sizeof(stPhModeSet)))
        .will(returnValue(AT_FAILURE));

    ulRet = AT_SetTmodeAutoPowerOff(ucIndex);

    ASSERT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}
#else
TEST_F(Test_AT_SetTmodeAutoPowerOff, Test_AT_SetTmodeAutoPowerOff_001)
{
    /*��������*/
    VOS_UINT8                              ucIndex;
    VOS_UINT32                             ulRet;

    ucIndex = 0;
    ulRet = AT_SetTmodeAutoPowerOff(ucIndex);

    ASSERT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();
}

#endif

#endif
class Test_AT_TestHsicCmdPara: public ::testing::Test
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


TEST_F(Test_AT_TestHsicCmdPara, Test_AT_TestHsicCmdPara_001)
{
    // ��������
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // ������ʼ��
    ucIndex = AT_CLIENT_ID_APP;

    // ��ʼ��ȫ�ֱ���;

    // MOCKER����;
    MOCKER(AT_CheckHsicUser)
        .expects(exactly(1))
        .with(eq(ucIndex))
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    // ���ñ��⺯��
    ulRet = AT_TestHsicCmdPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_TestHsicCmdPara, Test_AT_TestHsicCmdPara_002)
{
    // ��������
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    // ������ʼ��
    ucIndex = AT_CLIENT_ID_PCUI;

    // ��ʼ��ȫ�ֱ���;

    // MOCKER����;
    MOCKER(AT_CheckHsicUser)
        .expects(exactly(1))
        .with(eq(ucIndex))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    // ���ñ��⺯��
    ulRet = AT_TestHsicCmdPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}


class Test_AT_TestSimlockUnlockPara: public ::testing::Test
{
public:
    AT_PAR_CMD_ELEMENT_STRU                 stCmdInfo;
    VOS_UINT8                               ucIndex;

    void SetUp()
    {
        UT_STUB_INIT();
        ucIndex                     = AT_CLIENT_TAB_APP_INDEX;
        stCmdInfo.ulCmdIndex        = AT_CMD_SIMLOCKUNLOCK;
        stCmdInfo.pfnSetProc        = AT_SetSimlockUnlockPara;
        stCmdInfo.ulSetTimeOut      = AT_SET_PARA_TIME;
        stCmdInfo.pfnQryProc        = VOS_NULL_PTR;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.pfnTestProc       = AT_TestSimlockUnlockPara;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^SIMLOCKUNLOCK";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(\"NET\",\"NETSUB\",\"SP\"),(pwd)";
        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }

    void TearDown()
    {

    }
};


TEST_F(Test_AT_TestSimlockUnlockPara, Test_AT_TestSimlockUnlockPara_001)
{
    // ��������
    VOS_UINT32                          ulRet;

    //������ʼ��
    ucIndex         = AT_CLIENT_TAB_PCUI_INDEX;

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(AT_IsApPort)
        .expects(exactly(1))
        .with(eq(ucIndex))
        .will(returnValue((VOS_UINT32)VOS_FALSE));

    // ���ñ��⺯��
    ulRet = AT_TestSimlockUnlockPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_ERROR, ulRet);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_TestSimlockUnlockPara, Test_AT_TestSimlockUnlockPara_002)
{
    // ��������
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcExpect;

    //������ʼ��
    pcExpect        = "^SIMLOCKUNLOCK: (\"NET\",\"NETSUB\",\"SP\")";

    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(AT_IsApPort)
        .expects(exactly(1))
        .with(eq(ucIndex))
        .will(returnValue((VOS_UINT32)VOS_TRUE));

    // ���ñ��⺯��
    ulRet = AT_TestSimlockUnlockPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_OK, ulRet);
    EXPECT_EQ(VOS_StrLen(pcExpect), gstAtSendData.usBufLen);
    ASSERT_STREQ(pcExpect, (VOS_CHAR *)pgucAtSndCodeAddr);

    GlobalMockObject::verify();
}




class Test_AT_QryFPllStatusPara: public ::testing::Test
{
public:
    void SetUp()
    {
        UT_STUB_INIT();
        VOS_MemSet(&g_stAtDevCmdCtrl, 0, sizeof(g_stAtDevCmdCtrl));
    }
    void TearDown()
    {

    }
};

TEST_F(Test_AT_QryFPllStatusPara, Test_AT_QryFPllStatusPara_001)
{
    // ��������
    VOS_UINT8  ucIndex = 0;
    VOS_UINT32 ulResult; 


    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_BUTT;

    // MOCKER����

    // ���ñ��⺯��
    ulResult = AT_QryFPllStatusPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_DEVICE_MODE_ERROR, ulResult);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_QryFPllStatusPara, Test_AT_QryFPllStatusPara_002)
{
    // ��������
    VOS_UINT8  ucIndex = 0;
    VOS_UINT32 ulResult; 


    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_WCDMA;

    // MOCKER����
    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((MsgBlock *)VOS_NULL_PTR));

    // ���ñ��⺯��
    ulResult = AT_QryFPllStatusPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_ERROR, ulResult);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_QryFPllStatusPara, Test_AT_QryFPllStatusPara_003)
{
    // ��������
    VOS_UINT8  ucIndex = 0;
    VOS_UINT32 ulResult; 


    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_GSM;

    // MOCKER����
    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    // ���ñ��⺯��
    ulResult = AT_QryFPllStatusPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_ERROR, ulResult);

    GlobalMockObject::verify();
}


TEST_F(Test_AT_QryFPllStatusPara, Test_AT_QryFPllStatusPara_004)
{
    // ��������
    VOS_UINT8  ucIndex = 0;
    VOS_UINT32 ulResult; 


    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_GSM;

    // MOCKER����


    // ���ñ��⺯��
    ulResult = AT_QryFPllStatusPara(ucIndex);

    // ִ�м��
    EXPECT_EQ(AT_CMD_FPLLSTATUS_QRY, gastAtClientTab[ucIndex].CmdCurrentOpt);
    EXPECT_EQ(ucIndex, g_stAtDevCmdCtrl.ucIndex);

    GlobalMockObject::verify();
}


class Test_At_RfPllStatusCnfProc: public ::testing::Test
{
public:
    AT_PAR_CMD_ELEMENT_STRU                 stCmdInfo;
    VOS_UINT8                               ucIndex;

    void SetUp()
    {
        UT_STUB_INIT();

        MOCKER(V_StartRelTimer)
            .stubs()
            .will(returnValue((VOS_UINT32)VOS_OK));

        MOCKER(V_StopRelTimer)
            .stubs()
            .will(returnValue((VOS_UINT32)VOS_OK));
        
        ucIndex                     = AT_CLIENT_TAB_PCUI_INDEX;
        stCmdInfo.ulCmdIndex        = AT_CMD_FPLLSTATUS;
        stCmdInfo.pfnSetProc        = VOS_NULL_PTR;
        stCmdInfo.ulSetTimeOut      = AT_NOT_SET_TIME;
        stCmdInfo.pfnQryProc        = AT_QryFPllStatusPara;
        stCmdInfo.ulTestTimeOut     = AT_QRY_PARA_TIME;
        stCmdInfo.pfnTestProc       = VOS_NULL_PTR;
        stCmdInfo.ulTestTimeOut     = AT_NOT_SET_TIME;
        stCmdInfo.ulParamErrCode    = AT_CME_INCORRECT_PARAMETERS;
        stCmdInfo.ulChkFlag         = CMD_TBL_PIN_IS_LOCKED;
        stCmdInfo.pszCmdName        = (VOS_UINT8*)"^FPLLSTATUS";
        stCmdInfo.pszParam          = (VOS_UINT8 *)"(0,1),(0,1)";
        g_stParseContext[ucIndex].pstCmdElement = &stCmdInfo;
    }
    void TearDown()
    {

    }
};

TEST_F(Test_At_RfPllStatusCnfProc, Test_At_RfPllStatusCnfProc_001)
{
    // ��������
    PHY_AT_RF_PLL_STATUS_CNF_STRU   stMsg;

    // ������ʼ��

    // ��ʼ��ȫ�ֱ���
    g_stAtDevCmdCtrl.ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INVALID;

    // MOCKER����
    MOCKER(At_FormatResultData)
        .expects(never());

    // ���ñ��⺯��
    At_RfPllStatusCnfProc(&stMsg);

    // ִ�м��
    GlobalMockObject::verify();
}


TEST_F(Test_At_RfPllStatusCnfProc, Test_At_RfPllStatusCnfProc_002)
{
    // ��������
    PHY_AT_RF_PLL_STATUS_CNF_STRU   stMsg;
    VOS_CHAR                        *pcExpect = "^FPLLSTATUS: 0,1";


    // ������ʼ��
    stMsg.usTxStatus = 0;
    stMsg.usRxStatus = 1;

    // ��ʼ��ȫ�ֱ���
    g_stAtDevCmdCtrl.ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_FPLLSTATUS_QRY;

    // MOCKER����
    MOCKER(At_FormatResultData)
        .expects(exactly(1));

    // ���ñ��⺯��
    At_RfPllStatusCnfProc(&stMsg);
    EXPECT_EQ(VOS_StrLen(pcExpect), gstAtSendData.usBufLen);
    ASSERT_STREQ(pcExpect, (VOS_CHAR *)pgucAtSndCodeAddr);


    // ִ�м��
    GlobalMockObject::verify();
}
