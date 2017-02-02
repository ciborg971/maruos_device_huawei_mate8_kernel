#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include  "product_config.h"
#include  "vos.h"
#include  "MnErrorCode.h"
#include  "MnMsgApi.h"
#include  "ATCmdProc.h"

//�����������ã����������ùؼ���ʱ��Ҫ��ǰ׺ testing::
using namespace testing;

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

extern VOS_UINT32 MSG_SendAppReq(
    MN_MSG_MSGTYPE_ENUM_U16             enMsgType,
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const VOS_VOID                      *pSendParm
);

extern void UT_STUB_INIT(void);

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



class Test_MN_MSG_ReqStub: public ::testing::Test
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


TEST_F(Test_MN_MSG_ReqStub,Test_MN_MSG_ReqStub_001)
{
}


TEST_F(Test_MN_MSG_ReqStub,Test_MN_MSG_ReqStub_002)
{
}

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))


class Test_MN_MSG_GetAllCbMids: public ::testing::Test
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

TEST(Test_MN_MSG_GetAllCbMids,Test_MN_MSG_GetAllCbMids_01)
{
    MN_CLIENT_ID_T                      clientId = 0;
    MN_OPERATION_ID_T                   opId = 0;

    MOCKER(MSG_SendAppReq)
        .stubs()
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    EXPECT_EQ(MN_ERR_NO_ERROR,MN_MSG_GetAllCbMids(clientId,opId));
    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST(Test_MN_MSG_AddCbMids,Test_MN_MSG_GetAllCbMids_02)
{
    MN_CLIENT_ID_T                      clientId = 0;
    MN_OPERATION_ID_T                   opId = 0;
    TAF_CBA_CBMI_RANGE_LIST_STRU              stCbmirList;

    MOCKER(MSG_SendAppReq)
        .stubs()
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    EXPECT_EQ(MN_ERR_NO_ERROR,MN_MSG_AddCbMids(clientId,opId,&stCbmirList));
    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST(Test_MN_MSG_AddCbMids,Test_MN_MSG_GetAllCbMids_03)
{
    MN_CLIENT_ID_T                      clientId = 0;
    MN_OPERATION_ID_T                   opId = 0;

    MOCKER(MSG_SendAppReq)
        .stubs()
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    EXPECT_EQ(MN_ERR_NULLPTR,MN_MSG_AddCbMids(clientId,opId,VOS_NULL_PTR));

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}



class Test_MN_MSG_DelCbMids: public ::testing::Test
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

TEST(Test_MN_MSG_DelCbMids,Test_MN_MSG_DelCbMids_01)
{
    MN_CLIENT_ID_T                      clientId = 0;
    MN_OPERATION_ID_T                   opId = 0;
    TAF_CBA_CBMI_RANGE_LIST_STRU              stCbmirList;

    MOCKER(MSG_SendAppReq)
        .stubs()
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    EXPECT_EQ(MN_ERR_NO_ERROR,MN_MSG_DelCbMids(clientId,opId,&stCbmirList));
    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST(Test_MN_MSG_DelCbMids,Test_MN_MSG_DelCbMids_02)
{
    MN_CLIENT_ID_T                      clientId = 0;
    MN_OPERATION_ID_T                   opId = 0;

    MOCKER(MSG_SendAppReq)
        .stubs()
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    EXPECT_EQ(MN_ERR_NULLPTR,MN_MSG_DelCbMids(clientId,opId,VOS_NULL_PTR));

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


class Test_MN_MSG_EmptyCbMids: public ::testing::Test
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

TEST(Test_MN_MSG_EmptyCbMids,Test_MN_MSG_EmptyCbMids_01)
{
    MN_CLIENT_ID_T                      clientId = 0;
    MN_OPERATION_ID_T                   opId = 0;

    MOCKER(MSG_SendAppReq)
        .stubs()
        .will(returnValue((VOS_UINT32)MN_ERR_NO_ERROR));

    EXPECT_EQ(MN_ERR_NO_ERROR,MN_MSG_EmptyCbMids(clientId,opId));

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}



#endif

