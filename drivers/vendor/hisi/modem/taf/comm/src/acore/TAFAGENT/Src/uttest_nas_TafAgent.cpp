#include "gtest/gtest.h"
#include "llt_mockcpp.h"

#include "uttest_nas_TafAgent.h"

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



class Test_TAF_AGENT_PidInit: public ::testing::Test
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


TEST_F(Test_TAF_AGENT_PidInit,Test_TAF_AGENT_PidInit_001)
{
    VOS_UINT32              ulRet;
    VOS_INIT_PHASE_DEFINE   enPhase;
    enPhase = VOS_IP_INITIAL;

    MOCKER(VOS_SmMCreate)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(VOS_SmBCreate)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    ulRet = TAF_AGENT_PidInit(enPhase);

    EXPECT_EQ(VOS_OK, ulRet);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

TEST_F(Test_TAF_AGENT_PidInit,Test_TAF_AGENT_PidInit_002)
{
    VOS_UINT32              ulRet;
    VOS_INIT_PHASE_DEFINE   enPhase;
    enPhase = VOS_IP_INITIAL;

    MOCKER(VOS_SmMCreate)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(VOS_SmBCreate)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    ulRet = TAF_AGENT_PidInit(enPhase);

    EXPECT_EQ(VOS_ERR, ulRet);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

TEST_F(Test_TAF_AGENT_PidInit,Test_TAF_AGENT_PidInit_003)
{
    VOS_UINT32              ulRet;
    VOS_INIT_PHASE_DEFINE   enPhase;

    enPhase = VOS_IP_INITIAL;

    MOCKER(VOS_SmMCreate)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    ulRet = TAF_AGENT_PidInit(enPhase);

    EXPECT_EQ(VOS_ERR, ulRet);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

TEST_F(Test_TAF_AGENT_PidInit,Test_TAF_AGENT_PidInit_004)
{
    VOS_UINT32              ulRet;
    VOS_INIT_PHASE_DEFINE   enPhase;

    enPhase = VOS_IP_STARTUP;

    ulRet = TAF_AGENT_PidInit(enPhase);

    EXPECT_EQ(VOS_OK, ulRet);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

class Test_TAF_AGENT_ProcMsg: public ::testing::Test
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

TEST_F(Test_TAF_AGENT_ProcMsg,Test_TAF_AGENT_ProcMsg_001)
{
    MSG_HEADER_STRU  stMsg;

    TAF_AGENT_SetTafAcpuCnfMsg(VOS_NULL_PTR);
    stMsg.ulSenderPid   = WUEPS_PID_TAF;
    stMsg.ulMsgName     = ID_TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF;

    MOCKER(VOS_SmV)
        .expects(exactly(1));

    TAF_AGENT_ProcMsg((MsgBlock*)&stMsg);

    EXPECT_EQ((VOS_UINT8*)&stMsg, TAF_AGENT_GetTafAcpuCnfMsg());

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
#endif


TEST_F(Test_TAF_AGENT_ProcMsg,Test_TAF_AGENT_ProcMsg_002)
{
    MSG_HEADER_STRU  stMsg;

    TAF_AGENT_SetTafAcpuCnfMsg(VOS_NULL_PTR);
    stMsg.ulSenderPid   = WUEPS_PID_MMC;
    stMsg.ulMsgName     = ID_TAFAGENT_APS_SET_CID_PARA_REQ;

    MOCKER(VOS_SmV)
        .expects(never());

    TAF_AGENT_ProcMsg((MsgBlock*)&stMsg);

    EXPECT_EQ(VOS_NULL_PTR, TAF_AGENT_GetTafAcpuCnfMsg());

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_TAF_AGENT_ProcMsg,Test_TAF_AGENT_ProcMsg_003)
{
    MOCKER(VOS_SmV)
        .expects(never());

    MOCKER(VOS_SmV)
        .expects(never());

    TAF_AGENT_SetTafAcpuCnfMsg(VOS_NULL_PTR);

    TAF_AGENT_ProcMsg((MsgBlock*)VOS_NULL_PTR);

    EXPECT_EQ(VOS_NULL_PTR, TAF_AGENT_GetTafAcpuCnfMsg());

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_TAF_AGENT_FindCidForDial: public ::testing::Test
{
public:
    VOS_UINT8       m_ucCid;

    void SetUp()
	{
		UT_STUB_INIT();
		m_ucCid = 0;
    }
    void TearDown()
    {
        m_ucCid = 0;
    }
};

TEST_F(Test_TAF_AGENT_FindCidForDial,Test_TAF_AGENT_FindCidForDial_001)
{
    VOS_UINT32      ulRet;

    MOCKER(VOS_SmP)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    ulRet = TAF_AGENT_FindCidForDial(AT_CLIENT_TAB_PCUI_INDEX, &m_ucCid);

    EXPECT_EQ(VOS_ERR, ulRet);
    EXPECT_EQ(0, m_ucCid);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

TEST_F(Test_TAF_AGENT_FindCidForDial,Test_TAF_AGENT_FindCidForDial_002)
{
    VOS_UINT32      ulRet;

    MOCKER(VOS_SmP)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    MOCKER(VOS_SmV)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    ulRet = TAF_AGENT_FindCidForDial(AT_CLIENT_TAB_PCUI_INDEX, &m_ucCid);

    EXPECT_EQ(VOS_ERR, ulRet);
    EXPECT_EQ(0, m_ucCid);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


TEST_F(Test_TAF_AGENT_FindCidForDial,Test_TAF_AGENT_FindCidForDial_004)
{
    VOS_UINT32                                  ulRet;
    TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF_STRU     stCnf;

    stCnf.enMsgId             = ID_TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF;
    stCnf.ulRet               = VOS_ERR;
    stCnf.ucCid               = 1;

    MOCKER(VOS_SmP)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(VOS_SmV)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    TAF_AGENT_SetTafAcpuCnfMsg((VOS_UINT8*)&stCnf);
    ulRet = TAF_AGENT_FindCidForDial(AT_CLIENT_TAB_PCUI_INDEX, &m_ucCid);

    EXPECT_EQ(VOS_ERR, ulRet);
    EXPECT_EQ(0, m_ucCid);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

TEST_F(Test_TAF_AGENT_FindCidForDial,Test_TAF_AGENT_FindCidForDial_005)
{
    VOS_UINT32      ulRet;

    MOCKER(VOS_SmP)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((MsgBlock *)VOS_NULL_PTR));

    MOCKER(VOS_SmV)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    ulRet = TAF_AGENT_FindCidForDial(AT_CLIENT_TAB_PCUI_INDEX, &m_ucCid);

    EXPECT_EQ(VOS_ERR, ulRet);
    EXPECT_EQ(0, m_ucCid);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

TEST_F(Test_TAF_AGENT_FindCidForDial,Test_TAF_AGENT_FindCidForDial_006)
{
    VOS_UINT32                                  ulRet;

    MOCKER(VOS_SmP)
        .expects(exactly(2))
        .will(returnObjectList((VOS_UINT32)VOS_OK, (VOS_UINT32)VOS_ERR));

    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(VOS_SmV)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    ulRet = TAF_AGENT_FindCidForDial(AT_CLIENT_TAB_PCUI_INDEX, &m_ucCid);

    EXPECT_EQ(VOS_ERR, ulRet);
    EXPECT_EQ(0, m_ucCid);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_TAF_AGENT_SetPdpCidPara: public ::testing::Test
{
public:
    MN_CLIENT_ID_T                      m_usClientId;
    TAF_PDP_PRIM_CONTEXT_EXT_STRU       m_stPdpPrimContextExt;

    void SetUp()
	{
		UT_STUB_INIT();
	    m_usClientId = 0;
        memset((void*)&m_stPdpPrimContextExt,0,sizeof(TAF_PDP_PRIM_CONTEXT_EXT_STRU));
        m_stPdpPrimContextExt.bitOpApn      = VOS_FALSE;
        m_stPdpPrimContextExt.bitOpPdpAddr  = VOS_FALSE;
    }
    void TearDown()
    {
        m_usClientId = 0;
        memset((void*)&m_stPdpPrimContextExt,0,sizeof(TAF_PDP_PRIM_CONTEXT_EXT_STRU));
        m_stPdpPrimContextExt.bitOpApn      = VOS_FALSE;
        m_stPdpPrimContextExt.bitOpPdpAddr  = VOS_FALSE;
    }
};

TEST_F(Test_TAF_AGENT_SetPdpCidPara,Test_TAF_AGENT_SetPdpCidPara_001)
{
    VOS_UINT32                      ulRet;

    MOCKER(VOS_SmP)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    ulRet = TAF_AGENT_SetPdpCidPara(m_usClientId,&m_stPdpPrimContextExt);

    EXPECT_EQ(VOS_ERR, ulRet);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

TEST_F(Test_TAF_AGENT_SetPdpCidPara,Test_TAF_AGENT_SetPdpCidPara_002)
{
    VOS_UINT32      ulRet;

    MOCKER(VOS_SmP)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    MOCKER(VOS_SmV)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));
    ulRet = TAF_AGENT_SetPdpCidPara(m_usClientId,&m_stPdpPrimContextExt);

    EXPECT_EQ(VOS_ERR, ulRet);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

#if 0

TEST_F(Test_TAF_AGENT_SetPdpCidPara,Test_TAF_AGENT_SetPdpCidPara_003)
{
    VOS_UINT32                                  ulRet;
    TAFAGENT_APS_SET_CID_PARA_CNF_STRU          stCnf;

    stCnf.enMsgId                       = ID_TAFAGENT_APS_SET_CID_PARA_CNF;
    stCnf.ulRet                         = VOS_OK;

    m_stPdpPrimContextExt.bitOpApn      = VOS_TRUE;
    m_stPdpPrimContextExt.bitOpPdpAddr  = VOS_TRUE;

    MOCKER(VOS_SmP)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(VOS_SmP)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    TAF_AGENT_SetTafAcpuCnfMsg((VOS_UINT8*)&stCnf);
    ulRet = TAF_AGENT_SetPdpCidPara(m_usClientId,&m_stPdpPrimContextExt);

    EXPECT_EQ(VOS_OK, ulRet);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}
#endif


TEST_F(Test_TAF_AGENT_SetPdpCidPara,Test_TAF_AGENT_SetPdpCidPara_004)
{
    VOS_UINT32                                  ulRet;
    TAFAGENT_APS_SET_CID_PARA_CNF_STRU          stCnf;

    stCnf.enMsgId                       = ID_TAFAGENT_APS_SET_CID_PARA_CNF;
    stCnf.ulRet                         = VOS_ERR;


    m_stPdpPrimContextExt.bitOpApn      = VOS_TRUE;
    m_stPdpPrimContextExt.bitOpPdpAddr  = VOS_FALSE;

    MOCKER(VOS_SmP)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(VOS_SmV)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    TAF_AGENT_SetTafAcpuCnfMsg((VOS_UINT8*)&stCnf);
    ulRet = TAF_AGENT_SetPdpCidPara(m_usClientId,&m_stPdpPrimContextExt);

    EXPECT_EQ(VOS_ERR, ulRet);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

TEST_F(Test_TAF_AGENT_SetPdpCidPara,Test_TAF_AGENT_SetPdpCidPara_005)
{
    VOS_UINT32      ulRet;

    MOCKER(VOS_SmP)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((MsgBlock *)VOS_NULL_PTR));

    MOCKER(VOS_SmV)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    ulRet = TAF_AGENT_SetPdpCidPara(m_usClientId,&m_stPdpPrimContextExt);

    EXPECT_EQ(VOS_ERR, ulRet);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

TEST_F(Test_TAF_AGENT_SetPdpCidPara,Test_TAF_AGENT_SetPdpCidPara_006)
{
    VOS_UINT32                                  ulRet;

    MOCKER(VOS_SmP)
        .expects(exactly(2))
        .will(returnObjectList((VOS_UINT32)VOS_OK, (VOS_UINT32)VOS_ERR));

    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(VOS_SmV)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    ulRet = TAF_AGENT_SetPdpCidPara(m_usClientId,&m_stPdpPrimContextExt);

    EXPECT_EQ(VOS_ERR, ulRet);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

class Test_TAF_AGENT_GetPdpCidPara: public ::testing::Test
{
public:
    TAF_PDP_PRIM_CONTEXT_STRU                m_stPdpPri;
    VOS_UINT8                       m_ucCid;
    void SetUp()
	{
		UT_STUB_INIT();
		m_ucCid     = 0;
        memset((void*)&m_stPdpPri,0,sizeof(m_stPdpPri));
    }
    void TearDown()
    {
        m_ucCid     = 0;
        memset((void*)&m_stPdpPri,0,sizeof(m_stPdpPri));
    }
};

TEST_F(Test_TAF_AGENT_GetPdpCidPara,Test_TAF_AGENT_GetPdpCidPara_001)
{
    VOS_UINT32                      ulRet;
    TAF_PDP_PRIM_CONTEXT_STRU                stPdpPri;

    MOCKER(VOS_SmP)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    ulRet = TAF_AGENT_GetPdpCidPara(&m_stPdpPri, AT_CLIENT_TAB_PCUI_INDEX, m_ucCid);

    EXPECT_EQ(VOS_ERR, ulRet);
    EXPECT_EQ(0, m_stPdpPri.stPdpAddr.enPdpType);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

TEST_F(Test_TAF_AGENT_GetPdpCidPara,Test_TAF_AGENT_GetPdpCidPara_002)
{
    VOS_UINT32      ulRet;

    MOCKER(VOS_SmP)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_ERR));

    MOCKER(VOS_SmV)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    ulRet = TAF_AGENT_GetPdpCidPara(&m_stPdpPri, AT_CLIENT_TAB_PCUI_INDEX, m_ucCid);

    EXPECT_EQ(VOS_ERR, ulRet);
    EXPECT_EQ(0, m_stPdpPri.stPdpAddr.enPdpType);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}



TEST_F(Test_TAF_AGENT_GetPdpCidPara,Test_TAF_AGENT_GetPdpCidPara_004)
{
    VOS_UINT32                                  ulRet;
    TAFAGENT_APS_SET_CID_PARA_CNF_STRU          stCnf;

    stCnf.enMsgId               = ID_TAFAGENT_APS_SET_CID_PARA_CNF;
    stCnf.ulRet                 = VOS_ERR;

    MOCKER(VOS_SmP)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(VOS_SmV)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    TAF_AGENT_SetTafAcpuCnfMsg((VOS_UINT8*)&stCnf);
    ulRet = TAF_AGENT_GetPdpCidPara(&m_stPdpPri, AT_CLIENT_TAB_PCUI_INDEX, m_ucCid);

    EXPECT_EQ(VOS_ERR, ulRet);
    EXPECT_EQ(0, m_stPdpPri.stPdpAddr.enPdpType);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

TEST_F(Test_TAF_AGENT_GetPdpCidPara,Test_TAF_AGENT_GetPdpCidPara_005)
{
    VOS_UINT32      ulRet;

    MOCKER(VOS_SmP)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(V_AllocMsg)
        .stubs()
        .will(returnValue((MsgBlock *)VOS_NULL_PTR));

    MOCKER(VOS_SmV)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));


    ulRet = TAF_AGENT_GetPdpCidPara(&m_stPdpPri, AT_CLIENT_TAB_PCUI_INDEX, m_ucCid);

    EXPECT_EQ(VOS_ERR, ulRet);
    EXPECT_EQ(0, m_stPdpPri.stPdpAddr.enPdpType);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

TEST_F(Test_TAF_AGENT_GetPdpCidPara,Test_TAF_AGENT_GetPdpCidPara_006)
{
    VOS_UINT32                                  ulRet;

    MOCKER(VOS_SmP)
        .expects(exactly(2))
        .will(returnObjectList((VOS_UINT32)VOS_OK, (VOS_UINT32)VOS_ERR));

    MOCKER(Ps_SendMsg)
        .stubs()
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(VOS_SmV)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    ulRet = TAF_AGENT_GetPdpCidPara(&m_stPdpPri, AT_CLIENT_TAB_PCUI_INDEX, m_ucCid);

    EXPECT_EQ(VOS_ERR, ulRet);
    EXPECT_EQ(0, m_stPdpPri.stPdpAddr.enPdpType);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}


class Test_TAF_AGENT_GetCallInfoReq: public ::testing::Test
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

TEST_F(Test_TAF_AGENT_GetCallInfoReq,Test_TAF_AGENT_GetCallInfoReq_001)
{
    VOS_UINT8                           ucNumOfCalls;
    VOS_UINT32                          ulRlst;
    TAFAGERNT_MN_CALL_INFO_STRU         astCallInfos[MN_CALL_MAX_NUM];
    MN_CLIENT_ID_T                      usClientId;
    TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU *pstCnf;

    pstCnf = (TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU *)malloc(sizeof(TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU));

    pstCnf->ulSenderCpuId                 = VOS_LOCAL_CPUID;
    pstCnf->ulSenderPid                   = WUEPS_PID_TAF;
    pstCnf->ulReceiverCpuId               = VOS_LOCAL_CPUID;
    pstCnf->ulReceiverPid                 = ACPU_PID_TAFAGENT;
    pstCnf->ulLength                      = sizeof(TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstCnf->enMsgId                       = ID_TAFAGENT_MN_GET_CALL_INFO_CNF;
    pstCnf->ucNumOfCalls                  = 1;
    
    usClientId = AT_CLIENT_ID_PCUI;

    MOCKER(TAF_AGENT_GetTafAcpuCnfMsg)
        .stubs()
        .will(returnValue((VOS_UINT8 *)pstCnf));

    MOCKER(VOS_SmP)
        .expects(exactly(2))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(VOS_SmV)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    ulRlst = TAF_AGENT_GetCallInfoReq(usClientId, &ucNumOfCalls, astCallInfos);

    EXPECT_EQ(1, ucNumOfCalls);
    EXPECT_EQ(VOS_OK, ulRlst);

    free(pstCnf);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

class Test_TAF_AGENT_FidInit: public ::testing::Test
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


TEST_F(Test_TAF_AGENT_FidInit, Test_TAF_AGENT_FidInit_001)
{
    VOS_UINT32                          ulRst;
    VOS_INIT_PHASE_DEFINE               enPhase;

    /* ������ʼ�� */
    enPhase = VOS_IP_LOAD_CONFIG;

    /* ׮���� */
    MOCKER(VOS_RegisterPIDInfo)
        .expects(exactly(1))
        .with(eq(ACPU_PID_TAFAGENT), eq((Init_Fun_Type)TAF_AGENT_PidInit), eq((Msg_Fun_Type)TAF_AGENT_ProcMsg))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(VOS_RegisterTaskPrio)
        .expects(exactly(1))
        .with(eq(ACPU_FID_TAFAGENT), eq((VOS_UINT32)TAF_AGENT_TASK_PRIORITY))
        .will(returnValue((VOS_UINT32)VOS_OK));

    /* �������� */

    /* ������ں��� */
    ulRst = TAF_AGENT_FidInit(enPhase);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(VOS_OK, ulRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST_F(Test_TAF_AGENT_FidInit, Test_TAF_AGENT_FidInit_002)
{
    VOS_UINT32                          ulRst;
    VOS_INIT_PHASE_DEFINE               enPhase;

    /* ������ʼ�� */
    enPhase = VOS_IP_LOAD_CONFIG;

    /* ׮���� */
    MOCKER(VOS_RegisterPIDInfo)
        .expects(exactly(1))
        .with(eq(ACPU_PID_TAFAGENT), eq((Init_Fun_Type)TAF_AGENT_PidInit), eq((Msg_Fun_Type)TAF_AGENT_ProcMsg))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    /* �������� */

    /* ������ں��� */
    ulRst = TAF_AGENT_FidInit(enPhase);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(VOS_ERR, ulRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST_F(Test_TAF_AGENT_FidInit, Test_TAF_AGENT_FidInit_003)
{
    VOS_UINT32                          ulRst;
    VOS_INIT_PHASE_DEFINE               enPhase;

    /* ������ʼ�� */
    enPhase = VOS_IP_LOAD_CONFIG;

    /* ׮���� */
    MOCKER(VOS_RegisterPIDInfo)
        .expects(exactly(1))
        .with(eq(ACPU_PID_TAFAGENT), eq((Init_Fun_Type)TAF_AGENT_PidInit), eq((Msg_Fun_Type)TAF_AGENT_ProcMsg))
        .will(returnValue((VOS_UINT32)VOS_OK));

	MOCKER(VOS_RegisterTaskPrio)
		.expects(exactly(1))
		.with(eq(ACPU_FID_TAFAGENT), eq((VOS_UINT32)TAF_AGENT_TASK_PRIORITY))
        .will(returnValue((VOS_UINT32)VOS_ERR));

    /* �������� */

    /* ������ں��� */
    ulRst = TAF_AGENT_FidInit(enPhase);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(VOS_ERR, ulRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


TEST_F(Test_TAF_AGENT_FidInit, Test_TAF_AGENT_FidInit_004)
{
    VOS_UINT32                          ulRst;
    VOS_INIT_PHASE_DEFINE               enPhase;

    /* ������ʼ�� */
    enPhase = VOS_IP_FARMALLOC;

    /* ׮���� */
    MOCKER(VOS_RegisterPIDInfo)
        .expects(never());
    
    /* �������� */

    /* ������ں��� */
    ulRst = RNIC_FidInit(enPhase);

    /* ��ȡ��� */

    /* ����ƥ�� */
    EXPECT_EQ(VOS_OK, ulRst);

    enPhase = VOS_IP_BUTT;
    ulRst = TAF_AGENT_FidInit(enPhase);
    EXPECT_EQ(VOS_OK, ulRst);

    //������ʱ, ��Ҫ����������λ�ü������
    GlobalMockObject::verify();

}


class Test_TAF_AGENT_GetAntState: public ::testing::Test
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

TEST_F(Test_TAF_AGENT_GetAntState,Test_TAF_AGENT_GetAntState_001)
{
    VOS_UINT32                          ulRlst;
    MN_CLIENT_ID_T                      usClientId;
	VOS_UINT16							usAntState;
    TAFAGENT_MTA_GET_ANT_STATE_CNF_STRU *pstCnf;

    pstCnf = (TAFAGENT_MTA_GET_ANT_STATE_CNF_STRU *)malloc(sizeof(TAFAGENT_MTA_GET_ANT_STATE_CNF_STRU));

    pstCnf->ulSenderCpuId                 = VOS_LOCAL_CPUID;
    pstCnf->ulSenderPid                   = I0_UEPS_PID_MTA;
    pstCnf->ulReceiverCpuId               = VOS_LOCAL_CPUID;
    pstCnf->ulReceiverPid                 = ACPU_PID_TAFAGENT;
    pstCnf->ulLength                      = sizeof(TAFAGENT_MTA_GET_ANT_STATE_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstCnf->enMsgId                       = ID_TAFAGENT_MTA_GET_ANT_STATE_CNF;
    pstCnf->usAntState                    = 1;
	pstCnf->ulRslt						  = 0;

    usClientId = AT_CLIENT_ID_PCUI;

    MOCKER(VOS_SmP)
        .expects(exactly(2))
        .will(returnValue((VOS_UINT32)VOS_OK));

    MOCKER(TAF_AGENT_GetTafAcpuCnfMsg)
        .stubs()
        .will(returnValue((VOS_UINT8 *)pstCnf));

    MOCKER(VOS_SmV)
        .expects(exactly(1))
        .will(returnValue((VOS_UINT32)VOS_OK));

    ulRlst = TAF_AGENT_GetAntState(usClientId, &usAntState);

    EXPECT_EQ(1, usAntState);
    EXPECT_EQ(VOS_OK, ulRlst);

    free(pstCnf);

    //������ʱ����Ҫ����������λ�ü������
    GlobalMockObject::verify();
}

