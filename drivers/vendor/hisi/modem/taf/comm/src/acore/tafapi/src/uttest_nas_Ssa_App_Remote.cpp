#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "v_typdef.h"
#include "PsCommonDef.h"
#include "PsLogdef.h"
#include "TafAppSsa.h"
#include "MnCommApi.h"
#include "Taf_Tafm_Remote.h"

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

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_SSA_APP_REMOTE_C

extern void UT_STUB_INIT(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif




class Test_TAF_EraseSSReq: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    void SetUp()
	{
		UT_STUB_INIT();
    }

    void TearDown()
    {
    }
};


TEST_F(Test_TAF_EraseSSReq, Test_TAF_EraseSSReq_001)
{
    VOS_UINT32                          ulRet;
    MN_CLIENT_ID_T                      ClientId = 0;
    MN_OPERATION_ID_T                   OpId = 0;
    TAF_SS_ERASESS_REQ_STRU             stPara;
    VOS_UINT32                          ulParaLen;

    PS_MEM_SET(&stPara, 0, sizeof(stPara));

    ulParaLen = sizeof(stPara);
    MOCKER(MN_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(ClientId), eq(OpId), eq((unsigned short)TAF_MSG_ERASESS_MSG), any(), eq(ulParaLen), eq(I0_WUEPS_PID_TAF))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    ulRet = TAF_EraseSSReq(ClientId, OpId, &stPara);


    EXPECT_EQ(TAF_SUCCESS, ulRet);


    // ִ�м��
    GlobalMockObject::verify();

}


class Test_TAF_ActivateSSReq: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    void SetUp()
	{
		UT_STUB_INIT();
    }

    void TearDown()
    {
    }
};


TEST_F(Test_TAF_ActivateSSReq, Test_TAF_ActivateSSReq_001)
{
    VOS_UINT32                          ulRet;
    MN_CLIENT_ID_T                      ClientId = 0;
    MN_OPERATION_ID_T                   OpId = 0;
    TAF_SS_ACTIVATESS_REQ_STRU          stPara;
    VOS_UINT32                          ulParaLen;

    ulParaLen = sizeof(stPara);

    PS_MEM_SET(&stPara, 0, sizeof(stPara));

    MOCKER(MN_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(ClientId), eq(OpId), eq((unsigned short)TAF_MSG_ACTIVATESS_MSG), any(), eq(ulParaLen), eq(I0_WUEPS_PID_TAF))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    ulRet = TAF_ActivateSSReq(ClientId, OpId, &stPara);


    EXPECT_EQ(TAF_SUCCESS, ulRet);


    // ִ�м��
    GlobalMockObject::verify();

}


class Test_TAF_RegisterPasswordReq: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    void SetUp()
	{
		UT_STUB_INIT();
    }

    void TearDown()
    {
    }
};


TEST_F(Test_TAF_RegisterPasswordReq, Test_TAF_RegisterPasswordReq_001)
{
    VOS_UINT32                          ulRet;
    MN_CLIENT_ID_T                      ClientId = 0;
    MN_OPERATION_ID_T                   OpId = 0;
    TAF_SS_REGPWD_REQ_STRU              stPara;
    VOS_UINT32                          ulParaLen;

    ulParaLen = sizeof(stPara);

    PS_MEM_SET(&stPara, 0, sizeof(stPara));

    MOCKER(MN_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(ClientId), eq(OpId), eq((unsigned short)TAF_MSG_REGPWD_MSG), any(), eq(ulParaLen), eq(I0_WUEPS_PID_TAF))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    ulRet = TAF_RegisterPasswordReq(ClientId, OpId, &stPara);


    EXPECT_EQ(TAF_SUCCESS, ulRet);


    // ִ�м��
    GlobalMockObject::verify();

}


class Test_TAF_EraseCCEntryReq: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    void SetUp()
	{
		UT_STUB_INIT();
    }

    void TearDown()
    {
    }
};


TEST_F(Test_TAF_EraseCCEntryReq, Test_TAF_EraseCCEntryReq_001)
{
    VOS_UINT32                          ulRet;
    MN_CLIENT_ID_T                      ClientId = 0;
    MN_OPERATION_ID_T                   OpId = 0;
    TAF_SS_ERASECC_ENTRY_REQ_STRU       stPara;
    VOS_UINT32                          ulParaLen;

    ulParaLen = sizeof(stPara);

    PS_MEM_SET(&stPara, 0, sizeof(stPara));

    MOCKER(MN_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(ClientId), eq(OpId), eq((unsigned short)TAF_MSG_ERASECCENTRY_MSG), any(), eq(ulParaLen), eq(I0_WUEPS_PID_TAF))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    ulRet = TAF_EraseCCEntryReq(ClientId, OpId, &stPara);


    EXPECT_EQ(TAF_SUCCESS, ulRet);


    // ִ�м��
    GlobalMockObject::verify();

}


class Test_TAF_SsReleaseComplete: public ::testing::Test
{
public:
    VOS_UINT8                           ucIndex;
    void SetUp()
	{
		UT_STUB_INIT();
    }

    void TearDown()
    {
    }
};


TEST_F(Test_TAF_SsReleaseComplete, Test_TAF_SsReleaseComplete_001)
{
    VOS_UINT32                          ulRet;
    MN_CLIENT_ID_T                      ClientId = 0;
    MN_OPERATION_ID_T                   OpId = 0;
    VOS_UINT32                          ulParaLen;

    ulParaLen = 0;

    MOCKER(MN_FillAndSndAppReqMsg)
        .stubs()
        .with(eq(ClientId), eq(OpId), eq((unsigned short)TAF_MSG_RLEASE_MSG), any(), eq(ulParaLen), eq(I0_WUEPS_PID_TAF))
        .will(returnValue((VOS_UINT32)TAF_SUCCESS));

    ulRet = TAF_SsReleaseComplete(ClientId, OpId);


    EXPECT_EQ(TAF_SUCCESS, ulRet);


    // ִ�м��
    GlobalMockObject::verify();

}


