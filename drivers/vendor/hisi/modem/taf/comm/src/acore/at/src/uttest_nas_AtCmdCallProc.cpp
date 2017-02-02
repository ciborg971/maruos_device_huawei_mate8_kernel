#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_AtCmdCallProc.h"



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



#if (FEATURE_ON == FEATURE_ECALL)


class Test_AT_SetCecallPara: public ::testing::Test
{
public:
    void SetUp()
    {
        ucIndex                                                 = 0;
        PS_MEM_SET(&stAtCmdMsg, 0, sizeof(TEST_AT_MSG_STRU));
        stAtCmdMsg.ulSenderPid                                  = WUEPS_PID_AT;

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

		MOCKER(At_StartTimer)
			.defaults()
			.will(returnValue((VOS_UINT32)AT_SUCCESS));

		At_PidInit(VOS_IP_INITIAL);
    }
    void TearDown()
    {
    }
protected:
    TEST_AT_MSG_STRU                    stAtCmdMsg;
    VOS_UINT8                           ucIndex;
};


TEST_F(Test_AT_SetCecallPara, Test_AT_SetCecallPara_001)
{
    char *pucCmdString                                      = "AT+CECALL=0";

    /* ��ʼ������ */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* ������Ϣ��ں��� */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* �����֤*/
    EXPECT_EQ(AT_CMD_CECALL_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetCecallPara, Test_AT_SetCecallPara_002)
{
    char *pucCmdString                                      = "AT+CECALL=1";

    /* ��ʼ������ */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* ������Ϣ��ں��� */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* �����֤*/
    EXPECT_EQ(AT_CMD_CECALL_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
    GlobalMockObject::verify();
}


TEST_F(Test_AT_SetCecallPara, Test_AT_SetCecallPara_003)
{
    char *pucCmdString                                      = "AT+CECALL=2";

    /* ��ʼ������ */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* ������Ϣ��ں��� */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* �����֤*/
    EXPECT_EQ(AT_CMD_CECALL_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_SetCecallPara, Test_AT_SetCecallPara_004)
{
    char *pucCmdString                                      = "AT+CECALL=3";

    /* ��ʼ������ */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* ������Ϣ��ں��� */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* �����֤*/
    EXPECT_EQ(AT_CMD_CECALL_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_SetCecallPara, Test_AT_SetCecallPara_005)
{
    char *pucCmdString                                      = "AT+CECALL=";

    /* ��ʼ������ */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    At_PidInit(VOS_IP_INITIAL);

    /* ������Ϣ��ں��� */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* �����֤*/

    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_SetCecallPara, Test_AT_SetCecallPara_006)
{
    char *pucCmdString                                      = "AT+CECALL=,";

    /* ��ʼ������ */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* ������Ϣ��ں��� */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* �����֤*/

    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_SetCecallPara, Test_AT_SetCecallPara_007)
{
    /* �������� */
    VOS_UINT32                          ulRst;

    /* ������ʼ�� */
    gucAtParaIndex                      = 1;
    gastAtParaList[0].ulParaValue       = 4;

    /* ���ñ��⺯�� */
    ulRst = AT_SetCecallPara(ucIndex);

    /* �����֤ */
    ASSERT_EQ(AT_ERROR, ulRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
   GlobalMockObject::verify();
}
TEST_F(Test_AT_SetCecallPara, Test_AT_SetCecallPara_008)
{
    /* �������� */
    VOS_UINT32                          ulRst;

    /* ������ʼ�� */
    gucAtParaIndex                      = 1;
    gastAtParaList[0].ulParaValue       = 1;

    /* ������׮ */
    MOCKER(AT_FillAndSndAppReqMsg)
        .defaults()
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    /* ���ñ��⺯�� */
    ulRst = AT_SetCecallPara(ucIndex);

    /* �����֤ */
    ASSERT_EQ(AT_ERROR, ulRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
   GlobalMockObject::verify();
}


class Test_AT_SetEclstartPara: public ::testing::Test
{
public:
    void SetUp()
    {
        ucIndex                                                 = 0;
        PS_MEM_SET(&stAtCmdMsg, 0, sizeof(TEST_AT_MSG_STRU));
        stAtCmdMsg.ulSenderPid                                  = WUEPS_PID_AT;

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

		MOCKER(At_StartTimer)
			.defaults()
			.will(returnValue((VOS_UINT32)AT_SUCCESS));

		At_PidInit(VOS_IP_INITIAL);
    }
    void TearDown()
    {
    }
protected:
    TEST_AT_MSG_STRU                    stAtCmdMsg;
    VOS_UINT8                           ucIndex;
};


//TEST_F(Test_AT_SetEclstartPara, Test_AT_SetEclstartPara_001)
//{
//    char *pucCmdString                                      = "AT^ECLSTART=0,0,\"13911110008\"";
//
//    /* ��ʼ������ */
//    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
//    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
//    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;
//
//    /* ������Ϣ��ں��� */
//    At_MsgProc((MsgBlock *)&stAtCmdMsg);
//
//    /* �����֤*/
//    EXPECT_EQ(AT_CMD_ECLSTART_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);
//
//    /* ������ʱ, ��Ҫ����������λ�ü������ */
//   GlobalMockObject::verify();
//}


//TEST_F(Test_AT_SetEclstartPara, Test_AT_SetEclstartPara_002)
//{
//    char *pucCmdString                                      = "AT^ECLSTART=0,1,\"112\"";
//
//    /* ��ʼ������ */
//    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
//    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
//    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;
//
//    /* ������Ϣ��ں��� */
//    At_MsgProc((MsgBlock *)&stAtCmdMsg);
//
//    /* �����֤*/
//    EXPECT_EQ(AT_CMD_ECLSTART_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);
//
//    /* ������ʱ, ��Ҫ����������λ�ü������ */
//   GlobalMockObject::verify();
//}


TEST_F(Test_AT_SetEclstartPara, Test_AT_SetEclstartPara_003)
{
    char *pucCmdString                                      = "AT^ECLSTART=1,0";

    /* ��ʼ������ */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* ������Ϣ��ں��� */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* �����֤*/
    EXPECT_EQ(AT_CMD_ECLSTART_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_SetEclstartPara, Test_AT_SetEclstartPara_004)
{
    char *pucCmdString                                      = "AT^ECLSTART=1,1";

    /* ��ʼ������ */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* ������Ϣ��ں��� */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* �����֤*/
    EXPECT_EQ(AT_CMD_ECLSTART_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
   GlobalMockObject::verify();
}


//TEST_F(Test_AT_SetEclstartPara, Test_AT_SetEclstartPara_005)
//{
//    char *pucCmdString                                      = "AT^ECLSTART=,1,\"112\"";
//
//    /* ��ʼ������ */
//    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
//    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
//    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;
//
//    /* ������׮ */
//    MOCKER(AT_FillAndSndAppReqMsg)
//        .times(0);
//
//    /* ������Ϣ��ں��� */
//    At_MsgProc((MsgBlock *)&stAtCmdMsg);
//
//    /* �����֤*/
//    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
//
//    /* ������ʱ, ��Ҫ����������λ�ü������ */
//   GlobalMockObject::verify();
//}
//TEST_F(Test_AT_SetEclstartPara, Test_AT_SetEclstartPara_006)
//{
//    char *pucCmdString                                      = "AT^ECLSTART=1,,\"112\"";
//
//    /* ��ʼ������ */
//    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
//    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
//    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;
//
//    /* ������׮ */
//    MOCKER(AT_FillAndSndAppReqMsg)
//        .times(0);
//
//    /* ������Ϣ��ں��� */
//    At_MsgProc((MsgBlock *)&stAtCmdMsg);
//
//    /* �����֤*/
//    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
//
//    /* ������ʱ, ��Ҫ����������λ�ü������ */
//   GlobalMockObject::verify();
//}
//TEST_F(Test_AT_SetEclstartPara, Test_AT_SetEclstartPara_007)
//{
//    char *pucCmdString                                      = "AT^ECLSTART=1,1,\"112\",1";
//
//    /* ��ʼ������ */
//    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
//    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
//    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;
//
//    /* ������׮ */
//    MOCKER(AT_FillAndSndAppReqMsg)
//        .times(0);
//
//    /* ������Ϣ��ں��� */
//    At_MsgProc((MsgBlock *)&stAtCmdMsg);
//
//    /* �����֤*/
//    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
//
//    /* ������ʱ, ��Ҫ����������λ�ü������ */
//   GlobalMockObject::verify();
//}
TEST_F(Test_AT_SetEclstartPara, Test_AT_SetEclstartPara_008)
{
    char *pucCmdString                                      = "AT^ECLSTART=1,1,";

    /* ��ʼ������ */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* ������׮ */

    /* ������Ϣ��ں��� */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* �����֤*/
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
   GlobalMockObject::verify();
}
//TEST_F(Test_AT_SetEclstartPara, Test_AT_SetEclstartPara_009)
//{
//    char *pucCmdString = "AT^ECLSTART=1,0,\"1502683289923456789\"";
//
//    /* ��ʼ������ */
//    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
//    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
//    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;
//
//    /* ������׮ */
//    MOCKER(AT_FillAndSndAppReqMsg)
//        .times(0);
//
//    /* ������Ϣ��ں��� */
//    At_MsgProc((MsgBlock *)&stAtCmdMsg);
//
//    /* �����֤*/
//    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
//
//    /* ������ʱ, ��Ҫ����������λ�ü������ */
//   GlobalMockObject::verify();
//}
//TEST_F(Test_AT_SetEclstartPara, Test_AT_SetEclstartPara_010)
//{
//    char *pucCmdString = "AT^ECLSTART=1,0,\"&15026832899\"";
//
//    /* ��ʼ������ */
//    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
//    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
//    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;
//
//    /* ������׮ */
//    MOCKER(AT_SetCsCallErrCause)
//        .times(1);
//
//    /* ������Ϣ��ں��� */
//    At_MsgProc((MsgBlock *)&stAtCmdMsg);
//
//    /* �����֤*/
//    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);
//
//    /* ������ʱ, ��Ҫ����������λ�ü������ */
//   GlobalMockObject::verify();
//}
TEST_F(Test_AT_SetEclstartPara, Test_AT_SetEclstartPara_011)
{
    /* �������� */
    VOS_UINT32                          ulRst;

    /* ������ʼ�� */
    PS_MEM_SET(gastAtParaList, 0, sizeof(gastAtParaList));

    gucAtParaIndex                      = 2;
    gastAtParaList[0].ulParaValue       = 1;
    gastAtParaList[0].usParaLen         = 1;
    gastAtParaList[1].ulParaValue       = 1;
    gastAtParaList[1].usParaLen         = 1;

    /* ������׮ */
    MOCKER(AT_FillAndSndAppReqMsg)
		.defaults()
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    /* ���ñ��⺯�� */
    ulRst = AT_SetEclstartPara(ucIndex);

    /* �����֤ */
    ASSERT_EQ(AT_ERROR, ulRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
   GlobalMockObject::verify();
}


class Test_AT_SetEclstopPara: public ::testing::Test
{
public:
    void SetUp()
    {
        ucIndex                                                 = 0;
        PS_MEM_SET(&stAtCmdMsg, 0, sizeof(TEST_AT_MSG_STRU));
        stAtCmdMsg.ulSenderPid                                  = WUEPS_PID_AT;


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

		MOCKER(At_StartTimer)
			.defaults()
			.will(returnValue((VOS_UINT32)AT_SUCCESS));
		
		At_PidInit(VOS_IP_INITIAL);
    }
    void TearDown()
    {
    }
protected:
    TEST_AT_MSG_STRU                    stAtCmdMsg;
    VOS_UINT8                           ucIndex;
};


TEST_F(Test_AT_SetEclstopPara, Test_AT_SetEclstopPara_001)
{
    char *pucCmdString                                 = "AT^ECLSTOP";

    /* ��ʼ������ */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* ������Ϣ��ں��� */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* �����֤*/
    EXPECT_EQ(AT_CMD_ECLSTOP_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_SetEclstopPara, Test_AT_SetEclstopPara_002)
{
    char *pucCmdString                                 = "AT^ECLSTOP=";

    /* ��ʼ������ */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* ������Ϣ��ں��� */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* �����֤*/
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_SetEclstopPara, Test_AT_SetEclstopPara_003)
{
    /* �������� */
    VOS_UINT32                          ulRst;

    /* ������ʼ�� */
    g_stATParseCmd.ucCmdOptType         = AT_CMD_OPT_SET_CMD_NO_PARA;

    /* ������׮ */
    MOCKER(AT_FillAndSndAppReqMsg)
		.defaults()
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    /* ���ñ��⺯�� */
    ulRst = AT_SetEclstopPara(ucIndex);

    /* �����֤ */
    ASSERT_EQ(AT_ERROR, ulRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
   GlobalMockObject::verify();
}


class Test_AT_SetEclcfgPara: public ::testing::Test
{
public:
    void SetUp()
    {
        ucIndex                                                 = 0;
        PS_MEM_SET(&stAtCmdMsg, 0, sizeof(TEST_AT_MSG_STRU));
        stAtCmdMsg.ulSenderPid                                  = WUEPS_PID_AT;

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

		MOCKER(At_StartTimer)
			.defaults()
			.will(returnValue((VOS_UINT32)AT_SUCCESS));

		At_PidInit(VOS_IP_INITIAL);
    }
    void TearDown()
    {
    }
protected:
    TEST_AT_MSG_STRU                    stAtCmdMsg;
    VOS_UINT8                           ucIndex;
};


TEST_F(Test_AT_SetEclcfgPara, Test_AT_SetEclcfgPara_001)
{
    char *pucCmdString                                      = "AT^ECLCFG=0";

    /* ��ʼ������ */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* ������Ϣ��ں��� */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* �����֤*/
    EXPECT_EQ(AT_CMD_ECLCFG_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_SetEclcfgPara, Test_AT_SetEclcfgPara_002)
{
    char *pucCmdString                                      = "AT^ECLCFG=0,1";

    /* ��ʼ������ */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* ������Ϣ��ں��� */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* �����֤*/
    EXPECT_EQ(AT_CMD_ECLCFG_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_SetEclcfgPara, Test_AT_SetEclcfgPara_003)
{
    char *pucCmdString                                      = "AT^ECLCFG=";

    /* ��ʼ������ */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* ������Ϣ��ں��� */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* �����֤*/
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_SetEclcfgPara, Test_AT_SetEclcfgPara_004)
{
    char *pucCmdString                                      = "AT^ECLCFG=0,0,";

    /* ��ʼ������ */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* ������Ϣ��ں��� */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* �����֤*/
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_SetEclcfgPara, Test_AT_SetEclcfgPara_005)
{
    char *pucCmdString                                      = "AT^ECLCFG=0,";

    /* ��ʼ������ */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* ������Ϣ��ں��� */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* �����֤*/
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_SetEclcfgPara, Test_AT_SetEclcfgPara_006)
{
    /* �������� */
    VOS_UINT32                          ulRst;

    /* ������ʼ�� */
    gucAtParaIndex                      = 2;
    gastAtParaList[0].ulParaValue       = 0;
    gastAtParaList[0].usParaLen         = 1;
    gastAtParaList[1].ulParaValue       = 1;
    gastAtParaList[1].usParaLen         = 1;

    /* ������׮ */
    MOCKER(AT_FillAndSndAppReqMsg)
		.defaults()
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    /* ���ñ��⺯�� */
    ulRst = AT_SetEclcfgPara(ucIndex);

    /* �����֤ */
    ASSERT_EQ(AT_ERROR, ulRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
   GlobalMockObject::verify();

}
#if 0

class Test_AT_SetEclmsdPara: public ::testing::Test
{
public:
    void SetUp()
    {
        ucIndex                                                 = 0;
        PS_MEM_SET(&stAtCmdMsg, 0, sizeof(TEST_AT_MSG_STRU));
        stAtCmdMsg.ulSenderPid                                  = WUEPS_PID_AT;

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

		MOCKER(At_StartTimer)
			.defaults()
			.will(returnValue((VOS_UINT32)AT_SUCCESS));

		At_PidInit(VOS_IP_INITIAL);
    }
    void TearDown()
    {
    }
protected:
    TEST_AT_MSG_STRU                    stAtCmdMsg;
    VOS_UINT8                           ucIndex;
};


TEST_F(Test_AT_SetEclmsdPara, Test_AT_SetEclmsdPara_001)
{
    char *pucCmdString = "AT^ECLMSD=\"010108414141414141414141414131313131313188\
0000000100000001000000010100010001000100010600010db885a308d313198a2e037073340000\
00000000000000000000000000000000000000000000000000000000000000000000000000000000\
000000000000000000000000000000000000000000000000000000000000000000000000000000\"";

    /* ��ʼ������ */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* ������Ϣ��ں��� */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* �����֤*/
    EXPECT_EQ(AT_CMD_ECLMSD_SET, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_SetEclmsdPara, Test_AT_SetEclmsdPara_002)
{
    char *pucCmdString                                      = "AT^ECLMSD=";

    /* ��ʼ������ */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* ������Ϣ��ں��� */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* �����֤*/
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_SetEclmsdPara, Test_AT_SetEclmsdPara_003)
{
    char *pucCmdString                                      = "AT^ECLMSD=\"00\"";

    /* ��ʼ������ */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* ������Ϣ��ں��� */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* �����֤*/
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_SetEclmsdPara, Test_AT_SetEclmsdPara_004)
{
    char *pucCmdString = "AT^ECLMSD=\"&&0108414141414141414141414131313131313188\
0000000100000001000000010100010001000100010600010db885a308d313198a2e037073340000\
00000000000000000000000000000000000000000000000000000000000000000000000000000000\
000000000000000000000000000000000000000000000000000000000000000000000000000000\"";

    /* ��ʼ������ */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* ������Ϣ��ں��� */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* �����֤*/
    EXPECT_EQ(AT_CMD_CURRENT_OPT_BUTT, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_SetEclmsdPara, Test_AT_SetEclmsdPara_005)
{
    /* �������� */
    VOS_UINT32                          ulRst;
    char *pucMsdString = "010108414141414141414141414131313131313188000000010000\
0001000000010100010001000100010600010db885a308d313198a2e037073340000000000000000\
00000000000000000000000000000000000000000000000000000000000000000000000000000000\
000000000000000000000000000000000000000000000000000000000000000000";

    /* ������ʼ�� */
    gucAtParaIndex                      = 1;
    PS_MEM_CPY(gastAtParaList[0].aucPara, pucMsdString, strlen(pucMsdString)+1);
    gastAtParaList[0].usParaLen         = APP_VC_MSD_DATA_LEN * 2;

    /* ������׮ */
    MOCKER(AT_FillAndSndAppReqMsg)
        .will(returnValue(TAF_FAILURE));

    /* ���ñ��⺯�� */
    ulRst = AT_SetEclmsdPara(ucIndex);

    /* �����֤ */
    ASSERT_EQ(AT_ERROR, ulRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
   GlobalMockObject::verify();

}
#endif


class Test_AT_QryCecallPara: public ::testing::Test
{
public:
    void SetUp()
    {
        ucIndex                                                 = 0;
        PS_MEM_SET(&stAtCmdMsg, 0, sizeof(TEST_AT_MSG_STRU));
        stAtCmdMsg.ulSenderPid                                  = WUEPS_PID_AT;

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

		MOCKER(At_StartTimer)
			.defaults()
			.will(returnValue((VOS_UINT32)AT_SUCCESS));

		At_PidInit(VOS_IP_INITIAL);
    }
    void TearDown()
    {
    }
protected:
    TEST_AT_MSG_STRU                    stAtCmdMsg;
    VOS_UINT8                           ucIndex;
};


TEST_F(Test_AT_QryCecallPara, Test_AT_QryCecallPara_001)
{
    char *pucCmdString = "AT+CECALL?";

    /* ��ʼ������ */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* ������Ϣ��ں��� */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* �����֤*/
    EXPECT_EQ(AT_CMD_CECALL_QRY, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_QryCecallPara, Test_AT_QryCecallPara_002)
{
    /* �������� */
    VOS_UINT32                          ulRst;

    /* ������ʼ�� */

    /* ������׮ */
    MOCKER(AT_FillAndSndAppReqMsg)
		.defaults()
        .will(returnValue((VOS_UINT32)TAF_FAILURE));

    /* ���ñ��⺯�� */
    ulRst = AT_QryCecallPara(ucIndex);

    /* �����֤ */
    ASSERT_EQ(AT_ERROR, ulRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
   GlobalMockObject::verify();

}


class Test_AT_QryEclcfgPara: public ::testing::Test
{
public:
    void SetUp()
    {
        ucIndex                                                 = 0;
        PS_MEM_SET(&stAtCmdMsg, 0, sizeof(TEST_AT_MSG_STRU));
        stAtCmdMsg.ulSenderPid                                  = WUEPS_PID_AT;

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

		MOCKER(At_StartTimer)
			.defaults()
			.will(returnValue((VOS_UINT32)AT_SUCCESS));

		At_PidInit(VOS_IP_INITIAL);
    }
    void TearDown()
    {
    }
protected:
    TEST_AT_MSG_STRU                    stAtCmdMsg;
    VOS_UINT8                           ucIndex;
};


TEST_F(Test_AT_QryEclcfgPara, Test_AT_QryEclcfgPara_001)
{
    char *pucCmdString = "AT^ECLCFG?";

    /* ��ʼ������ */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* ������Ϣ��ں��� */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* �����֤*/
    EXPECT_EQ(AT_CMD_ECLCFG_QRY, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_QryEclcfgPara, Test_AT_QryEclcfgPara_002)
{
    /* �������� */
    VOS_UINT32                          ulRst;

    /* ������ʼ�� */

    /* ������׮ */
    MOCKER(AT_FillAndSndAppReqMsg)
        .defaults()
		.will(returnValue((VOS_UINT32)TAF_FAILURE));

    /* ���ñ��⺯�� */
    ulRst = AT_QryEclcfgPara(ucIndex);

    /* �����֤ */
    ASSERT_EQ(AT_ERROR, ulRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
   GlobalMockObject::verify();

}


class Test_AT_QryEclmsdPara: public ::testing::Test
{
public:
    void SetUp()
    {
        ucIndex                                                 = 0;
        PS_MEM_SET(&stAtCmdMsg, 0, sizeof(TEST_AT_MSG_STRU));
        stAtCmdMsg.ulSenderPid                                  = WUEPS_PID_AT;

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

		MOCKER(At_StartTimer)
			.defaults()
			.will(returnValue((VOS_UINT32)AT_SUCCESS));

		At_PidInit(VOS_IP_INITIAL);
    }
    void TearDown()
    {
    }
protected:
    TEST_AT_MSG_STRU                    stAtCmdMsg;
    VOS_UINT8                           ucIndex;
};


TEST_F(Test_AT_QryEclmsdPara, Test_AT_QryEclmsdPara_001)
{
    char *pucCmdString = "AT^ECLMSD?";

    /* ��ʼ������ */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* ������Ϣ��ں��� */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* �����֤*/
    EXPECT_EQ(AT_CMD_ECLMSD_QRY, gastAtClientTab[ucIndex].CmdCurrentOpt);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
   GlobalMockObject::verify();
}


TEST_F(Test_AT_QryEclmsdPara, Test_AT_QryEclmsdPara_002)
{
    /* �������� */
    VOS_UINT32                          ulRst;

    /* ������ʼ�� */

    /* ������׮ */
    MOCKER(AT_FillAndSndAppReqMsg)
		.defaults()
		.will(returnValue((VOS_UINT32)TAF_FAILURE));

    /* ���ñ��⺯�� */
    ulRst = AT_QryEclmsdPara(ucIndex);

    /* �����֤ */
    ASSERT_EQ(AT_ERROR, ulRst);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
   GlobalMockObject::verify();

}



class Test_AT_TestEclstartPara: public ::testing::Test
{
public:
    void SetUp()
    {
        ucIndex                                                 = 0;
        PS_MEM_SET(&stAtCmdMsg, 0, sizeof(TEST_AT_MSG_STRU));
        stAtCmdMsg.ulSenderPid                                  = WUEPS_PID_AT;

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

		MOCKER(At_StartTimer)
			.defaults()
			.will(returnValue((VOS_UINT32)AT_SUCCESS));

		At_PidInit(VOS_IP_INITIAL);
    }
    void TearDown()
    {
    }
protected:
    TEST_AT_MSG_STRU                    stAtCmdMsg;
    VOS_UINT8                           ucIndex;
};


TEST_F(Test_AT_TestEclstartPara, Test_AT_TestEclstartPara_001)
{
    char *pucCmdString = "AT^ECLSTART=?";

    /* ��ʼ������ */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* ������Ϣ��ں��� */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
   GlobalMockObject::verify();
}
class Test_AT_TestEclmsdPara: public ::testing::Test
{
public:
    void SetUp()
    {
        ucIndex                                                 = 0;
        PS_MEM_SET(&stAtCmdMsg, 0, sizeof(TEST_AT_MSG_STRU));
        stAtCmdMsg.ulSenderPid                                  = WUEPS_PID_AT;

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

		MOCKER(At_StartTimer)
			.defaults()
			.will(returnValue((VOS_UINT32)AT_SUCCESS));

		At_PidInit(VOS_IP_INITIAL);
    }
    void TearDown()
    {
    }
protected:
    TEST_AT_MSG_STRU                    stAtCmdMsg;
    VOS_UINT8                           ucIndex;
};


TEST_F(Test_AT_TestEclmsdPara, Test_AT_TestEclmsdPara_001)
{
    char *pucCmdString = "AT^ECLMSD=?";

    /* ��ʼ������ */
    stAtCmdMsg.usLen                                        = strlen(pucCmdString) + 1;
    PS_MEM_CPY(stAtCmdMsg.aucValue, pucCmdString, stAtCmdMsg.usLen);
    stAtCmdMsg.aucValue[stAtCmdMsg.usLen - 1]               = 0x0d;

    /* ������Ϣ��ں��� */
    At_MsgProc((MsgBlock *)&stAtCmdMsg);

    /* ������ʱ, ��Ҫ����������λ�ü������ */
   GlobalMockObject::verify();
}


#endif








