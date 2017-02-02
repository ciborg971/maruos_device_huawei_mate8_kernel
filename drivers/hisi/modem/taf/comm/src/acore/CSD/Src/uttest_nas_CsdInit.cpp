#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_nas_CsdInit.h"

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

#if( FEATURE_ON == FEATURE_CSD )

class Test_CSD_FidInit: public ::testing::Test
{
public:
    void SetUp()
	{
		UT_STUB_INIT();

    }
    void TearDown()
    {
    }
private:

};


TEST_F( Test_CSD_FidInit, TEST_CSD_FidInit_001 )
{
    VOS_INIT_PHASE_DEFINE          enInitPhase ;

    enInitPhase = VOS_IP_LOAD_CONFIG;

    MOCKER(VOS_SmBCreate)
        .expects(exactly(2))
        .will(returnValue(VOS_OK));

    MOCKER(VOS_RegisterPIDInfo)
        .with(eq(ACPU_PID_CSD))
        .will(returnValue(VOS_OK));

    MOCKER(VOS_RegisterSelfTaskPrio)
        .with(eq(ACPU_FID_CSD),eq(CSD_UL_ProcDataTask))
        .will(returnValue(VOS_OK));

   MOCKER(VOS_RegisterSelfTaskPrio)
        .with(eq(ACPU_FID_CSD),eq(CSD_DL_ProcDataTask))
        .will(returnValue(VOS_OK));

   MOCKER(VOS_RegisterTaskPrio)
        .will(returnValue(VOS_OK));

    EXPECT_EQ(VOS_OK, CSD_FidInit(enInitPhase));


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}

TEST_F( Test_CSD_FidInit, TEST_CSD_FidInit_005 )
{
    VOS_INIT_PHASE_DEFINE          enInitPhase ;

    enInitPhase = VOS_IP_LOAD_CONFIG;

    MOCKER(VOS_SmBCreate)
        .expects(exactly(2))
        .will(returnValue(VOS_OK));

    MOCKER(VOS_RegisterPIDInfo)
        .with(eq(ACPU_PID_CSD))
        .will(returnValue(VOS_OK));

    MOCKER(VOS_RegisterSelfTask)
        .with(eq(ACPU_FID_CSD),eq(CSD_UL_ProcDataTask))
        .will(returnValue(VOS_OK));

   MOCKER(VOS_RegisterSelfTask)
        .with(eq(ACPU_FID_CSD),eq(CSD_DL_ProcDataTask))
        .will(returnValue(VOS_OK));

   MOCKER(VOS_RegisterMsgTaskPrio)
        .will(returnValue(VOS_ERR));

    EXPECT_EQ(VOS_ERR, CSD_FidInit(enInitPhase));


    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST_F( Test_CSD_FidInit, TEST_CSD_FidInit_002 )
{
    VOS_INIT_PHASE_DEFINE          enInitPhase ;

     enInitPhase = VOS_IP_LOAD_CONFIG;

     MOCKER(VOS_SmBCreate)
         .expects(exactly(2))
         .will(returnValue(VOS_OK));

     MOCKER(VOS_RegisterPIDInfo)
         .with(eq(ACPU_PID_CSD))
         .will(returnValue(VOS_OK));

     MOCKER(VOS_RegisterSelfTask)
         .with(eq(ACPU_FID_CSD),eq(CSD_UL_ProcDataTask))
         .will(returnValue(VOS_OK));

    MOCKER(VOS_RegisterSelfTask)
         .with(eq(ACPU_FID_CSD),eq(CSD_DL_ProcDataTask))
         .will(returnValue(VOS_NULL_BYTE));

     EXPECT_EQ(VOS_ERR, CSD_FidInit(enInitPhase));


     //������ʱ����Ҫ����������λ�ü������
     GlobalMockObject::verify();


}


TEST_F( Test_CSD_FidInit, TEST_CSD_FidInit_003)
{
    VOS_INIT_PHASE_DEFINE          enInitPhase ;

     enInitPhase = VOS_IP_LOAD_CONFIG;

     MOCKER(VOS_SmBCreate)
         .expects(exactly(2))
         .will(returnValue(VOS_OK));

     MOCKER(VOS_RegisterPIDInfo)
         .with(eq(ACPU_PID_CSD))
         .will(returnValue(VOS_OK));

     MOCKER(VOS_RegisterSelfTask)
         .with(eq(ACPU_FID_CSD),eq(CSD_UL_ProcDataTask))
         .will(returnValue(VOS_NULL_BYTE));

     EXPECT_EQ(VOS_ERR, CSD_FidInit(enInitPhase));


     //������ʱ����Ҫ����������λ�ü������
     GlobalMockObject::verify();


}


TEST_F( Test_CSD_FidInit, TEST_CSD_FidInit_004 )
{
     VOS_INIT_PHASE_DEFINE          enInitPhase ;

     enInitPhase = VOS_IP_LOAD_CONFIG;

     MOCKER(VOS_SmBCreate)
         .expects(exactly(2))
         .will(returnValue(VOS_OK));

     MOCKER(VOS_RegisterPIDInfo)
         .with(eq(ACPU_PID_CSD))
         .will(returnValue(VOS_ERR));


     EXPECT_EQ(VOS_ERR, CSD_FidInit(enInitPhase));


     //������ʱ����Ҫ����������λ�ü������
     GlobalMockObject::verify();


}


TEST_F( Test_CSD_FidInit, TEST_CSD_InitDicc_001 )
{

    VOS_INIT_PHASE_DEFINE          enInitPhase ;

    enInitPhase = VOS_IP_LOAD_CONFIG;

    MOCKER(DICC_SingleChnInitAction)
          .will(returnValue(DICC_ERR_BUTT));

    MOCKER(DICC_OpenChannel)
          .expects(never());

    EXPECT_EQ(VOS_ERR,CSD_UL_PidInit(enInitPhase));

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();


}


TEST_F( Test_CSD_FidInit, TEST_CSD_InitDicc_002 )
{

    VOS_INIT_PHASE_DEFINE          enInitPhase ;

    enInitPhase = VOS_IP_LOAD_CONFIG;

    MOCKER(DICC_SingleChnInitAction)
          .will(returnValue(DICC_OK));

    MOCKER(DICC_SingleChnInitAction)
          .will(returnValue(DICC_OK));

    MOCKER(DICC_OpenChannel)
          .with(eq(ACPU_PID_CSD),eq(DICC_CHAN_ID_0),eq(DICC_CHAN_ROLE_SENDER),eq(DICC_CPU_ID_ACPU))
          .will(returnValue(DICC_OK));

    MOCKER(DICC_OpenChannel)
          .with(eq(ACPU_PID_CSD),eq(DICC_CHAN_ID_2),eq(DICC_CHAN_ROLE_RECVER),eq(DICC_CPU_ID_ACPU))
          .will(returnValue(DICC_ERR_BUTT));

    MOCKER(CSD_InitCtx)
          .expects(never());


    EXPECT_EQ(VOS_ERR,CSD_UL_PidInit(enInitPhase));

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();


}

TEST_F( Test_CSD_FidInit, TEST_CSD_InitDicc_003 )
{
    VOS_INIT_PHASE_DEFINE          enInitPhase ;

    enInitPhase = VOS_IP_LOAD_CONFIG;

    MOCKER(DICC_SingleChnInitAction)
          .will(returnValue(DICC_OK));



    MOCKER(DICC_OpenChannel)
          .with(eq(ACPU_PID_CSD),eq(DICC_CHAN_ID_0),eq(DICC_CHAN_ROLE_SENDER),eq(DICC_CPU_ID_ACPU))
          .will(returnValue(DICC_ERR_BUTT));

    MOCKER(CSD_InitCtx)
          .expects(never());


    EXPECT_EQ(VOS_ERR,CSD_UL_PidInit(enInitPhase));

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();


}


TEST_F( Test_CSD_FidInit, TEST_CSD_InitSem_001 )
{
    VOS_INIT_PHASE_DEFINE          enInitPhase ;

    enInitPhase = VOS_IP_LOAD_CONFIG;

    MOCKER(VOS_SmBCreate)
        .will(returnObjectList(VOS_OK, VOS_ERR));


    MOCKER(VOS_SmDelete)
        .with(eq(CSD_GetDownLinkDataSem()));


    EXPECT_EQ(VOS_ERR,CSD_FidInit(enInitPhase));

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();


}


TEST_F( Test_CSD_FidInit, TEST_CSD_InitSem_002 )
{
    VOS_INIT_PHASE_DEFINE          enInitPhase ;

    enInitPhase = VOS_IP_LOAD_CONFIG;

    MOCKER(VOS_SmBCreate)
        .expects(exactly(1))
        .will(returnValue(VOS_ERR));


    MOCKER(VOS_SmDelete)
        .expects(exactly(1))
        .with(eq(CSD_GetDownLinkDataSem()));


    EXPECT_EQ(VOS_ERR,CSD_FidInit(enInitPhase));

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();


}


TEST_F( Test_CSD_FidInit, TEST_CSD_UL_PidInit_001 )
{
    VOS_INIT_PHASE_DEFINE          enInitPhase ;

    enInitPhase = VOS_IP_LOAD_CONFIG;

    MOCKER(DICC_SingleChnInitAction)
          .will(returnValue(DICC_OK));

    MOCKER(DICC_OpenChannel)
          .with(eq(ACPU_PID_CSD),eq(DICC_CHAN_ID_2),eq(DICC_CHAN_ROLE_RECVER),eq(DICC_CPU_ID_ACPU))
          .will(returnValue(DICC_OK));

    MOCKER(DICC_OpenChannel)
          .with(eq(ACPU_PID_CSD),eq(DICC_CHAN_ID_0),eq(DICC_CHAN_ROLE_SENDER),eq(DICC_CPU_ID_ACPU))
          .will(returnValue(DICC_OK));



    EXPECT_EQ(DICC_OK,CSD_UL_PidInit(enInitPhase));

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();


}
#endif

#endif
