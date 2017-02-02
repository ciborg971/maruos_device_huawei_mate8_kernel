#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_AtMsgPrint.h"


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

#if 0

TEST_F(Test_At_PrintCsmsInfo, �������ҵ��֧��ѡ��������ŷ��͹���_���Ž��չ���_�㲥���Ź���)
{
    // ��������
    VOS_UINT8                           ucIndex;

    // ������ʼ��
    ucIndex = 0;

    // ���ȫ�ֱ�����ʼ��
    g_stParseContext[ucIndex].pstCmdElement->pszCmdName = (TAF_UINT8 *)"+CSMS";

    // MOCKER����;

    // ���ñ��⺯��
    At_PrintCsmsInfo(ucIndex);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
#endif


class Test_AT_StubSendAutoReplyMsg: public ::testing::Test
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

TEST_F(Test_AT_StubSendAutoReplyMsg, Test_AT_StubSendAutoReplyMsg_01)
{
    MN_MSG_EVENT_INFO_STRU              stEvent;
    MN_MSG_TS_DATA_INFO_STRU            stTsDataInfo;

    /*Ԥ�û�����*/

    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((void *)VOS_NULL_PTR));

    EXPECT_EQ(AT_ERROR, AT_StubSendAutoReplyMsg(0, &stEvent, &stTsDataInfo));

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
TEST_F(Test_AT_StubSendAutoReplyMsg, Test_AT_StubSendAutoReplyMsg_02)
{
    MN_MSG_EVENT_INFO_STRU              stEvent;
    MN_MSG_TS_DATA_INFO_STRU            stTsDataInfo;

    /*Ԥ�û�����*/

    MOCKER(MN_MSG_Encode)
        .stubs()
        .will(returnValue(1));

    EXPECT_EQ(AT_ERROR, AT_StubSendAutoReplyMsg(0, &stEvent, &stTsDataInfo));

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
TEST_F(Test_AT_StubSendAutoReplyMsg, Test_AT_StubSendAutoReplyMsg_03)
{
    MN_MSG_EVENT_INFO_STRU              stEvent;
    MN_MSG_TS_DATA_INFO_STRU            stTsDataInfo;

    /*Ԥ�û�����*/

    MOCKER(MN_MSG_Encode)
        .stubs()
        .will(returnValue((VOS_UINT32)0));

    MOCKER(MN_MSG_Send)
        .stubs()
        .will(returnValue((VOS_UINT32)1));

    EXPECT_EQ(AT_ERROR, AT_StubSendAutoReplyMsg(0, &stEvent, &stTsDataInfo));

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
TEST_F(Test_AT_StubSendAutoReplyMsg, Test_AT_StubSendAutoReplyMsg_04)
{
    MN_MSG_EVENT_INFO_STRU              stEvent;
    MN_MSG_TS_DATA_INFO_STRU            stTsDataInfo;

    /*Ԥ�û�����*/

    MOCKER(MN_MSG_Encode)
        .stubs()
        .will(returnValue((VOS_UINT32)0));

    MOCKER(MN_MSG_Send)
        .stubs()
        .will(returnValue((VOS_UINT32)0));

    EXPECT_EQ(AT_OK, AT_StubSendAutoReplyMsg(0, &stEvent, &stTsDataInfo));

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
class Test_AT_StubTriggerAutoReply: public ::testing::Test
{
public:
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    void SetUp()
    {
        UT_STUB_INIT();

        ucIndex = 0;

        pstAtClientCtx = AT_GetClientCtxAddr(ucIndex);

        pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_0;
    }

    void TearDown()
    {
    }

};

TEST_F(Test_AT_StubTriggerAutoReply, Test_AT_StubTriggerAutoReply_01)
{
    TAF_UINT8                           ucCfgValue = 0;
    MN_MSG_EVENT_INFO_STRU              stEvent;
    MN_MSG_TS_DATA_INFO_STRU            stTsDataInfo;

    /*Ԥ�û�����*/
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed = TAF_TRUE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstEvent = &stEvent;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstTsDataInfo = &stTsDataInfo;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed = TAF_TRUE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstEvent = &stEvent;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstTsDataInfo = &stTsDataInfo;

    MOCKER(V_MemFree)
        .expects(exactly(4))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_StubSendAutoReplyMsg)
        .expects(never())
        .will(returnValue((TAF_UINT32)AT_OK));

    AT_StubTriggerAutoReply(ucIndex, ucCfgValue);

    EXPECT_EQ(TAF_FALSE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed);
    EXPECT_EQ(TAF_FALSE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
TEST_F(Test_AT_StubTriggerAutoReply, Test_AT_StubTriggerAutoReply_02)
{
    TAF_UINT8                           ucCfgValue = 1;

    /*Ԥ�û�����*/
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed = TAF_FALSE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstEvent = (MN_MSG_EVENT_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed = TAF_FALSE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstEvent = (MN_MSG_EVENT_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)0;

    MOCKER(AT_StubSendAutoReplyMsg)
        .expects(never())
        .will(returnValue((TAF_UINT32)AT_OK));

    AT_StubTriggerAutoReply(ucIndex, ucCfgValue);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
TEST_F(Test_AT_StubTriggerAutoReply, Test_AT_StubTriggerAutoReply_03)
{
    TAF_UINT8                           ucCfgValue = 1;
    MN_MSG_EVENT_INFO_STRU              stEvent;
    MN_MSG_TS_DATA_INFO_STRU            stTsDataInfo;

    /*Ԥ�û�����*/
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed = TAF_TRUE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstEvent = (MN_MSG_EVENT_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)&stTsDataInfo;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed = TAF_TRUE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstEvent = (MN_MSG_EVENT_INFO_STRU *)&stEvent;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)0;

    MOCKER(V_MemFree)
        .expects(exactly(2))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_StubSendAutoReplyMsg)
        .expects(never())
        .will(returnValue((TAF_UINT32)AT_OK));

    AT_StubTriggerAutoReply(ucIndex, ucCfgValue);

    EXPECT_EQ(TAF_FALSE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed);
    EXPECT_EQ(TAF_FALSE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed);
    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
TEST_F(Test_AT_StubTriggerAutoReply, Test_AT_StubTriggerAutoReply_04)
{
    TAF_UINT8                           ucCfgValue = 1;
    MN_MSG_EVENT_INFO_STRU              stEvent;
    MN_MSG_TS_DATA_INFO_STRU            stTsDataInfo;

    /*Ԥ�û�����*/
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed = TAF_TRUE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstEvent = &stEvent;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstTsDataInfo = &stTsDataInfo;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed = TAF_TRUE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstEvent = &stEvent;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstTsDataInfo = &stTsDataInfo;

    MOCKER(V_MemFree)
        .expects(exactly(2))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(AT_StubSendAutoReplyMsg)
        .expects(exactly(1))
        .will(returnValue((TAF_UINT32)AT_OK));

    AT_StubTriggerAutoReply(ucIndex, ucCfgValue);

    EXPECT_EQ(TAF_FALSE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed);
    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
TEST_F(Test_AT_StubTriggerAutoReply, Test_AT_StubTriggerAutoReply_05)
{
    TAF_UINT8                           ucCfgValue = 1;

    /*Ԥ�û�����*/
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed = TAF_FALSE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstEvent = (MN_MSG_EVENT_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed = TAF_FALSE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstEvent = (MN_MSG_EVENT_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)0;

    MOCKER(AT_StubSendAutoReplyMsg)
        .expects(never())
        .will(returnValue((TAF_UINT32)AT_OK));

    AT_StubTriggerAutoReply(ucIndex, ucCfgValue);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
class Test_AT_StubSaveAutoReplyData: public ::testing::Test
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

TEST_F(Test_AT_StubSaveAutoReplyData, Test_AT_StubSaveAutoReplyData_01)
{
    MN_MSG_EVENT_INFO_STRU              stEvent;
    MN_MSG_TS_DATA_INFO_STRU            stTsDataInfo;

    /*Ԥ�û�����*/
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->ucSmsAutoReply = 0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed = TAF_FALSE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstEvent = (MN_MSG_EVENT_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed = TAF_FALSE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstEvent = (MN_MSG_EVENT_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)0;

    AT_StubSaveAutoReplyData(0, &stEvent, &stTsDataInfo);

    EXPECT_EQ(TAF_FALSE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed);
    EXPECT_EQ(TAF_FALSE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed);
    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
TEST_F(Test_AT_StubSaveAutoReplyData, Test_AT_StubSaveAutoReplyData_02)
{
    MN_MSG_EVENT_INFO_STRU              stEvent;
    MN_MSG_TS_DATA_INFO_STRU            stTsDataInfo;

    /*Ԥ�û�����*/
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->ucSmsAutoReply = 1;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed = TAF_FALSE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstEvent = (MN_MSG_EVENT_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed = TAF_FALSE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstEvent = (MN_MSG_EVENT_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)0;

    stTsDataInfo.enTpduType = MN_MSG_TPDU_STARPT;
    stTsDataInfo.u.stDeliver.bReplayPath  = VOS_FALSE;

    AT_StubSaveAutoReplyData(0, &stEvent, &stTsDataInfo);

    EXPECT_EQ(TAF_FALSE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed);
    EXPECT_EQ(TAF_FALSE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed);
    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
TEST_F(Test_AT_StubSaveAutoReplyData, Test_AT_StubSaveAutoReplyData_03)
{
    MN_MSG_EVENT_INFO_STRU              stEvent;
    MN_MSG_TS_DATA_INFO_STRU            stTsDataInfo;

    /*Ԥ�û�����*/
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->ucSmsAutoReply = 1;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed = TAF_FALSE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstEvent = (MN_MSG_EVENT_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed = TAF_FALSE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstEvent = (MN_MSG_EVENT_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)0;

    MOCKER(V_MemAlloc)
        .stubs()
        .will(returnValue((void *)VOS_NULL_PTR));

    stTsDataInfo.enTpduType = MN_MSG_TPDU_DELIVER;
    stTsDataInfo.u.stDeliver.bReplayPath  = VOS_TRUE;

    AT_StubSaveAutoReplyData(0, &stEvent, &stTsDataInfo);

    EXPECT_EQ(TAF_FALSE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed);
    EXPECT_EQ(TAF_FALSE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed);
    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
TEST_F(Test_AT_StubSaveAutoReplyData, Test_AT_StubSaveAutoReplyData_04)
{
    MN_MSG_EVENT_INFO_STRU              stEvent;
    MN_MSG_TS_DATA_INFO_STRU            stTsDataInfo;
    MN_MSG_EVENT_INFO_STRU             *pstMsgEventInfo;


    /*Ԥ�û�����*/
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->ucSmsAutoReply = 1;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed = TAF_FALSE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstEvent = (MN_MSG_EVENT_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed = TAF_FALSE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstEvent = (MN_MSG_EVENT_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)0;

    pstMsgEventInfo = (MN_MSG_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(MN_MSG_EVENT_INFO_STRU));

    MOCKER(V_MemAlloc)
        .expects(exactly(2))
        .will(returnObjectList((void *)pstMsgEventInfo, (void *)VOS_NULL_PTR));


    stTsDataInfo.enTpduType = MN_MSG_TPDU_DELIVER;
    stTsDataInfo.u.stDeliver.bReplayPath  = VOS_TRUE;

    AT_StubSaveAutoReplyData(0, &stEvent, &stTsDataInfo);

    EXPECT_EQ(TAF_FALSE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed);
    EXPECT_EQ(TAF_FALSE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
TEST_F(Test_AT_StubSaveAutoReplyData, Test_AT_StubSaveAutoReplyData_05)
{
    MN_MSG_EVENT_INFO_STRU              stEvent;
    MN_MSG_TS_DATA_INFO_STRU            stTsDataInfo;

    /*Ԥ�û�����*/
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->ucSmsAutoReply = 1;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed = TAF_TRUE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstEvent = &stEvent;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstTsDataInfo = &stTsDataInfo;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed = TAF_FALSE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstEvent = (MN_MSG_EVENT_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)0;

    stTsDataInfo.enTpduType = MN_MSG_TPDU_DELIVER;
    stTsDataInfo.u.stDeliver.bReplayPath  = VOS_TRUE;

    AT_StubSaveAutoReplyData(0, &stEvent, &stTsDataInfo);

    EXPECT_EQ(TAF_TRUE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed);
    EXPECT_EQ(TAF_TRUE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed);
    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
TEST_F(Test_AT_StubSaveAutoReplyData, Test_AT_StubSaveAutoReplyData_06)
{
    MN_MSG_EVENT_INFO_STRU              stEvent;
    MN_MSG_TS_DATA_INFO_STRU            stTsDataInfo;

    /*Ԥ�û�����*/
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->ucSmsAutoReply = 1;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed = TAF_TRUE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstEvent = &stEvent;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].pstTsDataInfo = &stTsDataInfo;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed = TAF_TRUE;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstEvent = (MN_MSG_EVENT_INFO_STRU *)0;
    AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)0;

    stTsDataInfo.enTpduType = MN_MSG_TPDU_DELIVER;
    stTsDataInfo.u.stDeliver.bReplayPath  = VOS_TRUE;

    AT_StubSaveAutoReplyData(0, &stEvent, &stTsDataInfo);

    EXPECT_EQ(TAF_TRUE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[0].bUsed);
    EXPECT_EQ(TAF_TRUE, AT_GetModemSmsCtxAddrFromModemId(MODEM_ID_0)->astSmsMtBuffer[1].bUsed);
    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
class Test_AT_SetAbsoluteValidPeriod: public ::testing::Test
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

TEST_F(Test_AT_SetAbsoluteValidPeriod, Test_AT_SetAbsoluteValidPeriod_01)
{
    TAF_UINT8                           aucPara[] = "\"94/05/06,22:10:00+08\"";
    TAF_UINT16                          usParaLen = 0;
    MN_MSG_VALID_PERIOD_STRU            stValidPeriod;
    TAF_UINT32                          ulRet;

    AT_GetModemSmsCtxAddrFromClientId(0)->stCscaCsmpInfo.stVp.enValidPeriod = MN_MSG_VALID_PERIOD_ABSOLUTE;

    ulRet = AT_SetAbsoluteValidPeriod(0, aucPara, usParaLen, &stValidPeriod);

    EXPECT_EQ(AT_SUCCESS, ulRet);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetAbsoluteValidPeriod, Test_AT_SetAbsoluteValidPeriod_02)
{
    TAF_UINT8                           aucPara[] = "\"94/05/06,22:10:00+08\"";
    TAF_UINT16                          usParaLen = 0;
    MN_MSG_VALID_PERIOD_STRU            stValidPeriod;
    TAF_UINT32                          ulRet;

    AT_GetModemSmsCtxAddrFromClientId(0)->stCscaCsmpInfo.stVp.enValidPeriod = MN_MSG_VALID_PERIOD_RELATIVE;

    ulRet = AT_SetAbsoluteValidPeriod(0, aucPara, usParaLen, &stValidPeriod);

    EXPECT_EQ(AT_ERROR, ulRet);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetAbsoluteValidPeriod, Test_AT_SetAbsoluteValidPeriod_03)
{
    TAF_UINT8                           aucPara[] = "\"94/05/06,22:10:00+08\"";
    TAF_UINT16                          usParaLen = sizeof(aucPara) - 1;
    MN_MSG_VALID_PERIOD_STRU            stValidPeriod;
    TAF_UINT32                          ulRet;

    AT_GetModemSmsCtxAddrFromClientId(0)->stCscaCsmpInfo.stVp.enValidPeriod = MN_MSG_VALID_PERIOD_RELATIVE;

    ulRet = AT_SetAbsoluteValidPeriod(0, aucPara, usParaLen, &stValidPeriod);

    EXPECT_EQ(AT_SUCCESS, ulRet);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetAbsoluteValidPeriod, Test_AT_SetAbsoluteValidPeriod_04)
{
    TAF_UINT8                           aucPara[] = "\"94//05/06,22:10:00+08\"";
    TAF_UINT16                          usParaLen = sizeof(aucPara) - 1;
    MN_MSG_VALID_PERIOD_STRU            stValidPeriod;
    TAF_UINT32                          ulRet;

    AT_GetModemSmsCtxAddrFromClientId(0)->stCscaCsmpInfo.stVp.enValidPeriod = MN_MSG_VALID_PERIOD_RELATIVE;

    ulRet = AT_SetAbsoluteValidPeriod(0, aucPara, usParaLen, &stValidPeriod);

    EXPECT_EQ(AT_CMS_OPERATION_NOT_ALLOWED, ulRet);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetAbsoluteValidPeriod, Test_AT_SetAbsoluteValidPeriod_05)
{
    TAF_UINT8                           aucPara[] = "\"14/20/06,22:10:00+08\"";
    TAF_UINT16                          usParaLen = sizeof(aucPara) - 1;
    MN_MSG_VALID_PERIOD_STRU            stValidPeriod;
    TAF_UINT32                          ulRet;

    AT_GetModemSmsCtxAddrFromClientId(0)->stCscaCsmpInfo.stVp.enValidPeriod = MN_MSG_VALID_PERIOD_RELATIVE;

    ulRet = AT_SetAbsoluteValidPeriod(0, aucPara, usParaLen, &stValidPeriod);

    EXPECT_EQ(AT_CMS_OPERATION_NOT_ALLOWED, ulRet);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_AT_SetRelativeValidPeriod: public ::testing::Test
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

TEST_F(Test_AT_SetRelativeValidPeriod, Test_AT_SetRelativeValidPeriod_01)
{
    TAF_UINT8                           aucPara[] = "1235";
    TAF_UINT16                          usParaLen = 0;
    MN_MSG_VALID_PERIOD_STRU            stValidPeriod;
    TAF_UINT32                          ulRet;

    AT_GetModemSmsCtxAddrFromClientId(0)->stCscaCsmpInfo.stVp.enValidPeriod = MN_MSG_VALID_PERIOD_RELATIVE;

    ulRet = AT_SetRelativeValidPeriod(0, aucPara, usParaLen, &stValidPeriod);

    EXPECT_EQ(AT_SUCCESS, ulRet);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetRelativeValidPeriod, Test_AT_SetRelativeValidPeriod_02)
{
    TAF_UINT8                           aucPara[] = "A4//05/06,22:10:00+08";
    TAF_UINT16                          usParaLen = 0;
    MN_MSG_VALID_PERIOD_STRU            stValidPeriod;
    TAF_UINT32                          ulRet;

    AT_GetModemSmsCtxAddrFromClientId(0)->stCscaCsmpInfo.stVp.enValidPeriod = MN_MSG_VALID_PERIOD_NONE;

    ulRet = AT_SetRelativeValidPeriod(0, aucPara, usParaLen, &stValidPeriod);

    EXPECT_EQ(AT_SUCCESS, ulRet);
    EXPECT_EQ(167, stValidPeriod.u.ucOtherTime);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetRelativeValidPeriod, Test_AT_SetRelativeValidPeriod_03)
{
    TAF_UINT8                           aucPara[] = "A4//05/06,22:10:00+08";
    TAF_UINT16                          usParaLen = 0;
    MN_MSG_VALID_PERIOD_STRU            stValidPeriod;
    TAF_UINT32                          ulRet;

    AT_GetModemSmsCtxAddrFromClientId(0)->stCscaCsmpInfo.stVp.enValidPeriod = MN_MSG_VALID_PERIOD_ABSOLUTE;

    ulRet = AT_SetRelativeValidPeriod(0, aucPara, usParaLen, &stValidPeriod);

    EXPECT_EQ(AT_ERROR, ulRet);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetRelativeValidPeriod, Test_AT_SetRelativeValidPeriod_04)
{
    TAF_UINT8                           aucPara[] = "abc";
    TAF_UINT16                          usParaLen = sizeof(aucPara) - 1;
    MN_MSG_VALID_PERIOD_STRU            stValidPeriod;
    TAF_UINT32                          ulRet;

    ulRet = AT_SetRelativeValidPeriod(0, aucPara, usParaLen, &stValidPeriod);

    EXPECT_EQ(AT_CMS_OPERATION_NOT_ALLOWED, ulRet);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetRelativeValidPeriod, Test_AT_SetRelativeValidPeriod_05)
{
    TAF_UINT8                           aucPara[] = "1234567890123";
    TAF_UINT16                          usParaLen = sizeof(aucPara) - 1;
    MN_MSG_VALID_PERIOD_STRU            stValidPeriod;
    TAF_UINT32                          ulRet;

    ulRet = AT_SetRelativeValidPeriod(0, aucPara, usParaLen, &stValidPeriod);

    EXPECT_EQ(AT_CMS_OPERATION_NOT_ALLOWED, ulRet);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetRelativeValidPeriod, Test_AT_SetRelativeValidPeriod_06)
{
    TAF_UINT8                           aucPara[] = "1234";
    TAF_UINT16                          usParaLen = sizeof(aucPara) - 1;
    MN_MSG_VALID_PERIOD_STRU            stValidPeriod;
    TAF_UINT32                          ulRet;

    ulRet = AT_SetRelativeValidPeriod(0, aucPara, usParaLen, &stValidPeriod);

    EXPECT_EQ(AT_CMS_OPERATION_NOT_ALLOWED, ulRet);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetRelativeValidPeriod, Test_AT_SetRelativeValidPeriod_07)
{
    TAF_UINT8                           aucPara[] = "123";
    TAF_UINT16                          usParaLen = sizeof(aucPara)-1;
    MN_MSG_VALID_PERIOD_STRU            stValidPeriod;
    TAF_UINT32                          ulRet;

    ulRet = AT_SetRelativeValidPeriod(0, aucPara, usParaLen, &stValidPeriod);

    EXPECT_EQ(AT_SUCCESS, ulRet);
    EXPECT_EQ(123, stValidPeriod.u.ucOtherTime);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

class Test_At_ParseCsmpVp: public ::testing::Test
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


TEST_F(Test_At_ParseCsmpVp, Test_At_ParseCsmpVp_001)
{
    MN_MSG_VALID_PERIOD_STRU            stValidPeriod;
    TAF_UINT32                          ulRet;

    gastAtParaList[0].usParaLen = 0;
    AT_GetModemSmsCtxAddrFromClientId(0)->stCscaCsmpInfo.stVp.enValidPeriod = MN_MSG_VALID_PERIOD_RELATIVE;
    gastAtParaList[1].usParaLen = sizeof("123") - 1;
    PS_MEM_CPY(gastAtParaList[1].aucPara, "123", gastAtParaList[1].usParaLen);
    ulRet = At_ParseCsmpVp(0,&stValidPeriod);

    EXPECT_EQ(AT_SUCCESS, ulRet);
    EXPECT_EQ(123, stValidPeriod.u.ucOtherTime);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_ParseCsmpVp, Test_At_ParseCsmpVp_002)
{
    MN_MSG_VALID_PERIOD_STRU            stValidPeriod;
    TAF_UINT32                          ulRet;

    gastAtParaList[0].usParaLen = 0;
    AT_GetModemSmsCtxAddrFromClientId(0)->stCscaCsmpInfo.stVp.enValidPeriod = MN_MSG_VALID_PERIOD_ABSOLUTE;
    gastAtParaList[1].usParaLen = sizeof("\"94/05/06,22:10:00+08\"") - 1;
    PS_MEM_CPY(gastAtParaList[1].aucPara, "\"94/05/06,22:10:00+08\"", gastAtParaList[1].usParaLen);
    ulRet = At_ParseCsmpVp(0, &stValidPeriod);

    EXPECT_EQ(AT_SUCCESS, ulRet);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_ParseCsmpVp,Test_At_ParseCsmpVp_003)
{
    //��������
    VOS_UINT8                           ucIndex = 0;
    MN_MSG_VALID_PERIOD_STRU            stVp;
    TAF_UINT32                          ulRet;

    // ������ʼ��
    stVp.enValidPeriod = MN_MSG_VALID_PERIOD_RELATIVE;

    // ���ȫ�ֱ�����ʼ��
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCscaCsmpInfo.stVp.enValidPeriod = MN_MSG_VALID_PERIOD_NONE;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[1].usParaLen = 0;

    //MOCKER����

    //���ñ��⺯��
    ulRet = At_ParseCsmpVp(ucIndex, &stVp);

    //ִ�м��
    EXPECT_EQ(AT_SUCCESS, ulRet);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_ParseCsmpVp,Test_At_ParseCsmpVp_004)
{
    //��������
    VOS_UINT8                           ucIndex = 0;
    MN_MSG_VALID_PERIOD_STRU            stVp;
    TAF_UINT32                          ulRet;

    // ������ʼ��

    // ���ȫ�ֱ�����ʼ��
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCscaCsmpInfo.stVp.enValidPeriod = MN_MSG_VALID_PERIOD_RELATIVE;
    gastAtParaList[0].usParaLen = 0;
    gastAtParaList[1].usParaLen = sizeof("\"94/05/06,22:10:00+08\"") - 1;
    PS_MEM_CPY(gastAtParaList[1].aucPara, "\"94/05/06,22:10:00+08\"", gastAtParaList[1].usParaLen);

    //MOCKER����

    //���ñ��⺯��
    ulRet = At_ParseCsmpVp(ucIndex, &stVp);

    //ִ�м��
    EXPECT_EQ(AT_CMS_OPERATION_NOT_ALLOWED, ulRet);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_ParseCsmpVp,Test_At_ParseCsmpVp_005)
{
    //��������
    VOS_UINT8                           ucIndex = 0;
    MN_MSG_VALID_PERIOD_STRU            stVp;
    TAF_UINT32                          ulRet;

    // ������ʼ��

    // ���ȫ�ֱ�����ʼ��
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    gastAtParaList[0].usParaLen = 0;
    gastAtParaList[1].usParaLen = 0;

    //MOCKER����

    //���ñ��⺯��
    ulRet = At_ParseCsmpVp(ucIndex, &stVp);

    //ִ�м��
    EXPECT_EQ(AT_SUCCESS, ulRet);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_ParseCsmpVp,Test_At_ParseCsmpVp_006)
{
    //��������
    VOS_UINT8                           ucIndex = 0;
    MN_MSG_VALID_PERIOD_STRU            stVp;
    TAF_UINT32                          ulRet;

    // ������ʼ��
    stVp.enValidPeriod = MN_MSG_VALID_PERIOD_NONE;

    // ���ȫ�ֱ�����ʼ��
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCscaCsmpInfo.stVp.enValidPeriod = MN_MSG_VALID_PERIOD_RELATIVE;
    gastAtParaList[0].usParaLen = 1;
    gastAtParaList[1].usParaLen = 0;

    //MOCKER����

    //���ñ��⺯��
    ulRet = At_ParseCsmpVp(ucIndex, &stVp);

    //ִ�м��
    EXPECT_EQ(AT_SUCCESS, ulRet);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_ParseCsmpVp,Test_At_ParseCsmpVp_007)
{
    //��������
    VOS_UINT8                           ucIndex = 0;
    MN_MSG_VALID_PERIOD_STRU            stVp;
    TAF_UINT32                          ulRet;

    // ������ʼ��

    // ���ȫ�ֱ�����ʼ��
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCscaCsmpInfo.stVp.enValidPeriod = MN_MSG_VALID_PERIOD_RELATIVE;
    gastAtParaList[0].usParaLen = 0;
    gastAtParaList[1].usParaLen = sizeof("\"94/05/06,22:10:00+08\"") - 1;
    PS_MEM_CPY(gastAtParaList[1].aucPara, "\"94/05/06,22:10:00+08\"", gastAtParaList[1].usParaLen);

    //MOCKER����
    MOCKER(At_CheckNumString)
        .stubs()
        .will(returnValue((TAF_UINT32)AT_SUCCESS));

    //���ñ��⺯��
    ulRet = At_ParseCsmpVp(ucIndex, &stVp);

    //ִ�м��
    EXPECT_EQ(AT_CMS_OPERATION_NOT_ALLOWED, ulRet);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_ParseCsmpVp,Test_At_ParseCsmpVp_008)
{
    //��������
    VOS_UINT8                           ucIndex = 0;
    MN_MSG_VALID_PERIOD_STRU            stVp;
    TAF_UINT32                          ulRet;

    // ������ʼ��

    // ���ȫ�ֱ�����ʼ��
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    gastAtParaList[0].usParaLen = 0;
    gastAtParaList[1].usParaLen = 0;

    //MOCKER����

    //���ñ��⺯��
    ulRet = At_ParseCsmpVp(ucIndex, &stVp);

    //ִ�м��
    EXPECT_EQ(AT_SUCCESS, ulRet);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
#endif

class Test_AT_PrintTimeZone: public ::testing::Test
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

TEST_F(Test_AT_PrintTimeZone, Test_AT_PrintTimeZone_01)
{
    TAF_INT8                            cTimezone = -12;
    TAF_UINT16                          usLength;

    PS_MEM_SET(pgucAtSndCodeAddr, 0x00, 10);

/*  MOCKER(At_sprintf)
        .with(any(), any(), any(), eq("-"))
        .expects(exactly(1));

    MOCKER(At_sprintf)
        .with(any(), any(), any(), any(), eq(1), eq(2))
        .expects(exactly(1));*/

    AT_PrintTimeZone(cTimezone, pgucAtSndCodeAddr, &usLength);

/*  EXPECT_EQ('-', pgucAtSndCodeAddr[0]);
    EXPECT_EQ('1', pgucAtSndCodeAddr[1]);
    EXPECT_EQ('2', pgucAtSndCodeAddr[2]);*/
    EXPECT_EQ(4, usLength);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_AT_PrintTimeZone, Test_AT_PrintTimeZone_02)
{
    TAF_INT8                            cTimezone = 49;
    TAF_UINT16                          usLength;

    PS_MEM_SET(pgucAtSndCodeAddr, 0x00, 10);

    AT_PrintTimeZone(cTimezone, pgucAtSndCodeAddr, &usLength);

    EXPECT_EQ(4, usLength);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_At_SmsPrintScts: public ::testing::Test
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

TEST_F(Test_At_SmsPrintScts, Test_At_SmsPrintScts_01)
{
    MN_MSG_TIMESTAMP_STRU         stTimeStamp;

    stTimeStamp.ucYear = 0xa0;
    stTimeStamp.ucMonth = 0x31;
    stTimeStamp.ucDay = 0x40;
    stTimeStamp.ucHour = 0x24;
    stTimeStamp.ucMinute = 0x60;
    stTimeStamp.ucSecond = 0x60;

    PS_MEM_SET(pgucAtSndCodeAddr, 0x00, 50);

    At_SmsPrintScts(&stTimeStamp, pgucAtSndCodeAddr);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_At_SmsPrintScts, Test_At_SmsPrintScts_02)
{
    MN_MSG_TIMESTAMP_STRU         stTimeStamp;

    stTimeStamp.ucYear = 0x10;
    stTimeStamp.ucMonth = 0x04;
    stTimeStamp.ucDay = 0x11;
    stTimeStamp.ucHour = 0x17;
    stTimeStamp.ucMinute = 0x00;
    stTimeStamp.ucSecond = 0x00;

    PS_MEM_SET(pgucAtSndCodeAddr, 0x00, 50);

    At_SmsPrintScts(&stTimeStamp, pgucAtSndCodeAddr);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_At_PrintAddrType: public ::testing::Test
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
#if 0

TEST_F(Test_At_PrintAddrType, Test_At_PrintAddrType_001)
{
    /*��������*/
    MN_MSG_ASCII_ADDR_STRU              stAddr;
    TAF_UINT8                           aucDst[1];
    TAF_UINT16                          usLength;
    TAF_UINT8                           ucCmpAddrType;

    /* ��ʼ������ */
    memset(&stAddr, 0, sizeof(stAddr));
    stAddr.enNumPlan = MN_MSG_NPI_ISDN;
    stAddr.enNumType = MN_MSG_TON_UNKNOWN;
    aucDst[0] = 0;
    ucCmpAddrType    = 0x81;

    /* ȫ�ֱ�����ֵ */

    /* ������Ϣ��ں��� */
    usLength = At_PrintAddrType(&stAddr, aucDst);

    /* �����֤*/

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}
#endif


class Test_AT_StubClearSpecificAutoRelyMsg: public ::testing::Test
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


TEST_F(Test_AT_StubClearSpecificAutoRelyMsg,Test_AT_StubClearSpecificAutoRelyMsg_001)
{
    // ��������
    VOS_UINT8                           ucClientIndex = 0;
    TAF_UINT32                          ulBufferIndex = 0;
    MN_MSG_EVENT_INFO_STRU              *pstEvent;
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo;

    // ������ʼ��
    pstEvent = (MN_MSG_EVENT_INFO_STRU *)malloc(sizeof(MN_MSG_EVENT_INFO_STRU));
    pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)malloc(sizeof(MN_MSG_TS_DATA_INFO_STRU));

    // ���ȫ�ֱ�����ʼ��
    g_astAtClientCtx[ucClientIndex].stClientConfiguration.enModemId = MODEM_ID_0;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.astSmsMtBuffer[ulBufferIndex].pstEvent = pstEvent;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.astSmsMtBuffer[ulBufferIndex].pstTsDataInfo = pstTsDataInfo;
    // MOCKER����

    // ���ñ��⺯��
    AT_StubClearSpecificAutoRelyMsg(ucClientIndex, ulBufferIndex);

    // ִ�м��

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_AT_StubClearSpecificAutoRelyMsg,Test_AT_StubClearSpecificAutoRelyMsg_002)
{
    // ��������
    VOS_UINT8                           ucClientIndex = 0;
    TAF_UINT32                          ulBufferIndex = 0;
    MN_MSG_EVENT_INFO_STRU              *pstEvent;
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo;

    // ������ʼ��
    pstEvent = (MN_MSG_EVENT_INFO_STRU *)malloc(sizeof(MN_MSG_EVENT_INFO_STRU));
    pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)malloc(sizeof(MN_MSG_TS_DATA_INFO_STRU));

    // ���ȫ�ֱ�����ʼ��
    g_astAtClientCtx[ucClientIndex].stClientConfiguration.enModemId = MODEM_ID_1;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.astSmsMtBuffer[ulBufferIndex].pstEvent = pstEvent;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.astSmsMtBuffer[ulBufferIndex].pstTsDataInfo = pstTsDataInfo;

    // MOCKER����

    // ���ñ��⺯��
    AT_StubClearSpecificAutoRelyMsg(ucClientIndex, ulBufferIndex);


    // ִ�м��

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
#endif


class Test_At_PrintGetCpmsRsp: public ::testing::Test
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


TEST_F(Test_At_PrintGetCpmsRsp,Test_At_PrintGetCpmsRsp_001)
{
    // ��������
    VOS_UINT8                           ucIndex = 0;
    VOS_CHAR                            acExpectedStr[] = "+CPMS: \"SM\",0,16,\"SM\",0,16,\"SM\",0,16";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_CPMS,
                                                        At_SetCpmsPara,     AT_SET_PARA_TIME,
                                                        At_QryCpmsPara,     AT_QRY_PARA_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"+CPMS",    (VOS_UINT8*)"(\"SM\"),(\"SM\"),(\"SM\")"};

    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;
    // ������ʼ��
    ucIndex = AT_CLIENT_TAB_APP_INDEX;

    // ���ȫ�ֱ�����ʼ��
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;
    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    pstSmsCtx->stCpmsInfo.enMemReadorDelete = MN_MSG_MEM_STORE_SIM;
    pstSmsCtx->stCpmsInfo.enMemSendorWrite  = MN_MSG_MEM_STORE_SIM;
    pstSmsCtx->stCpmsInfo.stRcvPath.enSmMemStore = MN_MSG_MEM_STORE_SIM;
    pstSmsCtx->stCpmsInfo.stUsimStorage.ulTotalRec = 16;
    pstSmsCtx->stCpmsInfo.stUsimStorage.ulUsedRec  = 0;

    // MOCKER����
    MOCKER(At_FormatResultData)
        .stubs()
        .with(any(), eq((VOS_UINT32)AT_OK));

    // ���ñ��⺯��
    At_PrintGetCpmsRsp(ucIndex);

    // ִ�м��
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)

TEST_F(Test_At_PrintGetCpmsRsp,Test_At_PrintGetCpmsRsp_002)
{
    // ��������
    VOS_UINT8                           ucIndex = 0;
    VOS_CHAR                            acExpectedStr[] = "+CPMS: \"ME\",0,16,\"ME\",0,16,\"ME\",0,16";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_CPMS,
                                                        At_SetCpmsPara,     AT_SET_PARA_TIME,
                                                        At_QryCpmsPara,     AT_QRY_PARA_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"+CPMS",    (VOS_UINT8*)"(\"SM\",\"c\"),(\"SM\",\"ME\"),(\"SM\",\"ME\")"};

    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;
    // ������ʼ��
    ucIndex = AT_CLIENT_TAB_APP_INDEX;

    // ���ȫ�ֱ�����ʼ��
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;
    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    pstSmsCtx->stCpmsInfo.enMemReadorDelete = MN_MSG_MEM_STORE_NV;
    pstSmsCtx->stCpmsInfo.enMemSendorWrite  = MN_MSG_MEM_STORE_NV;
    pstSmsCtx->stCpmsInfo.stRcvPath.enSmMemStore = MN_MSG_MEM_STORE_NV;
    pstSmsCtx->stCpmsInfo.stNvimStorage.ulTotalRec = 16;
    pstSmsCtx->stCpmsInfo.stNvimStorage.ulUsedRec  = 0;

    // MOCKER����
    MOCKER(At_FormatResultData)
        .stubs()
        .with(any(), eq((VOS_UINT32)AT_OK));

    // ���ñ��⺯��
    At_PrintGetCpmsRsp(ucIndex);

    // ִ�м��
    ASSERT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}
#endif
#endif


class Test_At_PrintSetCpmsRsp: public ::testing::Test
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


TEST_F(Test_At_PrintSetCpmsRsp,Test_At_PrintSetCpmsRsp_001)
{
    // ��������
    TAF_UINT8                           ucIndex;
    VOS_CHAR                            acExpectedStr[] = "+CPMS: 0,16,0,16,0,16";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_CPMS,
                                                        At_SetCpmsPara,     AT_SET_PARA_TIME,
                                                        At_QryCpmsPara,     AT_QRY_PARA_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"+CPMS",    (VOS_UINT8*)"(\"SM\"),(\"SM\"),(\"SM\")"};
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    // ������ʼ��
    ucIndex = AT_CLIENT_TAB_APP_INDEX;

    // ���ȫ�ֱ�����ʼ��
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;
    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    pstSmsCtx->stCpmsInfo.enMemReadorDelete = MN_MSG_MEM_STORE_SIM;
    pstSmsCtx->stCpmsInfo.enMemSendorWrite  = MN_MSG_MEM_STORE_SIM;
    pstSmsCtx->stCpmsInfo.stRcvPath.enSmMemStore = MN_MSG_MEM_STORE_SIM;
    pstSmsCtx->stCpmsInfo.stUsimStorage.ulTotalRec = 16;
    pstSmsCtx->stCpmsInfo.stUsimStorage.ulUsedRec  = 0;

    // MOCKER����
    MOCKER(At_FormatResultData)
        .stubs()
        .with(any(), eq((VOS_UINT32)AT_OK));

    // ���ñ��⺯��
    At_PrintSetCpmsRsp(ucIndex);

    // ִ�м��
    EXPECT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_PrintSetCpmsRsp,Test_At_PrintSetCpmsRsp_002)
{
    // ��������
    TAF_UINT8                           ucIndex;
    VOS_CHAR                            acExpectedStr[] = "+CPMS: 0,16,0,16,0,16";
    AT_PAR_CMD_ELEMENT_STRU             stCmdElement = {AT_CMD_CPMS,
                                                        At_SetCpmsPara,     AT_SET_PARA_TIME,
                                                        At_QryCpmsPara,     AT_QRY_PARA_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        VOS_NULL_PTR,       AT_NOT_SET_TIME,
                                                        AT_CMS_OPERATION_NOT_ALLOWED, CMD_TBL_LIMITED_NULL,
                                                        (VOS_UINT8*)"+CPMS",    (VOS_UINT8*)"(\"SM\"),(\"SM\"),(\"SM\")"};
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    // ������ʼ��
    ucIndex = AT_CLIENT_TAB_APP_INDEX;

    // ���ȫ�ֱ�����ʼ��
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    g_stParseContext[ucIndex].pstCmdElement                     = &stCmdElement;
    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    pstSmsCtx->stCpmsInfo.enMemReadorDelete = MN_MSG_MEM_STORE_SIM;
    pstSmsCtx->stCpmsInfo.enMemSendorWrite  = MN_MSG_MEM_STORE_SIM;
    pstSmsCtx->stCpmsInfo.stRcvPath.enSmMemStore = MN_MSG_MEM_STORE_SIM;
    pstSmsCtx->stCpmsInfo.stUsimStorage.ulTotalRec = 16;
    pstSmsCtx->stCpmsInfo.stUsimStorage.ulUsedRec  = 0;

    // MOCKER����
    MOCKER(At_FormatResultData)
        .stubs()
        .with(any(), eq((VOS_UINT32)AT_OK));

    // ���ñ��⺯��
    At_PrintSetCpmsRsp(ucIndex);

    // ִ�м��
    EXPECT_STREQ(acExpectedStr, (VOS_CHAR *)pgucAtSndCodeAddr);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
#endif


class Test_At_SendMsgFoAttr: public ::testing::Test
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


TEST_F(Test_At_SendMsgFoAttr,Test_At_SendMsgFoAttr_001)
{
    // ��������
    VOS_UINT8                           ucIndex = 0;
    MN_MSG_TS_DATA_INFO_STRU            stTsDataInfo;

    // ������ʼ��
    stTsDataInfo.enTpduType = MN_MSG_TPDU_COMMAND;

    // ���ȫ�ֱ�����ʼ��
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_0;
    gastAtClientTab[ucIndex].CmdCurrentOpt                      = AT_CMD_CMGC_PDU_SET;
    g_astAtModemCtx[MODEM_ID_0].stSmsCtx.stCscaCsmpInfo.bFoUsed = TAF_TRUE;

    // MOCKER����

    // ���ñ��⺯��
    At_SendMsgFoAttr(ucIndex, &stTsDataInfo);

    // ִ�м��

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

TEST_F(Test_At_SendMsgFoAttr,Test_At_SendMsgFoAttr_002)
{
    // ��������
    VOS_UINT8                           ucIndex = 0;
    MN_MSG_TS_DATA_INFO_STRU            stTsDataInfo;

    // ������ʼ��
    stTsDataInfo.enTpduType = MN_MSG_TPDU_DELIVER;

    // ���ȫ�ֱ�����ʼ��
    g_astAtClientCtx[ucIndex].stClientConfiguration.enModemId   = MODEM_ID_1;
    gastAtClientTab[ucIndex].CmdCurrentOpt                      = AT_CMD_CMGC_PDU_SET;
    g_astAtModemCtx[MODEM_ID_1].stSmsCtx.stCscaCsmpInfo.bFoUsed = TAF_TRUE;

    // MOCKER����

    // ���ñ��⺯��
    At_SendMsgFoAttr(ucIndex, &stTsDataInfo);

    // ִ�м��

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
#endif
