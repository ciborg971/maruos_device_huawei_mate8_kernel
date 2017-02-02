#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "vos.h"
#include "PsCommonDef.h"
#include "TafApsApi.h"
#include "MnClient.h"
//�����������ã����������ùؼ���ʱ��Ҫ��ǰ׺ testing::
using namespace testing;

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
extern VOS_UINT32 AT_GetDestPid(
                                MN_CLIENT_ID_T                      usClientId,
                                VOS_UINT32                          ulRcvPid
                                );
extern VOS_UINT32 TAF_PS_SndMsg(
    VOS_UINT32                          ulTaskId,
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
);

extern VOS_UINT8 TAF_APS_FindCidForDial(VOS_UINT32  ulAppPid);
extern VOS_UINT32 TAF_APS_GetSdfParaInfo(
    VOS_UINT8                           ucCid,
    TAF_SDF_PARA_STRU                  *pstSdfParaInfo
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



class Test_TAF_PS_SndMsg: public ::testing::Test
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


TEST_F(Test_TAF_PS_SndMsg,Test_TAF_PS_SndMsg_001)
{
    VOS_UINT32                          ulTaskId;
    VOS_UINT32                          ulMsgId;
    TAF_CTRL_STRU                      *pstCtrl;
    VOS_UINT32                          ulLength;

    ulTaskId = I0_WUEPS_PID_TAF;
    ulMsgId = 1;
    pstCtrl = (TAF_CTRL_STRU*)malloc(sizeof(TAF_CTRL_STRU));
    pstCtrl->usClientId = AT_CLIENT_TAB_APP_INDEX;
    ulLength = 1;

    MOCKER(AT_GetDestPid)
        .expects(exactly(1))
        .with(eq(pstCtrl->usClientId),eq(ulTaskId))
        .will(returnValue((VOS_UINT32)VOS_OK));

    TAF_PS_SndMsg(ulTaskId, ulMsgId,(VOS_VOID*)pstCtrl, ulLength);

    GlobalMockObject::verify();
}



class Test_TAF_PS_GetCidSdfParaInfo: public ::testing::Test
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

TEST_F(Test_TAF_PS_GetCidSdfParaInfo, Test_TAF_PS_GetCidSdfParaInfo_001)
{
    // ��������
    VOS_UINT32                          ulRelt;
    TAF_SDF_PARA_QUERY_INFO_STRU        stSdfInfo;
    TAF_PS_SDF_INFO_REQ_STRU            stSdfInfoReq;

    // ������ʼ��
    memset(&stSdfInfo, 0, sizeof(TAF_SDF_PARA_QUERY_INFO_STRU));
    memset(&stSdfInfoReq, 0, sizeof(TAF_PS_SDF_INFO_REQ_STRU));
#if (FEATURE_IMS == FEATURE_ON)
    stSdfInfoReq.stCtrl.ulModuleId = PS_PID_IMSA;
#endif

    stSdfInfoReq.stCtrl.usClientId = AT_CLIENT_ID_APP;
    stSdfInfoReq.stCtrl.ucOpId     = 0;
    // ��ʼ��ȫ�ֱ���

    // MOCKER����
    MOCKER(TAF_PS_SndMsg)
        .expects(exactly(1))
        .with(any(),
              eq(ID_MSG_TAF_PS_GET_CID_SDF_REQ),
              mirror((void *)&stSdfInfoReq,(unsigned int)sizeof(TAF_PS_SDF_INFO_REQ_STRU)),
              eq((unsigned int)sizeof(TAF_PS_SDF_INFO_REQ_STRU)))
              .will(returnValue((VOS_UINT32)VOS_OK));

    // ���ñ��⺯��
    ulRelt = TAF_PS_GetCidSdfParaInfo(stSdfInfoReq.stCtrl.ulModuleId,
                                      stSdfInfoReq.stCtrl.usClientId,
                                      stSdfInfoReq.stCtrl.ucOpId,
                                      VOS_NULL_PTR);

    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRelt);
    GlobalMockObject::verify();
}



class Test_TAF_PS_GetUnusedCid: public ::testing::Test
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

TEST_F(Test_TAF_PS_GetUnusedCid, Test_TAF_PS_GetUnusedCid_001)
{
    // ��������
    VOS_UINT32                          ulRelt;
    TAF_CTRL_STRU                       stCtrl;

    // ������ʼ��
    memset(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

#if (FEATURE_IMS == FEATURE_ON)
    stCtrl.ulModuleId = PS_PID_IMSA;
#endif
    stCtrl.usClientId = AT_CLIENT_ID_APP;
    stCtrl.ucOpId     = 0;
    // ��ʼ��ȫ�ֱ���

    // MOCKER����

    // ���ñ��⺯��
    ulRelt = TAF_PS_GetUnusedCid(stCtrl.ulModuleId,
                                 stCtrl.usClientId,
                                 stCtrl.ucOpId,
                                 VOS_NULL_PTR);

    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRelt);
    GlobalMockObject::verify();
}


