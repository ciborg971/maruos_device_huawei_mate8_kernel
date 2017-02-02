#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_AtSndMsg.h"

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


class Test_AT_FillAppReqMsgHeader: public ::testing::Test
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


TEST_F(Test_AT_FillAppReqMsgHeader, Test_AT_FillAppReqMsgHeader_001)
{
	MN_APP_REQ_MSG_STRU                *pMsg;
	MN_CLIENT_ID_T                      usClientId;
	MN_OPERATION_ID_T                   ucOpId = 0;
	VOS_UINT16                          usMsgType = 0;
	VOS_UINT32                          ulRcvPid;
	VOS_UINT32								ulRslt;

	pMsg = (MN_APP_REQ_MSG_STRU *)malloc(sizeof(MN_APP_REQ_MSG_STRU));
	usClientId = AT_CLIENT_ID_APP;
	ulRcvPid   = I0_WUEPS_PID_TAF;

	MOCKER(AT_GetDestPid)
		.expects(exactly(1))
		.with(eq(usClientId), eq(ulRcvPid))
		.will(returnValue((VOS_UINT32)I0_WUEPS_PID_TAF));

	ulRslt = AT_FillAppReqMsgHeader(pMsg, usClientId, ucOpId, usMsgType, ulRcvPid);

	EXPECT_EQ(I0_WUEPS_PID_TAF, pMsg->ulReceiverPid);
	EXPECT_EQ(VOS_OK, ulRslt);

	GlobalMockObject::verify();
}



class Test_AT_SndSetFastDorm: public ::testing::Test
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


TEST_F(Test_AT_SndSetFastDorm, Test_AT_SndSetFastDorm_001)
{
	VOS_UINT16                          usClientId;
	VOS_UINT8                           ucOpId = 0;
	AT_RABM_FASTDORM_PARA_STRU         *pstFastDormPara;
	VOS_UINT32                          ulRslt;

	usClientId = AT_CLIENT_ID_APP;
	pstFastDormPara = (AT_RABM_FASTDORM_PARA_STRU *)malloc(sizeof(AT_RABM_FASTDORM_PARA_STRU));

	MOCKER(AT_GetDestPid)
		.expects(exactly(1))
		.with(eq(usClientId), eq(I0_WUEPS_PID_RABM))
		.will(returnValue((VOS_UINT32)I0_WUEPS_PID_RABM));

	ulRslt = AT_SndSetFastDorm(usClientId, ucOpId, pstFastDormPara);
;
	EXPECT_EQ(VOS_OK, ulRslt);

    free(pstFastDormPara);

	GlobalMockObject::verify();
}




class Test_AT_SndQryFastDorm: public ::testing::Test
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


TEST_F(Test_AT_SndQryFastDorm, Test_AT_SndQryFastDorm_001)
{
	VOS_UINT16                          usClientId;
	VOS_UINT8                           ucOpId = 0;
	VOS_UINT32                          ulRslt;

	usClientId = AT_CLIENT_ID_APP;

	MOCKER(AT_GetDestPid)
		.expects(exactly(1))
		.with(eq(usClientId), eq(I0_WUEPS_PID_RABM))
		.will(returnValue((VOS_UINT32)I0_WUEPS_PID_RABM));

	ulRslt = AT_SndQryFastDorm (usClientId, ucOpId);

	EXPECT_EQ(VOS_OK, ulRslt);

	GlobalMockObject::verify();

}
