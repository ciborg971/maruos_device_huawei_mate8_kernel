#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "vos.h"
#include "PsCommonDef.h"
#include "AtMnInterface.h"
#include "MnCallApi.h"
#include  "product_config.h"
#include "MnErrorCode.h"
#include "AtParse.h"
#include "ATCmdProc.h"
#include "MnCommApi.h"

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

extern void UT_STUB_INIT(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif




class Test_MN_CALL_QryCdur: public ::testing::Test
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


TEST_F(Test_MN_CALL_QryCdur,Test_MN_CALL_QryCdur_001)
{
}


class Test_MN_CALL_Orig: public ::testing::Test
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


TEST_F(Test_MN_CALL_Orig,Test_MN_CALL_Orig_001)
{
        // ��������
    MN_CLIENT_ID_T                      clientId;
    MN_OPERATION_ID_T                   opId;
    MN_CALL_ID_T                        CallId;
    MN_CALL_ORIG_PARAM_STRU       stOrigParam;
    VOS_UINT32                          ulRst;

    // ������ʼ��
    clientId                            = 0;
    opId                                = 0;

    // ���ȫ�ֱ�����ʼ��

    // MOCKER����;
    MOCKER(V_MemCpy)
        .stubs()
        .will(returnValue((VOS_VOID *)0));

    // ���ñ��⺯��
    ulRst = MN_CALL_Orig(clientId, opId, &CallId, &stOrigParam);

    // ִ�м��
    EXPECT_EQ(VOS_OK,ulRst);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}




class Test_MN_CALL_GetCallInfos: public ::testing::Test
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


TEST_F(Test_MN_CALL_GetCallInfos,Test_MN_CALL_GetCallInfos_001)
{
        // ��������
    MN_CLIENT_ID_T                      clientId;
    MN_OPERATION_ID_T                   opId;
    MN_CALL_ID_T                        CallId;
    VOS_UINT32                          ulRst;

    // ������ʼ��
    clientId                            = 0;
    opId                                = 0;
    CallId                             = 1;
    // ���ȫ�ֱ�����ʼ��

    // MOCKER����;
    MOCKER(MN_CALL_SendAppRequest)
        .stubs()
        .with(eq((VOS_UINT32)MN_CALL_APP_GET_INFO_REQ), eq(clientId), eq(opId), eq(CallId), eq((MN_CALL_APP_REQ_PARM_UNION const*)VOS_NULL_PTR))
        .will(returnValue((VOS_UINT32)VOS_OK));

    // ���ñ��⺯��
    ulRst = MN_CALL_GetCallInfos(clientId, opId, CallId);

    // ִ�м��
    EXPECT_EQ(VOS_OK, ulRst);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}

TEST_F(Test_MN_CALL_GetCallInfos,Test_MN_CALL_GetCallInfos_002)
{
        // ��������
    MN_CLIENT_ID_T                      clientId;
    MN_OPERATION_ID_T                   opId;
    MN_CALL_ID_T                        pCallId;
    VOS_UINT32                          ulRst;

    // ������ʼ��
    clientId                            = 0;
    opId                                = 0;
    pCallId                             = 1;
    // ���ȫ�ֱ�����ʼ��

    // MOCKER����;
    MOCKER(MN_CALL_SendAppRequest)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    // ���ñ��⺯��
    ulRst = MN_CALL_GetCallInfos(clientId, opId, pCallId);

    // ִ�м��
    EXPECT_EQ(VOS_ERR, ulRst);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


class Test_MN_FillAppReqMsgHeader: public ::testing::Test
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


TEST_F(Test_MN_FillAppReqMsgHeader, Test_MN_FillAppReqMsgHeader_001)
{
	MN_APP_REQ_MSG_STRU                 *pMsg;
    MN_CLIENT_ID_T                      enClientId;
    MN_OPERATION_ID_T                   OpId;
    VOS_UINT16                          usMsgType;
    VOS_UINT32                          ulReceiverPid;
	AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;
  
	enClientId = AT_CLIENT_TAB_APP_INDEX;
    pstAtClientCtx = AT_GetClientCtxAddr(enClientId);
    pstAtClientCtx->stClientConfiguration.enModemId = MODEM_ID_1;

	pMsg = (MN_APP_REQ_MSG_STRU*)malloc(sizeof(MN_APP_REQ_MSG_STRU));
	OpId = 1;
    usMsgType = 1;
    ulReceiverPid = I0_WUEPS_PID_MMA;

	MN_FillAppReqMsgHeader(pMsg, enClientId, OpId, usMsgType, ulReceiverPid);

	EXPECT_EQ(pMsg->clientId, enClientId);
	EXPECT_EQ(pMsg->opId, OpId);
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
#if (OSA_CPU_ACPU == VOS_OSA_CPU)
	EXPECT_EQ(pMsg->ulReceiverPid, I1_WUEPS_PID_MMA);
#endif
#else
    EXPECT_EQ(pMsg->ulReceiverPid, I0_WUEPS_PID_MMA);
#endif
	EXPECT_EQ(pMsg->usMsgName, usMsgType);

	//������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

#if 0
#if (NAS_FEATURE_ALS == FEATURE_ON)
/*******************************************************************
*������:           ��ȡ��ǰʹ�õ���·��,��ǰʹ�õ�����·��1
*���⺯����������: ��ȡ��ǰʹ�õ���·�ţ���ǰʹ�õ�����·��1�Ĵ���
*Ԥ�ڽ����        �ɹ�
************************* �޸ļ�¼ *************************
#  1.��    ��: 2010��1��28��
#    ��    ��: z161729
#    �޸�����: �½�CASE
*******************************************************************/
TEST(Test_MN_CALL_QryAlsLineNo,��ȡ��ǰʹ�õ���·��ʹ�õ�����·��1�Ĵ���)
{

    MOCKER(MN_CALL_GetAlsLineInfo)
        .will(returnValue(MN_CALL_ALS_LINE_NO_1));

    EXPECT_EQ(MN_CALL_QryAlsLineNo(),MN_CALL_ALS_LINE_NO_1);

}

/*******************************************************************
*������:           �������õ���·�Ÿ���NV�͵�ǰʹ�õ���·��,���õ���·�Ų���ȡֵ��Χ֮��
*���⺯����������: �������õ���·�Ÿ���NV�͵�ǰʹ�õ���·��,���õ���·�Ų���ȡֵ��Χ֮�ڵĴ���
*Ԥ�ڽ����        ����MN_ERR_INVALIDPARM
************************* �޸ļ�¼ *************************
#  1.��    ��: 2010��1��28��
#    ��    ��: z161729
#    �޸�����: �½�CASE
*******************************************************************/
TEST(Test_MN_CALL_SetAlsLineNo,�������õ���·�Ÿ���NV�͵�ǰʹ�õ���·�����õ���·�Ų���ȡֵ��Χ֮�ڵĴ���)
{
    MN_CALL_ALS_LINE_NO_ENUM_U8         enAlsLine;

    enAlsLine = MN_CALL_ALS_LINE_NO_MAX;

    EXPECT_EQ(MN_CALL_SetAlsLineNo(enAlsLine),MN_ERR_INVALIDPARM);

}

/*******************************************************************
*������:           �������õ���·�Ÿ���NV�͵�ǰʹ�õ���·��,���õ���·��Ϊ2,���³ɹ�
*���⺯����������: �������õ���·�Ÿ���NV�͵�ǰʹ�õ���·��,���õ���·��Ϊ2,���³ɹ��Ĵ���
*Ԥ�ڽ����        ����MN_ERR_NO_ERROR
************************* �޸ļ�¼ *************************
#  1.��    ��: 2010��1��28��
#    ��    ��: z161729
#    �޸�����: �½�CASE
*******************************************************************/
TEST(Test_MN_CALL_SetAlsLineNo,�������õ���·�Ÿ���NV�͵�ǰʹ�õ���·�����õ���·��Ϊ2���³ɹ��Ĵ���)
{
    MN_CALL_ALS_LINE_NO_ENUM_U8         enAlsLine;

    enAlsLine = MN_CALL_ALS_LINE_NO_2;

    MOCKER(MN_CALL_UpdateAlsLineInfo)
        .will(returnValue((VOS_UINT32)VOS_OK));

    EXPECT_EQ(MN_CALL_SetAlsLineNo(enAlsLine),MN_ERR_NO_ERROR);

}

/*******************************************************************
*������:           �������õ���·�Ÿ���NV�͵�ǰʹ�õ���·��,���õ���·��Ϊ2,����ʧ��
*���⺯����������: �������õ���·�Ÿ���NV�͵�ǰʹ�õ���·��,���õ���·��Ϊ2,����ʧ�ܵĴ���
*Ԥ�ڽ����        ����MN_ERR_UNSPECIFIED
************************* �޸ļ�¼ *************************
#  1.��    ��: 2010��1��28��
#    ��    ��: z161729
#    �޸�����: �½�CASE
*******************************************************************/
TEST(Test_MN_CALL_SetAlsLineNo,�������õ���·�Ÿ���NV�͵�ǰʹ�õ���·�����õ���·��Ϊ2����ʧ�ܵĴ���)
{
    MN_CALL_ALS_LINE_NO_ENUM_U8         enAlsLine;

    enAlsLine = MN_CALL_ALS_LINE_NO_2;

    MOCKER(MN_CALL_UpdateAlsLineInfo)
        .will(returnValue((VOS_UINT32)VOS_ERR));

    EXPECT_EQ(MN_CALL_SetAlsLineNo(enAlsLine),MN_ERR_UNSPECIFIED);

}
#endif


TEST(Test_MN_CALL_CheckUus1ParmValid,����ָ��Ϊ��ʱֱ�ӷ��س���)
{
    MN_CALL_SET_UUS1_TYPE_ENUM_U32      enSetType;

    enSetType = MN_CALL_SET_UUS1_ACT;
    ASSERT_EQ(MN_ERR_INVALIDPARM,MN_CALL_CheckUus1ParmValid(enSetType,VOS_NULL_PTR));
}


TEST(Test_MN_CALL_CheckUus1ParmValid,��Ϣ����ΪPROGRESS���س���)
{
    MN_CALL_SET_UUS1_TYPE_ENUM_U32      enSetType;
    MN_CALL_UUS1_INFO_STRU              stUus1Info;

    enSetType = MN_CALL_SET_UUS1_ACT;
    stUus1Info.enMsgType = MN_CALL_UUS1_MSG_PROGRESS;

    ASSERT_EQ(MN_ERR_INVALIDPARM,MN_CALL_CheckUus1ParmValid(enSetType,&stUus1Info));

}



TEST(Test_MN_CALL_CheckUus1ParmValid,����UUS1ʱ_UUIE���ֽڷǷ����س���)
{
    MN_CALL_SET_UUS1_TYPE_ENUM_U32      enSetType;
    MN_CALL_UUS1_INFO_STRU              stUus1Info;

    enSetType = MN_CALL_SET_UUS1_ACT;
    stUus1Info.enMsgType = MN_CALL_UUS1_MSG_RELEASE_COMPLETE;
    stUus1Info.aucUuie[MN_CALL_IEI_POS] = 0x00;

    ASSERT_EQ(MN_ERR_INVALIDPARM,MN_CALL_CheckUus1ParmValid(enSetType,&stUus1Info));
}


TEST(Test_MN_CALL_CheckUus1ParmValid,ȥ����ANY��Ϣ��UUS1���سɹ�)
{
    MN_CALL_SET_UUS1_TYPE_ENUM_U32      enSetType;
    MN_CALL_UUS1_INFO_STRU              stUus1Info;

    enSetType = MN_CALL_SET_UUS1_DEACT;
    stUus1Info.enMsgType = MN_CALL_UUS1_MSG_ANY;

    ASSERT_EQ(MN_ERR_NO_ERROR,MN_CALL_CheckUus1ParmValid(enSetType,&stUus1Info));
}


TEST(Test_MN_CALL_SetUus1Info,��������Ƿ�ʱֱ�ӷ��س���)
{
    MN_CALL_SET_UUS1_TYPE_ENUM_U32      enSetType;
    MN_CALL_UUS1_INFO_STRU              stUus1Info;

    enSetType = MN_CALL_SET_UUS1_ACT;

    MOCKER(MN_CALL_CheckUus1ParmValid)
        .will(returnValue(MN_ERR_INVALIDPARM));

    ASSERT_EQ(MN_ERR_INVALIDPARM,MN_CALL_SetUus1Info(enSetType,&stUus1Info));
}



TEST(Test_MN_CALL_SetUus1Info,����CC�ڴ��UUS1��Ϣ�ɹ����سɹ�)
{
    MN_CALL_SET_UUS1_TYPE_ENUM_U32      enSetType;
    MN_CALL_UUS1_INFO_STRU              stUus1Info;

    enSetType = MN_CALL_SET_UUS1_ACT;

    MOCKER(MN_CALL_CheckUus1ParmValid)
        .will(returnValue(MN_ERR_NO_ERROR));

    MOCKER(MN_CALL_UpdateCcUus1Info)
        .will(returnValue(MN_ERR_NO_ERROR));

    ASSERT_EQ(MN_ERR_NO_ERROR,MN_CALL_SetUus1Info(enSetType,&stUus1Info));

}


TEST(Test_MN_CALL_QryUus1nfo,��ѯCC�ڴ��UUS1��Ϣʧ�ܷ��ز�ѯʧ��)
{
    VOS_UINT32                          ulActNum;
    MN_CALL_UUS1_INFO_STRU              stUus1Info;

    ulActNum = 0;

    MOCKER(MN_CALL_GetCcUus1Info)
        .will(returnValue((VOS_UINT32)VOS_ERR));

    ASSERT_EQ(MN_ERR_INVALIDPARM,MN_CALL_QryUus1nfo(&ulActNum,&stUus1Info));
}


TEST(Test_MN_CALL_QryUus1nfo,��ѯCC�ڴ��UUS1��Ϣ�ɹ����ز�ѯ�ɹ�)
{
    VOS_UINT32                          ulActNum;
    MN_CALL_UUS1_INFO_STRU              stUus1Info;

    ulActNum = 0;

    MOCKER(MN_CALL_GetCcUus1Info)
        .will(returnValue((VOS_UINT32)VOS_OK));

    ASSERT_EQ(MN_ERR_NO_ERROR,MN_CALL_QryUus1nfo(&ulActNum,&stUus1Info));
}
#endif


class Test_MN_CALL_Sups: public ::testing::Test
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


TEST_F(Test_MN_CALL_Sups, Test_MN_CALL_Sups_001)
{
    //��������
    MN_CLIENT_ID_T                      clientId;
    MN_OPERATION_ID_T                   opId;
    MN_CALL_SUPS_PARAM_STRU             stCallSupsParam;
    VOS_UINT32                          ulRslt;

    //������ʼ��
    clientId = 0;
    opId     = 0;

    //���ȫ�ֱ�����ʼ��

    //MOCKER����
    MOCKER(V_MemCpy)
        .stubs()
        .will(returnValue((VOS_VOID *)0));

    //���ñ��⺯��
    ulRslt = MN_CALL_Sups(clientId, opId, &stCallSupsParam);

    //ִ�м��
    ASSERT_EQ(VOS_OK, ulRslt);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_MN_CALL_SetAlsLineNo: public ::testing::Test
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


TEST_F(Test_MN_CALL_SetAlsLineNo, Test_MN_CALL_SetAlsLineNo_001)
{
    //��������
    TAF_UINT8                           ucIndex;
    MN_CALL_ALS_LINE_NO_ENUM_U8         enAlsLine;
    VOS_UINT32                          ulRslt;

    //������ʼ��
    ucIndex   = 0;
    enAlsLine = MN_CALL_ALS_LINE_NO_1;

    //���ȫ�ֱ�����ʼ��

    //MOCKER����
    MOCKER(V_MemCpy)
        .stubs()
        .will(returnValue((VOS_VOID *)0));

    //���ñ��⺯��
    ulRslt = MN_CALL_SetAlsLineNo(ucIndex, enAlsLine);

    //ִ�м��
    ASSERT_EQ(VOS_OK, ulRslt);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_MN_CALL_SendAppRequest: public ::testing::Test
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


TEST_F(Test_MN_CALL_SendAppRequest, Test_MN_CALL_SendAppRequest_001)
{
    //��������
    MN_CALL_APP_REQ_ENUM_UINT32         enReq;
    MN_CLIENT_ID_T                      clientId;
    MN_OPERATION_ID_T                   opId;
    MN_CALL_ID_T                        callId;
    VOS_UINT32                          ulRslt;

    //������ʼ��
    enReq    = MN_CALL_APP_ORIG_REQ;
    callId   = 1;
    opId     = 0;
    clientId = 0;

    //���ȫ�ֱ�����ʼ��

    //MOCKER����
    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((MsgCB *)VOS_NULL_PTR));

    //���ñ��⺯��
    ulRslt = MN_CALL_SendAppRequest(enReq, clientId, opId, callId, VOS_NULL_PTR);

    //ִ�м��
    ASSERT_EQ(VOS_ERR, ulRslt);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_MN_CALL_SendAppRequest, Test_MN_CALL_SendAppRequest_002)
{
    //��������
    MN_CALL_APP_REQ_ENUM_UINT32         enReq;
    MN_CLIENT_ID_T                      clientId;
    MN_OPERATION_ID_T                   opId;
    MN_CALL_ID_T                        callId;
    VOS_UINT32                          ulRslt;

    //������ʼ��
    enReq    = MN_CALL_APP_ORIG_REQ;
    callId   = 1;
    opId     = 0;
    clientId = 0;

    //���ȫ�ֱ�����ʼ��

    //MOCKER����
    MOCKER(V_MemCpy)
        .stubs()
        .will(returnValue((VOS_VOID *)0));

    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    //���ñ��⺯��
    ulRslt = MN_CALL_SendAppRequest(enReq, clientId, opId, callId, VOS_NULL_PTR);

    //ִ�м��
    ASSERT_EQ(VOS_ERR, ulRslt);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_MN_CALL_SendAppRequest, Test_MN_CALL_SendAppRequest_003)
{
	const MN_CALL_APP_REQ_PARM_UNION    *punParam;
    MN_CLIENT_ID_T                      enClientId;

    punParam = (MN_CALL_APP_REQ_PARM_UNION*)malloc(sizeof(MN_CALL_APP_REQ_PARM_UNION));
	enClientId = AT_CLIENT_TAB_APP_INDEX;

    MOCKER(V_MemCpy)
        .stubs()
        .will(returnValue((VOS_VOID *)0));

	MOCKER(AT_GetDestPid)
		.expects(exactly(1))
        .with(eq(enClientId),eq(I0_WUEPS_PID_TAF))
        .will(returnValue((VOS_UINT32)VOS_OK));

	MN_CALL_SendAppRequest(0,enClientId,0,0,punParam);

	//������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


class Test_MN_CALL_End: public ::testing::Test
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


TEST_F(Test_MN_CALL_End, Test_MN_CALL_End_001)
{
    //��������
    VOS_UINT32                          ulRelt;
    MN_CALL_END_PARAM_STRU             *pstEndParam = VOS_NULL_PTR;

    //������ʼ��

    //���ȫ�ֱ�����ʼ��

    //MOCKER����
    MOCKER(V_MemCpy)
        .stubs()
        .will(returnValue((VOS_VOID *)0));

    //���ñ��⺯��
    ulRelt = MN_CALL_End(TAF_AT_CLIENT, 0, 1, pstEndParam);

    //ִ�м��
    EXPECT_EQ(VOS_OK, ulRelt);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


